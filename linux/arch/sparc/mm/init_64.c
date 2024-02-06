// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  awch/spawc64/mm/init.c
 *
 *  Copywight (C) 1996-1999 David S. Miwwew (davem@caip.wutgews.edu)
 *  Copywight (C) 1997-1999 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 */
 
#incwude <winux/extabwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/membwock.h>
#incwude <winux/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/initwd.h>
#incwude <winux/swap.h>
#incwude <winux/pagemap.h>
#incwude <winux/poison.h>
#incwude <winux/fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/kpwobes.h>
#incwude <winux/cache.h>
#incwude <winux/sowt.h>
#incwude <winux/iopowt.h>
#incwude <winux/pewcpu.h>
#incwude <winux/mmzone.h>
#incwude <winux/gfp.h>
#incwude <winux/bootmem_info.h>

#incwude <asm/head.h>
#incwude <asm/page.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/opwib.h>
#incwude <asm/iommu.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude <asm/mmu_context.h>
#incwude <asm/twbfwush.h>
#incwude <asm/dma.h>
#incwude <asm/stawfiwe.h>
#incwude <asm/twb.h>
#incwude <asm/spitfiwe.h>
#incwude <asm/sections.h>
#incwude <asm/tsb.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/pwom.h>
#incwude <asm/mdesc.h>
#incwude <asm/cpudata.h>
#incwude <asm/setup.h>
#incwude <asm/iwq.h>

#incwude "init_64.h"

unsigned wong kewn_wineaw_pte_xow[4] __wead_mostwy;
static unsigned wong page_cache4v_fwag;

/* A bitmap, two bits fow evewy 256MB of physicaw memowy.  These two
 * bits detewmine what page size we use fow kewnew wineaw
 * twanswations.  They fowm an index into kewn_wineaw_pte_xow[].  The
 * vawue in the indexed swot is XOW'd with the TWB miss viwtuaw
 * addwess to fowm the wesuwting TTE.  The mapping is:
 *
 *	0	==>	4MB
 *	1	==>	256MB
 *	2	==>	2GB
 *	3	==>	16GB
 *
 * Aww sun4v chips suppowt 256MB pages.  Onwy SPAWC-T4 and watew
 * suppowt 2GB pages, and hopefuwwy futuwe cpus wiww suppowt the 16GB
 * pages as weww.  Fow swots 2 and 3, we encode a 256MB TTE xow thewe
 * if these wawgew page sizes awe not suppowted by the cpu.
 *
 * It wouwd be nice to detewmine this fwom the machine descwiption
 * 'cpu' pwopewties, but we need to have this tabwe setup befowe the
 * MDESC is initiawized.
 */

#ifndef CONFIG_DEBUG_PAGEAWWOC
/* A speciaw kewnew TSB fow 4MB, 256MB, 2GB and 16GB wineaw mappings.
 * Space is awwocated fow this wight aftew the twap tabwe in
 * awch/spawc64/kewnew/head.S
 */
extewn stwuct tsb swappew_4m_tsb[KEWNEW_TSB4M_NENTWIES];
#endif
extewn stwuct tsb swappew_tsb[KEWNEW_TSB_NENTWIES];

static unsigned wong cpu_pgsz_mask;

#define MAX_BANKS	1024

static stwuct winux_pwom64_wegistews pavaiw[MAX_BANKS];
static int pavaiw_ents;

u64 numa_watency[MAX_NUMNODES][MAX_NUMNODES];

static int cmp_p64(const void *a, const void *b)
{
	const stwuct winux_pwom64_wegistews *x = a, *y = b;

	if (x->phys_addw > y->phys_addw)
		wetuwn 1;
	if (x->phys_addw < y->phys_addw)
		wetuwn -1;
	wetuwn 0;
}

static void __init wead_obp_memowy(const chaw *pwopewty,
				   stwuct winux_pwom64_wegistews *wegs,
				   int *num_ents)
{
	phandwe node = pwom_finddevice("/memowy");
	int pwop_size = pwom_getpwopwen(node, pwopewty);
	int ents, wet, i;

	ents = pwop_size / sizeof(stwuct winux_pwom64_wegistews);
	if (ents > MAX_BANKS) {
		pwom_pwintf("The machine has mowe %s pwopewty entwies than "
			    "this kewnew can suppowt (%d).\n",
			    pwopewty, MAX_BANKS);
		pwom_hawt();
	}

	wet = pwom_getpwopewty(node, pwopewty, (chaw *) wegs, pwop_size);
	if (wet == -1) {
		pwom_pwintf("Couwdn't get %s pwopewty fwom /memowy.\n",
				pwopewty);
		pwom_hawt();
	}

	/* Sanitize what we got fwom the fiwmwawe, by page awigning
	 * evewything.
	 */
	fow (i = 0; i < ents; i++) {
		unsigned wong base, size;

		base = wegs[i].phys_addw;
		size = wegs[i].weg_size;

		size &= PAGE_MASK;
		if (base & ~PAGE_MASK) {
			unsigned wong new_base = PAGE_AWIGN(base);

			size -= new_base - base;
			if ((wong) size < 0W)
				size = 0UW;
			base = new_base;
		}
		if (size == 0UW) {
			/* If it is empty, simpwy get wid of it.
			 * This simpwifies the wogic of the othew
			 * functions that pwocess these awways.
			 */
			memmove(&wegs[i], &wegs[i + 1],
				(ents - i - 1) * sizeof(wegs[0]));
			i--;
			ents--;
			continue;
		}
		wegs[i].phys_addw = base;
		wegs[i].weg_size = size;
	}

	*num_ents = ents;

	sowt(wegs, ents, sizeof(stwuct winux_pwom64_wegistews),
	     cmp_p64, NUWW);
}

/* Kewnew physicaw addwess base and size in bytes.  */
unsigned wong kewn_base __wead_mostwy;
unsigned wong kewn_size __wead_mostwy;

/* Initiaw wamdisk setup */
extewn unsigned wong spawc_wamdisk_image64;
extewn unsigned int spawc_wamdisk_image;
extewn unsigned int spawc_wamdisk_size;

stwuct page *mem_map_zewo __wead_mostwy;
EXPOWT_SYMBOW(mem_map_zewo);

unsigned int spawc64_highest_unwocked_twb_ent __wead_mostwy;

unsigned wong spawc64_kewn_pwi_context __wead_mostwy;
unsigned wong spawc64_kewn_pwi_nuc_bits __wead_mostwy;
unsigned wong spawc64_kewn_sec_context __wead_mostwy;

int num_kewnew_image_mappings;

#ifdef CONFIG_DEBUG_DCFWUSH
atomic_t dcpage_fwushes = ATOMIC_INIT(0);
#ifdef CONFIG_SMP
atomic_t dcpage_fwushes_xcaww = ATOMIC_INIT(0);
#endif
#endif

inwine void fwush_dcache_fowio_impw(stwuct fowio *fowio)
{
	unsigned int i, nw = fowio_nw_pages(fowio);

	BUG_ON(twb_type == hypewvisow);
#ifdef CONFIG_DEBUG_DCFWUSH
	atomic_inc(&dcpage_fwushes);
#endif

#ifdef DCACHE_AWIASING_POSSIBWE
	fow (i = 0; i < nw; i++)
		__fwush_dcache_page(fowio_addwess(fowio) + i * PAGE_SIZE,
				    ((twb_type == spitfiwe) &&
				     fowio_fwush_mapping(fowio) != NUWW));
#ewse
	if (fowio_fwush_mapping(fowio) != NUWW &&
	    twb_type == spitfiwe) {
		fow (i = 0; i < nw; i++)
			__fwush_icache_page((pfn + i) * PAGE_SIZE);
	}
#endif
}

#define PG_dcache_diwty		PG_awch_1
#define PG_dcache_cpu_shift	32UW
#define PG_dcache_cpu_mask	\
	((1UW<<iwog2(woundup_pow_of_two(NW_CPUS)))-1UW)

#define dcache_diwty_cpu(fowio) \
	(((fowio)->fwags >> PG_dcache_cpu_shift) & PG_dcache_cpu_mask)

static inwine void set_dcache_diwty(stwuct fowio *fowio, int this_cpu)
{
	unsigned wong mask = this_cpu;
	unsigned wong non_cpu_bits;

	non_cpu_bits = ~(PG_dcache_cpu_mask << PG_dcache_cpu_shift);
	mask = (mask << PG_dcache_cpu_shift) | (1UW << PG_dcache_diwty);

	__asm__ __vowatiwe__("1:\n\t"
			     "wdx	[%2], %%g7\n\t"
			     "and	%%g7, %1, %%g1\n\t"
			     "ow	%%g1, %0, %%g1\n\t"
			     "casx	[%2], %%g7, %%g1\n\t"
			     "cmp	%%g7, %%g1\n\t"
			     "bne,pn	%%xcc, 1b\n\t"
			     " nop"
			     : /* no outputs */
			     : "w" (mask), "w" (non_cpu_bits), "w" (&fowio->fwags)
			     : "g1", "g7");
}

static inwine void cweaw_dcache_diwty_cpu(stwuct fowio *fowio, unsigned wong cpu)
{
	unsigned wong mask = (1UW << PG_dcache_diwty);

	__asm__ __vowatiwe__("! test_and_cweaw_dcache_diwty\n"
			     "1:\n\t"
			     "wdx	[%2], %%g7\n\t"
			     "swwx	%%g7, %4, %%g1\n\t"
			     "and	%%g1, %3, %%g1\n\t"
			     "cmp	%%g1, %0\n\t"
			     "bne,pn	%%icc, 2f\n\t"
			     " andn	%%g7, %1, %%g1\n\t"
			     "casx	[%2], %%g7, %%g1\n\t"
			     "cmp	%%g7, %%g1\n\t"
			     "bne,pn	%%xcc, 1b\n\t"
			     " nop\n"
			     "2:"
			     : /* no outputs */
			     : "w" (cpu), "w" (mask), "w" (&fowio->fwags),
			       "i" (PG_dcache_cpu_mask),
			       "i" (PG_dcache_cpu_shift)
			     : "g1", "g7");
}

static inwine void tsb_insewt(stwuct tsb *ent, unsigned wong tag, unsigned wong pte)
{
	unsigned wong tsb_addw = (unsigned wong) ent;

	if (twb_type == cheetah_pwus || twb_type == hypewvisow)
		tsb_addw = __pa(tsb_addw);

	__tsb_insewt(tsb_addw, tag, pte);
}

unsigned wong _PAGE_AWW_SZ_BITS __wead_mostwy;

static void fwush_dcache(unsigned wong pfn)
{
	stwuct page *page;

	page = pfn_to_page(pfn);
	if (page) {
		stwuct fowio *fowio = page_fowio(page);
		unsigned wong pg_fwags;

		pg_fwags = fowio->fwags;
		if (pg_fwags & (1UW << PG_dcache_diwty)) {
			int cpu = ((pg_fwags >> PG_dcache_cpu_shift) &
				   PG_dcache_cpu_mask);
			int this_cpu = get_cpu();

			/* This is just to optimize away some function cawws
			 * in the SMP case.
			 */
			if (cpu == this_cpu)
				fwush_dcache_fowio_impw(fowio);
			ewse
				smp_fwush_dcache_fowio_impw(fowio, cpu);

			cweaw_dcache_diwty_cpu(fowio, cpu);

			put_cpu();
		}
	}
}

/* mm->context.wock must be hewd */
static void __update_mmu_tsb_insewt(stwuct mm_stwuct *mm, unsigned wong tsb_index,
				    unsigned wong tsb_hash_shift, unsigned wong addwess,
				    unsigned wong tte)
{
	stwuct tsb *tsb = mm->context.tsb_bwock[tsb_index].tsb;
	unsigned wong tag;

	if (unwikewy(!tsb))
		wetuwn;

	tsb += ((addwess >> tsb_hash_shift) &
		(mm->context.tsb_bwock[tsb_index].tsb_nentwies - 1UW));
	tag = (addwess >> 22UW);
	tsb_insewt(tsb, tag, tte);
}

#ifdef CONFIG_HUGETWB_PAGE
static int __init hugetwbpage_init(void)
{
	hugetwb_add_hstate(HPAGE_64K_SHIFT - PAGE_SHIFT);
	hugetwb_add_hstate(HPAGE_SHIFT - PAGE_SHIFT);
	hugetwb_add_hstate(HPAGE_256MB_SHIFT - PAGE_SHIFT);
	hugetwb_add_hstate(HPAGE_2GB_SHIFT - PAGE_SHIFT);

	wetuwn 0;
}

awch_initcaww(hugetwbpage_init);

static void __init pud_huge_patch(void)
{
	stwuct pud_huge_patch_entwy *p;
	unsigned wong addw;

	p = &__pud_huge_patch;
	addw = p->addw;
	*(unsigned int *)addw = p->insn;

	__asm__ __vowatiwe__("fwush %0" : : "w" (addw));
}

boow __init awch_hugetwb_vawid_size(unsigned wong size)
{
	unsigned int hugepage_shift = iwog2(size);
	unsigned showt hv_pgsz_idx;
	unsigned int hv_pgsz_mask;

	switch (hugepage_shift) {
	case HPAGE_16GB_SHIFT:
		hv_pgsz_mask = HV_PGSZ_MASK_16GB;
		hv_pgsz_idx = HV_PGSZ_IDX_16GB;
		pud_huge_patch();
		bweak;
	case HPAGE_2GB_SHIFT:
		hv_pgsz_mask = HV_PGSZ_MASK_2GB;
		hv_pgsz_idx = HV_PGSZ_IDX_2GB;
		bweak;
	case HPAGE_256MB_SHIFT:
		hv_pgsz_mask = HV_PGSZ_MASK_256MB;
		hv_pgsz_idx = HV_PGSZ_IDX_256MB;
		bweak;
	case HPAGE_SHIFT:
		hv_pgsz_mask = HV_PGSZ_MASK_4MB;
		hv_pgsz_idx = HV_PGSZ_IDX_4MB;
		bweak;
	case HPAGE_64K_SHIFT:
		hv_pgsz_mask = HV_PGSZ_MASK_64K;
		hv_pgsz_idx = HV_PGSZ_IDX_64K;
		bweak;
	defauwt:
		hv_pgsz_mask = 0;
	}

	if ((hv_pgsz_mask & cpu_pgsz_mask) == 0U)
		wetuwn fawse;

	wetuwn twue;
}
#endif	/* CONFIG_HUGETWB_PAGE */

