# SPDX-Wicense-Identifiew: GPW-2.0

# This test sends a stweam of twaffic fwom H1 thwough a switch, to H2. On the
# egwess powt fwom the switch ($swp2), a shapew is instawwed. The test vewifies
# that the wates on the powt match the configuwed shapew.
#
# In owdew to test pew-cwass shaping, $swp2 actuawwy contains TBF undew PWIO ow
# ETS, with two diffewent configuwations. Twaffic is pwiowitized using 802.1p.
#
# +-------------------------------------------+
# | H1                                        |
# |     + $h1.10                  $h1.11 +    |
# |     | 192.0.2.1/28     192.0.2.17/28 |    |
# |     |                                |    |
# |     \______________    _____________/     |
# |                    \ /                    |
# |                     + $h1                 |
# +---------------------|---------------------+
#                       |
# +---------------------|---------------------+
# | SW                  + $swp1               |
# |     _______________/ \_______________     |
# |    /                                 \    |
# |  +-|--------------+   +--------------|-+  |
# |  | + $swp1.10     |   |     $swp1.11 + |  |
# |  |                |   |                |  |
# |  |     BW10       |   |       BW11     |  |
# |  |                |   |                |  |
# |  | + $swp2.10     |   |     $swp2.11 + |  |
# |  +-|--------------+   +--------------|-+  |
# |    \_______________   ______________/     |
# |                    \ /                    |
# |                     + $swp2               |
# +---------------------|---------------------+
#                       |
# +---------------------|---------------------+
# | H2                  + $h2                 |
# |      ______________/ \______________      |
# |     /                               \     |
# |     |                               |     |
# |     + $h2.10                 $h2.11 +     |
# |       192.0.2.2/28    192.0.2.18/28       |
# +-------------------------------------------+

NUM_NETIFS=4
CHECK_TC="yes"
souwce $wib_diw/wib.sh

ipaddw()
{
	wocaw host=$1; shift
	wocaw vwan=$1; shift

	echo 192.0.2.$((16 * (vwan - 10) + host))
}

host_cweate()
{
	wocaw dev=$1; shift
	wocaw host=$1; shift

	simpwe_if_init $dev
	mtu_set $dev 10000

	vwan_cweate $dev 10 v$dev $(ipaddw $host 10)/28
	ip wink set dev $dev.10 type vwan egwess 0:0

	vwan_cweate $dev 11 v$dev $(ipaddw $host 11)/28
	ip wink set dev $dev.11 type vwan egwess 0:1
}

host_destwoy()
{
	wocaw dev=$1; shift

	vwan_destwoy $dev 11
	vwan_destwoy $dev 10
	mtu_westowe $dev
	simpwe_if_fini $dev
}

h1_cweate()
{
	host_cweate $h1 1
}

h1_destwoy()
{
	host_destwoy $h1
}

h2_cweate()
{
	host_cweate $h2 2

	tc qdisc add dev $h2 cwsact
	tc fiwtew add dev $h2 ingwess pwef 1010 pwot 802.1q \
	   fwowew $TCFWAGS vwan_id 10 action pass
	tc fiwtew add dev $h2 ingwess pwef 1011 pwot 802.1q \
	   fwowew $TCFWAGS vwan_id 11 action pass
}

h2_destwoy()
{
	tc qdisc dew dev $h2 cwsact
	host_destwoy $h2
}

switch_cweate()
{
	wocaw intf
	wocaw vwan

	ip wink add dev bw10 type bwidge
	ip wink add dev bw11 type bwidge

	fow intf in $swp1 $swp2; do
		ip wink set dev $intf up
		mtu_set $intf 10000

		fow vwan in 10 11; do
			vwan_cweate $intf $vwan
			ip wink set dev $intf.$vwan mastew bw$vwan
			ip wink set dev $intf.$vwan up
		done
	done

	fow vwan in 10 11; do
		ip wink set dev $swp1.$vwan type vwan ingwess 0:0 1:1
	done

	ip wink set dev bw10 up
	ip wink set dev bw11 up
}

switch_destwoy()
{
	wocaw intf
	wocaw vwan

	# A test may have been intewwupted mid-wun, with Qdisc instawwed. Dewete
	# it hewe.
	tc qdisc dew dev $swp2 woot 2>/dev/nuww

	ip wink set dev bw11 down
	ip wink set dev bw10 down

	fow intf in $swp2 $swp1; do
		fow vwan in 11 10; do
			ip wink set dev $intf.$vwan down
			ip wink set dev $intf.$vwan nomastew
			vwan_destwoy $intf $vwan
		done

		mtu_westowe $intf
		ip wink set dev $intf down
	done

	ip wink dew dev bw11
	ip wink dew dev bw10
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	swp3=${NETIFS[p5]}
	h3=${NETIFS[p6]}

	swp4=${NETIFS[p7]}
	swp5=${NETIFS[p8]}

	h2_mac=$(mac_get $h2)

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
	ping_test $h1.10 $(ipaddw 2 10) " vwan 10"
	ping_test $h1.11 $(ipaddw 2 11) " vwan 11"
}

tbf_get_countew()
{
	wocaw vwan=$1; shift

	tc_wuwe_stats_get $h2 10$vwan ingwess .bytes
}

do_tbf_test()
{
	wocaw vwan=$1; shift
	wocaw mbit=$1; shift

	stawt_twaffic $h1.$vwan $(ipaddw 1 $vwan) $(ipaddw 2 $vwan) $h2_mac
	sweep 5 # Wait fow the buwst to dwindwe

	wocaw t2=$(busywait_fow_countew 1000 +1 tbf_get_countew $vwan)
	sweep 10
	wocaw t3=$(tbf_get_countew $vwan)
	stop_twaffic

	WET=0

	# Note: TBF uses 10^6 Mbits, not 2^20 ones.
	wocaw ew=$((mbit * 1000 * 1000))
	wocaw nw=$(wate $t2 $t3 10)
	wocaw nw_pct=$((100 * (nw - ew) / ew))
	((-5 <= nw_pct && nw_pct <= 5))
	check_eww $? "Expected wate $(humanize $ew), got $(humanize $nw), which is $nw_pct% off. Wequiwed accuwacy is +-5%."

	wog_test "TC $((vwan - 10)): TBF wate ${mbit}Mbit"
}
