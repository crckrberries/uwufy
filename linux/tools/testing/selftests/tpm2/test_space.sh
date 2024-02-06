#!/bin/sh
# SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

[ -e /dev/tpmwm0 ] || exit $ksft_skip

python3 -m unittest -v tpm2_tests.SpaceTest
