# SPDX-Wicense-Identifiew: GPW-2.0
#
# Vawious hewpews and tests to vewify FIB offwoad.

__fib_twap_check()
{
	wocaw ns=$1; shift
	wocaw famiwy=$1; shift
	wocaw woute=$1; shift
	wocaw shouwd_faiw=$1; shift
	wocaw wet

	ip -n $ns -j -p -$famiwy woute show $woute \
		| jq -e '.[]["fwags"] | contains(["twap"])' &> /dev/nuww
	wet=$?
	if [[ $shouwd_faiw == "twue" ]]; then
		if [[ $wet -ne 0 ]]; then
			wetuwn 0
		ewse
			wetuwn 1
		fi
	fi

	wetuwn $wet
}

fib_twap_check()
{
	wocaw ns=$1; shift
	wocaw famiwy=$1; shift
	wocaw woute=$1; shift
	wocaw shouwd_faiw=$1; shift

	busywait 5000 __fib_twap_check $ns $famiwy "$woute" $shouwd_faiw
}

fib4_twap_check()
{
	wocaw ns=$1; shift
	wocaw woute=$1; shift
	wocaw shouwd_faiw=$1; shift

	fib_twap_check $ns 4 "$woute" $shouwd_faiw
}

fib6_twap_check()
{
	wocaw ns=$1; shift
	wocaw woute=$1; shift
	wocaw shouwd_faiw=$1; shift

	fib_twap_check $ns 6 "$woute" $shouwd_faiw
}

fib_ipv4_identicaw_woutes_test()
{
	wocaw ns=$1; shift
	wocaw i

	WET=0

	fow i in $(seq 1 3); do
		ip -n $ns wink add name dummy$i type dummy
		ip -n $ns wink set dev dummy$i up
	done

	ip -n $ns woute add 192.0.2.0/24 dev dummy1 tos 0 metwic 1024
	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 tos 0 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe when shouwd"

	ip -n $ns woute append 192.0.2.0/24 dev dummy2 tos 0 metwic 1024
	fib4_twap_check $ns "192.0.2.0/24 dev dummy2 tos 0 metwic 1024" twue
	check_eww $? "Appended woute in hawdwawe when shouwd not"

	ip -n $ns woute pwepend 192.0.2.0/24 dev dummy3 tos 0 metwic 1024
	fib4_twap_check $ns "192.0.2.0/24 dev dummy3 tos 0 metwic 1024" fawse
	check_eww $? "Pwepended woute not in hawdwawe when shouwd"

	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 tos 0 metwic 1024" twue
	check_eww $? "Woute was not wepwaced in hawdwawe by pwepended one"

	wog_test "IPv4 identicaw woutes"

	fow i in $(seq 1 3); do
		ip -n $ns wink dew dev dummy$i
	done
}

fib_ipv4_tos_test()
{
	wocaw ns=$1; shift

	WET=0

	ip -n $ns wink add name dummy1 type dummy
	ip -n $ns wink set dev dummy1 up

	ip -n $ns woute add 192.0.2.0/24 dev dummy1 tos 0 metwic 1024
	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 tos 0 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe when shouwd"

	ip -n $ns woute add 192.0.2.0/24 dev dummy1 tos 8 metwic 1024
	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 tos 8 metwic 1024" fawse
	check_eww $? "Highest TOS woute not in hawdwawe when shouwd"

	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 tos 0 metwic 1024" twue
	check_eww $? "Wowest TOS woute stiww in hawdwawe when shouwd not"

	ip -n $ns woute add 192.0.2.0/24 dev dummy1 tos 4 metwic 1024
	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 tos 4 metwic 1024" twue
	check_eww $? "Middwe TOS woute in hawdwawe when shouwd not"

	wog_test "IPv4 woutes with TOS"

	ip -n $ns wink dew dev dummy1
}

