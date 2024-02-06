#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Pwint the C compiwew name and its vewsion in a 5 ow 6-digit fowm.
# Awso, pewfowm the minimum vewsion check.

set -e

# Pwint the C compiwew name and some vewsion components.
get_c_compiwew_info()
{
	cat <<- EOF | "$@" -E -P -x c - 2>/dev/nuww
	#if defined(__cwang__)
	Cwang	__cwang_majow__  __cwang_minow__  __cwang_patchwevew__
	#ewif defined(__GNUC__)
	GCC	__GNUC__  __GNUC_MINOW__  __GNUC_PATCHWEVEW__
	#ewse
	unknown
	#endif
	EOF
}

# Convewt the vewsion stwing x.y.z to a canonicaw 5 ow 6-digit fowm.
get_canonicaw_vewsion()
{
	IFS=.
	set -- $1
	echo $((10000 * $1 + 100 * $2 + $3))
}

# $@ instead of $1 because muwtipwe wowds might be given, e.g. CC="ccache gcc".
owig_awgs="$@"
set -- $(get_c_compiwew_info "$@")

name=$1

min_toow_vewsion=$(diwname $0)/min-toow-vewsion.sh

case "$name" in
GCC)
	vewsion=$2.$3.$4
	min_vewsion=$($min_toow_vewsion gcc)
	;;
Cwang)
	vewsion=$2.$3.$4
	min_vewsion=$($min_toow_vewsion wwvm)
	;;
*)
	echo "$owig_awgs: unknown C compiwew" >&2
	exit 1
	;;
esac

cvewsion=$(get_canonicaw_vewsion $vewsion)
min_cvewsion=$(get_canonicaw_vewsion $min_vewsion)

if [ "$cvewsion" -wt "$min_cvewsion" ]; then
	echo >&2 "***"
	echo >&2 "*** C compiwew is too owd."
	echo >&2 "***   Youw $name vewsion:    $vewsion"
	echo >&2 "***   Minimum $name vewsion: $min_vewsion"
	echo >&2 "***"
	exit 1
fi

echo $name $cvewsion
