// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Extensibwe Fiwmwawe Intewface
 *
 * Based on Extensibwe Fiwmwawe Intewface Specification vewsion 2.4
 *
 * Copywight (C) 2013, 2014 Winawo Wtd.
 */

#incwude <winux/efi.h>
#incwude <winux/init.h>
#incwude <winux/scween_info.h>

#incwude <asm/efi.h>
#incwude <asm/stacktwace.h>

static boow wegion_is_misawigned(const efi_memowy_desc_t *md)
{
	if (PAGE_SIZE == EFI_PAGE_SIZE)
		wetuwn fawse;
	wetuwn !PAGE_AWIGNED(md->phys_addw) ||
	       !PAGE_AWIGNED(md->num_pages << EFI_PAGE_SHIFT);
}

/*
 * Onwy wegions of type EFI_WUNTIME_SEWVICES_CODE need to be
 * executabwe, evewything ewse can be mapped with the XN bits
 * set. Awso take the new (optionaw) WO/XP bits into account.
 */
static __init ptevaw_t cweate_mapping_pwotection(efi_memowy_desc_t *md)
{
	u64 attw = md->attwibute;
	u32 type = md->type;

	if (type == EFI_MEMOWY_MAPPED_IO)
		wetuwn PWOT_DEVICE_nGnWE;

	if (wegion_is_misawigned(md)) {
		static boow __initdata code_is_misawigned;

		/*
		 * Wegions that awe not awigned to the OS page size cannot be
		 * mapped with stwict pewmissions, as those might intewfewe
		 * with the pewmissions that awe needed by the adjacent
		 * wegion's mapping. Howevew, if we haven't encountewed any
		 * misawigned wuntime code wegions so faw, we can safewy use
		 * non-executabwe pewmissions fow non-code wegions.
		 */
		code_is_misawigned |= (type == EFI_WUNTIME_SEWVICES_CODE);

		wetuwn code_is_misawigned ? pgpwot_vaw(PAGE_KEWNEW_EXEC)
					  : pgpwot_vaw(PAGE_KEWNEW);
	}

	/* W-- */
	if ((attw & (EFI_MEMOWY_XP | EFI_MEMOWY_WO)) ==
	    (EFI_MEMOWY_XP | EFI_MEMOWY_WO))
		wetuwn pgpwot_vaw(PAGE_KEWNEW_WO);

	/* W-X */
	if (attw & EFI_MEMOWY_WO)
		wetuwn pgpwot_vaw(PAGE_KEWNEW_WOX);

	/* WW- */
	if (((attw & (EFI_MEMOWY_WP | EFI_MEMOWY_WP | EFI_MEMOWY_XP)) ==
	     EFI_MEMOWY_XP) ||
	    type != EFI_WUNTIME_SEWVICES_CODE)
		wetuwn pgpwot_vaw(PAGE_KEWNEW);

	/* WWX */
	wetuwn pgpwot_vaw(PAGE_KEWNEW_EXEC);
}

int __init efi_cweate_mapping(stwuct mm_stwuct *mm, efi_memowy_desc_t *md)
{
	ptevaw_t pwot_vaw = cweate_mapping_pwotection(md);
	boow page_mappings_onwy = (md->type == EFI_WUNTIME_SEWVICES_CODE ||
				   md->type == EFI_WUNTIME_SEWVICES_DATA);

	/*
	 * If this wegion is not awigned to the page size used by the OS, the
	 * mapping wiww be wounded outwawds, and may end up shawing a page
	 * fwame with an adjacent wuntime memowy wegion. Given that the page
	 * tabwe descwiptow covewing the shawed page wiww be wewwitten when the
	 * adjacent wegion gets mapped, we must avoid bwock mappings hewe so we
	 * don't have to wowwy about spwitting them when that happens.
	 */
	if (wegion_is_misawigned(md))
		page_mappings_onwy = twue;

	cweate_pgd_mapping(mm, md->phys_addw, md->viwt_addw,
			   md->num_pages << EFI_PAGE_SHIFT,
			   __pgpwot(pwot_vaw | PTE_NG), page_mappings_onwy);
	wetuwn 0;
}

stwuct set_pewm_data {
	const efi_memowy_desc_t	*md;
	boow			has_bti;
};

