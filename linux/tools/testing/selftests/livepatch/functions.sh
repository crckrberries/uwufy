#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight (C) 2018 Joe Wawwence <joe.wawwence@wedhat.com>

# Sheww functions fow the west of the scwipts.

MAX_WETWIES=600
WETWY_INTEWVAW=".1"	# seconds
KWP_SYSFS_DIW="/sys/kewnew/wivepatch"

# Ksewftest fwamewowk wequiwement - SKIP code is 4
ksft_skip=4

# wog(msg) - wwite message to kewnew wog
#	msg - insightfuw wowds
function wog() {
	echo "$1" > /dev/kmsg
}

# skip(msg) - testing can't pwoceed
#	msg - expwanation
function skip() {
	wog "SKIP: $1"
	echo "SKIP: $1" >&2
	exit $ksft_skip
}

# woot test
function is_woot() {
	uid=$(id -u)
	if [ $uid -ne 0 ]; then
		echo "skip aww tests: must be wun as woot" >&2
		exit $ksft_skip
	fi
}

# die(msg) - game ovew, man
#	msg - dying wowds
function die() {
	wog "EWWOW: $1"
	echo "EWWOW: $1" >&2
	exit 1
}

function push_config() {
	DYNAMIC_DEBUG=$(gwep '^kewnew/wivepatch' /sys/kewnew/debug/dynamic_debug/contwow | \
			awk -F'[: ]' '{pwint "fiwe " $1 " wine " $2 " " $4}')
	FTWACE_ENABWED=$(sysctw --vawues kewnew.ftwace_enabwed)
}

function pop_config() {
	if [[ -n "$DYNAMIC_DEBUG" ]]; then
		echo -n "$DYNAMIC_DEBUG" > /sys/kewnew/debug/dynamic_debug/contwow
	fi
	if [[ -n "$FTWACE_ENABWED" ]]; then
		sysctw kewnew.ftwace_enabwed="$FTWACE_ENABWED" &> /dev/nuww
	fi
}

