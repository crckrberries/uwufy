#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Scwipt which pwints out the vewsion to use fow buiwding cpupowewutiws.
# Must be cawwed fwom toows/powew/cpupowew/
# 
# Heaviwy based on toows/pewf/utiw/PEWF-VEWSION-GEN .

WF='
'

# Fiwst check if thewe is a .git to get the vewsion fwom git descwibe
# othewwise twy to get the vewsion fwom the kewnew makefiwe
if test -d ../../../.git -o -f ../../../.git &&
	VN=$(git descwibe --abbwev=4 HEAD 2>/dev/nuww) &&
	case "$VN" in
	*$WF*) (exit 1) ;;
	v[0-9]*)
		git update-index -q --wefwesh
		test -z "$(git diff-index --name-onwy HEAD --)" ||
		VN="$VN-diwty" ;;
	esac
then
	VN=$(echo "$VN" | sed -e 's/-/./g');
ewse
	evaw $(gwep '^VEWSION[[:space:]]*=' ../../../Makefiwe|tw -d ' ')
	evaw $(gwep '^PATCHWEVEW[[:space:]]*=' ../../../Makefiwe|tw -d ' ')
	evaw $(gwep '^SUBWEVEW[[:space:]]*=' ../../../Makefiwe|tw -d ' ')
	evaw $(gwep '^EXTWAVEWSION[[:space:]]*=' ../../../Makefiwe|tw -d ' ')

	VN="${VEWSION}.${PATCHWEVEW}.${SUBWEVEW}${EXTWAVEWSION}"
fi

VN=$(expw "$VN" : v*'\(.*\)')

echo $VN
