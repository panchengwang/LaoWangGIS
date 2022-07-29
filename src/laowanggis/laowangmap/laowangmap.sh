#!/bin/sh

OS=`uname`

CUR_DIR=$(cd `dirname $0`; pwd)
export QML2_IMPORT_PATH=.:${CUR_DIR}/../laowangqml

echo $OS
if [ $OS = 'Darwin' ] ; then
    ${CUR_DIR}/laowangmap.app/Contents/MacOS/laowangmap
else
    ${CUR_DIR}/laowangmap
fi


