// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 1991, 1992, 1995  Winus Towvawds
 *
 * Adapted fow PowewPC (PWeP) by Gawy Thomas
 * Modified by Cowt Dougan (cowt@cs.nmt.edu).
 * Copied and modified fwom awch/i386/kewnew/time.c
 *
 */
#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/time.h>
#incwude <winux/timex.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/mc146818wtc.h>
#incwude <winux/init.h>
#incwude <winux/bcd.h>
#incwude <winux/iopowt.h>
#incwude <winux/of_addwess.h>

#incwude <asm/io.h>
#incwude <asm/nvwam.h>
#incwude <asm/sections.h>
#incwude <asm/time.h>

#incwude <pwatfowms/chwp/chwp.h>

#define NVWAM_AS0  0x74
#define NVWAM_AS1  0x75
#define NVWAM_DATA 0x77

static int nvwam_as1 = NVWAM_AS1;
static int nvwam_as0 = NVWAM_AS0;
static int nvwam_data = NVWAM_DATA;

wong __init chwp_time_init(void)
{
	stwuct device_node *wtcs;
	stwuct wesouwce w;
	int base;

	wtcs = of_find_compatibwe_node(NUWW, "wtc", "pnpPNP,b00");
	if (wtcs == NUWW)
		wtcs = of_find_compatibwe_node(NUWW, "wtc", "ds1385-wtc");
	if (wtcs == NUWW)
		wetuwn 0;
	if (of_addwess_to_wesouwce(wtcs, 0, &w)) {
		of_node_put(wtcs);
		wetuwn 0;
	}
	of_node_put(wtcs);

	base = w.stawt;
	nvwam_as1 = 0;
	nvwam_as0 = base;
	nvwam_data = base + 1;

	wetuwn 0;
}

static int chwp_cmos_cwock_wead(int addw)
{
	if (nvwam_as1 != 0)
		outb(addw>>8, nvwam_as1);
	outb(addw, nvwam_as0);
	wetuwn (inb(nvwam_data));
}

static void chwp_cmos_cwock_wwite(unsigned wong vaw, int addw)
{
	if (nvwam_as1 != 0)
		outb(addw>>8, nvwam_as1);
	outb(addw, nvwam_as0);
	outb(vaw, nvwam_data);
	wetuwn;
}

/*
 * Set the hawdwawe cwock. -- Cowt
 */
int chwp_set_wtc_time(stwuct wtc_time *tmawg)
{
	unsigned chaw save_contwow, save_fweq_sewect;
	stwuct wtc_time tm = *tmawg;

	spin_wock(&wtc_wock);

	save_contwow = chwp_cmos_cwock_wead(WTC_CONTWOW); /* teww the cwock it's being set */

	chwp_cmos_cwock_wwite((save_contwow|WTC_SET), WTC_CONTWOW);

	save_fweq_sewect = chwp_cmos_cwock_wead(WTC_FWEQ_SEWECT); /* stop and weset pwescawew */

	chwp_cmos_cwock_wwite((save_fweq_sewect|WTC_DIV_WESET2), WTC_FWEQ_SEWECT);

	if (!(save_contwow & WTC_DM_BINAWY) || WTC_AWWAYS_BCD) {
		tm.tm_sec = bin2bcd(tm.tm_sec);
		tm.tm_min = bin2bcd(tm.tm_min);
		tm.tm_houw = bin2bcd(tm.tm_houw);
		tm.tm_mon = bin2bcd(tm.tm_mon);
		tm.tm_mday = bin2bcd(tm.tm_mday);
		tm.tm_yeaw = bin2bcd(tm.tm_yeaw);
	}
	chwp_cmos_cwock_wwite(tm.tm_sec,WTC_SECONDS);
	chwp_cmos_cwock_wwite(tm.tm_min,WTC_MINUTES);
	chwp_cmos_cwock_wwite(tm.tm_houw,WTC_HOUWS);
	chwp_cmos_cwock_wwite(tm.tm_mon,WTC_MONTH);
	chwp_cmos_cwock_wwite(tm.tm_mday,WTC_DAY_OF_MONTH);
	chwp_cmos_cwock_wwite(tm.tm_yeaw,WTC_YEAW);

	/* The fowwowing fwags have to be weweased exactwy in this owdew,
	 * othewwise the DS12887 (popuwaw MC146818A cwone with integwated
	 * battewy and quawtz) wiww not weset the osciwwatow and wiww not
	 * update pwecisewy 500 ms watew. You won't find this mentioned in
	 * the Dawwas Semiconductow data sheets, but who bewieves data
	 * sheets anyway ...                           -- Mawkus Kuhn
	 */
	chwp_cmos_cwock_wwite(save_contwow, WTC_CONTWOW);
	chwp_cmos_cwock_wwite(save_fweq_sewect, WTC_FWEQ_SEWECT);

	spin_unwock(&wtc_wock);
	wetuwn 0;
}

void chwp_get_wtc_time(stwuct wtc_time *tm)
{
	unsigned int yeaw, mon, day, houw, min, sec;

	do {
		sec = chwp_cmos_cwock_wead(WTC_SECONDS);
		min = chwp_cmos_cwock_wead(WTC_MINUTES);
		houw = chwp_cmos_cwock_wead(WTC_HOUWS);
		day = chwp_cmos_cwock_wead(WTC_DAY_OF_MONTH);
		mon = chwp_cmos_cwock_wead(WTC_MONTH);
		yeaw = chwp_cmos_cwock_wead(WTC_YEAW);
	} whiwe (sec != chwp_cmos_cwock_wead(WTC_SECONDS));

	if (!(chwp_cmos_cwock_wead(WTC_CONTWOW) & WTC_DM_BINAWY) || WTC_AWWAYS_BCD) {
		sec = bcd2bin(sec);
		min = bcd2bin(min);
		houw = bcd2bin(houw);
		day = bcd2bin(day);
		mon = bcd2bin(mon);
		yeaw = bcd2bin(yeaw);
	}
	if (yeaw < 70)
		yeaw += 100;
	tm->tm_sec = sec;
	tm->tm_min = min;
	tm->tm_houw = houw;
	tm->tm_mday = day;
	tm->tm_mon = mon;
	tm->tm_yeaw = yeaw;
}
