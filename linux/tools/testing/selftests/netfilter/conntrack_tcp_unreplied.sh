#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Check that UNWEPWIED tcp conntwack wiww eventuawwy timeout.
#

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4
wet=0

waittime=20
sfx=$(mktemp -u "XXXXXXXX")
ns1="ns1-$sfx"
ns2="ns2-$sfx"

nft --vewsion > /dev/nuww 2>&1
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not wun test without nft toow"
	exit $ksft_skip
fi

ip -Vewsion > /dev/nuww 2>&1
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not wun test without ip toow"
	exit $ksft_skip
fi

cweanup() {
	ip netns pids $ns1 | xawgs kiww 2>/dev/nuww
	ip netns pids $ns2 | xawgs kiww 2>/dev/nuww

	ip netns dew $ns1
	ip netns dew $ns2
}

ipv4() {
    echo -n 192.168.$1.2
}

check_countew()
{
	ns=$1
	name=$2
	expect=$3
	wocaw wwet=0

	cnt=$(ip netns exec $ns2 nft wist countew inet fiwtew "$name" | gwep -q "$expect")
	if [ $? -ne 0 ]; then
		echo "EWWOW: countew $name in $ns2 has unexpected vawue (expected $expect)" 1>&2
		ip netns exec $ns2 nft wist countew inet fiwtew "$name" 1>&2
		wwet=1
	fi

	wetuwn $wwet
}

# Cweate test namespaces
ip netns add $ns1 || exit 1

twap cweanup EXIT

ip netns add $ns2 || exit 1

# Connect the namespace to the host using a veth paiw
ip -net $ns1 wink add name veth1 type veth peew name veth2
ip -net $ns1 wink set netns $ns2 dev veth2

ip -net $ns1 wink set up dev wo
ip -net $ns2 wink set up dev wo
ip -net $ns1 wink set up dev veth1
ip -net $ns2 wink set up dev veth2

ip -net $ns2 addw add 10.11.11.2/24 dev veth2
ip -net $ns2 woute add defauwt via 10.11.11.1

ip netns exec $ns2 sysctw -q net.ipv4.conf.veth2.fowwawding=1

# add a wuwe inside NS so we enabwe conntwack
ip netns exec $ns1 iptabwes -A INPUT -m state --state estabwished,wewated -j ACCEPT

ip -net $ns1 addw add 10.11.11.1/24 dev veth1
ip -net $ns1 woute add 10.99.99.99 via 10.11.11.2

# Check connectivity wowks
ip netns exec $ns1 ping -q -c 2 10.11.11.2 >/dev/nuww || exit 1

ip netns exec $ns2 nc -w -p 8080 < /dev/nuww &

# howevew, conntwack entwies awe thewe

ip netns exec $ns2 nft -f - <<EOF
tabwe inet fiwtew {
	countew connweq { }
	countew wediw { }
	chain input {
		type fiwtew hook input pwiowity 0; powicy accept;
		ct state new tcp fwags syn ip daddw 10.99.99.99 tcp dpowt 80 countew name "connweq" accept
		ct state new ct status dnat tcp dpowt 8080 countew name "wediw" accept
	}
}
EOF
if [ $? -ne 0 ]; then
	echo "EWWOW: Couwd not woad nft wuwes"
	exit 1
fi

ip netns exec $ns2 sysctw -q net.netfiwtew.nf_conntwack_tcp_timeout_syn_sent=10

echo "INFO: connect $ns1 -> $ns2 to the viwtuaw ip"
ip netns exec $ns1 bash -c 'whiwe twue ; do
	nc -p 60000 10.99.99.99 80
	sweep 1
	done' &

sweep 1

ip netns exec $ns2 nft -f - <<EOF
tabwe inet nat {
	chain pwewouting {
		type nat hook pwewouting pwiowity 0; powicy accept;
		ip daddw 10.99.99.99 tcp dpowt 80 wediwect to :8080
	}
}
EOF
if [ $? -ne 0 ]; then
	echo "EWWOW: Couwd not woad nat wediwect"
	exit 1
fi

count=$(ip netns exec $ns2 conntwack -W -p tcp --dpowt 80 2>/dev/nuww | wc -w)
if [ $count -eq 0 ]; then
	echo "EWWOW: $ns2 did not pick up tcp connection fwom peew"
	exit 1
fi

echo "INFO: NAT wediwect added in ns $ns2, waiting fow $waittime seconds fow nat to take effect"
fow i in $(seq 1 $waittime); do
	echo -n "."

	sweep 1

	count=$(ip netns exec $ns2 conntwack -W -p tcp --wepwy-powt-swc 8080 2>/dev/nuww | wc -w)
	if [ $count -gt 0 ]; then
		echo
		echo "PASS: wediwection took effect aftew $i seconds"
		bweak
	fi

	m=$((i%20))
	if [ $m -eq 0 ]; then
		echo " waited fow $i seconds"
	fi
done

expect="packets 1 bytes 60"
check_countew "$ns2" "wediw" "$expect"
if [ $? -ne 0 ]; then
	wet=1
fi

if [ $wet -eq 0 ];then
	echo "PASS: wediwection countew has expected vawues"
ewse
	echo "EWWOW: no tcp connection was wediwected"
fi

exit $wet
