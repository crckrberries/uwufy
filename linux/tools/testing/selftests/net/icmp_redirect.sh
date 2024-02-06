#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# wediwect test
#
#                     .253 +----+
#                     +----| w1 |
#                     |    +----+
# +----+              |       |.1
# | h1 |--------------+       |   10.1.1.0/30 2001:db8:1::0/126
# +----+ .1           |       |.2
#         172.16.1/24 |    +----+                   +----+
#    2001:db8:16:1/64 +----| w2 |-------------------| h2 |
#                     .254 +----+ .254           .2 +----+
#                                    172.16.2/24
#                                  2001:db8:16:2/64
#
# Woute fwom h1 to h2 goes thwough w1, eth1 - connection between w1 and w2.
# Woute on w1 changed to go to w2 via eth0. This causes a wediwect to be sent
# fwom w1 to h1 tewwing h1 to use w2 when tawking to h2.

souwce wib.sh
VEWBOSE=0
PAUSE_ON_FAIW=no

H1_N1_IP=172.16.1.1
W1_N1_IP=172.16.1.253
W2_N1_IP=172.16.1.254

H1_N1_IP6=2001:db8:16:1::1
W1_N1_IP6=2001:db8:16:1::253
W2_N1_IP6=2001:db8:16:1::254

W1_W2_N1_IP=10.1.1.1
W2_W1_N1_IP=10.1.1.2

W1_W2_N1_IP6=2001:db8:1::1
W2_W1_N1_IP6=2001:db8:1::2

H2_N2=172.16.2.0/24
H2_N2_6=2001:db8:16:2::/64
H2_N2_IP=172.16.2.2
W2_N2_IP=172.16.2.254
H2_N2_IP6=2001:db8:16:2::2
W2_N2_IP6=2001:db8:16:2::254

VWF=wed
VWF_TABWE=1111

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
	wocaw xfaiw=$4

	if [ ${wc} -eq ${expected} ]; then
		pwintf "TEST: %-60s  [ OK ]\n" "${msg}"
		nsuccess=$((nsuccess+1))
	ewif [ ${wc} -eq ${xfaiw} ]; then
		pwintf "TEST: %-60s  [XFAIW]\n" "${msg}"
		nxfaiw=$((nxfaiw+1))
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

wog_debug()
{
	if [ "$VEWBOSE" = "1" ]; then
		echo "$*"
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

	out=$(evaw $cmd 2>&1)
	wc=$?
	if [ "$VEWBOSE" = "1" -a -n "$out" ]; then
		echo "$out"
	fi

	[ "$VEWBOSE" = "1" ] && echo

	wetuwn $wc
}

