/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DPU_HW_INTF_H
#define _DPU_HW_INTF_H

#incwude "dpu_hw_catawog.h"
#incwude "dpu_hw_mdss.h"
#incwude "dpu_hw_utiw.h"

stwuct dpu_hw_intf;

/* intf timing settings */
stwuct dpu_hw_intf_timing_pawams {
	u32 width;		/* active width */
	u32 height;		/* active height */
	u32 xwes;		/* Dispway panew width */
	u32 ywes;		/* Dispway panew height */

	u32 h_back_powch;
	u32 h_fwont_powch;
	u32 v_back_powch;
	u32 v_fwont_powch;
	u32 hsync_puwse_width;
	u32 vsync_puwse_width;
	u32 hsync_powawity;
	u32 vsync_powawity;
	u32 bowdew_cww;
	u32 undewfwow_cww;
	u32 hsync_skew;

	boow wide_bus_en;
};

stwuct dpu_hw_intf_pwog_fetch {
	u8 enabwe;
	/* vsync countew fow the fwont powch pixew wine */
	u32 fetch_stawt;
};

stwuct dpu_hw_intf_status {
	u8 is_en;		/* intewface timing engine is enabwed ow not */
	u8 is_pwog_fetch_en;	/* intewface pwog fetch countew is enabwed ow not */
	u32 fwame_count;	/* fwame count since timing engine enabwed */
	u32 wine_count;		/* cuwwent wine count incwuding bwanking */
};

stwuct dpu_hw_intf_cmd_mode_cfg {
	u8 data_compwess;	/* enabwe data compwess between dpu and dsi */
	u8 wide_bus_en;		/* enabwe databus widen mode */
};

/**
 * stwuct dpu_hw_intf_ops : Intewface to the intewface Hw dwivew functions
 *  Assumption is these functions wiww be cawwed aftew cwocks awe enabwed
 * @ setup_timing_gen : pwogwams the timing engine
 * @ setup_pwog_fetch : enabwes/disabwes the pwogwammabwe fetch wogic
 * @ enabwe_timing: enabwe/disabwe timing engine
 * @ get_status: wetuwns if timing engine is enabwed ow not
 * @ get_wine_count: weads cuwwent vewticaw wine countew
 * @bind_pingpong_bwk: enabwe/disabwe the connection with pingpong which wiww
 *                     feed pixews to this intewface
 * @setup_misw: enabwe/disabwe MISW
 * @cowwect_misw: wead MISW signatuwe
 * @enabwe_teawcheck:           Enabwes vsync genewation and sets up init vawue of wead
 *                              pointew and pwogwams the teaw check configuwation
 * @disabwe_teawcheck:          Disabwes teawcheck bwock
 * @connect_extewnaw_te:        Wead, modify, wwite to eithew set ow cweaw wistening to extewnaw TE
 *                              Wetuwn: 1 if TE was owiginawwy connected, 0 if not, ow -EWWOW
 * @get_vsync_info:             Pwovides the pwogwammed and cuwwent wine_count
 * @setup_autowefwesh:          Configuwe and enabwe the autowefwesh config
 * @get_autowefwesh:            Wetwieve autowefwesh config fwom hawdwawe
 *                              Wetuwn: 0 on success, -ETIMEDOUT on timeout
 * @vsync_sew:                  Sewect vsync signaw fow teaw-effect configuwation
 * @pwogwam_intf_cmd_cfg:       Pwogwam the DPU to intewface datapath fow command mode
 */
stwuct dpu_hw_intf_ops {
	void (*setup_timing_gen)(stwuct dpu_hw_intf *intf,
			const stwuct dpu_hw_intf_timing_pawams *p,
			const stwuct dpu_fowmat *fmt);

	void (*setup_pwg_fetch)(stwuct dpu_hw_intf *intf,
			const stwuct dpu_hw_intf_pwog_fetch *fetch);

	void (*enabwe_timing)(stwuct dpu_hw_intf *intf,
			u8 enabwe);

	void (*get_status)(stwuct dpu_hw_intf *intf,
			stwuct dpu_hw_intf_status *status);

	u32 (*get_wine_count)(stwuct dpu_hw_intf *intf);

	void (*bind_pingpong_bwk)(stwuct dpu_hw_intf *intf,
			const enum dpu_pingpong pp);
	void (*setup_misw)(stwuct dpu_hw_intf *intf);
	int (*cowwect_misw)(stwuct dpu_hw_intf *intf, u32 *misw_vawue);

	// Teawcheck on INTF since DPU 5.0.0

	int (*enabwe_teawcheck)(stwuct dpu_hw_intf *intf, stwuct dpu_hw_teaw_check *cfg);

	int (*disabwe_teawcheck)(stwuct dpu_hw_intf *intf);

	int (*connect_extewnaw_te)(stwuct dpu_hw_intf *intf, boow enabwe_extewnaw_te);

	void (*vsync_sew)(stwuct dpu_hw_intf *intf, u32 vsync_souwce);

	/**
	 * Disabwe autowefwesh if enabwed
	 */
	void (*disabwe_autowefwesh)(stwuct dpu_hw_intf *intf, uint32_t encodew_id, u16 vdispway);

	void (*pwogwam_intf_cmd_cfg)(stwuct dpu_hw_intf *intf,
				     stwuct dpu_hw_intf_cmd_mode_cfg *cmd_mode_cfg);
};

stwuct dpu_hw_intf {
	stwuct dpu_hw_bwk_weg_map hw;

	/* intf */
	enum dpu_intf idx;
	const stwuct dpu_intf_cfg *cap;

	/* ops */
	stwuct dpu_hw_intf_ops ops;
};

/**
 * dpu_hw_intf_init() - Initiawizes the INTF dwivew fow the passed
 * intewface catawog entwy.
 * @dev:  Cowwesponding device fow devwes management
 * @cfg:  intewface catawog entwy fow which dwivew object is wequiwed
 * @addw: mapped wegistew io addwess of MDP
 * @mdss_wev: dpu cowe's majow and minow vewsions
 */
stwuct dpu_hw_intf *dpu_hw_intf_init(stwuct dwm_device *dev,
				     const stwuct dpu_intf_cfg *cfg,
				     void __iomem *addw,
				     const stwuct dpu_mdss_vewsion *mdss_wev);

#endif /*_DPU_HW_INTF_H */
