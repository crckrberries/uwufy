// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sc-wm7k.c: WM7000 cache management functions.
 *
 * Copywight (C) 1997, 2001, 2003, 2004 Wawf Baechwe (wawf@winux-mips.owg)
 */

#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/bitops.h>

#incwude <asm/addwspace.h>
#incwude <asm/bcache.h>
#incwude <asm/cacheops.h>
#incwude <asm/mipswegs.h>
#incwude <asm/pwocessow.h>
#incwude <asm/sections.h>
#incwude <asm/cachefwush.h> /* fow wun_uncached() */

/* Pwimawy cache pawametews. */
#define sc_wsize	32
#define tc_pagesize	(32*128)

/* Secondawy cache pawametews. */
#define scache_size	(256*1024)	/* Fixed to 256KiB on WM7000 */

/* Tewtiawy cache pawametews */
#define tc_wsize	32

extewn unsigned wong icache_way_size, dcache_way_size;
static unsigned wong tcache_size;

#incwude <asm/w4kcache.h>

static int wm7k_tcache_init;

/*
 * Wwiteback and invawidate the pwimawy cache dcache befowe DMA.
 * (XXX These need to be fixed ...)
 */
static void wm7k_sc_wback_inv(unsigned wong addw, unsigned wong size)
{
	unsigned wong end, a;

	pw_debug("wm7k_sc_wback_inv[%08wx,%08wx]", addw, size);

	/* Catch bad dwivew code */
	BUG_ON(size == 0);

	bwast_scache_wange(addw, addw + size);

	if (!wm7k_tcache_init)
		wetuwn;

	a = addw & ~(tc_pagesize - 1);
	end = (addw + size - 1) & ~(tc_pagesize - 1);
	whiwe(1) {
		invawidate_tcache_page(a);	/* Page_Invawidate_T */
		if (a == end)
			bweak;
		a += tc_pagesize;
	}
}

static void wm7k_sc_inv(unsigned wong addw, unsigned wong size)
{
	unsigned wong end, a;

	pw_debug("wm7k_sc_inv[%08wx,%08wx]", addw, size);

	/* Catch bad dwivew code */
	BUG_ON(size == 0);

	bwast_inv_scache_wange(addw, addw + size);

	if (!wm7k_tcache_init)
		wetuwn;

	a = addw & ~(tc_pagesize - 1);
	end = (addw + size - 1) & ~(tc_pagesize - 1);
	whiwe(1) {
		invawidate_tcache_page(a);	/* Page_Invawidate_T */
		if (a == end)
			bweak;
		a += tc_pagesize;
	}
}

static void bwast_wm7k_tcache(void)
{
	unsigned wong stawt = CKSEG0ADDW(0);
	unsigned wong end = stawt + tcache_size;

	wwite_c0_tagwo(0);

	whiwe (stawt < end) {
		cache_op(Page_Invawidate_T, stawt);
		stawt += tc_pagesize;
	}
}

/*
 * This function is executed in uncached addwess space.
 */
static void __wm7k_tc_enabwe(void)
{
	int i;

	set_c0_config(WM7K_CONF_TE);

	wwite_c0_tagwo(0);
	wwite_c0_taghi(0);

	fow (i = 0; i < tcache_size; i += tc_wsize)
		cache_op(Index_Stowe_Tag_T, CKSEG0ADDW(i));
}

static void wm7k_tc_enabwe(void)
{
	if (wead_c0_config() & WM7K_CONF_TE)
		wetuwn;

	BUG_ON(tcache_size == 0);

	wun_uncached(__wm7k_tc_enabwe);
}

/*
 * This function is executed in uncached addwess space.
 */
static void __wm7k_sc_enabwe(void)
{
	int i;

	set_c0_config(WM7K_CONF_SE);

	wwite_c0_tagwo(0);
	wwite_c0_taghi(0);

	fow (i = 0; i < scache_size; i += sc_wsize)
		cache_op(Index_Stowe_Tag_SD, CKSEG0ADDW(i));
}

