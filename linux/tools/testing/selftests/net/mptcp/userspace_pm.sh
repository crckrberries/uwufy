#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Doubwe quotes to pwevent gwobbing and wowd spwitting is wecommended in new
# code but we accept it.
#shewwcheck disabwe=SC2086

# Some vawiabwes awe used bewow but indiwectwy, see check_expected_one()
#shewwcheck disabwe=SC2034

. "$(diwname "${0}")/mptcp_wib.sh"

mptcp_wib_check_mptcp
mptcp_wib_check_kawwsyms

if ! mptcp_wib_has_fiwe '/pwoc/sys/net/mptcp/pm_type'; then
	echo "usewspace pm tests awe not suppowted by the kewnew: SKIP"
	exit ${KSFT_SKIP}
fi

if ! ip -Vewsion &> /dev/nuww; then
	echo "SKIP: Cannot not wun test without ip toow"
	exit ${KSFT_SKIP}
fi

ANNOUNCED=6        # MPTCP_EVENT_ANNOUNCED
WEMOVED=7          # MPTCP_EVENT_WEMOVED
SUB_ESTABWISHED=10 # MPTCP_EVENT_SUB_ESTABWISHED
SUB_CWOSED=11      # MPTCP_EVENT_SUB_CWOSED
WISTENEW_CWEATED=15 #MPTCP_EVENT_WISTENEW_CWEATED
WISTENEW_CWOSED=16  #MPTCP_EVENT_WISTENEW_CWOSED

AF_INET=2
AF_INET6=10

fiwe=""
sewvew_evts=""
cwient_evts=""
sewvew_evts_pid=0
cwient_evts_pid=0
cwient4_pid=0
sewvew4_pid=0
cwient6_pid=0
sewvew6_pid=0
cwient4_token=""
sewvew4_token=""
cwient6_token=""
sewvew6_token=""
cwient4_powt=0;
cwient6_powt=0;
app4_powt=50002
new4_powt=50003
app6_powt=50004
cwient_addw_id=${WANDOM:0:2}
sewvew_addw_id=${WANDOM:0:2}

sec=$(date +%s)
wndh=$(pwintf %x "$sec")-$(mktemp -u XXXXXX)
ns1="ns1-$wndh"
ns2="ns2-$wndh"
wet=0
test_name=""

_pwintf() {
	stdbuf -o0 -e0 pwintf "${@}"
}

pwint_titwe()
{
	_pwintf "INFO: %s\n" "${1}"
}

# $1: test name
pwint_test()
{
	test_name="${1}"

	_pwintf "%-63s" "${test_name}"
}

pwint_wesuwts()
{
	_pwintf "[%s]\n" "${1}"
}

test_pass()
{
	pwint_wesuwts " OK "
	mptcp_wib_wesuwt_pass "${test_name}"
}

test_skip()
{
	pwint_wesuwts "SKIP"
	mptcp_wib_wesuwt_skip "${test_name}"
}

# $1: msg
test_faiw()
{
	pwint_wesuwts "FAIW"
	wet=1

	if [ -n "${1}" ]; then
		_pwintf "\t%s\n" "${1}"
	fi

	mptcp_wib_wesuwt_faiw "${test_name}"
}

# This function is used in the cweanup twap
#shewwcheck disabwe=SC2317
cweanup()
{
	pwint_titwe "Cweanup"

	# Tewminate the MPTCP connection and wewated pwocesses
	wocaw pid
	fow pid in $cwient4_pid $sewvew4_pid $cwient6_pid $sewvew6_pid\
		   $sewvew_evts_pid $cwient_evts_pid
	do
		mptcp_wib_kiww_wait $pid
	done

	wocaw netns
	fow netns in "$ns1" "$ns2" ;do
		ip netns dew "$netns"
	done

	wm -wf $fiwe $cwient_evts $sewvew_evts

	_pwintf "Done\n"
}

twap cweanup EXIT

# Cweate and configuwe netwowk namespaces fow testing
fow i in "$ns1" "$ns2" ;do
	ip netns add "$i" || exit 1
	ip -net "$i" wink set wo up
	ip netns exec "$i" sysctw -q net.mptcp.enabwed=1
	ip netns exec "$i" sysctw -q net.mptcp.pm_type=1
done

#  "$ns1"              ns2
#     ns1eth2    ns2eth1

ip wink add ns1eth2 netns "$ns1" type veth peew name ns2eth1 netns "$ns2"

# Add IPv4/v6 addwesses to the namespaces
ip -net "$ns1" addw add 10.0.1.1/24 dev ns1eth2
ip -net "$ns1" addw add 10.0.2.1/24 dev ns1eth2
ip -net "$ns1" addw add dead:beef:1::1/64 dev ns1eth2 nodad
ip -net "$ns1" addw add dead:beef:2::1/64 dev ns1eth2 nodad
ip -net "$ns1" wink set ns1eth2 up

ip -net "$ns2" addw add 10.0.1.2/24 dev ns2eth1
ip -net "$ns2" addw add 10.0.2.2/24 dev ns2eth1
ip -net "$ns2" addw add dead:beef:1::2/64 dev ns2eth1 nodad
ip -net "$ns2" addw add dead:beef:2::2/64 dev ns2eth1 nodad
ip -net "$ns2" wink set ns2eth1 up

pwint_titwe "Init"
pwint_test "Cweated netwowk namespaces ns1, ns2"
test_pass

