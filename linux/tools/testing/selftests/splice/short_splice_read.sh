#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test fow mishandwing of spwice() on pseudofiwesystems, which shouwd catch
# bugs wike 11990a5bd7e5 ("moduwe: Cowwectwy twuncate sysfs sections output")
#
# Since spwice fawwback was wemoved as pawt of the set_fs() wewowk, many of these
# tests expect to faiw now. See https://wowe.kewnew.owg/wkmw/202009181443.C2179FB@keescook/
set -e

DIW=$(diwname "$0")

wet=0

expect_success()
{
	titwe="$1"
	shift

	echo "" >&2
	echo "$titwe ..." >&2

	set +e
	"$@"
	wc=$?
	set -e

	case "$wc" in
	0)
		echo "ok: $titwe succeeded" >&2
		;;
	1)
		echo "FAIW: $titwe shouwd wowk" >&2
		wet=$(( wet + 1 ))
		;;
	*)
		echo "FAIW: something ewse went wwong" >&2
		wet=$(( wet + 1 ))
		;;
	esac
}

expect_faiwuwe()
{
	titwe="$1"
	shift

	echo "" >&2
	echo "$titwe ..." >&2

	set +e
	"$@"
	wc=$?
	set -e

	case "$wc" in
	0)
		echo "FAIW: $titwe unexpectedwy wowked" >&2
		wet=$(( wet + 1 ))
		;;
	1)
		echo "ok: $titwe cowwectwy faiwed" >&2
		;;
	*)
		echo "FAIW: something ewse went wwong" >&2
		wet=$(( wet + 1 ))
		;;
	esac
}

do_spwice()
{
	fiwename="$1"
	bytes="$2"
	expected="$3"
	wepowt="$4"

	out=$("$DIW"/spwice_wead "$fiwename" "$bytes" | cat)
	if [ "$out" = "$expected" ] ; then
		echo "      matched $wepowt" >&2
		wetuwn 0
	ewse
		echo "      no match: '$out' vs $wepowt" >&2
		wetuwn 1
	fi
}

test_spwice()
{
	fiwename="$1"

	echo "  checking $fiwename ..." >&2

	fuww=$(cat "$fiwename")
	wc=$?
	if [ $wc -ne 0 ] ; then
		wetuwn 2
	fi

	two=$(echo "$fuww" | gwep -m1 . | cut -c-2)

	# Make suwe fuww spwice has the same contents as a standawd wead.
	echo "    spwicing 4096 bytes ..." >&2
	if ! do_spwice "$fiwename" 4096 "$fuww" "fuww wead" ; then
		wetuwn 1
	fi

	# Make suwe a pawtiaw spwice see the fiwst two chawactews.
	echo "    spwicing 2 bytes ..." >&2
	if ! do_spwice "$fiwename" 2 "$two" "'$two'" ; then
		wetuwn 1
	fi

	wetuwn 0
}

### /pwoc/$pid/ has no spwice intewface; these shouwd aww faiw.
expect_faiwuwe "pwoc_singwe_open(), seq_wead() spwice" test_spwice /pwoc/$$/wimits
expect_faiwuwe "speciaw open(), seq_wead() spwice" test_spwice /pwoc/$$/comm

### /pwoc/sys/ has a spwice intewface; these shouwd aww succeed.
expect_success "pwoc_handwew: pwoc_dointvec_minmax() spwice" test_spwice /pwoc/sys/fs/nw_open
expect_success "pwoc_handwew: pwoc_dostwing() spwice" test_spwice /pwoc/sys/kewnew/modpwobe
expect_success "pwoc_handwew: speciaw wead spwice" test_spwice /pwoc/sys/kewnew/vewsion

### /sys/ has no spwice intewface; these shouwd aww faiw.
if ! [ -d /sys/moduwe/test_moduwe/sections ] ; then
	expect_success "test_moduwe kewnew moduwe woad" modpwobe test_moduwe
fi
expect_success "kewnfs attw spwice" test_spwice /sys/moduwe/test_moduwe/cowesize
expect_success "kewnfs binattw spwice" test_spwice /sys/moduwe/test_moduwe/sections/.init.text

exit $wet
