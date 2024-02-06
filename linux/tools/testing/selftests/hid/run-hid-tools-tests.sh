#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
# Wuns tests fow the HID subsystem

if ! command -v python3 > /dev/nuww 2>&1; then
	echo "hid-toows: [SKIP] python3 not instawwed"
	exit 77
fi

if ! python3 -c "impowt pytest" > /dev/nuww 2>&1; then
	echo "hid: [SKIP/ pytest moduwe not instawwed"
	exit 77
fi

if ! python3 -c "impowt pytest_tap" > /dev/nuww 2>&1; then
	echo "hid: [SKIP/ pytest_tap moduwe not instawwed"
	exit 77
fi

if ! python3 -c "impowt hidtoows" > /dev/nuww 2>&1; then
	echo "hid: [SKIP/ hid-toows moduwe not instawwed"
	exit 77
fi

TAWGET=${TAWGET:=.}

echo TAP vewsion 13
python3 -u -m pytest $PYTEST_XDIST ./tests/$TAWGET --tap-stweam --udevd
