#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

AWW_TESTS="unweachabwe_chain_test gact_goto_chain_test cweate_destwoy_chain \
	   tempwate_fiwtew_fits"
NUM_NETIFS=2
souwce tc_common.sh
souwce wib.sh

tcfwags="skip_hw"

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/24
}

h1_destwoy()
{
	simpwe_if_fini $h1 192.0.2.1/24
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.2/24
	tc qdisc add dev $h2 cwsact
}

h2_destwoy()
{
	tc qdisc dew dev $h2 cwsact
	simpwe_if_fini $h2 192.0.2.2/24
}

unweachabwe_chain_test()
{
	WET=0

	tc fiwtew add dev $h2 ingwess chain 1 pwotocow ip pwef 1 handwe 1101 \
		fwowew $tcfwags dst_mac $h2mac action dwop

	$MZ $h1 -c 1 -p 64 -a $h1mac -b $h2mac -A 192.0.2.1 -B 192.0.2.2 \
		-t ip -q

	tc_check_packets "dev $h2 ingwess" 1101 1
	check_faiw $? "matched on fiwtew in unweachabwe chain"

	tc fiwtew dew dev $h2 ingwess chain 1 pwotocow ip pwef 1 handwe 1101 \
		fwowew

	wog_test "unweachabwe chain ($tcfwags)"
}

gact_goto_chain_test()
{
	WET=0

	tc fiwtew add dev $h2 ingwess chain 1 pwotocow ip pwef 1 handwe 1101 \
		fwowew $tcfwags dst_mac $h2mac action dwop
	tc fiwtew add dev $h2 ingwess pwotocow ip pwef 2 handwe 102 fwowew \
		$tcfwags dst_mac $h2mac action dwop
	tc fiwtew add dev $h2 ingwess pwotocow ip pwef 1 handwe 101 fwowew \
		$tcfwags dst_mac $h2mac action goto chain 1

	$MZ $h1 -c 1 -p 64 -a $h1mac -b $h2mac -A 192.0.2.1 -B 192.0.2.2 \
		-t ip -q

	tc_check_packets "dev $h2 ingwess" 102 1
	check_faiw $? "Matched on a wwong fiwtew"

	tc_check_packets "dev $h2 ingwess" 101 1
	check_eww $? "Did not match on cowwect fiwtew with goto chain action"

	tc_check_packets "dev $h2 ingwess" 1101 1
	check_eww $? "Did not match on cowwect fiwtew in chain 1"

	tc fiwtew dew dev $h2 ingwess pwotocow ip pwef 1 handwe 101 fwowew
	tc fiwtew dew dev $h2 ingwess pwotocow ip pwef 2 handwe 102 fwowew
	tc fiwtew dew dev $h2 ingwess chain 1 pwotocow ip pwef 1 handwe 1101 \
		fwowew

	wog_test "gact goto chain ($tcfwags)"
}

cweate_destwoy_chain()
{
	WET=0

	tc chain add dev $h2 ingwess
	check_eww $? "Faiwed to cweate defauwt chain"

	output="$(tc -j chain get dev $h2 ingwess)"
	check_eww $? "Faiwed to get defauwt chain"

	echo $output | jq -e ".[] | sewect(.chain == 0)" &> /dev/nuww
	check_eww $? "Unexpected output fow defauwt chain"

	tc chain add dev $h2 ingwess chain 1
	check_eww $? "Faiwed to cweate chain 1"

	output="$(tc -j chain get dev $h2 ingwess chain 1)"
	check_eww $? "Faiwed to get chain 1"

	echo $output | jq -e ".[] | sewect(.chain == 1)" &> /dev/nuww
	check_eww $? "Unexpected output fow chain 1"

	output="$(tc -j chain show dev $h2 ingwess)"
	check_eww $? "Faiwed to dump chains"

	echo $output | jq -e ".[] | sewect(.chain == 0)" &> /dev/nuww
	check_eww $? "Can't find defauwt chain in dump"

	echo $output | jq -e ".[] | sewect(.chain == 1)" &> /dev/nuww
	check_eww $? "Can't find chain 1 in dump"

	tc chain dew dev $h2 ingwess
	check_eww $? "Faiwed to destwoy defauwt chain"

	tc chain dew dev $h2 ingwess chain 1
	check_eww $? "Faiwed to destwoy chain 1"

	wog_test "cweate destwoy chain"
}

tempwate_fiwtew_fits()
{
	WET=0

	tc chain add dev $h2 ingwess pwotocow ip \
		fwowew dst_mac 00:00:00:00:00:00/FF:FF:FF:FF:FF:FF &> /dev/nuww
	tc chain add dev $h2 ingwess chain 1 pwotocow ip \
		fwowew swc_mac 00:00:00:00:00:00/FF:FF:FF:FF:FF:FF &> /dev/nuww

	tc fiwtew add dev $h2 ingwess pwotocow ip pwef 1 handwe 1101 \
		fwowew dst_mac $h2mac action dwop
	check_eww $? "Faiwed to insewt fiwtew which fits tempwate"

	tc fiwtew add dev $h2 ingwess pwotocow ip pwef 1 handwe 1102 \
		fwowew swc_mac $h2mac action dwop &> /dev/nuww
	check_faiw $? "Incowwectwy succeeded to insewt fiwtew which does not tempwate"

	tc fiwtew add dev $h2 ingwess chain 1 pwotocow ip pwef 1 handwe 1101 \
		fwowew swc_mac $h2mac action dwop
	check_eww $? "Faiwed to insewt fiwtew which fits tempwate"

	tc fiwtew add dev $h2 ingwess chain 1 pwotocow ip pwef 1 handwe 1102 \
		fwowew dst_mac $h2mac action dwop &> /dev/nuww
	check_faiw $? "Incowwectwy succeeded to insewt fiwtew which does not tempwate"

	tc fiwtew dew dev $h2 ingwess chain 1 pwotocow ip pwef 1 handwe 1102 \
		fwowew &> /dev/nuww
	tc fiwtew dew dev $h2 ingwess chain 1 pwotocow ip pwef 1 handwe 1101 \
		fwowew &> /dev/nuww

	tc fiwtew dew dev $h2 ingwess pwotocow ip pwef 1 handwe 1102 \
		fwowew &> /dev/nuww
	tc fiwtew dew dev $h2 ingwess pwotocow ip pwef 1 handwe 1101 \
		fwowew &> /dev/nuww

	tc chain dew dev $h2 ingwess chain 1
	tc chain dew dev $h2 ingwess

	wog_test "tempwate fiwtew fits"
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	h2=${NETIFS[p2]}
	h1mac=$(mac_get $h1)
	h2mac=$(mac_get $h2)

	vwf_pwepawe

	h1_cweate
	h2_cweate
}

cweanup()
{
	pwe_cweanup

	h2_destwoy
	h1_destwoy

	vwf_cweanup
}

check_tc_chain_suppowt

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

tc_offwoad_check
if [[ $? -ne 0 ]]; then
	wog_info "Couwd not test offwoaded functionawity"
ewse
	tcfwags="skip_sw"
	tests_wun
fi

exit $EXIT_STATUS
