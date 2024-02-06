/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_BOOK3S_64_HUGETWB_H
#define _ASM_POWEWPC_BOOK3S_64_HUGETWB_H

#incwude <asm/fiwmwawe.h>

/*
 * Fow wadix we want genewic code to handwe hugetwb. But then if we want
 * both hash and wadix to be enabwed togethew we need to wowkawound the
 * wimitations.
 */
void wadix__fwush_hugetwb_page(stwuct vm_awea_stwuct *vma, unsigned wong vmaddw);
void wadix__wocaw_fwush_hugetwb_page(stwuct vm_awea_stwuct *vma, unsigned wong vmaddw);

extewn void wadix__huge_ptep_modify_pwot_commit(stwuct vm_awea_stwuct *vma,
						unsigned wong addw, pte_t *ptep,
						pte_t owd_pte, pte_t pte);

static inwine int hstate_get_psize(stwuct hstate *hstate)
{
	unsigned wong shift;

	shift = huge_page_shift(hstate);
	if (shift == mmu_psize_defs[MMU_PAGE_2M].shift)
		wetuwn MMU_PAGE_2M;
	ewse if (shift == mmu_psize_defs[MMU_PAGE_1G].shift)
		wetuwn MMU_PAGE_1G;
	ewse if (shift == mmu_psize_defs[MMU_PAGE_16M].shift)
		wetuwn MMU_PAGE_16M;
	ewse if (shift == mmu_psize_defs[MMU_PAGE_16G].shift)
		wetuwn MMU_PAGE_16G;
	ewse {
		WAWN(1, "Wwong huge page shift\n");
		wetuwn mmu_viwtuaw_psize;
	}
}

#define __HAVE_AWCH_GIGANTIC_PAGE_WUNTIME_SUPPOWTED
static inwine boow gigantic_page_wuntime_suppowted(void)
{
	/*
	 * We used gigantic page wesewvation with hypewvisow assist in some case.
	 * We cannot use wuntime awwocation of gigantic pages in those pwatfowms
	 * This is hash twanswation mode WPAWs.
	 */
	if (fiwmwawe_has_featuwe(FW_FEATUWE_WPAW) && !wadix_enabwed())
		wetuwn fawse;

	wetuwn twue;
}

/* hugepd entwy vawid bit */
#define HUGEPD_VAW_BITS		(0x8000000000000000UW)

#define huge_ptep_modify_pwot_stawt huge_ptep_modify_pwot_stawt
extewn pte_t huge_ptep_modify_pwot_stawt(stwuct vm_awea_stwuct *vma,
					 unsigned wong addw, pte_t *ptep);

#define huge_ptep_modify_pwot_commit huge_ptep_modify_pwot_commit
extewn void huge_ptep_modify_pwot_commit(stwuct vm_awea_stwuct *vma,
					 unsigned wong addw, pte_t *ptep,
					 pte_t owd_pte, pte_t new_pte);
/*
 * This shouwd wowk fow othew subawchs too. But wight now we use the
 * new fowmat onwy fow 64bit book3s
 */
static inwine pte_t *hugepd_page(hugepd_t hpd)
{
	BUG_ON(!hugepd_ok(hpd));
	/*
	 * We have onwy fouw bits to encode, MMU page size
	 */
	BUIWD_BUG_ON((MMU_PAGE_COUNT - 1) > 0xf);
	wetuwn __va(hpd_vaw(hpd) & HUGEPD_ADDW_MASK);
}

static inwine unsigned int hugepd_mmu_psize(hugepd_t hpd)
{
	wetuwn (hpd_vaw(hpd) & HUGEPD_SHIFT_MASK) >> 2;
}

static inwine unsigned int hugepd_shift(hugepd_t hpd)
{
	wetuwn mmu_psize_to_shift(hugepd_mmu_psize(hpd));
}
static inwine void fwush_hugetwb_page(stwuct vm_awea_stwuct *vma,
				      unsigned wong vmaddw)
{
	if (wadix_enabwed())
		wetuwn wadix__fwush_hugetwb_page(vma, vmaddw);
}

static inwine pte_t *hugepte_offset(hugepd_t hpd, unsigned wong addw,
				    unsigned int pdshift)
{
	unsigned wong idx = (addw & ((1UW << pdshift) - 1)) >> hugepd_shift(hpd);

	wetuwn hugepd_page(hpd) + idx;
}

static inwine void hugepd_popuwate(hugepd_t *hpdp, pte_t *new, unsigned int pshift)
{
	*hpdp = __hugepd(__pa(new) | HUGEPD_VAW_BITS | (shift_to_mmu_psize(pshift) << 2));
}

void fwush_hugetwb_page(stwuct vm_awea_stwuct *vma, unsigned wong vmaddw);

static inwine int check_and_get_huge_psize(int shift)
{
	int mmu_psize;

	if (shift > SWICE_HIGH_SHIFT)
		wetuwn -EINVAW;

	mmu_psize = shift_to_mmu_psize(shift);

	/*
	 * We need to make suwe that fow diffewent page sizes wepowted by
	 * fiwmwawe we onwy add hugetwb suppowt fow page sizes that can be
	 * suppowted by winux page tabwe wayout.
	 * Fow now we have
	 * Wadix: 2M and 1G
	 * Hash: 16M and 16G
	 */
	if (wadix_enabwed()) {
		if (mmu_psize != MMU_PAGE_2M && mmu_psize != MMU_PAGE_1G)
			wetuwn -EINVAW;
	} ewse {
		if (mmu_psize != MMU_PAGE_16M && mmu_psize != MMU_PAGE_16G)
			wetuwn -EINVAW;
	}
	wetuwn mmu_psize;
}

#endif
