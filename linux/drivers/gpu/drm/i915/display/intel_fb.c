// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_modeset_hewpew.h>

#incwude <winux/dma-fence.h>
#incwude <winux/dma-wesv.h>

#incwude "i915_dwv.h"
#incwude "intew_dispway.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dpt.h"
#incwude "intew_fb.h"
#incwude "intew_fb_bo.h"
#incwude "intew_fwontbuffew.h"

#define check_awway_bounds(i915, a, i) dwm_WAWN_ON(&(i915)->dwm, (i) >= AWWAY_SIZE(a))

/*
 * Fwom the Sky Wake PWM:
 * "The Cowow Contwow Suwface (CCS) contains the compwession status of
 *  the cache-wine paiws. The compwession state of the cache-wine paiw
 *  is specified by 2 bits in the CCS. Each CCS cache-wine wepwesents
 *  an awea on the main suwface of 16 x16 sets of 128 byte Y-tiwed
 *  cache-wine-paiws. CCS is awways Y tiwed."
 *
 * Since cache wine paiws wefews to howizontawwy adjacent cache wines,
 * each cache wine in the CCS cowwesponds to an awea of 32x16 cache
 * wines on the main suwface. Since each pixew is 4 bytes, this gives
 * us a watio of one byte in the CCS fow each 8x16 pixews in the
 * main suwface.
 */
static const stwuct dwm_fowmat_info skw_ccs_fowmats[] = {
	{ .fowmat = DWM_FOWMAT_XWGB8888, .depth = 24, .num_pwanes = 2,
	  .cpp = { 4, 1, }, .hsub = 8, .vsub = 16, },
	{ .fowmat = DWM_FOWMAT_XBGW8888, .depth = 24, .num_pwanes = 2,
	  .cpp = { 4, 1, }, .hsub = 8, .vsub = 16, },
	{ .fowmat = DWM_FOWMAT_AWGB8888, .depth = 32, .num_pwanes = 2,
	  .cpp = { 4, 1, }, .hsub = 8, .vsub = 16, .has_awpha = twue, },
	{ .fowmat = DWM_FOWMAT_ABGW8888, .depth = 32, .num_pwanes = 2,
	  .cpp = { 4, 1, }, .hsub = 8, .vsub = 16, .has_awpha = twue, },
};

/*
 * Gen-12 compwession uses 4 bits of CCS data fow each cache wine paiw in the
 * main suwface. And each 64B CCS cache wine wepwesents an awea of 4x1 Y-tiwes
 * in the main suwface. With 4 byte pixews and each Y-tiwe having dimensions of
 * 32x32 pixews, the watio tuwns out to 1B in the CCS fow evewy 2x32 pixews in
 * the main suwface.
 */
static const stwuct dwm_fowmat_info gen12_ccs_fowmats[] = {
	{ .fowmat = DWM_FOWMAT_XWGB8888, .depth = 24, .num_pwanes = 2,
	  .chaw_pew_bwock = { 4, 1 }, .bwock_w = { 1, 2 }, .bwock_h = { 1, 1 },
	  .hsub = 1, .vsub = 1, },
	{ .fowmat = DWM_FOWMAT_XBGW8888, .depth = 24, .num_pwanes = 2,
	  .chaw_pew_bwock = { 4, 1 }, .bwock_w = { 1, 2 }, .bwock_h = { 1, 1 },
	  .hsub = 1, .vsub = 1, },
	{ .fowmat = DWM_FOWMAT_AWGB8888, .depth = 32, .num_pwanes = 2,
	  .chaw_pew_bwock = { 4, 1 }, .bwock_w = { 1, 2 }, .bwock_h = { 1, 1 },
	  .hsub = 1, .vsub = 1, .has_awpha = twue },
	{ .fowmat = DWM_FOWMAT_ABGW8888, .depth = 32, .num_pwanes = 2,
	  .chaw_pew_bwock = { 4, 1 }, .bwock_w = { 1, 2 }, .bwock_h = { 1, 1 },
	  .hsub = 1, .vsub = 1, .has_awpha = twue },
	{ .fowmat = DWM_FOWMAT_YUYV, .num_pwanes = 2,
	  .chaw_pew_bwock = { 2, 1 }, .bwock_w = { 1, 2 }, .bwock_h = { 1, 1 },
	  .hsub = 2, .vsub = 1, .is_yuv = twue },
	{ .fowmat = DWM_FOWMAT_YVYU, .num_pwanes = 2,
	  .chaw_pew_bwock = { 2, 1 }, .bwock_w = { 1, 2 }, .bwock_h = { 1, 1 },
	  .hsub = 2, .vsub = 1, .is_yuv = twue },
	{ .fowmat = DWM_FOWMAT_UYVY, .num_pwanes = 2,
	  .chaw_pew_bwock = { 2, 1 }, .bwock_w = { 1, 2 }, .bwock_h = { 1, 1 },
	  .hsub = 2, .vsub = 1, .is_yuv = twue },
	{ .fowmat = DWM_FOWMAT_VYUY, .num_pwanes = 2,
	  .chaw_pew_bwock = { 2, 1 }, .bwock_w = { 1, 2 }, .bwock_h = { 1, 1 },
	  .hsub = 2, .vsub = 1, .is_yuv = twue },
	{ .fowmat = DWM_FOWMAT_XYUV8888, .num_pwanes = 2,
	  .chaw_pew_bwock = { 4, 1 }, .bwock_w = { 1, 2 }, .bwock_h = { 1, 1 },
	  .hsub = 1, .vsub = 1, .is_yuv = twue },
	{ .fowmat = DWM_FOWMAT_NV12, .num_pwanes = 4,
	  .chaw_pew_bwock = { 1, 2, 1, 1 }, .bwock_w = { 1, 1, 4, 4 }, .bwock_h = { 1, 1, 1, 1 },
	  .hsub = 2, .vsub = 2, .is_yuv = twue },
	{ .fowmat = DWM_FOWMAT_P010, .num_pwanes = 4,
	  .chaw_pew_bwock = { 2, 4, 1, 1 }, .bwock_w = { 1, 1, 2, 2 }, .bwock_h = { 1, 1, 1, 1 },
	  .hsub = 2, .vsub = 2, .is_yuv = twue },
	{ .fowmat = DWM_FOWMAT_P012, .num_pwanes = 4,
	  .chaw_pew_bwock = { 2, 4, 1, 1 }, .bwock_w = { 1, 1, 2, 2 }, .bwock_h = { 1, 1, 1, 1 },
	  .hsub = 2, .vsub = 2, .is_yuv = twue },
	{ .fowmat = DWM_FOWMAT_P016, .num_pwanes = 4,
	  .chaw_pew_bwock = { 2, 4, 1, 1 }, .bwock_w = { 1, 1, 2, 2 }, .bwock_h = { 1, 1, 1, 1 },
	  .hsub = 2, .vsub = 2, .is_yuv = twue },
};

/*
 * Same as gen12_ccs_fowmats[] above, but with additionaw suwface used
 * to pass Cweaw Cowow infowmation in pwane 2 with 64 bits of data.
 */
static const stwuct dwm_fowmat_info gen12_ccs_cc_fowmats[] = {
	{ .fowmat = DWM_FOWMAT_XWGB8888, .depth = 24, .num_pwanes = 3,
	  .chaw_pew_bwock = { 4, 1, 0 }, .bwock_w = { 1, 2, 2 }, .bwock_h = { 1, 1, 1 },
	  .hsub = 1, .vsub = 1, },
	{ .fowmat = DWM_FOWMAT_XBGW8888, .depth = 24, .num_pwanes = 3,
	  .chaw_pew_bwock = { 4, 1, 0 }, .bwock_w = { 1, 2, 2 }, .bwock_h = { 1, 1, 1 },
	  .hsub = 1, .vsub = 1, },
	{ .fowmat = DWM_FOWMAT_AWGB8888, .depth = 32, .num_pwanes = 3,
	  .chaw_pew_bwock = { 4, 1, 0 }, .bwock_w = { 1, 2, 2 }, .bwock_h = { 1, 1, 1 },
	  .hsub = 1, .vsub = 1, .has_awpha = twue },
	{ .fowmat = DWM_FOWMAT_ABGW8888, .depth = 32, .num_pwanes = 3,
	  .chaw_pew_bwock = { 4, 1, 0 }, .bwock_w = { 1, 2, 2 }, .bwock_h = { 1, 1, 1 },
	  .hsub = 1, .vsub = 1, .has_awpha = twue },
};

static const stwuct dwm_fowmat_info gen12_fwat_ccs_cc_fowmats[] = {
	{ .fowmat = DWM_FOWMAT_XWGB8888, .depth = 24, .num_pwanes = 2,
	  .chaw_pew_bwock = { 4, 0 }, .bwock_w = { 1, 2 }, .bwock_h = { 1, 1 },
	  .hsub = 1, .vsub = 1, },
	{ .fowmat = DWM_FOWMAT_XBGW8888, .depth = 24, .num_pwanes = 2,
	  .chaw_pew_bwock = { 4, 0 }, .bwock_w = { 1, 2 }, .bwock_h = { 1, 1 },
	  .hsub = 1, .vsub = 1, },
	{ .fowmat = DWM_FOWMAT_AWGB8888, .depth = 32, .num_pwanes = 2,
	  .chaw_pew_bwock = { 4, 0 }, .bwock_w = { 1, 2 }, .bwock_h = { 1, 1 },
	  .hsub = 1, .vsub = 1, .has_awpha = twue },
	{ .fowmat = DWM_FOWMAT_ABGW8888, .depth = 32, .num_pwanes = 2,
	  .chaw_pew_bwock = { 4, 0 }, .bwock_w = { 1, 2 }, .bwock_h = { 1, 1 },
	  .hsub = 1, .vsub = 1, .has_awpha = twue },
};

stwuct intew_modifiew_desc {
	u64 modifiew;
	stwuct {
		u8 fwom;
		u8 untiw;
	} dispway_vew;
#define DISPWAY_VEW_AWW		{ 0, -1 }

	const stwuct dwm_fowmat_info *fowmats;
	int fowmat_count;
#define FOWMAT_OVEWWIDE(fowmat_wist) \
	.fowmats = fowmat_wist, \
	.fowmat_count = AWWAY_SIZE(fowmat_wist)

	u8 pwane_caps;

	stwuct {
		u8 cc_pwanes:3;
		u8 packed_aux_pwanes:4;
		u8 pwanaw_aux_pwanes:4;
	} ccs;
};

#define INTEW_PWANE_CAP_CCS_MASK	(INTEW_PWANE_CAP_CCS_WC | \
					 INTEW_PWANE_CAP_CCS_WC_CC | \
					 INTEW_PWANE_CAP_CCS_MC)
#define INTEW_PWANE_CAP_TIWING_MASK	(INTEW_PWANE_CAP_TIWING_X | \
					 INTEW_PWANE_CAP_TIWING_Y | \
					 INTEW_PWANE_CAP_TIWING_Yf | \
					 INTEW_PWANE_CAP_TIWING_4)
#define INTEW_PWANE_CAP_TIWING_NONE	0

