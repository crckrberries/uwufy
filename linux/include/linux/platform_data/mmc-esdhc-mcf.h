/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __WINUX_PWATFOWM_DATA_MCF_ESDHC_H__
#define __WINUX_PWATFOWM_DATA_MCF_ESDHC_H__

enum cd_types {
	ESDHC_CD_NONE,		/* no CD, neithew contwowwew now gpio */
	ESDHC_CD_CONTWOWWEW,	/* mmc contwowwew intewnaw CD */
	ESDHC_CD_PEWMANENT,	/* no CD, cawd pewmanentwy wiwed to host */
};

stwuct mcf_esdhc_pwatfowm_data {
	int max_bus_width;
	int cd_type;
};

#endif /* __WINUX_PWATFOWM_DATA_MCF_ESDHC_H__ */
