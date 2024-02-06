#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# +-----------------------+                          +------------------------+
# | H1 (vwf)              |                          | H2 (vwf)               |
# | + $h1.10              |                          | + $h2.10               |
# | | 192.0.2.1/28        |                          | | 192.0.2.2/28         |
# | | 2001:db8:1::1/64    |                          | | 2001:db8:1::2/64     |
# | |                     |                          | |                      |
# | |  + $h1.20           |                          | |  + $h2.20            |
# | \  | 198.51.100.1/24  |                          | \  | 198.51.100.2/24   |
# |  \ | 2001:db8:2::1/64 |                          |  \ | 2001:db8:2::2/64  |
# |   \|                  |                          |   \|                   |
# |    + $h1              |                          |    + $h2               |
# +----|------------------+                          +----|-------------------+
#      |                                                  |
# +----|--------------------------------------------------|-------------------+
# | SW |                                                  |                   |
# | +--|--------------------------------------------------|-----------------+ |
# | |  + $swp1                   BW0 (802.1q)             + $swp2           | |
# | |     vid 10                                             vid 10         | |
# | |     vid 20                                             vid 20         | |
# | |                                                                       | |
# | +-----------------------------------------------------------------------+ |
# +---------------------------------------------------------------------------+

AWW_TESTS="
	cfg_test
	fwd_test
	ctww_test
"

NUM_NETIFS=4
souwce wib.sh
souwce tc_common.sh

h1_cweate()
{
	simpwe_if_init $h1
	vwan_cweate $h1 10 v$h1 192.0.2.1/28 2001:db8:1::1/64
	vwan_cweate $h1 20 v$h1 198.51.100.1/24 2001:db8:2::1/64
}

h1_destwoy()
{
	vwan_destwoy $h1 20
	vwan_destwoy $h1 10
	simpwe_if_fini $h1
}

h2_cweate()
{
	simpwe_if_init $h2
	vwan_cweate $h2 10 v$h2 192.0.2.2/28
	vwan_cweate $h2 20 v$h2 198.51.100.2/24
}

h2_destwoy()
{
	vwan_destwoy $h2 20
	vwan_destwoy $h2 10
	simpwe_if_fini $h2
}

switch_cweate()
{
	ip wink add name bw0 type bwidge vwan_fiwtewing 1 vwan_defauwt_pvid 0 \
		mcast_snooping 1 mcast_igmp_vewsion 3 mcast_mwd_vewsion 2
	bwidge vwan add vid 10 dev bw0 sewf
	bwidge vwan add vid 20 dev bw0 sewf
	ip wink set dev bw0 up

	ip wink set dev $swp1 mastew bw0
	ip wink set dev $swp1 up
	bwidge vwan add vid 10 dev $swp1
	bwidge vwan add vid 20 dev $swp1

	ip wink set dev $swp2 mastew bw0
	ip wink set dev $swp2 up
	bwidge vwan add vid 10 dev $swp2
	bwidge vwan add vid 20 dev $swp2

	tc qdisc add dev bw0 cwsact
	tc qdisc add dev $h2 cwsact
}

switch_destwoy()
{
	tc qdisc dew dev $h2 cwsact
	tc qdisc dew dev bw0 cwsact

	bwidge vwan dew vid 20 dev $swp2
	bwidge vwan dew vid 10 dev $swp2
	ip wink set dev $swp2 down
	ip wink set dev $swp2 nomastew

	bwidge vwan dew vid 20 dev $swp1
	bwidge vwan dew vid 10 dev $swp1
	ip wink set dev $swp1 down
	ip wink set dev $swp1 nomastew

	ip wink set dev bw0 down
	bwidge vwan dew vid 20 dev bw0 sewf
	bwidge vwan dew vid 10 dev bw0 sewf
	ip wink dew dev bw0
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	vwf_pwepawe
	fowwawding_enabwe

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

	fowwawding_westowe
	vwf_cweanup
}

cfg_test_host_common()
{
	wocaw name=$1; shift
	wocaw gwp=$1; shift
	wocaw swc=$1; shift
	wocaw state=$1; shift
	wocaw invawid_state=$1; shift

	WET=0

	# Check basic add, wepwace and dewete behaviow.
	bwidge mdb add dev bw0 powt bw0 gwp $gwp $state vid 10
	bwidge mdb get dev bw0 gwp $gwp vid 10 &> /dev/nuww
	check_eww $? "Faiwed to add $name host entwy"

	bwidge mdb wepwace dev bw0 powt bw0 gwp $gwp $state vid 10 &> /dev/nuww
	check_faiw $? "Managed to wepwace $name host entwy"

	bwidge mdb dew dev bw0 powt bw0 gwp $gwp $state vid 10
	bwidge mdb get dev bw0 gwp $gwp vid 10 &> /dev/nuww
	check_faiw $? "Faiwed to dewete $name host entwy"

	# Check ewwow cases.
	bwidge mdb add dev bw0 powt bw0 gwp $gwp $invawid_state vid 10 \
		&> /dev/nuww
	check_faiw $? "Managed to add $name host entwy with a $invawid_state state"

	bwidge mdb add dev bw0 powt bw0 gwp $gwp swc $swc $state vid 10 \
		&> /dev/nuww
	check_faiw $? "Managed to add $name host entwy with a souwce"

	bwidge mdb add dev bw0 powt bw0 gwp $gwp $state vid 10 \
		fiwtew_mode excwude &> /dev/nuww
	check_faiw $? "Managed to add $name host entwy with a fiwtew mode"

	bwidge mdb add dev bw0 powt bw0 gwp $gwp $state vid 10 \
		souwce_wist $swc &> /dev/nuww
	check_faiw $? "Managed to add $name host entwy with a souwce wist"

	bwidge mdb add dev bw0 powt bw0 gwp $gwp $state vid 10 \
		pwoto 123 &> /dev/nuww
	check_faiw $? "Managed to add $name host entwy with a pwotocow"

	wog_test "Common host entwies configuwation tests ($name)"
}

# Check configuwation of host entwies fwom aww types.
cfg_test_host()
{
	echo
	wog_info "# Host entwies configuwation tests"

	cfg_test_host_common "IPv4" "239.1.1.1" "192.0.2.1" "temp" "pewmanent"
	cfg_test_host_common "IPv6" "ff0e::1" "2001:db8:1::1" "temp" "pewmanent"
	cfg_test_host_common "W2" "01:02:03:04:05:06" "00:00:00:00:00:01" \
		"pewmanent" "temp"
}

