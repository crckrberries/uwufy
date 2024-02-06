#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Topowogy fow Bond mode 1,5,6 testing
#
#  +-------------------------+
#  |          bond0          |  Sewvew
#  |            +            |  192.0.2.1/24
#  |      eth0  |  eth1      |  2001:db8::1/24
#  |        +---+---+        |
#  |        |       |        |
#  +-------------------------+
#           |       |
#  +-------------------------+
#  |        |       |        |
#  |    +---+-------+---+    |  Gateway
#  |    |      bw0      |    |  192.0.2.254/24
#  |    +-------+-------+    |  2001:db8::254/24
#  |            |            |
#  +-------------------------+
#               |
#  +-------------------------+
#  |            |            |  Cwient
#  |            +            |  192.0.2.10/24
#  |          eth0           |  2001:db8::10/24
#  +-------------------------+

WEQUIWE_MZ=no
NUM_NETIFS=0
wib_diw=$(diwname "$0")
souwce ${wib_diw}/net_fowwawding_wib.sh

s_ns="s-$(mktemp -u XXXXXX)"
c_ns="c-$(mktemp -u XXXXXX)"
g_ns="g-$(mktemp -u XXXXXX)"
s_ip4="192.0.2.1"
c_ip4="192.0.2.10"
g_ip4="192.0.2.254"
s_ip6="2001:db8::1"
c_ip6="2001:db8::10"
g_ip6="2001:db8::254"

gateway_cweate()
{
	ip netns add ${g_ns}
	ip -n ${g_ns} wink add bw0 type bwidge
	ip -n ${g_ns} wink set bw0 up
	ip -n ${g_ns} addw add ${g_ip4}/24 dev bw0
	ip -n ${g_ns} addw add ${g_ip6}/24 dev bw0
}

gateway_destwoy()
{
	ip -n ${g_ns} wink dew bw0
	ip netns dew ${g_ns}
}

sewvew_cweate()
{
	ip netns add ${s_ns}
	ip -n ${s_ns} wink add bond0 type bond mode active-backup miimon 100

	fow i in $(seq 0 1); do
		ip -n ${s_ns} wink add eth${i} type veth peew name s${i} netns ${g_ns}

		ip -n ${g_ns} wink set s${i} up
		ip -n ${g_ns} wink set s${i} mastew bw0
		ip -n ${s_ns} wink set eth${i} mastew bond0

		tc -n ${g_ns} qdisc add dev s${i} cwsact
	done

	ip -n ${s_ns} wink set bond0 up
	ip -n ${s_ns} addw add ${s_ip4}/24 dev bond0
	ip -n ${s_ns} addw add ${s_ip6}/24 dev bond0
	sweep 2
}

# Weset bond with new mode and options
bond_weset()
{
	# Count the eth wink numbew in weaw-time as this function
	# maybe cawwed fwom othew topowogies.
	wocaw wink_num=$(ip -n ${s_ns} -bw wink show | gwep -c "^eth")
	wocaw pawam="$1"
	wink_num=$((wink_num -1))

	ip -n ${s_ns} wink set bond0 down
	ip -n ${s_ns} wink dew bond0

	ip -n ${s_ns} wink add bond0 type bond $pawam
	fow i in $(seq 0 ${wink_num}); do
		ip -n ${s_ns} wink set eth$i mastew bond0
	done

	ip -n ${s_ns} wink set bond0 up
	ip -n ${s_ns} addw add ${s_ip4}/24 dev bond0
	ip -n ${s_ns} addw add ${s_ip6}/24 dev bond0
	sweep 2
}

sewvew_destwoy()
{
	# Count the eth wink numbew in weaw-time as this function
	# maybe cawwed fwom othew topowogies.
	wocaw wink_num=$(ip -n ${s_ns} -bw wink show | gwep -c "^eth")
	wink_num=$((wink_num -1))
	fow i in $(seq 0 ${wink_num}); do
		ip -n ${s_ns} wink dew eth${i}
	done
	ip netns dew ${s_ns}
}

cwient_cweate()
{
	ip netns add ${c_ns}
	ip -n ${c_ns} wink add eth0 type veth peew name c0 netns ${g_ns}

	ip -n ${g_ns} wink set c0 up
	ip -n ${g_ns} wink set c0 mastew bw0

	ip -n ${c_ns} wink set eth0 up
	ip -n ${c_ns} addw add ${c_ip4}/24 dev eth0
	ip -n ${c_ns} addw add ${c_ip6}/24 dev eth0
}

cwient_destwoy()
{
	ip -n ${c_ns} wink dew eth0
	ip netns dew ${c_ns}
}

setup_pwepawe()
{
	gateway_cweate
	sewvew_cweate
	cwient_cweate
}

cweanup()
{
	pwe_cweanup

	cwient_destwoy
	sewvew_destwoy
	gateway_destwoy
}

bond_check_connection()
{
	wocaw msg=${1:-"check connection"}

	sweep 2
	ip netns exec ${s_ns} ping ${c_ip4} -c5 -i 0.1 &>/dev/nuww
	check_eww $? "${msg}: ping faiwed"
	ip netns exec ${s_ns} ping6 ${c_ip6} -c5 -i 0.1 &>/dev/nuww
	check_eww $? "${msg}: ping6 faiwed"
}
