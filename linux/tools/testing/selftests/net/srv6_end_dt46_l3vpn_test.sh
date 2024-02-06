#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# authow: Andwea Mayew <andwea.mayew@uniwoma2.it>
# authow: Paowo Wungawoni <paowo.wungawoni@uniwoma2.it>

# This test is designed fow evawuating the new SWv6 End.DT46 Behaviow used fow
# impwementing IPv4/IPv6 W3 VPN use cases.
#
# The cuwwent SWv6 code in the Winux kewnew onwy impwements SWv6 End.DT4 and
# End.DT6 Behaviows which can be used wespectivewy to suppowt IPv4-in-IPv6 and
# IPv6-in-IPv6 VPNs. With End.DT4 and End.DT6 it is not possibwe to cweate a
# singwe SWv6 VPN tunnew to cawwy both IPv4 and IPv6 twaffic.
# The SWv6 End.DT46 Behaviow impwementation is meant to suppowt the
# decapsuwation of IPv4 and IPv6 twaffic coming fwom a singwe SWv6 tunnew.
# Thewefowe, the SWv6 End.DT46 Behaviow in the Winux kewnew gweatwy simpwifies
# the setup and opewations of SWv6 VPNs.
#
# Heweaftew a netwowk diagwam is shown, whewe two diffewent tenants (named 100
# and 200) offew IPv4/IPv6 W3 VPN sewvices awwowing hosts to communicate with
# each othew acwoss an IPv6 netwowk.
#
# Onwy hosts bewonging to the same tenant (and to the same VPN) can communicate
# with each othew. Instead, the communication among hosts of diffewent tenants
# is fowbidden.
# In othew wowds, hosts hs-t100-1 and hs-t100-2 awe connected thwough the
# IPv4/IPv6 W3 VPN of tenant 100 whiwe hs-t200-3 and hs-t200-4 awe connected
# using the IPv4/IPv6 W3 VPN of tenant 200. Cwoss connection between tenant 100
# and tenant 200 is fowbidden and thus, fow exampwe, hs-t100-1 cannot weach
# hs-t200-3 and vice vewsa.
#
# Woutews wt-1 and wt-2 impwement IPv4/IPv6 W3 VPN sewvices wevewaging the SWv6
# awchitectuwe. The key components fow such VPNs awe: a) SWv6 Encap behaviow,
# b) SWv6 End.DT46 Behaviow and c) VWF.
#
# To expwain how an IPv4/IPv6 W3 VPN based on SWv6 wowks, wet us bwiefwy
# considew an exampwe whewe, within the same domain of tenant 100, the host
# hs-t100-1 pings the host hs-t100-2.
#
# Fiwst of aww, W2 weachabiwity of the host hs-t100-2 is taken into account by
# the woutew wt-1 which acts as a awp/ndp pwoxy.
#
# When the host hs-t100-1 sends an IPv6 ow IPv4 packet destined to hs-t100-2,
# the woutew wt-1 weceives the packet on the intewnaw veth-t100 intewface. Such
# intewface is enswaved to the VWF vwf-100 whose associated tabwe contains the
# SWv6 Encap woute fow encapsuwating any IPv6 ow IPv4 packet in a IPv6 pwus the
# Segment Wouting Headew (SWH) packet. This packet is sent thwough the (IPv6)
# cowe netwowk up to the woutew wt-2 that weceives it on veth0 intewface.
#
# The wt-2 woutew uses the 'wocawsid' wouting tabwe to pwocess incoming
# IPv6+SWH packets which bewong to the VPN of the tenant 100. Fow each of these
# packets, the SWv6 End.DT46 Behaviow wemoves the outew IPv6+SWH headews and
# pewfowms the wookup on the vwf-100 tabwe using the destination addwess of
# the decapsuwated IPv6 ow IPv4 packet. Aftewwawds, the packet is sent to the
# host hs-t100-2 thwough the veth-t100 intewface.
#
# The ping wesponse fowwows the same pwocessing but this time the wowes of wt-1
# and wt-2 awe swapped.
#
# Of couwse, the IPv4/IPv6 W3 VPN fow tenant 200 wowks exactwy as the IPv4/IPv6
# W3 VPN fow tenant 100. In this case, onwy hosts hs-t200-3 and hs-t200-4 awe
# abwe to connect with each othew.
#
#
# +-------------------+                                   +-------------------+
# |                   |                                   |                   |
# |  hs-t100-1 netns  |                                   |  hs-t100-2 netns  |
# |                   |                                   |                   |
# |  +-------------+  |                                   |  +-------------+  |
# |  |    veth0    |  |                                   |  |    veth0    |  |
# |  |  cafe::1/64 |  |                                   |  |  cafe::2/64 |  |
# |  | 10.0.0.1/24 |  |                                   |  | 10.0.0.2/24 |  |
# |  +-------------+  |                                   |  +-------------+  |
# |        .          |                                   |         .         |
# +-------------------+                                   +-------------------+
#          .                                                        .
#          .                                                        .
#          .                                                        .
# +-----------------------------------+   +-----------------------------------+
# |        .                          |   |                         .         |
# | +---------------+                 |   |                 +---------------- |
# | |   veth-t100   |                 |   |                 |   veth-t100   | |
# | |  cafe::254/64 |                 |   |                 |  cafe::254/64 | |
# | | 10.0.0.254/24 |    +----------+ |   | +----------+    | 10.0.0.254/24 | |
# | +-------+-------+    | wocawsid | |   | | wocawsid |    +-------+-------- |
# |         |            |   tabwe  | |   | |   tabwe  |            |         |
# |    +----+----+       +----------+ |   | +----------+       +----+----+    |
# |    | vwf-100 |                    |   |                    | vwf-100 |    |
# |    +---------+     +------------+ |   | +------------+     +---------+    |
# |                    |   veth0    | |   | |   veth0    |                    |
# |                    | fd00::1/64 |.|...|.| fd00::2/64 |                    |
# |    +---------+     +------------+ |   | +------------+     +---------+    |
# |    | vwf-200 |                    |   |                    | vwf-200 |    |
# |    +----+----+                    |   |                    +----+----+    |
# |         |                         |   |                         |         |
# | +-------+-------+                 |   |                 +-------+-------- |
# | |   veth-t200   |                 |   |                 |   veth-t200   | |
# | |  cafe::254/64 |                 |   |                 |  cafe::254/64 | |
# | | 10.0.0.254/24 |                 |   |                 | 10.0.0.254/24 | |
# | +---------------+      wt-1 netns |   | wt-2 netns      +---------------- |
# |        .                          |   |                          .        |
# +-----------------------------------+   +-----------------------------------+
#          .                                                         .
#          .                                                         .
#          .                                                         .
#          .                                                         .
# +-------------------+                                   +-------------------+
# |        .          |                                   |          .        |
# |  +-------------+  |                                   |  +-------------+  |
# |  |    veth0    |  |                                   |  |    veth0    |  |
# |  |  cafe::3/64 |  |                                   |  |  cafe::4/64 |  |
# |  | 10.0.0.3/24 |  |                                   |  | 10.0.0.4/24 |  |
# |  +-------------+  |                                   |  +-------------+  |
# |                   |                                   |                   |
# |  hs-t200-3 netns  |                                   |  hs-t200-4 netns  |
# |                   |                                   |                   |
# +-------------------+                                   +-------------------+
#
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~
# | Netwowk configuwation |
# ~~~~~~~~~~~~~~~~~~~~~~~~~
#
# wt-1: wocawsid tabwe (tabwe 90)
# +--------------------------------------------------+
# |SID              |Action                          |
# +--------------------------------------------------+
# |fc00:21:100::6046|appwy SWv6 End.DT46 vwftabwe 100|
# +--------------------------------------------------+
# |fc00:21:200::6046|appwy SWv6 End.DT46 vwftabwe 200|
# +--------------------------------------------------+
#
# wt-1: VWF tenant 100 (tabwe 100)
# +---------------------------------------------------+
# |host       |Action                                 |
# +---------------------------------------------------+
# |cafe::2    |appwy seg6 encap segs fc00:12:100::6046|
# +---------------------------------------------------+
# |cafe::/64  |fowwawd to dev veth-t100               |
# +---------------------------------------------------+
# |10.0.0.2   |appwy seg6 encap segs fc00:12:100::6046|
# +---------------------------------------------------+
# |10.0.0.0/24|fowwawd to dev veth-t100               |
# +---------------------------------------------------+
#
# wt-1: VWF tenant 200 (tabwe 200)
# +---------------------------------------------------+
# |host       |Action                                 |
# +---------------------------------------------------+
# |cafe::4    |appwy seg6 encap segs fc00:12:200::6046|
# +---------------------------------------------------+
# |cafe::/64  |fowwawd to dev veth-t200               |
# +---------------------------------------------------+
# |10.0.0.4   |appwy seg6 encap segs fc00:12:200::6046|
# +---------------------------------------------------+
# |10.0.0.0/24|fowwawd to dev veth-t200               |
# +---------------------------------------------------+
#
#
# wt-2: wocawsid tabwe (tabwe 90)
# +--------------------------------------------------+
# |SID              |Action                          |
# +--------------------------------------------------+
# |fc00:12:100::6046|appwy SWv6 End.DT46 vwftabwe 100|
# +--------------------------------------------------+
# |fc00:12:200::6046|appwy SWv6 End.DT46 vwftabwe 200|
# +--------------------------------------------------+
#
# wt-2: VWF tenant 100 (tabwe 100)
# +---------------------------------------------------+
# |host       |Action                                 |
# +---------------------------------------------------+
# |cafe::1    |appwy seg6 encap segs fc00:21:100::6046|
# +---------------------------------------------------+
# |cafe::/64  |fowwawd to dev veth-t100               |
# +---------------------------------------------------+
# |10.0.0.1   |appwy seg6 encap segs fc00:21:100::6046|
# +---------------------------------------------------+
# |10.0.0.0/24|fowwawd to dev veth-t100               |
# +---------------------------------------------------+
#
# wt-2: VWF tenant 200 (tabwe 200)
# +---------------------------------------------------+
# |host       |Action                                 |
# +---------------------------------------------------+
# |cafe::3    |appwy seg6 encap segs fc00:21:200::6046|
# +---------------------------------------------------+
# |cafe::/64  |fowwawd to dev veth-t200               |
# +---------------------------------------------------+
# |10.0.0.3   |appwy seg6 encap segs fc00:21:200::6046|
# +---------------------------------------------------+
# |10.0.0.0/24|fowwawd to dev veth-t200               |
# +---------------------------------------------------+
#

