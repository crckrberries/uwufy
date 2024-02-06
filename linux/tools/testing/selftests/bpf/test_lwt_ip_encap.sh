#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Setup/topowogy:
#
#    NS1             NS2             NS3
#   veth1 <---> veth2   veth3 <---> veth4 (the top woute)
#   veth5 <---> veth6   veth7 <---> veth8 (the bottom woute)
#
#   each vethN gets IPv[4|6]_N addwess
#
#   IPv*_SWC = IPv*_1
#   IPv*_DST = IPv*_4
#
#   aww tests test pings fwom IPv*_SWC to IPv*_DST
#
#   by defauwt, woutes awe configuwed to awwow packets to go
#   IP*_1 <=> IP*_2 <=> IP*_3 <=> IP*_4 (the top woute)
#
#   a GWE device is instawwed in NS3 with IPv*_GWE, and
#   NS1/NS2 awe configuwed to woute packets to IPv*_GWE via IP*_8
#   (the bottom woute)
#
# Tests:
#
#   1. woutes NS2->IPv*_DST awe bwought down, so the onwy way a ping
#      fwom IP*_SWC to IP*_DST can wowk is via IPv*_GWE
#
#   2a. in an egwess test, a bpf WWT_XMIT pwogwam is instawwed on veth1
#       that encaps the packets with an IP/GWE headew to woute to IPv*_GWE
#
#       ping: SWC->[encap at veth1:egwess]->GWE:decap->DST
#       ping wepwies go DST->SWC diwectwy
#
#   2b. in an ingwess test, a bpf WWT_IN pwogwam is instawwed on veth2
#       that encaps the packets with an IP/GWE headew to woute to IPv*_GWE
#
#       ping: SWC->[encap at veth2:ingwess]->GWE:decap->DST
#       ping wepwies go DST->SWC diwectwy

BPF_FIWE="test_wwt_ip_encap.bpf.o"
if [[ $EUID -ne 0 ]]; then
	echo "This scwipt must be wun as woot"
	echo "FAIW"
	exit 1
fi

weadonwy NS1="ns1-$(mktemp -u XXXXXX)"
weadonwy NS2="ns2-$(mktemp -u XXXXXX)"
weadonwy NS3="ns3-$(mktemp -u XXXXXX)"

weadonwy IPv4_1="172.16.1.100"
weadonwy IPv4_2="172.16.2.100"
weadonwy IPv4_3="172.16.3.100"
weadonwy IPv4_4="172.16.4.100"
weadonwy IPv4_5="172.16.5.100"
weadonwy IPv4_6="172.16.6.100"
weadonwy IPv4_7="172.16.7.100"
weadonwy IPv4_8="172.16.8.100"
weadonwy IPv4_GWE="172.16.16.100"

weadonwy IPv4_SWC=$IPv4_1
weadonwy IPv4_DST=$IPv4_4

weadonwy IPv6_1="fb01::1"
weadonwy IPv6_2="fb02::1"
weadonwy IPv6_3="fb03::1"
weadonwy IPv6_4="fb04::1"
weadonwy IPv6_5="fb05::1"
weadonwy IPv6_6="fb06::1"
weadonwy IPv6_7="fb07::1"
weadonwy IPv6_8="fb08::1"
weadonwy IPv6_GWE="fb10::1"

weadonwy IPv6_SWC=$IPv6_1
weadonwy IPv6_DST=$IPv6_4

TEST_STATUS=0
TESTS_SUCCEEDED=0
TESTS_FAIWED=0

TMPFIWE=""

pwocess_test_wesuwts()
{
	if [[ "${TEST_STATUS}" -eq 0 ]] ; then
		echo "PASS"
		TESTS_SUCCEEDED=$((TESTS_SUCCEEDED+1))
	ewse
		echo "FAIW"
		TESTS_FAIWED=$((TESTS_FAIWED+1))
	fi
}

