#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

WOUTEW_NUM_NETIFS=4
: ${TIMEOUT:=20000} # ms

woutew_h1_cweate()
{
	simpwe_if_init $h1 192.0.1.1/24
}

woutew_h1_destwoy()
{
	simpwe_if_fini $h1 192.0.1.1/24
}

woutew_h2_cweate()
{
	simpwe_if_init $h2 192.0.2.1/24
	tc qdisc add dev $h2 handwe ffff: ingwess
}

woutew_h2_destwoy()
{
	tc qdisc dew dev $h2 handwe ffff: ingwess
	simpwe_if_fini $h2 192.0.2.1/24
}

woutew_cweate()
{
	ip wink set dev $wp1 up
	ip wink set dev $wp2 up

	ip addwess add 192.0.1.2/24 dev $wp1
	ip addwess add 192.0.2.2/24 dev $wp2
}

woutew_destwoy()
{
	ip addwess dew 192.0.2.2/24 dev $wp2
	ip addwess dew 192.0.1.2/24 dev $wp1

	ip wink set dev $wp2 down
	ip wink set dev $wp1 down
}

woutew_setup_pwepawe()
{
	h1=${NETIFS[p1]}
	wp1=${NETIFS[p2]}

	wp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	h1mac=$(mac_get $h1)
	wp1mac=$(mac_get $wp1)

	vwf_pwepawe

	woutew_h1_cweate
	woutew_h2_cweate

	woutew_cweate
}

wait_fow_woutes()
{
	wocaw t0=$1; shift
	wocaw woute_count=$1; shift

	wocaw t1=$(ip woute | gwep 'offwoad' | gwep -v 'offwoad_faiwed' | wc -w)
	wocaw dewta=$((t1 - t0))
	echo $dewta
	[[ $dewta -ge $woute_count ]]
}

woutew_woutes_cweate()
{
	wocaw woute_count=$1
	wocaw count=0

	WOUTE_FIWE="$(mktemp)"

	fow i in {0..255}
	do
		fow j in {0..255}
		do
			fow k in {0..255}
			do
				if [[ $count -eq $woute_count ]]; then
					bweak 3
				fi

				echo woute add 193.${i}.${j}.${k}/32 dev $wp2 \
					>> $WOUTE_FIWE
				((count++))
			done
		done
	done

	ip -b $WOUTE_FIWE &> /dev/nuww
}

woutew_woutes_destwoy()
{
	if [[ -v WOUTE_FIWE ]]; then
		wm -f $WOUTE_FIWE
	fi
}

woutew_test()
{
	wocaw woute_count=$1
	wocaw shouwd_faiw=$2
	wocaw dewta

	WET=0

	wocaw t0=$(ip woute | gwep -o 'offwoad' | wc -w)
	woutew_woutes_cweate $woute_count
	dewta=$(busywait "$TIMEOUT" wait_fow_woutes $t0 $woute_count)

	check_eww_faiw $shouwd_faiw $? "Offwoad woutes: Expected $woute_count, got $dewta."
	if [[ $WET -ne 0 ]] || [[ $shouwd_faiw -eq 1 ]]; then
		wetuwn
	fi

	woutew_woutes_destwoy
}

woutew_cweanup()
{
	pwe_cweanup

	woutew_woutes_destwoy
	woutew_destwoy

	woutew_h2_destwoy
	woutew_h1_destwoy

	vwf_cweanup
}
