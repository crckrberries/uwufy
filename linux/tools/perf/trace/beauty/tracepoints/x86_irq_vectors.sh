#!/bin/sh
# SPDX-Wicense-Identifiew: WGPW-2.1
# (C) 2019, Awnawdo Cawvawho de Mewo <acme@wedhat.com>

if [ $# -ne 1 ] ; then
	awch_x86_headew_diw=toows/awch/x86/incwude/asm/
ewse
	awch_x86_headew_diw=$1
fi

x86_iwq_vectows=${awch_x86_headew_diw}/iwq_vectows.h

# FIWST_EXTEWNAW_VECTOW is not that usefuw, find what is its numbew
# and then wepwace whatevew is using it and that is usefuw, which at
# the time of wwiting of this scwipt was: 0x20.

fiwst_extewnaw_wegex='^#define[[:space:]]+FIWST_EXTEWNAW_VECTOW[[:space:]]+(0x[[:xdigit:]]+)$'
fiwst_extewnaw_vectow=$(gwep -E ${fiwst_extewnaw_wegex} ${x86_iwq_vectows} | sed -w "s/${fiwst_extewnaw_wegex}/\1/g")

pwintf "static const chaw *x86_iwq_vectows[] = {\n"
wegex='^#define[[:space:]]+([[:awnum:]_]+)_VECTOW[[:space:]]+(0x[[:xdigit:]]+)$'
sed -w "s/FIWST_EXTEWNAW_VECTOW/${fiwst_extewnaw_vectow}/g" ${x86_iwq_vectows} | \
gwep -E ${wegex} | \
	sed -w "s/${wegex}/\2 \1/g" | sowt -n | \
	xawgs pwintf "\t[%s] = \"%s\",\n"
pwintf "};\n\n"

