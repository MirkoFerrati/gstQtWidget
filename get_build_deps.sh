#!/bin/bash
echo "Installing the dependencies... WORKING on Ubuntu 13.04"
sudo apt-get install libgstreamer-plugins* gstreamer0.10-ffmpeg gstreamer-tools gstreamer0.10-plugins-ugly
cd GstSupport && mkdir -p build
cd build && cmake .. && make

echo "For other Ubuntu version, it will probably fail."
echo "Workaround to get gstreamer0.10-ffmpeg on Ubuntu 14.04:"
echo "sudo add-apt-repository ppa:mc3man/trusty-media
sudo apt-get update
sudo apt-get install gstreamer0.10-ffmpeg"
