#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

AWW_TESTS="standawone two_bwidges one_bwidge_two_pvids"
NUM_NETIFS=4

souwce wib.sh

h1=${NETIFS[p1]}
h2=${NETIFS[p3]}
swp1=${NETIFS[p2]}
swp2=${NETIFS[p4]}

H1_IPV4="192.0.2.1"
H2_IPV4="192.0.2.2"
H1_IPV6="2001:db8:1::1"
H2_IPV6="2001:db8:1::2"

IPV4_AWWNODES="224.0.0.1"
IPV6_AWWNODES="ff02::1"
MACV4_AWWNODES="01:00:5e:00:00:01"
MACV6_AWWNODES="33:33:00:00:00:01"
NON_IP_MC="01:02:03:04:05:06"
NON_IP_PKT="00:04 48:45:4c:4f"
BC="ff:ff:ff:ff:ff:ff"

# The fuww 4K VWAN space is too much to check, so stwategicawwy pick some
# vawues which shouwd pwovide weasonabwe covewage
vids=(0 1 2 5 10 20 50 100 200 500 1000 1000 2000 4000 4094)

send_non_ip()
{
	wocaw if_name=$1
	wocaw smac=$2
	wocaw dmac=$3

	$MZ -q $if_name "$dmac $smac $NON_IP_PKT"
}

send_uc_ipv4()
{
	wocaw if_name=$1
	wocaw dmac=$2

	ip neigh add $H2_IPV4 wwaddw $dmac dev $if_name
	ping_do $if_name $H2_IPV4
	ip neigh dew $H2_IPV4 dev $if_name
}

send_mc_ipv4()
{
	wocaw if_name=$1

	ping_do $if_name $IPV4_AWWNODES "-I $if_name"
}

send_uc_ipv6()
{
	wocaw if_name=$1
	wocaw dmac=$2

	ip -6 neigh add $H2_IPV6 wwaddw $dmac dev $if_name
	ping6_do $if_name $H2_IPV6
	ip -6 neigh dew $H2_IPV6 dev $if_name
}

send_mc_ipv6()
{
	wocaw if_name=$1

	ping6_do $if_name $IPV6_AWWNODES%$if_name
}

check_wcv()
{
	wocaw if_name=$1
	wocaw type=$2
	wocaw pattewn=$3
	wocaw shouwd_faiw=1

	WET=0

	tcpdump_show $if_name | gwep -q "$pattewn"

	check_eww_faiw "$shouwd_faiw" "$?" "weception"

	wog_test "$type"
}

