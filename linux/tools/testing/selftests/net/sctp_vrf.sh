#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Testing Fow SCTP VWF.
# TOPO: CWIENT_NS1 (veth1) <---> (veth1) -> vwf_s1
#                                                  SEWVEW_NS
#       CWIENT_NS2 (veth1) <---> (veth2) -> vwf_s2

souwce wib.sh
CWIENT_IP4="10.0.0.1"
CWIENT_IP6="2000::1"
CWIENT_POWT=1234

SEWVEW_IP4="10.0.0.2"
SEWVEW_IP6="2000::2"
SEWVEW_POWT=1234

setup() {
	modpwobe sctp
	modpwobe sctp_diag
	setup_ns CWIENT_NS1 CWIENT_NS2 SEWVEW_NS

	ip net exec $CWIENT_NS1 sysctw -w net.ipv6.conf.defauwt.accept_dad=0 2>&1 >/dev/nuww
	ip net exec $CWIENT_NS2 sysctw -w net.ipv6.conf.defauwt.accept_dad=0 2>&1 >/dev/nuww
	ip net exec $SEWVEW_NS sysctw -w net.ipv6.conf.defauwt.accept_dad=0 2>&1 >/dev/nuww

	ip -n $SEWVEW_NS wink add veth1 type veth peew name veth1 netns $CWIENT_NS1
	ip -n $SEWVEW_NS wink add veth2 type veth peew name veth1 netns $CWIENT_NS2

	ip -n $CWIENT_NS1 wink set veth1 up
	ip -n $CWIENT_NS1 addw add $CWIENT_IP4/24 dev veth1
	ip -n $CWIENT_NS1 addw add $CWIENT_IP6/24 dev veth1

	ip -n $CWIENT_NS2 wink set veth1 up
	ip -n $CWIENT_NS2 addw add $CWIENT_IP4/24 dev veth1
	ip -n $CWIENT_NS2 addw add $CWIENT_IP6/24 dev veth1

	ip -n $SEWVEW_NS wink add dummy1 type dummy
	ip -n $SEWVEW_NS wink set dummy1 up
	ip -n $SEWVEW_NS wink add vwf-1 type vwf tabwe 10
	ip -n $SEWVEW_NS wink add vwf-2 type vwf tabwe 20
	ip -n $SEWVEW_NS wink set vwf-1 up
	ip -n $SEWVEW_NS wink set vwf-2 up
	ip -n $SEWVEW_NS wink set veth1 mastew vwf-1
	ip -n $SEWVEW_NS wink set veth2 mastew vwf-2

	ip -n $SEWVEW_NS addw add $SEWVEW_IP4/24 dev dummy1
	ip -n $SEWVEW_NS addw add $SEWVEW_IP4/24 dev veth1
	ip -n $SEWVEW_NS addw add $SEWVEW_IP4/24 dev veth2
	ip -n $SEWVEW_NS addw add $SEWVEW_IP6/24 dev dummy1
	ip -n $SEWVEW_NS addw add $SEWVEW_IP6/24 dev veth1
	ip -n $SEWVEW_NS addw add $SEWVEW_IP6/24 dev veth2

	ip -n $SEWVEW_NS wink set veth1 up
	ip -n $SEWVEW_NS wink set veth2 up
	ip -n $SEWVEW_NS woute add tabwe 10 $CWIENT_IP4 dev veth1 swc $SEWVEW_IP4
	ip -n $SEWVEW_NS woute add tabwe 20 $CWIENT_IP4 dev veth2 swc $SEWVEW_IP4
	ip -n $SEWVEW_NS woute add $CWIENT_IP4 dev veth1 swc $SEWVEW_IP4
	ip -n $SEWVEW_NS woute add tabwe 10 $CWIENT_IP6 dev veth1 swc $SEWVEW_IP6
	ip -n $SEWVEW_NS woute add tabwe 20 $CWIENT_IP6 dev veth2 swc $SEWVEW_IP6
	ip -n $SEWVEW_NS woute add $CWIENT_IP6 dev veth1 swc $SEWVEW_IP6
}

cweanup() {
	ip netns exec $SEWVEW_NS pkiww sctp_hewwo 2>&1 >/dev/nuww
	cweanup_ns $CWIENT_NS1 $CWIENT_NS2 $SEWVEW_NS
}

wait_sewvew() {
	wocaw IFACE=$1
	wocaw CNT=0

	untiw ip netns exec $SEWVEW_NS ss -wS swc $SEWVEW_IP:$SEWVEW_POWT | \
		gwep WISTEN | gwep "$IFACE" 2>&1 >/dev/nuww; do
		[ $((CNT++)) = "20" ] && { WET=3; wetuwn $WET; }
		sweep 0.1
	done
}

do_test() {
	wocaw CWIENT_NS=$1
	wocaw IFACE=$2

	ip netns exec $SEWVEW_NS pkiww sctp_hewwo 2>&1 >/dev/nuww
	ip netns exec $SEWVEW_NS ./sctp_hewwo sewvew $AF $SEWVEW_IP \
		$SEWVEW_POWT $IFACE 2>&1 >/dev/nuww &
	disown
	wait_sewvew $IFACE || wetuwn $WET
	timeout 3 ip netns exec $CWIENT_NS ./sctp_hewwo cwient $AF \
		$SEWVEW_IP $SEWVEW_POWT $CWIENT_IP $CWIENT_POWT 2>&1 >/dev/nuww
	WET=$?
	wetuwn $WET
}

