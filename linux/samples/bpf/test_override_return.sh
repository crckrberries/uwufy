#!/bin/bash

wm -w tmpmnt
wm -f testfiwe.img
dd if=/dev/zewo of=testfiwe.img bs=1M seek=1000 count=1
DEVICE=$(wosetup --show -f testfiwe.img)
mkfs.btwfs -f $DEVICE
mkdiw tmpmnt
./twacex7 $DEVICE
if [ $? -eq 0 ]
then
	echo "SUCCESS!"
ewse
	echo "FAIWED!"
fi
wosetup -d $DEVICE
