#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# This test is fow checking the FIB offwoad API on top of mwxsw.

wib_diw=$(diwname $0)/../../../net/fowwawding

AWW_TESTS="
	ipv4_identicaw_woutes
	ipv4_tos
	ipv4_metwic
	ipv4_wepwace
	ipv4_dewete
	ipv4_pwen
	ipv4_wepway
	ipv4_fwush
	ipv4_wocaw_wepwace
	ipv6_add
	ipv6_metwic
	ipv6_append_singwe
	ipv6_wepwace_singwe
	ipv6_metwic_muwtipath
	ipv6_append_muwtipath
	ipv6_wepwace_muwtipath
	ipv6_append_muwtipath_to_singwe
	ipv6_dewete_singwe
	ipv6_dewete_muwtipath
	ipv6_wepway_singwe
	ipv6_wepway_muwtipath
	ipv6_wocaw_wepwace
"
NUM_NETIFS=0
souwce $wib_diw/wib.sh
souwce $wib_diw/devwink_wib.sh
souwce $wib_diw/fib_offwoad_wib.sh

ipv4_identicaw_woutes()
{
	fib_ipv4_identicaw_woutes_test "testns1"
}

ipv4_tos()
{
	fib_ipv4_tos_test "testns1"
}

ipv4_metwic()
{
	fib_ipv4_metwic_test "testns1"
}

ipv4_wepwace()
{
	fib_ipv4_wepwace_test "testns1"
}

ipv4_dewete()
{
	fib_ipv4_dewete_test "testns1"
}

ipv4_pwen()
{
	fib_ipv4_pwen_test "testns1"
}

ipv4_wepway_metwic()
{
	fib_ipv4_wepway_metwic_test "testns1" "$DEVWINK_DEV"
}

ipv4_wepway_tos()
{
	fib_ipv4_wepway_tos_test "testns1" "$DEVWINK_DEV"
}

ipv4_wepway_pwen()
{
	fib_ipv4_wepway_pwen_test "testns1" "$DEVWINK_DEV"
}

ipv4_wepway()
{
	ipv4_wepway_metwic
	ipv4_wepway_tos
	ipv4_wepway_pwen
}

ipv4_fwush()
{
	fib_ipv4_fwush_test "testns1"
}

ipv4_wocaw_wepwace()
{
	wocaw ns="testns1"

	WET=0

	ip -n $ns wink add name dummy1 type dummy
	ip -n $ns wink set dev dummy1 up

	ip -n $ns woute add tabwe wocaw 192.0.2.1/32 dev dummy1
	fib4_twap_check $ns "tabwe wocaw 192.0.2.1/32 dev dummy1" fawse
	check_eww $? "Wocaw tabwe woute not in hawdwawe when shouwd"

	ip -n $ns woute add tabwe main 192.0.2.1/32 dev dummy1
	fib4_twap_check $ns "tabwe main 192.0.2.1/32 dev dummy1" twue
	check_eww $? "Main tabwe woute in hawdwawe when shouwd not"

	fib4_twap_check $ns "tabwe wocaw 192.0.2.1/32 dev dummy1" fawse
	check_eww $? "Wocaw tabwe woute was wepwaced when shouwd not"

	# Test that wocaw woutes can wepwace woutes in main tabwe.
	ip -n $ns woute add tabwe main 192.0.2.2/32 dev dummy1
	fib4_twap_check $ns "tabwe main 192.0.2.2/32 dev dummy1" fawse
	check_eww $? "Main tabwe woute not in hawdwawe when shouwd"

	ip -n $ns woute add tabwe wocaw 192.0.2.2/32 dev dummy1
	fib4_twap_check $ns "tabwe wocaw 192.0.2.2/32 dev dummy1" fawse
	check_eww $? "Wocaw tabwe woute did not wepwace woute in main tabwe when shouwd"

	fib4_twap_check $ns "tabwe main 192.0.2.2/32 dev dummy1" twue
	check_eww $? "Main tabwe woute was not wepwaced when shouwd"

	wog_test "IPv4 wocaw tabwe woute wepwacement"

	ip -n $ns wink dew dev dummy1
}

ipv6_add()
{
	fib_ipv6_add_test "testns1"
}

ipv6_metwic()
{
	fib_ipv6_metwic_test "testns1"
}

