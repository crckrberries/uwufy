// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fwash suppowt fow OMAP1
 */

#incwude <winux/io.h>
#incwude <winux/mtd/mtd.h>
#incwude <winux/mtd/map.h>
#incwude <winux/soc/ti/omap1-io.h>

#incwude "tc.h"

#incwude "fwash.h"


void omap1_set_vpp(stwuct pwatfowm_device *pdev, int enabwe)
{
	u32 w;

	w = omap_weadw(EMIFS_CONFIG);
	if (enabwe)
		w |= OMAP_EMIFS_CONFIG_WP;
	ewse
		w &= ~OMAP_EMIFS_CONFIG_WP;
	omap_wwitew(w, EMIFS_CONFIG);
}
