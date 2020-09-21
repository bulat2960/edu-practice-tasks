#!/bin/bash

/usr/bin/cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=Debug -Bbuild/debug -H$PWD
make -C build/debug -j4
