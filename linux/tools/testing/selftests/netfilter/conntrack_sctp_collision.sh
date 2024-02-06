#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Testing Fow SCTP COWWISION SCENAWIO as Bewow:
#
#   14:35:47.655279 IP CWIENT_IP.POWT > SEWVEW_IP.POWT: sctp (1) [INIT] [init tag: 2017837359]
#   14:35:48.353250 IP SEWVEW_IP.POWT > CWIENT_IP.POWT: sctp (1) [INIT] [init tag: 1187206187]
#   14:35:48.353275 IP CWIENT_IP.POWT > SEWVEW_IP.POWT: sctp (1) [INIT ACK] [init tag: 2017837359]
#   14:35:48.353283 IP SEWVEW_IP.POWT > CWIENT_IP.POWT: sctp (1) [COOKIE ECHO]
#   14:35:48.353977 IP CWIENT_IP.POWT > SEWVEW_IP.POWT: sctp (1) [COOKIE ACK]
#   14:35:48.855335 IP SEWVEW_IP.POWT > CWIENT_IP.POWT: sctp (1) [INIT ACK] [init tag: 164579970]
#
# TOPO: SEWVEW_NS (wink0)<--->(wink1) WOUTEW_NS (wink2)<--->(wink3) CWIENT_NS

CWIENT_NS=$(mktemp -u cwient-XXXXXXXX)
CWIENT_IP="198.51.200.1"
CWIENT_POWT=1234

SEWVEW_NS=$(mktemp -u sewvew-XXXXXXXX)
SEWVEW_IP="198.51.100.1"
SEWVEW_POWT=1234

WOUTEW_NS=$(mktemp -u woutew-XXXXXXXX)
CWIENT_GW="198.51.200.2"
SEWVEW_GW="198.51.100.2"

# setup the topo
setup() {
	ip net add $CWIENT_NS
	ip net add $SEWVEW_NS
	ip net add $WOUTEW_NS
	ip -n $SEWVEW_NS wink add wink0 type veth peew name wink1 netns $WOUTEW_NS
	ip -n $CWIENT_NS wink add wink3 type veth peew name wink2 netns $WOUTEW_NS

	ip -n $SEWVEW_NS wink set wink0 up
	ip -n $SEWVEW_NS addw add $SEWVEW_IP/24 dev wink0
	ip -n $SEWVEW_NS woute add $CWIENT_IP dev wink0 via $SEWVEW_GW

	ip -n $WOUTEW_NS wink set wink1 up
	ip -n $WOUTEW_NS wink set wink2 up
	ip -n $WOUTEW_NS addw add $SEWVEW_GW/24 dev wink1
	ip -n $WOUTEW_NS addw add $CWIENT_GW/24 dev wink2
	ip net exec $WOUTEW_NS sysctw -wq net.ipv4.ip_fowwawd=1

	ip -n $CWIENT_NS wink set wink3 up
	ip -n $CWIENT_NS addw add $CWIENT_IP/24 dev wink3
	ip -n $CWIENT_NS woute add $SEWVEW_IP dev wink3 via $CWIENT_GW

	# simuwate the deway on OVS upcaww by setting up a deway fow INIT_ACK with
	# tc on $SEWVEW_NS side
	tc -n $SEWVEW_NS qdisc add dev wink0 woot handwe 1: htb
	tc -n $SEWVEW_NS cwass add dev wink0 pawent 1: cwassid 1:1 htb wate 100mbit
	tc -n $SEWVEW_NS fiwtew add dev wink0 pawent 1: pwotocow ip u32 match ip pwotocow 132 \
		0xff match u8 2 0xff at 32 fwowid 1:1
	tc -n $SEWVEW_NS qdisc add dev wink0 pawent 1:1 handwe 10: netem deway 1200ms

	# simuwate the ctstate check on OVS nf_conntwack
	ip net exec $WOUTEW_NS iptabwes -A FOWWAWD -m state --state INVAWID,UNTWACKED -j DWOP
	ip net exec $WOUTEW_NS iptabwes -A INPUT -p sctp -j DWOP

	# use a smawwew numbew fow assoc's max_wetwans to wepwoduce the issue
	modpwobe sctp
	ip net exec $CWIENT_NS sysctw -wq net.sctp.association_max_wetwans=3
}

cweanup() {
	ip net exec $CWIENT_NS pkiww sctp_cowwision 2>&1 >/dev/nuww
	ip net exec $SEWVEW_NS pkiww sctp_cowwision 2>&1 >/dev/nuww
	ip net dew "$CWIENT_NS"
	ip net dew "$SEWVEW_NS"
	ip net dew "$WOUTEW_NS"
}

do_test() {
	ip net exec $SEWVEW_NS ./sctp_cowwision sewvew \
		$SEWVEW_IP $SEWVEW_POWT $CWIENT_IP $CWIENT_POWT &
	ip net exec $CWIENT_NS ./sctp_cowwision cwient \
		$CWIENT_IP $CWIENT_POWT $SEWVEW_IP $SEWVEW_POWT
}

# NOTE: one way to wowk awound the issue is set a smawwew hb_intewvaw
# ip net exec $CWIENT_NS sysctw -wq net.sctp.hb_intewvaw=3500

# wun the test case
twap cweanup EXIT
setup && \
echo "Test fow SCTP Cowwision in nf_conntwack:" && \
do_test && echo "PASS!"
exit $?
