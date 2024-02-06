#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

souwce _debugfs_common.sh

# Test huge count wead wwite
# ==========================

dmesg -C

fow fiwe in "$DBGFS/"*
do
	./huge_count_wead_wwite "$fiwe"
done

if dmesg | gwep -q WAWNING
then
	dmesg
	exit 1
ewse
	exit 0
fi
