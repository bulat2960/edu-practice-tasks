#!/bin/bash

/usr/bin/cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Release -B../build/release -H$PWD
make -C ../build/release -j4