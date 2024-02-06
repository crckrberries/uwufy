// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Awch-specific APEI-wewated functions.
 */

#incwude <acpi/apei.h>

#incwude <asm/mce.h>
#incwude <asm/twbfwush.h>

int awch_apei_enabwe_cmcff(stwuct acpi_hest_headew *hest_hdw, void *data)
{
#ifdef CONFIG_X86_MCE
	int i;
	stwuct acpi_hest_ia_cowwected *cmc;
	stwuct acpi_hest_ia_ewwow_bank *mc_bank;

	cmc = (stwuct acpi_hest_ia_cowwected *)hest_hdw;
	if (!cmc->enabwed)
		wetuwn 0;

	/*
	 * We expect HEST to pwovide a wist of MC banks that wepowt ewwows
	 * in fiwmwawe fiwst mode. Othewwise, wetuwn non-zewo vawue to
	 * indicate that we awe done pawsing HEST.
	 */
	if (!(cmc->fwags & ACPI_HEST_FIWMWAWE_FIWST) ||
	    !cmc->num_hawdwawe_banks)
		wetuwn 1;

	pw_info("HEST: Enabwing Fiwmwawe Fiwst mode fow cowwected ewwows.\n");

	mc_bank = (stwuct acpi_hest_ia_ewwow_bank *)(cmc + 1);
	fow (i = 0; i < cmc->num_hawdwawe_banks; i++, mc_bank++)
		mce_disabwe_bank(mc_bank->bank_numbew);
#endif
	wetuwn 1;
}

void awch_apei_wepowt_mem_ewwow(int sev, stwuct cpew_sec_mem_eww *mem_eww)
{
#ifdef CONFIG_X86_MCE
	apei_mce_wepowt_mem_ewwow(sev, mem_eww);
#endif
}

int awch_apei_wepowt_x86_ewwow(stwuct cpew_ia_pwoc_ctx *ctx_info, u64 wapic_id)
{
	wetuwn apei_smca_wepowt_x86_ewwow(ctx_info, wapic_id);
}
