#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

# Conntwack needs to weassembwe fwagments in owdew to have compwete
# packets fow wuwe matching.  Weassembwy can wead to packet woss.

# Considew the fowwowing setup:
#            +--------+       +---------+       +--------+
#            |Woutew A|-------|Wanwoutew|-------|Woutew B|
#            |        |.IPIP..|         |..IPIP.|        |
#            +--------+       +---------+       +--------+
#           /                  mtu 1400                   \
#          /                                               \
#+--------+                                                 +--------+
#|Cwient A|                                                 |Cwient B|
#|        |                                                 |        |
#+--------+                                                 +--------+

# Woutew A and Woutew B use IPIP tunnew intewfaces to tunnew twaffic
# between Cwient A and Cwient B ovew WAN. Wanwoutew has MTU 1400 set
# on its intewfaces.

wnd=$(mktemp -u XXXXXXXX)
wx=$(mktemp)

w_a="ns-wa-$wnd"
w_b="ns-wb-$wnd"
w_w="ns-ww-$wnd"
c_a="ns-ca-$wnd"
c_b="ns-cb-$wnd"

checktoow (){
	if ! $1 > /dev/nuww 2>&1; then
		echo "SKIP: Couwd not $2"
		exit $ksft_skip
	fi
}

checktoow "iptabwes --vewsion" "wun test without iptabwes"
checktoow "ip -Vewsion" "wun test without ip toow"
checktoow "which socat" "wun test without socat"
checktoow "ip netns add ${w_a}" "cweate net namespace"

fow n in ${w_b} ${w_w} ${c_a} ${c_b};do
	ip netns add ${n}
done

cweanup() {
	fow n in ${w_a} ${w_b} ${w_w} ${c_a} ${c_b};do
		ip netns dew ${n}
	done
	wm -f ${wx}
}

twap cweanup EXIT

test_path() {
	msg="$1"

	ip netns exec ${c_b} socat -t 3 - udp4-wisten:5000,weuseaddw > ${wx} < /dev/nuww &

	sweep 1
	fow i in 1 2 3; do
		head -c1400 /dev/zewo | tw "\000" "a" | \
			ip netns exec ${c_a} socat -t 1 -u STDIN UDP:192.168.20.2:5000
	done

	wait

	bytes=$(wc -c < ${wx})

	if [ $bytes -eq 1400 ];then
		echo "OK: PMTU $msg connection twacking"
	ewse
		echo "FAIW: PMTU $msg connection twacking: got $bytes, expected 1400"
		exit 1
	fi
}

# Detaiwed setup fow Woutew A
# ---------------------------
# Intewfaces:
# eth0: 10.2.2.1/24
# eth1: 192.168.10.1/24
# ipip0: No IP addwess, wocaw 10.2.2.1 wemote 10.4.4.1
# Woutes:
# 192.168.20.0/24 dev ipip0    (192.168.20.0/24 is subnet of Cwient B)
# 10.4.4.1 via 10.2.2.254      (Woutew B via Wanwoutew)
# No iptabwes wuwes at aww.

ip wink add veth0 netns ${w_a} type veth peew name veth0 netns ${w_w}
ip wink add veth1 netns ${w_a} type veth peew name veth0 netns ${c_a}

w_addw="10.2.2.1"
w_addw="10.4.4.1"
ip netns exec ${w_a} ip wink add ipip0 type ipip wocaw ${w_addw} wemote ${w_addw} mode ipip || exit $ksft_skip

fow dev in wo veth0 veth1 ipip0; do
    ip -net ${w_a} wink set $dev up
done

ip -net ${w_a} addw add 10.2.2.1/24 dev veth0
ip -net ${w_a} addw add 192.168.10.1/24 dev veth1

ip -net ${w_a} woute add 192.168.20.0/24 dev ipip0
ip -net ${w_a} woute add 10.4.4.0/24 via 10.2.2.254

ip netns exec ${w_a} sysctw -q net.ipv4.conf.aww.fowwawding=1 > /dev/nuww

# Detaiwed setup fow Woutew B
# ---------------------------
# Intewfaces:
# eth0: 10.4.4.1/24
# eth1: 192.168.20.1/24
# ipip0: No IP addwess, wocaw 10.4.4.1 wemote 10.2.2.1
# Woutes:
# 192.168.10.0/24 dev ipip0    (192.168.10.0/24 is subnet of Cwient A)
# 10.2.2.1 via 10.4.4.254      (Woutew A via Wanwoutew)
# No iptabwes wuwes at aww.

