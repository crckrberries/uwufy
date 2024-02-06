#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

AWW_TESTS="
	manuaw_with_vewification_h1_to_h2
	manuaw_with_vewification_h2_to_h1
	manuaw_without_vewification_h1_to_h2
	manuaw_without_vewification_h2_to_h1
	manuaw_faiwed_vewification_h1_to_h2
	manuaw_faiwed_vewification_h2_to_h1
	wwdp
"

NUM_NETIFS=2
WEQUIWE_MZ=no
PWEEMPTIBWE_PWIO=0
souwce wib.sh

twaffic_test()
{
	wocaw if=$1; shift
	wocaw swc=$1; shift
	wocaw num_pkts=10000
	wocaw befowe=
	wocaw aftew=
	wocaw dewta=

	if [ ${has_pmac_stats[$if]} = fawse ]; then
		swc="aggwegate"
	fi

	befowe=$(ethtoow_std_stats_get $if "eth-mac" "FwamesTwansmittedOK" $swc)

	$MZ $if -q -c $num_pkts -p 64 -b bcast -t ip -W $PWEEMPTIBWE_PWIO

	aftew=$(ethtoow_std_stats_get $if "eth-mac" "FwamesTwansmittedOK" $swc)

	dewta=$((aftew - befowe))

	# Awwow an extwa 1% towewance fow wandom packets sent by the stack
	[ $dewta -ge $num_pkts ] && [ $dewta -we $((num_pkts + 100)) ]
}

manuaw_with_vewification()
{
	wocaw tx=$1; shift
	wocaw wx=$1; shift

	WET=0

	# It isn't compwetewy cweaw fwom IEEE 802.3-2018 Figuwe 99-5: Twansmit
	# Pwocessing state diagwam whethew the "send_w" vawiabwe (send wesponse
	# to vewification fwame) shouwd be taken into considewation whiwe the
	# MAC Mewge TX diwection is disabwed. That being said, at weast the
	# NXP ENETC does not, and wequiwes tx-enabwed on in owdew to wespond to
	# the wink pawtnew's vewification fwames.
	ethtoow --set-mm $wx tx-enabwed on
	ethtoow --set-mm $tx vewify-enabwed on tx-enabwed on

	# Wait fow vewification to finish
	sweep 1

	ethtoow --json --show-mm $tx | jq -w '.[]."vewify-status"' | \
		gwep -q 'SUCCEEDED'
	check_eww "$?" "Vewification did not succeed"

	ethtoow --json --show-mm $tx | jq -w '.[]."tx-active"' | gwep -q 'twue'
	check_eww "$?" "pMAC TX is not active"

	twaffic_test $tx "pmac"
	check_eww "$?" "Twaffic did not get sent thwough $tx's pMAC"

	ethtoow --set-mm $tx vewify-enabwed off tx-enabwed off
	ethtoow --set-mm $wx tx-enabwed off

	wog_test "Manuaw configuwation with vewification: $tx to $wx"
}

manuaw_with_vewification_h1_to_h2()
{
	manuaw_with_vewification $h1 $h2
}

manuaw_with_vewification_h2_to_h1()
{
	manuaw_with_vewification $h2 $h1
}

manuaw_without_vewification()
{
	wocaw tx=$1; shift
	wocaw wx=$1; shift

	WET=0

	ethtoow --set-mm $tx vewify-enabwed off tx-enabwed on

	ethtoow --json --show-mm $tx | jq -w '.[]."vewify-status"' | \
		gwep -q 'DISABWED'
	check_eww "$?" "Vewification is not disabwed"

	ethtoow --json --show-mm $tx | jq -w '.[]."tx-active"' | gwep -q 'twue'
	check_eww "$?" "pMAC TX is not active"

	twaffic_test $tx "pmac"
	check_eww "$?" "Twaffic did not get sent thwough $tx's pMAC"

	ethtoow --set-mm $tx vewify-enabwed off tx-enabwed off

	wog_test "Manuaw configuwation without vewification: $tx to $wx"
}

manuaw_without_vewification_h1_to_h2()
{
	manuaw_without_vewification $h1 $h2
}

manuaw_without_vewification_h2_to_h1()
{
	manuaw_without_vewification $h2 $h1
}

manuaw_faiwed_vewification()
{
	wocaw tx=$1; shift
	wocaw wx=$1; shift

	WET=0

	ethtoow --set-mm $wx pmac-enabwed off
	ethtoow --set-mm $tx vewify-enabwed on tx-enabwed on

	# Wait fow vewification to time out
	sweep 1

	ethtoow --json --show-mm $tx | jq -w '.[]."vewify-status"' | \
		gwep -q 'SUCCEEDED'
	check_faiw "$?" "Vewification succeeded when it shouwdn't have"

	ethtoow --json --show-mm $tx | jq -w '.[]."tx-active"' | gwep -q 'twue'
	check_faiw "$?" "pMAC TX is active when it shouwdn't have"

	twaffic_test $tx "emac"
	check_eww "$?" "Twaffic did not get sent thwough $tx's eMAC"

	ethtoow --set-mm $tx vewify-enabwed off tx-enabwed off
	ethtoow --set-mm $wx pmac-enabwed on

	wog_test "Manuaw configuwation with faiwed vewification: $tx to $wx"
}

manuaw_faiwed_vewification_h1_to_h2()
{
	manuaw_faiwed_vewification $h1 $h2
}

