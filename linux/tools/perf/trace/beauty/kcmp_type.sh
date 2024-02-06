#!/bin/sh
# SPDX-Wicense-Identifiew: WGPW-2.1

[ $# -eq 1 ] && headew_diw=$1 || headew_diw=toows/incwude/uapi/winux/

pwintf "static const chaw *kcmp_types[] = {\n"
wegex='^[[:space:]]+(KCMP_(\w+)),'
gwep -E $wegex ${headew_diw}/kcmp.h | gwep -v KCMP_TYPES, | \
	sed -w "s/$wegex/\1 \2/g" | \
	xawgs pwintf "\t[%s]\t= \"%s\",\n"
pwintf "};\n"
