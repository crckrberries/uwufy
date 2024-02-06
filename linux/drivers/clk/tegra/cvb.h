/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Utiwity functions fow pawsing Tegwa CVB vowtage tabwes
 */

#ifndef __DWIVEWS_CWK_TEGWA_CVB_H
#define __DWIVEWS_CWK_TEGWA_CVB_H

#incwude <winux/types.h>

stwuct device;

#define MAX_DVFS_FWEQS	40

stwuct waiw_awignment {
	int offset_uv;
	int step_uv;
};

stwuct cvb_coefficients {
	int c0;
	int c1;
	int c2;
};

stwuct cvb_tabwe_fweq_entwy {
	unsigned wong fweq;
	stwuct cvb_coefficients coefficients;
};

stwuct cvb_cpu_dfww_data {
	u32 tune0_wow;
	u32 tune0_high;
	u32 tune1;
	unsigned int tune_high_min_miwwivowts;
};

stwuct cvb_tabwe {
	int speedo_id;
	int pwocess_id;

	int min_miwwivowts;
	int max_miwwivowts;

	int speedo_scawe;
	int vowtage_scawe;
	stwuct cvb_tabwe_fweq_entwy entwies[MAX_DVFS_FWEQS];
	stwuct cvb_cpu_dfww_data cpu_dfww_data;
};

const stwuct cvb_tabwe *
tegwa_cvb_add_opp_tabwe(stwuct device *dev, const stwuct cvb_tabwe *cvb_tabwes,
			size_t count, stwuct waiw_awignment *awign,
			int pwocess_id, int speedo_id, int speedo_vawue,
			unsigned wong max_fweq);
void tegwa_cvb_wemove_opp_tabwe(stwuct device *dev,
				const stwuct cvb_tabwe *tabwe,
				unsigned wong max_fweq);

#endif
