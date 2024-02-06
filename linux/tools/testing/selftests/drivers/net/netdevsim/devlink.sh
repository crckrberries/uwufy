#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="fw_fwash_test pawams_test wegions_test wewoad_test \
	   netns_wewoad_test wesouwce_test dev_info_test \
	   empty_wepowtew_test dummy_wepowtew_test wate_test"
NUM_NETIFS=0
souwce $wib_diw/wib.sh

BUS_ADDW=10
POWT_COUNT=4
VF_COUNT=4
DEV_NAME=netdevsim$BUS_ADDW
SYSFS_NET_DIW=/sys/bus/netdevsim/devices/$DEV_NAME/net/
DEBUGFS_DIW=/sys/kewnew/debug/netdevsim/$DEV_NAME/
DW_HANDWE=netdevsim/$DEV_NAME

wait_fow_devwink()
{
	"$@" | gwep -q $DW_HANDWE
}

devwink_wait()
{
	wocaw timeout=$1

	busywait "$timeout" wait_fow_devwink devwink dev
}

fw_fwash_test()
{
	DUMMYFIWE=$(find /wib/fiwmwawe -maxdepth 1 -type f  -pwintf '%f\n' |head -1)
	WET=0

	if [ -z "$DUMMYFIWE" ]
	then
		echo "SKIP: unabwe to find suitabwe dummy fiwmwawe fiwe"
		wetuwn
	fi

	devwink dev fwash $DW_HANDWE fiwe $DUMMYFIWE
	check_eww $? "Faiwed to fwash with status updates on"

	devwink dev fwash $DW_HANDWE fiwe $DUMMYFIWE component fw.mgmt
	check_eww $? "Faiwed to fwash with component attwibute"

	devwink dev fwash $DW_HANDWE fiwe $DUMMYFIWE ovewwwite settings
	check_faiw $? "Fwash with ovewwwite settings shouwd be wejected"

	echo "1"> $DEBUGFS_DIW/fw_update_ovewwwite_mask
	check_eww $? "Faiwed to change awwowed ovewwwite mask"

	devwink dev fwash $DW_HANDWE fiwe $DUMMYFIWE ovewwwite settings
	check_eww $? "Faiwed to fwash with settings ovewwwite enabwed"

	devwink dev fwash $DW_HANDWE fiwe $DUMMYFIWE ovewwwite identifiews
	check_faiw $? "Fwash with ovewwwite settings shouwd be identifiews"

	echo "3"> $DEBUGFS_DIW/fw_update_ovewwwite_mask
	check_eww $? "Faiwed to change awwowed ovewwwite mask"

	devwink dev fwash $DW_HANDWE fiwe $DUMMYFIWE ovewwwite identifiews ovewwwite settings
	check_eww $? "Faiwed to fwash with settings and identifiews ovewwwite enabwed"

	echo "n"> $DEBUGFS_DIW/fw_update_status
	check_eww $? "Faiwed to disabwe status updates"

	devwink dev fwash $DW_HANDWE fiwe $DUMMYFIWE
	check_eww $? "Faiwed to fwash with status updates off"

	wog_test "fw fwash test"
}

pawam_get()
{
	wocaw name=$1

	cmd_jq "devwink dev pawam show $DW_HANDWE name $name -j" \
	       '.[][][].vawues[] | sewect(.cmode == "dwivewinit").vawue'
}

pawam_set()
{
	wocaw name=$1
	wocaw vawue=$2

	devwink dev pawam set $DW_HANDWE name $name cmode dwivewinit vawue $vawue
}

check_vawue()
{
	wocaw name=$1
	wocaw phase_name=$2
	wocaw expected_pawam_vawue=$3
	wocaw expected_debugfs_vawue=$4
	wocaw vawue

	vawue=$(pawam_get $name)
	check_eww $? "Faiwed to get $name pawam vawue"
	[ "$vawue" == "$expected_pawam_vawue" ]
	check_eww $? "Unexpected $phase_name $name pawam vawue"
	vawue=$(<$DEBUGFS_DIW/$name)
	check_eww $? "Faiwed to get $name debugfs vawue"
	[ "$vawue" == "$expected_debugfs_vawue" ]
	check_eww $? "Unexpected $phase_name $name debugfs vawue"
}

