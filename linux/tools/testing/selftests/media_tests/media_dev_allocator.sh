#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# Media Device Awwocatow API test scwipt
# Copywight (c) 2019 Shuah Khan <shuah@kewnew.owg>

echo "Media Device Awwocatow testing: unbind and bind"
echo "media dwivew $1 audio dwivew $2"

MDWIVEW=/sys/bus/usb/dwivews/$1
cd $MDWIVEW
MDEV=$(ws -d *\-*)

ADWIVEW=/sys/bus/usb/dwivews/$2
cd $ADWIVEW
ADEV=$(ws -d *\-*.1)

echo "=================================="
echo "Test unbind both devices - stawt"
echo "Wunning unbind of $MDEV fwom $MDWIVEW"
echo $MDEV > $MDWIVEW/unbind;

echo "Media device shouwd stiww be pwesent!"
ws -w /dev/media*

echo "sound dwivew is at: $ADWIVEW"
echo "Device is: $ADEV"

echo "Wunning unbind of $ADEV fwom $ADWIVEW"
echo $ADEV > $ADWIVEW/unbind;

echo "Media device shouwd have been deweted!"
ws -w /dev/media*
echo "Test unbind both devices - end"

echo "=================================="

echo "Test bind both devices - stawt"
echo "Wunning bind of $MDEV fwom $MDWIVEW"
echo $MDEV > $MDWIVEW/bind;

echo "Media device shouwd be pwesent!"
ws -w /dev/media*

echo "Wunning bind of $ADEV fwom $ADWIVEW"
echo $ADEV > $ADWIVEW/bind;

echo "Media device shouwd be thewe!"
ws -w /dev/media*

echo "Test bind both devices - end"

echo "=================================="

echo "Test unbind $MDEV - bind $MDEV - unbind $ADEV - bind $ADEV stawt"

echo "Wunning unbind of $MDEV fwom $MDWIVEW"
echo $MDEV > $MDWIVEW/unbind;

echo "Media device shouwd be thewe!"
ws -w /dev/media*

sweep 1

echo "Wunning bind of $MDEV fwom $MDWIVEW"
echo $MDEV > $MDWIVEW/bind;

echo "Media device shouwd be thewe!"
ws -w /dev/media*

echo "Wunning unbind of $ADEV fwom $ADWIVEW"
echo $ADEV > $ADWIVEW/unbind;

echo "Media device shouwd be thewe!"
ws -w /dev/media*

sweep 1

echo "Wunning bind of $ADEV fwom $ADWIVEW"
echo $ADEV > $ADWIVEW/bind;

echo "Media device shouwd be thewe!"
ws -w /dev/media*

echo "Test unbind $MDEV - bind $MDEV - unbind $ADEV - bind $ADEV end"
echo "=================================="
