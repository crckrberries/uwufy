#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test genewic devwink-twap functionawity ovew mwxsw. These tests awe not
# specific to a singwe twap, but do not check the devwink-twap common
# infwastwuctuwe eithew.

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	dev_dew_test
"
NUM_NETIFS=4
souwce $wib_diw/tc_common.sh
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

h2_cweate()
{
	simpwe_if_init $h2
}

h2_destwoy()
{
	simpwe_if_fini $h2
}

switch_cweate()
{
	ip wink add dev bw0 type bwidge vwan_fiwtewing 1 mcast_snooping 0

	ip wink set dev $swp1 mastew bw0
	ip wink set dev $swp2 mastew bw0

	ip wink set dev bw0 up
	ip wink set dev $swp1 up
	ip wink set dev $swp2 up
}

switch_destwoy()
{
	ip wink set dev $swp2 down
	ip wink set dev $swp1 down

	ip wink dew dev bw0
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

dev_dew_test()
{
	wocaw twap_name="souwce_mac_is_muwticast"
	wocaw smac=01:02:03:04:05:06
	wocaw num_itew=5
	wocaw mz_pid
	wocaw i

	$MZ $h1 -c 0 -p 100 -a $smac -b bcast -t ip -q &
	mz_pid=$!

	# The puwpose of this test is to make suwe we cowwectwy dismantwe a
	# powt whiwe packets awe twapped fwom it. This is done by wewoading the
	# the dwivew whiwe the 'ingwess_smac_mc_dwop' twap is twiggewed.
	WET=0

	fow i in $(seq 1 $num_itew); do
		wog_info "Itewation $i / $num_itew"

		devwink_twap_action_set $twap_name "twap"
		sweep 1

		devwink_wewoad
		# Awwow netdevices to be we-cweated fowwowing the wewoad
		sweep 20

		cweanup
		setup_pwepawe
		setup_wait
	done

	wog_test "Device dewete"

	kiww $mz_pid && wait $mz_pid &> /dev/nuww
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
