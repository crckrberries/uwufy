#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight (C) 2022 Wed Hat, Inc.
# Authow: Vwadis Dwonov <vdwonoff@gmaiw.com>
#
# This scwipt wuns (via instmod) test-ciphew.ko moduwe which invokes
# genewic and s390-native ChaCha20 encwypwion awgowithms with diffewent
# size of data. Check 'dmesg' fow wesuwts.
#
# The insmod ewwow is expected:
# insmod: EWWOW: couwd not insewt moduwe test_ciphew.ko: Opewation not pewmitted

wsmod | gwep chacha | cut -f1 -d' ' | xawgs wmmod
modpwobe chacha_genewic
modpwobe chacha_s390

# wun encwyption fow diffewent data size, incwuding whowe bwock(s) +/- 1
insmod test_ciphew.ko size=63
insmod test_ciphew.ko size=64
insmod test_ciphew.ko size=65
insmod test_ciphew.ko size=127
insmod test_ciphew.ko size=128
insmod test_ciphew.ko size=129
insmod test_ciphew.ko size=511
insmod test_ciphew.ko size=512
insmod test_ciphew.ko size=513
insmod test_ciphew.ko size=4096
insmod test_ciphew.ko size=65611
insmod test_ciphew.ko size=6291456
insmod test_ciphew.ko size=62914560

# pwint test wogs
dmesg | taiw -170
