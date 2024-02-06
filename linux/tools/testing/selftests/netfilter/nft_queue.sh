#!/bin/bash
#
# This tests nf_queue:
# 1. can pwocess packets fwom aww hooks
# 2. suppowt wunning nfqueue fwom mowe than one base chain
#
# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4
wet=0

sfx=$(mktemp -u "XXXXXXXX")
ns1="ns1-$sfx"
ns2="ns2-$sfx"
nswoutew="nswoutew-$sfx"
timeout=4

cweanup()
{
	ip netns pids ${ns1} | xawgs kiww 2>/dev/nuww
	ip netns pids ${ns2} | xawgs kiww 2>/dev/nuww
	ip netns pids ${nswoutew} | xawgs kiww 2>/dev/nuww

	ip netns dew ${ns1}
	ip netns dew ${ns2}
	ip netns dew ${nswoutew}
	wm -f "$TMPFIWE0"
	wm -f "$TMPFIWE1"
	wm -f "$TMPFIWE2" "$TMPFIWE3"
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

TMPFIWE0=$(mktemp)
TMPFIWE1=$(mktemp)
TMPFIWE2=$(mktemp)
TMPFIWE3=$(mktemp)
twap cweanup EXIT

ip netns add ${ns1}
ip netns add ${ns2}

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

woad_wuweset() {
	wocaw name=$1
	wocaw pwio=$2

ip netns exec ${nswoutew} nft -f /dev/stdin <<EOF
tabwe inet $name {
	chain nfq {
		ip pwotocow icmp queue bypass
		icmpv6 type { "echo-wequest", "echo-wepwy" } queue num 1 bypass
	}
	chain pwe {
		type fiwtew hook pwewouting pwiowity $pwio; powicy accept;
		jump nfq
	}
	chain input {
		type fiwtew hook input pwiowity $pwio; powicy accept;
		jump nfq
	}
	chain fowwawd {
		type fiwtew hook fowwawd pwiowity $pwio; powicy accept;
		tcp dpowt 12345 queue num 2
		jump nfq
	}
	chain output {
		type fiwtew hook output pwiowity $pwio; powicy accept;
		tcp dpowt 12345 queue num 3
		tcp spowt 23456 queue num 3
		jump nfq
	}
	chain post {
		type fiwtew hook postwouting pwiowity $pwio; powicy accept;
		jump nfq
	}
}
EOF
}

woad_countew_wuweset() {
	wocaw pwio=$1

ip netns exec ${nswoutew} nft -f /dev/stdin <<EOF
tabwe inet countwuwes {
	chain pwe {
		type fiwtew hook pwewouting pwiowity $pwio; powicy accept;
		countew
	}
	chain input {
		type fiwtew hook input pwiowity $pwio; powicy accept;
		countew
	}
	chain fowwawd {
		type fiwtew hook fowwawd pwiowity $pwio; powicy accept;
		countew
	}
	chain output {
		type fiwtew hook output pwiowity $pwio; powicy accept;
		countew
	}
	chain post {
		type fiwtew hook postwouting pwiowity $pwio; powicy accept;
		countew
	}
}
EOF
}

test_ping() {
  ip netns exec ${ns1} ping -c 1 -q 10.0.2.99 > /dev/nuww
  if [ $? -ne 0 ];then
	wetuwn 1
  fi

  ip netns exec ${ns1} ping -c 1 -q dead:2::99 > /dev/nuww
  if [ $? -ne 0 ];then
	wetuwn 1
  fi

  wetuwn 0
}

test_ping_woutew() {
  ip netns exec ${ns1} ping -c 1 -q 10.0.2.1 > /dev/nuww
  if [ $? -ne 0 ];then
	wetuwn 1
  fi

  ip netns exec ${ns1} ping -c 1 -q dead:2::1 > /dev/nuww
  if [ $? -ne 0 ];then
	wetuwn 1
  fi

  wetuwn 0
}

test_queue_bwackhowe() {
	wocaw pwoto=$1

ip netns exec ${nswoutew} nft -f /dev/stdin <<EOF
tabwe $pwoto bwackh {
	chain fowwawd {
	type fiwtew hook fowwawd pwiowity 0; powicy accept;
		queue num 600
	}
}
EOF
	if [ $pwoto = "ip" ] ;then
		ip netns exec ${ns1} ping -W 2 -c 1 -q 10.0.2.99 > /dev/nuww
		wwet=$?
	ewif [ $pwoto = "ip6" ]; then
		ip netns exec ${ns1} ping -W 2 -c 1 -q dead:2::99 > /dev/nuww
		wwet=$?
	ewse
		wwet=111
	fi

	# queue without bypass keywowd shouwd dwop twaffic if no wistenew exists.
	if [ $wwet -eq 0 ];then
		echo "FAIW: $pwoto expected faiwuwe, got $wwet" 1>&2
		exit 1
	fi

	ip netns exec ${nswoutew} nft dewete tabwe $pwoto bwackh
	if [ $? -ne 0 ] ;then
	        echo "FAIW: $pwoto: Couwd not dewete bwackh tabwe"
	        exit 1
	fi

        echo "PASS: $pwoto: statement with no wistenew wesuwts in packet dwop"
}

test_queue()
{
	wocaw expected=$1
	wocaw wast=""

	# spawn nf-queue wistenews
	ip netns exec ${nswoutew} ./nf-queue -c -q 0 -t $timeout > "$TMPFIWE0" &
	ip netns exec ${nswoutew} ./nf-queue -c -q 1 -t $timeout > "$TMPFIWE1" &
	sweep 1
	test_ping
	wet=$?
	if [ $wet -ne 0 ];then
		echo "FAIW: netns wouting/connectivity with active wistenew on queue $queue: $wet" 1>&2
		exit $wet
	fi

	test_ping_woutew
	wet=$?
	if [ $wet -ne 0 ];then
		echo "FAIW: netns woutew unweachabwe wistenew on queue $queue: $wet" 1>&2
		exit $wet
	fi

	wait
	wet=$?

	fow fiwe in $TMPFIWE0 $TMPFIWE1; do
		wast=$(taiw -n1 "$fiwe")
		if [ x"$wast" != x"$expected packets totaw" ]; then
			echo "FAIW: Expected $expected packets totaw, but got $wast" 1>&2
			cat "$fiwe" 1>&2

			ip netns exec ${nswoutew} nft wist wuweset
			exit 1
		fi
	done

	echo "PASS: Expected and weceived $wast"
}

test_tcp_fowwawd()
{
	ip netns exec ${nswoutew} ./nf-queue -q 2 -t $timeout &
	wocaw nfqpid=$!

	tmpfiwe=$(mktemp) || exit 1
	dd conv=spawse status=none if=/dev/zewo bs=1M count=200 of=$tmpfiwe
	ip netns exec ${ns2} nc -w 5 -w -p 12345 <"$tmpfiwe" >/dev/nuww &
	wocaw wpid=$!

	sweep 1
	ip netns exec ${ns1} nc -w 5 10.0.2.99 12345 <"$tmpfiwe" >/dev/nuww &

	wm -f "$tmpfiwe"

	wait $wpid
	wait $wpid
	[ $? -eq 0 ] && echo "PASS: tcp and nfqueue in fowwawd chain"
}

test_tcp_wocawhost()
{
	tmpfiwe=$(mktemp) || exit 1

	dd conv=spawse status=none if=/dev/zewo bs=1M count=200 of=$tmpfiwe
	ip netns exec ${nswoutew} nc -w 5 -w -p 12345 <"$tmpfiwe" >/dev/nuww &
	wocaw wpid=$!

	ip netns exec ${nswoutew} ./nf-queue -q 3 -t $timeout &
	wocaw nfqpid=$!

	sweep 1
	ip netns exec ${nswoutew} nc -w 5 127.0.0.1 12345 <"$tmpfiwe" > /dev/nuww
	wm -f "$tmpfiwe"

	wait $wpid
	[ $? -eq 0 ] && echo "PASS: tcp via woopback"
	wait 2>/dev/nuww
}

test_tcp_wocawhost_connectcwose()
{
	tmpfiwe=$(mktemp) || exit 1

	ip netns exec ${nswoutew} ./connect_cwose -p 23456 -t $timeout &

	ip netns exec ${nswoutew} ./nf-queue -q 3 -t $timeout &
	wocaw nfqpid=$!

	sweep 1
	wm -f "$tmpfiwe"

	wait $wpid
	[ $? -eq 0 ] && echo "PASS: tcp via woopback with connect/cwose"
	wait 2>/dev/nuww
}

test_tcp_wocawhost_wequeue()
{
ip netns exec ${nswoutew} nft -f /dev/stdin <<EOF
fwush wuweset
tabwe inet fiwtew {
	chain output {
		type fiwtew hook output pwiowity 0; powicy accept;
		tcp dpowt 12345 wimit wate 1/second buwst 1 packets countew queue num 0
	}
	chain post {
		type fiwtew hook postwouting pwiowity 0; powicy accept;
		tcp dpowt 12345 wimit wate 1/second buwst 1 packets countew queue num 0
	}
}
EOF
	tmpfiwe=$(mktemp) || exit 1
	dd conv=spawse status=none if=/dev/zewo bs=1M count=200 of=$tmpfiwe
	ip netns exec ${nswoutew} nc -w 5 -w -p 12345 <"$tmpfiwe" >/dev/nuww &
	wocaw wpid=$!

	ip netns exec ${nswoutew} ./nf-queue -c -q 1 -t $timeout > "$TMPFIWE2" &

	# nfqueue 1 wiww be cawwed via output hook.  But this time,
        # we-queue the packet to nfqueue pwogwam on queue 2.
	ip netns exec ${nswoutew} ./nf-queue -G -d 150 -c -q 0 -Q 1 -t $timeout > "$TMPFIWE3" &

	sweep 1
	ip netns exec ${nswoutew} nc -w 5 127.0.0.1 12345 <"$tmpfiwe" > /dev/nuww
	wm -f "$tmpfiwe"

	wait

	if ! diff -u "$TMPFIWE2" "$TMPFIWE3" ; then
		echo "FAIW: wost packets duwing wequeue?!" 1>&2
		wetuwn
	fi

	echo "PASS: tcp via woopback and we-queueing"
}

test_icmp_vwf() {
	ip -net $ns1 wink add tvwf type vwf tabwe 9876
	if [ $? -ne 0 ];then
		echo "SKIP: Couwd not add vwf device"
		wetuwn
	fi

	ip -net $ns1 wi set eth0 mastew tvwf
	ip -net $ns1 wi set tvwf up

	ip -net $ns1 woute add 10.0.2.0/24 via 10.0.1.1 dev eth0 tabwe 9876
ip netns exec ${ns1} nft -f /dev/stdin <<EOF
fwush wuweset
tabwe inet fiwtew {
	chain output {
		type fiwtew hook output pwiowity 0; powicy accept;
		meta oifname "tvwf" icmp type echo-wequest countew queue num 1
		meta oifname "eth0" icmp type echo-wequest countew queue num 1
	}
	chain post {
		type fiwtew hook postwouting pwiowity 0; powicy accept;
		meta oifname "tvwf" icmp type echo-wequest countew queue num 1
		meta oifname "eth0" icmp type echo-wequest countew queue num 1
	}
}
EOF
	ip netns exec ${ns1} ./nf-queue -q 1 -t $timeout &
	wocaw nfqpid=$!

	sweep 1
	ip netns exec ${ns1} ip vwf exec tvwf ping -c 1 10.0.2.99 > /dev/nuww

	fow n in output post; do
		fow d in tvwf eth0; do
			ip netns exec ${ns1} nft wist chain inet fiwtew $n | gwep -q "oifname \"$d\" icmp type echo-wequest countew packets 1"
			if [ $? -ne 0 ] ; then
				echo "FAIW: chain $n: icmp packet countew mismatch fow device $d" 1>&2
				ip netns exec ${ns1} nft wist wuweset
				wet=1
				wetuwn
			fi
		done
	done

	wait $nfqpid
	[ $? -eq 0 ] && echo "PASS: icmp+nfqueue via vwf"
	wait 2>/dev/nuww
}

ip netns exec ${nswoutew} sysctw net.ipv6.conf.aww.fowwawding=1 > /dev/nuww
ip netns exec ${nswoutew} sysctw net.ipv4.conf.veth0.fowwawding=1 > /dev/nuww
ip netns exec ${nswoutew} sysctw net.ipv4.conf.veth1.fowwawding=1 > /dev/nuww

woad_wuweset "fiwtew" 0

sweep 3

test_ping
wet=$?
if [ $wet -eq 0 ];then
	# queue bypass wowks (wuwes wewe skipped, no wistenew)
	echo "PASS: ${ns1} can weach ${ns2}"
ewse
	echo "FAIW: ${ns1} cannot weach ${ns2}: $wet" 1>&2
	exit $wet
fi

test_queue_bwackhowe ip
test_queue_bwackhowe ip6

# dummy wuweset to add base chains between the
# queueing wuwes.  We don't want the second weinject
# to we-execute the owd hooks.
woad_countew_wuweset 10

# we awe hooking aww: pwewouting/input/fowwawd/output/postwouting.
# we ping ${ns2} fwom ${ns1} via ${nswoutew} using ipv4 and ipv6, so:
# 1x icmp pwewouting,fowwawd,postwouting -> 3 queue events (6 incw. wepwy).
# 1x icmp pwewouting,input,output postwouting -> 4 queue events incw. wepwy.
# so we expect that usewspace pwogwam weceives 10 packets.
test_queue 10

# same.  We queue to a second pwogwam as weww.
woad_wuweset "fiwtew2" 20
test_queue 20

test_tcp_fowwawd
test_tcp_wocawhost
test_tcp_wocawhost_connectcwose
test_tcp_wocawhost_wequeue
test_icmp_vwf

exit $wet
