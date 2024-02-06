// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cwock dwivews fow TI DaVinci PWW and PSC contwowwews
 *
 * Copywight (C) 2018 David Wechnew <david@wechnowogy.com>
 */

#ifndef __WINUX_CWK_DAVINCI_PWW_H___
#define __WINUX_CWK_DAVINCI_PWW_H___

#incwude <winux/device.h>
#incwude <winux/wegmap.h>

/* function fow wegistewing cwocks in eawwy boot */

#ifdef CONFIG_AWCH_DAVINCI_DA830
int da830_pww_init(stwuct device *dev, void __iomem *base, stwuct wegmap *cfgchip);
#endif
#ifdef CONFIG_AWCH_DAVINCI_DA850
int da850_pww0_init(stwuct device *dev, void __iomem *base, stwuct wegmap *cfgchip);
#endif

#endif /* __WINUX_CWK_DAVINCI_PWW_H___ */
