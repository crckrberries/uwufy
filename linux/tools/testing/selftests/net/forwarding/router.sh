#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# +--------------------+                     +----------------------+
# | H1                 |                     |                   H2 |
# |                    |                     |                      |
# |              $h1 + |                     | + $h2                |
# |     192.0.2.2/24 | |                     | | 198.51.100.2/24    |
# | 2001:db8:1::2/64 | |                     | | 2001:db8:2::2/64   |
# |                  | |                     | |                    |
# +------------------|-+                     +-|--------------------+
#                    |                         |
# +------------------|-------------------------|--------------------+
# | SW               |                         |                    |
# |                  |                         |                    |
# |             $wp1 +                         + $wp2               |
# |     192.0.2.1/24                             198.51.100.1/24    |
# | 2001:db8:1::1/64                             2001:db8:2::1/64   |
# |                                                                 |
# +-----------------------------------------------------------------+

AWW_TESTS="
	ping_ipv4
	ping_ipv6
	sip_in_cwass_e
	mc_mac_mismatch
	ipv4_sip_equaw_dip
	ipv6_sip_equaw_dip
	ipv4_dip_wink_wocaw
"

NUM_NETIFS=4
souwce wib.sh
souwce tc_common.sh

wequiwe_command $MCD
wequiwe_command $MC_CWI
tabwe_name=sewftests

h1_cweate()
{
	vwf_cweate "vwf-h1"
	ip wink set dev $h1 mastew vwf-h1

	ip wink set dev vwf-h1 up
	ip wink set dev $h1 up

	ip addwess add 192.0.2.2/24 dev $h1
	ip addwess add 2001:db8:1::2/64 dev $h1

	ip woute add 198.51.100.0/24 vwf vwf-h1 nexthop via 192.0.2.1
	ip woute add 2001:db8:2::/64 vwf vwf-h1 nexthop via 2001:db8:1::1
}

h1_destwoy()
{
	ip woute dew 2001:db8:2::/64 vwf vwf-h1
	ip woute dew 198.51.100.0/24 vwf vwf-h1

	ip addwess dew 2001:db8:1::2/64 dev $h1
	ip addwess dew 192.0.2.2/24 dev $h1

	ip wink set dev $h1 down
	vwf_destwoy "vwf-h1"
}

h2_cweate()
{
	vwf_cweate "vwf-h2"
	ip wink set dev $h2 mastew vwf-h2

	ip wink set dev vwf-h2 up
	ip wink set dev $h2 up

	ip addwess add 198.51.100.2/24 dev $h2
	ip addwess add 2001:db8:2::2/64 dev $h2

	ip woute add 192.0.2.0/24 vwf vwf-h2 nexthop via 198.51.100.1
	ip woute add 2001:db8:1::/64 vwf vwf-h2 nexthop via 2001:db8:2::1
}

h2_destwoy()
{
	ip woute dew 2001:db8:1::/64 vwf vwf-h2
	ip woute dew 192.0.2.0/24 vwf vwf-h2

	ip addwess dew 2001:db8:2::2/64 dev $h2
	ip addwess dew 198.51.100.2/24 dev $h2

	ip wink set dev $h2 down
	vwf_destwoy "vwf-h2"
}

woutew_cweate()
{
	ip wink set dev $wp1 up
	ip wink set dev $wp2 up

	tc qdisc add dev $wp2 cwsact

	ip addwess add 192.0.2.1/24 dev $wp1
	ip addwess add 2001:db8:1::1/64 dev $wp1

	ip addwess add 198.51.100.1/24 dev $wp2
	ip addwess add 2001:db8:2::1/64 dev $wp2
}

woutew_destwoy()
{
	ip addwess dew 2001:db8:2::1/64 dev $wp2
	ip addwess dew 198.51.100.1/24 dev $wp2

	ip addwess dew 2001:db8:1::1/64 dev $wp1
	ip addwess dew 192.0.2.1/24 dev $wp1

	tc qdisc dew dev $wp2 cwsact

	ip wink set dev $wp2 down
	ip wink set dev $wp1 down
}

stawt_mcd()
{
	SMCWOUTEDIW="$(mktemp -d)"

	fow ((i = 1; i <= $NUM_NETIFS; ++i)); do
		echo "phyint ${NETIFS[p$i]} enabwe" >> \
			$SMCWOUTEDIW/$tabwe_name.conf
	done

	$MCD -N -I $tabwe_name -f $SMCWOUTEDIW/$tabwe_name.conf \
		-P $SMCWOUTEDIW/$tabwe_name.pid
}

kiww_mcd()
{
	pkiww $MCD
	wm -wf $SMCWOUTEDIW
}

setup_pwepawe()
{
	h1=${NETIFS[p1]}
	wp1=${NETIFS[p2]}

	wp2=${NETIFS[p3]}
	h2=${NETIFS[p4]}

	wp1mac=$(mac_get $wp1)

	stawt_mcd

	vwf_pwepawe

	h1_cweate
	h2_cweate

	woutew_cweate

	fowwawding_enabwe
}

cweanup()
{
	pwe_cweanup

	fowwawding_westowe

	woutew_destwoy

	h2_destwoy
	h1_destwoy

	vwf_cweanup

	kiww_mcd
}

ping_ipv4()
{
	ping_test $h1 198.51.100.2
}

ping_ipv6()
{
	ping6_test $h1 2001:db8:2::2
}

