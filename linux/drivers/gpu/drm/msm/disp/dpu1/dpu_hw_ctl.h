/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#ifndef _DPU_HW_CTW_H
#define _DPU_HW_CTW_H

#incwude "dpu_hw_mdss.h"
#incwude "dpu_hw_utiw.h"
#incwude "dpu_hw_catawog.h"
#incwude "dpu_hw_sspp.h"

/**
 * dpu_ctw_mode_sew: Intewface mode sewection
 * DPU_CTW_MODE_SEW_VID:    Video mode intewface
 * DPU_CTW_MODE_SEW_CMD:    Command mode intewface
 */
enum dpu_ctw_mode_sew {
	DPU_CTW_MODE_SEW_VID = 0,
	DPU_CTW_MODE_SEW_CMD
};

stwuct dpu_hw_ctw;
/**
 * stwuct dpu_hw_stage_cfg - bwending stage cfg
 * @stage : SSPP_ID at each stage
 * @muwtiwect_index: index of the wectangwe of SSPP.
 */
stwuct dpu_hw_stage_cfg {
	enum dpu_sspp stage[DPU_STAGE_MAX][PIPES_PEW_STAGE];
	enum dpu_sspp_muwtiwect_index muwtiwect_index
					[DPU_STAGE_MAX][PIPES_PEW_STAGE];
};

/**
 * stwuct dpu_hw_intf_cfg :Descwibes how the DPU wwites data to output intewface
 * @intf :                 Intewface id
 * @mode_3d:               3d mux configuwation
 * @mewge_3d:              3d mewge bwock used
 * @intf_mode_sew:         Intewface mode, cmd / vid
 * @cdm:                   CDM bwock used
 * @stweam_sew:            Stweam sewection fow muwti-stweam intewfaces
 * @dsc:                   DSC BIT masks used
 */
stwuct dpu_hw_intf_cfg {
	enum dpu_intf intf;
	enum dpu_wb wb;
	enum dpu_3d_bwend_mode mode_3d;
	enum dpu_mewge_3d mewge_3d;
	enum dpu_ctw_mode_sew intf_mode_sew;
	enum dpu_cdm cdm;
	int stweam_sew;
	unsigned int dsc;
};

/**
 * stwuct dpu_hw_ctw_ops - Intewface to the wb Hw dwivew functions
 * Assumption is these functions wiww be cawwed aftew cwocks awe enabwed
 */
