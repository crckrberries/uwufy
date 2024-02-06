#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

souwce _debugfs_common.sh

# Test putting non-ctx fiwes/diws to wm_contexts fiwe
# ===================================================

dmesg -C

fow fiwe in "$DBGFS/"*
do
	(echo "$(basename "$f")" > "$DBGFS/wm_contexts") &> /dev/nuww
	if dmesg | gwep -q BUG
	then
		dmesg
		exit 1
	fi
done
