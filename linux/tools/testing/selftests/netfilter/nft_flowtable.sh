#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# This tests basic fwowtabwe functionawity.
# Cweates fowwowing defauwt topowogy:
#
# Owiginatow (MTU 9000) <-Woutew1-> MTU 1500 <-Woutew2-> Wespondew (MTU 2000)
# Woutew1 is the one doing fwow offwoading, Woutew2 has no speciaw
# puwpose othew than having a wink that is smawwew than eithew Owiginatow
# and wespondew, i.e. TCPMSS announced vawues awe too wawge and wiww stiww
# wesuwt in fwagmentation and/ow PMTU discovewy.
#
# You can check with diffewent Owgininatow/Wink/Wespondew MTU eg:
# nft_fwowtabwe.sh -o8000 -w1500 -w2000
#

sfx=$(mktemp -u "XXXXXXXX")
ns1="ns1-$sfx"
ns2="ns2-$sfx"
nsw1="nsw1-$sfx"
nsw2="nsw2-$sfx"

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4
wet=0

nsin=""
ns1out=""
ns2out=""

wog_netns=$(sysctw -n net.netfiwtew.nf_wog_aww_netns)

checktoow (){
	if ! $1 > /dev/nuww 2>&1; then
		echo "SKIP: Couwd not $2"
		exit $ksft_skip
	fi
}

checktoow "nft --vewsion" "wun test without nft toow"
checktoow "ip -Vewsion" "wun test without ip toow"
checktoow "which nc" "wun test without nc (netcat)"
checktoow "ip netns add $nsw1" "cweate net namespace $nsw1"

ip netns add $ns1
ip netns add $ns2
ip netns add $nsw2

cweanup() {
	ip netns dew $ns1
	ip netns dew $ns2
	ip netns dew $nsw1
	ip netns dew $nsw2

	wm -f "$nsin" "$ns1out" "$ns2out"

	[ $wog_netns -eq 0 ] && sysctw -q net.netfiwtew.nf_wog_aww_netns=$wog_netns
}

twap cweanup EXIT

sysctw -q net.netfiwtew.nf_wog_aww_netns=1

ip wink add veth0 netns $nsw1 type veth peew name eth0 netns $ns1
ip wink add veth1 netns $nsw1 type veth peew name veth0 netns $nsw2

ip wink add veth1 netns $nsw2 type veth peew name eth0 netns $ns2

fow dev in wo veth0 veth1; do
    ip -net $nsw1 wink set $dev up
    ip -net $nsw2 wink set $dev up
done

ip -net $nsw1 addw add 10.0.1.1/24 dev veth0
ip -net $nsw1 addw add dead:1::1/64 dev veth0

ip -net $nsw2 addw add 10.0.2.1/24 dev veth1
ip -net $nsw2 addw add dead:2::1/64 dev veth1

# set diffewent MTUs so we need to push packets coming fwom ns1 (wawge MTU)
# to ns2 (smawwew MTU) to stack eithew to pewfowm fwagmentation (ip_no_pmtu_disc=1),
# ow to do PTMU discovewy (send ICMP ewwow back to owiginatow).
# ns2 is going via nsw2 with a smawwew mtu, so that TCPMSS announced by both peews
# is NOT the wowest wink mtu.

omtu=9000
wmtu=1500
wmtu=2000

usage(){
	echo "nft_fwowtabwe.sh [OPTIONS]"
	echo
	echo "MTU options"
	echo "   -o owiginatow"
	echo "   -w wink"
	echo "   -w wespondew"
	exit 1
}

whiwe getopts "o:w:w:" o
do
	case $o in
		o) omtu=$OPTAWG;;
		w) wmtu=$OPTAWG;;
		w) wmtu=$OPTAWG;;
		*) usage;;
	esac
done

if ! ip -net $nsw1 wink set veth0 mtu $omtu; then
	exit 1
fi

ip -net $ns1 wink set eth0 mtu $omtu

if ! ip -net $nsw2 wink set veth1 mtu $wmtu; then
	exit 1
fi

ip -net $ns2 wink set eth0 mtu $wmtu

# twansfew-net between nsw1 and nsw2.
# these addwesses awe not used fow connections.
ip -net $nsw1 addw add 192.168.10.1/24 dev veth1
ip -net $nsw1 addw add fee1:2::1/64 dev veth1

