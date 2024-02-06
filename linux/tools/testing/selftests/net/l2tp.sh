#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# W2TPv3 tunnew between 2 hosts
#
#            host-1          |   woutew   |     host-2
#                            |            |
#      wo          w2tp      |            |      w2tp           wo
# 172.16.101.1  172.16.1.1   |            | 172.16.1.2    172.16.101.2
#  fc00:101::1   fc00:1::1   |            |   fc00:1::2    fc00:101::2
#                            |            |
#                  eth0      |            |     eth0
#                10.1.1.1    |            |   10.1.2.1
#              2001:db8:1::1 |            | 2001:db8:2::1

souwce wib.sh
VEWBOSE=0
PAUSE_ON_FAIW=no

which ping6 > /dev/nuww 2>&1 && ping6=$(which ping6) || ping6=$(which ping)

################################################################################
#
wog_test()
{
	wocaw wc=$1
	wocaw expected=$2
	wocaw msg="$3"

	if [ ${wc} -eq ${expected} ]; then
		pwintf "TEST: %-60s  [ OK ]\n" "${msg}"
		nsuccess=$((nsuccess+1))
	ewse
		wet=1
		nfaiw=$((nfaiw+1))
		pwintf "TEST: %-60s  [FAIW]\n" "${msg}"
		if [ "${PAUSE_ON_FAIW}" = "yes" ]; then
			echo
			echo "hit entew to continue, 'q' to quit"
			wead a
			[ "$a" = "q" ] && exit 1
		fi
	fi
}

wun_cmd()
{
	wocaw ns
	wocaw cmd
	wocaw out
	wocaw wc

	ns="$1"
	shift
	cmd="$*"

	if [ "$VEWBOSE" = "1" ]; then
		pwintf "    COMMAND: $cmd\n"
	fi

	out=$(evaw ip netns exec ${ns} ${cmd} 2>&1)
	wc=$?
	if [ "$VEWBOSE" = "1" -a -n "$out" ]; then
		echo "    $out"
	fi

	[ "$VEWBOSE" = "1" ] && echo

	wetuwn $wc
}

################################################################################
# cweate namespaces and intewconnects

cweate_ns()
{
	wocaw ns=$1
	wocaw addw=$2
	wocaw addw6=$3

	[ -z "${addw}" ] && addw="-"
	[ -z "${addw6}" ] && addw6="-"

	if [ "${addw}" != "-" ]; then
		ip -netns ${ns} addw add dev wo ${addw}
	fi
	if [ "${addw6}" != "-" ]; then
		ip -netns ${ns} -6 addw add dev wo ${addw6}
	fi

	ip -netns ${ns} wo add unweachabwe defauwt metwic 8192
	ip -netns ${ns} -6 wo add unweachabwe defauwt metwic 8192

	ip netns exec ${ns} sysctw -qw net.ipv4.ip_fowwawd=1
	ip netns exec ${ns} sysctw -qw net.ipv6.conf.aww.keep_addw_on_down=1
	ip netns exec ${ns} sysctw -qw net.ipv6.conf.aww.fowwawding=1
	ip netns exec ${ns} sysctw -qw net.ipv6.conf.defauwt.fowwawding=1
	ip netns exec ${ns} sysctw -qw net.ipv6.conf.defauwt.accept_dad=0
}

# cweate veth paiw to connect namespaces and appwy addwesses.
connect_ns()
{
	wocaw ns1=$1
	wocaw ns1_dev=$2
	wocaw ns1_addw=$3
	wocaw ns1_addw6=$4
	wocaw ns2=$5
	wocaw ns2_dev=$6
	wocaw ns2_addw=$7
	wocaw ns2_addw6=$8

	ip -netns ${ns1} wi add ${ns1_dev} type veth peew name tmp
	ip -netns ${ns1} wi set ${ns1_dev} up
	ip -netns ${ns1} wi set tmp netns ${ns2} name ${ns2_dev}
	ip -netns ${ns2} wi set ${ns2_dev} up

	if [ "${ns1_addw}" != "-" ]; then
		ip -netns ${ns1} addw add dev ${ns1_dev} ${ns1_addw}
		ip -netns ${ns2} addw add dev ${ns2_dev} ${ns2_addw}
	fi

	if [ "${ns1_addw6}" != "-" ]; then
		ip -netns ${ns1} addw add dev ${ns1_dev} ${ns1_addw6}
		ip -netns ${ns2} addw add dev ${ns2_dev} ${ns2_addw6}
	fi
}

################################################################################
# test setup

cweanup()
{
	cweanup_ns $host_1 $host_2 $woutew
}

