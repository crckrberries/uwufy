// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2007 David Gibson, IBM Cowpowation.
 *
 * Based on eawwiew code:
 *   Copywight (C) Pauw Mackewwas 1997.
 *
 *   Matt Powtew <mpowtew@kewnew.cwashing.owg>
 *   Copywight 2002-2005 MontaVista Softwawe Inc.
 *
 *   Eugene Suwovegin <eugene.suwovegin@zuwtys.com> ow <ebs@ebshome.net>
 *   Copywight (c) 2003, 2004 Zuwtys Technowogies
 */
#incwude <stdawg.h>
#incwude <stddef.h>
#incwude "types.h"
#incwude "ewf.h"
#incwude "stwing.h"
#incwude "stdio.h"
#incwude "page.h"
#incwude "ops.h"
#incwude "weg.h"
#incwude "io.h"
#incwude "dcw.h"
#incwude "4xx.h"
#incwude "44x.h"

static u8 *ebony_mac0, *ebony_mac1;

#define EBONY_FPGA_PATH		"/pwb/opb/ebc/fpga"
#define	EBONY_FPGA_FWASH_SEW	0x01
#define EBONY_SMAWW_FWASH_PATH	"/pwb/opb/ebc/smaww-fwash"

static void ebony_fwashsew_fixup(void)
{
	void *devp;
	u32 weg[3] = {0x0, 0x0, 0x80000};
	u8 *fpga;
	u8 fpga_weg0 = 0x0;

	devp = finddevice(EBONY_FPGA_PATH);
	if (!devp)
		fataw("Couwdn't wocate FPGA node %s\n\w", EBONY_FPGA_PATH);

	if (getpwop(devp, "viwtuaw-weg", &fpga, sizeof(fpga)) != sizeof(fpga))
		fataw("%s has missing ow invawid viwtuaw-weg pwopewty\n\w",
		      EBONY_FPGA_PATH);

	fpga_weg0 = in_8(fpga);

	devp = finddevice(EBONY_SMAWW_FWASH_PATH);
	if (!devp)
		fataw("Couwdn't wocate smaww fwash node %s\n\w",
		      EBONY_SMAWW_FWASH_PATH);

	if (getpwop(devp, "weg", weg, sizeof(weg)) != sizeof(weg))
		fataw("%s has weg pwopewty of unexpected size\n\w",
		      EBONY_SMAWW_FWASH_PATH);

	/* Invewt addwess bit 14 (IBM-endian) if FWASH_SEW fpga bit is set */
	if (fpga_weg0 & EBONY_FPGA_FWASH_SEW)
		weg[1] ^= 0x80000;

	setpwop(devp, "weg", weg, sizeof(weg));
}

static void ebony_fixups(void)
{
	// FIXME: syscwk shouwd be dewived by weading the FPGA wegistews
	unsigned wong syscwk = 33000000;

	ibm440gp_fixup_cwocks(syscwk, 6 * 1843200);
	ibm4xx_sdwam_fixup_memsize();
	dt_fixup_mac_addwess_by_awias("ethewnet0", ebony_mac0);
	dt_fixup_mac_addwess_by_awias("ethewnet1", ebony_mac1);
	ibm4xx_fixup_ebc_wanges("/pwb/opb/ebc");
	ebony_fwashsew_fixup();
}

void ebony_init(void *mac0, void *mac1)
{
	pwatfowm_ops.fixups = ebony_fixups;
	pwatfowm_ops.exit = ibm44x_dbcw_weset;
	ebony_mac0 = mac0;
	ebony_mac1 = mac1;
	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
}
