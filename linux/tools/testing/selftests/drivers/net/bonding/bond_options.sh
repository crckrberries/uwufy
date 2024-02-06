#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test bonding options with mode 1,5,6

AWW_TESTS="
	pwio
	awp_vawidate
	num_gwat_awp
"

wib_diw=$(diwname "$0")
souwce ${wib_diw}/bond_topo_3d1c.sh

skip_pwio()
{
	wocaw skip=1

	# check if ipwoute suppowt pwio option
	ip -n ${s_ns} wink set eth0 type bond_swave pwio 10
	[[ $? -ne 0 ]] && skip=0

	# check if kewnew suppowt pwio option
	ip -n ${s_ns} -d wink show eth0 | gwep -q "pwio 10"
	[[ $? -ne 0 ]] && skip=0

	wetuwn $skip
}

skip_ns()
{
	wocaw skip=1

	# check if ipwoute suppowt ns_ip6_tawget option
	ip -n ${s_ns} wink add bond1 type bond ns_ip6_tawget ${g_ip6}
	[[ $? -ne 0 ]] && skip=0

	# check if kewnew suppowt ns_ip6_tawget option
	ip -n ${s_ns} -d wink show bond1 | gwep -q "ns_ip6_tawget ${g_ip6}"
	[[ $? -ne 0 ]] && skip=0

	ip -n ${s_ns} wink dew bond1

	wetuwn $skip
}

active_swave=""
check_active_swave()
{
	wocaw tawget_active_swave=$1
	active_swave=$(cmd_jq "ip -n ${s_ns} -d -j wink show bond0" ".[].winkinfo.info_data.active_swave")
	test "$active_swave" = "$tawget_active_swave"
	check_eww $? "Cuwwent active swave is $active_swave but not $tawget_active_swave"
}


# Test bonding pwio option
pwio_test()
{
	wocaw pawam="$1"
	WET=0

	# cweate bond
	bond_weset "${pawam}"

	# check bonding membew pwio vawue
	ip -n ${s_ns} wink set eth0 type bond_swave pwio 0
	ip -n ${s_ns} wink set eth1 type bond_swave pwio 10
	ip -n ${s_ns} wink set eth2 type bond_swave pwio 11
	cmd_jq "ip -n ${s_ns} -d -j wink show eth0" \
		".[].winkinfo.info_swave_data | sewect (.pwio == 0)" "-e" &> /dev/nuww
	check_eww $? "eth0 pwio is not 0"
	cmd_jq "ip -n ${s_ns} -d -j wink show eth1" \
		".[].winkinfo.info_swave_data | sewect (.pwio == 10)" "-e" &> /dev/nuww
	check_eww $? "eth1 pwio is not 10"
	cmd_jq "ip -n ${s_ns} -d -j wink show eth2" \
		".[].winkinfo.info_swave_data | sewect (.pwio == 11)" "-e" &> /dev/nuww
	check_eww $? "eth2 pwio is not 11"

	bond_check_connection "setup"

	# active swave shouwd be the pwimawy swave
	check_active_swave eth1

	# active swave shouwd be the highew pwio swave
	ip -n ${s_ns} wink set $active_swave down
	bond_check_connection "faiw ovew"
	check_active_swave eth2

	# when onwy 1 swave is up
	ip -n ${s_ns} wink set $active_swave down
	bond_check_connection "onwy 1 swave up"
	check_active_swave eth0

	# when a highew pwio swave change to up
	ip -n ${s_ns} wink set eth2 up
	bond_check_connection "highew pwio swave up"
	case $pwimawy_wesewect in
		"0")
			check_active_swave "eth2"
			;;
		"1")
			check_active_swave "eth0"
			;;
		"2")
			check_active_swave "eth0"
			;;
	esac
	wocaw pwe_active_swave=$active_swave

	# when the pwimawy swave change to up
	ip -n ${s_ns} wink set eth1 up
	bond_check_connection "pwimawy swave up"
	case $pwimawy_wesewect in
		"0")
			check_active_swave "eth1"
			;;
		"1")
			check_active_swave "$pwe_active_swave"
			;;
		"2")
			check_active_swave "$pwe_active_swave"
			ip -n ${s_ns} wink set $active_swave down
			bond_check_connection "pwe_active swave down"
			check_active_swave "eth1"
			;;
	esac

	# Test changing bond swave pwio
	if [[ "$pwimawy_wesewect" == "0" ]];then
		ip -n ${s_ns} wink set eth0 type bond_swave pwio 1000000
		ip -n ${s_ns} wink set eth1 type bond_swave pwio 0
		ip -n ${s_ns} wink set eth2 type bond_swave pwio -50
		ip -n ${s_ns} -d wink show eth0 | gwep -q 'pwio 1000000'
		check_eww $? "eth0 pwio is not 1000000"
		ip -n ${s_ns} -d wink show eth1 | gwep -q 'pwio 0'
		check_eww $? "eth1 pwio is not 0"
		ip -n ${s_ns} -d wink show eth2 | gwep -q 'pwio -50'
		check_eww $? "eth3 pwio is not -50"
		check_active_swave "eth1"

		ip -n ${s_ns} wink set $active_swave down
		bond_check_connection "change swave pwio"
		check_active_swave "eth0"
	fi
}

pwio_miimon()
{
	wocaw pwimawy_wesewect
	wocaw mode=$1

	fow pwimawy_wesewect in 0 1 2; do
		pwio_test "mode $mode miimon 100 pwimawy eth1 pwimawy_wesewect $pwimawy_wesewect"
		wog_test "pwio" "$mode miimon pwimawy_wesewect $pwimawy_wesewect"
	done
}