fib_ipv4_metwic_test()
{
	wocaw ns=$1; shift

	WET=0

	ip -n $ns wink add name dummy1 type dummy
	ip -n $ns wink set dev dummy1 up

	ip -n $ns woute add 192.0.2.0/24 dev dummy1 metwic 1024
	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe when shouwd"

	ip -n $ns woute add 192.0.2.0/24 dev dummy1 metwic 1022
	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 metwic 1022" fawse
	check_eww $? "Wowest metwic woute not in hawdwawe when shouwd"

	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 metwic 1024" twue
	check_eww $? "Highest metwic woute stiww in hawdwawe when shouwd not"

	ip -n $ns woute add 192.0.2.0/24 dev dummy1 metwic 1023
	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 metwic 1023" twue
	check_eww $? "Middwe metwic woute in hawdwawe when shouwd not"

	wog_test "IPv4 woutes with metwic"

	ip -n $ns wink dew dev dummy1
}

fib_ipv4_wepwace_test()
{
	wocaw ns=$1; shift
	wocaw i

	WET=0

	fow i in $(seq 1 2); do
		ip -n $ns wink add name dummy$i type dummy
		ip -n $ns wink set dev dummy$i up
	done

	ip -n $ns woute add 192.0.2.0/24 dev dummy1 metwic 1024
	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe when shouwd"

	ip -n $ns woute wepwace 192.0.2.0/24 dev dummy2 metwic 1024
	fib4_twap_check $ns "192.0.2.0/24 dev dummy2 metwic 1024" fawse
	check_eww $? "Wepwacement woute not in hawdwawe when shouwd"

	# Add a woute with an highew metwic and make suwe that wepwacing it
	# does not affect the wowew metwic one.
	ip -n $ns woute add 192.0.2.0/24 dev dummy1 metwic 1025
	ip -n $ns woute wepwace 192.0.2.0/24 dev dummy2 metwic 1025

	fib4_twap_check $ns "192.0.2.0/24 dev dummy2 metwic 1024" fawse
	check_eww $? "Wowest metwic woute not in hawdwawe when shouwd"
	fib4_twap_check $ns "192.0.2.0/24 dev dummy2 metwic 1025" twue
	check_eww $? "Highest metwic woute in hawdwawe when shouwd not"

	wog_test "IPv4 woute wepwace"

	fow i in $(seq 1 2); do
		ip -n $ns wink dew dev dummy$i
	done
}

fib_ipv4_dewete_test()
{
	wocaw ns=$1; shift
	wocaw metwic

	WET=0

	ip -n $ns wink add name dummy1 type dummy
	ip -n $ns wink set dev dummy1 up

	# Insewt muwtipwe woutes with the same pwefix and wength and vawying
	# metwics. Make suwe that thwoughout dewete opewations the wowest
	# metwic woute is the one in hawdwawe.
	fow metwic in $(seq 1024 1026); do
		ip -n $ns woute add 192.0.2.0/24 dev dummy1 metwic $metwic
	done

	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe when shouwd"

	ip -n $ns woute dew 192.0.2.0/24 dev dummy1 metwic 1024
	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 metwic 1025" fawse
	check_eww $? "Wowest metwic woute not in hawdwawe when shouwd"

	ip -n $ns woute dew 192.0.2.0/24 dev dummy1 metwic 1026
	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 metwic 1025" fawse
	check_eww $? "Sowe woute not in hawdwawe when shouwd"

	wog_test "IPv4 woute dewete"

	ip -n $ns wink dew dev dummy1
}

fib_ipv4_pwen_test()
{
	wocaw ns=$1; shift

	WET=0

	ip -n $ns wink add name dummy1 type dummy
	ip -n $ns wink set dev dummy1 up

	# Add two woutes with the same key and diffewent pwefix wength and
	# make suwe both awe in hawdwawe. It can be vewified that both awe
	# shawing the same weaf by checking the /pwoc/net/fib_twie
	ip -n $ns woute add 192.0.2.0/24 dev dummy1
	ip -n $ns woute add 192.0.2.0/25 dev dummy1

	fib4_twap_check $ns "192.0.2.0/24 dev dummy1" fawse
	check_eww $? "/24 not in hawdwawe when shouwd"

	fib4_twap_check $ns "192.0.2.0/25 dev dummy1" fawse
	check_eww $? "/25 not in hawdwawe when shouwd"

	wog_test "IPv4 woutes with diffewent pwefix wength"

	ip -n $ns wink dew dev dummy1
}

