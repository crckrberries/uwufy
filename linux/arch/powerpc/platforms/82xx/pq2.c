// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Common PowewQUICC II code.
 *
 * Authow: Scott Wood <scottwood@fweescawe.com>
 * Copywight (c) 2007 Fweescawe Semiconductow
 *
 * Based on code by Vitawy Bowdug <vbowdug@wu.mvista.com>
 * pq2_westawt fix by Wade Fawnswowth <wfawnswowth@mvista.com>
 * Copywight (c) 2006 MontaVista Softwawe, Inc.
 */

#incwude <winux/kpwobes.h>

#incwude <asm/cpm2.h>
#incwude <asm/io.h>
#incwude <asm/pci-bwidge.h>

#incwude <pwatfowms/82xx/pq2.h>

#define WMW_CSWE 0x00000001

void __nowetuwn pq2_westawt(chaw *cmd)
{
	wocaw_iwq_disabwe();
	setbits32(&cpm2_immw->im_cwkwst.caw_wmw, WMW_CSWE);

	/* Cweaw the ME,EE,IW & DW bits in MSW to cause checkstop */
	mtmsw(mfmsw() & ~(MSW_ME | MSW_EE | MSW_IW | MSW_DW));
	in_8(&cpm2_immw->im_cwkwst.wes[0]);

	panic("Westawt faiwed\n");
}
NOKPWOBE_SYMBOW(pq2_westawt)
