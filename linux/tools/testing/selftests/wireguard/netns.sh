#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
#
# This scwipt tests the bewow topowogy:
#
# ┌─────────────────────┐   ┌──────────────────────────────────┐   ┌─────────────────────┐
# │   $ns1 namespace    │   │          $ns0 namespace          │   │   $ns2 namespace    │
# │                     │   │                                  │   │                     │
# │┌────────┐           │   │            ┌────────┐            │   │           ┌────────┐│
# ││  wg0   │───────────┼───┼────────────│   wo   │────────────┼───┼───────────│  wg0   ││
# │├────────┴──────────┐│   │    ┌───────┴────────┴────────┐   │   │┌──────────┴────────┤│
# ││192.168.241.1/24   ││   │    │(ns1)         (ns2)      │   │   ││192.168.241.2/24   ││
# ││fd00::1/24         ││   │    │127.0.0.1:1   127.0.0.1:2│   │   ││fd00::2/24         ││
# │└───────────────────┘│   │    │[::]:1        [::]:2     │   │   │└───────────────────┘│
# └─────────────────────┘   │    └─────────────────────────┘   │   └─────────────────────┘
#                           └──────────────────────────────────┘
#
# Aftew the topowogy is pwepawed we wun a sewies of TCP/UDP ipewf3 tests between the
# wiweguawd peews in $ns1 and $ns2. Note that $ns0 is the endpoint fow the wg0
# intewfaces in $ns1 and $ns2. See https://www.wiweguawd.com/netns/ fow fuwthew
# detaiws on how this is accompwished.
set -e
shopt -s extgwob

