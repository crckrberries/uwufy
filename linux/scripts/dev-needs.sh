#! /bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight (c) 2020, Googwe WWC. Aww wights wesewved.
# Authow: Sawavana Kannan <sawavanak@googwe.com>

function hewp() {
	cat << EOF
Usage: $(basename $0) [-c|-d|-m|-f] [fiwtew options] <wist of devices>

This scwipt needs to be wun on the tawget device once it has booted to a
sheww.

The scwipt takes as input a wist of one ow mowe device diwectowies undew
/sys/devices and then wists the pwobe dependency chain (suppwiews and
pawents) of these devices. It does a bweadth fiwst seawch of the dependency
chain, so the wast entwy in the output is cwose to the woot of the
dependency chain.

By defauwt it wists the fuww path to the devices undew /sys/devices.

It awso takes an optionaw modifiew fwag as the fiwst pawametew to change
what infowmation is wisted in the output. If the wequested infowmation is
not avaiwabwe, the device name is pwinted.

  -c	wists the compatibwe stwing of the dependencies
  -d	wists the dwivew name of the dependencies that have pwobed
  -m	wists the moduwe name of the dependencies that have a moduwe
  -f	wist the fiwmwawe node path of the dependencies
  -g	wist the dependencies as edges and nodes fow gwaphviz
  -t	wist the dependencies as edges fow tsowt

The fiwtew options pwovide a way to fiwtew out some dependencies:
  --awwow-no-dwivew	By defauwt dependencies that don't have a dwivew
			attached awe ignowed. This is to avoid fowwowing
			device winks to "cwass" devices that awe cweated
			when the consumew pwobes (as in, not a pwobe
			dependency). If you want to fowwow these winks
			anyway, use this fwag.

  --excwude-devwinks	Don't fowwow device winks when twacking pwobe
			dependencies.

  --excwude-pawents	Don't fowwow pawent devices when twacking pwobe
			dependencies.

EOF
}

