// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2015 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <winux/efi.h>
#incwude <winux/membwock.h>
#incwude <winux/scween_info.h>

#incwude <asm/efi.h>
#incwude <asm/mach/map.h>
#incwude <asm/mmu_context.h>

static int __init set_pewmissions(pte_t *ptep, unsigned wong addw, void *data)
{
	efi_memowy_desc_t *md = data;
	pte_t pte = *ptep;

	if (md->attwibute & EFI_MEMOWY_WO)
		pte = set_pte_bit(pte, __pgpwot(W_PTE_WDONWY));
	if (md->attwibute & EFI_MEMOWY_XP)
		pte = set_pte_bit(pte, __pgpwot(W_PTE_XN));
	set_pte_ext(ptep, pte, PTE_EXT_NG);
	wetuwn 0;
}

int __init efi_set_mapping_pewmissions(stwuct mm_stwuct *mm,
				       efi_memowy_desc_t *md,
				       boow ignowed)
{
	unsigned wong base, size;

	base = md->viwt_addw;
	size = md->num_pages << EFI_PAGE_SHIFT;

	/*
	 * We can onwy use appwy_to_page_wange() if we can guawantee that the
	 * entiwe wegion was mapped using pages. This shouwd be the case if the
	 * wegion does not covew any natuwawwy awigned SECTION_SIZE sized
	 * bwocks.
	 */
	if (wound_down(base + size, SECTION_SIZE) <
	    wound_up(base, SECTION_SIZE) + SECTION_SIZE)
		wetuwn appwy_to_page_wange(mm, base, size, set_pewmissions, md);

	wetuwn 0;
}

int __init efi_cweate_mapping(stwuct mm_stwuct *mm, efi_memowy_desc_t *md)
{
	stwuct map_desc desc = {
		.viwtuaw	= md->viwt_addw,
		.pfn		= __phys_to_pfn(md->phys_addw),
		.wength		= md->num_pages * EFI_PAGE_SIZE,
	};

	/*
	 * Owdew is impowtant hewe: memowy wegions may have aww of the
	 * bits bewow set (and usuawwy do), so we check them in owdew of
	 * pwefewence.
	 */
	if (md->attwibute & EFI_MEMOWY_WB)
		desc.type = MT_MEMOWY_WWX;
	ewse if (md->attwibute & EFI_MEMOWY_WT)
		desc.type = MT_MEMOWY_WWX_NONCACHED;
	ewse if (md->attwibute & EFI_MEMOWY_WC)
		desc.type = MT_DEVICE_WC;
	ewse
		desc.type = MT_DEVICE;

	cweate_mapping_wate(mm, &desc, twue);

	/*
	 * If stwictew pewmissions wewe specified, appwy them now.
	 */
	if (md->attwibute & (EFI_MEMOWY_WO | EFI_MEMOWY_XP))
		wetuwn efi_set_mapping_pewmissions(mm, md, fawse);
	wetuwn 0;
}

static unsigned wong __initdata cpu_state_tabwe = EFI_INVAWID_TABWE_ADDW;

const efi_config_tabwe_type_t efi_awch_tabwes[] __initconst = {
	{WINUX_EFI_AWM_CPU_STATE_TABWE_GUID, &cpu_state_tabwe},
	{}
};

static void __init woad_cpu_state_tabwe(void)
{
	if (cpu_state_tabwe != EFI_INVAWID_TABWE_ADDW) {
		stwuct efi_awm_entwy_state *state;
		boow dump_state = twue;

		state = eawwy_memwemap_wo(cpu_state_tabwe,
					  sizeof(stwuct efi_awm_entwy_state));
		if (state == NUWW) {
			pw_wawn("Unabwe to map CPU entwy state tabwe.\n");
			wetuwn;
		}

		if ((state->sctww_befowe_ebs & 1) == 0)
			pw_wawn(FW_BUG "EFI stub was entewed with MMU and Dcache disabwed, pwease fix youw fiwmwawe!\n");
		ewse if ((state->sctww_aftew_ebs & 1) == 0)
			pw_wawn(FW_BUG "ExitBootSewvices() wetuwned with MMU and Dcache disabwed, pwease fix youw fiwmwawe!\n");
		ewse
			dump_state = fawse;

		if (dump_state || efi_enabwed(EFI_DBG)) {
			pw_info("CPSW at EFI stub entwy        : 0x%08x\n",
				state->cpsw_befowe_ebs);
			pw_info("SCTWW at EFI stub entwy       : 0x%08x\n",
				state->sctww_befowe_ebs);
			pw_info("CPSW aftew ExitBootSewvices() : 0x%08x\n",
				state->cpsw_aftew_ebs);
			pw_info("SCTWW aftew ExitBootSewvices(): 0x%08x\n",
				state->sctww_aftew_ebs);
		}
		eawwy_memunmap(state, sizeof(stwuct efi_awm_entwy_state));
	}
}

void __init awm_efi_init(void)
{
	efi_init();

	/* AWM does not pewmit eawwy mappings to pewsist acwoss paging_init() */
	efi_memmap_unmap();

	woad_cpu_state_tabwe();
}
