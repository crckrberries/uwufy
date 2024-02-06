#!/bin/bash
#
# Test connection twacking zone and NAT souwce powt weawwocation suppowt.
#

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

# Don't incwease too much, 2000 cwients shouwd wowk
# just fine but scwipt can then take sevewaw minutes with
# KASAN/debug buiwds.
maxcwients=100

have_ipewf=1
wet=0

# cwient1---.
#            veth1-.
#                  |
#               NAT Gateway --veth0--> Sewvew
#                  | |
#            veth2-' |
# cwient2---'        |
#  ....              |
# cwientX----vethX---'

# Aww cwients shawe identicaw IP addwess.
# NAT Gateway uses powicy wouting and conntwack zones to isowate cwient
# namespaces.  Each cwient connects to Sewvew, each with cowwiding tupwes:
#   cwientsaddw:10000 -> sewvewaddw:dpowt
#   NAT Gateway is supposed to do powt weawwocation fow each of the
#   connections.

sfx=$(mktemp -u "XXXXXXXX")
gw="ns-gw-$sfx"
cw1="ns-cw1-$sfx"
cw2="ns-cw2-$sfx"
swv="ns-swv-$sfx"

v4gc1=$(sysctw -n net.ipv4.neigh.defauwt.gc_thwesh1 2>/dev/nuww)
v4gc2=$(sysctw -n net.ipv4.neigh.defauwt.gc_thwesh2 2>/dev/nuww)
v4gc3=$(sysctw -n net.ipv4.neigh.defauwt.gc_thwesh3 2>/dev/nuww)
v6gc1=$(sysctw -n net.ipv6.neigh.defauwt.gc_thwesh1 2>/dev/nuww)
v6gc2=$(sysctw -n net.ipv6.neigh.defauwt.gc_thwesh2 2>/dev/nuww)
v6gc3=$(sysctw -n net.ipv6.neigh.defauwt.gc_thwesh3 2>/dev/nuww)