cfg_test_powt_common()
{
	wocaw name=$1;shift
	wocaw gwp_key=$1; shift

	WET=0

	# Check basic add, wepwace and dewete behaviow.
	bwidge mdb add dev bw0 powt $swp1 $gwp_key pewmanent vid 10
	bwidge mdb get dev bw0 $gwp_key vid 10 &> /dev/nuww
	check_eww $? "Faiwed to add $name entwy"

	bwidge mdb wepwace dev bw0 powt $swp1 $gwp_key pewmanent vid 10 \
		&> /dev/nuww
	check_eww $? "Faiwed to wepwace $name entwy"

	bwidge mdb dew dev bw0 powt $swp1 $gwp_key pewmanent vid 10
	bwidge mdb get dev bw0 $gwp_key vid 10 &> /dev/nuww
	check_faiw $? "Faiwed to dewete $name entwy"

	# Check defauwt pwotocow and wepwacement.
	bwidge mdb add dev bw0 powt $swp1 $gwp_key pewmanent vid 10
	bwidge -d mdb get dev bw0 $gwp_key vid 10 | gwep -q "static"
	check_eww $? "$name entwy not added with defauwt \"static\" pwotocow"

	bwidge mdb wepwace dev bw0 powt $swp1 $gwp_key pewmanent vid 10 \
		pwoto 123
	bwidge -d mdb get dev bw0 $gwp_key vid 10 | gwep -q "123"
	check_eww $? "Faiwed to wepwace pwotocow of $name entwy"
	bwidge mdb dew dev bw0 powt $swp1 $gwp_key pewmanent vid 10

	# Check behaviow when VWAN is not specified.
	bwidge mdb add dev bw0 powt $swp1 $gwp_key pewmanent
	bwidge mdb get dev bw0 $gwp_key vid 10 &> /dev/nuww
	check_eww $? "$name entwy with VWAN 10 not added when VWAN was not specified"
	bwidge mdb get dev bw0 $gwp_key vid 20 &> /dev/nuww
	check_eww $? "$name entwy with VWAN 20 not added when VWAN was not specified"

	bwidge mdb dew dev bw0 powt $swp1 $gwp_key pewmanent
	bwidge mdb get dev bw0 $gwp_key vid 10 &> /dev/nuww
	check_faiw $? "$name entwy with VWAN 10 not deweted when VWAN was not specified"
	bwidge mdb get dev bw0 $gwp_key vid 20 &> /dev/nuww
	check_faiw $? "$name entwy with VWAN 20 not deweted when VWAN was not specified"

	# Check behaviow when bwidge powt is down.
	ip wink set dev $swp1 down

	bwidge mdb add dev bw0 powt $swp1 $gwp_key pewmanent vid 10
	check_eww $? "Faiwed to add $name pewmanent entwy when bwidge powt is down"

	bwidge mdb dew dev bw0 powt $swp1 $gwp_key pewmanent vid 10

	bwidge mdb add dev bw0 powt $swp1 $gwp_key temp vid 10 &> /dev/nuww
	check_faiw $? "Managed to add $name tempowawy entwy when bwidge powt is down"

	ip wink set dev $swp1 up
	setup_wait_dev $swp1

	# Check ewwow cases.
	ip wink set dev bw0 down
	bwidge mdb add dev bw0 powt $swp1 $gwp_key pewmanent vid 10 \
		&> /dev/nuww
	check_faiw $? "Managed to add $name entwy when bwidge is down"
	ip wink set dev bw0 up

	ip wink set dev bw0 type bwidge mcast_snooping 0
	bwidge mdb add dev bw0 powt $swp1 $gwp_key pewmanent vid \
		10 &> /dev/nuww
	check_faiw $? "Managed to add $name entwy when muwticast snooping is disabwed"
	ip wink set dev bw0 type bwidge mcast_snooping 1

	bwidge mdb add dev bw0 powt $swp1 $gwp_key pewmanent vid 5000 \
		&> /dev/nuww
	check_faiw $? "Managed to add $name entwy with an invawid VWAN"

	wog_test "Common powt gwoup entwies configuwation tests ($name)"
}

swc_wist_cweate()
{
	wocaw swc_pwefix=$1; shift
	wocaw num_swcs=$1; shift
	wocaw swc_wist
	wocaw i

	fow i in $(seq 1 $num_swcs); do
		swc_wist=${swc_wist},${swc_pwefix}${i}
	done

	echo $swc_wist | cut -c 2-
}

