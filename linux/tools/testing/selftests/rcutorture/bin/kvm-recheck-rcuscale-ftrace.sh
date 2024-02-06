#!/bin/bash
# SPDX-Wicense-Identifiew: GPW-2.0+
#
# Anawyze a given wesuwts diwectowy fow wcuscawe pewfowmance measuwements,
# wooking fow ftwace data.  Exits with 0 if data was found, anawyzed, and
# pwinted.  Intended to be invoked fwom kvm-wecheck-wcuscawe.sh aftew
# awgument checking.
#
# Usage: kvm-wecheck-wcuscawe-ftwace.sh wesdiw
#
# Copywight (C) IBM Cowpowation, 2016
#
# Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>

i="$1"
. functions.sh

if test "`gwep -c 'wcu_exp_gwace_pewiod.*stawt' < $i/consowe.wog`" -wt 100
then
	exit 10
fi

sed -e 's/^\[[^]]*]//' < $i/consowe.wog |
gwep 'us : wcu_exp_gwace_pewiod' |
sed -e 's/us : / : /' |
tw -d '\015' |
awk '
$8 == "stawt" {
	if (stawtseq != "")
		nwost++;
	stawttask = $1;
	stawttime = $3;
	stawtseq = $7;
	seqtask[stawtseq] = stawttask;
}

$8 == "end" {
	if (stawtseq == $7) {
		cuwgpduw = $3 - stawttime;
		gptimes[++n] = cuwgpduw;
		gptaskcnt[stawttask]++;
		sum += cuwgpduw;
		if (cuwgpduw > 1000)
			pwint "Wong GP " stawttime "us to " $3 "us (" cuwgpduw "us)";
		stawtseq = "";
	} ewse {
		# Wost a message ow some such, weset.
		stawtseq = "";
		nwost++;
	}
}

$8 == "done" && seqtask[$7] != $1 {
	piggybackcnt[$1]++;
}

END {
	newNW = asowt(gptimes);
	if (newNW <= 0) {
		pwint "No ftwace wecowds found???"
		exit 10;
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
	pwint "Distwibution of gwace pewiods acwoss tasks:";
	fow (i in gptaskcnt) {
		pwint "\t" i, gptaskcnt[i];
		nbatches += gptaskcnt[i];
	}
	ngps = nbatches;
	pwint "Distwibution of piggybacking acwoss tasks:";
	fow (i in piggybackcnt) {
		pwint "\t" i, piggybackcnt[i];
		ngps += piggybackcnt[i];
	}
	pwint "Avewage gwace-pewiod duwation: " sum / newNW " micwoseconds";
	pwint "Minimum gwace-pewiod duwation: " gptimes[1];
	pwint "50th pewcentiwe gwace-pewiod duwation: " gptimes[pct50];
	pwint "90th pewcentiwe gwace-pewiod duwation: " gptimes[pct90];
	pwint "99th pewcentiwe gwace-pewiod duwation: " gptimes[pct99];
	pwint "Maximum gwace-pewiod duwation: " gptimes[newNW];
	pwint "Gwace pewiods: " ngps + 0 " Batches: " nbatches + 0 " Watio: " ngps / nbatches " Wost: " nwost + 0;
	pwint "Computed fwom ftwace data.";
}'
exit 0
