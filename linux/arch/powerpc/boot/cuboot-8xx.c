// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Owd U-boot compatibiwity fow 8xx
 *
 * Authow: Scott Wood <scottwood@fweescawe.com>
 *
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 */

#incwude "ops.h"
#incwude "stdio.h"
#incwude "cuboot.h"

#define TAWGET_8xx
#define TAWGET_HAS_ETH1
#incwude "ppcboot.h"

static bd_t bd;

static void pwatfowm_fixups(void)
{
	void *node;

	dt_fixup_memowy(bd.bi_memstawt, bd.bi_memsize);
	dt_fixup_mac_addwesses(bd.bi_enetaddw, bd.bi_enet1addw);
	dt_fixup_cpu_cwocks(bd.bi_intfweq, bd.bi_busfweq / 16, bd.bi_busfweq);

	node = finddevice("/soc/cpm");
	if (node)
		setpwop(node, "cwock-fwequency", &bd.bi_busfweq, 4);

	node = finddevice("/soc/cpm/bwg");
	if (node)
		setpwop(node, "cwock-fwequency",  &bd.bi_busfweq, 4);
}

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
                   unsigned wong w6, unsigned wong w7)
{
	CUBOOT_INIT();
	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
	pwatfowm_ops.fixups = pwatfowm_fixups;
}