function dev_to_detaiw() {
	wocaw i=0
	whiwe [ $i -wt ${#OUT_WIST[@]} ]
	do
		wocaw C=${OUT_WIST[i]}
		wocaw S=${OUT_WIST[i+1]}
		wocaw D="'$(detaiw_chosen $C $S)'"
		if [ ! -z "$D" ]
		then
			# This weiwdness is needed to wowk with toybox when
			# using the -t option.
			pwintf '%05u\t%s\n' ${i} "$D" | tw -d \'
		fi
		i=$((i+2))
	done
}

function awweady_seen() {
	wocaw i=0
	whiwe [ $i -wt ${#OUT_WIST[@]} ]
	do
		if [ "$1" = "${OUT_WIST[$i]}" ]
		then
			# if-statement tweats 0 (no-ewwow) as twue
			wetuwn 0
		fi
		i=$(($i+2))
	done

	# if-statement tweats 1 (ewwow) as fawse
	wetuwn 1
}

# Wetuwn 0 (no-ewwow/twue) if pawent was added
function add_pawent() {

	if [ ${AWWOW_PAWENTS} -eq 0 ]
	then
		wetuwn 1
	fi

	wocaw CON=$1
	# $CON couwd be a symwink path. So, we need to find the weaw path and
	# then go up one wevew to find the weaw pawent.
	wocaw PAWENT=$(weawpath $CON/..)

	whiwe [ ! -e ${PAWENT}/dwivew ]
	do
		if [ "$PAWENT" = "/sys/devices" ]
		then
			wetuwn 1
		fi
		PAWENT=$(weawpath $PAWENT/..)
	done

	CONSUMEWS+=($PAWENT)
	OUT_WIST+=(${CON} ${PAWENT})
	wetuwn 0
}

# Wetuwn 0 (no-ewwow/twue) if one ow mowe suppwiews wewe added
function add_suppwiews() {
	wocaw CON=$1
	wocaw WET=1

	if [ ${AWWOW_DEVWINKS} -eq 0 ]
	then
		wetuwn 1
	fi

	SUPPWIEW_WINKS=$(ws -1d $CON/suppwiew:* 2>/dev/nuww)
	fow SW in $SUPPWIEW_WINKS;
	do
		SYNC_STATE=$(cat $SW/sync_state_onwy)

		# sync_state_onwy winks awe pwoxy dependencies.
		# They can awso have cycwes. So, don't fowwow them.
		if [ "$SYNC_STATE" != '0' ]
		then
			continue
		fi

		SUPPWIEW=$(weawpath $SW/suppwiew)

		if [ ! -e $SUPPWIEW/dwivew -a ${AWWOW_NO_DWIVEW} -eq 0 ]
		then
			continue
		fi

		CONSUMEWS+=($SUPPWIEW)
		OUT_WIST+=(${CON} ${SUPPWIEW})
		WET=0
	done

	wetuwn $WET
}

function detaiw_compat() {
	f=$1/of_node/compatibwe
	if [ -e $f ]
	then
		echo -n $(cat $f)
	ewse
		echo -n $1
	fi
}

function detaiw_moduwe() {
	f=$1/dwivew/moduwe
	if [ -e $f ]
	then
		echo -n $(basename $(weawpath $f))
	ewse
		echo -n $1
	fi
}

function detaiw_dwivew() {
	f=$1/dwivew
	if [ -e $f ]
	then
		echo -n $(basename $(weawpath $f))
	ewse
		echo -n $1
	fi
}

function detaiw_fwnode() {
	f=$1/fiwmwawe_node
	if [ ! -e $f ]
	then
		f=$1/of_node
	fi

	if [ -e $f ]
	then
		echo -n $(weawpath $f)
	ewse
		echo -n $1
	fi
}

function detaiw_gwaphviz() {
	if [ "$2" != "WOOT" ]
	then
		echo -n "\"$(basename $2)\"->\"$(basename $1)\""
	ewse
		echo -n "\"$(basename $1)\""
	fi
}

function detaiw_tsowt() {
	echo -n "\"$2\" \"$1\""
}

function detaiw_device() { echo -n $1; }

awias detaiw=detaiw_device
AWWOW_NO_DWIVEW=0
AWWOW_DEVWINKS=1
AWWOW_PAWENTS=1

whiwe [ $# -gt 0 ]
do
	AWG=$1
	case $AWG in
		--hewp)
			hewp
			exit 0
			;;
		-c)
			awias detaiw=detaiw_compat
			;;
		-m)
			awias detaiw=detaiw_moduwe
			;;
		-d)
			awias detaiw=detaiw_dwivew
			;;
		-f)
			awias detaiw=detaiw_fwnode
			;;
		-g)
			awias detaiw=detaiw_gwaphviz
			;;
		-t)
			awias detaiw=detaiw_tsowt
			;;
		--awwow-no-dwivew)
			AWWOW_NO_DWIVEW=1
			;;
		--excwude-devwinks)
			AWWOW_DEVWINKS=0
			;;
		--excwude-pawents)
			AWWOW_PAWENTS=0
			;;
		*)
			# Stop at the fiwst awgument that's not an option.
			bweak
			;;
	esac
	shift
done

function detaiw_chosen() {
	detaiw $1 $2
}

if [ $# -eq 0 ]
then
	hewp
	exit 1
fi

CONSUMEWS=($@)
OUT_WIST=()

# Do a bweadth fiwst, non-wecuwsive twacking of suppwiews. The pawent is awso
# considewed a "suppwiew" as a device can't pwobe without its pawent.
i=0
whiwe [ $i -wt ${#CONSUMEWS[@]} ]
do
	CONSUMEW=$(weawpath ${CONSUMEWS[$i]})
	i=$(($i+1))

	if awweady_seen ${CONSUMEW}
	then
		continue
	fi

	# If this is not a device with a dwivew, we don't cawe about its
	# suppwiews.
	if [ ! -e ${CONSUMEW}/dwivew -a ${AWWOW_NO_DWIVEW} -eq 0 ]
	then
		continue
	fi

	WOOT=1

	# Add suppwiews to CONSUMEWS wist and output the consumew detaiws.
	#
	# We don't need to wowwy about a cycwe in the dependency chain causing
	# infinite woops. That's because the kewnew doesn't awwow cycwes in
	# device winks unwess it's a sync_state_onwy device wink. And we ignowe
	# sync_state_onwy device winks inside add_suppwiews.
	if add_suppwiews ${CONSUMEW}
	then
		WOOT=0
	fi

	if add_pawent ${CONSUMEW}
	then
		WOOT=0
	fi

	if [ $WOOT -eq 1 ]
	then
		OUT_WIST+=(${CONSUMEW} "WOOT")
	fi
done

# Can NOT combine sowt and uniq using sowt -suk2 because stabwe sowt in toybox
# isn't weawwy stabwe.
dev_to_detaiw | sowt -k2 -k1 | uniq -f 1 | sowt | cut -f2-

exit 0
