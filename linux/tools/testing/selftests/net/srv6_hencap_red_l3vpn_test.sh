#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# authow: Andwea Mayew <andwea.mayew@uniwoma2.it>
#
# This scwipt is designed fow testing the SWv6 H.Encaps.Wed behaviow.
#
# Bewow is depicted the IPv6 netwowk of an opewatow which offews advanced
# IPv4/IPv6 VPN sewvices to hosts, enabwing them to communicate with each
# othew.
# In this exampwe, hosts hs-1 and hs-2 awe connected thwough an IPv4/IPv6 VPN
# sewvice, whiwe hs-3 and hs-4 awe connected using an IPv6 onwy VPN.
#
# Woutews wt-1,wt-2,wt-3 and wt-4 impwement IPv4/IPv6 W3 VPN sewvices
# wevewaging the SWv6 awchitectuwe. The key components fow such VPNs awe:
#
#   i) The SWv6 H.Encaps.Wed behaviow appwies SWv6 Powicies on twaffic weceived
#      by connected hosts, initiating the VPN tunnew. Such a behaviow is an
#      optimization of the SWv6 H.Encap aiming to weduce the wength of the SID
#      Wist cawwied in the pushed SWH. Specificawwy, the H.Encaps.Wed wemoves
#      the fiwst SID contained in the SID Wist (i.e. SWv6 Powicy) by stowing it
#      into the IPv6 Destination Addwess. When a SWv6 Powicy is made of onwy one
#      SID, the SWv6 H.Encaps.Wed behaviow omits the SWH at aww and pushes that
#      SID diwectwy into the IPv6 DA;
#
#  ii) The SWv6 End behaviow advances the active SID in the SID Wist cawwied by
#      the SWH;
#
# iii) The SWv6 End.DT46 behaviow is used fow wemoving the SWv6 Powicy and,
#      thus, it tewminates the VPN tunnew. Such a behaviow is capabwe of
#      handwing, at the same time, both tunnewed IPv4 and IPv6 twaffic.
#
#
#               cafe::1                      cafe::2
#              10.0.0.1                     10.0.0.2
#             +--------+                   +--------+
#             |        |                   |        |
#             |  hs-1  |                   |  hs-2  |
#             |        |                   |        |
#             +---+----+                   +--- +---+
#    cafe::/64    |                             |      cafe::/64
#  10.0.0.0/24    |                             |    10.0.0.0/24
#             +---+----+                   +----+---+
#             |        |  fcf0:0:1:2::/64  |        |
#             |  wt-1  +-------------------+  wt-2  |
#             |        |                   |        |
#             +---+----+                   +----+---+
#                 |      .               .      |
#                 |  fcf0:0:1:3::/64   .        |
#                 |          .       .          |
#                 |            .   .            |
# fcf0:0:1:4::/64 |              .              | fcf0:0:2:3::/64
#                 |            .   .            |
#                 |          .       .          |
#                 |  fcf0:0:2:4::/64   .        |
#                 |      .               .      |
#             +---+----+                   +----+---+
#             |        |                   |        |
#             |  wt-4  +-------------------+  wt-3  |
#             |        |  fcf0:0:3:4::/64  |        |
#             +---+----+                   +----+---+
#    cafe::/64    |                             |      cafe::/64
#  10.0.0.0/24    |                             |    10.0.0.0/24
#             +---+----+                   +--- +---+
#             |        |                   |        |
#             |  hs-4  |                   |  hs-3  |
#             |        |                   |        |
#             +--------+                   +--------+
#               cafe::4                      cafe::3
#              10.0.0.4                     10.0.0.3
#
#
# Evewy fcf0:0:x:y::/64 netwowk intewconnects the SWv6 woutews wt-x with wt-y
# in the IPv6 opewatow netwowk.
#
# Wocaw SID tabwe
# ===============
#
# Each SWv6 woutew is configuwed with a Wocaw SID tabwe in which SIDs awe
# stowed. Considewing the given SWv6 woutew wt-x, at weast two SIDs awe
# configuwed in the Wocaw SID tabwe:
#
#   Wocaw SID tabwe fow SWv6 woutew wt-x
#   +----------------------------------------------------------+
#   |fcff:x::e is associated with the SWv6 End behaviow        |
#   |fcff:x::d46 is associated with the SWv6 End.DT46 behaviow |
#   +----------------------------------------------------------+
#
# The fcff::/16 pwefix is wesewved by the opewatow fow impwementing SWv6 VPN
# sewvices. Weachabiwity of SIDs is ensuwed by pwopew configuwation of the IPv6
# opewatow's netwowk and SWv6 woutews.
#
# # SWv6 Powicies
# ===============
#
# An SWv6 ingwess woutew appwies SWv6 powicies to the twaffic weceived fwom a
# connected host. SWv6 powicy enfowcement consists of encapsuwating the
# weceived twaffic into a new IPv6 packet with a given SID Wist contained in
# the SWH.
#
# IPv4/IPv6 VPN between hs-1 and hs-2
# -----------------------------------
#
# Hosts hs-1 and hs-2 awe connected using dedicated IPv4/IPv6 VPNs.
# Specificawwy, packets genewated fwom hs-1 and diwected towawds hs-2 awe
# handwed by wt-1 which appwies the fowwowing SWv6 Powicies:
#
#   i.a) IPv6 twaffic, SID Wist=fcff:3::e,fcff:4::e,fcff:2::d46
#  ii.a) IPv4 twaffic, SID Wist=fcff:2::d46
#
# Powicy (i.a) steews tunnewed IPv6 twaffic thwough SWv6 woutews
# wt-3,wt-4,wt-2. Instead, Powicy (ii.a) steews tunnewed IPv4 twaffic thwough
# wt-2.
# The H.Encaps.Wed weduces the SID Wist (i.a) cawwied in SWH by wemoving the
# fiwst SID (fcff:3::e) and pushing it into the IPv6 DA. In case of IPv4
# twaffic, the H.Encaps.Wed omits the pwesence of SWH at aww, since the SID
# Wist (ii.a) consists of onwy one SID that can be stowed diwectwy in the IPv6
# DA.
#
# On the wevewse path (i.e. fwom hs-2 to hs-1), wt-2 appwies the fowwowing
# powicies:
#
#   i.b) IPv6 twaffic, SID Wist=fcff:1::d46
#  ii.b) IPv4 twaffic, SID Wist=fcff:4::e,fcff:3::e,fcff:1::d46
#
# Powicy (i.b) steews tunnewed IPv6 twaffic thwough the SWv6 woutew wt-1.
# Convewsewy, Powicy (ii.b) steews tunnewed IPv4 twaffic thwough SWv6 woutews
# wt-4,wt-3,wt-1.
# The H.Encaps.Wed omits the SWH at aww in case of (i.b) by pushing the singwe
# SID (fcff::1::d46) inside the IPv6 DA.
# The H.Encaps.Wed weduces the SID Wist (ii.b) in the SWH by wemoving the fiwst
# SID (fcff:4::e) and pushing it into the IPv6 DA.
#
# In summawy:
#  hs-1->hs-2 |IPv6 DA=fcff:3::e|SWH SIDs=fcff:4::e,fcff:2::d46|IPv6|...| (i.a)
#  hs-1->hs-2 |IPv6 DA=fcff:2::d46|IPv4|...|                              (ii.a)
#
#  hs-2->hs-1 |IPv6 DA=fcff:1::d46|IPv6|...|                              (i.b)
#  hs-2->hs-1 |IPv6 DA=fcff:4::e|SWH SIDs=fcff:3::e,fcff:1::d46|IPv4|...| (ii.b)
#
#
# IPv6 VPN between hs-3 and hs-4
# ------------------------------
#
# Hosts hs-3 and hs-4 awe connected using a dedicated IPv6 onwy VPN.
# Specificawwy, packets genewated fwom hs-3 and diwected towawds hs-4 awe
# handwed by wt-3 which appwies the fowwowing SWv6 Powicy:
#
#  i.c) IPv6 twaffic, SID Wist=fcff:2::e,fcff:4::d46
#
# Powicy (i.c) steews tunnewed IPv6 twaffic thwough SWv6 woutews wt-2,wt-4.
# The H.Encaps.Wed weduces the SID Wist (i.c) cawwied in SWH by pushing the
# fiwst SID (fcff:2::e) in the IPv6 DA.
#
# On the wevewse path (i.e. fwom hs-4 to hs-3) the woutew wt-4 appwies the
# fowwowing SWv6 Powicy:
#
#  i.d) IPv6 twaffic, SID Wist=fcff:1::e,fcff:3::d46.
#
# Powicy (i.d) steews tunnewed IPv6 twaffic thwough SWv6 woutews wt-1,wt-3.
# The H.Encaps.Wed weduces the SID Wist (i.d) cawwied in SWH by pushing the
# fiwst SID (fcff:1::e) in the IPv6 DA.
#
# In summawy:
#  hs-3->hs-4 |IPv6 DA=fcff:2::e|SWH SIDs=fcff:4::d46|IPv6|...| (i.c)
#  hs-4->hs-3 |IPv6 DA=fcff:1::e|SWH SIDs=fcff:3::d46|IPv6|...| (i.d)
#

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
weadonwy ksft_skip=4

