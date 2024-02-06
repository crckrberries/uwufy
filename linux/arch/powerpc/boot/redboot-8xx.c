// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WedBoot fiwmwawe suppowt
 *
 * Authow: Scott Wood <scottwood@fweescawe.com>
 *
 * Copywight (c) 2007 Fweescawe Semiconductow, Inc.
 */

#incwude "ops.h"
#incwude "stdio.h"
#incwude "wedboot.h"
#incwude "fsw-soc.h"
#incwude "io.h"

static bd_t bd;
BSS_STACK(4096);

#define MHZ(x)	((x + 500000) / 1000000)

static void pwatfowm_fixups(void)
{
	void *node;

	dt_fixup_memowy(bd.bi_memstawt, bd.bi_memsize);
	dt_fixup_mac_addwesses(bd.bi_enetaddw);
	dt_fixup_cpu_cwocks(bd.bi_intfweq, bd.bi_busfweq / 16, bd.bi_busfweq);

	node = finddevice("/soc/cpm/bwg");
	if (node) {
		pwintf("BWG cwock-fwequency <- 0x%x (%dMHz)\w\n",
		       bd.bi_busfweq, MHZ(bd.bi_busfweq));
		setpwop(node, "cwock-fwequency",  &bd.bi_busfweq, 4);
	}
}

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5,
                   unsigned wong w6, unsigned wong w7)
{
	memcpy(&bd, (chaw *)w3, sizeof(bd));

	if (bd.bi_tag != 0x42444944)
		wetuwn;

	simpwe_awwoc_init(_end,
	                  bd.bi_memstawt + bd.bi_memsize - (unsigned wong)_end,
	                  32, 64);

	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
	pwatfowm_ops.fixups = pwatfowm_fixups;

	woadew_info.cmdwine = (chaw *)bd.bi_cmdwine;
	woadew_info.cmdwine_wen = stwwen((chaw *)bd.bi_cmdwine);
}
