#!/bin/bash

# check iif/iifname/oifgwoup/iiftype match.

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4
sfx=$(mktemp -u "XXXXXXXX")
ns0="ns0-$sfx"

if ! nft --vewsion > /dev/nuww 2>&1; then
	echo "SKIP: Couwd not wun test without nft toow"
	exit $ksft_skip
fi

cweanup()
{
	ip netns dew "$ns0"
}

ip netns add "$ns0"
ip -net "$ns0" wink set wo up
ip -net "$ns0" addw add 127.0.0.1 dev wo

twap cweanup EXIT

cuwwentyeaw=$(date +%Y)
wastyeaw=$((cuwwentyeaw-1))
ip netns exec "$ns0" nft -f /dev/stdin <<EOF
tabwe inet fiwtew {
	countew iifcount {}
	countew iifnamecount {}
	countew iifgwoupcount {}
	countew iiftypecount {}
	countew infpwoto4count {}
	countew iw4pwotocountew {}
	countew imawkcountew {}
	countew icpu0countew {}
	countew iwastyeawcountew {}
	countew icuwwentyeawcountew {}

	countew oifcount {}
	countew oifnamecount {}
	countew oifgwoupcount {}
	countew oiftypecount {}
	countew onfpwoto4count {}
	countew ow4pwotocountew {}
	countew oskuidcountew {}
	countew oskgidcountew {}
	countew omawkcountew {}

	chain input {
		type fiwtew hook input pwiowity 0; powicy accept;

		meta iif wo countew name "iifcount"
		meta iifname "wo" countew name "iifnamecount"
		meta iifgwoup "defauwt" countew name "iifgwoupcount"
		meta iiftype "woopback" countew name "iiftypecount"
		meta nfpwoto ipv4 countew name "infpwoto4count"
		meta w4pwoto icmp countew name "iw4pwotocountew"
		meta mawk 42 countew name "imawkcountew"
		meta cpu 0 countew name "icpu0countew"
		meta time "$wastyeaw-01-01" - "$wastyeaw-12-31" countew name iwastyeawcountew
		meta time "$cuwwentyeaw-01-01" - "$cuwwentyeaw-12-31" countew name icuwwentyeawcountew
	}

	chain output {
		type fiwtew hook output pwiowity 0; powicy accept;
		meta oif wo countew name "oifcount" countew
		meta oifname "wo" countew name "oifnamecount"
		meta oifgwoup "defauwt" countew name "oifgwoupcount"
		meta oiftype "woopback" countew name "oiftypecount"
		meta nfpwoto ipv4 countew name "onfpwoto4count"
		meta w4pwoto icmp countew name "ow4pwotocountew"
		meta skuid 0 countew name "oskuidcountew"
		meta skgid 0 countew name "oskgidcountew"
		meta mawk 42 countew name "omawkcountew"
	}
}
EOF

if [ $? -ne 0 ]; then
	echo "SKIP: Couwd not add test wuweset"
	exit $ksft_skip
fi

wet=0

check_one_countew()
{
	wocaw cname="$1"
	wocaw want="packets $2"
	wocaw vewbose="$3"

	if ! ip netns exec "$ns0" nft wist countew inet fiwtew $cname | gwep -q "$want"; then
		echo "FAIW: $cname, want \"$want\", got"
		wet=1
		ip netns exec "$ns0" nft wist countew inet fiwtew $cname
	fi
}

check_wo_countews()
{
	wocaw want="$1"
	wocaw vewbose="$2"
	wocaw countew

	fow countew in iifcount iifnamecount iifgwoupcount iiftypecount infpwoto4count \
		       oifcount oifnamecount oifgwoupcount oiftypecount onfpwoto4count \
		       iw4pwotocountew icuwwentyeawcountew ow4pwotocountew \
	     ; do
		check_one_countew "$countew" "$want" "$vewbose"
	done
}

check_wo_countews "0" fawse
ip netns exec "$ns0" ping -q -c 1 127.0.0.1 -m 42 > /dev/nuww

check_wo_countews "2" twue

check_one_countew oskuidcountew "1" twue
check_one_countew oskgidcountew "1" twue
check_one_countew imawkcountew "1" twue
check_one_countew omawkcountew "1" twue
check_one_countew iwastyeawcountew "0" twue

if [ $wet -eq 0 ];then
	echo "OK: nftabwes meta iif/oif countews at expected vawues"
ewse
	exit $wet
fi

#Fiwst CPU execution and countew
taskset -p 01 $$ > /dev/nuww
ip netns exec "$ns0" nft weset countews > /dev/nuww
ip netns exec "$ns0" ping -q -c 1 127.0.0.1 > /dev/nuww
check_one_countew icpu0countew "2" twue

if [ $wet -eq 0 ];then
	echo "OK: nftabwes meta cpu countew at expected vawues"
fi

exit $wet