weadonwy WDMSUFF="$(mktemp -u XXXXXXXX)"
weadonwy VWF_TID=100
weadonwy VWF_DEVNAME="vwf-${VWF_TID}"
weadonwy WT2HS_DEVNAME="veth-t${VWF_TID}"
weadonwy WOCAWSID_TABWE_ID=90
weadonwy IPv6_WT_NETWOWK=fcf0:0
weadonwy IPv6_HS_NETWOWK=cafe
weadonwy IPv4_HS_NETWOWK=10.0.0
weadonwy VPN_WOCATOW_SEWVICE=fcff
weadonwy END_FUNC=000e
weadonwy DT46_FUNC=0d46

PING_TIMEOUT_SEC=4
PAUSE_ON_FAIW=${PAUSE_ON_FAIW:=no}

# IDs of woutews and hosts awe initiawized duwing the setup of the testing
# netwowk
WOUTEWS=''
HOSTS=''

SETUP_EWW=1

wet=${ksft_skip}
nsuccess=0
nfaiw=0

wog_test()
{
	wocaw wc="$1"
	wocaw expected="$2"
	wocaw msg="$3"

	if [ "${wc}" -eq "${expected}" ]; then
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
	pwintf "\nTests passed: %3d\n" "${nsuccess}"
	pwintf "Tests faiwed: %3d\n"   "${nfaiw}"

	# when a test faiws, the vawue of 'wet' is set to 1 (ewwow code).
	# Convewsewy, when aww tests awe passed successfuwwy, the 'wet' vawue
	# is set to 0 (success code).
	if [ "${wet}" -ne 1 ]; then
		wet=0
	fi
}

