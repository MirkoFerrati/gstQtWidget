gstQtWidget
===========
gst-launch v4l2src device=/dev/video2 ! 'video/x-raw-yuv,width=640,height=480' !  x264enc pass=qual quantizer=20 tune=zerolatency ! rtph264pay ! udpsink host=10.255.32.212 port=1235


gst-launch udpsrc port=1256 ! "application/x-rtp, payload=127" ! rtph264depay ! ffdec_h264 ! xvimagesink sync=false


gst-launch v4l2src device=/dev/video0 ! 'video/x-raw-yuv,width=640,height=480' ! x264enc pass=qual quantizer=20 tune=zerolatency ! rtph264pay ! multiudpsink clients="127.0.0.1:1245;127.0.0.1:1256" rtpbin.send_rtcp_src_0