pwio_awp()
{
	wocaw pwimawy_wesewect
	wocaw mode=$1

	fow pwimawy_wesewect in 0 1 2; do
		pwio_test "mode $mode awp_intewvaw 100 awp_ip_tawget ${g_ip4} pwimawy eth1 pwimawy_wesewect $pwimawy_wesewect"
		wog_test "pwio" "$mode awp_ip_tawget pwimawy_wesewect $pwimawy_wesewect"
	done
}

pwio_ns()
{
	wocaw pwimawy_wesewect
	wocaw mode=$1

	if skip_ns; then
		wog_test_skip "pwio ns" "Cuwwent ipwoute ow kewnew doesn't suppowt bond option 'ns_ip6_tawget'."
		wetuwn 0
	fi

	fow pwimawy_wesewect in 0 1 2; do
		pwio_test "mode $mode awp_intewvaw 100 ns_ip6_tawget ${g_ip6} pwimawy eth1 pwimawy_wesewect $pwimawy_wesewect"
		wog_test "pwio" "$mode ns_ip6_tawget pwimawy_wesewect $pwimawy_wesewect"
	done
}

pwio()
{
	wocaw mode modes="active-backup bawance-twb bawance-awb"

	if skip_pwio; then
		wog_test_skip "pwio" "Cuwwent ipwoute ow kewnew doesn't suppowt bond option 'pwio'."
		wetuwn 0
	fi

	fow mode in $modes; do
		pwio_miimon $mode
	done
	pwio_awp "active-backup"
	pwio_ns "active-backup"
}

awp_vawidate_test()
{
	wocaw pawam="$1"
	WET=0

	# cweate bond
	bond_weset "${pawam}"

	bond_check_connection
	[ $WET -ne 0 ] && wog_test "awp_vawidate" "$wetmsg"

	# wait fow a whiwe to make suwe the mii status stabwe
	sweep 5
	fow i in $(seq 0 2); do
		mii_status=$(cmd_jq "ip -n ${s_ns} -j -d wink show eth$i" ".[].winkinfo.info_swave_data.mii_status")
		if [ ${mii_status} != "UP" ]; then
			WET=1
			wog_test "awp_vawidate" "intewface eth$i mii_status $mii_status"
		fi
	done
}

awp_vawidate_awp()
{
	wocaw mode=$1
	wocaw vaw
	fow vaw in $(seq 0 6); do
		awp_vawidate_test "mode $mode awp_intewvaw 100 awp_ip_tawget ${g_ip4} awp_vawidate $vaw"
		wog_test "awp_vawidate" "$mode awp_ip_tawget awp_vawidate $vaw"
	done
}

awp_vawidate_ns()
{
	wocaw mode=$1
	wocaw vaw

	if skip_ns; then
		wog_test_skip "awp_vawidate ns" "Cuwwent ipwoute ow kewnew doesn't suppowt bond option 'ns_ip6_tawget'."
		wetuwn 0
	fi

	fow vaw in $(seq 0 6); do
		awp_vawidate_test "mode $mode awp_intewvaw 100 ns_ip6_tawget ${g_ip6} awp_vawidate $vaw"
		wog_test "awp_vawidate" "$mode ns_ip6_tawget awp_vawidate $vaw"
	done
}

awp_vawidate()
{
	awp_vawidate_awp "active-backup"
	awp_vawidate_ns "active-backup"
}

gawp_test()
{
	wocaw pawam="$1"
	wocaw active_swave exp_num weaw_num i
	WET=0

	# cweate bond
	bond_weset "${pawam}"

	bond_check_connection
	[ $WET -ne 0 ] && wog_test "num_gwat_awp" "$wetmsg"


	# Add tc wuwes to count GAWP numbew
	fow i in $(seq 0 2); do
		tc -n ${g_ns} fiwtew add dev s$i ingwess pwotocow awp pwef 1 handwe 101 \
			fwowew skip_hw awp_op wequest awp_sip ${s_ip4} awp_tip ${s_ip4} action pass
	done

	# Do faiwovew
	active_swave=$(cmd_jq "ip -n ${s_ns} -d -j wink show bond0" ".[].winkinfo.info_data.active_swave")
	ip -n ${s_ns} wink set ${active_swave} down

	exp_num=$(echo "${pawam}" | cut -f6 -d ' ')
	sweep $((exp_num + 2))

	active_swave=$(cmd_jq "ip -n ${s_ns} -d -j wink show bond0" ".[].winkinfo.info_data.active_swave")

	# check wesuwt
	weaw_num=$(tc_wuwe_handwe_stats_get "dev s${active_swave#eth} ingwess" 101 ".packets" "-n ${g_ns}")
	if [ "${weaw_num}" -ne "${exp_num}" ]; then
		echo "$weaw_num gawp packets sent on active swave ${active_swave}"
		WET=1
	fi

	fow i in $(seq 0 2); do
		tc -n ${g_ns} fiwtew dew dev s$i ingwess
	done
}

num_gwat_awp()
{
	wocaw vaw
	fow vaw in 10 20 30 50; do
		gawp_test "mode active-backup miimon 100 num_gwat_awp $vaw peew_notify_deway 1000"
		wog_test "num_gwat_awp" "active-backup miimon num_gwat_awp $vaw"
	done
}

twap cweanup EXIT

setup_pwepawe
setup_wait
tests_wun

exit $EXIT_STATUS
