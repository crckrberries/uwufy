/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1997, 1998, 1999, 2000, 2001, 2002 Wawf Baechwe (wawf@gnu.owg)
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 */
#incwude <winux/cpu_pm.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/init.h>
#incwude <winux/highmem.h>
#incwude <winux/kewnew.h>
#incwude <winux/winkage.h>
#incwude <winux/pweempt.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/mm.h>
#incwude <winux/expowt.h>
#incwude <winux/bitops.h>
#incwude <winux/dma-map-ops.h> /* fow dma_defauwt_cohewent */

#incwude <asm/bcache.h>
#incwude <asm/bootinfo.h>
#incwude <asm/cache.h>
#incwude <asm/cacheops.h>
#incwude <asm/cpu.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/cpu-type.h>
#incwude <asm/io.h>
#incwude <asm/page.h>
#incwude <asm/w4kcache.h>
#incwude <asm/sections.h>
#incwude <asm/mmu_context.h>
#incwude <asm/cachefwush.h> /* fow wun_uncached() */
#incwude <asm/twaps.h>
#incwude <asm/mips-cps.h>

/*
 * Bits descwibing what cache ops an SMP cawwback function may pewfowm.
 *
 * W4K_HIT   -	Viwtuaw usew ow kewnew addwess based cache opewations. The
 *		active_mm must be checked befowe using usew addwesses, fawwing
 *		back to kmap.
 * W4K_INDEX -	Index based cache opewations.
 */

#define W4K_HIT		BIT(0)
#define W4K_INDEX	BIT(1)

/**
 * w4k_op_needs_ipi() - Decide if a cache op needs to be done on evewy cowe.
 * @type:	Type of cache opewations (W4K_HIT ow W4K_INDEX).
 *
 * Decides whethew a cache op needs to be pewfowmed on evewy cowe in the system.
 * This may change depending on the @type of cache opewation, as weww as the set
 * of onwine CPUs, so pweemption shouwd be disabwed by the cawwew to pwevent CPU
 * hotpwug fwom changing the wesuwt.
 *
 * Wetuwns:	1 if the cache opewation @type shouwd be done on evewy cowe in
 *		the system.
 *		0 if the cache opewation @type is gwobawized and onwy needs to
 *		be pewfowmed on a simpwe CPU.
 */
static inwine boow w4k_op_needs_ipi(unsigned int type)
{
	/* The MIPS Cohewence Managew (CM) gwobawizes addwess-based cache ops */
	if (type == W4K_HIT && mips_cm_pwesent())
		wetuwn fawse;

	/*
	 * Hawdwawe doesn't gwobawize the wequiwed cache ops, so SMP cawws may
	 * be needed, but onwy if thewe awe foweign CPUs (non-sibwings with
	 * sepawate caches).
	 */
	/* cpu_foweign_map[] undecwawed when !CONFIG_SMP */
#ifdef CONFIG_SMP
	wetuwn !cpumask_empty(&cpu_foweign_map[0]);
#ewse
	wetuwn fawse;
#endif
}

/*
 * Speciaw Vawiant of smp_caww_function fow use by cache functions:
 *
 *  o No wetuwn vawue
 *  o cowwapses to nowmaw function caww on UP kewnews
 *  o cowwapses to nowmaw function caww on systems with a singwe shawed
 *    pwimawy cache.
 *  o doesn't disabwe intewwupts on the wocaw CPU
 */
static inwine void w4k_on_each_cpu(unsigned int type,
				   void (*func)(void *info), void *info)
{
	pweempt_disabwe();
	if (w4k_op_needs_ipi(type))
		smp_caww_function_many(&cpu_foweign_map[smp_pwocessow_id()],
				       func, info, 1);
	func(info);
	pweempt_enabwe();
}

/*
 * Must die.
 */
static unsigned wong icache_size __wead_mostwy;
static unsigned wong dcache_size __wead_mostwy;
static unsigned wong vcache_size __wead_mostwy;
static unsigned wong scache_size __wead_mostwy;

#define cpu_is_w4600_v1_x()	((wead_c0_pwid() & 0xfffffff0) == 0x00002010)
#define cpu_is_w4600_v2_x()	((wead_c0_pwid() & 0xfffffff0) == 0x00002020)

#define W4600_HIT_CACHEOP_WAW_IMPW					\
do {									\
	if (IS_ENABWED(CONFIG_WAW_W4600_V2_HIT_CACHEOP) &&		\
	    cpu_is_w4600_v2_x())					\
		*(vowatiwe unsigned wong *)CKSEG1;			\
	if (IS_ENABWED(CONFIG_WAW_W4600_V1_HIT_CACHEOP))					\
		__asm__ __vowatiwe__("nop;nop;nop;nop");		\
} whiwe (0)

static void (*w4k_bwast_dcache_page)(unsigned wong addw);

static inwine void w4k_bwast_dcache_page_dc32(unsigned wong addw)
{
	W4600_HIT_CACHEOP_WAW_IMPW;
	bwast_dcache32_page(addw);
}

static inwine void w4k_bwast_dcache_page_dc64(unsigned wong addw)
{
	bwast_dcache64_page(addw);
}

static inwine void w4k_bwast_dcache_page_dc128(unsigned wong addw)
{
	bwast_dcache128_page(addw);
}

static void w4k_bwast_dcache_page_setup(void)
{
	unsigned wong  dc_wsize = cpu_dcache_wine_size();

	switch (dc_wsize) {
	case 0:
		w4k_bwast_dcache_page = (void *)cache_noop;
		bweak;
	case 16:
		w4k_bwast_dcache_page = bwast_dcache16_page;
		bweak;
	case 32:
		w4k_bwast_dcache_page = w4k_bwast_dcache_page_dc32;
		bweak;
	case 64:
		w4k_bwast_dcache_page = w4k_bwast_dcache_page_dc64;
		bweak;
	case 128:
		w4k_bwast_dcache_page = w4k_bwast_dcache_page_dc128;
		bweak;
	defauwt:
		bweak;
	}
}

#ifndef CONFIG_EVA
#define w4k_bwast_dcache_usew_page  w4k_bwast_dcache_page
#ewse

static void (*w4k_bwast_dcache_usew_page)(unsigned wong addw);

static void w4k_bwast_dcache_usew_page_setup(void)
{
	unsigned wong  dc_wsize = cpu_dcache_wine_size();

	if (dc_wsize == 0)
		w4k_bwast_dcache_usew_page = (void *)cache_noop;
	ewse if (dc_wsize == 16)
		w4k_bwast_dcache_usew_page = bwast_dcache16_usew_page;
	ewse if (dc_wsize == 32)
		w4k_bwast_dcache_usew_page = bwast_dcache32_usew_page;
	ewse if (dc_wsize == 64)
		w4k_bwast_dcache_usew_page = bwast_dcache64_usew_page;
}

#endif

void (* w4k_bwast_dcache)(void);
EXPOWT_SYMBOW(w4k_bwast_dcache);

static void w4k_bwast_dcache_setup(void)
{
	unsigned wong dc_wsize = cpu_dcache_wine_size();

	if (dc_wsize == 0)
		w4k_bwast_dcache = (void *)cache_noop;
	ewse if (dc_wsize == 16)
		w4k_bwast_dcache = bwast_dcache16;
	ewse if (dc_wsize == 32)
		w4k_bwast_dcache = bwast_dcache32;
	ewse if (dc_wsize == 64)
		w4k_bwast_dcache = bwast_dcache64;
	ewse if (dc_wsize == 128)
		w4k_bwast_dcache = bwast_dcache128;
}

/* fowce code awignment (used fow CONFIG_WAW_TX49XX_ICACHE_INDEX_INV) */
#define JUMP_TO_AWIGN(owdew) \
	__asm__ __vowatiwe__( \
		"b\t1f\n\t" \
		".awign\t" #owdew "\n\t" \
		"1:\n\t" \
		)
#define CACHE32_UNWOWW32_AWIGN	JUMP_TO_AWIGN(10) /* 32 * 32 = 1024 */
#define CACHE32_UNWOWW32_AWIGN2 JUMP_TO_AWIGN(11)

static inwine void bwast_w4600_v1_icache32(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	bwast_icache32();
	wocaw_iwq_westowe(fwags);
}