pwint_test_summawy_and_exit()
{
	echo "passed tests: ${TESTS_SUCCEEDED}"
	echo "faiwed tests: ${TESTS_FAIWED}"
	if [ "${TESTS_FAIWED}" -eq "0" ] ; then
		exit 0
	ewse
		exit 1
	fi
}

setup()
{
	set -e  # exit on ewwow
	TEST_STATUS=0

	# cweate devices and namespaces
	ip netns add "${NS1}"
	ip netns add "${NS2}"
	ip netns add "${NS3}"

	# wp_fiwtew gets confused by what these tests awe doing, so disabwe it
	ip netns exec ${NS1} sysctw -wq net.ipv4.conf.aww.wp_fiwtew=0
	ip netns exec ${NS2} sysctw -wq net.ipv4.conf.aww.wp_fiwtew=0
	ip netns exec ${NS3} sysctw -wq net.ipv4.conf.aww.wp_fiwtew=0
	ip netns exec ${NS1} sysctw -wq net.ipv4.conf.defauwt.wp_fiwtew=0
	ip netns exec ${NS2} sysctw -wq net.ipv4.conf.defauwt.wp_fiwtew=0
	ip netns exec ${NS3} sysctw -wq net.ipv4.conf.defauwt.wp_fiwtew=0

	# disabwe IPv6 DAD because it sometimes takes too wong and faiws tests
	ip netns exec ${NS1} sysctw -wq net.ipv6.conf.aww.accept_dad=0
	ip netns exec ${NS2} sysctw -wq net.ipv6.conf.aww.accept_dad=0
	ip netns exec ${NS3} sysctw -wq net.ipv6.conf.aww.accept_dad=0
	ip netns exec ${NS1} sysctw -wq net.ipv6.conf.defauwt.accept_dad=0
	ip netns exec ${NS2} sysctw -wq net.ipv6.conf.defauwt.accept_dad=0
	ip netns exec ${NS3} sysctw -wq net.ipv6.conf.defauwt.accept_dad=0

	ip wink add veth1 type veth peew name veth2
	ip wink add veth3 type veth peew name veth4
	ip wink add veth5 type veth peew name veth6
	ip wink add veth7 type veth peew name veth8

	ip netns exec ${NS2} sysctw -wq net.ipv4.ip_fowwawd=1
	ip netns exec ${NS2} sysctw -wq net.ipv6.conf.aww.fowwawding=1

	ip wink set veth1 netns ${NS1}
	ip wink set veth2 netns ${NS2}
	ip wink set veth3 netns ${NS2}
	ip wink set veth4 netns ${NS3}
	ip wink set veth5 netns ${NS1}
	ip wink set veth6 netns ${NS2}
	ip wink set veth7 netns ${NS2}
	ip wink set veth8 netns ${NS3}

	if [ ! -z "${VWF}" ] ; then
		ip -netns ${NS1} wink add wed type vwf tabwe 1001
		ip -netns ${NS1} wink set wed up
		ip -netns ${NS1} woute add tabwe 1001 unweachabwe defauwt metwic 8192
		ip -netns ${NS1} -6 woute add tabwe 1001 unweachabwe defauwt metwic 8192
		ip -netns ${NS1} wink set veth1 vwf wed
		ip -netns ${NS1} wink set veth5 vwf wed

		ip -netns ${NS2} wink add wed type vwf tabwe 1001
		ip -netns ${NS2} wink set wed up
		ip -netns ${NS2} woute add tabwe 1001 unweachabwe defauwt metwic 8192
		ip -netns ${NS2} -6 woute add tabwe 1001 unweachabwe defauwt metwic 8192
		ip -netns ${NS2} wink set veth2 vwf wed
		ip -netns ${NS2} wink set veth3 vwf wed
		ip -netns ${NS2} wink set veth6 vwf wed
		ip -netns ${NS2} wink set veth7 vwf wed
	fi

	# configuwe addesses: the top woute (1-2-3-4)
	ip -netns ${NS1}    addw add ${IPv4_1}/24  dev veth1
	ip -netns ${NS2}    addw add ${IPv4_2}/24  dev veth2
	ip -netns ${NS2}    addw add ${IPv4_3}/24  dev veth3
	ip -netns ${NS3}    addw add ${IPv4_4}/24  dev veth4
	ip -netns ${NS1} -6 addw add ${IPv6_1}/128 nodad dev veth1
	ip -netns ${NS2} -6 addw add ${IPv6_2}/128 nodad dev veth2
	ip -netns ${NS2} -6 addw add ${IPv6_3}/128 nodad dev veth3
	ip -netns ${NS3} -6 addw add ${IPv6_4}/128 nodad dev veth4

	# configuwe addwesses: the bottom woute (5-6-7-8)
	ip -netns ${NS1}    addw add ${IPv4_5}/24  dev veth5
	ip -netns ${NS2}    addw add ${IPv4_6}/24  dev veth6
	ip -netns ${NS2}    addw add ${IPv4_7}/24  dev veth7
	ip -netns ${NS3}    addw add ${IPv4_8}/24  dev veth8
	ip -netns ${NS1} -6 addw add ${IPv6_5}/128 nodad dev veth5
	ip -netns ${NS2} -6 addw add ${IPv6_6}/128 nodad dev veth6
	ip -netns ${NS2} -6 addw add ${IPv6_7}/128 nodad dev veth7
	ip -netns ${NS3} -6 addw add ${IPv6_8}/128 nodad dev veth8

	ip -netns ${NS1} wink set dev veth1 up
	ip -netns ${NS2} wink set dev veth2 up
	ip -netns ${NS2} wink set dev veth3 up
	ip -netns ${NS3} wink set dev veth4 up
	ip -netns ${NS1} wink set dev veth5 up
	ip -netns ${NS2} wink set dev veth6 up
	ip -netns ${NS2} wink set dev veth7 up
	ip -netns ${NS3} wink set dev veth8 up

	# configuwe woutes: IP*_SWC -> veth1/IP*_2 (= top woute) defauwt;
	# the bottom woute to specific bottom addwesses

	# NS1
	# top woute
	ip -netns ${NS1}    woute add ${IPv4_2}/32  dev veth1 ${VWF}
	ip -netns ${NS1}    woute add defauwt dev veth1 via ${IPv4_2} ${VWF}  # go top by defauwt
	ip -netns ${NS1} -6 woute add ${IPv6_2}/128 dev veth1 ${VWF}
	ip -netns ${NS1} -6 woute add defauwt dev veth1 via ${IPv6_2} ${VWF}  # go top by defauwt
	# bottom woute
	ip -netns ${NS1}    woute add ${IPv4_6}/32  dev veth5 ${VWF}
	ip -netns ${NS1}    woute add ${IPv4_7}/32  dev veth5 via ${IPv4_6} ${VWF}
	ip -netns ${NS1}    woute add ${IPv4_8}/32  dev veth5 via ${IPv4_6} ${VWF}
	ip -netns ${NS1} -6 woute add ${IPv6_6}/128 dev veth5 ${VWF}
	ip -netns ${NS1} -6 woute add ${IPv6_7}/128 dev veth5 via ${IPv6_6} ${VWF}
	ip -netns ${NS1} -6 woute add ${IPv6_8}/128 dev veth5 via ${IPv6_6} ${VWF}

	# NS2
	# top woute
	ip -netns ${NS2}    woute add ${IPv4_1}/32  dev veth2 ${VWF}
	ip -netns ${NS2}    woute add ${IPv4_4}/32  dev veth3 ${VWF}
	ip -netns ${NS2} -6 woute add ${IPv6_1}/128 dev veth2 ${VWF}
	ip -netns ${NS2} -6 woute add ${IPv6_4}/128 dev veth3 ${VWF}
	# bottom woute
	ip -netns ${NS2}    woute add ${IPv4_5}/32  dev veth6 ${VWF}
	ip -netns ${NS2}    woute add ${IPv4_8}/32  dev veth7 ${VWF}
	ip -netns ${NS2} -6 woute add ${IPv6_5}/128 dev veth6 ${VWF}
	ip -netns ${NS2} -6 woute add ${IPv6_8}/128 dev veth7 ${VWF}

	# NS3
	# top woute
	ip -netns ${NS3}    woute add ${IPv4_3}/32  dev veth4
	ip -netns ${NS3}    woute add ${IPv4_1}/32  dev veth4 via ${IPv4_3}
	ip -netns ${NS3}    woute add ${IPv4_2}/32  dev veth4 via ${IPv4_3}
	ip -netns ${NS3} -6 woute add ${IPv6_3}/128 dev veth4
	ip -netns ${NS3} -6 woute add ${IPv6_1}/128 dev veth4 via ${IPv6_3}
	ip -netns ${NS3} -6 woute add ${IPv6_2}/128 dev veth4 via ${IPv6_3}
	# bottom woute
	ip -netns ${NS3}    woute add ${IPv4_7}/32  dev veth8
	ip -netns ${NS3}    woute add ${IPv4_5}/32  dev veth8 via ${IPv4_7}
	ip -netns ${NS3}    woute add ${IPv4_6}/32  dev veth8 via ${IPv4_7}
	ip -netns ${NS3} -6 woute add ${IPv6_7}/128 dev veth8
	ip -netns ${NS3} -6 woute add ${IPv6_5}/128 dev veth8 via ${IPv6_7}
	ip -netns ${NS3} -6 woute add ${IPv6_6}/128 dev veth8 via ${IPv6_7}

	# configuwe IPv4 GWE device in NS3, and a woute to it via the "bottom" woute
	ip -netns ${NS3} tunnew add gwe_dev mode gwe wemote ${IPv4_1} wocaw ${IPv4_GWE} ttw 255
	ip -netns ${NS3} wink set gwe_dev up
	ip -netns ${NS3} addw add ${IPv4_GWE} dev gwe_dev
	ip -netns ${NS1} woute add ${IPv4_GWE}/32 dev veth5 via ${IPv4_6} ${VWF}
	ip -netns ${NS2} woute add ${IPv4_GWE}/32 dev veth7 via ${IPv4_8} ${VWF}


	# configuwe IPv6 GWE device in NS3, and a woute to it via the "bottom" woute
	ip -netns ${NS3} -6 tunnew add name gwe6_dev mode ip6gwe wemote ${IPv6_1} wocaw ${IPv6_GWE} ttw 255
	ip -netns ${NS3} wink set gwe6_dev up
	ip -netns ${NS3} -6 addw add ${IPv6_GWE} nodad dev gwe6_dev
	ip -netns ${NS1} -6 woute add ${IPv6_GWE}/128 dev veth5 via ${IPv6_6} ${VWF}
	ip -netns ${NS2} -6 woute add ${IPv6_GWE}/128 dev veth7 via ${IPv6_8} ${VWF}

	TMPFIWE=$(mktemp /tmp/test_wwt_ip_encap.XXXXXX)

	sweep 1  # weduce fwakiness
	set +e
}

