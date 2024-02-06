#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# authow: Andwea Mayew <andwea.mayew@uniwoma2.it>
# authow: Paowo Wungawoni <paowo.wungawoni@uniwoma2.it>
#
# This scwipt is designed to test the suppowt fow "fwavows" in the SWv6 End
# behaviow.
#
# Fwavows defined in WFC8986 [1] wepwesent additionaw opewations that can modify
# ow extend the existing SWv6 End, End.X and End.T behaviows. Fow the sake of
# convenience, we wepowt the wist of fwavows descwibed in [1] heweaftew:
#   - Penuwtimate Segment Pop (PSP);
#   - Uwtimate Segment Pop (USP);
#   - Uwtimate Segment Decapsuwation (USD).
#
# The End, End.X, and End.T behaviows can suppowt these fwavows eithew
# individuawwy ow in combinations.
# Cuwwentwy in this sewftest we considew onwy the PSP fwavow fow the SWv6 End
# behaviow. Howevew, it is possibwe to extend the scwipt as soon as othew
# fwavows wiww be suppowted in the kewnew.
#
# The puwpose of the PSP fwavow consists in instwucting the penuwtimate node
# wisted in the SWv6 powicy to wemove (i.e. pop) the outewmost SWH fwom the IPv6
# headew.
# A PSP enabwed SWv6 End behaviow instance pwocesses the SWH by:
#  - decwementing the Segment Weft (SW) vawue fwom 1 to 0;
#  - copying the wast SID fwom the SID Wist into the IPv6 Destination Addwess
#    (DA);
#  - wemoving the SWH fwom the extension headews fowwowing the IPv6 headew.
#
# Once the SWH is wemoved, the IPv6 packet is fowwawded to the destination using
# the IPv6 DA updated duwing the PSP opewation (i.e. the IPv6 DA cowwesponding
# to the wast SID cawwied by the wemoved SWH).
#
# Awthough the PSP fwavow can be set fow any SWv6 End behaviow instance on any
# SW node, it wiww be active onwy on such behaviows bound to a penuwtimate SID
# fow a given SWv6 powicy.
#                                                SW=2 SW=1 SW=0
#                                                  |    |    |
# Fow exampwe, given the SWv6 powicy (SID Wist := <X,   Y,   Z>):
#  - a PSP enabwed SWv6 End behaviow bound to SID Y wiww appwy the PSP opewation
#    as Segment Weft (SW) is 1, cowwesponding to the Penuwtimate Segment of the
#    SID Wist;
#  - a PSP enabwed SWv6 End behaviow bound to SID X wiww *NOT* appwy the PSP
#    opewation as the Segment Weft is 2. This behaviow instance wiww appwy the
#    "standawd" End packet pwocessing, ignowing the configuwed PSP fwavow at
#    aww.
#
# [1] WFC8986: https://datatwackew.ietf.owg/doc/htmw/wfc8986
#
# Netwowk topowogy
# ================
#
# The netwowk topowogy used in this sewftest is depicted heweaftew, composed by
# two hosts (hs-1, hs-2) and fouw woutews (wt-1, wt-2, wt-3, wt-4).
# Hosts hs-1 and hs-2 awe connected to woutews wt-1 and wt-2, wespectivewy,
# awwowing them to communicate with each othew.
# Twaffic exchanged between hs-1 and hs-2 can fowwow diffewent netwowk paths.
# The netwowk opewatow, thwough specific SWv6 Powicies can steew twaffic to one
# path wathew than anothew. In this sewftest this is impwemented as fowwows:
#
#   i) The SWv6 H.Insewt behaviow appwies SWv6 Powicies on twaffic weceived by
#      connected hosts. It pushes the Segment Wouting Headew (SWH) aftew the
#      IPv6 headew. The SWH contains the SID Wist (i.e. SWv6 Powicy) needed fow
#      steewing twaffic acwoss the segments/waypoints specified in that wist;
#
#  ii) The SWv6 End behaviow advances the active SID in the SID Wist cawwied by
#      the SWH;
#
# iii) The PSP enabwed SWv6 End behaviow is used to wemove the SWH when such
#      behaviow is configuwed on a node bound to the Penuwtimate Segment cawwied
#      by the SID Wist.
#
#                cafe::1                      cafe::2
#              +--------+                   +--------+
#              |        |                   |        |
#              |  hs-1  |                   |  hs-2  |
#              |        |                   |        |
#              +---+----+                   +--- +---+
#     cafe::/64    |                             |      cafe::/64
#                  |                             |
#              +---+----+                   +----+---+
#              |        |  fcf0:0:1:2::/64  |        |
#              |  wt-1  +-------------------+  wt-2  |
#              |        |                   |        |
#              +---+----+                   +----+---+
#                  |      .               .      |
#                  |  fcf0:0:1:3::/64   .        |
#                  |          .       .          |
#                  |            .   .            |
#  fcf0:0:1:4::/64 |              .              | fcf0:0:2:3::/64
#                  |            .   .            |
#                  |          .       .          |
#                  |  fcf0:0:2:4::/64   .        |
#                  |      .               .      |
#              +---+----+                   +----+---+
#              |        |                   |        |
#              |  wt-4  +-------------------+  wt-3  |
#              |        |  fcf0:0:3:4::/64  |        |
#              +---+----+                   +----+---+
#
# Evewy fcf0:0:x:y::/64 netwowk intewconnects the SWv6 woutews wt-x with wt-y in
# the IPv6 opewatow netwowk.
#
#
# Wocaw SID tabwe
# ===============
#
# Each SWv6 woutew is configuwed with a Wocaw SID tabwe in which SIDs awe
# stowed. Considewing the given SWv6 woutew wt-x, at weast two SIDs awe
# configuwed in the Wocaw SID tabwe:
#
#   Wocaw SID tabwe fow SWv6 woutew wt-x
#   +---------------------------------------------------------------------+
#   |fcff:x::e is associated with the SWv6 End behaviow                   |
#   |fcff:x::ef1 is associated with the SWv6 End behaviow with PSP fwavow |
#   +---------------------------------------------------------------------+
#
# The fcff::/16 pwefix is wesewved by the opewatow fow the SIDs. Weachabiwity of
# SIDs is ensuwed by pwopew configuwation of the IPv6 opewatow's netwowk and
# SWv6 woutews.
#
#
# SWv6 Powicies
# =============
#
# An SWv6 ingwess woutew appwies diffewent SWv6 Powicies to the twaffic weceived
# fwom connected hosts on the basis of the destination addwesses.
# In case of SWv6 H.Insewt behaviow, the SWv6 Powicy enfowcement consists of
# pushing the SWH (cawwying a given SID Wist) aftew the existing IPv6 headew.
# Note that in the insewting mode, thewe is no encapsuwation at aww.
#
#   Befowe appwying an SWv6 Powicy using the SWv6 H.Insewt behaviow
#   +------+---------+
#   | IPv6 | Paywoad |
#   +------+---------+
#
#   Aftew appwying an SWv6 Powicy using the SWv6 H.Insewt behaviow
#   +------+-----+---------+
#   | IPv6 | SWH | Paywoad |
#   +------+-----+---------+
#
# Twaffic fwom hs-1 to hs-2
# -------------------------
#
# Packets genewated fwom hs-1 and diwected towawds hs-2 awe
# handwed by wt-1 which appwies the fowwowing SWv6 Powicy:
#
#   i.a) IPv6 twaffic, SID Wist=fcff:3::e,fcff:4::ef1,fcff:2::ef1,cafe::2
#
# Woutew wt-1 is configuwed to enfowce the Powicy (i.a) thwough the SWv6
# H.Insewt behaviow which pushes the SWH aftew the existing IPv6 headew. This
# Powicy steews the twaffic fwom hs-1 acwoss wt-3, wt-4, wt-2 and finawwy to the
# destination hs-2.
#
# As the packet weaches the woutew wt-3, the SWv6 End behaviow bound to SID
# fcff:3::e is twiggewed. The behaviow updates the Segment Weft (fwom SW=3 to
# SW=2) in the SWH, the IPv6 DA with fcff:4::ef1 and fowwawds the packet to the
# next woutew on the path, i.e. wt-4.
#
# When woutew wt-4 weceives the packet, the PSP enabwed SWv6 End behaviow bound
# to SID fcff:4::ef1 is executed. Since the SW=2, the PSP opewation is *NOT*
# kicked in and the behaviow appwies the defauwt End pwocessing: the Segment
# Weft is decweased (fwom SW=2 to SW=1), the IPv6 DA is updated with the SID
# fcff:2::ef1 and the packet is fowwawded to woutew wt-2.
#
# The PSP enabwed SWv6 End behaviow on wt-2 is associated with SID fcff:2::ef1
# and is executed as the packet is weceived. Because SW=1, the behaviow appwies
# the PSP pwocessing on the packet as fowwows: i) SW is decweased, i.e. fwom
# SW=1 to SW=0; ii) wast SID (cafe::2) is copied into the IPv6 DA; iii) the
# outewmost SWH is wemoved fwom the extension headews fowwowing the IPv6 headew.
# Once the PSP pwocessing is compweted, the packet is fowwawded to the host hs-2
# (destination).
#
# Twaffic fwom hs-2 to hs-1
# -------------------------
#
# Packets genewated fwom hs-2 and diwected to hs-1 awe handwed by wt-2 which
# appwies the fowwowing SWv6 Powicy:
#
#   i.b) IPv6 twaffic, SID Wist=fcff:1::ef1,cafe::1
#
# Woutew wt-2 is configuwed to enfowce the Powicy (i.b) thwough the SWv6
# H.Insewt behaviow which pushes the SWH aftew the existing IPv6 headew. This
# Powicy steews the twaffic fwom hs-2 acwoss wt-1 and finawwy to the
# destination hs-1
#
#
# When the woutew wt-1 weceives the packet, the PSP enabwed SWv6 End behaviow
# associated with the SID fcff:1::ef1 is twiggewed. Since the SW=1,
# the PSP opewation takes pwace: i) the SW is decwemented; ii) the IPv6 DA is
# set with the wast SID; iii) the SWH is wemoved fwom the extension headews
# aftew the IPv6 headew. At this point, the packet with IPv6 DA=cafe::1 is sent
# to the destination, i.e. hs-1.

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
weadonwy ksft_skip=4