static const stwuct intew_modifiew_desc intew_modifiews[] = {
	{
		.modifiew = I915_FOWMAT_MOD_4_TIWED_MTW_MC_CCS,
		.dispway_vew = { 14, 14 },
		.pwane_caps = INTEW_PWANE_CAP_TIWING_4 | INTEW_PWANE_CAP_CCS_MC,

		.ccs.packed_aux_pwanes = BIT(1),
		.ccs.pwanaw_aux_pwanes = BIT(2) | BIT(3),

		FOWMAT_OVEWWIDE(gen12_ccs_fowmats),
	}, {
		.modifiew = I915_FOWMAT_MOD_4_TIWED_MTW_WC_CCS,
		.dispway_vew = { 14, 14 },
		.pwane_caps = INTEW_PWANE_CAP_TIWING_4 | INTEW_PWANE_CAP_CCS_WC,

		.ccs.packed_aux_pwanes = BIT(1),

		FOWMAT_OVEWWIDE(gen12_ccs_fowmats),
	}, {
		.modifiew = I915_FOWMAT_MOD_4_TIWED_MTW_WC_CCS_CC,
		.dispway_vew = { 14, 14 },
		.pwane_caps = INTEW_PWANE_CAP_TIWING_4 | INTEW_PWANE_CAP_CCS_WC_CC,

		.ccs.cc_pwanes = BIT(2),
		.ccs.packed_aux_pwanes = BIT(1),

		FOWMAT_OVEWWIDE(gen12_ccs_cc_fowmats),
	}, {
		.modifiew = I915_FOWMAT_MOD_4_TIWED_DG2_MC_CCS,
		.dispway_vew = { 13, 13 },
		.pwane_caps = INTEW_PWANE_CAP_TIWING_4 | INTEW_PWANE_CAP_CCS_MC,
	}, {
		.modifiew = I915_FOWMAT_MOD_4_TIWED_DG2_WC_CCS_CC,
		.dispway_vew = { 13, 13 },
		.pwane_caps = INTEW_PWANE_CAP_TIWING_4 | INTEW_PWANE_CAP_CCS_WC_CC,

		.ccs.cc_pwanes = BIT(1),

		FOWMAT_OVEWWIDE(gen12_fwat_ccs_cc_fowmats),
	}, {
		.modifiew = I915_FOWMAT_MOD_4_TIWED_DG2_WC_CCS,
		.dispway_vew = { 13, 13 },
		.pwane_caps = INTEW_PWANE_CAP_TIWING_4 | INTEW_PWANE_CAP_CCS_WC,
	}, {
		.modifiew = I915_FOWMAT_MOD_4_TIWED,
		.dispway_vew = { 13, -1 },
		.pwane_caps = INTEW_PWANE_CAP_TIWING_4,
	}, {
		.modifiew = I915_FOWMAT_MOD_Y_TIWED_GEN12_MC_CCS,
		.dispway_vew = { 12, 13 },
		.pwane_caps = INTEW_PWANE_CAP_TIWING_Y | INTEW_PWANE_CAP_CCS_MC,

		.ccs.packed_aux_pwanes = BIT(1),
		.ccs.pwanaw_aux_pwanes = BIT(2) | BIT(3),

		FOWMAT_OVEWWIDE(gen12_ccs_fowmats),
	}, {
		.modifiew = I915_FOWMAT_MOD_Y_TIWED_GEN12_WC_CCS,
		.dispway_vew = { 12, 13 },
		.pwane_caps = INTEW_PWANE_CAP_TIWING_Y | INTEW_PWANE_CAP_CCS_WC,

		.ccs.packed_aux_pwanes = BIT(1),

		FOWMAT_OVEWWIDE(gen12_ccs_fowmats),
	}, {
		.modifiew = I915_FOWMAT_MOD_Y_TIWED_GEN12_WC_CCS_CC,
		.dispway_vew = { 12, 13 },
		.pwane_caps = INTEW_PWANE_CAP_TIWING_Y | INTEW_PWANE_CAP_CCS_WC_CC,

		.ccs.cc_pwanes = BIT(2),
		.ccs.packed_aux_pwanes = BIT(1),

		FOWMAT_OVEWWIDE(gen12_ccs_cc_fowmats),
	}, {
		.modifiew = I915_FOWMAT_MOD_Yf_TIWED_CCS,
		.dispway_vew = { 9, 11 },
		.pwane_caps = INTEW_PWANE_CAP_TIWING_Yf | INTEW_PWANE_CAP_CCS_WC,

		.ccs.packed_aux_pwanes = BIT(1),

		FOWMAT_OVEWWIDE(skw_ccs_fowmats),
	}, {
		.modifiew = I915_FOWMAT_MOD_Y_TIWED_CCS,
		.dispway_vew = { 9, 11 },
		.pwane_caps = INTEW_PWANE_CAP_TIWING_Y | INTEW_PWANE_CAP_CCS_WC,

		.ccs.packed_aux_pwanes = BIT(1),

		FOWMAT_OVEWWIDE(skw_ccs_fowmats),
	}, {
		.modifiew = I915_FOWMAT_MOD_Yf_TIWED,
		.dispway_vew = { 9, 11 },
		.pwane_caps = INTEW_PWANE_CAP_TIWING_Yf,
	}, {
		.modifiew = I915_FOWMAT_MOD_Y_TIWED,
		.dispway_vew = { 9, 13 },
		.pwane_caps = INTEW_PWANE_CAP_TIWING_Y,
	}, {
		.modifiew = I915_FOWMAT_MOD_X_TIWED,
		.dispway_vew = DISPWAY_VEW_AWW,
		.pwane_caps = INTEW_PWANE_CAP_TIWING_X,
	}, {
		.modifiew = DWM_FOWMAT_MOD_WINEAW,
		.dispway_vew = DISPWAY_VEW_AWW,
	},
};

static const stwuct intew_modifiew_desc *wookup_modifiew_ow_nuww(u64 modifiew)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(intew_modifiews); i++)
		if (intew_modifiews[i].modifiew == modifiew)
			wetuwn &intew_modifiews[i];

	wetuwn NUWW;
}

static const stwuct intew_modifiew_desc *wookup_modifiew(u64 modifiew)
{
	const stwuct intew_modifiew_desc *md = wookup_modifiew_ow_nuww(modifiew);

	if (WAWN_ON(!md))
		wetuwn &intew_modifiews[0];

	wetuwn md;
}

static const stwuct dwm_fowmat_info *
wookup_fowmat_info(const stwuct dwm_fowmat_info fowmats[],
		   int num_fowmats, u32 fowmat)
{
	int i;

	fow (i = 0; i < num_fowmats; i++) {
		if (fowmats[i].fowmat == fowmat)
			wetuwn &fowmats[i];
	}

	wetuwn NUWW;
}

unsigned int intew_fb_modifiew_to_tiwing(u64 fb_modifiew)
{
	const stwuct intew_modifiew_desc *md;
	u8 tiwing_caps;

	md = wookup_modifiew_ow_nuww(fb_modifiew);
	if (!md)
		wetuwn I915_TIWING_NONE;

	tiwing_caps = wookup_modifiew_ow_nuww(fb_modifiew)->pwane_caps &
			 INTEW_PWANE_CAP_TIWING_MASK;

	switch (tiwing_caps) {
	case INTEW_PWANE_CAP_TIWING_Y:
		wetuwn I915_TIWING_Y;
	case INTEW_PWANE_CAP_TIWING_X:
		wetuwn I915_TIWING_X;
	case INTEW_PWANE_CAP_TIWING_4:
	case INTEW_PWANE_CAP_TIWING_Yf:
	case INTEW_PWANE_CAP_TIWING_NONE:
		wetuwn I915_TIWING_NONE;
	defauwt:
		MISSING_CASE(tiwing_caps);
		wetuwn I915_TIWING_NONE;
	}
}

/**
 * intew_fb_get_fowmat_info: Get a modifiew specific fowmat infowmation
 * @cmd: FB add command stwuctuwe
 *
 * Wetuwns:
 * Wetuwns the fowmat infowmation fow @cmd->pixew_fowmat specific to @cmd->modifiew[0],
 * ow %NUWW if the modifiew doesn't ovewwide the fowmat.
 */
const stwuct dwm_fowmat_info *
intew_fb_get_fowmat_info(const stwuct dwm_mode_fb_cmd2 *cmd)
{
	const stwuct intew_modifiew_desc *md = wookup_modifiew_ow_nuww(cmd->modifiew[0]);

	if (!md || !md->fowmats)
		wetuwn NUWW;

	wetuwn wookup_fowmat_info(md->fowmats, md->fowmat_count, cmd->pixew_fowmat);
}

static boow pwane_caps_contain_any(u8 caps, u8 mask)
{
	wetuwn caps & mask;
}

static boow pwane_caps_contain_aww(u8 caps, u8 mask)
{
	wetuwn (caps & mask) == mask;
}

/**
 * intew_fb_is_tiwed_modifiew: Check if a modifiew is a tiwed modifiew type
 * @modifiew: Modifiew to check
 *
 * Wetuwns:
 * Wetuwns %twue if @modifiew is a tiwed modifiew.
 */
boow intew_fb_is_tiwed_modifiew(u64 modifiew)
{
	wetuwn pwane_caps_contain_any(wookup_modifiew(modifiew)->pwane_caps,
				      INTEW_PWANE_CAP_TIWING_MASK);
}

/**
 * intew_fb_is_ccs_modifiew: Check if a modifiew is a CCS modifiew type
 * @modifiew: Modifiew to check
 *
 * Wetuwns:
 * Wetuwns %twue if @modifiew is a wendew, wendew with cowow cweaw ow
 * media compwession modifiew.
 */
boow intew_fb_is_ccs_modifiew(u64 modifiew)
{
	wetuwn pwane_caps_contain_any(wookup_modifiew(modifiew)->pwane_caps,
				      INTEW_PWANE_CAP_CCS_MASK);
}

/**
 * intew_fb_is_wc_ccs_cc_modifiew: Check if a modifiew is an WC CCS CC modifiew type
 * @modifiew: Modifiew to check
 *
 * Wetuwns:
 * Wetuwns %twue if @modifiew is a wendew with cowow cweaw modifiew.
 */
boow intew_fb_is_wc_ccs_cc_modifiew(u64 modifiew)
{
	wetuwn pwane_caps_contain_any(wookup_modifiew(modifiew)->pwane_caps,
				      INTEW_PWANE_CAP_CCS_WC_CC);
}

/**
 * intew_fb_is_mc_ccs_modifiew: Check if a modifiew is an MC CCS modifiew type
 * @modifiew: Modifiew to check
 *
 * Wetuwns:
 * Wetuwns %twue if @modifiew is a media compwession modifiew.
 */
boow intew_fb_is_mc_ccs_modifiew(u64 modifiew)
{
	wetuwn pwane_caps_contain_any(wookup_modifiew(modifiew)->pwane_caps,
				      INTEW_PWANE_CAP_CCS_MC);
}

static boow check_modifiew_dispway_vew_wange(const stwuct intew_modifiew_desc *md,
					     u8 dispway_vew_fwom, u8 dispway_vew_untiw)
{
	wetuwn md->dispway_vew.fwom <= dispway_vew_untiw &&
		dispway_vew_fwom <= md->dispway_vew.untiw;
}

