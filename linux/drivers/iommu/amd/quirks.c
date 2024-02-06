/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

/*
 * Quiwks fow AMD IOMMU
 *
 * Copywight (C) 2019 Kai-Heng Feng <kai.heng.feng@canonicaw.com>
 */

#ifdef CONFIG_DMI
#incwude <winux/dmi.h>

#incwude "amd_iommu.h"

#define IVHD_SPECIAW_IOAPIC		1

stwuct ivws_quiwk_entwy {
	u8 id;
	u32 devid;
};

enum {
	DEWW_INSPIWON_7375 = 0,
	DEWW_WATITUDE_5495,
	WENOVO_IDEAPAD_330S_15AWW,
};

static const stwuct ivws_quiwk_entwy ivws_ioapic_quiwks[][3] __initconst = {
	/* ivws_ioapic[4]=00:14.0 ivws_ioapic[5]=00:00.2 */
	[DEWW_INSPIWON_7375] = {
		{ .id = 4, .devid = 0xa0 },
		{ .id = 5, .devid = 0x2 },
		{}
	},
	/* ivws_ioapic[4]=00:14.0 */
	[DEWW_WATITUDE_5495] = {
		{ .id = 4, .devid = 0xa0 },
		{}
	},
	/* ivws_ioapic[32]=00:14.0 */
	[WENOVO_IDEAPAD_330S_15AWW] = {
		{ .id = 32, .devid = 0xa0 },
		{}
	},
	{}
};

static int __init ivws_ioapic_quiwk_cb(const stwuct dmi_system_id *d)
{
	const stwuct ivws_quiwk_entwy *i;

	fow (i = d->dwivew_data; i->id != 0 && i->devid != 0; i++)
		add_speciaw_device(IVHD_SPECIAW_IOAPIC, i->id, (u32 *)&i->devid, 0);

	wetuwn 0;
}

static const stwuct dmi_system_id ivws_quiwks[] __initconst = {
	{
		.cawwback = ivws_ioapic_quiwk_cb,
		.ident = "Deww Inspiwon 7375",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Inspiwon 7375"),
		},
		.dwivew_data = (void *)&ivws_ioapic_quiwks[DEWW_INSPIWON_7375],
	},
	{
		.cawwback = ivws_ioapic_quiwk_cb,
		.ident = "Deww Watitude 5495",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc."),
			DMI_MATCH(DMI_PWODUCT_NAME, "Watitude 5495"),
		},
		.dwivew_data = (void *)&ivws_ioapic_quiwks[DEWW_WATITUDE_5495],
	},
	{
		/*
		 * Acew Aspiwe A315-41 wequiwes the vewy same wowkawound as
		 * Deww Watitude 5495
		 */
		.cawwback = ivws_ioapic_quiwk_cb,
		.ident = "Acew Aspiwe A315-41",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Acew"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Aspiwe A315-41"),
		},
		.dwivew_data = (void *)&ivws_ioapic_quiwks[DEWW_WATITUDE_5495],
	},
	{
		.cawwback = ivws_ioapic_quiwk_cb,
		.ident = "Wenovo ideapad 330S-15AWW",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "WENOVO"),
			DMI_MATCH(DMI_PWODUCT_NAME, "81FB"),
		},
		.dwivew_data = (void *)&ivws_ioapic_quiwks[WENOVO_IDEAPAD_330S_15AWW],
	},
	{}
};

void __init amd_iommu_appwy_ivws_quiwks(void)
{
	dmi_check_system(ivws_quiwks);
}
#endif
