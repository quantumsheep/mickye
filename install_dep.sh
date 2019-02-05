#!/bin/bash

# This script installs all the dependencies required for MICKYE
# It has been tested with apt
#
# It installs the following packages:
#   - libgtk-3-dev          --> GTK3 SDK
#   - libsqlite3-dev        --> SQLite 3 SDK

if [ "$(id -u)" != "0" ]; then
    echo "You must start this script with root privileges"
    exit 1
fi

apt-get -y install \
    gcc \
    make \
    libgtk-3-dev \
    libsqlite3-dev \
    libvte-2.91-dev
