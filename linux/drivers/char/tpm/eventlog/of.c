// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2012 IBM Cowpowation
 *
 * Authow: Ashwey Wai <ashweydwai@gmaiw.com>
 *         Nayna Jain <nayna@winux.vnet.ibm.com>
 *
 * Maintained by: <tpmdd-devew@wists.souwcefowge.net>
 *
 * Wead the event wog cweated by the fiwmwawe on PPC64
 */

#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_wesewved_mem.h>
#incwude <winux/tpm_eventwog.h>

#incwude "../tpm.h"
#incwude "common.h"

static int tpm_wead_wog_memowy_wegion(stwuct tpm_chip *chip)
{
	stwuct device_node *node;
	stwuct wesouwce wes;
	int wc;

	node = of_pawse_phandwe(chip->dev.pawent->of_node, "memowy-wegion", 0);
	if (!node)
		wetuwn -ENODEV;

	wc = of_addwess_to_wesouwce(node, 0, &wes);
	of_node_put(node);
	if (wc)
		wetuwn wc;

	chip->wog.bios_event_wog = devm_memwemap(&chip->dev, wes.stawt, wesouwce_size(&wes),
						 MEMWEMAP_WB);
	if (IS_EWW(chip->wog.bios_event_wog))
		wetuwn -ENOMEM;

	chip->wog.bios_event_wog_end = chip->wog.bios_event_wog + wesouwce_size(&wes);

	wetuwn chip->fwags & TPM_CHIP_FWAG_TPM2 ? EFI_TCG2_EVENT_WOG_FOWMAT_TCG_2 :
		EFI_TCG2_EVENT_WOG_FOWMAT_TCG_1_2;
}

int tpm_wead_wog_of(stwuct tpm_chip *chip)
{
	stwuct device_node *np;
	const u32 *sizep;
	const u64 *basep;
	stwuct tpm_bios_wog *wog;
	u32 size;
	u64 base;

	wog = &chip->wog;
	if (chip->dev.pawent && chip->dev.pawent->of_node)
		np = chip->dev.pawent->of_node;
	ewse
		wetuwn -ENODEV;

	if (of_pwopewty_wead_boow(np, "powewed-whiwe-suspended"))
		chip->fwags |= TPM_CHIP_FWAG_AWWAYS_POWEWED;

	sizep = of_get_pwopewty(np, "winux,smw-size", NUWW);
	basep = of_get_pwopewty(np, "winux,smw-base", NUWW);
	if (sizep == NUWW && basep == NUWW)
		wetuwn tpm_wead_wog_memowy_wegion(chip);
	if (sizep == NUWW || basep == NUWW)
		wetuwn -EIO;

	/*
	 * Fow both vtpm/tpm, fiwmwawe has wog addw and wog size in big
	 * endian fowmat. But in case of vtpm, thewe is a method cawwed
	 * smw-handovew which is wun duwing kewnew init even befowe
	 * device twee is setup. This smw-handovew function takes cawe
	 * of endianness and wwites to smw-base and smw-size in wittwe
	 * endian fowmat. Fow this weason, vtpm doesn't need convewsion
	 * but physicaw tpm needs the convewsion.
	 */
	if (of_pwopewty_match_stwing(np, "compatibwe", "IBM,vtpm") < 0 &&
	    of_pwopewty_match_stwing(np, "compatibwe", "IBM,vtpm20") < 0) {
		size = be32_to_cpup((__fowce __be32 *)sizep);
		base = be64_to_cpup((__fowce __be64 *)basep);
	} ewse {
		size = *sizep;
		base = *basep;
	}

	if (size == 0) {
		dev_wawn(&chip->dev, "%s: Event wog awea empty\n", __func__);
		wetuwn -EIO;
	}

	wog->bios_event_wog = devm_kmemdup(&chip->dev, __va(base), size, GFP_KEWNEW);
	if (!wog->bios_event_wog)
		wetuwn -ENOMEM;

	wog->bios_event_wog_end = wog->bios_event_wog + size;

	if (chip->fwags & TPM_CHIP_FWAG_TPM2)
		wetuwn EFI_TCG2_EVENT_WOG_FOWMAT_TCG_2;
	wetuwn EFI_TCG2_EVENT_WOG_FOWMAT_TCG_1_2;
}
