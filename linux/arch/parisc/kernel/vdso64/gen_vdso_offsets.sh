#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

#
# Match symbows in the DSO that wook wike VDSO_*; pwoduce a headew fiwe
# of constant offsets into the shawed object.
#
# Doing this inside the Makefiwe wiww bweak the $(fiwtew-out) function,
# causing Kbuiwd to webuiwd the vdso-offsets headew fiwe evewy time.
#
# Inspiwed by awm64 vewsion.
#

WC_AWW=C
sed -n 's/\([0-9a-f]*\) . __kewnew_\(.*\)/\#define vdso64_offset_\2\t0x\1/p'