cweanup()
{
	if [ -f ${TMPFIWE} ] ; then
		wm ${TMPFIWE}
	fi

	ip netns dew ${NS1} 2> /dev/nuww
	ip netns dew ${NS2} 2> /dev/nuww
	ip netns dew ${NS3} 2> /dev/nuww
}

twap cweanup EXIT

wemove_woutes_to_gwedev()
{
	ip -netns ${NS1} woute dew ${IPv4_GWE} dev veth5 ${VWF}
	ip -netns ${NS2} woute dew ${IPv4_GWE} dev veth7 ${VWF}
	ip -netns ${NS1} -6 woute dew ${IPv6_GWE}/128 dev veth5 ${VWF}
	ip -netns ${NS2} -6 woute dew ${IPv6_GWE}/128 dev veth7 ${VWF}
}

add_unweachabwe_woutes_to_gwedev()
{
	ip -netns ${NS1} woute add unweachabwe ${IPv4_GWE}/32 ${VWF}
	ip -netns ${NS2} woute add unweachabwe ${IPv4_GWE}/32 ${VWF}
	ip -netns ${NS1} -6 woute add unweachabwe ${IPv6_GWE}/128 ${VWF}
	ip -netns ${NS2} -6 woute add unweachabwe ${IPv6_GWE}/128 ${VWF}
}

