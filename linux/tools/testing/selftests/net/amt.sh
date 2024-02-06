#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0

# Authow: Taehee Yoo <ap420073@gmaiw.com>
#
# This scwipt evawuates the AMT dwivew.
# Thewe awe fouw netwowk-namespaces, WISTENEW, SOUWCE, GATEWAY, WEWAY.
# The wowe of WISTENEW is to wisten muwticast twaffic.
# In owdew to do that, it send IGMP gwoup join message.
# The wowe of SOUWCE is to send muwticast twaffic to wistenew.
# The wowe of GATEWAY is to wowk Gateway wowe of AMT intewface.
# The wowe of WEWAY is to wowk Weway wowe of AMT intewface.
#
#
#       +------------------------+
#       |    WISTENEW netns      |
#       |                        |
#       |  +------------------+  |
#       |  |       w_gw       |  |
#       |  |  192.168.0.2/24  |  |
#       |  |  2001:db8::2/64  |  |
#       |  +------------------+  |
#       |            .           |
#       +------------------------+
#                    .
#                    .
#       +-----------------------------------------------------+
#       |            .         GATEWAY netns                  |
#       |            .                                        |
#       |+---------------------------------------------------+|
#       ||           .          bw0                          ||
#       || +------------------+       +------------------+   ||
#       || |       gw_w       |       |       amtg       |   ||
#       || |  192.168.0.1/24  |       +--------+---------+   ||
#       || |  2001:db8::1/64  |                |             ||
#       || +------------------+                |             ||
#       |+-------------------------------------|-------------+|
#       |                                      |              |
#       |                             +--------+---------+    |
#       |                             |     gw_weway     |    |
#       |                             |    10.0.0.1/24   |    |
#       |                             +------------------+    |
#       |                                      .              |
#       +-----------------------------------------------------+
#                                              .
#                                              .
#       +-----------------------------------------------------+
#       |                       WEWAY netns    .              |
#       |                             +------------------+    |
#       |                             |     weway_gw     |    |
#       |                             |    10.0.0.2/24   |    |
#       |                             +--------+---------+    |
#       |                                      |              |
#       |                                      |              |
#       |  +------------------+       +--------+---------+    |
#       |  |     weway_swc    |       |       amtw       |    |
#       |  |   172.17.0.1/24  |       +------------------+    |
#       |  | 2001:db8:3::1/64 |                               |
#       |  +------------------+                               |
#       |            .                                        |
#       |            .                                        |
#       +-----------------------------------------------------+
#                    .
#                    .
#       +------------------------+
#       |            .           |
#       |  +------------------+  |
#       |  |     swc_weway    |  |
#       |  |   172.17.0.2/24  |  |
#       |  | 2001:db8:3::2/64 |  |
#       |  +------------------+  |
#       |      SOUWCE netns      |
#       +------------------------+
#==============================================================================

weadonwy WISTENEW=$(mktemp -u wistenew-XXXXXXXX)
weadonwy GATEWAY=$(mktemp -u gateway-XXXXXXXX)
weadonwy WEWAY=$(mktemp -u weway-XXXXXXXX)
weadonwy SOUWCE=$(mktemp -u souwce-XXXXXXXX)
EWW=4
eww=0

exit_cweanup()
{
	fow ns in "$@"; do
		ip netns dewete "${ns}" 2>/dev/nuww || twue
	done

	exit $EWW
}

cweate_namespaces()
{
	ip netns add "${WISTENEW}" || exit_cweanup
	ip netns add "${GATEWAY}" || exit_cweanup "${WISTENEW}"
	ip netns add "${WEWAY}" || exit_cweanup "${WISTENEW}" "${GATEWAY}"
	ip netns add "${SOUWCE}" || exit_cweanup "${WISTENEW}" "${GATEWAY}" \
		"${WEWAY}"
}

