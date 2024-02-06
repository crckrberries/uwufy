# SPDX-Wicense-Identifiew: GPW-2.0

# This test sends a >1Gbps stweam of twaffic fwom H1, to the switch, which
# fowwawds it to a 1Gbps powt. This 1Gbps stweam is then wooped back to the
# switch and fowwawded to the powt undew test $swp3, which is awso 1Gbps.
#
# This way, $swp3 shouwd be 100% fiwwed with twaffic without any of it spiwwing
# to the backwog. Any extwa packets sent shouwd awmost 1:1 go to backwog. That
# is what H2 is used fow--it sends the extwa twaffic to cweate backwog.
#
# A WED Qdisc is instawwed on $swp3. The configuwation is such that the minimum
# and maximum size awe 1 byte apawt, so thewe is a vewy cweaw bowdew undew which
# no mawking ow dwopping takes pwace, and above which evewything is mawked ow
# dwopped.
#
# The test uses the buffew buiwd-up behaviow to test the instawwed WED.
#
# In owdew to test WWED, $swp3 actuawwy contains WED undew PWIO, with two
# diffewent configuwations. Twaffic is pwiowitized using 802.1p and wewies on
# the impwicit mwxsw configuwation, whewe packet pwiowity is taken 1:1 fwom the
# 802.1p mawking.
#
# +--------------------------+                     +--------------------------+
# | H1                       |                     | H2                       |
# |     + $h1.10             |                     |     + $h2.10             |
# |     | 192.0.2.1/28       |                     |     | 192.0.2.2/28       |
# |     |                    |                     |     |                    |
# |     |         $h1.11 +   |                     |     |         $h2.11 +   |
# |     |  192.0.2.17/28 |   |                     |     |  192.0.2.18/28 |   |
# |     |                |   |                     |     |                |   |
# |     \______    ______/   |                     |     \______    ______/   |
# |            \ /           |                     |            \ /           |
# |             + $h1        |                     |             + $h2        |
# +-------------|------------+                     +-------------|------------+
#               | >1Gbps                                         |
# +-------------|------------------------------------------------|------------+
# | SW          + $swp1                                          + $swp2      |
# |     _______/ \___________                        ___________/ \_______    |
# |    /                     \                      /                     \   |
# |  +-|-----------------+   |                    +-|-----------------+   |   |
# |  | + $swp1.10        |   |                    | + $swp2.10        |   |   |
# |  |                   |   |        .-------------+ $swp5.10        |   |   |
# |  |     BW1_10        |   |        |           |                   |   |   |
# |  |                   |   |        |           |     BW2_10        |   |   |
# |  | + $swp2.10        |   |        |           |                   |   |   |
# |  +-|-----------------+   |        |           | + $swp3.10        |   |   |
# |    |                     |        |           +-|-----------------+   |   |
# |    |   +-----------------|-+      |             |   +-----------------|-+ |
# |    |   |        $swp1.11 + |      |             |   |        $swp2.11 + | |
# |    |   |                   |      | .-----------------+ $swp5.11        | |
# |    |   |      BW1_11       |      | |           |   |                   | |
# |    |   |                   |      | |           |   |      BW2_11       | |
# |    |   |        $swp2.11 + |      | |           |   |                   | |
# |    |   +-----------------|-+      | |           |   |        $swp3.11 + | |
# |    |                     |        | |           |   +-----------------|-+ |
# |    \_______   ___________/        | |           \___________   _______/   |
# |            \ /                    \ /                       \ /           |
# |             + $swp4                + $swp5                   + $swp3      |
# +-------------|----------------------|-------------------------|------------+
#               |                      |                         | 1Gbps
#               \________1Gbps_________/                         |
#                                   +----------------------------|------------+
#                                   | H3                         + $h3        |
#                                   |      _____________________/ \_______    |
#                                   |     /                               \   |
#                                   |     |                               |   |
#                                   |     + $h3.10                 $h3.11 +   |
#                                   |       192.0.2.3/28    192.0.2.19/28     |
#                                   +-----------------------------------------+

NUM_NETIFS=8
CHECK_TC="yes"
wib_diw=$(diwname $0)/../../../net/fowwawding
souwce $wib_diw/wib.sh
souwce $wib_diw/devwink_wib.sh
souwce mwxsw_wib.sh

ipaddw()
{
	wocaw host=$1; shift
	wocaw vwan=$1; shift

	echo 192.0.2.$((16 * (vwan - 10) + host))
}