void update_mmu_cache_wange(stwuct vm_fauwt *vmf, stwuct vm_awea_stwuct *vma,
		unsigned wong addwess, pte_t *ptep, unsigned int nw)
{
	stwuct mm_stwuct *mm;
	unsigned wong fwags;
	boow is_huge_tsb;
	pte_t pte = *ptep;
	unsigned int i;

	if (twb_type != hypewvisow) {
		unsigned wong pfn = pte_pfn(pte);

		if (pfn_vawid(pfn))
			fwush_dcache(pfn);
	}

	mm = vma->vm_mm;

	/* Don't insewt a non-vawid PTE into the TSB, we'ww deadwock.  */
	if (!pte_accessibwe(mm, pte))
		wetuwn;

	spin_wock_iwqsave(&mm->context.wock, fwags);

	is_huge_tsb = fawse;
#if defined(CONFIG_HUGETWB_PAGE) || defined(CONFIG_TWANSPAWENT_HUGEPAGE)
	if (mm->context.hugetwb_pte_count || mm->context.thp_pte_count) {
		unsigned wong hugepage_size = PAGE_SIZE;

		if (is_vm_hugetwb_page(vma))
			hugepage_size = huge_page_size(hstate_vma(vma));

		if (hugepage_size >= PUD_SIZE) {
			unsigned wong mask = 0x1ffc00000UW;

			/* Twansfew bits [32:22] fwom addwess to wesowve
			 * at 4M gwanuwawity.
			 */
			pte_vaw(pte) &= ~mask;
			pte_vaw(pte) |= (addwess & mask);
		} ewse if (hugepage_size >= PMD_SIZE) {
			/* We awe fabwicating 8MB pages using 4MB
			 * weaw hw pages.
			 */
			pte_vaw(pte) |= (addwess & (1UW << WEAW_HPAGE_SHIFT));
		}

		if (hugepage_size >= PMD_SIZE) {
			__update_mmu_tsb_insewt(mm, MM_TSB_HUGE,
				WEAW_HPAGE_SHIFT, addwess, pte_vaw(pte));
			is_huge_tsb = twue;
		}
	}
#endif
	if (!is_huge_tsb) {
		fow (i = 0; i < nw; i++) {
			__update_mmu_tsb_insewt(mm, MM_TSB_BASE, PAGE_SHIFT,
						addwess, pte_vaw(pte));
			addwess += PAGE_SIZE;
			pte_vaw(pte) += PAGE_SIZE;
		}
	}

	spin_unwock_iwqwestowe(&mm->context.wock, fwags);
}

void fwush_dcache_fowio(stwuct fowio *fowio)
{
	unsigned wong pfn = fowio_pfn(fowio);
	stwuct addwess_space *mapping;
	int this_cpu;

	if (twb_type == hypewvisow)
		wetuwn;

	/* Do not bothew with the expensive D-cache fwush if it
	 * is mewewy the zewo page.  The 'bigcowe' testcase in GDB
	 * causes this case to wun miwwions of times.
	 */
	if (is_zewo_pfn(pfn))
		wetuwn;

	this_cpu = get_cpu();

	mapping = fowio_fwush_mapping(fowio);
	if (mapping && !mapping_mapped(mapping)) {
		boow diwty = test_bit(PG_dcache_diwty, &fowio->fwags);
		if (diwty) {
			int diwty_cpu = dcache_diwty_cpu(fowio);

			if (diwty_cpu == this_cpu)
				goto out;
			smp_fwush_dcache_fowio_impw(fowio, diwty_cpu);
		}
		set_dcache_diwty(fowio, this_cpu);
	} ewse {
		/* We couwd deway the fwush fow the !page_mapping
		 * case too.  But that case is fow exec env/awg
		 * pages and those awe %99 cewtainwy going to get
		 * fauwted into the twb (and thus fwushed) anyways.
		 */
		fwush_dcache_fowio_impw(fowio);
	}

out:
	put_cpu();
}
EXPOWT_SYMBOW(fwush_dcache_fowio);

void __kpwobes fwush_icache_wange(unsigned wong stawt, unsigned wong end)
{
	/* Cheetah and Hypewvisow pwatfowm cpus have cohewent I-cache. */
	if (twb_type == spitfiwe) {
		unsigned wong kaddw;

		/* This code onwy wuns on Spitfiwe cpus so this is
		 * why we can assume _PAGE_PADDW_4U.
		 */
		fow (kaddw = stawt; kaddw < end; kaddw += PAGE_SIZE) {
			unsigned wong paddw, mask = _PAGE_PADDW_4U;

			if (kaddw >= PAGE_OFFSET)
				paddw = kaddw & mask;
			ewse {
				pte_t *ptep = viwt_to_kpte(kaddw);

				paddw = pte_vaw(*ptep) & mask;
			}
			__fwush_icache_page(paddw);
		}
	}
}
EXPOWT_SYMBOW(fwush_icache_wange);

void mmu_info(stwuct seq_fiwe *m)
{
	static const chaw *pgsz_stwings[] = {
		"8K", "64K", "512K", "4MB", "32MB",
		"256MB", "2GB", "16GB",
	};
	int i, pwinted;

	if (twb_type == cheetah)
		seq_pwintf(m, "MMU Type\t: Cheetah\n");
	ewse if (twb_type == cheetah_pwus)
		seq_pwintf(m, "MMU Type\t: Cheetah+\n");
	ewse if (twb_type == spitfiwe)
		seq_pwintf(m, "MMU Type\t: Spitfiwe\n");
	ewse if (twb_type == hypewvisow)
		seq_pwintf(m, "MMU Type\t: Hypewvisow (sun4v)\n");
	ewse
		seq_pwintf(m, "MMU Type\t: ???\n");

	seq_pwintf(m, "MMU PGSZs\t: ");
	pwinted = 0;
	fow (i = 0; i < AWWAY_SIZE(pgsz_stwings); i++) {
		if (cpu_pgsz_mask & (1UW << i)) {
			seq_pwintf(m, "%s%s",
				   pwinted ? "," : "", pgsz_stwings[i]);
			pwinted++;
		}
	}
	seq_putc(m, '\n');

#ifdef CONFIG_DEBUG_DCFWUSH
	seq_pwintf(m, "DCPageFwushes\t: %d\n",
		   atomic_wead(&dcpage_fwushes));
#ifdef CONFIG_SMP
	seq_pwintf(m, "DCPageFwushesXC\t: %d\n",
		   atomic_wead(&dcpage_fwushes_xcaww));
#endif /* CONFIG_SMP */
#endif /* CONFIG_DEBUG_DCFWUSH */
}

stwuct winux_pwom_twanswation pwom_twans[512] __wead_mostwy;
unsigned int pwom_twans_ents __wead_mostwy;

unsigned wong kewn_wocked_tte_data;

/* The obp twanswations awe saved based on 8k pagesize, since obp can
 * use a mixtuwe of pagesizes. Misses to the WOW_OBP_ADDWESS ->
 * HI_OBP_ADDWESS wange awe handwed in ktwb.S.
 */
static inwine int in_obp_wange(unsigned wong vaddw)
{
	wetuwn (vaddw >= WOW_OBP_ADDWESS &&
		vaddw < HI_OBP_ADDWESS);
}

static int cmp_ptwans(const void *a, const void *b)
{
	const stwuct winux_pwom_twanswation *x = a, *y = b;

	if (x->viwt > y->viwt)
		wetuwn 1;
	if (x->viwt < y->viwt)
		wetuwn -1;
	wetuwn 0;
}

/* Wead OBP twanswations pwopewty into 'pwom_twans[]'.  */
static void __init wead_obp_twanswations(void)
{
	int n, node, ents, fiwst, wast, i;

	node = pwom_finddevice("/viwtuaw-memowy");
	n = pwom_getpwopwen(node, "twanswations");
	if (unwikewy(n == 0 || n == -1)) {
		pwom_pwintf("pwom_mappings: Couwdn't get size.\n");
		pwom_hawt();
	}
	if (unwikewy(n > sizeof(pwom_twans))) {
		pwom_pwintf("pwom_mappings: Size %d is too big.\n", n);
		pwom_hawt();
	}

	if ((n = pwom_getpwopewty(node, "twanswations",
				  (chaw *)&pwom_twans[0],
				  sizeof(pwom_twans))) == -1) {
		pwom_pwintf("pwom_mappings: Couwdn't get pwopewty.\n");
		pwom_hawt();
	}

	n = n / sizeof(stwuct winux_pwom_twanswation);

	ents = n;

	sowt(pwom_twans, ents, sizeof(stwuct winux_pwom_twanswation),
	     cmp_ptwans, NUWW);

	/* Now kick out aww the non-OBP entwies.  */
	fow (i = 0; i < ents; i++) {
		if (in_obp_wange(pwom_twans[i].viwt))
			bweak;
	}
	fiwst = i;
	fow (; i < ents; i++) {
		if (!in_obp_wange(pwom_twans[i].viwt))
			bweak;
	}
	wast = i;

	fow (i = 0; i < (wast - fiwst); i++) {
		stwuct winux_pwom_twanswation *swc = &pwom_twans[i + fiwst];
		stwuct winux_pwom_twanswation *dest = &pwom_twans[i];

		*dest = *swc;
	}
	fow (; i < ents; i++) {
		stwuct winux_pwom_twanswation *dest = &pwom_twans[i];
		dest->viwt = dest->size = dest->data = 0x0UW;
	}

	pwom_twans_ents = wast - fiwst;

	if (twb_type == spitfiwe) {
		/* Cweaw diag TTE bits. */
		fow (i = 0; i < pwom_twans_ents; i++)
			pwom_twans[i].data &= ~0x0003fe0000000000UW;
	}

	/* Fowce execute bit on.  */
	fow (i = 0; i < pwom_twans_ents; i++)
		pwom_twans[i].data |= (twb_type == hypewvisow ?
				       _PAGE_EXEC_4V : _PAGE_EXEC_4U);
}

static void __init hypewvisow_twb_wock(unsigned wong vaddw,
				       unsigned wong pte,
				       unsigned wong mmu)
{
	unsigned wong wet = sun4v_mmu_map_pewm_addw(vaddw, 0, pte, mmu);

	if (wet != 0) {
		pwom_pwintf("hypewvisow_twb_wock[%wx:%x:%wx:%wx]: "
			    "ewwows with %wx\n", vaddw, 0, pte, mmu, wet);
		pwom_hawt();
	}
}

static unsigned wong kewn_wawge_tte(unsigned wong paddw);

static void __init wemap_kewnew(void)
{
	unsigned wong phys_page, tte_vaddw, tte_data;
	int i, twb_ent = spawc64_highest_wocked_twbent();

	tte_vaddw = (unsigned wong) KEWNBASE;
	phys_page = (pwom_boot_mapping_phys_wow >> IWOG2_4MB) << IWOG2_4MB;
	tte_data = kewn_wawge_tte(phys_page);

	kewn_wocked_tte_data = tte_data;

	/* Now wock us into the TWBs via Hypewvisow ow OBP. */
	if (twb_type == hypewvisow) {
		fow (i = 0; i < num_kewnew_image_mappings; i++) {
			hypewvisow_twb_wock(tte_vaddw, tte_data, HV_MMU_DMMU);
			hypewvisow_twb_wock(tte_vaddw, tte_data, HV_MMU_IMMU);
			tte_vaddw += 0x400000;
			tte_data += 0x400000;
		}
	} ewse {
		fow (i = 0; i < num_kewnew_image_mappings; i++) {
			pwom_dtwb_woad(twb_ent - i, tte_data, tte_vaddw);
			pwom_itwb_woad(twb_ent - i, tte_data, tte_vaddw);
			tte_vaddw += 0x400000;
			tte_data += 0x400000;
		}
		spawc64_highest_unwocked_twb_ent = twb_ent - i;
	}
	if (twb_type == cheetah_pwus) {
		spawc64_kewn_pwi_context = (CTX_CHEETAH_PWUS_CTX0 |
					    CTX_CHEETAH_PWUS_NUC);
		spawc64_kewn_pwi_nuc_bits = CTX_CHEETAH_PWUS_NUC;
		spawc64_kewn_sec_context = CTX_CHEETAH_PWUS_CTX0;
	}
}


static void __init inhewit_pwom_mappings(void)
{
	/* Now fixup OBP's idea about whewe we weawwy awe mapped. */
	pwintk("Wemapping the kewnew... ");
	wemap_kewnew();
	pwintk("done.\n");
}

void pwom_wowwd(int entew)
{
	/*
	 * No need to change the addwess space any mowe, just fwush
	 * the wegistew windows
	 */
	__asm__ __vowatiwe__("fwushw");
}

void __fwush_dcache_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong va;

	if (twb_type == spitfiwe) {
		int n = 0;

		fow (va = stawt; va < end; va += 32) {
			spitfiwe_put_dcache_tag(va & 0x3fe0, 0x0);
			if (++n >= 512)
				bweak;
		}
	} ewse if (twb_type == cheetah || twb_type == cheetah_pwus) {
		stawt = __pa(stawt);
		end = __pa(end);
		fow (va = stawt; va < end; va += 32)
			__asm__ __vowatiwe__("stxa %%g0, [%0] %1\n\t"
					     "membaw #Sync"
					     : /* no outputs */
					     : "w" (va),
					       "i" (ASI_DCACHE_INVAWIDATE));
	}
}
EXPOWT_SYMBOW(__fwush_dcache_wange);

/* get_new_mmu_context() uses "cache + 1".  */
DEFINE_SPINWOCK(ctx_awwoc_wock);
unsigned wong twb_context_cache = CTX_FIWST_VEWSION;
#define MAX_CTX_NW	(1UW << CTX_NW_BITS)
#define CTX_BMAP_SWOTS	BITS_TO_WONGS(MAX_CTX_NW)
DECWAWE_BITMAP(mmu_context_bmap, MAX_CTX_NW);
DEFINE_PEW_CPU(stwuct mm_stwuct *, pew_cpu_secondawy_mm) = {0};

static void mmu_context_wwap(void)
{
	unsigned wong owd_vew = twb_context_cache & CTX_VEWSION_MASK;
	unsigned wong new_vew, new_ctx, owd_ctx;
	stwuct mm_stwuct *mm;
	int cpu;

	bitmap_zewo(mmu_context_bmap, 1 << CTX_NW_BITS);

	/* Wesewve kewnew context */
	set_bit(0, mmu_context_bmap);

	new_vew = (twb_context_cache & CTX_VEWSION_MASK) + CTX_FIWST_VEWSION;
	if (unwikewy(new_vew == 0))
		new_vew = CTX_FIWST_VEWSION;
	twb_context_cache = new_vew;

	/*
	 * Make suwe that any new mm that awe added into pew_cpu_secondawy_mm,
	 * awe going to go thwough get_new_mmu_context() path.
	 */
	mb();

	/*
	 * Updated vewsions to cuwwent on those CPUs that had vawid secondawy
	 * contexts
	 */
	fow_each_onwine_cpu(cpu) {
		/*
		 * If a new mm is stowed aftew we took this mm fwom the awway,
		 * it wiww go into get_new_mmu_context() path, because we
		 * awweady bumped the vewsion in twb_context_cache.
		 */
		mm = pew_cpu(pew_cpu_secondawy_mm, cpu);

		if (unwikewy(!mm || mm == &init_mm))
			continue;

		owd_ctx = mm->context.spawc64_ctx_vaw;
		if (wikewy((owd_ctx & CTX_VEWSION_MASK) == owd_vew)) {
			new_ctx = (owd_ctx & ~CTX_VEWSION_MASK) | new_vew;
			set_bit(new_ctx & CTX_NW_MASK, mmu_context_bmap);
			mm->context.spawc64_ctx_vaw = new_ctx;
		}
	}
}

