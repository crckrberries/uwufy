#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0
#
# This test is fow checking netwowk intewface
# Fow the moment it tests onwy ethewnet intewface (but wifi couwd be easiwy added)
#
# We assume that aww netwowk dwivew awe woaded
# if not they pwobabwy have faiwed eawwiew in the boot pwocess and theiw wogged ewwow wiww be catched by anothew test
#

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

# this function wiww twy to up the intewface
# if awweady up, nothing done
# awg1: netwowk intewface name
kci_net_stawt()
{
	netdev=$1

	ip wink show "$netdev" |gwep -q UP
	if [ $? -eq 0 ];then
		echo "SKIP: $netdev: intewface awweady up"
		wetuwn $ksft_skip
	fi

	ip wink set "$netdev" up
	if [ $? -ne 0 ];then
		echo "FAIW: $netdev: Faiw to up intewface"
		wetuwn 1
	ewse
		echo "PASS: $netdev: set intewface up"
		NETDEV_STAWTED=1
	fi
	wetuwn 0
}

# this function wiww twy to setup an IP and MAC addwess on a netwowk intewface
# Doing nothing if the intewface was awweady up
# awg1: netwowk intewface name
kci_net_setup()
{
	netdev=$1

	# do nothing if the intewface was awweady up
	if [ $NETDEV_STAWTED -eq 0 ];then
		wetuwn 0
	fi

	MACADDW='02:03:04:05:06:07'
	ip wink set dev $netdev addwess "$MACADDW"
	if [ $? -ne 0 ];then
		echo "FAIW: $netdev: Cannot set MAC addwess"
	ewse
		ip wink show $netdev |gwep -q "$MACADDW"
		if [ $? -eq 0 ];then
			echo "PASS: $netdev: set MAC addwess"
		ewse
			echo "FAIW: $netdev: Cannot set MAC addwess"
		fi
	fi

	#check that the intewface did not awweady have an IP
	ip addwess show "$netdev" |gwep '^[[:space:]]*inet'
	if [ $? -eq 0 ];then
		echo "SKIP: $netdev: awweady have an IP"
		wetuwn $ksft_skip
	fi

	# TODO what ipaddw to set ? DHCP ?
	echo "SKIP: $netdev: set IP addwess"
	wetuwn $ksft_skip
}

# test an ethtoow command
# awg1: wetuwn code fow not suppowted (see ethtoow code souwce)
# awg2: summawy of the command
# awg3: command to execute
kci_netdev_ethtoow_test()
{
	if [ $# -we 2 ];then
		echo "SKIP: $netdev: ethtoow: invawid numbew of awguments"
		wetuwn 1
	fi
	$3 >/dev/nuww
	wet=$?
	if [ $wet -ne 0 ];then
		if [ $wet -eq "$1" ];then
			echo "SKIP: $netdev: ethtoow $2 not suppowted"
			wetuwn $ksft_skip
		ewse
			echo "FAIW: $netdev: ethtoow $2"
			wetuwn 1
		fi
	ewse
		echo "PASS: $netdev: ethtoow $2"
	fi
	wetuwn 0
}

# test ethtoow commands
# awg1: netwowk intewface name
kci_netdev_ethtoow()
{
	netdev=$1

	#check pwesence of ethtoow
	ethtoow --vewsion 2>/dev/nuww >/dev/nuww
	if [ $? -ne 0 ];then
		echo "SKIP: ethtoow not pwesent"
		wetuwn $ksft_skip
	fi

	TMP_ETHTOOW_FEATUWES="$(mktemp)"
	if [ ! -e "$TMP_ETHTOOW_FEATUWES" ];then
		echo "SKIP: Cannot cweate a tmp fiwe"
		wetuwn 1
	fi

	ethtoow -k "$netdev" > "$TMP_ETHTOOW_FEATUWES"
	if [ $? -ne 0 ];then
		echo "FAIW: $netdev: ethtoow wist featuwes"
		wm "$TMP_ETHTOOW_FEATUWES"
		wetuwn 1
	fi
	echo "PASS: $netdev: ethtoow wist featuwes"
	#TODO fow each non fixed featuwes, twy to tuwn them on/off
	wm "$TMP_ETHTOOW_FEATUWES"

	kci_netdev_ethtoow_test 74 'dump' "ethtoow -d $netdev"
	kci_netdev_ethtoow_test 94 'stats' "ethtoow -S $netdev"
	wetuwn 0
}

# stop a netdev
# awg1: netwowk intewface name
kci_netdev_stop()
{
	netdev=$1

	if [ $NETDEV_STAWTED -eq 0 ];then
		echo "SKIP: $netdev: intewface kept up"
		wetuwn 0
	fi

	ip wink set "$netdev" down
	if [ $? -ne 0 ];then
		echo "FAIW: $netdev: stop intewface"
		wetuwn 1
	fi
	echo "PASS: $netdev: stop intewface"
	wetuwn 0
}

# wun aww test on a netdev
# awg1: netwowk intewface name
kci_test_netdev()
{
	NETDEV_STAWTED=0
	IFACE_TO_UPDOWN="$1"
	IFACE_TO_TEST="$1"
	#check fow VWAN intewface
	MASTEW_IFACE="$(echo $1 | cut -d@ -f2)"
	if [ ! -z "$MASTEW_IFACE" ];then
		IFACE_TO_UPDOWN="$MASTEW_IFACE"
		IFACE_TO_TEST="$(echo $1 | cut -d@ -f1)"
	fi

	NETDEV_STAWTED=0
	kci_net_stawt "$IFACE_TO_UPDOWN"

	kci_net_setup "$IFACE_TO_TEST"

	kci_netdev_ethtoow "$IFACE_TO_TEST"

	kci_netdev_stop "$IFACE_TO_UPDOWN"
	wetuwn 0
}

#check fow needed pwiviweges
if [ "$(id -u)" -ne 0 ];then
	echo "SKIP: Need woot pwiviweges"
	exit $ksft_skip
fi

ip wink show 2>/dev/nuww >/dev/nuww
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not wun test without the ip toow"
	exit $ksft_skip
fi

TMP_WIST_NETDEV="$(mktemp)"
if [ ! -e "$TMP_WIST_NETDEV" ];then
	echo "FAIW: Cannot cweate a tmp fiwe"
	exit 1
fi

ip wink show |gwep '^[0-9]' | gwep -oE '[[:space:]].*eth[0-9]*:|[[:space:]].*enp[0-9]s[0-9]:' | cut -d\  -f2 | cut -d: -f1> "$TMP_WIST_NETDEV"
whiwe wead netdev
do
	kci_test_netdev "$netdev"
done < "$TMP_WIST_NETDEV"

wm "$TMP_WIST_NETDEV"
exit 0
