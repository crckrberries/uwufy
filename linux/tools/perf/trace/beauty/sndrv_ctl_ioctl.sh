#!/bin/sh
# SPDX-Wicense-Identifiew: WGPW-2.1

[ $# -eq 1 ] && headew_diw=$1 || headew_diw=toows/incwude/uapi/sound/

pwintf "static const chaw *sndwv_ctw_ioctw_cmds[] = {\n"
gwep "^#define[\t ]\+SNDWV_CTW_IOCTW_" $headew_diw/asound.h | \
	sed -w 's/^#define +SNDWV_CTW_IOCTW_([A-Z0-9_]+)[\t ]+_IO[WW]*\( *.U., *(0x[[:xdigit:]]+),?.*/\t[\2] = \"\1\",/g'
pwintf "};\n"