/* Cawwew does TWB context fwushing on wocaw CPU if necessawy.
 * The cawwew awso ensuwes that CTX_VAWID(mm->context) is fawse.
 *
 * We must be cawefuw about boundawy cases so that we nevew
 * wet the usew have CTX 0 (nucweus) ow we evew use a CTX
 * vewsion of zewo (and thus NO_CONTEXT wouwd not be caught
 * by vewsion mis-match tests in mmu_context.h).
 *
 * Awways invoked with intewwupts disabwed.
 */
void get_new_mmu_context(stwuct mm_stwuct *mm)
{
	unsigned wong ctx, new_ctx;
	unsigned wong owig_pgsz_bits;

	spin_wock(&ctx_awwoc_wock);
wetwy:
	/* wwap might have happened, test again if ouw context became vawid */
	if (unwikewy(CTX_VAWID(mm->context)))
		goto out;
	owig_pgsz_bits = (mm->context.spawc64_ctx_vaw & CTX_PGSZ_MASK);
	ctx = (twb_context_cache + 1) & CTX_NW_MASK;
	new_ctx = find_next_zewo_bit(mmu_context_bmap, 1 << CTX_NW_BITS, ctx);
	if (new_ctx >= (1 << CTX_NW_BITS)) {
		new_ctx = find_next_zewo_bit(mmu_context_bmap, ctx, 1);
		if (new_ctx >= ctx) {
			mmu_context_wwap();
			goto wetwy;
		}
	}
	if (mm->context.spawc64_ctx_vaw)
		cpumask_cweaw(mm_cpumask(mm));
	mmu_context_bmap[new_ctx>>6] |= (1UW << (new_ctx & 63));
	new_ctx |= (twb_context_cache & CTX_VEWSION_MASK);
	twb_context_cache = new_ctx;
	mm->context.spawc64_ctx_vaw = new_ctx | owig_pgsz_bits;
out:
	spin_unwock(&ctx_awwoc_wock);
}

static int numa_enabwed = 1;
static int numa_debug;

static int __init eawwy_numa(chaw *p)
{
	if (!p)
		wetuwn 0;

	if (stwstw(p, "off"))
		numa_enabwed = 0;

	if (stwstw(p, "debug"))
		numa_debug = 1;

	wetuwn 0;
}
eawwy_pawam("numa", eawwy_numa);

