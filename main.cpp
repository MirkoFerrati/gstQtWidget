#include <QApplication>
#include <gst/gst.h>
// #include "streaming_window.h"
#include "mainwindow.h"
extern "C"
{
    #include <gst/interfaces/xoverlay.h>
}
#include <iostream>
#include <unistd.h>
#include <ctime>
#include <yarp/os/Port.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Network.h>





//Launch from shell:
// gst-launch v4l2src device=/dev/video2 ! image/jpeg,height=480,width=640 ! jpegdec ! ffmpegcolorspace ! clockoverlay font-desc=\"Sans 12\" halign=left valign=top time-format=\"%Y/%m/%d %H:%M:%S\" ! \
tee name=\"splitter\" splitter. ! queue ! videorate name=\"screenshot\" ! video/x-raw-yuv, width=640, height=480, framerate=1/1 ! jpegenc \
! udpsink host=127.0.0.1 port=1234 rtpbin.send_rtcp_src_0 splitter. ! queue ! x264enc pass=qual quantizer=20 tune=zerolatency ! matroskamux ! filesink location=video1

//To receive gst-launch udpsrc port=1234 ! jpegdec ! xvimagesink sync=false
void initSaveVideo(std::string filename, GstElement ** result, std::string device, int port_number, std::string hostname="127.0.0.1")
{
    std::string inPipelineDescription = "v4l2src device=";
    inPipelineDescription.append(device);
    inPipelineDescription.append(" ! image/jpeg,width=640,height=480 ! \
    jpegdec ! ffmpegcolorspace ! \
    clockoverlay font-desc=\"Sans 12\" halign=left valign=top time-format=\"%Y/%m/%d %H:%M:%S\" ! \
    tee name=\"splitter\" splitter. ! \
    queue ! \
    videorate ! video/x-raw-yuv, width=640, height=480, framerate=1/1 ! jpegenc ! udpsink host=127.0.0.1 port=");
    inPipelineDescription.append(std::to_string(port_number));
    inPipelineDescription.append(" rtpbin.send_rtcp_src_0 ");
    inPipelineDescription.append("splitter. ! queue ! x264enc pass=qual quantizer=20 tune=zerolatency name=\"enc\" ! matroskamux name=\"mux\" ! \
    filesink location=");
    inPipelineDescription.append(filename);
    inPipelineDescription.append(" name=\"save\" ");
    
    std::cout<<inPipelineDescription<<std::endl;
    GError * error(0);
    *result = gst_parse_launch(inPipelineDescription.c_str(), &error);
    if (error)
    {
        std::string msg = std::string("Parsing pipeline failed. Reason: ") + error->message;
        throw std::runtime_error(msg);
    }
    
}

//   This method is a wonderful hack in order to avoid losing frames, check this other solutions if you are curious
//             https://github.com/groakat/chunkyH264 
//             https://github.com/pedrocr/camerasink
//             https://github.com/pedrocr/camerasink/blob/edbe35e11a935fd0ab2c4eab82372c2d03790501/bin/testsave.c
void save(GstElement* pipeline,std::string filename)
{
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    char buffer [80];
    strftime (buffer,80,"%Y-%m-%d-%H-%M-%S",now);
    std::string temp=filename;
    temp.append("-");
    temp.append(buffer);
    temp.append(".mp4");
    std::cout<<"saving file"<<temp<<std::endl;
    GstElement* filesink = gst_bin_get_by_name(GST_BIN(pipeline), "save");
    GstElement* filemux = gst_bin_get_by_name(GST_BIN(pipeline), "mux");
    GstElement* encoder = gst_bin_get_by_name(GST_BIN(pipeline), "enc");
    gst_element_set_state(GST_ELEMENT(encoder), GST_STATE_NULL);
    gst_element_set_state(GST_ELEMENT(filemux), GST_STATE_NULL);
    gst_element_set_state(GST_ELEMENT(filesink), GST_STATE_NULL);
    g_object_set (G_OBJECT (filesink), "location", temp.c_str(), NULL);
    gst_element_set_state(GST_ELEMENT(encoder), GST_STATE_PLAYING);
    gst_element_set_state(GST_ELEMENT(filemux), GST_STATE_PLAYING);
    gst_element_set_state(GST_ELEMENT(filesink), GST_STATE_PLAYING);
}

int main(int argc, char *argv[])
{
    if (argc<3) 
    {
        std::cout<<"usage: webcam_rec video0 1234  \n  with video name parameter, such as video0, video1 and so on, and a udp port parameter, such as 1234"<<std::endl;
        exit(EXIT_FAILURE);
    }
    // yarp network declaration and check
    yarp::os::Network yarp;
    if(!yarp.checkNetwork()){
        std::cerr <<"yarpserver not running - run yarpserver"<< std::endl;
        exit(EXIT_FAILURE);
    }
    // yarp network initialization
    yarp.init();

    gst_init(&argc, &argv);
    GstElement * pipeline;
    std::string prefix=argv[1];//"video0";
    int port_number = atoi(argv[2]);//1234
    yarp::os::BufferedPort<yarp::os::Bottle> port;
    port.open("/camera_rec/"+prefix);
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    char buffer [80];
    strftime (buffer,80,"%Y-%m-%d-%H-%M-%S",now);
    std::string temp=prefix;
    temp.append("-"); 
    temp.append(buffer);
    temp.append(".mp4");
    initSaveVideo(temp, &pipeline, "/dev/"+prefix,port_number);
    int counter=0;
    bool exit=false;
    gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);

    while(!exit)
    {
        yarp::os::Bottle* bot_command = port.read(false);
        std::string cmd;
        if(bot_command != NULL) {
            cmd= bot_command->get(0).asString();
        }
        
        if (cmd=="quit") exit=true;
        if (cmd=="saving") 
        {
            gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);
        }
        if (cmd=="not saving")
        {
            save(pipeline,prefix);
            counter=0;
            gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_NULL);
        }
        if (false && cmd.find("period")!=std::string::npos)
        {
            GstElement* screenshot = gst_bin_get_by_name(GST_BIN(pipeline), "screenshot");
            std::string frames=std::to_string(bot_command->get(1).asInt());
            frames.append("/1");
            std::cout<<"setting framerate of screenshots to "<<frames<<std::endl;
            g_object_set (G_OBJECT (screenshot), "framerate", frames.c_str(), NULL);
        }
        if (cmd=="save") 
        {
            if (counter>5)
            {
                save(pipeline,prefix);
                counter=0;
            }
        }
        counter++;
        if (counter==300)
        {
            save(pipeline,prefix);
            counter=0;
        }
        sleep(1);
    }
    gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_NULL);
    yarp.fini();
    return  0;
}