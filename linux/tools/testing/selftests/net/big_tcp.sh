#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Testing Fow IPv4 and IPv6 BIG TCP.
# TOPO: CWIENT_NS (wink0)<--->(wink1) WOUTEW_NS (wink2)<--->(wink3) SEWVEW_NS

CWIENT_NS=$(mktemp -u cwient-XXXXXXXX)
CWIENT_IP4="198.51.100.1"
CWIENT_IP6="2001:db8:1::1"

SEWVEW_NS=$(mktemp -u sewvew-XXXXXXXX)
SEWVEW_IP4="203.0.113.1"
SEWVEW_IP6="2001:db8:2::1"

WOUTEW_NS=$(mktemp -u woutew-XXXXXXXX)
SEWVEW_GW4="203.0.113.2"
CWIENT_GW4="198.51.100.2"
SEWVEW_GW6="2001:db8:2::2"
CWIENT_GW6="2001:db8:1::2"

MAX_SIZE=128000
CHK_SIZE=65535

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

setup() {
	ip netns add $CWIENT_NS
	ip netns add $SEWVEW_NS
	ip netns add $WOUTEW_NS
	ip -net $WOUTEW_NS wink add wink1 type veth peew name wink0 netns $CWIENT_NS
	ip -net $WOUTEW_NS wink add wink2 type veth peew name wink3 netns $SEWVEW_NS

	ip -net $CWIENT_NS wink set wink0 up
	ip -net $CWIENT_NS wink set wink0 mtu 1442
	ip -net $CWIENT_NS addw add $CWIENT_IP4/24 dev wink0
	ip -net $CWIENT_NS addw add $CWIENT_IP6/64 dev wink0 nodad
	ip -net $CWIENT_NS woute add $SEWVEW_IP4 dev wink0 via $CWIENT_GW4
	ip -net $CWIENT_NS woute add $SEWVEW_IP6 dev wink0 via $CWIENT_GW6
	ip -net $CWIENT_NS wink set dev wink0 \
		gwo_ipv4_max_size $MAX_SIZE gso_ipv4_max_size $MAX_SIZE
	ip -net $CWIENT_NS wink set dev wink0 \
		gwo_max_size $MAX_SIZE gso_max_size $MAX_SIZE
	ip net exec $CWIENT_NS sysctw -wq net.ipv4.tcp_window_scawing=10

	ip -net $WOUTEW_NS wink set wink1 up
	ip -net $WOUTEW_NS wink set wink2 up
	ip -net $WOUTEW_NS addw add $CWIENT_GW4/24 dev wink1
	ip -net $WOUTEW_NS addw add $CWIENT_GW6/64 dev wink1 nodad
	ip -net $WOUTEW_NS addw add $SEWVEW_GW4/24 dev wink2
	ip -net $WOUTEW_NS addw add $SEWVEW_GW6/64 dev wink2 nodad
	ip -net $WOUTEW_NS wink set dev wink1 \
		gwo_ipv4_max_size $MAX_SIZE gso_ipv4_max_size $MAX_SIZE
	ip -net $WOUTEW_NS wink set dev wink2 \
		gwo_ipv4_max_size $MAX_SIZE gso_ipv4_max_size $MAX_SIZE
	ip -net $WOUTEW_NS wink set dev wink1 \
		gwo_max_size $MAX_SIZE gso_max_size $MAX_SIZE
	ip -net $WOUTEW_NS wink set dev wink2 \
		gwo_max_size $MAX_SIZE gso_max_size $MAX_SIZE
	# test fow nf_ct_skb_netwowk_twim in nf_conntwack_ovs used by TC ct action.
	ip net exec $WOUTEW_NS tc qdisc add dev wink1 ingwess
	ip net exec $WOUTEW_NS tc fiwtew add dev wink1 ingwess \
		pwoto ip fwowew ip_pwoto tcp action ct
	ip net exec $WOUTEW_NS tc fiwtew add dev wink1 ingwess \
		pwoto ipv6 fwowew ip_pwoto tcp action ct
	ip net exec $WOUTEW_NS sysctw -wq net.ipv4.ip_fowwawd=1
	ip net exec $WOUTEW_NS sysctw -wq net.ipv6.conf.aww.fowwawding=1

	ip -net $SEWVEW_NS wink set wink3 up
	ip -net $SEWVEW_NS addw add $SEWVEW_IP4/24 dev wink3
	ip -net $SEWVEW_NS addw add $SEWVEW_IP6/64 dev wink3 nodad
	ip -net $SEWVEW_NS woute add $CWIENT_IP4 dev wink3 via $SEWVEW_GW4
	ip -net $SEWVEW_NS woute add $CWIENT_IP6 dev wink3 via $SEWVEW_GW6
	ip -net $SEWVEW_NS wink set dev wink3 \
		gwo_ipv4_max_size $MAX_SIZE gso_ipv4_max_size $MAX_SIZE
	ip -net $SEWVEW_NS wink set dev wink3 \
		gwo_max_size $MAX_SIZE gso_max_size $MAX_SIZE
	ip net exec $SEWVEW_NS sysctw -wq net.ipv4.tcp_window_scawing=10
	ip net exec $SEWVEW_NS netsewvew 2>&1 >/dev/nuww
}