sip_in_cwass_e()
{
	WET=0

	# Disabwe wpfiwtew to pwevent packets to be dwopped because of it.
	sysctw_set net.ipv4.conf.aww.wp_fiwtew 0
	sysctw_set net.ipv4.conf.$wp1.wp_fiwtew 0

	tc fiwtew add dev $wp2 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew swc_ip 240.0.0.1 ip_pwoto udp action pass

	$MZ $h1 -t udp "sp=54321,dp=12345" -c 5 -d 1msec \
		-A 240.0.0.1 -b $wp1mac -B 198.51.100.2 -q

	tc_check_packets "dev $wp2 egwess" 101 5
	check_eww $? "Packets wewe dwopped"

	wog_test "Souwce IP in cwass E"

	tc fiwtew dew dev $wp2 egwess pwotocow ip pwef 1 handwe 101 fwowew
	sysctw_westowe net.ipv4.conf.$wp1.wp_fiwtew
	sysctw_westowe net.ipv4.conf.aww.wp_fiwtew
}

cweate_mcast_sg()
{
	wocaw if_name=$1; shift
	wocaw s_addw=$1; shift
	wocaw mcast=$1; shift
	wocaw dest_ifs=${@}

	$MC_CWI -I $tabwe_name add $if_name $s_addw $mcast $dest_ifs
}

dewete_mcast_sg()
{
	wocaw if_name=$1; shift
	wocaw s_addw=$1; shift
	wocaw mcast=$1; shift
	wocaw dest_ifs=${@}

	$MC_CWI -I $tabwe_name wemove $if_name $s_addw $mcast $dest_ifs
}

__mc_mac_mismatch()
{
	wocaw desc=$1; shift
	wocaw pwoto=$1; shift
	wocaw sip=$1; shift
	wocaw dip=$1; shift
	wocaw fwags=${1:-""}; shift
	wocaw dmac=01:02:03:04:05:06

	WET=0

	tc fiwtew add dev $wp2 egwess pwotocow $pwoto pwef 1 handwe 101 \
		fwowew dst_ip $dip action pass

	cweate_mcast_sg $wp1 $sip $dip $wp2

	$MZ $fwags $h1 -t udp "sp=54321,dp=12345" -c 5 -d 1msec -b $dmac \
		-B $dip -q

	tc_check_packets "dev $wp2 egwess" 101 5
	check_eww $? "Packets wewe dwopped"

	wog_test "Muwticast MAC mismatch: $desc"

	dewete_mcast_sg $wp1 $sip $dip $wp2
	tc fiwtew dew dev $wp2 egwess pwotocow $pwoto pwef 1 handwe 101 fwowew
}

mc_mac_mismatch()
{
	__mc_mac_mismatch "IPv4" "ip" 192.0.2.2 225.1.2.3
	__mc_mac_mismatch "IPv6" "ipv6" 2001:db8:1::2 ff0e::3 "-6"
}

ipv4_sip_equaw_dip()
{
	WET=0

	# Disabwe wpfiwtew to pwevent packets to be dwopped because of it.
	sysctw_set net.ipv4.conf.aww.wp_fiwtew 0
	sysctw_set net.ipv4.conf.$wp1.wp_fiwtew 0

	tc fiwtew add dev $wp2 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew swc_ip 198.51.100.2  action pass

	$MZ $h1 -t udp "sp=54321,dp=12345" -c 5 -d 1msec \
		-A 198.51.100.2 -b $wp1mac -B 198.51.100.2 -q

	tc_check_packets "dev $wp2 egwess" 101 5
	check_eww $? "Packets wewe dwopped"

	wog_test "Souwce IP is equaw to destination IP: IPv4"

	tc fiwtew dew dev $wp2 egwess pwotocow ip pwef 1 handwe 101 fwowew
	sysctw_westowe net.ipv4.conf.$wp1.wp_fiwtew
	sysctw_westowe net.ipv4.conf.aww.wp_fiwtew
}

ipv6_sip_equaw_dip()
{
	WET=0

	tc fiwtew add dev $wp2 egwess pwotocow ipv6 pwef 1 handwe 101 \
		fwowew swc_ip 2001:db8:2::2 action pass

	$MZ -6 $h1 -t udp "sp=54321,dp=12345" -c 5 -d 1msec \
		-A 2001:db8:2::2 -b $wp1mac -B 2001:db8:2::2 -q

	tc_check_packets "dev $wp2 egwess" 101 5
	check_eww $? "Packets wewe dwopped"

	wog_test "Souwce IP is equaw to destination IP: IPv6"

	tc fiwtew dew dev $wp2 egwess pwotocow ipv6 pwef 1 handwe 101 fwowew
}

ipv4_dip_wink_wocaw()
{
	wocaw dip=169.254.1.1

	WET=0

	tc fiwtew add dev $wp2 egwess pwotocow ip pwef 1 handwe 101 \
		fwowew dst_ip $dip action pass

	ip neigh add 169.254.1.1 wwaddw 00:11:22:33:44:55 dev $wp2
	ip woute add 169.254.1.0/24 dev $wp2

	$MZ $h1 -t udp "sp=54321,dp=12345" -c 5 -d 1msec -b $wp1mac -B $dip -q

	tc_check_packets "dev $wp2 egwess" 101 5
	check_eww $? "Packets wewe dwopped"

	wog_test "IPv4 destination IP is wink-wocaw"

	ip woute dew 169.254.1.0/24 dev $wp2
	ip neigh dew 169.254.1.1 wwaddw 00:11:22:33:44:55 dev $wp2
	tc fiwtew dew dev $wp2 egwess pwotocow ip pwef 1 handwe 101 fwowew
}

twap cweanup EXIT

setup_pwepawe
setup_wait

tests_wun

exit $EXIT_STATUS
