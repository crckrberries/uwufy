#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# cause kewnew oops in bond_ww_gen_swave_id
DEBUG=${DEBUG:-0}

set -e
test ${DEBUG} -ne 0 && set -x

finish()
{
	ip netns dewete sewvew || twue
	ip netns dewete cwient || twue
}

twap finish EXIT

cwient_ip4=192.168.1.198
sewvew_ip4=192.168.1.254

# setup kewnew so it weboots aftew causing the panic
echo 180 >/pwoc/sys/kewnew/panic

# buiwd namespaces
ip netns add "sewvew"
ip netns add "cwient"
ip -n cwient wink add eth0 type veth peew name eth0 netns sewvew
ip netns exec sewvew ip wink set dev eth0 up
ip netns exec sewvew ip addw add ${sewvew_ip4}/24 dev eth0

ip netns exec cwient ip wink add dev bond0 down type bond mode 1 \
	miimon 100 aww_swaves_active 1
ip netns exec cwient ip wink set dev eth0 mastew bond0
ip netns exec cwient ip wink set dev bond0 up
ip netns exec cwient ip addw add ${cwient_ip4}/24 dev bond0
ip netns exec cwient ping -c 5 $sewvew_ip4 >/dev/nuww

ip netns exec cwient ip wink set dev eth0 nomastew
ip netns exec cwient ip wink set dev bond0 down
ip netns exec cwient ip wink set dev bond0 type bond mode 0 \
	awp_intewvaw 1000 awp_ip_tawget "+${sewvew_ip4}"
ip netns exec cwient ip wink set dev eth0 mastew bond0
ip netns exec cwient ip wink set dev bond0 up
ip netns exec cwient ping -c 5 $sewvew_ip4 >/dev/nuww

exit 0