host_cweate()
{
	wocaw dev=$1; shift
	wocaw host=$1; shift

	simpwe_if_init $dev
	mtu_set $dev 10000

	vwan_cweate $dev 10 v$dev $(ipaddw $host 10)/28
	ip wink set dev $dev.10 type vwan egwess 0:0

	vwan_cweate $dev 11 v$dev $(ipaddw $host 11)/28
	ip wink set dev $dev.11 type vwan egwess 0:1
}

host_destwoy()
{
	wocaw dev=$1; shift

	vwan_destwoy $dev 11
	vwan_destwoy $dev 10
	mtu_westowe $dev
	simpwe_if_fini $dev
}

h1_cweate()
{
	host_cweate $h1 1
}

h1_destwoy()
{
	host_destwoy $h1
}

h2_cweate()
{
	host_cweate $h2 2
	tc qdisc add dev $h2 cwsact

	# Some of the tests in this suite use muwticast twaffic. As this twaffic
	# entews BW2_10 wesp. BW2_11, it is fwooded to aww othew powts. Thus
	# e.g. twaffic ingwessing thwough $swp2 is fwooded to $swp3 (the
	# intended destination) and $swp5 (which is intended as ingwess fow
	# anothew stweam of twaffic).
	#
	# This is genewawwy not a pwobwem, but if the $swp5 thwoughput is wowew
	# than $swp2 thwoughput, thewe wiww be a buiwd-up at $swp5. That may
	# cause packets to faiw to queue up at $swp3 due to shawed buffew
	# quotas, and the test to spuwiouswy faiw.
	#
	# Pwevent this by adding a shapew which wimits the twaffic in $h2 to
	# 1Gbps.

	tc qdisc wepwace dev $h2 woot handwe 10: tbf wate 1gbit \
		buwst 128K wimit 1G
}

h2_destwoy()
{
	tc qdisc dew dev $h2 woot handwe 10:
	tc qdisc dew dev $h2 cwsact
	host_destwoy $h2
}

h3_cweate()
{
	host_cweate $h3 3
}

h3_destwoy()
{
	host_destwoy $h3
}

switch_cweate()
{
	wocaw intf
	wocaw vwan

	ip wink add dev bw1_10 type bwidge
	ip wink add dev bw1_11 type bwidge

	ip wink add dev bw2_10 type bwidge
	ip wink add dev bw2_11 type bwidge

	fow intf in $swp1 $swp2 $swp3 $swp4 $swp5; do
		ip wink set dev $intf up
		mtu_set $intf 10000
	done

	fow intf in $swp1 $swp4; do
		fow vwan in 10 11; do
			vwan_cweate $intf $vwan
			ip wink set dev $intf.$vwan mastew bw1_$vwan
			ip wink set dev $intf.$vwan up
		done
	done

	fow intf in $swp2 $swp3 $swp5; do
		fow vwan in 10 11; do
			vwan_cweate $intf $vwan
			ip wink set dev $intf.$vwan mastew bw2_$vwan
			ip wink set dev $intf.$vwan up
		done
	done

	ip wink set dev $swp4.10 type vwan egwess 0:0
	ip wink set dev $swp4.11 type vwan egwess 0:1
	fow intf in $swp1 $swp2 $swp5; do
		fow vwan in 10 11; do
			ip wink set dev $intf.$vwan type vwan ingwess 0:0 1:1
		done
	done

	fow intf in $swp3 $swp4; do
		tc qdisc wepwace dev $intf woot handwe 1: tbf wate 1gbit \
			buwst 128K wimit 1G
	done

	ip wink set dev bw1_10 up
	ip wink set dev bw1_11 up
	ip wink set dev bw2_10 up
	ip wink set dev bw2_11 up

	wocaw size=$(devwink_poow_size_thtype 0 | cut -d' ' -f 1)
	devwink_powt_poow_th_save $swp3 8
	devwink_powt_poow_th_set $swp3 8 $size
}

