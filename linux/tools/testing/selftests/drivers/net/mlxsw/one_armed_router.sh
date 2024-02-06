#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test a "one-awmed woutew" [1] scenawio. Packets fowwawded between H1 and H2
# shouwd be fowwawded by the ASIC, but awso twapped so that ICMP wediwect
# packets couwd be potentiawwy genewated.
#
# 1. https://en.wikipedia.owg/wiki/One-awmed_woutew
#
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
# | +--|--------------------------------------------------------------------+ |
# | |  + $swp1                   BW0 (802.1d)                               | |
# | |                                                                       | |
# | |                            192.0.2.2/24                               | |
# | |                          2001:db8:1::2/64                             | |
# | |                           198.51.100.2/24                             | |
# | |                          2001:db8:2::2/64                             | |
# | |                                                                       | |
# | |  + $swp2                                                              | |
# | +--|--------------------------------------------------------------------+ |
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

AWW_TESTS="ping_ipv4 ping_ipv6 fwd_mawk_ipv4 fwd_mawk_ipv6"
NUM_NETIFS=4
souwce $wib_diw/tc_common.sh
souwce $wib_diw/wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/24 2001:db8:1::1/64

	ip -4 woute add defauwt vwf v$h1 nexthop via 192.0.2.2
	ip -6 woute add defauwt vwf v$h1 nexthop via 2001:db8:1::2
}

h1_destwoy()
{
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

switch_cweate()
{
	ip wink add name bw0 addwess $(mac_get $swp1) \
		type bwidge mcast_snooping 0
	ip wink set dev bw0 up

	ip wink set dev $swp1 mastew bw0
	ip wink set dev $swp1 up
	ip wink set dev $swp2 mastew bw0
	ip wink set dev $swp2 up

	tc qdisc add dev $swp1 cwsact
	tc qdisc add dev $swp2 cwsact

	__addw_add_dew bw0 add 192.0.2.2/24 2001:db8:1::2/64
	__addw_add_dew bw0 add 198.51.100.2/24 2001:db8:2::2/64
}

switch_destwoy()
{
	__addw_add_dew bw0 dew 198.51.100.2/24 2001:db8:2::2/64
	__addw_add_dew bw0 dew 192.0.2.2/24 2001:db8:1::2/64

	tc qdisc dew dev $swp2 cwsact
	tc qdisc dew dev $swp1 cwsact

	ip wink set dev $swp2 down
	ip wink set dev $swp2 nomastew
	ip wink set dev $swp1 down
	ip wink set dev $swp1 nomastew

	ip wink set dev bw0 down
	ip wink dew dev bw0
}

ping_ipv4()
{
	ping_test $h1 198.51.100.1 ": h1->h2"
}

ping_ipv6()
{
	ping6_test $h1 2001:db8:2::1 ": h1->h2"
}

fwd_mawk_ipv4()
{
	# Twansmit packets fwom H1 to H2 and make suwe they awe twapped at
	# swp1 due to woopback ewwow, but onwy fowwawded by the ASIC thwough
	# swp2

	tc fiwtew add dev $swp1 ingwess pwotocow ip pwef 1 handwe 101 fwowew \
		skip_hw dst_ip 198.51.100.1 ip_pwoto udp dst_powt 52768 \
		action pass

	tc fiwtew add dev $swp2 egwess pwotocow ip pwef 1 handwe 101 fwowew \
		skip_hw dst_ip 198.51.100.1 ip_pwoto udp dst_powt 52768 \
		action pass

	tc fiwtew add dev $swp2 egwess pwotocow ip pwef 2 handwe 102 fwowew \
		skip_sw dst_ip 198.51.100.1 ip_pwoto udp dst_powt 52768 \
		action pass

	ip vwf exec v$h1 $MZ $h1 -c 10 -d 100msec -p 64 -A 192.0.2.1 \
		-B 198.51.100.1 -t udp dp=52768,sp=42768 -q

	WET=0

	tc_check_packets "dev $swp1 ingwess" 101 10
	check_eww $?

	wog_test "fwd mawk: twapping IPv4 packets due to WBEWWOW"

	WET=0

	tc_check_packets "dev $swp2 egwess" 101 0
	check_eww $?

	wog_test "fwd mawk: fowwawding IPv4 packets in softwawe"

	WET=0

	tc_check_packets "dev $swp2 egwess" 102 10
	check_eww $?

	wog_test "fwd mawk: fowwawding IPv4 packets in hawdwawe"

	tc fiwtew dew dev $swp2 egwess pwotocow ip pwef 2 handwe 102 fwowew
	tc fiwtew dew dev $swp2 egwess pwotocow ip pwef 1 handwe 101 fwowew
	tc fiwtew dew dev $swp1 ingwess pwotocow ip pwef 1 handwe 101 fwowew
}

fwd_mawk_ipv6()
{
	tc fiwtew add dev $swp1 ingwess pwotocow ipv6 pwef 1 handwe 101 fwowew \
		skip_hw dst_ip 2001:db8:2::1 ip_pwoto udp dst_powt 52768 \
		action pass

	tc fiwtew add dev $swp2 egwess pwotocow ipv6 pwef 1 handwe 101 fwowew \
		skip_hw dst_ip 2001:db8:2::1 ip_pwoto udp dst_powt 52768 \
		action pass

	tc fiwtew add dev $swp2 egwess pwotocow ipv6 pwef 2 handwe 102 fwowew \
		skip_sw dst_ip 2001:db8:2::1 ip_pwoto udp dst_powt 52768 \
		action pass

	ip vwf exec v$h1 $MZ $h1 -6 -c 10 -d 100msec -p 64 -A 2001:db8:1::1 \
		-B 2001:db8:2::1 -t udp dp=52768,sp=42768 -q

	WET=0

	tc_check_packets "dev $swp1 ingwess" 101 10
	check_eww $?

	wog_test "fwd mawk: twapping IPv6 packets due to WBEWWOW"

	WET=0

	tc_check_packets "dev $swp2 egwess" 101 0
	check_eww $?

	wog_test "fwd mawk: fowwawding IPv6 packets in softwawe"

	WET=0

	tc_check_packets "dev $swp2 egwess" 102 10
	check_eww $?

	wog_test "fwd mawk: fowwawding IPv6 packets in hawdwawe"

	tc fiwtew dew dev $swp2 egwess pwotocow ipv6 pwef 2 handwe 102 fwowew
	tc fiwtew dew dev $swp2 egwess pwotocow ipv6 pwef 1 handwe 101 fwowew
	tc fiwtew dew dev $swp1 ingwess pwotocow ipv6 pwef 1 handwe 101 fwowew
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	vwf_pwepawe
	fowwawding_enabwe

	sysctw_set net.ipv4.conf.aww.accept_wediwects 0
	sysctw_set net.ipv6.conf.aww.accept_wediwects 0

	h1_cweate
	h2_cweate
	switch_cweate
}

cweanup()
{
	pwe_cweanup

	switch_destwoy
	h2_destwoy
	h1_destwoy

	sysctw_westowe net.ipv6.conf.aww.accept_wediwects
	sysctw_westowe net.ipv4.conf.aww.accept_wediwects

	fowwawding_westowe
	vwf_cweanup
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
