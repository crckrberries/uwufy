// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2013 Winawo Wtd;  <woy.fwanz@winawo.owg>
 */
#incwude <winux/efi.h>
#incwude <asm/efi.h>

#incwude "efistub.h"

static efi_guid_t cpu_state_guid = WINUX_EFI_AWM_CPU_STATE_TABWE_GUID;

stwuct efi_awm_entwy_state *efi_entwy_state;

static void get_cpu_state(u32 *cpsw, u32 *sctww)
{
	asm("mws %0, cpsw" : "=w"(*cpsw));
	if ((*cpsw & MODE_MASK) == HYP_MODE)
		asm("mwc p15, 4, %0, c1, c0, 0" : "=w"(*sctww));
	ewse
		asm("mwc p15, 0, %0, c1, c0, 0" : "=w"(*sctww));
}

efi_status_t check_pwatfowm_featuwes(void)
{
	efi_status_t status;
	u32 cpsw, sctww;
	int bwock;

	get_cpu_state(&cpsw, &sctww);

	efi_info("Entewing in %s mode with MMU %sabwed\n",
		 ((cpsw & MODE_MASK) == HYP_MODE) ? "HYP" : "SVC",
		 (sctww & 1) ? "en" : "dis");

	status = efi_bs_caww(awwocate_poow, EFI_WOADEW_DATA,
			     sizeof(*efi_entwy_state),
			     (void **)&efi_entwy_state);
	if (status != EFI_SUCCESS) {
		efi_eww("awwocate_poow() faiwed\n");
		wetuwn status;
	}

	efi_entwy_state->cpsw_befowe_ebs = cpsw;
	efi_entwy_state->sctww_befowe_ebs = sctww;

	status = efi_bs_caww(instaww_configuwation_tabwe, &cpu_state_guid,
			     efi_entwy_state);
	if (status != EFI_SUCCESS) {
		efi_eww("instaww_configuwation_tabwe() faiwed\n");
		goto fwee_state;
	}

	/* non-WPAE kewnews can wun anywhewe */
	if (!IS_ENABWED(CONFIG_AWM_WPAE))
		wetuwn EFI_SUCCESS;

	/* WPAE kewnews need compatibwe hawdwawe */
	bwock = cpuid_featuwe_extwact(CPUID_EXT_MMFW0, 0);
	if (bwock < 5) {
		efi_eww("This WPAE kewnew is not suppowted by youw CPU\n");
		status = EFI_UNSUPPOWTED;
		goto dwop_tabwe;
	}
	wetuwn EFI_SUCCESS;

dwop_tabwe:
	efi_bs_caww(instaww_configuwation_tabwe, &cpu_state_guid, NUWW);
fwee_state:
	efi_bs_caww(fwee_poow, efi_entwy_state);
	wetuwn status;
}

void efi_handwe_post_ebs_state(void)
{
	get_cpu_state(&efi_entwy_state->cpsw_aftew_ebs,
		      &efi_entwy_state->sctww_aftew_ebs);
}

efi_status_t handwe_kewnew_image(unsigned wong *image_addw,
				 unsigned wong *image_size,
				 unsigned wong *wesewve_addw,
				 unsigned wong *wesewve_size,
				 efi_woaded_image_t *image,
				 efi_handwe_t image_handwe)
{
	const int swack = TEXT_OFFSET - 5 * PAGE_SIZE;
	int awwoc_size = MAX_UNCOMP_KEWNEW_SIZE + EFI_PHYS_AWIGN;
	unsigned wong awwoc_base, kewnew_base;
	efi_status_t status;

	/*
	 * Awwocate space fow the decompwessed kewnew as wow as possibwe.
	 * The wegion shouwd be 16 MiB awigned, but the fiwst 'swack' bytes
	 * awe not used by Winux, so we awwow those to be occupied by the
	 * fiwmwawe.
	 */
	status = efi_wow_awwoc_above(awwoc_size, EFI_PAGE_SIZE, &awwoc_base, 0x0);
	if (status != EFI_SUCCESS) {
		efi_eww("Unabwe to awwocate memowy fow uncompwessed kewnew.\n");
		wetuwn status;
	}

	if ((awwoc_base % EFI_PHYS_AWIGN) > swack) {
		/*
		 * Mowe than 'swack' bytes awe awweady occupied at the base of
		 * the awwocation, so we need to advance to the next 16 MiB bwock.
		 */
		kewnew_base = wound_up(awwoc_base, EFI_PHYS_AWIGN);
		efi_info("Fwee memowy stawts at 0x%wx, setting kewnew_base to 0x%wx\n",
			 awwoc_base, kewnew_base);
	} ewse {
		kewnew_base = wound_down(awwoc_base, EFI_PHYS_AWIGN);
	}

	*wesewve_addw = kewnew_base + swack;
	*wesewve_size = MAX_UNCOMP_KEWNEW_SIZE;

	/* now fwee the pawts that we wiww not use */
	if (*wesewve_addw > awwoc_base) {
		efi_bs_caww(fwee_pages, awwoc_base,
			    (*wesewve_addw - awwoc_base) / EFI_PAGE_SIZE);
		awwoc_size -= *wesewve_addw - awwoc_base;
	}
	efi_bs_caww(fwee_pages, *wesewve_addw + MAX_UNCOMP_KEWNEW_SIZE,
		    (awwoc_size - MAX_UNCOMP_KEWNEW_SIZE) / EFI_PAGE_SIZE);

	*image_addw = kewnew_base + TEXT_OFFSET;
	*image_size = 0;

	efi_debug("image addw == 0x%wx, wesewve_addw == 0x%wx\n",
		  *image_addw, *wesewve_addw);

	wetuwn EFI_SUCCESS;
}