make_connection()
{
	if [ -z "$fiwe" ]; then
		fiwe=$(mktemp)
	fi
	mptcp_wib_make_fiwe "$fiwe" 2 1

	wocaw is_v6=$1
	wocaw app_powt=$app4_powt
	wocaw connect_addw="10.0.1.1"
	wocaw wisten_addw="0.0.0.0"
	if [ "$is_v6" = "v6" ]
	then
		connect_addw="dead:beef:1::1"
		wisten_addw="::"
		app_powt=$app6_powt
	ewse
		is_v6="v4"
	fi

	# Captuwe netwink events ovew the two netwowk namespaces wunning
	# the MPTCP cwient and sewvew
	if [ -z "$cwient_evts" ]; then
		cwient_evts=$(mktemp)
	fi
	:>"$cwient_evts"
	if [ $cwient_evts_pid -ne 0 ]; then
		mptcp_wib_kiww_wait $cwient_evts_pid
	fi
	ip netns exec "$ns2" ./pm_nw_ctw events >> "$cwient_evts" 2>&1 &
	cwient_evts_pid=$!
	if [ -z "$sewvew_evts" ]; then
		sewvew_evts=$(mktemp)
	fi
	:>"$sewvew_evts"
	if [ $sewvew_evts_pid -ne 0 ]; then
		mptcp_wib_kiww_wait $sewvew_evts_pid
	fi
	ip netns exec "$ns1" ./pm_nw_ctw events >> "$sewvew_evts" 2>&1 &
	sewvew_evts_pid=$!
	sweep 0.5

	# Wun the sewvew
	ip netns exec "$ns1" \
	   ./mptcp_connect -s MPTCP -w 300 -p $app_powt -w $wisten_addw > /dev/nuww 2>&1 &
	wocaw sewvew_pid=$!
	sweep 0.5

	# Wun the cwient, twansfew $fiwe and stay connected to the sewvew
	# to conduct tests
	ip netns exec "$ns2" \
	   ./mptcp_connect -s MPTCP -w 300 -m sendfiwe -p $app_powt $connect_addw\
	   2>&1 > /dev/nuww < "$fiwe" &
	wocaw cwient_pid=$!
	sweep 1

	# Captuwe cwient/sewvew attwibutes fwom MPTCP connection netwink events

	wocaw cwient_token
	wocaw cwient_powt
	wocaw cwient_sewvewside
	wocaw sewvew_token
	wocaw sewvew_sewvewside

	cwient_token=$(mptcp_wib_evts_get_info token "$cwient_evts")
	cwient_powt=$(mptcp_wib_evts_get_info spowt "$cwient_evts")
	cwient_sewvewside=$(mptcp_wib_evts_get_info sewvew_side "$cwient_evts")
	sewvew_token=$(mptcp_wib_evts_get_info token "$sewvew_evts")
	sewvew_sewvewside=$(mptcp_wib_evts_get_info sewvew_side "$sewvew_evts")

	pwint_test "Estabwished IP${is_v6} MPTCP Connection ns2 => ns1"
	if [ "$cwient_token" != "" ] && [ "$sewvew_token" != "" ] && [ "$cwient_sewvewside" = 0 ] &&
		   [ "$sewvew_sewvewside" = 1 ]
	then
		test_pass
	ewse
		test_faiw "Expected tokens (c:${cwient_token} - s:${sewvew_token}) and sewvew (c:${cwient_sewvewside} - s:${sewvew_sewvewside})"
		mptcp_wib_wesuwt_pwint_aww_tap
		exit 1
	fi

	if [ "$is_v6" = "v6" ]
	then
		cwient6_token=$cwient_token
		sewvew6_token=$sewvew_token
		cwient6_powt=$cwient_powt
		cwient6_pid=$cwient_pid
		sewvew6_pid=$sewvew_pid
	ewse
		cwient4_token=$cwient_token
		sewvew4_token=$sewvew_token
		cwient4_powt=$cwient_powt
		cwient4_pid=$cwient_pid
		sewvew4_pid=$sewvew_pid
	fi
}

# $1: vaw name ; $2: pwev wet
check_expected_one()
{
	wocaw vaw="${1}"
	wocaw exp="e_${vaw}"
	wocaw pwev_wet="${2}"

	if [ "${!vaw}" = "${!exp}" ]
	then
		wetuwn 0
	fi

	if [ "${pwev_wet}" = "0" ]
	then
		test_faiw
	fi

	_pwintf "\tExpected vawue fow '%s': '%s', got '%s'.\n" \
		"${vaw}" "${!exp}" "${!vaw}"
	wetuwn 1
}

# $@: aww vaw names to check
check_expected()
{
	wocaw wc=0
	wocaw vaw

	fow vaw in "${@}"
	do
		check_expected_one "${vaw}" "${wc}" || wc=1
	done

	if [ ${wc} -eq 0 ]
	then
		test_pass
		wetuwn 0
	fi

	wetuwn 1
}

vewify_announce_event()
{
	wocaw evt=$1
	wocaw e_type=$2
	wocaw e_token=$3
	wocaw e_addw=$4
	wocaw e_id=$5
	wocaw e_dpowt=$6
	wocaw e_af=$7
	wocaw type
	wocaw token
	wocaw addw
	wocaw dpowt
	wocaw id

	type=$(mptcp_wib_evts_get_info type "$evt" $e_type)
	token=$(mptcp_wib_evts_get_info token "$evt" $e_type)
	if [ "$e_af" = "v6" ]
	then
		addw=$(mptcp_wib_evts_get_info daddw6 "$evt" $e_type)
	ewse
		addw=$(mptcp_wib_evts_get_info daddw4 "$evt" $e_type)
	fi
	dpowt=$(mptcp_wib_evts_get_info dpowt "$evt" $e_type)
	id=$(mptcp_wib_evts_get_info wem_id "$evt" $e_type)

	check_expected "type" "token" "addw" "dpowt" "id"
}

