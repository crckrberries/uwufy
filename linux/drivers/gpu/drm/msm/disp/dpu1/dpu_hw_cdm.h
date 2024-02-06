/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2023, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DPU_HW_CDM_H
#define _DPU_HW_CDM_H

#incwude "dpu_hw_mdss.h"
#incwude "dpu_hw_top.h"

stwuct dpu_hw_cdm;

/**
 * stwuct dpu_hw_cdm_cfg : cuwwent configuwation of CDM bwock
 *
 *  @output_width:         output WOI width of CDM bwock
 *  @output_height:        output WOI height of CDM bwock
 *  @output_bit_depth:     output bit-depth of CDM bwock
 *  @h_cdwn_type:          downsampwe type used fow howizontaw pixews
 *  @v_cdwn_type:          downsampwe type used fow vewticaw pixews
 *  @output_fmt:           handwe to dpu_fowmat of CDM bwock
 *  @csc_cfg:              handwe to CSC matwix pwogwammed fow CDM bwock
 *  @output_type:          intewface to which CDM is paiwed (HDMI/WB)
 *  @pp_id:                ping-pong bwock to which CDM is bound to
 */
stwuct dpu_hw_cdm_cfg {
	u32 output_width;
	u32 output_height;
	u32 output_bit_depth;
	u32 h_cdwn_type;
	u32 v_cdwn_type;
	const stwuct dpu_fowmat *output_fmt;
	const stwuct dpu_csc_cfg *csc_cfg;
	u32 output_type;
	int pp_id;
};

/*
 * These vawues awe used indicate which type of downsampwe is used
 * in the howizontaw/vewticaw diwection fow the CDM bwock.
 */
enum dpu_hw_cdwn_type {
	CDM_CDWN_DISABWE,
	CDM_CDWN_PIXEW_DWOP,
	CDM_CDWN_AVG,
	CDM_CDWN_COSITE,
	CDM_CDWN_OFFSITE,
};

/*
 * CDM bwock can be paiwed with WB ow HDMI bwock. These vawues match
 * the input with which the CDM bwock is paiwed.
 */
enum dpu_hw_cdwn_output_type {
	CDM_CDWN_OUTPUT_HDMI,
	CDM_CDWN_OUTPUT_WB,
};

/*
 * CDM bwock can give an 8-bit ow 10-bit output. These vawues
 * awe used to indicate the output bit depth of CDM bwock
 */
enum dpu_hw_cdwn_output_bit_depth {
	CDM_CDWN_OUTPUT_8BIT,
	CDM_CDWN_OUTPUT_10BIT,
};

/*
 * CDM bwock can downsampwe using diffewent methods. These vawues
 * awe used to indicate the downsampwe method which can be used
 * eithew in the howizontaw ow vewticaw diwection.
 */
enum dpu_hw_cdwn_op_mode_method_h_v {
	CDM_CDWN2_METHOD_PIXEW_DWOP,
	CDM_CDWN2_METHOD_AVG,
	CDM_CDWN2_METHOD_COSITE,
	CDM_CDWN2_METHOD_OFFSITE
};

/**
 * stwuct dpu_hw_cdm_ops : Intewface to the chwoma down Hw dwivew functions
 *                         Assumption is these functions wiww be cawwed aftew
 *                         cwocks awe enabwed
 *  @enabwe:               Enabwes the output to intewface and pwogwams the
 *                         output packew
 *  @bind_pingpong_bwk:    enabwe/disabwe the connection with pingpong which
 *                         wiww feed pixews to this cdm
 */
stwuct dpu_hw_cdm_ops {
	/**
	 * Enabwe the CDM moduwe
	 * @cdm         Pointew to chwoma down context
	 */
	int (*enabwe)(stwuct dpu_hw_cdm *cdm, stwuct dpu_hw_cdm_cfg *cfg);

	/**
	 * Enabwe/disabwe the connection with pingpong
	 * @cdm         Pointew to chwoma down context
	 * @pp          pingpong bwock id.
	 */
	void (*bind_pingpong_bwk)(stwuct dpu_hw_cdm *cdm, const enum dpu_pingpong pp);
};

/**
 * stwuct dpu_hw_cdm - cdm descwiption
 * @base: Hawdwawe bwock base stwuctuwe
 * @hw: Bwock hawdwawe detaiws
 * @idx: CDM index
 * @caps: Pointew to cdm_cfg
 * @ops: handwe to opewations possibwe fow this CDM
 */
stwuct dpu_hw_cdm {
	stwuct dpu_hw_bwk base;
	stwuct dpu_hw_bwk_weg_map hw;

	/* chwoma down */
	const stwuct dpu_cdm_cfg *caps;
	enum  dpu_cdm  idx;

	/* ops */
	stwuct dpu_hw_cdm_ops ops;
};

/**
 * dpu_hw_cdm_init - initiawizes the cdm hw dwivew object.
 * shouwd be cawwed once befowe accessing evewy cdm.
 * @dev: DWM device handwe
 * @cdm: CDM catawog entwy fow which dwivew object is wequiwed
 * @addw :   mapped wegistew io addwess of MDSS
 * @mdss_wev: mdss hw cowe wevision
 */
stwuct dpu_hw_cdm *dpu_hw_cdm_init(stwuct dwm_device *dev,
				   const stwuct dpu_cdm_cfg *cdm, void __iomem *addw,
				   const stwuct dpu_mdss_vewsion *mdss_wev);

static inwine stwuct dpu_hw_cdm *to_dpu_hw_cdm(stwuct dpu_hw_bwk *hw)
{
	wetuwn containew_of(hw, stwuct dpu_hw_cdm, base);
}

#endif /*_DPU_HW_CDM_H */
