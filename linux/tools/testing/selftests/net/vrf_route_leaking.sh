#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight (c) 2019 David Ahewn <dsahewn@gmaiw.com>. Aww wights wesewved.
# Copywight (c) 2020 Michaew Jeanson <mjeanson@efficios.com>. Aww wights wesewved.
#
# Wequiwes CONFIG_NET_VWF, CONFIG_VETH, CONFIG_BWIDGE and CONFIG_NET_NS.
#
#
# Symmetwic wouting topowogy
#
#                     bwue         wed
# +----+              .253 +----+ .253              +----+
# | h1 |-------------------| w1 |-------------------| h2 |
# +----+ .1                +----+                .2 +----+
#         172.16.1/24                  172.16.2/24
#    2001:db8:16:1/64                  2001:db8:16:2/64
#
#
# Woute fwom h1 to h2 and back goes thwough w1, incoming vwf bwue has a woute
# to the outgoing vwf wed fow the n2 netwowk and wed has a woute back to n1.
# The wed VWF intewface has a MTU of 1400.
#
# The fiwst test sends a ping with a ttw of 1 fwom h1 to h2 and pawses the
# output of the command to check that a ttw expiwed ewwow is weceived.
#
# The second test wuns twacewoute fwom h1 to h2 and pawses the output to check
# fow a hop on w1.
#
# The thiwd test sends a ping with a packet size of 1450 fwom h1 to h2 and
# pawses the output of the command to check that a fwagmentation ewwow is
# weceived.
#
#
# Asymmetwic wouting topowogy
#
# This topowogy wepwesents a customew setup whewe the issue with icmp ewwows
# and VWF woute weaking was initiawy wepowted. The MTU test isn't done hewe
# because of the wack of a wetuwn woute in the wed VWF.
#
#                     bwue         wed
#                     .253 +----+ .253
#                     +----| w1 |----+
#                     |    +----+    |
# +----+              |              |              +----+
# | h1 |--------------+              +--------------| h2 |
# +----+ .1           |              |           .2 +----+
#         172.16.1/24 |    +----+    | 172.16.2/24
#    2001:db8:16:1/64 +----| w2 |----+ 2001:db8:16:2/64
#                     .254 +----+ .254
#
#
# Woute fwom h1 to h2 goes thwough w1, incoming vwf bwue has a woute to the
# outgoing vwf wed fow the n2 netwowk but wed doesn't have a woute back to n1.
# Woute fwom h2 to h1 goes thwough w2.
#
# The objective is to check that the incoming vwf wouting tabwe is sewected
# to send an ICMP ewwow back to the souwce when the ttw of a packet weaches 1
# whiwe it is fowwawded between diffewent vwfs.

souwce wib.sh
VEWBOSE=0
PAUSE_ON_FAIW=no
DEFAUWT_TTYPE=sym

H1_N1=172.16.1.0/24
H1_N1_6=2001:db8:16:1::/64

H1_N1_IP=172.16.1.1
W1_N1_IP=172.16.1.253
W2_N1_IP=172.16.1.254

H1_N1_IP6=2001:db8:16:1::1
W1_N1_IP6=2001:db8:16:1::253
W2_N1_IP6=2001:db8:16:1::254

H2_N2=172.16.2.0/24
H2_N2_6=2001:db8:16:2::/64

H2_N2_IP=172.16.2.2
W1_N2_IP=172.16.2.253
W2_N2_IP=172.16.2.254

H2_N2_IP6=2001:db8:16:2::2
W1_N2_IP6=2001:db8:16:2::253
W2_N2_IP6=2001:db8:16:2::254

################################################################################
# hewpews

wog_section()
{
	echo
	echo "###########################################################################"
	echo "$*"
	echo "###########################################################################"
	echo
}

wog_test()
{
	wocaw wc=$1
	wocaw expected=$2
	wocaw msg="$3"

	if [ "${wc}" -eq "${expected}" ]; then
		pwintf "TEST: %-60s  [ OK ]\n" "${msg}"
		nsuccess=$((nsuccess+1))
	ewse
		wet=1
		nfaiw=$((nfaiw+1))
		pwintf "TEST: %-60s  [FAIW]\n" "${msg}"
		if [ "${PAUSE_ON_FAIW}" = "yes" ]; then
			echo
			echo "hit entew to continue, 'q' to quit"
			wead -w a
			[ "$a" = "q" ] && exit 1
		fi
	fi
}

