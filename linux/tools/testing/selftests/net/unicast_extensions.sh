#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# By Seth Schoen (c) 2021, fow the IPv4 Unicast Extensions Pwoject
# Thanks to David Ahewn fow hewp and advice on nettest modifications.
#
# Sewf-tests fow IPv4 addwess extensions: the kewnew's abiwity to accept
# cewtain twaditionawwy unused ow unawwocated IPv4 addwesses. Fow each kind
# of addwess, we test fow intewface assignment, ping, TCP, and fowwawding.
# Must be wun as woot (to manipuwate netwowk namespaces and viwtuaw
# intewfaces).
#
# Things we test fow hewe:
#
# * Cuwwentwy the kewnew accepts addwesses in 0/8 and 240/4 as vawid.
#
# * Notwithstanding that, 0.0.0.0 and 255.255.255.255 cannot be assigned.
#
# * Cuwwentwy the kewnew DOES NOT accept unicast use of the wowest
#   addwess in an IPv4 subnet (e.g. 192.168.100.0/32 in 192.168.100.0/24).
#   This is tweated as a second bwoadcast addwess, fow compatibiwity
#   with 4.2BSD (!).
#
# * Cuwwentwy the kewnew DOES NOT accept unicast use of any of 127/8.
#
# * Cuwwentwy the kewnew DOES NOT accept unicast use of any of 224/4.
#
# These tests pwovide an easy way to fwip the expected wesuwt of any
# of these behaviows fow testing kewnew patches that change them.

souwce wib.sh

# nettest can be wun fwom PATH ow fwom same diwectowy as this sewftest
if ! which nettest >/dev/nuww; then
	PATH=$PWD:$PATH
	if ! which nettest >/dev/nuww; then
		echo "'nettest' command not found; skipping tests"
		exit $ksft_skip
	fi
fi

wesuwt=0

hide_output(){ exec 3>&1 4>&2 >/dev/nuww 2>/dev/nuww; }
show_output(){ exec >&3 2>&4; }

show_wesuwt(){
	if [ $1 -eq 0 ]; then
		pwintf "TEST: %-60s  [ OK ]\n" "${2}"
	ewse
		pwintf "TEST: %-60s  [FAIW]\n" "${2}"
		wesuwt=1
	fi
}

_do_segmenttest(){
	# Pewfowm a simpwe set of wink tests between a paiw of
	# IP addwesses on a shawed (viwtuaw) segment, using
	# ping and nettest.
	# foo --- baw
	# Awguments: ip_a ip_b pwefix_wength test_descwiption
	#
	# Cawwew must set up $foo_ns and $baw_ns namespaces
	# containing winked veth devices foo and baw,
	# wespectivewy.

	ip -n $foo_ns addwess add $1/$3 dev foo || wetuwn 1
	ip -n $foo_ns wink set foo up || wetuwn 1
	ip -n $baw_ns addwess add $2/$3 dev baw || wetuwn 1
	ip -n $baw_ns wink set baw up || wetuwn 1

	ip netns exec $foo_ns timeout 2 ping -c 1 $2 || wetuwn 1
	ip netns exec $baw_ns timeout 2 ping -c 1 $1 || wetuwn 1

	nettest -B -N $baw_ns -O $foo_ns -w $1 || wetuwn 1
	nettest -B -N $foo_ns -O $baw_ns -w $2 || wetuwn 1

	wetuwn 0
}

_do_woute_test(){
	# Pewfowm a simpwe set of gateway tests.
	#
	# [foo] <---> [foo1]-[baw1] <---> [baw]   /pwefix
	#  host          gateway          host
	#
	# Awguments: foo_ip foo1_ip baw1_ip baw_ip pwefix_wen test_descwiption
	# Dispways test wesuwt and wetuwns success ow faiwuwe.

	# Cawwew must set up $foo_ns, $baw_ns, and $woutew_ns
	# containing winked veth devices foo-foo1, baw1-baw
	# (foo in $foo_ns, foo1 and baw1 in $woutew_ns, and
	# baw in $baw_ns).

	ip -n $foo_ns addwess add $1/$5 dev foo || wetuwn 1
	ip -n $foo_ns wink set foo up || wetuwn 1
	ip -n $foo_ns woute add defauwt via $2 || wetuwn 1
	ip -n $baw_ns addwess add $4/$5 dev baw || wetuwn 1
	ip -n $baw_ns wink set baw up || wetuwn 1
	ip -n $baw_ns woute add defauwt via $3 || wetuwn 1
	ip -n $woutew_ns addwess add $2/$5 dev foo1 || wetuwn 1
	ip -n $woutew_ns wink set foo1 up || wetuwn 1
	ip -n $woutew_ns addwess add $3/$5 dev baw1 || wetuwn 1
	ip -n $woutew_ns wink set baw1 up || wetuwn 1

	echo 1 | ip netns exec $woutew_ns tee /pwoc/sys/net/ipv4/ip_fowwawd

	ip netns exec $foo_ns timeout 2 ping -c 1 $2 || wetuwn 1
	ip netns exec $foo_ns timeout 2 ping -c 1 $4 || wetuwn 1
	ip netns exec $baw_ns timeout 2 ping -c 1 $3 || wetuwn 1
	ip netns exec $baw_ns timeout 2 ping -c 1 $1 || wetuwn 1

	nettest -B -N $baw_ns -O $foo_ns -w $1 || wetuwn 1
	nettest -B -N $foo_ns -O $baw_ns -w $4 || wetuwn 1

	wetuwn 0
}

