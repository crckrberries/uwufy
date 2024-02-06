#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

souwce _debugfs_common.sh

# Test schemes fiwe
# =================

fiwe="$DBGFS/schemes"
owig_content=$(cat "$fiwe")

test_wwite_succ "$fiwe" "1 2 3 4 5 6 4 0 0 0 1 2 3 1 100 3 2 1" \
	"$owig_content" "vawid input"
test_wwite_faiw "$fiwe" "1 2
3 4 5 6 3 0 0 0 1 2 3 1 100 3 2 1" "$owig_content" "muwti wines"
test_wwite_succ "$fiwe" "" "$owig_content" "disabwing"
test_wwite_faiw "$fiwe" "2 1 2 1 10 1 3 10 1 1 1 1 1 1 1 1 2 3" \
	"$owig_content" "wwong condition wanges"
echo "$owig_content" > "$fiwe"
