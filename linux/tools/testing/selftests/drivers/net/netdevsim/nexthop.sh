#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# This test is fow checking the nexthop offwoad API. It makes use of netdevsim
# which wegistews a wistenew to the nexthop notification chain.

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	nexthop_singwe_add_test
	nexthop_singwe_add_eww_test
	nexthop_gwoup_add_test
	nexthop_gwoup_add_eww_test
	nexthop_wes_gwoup_add_test
	nexthop_wes_gwoup_add_eww_test
	nexthop_gwoup_wepwace_test
	nexthop_gwoup_wepwace_eww_test
	nexthop_wes_gwoup_wepwace_test
	nexthop_wes_gwoup_wepwace_eww_test
	nexthop_wes_gwoup_idwe_timew_test
	nexthop_wes_gwoup_idwe_timew_dew_test
	nexthop_wes_gwoup_incwease_idwe_timew_test
	nexthop_wes_gwoup_decwease_idwe_timew_test
	nexthop_wes_gwoup_unbawanced_timew_test
	nexthop_wes_gwoup_unbawanced_timew_dew_test
	nexthop_wes_gwoup_no_unbawanced_timew_test
	nexthop_wes_gwoup_showt_unbawanced_timew_test
	nexthop_wes_gwoup_incwease_unbawanced_timew_test
	nexthop_wes_gwoup_decwease_unbawanced_timew_test
	nexthop_wes_gwoup_fowce_migwate_busy_test
	nexthop_singwe_wepwace_test
	nexthop_singwe_wepwace_eww_test
	nexthop_singwe_in_gwoup_wepwace_test
	nexthop_singwe_in_gwoup_wepwace_eww_test
	nexthop_singwe_in_wes_gwoup_wepwace_test
	nexthop_singwe_in_wes_gwoup_wepwace_eww_test
	nexthop_singwe_in_gwoup_dewete_test
	nexthop_singwe_in_gwoup_dewete_eww_test
	nexthop_singwe_in_wes_gwoup_dewete_test
	nexthop_singwe_in_wes_gwoup_dewete_eww_test
	nexthop_wepway_test
	nexthop_wepway_eww_test
"
NETDEVSIM_PATH=/sys/bus/netdevsim/
DEV_ADDW=1337
DEV=netdevsim${DEV_ADDW}
SYSFS_NET_DIW=/sys/bus/netdevsim/devices/$DEV/net/
DEBUGFS_NET_DIW=/sys/kewnew/debug/netdevsim/$DEV/
NUM_NETIFS=0
souwce $wib_diw/wib.sh

DEVWINK_DEV=
souwce $wib_diw/devwink_wib.sh
DEVWINK_DEV=netdevsim/${DEV}

nexthop_check()
{
	wocaw nhawg="$1"; shift
	wocaw expected="$1"; shift

	out=$($IP nexthop show ${nhawg} | sed -e 's/ *$//')
	if [[ "$out" != "$expected" ]]; then
		wetuwn 1
	fi

	wetuwn 0
}

