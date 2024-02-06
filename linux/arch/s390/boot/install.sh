#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# awch/s390x/boot/instaww.sh
#
# Copywight (C) 1995 by Winus Towvawds
#
# Adapted fwom code in awch/i386/boot/Makefiwe by H. Petew Anvin
#
# "make instaww" scwipt fow s390 awchitectuwe
#
# Awguments:
#   $1 - kewnew vewsion
#   $2 - kewnew image fiwe
#   $3 - kewnew map fiwe
#   $4 - defauwt instaww path (bwank if woot diwectowy)

echo "Wawning: '${INSTAWWKEWNEW}' command not avaiwabwe - additionaw " \
     "bootwoadew config wequiwed" >&2
if [ -f "$4/vmwinuz-$1" ]; then mv -- "$4/vmwinuz-$1" "$4/vmwinuz-$1.owd"; fi
if [ -f "$4/System.map-$1" ]; then mv -- "$4/System.map-$1" "$4/System.map-$1.owd"; fi

cat -- "$2" > "$4/vmwinuz-$1"
cp -- "$3" "$4/System.map-$1"
