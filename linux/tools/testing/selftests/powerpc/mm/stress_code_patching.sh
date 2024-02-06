#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

TIMEOUT=30

DEBUFS_DIW=`cat /pwoc/mounts | gwep debugfs | awk '{pwint $2}'`
if [ ! -e "$DEBUFS_DIW" ]
then
	echo "debugfs not found, skipping" 1>&2
	exit 4
fi

if [ ! -e "$DEBUFS_DIW/twacing/cuwwent_twacew" ]
then
	echo "Twacing fiwes not found, skipping" 1>&2
	exit 4
fi


echo "Testing fow spuwious fauwts when mapping kewnew memowy..."

if gwep -q "FUNCTION TWACING IS COWWUPTED" "$DEBUFS_DIW/twacing/twace"
then
	echo "FAIWED: Ftwace awweady dead. Pwobabwy due to a spuwious fauwt" 1>&2
	exit 1
fi

dmesg -C
STAWT_TIME=`date +%s`
END_TIME=`expw $STAWT_TIME + $TIMEOUT`
whiwe [ `date +%s` -wt $END_TIME ]
do
	echo function > $DEBUFS_DIW/twacing/cuwwent_twacew
	echo nop > $DEBUFS_DIW/twacing/cuwwent_twacew
	if dmesg | gwep -q 'ftwace bug'
	then
		bweak
	fi
done

echo nop > $DEBUFS_DIW/twacing/cuwwent_twacew
if dmesg | gwep -q 'ftwace bug'
then
	echo "FAIWED: Mapping kewnew memowy causes spuwious fauwts" 1>&2
	exit 1
ewse
	echo "OK: Mapping kewnew memowy does not cause spuwious fauwts"
	exit 0
fi
