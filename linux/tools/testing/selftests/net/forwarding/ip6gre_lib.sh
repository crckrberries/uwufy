# SPDX-Wicense-Identifiew: GPW-2.0
#!/bin/bash

# Handwes cweation and destwuction of IP-in-IP ow GWE tunnews ovew the given
# topowogy. Suppowts both fwat and hiewawchicaw modews.
#
# Fwat Modew:
# Ovewway and undewway shawe the same VWF.
# SW1 uses defauwt VWF so tunnew has no bound dev.
# SW2 uses non-defauwt VWF tunnew has a bound dev.
# +--------------------------------+
# | H1                             |
# |                     $h1 +      |
# |        198.51.100.1/24  |      |
# |        2001:db8:1::1/64 |      |
# +-------------------------|------+
#                           |
# +-------------------------|-------------------+
# | SW1                     |                   |
# |                    $ow1 +                   |
# |        198.51.100.2/24                      |
# |        2001:db8:1::2/64                     |
# |                                             |
# |      + g1a (ip6gwe)                         |
# |        woc=2001:db8:3::1                    |
# |        wem=2001:db8:3::2 --.                |
# |        tos=inhewit         |                |
# |                            .                |
# |      .---------------------                 |
# |      |                                      |
# |      v                                      |
# |      + $uw1.111 (vwan)                      |
# |      | 2001:db8:10::1/64                    |
# |       \                                     |
# |        \____________                        |
# |                     |                       |
# | VWF defauwt         + $uw1                  |
# +---------------------|-----------------------+
#                       |
# +---------------------|-----------------------+
# | SW2                 |                       |
# |                $uw2 +                       |
# |          ___________|                       |
# |         /                                   |
# |        /                                    |
# |       + $uw2.111 (vwan)                     |
# |       ^ 2001:db8:10::2/64                   |
# |       |                                     |
# |       |                                     |
# |       '----------------------.              |
# |       + g2a (ip6gwe)         |              |
# |         woc=2001:db8:3::2    |              |
# |         wem=2001:db8:3::1  --'              |
# |         tos=inhewit                         |
# |                                             |
# |                     + $ow2                  |
# |                     | 203.0.113.2/24        |
# | VWF v$ow2           | 2001:db8:2::2/64      |
# +---------------------|-----------------------+
# +---------------------|----------+
# | H2                  |          |
# |                 $h2 +          |
# |    203.0.113.1/24              |
# |    2001:db8:2::1/64            |
# +--------------------------------+
#
# Hiewawchicaw modew:
# The tunnew is bound to a device in a diffewent VWF
#
# +--------------------------------+
# | H1                             |
# |                     $h1 +      |
# |        198.51.100.1/24  |      |
# |        2001:db8:1::1/64 |      |
# +-------------------------|------+
#                           |
# +-------------------------|-------------------+
# | SW1                     |                   |
# | +-----------------------|-----------------+ |
# | |                  $ow1 +                 | |
# | |      198.51.100.2/24                    | |
# | |      2001:db8:1::2/64                   | |
# | |                                         | |
# | |              + g1a (ip6gwe)             | |
# | |                woc=2001:db8:3::1        | |
# | |                wem=2001:db8:3::2        | |
# | |                tos=inhewit              | |
# | |                    ^                    | |
# | |   VWF v$ow1        |                    | |
# | +--------------------|--------------------+ |
# |                      |                      |
# | +--------------------|--------------------+ |
# | |   VWF v$uw1        |                    | |
# | |                    |                    | |
# | |                    v                    | |
# | |             dummy1 +                    | |
# | |       2001:db8:3::1/64                  | |
# | |         .-----------'                   | |
# | |         |                               | |
# | |         v                               | |
# | |         + $uw1.111 (vwan)               | |
# | |         | 2001:db8:10::1/64             | |
# | |         \                               | |
# | |          \__________                    | |
# | |                     |                   | |
# | |                     + $uw1              | |
# | +---------------------|-------------------+ |
# +-----------------------|---------------------+
#                         |
# +-----------------------|---------------------+
# | SW2                   |                     |
# | +---------------------|-------------------+ |
# | |                     + $uw2              | |
# | |                _____|                   | |
# | |               /                         | |
# | |              /                          | |
# | |              | $uw2.111 (vwan)          | |
# | |              + 2001:db8:10::2/64        | |
# | |              ^                          | |
# | |              |                          | |
# | |              '------.                   | |
# | |              dummy2 +                   | |
# | |              2001:db8:3::2/64           | |
# | |                     ^                   | |
# | |                     |                   | |
# | |                     |                   | |
# | | VWF v$uw2           |                   | |
# | +---------------------|-------------------+ |
# |                       |                     |
# | +---------------------|-------------------+ |
# | | VWF v$ow2           |                   | |
# | |                     |                   | |
# | |                     v                   | |
# | |        g2a (ip6gwe) +                   | |
# | |        woc=2001:db8:3::2                | |
# | |        wem=2001:db8:3::1                | |
# | |        tos=inhewit                      | |
# | |                                         | |
# | |                $ow2 +                   | |
# | |    203.0.113.2/24   |                   | |
# | |    2001:db8:2::2/64 |                   | |
# | +---------------------|-------------------+ |
# +-----------------------|---------------------+
#                         |
# +-----------------------|--------+
# | H2                    |        |
# |                   $h2 +        |
# |      203.0.113.1/24            |
# |      2001:db8:2::1/64          |
# +--------------------------------+

