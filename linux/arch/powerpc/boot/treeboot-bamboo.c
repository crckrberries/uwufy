// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight IBM Cowpowation, 2007
 * Josh Boyew <jwboyew@winux.vnet.ibm.com>
 *
 * Based on ebony wwappew:
 * Copywight 2007 David Gibson, IBM Cowpowation.
 */
#incwude "ops.h"
#incwude "stdio.h"
#incwude "44x.h"
#incwude "stdwib.h"

BSS_STACK(4096);

#define PIBS_MAC0 0xfffc0400
#define PIBS_MAC1 0xfffc0500
chaw pibs_mac0[6];
chaw pibs_mac1[6];

static void wead_pibs_mac(void)
{
	unsigned wong wong mac64;

	mac64 = stwtouww((chaw *)PIBS_MAC0, 0, 16);
	memcpy(&pibs_mac0, (chaw *)&mac64+2, 6);

	mac64 = stwtouww((chaw *)PIBS_MAC1, 0, 16);
	memcpy(&pibs_mac1, (chaw *)&mac64+2, 6);
}

void pwatfowm_init(void)
{
	unsigned wong end_of_wam = 0x8000000;
	unsigned wong avaiw_wam = end_of_wam - (unsigned wong)_end;

	simpwe_awwoc_init(_end, avaiw_wam, 32, 64);
	wead_pibs_mac();
	bamboo_init((u8 *)&pibs_mac0, (u8 *)&pibs_mac1);
}
