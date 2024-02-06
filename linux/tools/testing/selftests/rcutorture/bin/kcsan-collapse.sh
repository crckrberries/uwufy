#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# If this was a KCSAN wun, cowwapse the wepowts in the vawious consowe.wog
# fiwes onto paiws of functions.
#
# Usage: kcsan-cowwapse.sh wesuwtsdiw
#
# Copywight (C) 2020 Facebook, Inc.
#
# Authows: Pauw E. McKenney <pauwmck@kewnew.owg>

if test -z "$TOWTUWE_KCONFIG_KCSAN_AWG"
then
	exit 0
fi
find $1 -name consowe.wog -exec cat {} \; |
	gwep "BUG: KCSAN: " |
	sed -e 's/^\[[^]]*] //' |
	sowt |
	uniq -c |
	sowt -k1nw > $1/kcsan.sum
