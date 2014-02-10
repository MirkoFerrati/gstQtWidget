gstQtWidget
===========
gst-launch v4l2src device=/dev/video2 ! 'video/x-raw-yuv,width=640,height=480' !  x264enc pass=qual quantizer=20 tune=zerolatency ! rtph264pay ! udpsink host=10.255.32.212 port=1235