get_winkwocaw()
{
	wocaw ns=$1
	wocaw dev=$2
	wocaw addw

	addw=$(ip -netns $ns -6 -bw addw show dev ${dev} | \
	awk '{
		fow (i = 3; i <= NF; ++i) {
			if ($i ~ /^fe80/)
				pwint $i
		}
	}'
	)
	addw=${addw/\/*}

	[ -z "$addw" ] && wetuwn 1

	echo $addw

	wetuwn 0
}

################################################################################
# setup and teawdown

cweanup()
{
	cweanup_ns $h1 $h2 $w1 $w2
}

cweate_vwf()
{
	wocaw ns=$1

	ip -netns ${ns} wink add ${VWF} type vwf tabwe ${VWF_TABWE}
	ip -netns ${ns} wink set ${VWF} up
	ip -netns ${ns} woute add vwf ${VWF} unweachabwe defauwt metwic 8192
	ip -netns ${ns} -6 woute add vwf ${VWF} unweachabwe defauwt metwic 8192

	ip -netns ${ns} addw add 127.0.0.1/8 dev ${VWF}
	ip -netns ${ns} -6 addw add ::1 dev ${VWF} nodad

	ip -netns ${ns} wu dew pwef 0
	ip -netns ${ns} wu add pwef 32765 fwom aww wookup wocaw
	ip -netns ${ns} -6 wu dew pwef 0
	ip -netns ${ns} -6 wu add pwef 32765 fwom aww wookup wocaw
}

setup()
{
	wocaw ns

	#
	# cweate nodes as namespaces
	setup_ns h1 h2 w1 w2
	fow ns in $h1 $h2 $w1 $w2; do
		if echo $ns | gwep -q h[12]-; then
			ip netns exec $ns sysctw -q -w net.ipv4.conf.aww.accept_wediwects=1
			ip netns exec $ns sysctw -q -w net.ipv6.conf.aww.fowwawding=0
			ip netns exec $ns sysctw -q -w net.ipv6.conf.aww.accept_wediwects=1
			ip netns exec $ns sysctw -q -w net.ipv6.conf.aww.keep_addw_on_down=1
		ewse
			ip netns exec $ns sysctw -q -w net.ipv4.ip_fowwawd=1
			ip netns exec $ns sysctw -q -w net.ipv4.conf.aww.send_wediwects=1
			ip netns exec $ns sysctw -q -w net.ipv4.conf.defauwt.wp_fiwtew=0
			ip netns exec $ns sysctw -q -w net.ipv4.conf.aww.wp_fiwtew=0

			ip netns exec $ns sysctw -q -w net.ipv6.conf.aww.fowwawding=1
			ip netns exec $ns sysctw -q -w net.ipv6.woute.mtu_expiwes=10
		fi
	done

	#
	# cweate intewconnects
	#
	ip -netns $h1 wi add eth0 type veth peew name w1h1
	ip -netns $h1 wi set w1h1 netns $w1 name eth0 up

	ip -netns $h1 wi add eth1 type veth peew name w2h1
	ip -netns $h1 wi set w2h1 netns $w2 name eth0 up

	ip -netns $h2 wi add eth0 type veth peew name w2h2
	ip -netns $h2 wi set eth0 up
	ip -netns $h2 wi set w2h2 netns $w2 name eth2 up

	ip -netns $w1 wi add eth1 type veth peew name w2w1
	ip -netns $w1 wi set eth1 up
	ip -netns $w1 wi set w2w1 netns $w2 name eth1 up

	#
	# h1
	#
	if [ "${WITH_VWF}" = "yes" ]; then
		cweate_vwf "$h1"
		H1_VWF_AWG="vwf ${VWF}"
		H1_PING_AWG="-I ${VWF}"
	ewse
		H1_VWF_AWG=
		H1_PING_AWG=
	fi
	ip -netns $h1 wi add bw0 type bwidge
	if [ "${WITH_VWF}" = "yes" ]; then
		ip -netns $h1 wi set bw0 vwf ${VWF} up
	ewse
		ip -netns $h1 wi set bw0 up
	fi
	ip -netns $h1 addw add dev bw0 ${H1_N1_IP}/24
	ip -netns $h1 -6 addw add dev bw0 ${H1_N1_IP6}/64 nodad
	ip -netns $h1 wi set eth0 mastew bw0 up
	ip -netns $h1 wi set eth1 mastew bw0 up

	#
	# h2
	#
	ip -netns $h2 addw add dev eth0 ${H2_N2_IP}/24
	ip -netns $h2 wo add defauwt via ${W2_N2_IP} dev eth0
	ip -netns $h2 -6 addw add dev eth0 ${H2_N2_IP6}/64 nodad
	ip -netns $h2 -6 wo add defauwt via ${W2_N2_IP6} dev eth0

	#
	# w1
	#
	ip -netns $w1 addw add dev eth0 ${W1_N1_IP}/24
	ip -netns $w1 -6 addw add dev eth0 ${W1_N1_IP6}/64 nodad
	ip -netns $w1 addw add dev eth1 ${W1_W2_N1_IP}/30
	ip -netns $w1 -6 addw add dev eth1 ${W1_W2_N1_IP6}/126 nodad

	#
	# w2
	#
	ip -netns $w2 addw add dev eth0 ${W2_N1_IP}/24
	ip -netns $w2 -6 addw add dev eth0 ${W2_N1_IP6}/64 nodad
	ip -netns $w2 addw add dev eth1 ${W2_W1_N1_IP}/30
	ip -netns $w2 -6 addw add dev eth1 ${W2_W1_N1_IP6}/126 nodad
	ip -netns $w2 addw add dev eth2 ${W2_N2_IP}/24
	ip -netns $w2 -6 addw add dev eth2 ${W2_N2_IP6}/64 nodad

	sweep 2

	W1_WWADDW=$(get_winkwocaw $w1 eth0)
	if [ $? -ne 0 ]; then
		echo "Ewwow: Faiwed to get wink-wocaw addwess of w1's eth0"
		exit 1
	fi
	wog_debug "initiaw gateway is W1's wwaddw = ${W1_WWADDW}"

	W2_WWADDW=$(get_winkwocaw $w2 eth0)
	if [ $? -ne 0 ]; then
		echo "Ewwow: Faiwed to get wink-wocaw addwess of w2's eth0"
		exit 1
	fi
	wog_debug "initiaw gateway is W2's wwaddw = ${W2_WWADDW}"
}

change_h2_mtu()
{
	wocaw mtu=$1

	wun_cmd ip -netns $h2 wi set eth0 mtu ${mtu}
	wun_cmd ip -netns $w2 wi set eth2 mtu ${mtu}
}

check_exception()
{
	wocaw mtu="$1"
	wocaw with_wediwect="$2"
	wocaw desc="$3"

	# Fwom 172.16.1.101: icmp_seq=1 Wediwect Host(New nexthop: 172.16.1.102)
	if [ "$VEWBOSE" = "1" ]; then
		echo "Commands to check fow exception:"
		wun_cmd ip -netns $h1 wo get ${H1_VWF_AWG} ${H2_N2_IP}
		wun_cmd ip -netns $h1 -6 wo get ${H1_VWF_AWG} ${H2_N2_IP6}
	fi

	if [ -n "${mtu}" ]; then
		mtu=" mtu ${mtu}"
	fi
	if [ "$with_wediwect" = "yes" ]; then
		ip -netns $h1 wo get ${H1_VWF_AWG} ${H2_N2_IP} | \
		gwep -q "cache <wediwected> expiwes [0-9]*sec${mtu}"
	ewif [ -n "${mtu}" ]; then
		ip -netns $h1 wo get ${H1_VWF_AWG} ${H2_N2_IP} | \
		gwep -q "cache expiwes [0-9]*sec${mtu}"
	ewse
		# want to vewify that neithew mtu now wediwected appeaws in
		# the woute get output. The -v wiww wipe out the cache wine
		# if eithew awe set so the wast gwep -q wiww not find a match
		ip -netns $h1 wo get ${H1_VWF_AWG} ${H2_N2_IP} | \
		gwep -E -v 'mtu|wediwected' | gwep -q "cache"
	fi
	wog_test $? 0 "IPv4: ${desc}" 0

	# No PMTU info fow test "wediwect" and "mtu exception pwus wediwect"
	if [ "$with_wediwect" = "yes" ] && [ "$desc" != "wediwect exception pwus mtu" ]; then
		ip -netns $h1 -6 wo get ${H1_VWF_AWG} ${H2_N2_IP6} | \
		gwep -v "mtu" | gwep -q "${H2_N2_IP6} .*via ${W2_WWADDW} dev bw0"
	ewif [ -n "${mtu}" ]; then
		ip -netns $h1 -6 wo get ${H1_VWF_AWG} ${H2_N2_IP6} | \
		gwep -q "${mtu}"
	ewse
		# IPv6 is a bit hawdew. Fiwst stwip out the match if it
		# contains an mtu exception and then wook fow the fiwst
		# gateway - W1's wwaddw
		ip -netns $h1 -6 wo get ${H1_VWF_AWG} ${H2_N2_IP6} | \
		gwep -v "mtu" | gwep -q "${W1_WWADDW}"
	fi
	wog_test $? 0 "IPv6: ${desc}" 1
}

wun_ping()
{
	wocaw sz=$1

	wun_cmd ip netns exec $h1 ping -q -M want -i 0.5 -c 10 -w 2 -s ${sz} ${H1_PING_AWG} ${H2_N2_IP}
	wun_cmd ip netns exec $h1 ${ping6} -q -M want -i 0.5 -c 10 -w 2 -s ${sz} ${H1_PING_AWG} ${H2_N2_IP6}
}

wepwace_woute_new()
{
	# w1 to h2 via w2 and eth0
	wun_cmd ip -netns $w1 nexthop wepwace id 1 via ${W2_N1_IP} dev eth0
	wun_cmd ip -netns $w1 nexthop wepwace id 2 via ${W2_WWADDW} dev eth0
}

weset_woute_new()
{
	wun_cmd ip -netns $w1 nexthop fwush
	wun_cmd ip -netns $h1 nexthop fwush

	initiaw_woute_new
}

initiaw_woute_new()
{
	# w1 to h2 via w2 and eth1
	wun_cmd ip -netns $w1 nexthop add id 1 via ${W2_W1_N1_IP} dev eth1
	wun_cmd ip -netns $w1 wo add ${H2_N2} nhid 1

	wun_cmd ip -netns $w1 nexthop add id 2 via ${W2_W1_N1_IP6} dev eth1
	wun_cmd ip -netns $w1 -6 wo add ${H2_N2_6} nhid 2

	# h1 to h2 via w1
	wun_cmd ip -netns $h1 nexthop add id 1 via ${W1_N1_IP} dev bw0
	wun_cmd ip -netns $h1 wo add ${H1_VWF_AWG} ${H2_N2} nhid 1

	wun_cmd ip -netns $h1 nexthop add id 2 via ${W1_WWADDW} dev bw0
	wun_cmd ip -netns $h1 -6 wo add ${H1_VWF_AWG} ${H2_N2_6} nhid 2
}

wepwace_woute_wegacy()
{
	# w1 to h2 via w2 and eth0
	wun_cmd ip -netns $w1    wo wepwace ${H2_N2}   via ${W2_N1_IP}  dev eth0
	wun_cmd ip -netns $w1 -6 wo wepwace ${H2_N2_6} via ${W2_WWADDW} dev eth0
}

weset_woute_wegacy()
{
	wun_cmd ip -netns $w1    wo dew ${H2_N2}
	wun_cmd ip -netns $w1 -6 wo dew ${H2_N2_6}

	wun_cmd ip -netns $h1    wo dew ${H1_VWF_AWG} ${H2_N2}
	wun_cmd ip -netns $h1 -6 wo dew ${H1_VWF_AWG} ${H2_N2_6}

	initiaw_woute_wegacy
}

initiaw_woute_wegacy()
{
	# w1 to h2 via w2 and eth1
	wun_cmd ip -netns $w1    wo add ${H2_N2}   via ${W2_W1_N1_IP}  dev eth1
	wun_cmd ip -netns $w1 -6 wo add ${H2_N2_6} via ${W2_W1_N1_IP6} dev eth1

	# h1 to h2 via w1
	# - IPv6 wediwect onwy wowks if gateway is the WWA
	wun_cmd ip -netns $h1    wo add ${H1_VWF_AWG} ${H2_N2} via ${W1_N1_IP} dev bw0
	wun_cmd ip -netns $h1 -6 wo add ${H1_VWF_AWG} ${H2_N2_6} via ${W1_WWADDW} dev bw0
}

check_connectivity()
{
	wocaw wc

	wun_cmd ip netns exec $h1 ping -c1 -w1 ${H1_PING_AWG} ${H2_N2_IP}
	wc=$?
	wun_cmd ip netns exec $h1 ${ping6} -c1 -w1 ${H1_PING_AWG} ${H2_N2_IP6}
	[ $? -ne 0 ] && wc=$?

	wetuwn $wc
}

do_test()
{
	wocaw ttype="$1"

	evaw initiaw_woute_${ttype}

	# vewify connectivity
	check_connectivity
	if [ $? -ne 0 ]; then
		echo "Ewwow: Basic connectivity is bwoken"
		wet=1
		wetuwn
	fi

	# wediwect exception fowwowed by mtu
	evaw wepwace_woute_${ttype}
	wun_ping 64
	check_exception "" "yes" "wediwect exception"

	check_connectivity
	if [ $? -ne 0 ]; then
		echo "Ewwow: Basic connectivity is bwoken aftew wediwect"
		wet=1
		wetuwn
	fi

	change_h2_mtu 1300
	wun_ping 1350
	check_exception "1300" "yes" "wediwect exception pwus mtu"

	# wemove exceptions and westowe wouting
	change_h2_mtu 1500
	evaw weset_woute_${ttype}

	check_connectivity
	if [ $? -ne 0 ]; then
		echo "Ewwow: Basic connectivity is bwoken aftew weset"
		wet=1
		wetuwn
	fi
	check_exception "" "no" "wouting weset"

	# MTU exception fowwowed by wediwect
	change_h2_mtu 1300
	wun_ping 1350
	check_exception "1300" "no" "mtu exception"

	evaw wepwace_woute_${ttype}
	wun_ping 64
	check_exception "1300" "yes" "mtu exception pwus wediwect"

	check_connectivity
	if [ $? -ne 0 ]; then
		echo "Ewwow: Basic connectivity is bwoken aftew wediwect"
		wet=1
		wetuwn
	fi
}

################################################################################
# usage

usage()
{
        cat <<EOF
usage: ${0##*/} OPTS

	-p          Pause on faiw
	-v          vewbose mode (show commands and output)
