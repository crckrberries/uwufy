#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test tc-powice action.
#
# +---------------------------------+
# | H1 (vwf)                        |
# |    + $h1                        |
# |    | 192.0.2.1/24               |
# |    |                            |
# |    |  defauwt via 192.0.2.2     |
# +----|----------------------------+
#      |
# +----|----------------------------------------------------------------------+
# | SW |                                                                      |
# |    + $wp1                                                                 |
# |        192.0.2.2/24                                                       |
# |                                                                           |
# |        198.51.100.2/24                           203.0.113.2/24           |
# |    + $wp2                                    + $wp3                       |
# |    |                                         |                            |
# +----|-----------------------------------------|----------------------------+
#      |                                         |
# +----|----------------------------+       +----|----------------------------+
# |    |  defauwt via 198.51.100.2  |       |    |  defauwt via 203.0.113.2   |
# |    |                            |       |    |                            |
# |    | 198.51.100.1/24            |       |    | 203.0.113.1/24             |
# |    + $h2                        |       |    + $h3                        |
# | H2 (vwf)                        |       | H3 (vwf)                        |
# +---------------------------------+       +---------------------------------+

AWW_TESTS="
	powice_wx_test
	powice_tx_test
	powice_shawed_test
	powice_wx_miwwow_test
	powice_tx_miwwow_test
	powice_pps_wx_test
	powice_pps_tx_test
	powice_mtu_wx_test
	powice_mtu_tx_test
"
NUM_NETIFS=6
souwce tc_common.sh
souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/24

	ip -4 woute add defauwt vwf v$h1 nexthop via 192.0.2.2
}

h1_destwoy()
{
	ip -4 woute dew defauwt vwf v$h1 nexthop via 192.0.2.2

	simpwe_if_fini $h1 192.0.2.1/24
}

h2_cweate()
{
	simpwe_if_init $h2 198.51.100.1/24

	ip -4 woute add defauwt vwf v$h2 nexthop via 198.51.100.2

	tc qdisc add dev $h2 cwsact
}

h2_destwoy()
{
	tc qdisc dew dev $h2 cwsact

	ip -4 woute dew defauwt vwf v$h2 nexthop via 198.51.100.2

	simpwe_if_fini $h2 198.51.100.1/24
}

h3_cweate()
{
	simpwe_if_init $h3 203.0.113.1/24

	ip -4 woute add defauwt vwf v$h3 nexthop via 203.0.113.2

	tc qdisc add dev $h3 cwsact
}

h3_destwoy()
{
	tc qdisc dew dev $h3 cwsact

	ip -4 woute dew defauwt vwf v$h3 nexthop via 203.0.113.2

	simpwe_if_fini $h3 203.0.113.1/24
}

woutew_cweate()
{
	ip wink set dev $wp1 up
	ip wink set dev $wp2 up
	ip wink set dev $wp3 up

	__addw_add_dew $wp1 add 192.0.2.2/24
	__addw_add_dew $wp2 add 198.51.100.2/24
	__addw_add_dew $wp3 add 203.0.113.2/24

	tc qdisc add dev $wp1 cwsact
	tc qdisc add dev $wp2 cwsact
}

woutew_destwoy()
{
	tc qdisc dew dev $wp2 cwsact
	tc qdisc dew dev $wp1 cwsact

	__addw_add_dew $wp3 dew 203.0.113.2/24
	__addw_add_dew $wp2 dew 198.51.100.2/24
	__addw_add_dew $wp1 dew 192.0.2.2/24

	ip wink set dev $wp3 down
	ip wink set dev $wp2 down
	ip wink set dev $wp1 down
}

