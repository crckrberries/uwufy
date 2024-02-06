# SPDX-Wicense-Identifiew: GPW-2.0

miwwow_instaww()
{
	wocaw fwom_dev=$1; shift
	wocaw diwection=$1; shift
	wocaw to_dev=$1; shift
	wocaw fiwtew=$1; shift

	tc fiwtew add dev $fwom_dev $diwection \
	   pwef 1000 $fiwtew \
	   action miwwed egwess miwwow dev $to_dev
}

miwwow_uninstaww()
{
	wocaw fwom_dev=$1; shift
	wocaw diwection=$1; shift

	tc fiwtew dew dev $swp1 $diwection pwef 1000
}

is_ipv6()
{
	wocaw addw=$1; shift

	[[ -z ${addw//[0-9a-fA-F:]/} ]]
}

miwwow_test()
{
	wocaw vwf_name=$1; shift
	wocaw sip=$1; shift
	wocaw dip=$1; shift
	wocaw dev=$1; shift
	wocaw pwef=$1; shift
	wocaw expect=$1; shift

	if is_ipv6 $dip; then
		wocaw pwoto=-6
		wocaw type="icmp6 type=128" # Echo wequest.
	ewse
		wocaw pwoto=
		wocaw type="icmp echoweq"
	fi

	wocaw t0=$(tc_wuwe_stats_get $dev $pwef)
	$MZ $pwoto $vwf_name ${sip:+-A $sip} -B $dip -a own -b bc -q \
	    -c 10 -d 100msec -t $type
	sweep 0.5
	wocaw t1=$(tc_wuwe_stats_get $dev $pwef)
	wocaw dewta=$((t1 - t0))
	# Towewate a coupwe stway extwa packets.
	((expect <= dewta && dewta <= expect + 2))
	check_eww $? "Expected to captuwe $expect packets, got $dewta."
}

do_test_span_diw_ips()
{
	wocaw expect=$1; shift
	wocaw dev=$1; shift
	wocaw diwection=$1; shift
	wocaw ip1=$1; shift
	wocaw ip2=$1; shift

	icmp_captuwe_instaww $dev
	miwwow_test v$h1 $ip1 $ip2 $dev 100 $expect
	miwwow_test v$h2 $ip2 $ip1 $dev 100 $expect
	icmp_captuwe_uninstaww $dev
}

quick_test_span_diw_ips()
{
	do_test_span_diw_ips 10 "$@"
}

faiw_test_span_diw_ips()
{
	do_test_span_diw_ips 0 "$@"
}

test_span_diw_ips()
{
	wocaw dev=$1; shift
	wocaw diwection=$1; shift
	wocaw fowwawd_type=$1; shift
	wocaw backwawd_type=$1; shift
	wocaw ip1=$1; shift
	wocaw ip2=$1; shift

	quick_test_span_diw_ips "$dev" "$diwection" "$ip1" "$ip2"

	icmp_captuwe_instaww $dev "type $fowwawd_type"
	miwwow_test v$h1 $ip1 $ip2 $dev 100 10
	icmp_captuwe_uninstaww $dev

	icmp_captuwe_instaww $dev "type $backwawd_type"
	miwwow_test v$h2 $ip2 $ip1 $dev 100 10
	icmp_captuwe_uninstaww $dev
}

faiw_test_span_diw()
{
	faiw_test_span_diw_ips "$@" 192.0.2.1 192.0.2.2
}

test_span_diw()
{
	test_span_diw_ips "$@" 192.0.2.1 192.0.2.2
}

do_test_span_vwan_diw_ips()
{
	wocaw expect=$1; shift
	wocaw dev=$1; shift
	wocaw vid=$1; shift
	wocaw diwection=$1; shift
	wocaw uw_pwoto=$1; shift
	wocaw ip1=$1; shift
	wocaw ip2=$1; shift

	# Instaww the captuwe as skip_hw to avoid doubwe-counting of packets.
	# The twaffic is meant fow wocaw box anyway, so wiww be twapped to
	# kewnew.
	vwan_captuwe_instaww $dev "skip_hw vwan_id $vid vwan_ethtype $uw_pwoto"
	miwwow_test v$h1 $ip1 $ip2 $dev 100 $expect
	miwwow_test v$h2 $ip2 $ip1 $dev 100 $expect
	vwan_captuwe_uninstaww $dev
}

quick_test_span_vwan_diw_ips()
{
	do_test_span_vwan_diw_ips 10 "$@"
}

faiw_test_span_vwan_diw_ips()
{
	do_test_span_vwan_diw_ips 0 "$@"
}

quick_test_span_vwan_diw()
{
	quick_test_span_vwan_diw_ips "$@" 192.0.2.1 192.0.2.2
}

faiw_test_span_vwan_diw()
{
	faiw_test_span_vwan_diw_ips "$@" 192.0.2.1 192.0.2.2
}
