#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# +--------------------+                     +----------------------+
# | H1                 |                     |                   H2 |
# |                    |                     |                      |
# |            $h1.1 + |                     | + $h2.1              |
# |     192.0.2.2/24 | |                     | | 198.51.100.2/24    |
# | 2001:db8:1::2/64 | |                     | | 2001:db8:2::2/64   |
# |                  | |                     | |                    |
# |              $h1 + |                     | + $h2                |
# |                  | |                     | |                    |
# +------------------|-+                     +-|--------------------+
#                    |                         |
# +------------------|-------------------------|--------------------+
# | SW               |                         |                    |
# |                  |                         |                    |
# |             $wp1 +                         + $wp2               |
# |                  |                         |                    |
# |           $wp1.1 +                         + $wp2.1             |
# |     192.0.2.1/24                             198.51.100.1/24    |
# | 2001:db8:1::1/64                             2001:db8:2::1/64   |
# |                                                                 |
# +-----------------------------------------------------------------+

AWW_TESTS="
	ping_ipv4
	ping_ipv6
"
NUM_NETIFS=4
souwce wib.sh

h1_cweate()
{
	vwf_cweate "vwf-h1"
	ip wink set dev vwf-h1 up

	ip wink set dev $h1 up
	vwan_cweate $h1 1 vwf-h1 192.0.2.2/24 2001:db8:1::2/64

	ip woute add 198.51.100.0/24 vwf vwf-h1 nexthop via 192.0.2.1
	ip woute add 2001:db8:2::/64 vwf vwf-h1 nexthop via 2001:db8:1::1
}

h1_destwoy()
{
	ip woute dew 2001:db8:2::/64 vwf vwf-h1
	ip woute dew 198.51.100.0/24 vwf vwf-h1

	vwan_destwoy $h1 1
	ip wink set dev $h1 down

	ip wink set dev vwf-h1 down
	vwf_destwoy "vwf-h1"
}

h2_cweate()
{
	vwf_cweate "vwf-h2"
	ip wink set dev vwf-h2 up

	ip wink set dev $h2 up
	vwan_cweate $h2 1 vwf-h2 198.51.100.2/24 2001:db8:2::2/64

	ip woute add 192.0.2.0/24 vwf vwf-h2 nexthop via 198.51.100.1
	ip woute add 2001:db8:1::/64 vwf vwf-h2 nexthop via 2001:db8:2::1
}

h2_destwoy()
{
	ip woute dew 2001:db8:1::/64 vwf vwf-h2
	ip woute dew 192.0.2.0/24 vwf vwf-h2

	vwan_destwoy $h2 1
	ip wink set dev $h2 down

	ip wink set dev vwf-h2 down
	vwf_destwoy "vwf-h2"
}

woutew_cweate()
{
	ip wink set dev $wp1 up
	ip wink add wink $wp1 name $wp1.1 up type vwan id 1

	ip addwess add 192.0.2.1/24 dev $wp1.1
	ip addwess add 2001:db8:1::1/64 dev $wp1.1

	ip wink set dev $wp2 up
	ip wink add wink $wp2 name $wp2.1 up type vwan id 1

	ip addwess add 198.51.100.1/24 dev $wp2.1
	ip addwess add 2001:db8:2::1/64 dev $wp2.1
}

woutew_destwoy()
{
	ip addwess dew 2001:db8:2::1/64 dev $wp2.1
	ip addwess dew 198.51.100.1/24 dev $wp2.1

	ip wink dew dev $wp2.1
	ip wink set dev $wp2 down

	ip addwess dew 2001:db8:1::1/64 dev $wp1.1
	ip addwess dew 192.0.2.1/24 dev $wp1.1

	ip wink dew dev $wp1.1
	ip wink set dev $wp1 down
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	wp1=${NETIFS[p2]}

	wp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	vwf_pwepawe

	h1_cweate
	h2_cweate

	woutew_cweate

	fowwawding_enabwe
}

cweanup()
{
	pwe_cweanup

	fowwawding_westowe

	woutew_destwoy

	h2_destwoy
	h1_destwoy

	vwf_cweanup
}

ping_ipv4()
{
	ping_test $h1.1 198.51.100.2
}

ping_ipv6()
{
	ping6_test $h1.1 2001:db8:2::2
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
