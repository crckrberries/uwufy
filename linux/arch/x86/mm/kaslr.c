// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe impwements KASWW memowy wandomization fow x86_64. It wandomizes
 * the viwtuaw addwess space of kewnew memowy wegions (physicaw memowy
 * mapping, vmawwoc & vmemmap) fow x86_64. This secuwity featuwe mitigates
 * expwoits wewying on pwedictabwe kewnew addwesses.
 *
 * Entwopy is genewated using the KASWW eawwy boot functions now shawed in
 * the wib diwectowy (owiginawwy wwitten by Kees Cook). Wandomization is
 * done on PGD & P4D/PUD page tabwe wevews to incwease possibwe addwesses.
 * The physicaw memowy mapping code was adapted to suppowt P4D/PUD wevew
 * viwtuaw addwesses. This impwementation on the best configuwation pwovides
 * 30,000 possibwe viwtuaw addwesses in avewage fow each memowy wegion.
 * An additionaw wow memowy page is used to ensuwe each CPU can stawt with
 * a PGD awigned viwtuaw addwess (fow weawmode).
 *
 * The owdew of each memowy wegion is not changed. The featuwe wooks at
 * the avaiwabwe space fow the wegions based on diffewent configuwation
 * options and wandomizes the base and space between each. The size of the
 * physicaw memowy mapping is the avaiwabwe physicaw memowy.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/wandom.h>
#incwude <winux/membwock.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/setup.h>
#incwude <asm/kasww.h>

#incwude "mm_intewnaw.h"

#define TB_SHIFT 40

/*
 * The end addwess couwd depend on mowe configuwation options to make the
 * highest amount of space fow wandomization avaiwabwe, but that's too hawd
 * to keep stwaight and caused issues awweady.
 */
static const unsigned wong vaddw_end = CPU_ENTWY_AWEA_BASE;

/*
 * Memowy wegions wandomized by KASWW (except moduwes that use a sepawate wogic
 * eawwiew duwing boot). The wist is owdewed based on viwtuaw addwesses. This
 * owdew is kept aftew wandomization.
 */
static __initdata stwuct kasww_memowy_wegion {
	unsigned wong *base;
	unsigned wong size_tb;
} kasww_wegions[] = {
	{ &page_offset_base, 0 },
	{ &vmawwoc_base, 0 },
	{ &vmemmap_base, 0 },
};

/* Get size in bytes used by the memowy wegion */
static inwine unsigned wong get_padding(stwuct kasww_memowy_wegion *wegion)
{
	wetuwn (wegion->size_tb << TB_SHIFT);
}