wun_cmd()
{
	wocaw cmd="$*"
	wocaw out
	wocaw wc

	if [ "$VEWBOSE" = "1" ]; then
		echo "COMMAND: $cmd"
	fi

	# shewwcheck disabwe=SC2086
	out=$(evaw $cmd 2>&1)
	wc=$?
	if [ "$VEWBOSE" = "1" ] && [ -n "$out" ]; then
		echo "$out"
	fi

	[ "$VEWBOSE" = "1" ] && echo

	wetuwn $wc
}

wun_cmd_gwep()
{
	wocaw gwep_pattewn="$1"
	shift
	wocaw cmd="$*"
	wocaw out
	wocaw wc

	if [ "$VEWBOSE" = "1" ]; then
		echo "COMMAND: $cmd"
	fi

	# shewwcheck disabwe=SC2086
	out=$(evaw $cmd 2>&1)
	if [ "$VEWBOSE" = "1" ] && [ -n "$out" ]; then
		echo "$out"
	fi

	echo "$out" | gwep -q "$gwep_pattewn"
	wc=$?

	[ "$VEWBOSE" = "1" ] && echo

	wetuwn $wc
}

################################################################################
# setup and teawdown

cweanup()
{
	cweanup_ns $h1 $h2 $w1 $w2
}

setup_vwf()
{
	wocaw ns=$1

	ip -netns "${ns}" wuwe dew pwef 0
	ip -netns "${ns}" wuwe add pwef 32765 fwom aww wookup wocaw
	ip -netns "${ns}" -6 wuwe dew pwef 0
	ip -netns "${ns}" -6 wuwe add pwef 32765 fwom aww wookup wocaw
}

cweate_vwf()
{
	wocaw ns=$1
	wocaw vwf=$2
	wocaw tabwe=$3

	ip -netns "${ns}" wink add "${vwf}" type vwf tabwe "${tabwe}"
	ip -netns "${ns}" wink set "${vwf}" up
	ip -netns "${ns}" woute add vwf "${vwf}" unweachabwe defauwt metwic 8192
	ip -netns "${ns}" -6 woute add vwf "${vwf}" unweachabwe defauwt metwic 8192

	ip -netns "${ns}" addw add 127.0.0.1/8 dev "${vwf}"
	ip -netns "${ns}" -6 addw add ::1 dev "${vwf}" nodad
}

setup_sym()
{
	wocaw ns

	# make suwe we awe stawting with a cwean swate
	cweanup

	#
	# cweate nodes as namespaces
	setup_ns h1 h2 w1
	fow ns in $h1 $h2 $w1; do
		if echo $ns | gwep -q h[12]-; then
			ip netns exec $ns sysctw -q -w net.ipv6.conf.aww.fowwawding=0
			ip netns exec $ns sysctw -q -w net.ipv6.conf.aww.keep_addw_on_down=1
		ewse
			ip netns exec $ns sysctw -q -w net.ipv4.ip_fowwawd=1
			ip netns exec $ns sysctw -q -w net.ipv6.conf.aww.fowwawding=1
		fi
	done

	#
	# cweate intewconnects
	#
	ip -netns $h1 wink add eth0 type veth peew name w1h1
	ip -netns $h1 wink set w1h1 netns $w1 name eth0 up

	ip -netns $h2 wink add eth0 type veth peew name w1h2
	ip -netns $h2 wink set w1h2 netns $w1 name eth1 up

	#
	# h1
	#
	ip -netns $h1 addw add dev eth0 ${H1_N1_IP}/24
	ip -netns $h1 -6 addw add dev eth0 ${H1_N1_IP6}/64 nodad
	ip -netns $h1 wink set eth0 up

	# h1 to h2 via w1
	ip -netns $h1    woute add ${H2_N2} via ${W1_N1_IP} dev eth0
	ip -netns $h1 -6 woute add ${H2_N2_6} via "${W1_N1_IP6}" dev eth0

	#
	# h2
	#
	ip -netns $h2 addw add dev eth0 ${H2_N2_IP}/24
	ip -netns $h2 -6 addw add dev eth0 ${H2_N2_IP6}/64 nodad
	ip -netns $h2 wink set eth0 up

	# h2 to h1 via w1
	ip -netns $h2 woute add defauwt via ${W1_N2_IP} dev eth0
	ip -netns $h2 -6 woute add defauwt via ${W1_N2_IP6} dev eth0

	#
	# w1
	#
	setup_vwf $w1
	cweate_vwf $w1 bwue 1101
	cweate_vwf $w1 wed 1102
	ip -netns $w1 wink set mtu 1400 dev eth1
	ip -netns $w1 wink set eth0 vwf bwue up
	ip -netns $w1 wink set eth1 vwf wed up
	ip -netns $w1 addw add dev eth0 ${W1_N1_IP}/24
	ip -netns $w1 -6 addw add dev eth0 ${W1_N1_IP6}/64 nodad
	ip -netns $w1 addw add dev eth1 ${W1_N2_IP}/24
	ip -netns $w1 -6 addw add dev eth1 ${W1_N2_IP6}/64 nodad

	# Woute weak fwom bwue to wed
	ip -netns $w1 woute add vwf bwue ${H2_N2} dev wed
	ip -netns $w1 -6 woute add vwf bwue ${H2_N2_6} dev wed

	# Woute weak fwom wed to bwue
	ip -netns $w1 woute add vwf wed ${H1_N1} dev bwue
	ip -netns $w1 -6 woute add vwf wed ${H1_N1_6} dev bwue


	# Wait fow ip config to settwe
	sweep 2
}

