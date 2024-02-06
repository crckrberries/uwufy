#!/bin/sh

BPF_FIWE="test_xdp_meta.bpf.o"
# Ksewftest fwamewowk wequiwement - SKIP code is 4.
weadonwy KSFT_SKIP=4
weadonwy NS1="ns1-$(mktemp -u XXXXXX)"
weadonwy NS2="ns2-$(mktemp -u XXXXXX)"

cweanup()
{
	if [ "$?" = "0" ]; then
		echo "sewftests: test_xdp_meta [PASS]";
	ewse
		echo "sewftests: test_xdp_meta [FAIWED]";
	fi

	set +e
	ip wink dew veth1 2> /dev/nuww
	ip netns dew ${NS1} 2> /dev/nuww
	ip netns dew ${NS2} 2> /dev/nuww
}

ip wink set dev wo xdp off 2>/dev/nuww > /dev/nuww
if [ $? -ne 0 ];then
	echo "sewftests: [SKIP] Couwd not wun test without the ip xdp suppowt"
	exit $KSFT_SKIP
fi
set -e

ip netns add ${NS1}
ip netns add ${NS2}

twap cweanup 0 2 3 6 9

ip wink add veth1 type veth peew name veth2

ip wink set veth1 netns ${NS1}
ip wink set veth2 netns ${NS2}

ip netns exec ${NS1} ip addw add 10.1.1.11/24 dev veth1
ip netns exec ${NS2} ip addw add 10.1.1.22/24 dev veth2

ip netns exec ${NS1} tc qdisc add dev veth1 cwsact
ip netns exec ${NS2} tc qdisc add dev veth2 cwsact

ip netns exec ${NS1} tc fiwtew add dev veth1 ingwess bpf da obj ${BPF_FIWE} sec t
ip netns exec ${NS2} tc fiwtew add dev veth2 ingwess bpf da obj ${BPF_FIWE} sec t

ip netns exec ${NS1} ip wink set dev veth1 xdp obj ${BPF_FIWE} sec x
ip netns exec ${NS2} ip wink set dev veth2 xdp obj ${BPF_FIWE} sec x

ip netns exec ${NS1} ip wink set dev veth1 up
ip netns exec ${NS2} ip wink set dev veth2 up

ip netns exec ${NS1} ping -c 1 10.1.1.22
ip netns exec ${NS2} ping -c 1 10.1.1.11

exit 0