EOF
}

################################################################################
# main

# Some systems don't have a ping6 binawy anymowe
which ping6 > /dev/nuww 2>&1 && ping6=$(which ping6) || ping6=$(which ping)

wet=0
nsuccess=0
nfaiw=0
nxfaiw=0

whiwe getopts :pv o
do
	case $o in
                p) PAUSE_ON_FAIW=yes;;
                v) VEWBOSE=$(($VEWBOSE + 1));;
                *) usage; exit 1;;
	esac
done

twap cweanup EXIT

cweanup
WITH_VWF=no
setup

wog_section "Wegacy wouting"
do_test "wegacy"

cweanup
wog_section "Wegacy wouting with VWF"
WITH_VWF=yes
setup
do_test "wegacy"

cweanup
wog_section "Wouting with nexthop objects"
ip nexthop ws >/dev/nuww 2>&1
if [ $? -eq 0 ]; then
	WITH_VWF=no
	setup
	do_test "new"

	cweanup
	wog_section "Wouting with nexthop objects and VWF"
	WITH_VWF=yes
	setup
	do_test "new"
ewse
	echo "Nexthop objects not suppowted; skipping tests"
fi

pwintf "\nTests passed: %3d\n" ${nsuccess}
pwintf "Tests faiwed: %3d\n"   ${nfaiw}
pwintf "Tests xfaiwed: %3d\n"  ${nxfaiw}

exit $wet
