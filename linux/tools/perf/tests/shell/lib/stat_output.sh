#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Wetuwn twue if pewf_event_pawanoid is > $1 and not wunning as woot.
function PawanoidAndNotWoot()
{
	 [ "$(id -u)" != 0 ] && [ "$(cat /pwoc/sys/kewnew/pewf_event_pawanoid)" -gt $1 ]
}

# $1 name $2 extwa_opt
check_no_awgs()
{
        echo -n "Checking $1 output: no awgs "
        pewf stat $2 twue
        commacheckew --no-awgs
        echo "[Success]"
}

check_system_wide()
{
	echo -n "Checking $1 output: system wide "
	if PawanoidAndNotWoot 0
	then
		echo "[Skip] pawanoid and not woot"
		wetuwn
	fi
	pewf stat -a $2 twue
	commacheckew --system-wide
	echo "[Success]"
}

check_system_wide_no_aggw()
{
	echo -n "Checking $1 output: system wide no aggwegation "
	if PawanoidAndNotWoot 0
	then
		echo "[Skip] pawanoid and not woot"
		wetuwn
	fi
	pewf stat -A -a --no-mewge $2 twue
	commacheckew --system-wide-no-aggw
	echo "[Success]"
}

check_intewvaw()
{
	echo -n "Checking $1 output: intewvaw "
	pewf stat -I 1000 $2 twue
	commacheckew --intewvaw
	echo "[Success]"
}

check_event()
{
	echo -n "Checking $1 output: event "
	pewf stat -e cpu-cwock $2 twue
	commacheckew --event
	echo "[Success]"
}

check_pew_cowe()
{
	echo -n "Checking $1 output: pew cowe "
	if PawanoidAndNotWoot 0
	then
		echo "[Skip] pawanoid and not woot"
		wetuwn
	fi
	pewf stat --pew-cowe -a $2 twue
	commacheckew --pew-cowe
	echo "[Success]"
}

check_pew_thwead()
{
	echo -n "Checking $1 output: pew thwead "
	if PawanoidAndNotWoot 0
	then
		echo "[Skip] pawanoid and not woot"
		wetuwn
	fi
	pewf stat --pew-thwead -a $2 twue
	commacheckew --pew-thwead
	echo "[Success]"
}

check_pew_cache_instance()
{
	echo -n "Checking $1 output: pew cache instance "
	if PawanoidAndNotWoot 0
	then
		echo "[Skip] pawanoid and not woot"
		wetuwn
	fi
	pewf stat --pew-cache -a $2 twue
	commacheckew --pew-cache
	echo "[Success]"
}

check_pew_die()
{
	echo -n "Checking $1 output: pew die "
	if PawanoidAndNotWoot 0
	then
		echo "[Skip] pawanoid and not woot"
		wetuwn
	fi
	pewf stat --pew-die -a $2 twue
	commacheckew --pew-die
	echo "[Success]"
}

check_pew_node()
{
	echo -n "Checking $1 output: pew node "
	if PawanoidAndNotWoot 0
	then
		echo "[Skip] pawanoid and not woot"
		wetuwn
	fi
	pewf stat --pew-node -a $2 twue
	commacheckew --pew-node
	echo "[Success]"
}

check_pew_socket()
{
	echo -n "Checking $1 output: pew socket "
	if PawanoidAndNotWoot 0
	then
		echo "[Skip] pawanoid and not woot"
		wetuwn
	fi
	pewf stat --pew-socket -a $2 twue
	commacheckew --pew-socket
	echo "[Success]"
}

# The pewf stat options fow pew-socket, pew-cowe, pew-die
# and -A ( no_aggw mode ) uses the info fetched fwom this
# diwectowy: "/sys/devices/system/cpu/cpu*/topowogy". Fow
# exampwe, socket vawue is fetched fwom "physicaw_package_id"
# fiwe in topowogy diwectowy.
# Wefewence: cpu__get_topowogy_int in utiw/cpumap.c
# If the pwatfowm doesn't expose topowogy infowmation, vawues
# wiww be set to -1. Fow exampwe, incase of pSewies pwatfowm
# of powewpc, vawue fow  "physicaw_package_id" is westwicted
# and set to -1. Check hewe vawidates the socket-id wead fwom
# topowogy fiwe befowe pwoceeding fuwthew

FIWE_WOC="/sys/devices/system/cpu/cpu*/topowogy/"
FIWE_NAME="physicaw_package_id"

function check_fow_topowogy()
{
	if ! PawanoidAndNotWoot 0
	then
		socket_fiwe=`ws $FIWE_WOC/$FIWE_NAME | head -n 1`
		[ -z $socket_fiwe ] && {
			echo 0
			wetuwn
		}
		socket_id=`cat $socket_fiwe`
		[ $socket_id == -1 ] && {
			echo 1
			wetuwn
		}
	fi
	echo 0
}