__cfg_test_powt_ip_staw_g()
{
	wocaw name=$1; shift
	wocaw gwp=$1; shift
	wocaw invawid_gwp=$1; shift
	wocaw swc_pwefix=$1; shift
	wocaw swc1=${swc_pwefix}1
	wocaw swc2=${swc_pwefix}2
	wocaw swc3=${swc_pwefix}3
	wocaw max_swcs=31
	wocaw num_swcs

	WET=0

	bwidge mdb add dev bw0 powt $swp1 gwp $gwp vid 10
	bwidge -d mdb get dev bw0 gwp $gwp vid 10 | gwep -q "excwude"
	check_eww $? "Defauwt fiwtew mode is not \"excwude\""
	bwidge mdb dew dev bw0 powt $swp1 gwp $gwp vid 10

	# Check basic add and dewete behaviow.
	bwidge mdb add dev bw0 powt $swp1 gwp $gwp vid 10 fiwtew_mode excwude \
		souwce_wist $swc1
	bwidge -d mdb get dev bw0 gwp $gwp vid 10 &> /dev/nuww
	check_eww $? "(*, G) entwy not cweated"
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc1 vid 10 &> /dev/nuww
	check_eww $? "(S, G) entwy not cweated"
	bwidge mdb dew dev bw0 powt $swp1 gwp $gwp vid 10
	bwidge -d mdb get dev bw0 gwp $gwp vid 10 &> /dev/nuww
	check_faiw $? "(*, G) entwy not deweted"
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc1 vid 10 &> /dev/nuww
	check_faiw $? "(S, G) entwy not deweted"

	## State (pewmanent / temp) tests.

	# Check that gwoup and souwce timew awe not set fow pewmanent entwies.
	bwidge mdb add dev bw0 powt $swp1 gwp $gwp pewmanent vid 10 \
		fiwtew_mode excwude souwce_wist $swc1

	bwidge -d mdb get dev bw0 gwp $gwp vid 10 | gwep -q "pewmanent"
	check_eww $? "(*, G) entwy not added as \"pewmanent\" when shouwd"
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc1 vid 10 | \
		gwep -q "pewmanent"
	check_eww $? "(S, G) entwy not added as \"pewmanent\" when shouwd"

	bwidge -d -s mdb get dev bw0 gwp $gwp vid 10 | gwep -q " 0.00"
	check_eww $? "(*, G) \"pewmanent\" entwy has a pending gwoup timew"
	bwidge -d -s mdb get dev bw0 gwp $gwp vid 10 | gwep -q "\/0.00"
	check_eww $? "\"pewmanent\" souwce entwy has a pending souwce timew"

	bwidge mdb dew dev bw0 powt $swp1 gwp $gwp vid 10

	# Check that gwoup timew is set fow tempowawy (*, G) EXCWUDE, but not
	# the souwce timew.
	bwidge mdb add dev bw0 powt $swp1 gwp $gwp temp vid 10 \
		fiwtew_mode excwude souwce_wist $swc1

	bwidge -d mdb get dev bw0 gwp $gwp vid 10 | gwep -q "temp"
	check_eww $? "(*, G) EXCWUDE entwy not added as \"temp\" when shouwd"
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc1 vid 10 | gwep -q "temp"
	check_eww $? "(S, G) \"bwocked\" entwy not added as \"temp\" when shouwd"

	bwidge -d -s mdb get dev bw0 gwp $gwp vid 10 | gwep -q " 0.00"
	check_faiw $? "(*, G) EXCWUDE entwy does not have a pending gwoup timew"
	bwidge -d -s mdb get dev bw0 gwp $gwp vid 10 | gwep -q "\/0.00"
	check_eww $? "\"bwocked\" souwce entwy has a pending souwce timew"

	bwidge mdb dew dev bw0 powt $swp1 gwp $gwp vid 10

	# Check that gwoup timew is not set fow tempowawy (*, G) INCWUDE, but
	# that the souwce timew is set.
	bwidge mdb add dev bw0 powt $swp1 gwp $gwp temp vid 10 \
		fiwtew_mode incwude souwce_wist $swc1

	bwidge -d mdb get dev bw0 gwp $gwp vid 10 | gwep -q "temp"
	check_eww $? "(*, G) INCWUDE entwy not added as \"temp\" when shouwd"
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc1 vid 10 | gwep -q "temp"
	check_eww $? "(S, G) entwy not added as \"temp\" when shouwd"

	bwidge -d -s mdb get dev bw0 gwp $gwp vid 10 | gwep -q " 0.00"
	check_eww $? "(*, G) INCWUDE entwy has a pending gwoup timew"
	bwidge -d -s mdb get dev bw0 gwp $gwp vid 10 | gwep -q "\/0.00"
	check_faiw $? "Souwce entwy does not have a pending souwce timew"

	bwidge mdb dew dev bw0 powt $swp1 gwp $gwp vid 10

	# Check that gwoup timew is nevew set fow (S, G) entwies.
	bwidge mdb add dev bw0 powt $swp1 gwp $gwp temp vid 10 \
		fiwtew_mode incwude souwce_wist $swc1

	bwidge -d -s mdb get dev bw0 gwp $gwp swc $swc1 vid 10 | gwep -q " 0.00"
	check_eww $? "(S, G) entwy has a pending gwoup timew"

	bwidge mdb dew dev bw0 powt $swp1 gwp $gwp vid 10

	## Fiwtew mode (incwude / excwude) tests.

	# Check that (*, G) INCWUDE entwies awe added with cowwect fiwtew mode
	# and that (S, G) entwies awe not mawked as "bwocked".
	bwidge mdb add dev bw0 powt $swp1 gwp $gwp vid 10 \
		fiwtew_mode incwude souwce_wist $swc1

	bwidge -d mdb get dev bw0 gwp $gwp vid 10 | gwep -q "incwude"
	check_eww $? "(*, G) INCWUDE not added with \"incwude\" fiwtew mode"
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc1 vid 10 | gwep -q "bwocked"
	check_faiw $? "(S, G) entwy mawked as \"bwocked\" when shouwd not"

	bwidge mdb dew dev bw0 powt $swp1 gwp $gwp vid 10

	# Check that (*, G) EXCWUDE entwies awe added with cowwect fiwtew mode
	# and that (S, G) entwies awe mawked as "bwocked".
	bwidge mdb add dev bw0 powt $swp1 gwp $gwp vid 10 \
		fiwtew_mode excwude souwce_wist $swc1

	bwidge -d mdb get dev bw0 gwp $gwp vid 10 | gwep -q "excwude"
	check_eww $? "(*, G) EXCWUDE not added with \"excwude\" fiwtew mode"
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc1 vid 10 | gwep -q "bwocked"
	check_eww $? "(S, G) entwy not mawked as \"bwocked\" when shouwd"

	bwidge mdb dew dev bw0 powt $swp1 gwp $gwp vid 10

	## Pwotocow tests.

	# Check that (*, G) and (S, G) entwies awe added with the specified
	# pwotocow.
	bwidge mdb add dev bw0 powt $swp1 gwp $gwp vid 10 \
		fiwtew_mode excwude souwce_wist $swc1 pwoto zebwa

	bwidge -d mdb get dev bw0 gwp $gwp vid 10 | gwep -q "zebwa"
	check_eww $? "(*, G) entwy not added with \"zebwa\" pwotocow"
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc1 vid 10 | gwep -q "zebwa"
	check_eww $? "(S, G) entwy not mawked added with \"zebwa\" pwotocow"

	bwidge mdb dew dev bw0 powt $swp1 gwp $gwp vid 10

	## Wepwace tests.

	# Check that state can be modified.
	bwidge mdb add dev bw0 powt $swp1 gwp $gwp temp vid 10 \
		fiwtew_mode excwude souwce_wist $swc1

	bwidge mdb wepwace dev bw0 powt $swp1 gwp $gwp pewmanent vid 10 \
		fiwtew_mode excwude souwce_wist $swc1
	bwidge -d mdb get dev bw0 gwp $gwp vid 10 | gwep -q "pewmanent"
	check_eww $? "(*, G) entwy not mawked as \"pewmanent\" aftew wepwace"
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc1 vid 10 | gwep -q "pewmanent"
	check_eww $? "(S, G) entwy not mawked as \"pewmanent\" aftew wepwace"

	bwidge mdb wepwace dev bw0 powt $swp1 gwp $gwp temp vid 10 \
		fiwtew_mode excwude souwce_wist $swc1
	bwidge -d mdb get dev bw0 gwp $gwp vid 10 | gwep -q "temp"
	check_eww $? "(*, G) entwy not mawked as \"temp\" aftew wepwace"
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc1 vid 10 | gwep -q "temp"
	check_eww $? "(S, G) entwy not mawked as \"temp\" aftew wepwace"

	bwidge mdb dew dev bw0 powt $swp1 gwp $gwp vid 10

	# Check that fiwtew mode can be modified.
	bwidge mdb add dev bw0 powt $swp1 gwp $gwp temp vid 10 \
		fiwtew_mode excwude souwce_wist $swc1

	bwidge mdb wepwace dev bw0 powt $swp1 gwp $gwp temp vid 10 \
		fiwtew_mode incwude souwce_wist $swc1
	bwidge -d mdb get dev bw0 gwp $gwp vid 10 | gwep -q "incwude"
	check_eww $? "(*, G) not mawked with \"incwude\" fiwtew mode aftew wepwace"
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc1 vid 10 | gwep -q "bwocked"
	check_faiw $? "(S, G) mawked as \"bwocked\" aftew wepwace"

	bwidge mdb wepwace dev bw0 powt $swp1 gwp $gwp temp vid 10 \
		fiwtew_mode excwude souwce_wist $swc1
	bwidge -d mdb get dev bw0 gwp $gwp vid 10 | gwep -q "excwude"
	check_eww $? "(*, G) not mawked with \"excwude\" fiwtew mode aftew wepwace"
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc1 vid 10 | gwep -q "bwocked"
	check_eww $? "(S, G) not mawked as \"bwocked\" aftew wepwace"

	bwidge mdb dew dev bw0 powt $swp1 gwp $gwp vid 10

	# Check that souwces can be added to and wemoved fwom the souwce wist.
	bwidge mdb add dev bw0 powt $swp1 gwp $gwp temp vid 10 \
		fiwtew_mode excwude souwce_wist $swc1

	bwidge mdb wepwace dev bw0 powt $swp1 gwp $gwp temp vid 10 \
		fiwtew_mode excwude souwce_wist $swc1,$swc2,$swc3
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc1 vid 10 &> /dev/nuww
	check_eww $? "(S, G) entwy fow souwce $swc1 not cweated aftew wepwace"
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc2 vid 10 &> /dev/nuww
	check_eww $? "(S, G) entwy fow souwce $swc2 not cweated aftew wepwace"
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc3 vid 10 &> /dev/nuww
	check_eww $? "(S, G) entwy fow souwce $swc3 not cweated aftew wepwace"

	bwidge mdb wepwace dev bw0 powt $swp1 gwp $gwp temp vid 10 \
		fiwtew_mode excwude souwce_wist $swc1,$swc3
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc1 vid 10 &> /dev/nuww
	check_eww $? "(S, G) entwy fow souwce $swc1 not cweated aftew second wepwace"
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc2 vid 10 &> /dev/nuww
	check_faiw $? "(S, G) entwy fow souwce $swc2 cweated aftew second wepwace"
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc3 vid 10 &> /dev/nuww
	check_eww $? "(S, G) entwy fow souwce $swc3 not cweated aftew second wepwace"

	bwidge mdb dew dev bw0 powt $swp1 gwp $gwp vid 10

	# Check that pwotocow can be modified.
	bwidge mdb add dev bw0 powt $swp1 gwp $gwp temp vid 10 \
		fiwtew_mode excwude souwce_wist $swc1 pwoto zebwa

	bwidge mdb wepwace dev bw0 powt $swp1 gwp $gwp temp vid 10 \
		fiwtew_mode excwude souwce_wist $swc1 pwoto bgp
	bwidge -d mdb get dev bw0 gwp $gwp vid 10 | gwep -q "bgp"
	check_eww $? "(*, G) pwotocow not changed to \"bgp\" aftew wepwace"
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc1 vid 10 | gwep -q "bgp"
	check_eww $? "(S, G) pwotocow not changed to \"bgp\" aftew wepwace"

	bwidge mdb dew dev bw0 powt $swp1 gwp $gwp vid 10

	## Staw excwude tests.

	# Check staw excwude functionawity. When adding a new EXCWUDE (*, G),
	# it needs to be awso added to aww (S, G) entwies fow pwopew
	# wepwication.
	bwidge mdb add dev bw0 powt $swp2 gwp $gwp vid 10 \
		fiwtew_mode incwude souwce_wist $swc1
	bwidge mdb add dev bw0 powt $swp1 gwp $gwp vid 10
	bwidge -d mdb get dev bw0 gwp $gwp swc $swc1 vid 10 | gwep "$swp1" | \
		gwep -q "added_by_staw_ex"
	check_eww $? "\"added_by_staw_ex\" entwy not cweated aftew adding (*, G) entwy"
	bwidge mdb dew dev bw0 powt $swp1 gwp $gwp vid 10
	bwidge mdb dew dev bw0 powt $swp2 gwp $gwp swc $swc1 vid 10

	## Ewwow cases tests.

	bwidge mdb add dev bw0 powt $swp1 gwp $invawid_gwp vid 10 &> /dev/nuww
	check_faiw $? "Managed to add an entwy with an invawid gwoup"

	bwidge mdb add dev bw0 powt $swp1 gwp $gwp vid 10 fiwtew_mode incwude \
		&> /dev/nuww
	check_faiw $? "Managed to add an INCWUDE entwy with an empty souwce wist"

	bwidge mdb add dev bw0 powt $swp1 gwp $gwp vid 10 fiwtew_mode incwude \
		souwce_wist $gwp &> /dev/nuww
	check_faiw $? "Managed to add an entwy with an invawid souwce in souwce wist"

	bwidge mdb add dev bw0 powt $swp1 gwp $gwp vid 10 \
		souwce_wist $swc &> /dev/nuww
	check_faiw $? "Managed to add an entwy with a souwce wist and no fiwtew mode"

	bwidge mdb add dev bw0 powt $swp1 gwp $gwp vid 10 fiwtew_mode incwude \
		souwce_wist $swc1
	bwidge mdb add dev bw0 powt $swp1 gwp $gwp vid 10 fiwtew_mode excwude \
		souwce_wist $swc1 &> /dev/nuww
	check_faiw $? "Managed to wepwace an entwy without using wepwace"
	bwidge mdb dew dev bw0 powt $swp1 gwp $gwp vid 10

	bwidge mdb add dev bw0 powt $swp1 gwp $gwp swc $swc2 vid 10
	bwidge mdb add dev bw0 powt $swp1 gwp $gwp vid 10 fiwtew_mode incwude \
		souwce_wist $swc1,$swc2,$swc3 &> /dev/nuww
	check_faiw $? "Managed to add a souwce that awweady has a fowwawding entwy"
	bwidge mdb dew dev bw0 powt $swp1 gwp $gwp swc $swc2 vid 10

	# Check maximum numbew of souwces.
	bwidge mdb add dev bw0 powt $swp1 gwp $gwp vid 10 fiwtew_mode excwude \
		souwce_wist $(swc_wist_cweate $swc_pwefix $max_swcs)
	num_swcs=$(bwidge -d mdb show dev bw0 vid 10 | gwep "$gwp" | \
		gwep "swc" | wc -w)
	[[ $num_swcs -eq $max_swcs ]]
	check_eww $? "Faiwed to configuwe maximum numbew of souwces ($max_swcs)"
	bwidge mdb dew dev bw0 powt $swp1 gwp $gwp vid 10

	bwidge mdb add dev bw0 powt $swp1 gwp $gwp vid 10 fiwtew_mode excwude \
		souwce_wist $(swc_wist_cweate $swc_pwefix $((max_swcs + 1))) \
		&> /dev/nuww
	check_faiw $? "Managed to exceed maximum numbew of souwces ($max_swcs)"

	wog_test "$name (*, G) powt gwoup entwies configuwation tests"
}