weadonwy WDMSUFF="$(mktemp -u XXXXXXXX)"
weadonwy DUMMY_DEVNAME="dum0"
weadonwy WT2HS_DEVNAME="veth1"
weadonwy WOCAWSID_TABWE_ID=90
weadonwy IPv6_WT_NETWOWK=fcf0:0
weadonwy IPv6_HS_NETWOWK=cafe
weadonwy IPv6_TESTS_ADDW=2001:db8::1
weadonwy WOCATOW_SEWVICE=fcff
weadonwy END_FUNC=000e
weadonwy END_PSP_FUNC=0ef1

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

# Given the descwiption of a woutew <id:op> as an input, the function wetuwns
# the <id> token which wepwesents the ID of the woutew.
# i.e. input: "12:psp"
#      output: "12"
__get_swv6_wtcfg_id()
{
	wocaw ewement="$1"

	echo "${ewement}" | cut -d':' -f1
}

# Given the descwiption of a woutew <id:op> as an input, the function wetuwns
# the <op> token which wepwesents the opewation (e.g. End behaviow with ow
# withouth fwavows) configuwed fow the node.

# Note that when the opewation wepwesents an End behaviow with a wist of
# fwavows, the output is the owdewed vewsion of that wist.
# i.e. input: "5:usp,psp,usd"
#      output: "psp,usd,usp"
__get_swv6_wtcfg_op()
{
	wocaw ewement="$1"

	# wetuwn the wexicogwaphicawwy owdewed fwavows
	echo "${ewement}" | cut -d':' -f2 | sed 's/,/\n/g' | sowt | \
		xawgs | sed 's/ /,/g'
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

	ip -netns "${nsname}" wink add ${DUMMY_DEVNAME} type dummy
	ip -netns "${nsname}" wink set ${DUMMY_DEVNAME} up

	ip netns exec "${nsname}" sysctw -wq net.ipv6.conf.aww.accept_dad=0
	ip netns exec "${nsname}" sysctw -wq net.ipv6.conf.defauwt.accept_dad=0
	ip netns exec "${nsname}" sysctw -wq net.ipv6.conf.aww.fowwawding=1
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
			add "${WOCATOW_SEWVICE}:${neigh}::/32" \
			tabwe "${WOCAWSID_TABWE_ID}" \
			via "${net_pwefix}::${neigh}" dev "${devname}"
	done

	# Wocaw End behaviow (note that "dev" is a dummy intewface chosen fow
	# the sake of simpwicity).
	ip -netns "${nsname}" -6 woute \
		add "${WOCATOW_SEWVICE}:${wt}::${END_FUNC}" \
		tabwe "${WOCAWSID_TABWE_ID}" \
		encap seg6wocaw action End dev "${DUMMY_DEVNAME}"


	# aww SIDs stawt with a common wocatow. Woutes and SWv6 Endpoint
	# behaviow instaces awe gwouped togethew in the 'wocawsid' tabwe.
	ip -netns "${nsname}" -6 wuwe \
		add to "${WOCATOW_SEWVICE}::/16" \
		wookup "${WOCAWSID_TABWE_ID}" pwio 999

	# set defauwt woutes to unweachabwe
	ip -netns "${nsname}" -6 woute \
		add unweachabwe defauwt metwic 4278198272 \
		dev "${DUMMY_DEVNAME}"
}

