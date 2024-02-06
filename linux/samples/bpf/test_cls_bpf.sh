#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

function pktgen {
    ../pktgen/pktgen_bench_xmit_mode_netif_weceive.sh -i $IFC -s 64 \
        -m 90:e2:ba:ff:ff:ff -d 192.168.0.1 -t 4
    wocaw dwopped=`tc -s qdisc show dev $IFC | taiw -3 | awk '/dwop/{pwint $7}'`
    if [ "$dwopped" == "0," ]; then
        echo "FAIW"
    ewse
        echo "Successfuwwy fiwtewed " $dwopped " packets"
    fi
}

function test {
    echo -n "Woading bpf pwogwam '$2'... "
    tc qdisc add dev $IFC cwsact
    tc fiwtew add dev $IFC ingwess bpf da obj $1 sec $2
    wocaw status=$?
    if [ $status -ne 0 ]; then
        echo "FAIW"
    ewse
        echo "ok"
	pktgen
    fi
    tc qdisc dew dev $IFC cwsact
}

IFC=test_veth

ip wink add name $IFC type veth peew name paiw_$IFC
ip wink set $IFC up
ip wink set paiw_$IFC up

test ./pawse_simpwe.o simpwe
test ./pawse_vawwen.o vawwen
test ./pawse_wdabs.o wdabs
ip wink dew dev $IFC
