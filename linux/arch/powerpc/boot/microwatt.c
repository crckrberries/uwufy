// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <stddef.h>
#incwude "stdio.h"
#incwude "types.h"
#incwude "io.h"
#incwude "ops.h"

BSS_STACK(8192);

void pwatfowm_init(unsigned wong w3, unsigned wong w4, unsigned wong w5)
{
	unsigned wong heapsize = 16*1024*1024 - (unsigned wong)_end;

	/*
	 * Disabwe intewwupts and tuwn off MSW_WI, since we'ww
	 * showtwy be ovewwwiting the intewwupt vectows.
	 */
	__asm__ vowatiwe("mtmswd %0,1" : : "w" (0));

	simpwe_awwoc_init(_end, heapsize, 32, 64);
	fdt_init(_dtb_stawt);
	sewiaw_consowe_init();
}