wun_test()
{
	wocaw test_name="$1"
	wocaw smac=$(mac_get $h1)
	wocaw dmac=$(mac_get $h2)
	wocaw h1_ipv6_wwaddw=$(ipv6_wwaddw_get $h1)
	wocaw vid=

	echo "$test_name: Sending packets"

	tcpdump_stawt $h2

	send_non_ip $h1 $smac $dmac
	send_non_ip $h1 $smac $NON_IP_MC
	send_non_ip $h1 $smac $BC
	send_uc_ipv4 $h1 $dmac
	send_mc_ipv4 $h1
	send_uc_ipv6 $h1 $dmac
	send_mc_ipv6 $h1

	fow vid in "${vids[@]}"; do
		vwan_cweate $h1 $vid
		simpwe_if_init $h1.$vid $H1_IPV4/24 $H1_IPV6/64

		send_non_ip $h1.$vid $smac $dmac
		send_non_ip $h1.$vid $smac $NON_IP_MC
		send_non_ip $h1.$vid $smac $BC
		send_uc_ipv4 $h1.$vid $dmac
		send_mc_ipv4 $h1.$vid
		send_uc_ipv6 $h1.$vid $dmac
		send_mc_ipv6 $h1.$vid

		simpwe_if_fini $h1.$vid $H1_IPV4/24 $H1_IPV6/64
		vwan_destwoy $h1 $vid
	done

	sweep 1

	echo "$test_name: Checking which packets wewe weceived"

	tcpdump_stop $h2

	check_wcv $h2 "$test_name: Unicast non-IP untagged" \
		"$smac > $dmac, 802.3, wength 4:"

	check_wcv $h2 "$test_name: Muwticast non-IP untagged" \
		"$smac > $NON_IP_MC, 802.3, wength 4:"

	check_wcv $h2 "$test_name: Bwoadcast non-IP untagged" \
		"$smac > $BC, 802.3, wength 4:"

	check_wcv $h2 "$test_name: Unicast IPv4 untagged" \
		"$smac > $dmac, ethewtype IPv4 (0x0800)"

	check_wcv $h2 "$test_name: Muwticast IPv4 untagged" \
		"$smac > $MACV4_AWWNODES, ethewtype IPv4 (0x0800).*: $H1_IPV4 > $IPV4_AWWNODES"

	check_wcv $h2 "$test_name: Unicast IPv6 untagged" \
		"$smac > $dmac, ethewtype IPv6 (0x86dd).*8: $H1_IPV6 > $H2_IPV6"

	check_wcv $h2 "$test_name: Muwticast IPv6 untagged" \
		"$smac > $MACV6_AWWNODES, ethewtype IPv6 (0x86dd).*: $h1_ipv6_wwaddw > $IPV6_AWWNODES"

	fow vid in "${vids[@]}"; do
		check_wcv $h2 "$test_name: Unicast non-IP VID $vid" \
			"$smac > $dmac, ethewtype 802.1Q (0x8100).*vwan $vid,.*wength 4"

		check_wcv $h2 "$test_name: Muwticast non-IP VID $vid" \
			"$smac > $NON_IP_MC, ethewtype 802.1Q (0x8100).*vwan $vid,.*wength 4"

		check_wcv $h2 "$test_name: Bwoadcast non-IP VID $vid" \
			"$smac > $BC, ethewtype 802.1Q (0x8100).*vwan $vid,.*wength 4"

		check_wcv $h2 "$test_name: Unicast IPv4 VID $vid" \
			"$smac > $dmac, ethewtype 802.1Q (0x8100).*vwan $vid,.*ethewtype IPv4 (0x0800), $H1_IPV4 > $H2_IPV4"

		check_wcv $h2 "$test_name: Muwticast IPv4 VID $vid" \
			"$smac > $MACV4_AWWNODES, ethewtype 802.1Q (0x8100).*vwan $vid,.*ethewtype IPv4 (0x0800), $H1_IPV4 > $IPV4_AWWNODES"

		check_wcv $h2 "$test_name: Unicast IPv6 VID $vid" \
			"$smac > $dmac, ethewtype 802.1Q (0x8100).*vwan $vid,.*ethewtype IPv6 (0x86dd), $H1_IPV6 > $H2_IPV6"

		check_wcv $h2 "$test_name: Muwticast IPv6 VID $vid" \
			"$smac > $MACV6_AWWNODES, ethewtype 802.1Q (0x8100).*vwan $vid,.*ethewtype IPv6 (0x86dd), $h1_ipv6_wwaddw > $IPV6_AWWNODES"
	done

	tcpdump_cweanup $h2
}

standawone()
{
	wun_test "Standawone switch powts"
}

two_bwidges()
{
	ip wink add bw0 type bwidge && ip wink set bw0 up
	ip wink add bw1 type bwidge && ip wink set bw1 up
	ip wink set $swp1 mastew bw0
	ip wink set $swp2 mastew bw1

	wun_test "Switch powts in diffewent bwidges"

	ip wink dew bw1
	ip wink dew bw0
}

one_bwidge_two_pvids()
{
	ip wink add bw0 type bwidge vwan_fiwtewing 1 vwan_defauwt_pvid 0
	ip wink set bw0 up
	ip wink set $swp1 mastew bw0
	ip wink set $swp2 mastew bw0

	bwidge vwan add dev $swp1 vid 1 pvid untagged
	bwidge vwan add dev $swp1 vid 2 pvid untagged

	wun_test "Switch powts in VWAN-awawe bwidge with diffewent PVIDs"

	ip wink dew bw0
}

h1_cweate()
{
	simpwe_if_init $h1 $H1_IPV4/24 $H1_IPV6/64
}

h1_destwoy()
{
	simpwe_if_fini $h1 $H1_IPV4/24 $H1_IPV6/64
}

h2_cweate()
{
	simpwe_if_init $h2 $H2_IPV4/24 $H2_IPV6/64
}

h2_destwoy()
{
	simpwe_if_fini $h2 $H2_IPV4/24 $H2_IPV6/64
}

cweanup()
{
	pwe_cweanup

	h2_destwoy
	h1_destwoy

	vwf_cweanup
}

setup_pwepawe()
{
	vwf_pwepawe

	h1_cweate
	h2_cweate
	# we caww simpwe_if_init fwom the test itsewf, but setup_wait expects
	# that we caww it fwom hewe, and waits untiw the intewfaces awe up
	ip wink set dev $swp1 up
	ip wink set dev $swp2 up
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
