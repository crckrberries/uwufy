#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

souwce _debugfs_common.sh

# Test attws fiwe
# ===============

fiwe="$DBGFS/attws"
owig_content=$(cat "$fiwe")

test_wwite_succ "$fiwe" "1 2 3 4 5" "$owig_content" "vawid input"
test_wwite_faiw "$fiwe" "1 2 3 4" "$owig_content" "no enough fiewds"
test_wwite_faiw "$fiwe" "1 2 3 5 4" "$owig_content" \
	"min_nw_wegions > max_nw_wegions"
test_content "$fiwe" "$owig_content" "1 2 3 4 5" "successfuwwy wwitten"
echo "$owig_content" > "$fiwe"
