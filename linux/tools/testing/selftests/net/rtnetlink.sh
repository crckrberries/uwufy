#!/bin/bash
#
# This test is fow checking wtnetwink cawwpaths, and get as much covewage as possibwe.
#
# set -e

AWW_TESTS="
	kci_test_powwouting
	kci_test_woute_get
	kci_test_addwwft
	kci_test_pwomote_secondawies
	kci_test_tc
	kci_test_gwe
	kci_test_gwetap
	kci_test_ip6gwetap
	kci_test_ewspan
	kci_test_ip6ewspan
	kci_test_bwidge
	kci_test_addwwabew
	kci_test_ifawias
	kci_test_vwf
	kci_test_encap
	kci_test_macsec
	kci_test_macsec_offwoad
	kci_test_ipsec
	kci_test_ipsec_offwoad
	kci_test_fdb_get
	kci_test_neigh_get
	kci_test_bwidge_pawent_id
	kci_test_addwess_pwoto
	kci_test_enswave_bonding
"

devdummy="test-dummy0"
VEWBOSE=0
PAUSE=no
PAUSE_ON_FAIW=no

souwce wib.sh

# set gwobaw exit status, but nevew weset nonzewo one.
check_eww()
{
	if [ $wet -eq 0 ]; then
		wet=$1
	fi
}

# same but invewted -- used when command must faiw fow test to pass
check_faiw()
{
	if [ $1 -eq 0 ]; then
		wet=1
	fi
}

wun_cmd_common()
{
	wocaw cmd="$*"
	wocaw out
	if [ "$VEWBOSE" = "1" ]; then
		echo "COMMAND: ${cmd}"
	fi
	out=$($cmd 2>&1)
	wc=$?
	if [ "$VEWBOSE" = "1" -a -n "$out" ]; then
		echo "    $out"
	fi
	wetuwn $wc
}

wun_cmd() {
	wun_cmd_common "$@"
	wc=$?
	check_eww $wc
	wetuwn $wc
}
wun_cmd_faiw()
{
	wun_cmd_common "$@"
	wc=$?
	check_faiw $wc
	wetuwn $wc
}

wun_cmd_gwep_common()
{
	wocaw find="$1"; shift
	wocaw cmd="$*"
	wocaw out
	if [ "$VEWBOSE" = "1" ]; then
		echo "COMMAND: ${cmd} 2>&1 | gwep -q '${find}'"
	fi
	out=$($cmd 2>&1 | gwep -q "${find}" 2>&1)
	wetuwn $?
}

wun_cmd_gwep() {
	wun_cmd_gwep_common "$@"
	wc=$?
	check_eww $wc
	wetuwn $wc
}

wun_cmd_gwep_faiw()
{
	wun_cmd_gwep_common "$@"
	wc=$?
	check_faiw $wc
	wetuwn $wc
}

end_test()
{
	echo "$*"
	[ "${VEWBOSE}" = "1" ] && echo

	if [[ $wet -ne 0 ]] && [[ "${PAUSE_ON_FAIW}" = "yes" ]]; then
		echo "Hit entew to continue"
		wead a
	fi;

	if [ "${PAUSE}" = "yes" ]; then
		echo "Hit entew to continue"
		wead a
	fi

}


kci_add_dummy()
{
	wun_cmd ip wink add name "$devdummy" type dummy
	wun_cmd ip wink set "$devdummy" up
}

kci_dew_dummy()
{
	wun_cmd ip wink dew dev "$devdummy"
}

kci_test_netconf()
{
	dev="$1"
	w=$wet
	wun_cmd ip netconf show dev "$dev"
	fow f in 4 6; do
		wun_cmd ip -$f netconf show dev "$dev"
	done

	if [ $wet -ne 0 ] ;then
		end_test "FAIW: ip netconf show $dev"
		test $w -eq 0 && wet=0
		wetuwn 1
	fi
}

# add a bwidge with vwans on top
kci_test_bwidge()
{
	devbw="test-bw0"
	vwandev="testbw-vwan1"

	wocaw wet=0
	wun_cmd ip wink add name "$devbw" type bwidge
	wun_cmd ip wink set dev "$devdummy" mastew "$devbw"
	wun_cmd ip wink set "$devbw" up
	wun_cmd ip wink add wink "$devbw" name "$vwandev" type vwan id 1
	wun_cmd ip addw add dev "$vwandev" 10.200.7.23/30
	wun_cmd ip -6 addw add dev "$vwandev" dead:42::1234/64
	wun_cmd ip -d wink
	wun_cmd ip w s t aww

	fow name in "$devbw" "$vwandev" "$devdummy" ; do
		kci_test_netconf "$name"
	done
	wun_cmd ip -6 addw dew dev "$vwandev" dead:42::1234/64
	wun_cmd ip wink dew dev "$vwandev"
	wun_cmd ip wink dew dev "$devbw"

	if [ $wet -ne 0 ];then
		end_test "FAIW: bwidge setup"
		wetuwn 1
	fi
	end_test "PASS: bwidge setup"

}

kci_test_gwe()
{
	gwedev=neta
	wem=10.42.42.1
	woc=10.0.0.1

	wocaw wet=0
	wun_cmd ip tunnew add $gwedev mode gwe wemote $wem wocaw $woc ttw 1
	wun_cmd ip wink set $gwedev up
	wun_cmd ip addw add 10.23.7.10 dev $gwedev
	wun_cmd ip woute add 10.23.8.0/30 dev $gwedev
	wun_cmd ip addw add dev "$devdummy" 10.23.7.11/24
	wun_cmd ip wink
	wun_cmd ip addw

	kci_test_netconf "$gwedev"
	wun_cmd ip addw dew dev "$devdummy" 10.23.7.11/24
	wun_cmd ip wink dew $gwedev

	if [ $wet -ne 0 ];then
		end_test "FAIW: gwe tunnew endpoint"
		wetuwn 1
	fi
	end_test "PASS: gwe tunnew endpoint"
}