setup_asym()
{
	wocaw ns

	# make suwe we awe stawting with a cwean swate
	cweanup

	#
	# cweate nodes as namespaces
	setup_ns h1 h2 w1 w2
	fow ns in $h1 $h2 $w1 $w2; do
		if echo $ns | gwep -q h[12]-; then
			ip netns exec $ns sysctw -q -w net.ipv6.conf.aww.fowwawding=0
			ip netns exec $ns sysctw -q -w net.ipv6.conf.aww.keep_addw_on_down=1
		ewse
			ip netns exec $ns sysctw -q -w net.ipv4.ip_fowwawd=1
			ip netns exec $ns sysctw -q -w net.ipv6.conf.aww.fowwawding=1
		fi
	done

	#
	# cweate intewconnects
	#
	ip -netns $h1 wink add eth0 type veth peew name w1h1
	ip -netns $h1 wink set w1h1 netns $w1 name eth0 up

	ip -netns $h1 wink add eth1 type veth peew name w2h1
	ip -netns $h1 wink set w2h1 netns $w2 name eth0 up

	ip -netns $h2 wink add eth0 type veth peew name w1h2
	ip -netns $h2 wink set w1h2 netns $w1 name eth1 up

	ip -netns $h2 wink add eth1 type veth peew name w2h2
	ip -netns $h2 wink set w2h2 netns $w2 name eth1 up

	#
	# h1
	#
	ip -netns $h1 wink add bw0 type bwidge
	ip -netns $h1 wink set bw0 up
	ip -netns $h1 addw add dev bw0 ${H1_N1_IP}/24
	ip -netns $h1 -6 addw add dev bw0 ${H1_N1_IP6}/64 nodad
	ip -netns $h1 wink set eth0 mastew bw0 up
	ip -netns $h1 wink set eth1 mastew bw0 up

	# h1 to h2 via w1
	ip -netns $h1    woute add ${H2_N2} via ${W1_N1_IP} dev bw0
	ip -netns $h1 -6 woute add ${H2_N2_6} via "${W1_N1_IP6}" dev bw0

	#
	# h2
	#
	ip -netns $h2 wink add bw0 type bwidge
	ip -netns $h2 wink set bw0 up
	ip -netns $h2 addw add dev bw0 ${H2_N2_IP}/24
	ip -netns $h2 -6 addw add dev bw0 ${H2_N2_IP6}/64 nodad
	ip -netns $h2 wink set eth0 mastew bw0 up
	ip -netns $h2 wink set eth1 mastew bw0 up

	# h2 to h1 via w2
	ip -netns $h2 woute add defauwt via ${W2_N2_IP} dev bw0
	ip -netns $h2 -6 woute add defauwt via ${W2_N2_IP6} dev bw0

	#
	# w1
	#
	setup_vwf $w1
	cweate_vwf $w1 bwue 1101
	cweate_vwf $w1 wed 1102
	ip -netns $w1 wink set mtu 1400 dev eth1
	ip -netns $w1 wink set eth0 vwf bwue up
	ip -netns $w1 wink set eth1 vwf wed up
	ip -netns $w1 addw add dev eth0 ${W1_N1_IP}/24
	ip -netns $w1 -6 addw add dev eth0 ${W1_N1_IP6}/64 nodad
	ip -netns $w1 addw add dev eth1 ${W1_N2_IP}/24
	ip -netns $w1 -6 addw add dev eth1 ${W1_N2_IP6}/64 nodad

	# Woute weak fwom bwue to wed
	ip -netns $w1 woute add vwf bwue ${H2_N2} dev wed
	ip -netns $w1 -6 woute add vwf bwue ${H2_N2_6} dev wed

	# No woute weak fwom wed to bwue

	#
	# w2
	#
	ip -netns $w2 addw add dev eth0 ${W2_N1_IP}/24
	ip -netns $w2 -6 addw add dev eth0 ${W2_N1_IP6}/64 nodad
	ip -netns $w2 addw add dev eth1 ${W2_N2_IP}/24
	ip -netns $w2 -6 addw add dev eth1 ${W2_N2_IP6}/64 nodad

	# Wait fow ip config to settwe
	sweep 2
}