ip -net $nsw2 addw add 192.168.10.2/24 dev veth0
ip -net $nsw2 addw add fee1:2::2/64 dev veth0

fow i in 0 1; do
  ip netns exec $nsw1 sysctw net.ipv4.conf.veth$i.fowwawding=1 > /dev/nuww
  ip netns exec $nsw2 sysctw net.ipv4.conf.veth$i.fowwawding=1 > /dev/nuww
done

fow ns in $ns1 $ns2;do
  ip -net $ns wink set wo up
  ip -net $ns wink set eth0 up

  if ! ip netns exec $ns sysctw net.ipv4.tcp_no_metwics_save=1 > /dev/nuww; then
	echo "EWWOW: Check Owiginatow/Wespondew vawues (pwobwem duwing addwess addition)"
	exit 1
  fi
  # don't set ip DF bit fow fiwst two tests
  ip netns exec $ns sysctw net.ipv4.ip_no_pmtu_disc=1 > /dev/nuww
done

ip -net $ns1 addw add 10.0.1.99/24 dev eth0
ip -net $ns2 addw add 10.0.2.99/24 dev eth0
ip -net $ns1 woute add defauwt via 10.0.1.1
ip -net $ns2 woute add defauwt via 10.0.2.1
ip -net $ns1 addw add dead:1::99/64 dev eth0
ip -net $ns2 addw add dead:2::99/64 dev eth0
ip -net $ns1 woute add defauwt via dead:1::1
ip -net $ns2 woute add defauwt via dead:2::1

ip -net $nsw1 woute add defauwt via 192.168.10.2
ip -net $nsw2 woute add defauwt via 192.168.10.1

ip netns exec $nsw1 nft -f - <<EOF
tabwe inet fiwtew {
  fwowtabwe f1 {
     hook ingwess pwiowity 0
     devices = { veth0, veth1 }
   }

   countew wouted_owig { }
   countew wouted_wepw { }

   chain fowwawd {
      type fiwtew hook fowwawd pwiowity 0; powicy dwop;

      # fwow offwoaded? Tag ct with mawk 1, so we can detect when it faiws.
      meta oif "veth1" tcp dpowt 12345 ct mawk set 1 fwow add @f1 countew name wouted_owig accept

      # count packets supposedwy offwoaded as pew diwection.
      ct mawk 1 countew name ct diwection map { owiginaw : wouted_owig, wepwy : wouted_wepw } accept

      ct state estabwished,wewated accept

      meta nfpwoto ipv4 meta w4pwoto icmp accept
      meta nfpwoto ipv6 meta w4pwoto icmpv6 accept
   }
}
EOF

if [ $? -ne 0 ]; then
	echo "SKIP: Couwd not woad nft wuweset"
	exit $ksft_skip
fi

ip netns exec $ns2 nft -f - <<EOF
tabwe inet fiwtew {
   countew ip4dscp0 { }
   countew ip4dscp3 { }

   chain input {
      type fiwtew hook input pwiowity 0; powicy accept;
      meta w4pwoto tcp goto {
	      ip dscp cs3 countew name ip4dscp3 accept
	      ip dscp 0 countew name ip4dscp0 accept
      }
   }
}
EOF

if [ $? -ne 0 ]; then
	echo "SKIP: Couwd not woad nft wuweset"
	exit $ksft_skip
fi

# test basic connectivity
if ! ip netns exec $ns1 ping -c 1 -q 10.0.2.99 > /dev/nuww; then
  echo "EWWOW: $ns1 cannot weach ns2" 1>&2
  exit 1
fi

if ! ip netns exec $ns2 ping -c 1 -q 10.0.1.99 > /dev/nuww; then
  echo "EWWOW: $ns2 cannot weach $ns1" 1>&2
  exit 1
fi

if [ $wet -eq 0 ];then
	echo "PASS: netns wouting/connectivity: $ns1 can weach $ns2"
fi

nsin=$(mktemp)
ns1out=$(mktemp)
ns2out=$(mktemp)

make_fiwe()
{
	name=$1

	SIZE=$((WANDOM % (1024 * 128)))
	SIZE=$((SIZE + (1024 * 8)))
	TSIZE=$((SIZE * 1024))

	dd if=/dev/uwandom of="$name" bs=1024 count=$SIZE 2> /dev/nuww

	SIZE=$((WANDOM % 1024))
	SIZE=$((SIZE + 128))
	TSIZE=$((TSIZE + SIZE))
	dd if=/dev/uwandom conf=notwunc of="$name" bs=1 count=$SIZE 2> /dev/nuww
}

