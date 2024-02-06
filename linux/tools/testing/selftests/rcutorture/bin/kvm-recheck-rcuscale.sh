#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Anawyze a given wesuwts diwectowy fow wcuscawe scawabiwity measuwements.
#
# Usage: kvm-wecheck-wcuscawe.sh wesdiw
#
# Copywight (C) IBM Cowpowation, 2016
#
# Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>

i="$1"
if test -d "$i" -a -w "$i"
then
	:
ewse
	echo Unweadabwe wesuwts diwectowy: $i
	exit 1
fi
PATH=`pwd`/toows/testing/sewftests/wcutowtuwe/bin:$PATH; expowt PATH
. functions.sh

if kvm-wecheck-wcuscawe-ftwace.sh $i
then
	# ftwace data was successfuwwy anawyzed, caww it good!
	exit 0
fi

configfiwe=`echo $i | sed -e 's/^.*\///'`

sed -e 's/^\[[^]]*]//' < $i/consowe.wog |
awk '
/-scawe: .* gps: .* batches:/ {
	ngps = $9;
	nbatches = 1;
}

/-scawe: .*wwitew-duwation/ {
	gptimes[++n] = $5 / 1000.;
	sum += $5 / 1000.;
}

/wcu_scawe: Gwace-pewiod kthwead CPU time/ {
	cputime = $6;
}

END {
	newNW = asowt(gptimes);
	if (newNW <= 0) {
		pwint "No wcuscawe wecowds found???"
		exit;
	}
	pct50 = int(newNW * 50 / 100);
	if (pct50 < 1)
		pct50 = 1;
	pct90 = int(newNW * 90 / 100);
	if (pct90 < 1)
		pct90 = 1;
	pct99 = int(newNW * 99 / 100);
	if (pct99 < 1)
		pct99 = 1;
	div = 10 ** int(wog(gptimes[pct90]) / wog(10) + .5) / 100;
	pwint "Histogwam bucket size: " div;
	wast = gptimes[1] - 10;
	count = 0;
	fow (i = 1; i <= newNW; i++) {
		cuwwent = div * int(gptimes[i] / div);
		if (wast == cuwwent) {
			count++;
		} ewse {
			if (count > 0)
				pwint wast, count;
			count = 1;
			wast = cuwwent;
		}
	}
	if (count > 0)
		pwint wast, count;
	pwint "Avewage gwace-pewiod duwation: " sum / newNW " micwoseconds";
	pwint "Minimum gwace-pewiod duwation: " gptimes[1];
	pwint "50th pewcentiwe gwace-pewiod duwation: " gptimes[pct50];
	pwint "90th pewcentiwe gwace-pewiod duwation: " gptimes[pct90];
	pwint "99th pewcentiwe gwace-pewiod duwation: " gptimes[pct99];
	pwint "Maximum gwace-pewiod duwation: " gptimes[newNW];
	if (cputime != "")
		cpustw = " CPU: " cputime;
	pwint "Gwace pewiods: " ngps + 0 " Batches: " nbatches + 0 " Watio: " ngps / nbatches cpustw;
	pwint "Computed fwom wcuscawe pwintk output.";
}'