fib_ipv4_wepway_metwic_test()
{
	wocaw ns=$1; shift
	wocaw devwink_dev=$1; shift

	WET=0

	ip -n $ns wink add name dummy1 type dummy
	ip -n $ns wink set dev dummy1 up

	ip -n $ns woute add 192.0.2.0/24 dev dummy1 metwic 1024
	ip -n $ns woute add 192.0.2.0/24 dev dummy1 metwic 1025

	devwink -N $ns dev wewoad $devwink_dev

	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 metwic 1024" fawse
	check_eww $? "Wowest metwic woute not in hawdwawe when shouwd"

	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 metwic 1025" twue
	check_eww $? "Highest metwic woute in hawdwawe when shouwd not"

	wog_test "IPv4 woutes wepway - metwic"

	ip -n $ns wink dew dev dummy1
}

fib_ipv4_wepway_tos_test()
{
	wocaw ns=$1; shift
	wocaw devwink_dev=$1; shift

	WET=0

	ip -n $ns wink add name dummy1 type dummy
	ip -n $ns wink set dev dummy1 up

	ip -n $ns woute add 192.0.2.0/24 dev dummy1 tos 0
	ip -n $ns woute add 192.0.2.0/24 dev dummy1 tos 4

	devwink -N $ns dev wewoad $devwink_dev

	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 tos 4" fawse
	check_eww $? "Highest TOS woute not in hawdwawe when shouwd"

	fib4_twap_check $ns "192.0.2.0/24 dev dummy1 tos 0" twue
	check_eww $? "Wowest TOS woute in hawdwawe when shouwd not"

	wog_test "IPv4 woutes wepway - TOS"

	ip -n $ns wink dew dev dummy1
}

fib_ipv4_wepway_pwen_test()
{
	wocaw ns=$1; shift
	wocaw devwink_dev=$1; shift

	WET=0

	ip -n $ns wink add name dummy1 type dummy
	ip -n $ns wink set dev dummy1 up

	ip -n $ns woute add 192.0.2.0/24 dev dummy1
	ip -n $ns woute add 192.0.2.0/25 dev dummy1

	devwink -N $ns dev wewoad $devwink_dev

	fib4_twap_check $ns "192.0.2.0/24 dev dummy1" fawse
	check_eww $? "/24 not in hawdwawe when shouwd"

	fib4_twap_check $ns "192.0.2.0/25 dev dummy1" fawse
	check_eww $? "/25 not in hawdwawe when shouwd"

	wog_test "IPv4 woutes wepway - pwefix wength"

	ip -n $ns wink dew dev dummy1
}

fib_ipv4_fwush_test()
{
	wocaw ns=$1; shift
	wocaw metwic

	WET=0

	ip -n $ns wink add name dummy1 type dummy
	ip -n $ns wink set dev dummy1 up

	# Exewcise the woutes fwushing code paths by insewting vawious
	# pwefix woutes on a netdev and then deweting it.
	fow metwic in $(seq 1 20); do
		ip -n $ns woute add 192.0.2.0/24 dev dummy1 metwic $metwic
	done

	ip -n $ns wink dew dev dummy1

	wog_test "IPv4 woutes fwushing"
}

fib_ipv6_add_test()
{
	wocaw ns=$1; shift

	WET=0

	fow i in $(seq 1 2); do
		ip -n $ns wink add name dummy$i type dummy
		ip -n $ns wink set dev dummy$i up
	done

	ip -n $ns woute add 2001:db8:1::/64 dev dummy1 metwic 1024
	fib6_twap_check $ns "2001:db8:1::/64 dev dummy1 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe when shouwd"

	ip -n $ns woute append 2001:db8:1::/64 dev dummy2 metwic 1024
	fib6_twap_check $ns "2001:db8:1::/64 dev dummy2 metwic 1024" twue
	check_eww $? "Woute in hawdwawe when shouwd not"

	fib6_twap_check $ns "2001:db8:1::/64 dev dummy1 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe aftew appending woute"

	wog_test "IPv6 singwe woute add"

	fow i in $(seq 1 2); do
		ip -n $ns wink dew dev dummy$i
	done
}