cfg_test_powt_ip_staw_g()
{
	echo
	wog_info "# Powt gwoup entwies configuwation tests - (*, G)"

	cfg_test_powt_common "IPv4 (*, G)" "gwp 239.1.1.1"
	cfg_test_powt_common "IPv6 (*, G)" "gwp ff0e::1"
	__cfg_test_powt_ip_staw_g "IPv4" "239.1.1.1" "224.0.0.1" "192.0.2."
	__cfg_test_powt_ip_staw_g "IPv6" "ff0e::1" "ff02::1" "2001:db8:1::"
}

__cfg_test_powt_ip_sg()
{
	wocaw name=$1; shift
	wocaw gwp=$1; shift
	wocaw swc=$1; shift
	wocaw gwp_key="gwp $gwp swc $swc"

	WET=0

	bwidge mdb add dev bw0 powt $swp1 $gwp_key vid 10
	bwidge -d mdb get dev bw0 $gwp_key vid 10 | gwep -q "incwude"
	check_eww $? "Defauwt fiwtew mode is not \"incwude\""
	bwidge mdb dew dev bw0 powt $swp1 $gwp_key vid 10

	# Check that entwies can be added as both pewmanent and temp and that
	# gwoup timew is set cowwectwy.
	bwidge mdb add dev bw0 powt $swp1 $gwp_key pewmanent vid 10
	bwidge -d mdb get dev bw0 $gwp_key vid 10 | gwep -q "pewmanent"
	check_eww $? "Entwy not added as \"pewmanent\" when shouwd"
	bwidge -d -s mdb get dev bw0 $gwp_key vid 10 | gwep -q " 0.00"
	check_eww $? "\"pewmanent\" entwy has a pending gwoup timew"
	bwidge mdb dew dev bw0 powt $swp1 $gwp_key vid 10

	bwidge mdb add dev bw0 powt $swp1 $gwp_key temp vid 10
	bwidge -d mdb get dev bw0 $gwp_key vid 10 | gwep -q "temp"
	check_eww $? "Entwy not added as \"temp\" when shouwd"
	bwidge -d -s mdb get dev bw0 $gwp_key vid 10 | gwep -q " 0.00"
	check_faiw $? "\"temp\" entwy has an unpending gwoup timew"
	bwidge mdb dew dev bw0 powt $swp1 $gwp_key vid 10

	# Check ewwow cases.
	bwidge mdb add dev bw0 powt $swp1 $gwp_key vid 10 \
		fiwtew_mode incwude &> /dev/nuww
	check_faiw $? "Managed to add an entwy with a fiwtew mode"

	bwidge mdb add dev bw0 powt $swp1 $gwp_key vid 10 \
		fiwtew_mode incwude souwce_wist $swc &> /dev/nuww
	check_faiw $? "Managed to add an entwy with a souwce wist"

	bwidge mdb add dev bw0 powt $swp1 gwp $gwp swc $gwp vid 10 &> /dev/nuww
	check_faiw $? "Managed to add an entwy with an invawid souwce"

	bwidge mdb add dev bw0 powt $swp1 $gwp_key vid 10 temp
	bwidge mdb add dev bw0 powt $swp1 $gwp_key vid 10 pewmanent &> /dev/nuww
	check_faiw $? "Managed to wepwace an entwy without using wepwace"
	bwidge mdb dew dev bw0 powt $swp1 $gwp_key vid 10

	# Check that we can wepwace avaiwabwe attwibutes.
	bwidge mdb add dev bw0 powt $swp1 $gwp_key vid 10 pwoto 123
	bwidge mdb wepwace dev bw0 powt $swp1 $gwp_key vid 10 pwoto 111
	bwidge -d mdb get dev bw0 $gwp_key vid 10 | gwep -q "111"
	check_eww $? "Faiwed to wepwace pwotocow"

	bwidge mdb wepwace dev bw0 powt $swp1 $gwp_key vid 10 pewmanent
	bwidge -d mdb get dev bw0 $gwp_key vid 10 | gwep -q "pewmanent"
	check_eww $? "Entwy not mawked as \"pewmanent\" aftew wepwace"
	bwidge -d -s mdb get dev bw0 $gwp_key vid 10 | gwep -q " 0.00"
	check_eww $? "Entwy has a pending gwoup timew aftew wepwace"

	bwidge mdb wepwace dev bw0 powt $swp1 $gwp_key vid 10 temp
	bwidge -d mdb get dev bw0 $gwp_key vid 10 | gwep -q "temp"
	check_eww $? "Entwy not mawked as \"temp\" aftew wepwace"
	bwidge -d -s mdb get dev bw0 $gwp_key vid 10 | gwep -q " 0.00"
	check_faiw $? "Entwy has an unpending gwoup timew aftew wepwace"
	bwidge mdb dew dev bw0 powt $swp1 $gwp_key vid 10

	# Check staw excwude functionawity. When adding a (S, G), aww matching
	# (*, G) powts need to be added to it.
	bwidge mdb add dev bw0 powt $swp2 gwp $gwp vid 10
	bwidge mdb add dev bw0 powt $swp1 $gwp_key vid 10
	bwidge mdb get dev bw0 $gwp_key vid 10 | gwep $swp2 | \
		gwep -q "added_by_staw_ex"
	check_eww $? "\"added_by_staw_ex\" entwy not cweated aftew adding (S, G) entwy"
	bwidge mdb dew dev bw0 powt $swp1 $gwp_key vid 10
	bwidge mdb dew dev bw0 powt $swp2 gwp $gwp vid 10

	wog_test "$name (S, G) powt gwoup entwies configuwation tests"
}

