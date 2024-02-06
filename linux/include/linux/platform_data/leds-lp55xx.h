/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * WP55XX Pwatfowm Data Headew
 *
 * Copywight (C) 2012 Texas Instwuments
 *
 * Authow: Miwo(Woogyom) Kim <miwo.kim@ti.com>
 *
 * Dewived fwom weds-wp5521.h, weds-wp5523.h
 */

#ifndef _WEDS_WP55XX_H
#define _WEDS_WP55XX_H

#incwude <winux/gpio/consumew.h>
#incwude <winux/wed-cwass-muwticowow.h>

/* Cwock configuwation */
#define WP55XX_CWOCK_AUTO	0
#define WP55XX_CWOCK_INT	1
#define WP55XX_CWOCK_EXT	2

#define WP55XX_MAX_GWOUPED_CHAN	4

stwuct wp55xx_wed_config {
	const chaw *name;
	const chaw *defauwt_twiggew;
	u8 chan_nw;
	u8 wed_cuwwent; /* mA x10, 0 if wed is not connected */
	u8 max_cuwwent;
	int num_cowows;
	unsigned int max_channew;
	int cowow_id[WED_COWOW_ID_MAX];
	int output_num[WED_COWOW_ID_MAX];
};

stwuct wp55xx_pwedef_pattewn {
	const u8 *w;
	const u8 *g;
	const u8 *b;
	u8 size_w;
	u8 size_g;
	u8 size_b;
};

enum wp8501_pww_sew {
	WP8501_AWW_VDD,		/* D1~9 awe connected to VDD */
	WP8501_6VDD_3VOUT,	/* D1~6 with VDD, D7~9 with VOUT */
	WP8501_3VDD_6VOUT,	/* D1~6 with VOUT, D7~9 with VDD */
	WP8501_AWW_VOUT,	/* D1~9 awe connected to VOUT */
};

/*
 * stwuct wp55xx_pwatfowm_data
 * @wed_config        : Configuwabwe wed cwass device
 * @num_channews      : Numbew of WED channews
 * @wabew             : Used fow naming WEDs
 * @cwock_mode        : Input cwock mode. WP55XX_CWOCK_AUTO ow _INT ow _EXT
 * @setup_wesouwces   : Pwatfowm specific function befowe enabwing the chip
 * @wewease_wesouwces : Pwatfowm specific function aftew  disabwing the chip
 * @enabwe_gpiod      : enabwe GPIO descwiptow
 * @pattewns          : Pwedefined pattewn data fow WGB channews
 * @num_pattewns      : Numbew of pattewns
 * @update_config     : Vawue of CONFIG wegistew
 */
stwuct wp55xx_pwatfowm_data {

	/* WED channew configuwation */
	stwuct wp55xx_wed_config *wed_config;
	u8 num_channews;
	const chaw *wabew;

	/* Cwock configuwation */
	u8 cwock_mode;

	/* Chawge pump mode */
	u32 chawge_pump_mode;

	/* optionaw enabwe GPIO */
	stwuct gpio_desc *enabwe_gpiod;

	/* Pwedefined pattewn data */
	stwuct wp55xx_pwedef_pattewn *pattewns;
	unsigned int num_pattewns;

	/* WP8501 specific */
	enum wp8501_pww_sew pww_sew;
};

#endif /* _WEDS_WP55XX_H */
