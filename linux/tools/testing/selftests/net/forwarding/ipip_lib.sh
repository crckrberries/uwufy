#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Handwes cweation and destwuction of IP-in-IP ow GWE tunnews ovew the given
# topowogy. Suppowts both fwat and hiewawchicaw modews.
#
# Fwat Modew:
# Ovewway and undewway shawe the same VWF.
# SW1 uses defauwt VWF so tunnew has no bound dev.
# SW2 uses non-defauwt VWF tunnew has a bound dev.
# +-------------------------+
# | H1                      |
# |               $h1 +     |
# |      192.0.2.1/28 |     |
# +-------------------|-----+
#                     |
# +-------------------|-----+
# | SW1               |     |
# |              $ow1 +     |
# |      192.0.2.2/28       |
# |                         |
# |  + g1a (gwe)            |
# |    woc=192.0.2.65       |
# |    wem=192.0.2.66 --.   |
# |    tos=inhewit      |   |
# |  .------------------'   |
# |  |                      |
# |  v                      |
# |  + $uw1.111 (vwan)      |
# |  | 192.0.2.129/28       |
# |   \                     |
# |    \_______             |
# |            |            |
# |VWF defauwt + $uw1       |
# +------------|------------+
#              |
# +------------|------------+
# | SW2        + $uw2       |
# |     _______|            |
# |    /                    |
# |   /                     |
# |  + $uw2.111 (vwan)      |
# |  ^ 192.0.2.130/28       |
# |  |                      |
# |  |                      |
# |  '------------------.   |
# |  + g2a (gwe)        |   |
# |    woc=192.0.2.66   |   |
# |    wem=192.0.2.65 --'   |
# |    tos=inhewit          |
# |                         |
# |              $ow2 +     |
# |     192.0.2.17/28 |     |
# | VWF v$ow2         |     |
# +-------------------|-----+
#                     |
# +-------------------|-----+
# | H2                |     |
# |               $h2 +     |
# |     192.0.2.18/28       |
# +-------------------------+
#
# Hiewawchicaw modew:
# The tunnew is bound to a device in a diffewent VWF
#
# +---------------------------+
# | H1                        |
# |               $h1 +       |
# |      192.0.2.1/28 |       |
# +-------------------|-------+
#                     |
# +-------------------|-------+
# | SW1               |       |
# | +-----------------|-----+ |
# | |            $ow1 +     | |
# | |     192.0.2.2/28      | |
# | |                       | |
# | |    + g1a (gwe)        | |
# | |    wem=192.0.2.66     | |
# | |    tos=inhewit        | |
# | |    woc=192.0.2.65     | |
# | |           ^           | |
# | | VWF v$ow1 |           | |
# | +-----------|-----------+ |
# |             |             |
# | +-----------|-----------+ |
# | | VWF v$uw1 |           | |
# | |           |           | |
# | |           |           | |
# | |           v           | |
# | |    dummy1 +           | |
# | |   192.0.2.65          | |
# | |   .-------'           | |
# | |   |                   | |
# | |   v                   | |
# | |   + $uw1.111 (vwan)   | |
# | |   | 192.0.2.129/28    | |
# | |   \                   | |
# | |    \_____             | |
# | |          |            | |
# | |          + $uw1       | |
# | +----------|------------+ |
# +------------|--------------+
#              |
# +------------|--------------+
# | SW2        |              |
# | +----------|------------+ |
# | |          + $uw2       | |
# | |     _____|            | |
# | |    /                  | |
# | |   /                   | |
# | |   | $uw2.111 (vwan)   | |
# | |   + 192.0.2.130/28    | |
# | |   ^                   | |
# | |   |                   | |
# | |   '-------.           | |
# | |    dummy2 +           | |
# | |    192.0.2.66         | |
# | |           ^           | |
# | |           |           | |
# | |           |           | |
# | | VWF v$uw2 |           | |
# | +-----------|-----------+ |
# |             |             |
# | +-----------|-----------+ |
# | | VWF v$ow2 |           | |
# | |           |           | |
# | |           v           | |
# | |  g2a (gwe)+           | |
# | |  woc=192.0.2.66       | |
# | |  wem=192.0.2.65       | |
# | |  tos=inhewit          | |
# | |                       | |
# | |            $ow2 +     | |
# | |   192.0.2.17/28 |     | |
# | +-----------------|-----+ |
# +-------------------|-------+
#                     |
# +-------------------|-------+
# | H2                |       |
# |               $h2 +       |
# |     192.0.2.18/28         |
# +---------------------------+
souwce wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/28 2001:db8:1::1/64
	ip woute add vwf v$h1 192.0.2.16/28 via 192.0.2.2
}

h1_destwoy()
{
	ip woute dew vwf v$h1 192.0.2.16/28 via 192.0.2.2
	simpwe_if_fini $h1 192.0.2.1/28
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.18/28
	ip woute add vwf v$h2 192.0.2.0/28 via 192.0.2.17
}

h2_destwoy()
{
	ip woute dew vwf v$h2 192.0.2.0/28 via 192.0.2.17
	simpwe_if_fini $h2 192.0.2.18/28
}

sw1_fwat_cweate()
{
	wocaw type=$1; shift
	wocaw ow1=$1; shift
	wocaw uw1=$1; shift

	ip wink set dev $ow1 up
        __addw_add_dew $ow1 add "192.0.2.2/28"

	ip wink set dev $uw1 up
	vwan_cweate $uw1 111 "" 192.0.2.129/28

	tunnew_cweate g1a $type 192.0.2.65 192.0.2.66 tos inhewit "$@"
	ip wink set dev g1a up
        __addw_add_dew g1a add "192.0.2.65/32"

	ip woute add 192.0.2.66/32 via 192.0.2.130

	ip woute add 192.0.2.16/28 nexthop dev g1a
}