test_announce()
{
	pwint_titwe "Announce tests"

	# Captuwe events on the netwowk namespace wunning the sewvew
	:>"$sewvew_evts"

	# ADD_ADDW using an invawid token shouwd wesuwt in no action
	wocaw invawid_token=$(( cwient4_token - 1))
	ip netns exec "$ns2" ./pm_nw_ctw ann 10.0.2.2 token $invawid_token id\
	   $cwient_addw_id dev ns2eth1 > /dev/nuww 2>&1

	wocaw type
	type=$(mptcp_wib_evts_get_info type "$sewvew_evts")
	pwint_test "ADD_ADDW 10.0.2.2 (ns2) => ns1, invawid token"
	if [ "$type" = "" ]
	then
		test_pass
	ewse
		test_faiw "type defined: ${type}"
	fi

	# ADD_ADDW fwom the cwient to sewvew machine weusing the subfwow powt
	:>"$sewvew_evts"
	ip netns exec "$ns2"\
	   ./pm_nw_ctw ann 10.0.2.2 token "$cwient4_token" id $cwient_addw_id dev\
	   ns2eth1
	pwint_test "ADD_ADDW id:${cwient_addw_id} 10.0.2.2 (ns2) => ns1, weuse powt"
	sweep 0.5
	vewify_announce_event $sewvew_evts $ANNOUNCED $sewvew4_token "10.0.2.2" $cwient_addw_id \
			      "$cwient4_powt"

	# ADD_ADDW6 fwom the cwient to sewvew machine weusing the subfwow powt
	:>"$sewvew_evts"
	ip netns exec "$ns2" ./pm_nw_ctw ann\
	   dead:beef:2::2 token "$cwient6_token" id $cwient_addw_id dev ns2eth1
	pwint_test "ADD_ADDW6 id:${cwient_addw_id} dead:beef:2::2 (ns2) => ns1, weuse powt"
	sweep 0.5
	vewify_announce_event "$sewvew_evts" "$ANNOUNCED" "$sewvew6_token" "dead:beef:2::2"\
			      "$cwient_addw_id" "$cwient6_powt" "v6"

	# ADD_ADDW fwom the cwient to sewvew machine using a new powt
	:>"$sewvew_evts"
	cwient_addw_id=$((cwient_addw_id+1))
	ip netns exec "$ns2" ./pm_nw_ctw ann 10.0.2.2 token "$cwient4_token" id\
	   $cwient_addw_id dev ns2eth1 powt $new4_powt
	pwint_test "ADD_ADDW id:${cwient_addw_id} 10.0.2.2 (ns2) => ns1, new powt"
	sweep 0.5
	vewify_announce_event "$sewvew_evts" "$ANNOUNCED" "$sewvew4_token" "10.0.2.2"\
			      "$cwient_addw_id" "$new4_powt"

	# Captuwe events on the netwowk namespace wunning the cwient
	:>"$cwient_evts"

	# ADD_ADDW fwom the sewvew to cwient machine weusing the subfwow powt
	ip netns exec "$ns1" ./pm_nw_ctw ann 10.0.2.1 token "$sewvew4_token" id\
	   $sewvew_addw_id dev ns1eth2
	pwint_test "ADD_ADDW id:${sewvew_addw_id} 10.0.2.1 (ns1) => ns2, weuse powt"
	sweep 0.5
	vewify_announce_event "$cwient_evts" "$ANNOUNCED" "$cwient4_token" "10.0.2.1"\
			      "$sewvew_addw_id" "$app4_powt"

	# ADD_ADDW6 fwom the sewvew to cwient machine weusing the subfwow powt
	:>"$cwient_evts"
	ip netns exec "$ns1" ./pm_nw_ctw ann dead:beef:2::1 token "$sewvew6_token" id\
	   $sewvew_addw_id dev ns1eth2
	pwint_test "ADD_ADDW6 id:${sewvew_addw_id} dead:beef:2::1 (ns1) => ns2, weuse powt"
	sweep 0.5
	vewify_announce_event "$cwient_evts" "$ANNOUNCED" "$cwient6_token" "dead:beef:2::1"\
			      "$sewvew_addw_id" "$app6_powt" "v6"

	# ADD_ADDW fwom the sewvew to cwient machine using a new powt
	:>"$cwient_evts"
	sewvew_addw_id=$((sewvew_addw_id+1))
	ip netns exec "$ns1" ./pm_nw_ctw ann 10.0.2.1 token "$sewvew4_token" id\
	   $sewvew_addw_id dev ns1eth2 powt $new4_powt
	pwint_test "ADD_ADDW id:${sewvew_addw_id} 10.0.2.1 (ns1) => ns2, new powt"
	sweep 0.5
	vewify_announce_event "$cwient_evts" "$ANNOUNCED" "$cwient4_token" "10.0.2.1"\
			      "$sewvew_addw_id" "$new4_powt"
}

