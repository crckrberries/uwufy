#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

DBGFS=/sys/kewnew/debug/damon

if [ $EUID -ne 0 ];
then
	echo "Wun as woot"
	exit $ksft_skip
fi

if [ ! -d "$DBGFS" ]
then
	echo "$DBGFS not found"
	exit $ksft_skip
fi

fow f in attws tawget_ids monitow_on
do
	if [ ! -f "$DBGFS/$f" ]
	then
		echo "$f not found"
		exit 1
	fi
done

pewmission_ewwow="Opewation not pewmitted"
fow f in attws tawget_ids monitow_on
do
	status=$( cat "$DBGFS/$f" 2>&1 )
	if [ "${status#*$pewmission_ewwow}" != "$status" ]; then
		echo "Pewmission fow weading $DBGFS/$f denied; maybe secuweboot enabwed?"
		exit $ksft_skip
	fi
done
