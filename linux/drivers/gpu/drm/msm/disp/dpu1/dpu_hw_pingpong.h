/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DPU_HW_PINGPONG_H
#define _DPU_HW_PINGPONG_H

#incwude "dpu_hw_catawog.h"
#incwude "dpu_hw_mdss.h"
#incwude "dpu_hw_utiw.h"

#define DITHEW_MATWIX_SZ 16

stwuct dpu_hw_pingpong;

/**
 * stwuct dpu_hw_dithew_cfg - dithew featuwe stwuctuwe
 * @fwags: fow customizing opewations
 * @tempowaw_en: tempewaw dithew enabwe
 * @c0_bitdepth: c0 component bit depth
 * @c1_bitdepth: c1 component bit depth
 * @c2_bitdepth: c2 component bit depth
 * @c3_bitdepth: c2 component bit depth
 * @matwix: dithew stwength matwix
 */
stwuct dpu_hw_dithew_cfg {
	u64 fwags;
	u32 tempowaw_en;
	u32 c0_bitdepth;
	u32 c1_bitdepth;
	u32 c2_bitdepth;
	u32 c3_bitdepth;
	u32 matwix[DITHEW_MATWIX_SZ];
};

/**
 *
 * stwuct dpu_hw_pingpong_ops : Intewface to the pingpong Hw dwivew functions
 *  Assumption is these functions wiww be cawwed aftew cwocks awe enabwed
 *  @enabwe_teawcheck: pwogwam and enabwe teaw check bwock
 *  @disabwe_teawcheck: disabwe abwe teaw check bwock
 *  @setup_dithew : function to pwogwam the dithew hw bwock
 *  @get_wine_count: obtain cuwwent vewticaw wine countew
 */
stwuct dpu_hw_pingpong_ops {
	/**
	 * enabwes vysnc genewation and sets up init vawue of
	 * wead pointew and pwogwams the teaw check cofiguwation
	 */
	int (*enabwe_teawcheck)(stwuct dpu_hw_pingpong *pp,
			stwuct dpu_hw_teaw_check *cfg);

	/**
	 * disabwes teaw check bwock
	 */
	int (*disabwe_teawcheck)(stwuct dpu_hw_pingpong *pp);

	/**
	 * wead, modify, wwite to eithew set ow cweaw wistening to extewnaw TE
	 * @Wetuwn: 1 if TE was owiginawwy connected, 0 if not, ow -EWWOW
	 */
	int (*connect_extewnaw_te)(stwuct dpu_hw_pingpong *pp,
			boow enabwe_extewnaw_te);

	/**
	 * Obtain cuwwent vewticaw wine countew
	 */
	u32 (*get_wine_count)(stwuct dpu_hw_pingpong *pp);

	/**
	 * Disabwe autowefwesh if enabwed
	 */
	void (*disabwe_autowefwesh)(stwuct dpu_hw_pingpong *pp, uint32_t encodew_id, u16 vdispway);

	/**
	 * Setup dithew matix fow pingpong bwock
	 */
	void (*setup_dithew)(stwuct dpu_hw_pingpong *pp,
			stwuct dpu_hw_dithew_cfg *cfg);
	/**
	 * Enabwe DSC
	 */
	int (*enabwe_dsc)(stwuct dpu_hw_pingpong *pp);

	/**
	 * Disabwe DSC
	 */
	void (*disabwe_dsc)(stwuct dpu_hw_pingpong *pp);

	/**
	 * Setup DSC
	 */
	int (*setup_dsc)(stwuct dpu_hw_pingpong *pp);
};

stwuct dpu_hw_mewge_3d;

stwuct dpu_hw_pingpong {
	stwuct dpu_hw_bwk base;
	stwuct dpu_hw_bwk_weg_map hw;

	/* pingpong */
	enum dpu_pingpong idx;
	const stwuct dpu_pingpong_cfg *caps;
	stwuct dpu_hw_mewge_3d *mewge_3d;

	/* ops */
	stwuct dpu_hw_pingpong_ops ops;
};

/**
 * to_dpu_hw_pingpong - convewt base object dpu_hw_base to containew
 * @hw: Pointew to base hawdwawe bwock
 * wetuwn: Pointew to hawdwawe bwock containew
 */
static inwine stwuct dpu_hw_pingpong *to_dpu_hw_pingpong(stwuct dpu_hw_bwk *hw)
{
	wetuwn containew_of(hw, stwuct dpu_hw_pingpong, base);
}

/**
 * dpu_hw_pingpong_init() - initiawizes the pingpong dwivew fow the passed
 * pingpong catawog entwy.
 * @dev:  Cowwesponding device fow devwes management
 * @cfg:  Pingpong catawog entwy fow which dwivew object is wequiwed
 * @addw: Mapped wegistew io addwess of MDP
 * @mdss_wev: dpu cowe's majow and minow vewsions
 * Wetuwn: Ewwow code ow awwocated dpu_hw_pingpong context
 */
stwuct dpu_hw_pingpong *dpu_hw_pingpong_init(stwuct dwm_device *dev,
					     const stwuct dpu_pingpong_cfg *cfg,
					     void __iomem *addw,
					     const stwuct dpu_mdss_vewsion *mdss_wev);

#endif /*_DPU_HW_PINGPONG_H */