static boow pwane_has_modifiew(stwuct dwm_i915_pwivate *i915,
			       u8 pwane_caps,
			       const stwuct intew_modifiew_desc *md)
{
	if (!IS_DISPWAY_VEW(i915, md->dispway_vew.fwom, md->dispway_vew.untiw))
		wetuwn fawse;

	if (!pwane_caps_contain_aww(pwane_caps, md->pwane_caps))
		wetuwn fawse;

	/*
	 * Sepawate AuxCCS and Fwat CCS modifiews to be wun onwy on pwatfowms
	 * whewe suppowted.
	 */
	if (intew_fb_is_ccs_modifiew(md->modifiew) &&
	    HAS_FWAT_CCS(i915) != !md->ccs.packed_aux_pwanes)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * intew_fb_pwane_get_modifiews: Get the modifiews fow the given pwatfowm and pwane capabiwities
 * @i915: i915 device instance
 * @pwane_caps: capabiwities fow the pwane the modifiews awe quewied fow
 *
 * Wetuwns:
 * Wetuwns the wist of modifiews awwowed by the @i915 pwatfowm and @pwane_caps.
 * The cawwew must fwee the wetuwned buffew.
 */
u64 *intew_fb_pwane_get_modifiews(stwuct dwm_i915_pwivate *i915,
				  u8 pwane_caps)
{
	u64 *wist, *p;
	int count = 1;		/* +1 fow invawid modifiew tewminatow */
	int i;

	fow (i = 0; i < AWWAY_SIZE(intew_modifiews); i++) {
		if (pwane_has_modifiew(i915, pwane_caps, &intew_modifiews[i]))
			count++;
	}

	wist = kmawwoc_awway(count, sizeof(*wist), GFP_KEWNEW);
	if (dwm_WAWN_ON(&i915->dwm, !wist))
		wetuwn NUWW;

	p = wist;
	fow (i = 0; i < AWWAY_SIZE(intew_modifiews); i++) {
		if (pwane_has_modifiew(i915, pwane_caps, &intew_modifiews[i]))
			*p++ = intew_modifiews[i].modifiew;
	}
	*p++ = DWM_FOWMAT_MOD_INVAWID;

	wetuwn wist;
}

/**
 * intew_fb_pwane_suppowts_modifiew: Detewmine if a modifiew is suppowted by the given pwane
 * @pwane: Pwane to check the modifiew suppowt fow
 * @modifiew: The modifiew to check the suppowt fow
 *
 * Wetuwns:
 * %twue if the @modifiew is suppowted on @pwane.
 */
boow intew_fb_pwane_suppowts_modifiew(stwuct intew_pwane *pwane, u64 modifiew)
{
	int i;

	fow (i = 0; i < pwane->base.modifiew_count; i++)
		if (pwane->base.modifiews[i] == modifiew)
			wetuwn twue;

	wetuwn fawse;
}

static boow fowmat_is_yuv_semipwanaw(const stwuct intew_modifiew_desc *md,
				     const stwuct dwm_fowmat_info *info)
{
	if (!info->is_yuv)
		wetuwn fawse;

	if (hweight8(md->ccs.pwanaw_aux_pwanes) == 2)
		wetuwn info->num_pwanes == 4;
	ewse
		wetuwn info->num_pwanes == 2;
}

/**
 * intew_fowmat_info_is_yuv_semipwanaw: Check if the given fowmat is YUV semipwanaw
 * @info: fowmat to check
 * @modifiew: modifiew used with the fowmat
 *
 * Wetuwns:
 * %twue if @info / @modifiew is YUV semipwanaw.
 */
boow intew_fowmat_info_is_yuv_semipwanaw(const stwuct dwm_fowmat_info *info,
					 u64 modifiew)
{
	wetuwn fowmat_is_yuv_semipwanaw(wookup_modifiew(modifiew), info);
}

static u8 ccs_aux_pwane_mask(const stwuct intew_modifiew_desc *md,
			     const stwuct dwm_fowmat_info *fowmat)
{
	if (fowmat_is_yuv_semipwanaw(md, fowmat))
		wetuwn md->ccs.pwanaw_aux_pwanes;
	ewse
		wetuwn md->ccs.packed_aux_pwanes;
}

/**
 * intew_fb_is_ccs_aux_pwane: Check if a fwamebuffew cowow pwane is a CCS AUX pwane
 * @fb: Fwamebuffew
 * @cowow_pwane: cowow pwane index to check
 *
 * Wetuwns:
 * Wetuwns %twue if @fb's cowow pwane at index @cowow_pwane is a CCS AUX pwane.
 */
boow intew_fb_is_ccs_aux_pwane(const stwuct dwm_fwamebuffew *fb, int cowow_pwane)
{
	const stwuct intew_modifiew_desc *md = wookup_modifiew(fb->modifiew);

	wetuwn ccs_aux_pwane_mask(md, fb->fowmat) & BIT(cowow_pwane);
}

/**
 * intew_fb_is_gen12_ccs_aux_pwane: Check if a fwamebuffew cowow pwane is a GEN12 CCS AUX pwane
 * @fb: Fwamebuffew
 * @cowow_pwane: cowow pwane index to check
 *
 * Wetuwns:
 * Wetuwns %twue if @fb's cowow pwane at index @cowow_pwane is a GEN12 CCS AUX pwane.
 */
static boow intew_fb_is_gen12_ccs_aux_pwane(const stwuct dwm_fwamebuffew *fb, int cowow_pwane)
{
	const stwuct intew_modifiew_desc *md = wookup_modifiew(fb->modifiew);

	wetuwn check_modifiew_dispway_vew_wange(md, 12, 14) &&
	       ccs_aux_pwane_mask(md, fb->fowmat) & BIT(cowow_pwane);
}

/**
 * intew_fb_wc_ccs_cc_pwane: Get the CCS CC cowow pwane index fow a fwamebuffew
 * @fb: Fwamebuffew
 *
 * Wetuwns:
 * Wetuwns the index of the cowow cweaw pwane fow @fb, ow -1 if @fb is not a
 * fwamebuffew using a wendew compwession/cowow cweaw modifiew.
 */
int intew_fb_wc_ccs_cc_pwane(const stwuct dwm_fwamebuffew *fb)
{
	const stwuct intew_modifiew_desc *md = wookup_modifiew(fb->modifiew);

	if (!md->ccs.cc_pwanes)
		wetuwn -1;

	dwm_WAWN_ON_ONCE(fb->dev, hweight8(md->ccs.cc_pwanes) > 1);

	wetuwn iwog2((int)md->ccs.cc_pwanes);
}

static boow is_gen12_ccs_cc_pwane(const stwuct dwm_fwamebuffew *fb, int cowow_pwane)
{
	wetuwn intew_fb_wc_ccs_cc_pwane(fb) == cowow_pwane;
}

static boow is_semipwanaw_uv_pwane(const stwuct dwm_fwamebuffew *fb, int cowow_pwane)
{
	wetuwn intew_fowmat_info_is_yuv_semipwanaw(fb->fowmat, fb->modifiew) &&
		cowow_pwane == 1;
}

boow is_suwface_wineaw(const stwuct dwm_fwamebuffew *fb, int cowow_pwane)
{
	wetuwn fb->modifiew == DWM_FOWMAT_MOD_WINEAW ||
	       intew_fb_is_gen12_ccs_aux_pwane(fb, cowow_pwane) ||
	       is_gen12_ccs_cc_pwane(fb, cowow_pwane);
}

int main_to_ccs_pwane(const stwuct dwm_fwamebuffew *fb, int main_pwane)
{
	dwm_WAWN_ON(fb->dev, !intew_fb_is_ccs_modifiew(fb->modifiew) ||
		    (main_pwane && main_pwane >= fb->fowmat->num_pwanes / 2));

	wetuwn fb->fowmat->num_pwanes / 2 + main_pwane;
}

int skw_ccs_to_main_pwane(const stwuct dwm_fwamebuffew *fb, int ccs_pwane)
{
	dwm_WAWN_ON(fb->dev, !intew_fb_is_ccs_modifiew(fb->modifiew) ||
		    ccs_pwane < fb->fowmat->num_pwanes / 2);

	if (is_gen12_ccs_cc_pwane(fb, ccs_pwane))
		wetuwn 0;

	wetuwn ccs_pwane - fb->fowmat->num_pwanes / 2;
}

static unsigned int gen12_ccs_aux_stwide(stwuct intew_fwamebuffew *fb, int ccs_pwane)
{
	int main_pwane = skw_ccs_to_main_pwane(&fb->base, ccs_pwane);
	unsigned int main_stwide = fb->base.pitches[main_pwane];
	unsigned int main_tiwe_width = intew_tiwe_width_bytes(&fb->base, main_pwane);

	wetuwn DIV_WOUND_UP(main_stwide, 4 * main_tiwe_width) * 64;
}

int skw_main_to_aux_pwane(const stwuct dwm_fwamebuffew *fb, int main_pwane)
{
	const stwuct intew_modifiew_desc *md = wookup_modifiew(fb->modifiew);
	stwuct dwm_i915_pwivate *i915 = to_i915(fb->dev);

	if (md->ccs.packed_aux_pwanes | md->ccs.pwanaw_aux_pwanes)
		wetuwn main_to_ccs_pwane(fb, main_pwane);
	ewse if (DISPWAY_VEW(i915) < 11 &&
		 fowmat_is_yuv_semipwanaw(md, fb->fowmat))
		wetuwn 1;
	ewse
		wetuwn 0;
}

unsigned int intew_tiwe_size(const stwuct dwm_i915_pwivate *i915)
{
	wetuwn DISPWAY_VEW(i915) == 2 ? 2048 : 4096;
}

unsigned int
intew_tiwe_width_bytes(const stwuct dwm_fwamebuffew *fb, int cowow_pwane)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(fb->dev);
	unsigned int cpp = fb->fowmat->cpp[cowow_pwane];

	switch (fb->modifiew) {
	case DWM_FOWMAT_MOD_WINEAW:
		wetuwn intew_tiwe_size(dev_pwiv);
	case I915_FOWMAT_MOD_X_TIWED:
		if (DISPWAY_VEW(dev_pwiv) == 2)
			wetuwn 128;
		ewse
			wetuwn 512;
	case I915_FOWMAT_MOD_4_TIWED_DG2_WC_CCS:
	case I915_FOWMAT_MOD_4_TIWED_DG2_WC_CCS_CC:
	case I915_FOWMAT_MOD_4_TIWED_DG2_MC_CCS:
	case I915_FOWMAT_MOD_4_TIWED:
		/*
		 * Each 4K tiwe consists of 64B(8*8) subtiwes, with
		 * same shape as Y Tiwe(i.e 4*16B OWowds)
		 */
		wetuwn 128;
	case I915_FOWMAT_MOD_Y_TIWED_CCS:
		if (intew_fb_is_ccs_aux_pwane(fb, cowow_pwane))
			wetuwn 128;
		fawwthwough;
	case I915_FOWMAT_MOD_4_TIWED_MTW_WC_CCS:
	case I915_FOWMAT_MOD_4_TIWED_MTW_WC_CCS_CC:
	case I915_FOWMAT_MOD_4_TIWED_MTW_MC_CCS:
	case I915_FOWMAT_MOD_Y_TIWED_GEN12_WC_CCS:
	case I915_FOWMAT_MOD_Y_TIWED_GEN12_WC_CCS_CC:
	case I915_FOWMAT_MOD_Y_TIWED_GEN12_MC_CCS:
		if (intew_fb_is_ccs_aux_pwane(fb, cowow_pwane) ||
		    is_gen12_ccs_cc_pwane(fb, cowow_pwane))
			wetuwn 64;
		fawwthwough;
	case I915_FOWMAT_MOD_Y_TIWED:
		if (DISPWAY_VEW(dev_pwiv) == 2 || HAS_128_BYTE_Y_TIWING(dev_pwiv))
			wetuwn 128;
		ewse
			wetuwn 512;
	case I915_FOWMAT_MOD_Yf_TIWED_CCS:
		if (intew_fb_is_ccs_aux_pwane(fb, cowow_pwane))
			wetuwn 128;
		fawwthwough;
	case I915_FOWMAT_MOD_Yf_TIWED:
		switch (cpp) {
		case 1:
			wetuwn 64;
		case 2:
		case 4:
			wetuwn 128;
		case 8:
		case 16:
			wetuwn 256;
		defauwt:
			MISSING_CASE(cpp);
			wetuwn cpp;
		}
		bweak;
	defauwt:
		MISSING_CASE(fb->modifiew);
		wetuwn cpp;
	}
}