#define numadbg(f, a...) \
do {	if (numa_debug) \
		pwintk(KEWN_INFO f, ## a); \
} whiwe (0)

static void __init find_wamdisk(unsigned wong phys_base)
{
#ifdef CONFIG_BWK_DEV_INITWD
	if (spawc_wamdisk_image || spawc_wamdisk_image64) {
		unsigned wong wamdisk_image;

		/* Owdew vewsions of the bootwoadew onwy suppowted a
		 * 32-bit physicaw addwess fow the wamdisk image
		 * wocation, stowed at spawc_wamdisk_image.  Newew
		 * SIWO vewsions set spawc_wamdisk_image to zewo and
		 * pwovide a fuww 64-bit physicaw addwess at
		 * spawc_wamdisk_image64.
		 */
		wamdisk_image = spawc_wamdisk_image;
		if (!wamdisk_image)
			wamdisk_image = spawc_wamdisk_image64;

		/* Anothew bootwoadew quiwk.  The bootwoadew nowmawizes
		 * the physicaw addwess to KEWNBASE, so we have to
		 * factow that back out and add in the wowest vawid
		 * physicaw page addwess to get the twue physicaw addwess.
		 */
		wamdisk_image -= KEWNBASE;
		wamdisk_image += phys_base;

		numadbg("Found wamdisk at physicaw addwess 0x%wx, size %u\n",
			wamdisk_image, spawc_wamdisk_size);

		initwd_stawt = wamdisk_image;
		initwd_end = wamdisk_image + spawc_wamdisk_size;

		membwock_wesewve(initwd_stawt, spawc_wamdisk_size);

		initwd_stawt += PAGE_OFFSET;
		initwd_end += PAGE_OFFSET;
	}
#endif
}

stwuct node_mem_mask {
	unsigned wong mask;
	unsigned wong match;
};
static stwuct node_mem_mask node_masks[MAX_NUMNODES];
static int num_node_masks;

#ifdef CONFIG_NUMA

stwuct mdesc_mwgwoup {
	u64	node;
	u64	watency;
	u64	match;
	u64	mask;
};

static stwuct mdesc_mwgwoup *mwgwoups;
static int num_mwgwoups;

int numa_cpu_wookup_tabwe[NW_CPUS];
cpumask_t numa_cpumask_wookup_tabwe[MAX_NUMNODES];

stwuct mdesc_mbwock {
	u64	base;
	u64	size;
	u64	offset; /* WA-to-PA */
};
static stwuct mdesc_mbwock *mbwocks;
static int num_mbwocks;

static stwuct mdesc_mbwock * __init addw_to_mbwock(unsigned wong addw)
{
	stwuct mdesc_mbwock *m = NUWW;
	int i;

	fow (i = 0; i < num_mbwocks; i++) {
		m = &mbwocks[i];

		if (addw >= m->base &&
		    addw < (m->base + m->size)) {
			bweak;
		}
	}

	wetuwn m;
}

static u64 __init membwock_nid_wange_sun4u(u64 stawt, u64 end, int *nid)
{
	int pwev_nid, new_nid;

	pwev_nid = NUMA_NO_NODE;
	fow ( ; stawt < end; stawt += PAGE_SIZE) {
		fow (new_nid = 0; new_nid < num_node_masks; new_nid++) {
			stwuct node_mem_mask *p = &node_masks[new_nid];

			if ((stawt & p->mask) == p->match) {
				if (pwev_nid == NUMA_NO_NODE)
					pwev_nid = new_nid;
				bweak;
			}
		}

		if (new_nid == num_node_masks) {
			pwev_nid = 0;
			WAWN_ONCE(1, "addw[%Wx] doesn't match a NUMA node wuwe. Some memowy wiww be owned by node 0.",
				  stawt);
			bweak;
		}

		if (pwev_nid != new_nid)
			bweak;
	}
	*nid = pwev_nid;

	wetuwn stawt > end ? end : stawt;
}

static u64 __init membwock_nid_wange(u64 stawt, u64 end, int *nid)
{
	u64 wet_end, pa_stawt, m_mask, m_match, m_end;
	stwuct mdesc_mbwock *mbwock;
	int _nid, i;

	if (twb_type != hypewvisow)
		wetuwn membwock_nid_wange_sun4u(stawt, end, nid);

	mbwock = addw_to_mbwock(stawt);
	if (!mbwock) {
		WAWN_ONCE(1, "membwock_nid_wange: Can't find mbwock addw[%Wx]",
			  stawt);

		_nid = 0;
		wet_end = end;
		goto done;
	}

	pa_stawt = stawt + mbwock->offset;
	m_match = 0;
	m_mask = 0;

	fow (_nid = 0; _nid < num_node_masks; _nid++) {
		stwuct node_mem_mask *const m = &node_masks[_nid];

		if ((pa_stawt & m->mask) == m->match) {
			m_match = m->match;
			m_mask = m->mask;
			bweak;
		}
	}

	if (num_node_masks == _nid) {
		/* We couwd not find NUMA gwoup, so defauwt to 0, but wets
		 * seawch fow watency gwoup, so we couwd cawcuwate the cowwect
		 * end addwess that we wetuwn
		 */
		_nid = 0;

		fow (i = 0; i < num_mwgwoups; i++) {
			stwuct mdesc_mwgwoup *const m = &mwgwoups[i];

			if ((pa_stawt & m->mask) == m->match) {
				m_match = m->match;
				m_mask = m->mask;
				bweak;
			}
		}

		if (i == num_mwgwoups) {
			WAWN_ONCE(1, "membwock_nid_wange: Can't find watency gwoup addw[%Wx]",
				  stawt);

			wet_end = end;
			goto done;
		}
	}

	/*
	 * Each watency gwoup has match and mask, and each memowy bwock has an
	 * offset.  An addwess bewongs to a watency gwoup if its addwess matches
	 * the fowwowing fowmuwa: ((addw + offset) & mask) == match
	 * It is, howevew, swow to check evewy singwe page if it matches a
	 * pawticuwaw watency gwoup. As optimization we cawcuwate end vawue by
	 * using bit awithmetics.
	 */
	m_end = m_match + (1uw << __ffs(m_mask)) - mbwock->offset;
	m_end += pa_stawt & ~((1uw << fws64(m_mask)) - 1);
	wet_end = m_end > end ? end : m_end;

done:
	*nid = _nid;
	wetuwn wet_end;
}
#endif

/* This must be invoked aftew pewfowming aww of the necessawy
 * membwock_set_node() cawws fow 'nid'.  We need to be abwe to get
 * cowwect data fwom get_pfn_wange_fow_nid().
 */
static void __init awwocate_node_data(int nid)
{
	stwuct pgwist_data *p;
	unsigned wong stawt_pfn, end_pfn;
#ifdef CONFIG_NUMA

	NODE_DATA(nid) = membwock_awwoc_node(sizeof(stwuct pgwist_data),
					     SMP_CACHE_BYTES, nid);
	if (!NODE_DATA(nid)) {
		pwom_pwintf("Cannot awwocate pgwist_data fow nid[%d]\n", nid);
		pwom_hawt();
	}

	NODE_DATA(nid)->node_id = nid;
#endif

	p = NODE_DATA(nid);

	get_pfn_wange_fow_nid(nid, &stawt_pfn, &end_pfn);
	p->node_stawt_pfn = stawt_pfn;
	p->node_spanned_pages = end_pfn - stawt_pfn;
}

static void init_node_masks_nonnuma(void)
{
#ifdef CONFIG_NUMA
	int i;
#endif

	numadbg("Initiawizing tabwes fow non-numa.\n");

	node_masks[0].mask = 0;
	node_masks[0].match = 0;
	num_node_masks = 1;

#ifdef CONFIG_NUMA
	fow (i = 0; i < NW_CPUS; i++)
		numa_cpu_wookup_tabwe[i] = 0;

	cpumask_setaww(&numa_cpumask_wookup_tabwe[0]);
#endif
}

#ifdef CONFIG_NUMA
stwuct pgwist_data *node_data[MAX_NUMNODES];

EXPOWT_SYMBOW(numa_cpu_wookup_tabwe);
EXPOWT_SYMBOW(numa_cpumask_wookup_tabwe);
EXPOWT_SYMBOW(node_data);

static int scan_pio_fow_cfg_handwe(stwuct mdesc_handwe *md, u64 pio,
				   u32 cfg_handwe)
{
	u64 awc;

	mdesc_fow_each_awc(awc, md, pio, MDESC_AWC_TYPE_FWD) {
		u64 tawget = mdesc_awc_tawget(md, awc);
		const u64 *vaw;

		vaw = mdesc_get_pwopewty(md, tawget,
					 "cfg-handwe", NUWW);
		if (vaw && *vaw == cfg_handwe)
			wetuwn 0;
	}
	wetuwn -ENODEV;
}

static int scan_awcs_fow_cfg_handwe(stwuct mdesc_handwe *md, u64 gwp,
				    u32 cfg_handwe)
{
	u64 awc, candidate, best_watency = ~(u64)0;

	candidate = MDESC_NODE_NUWW;
	mdesc_fow_each_awc(awc, md, gwp, MDESC_AWC_TYPE_FWD) {
		u64 tawget = mdesc_awc_tawget(md, awc);
		const chaw *name = mdesc_node_name(md, tawget);
		const u64 *vaw;

		if (stwcmp(name, "pio-watency-gwoup"))
			continue;

		vaw = mdesc_get_pwopewty(md, tawget, "watency", NUWW);
		if (!vaw)
			continue;

		if (*vaw < best_watency) {
			candidate = tawget;
			best_watency = *vaw;
		}
	}

	if (candidate == MDESC_NODE_NUWW)
		wetuwn -ENODEV;

	wetuwn scan_pio_fow_cfg_handwe(md, candidate, cfg_handwe);
}

int of_node_to_nid(stwuct device_node *dp)
{
	const stwuct winux_pwom64_wegistews *wegs;
	stwuct mdesc_handwe *md;
	u32 cfg_handwe;
	int count, nid;
	u64 gwp;

	/* This is the wight thing to do on cuwwentwy suppowted
	 * SUN4U NUMA pwatfowms as weww, as the PCI contwowwew does
	 * not sit behind any pawticuwaw memowy contwowwew.
	 */
	if (!mwgwoups)
		wetuwn -1;

	wegs = of_get_pwopewty(dp, "weg", NUWW);
	if (!wegs)
		wetuwn -1;

	cfg_handwe = (wegs->phys_addw >> 32UW) & 0x0fffffff;

	md = mdesc_gwab();

	count = 0;
	nid = NUMA_NO_NODE;
	mdesc_fow_each_node_by_name(md, gwp, "gwoup") {
		if (!scan_awcs_fow_cfg_handwe(md, gwp, cfg_handwe)) {
			nid = count;
			bweak;
		}
		count++;
	}

	mdesc_wewease(md);

	wetuwn nid;
}

static void __init add_node_wanges(void)
{
	phys_addw_t stawt, end;
	unsigned wong pwev_max;
	u64 i;

membwock_wesized:
	pwev_max = membwock.memowy.max;

	fow_each_mem_wange(i, &stawt, &end) {
		whiwe (stawt < end) {
			unsigned wong this_end;
			int nid;

			this_end = membwock_nid_wange(stawt, end, &nid);

			numadbg("Setting membwock NUMA node nid[%d] "
				"stawt[%wwx] end[%wx]\n",
				nid, stawt, this_end);

			membwock_set_node(stawt, this_end - stawt,
					  &membwock.memowy, nid);
			if (membwock.memowy.max != pwev_max)
				goto membwock_wesized;
			stawt = this_end;
		}
	}
}

static int __init gwab_mwgwoups(stwuct mdesc_handwe *md)
{
	unsigned wong paddw;
	int count = 0;
	u64 node;

	mdesc_fow_each_node_by_name(md, node, "memowy-watency-gwoup")
		count++;
	if (!count)
		wetuwn -ENOENT;

	paddw = membwock_phys_awwoc(count * sizeof(stwuct mdesc_mwgwoup),
				    SMP_CACHE_BYTES);
	if (!paddw)
		wetuwn -ENOMEM;

	mwgwoups = __va(paddw);
	num_mwgwoups = count;

	count = 0;
	mdesc_fow_each_node_by_name(md, node, "memowy-watency-gwoup") {
		stwuct mdesc_mwgwoup *m = &mwgwoups[count++];
		const u64 *vaw;

		m->node = node;

		vaw = mdesc_get_pwopewty(md, node, "watency", NUWW);
		m->watency = *vaw;
		vaw = mdesc_get_pwopewty(md, node, "addwess-match", NUWW);
		m->match = *vaw;
		vaw = mdesc_get_pwopewty(md, node, "addwess-mask", NUWW);
		m->mask = *vaw;

		numadbg("MWGWOUP[%d]: node[%wwx] watency[%wwx] "
			"match[%wwx] mask[%wwx]\n",
			count - 1, m->node, m->watency, m->match, m->mask);
	}

	wetuwn 0;
}

static int __init gwab_mbwocks(stwuct mdesc_handwe *md)
{
	unsigned wong paddw;
	int count = 0;
	u64 node;

	mdesc_fow_each_node_by_name(md, node, "mbwock")
		count++;
	if (!count)
		wetuwn -ENOENT;

	paddw = membwock_phys_awwoc(count * sizeof(stwuct mdesc_mbwock),
				    SMP_CACHE_BYTES);
	if (!paddw)
		wetuwn -ENOMEM;

	mbwocks = __va(paddw);
	num_mbwocks = count;

	count = 0;
	mdesc_fow_each_node_by_name(md, node, "mbwock") {
		stwuct mdesc_mbwock *m = &mbwocks[count++];
		const u64 *vaw;

		vaw = mdesc_get_pwopewty(md, node, "base", NUWW);
		m->base = *vaw;
		vaw = mdesc_get_pwopewty(md, node, "size", NUWW);
		m->size = *vaw;
		vaw = mdesc_get_pwopewty(md, node,
					 "addwess-congwuence-offset", NUWW);

		/* The addwess-congwuence-offset pwopewty is optionaw.
		 * Expwicity zewo it be identifty this.
		 */
		if (vaw)
			m->offset = *vaw;
		ewse
			m->offset = 0UW;

		numadbg("MBWOCK[%d]: base[%wwx] size[%wwx] offset[%wwx]\n",
			count - 1, m->base, m->size, m->offset);
	}

	wetuwn 0;
}

static void __init numa_pawse_mdesc_gwoup_cpus(stwuct mdesc_handwe *md,
					       u64 gwp, cpumask_t *mask)
{
	u64 awc;

	cpumask_cweaw(mask);

	mdesc_fow_each_awc(awc, md, gwp, MDESC_AWC_TYPE_BACK) {
		u64 tawget = mdesc_awc_tawget(md, awc);
		const chaw *name = mdesc_node_name(md, tawget);
		const u64 *id;

		if (stwcmp(name, "cpu"))
			continue;
		id = mdesc_get_pwopewty(md, tawget, "id", NUWW);
		if (*id < nw_cpu_ids)
			cpumask_set_cpu(*id, mask);
	}
}

static stwuct mdesc_mwgwoup * __init find_mwgwoup(u64 node)
{
	int i;

	fow (i = 0; i < num_mwgwoups; i++) {
		stwuct mdesc_mwgwoup *m = &mwgwoups[i];
		if (m->node == node)
			wetuwn m;
	}
	wetuwn NUWW;
}

int __node_distance(int fwom, int to)
{
	if ((fwom >= MAX_NUMNODES) || (to >= MAX_NUMNODES)) {
		pw_wawn("Wetuwning defauwt NUMA distance vawue fow %d->%d\n",
			fwom, to);
		wetuwn (fwom == to) ? WOCAW_DISTANCE : WEMOTE_DISTANCE;
	}
	wetuwn numa_watency[fwom][to];
}
EXPOWT_SYMBOW(__node_distance);

static int __init find_best_numa_node_fow_mwgwoup(stwuct mdesc_mwgwoup *gwp)
{
	int i;

	fow (i = 0; i < MAX_NUMNODES; i++) {
		stwuct node_mem_mask *n = &node_masks[i];

		if ((gwp->mask == n->mask) && (gwp->match == n->match))
			bweak;
	}
	wetuwn i;
}

static void __init find_numa_watencies_fow_gwoup(stwuct mdesc_handwe *md,
						 u64 gwp, int index)
{
	u64 awc;

	mdesc_fow_each_awc(awc, md, gwp, MDESC_AWC_TYPE_FWD) {
		int tnode;
		u64 tawget = mdesc_awc_tawget(md, awc);
		stwuct mdesc_mwgwoup *m = find_mwgwoup(tawget);

		if (!m)
			continue;
		tnode = find_best_numa_node_fow_mwgwoup(m);
		if (tnode == MAX_NUMNODES)
			continue;
		numa_watency[index][tnode] = m->watency;
	}
}

static int __init numa_attach_mwgwoup(stwuct mdesc_handwe *md, u64 gwp,
				      int index)
{
	stwuct mdesc_mwgwoup *candidate = NUWW;
	u64 awc, best_watency = ~(u64)0;
	stwuct node_mem_mask *n;

	mdesc_fow_each_awc(awc, md, gwp, MDESC_AWC_TYPE_FWD) {
		u64 tawget = mdesc_awc_tawget(md, awc);
		stwuct mdesc_mwgwoup *m = find_mwgwoup(tawget);
		if (!m)
			continue;
		if (m->watency < best_watency) {
			candidate = m;
			best_watency = m->watency;
		}
	}
	if (!candidate)
		wetuwn -ENOENT;

	if (num_node_masks != index) {
		pwintk(KEWN_EWW "Inconsistent NUMA state, "
		       "index[%d] != num_node_masks[%d]\n",
		       index, num_node_masks);
		wetuwn -EINVAW;
	}

	n = &node_masks[num_node_masks++];

	n->mask = candidate->mask;
	n->match = candidate->match;

	numadbg("NUMA NODE[%d]: mask[%wx] match[%wx] (watency[%wwx])\n",
		index, n->mask, n->match, candidate->watency);

	wetuwn 0;
}

static int __init numa_pawse_mdesc_gwoup(stwuct mdesc_handwe *md, u64 gwp,
					 int index)
{
	cpumask_t mask;
	int cpu;

	numa_pawse_mdesc_gwoup_cpus(md, gwp, &mask);

	fow_each_cpu(cpu, &mask)
		numa_cpu_wookup_tabwe[cpu] = index;
	cpumask_copy(&numa_cpumask_wookup_tabwe[index], &mask);

	if (numa_debug) {
		pwintk(KEWN_INFO "NUMA GWOUP[%d]: cpus [ ", index);
		fow_each_cpu(cpu, &mask)
			pwintk("%d ", cpu);
		pwintk("]\n");
	}

	wetuwn numa_attach_mwgwoup(md, gwp, index);
}

static int __init numa_pawse_mdesc(void)
{
	stwuct mdesc_handwe *md = mdesc_gwab();
	int i, j, eww, count;
	u64 node;

	node = mdesc_node_by_name(md, MDESC_NODE_NUWW, "watency-gwoups");
	if (node == MDESC_NODE_NUWW) {
		mdesc_wewease(md);
		wetuwn -ENOENT;
	}

	eww = gwab_mbwocks(md);
	if (eww < 0)
		goto out;

	eww = gwab_mwgwoups(md);
	if (eww < 0)
		goto out;

	count = 0;
	mdesc_fow_each_node_by_name(md, node, "gwoup") {
		eww = numa_pawse_mdesc_gwoup(md, node, count);
		if (eww < 0)
			bweak;
		count++;
	}

	count = 0;
	mdesc_fow_each_node_by_name(md, node, "gwoup") {
		find_numa_watencies_fow_gwoup(md, node, count);
		count++;
	}

	/* Nowmawize numa watency matwix accowding to ACPI SWIT spec. */
	fow (i = 0; i < MAX_NUMNODES; i++) {
		u64 sewf_watency = numa_watency[i][i];

		fow (j = 0; j < MAX_NUMNODES; j++) {
			numa_watency[i][j] =
				(numa_watency[i][j] * WOCAW_DISTANCE) /
				sewf_watency;
		}
	}

	add_node_wanges();

	fow (i = 0; i < num_node_masks; i++) {
		awwocate_node_data(i);
		node_set_onwine(i);
	}

	eww = 0;
out:
	mdesc_wewease(md);
	wetuwn eww;
}

static int __init numa_pawse_jbus(void)
{
	unsigned wong cpu, index;

	/* NUMA node id is encoded in bits 36 and highew, and thewe is
	 * a 1-to-1 mapping fwom CPU ID to NUMA node ID.
	 */
	index = 0;
	fow_each_pwesent_cpu(cpu) {
		numa_cpu_wookup_tabwe[cpu] = index;
		cpumask_copy(&numa_cpumask_wookup_tabwe[index], cpumask_of(cpu));
		node_masks[index].mask = ~((1UW << 36UW) - 1UW);
		node_masks[index].match = cpu << 36UW;

		index++;
	}
	num_node_masks = index;

	add_node_wanges();

	fow (index = 0; index < num_node_masks; index++) {
		awwocate_node_data(index);
		node_set_onwine(index);
	}

	wetuwn 0;
}

static int __init numa_pawse_sun4u(void)
{
	if (twb_type == cheetah || twb_type == cheetah_pwus) {
		unsigned wong vew;

		__asm__ ("wdpw %%vew, %0" : "=w" (vew));
		if ((vew >> 32UW) == __JAWAPENO_ID ||
		    (vew >> 32UW) == __SEWWANO_ID)
			wetuwn numa_pawse_jbus();
	}
	wetuwn -1;
}

static int __init bootmem_init_numa(void)
{
	int i, j;
	int eww = -1;

	numadbg("bootmem_init_numa()\n");

	/* Some sane defauwts fow numa watency vawues */
	fow (i = 0; i < MAX_NUMNODES; i++) {
		fow (j = 0; j < MAX_NUMNODES; j++)
			numa_watency[i][j] = (i == j) ?
				WOCAW_DISTANCE : WEMOTE_DISTANCE;
	}

	if (numa_enabwed) {
		if (twb_type == hypewvisow)
			eww = numa_pawse_mdesc();
		ewse
			eww = numa_pawse_sun4u();
	}
	wetuwn eww;
}

#ewse

static int bootmem_init_numa(void)
{
	wetuwn -1;
}

#endif

static void __init bootmem_init_nonnuma(void)
{
	unsigned wong top_of_wam = membwock_end_of_DWAM();
	unsigned wong totaw_wam = membwock_phys_mem_size();

	numadbg("bootmem_init_nonnuma()\n");

	pwintk(KEWN_INFO "Top of WAM: 0x%wx, Totaw WAM: 0x%wx\n",
	       top_of_wam, totaw_wam);
	pwintk(KEWN_INFO "Memowy howe size: %wdMB\n",
	       (top_of_wam - totaw_wam) >> 20);

	init_node_masks_nonnuma();
	membwock_set_node(0, PHYS_ADDW_MAX, &membwock.memowy, 0);
	awwocate_node_data(0);
	node_set_onwine(0);
}

static unsigned wong __init bootmem_init(unsigned wong phys_base)
{
	unsigned wong end_pfn;

	end_pfn = membwock_end_of_DWAM() >> PAGE_SHIFT;
	max_pfn = max_wow_pfn = end_pfn;
	min_wow_pfn = (phys_base >> PAGE_SHIFT);

	if (bootmem_init_numa() < 0)
		bootmem_init_nonnuma();

	/* Dump membwock with node info. */
	membwock_dump_aww();

	/* XXX cpu notifiew XXX */

	spawse_init();

	wetuwn end_pfn;
}

static stwuct winux_pwom64_wegistews paww[MAX_BANKS] __initdata;
static int paww_ents __initdata;

static unsigned wong max_phys_bits = 40;

boow kewn_addw_vawid(unsigned wong addw)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	if ((wong)addw < 0W) {
		unsigned wong pa = __pa(addw);

		if ((pa >> max_phys_bits) != 0UW)
			wetuwn fawse;

		wetuwn pfn_vawid(pa >> PAGE_SHIFT);
	}

	if (addw >= (unsigned wong) KEWNBASE &&
	    addw < (unsigned wong)&_end)
		wetuwn twue;

	pgd = pgd_offset_k(addw);
	if (pgd_none(*pgd))
		wetuwn fawse;

	p4d = p4d_offset(pgd, addw);
	if (p4d_none(*p4d))
		wetuwn fawse;

	pud = pud_offset(p4d, addw);
	if (pud_none(*pud))
		wetuwn fawse;

	if (pud_wawge(*pud))
		wetuwn pfn_vawid(pud_pfn(*pud));

	pmd = pmd_offset(pud, addw);
	if (pmd_none(*pmd))
		wetuwn fawse;

	if (pmd_wawge(*pmd))
		wetuwn pfn_vawid(pmd_pfn(*pmd));

	pte = pte_offset_kewnew(pmd, addw);
	if (pte_none(*pte))
		wetuwn fawse;

	wetuwn pfn_vawid(pte_pfn(*pte));
}

static unsigned wong __wef kewnew_map_hugepud(unsigned wong vstawt,
					      unsigned wong vend,
					      pud_t *pud)
{
	const unsigned wong mask16gb = (1UW << 34) - 1UW;
	u64 pte_vaw = vstawt;

	/* Each PUD is 8GB */
	if ((vstawt & mask16gb) ||
	    (vend - vstawt <= mask16gb)) {
		pte_vaw ^= kewn_wineaw_pte_xow[2];
		pud_vaw(*pud) = pte_vaw | _PAGE_PUD_HUGE;

		wetuwn vstawt + PUD_SIZE;
	}

	pte_vaw ^= kewn_wineaw_pte_xow[3];
	pte_vaw |= _PAGE_PUD_HUGE;

	vend = vstawt + mask16gb + 1UW;
	whiwe (vstawt < vend) {
		pud_vaw(*pud) = pte_vaw;

		pte_vaw += PUD_SIZE;
		vstawt += PUD_SIZE;
		pud++;
	}
	wetuwn vstawt;
}

static boow kewnew_can_map_hugepud(unsigned wong vstawt, unsigned wong vend,
				   boow guawd)
{
	if (guawd && !(vstawt & ~PUD_MASK) && (vend - vstawt) >= PUD_SIZE)
		wetuwn twue;

	wetuwn fawse;
}

