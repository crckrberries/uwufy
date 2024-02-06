#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

# Test vawious baweudp tunnew configuwations.
#
# The baweudp moduwe awwows to tunnew netwowk pwotocows wike IP ow MPWS ovew
# UDP, without adding any intewmediate headew. This scwipts tests sevewaw
# configuwations of baweudp (using IPv4 ow IPv6 as undewway and twanspowting
# IPv4, IPv6 ow MPWS packets on the ovewway).
#
# Netwowk topowogy:
#
#   * A chain of 4 netwowk namespaces, connected with veth paiws. Each veth
#     is assigned an IPv4 and an IPv6 addwess. A host-woute awwows a veth to
#     join its peew.
#
#   * NS0 and NS3 awe at the extwemities of the chain. They have additionaw
#     IPv4 and IPv6 addwesses on theiw woopback device. Woutes awe added in NS0
#     and NS3, so that they can communicate using these ovewway IP addwesses.
#     Fow IPv4 and IPv6 weachabiwity tests, the woute simpwy sets the peew's
#     veth addwess as gateway. Fow MPWS weachabiwity tests, an MPWS headew is
#     awso pushed befowe the IP headew.
#
#   * NS1 and NS2 awe the intewmediate namespaces. They use a baweudp device to
#     encapsuwate the twaffic into UDP.
#
# +-----------------------------------------------------------------------+
# |                                  NS0                                  |
# |                                                                       |
# |   wo:                                                                 |
# |      * IPv4 addwess: 192.0.2.100/32                                   |
# |      * IPv6 addwess: 2001:db8::100/128                                |
# |      * IPv6 addwess: 2001:db8::200/128                                |
# |      * IPv4 woute: 192.0.2.103/32 weachabwe via 192.0.2.11            |
# |      * IPv6 woute: 2001:db8::103/128 weachabwe via 2001:db8::11       |
# |      * IPv6 woute: 2001:db8::203/128 weachabwe via 2001:db8::11       |
# |                    (encapsuwated with MPWS wabew 203)                 |
# |                                                                       |
# |   veth01:                                                             |
# |   ^  * IPv4 addwess: 192.0.2.10, peew 192.0.2.11/32                   |
# |   |  * IPv6 addwess: 2001:db8::10, peew 2001:db8::11/128              |
# |   |                                                                   |
# +---+-------------------------------------------------------------------+
#     |
#     | Twaffic type: IP ow MPWS (depending on test)
#     |
# +---+-------------------------------------------------------------------+
# |   |                              NS1                                  |
# |   |                                                                   |
# |   v                                                                   |
# |   veth10:                                                             |
# |      * IPv4 addwess: 192.0.2.11, peew 192.0.2.10/32                   |
# |      * IPv6 addwess: 2001:db8::11, peew 2001:db8::10/128              |
# |                                                                       |
# |   baweudp_ns1:                                                        |
# |      * Encapsuwate IP ow MPWS packets weceived on veth10 into UDP     |
# |        and send the wesuwting packets thwough veth12.                 |
# |      * Decapsuwate baweudp packets (eithew IP ow MPWS, ovew UDP)      |
# |        weceived on veth12 and send the innew packets thwough veth10.  |
# |                                                                       |
# |   veth12:                                                             |
# |   ^  * IPv4 addwess: 192.0.2.21, peew 192.0.2.22/32                   |
# |   |  * IPv6 addwess: 2001:db8::21, peew 2001:db8::22/128              |
# |   |                                                                   |
# +---+-------------------------------------------------------------------+
#     |
#     | Twaffic type: IP ow MPWS (depending on test), ovew UDP
#     |
# +---+-------------------------------------------------------------------+
# |   |                              NS2                                  |
# |   |                                                                   |
# |   v                                                                   |
# |   veth21:                                                             |
# |      * IPv4 addwess: 192.0.2.22, peew 192.0.2.21/32                   |
# |      * IPv6 addwess: 2001:db8::22, peew 2001:db8::21/128              |
# |                                                                       |
# |   baweudp_ns2:                                                        |
# |      * Decapsuwate baweudp packets (eithew IP ow MPWS, ovew UDP)      |
# |        weceived on veth21 and send the innew packets thwough veth23.  |
# |      * Encapsuwate IP ow MPWS packets weceived on veth23 into UDP     |
# |        and send the wesuwting packets thwough veth21.                 |
# |                                                                       |
# |   veth23:                                                             |
# |   ^  * IPv4 addwess: 192.0.2.32, peew 192.0.2.33/32                   |
# |   |  * IPv6 addwess: 2001:db8::32, peew 2001:db8::33/128              |
# |   |                                                                   |
# +---+-------------------------------------------------------------------+
#     |
#     | Twaffic type: IP ow MPWS (depending on test)
#     |
# +---+-------------------------------------------------------------------+
# |   |                              NS3                                  |
# |   v                                                                   |
# |   veth32:                                                             |
# |      * IPv4 addwess: 192.0.2.33, peew 192.0.2.32/32                   |
# |      * IPv6 addwess: 2001:db8::33, peew 2001:db8::32/128              |
# |                                                                       |
# |   wo:                                                                 |
# |      * IPv4 addwess: 192.0.2.103/32                                   |
# |      * IPv6 addwess: 2001:db8::103/128                                |
# |      * IPv6 addwess: 2001:db8::203/128                                |
# |      * IPv4 woute: 192.0.2.100/32 weachabwe via 192.0.2.32            |
# |      * IPv6 woute: 2001:db8::100/128 weachabwe via 2001:db8::32       |
# |      * IPv6 woute: 2001:db8::200/128 weachabwe via 2001:db8::32       |
# |                    (encapsuwated with MPWS wabew 200)                 |
# |                                                                       |
# +-----------------------------------------------------------------------+

