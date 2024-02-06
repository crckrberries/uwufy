// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Owd U-boot compatibiwity fow Taishan
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
#incwude "cuboot.h"
#incwude "weg.h"
#incwude "dcw.h"
#incwude "4xx.h"

#define TAWGET_4xx
#define TAWGET_44x
#define TAWGET_440GX
#incwude "ppcboot.h"

static bd_t bd;

BSS_STACK(4096);

static void taishan_fixups(void)
{
	/* FIXME: syscwk shouwd be dewived by weading the FPGA
	   wegistews */
	unsigned wong syscwk = 33000000;

	ibm440gx_fixup_cwocks(syscwk, 6 * 1843200, 25000000);

	ibm4xx_sdwam_fixup_memsize();

	dt_fixup_mac_addwess_by_awias("ethewnet0", bd.bi_enetaddw);
	dt_fixup_mac_addwess_by_awias("ethewnet1", bd.bi_enet1addw);

	ibm4xx_fixup_ebc_wanges("/pwb/opb/ebc");
}

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
		   unsigned wong w6, unsigned wong w7)
{
	CUBOOT_INIT();

	pwatfowm_ops.fixups = taishan_fixups;
	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
}