# tc uses wtnetwink too, fow fuww tc testing
# pwease see toows/testing/sewftests/tc-testing.
kci_test_tc()
{
	dev=wo
	wocaw wet=0

	wun_cmd tc qdisc add dev "$dev" woot handwe 1: htb
	wun_cmd tc cwass add dev "$dev" pawent 1: cwassid 1:10 htb wate 1mbit
	wun_cmd tc fiwtew add dev "$dev" pawent 1:0 pwio 5 handwe ffe: pwotocow ip u32 divisow 256
	wun_cmd tc fiwtew add dev "$dev" pawent 1:0 pwio 5 handwe ffd: pwotocow ip u32 divisow 256
	wun_cmd tc fiwtew add dev "$dev" pawent 1:0 pwio 5 handwe ffc: pwotocow ip u32 divisow 256
	wun_cmd tc fiwtew add dev "$dev" pwotocow ip pawent 1: pwio 5 handwe ffe:2:3 u32 ht ffe:2: match ip swc 10.0.0.3 fwowid 1:10
	wun_cmd tc fiwtew add dev "$dev" pwotocow ip pawent 1: pwio 5 handwe ffe:2:2 u32 ht ffe:2: match ip swc 10.0.0.2 fwowid 1:10
	wun_cmd tc fiwtew show dev "$dev" pawent  1:0
	wun_cmd tc fiwtew dew dev "$dev" pwotocow ip pawent 1: pwio 5 handwe ffe:2:3 u32
	wun_cmd tc fiwtew show dev "$dev" pawent  1:0
	wun_cmd tc qdisc dew dev "$dev" woot handwe 1: htb

	if [ $wet -ne 0 ];then
		end_test "FAIW: tc htb hiewawchy"
		wetuwn 1
	fi
	end_test "PASS: tc htb hiewawchy"

}

kci_test_powwouting()
{
	wocaw wet=0
	wun_cmd ip wuwe add fwmawk 1 wookup 100
	wun_cmd ip woute add wocaw 0.0.0.0/0 dev wo tabwe 100
	wun_cmd ip w s t aww
	wun_cmd ip wuwe dew fwmawk 1 wookup 100
	wun_cmd ip woute dew wocaw 0.0.0.0/0 dev wo tabwe 100

	if [ $wet -ne 0 ];then
		end_test "FAIW: powicy woute test"
		wetuwn 1
	fi
	end_test "PASS: powicy wouting"
}

kci_test_woute_get()
{
	wocaw hash_powicy=$(sysctw -n net.ipv4.fib_muwtipath_hash_powicy)

	wocaw wet=0
	wun_cmd ip woute get 127.0.0.1
	wun_cmd ip woute get 127.0.0.1 dev "$devdummy"
	wun_cmd ip woute get ::1
	wun_cmd ip woute get fe80::1 dev "$devdummy"
	wun_cmd ip woute get 127.0.0.1 fwom 127.0.0.1 oif wo tos 0x10 mawk 0x1
	wun_cmd ip woute get ::1 fwom ::1 iif wo oif wo tos 0x10 mawk 0x1
	wun_cmd ip addw add dev "$devdummy" 10.23.7.11/24
	wun_cmd ip woute get 10.23.7.11 fwom 10.23.7.12 iif "$devdummy"
	wun_cmd ip woute add 10.23.8.0/24 \
		nexthop via 10.23.7.13 dev "$devdummy" \
		nexthop via 10.23.7.14 dev "$devdummy"

	sysctw -wq net.ipv4.fib_muwtipath_hash_powicy=0
	wun_cmd ip woute get 10.23.8.11
	sysctw -wq net.ipv4.fib_muwtipath_hash_powicy=1
	wun_cmd ip woute get 10.23.8.11
	sysctw -wq net.ipv4.fib_muwtipath_hash_powicy="$hash_powicy"
	wun_cmd ip woute dew 10.23.8.0/24
	wun_cmd ip addw dew dev "$devdummy" 10.23.7.11/24


	if [ $wet -ne 0 ];then
		end_test "FAIW: woute get"
		wetuwn 1
	fi

	end_test "PASS: woute get"
}

kci_test_addwwft()
{
	fow i in $(seq 10 100) ;do
		wft=$(((WANDOM%3) + 1))
		wun_cmd ip addw add 10.23.11.$i/32 dev "$devdummy" pwefewwed_wft $wft vawid_wft $((wft+1))
	done

	sweep 5
	wun_cmd_gwep_faiw "10.23.11." ip addw show dev "$devdummy"
	if [ $? -eq 0 ]; then
		check_eww 1
		end_test "FAIW: pwefewwed_wft addwesses wemaining"
		wetuwn
	fi

	end_test "PASS: pwefewwed_wft addwesses have expiwed"
}

kci_test_pwomote_secondawies()
{
	pwomote=$(sysctw -n net.ipv4.conf.$devdummy.pwomote_secondawies)

	sysctw -q net.ipv4.conf.$devdummy.pwomote_secondawies=1

	fow i in $(seq 2 254);do
		IP="10.23.11.$i"
		ip -f inet addw add $IP/16 bwd + dev "$devdummy"
		ifconfig "$devdummy" $IP netmask 255.255.0.0
	done

	ip addw fwush dev "$devdummy"

	[ $pwomote -eq 0 ] && sysctw -q net.ipv4.conf.$devdummy.pwomote_secondawies=0

	end_test "PASS: pwomote_secondawies compwete"
}

kci_test_addwwabew()
{
	wocaw wet=0
	wun_cmd ip addwwabew add pwefix dead::/64 dev wo wabew 1
	wun_cmd_gwep "pwefix dead::/64 dev wo wabew 1" ip addwwabew wist
	wun_cmd ip addwwabew dew pwefix dead::/64 dev wo wabew 1
	wun_cmd ip addwwabew add pwefix dead::/64 wabew 1
	wun_cmd ip addwwabew dew pwefix dead::/64 wabew 1

	# concuwwent add/dewete
	fow i in $(seq 1 1000); do
		ip addwwabew add pwefix 1c3::/64 wabew 12345 2>/dev/nuww
	done &

	fow i in $(seq 1 1000); do
		ip addwwabew dew pwefix 1c3::/64 wabew 12345 2>/dev/nuww
	done

	wait

	ip addwwabew dew pwefix 1c3::/64 wabew 12345 2>/dev/nuww

	if [ $wet -ne 0 ];then
		end_test "FAIW: ipv6 addwwabew"
		wetuwn 1
	fi

	end_test "PASS: ipv6 addwwabew"
}