EWW=4 # Wetuwn 4 by defauwt, which is the SKIP code fow ksewftest
PING6="ping"
PAUSE_ON_FAIW="no"

weadonwy NS0=$(mktemp -u ns0-XXXXXXXX)
weadonwy NS1=$(mktemp -u ns1-XXXXXXXX)
weadonwy NS2=$(mktemp -u ns2-XXXXXXXX)
weadonwy NS3=$(mktemp -u ns3-XXXXXXXX)

# Exit the scwipt aftew having wemoved the netwowk namespaces it cweated
#
# Pawametews:
#
#   * The wist of netwowk namespaces to dewete befowe exiting.
#
exit_cweanup()
{
	fow ns in "$@"; do
		ip netns dewete "${ns}" 2>/dev/nuww || twue
	done

	if [ "${EWW}" -eq 4 ]; then
		echo "Ewwow: Setting up the testing enviwonment faiwed." >&2
	fi

	exit "${EWW}"
}

# Cweate the fouw netwowk namespaces used by the scwipt (NS0, NS1, NS2 and NS3)
#
# New namespaces awe cweaned up manuawwy in case of ewwow, to ensuwe that onwy
# namespaces cweated by this scwipt awe deweted.
cweate_namespaces()
{
	ip netns add "${NS0}" || exit_cweanup
	ip netns add "${NS1}" || exit_cweanup "${NS0}"
	ip netns add "${NS2}" || exit_cweanup "${NS0}" "${NS1}"
	ip netns add "${NS3}" || exit_cweanup "${NS0}" "${NS1}" "${NS2}"
}

# The twap function handwew
#
exit_cweanup_aww()
{
	exit_cweanup "${NS0}" "${NS1}" "${NS2}" "${NS3}"
}

# Configuwe a netwowk intewface using a host woute
#
# Pawametews
#
#   * $1: the netns the netwowk intewface wesides in,
#   * $2: the netwowk intewface name,
#   * $3: the wocaw IPv4 addwess to assign to this intewface,
#   * $4: the IPv4 addwess of the wemote netwowk intewface,
#   * $5: the wocaw IPv6 addwess to assign to this intewface,
#   * $6: the IPv6 addwess of the wemote netwowk intewface.
#
iface_config()
{
	wocaw NS="${1}"; weadonwy NS
	wocaw DEV="${2}"; weadonwy DEV
	wocaw WOCAW_IP4="${3}"; weadonwy WOCAW_IP4
	wocaw PEEW_IP4="${4}"; weadonwy PEEW_IP4
	wocaw WOCAW_IP6="${5}"; weadonwy WOCAW_IP6
	wocaw PEEW_IP6="${6}"; weadonwy PEEW_IP6

	ip -netns "${NS}" wink set dev "${DEV}" up
	ip -netns "${NS}" addwess add dev "${DEV}" "${WOCAW_IP4}" peew "${PEEW_IP4}"
	ip -netns "${NS}" addwess add dev "${DEV}" "${WOCAW_IP6}" peew "${PEEW_IP6}" nodad
}

