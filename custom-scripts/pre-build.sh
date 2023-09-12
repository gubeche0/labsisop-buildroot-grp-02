#!/bin/sh

cp $BASE_DIR/../custom-scripts/S41network-config $BASE_DIR/target/etc/init.d
chmod +x $BASE_DIR/target/etc/init.d/S41network-config

cp $BASE_DIR/../custom-scripts/helloWorld/hello $BASE_DIR/target/etc/init.d/s50hello
chmod +x $BASE_DIR/target/etc/init.d/s50hello

cp $BASE_DIR/../custom-scripts/t1/server.py $BASE_DIR/target/usr/bin
chmod +x $BASE_DIR/target/usr/bin/server.py