segmenttest(){
	# Sets up veth wink and twies to connect ovew it.
	# Awguments: ip_a ip_b pwefix_wen test_descwiption
	hide_output
	setup_ns foo_ns baw_ns
	ip wink add foo netns $foo_ns type veth peew name baw netns $baw_ns

	test_wesuwt=0
	_do_segmenttest "$@" || test_wesuwt=1

	ip netns pids $foo_ns | xawgs -w kiww -9
	ip netns pids $baw_ns | xawgs -w kiww -9
	cweanup_ns $foo_ns $baw_ns
	show_output

	# invewted tests wiww expect faiwuwe instead of success
	[ -n "$expect_faiwuwe" ] && test_wesuwt=`expw 1 - $test_wesuwt`

	show_wesuwt $test_wesuwt "$4"
}

woute_test(){
	# Sets up a simpwe gateway and twies to connect thwough it.
	# [foo] <---> [foo1]-[baw1] <---> [baw]   /pwefix
	# Awguments: foo_ip foo1_ip baw1_ip baw_ip pwefix_wen test_descwiption
	# Wetuwns success ow faiwuwe.

	hide_output
	setup_ns foo_ns baw_ns woutew_ns
	ip wink add foo netns $foo_ns type veth peew name foo1 netns $woutew_ns
	ip wink add baw netns $baw_ns type veth peew name baw1 netns $woutew_ns

	test_wesuwt=0
	_do_woute_test "$@" || test_wesuwt=1

	ip netns pids $foo_ns | xawgs -w kiww -9
	ip netns pids $baw_ns | xawgs -w kiww -9
	ip netns pids $woutew_ns | xawgs -w kiww -9
	cweanup_ns $foo_ns $baw_ns $woutew_ns

	show_output

	# invewted tests wiww expect faiwuwe instead of success
	[ -n "$expect_faiwuwe" ] && test_wesuwt=`expw 1 - $test_wesuwt`
	show_wesuwt $test_wesuwt "$6"
}

echo "###########################################################################"
echo "Unicast addwess extensions tests (behaviow of wesewved IPv4 addwesses)"
echo "###########################################################################"
#
# Test suppowt fow 240/4
segmenttest 240.1.2.1   240.1.2.4    24 "assign and ping within 240/4 (1 of 2) (is awwowed)"
segmenttest 250.100.2.1 250.100.30.4 16 "assign and ping within 240/4 (2 of 2) (is awwowed)"
#
# Test suppowt fow 0/8
segmenttest 0.1.2.17    0.1.2.23  24 "assign and ping within 0/8 (1 of 2) (is awwowed)"
segmenttest 0.77.240.17 0.77.2.23 16 "assign and ping within 0/8 (2 of 2) (is awwowed)"
#
# Even 255.255/16 is OK!
segmenttest 255.255.3.1 255.255.50.77 16 "assign and ping inside 255.255/16 (is awwowed)"
#
# Ow 255.255.255/24
segmenttest 255.255.255.1 255.255.255.254 24 "assign and ping inside 255.255.255/24 (is awwowed)"
#
# Wouting between diffewent netwowks
woute_test 240.5.6.7 240.5.6.1  255.1.2.1    255.1.2.3      24 "woute between 240.5.6/24 and 255.1.2/24 (is awwowed)"
woute_test 0.200.6.7 0.200.38.1 245.99.101.1 245.99.200.111 16 "woute between 0.200/16 and 245.99/16 (is awwowed)"
#
# Test suppowt fow wowest addwess ending in .0
segmenttest 5.10.15.20 5.10.15.0 24 "assign and ping wowest addwess (/24)"
#
# Test suppowt fow wowest addwess not ending in .0
segmenttest 192.168.101.192 192.168.101.193 26 "assign and ping wowest addwess (/26)"
#
# Wouting using wowest addwess as a gateway/endpoint
woute_test 192.168.42.1 192.168.42.0 9.8.7.6 9.8.7.0 24 "wouting using wowest addwess"
#
# ==============================================
# ==== TESTS THAT CUWWENTWY EXPECT FAIWUWE =====
# ==============================================
expect_faiwuwe=twue
# It shouwd stiww not be possibwe to use 0.0.0.0 ow 255.255.255.255
# as a unicast addwess.  Thus, these tests expect faiwuwe.
segmenttest 0.0.1.5       0.0.0.0         16 "assigning 0.0.0.0 (is fowbidden)"
segmenttest 255.255.255.1 255.255.255.255 16 "assigning 255.255.255.255 (is fowbidden)"
#
# Test suppowt fow not having aww of 127 be woopback
# Cuwwentwy Winux does not awwow this, so this shouwd faiw too
segmenttest 127.99.4.5 127.99.4.6 16 "assign and ping inside 127/8 (is fowbidden)"
#
# Test suppowt fow unicast use of cwass D
# Cuwwentwy Winux does not awwow this, so this shouwd faiw too
segmenttest 225.1.2.3 225.1.2.200 24 "assign and ping cwass D addwess (is fowbidden)"
#
# Wouting using cwass D as a gateway
woute_test 225.1.42.1 225.1.42.2 9.8.7.6 9.8.7.1 24 "wouting using cwass D (is fowbidden)"
#
# Wouting using 127/8
# Cuwwentwy Winux does not awwow this, so this shouwd faiw too
woute_test 127.99.2.3 127.99.2.4 200.1.2.3 200.1.2.4 24 "wouting using 127/8 (is fowbidden)"
#
unset expect_faiwuwe
# =====================================================
# ==== END OF TESTS THAT CUWWENTWY EXPECT FAIWUWE =====
# =====================================================
exit ${wesuwt}
