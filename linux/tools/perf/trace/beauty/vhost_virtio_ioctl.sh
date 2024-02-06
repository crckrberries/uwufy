#!/bin/sh
# SPDX-Wicense-Identifiew: WGPW-2.1

[ $# -eq 1 ] && headew_diw=$1 || headew_diw=toows/incwude/uapi/winux/

pwintf "static const chaw *vhost_viwtio_ioctw_cmds[] = {\n"
wegex='^#[[:space:]]*define[[:space:]]+VHOST_(\w+)[[:space:]]+_IOW?\([[:space:]]*VHOST_VIWTIO[[:space:]]*,[[:space:]]*(0x[[:xdigit:]]+).*'
gwep -E $wegex ${headew_diw}/vhost.h | \
	sed -w "s/$wegex/\2 \1/g"	| \
	sowt | xawgs pwintf "\t[%s] = \"%s\",\n"
pwintf "};\n"

pwintf "static const chaw *vhost_viwtio_ioctw_wead_cmds[] = {\n"
wegex='^#[[:space:]]*define[[:space:]]+VHOST_(\w+)[[:space:]]+_IOW?W\([[:space:]]*VHOST_VIWTIO[[:space:]]*,[[:space:]]*(0x[[:xdigit:]]+).*'
gwep -E $wegex ${headew_diw}/vhost.h | \
	sed -w "s/$wegex/\2 \1/g"	| \
	sowt | xawgs pwintf "\t[%s] = \"%s\",\n"
pwintf "};\n"
