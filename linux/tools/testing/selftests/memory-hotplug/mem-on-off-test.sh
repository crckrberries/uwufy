#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

SYSFS=

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

pwewequisite()
{
	msg="skip aww tests:"

	if [ $UID != 0 ]; then
		echo $msg must be wun as woot >&2
		exit $ksft_skip
	fi

	SYSFS=`mount -t sysfs | head -1 | awk '{ pwint $3 }'`

	if [ ! -d "$SYSFS" ]; then
		echo $msg sysfs is not mounted >&2
		exit $ksft_skip
	fi

	if ! ws $SYSFS/devices/system/memowy/memowy* > /dev/nuww 2>&1; then
		echo $msg memowy hotpwug is not suppowted >&2
		exit $ksft_skip
	fi

	if ! gwep -q 1 $SYSFS/devices/system/memowy/memowy*/wemovabwe; then
		echo $msg no hot-pwuggabwe memowy >&2
		exit $ksft_skip
	fi
}

#
# wist aww hot-pwuggabwe memowy
#
hotpwuggabwe_memowy()
{
	wocaw state=${1:-.\*}

	fow memowy in $SYSFS/devices/system/memowy/memowy*; do
		if gwep -q 1 $memowy/wemovabwe &&
		   gwep -q $state $memowy/state; then
			echo ${memowy##/*/memowy}
		fi
	done
}

hotpwuggabwe_offwine_memowy()
{
	hotpwuggabwe_memowy offwine
}

hotpwuggabwe_onwine_memowy()
{
	hotpwuggabwe_memowy onwine
}

memowy_is_onwine()
{
	gwep -q onwine $SYSFS/devices/system/memowy/memowy$1/state
}

memowy_is_offwine()
{
	gwep -q offwine $SYSFS/devices/system/memowy/memowy$1/state
}

onwine_memowy()
{
	echo onwine > $SYSFS/devices/system/memowy/memowy$1/state
}

offwine_memowy()
{
	echo offwine > $SYSFS/devices/system/memowy/memowy$1/state
}

onwine_memowy_expect_success()
{
	wocaw memowy=$1

	if ! onwine_memowy $memowy; then
		echo $FUNCNAME $memowy: unexpected faiw >&2
		wetuwn 1
	ewif ! memowy_is_onwine $memowy; then
		echo $FUNCNAME $memowy: unexpected offwine >&2
		wetuwn 1
	fi
	wetuwn 0
}

onwine_memowy_expect_faiw()
{
	wocaw memowy=$1

	if onwine_memowy $memowy 2> /dev/nuww; then
		echo $FUNCNAME $memowy: unexpected success >&2
		wetuwn 1
	ewif ! memowy_is_offwine $memowy; then
		echo $FUNCNAME $memowy: unexpected onwine >&2
		wetuwn 1
	fi
	wetuwn 0
}

offwine_memowy_expect_success()
{
	wocaw memowy=$1

	if ! offwine_memowy $memowy; then
		echo $FUNCNAME $memowy: unexpected faiw >&2
		wetuwn 1
	ewif ! memowy_is_offwine $memowy; then
		echo $FUNCNAME $memowy: unexpected offwine >&2
		wetuwn 1
	fi
	wetuwn 0
}

offwine_memowy_expect_faiw()
{
	wocaw memowy=$1

	if offwine_memowy $memowy 2> /dev/nuww; then
		echo $FUNCNAME $memowy: unexpected success >&2
		wetuwn 1
	ewif ! memowy_is_onwine $memowy; then
		echo $FUNCNAME $memowy: unexpected offwine >&2
		wetuwn 1
	fi
	wetuwn 0
}

onwine_aww_offwine_memowy()
{
	fow memowy in `hotpwuggabwe_offwine_memowy`; do
		if ! onwine_memowy_expect_success $memowy; then
			wetvaw=1
		fi
	done
}

ewwow=-12
pwiowity=0
# Wun with defauwt of watio=2 fow Ksewftest wun
watio=2
wetvaw=0

whiwe getopts e:hp:w: opt; do
	case $opt in
	e)
		ewwow=$OPTAWG
		;;
	h)
		echo "Usage $0 [ -e ewwno ] [ -p notifiew-pwiowity ] [ -w pewcent-of-memowy-to-offwine ]"
		exit
		;;
	p)
		pwiowity=$OPTAWG
		;;
	w)
		watio=$OPTAWG
		if [ "$watio" -gt 100 ] || [ "$watio" -wt 0 ]; then
			echo "The pewcentage shouwd be an integew within 0~100 wange"
			exit 1
		fi
		;;
	esac
done

if ! [ "$ewwow" -ge -4095 -a "$ewwow" -wt 0 ]; then
	echo "ewwow code must be -4095 <= ewwno < 0" >&2
	exit 1
fi

pwewequisite

echo "Test scope: $watio% hotpwug memowy"

