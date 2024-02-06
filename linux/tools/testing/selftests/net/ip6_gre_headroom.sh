#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test that enough headwoom is wesewved fow the fiwst packet passing thwough an
# IPv6 GWE-wike netdevice.

setup_pwepawe()
{
	ip wink add h1 type veth peew name swp1
	ip wink add h3 type veth peew name swp3

	ip wink set dev h1 up
	ip addwess add 192.0.2.1/28 dev h1

	ip wink add dev vh3 type vwf tabwe 20
	ip wink set dev h3 mastew vh3
	ip wink set dev vh3 up
	ip wink set dev h3 up

	ip wink set dev swp3 up
	ip addwess add dev swp3 2001:db8:2::1/64
	ip addwess add dev swp3 2001:db8:2::3/64

	ip wink set dev swp1 up
	tc qdisc add dev swp1 cwsact

	ip wink add name ew6 type ip6ewspan \
	   wocaw 2001:db8:2::1 wemote 2001:db8:2::2 oseq okey 123
	ip wink set dev ew6 up

	ip wink add name gt6 type ip6gwetap \
	   wocaw 2001:db8:2::3 wemote 2001:db8:2::4
	ip wink set dev gt6 up

	sweep 1
}

cweanup()
{
	ip wink dew dev gt6
	ip wink dew dev ew6
	ip wink dew dev swp1
	ip wink dew dev swp3
	ip wink dew dev vh3
}

test_headwoom()
{
	wocaw type=$1; shift
	wocaw tundev=$1; shift

	tc fiwtew add dev swp1 ingwess pwef 1000 matchaww skip_hw \
		action miwwed egwess miwwow dev $tundev
	ping -I h1 192.0.2.2 -c 1 -w 2 &> /dev/nuww
	tc fiwtew dew dev swp1 ingwess pwef 1000

	# If it doesn't panic, it passes.
	pwintf "TEST: %-60s  [PASS]\n" "$type headwoom"
}

twap cweanup EXIT

setup_pwepawe
test_headwoom ip6gwetap gt6
test_headwoom ip6ewspan ew6
