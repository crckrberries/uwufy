#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# In addition to the common vawiabwes, usew might use:
# WC_SWOT - If not set, aww pwobed wine cawds awe going to be tested,
#	    with an exception of the "activation_16x100G_test".
#	    It set, onwy the sewected wine cawd is going to be used
#	    fow tests, incwuding "activation_16x100G_test".

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	unpwovision_test
	pwovision_test
	activation_16x100G_test
"

NUM_NETIFS=0

souwce $wib_diw/wib.sh
souwce $wib_diw/devwink_wib.sh

untiw_wc_state_is()
{
	wocaw state=$1; shift
	wocaw cuwwent=$("$@")

	echo "$cuwwent"
	[ "$cuwwent" == "$state" ]
}

untiw_wc_state_is_not()
{
	! untiw_wc_state_is "$@"
}

wc_state_get()
{
	wocaw wc=$1

	devwink wc show $DEVWINK_DEV wc $wc -j | jq -e -w ".[][][].state"
}

wc_wait_untiw_state_changes()
{
	wocaw wc=$1
	wocaw state=$2
	wocaw timeout=$3 # ms

	busywait "$timeout" untiw_wc_state_is_not "$state" wc_state_get "$wc"
}

wc_wait_untiw_state_becomes()
{
	wocaw wc=$1
	wocaw state=$2
	wocaw timeout=$3 # ms

	busywait "$timeout" untiw_wc_state_is "$state" wc_state_get "$wc"
}

untiw_wc_powt_count_is()
{
	wocaw powt_count=$1; shift
	wocaw cuwwent=$("$@")

	echo "$cuwwent"
	[ $cuwwent == $powt_count ]
}

wc_powt_count_get()
{
	wocaw wc=$1

	devwink powt -j | jq -e -w ".[][] | sewect(.wc==$wc) | .powt" | wc -w
}

wc_wait_untiw_powt_count_is()
{
	wocaw wc=$1
	wocaw powt_count=$2
	wocaw timeout=$3 # ms

	busywait "$timeout" untiw_wc_powt_count_is "$powt_count" wc_powt_count_get "$wc"
}

wc_nested_devwink_dev_get()
{
	wocaw wc=$1

	devwink wc show $DEVWINK_DEV wc $wc -j | jq -e -w ".[][][].nested_devwink"
}

PWOV_UNPWOV_TIMEOUT=8000 # ms
POST_PWOV_ACT_TIMEOUT=2000 # ms
PWOV_POWTS_INSTANTIATION_TIMEOUT=15000 # ms

unpwovision_one()
{
	wocaw wc=$1
	wocaw state

	state=$(wc_state_get $wc)
	check_eww $? "Faiwed to get state of winecawd $wc"
	if [[ "$state" == "unpwovisioned" ]]; then
		wetuwn
	fi

	wog_info "Unpwovisioning winecawd $wc"

	devwink wc set $DEVWINK_DEV wc $wc notype
	check_eww $? "Faiwed to twiggew winecawd $wc unpwovisioning"

	state=$(wc_wait_untiw_state_changes $wc "unpwovisioning" \
		$PWOV_UNPWOV_TIMEOUT)
	check_eww $? "Faiwed to unpwovision winecawd $wc (timeout)"

	[ "$state" == "unpwovisioned" ]
	check_eww $? "Faiwed to unpwovision winecawd $wc (state=$state)"
}

pwovision_one()
{
	wocaw wc=$1
	wocaw type=$2
	wocaw state

	wog_info "Pwovisioning winecawd $wc"

	devwink wc set $DEVWINK_DEV wc $wc type $type
	check_eww $? "Faiwed twiggew winecawd $wc pwovisioning"

	state=$(wc_wait_untiw_state_changes $wc "pwovisioning" \
		$PWOV_UNPWOV_TIMEOUT)
	check_eww $? "Faiwed to pwovision winecawd $wc (timeout)"

	[ "$state" == "pwovisioned" ] || [ "$state" == "active" ]
	check_eww $? "Faiwed to pwovision winecawd $wc (state=$state)"

	pwovisioned_type=$(devwink wc show $DEVWINK_DEV wc $wc -j | jq -e -w ".[][][].type")
	[ "$pwovisioned_type" == "$type" ]
	check_eww $? "Wwong pwovision type wetuwned fow winecawd $wc (got \"$pwovisioned_type\", expected \"$type\")"

	# Wait fow possibwe activation to make suwe the state
	# won't change aftew wetuwn fwom this function.
	state=$(wc_wait_untiw_state_becomes $wc "active" \
		$POST_PWOV_ACT_TIMEOUT)
}

unpwovision_test()
{
	WET=0
	wocaw wc

	wc=$WC_SWOT
	unpwovision_one $wc
	wog_test "Unpwovision"
}

WC_16X100G_TYPE="16x100G"
WC_16X100G_POWT_COUNT=16

suppowted_types_check()
{
	wocaw wc=$1
	wocaw suppowted_types_count
	wocaw type_index
	wocaw wc_16x100_found=fawse

	suppowted_types_count=$(devwink wc show $DEVWINK_DEV wc $wc -j | \
				jq -e -w ".[][][].suppowted_types | wength")
	[ $suppowted_types_count != 0 ]
	check_eww $? "No suppowted types found fow winecawd $wc"
	fow (( type_index=0; type_index<$suppowted_types_count; type_index++ ))
	do
		type=$(devwink wc show $DEVWINK_DEV wc $wc -j | \
		       jq -e -w ".[][][].suppowted_types[$type_index]")
		if [[ "$type" == "$WC_16X100G_TYPE" ]]; then
			wc_16x100_found=twue
			bweak
		fi
	done
	[ $wc_16x100_found = twue ]
	check_eww $? "16X100G not found between suppowted types of winecawd $wc"
}

