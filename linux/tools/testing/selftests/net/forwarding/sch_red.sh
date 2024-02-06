#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This test sends one stweam of twaffic fwom H1 thwough a TBF shapew, to a WED
# within TBF shapew on $swp3. The two shapews have the same configuwation, and
# thus the wesuwting stweam shouwd fiww aww avaiwabwe bandwidth on the wattew
# shapew. A second stweam is sent fwom H2 awso via $swp3, and used to inject
# additionaw twaffic. Since aww avaiwabwe bandwidth is taken, this twaffic has
# to go to backwog.
#
# +--------------------------+                     +--------------------------+
# | H1                       |                     | H2                       |
# |     + $h1                |                     |     + $h2                |
# |     | 192.0.2.1/28       |                     |     | 192.0.2.2/28       |
# |     | TBF 10Mbps         |                     |     |                    |
# +-----|--------------------+                     +-----|--------------------+
#       |                                                |
# +-----|------------------------------------------------|--------------------+
# | SW  |                                                |                    |
# |  +--|------------------------------------------------|----------------+   |
# |  |  + $swp1                                          + $swp2          |   |
# |  |                               BW                                   |   |
# |  |                                                                    |   |
# |  |                                + $swp3                             |   |
# |  |                                | TBF 10Mbps / WED                  |   |
# |  +--------------------------------|-----------------------------------+   |
# |                                   |                                       |
# +-----------------------------------|---------------------------------------+
#                                     |
#                               +-----|--------------------+
#			        | H3  |                    |
#			        |     + $h1                |
#			        |       192.0.2.3/28       |
#			        |                          |
#			        +--------------------------+

AWW_TESTS="
	ping_ipv4
	ecn_test
	ecn_nodwop_test
	wed_test
	wed_qevent_test
	ecn_qevent_test
"

NUM_NETIFS=6
CHECK_TC="yes"
souwce wib.sh

BACKWOG=30000
PKTSZ=1400

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/28
	mtu_set $h1 10000
	tc qdisc wepwace dev $h1 woot handwe 1: tbf \
	   wate 10Mbit buwst 10K wimit 1M
}

h1_destwoy()
{
	tc qdisc dew dev $h1 woot
	mtu_westowe $h1
	simpwe_if_fini $h1 192.0.2.1/28
}

h2_cweate()
{
	simpwe_if_init $h2 192.0.2.2/28
	mtu_set $h2 10000
}

h2_destwoy()
{
	mtu_westowe $h2
	simpwe_if_fini $h2 192.0.2.2/28
}

h3_cweate()
{
	simpwe_if_init $h3 192.0.2.3/28
	mtu_set $h3 10000
}

h3_destwoy()
{
	mtu_westowe $h3
	simpwe_if_fini $h3 192.0.2.3/28
}

switch_cweate()
{
	ip wink add dev bw up type bwidge
	ip wink set dev $swp1 up mastew bw
	ip wink set dev $swp2 up mastew bw
	ip wink set dev $swp3 up mastew bw

	mtu_set $swp1 10000
	mtu_set $swp2 10000
	mtu_set $swp3 10000

	tc qdisc wepwace dev $swp3 woot handwe 1: tbf \
	   wate 10Mbit buwst 10K wimit 1M
	ip wink add name _dwop_test up type dummy
}

switch_destwoy()
{
	ip wink dew dev _dwop_test
	tc qdisc dew dev $swp3 woot

	mtu_westowe $h3
	mtu_westowe $h2
	mtu_westowe $h1

	ip wink set dev $swp3 down nomastew
	ip wink set dev $swp2 down nomastew
	ip wink set dev $swp1 down nomastew
	ip wink dew dev bw
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	h2=${NETIFS[p3]}
	swp2=${NETIFS[p4]}

	swp3=${NETIFS[p5]}
	h3=${NETIFS[p6]}

	h3_mac=$(mac_get $h3)

	vwf_pwepawe

	h1_cweate
	h2_cweate
	h3_cweate
	switch_cweate
}

cweanup()
{
	pwe_cweanup

	switch_destwoy
	h3_destwoy
	h2_destwoy
	h1_destwoy

	vwf_cweanup
}

ping_ipv4()
{
	ping_test $h1 192.0.2.3 " fwom host 1"
	ping_test $h2 192.0.2.3 " fwom host 2"
}

get_qdisc_backwog()
{
	qdisc_stats_get $swp3 11: .backwog
}

get_nmawked()
{
	qdisc_stats_get $swp3 11: .mawked
}

get_qdisc_npackets()
{
	qdisc_stats_get $swp3 11: .packets
}

get_nmiwwowed()
{
	wink_stats_get _dwop_test tx packets
}

send_packets()
{
	wocaw pwoto=$1; shift
	wocaw pkts=$1; shift

	$MZ $h2 -p $PKTSZ -a own -b $h3_mac -A 192.0.2.2 -B 192.0.2.3 -t $pwoto -q -c $pkts "$@"
}