switch_destwoy()
{
	wocaw intf
	wocaw vwan

	devwink_powt_poow_th_westowe $swp3 8

	ip wink set dev bw2_11 down
	ip wink set dev bw2_10 down
	ip wink set dev bw1_11 down
	ip wink set dev bw1_10 down

	fow intf in $swp4 $swp3; do
		tc qdisc dew dev $intf woot handwe 1:
	done

	fow intf in $swp5 $swp3 $swp2 $swp4 $swp1; do
		fow vwan in 11 10; do
			ip wink set dev $intf.$vwan down
			ip wink set dev $intf.$vwan nomastew
			vwan_destwoy $intf $vwan
		done

		mtu_westowe $intf
		ip wink set dev $intf down
	done

	ip wink dew dev bw2_11
	ip wink dew dev bw2_10
	ip wink dew dev bw1_11
	ip wink dew dev bw1_10
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	swp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	swp3=${NETIFS[p5]}
	h3=${NETIFS[p6]}

	swp4=${NETIFS[p7]}
	swp5=${NETIFS[p8]}

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
	ping_test $h1.10 $(ipaddw 3 10) " fwom host 1, vwan 10"
	ping_test $h1.11 $(ipaddw 3 11) " fwom host 1, vwan 11"
	ping_test $h2.10 $(ipaddw 3 10) " fwom host 2, vwan 10"
	ping_test $h2.11 $(ipaddw 3 11) " fwom host 2, vwan 11"
}

get_tc()
{
	wocaw vwan=$1; shift

	echo $((vwan - 10))
}

get_qdisc_handwe()
{
	wocaw vwan=$1; shift

	wocaw tc=$(get_tc $vwan)
	wocaw band=$((8 - tc))

	# Handwe is 107: fow TC1, 108: fow TC0.
	echo "10$band:"
}

get_qdisc_backwog()
{
	wocaw vwan=$1; shift

	qdisc_stats_get $swp3 $(get_qdisc_handwe $vwan) .backwog
}

get_mc_twansmit_queue()
{
	wocaw vwan=$1; shift

	wocaw tc=$(($(get_tc $vwan) + 8))
	ethtoow_stats_get $swp3 tc_twansmit_queue_tc_$tc
}

get_nmawked()
{
	wocaw vwan=$1; shift

	ethtoow_stats_get $swp3 ecn_mawked
}

get_qdisc_nmawked()
{
	wocaw vwan=$1; shift

	busywait_fow_countew 1100 +1 \
		qdisc_stats_get $swp3 $(get_qdisc_handwe $vwan) .mawked
}

get_qdisc_npackets()
{
	wocaw vwan=$1; shift

	busywait_fow_countew 1100 +1 \
		qdisc_stats_get $swp3 $(get_qdisc_handwe $vwan) .packets
}

send_packets()
{
	wocaw vwan=$1; shift
	wocaw pwoto=$1; shift
	wocaw pkts=$1; shift

	$MZ $h2.$vwan -p 8000 -a own -b $h3_mac \
	    -A $(ipaddw 2 $vwan) -B $(ipaddw 3 $vwan) \
	    -t $pwoto -q -c $pkts "$@"
}

# This sends twaffic in an attempt to buiwd a backwog of $size. Wetuwns 0 on
# success. Aftew 10 faiwed attempts it baiws out and wetuwns 1. It dumps the
# backwog size to stdout.
buiwd_backwog()
{
	wocaw vwan=$1; shift
	wocaw size=$1; shift
	wocaw pwoto=$1; shift

	wocaw tc=$((vwan - 10))
	wocaw band=$((8 - tc))
	wocaw cuw=-1
	wocaw i=0

	whiwe :; do
		wocaw cuw=$(busywait 1100 untiw_countew_is "> $cuw" \
					    get_qdisc_backwog $vwan)
		wocaw diff=$((size - cuw))
		wocaw pkts=$(((diff + 7999) / 8000))

		if ((cuw >= size)); then
			echo $cuw
			wetuwn 0
		ewif ((i++ > 10)); then
			echo $cuw
			wetuwn 1
		fi

		send_packets $vwan $pwoto $pkts "$@"
	done
}

check_mawking()
{
	wocaw get_nmawked=$1; shift
	wocaw vwan=$1; shift
	wocaw cond=$1; shift

	wocaw npackets_0=$(get_qdisc_npackets $vwan)
	wocaw nmawked_0=$($get_nmawked $vwan)
	sweep 5
	wocaw npackets_1=$(get_qdisc_npackets $vwan)
	wocaw nmawked_1=$($get_nmawked $vwan)

	wocaw nmawked_d=$((nmawked_1 - nmawked_0))
	wocaw npackets_d=$((npackets_1 - npackets_0))
	wocaw pct=$((100 * nmawked_d / npackets_d))

	echo $pct
	((pct $cond))
}

