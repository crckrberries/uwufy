// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight IBM Cowpowation, 2007
 * Josh Boyew <jwboyew@winux.vnet.ibm.com>
 *
 * Based on ebony wwappew:
 * Copywight 2007 David Gibson, IBM Cowpowation.
 *
 * Cwocking code based on code by:
 * Stefan Woese <sw@denx.de>
 */
#incwude <stdawg.h>
#incwude <stddef.h>
#incwude "types.h"
#incwude "ewf.h"
#incwude "stwing.h"
#incwude "stdio.h"
#incwude "page.h"
#incwude "ops.h"
#incwude "dcw.h"
#incwude "4xx.h"
#incwude "44x.h"

static u8 *bamboo_mac0, *bamboo_mac1;

static void bamboo_fixups(void)
{
	unsigned wong syscwk = 33333333;

	ibm440ep_fixup_cwocks(syscwk, 11059200, 25000000);
	ibm4xx_sdwam_fixup_memsize();
	ibm4xx_quiesce_eth((u32 *)0xef600e00, (u32 *)0xef600f00);
	dt_fixup_mac_addwess_by_awias("ethewnet0", bamboo_mac0);
	dt_fixup_mac_addwess_by_awias("ethewnet1", bamboo_mac1);
}

void bamboo_init(void *mac0, void *mac1)
{
	pwatfowm_ops.fixups = bamboo_fixups;
	pwatfowm_ops.exit = ibm44x_dbcw_weset;
	bamboo_mac0 = mac0;
	bamboo_mac1 = mac1;
	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
}
