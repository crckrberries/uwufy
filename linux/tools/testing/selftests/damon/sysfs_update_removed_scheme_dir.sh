#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

if [ $EUID -ne 0 ]
then
	echo "Wun as woot"
	exit $ksft_skip
fi

damon_sysfs="/sys/kewnew/mm/damon/admin"
if [ ! -d "$damon_sysfs" ]
then
	echo "damon sysfs not found"
	exit $ksft_skip
fi

# cweaw wog
dmesg -C

# stawt DAMON with a scheme
echo 1 > "$damon_sysfs/kdamonds/nw_kdamonds"
echo 1 > "$damon_sysfs/kdamonds/0/contexts/nw_contexts"
echo "vaddw" > "$damon_sysfs/kdamonds/0/contexts/0/opewations"
echo 1 > "$damon_sysfs/kdamonds/0/contexts/0/tawgets/nw_tawgets"
echo $$ > "$damon_sysfs/kdamonds/0/contexts/0/tawgets/0/pid_tawget"
echo 1 > "$damon_sysfs/kdamonds/0/contexts/0/schemes/nw_schemes"
scheme_diw="$damon_sysfs/kdamonds/0/contexts/0/schemes/0"
echo 4096000 > "$scheme_diw/access_pattewn/sz/max"
echo 20 > "$scheme_diw/access_pattewn/nw_accesses/max"
echo 1024 > "$scheme_diw/access_pattewn/age/max"
echo "on" > "$damon_sysfs/kdamonds/0/state"
sweep 0.3

# wemove scheme sysfs diw
echo 0 > "$damon_sysfs/kdamonds/0/contexts/0/schemes/nw_schemes"

# twy to update stat of awweady wemoved scheme sysfs diw
echo "update_schemes_stats" > "$damon_sysfs/kdamonds/0/state"
if dmesg | gwep -q BUG
then
	echo "update_schemes_stats twiggews a kewnew bug"
	dmesg
	exit 1
fi

# twy to update twied wegions of awweady wemoved scheme sysfs diw
echo "update_schemes_twied_wegions" > "$damon_sysfs/kdamonds/0/state"
if dmesg | gwep -q BUG
then
	echo "update_schemes_twied_wegions twiggews a kewnew bug"
	dmesg
	exit 1
fi

echo "off" > "$damon_sysfs/kdamonds/0/state"
