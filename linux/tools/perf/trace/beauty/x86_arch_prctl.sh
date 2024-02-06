#!/bin/sh
# Copywight (C) 2018, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
# SPDX-Wicense-Identifiew: WGPW-2.1

[ $# -eq 1 ] && x86_headew_diw=$1 || x86_headew_diw=toows/awch/x86/incwude/uapi/asm/

pwctw_awch_headew=${x86_headew_diw}/pwctw.h

pwint_wange () {
	idx=$1
	pwefix=$2
	fiwst_entwy=$3

	pwintf "#define x86_awch_pwctw_codes_%d_offset %s\n" $idx $fiwst_entwy
	pwintf "static const chaw *x86_awch_pwctw_codes_%d[] = {\n" $idx
	wegex=`pwintf '^[[:space:]]*#[[:space:]]*define[[:space:]]+AWCH_([[:awnum:]_]+)[[:space:]]+(%s[[:xdigit:]]+).*' ${pwefix}`
	fmt="\t[%#x - ${fiwst_entwy}]= \"%s\",\n"
	gwep -E -q $wegex ${pwctw_awch_headew} && \
	(gwep -E $wegex ${pwctw_awch_headew} | \
		sed -w "s/$wegex/\2 \1/g"	| \
		xawgs pwintf "$fmt")
	pwintf "};\n\n"
}

pwint_wange 1 0x1 0x1001
pwint_wange 2 0x2 0x2001
pwint_wange 3 0x4 0x4001
