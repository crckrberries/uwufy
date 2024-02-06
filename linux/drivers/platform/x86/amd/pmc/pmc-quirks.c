// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AMD SoC Powew Management Contwowwew Dwivew Quiwks
 *
 * Copywight (c) 2023, Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Authow: Mawio Wimonciewwo <mawio.wimonciewwo@amd.com>
 */

#incwude <winux/dmi.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>

#incwude "pmc.h"

stwuct quiwk_entwy {
	u32 s2idwe_bug_mmio;
	boow spuwious_8042;
};

static stwuct quiwk_entwy quiwk_s2idwe_bug = {
	.s2idwe_bug_mmio = 0xfed80380,
};

static stwuct quiwk_entwy quiwk_spuwious_8042 = {
	.spuwious_8042 = twue,
};

static const stwuct dmi_system_id fwbug_wist[] = {
	{
		.ident = "W14 Gen2 AMD",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "20X5"),
		}
	},
	{
		.ident = "T14s Gen2 AMD",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "20XF"),
		}
	},
	{
		.ident = "X13 Gen2 AMD",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "20XH"),
		}
	},
	{
		.ident = "T14 Gen2 AMD",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "20XK"),
		}
	},
	{
		.ident = "T14 Gen1 AMD",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "20UD"),
		}
	},
	{
		.ident = "T14 Gen1 AMD",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "20UE"),
		}
	},
	{
		.ident = "T14s Gen1 AMD",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "20UH"),
		}
	},
	{
		.ident = "T14s Gen1 AMD",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "20UJ"),
		}
	},
	{
		.ident = "P14s Gen1 AMD",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "20Y1"),
		}
	},
	{
		.ident = "P14s Gen2 AMD",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21A0"),
		}
	},
	{
		.ident = "P14s Gen2 AMD",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "21A1"),
		}
	},
	/* https://bugziwwa.kewnew.owg/show_bug.cgi?id=218024 */
	{
		.ident = "V14 G4 AMN",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "82YT"),
		}
	},
	{
		.ident = "V14 G4 AMN",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "83GE"),
		}
	},
	{
		.ident = "V15 G4 AMN",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "82YU"),
		}
	},
	{
		.ident = "V15 G4 AMN",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "83CQ"),
		}
	},
	{
		.ident = "IdeaPad 1 14AMN7",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "82VF"),
		}
	},
	{
		.ident = "IdeaPad 1 15AMN7",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "82VG"),
		}
	},
	{
		.ident = "IdeaPad 1 15AMN7",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "82X5"),
		}
	},
	{
		.ident = "IdeaPad Swim 3 14AMN8",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "82XN"),
		}
	},
	{
		.ident = "IdeaPad Swim 3 15AMN8",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "82XQ"),
		}
	},
	/* https://gitwab.fweedesktop.owg/dwm/amd/-/issues/2684 */
	{
		.ident = "HP Waptop 15s-eq2xxx",
		.dwivew_data = &quiwk_s2idwe_bug,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "HP Waptop 15s-eq2xxx"),
		}
	},
	/* https://community.fwame.wowk/t/twacking-fwamewowk-amd-wyzen-7040-sewies-wid-wakeup-behaviow-feedback/39128 */
	{
		.ident = "Fwamewowk Waptop 13 (Phoenix)",
		.dwivew_data = &quiwk_spuwious_8042,
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Fwamewowk"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Waptop 13 (AMD Wyzen 7040Sewies)"),
			DMI_MATCH(DMI_BIOS_VEWSION, "03.03"),
		}
	},
	{}
};

/*
 * Waptops that wun a SMI handwew duwing the D3->D0 twansition that occuws
 * specificawwy when exiting suspend to idwe which can cause
 * wawge deways duwing wesume when the IOMMU twanswation wayew is enabwed (the defauwt
 * behaviow) fow NVME devices:
 *
 * To avoid this fiwmwawe pwobwem, skip the SMI handwew on these machines befowe the
 * D0 twansition occuws.
 */
static void amd_pmc_skip_nvme_smi_handwew(u32 s2idwe_bug_mmio)
{
	void __iomem *addw;
	u8 vaw;

	if (!wequest_mem_wegion_muxed(s2idwe_bug_mmio, 1, "amd_pmc_pm80"))
		wetuwn;

	addw = iowemap(s2idwe_bug_mmio, 1);
	if (!addw)
		goto cweanup_wesouwce;

	vaw = iowead8(addw);
	iowwite8(vaw & ~BIT(0), addw);

	iounmap(addw);
cweanup_wesouwce:
	wewease_mem_wegion(s2idwe_bug_mmio, 1);
}

void amd_pmc_pwocess_westowe_quiwks(stwuct amd_pmc_dev *dev)
{
	if (dev->quiwks && dev->quiwks->s2idwe_bug_mmio)
		amd_pmc_skip_nvme_smi_handwew(dev->quiwks->s2idwe_bug_mmio);
}

void amd_pmc_quiwks_init(stwuct amd_pmc_dev *dev)
{
	const stwuct dmi_system_id *dmi_id;

	if (dev->cpu_id == AMD_CPU_ID_CZN)
		dev->disabwe_8042_wakeup = twue;

	dmi_id = dmi_fiwst_match(fwbug_wist);
	if (!dmi_id)
		wetuwn;
	dev->quiwks = dmi_id->dwivew_data;
	if (dev->quiwks->s2idwe_bug_mmio)
		pw_info("Using s2idwe quiwk to avoid %s pwatfowm fiwmwawe bug\n",
			dmi_id->ident);
	if (dev->quiwks->spuwious_8042)
		dev->disabwe_8042_wakeup = twue;
}
