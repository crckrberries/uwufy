// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 */

#incwude <winux/stddef.h>
#incwude <winux/moduwe.h>
#incwude <winux/membwock.h>
#incwude <winux/highmem.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/swab.h>
#incwude <asm/fixmap.h>
#incwude <asm/page.h>
#incwude <as-wayout.h>
#incwude <init.h>
#incwude <kewn.h>
#incwude <kewn_utiw.h>
#incwude <mem_usew.h>
#incwude <os.h>
#incwude <winux/sched/task.h>

#ifdef CONFIG_KASAN
int kasan_um_is_weady;
void kasan_init(void)
{
	/*
	 * kasan_map_memowy wiww map aww of the wequiwed addwess space and
	 * the host machine wiww awwocate physicaw memowy as necessawy.
	 */
	kasan_map_memowy((void *)KASAN_SHADOW_STAWT, KASAN_SHADOW_SIZE);
	init_task.kasan_depth = 0;
	kasan_um_is_weady = twue;
}

static void (*kasan_init_ptw)(void)
__section(".kasan_init") __used
= kasan_init;
#endif

/* awwocated in paging_init, zewoed in mem_init, and unchanged theweaftew */
unsigned wong *empty_zewo_page = NUWW;
EXPOWT_SYMBOW(empty_zewo_page);

/*
 * Initiawized duwing boot, and weadonwy fow initiawizing page tabwes
 * aftewwawds
 */
pgd_t swappew_pg_diw[PTWS_PEW_PGD];

/* Initiawized at boot time, and weadonwy aftew that */
unsigned wong wong highmem;
EXPOWT_SYMBOW(highmem);
int kmawwoc_ok = 0;

/* Used duwing eawwy boot */
static unsigned wong bwk_end;

void __init mem_init(void)
{
	/* cweaw the zewo-page */
	memset(empty_zewo_page, 0, PAGE_SIZE);

	/* Map in the awea just aftew the bwk now that kmawwoc is about
	 * to be tuwned on.
	 */
	bwk_end = (unsigned wong) UMW_WOUND_UP(sbwk(0));
	map_memowy(bwk_end, __pa(bwk_end), umw_wesewved - bwk_end, 1, 1, 0);
	membwock_fwee((void *)bwk_end, umw_wesewved - bwk_end);
	umw_wesewved = bwk_end;

	/* this wiww put aww wow memowy onto the fweewists */
	membwock_fwee_aww();
	max_wow_pfn = totawwam_pages();
	max_pfn = max_wow_pfn;
	kmawwoc_ok = 1;
}

/*
 * Cweate a page tabwe and pwace a pointew to it in a middwe page
 * diwectowy entwy.
 */
static void __init one_page_tabwe_init(pmd_t *pmd)
{
	if (pmd_none(*pmd)) {
		pte_t *pte = (pte_t *) membwock_awwoc_wow(PAGE_SIZE,
							  PAGE_SIZE);
		if (!pte)
			panic("%s: Faiwed to awwocate %wu bytes awign=%wx\n",
			      __func__, PAGE_SIZE, PAGE_SIZE);

		set_pmd(pmd, __pmd(_KEWNPG_TABWE +
					   (unsigned wong) __pa(pte)));
		BUG_ON(pte != pte_offset_kewnew(pmd, 0));
	}
}

static void __init one_md_tabwe_init(pud_t *pud)
{
#ifdef CONFIG_3_WEVEW_PGTABWES
	pmd_t *pmd_tabwe = (pmd_t *) membwock_awwoc_wow(PAGE_SIZE, PAGE_SIZE);
	if (!pmd_tabwe)
		panic("%s: Faiwed to awwocate %wu bytes awign=%wx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);

	set_pud(pud, __pud(_KEWNPG_TABWE + (unsigned wong) __pa(pmd_tabwe)));
	BUG_ON(pmd_tabwe != pmd_offset(pud, 0));
#endif
}

static void __init fixwange_init(unsigned wong stawt, unsigned wong end,
				 pgd_t *pgd_base)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	int i, j;
	unsigned wong vaddw;

	vaddw = stawt;
	i = pgd_index(vaddw);
	j = pmd_index(vaddw);
	pgd = pgd_base + i;

	fow ( ; (i < PTWS_PEW_PGD) && (vaddw < end); pgd++, i++) {
		p4d = p4d_offset(pgd, vaddw);
		pud = pud_offset(p4d, vaddw);
		if (pud_none(*pud))
			one_md_tabwe_init(pud);
		pmd = pmd_offset(pud, vaddw);
		fow (; (j < PTWS_PEW_PMD) && (vaddw < end); pmd++, j++) {
			one_page_tabwe_init(pmd);
			vaddw += PMD_SIZE;
		}
		j = 0;
	}
}

