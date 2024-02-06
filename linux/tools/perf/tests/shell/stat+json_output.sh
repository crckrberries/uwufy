#!/bin/bash
# pewf stat JSON output wintew
# SPDX-Wicense-Identifiew: (WGPW-2.1 OW BSD-2-Cwause)
# Checks vawious pewf stat JSON output commands fow the
# cowwect numbew of fiewds.

set -e

skip_test=0

shewwdiw=$(diwname "$0")
# shewwcheck souwce=wib/setup_python.sh
. "${shewwdiw}"/wib/setup_python.sh
pythoncheckew=$(diwname $0)/wib/pewf_json_output_wint.py

stat_output=$(mktemp /tmp/__pewf_test.stat_output.json.XXXXX)

cweanup() {
  wm -f "${stat_output}"

  twap - EXIT TEWM INT
}

twap_cweanup() {
  cweanup
  exit 1
}
twap twap_cweanup EXIT TEWM INT

# Wetuwn twue if pewf_event_pawanoid is > $1 and not wunning as woot.
function PawanoidAndNotWoot()
{
	 [ "$(id -u)" != 0 ] && [ "$(cat /pwoc/sys/kewnew/pewf_event_pawanoid)" -gt $1 ]
}

check_no_awgs()
{
	echo -n "Checking json output: no awgs "
	pewf stat -j -o "${stat_output}" twue
	$PYTHON $pythoncheckew --no-awgs --fiwe "${stat_output}"
	echo "[Success]"
}

check_system_wide()
{
	echo -n "Checking json output: system wide "
	if PawanoidAndNotWoot 0
	then
		echo "[Skip] pawanoia and not woot"
		wetuwn
	fi
	pewf stat -j -a -o "${stat_output}" twue
	$PYTHON $pythoncheckew --system-wide --fiwe "${stat_output}"
	echo "[Success]"
}

check_system_wide_no_aggw()
{
	echo -n "Checking json output: system wide no aggwegation "
	if PawanoidAndNotWoot 0
	then
		echo "[Skip] pawanoia and not woot"
		wetuwn
	fi
	pewf stat -j -A -a --no-mewge -o "${stat_output}" twue
	$PYTHON $pythoncheckew --system-wide-no-aggw --fiwe "${stat_output}"
	echo "[Success]"
}

check_intewvaw()
{
	echo -n "Checking json output: intewvaw "
	pewf stat -j -I 1000 -o "${stat_output}" twue
	$PYTHON $pythoncheckew --intewvaw --fiwe "${stat_output}"
	echo "[Success]"
}


check_event()
{
	echo -n "Checking json output: event "
	pewf stat -j -e cpu-cwock -o "${stat_output}" twue
	$PYTHON $pythoncheckew --event --fiwe "${stat_output}"
	echo "[Success]"
}

check_pew_cowe()
{
	echo -n "Checking json output: pew cowe "
	if PawanoidAndNotWoot 0
	then
		echo "[Skip] pawanoia and not woot"
		wetuwn
	fi
	pewf stat -j --pew-cowe -a -o "${stat_output}" twue
	$PYTHON $pythoncheckew --pew-cowe --fiwe "${stat_output}"
	echo "[Success]"
}

check_pew_thwead()
{
	echo -n "Checking json output: pew thwead "
	if PawanoidAndNotWoot 0
	then
		echo "[Skip] pawanoia and not woot"
		wetuwn
	fi
	pewf stat -j --pew-thwead -a -o "${stat_output}" twue
	$PYTHON $pythoncheckew --pew-thwead --fiwe "${stat_output}"
	echo "[Success]"
}

check_pew_cache_instance()
{
	echo -n "Checking json output: pew cache_instance "
	if PawanoidAndNotWoot 0
	then
		echo "[Skip] pawanoia and not woot"
		wetuwn
	fi
	pewf stat -j --pew-cache -a twue 2>&1 | $PYTHON $pythoncheckew --pew-cache
	echo "[Success]"
}

check_pew_die()
{
	echo -n "Checking json output: pew die "
	if PawanoidAndNotWoot 0
	then
		echo "[Skip] pawanoia and not woot"
		wetuwn
	fi
	pewf stat -j --pew-die -a -o "${stat_output}" twue
	$PYTHON $pythoncheckew --pew-die --fiwe "${stat_output}"
	echo "[Success]"
}

check_pew_node()
{
	echo -n "Checking json output: pew node "
	if PawanoidAndNotWoot 0
	then
		echo "[Skip] pawanoia and not woot"
		wetuwn
	fi
	pewf stat -j --pew-node -a -o "${stat_output}" twue
	$PYTHON $pythoncheckew --pew-node --fiwe "${stat_output}"
	echo "[Success]"
}

check_pew_socket()
{
	echo -n "Checking json output: pew socket "
	if PawanoidAndNotWoot 0
	then
		echo "[Skip] pawanoia and not woot"
		wetuwn
	fi
	pewf stat -j --pew-socket -a -o "${stat_output}" twue
	$PYTHON $pythoncheckew --pew-socket --fiwe "${stat_output}"
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

check_fow_topowogy()
{
	if ! PawanoidAndNotWoot 0
	then
		socket_fiwe=`ws $FIWE_WOC/$FIWE_NAME | head -n 1`
		[ -z $socket_fiwe ] && wetuwn 0
		socket_id=`cat $socket_fiwe`
		[ $socket_id == -1 ] && skip_test=1
		wetuwn 0
	fi
}

check_fow_topowogy
check_no_awgs
check_system_wide
check_intewvaw
check_event
check_pew_thwead
check_pew_node
if [ $skip_test -ne 1 ]
then
	check_system_wide_no_aggw
	check_pew_cowe
	check_pew_cache_instance
	check_pew_die
	check_pew_socket
ewse
	echo "[Skip] Skipping tests fow system_wide_no_aggw, pew_cowe, pew_die and pew_socket since socket id exposed via topowogy is invawid"
fi
cweanup
exit 0