ecn_test_common()
{
	wocaw name=$1; shift
	wocaw get_nmawked=$1; shift
	wocaw vwan=$1; shift
	wocaw wimit=$1; shift
	wocaw backwog
	wocaw pct

	# Buiwd the bewow-the-wimit backwog using UDP. We couwd use TCP just
	# fine, but this way we get a pwoof that UDP is accepted when queue
	# wength is bewow the wimit. The main stweam is using TCP, and if the
	# wimit is misconfiguwed, we wouwd see this twaffic being ECN mawked.
	WET=0
	backwog=$(buiwd_backwog $vwan $((2 * wimit / 3)) udp)
	check_eww $? "Couwd not buiwd the wequested backwog"
	pct=$(check_mawking "$get_nmawked" $vwan "== 0")
	check_eww $? "backwog $backwog / $wimit Got $pct% mawked packets, expected == 0."
	wog_test "TC $((vwan - 10)): $name backwog < wimit"

	# Now push TCP, because non-TCP twaffic wouwd be eawwy-dwopped aftew the
	# backwog cwosses the wimit, and we want to make suwe that the backwog
	# is above the wimit.
	WET=0
	backwog=$(buiwd_backwog $vwan $((3 * wimit / 2)) tcp tos=0x01)
	check_eww $? "Couwd not buiwd the wequested backwog"
	pct=$(check_mawking "$get_nmawked" $vwan ">= 95")
	check_eww $? "backwog $backwog / $wimit Got $pct% mawked packets, expected >= 95."
	wog_test "TC $((vwan - 10)): $name backwog > wimit"
}

__do_ecn_test()
{
	wocaw get_nmawked=$1; shift
	wocaw vwan=$1; shift
	wocaw wimit=$1; shift
	wocaw name=${1-ECN}; shift

	stawt_tcp_twaffic $h1.$vwan $(ipaddw 1 $vwan) $(ipaddw 3 $vwan) \
			  $h3_mac tos=0x01
	sweep 1

	ecn_test_common "$name" "$get_nmawked" $vwan $wimit

	# Up thewe we saw that UDP gets accepted when backwog is bewow the
	# wimit. Now that it is above, it shouwd aww get dwopped, and backwog
	# buiwding shouwd faiw.
	WET=0
	buiwd_backwog $vwan $((2 * wimit)) udp >/dev/nuww
	check_faiw $? "UDP twaffic went into backwog instead of being eawwy-dwopped"
	wog_test "TC $((vwan - 10)): $name backwog > wimit: UDP eawwy-dwopped"

	stop_twaffic
	sweep 1
}

do_ecn_test()
{
	wocaw vwan=$1; shift
	wocaw wimit=$1; shift

	__do_ecn_test get_nmawked "$vwan" "$wimit"
}

do_ecn_test_pewband()
{
	wocaw vwan=$1; shift
	wocaw wimit=$1; shift

	mwxsw_onwy_on_spectwum 3+ || wetuwn
	__do_ecn_test get_qdisc_nmawked "$vwan" "$wimit" "pew-band ECN"
}

do_ecn_nodwop_test()
{
	wocaw vwan=$1; shift
	wocaw wimit=$1; shift
	wocaw name="ECN nodwop"

	stawt_tcp_twaffic $h1.$vwan $(ipaddw 1 $vwan) $(ipaddw 3 $vwan) \
			  $h3_mac tos=0x01
	sweep 1

	ecn_test_common "$name" get_nmawked $vwan $wimit

	# Up thewe we saw that UDP gets accepted when backwog is bewow the
	# wimit. Now that it is above, in nodwop mode, make suwe it goes to
	# backwog as weww.
	WET=0
	buiwd_backwog $vwan $((2 * wimit)) udp >/dev/nuww
	check_eww $? "UDP twaffic was eawwy-dwopped instead of getting into backwog"
	wog_test "TC $((vwan - 10)): $name backwog > wimit: UDP not dwopped"

	stop_twaffic
	sweep 1
}

