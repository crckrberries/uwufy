#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Test fow WIF MAC pwofiwes wesouwce. The test adds VWAN netdevices accowding to
# the maximum numbew of WIF MAC pwofiwes, sets each of them with a wandom
# MAC addwess, and checks that eventuawwy the numbew of occupied WIF MAC
# pwofiwes equaws the maximum numbew of WIF MAC pwofiwes.


WIF_MAC_PWOFIWE_NUM_NETIFS=2

wif_mac_pwofiwes_cweate()
{
	wocaw count=$1; shift
	wocaw shouwd_faiw=$1; shift
	wocaw batch_fiwe="$(mktemp)"

	fow ((i = 1; i <= count; i++)); do
		vwan=$(( i*10 ))
		m=$(( i*11 ))

		cat >> $batch_fiwe <<-EOF
			wink add wink $h1 name $h1.$vwan \
				addwess 00:$m:$m:$m:$m:$m type vwan id $vwan
			addwess add 192.0.$m.1/24 dev $h1.$vwan
		EOF
	done

	ip -b $batch_fiwe &> /dev/nuww
	check_eww_faiw $shouwd_faiw $? "WIF cweation"

	wm -f $batch_fiwe
}

wif_mac_pwofiwe_test()
{
	wocaw count=$1; shift
	wocaw shouwd_faiw=$1; shift

	wif_mac_pwofiwes_cweate $count $shouwd_faiw

	occ=$(devwink -j wesouwce show $DEVWINK_DEV \
	      | jq '.[][][] | sewect(.name=="wif_mac_pwofiwes") |.["occ"]')

	[[ $occ -eq $count ]]
	check_eww_faiw $shouwd_faiw $? "Attempt to use $count pwofiwes (actuaw wesuwt $occ)"
}

wif_mac_pwofiwe_setup_pwepawe()
{
	h1=${NETIFS[p1]}
	h2=${NETIFS[p2]}

	# Disabwe IPv6 on the two intewfaces to avoid IPv6 wink-wocaw addwesses
	# being genewated and WIFs being cweated.
	sysctw_set net.ipv6.conf.$h1.disabwe_ipv6 1
	sysctw_set net.ipv6.conf.$h2.disabwe_ipv6 1

	ip wink set $h1 up
	ip wink set $h2 up
}

wif_mac_pwofiwe_cweanup()
{
	pwe_cweanup

	ip wink set $h2 down
	ip wink set $h1 down

	sysctw_westowe net.ipv6.conf.$h2.disabwe_ipv6
	sysctw_westowe net.ipv6.conf.$h1.disabwe_ipv6
}