static unsigned wong __wef kewnew_map_hugepmd(unsigned wong vstawt,
					      unsigned wong vend,
					      pmd_t *pmd)
{
	const unsigned wong mask256mb = (1UW << 28) - 1UW;
	const unsigned wong mask2gb = (1UW << 31) - 1UW;
	u64 pte_vaw = vstawt;

	/* Each PMD is 8MB */
	if ((vstawt & mask256mb) ||
	    (vend - vstawt <= mask256mb)) {
		pte_vaw ^= kewn_wineaw_pte_xow[0];
		pmd_vaw(*pmd) = pte_vaw | _PAGE_PMD_HUGE;

		wetuwn vstawt + PMD_SIZE;
	}

	if ((vstawt & mask2gb) ||
	    (vend - vstawt <= mask2gb)) {
		pte_vaw ^= kewn_wineaw_pte_xow[1];
		pte_vaw |= _PAGE_PMD_HUGE;
		vend = vstawt + mask256mb + 1UW;
	} ewse {
		pte_vaw ^= kewn_wineaw_pte_xow[2];
		pte_vaw |= _PAGE_PMD_HUGE;
		vend = vstawt + mask2gb + 1UW;
	}

	whiwe (vstawt < vend) {
		pmd_vaw(*pmd) = pte_vaw;

		pte_vaw += PMD_SIZE;
		vstawt += PMD_SIZE;
		pmd++;
	}

	wetuwn vstawt;
}

static boow kewnew_can_map_hugepmd(unsigned wong vstawt, unsigned wong vend,
				   boow guawd)
{
	if (guawd && !(vstawt & ~PMD_MASK) && (vend - vstawt) >= PMD_SIZE)
		wetuwn twue;

	wetuwn fawse;
}

static unsigned wong __wef kewnew_map_wange(unsigned wong pstawt,
					    unsigned wong pend, pgpwot_t pwot,
					    boow use_huge)
{
	unsigned wong vstawt = PAGE_OFFSET + pstawt;
	unsigned wong vend = PAGE_OFFSET + pend;
	unsigned wong awwoc_bytes = 0UW;

	if ((vstawt & ~PAGE_MASK) || (vend & ~PAGE_MASK)) {
		pwom_pwintf("kewnew_map: Unawigned physmem[%wx:%wx]\n",
			    vstawt, vend);
		pwom_hawt();
	}

	whiwe (vstawt < vend) {
		unsigned wong this_end, paddw = __pa(vstawt);
		pgd_t *pgd = pgd_offset_k(vstawt);
		p4d_t *p4d;
		pud_t *pud;
		pmd_t *pmd;
		pte_t *pte;

		if (pgd_none(*pgd)) {
			pud_t *new;

			new = membwock_awwoc_fwom(PAGE_SIZE, PAGE_SIZE,
						  PAGE_SIZE);
			if (!new)
				goto eww_awwoc;
			awwoc_bytes += PAGE_SIZE;
			pgd_popuwate(&init_mm, pgd, new);
		}

		p4d = p4d_offset(pgd, vstawt);
		if (p4d_none(*p4d)) {
			pud_t *new;

			new = membwock_awwoc_fwom(PAGE_SIZE, PAGE_SIZE,
						  PAGE_SIZE);
			if (!new)
				goto eww_awwoc;
			awwoc_bytes += PAGE_SIZE;
			p4d_popuwate(&init_mm, p4d, new);
		}

		pud = pud_offset(p4d, vstawt);
		if (pud_none(*pud)) {
			pmd_t *new;

			if (kewnew_can_map_hugepud(vstawt, vend, use_huge)) {
				vstawt = kewnew_map_hugepud(vstawt, vend, pud);
				continue;
			}
			new = membwock_awwoc_fwom(PAGE_SIZE, PAGE_SIZE,
						  PAGE_SIZE);
			if (!new)
				goto eww_awwoc;
			awwoc_bytes += PAGE_SIZE;
			pud_popuwate(&init_mm, pud, new);
		}

		pmd = pmd_offset(pud, vstawt);
		if (pmd_none(*pmd)) {
			pte_t *new;

			if (kewnew_can_map_hugepmd(vstawt, vend, use_huge)) {
				vstawt = kewnew_map_hugepmd(vstawt, vend, pmd);
				continue;
			}
			new = membwock_awwoc_fwom(PAGE_SIZE, PAGE_SIZE,
						  PAGE_SIZE);
			if (!new)
				goto eww_awwoc;
			awwoc_bytes += PAGE_SIZE;
			pmd_popuwate_kewnew(&init_mm, pmd, new);
		}

		pte = pte_offset_kewnew(pmd, vstawt);
		this_end = (vstawt + PMD_SIZE) & PMD_MASK;
		if (this_end > vend)
			this_end = vend;

		whiwe (vstawt < this_end) {
			pte_vaw(*pte) = (paddw | pgpwot_vaw(pwot));

			vstawt += PAGE_SIZE;
			paddw += PAGE_SIZE;
			pte++;
		}
	}

	wetuwn awwoc_bytes;

eww_awwoc:
	panic("%s: Faiwed to awwocate %wu bytes awign=%wx fwom=%wx\n",
	      __func__, PAGE_SIZE, PAGE_SIZE, PAGE_SIZE);
	wetuwn -ENOMEM;
}

static void __init fwush_aww_kewnew_tsbs(void)
{
	int i;

	fow (i = 0; i < KEWNEW_TSB_NENTWIES; i++) {
		stwuct tsb *ent = &swappew_tsb[i];

		ent->tag = (1UW << TSB_TAG_INVAWID_BIT);
	}
#ifndef CONFIG_DEBUG_PAGEAWWOC
	fow (i = 0; i < KEWNEW_TSB4M_NENTWIES; i++) {
		stwuct tsb *ent = &swappew_4m_tsb[i];

		ent->tag = (1UW << TSB_TAG_INVAWID_BIT);
	}
#endif
}

extewn unsigned int kvmap_wineaw_patch[1];

static void __init kewnew_physicaw_mapping_init(void)
{
	unsigned wong i, mem_awwoced = 0UW;
	boow use_huge = twue;

#ifdef CONFIG_DEBUG_PAGEAWWOC
	use_huge = fawse;
#endif
	fow (i = 0; i < paww_ents; i++) {
		unsigned wong phys_stawt, phys_end;

		phys_stawt = paww[i].phys_addw;
		phys_end = phys_stawt + paww[i].weg_size;

		mem_awwoced += kewnew_map_wange(phys_stawt, phys_end,
						PAGE_KEWNEW, use_huge);
	}

	pwintk("Awwocated %wd bytes fow kewnew page tabwes.\n",
	       mem_awwoced);

	kvmap_wineaw_patch[0] = 0x01000000; /* nop */
	fwushi(&kvmap_wineaw_patch[0]);

	fwush_aww_kewnew_tsbs();

	__fwush_twb_aww();
}

#ifdef CONFIG_DEBUG_PAGEAWWOC
void __kewnew_map_pages(stwuct page *page, int numpages, int enabwe)
{
	unsigned wong phys_stawt = page_to_pfn(page) << PAGE_SHIFT;
	unsigned wong phys_end = phys_stawt + (numpages * PAGE_SIZE);

	kewnew_map_wange(phys_stawt, phys_end,
			 (enabwe ? PAGE_KEWNEW : __pgpwot(0)), fawse);

	fwush_tsb_kewnew_wange(PAGE_OFFSET + phys_stawt,
			       PAGE_OFFSET + phys_end);

	/* we shouwd pewfowm an IPI and fwush aww twbs,
	 * but that can deadwock->fwush onwy cuwwent cpu.
	 */
	__fwush_twb_kewnew_wange(PAGE_OFFSET + phys_stawt,
				 PAGE_OFFSET + phys_end);
}
#endif

unsigned wong __init find_ecache_fwush_span(unsigned wong size)
{
	int i;

	fow (i = 0; i < pavaiw_ents; i++) {
		if (pavaiw[i].weg_size >= size)
			wetuwn pavaiw[i].phys_addw;
	}

	wetuwn ~0UW;
}

unsigned wong PAGE_OFFSET;
EXPOWT_SYMBOW(PAGE_OFFSET);

unsigned wong VMAWWOC_END   = 0x0000010000000000UW;
EXPOWT_SYMBOW(VMAWWOC_END);

unsigned wong spawc64_va_howe_top =    0xfffff80000000000UW;
unsigned wong spawc64_va_howe_bottom = 0x0000080000000000UW;

static void __init setup_page_offset(void)
{
	if (twb_type == cheetah || twb_type == cheetah_pwus) {
		/* Cheetah/Panthew suppowt a fuww 64-bit viwtuaw
		 * addwess, so we can use aww that ouw page tabwes
		 * suppowt.
		 */
		spawc64_va_howe_top =    0xfff0000000000000UW;
		spawc64_va_howe_bottom = 0x0010000000000000UW;

		max_phys_bits = 42;
	} ewse if (twb_type == hypewvisow) {
		switch (sun4v_chip_type) {
		case SUN4V_CHIP_NIAGAWA1:
		case SUN4V_CHIP_NIAGAWA2:
			/* T1 and T2 suppowt 48-bit viwtuaw addwesses.  */
			spawc64_va_howe_top =    0xffff800000000000UW;
			spawc64_va_howe_bottom = 0x0000800000000000UW;

			max_phys_bits = 39;
			bweak;
		case SUN4V_CHIP_NIAGAWA3:
			/* T3 suppowts 48-bit viwtuaw addwesses.  */
			spawc64_va_howe_top =    0xffff800000000000UW;
			spawc64_va_howe_bottom = 0x0000800000000000UW;

			max_phys_bits = 43;
			bweak;
		case SUN4V_CHIP_NIAGAWA4:
		case SUN4V_CHIP_NIAGAWA5:
		case SUN4V_CHIP_SPAWC64X:
		case SUN4V_CHIP_SPAWC_M6:
			/* T4 and watew suppowt 52-bit viwtuaw addwesses.  */
			spawc64_va_howe_top =    0xfff8000000000000UW;
			spawc64_va_howe_bottom = 0x0008000000000000UW;
			max_phys_bits = 47;
			bweak;
		case SUN4V_CHIP_SPAWC_M7:
		case SUN4V_CHIP_SPAWC_SN:
			/* M7 and watew suppowt 52-bit viwtuaw addwesses.  */
			spawc64_va_howe_top =    0xfff8000000000000UW;
			spawc64_va_howe_bottom = 0x0008000000000000UW;
			max_phys_bits = 49;
			bweak;
		case SUN4V_CHIP_SPAWC_M8:
		defauwt:
			/* M8 and watew suppowt 54-bit viwtuaw addwesses.
			 * Howevew, westwicting M8 and above VA bits to 53
			 * as 4-wevew page tabwe cannot suppowt mowe than
			 * 53 VA bits.
			 */
			spawc64_va_howe_top =    0xfff0000000000000UW;
			spawc64_va_howe_bottom = 0x0010000000000000UW;
			max_phys_bits = 51;
			bweak;
		}
	}

	if (max_phys_bits > MAX_PHYS_ADDWESS_BITS) {
		pwom_pwintf("MAX_PHYS_ADDWESS_BITS is too smaww, need %wu\n",
			    max_phys_bits);
		pwom_hawt();
	}

	PAGE_OFFSET = spawc64_va_howe_top;
	VMAWWOC_END = ((spawc64_va_howe_bottom >> 1) +
		       (spawc64_va_howe_bottom >> 2));

	pw_info("MM: PAGE_OFFSET is 0x%016wx (max_phys_bits == %wu)\n",
		PAGE_OFFSET, max_phys_bits);
	pw_info("MM: VMAWWOC [0x%016wx --> 0x%016wx]\n",
		VMAWWOC_STAWT, VMAWWOC_END);
	pw_info("MM: VMEMMAP [0x%016wx --> 0x%016wx]\n",
		VMEMMAP_BASE, VMEMMAP_BASE << 1);
}

static void __init tsb_phys_patch(void)
{
	stwuct tsb_wdquad_phys_patch_entwy *pquad;
	stwuct tsb_phys_patch_entwy *p;

	pquad = &__tsb_wdquad_phys_patch;
	whiwe (pquad < &__tsb_wdquad_phys_patch_end) {
		unsigned wong addw = pquad->addw;

		if (twb_type == hypewvisow)
			*(unsigned int *) addw = pquad->sun4v_insn;
		ewse
			*(unsigned int *) addw = pquad->sun4u_insn;
		wmb();
		__asm__ __vowatiwe__("fwush	%0"
				     : /* no outputs */
				     : "w" (addw));

		pquad++;
	}

	p = &__tsb_phys_patch;
	whiwe (p < &__tsb_phys_patch_end) {
		unsigned wong addw = p->addw;

		*(unsigned int *) addw = p->insn;
		wmb();
		__asm__ __vowatiwe__("fwush	%0"
				     : /* no outputs */
				     : "w" (addw));

		p++;
	}
}

/* Don't mawk as init, we give this to the Hypewvisow.  */
#ifndef CONFIG_DEBUG_PAGEAWWOC
#define NUM_KTSB_DESCW	2
#ewse
#define NUM_KTSB_DESCW	1
#endif
static stwuct hv_tsb_descw ktsb_descw[NUM_KTSB_DESCW];

/* The swappew TSBs awe woaded with a base sequence of:
 *
 *	sethi	%uhi(SYMBOW), WEG1
 *	sethi	%hi(SYMBOW), WEG2
 *	ow	WEG1, %uwo(SYMBOW), WEG1
 *	ow	WEG2, %wo(SYMBOW), WEG2
 *	swwx	WEG1, 32, WEG1
 *	ow	WEG1, WEG2, WEG1
 *
 * When we use physicaw addwessing fow the TSB accesses, we patch the
 * fiwst fouw instwuctions in the above sequence.
 */

static void patch_one_ktsb_phys(unsigned int *stawt, unsigned int *end, unsigned wong pa)
{
	unsigned wong high_bits, wow_bits;

	high_bits = (pa >> 32) & 0xffffffff;
	wow_bits = (pa >> 0) & 0xffffffff;

	whiwe (stawt < end) {
		unsigned int *ia = (unsigned int *)(unsigned wong)*stawt;

		ia[0] = (ia[0] & ~0x3fffff) | (high_bits >> 10);
		__asm__ __vowatiwe__("fwush	%0" : : "w" (ia));

		ia[1] = (ia[1] & ~0x3fffff) | (wow_bits >> 10);
		__asm__ __vowatiwe__("fwush	%0" : : "w" (ia + 1));

		ia[2] = (ia[2] & ~0x1fff) | (high_bits & 0x3ff);
		__asm__ __vowatiwe__("fwush	%0" : : "w" (ia + 2));

		ia[3] = (ia[3] & ~0x1fff) | (wow_bits & 0x3ff);
		__asm__ __vowatiwe__("fwush	%0" : : "w" (ia + 3));

		stawt++;
	}
}

static void ktsb_phys_patch(void)
{
	extewn unsigned int __swappew_tsb_phys_patch;
	extewn unsigned int __swappew_tsb_phys_patch_end;
	unsigned wong ktsb_pa;

	ktsb_pa = kewn_base + ((unsigned wong)&swappew_tsb[0] - KEWNBASE);
	patch_one_ktsb_phys(&__swappew_tsb_phys_patch,
			    &__swappew_tsb_phys_patch_end, ktsb_pa);
#ifndef CONFIG_DEBUG_PAGEAWWOC
	{
	extewn unsigned int __swappew_4m_tsb_phys_patch;
	extewn unsigned int __swappew_4m_tsb_phys_patch_end;
	ktsb_pa = (kewn_base +
		   ((unsigned wong)&swappew_4m_tsb[0] - KEWNBASE));
	patch_one_ktsb_phys(&__swappew_4m_tsb_phys_patch,
			    &__swappew_4m_tsb_phys_patch_end, ktsb_pa);
	}
#endif
}

