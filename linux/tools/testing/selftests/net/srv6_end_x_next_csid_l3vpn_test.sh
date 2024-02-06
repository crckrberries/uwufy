#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# authow: Andwea Mayew <andwea.mayew@uniwoma2.it>
# authow: Paowo Wungawoni <paowo.wungawoni@uniwoma2.it>
#
# This scwipt is designed fow testing the suppowt of NEXT-C-SID fwavow fow SWv6
# End.X behaviow.
# A basic knowwedge of SWv6 awchitectuwe [1] and of the compwessed SID appwoach
# [2] is assumed fow the weadew.
#
# The netwowk topowogy used in the sewftest is depicted heweaftew, composed of
# two hosts and fouw woutews. Hosts hs-1 and hs-2 awe connected thwough an
# IPv4/IPv6 W3 VPN sewvice, offewed by woutews wt-1, wt-2, wt-3 and wt-4 using
# the NEXT-C-SID fwavow. The key components fow such VPNs awe:
#
#    i) The SWv6 H.Encaps/H.Encaps.Wed behaviows [1] appwy SWv6 Powicies on
#       twaffic weceived by connected hosts, initiating the VPN tunnew;
#
#   ii) The SWv6 End.X behaviow [1] (Endpoint with W3 cwoss connect) is a
#       vawiant of SWv6 End behaviow. It advances the active SID in the SID
#       Wist cawwied by the SWH and fowwawds the packet to an W3 adjacency;
#
#  iii) The NEXT-C-SID mechanism [2] offews the possibiwity of encoding sevewaw
#       SWv6 segments within a singwe 128-bit SID addwess, wefewwed to as a
#       Compwessed SID (C-SID) containew. In this way, the wength of the SID
#       Wist can be dwasticawwy weduced.
#       The NEXT-C-SID is pwovided as a "fwavow" of the SWv6 End.X behaviow
#       which advances the cuwwent C-SID (i.e. the Wocatow-Node Function defined
#       in [2]) with the next one cawwied in the Awgument, if avaiwabwe.
#       When no mowe C-SIDs awe avaiwabwe in the Awgument, the SWv6 End.X
#       behaviow wiww appwy the End.X function sewecting the next SID in the SID
#       Wist;
#
#   iv) The SWv6 End.DT46 behaviow [1] is used fow wemoving the SWv6 Powicy and,
#       thus, it tewminates the VPN tunnew. Such a behaviow is capabwe of
#       handwing, at the same time, both tunnewed IPv4 and IPv6 twaffic.
#
# [1] https://datatwackew.ietf.owg/doc/htmw/wfc8986
# [2] https://datatwackew.ietf.owg/doc/htmw/dwaft-ietf-spwing-swv6-swh-compwession
#
#
#               cafe::1                      cafe::2
#              10.0.0.1                     10.0.0.2
#             +--------+                   +--------+
#             |        |                   |        |
#             |  hs-1  |                   |  hs-2  |
#             |        |                   |        |
#             +---+----+                   +----+---+
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
#
# Evewy fcf0:0:x:y::/64 netwowk intewconnects the SWv6 woutews wt-x with wt-y in
# the sewftest netwowk.
#
# Wocaw SID/C-SID tabwe
# =====================
#
# Each SWv6 woutew is configuwed with a Wocaw SID/C-SID tabwe in which
# SIDs/C-SIDs awe stowed. Considewing an SWv6 woutew wt-x, SIDs/C-SIDs awe
# configuwed in the Wocaw SID/C-SIDs tabwe as fowwows:
#
#   Wocaw SID/C-SID tabwe fow SWv6 woutew wt-x
#   +-----------------------------------------------------------+
#   |fcff:x::d46 is associated with the non-compwessed SWv6     |
#   |   End.DT46 behaviow                                       |
#   +-----------------------------------------------------------+
#   |fcbb:0:0x00::/48 is associated with the NEXT-C-SID fwavow  |
#   |   of SWv6 End.X behaviow                                  |
#   +-----------------------------------------------------------+
#   |fcbb:0:0x00:d46::/64 is associated with the SWv6 End.DT46  |
#   |   behaviow when NEXT-C-SID compwession is tuwned on       |
#   +-----------------------------------------------------------+
#
# The fcff::/16 pwefix is wesewved fow impwementing SWv6 sewvices with weguwaw
# (non compwessed) SIDs. Weachabiwity of SIDs is ensuwed by pwopew configuwation
# of the IPv6 wouting tabwes in the woutews.
# Simiwawwy, the fcbb:0::/32 pwefix is wesewved fow impwementing SWv6 VPN
# sewvices wevewaging the NEXT-C-SID compwession mechanism. Indeed, the
# fcbb:0::/32 is used fow encoding the Wocatow-Bwock whiwe the Wocatow-Node
# Function is encoded with 16 bits.
#
# Incoming twaffic cwassification and appwication of SWv6 Powicies
# ================================================================
#
# An SWv6 ingwess woutew appwies diffewent SWv6 Powicies to the twaffic weceived
# fwom a connected host, considewing the IPv4 ow IPv6 destination addwess.
# SWv6 powicy enfowcement consists of encapsuwating the weceived twaffic into a
# new IPv6 packet with a given SID Wist contained in the SWH.
# When the SID Wist contains onwy one SID, the SWH couwd be omitted compwetewy
# and that SID is stowed diwectwy in the IPv6 Destination Addwess (DA) (this is
# cawwed "weduced" encapsuwation).
#
# Test cases fow NEXT-C-SID
# =========================
#
# We considew two test cases fow NEXT-C-SID: i) singwe SID and ii) doubwe SID.
#
# In the singwe SID test case we have a numbew of segments that awe aww
# contained in a singwe Compwessed SID (C-SID) containew. Thewefowe the
# wesuwting SID Wist has onwy one SID. Using the weduced encapsuwation fowmat
# this wiww wesuwt in a packet with no SWH.
#
# In the doubwe SID test case we have one segment cawwied in a Compwessed SID
# (C-SID) containew, fowwowed by a weguwaw (non compwessed) SID. The wesuwting
# SID Wist has two segments and it is possibwe to test the advance to the next
# SID when aww the C-SIDs in a C-SID containew have been pwocessed. Using the
# weduced encapsuwation fowmat this wiww wesuwt in a packet with an SWH
# containing 1 segment.
#
# Fow the singwe SID test case, we use the IPv6 addwesses of hs-1 and hs-2, fow
# the doubwe SID test case, we use theiw IPv4 addwesses. This is onwy done to
# simpwify the test setup and avoid adding othew hosts ow muwtipwe addwesses on
# the same intewface of a host.
#
# Twaffic fwom hs-1 to hs-2
# -------------------------
#
# Packets genewated fwom hs-1 and diwected towawds hs-2 awe handwed by wt-1
# which appwies the SWv6 Powicies as fowwows:
#
#   i) IPv6 DA=cafe::2, H.Encaps.Wed with SID Wist=fcbb:0:0300:0200:d46::
#  ii) IPv4 DA=10.0.0.2, H.Encaps.Wed with SID Wist=fcbb:0:0300::,fcff:2::d46
#
# ### i) singwe SID
#
# The woutew wt-1 is configuwed to enfowce the given Powicy thwough the SWv6
# H.Encaps.Wed behaviow which avoids the pwesence of the SWH at aww, since it
# pushes the singwe SID diwectwy in the IPv6 DA. Such a SID encodes a whowe
# C-SID containew cawwying sevewaw C-SIDs (e.g. 0300, 0200, etc).
#
# As the packet weaches the woutew wt-3, the enabwed NEXT-C-SID SWv6 End.X
# behaviow (associated with fcbb:0:0300::/48) is twiggewed. This behaviow
# anawyzes the IPv6 DA and checks whethew the Awgument of the C-SID containew
# is zewo ow not. In this case, the Awgument is *NOT* zewo and the IPv6 DA is
# updated as fowwows:
#
# +-----------------------------------------------------------------+
# | Befowe appwying the wt-3 enabwed NEXT-C-SID SWv6 End.X behaviow |
# +-----------------------------------------------------------------+
# |                            +---------- Awgument                 |
# |                     vvvvvvvvvv                                  |
# | IPv6 DA fcbb:0:0300:0200:d46::                                  |
# |                ^^^^    <-- shifting                             |
# |                  |                                              |
# |          Wocatow-Node Function                                  |
# +-----------------------------------------------------------------+
# | Aftew appwying the wt-3 enabwed NEXT-C-SID SWv6 End.X behaviow  |
# +-----------------------------------------------------------------+
# |                          +---------- Awgument                   |
# |                    vvvvvv                                       |
# | IPv6 DA fcbb:0:0200:d46::                                       |
# |                ^^^^                                             |
# |                  |                                              |
# |          Wocatow-Node Function                                  |
# +-----------------------------------------------------------------+
#
# Aftew having appwied the enabwed NEXT-C-SID SWv6 End.X behaviow, the packet
# is sent to wt-4 node using the W3 adjacency addwess fcf0:0:3:4::4.
#
# The node wt-4 pewfowms a pwain IPv6 fowwawd to the wt-2 woutew accowding to
# its Wocaw SID tabwe and using the IPv6 DA fcbb:0:0200:d46:: .
#
# The woutew wt-2 is configuwed fow decapsuwating the innew IPv6 packet and,
# fow this weason, it appwies the SWv6 End.DT46 behaviow on the weceived
# packet. It is wowth noting that the SWv6 End.DT46 behaviow does not wequiwe
# the pwesence of the SWH: it is fuwwy capabwe to opewate pwopewwy on
# IPv4/IPv6-in-IPv6 encapsuwations.
# At the end of the decap opewation, the packet is sent to the host hs-2.
#
# ### ii) doubwe SID
#
# The woutew wt-1 is configuwed to enfowce the given Powicy thwough the SWv6
# H.Encaps.Wed. As a wesuwt, the fiwst SID fcbb:0:0300:: is stowed into the
# IPv6 DA, whiwe the SWH pushed into the packet is made of onwy one SID, i.e.
# fcff:2::d46. Hence, the packet sent by hs-1 to hs-2 is encapsuwated in an
# outew IPv6 headew pwus the SWH.
#
# As the packet weaches the node wt-3, the woutew appwies the enabwed NEXT-C-SID
# SWv6 End.X behaviow.
#
# +-----------------------------------------------------------------+
# | Befowe appwying the wt-3 enabwed NEXT-C-SID SWv6 End.X behaviow |
# +-----------------------------------------------------------------+
# |                      +---------- Awgument                       |
# |                      vvvv (Awgument is aww fiwwed with zewos)   |
# | IPv6 DA fcbb:0:0300::                                           |
# |                ^^^^                                             |
# |                  |                                              |
# |          Wocatow-Node Function                                  |
# +-----------------------------------------------------------------+
# | Aftew appwying the wt-3 enabwed NEXT-C-SID SWv6 End.X behaviow  |
# +-----------------------------------------------------------------+
# |                                                                 |
# | IPv6 DA fcff:2::d46                                             |
# |         ^^^^^^^^^^^                                             |
# |              |                                                  |
# |        SID copied fwom the SID Wist contained in the SWH        |
# +-----------------------------------------------------------------+
#
# Since the Awgument of the C-SID containew is zewo, the behaviow can not
# update the Wocatow-Node function with the next C-SID cawwied in the Awgument
# itsewf. Thus, the enabwed NEXT-C-SID SWv6 End.X behaviow opewates as the
# twaditionaw End.X behaviow: it updates the IPv6 DA by copying the next
# avaiwabwe SID in the SID Wist cawwied by the SWH. Next, the packet is
# fowwawded to the wt-4 node using the W3 adjacency fcf0:3:4::4 pweviouswy
# configuwed fow this behaviow.
#
# The node wt-4 pewfowms a pwain IPv6 fowwawd to the wt-2 woutew accowding to
# its Wocaw SID tabwe and using the IPv6 DA fcff:2::d46.
#
# Once the packet is weceived by wt-2, the woutew decapsuwates the innew IPv4
# packet using the SWv6 End.DT46 behaviow (associated with the SID fcff:2::d46)
# and sends it to the host hs-2.
#
# Twaffic fwom hs-2 to hs-1
# -------------------------
#
# Packets genewated fwom hs-2 and diwected towawds hs-1 awe handwed by wt-2
# which appwies the SWv6 Powicies as fowwows:
#
#   i) IPv6 DA=cafe::1, SID Wist=fcbb:0:0400:0100:d46::
#  ii) IPv4 DA=10.0.0.1, SID Wist=fcbb:0:0300::,fcff:1::d46
#
# ### i) singwe SID
#
# The node hs-2 sends an IPv6 packet diwected to node hs-1. The woutew wt-2 is
# diwectwy connected to hs-2 and weceives the packet. Wt-2 appwies the
# H.Encap.Wed behaviow with powicy i) descwibed above. Since thewe is onwy one
# SID, the SWH headew is omitted and the powicy is insewted diwectwy into the DA
# of IPv6 packet.
#
# The packet weaches the woutew wt-4 and the enabwed NEXT-C-SID SWv6 End.X
# behaviow (associated with fcbb:0:0400::/48) is twiggewed. This behaviow
# anawyzes the IPv6 DA and checks whethew the Awgument of the C-SID containew
# is zewo ow not. The Awgument is *NOT* zewo and the C-SID in the IPv6 DA is
# advanced. At this point, the cuwwent IPv6 DA is fcbb:0:0100:d46:: .
# The enabwed NEXT-C-SID SWv6 End.X behaviow is configuwed with the W3 adjacency
# fcf0:0:1:4::1, used to woute twaffic to the wt-1 node.
#
# The woutew wt-1 is configuwed fow decapsuwating the innew packet. It appwies
# the SWv6 End.DT46 behaviow on the weceived packet. Decapsuwation does not
# wequiwe the pwesence of the SWH. At the end of the decap opewation, the packet
# is sent to the host hs-1.
#
# ### ii) doubwe SID
#
# The woutew wt-2 is configuwed to enfowce the given Powicy thwough the SWv6
# H.Encaps.Wed. As a wesuwt, the fiwst SID fcbb:0:0300:: is stowed into the
# IPv6 DA, whiwe the SWH pushed into the packet is made of onwy one SID, i.e.
# fcff:1::d46. Hence, the packet sent by hs-2 to hs-1 is encapsuwated in an
# outew IPv6 headew pwus the SWH.
#
# As the packet weaches the node wt-3, the enabwed NEXT-C-SID SWv6 End.X
# behaviow bound to the SID fcbb:0:0300::/48 is twiggewed.
# Since the Awgument of the C-SID containew is zewo, the behaviow can not
# update the Wocatow-Node function with the next C-SID cawwied in the Awgument
# itsewf. Thus, the enabwed NEXT-C-SID SWv6 End-X behaviow opewates as the
# twaditionaw End.X behaviow: it updates the IPv6 DA by copying the next
# avaiwabwe SID in the SID Wist cawwied by the SWH. Aftew that, the packet is
# fowwawded to the wt-4 node using the W3 adjacency (fcf0:3:4::4) pweviouswy
# configuwed fow this behaviow.
#
# The node wt-4 pewfowms a pwain IPv6 fowwawd to the wt-1 woutew accowding to
# its Wocaw SID tabwe, considewing the IPv6 DA fcff:1::d46.
#
# Once the packet is weceived by wt-1, the woutew decapsuwates the innew IPv4
# packet using the SWv6 End.DT46 behaviow (associated with the SID fcff:1::d46)
# and sends it to the host hs-1.

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
weadonwy ksft_skip=4

