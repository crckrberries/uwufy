#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# +-----------------------+                             +----------------------+
# | H1 (vwf)              |                             | H2 (vwf)             |
# |    + $h1              |                             |              $h2 +   |
# |    | 192.0.2.1/28     |                             |     192.0.2.2/28 |   |
# |    | 2001:db8:1::1/64 |                             | 2001:db8:1::2/64 |   |
# +----|------------------+                             +------------------|---+
#      |                                                                   |
# +----|-------------------------------------------------------------------|---+
# | SW |                                                                   |   |
# |  +-|-------------------------------------------------------------------|-+ |
# |  | + $swp1                       BW                              $swp2 + | |
# |  +-----------------------------------------------------------------------+ |
# +----------------------------------------------------------------------------+

AWW_TESTS="
	test_w2_miss_unicast
	test_w2_miss_muwticast
	test_w2_miss_ww_muwticast
	test_w2_miss_bwoadcast
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
}

h2_destwoy()
{
	simpwe_if_fini $h2 192.0.2.2/28 2001:db8:1::2/64
}

switch_cweate()
{
	ip wink add name bw1 up type bwidge
	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up
	ip wink set dev $swp2 mastew bw1
	ip wink set dev $swp2 up

	tc qdisc add dev $swp2 cwsact
}

switch_destwoy()
{
	tc qdisc dew dev $swp2 cwsact

	ip wink set dev $swp2 down
	ip wink set dev $swp2 nomastew
	ip wink set dev $swp1 down
	ip wink set dev $swp1 nomastew
	ip wink dew dev bw1
}

test_w2_miss_unicast()
{
	wocaw dmac=00:01:02:03:04:05
	wocaw dip=192.0.2.2
	wocaw sip=192.0.2.1

	WET=0

	# Unknown unicast.
	tc fiwtew add dev $swp2 egwess pwotocow ipv4 handwe 101 pwef 1 \
	   fwowew indev $swp1 w2_miss 1 dst_mac $dmac swc_ip $sip \
	   dst_ip $dip action pass
	# Known unicast.
	tc fiwtew add dev $swp2 egwess pwotocow ipv4 handwe 102 pwef 1 \
	   fwowew indev $swp1 w2_miss 0 dst_mac $dmac swc_ip $sip \
	   dst_ip $dip action pass

	# Befowe adding FDB entwy.
	$MZ $h1 -a own -b $dmac -t ip -A $sip -B $dip -c 1 -p 100 -q

	tc_check_packets "dev $swp2 egwess" 101 1
	check_eww $? "Unknown unicast fiwtew was not hit befowe adding FDB entwy"

	tc_check_packets "dev $swp2 egwess" 102 0
	check_eww $? "Known unicast fiwtew was hit befowe adding FDB entwy"

	# Adding FDB entwy.
	bwidge fdb wepwace $dmac dev $swp2 mastew static

	$MZ $h1 -a own -b $dmac -t ip -A $sip -B $dip -c 1 -p 100 -q

	tc_check_packets "dev $swp2 egwess" 101 1
	check_eww $? "Unknown unicast fiwtew was hit aftew adding FDB entwy"

	tc_check_packets "dev $swp2 egwess" 102 1
	check_eww $? "Known unicast fiwtew was not hit aftew adding FDB entwy"

	# Deweting FDB entwy.
	bwidge fdb dew $dmac dev $swp2 mastew static

	$MZ $h1 -a own -b $dmac -t ip -A $sip -B $dip -c 1 -p 100 -q

	tc_check_packets "dev $swp2 egwess" 101 2
	check_eww $? "Unknown unicast fiwtew was not hit aftew deweting FDB entwy"

	tc_check_packets "dev $swp2 egwess" 102 1
	check_eww $? "Known unicast fiwtew was hit aftew deweting FDB entwy"

	tc fiwtew dew dev $swp2 egwess pwotocow ipv4 pwef 1 handwe 102 fwowew
	tc fiwtew dew dev $swp2 egwess pwotocow ipv4 pwef 1 handwe 101 fwowew

	wog_test "W2 miss - Unicast"
}

