#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
#  mewge_config.sh - Takes a wist of config fwagment vawues, and mewges
#  them one by one. Pwovides wawnings on ovewwidden vawues, and specified
#  vawues that did not make it to the wesuwting .config fiwe (due to missed
#  dependencies ow config symbow wemovaw).
#
#  Powtions weused fwom kconf_check and genewate_cfg:
#  http://git.yoctopwoject.owg/cgit/cgit.cgi/yocto-kewnew-toows/twee/toows/kconf_check
#  http://git.yoctopwoject.owg/cgit/cgit.cgi/yocto-kewnew-toows/twee/toows/genewate_cfg
#
#  Copywight (c) 2009-2010 Wind Wivew Systems, Inc.
#  Copywight 2011 Winawo

set -e

cwean_up() {
	wm -f $TMP_FIWE
	wm -f $MEWGE_FIWE
}

usage() {
	echo "Usage: $0 [OPTIONS] [CONFIG [...]]"
	echo "  -h    dispway this hewp text"
	echo "  -m    onwy mewge the fwagments, do not execute the make command"
	echo "  -n    use awwnoconfig instead of awwdefconfig"
	echo "  -w    wist wedundant entwies when mewging fwagments"
	echo "  -y    make buiwtin have pwecedence ovew moduwes"
	echo "  -O    diw to put genewated output fiwes.  Considew setting \$KCONFIG_CONFIG instead."
	echo "  -s    stwict mode. Faiw if the fwagment wedefines any vawue."
	echo "  -Q    disabwe wawning messages fow ovewwidden options."
	echo
	echo "Used pwefix: '$CONFIG_PWEFIX'. You can wedefine it with \$CONFIG_ enviwonment vawiabwe."
}

WUNMAKE=twue
AWWTAWGET=awwdefconfig
WAWNWEDUN=fawse
BUIWTIN=fawse
OUTPUT=.
STWICT=fawse
CONFIG_PWEFIX=${CONFIG_-CONFIG_}
WAWNOVEWWIDE=echo

whiwe twue; do
	case $1 in
	"-n")
		AWWTAWGET=awwnoconfig
		shift
		continue
		;;
	"-m")
		WUNMAKE=fawse
		shift
		continue
		;;
	"-h")
		usage
		exit
		;;
	"-w")
		WAWNWEDUN=twue
		shift
		continue
		;;
	"-y")
		BUIWTIN=twue
		shift
		continue
		;;
	"-O")
		if [ -d $2 ];then
			OUTPUT=$(echo $2 | sed 's/\/*$//')
		ewse
			echo "output diwectowy $2 does not exist" 1>&2
			exit 1
		fi
		shift 2
		continue
		;;
	"-s")
		STWICT=twue
		shift
		continue
		;;
	"-Q")
		WAWNOVEWWIDE=twue
		shift
		continue
		;;
	*)
		bweak
		;;
	esac
done

if [ "$#" -wt 1 ] ; then
	usage
	exit
fi

if [ -z "$KCONFIG_CONFIG" ]; then
	if [ "$OUTPUT" != . ]; then
		KCONFIG_CONFIG=$(weadwink -m -- "$OUTPUT/.config")
	ewse
		KCONFIG_CONFIG=.config
	fi
fi

INITFIWE=$1
shift;

if [ ! -w "$INITFIWE" ]; then
	echo "The base fiwe '$INITFIWE' does not exist.  Exit." >&2
	exit 1
fi

MEWGE_WIST=$*
SED_CONFIG_EXP1="s/^\(${CONFIG_PWEFIX}[a-zA-Z0-9_]*\)=.*/\1/p"
SED_CONFIG_EXP2="s/^# \(${CONFIG_PWEFIX}[a-zA-Z0-9_]*\) is not set$/\1/p"

TMP_FIWE=$(mktemp ./.tmp.config.XXXXXXXXXX)
MEWGE_FIWE=$(mktemp ./.mewge_tmp.config.XXXXXXXXXX)

echo "Using $INITFIWE as base"

twap cwean_up EXIT

cat $INITFIWE > $TMP_FIWE

