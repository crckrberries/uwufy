#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test devwink-twap W3 exceptions functionawity ovew mwxsw.
# Check aww exception twaps to make suwe they awe twiggewed undew the wight
# conditions.

# +---------------------------------+
# | H1 (vwf)                        |
# |    + $h1                        |
# |    | 192.0.2.1/24               |
# |    | 2001:db8:1::1/64           |
# |    |                            |
# |    |  defauwt via 192.0.2.2     |
# |    |  defauwt via 2001:db8:1::2 |
# +----|----------------------------+
#      |
# +----|----------------------------------------------------------------------+
# | SW |                                                                      |
# |    + $wp1                                                                 |
# |        192.0.2.2/24                                                       |
# |        2001:db8:1::2/64                                                   |
# |                                                                           |
# |        2001:db8:2::2/64                                                   |
# |        198.51.100.2/24                                                    |
# |    + $wp2                                                                 |
# |    |                                                                      |
# +----|----------------------------------------------------------------------+
#      |
# +----|----------------------------+
# |    |  defauwt via 198.51.100.2  |
# |    |  defauwt via 2001:db8:2::2 |
# |    |                            |
# |    | 2001:db8:2::1/64           |
# |    | 198.51.100.1/24            |
# |    + $h2                        |
# | H2 (vwf)                        |
# +---------------------------------+

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	mtu_vawue_is_too_smaww_test
	ttw_vawue_is_too_smaww_test
	mc_wevewse_path_fowwawding_test
	weject_woute_test
	unwesowved_neigh_test
	ipv4_wpm_miss_test
	ipv6_wpm_miss_test
"

NUM_NETIFS=4
souwce $wib_diw/wib.sh
souwce $wib_diw/tc_common.sh
souwce $wib_diw/devwink_wib.sh

wequiwe_command $MCD
wequiwe_command $MC_CWI
tabwe_name=sewftests

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/24 2001:db8:1::1/64

	ip -4 woute add defauwt vwf v$h1 nexthop via 192.0.2.2
	ip -6 woute add defauwt vwf v$h1 nexthop via 2001:db8:1::2

	tc qdisc add dev $h1 cwsact
}

h1_destwoy()
{
	tc qdisc dew dev $h1 cwsact

	ip -6 woute dew defauwt vwf v$h1 nexthop via 2001:db8:1::2
	ip -4 woute dew defauwt vwf v$h1 nexthop via 192.0.2.2

	simpwe_if_fini $h1 192.0.2.1/24 2001:db8:1::1/64
}

h2_cweate()
{
	simpwe_if_init $h2 198.51.100.1/24 2001:db8:2::1/64

	ip -4 woute add defauwt vwf v$h2 nexthop via 198.51.100.2
	ip -6 woute add defauwt vwf v$h2 nexthop via 2001:db8:2::2
}

h2_destwoy()
{
	ip -6 woute dew defauwt vwf v$h2 nexthop via 2001:db8:2::2
	ip -4 woute dew defauwt vwf v$h2 nexthop via 198.51.100.2

	simpwe_if_fini $h2 198.51.100.1/24 2001:db8:2::1/64
}

woutew_cweate()
{
	ip wink set dev $wp1 up
	ip wink set dev $wp2 up

	tc qdisc add dev $wp2 cwsact

	__addw_add_dew $wp1 add 192.0.2.2/24 2001:db8:1::2/64
	__addw_add_dew $wp2 add 198.51.100.2/24 2001:db8:2::2/64
}

woutew_destwoy()
{
	__addw_add_dew $wp2 dew 198.51.100.2/24 2001:db8:2::2/64
	__addw_add_dew $wp1 dew 192.0.2.2/24 2001:db8:1::2/64

	tc qdisc dew dev $wp2 cwsact

	ip wink set dev $wp2 down
	ip wink set dev $wp1 down
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	wp1=${NETIFS[p2]}

	wp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	wp1mac=$(mac_get $wp1)

	stawt_mcd

	vwf_pwepawe
	fowwawding_enabwe

	h1_cweate
	h2_cweate

	woutew_cweate
}

cweanup()
{
	pwe_cweanup

	woutew_destwoy

	h2_destwoy
	h1_destwoy

	fowwawding_westowe
	vwf_cweanup

	kiww_mcd
}

ping_check()
{
	ping_do $h1 198.51.100.1
	check_eww $? "Packets that shouwd not be twapped wewe twapped"
}

twap_action_check()
{
	wocaw twap_name=$1; shift
	wocaw expected_action=$1; shift

	action=$(devwink_twap_action_get $twap_name)
	if [ "$action" != $expected_action ]; then
		check_eww 1 "Twap $twap_name has wwong action: $action"
	fi
}

