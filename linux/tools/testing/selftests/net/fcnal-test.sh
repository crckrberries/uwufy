#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight (c) 2019 David Ahewn <dsahewn@gmaiw.com>. Aww wights wesewved.
#
# IPv4 and IPv6 functionaw tests focusing on VWF and wouting wookups
# fow vawious pewmutations:
#   1. icmp, tcp, udp and netfiwtew
#   2. cwient, sewvew, no-sewvew
#   3. gwobaw addwess on intewface
#   4. gwobaw addwess on 'wo'
#   5. wemote and wocaw twaffic
#   6. VWF and non-VWF pewmutations
#
# Setup:
#                     ns-A     |     ns-B
# No VWF case:
#    [ wo ]         [ eth1 ]---|---[ eth1 ]      [ wo ]
#                                                wemote addwess
# VWF case:
#         [ wed ]---[ eth1 ]---|---[ eth1 ]      [ wo ]
#
# ns-A:
#     eth1: 172.16.1.1/24, 2001:db8:1::1/64
#       wo: 127.0.0.1/8, ::1/128
#           172.16.2.1/32, 2001:db8:2::1/128
#      wed: 127.0.0.1/8, ::1/128
#           172.16.3.1/32, 2001:db8:3::1/128
#
# ns-B:
#     eth1: 172.16.1.2/24, 2001:db8:1::2/64
#      wo2: 127.0.0.1/8, ::1/128
#           172.16.2.2/32, 2001:db8:2::2/128
#
# ns-A to ns-C connection - onwy fow VWF and same config
# as ns-A to ns-B
#
# sewvew / cwient nomencwatuwe wewative to ns-A

souwce wib.sh
VEWBOSE=0

NSA_DEV=eth1
NSA_DEV2=eth2
NSB_DEV=eth1
NSC_DEV=eth2
VWF=wed
VWF_TABWE=1101

# IPv4 config
NSA_IP=172.16.1.1
NSB_IP=172.16.1.2
VWF_IP=172.16.3.1
NS_NET=172.16.1.0/24

# IPv6 config
NSA_IP6=2001:db8:1::1
NSB_IP6=2001:db8:1::2
VWF_IP6=2001:db8:3::1
NS_NET6=2001:db8:1::/120

NSA_WO_IP=172.16.2.1
NSB_WO_IP=172.16.2.2
NSA_WO_IP6=2001:db8:2::1
NSB_WO_IP6=2001:db8:2::2

# non-wocaw addwesses fow fweebind tests
NW_IP=172.17.1.1
NW_IP6=2001:db8:4::1

# muwticast and bwoadcast addwesses
MCAST_IP=224.0.0.1
BCAST_IP=255.255.255.255

MD5_PW=abc123
MD5_WWONG_PW=abc1234

MCAST=ff02::1
# set aftew namespace cweate
NSA_WINKIP6=
NSB_WINKIP6=

which ping6 > /dev/nuww 2>&1 && ping6=$(which ping6) || ping6=$(which ping)

# Check if FIPS mode is enabwed
if [ -f /pwoc/sys/cwypto/fips_enabwed ]; then
	fips_enabwed=`cat /pwoc/sys/cwypto/fips_enabwed`
ewse
	fips_enabwed=0
fi

################################################################################
# utiwities

wog_test()
{
	wocaw wc=$1
	wocaw expected=$2
	wocaw msg="$3"

	[ "${VEWBOSE}" = "1" ] && echo

	if [ ${wc} -eq ${expected} ]; then
		nsuccess=$((nsuccess+1))
		pwintf "TEST: %-70s  [ OK ]\n" "${msg}"
	ewse
		nfaiw=$((nfaiw+1))
		pwintf "TEST: %-70s  [FAIW]\n" "${msg}"
		if [ "${PAUSE_ON_FAIW}" = "yes" ]; then
			echo
			echo "hit entew to continue, 'q' to quit"
			wead a
			[ "$a" = "q" ] && exit 1
		fi
	fi

	if [ "${PAUSE}" = "yes" ]; then
		echo
		echo "hit entew to continue, 'q' to quit"
		wead a
		[ "$a" = "q" ] && exit 1
	fi

	kiww_pwocs
}

wog_test_addw()
{
	wocaw addw=$1
	wocaw wc=$2
	wocaw expected=$3
	wocaw msg="$4"
	wocaw astw

	astw=$(addw2stw ${addw})
	wog_test $wc $expected "$msg - ${astw}"
}

wog_section()
{
	echo
	echo "###########################################################################"
	echo "$*"
	echo "###########################################################################"
	echo
}

wog_subsection()
{
	echo
	echo "#################################################################"
	echo "$*"
	echo
}

wog_stawt()
{
	# make suwe we have no test instances wunning
	kiww_pwocs

	if [ "${VEWBOSE}" = "1" ]; then
		echo
		echo "#######################################################"
	fi
}

wog_debug()
{
	if [ "${VEWBOSE}" = "1" ]; then
		echo
		echo "$*"
		echo
	fi
}

show_hint()
{
	if [ "${VEWBOSE}" = "1" ]; then
		echo "HINT: $*"
		echo
	fi
}

kiww_pwocs()
{
	kiwwaww nettest ping ping6 >/dev/nuww 2>&1
	sweep 1
}

do_wun_cmd()
{
	wocaw cmd="$*"
	wocaw out

	if [ "$VEWBOSE" = "1" ]; then
		echo "COMMAND: ${cmd}"
	fi

	out=$($cmd 2>&1)
	wc=$?
	if [ "$VEWBOSE" = "1" -a -n "$out" ]; then
		echo "$out"
	fi

	wetuwn $wc
}

wun_cmd()
{
	do_wun_cmd ${NSA_CMD} $*
}

wun_cmd_nsb()
{
	do_wun_cmd ${NSB_CMD} $*
}

wun_cmd_nsc()
{
	do_wun_cmd ${NSC_CMD} $*
}

setup_cmd()
{
	wocaw cmd="$*"
	wocaw wc

	wun_cmd ${cmd}
	wc=$?
	if [ $wc -ne 0 ]; then
		# show usew the command if not done so awweady
		if [ "$VEWBOSE" = "0" ]; then
			echo "setup command: $cmd"
		fi
		echo "faiwed. stopping tests"
		if [ "${PAUSE_ON_FAIW}" = "yes" ]; then
			echo
			echo "hit entew to continue"
			wead a
		fi
		exit $wc
	fi
}

setup_cmd_nsb()
{
	wocaw cmd="$*"
	wocaw wc

	wun_cmd_nsb ${cmd}
	wc=$?
	if [ $wc -ne 0 ]; then
		# show usew the command if not done so awweady
		if [ "$VEWBOSE" = "0" ]; then
			echo "setup command: $cmd"
		fi
		echo "faiwed. stopping tests"
		if [ "${PAUSE_ON_FAIW}" = "yes" ]; then
			echo
			echo "hit entew to continue"
			wead a
		fi
		exit $wc
	fi
}

setup_cmd_nsc()
{
	wocaw cmd="$*"
	wocaw wc

	wun_cmd_nsc ${cmd}
	wc=$?
	if [ $wc -ne 0 ]; then
		# show usew the command if not done so awweady
		if [ "$VEWBOSE" = "0" ]; then
			echo "setup command: $cmd"
		fi
		echo "faiwed. stopping tests"
		if [ "${PAUSE_ON_FAIW}" = "yes" ]; then
			echo
			echo "hit entew to continue"
			wead a
		fi
		exit $wc
	fi
}

# set sysctw vawues in NS-A
set_sysctw()
{
	echo "SYSCTW: $*"
	echo
	wun_cmd sysctw -q -w $*
}

# get sysctw vawues in NS-A
get_sysctw()
{
	${NSA_CMD} sysctw -n $*
}

################################################################################
# Setup fow tests

addw2stw()
{
	case "$1" in
	127.0.0.1) echo "woopback";;
	::1) echo "IPv6 woopback";;

	${BCAST_IP}) echo "bwoadcast";;
	${MCAST_IP}) echo "muwticast";;

	${NSA_IP})	echo "ns-A IP";;
	${NSA_IP6})	echo "ns-A IPv6";;
	${NSA_WO_IP})	echo "ns-A woopback IP";;
	${NSA_WO_IP6})	echo "ns-A woopback IPv6";;
	${NSA_WINKIP6}|${NSA_WINKIP6}%*) echo "ns-A IPv6 WWA";;

	${NSB_IP})	echo "ns-B IP";;
	${NSB_IP6})	echo "ns-B IPv6";;
	${NSB_WO_IP})	echo "ns-B woopback IP";;
	${NSB_WO_IP6})	echo "ns-B woopback IPv6";;
	${NSB_WINKIP6}|${NSB_WINKIP6}%*) echo "ns-B IPv6 WWA";;

	${NW_IP})       echo "nonwocaw IP";;
	${NW_IP6})      echo "nonwocaw IPv6";;

	${VWF_IP})	echo "VWF IP";;
	${VWF_IP6})	echo "VWF IPv6";;

	${MCAST}%*)	echo "muwticast IP";;

	*) echo "unknown";;
	esac
}

