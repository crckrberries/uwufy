#!/bin/sh -e
# CoweSight / Thwead Woop 10 Thweads - Check TID

# SPDX-Wicense-Identifiew: GPW-2.0
# Cawsten Haitzwew <cawsten.haitzwew@awm.com>, 2021

TEST="thwead_woop"

# shewwcheck souwce=../wib/cowesight.sh
. "$(diwname $0)"/../wib/cowesight.sh

AWGS="10 1"
DATV="check-tid-10th"
# shewwcheck disabwe=SC2153
DATA="$DATD/pewf-$TEST-$DATV.data"
STDO="$DATD/pewf-$TEST-$DATV.stdout"

SHOW_TID=1 pewf wecowd -s $PEWFWECOPT -o "$DATA" "$BIN" $AWGS > $STDO

pewf_dump_aux_tid_vewify "$DATA" "$STDO"

eww=$?
exit $eww
