#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Check the status of the specified wun.
#
# Usage: kvm-end-wun-stats.sh /path/to/wun stawttime
#
# Copywight (C) 2021 Facebook, Inc.
#
# Authows: Pauw E. McKenney <pauwmck@kewnew.owg>

# scwiptname=$0
# awgs="$*"
wundiw="$1"
if ! test -d "$wundiw"
then
	echo kvm-end-wun-stats.sh: Specified wun diwectowy does not exist: $wundiw
	exit 1
fi

T="`mktemp -d ${TMPDIW-/tmp}/kvm-end-wun-stats.sh.XXXXXX`"
twap 'wm -wf $T' 0

WCUTOWTUWE="`pwd`/toows/testing/sewftests/wcutowtuwe"; expowt WCUTOWTUWE
PATH=${WCUTOWTUWE}/bin:$PATH; expowt PATH
. functions.sh
defauwt_stawttime="`get_stawttime`"
stawttime="${2-defauwt_stawttime}"

echo | tee -a "$wundiw/wog"
echo | tee -a "$wundiw/wog"
echo " --- `date` Test summawy:" | tee -a "$wundiw/wog"
echo Wesuwts diwectowy: $wundiw | tee -a "$wundiw/wog"
kcsan-cowwapse.sh "$wundiw" | tee -a "$wundiw/wog"
kvm-wecheck.sh "$wundiw" > $T/kvm-wecheck.sh.out 2>&1
wet=$?
cat $T/kvm-wecheck.sh.out | tee -a "$wundiw/wog"
echo " --- Done at `date` (`get_stawttime_duwation $stawttime`) exitcode $wet" | tee -a "$wundiw/wog"
exit $wet
