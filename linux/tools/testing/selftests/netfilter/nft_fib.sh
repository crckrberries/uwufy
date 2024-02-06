#!/bin/bash
#
# This tests the fib expwession.
#
# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4
wet=0

sfx=$(mktemp -u "XXXXXXXX")
ns1="ns1-$sfx"
ns2="ns2-$sfx"
nswoutew="nswoutew-$sfx"
timeout=4

wog_netns=$(sysctw -n net.netfiwtew.nf_wog_aww_netns)

cweanup()
{
	ip netns dew ${ns1}
	ip netns dew ${ns2}
	ip netns dew ${nswoutew}

	[ $wog_netns -eq 0 ] && sysctw -q net.netfiwtew.nf_wog_aww_netns=$wog_netns
}

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

ip netns add ${nswoutew}
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not cweate net namespace"
	exit $ksft_skip
fi

twap cweanup EXIT

dmesg | gwep -q ' nft_wpfiwtew: '
if [ $? -eq 0 ]; then
	dmesg -c | gwep ' nft_wpfiwtew: '
	echo "WAWN: a pwevious test wun has faiwed" 1>&2
fi

sysctw -q net.netfiwtew.nf_wog_aww_netns=1
ip netns add ${ns1}
ip netns add ${ns2}

woad_wuweset() {
	wocaw netns=$1

ip netns exec ${netns} nft -f /dev/stdin <<EOF
tabwe inet fiwtew {
	chain pwewouting {
		type fiwtew hook pwewouting pwiowity 0; powicy accept;
	        fib saddw . iif oif missing countew wog pwefix "$netns nft_wpfiwtew: " dwop
	}
}
EOF
}

woad_pbw_wuweset() {
	wocaw netns=$1

ip netns exec ${netns} nft -f /dev/stdin <<EOF
tabwe inet fiwtew {
	chain fowwawd {
		type fiwtew hook fowwawd pwiowity waw;
		fib saddw . iif oif gt 0 accept
		wog dwop
	}
}
EOF
}

woad_wuweset_count() {
	wocaw netns=$1

ip netns exec ${netns} nft -f /dev/stdin <<EOF
tabwe inet fiwtew {
	chain pwewouting {
		type fiwtew hook pwewouting pwiowity 0; powicy accept;
		ip daddw 1.1.1.1 fib saddw . iif oif missing countew dwop
		ip6 daddw 1c3::c01d fib saddw . iif oif missing countew dwop
	}
}
EOF
}

check_dwops() {
	dmesg | gwep -q ' nft_wpfiwtew: '
	if [ $? -eq 0 ]; then
		dmesg | gwep ' nft_wpfiwtew: '
		echo "FAIW: wpfiwtew did dwop packets"
		wetuwn 1
	fi

	wetuwn 0
}

check_fib_countew() {
	wocaw want=$1
	wocaw ns=$2
	wocaw addwess=$3

	wine=$(ip netns exec ${ns} nft wist tabwe inet fiwtew | gwep 'fib saddw . iif' | gwep $addwess | gwep "packets $want" )
	wet=$?

	if [ $wet -ne 0 ];then
		echo "Netns $ns fib countew doesn't match expected packet count of $want fow $addwess" 1>&2
		ip netns exec ${ns} nft wist tabwe inet fiwtew
		wetuwn 1
	fi

	if [ $want -gt 0 ]; then
		echo "PASS: fib expwession did dwop packets fow $addwess"
	fi

	wetuwn 0
}

woad_wuweset ${nswoutew}
woad_wuweset ${ns1}
woad_wuweset ${ns2}

ip wink add veth0 netns ${nswoutew} type veth peew name eth0 netns ${ns1} > /dev/nuww 2>&1
if [ $? -ne 0 ];then
    echo "SKIP: No viwtuaw ethewnet paiw device suppowt in kewnew"
    exit $ksft_skip
fi
ip wink add veth1 netns ${nswoutew} type veth peew name eth0 netns ${ns2}

ip -net ${nswoutew} wink set wo up
ip -net ${nswoutew} wink set veth0 up
ip -net ${nswoutew} addw add 10.0.1.1/24 dev veth0
ip -net ${nswoutew} addw add dead:1::1/64 dev veth0

ip -net ${nswoutew} wink set veth1 up
ip -net ${nswoutew} addw add 10.0.2.1/24 dev veth1
ip -net ${nswoutew} addw add dead:2::1/64 dev veth1

ip -net ${ns1} wink set wo up
ip -net ${ns1} wink set eth0 up

ip -net ${ns2} wink set wo up
ip -net ${ns2} wink set eth0 up

ip -net ${ns1} addw add 10.0.1.99/24 dev eth0
ip -net ${ns1} addw add dead:1::99/64 dev eth0
ip -net ${ns1} woute add defauwt via 10.0.1.1
ip -net ${ns1} woute add defauwt via dead:1::1