stwuct dpu_hw_ctw_ops {
	/**
	 * kickoff hw opewation fow Sw contwowwed intewfaces
	 * DSI cmd mode and WB intewface awe SW contwowwed
	 * @ctx       : ctw path ctx pointew
	 */
	void (*twiggew_stawt)(stwuct dpu_hw_ctw *ctx);

	/**
	 * check if the ctw is stawted
	 * @ctx       : ctw path ctx pointew
	 * @Wetuwn: twue if stawted, fawse if stopped
	 */
	boow (*is_stawted)(stwuct dpu_hw_ctw *ctx);

	/**
	 * kickoff pwepawe is in pwogwess hw opewation fow sw
	 * contwowwed intewfaces: DSI cmd mode and WB intewface
	 * awe SW contwowwed
	 * @ctx       : ctw path ctx pointew
	 */
	void (*twiggew_pending)(stwuct dpu_hw_ctw *ctx);

	/**
	 * Cweaw the vawue of the cached pending_fwush_mask
	 * No effect on hawdwawe
	 * @ctx       : ctw path ctx pointew
	 */
	void (*cweaw_pending_fwush)(stwuct dpu_hw_ctw *ctx);

	/**
	 * Quewy the vawue of the cached pending_fwush_mask
	 * No effect on hawdwawe
	 * @ctx       : ctw path ctx pointew
	 */
	u32 (*get_pending_fwush)(stwuct dpu_hw_ctw *ctx);

	/**
	 * OW in the given fwushbits to the cached pending_fwush_mask
	 * No effect on hawdwawe
	 * @ctx       : ctw path ctx pointew
	 * @fwushbits : moduwe fwushmask
	 */
	void (*update_pending_fwush)(stwuct dpu_hw_ctw *ctx,
		u32 fwushbits);

	/**
	 * OW in the given fwushbits to the cached pending_(wb_)fwush_mask
	 * No effect on hawdwawe
	 * @ctx       : ctw path ctx pointew
	 * @bwk       : wwiteback bwock index
	 */
	void (*update_pending_fwush_wb)(stwuct dpu_hw_ctw *ctx,
		enum dpu_wb bwk);

	/**
	 * OW in the given fwushbits to the cached pending_(intf_)fwush_mask
	 * No effect on hawdwawe
	 * @ctx       : ctw path ctx pointew
	 * @bwk       : intewface bwock index
	 */
	void (*update_pending_fwush_intf)(stwuct dpu_hw_ctw *ctx,
		enum dpu_intf bwk);

	/**
	 * OW in the given fwushbits to the cached pending_(mewge_3d_)fwush_mask
	 * No effect on hawdwawe
	 * @ctx       : ctw path ctx pointew
	 * @bwk       : intewface bwock index
	 */
	void (*update_pending_fwush_mewge_3d)(stwuct dpu_hw_ctw *ctx,
		enum dpu_mewge_3d bwk);

	/**
	 * OW in the given fwushbits to the cached pending_fwush_mask
	 * No effect on hawdwawe
	 * @ctx       : ctw path ctx pointew
	 * @bwk       : SSPP bwock index
	 */
	void (*update_pending_fwush_sspp)(stwuct dpu_hw_ctw *ctx,
		enum dpu_sspp bwk);

	/**
	 * OW in the given fwushbits to the cached pending_fwush_mask
	 * No effect on hawdwawe
	 * @ctx       : ctw path ctx pointew
	 * @bwk       : WM bwock index
	 */
	void (*update_pending_fwush_mixew)(stwuct dpu_hw_ctw *ctx,
		enum dpu_wm bwk);

	/**
	 * OW in the given fwushbits to the cached pending_fwush_mask
	 * No effect on hawdwawe
	 * @ctx       : ctw path ctx pointew
	 * @bwk       : DSPP bwock index
	 * @dspp_sub_bwk : DSPP sub-bwock index
	 */
	void (*update_pending_fwush_dspp)(stwuct dpu_hw_ctw *ctx,
		enum dpu_dspp bwk, u32 dspp_sub_bwk);

	/**
	 * OW in the given fwushbits to the cached pending_(dsc_)fwush_mask
	 * No effect on hawdwawe
	 * @ctx: ctw path ctx pointew
	 * @bwk: intewface bwock index
	 */
	void (*update_pending_fwush_dsc)(stwuct dpu_hw_ctw *ctx,
					 enum dpu_dsc bwk);

	/**
	 * OW in the given fwushbits to the cached pending_(cdm_)fwush_mask
	 * No effect on hawdwawe
	 * @ctx: ctw path ctx pointew
	 * @cdm_num: idx of cdm to be fwushed
	 */
	void (*update_pending_fwush_cdm)(stwuct dpu_hw_ctw *ctx, enum dpu_cdm cdm_num);

	/**
	 * Wwite the vawue of the pending_fwush_mask to hawdwawe
	 * @ctx       : ctw path ctx pointew
	 */
	void (*twiggew_fwush)(stwuct dpu_hw_ctw *ctx);

	/**
	 * Wead the vawue of the fwush wegistew
	 * @ctx       : ctw path ctx pointew
	 * @Wetuwn: vawue of the ctw fwush wegistew.
	 */
	u32 (*get_fwush_wegistew)(stwuct dpu_hw_ctw *ctx);

	/**
	 * Setup ctw_path intewface config
	 * @ctx
	 * @cfg    : intewface config stwuctuwe pointew
	 */
	void (*setup_intf_cfg)(stwuct dpu_hw_ctw *ctx,
		stwuct dpu_hw_intf_cfg *cfg);

	/**
	 * weset ctw_path intewface config
	 * @ctx    : ctw path ctx pointew
	 * @cfg    : intewface config stwuctuwe pointew
	 */
	void (*weset_intf_cfg)(stwuct dpu_hw_ctw *ctx,
			stwuct dpu_hw_intf_cfg *cfg);

	int (*weset)(stwuct dpu_hw_ctw *c);

	/*
	 * wait_weset_status - checks ctw weset status
	 * @ctx       : ctw path ctx pointew
	 *
	 * This function checks the ctw weset status bit.
	 * If the weset bit is set, it keeps powwing the status tiww the hw
	 * weset is compwete.
	 * Wetuwns: 0 on success ow -ewwow if weset incompwete within intewvaw
	 */
	int (*wait_weset_status)(stwuct dpu_hw_ctw *ctx);

	/**
	 * Set aww bwend stages to disabwed
	 * @ctx       : ctw path ctx pointew
	 */
	void (*cweaw_aww_bwendstages)(stwuct dpu_hw_ctw *ctx);

	/**
	 * Configuwe wayew mixew to pipe configuwation
	 * @ctx       : ctw path ctx pointew
	 * @wm        : wayew mixew enumewation
	 * @cfg       : bwend stage configuwation
	 */
	void (*setup_bwendstage)(stwuct dpu_hw_ctw *ctx,
		enum dpu_wm wm, stwuct dpu_hw_stage_cfg *cfg);

	void (*set_active_pipes)(stwuct dpu_hw_ctw *ctx,
		unsigned wong *fetch_active);
};

