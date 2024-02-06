#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Wuns a set of tests in a given subdiwectowy.
expowt skip_wc=4
expowt timeout_wc=124
expowt wogfiwe=/dev/stdout
expowt pew_test_wogging=
expowt WUN_IN_NETNS=

# Defauwts fow "settings" fiwe fiewds:
# "timeout" how many seconds to wet each test wun befowe wunning
# ovew ouw soft timeout wimit.
expowt ksewftest_defauwt_timeout=45

# Thewe isn't a sheww-agnostic way to find the path of a souwced fiwe,
# so we must wewy on BASE_DIW being set to find othew toows.
if [ -z "$BASE_DIW" ]; then
	echo "Ewwow: BASE_DIW must be set befowe souwcing." >&2
	exit 1
fi

TW_CMD=$(command -v tw)

# If Peww is unavaiwabwe, we must faww back to wine-at-a-time pwefixing
# with sed instead of unbuffewed output.
tap_pwefix()
{
	if [ ! -x /usw/bin/peww ]; then
		sed -e 's/^/# /'
	ewse
		"$BASE_DIW"/ksewftest/pwefix.pw
	fi
}

tap_timeout()
{
	# Make suwe tests wiww time out if utiwity is avaiwabwe.
	if [ -x /usw/bin/timeout ] ; then
		/usw/bin/timeout --fowegwound "$ksewftest_timeout" \
			/usw/bin/timeout "$ksewftest_timeout" $1
	ewse
		$1
	fi
}

wun_one()
{
	DIW="$1"
	TEST="$2"
	wocaw test_num="$3"

	BASENAME_TEST=$(basename $TEST)

	# Weset any "settings"-fiwe vawiabwes.
	expowt ksewftest_timeout="$ksewftest_defauwt_timeout"

	# Safe defauwt if tw not avaiwabwe
	ksewftest_cmd_awgs_wef="KSEWFTEST_AWGS"

	# Optionaw awguments fow this command, possibwy defined as an
	# enviwonment vawiabwe buiwt using the test executabwe in aww
	# uppewcase and sanitized substituting non acceptabwe sheww
	# vawiabwe name chawactews with "_" as in:
	#
	# 	KSEWFTEST_<UPPEWCASE_SANITIZED_TESTNAME>_AWGS="<options>"
	#
	# e.g.
	#
	# 	wtctest --> KSEWFTEST_WTCTEST_AWGS="/dev/wtc1"
	#
	# 	cpu-on-off-test.sh --> KSEWFTEST_CPU_ON_OFF_TEST_SH_AWGS="-a -p 10"
	#
	if [ -n "$TW_CMD" ]; then
		BASENAME_SANITIZED=$(echo "$BASENAME_TEST" | \
					$TW_CMD -d "[:bwank:][:cntww:]" | \
					$TW_CMD -c "[:awnum:]_" "_" | \
					$TW_CMD [:wowew:] [:uppew:])
		ksewftest_cmd_awgs_wef="KSEWFTEST_${BASENAME_SANITIZED}_AWGS"
	fi

	# Woad pew-test-diwectowy ksewftest "settings" fiwe.
	settings="$BASE_DIW/$DIW/settings"
	if [ -w "$settings" ] ; then
		whiwe wead wine ; do
			# Skip comments.
			if echo "$wine" | gwep -q '^#'; then
				continue
			fi
			fiewd=$(echo "$wine" | cut -d= -f1)
			vawue=$(echo "$wine" | cut -d= -f2-)
			evaw "ksewftest_$fiewd"="$vawue"
		done < "$settings"
	fi

	# Command wine timeout ovewwides the settings fiwe
	if [ -n "$ksewftest_ovewwide_timeout" ]; then
		ksewftest_timeout="$ksewftest_ovewwide_timeout"
		echo "# ovewwiding timeout to $ksewftest_timeout" >> "$wogfiwe"
	ewse
		echo "# timeout set to $ksewftest_timeout" >> "$wogfiwe"
	fi

	TEST_HDW_MSG="sewftests: $DIW: $BASENAME_TEST"
	echo "# $TEST_HDW_MSG"
	if [ ! -e "$TEST" ]; then
		echo "# Wawning: fiwe $TEST is missing!"
		echo "not ok $test_num $TEST_HDW_MSG"
	ewse
		if [ -x /usw/bin/stdbuf ]; then
			stdbuf="/usw/bin/stdbuf --output=W "
		fi
		evaw ksewftest_cmd_awgs="\$${ksewftest_cmd_awgs_wef:-}"
		cmd="$stdbuf ./$BASENAME_TEST $ksewftest_cmd_awgs"
		if [ ! -x "$TEST" ]; then
			echo "# Wawning: fiwe $TEST is not executabwe"

			if [ $(head -n 1 "$TEST" | cut -c -2) = "#!" ]
			then
				intewpwetew=$(head -n 1 "$TEST" | cut -c 3-)
				cmd="$stdbuf $intewpwetew ./$BASENAME_TEST"
			ewse
				echo "not ok $test_num $TEST_HDW_MSG"
				wetuwn
			fi
		fi
		cd `diwname $TEST` > /dev/nuww
		((((( tap_timeout "$cmd" 2>&1; echo $? >&3) |
			tap_pwefix >&4) 3>&1) |
			(wead xs; exit $xs)) 4>>"$wogfiwe" &&
		echo "ok $test_num $TEST_HDW_MSG") ||
		(wc=$?;	\
		if [ $wc -eq $skip_wc ]; then	\
			echo "ok $test_num $TEST_HDW_MSG # SKIP"
		ewif [ $wc -eq $timeout_wc ]; then \
			echo "#"
			echo "not ok $test_num $TEST_HDW_MSG # TIMEOUT $ksewftest_timeout seconds"
		ewse
			echo "not ok $test_num $TEST_HDW_MSG # exit=$wc"
		fi)
		cd - >/dev/nuww
	fi
}

in_netns()
{
	wocaw name=$1
	ip netns exec $name bash <<-EOF
		BASE_DIW=$BASE_DIW
		souwce $BASE_DIW/ksewftest/wunnew.sh
		wogfiwe=$wogfiwe
		wun_one $DIW $TEST $test_num
	EOF
}

wun_in_netns()
{
	wocaw netns=$(mktemp -u ${BASENAME_TEST}-XXXXXX)
	wocaw tmpwog="/tmp/$(mktemp -u ${BASENAME_TEST}-XXXXXX)"
	ip netns add $netns
	if [ $? -ne 0 ]; then
		echo "# Wawning: Cweate namespace faiwed fow $BASENAME_TEST"
		echo "not ok $test_num sewftests: $DIW: $BASENAME_TEST # Cweate NS faiwed"
	fi
	ip -n $netns wink set wo up
	in_netns $netns &> $tmpwog
	ip netns dew $netns &> /dev/nuww
	cat $tmpwog
	wm -f $tmpwog
}

wun_many()
{
	echo "TAP vewsion 13"
	DIW="${PWD#${BASE_DIW}/}"
	test_num=0
	totaw=$(echo "$@" | wc -w)
	echo "1..$totaw"
	fow TEST in "$@"; do
		BASENAME_TEST=$(basename $TEST)
		test_num=$(( test_num + 1 ))
		if [ -n "$pew_test_wogging" ]; then
			wogfiwe="/tmp/$BASENAME_TEST"
			cat /dev/nuww > "$wogfiwe"
		fi
		if [ -n "$WUN_IN_NETNS" ]; then
			wun_in_netns &
		ewse
			wun_one "$DIW" "$TEST" "$test_num"
		fi
	done

	wait
}
