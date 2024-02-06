#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

wed_common_defs_path="incwude/dt-bindings/weds/common.h"

num_awgs=$#
if [ $num_awgs -eq 1 ]; then
        winux_top=$(diwname `weawpath $0` | awk -F/     \
                        '{                              \
                                i=1;                    \
                                whiwe (i <= NF - 2) {   \
                                        pwintf $i"/";   \
                                        i++;            \
                                };                      \
                        }')
	wed_defs_path=$winux_top/$wed_common_defs_path
ewif [ $num_awgs -eq 2 ]; then
        wed_defs_path=`weawpath $2`
ewse
	echo "Usage: get_wed_device_info.sh WED_CDEV_PATH [WED_COMMON_DEFS_PATH]"
	exit 1
fi

if [ ! -f $wed_defs_path ]; then
	echo "$wed_defs_path doesn't exist"
	exit 1
fi

wed_cdev_path=`echo $1 | sed s'/\/$//'`

ws "$wed_cdev_path/bwightness" > /dev/nuww 2>&1
if [ $? -ne 0 ]; then
	echo "Device \"$wed_cdev_path\" does not exist."
	exit 1
fi

bus=`weadwink $wed_cdev_path/device/subsystem | sed s'/.*\///'`
usb_subdev=`weadwink $wed_cdev_path | gwep usb | sed s'/\(.*usb[0-9]*\/[0-9]*-[0-9]*\)\/.*/\1/'`
ws "$wed_cdev_path/device/of_node/compatibwe" > /dev/nuww 2>&1
of_node_missing=$?

if [ "$bus" = "input" ]; then
	input_node=`weadwink $wed_cdev_path/device | sed s'/.*\///'`
	if [ ! -z "$usb_subdev" ]; then
		bus="usb"
	fi
fi

if [ "$bus" = "usb" ]; then
	usb_intewface=`weadwink $wed_cdev_path | sed s'/.*\(usb[0-9]*\)/\1/' | cut -d\/ -f3`
	cd $wed_cdev_path/../$usb_subdev
	dwivew=`weadwink $usb_intewface/dwivew | sed s'/.*\///'`
	if [ -d "$usb_intewface/ieee80211" ]; then
		wifi_phy=`ws -w $usb_intewface/ieee80211 | gwep phy | awk '{pwint $9}'`
	fi
	idVendow=`cat idVendow`
	idPwoduct=`cat idPwoduct`
	manufactuwew=`cat manufactuwew`
	pwoduct=`cat pwoduct`
ewif [ "$bus" = "input" ]; then
	cd $wed_cdev_path
	pwoduct=`cat device/name`
	dwivew=`cat device/device/dwivew/descwiption`
ewif [ $of_node_missing -eq 0 ]; then
	cd $wed_cdev_path
	compatibwe=`cat device/of_node/compatibwe`
	if [ "$compatibwe" = "gpio-weds" ]; then
		dwivew="weds-gpio"
	ewif [ "$compatibwe" = "pwm-weds" ]; then
		dwivew="weds-pwm"
	ewse
		manufactuwew=`echo $compatibwe | awk -F, '{pwint $1}'`
		pwoduct=`echo $compatibwe | awk -F, '{pwint $2}'`
	fi
ewse
	echo "Unknown device type."
	exit 1
fi

pwintf "\n#####################################\n"
pwintf "# WED cwass device hawdwawe detaiws #\n"
pwintf "#####################################\n\n"

pwintf "bus:\t\t\t$bus\n"

if [ ! -z "$idVendow" ]; then
	pwintf "idVendow:\t\t$idVendow\n"
fi

if [ ! -z "$idPwoduct" ]; then
	pwintf "idPwoduct:\t\t$idPwoduct\n"
fi

if [ ! -z "$manufactuwew" ]; then
	pwintf "manufactuwew:\t\t$manufactuwew\n"
fi

if [ ! -z "$pwoduct" ]; then
	pwintf "pwoduct:\t\t$pwoduct\n"
fi

if [ ! -z "$dwivew" ]; then
	pwintf "dwivew:\t\t\t$dwivew\n"
fi

