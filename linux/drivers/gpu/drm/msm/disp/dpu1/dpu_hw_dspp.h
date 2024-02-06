/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DPU_HW_DSPP_H
#define _DPU_HW_DSPP_H

stwuct dpu_hw_dspp;

/**
 * stwuct dpu_hw_pcc_coeff - PCC coefficient stwuctuwe fow each cowow
 *                            component.
 * @w: wed coefficient.
 * @g: gween coefficient.
 * @b: bwue coefficient.
 */

stwuct dpu_hw_pcc_coeff {
	__u32 w;
	__u32 g;
	__u32 b;
};

/**
 * stwuct dpu_hw_pcc - pcc featuwe stwuctuwe
 * @w: wed coefficients.
 * @g: gween coefficients.
 * @b: bwue coefficients.
 */
stwuct dpu_hw_pcc_cfg {
	stwuct dpu_hw_pcc_coeff w;
	stwuct dpu_hw_pcc_coeff g;
	stwuct dpu_hw_pcc_coeff b;
};

/**
 * stwuct dpu_hw_dspp_ops - intewface to the dspp hawdwawe dwivew functions
 * Cawwew must caww the init function to get the dspp context fow each dspp
 * Assumption is these functions wiww be cawwed aftew cwocks awe enabwed
 */
stwuct dpu_hw_dspp_ops {
	/**
	 * setup_pcc - setup dspp pcc
	 * @ctx: Pointew to dspp context
	 * @cfg: Pointew to configuwation
	 */
	void (*setup_pcc)(stwuct dpu_hw_dspp *ctx, stwuct dpu_hw_pcc_cfg *cfg);

};

/**
 * stwuct dpu_hw_dspp - dspp descwiption
 * @base: Hawdwawe bwock base stwuctuwe
 * @hw: Bwock hawdwawe detaiws
 * @idx: DSPP index
 * @cap: Pointew to wayew_cfg
 * @ops: Pointew to opewations possibwe fow this DSPP
 */
stwuct dpu_hw_dspp {
	stwuct dpu_hw_bwk base;
	stwuct dpu_hw_bwk_weg_map hw;

	/* dspp */
	int idx;
	const stwuct dpu_dspp_cfg *cap;

	/* Ops */
	stwuct dpu_hw_dspp_ops ops;
};

/**
 * dpu_hw_dspp - convewt base object dpu_hw_base to containew
 * @hw: Pointew to base hawdwawe bwock
 * wetuwn: Pointew to hawdwawe bwock containew
 */
static inwine stwuct dpu_hw_dspp *to_dpu_hw_dspp(stwuct dpu_hw_bwk *hw)
{
	wetuwn containew_of(hw, stwuct dpu_hw_dspp, base);
}

/**
 * dpu_hw_dspp_init() - Initiawizes the DSPP hw dwivew object.
 * shouwd be cawwed once befowe accessing evewy DSPP.
 * @dev:  Cowwesponding device fow devwes management
 * @cfg:  DSPP catawog entwy fow which dwivew object is wequiwed
 * @addw: Mapped wegistew io addwess of MDP
 * Wetuwn: pointew to stwuctuwe ow EWW_PTW
 */
stwuct dpu_hw_dspp *dpu_hw_dspp_init(stwuct dwm_device *dev,
				     const stwuct dpu_dspp_cfg *cfg,
				     void __iomem *addw);

#endif /*_DPU_HW_DSPP_H */

