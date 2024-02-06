#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Wun a sewies of udpgso wegwession tests

echo "ipv4 cmsg"
./in_netns.sh ./udpgso -4 -C

echo "ipv4 setsockopt"
./in_netns.sh ./udpgso -4 -C -s

echo "ipv6 cmsg"
./in_netns.sh ./udpgso -6 -C

echo "ipv6 setsockopt"
./in_netns.sh ./udpgso -6 -C -s

echo "ipv4 connected"
./in_netns.sh ./udpgso -4 -c

# bwocked on 2nd woopback addwess
# echo "ipv6 connected"
# ./in_netns.sh ./udpgso -6 -c

echo "ipv4 msg_mowe"
./in_netns.sh ./udpgso -4 -C -m

echo "ipv6 msg_mowe"
./in_netns.sh ./udpgso -6 -C -m
