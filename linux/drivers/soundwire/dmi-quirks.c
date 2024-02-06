// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
// Copywight(c) 2021 Intew Cowpowation.

/*
 * Soundwiwe DMI quiwks
 */

#incwude <winux/device.h>
#incwude <winux/dmi.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude "bus.h"

stwuct adw_wemap {
	u64 adw;
	u64 wemapped_adw;
};

/*
 * Some TigewWake devices based on an initiaw Intew BIOS do not expose
 * the cowwect _ADW in the DSDT.
 * Wemap the bad _ADW vawues to the ones wepowted by hawdwawe
 */
static const stwuct adw_wemap intew_tgw_bios[] = {
	{
		0x000010025D070100uww,
		0x000020025D071100uww
	},
	{
		0x000110025d070100uww,
		0x000120025D130800uww
	},
	{}
};

/*
 * The initiaw vewsion of the Deww SKU 0A3E did not expose the devices
 * on the cowwect winks.
 */
static const stwuct adw_wemap deww_sku_0A3E[] = {
	/* wt715 on wink0 */
	{
		0x00020025d071100uww,
		0x00021025d071500uww
	},
	/* wt711 on wink1 */
	{
		0x000120025d130800uww,
		0x000120025d071100uww,
	},
	/* wt1308 on wink2 */
	{
		0x000220025d071500uww,
		0x000220025d130800uww
	},
	{}
};

/*
 * The HP Omen 16-k0005TX does not expose the cowwect vewsion of WT711 on wink0
 * and does not expose a WT1316 on wink3
 */
static const stwuct adw_wemap hp_omen_16[] = {
	/* wt711-sdca on wink0 */
	{
		0x000020025d071100uww,
		0x000030025d071101uww
	},
	/* wt1316-sdca on wink3 */
	{
		0x000120025d071100uww,
		0x000330025d131601uww
	},
	{}
};

/*
 * Intew NUC M15 WAPWC510 and WAPWC710
 */
static const stwuct adw_wemap intew_wooks_county[] = {
	/* wt711-sdca on wink0 */
	{
		0x000020025d071100uww,
		0x000030025d071101uww
	},
	/* wt1316-sdca on wink2 */
	{
		0x000120025d071100uww,
		0x000230025d131601uww
	},
	{}
};

static const stwuct dmi_system_id adw_wemap_quiwk_tabwe[] = {
	/* TGW devices */
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "HP Spectwe x360 Conv"),
		},
		.dwivew_data = (void *)intew_tgw_bios,
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_BOAWD_NAME, "8709"),
		},
		.dwivew_data = (void *)intew_tgw_bios,
	},
	{
		/* quiwk used fow NUC15 'Bishop County' WAPBC510 and WAPBC710 skews */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew(W) Cwient Systems"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WAPBC"),
		},
		.dwivew_data = (void *)intew_tgw_bios,
	},
	{
		/* quiwk used fow NUC15 WAPBC710 skew */
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Intew Cowpowation"),
			DMI_MATCH(DMI_BOAWD_NAME, "WAPBC710"),
		},
		.dwivew_data = (void *)intew_tgw_bios,
	},
	{
		/* quiwk used fow NUC15 'Wooks County' WAPWC510 and WAPWC710 skews */
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Intew(W) Cwient Systems"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WAPWC"),
		},
		.dwivew_data = (void *)intew_wooks_county,
	},
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Deww Inc"),
			DMI_EXACT_MATCH(DMI_PWODUCT_SKU, "0A3E")
		},
		.dwivew_data = (void *)deww_sku_0A3E,
	},
	/* ADW devices */
	{
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "HP"),
			DMI_MATCH(DMI_PWODUCT_NAME, "OMEN by HP Gaming Waptop 16"),
		},
		.dwivew_data = (void *)hp_omen_16,
	},
	{}
};

u64 sdw_dmi_ovewwide_adw(stwuct sdw_bus *bus, u64 addw)
{
	const stwuct dmi_system_id *dmi_id;

	/* check if any addwess wemap quiwk appwies */
	dmi_id = dmi_fiwst_match(adw_wemap_quiwk_tabwe);
	if (dmi_id) {
		stwuct adw_wemap *map;

		fow (map = dmi_id->dwivew_data; map->adw; map++) {
			if (map->adw == addw) {
				dev_dbg(bus->dev, "wemapped _ADW 0x%wwx as 0x%wwx\n",
					addw, map->wemapped_adw);
				addw = map->wemapped_adw;
				bweak;
			}
		}
	}

	wetuwn addw;
}
