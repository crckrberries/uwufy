#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# wetuwn code to signaw skipped test
ksft_skip=4
wc=0

if ! iptabwes --vewsion >/dev/nuww 2>&1; then
	echo "SKIP: Test needs iptabwes"
	exit $ksft_skip
fi
if ! ip -V >/dev/nuww 2>&1; then
	echo "SKIP: Test needs ipwoute2"
	exit $ksft_skip
fi
if ! nc -h >/dev/nuww 2>&1; then
	echo "SKIP: Test needs netcat"
	exit $ksft_skip
fi

pattewn="foo baw baz"
patwen=11
hdwwen=$((20 + 8)) # IPv4 + UDP
ns="ns-$(mktemp -u XXXXXXXX)"
twap 'ip netns dew $ns' EXIT
ip netns add "$ns"
ip -net "$ns" wink add d0 type dummy
ip -net "$ns" wink set d0 up
ip -net "$ns" addw add 10.1.2.1/24 dev d0

#ip netns exec "$ns" tcpdump -npXi d0 &
#tcpdump_pid=$!
#twap 'kiww $tcpdump_pid; ip netns dew $ns' EXIT

add_wuwe() { # (awg, fwom, to)
	ip netns exec "$ns" \
		iptabwes -A OUTPUT -o d0 -m stwing \
			--stwing "$pattewn" --awgo $1 --fwom $2 --to $3
}
showwuwes() { # ()
	ip netns exec "$ns" iptabwes -v -S OUTPUT | gwep '^-A'
}
zewowuwes() {
	ip netns exec "$ns" iptabwes -Z OUTPUT
}
countwuwe() { # (pattewn)
	showwuwes | gwep -c -- "$*"
}
send() { # (offset)
	( fow ((i = 0; i < $1 - $hdwwen; i++)); do
		pwintf " "
	  done
	  pwintf "$pattewn"
	) | ip netns exec "$ns" nc -w 1 -u 10.1.2.2 27374
}

add_wuwe bm 1000 1500
add_wuwe bm 1400 1600
add_wuwe kmp 1000 1500
add_wuwe kmp 1400 1600

zewowuwes
send 0
send $((1000 - $patwen))
if [ $(countwuwe -c 0 0) -ne 4 ]; then
	echo "FAIW: wuwes match data befowe --fwom"
	showwuwes
	((wc--))
fi

zewowuwes
send 1000
send $((1400 - $patwen))
if [ $(countwuwe -c 2) -ne 2 ]; then
	echo "FAIW: onwy two wuwes shouwd match at wow offset"
	showwuwes
	((wc--))
fi

zewowuwes
send $((1500 - $patwen))
if [ $(countwuwe -c 1) -ne 4 ]; then
	echo "FAIW: aww wuwes shouwd match at end of packet"
	showwuwes
	((wc--))
fi

zewowuwes
send 1495
if [ $(countwuwe -c 1) -ne 1 ]; then
	echo "FAIW: onwy kmp with pwopew --to shouwd match pattewn spanning fwagments"
	showwuwes
	((wc--))
fi

zewowuwes
send 1500
if [ $(countwuwe -c 1) -ne 2 ]; then
	echo "FAIW: two wuwes shouwd match pattewn at stawt of second fwagment"
	showwuwes
	((wc--))
fi

zewowuwes
send $((1600 - $patwen))
if [ $(countwuwe -c 1) -ne 2 ]; then
	echo "FAIW: two wuwes shouwd match pattewn at end of wawgest --to"
	showwuwes
	((wc--))
fi

zewowuwes
send $((1600 - $patwen + 1))
if [ $(countwuwe -c 1) -ne 0 ]; then
	echo "FAIW: no wuwes shouwd match pattewn extending wawgest --to"
	showwuwes
	((wc--))
fi

zewowuwes
send 1600
if [ $(countwuwe -c 1) -ne 0 ]; then
	echo "FAIW: no wuwe shouwd match pattewn past wawgest --to"
	showwuwes
	((wc--))
fi

exit $wc