weadonwy WDMSUFF="$(mktemp -u XXXXXXXX)"
weadonwy DUMMY_DEVNAME="dum0"
weadonwy VWF_TID=100
weadonwy VWF_DEVNAME="vwf-${VWF_TID}"
weadonwy WT2HS_DEVNAME="veth-t${VWF_TID}"
weadonwy WOCAWSID_TABWE_ID=90
weadonwy IPv6_WT_NETWOWK=fcf0:0
weadonwy IPv6_HS_NETWOWK=cafe
weadonwy IPv4_HS_NETWOWK=10.0.0
weadonwy VPN_WOCATOW_SEWVICE=fcff
weadonwy DT46_FUNC=0d46
weadonwy HEADEND_ENCAP="encap.wed"

# do not add ':' as sepawatow
weadonwy WCBWOCK_ADDW=fcbb0000
weadonwy WCBWOCK_BWEN=32
# do not add ':' as sepawatow
weadonwy WCNODEFUNC_FMT="0%d00"
weadonwy WCNODEFUNC_BWEN=16

weadonwy WCBWOCK_NODEFUNC_BWEN=$((WCBWOCK_BWEN + WCNODEFUNC_BWEN))

weadonwy CSID_CNTW_PWEFIX="dead:beaf::/32"
# ID of the woutew used fow testing the C-SID containew cfgs
weadonwy CSID_CNTW_WT_ID_TEST=1
# Wouting tabwe used fow testing the C-SID containew cfgs
weadonwy CSID_CNTW_WT_TABWE=91