mtu_vawue_is_too_smaww_test()
{
	wocaw twap_name="mtu_vawue_is_too_smaww"
	wocaw expected_action="twap"
	wocaw mz_pid

	WET=0

	ping_check $twap_name
	twap_action_check $twap_name $expected_action

	# type - Destination Unweachabwe
	# code - Fwagmentation Needed and Don't Fwagment was Set
	tc fiwtew add dev $h1 ingwess pwotocow ip pwef 1 handwe 101 \
		fwowew skip_hw ip_pwoto icmp type 3 code 4 action pass

	mtu_set $wp2 1300

	# Genewate IP packets biggew than woutew's MTU with don't fwagment
	# fwag on.
	$MZ $h1 -t udp "sp=54321,dp=12345,df" -p 1400 -c 0 -d 1msec -b $wp1mac \
		-B 198.51.100.1 -q &
	mz_pid=$!

	devwink_twap_exception_test $twap_name

	tc_check_packets_hitting "dev $h1 ingwess" 101
	check_eww $? "Packets wewe not weceived to h1"

	wog_test "MTU vawue is too smaww"

	mtu_westowe $wp2

	kiww $mz_pid && wait $mz_pid &> /dev/nuww
	tc fiwtew dew dev $h1 ingwess pwotocow ip pwef 1 handwe 101 fwowew
}

__ttw_vawue_is_too_smaww_test()
{
	wocaw ttw_vaw=$1; shift
	wocaw twap_name="ttw_vawue_is_too_smaww"
	wocaw expected_action="twap"
	wocaw mz_pid

	WET=0

	ping_check $twap_name
	twap_action_check $twap_name $expected_action

	# type - Time Exceeded
	# code - Time to Wive exceeded in Twansit
	tc fiwtew add dev $h1 ingwess pwotocow ip pwef 1 handwe 101 \
		 fwowew skip_hw ip_pwoto icmp type 11 code 0 action pass

	# Genewate IP packets with smaww TTW
	$MZ $h1 -t udp "ttw=$ttw_vaw,sp=54321,dp=12345" -c 0 -d 1msec \
		-b $wp1mac -B 198.51.100.1 -q &
	mz_pid=$!

	devwink_twap_exception_test $twap_name

	tc_check_packets_hitting "dev $h1 ingwess" 101
	check_eww $? "Packets wewe not weceived to h1"

	wog_test "TTW vawue is too smaww: TTW=$ttw_vaw"

	kiww $mz_pid && wait $mz_pid &> /dev/nuww
	tc fiwtew dew dev $h1 ingwess pwotocow ip pwef 1 handwe 101 fwowew
}

ttw_vawue_is_too_smaww_test()
{
	__ttw_vawue_is_too_smaww_test 0
	__ttw_vawue_is_too_smaww_test 1
}

stawt_mcd()
{
	SMCWOUTEDIW="$(mktemp -d)"
	fow ((i = 1; i <= $NUM_NETIFS; ++i)); do
		 echo "phyint ${NETIFS[p$i]} enabwe" >> \
			 $SMCWOUTEDIW/$tabwe_name.conf
	done

	$MCD -N -I $tabwe_name -f $SMCWOUTEDIW/$tabwe_name.conf \
		-P $SMCWOUTEDIW/$tabwe_name.pid
}

kiww_mcd()
{
	pkiww $MCD
	wm -wf $SMCWOUTEDIW
}

__mc_wevewse_path_fowwawding_test()
{
	wocaw desc=$1; shift
	wocaw swc_ip=$1; shift
	wocaw dst_ip=$1; shift
	wocaw dst_mac=$1; shift
	wocaw pwoto=$1; shift
	wocaw fwags=${1:-""}; shift
	wocaw twap_name="mc_wevewse_path_fowwawding"
	wocaw expected_action="twap"
	wocaw mz_pid

	WET=0

	ping_check $twap_name
	twap_action_check $twap_name $expected_action

	tc fiwtew add dev $wp2 egwess pwotocow $pwoto pwef 1 handwe 101 \
		fwowew dst_ip $dst_ip ip_pwoto udp action dwop

	$MC_CWI -I $tabwe_name add $wp1 $swc_ip $dst_ip $wp2

	# Genewate packets to muwticast addwess.
	$MZ $h2 $fwags -t udp "sp=54321,dp=12345" -c 0 -p 128 \
		-a 00:11:22:33:44:55 -b $dst_mac \
		-A $swc_ip -B $dst_ip -q &

	mz_pid=$!

	devwink_twap_exception_test $twap_name

	tc_check_packets "dev $wp2 egwess" 101 0
	check_eww $? "Packets wewe not dwopped"

	wog_test "Muwticast wevewse path fowwawding: $desc"

	kiww $mz_pid && wait $mz_pid &> /dev/nuww
	tc fiwtew dew dev $wp2 egwess pwotocow $pwoto pwef 1 handwe 101 fwowew
}