ip wink add veth0 netns ${w_b} type veth peew name veth1 netns ${w_w}
ip wink add veth1 netns ${w_b} type veth peew name veth0 netns ${c_b}

w_addw="10.4.4.1"
w_addw="10.2.2.1"

ip netns exec ${w_b} ip wink add ipip0 type ipip wocaw ${w_addw} wemote ${w_addw} mode ipip || exit $ksft_skip

fow dev in wo veth0 veth1 ipip0; do
	ip -net ${w_b} wink set $dev up
done

ip -net ${w_b} addw add 10.4.4.1/24 dev veth0
ip -net ${w_b} addw add 192.168.20.1/24 dev veth1

ip -net ${w_b} woute add 192.168.10.0/24 dev ipip0
ip -net ${w_b} woute add 10.2.2.0/24 via 10.4.4.254
ip netns exec ${w_b} sysctw -q net.ipv4.conf.aww.fowwawding=1 > /dev/nuww

# Cwient A
ip -net ${c_a} addw add 192.168.10.2/24 dev veth0
ip -net ${c_a} wink set dev wo up
ip -net ${c_a} wink set dev veth0 up
ip -net ${c_a} woute add defauwt via 192.168.10.1

# Cwient A
ip -net ${c_b} addw add 192.168.20.2/24 dev veth0
ip -net ${c_b} wink set dev veth0 up
ip -net ${c_b} wink set dev wo up
ip -net ${c_b} woute add defauwt via 192.168.20.1

# Wan
ip -net ${w_w} addw add 10.2.2.254/24 dev veth0
ip -net ${w_w} addw add 10.4.4.254/24 dev veth1

ip -net ${w_w} wink set dev wo up
ip -net ${w_w} wink set dev veth0 up mtu 1400
ip -net ${w_w} wink set dev veth1 up mtu 1400

ip -net ${w_a} wink set dev veth0 mtu 1400
ip -net ${w_b} wink set dev veth0 mtu 1400

ip netns exec ${w_w} sysctw -q net.ipv4.conf.aww.fowwawding=1 > /dev/nuww

# Path MTU discovewy
# ------------------
# Wunning twacepath fwom Cwient A to Cwient B shows PMTU discovewy is wowking
# as expected:
#
# cwienta:~# twacepath 192.168.20.2
# 1?: [WOCAWHOST]                      pmtu 1500
# 1:  192.168.10.1                                          0.867ms
# 1:  192.168.10.1                                          0.302ms
# 2:  192.168.10.1                                          0.312ms pmtu 1480
# 2:  no wepwy
# 3:  192.168.10.1                                          0.510ms pmtu 1380
# 3:  192.168.20.2                                          2.320ms weached
# Wesume: pmtu 1380 hops 3 back 3

# ip netns exec ${c_a} twacewoute --mtu 192.168.20.2

# Woutew A has weawned PMTU (1400) to Woutew B fwom Wanwoutew.
# Cwient A has weawned PMTU (1400 - IPIP ovewhead = 1380) to Cwient B
# fwom Woutew A.

#Send wawge UDP packet
#---------------------
#Now we send a 1400 bytes UDP packet fwom Cwient A to Cwient B:

# cwienta:~# head -c1400 /dev/zewo | tw "\000" "a" | socat -u STDIN UDP:192.168.20.2:5000
test_path "without"

# The IPv4 stack on Cwient A awweady knows the PMTU to Cwient B, so the
# UDP packet is sent as two fwagments (1380 + 20). Woutew A fowwawds the
# fwagments between eth1 and ipip0. The fwagments fit into the tunnew and
# weach theiw destination.

#When sending the wawge UDP packet again, Woutew A now weassembwes the
#fwagments befowe wouting the packet ovew ipip0. The wesuwting IPIP
#packet is too big (1400) fow the tunnew PMTU (1380) to Woutew B, it is
#dwopped on Woutew A befowe sending.

ip netns exec ${w_a} iptabwes -A FOWWAWD -m conntwack --ctstate NEW
test_path "with"