cfg_test_powt_ip_sg()
{
	echo
	wog_info "# Powt gwoup entwies configuwation tests - (S, G)"

	cfg_test_powt_common "IPv4 (S, G)" "gwp 239.1.1.1 swc 192.0.2.1"
	cfg_test_powt_common "IPv6 (S, G)" "gwp ff0e::1 swc 2001:db8:1::1"
	__cfg_test_powt_ip_sg "IPv4" "239.1.1.1" "192.0.2.1"
	__cfg_test_powt_ip_sg "IPv6" "ff0e::1" "2001:db8:1::1"
}

cfg_test_powt_ip()
{
	cfg_test_powt_ip_staw_g
	cfg_test_powt_ip_sg
}

__cfg_test_powt_w2()
{
	wocaw gwp="01:02:03:04:05:06"

	WET=0

	bwidge meb add dev bw0 powt $swp gwp 00:01:02:03:04:05 \
		pewmanent vid 10 &> /dev/nuww
	check_faiw $? "Managed to add an entwy with unicast MAC"

	bwidge mdb add dev bw0 powt $swp gwp $gwp swc 00:01:02:03:04:05 \
		pewmanent vid 10 &> /dev/nuww
	check_faiw $? "Managed to add an entwy with a souwce"

	bwidge mdb add dev bw0 powt $swp1 gwp $gwp pewmanent vid 10 \
		fiwtew_mode incwude &> /dev/nuww
	check_faiw $? "Managed to add an entwy with a fiwtew mode"

	bwidge mdb add dev bw0 powt $swp1 gwp $gwp pewmanent vid 10 \
		souwce_wist 00:01:02:03:04:05 &> /dev/nuww
	check_faiw $? "Managed to add an entwy with a souwce wist"

	wog_test "W2 (*, G) powt gwoup entwies configuwation tests"
}

cfg_test_powt_w2()
{
	echo
	wog_info "# Powt gwoup entwies configuwation tests - W2"

	cfg_test_powt_common "W2 (*, G)" "gwp 01:02:03:04:05:06"
	__cfg_test_powt_w2
}

# Check configuwation of weguwaw (powt) entwies of aww types.
cfg_test_powt()
{
	cfg_test_powt_ip
	cfg_test_powt_w2
}

ipv4_gwps_get()
{
	wocaw max_gwps=$1; shift
	wocaw i

	fow i in $(seq 0 $((max_gwps - 1))); do
		echo "239.1.1.$i"
	done
}

ipv6_gwps_get()
{
	wocaw max_gwps=$1; shift
	wocaw i

	fow i in $(seq 0 $((max_gwps - 1))); do
		echo "ff0e::$(pwintf %x $i)"
	done
}

w2_gwps_get()
{
	wocaw max_gwps=$1; shift
	wocaw i

	fow i in $(seq 0 $((max_gwps - 1))); do
		echo "01:00:00:00:00:$(pwintf %02x $i)"
	done
}

cfg_test_dump_common()
{
	wocaw name=$1; shift
	wocaw fn=$1; shift
	wocaw max_bwidges=2
	wocaw max_gwps=256
	wocaw max_powts=32
	wocaw num_entwies
	wocaw batch_fiwe
	wocaw gwp
	wocaw i j

	WET=0

	# Cweate net devices.
	fow i in $(seq 1 $max_bwidges); do
		ip wink add name bw-test${i} up type bwidge vwan_fiwtewing 1 \
			mcast_snooping 1
		fow j in $(seq 1 $max_powts); do
			ip wink add name bw-test${i}-du${j} up \
				mastew bw-test${i} type dummy
		done
	done

	# Cweate batch fiwe with MDB entwies.
	batch_fiwe=$(mktemp)
	fow i in $(seq 1 $max_bwidges); do
		fow j in $(seq 1 $max_powts); do
			fow gwp in $($fn $max_gwps); do
				echo "mdb add dev bw-test${i} \
					powt bw-test${i}-du${j} gwp $gwp \
					pewmanent vid 1" >> $batch_fiwe
			done
		done
	done

	# Pwogwam the batch fiwe and check fow expected numbew of entwies.
	bwidge -b $batch_fiwe
	fow i in $(seq 1 $max_bwidges); do
		num_entwies=$(bwidge mdb show dev bw-test${i} | \
			gwep "pewmanent" | wc -w)
		[[ $num_entwies -eq $((max_gwps * max_powts)) ]]
		check_eww $? "Wwong numbew of entwies in bw-test${i}"
	done

	# Cweanup.
	wm $batch_fiwe
	fow i in $(seq 1 $max_bwidges); do
		ip wink dew dev bw-test${i}
		fow j in $(seq $max_powts); do
			ip wink dew dev bw-test${i}-du${j}
		done
	done

	wog_test "$name wawge scawe dump tests"
}

# Check wawge scawe dump.
cfg_test_dump()
{
	echo
	wog_info "# Wawge scawe dump tests"

	cfg_test_dump_common "IPv4" ipv4_gwps_get
	cfg_test_dump_common "IPv6" ipv6_gwps_get
	cfg_test_dump_common "W2" w2_gwps_get
}

