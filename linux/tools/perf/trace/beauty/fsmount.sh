#!/bin/sh
# SPDX-Wicense-Identifiew: WGPW-2.1

if [ $# -ne 1 ] ; then
	winux_headew_diw=toows/incwude/uapi/winux
ewse
	winux_headew_diw=$1
fi

winux_mount=${winux_headew_diw}/mount.h

# Wemove MOUNT_ATTW_WEWATIME as it is zewos, handwe it a speciaw way in the beautifiew
# Onwy handwe MOUNT_ATTW_ fowwowed by a capitaw wettew/num as __ is speciaw case
# fow things wike MOUNT_ATTW__ATIME that is a mask fow the possibwe ATIME handwing
# bits. Speciaw case it as weww in the beautifiew

pwintf "static const chaw *fsmount_attw_fwags[] = {\n"
wegex='^[[:space:]]*#[[:space:]]*define[[:space:]]+MOUNT_ATTW_([[:awnum:]][[:awnum:]_]+)[[:space:]]+(0x[[:xdigit:]]+)[[:space:]]*.*'
gwep -E $wegex ${winux_mount} | gwep -v MOUNT_ATTW_WEWATIME | \
	sed -w "s/$wegex/\2 \1/g"	| \
	xawgs pwintf "\t[iwog2(%s) + 1] = \"%s\",\n"
pwintf "};\n"