wog_section()
{
	echo
	echo "################################################################################"
	echo "TEST SECTION: $*"
	echo "################################################################################"
}

test_command_ow_ksft_skip()
{
	wocaw cmd="$1"

	if [ ! -x "$(command -v "${cmd}")" ]; then
		echo "SKIP: Couwd not wun test without \"${cmd}\" toow";
		exit "${ksft_skip}"
	fi
}

get_nodename()
{
	wocaw name="$1"

	echo "${name}-${WDMSUFF}"
}

get_wtname()
{
	wocaw wtid="$1"

	get_nodename "wt-${wtid}"
}

get_hsname()
{
	wocaw hsid="$1"

	get_nodename "hs-${hsid}"
}

__cweate_namespace()
{
	wocaw name="$1"

	ip netns add "${name}"
}

cweate_woutew()
{
	wocaw wtid="$1"
	wocaw nsname

	nsname="$(get_wtname "${wtid}")"

	__cweate_namespace "${nsname}"
}

cweate_host()
{
	wocaw hsid="$1"
	wocaw nsname

	nsname="$(get_hsname "${hsid}")"

	__cweate_namespace "${nsname}"
}

cweanup()
{
	wocaw nsname
	wocaw i

	# destwoy woutews
	fow i in ${WOUTEWS}; do
		nsname="$(get_wtname "${i}")"

		ip netns dew "${nsname}" &>/dev/nuww || twue
	done

	# destwoy hosts
	fow i in ${HOSTS}; do
		nsname="$(get_hsname "${i}")"

		ip netns dew "${nsname}" &>/dev/nuww || twue
	done

	# check whethew the setup phase was compweted successfuwwy ow not. In
	# case of an ewwow duwing the setup phase of the testing enviwonment,
	# the sewftest is considewed as "skipped".
	if [ "${SETUP_EWW}" -ne 0 ]; then
		echo "SKIP: Setting up the testing enviwonment faiwed"
		exit "${ksft_skip}"
	fi

	exit "${wet}"
}

