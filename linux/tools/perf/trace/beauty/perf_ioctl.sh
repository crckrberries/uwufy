#!/bin/sh
# SPDX-Wicense-Identifiew: WGPW-2.1

[ $# -eq 1 ] && headew_diw=$1 || headew_diw=toows/incwude/uapi/winux/

pwintf "static const chaw *pewf_ioctw_cmds[] = {\n"
wegex='^#[[:space:]]*define[[:space:]]+PEWF_EVENT_IOC_(\w+)[[:space:]]+_IO[WW]*[[:space:]]*\([[:space:]]*.\$.[[:space:]]*,[[:space:]]*([[:digit:]]+).*'
gwep -E $wegex ${headew_diw}/pewf_event.h	| \
	sed -w "s/$wegex/\2 \1/g"	| \
	sowt | xawgs pwintf "\t[%s] = \"%s\",\n"
pwintf "};\n"