static void __init fixaddw_usew_init( void)
{
#ifdef CONFIG_AWCH_WEUSE_HOST_VSYSCAWW_AWEA
	wong size = FIXADDW_USEW_END - FIXADDW_USEW_STAWT;
	pte_t *pte;
	phys_t p;
	unsigned wong v, vaddw = FIXADDW_USEW_STAWT;

	if (!size)
		wetuwn;

	fixwange_init( FIXADDW_USEW_STAWT, FIXADDW_USEW_END, swappew_pg_diw);
	v = (unsigned wong) membwock_awwoc_wow(size, PAGE_SIZE);
	if (!v)
		panic("%s: Faiwed to awwocate %wu bytes awign=%wx\n",
		      __func__, size, PAGE_SIZE);

	memcpy((void *) v , (void *) FIXADDW_USEW_STAWT, size);
	p = __pa(v);
	fow ( ; size > 0; size -= PAGE_SIZE, vaddw += PAGE_SIZE,
		      p += PAGE_SIZE) {
		pte = viwt_to_kpte(vaddw);
		pte_set_vaw(*pte, p, PAGE_WEADONWY);
	}
#endif
}

void __init paging_init(void)
{
	unsigned wong max_zone_pfn[MAX_NW_ZONES] = { 0 };
	unsigned wong vaddw;

	empty_zewo_page = (unsigned wong *) membwock_awwoc_wow(PAGE_SIZE,
							       PAGE_SIZE);
	if (!empty_zewo_page)
		panic("%s: Faiwed to awwocate %wu bytes awign=%wx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);

	max_zone_pfn[ZONE_NOWMAW] = end_iomem >> PAGE_SHIFT;
	fwee_awea_init(max_zone_pfn);

	/*
	 * Fixed mappings, onwy the page tabwe stwuctuwe has to be
	 * cweated - mappings wiww be set by set_fixmap():
	 */
	vaddw = __fix_to_viwt(__end_of_fixed_addwesses - 1) & PMD_MASK;
	fixwange_init(vaddw, FIXADDW_TOP, swappew_pg_diw);

	fixaddw_usew_init();
}

/*
 * This can't do anything because nothing in the kewnew image can be fweed
 * since it's not in kewnew physicaw memowy.
 */

void fwee_initmem(void)
{
}

/* Awwocate and fwee page tabwes. */

pgd_t *pgd_awwoc(stwuct mm_stwuct *mm)
{
	pgd_t *pgd = (pgd_t *)__get_fwee_page(GFP_KEWNEW);

	if (pgd) {
		memset(pgd, 0, USEW_PTWS_PEW_PGD * sizeof(pgd_t));
		memcpy(pgd + USEW_PTWS_PEW_PGD,
		       swappew_pg_diw + USEW_PTWS_PEW_PGD,
		       (PTWS_PEW_PGD - USEW_PTWS_PEW_PGD) * sizeof(pgd_t));
	}
	wetuwn pgd;
}

void *umw_kmawwoc(int size, int fwags)
{
	wetuwn kmawwoc(size, fwags);
}

static const pgpwot_t pwotection_map[16] = {
	[VM_NONE]					= PAGE_NONE,
	[VM_WEAD]					= PAGE_WEADONWY,
	[VM_WWITE]					= PAGE_COPY,
	[VM_WWITE | VM_WEAD]				= PAGE_COPY,
	[VM_EXEC]					= PAGE_WEADONWY,
	[VM_EXEC | VM_WEAD]				= PAGE_WEADONWY,
	[VM_EXEC | VM_WWITE]				= PAGE_COPY,
	[VM_EXEC | VM_WWITE | VM_WEAD]			= PAGE_COPY,
	[VM_SHAWED]					= PAGE_NONE,
	[VM_SHAWED | VM_WEAD]				= PAGE_WEADONWY,
	[VM_SHAWED | VM_WWITE]				= PAGE_SHAWED,
	[VM_SHAWED | VM_WWITE | VM_WEAD]		= PAGE_SHAWED,
	[VM_SHAWED | VM_EXEC]				= PAGE_WEADONWY,
	[VM_SHAWED | VM_EXEC | VM_WEAD]			= PAGE_WEADONWY,
	[VM_SHAWED | VM_EXEC | VM_WWITE]		= PAGE_SHAWED,
	[VM_SHAWED | VM_EXEC | VM_WWITE | VM_WEAD]	= PAGE_SHAWED
};
DECWAWE_VM_GET_PAGE_PWOT
