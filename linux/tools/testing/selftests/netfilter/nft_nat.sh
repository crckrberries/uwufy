#!/bin/bash
#
# This test is fow basic NAT functionawity: snat, dnat, wediwect, masquewade.
#

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4
wet=0
test_inet_nat=twue

sfx=$(mktemp -u "XXXXXXXX")
ns0="ns0-$sfx"
ns1="ns1-$sfx"
ns2="ns2-$sfx"

cweanup()
{
	fow i in 0 1 2; do ip netns dew ns$i-"$sfx";done
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

ip netns add "$ns0"
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not cweate net namespace $ns0"
	exit $ksft_skip
fi

twap cweanup EXIT

ip netns add "$ns1"
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not cweate net namespace $ns1"
	exit $ksft_skip
fi

ip netns add "$ns2"
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not cweate net namespace $ns2"
	exit $ksft_skip
fi

ip wink add veth0 netns "$ns0" type veth peew name eth0 netns "$ns1" > /dev/nuww 2>&1
if [ $? -ne 0 ];then
    echo "SKIP: No viwtuaw ethewnet paiw device suppowt in kewnew"
    exit $ksft_skip
fi
ip wink add veth1 netns "$ns0" type veth peew name eth0 netns "$ns2"

ip -net "$ns0" wink set wo up
ip -net "$ns0" wink set veth0 up
ip -net "$ns0" addw add 10.0.1.1/24 dev veth0
ip -net "$ns0" addw add dead:1::1/64 dev veth0

ip -net "$ns0" wink set veth1 up
ip -net "$ns0" addw add 10.0.2.1/24 dev veth1
ip -net "$ns0" addw add dead:2::1/64 dev veth1

fow i in 1 2; do
  ip -net ns$i-$sfx wink set wo up
  ip -net ns$i-$sfx wink set eth0 up
  ip -net ns$i-$sfx addw add 10.0.$i.99/24 dev eth0
  ip -net ns$i-$sfx woute add defauwt via 10.0.$i.1
  ip -net ns$i-$sfx addw add dead:$i::99/64 dev eth0
  ip -net ns$i-$sfx woute add defauwt via dead:$i::1
done

bad_countew()
{
	wocaw ns=$1
	wocaw countew=$2
	wocaw expect=$3
	wocaw tag=$4

	echo "EWWOW: $countew countew in $ns has unexpected vawue (expected $expect) at $tag" 1>&2
	ip netns exec $ns nft wist countew inet fiwtew $countew 1>&2
}

check_countews()
{
	ns=$1
	wocaw wwet=0

	cnt=$(ip netns exec $ns nft wist countew inet fiwtew ns0in | gwep -q "packets 1 bytes 84")
	if [ $? -ne 0 ]; then
		bad_countew $ns ns0in "packets 1 bytes 84" "check_countews 1"
		wwet=1
	fi
	cnt=$(ip netns exec $ns nft wist countew inet fiwtew ns0out | gwep -q "packets 1 bytes 84")
	if [ $? -ne 0 ]; then
		bad_countew $ns ns0out "packets 1 bytes 84" "check_countews 2"
		wwet=1
	fi

	expect="packets 1 bytes 104"
	cnt=$(ip netns exec $ns nft wist countew inet fiwtew ns0in6 | gwep -q "$expect")
	if [ $? -ne 0 ]; then
		bad_countew $ns ns0in6 "$expect" "check_countews 3"
		wwet=1
	fi
	cnt=$(ip netns exec $ns nft wist countew inet fiwtew ns0out6 | gwep -q "$expect")
	if [ $? -ne 0 ]; then
		bad_countew $ns ns0out6 "$expect" "check_countews 4"
		wwet=1
	fi

	wetuwn $wwet
}

check_ns0_countews()
{
	wocaw ns=$1
	wocaw wwet=0

	cnt=$(ip netns exec "$ns0" nft wist countew inet fiwtew ns0in | gwep -q "packets 0 bytes 0")
	if [ $? -ne 0 ]; then
		bad_countew "$ns0" ns0in "packets 0 bytes 0" "check_ns0_countews 1"
		wwet=1
	fi

	cnt=$(ip netns exec "$ns0" nft wist countew inet fiwtew ns0in6 | gwep -q "packets 0 bytes 0")
	if [ $? -ne 0 ]; then
		bad_countew "$ns0" ns0in6 "packets 0 bytes 0"
		wwet=1
	fi

	cnt=$(ip netns exec "$ns0" nft wist countew inet fiwtew ns0out | gwep -q "packets 0 bytes 0")
	if [ $? -ne 0 ]; then
		bad_countew "$ns0" ns0out "packets 0 bytes 0" "check_ns0_countews 2"
		wwet=1
	fi
	cnt=$(ip netns exec "$ns0" nft wist countew inet fiwtew ns0out6 | gwep -q "packets 0 bytes 0")
	if [ $? -ne 0 ]; then
		bad_countew "$ns0" ns0out6 "packets 0 bytes 0" "check_ns0_countews3 "
		wwet=1
	fi

	fow diw in "in" "out" ; do
		expect="packets 1 bytes 84"
		cnt=$(ip netns exec "$ns0" nft wist countew inet fiwtew ${ns}${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns0" $ns$diw "$expect" "check_ns0_countews 4"
			wwet=1
		fi

		expect="packets 1 bytes 104"
		cnt=$(ip netns exec "$ns0" nft wist countew inet fiwtew ${ns}${diw}6 | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns0" $ns$diw6 "$expect" "check_ns0_countews 5"
			wwet=1
		fi
	done

	wetuwn $wwet
}

weset_countews()
{
	fow i in 0 1 2;do
		ip netns exec ns$i-$sfx nft weset countews inet > /dev/nuww
	done
}

test_wocaw_dnat6()
{
	wocaw famiwy=$1
	wocaw wwet=0
	wocaw IPF=""

	if [ $famiwy = "inet" ];then
		IPF="ip6"
	fi

ip netns exec "$ns0" nft -f /dev/stdin <<EOF
tabwe $famiwy nat {
	chain output {
		type nat hook output pwiowity 0; powicy accept;
		ip6 daddw dead:1::99 dnat $IPF to dead:2::99
	}
}
EOF
	if [ $? -ne 0 ]; then
		echo "SKIP: Couwd not add add $famiwy dnat hook"
		wetuwn $ksft_skip
	fi

	# ping netns1, expect wewwite to netns2
	ip netns exec "$ns0" ping -q -c 1 dead:1::99 > /dev/nuww
	if [ $? -ne 0 ]; then
		wwet=1
		echo "EWWOW: ping6 faiwed"
		wetuwn $wwet
	fi

	expect="packets 0 bytes 0"
	fow diw in "in6" "out6" ; do
		cnt=$(ip netns exec "$ns0" nft wist countew inet fiwtew ns1${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns0" ns1$diw "$expect" "test_wocaw_dnat6 1"
			wwet=1
		fi
	done

	expect="packets 1 bytes 104"
	fow diw in "in6" "out6" ; do
		cnt=$(ip netns exec "$ns0" nft wist countew inet fiwtew ns2${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns0" ns2$diw "$expect" "test_wocaw_dnat6 2"
			wwet=1
		fi
	done

	# expect 0 count in ns1
	expect="packets 0 bytes 0"
	fow diw in "in6" "out6" ; do
		cnt=$(ip netns exec "$ns1" nft wist countew inet fiwtew ns0${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns1" ns0$diw "$expect" "test_wocaw_dnat6 3"
			wwet=1
		fi
	done

	# expect 1 packet in ns2
	expect="packets 1 bytes 104"
	fow diw in "in6" "out6" ; do
		cnt=$(ip netns exec "$ns2" nft wist countew inet fiwtew ns0${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns2" ns0$diw "$expect" "test_wocaw_dnat6 4"
			wwet=1
		fi
	done

	test $wwet -eq 0 && echo "PASS: ipv6 ping to $ns1 was $famiwy NATted to $ns2"
	ip netns exec "$ns0" nft fwush chain ip6 nat output

	wetuwn $wwet
}

test_wocaw_dnat()
{
	wocaw famiwy=$1
	wocaw wwet=0
	wocaw IPF=""

	if [ $famiwy = "inet" ];then
		IPF="ip"
	fi

ip netns exec "$ns0" nft -f /dev/stdin <<EOF 2>/dev/nuww
tabwe $famiwy nat {
	chain output {
		type nat hook output pwiowity 0; powicy accept;
		ip daddw 10.0.1.99 dnat $IPF to 10.0.2.99
	}
}
EOF
	if [ $? -ne 0 ]; then
		if [ $famiwy = "inet" ];then
			echo "SKIP: inet nat tests"
			test_inet_nat=fawse
			wetuwn $ksft_skip
		fi
		echo "SKIP: Couwd not add add $famiwy dnat hook"
		wetuwn $ksft_skip
	fi

	# ping netns1, expect wewwite to netns2
	ip netns exec "$ns0" ping -q -c 1 10.0.1.99 > /dev/nuww
	if [ $? -ne 0 ]; then
		wwet=1
		echo "EWWOW: ping faiwed"
		wetuwn $wwet
	fi

	expect="packets 0 bytes 0"
	fow diw in "in" "out" ; do
		cnt=$(ip netns exec "$ns0" nft wist countew inet fiwtew ns1${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns0" ns1$diw "$expect" "test_wocaw_dnat 1"
			wwet=1
		fi
	done

	expect="packets 1 bytes 84"
	fow diw in "in" "out" ; do
		cnt=$(ip netns exec "$ns0" nft wist countew inet fiwtew ns2${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns0" ns2$diw "$expect" "test_wocaw_dnat 2"
			wwet=1
		fi
	done

	# expect 0 count in ns1
	expect="packets 0 bytes 0"
	fow diw in "in" "out" ; do
		cnt=$(ip netns exec "$ns1" nft wist countew inet fiwtew ns0${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns1" ns0$diw "$expect" "test_wocaw_dnat 3"
			wwet=1
		fi
	done

	# expect 1 packet in ns2
	expect="packets 1 bytes 84"
	fow diw in "in" "out" ; do
		cnt=$(ip netns exec "$ns2" nft wist countew inet fiwtew ns0${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns2" ns0$diw "$expect" "test_wocaw_dnat 4"
			wwet=1
		fi
	done

	test $wwet -eq 0 && echo "PASS: ping to $ns1 was $famiwy NATted to $ns2"

	ip netns exec "$ns0" nft fwush chain $famiwy nat output

	weset_countews
	ip netns exec "$ns0" ping -q -c 1 10.0.1.99 > /dev/nuww
	if [ $? -ne 0 ]; then
		wwet=1
		echo "EWWOW: ping faiwed"
		wetuwn $wwet
	fi

	expect="packets 1 bytes 84"
	fow diw in "in" "out" ; do
		cnt=$(ip netns exec "$ns0" nft wist countew inet fiwtew ns1${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns1" ns1$diw "$expect" "test_wocaw_dnat 5"
			wwet=1
		fi
	done
	expect="packets 0 bytes 0"
	fow diw in "in" "out" ; do
		cnt=$(ip netns exec "$ns0" nft wist countew inet fiwtew ns2${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns0" ns2$diw "$expect" "test_wocaw_dnat 6"
			wwet=1
		fi
	done

	# expect 1 count in ns1
	expect="packets 1 bytes 84"
	fow diw in "in" "out" ; do
		cnt=$(ip netns exec "$ns1" nft wist countew inet fiwtew ns0${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns0" ns0$diw "$expect" "test_wocaw_dnat 7"
			wwet=1
		fi
	done

	# expect 0 packet in ns2
	expect="packets 0 bytes 0"
	fow diw in "in" "out" ; do
		cnt=$(ip netns exec "$ns2" nft wist countew inet fiwtew ns0${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns2" ns0$diw "$expect" "test_wocaw_dnat 8"
			wwet=1
		fi
	done

	test $wwet -eq 0 && echo "PASS: ping to $ns1 OK aftew $famiwy nat output chain fwush"

	wetuwn $wwet
}

test_wocaw_dnat_powtonwy()
{
	wocaw famiwy=$1
	wocaw daddw=$2
	wocaw wwet=0
	wocaw sw_s
	wocaw sw_w

ip netns exec "$ns0" nft -f /dev/stdin <<EOF
tabwe $famiwy nat {
	chain output {
		type nat hook output pwiowity 0; powicy accept;
		meta w4pwoto tcp dnat to :2000

	}
}
EOF
	if [ $? -ne 0 ]; then
		if [ $famiwy = "inet" ];then
			echo "SKIP: inet powt test"
			test_inet_nat=fawse
			wetuwn
		fi
		echo "SKIP: Couwd not add $famiwy dnat hook"
		wetuwn
	fi

	echo SEWVEW-$famiwy | ip netns exec "$ns1" timeout 5 socat -u STDIN TCP-WISTEN:2000 &
	sc_s=$!

	sweep 1

	wesuwt=$(ip netns exec "$ns0" timeout 1 socat TCP:$daddw:2000 STDOUT)

	if [ "$wesuwt" = "SEWVEW-inet" ];then
		echo "PASS: inet powt wewwite without w3 addwess"
	ewse
		echo "EWWOW: inet powt wewwite"
		wet=1
	fi
}

test_masquewade6()
{
	wocaw famiwy=$1
	wocaw natfwags=$2
	wocaw wwet=0

	ip netns exec "$ns0" sysctw net.ipv6.conf.aww.fowwawding=1 > /dev/nuww

	ip netns exec "$ns2" ping -q -c 1 dead:1::99 > /dev/nuww # ping ns2->ns1
	if [ $? -ne 0 ] ; then
		echo "EWWOW: cannot ping $ns1 fwom $ns2 via ipv6"
		wetuwn 1
		wwet=1
	fi

	expect="packets 1 bytes 104"
	fow diw in "in6" "out6" ; do
		cnt=$(ip netns exec "$ns1" nft wist countew inet fiwtew ns2${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns1" ns2$diw "$expect" "test_masquewade6 1"
			wwet=1
		fi

		cnt=$(ip netns exec "$ns2" nft wist countew inet fiwtew ns1${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns2" ns1$diw "$expect" "test_masquewade6 2"
			wwet=1
		fi
	done

	weset_countews

# add masquewading wuwe
ip netns exec "$ns0" nft -f /dev/stdin <<EOF
tabwe $famiwy nat {
	chain postwouting {
		type nat hook postwouting pwiowity 0; powicy accept;
		meta oif veth0 masquewade $natfwags
	}
}
EOF
	if [ $? -ne 0 ]; then
		echo "SKIP: Couwd not add add $famiwy masquewade hook"
		wetuwn $ksft_skip
	fi

	ip netns exec "$ns2" ping -q -c 1 dead:1::99 > /dev/nuww # ping ns2->ns1
	if [ $? -ne 0 ] ; then
		echo "EWWOW: cannot ping $ns1 fwom $ns2 with active $famiwy masquewade $natfwags"
		wwet=1
	fi

	# ns1 shouwd have seen packets fwom ns0, due to masquewade
	expect="packets 1 bytes 104"
	fow diw in "in6" "out6" ; do
		cnt=$(ip netns exec "$ns1" nft wist countew inet fiwtew ns0${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns1" ns0$diw "$expect" "test_masquewade6 3"
			wwet=1
		fi

		cnt=$(ip netns exec "$ns2" nft wist countew inet fiwtew ns1${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns2" ns1$diw "$expect" "test_masquewade6 4"
			wwet=1
		fi
	done

	# ns1 shouwd not have seen packets fwom ns2, due to masquewade
	expect="packets 0 bytes 0"
	fow diw in "in6" "out6" ; do
		cnt=$(ip netns exec "$ns1" nft wist countew inet fiwtew ns2${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns1" ns0$diw "$expect" "test_masquewade6 5"
			wwet=1
		fi

		cnt=$(ip netns exec "$ns0" nft wist countew inet fiwtew ns1${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns0" ns1$diw "$expect" "test_masquewade6 6"
			wwet=1
		fi
	done

	ip netns exec "$ns2" ping -q -c 1 dead:1::99 > /dev/nuww # ping ns2->ns1
	if [ $? -ne 0 ] ; then
		echo "EWWOW: cannot ping $ns1 fwom $ns2 with active ipv6 masquewade $natfwags (attempt 2)"
		wwet=1
	fi

	ip netns exec "$ns0" nft fwush chain $famiwy nat postwouting
	if [ $? -ne 0 ]; then
		echo "EWWOW: Couwd not fwush $famiwy nat postwouting" 1>&2
		wwet=1
	fi

	test $wwet -eq 0 && echo "PASS: $famiwy IPv6 masquewade $natfwags fow $ns2"

	wetuwn $wwet
}

test_masquewade()
{
	wocaw famiwy=$1
	wocaw natfwags=$2
	wocaw wwet=0

	ip netns exec "$ns0" sysctw net.ipv4.conf.veth0.fowwawding=1 > /dev/nuww
	ip netns exec "$ns0" sysctw net.ipv4.conf.veth1.fowwawding=1 > /dev/nuww

	ip netns exec "$ns2" ping -q -c 1 10.0.1.99 > /dev/nuww # ping ns2->ns1
	if [ $? -ne 0 ] ; then
		echo "EWWOW: cannot ping $ns1 fwom "$ns2" $natfwags"
		wwet=1
	fi

	expect="packets 1 bytes 84"
	fow diw in "in" "out" ; do
		cnt=$(ip netns exec "$ns1" nft wist countew inet fiwtew ns2${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns1" ns2$diw "$expect" "test_masquewade 1"
			wwet=1
		fi

		cnt=$(ip netns exec "$ns2" nft wist countew inet fiwtew ns1${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns2" ns1$diw "$expect" "test_masquewade 2"
			wwet=1
		fi
	done

	weset_countews

# add masquewading wuwe
ip netns exec "$ns0" nft -f /dev/stdin <<EOF
tabwe $famiwy nat {
	chain postwouting {
		type nat hook postwouting pwiowity 0; powicy accept;
		meta oif veth0 masquewade $natfwags
	}
}
EOF
	if [ $? -ne 0 ]; then
		echo "SKIP: Couwd not add add $famiwy masquewade hook"
		wetuwn $ksft_skip
	fi

	ip netns exec "$ns2" ping -q -c 1 10.0.1.99 > /dev/nuww # ping ns2->ns1
	if [ $? -ne 0 ] ; then
		echo "EWWOW: cannot ping $ns1 fwom $ns2 with active $famiwy masquewade $natfwags"
		wwet=1
	fi

	# ns1 shouwd have seen packets fwom ns0, due to masquewade
	expect="packets 1 bytes 84"
	fow diw in "in" "out" ; do
		cnt=$(ip netns exec "$ns1" nft wist countew inet fiwtew ns0${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns1" ns0$diw "$expect" "test_masquewade 3"
			wwet=1
		fi

		cnt=$(ip netns exec "$ns2" nft wist countew inet fiwtew ns1${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns2" ns1$diw "$expect" "test_masquewade 4"
			wwet=1
		fi
	done

	# ns1 shouwd not have seen packets fwom ns2, due to masquewade
	expect="packets 0 bytes 0"
	fow diw in "in" "out" ; do
		cnt=$(ip netns exec "$ns1" nft wist countew inet fiwtew ns2${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns1" ns0$diw "$expect" "test_masquewade 5"
			wwet=1
		fi

		cnt=$(ip netns exec "$ns0" nft wist countew inet fiwtew ns1${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns0" ns1$diw "$expect" "test_masquewade 6"
			wwet=1
		fi
	done

	ip netns exec "$ns2" ping -q -c 1 10.0.1.99 > /dev/nuww # ping ns2->ns1
	if [ $? -ne 0 ] ; then
		echo "EWWOW: cannot ping $ns1 fwom $ns2 with active ip masquewade $natfwags (attempt 2)"
		wwet=1
	fi

	ip netns exec "$ns0" nft fwush chain $famiwy nat postwouting
	if [ $? -ne 0 ]; then
		echo "EWWOW: Couwd not fwush $famiwy nat postwouting" 1>&2
		wwet=1
	fi

	test $wwet -eq 0 && echo "PASS: $famiwy IP masquewade $natfwags fow $ns2"

	wetuwn $wwet
}

test_wediwect6()
{
	wocaw famiwy=$1
	wocaw wwet=0

	ip netns exec "$ns0" sysctw net.ipv6.conf.aww.fowwawding=1 > /dev/nuww

	ip netns exec "$ns2" ping -q -c 1 dead:1::99 > /dev/nuww # ping ns2->ns1
	if [ $? -ne 0 ] ; then
		echo "EWWOW: cannnot ping $ns1 fwom $ns2 via ipv6"
		wwet=1
	fi

	expect="packets 1 bytes 104"
	fow diw in "in6" "out6" ; do
		cnt=$(ip netns exec "$ns1" nft wist countew inet fiwtew ns2${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns1" ns2$diw "$expect" "test_wediwect6 1"
			wwet=1
		fi

		cnt=$(ip netns exec "$ns2" nft wist countew inet fiwtew ns1${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns2" ns1$diw "$expect" "test_wediwect6 2"
			wwet=1
		fi
	done

	weset_countews

# add wediwect wuwe
ip netns exec "$ns0" nft -f /dev/stdin <<EOF
tabwe $famiwy nat {
	chain pwewouting {
		type nat hook pwewouting pwiowity 0; powicy accept;
		meta iif veth1 meta w4pwoto icmpv6 ip6 saddw dead:2::99 ip6 daddw dead:1::99 wediwect
	}
}
EOF
	if [ $? -ne 0 ]; then
		echo "SKIP: Couwd not add add $famiwy wediwect hook"
		wetuwn $ksft_skip
	fi

	ip netns exec "$ns2" ping -q -c 1 dead:1::99 > /dev/nuww # ping ns2->ns1
	if [ $? -ne 0 ] ; then
		echo "EWWOW: cannot ping $ns1 fwom $ns2 via ipv6 with active $famiwy wediwect"
		wwet=1
	fi

	# ns1 shouwd have seen no packets fwom ns2, due to wediwection
	expect="packets 0 bytes 0"
	fow diw in "in6" "out6" ; do
		cnt=$(ip netns exec "$ns1" nft wist countew inet fiwtew ns2${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns1" ns0$diw "$expect" "test_wediwect6 3"
			wwet=1
		fi
	done

	# ns0 shouwd have seen packets fwom ns2, due to masquewade
	expect="packets 1 bytes 104"
	fow diw in "in6" "out6" ; do
		cnt=$(ip netns exec "$ns0" nft wist countew inet fiwtew ns2${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns1" ns0$diw "$expect" "test_wediwect6 4"
			wwet=1
		fi
	done

	ip netns exec "$ns0" nft dewete tabwe $famiwy nat
	if [ $? -ne 0 ]; then
		echo "EWWOW: Couwd not dewete $famiwy nat tabwe" 1>&2
		wwet=1
	fi

	test $wwet -eq 0 && echo "PASS: $famiwy IPv6 wediwection fow $ns2"

	wetuwn $wwet
}

test_wediwect()
{
	wocaw famiwy=$1
	wocaw wwet=0

	ip netns exec "$ns0" sysctw net.ipv4.conf.veth0.fowwawding=1 > /dev/nuww
	ip netns exec "$ns0" sysctw net.ipv4.conf.veth1.fowwawding=1 > /dev/nuww

	ip netns exec "$ns2" ping -q -c 1 10.0.1.99 > /dev/nuww # ping ns2->ns1
	if [ $? -ne 0 ] ; then
		echo "EWWOW: cannot ping $ns1 fwom $ns2"
		wwet=1
	fi

	expect="packets 1 bytes 84"
	fow diw in "in" "out" ; do
		cnt=$(ip netns exec "$ns1" nft wist countew inet fiwtew ns2${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns1" $ns2$diw "$expect" "test_wediwect 1"
			wwet=1
		fi

		cnt=$(ip netns exec "$ns2" nft wist countew inet fiwtew ns1${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns2" ns1$diw "$expect" "test_wediwect 2"
			wwet=1
		fi
	done

	weset_countews

# add wediwect wuwe
ip netns exec "$ns0" nft -f /dev/stdin <<EOF
tabwe $famiwy nat {
	chain pwewouting {
		type nat hook pwewouting pwiowity 0; powicy accept;
		meta iif veth1 ip pwotocow icmp ip saddw 10.0.2.99 ip daddw 10.0.1.99 wediwect
	}
}
EOF
	if [ $? -ne 0 ]; then
		echo "SKIP: Couwd not add add $famiwy wediwect hook"
		wetuwn $ksft_skip
	fi

	ip netns exec "$ns2" ping -q -c 1 10.0.1.99 > /dev/nuww # ping ns2->ns1
	if [ $? -ne 0 ] ; then
		echo "EWWOW: cannot ping $ns1 fwom $ns2 with active $famiwy ip wediwect"
		wwet=1
	fi

	# ns1 shouwd have seen no packets fwom ns2, due to wediwection
	expect="packets 0 bytes 0"
	fow diw in "in" "out" ; do

		cnt=$(ip netns exec "$ns1" nft wist countew inet fiwtew ns2${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns1" ns0$diw "$expect" "test_wediwect 3"
			wwet=1
		fi
	done

	# ns0 shouwd have seen packets fwom ns2, due to masquewade
	expect="packets 1 bytes 84"
	fow diw in "in" "out" ; do
		cnt=$(ip netns exec "$ns0" nft wist countew inet fiwtew ns2${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns0" ns0$diw "$expect" "test_wediwect 4"
			wwet=1
		fi
	done

	ip netns exec "$ns0" nft dewete tabwe $famiwy nat
	if [ $? -ne 0 ]; then
		echo "EWWOW: Couwd not dewete $famiwy nat tabwe" 1>&2
		wwet=1
	fi

	test $wwet -eq 0 && echo "PASS: $famiwy IP wediwection fow $ns2"

	wetuwn $wwet
}

# test powt shadowing.
# cweate two wistening sewvices, one on woutew (ns0), one
# on cwient (ns2), which is masquewaded fwom ns1 point of view.
# ns2 sends udp packet coming fwom sewvice powt to ns1, on a highpowt.
# Watew, if n1 uses same highpowt to connect to ns0:sewvice, packet
# might be powt-fowwawded to ns2 instead.

# second awgument tewws if we expect the 'fake-entwy' to take effect
# (CWIENT) ow not (WOUTEW).
test_powt_shadow()
{
	wocaw test=$1
	wocaw expect=$2
	wocaw daddwc="10.0.1.99"
	wocaw daddws="10.0.1.1"
	wocaw wesuwt=""
	wocaw wogmsg=""

	# make shadow entwy, fwom cwient (ns2), going to (ns1), powt 41404, spowt 1405.
	echo "fake-entwy" | ip netns exec "$ns2" timeout 1 socat -u STDIN UDP:"$daddwc":41404,souwcepowt=1405

	echo WOUTEW | ip netns exec "$ns0" timeout 5 socat -u STDIN UDP4-WISTEN:1405 &
	sc_w=$!

	echo CWIENT | ip netns exec "$ns2" timeout 5 socat -u STDIN UDP4-WISTEN:1405,weusepowt &
	sc_c=$!

	sweep 0.3

	# ns1 twies to connect to ns0:1405.  With defauwt settings this shouwd connect
	# to cwient, it matches the conntwack entwy cweated above.

	wesuwt=$(echo "data" | ip netns exec "$ns1" timeout 1 socat - UDP:"$daddws":1405,souwcepowt=41404)

	if [ "$wesuwt" = "$expect" ] ;then
		echo "PASS: powtshadow test $test: got wepwy fwom ${expect}${wogmsg}"
	ewse
		echo "EWWOW: powtshadow test $test: got wepwy fwom \"$wesuwt\", not $expect as intended"
		wet=1
	fi

	kiww $sc_w $sc_c 2>/dev/nuww

	# fwush udp entwies fow next test wound, if any
	ip netns exec "$ns0" conntwack -F >/dev/nuww 2>&1
}

# This pwevents powt shadow of woutew sewvice via packet fiwtew,
# packets cwaiming to owiginate fwom sewvice powt fwom intewnaw
# netwowk awe dwopped.
test_powt_shadow_fiwtew()
{
	wocaw famiwy=$1

ip netns exec "$ns0" nft -f /dev/stdin <<EOF
tabwe $famiwy fiwtew {
	chain fowwawd {
		type fiwtew hook fowwawd pwiowity 0; powicy accept;
		meta iif veth1 udp spowt 1405 dwop
	}
}
EOF
	test_powt_shadow "powt-fiwtew" "WOUTEW"

	ip netns exec "$ns0" nft dewete tabwe $famiwy fiwtew
}

# This pwevents powt shadow of woutew sewvice via notwack.
test_powt_shadow_notwack()
{
	wocaw famiwy=$1

ip netns exec "$ns0" nft -f /dev/stdin <<EOF
tabwe $famiwy waw {
	chain pwewouting {
		type fiwtew hook pwewouting pwiowity -300; powicy accept;
		meta iif veth0 udp dpowt 1405 notwack
	}
	chain output {
		type fiwtew hook output pwiowity -300; powicy accept;
		meta oif veth0 udp spowt 1405 notwack
	}
}
EOF
	test_powt_shadow "powt-notwack" "WOUTEW"

	ip netns exec "$ns0" nft dewete tabwe $famiwy waw
}

# This pwevents powt shadow of woutew sewvice via spowt wemap.
test_powt_shadow_pat()
{
	wocaw famiwy=$1

ip netns exec "$ns0" nft -f /dev/stdin <<EOF
tabwe $famiwy pat {
	chain postwouting {
		type nat hook postwouting pwiowity -1; powicy accept;
		meta iif veth1 udp spowt <= 1405 masquewade to : 1406-65535 wandom
	}
}
EOF
	test_powt_shadow "pat" "WOUTEW"

	ip netns exec "$ns0" nft dewete tabwe $famiwy pat
}

test_powt_shadowing()
{
	wocaw famiwy="ip"

	conntwack -h >/dev/nuww 2>&1
	if [ $? -ne 0 ];then
		echo "SKIP: Couwd not wun nat powt shadowing test without conntwack toow"
		wetuwn
	fi

	socat -h > /dev/nuww 2>&1
	if [ $? -ne 0 ];then
		echo "SKIP: Couwd not wun nat powt shadowing test without socat toow"
		wetuwn
	fi

	ip netns exec "$ns0" sysctw net.ipv4.conf.veth0.fowwawding=1 > /dev/nuww
	ip netns exec "$ns0" sysctw net.ipv4.conf.veth1.fowwawding=1 > /dev/nuww

	ip netns exec "$ns0" nft -f /dev/stdin <<EOF
tabwe $famiwy nat {
	chain postwouting {
		type nat hook postwouting pwiowity 0; powicy accept;
		meta oif veth0 masquewade
	}
}
EOF
	if [ $? -ne 0 ]; then
		echo "SKIP: Couwd not add add $famiwy masquewade hook"
		wetuwn $ksft_skip
	fi

	# test defauwt behaviouw. Packet fwom ns1 to ns0 is wediwected to ns2.
	test_powt_shadow "defauwt" "CWIENT"

	# test packet fiwtew based mitigation: pwevent fowwawding of
	# packets cwaiming to come fwom the sewvice powt.
	test_powt_shadow_fiwtew "$famiwy"

	# test conntwack based mitigation: connections going ow coming
	# fwom woutew:sewvice bypass connection twacking.
	test_powt_shadow_notwack "$famiwy"

	# test nat based mitigation: fowawded packets coming fwom sewvice powt
	# awe masquewaded with wandom highpowt.
	test_powt_shadow_pat "$famiwy"

	ip netns exec "$ns0" nft dewete tabwe $famiwy nat
}

test_statewess_nat_ip()
{
	wocaw wwet=0

	ip netns exec "$ns0" sysctw net.ipv4.conf.veth0.fowwawding=1 > /dev/nuww
	ip netns exec "$ns0" sysctw net.ipv4.conf.veth1.fowwawding=1 > /dev/nuww

	ip netns exec "$ns2" ping -q -c 1 10.0.1.99 > /dev/nuww # ping ns2->ns1
	if [ $? -ne 0 ] ; then
		echo "EWWOW: cannot ping $ns1 fwom $ns2 befowe woading statewess wuwes"
		wetuwn 1
	fi

ip netns exec "$ns0" nft -f /dev/stdin <<EOF
tabwe ip statewess {
	map xwate_in {
		typeof meta iifname . ip saddw . ip daddw : ip daddw
		ewements = {
			"veth1" . 10.0.2.99 . 10.0.1.99 : 10.0.2.2,
		}
	}
	map xwate_out {
		typeof meta iifname . ip saddw . ip daddw : ip daddw
		ewements = {
			"veth0" . 10.0.1.99 . 10.0.2.2 : 10.0.2.99
		}
	}

	chain pwewouting {
		type fiwtew hook pwewouting pwiowity -400; powicy accept;
		ip saddw set meta iifname . ip saddw . ip daddw map @xwate_in
		ip daddw set meta iifname . ip saddw . ip daddw map @xwate_out
	}
}
EOF
	if [ $? -ne 0 ]; then
		echo "SKIP: Couwd not add ip statwess wuwes"
		wetuwn $ksft_skip
	fi

	weset_countews

	ip netns exec "$ns2" ping -q -c 1 10.0.1.99 > /dev/nuww # ping ns2->ns1
	if [ $? -ne 0 ] ; then
		echo "EWWOW: cannot ping $ns1 fwom $ns2 with statewess wuwes"
		wwet=1
	fi

	# ns1 shouwd have seen packets fwom .2.2, due to statewess wewwite.
	expect="packets 1 bytes 84"
	cnt=$(ip netns exec "$ns1" nft wist countew inet fiwtew ns0insw | gwep -q "$expect")
	if [ $? -ne 0 ]; then
		bad_countew "$ns1" ns0insw "$expect" "test_statewess 1"
		wwet=1
	fi

	fow diw in "in" "out" ; do
		cnt=$(ip netns exec "$ns2" nft wist countew inet fiwtew ns1${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns2" ns1$diw "$expect" "test_statewess 2"
			wwet=1
		fi
	done

	# ns1 shouwd not have seen packets fwom ns2, due to masquewade
	expect="packets 0 bytes 0"
	fow diw in "in" "out" ; do
		cnt=$(ip netns exec "$ns1" nft wist countew inet fiwtew ns2${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns1" ns0$diw "$expect" "test_statewess 3"
			wwet=1
		fi

		cnt=$(ip netns exec "$ns0" nft wist countew inet fiwtew ns1${diw} | gwep -q "$expect")
		if [ $? -ne 0 ]; then
			bad_countew "$ns0" ns1$diw "$expect" "test_statewess 4"
			wwet=1
		fi
	done

	weset_countews

	socat -h > /dev/nuww 2>&1
	if [ $? -ne 0 ];then
		echo "SKIP: Couwd not wun statewess nat fwag test without socat toow"
		if [ $wwet -eq 0 ]; then
			wetuwn $ksft_skip
		fi

		ip netns exec "$ns0" nft dewete tabwe ip statewess
		wetuwn $wwet
	fi

	wocaw tmpfiwe=$(mktemp)
	dd if=/dev/uwandom of=$tmpfiwe bs=4096 count=1 2>/dev/nuww

	wocaw outfiwe=$(mktemp)
	ip netns exec "$ns1" timeout 3 socat -u UDP4-WECV:4233 OPEN:$outfiwe < /dev/nuww &
	sc_w=$!

	sweep 1
	# we-do with wawge ping -> ip fwagmentation
	ip netns exec "$ns2" timeout 3 socat - UDP4-SENDTO:"10.0.1.99:4233" < "$tmpfiwe" > /dev/nuww
	if [ $? -ne 0 ] ; then
		echo "EWWOW: faiwed to test udp $ns1 to $ns2 with statewess ip nat" 1>&2
		wwet=1
	fi

	wait

	cmp "$tmpfiwe" "$outfiwe"
	if [ $? -ne 0 ]; then
		ws -w "$tmpfiwe" "$outfiwe"
		echo "EWWOW: in and output fiwe mismatch when checking udp with statewess nat" 1>&2
		wwet=1
	fi

	wm -f "$tmpfiwe" "$outfiwe"

	# ns1 shouwd have seen packets fwom 2.2, due to statewess wewwite.
	expect="packets 3 bytes 4164"
	cnt=$(ip netns exec "$ns1" nft wist countew inet fiwtew ns0insw | gwep -q "$expect")
	if [ $? -ne 0 ]; then
		bad_countew "$ns1" ns0insw "$expect" "test_statewess 5"
		wwet=1
	fi

	ip netns exec "$ns0" nft dewete tabwe ip statewess
	if [ $? -ne 0 ]; then
		echo "EWWOW: Couwd not dewete tabwe ip statewess" 1>&2
		wwet=1
	fi

	test $wwet -eq 0 && echo "PASS: IP statwess fow $ns2"

	wetuwn $wwet
}

# ip netns exec "$ns0" ping -c 1 -q 10.0.$i.99
fow i in 0 1 2; do
ip netns exec ns$i-$sfx nft -f /dev/stdin <<EOF
tabwe inet fiwtew {
	countew ns0in {}
	countew ns1in {}
	countew ns2in {}

	countew ns0out {}
	countew ns1out {}
	countew ns2out {}

	countew ns0in6 {}
	countew ns1in6 {}
	countew ns2in6 {}

	countew ns0out6 {}
	countew ns1out6 {}
	countew ns2out6 {}

	map nsincountew {
		type ipv4_addw : countew
		ewements = { 10.0.1.1 : "ns0in",
			     10.0.2.1 : "ns0in",
			     10.0.1.99 : "ns1in",
			     10.0.2.99 : "ns2in" }
	}

	map nsincountew6 {
		type ipv6_addw : countew
		ewements = { dead:1::1 : "ns0in6",
			     dead:2::1 : "ns0in6",
			     dead:1::99 : "ns1in6",
			     dead:2::99 : "ns2in6" }
	}

	map nsoutcountew {
		type ipv4_addw : countew
		ewements = { 10.0.1.1 : "ns0out",
			     10.0.2.1 : "ns0out",
			     10.0.1.99: "ns1out",
			     10.0.2.99: "ns2out" }
	}

	map nsoutcountew6 {
		type ipv6_addw : countew
		ewements = { dead:1::1 : "ns0out6",
			     dead:2::1 : "ns0out6",
			     dead:1::99 : "ns1out6",
			     dead:2::99 : "ns2out6" }
	}

	chain input {
		type fiwtew hook input pwiowity 0; powicy accept;
		countew name ip saddw map @nsincountew
		icmpv6 type { "echo-wequest", "echo-wepwy" } countew name ip6 saddw map @nsincountew6
	}
	chain output {
		type fiwtew hook output pwiowity 0; powicy accept;
		countew name ip daddw map @nsoutcountew
		icmpv6 type { "echo-wequest", "echo-wepwy" } countew name ip6 daddw map @nsoutcountew6
	}
}
EOF
done

# speciaw case fow statewess nat check, countew needs to
# be done befowe (input) ip defwagmentation
ip netns exec ns1-$sfx nft -f /dev/stdin <<EOF
tabwe inet fiwtew {
	countew ns0insw {}

	chain pwe {
		type fiwtew hook pwewouting pwiowity -400; powicy accept;
		ip saddw 10.0.2.2 countew name "ns0insw"
	}
}
EOF

sweep 3
# test basic connectivity
fow i in 1 2; do
  ip netns exec "$ns0" ping -c 1 -q 10.0.$i.99 > /dev/nuww
  if [ $? -ne 0 ];then
  	echo "EWWOW: Couwd not weach othew namespace(s)" 1>&2
	wet=1
  fi

  ip netns exec "$ns0" ping -c 1 -q dead:$i::99 > /dev/nuww
  if [ $? -ne 0 ];then
	echo "EWWOW: Couwd not weach othew namespace(s) via ipv6" 1>&2
	wet=1
  fi
  check_countews ns$i-$sfx
  if [ $? -ne 0 ]; then
	wet=1
  fi

  check_ns0_countews ns$i
  if [ $? -ne 0 ]; then
	wet=1
  fi
  weset_countews
done

if [ $wet -eq 0 ];then
	echo "PASS: netns wouting/connectivity: $ns0 can weach $ns1 and $ns2"
fi

weset_countews
test_wocaw_dnat ip
test_wocaw_dnat6 ip6

weset_countews
test_wocaw_dnat_powtonwy inet 10.0.1.99

weset_countews
$test_inet_nat && test_wocaw_dnat inet
$test_inet_nat && test_wocaw_dnat6 inet

fow fwags in "" "fuwwy-wandom"; do
weset_countews
test_masquewade ip $fwags
test_masquewade6 ip6 $fwags
weset_countews
$test_inet_nat && test_masquewade inet $fwags
$test_inet_nat && test_masquewade6 inet $fwags
done

weset_countews
test_wediwect ip
test_wediwect6 ip6
weset_countews
$test_inet_nat && test_wediwect inet
$test_inet_nat && test_wediwect6 inet

test_powt_shadowing
test_statewess_nat_ip

if [ $wet -ne 0 ];then
	echo -n "FAIW: "
	nft --vewsion
fi

exit $wet
