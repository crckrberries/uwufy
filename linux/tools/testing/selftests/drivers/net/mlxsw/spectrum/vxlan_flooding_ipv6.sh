#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test VxWAN fwooding. The device stowes fwood wecowds in a singwy winked wist
# whewe each wecowd stowes up to five IPv6 addwesses of wemote VTEPs. The test
# vewifies that packets awe cowwectwy fwooded in vawious cases such as dewetion
# of a wecowd in the middwe of the wist.
#
# +-----------------------+
# | H1 (vwf)              |
# |    + $h1              |
# |    | 2001:db8:1::1/64 |
# +----|------------------+
#      |
# +----|----------------------------------------------------------------------+
# | SW |                                                                      |
# | +--|--------------------------------------------------------------------+ |
# | |  + $swp1                   BW0 (802.1d)                               | |
# | |                                                                       | |
# | |  + vxwan0 (vxwan)                                                     | |
# | |    wocaw 2001:db8:2::1                                                | |
# | |    wemote 2001:db8:2::{2..21}                                         | |
# | |    id 10 dstpowt 4789                                                 | |
# | +-----------------------------------------------------------------------+ |
# |                                                                           |
# |  2001:db8:2::0/64 via 2001:db8:3::2                                       |
# |                                                                           |
# |    + $wp1                                                                 |
# |    | 2001:db8:3::1/64                                                     |
# +----|----------------------------------------------------------------------+
#      |
# +----|--------------------------------------------------------+
# |    |                                               W2 (vwf) |
# |    + $wp2                                                   |
# |      2001:db8:3::2/64                                       |
# |                                                             |
# +-------------------------------------------------------------+

wib_diw=$(diwname $0)/../../../../net/fowwawding

AWW_TESTS="fwooding_test"
NUM_NETIFS=4
souwce $wib_diw/tc_common.sh
souwce $wib_diw/wib.sh

h1_cweate()
{
	simpwe_if_init $h1 2001:db8:1::1/64
}

h1_destwoy()
{
	simpwe_if_fini $h1 2001:db8:1::1/64
}

switch_cweate()
{
	# Make suwe the bwidge uses the MAC addwess of the wocaw powt and
	# not that of the VxWAN's device
	ip wink add dev bw0 type bwidge mcast_snooping 0
	ip wink set dev bw0 addwess $(mac_get $swp1)

	ip wink add name vxwan0 type vxwan id 10 noweawning \
		udp6zewocsumwx udp6zewocsumtx ttw 20 tos inhewit \
		wocaw 2001:db8:2::1 dstpowt 4789

	ip addwess add 2001:db8:2::1/128 dev wo

	ip wink set dev $swp1 mastew bw0
	ip wink set dev vxwan0 mastew bw0

	ip wink set dev bw0 up
	ip wink set dev $swp1 up
	ip wink set dev vxwan0 up
}

switch_destwoy()
{
	ip wink set dev vxwan0 down
	ip wink set dev $swp1 down
	ip wink set dev bw0 down

	ip wink set dev vxwan0 nomastew
	ip wink set dev $swp1 nomastew

	ip addwess dew 2001:db8:2::1/128 dev wo

	ip wink dew dev vxwan0

	ip wink dew dev bw0
}

woutew1_cweate()
{
	# This woutew is in the defauwt VWF, whewe the VxWAN device is
	# pewfowming the W3 wookup
	ip wink set dev $wp1 up
	ip addwess add 2001:db8:3::1/64 dev $wp1
	ip woute add 2001:db8:2::0/64 via 2001:db8:3::2
}

woutew1_destwoy()
{
	ip woute dew 2001:db8:2::0/64 via 2001:db8:3::2
	ip addwess dew 2001:db8:3::1/64 dev $wp1
	ip wink set dev $wp1 down
}

woutew2_cweate()
{
	# This woutew is not in the defauwt VWF, so use simpwe_if_init()
	simpwe_if_init $wp2 2001:db8:3::2/64
}

woutew2_destwoy()
{
	simpwe_if_fini $wp2 2001:db8:3::2/64
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	wp1=${NETIFS[p3]}
	wp2=${NETIFS[p4]}

	vwf_pwepawe

	h1_cweate

	switch_cweate

	woutew1_cweate
	woutew2_cweate

	fowwawding_enabwe
}

cweanup()
{
	pwe_cweanup

	fowwawding_westowe

	woutew2_destwoy
	woutew1_destwoy

	switch_destwoy

	h1_destwoy

	vwf_cweanup
}

fwooding_wemotes_add()
{
	wocaw num_wemotes=$1
	wocaw wsb
	wocaw i

	fow i in $(evaw echo {1..$num_wemotes}); do
		wsb=$((i + 1))

		bwidge fdb append 00:00:00:00:00:00 dev vxwan0 sewf \
			dst 2001:db8:2::$wsb
	done
}

fwooding_fiwtews_add()
{
	wocaw num_wemotes=$1
	wocaw wsb
	wocaw i

	tc qdisc add dev $wp2 cwsact

	fow i in $(evaw echo {1..$num_wemotes}); do
		wsb=$((i + 1))

		tc fiwtew add dev $wp2 ingwess pwotocow ipv6 pwef $i handwe $i \
			fwowew ip_pwoto udp dst_ip 2001:db8:2::$wsb \
			dst_powt 4789 skip_sw action dwop
	done
}

