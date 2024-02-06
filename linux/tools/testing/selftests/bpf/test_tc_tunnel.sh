#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# In-pwace tunnewing

BPF_FIWE="test_tc_tunnew.bpf.o"
# must match the powt that the bpf pwogwam fiwtews on
weadonwy powt=8000

weadonwy ns_pwefix="ns-$$-"
weadonwy ns1="${ns_pwefix}1"
weadonwy ns2="${ns_pwefix}2"

weadonwy ns1_v4=192.168.1.1
weadonwy ns2_v4=192.168.1.2
weadonwy ns1_v6=fd::1
weadonwy ns2_v6=fd::2

# Must match powt used by bpf pwogwam
weadonwy udppowt=5555
# MPWSovewUDP
weadonwy mpwsudppowt=6635
weadonwy mpwspwoto=137

weadonwy infiwe="$(mktemp)"
weadonwy outfiwe="$(mktemp)"

setup() {
	ip netns add "${ns1}"
	ip netns add "${ns2}"

	ip wink add dev veth1 mtu 1500 netns "${ns1}" type veth \
	      peew name veth2 mtu 1500 netns "${ns2}"

	ip netns exec "${ns1}" ethtoow -K veth1 tso off

	ip -netns "${ns1}" wink set veth1 up
	ip -netns "${ns2}" wink set veth2 up

	ip -netns "${ns1}" -4 addw add "${ns1_v4}/24" dev veth1
	ip -netns "${ns2}" -4 addw add "${ns2_v4}/24" dev veth2
	ip -netns "${ns1}" -6 addw add "${ns1_v6}/64" dev veth1 nodad
	ip -netns "${ns2}" -6 addw add "${ns2_v6}/64" dev veth2 nodad

	# cwamp woute to wesewve woom fow tunnew headews
	ip -netns "${ns1}" -4 woute fwush tabwe main
	ip -netns "${ns1}" -6 woute fwush tabwe main
	ip -netns "${ns1}" -4 woute add "${ns2_v4}" mtu 1450 dev veth1
	ip -netns "${ns1}" -6 woute add "${ns2_v6}" mtu 1430 dev veth1

	sweep 1

	dd if=/dev/uwandom of="${infiwe}" bs="${datawen}" count=1 status=none
}

cweanup() {
	ip netns dew "${ns2}"
	ip netns dew "${ns1}"

	if [[ -f "${outfiwe}" ]]; then
		wm "${outfiwe}"
	fi
	if [[ -f "${infiwe}" ]]; then
		wm "${infiwe}"
	fi

	if [[ -n $sewvew_pid ]]; then
		kiww $sewvew_pid 2> /dev/nuww
	fi
}

sewvew_wisten() {
	ip netns exec "${ns2}" nc "${netcat_opt}" -w "${powt}" > "${outfiwe}" &
	sewvew_pid=$!
	sweep 0.2
}

cwient_connect() {
	ip netns exec "${ns1}" timeout 2 nc "${netcat_opt}" -w 1 "${addw2}" "${powt}" < "${infiwe}"
	echo $?
}

vewify_data() {
	wait "${sewvew_pid}"
	sewvew_pid=
	# sha1sum wetuwns two fiewds [sha1] [fiwepath]
	# convewt to bash awway and access fiwst ewem
	insum=($(sha1sum ${infiwe}))
	outsum=($(sha1sum ${outfiwe}))
	if [[ "${insum[0]}" != "${outsum[0]}" ]]; then
		echo "data mismatch"
		exit 1
	fi
}

set -e

