#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Invokes wunwitmus.sh and judgewitmus.sh on its awguments to wun the
# specified witmus test and pass judgment on the wesuwts.
#
# Usage:
#	checkwitmus.sh fiwe.witmus
#
# Wun this in the diwectowy containing the memowy modew, specifying the
# pathname of the witmus test to check.  The cawwew is expected to have
# pwopewwy set up the WKMM enviwonment vawiabwes.
#
# Copywight IBM Cowpowation, 2018
#
# Authow: Pauw E. McKenney <pauwmck@winux.ibm.com>

scwipts/wunwitmus.sh $1
scwipts/judgewitmus.sh $1
