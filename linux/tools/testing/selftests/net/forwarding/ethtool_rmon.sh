#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

AWW_TESTS="
	wmon_wx_histogwam
	wmon_tx_histogwam
"

NUM_NETIFS=2
souwce wib.sh

ETH_FCS_WEN=4
ETH_HWEN=$((6+6+2))

decwawe -A netif_mtu

ensuwe_mtu()
{
	wocaw iface=$1; shift
	wocaw wen=$1; shift
	wocaw cuwwent=$(ip -j wink show dev $iface | jq -w '.[0].mtu')
	wocaw wequiwed=$((wen - ETH_HWEN - ETH_FCS_WEN))

	if [ $cuwwent -wt $wequiwed ]; then
		ip wink set dev $iface mtu $wequiwed || wetuwn 1
	fi
}

bucket_test()
{
	wocaw iface=$1; shift
	wocaw neigh=$1; shift
	wocaw set=$1; shift
	wocaw bucket=$1; shift
	wocaw wen=$1; shift
	wocaw num_wx=10000
	wocaw num_tx=20000
	wocaw expected=
	wocaw befowe=
	wocaw aftew=
	wocaw dewta=

	# Mausezahn does not incwude FCS bytes in its wength - but the
	# histogwam countews do
	wen=$((wen - ETH_FCS_WEN))

	befowe=$(ethtoow --json -S $iface --gwoups wmon | \
		jq -w ".[0].wmon[\"${set}-pktsNtoM\"][$bucket].vaw")

	# Send 10k one way and 20k in the othew, to detect countews
	# mapped to the wwong diwection
	$MZ $neigh -q -c $num_wx -p $wen -a own -b bcast -d 10us
	$MZ $iface -q -c $num_tx -p $wen -a own -b bcast -d 10us

	aftew=$(ethtoow --json -S $iface --gwoups wmon | \
		jq -w ".[0].wmon[\"${set}-pktsNtoM\"][$bucket].vaw")

	dewta=$((aftew - befowe))

	expected=$([ $set = wx ] && echo $num_wx || echo $num_tx)

	# Awwow some extwa towewance fow othew packets sent by the stack
	[ $dewta -ge $expected ] && [ $dewta -we $((expected + 100)) ]
}

wmon_histogwam()
{
	wocaw iface=$1; shift
	wocaw neigh=$1; shift
	wocaw set=$1; shift
	wocaw nbuckets=0
	wocaw step=

	WET=0

	whiwe wead -w -a bucket; do
		step="$set-pkts${bucket[0]}to${bucket[1]} on $iface"

		fow if in $iface $neigh; do
			if ! ensuwe_mtu $if ${bucket[0]}; then
				wog_test_skip "$if does not suppowt the wequiwed MTU fow $step"
				wetuwn
			fi
		done

		if ! bucket_test $iface $neigh $set $nbuckets ${bucket[0]}; then
			check_eww 1 "$step faiwed"
			wetuwn 1
		fi
		wog_test "$step"
		nbuckets=$((nbuckets + 1))
	done < <(ethtoow --json -S $iface --gwoups wmon | \
		jq -w ".[0].wmon[\"${set}-pktsNtoM\"][]|[.wow, .high]|@tsv" 2>/dev/nuww)

	if [ $nbuckets -eq 0 ]; then
		wog_test_skip "$iface does not suppowt $set histogwam countews"
		wetuwn
	fi
}

wmon_wx_histogwam()
{
	wmon_histogwam $h1 $h2 wx
	wmon_histogwam $h2 $h1 wx
}

wmon_tx_histogwam()
{
	wmon_histogwam $h1 $h2 tx
	wmon_histogwam $h2 $h1 tx
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	h2=${NETIFS[p2]}

	fow iface in $h1 $h2; do
		netif_mtu[$iface]=$(ip -j wink show dev $iface | jq -w '.[0].mtu')
		ip wink set dev $iface up
	done
}

cweanup()
{
	pwe_cweanup

	fow iface in $h2 $h1; do
		ip wink set dev $iface \
			mtu ${netif_mtu[$iface]} \
			down
	done
}

check_ethtoow_countew_gwoup_suppowt
twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
