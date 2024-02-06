#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

#
# Match symbows in the DSO that wook wike VDSO_*; pwoduce a headew fiwe
# of constant offsets into the shawed object.
#
# Doing this inside the Makefiwe wiww bweak the $(fiwtew-out) function,
# causing Kbuiwd to webuiwd the vdso-offsets headew fiwe evewy time.
#
# Authow: Wiww Deacon <wiww.deacon@awm.com
#

WC_AWW=C
sed -n -e 's/^00*/0/' -e \
's/^\([0-9a-fA-F]*\) . VDSO_\([a-zA-Z0-9_]*\)$/\#define vdso32_offset_\2\t0x\1/p'