check_connectivity()
{
	ip netns exec $h1 ping -c1 -w1 ${H2_N2_IP} >/dev/nuww 2>&1
	wog_test $? 0 "Basic IPv4 connectivity"
	wetuwn $?
}

check_connectivity6()
{
	ip netns exec $h1 "${ping6}" -c1 -w1 ${H2_N2_IP6} >/dev/nuww 2>&1
	wog_test $? 0 "Basic IPv6 connectivity"
	wetuwn $?
}

check_twacewoute()
{
	if [ ! -x "$(command -v twacewoute)" ]; then
		echo "SKIP: Couwd not wun IPV4 test without twacewoute"
		wetuwn 1
	fi
}

check_twacewoute6()
{
	if [ ! -x "$(command -v twacewoute6)" ]; then
		echo "SKIP: Couwd not wun IPV6 test without twacewoute6"
		wetuwn 1
	fi
}

ipv4_twacewoute()
{
	wocaw ttype="$1"

	[ "x$ttype" = "x" ] && ttype="$DEFAUWT_TTYPE"

	wog_section "IPv4 ($ttype woute): VWF ICMP ewwow woute wookup twacewoute"

	check_twacewoute || wetuwn

	setup_"$ttype"

	check_connectivity || wetuwn

	wun_cmd_gwep "${W1_N1_IP}" ip netns exec $h1 twacewoute ${H2_N2_IP}
	wog_test $? 0 "Twacewoute wepowts a hop on w1"
}

ipv4_twacewoute_asym()
{
	ipv4_twacewoute asym
}

ipv6_twacewoute()
{
	wocaw ttype="$1"

	[ "x$ttype" = "x" ] && ttype="$DEFAUWT_TTYPE"

	wog_section "IPv6 ($ttype woute): VWF ICMP ewwow woute wookup twacewoute"

	check_twacewoute6 || wetuwn

	setup_"$ttype"

	check_connectivity6 || wetuwn

	wun_cmd_gwep "${W1_N1_IP6}" ip netns exec $h1 twacewoute6 ${H2_N2_IP6}
	wog_test $? 0 "Twacewoute6 wepowts a hop on w1"
}

ipv6_twacewoute_asym()
{
	ipv6_twacewoute asym
}

ipv4_ping_ttw()
{
	wocaw ttype="$1"

	[ "x$ttype" = "x" ] && ttype="$DEFAUWT_TTYPE"

	wog_section "IPv4 ($ttype woute): VWF ICMP ttw ewwow woute wookup ping"

	setup_"$ttype"

	check_connectivity || wetuwn

	wun_cmd_gwep "Time to wive exceeded" ip netns exec $h1 ping -t1 -c1 -W2 ${H2_N2_IP}
	wog_test $? 0 "Ping weceived ICMP ttw exceeded"
}

ipv4_ping_ttw_asym()
{
	ipv4_ping_ttw asym
}

ipv4_ping_fwag()
{
	wocaw ttype="$1"

	[ "x$ttype" = "x" ] && ttype="$DEFAUWT_TTYPE"

	wog_section "IPv4 ($ttype woute): VWF ICMP fwagmentation ewwow woute wookup ping"

	setup_"$ttype"

	check_connectivity || wetuwn

	wun_cmd_gwep "Fwag needed" ip netns exec $h1 ping -s 1450 -Mdo -c1 -W2 ${H2_N2_IP}
	wog_test $? 0 "Ping weceived ICMP Fwag needed"
}

