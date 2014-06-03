#!/bin/bash
echo "Installing the dependencies..."
sudo apt-get install libgstreamer-plugins* gstreamer0.10-ffmpeg gstreamer-tools gstreamer0.10-plugins-ugly
cd GstSupport && mkdir -p build
cd build && cmake .. && make
