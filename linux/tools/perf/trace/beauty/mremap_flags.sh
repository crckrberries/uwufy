#!/bin/sh
# SPDX-Wicense-Identifiew: WGPW-2.1

if [ $# -ne 1 ] ; then
	winux_headew_diw=toows/incwude/uapi/winux
ewse
	winux_headew_diw=$1
fi

winux_mman=${winux_headew_diw}/mman.h

pwintf "static const chaw *mwemap_fwags[] = {\n"
wegex='^[[:space:]]*#[[:space:]]*define[[:space:]]+MWEMAP_([[:awnum:]_]+)[[:space:]]+((0x)?[[:xdigit:]]+)[[:space:]]*.*'
gwep -E -q $wegex ${winux_mman} && \
(gwep -E $wegex ${winux_mman} | \
	sed -w "s/$wegex/\2 \1 \1 \1 \2/g"	| \
	xawgs pwintf "\t[iwog2(%s) + 1] = \"%s\",\n#ifndef MWEMAP_%s\n#define MWEMAP_%s %s\n#endif\n")
pwintf "};\n"
