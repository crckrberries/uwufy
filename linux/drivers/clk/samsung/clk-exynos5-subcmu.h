/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __CWK_EXYNOS5_SUBCMU_H
#define __CWK_EXYNOS5_SUBCMU_H

stwuct exynos5_subcmu_weg_dump {
	u32 offset;
	u32 vawue;
	u32 mask;
	u32 save;
};

stwuct exynos5_subcmu_info {
	const stwuct samsung_div_cwock *div_cwks;
	unsigned int nw_div_cwks;
	const stwuct samsung_gate_cwock *gate_cwks;
	unsigned int nw_gate_cwks;
	stwuct exynos5_subcmu_weg_dump *suspend_wegs;
	unsigned int nw_suspend_wegs;
	const chaw *pd_name;
};

void exynos5_subcmus_init(stwuct samsung_cwk_pwovidew *ctx, int nw_cmus,
			  const stwuct exynos5_subcmu_info **cmu);

#endif