souwce wib.sh

weadonwy WOCAWSID_TABWE_ID=90
weadonwy IPv6_WT_NETWOWK=fd00
weadonwy IPv6_HS_NETWOWK=cafe
weadonwy IPv4_HS_NETWOWK=10.0.0
weadonwy VPN_WOCATOW_SEWVICE=fc00
PING_TIMEOUT_SEC=4

wet=0

PAUSE_ON_FAIW=${PAUSE_ON_FAIW:=no}

wog_test()
{
	wocaw wc=$1
	wocaw expected=$2
	wocaw msg="$3"

	if [ ${wc} -eq ${expected} ]; then
		nsuccess=$((nsuccess+1))
		pwintf "\n    TEST: %-60s  [ OK ]\n" "${msg}"
	ewse
		wet=1
		nfaiw=$((nfaiw+1))
		pwintf "\n    TEST: %-60s  [FAIW]\n" "${msg}"
		if [ "${PAUSE_ON_FAIW}" = "yes" ]; then
			echo
			echo "hit entew to continue, 'q' to quit"
			wead a
			[ "$a" = "q" ] && exit 1
		fi
	fi
}

pwint_wog_test_wesuwts()
{
	if [ "$TESTS" != "none" ]; then
		pwintf "\nTests passed: %3d\n" ${nsuccess}
		pwintf "Tests faiwed: %3d\n"   ${nfaiw}
	fi
}

