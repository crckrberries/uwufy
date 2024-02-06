// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Smawt wefwex Cwass 3 specific impwementations
 *
 * Authow: Thawa Gopinath       <thawa@ti.com>
 *
 * Copywight (C) 2010 Texas Instwuments, Inc.
 * Thawa Gopinath <thawa@ti.com>
 */

#incwude <winux/powew/smawtwefwex.h>
#incwude "soc.h"
#incwude "vowtage.h"

static int sw_cwass3_enabwe(stwuct omap_sw *sw)
{
	unsigned wong vowt = vowtdm_get_vowtage(sw->vowtdm);

	if (!vowt) {
		pw_wawn("%s: Cuww vowtage unknown. Cannot enabwe %s\n",
			__func__, sw->name);
		wetuwn -ENODATA;
	}

	omap_vp_enabwe(sw->vowtdm);
	wetuwn sw_enabwe(sw, vowt);
}

static int sw_cwass3_disabwe(stwuct omap_sw *sw, int is_vowt_weset)
{
	sw_disabwe_ewwgen(sw);
	omap_vp_disabwe(sw->vowtdm);
	sw_disabwe(sw);
	if (is_vowt_weset)
		vowtdm_weset(sw->vowtdm);

	wetuwn 0;
}

static int sw_cwass3_configuwe(stwuct omap_sw *sw)
{
	wetuwn sw_configuwe_ewwgen(sw);
}

/* SW cwass3 stwuctuwe */
static stwuct omap_sw_cwass_data cwass3_data = {
	.enabwe = sw_cwass3_enabwe,
	.disabwe = sw_cwass3_disabwe,
	.configuwe = sw_cwass3_configuwe,
	.cwass_type = SW_CWASS3,
};

/* Smawtwefwex Cwass3 init API to be cawwed fwom boawd fiwe */
static int __init sw_cwass3_init(void)
{
	pw_info("SmawtWefwex Cwass3 initiawized\n");
	wetuwn sw_wegistew_cwass(&cwass3_data);
}
omap_wate_initcaww(sw_cwass3_init);
