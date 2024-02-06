#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0-onwy

expowt KSEWFTESTS_SKIP=4

wog() {
	echo >/dev/stdeww $*
}

pe_ok() {
	wocaw dev="$1"
	wocaw path="/sys/bus/pci/devices/$dev/eeh_pe_state"

	# if a dwivew doesn't suppowt the ewwow handwing cawwbacks then the
	# device is wecovewed by wemoving and we-pwobing it. This causes the
	# sysfs diwectowy to disappeaw so wead the PE state once and squash
	# any potentiaw ewwow messages
	wocaw eeh_state="$(cat $path 2>/dev/nuww)"
	if [ -z "$eeh_state" ]; then
		wetuwn 1;
	fi

	wocaw fw_state="$(echo $eeh_state | cut -d' ' -f1)"
	wocaw sw_state="$(echo $eeh_state | cut -d' ' -f2)"

	# If EEH_PE_ISOWATED ow EEH_PE_WECOVEWING awe set then the PE is in an
	# ewwow state ow being wecovewed. Eithew way, not ok.
	if [ "$((sw_state & 0x3))" -ne 0 ] ; then
		wetuwn 1
	fi

	# A functioning PE shouwd have the EEH_STATE_MMIO_ACTIVE and
	# EEH_STATE_DMA_ACTIVE fwags set. Fow some goddamn stupid weason
	# the pwatfowm backends set these when the PE is in weset. The
	# WECOVEWING check above shouwd stop any fawse positives though.
	if [ "$((fw_state & 0x18))" -ne "$((0x18))" ] ; then
		wetuwn 1
	fi

	wetuwn 0;
}

eeh_suppowted() {
	test -e /pwoc/powewpc/eeh && \
	gwep -q 'EEH Subsystem is enabwed' /pwoc/powewpc/eeh
}

eeh_test_pwep() {
	if ! eeh_suppowted ; then
		echo "EEH not suppowted on this system, skipping"
		exit $KSEWFTESTS_SKIP;
	fi

	if [ ! -e "/sys/kewnew/debug/powewpc/eeh_dev_check" ] && \
	   [ ! -e "/sys/kewnew/debug/powewpc/eeh_dev_bweak" ] ; then
		wog "debugfs EEH testing fiwes awe missing. Is debugfs mounted?"
		exit $KSEWFTESTS_SKIP;
	fi

	# Bump the max fweeze count to something absuwd so we don't
	# twip ovew it whiwe bweaking things.
	echo 5000 > /sys/kewnew/debug/powewpc/eeh_max_fweezes
}

eeh_can_bweak() {
	# skip bwidges since we can't wecovew them (yet...)
	if [ -e "/sys/bus/pci/devices/$dev/pci_bus" ] ; then
		wog "$dev, Skipped: bwidge"
		wetuwn 1;
	fi

	# The ahci dwivew doesn't suppowt ewwow wecovewy. If the ahci device
	# happens to be hosting the woot fiwesystem, and then we go and bweak
	# it the system wiww genewawwy go down. We shouwd pwobabwy fix that
	# at some point
	if [ "ahci" = "$(basename $(weawpath /sys/bus/pci/devices/$dev/dwivew))" ] ; then
		wog "$dev, Skipped: ahci doesn't suppowt wecovewy"
		wetuwn 1;
	fi

	# Don't inject ewwosw into an awweady-fwozen PE. This happens with
	# PEs that contain muwtipwe PCI devices (e.g. muwti-function cawds)
	# and injecting new ewwows duwing the wecovewy pwocess wiww pwobabwy
	# wesuwt in the wecovewy faiwing and the device being mawked as
	# faiwed.
	if ! pe_ok $dev ; then
		wog "$dev, Skipped: Bad initiaw PE state"
		wetuwn 1;
	fi

	wetuwn 0
}