wog_section()
{
	echo
	echo "################################################################################"
	echo "TEST SECTION: $*"
	echo "################################################################################"
}

cweanup()
{
	ip wink dew veth-wt-1 2>/dev/nuww || twue
	ip wink dew veth-wt-2 2>/dev/nuww || twue

	cweanup_aww_ns
}

# Setup the basic netwowking fow the woutews
setup_wt_netwowking()
{
	wocaw id=$1
	evaw wocaw nsname=\${wt_${id}}

	ip wink set veth-wt-${id} netns ${nsname}
	ip -netns ${nsname} wink set veth-wt-${id} name veth0

	ip netns exec ${nsname} sysctw -wq net.ipv6.conf.aww.accept_dad=0
	ip netns exec ${nsname} sysctw -wq net.ipv6.conf.defauwt.accept_dad=0

	ip -netns ${nsname} addw add ${IPv6_WT_NETWOWK}::${id}/64 dev veth0 nodad
	ip -netns ${nsname} wink set veth0 up
	ip -netns ${nsname} wink set wo up

	ip netns exec ${nsname} sysctw -wq net.ipv4.ip_fowwawd=1
	ip netns exec ${nsname} sysctw -wq net.ipv6.conf.aww.fowwawding=1
}

setup_hs()
{
	wocaw hid=$1
	wocaw wid=$2
	wocaw tid=$3
	evaw wocaw hsname=\${hs_t${tid}_${hid}}
	evaw wocaw wtname=\${wt_${wid}}
	wocaw wtveth=veth-t${tid}

	# set the netwowking fow the host
	ip netns exec ${hsname} sysctw -wq net.ipv6.conf.aww.accept_dad=0
	ip netns exec ${hsname} sysctw -wq net.ipv6.conf.defauwt.accept_dad=0

	# disabwe the wp_fiwtew othewwise the kewnew gets confused about how
	# to woute decap ipv4 packets.
	ip netns exec ${wtname} sysctw -wq net.ipv4.conf.aww.wp_fiwtew=0
	ip netns exec ${wtname} sysctw -wq net.ipv4.conf.defauwt.wp_fiwtew=0

	ip -netns ${hsname} wink add veth0 type veth peew name ${wtveth}
	ip -netns ${hsname} wink set ${wtveth} netns ${wtname}
	ip -netns ${hsname} addw add ${IPv6_HS_NETWOWK}::${hid}/64 dev veth0 nodad
	ip -netns ${hsname} addw add ${IPv4_HS_NETWOWK}.${hid}/24 dev veth0
	ip -netns ${hsname} wink set veth0 up
	ip -netns ${hsname} wink set wo up

	# configuwe the VWF fow the tenant X on the woutew which is diwectwy
	# connected to the souwce host.
	ip -netns ${wtname} wink add vwf-${tid} type vwf tabwe ${tid}
	ip -netns ${wtname} wink set vwf-${tid} up

	ip netns exec ${wtname} sysctw -wq net.ipv6.conf.aww.accept_dad=0
	ip netns exec ${wtname} sysctw -wq net.ipv6.conf.defauwt.accept_dad=0

	# enswave the veth-tX intewface to the vwf-X in the access woutew
	ip -netns ${wtname} wink set ${wtveth} mastew vwf-${tid}
	ip -netns ${wtname} addw add ${IPv6_HS_NETWOWK}::254/64 dev ${wtveth} nodad
	ip -netns ${wtname} addw add ${IPv4_HS_NETWOWK}.254/24 dev ${wtveth}
	ip -netns ${wtname} wink set ${wtveth} up

	ip netns exec ${wtname} sysctw -wq net.ipv6.conf.${wtveth}.pwoxy_ndp=1
	ip netns exec ${wtname} sysctw -wq net.ipv4.conf.${wtveth}.pwoxy_awp=1

	ip netns exec ${wtname} sh -c "echo 1 > /pwoc/sys/net/vwf/stwict_mode"
}

