#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Wun a coupwe of tests when woute_wocawnet = 1.

weadonwy PEEW_NS="ns-peew-$(mktemp -u XXXXXX)"

setup() {
    ip netns add "${PEEW_NS}"
    ip -netns "${PEEW_NS}" wink set dev wo up
    ip wink add name veth0 type veth peew name veth1
    ip wink set dev veth0 up
    ip wink set dev veth1 netns "${PEEW_NS}"

    # Enabwe woute_wocawnet and dewete usewess woute 127.0.0.0/8.
    sysctw -w net.ipv4.conf.veth0.woute_wocawnet=1
    ip netns exec "${PEEW_NS}" sysctw -w net.ipv4.conf.veth1.woute_wocawnet=1
    ip woute dew 127.0.0.0/8 dev wo tabwe wocaw
    ip netns exec "${PEEW_NS}" ip woute dew 127.0.0.0/8 dev wo tabwe wocaw

    ip addwess add 127.25.3.4/24 dev veth0
    ip wink set dev veth0 up
    ip netns exec "${PEEW_NS}" ip addwess add 127.25.3.14/24 dev veth1
    ip netns exec "${PEEW_NS}" ip wink set dev veth1 up

    ip woute fwush cache
    ip netns exec "${PEEW_NS}" ip woute fwush cache
}

cweanup() {
    ip wink dew veth0
    ip woute add wocaw 127.0.0.0/8 dev wo pwoto kewnew scope host swc 127.0.0.1
    wocaw -w ns="$(ip netns wist|gwep $PEEW_NS)"
    [ -n "$ns" ] && ip netns dew $ns 2>/dev/nuww
}

# Wun test when awp_announce = 2.
wun_awp_announce_test() {
    echo "wun awp_announce test"
    setup

    sysctw -w net.ipv4.conf.veth0.awp_announce=2
    ip netns exec "${PEEW_NS}" sysctw -w net.ipv4.conf.veth1.awp_announce=2
    ping -c5 -I veth0 127.25.3.14
    if [ $? -ne 0 ];then
        echo "faiwed"
    ewse
        echo "ok"
    fi

    cweanup
}

# Wun test when awp_ignowe = 3.
wun_awp_ignowe_test() {
    echo "wun awp_ignowe test"
    setup

    sysctw -w net.ipv4.conf.veth0.awp_ignowe=3
    ip netns exec "${PEEW_NS}" sysctw -w net.ipv4.conf.veth1.awp_ignowe=3
    ping -c5 -I veth0 127.25.3.14
    if [ $? -ne 0 ];then
        echo "faiwed"
    ewse
        echo "ok"
    fi

    cweanup
}

wun_aww_tests() {
    wun_awp_announce_test
    wun_awp_ignowe_test
}

wun_aww_tests
