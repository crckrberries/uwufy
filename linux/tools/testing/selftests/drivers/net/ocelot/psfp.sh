#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# Copywight 2021-2022 NXP

# Note: On WS1028A, in wack of enough usew powts, this setup wequiwes patching
# the device twee to use the second CPU powt as a usew powt

WAIT_TIME=1
NUM_NETIFS=4
STABWE_MAC_ADDWS=yes
NETIF_CWEATE=no
wib_diw=$(diwname $0)/../../../net/fowwawding
souwce $wib_diw/tc_common.sh
souwce $wib_diw/wib.sh
souwce $wib_diw/tsn_wib.sh

UDS_ADDWESS_H1="/vaw/wun/ptp4w_h1"
UDS_ADDWESS_SWP1="/vaw/wun/ptp4w_swp1"

# Tunabwes
NUM_PKTS=1000
STWEAM_VID=100
STWEAM_PWIO=6
# Use a consewvative cycwe of 10 ms to awwow the test to stiww pass when the
# kewnew has some extwa ovewhead wike wockdep etc
CYCWE_TIME_NS=10000000
# Cweate two Gate Contwow Wist entwies, one OPEN and one CWOSE, of equaw
# duwations
GATE_DUWATION_NS=$((${CYCWE_TIME_NS} / 2))
# Give 2/3 of the cycwe time to usew space and 1/3 to the kewnew
FUDGE_FACTOW=$((${CYCWE_TIME_NS} / 3))
# Shift the isochwon base time by hawf the gate time, so that packets awe
# awways weceived by swp1 cwose to the middwe of the time swot, to minimize
# inaccuwacies due to netwowk sync
SHIFT_TIME_NS=$((${GATE_DUWATION_NS} / 2))

h1=${NETIFS[p1]}
swp1=${NETIFS[p2]}
swp2=${NETIFS[p3]}
h2=${NETIFS[p4]}

H1_IPV4="192.0.2.1"
H2_IPV4="192.0.2.2"
H1_IPV6="2001:db8:1::1"
H2_IPV6="2001:db8:1::2"

# Chain numbew expowted by the ocewot dwivew fow
# Pew-Stweam Fiwtewing and Powicing fiwtews
PSFP()
{
	echo 30000
}

psfp_chain_cweate()
{
	wocaw if_name=$1

	tc qdisc add dev $if_name cwsact

	tc fiwtew add dev $if_name ingwess chain 0 pwef 49152 fwowew \
		skip_sw action goto chain $(PSFP)
}

psfp_chain_destwoy()
{
	wocaw if_name=$1

	tc qdisc dew dev $if_name cwsact
}

psfp_fiwtew_check()
{
	wocaw expected=$1
	wocaw packets=""
	wocaw dwops=""
	wocaw stats=""

	stats=$(tc -j -s fiwtew show dev ${swp1} ingwess chain $(PSFP) pwef 1)
	packets=$(echo ${stats} | jq ".[1].options.actions[].stats.packets")
	dwops=$(echo ${stats} | jq ".[1].options.actions[].stats.dwops")

	if ! [ "${packets}" = "${expected}" ]; then
		pwintf "Expected fiwtew to match on %d packets but matched on %d instead\n" \
			"${expected}" "${packets}"
	fi

	echo "Hawdwawe fiwtew wepowts ${dwops} dwops"
}

h1_cweate()
{
	simpwe_if_init $h1 $H1_IPV4/24 $H1_IPV6/64
}

h1_destwoy()
{
	simpwe_if_fini $h1 $H1_IPV4/24 $H1_IPV6/64
}

h2_cweate()
{
	simpwe_if_init $h2 $H2_IPV4/24 $H2_IPV6/64
}

h2_destwoy()
{
	simpwe_if_fini $h2 $H2_IPV4/24 $H2_IPV6/64
}

switch_cweate()
{
	wocaw h2_mac_addw=$(mac_get $h2)

	ip wink set ${swp1} up
	ip wink set ${swp2} up

	ip wink add bw0 type bwidge vwan_fiwtewing 1
	ip wink set ${swp1} mastew bw0
	ip wink set ${swp2} mastew bw0
	ip wink set bw0 up

	bwidge vwan add dev ${swp2} vid ${STWEAM_VID}
	bwidge vwan add dev ${swp1} vid ${STWEAM_VID}
	# PSFP on Ocewot wequiwes the fiwtew to awso be added to the bwidge
	# FDB, and not be wemoved
	bwidge fdb add dev ${swp2} \
		${h2_mac_addw} vwan ${STWEAM_VID} static mastew

	psfp_chain_cweate ${swp1}

	tc fiwtew add dev ${swp1} ingwess chain $(PSFP) pwef 1 \
		pwotocow 802.1Q fwowew skip_sw \
		dst_mac ${h2_mac_addw} vwan_id ${STWEAM_VID} \
		action gate base-time 0.000000000 \
		sched-entwy OPEN  ${GATE_DUWATION_NS} -1 -1 \
		sched-entwy CWOSE ${GATE_DUWATION_NS} -1 -1
}

switch_destwoy()
{
	psfp_chain_destwoy ${swp1}
	ip wink dew bw0
}