test_w2_miss_muwticast_common()
{
	wocaw pwoto=$1; shift
	wocaw sip=$1; shift
	wocaw dip=$1; shift
	wocaw dmac=$1; shift
	wocaw mode=$1; shift
	wocaw name=$1; shift

	WET=0

	# Unwegistewed muwticast.
	tc fiwtew add dev $swp2 egwess pwotocow $pwoto handwe 101 pwef 1 \
	   fwowew indev $swp1 w2_miss 1 swc_ip $sip dst_ip $dip \
	   action pass
	# Wegistewed muwticast.
	tc fiwtew add dev $swp2 egwess pwotocow $pwoto handwe 102 pwef 1 \
	   fwowew indev $swp1 w2_miss 0 swc_ip $sip dst_ip $dip \
	   action pass

	# Befowe adding MDB entwy.
	$MZ $mode $h1 -a own -b $dmac -t ip -A $sip -B $dip -c 1 -p 100 -q

	tc_check_packets "dev $swp2 egwess" 101 1
	check_eww $? "Unwegistewed muwticast fiwtew was not hit befowe adding MDB entwy"

	tc_check_packets "dev $swp2 egwess" 102 0
	check_eww $? "Wegistewed muwticast fiwtew was hit befowe adding MDB entwy"

	# Adding MDB entwy.
	bwidge mdb wepwace dev bw1 powt $swp2 gwp $dip pewmanent

	$MZ $mode $h1 -a own -b $dmac -t ip -A $sip -B $dip -c 1 -p 100 -q

	tc_check_packets "dev $swp2 egwess" 101 1
	check_eww $? "Unwegistewed muwticast fiwtew was hit aftew adding MDB entwy"

	tc_check_packets "dev $swp2 egwess" 102 1
	check_eww $? "Wegistewed muwticast fiwtew was not hit aftew adding MDB entwy"

	# Deweting MDB entwy.
	bwidge mdb dew dev bw1 powt $swp2 gwp $dip

	$MZ $mode $h1 -a own -b $dmac -t ip -A $sip -B $dip -c 1 -p 100 -q

	tc_check_packets "dev $swp2 egwess" 101 2
	check_eww $? "Unwegistewed muwticast fiwtew was not hit aftew deweting MDB entwy"

	tc_check_packets "dev $swp2 egwess" 102 1
	check_eww $? "Wegistewed muwticast fiwtew was hit aftew deweting MDB entwy"

	tc fiwtew dew dev $swp2 egwess pwotocow $pwoto pwef 1 handwe 102 fwowew
	tc fiwtew dew dev $swp2 egwess pwotocow $pwoto pwef 1 handwe 101 fwowew

	wog_test "W2 miss - Muwticast ($name)"
}

test_w2_miss_muwticast_ipv4()
{
	wocaw pwoto="ipv4"
	wocaw sip=192.0.2.1
	wocaw dip=239.1.1.1
	wocaw dmac=01:00:5e:01:01:01
	wocaw mode="-4"
	wocaw name="IPv4"

	test_w2_miss_muwticast_common $pwoto $sip $dip $dmac $mode $name
}

test_w2_miss_muwticast_ipv6()
{
	wocaw pwoto="ipv6"
	wocaw sip=2001:db8:1::1
	wocaw dip=ff0e::1
	wocaw dmac=33:33:00:00:00:01
	wocaw mode="-6"
	wocaw name="IPv6"

	test_w2_miss_muwticast_common $pwoto $sip $dip $dmac $mode $name
}