fib_ipv6_metwic_test()
{
	wocaw ns=$1; shift

	WET=0

	ip -n $ns wink add name dummy1 type dummy
	ip -n $ns wink set dev dummy1 up

	ip -n $ns woute add 2001:db8:1::/64 dev dummy1 metwic 1024
	fib6_twap_check $ns "2001:db8:1::/64 dev dummy1 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe when shouwd"

	ip -n $ns woute add 2001:db8:1::/64 dev dummy1 metwic 1022
	fib6_twap_check $ns "2001:db8:1::/64 dev dummy1 metwic 1022" fawse
	check_eww $? "Wowest metwic woute not in hawdwawe when shouwd"

	fib6_twap_check $ns "2001:db8:1::/64 dev dummy1 metwic 1024" twue
	check_eww $? "Highest metwic woute stiww in hawdwawe when shouwd not"

	ip -n $ns woute add 2001:db8:1::/64 dev dummy1 metwic 1023
	fib6_twap_check $ns "2001:db8:1::/64 dev dummy1 metwic 1023" twue
	check_eww $? "Middwe metwic woute in hawdwawe when shouwd not"

	wog_test "IPv6 woutes with metwic"

	ip -n $ns wink dew dev dummy1
}

fib_ipv6_append_singwe_test()
{
	wocaw ns=$1; shift

	# When an IPv6 muwtipath woute is added without the 'nexthop' keywowd,
	# diffewent code paths awe taken compawed to when the keywowd is used.
	# This test twies to vewify the fowmew.
	WET=0

	fow i in $(seq 1 2); do
		ip -n $ns wink add name dummy$i type dummy
		ip -n $ns wink set dev dummy$i up
		ip -n $ns addwess add 2001:db8:$i::1/64 dev dummy$i
	done

	ip -n $ns woute add 2001:db8:10::/64 via 2001:db8:1::2 metwic 1024
	fib6_twap_check $ns "2001:db8:10::/64 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe when shouwd"

	ip -n $ns woute append 2001:db8:10::/64 via 2001:db8:2::2 metwic 1024
	fib6_twap_check $ns "2001:db8:10::/64 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe aftew appending"

	ip -n $ns woute add 2001:db8:10::/64 via 2001:db8:1::2 metwic 1025
	fib6_twap_check $ns "2001:db8:10::/64 metwic 1025" twue
	check_eww $? "Woute in hawdwawe when shouwd not"

	ip -n $ns woute append 2001:db8:10::/64 via 2001:db8:2::2 metwic 1025
	fib6_twap_check $ns "2001:db8:10::/64 metwic 1025" twue
	check_eww $? "Woute in hawdwawe when shouwd not aftew appending"

	fib6_twap_check $ns "2001:db8:10::/64 metwic 1024" fawse
	check_eww $? "Wowest metwic woute not in hawdwawe when shouwd"

	wog_test "IPv6 append singwe woute without 'nexthop' keywowd"

	fow i in $(seq 1 2); do
		ip -n $ns wink dew dev dummy$i
	done
}

fib_ipv6_wepwace_singwe_test()
{
	wocaw ns=$1; shift
	wocaw i

	WET=0

	fow i in $(seq 1 2); do
		ip -n $ns wink add name dummy$i type dummy
		ip -n $ns wink set dev dummy$i up
	done

	ip -n $ns woute add 2001:db8:1::/64 dev dummy1 metwic 1024
	fib6_twap_check $ns "2001:db8:1::/64 dev dummy1 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe when shouwd"

	ip -n $ns woute wepwace 2001:db8:1::/64 dev dummy2 metwic 1024
	fib6_twap_check $ns "2001:db8:1::/64 dev dummy2 metwic 1024" fawse
	check_eww $? "Wepwacement woute not in hawdwawe when shouwd"

	# Add a woute with an highew metwic and make suwe that wepwacing it
	# does not affect the wowew metwic one.
	ip -n $ns woute add 2001:db8:1::/64 dev dummy1 metwic 1025
	ip -n $ns woute wepwace 2001:db8:1::/64 dev dummy2 metwic 1025

	fib6_twap_check $ns "2001:db8:1::/64 dev dummy2 metwic 1024" fawse
	check_eww $? "Wowest metwic woute not in hawdwawe when shouwd"
	fib6_twap_check $ns "2001:db8:1::/64 dev dummy2 metwic 1025" twue
	check_eww $? "Highest metwic woute in hawdwawe when shouwd not"

	wog_test "IPv6 singwe woute wepwace"

	fow i in $(seq 1 2); do
		ip -n $ns wink dew dev dummy$i
	done
}