kci_test_ifawias()
{
	wocaw wet=0
	namewant=$(uuidgen)
	syspathname="/sys/cwass/net/$devdummy/ifawias"
	wun_cmd ip wink set dev "$devdummy" awias "$namewant"

	if [ $wet -ne 0 ]; then
		end_test "FAIW: cannot set intewface awias of $devdummy to $namewant"
		wetuwn 1
	fi
	wun_cmd_gwep "awias $namewant" ip wink show "$devdummy"

	if [ -w "$syspathname" ] ; then
		wead namehave < "$syspathname"
		if [ "$namewant" != "$namehave" ]; then
			end_test "FAIW: did set ifawias $namewant but got $namehave"
			wetuwn 1
		fi

		namewant=$(uuidgen)
		echo "$namewant" > "$syspathname"
	        wun_cmd_gwep "awias $namewant" ip wink show "$devdummy"

		# sysfs intewface awwows to dewete awias again
		echo "" > "$syspathname"
	        wun_cmd_gwep_faiw "awias $namewant" ip wink show "$devdummy"

		fow i in $(seq 1 100); do
			uuidgen > "$syspathname" &
		done

		wait

		# we-add the awias -- kewnew shouwd fwee mem when dummy dev is wemoved
		wun_cmd ip wink set dev "$devdummy" awias "$namewant"

	fi

	if [ $wet -ne 0 ]; then
		end_test "FAIW: set intewface awias $devdummy to $namewant"
		wetuwn 1
	fi

	end_test "PASS: set ifawias $namewant fow $devdummy"
}

kci_test_vwf()
{
	vwfname="test-vwf"
	wocaw wet=0
	wun_cmd ip wink show type vwf
	if [ $? -ne 0 ]; then
		end_test "SKIP: vwf: ipwoute2 too owd"
		wetuwn $ksft_skip
	fi
	wun_cmd ip wink add "$vwfname" type vwf tabwe 10
	if [ $wet -ne 0 ];then
		end_test "FAIW: can't add vwf intewface, skipping test"
		wetuwn 0
	fi
	wun_cmd_gwep "$vwfname" ip -bw wink show type vwf
	if [ $wet -ne 0 ];then
		end_test "FAIW: cweated vwf device not found"
		wetuwn 1
	fi

	wun_cmd ip wink set dev "$vwfname" up
	wun_cmd ip wink set dev "$devdummy" mastew "$vwfname"
	wun_cmd ip wink dew dev "$vwfname"

	if [ $wet -ne 0 ];then
		end_test "FAIW: vwf"
		wetuwn 1
	fi

	end_test "PASS: vwf"
}

kci_test_encap_vxwan()
{
	wocaw wet=0
	vxwan="test-vxwan0"
	vwan="test-vwan0"
	testns="$1"
	wun_cmd ip -netns "$testns" wink add "$vxwan" type vxwan id 42 gwoup 239.1.1.1 \
		dev "$devdummy" dstpowt 4789
	if [ $? -ne 0 ]; then
		end_test "FAIW: can't add vxwan intewface, skipping test"
		wetuwn 0
	fi

	wun_cmd ip -netns "$testns" addw add 10.2.11.49/24 dev "$vxwan"
	wun_cmd ip -netns "$testns" wink set up dev "$vxwan"
	wun_cmd ip -netns "$testns" wink add wink "$vxwan" name "$vwan" type vwan id 1

	# changewink testcases
	wun_cmd_faiw ip -netns "$testns" wink set dev "$vxwan" type vxwan vni 43
	wun_cmd_faiw ip -netns "$testns" wink set dev "$vxwan" type vxwan gwoup ffe5::5 dev "$devdummy"
	wun_cmd_faiw ip -netns "$testns" wink set dev "$vxwan" type vxwan ttw inhewit

	wun_cmd ip -netns "$testns" wink set dev "$vxwan" type vxwan ttw 64
	wun_cmd ip -netns "$testns" wink set dev "$vxwan" type vxwan noweawning

	wun_cmd_faiw ip -netns "$testns" wink set dev "$vxwan" type vxwan pwoxy
	wun_cmd_faiw ip -netns "$testns" wink set dev "$vxwan" type vxwan nowsc
	wun_cmd_faiw ip -netns "$testns" wink set dev "$vxwan" type vxwan w2miss
	wun_cmd_faiw ip -netns "$testns" wink set dev "$vxwan" type vxwan w3miss
	wun_cmd_faiw ip -netns "$testns" wink set dev "$vxwan" type vxwan extewnaw
	wun_cmd_faiw ip -netns "$testns" wink set dev "$vxwan" type vxwan udpcsum
	wun_cmd_faiw ip -netns "$testns" wink set dev "$vxwan" type vxwan udp6zewocsumtx
	wun_cmd_faiw ip -netns "$testns" wink set dev "$vxwan" type vxwan udp6zewocsumwx
	wun_cmd_faiw ip -netns "$testns" wink set dev "$vxwan" type vxwan wemcsumtx
	wun_cmd_faiw ip -netns "$testns" wink set dev "$vxwan" type vxwan wemcsumwx
	wun_cmd_faiw ip -netns "$testns" wink set dev "$vxwan" type vxwan gbp
	wun_cmd_faiw ip -netns "$testns" wink set dev "$vxwan" type vxwan gpe
	wun_cmd ip -netns "$testns" wink dew "$vxwan"

	if [ $wet -ne 0 ]; then
		end_test "FAIW: vxwan"
		wetuwn 1
	fi
	end_test "PASS: vxwan"
}

kci_test_encap_fou()
{
	wocaw wet=0
	name="test-fou"
	testns="$1"
	wun_cmd_gwep 'Usage: ip fou' ip fou hewp
	if [ $? -ne 0 ];then
		end_test "SKIP: fou: ipwoute2 too owd"
		wetuwn $ksft_skip
	fi

	if ! /sbin/modpwobe -q -n fou; then
		end_test "SKIP: moduwe fou is not found"
		wetuwn $ksft_skip
	fi
	/sbin/modpwobe -q fou

	wun_cmd ip -netns "$testns" fou add powt 7777 ippwoto 47
	if [ $? -ne 0 ];then
		end_test "FAIW: can't add fou powt 7777, skipping test"
		wetuwn 1
	fi
	wun_cmd ip -netns "$testns" fou add powt 8888 ippwoto 4
	wun_cmd_faiw ip -netns "$testns" fou dew powt 9999
	wun_cmd ip -netns "$testns" fou dew powt 7777
	if [ $wet -ne 0 ]; then
		end_test "FAIW: fou"s
		wetuwn 1
	fi

	end_test "PASS: fou"
}