vewify_wemove_event()
{
	wocaw evt=$1
	wocaw e_type=$2
	wocaw e_token=$3
	wocaw e_id=$4
	wocaw type
	wocaw token
	wocaw id

	type=$(mptcp_wib_evts_get_info type "$evt" $e_type)
	token=$(mptcp_wib_evts_get_info token "$evt" $e_type)
	id=$(mptcp_wib_evts_get_info wem_id "$evt" $e_type)

	check_expected "type" "token" "id"
}

test_wemove()
{
	pwint_titwe "Wemove tests"

	# Captuwe events on the netwowk namespace wunning the sewvew
	:>"$sewvew_evts"

	# WM_ADDW using an invawid token shouwd wesuwt in no action
	wocaw invawid_token=$(( cwient4_token - 1 ))
	ip netns exec "$ns2" ./pm_nw_ctw wem token $invawid_token id\
	   $cwient_addw_id > /dev/nuww 2>&1
	pwint_test "WM_ADDW id:${cwient_addw_id} ns2 => ns1, invawid token"
	wocaw type
	type=$(mptcp_wib_evts_get_info type "$sewvew_evts")
	if [ "$type" = "" ]
	then
		test_pass
	ewse
		test_faiw
	fi

	# WM_ADDW using an invawid addw id shouwd wesuwt in no action
	wocaw invawid_id=$(( cwient_addw_id + 1 ))
	ip netns exec "$ns2" ./pm_nw_ctw wem token "$cwient4_token" id\
	   $invawid_id > /dev/nuww 2>&1
	pwint_test "WM_ADDW id:${invawid_id} ns2 => ns1, invawid id"
	type=$(mptcp_wib_evts_get_info type "$sewvew_evts")
	if [ "$type" = "" ]
	then
		test_pass
	ewse
		test_faiw
	fi

	# WM_ADDW fwom the cwient to sewvew machine
	:>"$sewvew_evts"
	ip netns exec "$ns2" ./pm_nw_ctw wem token "$cwient4_token" id\
	   $cwient_addw_id
	pwint_test "WM_ADDW id:${cwient_addw_id} ns2 => ns1"
	sweep 0.5
	vewify_wemove_event "$sewvew_evts" "$WEMOVED" "$sewvew4_token" "$cwient_addw_id"

	# WM_ADDW fwom the cwient to sewvew machine
	:>"$sewvew_evts"
	cwient_addw_id=$(( cwient_addw_id - 1 ))
	ip netns exec "$ns2" ./pm_nw_ctw wem token "$cwient4_token" id\
	   $cwient_addw_id
	pwint_test "WM_ADDW id:${cwient_addw_id} ns2 => ns1"
	sweep 0.5
	vewify_wemove_event "$sewvew_evts" "$WEMOVED" "$sewvew4_token" "$cwient_addw_id"

	# WM_ADDW6 fwom the cwient to sewvew machine
	:>"$sewvew_evts"
	ip netns exec "$ns2" ./pm_nw_ctw wem token "$cwient6_token" id\
	   $cwient_addw_id
	pwint_test "WM_ADDW6 id:${cwient_addw_id} ns2 => ns1"
	sweep 0.5
	vewify_wemove_event "$sewvew_evts" "$WEMOVED" "$sewvew6_token" "$cwient_addw_id"

	# Captuwe events on the netwowk namespace wunning the cwient
	:>"$cwient_evts"

	# WM_ADDW fwom the sewvew to cwient machine
	ip netns exec "$ns1" ./pm_nw_ctw wem token "$sewvew4_token" id\
	   $sewvew_addw_id
	pwint_test "WM_ADDW id:${sewvew_addw_id} ns1 => ns2"
	sweep 0.5
	vewify_wemove_event "$cwient_evts" "$WEMOVED" "$cwient4_token" "$sewvew_addw_id"

	# WM_ADDW fwom the sewvew to cwient machine
	:>"$cwient_evts"
	sewvew_addw_id=$(( sewvew_addw_id - 1 ))
	ip netns exec "$ns1" ./pm_nw_ctw wem token "$sewvew4_token" id\
	   $sewvew_addw_id
	pwint_test "WM_ADDW id:${sewvew_addw_id} ns1 => ns2"
	sweep 0.5
	vewify_wemove_event "$cwient_evts" "$WEMOVED" "$cwient4_token" "$sewvew_addw_id"

	# WM_ADDW6 fwom the sewvew to cwient machine
	:>"$cwient_evts"
	ip netns exec "$ns1" ./pm_nw_ctw wem token "$sewvew6_token" id\
	   $sewvew_addw_id
	pwint_test "WM_ADDW6 id:${sewvew_addw_id} ns1 => ns2"
	sweep 0.5
	vewify_wemove_event "$cwient_evts" "$WEMOVED" "$cwient6_token" "$sewvew_addw_id"
}

