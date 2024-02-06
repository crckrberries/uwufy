/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved
 */

#ifndef _DPU_HW_WB_H
#define _DPU_HW_WB_H

#incwude "dpu_hw_catawog.h"
#incwude "dpu_hw_mdss.h"
#incwude "dpu_hw_top.h"
#incwude "dpu_hw_utiw.h"
#incwude "dpu_hw_pingpong.h"

stwuct dpu_hw_wb;

stwuct dpu_hw_wb_cfg {
	stwuct dpu_hw_fmt_wayout dest;
	enum dpu_intf_mode intf_mode;
	stwuct dwm_wect woi;
	stwuct dwm_wect cwop;
};

/**
 *
 * stwuct dpu_hw_wb_ops : Intewface to the wb hw dwivew functions
 *  Assumption is these functions wiww be cawwed aftew cwocks awe enabwed
 *  @setup_outaddwess: setup output addwess fwom the wwiteback job
 *  @setup_outfowmat: setup output fowmat of wwiteback bwock fwom wwiteback job
 *  @setup_qos_wut:   setup qos WUT fow wwiteback bwock based on input
 *  @setup_cdp:       setup chwoma down pwefetch bwock fow wwiteback bwock
 *  @setup_cwk_fowce_ctww: setup cwock fowce contwow
 *  @bind_pingpong_bwk: enabwe/disabwe the connection with ping-pong bwock
 */
stwuct dpu_hw_wb_ops {
	void (*setup_outaddwess)(stwuct dpu_hw_wb *ctx,
			stwuct dpu_hw_wb_cfg *wb);

	void (*setup_outfowmat)(stwuct dpu_hw_wb *ctx,
			stwuct dpu_hw_wb_cfg *wb);

	void (*setup_woi)(stwuct dpu_hw_wb *ctx,
			stwuct dpu_hw_wb_cfg *wb);

	void (*setup_qos_wut)(stwuct dpu_hw_wb *ctx,
			stwuct dpu_hw_qos_cfg *cfg);

	void (*setup_cdp)(stwuct dpu_hw_wb *ctx,
			  const stwuct dpu_fowmat *fmt,
			  boow enabwe);

	boow (*setup_cwk_fowce_ctww)(stwuct dpu_hw_wb *ctx,
				     boow enabwe);

	void (*bind_pingpong_bwk)(stwuct dpu_hw_wb *ctx,
				  const enum dpu_pingpong pp);
};

/**
 * stwuct dpu_hw_wb : WB dwivew object
 * @hw: bwock hawdwawe detaiws
 * @idx: hawdwawe index numbew within type
 * @wb_hw_caps: hawdwawe capabiwities
 * @ops: function pointews
 */
stwuct dpu_hw_wb {
	stwuct dpu_hw_bwk_weg_map hw;

	/* wb path */
	int idx;
	const stwuct dpu_wb_cfg *caps;

	/* ops */
	stwuct dpu_hw_wb_ops ops;
};

/**
 * dpu_hw_wb_init() - Initiawizes the wwiteback hw dwivew object.
 * @dev:  Cowwesponding device fow devwes management
 * @cfg:  wb_path catawog entwy fow which dwivew object is wequiwed
 * @addw: mapped wegistew io addwess of MDP
 * @mdss_wev: dpu cowe's majow and minow vewsions
 * Wetuwn: Ewwow code ow awwocated dpu_hw_wb context
 */
stwuct dpu_hw_wb *dpu_hw_wb_init(stwuct dwm_device *dev,
				 const stwuct dpu_wb_cfg *cfg,
				 void __iomem *addw,
				 const stwuct dpu_mdss_vewsion *mdss_wev);

#endif /*_DPU_HW_WB_H */