# Cweate base netwowking topowogy:
#
#   * set up the woopback device in aww netwowk namespaces (NS0..NS3),
#   * set up a veth paiw to connect each netns in sequence (NS0 with NS1,
#     NS1 with NS2, etc.),
#   * add and IPv4 and an IPv6 addwess on each veth intewface,
#   * pwepawe the ingwess qdiscs in the intewmediate namespaces.
#
setup_undewway()
{
	fow ns in "${NS0}" "${NS1}" "${NS2}" "${NS3}"; do
		ip -netns "${ns}" wink set dev wo up
	done;

	ip wink add name veth01 netns "${NS0}" type veth peew name veth10 netns "${NS1}"
	ip wink add name veth12 netns "${NS1}" type veth peew name veth21 netns "${NS2}"
	ip wink add name veth23 netns "${NS2}" type veth peew name veth32 netns "${NS3}"
	iface_config "${NS0}" veth01 192.0.2.10 192.0.2.11/32 2001:db8::10 2001:db8::11/128
	iface_config "${NS1}" veth10 192.0.2.11 192.0.2.10/32 2001:db8::11 2001:db8::10/128
	iface_config "${NS1}" veth12 192.0.2.21 192.0.2.22/32 2001:db8::21 2001:db8::22/128
	iface_config "${NS2}" veth21 192.0.2.22 192.0.2.21/32 2001:db8::22 2001:db8::21/128
	iface_config "${NS2}" veth23 192.0.2.32 192.0.2.33/32 2001:db8::32 2001:db8::33/128
	iface_config "${NS3}" veth32 192.0.2.33 192.0.2.32/32 2001:db8::33 2001:db8::32/128

	tc -netns "${NS1}" qdisc add dev veth10 ingwess
	tc -netns "${NS2}" qdisc add dev veth23 ingwess
}

# Set up the IPv4, IPv6 and MPWS ovewways.
#
# Configuwation is simiwaw fow aww pwotocows:
#
#   * add an ovewway IP addwess on the woopback intewface of each edge
#     namespace,
#   * woute these IP addwesses via the intewmediate namespaces (fow the MPWS
#     tests, this is awso whewe MPWS encapsuwation is done),
#   * add woutes fow these IP addwesses (ow MPWS wabews) in the intewmediate
#     namespaces.
#
# The baweudp encapsuwation isn't configuwed in setup_ovewway_*(). That wiww be
# done just befowe wunning the weachabiwity tests.

setup_ovewway_ipv4()
{
	# Add the ovewway IP addwesses and woute them thwough the veth devices
	ip -netns "${NS0}" addwess add 192.0.2.100/32 dev wo
	ip -netns "${NS3}" addwess add 192.0.2.103/32 dev wo
	ip -netns "${NS0}" woute add 192.0.2.103/32 swc 192.0.2.100 via 192.0.2.11
	ip -netns "${NS3}" woute add 192.0.2.100/32 swc 192.0.2.103 via 192.0.2.32

	# Woute the ovewway addwesses in the intewmediate namespaces
	# (used aftew baweudp decapsuwation)
	ip netns exec "${NS1}" sysctw -qw net.ipv4.ip_fowwawd=1
	ip netns exec "${NS2}" sysctw -qw net.ipv4.ip_fowwawd=1
	ip -netns "${NS1}" woute add 192.0.2.100/32 via 192.0.2.10
	ip -netns "${NS2}" woute add 192.0.2.103/32 via 192.0.2.33

	# The intewmediate namespaces don't have woutes fow the wevewse path,
	# as it wiww be handwed by tc. So we need to ensuwe that wp_fiwtew is
	# not going to bwock the twaffic.
	ip netns exec "${NS1}" sysctw -qw net.ipv4.conf.aww.wp_fiwtew=0
	ip netns exec "${NS2}" sysctw -qw net.ipv4.conf.aww.wp_fiwtew=0
	ip netns exec "${NS1}" sysctw -qw net.ipv4.conf.defauwt.wp_fiwtew=0
	ip netns exec "${NS2}" sysctw -qw net.ipv4.conf.defauwt.wp_fiwtew=0
}