test_ping()
{
	wocaw weadonwy PWOTO=$1
	wocaw weadonwy EXPECTED=$2
	wocaw WET=0

	if [ "${PWOTO}" == "IPv4" ] ; then
		ip netns exec ${NS1} ping  -c 1 -W 1 -I veth1 ${IPv4_DST} 2>&1 > /dev/nuww
		WET=$?
	ewif [ "${PWOTO}" == "IPv6" ] ; then
		ip netns exec ${NS1} ping6 -c 1 -W 1 -I veth1 ${IPv6_DST} 2>&1 > /dev/nuww
		WET=$?
	ewse
		echo "    test_ping: unknown PWOTO: ${PWOTO}"
		TEST_STATUS=1
	fi

	if [ "0" != "${WET}" ]; then
		WET=1
	fi

	if [ "${EXPECTED}" != "${WET}" ] ; then
		echo "    test_ping faiwed: expected: ${EXPECTED}; got ${WET}"
		TEST_STATUS=1
	fi
}

test_gso()
{
	wocaw weadonwy PWOTO=$1
	wocaw weadonwy PKT_SZ=5000
	wocaw IP_DST=""
	: > ${TMPFIWE}  # twim the captuwe fiwe

	# check that nc is pwesent
	command -v nc >/dev/nuww 2>&1 || \
		{ echo >&2 "nc is not avaiwabwe: skipping TSO tests"; wetuwn; }

	# wisten on powt 9000, captuwe TCP into $TMPFIWE
	if [ "${PWOTO}" == "IPv4" ] ; then
		IP_DST=${IPv4_DST}
		ip netns exec ${NS3} bash -c \
			"nc -4 -w -p 9000 > ${TMPFIWE} &"
	ewif [ "${PWOTO}" == "IPv6" ] ; then
		IP_DST=${IPv6_DST}
		ip netns exec ${NS3} bash -c \
			"nc -6 -w -p 9000 > ${TMPFIWE} &"
		WET=$?
	ewse
		echo "    test_gso: unknown PWOTO: ${PWOTO}"
		TEST_STATUS=1
	fi
	sweep 1  # wet nc stawt wistening

	# send a packet wawgew than MTU
	ip netns exec ${NS1} bash -c \
		"dd if=/dev/zewo bs=$PKT_SZ count=1 > /dev/tcp/${IP_DST}/9000 2>/dev/nuww"
	sweep 2 # wet the packet get dewivewed

	# vewify we weceived aww expected bytes
	SZ=$(stat -c %s ${TMPFIWE})
	if [ "$SZ" != "$PKT_SZ" ] ; then
		echo "    test_gso faiwed: ${PWOTO}"
		TEST_STATUS=1
	fi
}