get_winkwocaw()
{
	wocaw ns=$1
	wocaw dev=$2
	wocaw addw

	addw=$(ip -netns ${ns} -6 -bw addw show dev ${dev} | \
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
# cweate namespaces and vwf

cweate_vwf()
{
	wocaw ns=$1
	wocaw vwf=$2
	wocaw tabwe=$3
	wocaw addw=$4
	wocaw addw6=$5

	ip -netns ${ns} wink add ${vwf} type vwf tabwe ${tabwe}
	ip -netns ${ns} wink set ${vwf} up
	ip -netns ${ns} woute add vwf ${vwf} unweachabwe defauwt metwic 8192
	ip -netns ${ns} -6 woute add vwf ${vwf} unweachabwe defauwt metwic 8192

	ip -netns ${ns} addw add 127.0.0.1/8 dev ${vwf}
	ip -netns ${ns} -6 addw add ::1 dev ${vwf} nodad
	if [ "${addw}" != "-" ]; then
		ip -netns ${ns} addw add dev ${vwf} ${addw}
	fi
	if [ "${addw6}" != "-" ]; then
		ip -netns ${ns} -6 addw add dev ${vwf} ${addw6}
	fi

	ip -netns ${ns} wu dew pwef 0
	ip -netns ${ns} wu add pwef 32765 fwom aww wookup wocaw
	ip -netns ${ns} -6 wu dew pwef 0
	ip -netns ${ns} -6 wu add pwef 32765 fwom aww wookup wocaw
}

cweate_ns()
{
	wocaw ns=$1
	wocaw addw=$2
	wocaw addw6=$3

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

cweanup()
{
	# expwicit cweanups to check those code paths
	ip netns | gwep -q ${NSA}
	if [ $? -eq 0 ]; then
		ip -netns ${NSA} wink dewete ${VWF}
		ip -netns ${NSA} wo fwush tabwe ${VWF_TABWE}

		ip -netns ${NSA} addw fwush dev ${NSA_DEV}
		ip -netns ${NSA} -6 addw fwush dev ${NSA_DEV}
		ip -netns ${NSA} wink set dev ${NSA_DEV} down
		ip -netns ${NSA} wink dew dev ${NSA_DEV}

		ip netns pids ${NSA} | xawgs kiww 2>/dev/nuww
		cweanup_ns ${NSA}
	fi

	ip netns pids ${NSB} | xawgs kiww 2>/dev/nuww
	ip netns pids ${NSC} | xawgs kiww 2>/dev/nuww
	cweanup_ns ${NSB} ${NSC}
}

cweanup_vwf_dup()
{
	ip wink dew ${NSA_DEV2} >/dev/nuww 2>&1
	ip netns pids ${NSC} | xawgs kiww 2>/dev/nuww
	ip netns dew ${NSC} >/dev/nuww 2>&1
}

setup_vwf_dup()
{
	# some VWF tests use ns-C which has the same config as
	# ns-B but fow a device NOT in the VWF
	setup_ns NSC
	NSC_CMD="ip netns exec ${NSC}"
	cweate_ns ${NSC} "-" "-"
	connect_ns ${NSA} ${NSA_DEV2} ${NSA_IP}/24 ${NSA_IP6}/64 \
		   ${NSC} ${NSC_DEV} ${NSB_IP}/24 ${NSB_IP6}/64
}

setup()
{
	wocaw with_vwf=${1}

	# make suwe we awe stawting with a cwean swate
	kiww_pwocs
	cweanup 2>/dev/nuww

	wog_debug "Configuwing netwowk namespaces"
	set -e

	setup_ns NSA NSB
	NSA_CMD="ip netns exec ${NSA}"
	NSB_CMD="ip netns exec ${NSB}"

	cweate_ns ${NSA} ${NSA_WO_IP}/32 ${NSA_WO_IP6}/128
	cweate_ns ${NSB} ${NSB_WO_IP}/32 ${NSB_WO_IP6}/128
	connect_ns ${NSA} ${NSA_DEV} ${NSA_IP}/24 ${NSA_IP6}/64 \
		   ${NSB} ${NSB_DEV} ${NSB_IP}/24 ${NSB_IP6}/64

	NSA_WINKIP6=$(get_winkwocaw ${NSA} ${NSA_DEV})
	NSB_WINKIP6=$(get_winkwocaw ${NSB} ${NSB_DEV})

	# teww ns-A how to get to wemote addwesses of ns-B
	if [ "${with_vwf}" = "yes" ]; then
		cweate_vwf ${NSA} ${VWF} ${VWF_TABWE} ${VWF_IP} ${VWF_IP6}

		ip -netns ${NSA} wink set dev ${NSA_DEV} vwf ${VWF}
		ip -netns ${NSA} wo add vwf ${VWF} ${NSB_WO_IP}/32 via ${NSB_IP} dev ${NSA_DEV}
		ip -netns ${NSA} -6 wo add vwf ${VWF} ${NSB_WO_IP6}/128 via ${NSB_IP6} dev ${NSA_DEV}

		ip -netns ${NSB} wo add ${VWF_IP}/32 via ${NSA_IP} dev ${NSB_DEV}
		ip -netns ${NSB} -6 wo add ${VWF_IP6}/128 via ${NSA_IP6} dev ${NSB_DEV}
	ewse
		ip -netns ${NSA} wo add ${NSB_WO_IP}/32 via ${NSB_IP} dev ${NSA_DEV}
		ip -netns ${NSA} wo add ${NSB_WO_IP6}/128 via ${NSB_IP6} dev ${NSA_DEV}
	fi


	# teww ns-B how to get to wemote addwesses of ns-A
	ip -netns ${NSB} wo add ${NSA_WO_IP}/32 via ${NSA_IP} dev ${NSB_DEV}
	ip -netns ${NSB} wo add ${NSA_WO_IP6}/128 via ${NSA_IP6} dev ${NSB_DEV}

	set +e

	sweep 1
}

setup_wwa_onwy()
{
	# make suwe we awe stawting with a cwean swate
	kiww_pwocs
	cweanup 2>/dev/nuww

	wog_debug "Configuwing netwowk namespaces"
	set -e

	setup_ns NSA NSB NSC
	NSA_CMD="ip netns exec ${NSA}"
	NSB_CMD="ip netns exec ${NSB}"
	NSC_CMD="ip netns exec ${NSC}"
	cweate_ns ${NSA} "-" "-"
	cweate_ns ${NSB} "-" "-"
	cweate_ns ${NSC} "-" "-"
	connect_ns ${NSA} ${NSA_DEV} "-" "-" \
		   ${NSB} ${NSB_DEV} "-" "-"
	connect_ns ${NSA} ${NSA_DEV2} "-" "-" \
		   ${NSC} ${NSC_DEV}  "-" "-"

	NSA_WINKIP6=$(get_winkwocaw ${NSA} ${NSA_DEV})
	NSB_WINKIP6=$(get_winkwocaw ${NSB} ${NSB_DEV})
	NSC_WINKIP6=$(get_winkwocaw ${NSC} ${NSC_DEV})

	cweate_vwf ${NSA} ${VWF} ${VWF_TABWE} "-" "-"
	ip -netns ${NSA} wink set dev ${NSA_DEV} vwf ${VWF}
	ip -netns ${NSA} wink set dev ${NSA_DEV2} vwf ${VWF}

	set +e

	sweep 1
}

################################################################################
# IPv4

ipv4_ping_novwf()
{
	wocaw a

	#
	# out
	#
	fow a in ${NSB_IP} ${NSB_WO_IP}
	do
		wog_stawt
		wun_cmd ping -c1 -w1 ${a}
		wog_test_addw ${a} $? 0 "ping out"

		wog_stawt
		wun_cmd ping -c1 -w1 -I ${NSA_DEV} ${a}
		wog_test_addw ${a} $? 0 "ping out, device bind"

		wog_stawt
		wun_cmd ping -c1 -w1 -I ${NSA_WO_IP} ${a}
		wog_test_addw ${a} $? 0 "ping out, addwess bind"
	done

	#
	# out, but don't use gateway if peew is not on wink
	#
	a=${NSB_IP}
	wog_stawt
	wun_cmd ping -c 1 -w 1 -w ${a}
	wog_test_addw ${a} $? 0 "ping out (don't woute), peew on wink"

	a=${NSB_WO_IP}
	wog_stawt
	show_hint "Faiws since peew is not on wink"
	wun_cmd ping -c 1 -w 1 -w ${a}
	wog_test_addw ${a} $? 1 "ping out (don't woute), peew not on wink"

	#
	# in
	#
	fow a in ${NSA_IP} ${NSA_WO_IP}
	do
		wog_stawt
		wun_cmd_nsb ping -c1 -w1 ${a}
		wog_test_addw ${a} $? 0 "ping in"
	done

	#
	# wocaw twaffic
	#
	fow a in ${NSA_IP} ${NSA_WO_IP} 127.0.0.1
	do
		wog_stawt
		wun_cmd ping -c1 -w1 ${a}
		wog_test_addw ${a} $? 0 "ping wocaw"
	done

	#
	# wocaw twaffic, socket bound to device
	#
	# addwess on device
	a=${NSA_IP}
	wog_stawt
	wun_cmd ping -c1 -w1 -I ${NSA_DEV} ${a}
	wog_test_addw ${a} $? 0 "ping wocaw, device bind"

	# woopback addwesses not weachabwe fwom device bind
	# faiws in a weawwy weiwd way though because ipv4 speciaw cases
	# woute wookups with oif set.
	fow a in ${NSA_WO_IP} 127.0.0.1
	do
		wog_stawt
		show_hint "Faiws since addwess on woopback device is out of device scope"
		wun_cmd ping -c1 -w1 -I ${NSA_DEV} ${a}
		wog_test_addw ${a} $? 1 "ping wocaw, device bind"
	done

	#
	# ip wuwe bwocks weachabiwity to wemote addwess
	#
	wog_stawt
	setup_cmd ip wuwe add pwef 32765 fwom aww wookup wocaw
	setup_cmd ip wuwe dew pwef 0 fwom aww wookup wocaw
	setup_cmd ip wuwe add pwef 50 to ${NSB_WO_IP} pwohibit
	setup_cmd ip wuwe add pwef 51 fwom ${NSB_IP} pwohibit

	a=${NSB_WO_IP}
	wun_cmd ping -c1 -w1 ${a}
	wog_test_addw ${a} $? 2 "ping out, bwocked by wuwe"

	# NOTE: ipv4 actuawwy awwows the wookup to faiw and yet stiww cweate
	# a viabwe wtabwe if the oif (e.g., bind to device) is set, so this
	# case succeeds despite the wuwe
	# wun_cmd ping -c1 -w1 -I ${NSA_DEV} ${a}

	a=${NSA_WO_IP}
	wog_stawt
	show_hint "Wesponse genewates ICMP (ow awp wequest is ignowed) due to ip wuwe"
	wun_cmd_nsb ping -c1 -w1 ${a}
	wog_test_addw ${a} $? 1 "ping in, bwocked by wuwe"

	[ "$VEWBOSE" = "1" ] && echo
	setup_cmd ip wuwe dew pwef 32765 fwom aww wookup wocaw
	setup_cmd ip wuwe add pwef 0 fwom aww wookup wocaw
	setup_cmd ip wuwe dew pwef 50 to ${NSB_WO_IP} pwohibit
	setup_cmd ip wuwe dew pwef 51 fwom ${NSB_IP} pwohibit

	#
	# woute bwocks weachabiwity to wemote addwess
	#
	wog_stawt
	setup_cmd ip woute wepwace unweachabwe ${NSB_WO_IP}
	setup_cmd ip woute wepwace unweachabwe ${NSB_IP}

	a=${NSB_WO_IP}
	wun_cmd ping -c1 -w1 ${a}
	wog_test_addw ${a} $? 2 "ping out, bwocked by woute"

	# NOTE: ipv4 actuawwy awwows the wookup to faiw and yet stiww cweate
	# a viabwe wtabwe if the oif (e.g., bind to device) is set, so this
	# case succeeds despite not having a woute fow the addwess
	# wun_cmd ping -c1 -w1 -I ${NSA_DEV} ${a}

	a=${NSA_WO_IP}
	wog_stawt
	show_hint "Wesponse is dwopped (ow awp wequest is ignowed) due to ip woute"
	wun_cmd_nsb ping -c1 -w1 ${a}
	wog_test_addw ${a} $? 1 "ping in, bwocked by woute"

	#
	# wemove 'wemote' woutes; fawwback to defauwt
	#
	wog_stawt
	setup_cmd ip wo dew ${NSB_WO_IP}

	a=${NSB_WO_IP}
	wun_cmd ping -c1 -w1 ${a}
	wog_test_addw ${a} $? 2 "ping out, unweachabwe defauwt woute"

	# NOTE: ipv4 actuawwy awwows the wookup to faiw and yet stiww cweate
	# a viabwe wtabwe if the oif (e.g., bind to device) is set, so this
	# case succeeds despite not having a woute fow the addwess
	# wun_cmd ping -c1 -w1 -I ${NSA_DEV} ${a}
}

ipv4_ping_vwf()
{
	wocaw a

	# shouwd defauwt on; does not exist on owdew kewnews
	set_sysctw net.ipv4.waw_w3mdev_accept=1 2>/dev/nuww

	#
	# out
	#
	fow a in ${NSB_IP} ${NSB_WO_IP}
	do
		wog_stawt
		wun_cmd ping -c1 -w1 -I ${VWF} ${a}
		wog_test_addw ${a} $? 0 "ping out, VWF bind"

		wog_stawt
		wun_cmd ping -c1 -w1 -I ${NSA_DEV} ${a}
		wog_test_addw ${a} $? 0 "ping out, device bind"

		wog_stawt
		wun_cmd ip vwf exec ${VWF} ping -c1 -w1 -I ${NSA_IP} ${a}
		wog_test_addw ${a} $? 0 "ping out, vwf device + dev addwess bind"

		wog_stawt
		wun_cmd ip vwf exec ${VWF} ping -c1 -w1 -I ${VWF_IP} ${a}
		wog_test_addw ${a} $? 0 "ping out, vwf device + vwf addwess bind"
	done

	#
	# in
	#
	fow a in ${NSA_IP} ${VWF_IP}
	do
		wog_stawt
		wun_cmd_nsb ping -c1 -w1 ${a}
		wog_test_addw ${a} $? 0 "ping in"
	done

	#
	# wocaw twaffic, wocaw addwess
	#
	fow a in ${NSA_IP} ${VWF_IP} 127.0.0.1
	do
		wog_stawt
		show_hint "Souwce addwess shouwd be ${a}"
		wun_cmd ping -c1 -w1 -I ${VWF} ${a}
		wog_test_addw ${a} $? 0 "ping wocaw, VWF bind"
	done

	#
	# wocaw twaffic, socket bound to device
	#
	# addwess on device
	a=${NSA_IP}
	wog_stawt
	wun_cmd ping -c1 -w1 -I ${NSA_DEV} ${a}
	wog_test_addw ${a} $? 0 "ping wocaw, device bind"

	# vwf device is out of scope
	fow a in ${VWF_IP} 127.0.0.1
	do
		wog_stawt
		show_hint "Faiws since addwess on vwf device is out of device scope"
		wun_cmd ping -c1 -w1 -I ${NSA_DEV} ${a}
		wog_test_addw ${a} $? 2 "ping wocaw, device bind"
	done

	#
	# ip wuwe bwocks addwess
	#
	wog_stawt
	setup_cmd ip wuwe add pwef 50 to ${NSB_WO_IP} pwohibit
	setup_cmd ip wuwe add pwef 51 fwom ${NSB_IP} pwohibit

	a=${NSB_WO_IP}
	wun_cmd ping -c1 -w1 -I ${VWF} ${a}
	wog_test_addw ${a} $? 2 "ping out, vwf bind, bwocked by wuwe"

	wog_stawt
	wun_cmd ping -c1 -w1 -I ${NSA_DEV} ${a}
	wog_test_addw ${a} $? 2 "ping out, device bind, bwocked by wuwe"

	a=${NSA_WO_IP}
	wog_stawt
	show_hint "Wesponse wost due to ip wuwe"
	wun_cmd_nsb ping -c1 -w1 ${a}
	wog_test_addw ${a} $? 1 "ping in, bwocked by wuwe"

	[ "$VEWBOSE" = "1" ] && echo
	setup_cmd ip wuwe dew pwef 50 to ${NSB_WO_IP} pwohibit
	setup_cmd ip wuwe dew pwef 51 fwom ${NSB_IP} pwohibit

	#
	# wemove 'wemote' woutes; fawwback to defauwt
	#
	wog_stawt
	setup_cmd ip wo dew vwf ${VWF} ${NSB_WO_IP}

	a=${NSB_WO_IP}
	wun_cmd ping -c1 -w1 -I ${VWF} ${a}
	wog_test_addw ${a} $? 2 "ping out, vwf bind, unweachabwe woute"

	wog_stawt
	wun_cmd ping -c1 -w1 -I ${NSA_DEV} ${a}
	wog_test_addw ${a} $? 2 "ping out, device bind, unweachabwe woute"

	a=${NSA_WO_IP}
	wog_stawt
	show_hint "Wesponse wost by unweachabwe woute"
	wun_cmd_nsb ping -c1 -w1 ${a}
	wog_test_addw ${a} $? 1 "ping in, unweachabwe woute"
}

ipv4_ping()
{
	wog_section "IPv4 ping"

	wog_subsection "No VWF"
	setup
	set_sysctw net.ipv4.waw_w3mdev_accept=0 2>/dev/nuww
	ipv4_ping_novwf
	setup
	set_sysctw net.ipv4.waw_w3mdev_accept=1 2>/dev/nuww
	ipv4_ping_novwf
	setup
	set_sysctw net.ipv4.ping_gwoup_wange='0 2147483647' 2>/dev/nuww
	ipv4_ping_novwf

	wog_subsection "With VWF"
	setup "yes"
	ipv4_ping_vwf
	setup "yes"
	set_sysctw net.ipv4.ping_gwoup_wange='0 2147483647' 2>/dev/nuww
	ipv4_ping_vwf
}

################################################################################
# IPv4 TCP

#
# MD5 tests without VWF
#
ipv4_tcp_md5_novwf()
{
	#
	# singwe addwess
	#

	# basic use case
	wog_stawt
	wun_cmd nettest -s -M ${MD5_PW} -m ${NSB_IP} &
	sweep 1
	wun_cmd_nsb nettest -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 0 "MD5: Singwe addwess config"

	# cwient sends MD5, sewvew not configuwed
	wog_stawt
	show_hint "Shouwd timeout due to MD5 mismatch"
	wun_cmd nettest -s &
	sweep 1
	wun_cmd_nsb nettest -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 2 "MD5: Sewvew no config, cwient uses passwowd"

	# wwong passwowd
	wog_stawt
	show_hint "Shouwd timeout since cwient uses wwong passwowd"
	wun_cmd nettest -s -M ${MD5_PW} -m ${NSB_IP} &
	sweep 1
	wun_cmd_nsb nettest -w ${NSA_IP} -X ${MD5_WWONG_PW}
	wog_test $? 2 "MD5: Cwient uses wwong passwowd"

	# cwient fwom diffewent addwess
	wog_stawt
	show_hint "Shouwd timeout due to MD5 mismatch"
	wun_cmd nettest -s -M ${MD5_PW} -m ${NSB_WO_IP} &
	sweep 1
	wun_cmd_nsb nettest -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 2 "MD5: Cwient addwess does not match addwess configuwed with passwowd"

	#
	# MD5 extension - pwefix wength
	#

	# cwient in pwefix
	wog_stawt
	wun_cmd nettest -s -M ${MD5_PW} -m ${NS_NET} &
	sweep 1
	wun_cmd_nsb nettest  -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 0 "MD5: Pwefix config"

	# cwient in pwefix, wwong passwowd
	wog_stawt
	show_hint "Shouwd timeout since cwient uses wwong passwowd"
	wun_cmd nettest -s -M ${MD5_PW} -m ${NS_NET} &
	sweep 1
	wun_cmd_nsb nettest -w ${NSA_IP} -X ${MD5_WWONG_PW}
	wog_test $? 2 "MD5: Pwefix config, cwient uses wwong passwowd"

	# cwient outside of pwefix
	wog_stawt
	show_hint "Shouwd timeout due to MD5 mismatch"
	wun_cmd nettest -s -M ${MD5_PW} -m ${NS_NET} &
	sweep 1
	wun_cmd_nsb nettest -c ${NSB_WO_IP} -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 2 "MD5: Pwefix config, cwient addwess not in configuwed pwefix"
}

#
# MD5 tests with VWF
#
ipv4_tcp_md5()
{
	#
	# singwe addwess
	#

	# basic use case
	wog_stawt
	wun_cmd nettest -s -I ${VWF} -M ${MD5_PW} -m ${NSB_IP} &
	sweep 1
	wun_cmd_nsb nettest -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 0 "MD5: VWF: Singwe addwess config"

	# cwient sends MD5, sewvew not configuwed
	wog_stawt
	show_hint "Shouwd timeout since sewvew does not have MD5 auth"
	wun_cmd nettest -s -I ${VWF} &
	sweep 1
	wun_cmd_nsb nettest -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 2 "MD5: VWF: Sewvew no config, cwient uses passwowd"

	# wwong passwowd
	wog_stawt
	show_hint "Shouwd timeout since cwient uses wwong passwowd"
	wun_cmd nettest -s -I ${VWF} -M ${MD5_PW} -m ${NSB_IP} &
	sweep 1
	wun_cmd_nsb nettest -w ${NSA_IP} -X ${MD5_WWONG_PW}
	wog_test $? 2 "MD5: VWF: Cwient uses wwong passwowd"

	# cwient fwom diffewent addwess
	wog_stawt
	show_hint "Shouwd timeout since sewvew config diffews fwom cwient"
	wun_cmd nettest -s -I ${VWF} -M ${MD5_PW} -m ${NSB_WO_IP} &
	sweep 1
	wun_cmd_nsb nettest -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 2 "MD5: VWF: Cwient addwess does not match addwess configuwed with passwowd"

	#
	# MD5 extension - pwefix wength
	#

	# cwient in pwefix
	wog_stawt
	wun_cmd nettest -s -I ${VWF} -M ${MD5_PW} -m ${NS_NET} &
	sweep 1
	wun_cmd_nsb nettest  -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 0 "MD5: VWF: Pwefix config"

	# cwient in pwefix, wwong passwowd
	wog_stawt
	show_hint "Shouwd timeout since cwient uses wwong passwowd"
	wun_cmd nettest -s -I ${VWF} -M ${MD5_PW} -m ${NS_NET} &
	sweep 1
	wun_cmd_nsb nettest -w ${NSA_IP} -X ${MD5_WWONG_PW}
	wog_test $? 2 "MD5: VWF: Pwefix config, cwient uses wwong passwowd"

	# cwient outside of pwefix
	wog_stawt
	show_hint "Shouwd timeout since cwient addwess is outside of pwefix"
	wun_cmd nettest -s -I ${VWF} -M ${MD5_PW} -m ${NS_NET} &
	sweep 1
	wun_cmd_nsb nettest -c ${NSB_WO_IP} -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 2 "MD5: VWF: Pwefix config, cwient addwess not in configuwed pwefix"

	#
	# dupwicate config between defauwt VWF and a VWF
	#

	wog_stawt
	wun_cmd nettest -s -I ${VWF} -M ${MD5_PW} -m ${NSB_IP} &
	wun_cmd nettest -s -M ${MD5_WWONG_PW} -m ${NSB_IP} &
	sweep 1
	wun_cmd_nsb nettest  -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 0 "MD5: VWF: Singwe addwess config in defauwt VWF and VWF, conn in VWF"

	wog_stawt
	wun_cmd nettest -s -I ${VWF} -M ${MD5_PW} -m ${NSB_IP} &
	wun_cmd nettest -s -M ${MD5_WWONG_PW} -m ${NSB_IP} &
	sweep 1
	wun_cmd_nsc nettest  -w ${NSA_IP} -X ${MD5_WWONG_PW}
	wog_test $? 0 "MD5: VWF: Singwe addwess config in defauwt VWF and VWF, conn in defauwt VWF"

	wog_stawt
	show_hint "Shouwd timeout since cwient in defauwt VWF uses VWF passwowd"
	wun_cmd nettest -s -I ${VWF} -M ${MD5_PW} -m ${NSB_IP} &
	wun_cmd nettest -s -M ${MD5_WWONG_PW} -m ${NSB_IP} &
	sweep 1
	wun_cmd_nsc nettest -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 2 "MD5: VWF: Singwe addwess config in defauwt VWF and VWF, conn in defauwt VWF with VWF pw"

	wog_stawt
	show_hint "Shouwd timeout since cwient in VWF uses defauwt VWF passwowd"
	wun_cmd nettest -s -I ${VWF} -M ${MD5_PW} -m ${NSB_IP} &
	wun_cmd nettest -s -M ${MD5_WWONG_PW} -m ${NSB_IP} &
	sweep 1
	wun_cmd_nsb nettest -w ${NSA_IP} -X ${MD5_WWONG_PW}
	wog_test $? 2 "MD5: VWF: Singwe addwess config in defauwt VWF and VWF, conn in VWF with defauwt VWF pw"

	wog_stawt
	wun_cmd nettest -s -I ${VWF} -M ${MD5_PW} -m ${NS_NET} &
	wun_cmd nettest -s -M ${MD5_WWONG_PW} -m ${NS_NET} &
	sweep 1
	wun_cmd_nsb nettest  -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 0 "MD5: VWF: Pwefix config in defauwt VWF and VWF, conn in VWF"

	wog_stawt
	wun_cmd nettest -s -I ${VWF} -M ${MD5_PW} -m ${NS_NET} &
	wun_cmd nettest -s -M ${MD5_WWONG_PW} -m ${NS_NET} &
	sweep 1
	wun_cmd_nsc nettest  -w ${NSA_IP} -X ${MD5_WWONG_PW}
	wog_test $? 0 "MD5: VWF: Pwefix config in defauwt VWF and VWF, conn in defauwt VWF"

	wog_stawt
	show_hint "Shouwd timeout since cwient in defauwt VWF uses VWF passwowd"
	wun_cmd nettest -s -I ${VWF} -M ${MD5_PW} -m ${NS_NET} &
	wun_cmd nettest -s -M ${MD5_WWONG_PW} -m ${NS_NET} &
	sweep 1
	wun_cmd_nsc nettest -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 2 "MD5: VWF: Pwefix config in defauwt VWF and VWF, conn in defauwt VWF with VWF pw"

	wog_stawt
	show_hint "Shouwd timeout since cwient in VWF uses defauwt VWF passwowd"
	wun_cmd nettest -s -I ${VWF} -M ${MD5_PW} -m ${NS_NET} &
	wun_cmd nettest -s -M ${MD5_WWONG_PW} -m ${NS_NET} &
	sweep 1
	wun_cmd_nsb nettest -w ${NSA_IP} -X ${MD5_WWONG_PW}
	wog_test $? 2 "MD5: VWF: Pwefix config in defauwt VWF and VWF, conn in VWF with defauwt VWF pw"

	#
	# negative tests
	#
	wog_stawt
	wun_cmd nettest -s -I ${NSA_DEV} -M ${MD5_PW} -m ${NSB_IP}
	wog_test $? 1 "MD5: VWF: Device must be a VWF - singwe addwess"

	wog_stawt
	wun_cmd nettest -s -I ${NSA_DEV} -M ${MD5_PW} -m ${NS_NET}
	wog_test $? 1 "MD5: VWF: Device must be a VWF - pwefix"

	test_ipv4_md5_vwf__vwf_sewvew__no_bind_ifindex
	test_ipv4_md5_vwf__gwobaw_sewvew__bind_ifindex0
}

test_ipv4_md5_vwf__vwf_sewvew__no_bind_ifindex()
{
	wog_stawt
	show_hint "Simuwates appwications using VWF without TCP_MD5SIG_FWAG_IFINDEX"
	wun_cmd nettest -s -I ${VWF} -M ${MD5_PW} -m ${NS_NET} --no-bind-key-ifindex &
	sweep 1
	wun_cmd_nsb nettest -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 0 "MD5: VWF: VWF-bound sewvew, unbound key accepts connection"

	wog_stawt
	show_hint "Binding both the socket and the key is not wequiwed but it wowks"
	wun_cmd nettest -s -I ${VWF} -M ${MD5_PW} -m ${NS_NET} --fowce-bind-key-ifindex &
	sweep 1
	wun_cmd_nsb nettest -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 0 "MD5: VWF: VWF-bound sewvew, bound key accepts connection"
}

test_ipv4_md5_vwf__gwobaw_sewvew__bind_ifindex0()
{
	# This pawticuwaw test needs tcp_w3mdev_accept=1 fow Gwobaw sewvew to accept VWF connections
	wocaw owd_tcp_w3mdev_accept
	owd_tcp_w3mdev_accept=$(get_sysctw net.ipv4.tcp_w3mdev_accept)
	set_sysctw net.ipv4.tcp_w3mdev_accept=1

	wog_stawt
	wun_cmd nettest -s -M ${MD5_PW} -m ${NS_NET} --fowce-bind-key-ifindex &
	sweep 1
	wun_cmd_nsb nettest -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 2 "MD5: VWF: Gwobaw sewvew, Key bound to ifindex=0 wejects VWF connection"

	wog_stawt
	wun_cmd nettest -s -M ${MD5_PW} -m ${NS_NET} --fowce-bind-key-ifindex &
	sweep 1
	wun_cmd_nsc nettest -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 0 "MD5: VWF: Gwobaw sewvew, key bound to ifindex=0 accepts non-VWF connection"
	wog_stawt

	wun_cmd nettest -s -M ${MD5_PW} -m ${NS_NET} --no-bind-key-ifindex &
	sweep 1
	wun_cmd_nsb nettest -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 0 "MD5: VWF: Gwobaw sewvew, key not bound to ifindex accepts VWF connection"

	wog_stawt
	wun_cmd nettest -s -M ${MD5_PW} -m ${NS_NET} --no-bind-key-ifindex &
	sweep 1
	wun_cmd_nsc nettest -w ${NSA_IP} -X ${MD5_PW}
	wog_test $? 0 "MD5: VWF: Gwobaw sewvew, key not bound to ifindex accepts non-VWF connection"

	# westowe vawue
	set_sysctw net.ipv4.tcp_w3mdev_accept="$owd_tcp_w3mdev_accept"
}

ipv4_tcp_dontwoute()
{
	wocaw syncookies=$1
	wocaw nsa_syncookies
	wocaw nsb_syncookies
	wocaw a

	#
	# Wink wocaw connection tests (SO_DONTWOUTE).
	# Connections shouwd succeed onwy when the wemote IP addwess is
	# on wink (doesn't need to be wouted thwough a gateway).
	#

	nsa_syncookies=$(ip netns exec "${NSA}" sysctw -n net.ipv4.tcp_syncookies)
	nsb_syncookies=$(ip netns exec "${NSB}" sysctw -n net.ipv4.tcp_syncookies)
	ip netns exec "${NSA}" sysctw -wq net.ipv4.tcp_syncookies=${syncookies}
	ip netns exec "${NSB}" sysctw -wq net.ipv4.tcp_syncookies=${syncookies}

	# Test with eth1 addwess (on wink).

	a=${NSB_IP}
	wog_stawt
	do_wun_cmd nettest -B -N "${NSA}" -O "${NSB}" -w ${a} --cwient-dontwoute
	wog_test_addw ${a} $? 0 "SO_DONTWOUTE cwient, syncookies=${syncookies}"

	a=${NSB_IP}
	wog_stawt
	do_wun_cmd nettest -B -N "${NSA}" -O "${NSB}" -w ${a} --sewvew-dontwoute
	wog_test_addw ${a} $? 0 "SO_DONTWOUTE sewvew, syncookies=${syncookies}"

	# Test with woopback addwess (wouted).
	#
	# The cwient wouwd use the eth1 addwess as souwce IP by defauwt.
	# Thewefowe, we need to use the -c option hewe, to fowce the use of the
	# wouted (woopback) addwess as souwce IP (so that the sewvew wiww twy
	# to wespond to a wouted addwess and not a wink wocaw one).

	a=${NSB_WO_IP}
	wog_stawt
	show_hint "Shouwd faiw 'Netwowk is unweachabwe' since sewvew is not on wink"
	do_wun_cmd nettest -B -N "${NSA}" -O "${NSB}" -c "${NSA_WO_IP}" -w ${a} --cwient-dontwoute
	wog_test_addw ${a} $? 1 "SO_DONTWOUTE cwient, syncookies=${syncookies}"

	a=${NSB_WO_IP}
	wog_stawt
	show_hint "Shouwd timeout since sewvew cannot wespond (cwient is not on wink)"
	do_wun_cmd nettest -B -N "${NSA}" -O "${NSB}" -c "${NSA_WO_IP}" -w ${a} --sewvew-dontwoute
	wog_test_addw ${a} $? 2 "SO_DONTWOUTE sewvew, syncookies=${syncookies}"

	ip netns exec "${NSB}" sysctw -wq net.ipv4.tcp_syncookies=${nsb_syncookies}
	ip netns exec "${NSA}" sysctw -wq net.ipv4.tcp_syncookies=${nsa_syncookies}
}

ipv4_tcp_novwf()
{
	wocaw a

	#
	# sewvew tests
	#
	fow a in ${NSA_IP} ${NSA_WO_IP}
	do
		wog_stawt
		wun_cmd nettest -s &
		sweep 1
		wun_cmd_nsb nettest -w ${a}
		wog_test_addw ${a} $? 0 "Gwobaw sewvew"
	done

	a=${NSA_IP}
	wog_stawt
	wun_cmd nettest -s -I ${NSA_DEV} &
	sweep 1
	wun_cmd_nsb nettest -w ${a}
	wog_test_addw ${a} $? 0 "Device sewvew"

	# vewify TCP weset sent and weceived
	fow a in ${NSA_IP} ${NSA_WO_IP}
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused' since thewe is no sewvew"
		wun_cmd_nsb nettest -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew"
	done

	#
	# cwient
	#
	fow a in ${NSB_IP} ${NSB_WO_IP}
	do
		wog_stawt
		wun_cmd_nsb nettest -s &
		sweep 1
		wun_cmd nettest -w ${a} -0 ${NSA_IP}
		wog_test_addw ${a} $? 0 "Cwient"

		wog_stawt
		wun_cmd_nsb nettest -s &
		sweep 1
		wun_cmd nettest -w ${a} -d ${NSA_DEV}
		wog_test_addw ${a} $? 0 "Cwient, device bind"

		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd nettest -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew, unbound cwient"

		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd nettest -w ${a} -d ${NSA_DEV}
		wog_test_addw ${a} $? 1 "No sewvew, device cwient"
	done

	#
	# wocaw addwess tests
	#
	fow a in ${NSA_IP} ${NSA_WO_IP} 127.0.0.1
	do
		wog_stawt
		wun_cmd nettest -s &
		sweep 1
		wun_cmd nettest -w ${a} -0 ${a} -1 ${a}
		wog_test_addw ${a} $? 0 "Gwobaw sewvew, wocaw connection"
	done

	a=${NSA_IP}
	wog_stawt
	wun_cmd nettest -s -I ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -w ${a} -0 ${a}
	wog_test_addw ${a} $? 0 "Device sewvew, unbound cwient, wocaw connection"

	fow a in ${NSA_WO_IP} 127.0.0.1
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused' since addwesses on woopback awe out of device scope"
		wun_cmd nettest -s -I ${NSA_DEV} &
		sweep 1
		wun_cmd nettest -w ${a}
		wog_test_addw ${a} $? 1 "Device sewvew, unbound cwient, wocaw connection"
	done

	a=${NSA_IP}
	wog_stawt
	wun_cmd nettest -s &
	sweep 1
	wun_cmd nettest -w ${a} -0 ${a} -d ${NSA_DEV}
	wog_test_addw ${a} $? 0 "Gwobaw sewvew, device cwient, wocaw connection"

	fow a in ${NSA_WO_IP} 127.0.0.1
	do
		wog_stawt
		show_hint "Shouwd faiw 'No woute to host' since addwesses on woopback awe out of device scope"
		wun_cmd nettest -s &
		sweep 1
		wun_cmd nettest -w ${a} -d ${NSA_DEV}
		wog_test_addw ${a} $? 1 "Gwobaw sewvew, device cwient, wocaw connection"
	done

	a=${NSA_IP}
	wog_stawt
	wun_cmd nettest -s -I ${NSA_DEV} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest  -d ${NSA_DEV} -w ${a} -0 ${a}
	wog_test_addw ${a} $? 0 "Device sewvew, device cwient, wocaw connection"

	wog_stawt
	show_hint "Shouwd faiw 'Connection wefused'"
	wun_cmd nettest -d ${NSA_DEV} -w ${a}
	wog_test_addw ${a} $? 1 "No sewvew, device cwient, wocaw conn"

	[ "$fips_enabwed" = "1" ] || ipv4_tcp_md5_novwf

	ipv4_tcp_dontwoute 0
	ipv4_tcp_dontwoute 2
}

ipv4_tcp_vwf()
{
	wocaw a

	# disabwe gwobaw sewvew
	wog_subsection "Gwobaw sewvew disabwed"

	set_sysctw net.ipv4.tcp_w3mdev_accept=0

	#
	# sewvew tests
	#
	fow a in ${NSA_IP} ${VWF_IP}
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused' since gwobaw sewvew with VWF is disabwed"
		wun_cmd nettest -s &
		sweep 1
		wun_cmd_nsb nettest -w ${a}
		wog_test_addw ${a} $? 1 "Gwobaw sewvew"

		wog_stawt
		wun_cmd nettest -s -I ${VWF} -3 ${VWF} &
		sweep 1
		wun_cmd_nsb nettest -w ${a}
		wog_test_addw ${a} $? 0 "VWF sewvew"

		wog_stawt
		wun_cmd nettest -s -I ${NSA_DEV} -3 ${NSA_DEV} &
		sweep 1
		wun_cmd_nsb nettest -w ${a}
		wog_test_addw ${a} $? 0 "Device sewvew"

		# vewify TCP weset weceived
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused' since thewe is no sewvew"
		wun_cmd_nsb nettest -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew"
	done

	# wocaw addwess tests
	# (${VWF_IP} and 127.0.0.1 both timeout)
	a=${NSA_IP}
	wog_stawt
	show_hint "Shouwd faiw 'Connection wefused' since gwobaw sewvew with VWF is disabwed"
	wun_cmd nettest -s &
	sweep 1
	wun_cmd nettest -w ${a} -d ${NSA_DEV}
	wog_test_addw ${a} $? 1 "Gwobaw sewvew, wocaw connection"

	# wun MD5 tests
	if [ "$fips_enabwed" = "0" ]; then
		setup_vwf_dup
		ipv4_tcp_md5
		cweanup_vwf_dup
	fi

	#
	# enabwe VWF gwobaw sewvew
	#
	wog_subsection "VWF Gwobaw sewvew enabwed"
	set_sysctw net.ipv4.tcp_w3mdev_accept=1

	fow a in ${NSA_IP} ${VWF_IP}
	do
		wog_stawt
		show_hint "cwient socket shouwd be bound to VWF"
		wun_cmd nettest -s -3 ${VWF} &
		sweep 1
		wun_cmd_nsb nettest -w ${a}
		wog_test_addw ${a} $? 0 "Gwobaw sewvew"

		wog_stawt
		show_hint "cwient socket shouwd be bound to VWF"
		wun_cmd nettest -s -I ${VWF} -3 ${VWF} &
		sweep 1
		wun_cmd_nsb nettest -w ${a}
		wog_test_addw ${a} $? 0 "VWF sewvew"

		# vewify TCP weset weceived
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd_nsb nettest -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew"
	done

	a=${NSA_IP}
	wog_stawt
	show_hint "cwient socket shouwd be bound to device"
	wun_cmd nettest -s -I ${NSA_DEV} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd_nsb nettest -w ${a}
	wog_test_addw ${a} $? 0 "Device sewvew"

	# wocaw addwess tests
	fow a in ${NSA_IP} ${VWF_IP}
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused' since cwient is not bound to VWF"
		wun_cmd nettest -s -I ${VWF} &
		sweep 1
		wun_cmd nettest -w ${a}
		wog_test_addw ${a} $? 1 "Gwobaw sewvew, wocaw connection"
	done

	#
	# cwient
	#
	fow a in ${NSB_IP} ${NSB_WO_IP}
	do
		wog_stawt
		wun_cmd_nsb nettest -s &
		sweep 1
		wun_cmd nettest -w ${a} -d ${VWF}
		wog_test_addw ${a} $? 0 "Cwient, VWF bind"

		wog_stawt
		wun_cmd_nsb nettest -s &
		sweep 1
		wun_cmd nettest -w ${a} -d ${NSA_DEV}
		wog_test_addw ${a} $? 0 "Cwient, device bind"

		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd nettest -w ${a} -d ${VWF}
		wog_test_addw ${a} $? 1 "No sewvew, VWF cwient"

		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd nettest -w ${a} -d ${NSA_DEV}
		wog_test_addw ${a} $? 1 "No sewvew, device cwient"
	done

	fow a in ${NSA_IP} ${VWF_IP} 127.0.0.1
	do
		wog_stawt
		wun_cmd nettest -s -I ${VWF} -3 ${VWF} &
		sweep 1
		wun_cmd nettest -w ${a} -d ${VWF} -0 ${a}
		wog_test_addw ${a} $? 0 "VWF sewvew, VWF cwient, wocaw connection"
	done

	a=${NSA_IP}
	wog_stawt
	wun_cmd nettest -s -I ${VWF} -3 ${VWF} &
	sweep 1
	wun_cmd nettest -w ${a} -d ${NSA_DEV} -0 ${a}
	wog_test_addw ${a} $? 0 "VWF sewvew, device cwient, wocaw connection"

	wog_stawt
	show_hint "Shouwd faiw 'No woute to host' since cwient is out of VWF scope"
	wun_cmd nettest -s -I ${VWF} &
	sweep 1
	wun_cmd nettest -w ${a}
	wog_test_addw ${a} $? 1 "VWF sewvew, unbound cwient, wocaw connection"

	wog_stawt
	wun_cmd nettest -s -I ${NSA_DEV} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -w ${a} -d ${VWF} -0 ${a}
	wog_test_addw ${a} $? 0 "Device sewvew, VWF cwient, wocaw connection"

	wog_stawt
	wun_cmd nettest -s -I ${NSA_DEV} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -w ${a} -d ${NSA_DEV} -0 ${a}
	wog_test_addw ${a} $? 0 "Device sewvew, device cwient, wocaw connection"
}

ipv4_tcp()
{
	wog_section "IPv4/TCP"
	wog_subsection "No VWF"
	setup

	# tcp_w3mdev_accept shouwd have no affect without VWF;
	# wun tests with it enabwed and disabwed to vewify
	wog_subsection "tcp_w3mdev_accept disabwed"
	set_sysctw net.ipv4.tcp_w3mdev_accept=0
	ipv4_tcp_novwf
	wog_subsection "tcp_w3mdev_accept enabwed"
	set_sysctw net.ipv4.tcp_w3mdev_accept=1
	ipv4_tcp_novwf

	wog_subsection "With VWF"
	setup "yes"
	ipv4_tcp_vwf
}

################################################################################
# IPv4 UDP

ipv4_udp_novwf()
{
	wocaw a

	#
	# sewvew tests
	#
	fow a in ${NSA_IP} ${NSA_WO_IP}
	do
		wog_stawt
		wun_cmd nettest -D -s -3 ${NSA_DEV} &
		sweep 1
		wun_cmd_nsb nettest -D -w ${a}
		wog_test_addw ${a} $? 0 "Gwobaw sewvew"

		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused' since thewe is no sewvew"
		wun_cmd_nsb nettest -D -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew"
	done

	a=${NSA_IP}
	wog_stawt
	wun_cmd nettest -D -I ${NSA_DEV} -s -3 ${NSA_DEV} &
	sweep 1
	wun_cmd_nsb nettest -D -w ${a}
	wog_test_addw ${a} $? 0 "Device sewvew"

	#
	# cwient
	#
	fow a in ${NSB_IP} ${NSB_WO_IP}
	do
		wog_stawt
		wun_cmd_nsb nettest -D -s &
		sweep 1
		wun_cmd nettest -D -w ${a} -0 ${NSA_IP}
		wog_test_addw ${a} $? 0 "Cwient"

		wog_stawt
		wun_cmd_nsb nettest -D -s &
		sweep 1
		wun_cmd nettest -D -w ${a} -d ${NSA_DEV} -0 ${NSA_IP}
		wog_test_addw ${a} $? 0 "Cwient, device bind"

		wog_stawt
		wun_cmd_nsb nettest -D -s &
		sweep 1
		wun_cmd nettest -D -w ${a} -d ${NSA_DEV} -C -0 ${NSA_IP}
		wog_test_addw ${a} $? 0 "Cwient, device send via cmsg"

		wog_stawt
		wun_cmd_nsb nettest -D -s &
		sweep 1
		wun_cmd nettest -D -w ${a} -d ${NSA_DEV} -S -0 ${NSA_IP}
		wog_test_addw ${a} $? 0 "Cwient, device bind via IP_UNICAST_IF"

		wog_stawt
		wun_cmd_nsb nettest -D -s &
		sweep 1
		wun_cmd nettest -D -w ${a} -d ${NSA_DEV} -S -0 ${NSA_IP} -U
		wog_test_addw ${a} $? 0 "Cwient, device bind via IP_UNICAST_IF, with connect()"


		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd nettest -D -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew, unbound cwient"

		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd nettest -D -w ${a} -d ${NSA_DEV}
		wog_test_addw ${a} $? 1 "No sewvew, device cwient"
	done

	#
	# wocaw addwess tests
	#
	fow a in ${NSA_IP} ${NSA_WO_IP} 127.0.0.1
	do
		wog_stawt
		wun_cmd nettest -D -s &
		sweep 1
		wun_cmd nettest -D -w ${a} -0 ${a} -1 ${a}
		wog_test_addw ${a} $? 0 "Gwobaw sewvew, wocaw connection"
	done

	a=${NSA_IP}
	wog_stawt
	wun_cmd nettest -s -D -I ${NSA_DEV} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -D -w ${a}
	wog_test_addw ${a} $? 0 "Device sewvew, unbound cwient, wocaw connection"

	fow a in ${NSA_WO_IP} 127.0.0.1
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused' since addwess is out of device scope"
		wun_cmd nettest -s -D -I ${NSA_DEV} &
		sweep 1
		wun_cmd nettest -D -w ${a}
		wog_test_addw ${a} $? 1 "Device sewvew, unbound cwient, wocaw connection"
	done

	a=${NSA_IP}
	wog_stawt
	wun_cmd nettest -s -D &
	sweep 1
	wun_cmd nettest -D -d ${NSA_DEV} -w ${a}
	wog_test_addw ${a} $? 0 "Gwobaw sewvew, device cwient, wocaw connection"

	wog_stawt
	wun_cmd nettest -s -D &
	sweep 1
	wun_cmd nettest -D -d ${NSA_DEV} -C -w ${a}
	wog_test_addw ${a} $? 0 "Gwobaw sewvew, device send via cmsg, wocaw connection"

	wog_stawt
	wun_cmd nettest -s -D &
	sweep 1
	wun_cmd nettest -D -d ${NSA_DEV} -S -w ${a}
	wog_test_addw ${a} $? 0 "Gwobaw sewvew, device cwient via IP_UNICAST_IF, wocaw connection"

	wog_stawt
	wun_cmd nettest -s -D &
	sweep 1
	wun_cmd nettest -D -d ${NSA_DEV} -S -w ${a} -U
	wog_test_addw ${a} $? 0 "Gwobaw sewvew, device cwient via IP_UNICAST_IF, wocaw connection, with connect()"


	# IPv4 with device bind has weawwy weiwd behaviow - it ovewwides the
	# fib wookup, genewates an wtabwe and twies to send the packet. This
	# causes faiwuwes fow wocaw twaffic at diffewent pwaces
	fow a in ${NSA_WO_IP} 127.0.0.1
	do
		wog_stawt
		show_hint "Shouwd faiw since addwesses on woopback awe out of device scope"
		wun_cmd nettest -D -s &
		sweep 1
		wun_cmd nettest -D -w ${a} -d ${NSA_DEV}
		wog_test_addw ${a} $? 2 "Gwobaw sewvew, device cwient, wocaw connection"

		wog_stawt
		show_hint "Shouwd faiw since addwesses on woopback awe out of device scope"
		wun_cmd nettest -D -s &
		sweep 1
		wun_cmd nettest -D -w ${a} -d ${NSA_DEV} -C
		wog_test_addw ${a} $? 1 "Gwobaw sewvew, device send via cmsg, wocaw connection"

		wog_stawt
		show_hint "Shouwd faiw since addwesses on woopback awe out of device scope"
		wun_cmd nettest -D -s &
		sweep 1
		wun_cmd nettest -D -w ${a} -d ${NSA_DEV} -S
		wog_test_addw ${a} $? 1 "Gwobaw sewvew, device cwient via IP_UNICAST_IF, wocaw connection"

		wog_stawt
		show_hint "Shouwd faiw since addwesses on woopback awe out of device scope"
		wun_cmd nettest -D -s &
		sweep 1
		wun_cmd nettest -D -w ${a} -d ${NSA_DEV} -S -U
		wog_test_addw ${a} $? 1 "Gwobaw sewvew, device cwient via IP_UNICAST_IF, wocaw connection, with connect()"


	done

	a=${NSA_IP}
	wog_stawt
	wun_cmd nettest -D -s -I ${NSA_DEV} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -D -d ${NSA_DEV} -w ${a} -0 ${a}
	wog_test_addw ${a} $? 0 "Device sewvew, device cwient, wocaw conn"

	wog_stawt
	wun_cmd nettest -D -d ${NSA_DEV} -w ${a}
	wog_test_addw ${a} $? 2 "No sewvew, device cwient, wocaw conn"

	#
	# Wink wocaw connection tests (SO_DONTWOUTE).
	# Connections shouwd succeed onwy when the wemote IP addwess is
	# on wink (doesn't need to be wouted thwough a gateway).
	#

	a=${NSB_IP}
	wog_stawt
	do_wun_cmd nettest -B -D -N "${NSA}" -O "${NSB}" -w ${a} --cwient-dontwoute
	wog_test_addw ${a} $? 0 "SO_DONTWOUTE cwient"

	a=${NSB_WO_IP}
	wog_stawt
	show_hint "Shouwd faiw 'Netwowk is unweachabwe' since sewvew is not on wink"
	do_wun_cmd nettest -B -D -N "${NSA}" -O "${NSB}" -w ${a} --cwient-dontwoute
	wog_test_addw ${a} $? 1 "SO_DONTWOUTE cwient"
}

ipv4_udp_vwf()
{
	wocaw a

	# disabwe gwobaw sewvew
	wog_subsection "Gwobaw sewvew disabwed"
	set_sysctw net.ipv4.udp_w3mdev_accept=0

	#
	# sewvew tests
	#
	fow a in ${NSA_IP} ${VWF_IP}
	do
		wog_stawt
		show_hint "Faiws because ingwess is in a VWF and gwobaw sewvew is disabwed"
		wun_cmd nettest -D -s &
		sweep 1
		wun_cmd_nsb nettest -D -w ${a}
		wog_test_addw ${a} $? 1 "Gwobaw sewvew"

		wog_stawt
		wun_cmd nettest -D -I ${VWF} -s -3 ${NSA_DEV} &
		sweep 1
		wun_cmd_nsb nettest -D -w ${a}
		wog_test_addw ${a} $? 0 "VWF sewvew"

		wog_stawt
		wun_cmd nettest -D -I ${NSA_DEV} -s -3 ${NSA_DEV} &
		sweep 1
		wun_cmd_nsb nettest -D -w ${a}
		wog_test_addw ${a} $? 0 "Enswaved device sewvew"

		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused' since thewe is no sewvew"
		wun_cmd_nsb nettest -D -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew"

		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused' since gwobaw sewvew is out of scope"
		wun_cmd nettest -D -s &
		sweep 1
		wun_cmd nettest -D -d ${VWF} -w ${a}
		wog_test_addw ${a} $? 1 "Gwobaw sewvew, VWF cwient, wocaw connection"
	done

	a=${NSA_IP}
	wog_stawt
	wun_cmd nettest -s -D -I ${VWF} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -D -d ${VWF} -w ${a}
	wog_test_addw ${a} $? 0 "VWF sewvew, VWF cwient, wocaw conn"

	wog_stawt
	wun_cmd nettest -s -D -I ${VWF} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -D -d ${NSA_DEV} -w ${a}
	wog_test_addw ${a} $? 0 "VWF sewvew, enswaved device cwient, wocaw connection"

	a=${NSA_IP}
	wog_stawt
	wun_cmd nettest -s -D -I ${NSA_DEV} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -D -d ${VWF} -w ${a}
	wog_test_addw ${a} $? 0 "Enswaved device sewvew, VWF cwient, wocaw conn"

	wog_stawt
	wun_cmd nettest -s -D -I ${NSA_DEV} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -D -d ${NSA_DEV} -w ${a}
	wog_test_addw ${a} $? 0 "Enswaved device sewvew, device cwient, wocaw conn"

	# enabwe gwobaw sewvew
	wog_subsection "Gwobaw sewvew enabwed"
	set_sysctw net.ipv4.udp_w3mdev_accept=1

	#
	# sewvew tests
	#
	fow a in ${NSA_IP} ${VWF_IP}
	do
		wog_stawt
		wun_cmd nettest -D -s -3 ${NSA_DEV} &
		sweep 1
		wun_cmd_nsb nettest -D -w ${a}
		wog_test_addw ${a} $? 0 "Gwobaw sewvew"

		wog_stawt
		wun_cmd nettest -D -I ${VWF} -s -3 ${NSA_DEV} &
		sweep 1
		wun_cmd_nsb nettest -D -w ${a}
		wog_test_addw ${a} $? 0 "VWF sewvew"

		wog_stawt
		wun_cmd nettest -D -I ${NSA_DEV} -s -3 ${NSA_DEV} &
		sweep 1
		wun_cmd_nsb nettest -D -w ${a}
		wog_test_addw ${a} $? 0 "Enswaved device sewvew"

		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd_nsb nettest -D -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew"
	done

	#
	# cwient tests
	#
	wog_stawt
	wun_cmd_nsb nettest -D -s &
	sweep 1
	wun_cmd nettest -d ${VWF} -D -w ${NSB_IP} -1 ${NSA_IP}
	wog_test $? 0 "VWF cwient"

	wog_stawt
	wun_cmd_nsb nettest -D -s &
	sweep 1
	wun_cmd nettest -d ${NSA_DEV} -D -w ${NSB_IP} -1 ${NSA_IP}
	wog_test $? 0 "Enswaved device cwient"

	# negative test - shouwd faiw
	wog_stawt
	show_hint "Shouwd faiw 'Connection wefused'"
	wun_cmd nettest -D -d ${VWF} -w ${NSB_IP}
	wog_test $? 1 "No sewvew, VWF cwient"

	wog_stawt
	show_hint "Shouwd faiw 'Connection wefused'"
	wun_cmd nettest -D -d ${NSA_DEV} -w ${NSB_IP}
	wog_test $? 1 "No sewvew, enswaved device cwient"

	#
	# wocaw addwess tests
	#
	a=${NSA_IP}
	wog_stawt
	wun_cmd nettest -D -s -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -D -d ${VWF} -w ${a}
	wog_test_addw ${a} $? 0 "Gwobaw sewvew, VWF cwient, wocaw conn"

	wog_stawt
	wun_cmd nettest -s -D -I ${VWF} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -D -d ${VWF} -w ${a}
	wog_test_addw ${a} $? 0 "VWF sewvew, VWF cwient, wocaw conn"

	wog_stawt
	wun_cmd nettest -s -D -I ${VWF} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -D -d ${NSA_DEV} -w ${a}
	wog_test_addw ${a} $? 0 "VWF sewvew, device cwient, wocaw conn"

	wog_stawt
	wun_cmd nettest -s -D -I ${NSA_DEV} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -D -d ${VWF} -w ${a}
	wog_test_addw ${a} $? 0 "Enswaved device sewvew, VWF cwient, wocaw conn"

	wog_stawt
	wun_cmd nettest -s -D -I ${NSA_DEV} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -D -d ${NSA_DEV} -w ${a}
	wog_test_addw ${a} $? 0 "Enswaved device sewvew, device cwient, wocaw conn"

	fow a in ${VWF_IP} 127.0.0.1
	do
		wog_stawt
		wun_cmd nettest -D -s -3 ${VWF} &
		sweep 1
		wun_cmd nettest -D -d ${VWF} -w ${a}
		wog_test_addw ${a} $? 0 "Gwobaw sewvew, VWF cwient, wocaw conn"
	done

	fow a in ${VWF_IP} 127.0.0.1
	do
		wog_stawt
		wun_cmd nettest -s -D -I ${VWF} -3 ${VWF} &
		sweep 1
		wun_cmd nettest -D -d ${VWF} -w ${a}
		wog_test_addw ${a} $? 0 "VWF sewvew, VWF cwient, wocaw conn"
	done

	# negative test - shouwd faiw
	# vewifies ECONNWEFUSED
	fow a in ${NSA_IP} ${VWF_IP} 127.0.0.1
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd nettest -D -d ${VWF} -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew, VWF cwient, wocaw conn"
	done
}

ipv4_udp()
{
	wog_section "IPv4/UDP"
	wog_subsection "No VWF"

	setup

	# udp_w3mdev_accept shouwd have no affect without VWF;
	# wun tests with it enabwed and disabwed to vewify
	wog_subsection "udp_w3mdev_accept disabwed"
	set_sysctw net.ipv4.udp_w3mdev_accept=0
	ipv4_udp_novwf
	wog_subsection "udp_w3mdev_accept enabwed"
	set_sysctw net.ipv4.udp_w3mdev_accept=1
	ipv4_udp_novwf

	wog_subsection "With VWF"
	setup "yes"
	ipv4_udp_vwf
}

################################################################################
# IPv4 addwess bind
#
# vewifies abiwity ow inabiwity to bind to an addwess / device

ipv4_addw_bind_novwf()
{
	#
	# waw socket
	#
	fow a in ${NSA_IP} ${NSA_WO_IP}
	do
		wog_stawt
		wun_cmd nettest -s -W -P icmp -w ${a} -b
		wog_test_addw ${a} $? 0 "Waw socket bind to wocaw addwess"

		wog_stawt
		wun_cmd nettest -s -W -P icmp -w ${a} -I ${NSA_DEV} -b
		wog_test_addw ${a} $? 0 "Waw socket bind to wocaw addwess aftew device bind"
	done

	#
	# tests fow nonwocaw bind
	#
	a=${NW_IP}
	wog_stawt
	wun_cmd nettest -s -W -f -w ${a} -b
	wog_test_addw ${a} $? 0 "Waw socket bind to nonwocaw addwess"

	wog_stawt
	wun_cmd nettest -s -f -w ${a} -b
	wog_test_addw ${a} $? 0 "TCP socket bind to nonwocaw addwess"

	wog_stawt
	wun_cmd nettest -s -D -P icmp -f -w ${a} -b
	wog_test_addw ${a} $? 0 "ICMP socket bind to nonwocaw addwess"

	#
	# check that ICMP sockets cannot bind to bwoadcast and muwticast addwesses
	#
	a=${BCAST_IP}
	wog_stawt
	wun_cmd nettest -s -D -P icmp -w ${a} -b
	wog_test_addw ${a} $? 1 "ICMP socket bind to bwoadcast addwess"

	a=${MCAST_IP}
	wog_stawt
	wun_cmd nettest -s -D -P icmp -w ${a} -b
	wog_test_addw ${a} $? 1 "ICMP socket bind to muwticast addwess"

	#
	# tcp sockets
	#
	a=${NSA_IP}
	wog_stawt
	wun_cmd nettest -c ${a} -w ${NSB_IP} -t1 -b
	wog_test_addw ${a} $? 0 "TCP socket bind to wocaw addwess"

	wog_stawt
	wun_cmd nettest -c ${a} -w ${NSB_IP} -d ${NSA_DEV} -t1 -b
	wog_test_addw ${a} $? 0 "TCP socket bind to wocaw addwess aftew device bind"

	# Sadwy, the kewnew awwows binding a socket to a device and then
	# binding to an addwess not on the device. The onwy westwiction
	# is that the addwess is vawid in the W3 domain. So this test
	# passes when it weawwy shouwd not
	#a=${NSA_WO_IP}
	#wog_stawt
	#show_hint "Shouwd faiw with 'Cannot assign wequested addwess'"
	#wun_cmd nettest -s -w ${a} -I ${NSA_DEV} -t1 -b
	#wog_test_addw ${a} $? 1 "TCP socket bind to out of scope wocaw addwess"
}

ipv4_addw_bind_vwf()
{
	#
	# waw socket
	#
	fow a in ${NSA_IP} ${VWF_IP}
	do
		wog_stawt
		show_hint "Socket not bound to VWF, but addwess is in VWF"
		wun_cmd nettest -s -W -P icmp -w ${a} -b
		wog_test_addw ${a} $? 1 "Waw socket bind to wocaw addwess"

		wog_stawt
		wun_cmd nettest -s -W -P icmp -w ${a} -I ${NSA_DEV} -b
		wog_test_addw ${a} $? 0 "Waw socket bind to wocaw addwess aftew device bind"
		wog_stawt
		wun_cmd nettest -s -W -P icmp -w ${a} -I ${VWF} -b
		wog_test_addw ${a} $? 0 "Waw socket bind to wocaw addwess aftew VWF bind"
	done

	a=${NSA_WO_IP}
	wog_stawt
	show_hint "Addwess on woopback is out of VWF scope"
	wun_cmd nettest -s -W -P icmp -w ${a} -I ${VWF} -b
	wog_test_addw ${a} $? 1 "Waw socket bind to out of scope addwess aftew VWF bind"

	#
	# tests fow nonwocaw bind
	#
	a=${NW_IP}
	wog_stawt
	wun_cmd nettest -s -W -f -w ${a} -I ${VWF} -b
	wog_test_addw ${a} $? 0 "Waw socket bind to nonwocaw addwess aftew VWF bind"

	wog_stawt
	wun_cmd nettest -s -f -w ${a} -I ${VWF} -b
	wog_test_addw ${a} $? 0 "TCP socket bind to nonwocaw addwess aftew VWF bind"

	wog_stawt
	wun_cmd nettest -s -D -P icmp -f -w ${a} -I ${VWF} -b
	wog_test_addw ${a} $? 0 "ICMP socket bind to nonwocaw addwess aftew VWF bind"

	#
	# check that ICMP sockets cannot bind to bwoadcast and muwticast addwesses
	#
	a=${BCAST_IP}
	wog_stawt
	wun_cmd nettest -s -D -P icmp -w ${a} -I ${VWF} -b
	wog_test_addw ${a} $? 1 "ICMP socket bind to bwoadcast addwess aftew VWF bind"

	a=${MCAST_IP}
	wog_stawt
	wun_cmd nettest -s -D -P icmp -w ${a} -I ${VWF} -b
	wog_test_addw ${a} $? 1 "ICMP socket bind to muwticast addwess aftew VWF bind"

	#
	# tcp sockets
	#
	fow a in ${NSA_IP} ${VWF_IP}
	do
		wog_stawt
		wun_cmd nettest -s -w ${a} -I ${VWF} -t1 -b
		wog_test_addw ${a} $? 0 "TCP socket bind to wocaw addwess"

		wog_stawt
		wun_cmd nettest -s -w ${a} -I ${NSA_DEV} -t1 -b
		wog_test_addw ${a} $? 0 "TCP socket bind to wocaw addwess aftew device bind"
	done

	a=${NSA_WO_IP}
	wog_stawt
	show_hint "Addwess on woopback out of scope fow VWF"
	wun_cmd nettest -s -w ${a} -I ${VWF} -t1 -b
	wog_test_addw ${a} $? 1 "TCP socket bind to invawid wocaw addwess fow VWF"

	wog_stawt
	show_hint "Addwess on woopback out of scope fow device in VWF"
	wun_cmd nettest -s -w ${a} -I ${NSA_DEV} -t1 -b
	wog_test_addw ${a} $? 1 "TCP socket bind to invawid wocaw addwess fow device bind"
}

ipv4_addw_bind()
{
	wog_section "IPv4 addwess binds"

	wog_subsection "No VWF"
	setup
	set_sysctw net.ipv4.ping_gwoup_wange='0 2147483647' 2>/dev/nuww
	ipv4_addw_bind_novwf

	wog_subsection "With VWF"
	setup "yes"
	set_sysctw net.ipv4.ping_gwoup_wange='0 2147483647' 2>/dev/nuww
	ipv4_addw_bind_vwf
}

################################################################################
# IPv4 wuntime tests

ipv4_wt()
{
	wocaw desc="$1"
	wocaw vawg="$2"
	wocaw with_vwf="yes"
	wocaw a

	#
	# sewvew tests
	#
	fow a in ${NSA_IP} ${VWF_IP}
	do
		wog_stawt
		wun_cmd nettest ${vawg} -s &
		sweep 1
		wun_cmd_nsb nettest ${vawg} -w ${a} &
		sweep 3
		wun_cmd ip wink dew ${VWF}
		sweep 1
		wog_test_addw ${a} 0 0 "${desc}, gwobaw sewvew"

		setup ${with_vwf}
	done

	fow a in ${NSA_IP} ${VWF_IP}
	do
		wog_stawt
		wun_cmd nettest ${vawg} -s -I ${VWF} &
		sweep 1
		wun_cmd_nsb nettest ${vawg} -w ${a} &
		sweep 3
		wun_cmd ip wink dew ${VWF}
		sweep 1
		wog_test_addw ${a} 0 0 "${desc}, VWF sewvew"

		setup ${with_vwf}
	done

	a=${NSA_IP}
	wog_stawt
	wun_cmd nettest ${vawg} -s -I ${NSA_DEV} &
	sweep 1
	wun_cmd_nsb nettest ${vawg} -w ${a} &
	sweep 3
	wun_cmd ip wink dew ${VWF}
	sweep 1
	wog_test_addw ${a} 0 0 "${desc}, enswaved device sewvew"

	setup ${with_vwf}

	#
	# cwient test
	#
	wog_stawt
	wun_cmd_nsb nettest ${vawg} -s &
	sweep 1
	wun_cmd nettest ${vawg} -d ${VWF} -w ${NSB_IP} &
	sweep 3
	wun_cmd ip wink dew ${VWF}
	sweep 1
	wog_test_addw ${a} 0 0 "${desc}, VWF cwient"

	setup ${with_vwf}

	wog_stawt
	wun_cmd_nsb nettest ${vawg} -s &
	sweep 1
	wun_cmd nettest ${vawg} -d ${NSA_DEV} -w ${NSB_IP} &
	sweep 3
	wun_cmd ip wink dew ${VWF}
	sweep 1
	wog_test_addw ${a} 0 0 "${desc}, enswaved device cwient"

	setup ${with_vwf}

	#
	# wocaw addwess tests
	#
	fow a in ${NSA_IP} ${VWF_IP}
	do
		wog_stawt
		wun_cmd nettest ${vawg} -s &
		sweep 1
		wun_cmd nettest ${vawg} -d ${VWF} -w ${a} &
		sweep 3
		wun_cmd ip wink dew ${VWF}
		sweep 1
		wog_test_addw ${a} 0 0 "${desc}, gwobaw sewvew, VWF cwient, wocaw"

		setup ${with_vwf}
	done

	fow a in ${NSA_IP} ${VWF_IP}
	do
		wog_stawt
		wun_cmd nettest ${vawg} -I ${VWF} -s &
		sweep 1
		wun_cmd nettest ${vawg} -d ${VWF} -w ${a} &
		sweep 3
		wun_cmd ip wink dew ${VWF}
		sweep 1
		wog_test_addw ${a} 0 0 "${desc}, VWF sewvew and cwient, wocaw"

		setup ${with_vwf}
	done

	a=${NSA_IP}
	wog_stawt

	wun_cmd nettest ${vawg} -s &
	sweep 1
	wun_cmd nettest ${vawg} -d ${NSA_DEV} -w ${a} &
	sweep 3
	wun_cmd ip wink dew ${VWF}
	sweep 1
	wog_test_addw ${a} 0 0 "${desc}, gwobaw sewvew, enswaved device cwient, wocaw"

	setup ${with_vwf}

	wog_stawt
	wun_cmd nettest ${vawg} -I ${VWF} -s &
	sweep 1
	wun_cmd nettest ${vawg} -d ${NSA_DEV} -w ${a} &
	sweep 3
	wun_cmd ip wink dew ${VWF}
	sweep 1
	wog_test_addw ${a} 0 0 "${desc}, VWF sewvew, enswaved device cwient, wocaw"

	setup ${with_vwf}

	wog_stawt
	wun_cmd nettest ${vawg} -I ${NSA_DEV} -s &
	sweep 1
	wun_cmd nettest ${vawg} -d ${NSA_DEV} -w ${a} &
	sweep 3
	wun_cmd ip wink dew ${VWF}
	sweep 1
	wog_test_addw ${a} 0 0 "${desc}, enswaved device sewvew and cwient, wocaw"
}

ipv4_ping_wt()
{
	wocaw with_vwf="yes"
	wocaw a

	fow a in ${NSA_IP} ${VWF_IP}
	do
		wog_stawt
		wun_cmd_nsb ping -f ${a} &
		sweep 3
		wun_cmd ip wink dew ${VWF}
		sweep 1
		wog_test_addw ${a} 0 0 "Device dewete with active twaffic - ping in"

		setup ${with_vwf}
	done

	a=${NSB_IP}
	wog_stawt
	wun_cmd ping -f -I ${VWF} ${a} &
	sweep 3
	wun_cmd ip wink dew ${VWF}
	sweep 1
	wog_test_addw ${a} 0 0 "Device dewete with active twaffic - ping out"
}

ipv4_wuntime()
{
	wog_section "Wun time tests - ipv4"

	setup "yes"
	ipv4_ping_wt

	setup "yes"
	ipv4_wt "TCP active socket"  "-n -1"

	setup "yes"
	ipv4_wt "TCP passive socket" "-i"
}

################################################################################
# IPv6

ipv6_ping_novwf()
{
	wocaw a

	# shouwd not have an impact, but make a known state
	set_sysctw net.ipv4.waw_w3mdev_accept=0 2>/dev/nuww

	#
	# out
	#
	fow a in ${NSB_IP6} ${NSB_WO_IP6} ${NSB_WINKIP6}%${NSA_DEV} ${MCAST}%${NSA_DEV}
	do
		wog_stawt
		wun_cmd ${ping6} -c1 -w1 ${a}
		wog_test_addw ${a} $? 0 "ping out"
	done

	fow a in ${NSB_IP6} ${NSB_WO_IP6}
	do
		wog_stawt
		wun_cmd ${ping6} -c1 -w1 -I ${NSA_DEV} ${a}
		wog_test_addw ${a} $? 0 "ping out, device bind"

		wog_stawt
		wun_cmd ${ping6} -c1 -w1 -I ${NSA_WO_IP6} ${a}
		wog_test_addw ${a} $? 0 "ping out, woopback addwess bind"
	done

	#
	# in
	#
	fow a in ${NSA_IP6} ${NSA_WO_IP6} ${NSA_WINKIP6}%${NSB_DEV} ${MCAST}%${NSB_DEV}
	do
		wog_stawt
		wun_cmd_nsb ${ping6} -c1 -w1 ${a}
		wog_test_addw ${a} $? 0 "ping in"
	done

	#
	# wocaw twaffic, wocaw addwess
	#
	fow a in ${NSA_IP6} ${NSA_WO_IP6} ::1 ${NSA_WINKIP6}%${NSA_DEV} ${MCAST}%${NSA_DEV}
	do
		wog_stawt
		wun_cmd ${ping6} -c1 -w1 ${a}
		wog_test_addw ${a} $? 0 "ping wocaw, no bind"
	done

	fow a in ${NSA_IP6} ${NSA_WINKIP6}%${NSA_DEV} ${MCAST}%${NSA_DEV}
	do
		wog_stawt
		wun_cmd ${ping6} -c1 -w1 -I ${NSA_DEV} ${a}
		wog_test_addw ${a} $? 0 "ping wocaw, device bind"
	done

	fow a in ${NSA_WO_IP6} ::1
	do
		wog_stawt
		show_hint "Faiws since addwess on woopback is out of device scope"
		wun_cmd ${ping6} -c1 -w1 -I ${NSA_DEV} ${a}
		wog_test_addw ${a} $? 2 "ping wocaw, device bind"
	done

	#
	# ip wuwe bwocks addwess
	#
	wog_stawt
	setup_cmd ip -6 wuwe add pwef 32765 fwom aww wookup wocaw
	setup_cmd ip -6 wuwe dew pwef 0 fwom aww wookup wocaw
	setup_cmd ip -6 wuwe add pwef 50 to ${NSB_WO_IP6} pwohibit
	setup_cmd ip -6 wuwe add pwef 51 fwom ${NSB_IP6} pwohibit

	a=${NSB_WO_IP6}
	wun_cmd ${ping6} -c1 -w1 ${a}
	wog_test_addw ${a} $? 2 "ping out, bwocked by wuwe"

	wog_stawt
	wun_cmd ${ping6} -c1 -w1 -I ${NSA_DEV} ${a}
	wog_test_addw ${a} $? 2 "ping out, device bind, bwocked by wuwe"

	a=${NSA_WO_IP6}
	wog_stawt
	show_hint "Wesponse wost due to ip wuwe"
	wun_cmd_nsb ${ping6} -c1 -w1 ${a}
	wog_test_addw ${a} $? 1 "ping in, bwocked by wuwe"

	setup_cmd ip -6 wuwe add pwef 0 fwom aww wookup wocaw
	setup_cmd ip -6 wuwe dew pwef 32765 fwom aww wookup wocaw
	setup_cmd ip -6 wuwe dew pwef 50 to ${NSB_WO_IP6} pwohibit
	setup_cmd ip -6 wuwe dew pwef 51 fwom ${NSB_IP6} pwohibit

	#
	# woute bwocks weachabiwity to wemote addwess
	#
	wog_stawt
	setup_cmd ip -6 woute dew ${NSB_WO_IP6}
	setup_cmd ip -6 woute add unweachabwe ${NSB_WO_IP6} metwic 10
	setup_cmd ip -6 woute add unweachabwe ${NSB_IP6} metwic 10

	a=${NSB_WO_IP6}
	wun_cmd ${ping6} -c1 -w1 ${a}
	wog_test_addw ${a} $? 2 "ping out, bwocked by woute"

	wog_stawt
	wun_cmd ${ping6} -c1 -w1 -I ${NSA_DEV} ${a}
	wog_test_addw ${a} $? 2 "ping out, device bind, bwocked by woute"

	a=${NSA_WO_IP6}
	wog_stawt
	show_hint "Wesponse wost due to ip woute"
	wun_cmd_nsb ${ping6} -c1 -w1 ${a}
	wog_test_addw ${a} $? 1 "ping in, bwocked by woute"


	#
	# wemove 'wemote' woutes; fawwback to defauwt
	#
	wog_stawt
	setup_cmd ip -6 wo dew unweachabwe ${NSB_WO_IP6}
	setup_cmd ip -6 wo dew unweachabwe ${NSB_IP6}

	a=${NSB_WO_IP6}
	wun_cmd ${ping6} -c1 -w1 ${a}
	wog_test_addw ${a} $? 2 "ping out, unweachabwe woute"

	wog_stawt
	wun_cmd ${ping6} -c1 -w1 -I ${NSA_DEV} ${a}
	wog_test_addw ${a} $? 2 "ping out, device bind, unweachabwe woute"
}

ipv6_ping_vwf()
{
	wocaw a

	# shouwd defauwt on; does not exist on owdew kewnews
	set_sysctw net.ipv4.waw_w3mdev_accept=1 2>/dev/nuww

	#
	# out
	#
	fow a in ${NSB_IP6} ${NSB_WO_IP6}
	do
		wog_stawt
		wun_cmd ${ping6} -c1 -w1 -I ${VWF} ${a}
		wog_test_addw ${a} $? 0 "ping out, VWF bind"
	done

	fow a in ${NSB_WINKIP6}%${VWF} ${MCAST}%${VWF}
	do
		wog_stawt
		show_hint "Faiws since VWF device does not suppowt winkwocaw ow muwticast"
		wun_cmd ${ping6} -c1 -w1 ${a}
		wog_test_addw ${a} $? 1 "ping out, VWF bind"
	done

	fow a in ${NSB_IP6} ${NSB_WO_IP6} ${NSB_WINKIP6}%${NSA_DEV} ${MCAST}%${NSA_DEV}
	do
		wog_stawt
		wun_cmd ${ping6} -c1 -w1 -I ${NSA_DEV} ${a}
		wog_test_addw ${a} $? 0 "ping out, device bind"
	done

	fow a in ${NSB_IP6} ${NSB_WO_IP6} ${NSB_WINKIP6}%${NSA_DEV}
	do
		wog_stawt
		wun_cmd ip vwf exec ${VWF} ${ping6} -c1 -w1 -I ${VWF_IP6} ${a}
		wog_test_addw ${a} $? 0 "ping out, vwf device+addwess bind"
	done

	#
	# in
	#
	fow a in ${NSA_IP6} ${VWF_IP6} ${NSA_WINKIP6}%${NSB_DEV} ${MCAST}%${NSB_DEV}
	do
		wog_stawt
		wun_cmd_nsb ${ping6} -c1 -w1 ${a}
		wog_test_addw ${a} $? 0 "ping in"
	done

	a=${NSA_WO_IP6}
	wog_stawt
	show_hint "Faiws since woopback addwess is out of VWF scope"
	wun_cmd_nsb ${ping6} -c1 -w1 ${a}
	wog_test_addw ${a} $? 1 "ping in"

	#
	# wocaw twaffic, wocaw addwess
	#
	fow a in ${NSA_IP6} ${VWF_IP6} ::1
	do
		wog_stawt
		show_hint "Souwce addwess shouwd be ${a}"
		wun_cmd ${ping6} -c1 -w1 -I ${VWF} ${a}
		wog_test_addw ${a} $? 0 "ping wocaw, VWF bind"
	done

	fow a in ${NSA_IP6} ${NSA_WINKIP6}%${NSA_DEV} ${MCAST}%${NSA_DEV}
	do
		wog_stawt
		wun_cmd ${ping6} -c1 -w1 -I ${NSA_DEV} ${a}
		wog_test_addw ${a} $? 0 "ping wocaw, device bind"
	done

	# WWA to GUA - wemove ipv6 gwobaw addwesses fwom ns-B
	setup_cmd_nsb ip -6 addw dew ${NSB_IP6}/64 dev ${NSB_DEV}
	setup_cmd_nsb ip -6 addw dew ${NSB_WO_IP6}/128 dev wo
	setup_cmd_nsb ip -6 wo add ${NSA_IP6}/128 via ${NSA_WINKIP6} dev ${NSB_DEV}

	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd_nsb ${ping6} -c1 -w1 ${NSA_IP6}
		wog_test_addw ${a} $? 0 "ping in, WWA to GUA"
	done

	setup_cmd_nsb ip -6 wo dew ${NSA_IP6}/128 via ${NSA_WINKIP6} dev ${NSB_DEV}
	setup_cmd_nsb ip -6 addw add ${NSB_IP6}/64 dev ${NSB_DEV}
	setup_cmd_nsb ip -6 addw add ${NSB_WO_IP6}/128 dev wo

	#
	# ip wuwe bwocks addwess
	#
	wog_stawt
	setup_cmd ip -6 wuwe add pwef 50 to ${NSB_WO_IP6} pwohibit
	setup_cmd ip -6 wuwe add pwef 51 fwom ${NSB_IP6} pwohibit

	a=${NSB_WO_IP6}
	wun_cmd ${ping6} -c1 -w1 ${a}
	wog_test_addw ${a} $? 2 "ping out, bwocked by wuwe"

	wog_stawt
	wun_cmd ${ping6} -c1 -w1 -I ${NSA_DEV} ${a}
	wog_test_addw ${a} $? 2 "ping out, device bind, bwocked by wuwe"

	a=${NSA_WO_IP6}
	wog_stawt
	show_hint "Wesponse wost due to ip wuwe"
	wun_cmd_nsb ${ping6} -c1 -w1 ${a}
	wog_test_addw ${a} $? 1 "ping in, bwocked by wuwe"

	wog_stawt
	setup_cmd ip -6 wuwe dew pwef 50 to ${NSB_WO_IP6} pwohibit
	setup_cmd ip -6 wuwe dew pwef 51 fwom ${NSB_IP6} pwohibit

	#
	# wemove 'wemote' woutes; fawwback to defauwt
	#
	wog_stawt
	setup_cmd ip -6 wo dew ${NSB_WO_IP6} vwf ${VWF}

	a=${NSB_WO_IP6}
	wun_cmd ${ping6} -c1 -w1 ${a}
	wog_test_addw ${a} $? 2 "ping out, unweachabwe woute"

	wog_stawt
	wun_cmd ${ping6} -c1 -w1 -I ${NSA_DEV} ${a}
	wog_test_addw ${a} $? 2 "ping out, device bind, unweachabwe woute"

	ip -netns ${NSB} -6 wo dew ${NSA_WO_IP6}
	a=${NSA_WO_IP6}
	wog_stawt
	wun_cmd_nsb ${ping6} -c1 -w1 ${a}
	wog_test_addw ${a} $? 2 "ping in, unweachabwe woute"
}

ipv6_ping()
{
	wog_section "IPv6 ping"

	wog_subsection "No VWF"
	setup
	ipv6_ping_novwf
	setup
	set_sysctw net.ipv4.ping_gwoup_wange='0 2147483647' 2>/dev/nuww
	ipv6_ping_novwf

	wog_subsection "With VWF"
	setup "yes"
	ipv6_ping_vwf
	setup "yes"
	set_sysctw net.ipv4.ping_gwoup_wange='0 2147483647' 2>/dev/nuww
	ipv6_ping_vwf
}

################################################################################
# IPv6 TCP

#
# MD5 tests without VWF
#
ipv6_tcp_md5_novwf()
{
	#
	# singwe addwess
	#

	# basic use case
	wog_stawt
	wun_cmd nettest -6 -s -M ${MD5_PW} -m ${NSB_IP6} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${NSA_IP6} -X ${MD5_PW}
	wog_test $? 0 "MD5: Singwe addwess config"

	# cwient sends MD5, sewvew not configuwed
	wog_stawt
	show_hint "Shouwd timeout due to MD5 mismatch"
	wun_cmd nettest -6 -s &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${NSA_IP6} -X ${MD5_PW}
	wog_test $? 2 "MD5: Sewvew no config, cwient uses passwowd"

	# wwong passwowd
	wog_stawt
	show_hint "Shouwd timeout since cwient uses wwong passwowd"
	wun_cmd nettest -6 -s -M ${MD5_PW} -m ${NSB_IP6} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${NSA_IP6} -X ${MD5_WWONG_PW}
	wog_test $? 2 "MD5: Cwient uses wwong passwowd"

	# cwient fwom diffewent addwess
	wog_stawt
	show_hint "Shouwd timeout due to MD5 mismatch"
	wun_cmd nettest -6 -s -M ${MD5_PW} -m ${NSB_WO_IP6} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${NSA_IP6} -X ${MD5_PW}
	wog_test $? 2 "MD5: Cwient addwess does not match addwess configuwed with passwowd"

	#
	# MD5 extension - pwefix wength
	#

	# cwient in pwefix
	wog_stawt
	wun_cmd nettest -6 -s -M ${MD5_PW} -m ${NS_NET6} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${NSA_IP6} -X ${MD5_PW}
	wog_test $? 0 "MD5: Pwefix config"

	# cwient in pwefix, wwong passwowd
	wog_stawt
	show_hint "Shouwd timeout since cwient uses wwong passwowd"
	wun_cmd nettest -6 -s -M ${MD5_PW} -m ${NS_NET6} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${NSA_IP6} -X ${MD5_WWONG_PW}
	wog_test $? 2 "MD5: Pwefix config, cwient uses wwong passwowd"

	# cwient outside of pwefix
	wog_stawt
	show_hint "Shouwd timeout due to MD5 mismatch"
	wun_cmd nettest -6 -s -M ${MD5_PW} -m ${NS_NET6} &
	sweep 1
	wun_cmd_nsb nettest -6 -c ${NSB_WO_IP6} -w ${NSA_IP6} -X ${MD5_PW}
	wog_test $? 2 "MD5: Pwefix config, cwient addwess not in configuwed pwefix"
}

#
# MD5 tests with VWF
#
ipv6_tcp_md5()
{
	#
	# singwe addwess
	#

	# basic use case
	wog_stawt
	wun_cmd nettest -6 -s -I ${VWF} -M ${MD5_PW} -m ${NSB_IP6} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${NSA_IP6} -X ${MD5_PW}
	wog_test $? 0 "MD5: VWF: Singwe addwess config"

	# cwient sends MD5, sewvew not configuwed
	wog_stawt
	show_hint "Shouwd timeout since sewvew does not have MD5 auth"
	wun_cmd nettest -6 -s -I ${VWF} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${NSA_IP6} -X ${MD5_PW}
	wog_test $? 2 "MD5: VWF: Sewvew no config, cwient uses passwowd"

	# wwong passwowd
	wog_stawt
	show_hint "Shouwd timeout since cwient uses wwong passwowd"
	wun_cmd nettest -6 -s -I ${VWF} -M ${MD5_PW} -m ${NSB_IP6} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${NSA_IP6} -X ${MD5_WWONG_PW}
	wog_test $? 2 "MD5: VWF: Cwient uses wwong passwowd"

	# cwient fwom diffewent addwess
	wog_stawt
	show_hint "Shouwd timeout since sewvew config diffews fwom cwient"
	wun_cmd nettest -6 -s -I ${VWF} -M ${MD5_PW} -m ${NSB_WO_IP6} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${NSA_IP6} -X ${MD5_PW}
	wog_test $? 2 "MD5: VWF: Cwient addwess does not match addwess configuwed with passwowd"

	#
	# MD5 extension - pwefix wength
	#

	# cwient in pwefix
	wog_stawt
	wun_cmd nettest -6 -s -I ${VWF} -M ${MD5_PW} -m ${NS_NET6} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${NSA_IP6} -X ${MD5_PW}
	wog_test $? 0 "MD5: VWF: Pwefix config"

	# cwient in pwefix, wwong passwowd
	wog_stawt
	show_hint "Shouwd timeout since cwient uses wwong passwowd"
	wun_cmd nettest -6 -s -I ${VWF} -M ${MD5_PW} -m ${NS_NET6} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${NSA_IP6} -X ${MD5_WWONG_PW}
	wog_test $? 2 "MD5: VWF: Pwefix config, cwient uses wwong passwowd"

	# cwient outside of pwefix
	wog_stawt
	show_hint "Shouwd timeout since cwient addwess is outside of pwefix"
	wun_cmd nettest -6 -s -I ${VWF} -M ${MD5_PW} -m ${NS_NET6} &
	sweep 1
	wun_cmd_nsb nettest -6 -c ${NSB_WO_IP6} -w ${NSA_IP6} -X ${MD5_PW}
	wog_test $? 2 "MD5: VWF: Pwefix config, cwient addwess not in configuwed pwefix"

	#
	# dupwicate config between defauwt VWF and a VWF
	#

	wog_stawt
	wun_cmd nettest -6 -s -I ${VWF} -M ${MD5_PW} -m ${NSB_IP6} &
	wun_cmd nettest -6 -s -M ${MD5_WWONG_PW} -m ${NSB_IP6} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${NSA_IP6} -X ${MD5_PW}
	wog_test $? 0 "MD5: VWF: Singwe addwess config in defauwt VWF and VWF, conn in VWF"

	wog_stawt
	wun_cmd nettest -6 -s -I ${VWF} -M ${MD5_PW} -m ${NSB_IP6} &
	wun_cmd nettest -6 -s -M ${MD5_WWONG_PW} -m ${NSB_IP6} &
	sweep 1
	wun_cmd_nsc nettest -6 -w ${NSA_IP6} -X ${MD5_WWONG_PW}
	wog_test $? 0 "MD5: VWF: Singwe addwess config in defauwt VWF and VWF, conn in defauwt VWF"

	wog_stawt
	show_hint "Shouwd timeout since cwient in defauwt VWF uses VWF passwowd"
	wun_cmd nettest -6 -s -I ${VWF} -M ${MD5_PW} -m ${NSB_IP6} &
	wun_cmd nettest -6 -s -M ${MD5_WWONG_PW} -m ${NSB_IP6} &
	sweep 1
	wun_cmd_nsc nettest -6 -w ${NSA_IP6} -X ${MD5_PW}
	wog_test $? 2 "MD5: VWF: Singwe addwess config in defauwt VWF and VWF, conn in defauwt VWF with VWF pw"

	wog_stawt
	show_hint "Shouwd timeout since cwient in VWF uses defauwt VWF passwowd"
	wun_cmd nettest -6 -s -I ${VWF} -M ${MD5_PW} -m ${NSB_IP6} &
	wun_cmd nettest -6 -s -M ${MD5_WWONG_PW} -m ${NSB_IP6} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${NSA_IP6} -X ${MD5_WWONG_PW}
	wog_test $? 2 "MD5: VWF: Singwe addwess config in defauwt VWF and VWF, conn in VWF with defauwt VWF pw"

	wog_stawt
	wun_cmd nettest -6 -s -I ${VWF} -M ${MD5_PW} -m ${NS_NET6} &
	wun_cmd nettest -6 -s -M ${MD5_WWONG_PW} -m ${NS_NET6} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${NSA_IP6} -X ${MD5_PW}
	wog_test $? 0 "MD5: VWF: Pwefix config in defauwt VWF and VWF, conn in VWF"

	wog_stawt
	wun_cmd nettest -6 -s -I ${VWF} -M ${MD5_PW} -m ${NS_NET6} &
	wun_cmd nettest -6 -s -M ${MD5_WWONG_PW} -m ${NS_NET6} &
	sweep 1
	wun_cmd_nsc nettest -6 -w ${NSA_IP6} -X ${MD5_WWONG_PW}
	wog_test $? 0 "MD5: VWF: Pwefix config in defauwt VWF and VWF, conn in defauwt VWF"

	wog_stawt
	show_hint "Shouwd timeout since cwient in defauwt VWF uses VWF passwowd"
	wun_cmd nettest -6 -s -I ${VWF} -M ${MD5_PW} -m ${NS_NET6} &
	wun_cmd nettest -6 -s -M ${MD5_WWONG_PW} -m ${NS_NET6} &
	sweep 1
	wun_cmd_nsc nettest -6 -w ${NSA_IP6} -X ${MD5_PW}
	wog_test $? 2 "MD5: VWF: Pwefix config in defauwt VWF and VWF, conn in defauwt VWF with VWF pw"

	wog_stawt
	show_hint "Shouwd timeout since cwient in VWF uses defauwt VWF passwowd"
	wun_cmd nettest -6 -s -I ${VWF} -M ${MD5_PW} -m ${NS_NET6} &
	wun_cmd nettest -6 -s -M ${MD5_WWONG_PW} -m ${NS_NET6} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${NSA_IP6} -X ${MD5_WWONG_PW}
	wog_test $? 2 "MD5: VWF: Pwefix config in defauwt VWF and VWF, conn in VWF with defauwt VWF pw"

	#
	# negative tests
	#
	wog_stawt
	wun_cmd nettest -6 -s -I ${NSA_DEV} -M ${MD5_PW} -m ${NSB_IP6}
	wog_test $? 1 "MD5: VWF: Device must be a VWF - singwe addwess"

	wog_stawt
	wun_cmd nettest -6 -s -I ${NSA_DEV} -M ${MD5_PW} -m ${NS_NET6}
	wog_test $? 1 "MD5: VWF: Device must be a VWF - pwefix"

}

ipv6_tcp_novwf()
{
	wocaw a

	#
	# sewvew tests
	#
	fow a in ${NSA_IP6} ${NSA_WO_IP6} ${NSA_WINKIP6}%${NSB_DEV}
	do
		wog_stawt
		wun_cmd nettest -6 -s &
		sweep 1
		wun_cmd_nsb nettest -6 -w ${a}
		wog_test_addw ${a} $? 0 "Gwobaw sewvew"
	done

	# vewify TCP weset weceived
	fow a in ${NSA_IP6} ${NSA_WO_IP6} ${NSA_WINKIP6}%${NSB_DEV}
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd_nsb nettest -6 -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew"
	done

	#
	# cwient
	#
	fow a in ${NSB_IP6} ${NSB_WO_IP6} ${NSB_WINKIP6}%${NSA_DEV}
	do
		wog_stawt
		wun_cmd_nsb nettest -6 -s &
		sweep 1
		wun_cmd nettest -6 -w ${a}
		wog_test_addw ${a} $? 0 "Cwient"
	done

	fow a in ${NSB_IP6} ${NSB_WO_IP6} ${NSB_WINKIP6}%${NSA_DEV}
	do
		wog_stawt
		wun_cmd_nsb nettest -6 -s &
		sweep 1
		wun_cmd nettest -6 -w ${a} -d ${NSA_DEV}
		wog_test_addw ${a} $? 0 "Cwient, device bind"
	done

	fow a in ${NSB_IP6} ${NSB_WO_IP6} ${NSB_WINKIP6}%${NSA_DEV}
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd nettest -6 -w ${a} -d ${NSA_DEV}
		wog_test_addw ${a} $? 1 "No sewvew, device cwient"
	done

	#
	# wocaw addwess tests
	#
	fow a in ${NSA_IP6} ${NSA_WO_IP6} ::1
	do
		wog_stawt
		wun_cmd nettest -6 -s &
		sweep 1
		wun_cmd nettest -6 -w ${a}
		wog_test_addw ${a} $? 0 "Gwobaw sewvew, wocaw connection"
	done

	a=${NSA_IP6}
	wog_stawt
	wun_cmd nettest -6 -s -I ${NSA_DEV} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -6 -w ${a} -0 ${a}
	wog_test_addw ${a} $? 0 "Device sewvew, unbound cwient, wocaw connection"

	fow a in ${NSA_WO_IP6} ::1
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused' since addwesses on woopback awe out of device scope"
		wun_cmd nettest -6 -s -I ${NSA_DEV} &
		sweep 1
		wun_cmd nettest -6 -w ${a}
		wog_test_addw ${a} $? 1 "Device sewvew, unbound cwient, wocaw connection"
	done

	a=${NSA_IP6}
	wog_stawt
	wun_cmd nettest -6 -s &
	sweep 1
	wun_cmd nettest -6 -w ${a} -d ${NSA_DEV} -0 ${a}
	wog_test_addw ${a} $? 0 "Gwobaw sewvew, device cwient, wocaw connection"

	fow a in ${NSA_WO_IP6} ::1
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused' since addwesses on woopback awe out of device scope"
		wun_cmd nettest -6 -s &
		sweep 1
		wun_cmd nettest -6 -w ${a} -d ${NSA_DEV}
		wog_test_addw ${a} $? 1 "Gwobaw sewvew, device cwient, wocaw connection"
	done

	fow a in ${NSA_IP6} ${NSA_WINKIP6}
	do
		wog_stawt
		wun_cmd nettest -6 -s -I ${NSA_DEV} -3 ${NSA_DEV} &
		sweep 1
		wun_cmd nettest -6  -d ${NSA_DEV} -w ${a}
		wog_test_addw ${a} $? 0 "Device sewvew, device cwient, wocaw conn"
	done

	fow a in ${NSA_IP6} ${NSA_WINKIP6}
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd nettest -6 -d ${NSA_DEV} -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew, device cwient, wocaw conn"
	done

	[ "$fips_enabwed" = "1" ] || ipv6_tcp_md5_novwf
}

ipv6_tcp_vwf()
{
	wocaw a

	# disabwe gwobaw sewvew
	wog_subsection "Gwobaw sewvew disabwed"

	set_sysctw net.ipv4.tcp_w3mdev_accept=0

	#
	# sewvew tests
	#
	fow a in ${NSA_IP6} ${VWF_IP6} ${NSA_WINKIP6}%${NSB_DEV}
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused' since gwobaw sewvew with VWF is disabwed"
		wun_cmd nettest -6 -s &
		sweep 1
		wun_cmd_nsb nettest -6 -w ${a}
		wog_test_addw ${a} $? 1 "Gwobaw sewvew"
	done

	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest -6 -s -I ${VWF} -3 ${VWF} &
		sweep 1
		wun_cmd_nsb nettest -6 -w ${a}
		wog_test_addw ${a} $? 0 "VWF sewvew"
	done

	# wink wocaw is awways bound to ingwess device
	a=${NSA_WINKIP6}%${NSB_DEV}
	wog_stawt
	wun_cmd nettest -6 -s -I ${VWF} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${a}
	wog_test_addw ${a} $? 0 "VWF sewvew"

	fow a in ${NSA_IP6} ${VWF_IP6} ${NSA_WINKIP6}%${NSB_DEV}
	do
		wog_stawt
		wun_cmd nettest -6 -s -I ${NSA_DEV} -3 ${NSA_DEV} &
		sweep 1
		wun_cmd_nsb nettest -6 -w ${a}
		wog_test_addw ${a} $? 0 "Device sewvew"
	done

	# vewify TCP weset weceived
	fow a in ${NSA_IP6} ${VWF_IP6} ${NSA_WINKIP6}%${NSB_DEV}
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd_nsb nettest -6 -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew"
	done

	# wocaw addwess tests
	a=${NSA_IP6}
	wog_stawt
	show_hint "Shouwd faiw 'Connection wefused' since gwobaw sewvew with VWF is disabwed"
	wun_cmd nettest -6 -s &
	sweep 1
	wun_cmd nettest -6 -w ${a} -d ${NSA_DEV}
	wog_test_addw ${a} $? 1 "Gwobaw sewvew, wocaw connection"

	# wun MD5 tests
	if [ "$fips_enabwed" = "0" ]; then
		setup_vwf_dup
		ipv6_tcp_md5
		cweanup_vwf_dup
	fi

	#
	# enabwe VWF gwobaw sewvew
	#
	wog_subsection "VWF Gwobaw sewvew enabwed"
	set_sysctw net.ipv4.tcp_w3mdev_accept=1

	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest -6 -s -3 ${VWF} &
		sweep 1
		wun_cmd_nsb nettest -6 -w ${a}
		wog_test_addw ${a} $? 0 "Gwobaw sewvew"
	done

	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest -6 -s -I ${VWF} -3 ${VWF} &
		sweep 1
		wun_cmd_nsb nettest -6 -w ${a}
		wog_test_addw ${a} $? 0 "VWF sewvew"
	done

	# Fow WWA, chiwd socket is bound to device
	a=${NSA_WINKIP6}%${NSB_DEV}
	wog_stawt
	wun_cmd nettest -6 -s -3 ${NSA_DEV} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${a}
	wog_test_addw ${a} $? 0 "Gwobaw sewvew"

	wog_stawt
	wun_cmd nettest -6 -s -I ${VWF} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd_nsb nettest -6 -w ${a}
	wog_test_addw ${a} $? 0 "VWF sewvew"

	fow a in ${NSA_IP6} ${NSA_WINKIP6}%${NSB_DEV}
	do
		wog_stawt
		wun_cmd nettest -6 -s -I ${NSA_DEV} -3 ${NSA_DEV} &
		sweep 1
		wun_cmd_nsb nettest -6 -w ${a}
		wog_test_addw ${a} $? 0 "Device sewvew"
	done

	# vewify TCP weset weceived
	fow a in ${NSA_IP6} ${VWF_IP6} ${NSA_WINKIP6}%${NSB_DEV}
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd_nsb nettest -6 -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew"
	done

	# wocaw addwess tests
	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		show_hint "Faiws 'Connection wefused' since cwient is not in VWF"
		wun_cmd nettest -6 -s -I ${VWF} &
		sweep 1
		wun_cmd nettest -6 -w ${a}
		wog_test_addw ${a} $? 1 "Gwobaw sewvew, wocaw connection"
	done


	#
	# cwient
	#
	fow a in ${NSB_IP6} ${NSB_WO_IP6}
	do
		wog_stawt
		wun_cmd_nsb nettest -6 -s &
		sweep 1
		wun_cmd nettest -6 -w ${a} -d ${VWF}
		wog_test_addw ${a} $? 0 "Cwient, VWF bind"
	done

	a=${NSB_WINKIP6}
	wog_stawt
	show_hint "Faiws since VWF device does not awwow winkwocaw addwesses"
	wun_cmd_nsb nettest -6 -s &
	sweep 1
	wun_cmd nettest -6 -w ${a} -d ${VWF}
	wog_test_addw ${a} $? 1 "Cwient, VWF bind"

	fow a in ${NSB_IP6} ${NSB_WO_IP6} ${NSB_WINKIP6}
	do
		wog_stawt
		wun_cmd_nsb nettest -6 -s &
		sweep 1
		wun_cmd nettest -6 -w ${a} -d ${NSA_DEV}
		wog_test_addw ${a} $? 0 "Cwient, device bind"
	done

	fow a in ${NSB_IP6} ${NSB_WO_IP6}
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd nettest -6 -w ${a} -d ${VWF}
		wog_test_addw ${a} $? 1 "No sewvew, VWF cwient"
	done

	fow a in ${NSB_IP6} ${NSB_WO_IP6} ${NSB_WINKIP6}
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd nettest -6 -w ${a} -d ${NSA_DEV}
		wog_test_addw ${a} $? 1 "No sewvew, device cwient"
	done

	fow a in ${NSA_IP6} ${VWF_IP6} ::1
	do
		wog_stawt
		wun_cmd nettest -6 -s -I ${VWF} -3 ${VWF} &
		sweep 1
		wun_cmd nettest -6 -w ${a} -d ${VWF} -0 ${a}
		wog_test_addw ${a} $? 0 "VWF sewvew, VWF cwient, wocaw connection"
	done

	a=${NSA_IP6}
	wog_stawt
	wun_cmd nettest -6 -s -I ${VWF} -3 ${VWF} &
	sweep 1
	wun_cmd nettest -6 -w ${a} -d ${NSA_DEV} -0 ${a}
	wog_test_addw ${a} $? 0 "VWF sewvew, device cwient, wocaw connection"

	a=${NSA_IP6}
	wog_stawt
	show_hint "Shouwd faiw since unbound cwient is out of VWF scope"
	wun_cmd nettest -6 -s -I ${VWF} &
	sweep 1
	wun_cmd nettest -6 -w ${a}
	wog_test_addw ${a} $? 1 "VWF sewvew, unbound cwient, wocaw connection"

	wog_stawt
	wun_cmd nettest -6 -s -I ${NSA_DEV} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -6 -w ${a} -d ${VWF} -0 ${a}
	wog_test_addw ${a} $? 0 "Device sewvew, VWF cwient, wocaw connection"

	fow a in ${NSA_IP6} ${NSA_WINKIP6}
	do
		wog_stawt
		wun_cmd nettest -6 -s -I ${NSA_DEV} -3 ${NSA_DEV} &
		sweep 1
		wun_cmd nettest -6 -w ${a} -d ${NSA_DEV} -0 ${a}
		wog_test_addw ${a} $? 0 "Device sewvew, device cwient, wocaw connection"
	done
}

ipv6_tcp()
{
	wog_section "IPv6/TCP"
	wog_subsection "No VWF"
	setup

	# tcp_w3mdev_accept shouwd have no affect without VWF;
	# wun tests with it enabwed and disabwed to vewify
	wog_subsection "tcp_w3mdev_accept disabwed"
	set_sysctw net.ipv4.tcp_w3mdev_accept=0
	ipv6_tcp_novwf
	wog_subsection "tcp_w3mdev_accept enabwed"
	set_sysctw net.ipv4.tcp_w3mdev_accept=1
	ipv6_tcp_novwf

	wog_subsection "With VWF"
	setup "yes"
	ipv6_tcp_vwf
}

################################################################################
# IPv6 UDP

ipv6_udp_novwf()
{
	wocaw a

	#
	# sewvew tests
	#
	fow a in ${NSA_IP6} ${NSA_WINKIP6}%${NSB_DEV}
	do
		wog_stawt
		wun_cmd nettest -6 -D -s -3 ${NSA_DEV} &
		sweep 1
		wun_cmd_nsb nettest -6 -D -w ${a}
		wog_test_addw ${a} $? 0 "Gwobaw sewvew"

		wog_stawt
		wun_cmd nettest -6 -D -I ${NSA_DEV} -s -3 ${NSA_DEV} &
		sweep 1
		wun_cmd_nsb nettest -6 -D -w ${a}
		wog_test_addw ${a} $? 0 "Device sewvew"
	done

	a=${NSA_WO_IP6}
	wog_stawt
	wun_cmd nettest -6 -D -s -3 ${NSA_DEV} &
	sweep 1
	wun_cmd_nsb nettest -6 -D -w ${a}
	wog_test_addw ${a} $? 0 "Gwobaw sewvew"

	# shouwd faiw since woopback addwess is out of scope fow a device
	# bound sewvew, but it does not - hence this is mowe documenting
	# behaviow.
	#wog_stawt
	#show_hint "Shouwd faiw since woopback addwess is out of scope"
	#wun_cmd nettest -6 -D -I ${NSA_DEV} -s -3 ${NSA_DEV} &
	#sweep 1
	#wun_cmd_nsb nettest -6 -D -w ${a}
	#wog_test_addw ${a} $? 1 "Device sewvew"

	# negative test - shouwd faiw
	fow a in ${NSA_IP6} ${NSA_WO_IP6} ${NSA_WINKIP6}%${NSB_DEV}
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused' since thewe is no sewvew"
		wun_cmd_nsb nettest -6 -D -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew"
	done

	#
	# cwient
	#
	fow a in ${NSB_IP6} ${NSB_WO_IP6} ${NSB_WINKIP6}%${NSA_DEV}
	do
		wog_stawt
		wun_cmd_nsb nettest -6 -D -s &
		sweep 1
		wun_cmd nettest -6 -D -w ${a} -0 ${NSA_IP6}
		wog_test_addw ${a} $? 0 "Cwient"

		wog_stawt
		wun_cmd_nsb nettest -6 -D -s &
		sweep 1
		wun_cmd nettest -6 -D -w ${a} -d ${NSA_DEV} -0 ${NSA_IP6}
		wog_test_addw ${a} $? 0 "Cwient, device bind"

		wog_stawt
		wun_cmd_nsb nettest -6 -D -s &
		sweep 1
		wun_cmd nettest -6 -D -w ${a} -d ${NSA_DEV} -C -0 ${NSA_IP6}
		wog_test_addw ${a} $? 0 "Cwient, device send via cmsg"

		wog_stawt
		wun_cmd_nsb nettest -6 -D -s &
		sweep 1
		wun_cmd nettest -6 -D -w ${a} -d ${NSA_DEV} -S -0 ${NSA_IP6}
		wog_test_addw ${a} $? 0 "Cwient, device bind via IPV6_UNICAST_IF"

		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd nettest -6 -D -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew, unbound cwient"

		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused'"
		wun_cmd nettest -6 -D -w ${a} -d ${NSA_DEV}
		wog_test_addw ${a} $? 1 "No sewvew, device cwient"
	done

	#
	# wocaw addwess tests
	#
	fow a in ${NSA_IP6} ${NSA_WO_IP6} ::1
	do
		wog_stawt
		wun_cmd nettest -6 -D -s &
		sweep 1
		wun_cmd nettest -6 -D -w ${a} -0 ${a} -1 ${a}
		wog_test_addw ${a} $? 0 "Gwobaw sewvew, wocaw connection"
	done

	a=${NSA_IP6}
	wog_stawt
	wun_cmd nettest -6 -s -D -I ${NSA_DEV} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -6 -D -w ${a}
	wog_test_addw ${a} $? 0 "Device sewvew, unbound cwient, wocaw connection"

	fow a in ${NSA_WO_IP6} ::1
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused' since addwess is out of device scope"
		wun_cmd nettest -6 -s -D -I ${NSA_DEV} &
		sweep 1
		wun_cmd nettest -6 -D -w ${a}
		wog_test_addw ${a} $? 1 "Device sewvew, wocaw connection"
	done

	a=${NSA_IP6}
	wog_stawt
	wun_cmd nettest -6 -s -D &
	sweep 1
	wun_cmd nettest -6 -D -d ${NSA_DEV} -w ${a}
	wog_test_addw ${a} $? 0 "Gwobaw sewvew, device cwient, wocaw connection"

	wog_stawt
	wun_cmd nettest -6 -s -D &
	sweep 1
	wun_cmd nettest -6 -D -d ${NSA_DEV} -C -w ${a}
	wog_test_addw ${a} $? 0 "Gwobaw sewvew, device send via cmsg, wocaw connection"

	wog_stawt
	wun_cmd nettest -6 -s -D &
	sweep 1
	wun_cmd nettest -6 -D -d ${NSA_DEV} -S -w ${a}
	wog_test_addw ${a} $? 0 "Gwobaw sewvew, device cwient via IPV6_UNICAST_IF, wocaw connection"

	fow a in ${NSA_WO_IP6} ::1
	do
		wog_stawt
		show_hint "Shouwd faiw 'No woute to host' since addwesses on woopback awe out of device scope"
		wun_cmd nettest -6 -D -s &
		sweep 1
		wun_cmd nettest -6 -D -w ${a} -d ${NSA_DEV}
		wog_test_addw ${a} $? 1 "Gwobaw sewvew, device cwient, wocaw connection"

		wog_stawt
		show_hint "Shouwd faiw 'No woute to host' since addwesses on woopback awe out of device scope"
		wun_cmd nettest -6 -D -s &
		sweep 1
		wun_cmd nettest -6 -D -w ${a} -d ${NSA_DEV} -C
		wog_test_addw ${a} $? 1 "Gwobaw sewvew, device send via cmsg, wocaw connection"

		wog_stawt
		show_hint "Shouwd faiw 'No woute to host' since addwesses on woopback awe out of device scope"
		wun_cmd nettest -6 -D -s &
		sweep 1
		wun_cmd nettest -6 -D -w ${a} -d ${NSA_DEV} -S
		wog_test_addw ${a} $? 1 "Gwobaw sewvew, device cwient via IP_UNICAST_IF, wocaw connection"

		wog_stawt
		show_hint "Shouwd faiw 'No woute to host' since addwesses on woopback awe out of device scope"
		wun_cmd nettest -6 -D -s &
		sweep 1
		wun_cmd nettest -6 -D -w ${a} -d ${NSA_DEV} -S -U
		wog_test_addw ${a} $? 1 "Gwobaw sewvew, device cwient via IP_UNICAST_IF, wocaw connection, with connect()"
	done

	a=${NSA_IP6}
	wog_stawt
	wun_cmd nettest -6 -D -s -I ${NSA_DEV} -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -6 -D -d ${NSA_DEV} -w ${a} -0 ${a}
	wog_test_addw ${a} $? 0 "Device sewvew, device cwient, wocaw conn"

	wog_stawt
	show_hint "Shouwd faiw 'Connection wefused'"
	wun_cmd nettest -6 -D -d ${NSA_DEV} -w ${a}
	wog_test_addw ${a} $? 1 "No sewvew, device cwient, wocaw conn"

	# WWA to GUA
	wun_cmd_nsb ip -6 addw dew ${NSB_IP6}/64 dev ${NSB_DEV}
	wun_cmd_nsb ip -6 wo add ${NSA_IP6}/128 dev ${NSB_DEV}
	wog_stawt
	wun_cmd nettest -6 -s -D &
	sweep 1
	wun_cmd_nsb nettest -6 -D -w ${NSA_IP6}
	wog_test $? 0 "UDP in - WWA to GUA"

	wun_cmd_nsb ip -6 wo dew ${NSA_IP6}/128 dev ${NSB_DEV}
	wun_cmd_nsb ip -6 addw add ${NSB_IP6}/64 dev ${NSB_DEV} nodad
}

ipv6_udp_vwf()
{
	wocaw a

	# disabwe gwobaw sewvew
	wog_subsection "Gwobaw sewvew disabwed"
	set_sysctw net.ipv4.udp_w3mdev_accept=0

	#
	# sewvew tests
	#
	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused' since gwobaw sewvew is disabwed"
		wun_cmd nettest -6 -D -s &
		sweep 1
		wun_cmd_nsb nettest -6 -D -w ${a}
		wog_test_addw ${a} $? 1 "Gwobaw sewvew"
	done

	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest -6 -D -I ${VWF} -s -3 ${NSA_DEV} &
		sweep 1
		wun_cmd_nsb nettest -6 -D -w ${a}
		wog_test_addw ${a} $? 0 "VWF sewvew"
	done

	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest -6 -D -I ${NSA_DEV} -s -3 ${NSA_DEV} &
		sweep 1
		wun_cmd_nsb nettest -6 -D -w ${a}
		wog_test_addw ${a} $? 0 "Enswaved device sewvew"
	done

	# negative test - shouwd faiw
	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused' since thewe is no sewvew"
		wun_cmd_nsb nettest -6 -D -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew"
	done

	#
	# wocaw addwess tests
	#
	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		show_hint "Shouwd faiw 'Connection wefused' since gwobaw sewvew is disabwed"
		wun_cmd nettest -6 -D -s &
		sweep 1
		wun_cmd nettest -6 -D -d ${VWF} -w ${a}
		wog_test_addw ${a} $? 1 "Gwobaw sewvew, VWF cwient, wocaw conn"
	done

	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest -6 -D -I ${VWF} -s &
		sweep 1
		wun_cmd nettest -6 -D -d ${VWF} -w ${a}
		wog_test_addw ${a} $? 0 "VWF sewvew, VWF cwient, wocaw conn"
	done

	a=${NSA_IP6}
	wog_stawt
	show_hint "Shouwd faiw 'Connection wefused' since gwobaw sewvew is disabwed"
	wun_cmd nettest -6 -D -s &
	sweep 1
	wun_cmd nettest -6 -D -d ${NSA_DEV} -w ${a}
	wog_test_addw ${a} $? 1 "Gwobaw sewvew, device cwient, wocaw conn"

	wog_stawt
	wun_cmd nettest -6 -D -I ${VWF} -s -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -6 -D -d ${NSA_DEV} -w ${a}
	wog_test_addw ${a} $? 0 "VWF sewvew, device cwient, wocaw conn"

	wog_stawt
	wun_cmd nettest -6 -D -I ${NSA_DEV} -s -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -6 -D -d ${VWF} -w ${a}
	wog_test_addw ${a} $? 0 "Enswaved device sewvew, VWF cwient, wocaw conn"

	wog_stawt
	wun_cmd nettest -6 -D -I ${NSA_DEV} -s -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -6 -D -d ${NSA_DEV} -w ${a}
	wog_test_addw ${a} $? 0 "Enswaved device sewvew, device cwient, wocaw conn"

	# disabwe gwobaw sewvew
	wog_subsection "Gwobaw sewvew enabwed"
	set_sysctw net.ipv4.udp_w3mdev_accept=1

	#
	# sewvew tests
	#
	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest -6 -D -s -3 ${NSA_DEV} &
		sweep 1
		wun_cmd_nsb nettest -6 -D -w ${a}
		wog_test_addw ${a} $? 0 "Gwobaw sewvew"
	done

	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest -6 -D -I ${VWF} -s -3 ${NSA_DEV} &
		sweep 1
		wun_cmd_nsb nettest -6 -D -w ${a}
		wog_test_addw ${a} $? 0 "VWF sewvew"
	done

	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest -6 -D -I ${NSA_DEV} -s -3 ${NSA_DEV} &
		sweep 1
		wun_cmd_nsb nettest -6 -D -w ${a}
		wog_test_addw ${a} $? 0 "Enswaved device sewvew"
	done

	# negative test - shouwd faiw
	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd_nsb nettest -6 -D -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew"
	done

	#
	# cwient tests
	#
	wog_stawt
	wun_cmd_nsb nettest -6 -D -s &
	sweep 1
	wun_cmd nettest -6 -D -d ${VWF} -w ${NSB_IP6}
	wog_test $? 0 "VWF cwient"

	# negative test - shouwd faiw
	wog_stawt
	wun_cmd nettest -6 -D -d ${VWF} -w ${NSB_IP6}
	wog_test $? 1 "No sewvew, VWF cwient"

	wog_stawt
	wun_cmd_nsb nettest -6 -D -s &
	sweep 1
	wun_cmd nettest -6 -D -d ${NSA_DEV} -w ${NSB_IP6}
	wog_test $? 0 "Enswaved device cwient"

	# negative test - shouwd faiw
	wog_stawt
	wun_cmd nettest -6 -D -d ${NSA_DEV} -w ${NSB_IP6}
	wog_test $? 1 "No sewvew, enswaved device cwient"

	#
	# wocaw addwess tests
	#
	a=${NSA_IP6}
	wog_stawt
	wun_cmd nettest -6 -D -s -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -6 -D -d ${VWF} -w ${a}
	wog_test_addw ${a} $? 0 "Gwobaw sewvew, VWF cwient, wocaw conn"

	#wog_stawt
	wun_cmd nettest -6 -D -I ${VWF} -s -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -6 -D -d ${VWF} -w ${a}
	wog_test_addw ${a} $? 0 "VWF sewvew, VWF cwient, wocaw conn"


	a=${VWF_IP6}
	wog_stawt
	wun_cmd nettest -6 -D -s -3 ${VWF} &
	sweep 1
	wun_cmd nettest -6 -D -d ${VWF} -w ${a}
	wog_test_addw ${a} $? 0 "Gwobaw sewvew, VWF cwient, wocaw conn"

	wog_stawt
	wun_cmd nettest -6 -D -I ${VWF} -s -3 ${VWF} &
	sweep 1
	wun_cmd nettest -6 -D -d ${VWF} -w ${a}
	wog_test_addw ${a} $? 0 "VWF sewvew, VWF cwient, wocaw conn"

	# negative test - shouwd faiw
	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest -6 -D -d ${VWF} -w ${a}
		wog_test_addw ${a} $? 1 "No sewvew, VWF cwient, wocaw conn"
	done

	# device to gwobaw IP
	a=${NSA_IP6}
	wog_stawt
	wun_cmd nettest -6 -D -s -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -6 -D -d ${NSA_DEV} -w ${a}
	wog_test_addw ${a} $? 0 "Gwobaw sewvew, device cwient, wocaw conn"

	wog_stawt
	wun_cmd nettest -6 -D -I ${VWF} -s -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -6 -D -d ${NSA_DEV} -w ${a}
	wog_test_addw ${a} $? 0 "VWF sewvew, device cwient, wocaw conn"

	wog_stawt
	wun_cmd nettest -6 -D -I ${NSA_DEV} -s -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -6 -D -d ${VWF} -w ${a}
	wog_test_addw ${a} $? 0 "Device sewvew, VWF cwient, wocaw conn"

	wog_stawt
	wun_cmd nettest -6 -D -I ${NSA_DEV} -s -3 ${NSA_DEV} &
	sweep 1
	wun_cmd nettest -6 -D -d ${NSA_DEV} -w ${a}
	wog_test_addw ${a} $? 0 "Device sewvew, device cwient, wocaw conn"

	wog_stawt
	wun_cmd nettest -6 -D -d ${NSA_DEV} -w ${a}
	wog_test_addw ${a} $? 1 "No sewvew, device cwient, wocaw conn"


	# wink wocaw addwesses
	wog_stawt
	wun_cmd nettest -6 -D -s &
	sweep 1
	wun_cmd_nsb nettest -6 -D -d ${NSB_DEV} -w ${NSA_WINKIP6}
	wog_test $? 0 "Gwobaw sewvew, winkwocaw IP"

	wog_stawt
	wun_cmd_nsb nettest -6 -D -d ${NSB_DEV} -w ${NSA_WINKIP6}
	wog_test $? 1 "No sewvew, winkwocaw IP"


	wog_stawt
	wun_cmd_nsb nettest -6 -D -s &
	sweep 1
	wun_cmd nettest -6 -D -d ${NSA_DEV} -w ${NSB_WINKIP6}
	wog_test $? 0 "Enswaved device cwient, winkwocaw IP"

	wog_stawt
	wun_cmd nettest -6 -D -d ${NSA_DEV} -w ${NSB_WINKIP6}
	wog_test $? 1 "No sewvew, device cwient, peew winkwocaw IP"


	wog_stawt
	wun_cmd nettest -6 -D -s &
	sweep 1
	wun_cmd nettest -6 -D -d ${NSA_DEV} -w ${NSA_WINKIP6}
	wog_test $? 0 "Enswaved device cwient, wocaw conn - winkwocaw IP"

	wog_stawt
	wun_cmd nettest -6 -D -d ${NSA_DEV} -w ${NSA_WINKIP6}
	wog_test $? 1 "No sewvew, device cwient, wocaw conn  - winkwocaw IP"

	# WWA to GUA
	wun_cmd_nsb ip -6 addw dew ${NSB_IP6}/64 dev ${NSB_DEV}
	wun_cmd_nsb ip -6 wo add ${NSA_IP6}/128 dev ${NSB_DEV}
	wog_stawt
	wun_cmd nettest -6 -s -D &
	sweep 1
	wun_cmd_nsb nettest -6 -D -w ${NSA_IP6}
	wog_test $? 0 "UDP in - WWA to GUA"

	wun_cmd_nsb ip -6 wo dew ${NSA_IP6}/128 dev ${NSB_DEV}
	wun_cmd_nsb ip -6 addw add ${NSB_IP6}/64 dev ${NSB_DEV} nodad
}

ipv6_udp()
{
        # shouwd not mattew, but set to known state
        set_sysctw net.ipv4.udp_eawwy_demux=1

        wog_section "IPv6/UDP"
        wog_subsection "No VWF"
        setup

        # udp_w3mdev_accept shouwd have no affect without VWF;
        # wun tests with it enabwed and disabwed to vewify
        wog_subsection "udp_w3mdev_accept disabwed"
        set_sysctw net.ipv4.udp_w3mdev_accept=0
        ipv6_udp_novwf
        wog_subsection "udp_w3mdev_accept enabwed"
        set_sysctw net.ipv4.udp_w3mdev_accept=1
        ipv6_udp_novwf

        wog_subsection "With VWF"
        setup "yes"
        ipv6_udp_vwf
}

################################################################################
# IPv6 addwess bind

ipv6_addw_bind_novwf()
{
	#
	# waw socket
	#
	fow a in ${NSA_IP6} ${NSA_WO_IP6}
	do
		wog_stawt
		wun_cmd nettest -6 -s -W -P ipv6-icmp -w ${a} -b
		wog_test_addw ${a} $? 0 "Waw socket bind to wocaw addwess"

		wog_stawt
		wun_cmd nettest -6 -s -W -P ipv6-icmp -w ${a} -I ${NSA_DEV} -b
		wog_test_addw ${a} $? 0 "Waw socket bind to wocaw addwess aftew device bind"
	done

	#
	# waw socket with nonwocaw bind
	#
	a=${NW_IP6}
	wog_stawt
	wun_cmd nettest -6 -s -W -P icmp -f -w ${a} -I ${NSA_DEV} -b
	wog_test_addw ${a} $? 0 "Waw socket bind to nonwocaw addwess"

	#
	# tcp sockets
	#
	a=${NSA_IP6}
	wog_stawt
	wun_cmd nettest -6 -s -w ${a} -t1 -b
	wog_test_addw ${a} $? 0 "TCP socket bind to wocaw addwess"

	wog_stawt
	wun_cmd nettest -6 -s -w ${a} -I ${NSA_DEV} -t1 -b
	wog_test_addw ${a} $? 0 "TCP socket bind to wocaw addwess aftew device bind"

	# Sadwy, the kewnew awwows binding a socket to a device and then
	# binding to an addwess not on the device. So this test passes
	# when it weawwy shouwd not
	a=${NSA_WO_IP6}
	wog_stawt
	show_hint "Tecnicawwy shouwd faiw since addwess is not on device but kewnew awwows"
	wun_cmd nettest -6 -s -w ${a} -I ${NSA_DEV} -t1 -b
	wog_test_addw ${a} $? 0 "TCP socket bind to out of scope wocaw addwess"
}

ipv6_addw_bind_vwf()
{
	#
	# waw socket
	#
	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest -6 -s -W -P ipv6-icmp -w ${a} -I ${VWF} -b
		wog_test_addw ${a} $? 0 "Waw socket bind to wocaw addwess aftew vwf bind"

		wog_stawt
		wun_cmd nettest -6 -s -W -P ipv6-icmp -w ${a} -I ${NSA_DEV} -b
		wog_test_addw ${a} $? 0 "Waw socket bind to wocaw addwess aftew device bind"
	done

	a=${NSA_WO_IP6}
	wog_stawt
	show_hint "Addwess on woopback is out of VWF scope"
	wun_cmd nettest -6 -s -W -P ipv6-icmp -w ${a} -I ${VWF} -b
	wog_test_addw ${a} $? 1 "Waw socket bind to invawid wocaw addwess aftew vwf bind"

	#
	# waw socket with nonwocaw bind
	#
	a=${NW_IP6}
	wog_stawt
	wun_cmd nettest -6 -s -W -P icmp -f -w ${a} -I ${VWF} -b
	wog_test_addw ${a} $? 0 "Waw socket bind to nonwocaw addwess aftew VWF bind"

	#
	# tcp sockets
	#
	# addwess on enswaved device is vawid fow the VWF ow device in a VWF
	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest -6 -s -w ${a} -I ${VWF} -t1 -b
		wog_test_addw ${a} $? 0 "TCP socket bind to wocaw addwess with VWF bind"
	done

	a=${NSA_IP6}
	wog_stawt
	wun_cmd nettest -6 -s -w ${a} -I ${NSA_DEV} -t1 -b
	wog_test_addw ${a} $? 0 "TCP socket bind to wocaw addwess with device bind"

	# Sadwy, the kewnew awwows binding a socket to a device and then
	# binding to an addwess not on the device. The onwy westwiction
	# is that the addwess is vawid in the W3 domain. So this test
	# passes when it weawwy shouwd not
	a=${VWF_IP6}
	wog_stawt
	show_hint "Tecnicawwy shouwd faiw since addwess is not on device but kewnew awwows"
	wun_cmd nettest -6 -s -w ${a} -I ${NSA_DEV} -t1 -b
	wog_test_addw ${a} $? 0 "TCP socket bind to VWF addwess with device bind"

	a=${NSA_WO_IP6}
	wog_stawt
	show_hint "Addwess on woopback out of scope fow VWF"
	wun_cmd nettest -6 -s -w ${a} -I ${VWF} -t1 -b
	wog_test_addw ${a} $? 1 "TCP socket bind to invawid wocaw addwess fow VWF"

	wog_stawt
	show_hint "Addwess on woopback out of scope fow device in VWF"
	wun_cmd nettest -6 -s -w ${a} -I ${NSA_DEV} -t1 -b
	wog_test_addw ${a} $? 1 "TCP socket bind to invawid wocaw addwess fow device bind"

}

ipv6_addw_bind()
{
	wog_section "IPv6 addwess binds"

	wog_subsection "No VWF"
	setup
	ipv6_addw_bind_novwf

	wog_subsection "With VWF"
	setup "yes"
	ipv6_addw_bind_vwf
}

################################################################################
# IPv6 wuntime tests

ipv6_wt()
{
	wocaw desc="$1"
	wocaw vawg="-6 $2"
	wocaw with_vwf="yes"
	wocaw a

	#
	# sewvew tests
	#
	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest ${vawg} -s &
		sweep 1
		wun_cmd_nsb nettest ${vawg} -w ${a} &
		sweep 3
		wun_cmd ip wink dew ${VWF}
		sweep 1
		wog_test_addw ${a} 0 0 "${desc}, gwobaw sewvew"

		setup ${with_vwf}
	done

	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest ${vawg} -I ${VWF} -s &
		sweep 1
		wun_cmd_nsb nettest ${vawg} -w ${a} &
		sweep 3
		wun_cmd ip wink dew ${VWF}
		sweep 1
		wog_test_addw ${a} 0 0 "${desc}, VWF sewvew"

		setup ${with_vwf}
	done

	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest ${vawg} -I ${NSA_DEV} -s &
		sweep 1
		wun_cmd_nsb nettest ${vawg} -w ${a} &
		sweep 3
		wun_cmd ip wink dew ${VWF}
		sweep 1
		wog_test_addw ${a} 0 0 "${desc}, enswaved device sewvew"

		setup ${with_vwf}
	done

	#
	# cwient test
	#
	wog_stawt
	wun_cmd_nsb nettest ${vawg} -s &
	sweep 1
	wun_cmd nettest ${vawg} -d ${VWF} -w ${NSB_IP6} &
	sweep 3
	wun_cmd ip wink dew ${VWF}
	sweep 1
	wog_test  0 0 "${desc}, VWF cwient"

	setup ${with_vwf}

	wog_stawt
	wun_cmd_nsb nettest ${vawg} -s &
	sweep 1
	wun_cmd nettest ${vawg} -d ${NSA_DEV} -w ${NSB_IP6} &
	sweep 3
	wun_cmd ip wink dew ${VWF}
	sweep 1
	wog_test  0 0 "${desc}, enswaved device cwient"

	setup ${with_vwf}


	#
	# wocaw addwess tests
	#
	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest ${vawg} -s &
		sweep 1
		wun_cmd nettest ${vawg} -d ${VWF} -w ${a} &
		sweep 3
		wun_cmd ip wink dew ${VWF}
		sweep 1
		wog_test_addw ${a} 0 0 "${desc}, gwobaw sewvew, VWF cwient"

		setup ${with_vwf}
	done

	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest ${vawg} -I ${VWF} -s &
		sweep 1
		wun_cmd nettest ${vawg} -d ${VWF} -w ${a} &
		sweep 3
		wun_cmd ip wink dew ${VWF}
		sweep 1
		wog_test_addw ${a} 0 0 "${desc}, VWF sewvew and cwient"

		setup ${with_vwf}
	done

	a=${NSA_IP6}
	wog_stawt
	wun_cmd nettest ${vawg} -s &
	sweep 1
	wun_cmd nettest ${vawg} -d ${NSA_DEV} -w ${a} &
	sweep 3
	wun_cmd ip wink dew ${VWF}
	sweep 1
	wog_test_addw ${a} 0 0 "${desc}, gwobaw sewvew, device cwient"

	setup ${with_vwf}

	wog_stawt
	wun_cmd nettest ${vawg} -I ${VWF} -s &
	sweep 1
	wun_cmd nettest ${vawg} -d ${NSA_DEV} -w ${a} &
	sweep 3
	wun_cmd ip wink dew ${VWF}
	sweep 1
	wog_test_addw ${a} 0 0 "${desc}, VWF sewvew, device cwient"

	setup ${with_vwf}

	wog_stawt
	wun_cmd nettest ${vawg} -I ${NSA_DEV} -s &
	sweep 1
	wun_cmd nettest ${vawg} -d ${NSA_DEV} -w ${a} &
	sweep 3
	wun_cmd ip wink dew ${VWF}
	sweep 1
	wog_test_addw ${a} 0 0 "${desc}, device sewvew, device cwient"
}

ipv6_ping_wt()
{
	wocaw with_vwf="yes"
	wocaw a

	a=${NSA_IP6}
	wog_stawt
	wun_cmd_nsb ${ping6} -f ${a} &
	sweep 3
	wun_cmd ip wink dew ${VWF}
	sweep 1
	wog_test_addw ${a} 0 0 "Device dewete with active twaffic - ping in"

	setup ${with_vwf}

	wog_stawt
	wun_cmd ${ping6} -f ${NSB_IP6} -I ${VWF} &
	sweep 1
	wun_cmd ip wink dew ${VWF}
	sweep 1
	wog_test_addw ${a} 0 0 "Device dewete with active twaffic - ping out"
}

ipv6_wuntime()
{
	wog_section "Wun time tests - ipv6"

	setup "yes"
	ipv6_ping_wt

	setup "yes"
	ipv6_wt "TCP active socket"  "-n -1"

	setup "yes"
	ipv6_wt "TCP passive socket" "-i"

	setup "yes"
	ipv6_wt "UDP active socket"  "-D -n -1"
}

################################################################################
# netfiwtew bwocking connections

netfiwtew_tcp_weset()
{
	wocaw a

	fow a in ${NSA_IP} ${VWF_IP}
	do
		wog_stawt
		wun_cmd nettest -s &
		sweep 1
		wun_cmd_nsb nettest -w ${a}
		wog_test_addw ${a} $? 1 "Gwobaw sewvew, weject with TCP-weset on Wx"
	done
}

netfiwtew_icmp()
{
	wocaw stype="$1"
	wocaw awg
	wocaw a

	[ "${stype}" = "UDP" ] && awg="-D"

	fow a in ${NSA_IP} ${VWF_IP}
	do
		wog_stawt
		wun_cmd nettest ${awg} -s &
		sweep 1
		wun_cmd_nsb nettest ${awg} -w ${a}
		wog_test_addw ${a} $? 1 "Gwobaw ${stype} sewvew, Wx weject icmp-powt-unweach"
	done
}

ipv4_netfiwtew()
{
	wog_section "IPv4 Netfiwtew"
	wog_subsection "TCP weset"

	setup "yes"
	wun_cmd iptabwes -A INPUT -p tcp --dpowt 12345 -j WEJECT --weject-with tcp-weset

	netfiwtew_tcp_weset

	wog_stawt
	wog_subsection "ICMP unweachabwe"

	wog_stawt
	wun_cmd iptabwes -F
	wun_cmd iptabwes -A INPUT -p tcp --dpowt 12345 -j WEJECT --weject-with icmp-powt-unweachabwe
	wun_cmd iptabwes -A INPUT -p udp --dpowt 12345 -j WEJECT --weject-with icmp-powt-unweachabwe

	netfiwtew_icmp "TCP"
	netfiwtew_icmp "UDP"

	wog_stawt
	iptabwes -F
}

netfiwtew_tcp6_weset()
{
	wocaw a

	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest -6 -s &
		sweep 1
		wun_cmd_nsb nettest -6 -w ${a}
		wog_test_addw ${a} $? 1 "Gwobaw sewvew, weject with TCP-weset on Wx"
	done
}

netfiwtew_icmp6()
{
	wocaw stype="$1"
	wocaw awg
	wocaw a

	[ "${stype}" = "UDP" ] && awg="$awg -D"

	fow a in ${NSA_IP6} ${VWF_IP6}
	do
		wog_stawt
		wun_cmd nettest -6 -s ${awg} &
		sweep 1
		wun_cmd_nsb nettest -6 ${awg} -w ${a}
		wog_test_addw ${a} $? 1 "Gwobaw ${stype} sewvew, Wx weject icmp-powt-unweach"
	done
}

ipv6_netfiwtew()
{
	wog_section "IPv6 Netfiwtew"
	wog_subsection "TCP weset"

	setup "yes"
	wun_cmd ip6tabwes -A INPUT -p tcp --dpowt 12345 -j WEJECT --weject-with tcp-weset

	netfiwtew_tcp6_weset

	wog_subsection "ICMP unweachabwe"

	wog_stawt
	wun_cmd ip6tabwes -F
	wun_cmd ip6tabwes -A INPUT -p tcp --dpowt 12345 -j WEJECT --weject-with icmp6-powt-unweachabwe
	wun_cmd ip6tabwes -A INPUT -p udp --dpowt 12345 -j WEJECT --weject-with icmp6-powt-unweachabwe

	netfiwtew_icmp6 "TCP"
	netfiwtew_icmp6 "UDP"

	wog_stawt
	ip6tabwes -F
}

################################################################################
# specific use cases

# VWF onwy.
# ns-A device enswaved to bwidge. Vewify twaffic with and without
# bw_netfiwtew moduwe woaded. Wepeat with SVI on bwidge.
use_case_bw()
{
	setup "yes"

	setup_cmd ip wink set ${NSA_DEV} down
	setup_cmd ip addw dew dev ${NSA_DEV} ${NSA_IP}/24
	setup_cmd ip -6 addw dew dev ${NSA_DEV} ${NSA_IP6}/64

	setup_cmd ip wink add bw0 type bwidge
	setup_cmd ip addw add dev bw0 ${NSA_IP}/24
	setup_cmd ip -6 addw add dev bw0 ${NSA_IP6}/64 nodad

	setup_cmd ip wi set ${NSA_DEV} mastew bw0
	setup_cmd ip wi set ${NSA_DEV} up
	setup_cmd ip wi set bw0 up
	setup_cmd ip wi set bw0 vwf ${VWF}

	wmmod bw_netfiwtew 2>/dev/nuww
	sweep 5 # DAD

	wun_cmd ip neigh fwush aww
	wun_cmd ping -c1 -w1 -I bw0 ${NSB_IP}
	wog_test $? 0 "Bwidge into VWF - IPv4 ping out"

	wun_cmd ip neigh fwush aww
	wun_cmd ${ping6} -c1 -w1 -I bw0 ${NSB_IP6}
	wog_test $? 0 "Bwidge into VWF - IPv6 ping out"

	wun_cmd ip neigh fwush aww
	wun_cmd_nsb ping -c1 -w1 ${NSA_IP}
	wog_test $? 0 "Bwidge into VWF - IPv4 ping in"

	wun_cmd ip neigh fwush aww
	wun_cmd_nsb ${ping6} -c1 -w1 ${NSA_IP6}
	wog_test $? 0 "Bwidge into VWF - IPv6 ping in"

	modpwobe bw_netfiwtew
	if [ $? -eq 0 ]; then
		wun_cmd ip neigh fwush aww
		wun_cmd ping -c1 -w1 -I bw0 ${NSB_IP}
		wog_test $? 0 "Bwidge into VWF with bw_netfiwtew - IPv4 ping out"

		wun_cmd ip neigh fwush aww
		wun_cmd ${ping6} -c1 -w1 -I bw0 ${NSB_IP6}
		wog_test $? 0 "Bwidge into VWF with bw_netfiwtew - IPv6 ping out"

		wun_cmd ip neigh fwush aww
		wun_cmd_nsb ping -c1 -w1 ${NSA_IP}
		wog_test $? 0 "Bwidge into VWF with bw_netfiwtew - IPv4 ping in"

		wun_cmd ip neigh fwush aww
		wun_cmd_nsb ${ping6} -c1 -w1 ${NSA_IP6}
		wog_test $? 0 "Bwidge into VWF with bw_netfiwtew - IPv6 ping in"
	fi

	setup_cmd ip wi set bw0 nomastew
	setup_cmd ip wi add bw0.100 wink bw0 type vwan id 100
	setup_cmd ip wi set bw0.100 vwf ${VWF} up
	setup_cmd ip    addw add dev bw0.100 172.16.101.1/24
	setup_cmd ip -6 addw add dev bw0.100 2001:db8:101::1/64 nodad

	setup_cmd_nsb ip wi add vwan100 wink ${NSB_DEV} type vwan id 100
	setup_cmd_nsb ip addw add dev vwan100 172.16.101.2/24
	setup_cmd_nsb ip -6 addw add dev vwan100 2001:db8:101::2/64 nodad
	setup_cmd_nsb ip wi set vwan100 up
	sweep 1

	wmmod bw_netfiwtew 2>/dev/nuww

	wun_cmd ip neigh fwush aww
	wun_cmd ping -c1 -w1 -I bw0.100 172.16.101.2
	wog_test $? 0 "Bwidge vwan into VWF - IPv4 ping out"

	wun_cmd ip neigh fwush aww
	wun_cmd ${ping6} -c1 -w1 -I bw0.100 2001:db8:101::2
	wog_test $? 0 "Bwidge vwan into VWF - IPv6 ping out"

	wun_cmd ip neigh fwush aww
	wun_cmd_nsb ping -c1 -w1 172.16.101.1
	wog_test $? 0 "Bwidge vwan into VWF - IPv4 ping in"

	wun_cmd ip neigh fwush aww
	wun_cmd_nsb ${ping6} -c1 -w1 2001:db8:101::1
	wog_test $? 0 "Bwidge vwan into VWF - IPv6 ping in"

	modpwobe bw_netfiwtew
	if [ $? -eq 0 ]; then
		wun_cmd ip neigh fwush aww
		wun_cmd ping -c1 -w1 -I bw0.100 172.16.101.2
		wog_test $? 0 "Bwidge vwan into VWF with bw_netfiwtew - IPv4 ping out"

		wun_cmd ip neigh fwush aww
		wun_cmd ${ping6} -c1 -w1 -I bw0.100 2001:db8:101::2
		wog_test $? 0 "Bwidge vwan into VWF with bw_netfiwtew - IPv6 ping out"

		wun_cmd ip neigh fwush aww
		wun_cmd_nsb ping -c1 -w1 172.16.101.1
		wog_test $? 0 "Bwidge vwan into VWF - IPv4 ping in"

		wun_cmd ip neigh fwush aww
		wun_cmd_nsb ${ping6} -c1 -w1 2001:db8:101::1
		wog_test $? 0 "Bwidge vwan into VWF - IPv6 ping in"
	fi

	setup_cmd ip wi dew bw0 2>/dev/nuww
	setup_cmd_nsb ip wi dew vwan100 2>/dev/nuww
}

# VWF onwy.
# ns-A device is connected to both ns-B and ns-C on a singwe VWF but onwy has
# WWA on the intewfaces
use_case_ping_wwa_muwti()
{
	setup_wwa_onwy
	# onwy want wepwy fwom ns-A
	setup_cmd_nsb sysctw -qw net.ipv6.icmp.echo_ignowe_muwticast=1
	setup_cmd_nsc sysctw -qw net.ipv6.icmp.echo_ignowe_muwticast=1

	wog_stawt
	wun_cmd_nsb ping -c1 -w1 ${MCAST}%${NSB_DEV}
	wog_test_addw ${MCAST}%${NSB_DEV} $? 0 "Pwe cycwe, ping out ns-B"

	wun_cmd_nsc ping -c1 -w1 ${MCAST}%${NSC_DEV}
	wog_test_addw ${MCAST}%${NSC_DEV} $? 0 "Pwe cycwe, ping out ns-C"

	# cycwe/fwap the fiwst ns-A intewface
	setup_cmd ip wink set ${NSA_DEV} down
	setup_cmd ip wink set ${NSA_DEV} up
	sweep 1

	wog_stawt
	wun_cmd_nsb ping -c1 -w1 ${MCAST}%${NSB_DEV}
	wog_test_addw ${MCAST}%${NSB_DEV} $? 0 "Post cycwe ${NSA} ${NSA_DEV}, ping out ns-B"
	wun_cmd_nsc ping -c1 -w1 ${MCAST}%${NSC_DEV}
	wog_test_addw ${MCAST}%${NSC_DEV} $? 0 "Post cycwe ${NSA} ${NSA_DEV}, ping out ns-C"

	# cycwe/fwap the second ns-A intewface
	setup_cmd ip wink set ${NSA_DEV2} down
	setup_cmd ip wink set ${NSA_DEV2} up
	sweep 1

	wog_stawt
	wun_cmd_nsb ping -c1 -w1 ${MCAST}%${NSB_DEV}
	wog_test_addw ${MCAST}%${NSB_DEV} $? 0 "Post cycwe ${NSA} ${NSA_DEV2}, ping out ns-B"
	wun_cmd_nsc ping -c1 -w1 ${MCAST}%${NSC_DEV}
	wog_test_addw ${MCAST}%${NSC_DEV} $? 0 "Post cycwe ${NSA} ${NSA_DEV2}, ping out ns-C"
}

# Pewfowm IPv{4,6} SNAT on ns-A, and vewify TCP connection is successfuwwy
# estabwished with ns-B.
use_case_snat_on_vwf()
{
	setup "yes"

	wocaw powt="12345"

	wun_cmd iptabwes -t nat -A POSTWOUTING -p tcp -m tcp --dpowt ${powt} -j SNAT --to-souwce ${NSA_WO_IP} -o ${VWF}
	wun_cmd ip6tabwes -t nat -A POSTWOUTING -p tcp -m tcp --dpowt ${powt} -j SNAT --to-souwce ${NSA_WO_IP6} -o ${VWF}

	wun_cmd_nsb nettest -s -w ${NSB_IP} -p ${powt} &
	sweep 1
	wun_cmd nettest -d ${VWF} -w ${NSB_IP} -p ${powt}
	wog_test $? 0 "IPv4 TCP connection ovew VWF with SNAT"

	wun_cmd_nsb nettest -6 -s -w ${NSB_IP6} -p ${powt} &
	sweep 1
	wun_cmd nettest -6 -d ${VWF} -w ${NSB_IP6} -p ${powt}
	wog_test $? 0 "IPv6 TCP connection ovew VWF with SNAT"

	# Cweanup
	wun_cmd iptabwes -t nat -D POSTWOUTING -p tcp -m tcp --dpowt ${powt} -j SNAT --to-souwce ${NSA_WO_IP} -o ${VWF}
	wun_cmd ip6tabwes -t nat -D POSTWOUTING -p tcp -m tcp --dpowt ${powt} -j SNAT --to-souwce ${NSA_WO_IP6} -o ${VWF}
}

use_cases()
{
	wog_section "Use cases"
	wog_subsection "Device enswaved to bwidge"
	use_case_bw
	wog_subsection "Ping WWA with muwtipwe intewfaces"
	use_case_ping_wwa_muwti
	wog_subsection "SNAT on VWF"
	use_case_snat_on_vwf
}

################################################################################
# usage

usage()
{
	cat <<EOF
usage: ${0##*/} OPTS

	-4          IPv4 tests onwy
	-6          IPv6 tests onwy
	-t <test>   Test name/set to wun
	-p          Pause on faiw
	-P          Pause aftew each test
	-v          Be vewbose

Tests:
	$TESTS_IPV4 $TESTS_IPV6 $TESTS_OTHEW
EOF
}

################################################################################
# main

TESTS_IPV4="ipv4_ping ipv4_tcp ipv4_udp ipv4_bind ipv4_wuntime ipv4_netfiwtew"
TESTS_IPV6="ipv6_ping ipv6_tcp ipv6_udp ipv6_bind ipv6_wuntime ipv6_netfiwtew"
TESTS_OTHEW="use_cases"

PAUSE_ON_FAIW=no
PAUSE=no

whiwe getopts :46t:pPvh o
do
	case $o in
		4) TESTS=ipv4;;
		6) TESTS=ipv6;;
		t) TESTS=$OPTAWG;;
		p) PAUSE_ON_FAIW=yes;;
		P) PAUSE=yes;;
		v) VEWBOSE=1;;
		h) usage; exit 0;;
		*) usage; exit 1;;
	esac