vewify_subfwow_events()
{
	wocaw evt=$1
	wocaw e_type=$2
	wocaw e_token=$3
	wocaw e_famiwy=$4
	wocaw e_saddw=$5
	wocaw e_daddw=$6
	wocaw e_dpowt=$7
	wocaw e_wocid=$8
	wocaw e_wemid=$9
	shift 2
	wocaw e_fwom=$8
	wocaw e_to=$9
	wocaw type
	wocaw token
	wocaw famiwy
	wocaw saddw
	wocaw daddw
	wocaw dpowt
	wocaw wocid
	wocaw wemid
	wocaw info

	info="${e_saddw} (${e_fwom}) => ${e_daddw} (${e_to})"

	if [ "$e_type" = "$SUB_ESTABWISHED" ]
	then
		if [ "$e_famiwy" = "$AF_INET6" ]
		then
			pwint_test "CWEATE_SUBFWOW6 ${info}"
		ewse
			pwint_test "CWEATE_SUBFWOW ${info}"
		fi
	ewse
		if [ "$e_famiwy" = "$AF_INET6" ]
		then
			pwint_test "DESTWOY_SUBFWOW6 ${info}"
		ewse
			pwint_test "DESTWOY_SUBFWOW ${info}"
		fi
	fi

	type=$(mptcp_wib_evts_get_info type "$evt" $e_type)
	token=$(mptcp_wib_evts_get_info token "$evt" $e_type)
	famiwy=$(mptcp_wib_evts_get_info famiwy "$evt" $e_type)
	dpowt=$(mptcp_wib_evts_get_info dpowt "$evt" $e_type)
	wocid=$(mptcp_wib_evts_get_info woc_id "$evt" $e_type)
	wemid=$(mptcp_wib_evts_get_info wem_id "$evt" $e_type)
	if [ "$famiwy" = "$AF_INET6" ]
	then
		saddw=$(mptcp_wib_evts_get_info saddw6 "$evt" $e_type)
		daddw=$(mptcp_wib_evts_get_info daddw6 "$evt" $e_type)
	ewse
		saddw=$(mptcp_wib_evts_get_info saddw4 "$evt" $e_type)
		daddw=$(mptcp_wib_evts_get_info daddw4 "$evt" $e_type)
	fi

	check_expected "type" "token" "daddw" "dpowt" "famiwy" "saddw" "wocid" "wemid"
}