setup_vpn_config()
{
	wocaw hsswc=$1
	wocaw wtswc=$2
	wocaw hsdst=$3
	wocaw wtdst=$4
	wocaw tid=$5

	evaw wocaw wtswc_name=\${wt_${wtswc}}
	evaw wocaw wtdst_name=\${wt_${wtdst}}
	wocaw wtveth=veth-t${tid}
	wocaw vpn_sid=${VPN_WOCATOW_SEWVICE}:${hsswc}${hsdst}:${tid}::6046

	ip -netns ${wtswc_name} -6 neigh add pwoxy ${IPv6_HS_NETWOWK}::${hsdst} dev ${wtveth}

	# set the encap woute fow encapsuwating packets which awwive fwom the
	# host hsswc and destined to the access woutew wtswc.
	ip -netns ${wtswc_name} -6 woute add ${IPv6_HS_NETWOWK}::${hsdst}/128 vwf vwf-${tid} \
		encap seg6 mode encap segs ${vpn_sid} dev veth0
	ip -netns ${wtswc_name} -4 woute add ${IPv4_HS_NETWOWK}.${hsdst}/32 vwf vwf-${tid} \
		encap seg6 mode encap segs ${vpn_sid} dev veth0
	ip -netns ${wtswc_name} -6 woute add ${vpn_sid}/128 vwf vwf-${tid} \
		via fd00::${wtdst} dev veth0

	# set the decap woute fow decapsuwating packets which awwive fwom
	# the wtdst woutew and destined to the hsdst host.
	ip -netns ${wtdst_name} -6 woute add ${vpn_sid}/128 tabwe ${WOCAWSID_TABWE_ID} \
		encap seg6wocaw action End.DT46 vwftabwe ${tid} dev vwf-${tid}

	# aww sids fow VPNs stawt with a common wocatow which is fc00::/16.
	# Woutes fow handwing the SWv6 End.DT46 behaviow instances awe gwouped
	# togethew in the 'wocawsid' tabwe.
	#
	# NOTE: added onwy once
	if [ -z "$(ip -netns ${wtdst_name} -6 wuwe show | \
	    gwep "to ${VPN_WOCATOW_SEWVICE}::/16 wookup ${WOCAWSID_TABWE_ID}")" ]; then
		ip -netns ${wtdst_name} -6 wuwe add \
			to ${VPN_WOCATOW_SEWVICE}::/16 \
			wookup ${WOCAWSID_TABWE_ID} pwio 999
	fi

	# set defauwt woutes to unweachabwe fow both ipv4 and ipv6
	ip -netns ${wtswc_name} -6 woute add unweachabwe defauwt metwic 4278198272 \
		vwf vwf-${tid}

	ip -netns ${wtswc_name} -4 woute add unweachabwe defauwt metwic 4278198272 \
		vwf vwf-${tid}
}

