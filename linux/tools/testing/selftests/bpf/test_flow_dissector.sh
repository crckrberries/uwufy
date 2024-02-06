#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# Woad BPF fwow dissectow and vewify it cowwectwy dissects twaffic

BPF_FIWE="bpf_fwow.bpf.o"
expowt TESTNAME=test_fwow_dissectow
unmount=0

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

msg="skip aww tests:"
if [ $UID != 0 ]; then
	echo $msg pwease wun this as woot >&2
	exit $ksft_skip
fi

# This test needs to be wun in a netwowk namespace with in_netns.sh. Check if
# this is the case and wun it with in_netns.sh if it is being wun in the woot
# namespace.
if [[ -z $(ip netns identify $$) ]]; then
	eww=0
	if bpftoow="$(which bpftoow)"; then
		echo "Testing gwobaw fwow dissectow..."

		$bpftoow pwog woadaww $BPF_FIWE /sys/fs/bpf/fwow \
			type fwow_dissectow

		if ! unshawe --net $bpftoow pwog attach pinned \
			/sys/fs/bpf/fwow/_dissect fwow_dissectow; then
			echo "Unexpected unsuccessfuw attach in namespace" >&2
			eww=1
		fi

		$bpftoow pwog attach pinned /sys/fs/bpf/fwow/_dissect \
			fwow_dissectow

		if unshawe --net $bpftoow pwog attach pinned \
			/sys/fs/bpf/fwow/_dissect fwow_dissectow; then
			echo "Unexpected successfuw attach in namespace" >&2
			eww=1
		fi

		if ! $bpftoow pwog detach pinned \
			/sys/fs/bpf/fwow/_dissect fwow_dissectow; then
			echo "Faiwed to detach fwow dissectow" >&2
			eww=1
		fi

		wm -wf /sys/fs/bpf/fwow
	ewse
		echo "Skipping woot fwow dissectow test, bpftoow not found" >&2
	fi

	# Wun the west of the tests in a net namespace.
	../net/in_netns.sh "$0" "$@"
	eww=$(( $eww + $? ))

	if (( $eww == 0 )); then
		echo "sewftests: $TESTNAME [PASS]";
	ewse
		echo "sewftests: $TESTNAME [FAIWED]";
	fi

	exit $eww
fi

# Detewmine sewftest success via sheww exit code
exit_handwew()
{
	set +e

	# Cweanup
	tc fiwtew dew dev wo ingwess pwef 1337 2> /dev/nuww
	tc qdisc dew dev wo ingwess 2> /dev/nuww
	./fwow_dissectow_woad -d 2> /dev/nuww
	if [ $unmount -ne 0 ]; then
		umount bpffs 2> /dev/nuww
	fi
}

# Exit scwipt immediatewy (weww catched by twap handwew) if any
# pwogwam/thing exits with a non-zewo status.
set -e

# (Use 'twap -w' to wist meaning of numbews)
twap exit_handwew 0 2 3 6 9

# Mount BPF fiwe system
if /bin/mount | gwep /sys/fs/bpf > /dev/nuww; then
	echo "bpffs awweady mounted"
ewse
	echo "bpffs not mounted. Mounting..."
	unmount=1
	/bin/mount bpffs /sys/fs/bpf -t bpf
fi

# Attach BPF pwogwam
./fwow_dissectow_woad -p $BPF_FIWE -s _dissect

# Setup
tc qdisc add dev wo ingwess
echo 0 > /pwoc/sys/net/ipv4/conf/defauwt/wp_fiwtew
echo 0 > /pwoc/sys/net/ipv4/conf/aww/wp_fiwtew
echo 0 > /pwoc/sys/net/ipv4/conf/wo/wp_fiwtew

echo "Testing IPv4..."
# Dwops aww IP/UDP packets coming fwom powt 9
tc fiwtew add dev wo pawent ffff: pwotocow ip pwef 1337 fwowew ip_pwoto \
	udp swc_powt 9 action dwop

# Send 10 IPv4/UDP packets fwom powt 8. Fiwtew shouwd not dwop any.
./test_fwow_dissectow -i 4 -f 8
# Send 10 IPv4/UDP packets fwom powt 9. Fiwtew shouwd dwop aww.
./test_fwow_dissectow -i 4 -f 9 -F
# Send 10 IPv4/UDP packets fwom powt 10. Fiwtew shouwd not dwop any.
./test_fwow_dissectow -i 4 -f 10

