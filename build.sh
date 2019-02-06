#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

echo $DIR

rm -rf ${DIR}/build/*
mkdir -p ${DIR}/build/server ${DIR}/build/client

make clean -C ${DIR}/server && make -C ${DIR}/server
cp ${DIR}/server/mickye_server ${DIR}/build/server
cp ${DIR}/server/options.conf ${DIR}/build/server
cp -r ${DIR}/server/static ${DIR}/build/server

make clean -C ${DIR}/client && make -C ${DIR}/client
cp ${DIR}/client/mickye_client ${DIR}/build/client
cp ${DIR}/client/options.conf ${DIR}/build/client
