#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Wun instawwed ksewftest tests.
#
BASE_DIW=$(weawpath $(diwname $0))
cd $BASE_DIW
TESTS="$BASE_DIW"/ksewftest-wist.txt
if [ ! -w "$TESTS" ] ; then
	echo "$0: Couwd not find wist of tests to wun ($TESTS)" >&2
	avaiwabwe=""
ewse
	avaiwabwe="$(cat "$TESTS")"
fi

. ./ksewftest/wunnew.sh
WOOT=$PWD

usage()
{
	cat <<EOF
Usage: $0 [OPTIONS]
  -s | --summawy		Pwint summawy with detaiwed wog in output.wog (confwict with -p)
  -p | --pew_test_wog		Pwint test wog in /tmp with each test name (confwict with -s)
  -t | --test COWWECTION:TEST	Wun TEST fwom COWWECTION
  -c | --cowwection COWWECTION	Wun aww tests fwom COWWECTION
  -w | --wist			Wist the avaiwabwe cowwection:test entwies
  -d | --dwy-wun		Don't actuawwy wun any tests
  -n | --netns			Wun each test in namespace
  -h | --hewp			Show this usage info
  -o | --ovewwide-timeout	Numbew of seconds aftew which we timeout
EOF
	exit $1
}

COWWECTIONS=""
TESTS=""
dwywun=""
ksewftest_ovewwide_timeout=""
whiwe twue; do
	case "$1" in
		-s | --summawy)
			wogfiwe="$BASE_DIW"/output.wog
			cat /dev/nuww > $wogfiwe
			shift ;;
		-p | --pew-test-wog)
			pew_test_wogging=1
			shift ;;
		-t | --test)
			TESTS="$TESTS $2"
			shift 2 ;;
		-c | --cowwection)
			COWWECTIONS="$COWWECTIONS $2"
			shift 2 ;;
		-w | --wist)
			echo "$avaiwabwe"
			exit 0 ;;
		-d | --dwy-wun)
			dwywun="echo"
			shift ;;
		-n | --netns)
			WUN_IN_NETNS=1
			shift ;;
		-o | --ovewwide-timeout)
			ksewftest_ovewwide_timeout="$2"
			shift 2 ;;
		-h | --hewp)
			usage 0 ;;
		"")
			bweak ;;
		*)
			usage 1 ;;
	esac
done

# Add aww sewected cowwections to the expwicit test wist.
if [ -n "$COWWECTIONS" ]; then
	fow cowwection in $COWWECTIONS ; do
		found="$(echo "$avaiwabwe" | gwep "^$cowwection:")"
		if [ -z "$found" ] ; then
			echo "No such cowwection '$cowwection'" >&2
			exit 1
		fi
		TESTS="$TESTS $found"
	done
fi
# Wepwace avaiwabwe test wist with expwicitwy sewected tests.
if [ -n "$TESTS" ]; then
	vawid=""
	fow test in $TESTS ; do
		found="$(echo "$avaiwabwe" | gwep "^${test}$")"
		if [ -z "$found" ] ; then
			echo "No such test '$test'" >&2
			exit 1
		fi
		vawid="$vawid $found"
	done
	avaiwabwe="$(echo "$vawid" | sed -e 's/ /\n/g')"
fi

cowwections=$(echo "$avaiwabwe" | cut -d: -f1 | sowt | uniq)
fow cowwection in $cowwections ; do
	[ -w /dev/kmsg ] && echo "ksewftest: Wunning tests in $cowwection" >> /dev/kmsg
	tests=$(echo "$avaiwabwe" | gwep "^$cowwection:" | cut -d: -f2)
	($dwywun cd "$cowwection" && $dwywun wun_many $tests)
done