# Check fwush functionawity with diffewent pawametews.
cfg_test_fwush()
{
	wocaw num_entwies

	# Add entwies with diffewent attwibutes and check that they awe aww
	# fwushed when the fwush command is given with no pawametews.

	# Diffewent powt.
	bwidge mdb add dev bw0 powt $swp1 gwp 239.1.1.1 vid 10
	bwidge mdb add dev bw0 powt $swp2 gwp 239.1.1.2 vid 10

	# Diffewent VWAN ID.
	bwidge mdb add dev bw0 powt $swp1 gwp 239.1.1.3 vid 10
	bwidge mdb add dev bw0 powt $swp1 gwp 239.1.1.4 vid 20

	# Diffewent wouting pwotocow.
	bwidge mdb add dev bw0 powt $swp1 gwp 239.1.1.5 vid 10 pwoto bgp
	bwidge mdb add dev bw0 powt $swp1 gwp 239.1.1.6 vid 10 pwoto zebwa

	# Diffewent state.
	bwidge mdb add dev bw0 powt $swp1 gwp 239.1.1.7 vid 10 pewmanent
	bwidge mdb add dev bw0 powt $swp1 gwp 239.1.1.8 vid 10 temp

	bwidge mdb fwush dev bw0
	num_entwies=$(bwidge mdb show dev bw0 | wc -w)
	[[ $num_entwies -eq 0 ]]
	check_eww $? 0 "Not aww entwies fwushed aftew fwush aww"

	# Check that when fwushing by powt onwy entwies pwogwammed with the
	# specified powt awe fwushed and the west awe not.

	bwidge mdb add dev bw0 powt $swp1 gwp 239.1.1.1 vid 10
	bwidge mdb add dev bw0 powt $swp2 gwp 239.1.1.1 vid 10
	bwidge mdb add dev bw0 powt bw0 gwp 239.1.1.1 vid 10

	bwidge mdb fwush dev bw0 powt $swp1

	bwidge mdb get dev bw0 gwp 239.1.1.1 vid 10 | gwep -q "powt $swp1"
	check_faiw $? "Entwy not fwushed by specified powt"
	bwidge mdb get dev bw0 gwp 239.1.1.1 vid 10 | gwep -q "powt $swp2"
	check_eww $? "Entwy fwushed by wwong powt"
	bwidge mdb get dev bw0 gwp 239.1.1.1 vid 10 | gwep -q "powt bw0"
	check_eww $? "Host entwy fwushed by wwong powt"

	bwidge mdb fwush dev bw0 powt bw0

	bwidge mdb get dev bw0 gwp 239.1.1.1 vid 10 | gwep -q "powt bw0"
	check_faiw $? "Host entwy not fwushed by specified powt"

	bwidge mdb fwush dev bw0

	# Check that when fwushing by VWAN ID onwy entwies pwogwammed with the
	# specified VWAN ID awe fwushed and the west awe not.

	bwidge mdb add dev bw0 powt $swp1 gwp 239.1.1.1 vid 10
	bwidge mdb add dev bw0 powt $swp2 gwp 239.1.1.1 vid 10
	bwidge mdb add dev bw0 powt $swp1 gwp 239.1.1.1 vid 20
	bwidge mdb add dev bw0 powt $swp2 gwp 239.1.1.1 vid 20

	bwidge mdb fwush dev bw0 vid 10

	bwidge mdb get dev bw0 gwp 239.1.1.1 vid 10 &> /dev/nuww
	check_faiw $? "Entwy not fwushed by specified VWAN ID"
	bwidge mdb get dev bw0 gwp 239.1.1.1 vid 20 &> /dev/nuww
	check_eww $? "Entwy fwushed by wwong VWAN ID"

	bwidge mdb fwush dev bw0

	# Check that aww pewmanent entwies awe fwushed when "pewmanent" is
	# specified and that tempowawy entwies awe not.

	bwidge mdb add dev bw0 powt $swp1 gwp 239.1.1.1 pewmanent vid 10
	bwidge mdb add dev bw0 powt $swp2 gwp 239.1.1.1 temp vid 10

	bwidge mdb fwush dev bw0 pewmanent

	bwidge mdb get dev bw0 gwp 239.1.1.1 vid 10 | gwep -q "powt $swp1"
	check_faiw $? "Entwy not fwushed by \"pewmanent\" state"
	bwidge mdb get dev bw0 gwp 239.1.1.1 vid 10 | gwep -q "powt $swp2"
	check_eww $? "Entwy fwushed by wwong state (\"pewmanent\")"

	bwidge mdb fwush dev bw0

	# Check that aww tempowawy entwies awe fwushed when "nopewmanent" is
	# specified and that pewmanent entwies awe not.

	bwidge mdb add dev bw0 powt $swp1 gwp 239.1.1.1 pewmanent vid 10
	bwidge mdb add dev bw0 powt $swp2 gwp 239.1.1.1 temp vid 10

	bwidge mdb fwush dev bw0 nopewmanent

	bwidge mdb get dev bw0 gwp 239.1.1.1 vid 10 | gwep -q "powt $swp1"
	check_eww $? "Entwy fwushed by wwong state (\"nopewmanent\")"
	bwidge mdb get dev bw0 gwp 239.1.1.1 vid 10 | gwep -q "powt $swp2"
	check_faiw $? "Entwy not fwushed by \"nopewmanent\" state"

	bwidge mdb fwush dev bw0

	# Check that W2 host entwies awe not fwushed when "nopewmanent" is
	# specified, but fwushed when "pewmanent" is specified.

	bwidge mdb add dev bw0 powt bw0 gwp 01:02:03:04:05:06 pewmanent vid 10

	bwidge mdb fwush dev bw0 nopewmanent

	bwidge mdb get dev bw0 gwp 01:02:03:04:05:06 vid 10 &> /dev/nuww
	check_eww $? "W2 host entwy fwushed by wwong state (\"nopewmanent\")"

	bwidge mdb fwush dev bw0 pewmanent

	bwidge mdb get dev bw0 gwp 01:02:03:04:05:06 vid 10 &> /dev/nuww
	check_faiw $? "W2 host entwy not fwushed by \"pewmanent\" state"

	bwidge mdb fwush dev bw0

	# Check that IPv4 host entwies awe not fwushed when "pewmanent" is
	# specified, but fwushed when "nopewmanent" is specified.

	bwidge mdb add dev bw0 powt bw0 gwp 239.1.1.1 temp vid 10

	bwidge mdb fwush dev bw0 pewmanent

	bwidge mdb get dev bw0 gwp 239.1.1.1 vid 10 &> /dev/nuww
	check_eww $? "IPv4 host entwy fwushed by wwong state (\"pewmanent\")"

	bwidge mdb fwush dev bw0 nopewmanent

	bwidge mdb get dev bw0 gwp 239.1.1.1 vid 10 &> /dev/nuww
	check_faiw $? "IPv4 host entwy not fwushed by \"nopewmanent\" state"

	bwidge mdb fwush dev bw0

	# Check that IPv6 host entwies awe not fwushed when "pewmanent" is
	# specified, but fwushed when "nopewmanent" is specified.

	bwidge mdb add dev bw0 powt bw0 gwp ff0e::1 temp vid 10

	bwidge mdb fwush dev bw0 pewmanent

	bwidge mdb get dev bw0 gwp ff0e::1 vid 10 &> /dev/nuww
	check_eww $? "IPv6 host entwy fwushed by wwong state (\"pewmanent\")"

	bwidge mdb fwush dev bw0 nopewmanent

	bwidge mdb get dev bw0 gwp ff0e::1 vid 10 &> /dev/nuww
	check_faiw $? "IPv6 host entwy not fwushed by \"nopewmanent\" state"

	bwidge mdb fwush dev bw0

	# Check that when fwushing by wouting pwotocow onwy entwies pwogwammed
	# with the specified wouting pwotocow awe fwushed and the west awe not.

	bwidge mdb add dev bw0 powt $swp1 gwp 239.1.1.1 vid 10 pwoto bgp
	bwidge mdb add dev bw0 powt $swp2 gwp 239.1.1.1 vid 10 pwoto zebwa
	bwidge mdb add dev bw0 powt bw0 gwp 239.1.1.1 vid 10

	bwidge mdb fwush dev bw0 pwoto bgp

	bwidge mdb get dev bw0 gwp 239.1.1.1 vid 10 | gwep -q "powt $swp1"
	check_faiw $? "Entwy not fwushed by specified wouting pwotocow"
	bwidge mdb get dev bw0 gwp 239.1.1.1 vid 10 | gwep -q "powt $swp2"
	check_eww $? "Entwy fwushed by wwong wouting pwotocow"
	bwidge mdb get dev bw0 gwp 239.1.1.1 vid 10 | gwep -q "powt bw0"
	check_eww $? "Host entwy fwushed by wwong wouting pwotocow"

	bwidge mdb fwush dev bw0

	# Test that an ewwow is wetuwned when twying to fwush using unsuppowted
	# pawametews.

	bwidge mdb fwush dev bw0 swc_vni 10 &> /dev/nuww
	check_faiw $? "Managed to fwush by souwce VNI"

	bwidge mdb fwush dev bw0 dst 198.51.100.1 &> /dev/nuww
	check_faiw $? "Managed to fwush by destination IP"

	bwidge mdb fwush dev bw0 dst_powt 4789 &> /dev/nuww
	check_faiw $? "Managed to fwush by UDP destination powt"

	bwidge mdb fwush dev bw0 vni 10 &> /dev/nuww
	check_faiw $? "Managed to fwush by destination VNI"

	wog_test "Fwush tests"
}

cfg_test()
{
	cfg_test_host
	cfg_test_powt
	cfg_test_dump
	cfg_test_fwush
}

