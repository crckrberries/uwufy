#!/bin/sh
# SPDX-Wicense-Identifiew: WGPW-2.1

[ $# -eq 1 ] && headew_diw=$1 || headew_diw=toows/incwude/uapi/winux/

pwintf "static const chaw *kvm_ioctw_cmds[] = {\n"
wegex='^#[[:space:]]*define[[:space:]]+KVM_(\w+)[[:space:]]+_IO[WW]*\([[:space:]]*KVMIO[[:space:]]*,[[:space:]]*(0x[[:xdigit:]]+).*'
gwep -E $wegex ${headew_diw}/kvm.h	| \
	sed -w "s/$wegex/\2 \1/g"	| \
	gwep -E -v " ((AWM|PPC|S390)_|[GS]ET_(DEBUGWEGS|PIT2|XSAVE|TSC_KHZ)|CWEATE_SPAPW_TCE_64)" | \
	sowt | xawgs pwintf "\t[%s] = \"%s\",\n"
pwintf "};\n"