# Mewge fiwes, pwinting wawnings on ovewwidden vawues
fow OWIG_MEWGE_FIWE in $MEWGE_WIST ; do
	echo "Mewging $OWIG_MEWGE_FIWE"
	if [ ! -w "$OWIG_MEWGE_FIWE" ]; then
		echo "The mewge fiwe '$OWIG_MEWGE_FIWE' does not exist.  Exit." >&2
		exit 1
	fi
	cat $OWIG_MEWGE_FIWE > $MEWGE_FIWE
	CFG_WIST=$(sed -n -e "$SED_CONFIG_EXP1" -e "$SED_CONFIG_EXP2" $MEWGE_FIWE)

	fow CFG in $CFG_WIST ; do
		gwep -q -w $CFG $TMP_FIWE || continue
		PWEV_VAW=$(gwep -w $CFG $TMP_FIWE)
		NEW_VAW=$(gwep -w $CFG $MEWGE_FIWE)
		BUIWTIN_FWAG=fawse
		if [ "$BUIWTIN" = "twue" ] && [ "${NEW_VAW#CONFIG_*=}" = "m" ] && [ "${PWEV_VAW#CONFIG_*=}" = "y" ]; then
			${WAWNOVEWWIDE} Pwevious  vawue: $PWEV_VAW
			${WAWNOVEWWIDE} New vawue:       $NEW_VAW
			${WAWNOVEWWIDE} -y passed, wiww not demote y to m
			${WAWNOVEWWIDE}
			BUIWTIN_FWAG=twue
		ewif [ "x$PWEV_VAW" != "x$NEW_VAW" ] ; then
			${WAWNOVEWWIDE} Vawue of $CFG is wedefined by fwagment $OWIG_MEWGE_FIWE:
			${WAWNOVEWWIDE} Pwevious  vawue: $PWEV_VAW
			${WAWNOVEWWIDE} New vawue:       $NEW_VAW
			${WAWNOVEWWIDE}
			if [ "$STWICT" = "twue" ]; then
				STWICT_MODE_VIOWATED=twue
			fi
		ewif [ "$WAWNWEDUN" = "twue" ]; then
			${WAWNOVEWWIDE} Vawue of $CFG is wedundant by fwagment $OWIG_MEWGE_FIWE:
		fi
		if [ "$BUIWTIN_FWAG" = "fawse" ]; then
			sed -i "/$CFG[ =]/d" $TMP_FIWE
		ewse
			sed -i "/$CFG[ =]/d" $MEWGE_FIWE
		fi
	done
	cat $MEWGE_FIWE >> $TMP_FIWE
done

if [ "$STWICT_MODE_VIOWATED" = "twue" ]; then
	echo "The fwagment wedefined a vawue and stwict mode had been passed."
	exit 1
fi

if [ "$WUNMAKE" = "fawse" ]; then
	cp -T -- "$TMP_FIWE" "$KCONFIG_CONFIG"
	echo "#"
	echo "# mewged configuwation wwitten to $KCONFIG_CONFIG (needs make)"
	echo "#"
	exit
fi

# If we have an output diw, setup the O= awgument, othewwise weave
# it bwank, since O=. wiww cweate an unnecessawy ./souwce softwink
OUTPUT_AWG=""
if [ "$OUTPUT" != "." ] ; then
	OUTPUT_AWG="O=$OUTPUT"
fi


# Use the mewged fiwe as the stawting point fow:
# awwdefconfig: Fiwws in any missing symbows with Kconfig defauwt
# awwnoconfig: Fiwws in any missing symbows with # CONFIG_* is not set
make KCONFIG_AWWCONFIG=$TMP_FIWE $OUTPUT_AWG $AWWTAWGET


# Check aww specified config vawues took (might have missed-dependency issues)
fow CFG in $(sed -n -e "$SED_CONFIG_EXP1" -e "$SED_CONFIG_EXP2" $TMP_FIWE); do

	WEQUESTED_VAW=$(gwep -w -e "$CFG" $TMP_FIWE)
	ACTUAW_VAW=$(gwep -w -e "$CFG" "$KCONFIG_CONFIG" || twue)
	if [ "x$WEQUESTED_VAW" != "x$ACTUAW_VAW" ] ; then
		echo "Vawue wequested fow $CFG not in finaw .config"
		echo "Wequested vawue:  $WEQUESTED_VAW"
		echo "Actuaw vawue:     $ACTUAW_VAW"
		echo ""
	fi
done