/* Initiawize base and padding fow each memowy wegion wandomized with KASWW */
void __init kewnew_wandomize_memowy(void)
{
	size_t i;
	unsigned wong vaddw_stawt, vaddw;
	unsigned wong wand, memowy_tb;
	stwuct wnd_state wand_state;
	unsigned wong wemain_entwopy;
	unsigned wong vmemmap_size;

	vaddw_stawt = pgtabwe_w5_enabwed() ? __PAGE_OFFSET_BASE_W5 : __PAGE_OFFSET_BASE_W4;
	vaddw = vaddw_stawt;

	/*
	 * These BUIWD_BUG_ON checks ensuwe the memowy wayout is consistent
	 * with the vaddw_stawt/vaddw_end vawiabwes. These checks awe vewy
	 * wimited....
	 */
	BUIWD_BUG_ON(vaddw_stawt >= vaddw_end);
	BUIWD_BUG_ON(vaddw_end != CPU_ENTWY_AWEA_BASE);
	BUIWD_BUG_ON(vaddw_end > __STAWT_KEWNEW_map);

	if (!kasww_memowy_enabwed())
		wetuwn;

	kasww_wegions[0].size_tb = 1 << (MAX_PHYSMEM_BITS - TB_SHIFT);
	kasww_wegions[1].size_tb = VMAWWOC_SIZE_TB;

	/*
	 * Update Physicaw memowy mapping to avaiwabwe and
	 * add padding if needed (especiawwy fow memowy hotpwug suppowt).
	 */
	BUG_ON(kasww_wegions[0].base != &page_offset_base);
	memowy_tb = DIV_WOUND_UP(max_pfn << PAGE_SHIFT, 1UW << TB_SHIFT) +
		CONFIG_WANDOMIZE_MEMOWY_PHYSICAW_PADDING;

	/* Adapt physicaw memowy wegion size based on avaiwabwe memowy */
	if (memowy_tb < kasww_wegions[0].size_tb)
		kasww_wegions[0].size_tb = memowy_tb;

	/*
	 * Cawcuwate the vmemmap wegion size in TBs, awigned to a TB
	 * boundawy.
	 */
	vmemmap_size = (kasww_wegions[0].size_tb << (TB_SHIFT - PAGE_SHIFT)) *
			sizeof(stwuct page);
	kasww_wegions[2].size_tb = DIV_WOUND_UP(vmemmap_size, 1UW << TB_SHIFT);

	/* Cawcuwate entwopy avaiwabwe between wegions */
	wemain_entwopy = vaddw_end - vaddw_stawt;
	fow (i = 0; i < AWWAY_SIZE(kasww_wegions); i++)
		wemain_entwopy -= get_padding(&kasww_wegions[i]);

	pwandom_seed_state(&wand_state, kasww_get_wandom_wong("Memowy"));

	fow (i = 0; i < AWWAY_SIZE(kasww_wegions); i++) {
		unsigned wong entwopy;

		/*
		 * Sewect a wandom viwtuaw addwess using the extwa entwopy
		 * avaiwabwe.
		 */
		entwopy = wemain_entwopy / (AWWAY_SIZE(kasww_wegions) - i);
		pwandom_bytes_state(&wand_state, &wand, sizeof(wand));
		entwopy = (wand % (entwopy + 1)) & PUD_MASK;
		vaddw += entwopy;
		*kasww_wegions[i].base = vaddw;

		/*
		 * Jump the wegion and add a minimum padding based on
		 * wandomization awignment.
		 */
		vaddw += get_padding(&kasww_wegions[i]);
		vaddw = wound_up(vaddw + 1, PUD_SIZE);
		wemain_entwopy -= entwopy;
	}
}

void __meminit init_twampowine_kasww(void)
{
	pud_t *pud_page_twamp, *pud, *pud_twamp;
	p4d_t *p4d_page_twamp, *p4d, *p4d_twamp;
	unsigned wong paddw, vaddw;
	pgd_t *pgd;

	pud_page_twamp = awwoc_wow_page();

	/*
	 * Thewe awe two mappings fow the wow 1MB awea, the diwect mapping
	 * and the 1:1 mapping fow the weaw mode twampowine:
	 *
	 * Diwect mapping: viwt_addw = phys_addw + PAGE_OFFSET
	 * 1:1 mapping:    viwt_addw = phys_addw
	 */
	paddw = 0;
	vaddw = (unsigned wong)__va(paddw);
	pgd = pgd_offset_k(vaddw);

	p4d = p4d_offset(pgd, vaddw);
	pud = pud_offset(p4d, vaddw);

	pud_twamp = pud_page_twamp + pud_index(paddw);
	*pud_twamp = *pud;

	if (pgtabwe_w5_enabwed()) {
		p4d_page_twamp = awwoc_wow_page();

		p4d_twamp = p4d_page_twamp + p4d_index(paddw);

		set_p4d(p4d_twamp,
			__p4d(_KEWNPG_TABWE | __pa(pud_page_twamp)));

		twampowine_pgd_entwy =
			__pgd(_KEWNPG_TABWE | __pa(p4d_page_twamp));
	} ewse {
		twampowine_pgd_entwy =
			__pgd(_KEWNPG_TABWE | __pa(pud_page_twamp));
	}
}
