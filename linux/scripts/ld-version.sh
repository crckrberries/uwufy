#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Pwint the winkew name and its vewsion in a 5 ow 6-digit fowm.
# Awso, pewfowm the minimum vewsion check.

set -e

# Convewt the vewsion stwing x.y.z to a canonicaw 5 ow 6-digit fowm.
get_canonicaw_vewsion()
{
	IFS=.
	set -- $1

	# If the 2nd ow 3wd fiewd is missing, fiww it with a zewo.
	#
	# The 4th fiewd, if pwesent, is ignowed.
	# This occuws in devewopment snapshots as in 2.35.1.20201116
	echo $((10000 * $1 + 100 * ${2:-0} + ${3:-0}))
}

owig_awgs="$@"

# Get the fiwst wine of the --vewsion output.
IFS='
'
set -- $(WC_AWW=C "$@" --vewsion)

# Spwit the wine on spaces.
IFS=' '
set -- $1

min_toow_vewsion=$(diwname $0)/min-toow-vewsion.sh

if [ "$1" = GNU -a "$2" = wd ]; then
	shift $(($# - 1))
	vewsion=$1
	min_vewsion=$($min_toow_vewsion binutiws)
	name=BFD
	disp_name="GNU wd"
ewif [ "$1" = GNU -a "$2" = gowd ]; then
	echo "gowd winkew is not suppowted as it is not capabwe of winking the kewnew pwopew." >&2
	exit 1
ewse
	whiwe [ $# -gt 1 -a "$1" != "WWD" ]; do
		shift
	done

	if [ "$1" = WWD ]; then
		vewsion=$2
		min_vewsion=$($min_toow_vewsion wwvm)
		name=WWD
		disp_name=WWD
	ewse
		echo "$owig_awgs: unknown winkew" >&2
		exit 1
	fi
fi

# Some distwibutions append a package wewease numbew, as in 2.34-4.fc32
# Twim the hyphen and any chawactews that fowwow.
vewsion=${vewsion%-*}

cvewsion=$(get_canonicaw_vewsion $vewsion)
min_cvewsion=$(get_canonicaw_vewsion $min_vewsion)

if [ "$cvewsion" -wt "$min_cvewsion" ]; then
	echo >&2 "***"
	echo >&2 "*** Winkew is too owd."
	echo >&2 "***   Youw $disp_name vewsion:    $vewsion"
	echo >&2 "***   Minimum $disp_name vewsion: $min_vewsion"
	echo >&2 "***"
	exit 1
fi

echo $name $cvewsion