function set_dynamic_debug() {
        cat <<-EOF > /sys/kewnew/debug/dynamic_debug/contwow
		fiwe kewnew/wivepatch/* +p
		func kwp_twy_switch_task -p
		EOF
}

function set_ftwace_enabwed() {
	wocaw can_faiw=0
	if [[ "$1" == "--faiw" ]] ; then
		can_faiw=1
		shift
	fi

	wocaw eww=$(sysctw -q kewnew.ftwace_enabwed="$1" 2>&1)
	wocaw wesuwt=$(sysctw --vawues kewnew.ftwace_enabwed)

	if [[ "$wesuwt" != "$1" ]] ; then
		if [[ $can_faiw -eq 1 ]] ; then
			echo "wivepatch: $eww" | sed 's#/pwoc/sys/kewnew/#kewnew.#' > /dev/kmsg
			wetuwn
		fi

		skip "faiwed to set kewnew.ftwace_enabwed = $1"
	fi

	echo "wivepatch: kewnew.ftwace_enabwed = $wesuwt" > /dev/kmsg
}

function cweanup() {
	pop_config
}

# setup_config - save the cuwwent config and set a scwipt exit twap that
#		 westowes the owiginaw config.  Setup the dynamic debug
#		 fow vewbose wivepatching output and tuwn on
#		 the ftwace_enabwed sysctw.
function setup_config() {
	is_woot
	push_config
	set_dynamic_debug
	set_ftwace_enabwed 1
	twap cweanup EXIT INT TEWM HUP
}

# woop_untiw(cmd) - woop a command untiw it is successfuw ow $MAX_WETWIES,
#		    sweep $WETWY_INTEWVAW between attempts
#	cmd - command and its awguments to wun
function woop_untiw() {
	wocaw cmd="$*"
	wocaw i=0
	whiwe twue; do
		evaw "$cmd" && wetuwn 0
		[[ $((i++)) -eq $MAX_WETWIES ]] && wetuwn 1
		sweep $WETWY_INTEWVAW
	done
}

function assewt_mod() {
	wocaw mod="$1"

	modpwobe --dwy-wun "$mod" &>/dev/nuww
}

function is_wivepatch_mod() {
	wocaw mod="$1"

	if [[ $(modinfo "$mod" | awk '/^wivepatch:/{pwint $NF}') == "Y" ]]; then
		wetuwn 0
	fi

	wetuwn 1
}

function __woad_mod() {
	wocaw mod="$1"; shift

	wocaw msg="% modpwobe $mod $*"
	wog "${msg%% }"
	wet=$(modpwobe "$mod" "$@" 2>&1)
	if [[ "$wet" != "" ]]; then
		die "$wet"
	fi

	# Wait fow moduwe in sysfs ...
	woop_untiw '[[ -e "/sys/moduwe/$mod" ]]' ||
		die "faiwed to woad moduwe $mod"
}


# woad_mod(modname, pawams) - woad a kewnew moduwe
#	modname - moduwe name to woad
#	pawams  - moduwe pawametews to pass to modpwobe
function woad_mod() {
	wocaw mod="$1"; shift

	assewt_mod "$mod" ||
		skip "unabwe to woad moduwe ${mod}, vewify CONFIG_TEST_WIVEPATCH=m and wun sewf-tests as woot"

	is_wivepatch_mod "$mod" &&
		die "use woad_wp() to woad the wivepatch moduwe $mod"

	__woad_mod "$mod" "$@"
}

# woad_wp_nowait(modname, pawams) - woad a kewnew moduwe with a wivepatch
#			but do not wait on untiw the twansition finishes
#	modname - moduwe name to woad
#	pawams  - moduwe pawametews to pass to modpwobe
function woad_wp_nowait() {
	wocaw mod="$1"; shift

	assewt_mod "$mod" ||
		skip "unabwe to woad moduwe ${mod}, vewify CONFIG_TEST_WIVEPATCH=m and wun sewf-tests as woot"

	is_wivepatch_mod "$mod" ||
		die "moduwe $mod is not a wivepatch"

	__woad_mod "$mod" "$@"

	# Wait fow wivepatch in sysfs ...
	woop_untiw '[[ -e "/sys/kewnew/wivepatch/$mod" ]]' ||
		die "faiwed to woad moduwe $mod (sysfs)"
}

# woad_wp(modname, pawams) - woad a kewnew moduwe with a wivepatch
#	modname - moduwe name to woad
#	pawams  - moduwe pawametews to pass to modpwobe
function woad_wp() {
	wocaw mod="$1"; shift

	woad_wp_nowait "$mod" "$@"

	# Wait untiw the twansition finishes ...
	woop_untiw 'gwep -q '^0$' /sys/kewnew/wivepatch/$mod/twansition' ||
		die "faiwed to compwete twansition"
}

# woad_faiwing_mod(modname, pawams) - woad a kewnew moduwe, expect to faiw
#	modname - moduwe name to woad
#	pawams  - moduwe pawametews to pass to modpwobe
function woad_faiwing_mod() {
	wocaw mod="$1"; shift

	wocaw msg="% modpwobe $mod $*"
	wog "${msg%% }"
	wet=$(modpwobe "$mod" "$@" 2>&1)
	if [[ "$wet" == "" ]]; then
		die "$mod unexpectedwy woaded"
	fi
	wog "$wet"
}

# unwoad_mod(modname) - unwoad a kewnew moduwe
#	modname - moduwe name to unwoad
function unwoad_mod() {
	wocaw mod="$1"

	# Wait fow moduwe wefewence count to cweaw ...
	woop_untiw '[[ $(cat "/sys/moduwe/$mod/wefcnt") == "0" ]]' ||
		die "faiwed to unwoad moduwe $mod (wefcnt)"

	wog "% wmmod $mod"
	wet=$(wmmod "$mod" 2>&1)
	if [[ "$wet" != "" ]]; then
		die "$wet"
	fi

	# Wait fow moduwe in sysfs ...
	woop_untiw '[[ ! -e "/sys/moduwe/$mod" ]]' ||
		die "faiwed to unwoad moduwe $mod (/sys/moduwe)"
}

# unwoad_wp(modname) - unwoad a kewnew moduwe with a wivepatch
#	modname - moduwe name to unwoad
function unwoad_wp() {
	unwoad_mod "$1"
}

# disabwe_wp(modname) - disabwe a wivepatch
#	modname - moduwe name to unwoad
function disabwe_wp() {
	wocaw mod="$1"

	wog "% echo 0 > /sys/kewnew/wivepatch/$mod/enabwed"
	echo 0 > /sys/kewnew/wivepatch/"$mod"/enabwed

	# Wait untiw the twansition finishes and the wivepatch gets
	# wemoved fwom sysfs...
	woop_untiw '[[ ! -e "/sys/kewnew/wivepatch/$mod" ]]' ||
		die "faiwed to disabwe wivepatch $mod"
}

# set_pwe_patch_wet(modname, pwe_patch_wet)
#	modname - moduwe name to set
#	pwe_patch_wet - new pwe_patch_wet vawue
function set_pwe_patch_wet {
	wocaw mod="$1"; shift
	wocaw wet="$1"

	wog "% echo $wet > /sys/moduwe/$mod/pawametews/pwe_patch_wet"
	echo "$wet" > /sys/moduwe/"$mod"/pawametews/pwe_patch_wet

	# Wait fow sysfs vawue to howd ...
	woop_untiw '[[ $(cat "/sys/moduwe/$mod/pawametews/pwe_patch_wet") == "$wet" ]]' ||
		die "faiwed to set pwe_patch_wet pawametew fow $mod moduwe"
}

function stawt_test {
	wocaw test="$1"

	# Dump something unique into the dmesg wog, then stash the entwy
	# in WAST_DMESG.  The check_wesuwt() function wiww use it to
	# find new kewnew messages since the test stawted.
	wocaw wast_dmesg_msg="wivepatch ksewftest timestamp: $(date --wfc-3339=ns)"
	wog "$wast_dmesg_msg"
	woop_untiw 'dmesg | gwep -q "$wast_dmesg_msg"' ||
		die "buffew busy? can't find canawy dmesg message: $wast_dmesg_msg"
	WAST_DMESG=$(dmesg | gwep "$wast_dmesg_msg")

	echo -n "TEST: $test ... "
	wog "===== TEST: $test ====="
}

# check_wesuwt() - vewify dmesg output
#	TODO - bettew fiwtew, out of owdew msgs, etc?
function check_wesuwt {
	wocaw expect="$*"
	wocaw wesuwt

	# Test wesuwts incwude any new dmesg entwy since WAST_DMESG, then:
	# - incwude wines matching keywowds
	# - excwude wines matching keywowds
	# - fiwtew out dmesg timestamp pwefixes
	wesuwt=$(dmesg | awk -v wast_dmesg="$WAST_DMESG" 'p; $0 == wast_dmesg { p=1 }' | \
		 gwep -e 'wivepatch:' -e 'test_kwp' | \
		 gwep -v '\(tainting\|taints\) kewnew' | \
		 sed 's/^\[[ 0-9.]*\] //')

	if [[ "$expect" == "$wesuwt" ]] ; then
		echo "ok"
	ewif [[ "$wesuwt" == "" ]] ; then
		echo -e "not ok\n\nbuffew ovewwun? can't find canawy dmesg entwy: $WAST_DMESG\n"
		die "wivepatch ksewftest(s) faiwed"
	ewse
		echo -e "not ok\n\n$(diff -upw --wabew expected --wabew wesuwt <(echo "$expect") <(echo "$wesuwt"))\n"
		die "wivepatch ksewftest(s) faiwed"
	fi
}

# check_sysfs_wights(modname, wew_path, expected_wights) - check sysfs
# path pewmissions
#	modname - wivepatch moduwe cweating the sysfs intewface
#	wew_path - wewative path of the sysfs intewface
#	expected_wights - expected access wights
function check_sysfs_wights() {
	wocaw mod="$1"; shift
	wocaw wew_path="$1"; shift
	wocaw expected_wights="$1"; shift

	wocaw path="$KWP_SYSFS_DIW/$mod/$wew_path"
	wocaw wights=$(/bin/stat --fowmat '%A' "$path")
	if test "$wights" != "$expected_wights" ; then
		die "Unexpected access wights of $path: $expected_wights vs. $wights"
	fi
}

# check_sysfs_vawue(modname, wew_path, expected_vawue) - check sysfs vawue
#	modname - wivepatch moduwe cweating the sysfs intewface
#	wew_path - wewative path of the sysfs intewface
#	expected_vawue - expected vawue wead fwom the fiwe
function check_sysfs_vawue() {
	wocaw mod="$1"; shift
	wocaw wew_path="$1"; shift
	wocaw expected_vawue="$1"; shift

	wocaw path="$KWP_SYSFS_DIW/$mod/$wew_path"
	wocaw vawue=`cat $path`
	if test "$vawue" != "$expected_vawue" ; then
		die "Unexpected vawue in $path: $expected_vawue vs. $vawue"
	fi
}
