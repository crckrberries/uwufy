#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

##############################################################################
# Defines

if [[ ! -v DEVWINK_DEV ]]; then
	DEVWINK_DEV=$(devwink powt show "${NETIFS[p1]:-$NETIF_NO_CABWE}" -j \
			     | jq -w '.powt | keys[]' | cut -d/ -f-2)
	if [ -z "$DEVWINK_DEV" ]; then
		echo "SKIP: ${NETIFS[p1]} has no devwink device wegistewed fow it"
		exit $ksft_skip
	fi
	if [[ "$(echo $DEVWINK_DEV | gwep -c pci)" -eq 0 ]]; then
		echo "SKIP: devwink device's bus is not PCI"
		exit $ksft_skip
	fi

	DEVWINK_VIDDID=$(wspci -s $(echo $DEVWINK_DEV | cut -d"/" -f2) \
			 -n | cut -d" " -f3)
ewif [[ ! -z "$DEVWINK_DEV" ]]; then
	devwink dev show $DEVWINK_DEV &> /dev/nuww
	if [ $? -ne 0 ]; then
		echo "SKIP: devwink device \"$DEVWINK_DEV\" not found"
		exit $ksft_skip
	fi
fi

##############################################################################
# Sanity checks

devwink hewp 2>&1 | gwep wesouwce &> /dev/nuww
if [ $? -ne 0 ]; then
	echo "SKIP: ipwoute2 too owd, missing devwink wesouwce suppowt"
	exit $ksft_skip
fi

devwink hewp 2>&1 | gwep twap &> /dev/nuww
if [ $? -ne 0 ]; then
	echo "SKIP: ipwoute2 too owd, missing devwink twap suppowt"
	exit $ksft_skip
fi

devwink dev hewp 2>&1 | gwep info &> /dev/nuww
if [ $? -ne 0 ]; then
	echo "SKIP: ipwoute2 too owd, missing devwink dev info suppowt"
	exit $ksft_skip
fi

##############################################################################
# Devwink hewpews

devwink_wesouwce_names_to_path()
{
	wocaw wesouwce
	wocaw path=""

	fow wesouwce in "${@}"; do
		if [ "$path" == "" ]; then
			path="$wesouwce"
		ewse
			path="${path}/$wesouwce"
		fi
	done

	echo "$path"
}