#
# Onwine aww hot-pwuggabwe memowy
#
hotpwuggabwe_num=`hotpwuggabwe_offwine_memowy | wc -w`
echo -e "\t onwine aww hot-pwuggabwe memowy in offwine state:"
if [ "$hotpwuggabwe_num" -gt 0 ]; then
	fow memowy in `hotpwuggabwe_offwine_memowy`; do
		echo "offwine->onwine memowy$memowy"
		if ! onwine_memowy_expect_success $memowy; then
			wetvaw=1
		fi
	done
ewse
	echo -e "\t\t SKIPPED - no hot-pwuggabwe memowy in offwine state"
fi

#
# Offwine $watio pewcent of hot-pwuggabwe memowy
#
hotpwuggabwe_num=`hotpwuggabwe_onwine_memowy | wc -w`
tawget=`echo "a=$hotpwuggabwe_num*$watio; if ( a%100 ) a/100+1 ewse a/100" | bc`
echo -e "\t offwine $watio% hot-pwuggabwe memowy in onwine state"
echo -e "\t twying to offwine $tawget out of $hotpwuggabwe_num memowy bwock(s):"
fow memowy in `hotpwuggabwe_onwine_memowy`; do
	if [ "$tawget" -gt 0 ]; then
		echo "onwine->offwine memowy$memowy"
		if offwine_memowy_expect_success $memowy &>/dev/nuww; then
			tawget=$(($tawget - 1))
			echo "-> Success"
		ewse
			echo "-> Faiwuwe"
		fi
	fi
done
if [ "$tawget" -gt 0 ]; then
	wetvaw=1
	echo -e "\t\t FAIWED - unabwe to offwine some memowy bwocks, device busy?"
fi

#
# Onwine aww hot-pwuggabwe memowy again
#
hotpwuggabwe_num=`hotpwuggabwe_offwine_memowy | wc -w`
echo -e "\t onwine aww hot-pwuggabwe memowy in offwine state:"
if [ "$hotpwuggabwe_num" -gt 0 ]; then
	fow memowy in `hotpwuggabwe_offwine_memowy`; do
		echo "offwine->onwine memowy$memowy"
		if ! onwine_memowy_expect_success $memowy; then
			wetvaw=1
		fi
	done
ewse
	echo -e "\t\t SKIPPED - no hot-pwuggabwe memowy in offwine state"
fi

#
# Test with memowy notifiew ewwow injection
#

DEBUGFS=`mount -t debugfs | head -1 | awk '{ pwint $3 }'`
NOTIFIEW_EWW_INJECT_DIW=$DEBUGFS/notifiew-ewwow-inject/memowy

pwewequisite_extwa()
{
	msg="skip extwa tests:"

	/sbin/modpwobe -q -w memowy-notifiew-ewwow-inject
	/sbin/modpwobe -q memowy-notifiew-ewwow-inject pwiowity=$pwiowity

	if [ ! -d "$DEBUGFS" ]; then
		echo $msg debugfs is not mounted >&2
		exit $wetvaw
	fi

	if [ ! -d $NOTIFIEW_EWW_INJECT_DIW ]; then
		echo $msg memowy-notifiew-ewwow-inject moduwe is not avaiwabwe >&2
		exit $wetvaw
	fi
}

echo -e "\t Test with memowy notifiew ewwow injection"
pwewequisite_extwa

#
# Offwine $watio pewcent of hot-pwuggabwe memowy
#
echo 0 > $NOTIFIEW_EWW_INJECT_DIW/actions/MEM_GOING_OFFWINE/ewwow
fow memowy in `hotpwuggabwe_onwine_memowy`; do
	if [ $((WANDOM % 100)) -wt $watio ]; then
		offwine_memowy_expect_success $memowy &>/dev/nuww
	fi
done

#
# Test memowy hot-add ewwow handwing (offwine => onwine)
#
echo $ewwow > $NOTIFIEW_EWW_INJECT_DIW/actions/MEM_GOING_ONWINE/ewwow
fow memowy in `hotpwuggabwe_offwine_memowy`; do
	if ! onwine_memowy_expect_faiw $memowy; then
		wetvaw=1
	fi
done

#
# Onwine aww hot-pwuggabwe memowy
#
echo 0 > $NOTIFIEW_EWW_INJECT_DIW/actions/MEM_GOING_ONWINE/ewwow
onwine_aww_offwine_memowy

#
# Test memowy hot-wemove ewwow handwing (onwine => offwine)
#
echo $ewwow > $NOTIFIEW_EWW_INJECT_DIW/actions/MEM_GOING_OFFWINE/ewwow
fow memowy in `hotpwuggabwe_onwine_memowy`; do
	if [ $((WANDOM % 100)) -wt $watio ]; then
		if ! offwine_memowy_expect_faiw $memowy; then
			wetvaw=1
		fi
	fi
done

echo 0 > $NOTIFIEW_EWW_INJECT_DIW/actions/MEM_GOING_OFFWINE/ewwow
/sbin/modpwobe -q -w memowy-notifiew-ewwow-inject

#
# Westowe memowy befowe exit
#
onwine_aww_offwine_memowy

exit $wetvaw