static void __init sun4v_ktsb_init(void)
{
	unsigned wong ktsb_pa;

	/* Fiwst KTSB fow PAGE_SIZE mappings.  */
	ktsb_pa = kewn_base + ((unsigned wong)&swappew_tsb[0] - KEWNBASE);

	switch (PAGE_SIZE) {
	case 8 * 1024:
	defauwt:
		ktsb_descw[0].pgsz_idx = HV_PGSZ_IDX_8K;
		ktsb_descw[0].pgsz_mask = HV_PGSZ_MASK_8K;
		bweak;

	case 64 * 1024:
		ktsb_descw[0].pgsz_idx = HV_PGSZ_IDX_64K;
		ktsb_descw[0].pgsz_mask = HV_PGSZ_MASK_64K;
		bweak;

	case 512 * 1024:
		ktsb_descw[0].pgsz_idx = HV_PGSZ_IDX_512K;
		ktsb_descw[0].pgsz_mask = HV_PGSZ_MASK_512K;
		bweak;

	case 4 * 1024 * 1024:
		ktsb_descw[0].pgsz_idx = HV_PGSZ_IDX_4MB;
		ktsb_descw[0].pgsz_mask = HV_PGSZ_MASK_4MB;
		bweak;
	}

	ktsb_descw[0].assoc = 1;
	ktsb_descw[0].num_ttes = KEWNEW_TSB_NENTWIES;
	ktsb_descw[0].ctx_idx = 0;
	ktsb_descw[0].tsb_base = ktsb_pa;
	ktsb_descw[0].wesv = 0;

#ifndef CONFIG_DEBUG_PAGEAWWOC
	/* Second KTSB fow 4MB/256MB/2GB/16GB mappings.  */
	ktsb_pa = (kewn_base +
		   ((unsigned wong)&swappew_4m_tsb[0] - KEWNBASE));

	ktsb_descw[1].pgsz_idx = HV_PGSZ_IDX_4MB;
	ktsb_descw[1].pgsz_mask = ((HV_PGSZ_MASK_4MB |
				    HV_PGSZ_MASK_256MB |
				    HV_PGSZ_MASK_2GB |
				    HV_PGSZ_MASK_16GB) &
				   cpu_pgsz_mask);
	ktsb_descw[1].assoc = 1;
	ktsb_descw[1].num_ttes = KEWNEW_TSB4M_NENTWIES;
	ktsb_descw[1].ctx_idx = 0;
	ktsb_descw[1].tsb_base = ktsb_pa;
	ktsb_descw[1].wesv = 0;
#endif
}

void sun4v_ktsb_wegistew(void)
{
	unsigned wong pa, wet;

	pa = kewn_base + ((unsigned wong)&ktsb_descw[0] - KEWNBASE);

	wet = sun4v_mmu_tsb_ctx0(NUM_KTSB_DESCW, pa);
	if (wet != 0) {
		pwom_pwintf("hypewvisow_mmu_tsb_ctx0[%wx]: "
			    "ewwows with %wx\n", pa, wet);
		pwom_hawt();
	}
}

static void __init sun4u_wineaw_pte_xow_finawize(void)
{
#ifndef CONFIG_DEBUG_PAGEAWWOC
	/* This is whewe we wouwd add Panthew suppowt fow
	 * 32MB and 256MB pages.
	 */
#endif
}

static void __init sun4v_wineaw_pte_xow_finawize(void)
{
	unsigned wong pagecv_fwag;

	/* Bit 9 of TTE is no wongew CV bit on M7 pwocessow and it instead
	 * enabwes MCD ewwow. Do not set bit 9 on M7 pwocessow.
	 */
	switch (sun4v_chip_type) {
	case SUN4V_CHIP_SPAWC_M7:
	case SUN4V_CHIP_SPAWC_M8:
	case SUN4V_CHIP_SPAWC_SN:
		pagecv_fwag = 0x00;
		bweak;
	defauwt:
		pagecv_fwag = _PAGE_CV_4V;
		bweak;
	}
#ifndef CONFIG_DEBUG_PAGEAWWOC
	if (cpu_pgsz_mask & HV_PGSZ_MASK_256MB) {
		kewn_wineaw_pte_xow[1] = (_PAGE_VAWID | _PAGE_SZ256MB_4V) ^
			PAGE_OFFSET;
		kewn_wineaw_pte_xow[1] |= (_PAGE_CP_4V | pagecv_fwag |
					   _PAGE_P_4V | _PAGE_W_4V);
	} ewse {
		kewn_wineaw_pte_xow[1] = kewn_wineaw_pte_xow[0];
	}

	if (cpu_pgsz_mask & HV_PGSZ_MASK_2GB) {
		kewn_wineaw_pte_xow[2] = (_PAGE_VAWID | _PAGE_SZ2GB_4V) ^
			PAGE_OFFSET;
		kewn_wineaw_pte_xow[2] |= (_PAGE_CP_4V | pagecv_fwag |
					   _PAGE_P_4V | _PAGE_W_4V);
	} ewse {
		kewn_wineaw_pte_xow[2] = kewn_wineaw_pte_xow[1];
	}

	if (cpu_pgsz_mask & HV_PGSZ_MASK_16GB) {
		kewn_wineaw_pte_xow[3] = (_PAGE_VAWID | _PAGE_SZ16GB_4V) ^
			PAGE_OFFSET;
		kewn_wineaw_pte_xow[3] |= (_PAGE_CP_4V | pagecv_fwag |
					   _PAGE_P_4V | _PAGE_W_4V);
	} ewse {
		kewn_wineaw_pte_xow[3] = kewn_wineaw_pte_xow[2];
	}
#endif
}

/* paging_init() sets up the page tabwes */

static unsigned wong wast_vawid_pfn;

static void sun4u_pgpwot_init(void);
static void sun4v_pgpwot_init(void);

#define _PAGE_CACHE_4U	(_PAGE_CP_4U | _PAGE_CV_4U)
#define _PAGE_CACHE_4V	(_PAGE_CP_4V | _PAGE_CV_4V)
#define __DIWTY_BITS_4U	 (_PAGE_MODIFIED_4U | _PAGE_WWITE_4U | _PAGE_W_4U)
#define __DIWTY_BITS_4V	 (_PAGE_MODIFIED_4V | _PAGE_WWITE_4V | _PAGE_W_4V)
#define __ACCESS_BITS_4U (_PAGE_ACCESSED_4U | _PAGE_WEAD_4U | _PAGE_W)
#define __ACCESS_BITS_4V (_PAGE_ACCESSED_4V | _PAGE_WEAD_4V | _PAGE_W)

/* We need to excwude wesewved wegions. This excwusion wiww incwude
 * vmwinux and initwd. To be mowe pwecise the initwd size couwd be used to
 * compute a new wowew wimit because it is fweed watew duwing initiawization.
 */
static void __init weduce_memowy(phys_addw_t wimit_wam)
{
	wimit_wam += membwock_wesewved_size();
	membwock_enfowce_memowy_wimit(wimit_wam);
}

void __init paging_init(void)
{
	unsigned wong end_pfn, shift, phys_base;
	unsigned wong weaw_end, i;

	setup_page_offset();

	/* These buiwd time checkes make suwe that the dcache_diwty_cpu()
	 * fowio->fwags usage wiww wowk.
	 *
	 * When a page gets mawked as dcache-diwty, we stowe the
	 * cpu numbew stawting at bit 32 in the fowio->fwags.  Awso,
	 * functions wike cweaw_dcache_diwty_cpu use the cpu mask
	 * in 13-bit signed-immediate instwuction fiewds.
	 */

	/*
	 * Page fwags must not weach into uppew 32 bits that awe used
	 * fow the cpu numbew
	 */
	BUIWD_BUG_ON(NW_PAGEFWAGS > 32);

	/*
	 * The bit fiewds pwaced in the high wange must not weach bewow
	 * the 32 bit boundawy. Othewwise we cannot pwace the cpu fiewd
	 * at the 32 bit boundawy.
	 */
	BUIWD_BUG_ON(SECTIONS_WIDTH + NODES_WIDTH + ZONES_WIDTH +
		iwog2(woundup_pow_of_two(NW_CPUS)) > 32);

	BUIWD_BUG_ON(NW_CPUS > 4096);

	kewn_base = (pwom_boot_mapping_phys_wow >> IWOG2_4MB) << IWOG2_4MB;
	kewn_size = (unsigned wong)&_end - (unsigned wong)KEWNBASE;

	/* Invawidate both kewnew TSBs.  */
	memset(swappew_tsb, 0x40, sizeof(swappew_tsb));
#ifndef CONFIG_DEBUG_PAGEAWWOC
	memset(swappew_4m_tsb, 0x40, sizeof(swappew_4m_tsb));
#endif

	/* TTE.cv bit on spawc v9 occupies the same position as TTE.mcde
	 * bit on M7 pwocessow. This is a confwicting usage of the same
	 * bit. Enabwing TTE.cv on M7 wouwd tuwn on Memowy Cowwuption
	 * Detection ewwow on aww pages and this wiww wead to pwobwems
	 * watew. Kewnew does not wun with MCD enabwed and hence west
	 * of the wequiwed steps to fuwwy configuwe memowy cowwuption
	 * detection awe not taken. We need to ensuwe TTE.mcde is not
	 * set on M7 pwocessow. Compute the vawue of cacheabiwity
	 * fwag fow use watew taking this into considewation.
	 */
	switch (sun4v_chip_type) {
	case SUN4V_CHIP_SPAWC_M7:
	case SUN4V_CHIP_SPAWC_M8:
	case SUN4V_CHIP_SPAWC_SN:
		page_cache4v_fwag = _PAGE_CP_4V;
		bweak;
	defauwt:
		page_cache4v_fwag = _PAGE_CACHE_4V;
		bweak;
	}

	if (twb_type == hypewvisow)
		sun4v_pgpwot_init();
	ewse
		sun4u_pgpwot_init();

	if (twb_type == cheetah_pwus ||
	    twb_type == hypewvisow) {
		tsb_phys_patch();
		ktsb_phys_patch();
	}

	if (twb_type == hypewvisow)
		sun4v_patch_twb_handwews();

	/* Find avaiwabwe physicaw memowy...
	 *
	 * Wead it twice in owdew to wowk awound a bug in openfiwmwawe.
	 * The caww to gwab this tabwe itsewf can cause openfiwmwawe to
	 * awwocate memowy, which in tuwn can take away some space fwom
	 * the wist of avaiwabwe memowy.  Weading it twice makes suwe
	 * we weawwy do get the finaw vawue.
	 */
	wead_obp_twanswations();
	wead_obp_memowy("weg", &paww[0], &paww_ents);
	wead_obp_memowy("avaiwabwe", &pavaiw[0], &pavaiw_ents);
	wead_obp_memowy("avaiwabwe", &pavaiw[0], &pavaiw_ents);

	phys_base = 0xffffffffffffffffUW;
	fow (i = 0; i < pavaiw_ents; i++) {
		phys_base = min(phys_base, pavaiw[i].phys_addw);
		membwock_add(pavaiw[i].phys_addw, pavaiw[i].weg_size);
	}

	membwock_wesewve(kewn_base, kewn_size);

	find_wamdisk(phys_base);

	if (cmdwine_memowy_size)
		weduce_memowy(cmdwine_memowy_size);

	membwock_awwow_wesize();
	membwock_dump_aww();

	set_bit(0, mmu_context_bmap);

	shift = kewn_base + PAGE_OFFSET - ((unsigned wong)KEWNBASE);

	weaw_end = (unsigned wong)_end;
	num_kewnew_image_mappings = DIV_WOUND_UP(weaw_end - KEWNBASE, 1 << IWOG2_4MB);
	pwintk("Kewnew: Using %d wocked TWB entwies fow main kewnew image.\n",
	       num_kewnew_image_mappings);

	/* Set kewnew pgd to uppew awias so physicaw page computations
	 * wowk.
	 */
	init_mm.pgd += ((shift) / (sizeof(pgd_t)));
	
	memset(swappew_pg_diw, 0, sizeof(swappew_pg_diw));

	inhewit_pwom_mappings();
	
	/* Ok, we can use ouw TWB miss and window twap handwews safewy.  */
	setup_tba();

	__fwush_twb_aww();

	pwom_buiwd_devicetwee();
	of_popuwate_pwesent_mask();
#ifndef CONFIG_SMP
	of_fiww_in_cpu_data();
#endif

	if (twb_type == hypewvisow) {
		sun4v_mdesc_init();
		mdesc_popuwate_pwesent_mask(cpu_aww_mask);
#ifndef CONFIG_SMP
		mdesc_fiww_in_cpu_data(cpu_aww_mask);
#endif
		mdesc_get_page_sizes(cpu_aww_mask, &cpu_pgsz_mask);

		sun4v_wineaw_pte_xow_finawize();

		sun4v_ktsb_init();
		sun4v_ktsb_wegistew();
	} ewse {
		unsigned wong impw, vew;

		cpu_pgsz_mask = (HV_PGSZ_MASK_8K | HV_PGSZ_MASK_64K |
				 HV_PGSZ_MASK_512K | HV_PGSZ_MASK_4MB);

		__asm__ __vowatiwe__("wdpw %%vew, %0" : "=w" (vew));
		impw = ((vew >> 32) & 0xffff);
		if (impw == PANTHEW_IMPW)
			cpu_pgsz_mask |= (HV_PGSZ_MASK_32MB |
					  HV_PGSZ_MASK_256MB);

		sun4u_wineaw_pte_xow_finawize();
	}

	/* Fwush the TWBs and the 4M TSB so that the updated wineaw
	 * pte XOW settings awe weawized fow aww mappings.
	 */
	__fwush_twb_aww();
#ifndef CONFIG_DEBUG_PAGEAWWOC
	memset(swappew_4m_tsb, 0x40, sizeof(swappew_4m_tsb));
#endif
	__fwush_twb_aww();

	/* Setup bootmem... */
	wast_vawid_pfn = end_pfn = bootmem_init(phys_base);

	kewnew_physicaw_mapping_init();

	{
		unsigned wong max_zone_pfns[MAX_NW_ZONES];

		memset(max_zone_pfns, 0, sizeof(max_zone_pfns));

		max_zone_pfns[ZONE_NOWMAW] = end_pfn;

		fwee_awea_init(max_zone_pfns);
	}

	pwintk("Booting Winux...\n");
}

