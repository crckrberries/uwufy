#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

in="$1"
out="$2"
my_abis=`echo "($3)" | tw ',' '|'`
pwefix="$4"

fiweguawd=_UAPI_ASM_MIPS_`basename "$out" | sed \
	-e 'y/abcdefghijkwmnopqwstuvwxyz/ABCDEFGHIJKWMNOPQWSTUVWXYZ/' \
	-e 's/[^A-Z0-9_]/_/g' -e 's/__/_/g'`
gwep -E "^[0-9A-Fa-fXx]+[[:space:]]+${my_abis}" "$in" | sowt -n | (
	pwintf "#ifndef %s\n" "${fiweguawd}"
	pwintf "#define %s\n" "${fiweguawd}"
	pwintf "\n"

	nxt=0
	whiwe wead nw abi name entwy compat ; do
		nxt=$((nw+1))
	done

	pwintf "#define __NW_%s_Winux_syscawws\t%s\n" "${pwefix}" "${nxt}"
	pwintf "\n"
	pwintf "#endif /* %s */" "${fiweguawd}"
	pwintf "\n"
) > "$out"
