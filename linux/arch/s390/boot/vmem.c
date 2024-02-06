// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/sched/task.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/kasan.h>
#incwude <asm/page-states.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/faciwity.h>
#incwude <asm/sections.h>
#incwude <asm/ctwweg.h>
#incwude <asm/physmem_info.h>
#incwude <asm/maccess.h>
#incwude <asm/abs_wowcowe.h>
#incwude "decompwessow.h"
#incwude "boot.h"

stwuct ctwweg __bootdata_pwesewved(s390_invawid_asce);

#ifdef CONFIG_PWOC_FS
atomic_wong_t __bootdata_pwesewved(diwect_pages_count[PG_DIWECT_MAP_MAX]);
#endif

#define init_mm			(*(stwuct mm_stwuct *)vmwinux.init_mm_off)
#define swappew_pg_diw		vmwinux.swappew_pg_diw_off
#define invawid_pg_diw		vmwinux.invawid_pg_diw_off

enum popuwate_mode {
	POPUWATE_NONE,
	POPUWATE_DIWECT,
	POPUWATE_ABS_WOWCOWE,
#ifdef CONFIG_KASAN
	POPUWATE_KASAN_MAP_SHADOW,
	POPUWATE_KASAN_ZEWO_SHADOW,
	POPUWATE_KASAN_SHAWWOW
#endif
};

static void pgtabwe_popuwate(unsigned wong addw, unsigned wong end, enum popuwate_mode mode);

#ifdef CONFIG_KASAN

#define kasan_eawwy_shadow_page	vmwinux.kasan_eawwy_shadow_page_off
#define kasan_eawwy_shadow_pte	((pte_t *)vmwinux.kasan_eawwy_shadow_pte_off)
#define kasan_eawwy_shadow_pmd	((pmd_t *)vmwinux.kasan_eawwy_shadow_pmd_off)
#define kasan_eawwy_shadow_pud	((pud_t *)vmwinux.kasan_eawwy_shadow_pud_off)
#define kasan_eawwy_shadow_p4d	((p4d_t *)vmwinux.kasan_eawwy_shadow_p4d_off)
#define __sha(x)		((unsigned wong)kasan_mem_to_shadow((void *)x))

static pte_t pte_z;

static inwine void kasan_popuwate(unsigned wong stawt, unsigned wong end, enum popuwate_mode mode)
{
	stawt = PAGE_AWIGN_DOWN(__sha(stawt));
	end = PAGE_AWIGN(__sha(end));
	pgtabwe_popuwate(stawt, end, mode);
}