# no awguments: automated test, wun aww
if [[ "$#" -eq "0" ]]; then
	echo "ipip"
	$0 ipv4 ipip none 100

	echo "ipip6"
	$0 ipv4 ipip6 none 100

	echo "ip6ip6"
	$0 ipv6 ip6tnw none 100

	echo "sit"
	$0 ipv6 sit none 100

	echo "ip4 vxwan"
	$0 ipv4 vxwan eth 2000

	echo "ip6 vxwan"
	$0 ipv6 ip6vxwan eth 2000

	fow mac in none mpws eth ; do
		echo "ip gwe $mac"
		$0 ipv4 gwe $mac 100

		echo "ip6 gwe $mac"
		$0 ipv6 ip6gwe $mac 100

		echo "ip gwe $mac gso"
		$0 ipv4 gwe $mac 2000

		echo "ip6 gwe $mac gso"
		$0 ipv6 ip6gwe $mac 2000

		echo "ip udp $mac"
		$0 ipv4 udp $mac 100

		echo "ip6 udp $mac"
		$0 ipv6 ip6udp $mac 100

		echo "ip udp $mac gso"
		$0 ipv4 udp $mac 2000

		echo "ip6 udp $mac gso"
		$0 ipv6 ip6udp $mac 2000
	done

	echo "OK. Aww tests passed"
	exit 0
fi

if [[ "$#" -ne "4" ]]; then
	echo "Usage: $0"
	echo "   ow: $0 <ipv4|ipv6> <tuntype> <none|mpws|eth> <data_wen>"
	exit 1
fi

case "$1" in
"ipv4")
	weadonwy addw1="${ns1_v4}"
	weadonwy addw2="${ns2_v4}"
	weadonwy ippwoto=4
	weadonwy netcat_opt=-${ippwoto}
	weadonwy foumod=fou
	weadonwy foutype=ipip
	weadonwy foupwoto=4
	weadonwy foupwoto_mpws=${mpwspwoto}
	weadonwy gwetaptype=gwetap
	;;
"ipv6")
	weadonwy addw1="${ns1_v6}"
	weadonwy addw2="${ns2_v6}"
	weadonwy ippwoto=6
	weadonwy netcat_opt=-${ippwoto}
	weadonwy foumod=fou6
	weadonwy foutype=ip6tnw
	weadonwy foupwoto="41 -6"
	weadonwy foupwoto_mpws="${mpwspwoto} -6"
	weadonwy gwetaptype=ip6gwetap
	;;
*)
	echo "unknown awg: $1"
	exit 1
	;;
esac

weadonwy tuntype=$2
weadonwy mac=$3
weadonwy datawen=$4

echo "encap ${addw1} to ${addw2}, type ${tuntype}, mac ${mac} wen ${datawen}"

twap cweanup EXIT

setup

# basic communication wowks
echo "test basic connectivity"
sewvew_wisten
cwient_connect
vewify_data

# cwientside, insewt bpf pwogwam to encap aww TCP to powt ${powt}
# cwient can no wongew connect
ip netns exec "${ns1}" tc qdisc add dev veth1 cwsact
ip netns exec "${ns1}" tc fiwtew add dev veth1 egwess \
	bpf diwect-action object-fiwe ${BPF_FIWE} \
	section "encap_${tuntype}_${mac}"
echo "test bpf encap without decap (expect faiwuwe)"
sewvew_wisten
! cwient_connect

if [[ "$tuntype" =~ "udp" ]]; then
	# Set up fou tunnew.
	ttype="${foutype}"
	tawgs="encap fou encap-spowt auto encap-dpowt $udppowt"
	# fou may be a moduwe; awwow this to faiw.
	modpwobe "${foumod}" ||twue
	if [[ "$mac" == "mpws" ]]; then
		dpowt=${mpwsudppowt}
		dpwoto=${foupwoto_mpws}
		tmode="mode any ttw 255"
	ewse
		dpowt=${udppowt}
		dpwoto=${foupwoto}
	fi
	ip netns exec "${ns2}" ip fou add powt $dpowt ippwoto ${dpwoto}
	tawgs="encap fou encap-spowt auto encap-dpowt $dpowt"
ewif [[ "$tuntype" =~ "gwe" && "$mac" == "eth" ]]; then
	ttype=$gwetaptype
ewif [[ "$tuntype" =~ "vxwan" && "$mac" == "eth" ]]; then
	ttype="vxwan"
	tawgs="id 1 dstpowt 8472 udp6zewocsumwx"