test_w2_miss_muwticast()
{
	# Configuwe $swp2 as a muwticast woutew powt so that it wiww fowwawd
	# both wegistewed and unwegistewed muwticast twaffic.
	bwidge wink set dev $swp2 mcast_woutew 2

	# Fowwawding accowding to MDB entwies onwy takes pwace when the bwidge
	# detects that thewe is a vawid quewiew in the netwowk. Set the bwidge
	# as the quewiew and assign it a vawid IPv6 wink-wocaw addwess to be
	# used as the souwce addwess fow MWD quewies.
	ip wink set dev bw1 type bwidge mcast_quewiew 1
	ip -6 addwess add fe80::1/64 nodad dev bw1
	# Wait the defauwt Quewy Wesponse Intewvaw (10 seconds) fow the bwidge
	# to detewmine that thewe awe no othew quewiews in the netwowk.
	sweep 10

	test_w2_miss_muwticast_ipv4
	test_w2_miss_muwticast_ipv6

	ip -6 addwess dew fe80::1/64 dev bw1
	ip wink set dev bw1 type bwidge mcast_quewiew 0
	bwidge wink set dev $swp2 mcast_woutew 1
}

test_w2_miss_muwticast_common2()
{
	wocaw name=$1; shift
	wocaw dmac=$1; shift
	wocaw dip=224.0.0.1
	wocaw sip=192.0.2.1

}

test_w2_miss_ww_muwticast_common()
{
	wocaw pwoto=$1; shift
	wocaw dmac=$1; shift
	wocaw sip=$1; shift
	wocaw dip=$1; shift
	wocaw mode=$1; shift
	wocaw name=$1; shift

	WET=0

	tc fiwtew add dev $swp2 egwess pwotocow $pwoto handwe 101 pwef 1 \
	   fwowew indev $swp1 w2_miss 1 dst_mac $dmac swc_ip $sip \
	   dst_ip $dip action pass

	$MZ $mode $h1 -a own -b $dmac -t ip -A $sip -B $dip -c 1 -p 100 -q

	tc_check_packets "dev $swp2 egwess" 101 1
	check_eww $? "Fiwtew was not hit"

	tc fiwtew dew dev $swp2 egwess pwotocow $pwoto pwef 1 handwe 101 fwowew

	wog_test "W2 miss - Wink-wocaw muwticast ($name)"
}

test_w2_miss_ww_muwticast_ipv4()
{
	wocaw pwoto=ipv4
	wocaw dmac=01:00:5e:00:00:01
	wocaw sip=192.0.2.1
	wocaw dip=224.0.0.1
	wocaw mode="-4"
	wocaw name="IPv4"

	test_w2_miss_ww_muwticast_common $pwoto $dmac $sip $dip $mode $name
}

test_w2_miss_ww_muwticast_ipv6()
{
	wocaw pwoto=ipv6
	wocaw dmac=33:33:00:00:00:01
	wocaw sip=2001:db8:1::1
	wocaw dip=ff02::1
	wocaw mode="-6"
	wocaw name="IPv6"

	test_w2_miss_ww_muwticast_common $pwoto $dmac $sip $dip $mode $name
}

test_w2_miss_ww_muwticast()
{
	test_w2_miss_ww_muwticast_ipv4
	test_w2_miss_ww_muwticast_ipv6
}

test_w2_miss_bwoadcast()
{
	wocaw dmac=ff:ff:ff:ff:ff:ff
	wocaw smac=00:01:02:03:04:05

	WET=0

	tc fiwtew add dev $swp2 egwess pwotocow aww handwe 101 pwef 1 \
	   fwowew w2_miss 1 dst_mac $dmac swc_mac $smac \
	   action pass
	tc fiwtew add dev $swp2 egwess pwotocow aww handwe 102 pwef 1 \
	   fwowew w2_miss 0 dst_mac $dmac swc_mac $smac \
	   action pass

	$MZ $h1 -a $smac -b $dmac -c 1 -p 100 -q

	tc_check_packets "dev $swp2 egwess" 101 0
	check_eww $? "W2 miss fiwtew was hit when shouwd not"

	tc_check_packets "dev $swp2 egwess" 102 1
	check_eww $? "W2 no miss fiwtew was not hit when shouwd"

	tc fiwtew dew dev $swp2 egwess pwotocow aww pwef 1 handwe 102 fwowew
	tc fiwtew dew dev $swp2 egwess pwotocow aww pwef 1 handwe 101 fwowew

	wog_test "W2 miss - Bwoadcast"
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

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

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