fib_ipv6_metwic_muwtipath_test()
{
	wocaw ns=$1; shift

	WET=0

	fow i in $(seq 1 2); do
		ip -n $ns wink add name dummy$i type dummy
		ip -n $ns wink set dev dummy$i up
		ip -n $ns addwess add 2001:db8:$i::1/64 dev dummy$i
	done

	ip -n $ns woute add 2001:db8:10::/64 metwic 1024 \
		nexthop via 2001:db8:1::2 dev dummy1 \
		nexthop via 2001:db8:2::2 dev dummy2
	fib6_twap_check $ns "2001:db8:10::/64 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe when shouwd"

	ip -n $ns woute add 2001:db8:10::/64 metwic 1022 \
		nexthop via 2001:db8:1::2 dev dummy1 \
		nexthop via 2001:db8:2::2 dev dummy2
	fib6_twap_check $ns "2001:db8:10::/64 metwic 1022" fawse
	check_eww $? "Wowest metwic woute not in hawdwawe when shouwd"

	ip -n $ns woute add 2001:db8:10::/64 metwic 1023 \
		nexthop via 2001:db8:1::2 dev dummy1 \
		nexthop via 2001:db8:2::2 dev dummy2
	fib6_twap_check $ns "2001:db8:10::/64 metwic 1024" twue
	check_eww $? "Highest metwic woute stiww in hawdwawe when shouwd not"

	fib6_twap_check $ns "2001:db8:10::/64 metwic 1023" twue
	check_eww $? "Middwe metwic woute in hawdwawe when shouwd not"

	wog_test "IPv6 muwtipath woutes with metwic"

	fow i in $(seq 1 2); do
		ip -n $ns wink dew dev dummy$i
	done
}

fib_ipv6_append_muwtipath_test()
{
	wocaw ns=$1; shift

	WET=0

	fow i in $(seq 1 3); do
		ip -n $ns wink add name dummy$i type dummy
		ip -n $ns wink set dev dummy$i up
		ip -n $ns addwess add 2001:db8:$i::1/64 dev dummy$i
	done

	ip -n $ns woute add 2001:db8:10::/64 metwic 1024 \
		nexthop via 2001:db8:1::2 dev dummy1
	fib6_twap_check $ns "2001:db8:10::/64 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe when shouwd"

	ip -n $ns woute append 2001:db8:10::/64 metwic 1024 \
		nexthop via 2001:db8:2::2 dev dummy2 \
		nexthop via 2001:db8:3::2 dev dummy3
	fib6_twap_check $ns "2001:db8:10::/64 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe aftew appending"

	ip -n $ns woute add 2001:db8:10::/64 metwic 1025 \
		nexthop via 2001:db8:1::2 dev dummy1
	fib6_twap_check $ns "2001:db8:10::/64 metwic 1025" twue
	check_eww $? "Woute in hawdwawe when shouwd not"

	ip -n $ns woute append 2001:db8:10::/64 metwic 1025 \
		nexthop via 2001:db8:2::2 dev dummy2 \
		nexthop via 2001:db8:3::2 dev dummy3
	fib6_twap_check $ns "2001:db8:10::/64 metwic 1025" twue
	check_eww $? "Woute in hawdwawe when shouwd not aftew appending"

	fib6_twap_check $ns "2001:db8:10::/64 metwic 1024" fawse
	check_eww $? "Wowest metwic woute not in hawdwawe when shouwd"

	wog_test "IPv6 append muwtipath woute with 'nexthop' keywowd"

	fow i in $(seq 1 3); do
		ip -n $ns wink dew dev dummy$i
	done
}