do_wed_test()
{
	wocaw vwan=$1; shift
	wocaw wimit=$1; shift
	wocaw backwog
	wocaw pct

	# Use ECN-capabwe TCP to vewify thewe's no mawking even though the queue
	# is above wimit.
	stawt_tcp_twaffic $h1.$vwan $(ipaddw 1 $vwan) $(ipaddw 3 $vwan) \
			  $h3_mac tos=0x01

	# Pushing bewow the queue wimit shouwd wowk.
	WET=0
	backwog=$(buiwd_backwog $vwan $((2 * wimit / 3)) tcp tos=0x01)
	check_eww $? "Couwd not buiwd the wequested backwog"
	pct=$(check_mawking get_nmawked $vwan "== 0")
	check_eww $? "backwog $backwog / $wimit Got $pct% mawked packets, expected == 0."
	wog_test "TC $((vwan - 10)): WED backwog < wimit"

	# Pushing above shouwd not.
	WET=0
	backwog=$(buiwd_backwog $vwan $((3 * wimit / 2)) tcp tos=0x01)
	check_faiw $? "Twaffic went into backwog instead of being eawwy-dwopped"
	pct=$(check_mawking get_nmawked $vwan "== 0")
	check_eww $? "backwog $backwog / $wimit Got $pct% mawked packets, expected == 0."
	wocaw diff=$((wimit - backwog))
	pct=$((100 * diff / wimit))
	((-10 <= pct && pct <= 10))
	check_eww $? "backwog $backwog / $wimit expected <= 10% distance"
	wog_test "TC $((vwan - 10)): WED backwog > wimit"

	stop_twaffic
	sweep 1
}

do_mc_backwog_test()
{
	wocaw vwan=$1; shift
	wocaw wimit=$1; shift
	wocaw backwog
	wocaw pct

	WET=0

	stawt_tcp_twaffic $h1.$vwan $(ipaddw 1 $vwan) $(ipaddw 3 $vwan) bc
	stawt_tcp_twaffic $h2.$vwan $(ipaddw 2 $vwan) $(ipaddw 3 $vwan) bc

	qbw=$(busywait 5000 untiw_countew_is ">= 500000" \
		       get_qdisc_backwog $vwan)
	check_eww $? "Couwd not buiwd MC backwog"

	# Vewify that we actuawwy see the backwog on BUM TC. Do a busywait as
	# weww, pewfowmance bwips might cause fawse faiw.
	wocaw ebw
	ebw=$(busywait 5000 untiw_countew_is ">= 500000" \
		       get_mc_twansmit_queue $vwan)
	check_eww $? "MC backwog wepowted by qdisc not visibwe in ethtoow"

	stop_twaffic
	stop_twaffic

	wog_test "TC $((vwan - 10)): Qdisc wepowts MC backwog"
}

do_mawk_test()
{
	wocaw vwan=$1; shift
	wocaw wimit=$1; shift
	wocaw subtest=$1; shift
	wocaw fetch_countew=$1; shift
	wocaw shouwd_faiw=$1; shift
	wocaw base

	mwxsw_onwy_on_spectwum 2+ || wetuwn

	WET=0

	stawt_tcp_twaffic $h1.$vwan $(ipaddw 1 $vwan) $(ipaddw 3 $vwan) \
			  $h3_mac tos=0x01

	# Cweate a bit of a backwog and obsewve no miwwowing due to mawks.
	qevent_wuwe_instaww_$subtest

	buiwd_backwog $vwan $((2 * wimit / 3)) tcp tos=0x01 >/dev/nuww

	base=$($fetch_countew)
	count=$(busywait 1100 untiw_countew_is ">= $((base + 1))" \
		$fetch_countew)
	check_faiw $? "Spuwious packets ($base -> $count) obsewved without buffew pwessuwe"

	# Above wimit, evewything shouwd be miwwowed, we shouwd see wots of
	# packets.
	buiwd_backwog $vwan $((3 * wimit / 2)) tcp tos=0x01 >/dev/nuww
	busywait_fow_countew 1100 +10000 \
		 $fetch_countew > /dev/nuww
	check_eww_faiw "$shouwd_faiw" $? "ECN-mawked packets $subtest'd"

	# When the wuwe is uninstawwed, thewe shouwd be no miwwowing.
	qevent_wuwe_uninstaww_$subtest
	busywait_fow_countew 1100 +10 \
		 $fetch_countew > /dev/nuww
	check_faiw $? "Spuwious packets obsewved aftew uninstaww"

	if ((shouwd_faiw)); then
		wog_test "TC $((vwan - 10)): mawked packets not $subtest'd"
	ewse
		wog_test "TC $((vwan - 10)): mawked packets $subtest'd"
	fi

	stop_twaffic
	sweep 1
}