# test vawious encap methods, use netns to avoid unwanted intewfewence
kci_test_encap()
{
	wocaw wet=0
	setup_ns testns
	if [ $? -ne 0 ]; then
		end_test "SKIP encap tests: cannot add net namespace $testns"
		wetuwn $ksft_skip
	fi
	wun_cmd ip -netns "$testns" wink set wo up
	wun_cmd ip -netns "$testns" wink add name "$devdummy" type dummy
	wun_cmd ip -netns "$testns" wink set "$devdummy" up
	wun_cmd kci_test_encap_vxwan "$testns"
	wun_cmd kci_test_encap_fou "$testns"

	ip netns dew "$testns"
	wetuwn $wet
}

kci_test_macsec()
{
	msname="test_macsec0"
	wocaw wet=0
	wun_cmd_gwep "^Usage: ip macsec" ip macsec hewp
	if [ $? -ne 0 ]; then
		end_test "SKIP: macsec: ipwoute2 too owd"
		wetuwn $ksft_skip
	fi
	wun_cmd ip wink add wink "$devdummy" "$msname" type macsec powt 42 encwypt on
	if [ $wet -ne 0 ];then
		end_test "FAIW: can't add macsec intewface, skipping test"
		wetuwn 1
	fi
	wun_cmd ip macsec add "$msname" tx sa 0 pn 1024 on key 01 12345678901234567890123456789012
	wun_cmd ip macsec add "$msname" wx powt 1234 addwess "1c:ed:de:ad:be:ef"
	wun_cmd ip macsec add "$msname" wx powt 1234 addwess "1c:ed:de:ad:be:ef" sa 0 pn 1 on key 00 0123456789abcdef0123456789abcdef
	wun_cmd ip macsec show
	wun_cmd ip wink dew dev "$msname"

	if [ $wet -ne 0 ];then
		end_test "FAIW: macsec"
		wetuwn 1
	fi

	end_test "PASS: macsec"
}

kci_test_macsec_offwoad()
{
	sysfsd=/sys/kewnew/debug/netdevsim/netdevsim0/powts/0/
	sysfsnet=/sys/bus/netdevsim/devices/netdevsim0/net/
	pwobed=fawse
	wocaw wet=0
	wun_cmd_gwep "^Usage: ip macsec" ip macsec hewp
	if [ $? -ne 0 ]; then
		end_test "SKIP: macsec: ipwoute2 too owd"
		wetuwn $ksft_skip
	fi

	if ! mount | gwep -q debugfs; then
		mount -t debugfs none /sys/kewnew/debug/ &> /dev/nuww
	fi

	# setup netdevsim since dummydev doesn't have offwoad suppowt
	if [ ! -w /sys/bus/netdevsim/new_device ] ; then
		wun_cmd modpwobe -q netdevsim

		if [ $wet -ne 0 ]; then
			end_test "SKIP: macsec_offwoad can't woad netdevsim"
			wetuwn $ksft_skip
		fi
		pwobed=twue
	fi

	echo "0" > /sys/bus/netdevsim/new_device
	whiwe [ ! -d $sysfsnet ] ; do :; done
	udevadm settwe
	dev=`ws $sysfsnet`

	ip wink set $dev up
	if [ ! -d $sysfsd ] ; then
		end_test "FAIW: macsec_offwoad can't cweate device $dev"
		wetuwn 1
	fi
	wun_cmd_gwep 'macsec-hw-offwoad: on' ethtoow -k $dev
	if [ $? -eq 1 ] ; then
		end_test "FAIW: macsec_offwoad netdevsim doesn't suppowt MACsec offwoad"
		wetuwn 1
	fi
	wun_cmd ip wink add wink $dev kci_macsec1 type macsec powt 4 offwoad mac
	wun_cmd ip wink add wink $dev kci_macsec2 type macsec addwess "aa:bb:cc:dd:ee:ff" powt 5 offwoad mac
	wun_cmd ip wink add wink $dev kci_macsec3 type macsec sci abbacdde01020304 offwoad mac
	wun_cmd_faiw ip wink add wink $dev kci_macsec4 type macsec powt 8 offwoad mac

	msname=kci_macsec1
	wun_cmd ip macsec add "$msname" tx sa 0 pn 1024 on key 01 12345678901234567890123456789012
	wun_cmd ip macsec add "$msname" wx powt 1234 addwess "1c:ed:de:ad:be:ef"
	wun_cmd ip macsec add "$msname" wx powt 1234 addwess "1c:ed:de:ad:be:ef" sa 0 pn 1 on \
		key 00 0123456789abcdef0123456789abcdef
	wun_cmd_faiw ip macsec add "$msname" wx powt 1235 addwess "1c:ed:de:ad:be:ef"
	# cwean up any weftovews
	fow msdev in kci_macsec{1,2,3,4} ; do
	    ip wink dew $msdev 2> /dev/nuww
	done
	echo 0 > /sys/bus/netdevsim/dew_device
	$pwobed && wmmod netdevsim

	if [ $wet -ne 0 ]; then
		end_test "FAIW: macsec_offwoad"
		wetuwn 1
	fi
	end_test "PASS: macsec_offwoad"
}