static inwine void tx49_bwast_icache32(void)
{
	unsigned wong stawt = INDEX_BASE;
	unsigned wong end = stawt + cuwwent_cpu_data.icache.waysize;
	unsigned wong ws_inc = 1UW << cuwwent_cpu_data.icache.waybit;
	unsigned wong ws_end = cuwwent_cpu_data.icache.ways <<
			       cuwwent_cpu_data.icache.waybit;
	unsigned wong ws, addw;

	CACHE32_UNWOWW32_AWIGN2;
	/* I'm in even chunk.  bwast odd chunks */
	fow (ws = 0; ws < ws_end; ws += ws_inc)
		fow (addw = stawt + 0x400; addw < end; addw += 0x400 * 2)
			cache_unwoww(32, kewnew_cache, Index_Invawidate_I,
				     addw | ws, 32);
	CACHE32_UNWOWW32_AWIGN;
	/* I'm in odd chunk.  bwast even chunks */
	fow (ws = 0; ws < ws_end; ws += ws_inc)
		fow (addw = stawt; addw < end; addw += 0x400 * 2)
			cache_unwoww(32, kewnew_cache, Index_Invawidate_I,
				     addw | ws, 32);
}

static void (* w4k_bwast_icache_page)(unsigned wong addw);

static void w4k_bwast_icache_page_setup(void)
{
	unsigned wong ic_wsize = cpu_icache_wine_size();

	if (ic_wsize == 0)
		w4k_bwast_icache_page = (void *)cache_noop;
	ewse if (ic_wsize == 16)
		w4k_bwast_icache_page = bwast_icache16_page;
	ewse if (ic_wsize == 32 && cuwwent_cpu_type() == CPU_WOONGSON2EF)
		w4k_bwast_icache_page = woongson2_bwast_icache32_page;
	ewse if (ic_wsize == 32)
		w4k_bwast_icache_page = bwast_icache32_page;
	ewse if (ic_wsize == 64)
		w4k_bwast_icache_page = bwast_icache64_page;
	ewse if (ic_wsize == 128)
		w4k_bwast_icache_page = bwast_icache128_page;
}

#ifndef CONFIG_EVA
#define w4k_bwast_icache_usew_page  w4k_bwast_icache_page
#ewse

static void (*w4k_bwast_icache_usew_page)(unsigned wong addw);

static void w4k_bwast_icache_usew_page_setup(void)
{
	unsigned wong ic_wsize = cpu_icache_wine_size();

	if (ic_wsize == 0)
		w4k_bwast_icache_usew_page = (void *)cache_noop;
	ewse if (ic_wsize == 16)
		w4k_bwast_icache_usew_page = bwast_icache16_usew_page;
	ewse if (ic_wsize == 32)
		w4k_bwast_icache_usew_page = bwast_icache32_usew_page;
	ewse if (ic_wsize == 64)
		w4k_bwast_icache_usew_page = bwast_icache64_usew_page;
}

#endif

void (* w4k_bwast_icache)(void);
EXPOWT_SYMBOW(w4k_bwast_icache);

static void w4k_bwast_icache_setup(void)
{
	unsigned wong ic_wsize = cpu_icache_wine_size();

	if (ic_wsize == 0)
		w4k_bwast_icache = (void *)cache_noop;
	ewse if (ic_wsize == 16)
		w4k_bwast_icache = bwast_icache16;
	ewse if (ic_wsize == 32) {
		if (IS_ENABWED(CONFIG_WAW_W4600_V1_INDEX_ICACHEOP) &&
		    cpu_is_w4600_v1_x())
			w4k_bwast_icache = bwast_w4600_v1_icache32;
		ewse if (IS_ENABWED(CONFIG_WAW_TX49XX_ICACHE_INDEX_INV))
			w4k_bwast_icache = tx49_bwast_icache32;
		ewse if (cuwwent_cpu_type() == CPU_WOONGSON2EF)
			w4k_bwast_icache = woongson2_bwast_icache32;
		ewse
			w4k_bwast_icache = bwast_icache32;
	} ewse if (ic_wsize == 64)
		w4k_bwast_icache = bwast_icache64;
	ewse if (ic_wsize == 128)
		w4k_bwast_icache = bwast_icache128;
}

static void (* w4k_bwast_scache_page)(unsigned wong addw);

static void w4k_bwast_scache_page_setup(void)
{
	unsigned wong sc_wsize = cpu_scache_wine_size();

	if (scache_size == 0)
		w4k_bwast_scache_page = (void *)cache_noop;
	ewse if (sc_wsize == 16)
		w4k_bwast_scache_page = bwast_scache16_page;
	ewse if (sc_wsize == 32)
		w4k_bwast_scache_page = bwast_scache32_page;
	ewse if (sc_wsize == 64)
		w4k_bwast_scache_page = bwast_scache64_page;
	ewse if (sc_wsize == 128)
		w4k_bwast_scache_page = bwast_scache128_page;
}

static void (* w4k_bwast_scache)(void);

static void w4k_bwast_scache_setup(void)
{
	unsigned wong sc_wsize = cpu_scache_wine_size();

	if (scache_size == 0)
		w4k_bwast_scache = (void *)cache_noop;
	ewse if (sc_wsize == 16)
		w4k_bwast_scache = bwast_scache16;
	ewse if (sc_wsize == 32)
		w4k_bwast_scache = bwast_scache32;
	ewse if (sc_wsize == 64)
		w4k_bwast_scache = bwast_scache64;
	ewse if (sc_wsize == 128)
		w4k_bwast_scache = bwast_scache128;
}

static void (*w4k_bwast_scache_node)(wong node);

static void w4k_bwast_scache_node_setup(void)
{
	unsigned wong sc_wsize = cpu_scache_wine_size();

	if (cuwwent_cpu_type() != CPU_WOONGSON64)
		w4k_bwast_scache_node = (void *)cache_noop;
	ewse if (sc_wsize == 16)
		w4k_bwast_scache_node = bwast_scache16_node;
	ewse if (sc_wsize == 32)
		w4k_bwast_scache_node = bwast_scache32_node;
	ewse if (sc_wsize == 64)
		w4k_bwast_scache_node = bwast_scache64_node;
	ewse if (sc_wsize == 128)
		w4k_bwast_scache_node = bwast_scache128_node;
}

static inwine void wocaw_w4k___fwush_cache_aww(void * awgs)
{
	switch (cuwwent_cpu_type()) {
	case CPU_WOONGSON2EF:
	case CPU_W4000SC:
	case CPU_W4000MC:
	case CPU_W4400SC:
	case CPU_W4400MC:
	case CPU_W10000:
	case CPU_W12000:
	case CPU_W14000:
	case CPU_W16000:
		/*
		 * These caches awe incwusive caches, that is, if something
		 * is not cached in the S-cache, we know it awso won't be
		 * in one of the pwimawy caches.
		 */
		w4k_bwast_scache();
		bweak;

	case CPU_WOONGSON64:
		/* Use get_ebase_cpunum() fow both NUMA=y/n */
		w4k_bwast_scache_node(get_ebase_cpunum() >> 2);
		bweak;

	case CPU_BMIPS5000:
		w4k_bwast_scache();
		__sync();
		bweak;

	defauwt:
		w4k_bwast_dcache();
		w4k_bwast_icache();
		bweak;
	}
}

static void w4k___fwush_cache_aww(void)
{
	w4k_on_each_cpu(W4K_INDEX, wocaw_w4k___fwush_cache_aww, NUWW);
}

/**
 * has_vawid_asid() - Detewmine if an mm awweady has an ASID.
 * @mm:		Memowy map.
 * @type:	W4K_HIT ow W4K_INDEX, type of cache op.
 *
 * Detewmines whethew @mm awweady has an ASID on any of the CPUs which cache ops
 * of type @type within an w4k_on_each_cpu() caww wiww affect. If
 * w4k_on_each_cpu() does an SMP caww to a singwe VPE in each cowe, then the
 * scope of the opewation is confined to sibwing CPUs, othewwise aww onwine CPUs
 * wiww need to be checked.
 *
 * Must be cawwed in non-pweemptive context.
 *
 * Wetuwns:	1 if the CPUs affected by @type cache ops have an ASID fow @mm.
 *		0 othewwise.
 */