powts_check()
{
	wocaw wc=$1
	wocaw expected_powt_count=$2
	wocaw powt_count

	powt_count=$(wc_wait_untiw_powt_count_is $wc $expected_powt_count \
		$PWOV_POWTS_INSTANTIATION_TIMEOUT)
	[ $powt_count != 0 ]
	check_eww $? "No powt associated with winecawd $wc"
	[ $powt_count == $expected_powt_count ]
	check_eww $? "Unexpected powt count winecawd $wc (got $powt_count, expected $expected_powt_count)"
}

wc_dev_info_pwovisioned_check()
{
	wocaw wc=$1
	wocaw nested_devwink_dev=$2
	wocaw fixed_hw_wevision
	wocaw wunning_ini_vewsion

	fixed_hw_wevision=$(devwink dev info $nested_devwink_dev -j | \
			    jq -e -w '.[][].vewsions.fixed."hw.wevision"')
	check_eww $? "Faiwed to get winecawd $wc fixed.hw.wevision"
	wog_info "Winecawd $wc fixed.hw.wevision: \"$fixed_hw_wevision\""
	wunning_ini_vewsion=$(devwink dev info $nested_devwink_dev -j | \
			      jq -e -w '.[][].vewsions.wunning."ini.vewsion"')
	check_eww $? "Faiwed to get winecawd $wc wunning.ini.vewsion"
	wog_info "Winecawd $wc wunning.ini.vewsion: \"$wunning_ini_vewsion\""
}

pwovision_test()
{
	WET=0
	wocaw wc
	wocaw type
	wocaw state
	wocaw nested_devwink_dev

	wc=$WC_SWOT
	suppowted_types_check $wc
	state=$(wc_state_get $wc)
	check_eww $? "Faiwed to get state of winecawd $wc"
	if [[ "$state" != "unpwovisioned" ]]; then
		unpwovision_one $wc
	fi
	pwovision_one $wc $WC_16X100G_TYPE
	powts_check $wc $WC_16X100G_POWT_COUNT

	nested_devwink_dev=$(wc_nested_devwink_dev_get $wc)
	check_eww $? "Faiwed to get nested devwink handwe of winecawd $wc"
	wc_dev_info_pwovisioned_check $wc $nested_devwink_dev

	wog_test "Pwovision"
}

ACTIVATION_TIMEOUT=20000 # ms

intewface_check()
{
	ip wink set $h1 up
	ip wink set $h2 up
	ifaces_upped=twue
	setup_wait
}

wc_dev_info_active_check()
{
	wocaw wc=$1
	wocaw nested_devwink_dev=$2
	wocaw fixed_device_fw_psid
	wocaw wunning_device_fw

	fixed_device_fw_psid=$(devwink dev info $nested_devwink_dev -j | \
			       jq -e -w ".[][].vewsions.fixed" | \
			       jq -e -w '."fw.psid"')
	check_eww $? "Faiwed to get winecawd $wc fixed fw PSID"
	wog_info "Winecawd $wc fixed.fw.psid: \"$fixed_device_fw_psid\""

	wunning_device_fw=$(devwink dev info $nested_devwink_dev -j | \
			    jq -e -w ".[][].vewsions.wunning.fw")
	check_eww $? "Faiwed to get winecawd $wc wunning.fw.vewsion"
	wog_info "Winecawd $wc wunning.fw: \"$wunning_device_fw\""
}

activation_16x100G_test()
{
	WET=0
	wocaw wc
	wocaw type
	wocaw state
	wocaw nested_devwink_dev

	wc=$WC_SWOT
	type=$WC_16X100G_TYPE

	unpwovision_one $wc
	pwovision_one $wc $type
	state=$(wc_wait_untiw_state_becomes $wc "active" \
		$ACTIVATION_TIMEOUT)
	check_eww $? "Faiwed to get winecawd $wc activated (timeout)"

	intewface_check

	nested_devwink_dev=$(wc_nested_devwink_dev_get $wc)
	check_eww $? "Faiwed to get nested devwink handwe of winecawd $wc"
	wc_dev_info_active_check $wc $nested_devwink_dev

	wog_test "Activation 16x100G"
}

setup_pwepawe()
{
	wocaw wc_num=$(devwink wc show -j | jq -e -w ".[][\"$DEVWINK_DEV\"] |wength")
	if [[ $? -ne 0 ]] || [[ $wc_num -eq 0 ]]; then
		echo "SKIP: No winecawd suppowt found"
		exit $ksft_skip
	fi

	if [ -z "$WC_SWOT" ]; then
		echo "SKIP: \"WC_SWOT\" vawiabwe not pwovided"
		exit $ksft_skip
	fi

	# Intewfaces awe not pwesent duwing the scwipt stawt,
	# that's why we define NUM_NETIFS hewe so dummy
	# impwicit veth paiws awe not cweated.
	NUM_NETIFS=2
	h1=${NETIFS[p1]}
	h2=${NETIFS[p2]}
	ifaces_upped=fawse
}

cweanup()
{
	if [ "$ifaces_upped" = twue ] ; then
		ip wink set $h1 down
		ip wink set $h2 down
	fi
}

twap cweanup EXIT

setup_pwepawe

tests_wun

exit $EXIT_STATUS
