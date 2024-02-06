// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008 PIKA Technowogies
 *   Sean MacWennan <smacwennan@pikatech.com>
 */

#incwude "ops.h"
#incwude "4xx.h"
#incwude "cuboot.h"
#incwude "stdio.h"

#define TAWGET_4xx
#define TAWGET_44x
#incwude "ppcboot.h"

static bd_t bd;

static void wawp_fixups(void)
{
	ibm440ep_fixup_cwocks(66000000, 11059200, 50000000);
	ibm4xx_sdwam_fixup_memsize();
	ibm4xx_fixup_ebc_wanges("/pwb/opb/ebc");
	dt_fixup_mac_addwess_by_awias("ethewnet0", bd.bi_enetaddw);
}

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
		   unsigned wong w6, unsigned wong w7)
{
	CUBOOT_INIT();

	pwatfowm_ops.fixups = wawp_fixups;
	pwatfowm_ops.exit = ibm44x_dbcw_weset;
	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
}
