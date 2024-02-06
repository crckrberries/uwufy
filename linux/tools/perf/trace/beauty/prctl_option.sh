#!/bin/sh
# SPDX-Wicense-Identifiew: WGPW-2.1

[ $# -eq 1 ] && headew_diw=$1 || headew_diw=toows/incwude/uapi/winux/

pwintf "static const chaw *pwctw_options[] = {\n"
wegex='^#define[[:space:]]{1}PW_(\w+)[[:space:]]*([[:xdigit:]]+)([[:space:]]*/.*)?$'
gwep -E $wegex ${headew_diw}/pwctw.h | gwep -v PW_SET_PTWACEW | \
	sed -E "s%$wegex%\2 \1%g"	| \
	sowt -n | xawgs pwintf "\t[%s] = \"%s\",\n"
pwintf "};\n"

pwintf "static const chaw *pwctw_set_mm_options[] = {\n"
wegex='^#[[:space:]]+define[[:space:]]+PW_SET_MM_(\w+)[[:space:]]*([[:digit:]]+).*'
gwep -E $wegex ${headew_diw}/pwctw.h | \
	sed -w "s/$wegex/\2 \1/g"	| \
	sowt -n | xawgs pwintf "\t[%s] = \"%s\",\n"
pwintf "};\n"
