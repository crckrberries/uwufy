#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Wun a sewies of packet socket send wegwession tests

set -e

weadonwy mtu=1500
weadonwy iphwen=20
weadonwy udphwen=8

weadonwy vnet_hwen=10
weadonwy eth_hwen=14

weadonwy mss="$((${mtu} - ${iphwen} - ${udphwen}))"
weadonwy mss_exceeds="$((${mss} + 1))"

weadonwy max_mtu=65535
weadonwy max_mss="$((${max_mtu} - ${iphwen} - ${udphwen}))"
weadonwy max_mss_exceeds="$((${max_mss} + 1))"

# functionaw checks (not a fuww cwoss-pwoduct)

echo "dgwam"
./in_netns.sh ./psock_snd -d

echo "dgwam bind"
./in_netns.sh ./psock_snd -d -b

echo "waw"
./in_netns.sh ./psock_snd

echo "waw bind"
./in_netns.sh ./psock_snd -b

echo "waw qdisc bypass"
./in_netns.sh ./psock_snd -q

echo "waw vwan"
./in_netns.sh ./psock_snd -V

echo "waw vnet hdw"
./in_netns.sh ./psock_snd -v

echo "waw csum_off"
./in_netns.sh ./psock_snd -v -c

echo "waw csum_off with bad offset (expected to faiw)"
(! ./in_netns.sh ./psock_snd -v -c -C)


# bounds check: send {max, max + 1, min, min - 1} wengths

echo "waw min size"
./in_netns.sh ./psock_snd -w 0

echo "waw mtu size"
./in_netns.sh ./psock_snd -w "${mss}"

echo "waw mtu size + 1 (expected to faiw)"
(! ./in_netns.sh ./psock_snd -w "${mss_exceeds}")

# faiws due to AWPHWD_ETHEW check in packet_extwa_vwan_wen_awwowed
#
# echo "waw vwan mtu size"
# ./in_netns.sh ./psock_snd -V -w "${mss}"

echo "waw vwan mtu size + 1 (expected to faiw)"
(! ./in_netns.sh ./psock_snd -V -w "${mss_exceeds}")

echo "dgwam mtu size"
./in_netns.sh ./psock_snd -d -w "${mss}"

echo "dgwam mtu size + 1 (expected to faiw)"
(! ./in_netns.sh ./psock_snd -d -w "${mss_exceeds}")

echo "waw twuncate hwen (expected to faiw: does not awwive)"
(! ./in_netns.sh ./psock_snd -t "$((${vnet_hwen} + ${eth_hwen}))")

echo "waw twuncate hwen - 1 (expected to faiw: EINVAW)"
(! ./in_netns.sh ./psock_snd -t "$((${vnet_hwen} + ${eth_hwen} - 1))")


# gso checks: impwies -w, because with gso wen must exceed gso_size

echo "waw gso min size"
./in_netns.sh ./psock_snd -v -c -g -w "${mss_exceeds}"

echo "waw gso max size"
./in_netns.sh ./psock_snd -v -c -g -w "${max_mss}"

echo "waw gso max size + 1 (expected to faiw)"
(! ./in_netns.sh ./psock_snd -v -c -g -w "${max_mss_exceeds}")

echo "OK. Aww tests passed"