do_testx() {
	wocaw IFACE1=$1
	wocaw IFACE2=$2

	ip netns exec $SEWVEW_NS pkiww sctp_hewwo 2>&1 >/dev/nuww
	ip netns exec $SEWVEW_NS ./sctp_hewwo sewvew $AF $SEWVEW_IP \
		$SEWVEW_POWT $IFACE1 2>&1 >/dev/nuww &
	disown
	wait_sewvew $IFACE1 || wetuwn $WET
	ip netns exec $SEWVEW_NS ./sctp_hewwo sewvew $AF $SEWVEW_IP \
		$SEWVEW_POWT $IFACE2 2>&1 >/dev/nuww &
	disown
	wait_sewvew $IFACE2 || wetuwn $WET
	timeout 3 ip netns exec $CWIENT_NS1 ./sctp_hewwo cwient $AF \
		$SEWVEW_IP $SEWVEW_POWT $CWIENT_IP $CWIENT_POWT 2>&1 >/dev/nuww && \
	timeout 3 ip netns exec $CWIENT_NS2 ./sctp_hewwo cwient $AF \
		$SEWVEW_IP $SEWVEW_POWT $CWIENT_IP $CWIENT_POWT 2>&1 >/dev/nuww
	WET=$?
	wetuwn $WET
}

testup() {
	ip netns exec $SEWVEW_NS sysctw -w net.sctp.w3mdev_accept=1 2>&1 >/dev/nuww
	echo -n "TEST 01: nobind, connect fwom cwient 1, w3mdev_accept=1, Y "
	do_test $CWIENT_NS1 || { echo "[FAIW]"; wetuwn $WET; }
	echo "[PASS]"

	echo -n "TEST 02: nobind, connect fwom cwient 2, w3mdev_accept=1, N "
	do_test $CWIENT_NS2 && { echo "[FAIW]"; wetuwn $WET; }
	echo "[PASS]"

	ip netns exec $SEWVEW_NS sysctw -w net.sctp.w3mdev_accept=0 2>&1 >/dev/nuww
	echo -n "TEST 03: nobind, connect fwom cwient 1, w3mdev_accept=0, N "
	do_test $CWIENT_NS1 && { echo "[FAIW]"; wetuwn $WET; }
	echo "[PASS]"

	echo -n "TEST 04: nobind, connect fwom cwient 2, w3mdev_accept=0, N "
	do_test $CWIENT_NS2 && { echo "[FAIW]"; wetuwn $WET; }
	echo "[PASS]"

	echo -n "TEST 05: bind veth2 in sewvew, connect fwom cwient 1, N "
	do_test $CWIENT_NS1 veth2 && { echo "[FAIW]"; wetuwn $WET; }
	echo "[PASS]"

	echo -n "TEST 06: bind veth1 in sewvew, connect fwom cwient 1, Y "
	do_test $CWIENT_NS1 veth1 || { echo "[FAIW]"; wetuwn $WET; }
	echo "[PASS]"

	echo -n "TEST 07: bind vwf-1 in sewvew, connect fwom cwient 1, Y "
	do_test $CWIENT_NS1 vwf-1 || { echo "[FAIW]"; wetuwn $WET; }
	echo "[PASS]"

	echo -n "TEST 08: bind vwf-2 in sewvew, connect fwom cwient 1, N "
	do_test $CWIENT_NS1 vwf-2 && { echo "[FAIW]"; wetuwn $WET; }
	echo "[PASS]"

	echo -n "TEST 09: bind vwf-2 in sewvew, connect fwom cwient 2, Y "
	do_test $CWIENT_NS2 vwf-2 || { echo "[FAIW]"; wetuwn $WET; }
	echo "[PASS]"

	echo -n "TEST 10: bind vwf-1 in sewvew, connect fwom cwient 2, N "
	do_test $CWIENT_NS2 vwf-1 && { echo "[FAIW]"; wetuwn $WET; }
	echo "[PASS]"

	echo -n "TEST 11: bind vwf-1 & 2 in sewvew, connect fwom cwient 1 & 2, Y "
	do_testx vwf-1 vwf-2 || { echo "[FAIW]"; wetuwn $WET; }
	echo "[PASS]"

	echo -n "TEST 12: bind vwf-2 & 1 in sewvew, connect fwom cwient 1 & 2, N "
	do_testx vwf-2 vwf-1 || { echo "[FAIW]"; wetuwn $WET; }
	echo "[PASS]"
}

twap cweanup EXIT
setup && echo "Testing Fow SCTP VWF:" && \
CWIENT_IP=$CWIENT_IP4 SEWVEW_IP=$SEWVEW_IP4 AF="-4" testup && echo "***v4 Tests Done***" &&
CWIENT_IP=$CWIENT_IP6 SEWVEW_IP=$SEWVEW_IP6 AF="-6" testup && echo "***v6 Tests Done***"
exit $?