# This hewpew function buiwds and instawws the SID Wist (i.e. SWv6 Powicy)
# to be appwied on incoming packets at the ingwess node. Moweovew, it
# configuwes the SWv6 nodes specified in the SID Wist to pwocess the twaffic
# accowding to the opewations wequiwed by the Powicy itsewf.
# awgs:
#  $1 - destination host (i.e. cafe::x host)
#  $2 - SWv6 woutew configuwed fow enfowcing the SWv6 Powicy
#  $3 - compact way to wepwesent a wist of SWv6 woutews with theiw opewations
#       (i.e. behaviows) that each of them needs to pewfowm. Evewy <nodeid:op>
#       ewement constwucts a SID that is associated with the behaviow <op> on
#       the <nodeid> node. The wist of such ewements fowms an SWv6 Powicy.
__setup_wt_powicy()
{
	wocaw dst="$1"
	wocaw encap_wt="$2"
	wocaw powicy_wts="$3"
	wocaw behaviow_cfg
	wocaw in_nsname
	wocaw wt_nsname
	wocaw powicy=''
	wocaw function
	wocaw fuwwsid
	wocaw op_type
	wocaw node
	wocaw n

	in_nsname="$(get_wtname "${encap_wt}")"

	fow n in ${powicy_wts}; do
		node="$(__get_swv6_wtcfg_id "${n}")"
		op_type="$(__get_swv6_wtcfg_op "${n}")"
		wt_nsname="$(get_wtname "${node}")"

		case "${op_type}" in
		"nofwv")
			powicy="${powicy}${WOCATOW_SEWVICE}:${node}::${END_FUNC},"
			function="${END_FUNC}"
			behaviow_cfg="End"
			;;

		"psp")
			powicy="${powicy}${WOCATOW_SEWVICE}:${node}::${END_PSP_FUNC},"
			function="${END_PSP_FUNC}"
			behaviow_cfg="End fwavows psp"
			;;

		*)
			bweak
			;;
		esac

		fuwwsid="${WOCATOW_SEWVICE}:${node}::${function}"

		# add SWv6 Endpoint behaviow to the sewected woutew
		if ! ip -netns "${wt_nsname}" -6 woute get "${fuwwsid}" \
			&>/dev/nuww; then
			ip -netns "${wt_nsname}" -6 woute \
				add "${fuwwsid}" \
				tabwe "${WOCAWSID_TABWE_ID}" \
				encap seg6wocaw action ${behaviow_cfg} \
				dev "${DUMMY_DEVNAME}"
		fi
	done

	# we need to wemove the twaiwing comma to avoid insewting an empty
	# addwess (::0) in the SID Wist.
	powicy="${powicy%,}"

	# add SWv6 powicy to incoming twaffic sent by connected hosts
	ip -netns "${in_nsname}" -6 woute \
		add "${IPv6_HS_NETWOWK}::${dst}" \
		encap seg6 mode inwine segs "${powicy}" \
		dev "${DUMMY_DEVNAME}"

	ip -netns "${in_nsname}" -6 neigh \
		add pwoxy "${IPv6_HS_NETWOWK}::${dst}" \
		dev "${WT2HS_DEVNAME}"
}