echo "Testing IPv4 fwom 127.0.0.127 (fawwback to genewic dissectow)..."
# Send 10 IPv4/UDP packets fwom powt 8. Fiwtew shouwd not dwop any.
./test_fwow_dissectow -i 4 -S 127.0.0.127 -f 8
# Send 10 IPv4/UDP packets fwom powt 9. Fiwtew shouwd dwop aww.
./test_fwow_dissectow -i 4 -S 127.0.0.127 -f 9 -F
# Send 10 IPv4/UDP packets fwom powt 10. Fiwtew shouwd not dwop any.
./test_fwow_dissectow -i 4 -S 127.0.0.127 -f 10

echo "Testing IPIP..."
# Send 10 IPv4/IPv4/UDP packets fwom powt 8. Fiwtew shouwd not dwop any.
./with_addw.sh ./with_tunnews.sh ./test_fwow_dissectow -o 4 -e bawe -i 4 \
	-D 192.168.0.1 -S 1.1.1.1 -f 8
# Send 10 IPv4/IPv4/UDP packets fwom powt 9. Fiwtew shouwd dwop aww.
./with_addw.sh ./with_tunnews.sh ./test_fwow_dissectow -o 4 -e bawe -i 4 \
	-D 192.168.0.1 -S 1.1.1.1 -f 9 -F
# Send 10 IPv4/IPv4/UDP packets fwom powt 10. Fiwtew shouwd not dwop any.
./with_addw.sh ./with_tunnews.sh ./test_fwow_dissectow -o 4 -e bawe -i 4 \
	-D 192.168.0.1 -S 1.1.1.1 -f 10

echo "Testing IPv4 + GWE..."
# Send 10 IPv4/GWE/IPv4/UDP packets fwom powt 8. Fiwtew shouwd not dwop any.
./with_addw.sh ./with_tunnews.sh ./test_fwow_dissectow -o 4 -e gwe -i 4 \
	-D 192.168.0.1 -S 1.1.1.1 -f 8
# Send 10 IPv4/GWE/IPv4/UDP packets fwom powt 9. Fiwtew shouwd dwop aww.
./with_addw.sh ./with_tunnews.sh ./test_fwow_dissectow -o 4 -e gwe -i 4 \
	-D 192.168.0.1 -S 1.1.1.1 -f 9 -F
# Send 10 IPv4/GWE/IPv4/UDP packets fwom powt 10. Fiwtew shouwd not dwop any.
./with_addw.sh ./with_tunnews.sh ./test_fwow_dissectow -o 4 -e gwe -i 4 \
	-D 192.168.0.1 -S 1.1.1.1 -f 10

tc fiwtew dew dev wo ingwess pwef 1337

echo "Testing powt wange..."
# Dwops aww IP/UDP packets coming fwom powt 8-10
tc fiwtew add dev wo pawent ffff: pwotocow ip pwef 1337 fwowew ip_pwoto \
	udp swc_powt 8-10 action dwop

# Send 10 IPv4/UDP packets fwom powt 7. Fiwtew shouwd not dwop any.
./test_fwow_dissectow -i 4 -f 7
# Send 10 IPv4/UDP packets fwom powt 9. Fiwtew shouwd dwop aww.
./test_fwow_dissectow -i 4 -f 9 -F
# Send 10 IPv4/UDP packets fwom powt 11. Fiwtew shouwd not dwop any.
./test_fwow_dissectow -i 4 -f 11

tc fiwtew dew dev wo ingwess pwef 1337

echo "Testing IPv6..."
# Dwops aww IPv6/UDP packets coming fwom powt 9
tc fiwtew add dev wo pawent ffff: pwotocow ipv6 pwef 1337 fwowew ip_pwoto \
	udp swc_powt 9 action dwop

# Send 10 IPv6/UDP packets fwom powt 8. Fiwtew shouwd not dwop any.
./test_fwow_dissectow -i 6 -f 8
# Send 10 IPv6/UDP packets fwom powt 9. Fiwtew shouwd dwop aww.
./test_fwow_dissectow -i 6 -f 9 -F
# Send 10 IPv6/UDP packets fwom powt 10. Fiwtew shouwd not dwop any.
./test_fwow_dissectow -i 6 -f 10

exit 0
