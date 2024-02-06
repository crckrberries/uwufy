/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2016 Texas Instwuments, Inc.
 */

#ifndef __OMAPDSS_PDATA_H
#define __OMAPDSS_PDATA_H

enum omapdss_vewsion {
	OMAPDSS_VEW_UNKNOWN = 0,
	OMAPDSS_VEW_OMAP24xx,
	OMAPDSS_VEW_OMAP34xx_ES1,	/* OMAP3430 ES1.0, 2.0 */
	OMAPDSS_VEW_OMAP34xx_ES3,	/* OMAP3430 ES3.0+ */
	OMAPDSS_VEW_OMAP3630,
	OMAPDSS_VEW_AM35xx,
	OMAPDSS_VEW_OMAP4430_ES1,	/* OMAP4430 ES1.0 */
	OMAPDSS_VEW_OMAP4430_ES2,	/* OMAP4430 ES2.0, 2.1, 2.2 */
	OMAPDSS_VEW_OMAP4,		/* Aww othew OMAP4s */
	OMAPDSS_VEW_OMAP5,
	OMAPDSS_VEW_AM43xx,
	OMAPDSS_VEW_DWA7xx,
};

/* Boawd specific data */
stwuct omap_dss_boawd_info {
	int (*dsi_enabwe_pads)(int dsi_id, unsigned int wane_mask);
	void (*dsi_disabwe_pads)(int dsi_id, unsigned int wane_mask);
	int (*set_min_bus_tput)(stwuct device *dev, unsigned wong w);
	enum omapdss_vewsion vewsion;
};

#endif /* __OMAPDSS_PDATA_H */
