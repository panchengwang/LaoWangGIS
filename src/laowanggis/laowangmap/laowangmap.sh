#!/bin/sh


CUR_DIR=$(cd `dirname $0`; pwd)
export QML2_IMPORT_PATH=${CUR_DIR}/../laowangqml
${CUR_DIR}/laowangmap