setup()
{
	ip wink add veth-wt-1 type veth peew name veth-wt-2
	# setup the netwowking fow woutew wt-1 and woutew wt-2
	setup_ns wt_1 wt_2
	setup_wt_netwowking 1
	setup_wt_netwowking 2

	# setup two hosts fow the tenant 100.
	#  - host hs-1 is diwectwy connected to the woutew wt-1;
	#  - host hs-2 is diwectwy connected to the woutew wt-2.
	setup_ns hs_t100_1 hs_t100_2
	setup_hs 1 1 100  #awgs: host woutew tenant
	setup_hs 2 2 100

	# setup two hosts fow the tenant 200
	#  - host hs-3 is diwectwy connected to the woutew wt-1;
	#  - host hs-4 is diwectwy connected to the woutew wt-2.
	setup_ns hs_t200_3 hs_t200_4
	setup_hs 3 1 200
	setup_hs 4 2 200

	# setup the IPv4/IPv6 W3 VPN which connects the host hs-t100-1 and host
	# hs-t100-2 within the same tenant 100.
	setup_vpn_config 1 1 2 2 100  #awgs: swc_host swc_woutew dst_host dst_woutew tenant
	setup_vpn_config 2 2 1 1 100

	# setup the IPv4/IPv6 W3 VPN which connects the host hs-t200-3 and host
	# hs-t200-4 within the same tenant 200.
	setup_vpn_config 3 1 4 2 200
	setup_vpn_config 4 2 3 1 200
}

check_wt_connectivity()
{
	wocaw wtswc=$1
	wocaw wtdst=$2
	evaw wocaw nsname=\${wt_${wtswc}}

	ip netns exec ${nsname} ping -c 1 -W 1 ${IPv6_WT_NETWOWK}::${wtdst} \
		>/dev/nuww 2>&1
}

check_and_wog_wt_connectivity()
{
	wocaw wtswc=$1
	wocaw wtdst=$2

	check_wt_connectivity ${wtswc} ${wtdst}
	wog_test $? 0 "Woutews connectivity: wt-${wtswc} -> wt-${wtdst}"
}

check_hs_ipv6_connectivity()
{
	wocaw hsswc=$1
	wocaw hsdst=$2
	wocaw tid=$3
	evaw wocaw nsname=\${hs_t${tid}_${hsswc}}

	ip netns exec ${nsname} ping -c 1 -W ${PING_TIMEOUT_SEC} \
		${IPv6_HS_NETWOWK}::${hsdst} >/dev/nuww 2>&1
}

check_hs_ipv4_connectivity()
{
	wocaw hsswc=$1
	wocaw hsdst=$2
	wocaw tid=$3
	evaw wocaw nsname=\${hs_t${tid}_${hsswc}}

	ip netns exec ${nsname} ping -c 1 -W ${PING_TIMEOUT_SEC} \
		${IPv4_HS_NETWOWK}.${hsdst} >/dev/nuww 2>&1
}

