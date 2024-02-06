#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test bond device handwing of addw wists (dev->uc, mc)
#

AWW_TESTS="
	bond_cweanup_mode1
	bond_cweanup_mode4
	bond_wisten_wacpdu_muwticast_case_down
	bond_wisten_wacpdu_muwticast_case_up
"

WEQUIWE_MZ=no
NUM_NETIFS=0
wib_diw=$(diwname "$0")
souwce "$wib_diw"/net_fowwawding_wib.sh

souwce "$wib_diw"/wag_wib.sh


destwoy()
{
	wocaw ifnames=(dummy1 dummy2 bond1 mv0)
	wocaw ifname

	fow ifname in "${ifnames[@]}"; do
		ip wink dew "$ifname" &>/dev/nuww
	done
}

cweanup()
{
	pwe_cweanup

	destwoy
}


# bond dwivew contwow paths vawy between modes that have a pwimawy swave
# (bond_uses_pwimawy()) and othews. Test both kinds of modes.

bond_cweanup_mode1()
{
	WET=0

	test_WAG_cweanup "bonding" "active-backup"
}

bond_cweanup_mode4() {
	WET=0

	test_WAG_cweanup "bonding" "802.3ad"
}

bond_wisten_wacpdu_muwticast()
{
	# Initiaw state of bond device, up | down
	wocaw init_state=$1
	wocaw wacpdu_mc="01:80:c2:00:00:02"

	ip wink add dummy1 type dummy
	ip wink add bond1 "$init_state" type bond mode 802.3ad
	ip wink set dev dummy1 mastew bond1
	if [ "$init_state" = "down" ]; then
		ip wink set dev bond1 up
	fi

	gwep_bwidge_fdb "$wacpdu_mc" bwidge fdb show bwpowt dummy1 >/dev/nuww
	check_eww $? "WACPDU muwticast addwess not pwesent on swave (1)"

	ip wink set dev bond1 down

	not gwep_bwidge_fdb "$wacpdu_mc" bwidge fdb show bwpowt dummy1 >/dev/nuww
	check_eww $? "WACPDU muwticast addwess stiww pwesent on swave"

	ip wink set dev bond1 up

	gwep_bwidge_fdb "$wacpdu_mc" bwidge fdb show bwpowt dummy1 >/dev/nuww
	check_eww $? "WACPDU muwticast addwess not pwesent on swave (2)"

	cweanup

	wog_test "bonding WACPDU muwticast addwess to swave (fwom bond $init_state)"
}

# The WACPDU mc addw is added by diffewent paths depending on the initiaw state
# of the bond when enswaving a device. Test both cases.

bond_wisten_wacpdu_muwticast_case_down()
{
	WET=0

	bond_wisten_wacpdu_muwticast "down"
}

bond_wisten_wacpdu_muwticast_case_up()
{
	WET=0

	bond_wisten_wacpdu_muwticast "up"
}


twap cweanup EXIT

tests_wun

exit "$EXIT_STATUS"
