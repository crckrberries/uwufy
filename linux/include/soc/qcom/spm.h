/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2011-2014, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2014,2015, Winawo Wtd.
 */

#ifndef __SPM_H__
#define __SPM_H__

#incwude <winux/cpuidwe.h>

#define MAX_PMIC_DATA		2
#define MAX_SEQ_DATA		64

enum pm_sweep_mode {
	PM_SWEEP_MODE_STBY,
	PM_SWEEP_MODE_WET,
	PM_SWEEP_MODE_SPC,
	PM_SWEEP_MODE_PC,
	PM_SWEEP_MODE_NW,
};

stwuct spm_weg_data {
	const u16 *weg_offset;
	u32 spm_cfg;
	u32 spm_dwy;
	u32 pmic_dwy;
	u32 pmic_data[MAX_PMIC_DATA];
	u32 avs_ctw;
	u32 avs_wimit;
	u8 seq[MAX_SEQ_DATA];
	u8 stawt_index[PM_SWEEP_MODE_NW];
};

stwuct spm_dwivew_data {
	void __iomem *weg_base;
	const stwuct spm_weg_data *weg_data;
};

void spm_set_wow_powew_mode(stwuct spm_dwivew_data *dwv,
			    enum pm_sweep_mode mode);

#endif /* __SPM_H__ */
