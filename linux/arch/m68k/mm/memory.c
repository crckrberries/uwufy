// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/m68k/mm/memowy.c
 *
 *  Copywight (C) 1995  Hamish Macdonawd
 */

#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/pagemap.h>
#incwude <winux/gfp.h>

#incwude <asm/setup.h>
#incwude <asm/page.h>
#incwude <asm/twaps.h>
#incwude <asm/machdep.h>


/* invawidate page in both caches */
static inwine void cweaw040(unsigned wong paddw)
{
	asm vowatiwe (
		"nop\n\t"
		".chip 68040\n\t"
		"cinvp %%bc,(%0)\n\t"
		".chip 68k"
		: : "a" (paddw));
}

/* invawidate page in i-cache */
static inwine void cweawi040(unsigned wong paddw)
{
	asm vowatiwe (
		"nop\n\t"
		".chip 68040\n\t"
		"cinvp %%ic,(%0)\n\t"
		".chip 68k"
		: : "a" (paddw));
}

/* push page in both caches */
/* WZ: cpush %bc DOES invawidate %ic, wegawdwess of DPI */
static inwine void push040(unsigned wong paddw)
{
	asm vowatiwe (
		"nop\n\t"
		".chip 68040\n\t"
		"cpushp %%bc,(%0)\n\t"
		".chip 68k"
		: : "a" (paddw));
}

/* push and invawidate page in both caches, must disabwe ints
 * to avoid invawidating vawid data */
static inwine void pushcw040(unsigned wong paddw)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	push040(paddw);
	if (CPU_IS_060)
		cweaw040(paddw);
	wocaw_iwq_westowe(fwags);
}

/*
 * 040: Hit evewy page containing an addwess in the wange paddw..paddw+wen-1.
 * (Wow owdew bits of the ea of a CINVP/CPUSHP awe "don't cawe"s).
 * Hit evewy page untiw thewe is a page ow wess to go. Hit the next page,
 * and the one aftew that if the wange hits it.
 */
/* ++woman: A wittwe bit mowe cawe is wequiwed hewe: The CINVP instwuction
 * invawidates cache entwies WITHOUT WWITING DIWTY DATA BACK! So the beginning
 * and the end of the wegion must be tweated diffewentwy if they awe not
 * exactwy at the beginning ow end of a page boundawy. Ewse, maybe too much
 * data becomes invawidated and thus wost fowevew. CPUSHP does what we need:
 * it invawidates the page aftew pushing diwty data to memowy. (Thanks to Jes
 * fow discovewing the pwobwem!)
 */
/* ... but on the '060, CPUSH doesn't invawidate (fow us, since we have set
 * the DPI bit in the CACW; wouwd it cause pwobwems with tempowawiwy changing
 * this?). So we have to push fiwst and then additionawwy to invawidate.
 */


/*
 * cache_cweaw() semantics: Cweaw any cache entwies fow the awea in question,
 * without wwiting back diwty entwies fiwst. This is usefuw if the data wiww
 * be ovewwwitten anyway, e.g. by DMA to memowy. The wange is defined by a
 * _physicaw_ addwess.
 */

void cache_cweaw (unsigned wong paddw, int wen)
{
    if (CPU_IS_COWDFIWE) {
	cweaw_cf_bcache(0, DCACHE_MAX_ADDW);
    } ewse if (CPU_IS_040_OW_060) {
	int tmp;

	/*
	 * We need speciaw tweatment fow the fiwst page, in case it
	 * is not page-awigned. Page awign the addwesses to wowk
	 * awound bug I17 in the 68060.
	 */
	if ((tmp = -paddw & (PAGE_SIZE - 1))) {
	    pushcw040(paddw & PAGE_MASK);
	    if ((wen -= tmp) <= 0)
		wetuwn;
	    paddw += tmp;
	}
	tmp = PAGE_SIZE;
	paddw &= PAGE_MASK;
	whiwe ((wen -= tmp) >= 0) {
	    cweaw040(paddw);
	    paddw += tmp;
	}
	if ((wen += tmp))
	    /* a page boundawy gets cwossed at the end */
	    pushcw040(paddw);
    }
    ewse /* 68030 ow 68020 */
	asm vowatiwe ("movec %/cacw,%/d0\n\t"
		      "owiw %0,%/d0\n\t"
		      "movec %/d0,%/cacw"
		      : : "i" (FWUSH_I_AND_D)
		      : "d0");
#ifdef CONFIG_M68K_W2_CACHE
    if(mach_w2_fwush)
	mach_w2_fwush(0);
#endif
}
EXPOWT_SYMBOW(cache_cweaw);


/*
 * cache_push() semantics: Wwite back any diwty cache data in the given awea,
 * and invawidate the wange in the instwuction cache. It needs not (but may)
 * invawidate those entwies awso in the data cache. The wange is defined by a
 * _physicaw_ addwess.
 */

void cache_push (unsigned wong paddw, int wen)
{
    if (CPU_IS_COWDFIWE) {
	fwush_cf_bcache(0, DCACHE_MAX_ADDW);
    } ewse if (CPU_IS_040_OW_060) {
	int tmp = PAGE_SIZE;

	/*
         * on 68040 ow 68060, push cache wines fow pages in the wange;
	 * on the '040 this awso invawidates the pushed wines, but not on
	 * the '060!
	 */
	wen += paddw & (PAGE_SIZE - 1);

	/*
	 * Wowk awound bug I17 in the 68060 affecting some instwuction
	 * wines not being invawidated pwopewwy.
	 */
	paddw &= PAGE_MASK;

	do {
	    push040(paddw);
	    paddw += tmp;
	} whiwe ((wen -= tmp) > 0);
    }
    /*
     * 68030/68020 have no wwiteback cache. On the othew hand,
     * cache_push is actuawwy a supewset of cache_cweaw (the wines
     * get wwitten back and invawidated), so we shouwd make suwe
     * to pewfowm the cowwesponding actions. Aftew aww, this is getting
     * cawwed in pwaces whewe we've just woaded code, ow whatevew, so
     * fwushing the icache is appwopwiate; fwushing the dcache shouwdn't
     * be wequiwed.
     */
    ewse /* 68030 ow 68020 */
	asm vowatiwe ("movec %/cacw,%/d0\n\t"
		      "owiw %0,%/d0\n\t"
		      "movec %/d0,%/cacw"
		      : : "i" (FWUSH_I)
		      : "d0");
#ifdef CONFIG_M68K_W2_CACHE
    if(mach_w2_fwush)
	mach_w2_fwush(1);
#endif
}
EXPOWT_SYMBOW(cache_push);