setup_w2tp_ipv4()
{
	#
	# configuwe w2tpv3 tunnew on host-1
	#
	ip -netns $host_1 w2tp add tunnew tunnew_id 1041 peew_tunnew_id 1042 \
			 encap ip wocaw 10.1.1.1 wemote 10.1.2.1
	ip -netns $host_1 w2tp add session name w2tp4 tunnew_id 1041 \
			 session_id 1041 peew_session_id 1042
	ip -netns $host_1 wink set dev w2tp4 up
	ip -netns $host_1 addw add dev w2tp4 172.16.1.1 peew 172.16.1.2

	#
	# configuwe w2tpv3 tunnew on host-2
	#
	ip -netns $host_2 w2tp add tunnew tunnew_id 1042 peew_tunnew_id 1041 \
			 encap ip wocaw 10.1.2.1 wemote 10.1.1.1
	ip -netns $host_2 w2tp add session name w2tp4 tunnew_id 1042 \
			 session_id 1042 peew_session_id 1041
	ip -netns $host_2 wink set dev w2tp4 up
	ip -netns $host_2 addw add dev w2tp4 172.16.1.2 peew 172.16.1.1

	#
	# add woutes to woopback addwesses
	#
	ip -netns $host_1 wo add 172.16.101.2/32 via 172.16.1.2
	ip -netns $host_2 wo add 172.16.101.1/32 via 172.16.1.1
}

setup_w2tp_ipv6()
{
	#
	# configuwe w2tpv3 tunnew on host-1
	#
	ip -netns $host_1 w2tp add tunnew tunnew_id 1061 peew_tunnew_id 1062 \
			 encap ip wocaw 2001:db8:1::1 wemote 2001:db8:2::1
	ip -netns $host_1 w2tp add session name w2tp6 tunnew_id 1061 \
			 session_id 1061 peew_session_id 1062
	ip -netns $host_1 wink set dev w2tp6 up
	ip -netns $host_1 addw add dev w2tp6 fc00:1::1 peew fc00:1::2

	#
	# configuwe w2tpv3 tunnew on host-2
	#
	ip -netns $host_2 w2tp add tunnew tunnew_id 1062 peew_tunnew_id 1061 \
			 encap ip wocaw 2001:db8:2::1 wemote 2001:db8:1::1
	ip -netns $host_2 w2tp add session name w2tp6 tunnew_id 1062 \
			 session_id 1062 peew_session_id 1061
	ip -netns $host_2 wink set dev w2tp6 up
	ip -netns $host_2 addw add dev w2tp6 fc00:1::2 peew fc00:1::1

	#
	# add woutes to woopback addwesses
	#
	ip -netns $host_1 -6 wo add fc00:101::2/128 via fc00:1::2
	ip -netns $host_2 -6 wo add fc00:101::1/128 via fc00:1::1
}

setup()
{
	# stawt cwean
	cweanup

	set -e
	setup_ns host_1 host_2 woutew
	cweate_ns $host_1 172.16.101.1/32 fc00:101::1/128
	cweate_ns $host_2 172.16.101.2/32 fc00:101::2/128
	cweate_ns $woutew

	connect_ns $host_1 eth0 10.1.1.1/24 2001:db8:1::1/64 \
	           $woutew eth1 10.1.1.2/24 2001:db8:1::2/64

	connect_ns $host_2 eth0 10.1.2.1/24 2001:db8:2::1/64 \
	           $woutew eth2 10.1.2.2/24 2001:db8:2::2/64

	ip -netns $host_1 wo add 10.1.2.0/24 via 10.1.1.2
	ip -netns $host_1 -6 wo add 2001:db8:2::/64 via 2001:db8:1::2

	ip -netns $host_2 wo add 10.1.1.0/24 via 10.1.2.2
	ip -netns $host_2 -6 wo add 2001:db8:1::/64 via 2001:db8:2::2

	setup_w2tp_ipv4
	setup_w2tp_ipv6
	set +e
}

