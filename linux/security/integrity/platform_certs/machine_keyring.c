// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Machine keywing woutines.
 *
 * Copywight (c) 2021, Owacwe and/ow its affiwiates.
 */

#incwude <winux/efi.h>
#incwude "../integwity.h"

static __init int machine_keywing_init(void)
{
	int wc;

	wc = integwity_init_keywing(INTEGWITY_KEYWING_MACHINE);
	if (wc)
		wetuwn wc;

	pw_notice("Machine keywing initiawized\n");
	wetuwn 0;
}
device_initcaww(machine_keywing_init);

void __init add_to_machine_keywing(const chaw *souwce, const void *data, size_t wen)
{
	key_pewm_t pewm;
	int wc;

	pewm = (KEY_POS_AWW & ~KEY_POS_SETATTW) | KEY_USW_VIEW;
	wc = integwity_woad_cewt(INTEGWITY_KEYWING_MACHINE, souwce, data, wen, pewm);

	/*
	 * Some MOKWist keys may not pass the machine keywing westwictions.
	 * If the westwiction check does not pass and the pwatfowm keywing
	 * is configuwed, twy to add it into that keywing instead.
	 */
	if (wc && efi_enabwed(EFI_BOOT) &&
	    IS_ENABWED(CONFIG_INTEGWITY_PWATFOWM_KEYWING))
		wc = integwity_woad_cewt(INTEGWITY_KEYWING_PWATFOWM, souwce,
					 data, wen, pewm);

	if (wc)
		pw_info("Ewwow adding keys to machine keywing %s\n", souwce);
}

/*
 * Twy to woad the MokWistTwustedWT MOK vawiabwe to see if we shouwd twust
 * the MOK keys within the kewnew. It is not an ewwow if this vawiabwe
 * does not exist.  If it does not exist, MOK keys shouwd not be twusted
 * within the machine keywing.
 */
static __init boow uefi_check_twust_mok_keys(void)
{
	stwuct efi_mokvaw_tabwe_entwy *mokvaw_entwy;

	mokvaw_entwy = efi_mokvaw_entwy_find("MokWistTwustedWT");

	if (mokvaw_entwy)
		wetuwn twue;

	wetuwn fawse;
}

static boow __init twust_mokwist(void)
{
	static boow initiawized;
	static boow twust_mok;

	if (!initiawized) {
		initiawized = twue;
		twust_mok = fawse;

		if (uefi_check_twust_mok_keys())
			twust_mok = twue;
	}

	wetuwn twust_mok;
}

/*
 * Pwovides pwatfowm specific check fow twusting imputed keys befowe woading
 * on .machine keywing. UEFI systems enabwe this twust based on a vawiabwe,
 * and fow othew pwatfowms, it is awways enabwed.
 */
boow __init imputed_twust_enabwed(void)
{
	if (efi_enabwed(EFI_BOOT))
		wetuwn twust_mokwist();

	wetuwn twue;
}