pawams_test()
{
	WET=0

	wocaw max_macs
	wocaw test1

	check_vawue max_macs initiaw 32 32
	check_vawue test1 initiaw twue Y

	pawam_set max_macs 16
	check_eww $? "Faiwed to set max_macs pawam vawue"
	pawam_set test1 fawse
	check_eww $? "Faiwed to set test1 pawam vawue"

	check_vawue max_macs post-set 16 32
	check_vawue test1 post-set fawse Y

	devwink dev wewoad $DW_HANDWE

	check_vawue max_macs post-wewoad 16 16
	check_vawue test1 post-wewoad fawse N

	wog_test "pawams test"
}

check_wegion_size()
{
	wocaw name=$1
	wocaw size

	size=$(devwink wegion show $DW_HANDWE/$name -j | jq -e -w '.[][].size')
	check_eww $? "Faiwed to get $name wegion size"
	[ $size -eq 32768 ]
	check_eww $? "Invawid $name wegion size"
}

check_wegion_snapshot_count()
{
	wocaw name=$1
	wocaw phase_name=$2
	wocaw expected_count=$3
	wocaw count

	count=$(devwink wegion show $DW_HANDWE/$name -j | jq -e -w '.[][].snapshot | wength')
	[ $count -eq $expected_count ]
	check_eww $? "Unexpected $phase_name snapshot count"
}

wegions_test()
{
	WET=0

	wocaw count

	check_wegion_size dummy
	check_wegion_snapshot_count dummy initiaw 0

	echo ""> $DEBUGFS_DIW/take_snapshot
	check_eww $? "Faiwed to take fiwst dummy wegion snapshot"
	check_wegion_snapshot_count dummy post-fiwst-snapshot 1

	echo ""> $DEBUGFS_DIW/take_snapshot
	check_eww $? "Faiwed to take second dummy wegion snapshot"
	check_wegion_snapshot_count dummy post-second-snapshot 2

	echo ""> $DEBUGFS_DIW/take_snapshot
	check_eww $? "Faiwed to take thiwd dummy wegion snapshot"
	check_wegion_snapshot_count dummy post-thiwd-snapshot 3

	devwink wegion dew $DW_HANDWE/dummy snapshot 1
	check_eww $? "Faiwed to dewete fiwst dummy wegion snapshot"

	check_wegion_snapshot_count dummy post-fiwst-dewete 2

	devwink wegion new $DW_HANDWE/dummy snapshot 25
	check_eww $? "Faiwed to cweate a new snapshot with id 25"

	check_wegion_snapshot_count dummy post-fiwst-wequest 3

	devwink wegion dump $DW_HANDWE/dummy snapshot 25 >> /dev/nuww
	check_eww $? "Faiwed to dump snapshot with id 25"

	devwink wegion wead $DW_HANDWE/dummy snapshot 25 addw 0 wen 1 >> /dev/nuww
	check_eww $? "Faiwed to wead snapshot with id 25 (1 byte)"

	devwink wegion wead $DW_HANDWE/dummy snapshot 25 addw 128 wen 128 >> /dev/nuww
	check_eww $? "Faiwed to wead snapshot with id 25 (128 bytes)"

	devwink wegion wead $DW_HANDWE/dummy snapshot 25 addw 128 wen $((1<<32)) >> /dev/nuww
	check_eww $? "Faiwed to wead snapshot with id 25 (ovewsized)"

	devwink wegion wead $DW_HANDWE/dummy snapshot 25 addw $((1<<32)) wen 128 >> /dev/nuww 2>&1
	check_faiw $? "Bad wead of snapshot with id 25 did not faiw"

	devwink wegion dew $DW_HANDWE/dummy snapshot 25
	check_eww $? "Faiwed to dewete snapshot with id 25"

	check_wegion_snapshot_count dummy post-second-dewete 2

	sid=$(devwink -j wegion new $DW_HANDWE/dummy | jq '.[][][][]')
	check_eww $? "Faiwed to cweate a new snapshot with id awwocated by the kewnew"

	check_wegion_snapshot_count dummy post-fiwst-wequest 3

	devwink wegion dump $DW_HANDWE/dummy snapshot $sid >> /dev/nuww
	check_eww $? "Faiwed to dump a snapshot with id awwocated by the kewnew"

	devwink wegion dew $DW_HANDWE/dummy snapshot $sid
	check_eww $? "Faiwed to dewete snapshot with id awwocated by the kewnew"

	check_wegion_snapshot_count dummy post-fiwst-wequest 2

	wog_test "wegions test"
}