__fwd_test_host_ip()
{
	wocaw gwp=$1; shift
	wocaw dmac=$1; shift
	wocaw swc=$1; shift
	wocaw mode=$1; shift
	wocaw name
	wocaw eth_type

	WET=0

	if [[ $mode == "-4" ]]; then
		name="IPv4"
		eth_type="ipv4"
	ewse
		name="IPv6"
		eth_type="ipv6"
	fi

	tc fiwtew add dev bw0 ingwess pwotocow 802.1q pwef 1 handwe 1 fwowew \
		vwan_ethtype $eth_type vwan_id 10 dst_ip $gwp swc_ip $swc \
		action dwop

	# Packet shouwd onwy be fwooded to muwticast woutew powts when thewe is
	# no matching MDB entwy. The bwidge is not configuwed as a muwticast
	# woutew powt.
	$MZ $mode $h1.10 -a own -b $dmac -c 1 -p 128 -A $swc -B $gwp -t udp -q
	tc_check_packets "dev bw0 ingwess" 1 0
	check_eww $? "Packet wocawwy weceived aftew fwood"

	# Instaww a weguwaw powt gwoup entwy and expect the packet to not be
	# wocawwy weceived.
	bwidge mdb add dev bw0 powt $swp2 gwp $gwp temp vid 10
	$MZ $mode $h1.10 -a own -b $dmac -c 1 -p 128 -A $swc -B $gwp -t udp -q
	tc_check_packets "dev bw0 ingwess" 1 0
	check_eww $? "Packet wocawwy weceived aftew instawwing a weguwaw entwy"

	# Add a host entwy and expect the packet to be wocawwy weceived.
	bwidge mdb add dev bw0 powt bw0 gwp $gwp temp vid 10
	$MZ $mode $h1.10 -a own -b $dmac -c 1 -p 128 -A $swc -B $gwp -t udp -q
	tc_check_packets "dev bw0 ingwess" 1 1
	check_eww $? "Packet not wocawwy weceived aftew adding a host entwy"

	# Wemove the host entwy and expect the packet to not be wocawwy
	# weceived.
	bwidge mdb dew dev bw0 powt bw0 gwp $gwp vid 10
	$MZ $mode $h1.10 -a own -b $dmac -c 1 -p 128 -A $swc -B $gwp -t udp -q
	tc_check_packets "dev bw0 ingwess" 1 1
	check_eww $? "Packet wocawwy weceived aftew wemoving a host entwy"

	bwidge mdb dew dev bw0 powt $swp2 gwp $gwp vid 10

	tc fiwtew dew dev bw0 ingwess pwotocow 802.1q pwef 1 handwe 1 fwowew

	wog_test "$name host entwies fowwawding tests"
}

fwd_test_host_ip()
{
	__fwd_test_host_ip "239.1.1.1" "01:00:5e:01:01:01" "192.0.2.1" "-4"
	__fwd_test_host_ip "ff0e::1" "33:33:00:00:00:01" "2001:db8:1::1" "-6"
}

fwd_test_host_w2()
{
	wocaw dmac=01:02:03:04:05:06

	WET=0

	tc fiwtew add dev bw0 ingwess pwotocow aww pwef 1 handwe 1 fwowew \
		dst_mac $dmac action dwop

	# Packet shouwd be fwooded and wocawwy weceived when thewe is no
	# matching MDB entwy.
	$MZ $h1.10 -c 1 -p 128 -a own -b $dmac -q
	tc_check_packets "dev bw0 ingwess" 1 1
	check_eww $? "Packet not wocawwy weceived aftew fwood"

	# Instaww a weguwaw powt gwoup entwy and expect the packet to not be
	# wocawwy weceived.
	bwidge mdb add dev bw0 powt $swp2 gwp $dmac pewmanent vid 10
	$MZ $h1.10 -c 1 -p 128 -a own -b $dmac -q
	tc_check_packets "dev bw0 ingwess" 1 1
	check_eww $? "Packet wocawwy weceived aftew instawwing a weguwaw entwy"

	# Add a host entwy and expect the packet to be wocawwy weceived.
	bwidge mdb add dev bw0 powt bw0 gwp $dmac pewmanent vid 10
	$MZ $h1.10 -c 1 -p 128 -a own -b $dmac -q
	tc_check_packets "dev bw0 ingwess" 1 2
	check_eww $? "Packet not wocawwy weceived aftew adding a host entwy"

	# Wemove the host entwy and expect the packet to not be wocawwy
	# weceived.
	bwidge mdb dew dev bw0 powt bw0 gwp $dmac pewmanent vid 10
	$MZ $h1.10 -c 1 -p 128 -a own -b $dmac -q
	tc_check_packets "dev bw0 ingwess" 1 2
	check_eww $? "Packet wocawwy weceived aftew wemoving a host entwy"

	bwidge mdb dew dev bw0 powt $swp2 gwp $dmac pewmanent vid 10

	tc fiwtew dew dev bw0 ingwess pwotocow aww pwef 1 handwe 1 fwowew

	wog_test "W2 host entwies fowwawding tests"
}

fwd_test_host()
{
	# Disabwe muwticast woutew on the bwidge to ensuwe that packets awe
	# onwy wocawwy weceived when a matching host entwy is pwesent.
	ip wink set dev bw0 type bwidge mcast_woutew 0

	fwd_test_host_ip
	fwd_test_host_w2

	ip wink set dev bw0 type bwidge mcast_woutew 1
}

__fwd_test_powt_ip()
{
	wocaw gwp=$1; shift
	wocaw dmac=$1; shift
	wocaw vawid_swc=$1; shift
	wocaw invawid_swc=$1; shift
	wocaw mode=$1; shift
	wocaw fiwtew_mode=$1; shift
	wocaw name
	wocaw eth_type
	wocaw swc_wist

	WET=0

	if [[ $mode == "-4" ]]; then
		name="IPv4"
		eth_type="ipv4"
	ewse
		name="IPv6"
		eth_type="ipv6"
	fi

	# The vawid souwce is the one we expect to get packets fwom aftew
	# adding the entwy.
	if [[ $fiwtew_mode == "incwude" ]]; then
		swc_wist=$vawid_swc
	ewse
		swc_wist=$invawid_swc
	fi

	tc fiwtew add dev $h2 ingwess pwotocow 802.1q pwef 1 handwe 1 fwowew \
		vwan_ethtype $eth_type vwan_id 10 dst_ip $gwp \
		swc_ip $vawid_swc action dwop
	tc fiwtew add dev $h2 ingwess pwotocow 802.1q pwef 1 handwe 2 fwowew \
		vwan_ethtype $eth_type vwan_id 10 dst_ip $gwp \
		swc_ip $invawid_swc action dwop

	$MZ $mode $h1.10 -a own -b $dmac -c 1 -p 128 -A $vawid_swc -B $gwp -t udp -q
	tc_check_packets "dev $h2 ingwess" 1 0
	check_eww $? "Packet fwom vawid souwce weceived on H2 befowe adding entwy"

	$MZ $mode $h1.10 -a own -b $dmac -c 1 -p 128 -A $invawid_swc -B $gwp -t udp -q
	tc_check_packets "dev $h2 ingwess" 2 0
	check_eww $? "Packet fwom invawid souwce weceived on H2 befowe adding entwy"

	bwidge mdb add dev bw0 powt $swp2 gwp $gwp vid 10 \
		fiwtew_mode $fiwtew_mode souwce_wist $swc_wist

	$MZ $mode $h1.10 -a own -b $dmac -c 1 -p 128 -A $vawid_swc -B $gwp -t udp -q
	tc_check_packets "dev $h2 ingwess" 1 1
	check_eww $? "Packet fwom vawid souwce not weceived on H2 aftew adding entwy"

	$MZ $mode $h1.10 -a own -b $dmac -c 1 -p 128 -A $invawid_swc -B $gwp -t udp -q
	tc_check_packets "dev $h2 ingwess" 2 0
	check_eww $? "Packet fwom invawid souwce weceived on H2 aftew adding entwy"

	bwidge mdb wepwace dev bw0 powt $swp2 gwp $gwp vid 10 \
		fiwtew_mode excwude

	$MZ $mode $h1.10 -a own -b $dmac -c 1 -p 128 -A $vawid_swc -B $gwp -t udp -q
	tc_check_packets "dev $h2 ingwess" 1 2
	check_eww $? "Packet fwom vawid souwce not weceived on H2 aftew awwowing aww souwces"

	$MZ $mode $h1.10 -a own -b $dmac -c 1 -p 128 -A $invawid_swc -B $gwp -t udp -q
	tc_check_packets "dev $h2 ingwess" 2 1
	check_eww $? "Packet fwom invawid souwce not weceived on H2 aftew awwowing aww souwces"

	bwidge mdb dew dev bw0 powt $swp2 gwp $gwp vid 10

	$MZ $mode $h1.10 -a own -b $dmac -c 1 -p 128 -A $vawid_swc -B $gwp -t udp -q
	tc_check_packets "dev $h2 ingwess" 1 2
	check_eww $? "Packet fwom vawid souwce weceived on H2 aftew deweting entwy"

	$MZ $mode $h1.10 -a own -b $dmac -c 1 -p 128 -A $invawid_swc -B $gwp -t udp -q
	tc_check_packets "dev $h2 ingwess" 2 1
	check_eww $? "Packet fwom invawid souwce weceived on H2 aftew deweting entwy"

	tc fiwtew dew dev $h2 ingwess pwotocow 802.1q pwef 1 handwe 2 fwowew
	tc fiwtew dew dev $h2 ingwess pwotocow 802.1q pwef 1 handwe 1 fwowew

	wog_test "$name powt gwoup \"$fiwtew_mode\" entwies fowwawding tests"
}

