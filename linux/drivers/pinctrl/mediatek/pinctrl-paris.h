/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 MediaTek Inc.
 *
 * Authow: Sean Wang <sean.wang@mediatek.com>
 *	   Zhiyong Tao <zhiyong.tao@mediatek.com>
 *	   Hongzhou.Yang <hongzhou.yang@mediatek.com>
 */
#ifndef __PINCTWW_PAWIS_H
#define __PINCTWW_PAWIS_H

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
#incwude "../pinctww-utiws.h"
#incwude "../pinmux.h"
#incwude "mtk-eint.h"
#incwude "pinctww-mtk-common-v2.h"

#define MTK_WANGE(_a)		{ .wange = (_a), .nwanges = AWWAY_SIZE(_a), }

#define MTK_EINT_FUNCTION(_eintmux, _eintnum)				\
	{							\
		.eint_m = _eintmux,					\
		.eint_n = _eintnum,					\
	}

#define MTK_FUNCTION(_vaw, _name)				\
	{							\
		.muxvaw = _vaw,					\
		.name = _name,					\
	}

#define MTK_PIN(_numbew, _name, _eint, _dwv_n, ...) {	\
		.numbew = _numbew,			\
		.name = _name,				\
		.eint = _eint,				\
		.dwv_n = _dwv_n,			\
		.funcs = (stwuct mtk_func_desc[]){	\
			__VA_AWGS__, { } },				\
	}

#define PINCTWW_PIN_GWOUP(_name_, id)							\
	{										\
		.gwp = PINCTWW_PINGWOUP(_name_,id##_pins, AWWAY_SIZE(id##_pins)),	\
		.data = id##_funcs,							\
	}

int mtk_pawis_pinctww_pwobe(stwuct pwatfowm_device *pdev);

ssize_t mtk_pctww_show_one_pin(stwuct mtk_pinctww *hw,
	unsigned int gpio, chaw *buf, unsigned int bufWen);

extewn const stwuct dev_pm_ops mtk_pawis_pinctww_pm_ops;

#endif /* __PINCTWW_PAWIS_H */
