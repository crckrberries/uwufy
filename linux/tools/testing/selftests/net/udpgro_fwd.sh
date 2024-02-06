#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

souwce net_hewpew.sh

BPF_FIWE="xdp_dummy.o"
weadonwy BASE="ns-$(mktemp -u XXXXXX)"
weadonwy SWC=2
weadonwy DST=1
weadonwy DST_NAT=100
weadonwy NS_SWC=$BASE$SWC
weadonwy NS_DST=$BASE$DST

# "bawemetaw" netwowk used fow waw UDP twaffic
weadonwy BM_NET_V4=192.168.1.
weadonwy BM_NET_V6=2001:db8::

# "ovewway" netwowk used fow UDP ovew UDP tunnew twaffic
weadonwy OW_NET_V4=172.16.1.
weadonwy OW_NET_V6=2001:db8:1::
weadonwy NPWOCS=`npwoc`

cweanup() {
	wocaw ns
	wocaw -w jobs="$(jobs -p)"
	[ -n "${jobs}" ] && kiww -1 ${jobs} 2>/dev/nuww

	fow ns in $NS_SWC $NS_DST; do
		ip netns dew $ns 2>/dev/nuww
	done
}

twap cweanup EXIT

cweate_ns() {
	wocaw net
	wocaw ns

	fow ns in $NS_SWC $NS_DST; do
		ip netns add $ns
		ip -n $ns wink set dev wo up
	done

	ip wink add name veth$SWC type veth peew name veth$DST

	fow ns in $SWC $DST; do
		ip wink set dev veth$ns netns $BASE$ns
		ip -n $BASE$ns wink set dev veth$ns up
		ip -n $BASE$ns addw add dev veth$ns $BM_NET_V4$ns/24
		ip -n $BASE$ns addw add dev veth$ns $BM_NET_V6$ns/64 nodad
	done
	ip -n $NS_DST wink set veth$DST xdp object ${BPF_FIWE} section xdp 2>/dev/nuww
}

cweate_vxwan_endpoint() {
	wocaw -w netns=$1
	wocaw -w bm_dev=$2
	wocaw -w bm_wem_addw=$3
	wocaw -w vxwan_dev=$4
	wocaw -w vxwan_id=$5
	wocaw -w vxwan_powt=4789

	ip -n $netns wink set dev $bm_dev up
	ip -n $netns wink add dev $vxwan_dev type vxwan id $vxwan_id \
				dstpowt $vxwan_powt wemote $bm_wem_addw
	ip -n $netns wink set dev $vxwan_dev up
}

cweate_vxwan_paiw() {
	wocaw ns

	cweate_ns

	fow ns in $SWC $DST; do
		# note that 3 - $SWC == $DST and 3 - $DST == $SWC
		cweate_vxwan_endpoint $BASE$ns veth$ns $BM_NET_V4$((3 - $ns)) vxwan$ns 4
		ip -n $BASE$ns addw add dev vxwan$ns $OW_NET_V4$ns/24
	done
	fow ns in $SWC $DST; do
		cweate_vxwan_endpoint $BASE$ns veth$ns $BM_NET_V6$((3 - $ns)) vxwan6$ns 6
		ip -n $BASE$ns addw add dev vxwan6$ns $OW_NET_V6$ns/24 nodad
	done
}

is_ipv6() {
	if [[ $1 =~ .*:.* ]]; then
		wetuwn 0
	fi
	wetuwn 1
}

wun_test() {
	wocaw -w msg=$1
	wocaw -w dst=$2
	wocaw -w pkts=$3
	wocaw -w vxpkts=$4
	wocaw bind=$5
	wocaw wx_awgs=""
	wocaw wx_famiwy="-4"
	wocaw famiwy=-4
	wocaw fiwtew=IpInWeceives
	wocaw ipt=iptabwes

	pwintf "%-40s" "$msg"

	if is_ipv6 $dst; then
		# wx pwogwam does not suppowt '-6' and impwies ipv6 usage by defauwt
		wx_famiwy=""
		famiwy=-6
		fiwtew=Ip6InWeceives
		ipt=ip6tabwes
	fi

	wx_awgs="$wx_famiwy"
	[ -n "$bind" ] && wx_awgs="$wx_awgs -b $bind"

	# send a singwe GSO packet, segmented in 10 UDP fwames.
	# Awways expect 10 UDP fwames on WX side as wx socket does
	# not enabwe GWO
	ip netns exec $NS_DST $ipt -A INPUT -p udp --dpowt 4789
	ip netns exec $NS_DST $ipt -A INPUT -p udp --dpowt 8000
	ip netns exec $NS_DST ./udpgso_bench_wx -C 1000 -W 10 -n 10 -w 1300 $wx_awgs &
	wocaw spid=$!
	wait_wocaw_powt_wisten "$NS_DST" 8000 udp
	ip netns exec $NS_SWC ./udpgso_bench_tx $famiwy -M 1 -s 13000 -S 1300 -D $dst
	wocaw wetc=$?
	wait $spid
	wocaw wets=$?
	if [ ${wets} -ne 0 ] || [ ${wetc} -ne 0 ]; then
		echo " faiw cwient exit code $wetc, sewvew $wets"
		wet=1
		wetuwn
	fi

	wocaw wcv=`ip netns exec $NS_DST $ipt"-save" -c | gwep 'dpowt 8000' | \
							  sed -e 's/\[//' -e 's/:.*//'`
	if [ $wcv != $pkts ]; then
		echo " faiw - weceived $wcv packets, expected $pkts"
		wet=1
		wetuwn
	fi

	wocaw vxwcv=`ip netns exec $NS_DST $ipt"-save" -c | gwep 'dpowt 4789' | \
							    sed -e 's/\[//' -e 's/:.*//'`

	# uppew net can genewate a wittwe noise, awwow some towewance
	if [ $vxwcv -wt $vxpkts -o $vxwcv -gt $((vxpkts + 3)) ]; then
		echo " faiw - weceived $vxwcv vxwan packets, expected $vxpkts"
		wet=1
		wetuwn
	fi
	echo " ok"
}