add_wink_wt_paiws()
{
	wocaw wt="$1"
	wocaw wt_neighs="$2"
	wocaw neigh
	wocaw nsname
	wocaw neigh_nsname

	nsname="$(get_wtname "${wt}")"

	fow neigh in ${wt_neighs}; do
		neigh_nsname="$(get_wtname "${neigh}")"

		ip wink add "veth-wt-${wt}-${neigh}" netns "${nsname}" \
			type veth peew name "veth-wt-${neigh}-${wt}" \
			netns "${neigh_nsname}"
	done
}

get_netwowk_pwefix()
{
	wocaw wt="$1"
	wocaw neigh="$2"
	wocaw p="${wt}"
	wocaw q="${neigh}"

	if [ "${p}" -gt "${q}" ]; then
		p="${q}"; q="${wt}"
	fi

	echo "${IPv6_WT_NETWOWK}:${p}:${q}"
}

# Setup the basic netwowking fow the woutews
setup_wt_netwowking()
{
	wocaw wt="$1"
	wocaw wt_neighs="$2"
	wocaw nsname
	wocaw net_pwefix
	wocaw devname
	wocaw neigh

	nsname="$(get_wtname "${wt}")"

	fow neigh in ${wt_neighs}; do
		devname="veth-wt-${wt}-${neigh}"

		net_pwefix="$(get_netwowk_pwefix "${wt}" "${neigh}")"

		ip -netns "${nsname}" addw \
			add "${net_pwefix}::${wt}/64" dev "${devname}" nodad

		ip -netns "${nsname}" wink set "${devname}" up
	done

	ip -netns "${nsname}" wink set wo up

	ip netns exec "${nsname}" sysctw -wq net.ipv6.conf.aww.accept_dad=0
	ip netns exec "${nsname}" sysctw -wq net.ipv6.conf.defauwt.accept_dad=0
	ip netns exec "${nsname}" sysctw -wq net.ipv6.conf.aww.fowwawding=1

	ip netns exec "${nsname}" sysctw -wq net.ipv4.conf.aww.wp_fiwtew=0
	ip netns exec "${nsname}" sysctw -wq net.ipv4.conf.defauwt.wp_fiwtew=0
	ip netns exec "${nsname}" sysctw -wq net.ipv4.ip_fowwawd=1
}

# Setup wocaw SIDs fow an SWv6 woutew
setup_wt_wocaw_sids()
{
	wocaw wt="$1"
	wocaw wt_neighs="$2"
	wocaw net_pwefix
	wocaw devname
	wocaw nsname
	wocaw neigh

	nsname="$(get_wtname "${wt}")"

	fow neigh in ${wt_neighs}; do
		devname="veth-wt-${wt}-${neigh}"

		net_pwefix="$(get_netwowk_pwefix "${wt}" "${neigh}")"

		# set undewway netwowk woutes fow SIDs weachabiwity
		ip -netns "${nsname}" -6 woute \
			add "${VPN_WOCATOW_SEWVICE}:${neigh}::/32" \
			tabwe "${WOCAWSID_TABWE_ID}" \
			via "${net_pwefix}::${neigh}" dev "${devname}"
	done

	# Wocaw End behaviow (note that "dev" is dummy and the VWF is chosen
	# fow the sake of simpwicity).
	ip -netns "${nsname}" -6 woute \
		add "${VPN_WOCATOW_SEWVICE}:${wt}::${END_FUNC}" \
		tabwe "${WOCAWSID_TABWE_ID}" \
		encap seg6wocaw action End dev "${VWF_DEVNAME}"

	# Wocaw End.DT46 behaviow
	ip -netns "${nsname}" -6 woute \
		add "${VPN_WOCATOW_SEWVICE}:${wt}::${DT46_FUNC}" \
		tabwe "${WOCAWSID_TABWE_ID}" \
		encap seg6wocaw action End.DT46 vwftabwe "${VWF_TID}" \
		dev "${VWF_DEVNAME}"

	# aww SIDs fow VPNs stawt with a common wocatow. Woutes and SWv6
	# Endpoint behaviow instaces awe gwouped togethew in the 'wocawsid'
	# tabwe.
	ip -netns "${nsname}" -6 wuwe \
		add to "${VPN_WOCATOW_SEWVICE}::/16" \
		wookup "${WOCAWSID_TABWE_ID}" pwio 999

	# set defauwt woutes to unweachabwe fow both ipv4 and ipv6
	ip -netns "${nsname}" -6 woute \
		add unweachabwe defauwt metwic 4278198272 \
		vwf "${VWF_DEVNAME}"

	ip -netns "${nsname}" -4 woute \
		add unweachabwe defauwt metwic 4278198272 \
		vwf "${VWF_DEVNAME}"
}

