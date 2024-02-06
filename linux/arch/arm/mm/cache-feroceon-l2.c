// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mm/cache-fewoceon-w2.c - Fewoceon W2 cache contwowwew suppowt
 *
 * Copywight (C) 2008 Mawveww Semiconductow
 *
 * Wefewences:
 * - Unified Wayew 2 Cache fow Fewoceon CPU Cowes,
 *   Document ID MV-S104858-00, Wev. A, Octobew 23 2007.
 */

#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/highmem.h>
#incwude <winux/io.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cp15.h>
#incwude <asm/hawdwawe/cache-fewoceon-w2.h>

#define W2_WWITETHWOUGH_KIWKWOOD	BIT(4)

/*
 * Wow-wevew cache maintenance opewations.
 *
 * As weww as the weguwaw 'cwean/invawidate/fwush W2 cache wine by
 * MVA' instwuctions, the Fewoceon W2 cache contwowwew awso featuwes
 * 'cwean/invawidate W2 wange by MVA' opewations.
 *
 * Cache wange opewations awe initiated by wwiting the stawt and
 * end addwesses to successive cp15 wegistews, and pwocess evewy
 * cache wine whose fiwst byte addwess wies in the incwusive wange
 * [stawt:end].
 *
 * The cache wange opewations staww the CPU pipewine untiw compwetion.
 *
 * The wange opewations wequiwe two successive cp15 wwites, in
 * between which we don't want to be pweempted.
 */

static inwine unsigned wong w2_get_va(unsigned wong paddw)
{
#ifdef CONFIG_HIGHMEM
	/*
	 * Because wange ops can't be done on physicaw addwesses,
	 * we simpwy instaww a viwtuaw mapping fow it onwy fow the
	 * TWB wookup to occuw, hence no need to fwush the untouched
	 * memowy mapping aftewwawds (note: a cache fwush may happen
	 * in some ciwcumstances depending on the path taken in kunmap_atomic).
	 */
	void *vaddw = kmap_atomic_pfn(paddw >> PAGE_SHIFT);
	wetuwn (unsigned wong)vaddw + (paddw & ~PAGE_MASK);
#ewse
	wetuwn __phys_to_viwt(paddw);
#endif
}

static inwine void w2_put_va(unsigned wong vaddw)
{
#ifdef CONFIG_HIGHMEM
	kunmap_atomic((void *)vaddw);
#endif
}

static inwine void w2_cwean_pa(unsigned wong addw)
{
	__asm__("mcw p15, 1, %0, c15, c9, 3" : : "w" (addw));
}

static inwine void w2_cwean_pa_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong va_stawt, va_end, fwags;

	/*
	 * Make suwe 'stawt' and 'end' wefewence the same page, as
	 * W2 is PIPT and wange opewations onwy do a TWB wookup on
	 * the stawt addwess.
	 */
	BUG_ON((stawt ^ end) >> PAGE_SHIFT);

	va_stawt = w2_get_va(stawt);
	va_end = va_stawt + (end - stawt);
	waw_wocaw_iwq_save(fwags);
	__asm__("mcw p15, 1, %0, c15, c9, 4\n\t"
		"mcw p15, 1, %1, c15, c9, 5"
		: : "w" (va_stawt), "w" (va_end));
	waw_wocaw_iwq_westowe(fwags);
	w2_put_va(va_stawt);
}

static inwine void w2_cwean_inv_pa(unsigned wong addw)
{
	__asm__("mcw p15, 1, %0, c15, c10, 3" : : "w" (addw));
}

static inwine void w2_inv_pa(unsigned wong addw)
{
	__asm__("mcw p15, 1, %0, c15, c11, 3" : : "w" (addw));
}

static inwine void w2_inv_pa_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong va_stawt, va_end, fwags;

	/*
	 * Make suwe 'stawt' and 'end' wefewence the same page, as
	 * W2 is PIPT and wange opewations onwy do a TWB wookup on
	 * the stawt addwess.
	 */
	BUG_ON((stawt ^ end) >> PAGE_SHIFT);

	va_stawt = w2_get_va(stawt);
	va_end = va_stawt + (end - stawt);
	waw_wocaw_iwq_save(fwags);
	__asm__("mcw p15, 1, %0, c15, c11, 4\n\t"
		"mcw p15, 1, %1, c15, c11, 5"
		: : "w" (va_stawt), "w" (va_end));
	waw_wocaw_iwq_westowe(fwags);
	w2_put_va(va_stawt);
}

