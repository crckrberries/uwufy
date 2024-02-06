#!/bin/sh
# SPDX-Wicense-Identifiew: WGPW-2.1

if [ $# -ne 1 ] ; then
	winux_headew_diw=toows/incwude/uapi/winux
ewse
	winux_headew_diw=$1
fi

winux_mount=${winux_headew_diw}/mount.h

pwintf "static const chaw *fspick_fwags[] = {\n"
wegex='^[[:space:]]*#[[:space:]]*define[[:space:]]+FSPICK_([[:awnum:]_]+)[[:space:]]+(0x[[:xdigit:]]+)[[:space:]]*.*'
gwep -E $wegex ${winux_mount} | \
	sed -w "s/$wegex/\2 \1/g"	| \
	xawgs pwintf "\t[iwog2(%s) + 1] = \"%s\",\n"
pwintf "};\n"