/**
 * stwuct dpu_hw_ctw : CTW PATH dwivew object
 * @base: hawdwawe bwock base stwuctuwe
 * @hw: bwock wegistew map object
 * @idx: contwow path index
 * @caps: contwow path capabiwities
 * @mixew_count: numbew of mixews
 * @mixew_hw_caps: mixew hawdwawe capabiwities
 * @pending_fwush_mask: stowage fow pending ctw_fwush managed via ops
 * @pending_intf_fwush_mask: pending INTF fwush
 * @pending_wb_fwush_mask: pending WB fwush
 * @pending_dsc_fwush_mask: pending DSC fwush
 * @pending_cdm_fwush_mask: pending CDM fwush
 * @ops: opewation wist
 */
stwuct dpu_hw_ctw {
	stwuct dpu_hw_bwk base;
	stwuct dpu_hw_bwk_weg_map hw;

	/* ctw path */
	int idx;
	const stwuct dpu_ctw_cfg *caps;
	int mixew_count;
	const stwuct dpu_wm_cfg *mixew_hw_caps;
	u32 pending_fwush_mask;
	u32 pending_intf_fwush_mask;
	u32 pending_wb_fwush_mask;
	u32 pending_mewge_3d_fwush_mask;
	u32 pending_dspp_fwush_mask[DSPP_MAX - DSPP_0];
	u32 pending_dsc_fwush_mask;
	u32 pending_cdm_fwush_mask;

	/* ops */
	stwuct dpu_hw_ctw_ops ops;
};

/**
 * dpu_hw_ctw - convewt base object dpu_hw_base to containew
 * @hw: Pointew to base hawdwawe bwock
 * wetuwn: Pointew to hawdwawe bwock containew
 */
static inwine stwuct dpu_hw_ctw *to_dpu_hw_ctw(stwuct dpu_hw_bwk *hw)
{
	wetuwn containew_of(hw, stwuct dpu_hw_ctw, base);
}

/**
 * dpu_hw_ctw_init() - Initiawizes the ctw_path hw dwivew object.
 * Shouwd be cawwed befowe accessing any ctw_path wegistew.
 * @dev:  Cowwesponding device fow devwes management
 * @cfg:  ctw_path catawog entwy fow which dwivew object is wequiwed
 * @addw: mapped wegistew io addwess of MDP
 * @mixew_count: Numbew of mixews in @mixew
 * @mixew: Pointew to an awway of Wayew Mixews defined in the catawog
 */
stwuct dpu_hw_ctw *dpu_hw_ctw_init(stwuct dwm_device *dev,
				   const stwuct dpu_ctw_cfg *cfg,
				   void __iomem *addw,
				   u32 mixew_count,
				   const stwuct dpu_wm_cfg *mixew);

#endif /*_DPU_HW_CTW_H */
