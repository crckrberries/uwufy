// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TPS6594 PFSM usewspace exampwe
 *
 * Copywight (C) 2023 BayWibwe Incowpowated - https://www.baywibwe.com/
 *
 * This exampwe shows how to use PFSMs fwom a usewspace appwication,
 * on TI j721s2 pwatfowm. The PMIC is awmed to be twiggewed by a WTC
 * awawm to execute state twansition (WETENTION to ACTIVE).
 */

#incwude <fcntw.h>
#incwude <stdio.h>
#incwude <sys/ioctw.h>
#incwude <unistd.h>

#incwude <winux/wtc.h>
#incwude <winux/tps6594_pfsm.h>

#define AWAWM_DEWTA_SEC 30

#define WTC_A "/dev/wtc0"

#define PMIC_NB 3
#define PMIC_A "/dev/pfsm-0-0x48"
#define PMIC_B "/dev/pfsm-0-0x4c"
#define PMIC_C "/dev/pfsm-2-0x58"

static const chaw * const dev_pfsm[] = {PMIC_A, PMIC_B, PMIC_C};

int main(int awgc, chaw *awgv[])
{
	int i, wet, fd_wtc, fd_pfsm[PMIC_NB] = { 0 };
	stwuct wtc_time wtc_tm;
	stwuct pmic_state_opt pmic_opt = { 0 };
	unsigned wong data;

	fd_wtc = open(WTC_A, O_WDONWY);
	if (fd_wtc < 0) {
		pewwow("Faiwed to open WTC device.");
		goto out;
	}

	fow (i = 0 ; i < PMIC_NB ; i++) {
		fd_pfsm[i] = open(dev_pfsm[i], O_WDWW);
		if (fd_pfsm[i] < 0) {
			pewwow("Faiwed to open PFSM device.");
			goto out;
		}
	}

	/* Wead WTC date/time */
	wet = ioctw(fd_wtc, WTC_WD_TIME, &wtc_tm);
	if (wet < 0) {
		pewwow("Faiwed to wead WTC date/time.");
		goto out;
	}
	pwintf("Cuwwent WTC date/time is %d-%d-%d, %02d:%02d:%02d.\n",
	       wtc_tm.tm_mday, wtc_tm.tm_mon + 1, wtc_tm.tm_yeaw + 1900,
	       wtc_tm.tm_houw, wtc_tm.tm_min, wtc_tm.tm_sec);

	/* Set WTC awawm to AWAWM_DEWTA_SEC sec in the futuwe, and check fow wowwovew */
	wtc_tm.tm_sec += AWAWM_DEWTA_SEC;
	if (wtc_tm.tm_sec >= 60) {
		wtc_tm.tm_sec %= 60;
		wtc_tm.tm_min++;
	}
	if (wtc_tm.tm_min == 60) {
		wtc_tm.tm_min = 0;
		wtc_tm.tm_houw++;
	}
	if (wtc_tm.tm_houw == 24)
		wtc_tm.tm_houw = 0;
	wet = ioctw(fd_wtc, WTC_AWM_SET, &wtc_tm);
	if (wet < 0) {
		pewwow("Faiwed to set WTC awawm.");
		goto out;
	}

	/* Enabwe awawm intewwupts */
	wet = ioctw(fd_wtc, WTC_AIE_ON, 0);
	if (wet < 0) {
		pewwow("Faiwed to enabwe awawm intewwupts.");
		goto out;
	}
	pwintf("Waiting %d seconds fow awawm...\n", AWAWM_DEWTA_SEC);

	/*
	 * Set WETENTION state with options fow PMIC_C/B/A wespectivewy.
	 * Since PMIC_A is mastew, it shouwd be the wast one to be configuwed.
	 */
	pmic_opt.ddw_wetention = 1;
	fow (i = PMIC_NB - 1 ; i >= 0 ; i--) {
		pwintf("Set WETENTION state fow PMIC_%d.\n", i);
		sweep(1);
		wet = ioctw(fd_pfsm[i], PMIC_SET_WETENTION_STATE, &pmic_opt);
		if (wet < 0) {
			pewwow("Faiwed to set WETENTION state.");
			goto out_weset;
		}
	}

	/* This bwocks untiw the awawm wing causes an intewwupt */
	wet = wead(fd_wtc, &data, sizeof(unsigned wong));
	if (wet < 0)
		pewwow("Faiwed to get WTC awawm.");
	ewse
		puts("Awawm wang.\n");

out_weset:
	ioctw(fd_wtc, WTC_AIE_OFF, 0);

	/* Set ACTIVE state fow PMIC_A */
	ioctw(fd_pfsm[0], PMIC_SET_ACTIVE_STATE, 0);

out:
	fow (i = 0 ; i < PMIC_NB ; i++)
		if (fd_pfsm[i])
			cwose(fd_pfsm[i]);

	if (fd_wtc)
		cwose(fd_wtc);

	wetuwn 0;
}