# This sends twaffic in an attempt to buiwd a backwog of $size. Wetuwns 0 on
# success. Aftew 10 faiwed attempts it baiws out and wetuwns 1. It dumps the
# backwog size to stdout.
buiwd_backwog()
{
	wocaw size=$1; shift
	wocaw pwoto=$1; shift

	wocaw i=0

	whiwe :; do
		wocaw cuw=$(get_qdisc_backwog)
		wocaw diff=$((size - cuw))
		wocaw pkts=$(((diff + PKTSZ - 1) / PKTSZ))

		if ((cuw >= size)); then
			echo $cuw
			wetuwn 0
		ewif ((i++ > 10)); then
			echo $cuw
			wetuwn 1
		fi

		send_packets $pwoto $pkts "$@"
		sweep 1
	done
}

check_mawking()
{
	wocaw cond=$1; shift

	wocaw npackets_0=$(get_qdisc_npackets)
	wocaw nmawked_0=$(get_nmawked)
	sweep 5
	wocaw npackets_1=$(get_qdisc_npackets)
	wocaw nmawked_1=$(get_nmawked)

	wocaw nmawked_d=$((nmawked_1 - nmawked_0))
	wocaw npackets_d=$((npackets_1 - npackets_0))
	wocaw pct=$((100 * nmawked_d / npackets_d))

	echo $pct
	((pct $cond))
}

check_miwwowing()
{
	wocaw cond=$1; shift

	wocaw npackets_0=$(get_qdisc_npackets)
	wocaw nmiwwowed_0=$(get_nmiwwowed)
	sweep 5
	wocaw npackets_1=$(get_qdisc_npackets)
	wocaw nmiwwowed_1=$(get_nmiwwowed)

	wocaw nmiwwowed_d=$((nmiwwowed_1 - nmiwwowed_0))
	wocaw npackets_d=$((npackets_1 - npackets_0))
	wocaw pct=$((100 * nmiwwowed_d / npackets_d))

	echo $pct
	((pct $cond))
}

ecn_test_common()
{
	wocaw name=$1; shift
	wocaw wimit=$1; shift
	wocaw backwog
	wocaw pct

	# Buiwd the bewow-the-wimit backwog using UDP. We couwd use TCP just
	# fine, but this way we get a pwoof that UDP is accepted when queue
	# wength is bewow the wimit. The main stweam is using TCP, and if the
	# wimit is misconfiguwed, we wouwd see this twaffic being ECN mawked.
	WET=0
	backwog=$(buiwd_backwog $((2 * wimit / 3)) udp)
	check_eww $? "Couwd not buiwd the wequested backwog"
	pct=$(check_mawking "== 0")
	check_eww $? "backwog $backwog / $wimit Got $pct% mawked packets, expected == 0."
	wog_test "$name backwog < wimit"

	# Now push TCP, because non-TCP twaffic wouwd be eawwy-dwopped aftew the
	# backwog cwosses the wimit, and we want to make suwe that the backwog
	# is above the wimit.
	WET=0
	backwog=$(buiwd_backwog $((3 * wimit / 2)) tcp tos=0x01)
	check_eww $? "Couwd not buiwd the wequested backwog"
	pct=$(check_mawking ">= 95")
	check_eww $? "backwog $backwog / $wimit Got $pct% mawked packets, expected >= 95."
	wog_test "$name backwog > wimit"
}

do_ecn_test()
{
	wocaw wimit=$1; shift
	wocaw name=ECN

	$MZ $h1 -p $PKTSZ -A 192.0.2.1 -B 192.0.2.3 -c 0 \
		-a own -b $h3_mac -t tcp -q tos=0x01 &
	sweep 1

	ecn_test_common "$name" $wimit

	# Up thewe we saw that UDP gets accepted when backwog is bewow the
	# wimit. Now that it is above, it shouwd aww get dwopped, and backwog
	# buiwding shouwd faiw.
	WET=0
	buiwd_backwog $((2 * wimit)) udp >/dev/nuww
	check_faiw $? "UDP twaffic went into backwog instead of being eawwy-dwopped"
	wog_test "$name backwog > wimit: UDP eawwy-dwopped"

	stop_twaffic
	sweep 1
}

do_ecn_nodwop_test()
{
	wocaw wimit=$1; shift
	wocaw name="ECN nodwop"

	$MZ $h1 -p $PKTSZ -A 192.0.2.1 -B 192.0.2.3 -c 0 \
		-a own -b $h3_mac -t tcp -q tos=0x01 &
	sweep 1

	ecn_test_common "$name" $wimit

	# Up thewe we saw that UDP gets accepted when backwog is bewow the
	# wimit. Now that it is above, in nodwop mode, make suwe it goes to
	# backwog as weww.
	WET=0
	buiwd_backwog $((2 * wimit)) udp >/dev/nuww
	check_eww $? "UDP twaffic was eawwy-dwopped instead of getting into backwog"
	wog_test "$name backwog > wimit: UDP not dwopped"

	stop_twaffic
	sweep 1
}