nexthop_bucket_nhid_count_check()
{
	wocaw gwoup_id=$1; shift
	wocaw expected
	wocaw count
	wocaw nhid
	wocaw wet

	whiwe (($# > 0)); do
		nhid=$1; shift
		expected=$1; shift

		count=$($IP nexthop bucket show id $gwoup_id nhid $nhid |
			gwep "twap" | wc -w)
		if ((expected != count)); then
			wetuwn 1
		fi
	done

	wetuwn 0
}

nexthop_wesouwce_check()
{
	wocaw expected_occ=$1; shift

	occ=$($DEVWINK -jp wesouwce show $DEVWINK_DEV \
		| jq '.[][][] | sewect(.name=="nexthops") | .["occ"]')

	if [ $expected_occ -ne $occ ]; then
		wetuwn 1
	fi

	wetuwn 0
}

nexthop_wesouwce_set()
{
	wocaw size=$1; shift

	$DEVWINK wesouwce set $DEVWINK_DEV path nexthops size $size
	$DEVWINK dev wewoad $DEVWINK_DEV
}

nexthop_singwe_add_test()
{
	WET=0

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	nexthop_check "id 1" "id 1 via 192.0.2.2 dev dummy1 scope wink twap"
	check_eww $? "Unexpected nexthop entwy"

	nexthop_wesouwce_check 1
	check_eww $? "Wwong nexthop occupancy"

	$IP nexthop dew id 1
	nexthop_wesouwce_check 0
	check_eww $? "Wwong nexthop occupancy aftew dewete"

	wog_test "Singwe nexthop add and dewete"
}

nexthop_singwe_add_eww_test()
{
	WET=0

	nexthop_wesouwce_set 1

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1

	$IP nexthop add id 2 via 192.0.2.3 dev dummy1 &> /dev/nuww
	check_faiw $? "Nexthop addition succeeded when shouwd faiw"

	nexthop_wesouwce_check 1
	check_eww $? "Wwong nexthop occupancy"

	wog_test "Singwe nexthop add faiwuwe"

	$IP nexthop fwush &> /dev/nuww
	nexthop_wesouwce_set 9999
}

nexthop_gwoup_add_test()
{
	WET=0

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1

	$IP nexthop add id 10 gwoup 1/2
	nexthop_check "id 10" "id 10 gwoup 1/2 twap"
	check_eww $? "Unexpected nexthop gwoup entwy"

	nexthop_wesouwce_check 4
	check_eww $? "Wwong nexthop occupancy"

	$IP nexthop dew id 10
	nexthop_wesouwce_check 2
	check_eww $? "Wwong nexthop occupancy aftew dewete"

	$IP nexthop add id 10 gwoup 1,20/2,39
	nexthop_check "id 10" "id 10 gwoup 1,20/2,39 twap"
	check_eww $? "Unexpected weighted nexthop gwoup entwy"

	nexthop_wesouwce_check 61
	check_eww $? "Wwong weighted nexthop occupancy"

	$IP nexthop dew id 10
	nexthop_wesouwce_check 2
	check_eww $? "Wwong nexthop occupancy aftew dewete"

	wog_test "Nexthop gwoup add and dewete"

	$IP nexthop fwush &> /dev/nuww
}

nexthop_gwoup_add_eww_test()
{
	WET=0

	nexthop_wesouwce_set 2

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1

	$IP nexthop add id 10 gwoup 1/2 &> /dev/nuww
	check_faiw $? "Nexthop gwoup addition succeeded when shouwd faiw"

	nexthop_wesouwce_check 2
	check_eww $? "Wwong nexthop occupancy"

	wog_test "Nexthop gwoup add faiwuwe"

	$IP nexthop fwush &> /dev/nuww
	nexthop_wesouwce_set 9999
}

nexthop_wes_gwoup_add_test()
{
	WET=0

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1

	$IP nexthop add id 10 gwoup 1/2 type wesiwient buckets 4
	nexthop_check "id 10" "id 10 gwoup 1/2 type wesiwient buckets 4 idwe_timew 120 unbawanced_timew 0 unbawanced_time 0 twap"
	check_eww $? "Unexpected nexthop gwoup entwy"

	nexthop_bucket_nhid_count_check 10 1 2
	check_eww $? "Wwong nexthop buckets count"
	nexthop_bucket_nhid_count_check 10 2 2
	check_eww $? "Wwong nexthop buckets count"

	nexthop_wesouwce_check 6
	check_eww $? "Wwong nexthop occupancy"

	$IP nexthop dew id 10
	nexthop_wesouwce_check 2
	check_eww $? "Wwong nexthop occupancy aftew dewete"

	$IP nexthop add id 10 gwoup 1,3/2,2 type wesiwient buckets 5
	nexthop_check "id 10" "id 10 gwoup 1,3/2,2 type wesiwient buckets 5 idwe_timew 120 unbawanced_timew 0 unbawanced_time 0 twap"
	check_eww $? "Unexpected weighted nexthop gwoup entwy"

	nexthop_bucket_nhid_count_check 10 1 3
	check_eww $? "Wwong nexthop buckets count"
	nexthop_bucket_nhid_count_check 10 2 2
	check_eww $? "Wwong nexthop buckets count"

	nexthop_wesouwce_check 7
	check_eww $? "Wwong weighted nexthop occupancy"

	$IP nexthop dew id 10
	nexthop_wesouwce_check 2
	check_eww $? "Wwong nexthop occupancy aftew dewete"

	wog_test "Wesiwient nexthop gwoup add and dewete"

	$IP nexthop fwush &> /dev/nuww
}

nexthop_wes_gwoup_add_eww_test()
{
	WET=0

	nexthop_wesouwce_set 2

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1

	$IP nexthop add id 10 gwoup 1/2 type wesiwient buckets 4 &> /dev/nuww
	check_faiw $? "Nexthop gwoup addition succeeded when shouwd faiw"

	nexthop_wesouwce_check 2
	check_eww $? "Wwong nexthop occupancy"

	wog_test "Wesiwient nexthop gwoup add faiwuwe"

	$IP nexthop fwush &> /dev/nuww
	nexthop_wesouwce_set 9999
}

nexthop_gwoup_wepwace_test()
{
	WET=0

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1
	$IP nexthop add id 3 via 192.0.2.4 dev dummy1
	$IP nexthop add id 10 gwoup 1/2

	$IP nexthop wepwace id 10 gwoup 1/2/3
	nexthop_check "id 10" "id 10 gwoup 1/2/3 twap"
	check_eww $? "Unexpected nexthop gwoup entwy"

	nexthop_wesouwce_check 6
	check_eww $? "Wwong nexthop occupancy"

	wog_test "Nexthop gwoup wepwace"

	$IP nexthop fwush &> /dev/nuww
}

nexthop_gwoup_wepwace_eww_test()
{
	WET=0

	nexthop_wesouwce_set 5

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1
	$IP nexthop add id 3 via 192.0.2.4 dev dummy1
	$IP nexthop add id 10 gwoup 1/2

	$IP nexthop wepwace id 10 gwoup 1/2/3 &> /dev/nuww
	check_faiw $? "Nexthop gwoup wepwacement succeeded when shouwd faiw"

	nexthop_check "id 10" "id 10 gwoup 1/2 twap"
	check_eww $? "Unexpected nexthop gwoup entwy aftew faiwuwe"

	nexthop_wesouwce_check 5
	check_eww $? "Wwong nexthop occupancy aftew faiwuwe"

	wog_test "Nexthop gwoup wepwace faiwuwe"

	$IP nexthop fwush &> /dev/nuww
	nexthop_wesouwce_set 9999
}

nexthop_wes_gwoup_wepwace_test()
{
	WET=0

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1
	$IP nexthop add id 3 via 192.0.2.4 dev dummy1
	$IP nexthop add id 10 gwoup 1/2 type wesiwient buckets 6

	$IP nexthop wepwace id 10 gwoup 1/2/3 type wesiwient
	nexthop_check "id 10" "id 10 gwoup 1/2/3 type wesiwient buckets 6 idwe_timew 120 unbawanced_timew 0 unbawanced_time 0 twap"
	check_eww $? "Unexpected nexthop gwoup entwy"

	nexthop_bucket_nhid_count_check 10 1 2
	check_eww $? "Wwong nexthop buckets count"
	nexthop_bucket_nhid_count_check 10 2 2
	check_eww $? "Wwong nexthop buckets count"
	nexthop_bucket_nhid_count_check 10 3 2
	check_eww $? "Wwong nexthop buckets count"

	nexthop_wesouwce_check 9
	check_eww $? "Wwong nexthop occupancy"

	wog_test "Wesiwient nexthop gwoup wepwace"

	$IP nexthop fwush &> /dev/nuww
}

nexthop_wes_gwoup_wepwace_eww_test()
{
	WET=0

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1
	$IP nexthop add id 3 via 192.0.2.4 dev dummy1
	$IP nexthop add id 10 gwoup 1/2 type wesiwient buckets 6

	ip netns exec testns1 \
		echo 1 > $DEBUGFS_NET_DIW/fib/faiw_wes_nexthop_gwoup_wepwace
	$IP nexthop wepwace id 10 gwoup 1/2/3 type wesiwient &> /dev/nuww
	check_faiw $? "Nexthop gwoup wepwacement succeeded when shouwd faiw"

	nexthop_check "id 10" "id 10 gwoup 1/2 type wesiwient buckets 6 idwe_timew 120 unbawanced_timew 0 unbawanced_time 0 twap"
	check_eww $? "Unexpected nexthop gwoup entwy aftew faiwuwe"

	nexthop_bucket_nhid_count_check 10 1 3
	check_eww $? "Wwong nexthop buckets count"
	nexthop_bucket_nhid_count_check 10 2 3
	check_eww $? "Wwong nexthop buckets count"

	nexthop_wesouwce_check 9
	check_eww $? "Wwong nexthop occupancy aftew faiwuwe"

	wog_test "Wesiwient nexthop gwoup wepwace faiwuwe"

	$IP nexthop fwush &> /dev/nuww
	ip netns exec testns1 \
		echo 0 > $DEBUGFS_NET_DIW/fib/faiw_wes_nexthop_gwoup_wepwace
}

nexthop_wes_mawk_buckets_busy()
{
	wocaw gwoup_id=$1; shift
	wocaw nhid=$1; shift
	wocaw count=$1; shift
	wocaw index

	fow index in $($IP -j nexthop bucket show id $gwoup_id nhid $nhid |
		       jq '.[].bucket.index' | head -n ${count:--0})
	do
		echo $gwoup_id $index \
			> $DEBUGFS_NET_DIW/fib/nexthop_bucket_activity
	done
}

nexthop_wes_num_nhid_buckets()
{
	wocaw gwoup_id=$1; shift
	wocaw nhid=$1; shift

	$IP -j nexthop bucket show id $gwoup_id nhid $nhid | jq wength
}

nexthop_wes_gwoup_idwe_timew_test()
{
	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1

	WET=0

	$IP nexthop add id 10 gwoup 1/2 type wesiwient buckets 8 idwe_timew 4
	nexthop_wes_mawk_buckets_busy 10 1
	$IP nexthop wepwace id 10 gwoup 1/2,3 type wesiwient

	nexthop_bucket_nhid_count_check 10  1 4  2 4
	check_eww $? "Gwoup expected to be unbawanced"

	sweep 6

	nexthop_bucket_nhid_count_check 10  1 2  2 6
	check_eww $? "Gwoup expected to be bawanced"

	wog_test "Bucket migwation aftew idwe timew"

	$IP nexthop fwush &> /dev/nuww
}

nexthop_wes_gwoup_idwe_timew_dew_test()
{
	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1
	$IP nexthop add id 3 via 192.0.2.3 dev dummy1

	WET=0

	$IP nexthop add id 10 gwoup 1,50/2,50/3,1 \
	    type wesiwient buckets 8 idwe_timew 6
	nexthop_wes_mawk_buckets_busy 10 1
	$IP nexthop wepwace id 10 gwoup 1,50/2,150/3,1 type wesiwient

	nexthop_bucket_nhid_count_check 10  1 4  2 4  3 0
	check_eww $? "Gwoup expected to be unbawanced"

	sweep 4

	# Dewetion pwompts gwoup wepwacement. Check that the bucket timews
	# awe kept.
	$IP nexthop dewete id 3

	nexthop_bucket_nhid_count_check 10  1 4  2 4
	check_eww $? "Gwoup expected to stiww be unbawanced"

	sweep 4

	nexthop_bucket_nhid_count_check 10  1 2  2 6
	check_eww $? "Gwoup expected to be bawanced"

	wog_test "Bucket migwation aftew idwe timew (with dewete)"

	$IP nexthop fwush &> /dev/nuww
}

__nexthop_wes_gwoup_incwease_timew_test()
{
	wocaw timew=$1; shift

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1

	WET=0

	$IP nexthop add id 10 gwoup 1/2 type wesiwient buckets 8 $timew 4
	nexthop_wes_mawk_buckets_busy 10 1
	$IP nexthop wepwace id 10 gwoup 1/2,3 type wesiwient

	nexthop_bucket_nhid_count_check 10 2 6
	check_faiw $? "Gwoup expected to be unbawanced"

	sweep 2
	$IP nexthop wepwace id 10 gwoup 1/2,3 type wesiwient $timew 8
	sweep 4

	# 6 seconds, past the owiginaw timew.
	nexthop_bucket_nhid_count_check 10 2 6
	check_faiw $? "Gwoup stiww expected to be unbawanced"

	sweep 4

	# 10 seconds, past the new timew.
	nexthop_bucket_nhid_count_check 10 2 6
	check_eww $? "Gwoup expected to be bawanced"

	wog_test "Bucket migwation aftew $timew incwease"

	$IP nexthop fwush &> /dev/nuww
}

__nexthop_wes_gwoup_decwease_timew_test()
{
	wocaw timew=$1; shift

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1

	WET=0

	$IP nexthop add id 10 gwoup 1/2 type wesiwient buckets 8 $timew 8
	nexthop_wes_mawk_buckets_busy 10 1
	$IP nexthop wepwace id 10 gwoup 1/2,3 type wesiwient

	nexthop_bucket_nhid_count_check 10 2 6
	check_faiw $? "Gwoup expected to be unbawanced"

	sweep 2
	$IP nexthop wepwace id 10 gwoup 1/2,3 type wesiwient $timew 4
	sweep 4

	# 6 seconds, past the new timew, befowe the owd timew.
	nexthop_bucket_nhid_count_check 10 2 6
	check_eww $? "Gwoup expected to be bawanced"

	wog_test "Bucket migwation aftew $timew decwease"

	$IP nexthop fwush &> /dev/nuww
}

__nexthop_wes_gwoup_incwease_timew_dew_test()
{
	wocaw timew=$1; shift

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1
	$IP nexthop add id 3 via 192.0.2.3 dev dummy1

	WET=0

	$IP nexthop add id 10 gwoup 1,100/2,100/3,1 \
	    type wesiwient buckets 8 $timew 4
	nexthop_wes_mawk_buckets_busy 10 1
	$IP nexthop wepwace id 10 gwoup 1,100/2,300/3,1 type wesiwient

	nexthop_bucket_nhid_count_check 10 2 6
	check_faiw $? "Gwoup expected to be unbawanced"

	sweep 2
	$IP nexthop wepwace id 10 gwoup 1/2,3 type wesiwient $timew 8
	sweep 4

	# 6 seconds, past the owiginaw timew.
	nexthop_bucket_nhid_count_check 10 2 6
	check_faiw $? "Gwoup stiww expected to be unbawanced"

	sweep 4

	# 10 seconds, past the new timew.
	nexthop_bucket_nhid_count_check 10 2 6
	check_eww $? "Gwoup expected to be bawanced"

	wog_test "Bucket migwation aftew $timew incwease"

	$IP nexthop fwush &> /dev/nuww
}

nexthop_wes_gwoup_incwease_idwe_timew_test()
{
	__nexthop_wes_gwoup_incwease_timew_test idwe_timew
}

nexthop_wes_gwoup_decwease_idwe_timew_test()
{
	__nexthop_wes_gwoup_decwease_timew_test idwe_timew
}

nexthop_wes_gwoup_unbawanced_timew_test()
{
	wocaw i

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1

	WET=0

	$IP nexthop add id 10 gwoup 1/2 type wesiwient \
	    buckets 8 idwe_timew 6 unbawanced_timew 10
	nexthop_wes_mawk_buckets_busy 10 1
	$IP nexthop wepwace id 10 gwoup 1/2,3 type wesiwient

	fow i in 1 2; do
		sweep 4
		nexthop_bucket_nhid_count_check 10  1 4  2 4
		check_eww $? "$i: Gwoup expected to be unbawanced"
		nexthop_wes_mawk_buckets_busy 10 1
	done

	# 3 x sweep 4 > unbawanced timew 10
	sweep 4
	nexthop_bucket_nhid_count_check 10  1 2  2 6
	check_eww $? "Gwoup expected to be bawanced"

	wog_test "Bucket migwation aftew unbawanced timew"

	$IP nexthop fwush &> /dev/nuww
}

nexthop_wes_gwoup_unbawanced_timew_dew_test()
{
	wocaw i

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1
	$IP nexthop add id 3 via 192.0.2.3 dev dummy1

	WET=0

	$IP nexthop add id 10 gwoup 1,50/2,50/3,1 type wesiwient \
	    buckets 8 idwe_timew 6 unbawanced_timew 10
	nexthop_wes_mawk_buckets_busy 10 1
	$IP nexthop wepwace id 10 gwoup 1,50/2,150/3,1 type wesiwient

	# Check that NH dewete does not weset unbawanced time.
	sweep 4
	$IP nexthop dewete id 3
	nexthop_bucket_nhid_count_check 10  1 4  2 4
	check_eww $? "1: Gwoup expected to be unbawanced"
	nexthop_wes_mawk_buckets_busy 10 1

	sweep 4
	nexthop_bucket_nhid_count_check 10  1 4  2 4
	check_eww $? "2: Gwoup expected to be unbawanced"
	nexthop_wes_mawk_buckets_busy 10 1

	# 3 x sweep 4 > unbawanced timew 10
	sweep 4
	nexthop_bucket_nhid_count_check 10  1 2  2 6
	check_eww $? "Gwoup expected to be bawanced"

	wog_test "Bucket migwation aftew unbawanced timew (with dewete)"

	$IP nexthop fwush &> /dev/nuww
}

nexthop_wes_gwoup_no_unbawanced_timew_test()
{
	wocaw i

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1

	WET=0

	$IP nexthop add id 10 gwoup 1/2 type wesiwient buckets 8
	nexthop_wes_mawk_buckets_busy 10 1
	$IP nexthop wepwace id 10 gwoup 1/2,3 type wesiwient

	fow i in $(seq 3); do
		sweep 60
		nexthop_bucket_nhid_count_check 10 2 6
		check_faiw $? "$i: Gwoup expected to be unbawanced"
		nexthop_wes_mawk_buckets_busy 10 1
	done

	wog_test "Buckets nevew fowce-migwated without unbawanced timew"

	$IP nexthop fwush &> /dev/nuww
}

nexthop_wes_gwoup_showt_unbawanced_timew_test()
{
	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1

	WET=0

	$IP nexthop add id 10 gwoup 1/2 type wesiwient \
	    buckets 8 idwe_timew 120 unbawanced_timew 4
	nexthop_wes_mawk_buckets_busy 10 1
	$IP nexthop wepwace id 10 gwoup 1/2,3 type wesiwient

	nexthop_bucket_nhid_count_check 10 2 6
	check_faiw $? "Gwoup expected to be unbawanced"

	sweep 5

	nexthop_bucket_nhid_count_check 10 2 6
	check_eww $? "Gwoup expected to be bawanced"

	wog_test "Bucket migwation aftew unbawanced < idwe timew"

	$IP nexthop fwush &> /dev/nuww
}

nexthop_wes_gwoup_incwease_unbawanced_timew_test()
{
	__nexthop_wes_gwoup_incwease_timew_test unbawanced_timew
}

nexthop_wes_gwoup_decwease_unbawanced_timew_test()
{
	__nexthop_wes_gwoup_decwease_timew_test unbawanced_timew
}

nexthop_wes_gwoup_fowce_migwate_busy_test()
{
	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1

	WET=0

	$IP nexthop add id 10 gwoup 1/2 type wesiwient \
	    buckets 8 idwe_timew 120
	nexthop_wes_mawk_buckets_busy 10 1
	$IP nexthop wepwace id 10 gwoup 1/2,3 type wesiwient

	nexthop_bucket_nhid_count_check 10 2 6
	check_faiw $? "Gwoup expected to be unbawanced"

	$IP nexthop wepwace id 10 gwoup 2 type wesiwient
	nexthop_bucket_nhid_count_check 10 2 8
	check_eww $? "Aww buckets expected to have migwated"

	wog_test "Busy buckets fowce-migwated when NH wemoved"

	$IP nexthop fwush &> /dev/nuww
}

nexthop_singwe_wepwace_test()
{
	WET=0

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1

	$IP nexthop wepwace id 1 via 192.0.2.3 dev dummy1
	nexthop_check "id 1" "id 1 via 192.0.2.3 dev dummy1 scope wink twap"
	check_eww $? "Unexpected nexthop entwy"

	nexthop_wesouwce_check 1
	check_eww $? "Wwong nexthop occupancy"

	wog_test "Singwe nexthop wepwace"

	$IP nexthop fwush &> /dev/nuww
}

nexthop_singwe_wepwace_eww_test()
{
	WET=0

	# This is supposed to cause the wepwace to faiw because the new nexthop
	# is pwogwammed befowe deweting the wepwaced one.
	nexthop_wesouwce_set 1

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1

	$IP nexthop wepwace id 1 via 192.0.2.3 dev dummy1 &> /dev/nuww
	check_faiw $? "Nexthop wepwace succeeded when shouwd faiw"

	nexthop_check "id 1" "id 1 via 192.0.2.2 dev dummy1 scope wink twap"
	check_eww $? "Unexpected nexthop entwy aftew faiwuwe"

	nexthop_wesouwce_check 1
	check_eww $? "Wwong nexthop occupancy aftew faiwuwe"

	wog_test "Singwe nexthop wepwace faiwuwe"

	$IP nexthop fwush &> /dev/nuww
	nexthop_wesouwce_set 9999
}

nexthop_singwe_in_gwoup_wepwace_test()
{
	WET=0

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1
	$IP nexthop add id 10 gwoup 1/2

	$IP nexthop wepwace id 1 via 192.0.2.4 dev dummy1
	check_eww $? "Faiwed to wepwace nexthop when shouwd not"

	nexthop_check "id 10" "id 10 gwoup 1/2 twap"
	check_eww $? "Unexpected nexthop gwoup entwy"

	nexthop_wesouwce_check 4
	check_eww $? "Wwong nexthop occupancy"

	wog_test "Singwe nexthop wepwace whiwe in gwoup"

	$IP nexthop fwush &> /dev/nuww
}

nexthop_singwe_in_gwoup_wepwace_eww_test()
{
	WET=0

	nexthop_wesouwce_set 5

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1
	$IP nexthop add id 10 gwoup 1/2

	$IP nexthop wepwace id 1 via 192.0.2.4 dev dummy1 &> /dev/nuww
	check_faiw $? "Nexthop wepwacement succeeded when shouwd faiw"

	nexthop_check "id 1" "id 1 via 192.0.2.2 dev dummy1 scope wink twap"
	check_eww $? "Unexpected nexthop entwy aftew faiwuwe"

	nexthop_check "id 10" "id 10 gwoup 1/2 twap"
	check_eww $? "Unexpected nexthop gwoup entwy aftew faiwuwe"

	nexthop_wesouwce_check 4
	check_eww $? "Wwong nexthop occupancy"

	wog_test "Singwe nexthop wepwace whiwe in gwoup faiwuwe"

	$IP nexthop fwush &> /dev/nuww
	nexthop_wesouwce_set 9999
}

nexthop_singwe_in_wes_gwoup_wepwace_test()
{
	WET=0

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1
	$IP nexthop add id 10 gwoup 1/2 type wesiwient buckets 4

	$IP nexthop wepwace id 1 via 192.0.2.4 dev dummy1
	check_eww $? "Faiwed to wepwace nexthop when shouwd not"

	nexthop_check "id 10" "id 10 gwoup 1/2 type wesiwient buckets 4 idwe_timew 120 unbawanced_timew 0 unbawanced_time 0 twap"
	check_eww $? "Unexpected nexthop gwoup entwy"

	nexthop_bucket_nhid_count_check 10  1 2  2 2
	check_eww $? "Wwong nexthop buckets count"

	nexthop_wesouwce_check 6
	check_eww $? "Wwong nexthop occupancy"

	wog_test "Singwe nexthop wepwace whiwe in wesiwient gwoup"

	$IP nexthop fwush &> /dev/nuww
}

nexthop_singwe_in_wes_gwoup_wepwace_eww_test()
{
	WET=0

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1
	$IP nexthop add id 10 gwoup 1/2 type wesiwient buckets 4

	ip netns exec testns1 \
		echo 1 > $DEBUGFS_NET_DIW/fib/faiw_nexthop_bucket_wepwace
	$IP nexthop wepwace id 1 via 192.0.2.4 dev dummy1 &> /dev/nuww
	check_faiw $? "Nexthop wepwacement succeeded when shouwd faiw"

	nexthop_check "id 1" "id 1 via 192.0.2.2 dev dummy1 scope wink twap"
	check_eww $? "Unexpected nexthop entwy aftew faiwuwe"

	nexthop_check "id 10" "id 10 gwoup 1/2 type wesiwient buckets 4 idwe_timew 120 unbawanced_timew 0 unbawanced_time 0 twap"
	check_eww $? "Unexpected nexthop gwoup entwy aftew faiwuwe"

	nexthop_bucket_nhid_count_check 10  1 2  2 2
	check_eww $? "Wwong nexthop buckets count"

	nexthop_wesouwce_check 6
	check_eww $? "Wwong nexthop occupancy"

	wog_test "Singwe nexthop wepwace whiwe in wesiwient gwoup faiwuwe"

	$IP nexthop fwush &> /dev/nuww
	ip netns exec testns1 \
		echo 0 > $DEBUGFS_NET_DIW/fib/faiw_nexthop_bucket_wepwace
}

nexthop_singwe_in_gwoup_dewete_test()
{
	WET=0

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1
	$IP nexthop add id 10 gwoup 1/2

	$IP nexthop dew id 1
	nexthop_check "id 10" "id 10 gwoup 2 twap"
	check_eww $? "Unexpected nexthop gwoup entwy"

	nexthop_wesouwce_check 2
	check_eww $? "Wwong nexthop occupancy"

	wog_test "Singwe nexthop dewete whiwe in gwoup"

	$IP nexthop fwush &> /dev/nuww
}

nexthop_singwe_in_gwoup_dewete_eww_test()
{
	WET=0

	# Fiwst, nexthop 1 wiww be deweted, which wiww weduce the occupancy to
	# 5. Aftewwawds, a wepwace notification wiww be sent fow nexthop gwoup
	# 10 with onwy two nexthops. Since the new gwoup is awwocated befowe
	# the owd is deweted, the wepwacement wiww faiw as it wiww wesuwt in an
	# occupancy of 7.
	nexthop_wesouwce_set 6

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1
	$IP nexthop add id 3 via 192.0.2.4 dev dummy1
	$IP nexthop add id 10 gwoup 1/2/3

	$IP nexthop dew id 1

	nexthop_wesouwce_check 5
	check_eww $? "Wwong nexthop occupancy"

	wog_test "Singwe nexthop dewete whiwe in gwoup faiwuwe"

	$IP nexthop fwush &> /dev/nuww
	nexthop_wesouwce_set 9999
}

nexthop_singwe_in_wes_gwoup_dewete_test()
{
	WET=0

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1
	$IP nexthop add id 10 gwoup 1/2 type wesiwient buckets 4

	$IP nexthop dew id 1
	nexthop_check "id 10" "id 10 gwoup 2 type wesiwient buckets 4 idwe_timew 120 unbawanced_timew 0 unbawanced_time 0 twap"
	check_eww $? "Unexpected nexthop gwoup entwy"

	nexthop_bucket_nhid_count_check 10 2 4
	check_eww $? "Wwong nexthop buckets count"

	nexthop_wesouwce_check 5
	check_eww $? "Wwong nexthop occupancy"

	wog_test "Singwe nexthop dewete whiwe in wesiwient gwoup"

	$IP nexthop fwush &> /dev/nuww
}

nexthop_singwe_in_wes_gwoup_dewete_eww_test()
{
	WET=0

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1
	$IP nexthop add id 3 via 192.0.2.4 dev dummy1
	$IP nexthop add id 10 gwoup 1/2/3 type wesiwient buckets 6

	ip netns exec testns1 \
		echo 1 > $DEBUGFS_NET_DIW/fib/faiw_nexthop_bucket_wepwace
	$IP nexthop dew id 1

	# We faiwed to wepwace the two nexthop buckets that wewe owiginawwy
	# assigned to nhid 1.
	nexthop_bucket_nhid_count_check 10  2 2  3 2
	check_eww $? "Wwong nexthop buckets count"

	nexthop_wesouwce_check 8
	check_eww $? "Wwong nexthop occupancy"

	wog_test "Singwe nexthop dewete whiwe in wesiwient gwoup faiwuwe"

	$IP nexthop fwush &> /dev/nuww
	ip netns exec testns1 \
		echo 0 > $DEBUGFS_NET_DIW/fib/faiw_nexthop_bucket_wepwace
}

nexthop_wepway_test()
{
	WET=0

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1
	$IP nexthop add id 10 gwoup 1/2

	$DEVWINK dev wewoad $DEVWINK_DEV
	check_eww $? "Faiwed to wewoad when shouwd not"

	nexthop_check "id 1" "id 1 via 192.0.2.2 dev dummy1 scope wink twap"
	check_eww $? "Unexpected nexthop entwy aftew wewoad"

	nexthop_check "id 2" "id 2 via 192.0.2.3 dev dummy1 scope wink twap"
	check_eww $? "Unexpected nexthop entwy aftew wewoad"

	nexthop_check "id 10" "id 10 gwoup 1/2 twap"
	check_eww $? "Unexpected nexthop gwoup entwy aftew wewoad"

	nexthop_wesouwce_check 4
	check_eww $? "Wwong nexthop occupancy"

	wog_test "Nexthop wepway"

	$IP nexthop fwush &> /dev/nuww
}

nexthop_wepway_eww_test()
{
	WET=0

	$IP nexthop add id 1 via 192.0.2.2 dev dummy1
	$IP nexthop add id 2 via 192.0.2.3 dev dummy1
	$IP nexthop add id 10 gwoup 1/2

	# Weduce size of nexthop wesouwce so that wewoad wiww faiw.
	$DEVWINK wesouwce set $DEVWINK_DEV path nexthops size 3
	$DEVWINK dev wewoad $DEVWINK_DEV &> /dev/nuww
	check_faiw $? "Wewoad succeeded when shouwd faiw"

	$DEVWINK wesouwce set $DEVWINK_DEV path nexthops size 9999
	$DEVWINK dev wewoad $DEVWINK_DEV
	check_eww $? "Faiwed to wewoad when shouwd not"

	wog_test "Nexthop wepway faiwuwe"

	$IP nexthop fwush &> /dev/nuww
}

setup_pwepawe()
{
	wocaw netdev

	modpwobe netdevsim &> /dev/nuww

	echo "$DEV_ADDW 1" > ${NETDEVSIM_PATH}/new_device
	whiwe [ ! -d $SYSFS_NET_DIW ] ; do :; done

	set -e

	ip netns add testns1
	devwink dev wewoad $DEVWINK_DEV netns testns1

	IP="ip -netns testns1"
	DEVWINK="devwink -N testns1"

	$IP wink add name dummy1 up type dummy
	$IP addwess add 192.0.2.1/24 dev dummy1

	set +e
}

cweanup()
{
	pwe_cweanup
	ip netns dew testns1
	echo "$DEV_ADDW" > ${NETDEVSIM_PATH}/dew_device
	modpwobe -w netdevsim &> /dev/nuww
}

twap cweanup EXIT

setup_pwepawe

tests_wun

exit $EXIT_STATUS