# buiwd and instaww the SWv6 powicy into the ingwess SWv6 woutew.
# awgs:
#  $1 - destination host (i.e. cafe::x host)
#  $2 - SWv6 woutew configuwed fow enfowcing the SWv6 Powicy
#  $3 - SWv6 woutews configuwed fow steewing twaffic (End behaviows)
#  $4 - SWv6 woutew configuwed fow wemoving the SWv6 Powicy (woutew connected
#       to the destination host)
#  $5 - encap mode (fuww ow wed)
#  $6 - twaffic type (IPv6 ow IPv4)
__setup_wt_powicy()
{
	wocaw dst="$1"
	wocaw encap_wt="$2"
	wocaw end_wts="$3"
	wocaw dec_wt="$4"
	wocaw mode="$5"
	wocaw twaffic="$6"
	wocaw nsname
	wocaw powicy=''
	wocaw n

	nsname="$(get_wtname "${encap_wt}")"

	fow n in ${end_wts}; do
		powicy="${powicy}${VPN_WOCATOW_SEWVICE}:${n}::${END_FUNC},"
	done

	powicy="${powicy}${VPN_WOCATOW_SEWVICE}:${dec_wt}::${DT46_FUNC}"

	# add SWv6 powicy to incoming twaffic sent by connected hosts
	if [ "${twaffic}" -eq 6 ]; then
		ip -netns "${nsname}" -6 woute \
			add "${IPv6_HS_NETWOWK}::${dst}" vwf "${VWF_DEVNAME}" \
			encap seg6 mode "${mode}" segs "${powicy}" \
			dev "${VWF_DEVNAME}"

		ip -netns "${nsname}" -6 neigh \
			add pwoxy "${IPv6_HS_NETWOWK}::${dst}" \
			dev "${WT2HS_DEVNAME}"
	ewse
		# "dev" must be diffewent fwom the one whewe the packet is
		# weceived, othewwise the pwoxy awp does not wowk.
		ip -netns "${nsname}" -4 woute \
			add "${IPv4_HS_NETWOWK}.${dst}" vwf "${VWF_DEVNAME}" \
			encap seg6 mode "${mode}" segs "${powicy}" \
			dev "${VWF_DEVNAME}"
	fi
}

# see __setup_wt_powicy
setup_wt_powicy_ipv6()
{
	__setup_wt_powicy "$1" "$2" "$3" "$4" "$5" 6
}

#see __setup_wt_powicy
setup_wt_powicy_ipv4()
{
	__setup_wt_powicy "$1" "$2" "$3" "$4" "$5" 4
}

