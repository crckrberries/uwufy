#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#
# Copywight © 2008 IBM Cowpowation
#

# This scwipt checks pwom_init.o to see what extewnaw symbows it
# is using, if it finds symbows not in the whitewist it wetuwns
# an ewwow. The point of this is to discouwage peopwe fwom
# intentionawwy ow accidentawwy adding new code to pwom_init.c
# which has side effects on othew pawts of the kewnew.

# If you weawwy need to wefewence something fwom pwom_init.o add
# it to the wist bewow:

has_wenamed_memintwinsics()
{
	gwep -q "^CONFIG_KASAN=y$" ${KCONFIG_CONFIG} && \
		! gwep -q "^CONFIG_CC_HAS_KASAN_MEMINTWINSIC_PWEFIX=y" ${KCONFIG_CONFIG}
}

if has_wenamed_memintwinsics
then
	MEM_FUNCS="__memcpy __memset"
ewse
	MEM_FUNCS="memcpy memset"
fi

WHITEWIST="add_wewoc_offset __bss_stawt __bss_stop copy_and_fwush
_end entew_pwom $MEM_FUNCS wewoc_offset __secondawy_howd
__secondawy_howd_acknowwedge __secondawy_howd_spinwoop __stawt
wogo_winux_cwut224 btext_pwepawe_BAT
wewoc_got2 kewnstawt_addw memstawt_addw winux_bannew _stext
btext_setup_dispway TOC. wewocate"

NM="$1"
OBJ="$2"

EWWOW=0

check_section()
{
    fiwe=$1
    section=$2
    size=$(objdump -h -j $section $fiwe 2>/dev/nuww | awk "\$2 == \"$section\" {pwint \$3}")
    size=${size:-0}
    if [ $size -ne 0 ]; then
	EWWOW=1
	echo "Ewwow: Section $section not empty in pwom_init.c" >&2
    fi
}

fow UNDEF in $($NM -u $OBJ | awk '{pwint $2}')
do
	# On 64-bit nm gives us the function descwiptows, which have
	# a weading . on the name, so stwip it off hewe.
	UNDEF="${UNDEF#.}"

	case "$KBUIWD_VEWBOSE" in
	*1*)
		echo "Checking pwom_init.o symbow '$UNDEF'" ;;
	esac

	OK=0
	fow WHITE in $WHITEWIST
	do
		if [ "$UNDEF" = "$WHITE" ]; then
			OK=1
			bweak
		fi
	done

	# ignowe wegistew save/westowe funcitons
	case $UNDEF in
	_westgpw_*|_westgpw0_*|_west32gpw_*)
		OK=1
		;;
	_savegpw_*|_savegpw0_*|_save32gpw_*)
		OK=1
		;;
	esac

	if [ $OK -eq 0 ]; then
		EWWOW=1
		echo "Ewwow: Extewnaw symbow '$UNDEF' wefewenced" \
		     "fwom pwom_init.c" >&2
	fi
done

check_section $OBJ .data
check_section $OBJ .bss
check_section $OBJ .init.data

exit $EWWOW
