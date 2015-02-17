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

void initSaveVideo(std::string filename, GstElement ** result, std::string device)
{
    std::string inPipelineDescription = "v4l2src device=";
    inPipelineDescription.append(device);
    inPipelineDescription.append(" ! video/x-raw-yuv,framerate=30/1 ! \
    clockoverlay font-desc=\"Sans 12\" halign=left valign=top time-format=\"%Y/%m/%d %H:%M:%S\" ! \
    x264enc pass=qual quantizer=20 tune=zerolatency name=\"enc\" ! matroskamux name=\"mux\" ! filesink location=");
    inPipelineDescription.append(filename);
    inPipelineDescription.append(" name=\"save\"");
    GError * error(0);
    *result = gst_parse_launch(inPipelineDescription.c_str(), &error);
    if (error)
    {
        std::string msg = std::string("Parsing pipeline failed. Reason: ") + error->message;
        throw std::runtime_error(msg);
    }
    
}

std::string getCommand(yarp::os::BufferedPort<yarp::os::Bottle>& command_port)
{
//     //TODO: replace with some yarp stuff!
//     std::string cmd="";
//     std::cin>>cmd;
//     return cmd;
//     
    yarp::os::Bottle* bot_command = command_port.read(false);
    if(bot_command != NULL) {
        std::string command_i= bot_command->get(0).asString();
        return command_i;
    }
    return "";
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
    temp.append(buffer);
    temp.append(".mp4");
    std::cout<<"saving file"<<temp<<std::endl;
    GstElement* filesink = gst_bin_get_by_name(GST_BIN(pipeline), "save");
    GstElement* filemux = gst_bin_get_by_name(GST_BIN(pipeline), "mux");
    GstElement* encoder = gst_bin_get_by_name(GST_BIN(pipeline), "enc");
    gst_element_set_state(GST_ELEMENT(encoder), GST_STATE_NULL);
    gst_element_set_state(GST_ELEMENT(filesink), GST_STATE_NULL);
    gst_element_set_state(GST_ELEMENT(filemux), GST_STATE_NULL);
    g_object_set (G_OBJECT (filesink), "location", temp.c_str(), NULL);
    gst_element_set_state(GST_ELEMENT(encoder), GST_STATE_PLAYING);
    gst_element_set_state(GST_ELEMENT(filemux), GST_STATE_PLAYING);
    gst_element_set_state(GST_ELEMENT(filesink), GST_STATE_PLAYING);
}

int main(int argc, char *argv[])
{
    if (argc<2) 
    {
        std::cout<<"usage: webcam_rec video0  \n  missing video name parameter, such as video0, video1 and so on"<<std::endl;
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
    yarp::os::BufferedPort<yarp::os::Bottle> port;
    port.open("/camera_rec/"+prefix);
    prefix.append("-");
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    char buffer [80];
    strftime (buffer,80,"%Y-%m-%d-%H-%M-%S",now);
    std::string temp=prefix;
    temp.append(buffer);
    temp.append(".mp4");
    initSaveVideo(temp, &pipeline, "/dev/"+prefix);
    int counter=0;
    bool exit=false;
    gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_PLAYING);

    while(!exit)
    {
        std::string cmd=getCommand(port);
        if (cmd=="quit") exit=true;
        if (cmd=="save") 
        {
            if (counter>5)
            {
                save(pipeline,prefix);
                counter=0;
            }
        }
        counter++;
        if (counter==20)
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