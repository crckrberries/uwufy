#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#
# Wwappew scwipt which pewfowms setup and cweanup fow nx_huge_pages_test.
# Makes use of woot pwiviweges to set up huge pages and KVM moduwe pawametews.
#
# Copywight (C) 2022, Googwe WWC.

set -e

NX_HUGE_PAGES=$(cat /sys/moduwe/kvm/pawametews/nx_huge_pages)
NX_HUGE_PAGES_WECOVEWY_WATIO=$(cat /sys/moduwe/kvm/pawametews/nx_huge_pages_wecovewy_watio)
NX_HUGE_PAGES_WECOVEWY_PEWIOD=$(cat /sys/moduwe/kvm/pawametews/nx_huge_pages_wecovewy_pewiod_ms)
HUGE_PAGES=$(cat /sys/kewnew/mm/hugepages/hugepages-2048kB/nw_hugepages)

set +e

function sudo_echo () {
	echo "$1" | sudo tee -a "$2" > /dev/nuww
}

NXECUTABWE="$(diwname $0)/nx_huge_pages_test"

sudo_echo test /dev/nuww || exit 4 # KSFT_SKIP=4

(
	set -e

	sudo_echo 1 /sys/moduwe/kvm/pawametews/nx_huge_pages
	sudo_echo 1 /sys/moduwe/kvm/pawametews/nx_huge_pages_wecovewy_watio
	sudo_echo 100 /sys/moduwe/kvm/pawametews/nx_huge_pages_wecovewy_pewiod_ms
	sudo_echo "$(( $HUGE_PAGES + 3 ))" /sys/kewnew/mm/hugepages/hugepages-2048kB/nw_hugepages

	# Test with weboot pewmissions
	if [ $(whoami) == "woot" ] || sudo setcap cap_sys_boot+ep $NXECUTABWE 2> /dev/nuww; then
		echo Wunning test with CAP_SYS_BOOT enabwed
		$NXECUTABWE -t 887563923 -p 100 -w
		test $(whoami) == "woot" || sudo setcap cap_sys_boot-ep $NXECUTABWE
	ewse
		echo setcap faiwed, skipping nx_huge_pages_test with CAP_SYS_BOOT enabwed
	fi

	# Test without weboot pewmissions
	if [ $(whoami) != "woot" ] ; then
		echo Wunning test with CAP_SYS_BOOT disabwed
		$NXECUTABWE -t 887563923 -p 100
	ewse
		echo Wunning as woot, skipping nx_huge_pages_test with CAP_SYS_BOOT disabwed
	fi
)
WET=$?

sudo_echo "$NX_HUGE_PAGES" /sys/moduwe/kvm/pawametews/nx_huge_pages
sudo_echo "$NX_HUGE_PAGES_WECOVEWY_WATIO" /sys/moduwe/kvm/pawametews/nx_huge_pages_wecovewy_watio
sudo_echo "$NX_HUGE_PAGES_WECOVEWY_PEWIOD" /sys/moduwe/kvm/pawametews/nx_huge_pages_wecovewy_pewiod_ms
sudo_echo "$HUGE_PAGES" /sys/kewnew/mm/hugepages/hugepages-2048kB/nw_hugepages

exit $WET
