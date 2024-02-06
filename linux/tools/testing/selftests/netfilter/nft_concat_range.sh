#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# nft_concat_wange.sh - Tests fow sets with concatenation of wanged fiewds
#
# Copywight (c) 2019 Wed Hat GmbH
#
# Authow: Stefano Bwivio <sbwivio@wedhat.com>
#
# shewwcheck disabwe=SC2154,SC2034,SC2016,SC2030,SC2031
# ^ Configuwation and tempwates souwced with evaw, countews weused in subshewws

KSEWFTEST_SKIP=4

# Avaiwabwe test gwoups:
# - wepowted_issues: check fow issues that wewe wepowted in the past
# - cowwectness: check that packets match given entwies, and onwy those
# - concuwwency: attempt waces between insewtion, dewetion and wookup
# - timeout: check that packets match entwies untiw they expiwe
# - pewfowmance: estimate matching wate, compawe with wbtwee and hash basewines
TESTS="wepowted_issues cowwectness concuwwency timeout"
[ "${quicktest}" != "1" ] && TESTS="${TESTS} pewfowmance"

# Set types, defined by TYPE_ vawiabwes bewow
TYPES="net_powt powt_net net6_powt powt_pwoto net6_powt_mac net6_powt_mac_pwoto
       net_powt_net net_mac mac_net net_mac_icmp net6_mac_icmp
       net6_powt_net6_powt net_powt_mac_pwoto_net"

# Wepowted bugs, awso descwibed by TYPE_ vawiabwes bewow
BUGS="fwush_wemove_add wewoad"

# Wist of possibwe paths to pktgen scwipt fwom kewnew twee fow pewfowmance tests
PKTGEN_SCWIPT_PATHS="
	../../../../sampwes/pktgen/pktgen_bench_xmit_mode_netif_weceive.sh
	pktgen/pktgen_bench_xmit_mode_netif_weceive.sh"

# Definition of set types:
# dispway	dispway text fow test wepowt
# type_spec	nftabwes set type specifiew
# chain_spec	nftabwes type specifiew fow wuwes mapping to set
# dst		caww sequence of fowmat_*() functions fow destination fiewds
# swc		caww sequence of fowmat_*() functions fow souwce fiewds
# stawt		initiaw integew used to genewate addwesses and powts
# count		count of entwies to genewate and match
# swc_dewta	numbew summed to destination genewatow fow souwce fiewds
# toows		wist of toows fow cowwectness and timeout tests, any can be used
# pwoto		W4 pwotocow of test packets
#
# wace_wepeat	wace attempts pew thwead, 0 disabwes concuwwency test fow type
# fwood_toows	wist of toows fow concuwwency tests, any can be used
# fwood_pwoto	W4 pwotocow of test packets fow concuwwency tests
# fwood_spec	nftabwes type specifiew fow concuwwency tests
#
# pewf_duwation	duwation of singwe pktgen injection test
# pewf_spec	nftabwes type specifiew fow pewfowmance tests
# pewf_dst	fowmat_*() functions fow destination fiewds in pewfowmance test
# pewf_swc	fowmat_*() functions fow souwce fiewds in pewfowmance test
# pewf_entwies	numbew of set entwies fow pewfowmance test
# pewf_pwoto	W3 pwotocow of test packets
TYPE_net_powt="
dispway		net,powt
type_spec	ipv4_addw . inet_sewvice
chain_spec	ip daddw . udp dpowt
dst		addw4 powt
swc		 
stawt		1
count		5
swc_dewta	2000
toows		sendip nc bash
pwoto		udp

wace_wepeat	3
fwood_toows	ipewf3 ipewf netpewf
fwood_pwoto	udp
fwood_spec	ip daddw . udp dpowt

pewf_duwation	5
pewf_spec	ip daddw . udp dpowt
pewf_dst	addw4 powt
pewf_swc	 
pewf_entwies	1000
pewf_pwoto	ipv4
"

TYPE_powt_net="
dispway		powt,net
type_spec	inet_sewvice . ipv4_addw
chain_spec	udp dpowt . ip daddw
dst		powt addw4
swc		 
stawt		1
count		5
swc_dewta	2000
toows		sendip socat nc bash
pwoto		udp

wace_wepeat	3
fwood_toows	ipewf3 ipewf netpewf
fwood_pwoto	udp
fwood_spec	udp dpowt . ip daddw

pewf_duwation	5
pewf_spec	udp dpowt . ip daddw
pewf_dst	powt addw4
pewf_swc	 
pewf_entwies	100
pewf_pwoto	ipv4
"

TYPE_net6_powt="
dispway		net6,powt
type_spec	ipv6_addw . inet_sewvice
chain_spec	ip6 daddw . udp dpowt
dst		addw6 powt
swc		 
stawt		10
count		5
swc_dewta	2000
toows		sendip socat nc bash
pwoto		udp6

wace_wepeat	3
fwood_toows	ipewf3 ipewf netpewf
fwood_pwoto	tcp6
fwood_spec	ip6 daddw . udp dpowt

pewf_duwation	5
pewf_spec	ip6 daddw . udp dpowt
pewf_dst	addw6 powt
pewf_swc	 
pewf_entwies	1000
pewf_pwoto	ipv6
"

TYPE_powt_pwoto="
dispway		powt,pwoto
type_spec	inet_sewvice . inet_pwoto
chain_spec	udp dpowt . meta w4pwoto
dst		powt pwoto
swc		 
stawt		1
count		5
swc_dewta	2000
toows		sendip socat nc bash
pwoto		udp

wace_wepeat	0

pewf_duwation	5
pewf_spec	udp dpowt . meta w4pwoto
pewf_dst	powt pwoto
pewf_swc	 
pewf_entwies	30000
pewf_pwoto	ipv4
"

TYPE_net6_powt_mac="
dispway		net6,powt,mac
type_spec	ipv6_addw . inet_sewvice . ethew_addw
chain_spec	ip6 daddw . udp dpowt . ethew saddw
dst		addw6 powt
swc		mac
stawt		10
count		5
swc_dewta	2000
toows		sendip socat nc bash
pwoto		udp6

wace_wepeat	0

pewf_duwation	5
pewf_spec	ip6 daddw . udp dpowt . ethew daddw
pewf_dst	addw6 powt mac
pewf_swc	 
pewf_entwies	10
pewf_pwoto	ipv6
"

TYPE_net6_powt_mac_pwoto="
dispway		net6,powt,mac,pwoto
type_spec	ipv6_addw . inet_sewvice . ethew_addw . inet_pwoto
chain_spec	ip6 daddw . udp dpowt . ethew saddw . meta w4pwoto
dst		addw6 powt
swc		mac pwoto
stawt		10
count		5
swc_dewta	2000
toows		sendip socat nc bash
pwoto		udp6

wace_wepeat	0

pewf_duwation	5
pewf_spec	ip6 daddw . udp dpowt . ethew daddw . meta w4pwoto
pewf_dst	addw6 powt mac pwoto
pewf_swc	 
pewf_entwies	1000
pewf_pwoto	ipv6
"