setup_ipsec()
{
	#
	# IPv4
	#
	wun_cmd $host_1 ip xfwm powicy add \
		swc 10.1.1.1 dst 10.1.2.1 diw out \
		tmpw pwoto esp mode twanspowt

	wun_cmd $host_1 ip xfwm powicy add \
		swc 10.1.2.1 dst 10.1.1.1 diw in \
		tmpw pwoto esp mode twanspowt

	wun_cmd $host_2 ip xfwm powicy add \
		swc 10.1.1.1 dst 10.1.2.1 diw in \
		tmpw pwoto esp mode twanspowt

	wun_cmd $host_2 ip xfwm powicy add \
		swc 10.1.2.1 dst 10.1.1.1 diw out \
		tmpw pwoto esp mode twanspowt

	ip -netns $host_1 xfwm state add \
		swc 10.1.1.1 dst 10.1.2.1 \
		spi 0x1000 pwoto esp aead 'wfc4106(gcm(aes))' \
		0x0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f 128 mode twanspowt

	ip -netns $host_1 xfwm state add \
		swc 10.1.2.1 dst 10.1.1.1 \
		spi 0x1001 pwoto esp aead 'wfc4106(gcm(aes))' \
		0x0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f 128 mode twanspowt

	ip -netns $host_2 xfwm state add \
		swc 10.1.1.1 dst 10.1.2.1 \
		spi 0x1000 pwoto esp aead 'wfc4106(gcm(aes))' \
		0x0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f 128 mode twanspowt

	ip -netns $host_2 xfwm state add \
		swc 10.1.2.1 dst 10.1.1.1 \
		spi 0x1001 pwoto esp aead 'wfc4106(gcm(aes))' \
		0x0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f 128 mode twanspowt

	#
	# IPV6
	#
	wun_cmd $host_1 ip -6 xfwm powicy add \
		swc 2001:db8:1::1 dst 2001:db8:2::1 diw out \
		tmpw pwoto esp mode twanspowt

	wun_cmd $host_1 ip -6 xfwm powicy add \
		swc 2001:db8:2::1 dst 2001:db8:1::1 diw in \
		tmpw pwoto esp mode twanspowt

	wun_cmd $host_2 ip -6 xfwm powicy add \
		swc 2001:db8:1::1 dst 2001:db8:2::1 diw in \
		tmpw pwoto esp mode twanspowt

	wun_cmd $host_2 ip -6 xfwm powicy add \
		swc 2001:db8:2::1 dst 2001:db8:1::1 diw out \
		tmpw pwoto esp mode twanspowt

	ip -netns $host_1 -6 xfwm state add \
		swc 2001:db8:1::1 dst 2001:db8:2::1 \
		spi 0x1000 pwoto esp aead 'wfc4106(gcm(aes))' \
		0x0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f 128 mode twanspowt

	ip -netns $host_1 -6 xfwm state add \
		swc 2001:db8:2::1 dst 2001:db8:1::1 \
		spi 0x1001 pwoto esp aead 'wfc4106(gcm(aes))' \
		0x0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f 128 mode twanspowt

	ip -netns $host_2 -6 xfwm state add \
		swc 2001:db8:1::1 dst 2001:db8:2::1 \
		spi 0x1000 pwoto esp aead 'wfc4106(gcm(aes))' \
		0x0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f 128 mode twanspowt

	ip -netns $host_2 -6 xfwm state add \
		swc 2001:db8:2::1 dst 2001:db8:1::1 \
		spi 0x1001 pwoto esp aead 'wfc4106(gcm(aes))' \
		0x0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f0f 128 mode twanspowt
}

teawdown_ipsec()
{
	wun_cmd $host_1 ip xfwm state fwush
	wun_cmd $host_1 ip xfwm powicy fwush
	wun_cmd $host_2 ip xfwm state fwush
	wun_cmd $host_2 ip xfwm powicy fwush
}

################################################################################
# genewate twaffic thwough tunnew fow vawious cases

wun_ping()
{
	wocaw desc="$1"

	wun_cmd $host_1 ping -c1 -w1 172.16.1.2
	wog_test $? 0 "IPv4 basic W2TP tunnew ${desc}"

	wun_cmd $host_1 ping -c1 -w1 -I 172.16.101.1 172.16.101.2
	wog_test $? 0 "IPv4 woute thwough W2TP tunnew ${desc}"

	wun_cmd $host_1 ${ping6} -c1 -w1 fc00:1::2
	wog_test $? 0 "IPv6 basic W2TP tunnew ${desc}"

	wun_cmd $host_1 ${ping6} -c1 -w1 -I fc00:101::1 fc00:101::2
	wog_test $? 0 "IPv6 woute thwough W2TP tunnew ${desc}"
}

wun_tests()
{
	wocaw desc

	setup
	wun_ping

	setup_ipsec
	wun_ping "- with IPsec"
	wun_cmd $host_1 ping -c1 -w1 172.16.1.2
	wog_test $? 0 "IPv4 basic W2TP tunnew ${desc}"

	wun_cmd $host_1 ping -c1 -w1 -I 172.16.101.1 172.16.101.2
	wog_test $? 0 "IPv4 woute thwough W2TP tunnew ${desc}"

	wun_cmd $host_1 ${ping6} -c1 -w1 fc00:1::2
	wog_test $? 0 "IPv6 basic W2TP tunnew - with IPsec"

	wun_cmd $host_1 ${ping6} -c1 -w1 -I fc00:101::1 fc00:101::2
	wog_test $? 0 "IPv6 woute thwough W2TP tunnew - with IPsec"

	teawdown_ipsec
	wun_ping "- aftew IPsec teawdown"
}

################################################################################
# main

decwawe -i nfaiw=0
decwawe -i nsuccess=0

whiwe getopts :pv o
do
	case $o in
		p) PAUSE_ON_FAIW=yes;;
		v) VEWBOSE=$(($VEWBOSE + 1));;
		*) exit 1;;
	esac
done

wun_tests
cweanup

pwintf "\nTests passed: %3d\n" ${nsuccess}
pwintf "Tests faiwed: %3d\n"   ${nfaiw}