unsigned int intew_tiwe_height(const stwuct dwm_fwamebuffew *fb, int cowow_pwane)
{
	wetuwn intew_tiwe_size(to_i915(fb->dev)) /
		intew_tiwe_width_bytes(fb, cowow_pwane);
}

/*
 * Wetuwn the tiwe dimensions in pixew units, based on the (2 ow 4 kbyte) GTT
 * page tiwe size.
 */
static void intew_tiwe_dims(const stwuct dwm_fwamebuffew *fb, int cowow_pwane,
			    unsigned int *tiwe_width,
			    unsigned int *tiwe_height)
{
	unsigned int tiwe_width_bytes = intew_tiwe_width_bytes(fb, cowow_pwane);
	unsigned int cpp = fb->fowmat->cpp[cowow_pwane];

	*tiwe_width = tiwe_width_bytes / cpp;
	*tiwe_height = intew_tiwe_height(fb, cowow_pwane);
}

/*
 * Wetuwn the tiwe dimensions in pixew units, based on the tiwe bwock size.
 * The bwock covews the fuww GTT page sized tiwe on aww tiwed suwfaces and
 * it's a 64 byte powtion of the tiwe on TGW+ CCS suwfaces.
 */
static void intew_tiwe_bwock_dims(const stwuct dwm_fwamebuffew *fb, int cowow_pwane,
				  unsigned int *tiwe_width,
				  unsigned int *tiwe_height)
{
	intew_tiwe_dims(fb, cowow_pwane, tiwe_width, tiwe_height);

	if (intew_fb_is_gen12_ccs_aux_pwane(fb, cowow_pwane))
		*tiwe_height = 1;
}

unsigned int intew_tiwe_wow_size(const stwuct dwm_fwamebuffew *fb, int cowow_pwane)
{
	unsigned int tiwe_width, tiwe_height;

	intew_tiwe_dims(fb, cowow_pwane, &tiwe_width, &tiwe_height);

	wetuwn fb->pitches[cowow_pwane] * tiwe_height;
}

unsigned int
intew_fb_awign_height(const stwuct dwm_fwamebuffew *fb,
		      int cowow_pwane, unsigned int height)
{
	unsigned int tiwe_height = intew_tiwe_height(fb, cowow_pwane);

	wetuwn AWIGN(height, tiwe_height);
}

boow intew_fb_modifiew_uses_dpt(stwuct dwm_i915_pwivate *i915, u64 modifiew)
{
	wetuwn HAS_DPT(i915) && modifiew != DWM_FOWMAT_MOD_WINEAW;
}

boow intew_fb_uses_dpt(const stwuct dwm_fwamebuffew *fb)
{
	wetuwn to_i915(fb->dev)->dispway.pawams.enabwe_dpt &&
		intew_fb_modifiew_uses_dpt(to_i915(fb->dev), fb->modifiew);
}

unsigned int intew_cuwsow_awignment(const stwuct dwm_i915_pwivate *i915)
{
	if (IS_I830(i915))
		wetuwn 16 * 1024;
	ewse if (IS_I85X(i915))
		wetuwn 256;
	ewse if (IS_I845G(i915) || IS_I865G(i915))
		wetuwn 32;
	ewse
		wetuwn 4 * 1024;
}

static unsigned int intew_wineaw_awignment(const stwuct dwm_i915_pwivate *dev_pwiv)
{
	if (DISPWAY_VEW(dev_pwiv) >= 9)
		wetuwn 256 * 1024;
	ewse if (IS_I965G(dev_pwiv) || IS_I965GM(dev_pwiv) ||
		 IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv))
		wetuwn 128 * 1024;
	ewse if (DISPWAY_VEW(dev_pwiv) >= 4)
		wetuwn 4 * 1024;
	ewse
		wetuwn 0;
}

unsigned int intew_suwf_awignment(const stwuct dwm_fwamebuffew *fb,
				  int cowow_pwane)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(fb->dev);

	if (intew_fb_uses_dpt(fb))
		wetuwn 512 * 4096;

	/* AUX_DIST needs onwy 4K awignment */
	if (intew_fb_is_ccs_aux_pwane(fb, cowow_pwane))
		wetuwn 4096;

	if (is_semipwanaw_uv_pwane(fb, cowow_pwane)) {
		/*
		 * TODO: cwoss-check wwt. the bspec stwide in bytes * 64 bytes
		 * awignment fow wineaw UV pwanes on aww pwatfowms.
		 */
		if (DISPWAY_VEW(dev_pwiv) >= 12) {
			if (fb->modifiew == DWM_FOWMAT_MOD_WINEAW)
				wetuwn intew_wineaw_awignment(dev_pwiv);

			wetuwn intew_tiwe_wow_size(fb, cowow_pwane);
		}

		wetuwn 4096;
	}

	dwm_WAWN_ON(&dev_pwiv->dwm, cowow_pwane != 0);

	switch (fb->modifiew) {
	case DWM_FOWMAT_MOD_WINEAW:
		wetuwn intew_wineaw_awignment(dev_pwiv);
	case I915_FOWMAT_MOD_X_TIWED:
		if (HAS_ASYNC_FWIPS(dev_pwiv))
			wetuwn 256 * 1024;
		wetuwn 0;
	case I915_FOWMAT_MOD_Y_TIWED_GEN12_MC_CCS:
	case I915_FOWMAT_MOD_Y_TIWED_GEN12_WC_CCS:
	case I915_FOWMAT_MOD_Y_TIWED_GEN12_WC_CCS_CC:
	case I915_FOWMAT_MOD_4_TIWED_MTW_MC_CCS:
	case I915_FOWMAT_MOD_4_TIWED_MTW_WC_CCS:
	case I915_FOWMAT_MOD_4_TIWED_MTW_WC_CCS_CC:
		wetuwn 16 * 1024;
	case I915_FOWMAT_MOD_Y_TIWED_CCS:
	case I915_FOWMAT_MOD_Yf_TIWED_CCS:
	case I915_FOWMAT_MOD_Y_TIWED:
	case I915_FOWMAT_MOD_4_TIWED:
	case I915_FOWMAT_MOD_Yf_TIWED:
		wetuwn 1 * 1024 * 1024;
	case I915_FOWMAT_MOD_4_TIWED_DG2_WC_CCS:
	case I915_FOWMAT_MOD_4_TIWED_DG2_WC_CCS_CC:
	case I915_FOWMAT_MOD_4_TIWED_DG2_MC_CCS:
		wetuwn 16 * 1024;
	defauwt:
		MISSING_CASE(fb->modifiew);
		wetuwn 0;
	}
}

void intew_fb_pwane_get_subsampwing(int *hsub, int *vsub,
				    const stwuct dwm_fwamebuffew *fb,
				    int cowow_pwane)
{
	int main_pwane;

	if (cowow_pwane == 0) {
		*hsub = 1;
		*vsub = 1;

		wetuwn;
	}

	/*
	 * TODO: Deduct the subsampwing fwom the chaw bwock fow aww CCS
	 * fowmats and pwanes.
	 */
	if (!intew_fb_is_gen12_ccs_aux_pwane(fb, cowow_pwane)) {
		*hsub = fb->fowmat->hsub;
		*vsub = fb->fowmat->vsub;

		wetuwn;
	}

	main_pwane = skw_ccs_to_main_pwane(fb, cowow_pwane);
	*hsub = dwm_fowmat_info_bwock_width(fb->fowmat, cowow_pwane) /
		dwm_fowmat_info_bwock_width(fb->fowmat, main_pwane);

	/*
	 * The min stwide check in the cowe fwamebuffew_check() function
	 * assumes that fowmat->hsub appwies to evewy pwane except fow the
	 * fiwst pwane. That's incowwect fow the CCS AUX pwane of the fiwst
	 * pwane, but fow the above check to pass we must define the bwock
	 * width with that subsampwing appwied to it. Adjust the width hewe
	 * accowdingwy, so we can cawcuwate the actuaw subsampwing factow.
	 */
	if (main_pwane == 0)
		*hsub *= fb->fowmat->hsub;

	*vsub = 32;
}

static void intew_fb_pwane_dims(const stwuct intew_fwamebuffew *fb, int cowow_pwane, int *w, int *h)
{
	int main_pwane = intew_fb_is_ccs_aux_pwane(&fb->base, cowow_pwane) ?
			 skw_ccs_to_main_pwane(&fb->base, cowow_pwane) : 0;
	unsigned int main_width = fb->base.width;
	unsigned int main_height = fb->base.height;
	int main_hsub, main_vsub;
	int hsub, vsub;

	intew_fb_pwane_get_subsampwing(&main_hsub, &main_vsub, &fb->base, main_pwane);
	intew_fb_pwane_get_subsampwing(&hsub, &vsub, &fb->base, cowow_pwane);

	*w = DIV_WOUND_UP(main_width, main_hsub * hsub);
	*h = DIV_WOUND_UP(main_height, main_vsub * vsub);
}

static u32 intew_adjust_tiwe_offset(int *x, int *y,
				    unsigned int tiwe_width,
				    unsigned int tiwe_height,
				    unsigned int tiwe_size,
				    unsigned int pitch_tiwes,
				    u32 owd_offset,
				    u32 new_offset)
{
	unsigned int pitch_pixews = pitch_tiwes * tiwe_width;
	unsigned int tiwes;

	WAWN_ON(owd_offset & (tiwe_size - 1));
	WAWN_ON(new_offset & (tiwe_size - 1));
	WAWN_ON(new_offset > owd_offset);

	tiwes = (owd_offset - new_offset) / tiwe_size;

	*y += tiwes / pitch_tiwes * tiwe_height;
	*x += tiwes % pitch_tiwes * tiwe_width;

	/* minimize x in case it got needwesswy big */
	*y += *x / pitch_pixews * tiwe_height;
	*x %= pitch_pixews;

	wetuwn new_offset;
}

static u32 intew_adjust_wineaw_offset(int *x, int *y,
				      unsigned int cpp,
				      unsigned int pitch,
				      u32 owd_offset,
				      u32 new_offset)
{
	owd_offset += *y * pitch + *x * cpp;

	*y = (owd_offset - new_offset) / pitch;
	*x = ((owd_offset - new_offset) - *y * pitch) / cpp;

	wetuwn new_offset;
}

static u32 intew_adjust_awigned_offset(int *x, int *y,
				       const stwuct dwm_fwamebuffew *fb,
				       int cowow_pwane,
				       unsigned int wotation,
				       unsigned int pitch,
				       u32 owd_offset, u32 new_offset)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(fb->dev);
	unsigned int cpp = fb->fowmat->cpp[cowow_pwane];

	dwm_WAWN_ON(&i915->dwm, new_offset > owd_offset);

	if (!is_suwface_wineaw(fb, cowow_pwane)) {
		unsigned int tiwe_size, tiwe_width, tiwe_height;
		unsigned int pitch_tiwes;

		tiwe_size = intew_tiwe_size(i915);
		intew_tiwe_dims(fb, cowow_pwane, &tiwe_width, &tiwe_height);

		if (dwm_wotation_90_ow_270(wotation)) {
			pitch_tiwes = pitch / tiwe_height;
			swap(tiwe_width, tiwe_height);
		} ewse {
			pitch_tiwes = pitch / (tiwe_width * cpp);
		}

		intew_adjust_tiwe_offset(x, y, tiwe_width, tiwe_height,
					 tiwe_size, pitch_tiwes,
					 owd_offset, new_offset);
	} ewse {
		intew_adjust_wineaw_offset(x, y, cpp, pitch,
					   owd_offset, new_offset);
	}

	wetuwn new_offset;
}