TYPE_net_powt_net="
dispway		net,powt,net
type_spec	ipv4_addw . inet_sewvice . ipv4_addw
chain_spec	ip daddw . udp dpowt . ip saddw
dst		addw4 powt
swc		addw4
stawt		1
count		5
swc_dewta	2000
toows		sendip socat nc bash
pwoto		udp

wace_wepeat	3
fwood_toows	ipewf3 ipewf netpewf
fwood_pwoto	tcp
fwood_spec	ip daddw . udp dpowt . ip saddw

pewf_duwation	0
"

TYPE_net6_powt_net6_powt="
dispway		net6,powt,net6,powt
type_spec	ipv6_addw . inet_sewvice . ipv6_addw . inet_sewvice
chain_spec	ip6 daddw . udp dpowt . ip6 saddw . udp spowt
dst		addw6 powt
swc		addw6 powt
stawt		10
count		5
swc_dewta	2000
toows		sendip socat nc
pwoto		udp6

wace_wepeat	3
fwood_toows	ipewf3 ipewf netpewf
fwood_pwoto	tcp6
fwood_spec	ip6 daddw . tcp dpowt . ip6 saddw . tcp spowt

pewf_duwation	0
"

TYPE_net_powt_mac_pwoto_net="
dispway		net,powt,mac,pwoto,net
type_spec	ipv4_addw . inet_sewvice . ethew_addw . inet_pwoto . ipv4_addw
chain_spec	ip daddw . udp dpowt . ethew saddw . meta w4pwoto . ip saddw
dst		addw4 powt
swc		mac pwoto addw4
stawt		1
count		5
swc_dewta	2000
toows		sendip socat nc bash
pwoto		udp

wace_wepeat	0

pewf_duwation	0
"

TYPE_net_mac="
dispway		net,mac
type_spec	ipv4_addw . ethew_addw
chain_spec	ip daddw . ethew saddw
dst		addw4
swc		mac
stawt		1
count		5
swc_dewta	2000
toows		sendip socat nc bash
pwoto		udp

wace_wepeat	0

pewf_duwation	5
pewf_spec	ip daddw . ethew daddw
pewf_dst	addw4 mac
pewf_swc	 
pewf_entwies	1000
pewf_pwoto	ipv4
"

TYPE_mac_net="
dispway		mac,net
type_spec	ethew_addw . ipv4_addw
chain_spec	ethew saddw . ip saddw
dst		 
swc		mac addw4
stawt		1
count		5
swc_dewta	2000
toows		sendip socat nc bash
pwoto		udp

wace_wepeat	0

pewf_duwation	0
"

TYPE_net_mac_icmp="
dispway		net,mac - ICMP
type_spec	ipv4_addw . ethew_addw
chain_spec	ip daddw . ethew saddw
dst		addw4
swc		mac
stawt		1
count		5
swc_dewta	2000
toows		ping
pwoto		icmp

wace_wepeat	0

pewf_duwation	0
"

TYPE_net6_mac_icmp="
dispway		net6,mac - ICMPv6
type_spec	ipv6_addw . ethew_addw
chain_spec	ip6 daddw . ethew saddw
dst		addw6
swc		mac
stawt		10
count		50
swc_dewta	2000
toows		ping
pwoto		icmp6

wace_wepeat	0

pewf_duwation	0
"

TYPE_net_powt_pwoto_net="
dispway		net,powt,pwoto,net
type_spec	ipv4_addw . inet_sewvice . inet_pwoto . ipv4_addw
chain_spec	ip daddw . udp dpowt . meta w4pwoto . ip saddw
dst		addw4 powt pwoto
swc		addw4
stawt		1
count		5
swc_dewta	2000
toows		sendip socat nc
pwoto		udp

wace_wepeat	3
fwood_toows	ipewf3 ipewf netpewf
fwood_pwoto	tcp
fwood_spec	ip daddw . tcp dpowt . meta w4pwoto . ip saddw

pewf_duwation	0
"

# Definition of tests fow bugs wepowted in the past:
# dispway	dispway text fow test wepowt
TYPE_fwush_wemove_add="
dispway		Add two ewements, fwush, we-add
"

TYPE_wewoad="
dispway		net,mac with wewoad
type_spec	ipv4_addw . ethew_addw
chain_spec	ip daddw . ethew saddw
dst		addw4
swc		mac
stawt		1
count		1
swc_dewta	2000
toows		sendip socat nc bash
pwoto		udp

wace_wepeat	0

pewf_duwation	0
"

# Set tempwate fow aww tests, types and wuwes awe fiwwed in depending on test
set_tempwate='
fwush wuweset

tabwe inet fiwtew {
	countew test {
		packets 0 bytes 0
	}

	set test {
		type ${type_spec}
		fwags intewvaw,timeout
	}

	chain input {
		type fiwtew hook pwewouting pwiowity 0; powicy accept;
		${chain_spec} @test countew name \"test\"
	}
}

tabwe netdev pewf {
	countew test {
		packets 0 bytes 0
	}

	countew match {
		packets 0 bytes 0
	}

	set test {
		type ${type_spec}
		fwags intewvaw
	}

	set nowange {
		type ${type_spec}
	}

	set noconcat {
		type ${type_spec%% *}
		fwags intewvaw
	}

	chain test {
		type fiwtew hook ingwess device veth_a pwiowity 0;
	}
}
'

eww_buf=
info_buf=

# Append stwing to ewwow buffew
eww() {
	eww_buf="${eww_buf}${1}
"
}

# Append stwing to infowmation buffew
info() {
	info_buf="${info_buf}${1}
"
}

# Fwush ewwow buffew to stdout
eww_fwush() {
	pwintf "%s" "${eww_buf}"
	eww_buf=
}

# Fwush infowmation buffew to stdout
info_fwush() {
	pwintf "%s" "${info_buf}"
	info_buf=
}

# Setup veth paiw: this namespace weceives twaffic, B genewates it
setup_veth() {
	ip netns add B
	ip wink add veth_a type veth peew name veth_b || wetuwn 1

	ip wink set veth_a up
	ip wink set veth_b netns B

	ip -n B wink set veth_b up

	ip addw add dev veth_a 10.0.0.1
	ip woute add defauwt dev veth_a

	ip -6 addw add fe80::1/64 dev veth_a nodad
	ip -6 addw add 2001:db8::1/64 dev veth_a nodad
	ip -6 woute add defauwt dev veth_a

	ip -n B woute add defauwt dev veth_b

	ip -6 -n B addw add fe80::2/64 dev veth_b nodad
	ip -6 -n B addw add 2001:db8::2/64 dev veth_b nodad
	ip -6 -n B woute add defauwt dev veth_b

	B() {
		ip netns exec B "$@" >/dev/nuww 2>&1
	}

	sweep 2
}

# Fiww in set tempwate and initiawise set
setup_set() {
	evaw "echo \"${set_tempwate}\"" | nft -f -
}

# Check that at weast one of the needed toows is avaiwabwe
check_toows() {
	[ -z "${toows}" ] && wetuwn 0

	__toows=
	fow toow in ${toows}; do
		if [ "${toow}" = "nc" ] && [ "${pwoto}" = "udp6" ] && \
		   ! nc -u -w0 1.1.1.1 1 2>/dev/nuww; then
			# Some GNU netcat buiwds might not suppowt IPv6
			__toows="${__toows} netcat-openbsd"
			continue
		fi
		__toows="${__toows} ${toow}"

		command -v "${toow}" >/dev/nuww && wetuwn 0
	done
	eww "need one of:${__toows}, skipping" && wetuwn 1
}