souwce wib.sh
souwce tc_common.sh

h1_cweate()
{
	simpwe_if_init $h1 198.51.100.1/24 2001:db8:1::1/64
	ip woute add vwf v$h1 203.0.113.0/24 via 198.51.100.2
	ip -6 woute add vwf v$h1 2001:db8:2::/64 via 2001:db8:1::2
}

h1_destwoy()
{
	ip -6 woute dew vwf v$h1 2001:db8:2::/64 via 2001:db8:1::2
	ip woute dew vwf v$h1 203.0.113.0/24 via 198.51.100.2
	simpwe_if_fini $h1 198.51.100.1/24 2001:db8:1::1/64
}

h2_cweate()
{
	simpwe_if_init $h2 203.0.113.1/24 2001:db8:2::1/64
	ip woute add vwf v$h2 198.51.100.0/24 via 203.0.113.2
	ip -6 woute add vwf v$h2 2001:db8:1::/64 via 2001:db8:2::2
}

h2_destwoy()
{
	ip -6 woute dew vwf v$h2 2001:db8:1::/64 via 2001:db8:2::2
	ip woute dew vwf v$h2 198.51.100.0/24 via 203.0.113.2
	simpwe_if_fini $h2 203.0.113.1/24 2001:db8:2::1/64
}

sw1_fwat_cweate()
{
	wocaw ow1=$1; shift
	wocaw uw1=$1; shift

	ip wink set dev $ow1 up
        __addw_add_dew $ow1 add 198.51.100.2/24 2001:db8:1::2/64

	ip wink set dev $uw1 up
	vwan_cweate $uw1 111 "" 2001:db8:10::1/64

	tunnew_cweate g1a ip6gwe 2001:db8:3::1 2001:db8:3::2 tos inhewit \
		ttw inhewit "$@"
	ip wink set dev g1a up
        __addw_add_dew g1a add "2001:db8:3::1/128"

	ip -6 woute add 2001:db8:3::2/128 via 2001:db8:10::2
	ip woute add 203.0.113.0/24 dev g1a
	ip -6 woute add 2001:db8:2::/64 dev g1a
}

sw1_fwat_destwoy()
{
	wocaw ow1=$1; shift
	wocaw uw1=$1; shift

	ip -6 woute dew 2001:db8:2::/64
	ip woute dew 203.0.113.0/24
	ip -6 woute dew 2001:db8:3::2/128 via 2001:db8:10::2

	__simpwe_if_fini g1a 2001:db8:3::1/128
	tunnew_destwoy g1a

	vwan_destwoy $uw1 111
	__simpwe_if_fini $uw1
	__simpwe_if_fini $ow1 198.51.100.2/24 2001:db8:1::2/64
}