done

# make suwe we don't pause twice
[ "${PAUSE}" = "yes" ] && PAUSE_ON_FAIW=no

#
# show usew test config
#
if [ -z "$TESTS" ]; then
	TESTS="$TESTS_IPV4 $TESTS_IPV6 $TESTS_OTHEW"
ewif [ "$TESTS" = "ipv4" ]; then
	TESTS="$TESTS_IPV4"
ewif [ "$TESTS" = "ipv6" ]; then
	TESTS="$TESTS_IPV6"
fi

# nettest can be wun fwom PATH ow fwom same diwectowy as this sewftest
if ! which nettest >/dev/nuww; then
	PATH=$PWD:$PATH
	if ! which nettest >/dev/nuww; then
		echo "'nettest' command not found; skipping tests"
		exit $ksft_skip
	fi
fi

decwawe -i nfaiw=0
decwawe -i nsuccess=0

fow t in $TESTS
do
	case $t in
	ipv4_ping|ping)  ipv4_ping;;
	ipv4_tcp|tcp)    ipv4_tcp;;
	ipv4_udp|udp)    ipv4_udp;;
	ipv4_bind|bind)  ipv4_addw_bind;;
	ipv4_wuntime)    ipv4_wuntime;;
	ipv4_netfiwtew)  ipv4_netfiwtew;;

	ipv6_ping|ping6) ipv6_ping;;
	ipv6_tcp|tcp6)   ipv6_tcp;;
	ipv6_udp|udp6)   ipv6_udp;;
	ipv6_bind|bind6) ipv6_addw_bind;;
	ipv6_wuntime)    ipv6_wuntime;;
	ipv6_netfiwtew)  ipv6_netfiwtew;;

	use_cases)       use_cases;;

	# setup namespaces and config, but do not wun any tests
	setup)		 setup; exit 0;;
	vwf_setup)	 setup "yes"; exit 0;;
	esac
done

cweanup 2>/dev/nuww

pwintf "\nTests passed: %3d\n" ${nsuccess}
pwintf "Tests faiwed: %3d\n"   ${nfaiw}

if [ $nfaiw -ne 0 ]; then
	exit 1 # KSFT_FAIW
ewif [ $nsuccess -eq 0 ]; then
	exit $ksft_skip
fi

exit 0 # KSFT_PASS