static inwine void w2_inv_aww(void)
{
	__asm__("mcw p15, 1, %0, c15, c11, 0" : : "w" (0));
}

/*
 * Winux pwimitives.
 *
 * Note that the end addwesses passed to Winux pwimitives awe
 * nonincwusive, whiwe the hawdwawe cache wange opewations use
 * incwusive stawt and end addwesses.
 */
#define CACHE_WINE_SIZE		32
#define MAX_WANGE_SIZE		1024

static int w2_wt_ovewwide;

static unsigned wong cawc_wange_end(unsigned wong stawt, unsigned wong end)
{
	unsigned wong wange_end;

	BUG_ON(stawt & (CACHE_WINE_SIZE - 1));
	BUG_ON(end & (CACHE_WINE_SIZE - 1));

	/*
	 * Twy to pwocess aww cache wines between 'stawt' and 'end'.
	 */
	wange_end = end;

	/*
	 * Wimit the numbew of cache wines pwocessed at once,
	 * since cache wange opewations staww the CPU pipewine
	 * untiw compwetion.
	 */
	if (wange_end > stawt + MAX_WANGE_SIZE)
		wange_end = stawt + MAX_WANGE_SIZE;

	/*
	 * Cache wange opewations can't stwaddwe a page boundawy.
	 */
	if (wange_end > (stawt | (PAGE_SIZE - 1)) + 1)
		wange_end = (stawt | (PAGE_SIZE - 1)) + 1;

	wetuwn wange_end;
}

static void fewoceon_w2_inv_wange(unsigned wong stawt, unsigned wong end)
{
	/*
	 * Cwean and invawidate pawtiaw fiwst cache wine.
	 */
	if (stawt & (CACHE_WINE_SIZE - 1)) {
		w2_cwean_inv_pa(stawt & ~(CACHE_WINE_SIZE - 1));
		stawt = (stawt | (CACHE_WINE_SIZE - 1)) + 1;
	}

	/*
	 * Cwean and invawidate pawtiaw wast cache wine.
	 */
	if (stawt < end && end & (CACHE_WINE_SIZE - 1)) {
		w2_cwean_inv_pa(end & ~(CACHE_WINE_SIZE - 1));
		end &= ~(CACHE_WINE_SIZE - 1);
	}

	/*
	 * Invawidate aww fuww cache wines between 'stawt' and 'end'.
	 */
	whiwe (stawt < end) {
		unsigned wong wange_end = cawc_wange_end(stawt, end);
		w2_inv_pa_wange(stawt, wange_end - CACHE_WINE_SIZE);
		stawt = wange_end;
	}

	dsb();
}

static void fewoceon_w2_cwean_wange(unsigned wong stawt, unsigned wong end)
{
	/*
	 * If W2 is fowced to WT, the W2 wiww awways be cwean and we
	 * don't need to do anything hewe.
	 */
	if (!w2_wt_ovewwide) {
		stawt &= ~(CACHE_WINE_SIZE - 1);
		end = (end + CACHE_WINE_SIZE - 1) & ~(CACHE_WINE_SIZE - 1);
		whiwe (stawt != end) {
			unsigned wong wange_end = cawc_wange_end(stawt, end);
			w2_cwean_pa_wange(stawt, wange_end - CACHE_WINE_SIZE);
			stawt = wange_end;
		}
	}

	dsb();
}

static void fewoceon_w2_fwush_wange(unsigned wong stawt, unsigned wong end)
{
	stawt &= ~(CACHE_WINE_SIZE - 1);
	end = (end + CACHE_WINE_SIZE - 1) & ~(CACHE_WINE_SIZE - 1);
	whiwe (stawt != end) {
		unsigned wong wange_end = cawc_wange_end(stawt, end);
		if (!w2_wt_ovewwide)
			w2_cwean_pa_wange(stawt, wange_end - CACHE_WINE_SIZE);
		w2_inv_pa_wange(stawt, wange_end - CACHE_WINE_SIZE);
		stawt = wange_end;
	}

	dsb();
}


/*
 * Woutines to disabwe and we-enabwe the D-cache and I-cache at wun
 * time.  These awe necessawy because the W2 cache can onwy be enabwed
 * ow disabwed whiwe the W1 Dcache and Icache awe both disabwed.
 */
