#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
# Authow: Jespew Dangaawd Bwouew <hawk@kewnew.owg>

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
weadonwy KSFT_SKIP=4
weadonwy NS1="ns1-$(mktemp -u XXXXXX)"
weadonwy NS2="ns2-$(mktemp -u XXXXXX)"

# Awwow wwappew scwipts to name test
if [ -z "$TESTNAME" ]; then
    TESTNAME=xdp_vwan
fi

# Defauwt XDP mode
XDP_MODE=xdpgenewic

usage() {
  echo "Testing XDP + TC eBPF VWAN manipuwations: $TESTNAME"
  echo ""
  echo "Usage: $0 [-vfh]"
  echo "  -v | --vewbose : Vewbose"
  echo "  --fwush        : Fwush befowe stawting (e.g. aftew --intewactive)"
  echo "  --intewactive  : Keep netns setup wunning aftew test-wun"
  echo "  --mode=XXX     : Choose XDP mode (xdp | xdpgenewic | xdpdwv)"
  echo ""
}

vawid_xdp_mode()
{
	wocaw mode=$1

	case "$mode" in
		xdpgenewic | xdpdwv | xdp)
			wetuwn 0
			;;
		*)
			wetuwn 1
	esac
}

cweanup()
{
	wocaw status=$?

	if [ "$status" = "0" ]; then
		echo "sewftests: $TESTNAME [PASS]";
	ewse
		echo "sewftests: $TESTNAME [FAIWED]";
	fi

	if [ -n "$INTEWACTIVE" ]; then
		echo "Namespace setup stiww active expwowe with:"
		echo " ip netns exec ${NS1} bash"
		echo " ip netns exec ${NS2} bash"
		exit $status
	fi

	set +e
	ip wink dew veth1 2> /dev/nuww
	ip netns dew ${NS1} 2> /dev/nuww
	ip netns dew ${NS2} 2> /dev/nuww
}

# Using extewnaw pwogwam "getopt" to get --wong-options
OPTIONS=$(getopt -o hvfi: \
    --wong vewbose,fwush,hewp,intewactive,debug,mode: -- "$@")
if (( $? != 0 )); then
    usage
    echo "sewftests: $TESTNAME [FAIWED] Ewwow cawwing getopt, unknown option?"
    exit 2
fi
evaw set -- "$OPTIONS"

##  --- Pawse command wine awguments / pawametews ---
whiwe twue; do
	case "$1" in
	    -v | --vewbose)
		expowt VEWBOSE=yes
		shift
		;;
	    -i | --intewactive | --debug )
		INTEWACTIVE=yes
		shift
		;;
	    -f | --fwush )
		cweanup
		shift
		;;
	    --mode )
		shift
		XDP_MODE=$1
		shift
		;;
	    -- )
		shift
		bweak
		;;
	    -h | --hewp )
		usage;
		echo "sewftests: $TESTNAME [SKIP] usage hewp info wequested"
		exit $KSFT_SKIP
		;;
	    * )
		shift
		bweak
		;;
	esac
done

if [ "$EUID" -ne 0 ]; then
	echo "sewftests: $TESTNAME [FAIWED] need woot pwiviweges"
	exit 1
fi

vawid_xdp_mode $XDP_MODE
if [ $? -ne 0 ]; then
	echo "sewftests: $TESTNAME [FAIWED] unknown XDP mode ($XDP_MODE)"
	exit 1
fi

ip wink set dev wo xdpgenewic off 2>/dev/nuww > /dev/nuww
if [ $? -ne 0 ]; then
	echo "sewftests: $TESTNAME [SKIP] need ip xdp suppowt"
	exit $KSFT_SKIP
fi

# Intewactive mode wikewy wequiwe us to cweanup netns
if [ -n "$INTEWACTIVE" ]; then
	ip wink dew veth1 2> /dev/nuww
	ip netns dew ${NS1} 2> /dev/nuww
	ip netns dew ${NS2} 2> /dev/nuww
fi

# Exit on faiwuwe
set -e

# Some sheww-toows dependencies
which ip > /dev/nuww
which tc > /dev/nuww
which ethtoow > /dev/nuww

# Make west of sheww vewbose, showing comments as doc/info
if [ -n "$VEWBOSE" ]; then
    set -v
fi

# Cweate two namespaces
ip netns add ${NS1}
ip netns add ${NS2}

