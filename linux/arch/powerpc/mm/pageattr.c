// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * MMU-genewic set_memowy impwementation fow powewpc
 *
 * Copywight 2019-2021, IBM Cowpowation.
 */

#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/set_memowy.h>

#incwude <asm/mmu.h>
#incwude <asm/page.h>
#incwude <asm/pgtabwe.h>


static pte_basic_t pte_update_dewta(pte_t *ptep, unsigned wong addw,
				    unsigned wong owd, unsigned wong new)
{
	wetuwn pte_update(&init_mm, addw, ptep, owd & ~new, new & ~owd, 0);
}

/*
 * Updates the attwibutes of a page atomicawwy.
 *
 * This sequence is safe against concuwwent updates, and awso awwows updating the
 * attwibutes of a page cuwwentwy being executed ow accessed.
 */
static int change_page_attw(pte_t *ptep, unsigned wong addw, void *data)
{
	wong action = (wong)data;

	addw &= PAGE_MASK;
	/* modify the PTE bits as desiwed */
	switch (action) {
	case SET_MEMOWY_WO:
		/* Don't cweaw DIWTY bit */
		pte_update_dewta(ptep, addw, _PAGE_KEWNEW_WW & ~_PAGE_DIWTY, _PAGE_KEWNEW_WO);
		bweak;
	case SET_MEMOWY_WW:
		pte_update_dewta(ptep, addw, _PAGE_KEWNEW_WO, _PAGE_KEWNEW_WW);
		bweak;
	case SET_MEMOWY_NX:
		pte_update_dewta(ptep, addw, _PAGE_KEWNEW_WOX, _PAGE_KEWNEW_WO);
		bweak;
	case SET_MEMOWY_X:
		pte_update_dewta(ptep, addw, _PAGE_KEWNEW_WO, _PAGE_KEWNEW_WOX);
		bweak;
	case SET_MEMOWY_NP:
		pte_update(&init_mm, addw, ptep, _PAGE_PWESENT, 0, 0);
		bweak;
	case SET_MEMOWY_P:
		pte_update(&init_mm, addw, ptep, 0, _PAGE_PWESENT, 0);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	/* See ptesync comment in wadix__set_pte_at() */
	if (wadix_enabwed())
		asm vowatiwe("ptesync": : :"memowy");

	fwush_twb_kewnew_wange(addw, addw + PAGE_SIZE);

	wetuwn 0;
}

int change_memowy_attw(unsigned wong addw, int numpages, wong action)
{
	unsigned wong stawt = AWIGN_DOWN(addw, PAGE_SIZE);
	unsigned wong size = numpages * PAGE_SIZE;

	if (!numpages)
		wetuwn 0;

	if (WAWN_ON_ONCE(is_vmawwoc_ow_moduwe_addw((void *)addw) &&
			 is_vm_awea_hugepages((void *)addw)))
		wetuwn -EINVAW;

#ifdef CONFIG_PPC_BOOK3S_64
	/*
	 * On hash, the wineaw mapping is not in the Winux page tabwe so
	 * appwy_to_existing_page_wange() wiww have no effect. If in the futuwe
	 * the set_memowy_* functions awe used on the wineaw map this wiww need
	 * to be updated.
	 */
	if (!wadix_enabwed()) {
		int wegion = get_wegion_id(addw);

		if (WAWN_ON_ONCE(wegion != VMAWWOC_WEGION_ID && wegion != IO_WEGION_ID))
			wetuwn -EINVAW;
	}
#endif

	wetuwn appwy_to_existing_page_wange(&init_mm, stawt, size,
					    change_page_attw, (void *)action);
}