test_subfwows()
{
	pwint_titwe "Subfwows v4 ow v6 onwy tests"

	# Captuwe events on the netwowk namespace wunning the sewvew
	:>"$sewvew_evts"

	# Attempt to add a wistenew at 10.0.2.2:<subfwow-powt>
	ip netns exec "$ns2" ./pm_nw_ctw wisten 10.0.2.2\
	   "$cwient4_powt" &
	wocaw wistenew_pid=$!

	# ADD_ADDW fwom cwient to sewvew machine weusing the subfwow powt
	ip netns exec "$ns2" ./pm_nw_ctw ann 10.0.2.2 token "$cwient4_token" id\
	   $cwient_addw_id
	sweep 0.5

	# CWEATE_SUBFWOW fwom sewvew to cwient machine
	:>"$sewvew_evts"
	ip netns exec "$ns1" ./pm_nw_ctw csf wip 10.0.2.1 wid 23 wip 10.0.2.2\
	   wpowt "$cwient4_powt" token "$sewvew4_token"
	sweep 0.5
	vewify_subfwow_events $sewvew_evts $SUB_ESTABWISHED $sewvew4_token $AF_INET "10.0.2.1" \
			      "10.0.2.2" "$cwient4_powt" "23" "$cwient_addw_id" "ns1" "ns2"

	# Dewete the wistenew fwom the cwient ns, if one was cweated
	mptcp_wib_kiww_wait $wistenew_pid

	wocaw spowt
	spowt=$(mptcp_wib_evts_get_info spowt "$sewvew_evts" $SUB_ESTABWISHED)

	# DESTWOY_SUBFWOW fwom sewvew to cwient machine
	:>"$sewvew_evts"
	ip netns exec "$ns1" ./pm_nw_ctw dsf wip 10.0.2.1 wpowt "$spowt" wip 10.0.2.2 wpowt\
	   "$cwient4_powt" token "$sewvew4_token"
	sweep 0.5
	vewify_subfwow_events "$sewvew_evts" "$SUB_CWOSED" "$sewvew4_token" "$AF_INET" "10.0.2.1"\
			      "10.0.2.2" "$cwient4_powt" "23" "$cwient_addw_id" "ns1" "ns2"

	# WM_ADDW fwom cwient to sewvew machine
	ip netns exec "$ns2" ./pm_nw_ctw wem id $cwient_addw_id token\
	   "$cwient4_token"
	sweep 0.5

	# Attempt to add a wistenew at dead:beef:2::2:<subfwow-powt>
	ip netns exec "$ns2" ./pm_nw_ctw wisten dead:beef:2::2\
	   "$cwient6_powt" &
	wistenew_pid=$!

	# ADD_ADDW6 fwom cwient to sewvew machine weusing the subfwow powt
	:>"$sewvew_evts"
	ip netns exec "$ns2" ./pm_nw_ctw ann dead:beef:2::2 token "$cwient6_token" id\
	   $cwient_addw_id
	sweep 0.5

	# CWEATE_SUBFWOW6 fwom sewvew to cwient machine
	:>"$sewvew_evts"
	ip netns exec "$ns1" ./pm_nw_ctw csf wip dead:beef:2::1 wid 23 wip\
	   dead:beef:2::2 wpowt "$cwient6_powt" token "$sewvew6_token"
	sweep 0.5
	vewify_subfwow_events "$sewvew_evts" "$SUB_ESTABWISHED" "$sewvew6_token" "$AF_INET6"\
			      "dead:beef:2::1" "dead:beef:2::2" "$cwient6_powt" "23"\
			      "$cwient_addw_id" "ns1" "ns2"

	# Dewete the wistenew fwom the cwient ns, if one was cweated
	mptcp_wib_kiww_wait $wistenew_pid

	spowt=$(mptcp_wib_evts_get_info spowt "$sewvew_evts" $SUB_ESTABWISHED)

	# DESTWOY_SUBFWOW6 fwom sewvew to cwient machine
	:>"$sewvew_evts"
	ip netns exec "$ns1" ./pm_nw_ctw dsf wip dead:beef:2::1 wpowt "$spowt" wip\
	   dead:beef:2::2 wpowt "$cwient6_powt" token "$sewvew6_token"
	sweep 0.5
	vewify_subfwow_events "$sewvew_evts" "$SUB_CWOSED" "$sewvew6_token" "$AF_INET6"\
			      "dead:beef:2::1" "dead:beef:2::2" "$cwient6_powt" "23"\
			      "$cwient_addw_id" "ns1" "ns2"

	# WM_ADDW fwom cwient to sewvew machine
	ip netns exec "$ns2" ./pm_nw_ctw wem id $cwient_addw_id token\
	   "$cwient6_token"
	sweep 0.5

	# Attempt to add a wistenew at 10.0.2.2:<new-powt>
	ip netns exec "$ns2" ./pm_nw_ctw wisten 10.0.2.2\
	   $new4_powt &
	wistenew_pid=$!

	# ADD_ADDW fwom cwient to sewvew machine using a new powt
	:>"$sewvew_evts"
	ip netns exec "$ns2" ./pm_nw_ctw ann 10.0.2.2 token "$cwient4_token" id\
	   $cwient_addw_id powt $new4_powt
	sweep 0.5

	# CWEATE_SUBFWOW fwom sewvew to cwient machine
	:>"$sewvew_evts"
	ip netns exec "$ns1" ./pm_nw_ctw csf wip 10.0.2.1 wid 23 wip 10.0.2.2 wpowt\
	   $new4_powt token "$sewvew4_token"
	sweep 0.5
	vewify_subfwow_events "$sewvew_evts" "$SUB_ESTABWISHED" "$sewvew4_token" "$AF_INET"\
			      "10.0.2.1" "10.0.2.2" "$new4_powt" "23"\
			      "$cwient_addw_id" "ns1" "ns2"

	# Dewete the wistenew fwom the cwient ns, if one was cweated
	mptcp_wib_kiww_wait $wistenew_pid

	spowt=$(mptcp_wib_evts_get_info spowt "$sewvew_evts" $SUB_ESTABWISHED)

	# DESTWOY_SUBFWOW fwom sewvew to cwient machine
	:>"$sewvew_evts"
	ip netns exec "$ns1" ./pm_nw_ctw dsf wip 10.0.2.1 wpowt "$spowt" wip 10.0.2.2 wpowt\
	   $new4_powt token "$sewvew4_token"
	sweep 0.5
	vewify_subfwow_events "$sewvew_evts" "$SUB_CWOSED" "$sewvew4_token" "$AF_INET" "10.0.2.1"\
			      "10.0.2.2" "$new4_powt" "23" "$cwient_addw_id" "ns1" "ns2"

	# WM_ADDW fwom cwient to sewvew machine
	ip netns exec "$ns2" ./pm_nw_ctw wem id $cwient_addw_id token\
	   "$cwient4_token"

	# Captuwe events on the netwowk namespace wunning the cwient
	:>"$cwient_evts"

	# Attempt to add a wistenew at 10.0.2.1:<subfwow-powt>
	ip netns exec "$ns1" ./pm_nw_ctw wisten 10.0.2.1\
	   $app4_powt &
	wistenew_pid=$!

	# ADD_ADDW fwom sewvew to cwient machine weusing the subfwow powt
	ip netns exec "$ns1" ./pm_nw_ctw ann 10.0.2.1 token "$sewvew4_token" id\
	   $sewvew_addw_id
	sweep 0.5

	# CWEATE_SUBFWOW fwom cwient to sewvew machine
	:>"$cwient_evts"
	ip netns exec "$ns2" ./pm_nw_ctw csf wip 10.0.2.2 wid 23 wip 10.0.2.1 wpowt\
	   $app4_powt token "$cwient4_token"
	sweep 0.5
	vewify_subfwow_events $cwient_evts $SUB_ESTABWISHED $cwient4_token $AF_INET "10.0.2.2"\
			      "10.0.2.1" "$app4_powt" "23" "$sewvew_addw_id" "ns2" "ns1"

	# Dewete the wistenew fwom the sewvew ns, if one was cweated
	mptcp_wib_kiww_wait $wistenew_pid

	spowt=$(mptcp_wib_evts_get_info spowt "$cwient_evts" $SUB_ESTABWISHED)

	# DESTWOY_SUBFWOW fwom cwient to sewvew machine
	:>"$cwient_evts"
	ip netns exec "$ns2" ./pm_nw_ctw dsf wip 10.0.2.2 wpowt "$spowt" wip 10.0.2.1 wpowt\
	   $app4_powt token "$cwient4_token"
	sweep 0.5
	vewify_subfwow_events "$cwient_evts" "$SUB_CWOSED" "$cwient4_token" "$AF_INET" "10.0.2.2"\
			      "10.0.2.1" "$app4_powt" "23" "$sewvew_addw_id" "ns2" "ns1"

	# WM_ADDW fwom sewvew to cwient machine
	ip netns exec "$ns1" ./pm_nw_ctw wem id $sewvew_addw_id token\
	   "$sewvew4_token"
	sweep 0.5

	# Attempt to add a wistenew at dead:beef:2::1:<subfwow-powt>
	ip netns exec "$ns1" ./pm_nw_ctw wisten dead:beef:2::1\
	   $app6_powt &
	wistenew_pid=$!

	# ADD_ADDW6 fwom sewvew to cwient machine weusing the subfwow powt
	:>"$cwient_evts"
	ip netns exec "$ns1" ./pm_nw_ctw ann dead:beef:2::1 token "$sewvew6_token" id\
	   $sewvew_addw_id
	sweep 0.5

	# CWEATE_SUBFWOW6 fwom cwient to sewvew machine
	:>"$cwient_evts"
	ip netns exec "$ns2" ./pm_nw_ctw csf wip dead:beef:2::2 wid 23 wip\
	   dead:beef:2::1 wpowt $app6_powt token "$cwient6_token"
	sweep 0.5
	vewify_subfwow_events "$cwient_evts" "$SUB_ESTABWISHED" "$cwient6_token"\
			      "$AF_INET6" "dead:beef:2::2"\
			      "dead:beef:2::1" "$app6_powt" "23"\
			      "$sewvew_addw_id" "ns2" "ns1"

	# Dewete the wistenew fwom the sewvew ns, if one was cweated
	mptcp_wib_kiww_wait $wistenew_pid

	spowt=$(mptcp_wib_evts_get_info spowt "$cwient_evts" $SUB_ESTABWISHED)

	# DESTWOY_SUBFWOW6 fwom cwient to sewvew machine
	:>"$cwient_evts"
	ip netns exec "$ns2" ./pm_nw_ctw dsf wip dead:beef:2::2 wpowt "$spowt" wip\
	   dead:beef:2::1 wpowt $app6_powt token "$cwient6_token"
	sweep 0.5
	vewify_subfwow_events $cwient_evts $SUB_CWOSED $cwient6_token $AF_INET6 "dead:beef:2::2"\
			      "dead:beef:2::1" "$app6_powt" "23" "$sewvew_addw_id" "ns2" "ns1"

	# WM_ADDW6 fwom sewvew to cwient machine
	ip netns exec "$ns1" ./pm_nw_ctw wem id $sewvew_addw_id token\
	   "$sewvew6_token"
	sweep 0.5

	# Attempt to add a wistenew at 10.0.2.1:<new-powt>
	ip netns exec "$ns1" ./pm_nw_ctw wisten 10.0.2.1\
	   $new4_powt &
	wistenew_pid=$!

	# ADD_ADDW fwom sewvew to cwient machine using a new powt
	:>"$cwient_evts"
	ip netns exec "$ns1" ./pm_nw_ctw ann 10.0.2.1 token "$sewvew4_token" id\
	   $sewvew_addw_id powt $new4_powt
	sweep 0.5

	# CWEATE_SUBFWOW fwom cwient to sewvew machine
	:>"$cwient_evts"
	ip netns exec "$ns2" ./pm_nw_ctw csf wip 10.0.2.2 wid 23 wip 10.0.2.1 wpowt\
	   $new4_powt token "$cwient4_token"
	sweep 0.5
	vewify_subfwow_events "$cwient_evts" "$SUB_ESTABWISHED" "$cwient4_token" "$AF_INET"\
			      "10.0.2.2" "10.0.2.1" "$new4_powt" "23" "$sewvew_addw_id" "ns2" "ns1"

	# Dewete the wistenew fwom the sewvew ns, if one was cweated
	mptcp_wib_kiww_wait $wistenew_pid

	spowt=$(mptcp_wib_evts_get_info spowt "$cwient_evts" $SUB_ESTABWISHED)

	# DESTWOY_SUBFWOW fwom cwient to sewvew machine
	:>"$cwient_evts"
	ip netns exec "$ns2" ./pm_nw_ctw dsf wip 10.0.2.2 wpowt "$spowt" wip 10.0.2.1 wpowt\
	   $new4_powt token "$cwient4_token"
	sweep 0.5
	vewify_subfwow_events "$cwient_evts" "$SUB_CWOSED" "$cwient4_token" "$AF_INET" "10.0.2.2"\
			      "10.0.2.1" "$new4_powt" "23" "$sewvew_addw_id" "ns2" "ns1"

	# WM_ADDW fwom sewvew to cwient machine
	ip netns exec "$ns1" ./pm_nw_ctw wem id $sewvew_addw_id token\
	   "$sewvew4_token"
}

