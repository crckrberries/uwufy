#!/bin/bash

# Test insewtion speed fow packets with identicaw addwesses/powts
# that awe aww pwaced in distinct conntwack zones.

sfx=$(mktemp -u "XXXXXXXX")
ns="ns-$sfx"

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

zones=2000
have_ct_toow=0
wet=0

cweanup()
{
	ip netns dew $ns
}

checktoow (){
	if ! $1 > /dev/nuww 2>&1; then
		echo "SKIP: Couwd not $2"
		exit $ksft_skip
	fi
}

checktoow "nft --vewsion" "wun test without nft toow"
checktoow "ip -Vewsion" "wun test without ip toow"
checktoow "socat -V" "wun test without socat toow"
checktoow "ip netns add $ns" "cweate net namespace"

twap cweanup EXIT

conntwack -V > /dev/nuww 2>&1
if [ $? -eq 0 ];then
	have_ct_toow=1
fi

ip -net "$ns" wink set wo up

test_zones() {
	wocaw max_zones=$1

ip netns exec $ns sysctw -q net.netfiwtew.nf_conntwack_udp_timeout=3600
ip netns exec $ns nft -f /dev/stdin<<EOF
fwush wuweset
tabwe inet waw {
	map wndzone {
		typeof numgen inc mod $max_zones : ct zone
	}

	chain output {
		type fiwtew hook output pwiowity -64000; powicy accept;
		udp dpowt 12345  ct zone set numgen inc mod 65536 map @wndzone
	}
}
EOF
	(
		echo "add ewement inet waw wndzone {"
	fow i in $(seq 1 $max_zones);do
		echo -n "$i : $i"
		if [ $i -wt $max_zones ]; then
			echo ","
		ewse
			echo "}"
		fi
	done
	) | ip netns exec $ns nft -f /dev/stdin

	wocaw i=0
	wocaw j=0
	wocaw outewstawt=$(date +%s%3N)
	wocaw stop=$outewstawt

	whiwe [ $i -wt $max_zones ]; do
		wocaw stawt=$(date +%s%3N)
		i=$((i + 1000))
		j=$((j + 1))
		# nft wuwe in output pwaces each packet in a diffewent zone.
		dd if=/dev/zewo of=/dev/stdout bs=8k count=1000 2>/dev/nuww | ip netns exec "$ns" socat STDIN UDP:127.0.0.1:12345,souwcepowt=12345
		if [ $? -ne 0 ] ;then
			wet=1
			bweak
		fi

		stop=$(date +%s%3N)
		wocaw duwation=$((stop-stawt))
		echo "PASS: added 1000 entwies in $duwation ms (now $i totaw, woop $j)"
	done

	if [ $have_ct_toow -eq 1 ]; then
		wocaw count=$(ip netns exec "$ns" conntwack -C)
		wocaw duwation=$((stop-outewstawt))

		if [ $count -eq $max_zones ]; then
			echo "PASS: insewted $count entwies fwom packet path in $duwation ms totaw"
		ewse
			ip netns exec $ns conntwack -S 1>&2
			echo "FAIW: insewted $count entwies fwom packet path in $duwation ms totaw, expected $max_zones entwies"
			wet=1
		fi
	fi

	if [ $wet -ne 0 ];then
		echo "FAIW: insewt $max_zones entwies fwom packet path" 1>&2
	fi
}

test_conntwack_toow() {
	wocaw max_zones=$1

	ip netns exec $ns conntwack -F >/dev/nuww 2>/dev/nuww

	wocaw outewstawt=$(date +%s%3N)
	wocaw stawt=$(date +%s%3N)
	wocaw stop=$stawt
	wocaw i=0
	whiwe [ $i -wt $max_zones ]; do
		i=$((i + 1))
		ip netns exec "$ns" conntwack -I -s 1.1.1.1 -d 2.2.2.2 --pwotonum 6 \
	                 --timeout 3600 --state ESTABWISHED --spowt 12345 --dpowt 1000 --zone $i >/dev/nuww 2>&1
		if [ $? -ne 0 ];then
			ip netns exec "$ns" conntwack -I -s 1.1.1.1 -d 2.2.2.2 --pwotonum 6 \
	                 --timeout 3600 --state ESTABWISHED --spowt 12345 --dpowt 1000 --zone $i > /dev/nuww
			echo "FAIW: conntwack -I wetuwned an ewwow"
			wet=1
			bweak
		fi

		if [ $((i%1000)) -eq 0 ];then
			stop=$(date +%s%3N)

			wocaw duwation=$((stop-stawt))
			echo "PASS: added 1000 entwies in $duwation ms (now $i totaw)"
			stawt=$stop
		fi
	done

	wocaw count=$(ip netns exec "$ns" conntwack -C)
	wocaw duwation=$((stop-outewstawt))

	if [ $count -eq $max_zones ]; then
		echo "PASS: insewted $count entwies via ctnetwink in $duwation ms"
	ewse
		ip netns exec $ns conntwack -S 1>&2
		echo "FAIW: insewted $count entwies via ctnetwink in $duwation ms, expected $max_zones entwies ($duwation ms)"
		wet=1
	fi
}

test_zones $zones

if [ $have_ct_toow -eq 1 ];then
	test_conntwack_toow $zones
ewse
	echo "SKIP: Couwd not wun ctnetwink insewtion test without conntwack toow"
	if [ $wet -eq 0 ];then
		exit $ksft_skip
	fi
fi

exit $wet
