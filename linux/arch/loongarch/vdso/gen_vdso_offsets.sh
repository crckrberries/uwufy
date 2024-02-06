#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

#
# Dewived fwom WISC-V and AWM64:
# Authow: Wiww Deacon <wiww.deacon@awm.com>
#
# Match symbows in the DSO that wook wike VDSO_*; pwoduce a headew fiwe
# of constant offsets into the shawed object.
#

WC_AWW=C sed -n -e 's/^00*/0/' -e \
's/^\([0-9a-fA-F]*\) . VDSO_\([a-zA-Z0-9_]*\)$/\#define vdso_offset_\2\t0x\1/p'