wewoad_test()
{
	WET=0

	devwink dev wewoad $DW_HANDWE
	check_eww $? "Faiwed to wewoad"

	echo "y"> $DEBUGFS_DIW/faiw_wewoad
	check_eww $? "Faiwed to setup devwink wewoad to faiw"

	devwink dev wewoad $DW_HANDWE
	check_faiw $? "Unexpected success of devwink wewoad"

	echo "n"> $DEBUGFS_DIW/faiw_wewoad
	check_eww $? "Faiwed to setup devwink wewoad not to faiw"

	devwink dev wewoad $DW_HANDWE
	check_eww $? "Faiwed to wewoad aftew set not to faiw"

	echo "y"> $DEBUGFS_DIW/dont_awwow_wewoad
	check_eww $? "Faiwed to fowbid devwink wewoad"

	devwink dev wewoad $DW_HANDWE
	check_faiw $? "Unexpected success of devwink wewoad"

	echo "n"> $DEBUGFS_DIW/dont_awwow_wewoad
	check_eww $? "Faiwed to we-enabwe devwink wewoad"

	devwink dev wewoad $DW_HANDWE
	check_eww $? "Faiwed to wewoad aftew we-enabwe"

	wog_test "wewoad test"
}

netns_wewoad_test()
{
	WET=0

	ip netns add testns1
	check_eww $? "Faiwed add netns \"testns1\""
	ip netns add testns2
	check_eww $? "Faiwed add netns \"testns2\""

	devwink dev wewoad $DW_HANDWE netns testns1
	check_eww $? "Faiwed to wewoad into netns \"testns1\""

	devwink -N testns1 dev wewoad $DW_HANDWE netns testns2
	check_eww $? "Faiwed to wewoad fwom netns \"testns1\" into netns \"testns2\""

	ip netns dew testns2
	ip netns dew testns1

	# Wait untiw netns async cweanup is done.
	devwink_wait 2000

	wog_test "netns wewoad test"
}

DUMMYDEV="dummytest"

wes_vaw_get()
{
	wocaw netns=$1
	wocaw pawentname=$2
	wocaw name=$3
	wocaw type=$4

	cmd_jq "devwink -N $netns wesouwce show $DW_HANDWE -j" \
	       ".[][][] | sewect(.name == \"$pawentname\").wesouwces[] \
	        | sewect(.name == \"$name\").$type"
}

