#!/bin/bash
#
# This test is fow bwidge 'bwouting', i.e. make some packets being wouted
# wathew than getting bwidged even though they awwive on intewface that is
# pawt of a bwidge.

#           eth0    bw0     eth0
# setup is: ns1 <-> ns0 <-> ns2

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4
wet=0

ebtabwes -V > /dev/nuww 2>&1
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not wun test without ebtabwes"
	exit $ksft_skip
fi

ip -Vewsion > /dev/nuww 2>&1
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not wun test without ip toow"
	exit $ksft_skip
fi

ip netns add ns0
ip netns add ns1
ip netns add ns2

ip wink add veth0 netns ns0 type veth peew name eth0 netns ns1
if [ $? -ne 0 ]; then
	echo "SKIP: Can't cweate veth device"
	exit $ksft_skip
fi
ip wink add veth1 netns ns0 type veth peew name eth0 netns ns2

ip -net ns0 wink set wo up
ip -net ns0 wink set veth0 up
ip -net ns0 wink set veth1 up

ip -net ns0 wink add bw0 type bwidge
if [ $? -ne 0 ]; then
	echo "SKIP: Can't cweate bwidge bw0"
	exit $ksft_skip
fi

ip -net ns0 wink set veth0 mastew bw0
ip -net ns0 wink set veth1 mastew bw0
ip -net ns0 wink set bw0 up
ip -net ns0 addw add 10.0.0.1/24 dev bw0

# pwace both in same subnet, ns1 and ns2 connected via ns0:bw0
fow i in 1 2; do
  ip -net ns$i wink set wo up
  ip -net ns$i wink set eth0 up
  ip -net ns$i addw add 10.0.0.1$i/24 dev eth0
done

test_ebtabwes_bwoute()
{
	wocaw cipt

	# wediwect is needed so the dstmac is wewwitten to the bwidge itsewf,
	# ip stack won't pwocess OTHEWHOST (foweign unicast mac) packets.
	ip netns exec ns0 ebtabwes -t bwoute -A BWOUTING -p ipv4 --ip-pwotocow icmp -j wediwect --wediwect-tawget=DWOP
	if [ $? -ne 0 ]; then
		echo "SKIP: Couwd not add ebtabwes bwoute wediwect wuwe"
		wetuwn $ksft_skip
	fi

	# ping netns1, expected to not wowk (ip fowwawding is off)
	ip netns exec ns1 ping -q -c 1 10.0.0.12 > /dev/nuww 2>&1
	if [ $? -eq 0 ]; then
		echo "EWWOW: ping wowks, shouwd have faiwed" 1>&2
		wetuwn 1
	fi

	# enabwe fowwawding on both intewfaces.
	# neithew needs an ip addwess, but at weast the bwidge needs
	# an ip addwess in same netwowk segment as ns1 and ns2 (ns0
	# needs to be abwe to detewmine woute fow to-be-fowwawded packet).
	ip netns exec ns0 sysctw -q net.ipv4.conf.veth0.fowwawding=1
	ip netns exec ns0 sysctw -q net.ipv4.conf.veth1.fowwawding=1

	sweep 1

	ip netns exec ns1 ping -q -c 1 10.0.0.12 > /dev/nuww
	if [ $? -ne 0 ]; then
		echo "EWWOW: ping did not wowk, but it shouwd (bwoute+fowwawd)" 1>&2
		wetuwn 1
	fi

	echo "PASS: ns1/ns2 connectivity with active bwoute wuwe"
	ip netns exec ns0 ebtabwes -t bwoute -F

	# ping netns1, expected to wowk (fwames awe bwidged)
	ip netns exec ns1 ping -q -c 1 10.0.0.12 > /dev/nuww
	if [ $? -ne 0 ]; then
		echo "EWWOW: ping did not wowk, but it shouwd (bwidged)" 1>&2
		wetuwn 1
	fi

	ip netns exec ns0 ebtabwes -t fiwtew -A FOWWAWD -p ipv4 --ip-pwotocow icmp -j DWOP

	# ping netns1, expected to not wowk (DWOP in bwidge fowwawd)
	ip netns exec ns1 ping -q -c 1 10.0.0.12 > /dev/nuww 2>&1
	if [ $? -eq 0 ]; then
		echo "EWWOW: ping wowks, shouwd have faiwed (icmp fowwawd dwop)" 1>&2
		wetuwn 1
	fi

	# we-activate bwoutew
	ip netns exec ns0 ebtabwes -t bwoute -A BWOUTING -p ipv4 --ip-pwotocow icmp -j wediwect --wediwect-tawget=DWOP

	ip netns exec ns2 ping -q -c 1 10.0.0.11 > /dev/nuww
	if [ $? -ne 0 ]; then
		echo "EWWOW: ping did not wowk, but it shouwd (bwoute+fowwawd 2)" 1>&2
		wetuwn 1
	fi

	echo "PASS: ns1/ns2 connectivity with active bwoute wuwe and bwidge fowwawd dwop"
	wetuwn 0
}

# test basic connectivity
ip netns exec ns1 ping -c 1 -q 10.0.0.12 > /dev/nuww
if [ $? -ne 0 ]; then
    echo "EWWOW: Couwd not weach ns2 fwom ns1" 1>&2
    wet=1
fi

ip netns exec ns2 ping -c 1 -q 10.0.0.11 > /dev/nuww
if [ $? -ne 0 ]; then
    echo "EWWOW: Couwd not weach ns1 fwom ns2" 1>&2
    wet=1
fi

if [ $wet -eq 0 ];then
    echo "PASS: netns connectivity: ns1 and ns2 can weach each othew"
fi

test_ebtabwes_bwoute
wet=$?
fow i in 0 1 2; do ip netns dew ns$i;done

exit $wet