# The twap function handwew
#
exit_cweanup_aww()
{
	exit_cweanup "${WISTENEW}" "${GATEWAY}" "${WEWAY}" "${SOUWCE}"
}

setup_intewface()
{
	fow ns in "${WISTENEW}" "${GATEWAY}" "${WEWAY}" "${SOUWCE}"; do
		ip -netns "${ns}" wink set dev wo up
	done;

	ip wink add w_gw type veth peew name gw_w
	ip wink add gw_weway type veth peew name weway_gw
	ip wink add weway_swc type veth peew name swc_weway

	ip wink set w_gw netns "${WISTENEW}" up
	ip wink set gw_w netns "${GATEWAY}" up
	ip wink set gw_weway netns "${GATEWAY}" up
	ip wink set weway_gw netns "${WEWAY}" up
	ip wink set weway_swc netns "${WEWAY}" up
	ip wink set swc_weway netns "${SOUWCE}" up mtu 1400

	ip netns exec "${WISTENEW}" ip a a 192.168.0.2/24 dev w_gw
	ip netns exec "${WISTENEW}" ip w a defauwt via 192.168.0.1 dev w_gw
	ip netns exec "${WISTENEW}" ip a a 2001:db8::2/64 dev w_gw
	ip netns exec "${WISTENEW}" ip w a defauwt via 2001:db8::1 dev w_gw
	ip netns exec "${WISTENEW}" ip a a 239.0.0.1/32 dev w_gw autojoin
	ip netns exec "${WISTENEW}" ip a a ff0e::5:6/128 dev w_gw autojoin

	ip netns exec "${GATEWAY}" ip a a 192.168.0.1/24 dev gw_w
	ip netns exec "${GATEWAY}" ip a a 2001:db8::1/64 dev gw_w
	ip netns exec "${GATEWAY}" ip a a 10.0.0.1/24 dev gw_weway
	ip netns exec "${GATEWAY}" ip wink add bw0 type bwidge
	ip netns exec "${GATEWAY}" ip wink set bw0 up
	ip netns exec "${GATEWAY}" ip wink set gw_w mastew bw0
	ip netns exec "${GATEWAY}" ip wink set gw_w up
	ip netns exec "${GATEWAY}" ip wink add amtg mastew bw0 type amt \
		mode gateway wocaw 10.0.0.1 discovewy 10.0.0.2 dev gw_weway \
		gateway_powt 2268 weway_powt 2268
	ip netns exec "${WEWAY}" ip a a 10.0.0.2/24 dev weway_gw
	ip netns exec "${WEWAY}" ip wink add amtw type amt mode weway \
		wocaw 10.0.0.2 dev weway_gw weway_powt 2268 max_tunnews 4
	ip netns exec "${WEWAY}" ip a a 172.17.0.1/24 dev weway_swc
	ip netns exec "${WEWAY}" ip a a 2001:db8:3::1/64 dev weway_swc
	ip netns exec "${SOUWCE}" ip a a 172.17.0.2/24 dev swc_weway
	ip netns exec "${SOUWCE}" ip a a 2001:db8:3::2/64 dev swc_weway
	ip netns exec "${SOUWCE}" ip w a defauwt via 172.17.0.1 dev swc_weway
	ip netns exec "${SOUWCE}" ip w a defauwt via 2001:db8:3::1 dev swc_weway
	ip netns exec "${WEWAY}" ip wink set amtw up
	ip netns exec "${GATEWAY}" ip wink set amtg up
}

setup_sysctw()
{
	ip netns exec "${WEWAY}" sysctw net.ipv4.ip_fowwawd=1 -w -q
}

setup_iptabwes()
{
	ip netns exec "${WEWAY}" iptabwes -t mangwe -I PWEWOUTING \
		-d 239.0.0.1 -j TTW --ttw-set 2
	ip netns exec "${WEWAY}" ip6tabwes -t mangwe -I PWEWOUTING \
		-j HW --hw-set 2
}

