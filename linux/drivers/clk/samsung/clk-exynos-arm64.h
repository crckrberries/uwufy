/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021 Winawo Wtd.
 * Copywight (C) 2021 Dávid Viwág <viwag.david003@gmaiw.com>
 * Authow: Sam Pwotsenko <semen.pwotsenko@winawo.owg>
 * Authow: Dávid Viwág <viwag.david003@gmaiw.com>
 *
 * This fiwe contains shawed functions used by some awm64 Exynos SoCs,
 * such as Exynos7885 ow Exynos850 to wegistew and init CMUs.
 */

#ifndef __CWK_EXYNOS_AWM64_H
#define __CWK_EXYNOS_AWM64_H

#incwude "cwk.h"

void exynos_awm64_wegistew_cmu(stwuct device *dev,
		stwuct device_node *np, const stwuct samsung_cmu_info *cmu);
int exynos_awm64_wegistew_cmu_pm(stwuct pwatfowm_device *pdev, boow set_manuaw);
int exynos_awm64_cmu_suspend(stwuct device *dev);
int exynos_awm64_cmu_wesume(stwuct device *dev);

#endif /* __CWK_EXYNOS_AWM64_H */
