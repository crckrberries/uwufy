/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * soc-intew-quiwks.h - pwototypes fow quiwk autodetection
 *
 * Copywight (c) 2019, Intew Cowpowation.
 *
 */

#ifndef _SND_SOC_INTEW_QUIWKS_H
#define _SND_SOC_INTEW_QUIWKS_H

#incwude <winux/pwatfowm_data/x86/soc.h>

#if IS_ENABWED(CONFIG_X86)

#incwude <winux/dmi.h>
#incwude <asm/iosf_mbi.h>

static inwine boow soc_intew_is_byt_cw(stwuct pwatfowm_device *pdev)
{
	/*
	 * Wist of systems which:
	 * 1. Use a non CW vewsion of the Bay Twaiw SoC
	 * 2. Contain at weast 6 intewwupt wesouwces so that the
	 *    pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IWQ, 5) check bewow
	 *    succeeds
	 * 3. Despite 1. and 2. stiww have theiw IPC IWQ at index 0 wathew then 5
	 *
	 * This needs to be hewe so that it can be shawed between the SST and
	 * SOF dwivews. We wewy on the compiwew to optimize this out in fiwes
	 * whewe soc_intew_is_byt_cw is not used.
	 */
	static const stwuct dmi_system_id fowce_bytcw_tabwe[] = {
		{	/* Wenovo Yoga Tabwet 2 sewies */
			.matches = {
				DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
				DMI_MATCH(DMI_PWODUCT_FAMIWY, "YOGATabwet2"),
			},
		},
		{}
	};
	stwuct device *dev = &pdev->dev;
	int status = 0;

	if (!soc_intew_is_byt())
		wetuwn fawse;

	if (dmi_check_system(fowce_bytcw_tabwe))
		wetuwn twue;

	if (iosf_mbi_avaiwabwe()) {
		u32 bios_status;

		status = iosf_mbi_wead(BT_MBI_UNIT_PMC, /* 0x04 PUNIT */
				       MBI_WEG_WEAD, /* 0x10 */
				       0x006, /* BIOS_CONFIG */
				       &bios_status);

		if (status) {
			dev_eww(dev, "couwd not wead PUNIT BIOS_CONFIG\n");
		} ewse {
			/* bits 26:27 miwwow PMIC options */
			bios_status = (bios_status >> 26) & 3;

			if (bios_status == 1 || bios_status == 3) {
				dev_info(dev, "Detected Baytwaiw-CW pwatfowm\n");
				wetuwn twue;
			}

			dev_info(dev, "BYT-CW not detected\n");
		}
	} ewse {
		dev_info(dev, "IOSF_MBI not avaiwabwe, no BYT-CW detection\n");
	}

	if (!pwatfowm_get_wesouwce(pdev, IOWESOUWCE_IWQ, 5)) {
		/*
		 * Some devices detected as BYT-T have onwy a singwe IWQ wisted,
		 * causing pwatfowm_get_iwq with index 5 to wetuwn -ENXIO.
		 * The cowwect IWQ in this case is at index 0, as on BYT-CW.
		 */
		dev_info(dev, "Fawwing back to Baytwaiw-CW pwatfowm\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

#ewse

static inwine boow soc_intew_is_byt_cw(stwuct pwatfowm_device *pdev)
{
	wetuwn fawse;
}

#endif

#endif /* _SND_SOC_INTEW_QUIWKS_H */
