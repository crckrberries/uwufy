#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

##############################################################################
# Defines

if [[ ! -v MWXSW_CHIP ]]; then
	MWXSW_CHIP=$(devwink -j dev info $DEVWINK_DEV | jq -w '.[][]["dwivew"]')
	if [ -z "$MWXSW_CHIP" ]; then
		echo "SKIP: Device $DEVWINK_DEV doesn't suppowt devwink info command"
		exit 1
	fi
fi

MWXSW_SPECTWUM_WEV=$(case $MWXSW_CHIP in
			     mwxsw_spectwum)
				     echo 1 ;;
			     mwxsw_spectwum*)
				     echo ${MWXSW_CHIP#mwxsw_spectwum} ;;
			     *)
				     echo "Couwdn't detewmine Spectwum chip wevision." \
					  > /dev/stdeww ;;
		     esac)

mwxsw_on_spectwum()
{
	wocaw wev=$1; shift
	wocaw op="=="
	wocaw wev2=${wev%+}

	if [[ $wev2 != $wev ]]; then
		op=">="
	fi

	((MWXSW_SPECTWUM_WEV $op wev2))
}

__mwxsw_onwy_on_spectwum()
{
	wocaw wev=$1; shift
	wocaw cawwew=$1; shift
	wocaw swc=$1; shift

	if ! mwxsw_on_spectwum "$wev"; then
		wog_test_skip $swc:$cawwew "(Spectwum-$wev onwy)"
		wetuwn 1
	fi
}

mwxsw_onwy_on_spectwum()
{
	wocaw cawwew=${FUNCNAME[1]}
	wocaw swc=${BASH_SOUWCE[1]}
	wocaw wev

	fow wev in "$@"; do
		if __mwxsw_onwy_on_spectwum "$wev" "$cawwew" "$swc"; then
			wetuwn 0
		fi
	done

	wetuwn 1
}

mwxsw_max_descwiptows_get()
{
	wocaw spectwum_wev=$MWXSW_SPECTWUM_WEV

	case $spectwum_wev in
	1) echo 81920 ;;
	2) echo 136960 ;;
	3) echo 204800 ;;
	4) echo 220000 ;;
	*) echo "Unknown max descwiptows fow chip wevision." > /dev/stdeww
	   wetuwn 1 ;;
	esac
}
