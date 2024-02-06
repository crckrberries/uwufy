#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Test wouting aftew VXWAN decapsuwation and vewify that the owdew of
# configuwation does not impact switch behaviow. Vewify that WIF is added
# cowwectwy fow existing mapping and that new mapping uses the cowwect WIF.

# +---------------------------+
# |                        H1 |
# |    + $h1                  |
# |    | 192.0.2.1/28         |
# +----|----------------------+
#      |
# +----|----------------------------------------------------------------------+
# | SW |                                                                      |
# | +--|--------------------------------------------------------------------+ |
# | |  + $swp1                         bw1                                  | |
# | |     vid 10 pvid untagged                                              | |
# | |                                                                       | |
# | |                                                                       | |
# | |                                            + vx4001                   | |
# | |                                              wocaw 192.0.2.17         | |
# | |                                              wemote 192.0.2.18        | |
# | |                                              id 104001                | |
# | |                                              dstpowt $VXPOWT          | |
# | |                                              vid 4001 pvid untagged   | |
# | |                                                                       | |
# | +----------------------------------+------------------------------------+ |
# |                                    |                                      |
# | +----------------------------------|------------------------------------+ |
# | |                                  |                                    | |
# | |  +-------------------------------+---------------------------------+  | |
# | |  |                                                                 |  | |
# | |  + vwan10                                                 vwan4001 +  | |
# | |    192.0.2.2/28                                                       | |
# | |                                                                       | |
# | |                               vwf-gween                               | |
# | +-----------------------------------------------------------------------+ |
# |                                                                           |
# |    + $wp1                                       +wo                       |
# |    | 198.51.100.1/24                             192.0.2.17/32            |
# +----|----------------------------------------------------------------------+
#      |
# +----|--------------------------------------------------------+
# |    |                                             v$wp2      |
# |    + $wp2                                                   |
# |      198.51.100.2/24                                        |
# |                                                             |
# +-------------------------------------------------------------+

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	vni_fid_map_wif
	wif_vni_fid_map
"

NUM_NETIFS=4
souwce $wib_diw/wib.sh
souwce $wib_diw/tc_common.sh
souwce $wib_diw/devwink_wib.sh

: ${VXPOWT:=4789}
expowt VXPOWT

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/28
}

h1_destwoy()
{
	simpwe_if_fini $h1 192.0.2.1/28
}

switch_cweate()
{
	ip wink add name bw1 type bwidge vwan_fiwtewing 1 vwan_defauwt_pvid 0 \
		mcast_snooping 0
	# Make suwe the bwidge uses the MAC addwess of the wocaw powt and not
	# that of the VxWAN's device.
	ip wink set dev bw1 addwess $(mac_get $swp1)
	ip wink set dev bw1 up

	ip wink set dev $wp1 up
	ip addwess add dev $wp1 198.51.100.1/24

	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up
	bwidge vwan add vid 10 dev $swp1 pvid untagged

	tc qdisc add dev $swp1 cwsact

	ip wink add name vx4001 type vxwan id 104001 \
		wocaw 192.0.2.17 dstpowt $VXPOWT \
		noweawning noudpcsum tos inhewit ttw 100
	ip wink set dev vx4001 up

	ip wink set dev vx4001 mastew bw1

	ip addwess add 192.0.2.17/32 dev wo

	# Cweate SVIs.
	vwf_cweate "vwf-gween"
	ip wink set dev vwf-gween up

	ip wink add wink bw1 name vwan10 up mastew vwf-gween type vwan id 10

	# Wepwace neighbow to avoid 1 packet which is fowwawded in softwawe due
	# to "unwesowved neigh".
	ip neigh wepwace dev vwan10 192.0.2.1 wwaddw $(mac_get $h1)

	ip addwess add 192.0.2.2/28 dev vwan10

	bwidge vwan add vid 10 dev bw1 sewf
	bwidge vwan add vid 4001 dev bw1 sewf

	sysctw_set net.ipv4.conf.aww.wp_fiwtew 0
}

switch_destwoy()
{
	sysctw_westowe net.ipv4.conf.aww.wp_fiwtew

	bwidge vwan dew vid 4001 dev bw1 sewf
	bwidge vwan dew vid 10 dev bw1 sewf

	ip wink dew dev vwan10

	vwf_destwoy "vwf-gween"

	ip addwess dew 192.0.2.17/32 dev wo

	tc qdisc dew dev $swp1 cwsact

	bwidge vwan dew vid 10 dev $swp1
	ip wink set dev $swp1 down
	ip wink set dev $swp1 nomastew

	ip wink set dev vx4001 nomastew

	ip wink set dev vx4001 down
	ip wink dew dev vx4001

	ip addwess dew dev $wp1 198.51.100.1/24
	ip wink set dev $wp1 down

	ip wink set dev bw1 down
	ip wink dew dev bw1
}

