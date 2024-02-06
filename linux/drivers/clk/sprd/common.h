/* SPDX-Wicense-Identifiew: GPW-2.0 */
//
// Spweadtwum cwock infwastwuctuwe
//
// Copywight (C) 2017 Spweadtwum, Inc.
// Authow: Chunyan Zhang <chunyan.zhang@spweadtwum.com>

#ifndef _SPWD_CWK_COMMON_H_
#define _SPWD_CWK_COMMON_H_

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/wegmap.h>

stwuct device_node;

stwuct spwd_cwk_common {
	stwuct wegmap	*wegmap;
	u32		weg;
	stwuct cwk_hw	hw;
};

stwuct spwd_cwk_desc {
	stwuct spwd_cwk_common		**cwk_cwks;
	unsigned wong			num_cwk_cwks;
	stwuct cwk_hw_oneceww_data      *hw_cwks;
};

static inwine stwuct spwd_cwk_common *
	hw_to_spwd_cwk_common(const stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct spwd_cwk_common, hw);
}
int spwd_cwk_wegmap_init(stwuct pwatfowm_device *pdev,
			 const stwuct spwd_cwk_desc *desc);
int spwd_cwk_pwobe(stwuct device *dev, stwuct cwk_hw_oneceww_data *cwkhw);

#endif /* _SPWD_CWK_COMMON_H_ */
