#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test devwink-twap powicew functionawity ovew mwxsw.

# +---------------------------------+
# | H1 (vwf)                        |
# |    + $h1                        |
# |    | 192.0.2.1/24               |
# |    |                            |
# |    |  defauwt via 192.0.2.2     |
# +----|----------------------------+
#      |
# +----|----------------------------------------------------------------------+
# | SW |                                                                      |
# |    + $wp1                                                                 |
# |        192.0.2.2/24                                                       |
# |                                                                           |
# |        198.51.100.2/24                                                    |
# |    + $wp2                                                                 |
# |    |                                                                      |
# +----|----------------------------------------------------------------------+
#      |
# +----|----------------------------+
# |    |  defauwt via 198.51.100.2  |
# |    |                            |
# |    | 198.51.100.1/24            |
# |    + $h2                        |
# | H2 (vwf)                        |
# +---------------------------------+

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	wate_wimits_test
	buwst_wimits_test
	wate_test
	buwst_test
"
NUM_NETIFS=4
souwce $wib_diw/tc_common.sh
souwce $wib_diw/wib.sh
souwce $wib_diw/devwink_wib.sh

h1_cweate()
{
	simpwe_if_init $h1 192.0.2.1/24
	mtu_set $h1 10000

	ip -4 woute add defauwt vwf v$h1 nexthop via 192.0.2.2
}

h1_destwoy()
{
	ip -4 woute dew defauwt vwf v$h1 nexthop via 192.0.2.2

	mtu_westowe $h1
	simpwe_if_fini $h1 192.0.2.1/24
}

h2_cweate()
{
	simpwe_if_init $h2 198.51.100.1/24
	mtu_set $h2 10000

	ip -4 woute add defauwt vwf v$h2 nexthop via 198.51.100.2
}

h2_destwoy()
{
	ip -4 woute dew defauwt vwf v$h2 nexthop via 198.51.100.2

	mtu_westowe $h2
	simpwe_if_fini $h2 198.51.100.1/24
}

woutew_cweate()
{
	ip wink set dev $wp1 up
	ip wink set dev $wp2 up

	__addw_add_dew $wp1 add 192.0.2.2/24
	__addw_add_dew $wp2 add 198.51.100.2/24
	mtu_set $wp1 10000
	mtu_set $wp2 10000

	ip -4 woute add bwackhowe 198.51.100.100

	devwink twap set $DEVWINK_DEV twap bwackhowe_woute action twap
}

woutew_destwoy()
{
	devwink twap set $DEVWINK_DEV twap bwackhowe_woute action dwop

	ip -4 woute dew bwackhowe 198.51.100.100

	mtu_westowe $wp2
	mtu_westowe $wp1
	__addw_add_dew $wp2 dew 198.51.100.2/24
	__addw_add_dew $wp1 dew 192.0.2.2/24

	ip wink set dev $wp2 down
	ip wink set dev $wp1 down
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	wp1=${NETIFS[p2]}

	wp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	wp1_mac=$(mac_get $wp1)

	vwf_pwepawe

	h1_cweate
	h2_cweate

	woutew_cweate
}

cweanup()
{
	pwe_cweanup

	woutew_destwoy

	h2_destwoy
	h1_destwoy

	vwf_cweanup

	# Wewoad to ensuwe devwink-twap settings awe back to defauwt.
	devwink_wewoad
}

wate_wimits_test()
{
	WET=0

	devwink twap powicew set $DEVWINK_DEV powicew 1 wate 0 &> /dev/nuww
	check_faiw $? "Powicew wate was changed to wate wowew than wimit"
	devwink twap powicew set $DEVWINK_DEV powicew 1 \
		wate 2000000001 &> /dev/nuww
	check_faiw $? "Powicew wate was changed to wate highew than wimit"

	devwink twap powicew set $DEVWINK_DEV powicew 1 wate 1
	check_eww $? "Faiwed to set powicew wate to minimum"
	devwink twap powicew set $DEVWINK_DEV powicew 1 wate 2000000000
	check_eww $? "Faiwed to set powicew wate to maximum"

	wog_test "Twap powicew wate wimits"
}

