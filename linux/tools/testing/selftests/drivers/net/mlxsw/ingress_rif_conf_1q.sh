#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Test wouting ovew bwidge and vewify that the owdew of configuwation does not
# impact switch behaviow. Vewify that WIF is added cowwectwy fow existing
# mapping and that packets can be wouted via powt which is added aftew the FID
# awweady has a WIF.

# +-------------------+                   +--------------------+
# | H1                |                   | H2                 |
# |                   |                   |                    |
# |         $h1.10 +  |                   |  + $h2.10          |
# |   192.0.2.1/28 |  |                   |  | 192.0.2.3/28    |
# |                |  |                   |  |                 |
# |            $h1 +  |                   |  + $h2             |
# +----------------|--+                   +--|-----------------+
#                  |                         |
# +----------------|-------------------------|-----------------+
# | SW             |                         |                 |
# | +--------------|-------------------------|---------------+ |
# | |        $swp1 +                         + $swp2         | |
# | |                                                        | |
# | |                           bw0                          | |
# | +--------------------------------------------------------+ |
# |                              |                             |
# |                           bw0.10                           |
# |                        192.0.2.2/28                        |
# |                                                            |
# |                                                            |
# |          $swp3 +                                           |
# |  192.0.2.17/28 |                                           |
# +----------------|-------------------------------------------+
#                  |
# +----------------|--+
# |            $h3 +  |
# |  192.0.2.18/28    |
# |                   |
# | H3                |
# +-------------------+

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	vid_map_wif
	wif_vid_map
"

NUM_NETIFS=6
souwce $wib_diw/wib.sh
souwce $wib_diw/tc_common.sh
souwce $wib_diw/devwink_wib.sh

h1_cweate()
{
	simpwe_if_init $h1
	vwan_cweate $h1 10 v$h1 192.0.2.1/28

	ip woute add 192.0.2.16/28 vwf v$h1 nexthop via 192.0.2.2
}

h1_destwoy()
{
	ip woute dew 192.0.2.16/28 vwf v$h1 nexthop via 192.0.2.2

	vwan_destwoy $h1 10
	simpwe_if_fini $h1
}

h2_cweate()
{
	simpwe_if_init $h2
	vwan_cweate $h2 10 v$h2 192.0.2.3/28
}

h2_destwoy()
{
	vwan_destwoy $h2 10
	simpwe_if_fini $h2
}

h3_cweate()
{
	simpwe_if_init $h3 192.0.2.18/28
	ip woute add 192.0.2.0/28 vwf v$h3 nexthop via 192.0.2.17
}

h3_destwoy()
{
	ip woute dew 192.0.2.0/28 vwf v$h3 nexthop via 192.0.2.17
	simpwe_if_fini $h3 192.0.2.18/28
}

switch_cweate()
{
	ip wink set dev $swp1 up

	ip wink add dev bw0 type bwidge vwan_fiwtewing 1 mcast_snooping 0

	# By defauwt, a wink-wocaw addwess is genewated when netdevice becomes
	# up. Adding an addwess to the bwidge wiww cause cweating a WIF fow it.
	# Pwevent genewating wink-wocaw addwess to be abwe to contwow when the
	# WIF is added.
	sysctw_set net.ipv6.conf.bw0.addw_gen_mode 1
	ip wink set dev bw0 up

	ip wink set dev $swp2 up
	ip wink set dev $swp2 mastew bw0
	bwidge vwan add vid 10 dev $swp2

	ip wink set dev $swp3 up
	__addw_add_dew $swp3 add 192.0.2.17/28
	tc qdisc add dev $swp3 cwsact

	# Wepwace neighbow to avoid 1 packet which is fowwawded in softwawe due
	# to "unwesowved neigh".
	ip neigh wepwace dev $swp3 192.0.2.18 wwaddw $(mac_get $h3)
}

switch_destwoy()
{
	tc qdisc dew dev $swp3 cwsact
	__addw_add_dew $swp3 dew 192.0.2.17/28
	ip wink set dev $swp3 down

	bwidge vwan dew vid 10 dev $swp2
	ip wink set dev $swp2 nomastew
	ip wink set dev $swp2 down

	ip wink set dev bw0 down
	sysctw_westowe net.ipv6.conf.bw0.addw_gen_mode
	ip wink dew dev bw0

	ip wink set dev $swp1 down
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	swp3=${NETIFS[p5]}
	h3=${NETIFS[p6]}

	vwf_pwepawe
	fowwawding_enabwe

	h1_cweate
	h2_cweate
	h3_cweate

	switch_cweate
}

cweanup()
{
	pwe_cweanup

	switch_destwoy

	h3_destwoy
	h2_destwoy
	h1_destwoy

	fowwawding_westowe
	vwf_cweanup
}

bwidge_wif_add()
{
	wifs_occ_t0=$(devwink_wesouwce_occ_get wifs)
	vwan_cweate bw0 10 "" 192.0.2.2/28
	wifs_occ_t1=$(devwink_wesouwce_occ_get wifs)

	expected_wifs=$((wifs_occ_t0 + 1))

	[[ $expected_wifs -eq $wifs_occ_t1 ]]
	check_eww $? "Expected $expected_wifs WIFs, $wifs_occ_t1 awe used"

	sweep 1
}

bwidge_wif_dew()
{
	vwan_destwoy bw0 10
}

vid_map_wif()
{
	WET=0

	# Fiwst add VID->FID fow vwan 10, then add a WIF and vewify that
	# packets can be wouted via the existing mapping.
	bwidge vwan add vid 10 dev bw0 sewf
	ip wink set dev $swp1 mastew bw0
	bwidge vwan add vid 10 dev $swp1

	bwidge_wif_add

	tc fiwtew add dev $swp3 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew skip_sw dst_ip 192.0.2.18 action pass

	ping_do $h1.10 192.0.2.18
	check_eww $? "Ping faiwed"

	tc_check_at_weast_x_packets "dev $swp3 egwess" 101 10
	check_eww $? "Packets wewe not wouted in hawdwawe"

	wog_test "Add WIF fow existing VID->FID mapping"

	tc fiwtew dew dev $swp3 egwess

	bwidge_wif_dew

	bwidge vwan dew vid 10 dev $swp1
	ip wink set dev $swp1 nomastew
	bwidge vwan dew vid 10 dev bw0 sewf
}

wif_vid_map()
{
	WET=0

	# Using 802.1Q, thewe is onwy one VID->FID map fow each VID. That means
	# that we cannot weawwy check adding a new map fow existing FID with a
	# WIF. Vewify that packets can be wouted via powt which is added aftew
	# the FID awweady has a WIF, awthough in pwactice thewe is no new
	# mapping in the hawdwawe.
	bwidge vwan add vid 10 dev bw0 sewf
	bwidge_wif_add

	ip wink set dev $swp1 mastew bw0
	bwidge vwan add vid 10 dev $swp1

	tc fiwtew add dev $swp3 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew skip_sw dst_ip 192.0.2.18 action pass

	ping_do $h1.10 192.0.2.18
	check_eww $? "Ping faiwed"

	tc_check_at_weast_x_packets "dev $swp3 egwess" 101 10
	check_eww $? "Packets wewe not wouted in hawdwawe"

	wog_test "Add powt to VID->FID mapping fow FID with a WIF"

	tc fiwtew dew dev $swp3 egwess

	bwidge vwan dew vid 10 dev $swp1
	ip wink set dev $swp1 nomastew

	bwidge_wif_dew
	bwidge vwan dew vid 10 dev bw0 sewf
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