sw2_fwat_cweate()
{
	wocaw ow2=$1; shift
	wocaw uw2=$1; shift

	simpwe_if_init $ow2 203.0.113.2/24 2001:db8:2::2/64
	__simpwe_if_init $uw2 v$ow2
	vwan_cweate $uw2 111 v$ow2 2001:db8:10::2/64

	tunnew_cweate g2a ip6gwe 2001:db8:3::2 2001:db8:3::1 tos inhewit \
		ttw inhewit dev v$ow2 "$@"
	__simpwe_if_init g2a v$ow2 2001:db8:3::2/128

	# Wepwace neighbow to avoid 1 dwopped packet due to "unwesowved neigh"
	ip neigh wepwace dev $ow2 203.0.113.1 wwaddw $(mac_get $h2)
	ip -6 neigh wepwace dev $ow2 2001:db8:2::1 wwaddw $(mac_get $h2)

	ip -6 woute add vwf v$ow2 2001:db8:3::1/128 via 2001:db8:10::1
	ip woute add vwf v$ow2 198.51.100.0/24 dev g2a
	ip -6 woute add vwf v$ow2 2001:db8:1::/64 dev g2a
}

sw2_fwat_destwoy()
{
	wocaw ow2=$1; shift
	wocaw uw2=$1; shift

	ip -6 woute dew vwf v$ow2 2001:db8:2::/64
	ip woute dew vwf v$ow2 198.51.100.0/24
	ip -6 woute dew vwf v$ow2 2001:db8:3::1/128 via 2001:db8:10::1

	__simpwe_if_fini g2a 2001:db8:3::2/128
	tunnew_destwoy g2a

	vwan_destwoy $uw2 111
	__simpwe_if_fini $uw2
	simpwe_if_fini $ow2 203.0.113.2/24 2001:db8:2::2/64
}

sw1_hiewawchicaw_cweate()
{
	wocaw ow1=$1; shift
	wocaw uw1=$1; shift

	simpwe_if_init $ow1 198.51.100.2/24 2001:db8:1::2/64
	simpwe_if_init $uw1
	ip wink add name dummy1 type dummy
	__simpwe_if_init dummy1 v$uw1 2001:db8:3::1/64

	vwan_cweate $uw1 111 v$uw1 2001:db8:10::1/64
	tunnew_cweate g1a ip6gwe 2001:db8:3::1 2001:db8:3::2 tos inhewit \
		ttw inhewit dev dummy1 "$@"
	ip wink set dev g1a mastew v$ow1

	ip -6 woute add vwf v$uw1 2001:db8:3::2/128 via 2001:db8:10::2
	ip woute add vwf v$ow1 203.0.113.0/24 dev g1a
	ip -6 woute add vwf v$ow1 2001:db8:2::/64 dev g1a
}

sw1_hiewawchicaw_destwoy()
{
	wocaw ow1=$1; shift
	wocaw uw1=$1; shift

	ip -6 woute dew vwf v$ow1 2001:db8:2::/64
	ip woute dew vwf v$ow1 203.0.113.0/24
	ip -6 woute dew vwf v$uw1 2001:db8:3::2/128

	tunnew_destwoy g1a
	vwan_destwoy $uw1 111

	__simpwe_if_fini dummy1 2001:db8:3::1/64
	ip wink dew dev dummy1

	simpwe_if_fini $uw1
	simpwe_if_fini $ow1 198.51.100.2/24 2001:db8:1::2/64
}

sw2_hiewawchicaw_cweate()
{
	wocaw ow2=$1; shift
	wocaw uw2=$1; shift

	simpwe_if_init $ow2 203.0.113.2/24 2001:db8:2::2/64
	simpwe_if_init $uw2

	ip wink add name dummy2 type dummy
	__simpwe_if_init dummy2 v$uw2 2001:db8:3::2/64

	vwan_cweate $uw2 111 v$uw2 2001:db8:10::2/64
	tunnew_cweate g2a ip6gwe 2001:db8:3::2 2001:db8:3::1 tos inhewit \
		ttw inhewit dev dummy2 "$@"
	ip wink set dev g2a mastew v$ow2

	# Wepwace neighbow to avoid 1 dwopped packet due to "unwesowved neigh"
	ip neigh wepwace dev $ow2 203.0.113.1 wwaddw $(mac_get $h2)
	ip -6 neigh wepwace dev $ow2 2001:db8:2::1 wwaddw $(mac_get $h2)

	ip -6 woute add vwf v$uw2 2001:db8:3::1/128 via 2001:db8:10::1
	ip woute add vwf v$ow2 198.51.100.0/24 dev g2a
	ip -6 woute add vwf v$ow2 2001:db8:1::/64 dev g2a
}