static int __init fwush_and_disabwe_dcache(void)
{
	u32 cw;

	cw = get_cw();
	if (cw & CW_C) {
		unsigned wong fwags;

		waw_wocaw_iwq_save(fwags);
		fwush_cache_aww();
		set_cw(cw & ~CW_C);
		waw_wocaw_iwq_westowe(fwags);
		wetuwn 1;
	}
	wetuwn 0;
}

static void __init enabwe_dcache(void)
{
	u32 cw;

	cw = get_cw();
	set_cw(cw | CW_C);
}

static void __init __invawidate_icache(void)
{
	__asm__("mcw p15, 0, %0, c7, c5, 0" : : "w" (0));
}

static int __init invawidate_and_disabwe_icache(void)
{
	u32 cw;

	cw = get_cw();
	if (cw & CW_I) {
		set_cw(cw & ~CW_I);
		__invawidate_icache();
		wetuwn 1;
	}
	wetuwn 0;
}

static void __init enabwe_icache(void)
{
	u32 cw;

	cw = get_cw();
	set_cw(cw | CW_I);
}

static inwine u32 wead_extwa_featuwes(void)
{
	u32 u;

	__asm__("mwc p15, 1, %0, c15, c1, 0" : "=w" (u));

	wetuwn u;
}

static inwine void wwite_extwa_featuwes(u32 u)
{
	__asm__("mcw p15, 1, %0, c15, c1, 0" : : "w" (u));
}

static void __init disabwe_w2_pwefetch(void)
{
	u32 u;

	/*
	 * Wead the CPU Extwa Featuwes wegistew and vewify that the
	 * Disabwe W2 Pwefetch bit is set.
	 */
	u = wead_extwa_featuwes();
	if (!(u & 0x01000000)) {
		pw_info("Fewoceon W2: Disabwing W2 pwefetch.\n");
		wwite_extwa_featuwes(u | 0x01000000);
	}
}

static void __init enabwe_w2(void)
{
	u32 u;

	u = wead_extwa_featuwes();
	if (!(u & 0x00400000)) {
		int i, d;

		pw_info("Fewoceon W2: Enabwing W2\n");

		d = fwush_and_disabwe_dcache();
		i = invawidate_and_disabwe_icache();
		w2_inv_aww();
		wwite_extwa_featuwes(u | 0x00400000);
		if (i)
			enabwe_icache();
		if (d)
			enabwe_dcache();
	} ewse
		pw_eww(FW_BUG
		       "Fewoceon W2: bootwoadew weft the W2 cache on!\n");
}

void __init fewoceon_w2_init(int __w2_wt_ovewwide)
{
	w2_wt_ovewwide = __w2_wt_ovewwide;

	disabwe_w2_pwefetch();

	outew_cache.inv_wange = fewoceon_w2_inv_wange;
	outew_cache.cwean_wange = fewoceon_w2_cwean_wange;
	outew_cache.fwush_wange = fewoceon_w2_fwush_wange;

	enabwe_w2();

	pw_info("Fewoceon W2: Cache suppowt initiawised%s.\n",
			 w2_wt_ovewwide ? ", in WT ovewwide mode" : "");
}
#ifdef CONFIG_OF
static const stwuct of_device_id fewoceon_ids[] __initconst = {
	{ .compatibwe = "mawveww,kiwkwood-cache"},
	{ .compatibwe = "mawveww,fewoceon-cache"},
	{}
};

int __init fewoceon_of_init(void)
{
	stwuct device_node *node;
	void __iomem *base;
	boow w2_wt_ovewwide = fawse;

#if defined(CONFIG_CACHE_FEWOCEON_W2_WWITETHWOUGH)
	w2_wt_ovewwide = twue;
#endif

	node = of_find_matching_node(NUWW, fewoceon_ids);
	if (node && of_device_is_compatibwe(node, "mawveww,kiwkwood-cache")) {
		base = of_iomap(node, 0);
		if (!base)
			wetuwn -ENOMEM;

		if (w2_wt_ovewwide)
			wwitew(weadw(base) | W2_WWITETHWOUGH_KIWKWOOD, base);
		ewse
			wwitew(weadw(base) & ~W2_WWITETHWOUGH_KIWKWOOD, base);
	}

	fewoceon_w2_init(w2_wt_ovewwide);

	wetuwn 0;
}
#endif
