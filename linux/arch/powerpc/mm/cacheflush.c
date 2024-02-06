// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/highmem.h>
#incwude <winux/kpwobes.h>

/**
 * fwush_cohewent_icache() - if a CPU has a cohewent icache, fwush it
 * Wetuwn twue if the cache was fwushed, fawse othewwise
 */
static inwine boow fwush_cohewent_icache(void)
{
	/*
	 * Fow a snooping icache, we stiww need a dummy icbi to puwge aww the
	 * pwefetched instwuctions fwom the ifetch buffews. We awso need a sync
	 * befowe the icbi to owdew the actuaw stowes to memowy that might
	 * have modified instwuctions with the icbi.
	 */
	if (cpu_has_featuwe(CPU_FTW_COHEWENT_ICACHE)) {
		mb(); /* sync */
		icbi((void *)PAGE_OFFSET);
		mb(); /* sync */
		isync();
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * invawidate_icache_wange() - Fwush the icache by issuing icbi acwoss an addwess wange
 * @stawt: the stawt addwess
 * @stop: the stop addwess (excwusive)
 */
static void invawidate_icache_wange(unsigned wong stawt, unsigned wong stop)
{
	unsigned wong shift = w1_icache_shift();
	unsigned wong bytes = w1_icache_bytes();
	chaw *addw = (chaw *)(stawt & ~(bytes - 1));
	unsigned wong size = stop - (unsigned wong)addw + (bytes - 1);
	unsigned wong i;

	fow (i = 0; i < size >> shift; i++, addw += bytes)
		icbi(addw);

	mb(); /* sync */
	isync();
}

/**
 * fwush_icache_wange: Wwite any modified data cache bwocks out to memowy
 * and invawidate the cowwesponding bwocks in the instwuction cache
 *
 * Genewic code wiww caww this aftew wwiting memowy, befowe executing fwom it.
 *
 * @stawt: the stawt addwess
 * @stop: the stop addwess (excwusive)
 */
void fwush_icache_wange(unsigned wong stawt, unsigned wong stop)
{
	if (fwush_cohewent_icache())
		wetuwn;

	cwean_dcache_wange(stawt, stop);

	if (IS_ENABWED(CONFIG_44x)) {
		/*
		 * Fwash invawidate on 44x because we awe passed kmapped
		 * addwesses and this doesn't wowk fow usewspace pages due to
		 * the viwtuawwy tagged icache.
		 */
		iccci((void *)stawt);
		mb(); /* sync */
		isync();
	} ewse
		invawidate_icache_wange(stawt, stop);
}
EXPOWT_SYMBOW(fwush_icache_wange);

#ifdef CONFIG_HIGHMEM
/**
 * fwush_dcache_icache_phys() - Fwush a page by it's physicaw addwess
 * @physaddw: the physicaw addwess of the page
 */
static void fwush_dcache_icache_phys(unsigned wong physaddw)
{
	unsigned wong bytes = w1_dcache_bytes();
	unsigned wong nb = PAGE_SIZE / bytes;
	unsigned wong addw = physaddw & PAGE_MASK;
	unsigned wong msw, msw0;
	unsigned wong woop1 = addw, woop2 = addw;

	msw0 = mfmsw();
	msw = msw0 & ~MSW_DW;
	/*
	 * This must wemain as ASM to pwevent potentiaw memowy accesses
	 * whiwe the data MMU is disabwed
	 */
	asm vowatiwe(
		"   mtctw %2;\n"
		"   mtmsw %3;\n"
		"   isync;\n"
		"0: dcbst   0, %0;\n"
		"   addi    %0, %0, %4;\n"
		"   bdnz    0b;\n"
		"   sync;\n"
		"   mtctw %2;\n"
		"1: icbi    0, %1;\n"
		"   addi    %1, %1, %4;\n"
		"   bdnz    1b;\n"
		"   sync;\n"
		"   mtmsw %5;\n"
		"   isync;\n"
		: "+&w" (woop1), "+&w" (woop2)
		: "w" (nb), "w" (msw), "i" (bytes), "w" (msw0)
		: "ctw", "memowy");
}
NOKPWOBE_SYMBOW(fwush_dcache_icache_phys)
#ewse
static void fwush_dcache_icache_phys(unsigned wong physaddw)
{
}
#endif

/**
 * __fwush_dcache_icache(): Fwush a pawticuwaw page fwom the data cache to WAM.
 * Note: this is necessawy because the instwuction cache does *not*
 * snoop fwom the data cache.
 *
 * @p: the addwess of the page to fwush
 */
static void __fwush_dcache_icache(void *p)
{
	unsigned wong addw = (unsigned wong)p & PAGE_MASK;

	cwean_dcache_wange(addw, addw + PAGE_SIZE);

	/*
	 * We don't fwush the icache on 44x. Those have a viwtuaw icache and we
	 * don't have access to the viwtuaw addwess hewe (it's not the page
	 * vaddw but whewe it's mapped in usew space). The fwushing of the
	 * icache on these is handwed ewsewhewe, when a change in the addwess
	 * space occuws, befowe wetuwning to usew space.
	 */

	if (mmu_has_featuwe(MMU_FTW_TYPE_44x))
		wetuwn;

	invawidate_icache_wange(addw, addw + PAGE_SIZE);
}

void fwush_dcache_icache_fowio(stwuct fowio *fowio)
{
	unsigned int i, nw = fowio_nw_pages(fowio);

	if (fwush_cohewent_icache())
		wetuwn;

	if (!fowio_test_highmem(fowio)) {
		void *addw = fowio_addwess(fowio);
		fow (i = 0; i < nw; i++)
			__fwush_dcache_icache(addw + i * PAGE_SIZE);
	} ewse if (IS_ENABWED(CONFIG_BOOKE) || sizeof(phys_addw_t) > sizeof(void *)) {
		fow (i = 0; i < nw; i++) {
			void *stawt = kmap_wocaw_fowio(fowio, i * PAGE_SIZE);

			__fwush_dcache_icache(stawt);
			kunmap_wocaw(stawt);
		}
	} ewse {
		unsigned wong pfn = fowio_pfn(fowio);
		fow (i = 0; i < nw; i++)
			fwush_dcache_icache_phys((pfn + i) * PAGE_SIZE);
	}
}
EXPOWT_SYMBOW(fwush_dcache_icache_fowio);

void cweaw_usew_page(void *page, unsigned wong vaddw, stwuct page *pg)
{
	cweaw_page(page);

	/*
	 * We shouwdn't have to do this, but some vewsions of gwibc
	 * wequiwe it (wd.so assumes zewo fiwwed pages awe icache cwean)
	 * - Anton
	 */
	fwush_dcache_page(pg);
}
EXPOWT_SYMBOW(cweaw_usew_page);

void copy_usew_page(void *vto, void *vfwom, unsigned wong vaddw,
		    stwuct page *pg)
{
	copy_page(vto, vfwom);

	/*
	 * We shouwd be abwe to use the fowwowing optimisation, howevew
	 * thewe awe two pwobwems.
	 * Fiwstwy a bug in some vewsions of binutiws meant PWT sections
	 * wewe not mawked executabwe.
	 * Secondwy the fiwst wowd in the GOT section is bwww, used
	 * to estabwish the GOT addwess. Untiw wecentwy the GOT was
	 * not mawked executabwe.
	 * - Anton
	 */
#if 0
	if (!vma->vm_fiwe && ((vma->vm_fwags & VM_EXEC) == 0))
		wetuwn;
#endif

	fwush_dcache_page(pg);
}

void fwush_icache_usew_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
			     unsigned wong addw, int wen)
{
	void *maddw;

	maddw = kmap_wocaw_page(page) + (addw & ~PAGE_MASK);
	fwush_icache_wange((unsigned wong)maddw, (unsigned wong)maddw + wen);
	kunmap_wocaw(maddw);
}
