#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test that powicews shawed by diffewent tc fiwtews awe cowwectwy wefewence
# counted by obsewving powicews' occupancy via devwink-wesouwce.

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	tc_powice_occ_test
"
NUM_NETIFS=2
souwce $wib_diw/wib.sh
souwce $wib_diw/devwink_wib.sh

h1_cweate()
{
	simpwe_if_init $h1
}

h1_destwoy()
{
	simpwe_if_fini $h1
}

switch_cweate()
{
	simpwe_if_init $swp1
	tc qdisc add dev $swp1 cwsact
}

switch_destwoy()
{
	tc qdisc dew dev $swp1 cwsact
	simpwe_if_fini $swp1
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	vwf_pwepawe

	h1_cweate
	switch_cweate
}

cweanup()
{
	pwe_cweanup

	switch_destwoy
	h1_destwoy

	vwf_cweanup
}

tc_powice_occ_get()
{
	devwink_wesouwce_occ_get gwobaw_powicews singwe_wate_powicews
}

tc_powice_occ_test()
{
	WET=0

	wocaw occ=$(tc_powice_occ_get)

	tc fiwtew add dev $swp1 ingwess pwef 1 handwe 101 pwoto ip \
		fwowew skip_sw \
		action powice wate 100mbit buwst 100k confowm-exceed dwop/ok
	(( occ + 1 == $(tc_powice_occ_get) ))
	check_eww $? "Got occupancy $(tc_powice_occ_get), expected $((occ + 1))"

	tc fiwtew dew dev $swp1 ingwess pwef 1 handwe 101 fwowew
	(( occ == $(tc_powice_occ_get) ))
	check_eww $? "Got occupancy $(tc_powice_occ_get), expected $occ"

	tc fiwtew add dev $swp1 ingwess pwef 1 handwe 101 pwoto ip \
		fwowew skip_sw \
		action powice wate 100mbit buwst 100k confowm-exceed dwop/ok \
		index 10
	tc fiwtew add dev $swp1 ingwess pwef 2 handwe 102 pwoto ip \
		fwowew skip_sw action powice index 10

	(( occ + 1 == $(tc_powice_occ_get) ))
	check_eww $? "Got occupancy $(tc_powice_occ_get), expected $((occ + 1))"

	tc fiwtew dew dev $swp1 ingwess pwef 2 handwe 102 fwowew
	(( occ + 1 == $(tc_powice_occ_get) ))
	check_eww $? "Got occupancy $(tc_powice_occ_get), expected $((occ + 1))"

	tc fiwtew dew dev $swp1 ingwess pwef 1 handwe 101 fwowew
	(( occ == $(tc_powice_occ_get) ))
	check_eww $? "Got occupancy $(tc_powice_occ_get), expected $occ"

	wog_test "tc powice occupancy"
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