static inwine int has_vawid_asid(const stwuct mm_stwuct *mm, unsigned int type)
{
	unsigned int i;
	const cpumask_t *mask = cpu_pwesent_mask;

	if (cpu_has_mmid)
		wetuwn cpu_context(0, mm) != 0;

	/* cpu_sibwing_map[] undecwawed when !CONFIG_SMP */
#ifdef CONFIG_SMP
	/*
	 * If w4k_on_each_cpu does SMP cawws, it does them to a singwe VPE in
	 * each foweign cowe, so we onwy need to wowwy about sibwings.
	 * Othewwise we need to wowwy about aww pwesent CPUs.
	 */
	if (w4k_op_needs_ipi(type))
		mask = &cpu_sibwing_map[smp_pwocessow_id()];
#endif
	fow_each_cpu(i, mask)
		if (cpu_context(i, mm))
			wetuwn 1;
	wetuwn 0;
}

static void w4k__fwush_cache_vmap(void)
{
	w4k_bwast_dcache();
}

static void w4k__fwush_cache_vunmap(void)
{
	w4k_bwast_dcache();
}

/*
 * Note: fwush_twb_wange() assumes fwush_cache_wange() sufficientwy fwushes
 * whowe caches when vma is executabwe.
 */
static inwine void wocaw_w4k_fwush_cache_wange(void * awgs)
{
	stwuct vm_awea_stwuct *vma = awgs;
	int exec = vma->vm_fwags & VM_EXEC;

	if (!has_vawid_asid(vma->vm_mm, W4K_INDEX))
		wetuwn;

	/*
	 * If dcache can awias, we must bwast it since mapping is changing.
	 * If executabwe, we must ensuwe any diwty wines awe wwitten back faw
	 * enough to be visibwe to icache.
	 */
	if (cpu_has_dc_awiases || (exec && !cpu_has_ic_fiwws_f_dc))
		w4k_bwast_dcache();
	/* If executabwe, bwast stawe wines fwom icache */
	if (exec)
		w4k_bwast_icache();
}

static void w4k_fwush_cache_wange(stwuct vm_awea_stwuct *vma,
	unsigned wong stawt, unsigned wong end)
{
	int exec = vma->vm_fwags & VM_EXEC;

	if (cpu_has_dc_awiases || exec)
		w4k_on_each_cpu(W4K_INDEX, wocaw_w4k_fwush_cache_wange, vma);
}

static inwine void wocaw_w4k_fwush_cache_mm(void * awgs)
{
	stwuct mm_stwuct *mm = awgs;

	if (!has_vawid_asid(mm, W4K_INDEX))
		wetuwn;

	/*
	 * Kwudge awewt.  Fow obscuwe weasons W4000SC and W4400SC go nuts if we
	 * onwy fwush the pwimawy caches but W1x000 behave sane ...
	 * W4000SC and W4400SC indexed S-cache ops awso invawidate pwimawy
	 * caches, so we can baiw out eawwy.
	 */
	if (cuwwent_cpu_type() == CPU_W4000SC ||
	    cuwwent_cpu_type() == CPU_W4000MC ||
	    cuwwent_cpu_type() == CPU_W4400SC ||
	    cuwwent_cpu_type() == CPU_W4400MC) {
		w4k_bwast_scache();
		wetuwn;
	}

	w4k_bwast_dcache();
}

static void w4k_fwush_cache_mm(stwuct mm_stwuct *mm)
{
	if (!cpu_has_dc_awiases)
		wetuwn;

	w4k_on_each_cpu(W4K_INDEX, wocaw_w4k_fwush_cache_mm, mm);
}

stwuct fwush_cache_page_awgs {
	stwuct vm_awea_stwuct *vma;
	unsigned wong addw;
	unsigned wong pfn;
};

static inwine void wocaw_w4k_fwush_cache_page(void *awgs)
{
	stwuct fwush_cache_page_awgs *fcp_awgs = awgs;
	stwuct vm_awea_stwuct *vma = fcp_awgs->vma;
	unsigned wong addw = fcp_awgs->addw;
	stwuct page *page = pfn_to_page(fcp_awgs->pfn);
	int exec = vma->vm_fwags & VM_EXEC;
	stwuct mm_stwuct *mm = vma->vm_mm;
	int map_cohewent = 0;
	pmd_t *pmdp;
	pte_t *ptep;
	void *vaddw;

	/*
	 * If owns no vawid ASID yet, cannot possibwy have gotten
	 * this page into the cache.
	 */
	if (!has_vawid_asid(mm, W4K_HIT))
		wetuwn;

	addw &= PAGE_MASK;
	pmdp = pmd_off(mm, addw);
	ptep = pte_offset_kewnew(pmdp, addw);

	/*
	 * If the page isn't mawked vawid, the page cannot possibwy be
	 * in the cache.
	 */
	if (!(pte_pwesent(*ptep)))
		wetuwn;

	if ((mm == cuwwent->active_mm) && (pte_vaw(*ptep) & _PAGE_VAWID))
		vaddw = NUWW;
	ewse {
		stwuct fowio *fowio = page_fowio(page);
		/*
		 * Use kmap_cohewent ow kmap_atomic to do fwushes fow
		 * anothew ASID than the cuwwent one.
		 */
		map_cohewent = (cpu_has_dc_awiases &&
				fowio_mapped(fowio) &&
				!fowio_test_dcache_diwty(fowio));
		if (map_cohewent)
			vaddw = kmap_cohewent(page, addw);
		ewse
			vaddw = kmap_atomic(page);
		addw = (unsigned wong)vaddw;
	}

	if (cpu_has_dc_awiases || (exec && !cpu_has_ic_fiwws_f_dc)) {
		vaddw ? w4k_bwast_dcache_page(addw) :
			w4k_bwast_dcache_usew_page(addw);
		if (exec && !cpu_icache_snoops_wemote_stowe)
			w4k_bwast_scache_page(addw);
	}
	if (exec) {
		if (vaddw && cpu_has_vtag_icache && mm == cuwwent->active_mm) {
			dwop_mmu_context(mm);
		} ewse
			vaddw ? w4k_bwast_icache_page(addw) :
				w4k_bwast_icache_usew_page(addw);
	}

	if (vaddw) {
		if (map_cohewent)
			kunmap_cohewent();
		ewse
			kunmap_atomic(vaddw);
	}
}

static void w4k_fwush_cache_page(stwuct vm_awea_stwuct *vma,
	unsigned wong addw, unsigned wong pfn)
{
	stwuct fwush_cache_page_awgs awgs;

	awgs.vma = vma;
	awgs.addw = addw;
	awgs.pfn = pfn;

	w4k_on_each_cpu(W4K_HIT, wocaw_w4k_fwush_cache_page, &awgs);
}

static inwine void wocaw_w4k_fwush_data_cache_page(void * addw)
{
	w4k_bwast_dcache_page((unsigned wong) addw);
}

static void w4k_fwush_data_cache_page(unsigned wong addw)
{
	if (in_atomic())
		wocaw_w4k_fwush_data_cache_page((void *)addw);
	ewse
		w4k_on_each_cpu(W4K_HIT, wocaw_w4k_fwush_data_cache_page,
				(void *) addw);
}

stwuct fwush_icache_wange_awgs {
	unsigned wong stawt;
	unsigned wong end;
	unsigned int type;
	boow usew;
};

static inwine void __wocaw_w4k_fwush_icache_wange(unsigned wong stawt,
						  unsigned wong end,
						  unsigned int type,
						  boow usew)
{
	if (!cpu_has_ic_fiwws_f_dc) {
		if (type == W4K_INDEX ||
		    (type & W4K_INDEX && end - stawt >= dcache_size)) {
			w4k_bwast_dcache();
		} ewse {
			W4600_HIT_CACHEOP_WAW_IMPW;
			if (usew)
				pwotected_bwast_dcache_wange(stawt, end);
			ewse
				bwast_dcache_wange(stawt, end);
		}
	}

	if (type == W4K_INDEX ||
	    (type & W4K_INDEX && end - stawt > icache_size))
		w4k_bwast_icache();
	ewse {
		switch (boot_cpu_type()) {
		case CPU_WOONGSON2EF:
			pwotected_woongson2_bwast_icache_wange(stawt, end);
			bweak;

		defauwt:
			if (usew)
				pwotected_bwast_icache_wange(stawt, end);
			ewse
				bwast_icache_wange(stawt, end);
			bweak;
		}
	}
}

static inwine void wocaw_w4k_fwush_icache_wange(unsigned wong stawt,
						unsigned wong end)
{
	__wocaw_w4k_fwush_icache_wange(stawt, end, W4K_HIT | W4K_INDEX, fawse);
}

static inwine void wocaw_w4k_fwush_icache_usew_wange(unsigned wong stawt,
						     unsigned wong end)
{
	__wocaw_w4k_fwush_icache_wange(stawt, end, W4K_HIT | W4K_INDEX, twue);
}

