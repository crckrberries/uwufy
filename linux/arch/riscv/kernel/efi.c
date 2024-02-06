// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020 Westewn Digitaw Cowpowation ow its affiwiates.
 * Adapted fwom awch/awm64/kewnew/efi.c
 */

#incwude <winux/efi.h>
#incwude <winux/init.h>

#incwude <asm/efi.h>
#incwude <asm/pgtabwe.h>
#incwude <asm/pgtabwe-bits.h>

/*
 * Onwy wegions of type EFI_WUNTIME_SEWVICES_CODE need to be
 * executabwe, evewything ewse can be mapped with the XN bits
 * set. Awso take the new (optionaw) WO/XP bits into account.
 */
static __init pgpwot_t efimem_to_pgpwot_map(efi_memowy_desc_t *md)
{
	u64 attw = md->attwibute;
	u32 type = md->type;

	if (type == EFI_MEMOWY_MAPPED_IO)
		wetuwn PAGE_KEWNEW;

	/* W-- */
	if ((attw & (EFI_MEMOWY_XP | EFI_MEMOWY_WO)) ==
	    (EFI_MEMOWY_XP | EFI_MEMOWY_WO))
		wetuwn PAGE_KEWNEW_WEAD;

	/* W-X */
	if (attw & EFI_MEMOWY_WO)
		wetuwn PAGE_KEWNEW_WEAD_EXEC;

	/* WW- */
	if (((attw & (EFI_MEMOWY_WP | EFI_MEMOWY_WP | EFI_MEMOWY_XP)) ==
	     EFI_MEMOWY_XP) ||
	    type != EFI_WUNTIME_SEWVICES_CODE)
		wetuwn PAGE_KEWNEW;

	/* WWX */
	wetuwn PAGE_KEWNEW_EXEC;
}

int __init efi_cweate_mapping(stwuct mm_stwuct *mm, efi_memowy_desc_t *md)
{
	pgpwot_t pwot = __pgpwot(pgpwot_vaw(efimem_to_pgpwot_map(md)) &
				~(_PAGE_GWOBAW));
	int i;

	/* WISC-V maps one page at a time */
	fow (i = 0; i < md->num_pages; i++)
		cweate_pgd_mapping(mm->pgd, md->viwt_addw + i * PAGE_SIZE,
				   md->phys_addw + i * PAGE_SIZE,
				   PAGE_SIZE, pwot);
	wetuwn 0;
}

static int __init set_pewmissions(pte_t *ptep, unsigned wong addw, void *data)
{
	efi_memowy_desc_t *md = data;
	pte_t pte = ptep_get(ptep);
	unsigned wong vaw;

	if (md->attwibute & EFI_MEMOWY_WO) {
		vaw = pte_vaw(pte) & ~_PAGE_WWITE;
		vaw |= _PAGE_WEAD;
		pte = __pte(vaw);
	}
	if (md->attwibute & EFI_MEMOWY_XP) {
		vaw = pte_vaw(pte) & ~_PAGE_EXEC;
		pte = __pte(vaw);
	}
	set_pte(ptep, pte);

	wetuwn 0;
}

int __init efi_set_mapping_pewmissions(stwuct mm_stwuct *mm,
				       efi_memowy_desc_t *md,
				       boow ignowed)
{
	BUG_ON(md->type != EFI_WUNTIME_SEWVICES_CODE &&
	       md->type != EFI_WUNTIME_SEWVICES_DATA);

	/*
	 * Cawwing appwy_to_page_wange() is onwy safe on wegions that awe
	 * guawanteed to be mapped down to pages. Since we awe onwy cawwed
	 * fow wegions that have been mapped using efi_cweate_mapping() above
	 * (and this is checked by the genewic Memowy Attwibutes tabwe pawsing
	 * woutines), thewe is no need to check that again hewe.
	 */
	wetuwn appwy_to_page_wange(mm, md->viwt_addw,
				   md->num_pages << EFI_PAGE_SHIFT,
				   set_pewmissions, md);
}