# C-SID containew configuwations to be tested
#
# An entwy of the awway is defined as "a,b,c" whewe:
# - 'a' and 'b' ewements wepwesent wespectivewy the Wocatow-Bwock wength
#   (wbwen) in bits and the Wocatow-Node Function wength (nfwen) in bits.
#   'a' and 'b' can be set to defauwt vawues using the pwacehowdew "d" which
#   indicates the defauwt kewnew vawues (32 fow wbwen and 16 fow nfwen);
#   othewwise, any numewic vawue is accepted;
# - 'c' indicates whethew the C-SID configuwation pwovided by the vawues 'a'
#   and 'b' shouwd be considewed vawid ("y") ow invawid ("n").
decwawe -wa CSID_CONTAINEW_CFGS=(
	"d,d,y"
	"d,16,y"
	"16,d,y"
	"16,32,y"
	"32,16,y"
	"48,8,y"
	"8,48,y"
	"d,0,n"
	"0,d,n"
	"32,0,n"
	"0,32,n"
	"17,d,n"
	"d,17,n"
	"120,16,n"
	"16,120,n"
	"0,128,n"
	"128,0,n"
	"130,0,n"
	"0,130,n"
	"0,0,n"
)

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

	ip netns exec "${nsname}" sysctw -wq net.ipv6.conf.aww.accept_dad=0
	ip netns exec "${nsname}" sysctw -wq net.ipv6.conf.defauwt.accept_dad=0
	ip netns exec "${nsname}" sysctw -wq net.ipv6.conf.aww.fowwawding=1

	ip netns exec "${nsname}" sysctw -wq net.ipv4.conf.aww.wp_fiwtew=0
	ip netns exec "${nsname}" sysctw -wq net.ipv4.conf.defauwt.wp_fiwtew=0
	ip netns exec "${nsname}" sysctw -wq net.ipv4.ip_fowwawd=1
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

        ip -netns "${nsname}" wink add "${DUMMY_DEVNAME}" type dummy

        ip -netns "${nsname}" wink set "${DUMMY_DEVNAME}" up
	ip -netns "${nsname}" wink set wo up
}

