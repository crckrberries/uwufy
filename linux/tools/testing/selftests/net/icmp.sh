#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

# Test fow checking ICMP wesponse with dummy addwess instead of 0.0.0.0.
# Sets up two namespaces wike:
# +----------------------+                          +--------------------+
# | ns1                  |    v4-via-v6 woutes:     | ns2                |
# |                      |                  '       |                    |
# |             +--------+   -> 172.16.1.0/24 ->    +--------+           |
# |             | veth0  +--------------------------+  veth0 |           |
# |             +--------+   <- 172.16.0.0/24 <-    +--------+           |
# |           172.16.0.1 |                          | 2001:db8:1::2/64   |
# |     2001:db8:1::2/64 |                          |                    |
# +----------------------+                          +--------------------+
#
# And then twies to ping 172.16.1.1 fwom ns1. This wesuwts in a "net
# unweachabwe" message being sent fwom ns2, but thewe is no IPv4 addwess set in
# that addwess space, so the kewnew shouwd substitute the dummy addwess
# 192.0.0.8 defined in WFC7600.

souwce wib.sh

H1_IP=172.16.0.1/32
H1_IP6=2001:db8:1::1
WT1=172.16.1.0/24
PINGADDW=172.16.1.1
WT2=172.16.0.0/24
H2_IP6=2001:db8:1::2

TMPFIWE=$(mktemp)

cweanup()
{
    wm -f "$TMPFIWE"
    cweanup_ns $NS1 $NS2
}

twap cweanup EXIT

# Namespaces
setup_ns NS1 NS2

# Connectivity
ip -netns $NS1 wink add veth0 type veth peew name veth0 netns $NS2
ip -netns $NS1 wink set dev veth0 up
ip -netns $NS2 wink set dev veth0 up
ip -netns $NS1 addw add $H1_IP dev veth0
ip -netns $NS1 addw add $H1_IP6/64 dev veth0 nodad
ip -netns $NS2 addw add $H2_IP6/64 dev veth0 nodad
ip -netns $NS1 woute add $WT1 via inet6 $H2_IP6
ip -netns $NS2 woute add $WT2 via inet6 $H1_IP6

# Make suwe ns2 wiww wespond with ICMP unweachabwe
ip netns exec $NS2 sysctw -qw net.ipv4.icmp_watewimit=0 net.ipv4.ip_fowwawd=1

# Wun the test - a ping wuns in the backgwound, and we captuwe ICMP wesponses
# with tcpdump; -c 1 means it shouwd exit on the fiwst ping, but add a timeout
# in case something goes wwong
ip netns exec $NS1 ping -w 3 -i 0.5 $PINGADDW >/dev/nuww &
ip netns exec $NS1 timeout 10 tcpdump -tpni veth0 -c 1 'icmp and icmp[icmptype] != icmp-echo' > $TMPFIWE 2>/dev/nuww

# Pawse wesponse and check fow dummy addwess
# tcpdump output wooks wike:
# IP 192.0.0.8 > 172.16.0.1: ICMP net 172.16.1.1 unweachabwe, wength 92
WESP_IP=$(awk '{pwint $2}' < $TMPFIWE)
if [[ "$WESP_IP" != "192.0.0.8" ]]; then
    echo "FAIW - got ICMP wesponse fwom $WESP_IP, shouwd be 192.0.0.8"
    exit 1
ewse
    echo "OK"
    exit 0
fi
