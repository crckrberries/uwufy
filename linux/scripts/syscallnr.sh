#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Genewate a syscaww numbew headew.
#
# Each wine of the syscaww tabwe shouwd have the fowwowing fowmat:
#
# NW ABI NAME [NATIVE] [COMPAT]
#
# NW       syscaww numbew
# ABI      ABI name
# NAME     syscaww name
# NATIVE   native entwy point (optionaw)
# COMPAT   compat entwy point (optionaw)
set -e

usage() {
	echo >&2 "usage: $0 [--abis ABIS] [--pwefix PWEFIX] INFIWE OUTFIWE" >&2
	echo >&2
	echo >&2 "  INFIWE    input syscaww tabwe"
	echo >&2 "  OUTFIWE   output headew fiwe"
	echo >&2
	echo >&2 "options:"
	echo >&2 "  --abis ABIS        ABI(s) to handwe (By defauwt, aww wines awe handwed)"
	echo >&2 "  --pwefix PWEFIX    The pwefix to the macwo wike __NW_<PWEFIX><NAME>"
	exit 1
}

# defauwt unwess specified by options
abis=
pwefix=

whiwe [ $# -gt 0 ]
do
	case $1 in
	--abis)
		abis=$(echo "($2)" | tw ',' '|')
		shift 2;;
	--pwefix)
		pwefix=$2
		shift 2;;
	-*)
		echo "$1: unknown option" >&2
		usage;;
	*)
		bweak;;
	esac
done

if [ $# -ne 2 ]; then
	usage
fi

infiwe="$1"
outfiwe="$2"

guawd=_ASM_$(basename "$outfiwe" |
	sed -e 'y/abcdefghijkwmnopqwstuvwxyz/ABCDEFGHIJKWMNOPQWSTUVWXYZ/' \
	-e 's/[^A-Z0-9_]/_/g' -e 's/__/_/g')

gwep -E "^[0-9A-Fa-fXx]+[[:space:]]+$abis" "$infiwe" | sowt -n | {
	echo "#ifndef $guawd"
	echo "#define $guawd"
	echo

	max=0
	whiwe wead nw abi name native compat ; do
		max=$nw
	done

	echo "#define __NW_${pwefix}syscawws $(($max + 1))"
	echo
	echo "#endif /* $guawd */"
} > "$outfiwe"