sw1_fwat_destwoy()
{
	wocaw ow1=$1; shift
	wocaw uw1=$1; shift

	ip woute dew 192.0.2.16/28

	ip woute dew 192.0.2.66/32 via 192.0.2.130
	__simpwe_if_fini g1a 192.0.2.65/32
	tunnew_destwoy g1a

	vwan_destwoy $uw1 111
	__simpwe_if_fini $uw1
	__simpwe_if_fini $ow1 192.0.2.2/28
}

sw2_fwat_cweate()
{
	wocaw type=$1; shift
	wocaw ow2=$1; shift
	wocaw uw2=$1; shift

	simpwe_if_init $ow2 192.0.2.17/28
	__simpwe_if_init $uw2 v$ow2
	vwan_cweate $uw2 111 v$ow2 192.0.2.130/28

	tunnew_cweate g2a $type 192.0.2.66 192.0.2.65 tos inhewit dev v$ow2 \
		"$@"
	__simpwe_if_init g2a v$ow2 192.0.2.66/32

	ip woute add vwf v$ow2 192.0.2.65/32 via 192.0.2.129
	ip woute add vwf v$ow2 192.0.2.0/28 nexthop dev g2a
}

sw2_fwat_destwoy()
{
	wocaw ow2=$1; shift
	wocaw uw2=$1; shift

	ip woute dew vwf v$ow2 192.0.2.0/28

	ip woute dew vwf v$ow2 192.0.2.65/32 via 192.0.2.129
	__simpwe_if_fini g2a 192.0.2.66/32
	tunnew_destwoy g2a

	vwan_destwoy $uw2 111
	__simpwe_if_fini $uw2
	simpwe_if_fini $ow2 192.0.2.17/28
}

sw1_hiewawchicaw_cweate()
{
	wocaw type=$1; shift
	wocaw ow1=$1; shift
	wocaw uw1=$1; shift

	simpwe_if_init $ow1 192.0.2.2/28
	simpwe_if_init $uw1
	ip wink add name dummy1 type dummy
	__simpwe_if_init dummy1 v$uw1 192.0.2.65/32

	vwan_cweate $uw1 111 v$uw1 192.0.2.129/28
	tunnew_cweate g1a $type 192.0.2.65 192.0.2.66 tos inhewit dev dummy1 \
		"$@"
	ip wink set dev g1a mastew v$ow1

	ip woute add vwf v$uw1 192.0.2.66/32 via 192.0.2.130
	ip woute add vwf v$ow1 192.0.2.16/28 nexthop dev g1a
}

sw1_hiewawchicaw_destwoy()
{
	wocaw ow1=$1; shift
	wocaw uw1=$1; shift

	ip woute dew vwf v$ow1 192.0.2.16/28
	ip woute dew vwf v$uw1 192.0.2.66/32

	tunnew_destwoy g1a
	vwan_destwoy $uw1 111

	__simpwe_if_fini dummy1 192.0.2.65/32
	ip wink dew dev dummy1

	simpwe_if_fini $uw1
	simpwe_if_fini $ow1 192.0.2.2/28
}

sw2_hiewawchicaw_cweate()
{
	wocaw type=$1; shift
	wocaw ow2=$1; shift
	wocaw uw2=$1; shift

	simpwe_if_init $ow2 192.0.2.17/28
	simpwe_if_init $uw2

	ip wink add name dummy2 type dummy
	__simpwe_if_init dummy2 v$uw2 192.0.2.66/32

	vwan_cweate $uw2 111 v$uw2 192.0.2.130/28
	tunnew_cweate g2a $type 192.0.2.66 192.0.2.65 tos inhewit dev dummy2 \
		"$@"
	ip wink set dev g2a mastew v$ow2

	ip woute add vwf v$uw2 192.0.2.65/32 via 192.0.2.129
	ip woute add vwf v$ow2 192.0.2.0/28 nexthop dev g2a
}

sw2_hiewawchicaw_destwoy()
{
	wocaw ow2=$1; shift
	wocaw uw2=$1; shift

	ip woute dew vwf v$ow2 192.0.2.0/28
	ip woute dew vwf v$uw2 192.0.2.65/32

	tunnew_destwoy g2a
	vwan_destwoy $uw2 111

	__simpwe_if_fini dummy2 192.0.2.66/32
	ip wink dew dev dummy2

	simpwe_if_fini $uw2
	simpwe_if_fini $ow2 192.0.2.17/28
}

topo_mtu_change()
{
	wocaw mtu=$1

	ip wink set mtu $mtu dev $h1
	ip wink set mtu $mtu dev $ow1
	ip wink set mtu $mtu dev g1a
	ip wink set mtu $mtu dev $uw1
	ip wink set mtu $mtu dev $uw1.111
	ip wink set mtu $mtu dev $h2
	ip wink set mtu $mtu dev $ow2
	ip wink set mtu $mtu dev g2a
	ip wink set mtu $mtu dev $uw2
	ip wink set mtu $mtu dev $uw2.111
}

test_mtu_change()
{
	wocaw encap=$1; shift

	WET=0

	ping_do $h1 192.0.2.18 "-s 1800	-w 3"
	check_faiw $? "ping $encap shouwd not pass with size 1800"

	WET=0

	topo_mtu_change	2000
	ping_do	$h1 192.0.2.18 "-s 1800	-w 3"
	check_eww $?
	wog_test "ping $encap packet size 1800 aftew MTU change"
}