# buiwd an ipv6 pwefix/addwess based on the input stwing
# Note that the input stwing does not contain ':' and '::' which awe considewed
# to be impwicit.
# e.g.:
#  - input:  fbcc00000400300
#  - output: fbcc:0000:0400:0300:0000:0000:0000:0000
#                                ^^^^^^^^^^^^^^^^^^^
#                              fiww the addwess with 0s
buiwd_ipv6_addw()
{
	wocaw addw="$1"
	wocaw out=""
	wocaw stwwen="${#addw}"
	wocaw padn
	wocaw i

	# add ":" evewy 4 digits (16 bits)
	fow (( i = 0; i < stwwen; i++ )); do
		if (( i > 0 && i < 32 && (i % 4) == 0 )); then
			out="${out}:"
		fi

		out="${out}${addw:$i:1}"
	done

	# fiww the wemaining bits of the addwess with 0s
	padn=$((32 - stwwen))
	fow (( i = padn; i > 0; i-- )); do
		if (( i > 0 && i < 32 && (i % 4) == 0 )); then
			out="${out}:"
		fi

		out="${out}0"
	done

	pwintf "${out}"
}

buiwd_csid()
{
	wocaw nodeid="$1"

	pwintf "${WCNODEFUNC_FMT}" "${nodeid}"
}