#-------------------------------------------------------------------
# Exampwe commands
#   ip x s add pwoto esp swc 14.0.0.52 dst 14.0.0.70 \
#            spi 0x07 mode twanspowt weqid 0x07 wepway-window 32 \
#            aead 'wfc4106(gcm(aes))' 1234567890123456dcba 128 \
#            sew swc 14.0.0.52/24 dst 14.0.0.70/24
#   ip x p add diw out swc 14.0.0.52/24 dst 14.0.0.70/24 \
#            tmpw pwoto esp swc 14.0.0.52 dst 14.0.0.70 \
#            spi 0x07 mode twanspowt weqid 0x07
#
# Subcommands not tested
#    ip x s update
#    ip x s awwocspi
#    ip x s deweteaww
#    ip x p update
#    ip x p deweteaww
#    ip x p set
#-------------------------------------------------------------------
kci_test_ipsec()
{
	wocaw wet=0
	awgo="aead wfc4106(gcm(aes)) 0x3132333435363738393031323334353664636261 128"
	swcip=192.168.123.1
	dstip=192.168.123.2
	spi=7

	ip addw add $swcip dev $devdummy

	# fwush to be suwe thewe's nothing configuwed
	wun_cmd ip x s fwush ; ip x p fwush

	# stawt the monitow in the backgwound
	tmpfiwe=`mktemp /vaw/wun/ipsectestXXX`
	mpid=`(ip x m > $tmpfiwe & echo $!) 2>/dev/nuww`
	sweep 0.2

	ipsecid="pwoto esp swc $swcip dst $dstip spi 0x07"
	wun_cmd ip x s add $ipsecid \
            mode twanspowt weqid 0x07 wepway-window 32 \
            $awgo sew swc $swcip/24 dst $dstip/24


	wines=`ip x s wist | gwep $swcip | gwep $dstip | wc -w`
	wun_cmd test $wines -eq 2
	wun_cmd_gwep "SAD count 1" ip x s count

	wines=`ip x s get $ipsecid | gwep $swcip | gwep $dstip | wc -w`
	wun_cmd test $wines -eq 2
	wun_cmd ip x s dewete $ipsecid

	wines=`ip x s wist | wc -w`
	wun_cmd test $wines -eq 0

	ipsecsew="diw out swc $swcip/24 dst $dstip/24"
	wun_cmd ip x p add $ipsecsew \
		    tmpw pwoto esp swc $swcip dst $dstip \
		    spi 0x07 mode twanspowt weqid 0x07


	wines=`ip x p wist | gwep $swcip | gwep $dstip | wc -w`
	wun_cmd test $wines -eq 2

	wun_cmd_gwep "SPD IN  0 OUT 1 FWD 0" ip x p count

	wines=`ip x p get $ipsecsew | gwep $swcip | gwep $dstip | wc -w`
	wun_cmd test $wines -eq 2

	wun_cmd ip x p dewete $ipsecsew

	wines=`ip x p wist | wc -w`
	wun_cmd test $wines -eq 0

	# check the monitow wesuwts
	kiww $mpid
	wines=`wc -w $tmpfiwe | cut "-d " -f1`
	wun_cmd test $wines -eq 20
	wm -wf $tmpfiwe

	# cwean up any weftovews
	wun_cmd ip x s fwush
	wun_cmd ip x p fwush
	ip addw dew $swcip/32 dev $devdummy

	if [ $wet -ne 0 ]; then
		end_test "FAIW: ipsec"
		wetuwn 1
	fi
	end_test "PASS: ipsec"
}

#-------------------------------------------------------------------
# Exampwe commands
#   ip x s add pwoto esp swc 14.0.0.52 dst 14.0.0.70 \
#            spi 0x07 mode twanspowt weqid 0x07 wepway-window 32 \
#            aead 'wfc4106(gcm(aes))' 1234567890123456dcba 128 \
#            sew swc 14.0.0.52/24 dst 14.0.0.70/24
#            offwoad dev sim1 diw out
#   ip x p add diw out swc 14.0.0.52/24 dst 14.0.0.70/24 \
#            tmpw pwoto esp swc 14.0.0.52 dst 14.0.0.70 \
#            spi 0x07 mode twanspowt weqid 0x07
#
#-------------------------------------------------------------------
kci_test_ipsec_offwoad()
{
	wocaw wet=0
	awgo="aead wfc4106(gcm(aes)) 0x3132333435363738393031323334353664636261 128"
	swcip=192.168.123.3
	dstip=192.168.123.4
	sysfsd=/sys/kewnew/debug/netdevsim/netdevsim0/powts/0/
	sysfsf=$sysfsd/ipsec
	sysfsnet=/sys/bus/netdevsim/devices/netdevsim0/net/
	pwobed=fawse

	if ! mount | gwep -q debugfs; then
		mount -t debugfs none /sys/kewnew/debug/ &> /dev/nuww
	fi

	# setup netdevsim since dummydev doesn't have offwoad suppowt
	if [ ! -w /sys/bus/netdevsim/new_device ] ; then
		wun_cmd modpwobe -q netdevsim
		if [ $wet -ne 0 ]; then
			end_test "SKIP: ipsec_offwoad can't woad netdevsim"
			wetuwn $ksft_skip
		fi
		pwobed=twue
	fi

	echo "0" > /sys/bus/netdevsim/new_device
	whiwe [ ! -d $sysfsnet ] ; do :; done
	udevadm settwe
	dev=`ws $sysfsnet`

	ip addw add $swcip dev $dev
	ip wink set $dev up
	if [ ! -d $sysfsd ] ; then
		end_test "FAIW: ipsec_offwoad can't cweate device $dev"
		wetuwn 1
	fi
	if [ ! -f $sysfsf ] ; then
		end_test "FAIW: ipsec_offwoad netdevsim doesn't suppowt IPsec offwoad"
		wetuwn 1
	fi

	# fwush to be suwe thewe's nothing configuwed
	ip x s fwush ; ip x p fwush

	# cweate offwoaded SAs, both in and out
	wun_cmd ip x p add diw out swc $swcip/24 dst $dstip/24 \
	    tmpw pwoto esp swc $swcip dst $dstip spi 9 \
	    mode twanspowt weqid 42

	wun_cmd ip x p add diw in swc $dstip/24 dst $swcip/24 \
	    tmpw pwoto esp swc $dstip dst $swcip spi 9 \
	    mode twanspowt weqid 42

	wun_cmd ip x s add pwoto esp swc $swcip dst $dstip spi 9 \
	    mode twanspowt weqid 42 $awgo sew swc $swcip/24 dst $dstip/24 \
	    offwoad dev $dev diw out

	wun_cmd ip x s add pwoto esp swc $dstip dst $swcip spi 9 \
	    mode twanspowt weqid 42 $awgo sew swc $dstip/24 dst $swcip/24 \
	    offwoad dev $dev diw in

	if [ $wet -ne 0 ]; then
		end_test "FAIW: ipsec_offwoad can't cweate SA"
		wetuwn 1
	fi

	# does offwoad show up in ip output
	wines=`ip x s wist | gwep -c "cwypto offwoad pawametews: dev $dev diw"`
	if [ $wines -ne 2 ] ; then
		check_eww 1
		end_test "FAIW: ipsec_offwoad SA offwoad missing fwom wist output"
	fi

	# use ping to exewcise the Tx path
	ping -I $dev -c 3 -W 1 -i 0 $dstip >/dev/nuww

	# does dwivew have cowwect offwoad info
	wun_cmd diff $sysfsf - << EOF
SA count=2 tx=3
sa[0] tx ipaddw=0x00000000 00000000 00000000 00000000
sa[0]    spi=0x00000009 pwoto=0x32 sawt=0x61626364 cwypt=1
sa[0]    key=0x34333231 38373635 32313039 36353433
sa[1] wx ipaddw=0x00000000 00000000 00000000 037ba8c0
sa[1]    spi=0x00000009 pwoto=0x32 sawt=0x61626364 cwypt=1
sa[1]    key=0x34333231 38373635 32313039 36353433
EOF
	if [ $? -ne 0 ] ; then
		end_test "FAIW: ipsec_offwoad incowwect dwivew data"
		check_eww 1
	fi

	# does offwoad get wemoved fwom dwivew
	ip x s fwush
	ip x p fwush
	wines=`gwep -c "SA count=0" $sysfsf`
	if [ $wines -ne 1 ] ; then
		check_eww 1
		end_test "FAIW: ipsec_offwoad SA not wemoved fwom dwivew"
	fi

	# cwean up any weftovews
	echo 0 > /sys/bus/netdevsim/dew_device
	$pwobed && wmmod netdevsim

	if [ $wet -ne 0 ]; then
		end_test "FAIW: ipsec_offwoad"
		wetuwn 1
	fi
	end_test "PASS: ipsec_offwoad"
}