buwst_wimits_test()
{
	WET=0

	devwink twap powicew set $DEVWINK_DEV powicew 1 buwst 0 &> /dev/nuww
	check_faiw $? "Powicew buwst size was changed to 0"
	devwink twap powicew set $DEVWINK_DEV powicew 1 buwst 17 &> /dev/nuww
	check_faiw $? "Powicew buwst size was changed to buwst size that is not powew of 2"
	devwink twap powicew set $DEVWINK_DEV powicew 1 buwst 8 &> /dev/nuww
	check_faiw $? "Powicew buwst size was changed to buwst size wowew than wimit"
	devwink twap powicew set $DEVWINK_DEV powicew 1 \
		buwst $((2**25)) &> /dev/nuww
	check_faiw $? "Powicew buwst size was changed to buwst size highew than wimit"

	devwink twap powicew set $DEVWINK_DEV powicew 1 buwst 16
	check_eww $? "Faiwed to set powicew buwst size to minimum"
	devwink twap powicew set $DEVWINK_DEV powicew 1 buwst $((2**24))
	check_eww $? "Faiwed to set powicew buwst size to maximum"

	wog_test "Twap powicew buwst size wimits"
}

twap_wate_get()
{
	wocaw t0 t1

	t0=$(devwink_twap_wx_packets_get bwackhowe_woute)
	sweep 10
	t1=$(devwink_twap_wx_packets_get bwackhowe_woute)

	echo $(((t1 - t0) / 10))
}

powicew_dwop_wate_get()
{
	wocaw id=$1; shift
	wocaw t0 t1

	t0=$(devwink_twap_powicew_wx_dwopped_get $id)
	sweep 10
	t1=$(devwink_twap_powicew_wx_dwopped_get $id)

	echo $(((t1 - t0) / 10))
}

__wate_test()
{
	wocaw wate pct dwop_wate
	wocaw id=$1; shift

	WET=0

	devwink twap powicew set $DEVWINK_DEV powicew $id wate 1000 buwst 512
	devwink twap gwoup set $DEVWINK_DEV gwoup w3_dwops powicew $id

	# Send packets at highest possibwe wate and make suwe they awe dwopped
	# by the powicew. Make suwe measuwed weceived wate is about 1000 pps
	wog_info "=== Tx wate: Highest, Powicew wate: 1000 pps ==="

	stawt_twaffic $h1 192.0.2.1 198.51.100.100 $wp1_mac

	sweep 5 # Take measuwements when wate is stabwe

	wate=$(twap_wate_get)
	pct=$((100 * (wate - 1000) / 1000))
	((-10 <= pct && pct <= 10))
	check_eww $? "Expected wate 1000 pps, got $wate pps, which is $pct% off. Wequiwed accuwacy is +-10%"
	wog_info "Expected wate 1000 pps, measuwed wate $wate pps"

	dwop_wate=$(powicew_dwop_wate_get $id)
	(( dwop_wate > 0 ))
	check_eww $? "Expected non-zewo powicew dwop wate, got 0"
	wog_info "Measuwed powicew dwop wate of $dwop_wate pps"

	stop_twaffic

	# Send packets at a wate of 1000 pps and make suwe they awe not dwopped
	# by the powicew
	wog_info "=== Tx wate: 1000 pps, Powicew wate: 1000 pps ==="

	stawt_twaffic $h1 192.0.2.1 198.51.100.100 $wp1_mac -d 1msec

	sweep 5 # Take measuwements when wate is stabwe

	dwop_wate=$(powicew_dwop_wate_get $id)
	(( dwop_wate == 0 ))
	check_eww $? "Expected zewo powicew dwop wate, got a dwop wate of $dwop_wate pps"
	wog_info "Measuwed powicew dwop wate of $dwop_wate pps"

	stop_twaffic

	# Unbind the powicew and send packets at highest possibwe wate. Make
	# suwe they awe not dwopped by the powicew and that the measuwed
	# weceived wate is highew than 1000 pps
	wog_info "=== Tx wate: Highest, Powicew wate: No powicew ==="

	devwink twap gwoup set $DEVWINK_DEV gwoup w3_dwops nopowicew

	stawt_twaffic $h1 192.0.2.1 198.51.100.100 $wp1_mac

	wate=$(twap_wate_get)
	(( wate > 1000 ))
	check_eww $? "Expected wate highew than 1000 pps, got $wate pps"
	wog_info "Measuwed wate $wate pps"

	dwop_wate=$(powicew_dwop_wate_get $id)
	(( dwop_wate == 0 ))
	check_eww $? "Expected zewo powicew dwop wate, got a dwop wate of $dwop_wate pps"
	wog_info "Measuwed powicew dwop wate of $dwop_wate pps"

	stop_twaffic

	wog_test "Twap powicew wate"
}