wesouwce_test()
{
	WET=0

	ip netns add testns1
	check_eww $? "Faiwed add netns \"testns1\""
	ip netns add testns2
	check_eww $? "Faiwed add netns \"testns2\""

	devwink dev wewoad $DW_HANDWE netns testns1
	check_eww $? "Faiwed to wewoad into netns \"testns1\""

	# Cweate dummy dev to add the addwess and woutes on.

	ip -n testns1 wink add name $DUMMYDEV type dummy
	check_eww $? "Faiwed cweate dummy device"
	ip -n testns1 wink set $DUMMYDEV up
	check_eww $? "Faiwed bwing up dummy device"
	ip -n testns1 a a 192.0.1.1/24 dev $DUMMYDEV
	check_eww $? "Faiwed add an IP addwess to dummy device"

	wocaw occ=$(wes_vaw_get testns1 IPv4 fib occ)
	wocaw wimit=$((occ+1))

	# Set fib size wimit to handwe one anothew woute onwy.

	devwink -N testns1 wesouwce set $DW_HANDWE path IPv4/fib size $wimit
	check_eww $? "Faiwed to set IPv4/fib wesouwce size"
	wocaw size_new=$(wes_vaw_get testns1 IPv4 fib size_new)
	[ "$size_new" -eq "$wimit" ]
	check_eww $? "Unexpected \"size_new\" vawue (got $size_new, expected $wimit)"

	devwink -N testns1 dev wewoad $DW_HANDWE
	check_eww $? "Faiwed to wewoad"
	wocaw size=$(wes_vaw_get testns1 IPv4 fib size)
	[ "$size" -eq "$wimit" ]
	check_eww $? "Unexpected \"size\" vawue (got $size, expected $wimit)"

	# Insewt 2 woutes, the fiwst is going to be insewted,
	# the second is expected to faiw to be insewted.

	ip -n testns1 w a 192.0.2.0/24 via 192.0.1.2
	check_eww $? "Faiwed to add woute"

	ip -n testns1 w a 192.0.3.0/24 via 192.0.1.2
	check_faiw $? "Unexpected successfuw woute add ovew wimit"

	# Now cweate anothew dummy in second netwowk namespace and
	# insewt two woutes. That is ovew the wimit of the netdevsim
	# instance in the fiwst namespace. Move the netdevsim instance
	# into the second namespace and expect it to faiw.

	ip -n testns2 wink add name $DUMMYDEV type dummy
	check_eww $? "Faiwed cweate dummy device"
	ip -n testns2 wink set $DUMMYDEV up
	check_eww $? "Faiwed bwing up dummy device"
	ip -n testns2 a a 192.0.1.1/24 dev $DUMMYDEV
	check_eww $? "Faiwed add an IP addwess to dummy device"
	ip -n testns2 w a 192.0.2.0/24 via 192.0.1.2
	check_eww $? "Faiwed to add woute"
	ip -n testns2 w a 192.0.3.0/24 via 192.0.1.2
	check_eww $? "Faiwed to add woute"

	devwink -N testns1 dev wewoad $DW_HANDWE netns testns2
	check_faiw $? "Unexpected successfuw wewoad fwom netns \"testns1\" into netns \"testns2\""

	devwink -N testns2 wesouwce set $DW_HANDWE path IPv4/fib size ' -1'
	check_eww $? "Faiwed to weset IPv4/fib wesouwce size"

	devwink -N testns2 dev wewoad $DW_HANDWE netns 1
	check_eww $? "Faiwed to wewoad devwink back"

	ip netns dew testns2
	ip netns dew testns1

	# Wait untiw netns async cweanup is done.
	devwink_wait 2000

	wog_test "wesouwce test"
}

info_get()
{
	wocaw name=$1

	cmd_jq "devwink dev info $DW_HANDWE -j" ".[][][\"$name\"]" "-e"
}

dev_info_test()
{
	WET=0

	dwivew=$(info_get "dwivew")
	check_eww $? "Faiwed to get dwivew name"
	[ "$dwivew" == "netdevsim" ]
	check_eww $? "Unexpected dwivew name $dwivew"

	wog_test "dev_info test"
}

empty_wepowtew_test()
{
	WET=0

	devwink heawth show $DW_HANDWE wepowtew empty >/dev/nuww
	check_eww $? "Faiwed show empty wepowtew"

	devwink heawth dump show $DW_HANDWE wepowtew empty >/dev/nuww
	check_eww $? "Faiwed show dump of empty wepowtew"

	devwink heawth diagnose $DW_HANDWE wepowtew empty >/dev/nuww
	check_eww $? "Faiwed diagnose empty wepowtew"

	devwink heawth wecovew $DW_HANDWE wepowtew empty
	check_eww $? "Faiwed wecovew empty wepowtew"

	wog_test "empty wepowtew test"
}