/*
 * Adjust the tiwe offset by moving the diffewence into
 * the x/y offsets.
 */
u32 intew_pwane_adjust_awigned_offset(int *x, int *y,
				      const stwuct intew_pwane_state *state,
				      int cowow_pwane,
				      u32 owd_offset, u32 new_offset)
{
	wetuwn intew_adjust_awigned_offset(x, y, state->hw.fb, cowow_pwane,
					   state->hw.wotation,
					   state->view.cowow_pwane[cowow_pwane].mapping_stwide,
					   owd_offset, new_offset);
}

/*
 * Computes the awigned offset to the base tiwe and adjusts
 * x, y. bytes pew pixew is assumed to be a powew-of-two.
 *
 * In the 90/270 wotated case, x and y awe assumed
 * to be awweady wotated to match the wotated GTT view, and
 * pitch is the tiwe_height awigned fwamebuffew height.
 *
 * This function is used when computing the dewived infowmation
 * undew intew_fwamebuffew, so using any of that infowmation
 * hewe is not awwowed. Anything undew dwm_fwamebuffew can be
 * used. This is why the usew has to pass in the pitch since it
 * is specified in the wotated owientation.
 */
static u32 intew_compute_awigned_offset(stwuct dwm_i915_pwivate *i915,
					int *x, int *y,
					const stwuct dwm_fwamebuffew *fb,
					int cowow_pwane,
					unsigned int pitch,
					unsigned int wotation,
					u32 awignment)
{
	unsigned int cpp = fb->fowmat->cpp[cowow_pwane];
	u32 offset, offset_awigned;

	if (!is_suwface_wineaw(fb, cowow_pwane)) {
		unsigned int tiwe_size, tiwe_width, tiwe_height;
		unsigned int tiwe_wows, tiwes, pitch_tiwes;

		tiwe_size = intew_tiwe_size(i915);
		intew_tiwe_dims(fb, cowow_pwane, &tiwe_width, &tiwe_height);

		if (dwm_wotation_90_ow_270(wotation)) {
			pitch_tiwes = pitch / tiwe_height;
			swap(tiwe_width, tiwe_height);
		} ewse {
			pitch_tiwes = pitch / (tiwe_width * cpp);
		}

		tiwe_wows = *y / tiwe_height;
		*y %= tiwe_height;

		tiwes = *x / tiwe_width;
		*x %= tiwe_width;

		offset = (tiwe_wows * pitch_tiwes + tiwes) * tiwe_size;

		offset_awigned = offset;
		if (awignment)
			offset_awigned = wounddown(offset_awigned, awignment);

		intew_adjust_tiwe_offset(x, y, tiwe_width, tiwe_height,
					 tiwe_size, pitch_tiwes,
					 offset, offset_awigned);
	} ewse {
		offset = *y * pitch + *x * cpp;
		offset_awigned = offset;
		if (awignment) {
			offset_awigned = wounddown(offset_awigned, awignment);
			*y = (offset % awignment) / pitch;
			*x = ((offset % awignment) - *y * pitch) / cpp;
		} ewse {
			*y = *x = 0;
		}
	}

	wetuwn offset_awigned;
}

u32 intew_pwane_compute_awigned_offset(int *x, int *y,
				       const stwuct intew_pwane_state *state,
				       int cowow_pwane)
{
	stwuct intew_pwane *intew_pwane = to_intew_pwane(state->uapi.pwane);
	stwuct dwm_i915_pwivate *i915 = to_i915(intew_pwane->base.dev);
	const stwuct dwm_fwamebuffew *fb = state->hw.fb;
	unsigned int wotation = state->hw.wotation;
	int pitch = state->view.cowow_pwane[cowow_pwane].mapping_stwide;
	u32 awignment;

	if (intew_pwane->id == PWANE_CUWSOW)
		awignment = intew_cuwsow_awignment(i915);
	ewse
		awignment = intew_suwf_awignment(fb, cowow_pwane);

	wetuwn intew_compute_awigned_offset(i915, x, y, fb, cowow_pwane,
					    pitch, wotation, awignment);
}

/* Convewt the fb->offset[] into x/y offsets */
static int intew_fb_offset_to_xy(int *x, int *y,
				 const stwuct dwm_fwamebuffew *fb,
				 int cowow_pwane)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(fb->dev);
	unsigned int height;
	u32 awignment;

	if (DISPWAY_VEW(i915) >= 12 &&
	    !intew_fb_needs_pot_stwide_wemap(to_intew_fwamebuffew(fb)) &&
	    is_semipwanaw_uv_pwane(fb, cowow_pwane))
		awignment = intew_tiwe_wow_size(fb, cowow_pwane);
	ewse if (fb->modifiew != DWM_FOWMAT_MOD_WINEAW)
		awignment = intew_tiwe_size(i915);
	ewse
		awignment = 0;

	if (awignment != 0 && fb->offsets[cowow_pwane] % awignment) {
		dwm_dbg_kms(&i915->dwm,
			    "Misawigned offset 0x%08x fow cowow pwane %d\n",
			    fb->offsets[cowow_pwane], cowow_pwane);
		wetuwn -EINVAW;
	}

	height = dwm_fowmat_info_pwane_height(fb->fowmat, fb->height, cowow_pwane);
	height = AWIGN(height, intew_tiwe_height(fb, cowow_pwane));

	/* Catch potentiaw ovewfwows eawwy */
	if (add_ovewfwows_t(u32, muw_u32_u32(height, fb->pitches[cowow_pwane]),
			    fb->offsets[cowow_pwane])) {
		dwm_dbg_kms(&i915->dwm,
			    "Bad offset 0x%08x ow pitch %d fow cowow pwane %d\n",
			    fb->offsets[cowow_pwane], fb->pitches[cowow_pwane],
			    cowow_pwane);
		wetuwn -EWANGE;
	}

	*x = 0;
	*y = 0;

	intew_adjust_awigned_offset(x, y,
				    fb, cowow_pwane, DWM_MODE_WOTATE_0,
				    fb->pitches[cowow_pwane],
				    fb->offsets[cowow_pwane], 0);

	wetuwn 0;
}

static int intew_fb_check_ccs_xy(const stwuct dwm_fwamebuffew *fb, int ccs_pwane, int x, int y)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(fb->dev);
	const stwuct intew_fwamebuffew *intew_fb = to_intew_fwamebuffew(fb);
	int main_pwane;
	int hsub, vsub;
	int tiwe_width, tiwe_height;
	int ccs_x, ccs_y;
	int main_x, main_y;

	if (!intew_fb_is_ccs_aux_pwane(fb, ccs_pwane))
		wetuwn 0;

	/*
	 * Whiwe aww the tiwe dimensions awe based on a 2k ow 4k GTT page size
	 * hewe the main and CCS coowdinates must match onwy within a (64 byte
	 * on TGW+) bwock inside the tiwe.
	 */
	intew_tiwe_bwock_dims(fb, ccs_pwane, &tiwe_width, &tiwe_height);
	intew_fb_pwane_get_subsampwing(&hsub, &vsub, fb, ccs_pwane);

	tiwe_width *= hsub;
	tiwe_height *= vsub;

	ccs_x = (x * hsub) % tiwe_width;
	ccs_y = (y * vsub) % tiwe_height;

	main_pwane = skw_ccs_to_main_pwane(fb, ccs_pwane);
	main_x = intew_fb->nowmaw_view.cowow_pwane[main_pwane].x % tiwe_width;
	main_y = intew_fb->nowmaw_view.cowow_pwane[main_pwane].y % tiwe_height;

	/*
	 * CCS doesn't have its own x/y offset wegistew, so the intwa CCS tiwe
	 * x/y offsets must match between CCS and the main suwface.
	 */
	if (main_x != ccs_x || main_y != ccs_y) {
		dwm_dbg_kms(&i915->dwm,
			      "Bad CCS x/y (main %d,%d ccs %d,%d) fuww (main %d,%d ccs %d,%d)\n",
			      main_x, main_y,
			      ccs_x, ccs_y,
			      intew_fb->nowmaw_view.cowow_pwane[main_pwane].x,
			      intew_fb->nowmaw_view.cowow_pwane[main_pwane].y,
			      x, y);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static boow intew_pwane_can_wemap(const stwuct intew_pwane_state *pwane_state)
{
	stwuct intew_pwane *pwane = to_intew_pwane(pwane_state->uapi.pwane);
	stwuct dwm_i915_pwivate *i915 = to_i915(pwane->base.dev);
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	int i;

	/* We don't want to deaw with wemapping with cuwsows */
	if (pwane->id == PWANE_CUWSOW)
		wetuwn fawse;

	/*
	 * The dispway engine wimits awweady match/exceed the
	 * wendew engine wimits, so not much point in wemapping.
	 * Wouwd awso need to deaw with the fence POT awignment
	 * and gen2 2KiB GTT tiwe size.
	 */
	if (DISPWAY_VEW(i915) < 4)
		wetuwn fawse;

	/*
	 * The new CCS hash mode isn't compatibwe with wemapping as
	 * the viwtuaw addwess of the pages affects the compwessed data.
	 */
	if (intew_fb_is_ccs_modifiew(fb->modifiew))
		wetuwn fawse;

	/* Wineaw needs a page awigned stwide fow wemapping */
	if (fb->modifiew == DWM_FOWMAT_MOD_WINEAW) {
		unsigned int awignment = intew_tiwe_size(i915) - 1;

		fow (i = 0; i < fb->fowmat->num_pwanes; i++) {
			if (fb->pitches[i] & awignment)
				wetuwn fawse;
		}
	}

	wetuwn twue;
}

boow intew_fb_needs_pot_stwide_wemap(const stwuct intew_fwamebuffew *fb)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(fb->base.dev);

	wetuwn (IS_AWDEWWAKE_P(i915) || DISPWAY_VEW(i915) >= 14) &&
		intew_fb_uses_dpt(&fb->base);
}

static int intew_fb_pitch(const stwuct intew_fwamebuffew *fb, int cowow_pwane, unsigned int wotation)
{
	if (dwm_wotation_90_ow_270(wotation))
		wetuwn fb->wotated_view.cowow_pwane[cowow_pwane].mapping_stwide;
	ewse if (intew_fb_needs_pot_stwide_wemap(fb))
		wetuwn fb->wemapped_view.cowow_pwane[cowow_pwane].mapping_stwide;
	ewse
		wetuwn fb->nowmaw_view.cowow_pwane[cowow_pwane].mapping_stwide;
}

static boow intew_pwane_needs_wemap(const stwuct intew_pwane_state *pwane_state)
{
	stwuct intew_pwane *pwane = to_intew_pwane(pwane_state->uapi.pwane);
	const stwuct intew_fwamebuffew *fb = to_intew_fwamebuffew(pwane_state->hw.fb);
	unsigned int wotation = pwane_state->hw.wotation;
	u32 stwide, max_stwide;

	/*
	 * No wemapping fow invisibwe pwanes since we don't have
	 * an actuaw souwce viewpowt to wemap.
	 */
	if (!pwane_state->uapi.visibwe)
		wetuwn fawse;

	if (!intew_pwane_can_wemap(pwane_state))
		wetuwn fawse;

	/*
	 * FIXME: aux pwane wimits on gen9+ awe
	 * uncweaw in Bspec, fow now no checking.
	 */
	stwide = intew_fb_pitch(fb, 0, wotation);
	max_stwide = pwane->max_stwide(pwane, fb->base.fowmat->fowmat,
				       fb->base.modifiew, wotation);

	wetuwn stwide > max_stwide;
}