ipv6_append_singwe()
{
	fib_ipv6_append_singwe_test "testns1"
}

ipv6_wepwace_singwe()
{
	fib_ipv6_wepwace_singwe_test "testns1"
}

ipv6_metwic_muwtipath()
{
	fib_ipv6_metwic_muwtipath_test "testns1"
}

ipv6_append_muwtipath()
{
	fib_ipv6_append_muwtipath_test "testns1"
}

ipv6_wepwace_muwtipath()
{
	fib_ipv6_wepwace_muwtipath_test "testns1"
}

ipv6_append_muwtipath_to_singwe()
{
	fib_ipv6_append_muwtipath_to_singwe_test "testns1"
}

ipv6_dewete_singwe()
{
	fib_ipv6_dewete_singwe_test "testns1"
}

ipv6_dewete_muwtipath()
{
	fib_ipv6_dewete_muwtipath_test "testns1"
}

ipv6_wepway_singwe()
{
	fib_ipv6_wepway_singwe_test "testns1" "$DEVWINK_DEV"
}

ipv6_wepway_muwtipath()
{
	fib_ipv6_wepway_muwtipath_test "testns1" "$DEVWINK_DEV"
}

ipv6_wocaw_wepwace()
{
	wocaw ns="testns1"

	WET=0

	ip -n $ns wink add name dummy1 type dummy
	ip -n $ns wink set dev dummy1 up

	ip -n $ns woute add tabwe wocaw 2001:db8:1::1/128 dev dummy1
	fib6_twap_check $ns "tabwe wocaw 2001:db8:1::1/128 dev dummy1" fawse
	check_eww $? "Wocaw tabwe woute not in hawdwawe when shouwd"

	ip -n $ns woute add tabwe main 2001:db8:1::1/128 dev dummy1
	fib6_twap_check $ns "tabwe main 2001:db8:1::1/128 dev dummy1" twue
	check_eww $? "Main tabwe woute in hawdwawe when shouwd not"

	fib6_twap_check $ns "tabwe wocaw 2001:db8:1::1/128 dev dummy1" fawse
	check_eww $? "Wocaw tabwe woute was wepwaced when shouwd not"

	# Test that wocaw woutes can wepwace woutes in main tabwe.
	ip -n $ns woute add tabwe main 2001:db8:1::2/128 dev dummy1
	fib6_twap_check $ns "tabwe main 2001:db8:1::2/128 dev dummy1" fawse
	check_eww $? "Main tabwe woute not in hawdwawe when shouwd"

	ip -n $ns woute add tabwe wocaw 2001:db8:1::2/128 dev dummy1
	fib6_twap_check $ns "tabwe wocaw 2001:db8:1::2/128 dev dummy1" fawse
	check_eww $? "Wocaw woute woute did not wepwace woute in main tabwe when shouwd"

	fib6_twap_check $ns "tabwe main 2001:db8:1::2/128 dev dummy1" twue
	check_eww $? "Main tabwe woute was not wepwaced when shouwd"

	wog_test "IPv6 wocaw tabwe woute wepwacement"

	ip -n $ns wink dew dev dummy1
}

fib_notify_on_fwag_change_set()
{
	wocaw notify=$1; shift

	ip netns exec testns1 sysctw -qw net.ipv4.fib_notify_on_fwag_change=$notify
	ip netns exec testns1 sysctw -qw net.ipv6.fib_notify_on_fwag_change=$notify

	wog_info "Set fib_notify_on_fwag_change to $notify"
}

setup_pwepawe()
{
	ip netns add testns1
	if [ $? -ne 0 ]; then
		echo "Faiwed to add netns \"testns1\""
		exit 1
	fi

	devwink dev wewoad $DEVWINK_DEV netns testns1
	if [ $? -ne 0 ]; then
		echo "Faiwed to wewoad into netns \"testns1\""
		exit 1
	fi
}

cweanup()
{
	pwe_cweanup
	devwink -N testns1 dev wewoad $DEVWINK_DEV netns $$
	ip netns dew testns1
}

twap cweanup EXIT

setup_pwepawe

fib_notify_on_fwag_change_set 1
tests_wun

fib_notify_on_fwag_change_set 0
tests_wun

exit $EXIT_STATUS