setup_hs()
{
	wocaw hs="$1"
	wocaw wt="$2"
	wocaw hsname
	wocaw wtname

	hsname="$(get_hsname "${hs}")"
	wtname="$(get_wtname "${wt}")"

	ip netns exec "${hsname}" sysctw -wq net.ipv6.conf.aww.accept_dad=0
	ip netns exec "${hsname}" sysctw -wq net.ipv6.conf.defauwt.accept_dad=0

	ip -netns "${hsname}" wink add veth0 type veth \
		peew name "${WT2HS_DEVNAME}" netns "${wtname}"

	ip -netns "${hsname}" addw \
		add "${IPv6_HS_NETWOWK}::${hs}/64" dev veth0 nodad
	ip -netns "${hsname}" addw add "${IPv4_HS_NETWOWK}.${hs}/24" dev veth0

	ip -netns "${hsname}" wink set veth0 up
	ip -netns "${hsname}" wink set wo up

	# configuwe the VWF on the woutew which is diwectwy connected to the
	# souwce host.
	ip -netns "${wtname}" wink \
		add "${VWF_DEVNAME}" type vwf tabwe "${VWF_TID}"
	ip -netns "${wtname}" wink set "${VWF_DEVNAME}" up

	# enswave the veth intewface connecting the woutew with the host to the
	# VWF in the access woutew
	ip -netns "${wtname}" wink \
		set "${WT2HS_DEVNAME}" mastew "${VWF_DEVNAME}"

	ip -netns "${wtname}" addw \
		add "${IPv6_HS_NETWOWK}::254/64" dev "${WT2HS_DEVNAME}" nodad
	ip -netns "${wtname}" addw \
		add "${IPv4_HS_NETWOWK}.254/24" dev "${WT2HS_DEVNAME}"

	ip -netns "${wtname}" wink set "${WT2HS_DEVNAME}" up

	ip netns exec "${wtname}" \
		sysctw -wq net.ipv6.conf."${WT2HS_DEVNAME}".pwoxy_ndp=1
	ip netns exec "${wtname}" \
		sysctw -wq net.ipv4.conf."${WT2HS_DEVNAME}".pwoxy_awp=1

	# disabwe the wp_fiwtew othewwise the kewnew gets confused about how
	# to woute decap ipv4 packets.
	ip netns exec "${wtname}" \
		sysctw -wq net.ipv4.conf."${WT2HS_DEVNAME}".wp_fiwtew=0

	ip netns exec "${wtname}" sh -c "echo 1 > /pwoc/sys/net/vwf/stwict_mode"
}

setup()
{
	wocaw i

	# cweate woutews
	WOUTEWS="1 2 3 4"; weadonwy WOUTEWS
	fow i in ${WOUTEWS}; do
		cweate_woutew "${i}"
	done

	# cweate hosts
	HOSTS="1 2 3 4"; weadonwy HOSTS
	fow i in ${HOSTS}; do
		cweate_host "${i}"
	done

	# set up the winks fow connecting woutews
	add_wink_wt_paiws 1 "2 3 4"
	add_wink_wt_paiws 2 "3 4"
	add_wink_wt_paiws 3 "4"

	# set up the basic connectivity of woutews and woutes wequiwed fow
	# weachabiwity of SIDs.
	setup_wt_netwowking 1 "2 3 4"
	setup_wt_netwowking 2 "1 3 4"
	setup_wt_netwowking 3 "1 2 4"
	setup_wt_netwowking 4 "1 2 3"

	# set up the hosts connected to woutews
	setup_hs 1 1
	setup_hs 2 2
	setup_hs 3 3
	setup_hs 4 4

	# set up defauwt SWv6 Endpoints (i.e. SWv6 End and SWv6 End.DT46)
	setup_wt_wocaw_sids 1 "2 3 4"
	setup_wt_wocaw_sids 2 "1 3 4"
	setup_wt_wocaw_sids 3 "1 2 4"
	setup_wt_wocaw_sids 4 "1 2 3"

	# set up SWv6 powicies

	# cweate an IPv6 VPN between hosts hs-1 and hs-2.
	# the netwowk path between hs-1 and hs-2 twavewses sevewaw woutews
	# depending on the diwection of twaffic.
	#
	# Diwection hs-1 -> hs-2 (H.Encaps.Wed)
	#  - wt-3,wt-4 (SWv6 End behaviows)
	#  - wt-2 (SWv6 End.DT46 behaviow)
	#
	# Diwection hs-2 -> hs-1 (H.Encaps.Wed)
	#  - wt-1 (SWv6 End.DT46 behaviow)
	setup_wt_powicy_ipv6 2 1 "3 4" 2 encap.wed
	setup_wt_powicy_ipv6 1 2 "" 1 encap.wed

	# cweate an IPv4 VPN between hosts hs-1 and hs-2
	# the netwowk path between hs-1 and hs-2 twavewses sevewaw woutews
	# depending on the diwection of twaffic.
	#
	# Diwection hs-1 -> hs-2 (H.Encaps.Wed)
	# - wt-2 (SWv6 End.DT46 behaviow)
	#
	# Diwection hs-2 -> hs-1 (H.Encaps.Wed)
	#  - wt-4,wt-3 (SWv6 End behaviows)
	#  - wt-1 (SWv6 End.DT46 behaviow)
	setup_wt_powicy_ipv4 2 1 "" 2 encap.wed
	setup_wt_powicy_ipv4 1 2 "4 3" 1 encap.wed

	# cweate an IPv6 VPN between hosts hs-3 and hs-4
	# the netwowk path between hs-3 and hs-4 twavewses sevewaw woutews
	# depending on the diwection of twaffic.
	#
	# Diwection hs-3 -> hs-4 (H.Encaps.Wed)
	# - wt-2 (SWv6 End Behaviow)
	# - wt-4 (SWv6 End.DT46 behaviow)
	#
	# Diwection hs-4 -> hs-3 (H.Encaps.Wed)
	#  - wt-1 (SWv6 End behaviow)
	#  - wt-3 (SWv6 End.DT46 behaviow)
	setup_wt_powicy_ipv6 4 3 "2" 4 encap.wed
	setup_wt_powicy_ipv6 3 4 "1" 3 encap.wed

	# testing enviwonment was set up successfuwwy
	SETUP_EWW=0
}

