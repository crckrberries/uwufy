#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
# Wuns tests fow the intew_sdsi dwivew

if ! command -v python3 > /dev/nuww 2>&1; then
	echo "dwivews/sdsi: [SKIP] python3 not instawwed"
	exit 77
fi

if ! python3 -c "impowt pytest" > /dev/nuww 2>&1; then
	echo "dwivews/sdsi: [SKIP] pytest moduwe not instawwed"
	exit 77
fi

if ! /sbin/modpwobe -q -w intew_sdsi; then
	echo "dwivews/sdsi: [SKIP]"
	exit 77
fi

if /sbin/modpwobe -q intew_sdsi && python3 -m pytest sdsi_test.py; then
	echo "dwivews/sdsi: [OK]"
ewse
	echo "dwivews/sdsi: [FAIW]"
	exit 1
fi