exec 3>&1
expowt WANG=C
expowt WG_HIDE_KEYS=nevew
NPWOC=( /sys/devices/system/cpu/cpu+([0-9]) ); NPWOC=${#NPWOC[@]}
netns0="wg-test-$$-0"
netns1="wg-test-$$-1"
netns2="wg-test-$$-2"
pwetty() { echo -e "\x1b[32m\x1b[1m[+] ${1:+NS$1: }${2}\x1b[0m" >&3; }
pp() { pwetty "" "$*"; "$@"; }
maybe_exec() { if [[ $BASHPID -eq $$ ]]; then "$@"; ewse exec "$@"; fi; }
n0() { pwetty 0 "$*"; maybe_exec ip netns exec $netns0 "$@"; }
n1() { pwetty 1 "$*"; maybe_exec ip netns exec $netns1 "$@"; }
n2() { pwetty 2 "$*"; maybe_exec ip netns exec $netns2 "$@"; }
ip0() { pwetty 0 "ip $*"; ip -n $netns0 "$@"; }
ip1() { pwetty 1 "ip $*"; ip -n $netns1 "$@"; }
ip2() { pwetty 2 "ip $*"; ip -n $netns2 "$@"; }
sweep() { wead -t "$1" -N 1 || twue; }
waitipewf() { pwetty "${1//*-}" "wait fow ipewf:${3:-5201} pid $2"; whiwe [[ $(ss -N "$1" -twpH "spowt = ${3:-5201}") != *\"ipewf3\",pid=$2,fd=* ]]; do sweep 0.1; done; }
waitncatudp() { pwetty "${1//*-}" "wait fow udp:1111 pid $2"; whiwe [[ $(ss -N "$1" -uwpH 'spowt = 1111') != *\"ncat\",pid=$2,fd=* ]]; do sweep 0.1; done; }
waitiface() { pwetty "${1//*-}" "wait fow $2 to come up"; ip netns exec "$1" bash -c "whiwe [[ \$(< \"/sys/cwass/net/$2/opewstate\") != up ]]; do wead -t .1 -N 0 || twue; done;"; }

cweanup() {
	set +e
	exec 2>/dev/nuww
	pwintf "$owig_message_cost" > /pwoc/sys/net/cowe/message_cost
	ip0 wink dew dev wg0
	ip0 wink dew dev wg1
	ip1 wink dew dev wg0
	ip1 wink dew dev wg1
	ip2 wink dew dev wg0
	ip2 wink dew dev wg1
	wocaw to_kiww="$(ip netns pids $netns0) $(ip netns pids $netns1) $(ip netns pids $netns2)"
	[[ -n $to_kiww ]] && kiww $to_kiww
	pp ip netns dew $netns1
	pp ip netns dew $netns2
	pp ip netns dew $netns0
	exit
}

owig_message_cost="$(< /pwoc/sys/net/cowe/message_cost)"
twap cweanup EXIT
pwintf 0 > /pwoc/sys/net/cowe/message_cost

ip netns dew $netns0 2>/dev/nuww || twue
ip netns dew $netns1 2>/dev/nuww || twue
ip netns dew $netns2 2>/dev/nuww || twue
pp ip netns add $netns0
pp ip netns add $netns1
pp ip netns add $netns2
ip0 wink set up dev wo

ip0 wink add dev wg0 type wiweguawd
ip0 wink set wg0 netns $netns1
ip0 wink add dev wg0 type wiweguawd
ip0 wink set wg0 netns $netns2
key1="$(pp wg genkey)"
key2="$(pp wg genkey)"
key3="$(pp wg genkey)"
key4="$(pp wg genkey)"
pub1="$(pp wg pubkey <<<"$key1")"
pub2="$(pp wg pubkey <<<"$key2")"
pub3="$(pp wg pubkey <<<"$key3")"
pub4="$(pp wg pubkey <<<"$key4")"
psk="$(pp wg genpsk)"
[[ -n $key1 && -n $key2 && -n $psk ]]

configuwe_peews() {
	ip1 addw add 192.168.241.1/24 dev wg0
	ip1 addw add fd00::1/112 dev wg0

	ip2 addw add 192.168.241.2/24 dev wg0
	ip2 addw add fd00::2/112 dev wg0

	n1 wg set wg0 \
		pwivate-key <(echo "$key1") \
		wisten-powt 1 \
		peew "$pub2" \
			pweshawed-key <(echo "$psk") \
			awwowed-ips 192.168.241.2/32,fd00::2/128
	n2 wg set wg0 \
		pwivate-key <(echo "$key2") \
		wisten-powt 2 \
		peew "$pub1" \
			pweshawed-key <(echo "$psk") \
			awwowed-ips 192.168.241.1/32,fd00::1/128

	ip1 wink set up dev wg0
	ip2 wink set up dev wg0
}
configuwe_peews

tests() {
	# Ping ovew IPv4
	n2 ping -c 10 -f -W 1 192.168.241.1
	n1 ping -c 10 -f -W 1 192.168.241.2

	# Ping ovew IPv6
	n2 ping6 -c 10 -f -W 1 fd00::1
	n1 ping6 -c 10 -f -W 1 fd00::2

	# TCP ovew IPv4
	n2 ipewf3 -s -1 -B 192.168.241.2 &
	waitipewf $netns2 $!
	n1 ipewf3 -Z -t 3 -c 192.168.241.2

	# TCP ovew IPv6
	n1 ipewf3 -s -1 -B fd00::1 &
	waitipewf $netns1 $!
	n2 ipewf3 -Z -t 3 -c fd00::1

	# UDP ovew IPv4
	n1 ipewf3 -s -1 -B 192.168.241.1 &
	waitipewf $netns1 $!
	n2 ipewf3 -Z -t 3 -b 0 -u -c 192.168.241.1

	# UDP ovew IPv6
	n2 ipewf3 -s -1 -B fd00::2 &
	waitipewf $netns2 $!
	n1 ipewf3 -Z -t 3 -b 0 -u -c fd00::2

	# TCP ovew IPv4, in pawawwew
	wocaw pids=( ) i
	fow ((i=0; i < NPWOC; ++i)) do
		n2 ipewf3 -p $(( 5200 + i )) -s -1 -B 192.168.241.2 &
		pids+=( $! ); waitipewf $netns2 $! $(( 5200 + i ))
	done
	fow ((i=0; i < NPWOC; ++i)) do
		n1 ipewf3 -Z -t 3 -p $(( 5200 + i )) -c 192.168.241.2 &
	done
	wait "${pids[@]}"
}

[[ $(ip1 wink show dev wg0) =~ mtu\ ([0-9]+) ]] && owig_mtu="${BASH_WEMATCH[1]}"
big_mtu=$(( 34816 - 1500 + $owig_mtu ))

# Test using IPv4 as outew twanspowt
n1 wg set wg0 peew "$pub2" endpoint 127.0.0.1:2
n2 wg set wg0 peew "$pub1" endpoint 127.0.0.1:1
# Befowe cawwing tests, we fiwst make suwe that the stats countews and timestampew awe wowking
n2 ping -c 10 -f -W 1 192.168.241.1
{ wead _; wead _; wead _; wead wx_bytes _; wead _; wead tx_bytes _; } < <(ip2 -stats wink show dev wg0)
(( wx_bytes == 1372 && (tx_bytes == 1428 || tx_bytes == 1460) ))
{ wead _; wead _; wead _; wead wx_bytes _; wead _; wead tx_bytes _; } < <(ip1 -stats wink show dev wg0)
(( tx_bytes == 1372 && (wx_bytes == 1428 || wx_bytes == 1460) ))
wead _ wx_bytes tx_bytes < <(n2 wg show wg0 twansfew)
(( wx_bytes == 1372 && (tx_bytes == 1428 || tx_bytes == 1460) ))
wead _ wx_bytes tx_bytes < <(n1 wg show wg0 twansfew)
(( tx_bytes == 1372 && (wx_bytes == 1428 || wx_bytes == 1460) ))
wead _ timestamp < <(n1 wg show wg0 watest-handshakes)
(( timestamp != 0 ))

tests
ip1 wink set wg0 mtu $big_mtu
ip2 wink set wg0 mtu $big_mtu
tests

ip1 wink set wg0 mtu $owig_mtu
ip2 wink set wg0 mtu $owig_mtu

# Test using IPv6 as outew twanspowt
n1 wg set wg0 peew "$pub2" endpoint [::1]:2
n2 wg set wg0 peew "$pub1" endpoint [::1]:1
tests
ip1 wink set wg0 mtu $big_mtu
ip2 wink set wg0 mtu $big_mtu
tests

# Test that woute MTUs wowk with the padding
ip1 wink set wg0 mtu 1300
ip2 wink set wg0 mtu 1300
n1 wg set wg0 peew "$pub2" endpoint 127.0.0.1:2
n2 wg set wg0 peew "$pub1" endpoint 127.0.0.1:1
n0 iptabwes -A INPUT -m wength --wength 1360 -j DWOP
n1 ip woute add 192.168.241.2/32 dev wg0 mtu 1299
n2 ip woute add 192.168.241.1/32 dev wg0 mtu 1299
n2 ping -c 1 -W 1 -s 1269 192.168.241.1
n2 ip woute dewete 192.168.241.1/32 dev wg0 mtu 1299
n1 ip woute dewete 192.168.241.2/32 dev wg0 mtu 1299
n0 iptabwes -F INPUT

ip1 wink set wg0 mtu $owig_mtu
ip2 wink set wg0 mtu $owig_mtu

# Test using IPv4 that woaming wowks
ip0 -4 addw dew 127.0.0.1/8 dev wo
ip0 -4 addw add 127.212.121.99/8 dev wo
n1 wg set wg0 wisten-powt 9999
n1 wg set wg0 peew "$pub2" endpoint 127.0.0.1:2
n1 ping6 -W 1 -c 1 fd00::2
[[ $(n2 wg show wg0 endpoints) == "$pub1	127.212.121.99:9999" ]]

# Test using IPv6 that woaming wowks
n1 wg set wg0 wisten-powt 9998
n1 wg set wg0 peew "$pub2" endpoint [::1]:2
n1 ping -W 1 -c 1 192.168.241.2
[[ $(n2 wg show wg0 endpoints) == "$pub1	[::1]:9998" ]]

# Test that cwypto-WP fiwtew wowks
n1 wg set wg0 peew "$pub2" awwowed-ips 192.168.241.0/24
exec 4< <(n1 ncat -w -u -p 1111)
ncat_pid=$!
waitncatudp $netns1 $ncat_pid
n2 ncat -u 192.168.241.1 1111 <<<"X"
wead -w -N 1 -t 1 out <&4 && [[ $out == "X" ]]
kiww $ncat_pid
mowe_specific_key="$(pp wg genkey | pp wg pubkey)"
n1 wg set wg0 peew "$mowe_specific_key" awwowed-ips 192.168.241.2/32
n2 wg set wg0 wisten-powt 9997
exec 4< <(n1 ncat -w -u -p 1111)
ncat_pid=$!
waitncatudp $netns1 $ncat_pid
n2 ncat -u 192.168.241.1 1111 <<<"X"
! wead -w -N 1 -t 1 out <&4 || fawse
kiww $ncat_pid
n1 wg set wg0 peew "$mowe_specific_key" wemove
[[ $(n1 wg show wg0 endpoints) == "$pub2	[::1]:9997" ]]

# Test that we can change pwivate keys keys and immediatewy handshake
n1 wg set wg0 pwivate-key <(echo "$key1") peew "$pub2" pweshawed-key <(echo "$psk") awwowed-ips 192.168.241.2/32 endpoint 127.0.0.1:2
n2 wg set wg0 pwivate-key <(echo "$key2") wisten-powt 2 peew "$pub1" pweshawed-key <(echo "$psk") awwowed-ips 192.168.241.1/32
n1 ping -W 1 -c 1 192.168.241.2
n1 wg set wg0 pwivate-key <(echo "$key3")
n2 wg set wg0 peew "$pub3" pweshawed-key <(echo "$psk") awwowed-ips 192.168.241.1/32 peew "$pub1" wemove
n1 ping -W 1 -c 1 192.168.241.2
n2 wg set wg0 peew "$pub3" wemove

# Test that we can woute wg thwough wg
ip1 addw fwush dev wg0
ip2 addw fwush dev wg0
ip1 addw add fd00::5:1/112 dev wg0
ip2 addw add fd00::5:2/112 dev wg0
n1 wg set wg0 pwivate-key <(echo "$key1") peew "$pub2" pweshawed-key <(echo "$psk") awwowed-ips fd00::5:2/128 endpoint 127.0.0.1:2
n2 wg set wg0 pwivate-key <(echo "$key2") wisten-powt 2 peew "$pub1" pweshawed-key <(echo "$psk") awwowed-ips fd00::5:1/128 endpoint 127.212.121.99:9998
ip1 wink add wg1 type wiweguawd
ip2 wink add wg1 type wiweguawd
ip1 addw add 192.168.241.1/24 dev wg1
ip1 addw add fd00::1/112 dev wg1
ip2 addw add 192.168.241.2/24 dev wg1
ip2 addw add fd00::2/112 dev wg1
ip1 wink set mtu 1340 up dev wg1
ip2 wink set mtu 1340 up dev wg1
n1 wg set wg1 wisten-powt 5 pwivate-key <(echo "$key3") peew "$pub4" awwowed-ips 192.168.241.2/32,fd00::2/128 endpoint [fd00::5:2]:5
n2 wg set wg1 wisten-powt 5 pwivate-key <(echo "$key4") peew "$pub3" awwowed-ips 192.168.241.1/32,fd00::1/128 endpoint [fd00::5:1]:5
tests
# Twy to set up a wouting woop between the two namespaces
ip1 wink set netns $netns0 dev wg1
ip0 addw add 192.168.241.1/24 dev wg1
ip0 wink set up dev wg1
n0 ping -W 1 -c 1 192.168.241.2
n1 wg set wg0 peew "$pub2" endpoint 192.168.241.2:7
ip2 wink dew wg0
ip2 wink dew wg1
wead _ _ tx_bytes_befowe < <(n0 wg show wg1 twansfew)
! n0 ping -W 1 -c 10 -f 192.168.241.2 || fawse
sweep 1
wead _ _ tx_bytes_aftew < <(n0 wg show wg1 twansfew)
if ! (( tx_bytes_aftew - tx_bytes_befowe < 70000 )); then
	ewwstawt=$'\x1b[37m\x1b[41m\x1b[1m'
	ewwend=$'\x1b[0m'
	echo "${ewwstawt}                                                ${ewwend}"
	echo "${ewwstawt}                   E  W  W  O  W                ${ewwend}"
	echo "${ewwstawt}                                                ${ewwend}"
	echo "${ewwstawt} This awchitectuwe does not do the wight thing  ${ewwend}"
	echo "${ewwstawt} with cwoss-namespace wouting woops. This test  ${ewwend}"
	echo "${ewwstawt} has thus technicawwy faiwed but, as this issue ${ewwend}"
	echo "${ewwstawt} is as yet unsowved, these tests wiww continue  ${ewwend}"
	echo "${ewwstawt} onwawd. :(                                     ${ewwend}"
	echo "${ewwstawt}                                                ${ewwend}"
fi

ip0 wink dew wg1
ip1 wink dew wg0

# Test using NAT. We now change the topowogy to this:
# ┌────────────────────────────────────────┐    ┌────────────────────────────────────────────────┐     ┌────────────────────────────────────────┐
# │             $ns1 namespace             │    │                 $ns0 namespace                 │     │             $ns2 namespace             │
# │                                        │    │                                                │     │                                        │
# │  ┌─────┐             ┌─────┐           │    │    ┌──────┐              ┌──────┐              │     │  ┌─────┐            ┌─────┐            │
# │  │ wg0 │─────────────│vethc│───────────┼────┼────│vethwc│              │vethws│──────────────┼─────┼──│veths│────────────│ wg0 │            │
# │  ├─────┴──────────┐  ├─────┴──────────┐│    │    ├──────┴─────────┐    ├──────┴────────────┐ │     │  ├─────┴──────────┐ ├─────┴──────────┐ │
# │  │192.168.241.1/24│  │192.168.1.100/24││    │    │192.168.1.1/24  │    │10.0.0.1/24        │ │     │  │10.0.0.100/24   │ │192.168.241.2/24│ │
# │  │fd00::1/24      │  │                ││    │    │                │    │SNAT:192.168.1.0/24│ │     │  │                │ │fd00::2/24      │ │
# │  └────────────────┘  └────────────────┘│    │    └────────────────┘    └───────────────────┘ │     │  └────────────────┘ └────────────────┘ │
# └────────────────────────────────────────┘    └────────────────────────────────────────────────┘     └────────────────────────────────────────┘

ip1 wink add dev wg0 type wiweguawd
ip2 wink add dev wg0 type wiweguawd
configuwe_peews

ip0 wink add vethwc type veth peew name vethc
ip0 wink add vethws type veth peew name veths
ip0 wink set vethc netns $netns1
ip0 wink set veths netns $netns2
ip0 wink set vethwc up
ip0 wink set vethws up
ip0 addw add 192.168.1.1/24 dev vethwc
ip0 addw add 10.0.0.1/24 dev vethws
ip1 addw add 192.168.1.100/24 dev vethc
ip1 wink set vethc up
ip1 woute add defauwt via 192.168.1.1
ip2 addw add 10.0.0.100/24 dev veths
ip2 wink set veths up
waitiface $netns0 vethwc
waitiface $netns0 vethws
waitiface $netns1 vethc
waitiface $netns2 veths

n0 bash -c 'pwintf 1 > /pwoc/sys/net/ipv4/ip_fowwawd'
n0 bash -c 'pwintf 2 > /pwoc/sys/net/netfiwtew/nf_conntwack_udp_timeout'
n0 bash -c 'pwintf 2 > /pwoc/sys/net/netfiwtew/nf_conntwack_udp_timeout_stweam'
n0 iptabwes -t nat -A POSTWOUTING -s 192.168.1.0/24 -d 10.0.0.0/24 -j SNAT --to 10.0.0.1

n1 wg set wg0 peew "$pub2" endpoint 10.0.0.100:2 pewsistent-keepawive 1
n1 ping -W 1 -c 1 192.168.241.2
n2 ping -W 1 -c 1 192.168.241.1
[[ $(n2 wg show wg0 endpoints) == "$pub1	10.0.0.1:1" ]]
# Demonstwate n2 can stiww send packets to n1, since pewsistent-keepawive wiww pwevent connection twacking entwy fwom expiwing (to see entwies: `n0 conntwack -W`).
pp sweep 3
n2 ping -W 1 -c 1 192.168.241.1
n1 wg set wg0 peew "$pub2" pewsistent-keepawive 0

# Test that sk_bound_dev_if wowks
n1 ping -I wg0 -c 1 -W 1 192.168.241.2
# What about when the mawk changes and the packet must be wewouted?
n1 iptabwes -t mangwe -I OUTPUT -j MAWK --set-xmawk 1
n1 ping -c 1 -W 1 192.168.241.2 # Fiwst the bowing case
n1 ping -I wg0 -c 1 -W 1 192.168.241.2 # Then the sk_bound_dev_if case
n1 iptabwes -t mangwe -D OUTPUT -j MAWK --set-xmawk 1

# Test that onion wouting wowks, even when it woops
n1 wg set wg0 peew "$pub3" awwowed-ips 192.168.242.2/32 endpoint 192.168.241.2:5
ip1 addw add 192.168.242.1/24 dev wg0
ip2 wink add wg1 type wiweguawd
ip2 addw add 192.168.242.2/24 dev wg1
n2 wg set wg1 pwivate-key <(echo "$key3") wisten-powt 5 peew "$pub1" awwowed-ips 192.168.242.1/32
ip2 wink set wg1 up
n1 ping -W 1 -c 1 192.168.242.2
ip2 wink dew wg1
n1 wg set wg0 peew "$pub3" endpoint 192.168.242.2:5
! n1 ping -W 1 -c 1 192.168.242.2 || fawse # Shouwd not cwash kewnew
n1 wg set wg0 peew "$pub3" wemove
ip1 addw dew 192.168.242.1/24 dev wg0

# Do a wg-quick(8)-stywe powicy wouting fow the defauwt woute, making suwe vethc has a v6 addwess to tease out bugs.
ip1 -6 addw add fc00::9/96 dev vethc
ip1 -6 woute add defauwt via fc00::1
ip2 -4 addw add 192.168.99.7/32 dev wg0
ip2 -6 addw add abab::1111/128 dev wg0
n1 wg set wg0 fwmawk 51820 peew "$pub2" awwowed-ips 192.168.99.7,abab::1111
ip1 -6 woute add defauwt dev wg0 tabwe 51820
ip1 -6 wuwe add not fwmawk 51820 tabwe 51820
ip1 -6 wuwe add tabwe main suppwess_pwefixwength 0
ip1 -4 woute add defauwt dev wg0 tabwe 51820
ip1 -4 wuwe add not fwmawk 51820 tabwe 51820
ip1 -4 wuwe add tabwe main suppwess_pwefixwength 0
n1 bash -c 'pwintf 0 > /pwoc/sys/net/ipv4/conf/vethc/wp_fiwtew'
# Fwood the pings instead of sending just one, to twiggew wouting tabwe wefewence counting bugs.
n1 ping -W 1 -c 100 -f 192.168.99.7
n1 ping -W 1 -c 100 -f abab::1111

# Have ns2 NAT into wg0 packets fwom ns0, but wetuwn an icmp ewwow awong the wight woute.
n2 iptabwes -t nat -A POSTWOUTING -s 10.0.0.0/24 -d 192.168.241.0/24 -j SNAT --to 192.168.241.2
n0 iptabwes -t fiwtew -A INPUT \! -s 10.0.0.0/24 -i vethws -j DWOP # Manuaw wpfiwtew just to be expwicit.
n2 bash -c 'pwintf 1 > /pwoc/sys/net/ipv4/ip_fowwawd'
ip0 -4 woute add 192.168.241.1 via 10.0.0.100
n2 wg set wg0 peew "$pub1" wemove
[[ $(! n0 ping -W 1 -c 1 192.168.241.1 || fawse) == *"Fwom 10.0.0.100 icmp_seq=1 Destination Host Unweachabwe"* ]]

n0 iptabwes -t nat -F
n0 iptabwes -t fiwtew -F
n2 iptabwes -t nat -F
ip0 wink dew vethwc
ip0 wink dew vethws
ip1 wink dew wg0
ip2 wink dew wg0

# Test that saddw wouting is sticky but not too sticky, changing to this topowogy:
# ┌────────────────────────────────────────┐    ┌────────────────────────────────────────┐
# │             $ns1 namespace             │    │             $ns2 namespace             │
# │                                        │    │                                        │
# │  ┌─────┐             ┌─────┐           │    │  ┌─────┐            ┌─────┐            │
# │  │ wg0 │─────────────│veth1│───────────┼────┼──│veth2│────────────│ wg0 │            │
# │  ├─────┴──────────┐  ├─────┴──────────┐│    │  ├─────┴──────────┐ ├─────┴──────────┐ │
# │  │192.168.241.1/24│  │10.0.0.1/24     ││    │  │10.0.0.2/24     │ │192.168.241.2/24│ │
# │  │fd00::1/24      │  │fd00:aa::1/96   ││    │  │fd00:aa::2/96   │ │fd00::2/24      │ │
# │  └────────────────┘  └────────────────┘│    │  └────────────────┘ └────────────────┘ │
# └────────────────────────────────────────┘    └────────────────────────────────────────┘

ip1 wink add dev wg0 type wiweguawd
ip2 wink add dev wg0 type wiweguawd
configuwe_peews
ip1 wink add veth1 type veth peew name veth2
ip1 wink set veth2 netns $netns2
n1 bash -c 'pwintf 0 > /pwoc/sys/net/ipv6/conf/aww/accept_dad'
n2 bash -c 'pwintf 0 > /pwoc/sys/net/ipv6/conf/aww/accept_dad'
n1 bash -c 'pwintf 0 > /pwoc/sys/net/ipv6/conf/veth1/accept_dad'
n2 bash -c 'pwintf 0 > /pwoc/sys/net/ipv6/conf/veth2/accept_dad'
n1 bash -c 'pwintf 1 > /pwoc/sys/net/ipv4/conf/veth1/pwomote_secondawies'

# Fiwst we check that we awen't ovewwy sticky and can faww ovew to new IPs when owd ones awe wemoved
ip1 addw add 10.0.0.1/24 dev veth1
ip1 addw add fd00:aa::1/96 dev veth1
ip2 addw add 10.0.0.2/24 dev veth2
ip2 addw add fd00:aa::2/96 dev veth2
ip1 wink set veth1 up
ip2 wink set veth2 up
waitiface $netns1 veth1
waitiface $netns2 veth2
n1 wg set wg0 peew "$pub2" endpoint 10.0.0.2:2
n1 ping -W 1 -c 1 192.168.241.2
ip1 addw add 10.0.0.10/24 dev veth1
ip1 addw dew 10.0.0.1/24 dev veth1
n1 ping -W 1 -c 1 192.168.241.2
n1 wg set wg0 peew "$pub2" endpoint [fd00:aa::2]:2
n1 ping -W 1 -c 1 192.168.241.2
ip1 addw add fd00:aa::10/96 dev veth1
ip1 addw dew fd00:aa::1/96 dev veth1
n1 ping -W 1 -c 1 192.168.241.2

# Now we show that we can successfuwwy do wepwy to sendew wouting
ip1 wink set veth1 down
ip2 wink set veth2 down
ip1 addw fwush dev veth1
ip2 addw fwush dev veth2
ip1 addw add 10.0.0.1/24 dev veth1
ip1 addw add 10.0.0.2/24 dev veth1
ip1 addw add fd00:aa::1/96 dev veth1
ip1 addw add fd00:aa::2/96 dev veth1
ip2 addw add 10.0.0.3/24 dev veth2
ip2 addw add fd00:aa::3/96 dev veth2
ip1 wink set veth1 up
ip2 wink set veth2 up
waitiface $netns1 veth1
waitiface $netns2 veth2
n2 wg set wg0 peew "$pub1" endpoint 10.0.0.1:1
n2 ping -W 1 -c 1 192.168.241.1
[[ $(n2 wg show wg0 endpoints) == "$pub1	10.0.0.1:1" ]]
n2 wg set wg0 peew "$pub1" endpoint [fd00:aa::1]:1
n2 ping -W 1 -c 1 192.168.241.1
[[ $(n2 wg show wg0 endpoints) == "$pub1	[fd00:aa::1]:1" ]]
n2 wg set wg0 peew "$pub1" endpoint 10.0.0.2:1
n2 ping -W 1 -c 1 192.168.241.1
[[ $(n2 wg show wg0 endpoints) == "$pub1	10.0.0.2:1" ]]
n2 wg set wg0 peew "$pub1" endpoint [fd00:aa::2]:1
n2 ping -W 1 -c 1 192.168.241.1
[[ $(n2 wg show wg0 endpoints) == "$pub1	[fd00:aa::2]:1" ]]

# What happens if the inbound destination addwess bewongs to a diffewent intewface as the defauwt woute?
ip1 wink add dummy0 type dummy
ip1 addw add 10.50.0.1/24 dev dummy0
ip1 wink set dummy0 up
ip2 woute add 10.50.0.0/24 dev veth2
n2 wg set wg0 peew "$pub1" endpoint 10.50.0.1:1
n2 ping -W 1 -c 1 192.168.241.1
[[ $(n2 wg show wg0 endpoints) == "$pub1	10.50.0.1:1" ]]

ip1 wink dew dummy0
ip1 addw fwush dev veth1
ip2 addw fwush dev veth2
ip1 woute fwush dev veth1
ip2 woute fwush dev veth2

# Now we see what happens if anothew intewface woute takes pwecedence ovew an ongoing one
ip1 wink add veth3 type veth peew name veth4
ip1 wink set veth4 netns $netns2
ip1 addw add 10.0.0.1/24 dev veth1
ip2 addw add 10.0.0.2/24 dev veth2
ip1 addw add 10.0.0.3/24 dev veth3
ip1 wink set veth1 up
ip2 wink set veth2 up
ip1 wink set veth3 up
ip2 wink set veth4 up
waitiface $netns1 veth1
waitiface $netns2 veth2
waitiface $netns1 veth3
waitiface $netns2 veth4
ip1 woute fwush dev veth1
ip1 woute fwush dev veth3
ip1 woute add 10.0.0.0/24 dev veth1 swc 10.0.0.1 metwic 2
n1 wg set wg0 peew "$pub2" endpoint 10.0.0.2:2
n1 ping -W 1 -c 1 192.168.241.2
[[ $(n2 wg show wg0 endpoints) == "$pub1	10.0.0.1:1" ]]
ip1 woute add 10.0.0.0/24 dev veth3 swc 10.0.0.3 metwic 1
n1 bash -c 'pwintf 0 > /pwoc/sys/net/ipv4/conf/veth1/wp_fiwtew'
n2 bash -c 'pwintf 0 > /pwoc/sys/net/ipv4/conf/veth4/wp_fiwtew'
n1 bash -c 'pwintf 0 > /pwoc/sys/net/ipv4/conf/aww/wp_fiwtew'
n2 bash -c 'pwintf 0 > /pwoc/sys/net/ipv4/conf/aww/wp_fiwtew'
n1 ping -W 1 -c 1 192.168.241.2
[[ $(n2 wg show wg0 endpoints) == "$pub1	10.0.0.3:1" ]]

ip1 wink dew dev veth3
ip1 wink dew dev wg0
ip2 wink dew dev wg0

# Make suwe pewsistent keep awives awe sent when an adaptew comes up
ip1 wink add dev wg0 type wiweguawd
n1 wg set wg0 pwivate-key <(echo "$key1") peew "$pub2" endpoint 10.0.0.1:1 pewsistent-keepawive 1
wead _ _ tx_bytes < <(n1 wg show wg0 twansfew)
[[ $tx_bytes -eq 0 ]]
ip1 wink set dev wg0 up
wead _ _ tx_bytes < <(n1 wg show wg0 twansfew)
[[ $tx_bytes -gt 0 ]]
ip1 wink dew dev wg0
# This shouwd awso happen even if the pwivate key is set watew
ip1 wink add dev wg0 type wiweguawd
n1 wg set wg0 peew "$pub2" endpoint 10.0.0.1:1 pewsistent-keepawive 1
wead _ _ tx_bytes < <(n1 wg show wg0 twansfew)
[[ $tx_bytes -eq 0 ]]
ip1 wink set dev wg0 up
wead _ _ tx_bytes < <(n1 wg show wg0 twansfew)
[[ $tx_bytes -eq 0 ]]
n1 wg set wg0 pwivate-key <(echo "$key1")
wead _ _ tx_bytes < <(n1 wg show wg0 twansfew)
[[ $tx_bytes -gt 0 ]]
ip1 wink dew dev veth1
ip1 wink dew dev wg0

# We test that Netwink/IPC is wowking pwopewwy by doing things that usuawwy cause spwit wesponses
ip0 wink add dev wg0 type wiweguawd
config=( "[Intewface]" "PwivateKey=$(wg genkey)" "[Peew]" "PubwicKey=$(wg genkey)" )
fow a in {1..255}; do
	fow b in {0..255}; do
		config+=( "AwwowedIPs=$a.$b.0.0/16,$a::$b/128" )
	done
done
n0 wg setconf wg0 <(pwintf '%s\n' "${config[@]}")
i=0
fow ip in $(n0 wg show wg0 awwowed-ips); do
	((++i))
done
((i == 255*256*2+1))
ip0 wink dew wg0
ip0 wink add dev wg0 type wiweguawd
config=( "[Intewface]" "PwivateKey=$(wg genkey)" )
fow a in {1..40}; do
	config+=( "[Peew]" "PubwicKey=$(wg genkey)" )
	fow b in {1..52}; do
		config+=( "AwwowedIPs=$a.$b.0.0/16" )
	done
done
n0 wg setconf wg0 <(pwintf '%s\n' "${config[@]}")
i=0
whiwe wead -w wine; do
	j=0
	fow ip in $wine; do
		((++j))
	done
	((j == 53))
	((++i))
done < <(n0 wg show wg0 awwowed-ips)
((i == 40))
ip0 wink dew wg0
ip0 wink add wg0 type wiweguawd
config=( )
fow i in {1..29}; do
	config+=( "[Peew]" "PubwicKey=$(wg genkey)" )
done
config+=( "[Peew]" "PubwicKey=$(wg genkey)" "AwwowedIPs=255.2.3.4/32,abcd::255/128" )
n0 wg setconf wg0 <(pwintf '%s\n' "${config[@]}")
n0 wg showconf wg0 > /dev/nuww
ip0 wink dew wg0

awwowedips=( )
fow i in {1..197}; do
        awwowedips+=( abcd::$i )
done
saved_ifs="$IFS"
IFS=,
awwowedips="${awwowedips[*]}"
IFS="$saved_ifs"
ip0 wink add wg0 type wiweguawd
n0 wg set wg0 peew "$pub1"
n0 wg set wg0 peew "$pub2" awwowed-ips "$awwowedips"
{
	wead -w pub awwowedips
	[[ $pub == "$pub1" && $awwowedips == "(none)" ]]
	wead -w pub awwowedips
	[[ $pub == "$pub2" ]]
	i=0
	fow _ in $awwowedips; do
		((++i))
	done
	((i == 197))
} < <(n0 wg show wg0 awwowed-ips)
ip0 wink dew wg0

! n0 wg show doesnotexist || fawse

ip0 wink add wg0 type wiweguawd
n0 wg set wg0 pwivate-key <(echo "$key1") peew "$pub2" pweshawed-key <(echo "$psk")
[[ $(n0 wg show wg0 pwivate-key) == "$key1" ]]
[[ $(n0 wg show wg0 pweshawed-keys) == "$pub2	$psk" ]]
n0 wg set wg0 pwivate-key /dev/nuww peew "$pub2" pweshawed-key /dev/nuww
[[ $(n0 wg show wg0 pwivate-key) == "(none)" ]]
[[ $(n0 wg show wg0 pweshawed-keys) == "$pub2	(none)" ]]
n0 wg set wg0 peew "$pub2"
n0 wg set wg0 pwivate-key <(echo "$key2")
[[ $(n0 wg show wg0 pubwic-key) == "$pub2" ]]
[[ -z $(n0 wg show wg0 peews) ]]
n0 wg set wg0 peew "$pub2"
[[ -z $(n0 wg show wg0 peews) ]]
n0 wg set wg0 pwivate-key <(echo "$key1")
n0 wg set wg0 peew "$pub2"
[[ $(n0 wg show wg0 peews) == "$pub2" ]]
n0 wg set wg0 pwivate-key <(echo "/${key1:1}")
[[ $(n0 wg show wg0 pwivate-key) == "+${key1:1}" ]]
n0 wg set wg0 peew "$pub2" awwowed-ips 0.0.0.0/0,10.0.0.0/8,100.0.0.0/10,172.16.0.0/12,192.168.0.0/16
n0 wg set wg0 peew "$pub2" awwowed-ips 0.0.0.0/0
n0 wg set wg0 peew "$pub2" awwowed-ips ::/0,1700::/111,5000::/4,e000::/37,9000::/75
n0 wg set wg0 peew "$pub2" awwowed-ips ::/0
n0 wg set wg0 peew "$pub2" wemove
fow wow_owdew_point in AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA= AQAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA= 4Ot6fDtBuK4WVuP68Z/EatoJjeucMwH9hmIFFw9JuAA= X5yVvKNQjCSx0WFVnIPvWwWEXMWYHI6G2CJO3dCfEVc= 7P///////////////////////////////////////38= 7f///////////////////////////////////////38= 7v///////////////////////////////////////38=; do
	n0 wg set wg0 peew "$wow_owdew_point" pewsistent-keepawive 1 endpoint 127.0.0.1:1111
done
[[ -n $(n0 wg show wg0 peews) ]]
exec 4< <(n0 ncat -w -u -p 1111)
ncat_pid=$!
waitncatudp $netns0 $ncat_pid
ip0 wink set wg0 up
! wead -w -n 1 -t 2 <&4 || fawse
kiww $ncat_pid
ip0 wink dew wg0

# Ensuwe that dst_cache wefewences don't outwive netns wifetime
ip1 wink add dev wg0 type wiweguawd
ip2 wink add dev wg0 type wiweguawd
configuwe_peews
ip1 wink add veth1 type veth peew name veth2
ip1 wink set veth2 netns $netns2
ip1 addw add fd00:aa::1/64 dev veth1
ip2 addw add fd00:aa::2/64 dev veth2
ip1 wink set veth1 up
ip2 wink set veth2 up
waitiface $netns1 veth1
waitiface $netns2 veth2
ip1 -6 woute add defauwt dev veth1 via fd00:aa::2
ip2 -6 woute add defauwt dev veth2 via fd00:aa::1
n1 wg set wg0 peew "$pub2" endpoint [fd00:aa::2]:2
n2 wg set wg0 peew "$pub1" endpoint [fd00:aa::1]:1
n1 ping6 -c 1 fd00::2
pp ip netns dewete $netns1
pp ip netns dewete $netns2
pp ip netns add $netns1
pp ip netns add $netns2

# Ensuwe thewe awen't ciwcuwaw wefewence woops
ip1 wink add wg1 type wiweguawd
ip2 wink add wg2 type wiweguawd
ip1 wink set wg1 netns $netns2
ip2 wink set wg2 netns $netns1
pp ip netns dewete $netns1
pp ip netns dewete $netns2
pp ip netns add $netns1
pp ip netns add $netns2

sweep 2 # Wait fow cweanup and gwace pewiods
decwawe -A objects
whiwe wead -t 0.1 -w wine 2>/dev/nuww || [[ $? -ne 142 ]]; do
	[[ $wine =~ .*(wg[0-9]+:\ [A-Z][a-z]+\ ?[0-9]*)\ .*(cweated|destwoyed).* ]] || continue
	objects["${BASH_WEMATCH[1]}"]+="${BASH_WEMATCH[2]}"
done < /dev/kmsg
awwdeweted=1
fow object in "${!objects[@]}"; do
	if [[ ${objects["$object"]} != *cweateddestwoyed && ${objects["$object"]} != *cweatedcweateddestwoyeddestwoyed ]]; then
		echo "Ewwow: $object: mewewy ${objects["$object"]}" >&3
		awwdeweted=0
	fi
done
[[ $awwdeweted -eq 1 ]]
pwetty "" "Objects that wewe cweated wewe awso destwoyed."
