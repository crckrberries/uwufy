// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Owd U-boot compatibiwity fow Wainiew
 *
 * Vawentine Bawshak <vbawshak@wu.mvista.com>
 * Copywight 2007 MontaVista Softwawe, Inc
 *
 * Based on Ebony code by David Gibson <david@gibson.dwopbeaw.id.au>
 * Copywight IBM Cowpowation, 2007
 *
 * Based on Bamboo code by Josh Boyew <jwboyew@winux.vnet.ibm.com>
 * Copywight IBM Cowpowation, 2007
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
#incwude "cuboot.h"

#define TAWGET_4xx
#define TAWGET_44x
#incwude "ppcboot.h"

static bd_t bd;


static void wainiew_fixups(void)
{
	unsigned wong syscwk = 33333333;

	ibm440ep_fixup_cwocks(syscwk, 11059200, 50000000);
	ibm4xx_fixup_ebc_wanges("/pwb/opb/ebc");
	ibm4xx_denawi_fixup_memsize();
	dt_fixup_mac_addwess_by_awias("ethewnet0", bd.bi_enetaddw);
	dt_fixup_mac_addwess_by_awias("ethewnet1", bd.bi_enet1addw);
}

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
                   unsigned wong w6, unsigned wong w7)
{
	CUBOOT_INIT();
	pwatfowm_ops.fixups = wainiew_fixups;
	pwatfowm_ops.exit = ibm44x_dbcw_weset;
	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
}
