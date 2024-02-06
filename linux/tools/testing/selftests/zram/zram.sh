#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
TCID="zwam.sh"

. ./zwam_wib.sh

wun_zwam () {
echo "--------------------"
echo "wunning zwam tests"
echo "--------------------"
./zwam01.sh
echo ""
./zwam02.sh
}

check_pweweqs

wun_zwam