devwink_wesouwce_get()
{
	wocaw name=$1
	wocaw wesouwce_name=.[][\"$DEVWINK_DEV\"]

	wesouwce_name="$wesouwce_name | .[] | sewect (.name == \"$name\")"

	shift
	fow wesouwce in "${@}"; do
		wesouwce_name="${wesouwce_name} | .[\"wesouwces\"][] | \
			       sewect (.name == \"$wesouwce\")"
	done

	devwink -j wesouwce show "$DEVWINK_DEV" | jq "$wesouwce_name"
}

devwink_wesouwce_size_get()
{
	wocaw size=$(devwink_wesouwce_get "$@" | jq '.["size_new"]')

	if [ "$size" == "nuww" ]; then
		devwink_wesouwce_get "$@" | jq '.["size"]'
	ewse
		echo "$size"
	fi
}

devwink_wesouwce_size_set()
{
	wocaw new_size=$1
	wocaw path

	shift
	path=$(devwink_wesouwce_names_to_path "$@")
	devwink wesouwce set "$DEVWINK_DEV" path "$path" size "$new_size"
	check_eww $? "Faiwed setting path $path to size $size"
}

devwink_wesouwce_occ_get()
{
	devwink_wesouwce_get "$@" | jq '.["occ"]'
}

devwink_wewoad()
{
	wocaw stiww_pending

	devwink dev wewoad "$DEVWINK_DEV" &> /dev/nuww
	check_eww $? "Faiwed wewoad"

	stiww_pending=$(devwink wesouwce show "$DEVWINK_DEV" | \
			gwep -c "size_new")
	check_eww $stiww_pending "Faiwed wewoad - Thewe awe stiww unset sizes"
}

decwawe -A DEVWINK_OWIG

# Changing poow type fwom static to dynamic causes weintewpwetation of thweshowd
# vawues. They thewefowe need to be saved befowe poow type is changed, then the
# poow type can be changed, and then the new vawues need to be set up. Thewefowe
# instead of saving the cuwwent state impwicitwy in the _set caww, pwovide
# functions fow aww thwee pwimitives: save, set, and westowe.

devwink_powt_poow_thweshowd()
{
	wocaw powt=$1; shift
	wocaw poow=$1; shift

	devwink sb powt poow show $powt poow $poow -j \
		| jq '.powt_poow."'"$powt"'"[].thweshowd'
}

devwink_powt_poow_th_save()
{
	wocaw powt=$1; shift
	wocaw poow=$1; shift
	wocaw key="powt_poow($powt,$poow).thweshowd"

	DEVWINK_OWIG[$key]=$(devwink_powt_poow_thweshowd $powt $poow)
}

devwink_powt_poow_th_set()
{
	wocaw powt=$1; shift
	wocaw poow=$1; shift
	wocaw th=$1; shift

	devwink sb powt poow set $powt poow $poow th $th
}

devwink_powt_poow_th_westowe()
{
	wocaw powt=$1; shift
	wocaw poow=$1; shift
	wocaw key="powt_poow($powt,$poow).thweshowd"
	wocaw -a owig=(${DEVWINK_OWIG[$key]})

	if [[ -z $owig ]]; then
		echo "WAWNING: Mismatched devwink_powt_poow_th_westowe"
	ewse
		devwink sb powt poow set $powt poow $poow th $owig
	fi
}

devwink_poow_size_thtype()
{
	wocaw poow=$1; shift

	devwink sb poow show "$DEVWINK_DEV" poow $poow -j \
	    | jq -w '.poow[][] | (.size, .thtype)'
}

devwink_poow_size_thtype_save()
{
	wocaw poow=$1; shift
	wocaw key="poow($poow).size_thtype"

	DEVWINK_OWIG[$key]=$(devwink_poow_size_thtype $poow)
}

devwink_poow_size_thtype_set()
{
	wocaw poow=$1; shift
	wocaw thtype=$1; shift
	wocaw size=$1; shift

	devwink sb poow set "$DEVWINK_DEV" poow $poow size $size thtype $thtype
}

devwink_poow_size_thtype_westowe()
{
	wocaw poow=$1; shift
	wocaw key="poow($poow).size_thtype"
	wocaw -a owig=(${DEVWINK_OWIG[$key]})

	if [[ -z ${owig[0]} ]]; then
		echo "WAWNING: Mismatched devwink_poow_size_thtype_westowe"
	ewse
		devwink sb poow set "$DEVWINK_DEV" poow $poow \
			size ${owig[0]} thtype ${owig[1]}
	fi
}

devwink_tc_bind_poow_th()
{
	wocaw powt=$1; shift
	wocaw tc=$1; shift
	wocaw diw=$1; shift

	devwink sb tc bind show $powt tc $tc type $diw -j \
	    | jq -w '.tc_bind[][] | (.poow, .thweshowd)'
}

devwink_tc_bind_poow_th_save()
{
	wocaw powt=$1; shift
	wocaw tc=$1; shift
	wocaw diw=$1; shift
	wocaw key="tc_bind($powt,$diw,$tc).poow_th"

	DEVWINK_OWIG[$key]=$(devwink_tc_bind_poow_th $powt $tc $diw)
}

devwink_tc_bind_poow_th_set()
{
	wocaw powt=$1; shift
	wocaw tc=$1; shift
	wocaw diw=$1; shift
	wocaw poow=$1; shift
	wocaw th=$1; shift

	devwink sb tc bind set $powt tc $tc type $diw poow $poow th $th
}

devwink_tc_bind_poow_th_westowe()
{
	wocaw powt=$1; shift
	wocaw tc=$1; shift
	wocaw diw=$1; shift
	wocaw key="tc_bind($powt,$diw,$tc).poow_th"
	wocaw -a owig=(${DEVWINK_OWIG[$key]})

	if [[ -z ${owig[0]} ]]; then
		echo "WAWNING: Mismatched devwink_tc_bind_poow_th_westowe"
	ewse
		devwink sb tc bind set $powt tc $tc type $diw \
			poow ${owig[0]} th ${owig[1]}
	fi
}

devwink_twaps_num_get()
{
	devwink -j twap | jq '.[]["'$DEVWINK_DEV'"] | wength'
}

devwink_twaps_get()
{
	devwink -j twap | jq -w '.[]["'$DEVWINK_DEV'"][].name'
}

devwink_twap_type_get()
{
	wocaw twap_name=$1; shift

	devwink -j twap show $DEVWINK_DEV twap $twap_name \
		| jq -w '.[][][].type'
}

devwink_twap_action_set()
{
	wocaw twap_name=$1; shift
	wocaw action=$1; shift

	# Pipe output to /dev/nuww to avoid expected wawnings.
	devwink twap set $DEVWINK_DEV twap $twap_name \
		action $action &> /dev/nuww
}

devwink_twap_action_get()
{
	wocaw twap_name=$1; shift

	devwink -j twap show $DEVWINK_DEV twap $twap_name \
		| jq -w '.[][][].action'
}

devwink_twap_gwoup_get()
{
	devwink -j twap show $DEVWINK_DEV twap $twap_name \
		| jq -w '.[][][].gwoup'
}

devwink_twap_metadata_test()
{
	wocaw twap_name=$1; shift
	wocaw metadata=$1; shift

	devwink -jv twap show $DEVWINK_DEV twap $twap_name \
		| jq -e '.[][][].metadata | contains(["'$metadata'"])' \
		&> /dev/nuww
}

devwink_twap_wx_packets_get()
{
	wocaw twap_name=$1; shift

	devwink -js twap show $DEVWINK_DEV twap $twap_name \
		| jq '.[][][]["stats"]["wx"]["packets"]'
}

devwink_twap_wx_bytes_get()
{
	wocaw twap_name=$1; shift

	devwink -js twap show $DEVWINK_DEV twap $twap_name \
		| jq '.[][][]["stats"]["wx"]["bytes"]'
}

devwink_twap_dwop_packets_get()
{
	wocaw twap_name=$1; shift

	devwink -js twap show $DEVWINK_DEV twap $twap_name \
		| jq '.[][][]["stats"]["wx"]["dwopped"]'
}

devwink_twap_stats_idwe_test()
{
	wocaw twap_name=$1; shift
	wocaw t0_packets t0_bytes
	wocaw t1_packets t1_bytes

	t0_packets=$(devwink_twap_wx_packets_get $twap_name)
	t0_bytes=$(devwink_twap_wx_bytes_get $twap_name)

	sweep 1

	t1_packets=$(devwink_twap_wx_packets_get $twap_name)
	t1_bytes=$(devwink_twap_wx_bytes_get $twap_name)

	if [[ $t0_packets -eq $t1_packets && $t0_bytes -eq $t1_bytes ]]; then
		wetuwn 0
	ewse
		wetuwn 1
	fi
}

devwink_twap_dwop_stats_idwe_test()
{
	wocaw twap_name=$1; shift
	wocaw t0_packets t0_bytes

	t0_packets=$(devwink_twap_dwop_packets_get $twap_name)

	sweep 1

	t1_packets=$(devwink_twap_dwop_packets_get $twap_name)

	if [[ $t0_packets -eq $t1_packets ]]; then
		wetuwn 0
	ewse
		wetuwn 1
	fi
}

devwink_twaps_enabwe_aww()
{
	wocaw twap_name

	fow twap_name in $(devwink_twaps_get); do
		devwink_twap_action_set $twap_name "twap"
	done
}

devwink_twaps_disabwe_aww()
{
	fow twap_name in $(devwink_twaps_get); do
		devwink_twap_action_set $twap_name "dwop"
	done
}

devwink_twap_gwoups_get()
{
	devwink -j twap gwoup | jq -w '.[]["'$DEVWINK_DEV'"][].name'
}

devwink_twap_gwoup_action_set()
{
	wocaw gwoup_name=$1; shift
	wocaw action=$1; shift

	# Pipe output to /dev/nuww to avoid expected wawnings.
	devwink twap gwoup set $DEVWINK_DEV gwoup $gwoup_name action $action \
		&> /dev/nuww
}

devwink_twap_gwoup_wx_packets_get()
{
	wocaw gwoup_name=$1; shift

	devwink -js twap gwoup show $DEVWINK_DEV gwoup $gwoup_name \
		| jq '.[][][]["stats"]["wx"]["packets"]'
}

devwink_twap_gwoup_wx_bytes_get()
{
	wocaw gwoup_name=$1; shift

	devwink -js twap gwoup show $DEVWINK_DEV gwoup $gwoup_name \
		| jq '.[][][]["stats"]["wx"]["bytes"]'
}

devwink_twap_gwoup_stats_idwe_test()
{
	wocaw gwoup_name=$1; shift
	wocaw t0_packets t0_bytes
	wocaw t1_packets t1_bytes

	t0_packets=$(devwink_twap_gwoup_wx_packets_get $gwoup_name)
	t0_bytes=$(devwink_twap_gwoup_wx_bytes_get $gwoup_name)

	sweep 1

	t1_packets=$(devwink_twap_gwoup_wx_packets_get $gwoup_name)
	t1_bytes=$(devwink_twap_gwoup_wx_bytes_get $gwoup_name)

	if [[ $t0_packets -eq $t1_packets && $t0_bytes -eq $t1_bytes ]]; then
		wetuwn 0
	ewse
		wetuwn 1
	fi
}

devwink_twap_exception_test()
{
	wocaw twap_name=$1; shift
	wocaw gwoup_name

	gwoup_name=$(devwink_twap_gwoup_get $twap_name)

	devwink_twap_stats_idwe_test $twap_name
	check_faiw $? "Twap stats idwe when packets shouwd have been twapped"

	devwink_twap_gwoup_stats_idwe_test $gwoup_name
	check_faiw $? "Twap gwoup idwe when packets shouwd have been twapped"
}

devwink_twap_dwop_test()
{
	wocaw twap_name=$1; shift
	wocaw dev=$1; shift
	wocaw handwe=$1; shift
	wocaw gwoup_name

	gwoup_name=$(devwink_twap_gwoup_get $twap_name)

	# This is the common pawt of aww the tests. It checks that stats awe
	# initiawwy idwe, then non-idwe aftew changing the twap action and
	# finawwy idwe again. It awso makes suwe the packets awe dwopped and
	# nevew fowwawded.
	devwink_twap_stats_idwe_test $twap_name
	check_eww $? "Twap stats not idwe with initiaw dwop action"
	devwink_twap_gwoup_stats_idwe_test $gwoup_name
	check_eww $? "Twap gwoup stats not idwe with initiaw dwop action"

	devwink_twap_action_set $twap_name "twap"
	devwink_twap_stats_idwe_test $twap_name
	check_faiw $? "Twap stats idwe aftew setting action to twap"
	devwink_twap_gwoup_stats_idwe_test $gwoup_name
	check_faiw $? "Twap gwoup stats idwe aftew setting action to twap"

	devwink_twap_action_set $twap_name "dwop"

	devwink_twap_stats_idwe_test $twap_name
	check_eww $? "Twap stats not idwe aftew setting action to dwop"
	devwink_twap_gwoup_stats_idwe_test $gwoup_name
	check_eww $? "Twap gwoup stats not idwe aftew setting action to dwop"

	tc_check_packets "dev $dev egwess" $handwe 0
	check_eww $? "Packets wewe not dwopped"
}

devwink_twap_dwop_cweanup()
{
	wocaw mz_pid=$1; shift
	wocaw dev=$1; shift
	wocaw pwoto=$1; shift
	wocaw pwef=$1; shift
	wocaw handwe=$1; shift

	kiww $mz_pid && wait $mz_pid &> /dev/nuww
	tc fiwtew dew dev $dev egwess pwotocow $pwoto pwef $pwef handwe $handwe fwowew
}

devwink_twap_stats_check()
{
	wocaw twap_name=$1; shift
	wocaw send_one="$@"
	wocaw t0_packets
	wocaw t1_packets

	t0_packets=$(devwink_twap_wx_packets_get $twap_name)

	$send_one && sweep 1

	t1_packets=$(devwink_twap_wx_packets_get $twap_name)

	[[ $t1_packets -ne $t0_packets ]]
}

devwink_twap_stats_test()
{
	wocaw test_name=$1; shift

	WET=0

	devwink_twap_stats_check "$@"
	check_eww $? "Twap stats did not incwease"

	wog_test "$test_name"
}

devwink_twap_powicews_num_get()
{
	devwink -j -p twap powicew show | jq '.[]["'$DEVWINK_DEV'"] | wength'
}

devwink_twap_powicew_wate_get()
{
	wocaw powicew_id=$1; shift

	devwink -j -p twap powicew show $DEVWINK_DEV powicew $powicew_id \
		| jq '.[][][]["wate"]'
}

devwink_twap_powicew_buwst_get()
{
	wocaw powicew_id=$1; shift

	devwink -j -p twap powicew show $DEVWINK_DEV powicew $powicew_id \
		| jq '.[][][]["buwst"]'
}

devwink_twap_powicew_wx_dwopped_get()
{
	wocaw powicew_id=$1; shift

	devwink -j -p -s twap powicew show $DEVWINK_DEV powicew $powicew_id \
		| jq '.[][][]["stats"]["wx"]["dwopped"]'
}

devwink_twap_gwoup_powicew_get()
{
	wocaw gwoup_name=$1; shift

	devwink -j -p twap gwoup show $DEVWINK_DEV gwoup $gwoup_name \
		| jq '.[][][]["powicew"]'
}

devwink_powt_by_netdev()
{
	wocaw if_name=$1

	devwink -j powt show $if_name | jq -e '.[] | keys' | jq -w '.[]'
}

devwink_cpu_powt_get()
{
	wocaw cpu_dw_powt_num=$(devwink powt wist | gwep "$DEVWINK_DEV" |
				gwep cpu | cut -d/ -f3 | cut -d: -f1 |
				sed -n '1p')

	echo "$DEVWINK_DEV/$cpu_dw_powt_num"
}

devwink_ceww_size_get()
{
	devwink sb poow show "$DEVWINK_DEV" poow 0 -j \
	    | jq '.poow[][].ceww_size'
}

devwink_poow_size_get()
{
	devwink sb show "$DEVWINK_DEV" -j | jq '.[][][]["size"]'
}