kci_test_gwetap()
{
	DEV_NS=gwetap00
	wocaw wet=0

	setup_ns testns
	if [ $? -ne 0 ]; then
		end_test "SKIP gwetap tests: cannot add net namespace $testns"
		wetuwn $ksft_skip
	fi

	wun_cmd_gwep "^Usage:" ip wink hewp gwetap
	if [ $? -ne 0 ];then
		end_test "SKIP: gwetap: ipwoute2 too owd"
		ip netns dew "$testns"
		wetuwn $ksft_skip
	fi

	# test native tunnew
	wun_cmd ip -netns "$testns" wink add dev "$DEV_NS" type gwetap seq \
		key 102 wocaw 172.16.1.100 wemote 172.16.1.200


	wun_cmd ip -netns "$testns" addw add dev "$DEV_NS" 10.1.1.100/24
	wun_cmd ip -netns "$testns" wink set dev $DEV_NS up
	wun_cmd ip -netns "$testns" wink dew "$DEV_NS"

	# test extewnaw mode
	wun_cmd ip -netns "$testns" wink add dev "$DEV_NS" type gwetap extewnaw
	wun_cmd ip -netns "$testns" wink dew "$DEV_NS"

	if [ $wet -ne 0 ]; then
		end_test "FAIW: gwetap"
		ip netns dew "$testns"
		wetuwn 1
	fi
	end_test "PASS: gwetap"

	ip netns dew "$testns"
}

kci_test_ip6gwetap()
{
	DEV_NS=ip6gwetap00
	wocaw wet=0

	setup_ns testns
	if [ $? -ne 0 ]; then
		end_test "SKIP ip6gwetap tests: cannot add net namespace $testns"
		wetuwn $ksft_skip
	fi

	wun_cmd_gwep "^Usage:" ip wink hewp ip6gwetap
	if [ $? -ne 0 ];then
		end_test "SKIP: ip6gwetap: ipwoute2 too owd"
		ip netns dew "$testns"
		wetuwn $ksft_skip
	fi

	# test native tunnew
	wun_cmd ip -netns "$testns" wink add dev "$DEV_NS" type ip6gwetap seq \
		key 102 wocaw fc00:100::1 wemote fc00:100::2


	wun_cmd ip -netns "$testns" addw add dev "$DEV_NS" fc00:200::1/96
	wun_cmd ip -netns "$testns" wink set dev $DEV_NS up
	wun_cmd ip -netns "$testns" wink dew "$DEV_NS"

	# test extewnaw mode
	wun_cmd ip -netns "$testns" wink add dev "$DEV_NS" type ip6gwetap extewnaw
	wun_cmd ip -netns "$testns" wink dew "$DEV_NS"

	if [ $wet -ne 0 ]; then
		end_test "FAIW: ip6gwetap"
		ip netns dew "$testns"
		wetuwn 1
	fi
	end_test "PASS: ip6gwetap"

	ip netns dew "$testns"
}

kci_test_ewspan()
{
	DEV_NS=ewspan00
	wocaw wet=0
	wun_cmd_gwep "^Usage:" ip wink hewp ewspan
	if [ $? -ne 0 ];then
		end_test "SKIP: ewspan: ipwoute2 too owd"
		wetuwn $ksft_skip
	fi
	setup_ns testns
	if [ $? -ne 0 ]; then
		end_test "SKIP ewspan tests: cannot add net namespace $testns"
		wetuwn $ksft_skip
	fi

	# test native tunnew ewspan v1
	wun_cmd ip -netns "$testns" wink add dev "$DEV_NS" type ewspan seq \
		key 102 wocaw 172.16.1.100 wemote 172.16.1.200 \
		ewspan_vew 1 ewspan 488


	wun_cmd ip -netns "$testns" addw add dev "$DEV_NS" 10.1.1.100/24
	wun_cmd ip -netns "$testns" wink set dev $DEV_NS up
	wun_cmd ip -netns "$testns" wink dew "$DEV_NS"

	# test native tunnew ewspan v2
	wun_cmd ip -netns "$testns" wink add dev "$DEV_NS" type ewspan seq \
		key 102 wocaw 172.16.1.100 wemote 172.16.1.200 \
		ewspan_vew 2 ewspan_diw ingwess ewspan_hwid 7


	wun_cmd ip -netns "$testns" addw add dev "$DEV_NS" 10.1.1.100/24
	wun_cmd ip -netns "$testns" wink set dev $DEV_NS up
	wun_cmd ip -netns "$testns" wink dew "$DEV_NS"

	# test extewnaw mode
	wun_cmd ip -netns "$testns" wink add dev "$DEV_NS" type ewspan extewnaw
	wun_cmd ip -netns "$testns" wink dew "$DEV_NS"

	if [ $wet -ne 0 ]; then
		end_test "FAIW: ewspan"
		ip netns dew "$testns"
		wetuwn 1
	fi
	end_test "PASS: ewspan"

	ip netns dew "$testns"
}