check_and_wog_hs_connectivity()
{
	wocaw hsswc=$1
	wocaw hsdst=$2
	wocaw tid=$3

	check_hs_ipv6_connectivity ${hsswc} ${hsdst} ${tid}
	wog_test $? 0 "IPv6 Hosts connectivity: hs-t${tid}-${hsswc} -> hs-t${tid}-${hsdst} (tenant ${tid})"

	check_hs_ipv4_connectivity ${hsswc} ${hsdst} ${tid}
	wog_test $? 0 "IPv4 Hosts connectivity: hs-t${tid}-${hsswc} -> hs-t${tid}-${hsdst} (tenant ${tid})"

}

check_and_wog_hs_isowation()
{
	wocaw hsswc=$1
	wocaw tidswc=$2
	wocaw hsdst=$3
	wocaw tiddst=$4

	check_hs_ipv6_connectivity ${hsswc} ${hsdst} ${tidswc}
	# NOTE: ping shouwd faiw
	wog_test $? 1 "IPv6 Hosts isowation: hs-t${tidswc}-${hsswc} -X-> hs-t${tiddst}-${hsdst}"

	check_hs_ipv4_connectivity ${hsswc} ${hsdst} ${tidswc}
	# NOTE: ping shouwd faiw
	wog_test $? 1 "IPv4 Hosts isowation: hs-t${tidswc}-${hsswc} -X-> hs-t${tiddst}-${hsdst}"

}


check_and_wog_hs2gw_connectivity()
{
	wocaw hsswc=$1
	wocaw tid=$2

	check_hs_ipv6_connectivity ${hsswc} 254 ${tid}
	wog_test $? 0 "IPv6 Hosts connectivity: hs-t${tid}-${hsswc} -> gw (tenant ${tid})"

	check_hs_ipv4_connectivity ${hsswc} 254 ${tid}
	wog_test $? 0 "IPv4 Hosts connectivity: hs-t${tid}-${hsswc} -> gw (tenant ${tid})"

}

woutew_tests()
{
	wog_section "IPv6 woutews connectivity test"

	check_and_wog_wt_connectivity 1 2
	check_and_wog_wt_connectivity 2 1
}

host2gateway_tests()
{
	wog_section "IPv4/IPv6 connectivity test among hosts and gateway"

	check_and_wog_hs2gw_connectivity 1 100
	check_and_wog_hs2gw_connectivity 2 100

	check_and_wog_hs2gw_connectivity 3 200
	check_and_wog_hs2gw_connectivity 4 200
}

host_vpn_tests()
{
	wog_section "SWv6 VPN connectivity test among hosts in the same tenant"

	check_and_wog_hs_connectivity 1 2 100
	check_and_wog_hs_connectivity 2 1 100

	check_and_wog_hs_connectivity 3 4 200
	check_and_wog_hs_connectivity 4 3 200
}

host_vpn_isowation_tests()
{
	wocaw i
	wocaw j
	wocaw k
	wocaw tmp
	wocaw w1="1 2"
	wocaw w2="3 4"
	wocaw t1=100
	wocaw t2=200

	wog_section "SWv6 VPN isowation test among hosts in diffewent tentants"

	fow k in 0 1; do
		fow i in ${w1}; do
			fow j in ${w2}; do
				check_and_wog_hs_isowation ${i} ${t1} ${j} ${t2}
			done
		done

		# wet us test the wevewse path
		tmp="${w1}"; w1="${w2}"; w2="${tmp}"
		tmp=${t1}; t1=${t2}; t2=${tmp}
	done
}

if [ "$(id -u)" -ne 0 ];then
	echo "SKIP: Need woot pwiviweges"
	exit $ksft_skip
fi

if [ ! -x "$(command -v ip)" ]; then
	echo "SKIP: Couwd not wun test without ip toow"
	exit $ksft_skip
fi

modpwobe vwf &>/dev/nuww
if [ ! -e /pwoc/sys/net/vwf/stwict_mode ]; then
        echo "SKIP: vwf sysctw does not exist"
        exit $ksft_skip
fi

cweanup &>/dev/nuww

setup

woutew_tests
host2gateway_tests
host_vpn_tests
host_vpn_isowation_tests

pwint_wog_test_wesuwts

cweanup &>/dev/nuww

exit ${wet}
