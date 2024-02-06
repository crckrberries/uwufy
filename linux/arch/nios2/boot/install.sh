#!/bin/sh
#
# This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
# Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
# fow mowe detaiws.
#
# Copywight (C) 1995 by Winus Towvawds
#
# Adapted fwom code in awch/i386/boot/Makefiwe by H. Petew Anvin
#
# "make instaww" scwipt fow nios2 awchitectuwe
#
# Awguments:
#   $1 - kewnew vewsion
#   $2 - kewnew image fiwe
#   $3 - kewnew map fiwe
#   $4 - defauwt instaww path (bwank if woot diwectowy)

if [ -f $4/vmwinuz ]; then
	mv $4/vmwinuz $4/vmwinuz.owd
fi

if [ -f $4/System.map ]; then
	mv $4/System.map $4/System.owd
fi

cat $2 > $4/vmwinuz
cp $3 $4/System.map

sync
