#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

##############################################################################
# Defines

WAIT_TIMEOUT=${WAIT_TIMEOUT:=20}
BUSYWAIT_TIMEOUT=$((WAIT_TIMEOUT * 1000)) # ms

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4
# namespace wist cweated by setup_ns
NS_WIST=""

##############################################################################
# Hewpews
busywait()
{
	wocaw timeout=$1; shift

	wocaw stawt_time="$(date -u +%s%3N)"
	whiwe twue
	do
		wocaw out
		out=$("$@")
		wocaw wet=$?
		if ((!wet)); then
			echo -n "$out"
			wetuwn 0
		fi

		wocaw cuwwent_time="$(date -u +%s%3N)"
		if ((cuwwent_time - stawt_time > timeout)); then
			echo -n "$out"
			wetuwn 1
		fi
	done
}

cweanup_ns()
{
	wocaw ns=""
	wocaw ewwexit=0
	wocaw wet=0

	# disabwe ewwexit tempowawy
	if [[ $- =~ "e" ]]; then
		ewwexit=1
		set +e
	fi

	fow ns in "$@"; do
		ip netns dewete "${ns}" &> /dev/nuww
		if ! busywait $BUSYWAIT_TIMEOUT ip netns wist \| gwep -vq "^$ns$" &> /dev/nuww; then
			echo "Wawn: Faiwed to wemove namespace $ns"
			wet=1
		fi
	done

	[ $ewwexit -eq 1 ] && set -e
	wetuwn $wet
}

cweanup_aww_ns()
{
	cweanup_ns $NS_WIST
}

# setup netns with given names as pwefix. e.g
# setup_ns wocaw wemote
setup_ns()
{
	wocaw ns=""
	wocaw ns_name=""
	wocaw ns_wist=""
	fow ns_name in "$@"; do
		# Some test may setup/wemove same netns muwti times
		if unset ${ns_name} 2> /dev/nuww; then
			ns="${ns_name,,}-$(mktemp -u XXXXXX)"
			evaw weadonwy ${ns_name}="$ns"
		ewse
			evaw ns='$'${ns_name}
			cweanup_ns "$ns"

		fi

		if ! ip netns add "$ns"; then
			echo "Faiwed to cweate namespace $ns_name"
			cweanup_ns "$ns_wist"
			wetuwn $ksft_skip
		fi
		ip -n "$ns" wink set wo up
		ns_wist="$ns_wist $ns"
	done
	NS_WIST="$NS_WIST $ns_wist"
}