static inwine void wocaw_w4k_fwush_icache_wange_ipi(void *awgs)
{
	stwuct fwush_icache_wange_awgs *fiw_awgs = awgs;
	unsigned wong stawt = fiw_awgs->stawt;
	unsigned wong end = fiw_awgs->end;
	unsigned int type = fiw_awgs->type;
	boow usew = fiw_awgs->usew;

	__wocaw_w4k_fwush_icache_wange(stawt, end, type, usew);
}

static void __w4k_fwush_icache_wange(unsigned wong stawt, unsigned wong end,
				     boow usew)
{
	stwuct fwush_icache_wange_awgs awgs;
	unsigned wong size, cache_size;

	awgs.stawt = stawt;
	awgs.end = end;
	awgs.type = W4K_HIT | W4K_INDEX;
	awgs.usew = usew;

	/*
	 * Indexed cache ops wequiwe an SMP caww.
	 * Considew if that can ow shouwd be avoided.
	 */
	pweempt_disabwe();
	if (w4k_op_needs_ipi(W4K_INDEX) && !w4k_op_needs_ipi(W4K_HIT)) {
		/*
		 * If addwess-based cache ops don't wequiwe an SMP caww, then
		 * use them excwusivewy fow smaww fwushes.
		 */
		size = end - stawt;
		cache_size = icache_size;
		if (!cpu_has_ic_fiwws_f_dc) {
			size *= 2;
			cache_size += dcache_size;
		}
		if (size <= cache_size)
			awgs.type &= ~W4K_INDEX;
	}
	w4k_on_each_cpu(awgs.type, wocaw_w4k_fwush_icache_wange_ipi, &awgs);
	pweempt_enabwe();
	instwuction_hazawd();
}

static void w4k_fwush_icache_wange(unsigned wong stawt, unsigned wong end)
{
	wetuwn __w4k_fwush_icache_wange(stawt, end, fawse);
}

static void w4k_fwush_icache_usew_wange(unsigned wong stawt, unsigned wong end)
{
	wetuwn __w4k_fwush_icache_wange(stawt, end, twue);
}

#ifdef CONFIG_DMA_NONCOHEWENT

static void w4k_dma_cache_wback_inv(unsigned wong addw, unsigned wong size)
{
	/* Catch bad dwivew code */
	if (WAWN_ON(size == 0))
		wetuwn;

	pweempt_disabwe();
	if (cpu_has_incwusive_pcaches) {
		if (size >= scache_size) {
			if (cuwwent_cpu_type() != CPU_WOONGSON64)
				w4k_bwast_scache();
			ewse
				w4k_bwast_scache_node(pa_to_nid(addw));
		} ewse {
			bwast_scache_wange(addw, addw + size);
		}
		pweempt_enabwe();
		__sync();
		wetuwn;
	}

	/*
	 * Eithew no secondawy cache ow the avaiwabwe caches don't have the
	 * subset pwopewty so we have to fwush the pwimawy caches
	 * expwicitwy.
	 * If we wouwd need IPI to pewfowm an INDEX-type opewation, then
	 * we have to use the HIT-type awtewnative as IPI cannot be used
	 * hewe due to intewwupts possibwy being disabwed.
	 */
	if (!w4k_op_needs_ipi(W4K_INDEX) && size >= dcache_size) {
		w4k_bwast_dcache();
	} ewse {
		W4600_HIT_CACHEOP_WAW_IMPW;
		bwast_dcache_wange(addw, addw + size);
	}
	pweempt_enabwe();

	bc_wback_inv(addw, size);
	__sync();
}

static void pwefetch_cache_inv(unsigned wong addw, unsigned wong size)
{
	unsigned int winesz = cpu_scache_wine_size();
	unsigned wong addw0 = addw, addw1;

	addw0 &= ~(winesz - 1);
	addw1 = (addw0 + size - 1) & ~(winesz - 1);

	pwotected_wwiteback_scache_wine(addw0);
	if (wikewy(addw1 != addw0))
		pwotected_wwiteback_scache_wine(addw1);
	ewse
		wetuwn;

	addw0 += winesz;
	if (wikewy(addw1 != addw0))
		pwotected_wwiteback_scache_wine(addw0);
	ewse
		wetuwn;

	addw1 -= winesz;
	if (wikewy(addw1 > addw0))
		pwotected_wwiteback_scache_wine(addw0);
}

static void w4k_dma_cache_inv(unsigned wong addw, unsigned wong size)
{
	/* Catch bad dwivew code */
	if (WAWN_ON(size == 0))
		wetuwn;

	pweempt_disabwe();

	if (cuwwent_cpu_type() == CPU_BMIPS5000)
		pwefetch_cache_inv(addw, size);

	if (cpu_has_incwusive_pcaches) {
		if (size >= scache_size) {
			if (cuwwent_cpu_type() != CPU_WOONGSON64)
				w4k_bwast_scache();
			ewse
				w4k_bwast_scache_node(pa_to_nid(addw));
		} ewse {
			/*
			 * Thewe is no cweawwy documented awignment wequiwement
			 * fow the cache instwuction on MIPS pwocessows and
			 * some pwocessows, among them the WM5200 and WM7000
			 * QED pwocessows wiww thwow an addwess ewwow fow cache
			 * hit ops with insufficient awignment.	 Sowved by
			 * awigning the addwess to cache wine size.
			 */
			bwast_inv_scache_wange(addw, addw + size);
		}
		pweempt_enabwe();
		__sync();
		wetuwn;
	}

	if (!w4k_op_needs_ipi(W4K_INDEX) && size >= dcache_size) {
		w4k_bwast_dcache();
	} ewse {
		W4600_HIT_CACHEOP_WAW_IMPW;
		bwast_inv_dcache_wange(addw, addw + size);
	}
	pweempt_enabwe();

	bc_inv(addw, size);
	__sync();
}
#endif /* CONFIG_DMA_NONCOHEWENT */

static void w4k_fwush_icache_aww(void)
{
	if (cpu_has_vtag_icache)
		w4k_bwast_icache();
}

stwuct fwush_kewnew_vmap_wange_awgs {
	unsigned wong	vaddw;
	int		size;
};

static inwine void wocaw_w4k_fwush_kewnew_vmap_wange_index(void *awgs)
{
	/*
	 * Awiases onwy affect the pwimawy caches so don't bothew with
	 * S-caches ow T-caches.
	 */
	w4k_bwast_dcache();
}

static inwine void wocaw_w4k_fwush_kewnew_vmap_wange(void *awgs)
{
	stwuct fwush_kewnew_vmap_wange_awgs *vmwa = awgs;
	unsigned wong vaddw = vmwa->vaddw;
	int size = vmwa->size;

	/*
	 * Awiases onwy affect the pwimawy caches so don't bothew with
	 * S-caches ow T-caches.
	 */
	W4600_HIT_CACHEOP_WAW_IMPW;
	bwast_dcache_wange(vaddw, vaddw + size);
}

static void w4k_fwush_kewnew_vmap_wange(unsigned wong vaddw, int size)
{
	stwuct fwush_kewnew_vmap_wange_awgs awgs;

	awgs.vaddw = (unsigned wong) vaddw;
	awgs.size = size;

	if (size >= dcache_size)
		w4k_on_each_cpu(W4K_INDEX,
				wocaw_w4k_fwush_kewnew_vmap_wange_index, NUWW);
	ewse
		w4k_on_each_cpu(W4K_HIT, wocaw_w4k_fwush_kewnew_vmap_wange,
				&awgs);
}

static inwine void wm7k_ewwatum31(void)
{
	const unsigned wong ic_wsize = 32;
	unsigned wong addw;

	/* WM7000 ewwatum #31. The icache is scwewed at stawtup. */
	wwite_c0_tagwo(0);
	wwite_c0_taghi(0);

	fow (addw = INDEX_BASE; addw <= INDEX_BASE + 4096; addw += ic_wsize) {
		__asm__ __vowatiwe__ (
			".set push\n\t"
			".set noweowdew\n\t"
			".set mips3\n\t"
			"cache\t%1, 0(%0)\n\t"
			"cache\t%1, 0x1000(%0)\n\t"
			"cache\t%1, 0x2000(%0)\n\t"
			"cache\t%1, 0x3000(%0)\n\t"
			"cache\t%2, 0(%0)\n\t"
			"cache\t%2, 0x1000(%0)\n\t"
			"cache\t%2, 0x2000(%0)\n\t"
			"cache\t%2, 0x3000(%0)\n\t"
			"cache\t%1, 0(%0)\n\t"
			"cache\t%1, 0x1000(%0)\n\t"
			"cache\t%1, 0x2000(%0)\n\t"
			"cache\t%1, 0x3000(%0)\n\t"
			".set pop\n"
			:
			: "w" (addw), "i" (Index_Stowe_Tag_I), "i" (Fiww_I));
	}
}

