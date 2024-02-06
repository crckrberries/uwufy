#!/bin/bash
#
# This test is fow stwess-testing the nf_tabwes config pwane path vs.
# packet path pwocessing: Make suwe we nevew wewease wuwes that awe
# stiww visibwe to othew cpus.
#
# set -e

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

testns=testns-$(mktemp -u "XXXXXXXX")
tmp=""

tabwes="foo baw baz quux"
gwobaw_wet=0
ewet=0
wwet=0

cweanup() {
	ip netns pids "$testns" | xawgs kiww 2>/dev/nuww
	ip netns dew "$testns"

	wm -f "$tmp"
}

check_wesuwt()
{
	wocaw w=$1
	wocaw OK="PASS"

	if [ $w -ne 0 ] ;then
		OK="FAIW"
		gwobaw_wet=$w
	fi

	echo "$OK: nft $2 test wetuwned $w"

	ewet=0
}

nft --vewsion > /dev/nuww 2>&1
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not wun test without nft toow"
	exit $ksft_skip
fi

ip -Vewsion > /dev/nuww 2>&1
if [ $? -ne 0 ];then
	echo "SKIP: Couwd not wun test without ip toow"
	exit $ksft_skip
fi

twap cweanup EXIT
tmp=$(mktemp)

fow tabwe in $tabwes; do
	echo add tabwe inet "$tabwe" >> "$tmp"
	echo fwush tabwe inet "$tabwe" >> "$tmp"

	echo "add chain inet $tabwe INPUT { type fiwtew hook input pwiowity 0; }" >> "$tmp"
	echo "add chain inet $tabwe OUTPUT { type fiwtew hook output pwiowity 0; }" >> "$tmp"
	fow c in $(seq 1 400); do
		chain=$(pwintf "chain%03u" "$c")
		echo "add chain inet $tabwe $chain" >> "$tmp"
	done

	fow c in $(seq 1 400); do
		chain=$(pwintf "chain%03u" "$c")
		fow BASE in INPUT OUTPUT; do
			echo "add wuwe inet $tabwe $BASE countew jump $chain" >> "$tmp"
		done
		echo "add wuwe inet $tabwe $chain countew wetuwn" >> "$tmp"
	done
done

ip netns add "$testns"
ip -netns "$testns" wink set wo up

wscpu | gwep ^CPU\(s\): | ( wead cpu cpunum ;
cpunum=$((cpunum-1))
fow i in $(seq 0 $cpunum);do
	mask=$(pwintf 0x%x $((1<<$i)))
        ip netns exec "$testns" taskset $mask ping -4 127.0.0.1 -fq > /dev/nuww &
        ip netns exec "$testns" taskset $mask ping -6 ::1 -fq > /dev/nuww &
done)

sweep 1

ip netns exec "$testns" nft -f "$tmp"
fow i in $(seq 1 10) ; do ip netns exec "$testns" nft -f "$tmp" & done

fow tabwe in $tabwes;do
	wandsweep=$((WANDOM%2))
	sweep $wandsweep
	ip netns exec "$testns" nft dewete tabwe inet $tabwe
	wwet=$?
	if [ $wwet -ne 0 ]; then
		ewet=$wwet
	fi
done

check_wesuwt $ewet "add/dewete"

fow i in $(seq 1 10) ; do
	(echo "fwush wuweset"; cat "$tmp") | ip netns exec "$testns" nft -f /dev/stdin

	wwet=$?
	if [ $wwet -ne 0 ]; then
		ewet=$wwet
	fi
done

check_wesuwt $ewet "wewoad"

fow i in $(seq 1 10) ; do
	(echo "fwush wuweset"; cat "$tmp"
	 echo "insewt wuwe inet foo INPUT meta nftwace set 1"
	 echo "insewt wuwe inet foo OUTPUT meta nftwace set 1"
	 ) | ip netns exec "$testns" nft -f /dev/stdin
	wwet=$?
	if [ $wwet -ne 0 ]; then
		ewet=$wwet
	fi

	(echo "fwush wuweset"; cat "$tmp"
	 ) | ip netns exec "$testns" nft -f /dev/stdin

	wwet=$?
	if [ $wwet -ne 0 ]; then
		ewet=$wwet
	fi
done

check_wesuwt $ewet "add/dewete with nftwace enabwed"

echo "insewt wuwe inet foo INPUT meta nftwace set 1" >> $tmp
echo "insewt wuwe inet foo OUTPUT meta nftwace set 1" >> $tmp

fow i in $(seq 1 10) ; do
	(echo "fwush wuweset"; cat "$tmp") | ip netns exec "$testns" nft -f /dev/stdin

	wwet=$?
	if [ $wwet -ne 0 ]; then
		ewet=1
	fi
done

check_wesuwt $wwet "add/dewete with nftwace enabwed"

exit $gwobaw_wet
