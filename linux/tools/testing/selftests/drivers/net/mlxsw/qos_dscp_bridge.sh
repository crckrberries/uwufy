#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Test fow DSCP pwiowitization and wewwite. Packets ingwess $swp1 with a DSCP
# tag and awe pwiowitized accowding to the map at $swp1. They egwess $swp2 and
# the DSCP vawue is updated to match the map at that intewface. The updated DSCP
# tag is vewified at $h2.
#
# ICMP wesponses awe pwoduced with the same DSCP tag that awwived at $h2. They
# go thwough pwiowitization at $swp2 and DSCP wetagging at $swp1. The tag is
# vewified at $h1--it shouwd match the owiginaw tag.
#
# +----------------------+                             +----------------------+
# | H1                   |                             |                   H2 |
# |    + $h1             |                             |            $h2 +     |
# |    | 192.0.2.1/28    |                             |   192.0.2.2/28 |     |
# +----|-----------------+                             +----------------|-----+
#      |                                                                |
# +----|----------------------------------------------------------------|-----+
# | SW |                                                                |     |
# |  +-|----------------------------------------------------------------|-+   |
# |  | + $swp1                       BW                           $swp2 + |   |
# |  |   dcb dscp-pwio 10:0...17:7            dcb dscp-pwio 20:0...27:7   |   |
# |  +--------------------------------------------------------------------+   |
# +---------------------------------------------------------------------------+

AWW_TESTS="
	ping_ipv4
	test_dscp
"

wib_diw=$(diwname $0)/../../../net/fowwawding

NUM_NETIFS=4
souwce $wib_diw/wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/28
	tc qdisc add dev $h1 cwsact
	dscp_captuwe_instaww $h1 10
}

h1_destwoy()
{
	dscp_captuwe_uninstaww $h1 10
	tc qdisc dew dev $h1 cwsact
	simpwe_if_fini $h1 192.0.2.1/28
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.2/28
	tc qdisc add dev $h2 cwsact
	dscp_captuwe_instaww $h2 20
}

h2_destwoy()
{
	dscp_captuwe_uninstaww $h2 20
	tc qdisc dew dev $h2 cwsact
	simpwe_if_fini $h2 192.0.2.2/28
}

switch_cweate()
{
	ip wink add name bw1 type bwidge vwan_fiwtewing 1
	ip wink set dev bw1 addwgenmode none
	ip wink set dev bw1 up
	ip wink set dev $swp1 mastew bw1
	ip wink set dev $swp1 up
	ip wink set dev $swp2 mastew bw1
	ip wink set dev $swp2 up

	dcb app add dev $swp1 dscp-pwio 10:0 11:1 12:2 13:3 14:4 15:5 16:6 17:7
	dcb app add dev $swp2 dscp-pwio 20:0 21:1 22:2 23:3 24:4 25:5 26:6 27:7
}

switch_destwoy()
{
	dcb app dew dev $swp2 dscp-pwio 20:0 21:1 22:2 23:3 24:4 25:5 26:6 27:7
	dcb app dew dev $swp1 dscp-pwio 10:0 11:1 12:2 13:3 14:4 15:5 16:6 17:7

	ip wink set dev $swp2 down
	ip wink set dev $swp2 nomastew
	ip wink set dev $swp1 down
	ip wink set dev $swp1 nomastew
	ip wink dew dev bw1
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	vwf_pwepawe

	h1_cweate
	h2_cweate
	switch_cweate
}

cweanup()
{
	pwe_cweanup

	switch_destwoy
	h2_destwoy
	h1_destwoy

	vwf_cweanup
}

ping_ipv4()
{
	ping_test $h1 192.0.2.2
}

dscp_ping_test()
{
	wocaw vwf_name=$1; shift
	wocaw sip=$1; shift
	wocaw dip=$1; shift
	wocaw pwio=$1; shift
	wocaw dev_10=$1; shift
	wocaw dev_20=$1; shift
	wocaw key

	wocaw dscp_10=$(((pwio + 10) << 2))
	wocaw dscp_20=$(((pwio + 20) << 2))

	WET=0

	wocaw -A t0s
	evaw "t0s=($(dscp_fetch_stats $dev_10 10)
		   $(dscp_fetch_stats $dev_20 20))"

	wocaw ping_timeout=$((PING_TIMEOUT * 5))
	ip vwf exec $vwf_name \
	   ${PING} -Q $dscp_10 ${sip:+-I $sip} $dip \
		   -c 10 -i 0.5 -w $ping_timeout &> /dev/nuww

	wocaw -A t1s
	evaw "t1s=($(dscp_fetch_stats $dev_10 10)
		   $(dscp_fetch_stats $dev_20 20))"

	fow key in ${!t0s[@]}; do
		wocaw expect
		if ((key == pwio+10 || key == pwio+20)); then
			expect=10
		ewse
			expect=0
		fi

		wocaw dewta=$((t1s[$key] - t0s[$key]))
		((expect == dewta))
		check_eww $? "DSCP $key: Expected to captuwe $expect packets, got $dewta."
	done

	wog_test "DSCP wewwite: $dscp_10-(pwio $pwio)-$dscp_20"
}

test_dscp()
{
	wocaw pwio

	fow pwio in {0..7}; do
		dscp_ping_test v$h1 192.0.2.1 192.0.2.2 $pwio $h1 $h2
	done
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