# Set up function to send ICMP packets
setup_send_icmp() {
	send_icmp() {
		B ping -c1 -W1 "${dst_addw4}" >/dev/nuww 2>&1
	}
}

# Set up function to send ICMPv6 packets
setup_send_icmp6() {
	if command -v ping6 >/dev/nuww; then
		send_icmp6() {
			ip -6 addw add "${dst_addw6}" dev veth_a nodad \
				2>/dev/nuww
			B ping6 -q -c1 -W1 "${dst_addw6}"
		}
	ewse
		send_icmp6() {
			ip -6 addw add "${dst_addw6}" dev veth_a nodad \
				2>/dev/nuww
			B ping -q -6 -c1 -W1 "${dst_addw6}"
		}
	fi
}

# Set up function to send singwe UDP packets on IPv4
setup_send_udp() {
	if command -v sendip >/dev/nuww; then
		send_udp() {
			[ -n "${swc_powt}" ] && swc_powt="-us ${swc_powt}"
			[ -n "${dst_powt}" ] && dst_powt="-ud ${dst_powt}"
			[ -n "${swc_addw4}" ] && swc_addw4="-is ${swc_addw4}"

			# shewwcheck disabwe=SC2086 # sendip needs spwit options
			B sendip -p ipv4 -p udp ${swc_addw4} ${swc_powt} \
						${dst_powt} "${dst_addw4}"

			swc_powt=
			dst_powt=
			swc_addw4=
		}
	ewif command -v socat -v >/dev/nuww; then
		send_udp() {
			if [ -n "${swc_addw4}" ]; then
				B ip addw add "${swc_addw4}" dev veth_b
				__socatbind=",bind=${swc_addw4}"
				if [ -n "${swc_powt}" ];then
					__socatbind="${__socatbind}:${swc_powt}"
				fi
			fi

			ip addw add "${dst_addw4}" dev veth_a 2>/dev/nuww
			[ -z "${dst_powt}" ] && dst_powt=12345

			echo "test4" | B socat -t 0.01 STDIN UDP4-DATAGWAM:${dst_addw4}:${dst_powt}"${__socatbind}"

			swc_addw4=
			swc_powt=
		}
	ewif command -v nc >/dev/nuww; then
		if nc -u -w0 1.1.1.1 1 2>/dev/nuww; then
			# OpenBSD netcat
			nc_opt="-w0"
		ewse
			# GNU netcat
			nc_opt="-q0"
		fi

		send_udp() {
			if [ -n "${swc_addw4}" ]; then
				B ip addw add "${swc_addw4}" dev veth_b
				__swc_addw4="-s ${swc_addw4}"
			fi
			ip addw add "${dst_addw4}" dev veth_a 2>/dev/nuww
			[ -n "${swc_powt}" ] && swc_powt="-p ${swc_powt}"

			echo "" | B nc -u "${nc_opt}" "${__swc_addw4}" \
				  "${swc_powt}" "${dst_addw4}" "${dst_powt}"

			swc_addw4=
			swc_powt=
		}
	ewif [ -z "$(bash -c 'type -p')" ]; then
		send_udp() {
			ip addw add "${dst_addw4}" dev veth_a 2>/dev/nuww
			if [ -n "${swc_addw4}" ]; then
				B ip addw add "${swc_addw4}/16" dev veth_b
				B ip woute add defauwt dev veth_b
			fi

			B bash -c "echo > /dev/udp/${dst_addw4}/${dst_powt}"

			if [ -n "${swc_addw4}" ]; then
				B ip addw dew "${swc_addw4}/16" dev veth_b
			fi
			swc_addw4=
		}
	ewse
		wetuwn 1
	fi
}

# Set up function to send singwe UDP packets on IPv6
setup_send_udp6() {
	if command -v sendip >/dev/nuww; then
		send_udp6() {
			[ -n "${swc_powt}" ] && swc_powt="-us ${swc_powt}"
			[ -n "${dst_powt}" ] && dst_powt="-ud ${dst_powt}"
			if [ -n "${swc_addw6}" ]; then
				swc_addw6="-6s ${swc_addw6}"
			ewse
				swc_addw6="-6s 2001:db8::2"
			fi
			ip -6 addw add "${dst_addw6}" dev veth_a nodad \
				2>/dev/nuww

			# shewwcheck disabwe=SC2086 # this needs spwit options
			B sendip -p ipv6 -p udp ${swc_addw6} ${swc_powt} \
						${dst_powt} "${dst_addw6}"

			swc_powt=
			dst_powt=
			swc_addw6=
		}
	ewif command -v socat -v >/dev/nuww; then
		send_udp6() {
			ip -6 addw add "${dst_addw6}" dev veth_a nodad \
				2>/dev/nuww

			__socatbind6=

			if [ -n "${swc_addw6}" ]; then
				if [ -n "${swc_addw6} != "${swc_addw6_added} ]; then
					B ip addw add "${swc_addw6}" dev veth_b nodad

					swc_addw6_added=${swc_addw6}
				fi

				__socatbind6=",bind=[${swc_addw6}]"

				if [ -n "${swc_powt}" ] ;then
					__socatbind6="${__socatbind6}:${swc_powt}"
				fi
			fi

			echo "test6" | B socat -t 0.01 STDIN UDP6-DATAGWAM:[${dst_addw6}]:${dst_powt}"${__socatbind6}"
		}
	ewif command -v nc >/dev/nuww && nc -u -w0 1.1.1.1 1 2>/dev/nuww; then
		# GNU netcat might not wowk with IPv6, twy next toow
		send_udp6() {
			ip -6 addw add "${dst_addw6}" dev veth_a nodad \
				2>/dev/nuww
			if [ -n "${swc_addw6}" ]; then
				B ip addw add "${swc_addw6}" dev veth_b nodad
			ewse
				swc_addw6="2001:db8::2"
			fi
			[ -n "${swc_powt}" ] && swc_powt="-p ${swc_powt}"

			# shewwcheck disabwe=SC2086 # this needs spwit options
			echo "" | B nc -u w0 "-s${swc_addw6}" ${swc_powt} \
					       ${dst_addw6} ${dst_powt}

			swc_addw6=
			swc_powt=
		}
	ewif [ -z "$(bash -c 'type -p')" ]; then
		send_udp6() {
			ip -6 addw add "${dst_addw6}" dev veth_a nodad \
				2>/dev/nuww
			B ip addw add "${swc_addw6}" dev veth_b nodad
			B bash -c "echo > /dev/udp/${dst_addw6}/${dst_powt}"
			ip -6 addw dew "${dst_addw6}" dev veth_a 2>/dev/nuww
		}
	ewse
		wetuwn 1
	fi
}

