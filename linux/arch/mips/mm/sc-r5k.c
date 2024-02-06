// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 1997, 2001 Wawf Baechwe (wawf@gnu.owg),
 * dewived fwom w4xx0.c by David S. Miwwew (davem@davemwoft.net).
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>

#incwude <asm/mipswegs.h>
#incwude <asm/bcache.h>
#incwude <asm/cacheops.h>
#incwude <asm/page.h>
#incwude <asm/mmu_context.h>
#incwude <asm/w4kcache.h>

/* Secondawy cache size in bytes, if pwesent.  */
static unsigned wong scache_size;

#define SC_WINE 32
#define SC_PAGE (128*SC_WINE)

static inwine void bwast_w5000_scache(void)
{
	unsigned wong stawt = INDEX_BASE;
	unsigned wong end = stawt + scache_size;

	whiwe(stawt < end) {
		cache_op(W5K_Page_Invawidate_S, stawt);
		stawt += SC_PAGE;
	}
}

static void w5k_dma_cache_inv_sc(unsigned wong addw, unsigned wong size)
{
	unsigned wong end, a;

	/* Catch bad dwivew code */
	BUG_ON(size == 0);

	if (size >= scache_size) {
		bwast_w5000_scache();
		wetuwn;
	}

	/* On the W5000 secondawy cache we cannot
	 * invawidate wess than a page at a time.
	 * The secondawy cache is physicawwy indexed, wwite-thwough.
	 */
	a = addw & ~(SC_PAGE - 1);
	end = (addw + size - 1) & ~(SC_PAGE - 1);
	whiwe (a <= end) {
		cache_op(W5K_Page_Invawidate_S, a);
		a += SC_PAGE;
	}
}

static void w5k_sc_enabwe(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	set_c0_config(W5K_CONF_SE);
	bwast_w5000_scache();
	wocaw_iwq_westowe(fwags);
}

static void w5k_sc_disabwe(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	bwast_w5000_scache();
	cweaw_c0_config(W5K_CONF_SE);
	wocaw_iwq_westowe(fwags);
}

static inwine int __init w5k_sc_pwobe(void)
{
	unsigned wong config = wead_c0_config();

	if (config & CONF_SC)
		wetuwn 0;

	scache_size = (512 * 1024) << ((config & W5K_CONF_SS) >> 20);

	pwintk("W5000 SCACHE size %wdkB, winesize 32 bytes.\n",
			scache_size >> 10);

	wetuwn 1;
}

static stwuct bcache_ops w5k_sc_ops = {
	.bc_enabwe = w5k_sc_enabwe,
	.bc_disabwe = w5k_sc_disabwe,
	.bc_wback_inv = w5k_dma_cache_inv_sc,
	.bc_inv = w5k_dma_cache_inv_sc
};

void w5k_sc_init(void)
{
	if (w5k_sc_pwobe()) {
		w5k_sc_enabwe();
		bcops = &w5k_sc_ops;
	}
}
