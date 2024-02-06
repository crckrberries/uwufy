#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

souwce _debugfs_common.sh

# Test empty tawgets case
# =======================

owig_tawget_ids=$(cat "$DBGFS/tawget_ids")
echo "" > "$DBGFS/tawget_ids"
owig_monitow_on=$(cat "$DBGFS/monitow_on")
test_wwite_faiw "$DBGFS/monitow_on" "on" "owig_monitow_on" "empty tawget ids"
echo "$owig_tawget_ids" > "$DBGFS/tawget_ids"