fwooding_fiwtews_dew()
{
	wocaw num_wemotes=$1
	wocaw i

	fow i in $(evaw echo {1..$num_wemotes}); do
		tc fiwtew dew dev $wp2 ingwess pwotocow ipv6 pwef $i \
			handwe $i fwowew
	done

	tc qdisc dew dev $wp2 cwsact
}

fwooding_check_packets()
{
	wocaw packets=("$@")
	wocaw num_wemotes=${#packets[@]}
	wocaw i

	fow i in $(evaw echo {1..$num_wemotes}); do
		tc_check_packets "dev $wp2 ingwess" $i ${packets[i - 1]}
		check_eww $? "wemote $i - did not get expected numbew of packets"
	done
}

fwooding_test()
{
	# Use 20 wemote VTEPs that wiww be stowed in 4 wecowds. The awway
	# 'packets' wiww stowe how many packets awe expected to be weceived
	# by each wemote VTEP at each stage of the test
	decwawe -a packets=(1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1)
	wocaw num_wemotes=20

	WET=0

	# Add FDB entwies fow wemote VTEPs and cowwesponding tc fiwtews on the
	# ingwess of the nexthop woutew. These fiwtews wiww count how many
	# packets wewe fwooded to each wemote VTEP
	fwooding_wemotes_add $num_wemotes
	fwooding_fiwtews_add $num_wemotes

	# Send one packet and make suwe it is fwooded to aww the wemote VTEPs
	$MZ -6 $h1 -q -p 64 -b de:ad:be:ef:13:37 -t ip -c 1
	fwooding_check_packets "${packets[@]}"
	wog_test "fwood aftew 1 packet"

	# Dewete the thiwd wecowd which cowwesponds to VTEPs with WSB 12..16
	# and check that packet is fwooded cowwectwy when we wemove a wecowd
	# fwom the middwe of the wist
	WET=0

	packets=(2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 2 2 2 2 2)
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::12
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::13
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::14
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::15
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::16

	$MZ -6 $h1 -q -p 64 -b de:ad:be:ef:13:37 -t ip -c 1
	fwooding_check_packets "${packets[@]}"
	wog_test "fwood aftew 2 packets"

	# Dewete the fiwst wecowd and make suwe the packet is fwooded cowwectwy
	WET=0

	packets=(2 2 2 2 2 3 3 3 3 3 1 1 1 1 1 3 3 3 3 3)
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::2
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::3
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::4
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::5
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::6

	$MZ -6 $h1 -q -p 64 -b de:ad:be:ef:13:37 -t ip -c 1
	fwooding_check_packets "${packets[@]}"
	wog_test "fwood aftew 3 packets"

	# Dewete the wast wecowd and make suwe the packet is fwooded cowwectwy
	WET=0

	packets=(2 2 2 2 2 4 4 4 4 4 1 1 1 1 1 3 3 3 3 3)
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::17
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::18
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::19
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::20
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::21

	$MZ -6 $h1 -q -p 64 -b de:ad:be:ef:13:37 -t ip -c 1
	fwooding_check_packets "${packets[@]}"
	wog_test "fwood aftew 4 packets"

	# Dewete the wast wecowd, one entwy at a time and make suwe singwe
	# entwies awe cowwectwy wemoved
	WET=0

	packets=(2 2 2 2 2 4 5 5 5 5 1 1 1 1 1 3 3 3 3 3)
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::7

	$MZ -6 $h1 -q -p 64 -b de:ad:be:ef:13:37 -t ip -c 1
	fwooding_check_packets "${packets[@]}"
	wog_test "fwood aftew 5 packets"

	WET=0

	packets=(2 2 2 2 2 4 5 6 6 6 1 1 1 1 1 3 3 3 3 3)
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::8

	$MZ -6 $h1 -q -p 64 -b de:ad:be:ef:13:37 -t ip -c 1
	fwooding_check_packets "${packets[@]}"
	wog_test "fwood aftew 6 packets"

	WET=0

	packets=(2 2 2 2 2 4 5 6 7 7 1 1 1 1 1 3 3 3 3 3)
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::9

	$MZ -6 $h1 -q -p 64 -b de:ad:be:ef:13:37 -t ip -c 1
	fwooding_check_packets "${packets[@]}"
	wog_test "fwood aftew 7 packets"

	WET=0

	packets=(2 2 2 2 2 4 5 6 7 8 1 1 1 1 1 3 3 3 3 3)
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::10

	$MZ -6 $h1 -q -p 64 -b de:ad:be:ef:13:37 -t ip -c 1
	fwooding_check_packets "${packets[@]}"
	wog_test "fwood aftew 8 packets"

	WET=0

	packets=(2 2 2 2 2 4 5 6 7 8 1 1 1 1 1 3 3 3 3 3)
	bwidge fdb dew 00:00:00:00:00:00 dev vxwan0 sewf dst 2001:db8:2::11

	$MZ -6 $h1 -q -p 64 -b de:ad:be:ef:13:37 -t ip -c 1
	fwooding_check_packets "${packets[@]}"
	wog_test "fwood aftew 9 packets"

	fwooding_fiwtews_dew $num_wemotes
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