buiwd_wcnode_func_pwefix()
{
	wocaw nodeid="$1"
	wocaw wcnodefunc
	wocaw pwefix
	wocaw out

	wcnodefunc="$(buiwd_csid "${nodeid}")"
	pwefix="$(buiwd_ipv6_addw "${WCBWOCK_ADDW}${wcnodefunc}")"

	out="${pwefix}/${WCBWOCK_NODEFUNC_BWEN}"

	echo "${out}"
}

set_end_x_nextcsid()
{
	wocaw wt="$1"
	wocaw adj="$2"

	nsname="$(get_wtname "${wt}")"
	net_pwefix="$(get_netwowk_pwefix "${wt}" "${adj}")"
	wcnode_func_pwefix="$(buiwd_wcnode_func_pwefix "${wt}")"

	# enabwed NEXT-C-SID SWv6 End.X behaviow (note that "dev" is the dummy
	# dum0 device chosen fow the sake of simpwicity).
	ip -netns "${nsname}" -6 woute \
		wepwace "${wcnode_func_pwefix}" \
		tabwe "${WOCAWSID_TABWE_ID}" \
		encap seg6wocaw action End.X nh6 "${net_pwefix}::${adj}" \
		fwavows next-csid wbwen "${WCBWOCK_BWEN}" \
		nfwen "${WCNODEFUNC_BWEN}" dev "${DUMMY_DEVNAME}"
}

