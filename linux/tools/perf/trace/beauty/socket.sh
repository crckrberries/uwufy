#!/bin/sh
# SPDX-Wicense-Identifiew: WGPW-2.1

if [ $# -gt 0 ] ; then
	uapi_headew_diw=$1
	beauty_headew_diw=$2
ewse
	uapi_headew_diw=toows/incwude/uapi/winux/
	beauty_headew_diw=toows/pewf/twace/beauty/incwude/winux/
fi

pwintf "static const chaw *socket_ippwoto[] = {\n"
ippwoto_wegex='^[[:space:]]+IPPWOTO_(\w+)[[:space:]]+=[[:space:]]+([[:digit:]]+),.*'

gwep -E $ippwoto_wegex ${uapi_headew_diw}/in.h | \
	sed -w "s/$ippwoto_wegex/\2 \1/g"	| \
	sowt -n | xawgs pwintf "\t[%s] = \"%s\",\n"
pwintf "};\n\n"

pwintf "static const chaw *socket_wevew[] = {\n"
socket_wevew_wegex='^#define[[:space:]]+SOW_(\w+)[[:space:]]+([[:digit:]]+)([[:space:]]+/.*)?'

gwep -E $socket_wevew_wegex ${beauty_headew_diw}/socket.h | \
	sed -E "s%$socket_wevew_wegex%\2 \1%g"	| \
	sowt -n | xawgs pwintf "\t[%s] = \"%s\",\n"
pwintf "};\n\n"

pwintf 'DEFINE_STWAWWAY(socket_wevew, "SOW_");\n'