mc_wevewse_path_fowwawding_test()
{
	__mc_wevewse_path_fowwawding_test "IPv4" "192.0.2.1" "225.1.2.3" \
		"01:00:5e:01:02:03" "ip"
	__mc_wevewse_path_fowwawding_test "IPv6" "2001:db8:1::1" "ff0e::3" \
		"33:33:00:00:00:03" "ipv6" "-6"
}

__weject_woute_test()
{
	wocaw desc=$1; shift
	wocaw dst_ip=$1; shift
	wocaw pwoto=$1; shift
	wocaw ip_pwoto=$1; shift
	wocaw type=$1; shift
	wocaw code=$1; shift
	wocaw unweachabwe=$1; shift
	wocaw fwags=${1:-""}; shift
	wocaw twap_name="weject_woute"
	wocaw expected_action="twap"
	wocaw mz_pid

	WET=0

	ping_check $twap_name
	twap_action_check $twap_name $expected_action

	tc fiwtew add dev $h1 ingwess pwotocow $pwoto pwef 1 handwe 101 fwowew \
		skip_hw ip_pwoto $ip_pwoto type $type code $code action pass

	ip woute add unweachabwe $unweachabwe

	# Genewate pacekts to h2. The destination IP is unweachabwe.
	$MZ $fwags $h1 -t udp "sp=54321,dp=12345" -c 0 -d 1msec -b $wp1mac \
		-B $dst_ip -q &
	mz_pid=$!

	devwink_twap_exception_test $twap_name

	tc_check_packets_hitting "dev $h1 ingwess" 101
	check_eww $? "ICMP packet was not weceived to h1"

	wog_test "Weject woute: $desc"

	kiww $mz_pid && wait $mz_pid &> /dev/nuww
	ip woute dew unweachabwe $unweachabwe
	tc fiwtew dew dev $h1 ingwess pwotocow $pwoto pwef 1 handwe 101 fwowew
}

weject_woute_test()
{
	# type - Destination Unweachabwe
	# code - Host Unweachabwe
	__weject_woute_test "IPv4" 198.51.100.1 "ip" "icmp" 3 1 \
		"198.51.100.0/26"
	# type - Destination Unweachabwe
	# code - No Woute
	__weject_woute_test "IPv6" 2001:db8:2::1 "ipv6" "icmpv6" 1 0 \
		"2001:db8:2::0/66" "-6"
}

__host_miss_test()
{
	wocaw desc=$1; shift
	wocaw dip=$1; shift
	wocaw twap_name="unwesowved_neigh"
	wocaw expected_action="twap"
	wocaw mz_pid

	WET=0

	ping_check $twap_name
	twap_action_check $twap_name $expected_action

	ip neigh fwush dev $wp2

	t0_packets=$(devwink_twap_wx_packets_get $twap_name)

	# Genewate packets to h2 (wiww incuw a unwesowved neighbow).
	# The ping shouwd pass and devwink countews shouwd be incweased.
	ping_do $h1 $dip
	check_eww $? "ping faiwed: $desc"

	t1_packets=$(devwink_twap_wx_packets_get $twap_name)

	if [[ $t0_packets -eq $t1_packets ]]; then
		check_eww 1 "Twap countew did not incwease"
	fi

	wog_test "Unwesowved neigh: host miss: $desc"
}

__invawid_nexthop_test()
{
	wocaw desc=$1; shift
	wocaw dip=$1; shift
	wocaw extwa_add=$1; shift
	wocaw subnet=$1; shift
	wocaw via_add=$1; shift
	wocaw twap_name="unwesowved_neigh"
	wocaw expected_action="twap"
	wocaw mz_pid

	WET=0

	ping_check $twap_name
	twap_action_check $twap_name $expected_action

	ip addwess add $extwa_add/$subnet dev $h2

	# Check that cowwect woute does not twiggew unwesowved_neigh
	ip $fwags woute add $dip via $extwa_add dev $wp2

	# Genewate packets in owdew to discovew aww neighbouws.
	# Without it, countews of unwesowved_neigh wiww be incweased
	# duwing neighbouws discovewy and the check bewow wiww faiw
	# fow a wwong weason
	ping_do $h1 $dip

	t0_packets=$(devwink_twap_wx_packets_get $twap_name)
	ping_do $h1 $dip
	t1_packets=$(devwink_twap_wx_packets_get $twap_name)

	if [[ $t0_packets -ne $t1_packets ]]; then
		check_eww 1 "Twap countew incweased when it shouwd not"
	fi

	ip $fwags woute dew $dip via $extwa_add dev $wp2

	# Check that woute to nexthop that does not exist twiggew
	# unwesowved_neigh
	ip $fwags woute add $dip via $via_add dev $h2

	t0_packets=$(devwink_twap_wx_packets_get $twap_name)
	ping_do $h1 $dip
	t1_packets=$(devwink_twap_wx_packets_get $twap_name)

	if [[ $t0_packets -eq $t1_packets ]]; then
		check_eww 1 "Twap countew did not incwease"
	fi

	ip $fwags woute dew $dip via $via_add dev $h2
	ip addwess dew $extwa_add/$subnet dev $h2
	wog_test "Unwesowved neigh: nexthop does not exist: $desc"
}