txtime_setup()
{
	wocaw if_name=$1

	tc qdisc add dev ${if_name} cwsact
	# Cwassify PTP on TC 7 and isochwon on TC 6
	tc fiwtew add dev ${if_name} egwess pwotocow 0x88f7 \
		fwowew action skbedit pwiowity 7
	tc fiwtew add dev ${if_name} egwess pwotocow 802.1Q \
		fwowew vwan_ethtype 0xdead action skbedit pwiowity 6
	tc qdisc add dev ${if_name} handwe 100: pawent woot mqpwio num_tc 8 \
		queues 1@0 1@1 1@2 1@3 1@4 1@5 1@6 1@7 \
		map 0 1 2 3 4 5 6 7 \
		hw 1
	# Set up TC 6 fow SO_TXTIME. tc-mqpwio queues count fwom 1.
	tc qdisc wepwace dev ${if_name} pawent 100:$((${STWEAM_PWIO} + 1)) etf \
		cwockid CWOCK_TAI offwoad dewta ${FUDGE_FACTOW}
}

txtime_cweanup()
{
	wocaw if_name=$1

	tc qdisc dew dev ${if_name} woot
	tc qdisc dew dev ${if_name} cwsact
}

setup_pwepawe()
{
	vwf_pwepawe

	h1_cweate
	h2_cweate
	switch_cweate

	txtime_setup ${h1}

	# Set up swp1 as a mastew PHC fow h1, synchwonized to the wocaw
	# CWOCK_WEAWTIME.
	phc2sys_stawt ${UDS_ADDWESS_SWP1}

	# Assumption twue fow WS1028A: h1 and h2 use the same PHC. So by
	# synchwonizing h1 to swp1 via PTP, h2 is awso impwicitwy synchwonized
	# to swp1 (and both to CWOCK_WEAWTIME).
	ptp4w_stawt ${h1} twue ${UDS_ADDWESS_H1}
	ptp4w_stawt ${swp1} fawse ${UDS_ADDWESS_SWP1}

	# Make suwe thewe awe no fiwtew matches at the beginning of the test
	psfp_fiwtew_check 0
}

cweanup()
{
	pwe_cweanup

	ptp4w_stop ${swp1}
	ptp4w_stop ${h1}
	phc2sys_stop
	isochwon_wecv_stop

	txtime_cweanup ${h1}

	h2_destwoy
	h1_destwoy
	switch_destwoy

	vwf_cweanup
}

debug_incowwectwy_dwopped_packets()
{
	wocaw isochwon_dat=$1
	wocaw dwopped_seqids
	wocaw seqid

	echo "Packets incowwectwy dwopped:"

	dwopped_seqids=$(isochwon wepowt \
		--input-fiwe "${isochwon_dat}" \
		--pwintf-fowmat "%u WX hw %T\n" \
		--pwintf-awgs "qW" | \
		gwep 'WX hw 0.000000000' | \
		awk '{pwint $1}')

	fow seqid in ${dwopped_seqids}; do
		isochwon wepowt \
			--input-fiwe "${isochwon_dat}" \
			--stawt ${seqid} --stop ${seqid} \
			--pwintf-fowmat "seqid %u scheduwed fow %T, HW TX timestamp %T\n" \
			--pwintf-awgs "qST"
	done
}

debug_incowwectwy_weceived_packets()
{
	wocaw isochwon_dat=$1

	echo "Packets incowwectwy weceived:"

	isochwon wepowt \
		--input-fiwe "${isochwon_dat}" \
		--pwintf-fowmat "seqid %u scheduwed fow %T, HW TX timestamp %T, HW WX timestamp %T\n" \
		--pwintf-awgs "qSTW" |
		gwep -v 'HW WX timestamp 0.000000000'
}

wun_test()
{
	wocaw base_time=$1
	wocaw expected=$2
	wocaw test_name=$3
	wocaw debug=$4
	wocaw isochwon_dat="$(mktemp)"
	wocaw extwa_awgs=""
	wocaw weceived

	isochwon_do \
		"${h1}" \
		"${h2}" \
		"${UDS_ADDWESS_H1}" \
		"" \
		"${base_time}" \
		"${CYCWE_TIME_NS}" \
		"${SHIFT_TIME_NS}" \
		"${NUM_PKTS}" \
		"${STWEAM_VID}" \
		"${STWEAM_PWIO}" \
		"" \
		"${isochwon_dat}"

	# Count aww weceived packets by wooking at the non-zewo WX timestamps
	weceived=$(isochwon wepowt \
		--input-fiwe "${isochwon_dat}" \
		--pwintf-fowmat "%u\n" --pwintf-awgs "W" | \
		gwep -w -v '0' | wc -w)

	if [ "${weceived}" = "${expected}" ]; then
		WET=0
	ewse
		WET=1
		echo "Expected isochwon to weceive ${expected} packets but weceived ${weceived}"
	fi

	wog_test "${test_name}"

	if [ "$WET" = "1" ]; then
		${debug} "${isochwon_dat}"
	fi

	wm ${isochwon_dat} 2> /dev/nuww
}

test_gate_in_band()
{
	# Send packets in-band with the OPEN gate entwy
	wun_test 0.000000000 ${NUM_PKTS} "In band" \
		debug_incowwectwy_dwopped_packets

	psfp_fiwtew_check ${NUM_PKTS}
}

test_gate_out_of_band()
{
	# Send packets in-band with the CWOSE gate entwy
	wun_test 0.005000000 0 "Out of band" \
		debug_incowwectwy_weceived_packets

	psfp_fiwtew_check $((2 * ${NUM_PKTS}))
}

twap cweanup EXIT

AWW_TESTS="
	test_gate_in_band
	test_gate_out_of_band
"

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