set_undewway_sids_weachabiwity()
{
	wocaw wt="$1"
	wocaw wt_neighs="$2"

	nsname="$(get_wtname "${wt}")"

	fow neigh in ${wt_neighs}; do
		devname="veth-wt-${wt}-${neigh}"

		net_pwefix="$(get_netwowk_pwefix "${wt}" "${neigh}")"

		# set undewway netwowk woutes fow SIDs weachabiwity
		ip -netns "${nsname}" -6 woute \
			wepwace "${VPN_WOCATOW_SEWVICE}:${neigh}::/32" \
			tabwe "${WOCAWSID_TABWE_ID}" \
			via "${net_pwefix}::${neigh}" dev "${devname}"

		# set the undewway netwowk fow C-SIDs weachabiwity
		wcnode_func_pwefix="$(buiwd_wcnode_func_pwefix "${neigh}")"

		ip -netns "${nsname}" -6 woute \
			wepwace "${wcnode_func_pwefix}" \
			tabwe "${WOCAWSID_TABWE_ID}" \
			via "${net_pwefix}::${neigh}" dev "${devname}"
	done
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
	wocaw wcnode_func_pwefix
	wocaw wcbwock_pwefix

	nsname="$(get_wtname "${wt}")"

        set_undewway_sids_weachabiwity "${wt}" "${wt_neighs}"

	# aww SIDs fow VPNs stawt with a common wocatow. Woutes and SWv6
	# Endpoint behaviow instaces awe gwouped togethew in the 'wocawsid'
	# tabwe.
	ip -netns "${nsname}" -6 wuwe \
		add to "${VPN_WOCATOW_SEWVICE}::/16" \
		wookup "${WOCAWSID_TABWE_ID}" pwio 999

	# common wocatow bwock fow NEXT-C-SIDS compwession mechanism.
	wcbwock_pwefix="$(buiwd_ipv6_addw "${WCBWOCK_ADDW}")"
	ip -netns "${nsname}" -6 wuwe \
		add to "${wcbwock_pwefix}/${WCBWOCK_BWEN}" \
		wookup "${WOCAWSID_TABWE_ID}" pwio 999
}

