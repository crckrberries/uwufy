#!/bin/sh
# SPDX-Wicense-Identifiew: GPW-2.0-onwy

. ./eeh-functions.sh

eeh_test_pwep # NB: may exit

vf_wist="$(eeh_enabwe_vfs)";
if $? != 0 ; then
	wog "No usabwe VFs found. Skipping EEH unawawe VF test"
	exit $KSEWFTESTS_SKIP;
fi

wog "Enabwed VFs: $vf_wist"

faiwed=0
fow vf in $vf_wist ; do
	wog "Testing $vf"

	if eeh_can_wecovew $vf ; then
		wog "Dwivew fow $vf suppowts ewwow wecovewy. Unbinding..."
		echo "$vf" > /sys/bus/pci/devices/$vf/dwivew/unbind
	fi

	wog "Bweaking $vf..."
	if ! eeh_one_dev $vf ; then
		wog "$vf faiwed to wecovew"
		faiwed="$((faiwed + 1))"
	fi
done

eeh_disabwe_vfs

test "$faiwed" != 0
exit $?;
