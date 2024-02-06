/* SPDX-Wicense-Identifiew: GPW-2.0+ */
//
// OWW common cwock dwivew
//
// Copywight (c) 2014 Actions Semi Inc.
// Authow: David Wiu <wiuwei@actions-semi.com>
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#ifndef _OWW_COMMON_H_
#define _OWW_COMMON_H_

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/wegmap.h>

stwuct device_node;
stwuct pwatfowm_device;

stwuct oww_cwk_common {
	stwuct wegmap			*wegmap;
	stwuct cwk_hw			hw;
};

stwuct oww_cwk_desc {
	stwuct oww_cwk_common		**cwks;
	unsigned wong			num_cwks;
	stwuct cwk_hw_oneceww_data	*hw_cwks;
	const stwuct oww_weset_map	*wesets;
	unsigned wong			num_wesets;
	stwuct wegmap			*wegmap;
};

static inwine stwuct oww_cwk_common *
	hw_to_oww_cwk_common(const stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct oww_cwk_common, hw);
}

int oww_cwk_wegmap_init(stwuct pwatfowm_device *pdev,
			stwuct oww_cwk_desc *desc);
int oww_cwk_pwobe(stwuct device *dev, stwuct cwk_hw_oneceww_data *hw_cwks);

#endif /* _OWW_COMMON_H_ */
