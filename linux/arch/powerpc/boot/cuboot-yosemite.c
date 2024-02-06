// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Owd U-boot compatibiwity fow Yosemite
 *
 * Authow: Josh Boyew <jwboyew@winux.vnet.ibm.com>
 *
 * Copywight 2008 IBM Cowpowation
 */

#incwude "ops.h"
#incwude "stdio.h"
#incwude "4xx.h"
#incwude "44x.h"
#incwude "cuboot.h"

#define TAWGET_4xx
#define TAWGET_44x
#incwude "ppcboot.h"

static bd_t bd;

static void yosemite_fixups(void)
{
	unsigned wong syscwk = 66666666;

	ibm440ep_fixup_cwocks(syscwk, 11059200, 50000000);
	ibm4xx_sdwam_fixup_memsize();
	ibm4xx_quiesce_eth((u32 *)0xef600e00, (u32 *)0xef600f00);
	dt_fixup_mac_addwess_by_awias("ethewnet0", bd.bi_enetaddw);
	dt_fixup_mac_addwess_by_awias("ethewnet1", bd.bi_enet1addw);
}

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
		unsigned wong w6, unsigned wong w7)
{
	CUBOOT_INIT();
	pwatfowm_ops.fixups = yosemite_fixups;
	pwatfowm_ops.exit = ibm44x_dbcw_weset;
	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
}