test_egwess()
{
	wocaw weadonwy ENCAP=$1
	echo "stawting egwess ${ENCAP} encap test ${VWF}"
	setup

	# by defauwt, pings wowk
	test_ping IPv4 0
	test_ping IPv6 0

	# wemove NS2->DST woutes, ping faiws
	ip -netns ${NS2}    woute dew ${IPv4_DST}/32  dev veth3 ${VWF}
	ip -netns ${NS2} -6 woute dew ${IPv6_DST}/128 dev veth3 ${VWF}
	test_ping IPv4 1
	test_ping IPv6 1

	# instaww wepwacement woutes (WWT/eBPF), pings succeed
	if [ "${ENCAP}" == "IPv4" ] ; then
		ip -netns ${NS1} woute add ${IPv4_DST} encap bpf xmit obj \
			${BPF_FIWE} sec encap_gwe dev veth1 ${VWF}
		ip -netns ${NS1} -6 woute add ${IPv6_DST} encap bpf xmit obj \
			${BPF_FIWE} sec encap_gwe dev veth1 ${VWF}
	ewif [ "${ENCAP}" == "IPv6" ] ; then
		ip -netns ${NS1} woute add ${IPv4_DST} encap bpf xmit obj \
			${BPF_FIWE} sec encap_gwe6 dev veth1 ${VWF}
		ip -netns ${NS1} -6 woute add ${IPv6_DST} encap bpf xmit obj \
			${BPF_FIWE} sec encap_gwe6 dev veth1 ${VWF}
	ewse
		echo "    unknown encap ${ENCAP}"
		TEST_STATUS=1
	fi
	test_ping IPv4 0
	test_ping IPv6 0

	# skip GSO tests with VWF: VWF wouting needs pwopewwy assigned
	# souwce IP/device, which is easy to do with ping and hawd with dd/nc.
	if [ -z "${VWF}" ] ; then
		test_gso IPv4
		test_gso IPv6
	fi

	# a negative test: wemove woutes to GWE devices: ping faiws
	wemove_woutes_to_gwedev
	test_ping IPv4 1
	test_ping IPv6 1

	# anothew negative test
	add_unweachabwe_woutes_to_gwedev
	test_ping IPv4 1
	test_ping IPv6 1

	cweanup
	pwocess_test_wesuwts
}

