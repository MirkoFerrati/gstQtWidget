# 
#  Copyright (C) 2014 Walkman
#  Author: 
#  email: 
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU Lesser General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public License
#  along with this program. If not, see <http://www.gnu.org/licenses/>
#

cmake_minimum_required(VERSION 2.8.12)
if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 OLD)
    cmake_policy(SET CMP0005 NEW)
    cmake_policy(SET CMP0017 NEW)
endif(COMMAND cmake_policy)
set (PROJECT_NAME gstreamer-gui)
project(${PROJECT_NAME})

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

find_package(Qt4 COMPONENTS QtCore QtGui REQUIRED)
find_package(YARP)
include(${QT_USE_FILE})
find_library(GST NAMES gst PATHS /usr/lib/gstreamer-0.10/)

include_directories(
/usr/include/gstreamer-0.10
#    /opt/local/include
#    /opt/local/include/gstreamer-0.10
    /usr/include/glib-2.0
    /usr/include/gstreamer-0.10/gst
    /usr/lib/x86_64-linux-gnu/glib-2.0/include/
   /usr/lib/glib-2.0/include
   /usr/include/libxml2
    ${PROJECT_SOURCE_DIR}/include
)
# add_subdirectory(GstSupport/)

qt4_wrap_cpp(MOC_FILES
#   streaming_window.h 
  mainwindow.h
)
# add include directories
INCLUDE_DIRECTORIES(
# GstSupport/include
build/
)

# link_directories( GstSupport/build/ )

ADD_EXECUTABLE(${PROJECT_NAME} ${MOC_FILES} ${FORMS_HEADERS}
main.cpp 
# streaming_window.cpp 
mainwindow.cpp
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
${QT_LIBRARIES} 
${YARP_LIBRARIES}
# GstSupport 
gstinterfaces-0.10
gstreamer-0.10 gobject-2.0 gmodule-2.0 gthread-2.0 xml2 pthread z m glib-2.0   gstinterfaces-0.10
)