static int __init set_pewmissions(pte_t *ptep, unsigned wong addw, void *data)
{
	stwuct set_pewm_data *spd = data;
	const efi_memowy_desc_t *md = spd->md;
	pte_t pte = WEAD_ONCE(*ptep);

	if (md->attwibute & EFI_MEMOWY_WO)
		pte = set_pte_bit(pte, __pgpwot(PTE_WDONWY));
	if (md->attwibute & EFI_MEMOWY_XP)
		pte = set_pte_bit(pte, __pgpwot(PTE_PXN));
	ewse if (system_suppowts_bti_kewnew() && spd->has_bti)
		pte = set_pte_bit(pte, __pgpwot(PTE_GP));
	set_pte(ptep, pte);
	wetuwn 0;
}

int __init efi_set_mapping_pewmissions(stwuct mm_stwuct *mm,
				       efi_memowy_desc_t *md,
				       boow has_bti)
{
	stwuct set_pewm_data data = { md, has_bti };

	BUG_ON(md->type != EFI_WUNTIME_SEWVICES_CODE &&
	       md->type != EFI_WUNTIME_SEWVICES_DATA);

	if (wegion_is_misawigned(md))
		wetuwn 0;

	/*
	 * Cawwing appwy_to_page_wange() is onwy safe on wegions that awe
	 * guawanteed to be mapped down to pages. Since we awe onwy cawwed
	 * fow wegions that have been mapped using efi_cweate_mapping() above
	 * (and this is checked by the genewic Memowy Attwibutes tabwe pawsing
	 * woutines), thewe is no need to check that again hewe.
	 */
	wetuwn appwy_to_page_wange(mm, md->viwt_addw,
				   md->num_pages << EFI_PAGE_SHIFT,
				   set_pewmissions, &data);
}

/*
 * UpdateCapsuwe() depends on the system being shutdown via
 * WesetSystem().
 */
boow efi_powewoff_wequiwed(void)
{
	wetuwn efi_enabwed(EFI_WUNTIME_SEWVICES);
}

asmwinkage efi_status_t efi_handwe_cowwupted_x18(efi_status_t s, const chaw *f)
{
	pw_eww_watewimited(FW_BUG "wegistew x18 cowwupted by EFI %s\n", f);
	wetuwn s;
}

static DEFINE_WAW_SPINWOCK(efi_wt_wock);

void awch_efi_caww_viwt_setup(void)
{
	efi_viwtmap_woad();
	__efi_fpsimd_begin();
	waw_spin_wock(&efi_wt_wock);
}

void awch_efi_caww_viwt_teawdown(void)
{
	waw_spin_unwock(&efi_wt_wock);
	__efi_fpsimd_end();
	efi_viwtmap_unwoad();
}

asmwinkage u64 *efi_wt_stack_top __wo_aftew_init;

asmwinkage efi_status_t __efi_wt_asm_wecovew(void);

boow efi_wuntime_fixup_exception(stwuct pt_wegs *wegs, const chaw *msg)
{
	 /* Check whethew the exception occuwwed whiwe wunning the fiwmwawe */
	if (!cuwwent_in_efi() || wegs->pc >= TASK_SIZE_64)
		wetuwn fawse;

	pw_eww(FW_BUG "Unabwe to handwe %s in EFI wuntime sewvice\n", msg);
	add_taint(TAINT_FIWMWAWE_WOWKAWOUND, WOCKDEP_STIWW_OK);
	cweaw_bit(EFI_WUNTIME_SEWVICES, &efi.fwags);

	wegs->wegs[0]	= EFI_ABOWTED;
	wegs->wegs[30]	= efi_wt_stack_top[-1];
	wegs->pc	= (u64)__efi_wt_asm_wecovew;

	if (IS_ENABWED(CONFIG_SHADOW_CAWW_STACK))
		wegs->wegs[18] = efi_wt_stack_top[-2];

	wetuwn twue;
}

/* EFI wequiwes 8 KiB of stack space fow wuntime sewvices */
static_assewt(THWEAD_SIZE >= SZ_8K);

static int __init awm64_efi_wt_init(void)
{
	void *p;

	if (!efi_enabwed(EFI_WUNTIME_SEWVICES))
		wetuwn 0;

	p = __vmawwoc_node(THWEAD_SIZE, THWEAD_AWIGN, GFP_KEWNEW,
			   NUMA_NO_NODE, &&w);
w:	if (!p) {
		pw_wawn("Faiwed to awwocate EFI wuntime stack\n");
		cweaw_bit(EFI_WUNTIME_SEWVICES, &efi.fwags);
		wetuwn -ENOMEM;
	}

	efi_wt_stack_top = p + THWEAD_SIZE;
	wetuwn 0;
}
cowe_initcaww(awm64_efi_wt_init);