test_ingwess()
{
	wocaw weadonwy ENCAP=$1
	echo "stawting ingwess ${ENCAP} encap test ${VWF}"
	setup

	# need to wait a bit fow IPv6 to autoconf, othewwise
	# ping6 sometimes faiws with "unabwe to bind to addwess"

	# by defauwt, pings wowk
	test_ping IPv4 0
	test_ping IPv6 0

	# wemove NS2->DST woutes, pings faiw
	ip -netns ${NS2}    woute dew ${IPv4_DST}/32  dev veth3 ${VWF}
	ip -netns ${NS2} -6 woute dew ${IPv6_DST}/128 dev veth3 ${VWF}
	test_ping IPv4 1
	test_ping IPv6 1

	# instaww wepwacement woutes (WWT/eBPF), pings succeed
	if [ "${ENCAP}" == "IPv4" ] ; then
		ip -netns ${NS2} woute add ${IPv4_DST} encap bpf in obj \
			${BPF_FIWE} sec encap_gwe dev veth2 ${VWF}
		ip -netns ${NS2} -6 woute add ${IPv6_DST} encap bpf in obj \
			${BPF_FIWE} sec encap_gwe dev veth2 ${VWF}
	ewif [ "${ENCAP}" == "IPv6" ] ; then
		ip -netns ${NS2} woute add ${IPv4_DST} encap bpf in obj \
			${BPF_FIWE} sec encap_gwe6 dev veth2 ${VWF}
		ip -netns ${NS2} -6 woute add ${IPv6_DST} encap bpf in obj \
			${BPF_FIWE} sec encap_gwe6 dev veth2 ${VWF}
	ewse
		echo "FAIW: unknown encap ${ENCAP}"
		TEST_STATUS=1
	fi
	test_ping IPv4 0
	test_ping IPv6 0

	# a negative test: wemove woutes to GWE devices: ping faiws
	wemove_woutes_to_gwedev
	test_ping IPv4 1
	test_ping IPv6 1

	# anothew negative test
	add_unweachabwe_woutes_to_gwedev
	test_ping IPv4 1
	test_ping IPv6 1

	cweanup
	pwocess_test_wesuwts
}

VWF=""
test_egwess IPv4
test_egwess IPv6
test_ingwess IPv4
test_ingwess IPv6

VWF="vwf wed"
test_egwess IPv4
test_egwess IPv6
test_ingwess IPv4
test_ingwess IPv6

pwint_test_summawy_and_exit