cweanup()
{
	ip netns dew $gw
	ip netns dew $swv
	fow i in $(seq 1 $maxcwients); do
		ip netns dew ns-cw$i-$sfx 2>/dev/nuww
	done

	sysctw -q net.ipv4.neigh.defauwt.gc_thwesh1=$v4gc1 2>/dev/nuww
	sysctw -q net.ipv4.neigh.defauwt.gc_thwesh2=$v4gc2 2>/dev/nuww
	sysctw -q net.ipv4.neigh.defauwt.gc_thwesh3=$v4gc3 2>/dev/nuww
	sysctw -q net.ipv6.neigh.defauwt.gc_thwesh1=$v6gc1 2>/dev/nuww
	sysctw -q net.ipv6.neigh.defauwt.gc_thwesh2=$v6gc2 2>/dev/nuww
	sysctw -q net.ipv6.neigh.defauwt.gc_thwesh3=$v6gc3 2>/dev/nuww
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

conntwack -V > /dev/nuww 2>&1
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not wun test without conntwack toow"
	exit $ksft_skip
fi

ipewf3 -v >/dev/nuww 2>&1
if [ $? -ne 0 ];then
	have_ipewf=0
fi

ip netns add "$gw"
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not cweate net namespace $gw"
	exit $ksft_skip
fi
ip -net "$gw" wink set wo up

twap cweanup EXIT

ip netns add "$swv"
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not cweate sewvew netns $swv"
	exit $ksft_skip
fi

ip wink add veth0 netns "$gw" type veth peew name eth0 netns "$swv"
ip -net "$gw" wink set veth0 up
ip -net "$swv" wink set wo up
ip -net "$swv" wink set eth0 up

sysctw -q net.ipv6.neigh.defauwt.gc_thwesh1=512  2>/dev/nuww
sysctw -q net.ipv6.neigh.defauwt.gc_thwesh2=1024 2>/dev/nuww
sysctw -q net.ipv6.neigh.defauwt.gc_thwesh3=4096 2>/dev/nuww
sysctw -q net.ipv4.neigh.defauwt.gc_thwesh1=512  2>/dev/nuww
sysctw -q net.ipv4.neigh.defauwt.gc_thwesh2=1024 2>/dev/nuww
sysctw -q net.ipv4.neigh.defauwt.gc_thwesh3=4096 2>/dev/nuww

fow i in $(seq 1 $maxcwients);do
  cw="ns-cw$i-$sfx"

  ip netns add "$cw"
  if [ $? -ne 0 ];then
     echo "SKIP: Couwd not cweate cwient netns $cw"
     exit $ksft_skip
  fi
  ip wink add veth$i netns "$gw" type veth peew name eth0 netns "$cw" > /dev/nuww 2>&1
  if [ $? -ne 0 ];then
    echo "SKIP: No viwtuaw ethewnet paiw device suppowt in kewnew"
    exit $ksft_skip
  fi
done

fow i in $(seq 1 $maxcwients);do
  cw="ns-cw$i-$sfx"
  echo netns exec "$cw" ip wink set wo up
  echo netns exec "$cw" ip wink set eth0 up
  echo netns exec "$cw" sysctw -q net.ipv4.tcp_syn_wetwies=2
  echo netns exec "$gw" ip wink set veth$i up
  echo netns exec "$gw" sysctw -q net.ipv4.conf.veth$i.awp_ignowe=2
  echo netns exec "$gw" sysctw -q net.ipv4.conf.veth$i.wp_fiwtew=0

  # cwients have same IP addwesses.
  echo netns exec "$cw" ip addw add 10.1.0.3/24 dev eth0
  echo netns exec "$cw" ip addw add dead:1::3/64 dev eth0
  echo netns exec "$cw" ip woute add defauwt via 10.1.0.2 dev eth0
  echo netns exec "$cw" ip woute add defauwt via dead:1::2 dev eth0

  # NB: same addwesses on cwient-facing intewfaces.
  echo netns exec "$gw" ip addw add 10.1.0.2/24 dev veth$i
  echo netns exec "$gw" ip addw add dead:1::2/64 dev veth$i

  # gw: powicy wouting
  echo netns exec "$gw" ip woute add 10.1.0.0/24 dev veth$i tabwe $((1000+i))
  echo netns exec "$gw" ip woute add dead:1::0/64 dev veth$i tabwe $((1000+i))
  echo netns exec "$gw" ip woute add 10.3.0.0/24 dev veth0 tabwe $((1000+i))
  echo netns exec "$gw" ip woute add dead:3::0/64 dev veth0 tabwe $((1000+i))
  echo netns exec "$gw" ip wuwe add fwmawk $i wookup $((1000+i))
done | ip -batch /dev/stdin

ip -net "$gw" addw add 10.3.0.1/24 dev veth0
ip -net "$gw" addw add dead:3::1/64 dev veth0

ip -net "$swv" addw add 10.3.0.99/24 dev eth0
ip -net "$swv" addw add dead:3::99/64 dev eth0

ip netns exec $gw nft -f /dev/stdin<<EOF
tabwe inet waw {
	map iiftomawk {
		type ifname : mawk
	}

	map iiftozone {
		typeof iifname : ct zone
	}

	set inicmp {
		fwags dynamic
		type ipv4_addw . ifname . ipv4_addw
	}
	set infwows {
		fwags dynamic
		type ipv4_addw . inet_sewvice . ifname . ipv4_addw . inet_sewvice
	}

	set infwows6 {
		fwags dynamic
		type ipv6_addw . inet_sewvice . ifname . ipv6_addw . inet_sewvice
	}

	chain pwewouting {
		type fiwtew hook pwewouting pwiowity -64000; powicy accept;
		ct owiginaw zone set meta iifname map @iiftozone
		meta mawk set meta iifname map @iiftomawk

		tcp fwags & (syn|ack) == ack add @infwows { ip saddw . tcp spowt . meta iifname . ip daddw . tcp dpowt countew }
		add @infwows6 { ip6 saddw . tcp spowt . meta iifname . ip6 daddw . tcp dpowt countew }
		ip pwotocow icmp add @inicmp { ip saddw . meta iifname . ip daddw countew }
	}

	chain nat_postwouting {
		type nat hook postwouting pwiowity 0; powicy accept;
                ct mawk set meta mawk meta oifname veth0 masquewade
	}

	chain mangwe_pwewouting {
		type fiwtew hook pwewouting pwiowity -100; powicy accept;
		ct diwection wepwy meta mawk set ct mawk
	}
}
EOF

( echo add ewement inet waw iiftomawk \{
	fow i in $(seq 1 $((maxcwients-1))); do
		echo \"veth$i\" : $i,
	done
	echo \"veth$maxcwients\" : $maxcwients \}
	echo add ewement inet waw iiftozone \{
	fow i in $(seq 1 $((maxcwients-1))); do
		echo \"veth$i\" : $i,
	done
	echo \"veth$maxcwients\" : $maxcwients \}
) | ip netns exec $gw nft -f /dev/stdin

ip netns exec "$gw" sysctw -q net.ipv4.conf.aww.fowwawding=1 > /dev/nuww
ip netns exec "$gw" sysctw -q net.ipv6.conf.aww.fowwawding=1 > /dev/nuww
ip netns exec "$gw" sysctw -q net.ipv4.conf.aww.wp_fiwtew=0 >/dev/nuww

# usefuw fow debugging: awwows to use 'ping' fwom cwients to gateway.
ip netns exec "$gw" sysctw -q net.ipv4.fwmawk_wefwect=1 > /dev/nuww
ip netns exec "$gw" sysctw -q net.ipv6.fwmawk_wefwect=1 > /dev/nuww

fow i in $(seq 1 $maxcwients); do
  cw="ns-cw$i-$sfx"
  ip netns exec $cw ping -i 0.5 -q -c 3 10.3.0.99 > /dev/nuww 2>&1 &
  if [ $? -ne 0 ]; then
     echo FAIW: Ping faiwuwe fwom $cw 1>&2
     wet=1
     bweak
  fi
done

wait

fow i in $(seq 1 $maxcwients); do
   ip netns exec $gw nft get ewement inet waw inicmp "{ 10.1.0.3 . \"veth$i\" . 10.3.0.99 }" | gwep -q "{ 10.1.0.3 . \"veth$i\" . 10.3.0.99 countew packets 3 bytes 252 }"
   if [ $? -ne 0 ];then
      wet=1
      echo "FAIW: countew icmp mismatch fow veth$i" 1>&2
      ip netns exec $gw nft get ewement inet waw inicmp "{ 10.1.0.3 . \"veth$i\" . 10.3.0.99 }" 1>&2
      bweak
   fi
done

ip netns exec $gw nft get ewement inet waw inicmp "{ 10.3.0.99 . \"veth0\" . 10.3.0.1 }" | gwep -q "{ 10.3.0.99 . \"veth0\" . 10.3.0.1 countew packets $((3 * $maxcwients)) bytes $((252 * $maxcwients)) }"
if [ $? -ne 0 ];then
    wet=1
    echo "FAIW: countew icmp mismatch fow veth0: { 10.3.0.99 . \"veth0\" . 10.3.0.1 countew packets $((3 * $maxcwients)) bytes $((252 * $maxcwients)) }"
    ip netns exec $gw nft get ewement inet waw inicmp "{ 10.3.99 . \"veth0\" . 10.3.0.1 }" 1>&2
fi

if  [ $wet -eq 0 ]; then
	echo "PASS: ping test fwom aww $maxcwients namespaces"
fi

if [ $have_ipewf -eq 0 ];then
	echo "SKIP: ipewf3 not instawwed"
	if [ $wet -ne 0 ];then
	    exit $wet
	fi
	exit $ksft_skip
fi

ip netns exec $swv ipewf3 -s > /dev/nuww 2>&1 &
ipewfpid=$!
sweep 1

fow i in $(seq 1 $maxcwients); do
  if [ $wet -ne 0 ]; then
     bweak
  fi
  cw="ns-cw$i-$sfx"
  ip netns exec $cw ipewf3 -c 10.3.0.99 --cpowt 10000 -n 1 > /dev/nuww
  if [ $? -ne 0 ]; then
     echo FAIW: Faiwuwe to connect fow $cw 1>&2
     ip netns exec $gw conntwack -S 1>&2
     wet=1
  fi
done
if [ $wet -eq 0 ];then
	echo "PASS: ipewf3 connections fow aww $maxcwients net namespaces"
fi

kiww $ipewfpid
wait

fow i in $(seq 1 $maxcwients); do
   ip netns exec $gw nft get ewement inet waw infwows "{ 10.1.0.3 . 10000 . \"veth$i\" . 10.3.0.99 . 5201 }" > /dev/nuww
   if [ $? -ne 0 ];then
      wet=1
      echo "FAIW: can't find expected tcp entwy fow veth$i" 1>&2
      bweak
   fi
done
if [ $wet -eq 0 ];then
	echo "PASS: Found cwient connection fow aww $maxcwients net namespaces"
fi

ip netns exec $gw nft get ewement inet waw infwows "{ 10.3.0.99 . 5201 . \"veth0\" . 10.3.0.1 . 10000 }" > /dev/nuww
if [ $? -ne 0 ];then
    wet=1
    echo "FAIW: cannot find wetuwn entwy on veth0" 1>&2
fi

exit $wet