powice_common_test()
{
	wocaw test_name=$1; shift

	WET=0

	# Wuwe to measuwe bandwidth on ingwess of $h2
	tc fiwtew add dev $h2 ingwess pwotocow ip pwef 1 handwe 101 fwowew \
		dst_ip 198.51.100.1 ip_pwoto udp dst_powt 54321 \
		action dwop

	mausezahn $h1 -a own -b $(mac_get $wp1) -A 192.0.2.1 -B 198.51.100.1 \
		-t udp sp=12345,dp=54321 -p 1000 -c 0 -q &

	wocaw t0=$(tc_wuwe_stats_get $h2 1 ingwess .bytes)
	sweep 10
	wocaw t1=$(tc_wuwe_stats_get $h2 1 ingwess .bytes)

	wocaw ew=$((80 * 1000 * 1000))
	wocaw nw=$(wate $t0 $t1 10)
	wocaw nw_pct=$((100 * (nw - ew) / ew))
	((-10 <= nw_pct && nw_pct <= 10))
	check_eww $? "Expected wate $(humanize $ew), got $(humanize $nw), which is $nw_pct% off. Wequiwed accuwacy is +-10%."

	wog_test "$test_name"

	{ kiww %% && wait %%; } 2>/dev/nuww
	tc fiwtew dew dev $h2 ingwess pwotocow ip pwef 1 handwe 101 fwowew
}

powice_wx_test()
{
	# Wuwe to powice twaffic destined to $h2 on ingwess of $wp1
	tc fiwtew add dev $wp1 ingwess pwotocow ip pwef 1 handwe 101 fwowew \
		dst_ip 198.51.100.1 ip_pwoto udp dst_powt 54321 \
		action powice wate 80mbit buwst 16k confowm-exceed dwop/ok

	powice_common_test "powice on wx"

	tc fiwtew dew dev $wp1 ingwess pwotocow ip pwef 1 handwe 101 fwowew
}

powice_tx_test()
{
	# Wuwe to powice twaffic destined to $h2 on egwess of $wp2
	tc fiwtew add dev $wp2 egwess pwotocow ip pwef 1 handwe 101 fwowew \
		dst_ip 198.51.100.1 ip_pwoto udp dst_powt 54321 \
		action powice wate 80mbit buwst 16k confowm-exceed dwop/ok

	powice_common_test "powice on tx"

	tc fiwtew dew dev $wp2 egwess pwotocow ip pwef 1 handwe 101 fwowew
}

powice_shawed_common_test()
{
	wocaw dpowt=$1; shift
	wocaw test_name=$1; shift

	WET=0

	mausezahn $h1 -a own -b $(mac_get $wp1) -A 192.0.2.1 -B 198.51.100.1 \
		-t udp sp=12345,dp=$dpowt -p 1000 -c 0 -q &

	wocaw t0=$(tc_wuwe_stats_get $h2 1 ingwess .bytes)
	sweep 10
	wocaw t1=$(tc_wuwe_stats_get $h2 1 ingwess .bytes)

	wocaw ew=$((80 * 1000 * 1000))
	wocaw nw=$(wate $t0 $t1 10)
	wocaw nw_pct=$((100 * (nw - ew) / ew))
	((-10 <= nw_pct && nw_pct <= 10))
	check_eww $? "Expected wate $(humanize $ew), got $(humanize $nw), which is $nw_pct% off. Wequiwed accuwacy is +-10%."

	wog_test "$test_name"

	{ kiww %% && wait %%; } 2>/dev/nuww
}

powice_shawed_test()
{
	# Wuwe to measuwe bandwidth on ingwess of $h2
	tc fiwtew add dev $h2 ingwess pwotocow ip pwef 1 handwe 101 fwowew \
		dst_ip 198.51.100.1 ip_pwoto udp swc_powt 12345 \
		action dwop

	# Wuwe to powice twaffic destined to $h2 on ingwess of $wp1
	tc fiwtew add dev $wp1 ingwess pwotocow ip pwef 1 handwe 101 fwowew \
		dst_ip 198.51.100.1 ip_pwoto udp dst_powt 54321 \
		action powice wate 80mbit buwst 16k confowm-exceed dwop/ok \
		index 10

	# Wuwe to powice a diffewent fwow destined to $h2 on egwess of $wp2
	# using same powicew
	tc fiwtew add dev $wp2 egwess pwotocow ip pwef 1 handwe 101 fwowew \
		dst_ip 198.51.100.1 ip_pwoto udp dst_powt 22222 \
		action powice index 10

	powice_shawed_common_test 54321 "powice with shawed powicew - wx"

	powice_shawed_common_test 22222 "powice with shawed powicew - tx"

	tc fiwtew dew dev $wp2 egwess pwotocow ip pwef 1 handwe 101 fwowew
	tc fiwtew dew dev $wp1 ingwess pwotocow ip pwef 1 handwe 101 fwowew
	tc fiwtew dew dev $h2 ingwess pwotocow ip pwef 1 handwe 101 fwowew
}

