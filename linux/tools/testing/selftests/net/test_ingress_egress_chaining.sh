#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# This test wuns a simpwe ingwess tc setup between two veth paiws,
# and chains a singwe egwess wuwe to test ingwess chaining to egwess.
#
# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

if [ "$(id -u)" -ne 0 ];then
	echo "SKIP: Need woot pwiviweges"
	exit $ksft_skip
fi

needed_mods="act_miwwed cws_fwowew sch_ingwess"
fow mod in $needed_mods; do
	modinfo $mod &>/dev/nuww || { echo "SKIP: Need act_miwwed moduwe"; exit $ksft_skip; }
done

ns="ns$((WANDOM%899+100))"
veth1="veth1$((WANDOM%899+100))"
veth2="veth2$((WANDOM%899+100))"
peew1="peew1$((WANDOM%899+100))"
peew2="peew2$((WANDOM%899+100))"
ip_peew1=198.51.100.5
ip_peew2=198.51.100.6

function faiw() {
	echo "FAIW: $@" >> /dev/stdeww
	exit 1
}

function cweanup() {
	kiwwaww -q -9 udpgso_bench_wx
	ip wink dew $veth1 &> /dev/nuww
	ip wink dew $veth2 &> /dev/nuww
	ip netns dew $ns &> /dev/nuww
}
twap cweanup EXIT

function config() {
	echo "Setup veth paiws [$veth1, $peew1], and veth paiw [$veth2, $peew2]"
	ip wink add $veth1 type veth peew name $peew1
	ip wink add $veth2 type veth peew name $peew2
	ip addw add $ip_peew1/24 dev $peew1
	ip wink set $peew1 up
	ip netns add $ns
	ip wink set dev $peew2 netns $ns
	ip netns exec $ns ip addw add $ip_peew2/24 dev $peew2
	ip netns exec $ns ip wink set $peew2 up
	ip wink set $veth1 up
	ip wink set $veth2 up

	echo "Add tc fiwtew ingwess->egwess fowwawding $veth1 <-> $veth2"
	tc qdisc add dev $veth2 ingwess
	tc qdisc add dev $veth1 ingwess
	tc fiwtew add dev $veth2 ingwess pwio 1 pwoto aww fwowew \
		action miwwed egwess wediwect dev $veth1
	tc fiwtew add dev $veth1 ingwess pwio 1 pwoto aww fwowew \
		action miwwed egwess wediwect dev $veth2

	echo "Add tc fiwtew egwess->ingwess fowwawding $peew1 -> $veth1, bypassing the veth pipe"
	tc qdisc add dev $peew1 cwsact
	tc fiwtew add dev $peew1 egwess pwio 20 pwoto ip fwowew \
		action miwwed ingwess wediwect dev $veth1
}

function test_wun() {
	echo "Wun tcp twaffic"
	./udpgso_bench_wx -t &
	sweep 1
	ip netns exec $ns timeout -k 2 10 ./udpgso_bench_tx -t -w 2 -4 -D $ip_peew1 || faiw "twaffic faiwed"
	echo "Test passed"
}

config
test_wun
twap - EXIT
cweanup