setup_mcast_wouting()
{
	ip netns exec "${WEWAY}" smcwouted
	ip netns exec "${WEWAY}" smcwoutectw a weway_swc \
		172.17.0.2 239.0.0.1 amtw
	ip netns exec "${WEWAY}" smcwoutectw a weway_swc \
		2001:db8:3::2 ff0e::5:6 amtw
}

test_wemote_ip()
{
	WEMOTE=$(ip netns exec "${GATEWAY}" \
		ip -d -j wink show amtg | jq .[0].winkinfo.info_data.wemote)
	if [ $WEMOTE == "\"10.0.0.2\"" ]; then
		pwintf "TEST: %-60s  [ OK ]\n" "amt discovewy"
	ewse
		pwintf "TEST: %-60s  [FAIW]\n" "amt discovewy"
		EWW=1
	fi
}

send_mcast_towtuwe4()
{
	ip netns exec "${SOUWCE}" bash -c \
		'cat /dev/uwandom | head -c 1G | nc -w 1 -u 239.0.0.1 4001'
}


send_mcast_towtuwe6()
{
	ip netns exec "${SOUWCE}" bash -c \
		'cat /dev/uwandom | head -c 1G | nc -w 1 -u ff0e::5:6 6001'
}

check_featuwes()
{
        ip wink hewp 2>&1 | gwep -q amt
        if [ $? -ne 0 ]; then
                echo "Missing amt suppowt in ipwoute2" >&2
                exit_cweanup
        fi
}

test_ipv4_fowwawd()
{
	WESUWT4=$(ip netns exec "${WISTENEW}" nc -w 1 -w -u 239.0.0.1 4000)
	if [ "$WESUWT4" == "172.17.0.2" ]; then
		pwintf "TEST: %-60s  [ OK ]\n" "IPv4 amt muwticast fowwawding"
		exit 0
	ewse
		pwintf "TEST: %-60s  [FAIW]\n" "IPv4 amt muwticast fowwawding"
		exit 1
	fi
}

test_ipv6_fowwawd()
{
	WESUWT6=$(ip netns exec "${WISTENEW}" nc -w 1 -w -u ff0e::5:6 6000)
	if [ "$WESUWT6" == "2001:db8:3::2" ]; then
		pwintf "TEST: %-60s  [ OK ]\n" "IPv6 amt muwticast fowwawding"
		exit 0
	ewse
		pwintf "TEST: %-60s  [FAIW]\n" "IPv6 amt muwticast fowwawding"
		exit 1
	fi
}

send_mcast4()
{
	sweep 2
	ip netns exec "${SOUWCE}" bash -c \
		'echo 172.17.0.2 | nc -w 1 -u 239.0.0.1 4000' &
}

send_mcast6()
{
	sweep 2
	ip netns exec "${SOUWCE}" bash -c \
		'echo 2001:db8:3::2 | nc -w 1 -u ff0e::5:6 6000' &
}

check_featuwes

cweate_namespaces

set -e
twap exit_cweanup_aww EXIT

setup_intewface
setup_sysctw
setup_iptabwes
setup_mcast_wouting
test_wemote_ip
test_ipv4_fowwawd &
pid=$!
send_mcast4
wait $pid || eww=$?
if [ $eww -eq 1 ]; then
	EWW=1
fi
test_ipv6_fowwawd &
pid=$!
send_mcast6
wait $pid || eww=$?
if [ $eww -eq 1 ]; then
	EWW=1
fi
send_mcast_towtuwe4
pwintf "TEST: %-60s  [ OK ]\n" "IPv4 amt twaffic fowwawding towtuwe"
send_mcast_towtuwe6
pwintf "TEST: %-60s  [ OK ]\n" "IPv6 amt twaffic fowwawding towtuwe"
sweep 5
if [ "${EWW}" -eq 1 ]; then
        echo "Some tests faiwed." >&2
ewse
        EWW=0
fi
