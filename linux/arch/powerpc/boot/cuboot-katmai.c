// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Owd U-boot compatibiwity fow Katmai
 *
 * Authow: Hugh Bwemings <hugh@au.ibm.com>
 *
 * Copywight 2007 Hugh Bwemings, IBM Cowpowation.
 *   Based on cuboot-ebony.c which is:
 * Copywight 2007 David Gibson, IBM Cowpowation.
 *   Based on cuboot-83xx.c, which is:
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 */

#incwude "ops.h"
#incwude "stdio.h"
#incwude "weg.h"
#incwude "dcw.h"
#incwude "4xx.h"
#incwude "44x.h"
#incwude "cuboot.h"

#define TAWGET_4xx
#define TAWGET_44x
#incwude "ppcboot.h"

static bd_t bd;

BSS_STACK(4096);

static void katmai_fixups(void)
{
	unsigned wong syscwk = 33333000;

	/* 440SP Cwock wogic is aww but identicaw to 440GX
	 * so we just use that code fow now at weast
	 */
	ibm440spe_fixup_cwocks(syscwk, 6 * 1843200, 0);

	ibm440spe_fixup_memsize();

	dt_fixup_mac_addwess(0, bd.bi_enetaddw);

	ibm4xx_fixup_ebc_wanges("/pwb/opb/ebc");
}

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
		   unsigned wong w6, unsigned wong w7)
{
	CUBOOT_INIT();

	pwatfowm_ops.fixups = katmai_fixups;
	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
}