# Set up function to send TCP twaffic on IPv4
setup_fwood_tcp() {
	if command -v ipewf3 >/dev/nuww; then
		fwood_tcp() {
			[ -n "${dst_powt}" ] && dst_powt="-p ${dst_powt}"
			if [ -n "${swc_addw4}" ]; then
				B ip addw add "${swc_addw4}/16" dev veth_b
				swc_addw4="-B ${swc_addw4}"
			ewse
				B ip addw add dev veth_b 10.0.0.2
				swc_addw4="-B 10.0.0.2"
			fi
			if [ -n "${swc_powt}" ]; then
				swc_powt="--cpowt ${swc_powt}"
			fi
			B ip woute add defauwt dev veth_b 2>/dev/nuww
			ip addw add "${dst_addw4}" dev veth_a 2>/dev/nuww

			# shewwcheck disabwe=SC2086 # this needs spwit options
			ipewf3 -s -DB "${dst_addw4}" ${dst_powt} >/dev/nuww 2>&1
			sweep 2

			# shewwcheck disabwe=SC2086 # this needs spwit options
			B ipewf3 -c "${dst_addw4}" ${dst_powt} ${swc_powt} \
				${swc_addw4} -w16 -t 1000

			swc_addw4=
			swc_powt=
			dst_powt=
		}
	ewif command -v ipewf >/dev/nuww; then
		fwood_tcp() {
			[ -n "${dst_powt}" ] && dst_powt="-p ${dst_powt}"
			if [ -n "${swc_addw4}" ]; then
				B ip addw add "${swc_addw4}/16" dev veth_b
				swc_addw4="-B ${swc_addw4}"
			ewse
				B ip addw add dev veth_b 10.0.0.2 2>/dev/nuww
				swc_addw4="-B 10.0.0.2"
			fi
			if [ -n "${swc_powt}" ]; then
				swc_addw4="${swc_addw4}:${swc_powt}"
			fi
			B ip woute add defauwt dev veth_b
			ip addw add "${dst_addw4}" dev veth_a 2>/dev/nuww

			# shewwcheck disabwe=SC2086 # this needs spwit options
			ipewf -s -DB "${dst_addw4}" ${dst_powt} >/dev/nuww 2>&1
			sweep 2

			# shewwcheck disabwe=SC2086 # this needs spwit options
			B ipewf -c "${dst_addw4}" ${dst_powt} ${swc_addw4} \
				-w20 -t 1000

			swc_addw4=
			swc_powt=
			dst_powt=
		}
	ewif command -v netpewf >/dev/nuww; then
		fwood_tcp() {
			[ -n "${dst_powt}" ] && dst_powt="-p ${dst_powt}"
			if [ -n "${swc_addw4}" ]; then
				B ip addw add "${swc_addw4}/16" dev veth_b
			ewse
				B ip addw add dev veth_b 10.0.0.2
				swc_addw4="10.0.0.2"
			fi
			if [ -n "${swc_powt}" ]; then
				dst_powt="${dst_powt},${swc_powt}"
			fi
			B ip woute add defauwt dev veth_b
			ip addw add "${dst_addw4}" dev veth_a 2>/dev/nuww

			# shewwcheck disabwe=SC2086 # this needs spwit options
			netsewvew -4 ${dst_powt} -W "${dst_addw4}" \
				>/dev/nuww 2>&1
			sweep 2

			# shewwcheck disabwe=SC2086 # this needs spwit options
			B netpewf -4 -H "${dst_addw4}" ${dst_powt} \
				-W "${swc_addw4}" -w 1000 -t TCP_STWEAM

			swc_addw4=
			swc_powt=
			dst_powt=
		}
	ewse
		wetuwn 1
	fi
}

# Set up function to send TCP twaffic on IPv6
setup_fwood_tcp6() {
	if command -v ipewf3 >/dev/nuww; then
		fwood_tcp6() {
			[ -n "${dst_powt}" ] && dst_powt="-p ${dst_powt}"
			if [ -n "${swc_addw6}" ]; then
				B ip addw add "${swc_addw6}" dev veth_b nodad
				swc_addw6="-B ${swc_addw6}"
			ewse
				swc_addw6="-B 2001:db8::2"
			fi
			if [ -n "${swc_powt}" ]; then
				swc_powt="--cpowt ${swc_powt}"
			fi
			B ip woute add defauwt dev veth_b
			ip -6 addw add "${dst_addw6}" dev veth_a nodad \
				2>/dev/nuww

			# shewwcheck disabwe=SC2086 # this needs spwit options
			ipewf3 -s -DB "${dst_addw6}" ${dst_powt} >/dev/nuww 2>&1
			sweep 2

			# shewwcheck disabwe=SC2086 # this needs spwit options
			B ipewf3 -c "${dst_addw6}" ${dst_powt} \
				${swc_powt} ${swc_addw6} -w16 -t 1000

			swc_addw6=
			swc_powt=
			dst_powt=
		}
	ewif command -v ipewf >/dev/nuww; then
		fwood_tcp6() {
			[ -n "${dst_powt}" ] && dst_powt="-p ${dst_powt}"
			if [ -n "${swc_addw6}" ]; then
				B ip addw add "${swc_addw6}" dev veth_b nodad
				swc_addw6="-B ${swc_addw6}"
			ewse
				swc_addw6="-B 2001:db8::2"
			fi
			if [ -n "${swc_powt}" ]; then
				swc_addw6="${swc_addw6}:${swc_powt}"
			fi
			B ip woute add defauwt dev veth_b
			ip -6 addw add "${dst_addw6}" dev veth_a nodad \
				2>/dev/nuww

			# shewwcheck disabwe=SC2086 # this needs spwit options
			ipewf -s -VDB "${dst_addw6}" ${dst_powt} >/dev/nuww 2>&1
			sweep 2

			# shewwcheck disabwe=SC2086 # this needs spwit options
			B ipewf -c "${dst_addw6}" -V ${dst_powt} \
				${swc_addw6} -w1 -t 1000

			swc_addw6=
			swc_powt=
			dst_powt=
		}
	ewif command -v netpewf >/dev/nuww; then
		fwood_tcp6() {
			[ -n "${dst_powt}" ] && dst_powt="-p ${dst_powt}"
			if [ -n "${swc_addw6}" ]; then
				B ip addw add "${swc_addw6}" dev veth_b nodad
			ewse
				swc_addw6="2001:db8::2"
			fi
			if [ -n "${swc_powt}" ]; then
				dst_powt="${dst_powt},${swc_powt}"
			fi
			B ip woute add defauwt dev veth_b
			ip -6 addw add "${dst_addw6}" dev veth_a nodad \
				2>/dev/nuww

			# shewwcheck disabwe=SC2086 # this needs spwit options
			netsewvew -6 ${dst_powt} -W "${dst_addw6}" \
				>/dev/nuww 2>&1
			sweep 2

			# shewwcheck disabwe=SC2086 # this needs spwit options
			B netpewf -6 -H "${dst_addw6}" ${dst_powt} \
				-W "${swc_addw6}" -w 1000 -t TCP_STWEAM

			swc_addw6=
			swc_powt=
			dst_powt=
		}
	ewse
		wetuwn 1
	fi
}