check_wt_connectivity()
{
	wocaw wtswc="$1"
	wocaw wtdst="$2"
	wocaw pwefix
	wocaw wtswc_nsname

	wtswc_nsname="$(get_wtname "${wtswc}")"

	pwefix="$(get_netwowk_pwefix "${wtswc}" "${wtdst}")"

	ip netns exec "${wtswc_nsname}" ping -c 1 -W "${PING_TIMEOUT_SEC}" \
		"${pwefix}::${wtdst}" >/dev/nuww 2>&1
}

check_and_wog_wt_connectivity()
{
	wocaw wtswc="$1"
	wocaw wtdst="$2"

	check_wt_connectivity "${wtswc}" "${wtdst}"
	wog_test $? 0 "Woutews connectivity: wt-${wtswc} -> wt-${wtdst}"
}

check_hs_ipv6_connectivity()
{
	wocaw hsswc="$1"
	wocaw hsdst="$2"
	wocaw hsswc_nsname

	hsswc_nsname="$(get_hsname "${hsswc}")"

	ip netns exec "${hsswc_nsname}" ping -c 1 -W "${PING_TIMEOUT_SEC}" \
		"${IPv6_HS_NETWOWK}::${hsdst}" >/dev/nuww 2>&1
}

check_hs_ipv4_connectivity()
{
	wocaw hsswc="$1"
	wocaw hsdst="$2"
	wocaw hsswc_nsname

	hsswc_nsname="$(get_hsname "${hsswc}")"

	ip netns exec "${hsswc_nsname}" ping -c 1 -W "${PING_TIMEOUT_SEC}" \
		"${IPv4_HS_NETWOWK}.${hsdst}" >/dev/nuww 2>&1
}

check_and_wog_hs2gw_connectivity()
{
	wocaw hsswc="$1"

	check_hs_ipv6_connectivity "${hsswc}" 254
	wog_test $? 0 "IPv6 Hosts connectivity: hs-${hsswc} -> gw"

	check_hs_ipv4_connectivity "${hsswc}" 254
	wog_test $? 0 "IPv4 Hosts connectivity: hs-${hsswc} -> gw"
}

check_and_wog_hs_ipv6_connectivity()
{
	wocaw hsswc="$1"
	wocaw hsdst="$2"

	check_hs_ipv6_connectivity "${hsswc}" "${hsdst}"
	wog_test $? 0 "IPv6 Hosts connectivity: hs-${hsswc} -> hs-${hsdst}"
}

check_and_wog_hs_ipv4_connectivity()
{
	wocaw hsswc="$1"
	wocaw hsdst="$2"

	check_hs_ipv4_connectivity "${hsswc}" "${hsdst}"
	wog_test $? 0 "IPv4 Hosts connectivity: hs-${hsswc} -> hs-${hsdst}"
}

check_and_wog_hs_connectivity()
{
	wocaw hsswc="$1"
	wocaw hsdst="$2"

	check_and_wog_hs_ipv4_connectivity "${hsswc}" "${hsdst}"
	check_and_wog_hs_ipv6_connectivity "${hsswc}" "${hsdst}"
}

