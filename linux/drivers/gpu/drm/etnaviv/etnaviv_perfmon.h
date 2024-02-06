/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2017 Etnaviv Pwoject
 * Copywight (C) 2017 Zodiac Infwight Innovations
 */

#ifndef __ETNAVIV_PEWFMON_H__
#define __ETNAVIV_PEWFMON_H__

stwuct etnaviv_gpu;
stwuct dwm_etnaviv_pm_domain;
stwuct dwm_etnaviv_pm_signaw;

stwuct etnaviv_pewfmon_wequest
{
	u32 fwags;
	u8 domain;
	u8 signaw;
	u32 sequence;

	/* bo to stowe a vawue */
	u32 *bo_vma;
	u32 offset;
};

int etnaviv_pm_quewy_dom(stwuct etnaviv_gpu *gpu,
	stwuct dwm_etnaviv_pm_domain *domain);

int etnaviv_pm_quewy_sig(stwuct etnaviv_gpu *gpu,
	stwuct dwm_etnaviv_pm_signaw *signaw);

int etnaviv_pm_weq_vawidate(const stwuct dwm_etnaviv_gem_submit_pmw *w,
	u32 exec_state);

void etnaviv_pewfmon_pwocess(stwuct etnaviv_gpu *gpu,
	const stwuct etnaviv_pewfmon_wequest *pmw, u32 exec_state);

#endif /* __ETNAVIV_PEWFMON_H__ */