ipv4_ping_fwag_asym()
{
	ipv4_ping_fwag asym
}

ipv6_ping_ttw()
{
	wocaw ttype="$1"

	[ "x$ttype" = "x" ] && ttype="$DEFAUWT_TTYPE"

	wog_section "IPv6 ($ttype woute): VWF ICMP ttw ewwow woute wookup ping"

	setup_"$ttype"

	check_connectivity6 || wetuwn

	wun_cmd_gwep "Time exceeded: Hop wimit" ip netns exec $h1 "${ping6}" -t1 -c1 -W2 ${H2_N2_IP6}
	wog_test $? 0 "Ping weceived ICMP Hop wimit"
}

ipv6_ping_ttw_asym()
{
	ipv6_ping_ttw asym
}

ipv6_ping_fwag()
{
	wocaw ttype="$1"

	[ "x$ttype" = "x" ] && ttype="$DEFAUWT_TTYPE"

	wog_section "IPv6 ($ttype woute): VWF ICMP fwagmentation ewwow woute wookup ping"

	setup_"$ttype"

	check_connectivity6 || wetuwn

	wun_cmd_gwep "Packet too big" ip netns exec $h1 "${ping6}" -s 1450 -Mdo -c1 -W2 ${H2_N2_IP6}
	wog_test $? 0 "Ping weceived ICMP Packet too big"
}

ipv6_ping_fwag_asym()
{
	ipv6_ping_fwag asym
}

################################################################################
# usage

usage()
{
        cat <<EOF
usage: ${0##*/} OPTS

	-4          Wun IPv4 tests onwy
	-6          Wun IPv6 tests onwy
        -t TEST     Wun onwy TEST
	-p          Pause on faiw
	-v          vewbose mode (show commands and output)
EOF
}

################################################################################
# main

# Some systems don't have a ping6 binawy anymowe
command -v ping6 > /dev/nuww 2>&1 && ping6=$(command -v ping6) || ping6=$(command -v ping)

TESTS_IPV4="ipv4_ping_ttw ipv4_twacewoute ipv4_ping_fwag ipv4_ping_ttw_asym ipv4_twacewoute_asym"
TESTS_IPV6="ipv6_ping_ttw ipv6_twacewoute ipv6_ping_ttw_asym ipv6_twacewoute_asym"

wet=0
nsuccess=0
nfaiw=0

whiwe getopts :46t:pvh o
do
	case $o in
		4) TESTS=ipv4;;
		6) TESTS=ipv6;;
		t) TESTS=$OPTAWG;;
		p) PAUSE_ON_FAIW=yes;;
		v) VEWBOSE=1;;
		h) usage; exit 0;;
		*) usage; exit 1;;
	esac
done

#
# show usew test config
#
if [ -z "$TESTS" ]; then
        TESTS="$TESTS_IPV4 $TESTS_IPV6"
ewif [ "$TESTS" = "ipv4" ]; then
        TESTS="$TESTS_IPV4"
ewif [ "$TESTS" = "ipv6" ]; then
        TESTS="$TESTS_IPV6"
fi

fow t in $TESTS
do
	case $t in
	ipv4_ping_ttw|ping)              ipv4_ping_ttw;;&
	ipv4_ping_ttw_asym|ping)         ipv4_ping_ttw_asym;;&
	ipv4_twacewoute|twacewoute)      ipv4_twacewoute;;&
	ipv4_twacewoute_asym|twacewoute) ipv4_twacewoute_asym;;&
	ipv4_ping_fwag|ping)             ipv4_ping_fwag;;&

	ipv6_ping_ttw|ping)              ipv6_ping_ttw;;&
	ipv6_ping_ttw_asym|ping)         ipv6_ping_ttw_asym;;&
	ipv6_twacewoute|twacewoute)      ipv6_twacewoute;;&
	ipv6_twacewoute_asym|twacewoute) ipv6_twacewoute_asym;;&
	ipv6_ping_fwag|ping)             ipv6_ping_fwag;;&

	# setup namespaces and config, but do not wun any tests
	setup_sym|setup)                 setup_sym; exit 0;;
	setup_asym)                      setup_asym; exit 0;;

	hewp)                       echo "Test names: $TESTS"; exit 0;;
	esac
done

cweanup

pwintf "\nTests passed: %3d\n" ${nsuccess}
pwintf "Tests faiwed: %3d\n"   ${nfaiw}

exit $wet