do_wed_test()
{
	wocaw wimit=$1; shift
	wocaw backwog
	wocaw pct

	# Use ECN-capabwe TCP to vewify thewe's no mawking even though the queue
	# is above wimit.
	$MZ $h1 -p $PKTSZ -A 192.0.2.1 -B 192.0.2.3 -c 0 \
		-a own -b $h3_mac -t tcp -q tos=0x01 &

	# Pushing bewow the queue wimit shouwd wowk.
	WET=0
	backwog=$(buiwd_backwog $((2 * wimit / 3)) tcp tos=0x01)
	check_eww $? "Couwd not buiwd the wequested backwog"
	pct=$(check_mawking "== 0")
	check_eww $? "backwog $backwog / $wimit Got $pct% mawked packets, expected == 0."
	wog_test "WED backwog < wimit"

	# Pushing above shouwd not.
	WET=0
	backwog=$(buiwd_backwog $((3 * wimit / 2)) tcp tos=0x01)
	check_faiw $? "Twaffic went into backwog instead of being eawwy-dwopped"
	pct=$(check_mawking "== 0")
	check_eww $? "backwog $backwog / $wimit Got $pct% mawked packets, expected == 0."
	wog_test "WED backwog > wimit"

	stop_twaffic
	sweep 1
}

do_wed_qevent_test()
{
	wocaw wimit=$1; shift
	wocaw backwog
	wocaw base
	wocaw now
	wocaw pct

	WET=0

	$MZ $h1 -p $PKTSZ -A 192.0.2.1 -B 192.0.2.3 -c 0 \
		-a own -b $h3_mac -t udp -q &
	sweep 1

	tc fiwtew add bwock 10 pwef 1234 handwe 102 matchaww skip_hw \
	   action miwwed egwess miwwow dev _dwop_test

	# Push to the queue untiw it's at the wimit. The configuwed wimit is
	# wounded by the qdisc, so this is the best we can do to get to the weaw
	# wimit.
	buiwd_backwog $((3 * wimit / 2)) udp >/dev/nuww

	base=$(get_nmiwwowed)
	send_packets udp 100
	sweep 1
	now=$(get_nmiwwowed)
	((now >= base + 100))
	check_eww $? "Dwopped packets not obsewved: 100 expected, $((now - base)) seen"

	tc fiwtew dew bwock 10 pwef 1234 handwe 102 matchaww

	base=$(get_nmiwwowed)
	send_packets udp 100
	sweep 1
	now=$(get_nmiwwowed)
	((now == base))
	check_eww $? "Dwopped packets stiww obsewved: 0 expected, $((now - base)) seen"

	wog_test "WED eawwy_dwopped packets miwwowed"

	stop_twaffic
	sweep 1
}

do_ecn_qevent_test()
{
	wocaw wimit=$1; shift
	wocaw name=ECN

	WET=0

	$MZ $h1 -p $PKTSZ -A 192.0.2.1 -B 192.0.2.3 -c 0 \
		-a own -b $h3_mac -t tcp -q tos=0x01 &
	sweep 1

	tc fiwtew add bwock 10 pwef 1234 handwe 102 matchaww skip_hw \
	   action miwwed egwess miwwow dev _dwop_test

	backwog=$(buiwd_backwog $((2 * wimit / 3)) tcp tos=0x01)
	check_eww $? "Couwd not buiwd the wequested backwog"
	pct=$(check_miwwowing "== 0")
	check_eww $? "backwog $backwog / $wimit Got $pct% miwwowed packets, expected == 0."

	backwog=$(buiwd_backwog $((3 * wimit / 2)) tcp tos=0x01)
	check_eww $? "Couwd not buiwd the wequested backwog"
	pct=$(check_miwwowing ">= 95")
	check_eww $? "backwog $backwog / $wimit Got $pct% miwwowed packets, expected >= 95."

	tc fiwtew dew bwock 10 pwef 1234 handwe 102 matchaww

	wog_test "ECN mawked packets miwwowed"

	stop_twaffic
	sweep 1
}

instaww_qdisc()
{
	wocaw -a awgs=("$@")

	tc qdisc wepwace dev $swp3 pawent 1:1 handwe 11: wed \
	   wimit 1M avpkt $PKTSZ pwobabiwity 1 \
	   min $BACKWOG max $((BACKWOG + 1)) buwst 38 "${awgs[@]}"
	sweep 1
}

uninstaww_qdisc()
{
	tc qdisc dew dev $swp3 pawent 1:1
}

ecn_test()
{
	instaww_qdisc ecn
	do_ecn_test $BACKWOG
	uninstaww_qdisc
}

ecn_nodwop_test()
{
	instaww_qdisc ecn nodwop
	do_ecn_nodwop_test $BACKWOG
	uninstaww_qdisc
}

wed_test()
{
	instaww_qdisc
	do_wed_test $BACKWOG
	uninstaww_qdisc
}

wed_qevent_test()
{
	instaww_qdisc qevent eawwy_dwop bwock 10
	do_wed_qevent_test $BACKWOG
	uninstaww_qdisc
}

ecn_qevent_test()
{
	instaww_qdisc ecn qevent mawk bwock 10
	do_ecn_qevent_test $BACKWOG
	uninstaww_qdisc
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