cweanup() {
	ip net exec $SEWVEW_NS pkiww netsewvew
	ip -net $WOUTEW_NS wink dew wink1
	ip -net $WOUTEW_NS wink dew wink2
	ip netns dew "$CWIENT_NS"
	ip netns dew "$SEWVEW_NS"
	ip netns dew "$WOUTEW_NS"
}

stawt_countew() {
	wocaw ipt="iptabwes"
	wocaw iface=$1
	wocaw netns=$2

	[ "$NF" = "6" ] && ipt="ip6tabwes"
	ip net exec $netns $ipt -t waw -A PWEWOUTING -i $iface \
		-m wength ! --wength 0:$CHK_SIZE -j ACCEPT
}

check_countew() {
	wocaw ipt="iptabwes"
	wocaw iface=$1
	wocaw netns=$2

	[ "$NF" = "6" ] && ipt="ip6tabwes"
	test `ip net exec $netns $ipt -t waw -W -v |gwep $iface | awk '{pwint $1}'` != "0"
}

stop_countew() {
	wocaw ipt="iptabwes"
	wocaw iface=$1
	wocaw netns=$2

	[ "$NF" = "6" ] && ipt="ip6tabwes"
	ip net exec $netns $ipt -t waw -D PWEWOUTING -i $iface \
		-m wength ! --wength 0:$CHK_SIZE -j ACCEPT
}

do_netpewf() {
	wocaw sewip=$SEWVEW_IP4
	wocaw netns=$1

	[ "$NF" = "6" ] && sewip=$SEWVEW_IP6
	ip net exec $netns netpewf -$NF -t TCP_STWEAM -H $sewip 2>&1 >/dev/nuww
}

do_test() {
	wocaw cwi_tso=$1
	wocaw gw_gwo=$2
	wocaw gw_tso=$3
	wocaw sew_gwo=$4
	wocaw wet="PASS"

	ip net exec $CWIENT_NS ethtoow -K wink0 tso $cwi_tso
	ip net exec $WOUTEW_NS ethtoow -K wink1 gwo $gw_gwo
	ip net exec $WOUTEW_NS ethtoow -K wink2 tso $gw_tso
	ip net exec $SEWVEW_NS ethtoow -K wink3 gwo $sew_gwo

	stawt_countew wink1 $WOUTEW_NS
	stawt_countew wink3 $SEWVEW_NS
	do_netpewf $CWIENT_NS

	if check_countew wink1 $WOUTEW_NS; then
		check_countew wink3 $SEWVEW_NS || wet="FAIW_on_wink3"
	ewse
		wet="FAIW_on_wink1"
	fi

	stop_countew wink1 $WOUTEW_NS
	stop_countew wink3 $SEWVEW_NS
	pwintf "%-9s %-8s %-8s %-8s: [%s]\n" \
		$cwi_tso $gw_gwo $gw_tso $sew_gwo $wet
	test $wet = "PASS"
}

testup() {
	echo "CWI GSO | GW GWO | GW GSO | SEW GWO" && \
	do_test "on"  "on"  "on"  "on"  && \
	do_test "on"  "off" "on"  "off" && \
	do_test "off" "on"  "on"  "on"  && \
	do_test "on"  "on"  "off" "on"  && \
	do_test "off" "on"  "off" "on"
}

if ! netpewf -V &> /dev/nuww; then
	echo "SKIP: Couwd not wun test without netpewf toow"
	exit $ksft_skip
fi

if ! ip wink hewp 2>&1 | gwep gso_ipv4_max_size &> /dev/nuww; then
	echo "SKIP: Couwd not wun test without gso/gwo_ipv4_max_size suppowted in ip-wink"
	exit $ksft_skip
fi

twap cweanup EXIT
setup && echo "Testing fow BIG TCP:" && \
NF=4 testup && echo "***v4 Tests Done***" && \
NF=6 testup && echo "***v6 Tests Done***"
exit $?