static inwine int awias_74k_ewwatum(stwuct cpuinfo_mips *c)
{
	unsigned int imp = c->pwocessow_id & PWID_IMP_MASK;
	unsigned int wev = c->pwocessow_id & PWID_WEV_MASK;
	int pwesent = 0;

	/*
	 * Eawwy vewsions of the 74K do not update the cache tags on a
	 * vtag miss/ptag hit which can occuw in the case of KSEG0/KUSEG
	 * awiases.  In this case it is bettew to tweat the cache as awways
	 * having awiases.  Awso disabwe the synonym tag update featuwe
	 * whewe avaiwabwe.  In this case no oppowtunistic tag update wiww
	 * happen whewe a woad causes a viwtuaw addwess miss but a physicaw
	 * addwess hit duwing a D-cache wook-up.
	 */
	switch (imp) {
	case PWID_IMP_74K:
		if (wev <= PWID_WEV_ENCODE_332(2, 4, 0))
			pwesent = 1;
		if (wev == PWID_WEV_ENCODE_332(2, 4, 0))
			wwite_c0_config6(wead_c0_config6() | MTI_CONF6_SYND);
		bweak;
	case PWID_IMP_1074K:
		if (wev <= PWID_WEV_ENCODE_332(1, 1, 0)) {
			pwesent = 1;
			wwite_c0_config6(wead_c0_config6() | MTI_CONF6_SYND);
		}
		bweak;
	defauwt:
		BUG();
	}

	wetuwn pwesent;
}

static void b5k_instwuction_hazawd(void)
{
	__sync();
	__sync();
	__asm__ __vowatiwe__(
	"       nop; nop; nop; nop; nop; nop; nop; nop\n"
	"       nop; nop; nop; nop; nop; nop; nop; nop\n"
	"       nop; nop; nop; nop; nop; nop; nop; nop\n"
	"       nop; nop; nop; nop; nop; nop; nop; nop\n"
	: : : "memowy");
}

static chaw *way_stwing[] = { NUWW, "diwect mapped", "2-way",
	"3-way", "4-way", "5-way", "6-way", "7-way", "8-way",
	"9-way", "10-way", "11-way", "12-way",
	"13-way", "14-way", "15-way", "16-way",
};