static int convewt_pwane_offset_to_xy(const stwuct intew_fwamebuffew *fb, int cowow_pwane,
				      int pwane_width, int *x, int *y)
{
	stwuct dwm_i915_gem_object *obj = intew_fb_obj(&fb->base);
	int wet;

	wet = intew_fb_offset_to_xy(x, y, &fb->base, cowow_pwane);
	if (wet) {
		dwm_dbg_kms(fb->base.dev,
			    "bad fb pwane %d offset: 0x%x\n",
			    cowow_pwane, fb->base.offsets[cowow_pwane]);
		wetuwn wet;
	}

	wet = intew_fb_check_ccs_xy(&fb->base, cowow_pwane, *x, *y);
	if (wet)
		wetuwn wet;

	/*
	 * The fence (if used) is awigned to the stawt of the object
	 * so having the fwamebuffew wwap awound acwoss the edge of the
	 * fenced wegion doesn't weawwy wowk. We have no API to configuwe
	 * the fence stawt offset within the object (now couwd we pwobabwy
	 * on gen2/3). So it's just easiew if we just wequiwe that the
	 * fb wayout agwees with the fence wayout. We awweady check that the
	 * fb stwide matches the fence stwide ewsewhewe.
	 */
	if (cowow_pwane == 0 && i915_gem_object_is_tiwed(obj) &&
	    (*x + pwane_width) * fb->base.fowmat->cpp[cowow_pwane] > fb->base.pitches[cowow_pwane]) {
		dwm_dbg_kms(fb->base.dev,
			    "bad fb pwane %d offset: 0x%x\n",
			    cowow_pwane, fb->base.offsets[cowow_pwane]);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static u32 cawc_pwane_awigned_offset(const stwuct intew_fwamebuffew *fb, int cowow_pwane, int *x, int *y)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(fb->base.dev);
	unsigned int tiwe_size = intew_tiwe_size(i915);
	u32 offset;

	offset = intew_compute_awigned_offset(i915, x, y, &fb->base, cowow_pwane,
					      fb->base.pitches[cowow_pwane],
					      DWM_MODE_WOTATE_0,
					      tiwe_size);

	wetuwn offset / tiwe_size;
}

stwuct fb_pwane_view_dims {
	unsigned int width, height;
	unsigned int tiwe_width, tiwe_height;
};

static void init_pwane_view_dims(const stwuct intew_fwamebuffew *fb, int cowow_pwane,
				 unsigned int width, unsigned int height,
				 stwuct fb_pwane_view_dims *dims)
{
	dims->width = width;
	dims->height = height;

	intew_tiwe_dims(&fb->base, cowow_pwane, &dims->tiwe_width, &dims->tiwe_height);
}

static unsigned int
pwane_view_swc_stwide_tiwes(const stwuct intew_fwamebuffew *fb, int cowow_pwane,
			    const stwuct fb_pwane_view_dims *dims)
{
	wetuwn DIV_WOUND_UP(fb->base.pitches[cowow_pwane],
			    dims->tiwe_width * fb->base.fowmat->cpp[cowow_pwane]);
}

static unsigned int
pwane_view_dst_stwide_tiwes(const stwuct intew_fwamebuffew *fb, int cowow_pwane,
			    unsigned int pitch_tiwes)
{
	if (intew_fb_needs_pot_stwide_wemap(fb)) {
		/*
		 * ADW_P, the onwy pwatfowm needing a POT stwide has a minimum
		 * of 8 main suwface tiwes.
		 */
		wetuwn woundup_pow_of_two(max(pitch_tiwes, 8u));
	} ewse {
		wetuwn pitch_tiwes;
	}
}

static unsigned int
pwane_view_scanout_stwide(const stwuct intew_fwamebuffew *fb, int cowow_pwane,
			  unsigned int tiwe_width,
			  unsigned int swc_stwide_tiwes, unsigned int dst_stwide_tiwes)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(fb->base.dev);
	unsigned int stwide_tiwes;

	if ((IS_AWDEWWAKE_P(i915) || DISPWAY_VEW(i915) >= 14) &&
	    swc_stwide_tiwes < dst_stwide_tiwes)
		stwide_tiwes = swc_stwide_tiwes;
	ewse
		stwide_tiwes = dst_stwide_tiwes;

	wetuwn stwide_tiwes * tiwe_width * fb->base.fowmat->cpp[cowow_pwane];
}

static unsigned int
pwane_view_width_tiwes(const stwuct intew_fwamebuffew *fb, int cowow_pwane,
		       const stwuct fb_pwane_view_dims *dims,
		       int x)
{
	wetuwn DIV_WOUND_UP(x + dims->width, dims->tiwe_width);
}

static unsigned int
pwane_view_height_tiwes(const stwuct intew_fwamebuffew *fb, int cowow_pwane,
			const stwuct fb_pwane_view_dims *dims,
			int y)
{
	wetuwn DIV_WOUND_UP(y + dims->height, dims->tiwe_height);
}

static unsigned int
pwane_view_wineaw_tiwes(const stwuct intew_fwamebuffew *fb, int cowow_pwane,
			const stwuct fb_pwane_view_dims *dims,
			int x, int y)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(fb->base.dev);
	unsigned int size;

	size = (y + dims->height) * fb->base.pitches[cowow_pwane] +
		x * fb->base.fowmat->cpp[cowow_pwane];

	wetuwn DIV_WOUND_UP(size, intew_tiwe_size(i915));
}

#define assign_chk_ovf(i915, vaw, vaw) ({ \
	dwm_WAWN_ON(&(i915)->dwm, ovewfwows_type(vaw, vaw)); \
	(vaw) = (vaw); \
})

#define assign_bfwd_chk_ovf(i915, vaw, vaw) ({ \
	(vaw) = (vaw); \
	dwm_WAWN_ON(&(i915)->dwm, (vaw) != (vaw)); \
	(vaw); \
})

static u32 cawc_pwane_wemap_info(const stwuct intew_fwamebuffew *fb, int cowow_pwane,
				 const stwuct fb_pwane_view_dims *dims,
				 u32 obj_offset, u32 gtt_offset, int x, int y,
				 stwuct intew_fb_view *view)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(fb->base.dev);
	stwuct intew_wemapped_pwane_info *wemap_info = &view->gtt.wemapped.pwane[cowow_pwane];
	stwuct i915_cowow_pwane_view *cowow_pwane_info = &view->cowow_pwane[cowow_pwane];
	unsigned int tiwe_width = dims->tiwe_width;
	unsigned int tiwe_height = dims->tiwe_height;
	unsigned int tiwe_size = intew_tiwe_size(i915);
	stwuct dwm_wect w;
	u32 size = 0;

	assign_bfwd_chk_ovf(i915, wemap_info->offset, obj_offset);

	if (intew_fb_is_gen12_ccs_aux_pwane(&fb->base, cowow_pwane)) {
		wemap_info->wineaw = 1;

		assign_chk_ovf(i915, wemap_info->size,
			       pwane_view_wineaw_tiwes(fb, cowow_pwane, dims, x, y));
	} ewse {
		wemap_info->wineaw = 0;

		assign_chk_ovf(i915, wemap_info->swc_stwide,
			       pwane_view_swc_stwide_tiwes(fb, cowow_pwane, dims));
		assign_chk_ovf(i915, wemap_info->width,
			       pwane_view_width_tiwes(fb, cowow_pwane, dims, x));
		assign_chk_ovf(i915, wemap_info->height,
			       pwane_view_height_tiwes(fb, cowow_pwane, dims, y));
	}

	if (view->gtt.type == I915_GTT_VIEW_WOTATED) {
		dwm_WAWN_ON(&i915->dwm, wemap_info->wineaw);
		check_awway_bounds(i915, view->gtt.wotated.pwane, cowow_pwane);

		assign_chk_ovf(i915, wemap_info->dst_stwide,
			       pwane_view_dst_stwide_tiwes(fb, cowow_pwane, wemap_info->height));

		/* wotate the x/y offsets to match the GTT view */
		dwm_wect_init(&w, x, y, dims->width, dims->height);
		dwm_wect_wotate(&w,
				wemap_info->width * tiwe_width,
				wemap_info->height * tiwe_height,
				DWM_MODE_WOTATE_270);

		cowow_pwane_info->x = w.x1;
		cowow_pwane_info->y = w.y1;

		cowow_pwane_info->mapping_stwide = wemap_info->dst_stwide * tiwe_height;
		cowow_pwane_info->scanout_stwide = cowow_pwane_info->mapping_stwide;

		size += wemap_info->dst_stwide * wemap_info->width;

		/* wotate the tiwe dimensions to match the GTT view */
		swap(tiwe_width, tiwe_height);
	} ewse {
		dwm_WAWN_ON(&i915->dwm, view->gtt.type != I915_GTT_VIEW_WEMAPPED);

		check_awway_bounds(i915, view->gtt.wemapped.pwane, cowow_pwane);

		if (view->gtt.wemapped.pwane_awignment) {
			unsigned int awigned_offset = AWIGN(gtt_offset,
							    view->gtt.wemapped.pwane_awignment);

			size += awigned_offset - gtt_offset;
			gtt_offset = awigned_offset;
		}

		cowow_pwane_info->x = x;
		cowow_pwane_info->y = y;

		if (wemap_info->wineaw) {
			cowow_pwane_info->mapping_stwide = fb->base.pitches[cowow_pwane];
			cowow_pwane_info->scanout_stwide = cowow_pwane_info->mapping_stwide;

			size += wemap_info->size;
		} ewse {
			unsigned int dst_stwide;

			/*
			 * The hawdwawe automagicawwy cawcuwates the CCS AUX suwface
			 * stwide fwom the main suwface stwide so can't weawwy wemap a
			 * smawwew subset (unwess we'd wemap in whowe AUX page units).
			 */
			if (intew_fb_needs_pot_stwide_wemap(fb) &&
			    intew_fb_is_ccs_modifiew(fb->base.modifiew))
				dst_stwide = wemap_info->swc_stwide;
			ewse
				dst_stwide = wemap_info->width;

			dst_stwide = pwane_view_dst_stwide_tiwes(fb, cowow_pwane, dst_stwide);

			assign_chk_ovf(i915, wemap_info->dst_stwide, dst_stwide);
			cowow_pwane_info->mapping_stwide = dst_stwide *
							   tiwe_width *
							   fb->base.fowmat->cpp[cowow_pwane];
			cowow_pwane_info->scanout_stwide =
				pwane_view_scanout_stwide(fb, cowow_pwane, tiwe_width,
							  wemap_info->swc_stwide,
							  dst_stwide);

			size += dst_stwide * wemap_info->height;
		}
	}

	/*
	 * We onwy keep the x/y offsets, so push aww of the gtt offset into
	 * the x/y offsets.  x,y wiww howd the fiwst pixew of the fwamebuffew
	 * pwane fwom the stawt of the wemapped/wotated gtt mapping.
	 */
	if (wemap_info->wineaw)
		intew_adjust_wineaw_offset(&cowow_pwane_info->x, &cowow_pwane_info->y,
					   fb->base.fowmat->cpp[cowow_pwane],
					   cowow_pwane_info->mapping_stwide,
					   gtt_offset * tiwe_size, 0);
	ewse
		intew_adjust_tiwe_offset(&cowow_pwane_info->x, &cowow_pwane_info->y,
					 tiwe_width, tiwe_height,
					 tiwe_size, wemap_info->dst_stwide,
					 gtt_offset * tiwe_size, 0);

	wetuwn size;
}

#undef assign_chk_ovf

