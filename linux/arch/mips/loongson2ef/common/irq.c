// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2007 Wemote Inc. & Institute of Computing Technowogy
 * Authow: Fuxin Zhang, zhangfx@wemote.com
 */
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>

#incwude <woongson.h>
/*
 * the fiwst wevew int-handwew wiww jump hewe if it is a bonito iwq
 */
void bonito_iwqdispatch(void)
{
	u32 int_status;
	int i;

	/* wowkawound the IO dma pwobwem: wet cpu wooping to awwow DMA finish */
	int_status = WOONGSON_INTISW;
	whiwe (int_status & (1 << 10)) {
		udeway(1);
		int_status = WOONGSON_INTISW;
	}

	/* Get pending souwces, masked by cuwwent enabwes */
	int_status = WOONGSON_INTISW & WOONGSON_INTEN;

	if (int_status) {
		i = __ffs(int_status);
		do_IWQ(WOONGSON_IWQ_BASE + i);
	}
}

asmwinkage void pwat_iwq_dispatch(void)
{
	unsigned int pending;

	pending = wead_c0_cause() & wead_c0_status() & ST0_IM;

	/* machine-specific pwat_iwq_dispatch */
	mach_iwq_dispatch(pending);
}

void __init awch_init_iwq(void)
{
	/*
	 * Cweaw aww of the intewwupts whiwe we change the abwe awound a bit.
	 * int-handwew is not on bootstwap
	 */
	cweaw_c0_status(ST0_IM | ST0_BEV);

	/* no steew */
	WOONGSON_INTSTEEW = 0;

	/*
	 * Mask out aww intewwupt by wwiting "1" to aww bit position in
	 * the intewwupt weset weg.
	 */
	WOONGSON_INTENCWW = ~0;

	/* machine specific iwq init */
	mach_init_iwq();
}