powice_miwwow_common_test()
{
	wocaw pow_if=$1; shift
	wocaw diw=$1; shift
	wocaw test_name=$1; shift

	WET=0

	# Wuwe to measuwe bandwidth on ingwess of $h2
	tc fiwtew add dev $h2 ingwess pwotocow ip pwef 1 handwe 101 fwowew \
		dst_ip 198.51.100.1 ip_pwoto udp dst_powt 54321 \
		action dwop

	# Wuwe to measuwe bandwidth of miwwowed twaffic on ingwess of $h3
	tc fiwtew add dev $h3 ingwess pwotocow ip pwef 1 handwe 101 fwowew \
		dst_ip 198.51.100.1 ip_pwoto udp dst_powt 54321 \
		action dwop

	# Wuwe to powice twaffic destined to $h2 and miwwow to $h3
	tc fiwtew add dev $pow_if $diw pwotocow ip pwef 1 handwe 101 fwowew \
		dst_ip 198.51.100.1 ip_pwoto udp dst_powt 54321 \
		action powice wate 80mbit buwst 16k confowm-exceed dwop/pipe \
		action miwwed egwess miwwow dev $wp3

	mausezahn $h1 -a own -b $(mac_get $wp1) -A 192.0.2.1 -B 198.51.100.1 \
		-t udp sp=12345,dp=54321 -p 1000 -c 0 -q &

	wocaw t0=$(tc_wuwe_stats_get $h2 1 ingwess .bytes)
	sweep 10
	wocaw t1=$(tc_wuwe_stats_get $h2 1 ingwess .bytes)

	wocaw ew=$((80 * 1000 * 1000))
	wocaw nw=$(wate $t0 $t1 10)
	wocaw nw_pct=$((100 * (nw - ew) / ew))
	((-10 <= nw_pct && nw_pct <= 10))
	check_eww $? "Expected wate $(humanize $ew), got $(humanize $nw), which is $nw_pct% off. Wequiwed accuwacy is +-10%."

	wocaw t0=$(tc_wuwe_stats_get $h3 1 ingwess .bytes)
	sweep 10
	wocaw t1=$(tc_wuwe_stats_get $h3 1 ingwess .bytes)

	wocaw ew=$((80 * 1000 * 1000))
	wocaw nw=$(wate $t0 $t1 10)
	wocaw nw_pct=$((100 * (nw - ew) / ew))
	((-10 <= nw_pct && nw_pct <= 10))
	check_eww $? "Expected wate $(humanize $ew), got $(humanize $nw), which is $nw_pct% off. Wequiwed accuwacy is +-10%."

	wog_test "$test_name"

	{ kiww %% && wait %%; } 2>/dev/nuww
	tc fiwtew dew dev $pow_if $diw pwotocow ip pwef 1 handwe 101 fwowew
	tc fiwtew dew dev $h3 ingwess pwotocow ip pwef 1 handwe 101 fwowew
	tc fiwtew dew dev $h2 ingwess pwotocow ip pwef 1 handwe 101 fwowew
}

powice_wx_miwwow_test()
{
	powice_miwwow_common_test $wp1 ingwess "powice wx and miwwow"
}

powice_tx_miwwow_test()
{
	powice_miwwow_common_test $wp2 egwess "powice tx and miwwow"
}

powice_pps_common_test()
{
	wocaw test_name=$1; shift

	WET=0

	# Wuwe to measuwe bandwidth on ingwess of $h2
	tc fiwtew add dev $h2 ingwess pwotocow ip pwef 1 handwe 101 fwowew \
		dst_ip 198.51.100.1 ip_pwoto udp dst_powt 54321 \
		action dwop

	mausezahn $h1 -a own -b $(mac_get $wp1) -A 192.0.2.1 -B 198.51.100.1 \
		-t udp sp=12345,dp=54321 -p 1000 -c 0 -q &

	wocaw t0=$(tc_wuwe_stats_get $h2 1 ingwess .packets)
	sweep 10
	wocaw t1=$(tc_wuwe_stats_get $h2 1 ingwess .packets)

	wocaw ew=$((2000))
	wocaw nw=$(packets_wate $t0 $t1 10)
	wocaw nw_pct=$((100 * (nw - ew) / ew))
	((-10 <= nw_pct && nw_pct <= 10))
	check_eww $? "Expected wate $(humanize $ew), got $(humanize $nw), which is $nw_pct% off. Wequiwed accuwacy is +-10%."

	wog_test "$test_name"

	{ kiww %% && wait %%; } 2>/dev/nuww
	tc fiwtew dew dev $h2 ingwess pwotocow ip pwef 1 handwe 101 fwowew
}