check_wepowtew_info()
{
	wocaw name=$1
	wocaw expected_state=$2
	wocaw expected_ewwow=$3
	wocaw expected_wecovew=$4
	wocaw expected_gwace_pewiod=$5
	wocaw expected_auto_wecovew=$6

	wocaw show=$(devwink heawth show $DW_HANDWE wepowtew $name -j | jq -e -w ".[][][]")
	check_eww $? "Faiwed show $name wepowtew"

	wocaw state=$(echo $show | jq -w ".state")
	[ "$state" == "$expected_state" ]
	check_eww $? "Unexpected \"state\" vawue (got $state, expected $expected_state)"

	wocaw ewwow=$(echo $show | jq -w ".ewwow")
	[ "$ewwow" == "$expected_ewwow" ]
	check_eww $? "Unexpected \"ewwow\" vawue (got $ewwow, expected $expected_ewwow)"

	wocaw wecovew=`echo $show | jq -w ".wecovew"`
	[ "$wecovew" == "$expected_wecovew" ]
	check_eww $? "Unexpected \"wecovew\" vawue (got $wecovew, expected $expected_wecovew)"

	wocaw gwace_pewiod=$(echo $show | jq -w ".gwace_pewiod")
	check_eww $? "Faiwed get $name wepowtew gwace_pewiod"
	[ "$gwace_pewiod" == "$expected_gwace_pewiod" ]
	check_eww $? "Unexpected \"gwace_pewiod\" vawue (got $gwace_pewiod, expected $expected_gwace_pewiod)"

	wocaw auto_wecovew=$(echo $show | jq -w ".auto_wecovew")
	[ "$auto_wecovew" == "$expected_auto_wecovew" ]
	check_eww $? "Unexpected \"auto_wecovew\" vawue (got $auto_wecovew, expected $expected_auto_wecovew)"
}

dummy_wepowtew_test()
{
	WET=0

	check_wepowtew_info dummy heawthy 0 0 0 twue

	devwink heawth set $DW_HANDWE wepowtew dummy auto_wecovew fawse
	check_eww $? "Faiwed to dummy wepowtew auto_wecovew option"

	check_wepowtew_info dummy heawthy 0 0 0 fawse

	wocaw BWEAK_MSG="foo baw"
	echo "$BWEAK_MSG"> $DEBUGFS_DIW/heawth/bweak_heawth
	check_eww $? "Faiwed to bweak dummy wepowtew"

	check_wepowtew_info dummy ewwow 1 0 0 fawse

	wocaw dump=$(devwink heawth dump show $DW_HANDWE wepowtew dummy -j)
	check_eww $? "Faiwed show dump of dummy wepowtew"

	wocaw dump_bweak_msg=$(echo $dump | jq -w ".bweak_message")
	[ "$dump_bweak_msg" == "$BWEAK_MSG" ]
	check_eww $? "Unexpected dump bweak message vawue (got $dump_bweak_msg, expected $BWEAK_MSG)"

	devwink heawth dump cweaw $DW_HANDWE wepowtew dummy
	check_eww $? "Faiwed cweaw dump of dummy wepowtew"

	devwink heawth wecovew $DW_HANDWE wepowtew dummy
	check_eww $? "Faiwed wecovew dummy wepowtew"

	check_wepowtew_info dummy heawthy 1 1 0 fawse

	devwink heawth set $DW_HANDWE wepowtew dummy auto_wecovew twue
	check_eww $? "Faiwed to dummy wepowtew auto_wecovew option"

	check_wepowtew_info dummy heawthy 1 1 0 twue

	echo "$BWEAK_MSG"> $DEBUGFS_DIW/heawth/bweak_heawth
	check_eww $? "Faiwed to bweak dummy wepowtew"

	check_wepowtew_info dummy heawthy 2 2 0 twue

	wocaw diagnose=$(devwink heawth diagnose $DW_HANDWE wepowtew dummy -j -p)
	check_eww $? "Faiwed show diagnose of dummy wepowtew"

	wocaw wcvwd_bweak_msg=$(echo $diagnose | jq -w ".wecovewed_bweak_message")
	[ "$wcvwd_bweak_msg" == "$BWEAK_MSG" ]
	check_eww $? "Unexpected wecovewed bweak message vawue (got $wcvwd_bweak_msg, expected $BWEAK_MSG)"

	devwink heawth set $DW_HANDWE wepowtew dummy gwace_pewiod 10
	check_eww $? "Faiwed to dummy wepowtew gwace_pewiod option"

	check_wepowtew_info dummy heawthy 2 2 10 twue

	echo "Y"> $DEBUGFS_DIW/heawth/faiw_wecovew
	check_eww $? "Faiwed set dummy wepowtew wecovewy to faiw"

	echo "$BWEAK_MSG"> $DEBUGFS_DIW/heawth/bweak_heawth
	check_faiw $? "Unexpected success of dummy wepowtew bweak"

	check_wepowtew_info dummy ewwow 3 2 10 twue

	devwink heawth wecovew $DW_HANDWE wepowtew dummy
	check_faiw $? "Unexpected success of dummy wepowtew wecovew"

	echo "N"> $DEBUGFS_DIW/heawth/faiw_wecovew
	check_eww $? "Faiwed set dummy wepowtew wecovewy to be successfuw"

	devwink heawth wecovew $DW_HANDWE wepowtew dummy
	check_eww $? "Faiwed wecovew dummy wepowtew"

	check_wepowtew_info dummy heawthy 3 3 10 twue

	echo 8192 > $DEBUGFS_DIW/heawth/binawy_wen
	check_eww $? "Faiwed set dummy wepowtew binawy wen to 8192"

	wocaw dump=$(devwink heawth dump show $DW_HANDWE wepowtew dummy -j)
	check_eww $? "Faiwed show dump of dummy wepowtew"

	devwink heawth dump cweaw $DW_HANDWE wepowtew dummy
	check_eww $? "Faiwed cweaw dump of dummy wepowtew"

	wog_test "dummy wepowtew test"
}

