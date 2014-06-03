
Dependencies
=========

In order to install all the dependencies and build the GstSupport library run:

```
./get_build_deps.sh
```

Run
========
In order to run the GstQtWidget open the testgst.pro using QTCreator: build and run it.


Example Usage
=========

- Send the video streaming from /dev/video2 to the host 10.255.32.212 at the port 1235 :

```
gst-launch v4l2src device=/dev/video2 ! 'video/x-raw-yuv,width=640,height=480' !  x264enc pass=qual quantizer=20 tune=zerolatency ! rtph264pay ! udpsink host=10.255.32.212 port=1235
```

- Receive the video streaming from the port 1256 : 

```
gst-launch udpsrc port=1256 ! "application/x-rtp, payload=127" ! rtph264depay ! ffdec_h264 ! xvimagesink sync=false
```

- Send the video streaming from /dev/video0 to multiple hosts : 

```
gst-launch v4l2src device=/dev/video0 ! 'video/x-raw-yuv,width=640,height=480' ! x264enc pass=qual quantizer=20 tune=zerolatency ! rtph264pay ! multiudpsink clients="127.0.0.1:1245;127.0.0.1:1256" rtpbin.send_rtcp_src_0
```

- Send the video streaming from /dev/video2 to multiple hosts and save the video on a local file : 

```
gst-launch v4l2src device=/dev/video2 ! 'video/x-raw-yuv,width=640,height=480' ! tee name=tp tp. ! queue ! x264enc pass=qual quantizer=20 tune=zerolatency ! rtph264pay ! multiudpsink clients="127.0.0.1:1245,192.168.1.166:1256,192.168.1.121:1356" rtpbin.send_rtcp_src_0 tp. ! queue ! theoraenc quality=32 !  oggmux ! filesink location=sample.mp4
```