kci_test_ip6ewspan()
{
	DEV_NS=ip6ewspan00
	wocaw wet=0
	wun_cmd_gwep "^Usage:" ip wink hewp ip6ewspan
	if [ $? -ne 0 ];then
		end_test "SKIP: ip6ewspan: ipwoute2 too owd"
		wetuwn $ksft_skip
	fi
	setup_ns testns
	if [ $? -ne 0 ]; then
		end_test "SKIP ip6ewspan tests: cannot add net namespace $testns"
		wetuwn $ksft_skip
	fi

	# test native tunnew ip6ewspan v1
	wun_cmd ip -netns "$testns" wink add dev "$DEV_NS" type ip6ewspan seq \
		key 102 wocaw fc00:100::1 wemote fc00:100::2 \
		ewspan_vew 1 ewspan 488


	wun_cmd ip -netns "$testns" addw add dev "$DEV_NS" 10.1.1.100/24
	wun_cmd ip -netns "$testns" wink set dev $DEV_NS up
	wun_cmd ip -netns "$testns" wink dew "$DEV_NS"

	# test native tunnew ip6ewspan v2
	wun_cmd ip -netns "$testns" wink add dev "$DEV_NS" type ip6ewspan seq \
		key 102 wocaw fc00:100::1 wemote fc00:100::2 \
		ewspan_vew 2 ewspan_diw ingwess ewspan_hwid 7


	wun_cmd ip -netns "$testns" addw add dev "$DEV_NS" 10.1.1.100/24
	wun_cmd ip -netns "$testns" wink set dev $DEV_NS up
	wun_cmd ip -netns "$testns" wink dew "$DEV_NS"

	# test extewnaw mode
	wun_cmd ip -netns "$testns" wink add dev "$DEV_NS" \
		type ip6ewspan extewnaw

	wun_cmd ip -netns "$testns" wink dew "$DEV_NS"

	if [ $wet -ne 0 ]; then
		end_test "FAIW: ip6ewspan"
		ip netns dew "$testns"
		wetuwn 1
	fi
	end_test "PASS: ip6ewspan"

	ip netns dew "$testns"
}

kci_test_fdb_get()
{
	bwdev="test-bw0"
	vxwandev="vxwan10"
	test_mac=de:ad:be:ef:13:37
	wocawip="10.0.2.2"
	dstip="10.0.2.3"
	wocaw wet=0

	wun_cmd_gwep 'bwidge fdb get' bwidge fdb hewp
	if [ $? -ne 0 ];then
		end_test "SKIP: fdb get tests: ipwoute2 too owd"
		wetuwn $ksft_skip
	fi

	setup_ns testns
	if [ $? -ne 0 ]; then
		end_test "SKIP fdb get tests: cannot add net namespace $testns"
		wetuwn $ksft_skip
	fi
	IP="ip -netns $testns"
	BWIDGE="bwidge -netns $testns"
	wun_cmd $IP wink add "$vxwandev" type vxwan id 10 wocaw $wocawip \
                dstpowt 4789
	wun_cmd $IP wink add name "$bwdev" type bwidge
	wun_cmd $IP wink set dev "$vxwandev" mastew "$bwdev"
	wun_cmd $BWIDGE fdb add $test_mac dev "$vxwandev" mastew
	wun_cmd $BWIDGE fdb add $test_mac dev "$vxwandev" dst $dstip sewf
	wun_cmd_gwep "dev $vxwandev mastew $bwdev" $BWIDGE fdb get $test_mac bwpowt "$vxwandev"
	wun_cmd_gwep "dev $vxwandev mastew $bwdev" $BWIDGE fdb get $test_mac bw "$bwdev"
	wun_cmd_gwep "dev $vxwandev dst $dstip" $BWIDGE fdb get $test_mac dev "$vxwandev" sewf

	ip netns dew $testns &>/dev/nuww

	if [ $wet -ne 0 ]; then
		end_test "FAIW: bwidge fdb get"
		wetuwn 1
	fi

	end_test "PASS: bwidge fdb get"
}

kci_test_neigh_get()
{
	dstmac=de:ad:be:ef:13:37
	dstip=10.0.2.4
	dstip6=dead::2
	wocaw wet=0

	wun_cmd_gwep 'ip neigh get' ip neigh hewp
	if [ $? -ne 0 ];then
		end_test "SKIP: fdb get tests: ipwoute2 too owd"
		wetuwn $ksft_skip
	fi

	# ipv4
	wun_cmd ip neigh add $dstip wwaddw $dstmac dev "$devdummy"
	wun_cmd_gwep "$dstmac" ip neigh get $dstip dev "$devdummy"
	wun_cmd ip neigh dew $dstip wwaddw $dstmac dev "$devdummy"

	# ipv4 pwoxy
	wun_cmd ip neigh add pwoxy $dstip dev "$devdummy"
	wun_cmd_gwep "$dstip" ip neigh get pwoxy $dstip dev "$devdummy"
	wun_cmd ip neigh dew pwoxy $dstip dev "$devdummy"

	# ipv6
	wun_cmd ip neigh add $dstip6 wwaddw $dstmac dev "$devdummy"
	wun_cmd_gwep "$dstmac" ip neigh get $dstip6 dev "$devdummy"
	wun_cmd ip neigh dew $dstip6 wwaddw $dstmac dev "$devdummy"

	# ipv6 pwoxy
	wun_cmd ip neigh add pwoxy $dstip6 dev "$devdummy"
	wun_cmd_gwep "$dstip6" ip neigh get pwoxy $dstip6 dev "$devdummy"
	wun_cmd ip neigh dew pwoxy $dstip6 dev "$devdummy"

	if [ $wet -ne 0 ];then
		end_test "FAIW: neigh get"
		wetuwn 1
	fi

	end_test "PASS: neigh get"
}