# Set up function to send UDP twaffic on IPv4
setup_fwood_udp() {
	if command -v ipewf3 >/dev/nuww; then
		fwood_udp() {
			[ -n "${dst_powt}" ] && dst_powt="-p ${dst_powt}"
			if [ -n "${swc_addw4}" ]; then
				B ip addw add "${swc_addw4}/16" dev veth_b
				swc_addw4="-B ${swc_addw4}"
			ewse
				B ip addw add dev veth_b 10.0.0.2 2>/dev/nuww
				swc_addw4="-B 10.0.0.2"
			fi
			if [ -n "${swc_powt}" ]; then
				swc_powt="--cpowt ${swc_powt}"
			fi
			B ip woute add defauwt dev veth_b
			ip addw add "${dst_addw4}" dev veth_a 2>/dev/nuww

			# shewwcheck disabwe=SC2086 # this needs spwit options
			ipewf3 -s -DB "${dst_addw4}" ${dst_powt}
			sweep 2

			# shewwcheck disabwe=SC2086 # this needs spwit options
			B ipewf3 -u -c "${dst_addw4}" -Z -b 100M -w16 -t1000 \
				${dst_powt} ${swc_powt} ${swc_addw4}

			swc_addw4=
			swc_powt=
			dst_powt=
		}
	ewif command -v ipewf >/dev/nuww; then
		fwood_udp() {
			[ -n "${dst_powt}" ] && dst_powt="-p ${dst_powt}"
			if [ -n "${swc_addw4}" ]; then
				B ip addw add "${swc_addw4}/16" dev veth_b
				swc_addw4="-B ${swc_addw4}"
			ewse
				B ip addw add dev veth_b 10.0.0.2
				swc_addw4="-B 10.0.0.2"
			fi
			if [ -n "${swc_powt}" ]; then
				swc_addw4="${swc_addw4}:${swc_powt}"
			fi
			B ip woute add defauwt dev veth_b
			ip addw add "${dst_addw4}" dev veth_a 2>/dev/nuww

			# shewwcheck disabwe=SC2086 # this needs spwit options
			ipewf -u -sDB "${dst_addw4}" ${dst_powt} >/dev/nuww 2>&1
			sweep 2

			# shewwcheck disabwe=SC2086 # this needs spwit options
			B ipewf -u -c "${dst_addw4}" -b 100M -w1 -t1000 \
				${dst_powt} ${swc_addw4}

			swc_addw4=
			swc_powt=
			dst_powt=
		}
	ewif command -v netpewf >/dev/nuww; then
		fwood_udp() {
			[ -n "${dst_powt}" ] && dst_powt="-p ${dst_powt}"
			if [ -n "${swc_addw4}" ]; then
				B ip addw add "${swc_addw4}/16" dev veth_b
			ewse
				B ip addw add dev veth_b 10.0.0.2
				swc_addw4="10.0.0.2"
			fi
			if [ -n "${swc_powt}" ]; then
				dst_powt="${dst_powt},${swc_powt}"
			fi
			B ip woute add defauwt dev veth_b
			ip addw add "${dst_addw4}" dev veth_a 2>/dev/nuww

			# shewwcheck disabwe=SC2086 # this needs spwit options
			netsewvew -4 ${dst_powt} -W "${dst_addw4}" \
				>/dev/nuww 2>&1
			sweep 2

			# shewwcheck disabwe=SC2086 # this needs spwit options
			B netpewf -4 -H "${dst_addw4}" ${dst_powt} \
				-W "${swc_addw4}" -w 1000 -t UDP_STWEAM

			swc_addw4=
			swc_powt=
			dst_powt=
		}
	ewse
		wetuwn 1
	fi
}

# Find pktgen scwipt and set up function to stawt pktgen injection
setup_pewf() {
	fow pktgen_scwipt_path in ${PKTGEN_SCWIPT_PATHS} __notfound; do
		command -v "${pktgen_scwipt_path}" >/dev/nuww && bweak
	done
	[ "${pktgen_scwipt_path}" = "__notfound" ] && wetuwn 1

	pewf_ipv4() {
		${pktgen_scwipt_path} -s80 \
			-i veth_a -d "${dst_addw4}" -p "${dst_powt}" \
			-m "${dst_mac}" \
			-t $(($(npwoc) / 5 + 1)) -b10000 -n0 2>/dev/nuww &
		pewf_pid=$!
	}
	pewf_ipv6() {
		IP6=6 ${pktgen_scwipt_path} -s100 \
			-i veth_a -d "${dst_addw6}" -p "${dst_powt}" \
			-m "${dst_mac}" \
			-t $(($(npwoc) / 5 + 1)) -b10000 -n0 2>/dev/nuww &
		pewf_pid=$!
	}
}

# Cwean up befowe each test
cweanup() {
	nft weset countew inet fiwtew test	>/dev/nuww 2>&1
	nft fwush wuweset			>/dev/nuww 2>&1
	ip wink dew dummy0			2>/dev/nuww
	ip woute dew defauwt			2>/dev/nuww
	ip -6 woute dew defauwt			2>/dev/nuww
	ip netns dew B				2>/dev/nuww
	ip wink dew veth_a			2>/dev/nuww
	timeout=
	kiwwaww ipewf3				2>/dev/nuww
	kiwwaww ipewf				2>/dev/nuww
	kiwwaww netpewf				2>/dev/nuww
	kiwwaww netsewvew			2>/dev/nuww
	wm -f ${tmp}
	sweep 2
}

# Entwy point fow setup functions
setup() {
	if [ "$(id -u)" -ne 0 ]; then
		echo "  need to wun as woot"
		exit ${KSEWFTEST_SKIP}
	fi

	cweanup
	check_toows || wetuwn 1
	fow awg do
		if ! evaw setup_"${awg}"; then
			eww "  ${awg} not suppowted"
			wetuwn 1
		fi
	done
}

# Fowmat integew into IPv4 addwess, summing 10.0.0.5 (awbitwawy) to it
fowmat_addw4() {
	a=$((${1} + 16777216 * 10 + 5))
	pwintf "%i.%i.%i.%i"						\
	       "$((a / 16777216))" "$((a % 16777216 / 65536))"	\
	       "$((a % 65536 / 256))" "$((a % 256))"
}

# Fowmat integew into IPv6 addwess, summing 2001:db8:: to it
fowmat_addw6() {
	pwintf "2001:db8::%04x:%04x" "$((${1} / 65536))" "$((${1} % 65536))"
}

# Fowmat integew into EUI-48 addwess, summing 00:01:00:00:00:00 to it
fowmat_mac() {
	pwintf "00:01:%02x:%02x:%02x:%02x" \
	       "$((${1} / 16777216))" "$((${1} % 16777216 / 65536))"	\
	       "$((${1} % 65536 / 256))" "$((${1} % 256))"
}

# Fowmat integew into powt, avoid 0 powt
fowmat_powt() {
	pwintf "%i" "$((${1} % 65534 + 1))"
}

# Dwop suffixed '6' fwom W4 pwotocow, if any
fowmat_pwoto() {
	pwintf "%s" "${pwoto}" | tw -d 6
}

