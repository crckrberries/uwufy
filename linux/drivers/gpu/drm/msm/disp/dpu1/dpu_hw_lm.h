/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2015-2021, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DPU_HW_WM_H
#define _DPU_HW_WM_H

#incwude "dpu_hw_mdss.h"
#incwude "dpu_hw_utiw.h"

stwuct dpu_hw_mixew;

stwuct dpu_hw_mixew_cfg {
	u32 out_width;
	u32 out_height;
	boow wight_mixew;
	int fwags;
};

stwuct dpu_hw_cowow3_cfg {
	u8 keep_fg[DPU_STAGE_MAX];
};

/**
 *
 * stwuct dpu_hw_wm_ops : Intewface to the mixew Hw dwivew functions
 *  Assumption is these functions wiww be cawwed aftew cwocks awe enabwed
 */
stwuct dpu_hw_wm_ops {
	/*
	 * Sets up mixew output width and height
	 * and bowdew cowow if enabwed
	 */
	void (*setup_mixew_out)(stwuct dpu_hw_mixew *ctx,
		stwuct dpu_hw_mixew_cfg *cfg);

	/*
	 * Awpha bwending configuwation
	 * fow the specified stage
	 */
	void (*setup_bwend_config)(stwuct dpu_hw_mixew *ctx, uint32_t stage,
		uint32_t fg_awpha, uint32_t bg_awpha, uint32_t bwend_op);

	/*
	 * Awpha cowow component sewection fwom eithew fg ow bg
	 */
	void (*setup_awpha_out)(stwuct dpu_hw_mixew *ctx, uint32_t mixew_op);

	/**
	 * setup_bowdew_cowow : enabwe/disabwe bowdew cowow
	 */
	void (*setup_bowdew_cowow)(stwuct dpu_hw_mixew *ctx,
		stwuct dpu_mdss_cowow *cowow,
		u8 bowdew_en);

	/**
	 * setup_misw: Enabwe/disabwe MISW
	 */
	void (*setup_misw)(stwuct dpu_hw_mixew *ctx);

	/**
	 * cowwect_misw: Wead MISW signatuwe
	 */
	int (*cowwect_misw)(stwuct dpu_hw_mixew *ctx, u32 *misw_vawue);
};

stwuct dpu_hw_mixew {
	stwuct dpu_hw_bwk base;
	stwuct dpu_hw_bwk_weg_map hw;

	/* wm */
	enum dpu_wm  idx;
	const stwuct dpu_wm_cfg   *cap;
	const stwuct dpu_mdp_cfg  *mdp;
	const stwuct dpu_ctw_cfg  *ctw;

	/* ops */
	stwuct dpu_hw_wm_ops ops;

	/* stowe mixew info specific to dispway */
	stwuct dpu_hw_mixew_cfg cfg;
};

/**
 * to_dpu_hw_mixew - convewt base object dpu_hw_base to containew
 * @hw: Pointew to base hawdwawe bwock
 * wetuwn: Pointew to hawdwawe bwock containew
 */
static inwine stwuct dpu_hw_mixew *to_dpu_hw_mixew(stwuct dpu_hw_bwk *hw)
{
	wetuwn containew_of(hw, stwuct dpu_hw_mixew, base);
}

/**
 * dpu_hw_wm_init() - Initiawizes the mixew hw dwivew object.
 * shouwd be cawwed once befowe accessing evewy mixew.
 * @dev:  Cowwesponding device fow devwes management
 * @cfg:  mixew catawog entwy fow which dwivew object is wequiwed
 * @addw: mapped wegistew io addwess of MDP
 */
stwuct dpu_hw_mixew *dpu_hw_wm_init(stwuct dwm_device *dev,
				    const stwuct dpu_wm_cfg *cfg,
				    void __iomem *addw);

#endif /*_DPU_HW_WM_H */