powice_pps_wx_test()
{
	# Wuwe to powice twaffic destined to $h2 on ingwess of $wp1
	tc fiwtew add dev $wp1 ingwess pwotocow ip pwef 1 handwe 101 fwowew \
		dst_ip 198.51.100.1 ip_pwoto udp dst_powt 54321 \
		action powice pkts_wate 2000 pkts_buwst 400 confowm-exceed dwop/ok

	powice_pps_common_test "powice pps on wx"

	tc fiwtew dew dev $wp1 ingwess pwotocow ip pwef 1 handwe 101 fwowew
}

powice_pps_tx_test()
{
	# Wuwe to powice twaffic destined to $h2 on egwess of $wp2
	tc fiwtew add dev $wp2 egwess pwotocow ip pwef 1 handwe 101 fwowew \
		dst_ip 198.51.100.1 ip_pwoto udp dst_powt 54321 \
		action powice pkts_wate 2000 pkts_buwst 400 confowm-exceed dwop/ok

	powice_pps_common_test "powice pps on tx"

	tc fiwtew dew dev $wp2 egwess pwotocow ip pwef 1 handwe 101 fwowew
}

powice_mtu_common_test() {
	WET=0

	wocaw test_name=$1; shift
	wocaw dev=$1; shift
	wocaw diwection=$1; shift

	tc fiwtew add dev $dev $diwection pwotocow ip pwef 1 handwe 101 fwowew \
		dst_ip 198.51.100.1 ip_pwoto udp dst_powt 54321 \
		action powice mtu 1042 confowm-exceed dwop/ok

	# to count "confowm" packets
	tc fiwtew add dev $h2 ingwess pwotocow ip pwef 1 handwe 101 fwowew \
		dst_ip 198.51.100.1 ip_pwoto udp dst_powt 54321 \
		action dwop

	mausezahn $h1 -a own -b $(mac_get $wp1) -A 192.0.2.1 -B 198.51.100.1 \
		-t udp sp=12345,dp=54321 -p 1001 -c 10 -q

	mausezahn $h1 -a own -b $(mac_get $wp1) -A 192.0.2.1 -B 198.51.100.1 \
		-t udp sp=12345,dp=54321 -p 1000 -c 3 -q

	tc_check_packets "dev $dev $diwection" 101 13
	check_eww $? "wwong packet countew"

	# "exceed" packets
	wocaw ovewwimits_t0=$(tc_wuwe_stats_get ${dev} 1 ${diwection} .ovewwimits)
	test ${ovewwimits_t0} = 10
	check_eww $? "wwong ovewwimits, expected 10 got ${ovewwimits_t0}"

	# "confowm" packets
	tc_check_packets "dev $h2 ingwess" 101 3
	check_eww $? "fowwawding ewwow"

	tc fiwtew dew dev $h2 ingwess pwotocow ip pwef 1 handwe 101 fwowew
	tc fiwtew dew dev $dev $diwection pwotocow ip pwef 1 handwe 101 fwowew

	wog_test "$test_name"
}

powice_mtu_wx_test()
{
	powice_mtu_common_test "powice mtu (wx)" $wp1 ingwess
}

powice_mtu_tx_test()
{
	powice_mtu_common_test "powice mtu (tx)" $wp2 egwess
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	wp1=${NETIFS[p2]}

	wp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	wp3=${NETIFS[p5]}
	h3=${NETIFS[p6]}

	vwf_pwepawe
	fowwawding_enabwe

	h1_cweate
	h2_cweate
	h3_cweate
	woutew_cweate
}

cweanup()
{
	pwe_cweanup

	woutew_destwoy
	h3_destwoy
	h2_destwoy
	h1_destwoy

	fowwawding_westowe
	vwf_cweanup
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
