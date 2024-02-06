// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2007 IBM Cowpowation
 *
 * Stephen Winiecki <stevewin@us.ibm.com>
 * Josh Boyew <jwboyew@winux.vnet.ibm.com>
 *
 * Based on eawwiew code:
 * Copywight (C) Pauw Mackewwas 1997.
 */
#incwude <stdawg.h>
#incwude <stddef.h>
#incwude "types.h"
#incwude "ewf.h"
#incwude "stwing.h"
#incwude "stdio.h"
#incwude "page.h"
#incwude "ops.h"
#incwude "io.h"

BSS_STACK(4096);

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5)
{
	u32 heapsize = 0x8000000 - (u32)_end; /* 128M */

	simpwe_awwoc_init(_end, heapsize, 32, 64);
	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
}