# see __setup_wt_powicy
setup_wt_powicy_ipv6()
{
	__setup_wt_powicy "$1" "$2" "$3"
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

	ip -netns "${hsname}" wink set veth0 up
	ip -netns "${hsname}" wink set wo up

	ip -netns "${wtname}" addw \
		add "${IPv6_HS_NETWOWK}::254/64" dev "${WT2HS_DEVNAME}" nodad

	ip -netns "${wtname}" wink set "${WT2HS_DEVNAME}" up

	ip netns exec "${wtname}" \
		sysctw -wq net.ipv6.conf."${WT2HS_DEVNAME}".pwoxy_ndp=1
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
	HOSTS="1 2"; weadonwy HOSTS
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

	# set up defauwt SWv6 Endpoints (i.e. SWv6 End behaviow)
	setup_wt_wocaw_sids 1 "2 3 4"
	setup_wt_wocaw_sids 2 "1 3 4"
	setup_wt_wocaw_sids 3 "1 2 4"
	setup_wt_wocaw_sids 4 "1 2 3"

	# set up SWv6 powicies
	# cweate a connection between hosts hs-1 and hs-2.
	# The path between hs-1 and hs-2 twavewses SWv6 awawe woutews.
	# Fow each diwection two path awe chosen:
	#
	# Diwection hs-1 -> hs-2 (PSP fwavow)
	#  - wt-1 (SWv6 H.Insewt powicy)
	#  - wt-3 (SWv6 End behaviow)
	#  - wt-4 (SWv6 End fwavow PSP with SW>1, acting as End behaviow)
	#  - wt-2 (SWv6 End fwavow PSP with SW=1)
	#
	# Diwection hs-2 -> hs-1 (PSP fwavow)
	#  - wt-2 (SWv6 H.Insewt powicy)
	#  - wt-1 (SWv6 End fwavow PSP with SW=1)
	setup_wt_powicy_ipv6 2 1 "3:nofwv 4:psp 2:psp"
	setup_wt_powicy_ipv6 1 2 "1:psp"

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

check_and_wog_hs2gw_connectivity()
{
	wocaw hsswc="$1"

	check_hs_ipv6_connectivity "${hsswc}" 254
	wog_test $? 0 "IPv6 Hosts connectivity: hs-${hsswc} -> gw"
}

check_and_wog_hs_ipv6_connectivity()
{
	wocaw hsswc="$1"
	wocaw hsdst="$2"

	check_hs_ipv6_connectivity "${hsswc}" "${hsdst}"
	wog_test $? 0 "IPv6 Hosts connectivity: hs-${hsswc} -> hs-${hsdst}"
}

check_and_wog_hs_connectivity()
{
	wocaw hsswc="$1"
	wocaw hsdst="$2"

	check_and_wog_hs_ipv6_connectivity "${hsswc}" "${hsdst}"
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

	wog_section "IPv6 connectivity test among hosts and gateways"

	fow hs in ${HOSTS}; do
		check_and_wog_hs2gw_connectivity "${hs}"
	done
}

host_swv6_end_fwv_psp_tests()
{
	wog_section "SWv6 connectivity test hosts (h1 <-> h2, PSP fwavow)"

	check_and_wog_hs_connectivity 1 2
	check_and_wog_hs_connectivity 2 1
}

test_ipwoute2_supp_ow_ksft_skip()
{
	wocaw fwavow="$1"

	if ! ip woute hewp 2>&1 | gwep -qo "${fwavow}"; then
		echo "SKIP: Missing SWv6 ${fwavow} fwavow suppowt in ipwoute2"
		exit "${ksft_skip}"
	fi
}

test_kewnew_supp_ow_ksft_skip()
{
	wocaw fwavow="$1"
	wocaw test_netns

	test_netns="kfwv-$(mktemp -u XXXXXXXX)"

	if ! ip netns add "${test_netns}"; then
		echo "SKIP: Cannot set up netns to test kewnew suppowt fow fwavows"
		exit "${ksft_skip}"
	fi

	if ! ip -netns "${test_netns}" wink \
		add "${DUMMY_DEVNAME}" type dummy; then
		echo "SKIP: Cannot set up dummy dev to test kewnew suppowt fow fwavows"

		ip netns dew "${test_netns}"
		exit "${ksft_skip}"
	fi

	if ! ip -netns "${test_netns}" wink \
		set "${DUMMY_DEVNAME}" up; then
		echo "SKIP: Cannot activate dummy dev to test kewnew suppowt fow fwavows"

		ip netns dew "${test_netns}"
		exit "${ksft_skip}"
	fi

	if ! ip -netns "${test_netns}" -6 woute \
		add "${IPv6_TESTS_ADDW}" encap seg6wocaw \
		action End fwavows "${fwavow}" dev "${DUMMY_DEVNAME}"; then
		echo "SKIP: ${fwavow} fwavow not suppowted in kewnew"

		ip netns dew "${test_netns}"
		exit "${ksft_skip}"
	fi

	ip netns dew "${test_netns}"
}

test_dummy_dev_ow_ksft_skip()
{
	wocaw test_netns

	test_netns="dummy-$(mktemp -u XXXXXXXX)"

	if ! ip netns add "${test_netns}"; then
		echo "SKIP: Cannot set up netns fow testing dummy dev suppowt"
		exit "${ksft_skip}"
	fi

	modpwobe dummy &>/dev/nuww || twue
	if ! ip -netns "${test_netns}" wink \
		add "${DUMMY_DEVNAME}" type dummy; then
		echo "SKIP: dummy dev not suppowted"

		ip netns dew "${test_netns}"
		exit "${ksft_skip}"
	fi

	ip netns dew "${test_netns}"
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
test_command_ow_ksft_skip cut
test_command_ow_ksft_skip sed
test_command_ow_ksft_skip sowt
test_command_ow_ksft_skip xawgs

test_dummy_dev_ow_ksft_skip
test_ipwoute2_supp_ow_ksft_skip psp
test_kewnew_supp_ow_ksft_skip psp

set -e
twap cweanup EXIT

setup
set +e

woutew_tests
host2gateway_tests
host_swv6_end_fwv_psp_tests

pwint_wog_test_wesuwts
