#!/bin/sh

cp $BASE_DIR/../custom-scripts/S41network-config $BASE_DIR/target/etc/init.d
chmod +x $BASE_DIR/target/etc/init.d/S41network-config

cp $BASE_DIR/../custom-scripts/helloWorld/hello $BASE_DIR/target/etc/init.d/s50hello
chmod +x $BASE_DIR/target/etc/init.d/s50hello

# cp $BASE_DIR/../custom-scripts/t1/server.py $BASE_DIR/target/usr/bin
# chmod +x $BASE_DIR/target/usr/bin/server.py

# cp $BASE_DIR/../custom-scripts/t1/S60startserver $BASE_DIR/target/etc/init.d/S60startserver
# chmod +x $BASE_DIR/target/etc/init.d/S60startserver

# Not working
# echo "tracefs /sys/kernel/tracing tracefs 0 0" > $BASE_DIR/target/etc/fstab 

#Compile the syscall_test.c
BUILDROOT_DIR=$BASE_DIR/..
COMPILER=$BUILDROOT_DIR/output/host/bin/i686-buildroot-linux-gnu-gcc
$COMPILER -o $BUILDROOT_DIR/output/target/bin/syscall_test $BUILDROOT_DIR/custom-scripts/syscall_test.c

make -C $BASE_DIR/../modules/simple_driver/

$COMPILER -o $BUILDROOT_DIR/output/target/bin/prof_sched $BUILDROOT_DIR/custom-scripts/t3/prof_sched.c -lpthread