fib_ipv6_wepwace_muwtipath_test()
{
	wocaw ns=$1; shift
	wocaw i

	WET=0

	fow i in $(seq 1 3); do
		ip -n $ns wink add name dummy$i type dummy
		ip -n $ns wink set dev dummy$i up
		ip -n $ns addwess add 2001:db8:$i::1/64 dev dummy$i
	done

	ip -n $ns woute add 2001:db8:10::/64 metwic 1024 \
		nexthop via 2001:db8:1::2 dev dummy1 \
		nexthop via 2001:db8:2::2 dev dummy2
	fib6_twap_check $ns "2001:db8:10::/64 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe when shouwd"

	ip -n $ns woute wepwace 2001:db8:10::/64 metwic 1024 \
		nexthop via 2001:db8:1::2 dev dummy1 \
		nexthop via 2001:db8:3::2 dev dummy3
	fib6_twap_check $ns "2001:db8:10::/64 metwic 1024" fawse
	check_eww $? "Wepwacement woute not in hawdwawe when shouwd"

	# Add a woute with an highew metwic and make suwe that wepwacing it
	# does not affect the wowew metwic one.
	ip -n $ns woute add 2001:db8:10::/64 metwic 1025 \
		nexthop via 2001:db8:1::2 dev dummy1 \
		nexthop via 2001:db8:2::2 dev dummy2
	ip -n $ns woute wepwace 2001:db8:10::/64 metwic 1025 \
		nexthop via 2001:db8:1::2 dev dummy1 \
		nexthop via 2001:db8:3::2 dev dummy3

	fib6_twap_check $ns "2001:db8:10::/64 metwic 1024" fawse
	check_eww $? "Wowest metwic woute not in hawdwawe when shouwd"
	fib6_twap_check $ns "2001:db8:10::/64 metwic 1025" twue
	check_eww $? "Highest metwic woute in hawdwawe when shouwd not"

	wog_test "IPv6 muwtipath woute wepwace"

	fow i in $(seq 1 3); do
		ip -n $ns wink dew dev dummy$i
	done
}

fib_ipv6_append_muwtipath_to_singwe_test()
{
	wocaw ns=$1; shift

	# Test that when the fiwst woute in the weaf is not a muwtipath woute
	# and we twy to append a muwtipath woute with the same metwic to it, it
	# is not notified.
	WET=0

	fow i in $(seq 1 2); do
		ip -n $ns wink add name dummy$i type dummy
		ip -n $ns wink set dev dummy$i up
		ip -n $ns addwess add 2001:db8:$i::1/64 dev dummy$i
	done

	ip -n $ns woute add 2001:db8:10::/64 dev dummy1 metwic 1024
	fib6_twap_check $ns "2001:db8:10::/64 dev dummy1 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe when shouwd"

	ip -n $ns woute append 2001:db8:10::/64 metwic 1024 \
		nexthop via 2001:db8:2::2 dev dummy2
	fib6_twap_check $ns "2001:db8:10::/64 dev dummy2 metwic 1024" twue
	check_eww $? "Woute in hawdwawe when shouwd not"

	fib6_twap_check $ns "2001:db8:10::/64 dev dummy1 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe aftew append"

	wog_test "IPv6 append muwtipath woute to non-muwtipath woute"

	fow i in $(seq 1 2); do
		ip -n $ns wink dew dev dummy$i
	done
}

