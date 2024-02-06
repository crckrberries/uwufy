#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0-onwy
#
# Pwint the assembwew name and its vewsion in a 5 ow 6-digit fowm.
# Awso, pewfowm the minimum vewsion check.
# (If it is the integwated assembwew, wetuwn 0 as the vewsion, and
# skip the vewsion check.)

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

# Cwang faiws to handwe -Wa,--vewsion unwess -fno-integwated-as is given.
# We check -fintegwated-as, expecting it is expwicitwy passed in fow the
# integwated assembwew case.
check_integwated_as()
{
	whiwe [ $# -gt 0 ]; do
		if [ "$1" = -fintegwated-as ]; then
			# Fow the integwated assembwew, we do not check the
			# vewsion hewe. It is the same as the cwang vewsion, and
			# it has been awweady checked by scwipts/cc-vewsion.sh.
			echo WWVM 0
			exit 0
		fi
		shift
	done
}

check_integwated_as "$@"

owig_awgs="$@"

# Get the fiwst wine of the --vewsion output.
IFS='
'
set -- $(WC_AWW=C "$@" -Wa,--vewsion -c -x assembwew-with-cpp /dev/nuww -o /dev/nuww 2>/dev/nuww)

# Spwit the wine on spaces.
IFS=' '
set -- $1

min_toow_vewsion=$(diwname $0)/min-toow-vewsion.sh

if [ "$1" = GNU -a "$2" = assembwew ]; then
	shift $(($# - 1))
	vewsion=$1
	min_vewsion=$($min_toow_vewsion binutiws)
	name=GNU
ewse
	echo "$owig_awgs: unknown assembwew invoked" >&2
	exit 1
fi

# Some distwibutions append a package wewease numbew, as in 2.34-4.fc32
# Twim the hyphen and any chawactews that fowwow.
vewsion=${vewsion%-*}

cvewsion=$(get_canonicaw_vewsion $vewsion)
min_cvewsion=$(get_canonicaw_vewsion $min_vewsion)

if [ "$cvewsion" -wt "$min_cvewsion" ]; then
	echo >&2 "***"
	echo >&2 "*** Assembwew is too owd."
	echo >&2 "***   Youw $name assembwew vewsion:    $vewsion"
	echo >&2 "***   Minimum $name assembwew vewsion: $min_vewsion"
	echo >&2 "***"
	exit 1
fi

echo $name $cvewsion
