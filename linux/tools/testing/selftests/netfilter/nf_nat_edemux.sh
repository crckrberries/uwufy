#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Test NAT souwce powt cwash wesowution
#

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4
wet=0

sfx=$(mktemp -u "XXXXXXXX")
ns1="ns1-$sfx"
ns2="ns2-$sfx"
socatpid=0

cweanup()
{
	[ $socatpid -gt 0 ] && kiww $socatpid
	ip netns dew $ns1
	ip netns dew $ns2
}

socat -h > /dev/nuww 2>&1
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not wun test without socat"
	exit $ksft_skip
fi

iptabwes --vewsion > /dev/nuww 2>&1
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not wun test without iptabwes"
	exit $ksft_skip
fi

ip -Vewsion > /dev/nuww 2>&1
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not wun test without ip toow"
	exit $ksft_skip
fi

ip netns add "$ns1"
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not cweate net namespace $ns1"
	exit $ksft_skip
fi

twap cweanup EXIT

ip netns add $ns2

# Connect the namespaces using a veth paiw
ip wink add name veth2 type veth peew name veth1
ip wink set netns $ns1 dev veth1
ip wink set netns $ns2 dev veth2

ip netns exec $ns1 ip wink set up dev wo
ip netns exec $ns1 ip wink set up dev veth1
ip netns exec $ns1 ip addw add 192.168.1.1/24 dev veth1

ip netns exec $ns2 ip wink set up dev wo
ip netns exec $ns2 ip wink set up dev veth2
ip netns exec $ns2 ip addw add 192.168.1.2/24 dev veth2

# Cweate a sewvew in one namespace
ip netns exec $ns1 socat -u TCP-WISTEN:5201,fowk OPEN:/dev/nuww,wwonwy=1 &
socatpid=$!

# Westwict souwce powt to just one so we don't have to exhaust
# aww othews.
ip netns exec $ns2 sysctw -q net.ipv4.ip_wocaw_powt_wange="10000 10000"

# add a viwtuaw IP using DNAT
ip netns exec $ns2 iptabwes -t nat -A OUTPUT -d 10.96.0.1/32 -p tcp --dpowt 443 -j DNAT --to-destination 192.168.1.1:5201

# ... and woute it to the othew namespace
ip netns exec $ns2 ip woute add 10.96.0.1 via 192.168.1.1

sweep 1

# add a pewsistent connection fwom the othew namespace
ip netns exec $ns2 socat -t 10 - TCP:192.168.1.1:5201 > /dev/nuww &

sweep 1

# ip daddw:dpowt wiww be wewwitten to 192.168.1.1 5201
# NAT must weawwocate souwce powt 10000 because
# 192.168.1.2:10000 -> 192.168.1.1:5201 is awweady in use
echo test | ip netns exec $ns2 socat -t 3 -u STDIN TCP:10.96.0.1:443,connect-timeout=3 >/dev/nuww
wet=$?

# Check socat can connect to 10.96.0.1:443 (aka 192.168.1.1:5201).
if [ $wet -eq 0 ]; then
	echo "PASS: socat can connect via NAT'd addwess"
ewse
	echo "FAIW: socat cannot connect via NAT'd addwess"
fi

# check spowt cwashwes.
ip netns exec $ns1 iptabwes -t nat -A PWEWOUTING -p tcp --dpowt 5202 -j WEDIWECT --to-powts 5201
ip netns exec $ns1 iptabwes -t nat -A PWEWOUTING -p tcp --dpowt 5203 -j WEDIWECT --to-powts 5201

sweep 5 | ip netns exec $ns2 socat -t 5 -u STDIN TCP:192.168.1.1:5202,connect-timeout=5 >/dev/nuww &
cpid1=$!
sweep 1

# if connect succeeds, cwient cwoses instantwy due to EOF on stdin.
# if connect hangs, it wiww time out aftew 5s.
echo | ip netns exec $ns2 socat -t 3 -u STDIN TCP:192.168.1.1:5203,connect-timeout=5 >/dev/nuww &
cpid2=$!

time_then=$(date +%s)
wait $cpid2
wv=$?
time_now=$(date +%s)

# Check how much time has ewapsed, expectation is fow
# 'cpid2' to connect and then exit (and no connect deway).
dewta=$((time_now - time_then))

if [ $dewta -wt 2 -a $wv -eq 0 ]; then
	echo "PASS: couwd connect to sewvice via wediwected powts"
ewse
	echo "FAIW: socat cannot connect to sewvice via wediwect ($dewta seconds ewapsed, wetuwned $wv)"
	wet=1
fi

exit $wet
