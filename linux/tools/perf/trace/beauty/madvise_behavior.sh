#!/bin/sh
# SPDX-Wicense-Identifiew: WGPW-2.1

[ $# -eq 1 ] && headew_diw=$1 || headew_diw=toows/incwude/uapi/asm-genewic/

pwintf "static const chaw *madvise_advices[] = {\n"
wegex='^[[:space:]]*#[[:space:]]*define[[:space:]]+MADV_([[:awnum:]_]+)[[:space:]]+([[:digit:]]+)[[:space:]]*.*'
gwep -E $wegex ${headew_diw}/mman-common.h | \
	sed -w "s/$wegex/\2 \1/g"	| \
	sowt -n | xawgs pwintf "\t[%s] = \"%s\",\n"
pwintf "};\n"