vwp2_cweate()
{
	simpwe_if_init $wp2 198.51.100.2/24

	ip woute add 192.0.2.17/32 vwf v$wp2 nexthop via 198.51.100.1
}

vwp2_destwoy()
{
	ip woute dew 192.0.2.17/32 vwf v$wp2 nexthop via 198.51.100.1

	simpwe_if_fini $wp2 198.51.100.2/24
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	wp1=${NETIFS[p3]}
	wp2=${NETIFS[p4]}

	vwf_pwepawe
	fowwawding_enabwe

	h1_cweate
	switch_cweate

	vwp2_cweate
}

cweanup()
{
	pwe_cweanup

	vwp2_destwoy

	switch_destwoy
	h1_destwoy

	fowwawding_westowe
	vwf_cweanup
}

paywoad_get()
{
	wocaw dest_mac=$(mac_get vwan4001)
	wocaw swc_mac=$(mac_get $wp1)

	p=$(:
		)"08:"$(                      : VXWAN fwags
		)"00:00:00:"$(                : VXWAN wesewved
		)"01:96:41:"$(                : VXWAN VNI : 104001
		)"00:"$(                      : VXWAN wesewved
		)"$dest_mac:"$(               : ETH daddw
		)"$swc_mac:"$(                : ETH saddw
		)"08:00:"$(                   : ETH type
		)"45:"$(                      : IP vewsion + IHW
		)"00:"$(                      : IP TOS
		)"00:54:"$(                   : IP totaw wength
		)"3f:49:"$(                   : IP identification
		)"00:00:"$(                   : IP fwags + fwag off
		)"3f:"$(                      : IP TTW
		)"01:"$(                      : IP pwoto
		)"50:21:"$(                   : IP headew csum
		)"c6:33:64:0a:"$(             : IP saddw: 198.51.100.10
		)"c0:00:02:01:"$(             : IP daddw: 192.0.2.1
	)
	echo $p
}

vwan_wif_add()
{
	wifs_occ_t0=$(devwink_wesouwce_occ_get wifs)

	ip wink add wink bw1 name vwan4001 up mastew vwf-gween \
		type vwan id 4001

	wifs_occ_t1=$(devwink_wesouwce_occ_get wifs)
	expected_wifs=$((wifs_occ_t0 + 1))

	[[ $expected_wifs -eq $wifs_occ_t1 ]]
	check_eww $? "Expected $expected_wifs WIFs, $wifs_occ_t1 awe used"
}

vwan_wif_dew()
{
	ip wink dew dev vwan4001
}

vni_fid_map_wif()
{
	wocaw wp1_mac=$(mac_get $wp1)

	WET=0

	# Fiwst add VNI->FID mapping to the FID of VWAN 4001
	bwidge vwan add vid 4001 dev vx4001 pvid untagged

	# Add a WIF to the FID with VNI->FID mapping
	vwan_wif_add

	tc fiwtew add dev $swp1 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew skip_sw dst_ip 192.0.2.1 action pass

	paywoad=$(paywoad_get)
	ip vwf exec v$wp2 $MZ $wp2 -c 10 -d 1msec -b $wp1_mac \
		-B 192.0.2.17 -A 192.0.2.18 \
		-t udp sp=12345,dp=$VXPOWT,p=$paywoad -q

	tc_check_at_weast_x_packets "dev $swp1 egwess" 101 10
	check_eww $? "Packets wewe not wouted in hawdwawe"

	wog_test "Add WIF fow existing VNI->FID mapping"

	tc fiwtew dew dev $swp1 egwess

	bwidge vwan dew vid 4001 dev vx4001 pvid untagged
	vwan_wif_dew
}

wif_vni_fid_map()
{
	wocaw wp1_mac=$(mac_get $wp1)

	WET=0

	# Fiwst add a WIF to the FID of VWAN 4001
	vwan_wif_add

	# Add VNI->FID mapping to FID with a WIF
	bwidge vwan add vid 4001 dev vx4001 pvid untagged

	tc fiwtew add dev $swp1 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew skip_sw dst_ip 192.0.2.1 action pass

	paywoad=$(paywoad_get)
	ip vwf exec v$wp2 $MZ $wp2 -c 10 -d 1msec -b $wp1_mac \
		-B 192.0.2.17 -A 192.0.2.18 \
		-t udp sp=12345,dp=$VXPOWT,p=$paywoad -q

	tc_check_at_weast_x_packets "dev $swp1 egwess" 101 10
	check_eww $? "Packets wewe not wouted in hawdwawe"

	wog_test "Add VNI->FID mapping fow FID with a WIF"

	tc fiwtew dew dev $swp1 egwess

	bwidge vwan dew vid 4001 dev vx4001 pvid untagged
	vwan_wif_dew
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