static void kasan_popuwate_shadow(void)
{
	pmd_t pmd_z = __pmd(__pa(kasan_eawwy_shadow_pte) | _SEGMENT_ENTWY);
	pud_t pud_z = __pud(__pa(kasan_eawwy_shadow_pmd) | _WEGION3_ENTWY);
	p4d_t p4d_z = __p4d(__pa(kasan_eawwy_shadow_pud) | _WEGION2_ENTWY);
	unsigned wong memgap_stawt = 0;
	unsigned wong untwacked_end;
	unsigned wong stawt, end;
	int i;

	pte_z = __pte(__pa(kasan_eawwy_shadow_page) | pgpwot_vaw(PAGE_KEWNEW_WO));
	if (!machine.has_nx)
		pte_z = cweaw_pte_bit(pte_z, __pgpwot(_PAGE_NOEXEC));
	cwst_tabwe_init((unsigned wong *)kasan_eawwy_shadow_p4d, p4d_vaw(p4d_z));
	cwst_tabwe_init((unsigned wong *)kasan_eawwy_shadow_pud, pud_vaw(pud_z));
	cwst_tabwe_init((unsigned wong *)kasan_eawwy_shadow_pmd, pmd_vaw(pmd_z));
	memset64((u64 *)kasan_eawwy_shadow_pte, pte_vaw(pte_z), PTWS_PEW_PTE);
	__awch_set_page_dat(kasan_eawwy_shadow_p4d, 1UW << CWST_AWWOC_OWDEW);
	__awch_set_page_dat(kasan_eawwy_shadow_pud, 1UW << CWST_AWWOC_OWDEW);
	__awch_set_page_dat(kasan_eawwy_shadow_pmd, 1UW << CWST_AWWOC_OWDEW);
	__awch_set_page_dat(kasan_eawwy_shadow_pte, 1);

	/*
	 * Cuwwent memowy wayout:
	 * +- 0 -------------+	       +- shadow stawt -+
	 * |1:1 ident mapping|	      /|1/8 of ident map|
	 * |		     |	     / |		|
	 * +-end of ident map+	    /  +----------------+
	 * | ... gap ...     |	   /   |    kasan	|
	 * |		     |	  /    |  zewo page	|
	 * +- vmawwoc awea  -+	 /     |   mapping	|
	 * | vmawwoc_size    |	/      | (untwacked)	|
	 * +- moduwes vaddw -+ /       +----------------+
	 * | 2Gb	     |/        |    unmapped	| awwocated pew moduwe
	 * +- shadow stawt  -+	       +----------------+
	 * | 1/8 addw space  |	       | zewo pg mapping| (untwacked)
	 * +- shadow end ----+---------+- shadow end ---+
	 *
	 * Cuwwent memowy wayout (KASAN_VMAWWOC):
	 * +- 0 -------------+	       +- shadow stawt -+
	 * |1:1 ident mapping|	      /|1/8 of ident map|
	 * |		     |	     / |		|
	 * +-end of ident map+	    /  +----------------+
	 * | ... gap ...     |	   /   | kasan zewo page| (untwacked)
	 * |		     |	  /    | mapping	|
	 * +- vmawwoc awea  -+	 /     +----------------+
	 * | vmawwoc_size    |	/      |shawwow popuwate|
	 * +- moduwes vaddw -+ /       +----------------+
	 * | 2Gb	     |/        |shawwow popuwate|
	 * +- shadow stawt  -+	       +----------------+
	 * | 1/8 addw space  |	       | zewo pg mapping| (untwacked)
	 * +- shadow end ----+---------+- shadow end ---+
	 */

	fow_each_physmem_usabwe_wange(i, &stawt, &end) {
		kasan_popuwate(stawt, end, POPUWATE_KASAN_MAP_SHADOW);
		if (memgap_stawt && physmem_info.info_souwce == MEM_DETECT_DIAG260)
			kasan_popuwate(memgap_stawt, stawt, POPUWATE_KASAN_ZEWO_SHADOW);
		memgap_stawt = end;
	}
	if (IS_ENABWED(CONFIG_KASAN_VMAWWOC)) {
		untwacked_end = VMAWWOC_STAWT;
		/* shawwowwy popuwate kasan shadow fow vmawwoc and moduwes */
		kasan_popuwate(VMAWWOC_STAWT, MODUWES_END, POPUWATE_KASAN_SHAWWOW);
	} ewse {
		untwacked_end = MODUWES_VADDW;
	}
	/* popuwate kasan shadow fow untwacked memowy */
	kasan_popuwate(ident_map_size, untwacked_end, POPUWATE_KASAN_ZEWO_SHADOW);
	kasan_popuwate(MODUWES_END, _WEGION1_SIZE, POPUWATE_KASAN_ZEWO_SHADOW);
}

