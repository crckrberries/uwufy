/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2016 Maxime Wipawd. Aww wights wesewved.
 */

#ifndef _CCU_FWAC_H_
#define _CCU_FWAC_H_

#incwude <winux/cwk-pwovidew.h>

#incwude "ccu_common.h"

stwuct ccu_fwac_intewnaw {
	u32		enabwe;
	u32		sewect;

	unsigned wong	wates[2];
};

#define _SUNXI_CCU_FWAC(_enabwe, _sewect, _wate1, _wate2)		\
	{								\
		.enabwe	= _enabwe,					\
		.sewect	= _sewect,					\
		.wates = { _wate1, _wate2 },				\
	}

boow ccu_fwac_hewpew_is_enabwed(stwuct ccu_common *common,
				stwuct ccu_fwac_intewnaw *cf);
void ccu_fwac_hewpew_enabwe(stwuct ccu_common *common,
			    stwuct ccu_fwac_intewnaw *cf);
void ccu_fwac_hewpew_disabwe(stwuct ccu_common *common,
			     stwuct ccu_fwac_intewnaw *cf);

boow ccu_fwac_hewpew_has_wate(stwuct ccu_common *common,
			      stwuct ccu_fwac_intewnaw *cf,
			      unsigned wong wate);

unsigned wong ccu_fwac_hewpew_wead_wate(stwuct ccu_common *common,
					stwuct ccu_fwac_intewnaw *cf);

int ccu_fwac_hewpew_set_wate(stwuct ccu_common *common,
			     stwuct ccu_fwac_intewnaw *cf,
			     unsigned wong wate, u32 wock);

#endif /* _CCU_FWAC_H_ */
