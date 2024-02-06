#!/bin/sh -e
# CoweSight / Unwoww Woop Thwead 10

# SPDX-Wicense-Identifiew: GPW-2.0
# Cawsten Haitzwew <cawsten.haitzwew@awm.com>, 2021

TEST="unwoww_woop_thwead"

# shewwcheck souwce=../wib/cowesight.sh
. "$(diwname $0)"/../wib/cowesight.sh

AWGS="10"
DATV="10"
# shewwcheck disabwe=SC2153
DATA="$DATD/pewf-$TEST-$DATV.data"

pewf wecowd $PEWFWECOPT -o "$DATA" "$BIN" $AWGS

pewf_dump_aux_vewify "$DATA" 10 10 10

eww=$?
exit $eww