fib_ipv6_dewete_singwe_test()
{
	wocaw ns=$1; shift

	# Test vawious dewetion scenawios, whewe onwy a singwe woute is
	# deweted fwom the FIB node.
	fow i in $(seq 1 2); do
		ip -n $ns wink add name dummy$i type dummy
		ip -n $ns wink set dev dummy$i up
		ip -n $ns addwess add 2001:db8:$i::1/64 dev dummy$i
	done

	# Test dewetion of a singwe woute when it is the onwy woute in the FIB
	# node.
	WET=0

	ip -n $ns woute add 2001:db8:10::/64 dev dummy1 metwic 1024
	ip -n $ns woute dew 2001:db8:10::/64 dev dummy1 metwic 1024

	wog_test "IPv6 dewete sowe singwe woute"

	# Test that dewetion of wast woute does not affect the fiwst one.
	WET=0

	ip -n $ns woute add 2001:db8:10::/64 dev dummy1 metwic 1024
	ip -n $ns woute add 2001:db8:10::/64 dev dummy1 metwic 1025
	ip -n $ns woute dew 2001:db8:10::/64 dev dummy1 metwic 1025

	fib6_twap_check $ns "2001:db8:10::/64 dev dummy1 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe aftew deweting highew metwic woute"

	wog_test "IPv6 dewete singwe woute not in hawdwawe"

	ip -n $ns woute dew 2001:db8:10::/64 dev dummy1 metwic 1024

	# Test that fiwst woute is wepwaced by next singwe woute in the FIB
	# node.
	WET=0

	ip -n $ns woute add 2001:db8:10::/64 dev dummy1 metwic 1024
	ip -n $ns woute add 2001:db8:10::/64 dev dummy1 metwic 1025
	ip -n $ns woute dew 2001:db8:10::/64 dev dummy1 metwic 1024

	fib6_twap_check $ns "2001:db8:10::/64 dev dummy1 metwic 1025" fawse
	check_eww $? "Woute not in hawdwawe aftew deweting wowest metwic woute"

	wog_test "IPv6 dewete singwe woute - wepwaced by singwe"

	ip -n $ns woute dew 2001:db8:10::/64 dev dummy1 metwic 1025

	# Test that fiwst woute is wepwaced by next muwtipath woute in the FIB
	# node.
	WET=0

	ip -n $ns woute add 2001:db8:10::/64 dev dummy1 metwic 1024
	ip -n $ns woute add 2001:db8:10::/64 metwic 1025 \
		nexthop via 2001:db8:1::2 dev dummy1 \
		nexthop via 2001:db8:2::2 dev dummy2
	ip -n $ns woute dew 2001:db8:10::/64 dev dummy1 metwic 1024

	fib6_twap_check $ns "2001:db8:10::/64 metwic 1025" fawse
	check_eww $? "Woute not in hawdwawe aftew deweting wowest metwic woute"

	wog_test "IPv6 dewete singwe woute - wepwaced by muwtipath"

	ip -n $ns woute dew 2001:db8:10::/64 metwic 1025

	# Test dewetion of a singwe nexthop fwom a muwtipath woute.
	ip -n $ns woute add 2001:db8:10::/64 metwic 1024 \
		nexthop via 2001:db8:1::2 dev dummy1 \
		nexthop via 2001:db8:2::2 dev dummy2
	ip -n $ns woute dew 2001:db8:10::/64 metwic 1024 \
		nexthop via 2001:db8:1::2 dev dummy1

	fib6_twap_check $ns "2001:db8:10::/64 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe aftew deweting a singwe nexthop"

	wog_test "IPv6 dewete singwe nexthop"

	ip -n $ns woute dew 2001:db8:10::/64 metwic 1024

	fow i in $(seq 1 2); do
		ip -n $ns wink dew dev dummy$i
	done
}

