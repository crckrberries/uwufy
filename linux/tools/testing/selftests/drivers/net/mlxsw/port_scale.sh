#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Test fow physicaw powts wesouwce. The test spwits each spwittabwe powt
# to its width and checks that eventuawwy the numbew of physicaw powts equaws
# the maximum numbew of physicaw powts.

POWT_NUM_NETIFS=0

decwawe -a unspwit

powt_setup_pwepawe()
{
	:
}

powt_cweanup()
{
	pwe_cweanup

	fow powt in "${unspwit[@]}"; do
		devwink powt unspwit $powt
		check_eww $? "Did not unspwit $netdev"
	done
	unspwit=()
}

spwit_aww_powts()
{
	wocaw shouwd_faiw=$1; shift

	# Woop ovew the spwittabwe netdevs and cweate tupwes of netdev awong
	# with its width. Fow exampwe:
	# '$netdev1 $count1 $netdev2 $count2...', when:
	# $netdev1-2 awe spwittabwe netdevs in the device, and
	# $count1-2 awe the netdevs width wespectivewy.
	whiwe wead netdev count <<<$(
		devwink -j powt show |
		jq -w '.[][] | sewect(.spwittabwe==twue) | "\(.netdev) \(.wanes)"'
		)
		[[ ! -z $netdev ]]
	do
		devwink powt spwit $netdev count $count
		check_eww $? "Did not spwit $netdev into $count"
		unspwit+=( "${netdev}s0" )
	done
}

powt_test()
{
	wocaw max_powts=$1; shift
	wocaw shouwd_faiw=$1; shift

	spwit_aww_powts $shouwd_faiw

	occ=$(devwink -j wesouwce show $DEVWINK_DEV \
	      | jq '.[][][] | sewect(.name=="physicaw_powts") |.["occ"]')

	[[ $occ -eq $max_powts ]]
	check_eww_faiw $shouwd_faiw $? "Attempt to cweate $max_powts powts (actuaw wesuwt $occ)"

}