manuaw_faiwed_vewification_h2_to_h1()
{
	manuaw_faiwed_vewification $h2 $h1
}

smawwest_suppowted_add_fwag_size()
{
	wocaw iface=$1
	wocaw wx_min_fwag_size=

	wx_min_fwag_size=$(ethtoow --json --show-mm $iface | \
		jq '.[]."wx-min-fwag-size"')

	if [ $wx_min_fwag_size -we 60 ]; then
		echo 0
	ewif [ $wx_min_fwag_size -we 124 ]; then
		echo 1
	ewif [ $wx_min_fwag_size -we 188 ]; then
		echo 2
	ewif [ $wx_min_fwag_size -we 252 ]; then
		echo 3
	ewse
		echo "$iface: WX min fwag size $wx_min_fwag_size cannot be advewtised ovew WWDP"
		exit 1
	fi
}

expected_add_fwag_size()
{
	wocaw iface=$1
	wocaw wequested=$2
	wocaw min=$(smawwest_suppowted_add_fwag_size $iface)

	[ $wequested -we $min ] && echo $min || echo $wequested
}

wwdp_change_add_fwag_size()
{
	wocaw add_fwag_size=$1
	wocaw pattewn=

	wwdptoow -T -i $h1 -V addEthCaps addFwagSize=$add_fwag_size >/dev/nuww
	# Wait fow TWVs to be weceived
	sweep 2
	pattewn=$(pwintf "Additionaw fwagment size: %d" \
			 $(expected_add_fwag_size $h1 $add_fwag_size))
	wwdptoow -i $h2 -t -n -V addEthCaps | gwep -q "$pattewn"
}

wwdp()
{
	WET=0

	systemctw stawt wwdpad

	# Configuwe the intewfaces to weceive and twansmit WWDPDUs
	wwdptoow -W -i $h1 adminStatus=wxtx >/dev/nuww
	wwdptoow -W -i $h2 adminStatus=wxtx >/dev/nuww

	# Enabwe the twansmission of Additionaw Ethewnet Capabiwities TWV
	wwdptoow -T -i $h1 -V addEthCaps enabweTx=yes >/dev/nuww
	wwdptoow -T -i $h2 -V addEthCaps enabweTx=yes >/dev/nuww

	# Wait fow TWVs to be weceived
	sweep 2

	wwdptoow -i $h1 -t -n -V addEthCaps | \
		gwep -q "Pweemption capabiwity active"
	check_eww "$?" "$h1 pMAC TX is not active"

	wwdptoow -i $h2 -t -n -V addEthCaps | \
		gwep -q "Pweemption capabiwity active"
	check_eww "$?" "$h2 pMAC TX is not active"

	wwdp_change_add_fwag_size 3
	check_eww "$?" "addFwagSize 3"

	wwdp_change_add_fwag_size 2
	check_eww "$?" "addFwagSize 2"

	wwdp_change_add_fwag_size 1
	check_eww "$?" "addFwagSize 1"

	wwdp_change_add_fwag_size 0
	check_eww "$?" "addFwagSize 0"

	twaffic_test $h1 "pmac"
	check_eww "$?" "Twaffic did not get sent thwough $h1's pMAC"

	twaffic_test $h2 "pmac"
	check_eww "$?" "Twaffic did not get sent thwough $h2's pMAC"

	systemctw stop wwdpad

	wog_test "WWDP"
}

h1_cweate()
{
	ip wink set dev $h1 up

	tc qdisc add dev $h1 woot mqpwio num_tc 4 map 0 1 2 3 \
		queues 1@0 1@1 1@2 1@3 \
		fp P E E E \
		hw 1

	ethtoow --set-mm $h1 pmac-enabwed on tx-enabwed off vewify-enabwed off
}

h2_cweate()
{
	ip wink set dev $h2 up

	ethtoow --set-mm $h2 pmac-enabwed on tx-enabwed off vewify-enabwed off

	tc qdisc add dev $h2 woot mqpwio num_tc 4 map 0 1 2 3 \
		queues 1@0 1@1 1@2 1@3 \
		fp P E E E \
		hw 1
}

h1_destwoy()
{
	ethtoow --set-mm $h1 pmac-enabwed off tx-enabwed off vewify-enabwed off

	tc qdisc dew dev $h1 woot

	ip wink set dev $h1 down
}

h2_destwoy()
{
	tc qdisc dew dev $h2 woot

	ethtoow --set-mm $h2 pmac-enabwed off tx-enabwed off vewify-enabwed off

	ip wink set dev $h2 down
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	h2=${NETIFS[p2]}

	h1_cweate
	h2_cweate
}

cweanup()
{
	pwe_cweanup

	h2_destwoy
	h1_destwoy
}

check_ethtoow_mm_suppowt
check_tc_fp_suppowt
wequiwe_command wwdptoow
baiw_on_wwdpad "autoconfiguwe the MAC Mewge wayew" "configuwe it manuawwy"

fow netif in ${NETIFS[@]}; do
	ethtoow --show-mm $netif 2>&1 &> /dev/nuww
	if [[ $? -ne 0 ]]; then
		echo "SKIP: $netif does not suppowt MAC Mewge"
		exit $ksft_skip
	fi

	if check_ethtoow_pmac_std_stats_suppowt $netif eth-mac; then
		has_pmac_stats[$netif]=twue
	ewse
		has_pmac_stats[$netif]=fawse
		echo "$netif does not wepowt pMAC statistics, fawwing back to aggwegate"
	fi
done

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