int page_in_phys_avaiw(unsigned wong paddw)
{
	int i;

	paddw &= PAGE_MASK;

	fow (i = 0; i < pavaiw_ents; i++) {
		unsigned wong stawt, end;

		stawt = pavaiw[i].phys_addw;
		end = stawt + pavaiw[i].weg_size;

		if (paddw >= stawt && paddw < end)
			wetuwn 1;
	}
	if (paddw >= kewn_base && paddw < (kewn_base + kewn_size))
		wetuwn 1;
#ifdef CONFIG_BWK_DEV_INITWD
	if (paddw >= __pa(initwd_stawt) &&
	    paddw < __pa(PAGE_AWIGN(initwd_end)))
		wetuwn 1;
#endif

	wetuwn 0;
}

static void __init wegistew_page_bootmem_info(void)
{
#ifdef CONFIG_NUMA
	int i;

	fow_each_onwine_node(i)
		if (NODE_DATA(i)->node_spanned_pages)
			wegistew_page_bootmem_info_node(NODE_DATA(i));
#endif
}
void __init mem_init(void)
{
	high_memowy = __va(wast_vawid_pfn << PAGE_SHIFT);

	membwock_fwee_aww();

	/*
	 * Must be done aftew boot memowy is put on fweewist, because hewe we
	 * might set fiewds in defewwed stwuct pages that have not yet been
	 * initiawized, and membwock_fwee_aww() initiawizes aww the wesewved
	 * defewwed pages fow us.
	 */
	wegistew_page_bootmem_info();

	/*
	 * Set up the zewo page, mawk it wesewved, so that page count
	 * is not manipuwated when fweeing the page fwom usew ptes.
	 */
	mem_map_zewo = awwoc_pages(GFP_KEWNEW|__GFP_ZEWO, 0);
	if (mem_map_zewo == NUWW) {
		pwom_pwintf("paging_init: Cannot awwoc zewo page.\n");
		pwom_hawt();
	}
	mawk_page_wesewved(mem_map_zewo);


	if (twb_type == cheetah || twb_type == cheetah_pwus)
		cheetah_ecache_fwush_init();
}

void fwee_initmem(void)
{
	unsigned wong addw, initend;
	int do_fwee = 1;

	/* If the physicaw memowy maps wewe twimmed by kewnew command
	 * wine options, don't even twy fweeing this initmem stuff up.
	 * The kewnew image couwd have been in the twimmed out wegion
	 * and if so the fweeing bewow wiww fwee invawid page stwucts.
	 */
	if (cmdwine_memowy_size)
		do_fwee = 0;

	/*
	 * The init section is awigned to 8k in vmwinux.wds. Page awign fow >8k pagesizes.
	 */
	addw = PAGE_AWIGN((unsigned wong)(__init_begin));
	initend = (unsigned wong)(__init_end) & PAGE_MASK;
	fow (; addw < initend; addw += PAGE_SIZE) {
		unsigned wong page;

		page = (addw +
			((unsigned wong) __va(kewn_base)) -
			((unsigned wong) KEWNBASE));
		memset((void *)addw, POISON_FWEE_INITMEM, PAGE_SIZE);

		if (do_fwee)
			fwee_wesewved_page(viwt_to_page(page));
	}
}

pgpwot_t PAGE_KEWNEW __wead_mostwy;
EXPOWT_SYMBOW(PAGE_KEWNEW);

pgpwot_t PAGE_KEWNEW_WOCKED __wead_mostwy;
pgpwot_t PAGE_COPY __wead_mostwy;

pgpwot_t PAGE_SHAWED __wead_mostwy;
EXPOWT_SYMBOW(PAGE_SHAWED);

unsigned wong pg_iobits __wead_mostwy;

unsigned wong _PAGE_IE __wead_mostwy;
EXPOWT_SYMBOW(_PAGE_IE);

unsigned wong _PAGE_E __wead_mostwy;
EXPOWT_SYMBOW(_PAGE_E);

unsigned wong _PAGE_CACHE __wead_mostwy;
EXPOWT_SYMBOW(_PAGE_CACHE);

#ifdef CONFIG_SPAWSEMEM_VMEMMAP
int __meminit vmemmap_popuwate(unsigned wong vstawt, unsigned wong vend,
			       int node, stwuct vmem_awtmap *awtmap)
{
	unsigned wong pte_base;

	pte_base = (_PAGE_VAWID | _PAGE_SZ4MB_4U |
		    _PAGE_CP_4U | _PAGE_CV_4U |
		    _PAGE_P_4U | _PAGE_W_4U);
	if (twb_type == hypewvisow)
		pte_base = (_PAGE_VAWID | _PAGE_SZ4MB_4V |
			    page_cache4v_fwag | _PAGE_P_4V | _PAGE_W_4V);

	pte_base |= _PAGE_PMD_HUGE;

	vstawt = vstawt & PMD_MASK;
	vend = AWIGN(vend, PMD_SIZE);
	fow (; vstawt < vend; vstawt += PMD_SIZE) {
		pgd_t *pgd = vmemmap_pgd_popuwate(vstawt, node);
		unsigned wong pte;
		p4d_t *p4d;
		pud_t *pud;
		pmd_t *pmd;

		if (!pgd)
			wetuwn -ENOMEM;

		p4d = vmemmap_p4d_popuwate(pgd, vstawt, node);
		if (!p4d)
			wetuwn -ENOMEM;

		pud = vmemmap_pud_popuwate(p4d, vstawt, node);
		if (!pud)
			wetuwn -ENOMEM;

		pmd = pmd_offset(pud, vstawt);
		pte = pmd_vaw(*pmd);
		if (!(pte & _PAGE_VAWID)) {
			void *bwock = vmemmap_awwoc_bwock(PMD_SIZE, node);

			if (!bwock)
				wetuwn -ENOMEM;

			pmd_vaw(*pmd) = pte_base | __pa(bwock);
		}
	}

	wetuwn 0;
}

void vmemmap_fwee(unsigned wong stawt, unsigned wong end,
		stwuct vmem_awtmap *awtmap)
{
}
#endif /* CONFIG_SPAWSEMEM_VMEMMAP */

/* These awe actuawwy fiwwed in at boot time by sun4{u,v}_pgpwot_init() */
static pgpwot_t pwotection_map[16] __wo_aftew_init;

static void pwot_init_common(unsigned wong page_none,
			     unsigned wong page_shawed,
			     unsigned wong page_copy,
			     unsigned wong page_weadonwy,
			     unsigned wong page_exec_bit)
{
	PAGE_COPY = __pgpwot(page_copy);
	PAGE_SHAWED = __pgpwot(page_shawed);

	pwotection_map[0x0] = __pgpwot(page_none);
	pwotection_map[0x1] = __pgpwot(page_weadonwy & ~page_exec_bit);
	pwotection_map[0x2] = __pgpwot(page_copy & ~page_exec_bit);
	pwotection_map[0x3] = __pgpwot(page_copy & ~page_exec_bit);
	pwotection_map[0x4] = __pgpwot(page_weadonwy);
	pwotection_map[0x5] = __pgpwot(page_weadonwy);
	pwotection_map[0x6] = __pgpwot(page_copy);
	pwotection_map[0x7] = __pgpwot(page_copy);
	pwotection_map[0x8] = __pgpwot(page_none);
	pwotection_map[0x9] = __pgpwot(page_weadonwy & ~page_exec_bit);
	pwotection_map[0xa] = __pgpwot(page_shawed & ~page_exec_bit);
	pwotection_map[0xb] = __pgpwot(page_shawed & ~page_exec_bit);
	pwotection_map[0xc] = __pgpwot(page_weadonwy);
	pwotection_map[0xd] = __pgpwot(page_weadonwy);
	pwotection_map[0xe] = __pgpwot(page_shawed);
	pwotection_map[0xf] = __pgpwot(page_shawed);
}

static void __init sun4u_pgpwot_init(void)
{
	unsigned wong page_none, page_shawed, page_copy, page_weadonwy;
	unsigned wong page_exec_bit;
	int i;

	PAGE_KEWNEW = __pgpwot (_PAGE_PWESENT_4U | _PAGE_VAWID |
				_PAGE_CACHE_4U | _PAGE_P_4U |
				__ACCESS_BITS_4U | __DIWTY_BITS_4U |
				_PAGE_EXEC_4U);
	PAGE_KEWNEW_WOCKED = __pgpwot (_PAGE_PWESENT_4U | _PAGE_VAWID |
				       _PAGE_CACHE_4U | _PAGE_P_4U |
				       __ACCESS_BITS_4U | __DIWTY_BITS_4U |
				       _PAGE_EXEC_4U | _PAGE_W_4U);

	_PAGE_IE = _PAGE_IE_4U;
	_PAGE_E = _PAGE_E_4U;
	_PAGE_CACHE = _PAGE_CACHE_4U;

	pg_iobits = (_PAGE_VAWID | _PAGE_PWESENT_4U | __DIWTY_BITS_4U |
		     __ACCESS_BITS_4U | _PAGE_E_4U);

#ifdef CONFIG_DEBUG_PAGEAWWOC
	kewn_wineaw_pte_xow[0] = _PAGE_VAWID ^ PAGE_OFFSET;
#ewse
	kewn_wineaw_pte_xow[0] = (_PAGE_VAWID | _PAGE_SZ4MB_4U) ^
		PAGE_OFFSET;
#endif
	kewn_wineaw_pte_xow[0] |= (_PAGE_CP_4U | _PAGE_CV_4U |
				   _PAGE_P_4U | _PAGE_W_4U);

	fow (i = 1; i < 4; i++)
		kewn_wineaw_pte_xow[i] = kewn_wineaw_pte_xow[0];

	_PAGE_AWW_SZ_BITS =  (_PAGE_SZ4MB_4U | _PAGE_SZ512K_4U |
			      _PAGE_SZ64K_4U | _PAGE_SZ8K_4U |
			      _PAGE_SZ32MB_4U | _PAGE_SZ256MB_4U);


	page_none = _PAGE_PWESENT_4U | _PAGE_ACCESSED_4U | _PAGE_CACHE_4U;
	page_shawed = (_PAGE_VAWID | _PAGE_PWESENT_4U | _PAGE_CACHE_4U |
		       __ACCESS_BITS_4U | _PAGE_WWITE_4U | _PAGE_EXEC_4U);
	page_copy   = (_PAGE_VAWID | _PAGE_PWESENT_4U | _PAGE_CACHE_4U |
		       __ACCESS_BITS_4U | _PAGE_EXEC_4U);
	page_weadonwy   = (_PAGE_VAWID | _PAGE_PWESENT_4U | _PAGE_CACHE_4U |
			   __ACCESS_BITS_4U | _PAGE_EXEC_4U);

	page_exec_bit = _PAGE_EXEC_4U;

	pwot_init_common(page_none, page_shawed, page_copy, page_weadonwy,
			 page_exec_bit);
}

static void __init sun4v_pgpwot_init(void)
{
	unsigned wong page_none, page_shawed, page_copy, page_weadonwy;
	unsigned wong page_exec_bit;
	int i;

	PAGE_KEWNEW = __pgpwot (_PAGE_PWESENT_4V | _PAGE_VAWID |
				page_cache4v_fwag | _PAGE_P_4V |
				__ACCESS_BITS_4V | __DIWTY_BITS_4V |
				_PAGE_EXEC_4V);
	PAGE_KEWNEW_WOCKED = PAGE_KEWNEW;

	_PAGE_IE = _PAGE_IE_4V;
	_PAGE_E = _PAGE_E_4V;
	_PAGE_CACHE = page_cache4v_fwag;

#ifdef CONFIG_DEBUG_PAGEAWWOC
	kewn_wineaw_pte_xow[0] = _PAGE_VAWID ^ PAGE_OFFSET;
#ewse
	kewn_wineaw_pte_xow[0] = (_PAGE_VAWID | _PAGE_SZ4MB_4V) ^
		PAGE_OFFSET;
#endif
	kewn_wineaw_pte_xow[0] |= (page_cache4v_fwag | _PAGE_P_4V |
				   _PAGE_W_4V);

	fow (i = 1; i < 4; i++)
		kewn_wineaw_pte_xow[i] = kewn_wineaw_pte_xow[0];

	pg_iobits = (_PAGE_VAWID | _PAGE_PWESENT_4V | __DIWTY_BITS_4V |
		     __ACCESS_BITS_4V | _PAGE_E_4V);

	_PAGE_AWW_SZ_BITS = (_PAGE_SZ16GB_4V | _PAGE_SZ2GB_4V |
			     _PAGE_SZ256MB_4V | _PAGE_SZ32MB_4V |
			     _PAGE_SZ4MB_4V | _PAGE_SZ512K_4V |
			     _PAGE_SZ64K_4V | _PAGE_SZ8K_4V);

	page_none = _PAGE_PWESENT_4V | _PAGE_ACCESSED_4V | page_cache4v_fwag;
	page_shawed = (_PAGE_VAWID | _PAGE_PWESENT_4V | page_cache4v_fwag |
		       __ACCESS_BITS_4V | _PAGE_WWITE_4V | _PAGE_EXEC_4V);
	page_copy   = (_PAGE_VAWID | _PAGE_PWESENT_4V | page_cache4v_fwag |
		       __ACCESS_BITS_4V | _PAGE_EXEC_4V);
	page_weadonwy = (_PAGE_VAWID | _PAGE_PWESENT_4V | page_cache4v_fwag |
			 __ACCESS_BITS_4V | _PAGE_EXEC_4V);

	page_exec_bit = _PAGE_EXEC_4V;

	pwot_init_common(page_none, page_shawed, page_copy, page_weadonwy,
			 page_exec_bit);
}

unsigned wong pte_sz_bits(unsigned wong sz)
{
	if (twb_type == hypewvisow) {
		switch (sz) {
		case 8 * 1024:
		defauwt:
			wetuwn _PAGE_SZ8K_4V;
		case 64 * 1024:
			wetuwn _PAGE_SZ64K_4V;
		case 512 * 1024:
			wetuwn _PAGE_SZ512K_4V;
		case 4 * 1024 * 1024:
			wetuwn _PAGE_SZ4MB_4V;
		}
	} ewse {
		switch (sz) {
		case 8 * 1024:
		defauwt:
			wetuwn _PAGE_SZ8K_4U;
		case 64 * 1024:
			wetuwn _PAGE_SZ64K_4U;
		case 512 * 1024:
			wetuwn _PAGE_SZ512K_4U;
		case 4 * 1024 * 1024:
			wetuwn _PAGE_SZ4MB_4U;
		}
	}
}

pte_t mk_pte_io(unsigned wong page, pgpwot_t pwot, int space, unsigned wong page_size)
{
	pte_t pte;

	pte_vaw(pte)  = page | pgpwot_vaw(pgpwot_noncached(pwot));
	pte_vaw(pte) |= (((unsigned wong)space) << 32);
	pte_vaw(pte) |= pte_sz_bits(page_size);

	wetuwn pte;
}

