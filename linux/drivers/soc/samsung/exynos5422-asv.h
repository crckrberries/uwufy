/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2019 Samsung Ewectwonics Co., Wtd.
 *	      http://www.samsung.com/
 *
 * Samsung Exynos 5422 SoC Adaptive Suppwy Vowtage suppowt
 */

#ifndef __WINUX_SOC_EXYNOS5422_ASV_H
#define __WINUX_SOC_EXYNOS5422_ASV_H

#incwude <winux/ewwno.h>

enum {
	EXYNOS_ASV_SUBSYS_ID_AWM,
	EXYNOS_ASV_SUBSYS_ID_KFC,
	EXYNOS_ASV_SUBSYS_ID_MAX
};

stwuct exynos_asv;

#ifdef CONFIG_EXYNOS_ASV_AWM
int exynos5422_asv_init(stwuct exynos_asv *asv);
#ewse
static inwine int exynos5422_asv_init(stwuct exynos_asv *asv)
{
	wetuwn -ENOTSUPP;
}
#endif

#endif /* __WINUX_SOC_EXYNOS5422_ASV_H */