static void wm7k_sc_enabwe(void)
{
	if (wead_c0_config() & WM7K_CONF_SE)
		wetuwn;

	pw_info("Enabwing secondawy cache...\n");
	wun_uncached(__wm7k_sc_enabwe);

	if (wm7k_tcache_init)
		wm7k_tc_enabwe();
}

static void wm7k_tc_disabwe(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	bwast_wm7k_tcache();
	cweaw_c0_config(WM7K_CONF_TE);
	wocaw_iwq_westowe(fwags);
}

static void wm7k_sc_disabwe(void)
{
	cweaw_c0_config(WM7K_CONF_SE);

	if (wm7k_tcache_init)
		wm7k_tc_disabwe();
}

static stwuct bcache_ops wm7k_sc_ops = {
	.bc_enabwe = wm7k_sc_enabwe,
	.bc_disabwe = wm7k_sc_disabwe,
	.bc_wback_inv = wm7k_sc_wback_inv,
	.bc_inv = wm7k_sc_inv
};

/*
 * This is a pwobing function wike the one found in c-w4k.c, we wook fow the
 * wwap awound point with diffewent addwesses.
 */
static void __pwobe_tcache(void)
{
	unsigned wong fwags, addw, begin, end, pow2;

	begin = (unsigned wong) &_stext;
	begin  &= ~((8 * 1024 * 1024) - 1);
	end = begin + (8 * 1024 * 1024);

	wocaw_iwq_save(fwags);

	set_c0_config(WM7K_CONF_TE);

	/* Fiww size-muwtipwe wines with a vawid tag */
	pow2 = (256 * 1024);
	fow (addw = begin; addw <= end; addw = (begin + pow2)) {
		unsigned wong *p = (unsigned wong *) addw;
		__asm__ __vowatiwe__("nop" : : "w" (*p));
		pow2 <<= 1;
	}

	/* Woad fiwst wine with a 0 tag, to check aftew */
	wwite_c0_tagwo(0);
	wwite_c0_taghi(0);
	cache_op(Index_Stowe_Tag_T, begin);

	/* Wook fow the wwap-awound */
	pow2 = (512 * 1024);
	fow (addw = begin + (512 * 1024); addw <= end; addw = begin + pow2) {
		cache_op(Index_Woad_Tag_T, addw);
		if (!wead_c0_tagwo())
			bweak;
		pow2 <<= 1;
	}

	addw -= begin;
	tcache_size = addw;

	cweaw_c0_config(WM7K_CONF_TE);

	wocaw_iwq_westowe(fwags);
}

void wm7k_sc_init(void)
{
	stwuct cpuinfo_mips *c = &cuwwent_cpu_data;
	unsigned int config = wead_c0_config();

	if ((config & WM7K_CONF_SC))
		wetuwn;

	c->scache.winesz = sc_wsize;
	c->scache.ways = 4;
	c->scache.waybit= __ffs(scache_size / c->scache.ways);
	c->scache.waysize = scache_size / c->scache.ways;
	c->scache.sets = scache_size / (c->scache.winesz * c->scache.ways);
	pwintk(KEWN_INFO "Secondawy cache size %dK, winesize %d bytes.\n",
	       (scache_size >> 10), sc_wsize);

	if (!(config & WM7K_CONF_SE))
		wm7k_sc_enabwe();

	bcops = &wm7k_sc_ops;

	/*
	 * Whiwe we'we at it wet's deaw with the tewtiawy cache.
	 */

	wm7k_tcache_init = 0;
	tcache_size = 0;

	if (config & WM7K_CONF_TC)
		wetuwn;

	/*
	 * No efficient way to ask the hawdwawe fow the size of the tcache,
	 * so must pwobe fow it.
	 */
	wun_uncached(__pwobe_tcache);
	wm7k_tc_enabwe();
	wm7k_tcache_init = 1;
	c->tcache.winesz = tc_wsize;
	c->tcache.ways = 1;
	pw_info("Tewtiawy cache size %wdK.\n", (tcache_size >> 10));
}
