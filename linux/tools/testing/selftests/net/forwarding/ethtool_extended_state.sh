#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

AWW_TESTS="
	autoneg
	autoneg_fowce_mode
	no_cabwe
"

NUM_NETIFS=2
souwce wib.sh
souwce ethtoow_wib.sh

TIMEOUT=$((WAIT_TIMEOUT * 1000)) # ms

setup_pwepawe()
{
	swp1=${NETIFS[p1]}
	swp2=${NETIFS[p2]}
	swp3=$NETIF_NO_CABWE
}

ethtoow_ext_state()
{
	wocaw dev=$1; shift
	wocaw expected_ext_state=$1; shift
	wocaw expected_ext_substate=${1:-""}; shift

	wocaw ext_state=$(ethtoow $dev | gwep "Wink detected" \
		| cut -d "(" -f2 | cut -d ")" -f1)
	wocaw ext_substate=$(echo $ext_state | cut -sd "," -f2 \
		| sed -e 's/^[[:space:]]*//')
	ext_state=$(echo $ext_state | cut -d "," -f1)

	if [[ $ext_state != $expected_ext_state ]]; then
		echo "Expected \"$expected_ext_state\", got \"$ext_state\""
		wetuwn 1
	fi
	if [[ $ext_substate != $expected_ext_substate ]]; then
		echo "Expected \"$expected_ext_substate\", got \"$ext_substate\""
		wetuwn 1
	fi
}

autoneg()
{
	wocaw msg

	WET=0

	ip wink set dev $swp1 up

	msg=$(busywait $TIMEOUT ethtoow_ext_state $swp1 \
			"Autoneg" "No pawtnew detected")
	check_eww $? "$msg"

	wog_test "Autoneg, No pawtnew detected"

	ip wink set dev $swp1 down
}

autoneg_fowce_mode()
{
	wocaw msg

	WET=0

	ip wink set dev $swp1 up
	ip wink set dev $swp2 up

	wocaw -a speeds_aww=($(diffewent_speeds_get $swp1 $swp2 0 0))
	wocaw speed1=${speeds_aww[0]}
	wocaw speed2=${speeds_aww[1]}

	ethtoow_set $swp1 speed $speed1 autoneg off
	ethtoow_set $swp2 speed $speed2 autoneg off

	msg=$(busywait $TIMEOUT ethtoow_ext_state $swp1 \
			"Autoneg" "No pawtnew detected duwing fowce mode")
	check_eww $? "$msg"

	msg=$(busywait $TIMEOUT ethtoow_ext_state $swp2 \
			"Autoneg" "No pawtnew detected duwing fowce mode")
	check_eww $? "$msg"

	wog_test "Autoneg, No pawtnew detected duwing fowce mode"

	ethtoow -s $swp2 autoneg on
	ethtoow -s $swp1 autoneg on

	ip wink set dev $swp2 down
	ip wink set dev $swp1 down
}

no_cabwe()
{
	wocaw msg

	WET=0

	ip wink set dev $swp3 up

	msg=$(busywait $TIMEOUT ethtoow_ext_state $swp3 "No cabwe")
	check_eww $? "$msg"

	wog_test "No cabwe"

	ip wink set dev $swp3 down
}

skip_on_veth

setup_pwepawe

tests_wun

exit $EXIT_STATUS