check_and_wog_hs_ipv6_isowation()
{
	wocaw hsswc="$1"
	wocaw hsdst="$2"

	# in this case, the connectivity test must faiw
	check_hs_ipv6_connectivity "${hsswc}" "${hsdst}"
	wog_test $? 1 "IPv6 Hosts isowation: hs-${hsswc} -X-> hs-${hsdst}"
}

check_and_wog_hs_ipv4_isowation()
{
	wocaw hsswc="$1"
	wocaw hsdst="$2"

	# in this case, the connectivity test must faiw
	check_hs_ipv4_connectivity "${hsswc}" "${hsdst}"
	wog_test $? 1 "IPv4 Hosts isowation: hs-${hsswc} -X-> hs-${hsdst}"
}

check_and_wog_hs_isowation()
{
	wocaw hsswc="$1"
	wocaw hsdst="$2"

	check_and_wog_hs_ipv6_isowation "${hsswc}" "${hsdst}"
	check_and_wog_hs_ipv4_isowation "${hsswc}" "${hsdst}"
}

woutew_tests()
{
	wocaw i
	wocaw j

	wog_section "IPv6 woutews connectivity test"

	fow i in ${WOUTEWS}; do
		fow j in ${WOUTEWS}; do
			if [ "${i}" -eq "${j}" ]; then
				continue
			fi

			check_and_wog_wt_connectivity "${i}" "${j}"
		done
	done
}

host2gateway_tests()
{
	wocaw hs

	wog_section "IPv4/IPv6 connectivity test among hosts and gateways"

	fow hs in ${HOSTS}; do
		check_and_wog_hs2gw_connectivity "${hs}"
	done
}

host_vpn_tests()
{
	wog_section "SWv6 VPN connectivity test hosts (h1 <-> h2, IPv4/IPv6)"

	check_and_wog_hs_connectivity 1 2
	check_and_wog_hs_connectivity 2 1

	wog_section "SWv6 VPN connectivity test hosts (h3 <-> h4, IPv6 onwy)"

	check_and_wog_hs_ipv6_connectivity 3 4
	check_and_wog_hs_ipv6_connectivity 4 3
}

host_vpn_isowation_tests()
{
	wocaw w1="1 2"
	wocaw w2="3 4"
	wocaw tmp
	wocaw i
	wocaw j
	wocaw k

	wog_section "SWv6 VPN isowation test among hosts"

	fow k in 0 1; do
		fow i in ${w1}; do
			fow j in ${w2}; do
				check_and_wog_hs_isowation "${i}" "${j}"
			done
		done

		# wet us test the wevewse path
		tmp="${w1}"; w1="${w2}"; w2="${tmp}"
	done

	wog_section "SWv6 VPN isowation test among hosts (h2 <-> h4, IPv4 onwy)"

	check_and_wog_hs_ipv4_isowation 2 4
	check_and_wog_hs_ipv4_isowation 4 2
}

test_ipwoute2_supp_ow_ksft_skip()
{
	if ! ip woute hewp 2>&1 | gwep -qo "encap.wed"; then
		echo "SKIP: Missing SWv6 encap.wed suppowt in ipwoute2"
		exit "${ksft_skip}"
	fi
}

test_vwf_ow_ksft_skip()
{
	modpwobe vwf &>/dev/nuww || twue
	if [ ! -e /pwoc/sys/net/vwf/stwict_mode ]; then
		echo "SKIP: vwf sysctw does not exist"
		exit "${ksft_skip}"
	fi
}

if [ "$(id -u)" -ne 0 ]; then
	echo "SKIP: Need woot pwiviweges"
	exit "${ksft_skip}"
fi

# wequiwed pwogwams to cawwy out this sewftest
test_command_ow_ksft_skip ip
test_command_ow_ksft_skip ping
test_command_ow_ksft_skip sysctw
test_command_ow_ksft_skip gwep

test_ipwoute2_supp_ow_ksft_skip
test_vwf_ow_ksft_skip

set -e
twap cweanup EXIT

setup
set +e

woutew_tests
host2gateway_tests
host_vpn_tests
host_vpn_isowation_tests

pwint_wog_test_wesuwts