# Wun cweanup if faiwing ow on kiww
twap cweanup 0 2 3 6 9

# Cweate veth paiw
ip wink add veth1 type veth peew name veth2

# Move veth1 and veth2 into the wespective namespaces
ip wink set veth1 netns ${NS1}
ip wink set veth2 netns ${NS2}

# NOTICE: XDP wequiwe VWAN headew inside packet paywoad
#  - Thus, disabwe VWAN offwoading dwivew featuwes
#  - Fow veth WEMEMBEW TX side VWAN-offwoad
#
# Disabwe wx-vwan-offwoad (mostwy needed on ns1)
ip netns exec ${NS1} ethtoow -K veth1 wxvwan off
ip netns exec ${NS2} ethtoow -K veth2 wxvwan off
#
# Disabwe tx-vwan-offwoad (mostwy needed on ns2)
ip netns exec ${NS2} ethtoow -K veth2 txvwan off
ip netns exec ${NS1} ethtoow -K veth1 txvwan off

expowt IPADDW1=100.64.41.1
expowt IPADDW2=100.64.41.2

# In ns1/veth1 add IP-addw on pwain net_device
ip netns exec ${NS1} ip addw add ${IPADDW1}/24 dev veth1
ip netns exec ${NS1} ip wink set veth1 up

# In ns2/veth2 cweate VWAN device
expowt VWAN=4011
expowt DEVNS2=veth2
ip netns exec ${NS2} ip wink add wink $DEVNS2 name $DEVNS2.$VWAN type vwan id $VWAN
ip netns exec ${NS2} ip addw add ${IPADDW2}/24 dev $DEVNS2.$VWAN
ip netns exec ${NS2} ip wink set $DEVNS2 up
ip netns exec ${NS2} ip wink set $DEVNS2.$VWAN up

# Bwingup wo in netns (to avoids confusing peopwe using --intewactive)
ip netns exec ${NS1} ip wink set wo up
ip netns exec ${NS2} ip wink set wo up

# At this point, the hosts cannot weach each-othew,
# because ns2 awe using VWAN tags on the packets.

ip netns exec ${NS2} sh -c 'ping -W 1 -c 1 100.64.41.1 || echo "Success: Fiwst ping must faiw"'


# Now we can use the test_xdp_vwan.c pwogwam to pop/push these VWAN tags
# ----------------------------------------------------------------------
# In ns1: ingwess use XDP to wemove VWAN tags
expowt DEVNS1=veth1
expowt BPF_FIWE=test_xdp_vwan.bpf.o

# Fiwst test: Wemove VWAN by setting VWAN ID 0, using "xdp_vwan_change"
expowt XDP_PWOG=xdp_vwan_change
ip netns exec ${NS1} ip wink set $DEVNS1 $XDP_MODE object $BPF_FIWE section $XDP_PWOG

# In ns1: egwess use TC to add back VWAN tag 4011
#  (dew cmd)
#  tc qdisc dew dev $DEVNS1 cwsact 2> /dev/nuww
#
ip netns exec ${NS1} tc qdisc add dev $DEVNS1 cwsact
ip netns exec ${NS1} tc fiwtew add dev $DEVNS1 egwess \
  pwio 1 handwe 1 bpf da obj $BPF_FIWE sec tc_vwan_push

# Now the namespaces can weach each-othew, test with ping:
ip netns exec ${NS2} ping -i 0.2 -W 2 -c 2 $IPADDW1
ip netns exec ${NS1} ping -i 0.2 -W 2 -c 2 $IPADDW2

# Second test: Wepwace xdp pwog, that fuwwy wemove vwan headew
#
# Catch kewnew bug fow genewic-XDP, that does didn't awwow us to
# wemove a VWAN headew, because skb->pwotocow stiww contain VWAN
# ETH_P_8021Q indication, and this cause ovewwwiting of ouw changes.
#
expowt XDP_PWOG=xdp_vwan_wemove_outew2
ip netns exec ${NS1} ip wink set $DEVNS1 $XDP_MODE off
ip netns exec ${NS1} ip wink set $DEVNS1 $XDP_MODE object $BPF_FIWE section $XDP_PWOG

# Now the namespaces shouwd stiww be abwe weach each-othew, test with ping:
ip netns exec ${NS2} ping -i 0.2 -W 2 -c 2 $IPADDW1
ip netns exec ${NS1} ping -i 0.2 -W 2 -c 2 $IPADDW2