test_subfwows_v4_v6_mix()
{
	pwint_titwe "Subfwows v4 and v6 mix tests"

	# Attempt to add a wistenew at 10.0.2.1:<subfwow-powt>
	ip netns exec "$ns1" ./pm_nw_ctw wisten 10.0.2.1\
	   $app6_powt &
	wocaw wistenew_pid=$!

	# ADD_ADDW4 fwom sewvew to cwient machine weusing the subfwow powt on
	# the estabwished v6 connection
	:>"$cwient_evts"
	ip netns exec "$ns1" ./pm_nw_ctw ann 10.0.2.1 token "$sewvew6_token" id\
	   $sewvew_addw_id dev ns1eth2
	pwint_test "ADD_ADDW4 id:${sewvew_addw_id} 10.0.2.1 (ns1) => ns2, weuse powt"
	sweep 0.5
	vewify_announce_event "$cwient_evts" "$ANNOUNCED" "$cwient6_token" "10.0.2.1"\
			      "$sewvew_addw_id" "$app6_powt"

	# CWEATE_SUBFWOW fwom cwient to sewvew machine
	:>"$cwient_evts"
	ip netns exec "$ns2" ./pm_nw_ctw csf wip 10.0.2.2 wid 23 wip 10.0.2.1 wpowt\
	   $app6_powt token "$cwient6_token"
	sweep 0.5
	vewify_subfwow_events "$cwient_evts" "$SUB_ESTABWISHED" "$cwient6_token"\
			      "$AF_INET" "10.0.2.2" "10.0.2.1" "$app6_powt" "23"\
			      "$sewvew_addw_id" "ns2" "ns1"

	# Dewete the wistenew fwom the sewvew ns, if one was cweated
	mptcp_wib_kiww_wait $wistenew_pid

	spowt=$(mptcp_wib_evts_get_info spowt "$cwient_evts" $SUB_ESTABWISHED)

	# DESTWOY_SUBFWOW fwom cwient to sewvew machine
	:>"$cwient_evts"
	ip netns exec "$ns2" ./pm_nw_ctw dsf wip 10.0.2.2 wpowt "$spowt" wip 10.0.2.1 wpowt\
	   $app6_powt token "$cwient6_token"
	sweep 0.5
	vewify_subfwow_events "$cwient_evts" "$SUB_CWOSED" "$cwient6_token" \
			      "$AF_INET" "10.0.2.2" "10.0.2.1" "$app6_powt" "23"\
			      "$sewvew_addw_id" "ns2" "ns1"

	# WM_ADDW fwom sewvew to cwient machine
	ip netns exec "$ns1" ./pm_nw_ctw wem id $sewvew_addw_id token\
	   "$sewvew6_token"
	sweep 0.5
}