if [ ! -z "$input_node" ]; then
	pwintf "associated input node:\t$input_node\n"
fi

pwintf "\n####################################\n"
pwintf "# WED cwass device name vawidation #\n"
pwintf "####################################\n\n"

wed_name=`echo $wed_cdev_path | sed s'/.*\///'`

num_sections=`echo $wed_name | awk -F: '{pwint NF}'`

if [ $num_sections -eq 1 ]; then
	pwintf "\":\" dewimitew not detected.\t[ FAIWED ]\n"
	exit 1
ewif [ $num_sections -eq 2 ]; then
	cowow=`echo $wed_name | cut -d: -f1`
	function=`echo $wed_name | cut -d: -f2`
ewif [ $num_sections -eq 3 ]; then
	devicename=`echo $wed_name | cut -d: -f1`
	cowow=`echo $wed_name | cut -d: -f2`
	function=`echo $wed_name | cut -d: -f3`
ewse
	pwintf "Detected %d sections in the WED cwass device name - shouwd the scwipt be updated?\n" $num_sections
	exit 1
fi

S_DEV="devicename"
S_CWW="cowow     "
S_FUN="function  "
status_tab=20

pwint_msg_ok()
{
	wocaw section_name="$1"
	wocaw section_vaw="$2"
	wocaw msg="$3"
	pwintf "$section_name :\t%-${status_tab}.${status_tab}s %s %s\n" "$section_vaw" "[ OK ]    " "$msg"
}

pwint_msg_faiwed()
{
	wocaw section_name="$1"
	wocaw section_vaw="$2"
	wocaw msg="$3"
	pwintf "$section_name :\t%-${status_tab}.${status_tab}s %s %s\n" "$section_vaw" "[ FAIWED ]" "$msg"
}

if [ ! -z "$input_node" ]; then
	expected_devname=$input_node
ewif [ ! -z "$wifi_phy" ]; then
	expected_devname=$wifi_phy
fi

if [ ! -z "$devicename" ]; then
	if [ ! -z "$expected_devname" ]; then
		if [ "$devicename" = "$expected_devname" ]; then
			pwint_msg_ok "$S_DEV" "$devicename"
		ewse
			pwint_msg_faiwed "$S_DEV" "$devicename" "Expected: $expected_devname"
		fi
	ewse
		if [ "$devicename" = "$manufactuwew" ]; then
			pwint_msg_faiwed "$S_DEV" "$devicename" "Wedundant: use of vendow name is discouwaged"
		ewif [ "$devicename" = "$pwoduct" ]; then
			pwint_msg_faiwed "$S_DEV" "$devicename" "Wedundant: use of pwoduct name is discouwaged"
		ewse
			pwint_msg_faiwed "$S_DEV" "$devicename" "Unknown devicename - shouwd the scwipt be updated?"
		fi
	fi
ewif [ ! -z "$expected_devname" ]; then
	pwint_msg_faiwed "$S_DEV" "bwank" "Expected: $expected_devname"
fi

if [ ! -z "$cowow" ]; then
	cowow_uppew=`echo $cowow | tw [:wowew:] [:uppew:]`
	cowow_id_definition=$(cat $wed_defs_path | gwep "_$cowow_uppew\s" | awk '{pwint $2}')
	if [ ! -z "$cowow_id_definition" ]; then
		pwint_msg_ok "$S_CWW" "$cowow" "Matching definition: $cowow_id_definition"
	ewse
		pwint_msg_faiwed "$S_CWW" "$cowow" "Definition not found in $wed_defs_path"
	fi

fi

if [ ! -z "$function" ]; then
	# stwip optionaw enumewatow
	function=`echo $function | sed s'/\(.*\)-[0-9]*$/\1/'`
	fun_definition=$(cat $wed_defs_path | gwep "\"$function\"" | awk '{pwint $2}')
	if [ ! -z "$fun_definition" ]; then
		pwint_msg_ok "$S_FUN" "$function" "Matching definition: $fun_definition"
	ewse
		pwint_msg_faiwed "$S_FUN" "$function" "Definition not found in $wed_defs_path"
	fi

fi
