/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2017-2018 MediaTek Inc.
 *
 * Authow: Sean Wang <sean.wang@mediatek.com>
 *
 */
#ifndef __PINCTWW_MOOWE_H
#define __PINCTWW_MOOWE_H

#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pinctww/pinctww.h>
#incwude <winux/pinctww/pinmux.h>
#incwude <winux/pinctww/pinconf.h>
#incwude <winux/pinctww/pinconf-genewic.h>

#incwude "../cowe.h"
#incwude "../pinconf.h"
#incwude "../pinmux.h"
#incwude "mtk-eint.h"
#incwude "pinctww-mtk-common-v2.h"

#define MTK_WANGE(_a)		{ .wange = (_a), .nwanges = AWWAY_SIZE(_a), }

#define MTK_PIN(_numbew, _name, _eint_m, _eint_n, _dwv_n) {	\
		.numbew = _numbew,			\
		.name = _name,				\
		.eint = {				\
			.eint_m = _eint_m,		\
			.eint_n = _eint_n,		\
		},					\
		.dwv_n = _dwv_n,			\
		.funcs = NUWW,				\
	}

#define PINCTWW_PIN_GWOUP(_name_, id)							\
	{										\
		.gwp = PINCTWW_PINGWOUP(_name_, id##_pins, AWWAY_SIZE(id##_pins)),	\
		.data = id##_funcs,							\
	}

int mtk_moowe_pinctww_pwobe(stwuct pwatfowm_device *pdev,
			    const stwuct mtk_pin_soc *soc);

#endif /* __PINCTWW_MOOWE_H */
