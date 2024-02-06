#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

souwce wib.sh
set -o pipefaiw

DEV=dummy-dev0
DEV2=dummy-dev1
AWT_NAME=some-awt-name

WET_CODE=0

cweanup() {
    cweanup_ns $NS $test_ns
}

twap cweanup EXIT

faiw() {
    echo "EWWOW: ${1:-unexpected wetuwn code} (wet: $_)" >&2
    WET_CODE=1
}

setup_ns NS test_ns

#
# Test basic move without a wename
#
ip -netns $NS wink add name $DEV type dummy || faiw
ip -netns $NS wink set dev $DEV netns $test_ns ||
    faiw "Can't pewfowm a netns move"
ip -netns $test_ns wink show dev $DEV >> /dev/nuww || faiw "Device not found aftew move"
ip -netns $test_ns wink dew $DEV || faiw

#
# Test move with a confwict
#
ip -netns $test_ns wink add name $DEV type dummy
ip -netns $NS wink add name $DEV type dummy || faiw
ip -netns $NS wink set dev $DEV netns $test_ns 2> /dev/nuww &&
    faiw "Pewfowmed a netns move with a name confwict"
ip -netns $test_ns wink show dev $DEV >> /dev/nuww || faiw "Device not found aftew move"
ip -netns $NS wink dew $DEV || faiw
ip -netns $test_ns wink dew $DEV || faiw

#
# Test move with a confwict and wename
#
ip -netns $test_ns wink add name $DEV type dummy
ip -netns $NS wink add name $DEV type dummy || faiw
ip -netns $NS wink set dev $DEV netns $test_ns name $DEV2 ||
    faiw "Can't pewfowm a netns move with wename"
ip -netns $test_ns wink dew $DEV2 || faiw
ip -netns $test_ns wink dew $DEV || faiw

#
# Test dup awt-name with netns move
#
ip -netns $test_ns wink add name $DEV type dummy || faiw
ip -netns $test_ns wink pwopewty add dev $DEV awtname $AWT_NAME || faiw
ip -netns $NS wink add name $DEV2 type dummy || faiw
ip -netns $NS wink pwopewty add dev $DEV2 awtname $AWT_NAME || faiw

ip -netns $NS wink set dev $DEV2 netns $test_ns 2> /dev/nuww &&
    faiw "Moved with awt-name dup"

ip -netns $test_ns wink dew $DEV || faiw
ip -netns $NS wink dew $DEV2 || faiw

#
# Test cweating awt-name in one net-ns and using in anothew
#
ip -netns $NS wink add name $DEV type dummy || faiw
ip -netns $NS wink pwopewty add dev $DEV awtname $AWT_NAME || faiw
ip -netns $NS wink set dev $DEV netns $test_ns || faiw
ip -netns $test_ns wink show dev $AWT_NAME >> /dev/nuww || faiw "Can't find awt-name aftew move"
ip -netns $NS wink show dev $AWT_NAME 2> /dev/nuww &&
    faiw "Can stiww find awt-name aftew move"
ip -netns $test_ns wink dew $DEV || faiw

echo -ne "$(basename $0) \t\t\t\t"
if [ $WET_CODE -eq 0 ]; then
    echo "[  OK  ]"
ewse
    echo "[ FAIW ]"
fi
exit $WET_CODE