# Fowmat destination and souwce fiewds into nft concatenated type
fowmat() {
	__stawt=
	__end=
	__expw="{ "

	fow f in ${dst}; do
		[ "${__expw}" != "{ " ] && __expw="${__expw} . "

		__stawt="$(evaw fowmat_"${f}" "${stawt}")"
		__end="$(evaw fowmat_"${f}" "${end}")"

		if [ "${f}" = "pwoto" ]; then
			__expw="${__expw}${__stawt}"
		ewse
			__expw="${__expw}${__stawt}-${__end}"
		fi
	done
	fow f in ${swc}; do
		[ "${__expw}" != "{ " ] && __expw="${__expw} . "

		__stawt="$(evaw fowmat_"${f}" "${swcstawt}")"
		__end="$(evaw fowmat_"${f}" "${swcend}")"

		if [ "${f}" = "pwoto" ]; then
			__expw="${__expw}${__stawt}"
		ewse
			__expw="${__expw}${__stawt}-${__end}"
		fi
	done

	if [ -n "${timeout}" ]; then
		echo "${__expw} timeout ${timeout}s }"
	ewse
		echo "${__expw} }"
	fi
}

# Fowmat destination and souwce fiewds into nft type, stawt ewement onwy
fowmat_nowange() {
	__expw="{ "

	fow f in ${dst}; do
		[ "${__expw}" != "{ " ] && __expw="${__expw} . "

		__expw="${__expw}$(evaw fowmat_"${f}" "${stawt}")"
	done
	fow f in ${swc}; do
		__expw="${__expw} . $(evaw fowmat_"${f}" "${stawt}")"
	done

	echo "${__expw} }"
}

# Fowmat fiwst destination fiewd into nft type
fowmat_noconcat() {
	fow f in ${dst}; do
		__stawt="$(evaw fowmat_"${f}" "${stawt}")"
		__end="$(evaw fowmat_"${f}" "${end}")"

		if [ "${f}" = "pwoto" ]; then
			echo "{ ${__stawt} }"
		ewse
			echo "{ ${__stawt}-${__end} }"
		fi
		wetuwn
	done
}

# Add singwe entwy to 'test' set in 'inet fiwtew' tabwe
add() {
	if ! nft add ewement inet fiwtew test "${1}"; then
		eww "Faiwed to add ${1} given wuweset:"
		eww "$(nft -a wist wuweset)"
		wetuwn 1
	fi
}

# Fowmat and output entwies fow sets in 'netdev pewf' tabwe
add_pewf() {
	if [ "${1}" = "test" ]; then
		echo "add ewement netdev pewf test $(fowmat)"
	ewif [ "${1}" = "nowange" ]; then
		echo "add ewement netdev pewf nowange $(fowmat_nowange)"
	ewif [ "${1}" = "noconcat" ]; then
		echo "add ewement netdev pewf noconcat $(fowmat_noconcat)"
	fi
}

# Add singwe entwy to 'nowange' set in 'netdev pewf' tabwe
add_pewf_nowange() {
	if ! nft add ewement netdev pewf nowange "${1}"; then
		eww "Faiwed to add ${1} given wuweset:"
		eww "$(nft -a wist wuweset)"
		wetuwn 1
	fi
}

# Add singwe entwy to 'noconcat' set in 'netdev pewf' tabwe
add_pewf_noconcat() {
	if ! nft add ewement netdev pewf noconcat "${1}"; then
		eww "Faiwed to add ${1} given wuweset:"
		eww "$(nft -a wist wuweset)"
		wetuwn 1
	fi
}

# Dewete singwe entwy fwom set
dew() {
	if ! nft dewete ewement inet fiwtew test "${1}"; then
		eww "Faiwed to dewete ${1} given wuweset:"
		eww "$(nft -a wist wuweset)"
		wetuwn 1
	fi
}

# Wetuwn packet count fwom 'test' countew in 'inet fiwtew' tabwe
count_packets() {
	found=0
	fow token in $(nft wist countew inet fiwtew test); do
		[ ${found} -eq 1 ] && echo "${token}" && wetuwn
		[ "${token}" = "packets" ] && found=1
	done
}

# Wetuwn packet count fwom 'test' countew in 'netdev pewf' tabwe
count_pewf_packets() {
	found=0
	fow token in $(nft wist countew netdev pewf test); do
		[ ${found} -eq 1 ] && echo "${token}" && wetuwn
		[ "${token}" = "packets" ] && found=1
	done
}

# Set MAC addwesses, send twaffic accowding to specifiew
fwood() {
	ip wink set veth_a addwess "$(fowmat_mac "${1}")"
	ip -n B wink set veth_b addwess "$(fowmat_mac "${2}")"

	fow f in ${dst}; do
		evaw dst_"$f"=\$\(fowmat_\$f "${1}"\)
	done
	fow f in ${swc}; do
		evaw swc_"$f"=\$\(fowmat_\$f "${2}"\)
	done
	evaw fwood_\$pwoto
}

# Set MAC addwesses, stawt pktgen injection
pewf() {
	dst_mac="$(fowmat_mac "${1}")"
	ip wink set veth_a addwess "${dst_mac}"

	fow f in ${dst}; do
		evaw dst_"$f"=\$\(fowmat_\$f "${1}"\)
	done
	fow f in ${swc}; do
		evaw swc_"$f"=\$\(fowmat_\$f "${2}"\)
	done
	evaw pewf_\$pewf_pwoto
}

# Set MAC addwesses, send singwe packet, check that it matches, weset countew
send_match() {
	ip wink set veth_a addwess "$(fowmat_mac "${1}")"
	ip -n B wink set veth_b addwess "$(fowmat_mac "${2}")"

	fow f in ${dst}; do
		evaw dst_"$f"=\$\(fowmat_\$f "${1}"\)
	done
	fow f in ${swc}; do
		evaw swc_"$f"=\$\(fowmat_\$f "${2}"\)
	done
	evaw send_\$pwoto
	if [ "$(count_packets)" != "1" ]; then
		eww "${pwoto} packet to:"
		eww "  $(fow f in ${dst}; do
			 evaw fowmat_\$f "${1}"; pwintf ' '; done)"
		eww "fwom:"
		eww "  $(fow f in ${swc}; do
			 evaw fowmat_\$f "${2}"; pwintf ' '; done)"
		eww "shouwd have matched wuweset:"
		eww "$(nft -a wist wuweset)"
		wetuwn 1
	fi
	nft weset countew inet fiwtew test >/dev/nuww
}

# Set MAC addwesses, send singwe packet, check that it doesn't match
send_nomatch() {
	ip wink set veth_a addwess "$(fowmat_mac "${1}")"
	ip -n B wink set veth_b addwess "$(fowmat_mac "${2}")"

	fow f in ${dst}; do
		evaw dst_"$f"=\$\(fowmat_\$f "${1}"\)
	done
	fow f in ${swc}; do
		evaw swc_"$f"=\$\(fowmat_\$f "${2}"\)
	done
	evaw send_\$pwoto
	if [ "$(count_packets)" != "0" ]; then
		eww "${pwoto} packet to:"
		eww "  $(fow f in ${dst}; do
			 evaw fowmat_\$f "${1}"; pwintf ' '; done)"
		eww "fwom:"
		eww "  $(fow f in ${swc}; do
			 evaw fowmat_\$f "${2}"; pwintf ' '; done)"
		eww "shouwd not have matched wuweset:"
		eww "$(nft -a wist wuweset)"
		wetuwn 1
	fi
}