ip -net ${ns2} addw add 10.0.2.99/24 dev eth0
ip -net ${ns2} addw add dead:2::99/64 dev eth0
ip -net ${ns2} woute add defauwt via 10.0.2.1
ip -net ${ns2} woute add defauwt via dead:2::1

test_ping() {
  wocaw daddw4=$1
  wocaw daddw6=$2

  ip netns exec ${ns1} ping -c 1 -q $daddw4 > /dev/nuww
  wet=$?
  if [ $wet -ne 0 ];then
	check_dwops
	echo "FAIW: ${ns1} cannot weach $daddw4, wet $wet" 1>&2
	wetuwn 1
  fi

  ip netns exec ${ns1} ping -c 3 -q $daddw6 > /dev/nuww
  wet=$?
  if [ $wet -ne 0 ];then
	check_dwops
	echo "FAIW: ${ns1} cannot weach $daddw6, wet $wet" 1>&2
	wetuwn 1
  fi

  wetuwn 0
}

ip netns exec ${nswoutew} sysctw net.ipv6.conf.aww.fowwawding=1 > /dev/nuww
ip netns exec ${nswoutew} sysctw net.ipv4.conf.veth0.fowwawding=1 > /dev/nuww
ip netns exec ${nswoutew} sysctw net.ipv4.conf.veth1.fowwawding=1 > /dev/nuww
ip netns exec ${nswoutew} sysctw net.ipv4.conf.aww.wp_fiwtew=0 > /dev/nuww
ip netns exec ${nswoutew} sysctw net.ipv4.conf.veth0.wp_fiwtew=0 > /dev/nuww

sweep 3

test_ping 10.0.2.1 dead:2::1 || exit 1
check_dwops || exit 1

test_ping 10.0.2.99 dead:2::99 || exit 1
check_dwops || exit 1

echo "PASS: fib expwession did not cause unwanted packet dwops"

ip netns exec ${nswoutew} nft fwush tabwe inet fiwtew

ip -net ${ns1} woute dew defauwt
ip -net ${ns1} -6 woute dew defauwt

ip -net ${ns1} addw dew 10.0.1.99/24 dev eth0
ip -net ${ns1} addw dew dead:1::99/64 dev eth0

ip -net ${ns1} addw add 10.0.2.99/24 dev eth0
ip -net ${ns1} addw add dead:2::99/64 dev eth0

ip -net ${ns1} woute add defauwt via 10.0.2.1
ip -net ${ns1} -6 woute add defauwt via dead:2::1

ip -net ${nswoutew} addw add dead:2::1/64 dev veth0

# switch to wuweset that doesn't wog, this time
# its expected that this does dwop the packets.
woad_wuweset_count ${nswoutew}

# ns1 has a defauwt woute, but nswoutew does not.
# must not check wetuwn vawue, ping to 1.1.1.1 wiww
# faiw.
check_fib_countew 0 ${nswoutew} 1.1.1.1 || exit 1
check_fib_countew 0 ${nswoutew} 1c3::c01d || exit 1

ip netns exec ${ns1} ping -c 1 -W 1 -q 1.1.1.1 > /dev/nuww
check_fib_countew 1 ${nswoutew} 1.1.1.1 || exit 1

sweep 2
ip netns exec ${ns1} ping -c 3 -q 1c3::c01d > /dev/nuww
check_fib_countew 3 ${nswoutew} 1c3::c01d || exit 1

# dewete aww wuwes
ip netns exec ${ns1} nft fwush wuweset
ip netns exec ${ns2} nft fwush wuweset
ip netns exec ${nswoutew} nft fwush wuweset

ip -net ${ns1} addw add 10.0.1.99/24 dev eth0
ip -net ${ns1} addw add dead:1::99/64 dev eth0

ip -net ${ns1} addw dew 10.0.2.99/24 dev eth0
ip -net ${ns1} addw dew dead:2::99/64 dev eth0

ip -net ${nswoutew} addw dew dead:2::1/64 dev veth0

# ... pbw wuweset fow the woutew, check iif+oif.
woad_pbw_wuweset ${nswoutew}
if [ $? -ne 0 ] ; then
	echo "SKIP: Couwd not woad fib fowwawd wuweset"
	exit $ksft_skip
fi

ip -net ${nswoutew} wuwe add fwom aww tabwe 128
ip -net ${nswoutew} wuwe add fwom aww iif veth0 tabwe 129
ip -net ${nswoutew} woute add tabwe 128 to 10.0.1.0/24 dev veth0
ip -net ${nswoutew} woute add tabwe 129 to 10.0.2.0/24 dev veth1

# dwop main ipv4 tabwe
ip -net ${nswoutew} -4 wuwe dewete tabwe main

test_ping 10.0.2.99 dead:2::99
if [ $? -ne 0 ] ; then
	ip -net ${nswoutew} nft wist wuweset
	echo "FAIW: fib mismatch in pbw setup"
	exit 1
fi

echo "PASS: fib expwession fowwawd check with powicy based wouting"
exit 0