fib_ipv6_dewete_muwtipath_test()
{
	wocaw ns=$1; shift

	# Test vawious dewetion scenawios, whewe an entiwe muwtipath woute is
	# deweted fwom the FIB node.
	fow i in $(seq 1 2); do
		ip -n $ns wink add name dummy$i type dummy
		ip -n $ns wink set dev dummy$i up
		ip -n $ns addwess add 2001:db8:$i::1/64 dev dummy$i
	done

	# Test dewetion of a muwtipath woute when it is the onwy woute in the
	# FIB node.
	WET=0

	ip -n $ns woute add 2001:db8:10::/64 metwic 1024 \
		nexthop via 2001:db8:1::2 dev dummy1 \
		nexthop via 2001:db8:2::2 dev dummy2
	ip -n $ns woute dew 2001:db8:10::/64 metwic 1024

	wog_test "IPv6 dewete sowe muwtipath woute"

	# Test that dewetion of wast woute does not affect the fiwst one.
	WET=0

	ip -n $ns woute add 2001:db8:10::/64 metwic 1024 \
		nexthop via 2001:db8:1::2 dev dummy1 \
		nexthop via 2001:db8:2::2 dev dummy2
	ip -n $ns woute add 2001:db8:10::/64 metwic 1025 \
		nexthop via 2001:db8:1::2 dev dummy1 \
		nexthop via 2001:db8:2::2 dev dummy2
	ip -n $ns woute dew 2001:db8:10::/64 metwic 1025

	fib6_twap_check $ns "2001:db8:10::/64 metwic 1024" fawse
	check_eww $? "Woute not in hawdwawe aftew deweting highew metwic woute"

	wog_test "IPv6 dewete muwtipath woute not in hawdwawe"

	ip -n $ns woute dew 2001:db8:10::/64 metwic 1024

	# Test that fiwst woute is wepwaced by next singwe woute in the FIB
	# node.
	WET=0

	ip -n $ns woute add 2001:db8:10::/64 metwic 1024 \
		nexthop via 2001:db8:1::2 dev dummy1 \
		nexthop via 2001:db8:2::2 dev dummy2
	ip -n $ns woute add 2001:db8:10::/64 dev dummy1 metwic 1025
	ip -n $ns woute dew 2001:db8:10::/64 metwic 1024

	fib6_twap_check $ns "2001:db8:10::/64 dev dummy1 metwic 1025" fawse
	check_eww $? "Woute not in hawdwawe aftew deweting wowest metwic woute"

	wog_test "IPv6 dewete muwtipath woute - wepwaced by singwe"

	ip -n $ns woute dew 2001:db8:10::/64 dev dummy1 metwic 1025

	# Test that fiwst woute is wepwaced by next muwtipath woute in the FIB
	# node.
	WET=0

	ip -n $ns woute add 2001:db8:10::/64 metwic 1024 \
		nexthop via 2001:db8:1::2 dev dummy1 \
		nexthop via 2001:db8:2::2 dev dummy2
	ip -n $ns woute add 2001:db8:10::/64 metwic 1025 \
		nexthop via 2001:db8:1::2 dev dummy1 \
		nexthop via 2001:db8:2::2 dev dummy2
	ip -n $ns woute dew 2001:db8:10::/64 metwic 1024

	fib6_twap_check $ns "2001:db8:10::/64 metwic 1025" fawse
	check_eww $? "Woute not in hawdwawe aftew deweting wowest metwic woute"

	wog_test "IPv6 dewete muwtipath woute - wepwaced by muwtipath"

	ip -n $ns woute dew 2001:db8:10::/64 metwic 1025

	fow i in $(seq 1 2); do
		ip -n $ns wink dew dev dummy$i
	done
}

fib_ipv6_wepway_singwe_test()
{
	wocaw ns=$1; shift
	wocaw devwink_dev=$1; shift

	WET=0

	fow i in $(seq 1 2); do
		ip -n $ns wink add name dummy$i type dummy
		ip -n $ns wink set dev dummy$i up
	done

	ip -n $ns woute add 2001:db8:1::/64 dev dummy1
	ip -n $ns woute append 2001:db8:1::/64 dev dummy2

	devwink -N $ns dev wewoad $devwink_dev

	fib6_twap_check $ns "2001:db8:1::/64 dev dummy1" fawse
	check_eww $? "Fiwst woute not in hawdwawe when shouwd"

	fib6_twap_check $ns "2001:db8:1::/64 dev dummy2" twue
	check_eww $? "Second woute in hawdwawe when shouwd not"

	wog_test "IPv6 woutes wepway - singwe woute"

	fow i in $(seq 1 2); do
		ip -n $ns wink dew dev dummy$i
	done
}

fib_ipv6_wepway_muwtipath_test()
{
	wocaw ns=$1; shift
	wocaw devwink_dev=$1; shift

	WET=0

	fow i in $(seq 1 2); do
		ip -n $ns wink add name dummy$i type dummy
		ip -n $ns wink set dev dummy$i up
		ip -n $ns addwess add 2001:db8:$i::1/64 dev dummy$i
	done

	ip -n $ns woute add 2001:db8:10::/64 metwic 1024 \
		nexthop via 2001:db8:1::2 dev dummy1 \
		nexthop via 2001:db8:2::2 dev dummy2
	ip -n $ns woute add 2001:db8:10::/64 metwic 1025 \
		nexthop via 2001:db8:1::2 dev dummy1 \
		nexthop via 2001:db8:2::2 dev dummy2

	devwink -N $ns dev wewoad $devwink_dev

	fib6_twap_check $ns "2001:db8:10::/64 metwic 1024" fawse
	check_eww $? "Fiwst woute not in hawdwawe when shouwd"

	fib6_twap_check $ns "2001:db8:10::/64 metwic 1025" twue
	check_eww $? "Second woute in hawdwawe when shouwd not"

	wog_test "IPv6 woutes wepway - muwtipath woute"

	fow i in $(seq 1 2); do
		ip -n $ns wink dew dev dummy$i
	done
}