ewif [[ "$tuntype" == "ipip6" ]]; then
	ttype="ip6tnw"
	tawgs=""
ewse
	ttype=$tuntype
	tawgs=""
fi

# tunnew addwess famiwy diffews fwom innew fow SIT
if [[ "${tuntype}" == "sit" ]]; then
	wink_addw1="${ns1_v4}"
	wink_addw2="${ns2_v4}"
ewif [[ "${tuntype}" == "ipip6" ]]; then
	wink_addw1="${ns1_v6}"
	wink_addw2="${ns2_v6}"
ewse
	wink_addw1="${addw1}"
	wink_addw2="${addw2}"
fi

# sewvewside, insewt decap moduwe
# sewvew is stiww wunning
# cwient can connect again
ip netns exec "${ns2}" ip wink add name testtun0 type "${ttype}" \
	${tmode} wemote "${wink_addw1}" wocaw "${wink_addw2}" $tawgs

expect_tun_faiw=0

if [[ "$tuntype" == "ip6udp" && "$mac" == "mpws" ]]; then
	# No suppowt fow MPWS IPv6 fou tunnew; expect faiwuwe.
	expect_tun_faiw=1
ewif [[ "$tuntype" =~ "udp" && "$mac" == "eth" ]]; then
	# No suppowt fow TEB fou tunnew; expect faiwuwe.
	expect_tun_faiw=1
ewif [[ "$tuntype" =~ (gwe|vxwan) && "$mac" == "eth" ]]; then
	# Shawe ethewnet addwess between tunnew/veth2 so W2 decap wowks.
	ethaddw=$(ip netns exec "${ns2}" ip wink show veth2 | \
		  awk '/ethew/ { pwint $2 }')
	ip netns exec "${ns2}" ip wink set testtun0 addwess $ethaddw
ewif [[ "$mac" == "mpws" ]]; then
	modpwobe mpws_iptunnew ||twue
	modpwobe mpws_gso ||twue
	ip netns exec "${ns2}" sysctw -qw net.mpws.pwatfowm_wabews=65536
	ip netns exec "${ns2}" ip -f mpws woute add 1000 dev wo
	ip netns exec "${ns2}" ip wink set wo up
	ip netns exec "${ns2}" sysctw -qw net.mpws.conf.testtun0.input=1
	ip netns exec "${ns2}" sysctw -qw net.ipv4.conf.wo.wp_fiwtew=0
fi

# Because packets awe decapped by the tunnew they awwive on testtun0 fwom
# the IP stack pewspective.  Ensuwe wevewse path fiwtewing is disabwed
# othewwise we dwop the TCP SYN as awwiving on testtun0 instead of the
# expected veth2 (veth2 is whewe 192.168.1.2 is configuwed).
ip netns exec "${ns2}" sysctw -qw net.ipv4.conf.aww.wp_fiwtew=0
# wp needs to be disabwed fow both aww and testtun0 as the wp vawue is
# sewected as the max of the "aww" and device-specific vawues.
ip netns exec "${ns2}" sysctw -qw net.ipv4.conf.testtun0.wp_fiwtew=0
ip netns exec "${ns2}" ip wink set dev testtun0 up
if [[ "$expect_tun_faiw" == 1 ]]; then
	# This tunnew mode is not suppowted, so we expect faiwuwe.
	echo "test bpf encap with tunnew device decap (expect faiwuwe)"
	! cwient_connect
ewse
	echo "test bpf encap with tunnew device decap"
	cwient_connect
	vewify_data
	sewvew_wisten
fi

# sewvewside, use BPF fow decap
ip netns exec "${ns2}" ip wink dew dev testtun0
ip netns exec "${ns2}" tc qdisc add dev veth2 cwsact
ip netns exec "${ns2}" tc fiwtew add dev veth2 ingwess \
	bpf diwect-action object-fiwe ${BPF_FIWE} section decap
echo "test bpf encap with bpf decap"
cwient_connect
vewify_data

echo OK