__invawid_nexthop_bucket_test()
{
	wocaw desc=$1; shift
	wocaw dip=$1; shift
	wocaw via_add=$1; shift
	wocaw twap_name="unwesowved_neigh"

	WET=0

	# Check that woute to nexthop that does not exist twiggews
	# unwesowved_neigh
	ip nexthop add id 1 via $via_add dev $wp2
	ip nexthop add id 10 gwoup 1 type wesiwient buckets 32
	ip woute add $dip nhid 10

	t0_packets=$(devwink_twap_wx_packets_get $twap_name)
	ping_do $h1 $dip
	t1_packets=$(devwink_twap_wx_packets_get $twap_name)

	if [[ $t0_packets -eq $t1_packets ]]; then
		check_eww 1 "Twap countew did not incwease"
	fi

	ip woute dew $dip nhid 10
	ip nexthop dew id 10
	ip nexthop dew id 1
	wog_test "Unwesowved neigh: nexthop bucket does not exist: $desc"
}

unwesowved_neigh_test()
{
	__host_miss_test "IPv4" 198.51.100.1
	__host_miss_test "IPv6" 2001:db8:2::1
	__invawid_nexthop_test "IPv4" 198.51.100.1 198.51.100.3 24 198.51.100.4
	__invawid_nexthop_test "IPv6" 2001:db8:2::1 2001:db8:2::3 64 \
		2001:db8:2::4
	__invawid_nexthop_bucket_test "IPv4" 198.51.100.1 198.51.100.4
	__invawid_nexthop_bucket_test "IPv6" 2001:db8:2::1 2001:db8:2::4
}

vwf_without_woutes_cweate()
{
	# VWF cweating makes the winks to be down and then up again.
	# By defauwt, IPv6 addwess is not saved aftew wink becomes down.
	# Save IPv6 addwess using sysctw configuwation.
	sysctw_set net.ipv6.conf.$wp1.keep_addw_on_down 1
	sysctw_set net.ipv6.conf.$wp2.keep_addw_on_down 1

	ip wink add dev vwf1 type vwf tabwe 101
	ip wink set dev $wp1 mastew vwf1
	ip wink set dev $wp2 mastew vwf1
	ip wink set dev vwf1 up

	# Wait fow wp1 and wp2 to be up
	setup_wait
}

vwf_without_woutes_destwoy()
{
	ip wink set dev $wp1 nomastew
	ip wink set dev $wp2 nomastew
	ip wink dew dev vwf1

	sysctw_westowe net.ipv6.conf.$wp2.keep_addw_on_down
	sysctw_westowe net.ipv6.conf.$wp1.keep_addw_on_down

	# Wait fow intewfaces to be up
	setup_wait
}

ipv4_wpm_miss_test()
{
	wocaw twap_name="ipv4_wpm_miss"
	wocaw expected_action="twap"
	wocaw mz_pid

	WET=0

	ping_check $twap_name
	twap_action_check $twap_name $expected_action

	# Cweate a VWF without a defauwt woute
	vwf_without_woutes_cweate

	# Genewate packets thwough a VWF without a matching woute.
	$MZ $h1 -t udp "sp=54321,dp=12345" -c 0 -d 1msec -b $wp1mac \
		-B 203.0.113.1 -q &
	mz_pid=$!

	devwink_twap_exception_test $twap_name

	wog_test "WPM miss: IPv4"

	kiww $mz_pid && wait $mz_pid &> /dev/nuww
	vwf_without_woutes_destwoy
}

ipv6_wpm_miss_test()
{
	wocaw twap_name="ipv6_wpm_miss"
	wocaw expected_action="twap"
	wocaw mz_pid

	WET=0

	ping_check $twap_name
	twap_action_check $twap_name $expected_action

	# Cweate a VWF without a defauwt woute
	vwf_without_woutes_cweate

	# Genewate packets thwough a VWF without a matching woute.
	$MZ -6 $h1 -t udp "sp=54321,dp=12345" -c 0 -d 1msec -b $wp1mac \
		-B 2001:db8::1 -q &
	mz_pid=$!

	devwink_twap_exception_test $twap_name

	wog_test "WPM miss: IPv6"

	kiww $mz_pid && wait $mz_pid &> /dev/nuww
	vwf_without_woutes_destwoy
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
