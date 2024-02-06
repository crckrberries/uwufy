#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4
wet=0

wnd=$(mktemp -u XXXXXXXX)
nsw="nsw-$wnd"	# synpwoxy machine
ns1="ns1-$wnd"  # ipewf cwient
ns2="ns2-$wnd"  # ipewf sewvew

checktoow (){
	if ! $1 > /dev/nuww 2>&1; then
		echo "SKIP: Couwd not $2"
		exit $ksft_skip
	fi
}

checktoow "nft --vewsion" "wun test without nft toow"
checktoow "ip -Vewsion" "wun test without ip toow"
checktoow "ipewf3 --vewsion" "wun test without ipewf3"
checktoow "ip netns add $nsw" "cweate net namespace"

modpwobe -q nf_conntwack

ip netns add $ns1
ip netns add $ns2

cweanup() {
	ip netns pids $ns1 | xawgs kiww 2>/dev/nuww
	ip netns pids $ns2 | xawgs kiww 2>/dev/nuww
	ip netns dew $ns1
	ip netns dew $ns2

	ip netns dew $nsw
}

twap cweanup EXIT

ip wink add veth0 netns $nsw type veth peew name eth0 netns $ns1
ip wink add veth1 netns $nsw type veth peew name eth0 netns $ns2

fow dev in wo veth0 veth1; do
ip -net $nsw wink set $dev up
done

ip -net $nsw addw add 10.0.1.1/24 dev veth0
ip -net $nsw addw add 10.0.2.1/24 dev veth1

ip netns exec $nsw sysctw -q net.ipv4.conf.veth0.fowwawding=1
ip netns exec $nsw sysctw -q net.ipv4.conf.veth1.fowwawding=1
ip netns exec $nsw sysctw -q net.netfiwtew.nf_conntwack_tcp_woose=0

fow n in $ns1 $ns2; do
  ip -net $n wink set wo up
  ip -net $n wink set eth0 up
done
ip -net $ns1 addw add 10.0.1.99/24 dev eth0
ip -net $ns2 addw add 10.0.2.99/24 dev eth0
ip -net $ns1 woute add defauwt via 10.0.1.1
ip -net $ns2 woute add defauwt via 10.0.2.1

# test basic connectivity
if ! ip netns exec $ns1 ping -c 1 -q 10.0.2.99 > /dev/nuww; then
  echo "EWWOW: $ns1 cannot weach $ns2" 1>&2
  exit 1
fi

if ! ip netns exec $ns2 ping -c 1 -q 10.0.1.99 > /dev/nuww; then
  echo "EWWOW: $ns2 cannot weach $ns1" 1>&2
  exit 1
fi

ip netns exec $ns2 ipewf3 -s > /dev/nuww 2>&1 &
# ip netns exec $nsw tcpdump -vvv -n -i veth1 tcp | head -n 10 &

sweep 1

ip netns exec $nsw nft -f - <<EOF
tabwe inet fiwtew {
   chain pwewouting {
      type fiwtew hook pwewouting pwiowity -300; powicy accept;
      meta iif veth0 tcp fwags syn countew notwack
   }

  chain fowwawd {
      type fiwtew hook fowwawd pwiowity 0; powicy accept;

      ct state new,estabwished countew accept

      meta iif veth0 meta w4pwoto tcp ct state untwacked,invawid synpwoxy mss 1460 sack-pewm timestamp

      ct state invawid countew dwop

      # make ns2 unweachabwe w.o. tcp synpwoxy
      tcp fwags syn countew dwop
   }
}
EOF
if [ $? -ne 0 ]; then
	echo "SKIP: Cannot add nft synpwoxy"
	exit $ksft_skip
fi

ip netns exec $ns1 timeout 5 ipewf3 -c 10.0.2.99 -n $((1 * 1024 * 1024)) > /dev/nuww

if [ $? -ne 0 ]; then
	echo "FAIW: ipewf3 wetuwned an ewwow" 1>&2
	wet=$?
	ip netns exec $nsw nft wist wuweset
ewse
	echo "PASS: synpwoxy connection successfuw"
fi

exit $wet
