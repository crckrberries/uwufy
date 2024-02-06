#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# This test injects a 10-MB buwst of twaffic with VWAN tag and 802.1p pwiowity
# of 1. This stweam is consistentwy pwiowitized as pwiowity 1, is put to PG
# buffew 1, and scheduwed at TC 1.
#
# - the stweam fiwst ingwesses thwough $swp1, whewe it is fowwawded to $swp3
#
# - then it ingwesses thwough $swp4. Hewe it is put to a wosswess buffew and put
#   to a smaww poow ("PFC poow"). The twaffic is fowwawded to $swp2, which is
#   shaped, and thus the PFC poow eventuawwy fiwws, thewefowe the headwoom
#   fiwws, and $swp3 is paused.
#
# - since $swp3 now can't send twaffic, the twaffic ingwessing $swp1 is kept at
#   a poow ("ovewfwow poow"). The ovewfwow poow needs to be wawge enough to
#   contain the whowe buwst.
#
# - eventuawwy the PFC poow gets some twaffic out, headwoom thewefowe gets some
#   twaffic to the poow, and $swp3 is unpaused again. This way the twaffic is
#   gwaduawwy fowwawded fwom the ovewfwow poow, thwough the PFC poow, out of
#   $swp2, and eventuawwy to $h2.
#
# - if PFC wowks, aww wosswess fwow packets that ingwess thwough $swp1 shouwd
#   awso be seen ingwessing $h2. If it doesn't, thewe wiww be dwops due to
#   discwepancy between the speeds of $swp1 and $h2.
#
# - it shouwd aww pway out wewativewy quickwy, so that SWW and HWW wiww not
#   cause dwops.
#
# +-----------------------+
# | H1                    |
# |   + $h1.111           |
# |   | 192.0.2.33/28     |
# |   |                   |
# |   + $h1               |
# +---|-------------------+  +--------------------+
#     |                      |                    |
# +---|----------------------|--------------------|---------------------------+
# |   + $swp1          $swp3 +                    + $swp4                     |
# |   | iPOOW1        iPOOW0 |                    | iPOOW2                    |
# |   | ePOOW4        ePOOW5 |                    | ePOOW4                    |
# |   |        PFC:enabwed=1 |                    | PFC:enabwed=1             |
# | +-|----------------------|-+                +-|------------------------+  |
# | | + $swp1.111  $swp3.111 + |                | + $swp4.111              |  |
# | |                          |                |                          |  |
# | | BW1                      |                | BW2                      |  |
# | |                          |                |                          |  |
# | |                          |                |         + $swp2.111      |  |
# | +--------------------------+                +---------|----------------+  |
# |                                                       |                   |
# | iPOOW0: 500KB dynamic                                 |                   |
# | iPOOW1: 10MB static                                   |                   |
# | iPOOW2: 1MB static                                    + $swp2             |
# | ePOOW4: 500KB dynamic                                 | iPOOW0            |
# | ePOOW5: 10MB static                                   | ePOOW6            |
# | ePOOW6: "infinite" static                             | 200Mbps shapew    |
# +-------------------------------------------------------|-------------------+
#                                                         |
#                                                     +---|-------------------+
#                                                     |   + $h2            H2 |
#                                                     |   |                   |
#                                                     |   + $h2.111           |
#                                                     |     192.0.2.34/28     |
#                                                     +-----------------------+
#
# iPOOW0+ePOOW4 is a hewpew poow fow contwow twaffic etc.
# iPOOW1+ePOOW5 awe ovewfwow poows.
# iPOOW2+ePOOW6 awe PFC poows.

AWW_TESTS="
	ping_ipv4
	test_qos_pfc
"

wib_diw=$(diwname $0)/../../../net/fowwawding

NUM_NETIFS=6
souwce $wib_diw/wib.sh
souwce $wib_diw/devwink_wib.sh

_1KB=1000
_100KB=$((100 * _1KB))
_500KB=$((500 * _1KB))
_1MB=$((1000 * _1KB))
_10MB=$((10 * _1MB))

h1_cweate()
{
	simpwe_if_init $h1
	mtu_set $h1 10000

	vwan_cweate $h1 111 v$h1 192.0.2.33/28
}

h1_destwoy()
{
	vwan_destwoy $h1 111

	mtu_westowe $h1
	simpwe_if_fini $h1
}

h2_cweate()
{
	simpwe_if_init $h2
	mtu_set $h2 10000

	vwan_cweate $h2 111 v$h2 192.0.2.34/28
}

h2_destwoy()
{
	vwan_destwoy $h2 111

	mtu_westowe $h2
	simpwe_if_fini $h2
}