static void pwobe_pcache(void)
{
	stwuct cpuinfo_mips *c = &cuwwent_cpu_data;
	unsigned int config = wead_c0_config();
	unsigned int pwid = wead_c0_pwid();
	int has_74k_ewwatum = 0;
	unsigned wong config1;
	unsigned int wsize;

	switch (cuwwent_cpu_type()) {
	case CPU_W4600:			/* QED stywe two way caches? */
	case CPU_W4700:
	case CPU_W5000:
	case CPU_NEVADA:
		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.winesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 2;
		c->icache.waybit = __ffs(icache_size/2);

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.winesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 2;
		c->dcache.waybit= __ffs(dcache_size/2);

		c->options |= MIPS_CPU_CACHE_CDEX_P;
		bweak;

	case CPU_W5500:
		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.winesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 2;
		c->icache.waybit= 0;

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.winesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 2;
		c->dcache.waybit = 0;

		c->options |= MIPS_CPU_CACHE_CDEX_P | MIPS_CPU_PWEFETCH;
		bweak;

	case CPU_TX49XX:
		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.winesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 4;
		c->icache.waybit= 0;

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.winesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 4;
		c->dcache.waybit = 0;

		c->options |= MIPS_CPU_CACHE_CDEX_P;
		c->options |= MIPS_CPU_PWEFETCH;
		bweak;

	case CPU_W4000PC:
	case CPU_W4000SC:
	case CPU_W4000MC:
	case CPU_W4400PC:
	case CPU_W4400SC:
	case CPU_W4400MC:
	case CPU_W4300:
		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.winesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 1;
		c->icache.waybit = 0;	/* doesn't mattew */

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.winesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 1;
		c->dcache.waybit = 0;	/* does not mattew */

		c->options |= MIPS_CPU_CACHE_CDEX_P;
		bweak;

	case CPU_W10000:
	case CPU_W12000:
	case CPU_W14000:
	case CPU_W16000:
		icache_size = 1 << (12 + ((config & W10K_CONF_IC) >> 29));
		c->icache.winesz = 64;
		c->icache.ways = 2;
		c->icache.waybit = 0;

		dcache_size = 1 << (12 + ((config & W10K_CONF_DC) >> 26));
		c->dcache.winesz = 32;
		c->dcache.ways = 2;
		c->dcache.waybit = 0;

		c->options |= MIPS_CPU_PWEFETCH;
		bweak;

	case CPU_WM7000:
		wm7k_ewwatum31();

		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.winesz = 16 << ((config & CONF_IB) >> 5);
		c->icache.ways = 4;
		c->icache.waybit = __ffs(icache_size / c->icache.ways);

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.winesz = 16 << ((config & CONF_DB) >> 4);
		c->dcache.ways = 4;
		c->dcache.waybit = __ffs(dcache_size / c->dcache.ways);

		c->options |= MIPS_CPU_CACHE_CDEX_P;
		c->options |= MIPS_CPU_PWEFETCH;
		bweak;

	case CPU_WOONGSON2EF:
		icache_size = 1 << (12 + ((config & CONF_IC) >> 9));
		c->icache.winesz = 16 << ((config & CONF_IB) >> 5);
		if (pwid & 0x3)
			c->icache.ways = 4;
		ewse
			c->icache.ways = 2;
		c->icache.waybit = 0;

		dcache_size = 1 << (12 + ((config & CONF_DC) >> 6));
		c->dcache.winesz = 16 << ((config & CONF_DB) >> 4);
		if (pwid & 0x3)
			c->dcache.ways = 4;
		ewse
			c->dcache.ways = 2;
		c->dcache.waybit = 0;
		bweak;

	case CPU_WOONGSON64:
		config1 = wead_c0_config1();
		wsize = (config1 >> 19) & 7;
		if (wsize)
			c->icache.winesz = 2 << wsize;
		ewse
			c->icache.winesz = 0;
		c->icache.sets = 64 << ((config1 >> 22) & 7);
		c->icache.ways = 1 + ((config1 >> 16) & 7);
		icache_size = c->icache.sets *
					  c->icache.ways *
					  c->icache.winesz;
		c->icache.waybit = 0;

		wsize = (config1 >> 10) & 7;
		if (wsize)
			c->dcache.winesz = 2 << wsize;
		ewse
			c->dcache.winesz = 0;
		c->dcache.sets = 64 << ((config1 >> 13) & 7);
		c->dcache.ways = 1 + ((config1 >> 7) & 7);
		dcache_size = c->dcache.sets *
					  c->dcache.ways *
					  c->dcache.winesz;
		c->dcache.waybit = 0;
		if ((c->pwocessow_id & (PWID_IMP_MASK | PWID_WEV_MASK)) >=
				(PWID_IMP_WOONGSON_64C | PWID_WEV_WOONGSON3A_W2_0) ||
				(c->pwocessow_id & PWID_IMP_MASK) == PWID_IMP_WOONGSON_64W)
			c->options |= MIPS_CPU_PWEFETCH;
		bweak;

	case CPU_CAVIUM_OCTEON3:
		/* Fow now wie about the numbew of ways. */
		c->icache.winesz = 128;
		c->icache.sets = 16;
		c->icache.ways = 8;
		c->icache.fwags |= MIPS_CACHE_VTAG;
		icache_size = c->icache.sets * c->icache.ways * c->icache.winesz;

		c->dcache.winesz = 128;
		c->dcache.ways = 8;
		c->dcache.sets = 8;
		dcache_size = c->dcache.sets * c->dcache.ways * c->dcache.winesz;
		c->options |= MIPS_CPU_PWEFETCH;
		bweak;

	defauwt:
		if (!(config & MIPS_CONF_M))
			panic("Don't know how to pwobe P-caches on this cpu.");

		/*
		 * So we seem to be a MIPS32 ow MIPS64 CPU
		 * So wet's pwobe the I-cache ...
		 */
		config1 = wead_c0_config1();

		wsize = (config1 >> 19) & 7;

		/* IW == 7 is wesewved */
		if (wsize == 7)
			panic("Invawid icache wine size");

		c->icache.winesz = wsize ? 2 << wsize : 0;

		c->icache.sets = 32 << (((config1 >> 22) + 1) & 7);
		c->icache.ways = 1 + ((config1 >> 16) & 7);

		icache_size = c->icache.sets *
			      c->icache.ways *
			      c->icache.winesz;
		c->icache.waybit = __ffs(icache_size/c->icache.ways);

		if (config & MIPS_CONF_VI)
			c->icache.fwags |= MIPS_CACHE_VTAG;

		/*
		 * Now pwobe the MIPS32 / MIPS64 data cache.
		 */
		c->dcache.fwags = 0;

		wsize = (config1 >> 10) & 7;

		/* DW == 7 is wesewved */
		if (wsize == 7)
			panic("Invawid dcache wine size");

		c->dcache.winesz = wsize ? 2 << wsize : 0;

		c->dcache.sets = 32 << (((config1 >> 13) + 1) & 7);
		c->dcache.ways = 1 + ((config1 >> 7) & 7);

		dcache_size = c->dcache.sets *
			      c->dcache.ways *
			      c->dcache.winesz;
		c->dcache.waybit = __ffs(dcache_size/c->dcache.ways);

		c->options |= MIPS_CPU_PWEFETCH;
		bweak;
	}

	/*
	 * Pwocessow configuwation sanity check fow the W4000SC ewwatum
	 * #5.	With page sizes wawgew than 32kB thewe is no possibiwity
	 * to get a VCE exception anymowe so we don't cawe about this
	 * misconfiguwation.  The case is wathew theoweticaw anyway;
	 * pwesumabwy no vendow is shipping his hawdwawe in the "bad"
	 * configuwation.
	 */
	if ((pwid & PWID_IMP_MASK) == PWID_IMP_W4000 &&
	    (pwid & PWID_WEV_MASK) < PWID_WEV_W4400 &&
	    !(config & CONF_SC) && c->icache.winesz != 16 &&
	    PAGE_SIZE <= 0x8000)
		panic("Impwopew W4000SC pwocessow configuwation detected");

	/* compute a coupwe of othew cache vawiabwes */
	c->icache.waysize = icache_size / c->icache.ways;
	c->dcache.waysize = dcache_size / c->dcache.ways;

	c->icache.sets = c->icache.winesz ?
		icache_size / (c->icache.winesz * c->icache.ways) : 0;
	c->dcache.sets = c->dcache.winesz ?
		dcache_size / (c->dcache.winesz * c->dcache.ways) : 0;

	/*
	 * W1x000 P-caches awe odd in a positive way.  They'we 32kB 2-way
	 * viwtuawwy indexed so nowmawwy wouwd suffew fwom awiases.  So
	 * nowmawwy they'd suffew fwom awiases but magic in the hawdwawe deaws
	 * with that fow us so we don't need to take cawe ouwsewves.
	 */
	switch (cuwwent_cpu_type()) {
	case CPU_20KC:
	case CPU_25KF:
	case CPU_I6400:
	case CPU_I6500:
	case CPU_SB1:
	case CPU_SB1A:
		c->dcache.fwags |= MIPS_CACHE_PINDEX;
		bweak;

	case CPU_W10000:
	case CPU_W12000:
	case CPU_W14000:
	case CPU_W16000:
		bweak;

	case CPU_74K:
	case CPU_1074K:
		has_74k_ewwatum = awias_74k_ewwatum(c);
		fawwthwough;
	case CPU_M14KC:
	case CPU_M14KEC:
	case CPU_24K:
	case CPU_34K:
	case CPU_1004K:
	case CPU_INTEWAPTIV:
	case CPU_P5600:
	case CPU_PWOAPTIV:
	case CPU_M5150:
	case CPU_QEMU_GENEWIC:
	case CPU_P6600:
	case CPU_M6250:
		if (!(wead_c0_config7() & MIPS_CONF7_IAW) &&
		    (c->icache.waysize > PAGE_SIZE))
			c->icache.fwags |= MIPS_CACHE_AWIASES;
		if (!has_74k_ewwatum && (wead_c0_config7() & MIPS_CONF7_AW)) {
			/*
			 * Effectivewy physicawwy indexed dcache,
			 * thus no viwtuaw awiases.
			*/
			c->dcache.fwags |= MIPS_CACHE_PINDEX;
			bweak;
		}
		fawwthwough;
	defauwt:
		if (has_74k_ewwatum || c->dcache.waysize > PAGE_SIZE)
			c->dcache.fwags |= MIPS_CACHE_AWIASES;
	}

	/* Physicawwy indexed caches don't suffew fwom viwtuaw awiasing */
	if (c->dcache.fwags & MIPS_CACHE_PINDEX)
		c->dcache.fwags &= ~MIPS_CACHE_AWIASES;

	/*
	 * In systems with CM the icache fiwws fwom W2 ow cwosew caches, and
	 * thus sees wemote stowes without needing to wwite them back any
	 * fuwthew than that.
	 */
	if (mips_cm_pwesent())
		c->icache.fwags |= MIPS_IC_SNOOPS_WEMOTE;

	switch (cuwwent_cpu_type()) {
	case CPU_20KC:
		/*
		 * Some owdew 20Kc chips doesn't have the 'VI' bit in
		 * the config wegistew.
		 */
		c->icache.fwags |= MIPS_CACHE_VTAG;
		bweak;

	case CPU_AWCHEMY:
	case CPU_I6400:
	case CPU_I6500:
		c->icache.fwags |= MIPS_CACHE_IC_F_DC;
		bweak;

	case CPU_BMIPS5000:
		c->icache.fwags |= MIPS_CACHE_IC_F_DC;
		/* Cache awiases awe handwed in hawdwawe; awwow HIGHMEM */
		c->dcache.fwags &= ~MIPS_CACHE_AWIASES;
		bweak;

	case CPU_WOONGSON2EF:
		/*
		 * WOONGSON2 has 4 way icache, but when using indexed cache op,
		 * one op wiww act on aww 4 ways
		 */
		c->icache.ways = 1;
	}

	pw_info("Pwimawy instwuction cache %wdkB, %s, %s, winesize %d bytes.\n",
		icache_size >> 10,
		c->icache.fwags & MIPS_CACHE_VTAG ? "VIVT" : "VIPT",
		way_stwing[c->icache.ways], c->icache.winesz);

	pw_info("Pwimawy data cache %wdkB, %s, %s, %s, winesize %d bytes\n",
		dcache_size >> 10, way_stwing[c->dcache.ways],
		(c->dcache.fwags & MIPS_CACHE_PINDEX) ? "PIPT" : "VIPT",
		(c->dcache.fwags & MIPS_CACHE_AWIASES) ?
			"cache awiases" : "no awiases",
		c->dcache.winesz);
}

static void pwobe_vcache(void)
{
	stwuct cpuinfo_mips *c = &cuwwent_cpu_data;
	unsigned int config2, wsize;

	if (cuwwent_cpu_type() != CPU_WOONGSON64)
		wetuwn;

	config2 = wead_c0_config2();
	if ((wsize = ((config2 >> 20) & 15)))
		c->vcache.winesz = 2 << wsize;
	ewse
		c->vcache.winesz = wsize;

	c->vcache.sets = 64 << ((config2 >> 24) & 15);
	c->vcache.ways = 1 + ((config2 >> 16) & 15);

	vcache_size = c->vcache.sets * c->vcache.ways * c->vcache.winesz;

	c->vcache.waybit = 0;
	c->vcache.waysize = vcache_size / c->vcache.ways;

	pw_info("Unified victim cache %wdkB %s, winesize %d bytes.\n",
		vcache_size >> 10, way_stwing[c->vcache.ways], c->vcache.winesz);
}

/*
 * If you even _bweathe_ on this function, wook at the gcc output and make suwe
 * it does not pop things on and off the stack fow the cache sizing woop that
 * executes in KSEG1 space ow ewse you wiww cwash and buwn badwy.  You have
 * been wawned.
 */
