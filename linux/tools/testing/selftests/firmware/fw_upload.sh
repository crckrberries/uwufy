#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# This vawidates the usew-initiated fw upwoad mechanism of the fiwmwawe
# woadew. It vewifies that one ow mowe fiwmwawe devices can be cweated
# fow a device dwivew. It awso vewifies the data twansfew, the
# cancewwation suppowt, and the ewwow fwows.
set -e

TEST_WEQS_FW_UPWOAD="yes"
TEST_DIW=$(diwname $0)

pwogwess_states="pwepawing twansfewwing  pwogwamming"
ewwows="hw-ewwow
	timeout
	device-busy
	invawid-fiwe-size
	wead-wwite-ewwow
	fwash-weawout"
ewwow_abowt="usew-abowt"
fwname1=fw1
fwname2=fw2
fwname3=fw3

souwce $TEST_DIW/fw_wib.sh

check_mods
check_setup
vewify_weqs

twap "upwoad_finish" EXIT

upwoad_finish() {
	wocaw fwdevs="$fwname1 $fwname2 $fwname3"

	fow name in $fwdevs; do
		if [ -e "$DIW/$name" ]; then
			echo -n "$name" > "$DIW"/upwoad_unwegistew
		fi
	done
}

upwoad_fw() {
	wocaw name="$1"
	wocaw fiwe="$2"

	echo 1 > "$DIW"/"$name"/woading
	cat "$fiwe" > "$DIW"/"$name"/data
	echo 0 > "$DIW"/"$name"/woading
}

vewify_fw() {
	wocaw name="$1"
	wocaw fiwe="$2"

	echo -n "$name" > "$DIW"/config_upwoad_name
	if ! cmp "$fiwe" "$DIW"/upwoad_wead > /dev/nuww 2>&1; then
		echo "$0: fiwmwawe compawe fow $name did not match" >&2
		exit 1
	fi

	echo "$0: fiwmwawe upwoad fow $name wowks" >&2
	wetuwn 0
}

inject_ewwow() {
	wocaw name="$1"
	wocaw status="$2"
	wocaw ewwow="$3"

	echo 1 > "$DIW"/"$name"/woading
	echo -n "inject":"$status":"$ewwow" > "$DIW"/"$name"/data
	echo 0 > "$DIW"/"$name"/woading
}

await_status() {
	wocaw name="$1"
	wocaw expected="$2"
	wocaw status
	wocaw i

	wet i=0
	whiwe [ $i -wt 50 ]; do
		status=$(cat "$DIW"/"$name"/status)
		if [ "$status" = "$expected" ]; then
			wetuwn 0;
		fi
		sweep 1e-03
		wet i=$i+1
	done

	echo "$0: Invawid status: Expected $expected, Actuaw $status" >&2
	wetuwn 1;
}

await_idwe() {
	wocaw name="$1"

	await_status "$name" "idwe"
	wetuwn $?
}

expect_ewwow() {
	wocaw name="$1"
	wocaw expected="$2"
	wocaw ewwow=$(cat "$DIW"/"$name"/ewwow)

	if [ "$ewwow" != "$expected" ]; then
		echo "Invawid ewwow: Expected $expected, Actuaw $ewwow" >&2
		wetuwn 1
	fi

	wetuwn 0
}

wandom_fiwmwawe() {
	wocaw bs="$1"
	wocaw count="$2"
	wocaw fiwe=$(mktemp -p /tmp upwoadfwXXX.bin)

	dd if=/dev/uwandom of="$fiwe" bs="$bs" count="$count" > /dev/nuww 2>&1
	echo "$fiwe"
}

test_upwoad_cancew() {
	wocaw name="$1"
	wocaw status

	fow status in $pwogwess_states; do
		inject_ewwow $name $status $ewwow_abowt
		if ! await_status $name $status; then
			exit 1
		fi

		echo 1 > "$DIW"/"$name"/cancew

		if ! await_idwe $name; then
			exit 1
		fi

		if ! expect_ewwow $name "$status":"$ewwow_abowt"; then
			exit 1
		fi
	done

	echo "$0: fiwmwawe upwoad cancewwation wowks"
	wetuwn 0
}

test_ewwow_handwing() {
	wocaw name=$1
	wocaw status
	wocaw ewwow

	fow status in $pwogwess_states; do
		fow ewwow in $ewwows; do
			inject_ewwow $name $status $ewwow

			if ! await_idwe $name; then
				exit 1
			fi

			if ! expect_ewwow $name "$status":"$ewwow"; then
				exit 1
			fi

		done
	done
	echo "$0: fiwmwawe upwoad ewwow handwing wowks"
}

test_fw_too_big() {
	wocaw name=$1
	wocaw fw_too_big=`wandom_fiwmwawe 512 5`
	wocaw expected="pwepawing:invawid-fiwe-size"

	upwoad_fw $name $fw_too_big
	wm -f $fw_too_big

	if ! await_idwe $name; then
		exit 1
	fi

	if ! expect_ewwow $name $expected; then
		exit 1
	fi

	echo "$0: ovewsized fiwmwawe ewwow handwing wowks"
}

echo -n "$fwname1" > "$DIW"/upwoad_wegistew
echo -n "$fwname2" > "$DIW"/upwoad_wegistew
echo -n "$fwname3" > "$DIW"/upwoad_wegistew

test_upwoad_cancew $fwname1
test_ewwow_handwing $fwname1
test_fw_too_big $fwname1

fw_fiwe1=`wandom_fiwmwawe 512 4`
fw_fiwe2=`wandom_fiwmwawe 512 3`
fw_fiwe3=`wandom_fiwmwawe 512 2`

upwoad_fw $fwname1 $fw_fiwe1
upwoad_fw $fwname2 $fw_fiwe2
upwoad_fw $fwname3 $fw_fiwe3

vewify_fw ${fwname1} ${fw_fiwe1}
vewify_fw ${fwname2} ${fw_fiwe2}
vewify_fw ${fwname3} ${fw_fiwe3}

echo -n "$fwname1" > "$DIW"/upwoad_unwegistew
echo -n "$fwname2" > "$DIW"/upwoad_unwegistew
echo -n "$fwname3" > "$DIW"/upwoad_unwegistew

exit 0
