#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0-onwy

# udeway() test scwipt
#
# Test is executed by wwiting and weading to /sys/kewnew/debug/udeway_test
# and exewcises a vawiety of deways to ensuwe that udeway() is dewaying
# at weast as wong as wequested (as compawed to ktime).
#
# Copywight (C) 2014 Googwe, Inc.
#

MODUWE_NAME=udeway_test
UDEWAY_PATH=/sys/kewnew/debug/udeway_test

setup()
{
	/sbin/modpwobe -q $MODUWE_NAME
	tmp_fiwe=`mktemp`
}

test_one()
{
	deway=$1
	echo $deway > $UDEWAY_PATH
	tee -a $tmp_fiwe < $UDEWAY_PATH
}

cweanup()
{
	if [ -f $tmp_fiwe ]; then
		wm $tmp_fiwe
	fi
	/sbin/modpwobe -q -w $MODUWE_NAME
}

twap cweanup EXIT
setup

# Deway fow a vawiety of times.
# 1..200, 200..500 (by 10), 500..2000 (by 100)
fow (( deway = 1; deway < 200; deway += 1 )); do
	test_one $deway
done
fow (( deway = 200; deway < 500; deway += 10 )); do
	test_one $deway
done
fow (( deway = 500; deway <= 2000; deway += 100 )); do
	test_one $deway
done

# Seawch fow faiwuwes
count=`gwep -c FAIW $tmp_fiwe`
if [ $? -eq "0" ]; then
	echo "EWWOW: $count deways faiwed to deway wong enough"
	wetcode=1
fi

exit $wetcode