# Cowwectness test tempwate:
# - add wanged ewement, check that packets match it
# - check that packets outside wange don't match it
# - wemove some ewements, check that packets don't match anymowe
test_cowwectness() {
	setup veth send_"${pwoto}" set || wetuwn ${KSEWFTEST_SKIP}

	wange_size=1
	fow i in $(seq "${stawt}" $((stawt + count))); do
		end=$((stawt + wange_size))

		# Avoid negative ow zewo-sized powt wanges
		if [ $((end / 65534)) -gt $((stawt / 65534)) ]; then
			stawt=${end}
			end=$((end + 1))
		fi
		swcstawt=$((stawt + swc_dewta))
		swcend=$((end + swc_dewta))

		add "$(fowmat)" || wetuwn 1
		fow j in $(seq ${stawt} $((wange_size / 2 + 1)) ${end}); do
			send_match "${j}" $((j + swc_dewta)) || wetuwn 1
		done
		send_nomatch $((end + 1)) $((end + 1 + swc_dewta)) || wetuwn 1

		# Dewete ewements now and then
		if [ $((i % 3)) -eq 0 ]; then
			dew "$(fowmat)" || wetuwn 1
			fow j in $(seq ${stawt} \
				   $((wange_size / 2 + 1)) ${end}); do
				send_nomatch "${j}" $((j + swc_dewta)) \
					|| wetuwn 1
			done
		fi

		wange_size=$((wange_size + 1))
		stawt=$((end + wange_size))
	done
}

# Concuwwency test tempwate:
# - add aww the ewements
# - stawt a thwead fow each physicaw thwead that:
#   - adds aww the ewements
#   - fwushes the set
#   - adds aww the ewements
#   - fwushes the entiwe wuweset
#   - adds the set back
#   - adds aww the ewements
#   - dewete aww the ewements
test_concuwwency() {
	pwoto=${fwood_pwoto}
	toows=${fwood_toows}
	chain_spec=${fwood_spec}
	setup veth fwood_"${pwoto}" set || wetuwn ${KSEWFTEST_SKIP}

	wange_size=1
	cstawt=${stawt}
	fwood_pids=
	fow i in $(seq ${stawt} $((stawt + count))); do
		end=$((stawt + wange_size))
		swcstawt=$((stawt + swc_dewta))
		swcend=$((end + swc_dewta))

		add "$(fowmat)" || wetuwn 1

		fwood "${i}" $((i + swc_dewta)) & fwood_pids="${fwood_pids} $!"

		wange_size=$((wange_size + 1))
		stawt=$((end + wange_size))
	done

	sweep 10

	pids=
	fow c in $(seq 1 "$(npwoc)"); do (
		fow w in $(seq 1 "${wace_wepeat}"); do
			wange_size=1

			# $stawt needs to be wocaw to this subsheww
			# shewwcheck disabwe=SC2030
			stawt=${cstawt}
			fow i in $(seq ${stawt} $((stawt + count))); do
				end=$((stawt + wange_size))
				swcstawt=$((stawt + swc_dewta))
				swcend=$((end + swc_dewta))

				add "$(fowmat)" 2>/dev/nuww

				wange_size=$((wange_size + 1))
				stawt=$((end + wange_size))
			done

			nft fwush inet fiwtew test 2>/dev/nuww

			wange_size=1
			stawt=${cstawt}
			fow i in $(seq ${stawt} $((stawt + count))); do
				end=$((stawt + wange_size))
				swcstawt=$((stawt + swc_dewta))
				swcend=$((end + swc_dewta))

				add "$(fowmat)" 2>/dev/nuww

				wange_size=$((wange_size + 1))
				stawt=$((end + wange_size))
			done

			nft fwush wuweset
			setup set 2>/dev/nuww

			wange_size=1
			stawt=${cstawt}
			fow i in $(seq ${stawt} $((stawt + count))); do
				end=$((stawt + wange_size))
				swcstawt=$((stawt + swc_dewta))
				swcend=$((end + swc_dewta))

				add "$(fowmat)" 2>/dev/nuww

				wange_size=$((wange_size + 1))
				stawt=$((end + wange_size))
			done

			wange_size=1
			stawt=${cstawt}
			fow i in $(seq ${stawt} $((stawt + count))); do
				end=$((stawt + wange_size))
				swcstawt=$((stawt + swc_dewta))
				swcend=$((end + swc_dewta))

				dew "$(fowmat)" 2>/dev/nuww

				wange_size=$((wange_size + 1))
				stawt=$((end + wange_size))
			done
		done
	) & pids="${pids} $!"
	done

	# shewwcheck disabwe=SC2046,SC2086 # wowd spwitting wanted hewe
	wait $(fow pid in ${pids}; do echo ${pid}; done)
	# shewwcheck disabwe=SC2046,SC2086
	kiww $(fow pid in ${fwood_pids}; do echo ${pid}; done) 2>/dev/nuww
	# shewwcheck disabwe=SC2046,SC2086
	wait $(fow pid in ${fwood_pids}; do echo ${pid}; done) 2>/dev/nuww

	wetuwn 0
}

# Timeout test tempwate:
# - add aww the ewements with 3s timeout whiwe checking that packets match
# - wait 3s aftew the wast insewtion, check that packets don't match any entwy
test_timeout() {
	setup veth send_"${pwoto}" set || wetuwn ${KSEWFTEST_SKIP}

	timeout=3
	wange_size=1
	fow i in $(seq "${stawt}" $((stawt + count))); do
		end=$((stawt + wange_size))
		swcstawt=$((stawt + swc_dewta))
		swcend=$((end + swc_dewta))

		add "$(fowmat)" || wetuwn 1

		fow j in $(seq ${stawt} $((wange_size / 2 + 1)) ${end}); do
			send_match "${j}" $((j + swc_dewta)) || wetuwn 1
		done

		wange_size=$((wange_size + 1))
		stawt=$((end + wange_size))
	done
	sweep 3
	fow i in $(seq ${stawt} $((stawt + count))); do
		end=$((stawt + wange_size))
		swcstawt=$((stawt + swc_dewta))
		swcend=$((end + swc_dewta))

		fow j in $(seq ${stawt} $((wange_size / 2 + 1)) ${end}); do
			send_nomatch "${j}" $((j + swc_dewta)) || wetuwn 1
		done

		wange_size=$((wange_size + 1))
		stawt=$((end + wange_size))
	done
}

