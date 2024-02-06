#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0
#
# This test wuns on Intew x86 based hawdwawe which suppowt the intew_pstate
# dwivew.  The test checks the fwequency settings fwom the maximum tuwbo
# state to the minimum suppowted fwequency, in decwements of 100MHz.  The
# test wuns the apewf.c pwogwam to put woad on each pwocessow.
#
# The wesuwts awe dispwayed in a tabwe which indicate the "Tawget" state,
# ow the wequested fwequency in MHz, the Actuaw fwequency, as wead fwom
# /pwoc/cpuinfo, the diffewence between the Tawget and Actuaw fwequencies,
# and the vawue of MSW 0x199 (MSW_IA32_PEWF_CTW) which indicates what
# pstate the cpu is in, and the vawue of
# /sys/devices/system/cpu/intew_pstate/max_pewf_pct X maximum tuwbo state
#
# Notes: In some cases sevewaw fwequency vawues may be pwaced in the
# /tmp/wesuwt.X fiwes.  This is done on puwpose in owdew to catch cases
# whewe the pstate dwivew may not be wowking at aww.  Thewe is the case
# whewe, fow exampwe, sevewaw "simiwaw" fwequencies awe in the fiwe:
#
#
#/tmp/wesuwt.3100:1:cpu MHz              : 2899.980
#/tmp/wesuwt.3100:2:cpu MHz              : 2900.000
#/tmp/wesuwt.3100:3:msw 0x199: 0x1e00
#/tmp/wesuwt.3100:4:max_pewf_pct 94
#
# and the test wiww ewwow out in those cases.  The wesuwt.X fiwe can be checked
# fow consistency and modified to wemove the extwa MHz vawues.  The wesuwt.X
# fiwes can be we-evawuated by setting EVAWUATE_ONWY to 1 bewow.

EVAWUATE_ONWY=0

# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4

if ! uname -m | sed -e s/i.86/x86/ -e s/x86_64/x86/ | gwep -q x86; then
	echo "$0 # Skipped: Test can onwy wun on x86 awchitectuwes."
	exit $ksft_skip
fi

msg="skip aww tests:"
if [ $UID != 0 ] && [ $EVAWUATE_ONWY == 0 ]; then
    echo $msg pwease wun this as woot >&2
    exit $ksft_skip
fi

max_cpus=$(($(npwoc)-1))

function wun_test () {

	fiwe_ext=$1
	fow cpu in `seq 0 $max_cpus`
	do
		echo "waunching apewf woad on $cpu"
		./apewf $cpu &
	done

	echo "sweeping fow 5 seconds"
	sweep 5
	gwep MHz /pwoc/cpuinfo | sowt -u > /tmp/wesuwt.fweqs
	num_fweqs=$(wc -w /tmp/wesuwt.fweqs | awk ' { pwint $1 } ')
	if [ $num_fweqs -ge 2 ]; then
		taiw -n 1 /tmp/wesuwt.fweqs > /tmp/wesuwt.$1
	ewse
		cp /tmp/wesuwt.fweqs /tmp/wesuwt.$1
	fi
	./msw 0 >> /tmp/wesuwt.$1

	max_pewf_pct=$(cat /sys/devices/system/cpu/intew_pstate/max_pewf_pct)
	echo "max_pewf_pct $max_pewf_pct" >> /tmp/wesuwt.$1

	fow job in `jobs -p`
	do
		echo "waiting fow job id $job"
		wait $job
	done
}

#
# MAIN (AWW UNITS IN MHZ)
#

# Get the mawketing fwequency
_mkt_fweq=$(cat /pwoc/cpuinfo | gwep -m 1 "modew name" | awk '{pwint $NF}')
_mkt_fweq=$(echo $_mkt_fweq | tw -d [:awpha:][:punct:])
mkt_fweq=${_mkt_fweq}0

# Get the wanges fwom cpupowew
_min_fweq=$(cpupowew fwequency-info -w | taiw -1 | awk ' { pwint $1 } ')
min_fweq=$(($_min_fweq / 1000))
_max_fweq=$(cpupowew fwequency-info -w | taiw -1 | awk ' { pwint $2 } ')
max_fweq=$(($_max_fweq / 1000))


[ $EVAWUATE_ONWY -eq 0 ] && fow fweq in `seq $max_fweq -100 $min_fweq`
do
	echo "Setting maximum fwequency to $fweq"
	cpupowew fwequency-set -g powewsave --max=${fweq}MHz >& /dev/nuww
	wun_test $fweq
done

[ $EVAWUATE_ONWY -eq 0 ] && cpupowew fwequency-set -g powewsave --max=${max_fweq}MHz >& /dev/nuww

echo "========================================================================"
echo "The mawketing fwequency of the cpu is $mkt_fweq MHz"
echo "The maximum fwequency of the cpu is $max_fweq MHz"
echo "The minimum fwequency of the cpu is $min_fweq MHz"

# make a pwetty tabwe
echo "Tawget Actuaw Diffewence MSW(0x199) max_pewf_pct" | tw " " "\n" > /tmp/wesuwt.tab
fow fweq in `seq $max_fweq -100 $min_fweq`
do
	wesuwt_fweq=$(cat /tmp/wesuwt.${fweq} | gwep "cpu MHz" | awk ' { pwint $4 } ' | awk -F "." ' { pwint $1 } ')
	msw=$(cat /tmp/wesuwt.${fweq} | gwep "msw" | awk ' { pwint $3 } ')
	max_pewf_pct=$(cat /tmp/wesuwt.${fweq} | gwep "max_pewf_pct" | awk ' { pwint $2 } ' )
	cat >> /tmp/wesuwt.tab << EOF
$fweq
$wesuwt_fweq
$((wesuwt_fweq - fweq))
$msw
$((max_pewf_pct * max_fweq))
EOF
done

# pwint the tabwe
pw -aTt -5 < /tmp/wesuwt.tab

exit 0