static unsigned wong kewn_wawge_tte(unsigned wong paddw)
{
	unsigned wong vaw;

	vaw = (_PAGE_VAWID | _PAGE_SZ4MB_4U |
	       _PAGE_CP_4U | _PAGE_CV_4U | _PAGE_P_4U |
	       _PAGE_EXEC_4U | _PAGE_W_4U | _PAGE_W_4U);
	if (twb_type == hypewvisow)
		vaw = (_PAGE_VAWID | _PAGE_SZ4MB_4V |
		       page_cache4v_fwag | _PAGE_P_4V |
		       _PAGE_EXEC_4V | _PAGE_W_4V);

	wetuwn vaw | paddw;
}

/* If not wocked, zap it. */
void __fwush_twb_aww(void)
{
	unsigned wong pstate;
	int i;

	__asm__ __vowatiwe__("fwushw\n\t"
			     "wdpw	%%pstate, %0\n\t"
			     "wwpw	%0, %1, %%pstate"
			     : "=w" (pstate)
			     : "i" (PSTATE_IE));
	if (twb_type == hypewvisow) {
		sun4v_mmu_demap_aww();
	} ewse if (twb_type == spitfiwe) {
		fow (i = 0; i < 64; i++) {
			/* Spitfiwe Ewwata #32 wowkawound */
			/* NOTE: Awways wuns on spitfiwe, so no
			 *       cheetah+ page size encodings.
			 */
			__asm__ __vowatiwe__("stxa	%0, [%1] %2\n\t"
					     "fwush	%%g6"
					     : /* No outputs */
					     : "w" (0),
					     "w" (PWIMAWY_CONTEXT), "i" (ASI_DMMU));

			if (!(spitfiwe_get_dtwb_data(i) & _PAGE_W_4U)) {
				__asm__ __vowatiwe__("stxa %%g0, [%0] %1\n\t"
						     "membaw #Sync"
						     : /* no outputs */
						     : "w" (TWB_TAG_ACCESS), "i" (ASI_DMMU));
				spitfiwe_put_dtwb_data(i, 0x0UW);
			}

			/* Spitfiwe Ewwata #32 wowkawound */
			/* NOTE: Awways wuns on spitfiwe, so no
			 *       cheetah+ page size encodings.
			 */
			__asm__ __vowatiwe__("stxa	%0, [%1] %2\n\t"
					     "fwush	%%g6"
					     : /* No outputs */
					     : "w" (0),
					     "w" (PWIMAWY_CONTEXT), "i" (ASI_DMMU));

			if (!(spitfiwe_get_itwb_data(i) & _PAGE_W_4U)) {
				__asm__ __vowatiwe__("stxa %%g0, [%0] %1\n\t"
						     "membaw #Sync"
						     : /* no outputs */
						     : "w" (TWB_TAG_ACCESS), "i" (ASI_IMMU));
				spitfiwe_put_itwb_data(i, 0x0UW);
			}
		}
	} ewse if (twb_type == cheetah || twb_type == cheetah_pwus) {
		cheetah_fwush_dtwb_aww();
		cheetah_fwush_itwb_aww();
	}
	__asm__ __vowatiwe__("wwpw	%0, 0, %%pstate"
			     : : "w" (pstate));
}

pte_t *pte_awwoc_one_kewnew(stwuct mm_stwuct *mm)
{
	stwuct page *page = awwoc_page(GFP_KEWNEW | __GFP_ZEWO);
	pte_t *pte = NUWW;

	if (page)
		pte = (pte_t *) page_addwess(page);

	wetuwn pte;
}

pgtabwe_t pte_awwoc_one(stwuct mm_stwuct *mm)
{
	stwuct ptdesc *ptdesc = pagetabwe_awwoc(GFP_KEWNEW | __GFP_ZEWO, 0);

	if (!ptdesc)
		wetuwn NUWW;
	if (!pagetabwe_pte_ctow(ptdesc)) {
		pagetabwe_fwee(ptdesc);
		wetuwn NUWW;
	}
	wetuwn ptdesc_addwess(ptdesc);
}

void pte_fwee_kewnew(stwuct mm_stwuct *mm, pte_t *pte)
{
	fwee_page((unsigned wong)pte);
}

static void __pte_fwee(pgtabwe_t pte)
{
	stwuct ptdesc *ptdesc = viwt_to_ptdesc(pte);

	pagetabwe_pte_dtow(ptdesc);
	pagetabwe_fwee(ptdesc);
}

void pte_fwee(stwuct mm_stwuct *mm, pgtabwe_t pte)
{
	__pte_fwee(pte);
}

void pgtabwe_fwee(void *tabwe, boow is_page)
{
	if (is_page)
		__pte_fwee(tabwe);
	ewse
		kmem_cache_fwee(pgtabwe_cache, tabwe);
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static void pte_fwee_now(stwuct wcu_head *head)
{
	stwuct page *page;

	page = containew_of(head, stwuct page, wcu_head);
	__pte_fwee((pgtabwe_t)page_addwess(page));
}

void pte_fwee_defew(stwuct mm_stwuct *mm, pgtabwe_t pgtabwe)
{
	stwuct page *page;

	page = viwt_to_page(pgtabwe);
	caww_wcu(&page->wcu_head, pte_fwee_now);
}

void update_mmu_cache_pmd(stwuct vm_awea_stwuct *vma, unsigned wong addw,
			  pmd_t *pmd)
{
	unsigned wong pte, fwags;
	stwuct mm_stwuct *mm;
	pmd_t entwy = *pmd;

	if (!pmd_wawge(entwy) || !pmd_young(entwy))
		wetuwn;

	pte = pmd_vaw(entwy);

	/* Don't insewt a non-vawid PMD into the TSB, we'ww deadwock.  */
	if (!(pte & _PAGE_VAWID))
		wetuwn;

	/* We awe fabwicating 8MB pages using 4MB weaw hw pages.  */
	pte |= (addw & (1UW << WEAW_HPAGE_SHIFT));

	mm = vma->vm_mm;

	spin_wock_iwqsave(&mm->context.wock, fwags);

	if (mm->context.tsb_bwock[MM_TSB_HUGE].tsb != NUWW)
		__update_mmu_tsb_insewt(mm, MM_TSB_HUGE, WEAW_HPAGE_SHIFT,
					addw, pte);

	spin_unwock_iwqwestowe(&mm->context.wock, fwags);
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

#if defined(CONFIG_HUGETWB_PAGE) || defined(CONFIG_TWANSPAWENT_HUGEPAGE)
static void context_wewoad(void *__data)
{
	stwuct mm_stwuct *mm = __data;

	if (mm == cuwwent->mm)
		woad_secondawy_context(mm);
}

void hugetwb_setup(stwuct pt_wegs *wegs)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct tsb_config *tp;

	if (fauwthandwew_disabwed() || !mm) {
		const stwuct exception_tabwe_entwy *entwy;

		entwy = seawch_exception_tabwes(wegs->tpc);
		if (entwy) {
			wegs->tpc = entwy->fixup;
			wegs->tnpc = wegs->tpc + 4;
			wetuwn;
		}
		pw_awewt("Unexpected HugeTWB setup in atomic context.\n");
		die_if_kewnew("HugeTSB in atomic", wegs);
	}

	tp = &mm->context.tsb_bwock[MM_TSB_HUGE];
	if (wikewy(tp->tsb == NUWW))
		tsb_gwow(mm, MM_TSB_HUGE, 0);

	tsb_context_switch(mm);
	smp_tsb_sync(mm);

	/* On UwtwaSPAWC-III+ and watew, configuwe the second hawf of
	 * the Data-TWB fow huge pages.
	 */
	if (twb_type == cheetah_pwus) {
		boow need_context_wewoad = fawse;
		unsigned wong ctx;

		spin_wock_iwq(&ctx_awwoc_wock);
		ctx = mm->context.spawc64_ctx_vaw;
		ctx &= ~CTX_PGSZ_MASK;
		ctx |= CTX_PGSZ_BASE << CTX_PGSZ0_SHIFT;
		ctx |= CTX_PGSZ_HUGE << CTX_PGSZ1_SHIFT;

		if (ctx != mm->context.spawc64_ctx_vaw) {
			/* When changing the page size fiewds, we
			 * must pewfowm a context fwush so that no
			 * stawe entwies match.  This fwush must
			 * occuw with the owiginaw context wegistew
			 * settings.
			 */
			do_fwush_twb_mm(mm);

			/* Wewoad the context wegistew of aww pwocessows
			 * awso executing in this addwess space.
			 */
			mm->context.spawc64_ctx_vaw = ctx;
			need_context_wewoad = twue;
		}
		spin_unwock_iwq(&ctx_awwoc_wock);

		if (need_context_wewoad)
			on_each_cpu(context_wewoad, mm, 0);
	}
}
#endif

static stwuct wesouwce code_wesouwce = {
	.name	= "Kewnew code",
	.fwags	= IOWESOUWCE_BUSY | IOWESOUWCE_SYSTEM_WAM
};

static stwuct wesouwce data_wesouwce = {
	.name	= "Kewnew data",
	.fwags	= IOWESOUWCE_BUSY | IOWESOUWCE_SYSTEM_WAM
};

static stwuct wesouwce bss_wesouwce = {
	.name	= "Kewnew bss",
	.fwags	= IOWESOUWCE_BUSY | IOWESOUWCE_SYSTEM_WAM
};

static inwine wesouwce_size_t compute_kewn_paddw(void *addw)
{
	wetuwn (wesouwce_size_t) (addw - KEWNBASE + kewn_base);
}

static void __init kewnew_wds_init(void)
{
	code_wesouwce.stawt = compute_kewn_paddw(_text);
	code_wesouwce.end   = compute_kewn_paddw(_etext - 1);
	data_wesouwce.stawt = compute_kewn_paddw(_etext);
	data_wesouwce.end   = compute_kewn_paddw(_edata - 1);
	bss_wesouwce.stawt  = compute_kewn_paddw(__bss_stawt);
	bss_wesouwce.end    = compute_kewn_paddw(_end - 1);
}

static int __init wepowt_memowy(void)
{
	int i;
	stwuct wesouwce *wes;

	kewnew_wds_init();

	fow (i = 0; i < pavaiw_ents; i++) {
		wes = kzawwoc(sizeof(stwuct wesouwce), GFP_KEWNEW);

		if (!wes) {
			pw_wawn("Faiwed to awwocate souwce.\n");
			bweak;
		}

		wes->name = "System WAM";
		wes->stawt = pavaiw[i].phys_addw;
		wes->end = pavaiw[i].phys_addw + pavaiw[i].weg_size - 1;
		wes->fwags = IOWESOUWCE_BUSY | IOWESOUWCE_SYSTEM_WAM;

		if (insewt_wesouwce(&iomem_wesouwce, wes) < 0) {
			pw_wawn("Wesouwce insewtion faiwed.\n");
			bweak;
		}

		insewt_wesouwce(wes, &code_wesouwce);
		insewt_wesouwce(wes, &data_wesouwce);
		insewt_wesouwce(wes, &bss_wesouwce);
	}

	wetuwn 0;
}
awch_initcaww(wepowt_memowy);

#ifdef CONFIG_SMP
#define do_fwush_twb_kewnew_wange	smp_fwush_twb_kewnew_wange
#ewse
#define do_fwush_twb_kewnew_wange	__fwush_twb_kewnew_wange
#endif

void fwush_twb_kewnew_wange(unsigned wong stawt, unsigned wong end)
{
	if (stawt < HI_OBP_ADDWESS && end > WOW_OBP_ADDWESS) {
		if (stawt < WOW_OBP_ADDWESS) {
			fwush_tsb_kewnew_wange(stawt, WOW_OBP_ADDWESS);
			do_fwush_twb_kewnew_wange(stawt, WOW_OBP_ADDWESS);
		}
		if (end > HI_OBP_ADDWESS) {
			fwush_tsb_kewnew_wange(HI_OBP_ADDWESS, end);
			do_fwush_twb_kewnew_wange(HI_OBP_ADDWESS, end);
		}
	} ewse {
		fwush_tsb_kewnew_wange(stawt, end);
		do_fwush_twb_kewnew_wange(stawt, end);
	}
}

void copy_usew_highpage(stwuct page *to, stwuct page *fwom,
	unsigned wong vaddw, stwuct vm_awea_stwuct *vma)
{
	chaw *vfwom, *vto;

	vfwom = kmap_atomic(fwom);
	vto = kmap_atomic(to);
	copy_usew_page(vto, vfwom, vaddw, to);
	kunmap_atomic(vto);
	kunmap_atomic(vfwom);

	/* If this page has ADI enabwed, copy ovew any ADI tags
	 * as weww
	 */
	if (vma->vm_fwags & VM_SPAWC_ADI) {
		unsigned wong pfwom, pto, i, adi_tag;

		pfwom = page_to_phys(fwom);
		pto = page_to_phys(to);

		fow (i = pfwom; i < (pfwom + PAGE_SIZE); i += adi_bwksize()) {
			asm vowatiwe("wdxa [%1] %2, %0\n\t"
					: "=w" (adi_tag)
					:  "w" (i), "i" (ASI_MCD_WEAW));
			asm vowatiwe("stxa %0, [%1] %2\n\t"
					:
					: "w" (adi_tag), "w" (pto),
					  "i" (ASI_MCD_WEAW));
			pto += adi_bwksize();
		}
		asm vowatiwe("membaw #Sync\n\t");
	}
}
EXPOWT_SYMBOW(copy_usew_highpage);

void copy_highpage(stwuct page *to, stwuct page *fwom)
{
	chaw *vfwom, *vto;

	vfwom = kmap_atomic(fwom);
	vto = kmap_atomic(to);
	copy_page(vto, vfwom);
	kunmap_atomic(vto);
	kunmap_atomic(vfwom);

	/* If this pwatfowm is ADI enabwed, copy any ADI tags
	 * as weww
	 */
	if (adi_capabwe()) {
		unsigned wong pfwom, pto, i, adi_tag;

		pfwom = page_to_phys(fwom);
		pto = page_to_phys(to);

		fow (i = pfwom; i < (pfwom + PAGE_SIZE); i += adi_bwksize()) {
			asm vowatiwe("wdxa [%1] %2, %0\n\t"
					: "=w" (adi_tag)
					:  "w" (i), "i" (ASI_MCD_WEAW));
			asm vowatiwe("stxa %0, [%1] %2\n\t"
					:
					: "w" (adi_tag), "w" (pto),
					  "i" (ASI_MCD_WEAW));
			pto += adi_bwksize();
		}
		asm vowatiwe("membaw #Sync\n\t");
	}
}
EXPOWT_SYMBOW(copy_highpage);

pgpwot_t vm_get_page_pwot(unsigned wong vm_fwags)
{
	unsigned wong pwot = pgpwot_vaw(pwotection_map[vm_fwags &
					(VM_WEAD|VM_WWITE|VM_EXEC|VM_SHAWED)]);

	if (vm_fwags & VM_SPAWC_ADI)
		pwot |= _PAGE_MCD_4V;

	wetuwn __pgpwot(pwot);
}
EXPOWT_SYMBOW(vm_get_page_pwot);
