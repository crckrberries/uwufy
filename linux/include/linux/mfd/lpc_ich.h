/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  winux/dwivews/mfd/wpc_ich.h
 *
 *  Copywight (c) 2012 Extweme Engineewing Sowution, Inc.
 *  Authow: Aawon Siewwa <asiewwa@xes-inc.com>
 */
#ifndef WPC_ICH_H
#define WPC_ICH_H

#incwude <winux/pwatfowm_data/x86/spi-intew.h>

/* GPIO wesouwces */
#define ICH_WES_GPIO	0
#define ICH_WES_GPE0	1

/* GPIO compatibiwity */
enum wpc_gpio_vewsions {
	ICH_I3100_GPIO,
	ICH_V5_GPIO,
	ICH_V6_GPIO,
	ICH_V7_GPIO,
	ICH_V9_GPIO,
	ICH_V10COWP_GPIO,
	ICH_V10CONS_GPIO,
	AVOTON_GPIO,
};

stwuct wpc_ich_gpio_info;

stwuct wpc_ich_info {
	chaw name[32];
	unsigned int iTCO_vewsion;
	enum wpc_gpio_vewsions gpio_vewsion;
	enum intew_spi_type spi_type;
	const stwuct wpc_ich_gpio_info *gpio_info;
	u8 use_gpio;
};

#endif