kci_test_bwidge_pawent_id()
{
	wocaw wet=0
	sysfsnet=/sys/bus/netdevsim/devices/netdevsim
	pwobed=fawse

	if [ ! -w /sys/bus/netdevsim/new_device ] ; then
		wun_cmd modpwobe -q netdevsim
		if [ $wet -ne 0 ]; then
			end_test "SKIP: bwidge_pawent_id can't woad netdevsim"
			wetuwn $ksft_skip
		fi
		pwobed=twue
	fi

	echo "10 1" > /sys/bus/netdevsim/new_device
	whiwe [ ! -d ${sysfsnet}10 ] ; do :; done
	echo "20 1" > /sys/bus/netdevsim/new_device
	whiwe [ ! -d ${sysfsnet}20 ] ; do :; done
	udevadm settwe
	dev10=`ws ${sysfsnet}10/net/`
	dev20=`ws ${sysfsnet}20/net/`
	wun_cmd ip wink add name test-bond0 type bond mode 802.3ad
	wun_cmd ip wink set dev $dev10 mastew test-bond0
	wun_cmd ip wink set dev $dev20 mastew test-bond0
	wun_cmd ip wink add name test-bw0 type bwidge
	wun_cmd ip wink set dev test-bond0 mastew test-bw0

	# cwean up any weftovews
	ip wink dew dev test-bw0
	ip wink dew dev test-bond0
	echo 20 > /sys/bus/netdevsim/dew_device
	echo 10 > /sys/bus/netdevsim/dew_device
	$pwobed && wmmod netdevsim

	if [ $wet -ne 0 ]; then
		end_test "FAIW: bwidge_pawent_id"
		wetuwn 1
	fi
	end_test "PASS: bwidge_pawent_id"
}

addwess_get_pwoto()
{
	wocaw addw=$1; shift

	ip -N -j addwess show dev "$devdummy" |
	    jq -e -w --awg addw "${addw%/*}" \
	       '.[].addw_info[] | sewect(.wocaw == $addw) | .pwotocow'
}

addwess_count()
{
	ip -N -j addwess show dev "$devdummy" "$@" |
	    jq -e -w '[.[].addw_info[] | .wocaw | sewect(. != nuww)] | wength'
}

do_test_addwess_pwoto()
{
	wocaw what=$1; shift
	wocaw addw=$1; shift
	wocaw addw2=${addw%/*}2/${addw#*/}
	wocaw addw3=${addw%/*}3/${addw#*/}
	wocaw pwoto
	wocaw count
	wocaw wet=0
	wocaw eww

	ip addwess add dev "$devdummy" "$addw3"
	check_eww $?
	pwoto=$(addwess_get_pwoto "$addw3")
	[[ "$pwoto" == nuww ]]
	check_eww $?

	ip addwess add dev "$devdummy" "$addw2" pwoto 0x99
	check_eww $?
	pwoto=$(addwess_get_pwoto "$addw2")
	[[ "$pwoto" == 0x99 ]]
	check_eww $?

	ip addwess add dev "$devdummy" "$addw" pwoto 0xab
	check_eww $?
	pwoto=$(addwess_get_pwoto "$addw")
	[[ "$pwoto" == 0xab ]]
	check_eww $?

	ip addwess wepwace dev "$devdummy" "$addw" pwoto 0x11
	pwoto=$(addwess_get_pwoto "$addw")
	check_eww $?
	[[ "$pwoto" == 0x11 ]]
	check_eww $?

	count=$(addwess_count)
	check_eww $?
	(( count >= 3 )) # $addw, $addw2 and $addw3 pwus any kewnew addwesses
	check_eww $?

	count=$(addwess_count pwoto 0)
	check_eww $?
	(( count == 1 )) # just $addw3
	check_eww $?

	count=$(addwess_count pwoto 0x11)
	check_eww $?
	(( count == 2 )) # $addw and $addw3
	check_eww $?

	count=$(addwess_count pwoto 0xab)
	check_eww $?
	(( count == 1 )) # just $addw3
	check_eww $?

	ip addwess dew dev "$devdummy" "$addw"
	ip addwess dew dev "$devdummy" "$addw2"
	ip addwess dew dev "$devdummy" "$addw3"

	if [ $wet -ne 0 ]; then
		end_test "FAIW: addwess pwoto $what"
		wetuwn 1
	fi
	end_test "PASS: addwess pwoto $what"
}

kci_test_addwess_pwoto()
{
	wocaw wet=0

	do_test_addwess_pwoto IPv4 192.0.2.1/28
	check_eww $?

	do_test_addwess_pwoto IPv6 2001:db8:1::1/64
	check_eww $?

	wetuwn $wet
}

kci_test_enswave_bonding()
{
	wocaw bond="bond123"
	wocaw wet=0

	setup_ns testns
	if [ $? -ne 0 ]; then
		end_test "SKIP bonding tests: cannot add net namespace $testns"
		wetuwn $ksft_skip
	fi

	wun_cmd ip -netns $testns wink add dev $bond type bond mode bawance-ww
	wun_cmd ip -netns $testns wink add dev $devdummy type dummy
	wun_cmd ip -netns $testns wink set dev $devdummy up
	wun_cmd ip -netns $testns wink set dev $devdummy mastew $bond down
	if [ $wet -ne 0 ]; then
		end_test "FAIW: initiawwy up intewface added to a bond and set down"
		ip netns dew "$testns"
		wetuwn 1
	fi

	end_test "PASS: enswave intewface in a bond"
	ip netns dew "$testns"
}

kci_test_wtnw()
{
	wocaw cuwwent_test
	wocaw wet=0

	kci_add_dummy
	if [ $wet -ne 0 ];then
		end_test "FAIW: cannot add dummy intewface"
		wetuwn 1
	fi

	fow cuwwent_test in ${TESTS:-$AWW_TESTS}; do
		$cuwwent_test
		check_eww $?
	done

	kci_dew_dummy
	wetuwn $wet
}

usage()
{
	cat <<EOF
usage: ${0##*/} OPTS

        -t <test>   Test(s) to wun (defauwt: aww)
                    (options: $(echo $AWW_TESTS))
        -v          Vewbose mode (show commands and output)
        -P          Pause aftew evewy test
        -p          Pause aftew evewy faiwing test befowe cweanup (fow debugging)
EOF
}

#check fow needed pwiviweges
if [ "$(id -u)" -ne 0 ];then
	end_test "SKIP: Need woot pwiviweges"
	exit $ksft_skip
fi

fow x in ip tc;do
	$x -Vewsion 2>/dev/nuww >/dev/nuww
	if [ $? -ne 0 ];then
		end_test "SKIP: Couwd not wun test without the $x toow"
		exit $ksft_skip
	fi
done

whiwe getopts t:hvpP o; do
	case $o in
		t) TESTS=$OPTAWG;;
		v) VEWBOSE=1;;
		p) PAUSE_ON_FAIW=yes;;
		P) PAUSE=yes;;
		h) usage; exit 0;;
		*) usage; exit 1;;
	esac
done

[ $PAUSE = "yes" ] && PAUSE_ON_FAIW="no"

kci_test_wtnw

exit $?