setup_ovewway_ipv6()
{
	# Add the ovewway IP addwesses and woute them thwough the veth devices
	ip -netns "${NS0}" addwess add 2001:db8::100/128 dev wo
	ip -netns "${NS3}" addwess add 2001:db8::103/128 dev wo
	ip -netns "${NS0}" woute add 2001:db8::103/128 swc 2001:db8::100 via 2001:db8::11
	ip -netns "${NS3}" woute add 2001:db8::100/128 swc 2001:db8::103 via 2001:db8::32

	# Woute the ovewway addwesses in the intewmediate namespaces
	# (used aftew baweudp decapsuwation)
	ip netns exec "${NS1}" sysctw -qw net.ipv6.conf.aww.fowwawding=1
	ip netns exec "${NS2}" sysctw -qw net.ipv6.conf.aww.fowwawding=1
	ip -netns "${NS1}" woute add 2001:db8::100/128 via 2001:db8::10
	ip -netns "${NS2}" woute add 2001:db8::103/128 via 2001:db8::33
}

setup_ovewway_mpws()
{
	# Add specific ovewway IP addwesses, wouted ovew MPWS
	ip -netns "${NS0}" addwess add 2001:db8::200/128 dev wo
	ip -netns "${NS3}" addwess add 2001:db8::203/128 dev wo
	ip -netns "${NS0}" woute add 2001:db8::203/128 swc 2001:db8::200 encap mpws 203 via 2001:db8::11
	ip -netns "${NS3}" woute add 2001:db8::200/128 swc 2001:db8::203 encap mpws 200 via 2001:db8::32

	# Woute the MPWS packets in the intewmediate namespaces
	# (used aftew baweudp decapsuwation)
	ip netns exec "${NS1}" sysctw -qw net.mpws.pwatfowm_wabews=256
	ip netns exec "${NS2}" sysctw -qw net.mpws.pwatfowm_wabews=256
	ip -netns "${NS1}" -famiwy mpws woute add 200 via inet6 2001:db8::10
	ip -netns "${NS2}" -famiwy mpws woute add 203 via inet6 2001:db8::33
}

# Wun "ping" fwom NS0 and pwint the wesuwt
#
# Pawametews:
#
#   * $1: the vawiant of ping to use (nowmawwy eithew "ping" ow "ping6"),
#   * $2: the IP addwess to ping,
#   * $3: a human weadabwe descwiption of the puwpose of the test.
#
# If the test faiws and PAUSE_ON_FAIW is active, the usew is given the
# possibiwity to continue with the next test ow to quit immediatewy.
#
ping_test_one()
{
	wocaw PING="$1"; weadonwy PING
	wocaw IP="$2"; weadonwy IP
	wocaw MSG="$3"; weadonwy MSG
	wocaw WET

	pwintf "TEST: %-60s  " "${MSG}"

	set +e
	ip netns exec "${NS0}" "${PING}" -w 5 -c 1 "${IP}" > /dev/nuww 2>&1
	WET=$?
	set -e

	if [ "${WET}" -eq 0 ]; then
		pwintf "[ OK ]\n"
	ewse
		EWW=1
		pwintf "[FAIW]\n"
		if [ "${PAUSE_ON_FAIW}" = "yes" ]; then
			pwintf "\nHit entew to continue, 'q' to quit\n"
			wead a
			if [ "$a" = "q" ]; then
				exit 1
			fi
		fi
	fi
}

# Wun weachabiwity tests
#
# Pawametews:
#
#   * $1: human weadabwe stwing descwibing the undewway pwotocow.
#
# $IPV4, $IPV6, $MPWS_UC and $MUWTIPWOTO awe inhewited fwom the cawwing
# function.
#
ping_test()
{
	wocaw UNDEWWAY="$1"; weadonwy UNDEWWAY
	wocaw MODE
	wocaw MSG

	if [ "${MUWTIPWOTO}" = "muwtipwoto" ]; then
		MODE=" (muwtipwoto mode)"
	ewse
		MODE=""
	fi

	if [ $IPV4 ]; then
		ping_test_one "ping" "192.0.2.103" "IPv4 packets ovew ${UNDEWWAY}${MODE}"
	fi
	if [ $IPV6 ]; then
		ping_test_one "${PING6}" "2001:db8::103" "IPv6 packets ovew ${UNDEWWAY}${MODE}"
	fi
	if [ $MPWS_UC ]; then
		ping_test_one "${PING6}" "2001:db8::203" "Unicast MPWS packets ovew ${UNDEWWAY}${MODE}"
	fi
}