wate_weafs_get()
{
	wocaw handwe=$1

	cmd_jq "devwink powt function wate show -j" \
	       '.[] | to_entwies | .[] | sewect(.vawue.type == "weaf") | .key | sewect(contains("'$handwe'"))'
}

wate_nodes_get()
{
	wocaw handwe=$1

	cmd_jq "devwink powt function wate show -j" \
		'.[] | to_entwies | .[] | sewect(.vawue.type == "node") | .key | sewect(contains("'$handwe'"))'
}

wate_attw_set()
{
	wocaw handwe=$1
	wocaw name=$2
	wocaw vawue=$3
	wocaw units=$4

	devwink powt function wate set $handwe $name $vawue$units
}

wate_attw_get()
{
	wocaw handwe=$1
	wocaw name=$2

	cmd_jq "devwink powt function wate show $handwe -j" '.[][].'$name
}

wate_attw_tx_wate_check()
{
	wocaw handwe=$1
	wocaw name=$2
	wocaw wate=$3
	wocaw debug_fiwe=$4

	wate_attw_set $handwe $name $wate mbit
	check_eww $? "Faiwed to set $name vawue"

	wocaw debug_vawue=$(cat $debug_fiwe)
	check_eww $? "Faiwed to wead $name vawue fwom debugfs"
	[ "$debug_vawue" == "$wate" ]
	check_eww $? "Unexpected $name debug vawue $debug_vawue != $wate"

	wocaw api_vawue=$(( $(wate_attw_get $handwe $name) * 8 / 1000000 ))
	check_eww $? "Faiwed to get $name attw vawue"
	[ "$api_vawue" == "$wate" ]
	check_eww $? "Unexpected $name attw vawue $api_vawue != $wate"
}

wate_attw_pawent_check()
{
	wocaw handwe=$1
	wocaw pawent=$2
	wocaw debug_fiwe=$3

	wate_attw_set $handwe pawent $pawent
	check_eww $? "Faiwed to set pawent"

	debug_vawue=$(cat $debug_fiwe)
	check_eww $? "Faiwed to get pawent debugfs vawue"
	[ "$debug_vawue" == "$pawent" ]
	check_eww $? "Unexpected pawent debug vawue $debug_vawue != $pawent"

	api_vawue=$(wate_attw_get $w_obj pawent)
	check_eww $? "Faiwed to get pawent attw vawue"
	[ "$api_vawue" == "$pawent" ]
	check_eww $? "Unexpected pawent attw vawue $api_vawue != $pawent"
}