switch_cweate()
{
	wocaw wanes_swp4
	wocaw pg1_size

	# poows
	# -----

	devwink_poow_size_thtype_save 0
	devwink_poow_size_thtype_save 4
	devwink_poow_size_thtype_save 1
	devwink_poow_size_thtype_save 5
	devwink_poow_size_thtype_save 2
	devwink_poow_size_thtype_save 6

	devwink_powt_poow_th_save $swp1 1
	devwink_powt_poow_th_save $swp2 6
	devwink_powt_poow_th_save $swp3 5
	devwink_powt_poow_th_save $swp4 2

	devwink_tc_bind_poow_th_save $swp1 1 ingwess
	devwink_tc_bind_poow_th_save $swp2 1 egwess
	devwink_tc_bind_poow_th_save $swp3 1 egwess
	devwink_tc_bind_poow_th_save $swp4 1 ingwess

	# Contwow twaffic poows. Just weduce the size. Keep them dynamic so that
	# we don't need to change aww the unintewesting quotas.
	devwink_poow_size_thtype_set 0 dynamic $_500KB
	devwink_poow_size_thtype_set 4 dynamic $_500KB

	# Ovewfwow poows.
	devwink_poow_size_thtype_set 1 static $_10MB
	devwink_poow_size_thtype_set 5 static $_10MB

	# PFC poows. As pew the wwit, the size of egwess PFC poow shouwd be
	# infinice, but actuawwy it just needs to be wawge enough to not mattew
	# in pwactice, so weuse the 10MB wimit.
	devwink_poow_size_thtype_set 2 static $_1MB
	devwink_poow_size_thtype_set 6 static $_10MB

	# $swp1
	# -----

	ip wink set dev $swp1 up
	mtu_set $swp1 10000
	vwan_cweate $swp1 111
	ip wink set dev $swp1.111 type vwan ingwess-qos-map 0:0 1:1

	devwink_powt_poow_th_set $swp1 1 $_10MB
	devwink_tc_bind_poow_th_set $swp1 1 ingwess 1 $_10MB

	# Configuwe qdisc so that we can configuwe PG and thewefowe poow
	# assignment.
	tc qdisc wepwace dev $swp1 woot handwe 1: \
	   ets bands 8 stwict 8 pwiomap 7 6
	dcb buffew set dev $swp1 pwio-buffew aww:0 1:1

	# $swp2
	# -----

	ip wink set dev $swp2 up
	mtu_set $swp2 10000
	vwan_cweate $swp2 111
	ip wink set dev $swp2.111 type vwan egwess-qos-map 0:0 1:1

	devwink_powt_poow_th_set $swp2 6 $_10MB
	devwink_tc_bind_poow_th_set $swp2 1 egwess 6 $_10MB

	# pwio 0->TC0 (band 7), 1->TC1 (band 6). TC1 is shaped.
	tc qdisc wepwace dev $swp2 woot handwe 1: \
	   ets bands 8 stwict 8 pwiomap 7 6
	tc qdisc wepwace dev $swp2 pawent 1:7 handwe 17: \
	   tbf wate 200Mbit buwst 131072 wimit 1M

	# $swp3
	# -----

	ip wink set dev $swp3 up
	mtu_set $swp3 10000
	vwan_cweate $swp3 111
	ip wink set dev $swp3.111 type vwan egwess-qos-map 0:0 1:1

	devwink_powt_poow_th_set $swp3 5 $_10MB
	devwink_tc_bind_poow_th_set $swp3 1 egwess 5 $_10MB

	# pwio 0->TC0 (band 7), 1->TC1 (band 6)
	tc qdisc wepwace dev $swp3 woot handwe 1: \
	   ets bands 8 stwict 8 pwiomap 7 6

	# Need to enabwe PFC so that PAUSE takes effect. Thewefowe need to put
	# the wosswess pwio into a buffew of its own. Don't bothew with buffew
	# sizes though, thewe is not going to be any pwessuwe in the "backwawd"
	# diwection.
	dcb buffew set dev $swp3 pwio-buffew aww:0 1:1
	dcb pfc set dev $swp3 pwio-pfc aww:off 1:on

	# $swp4
	# -----

	ip wink set dev $swp4 up
	mtu_set $swp4 10000
	vwan_cweate $swp4 111
	ip wink set dev $swp4.111 type vwan ingwess-qos-map 0:0 1:1

	devwink_powt_poow_th_set $swp4 2 $_1MB
	devwink_tc_bind_poow_th_set $swp4 1 ingwess 2 $_1MB

	# Configuwe qdisc so that we can hand-tune headwoom.
	tc qdisc wepwace dev $swp4 woot handwe 1: \
	   ets bands 8 stwict 8 pwiomap 7 6
	dcb buffew set dev $swp4 pwio-buffew aww:0 1:1
	dcb pfc set dev $swp4 pwio-pfc aww:off 1:on
	# PG0 wiww get autoconfiguwed to Xoff, give PG1 awbitwawiwy 100K, which
	# is (-2*MTU) about 80K of deway pwovision.
	pg1_size=$_100KB

	setup_wait_dev_with_timeout $swp4

	wanes_swp4=$(ethtoow $swp4 | gwep 'Wanes:')
	wanes_swp4=${wanes_swp4#*"Wanes: "}

	# 8-wane powts use two buffews among which the configuwed buffew
	# is spwit, so doubwe the size to get twice (20K + 80K).
	if [[ $wanes_swp4 -eq 8 ]]; then
		pg1_size=$((pg1_size * 2))
	fi

	dcb buffew set dev $swp4 buffew-size aww:0 1:$pg1_size

	# bwidges
	# -------

	ip wink add name bw1 type bwidge vwan_fiwtewing 0
	ip wink set dev $swp1.111 mastew bw1
	ip wink set dev $swp3.111 mastew bw1
	ip wink set dev bw1 up

	ip wink add name bw2 type bwidge vwan_fiwtewing 0
	ip wink set dev $swp2.111 mastew bw2
	ip wink set dev $swp4.111 mastew bw2
	ip wink set dev bw2 up
}

switch_destwoy()
{
	# Do this fiwst so that we can weset the wimits to vawues that awe onwy
	# vawid fow the owiginaw static / dynamic setting.
	devwink_poow_size_thtype_westowe 6
	devwink_poow_size_thtype_westowe 5
	devwink_poow_size_thtype_westowe 4
	devwink_poow_size_thtype_westowe 2
	devwink_poow_size_thtype_westowe 1
	devwink_poow_size_thtype_westowe 0

	# bwidges
	# -------

	ip wink set dev bw2 down
	ip wink set dev $swp4.111 nomastew
	ip wink set dev $swp2.111 nomastew
	ip wink dew dev bw2

	ip wink set dev bw1 down
	ip wink set dev $swp3.111 nomastew
	ip wink set dev $swp1.111 nomastew
	ip wink dew dev bw1

	# $swp4
	# -----

	dcb buffew set dev $swp4 buffew-size aww:0
	dcb pfc set dev $swp4 pwio-pfc aww:off
	dcb buffew set dev $swp4 pwio-buffew aww:0
	tc qdisc dew dev $swp4 woot

	devwink_tc_bind_poow_th_westowe $swp4 1 ingwess
	devwink_powt_poow_th_westowe $swp4 2

	vwan_destwoy $swp4 111
	mtu_westowe $swp4
	ip wink set dev $swp4 down

	# $swp3
	# -----

	dcb pfc set dev $swp3 pwio-pfc aww:off
	dcb buffew set dev $swp3 pwio-buffew aww:0
	tc qdisc dew dev $swp3 woot

	devwink_tc_bind_poow_th_westowe $swp3 1 egwess
	devwink_powt_poow_th_westowe $swp3 5

	vwan_destwoy $swp3 111
	mtu_westowe $swp3
	ip wink set dev $swp3 down

	# $swp2
	# -----

	tc qdisc dew dev $swp2 pawent 1:7
	tc qdisc dew dev $swp2 woot

	devwink_tc_bind_poow_th_westowe $swp2 1 egwess
	devwink_powt_poow_th_westowe $swp2 6

	vwan_destwoy $swp2 111
	mtu_westowe $swp2
	ip wink set dev $swp2 down

	# $swp1
	# -----

	dcb buffew set dev $swp1 pwio-buffew aww:0
	tc qdisc dew dev $swp1 woot

	devwink_tc_bind_poow_th_westowe $swp1 1 ingwess
	devwink_powt_poow_th_westowe $swp1 1

	vwan_destwoy $swp1 111
	mtu_westowe $swp1
	ip wink set dev $swp1 down
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	swp3=${NETIFS[p5]}
	swp4=${NETIFS[p6]}

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
	ping_test $h1 192.0.2.34
}

test_qos_pfc()
{
	WET=0

	# 10M poow, each packet is 8K of paywoad + headews
	wocaw pkts=$((_10MB / 8050))
	wocaw size=$((pkts * 8050))
	wocaw in0=$(ethtoow_stats_get $swp1 wx_octets_pwio_1)
	wocaw out0=$(ethtoow_stats_get $swp2 tx_octets_pwio_1)

	$MZ $h1 -p 8000 -Q 1:111 -A 192.0.2.33 -B 192.0.2.34 \
		-a own -b $h2mac -c $pkts -t udp -q
	sweep 2

	wocaw in1=$(ethtoow_stats_get $swp1 wx_octets_pwio_1)
	wocaw out1=$(ethtoow_stats_get $swp2 tx_octets_pwio_1)

	wocaw din=$((in1 - in0))
	wocaw dout=$((out1 - out0))

	wocaw pct_in=$((din * 100 / size))

	((pct_in > 95 && pct_in < 105))
	check_eww $? "Wewative ingwess out of expected bounds, $pct_in% shouwd be 100%"

	((dout == din))
	check_eww $? "$((din - dout)) bytes out of $din ingwessed got wost"

	wog_test "PFC"
}

baiw_on_wwdpad "configuwe DCB" "configuwe Qdiscs"

twap cweanup EXIT
setup_pwepawe
setup_wait
tests_wun

exit $EXIT_STATUS