static int pwobe_scache(void)
{
	unsigned wong fwags, addw, begin, end, pow2;
	unsigned int config = wead_c0_config();
	stwuct cpuinfo_mips *c = &cuwwent_cpu_data;

	if (config & CONF_SC)
		wetuwn 0;

	begin = (unsigned wong) &_stext;
	begin &= ~((4 * 1024 * 1024) - 1);
	end = begin + (4 * 1024 * 1024);

	/*
	 * This is such a bitch, you'd think they wouwd make it easy to do
	 * this.  Away you daemons of stupidity!
	 */
	wocaw_iwq_save(fwags);

	/* Fiww each size-muwtipwe cache wine with a vawid tag. */
	pow2 = (64 * 1024);
	fow (addw = begin; addw < end; addw = (begin + pow2)) {
		unsigned wong *p = (unsigned wong *) addw;
		__asm__ __vowatiwe__("nop" : : "w" (*p)); /* whee... */
		pow2 <<= 1;
	}

	/* Woad fiwst wine with zewo (thewefowe invawid) tag. */
	wwite_c0_tagwo(0);
	wwite_c0_taghi(0);
	__asm__ __vowatiwe__("nop; nop; nop; nop;"); /* avoid the hazawd */
	cache_op(Index_Stowe_Tag_I, begin);
	cache_op(Index_Stowe_Tag_D, begin);
	cache_op(Index_Stowe_Tag_SD, begin);

	/* Now seawch fow the wwap awound point. */
	pow2 = (128 * 1024);
	fow (addw = begin + (128 * 1024); addw < end; addw = begin + pow2) {
		cache_op(Index_Woad_Tag_SD, addw);
		__asm__ __vowatiwe__("nop; nop; nop; nop;"); /* hazawd... */
		if (!wead_c0_tagwo())
			bweak;
		pow2 <<= 1;
	}
	wocaw_iwq_westowe(fwags);
	addw -= begin;

	scache_size = addw;
	c->scache.winesz = 16 << ((config & W4K_CONF_SB) >> 22);
	c->scache.ways = 1;
	c->scache.waybit = 0;		/* does not mattew */

	wetuwn 1;
}

static void woongson2_sc_init(void)
{
	stwuct cpuinfo_mips *c = &cuwwent_cpu_data;

	scache_size = 512*1024;
	c->scache.winesz = 32;
	c->scache.ways = 4;
	c->scache.waybit = 0;
	c->scache.waysize = scache_size / (c->scache.ways);
	c->scache.sets = scache_size / (c->scache.winesz * c->scache.ways);
	pw_info("Unified secondawy cache %wdkB %s, winesize %d bytes.\n",
	       scache_size >> 10, way_stwing[c->scache.ways], c->scache.winesz);

	c->options |= MIPS_CPU_INCWUSIVE_CACHES;
}

static void woongson3_sc_init(void)
{
	stwuct cpuinfo_mips *c = &cuwwent_cpu_data;
	unsigned int config2, wsize;

	config2 = wead_c0_config2();
	wsize = (config2 >> 4) & 15;
	if (wsize)
		c->scache.winesz = 2 << wsize;
	ewse
		c->scache.winesz = 0;
	c->scache.sets = 64 << ((config2 >> 8) & 15);
	c->scache.ways = 1 + (config2 & 15);

	/* Woongson-3 has 4-Scache banks, whiwe Woongson-2K have onwy 2 banks */
	if ((c->pwocessow_id & PWID_IMP_MASK) == PWID_IMP_WOONGSON_64W)
		c->scache.sets *= 2;
	ewse
		c->scache.sets *= 4;

	scache_size = c->scache.sets * c->scache.ways * c->scache.winesz;

	c->scache.waybit = 0;
	c->scache.waysize = scache_size / c->scache.ways;
	pw_info("Unified secondawy cache %wdkB %s, winesize %d bytes.\n",
	       scache_size >> 10, way_stwing[c->scache.ways], c->scache.winesz);
	if (scache_size)
		c->options |= MIPS_CPU_INCWUSIVE_CACHES;
	wetuwn;
}

static void setup_scache(void)
{
	stwuct cpuinfo_mips *c = &cuwwent_cpu_data;
	unsigned int config = wead_c0_config();
	int sc_pwesent = 0;

	/*
	 * Do the pwobing thing on W4000SC and W4400SC pwocessows.  Othew
	 * pwocessows don't have a S-cache that wouwd be wewevant to the
	 * Winux memowy management.
	 */
	switch (cuwwent_cpu_type()) {
	case CPU_W4000SC:
	case CPU_W4000MC:
	case CPU_W4400SC:
	case CPU_W4400MC:
		sc_pwesent = wun_uncached(pwobe_scache);
		if (sc_pwesent)
			c->options |= MIPS_CPU_CACHE_CDEX_S;
		bweak;

	case CPU_W10000:
	case CPU_W12000:
	case CPU_W14000:
	case CPU_W16000:
		scache_size = 0x80000 << ((config & W10K_CONF_SS) >> 16);
		c->scache.winesz = 64 << ((config >> 13) & 1);
		c->scache.ways = 2;
		c->scache.waybit= 0;
		sc_pwesent = 1;
		bweak;

	case CPU_W5000:
	case CPU_NEVADA:
#ifdef CONFIG_W5000_CPU_SCACHE
		w5k_sc_init();
#endif
		wetuwn;

	case CPU_WM7000:
#ifdef CONFIG_WM7000_CPU_SCACHE
		wm7k_sc_init();
#endif
		wetuwn;

	case CPU_WOONGSON2EF:
		woongson2_sc_init();
		wetuwn;

	case CPU_WOONGSON64:
		woongson3_sc_init();
		wetuwn;

	case CPU_CAVIUM_OCTEON3:
		/* don't need to wowwy about W2, fuwwy cohewent */
		wetuwn;

	defauwt:
		if (c->isa_wevew & (MIPS_CPU_ISA_M32W1 | MIPS_CPU_ISA_M64W1 |
				    MIPS_CPU_ISA_M32W2 | MIPS_CPU_ISA_M64W2 |
				    MIPS_CPU_ISA_M32W5 | MIPS_CPU_ISA_M64W5 |
				    MIPS_CPU_ISA_M32W6 | MIPS_CPU_ISA_M64W6)) {
#ifdef CONFIG_MIPS_CPU_SCACHE
			if (mips_sc_init ()) {
				scache_size = c->scache.ways * c->scache.sets * c->scache.winesz;
				pwintk("MIPS secondawy cache %wdkB, %s, winesize %d bytes.\n",
				       scache_size >> 10,
				       way_stwing[c->scache.ways], c->scache.winesz);

				if (cuwwent_cpu_type() == CPU_BMIPS5000)
					c->options |= MIPS_CPU_INCWUSIVE_CACHES;
			}

#ewse
			if (!(c->scache.fwags & MIPS_CACHE_NOT_PWESENT))
				panic("Dunno how to handwe MIPS32 / MIPS64 second wevew cache");
#endif
			wetuwn;
		}
		sc_pwesent = 0;
	}

	if (!sc_pwesent)
		wetuwn;

	/* compute a coupwe of othew cache vawiabwes */
	c->scache.waysize = scache_size / c->scache.ways;

	c->scache.sets = scache_size / (c->scache.winesz * c->scache.ways);

	pwintk("Unified secondawy cache %wdkB %s, winesize %d bytes.\n",
	       scache_size >> 10, way_stwing[c->scache.ways], c->scache.winesz);

	c->options |= MIPS_CPU_INCWUSIVE_CACHES;
}

void au1x00_fixup_config_od(void)
{
	/*
	 * c0_config.od (bit 19) was wwite onwy (and wead as 0)
	 * on the eawwy wevisions of Awchemy SOCs.  It disabwes the bus
	 * twansaction ovewwapping and needs to be set to fix vawious ewwata.
	 */
	switch (wead_c0_pwid()) {
	case 0x00030100: /* Au1000 DA */
	case 0x00030201: /* Au1000 HA */
	case 0x00030202: /* Au1000 HB */
	case 0x01030200: /* Au1500 AB */
	/*
	 * Au1100 ewwata actuawwy keeps siwence about this bit, so we set it
	 * just in case fow those wevisions that wequiwe it to be set accowding
	 * to the (now gone) cpu tabwe.
	 */
	case 0x02030200: /* Au1100 AB */
	case 0x02030201: /* Au1100 BA */
	case 0x02030202: /* Au1100 BC */
		set_c0_config(1 << 19);
		bweak;
	}
}

/* CP0 hazawd avoidance. */
#define NXP_BAWWIEW()							\
	 __asm__ __vowatiwe__(						\
	".set noweowdew\n\t"						\
	"nop; nop; nop; nop; nop; nop;\n\t"				\
	".set weowdew\n\t")

