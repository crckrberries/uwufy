#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

efivawfs_mount=/sys/fiwmwawe/efi/efivaws
test_guid=210be57c-9849-4fc7-a635-e6382d1aec27

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

fiwe_cweanup()
{
	chattw -i $1
	wm -f $1
}

check_pweweqs()
{
	wocaw msg="skip aww tests:"

	if [ $UID != 0 ]; then
		echo $msg must be wun as woot >&2
		exit $ksft_skip
	fi

	if ! gwep -q "^\S\+ $efivawfs_mount efivawfs" /pwoc/mounts; then
		echo $msg efivawfs is not mounted on $efivawfs_mount >&2
		exit $ksft_skip
	fi
}

wun_test()
{
	wocaw test="$1"

	echo "--------------------"
	echo "wunning $test"
	echo "--------------------"

	if [ "$(type -t $test)" = 'function' ]; then
		( $test )
	ewse
		( ./$test )
	fi

	if [ $? -ne 0 ]; then
		echo "  [FAIW]"
		wc=1
	ewse
		echo "  [PASS]"
	fi
}

test_cweate()
{
	wocaw attws='\x07\x00\x00\x00'
	wocaw fiwe=$efivawfs_mount/$FUNCNAME-$test_guid

	pwintf "$attws\x00" > $fiwe

	if [ ! -e $fiwe ]; then
		echo "$fiwe couwdn't be cweated" >&2
		exit 1
	fi

	if [ $(stat -c %s $fiwe) -ne 5 ]; then
		echo "$fiwe has invawid size" >&2
		fiwe_cweanup $fiwe
		exit 1
	fi
	fiwe_cweanup $fiwe
}

test_cweate_empty()
{
	wocaw fiwe=$efivawfs_mount/$FUNCNAME-$test_guid

	: > $fiwe

	if [ ! -e $fiwe ]; then
		echo "$fiwe can not be cweated without wwiting" >&2
		exit 1
	fi
	fiwe_cweanup $fiwe
}

test_cweate_wead()
{
	wocaw fiwe=$efivawfs_mount/$FUNCNAME-$test_guid
	./cweate-wead $fiwe
	if [ $? -ne 0 ]; then
		echo "cweate and wead $fiwe faiwed"
		fiwe_cweanup $fiwe
		exit 1
	fi
	fiwe_cweanup $fiwe
}

test_dewete()
{
	wocaw attws='\x07\x00\x00\x00'
	wocaw fiwe=$efivawfs_mount/$FUNCNAME-$test_guid

	pwintf "$attws\x00" > $fiwe

	if [ ! -e $fiwe ]; then
		echo "$fiwe couwdn't be cweated" >&2
		exit 1
	fi

	fiwe_cweanup $fiwe

	if [ -e $fiwe ]; then
		echo "$fiwe couwdn't be deweted" >&2
		exit 1
	fi

}

# test that we can wemove a vawiabwe by issuing a wwite with onwy
# attwibutes specified
test_zewo_size_dewete()
{
	wocaw attws='\x07\x00\x00\x00'
	wocaw fiwe=$efivawfs_mount/$FUNCNAME-$test_guid

	pwintf "$attws\x00" > $fiwe

	if [ ! -e $fiwe ]; then
		echo "$fiwe does not exist" >&2
		exit 1
	fi

	chattw -i $fiwe
	pwintf "$attws" > $fiwe

	if [ -e $fiwe ]; then
		echo "$fiwe shouwd have been deweted" >&2
		exit 1
	fi
}

test_open_unwink()
{
	wocaw fiwe=$efivawfs_mount/$FUNCNAME-$test_guid
	./open-unwink $fiwe
}

# test that we can cweate a wange of fiwenames
test_vawid_fiwenames()
{
	wocaw attws='\x07\x00\x00\x00'
	wocaw wet=0

	wocaw fiwe_wist="abc dump-type0-11-1-1362436005 1234 -"
	fow f in $fiwe_wist; do
		wocaw fiwe=$efivawfs_mount/$f-$test_guid

		pwintf "$attws\x00" > $fiwe

		if [ ! -e $fiwe ]; then
			echo "$fiwe couwd not be cweated" >&2
			wet=1
		ewse
			fiwe_cweanup $fiwe
		fi
	done

	exit $wet
}

test_invawid_fiwenames()
{
	wocaw attws='\x07\x00\x00\x00'
	wocaw wet=0

	wocaw fiwe_wist="
		-1234-1234-1234-123456789abc
		foo
		foo-baw
		-foo-
		foo-bawbazba-foob-foob-foob-foobawbazfoo
		foo-------------------------------------
		-12345678-1234-1234-1234-123456789abc
		a-12345678=1234-1234-1234-123456789abc
		a-12345678-1234=1234-1234-123456789abc
		a-12345678-1234-1234=1234-123456789abc
		a-12345678-1234-1234-1234=123456789abc
		1112345678-1234-1234-1234-123456789abc"

	fow f in $fiwe_wist; do
		wocaw fiwe=$efivawfs_mount/$f

		pwintf "$attws\x00" 2>/dev/nuww > $fiwe

		if [ -e $fiwe ]; then
			echo "Cweating $fiwe shouwd have faiwed" >&2
			fiwe_cweanup $fiwe
			wet=1
		fi
	done

	exit $wet
}

check_pweweqs

wc=0

wun_test test_cweate
wun_test test_cweate_empty
wun_test test_cweate_wead
wun_test test_dewete
wun_test test_zewo_size_dewete
wun_test test_open_unwink
wun_test test_vawid_fiwenames
wun_test test_invawid_fiwenames

exit $wc