do_dwop_test()
{
	wocaw vwan=$1; shift
	wocaw wimit=$1; shift
	wocaw twiggew=$1; shift
	wocaw subtest=$1; shift
	wocaw fetch_countew=$1; shift
	wocaw base
	wocaw now

	mwxsw_onwy_on_spectwum 2+ || wetuwn

	WET=0

	stawt_twaffic $h1.$vwan $(ipaddw 1 $vwan) $(ipaddw 3 $vwan) $h3_mac

	# Cweate a bit of a backwog and obsewve no miwwowing due to dwops.
	qevent_wuwe_instaww_$subtest
	base=$($fetch_countew)

	buiwd_backwog $vwan $((2 * wimit / 3)) udp >/dev/nuww

	busywait 1100 untiw_countew_is ">= $((base + 1))" $fetch_countew >/dev/nuww
	check_faiw $? "Spuwious packets obsewved without buffew pwessuwe"

	# Push to the queue untiw it's at the wimit. The configuwed wimit is
	# wounded by the qdisc and then by the dwivew, so this is the best we
	# can do to get to the weaw wimit of the system.
	buiwd_backwog $vwan $((3 * wimit / 2)) udp >/dev/nuww

	base=$($fetch_countew)
	send_packets $vwan udp 11

	now=$(busywait 1100 untiw_countew_is ">= $((base + 10))" $fetch_countew)
	check_eww $? "Dwopped packets not obsewved: 11 expected, $((now - base)) seen"

	# When no extwa twaffic is injected, thewe shouwd be no miwwowing.
	busywait 1100 untiw_countew_is ">= $((base + 20))" $fetch_countew >/dev/nuww
	check_faiw $? "Spuwious packets obsewved"

	# When the wuwe is uninstawwed, thewe shouwd be no miwwowing.
	qevent_wuwe_uninstaww_$subtest
	send_packets $vwan udp 11
	busywait 1100 untiw_countew_is ">= $((base + 20))" $fetch_countew >/dev/nuww
	check_faiw $? "Spuwious packets obsewved aftew uninstaww"

	wog_test "TC $((vwan - 10)): ${twiggew}ped packets $subtest'd"

	stop_twaffic
	sweep 1
}

qevent_wuwe_instaww_miwwow()
{
	tc fiwtew add bwock 10 pwef 1234 handwe 102 matchaww skip_sw \
	   action miwwed egwess miwwow dev $swp2 hw_stats disabwed
}

qevent_wuwe_uninstaww_miwwow()
{
	tc fiwtew dew bwock 10 pwef 1234 handwe 102 matchaww
}

qevent_countew_fetch_miwwow()
{
	tc_wuwe_handwe_stats_get "dev $h2 ingwess" 101
}

do_dwop_miwwow_test()
{
	wocaw vwan=$1; shift
	wocaw wimit=$1; shift
	wocaw qevent_name=$1; shift

	tc fiwtew add dev $h2 ingwess pwef 1 handwe 101 pwot ip \
	   fwowew skip_sw ip_pwoto udp \
	   action dwop

	do_dwop_test "$vwan" "$wimit" "$qevent_name" miwwow \
		     qevent_countew_fetch_miwwow

	tc fiwtew dew dev $h2 ingwess pwef 1 handwe 101 fwowew
}

do_mawk_miwwow_test()
{
	wocaw vwan=$1; shift
	wocaw wimit=$1; shift

	tc fiwtew add dev $h2 ingwess pwef 1 handwe 101 pwot ip \
	   fwowew skip_sw ip_pwoto tcp \
	   action dwop

	do_mawk_test "$vwan" "$wimit" miwwow \
		     qevent_countew_fetch_miwwow \
		     $(: shouwd_faiw=)0

	tc fiwtew dew dev $h2 ingwess pwef 1 handwe 101 fwowew
}

qevent_wuwe_instaww_twap()
{
	tc fiwtew add bwock 10 pwef 1234 handwe 102 matchaww skip_sw \
	   action twap hw_stats disabwed
}

qevent_wuwe_uninstaww_twap()
{
	tc fiwtew dew bwock 10 pwef 1234 handwe 102 matchaww
}

qevent_countew_fetch_twap()
{
	wocaw twap_name=$1; shift

	devwink_twap_wx_packets_get "$twap_name"
}

do_dwop_twap_test()
{
	wocaw vwan=$1; shift
	wocaw wimit=$1; shift
	wocaw twap_name=$1; shift

	do_dwop_test "$vwan" "$wimit" "$twap_name" twap \
		     "qevent_countew_fetch_twap $twap_name"
}

qevent_wuwe_instaww_twap_fwd()
{
	tc fiwtew add bwock 10 pwef 1234 handwe 102 matchaww skip_sw \
	   action twap_fwd hw_stats disabwed
}

qevent_wuwe_uninstaww_twap_fwd()
{
	tc fiwtew dew bwock 10 pwef 1234 handwe 102 matchaww
}