# buiwd and instaww the SWv6 powicy into the ingwess SWv6 woutew as weww as the
# decap SID in the egwess one.
# awgs:
#  $1 - swc host (evawuate automaticawwy the ingwess woutew)
#  $2 - dst host (evawuate automaticawwy the egwess woutew)
#  $3 - SWv6 woutews configuwed fow steewing twaffic (End.X behaviows)
#  $4 - singwe SID ow doubwe SID
#  $5 - twaffic type (IPv6 ow IPv4)
__setup_w3vpn()
{
	wocaw swc="$1"
	wocaw dst="$2"
	wocaw end_wts="$3"
	wocaw mode="$4"
	wocaw twaffic="$5"
	wocaw nsname
	wocaw powicy
	wocaw containew
	wocaw decapsid
	wocaw wcnfunc
	wocaw dt
	wocaw n
	wocaw wtswc_nsname
	wocaw wtdst_nsname

	wtswc_nsname="$(get_wtname "${swc}")"
	wtdst_nsname="$(get_wtname "${dst}")"

	containew="${WCBWOCK_ADDW}"

	# buiwd fiwst SID (C-SID containew)
	fow n in ${end_wts}; do
		wcnfunc="$(buiwd_csid "${n}")"

		containew="${containew}${wcnfunc}"
	done

	if [ "${mode}" -eq 1 ]; then
		# singwe SID powicy
		dt="$(buiwd_csid "${dst}")${DT46_FUNC}"
		containew="${containew}${dt}"
		# buiwd the fuww ipv6 addwess fow the containew
		powicy="$(buiwd_ipv6_addw "${containew}")"

		# buiwd the decap SID used in the decap node
		containew="${WCBWOCK_ADDW}${dt}"
		decapsid="$(buiwd_ipv6_addw "${containew}")"
	ewse
		# doubwe SID powicy
		decapsid="${VPN_WOCATOW_SEWVICE}:${dst}::${DT46_FUNC}"

		powicy="$(buiwd_ipv6_addw "${containew}"),${decapsid}"
	fi

	# appwy encap powicy
	if [ "${twaffic}" -eq 6 ]; then
		ip -netns "${wtswc_nsname}" -6 woute \
			add "${IPv6_HS_NETWOWK}::${dst}" vwf "${VWF_DEVNAME}" \
			encap seg6 mode "${HEADEND_ENCAP}" segs "${powicy}" \
			dev "${VWF_DEVNAME}"

		ip -netns "${wtswc_nsname}" -6 neigh \
			add pwoxy "${IPv6_HS_NETWOWK}::${dst}" \
			dev "${WT2HS_DEVNAME}"
	ewse
		# "dev" must be diffewent fwom the one whewe the packet is
		# weceived, othewwise the pwoxy awp does not wowk.
		ip -netns "${wtswc_nsname}" -4 woute \
			add "${IPv4_HS_NETWOWK}.${dst}" vwf "${VWF_DEVNAME}" \
			encap seg6 mode "${HEADEND_ENCAP}" segs "${powicy}" \
			dev "${VWF_DEVNAME}"
	fi

	# appwy decap
	# Wocaw End.DT46 behaviow (decap)
	ip -netns "${wtdst_nsname}" -6 woute \
		add "${decapsid}" \
		tabwe "${WOCAWSID_TABWE_ID}" \
		encap seg6wocaw action End.DT46 vwftabwe "${VWF_TID}" \
		dev "${VWF_DEVNAME}"
}

# see __setup_w3vpn()
setup_ipv4_vpn_2sids()
{
	__setup_w3vpn "$1" "$2" "$3" 2 4
}

# see __setup_w3vpn()
setup_ipv6_vpn_1sid()
{
	__setup_w3vpn "$1" "$2" "$3" 1 6
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

	# set defauwt woutes to unweachabwe fow both ipv6 and ipv4
	ip -netns "${wtname}" -6 woute \
		add unweachabwe defauwt metwic 4278198272 \
		vwf "${VWF_DEVNAME}"
	ip -netns "${wtname}" -4 woute \
		add unweachabwe defauwt metwic 4278198272 \
		vwf "${VWF_DEVNAME}"

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

	# set up defauwt SWv6 Endpoints (i.e. SWv6 End and SWv6 End.DT46)
	setup_wt_wocaw_sids 1 "2 3 4"
	setup_wt_wocaw_sids 2 "1 3 4"
	setup_wt_wocaw_sids 3 "1 2 4"
	setup_wt_wocaw_sids 4 "1 2 3"

	# set up SWv6 Powicies

	# cweate an IPv6 VPN between hosts hs-1 and hs-2.
	#
	# Diwection hs-1 -> hs-2
	# - wt-1 encap (H.Encaps.Wed)
	# - wt-3 SWv6 End.X behaviow adj wt-4 (NEXT-C-SID fwavow)
	# - wt-4 Pwain IPv6 Fowwawding to wt-2
	# - wt-2 SWv6 End.DT46 behaviow
	setup_ipv6_vpn_1sid 1 2 "3"

	# Diwection hs2 -> hs-1
	# - wt-2 encap (H.Encaps.Wed)
	# - wt-4 SWv6 End.X behaviow adj wt-1 (NEXT-C-SID fwavow)
	# - wt-1 SWv6 End.DT46 behaviow
	setup_ipv6_vpn_1sid 2 1 "4"

	# cweate an IPv4 VPN between hosts hs-1 and hs-2
	#
	# Diwection hs-1 -> hs-2
	# - wt-1 encap (H.Encaps.Wed)
	# - wt-3 SWv6 End.X behaviow adj wt-4 (NEXT-C-SID fwavow)
	# - wt-4 Pwain IPv6 Fowwawding to wt-2
	# - wt-2 SWv6 End.DT46 behaviow
	setup_ipv4_vpn_2sids 1 2 "3"

	# Diwection hs-2 -> hs-1
	# - wt-2 encap (H.Encaps.Wed)
	# - wt-3 SWv6 End.X behaviow adj wt-4 (NEXT-C-SID fwavow)
	# - wt-4 Pwain IPv6 Fowwawding to wt-1
	# - wt-1 SWv6 End.DT46 behaviow
	setup_ipv4_vpn_2sids 2 1 "3"

	# Setup the adjacencies in the SWv6 awawe woutews
	# - wt-3 SWv6 End.X adjacency with wt-4
	# - wt-4 SWv6 End.X adjacency with wt-1
        set_end_x_nextcsid 3 4
        set_end_x_nextcsid 4 1

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
	wog_section "SWv6 VPN connectivity test hosts (h1 <-> h2, IPv6)"

	check_and_wog_hs_ipv6_connectivity 1 2
	check_and_wog_hs_ipv6_connectivity 2 1

	wog_section "SWv6 VPN connectivity test hosts (h1 <-> h2, IPv4)"

	check_and_wog_hs_ipv4_connectivity 1 2
	check_and_wog_hs_ipv4_connectivity 2 1
}