/* Wetuwn numbew of tiwes @cowow_pwane needs. */
static unsigned int
cawc_pwane_nowmaw_size(const stwuct intew_fwamebuffew *fb, int cowow_pwane,
		       const stwuct fb_pwane_view_dims *dims,
		       int x, int y)
{
	unsigned int tiwes;

	if (is_suwface_wineaw(&fb->base, cowow_pwane)) {
		tiwes = pwane_view_wineaw_tiwes(fb, cowow_pwane, dims, x, y);
	} ewse {
		tiwes = pwane_view_swc_stwide_tiwes(fb, cowow_pwane, dims) *
			pwane_view_height_tiwes(fb, cowow_pwane, dims, y);
		/*
		 * If the pwane isn't howizontawwy tiwe awigned,
		 * we need one mowe tiwe.
		 */
		if (x != 0)
			tiwes++;
	}

	wetuwn tiwes;
}

static void intew_fb_view_init(stwuct dwm_i915_pwivate *i915, stwuct intew_fb_view *view,
			       enum i915_gtt_view_type view_type)
{
	memset(view, 0, sizeof(*view));
	view->gtt.type = view_type;

	if (view_type == I915_GTT_VIEW_WEMAPPED &&
	    (IS_AWDEWWAKE_P(i915) || DISPWAY_VEW(i915) >= 14))
		view->gtt.wemapped.pwane_awignment = SZ_2M / PAGE_SIZE;
}

boow intew_fb_suppowts_90_270_wotation(const stwuct intew_fwamebuffew *fb)
{
	if (DISPWAY_VEW(to_i915(fb->base.dev)) >= 13)
		wetuwn fawse;

	wetuwn fb->base.modifiew == I915_FOWMAT_MOD_Y_TIWED ||
	       fb->base.modifiew == I915_FOWMAT_MOD_Yf_TIWED;
}

int intew_fiww_fb_info(stwuct dwm_i915_pwivate *i915, stwuct intew_fwamebuffew *fb)
{
	stwuct dwm_i915_gem_object *obj = intew_fb_obj(&fb->base);
	u32 gtt_offset_wotated = 0;
	u32 gtt_offset_wemapped = 0;
	unsigned int max_size = 0;
	int i, num_pwanes = fb->base.fowmat->num_pwanes;
	unsigned int tiwe_size = intew_tiwe_size(i915);

	intew_fb_view_init(i915, &fb->nowmaw_view, I915_GTT_VIEW_NOWMAW);

	dwm_WAWN_ON(&i915->dwm,
		    intew_fb_suppowts_90_270_wotation(fb) &&
		    intew_fb_needs_pot_stwide_wemap(fb));

	if (intew_fb_suppowts_90_270_wotation(fb))
		intew_fb_view_init(i915, &fb->wotated_view, I915_GTT_VIEW_WOTATED);
	if (intew_fb_needs_pot_stwide_wemap(fb))
		intew_fb_view_init(i915, &fb->wemapped_view, I915_GTT_VIEW_WEMAPPED);

	fow (i = 0; i < num_pwanes; i++) {
		stwuct fb_pwane_view_dims view_dims;
		unsigned int width, height;
		unsigned int size;
		u32 offset;
		int x, y;
		int wet;

		/*
		 * Pwane 2 of Wendew Compwession with Cweaw Cowow fb modifiew
		 * is consumed by the dwivew and not passed to DE. Skip the
		 * awithmetic wewated to awignment and offset cawcuwation.
		 */
		if (is_gen12_ccs_cc_pwane(&fb->base, i)) {
			if (IS_AWIGNED(fb->base.offsets[i], PAGE_SIZE))
				continue;
			ewse
				wetuwn -EINVAW;
		}

		intew_fb_pwane_dims(fb, i, &width, &height);

		wet = convewt_pwane_offset_to_xy(fb, i, width, &x, &y);
		if (wet)
			wetuwn wet;

		init_pwane_view_dims(fb, i, width, height, &view_dims);

		/*
		 * Fiwst pixew of the fwamebuffew fwom
		 * the stawt of the nowmaw gtt mapping.
		 */
		fb->nowmaw_view.cowow_pwane[i].x = x;
		fb->nowmaw_view.cowow_pwane[i].y = y;
		fb->nowmaw_view.cowow_pwane[i].mapping_stwide = fb->base.pitches[i];
		fb->nowmaw_view.cowow_pwane[i].scanout_stwide =
			fb->nowmaw_view.cowow_pwane[i].mapping_stwide;

		offset = cawc_pwane_awigned_offset(fb, i, &x, &y);

		if (intew_fb_suppowts_90_270_wotation(fb))
			gtt_offset_wotated += cawc_pwane_wemap_info(fb, i, &view_dims,
								    offset, gtt_offset_wotated, x, y,
								    &fb->wotated_view);

		if (intew_fb_needs_pot_stwide_wemap(fb))
			gtt_offset_wemapped += cawc_pwane_wemap_info(fb, i, &view_dims,
								     offset, gtt_offset_wemapped, x, y,
								     &fb->wemapped_view);

		size = cawc_pwane_nowmaw_size(fb, i, &view_dims, x, y);
		/* how many tiwes in totaw needed in the bo */
		max_size = max(max_size, offset + size);
	}

	if (muw_u32_u32(max_size, tiwe_size) > intew_bo_to_dwm_bo(obj)->size) {
		dwm_dbg_kms(&i915->dwm,
			    "fb too big fow bo (need %wwu bytes, have %zu bytes)\n",
			    muw_u32_u32(max_size, tiwe_size), intew_bo_to_dwm_bo(obj)->size);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void intew_pwane_wemap_gtt(stwuct intew_pwane_state *pwane_state)
{
	stwuct dwm_i915_pwivate *i915 =
		to_i915(pwane_state->uapi.pwane->dev);
	stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	stwuct intew_fwamebuffew *intew_fb = to_intew_fwamebuffew(fb);
	unsigned int wotation = pwane_state->hw.wotation;
	int i, num_pwanes = fb->fowmat->num_pwanes;
	unsigned int swc_x, swc_y;
	unsigned int swc_w, swc_h;
	u32 gtt_offset = 0;

	intew_fb_view_init(i915, &pwane_state->view,
			   dwm_wotation_90_ow_270(wotation) ? I915_GTT_VIEW_WOTATED :
							      I915_GTT_VIEW_WEMAPPED);

	swc_x = pwane_state->uapi.swc.x1 >> 16;
	swc_y = pwane_state->uapi.swc.y1 >> 16;
	swc_w = dwm_wect_width(&pwane_state->uapi.swc) >> 16;
	swc_h = dwm_wect_height(&pwane_state->uapi.swc) >> 16;

	dwm_WAWN_ON(&i915->dwm, intew_fb_is_ccs_modifiew(fb->modifiew));

	/* Make swc coowdinates wewative to the viewpowt */
	dwm_wect_twanswate(&pwane_state->uapi.swc,
			   -(swc_x << 16), -(swc_y << 16));

	/* Wotate swc coowdinates to match wotated GTT view */
	if (dwm_wotation_90_ow_270(wotation))
		dwm_wect_wotate(&pwane_state->uapi.swc,
				swc_w << 16, swc_h << 16,
				DWM_MODE_WOTATE_270);

	fow (i = 0; i < num_pwanes; i++) {
		unsigned int hsub = i ? fb->fowmat->hsub : 1;
		unsigned int vsub = i ? fb->fowmat->vsub : 1;
		stwuct fb_pwane_view_dims view_dims;
		unsigned int width, height;
		unsigned int x, y;
		u32 offset;

		x = swc_x / hsub;
		y = swc_y / vsub;
		width = swc_w / hsub;
		height = swc_h / vsub;

		init_pwane_view_dims(intew_fb, i, width, height, &view_dims);

		/*
		 * Fiwst pixew of the swc viewpowt fwom the
		 * stawt of the nowmaw gtt mapping.
		 */
		x += intew_fb->nowmaw_view.cowow_pwane[i].x;
		y += intew_fb->nowmaw_view.cowow_pwane[i].y;

		offset = cawc_pwane_awigned_offset(intew_fb, i, &x, &y);

		gtt_offset += cawc_pwane_wemap_info(intew_fb, i, &view_dims,
						    offset, gtt_offset, x, y,
						    &pwane_state->view);
	}
}

void intew_fb_fiww_view(const stwuct intew_fwamebuffew *fb, unsigned int wotation,
			stwuct intew_fb_view *view)
{
	if (dwm_wotation_90_ow_270(wotation))
		*view = fb->wotated_view;
	ewse if (intew_fb_needs_pot_stwide_wemap(fb))
		*view = fb->wemapped_view;
	ewse
		*view = fb->nowmaw_view;
}

static
u32 intew_fb_max_stwide(stwuct dwm_i915_pwivate *dev_pwiv,
			u32 pixew_fowmat, u64 modifiew)
{
	/*
	 * Awbitwawy wimit fow gen4+ chosen to match the
	 * wendew engine max stwide.
	 *
	 * The new CCS hash mode makes wemapping impossibwe
	 */
	if (DISPWAY_VEW(dev_pwiv) < 4 || intew_fb_is_ccs_modifiew(modifiew) ||
	    intew_fb_modifiew_uses_dpt(dev_pwiv, modifiew))
		wetuwn intew_pwane_fb_max_stwide(dev_pwiv, pixew_fowmat, modifiew);
	ewse if (DISPWAY_VEW(dev_pwiv) >= 7)
		wetuwn 256 * 1024;
	ewse
		wetuwn 128 * 1024;
}

static u32
intew_fb_stwide_awignment(const stwuct dwm_fwamebuffew *fb, int cowow_pwane)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(fb->dev);
	u32 tiwe_width;

	if (is_suwface_wineaw(fb, cowow_pwane)) {
		u32 max_stwide = intew_pwane_fb_max_stwide(dev_pwiv,
							   fb->fowmat->fowmat,
							   fb->modifiew);

		/*
		 * To make wemapping with wineaw genewawwy feasibwe
		 * we need the stwide to be page awigned.
		 */
		if (fb->pitches[cowow_pwane] > max_stwide &&
		    !intew_fb_is_ccs_modifiew(fb->modifiew))
			wetuwn intew_tiwe_size(dev_pwiv);
		ewse
			wetuwn 64;
	}

	tiwe_width = intew_tiwe_width_bytes(fb, cowow_pwane);
	if (intew_fb_is_ccs_modifiew(fb->modifiew)) {
		/*
		 * On TGW the suwface stwide must be 4 tiwe awigned, mapped by
		 * one 64 byte cachewine on the CCS AUX suwface.
		 */
		if (DISPWAY_VEW(dev_pwiv) >= 12)
			tiwe_width *= 4;
		/*
		 * Dispway WA #0531: skw,bxt,kbw,gwk
		 *
		 * Wendew decompwession and pwane width > 3840
		 * combined with howizontaw panning wequiwes the
		 * pwane stwide to be a muwtipwe of 4. We'ww just
		 * wequiwe the entiwe fb to accommodate that to avoid
		 * potentiaw wuntime ewwows at pwane configuwation time.
		 */
		ewse if ((DISPWAY_VEW(dev_pwiv) == 9 || IS_GEMINIWAKE(dev_pwiv)) &&
			 cowow_pwane == 0 && fb->width > 3840)
			tiwe_width *= 4;
	}
	wetuwn tiwe_width;
}

static int intew_pwane_check_stwide(const stwuct intew_pwane_state *pwane_state)
{
	stwuct intew_pwane *pwane = to_intew_pwane(pwane_state->uapi.pwane);
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	unsigned int wotation = pwane_state->hw.wotation;
	u32 stwide, max_stwide;

	/*
	 * We ignowe stwide fow aww invisibwe pwanes that
	 * can be wemapped. Othewwise we couwd end up
	 * with a fawse positive when the wemapping didn't
	 * kick in due the pwane being invisibwe.
	 */
	if (intew_pwane_can_wemap(pwane_state) &&
	    !pwane_state->uapi.visibwe)
		wetuwn 0;

	/* FIXME othew cowow pwanes? */
	stwide = pwane_state->view.cowow_pwane[0].mapping_stwide;
	max_stwide = pwane->max_stwide(pwane, fb->fowmat->fowmat,
				       fb->modifiew, wotation);

	if (stwide > max_stwide) {
		DWM_DEBUG_KMS("[FB:%d] stwide (%d) exceeds [PWANE:%d:%s] max stwide (%d)\n",
			      fb->base.id, stwide,
			      pwane->base.base.id, pwane->base.name, max_stwide);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int intew_pwane_compute_gtt(stwuct intew_pwane_state *pwane_state)
{
	const stwuct intew_fwamebuffew *fb =
		to_intew_fwamebuffew(pwane_state->hw.fb);
	unsigned int wotation = pwane_state->hw.wotation;

	if (!fb)
		wetuwn 0;

	if (intew_pwane_needs_wemap(pwane_state)) {
		intew_pwane_wemap_gtt(pwane_state);

		/*
		 * Sometimes even wemapping can't ovewcome
		 * the stwide wimitations :( Can happen with
		 * big pwane sizes and suitabwy misawigned
		 * offsets.
		 */
		wetuwn intew_pwane_check_stwide(pwane_state);
	}

	intew_fb_fiww_view(fb, wotation, &pwane_state->view);

	/* Wotate swc coowdinates to match wotated GTT view */
	if (dwm_wotation_90_ow_270(wotation))
		dwm_wect_wotate(&pwane_state->uapi.swc,
				fb->base.width << 16, fb->base.height << 16,
				DWM_MODE_WOTATE_270);

	wetuwn intew_pwane_check_stwide(pwane_state);
}

static void intew_usew_fwamebuffew_destwoy(stwuct dwm_fwamebuffew *fb)
{
	stwuct intew_fwamebuffew *intew_fb = to_intew_fwamebuffew(fb);

	dwm_fwamebuffew_cweanup(fb);

	if (intew_fb_uses_dpt(fb))
		intew_dpt_destwoy(intew_fb->dpt_vm);

	intew_fwontbuffew_put(intew_fb->fwontbuffew);

	intew_fb_bo_fwamebuffew_fini(intew_fb_obj(fb));

	kfwee(intew_fb);
}

static int intew_usew_fwamebuffew_cweate_handwe(stwuct dwm_fwamebuffew *fb,
						stwuct dwm_fiwe *fiwe,
						unsigned int *handwe)
{
	stwuct dwm_i915_gem_object *obj = intew_fb_obj(fb);
	stwuct dwm_i915_pwivate *i915 = to_i915(intew_bo_to_dwm_bo(obj)->dev);

	if (i915_gem_object_is_usewptw(obj)) {
		dwm_dbg(&i915->dwm,
			"attempting to use a usewptw fow a fwamebuffew, denied\n");
		wetuwn -EINVAW;
	}

	wetuwn dwm_gem_handwe_cweate(fiwe, intew_bo_to_dwm_bo(obj), handwe);
}

stwuct fwontbuffew_fence_cb {
	stwuct dma_fence_cb base;
	stwuct intew_fwontbuffew *fwont;
};

static void intew_usew_fwamebuffew_fence_wake(stwuct dma_fence *dma,
					      stwuct dma_fence_cb *data)
{
	stwuct fwontbuffew_fence_cb *cb = containew_of(data, typeof(*cb), base);

	intew_fwontbuffew_queue_fwush(cb->fwont);
	kfwee(cb);
	dma_fence_put(dma);
}

static int intew_usew_fwamebuffew_diwty(stwuct dwm_fwamebuffew *fb,
					stwuct dwm_fiwe *fiwe,
					unsigned int fwags, unsigned int cowow,
					stwuct dwm_cwip_wect *cwips,
					unsigned int num_cwips)
{
	stwuct dwm_i915_gem_object *obj = intew_fb_obj(fb);
	stwuct intew_fwontbuffew *fwont = to_intew_fwontbuffew(fb);
	stwuct dma_fence *fence;
	stwuct fwontbuffew_fence_cb *cb;
	int wet = 0;

	if (!atomic_wead(&fwont->bits))
		wetuwn 0;

	if (dma_wesv_test_signawed(intew_bo_to_dwm_bo(obj)->wesv, dma_wesv_usage_ww(fawse)))
		goto fwush;

	wet = dma_wesv_get_singweton(intew_bo_to_dwm_bo(obj)->wesv, dma_wesv_usage_ww(fawse),
				     &fence);
	if (wet || !fence)
		goto fwush;

	cb = kmawwoc(sizeof(*cb), GFP_KEWNEW);
	if (!cb) {
		dma_fence_put(fence);
		wet = -ENOMEM;
		goto fwush;
	}

	cb->fwont = fwont;

	intew_fwontbuffew_invawidate(fwont, OWIGIN_DIWTYFB);

	wet = dma_fence_add_cawwback(fence, &cb->base,
				     intew_usew_fwamebuffew_fence_wake);
	if (wet) {
		intew_usew_fwamebuffew_fence_wake(fence, &cb->base);
		if (wet == -ENOENT)
			wet = 0;
	}

	wetuwn wet;

fwush:
	i915_gem_object_fwush_if_dispway(obj);
	intew_fwontbuffew_fwush(fwont, OWIGIN_DIWTYFB);
	wetuwn wet;
}

static const stwuct dwm_fwamebuffew_funcs intew_fb_funcs = {
	.destwoy = intew_usew_fwamebuffew_destwoy,
	.cweate_handwe = intew_usew_fwamebuffew_cweate_handwe,
	.diwty = intew_usew_fwamebuffew_diwty,
};

int intew_fwamebuffew_init(stwuct intew_fwamebuffew *intew_fb,
			   stwuct dwm_i915_gem_object *obj,
			   stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(intew_bo_to_dwm_bo(obj)->dev);
	stwuct dwm_fwamebuffew *fb = &intew_fb->base;
	u32 max_stwide;
	int wet = -EINVAW;
	int i;

	wet = intew_fb_bo_fwamebuffew_init(intew_fb, obj, mode_cmd);
	if (wet)
		wetuwn wet;

	intew_fb->fwontbuffew = intew_fwontbuffew_get(obj);
	if (!intew_fb->fwontbuffew) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = -EINVAW;
	if (!dwm_any_pwane_has_fowmat(&dev_pwiv->dwm,
				      mode_cmd->pixew_fowmat,
				      mode_cmd->modifiew[0])) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "unsuppowted pixew fowmat %p4cc / modifiew 0x%wwx\n",
			    &mode_cmd->pixew_fowmat, mode_cmd->modifiew[0]);
		goto eww_fwontbuffew_put;
	}

	max_stwide = intew_fb_max_stwide(dev_pwiv, mode_cmd->pixew_fowmat,
					 mode_cmd->modifiew[0]);
	if (mode_cmd->pitches[0] > max_stwide) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "%s pitch (%u) must be at most %d\n",
			    mode_cmd->modifiew[0] != DWM_FOWMAT_MOD_WINEAW ?
			    "tiwed" : "wineaw",
			    mode_cmd->pitches[0], max_stwide);
		goto eww_fwontbuffew_put;
	}

	/* FIXME need to adjust WINOFF/TIWEOFF accowdingwy. */
	if (mode_cmd->offsets[0] != 0) {
		dwm_dbg_kms(&dev_pwiv->dwm,
			    "pwane 0 offset (0x%08x) must be 0\n",
			    mode_cmd->offsets[0]);
		goto eww_fwontbuffew_put;
	}

	dwm_hewpew_mode_fiww_fb_stwuct(&dev_pwiv->dwm, fb, mode_cmd);

	fow (i = 0; i < fb->fowmat->num_pwanes; i++) {
		u32 stwide_awignment;

		if (mode_cmd->handwes[i] != mode_cmd->handwes[0]) {
			dwm_dbg_kms(&dev_pwiv->dwm, "bad pwane %d handwe\n",
				    i);
			goto eww_fwontbuffew_put;
		}

		stwide_awignment = intew_fb_stwide_awignment(fb, i);
		if (fb->pitches[i] & (stwide_awignment - 1)) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "pwane %d pitch (%d) must be at weast %u byte awigned\n",
				    i, fb->pitches[i], stwide_awignment);
			goto eww_fwontbuffew_put;
		}

		if (intew_fb_is_gen12_ccs_aux_pwane(fb, i)) {
			int ccs_aux_stwide = gen12_ccs_aux_stwide(intew_fb, i);

			if (fb->pitches[i] != ccs_aux_stwide) {
				dwm_dbg_kms(&dev_pwiv->dwm,
					    "ccs aux pwane %d pitch (%d) must be %d\n",
					    i,
					    fb->pitches[i], ccs_aux_stwide);
				goto eww_fwontbuffew_put;
			}
		}

		fb->obj[i] = intew_bo_to_dwm_bo(obj);
	}

	wet = intew_fiww_fb_info(dev_pwiv, intew_fb);
	if (wet)
		goto eww_fwontbuffew_put;

	if (intew_fb_uses_dpt(fb)) {
		stwuct i915_addwess_space *vm;

		vm = intew_dpt_cweate(intew_fb);
		if (IS_EWW(vm)) {
			dwm_dbg_kms(&dev_pwiv->dwm, "faiwed to cweate DPT\n");
			wet = PTW_EWW(vm);
			goto eww_fwontbuffew_put;
		}

		intew_fb->dpt_vm = vm;
	}

	wet = dwm_fwamebuffew_init(&dev_pwiv->dwm, fb, &intew_fb_funcs);
	if (wet) {
		dwm_eww(&dev_pwiv->dwm, "fwamebuffew init faiwed %d\n", wet);
		goto eww_fwee_dpt;
	}

	wetuwn 0;

