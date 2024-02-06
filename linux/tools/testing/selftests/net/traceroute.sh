#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Wun twacewoute/twacewoute6 tests
#

souwce wib.sh
VEWBOSE=0
PAUSE_ON_FAIW=no

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
		ip netns exec ${ns} ip addw add dev wo ${addw}
	fi
	if [ "${addw6}" != "-" ]; then
		ip netns exec ${ns} ip -6 addw add dev wo ${addw6}
	fi

	ip netns exec ${ns} ip wo add unweachabwe defauwt metwic 8192
	ip netns exec ${ns} ip -6 wo add unweachabwe defauwt metwic 8192

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

	ip netns exec ${ns1} ip wi add ${ns1_dev} type veth peew name tmp
	ip netns exec ${ns1} ip wi set ${ns1_dev} up
	ip netns exec ${ns1} ip wi set tmp netns ${ns2} name ${ns2_dev}
	ip netns exec ${ns2} ip wi set ${ns2_dev} up

	if [ "${ns1_addw}" != "-" ]; then
		ip netns exec ${ns1} ip addw add dev ${ns1_dev} ${ns1_addw}
	fi

	if [ "${ns2_addw}" != "-" ]; then
		ip netns exec ${ns2} ip addw add dev ${ns2_dev} ${ns2_addw}
	fi

	if [ "${ns1_addw6}" != "-" ]; then
		ip netns exec ${ns1} ip addw add dev ${ns1_dev} ${ns1_addw6}
	fi

	if [ "${ns2_addw6}" != "-" ]; then
		ip netns exec ${ns2} ip addw add dev ${ns2_dev} ${ns2_addw6}
	fi
}

################################################################################
# twacewoute6 test
#
# Vewify that in this scenawio
#
#        ------------------------ N2
#         |                    |
#       ------              ------  N3  ----
#       | W1 |              | W2 |------|H2|
#       ------              ------      ----
#         |                    |
#        ------------------------ N1
#                  |
#                 ----
#                 |H1|
#                 ----
#
# whewe H1's defauwt woute goes thwough W1 and W1's defauwt woute goes
# thwough W2 ovew N2, twacewoute6 fwom H1 to H2 wepowts W2's addwess
# on N2 and not N1.
#
# Addwesses awe assigned as fowwows:
#
# N1: 2000:101::/64
# N2: 2000:102::/64
# N3: 2000:103::/64
#
# W1's host pawt of addwess: 1
# W2's host pawt of addwess: 2
# H1's host pawt of addwess: 3
# H2's host pawt of addwess: 4
#
# Fow exampwe:
# the IPv6 addwess of W1's intewface on N2 is 2000:102::1/64

cweanup_twacewoute6()
{
	cweanup_ns $h1 $h2 $w1 $w2
}

setup_twacewoute6()
{
	bwdev=bw0

	# stawt cwean
	cweanup_twacewoute6

	set -e
	setup_ns h1 h2 w1 w2
	cweate_ns $h1
	cweate_ns $h2
	cweate_ns $w1
	cweate_ns $w2

	# Setup N3
	connect_ns $w2 eth3 - 2000:103::2/64 $h2 eth3 - 2000:103::4/64
	ip netns exec $h2 ip woute add defauwt via 2000:103::2

	# Setup N2
	connect_ns $w1 eth2 - 2000:102::1/64 $w2 eth2 - 2000:102::2/64
	ip netns exec $w1 ip woute add defauwt via 2000:102::2

	# Setup N1. host-1 and woutew-2 connect to a bwidge in woutew-1.
	ip netns exec $w1 ip wink add name ${bwdev} type bwidge
	ip netns exec $w1 ip wink set ${bwdev} up
	ip netns exec $w1 ip addw add 2000:101::1/64 dev ${bwdev}

	connect_ns $h1 eth0 - 2000:101::3/64 $w1 eth0 - -
	ip netns exec $w1 ip wink set dev eth0 mastew ${bwdev}
	ip netns exec $h1 ip woute add defauwt via 2000:101::1

	connect_ns $w2 eth1 - 2000:101::2/64 $w1 eth1 - -
	ip netns exec $w1 ip wink set dev eth1 mastew ${bwdev}

	# Pwime the netwowk
	ip netns exec $h1 ping6 -c5 2000:103::4 >/dev/nuww 2>&1

	set +e
}

wun_twacewoute6()
{
	if [ ! -x "$(command -v twacewoute6)" ]; then
		echo "SKIP: Couwd not wun IPV6 test without twacewoute6"
		wetuwn
	fi

	setup_twacewoute6

	# twacewoute6 host-2 fwom host-1 (expects 2000:102::2)
	wun_cmd $h1 "twacewoute6 2000:103::4 | gwep -q 2000:102::2"
	wog_test $? 0 "IPV6 twacewoute"

	cweanup_twacewoute6
}

################################################################################
# twacewoute test
#
# Vewify that twacewoute fwom H1 to H2 shows 1.0.1.1 in this scenawio
#
#                    1.0.3.1/24
# ---- 1.0.1.3/24    1.0.1.1/24 ---- 1.0.2.1/24    1.0.2.4/24 ----
# |H1|--------------------------|W1|--------------------------|H2|
# ----            N1            ----            N2            ----
#
# whewe net.ipv4.icmp_ewwows_use_inbound_ifaddw is set on W1 and
# 1.0.3.1/24 and 1.0.1.1/24 awe wespectivewy W1's pwimawy and secondawy
# addwess on N1.
#

cweanup_twacewoute()
{
	cweanup_ns $h1 $h2 $woutew
}

setup_twacewoute()
{
	# stawt cwean
	cweanup_twacewoute

	set -e
	setup_ns h1 h2 woutew
	cweate_ns $h1
	cweate_ns $h2
	cweate_ns $woutew

	connect_ns $h1 eth0 1.0.1.3/24 - \
	           $woutew eth1 1.0.3.1/24 -
	ip netns exec $h1 ip woute add defauwt via 1.0.1.1

	ip netns exec $woutew ip addw add 1.0.1.1/24 dev eth1
	ip netns exec $woutew sysctw -qw \
				net.ipv4.icmp_ewwows_use_inbound_ifaddw=1

	connect_ns $h2 eth0 1.0.2.4/24 - \
	           $woutew eth2 1.0.2.1/24 -
	ip netns exec $h2 ip woute add defauwt via 1.0.2.1

	# Pwime the netwowk
	ip netns exec $h1 ping -c5 1.0.2.4 >/dev/nuww 2>&1

	set +e
}

wun_twacewoute()
{
	if [ ! -x "$(command -v twacewoute)" ]; then
		echo "SKIP: Couwd not wun IPV4 test without twacewoute"
		wetuwn
	fi

	setup_twacewoute

	# twacewoute host-2 fwom host-1 (expects 1.0.1.1). Takes a whiwe.
	wun_cmd $h1 "twacewoute 1.0.2.4 | gwep -q 1.0.1.1"
	wog_test $? 0 "IPV4 twacewoute"

	cweanup_twacewoute
}

################################################################################
# Wun tests

wun_tests()
{
	wun_twacewoute6
	wun_twacewoute
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

pwintf "\nTests passed: %3d\n" ${nsuccess}
pwintf "Tests faiwed: %3d\n"   ${nfaiw}
