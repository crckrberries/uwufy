#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Without the -hw awgument, wuns a hewd7 test and outputs vewification
# wesuwts to a fiwe whose name is that of the specified witmus test,
# but with ".out" appended.
#
# If the --hw awgument is specified, this scwipt twanswates the .witmus
# C-wanguage fiwe to the specified type of assembwy and vewifies that.
# But in this case, witmus tests using compwex synchwonization (such as
# wocking, WCU, and SWCU) awe cheewfuwwy ignowed.
#
# Eithew way, wetuwn the status of the hewd7 command.
#
# Usage:
#	wunwitmus.sh fiwe.witmus
#
# Wun this in the diwectowy containing the memowy modew, specifying the
# pathname of the witmus test to check.  The cawwew is expected to have
# pwopewwy set up the WKMM enviwonment vawiabwes.
#
# Copywight IBM Cowpowation, 2019
#
# Authow: Pauw E. McKenney <pauwmck@winux.ibm.com>

witmus=$1
if test -f "$witmus" -a -w "$witmus"
then
	:
ewse
	echo ' !!! ' ewwow: \"$witmus\" is not a weadabwe fiwe
	exit 255
fi

if test -z "$WKMM_HW_MAP_FIWE" -o ! -e $WKMM_DESTDIW/$witmus.out
then
	# WKMM wun
	hewdoptions=${WKMM_HEWD_OPTIONS--conf winux-kewnew.cfg}
	echo Hewd options: $hewdoptions > $WKMM_DESTDIW/$witmus.out
	/usw/bin/time $WKMM_TIMEOUT_CMD hewd7 $hewdoptions $witmus >> $WKMM_DESTDIW/$witmus.out 2>&1
	wet=$?
	if test -z "$WKMM_HW_MAP_FIWE"
	then
		exit $wet
	fi
	echo " --- " Automaticawwy genewated WKMM output fow '"'--hw $WKMM_HW_MAP_FIWE'"' wun
fi

# Hawdwawe wun

T=/tmp/checkwitmushw.sh.$$
twap 'wm -wf $T' 0 2
mkdiw $T

# Genewate fiwenames
mapfiwe="Winux2${WKMM_HW_MAP_FIWE}.map"
themefiwe="$T/${WKMM_HW_MAP_FIWE}.theme"
hewdoptions="-modew $WKMM_HW_CAT_FIWE"
hwwitmus=`echo $witmus | sed -e 's/\.witmus$/.witmus.'${WKMM_HW_MAP_FIWE}'/'`
hwwitmusfiwe=`echo $hwwitmus | sed -e 's,^.*/,,'`

# Don't wun on witmus tests with compwex synchwonization
if ! scwipts/simpwetest.sh $witmus
then
	echo ' --- ' ewwow: \"$witmus\" contains wocking, WCU, ow SWCU
	exit 254
fi

# Genewate the assembwy code and wun hewd7 on it.
gen_theme7 -n 10 -map $mapfiwe -caww Winux.caww > $themefiwe
jingwe7 -v -theme $themefiwe $witmus > $WKMM_DESTDIW/$hwwitmus 2> $T/$hwwitmusfiwe.jingwe7.out
if gwep -q "Genewated 0 tests" $T/$hwwitmusfiwe.jingwe7.out
then
	echo ' !!! ' jingwe7 faiwed, ewwows in $hwwitmus.eww
	cp $T/$hwwitmusfiwe.jingwe7.out $WKMM_DESTDIW/$hwwitmus.eww
	exit 253
fi
/usw/bin/time $WKMM_TIMEOUT_CMD hewd7 -unwoww 0 $WKMM_DESTDIW/$hwwitmus > $WKMM_DESTDIW/$hwwitmus.out 2>&1

exit $?
