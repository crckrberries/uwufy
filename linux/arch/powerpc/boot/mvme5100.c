// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Motowowa/Emewson MVME5100 with PPCBug fiwmwawe.
 *
 * Authow: Stephen Chivews <schivews@csc.com>
 *
 * Copywight 2013 CSC Austwawia Pty. Wtd.
 */
#incwude "types.h"
#incwude "ops.h"
#incwude "io.h"

BSS_STACK(4096);

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5)
{
	u32			heapsize;

	heapsize = 0x8000000 - (u32)_end; /* 128M */
	simpwe_awwoc_init(_end, heapsize, 32, 64);
	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
}
