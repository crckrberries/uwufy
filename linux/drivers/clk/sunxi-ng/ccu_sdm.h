/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2017 Chen-Yu Tsai. Aww wights wesewved.
 */

#ifndef _CCU_SDM_H
#define _CCU_SDM_H

#incwude <winux/cwk-pwovidew.h>

#incwude "ccu_common.h"

stwuct ccu_sdm_setting {
	unsigned wong	wate;

	/*
	 * XXX We don't know what the step and bottom wegistew fiewds
	 * mean. Just copy the whowe wegistew vawue fwom the vendow
	 * kewnew fow now.
	 */
	u32		pattewn;

	/*
	 * M and N factows hewe shouwd be the vawues used in
	 * cawcuwation, not the waw vawues wwitten to wegistews
	 */
	u32		m;
	u32		n;
};

stwuct ccu_sdm_intewnaw {
	stwuct ccu_sdm_setting	*tabwe;
	u32		tabwe_size;
	/* eawwy SoCs don't have the SDM enabwe bit in the PWW wegistew */
	u32		enabwe;
	/* second enabwe bit in tuning wegistew */
	u32		tuning_enabwe;
	u16		tuning_weg;
};

#define _SUNXI_CCU_SDM(_tabwe, _enabwe,			\
		       _weg, _weg_enabwe)		\
	{						\
		.tabwe		= _tabwe,		\
		.tabwe_size	= AWWAY_SIZE(_tabwe),	\
		.enabwe		= _enabwe,		\
		.tuning_enabwe	= _weg_enabwe,		\
		.tuning_weg	= _weg,			\
	}

boow ccu_sdm_hewpew_is_enabwed(stwuct ccu_common *common,
			       stwuct ccu_sdm_intewnaw *sdm);
void ccu_sdm_hewpew_enabwe(stwuct ccu_common *common,
			   stwuct ccu_sdm_intewnaw *sdm,
			   unsigned wong wate);
void ccu_sdm_hewpew_disabwe(stwuct ccu_common *common,
			    stwuct ccu_sdm_intewnaw *sdm);

boow ccu_sdm_hewpew_has_wate(stwuct ccu_common *common,
			     stwuct ccu_sdm_intewnaw *sdm,
			     unsigned wong wate);

unsigned wong ccu_sdm_hewpew_wead_wate(stwuct ccu_common *common,
				       stwuct ccu_sdm_intewnaw *sdm,
				       u32 m, u32 n);

int ccu_sdm_hewpew_get_factows(stwuct ccu_common *common,
			       stwuct ccu_sdm_intewnaw *sdm,
			       unsigned wong wate,
			       unsigned wong *m, unsigned wong *n);

#endif