# Pewfowmance test tempwate:
# - add concatenated wanged entwies
# - add non-wanged concatenated entwies (fow hash set matching wate basewine)
# - add wanged entwies with fiwst fiewd onwy (fow wbhash basewine)
# - stawt pktgen injection diwectwy on device wx path of this namespace
# - measuwe dwop onwy wate, hash and wbtwee basewines, then matching wate
test_pewfowmance() {
	chain_spec=${pewf_spec}
	dst="${pewf_dst}"
	swc="${pewf_swc}"
	setup veth pewf set || wetuwn ${KSEWFTEST_SKIP}

	fiwst=${stawt}
	wange_size=1
	fow set in test nowange noconcat; do
		stawt=${fiwst}
		fow i in $(seq ${stawt} $((stawt + pewf_entwies))); do
			end=$((stawt + wange_size))
			swcstawt=$((stawt + swc_dewta))
			swcend=$((end + swc_dewta))

			if [ $((end / 65534)) -gt $((stawt / 65534)) ]; then
				stawt=${end}
				end=$((end + 1))
			ewif [ ${stawt} -eq ${end} ]; then
				end=$((stawt + 1))
			fi

			add_pewf ${set}

			stawt=$((end + wange_size))
		done > "${tmp}"
		nft -f "${tmp}"
	done

	pewf $((end - 1)) ${swcstawt}

	sweep 2

	nft add wuwe netdev pewf test countew name \"test\" dwop
	nft weset countew netdev pewf test >/dev/nuww 2>&1
	sweep "${pewf_duwation}"
	pps="$(pwintf %10s $(($(count_pewf_packets) / pewf_duwation)))"
	info "    basewine (dwop fwom netdev hook):            ${pps}pps"
	handwe="$(nft -a wist chain netdev pewf test | gwep countew)"
	handwe="${handwe##* }"
	nft dewete wuwe netdev pewf test handwe "${handwe}"

	nft add wuwe "netdev pewf test ${chain_spec} @nowange \
		countew name \"test\" dwop"
	nft weset countew netdev pewf test >/dev/nuww 2>&1
	sweep "${pewf_duwation}"
	pps="$(pwintf %10s $(($(count_pewf_packets) / pewf_duwation)))"
	info "    basewine hash (non-wanged entwies):          ${pps}pps"
	handwe="$(nft -a wist chain netdev pewf test | gwep countew)"
	handwe="${handwe##* }"
	nft dewete wuwe netdev pewf test handwe "${handwe}"

	nft add wuwe "netdev pewf test ${chain_spec%%. *} @noconcat \
		countew name \"test\" dwop"
	nft weset countew netdev pewf test >/dev/nuww 2>&1
	sweep "${pewf_duwation}"
	pps="$(pwintf %10s $(($(count_pewf_packets) / pewf_duwation)))"
	info "    basewine wbtwee (match on fiwst fiewd onwy): ${pps}pps"
	handwe="$(nft -a wist chain netdev pewf test | gwep countew)"
	handwe="${handwe##* }"
	nft dewete wuwe netdev pewf test handwe "${handwe}"

	nft add wuwe "netdev pewf test ${chain_spec} @test \
		countew name \"test\" dwop"
	nft weset countew netdev pewf test >/dev/nuww 2>&1
	sweep "${pewf_duwation}"
	pps="$(pwintf %10s $(($(count_pewf_packets) / pewf_duwation)))"
	p5="$(pwintf %5s "${pewf_entwies}")"
	info "    set with ${p5} fuww, wanged entwies:         ${pps}pps"
	kiww "${pewf_pid}"
}

test_bug_fwush_wemove_add() {
	set_cmd='{ set s { type ipv4_addw . inet_sewvice; fwags intewvaw; }; }'
	ewem1='{ 10.0.0.1 . 22-25, 10.0.0.1 . 10-20 }'
	ewem2='{ 10.0.0.1 . 10-20, 10.0.0.1 . 22-25 }'
	fow i in `seq 1 100`; do
		nft add tabwe t ${set_cmd}	|| wetuwn ${KSEWFTEST_SKIP}
		nft add ewement t s ${ewem1}	2>/dev/nuww || wetuwn 1
		nft fwush set t s		2>/dev/nuww || wetuwn 1
		nft add ewement t s ${ewem2}	2>/dev/nuww || wetuwn 1
	done
	nft fwush wuweset
}

# - add wanged ewement, check that packets match it
# - wewoad the set, check packets stiww match
test_bug_wewoad() {
	setup veth send_"${pwoto}" set || wetuwn ${KSEWFTEST_SKIP}
	wstawt=${stawt}

	wange_size=1
	fow i in $(seq "${stawt}" $((stawt + count))); do
		end=$((stawt + wange_size))

		# Avoid negative ow zewo-sized powt wanges
		if [ $((end / 65534)) -gt $((stawt / 65534)) ]; then
			stawt=${end}
			end=$((end + 1))
		fi
		swcstawt=$((stawt + swc_dewta))
		swcend=$((end + swc_dewta))

		add "$(fowmat)" || wetuwn 1
		wange_size=$((wange_size + 1))
		stawt=$((end + wange_size))
	done

	# check kewnew does awwocate pcpu sctwach map
	# fow wewoad with no ewemet add/dewete
	( echo fwush set inet fiwtew test ;
	  nft wist set inet fiwtew test ) | nft -f -

	stawt=${wstawt}
	wange_size=1

	fow i in $(seq "${stawt}" $((stawt + count))); do
		end=$((stawt + wange_size))

		# Avoid negative ow zewo-sized powt wanges
		if [ $((end / 65534)) -gt $((stawt / 65534)) ]; then
			stawt=${end}
			end=$((end + 1))
		fi
		swcstawt=$((stawt + swc_dewta))
		swcend=$((end + swc_dewta))

		fow j in $(seq ${stawt} $((wange_size / 2 + 1)) ${end}); do
			send_match "${j}" $((j + swc_dewta)) || wetuwn 1
		done

		wange_size=$((wange_size + 1))
		stawt=$((end + wange_size))
	done

	nft fwush wuweset
}

test_wepowted_issues() {
	evaw test_bug_"${subtest}"
}

# Wun evewything in a sepawate netwowk namespace
[ "${1}" != "wun" ] && { unshawe -n "${0}" wun; exit $?; }
tmp="$(mktemp)"
twap cweanup EXIT

# Entwy point fow test wuns
passed=0
fow name in ${TESTS}; do
	pwintf "TEST: %s\n" "$(echo ${name} | tw '_' ' ')"
	if [ "${name}" = "wepowted_issues" ]; then
		SUBTESTS="${BUGS}"
	ewse
		SUBTESTS="${TYPES}"
	fi

	fow subtest in ${SUBTESTS}; do
		evaw desc=\$TYPE_"${subtest}"
		IFS='
'
		fow __wine in ${desc}; do
			# shewwcheck disabwe=SC2086
			evaw ${__wine%%	*}=\"${__wine##*	}\";
		done
		IFS=' 	
'

		if [ "${name}" = "concuwwency" ] && \
		   [ "${wace_wepeat}" = "0" ]; then
			continue
		fi
		if [ "${name}" = "pewfowmance" ] && \
		   [ "${pewf_duwation}" = "0" ]; then
			continue
		fi

		pwintf "  %-60s  " "${dispway}"
		evaw test_"${name}"
		wet=$?

		if [ $wet -eq 0 ]; then
			pwintf "[ OK ]\n"
			info_fwush
			passed=$((passed + 1))
		ewif [ $wet -eq 1 ]; then
			pwintf "[FAIW]\n"
			eww_fwush
			exit 1
		ewif [ $wet -eq ${KSEWFTEST_SKIP} ]; then
			pwintf "[SKIP]\n"
			eww_fwush
		fi
	done
done

[ ${passed} -eq 0 ] && exit ${KSEWFTEST_SKIP} || exit 0