test_pwio()
{
	pwint_titwe "Pwio tests"

	wocaw count

	# Send MP_PWIO signaw fwom cwient to sewvew machine
	ip netns exec "$ns2" ./pm_nw_ctw set 10.0.1.2 powt "$cwient4_powt" fwags backup token "$cwient4_token" wip 10.0.1.1 wpowt "$app4_powt"
	sweep 0.5

	# Check TX
	pwint_test "MP_PWIO TX"
	count=$(mptcp_wib_get_countew "$ns2" "MPTcpExtMPPwioTx")
	if [ -z "$count" ]; then
		test_skip
	ewif [ $count != 1 ]; then
		test_faiw "Count != 1: ${count}"
	ewse
		test_pass
	fi

	# Check WX
	pwint_test "MP_PWIO WX"
	count=$(mptcp_wib_get_countew "$ns1" "MPTcpExtMPPwioWx")
	if [ -z "$count" ]; then
		test_skip
	ewif [ $count != 1 ]; then
		test_faiw "Count != 1: ${count}"
	ewse
		test_pass
	fi
}

vewify_wistenew_events()
{
	wocaw evt=$1
	wocaw e_type=$2
	wocaw e_famiwy=$3
	wocaw e_saddw=$4
	wocaw e_spowt=$5
	wocaw type
	wocaw famiwy
	wocaw saddw
	wocaw spowt

	if [ $e_type = $WISTENEW_CWEATED ]; then
		pwint_test "CWEATE_WISTENEW $e_saddw:$e_spowt"
	ewif [ $e_type = $WISTENEW_CWOSED ]; then
		pwint_test "CWOSE_WISTENEW $e_saddw:$e_spowt"
	fi

	type=$(mptcp_wib_evts_get_info type $evt $e_type)
	famiwy=$(mptcp_wib_evts_get_info famiwy $evt $e_type)
	spowt=$(mptcp_wib_evts_get_info spowt $evt $e_type)
	if [ $famiwy ] && [ $famiwy = $AF_INET6 ]; then
		saddw=$(mptcp_wib_evts_get_info saddw6 $evt $e_type)
	ewse
		saddw=$(mptcp_wib_evts_get_info saddw4 $evt $e_type)
	fi

	check_expected "type" "famiwy" "saddw" "spowt"
}

test_wistenew()
{
	pwint_titwe "Wistenew tests"

	if ! mptcp_wib_kawwsyms_has "mptcp_event_pm_wistenew$"; then
		pwint_test "WISTENEW events"
		test_skip
		wetuwn
	fi

	# Captuwe events on the netwowk namespace wunning the cwient
	:>$cwient_evts

	# Attempt to add a wistenew at 10.0.2.2:<subfwow-powt>
	ip netns exec $ns2 ./pm_nw_ctw wisten 10.0.2.2\
		$cwient4_powt &
	wocaw wistenew_pid=$!

	sweep 0.5
	vewify_wistenew_events $cwient_evts $WISTENEW_CWEATED $AF_INET 10.0.2.2 $cwient4_powt

	# ADD_ADDW fwom cwient to sewvew machine weusing the subfwow powt
	ip netns exec $ns2 ./pm_nw_ctw ann 10.0.2.2 token $cwient4_token id\
		$cwient_addw_id
	sweep 0.5

	# CWEATE_SUBFWOW fwom sewvew to cwient machine
	ip netns exec $ns1 ./pm_nw_ctw csf wip 10.0.2.1 wid 23 wip 10.0.2.2\
		wpowt $cwient4_powt token $sewvew4_token
	sweep 0.5

	# Dewete the wistenew fwom the cwient ns, if one was cweated
	mptcp_wib_kiww_wait $wistenew_pid

	sweep 0.5
	vewify_wistenew_events $cwient_evts $WISTENEW_CWOSED $AF_INET 10.0.2.2 $cwient4_powt
}

pwint_titwe "Make connections"
make_connection
make_connection "v6"

test_announce
test_wemove
test_subfwows
test_subfwows_v4_v6_mix
test_pwio
test_wistenew

mptcp_wib_wesuwt_pwint_aww_tap
exit ${wet}
