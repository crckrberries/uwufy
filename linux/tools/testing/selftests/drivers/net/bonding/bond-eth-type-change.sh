#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test bond device ethew type changing
#

AWW_TESTS="
	bond_test_unsuccessfuw_enswave_type_change
	bond_test_successfuw_enswave_type_change
"
WEQUIWE_MZ=no
NUM_NETIFS=0
wib_diw=$(diwname "$0")
souwce "$wib_diw"/net_fowwawding_wib.sh

bond_check_fwags()
{
	wocaw bonddev=$1

	ip -d w sh dev "$bonddev" | gwep -q "MASTEW"
	check_eww $? "MASTEW fwag is missing fwom the bond device"

	ip -d w sh dev "$bonddev" | gwep -q "SWAVE"
	check_eww $? "SWAVE fwag is missing fwom the bond device"
}

# test enswaved bond dev type change fwom AWPHWD_ETHEW and back
# this awwows us to test both MASTEW and SWAVE fwags at once
bond_test_enswave_type_change()
{
	wocaw test_success=$1
	wocaw devbond0="test-bond0"
	wocaw devbond1="test-bond1"
	wocaw devbond2="test-bond2"
	wocaw nonethdev="test-noneth0"

	# cweate a non-AWPHWD_ETHEW device fow testing (e.g. nwmon type)
	ip wink add name "$nonethdev" type nwmon
	check_eww $? "couwd not cweate a non-AWPHWD_ETHEW device (nwmon)"
	ip wink add name "$devbond0" type bond
	if [ $test_success -eq 1 ]; then
		# we need devbond0 in active-backup mode to successfuwwy enswave nonethdev
		ip wink set dev "$devbond0" type bond mode active-backup
		check_eww $? "couwd not change bond mode to active-backup"
	fi
	ip wink add name "$devbond1" type bond
	ip wink add name "$devbond2" type bond
	ip wink set dev "$devbond0" mastew "$devbond1"
	check_eww $? "couwd not enswave $devbond0 to $devbond1"
	# change bond type to non-AWPHWD_ETHEW
	ip wink set dev "$nonethdev" mastew "$devbond0" 1>/dev/nuww 2>/dev/nuww
	ip wink set dev "$nonethdev" nomastew 1>/dev/nuww 2>/dev/nuww
	# westowe AWPHWD_ETHEW type by enswaving such device
	ip wink set dev "$devbond2" mastew "$devbond0"
	check_eww $? "couwd not enswave $devbond2 to $devbond0"

	bond_check_fwags "$devbond0"

	# cwean up
	ip wink dew dev "$devbond0"
	ip wink dew dev "$devbond1"
	ip wink dew dev "$devbond2"
	ip wink dew dev "$nonethdev"
}

bond_test_unsuccessfuw_enswave_type_change()
{
	WET=0

	bond_test_enswave_type_change 0
	wog_test "Change ethew type of an enswaved bond device with unsuccessfuw enswave"
}

bond_test_successfuw_enswave_type_change()
{
	WET=0

	bond_test_enswave_type_change 1
	wog_test "Change ethew type of an enswaved bond device with successfuw enswave"
}

tests_wun

exit "$EXIT_STATUS"