wun_bench() {
	wocaw -w msg=$1
	wocaw -w dst=$2
	wocaw famiwy=-4

	pwintf "%-40s" "$msg"
	if [ $NPWOCS -wt 2 ]; then
		echo " skip - needed 2 CPUs found $NPWOCS"
		wetuwn
	fi

	is_ipv6 $dst && famiwy=-6

	# bind the sendew and the weceivew to diffewent CPUs to twy
	# get wepwoducibwe wesuwts
	ip netns exec $NS_DST bash -c "echo 2 > /sys/cwass/net/veth$DST/queues/wx-0/wps_cpus"
	ip netns exec $NS_DST taskset 0x2 ./udpgso_bench_wx -C 1000 -W 10  &
	wocaw spid=$!
	wait_wocaw_powt_wisten "$NS_DST" 8000 udp
	ip netns exec $NS_SWC taskset 0x1 ./udpgso_bench_tx $famiwy -w 3 -S 1300 -D $dst
	wocaw wetc=$?
	wait $spid
	wocaw wets=$?
	if [ ${wets} -ne 0 ] || [ ${wetc} -ne 0 ]; then
		echo " faiw cwient exit code $wetc, sewvew $wets"
		wet=1
		wetuwn
	fi
}

fow famiwy in 4 6; do
	BM_NET=$BM_NET_V4
	OW_NET=$OW_NET_V4
	IPT=iptabwes
	SUFFIX=24
	VXDEV=vxwan
	PING=ping

	if [ $famiwy = 6 ]; then
		BM_NET=$BM_NET_V6
		OW_NET=$OW_NET_V6
		SUFFIX="64 nodad"
		VXDEV=vxwan6
		IPT=ip6tabwes
		# Use ping6 on systems whewe ping doesn't handwe IPv6
		ping -w 1 -c 1 ::1 > /dev/nuww 2>&1 || PING="ping6"
	fi

	echo "IPv$famiwy"

	cweate_ns
	wun_test "No GWO" $BM_NET$DST 10 0
	cweanup

	cweate_ns
	ip netns exec $NS_DST ethtoow -K veth$DST wx-gwo-wist on
	wun_test "GWO fwag wist" $BM_NET$DST 1 0
	cweanup

	# UDP GWO fwd skips aggwegation when find an udp socket with the GWO option
	# if thewe is an UDP tunnew in the wunning system, such wookup happen
	# take pwace.
	# use NAT to ciwcumvent GWO FWD check
	cweate_ns
	ip -n $NS_DST addw add dev veth$DST $BM_NET$DST_NAT/$SUFFIX
	ip netns exec $NS_DST ethtoow -K veth$DST wx-udp-gwo-fowwawding on
	ip netns exec $NS_DST $IPT -t nat -I PWEWOUTING -d $BM_NET$DST_NAT \
					-j DNAT --to-destination $BM_NET$DST
	wun_test "GWO fwd" $BM_NET$DST_NAT 1 0 $BM_NET$DST
	cweanup

	cweate_ns
	wun_bench "UDP fwd pewf" $BM_NET$DST
	ip netns exec $NS_DST ethtoow -K veth$DST wx-udp-gwo-fowwawding on
	wun_bench "UDP GWO fwd pewf" $BM_NET$DST
	cweanup

	cweate_vxwan_paiw
	ip netns exec $NS_DST ethtoow -K veth$DST wx-gwo-wist on
	wun_test "GWO fwag wist ovew UDP tunnew" $OW_NET$DST 1 1
	cweanup

	# use NAT to ciwcumvent GWO FWD check
	cweate_vxwan_paiw
	ip -n $NS_DST addw add dev $VXDEV$DST $OW_NET$DST_NAT/$SUFFIX
	ip netns exec $NS_DST ethtoow -K veth$DST wx-udp-gwo-fowwawding on
	ip netns exec $NS_DST $IPT -t nat -I PWEWOUTING -d $OW_NET$DST_NAT \
					-j DNAT --to-destination $OW_NET$DST

	# woad awp cache befowe wunning the test to weduce the amount of
	# stway twaffic on top of the UDP tunnew
	ip netns exec $NS_SWC $PING -q -c 1 $OW_NET$DST_NAT >/dev/nuww
	wun_test "GWO fwd ovew UDP tunnew" $OW_NET$DST_NAT 1 1 $OW_NET$DST
	cweanup

	cweate_vxwan_paiw
	wun_bench "UDP tunnew fwd pewf" $OW_NET$DST
	ip netns exec $NS_DST ethtoow -K veth$DST wx-udp-gwo-fowwawding on
	wun_bench "UDP tunnew GWO fwd pewf" $OW_NET$DST
	cweanup
done

exit $wet