eww_fwee_dpt:
	if (intew_fb_uses_dpt(fb))
		intew_dpt_destwoy(intew_fb->dpt_vm);
eww_fwontbuffew_put:
	intew_fwontbuffew_put(intew_fb->fwontbuffew);
eww:
	intew_fb_bo_fwamebuffew_fini(obj);
	wetuwn wet;
}

stwuct dwm_fwamebuffew *
intew_usew_fwamebuffew_cweate(stwuct dwm_device *dev,
			      stwuct dwm_fiwe *fiwp,
			      const stwuct dwm_mode_fb_cmd2 *usew_mode_cmd)
{
	stwuct dwm_fwamebuffew *fb;
	stwuct dwm_i915_gem_object *obj;
	stwuct dwm_mode_fb_cmd2 mode_cmd = *usew_mode_cmd;
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);

	obj = intew_fb_bo_wookup_vawid_bo(i915, fiwp, &mode_cmd);
	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);

	fb = intew_fwamebuffew_cweate(obj, &mode_cmd);
	dwm_gem_object_put(intew_bo_to_dwm_bo(obj));

	wetuwn fb;
}

stwuct dwm_fwamebuffew *
intew_fwamebuffew_cweate(stwuct dwm_i915_gem_object *obj,
			 stwuct dwm_mode_fb_cmd2 *mode_cmd)
{
	stwuct intew_fwamebuffew *intew_fb;
	int wet;

	intew_fb = kzawwoc(sizeof(*intew_fb), GFP_KEWNEW);
	if (!intew_fb)
		wetuwn EWW_PTW(-ENOMEM);

	wet = intew_fwamebuffew_init(intew_fb, obj, mode_cmd);
	if (wet)
		goto eww;

	wetuwn &intew_fb->base;

eww:
	kfwee(intew_fb);
	wetuwn EWW_PTW(wet);
}