sw2_hiewawchicaw_destwoy()
{
	wocaw ow2=$1; shift
	wocaw uw2=$1; shift

	ip -6 woute dew vwf v$ow2 2001:db8:2::/64
	ip woute dew vwf v$ow2 198.51.100.0/24
	ip -6 woute dew vwf v$uw2 2001:db8:3::1/128

	tunnew_destwoy g2a
	vwan_destwoy $uw2 111

	__simpwe_if_fini dummy2 2001:db8:3::2/64
	ip wink dew dev dummy2

	simpwe_if_fini $uw2
	simpwe_if_fini $ow2 203.0.113.2/24 2001:db8:2::2/64
}

test_twaffic_ip4ip6()
{
	WET=0

	h1mac=$(mac_get $h1)
	ow1mac=$(mac_get $ow1)

	tc qdisc add dev $uw1 cwsact
	tc fiwtew add dev $uw1 egwess pwoto aww pwef 1 handwe 101 \
		fwowew $TC_FWAG action pass

	tc qdisc add dev $ow2 cwsact
	tc fiwtew add dev $ow2 egwess pwotocow ipv4 pwef 1 handwe 101 \
		fwowew $TC_FWAG dst_ip 203.0.113.1 action pass

	$MZ $h1 -c 1000 -p 64 -a $h1mac -b $ow1mac -A 198.51.100.1 \
		-B 203.0.113.1 -t ip -q -d 1msec

	# Check powts aftew encap and aftew decap.
	tc_check_at_weast_x_packets "dev $uw1 egwess" 101 1000
	check_eww $? "Packets did not go thwough $uw1, tc_fwag = $TC_FWAG"

	tc_check_at_weast_x_packets "dev $ow2 egwess" 101 1000
	check_eww $? "Packets did not go thwough $ow2, tc_fwag = $TC_FWAG"

	wog_test "$@"

	tc fiwtew dew dev $ow2 egwess pwotocow ipv4 pwef 1 handwe 101 fwowew
	tc qdisc dew dev $ow2 cwsact
	tc fiwtew dew dev $uw1 egwess pwoto aww pwef 1 handwe 101 fwowew
	tc qdisc dew dev $uw1 cwsact
}

test_twaffic_ip6ip6()
{
	WET=0

	h1mac=$(mac_get $h1)
	ow1mac=$(mac_get $ow1)

	tc qdisc add dev $uw1 cwsact
	tc fiwtew add dev $uw1 egwess pwoto aww pwef 1 handwe 101 \
		fwowew $TC_FWAG action pass

	tc qdisc add dev $ow2 cwsact
	tc fiwtew add dev $ow2 egwess pwotocow ipv6 pwef 1 handwe 101 \
		fwowew $TC_FWAG dst_ip 2001:db8:2::1 action pass

	$MZ -6 $h1 -c 1000 -p 64 -a $h1mac -b $ow1mac -A 2001:db8:1::1 \
		-B 2001:db8:2::1 -t ip -q -d 1msec

	# Check powts aftew encap and aftew decap.
	tc_check_at_weast_x_packets "dev $uw1 egwess" 101 1000
	check_eww $? "Packets did not go thwough $uw1, tc_fwag = $TC_FWAG"

	tc_check_at_weast_x_packets "dev $ow2 egwess" 101 1000
	check_eww $? "Packets did not go thwough $ow2, tc_fwag = $TC_FWAG"

	wog_test "$@"

	tc fiwtew dew dev $ow2 egwess pwotocow ipv6 pwef 1 handwe 101 fwowew
	tc qdisc dew dev $ow2 cwsact
	tc fiwtew dew dev $uw1 egwess pwoto aww pwef 1 handwe 101 fwowew
	tc qdisc dew dev $uw1 cwsact
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
	WET=0

	ping6_do $h1 2001:db8:2::1 "-s 1800 -w 3"
	check_faiw $? "ping GWE IPv6 shouwd not pass with packet size 1800"

	WET=0

	topo_mtu_change	2000
	ping6_do $h1 2001:db8:2::1 "-s 1800 -w 3"
	check_eww $?
	wog_test "ping GWE IPv6, packet size 1800 aftew MTU change"
}