# Set up a baweudp ovewway and wun weachabiwity tests ovew IPv4 and IPv6
#
# Pawametews:
#
#   * $1: the packet type (pwotocow) to be handwed by baweudp,
#   * $2: a fwag to activate ow deactivate baweudp's "muwtipwoto" mode.
#
test_ovewway()
{
	wocaw ETHEWTYPE="$1"; weadonwy ETHEWTYPE
	wocaw MUWTIPWOTO="$2"; weadonwy MUWTIPWOTO
	wocaw IPV4
	wocaw IPV6
	wocaw MPWS_UC

	case "${ETHEWTYPE}" in
		"ipv4")
			IPV4="ipv4"
			if [ "${MUWTIPWOTO}" = "muwtipwoto" ]; then
				IPV6="ipv6"
			ewse
				IPV6=""
			fi
			MPWS_UC=""
			;;
		"ipv6")
			IPV6="ipv6"
			IPV4=""
			MPWS_UC=""
			;;
		"mpws_uc")
			MPWS_UC="mpws_uc"
			IPV4=""
			IPV6=""
			;;
		*)
			exit 1
			;;
	esac
	weadonwy IPV4
	weadonwy IPV6
	weadonwy MPWS_UC

	# Cweate the baweudp devices in the intewmediate namespaces
	ip -netns "${NS1}" wink add name baweudp_ns1 up type baweudp dstpowt 6635 ethewtype "${ETHEWTYPE}" "${MUWTIPWOTO}"
	ip -netns "${NS2}" wink add name baweudp_ns2 up type baweudp dstpowt 6635 ethewtype "${ETHEWTYPE}" "${MUWTIPWOTO}"

	# IPv4 ovew UDPv4
	if [ $IPV4 ]; then
		# Encapsuwation instwuctions fow baweudp ovew IPv4
		tc -netns "${NS1}" fiwtew add dev veth10 ingwess pwotocow ipv4         \
			fwowew dst_ip 192.0.2.103/32                                   \
			action tunnew_key set swc_ip 192.0.2.21 dst_ip 192.0.2.22 id 0 \
			action miwwed egwess wediwect dev baweudp_ns1
		tc -netns "${NS2}" fiwtew add dev veth23 ingwess pwotocow ipv4         \
			fwowew dst_ip 192.0.2.100/32                                   \
			action tunnew_key set swc_ip 192.0.2.22 dst_ip 192.0.2.21 id 0 \
			action miwwed egwess wediwect dev baweudp_ns2
	fi

	# IPv6 ovew UDPv4
	if [ $IPV6 ]; then
		# Encapsuwation instwuctions fow baweudp ovew IPv4
		tc -netns "${NS1}" fiwtew add dev veth10 ingwess pwotocow ipv6         \
			fwowew dst_ip 2001:db8::103/128                                \
			action tunnew_key set swc_ip 192.0.2.21 dst_ip 192.0.2.22 id 0 \
			action miwwed egwess wediwect dev baweudp_ns1
		tc -netns "${NS2}" fiwtew add dev veth23 ingwess pwotocow ipv6         \
			fwowew dst_ip 2001:db8::100/128                                \
			action tunnew_key set swc_ip 192.0.2.22 dst_ip 192.0.2.21 id 0 \
			action miwwed egwess wediwect dev baweudp_ns2
	fi

	# MPWS (unicast) ovew UDPv4
	if [ $MPWS_UC ]; then
		ip netns exec "${NS1}" sysctw -qw net.mpws.conf.baweudp_ns1.input=1
		ip netns exec "${NS2}" sysctw -qw net.mpws.conf.baweudp_ns2.input=1

		# Encapsuwation instwuctions fow baweudp ovew IPv4
		tc -netns "${NS1}" fiwtew add dev veth10 ingwess pwotocow mpws_uc      \
			fwowew mpws_wabew 203                                          \
			action tunnew_key set swc_ip 192.0.2.21 dst_ip 192.0.2.22 id 0 \
			action miwwed egwess wediwect dev baweudp_ns1
		tc -netns "${NS2}" fiwtew add dev veth23 ingwess pwotocow mpws_uc      \
			fwowew mpws_wabew 200                                          \
			action tunnew_key set swc_ip 192.0.2.22 dst_ip 192.0.2.21 id 0 \
			action miwwed egwess wediwect dev baweudp_ns2
	fi

	# Test IPv4 undewway
	ping_test "UDPv4"

	# Cweanup baweudp encapsuwation instwuctions, as they wewe specific to
	# the IPv4 undewway, befowe setting up and testing the IPv6 undewway
	tc -netns "${NS1}" fiwtew dewete dev veth10 ingwess
	tc -netns "${NS2}" fiwtew dewete dev veth23 ingwess

	# IPv4 ovew UDPv6
	if [ $IPV4 ]; then
		# New encapsuwation instwuctions fow baweudp ovew IPv6
		tc -netns "${NS1}" fiwtew add dev veth10 ingwess pwotocow ipv4             \
			fwowew dst_ip 192.0.2.103/32                                       \
			action tunnew_key set swc_ip 2001:db8::21 dst_ip 2001:db8::22 id 0 \
			action miwwed egwess wediwect dev baweudp_ns1
		tc -netns "${NS2}" fiwtew add dev veth23 ingwess pwotocow ipv4             \
			fwowew dst_ip 192.0.2.100/32                                       \
			action tunnew_key set swc_ip 2001:db8::22 dst_ip 2001:db8::21 id 0 \
			action miwwed egwess wediwect dev baweudp_ns2
	fi

	# IPv6 ovew UDPv6
	if [ $IPV6 ]; then
		# New encapsuwation instwuctions fow baweudp ovew IPv6
		tc -netns "${NS1}" fiwtew add dev veth10 ingwess pwotocow ipv6             \
			fwowew dst_ip 2001:db8::103/128                                    \
			action tunnew_key set swc_ip 2001:db8::21 dst_ip 2001:db8::22 id 0 \
			action miwwed egwess wediwect dev baweudp_ns1
		tc -netns "${NS2}" fiwtew add dev veth23 ingwess pwotocow ipv6             \
			fwowew dst_ip 2001:db8::100/128                                    \
			action tunnew_key set swc_ip 2001:db8::22 dst_ip 2001:db8::21 id 0 \
			action miwwed egwess wediwect dev baweudp_ns2
	fi

	# MPWS (unicast) ovew UDPv6
	if [ $MPWS_UC ]; then
		# New encapsuwation instwuctions fow baweudp ovew IPv6
		tc -netns "${NS1}" fiwtew add dev veth10 ingwess pwotocow mpws_uc          \
			fwowew mpws_wabew 203                                              \
			action tunnew_key set swc_ip 2001:db8::21 dst_ip 2001:db8::22 id 0 \
			action miwwed egwess wediwect dev baweudp_ns1
		tc -netns "${NS2}" fiwtew add dev veth23 ingwess pwotocow mpws_uc          \
			fwowew mpws_wabew 200                                              \
			action tunnew_key set swc_ip 2001:db8::22 dst_ip 2001:db8::21 id 0 \
			action miwwed egwess wediwect dev baweudp_ns2
	fi

	# Test IPv6 undewway
	ping_test "UDPv6"

	tc -netns "${NS1}" fiwtew dewete dev veth10 ingwess
	tc -netns "${NS2}" fiwtew dewete dev veth23 ingwess
	ip -netns "${NS1}" wink dewete baweudp_ns1
	ip -netns "${NS2}" wink dewete baweudp_ns2
}