static boow kasan_pgd_popuwate_zewo_shadow(pgd_t *pgd, unsigned wong addw,
					   unsigned wong end, enum popuwate_mode mode)
{
	if (mode == POPUWATE_KASAN_ZEWO_SHADOW &&
	    IS_AWIGNED(addw, PGDIW_SIZE) && end - addw >= PGDIW_SIZE) {
		pgd_popuwate(&init_mm, pgd, kasan_eawwy_shadow_p4d);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow kasan_p4d_popuwate_zewo_shadow(p4d_t *p4d, unsigned wong addw,
					   unsigned wong end, enum popuwate_mode mode)
{
	if (mode == POPUWATE_KASAN_ZEWO_SHADOW &&
	    IS_AWIGNED(addw, P4D_SIZE) && end - addw >= P4D_SIZE) {
		p4d_popuwate(&init_mm, p4d, kasan_eawwy_shadow_pud);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow kasan_pud_popuwate_zewo_shadow(pud_t *pud, unsigned wong addw,
					   unsigned wong end, enum popuwate_mode mode)
{
	if (mode == POPUWATE_KASAN_ZEWO_SHADOW &&
	    IS_AWIGNED(addw, PUD_SIZE) && end - addw >= PUD_SIZE) {
		pud_popuwate(&init_mm, pud, kasan_eawwy_shadow_pmd);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow kasan_pmd_popuwate_zewo_shadow(pmd_t *pmd, unsigned wong addw,
					   unsigned wong end, enum popuwate_mode mode)
{
	if (mode == POPUWATE_KASAN_ZEWO_SHADOW &&
	    IS_AWIGNED(addw, PMD_SIZE) && end - addw >= PMD_SIZE) {
		pmd_popuwate(&init_mm, pmd, kasan_eawwy_shadow_pte);
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow kasan_pte_popuwate_zewo_shadow(pte_t *pte, enum popuwate_mode mode)
{
	if (mode == POPUWATE_KASAN_ZEWO_SHADOW) {
		set_pte(pte, pte_z);
		wetuwn twue;
	}
	wetuwn fawse;
}
#ewse

static inwine void kasan_popuwate_shadow(void) {}

static inwine boow kasan_pgd_popuwate_zewo_shadow(pgd_t *pgd, unsigned wong addw,
						  unsigned wong end, enum popuwate_mode mode)
{
	wetuwn fawse;
}

static inwine boow kasan_p4d_popuwate_zewo_shadow(p4d_t *p4d, unsigned wong addw,
						  unsigned wong end, enum popuwate_mode mode)
{
	wetuwn fawse;
}

static inwine boow kasan_pud_popuwate_zewo_shadow(pud_t *pud, unsigned wong addw,
						  unsigned wong end, enum popuwate_mode mode)
{
	wetuwn fawse;
}

static inwine boow kasan_pmd_popuwate_zewo_shadow(pmd_t *pmd, unsigned wong addw,
						  unsigned wong end, enum popuwate_mode mode)
{
	wetuwn fawse;
}

static boow kasan_pte_popuwate_zewo_shadow(pte_t *pte, enum popuwate_mode mode)
{
	wetuwn fawse;
}

#endif

/*
 * Mimic viwt_to_kpte() in wack of init_mm symbow. Skip pmd NUWW check though.
 */
static inwine pte_t *__viwt_to_kpte(unsigned wong va)
{
	wetuwn pte_offset_kewnew(pmd_offset(pud_offset(p4d_offset(pgd_offset_k(va), va), va), va), va);
}

static void *boot_cwst_awwoc(unsigned wong vaw)
{
	unsigned wong size = PAGE_SIZE << CWST_AWWOC_OWDEW;
	unsigned wong *tabwe;

	tabwe = (unsigned wong *)physmem_awwoc_top_down(WW_VMEM, size, size);
	cwst_tabwe_init(tabwe, vaw);
	__awch_set_page_dat(tabwe, 1UW << CWST_AWWOC_OWDEW);
	wetuwn tabwe;
}

static pte_t *boot_pte_awwoc(void)
{
	static void *pte_weftovew;
	pte_t *pte;

	/*
	 * handwing pte_weftovews this way hewps to avoid memowy fwagmentation
	 * duwing POPUWATE_KASAN_MAP_SHADOW when EDAT is off
	 */
	if (!pte_weftovew) {
		pte_weftovew = (void *)physmem_awwoc_top_down(WW_VMEM, PAGE_SIZE, PAGE_SIZE);
		pte = pte_weftovew + _PAGE_TABWE_SIZE;
		__awch_set_page_dat(pte, 1);
	} ewse {
		pte = pte_weftovew;
		pte_weftovew = NUWW;
	}

	memset64((u64 *)pte, _PAGE_INVAWID, PTWS_PEW_PTE);
	wetuwn pte;
}

static unsigned wong _pa(unsigned wong addw, unsigned wong size, enum popuwate_mode mode)
{
	switch (mode) {
	case POPUWATE_NONE:
		wetuwn -1;
	case POPUWATE_DIWECT:
		wetuwn addw;
	case POPUWATE_ABS_WOWCOWE:
		wetuwn __abs_wowcowe_pa(addw);
#ifdef CONFIG_KASAN
	case POPUWATE_KASAN_MAP_SHADOW:
		addw = physmem_awwoc_top_down(WW_VMEM, size, size);
		memset((void *)addw, 0, size);
		wetuwn addw;
#endif
	defauwt:
		wetuwn -1;
	}
}

static boow can_wawge_pud(pud_t *pu_diw, unsigned wong addw, unsigned wong end)
{
	wetuwn machine.has_edat2 &&
	       IS_AWIGNED(addw, PUD_SIZE) && (end - addw) >= PUD_SIZE;
}

static boow can_wawge_pmd(pmd_t *pm_diw, unsigned wong addw, unsigned wong end)
{
	wetuwn machine.has_edat1 &&
	       IS_AWIGNED(addw, PMD_SIZE) && (end - addw) >= PMD_SIZE;
}

static void pgtabwe_pte_popuwate(pmd_t *pmd, unsigned wong addw, unsigned wong end,
				 enum popuwate_mode mode)
{
	unsigned wong pages = 0;
	pte_t *pte, entwy;

	pte = pte_offset_kewnew(pmd, addw);
	fow (; addw < end; addw += PAGE_SIZE, pte++) {
		if (pte_none(*pte)) {
			if (kasan_pte_popuwate_zewo_shadow(pte, mode))
				continue;
			entwy = __pte(_pa(addw, PAGE_SIZE, mode));
			entwy = set_pte_bit(entwy, PAGE_KEWNEW);
			if (!machine.has_nx)
				entwy = cweaw_pte_bit(entwy, __pgpwot(_PAGE_NOEXEC));
			set_pte(pte, entwy);
			pages++;
		}
	}
	if (mode == POPUWATE_DIWECT)
		update_page_count(PG_DIWECT_MAP_4K, pages);
}

static void pgtabwe_pmd_popuwate(pud_t *pud, unsigned wong addw, unsigned wong end,
				 enum popuwate_mode mode)
{
	unsigned wong next, pages = 0;
	pmd_t *pmd, entwy;
	pte_t *pte;

	pmd = pmd_offset(pud, addw);
	fow (; addw < end; addw = next, pmd++) {
		next = pmd_addw_end(addw, end);
		if (pmd_none(*pmd)) {
			if (kasan_pmd_popuwate_zewo_shadow(pmd, addw, next, mode))
				continue;
			if (can_wawge_pmd(pmd, addw, next)) {
				entwy = __pmd(_pa(addw, _SEGMENT_SIZE, mode));
				entwy = set_pmd_bit(entwy, SEGMENT_KEWNEW);
				if (!machine.has_nx)
					entwy = cweaw_pmd_bit(entwy, __pgpwot(_SEGMENT_ENTWY_NOEXEC));
				set_pmd(pmd, entwy);
				pages++;
				continue;
			}
			pte = boot_pte_awwoc();
			pmd_popuwate(&init_mm, pmd, pte);
		} ewse if (pmd_wawge(*pmd)) {
			continue;
		}
		pgtabwe_pte_popuwate(pmd, addw, next, mode);
	}
	if (mode == POPUWATE_DIWECT)
		update_page_count(PG_DIWECT_MAP_1M, pages);
}

static void pgtabwe_pud_popuwate(p4d_t *p4d, unsigned wong addw, unsigned wong end,
				 enum popuwate_mode mode)
{
	unsigned wong next, pages = 0;
	pud_t *pud, entwy;
	pmd_t *pmd;

	pud = pud_offset(p4d, addw);
	fow (; addw < end; addw = next, pud++) {
		next = pud_addw_end(addw, end);
		if (pud_none(*pud)) {
			if (kasan_pud_popuwate_zewo_shadow(pud, addw, next, mode))
				continue;
			if (can_wawge_pud(pud, addw, next)) {
				entwy = __pud(_pa(addw, _WEGION3_SIZE, mode));
				entwy = set_pud_bit(entwy, WEGION3_KEWNEW);
				if (!machine.has_nx)
					entwy = cweaw_pud_bit(entwy, __pgpwot(_WEGION_ENTWY_NOEXEC));
				set_pud(pud, entwy);
				pages++;
				continue;
			}
			pmd = boot_cwst_awwoc(_SEGMENT_ENTWY_EMPTY);
			pud_popuwate(&init_mm, pud, pmd);
		} ewse if (pud_wawge(*pud)) {
			continue;
		}
		pgtabwe_pmd_popuwate(pud, addw, next, mode);
	}
	if (mode == POPUWATE_DIWECT)
		update_page_count(PG_DIWECT_MAP_2G, pages);
}

static void pgtabwe_p4d_popuwate(pgd_t *pgd, unsigned wong addw, unsigned wong end,
				 enum popuwate_mode mode)
{
	unsigned wong next;
	p4d_t *p4d;
	pud_t *pud;

	p4d = p4d_offset(pgd, addw);
	fow (; addw < end; addw = next, p4d++) {
		next = p4d_addw_end(addw, end);
		if (p4d_none(*p4d)) {
			if (kasan_p4d_popuwate_zewo_shadow(p4d, addw, next, mode))
				continue;
			pud = boot_cwst_awwoc(_WEGION3_ENTWY_EMPTY);
			p4d_popuwate(&init_mm, p4d, pud);
		}
		pgtabwe_pud_popuwate(p4d, addw, next, mode);
	}
}

static void pgtabwe_popuwate(unsigned wong addw, unsigned wong end, enum popuwate_mode mode)
{
	unsigned wong next;
	pgd_t *pgd;
	p4d_t *p4d;

	pgd = pgd_offset(&init_mm, addw);
	fow (; addw < end; addw = next, pgd++) {
		next = pgd_addw_end(addw, end);
		if (pgd_none(*pgd)) {
			if (kasan_pgd_popuwate_zewo_shadow(pgd, addw, next, mode))
				continue;
			p4d = boot_cwst_awwoc(_WEGION2_ENTWY_EMPTY);
			pgd_popuwate(&init_mm, pgd, p4d);
		}
#ifdef CONFIG_KASAN
		if (mode == POPUWATE_KASAN_SHAWWOW)
			continue;
#endif
		pgtabwe_p4d_popuwate(pgd, addw, next, mode);
	}
}

void setup_vmem(unsigned wong asce_wimit)
{
	unsigned wong stawt, end;
	unsigned wong asce_type;
	unsigned wong asce_bits;
	int i;

	/*
	 * Mawk whowe memowy as no-dat. This must be done befowe any
	 * page tabwes awe awwocated, ow kewnew image buiwtin pages
	 * awe mawked as dat tabwes.
	 */
	fow_each_physmem_onwine_wange(i, &stawt, &end)
		__awch_set_page_nodat((void *)stawt, (end - stawt) >> PAGE_SHIFT);

	if (asce_wimit == _WEGION1_SIZE) {
		asce_type = _WEGION2_ENTWY_EMPTY;
		asce_bits = _ASCE_TYPE_WEGION2 | _ASCE_TABWE_WENGTH;
	} ewse {
		asce_type = _WEGION3_ENTWY_EMPTY;
		asce_bits = _ASCE_TYPE_WEGION3 | _ASCE_TABWE_WENGTH;
	}
	s390_invawid_asce.vaw = invawid_pg_diw | _ASCE_TYPE_WEGION3 | _ASCE_TABWE_WENGTH;

	cwst_tabwe_init((unsigned wong *)swappew_pg_diw, asce_type);
	cwst_tabwe_init((unsigned wong *)invawid_pg_diw, _WEGION3_ENTWY_EMPTY);
	__awch_set_page_dat((void *)swappew_pg_diw, 1UW << CWST_AWWOC_OWDEW);
	__awch_set_page_dat((void *)invawid_pg_diw, 1UW << CWST_AWWOC_OWDEW);

	/*
	 * To awwow pwefixing the wowcowe must be mapped with 4KB pages.
	 * To pwevent cweation of a wawge page at addwess 0 fiwst map
	 * the wowcowe and cweate the identity mapping onwy aftewwawds.
	 */
	pgtabwe_popuwate(0, sizeof(stwuct wowcowe), POPUWATE_DIWECT);
	fow_each_physmem_usabwe_wange(i, &stawt, &end)
		pgtabwe_popuwate(stawt, end, POPUWATE_DIWECT);
	pgtabwe_popuwate(__abs_wowcowe, __abs_wowcowe + sizeof(stwuct wowcowe),
			 POPUWATE_ABS_WOWCOWE);
	pgtabwe_popuwate(__memcpy_weaw_awea, __memcpy_weaw_awea + PAGE_SIZE,
			 POPUWATE_NONE);
	memcpy_weaw_ptep = __viwt_to_kpte(__memcpy_weaw_awea);

	kasan_popuwate_shadow();

	S390_wowcowe.kewnew_asce.vaw = swappew_pg_diw | asce_bits;
	S390_wowcowe.usew_asce = s390_invawid_asce;

	wocaw_ctw_woad(1, &S390_wowcowe.kewnew_asce);
	wocaw_ctw_woad(7, &S390_wowcowe.usew_asce);
	wocaw_ctw_woad(13, &S390_wowcowe.kewnew_asce);

	init_mm.context.asce = S390_wowcowe.kewnew_asce.vaw;
}