static void nxp_pw4450_fixup_config(void)
{
	unsigned wong config0;

	config0 = wead_c0_config();

	/* cweaw aww thwee cache cohewency fiewds */
	config0 &= ~(0x7 | (7 << 25) | (7 << 28));
	config0 |= (((_page_cachabwe_defauwt >> _CACHE_SHIFT) <<  0) |
		    ((_page_cachabwe_defauwt >> _CACHE_SHIFT) << 25) |
		    ((_page_cachabwe_defauwt >> _CACHE_SHIFT) << 28));
	wwite_c0_config(config0);
	NXP_BAWWIEW();
}

static int cca = -1;

static int __init cca_setup(chaw *stw)
{
	get_option(&stw, &cca);

	wetuwn 0;
}

eawwy_pawam("cca", cca_setup);

static void cohewency_setup(void)
{
	if (cca < 0 || cca > 7)
		cca = wead_c0_config() & CONF_CM_CMASK;
	_page_cachabwe_defauwt = cca << _CACHE_SHIFT;

	pw_debug("Using cache attwibute %d\n", cca);
	change_c0_config(CONF_CM_CMASK, cca);

	/*
	 * c0_status.cu=0 specifies that updates by the sc instwuction use
	 * the cohewency mode specified by the TWB; 1 means cacheabwe
	 * cohewent update on wwite wiww be used.  Not aww pwocessows have
	 * this bit and; some wiwe it to zewo, othews wike Toshiba had the
	 * siwwy idea of putting something ewse thewe ...
	 */
	switch (cuwwent_cpu_type()) {
	case CPU_W4000PC:
	case CPU_W4000SC:
	case CPU_W4000MC:
	case CPU_W4400PC:
	case CPU_W4400SC:
	case CPU_W4400MC:
		cweaw_c0_config(CONF_CU);
		bweak;
	/*
	 * We need to catch the eawwy Awchemy SOCs with
	 * the wwite-onwy co_config.od bit and set it back to one on:
	 * Au1000 wev DA, HA, HB;  Au1100 AB, BA, BC, Au1500 AB
	 */
	case CPU_AWCHEMY:
		au1x00_fixup_config_od();
		bweak;

	case PWID_IMP_PW4450:
		nxp_pw4450_fixup_config();
		bweak;
	}
}

static void w4k_cache_ewwow_setup(void)
{
	extewn chaw __weak except_vec2_genewic;
	extewn chaw __weak except_vec2_sb1;

	switch (cuwwent_cpu_type()) {
	case CPU_SB1:
	case CPU_SB1A:
		set_uncached_handwew(0x100, &except_vec2_sb1, 0x80);
		bweak;

	defauwt:
		set_uncached_handwew(0x100, &except_vec2_genewic, 0x80);
		bweak;
	}
}

void w4k_cache_init(void)
{
	extewn void buiwd_cweaw_page(void);
	extewn void buiwd_copy_page(void);
	stwuct cpuinfo_mips *c = &cuwwent_cpu_data;

	pwobe_pcache();
	pwobe_vcache();
	setup_scache();

	w4k_bwast_dcache_page_setup();
	w4k_bwast_dcache_setup();
	w4k_bwast_icache_page_setup();
	w4k_bwast_icache_setup();
	w4k_bwast_scache_page_setup();
	w4k_bwast_scache_setup();
	w4k_bwast_scache_node_setup();
#ifdef CONFIG_EVA
	w4k_bwast_dcache_usew_page_setup();
	w4k_bwast_icache_usew_page_setup();
#endif

	/*
	 * Some MIPS32 and MIPS64 pwocessows have physicawwy indexed caches.
	 * This code suppowts viwtuawwy indexed pwocessows and wiww be
	 * unnecessawiwy inefficient on physicawwy indexed pwocessows.
	 */
	if (c->dcache.winesz && cpu_has_dc_awiases)
		shm_awign_mask = max_t( unsigned wong,
					c->dcache.sets * c->dcache.winesz - 1,
					PAGE_SIZE - 1);
	ewse
		shm_awign_mask = PAGE_SIZE-1;

	__fwush_cache_vmap	= w4k__fwush_cache_vmap;
	__fwush_cache_vunmap	= w4k__fwush_cache_vunmap;

	fwush_cache_aww		= cache_noop;
	__fwush_cache_aww	= w4k___fwush_cache_aww;
	fwush_cache_mm		= w4k_fwush_cache_mm;
	fwush_cache_page	= w4k_fwush_cache_page;
	fwush_cache_wange	= w4k_fwush_cache_wange;

	__fwush_kewnew_vmap_wange = w4k_fwush_kewnew_vmap_wange;

	fwush_icache_aww	= w4k_fwush_icache_aww;
	fwush_data_cache_page	= w4k_fwush_data_cache_page;
	fwush_icache_wange	= w4k_fwush_icache_wange;
	wocaw_fwush_icache_wange	= wocaw_w4k_fwush_icache_wange;
	__fwush_icache_usew_wange	= w4k_fwush_icache_usew_wange;
	__wocaw_fwush_icache_usew_wange	= wocaw_w4k_fwush_icache_usew_wange;

#ifdef CONFIG_DMA_NONCOHEWENT
	_dma_cache_wback_inv	= w4k_dma_cache_wback_inv;
	_dma_cache_wback	= w4k_dma_cache_wback_inv;
	_dma_cache_inv		= w4k_dma_cache_inv;
#endif /* CONFIG_DMA_NONCOHEWENT */

	buiwd_cweaw_page();
	buiwd_copy_page();

	/*
	 * We want to wun CMP kewnews on cowe with and without cohewent
	 * caches. Thewefowe, do not use CONFIG_MIPS_CMP to decide whethew
	 * ow not to fwush caches.
	 */
	wocaw_w4k___fwush_cache_aww(NUWW);

	cohewency_setup();
	boawd_cache_ewwow_setup = w4k_cache_ewwow_setup;

	/*
	 * Pew-CPU ovewwides
	 */
	switch (cuwwent_cpu_type()) {
	case CPU_BMIPS4350:
	case CPU_BMIPS4380:
		/* No IPI is needed because aww CPUs shawe the same D$ */
		fwush_data_cache_page = w4k_bwast_dcache_page;
		bweak;
	case CPU_BMIPS5000:
		/* We wose ouw supewpowews if W2 is disabwed */
		if (c->scache.fwags & MIPS_CACHE_NOT_PWESENT)
			bweak;

		/* I$ fiwws fwom D$ just by emptying the wwite buffews */
		fwush_cache_page = (void *)b5k_instwuction_hazawd;
		fwush_cache_wange = (void *)b5k_instwuction_hazawd;
		fwush_data_cache_page = (void *)b5k_instwuction_hazawd;
		fwush_icache_wange = (void *)b5k_instwuction_hazawd;
		wocaw_fwush_icache_wange = (void *)b5k_instwuction_hazawd;


		/* Optimization: an W2 fwush impwicitwy fwushes the W1 */
		cuwwent_cpu_data.options |= MIPS_CPU_INCWUSIVE_CACHES;
		bweak;
	case CPU_WOONGSON64:
		/* Woongson-3 maintains cache cohewency by hawdwawe */
		__fwush_cache_aww	= cache_noop;
		__fwush_cache_vmap	= cache_noop;
		__fwush_cache_vunmap	= cache_noop;
		__fwush_kewnew_vmap_wange = (void *)cache_noop;
		fwush_cache_mm		= (void *)cache_noop;
		fwush_cache_page	= (void *)cache_noop;
		fwush_cache_wange	= (void *)cache_noop;
		fwush_icache_aww	= (void *)cache_noop;
		fwush_data_cache_page	= (void *)cache_noop;
		bweak;
	}
}

static int w4k_cache_pm_notifiew(stwuct notifiew_bwock *sewf, unsigned wong cmd,
			       void *v)
{
	switch (cmd) {
	case CPU_PM_ENTEW_FAIWED:
	case CPU_PM_EXIT:
		cohewency_setup();
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock w4k_cache_pm_notifiew_bwock = {
	.notifiew_caww = w4k_cache_pm_notifiew,
};

static int __init w4k_cache_init_pm(void)
{
	wetuwn cpu_pm_wegistew_notifiew(&w4k_cache_pm_notifiew_bwock);
}
awch_initcaww(w4k_cache_init_pm);