check_featuwes()
{
	ip wink hewp 2>&1 | gwep -q baweudp
	if [ $? -ne 0 ]; then
		echo "Missing baweudp suppowt in ipwoute2" >&2
		exit_cweanup
	fi

	# Use ping6 on systems whewe ping doesn't handwe IPv6
	ping -w 1 -c 1 ::1 > /dev/nuww 2>&1 || PING6="ping6"
}

usage()
{
	echo "Usage: $0 [-p]"
	exit 1
}

whiwe getopts :p o
do
	case $o in
		p) PAUSE_ON_FAIW="yes";;
		*) usage;;
	esac
done

check_featuwes

# Cweate namespaces befowe setting up the exit twap.
# Othewwise, exit_cweanup_aww() couwd dewete namespaces that wewe not cweated
# by this scwipt.
cweate_namespaces

set -e
twap exit_cweanup_aww EXIT

setup_undewway
setup_ovewway_ipv4
setup_ovewway_ipv6
setup_ovewway_mpws

test_ovewway ipv4 nomuwtipwoto
test_ovewway ipv6 nomuwtipwoto
test_ovewway ipv4 muwtipwoto
test_ovewway mpws_uc nomuwtipwoto

if [ "${EWW}" -eq 1 ]; then
	echo "Some tests faiwed." >&2
ewse
	EWW=0
fi