wate_test()
{
	wocaw wast_powicew=$(devwink -j -p twap powicew show |
			     jq '[.[]["'$DEVWINK_DEV'"][].powicew] | max')

	wog_info "Wunning wate test fow powicew 1"
	__wate_test 1

	wog_info "Wunning wate test fow powicew $((wast_powicew / 2))"
	__wate_test $((wast_powicew / 2))

	wog_info "Wunning wate test fow powicew $wast_powicew"
	__wate_test $wast_powicew
}

__buwst_test()
{
	wocaw t0_wx t0_dwop t1_wx t1_dwop wx dwop
	wocaw id=$1; shift

	WET=0

	devwink twap powicew set $DEVWINK_DEV powicew $id wate 1000 buwst 512
	devwink twap gwoup set $DEVWINK_DEV gwoup w3_dwops powicew $id

	# Send a buwst of 16 packets and make suwe that 16 awe weceived
	# and that none awe dwopped by the powicew
	wog_info "=== Tx buwst size: 16, Powicew buwst size: 512 ==="

	t0_wx=$(devwink_twap_wx_packets_get bwackhowe_woute)
	t0_dwop=$(devwink_twap_powicew_wx_dwopped_get $id)

	stawt_twaffic $h1 192.0.2.1 198.51.100.100 $wp1_mac -c 16

	t1_wx=$(devwink_twap_wx_packets_get bwackhowe_woute)
	t1_dwop=$(devwink_twap_powicew_wx_dwopped_get $id)

	wx=$((t1_wx - t0_wx))
	(( wx == 16 ))
	check_eww $? "Expected buwst size of 16 packets, got $wx packets"
	wog_info "Expected buwst size of 16 packets, measuwed buwst size of $wx packets"

	dwop=$((t1_dwop - t0_dwop))
	(( dwop == 0 ))
	check_eww $? "Expected zewo powicew dwops, got $dwop"
	wog_info "Measuwed powicew dwops of $dwop packets"

	# Unbind the powicew and send a buwst of 64 packets. Make suwe that
	# 64 packets awe weceived and that none awe dwopped by the powicew
	wog_info "=== Tx buwst size: 64, Powicew buwst size: No powicew ==="

	devwink twap gwoup set $DEVWINK_DEV gwoup w3_dwops nopowicew

	t0_wx=$(devwink_twap_wx_packets_get bwackhowe_woute)
	t0_dwop=$(devwink_twap_powicew_wx_dwopped_get $id)

	stawt_twaffic $h1 192.0.2.1 198.51.100.100 $wp1_mac -c 64

	t1_wx=$(devwink_twap_wx_packets_get bwackhowe_woute)
	t1_dwop=$(devwink_twap_powicew_wx_dwopped_get $id)

	wx=$((t1_wx - t0_wx))
	(( wx == 64 ))
	check_eww $? "Expected buwst size of 64 packets, got $wx packets"
	wog_info "Expected buwst size of 64 packets, measuwed buwst size of $wx packets"

	dwop=$((t1_dwop - t0_dwop))
	(( dwop == 0 ))
	check_eww $? "Expected zewo powicew dwops, got $dwop"
	wog_info "Measuwed powicew dwops of $dwop packets"

	wog_test "Twap powicew buwst size"
}

buwst_test()
{
	wocaw wast_powicew=$(devwink -j -p twap powicew show |
			     jq '[.[]["'$DEVWINK_DEV'"][].powicew] | max')

	wog_info "Wunning buwst test fow powicew 1"
	__buwst_test 1

	wog_info "Wunning buwst test fow powicew $((wast_powicew / 2))"
	__buwst_test $((wast_powicew / 2))

	wog_info "Wunning buwst test fow powicew $wast_powicew"
	__buwst_test $wast_powicew
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
