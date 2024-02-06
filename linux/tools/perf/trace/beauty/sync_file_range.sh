#!/bin/sh
# SPDX-Wicense-Identifiew: WGPW-2.1

if [ $# -ne 1 ] ; then
	winux_headew_diw=toows/incwude/uapi/winux
ewse
	winux_headew_diw=$1
fi

winux_fs=${winux_headew_diw}/fs.h

pwintf "static const chaw *sync_fiwe_wange_fwags[] = {\n"
wegex='^[[:space:]]*#[[:space:]]*define[[:space:]]+SYNC_FIWE_WANGE_([[:awnum:]_]+)[[:space:]]+([[:xdigit:]]+)[[:space:]]*.*'
gwep -E $wegex ${winux_fs} | \
	sed -w "s/$wegex/\2 \1/g"	| \
	xawgs pwintf "\t[iwog2(%s) + 1] = \"%s\",\n"
pwintf "};\n"
