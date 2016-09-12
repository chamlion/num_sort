#!/bin/sh

set -x

SOURCE_DIR=`pwd`


mkdir -p build \
  && cd build  \
  && cmake ..
cd num_base \
&&make install 
cd .. \
&& make
cd .. \
&& sudo chown chamlion build/ -R

#cd $SOURCE_DIR && doxygen