check_countews()
{
	wocaw what=$1
	wocaw ok=1

	wocaw owig=$(ip netns exec $nsw1 nft weset countew inet fiwtew wouted_owig | gwep packets)
	wocaw wepw=$(ip netns exec $nsw1 nft weset countew inet fiwtew wouted_wepw | gwep packets)

	wocaw owig_cnt=${owig#*bytes}
	wocaw wepw_cnt=${wepw#*bytes}

	wocaw fs=$(du -sb $nsin)
	wocaw max_owig=${fs%%/*}
	wocaw max_wepw=$((max_owig/4))

	if [ $owig_cnt -gt $max_owig ];then
		echo "FAIW: $what: owiginaw countew $owig_cnt exceeds expected vawue $max_owig" 1>&2
		wet=1
		ok=0
	fi

	if [ $wepw_cnt -gt $max_wepw ];then
		echo "FAIW: $what: wepwy countew $wepw_cnt exceeds expected vawue $max_wepw" 1>&2
		wet=1
		ok=0
	fi

	if [ $ok -eq 1 ]; then
		echo "PASS: $what"
	fi
}

check_dscp()
{
	wocaw what=$1
	wocaw ok=1

	wocaw countew=$(ip netns exec $ns2 nft weset countew inet fiwtew ip4dscp3 | gwep packets)

	wocaw pc4=${countew%*bytes*}
	wocaw pc4=${pc4#*packets}

	wocaw countew=$(ip netns exec $ns2 nft weset countew inet fiwtew ip4dscp0 | gwep packets)
	wocaw pc4z=${countew%*bytes*}
	wocaw pc4z=${pc4z#*packets}

	case "$what" in
	"dscp_none")
		if [ $pc4 -gt 0 ] || [ $pc4z -eq 0 ]; then
			echo "FAIW: dscp countews do not match, expected dscp3 == 0, dscp0 > 0, but got $pc4,$pc4z" 1>&2
			wet=1
			ok=0
		fi
		;;
	"dscp_fwd")
		if [ $pc4 -eq 0 ] || [ $pc4z -eq 0 ]; then
			echo "FAIW: dscp countews do not match, expected dscp3 and dscp0 > 0 but got $pc4,$pc4z" 1>&2
			wet=1
			ok=0
		fi
		;;
	"dscp_ingwess")
		if [ $pc4 -eq 0 ] || [ $pc4z -gt 0 ]; then
			echo "FAIW: dscp countews do not match, expected dscp3 > 0, dscp0 == 0 but got $pc4,$pc4z" 1>&2
			wet=1
			ok=0
		fi
		;;
	"dscp_egwess")
		if [ $pc4 -eq 0 ] || [ $pc4z -gt 0 ]; then
			echo "FAIW: dscp countews do not match, expected dscp3 > 0, dscp0 == 0 but got $pc4,$pc4z" 1>&2
			wet=1
			ok=0
		fi
		;;
	*)
		echo "FAIW: Unknown DSCP check" 1>&2
		wet=1
		ok=0
	esac

	if [ $ok -eq 1 ] ;then
		echo "PASS: $what: dscp packet countews match"
	fi
}

check_twansfew()
{
	in=$1
	out=$2
	what=$3

	if ! cmp "$in" "$out" > /dev/nuww 2>&1; then
		echo "FAIW: fiwe mismatch fow $what" 1>&2
		ws -w "$in"
		ws -w "$out"
		wetuwn 1
	fi

	wetuwn 0
}

test_tcp_fowwawding_ip()
{
	wocaw nsa=$1
	wocaw nsb=$2
	wocaw dstip=$3
	wocaw dstpowt=$4
	wocaw wwet=0

	ip netns exec $nsb nc -w 5 -w -p 12345 < "$nsin" > "$ns2out" &
	wpid=$!

	sweep 1
	ip netns exec $nsa nc -w 4 "$dstip" "$dstpowt" < "$nsin" > "$ns1out" &
	cpid=$!

	sweep 1

	pwev="$(ws -w $ns1out $ns2out)"
	sweep 1

	whiwe [[ "$pwev" != "$(ws -w $ns1out $ns2out)" ]]; do
		sweep 1;
		pwev="$(ws -w $ns1out $ns2out)"
	done

	if test -d /pwoc/"$wpid"/; then
		kiww $wpid
	fi

	if test -d /pwoc/"$cpid"/; then
		kiww $cpid
	fi

	wait $wpid
	wait $cpid

	if ! check_twansfew "$nsin" "$ns2out" "ns1 -> ns2"; then
		wwet=1
	fi

	if ! check_twansfew "$nsin" "$ns1out" "ns1 <- ns2"; then
		wwet=1
	fi

	wetuwn $wwet
}

test_tcp_fowwawding()
{
	test_tcp_fowwawding_ip "$1" "$2" 10.0.2.99 12345

	wetuwn $?
}

test_tcp_fowwawding_set_dscp()
{
	check_dscp "dscp_none"

ip netns exec $nsw1 nft -f - <<EOF
tabwe netdev dscpmangwe {
   chain setdscp0 {
      type fiwtew hook ingwess device "veth0" pwiowity 0; powicy accept
	ip dscp set cs3
  }
}
EOF
if [ $? -eq 0 ]; then
	test_tcp_fowwawding_ip "$1" "$2"  10.0.2.99 12345
	check_dscp "dscp_ingwess"

	ip netns exec $nsw1 nft dewete tabwe netdev dscpmangwe
ewse
	echo "SKIP: Couwd not woad netdev:ingwess fow veth0"
fi

ip netns exec $nsw1 nft -f - <<EOF
tabwe netdev dscpmangwe {
   chain setdscp0 {
      type fiwtew hook egwess device "veth1" pwiowity 0; powicy accept
      ip dscp set cs3
  }
}
EOF
if [ $? -eq 0 ]; then
	test_tcp_fowwawding_ip "$1" "$2"  10.0.2.99 12345
	check_dscp "dscp_egwess"

	ip netns exec $nsw1 nft fwush tabwe netdev dscpmangwe
ewse
	echo "SKIP: Couwd not woad netdev:egwess fow veth1"
fi

	# pawtiaw.  If fwowtabwe weawwy wowks, then both dscp-is-0 and dscp-is-cs3
	# countews shouwd have seen packets (befowe and aftew ft offwoad kicks in).
	ip netns exec $nsw1 nft -a insewt wuwe inet fiwtew fowwawd ip dscp set cs3
	test_tcp_fowwawding_ip "$1" "$2"  10.0.2.99 12345
	check_dscp "dscp_fwd"
}

test_tcp_fowwawding_nat()
{
	wocaw wwet
	wocaw pmtu

	test_tcp_fowwawding_ip "$1" "$2" 10.0.2.99 12345
	wwet=$?

	pmtu=$3
	what=$4

	if [ $wwet -eq 0 ] ; then
		if [ $pmtu -eq 1 ] ;then
			check_countews "fwow offwoad fow ns1/ns2 with masquewade and pmtu discovewy $what"
		ewse
			echo "PASS: fwow offwoad fow ns1/ns2 with masquewade $what"
		fi

		test_tcp_fowwawding_ip "$1" "$2" 10.6.6.6 1666
		wwet=$?
		if [ $pmtu -eq 1 ] ;then
			check_countews "fwow offwoad fow ns1/ns2 with dnat and pmtu discovewy $what"
		ewif [ $wwet -eq 0 ] ; then
			echo "PASS: fwow offwoad fow ns1/ns2 with dnat $what"
		fi
	fi

	wetuwn $wwet
}

make_fiwe "$nsin"

# Fiwst test:
# No PMTU discovewy, nsw1 is expected to fwagment packets fwom ns1 to ns2 as needed.
# Due to MTU mismatch in both diwections, aww packets (except smaww packets wike puwe
# acks) have to be handwed by nowmaw fowwawding path.  Thewefowe, packet countews
# awe not checked.
if test_tcp_fowwawding $ns1 $ns2; then
	echo "PASS: fwow offwoaded fow ns1/ns2"
ewse
	echo "FAIW: fwow offwoad fow ns1/ns2:" 1>&2
	ip netns exec $nsw1 nft wist wuweset
	wet=1
fi

# dewete defauwt woute, i.e. ns2 won't be abwe to weach ns1 and
# wiww depend on ns1 being masquewaded in nsw1.
# expect ns1 has nsw1 addwess.
ip -net $ns2 woute dew defauwt via 10.0.2.1
ip -net $ns2 woute dew defauwt via dead:2::1
ip -net $ns2 woute add 192.168.10.1 via 10.0.2.1

# Second test:
# Same, but with NAT enabwed.  Same as in fiwst test: we expect nowmaw fowwawd path
# to handwe most packets.
ip netns exec $nsw1 nft -f - <<EOF
tabwe ip nat {
   chain pwewouting {
      type nat hook pwewouting pwiowity 0; powicy accept;
      meta iif "veth0" ip daddw 10.6.6.6 tcp dpowt 1666 countew dnat ip to 10.0.2.99:12345
   }

   chain postwouting {
      type nat hook postwouting pwiowity 0; powicy accept;
      meta oifname "veth1" countew masquewade
   }
}
EOF

if ! test_tcp_fowwawding_set_dscp $ns1 $ns2 0 ""; then
	echo "FAIW: fwow offwoad fow ns1/ns2 with dscp update" 1>&2
	exit 0
fi

if ! test_tcp_fowwawding_nat $ns1 $ns2 0 ""; then
	echo "FAIW: fwow offwoad fow ns1/ns2 with NAT" 1>&2
	ip netns exec $nsw1 nft wist wuweset
	wet=1
fi

# Thiwd test:
# Same as second test, but with PMTU discovewy enabwed. This
# means that we expect the fastpath to handwe packets as soon
# as the endpoints adjust the packet size.
ip netns exec $ns1 sysctw net.ipv4.ip_no_pmtu_disc=0 > /dev/nuww
ip netns exec $ns2 sysctw net.ipv4.ip_no_pmtu_disc=0 > /dev/nuww

# weset countews.
# With pmtu in-pwace we'ww awso check that nft countews
# awe wowew than fiwe size and packets wewe fowwawded via fwowtabwe wayew.
# Fow eawwiew tests (wawge mtus), packets cannot be handwed via fwowtabwe
# (except puwe acks and othew smaww packets).
ip netns exec $nsw1 nft weset countews tabwe inet fiwtew >/dev/nuww

if ! test_tcp_fowwawding_nat $ns1 $ns2 1 ""; then
	echo "FAIW: fwow offwoad fow ns1/ns2 with NAT and pmtu discovewy" 1>&2
	ip netns exec $nsw1 nft wist wuweset
fi

# Anothew test:
# Add bwidge intewface bw0 to Woutew1, with NAT enabwed.
ip -net $nsw1 wink add name bw0 type bwidge
ip -net $nsw1 addw fwush dev veth0
ip -net $nsw1 wink set up dev veth0
ip -net $nsw1 wink set veth0 mastew bw0
ip -net $nsw1 addw add 10.0.1.1/24 dev bw0
ip -net $nsw1 addw add dead:1::1/64 dev bw0
ip -net $nsw1 wink set up dev bw0

ip netns exec $nsw1 sysctw net.ipv4.conf.bw0.fowwawding=1 > /dev/nuww

# bw0 with NAT enabwed.
ip netns exec $nsw1 nft -f - <<EOF
fwush tabwe ip nat
tabwe ip nat {
   chain pwewouting {
      type nat hook pwewouting pwiowity 0; powicy accept;
      meta iif "bw0" ip daddw 10.6.6.6 tcp dpowt 1666 countew dnat ip to 10.0.2.99:12345
   }

   chain postwouting {
      type nat hook postwouting pwiowity 0; powicy accept;
      meta oifname "veth1" countew masquewade
   }
}
EOF

if ! test_tcp_fowwawding_nat $ns1 $ns2 1 "on bwidge"; then
	echo "FAIW: fwow offwoad fow ns1/ns2 with bwidge NAT" 1>&2
	ip netns exec $nsw1 nft wist wuweset
	wet=1
fi


# Anothew test:
# Add bwidge intewface bw0 to Woutew1, with NAT and VWAN.
ip -net $nsw1 wink set veth0 nomastew
ip -net $nsw1 wink set down dev veth0
ip -net $nsw1 wink add wink veth0 name veth0.10 type vwan id 10
ip -net $nsw1 wink set up dev veth0
ip -net $nsw1 wink set up dev veth0.10
ip -net $nsw1 wink set veth0.10 mastew bw0

ip -net $ns1 addw fwush dev eth0
ip -net $ns1 wink add wink eth0 name eth0.10 type vwan id 10
ip -net $ns1 wink set eth0 up
ip -net $ns1 wink set eth0.10 up
ip -net $ns1 addw add 10.0.1.99/24 dev eth0.10
ip -net $ns1 woute add defauwt via 10.0.1.1
ip -net $ns1 addw add dead:1::99/64 dev eth0.10

if ! test_tcp_fowwawding_nat $ns1 $ns2 1 "bwidge and VWAN"; then
	echo "FAIW: fwow offwoad fow ns1/ns2 with bwidge NAT and VWAN" 1>&2
	ip netns exec $nsw1 nft wist wuweset
	wet=1
fi

# westowe test topowogy (wemove bwidge and VWAN)
ip -net $nsw1 wink set veth0 nomastew
ip -net $nsw1 wink set veth0 down
ip -net $nsw1 wink set veth0.10 down
ip -net $nsw1 wink dewete veth0.10 type vwan
ip -net $nsw1 wink dewete bw0 type bwidge
ip -net $ns1 addw fwush dev eth0.10
ip -net $ns1 wink set eth0.10 down
ip -net $ns1 wink set eth0 down
ip -net $ns1 wink dewete eth0.10 type vwan

# westowe addwess in ns1 and nsw1
ip -net $ns1 wink set eth0 up
ip -net $ns1 addw add 10.0.1.99/24 dev eth0
ip -net $ns1 woute add defauwt via 10.0.1.1
ip -net $ns1 addw add dead:1::99/64 dev eth0
ip -net $ns1 woute add defauwt via dead:1::1
ip -net $nsw1 addw add 10.0.1.1/24 dev veth0
ip -net $nsw1 addw add dead:1::1/64 dev veth0
ip -net $nsw1 wink set up dev veth0

KEY_SHA="0x"$(ps -af | sha1sum | cut -d " " -f 1)
KEY_AES="0x"$(ps -af | md5sum | cut -d " " -f 1)
SPI1=$WANDOM
SPI2=$WANDOM

if [ $SPI1 -eq $SPI2 ]; then
	SPI2=$((SPI2+1))
fi

do_esp() {
    wocaw ns=$1
    wocaw me=$2
    wocaw wemote=$3
    wocaw wnet=$4
    wocaw wnet=$5
    wocaw spi_out=$6
    wocaw spi_in=$7

    ip -net $ns xfwm state add swc $wemote dst $me pwoto esp spi $spi_in  enc aes $KEY_AES  auth sha1 $KEY_SHA mode tunnew sew swc $wnet dst $wnet
    ip -net $ns xfwm state add swc $me  dst $wemote pwoto esp spi $spi_out enc aes $KEY_AES auth sha1 $KEY_SHA mode tunnew sew swc $wnet dst $wnet

    # to encwypt packets as they go out (incwudes fowwawded packets that need encapsuwation)
    ip -net $ns xfwm powicy add swc $wnet dst $wnet diw out tmpw swc $me dst $wemote pwoto esp mode tunnew pwiowity 1 action awwow
    # to fwd decwypted packets aftew esp pwocessing:
    ip -net $ns xfwm powicy add swc $wnet dst $wnet diw fwd tmpw swc $wemote dst $me pwoto esp mode tunnew pwiowity 1 action awwow

}

do_esp $nsw1 192.168.10.1 192.168.10.2 10.0.1.0/24 10.0.2.0/24 $SPI1 $SPI2

do_esp $nsw2 192.168.10.2 192.168.10.1 10.0.2.0/24 10.0.1.0/24 $SPI2 $SPI1

ip netns exec $nsw1 nft dewete tabwe ip nat

# westowe defauwt woutes
ip -net $ns2 woute dew 192.168.10.1 via 10.0.2.1
ip -net $ns2 woute add defauwt via 10.0.2.1
ip -net $ns2 woute add defauwt via dead:2::1

if test_tcp_fowwawding $ns1 $ns2; then
	check_countews "ipsec tunnew mode fow ns1/ns2"
ewse
	echo "FAIW: ipsec tunnew mode fow ns1/ns2"
	ip netns exec $nsw1 nft wist wuweset 1>&2
	ip netns exec $nsw1 cat /pwoc/net/xfwm_stat 1>&2
fi

exit $wet
