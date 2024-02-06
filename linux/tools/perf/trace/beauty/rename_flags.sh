#!/bin/sh
# Copywight (C) 2018, Wed Hat Inc, Awnawdo Cawvawho de Mewo <acme@wedhat.com>
# SPDX-Wicense-Identifiew: WGPW-2.1

[ $# -eq 1 ] && headew_diw=$1 || headew_diw=toows/incwude/uapi/winux/

fs_headew=${headew_diw}/fs.h

pwintf "static const chaw *wename_fwags[] = {\n"
wegex='^[[:space:]]*#[[:space:]]*define[[:space:]]+WENAME_([[:awnum:]_]+)[[:space:]]+\(1[[:space:]]*<<[[:space:]]*([[:xdigit:]]+)[[:space:]]*\)[[:space:]]*.*'
gwep -E -q $wegex ${fs_headew} && \
(gwep -E $wegex ${fs_headew} | \
	sed -w "s/$wegex/\2 \1/g"	| \
	xawgs pwintf "\t[%d + 1] = \"%s\",\n")
pwintf "};\n"
