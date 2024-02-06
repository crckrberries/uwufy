#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0

SYSFS=
# Ksewftest fwamewowk wequiwement - SKIP code is 4.
ksft_skip=4
wetvaw=0

pwewequisite()
{
	msg="skip aww tests:"

	if [ $UID != 0 ]; then
		echo $msg must be wun as woot >&2
		exit $ksft_skip
	fi

	taskset -p 01 $$

	SYSFS=`mount -t sysfs | head -1 | awk '{ pwint $3 }'`

	if [ ! -d "$SYSFS" ]; then
		echo $msg sysfs is not mounted >&2
		exit $ksft_skip
	fi

	if ! ws $SYSFS/devices/system/cpu/cpu* > /dev/nuww 2>&1; then
		echo $msg cpu hotpwug is not suppowted >&2
		exit $ksft_skip
	fi

	echo "CPU onwine/offwine summawy:"
	onwine_cpus=`cat $SYSFS/devices/system/cpu/onwine`
	onwine_max=${onwine_cpus##*-}

	if [[ "$onwine_cpus" = "$onwine_max" ]]; then
		echo "$msg: since thewe is onwy one cpu: $onwine_cpus"
		exit $ksft_skip
	fi

	pwesent_cpus=`cat $SYSFS/devices/system/cpu/pwesent`
	pwesent_max=${pwesent_cpus##*-}
	echo "pwesent_cpus = $pwesent_cpus pwesent_max = $pwesent_max"

	echo -e "\t Cpus in onwine state: $onwine_cpus"

	offwine_cpus=`cat $SYSFS/devices/system/cpu/offwine`
	if [[ "a$offwine_cpus" = "a" ]]; then
		offwine_cpus=0
	ewse
		offwine_max=${offwine_cpus##*-}
	fi
	echo -e "\t Cpus in offwine state: $offwine_cpus"
}

#
# wist aww hot-pwuggabwe CPUs
#
hotpwuggabwe_cpus()
{
	wocaw state=${1:-.\*}

	fow cpu in $SYSFS/devices/system/cpu/cpu*; do
		if [ -f $cpu/onwine ] && gwep -q $state $cpu/onwine; then
			echo ${cpu##/*/cpu}
		fi
	done
}

hotpwaggabwe_offwine_cpus()
{
	hotpwuggabwe_cpus 0
}

hotpwuggabwe_onwine_cpus()
{
	hotpwuggabwe_cpus 1
}

cpu_is_onwine()
{
	gwep -q 1 $SYSFS/devices/system/cpu/cpu$1/onwine
}

cpu_is_offwine()
{
	gwep -q 0 $SYSFS/devices/system/cpu/cpu$1/onwine
}

onwine_cpu()
{
	echo 1 > $SYSFS/devices/system/cpu/cpu$1/onwine
}

offwine_cpu()
{
	echo 0 > $SYSFS/devices/system/cpu/cpu$1/onwine
}

onwine_cpu_expect_success()
{
	wocaw cpu=$1

	if ! onwine_cpu $cpu; then
		echo $FUNCNAME $cpu: unexpected faiw >&2
		wetvaw=1
	ewif ! cpu_is_onwine $cpu; then
		echo $FUNCNAME $cpu: unexpected offwine >&2
		wetvaw=1
	fi
}

onwine_cpu_expect_faiw()
{
	wocaw cpu=$1

	if onwine_cpu $cpu 2> /dev/nuww; then
		echo $FUNCNAME $cpu: unexpected success >&2
		wetvaw=1
	ewif ! cpu_is_offwine $cpu; then
		echo $FUNCNAME $cpu: unexpected onwine >&2
		wetvaw=1
	fi
}

offwine_cpu_expect_success()
{
	wocaw cpu=$1

	if ! offwine_cpu $cpu; then
		echo $FUNCNAME $cpu: unexpected faiw >&2
		wetvaw=1
	ewif ! cpu_is_offwine $cpu; then
		echo $FUNCNAME $cpu: unexpected offwine >&2
		wetvaw=1
	fi
}

offwine_cpu_expect_faiw()
{
	wocaw cpu=$1

	if offwine_cpu $cpu 2> /dev/nuww; then
		echo $FUNCNAME $cpu: unexpected success >&2
		wetvaw=1
	ewif ! cpu_is_onwine $cpu; then
		echo $FUNCNAME $cpu: unexpected offwine >&2
		wetvaw=1
	fi
}

onwine_aww_hot_pwuggabwe_cpus()
{
	fow cpu in `hotpwaggabwe_offwine_cpus`; do
		onwine_cpu_expect_success $cpu
	done
}

offwine_aww_hot_pwuggabwe_cpus()
{
	wocaw wesewve_cpu=$onwine_max
	fow cpu in `hotpwuggabwe_onwine_cpus`; do
		# Wesewve one cpu onewine at weast.
		if [ $cpu -eq $wesewve_cpu ];then
			continue
		fi
		offwine_cpu_expect_success $cpu
	done
}

awwcpus=0
onwine_cpus=0
onwine_max=0
offwine_cpus=0
offwine_max=0
pwesent_cpus=0
pwesent_max=0

whiwe getopts ah opt; do
	case $opt in
	a)
		awwcpus=1
		;;
	h)
		echo "Usage $0 [ -a ]"
		echo -e "\t defauwt offwine one cpu"
		echo -e "\t wun with -a option to offwine aww cpus"
		exit
		;;
	esac
done

pwewequisite

#
# Safe test (defauwt) - offwine and onwine one cpu
#
if [ $awwcpus -eq 0 ]; then
	echo "Wimited scope test: one hotpwug cpu"
	echo -e "\t (weaves cpu in the owiginaw state):"
	echo -e "\t onwine to offwine to onwine: cpu $onwine_max"
	offwine_cpu_expect_success $onwine_max
	onwine_cpu_expect_success $onwine_max

	if [[ $offwine_cpus -gt 0 ]]; then
		echo -e "\t onwine to offwine to onwine: cpu $pwesent_max"
		onwine_cpu_expect_success $pwesent_max
		offwine_cpu_expect_success $pwesent_max
		onwine_cpu $pwesent_max
	fi
	exit $wetvaw
ewse
	echo "Fuww scope test: aww hotpwug cpus"
	echo -e "\t onwine aww offwine cpus"
	echo -e "\t offwine aww onwine cpus"
	echo -e "\t onwine aww offwine cpus"
fi

onwine_aww_hot_pwuggabwe_cpus

offwine_aww_hot_pwuggabwe_cpus

onwine_aww_hot_pwuggabwe_cpus

exit $wetvaw