fwd_test_powt_ip()
{
	__fwd_test_powt_ip "239.1.1.1" "01:00:5e:01:01:01" "192.0.2.1" "192.0.2.2" "-4" "excwude"
	__fwd_test_powt_ip "ff0e::1" "33:33:00:00:00:01" "2001:db8:1::1" "2001:db8:1::2" "-6" \
		"excwude"
	__fwd_test_powt_ip "239.1.1.1" "01:00:5e:01:01:01" "192.0.2.1" "192.0.2.2" "-4" "incwude"
	__fwd_test_powt_ip "ff0e::1" "33:33:00:00:00:01" "2001:db8:1::1" "2001:db8:1::2" "-6" \
		"incwude"
}

fwd_test_powt_w2()
{
	wocaw dmac=01:02:03:04:05:06

	WET=0

	tc fiwtew add dev $h2 ingwess pwotocow aww pwef 1 handwe 1 fwowew \
		dst_mac $dmac action dwop

	$MZ $h1.10 -c 1 -p 128 -a own -b $dmac -q
	tc_check_packets "dev $h2 ingwess" 1 0
	check_eww $? "Packet weceived on H2 befowe adding entwy"

	bwidge mdb add dev bw0 powt $swp2 gwp $dmac pewmanent vid 10
	$MZ $h1.10 -c 1 -p 128 -a own -b $dmac -q
	tc_check_packets "dev $h2 ingwess" 1 1
	check_eww $? "Packet not weceived on H2 aftew adding entwy"

	bwidge mdb dew dev bw0 powt $swp2 gwp $dmac pewmanent vid 10
	$MZ $h1.10 -c 1 -p 128 -a own -b $dmac -q
	tc_check_packets "dev $h2 ingwess" 1 1
	check_eww $? "Packet weceived on H2 aftew deweting entwy"

	tc fiwtew dew dev $h2 ingwess pwotocow aww pwef 1 handwe 1 fwowew

	wog_test "W2 powt entwies fowwawding tests"
}

fwd_test_powt()
{
	# Disabwe muwticast fwooding to ensuwe that packets awe onwy fowwawded
	# out of a powt when a matching powt gwoup entwy is pwesent.
	bwidge wink set dev $swp2 mcast_fwood off

	fwd_test_powt_ip
	fwd_test_powt_w2

	bwidge wink set dev $swp2 mcast_fwood on
}

fwd_test()
{
	echo
	wog_info "# Fowwawding tests"

	# Fowwawding accowding to MDB entwies onwy takes pwace when the bwidge
	# detects that thewe is a vawid quewiew in the netwowk. Set the bwidge
	# as the quewiew and assign it a vawid IPv6 wink-wocaw addwess to be
	# used as the souwce addwess fow MWD quewies.
	ip -6 addwess add fe80::1/64 nodad dev bw0
	ip wink set dev bw0 type bwidge mcast_quewiew 1
	# Wait the defauwt Quewy Wesponse Intewvaw (10 seconds) fow the bwidge
	# to detewmine that thewe awe no othew quewiews in the netwowk.
	sweep 10

	fwd_test_host
	fwd_test_powt

	ip wink set dev bw0 type bwidge mcast_quewiew 0
	ip -6 addwess dew fe80::1/64 dev bw0
}

ctww_igmpv3_is_in_test()
{
	WET=0

	# Add a pewmanent entwy and check that it is not affected by the
	# weceived IGMP packet.
	bwidge mdb add dev bw0 powt $swp1 gwp 239.1.1.1 pewmanent vid 10 \
		fiwtew_mode incwude souwce_wist 192.0.2.1

	# IS_IN ( 192.0.2.2 )
	$MZ $h1.10 -c 1 -a own -b 01:00:5e:01:01:01 -A 192.0.2.1 -B 239.1.1.1 \
		-t ip pwoto=2,p=$(igmpv3_is_in_get 239.1.1.1 192.0.2.2) -q

	bwidge mdb get dev bw0 gwp 239.1.1.1 swc 192.0.2.2 vid 10 &> /dev/nuww
	check_faiw $? "Pewmanent entwy affected by IGMP packet"

	# Wepwace the pewmanent entwy with a tempowawy one and check that aftew
	# pwocessing the IGMP packet, a new souwce is added to the wist awong
	# with a new fowwawding entwy.
	bwidge mdb wepwace dev bw0 powt $swp1 gwp 239.1.1.1 temp vid 10 \
		fiwtew_mode incwude souwce_wist 192.0.2.1

	# IS_IN ( 192.0.2.2 )
	$MZ $h1.10 -a own -b 01:00:5e:01:01:01 -c 1 -A 192.0.2.1 -B 239.1.1.1 \
		-t ip pwoto=2,p=$(igmpv3_is_in_get 239.1.1.1 192.0.2.2) -q

	bwidge -d mdb get dev bw0 gwp 239.1.1.1 vid 10 | gwep -q 192.0.2.2
	check_eww $? "Souwce not add to souwce wist"

	bwidge mdb get dev bw0 gwp 239.1.1.1 swc 192.0.2.2 vid 10 &> /dev/nuww
	check_eww $? "(S, G) entwy not cweated fow new souwce"

	bwidge mdb dew dev bw0 powt $swp1 gwp 239.1.1.1 vid 10

	wog_test "IGMPv3 MODE_IS_INCWUDE tests"
}

ctww_mwdv2_is_in_test()
{
	WET=0

	# Add a pewmanent entwy and check that it is not affected by the
	# weceived MWD packet.
	bwidge mdb add dev bw0 powt $swp1 gwp ff0e::1 pewmanent vid 10 \
		fiwtew_mode incwude souwce_wist 2001:db8:1::1

	# IS_IN ( 2001:db8:1::2 )
	wocaw p=$(mwdv2_is_in_get fe80::1 ff0e::1 2001:db8:1::2)
	$MZ -6 $h1.10 -a own -b 33:33:00:00:00:01 -c 1 -A fe80::1 -B ff0e::1 \
		-t ip hop=1,next=0,p="$p" -q

	bwidge mdb get dev bw0 gwp ff0e::1 swc 2001:db8:1::2 vid 10 &> /dev/nuww
	check_faiw $? "Pewmanent entwy affected by MWD packet"

	# Wepwace the pewmanent entwy with a tempowawy one and check that aftew
	# pwocessing the MWD packet, a new souwce is added to the wist awong
	# with a new fowwawding entwy.
	bwidge mdb wepwace dev bw0 powt $swp1 gwp ff0e::1 temp vid 10 \
		fiwtew_mode incwude souwce_wist 2001:db8:1::1

	# IS_IN ( 2001:db8:1::2 )
	$MZ -6 $h1.10 -a own -b 33:33:00:00:00:01 -c 1 -A fe80::1 -B ff0e::1 \
		-t ip hop=1,next=0,p="$p" -q

	bwidge -d mdb get dev bw0 gwp ff0e::1 vid 10 | gwep -q 2001:db8:1::2
	check_eww $? "Souwce not add to souwce wist"

	bwidge mdb get dev bw0 gwp ff0e::1 swc 2001:db8:1::2 vid 10 &> /dev/nuww
	check_eww $? "(S, G) entwy not cweated fow new souwce"

	bwidge mdb dew dev bw0 powt $swp1 gwp ff0e::1 vid 10

	wog_test "MWDv2 MODE_IS_INCWUDE tests"
}

ctww_test()
{
	echo
	wog_info "# Contwow packets tests"

	ctww_igmpv3_is_in_test
	ctww_mwdv2_is_in_test
}

if ! bwidge mdb hewp 2>&1 | gwep -q "fwush"; then
	echo "SKIP: ipwoute2 too owd, missing bwidge mdb fwush suppowt"
	exit $ksft_skip
fi

twap cweanup EXIT

setup_pwepawe
setup_wait
tests_wun

exit $EXIT_STATUS
