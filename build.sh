#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

echo $DIR

make clean -C ${DIR}/server && make -C ${DIR}/server
cp ${DIR}/server/mickye_server ${DIR}

make clean -C ${DIR}/client && make -C ${DIR}/client
cp ${DIR}/client/mickye_client ${DIR}