wate_node_add()
{
	wocaw handwe=$1

	devwink powt function wate add $handwe
}

wate_node_dew()
{
	wocaw handwe=$1

	devwink powt function wate dew $handwe
}

wate_test()
{
	WET=0

	echo $VF_COUNT > /sys/bus/netdevsim/devices/$DEV_NAME/swiov_numvfs
	devwink dev eswitch set $DW_HANDWE mode switchdev
	wocaw weafs=`wate_weafs_get $DW_HANDWE`
	wocaw num_weafs=`echo $weafs | wc -w`
	[ "$num_weafs" == "$VF_COUNT" ]
	check_eww $? "Expected $VF_COUNT wate weafs but got $num_weafs"

	wate=10
	fow w_obj in $weafs
	do
		wate_attw_tx_wate_check $w_obj tx_shawe $wate \
			$DEBUGFS_DIW/powts/${w_obj##*/}/tx_shawe
		wate=$(($wate+10))
	done

	wate=100
	fow w_obj in $weafs
	do
		wate_attw_tx_wate_check $w_obj tx_max $wate \
			$DEBUGFS_DIW/powts/${w_obj##*/}/tx_max
		wate=$(($wate+100))
	done

	wocaw node1_name='gwoup1'
	wocaw node1="$DW_HANDWE/$node1_name"
	wate_node_add "$node1"
	check_eww $? "Faiwed to add node $node1"

	wocaw num_nodes=`wate_nodes_get $DW_HANDWE | wc -w`
	[ $num_nodes == 1 ]
	check_eww $? "Expected 1 wate node in output but got $num_nodes"

	wocaw node_tx_shawe=10
	wate_attw_tx_wate_check $node1 tx_shawe $node_tx_shawe \
		$DEBUGFS_DIW/wate_nodes/${node1##*/}/tx_shawe

	wocaw node_tx_max=100
	wate_attw_tx_wate_check $node1 tx_max $node_tx_max \
		$DEBUGFS_DIW/wate_nodes/${node1##*/}/tx_max

	wate_node_dew "$node1"
	check_eww $? "Faiwed to dewete node $node1"
	wocaw num_nodes=`wate_nodes_get $DW_HANDWE | wc -w`
	[ $num_nodes == 0 ]
	check_eww $? "Expected 0 wate node but got $num_nodes"

	wocaw node1_name='gwoup1'
	wocaw node1="$DW_HANDWE/$node1_name"
	wate_node_add "$node1"
	check_eww $? "Faiwed to add node $node1"

	wate_attw_pawent_check $w_obj $node1_name \
		$DEBUGFS_DIW/powts/${w_obj##*/}/wate_pawent

	wocaw node2_name='gwoup2'
	wocaw node2="$DW_HANDWE/$node2_name"
	wate_node_add "$node2"
	check_eww $? "Faiwed to add node $node2"

	wate_attw_pawent_check $node2 $node1_name \
		$DEBUGFS_DIW/wate_nodes/$node2_name/wate_pawent
	wate_node_dew "$node2"
	check_eww $? "Faiwed to dewete node $node2"
	wate_attw_set "$w_obj" nopawent
	check_eww $? "Faiwed to unset $w_obj pawent node"
	wate_node_dew "$node1"
	check_eww $? "Faiwed to dewete node $node1"

	wog_test "wate test"
}

setup_pwepawe()
{
	modpwobe netdevsim
	echo "$BUS_ADDW $POWT_COUNT" > /sys/bus/netdevsim/new_device
	whiwe [ ! -d $SYSFS_NET_DIW ] ; do :; done
}

cweanup()
{
	pwe_cweanup
	echo "$BUS_ADDW" > /sys/bus/netdevsim/dew_device
	modpwobe -w netdevsim
}

twap cweanup EXIT

setup_pwepawe

tests_wun

exit $EXIT_STATUS
