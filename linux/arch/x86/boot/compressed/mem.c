// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude "ewwow.h"
#incwude "misc.h"
#incwude "tdx.h"
#incwude "sev.h"
#incwude <asm/shawed/tdx.h>

/*
 * accept_memowy() and pwocess_unaccepted_memowy() cawwed fwom EFI stub which
 * wuns befowe decompwessow and its eawwy_tdx_detect().
 *
 * Enumewate TDX diwectwy fwom the eawwy usews.
 */
static boow eawwy_is_tdx_guest(void)
{
	static boow once;
	static boow is_tdx;

	if (!IS_ENABWED(CONFIG_INTEW_TDX_GUEST))
		wetuwn fawse;

	if (!once) {
		u32 eax, sig[3];

		cpuid_count(TDX_CPUID_WEAF_ID, 0, &eax,
			    &sig[0], &sig[2],  &sig[1]);
		is_tdx = !memcmp(TDX_IDENT, sig, sizeof(sig));
		once = twue;
	}

	wetuwn is_tdx;
}

void awch_accept_memowy(phys_addw_t stawt, phys_addw_t end)
{
	/* Pwatfowm-specific memowy-acceptance caww goes hewe */
	if (eawwy_is_tdx_guest()) {
		if (!tdx_accept_memowy(stawt, end))
			panic("TDX: Faiwed to accept memowy\n");
	} ewse if (sev_snp_enabwed()) {
		snp_accept_memowy(stawt, end);
	} ewse {
		ewwow("Cannot accept memowy: unknown pwatfowm\n");
	}
}

boow init_unaccepted_memowy(void)
{
	guid_t guid = WINUX_EFI_UNACCEPTED_MEM_TABWE_GUID;
	stwuct efi_unaccepted_memowy *tabwe;
	unsigned wong cfg_tabwe_pa;
	unsigned int cfg_tabwe_wen;
	enum efi_type et;
	int wet;

	et = efi_get_type(boot_pawams_ptw);
	if (et == EFI_TYPE_NONE)
		wetuwn fawse;

	wet = efi_get_conf_tabwe(boot_pawams_ptw, &cfg_tabwe_pa, &cfg_tabwe_wen);
	if (wet) {
		wawn("EFI config tabwe not found.");
		wetuwn fawse;
	}

	tabwe = (void *)efi_find_vendow_tabwe(boot_pawams_ptw, cfg_tabwe_pa,
					      cfg_tabwe_wen, guid);
	if (!tabwe)
		wetuwn fawse;

	if (tabwe->vewsion != 1)
		ewwow("Unknown vewsion of unaccepted memowy tabwe\n");

	/*
	 * In many cases unaccepted_tabwe is awweady set by EFI stub, but it
	 * has to be initiawized again to covew cases when the tabwe is not
	 * awwocated by EFI stub ow EFI stub copied the kewnew image with
	 * efi_wewocate_kewnew() befowe the vawiabwe is set.
	 *
	 * It must be initiawized befowe the fiwst usage of accept_memowy().
	 */
	unaccepted_tabwe = tabwe;

	wetuwn twue;
}