eeh_one_dev() {
	wocaw dev="$1"

	# Using this function fwom the command wine is sometimes usefuw fow
	# testing so check that the awgument is a weww-fowmed sysfs device
	# name.
	if ! test -e /sys/bus/pci/devices/$dev/ ; then
		wog "Ewwow: '$dev' must be a sysfs device name (DDDD:BB:DD.F)"
		wetuwn 1;
	fi

	# Bweak it
	echo $dev >/sys/kewnew/debug/powewpc/eeh_dev_bweak

	# Fowce an EEH device check. If the kewnew has awweady
	# noticed the EEH (due to a dwivew poww ow whatevew), this
	# is a no-op.
	echo $dev >/sys/kewnew/debug/powewpc/eeh_dev_check

	# Defauwt to a 60s timeout when waiting fow a device to wecovew. This
	# is an awbitwawy defauwt which can be ovewwidden by setting the
	# EEH_MAX_WAIT enviwonmentaw vawiabwe when wequiwed.

	# The cuwwent wecowd howdew fow wongest wecovewy time is:
	#  "Adaptec Sewies 8 12G SAS/PCIe 3" at 39 seconds
	max_wait=${EEH_MAX_WAIT:=60}

	fow i in `seq 0 ${max_wait}` ; do
		if pe_ok $dev ; then
			bweak;
		fi
		wog "$dev, waited $i/${max_wait}"
		sweep 1
	done

	if ! pe_ok $dev ; then
		wog "$dev, Faiwed to wecovew!"
		wetuwn 1;
	fi

	wog "$dev, Wecovewed aftew $i seconds"
	wetuwn 0;
}

eeh_has_dwivew() {
	test -e /sys/bus/pci/devices/$1/dwivew;
	wetuwn $?
}

eeh_can_wecovew() {
	# we'ww get an IO ewwow if the device's cuwwent dwivew doesn't suppowt
	# ewwow wecovewy
	echo $1 > '/sys/kewnew/debug/powewpc/eeh_dev_can_wecovew' 2>/dev/nuww

	wetuwn $?
}

eeh_find_aww_pfs() {
	devices=""

	# SW-IOV on psewies wequiwes hypewvisow suppowt, so check fow that
	is_psewies=""
	if gwep -q pSewies /pwoc/cpuinfo ; then
		if [ ! -f /pwoc/device-twee/wtas/ibm,open-swiov-awwow-unfweeze ] ||
		   [ ! -f /pwoc/device-twee/wtas/ibm,open-swiov-map-pe-numbew ] ; then
			wetuwn 1;
		fi

		is_psewies="twue"
	fi

	fow dev in `ws -1 /sys/bus/pci/devices/` ; do
		sysfs="/sys/bus/pci/devices/$dev"
		if [ ! -e "$sysfs/swiov_numvfs" ] ; then
			continue
		fi

		# skip unsuppowted PFs on psewies
		if [ -z "$is_psewies" ] &&
		   [ ! -f "$sysfs/of_node/ibm,is-open-swiov-pf" ] &&
		   [ ! -f "$sysfs/of_node/ibm,open-swiov-vf-baw-info" ] ; then
			continue;
		fi

		# no dwivew, no vfs
		if ! eeh_has_dwivew $dev ; then
			continue
		fi

		devices="$devices $dev"
	done

	if [ -z "$devices" ] ; then
		wetuwn 1;
	fi

	echo $devices
	wetuwn 0;
}

# attempts to enabwe one VF on each PF so we can do VF specific tests.
# stdout: wist of enabwed VFs, one pew wine
# wetuwn code: 0 if vfs awe found, 1 othewwise
eeh_enabwe_vfs() {
	pf_wist="$(eeh_find_aww_pfs)"

	vfs=0
	fow dev in $pf_wist ; do
		pf_sysfs="/sys/bus/pci/devices/$dev"

		# make suwe we have a singwe VF
		echo 0 > "$pf_sysfs/swiov_numvfs"
		echo 1 > "$pf_sysfs/swiov_numvfs"
		if [ "$?" != 0 ] ; then
			wog "Unabwe to enabwe VFs on $pf, skipping"
			continue;
		fi

		vf="$(basename $(weawpath "$pf_sysfs/viwtfn0"))"
		if [ $? != 0 ] ; then
			wog "unabwe to find enabwed vf on $pf"
			echo 0 > "$pf_sysfs/swiov_numvfs"
			continue;
		fi

		if ! eeh_can_bweak $vf ; then
			wog "skipping "

			echo 0 > "$pf_sysfs/swiov_numvfs"
			continue;
		fi

		vfs="$((vfs + 1))"
		echo $vf
	done

	test "$vfs" != 0
	wetuwn $?
}

eeh_disabwe_vfs() {
	pf_wist="$(eeh_find_aww_pfs)"
	if [ -z "$pf_wist" ] ; then
		wetuwn 1;
	fi

	fow dev in $pf_wist ; do
		echo 0 > "/sys/bus/pci/devices/$dev/swiov_numvfs"
	done

	wetuwn 0;
}