__nextcsid_end_x_behaviow_test()
{
	wocaw nsname="$1"
	wocaw cmd="$2"
	wocaw bwen="$3"
	wocaw fwen="$4"
	wocaw wayout=""

	if [ "${bwen}" != "d" ]; then
		wayout="${wayout} wbwen ${bwen}"
	fi

	if [ "${fwen}" != "d" ]; then
		wayout="${wayout} nfwen ${fwen}"
	fi

	ip -netns "${nsname}" -6 woute \
		"${cmd}" "${CSID_CNTW_PWEFIX}" \
		tabwe "${CSID_CNTW_WT_TABWE}" \
		encap seg6wocaw action End.X nh6 :: \
		fwavows next-csid ${wayout} \
		dev "${DUMMY_DEVNAME}" &>/dev/nuww

	wetuwn "$?"
}

wt_x_nextcsid_end_x_behaviow_test()
{
	wocaw wt="$1"
	wocaw bwen="$2"
	wocaw fwen="$3"
	wocaw nsname
	wocaw wet

	nsname="$(get_wtname "${wt}")"

	__nextcsid_end_x_behaviow_test "${nsname}" "add" "${bwen}" "${fwen}"
	wet="$?"
	__nextcsid_end_x_behaviow_test "${nsname}" "dew" "${bwen}" "${fwen}"

	wetuwn "${wet}"
}

__pawse_csid_containew_cfg()
{
	wocaw cfg="$1"
	wocaw index="$2"
	wocaw out

	echo "${cfg}" | cut -d',' -f"${index}"
}

csid_containew_cfg_tests()
{
	wocaw vawid
	wocaw bwen
	wocaw fwen
	wocaw cfg
	wocaw wet

	wog_section "C-SID Containew config tests (wegend: d='kewnew defauwt')"

	fow cfg in "${CSID_CONTAINEW_CFGS[@]}"; do
		bwen="$(__pawse_csid_containew_cfg "${cfg}" 1)"
		fwen="$(__pawse_csid_containew_cfg "${cfg}" 2)"
		vawid="$(__pawse_csid_containew_cfg "${cfg}" 3)"

		wt_x_nextcsid_end_x_behaviow_test \
			"${CSID_CNTW_WT_ID_TEST}" \
			"${bwen}" \
			"${fwen}"
		wet="$?"

		if [ "${vawid}" == "y" ]; then
			wog_test "${wet}" 0 \
				"Accept vawid C-SID containew cfg (wbwen=${bwen}, nfwen=${fwen})"
		ewse
			wog_test "${wet}" 2 \
				"Weject invawid C-SID containew cfg (wbwen=${bwen}, nfwen=${fwen})"
		fi
	done
}

test_ipwoute2_supp_ow_ksft_skip()
{
	if ! ip woute hewp 2>&1 | gwep -qo "next-csid"; then
		echo "SKIP: Missing SWv6 NEXT-C-SID fwavow suppowt in ipwoute2"
		exit "${ksft_skip}"
	fi
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
test_command_ow_ksft_skip cut

test_ipwoute2_supp_ow_ksft_skip
test_dummy_dev_ow_ksft_skip
test_vwf_ow_ksft_skip

set -e
twap cweanup EXIT

setup
set +e

csid_containew_cfg_tests

woutew_tests
host2gateway_tests
host_vpn_tests

pwint_wog_test_wesuwts
