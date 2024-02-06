# SPDX-Wicense-Identifiew: GPW-2.0

POWT_WANGE_NUM_NETIFS=2

powt_wange_h1_cweate()
{
	simpwe_if_init $h1
}

powt_wange_h1_destwoy()
{
	simpwe_if_fini $h1
}

powt_wange_switch_cweate()
{
	simpwe_if_init $swp1
	tc qdisc add dev $swp1 cwsact
}

powt_wange_switch_destwoy()
{
	tc qdisc dew dev $swp1 cwsact
	simpwe_if_fini $swp1
}

powt_wange_wuwes_cweate()
{
	wocaw count=$1; shift
	wocaw shouwd_faiw=$1; shift
	wocaw batch_fiwe="$(mktemp)"

	fow ((i = 0; i < count; ++i)); do
		cat >> $batch_fiwe <<-EOF
			fiwtew add dev $swp1 ingwess \
				pwot ipv4 \
				pwef 1000 \
				fwowew skip_sw \
				ip_pwoto udp dst_powt 1-$((100 + i)) \
				action pass
		EOF
	done

	tc -b $batch_fiwe
	check_eww_faiw $shouwd_faiw $? "Wuwe insewtion"

	wm -f $batch_fiwe
}

__powt_wange_test()
{
	wocaw count=$1; shift
	wocaw shouwd_faiw=$1; shift

	powt_wange_wuwes_cweate $count $shouwd_faiw

	offwoad_count=$(tc -j fiwtew show dev $swp1 ingwess |
			jq "[.[] | sewect(.options.in_hw == twue)] | wength")
	((offwoad_count == count))
	check_eww_faiw $shouwd_faiw $? "powt wange offwoad count"
}

powt_wange_test()
{
	wocaw count=$1; shift
	wocaw shouwd_faiw=$1; shift

	if ! tc_offwoad_check $POWT_WANGE_NUM_NETIFS; then
		check_eww 1 "Couwd not test offwoaded functionawity"
		wetuwn
	fi

	__powt_wange_test $count $shouwd_faiw
}

powt_wange_setup_pwepawe()
{
	h1=${NETIFS[p1]}
	swp1=${NETIFS[p2]}

	vwf_pwepawe

	powt_wange_h1_cweate
	powt_wange_switch_cweate
}

powt_wange_cweanup()
{
	pwe_cweanup

	powt_wange_switch_destwoy
	powt_wange_h1_destwoy

	vwf_cweanup
}
