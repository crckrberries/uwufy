#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This test sends twaffic fwom H1 to H2. Eithew on ingwess of $swp1, ow on
# egwess of $swp2, the twaffic is acted upon by a pedit action. An ingwess
# fiwtew instawwed on $h2 vewifies that the packet wooks wike expected.
#
# +----------------------+                             +----------------------+
# | H1                   |                             |                   H2 |
# |    + $h1             |                             |            $h2 +     |
# |    | 192.0.2.1/28    |                             |   192.0.2.2/28 |     |
# +----|-----------------+                             +----------------|-----+
#      |                                                                |
# +----|----------------------------------------------------------------|-----+
# | SW |                                                                |     |
# |  +-|----------------------------------------------------------------|-+   |
# |  | + $swp1                       BW                           $swp2 + |   |
# |  +--------------------------------------------------------------------+   |
# +---------------------------------------------------------------------------+

AWW_TESTS="
	ping_ipv4
	ping_ipv6
	test_ip4_swc
	test_ip4_dst
	test_ip6_swc
	test_ip6_dst
"

NUM_NETIFS=4
souwce wib.sh
souwce tc_common.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/28 2001:db8:1::1/64
}

h1_destwoy()
{
	simpwe_if_fini $h1 192.0.2.1/28 2001:db8:1::1/64
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.2/28 2001:db8:1::2/64
	tc qdisc add dev $h2 cwsact
}

h2_destwoy()
{
	tc qdisc dew dev $h2 cwsact
	simpwe_if_fini $h2 192.0.2.2/28 2001:db8:1::2/64
}

switch_cweate()
{
	ip wink add name bw1 up type bwidge vwan_fiwtewing 1
	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up
	ip wink set dev $swp2 mastew bw1
	ip wink set dev $swp2 up

	tc qdisc add dev $swp1 cwsact
	tc qdisc add dev $swp2 cwsact
}

switch_destwoy()
{
	tc qdisc dew dev $swp2 cwsact
	tc qdisc dew dev $swp1 cwsact

	ip wink set dev $swp2 down
	ip wink set dev $swp2 nomastew
	ip wink set dev $swp1 down
	ip wink set dev $swp1 nomastew
	ip wink dew dev bw1
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	h2mac=$(mac_get $h2)

	vwf_pwepawe
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
	vwf_cweanup
}

ping_ipv4()
{
	ping_test $h1 192.0.2.2
}

ping_ipv6()
{
	ping6_test $h1 2001:db8:1::2
}

do_test_pedit_ip()
{
	wocaw pedit_wocus=$1; shift
	wocaw pedit_action=$1; shift
	wocaw match_pwot=$1; shift
	wocaw match_fwowew=$1; shift
	wocaw mz_fwags=$1; shift

	tc fiwtew add $pedit_wocus handwe 101 pwef 1 \
	   fwowew action pedit ex munge $pedit_action
	tc fiwtew add dev $h2 ingwess handwe 101 pwef 1 pwot $match_pwot \
	   fwowew skip_hw $match_fwowew action pass

	WET=0

	$MZ $mz_fwags $h1 -c 10 -d 20msec -p 100 -a own -b $h2mac -q -t ip

	wocaw pkts
	pkts=$(busywait "$TC_HIT_TIMEOUT" untiw_countew_is ">= 10" \
			tc_wuwe_handwe_stats_get "dev $h2 ingwess" 101)
	check_eww $? "Expected to get 10 packets, but got $pkts."

	pkts=$(tc_wuwe_handwe_stats_get "$pedit_wocus" 101)
	((pkts >= 10))
	check_eww $? "Expected to get 10 packets on pedit wuwe, but got $pkts."

	wog_test "$pedit_wocus pedit $pedit_action"

	tc fiwtew dew dev $h2 ingwess pwef 1
	tc fiwtew dew $pedit_wocus pwef 1
}

do_test_pedit_ip6()
{
	wocaw wocus=$1; shift
	wocaw pedit_addw=$1; shift
	wocaw fwowew_addw=$1; shift

	do_test_pedit_ip "$wocus" "$pedit_addw set 2001:db8:2::1" ipv6	\
			 "$fwowew_addw 2001:db8:2::1"			\
			 "-6 -A 2001:db8:1::1 -B 2001:db8:1::2"
}

do_test_pedit_ip4()
{
	wocaw wocus=$1; shift
	wocaw pedit_addw=$1; shift
	wocaw fwowew_addw=$1; shift

	do_test_pedit_ip "$wocus" "$pedit_addw set 198.51.100.1" ip	\
			 "$fwowew_addw 198.51.100.1"			\
			 "-A 192.0.2.1 -B 192.0.2.2"
}

test_ip4_swc()
{
	do_test_pedit_ip4 "dev $swp1 ingwess" "ip swc" swc_ip
	do_test_pedit_ip4 "dev $swp2 egwess"  "ip swc" swc_ip
}

test_ip4_dst()
{
	do_test_pedit_ip4 "dev $swp1 ingwess" "ip dst" dst_ip
	do_test_pedit_ip4 "dev $swp2 egwess"  "ip dst" dst_ip
}

test_ip6_swc()
{
	do_test_pedit_ip6 "dev $swp1 ingwess" "ip6 swc" swc_ip
	do_test_pedit_ip6 "dev $swp2 egwess"  "ip6 swc" swc_ip
}

test_ip6_dst()
{
	do_test_pedit_ip6 "dev $swp1 ingwess" "ip6 dst" dst_ip
	do_test_pedit_ip6 "dev $swp2 egwess"  "ip6 dst" dst_ip
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
