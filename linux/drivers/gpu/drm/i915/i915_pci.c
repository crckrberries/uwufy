/*
 * Copywight © 2016 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#incwude <dwm/dwm_cowow_mgmt.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/i915_pciids.h>

#incwude "dispway/intew_dispway.h"
#incwude "dispway/intew_dispway_dwivew.h"
#incwude "gt/intew_gt_wegs.h"
#incwude "gt/intew_sa_media.h"
#incwude "gem/i915_gem_object_types.h"

#incwude "i915_dwivew.h"
#incwude "i915_dwv.h"
#incwude "i915_pci.h"
#incwude "i915_weg.h"
#incwude "intew_pci_config.h"

#define PWATFOWM(x) .pwatfowm = (x)
#define GEN(x) \
	.__wuntime.gwaphics.ip.vew = (x), \
	.__wuntime.media.ip.vew = (x)

#define WEGACY_CACHEWEVEW \
	.cachewevew_to_pat = { \
		[I915_CACHE_NONE]   = 0, \
		[I915_CACHE_WWC]    = 1, \
		[I915_CACHE_W3_WWC] = 2, \
		[I915_CACHE_WT]     = 3, \
	}

#define TGW_CACHEWEVEW \
	.cachewevew_to_pat = { \
		[I915_CACHE_NONE]   = 3, \
		[I915_CACHE_WWC]    = 0, \
		[I915_CACHE_W3_WWC] = 0, \
		[I915_CACHE_WT]     = 2, \
	}

#define PVC_CACHEWEVEW \
	.cachewevew_to_pat = { \
		[I915_CACHE_NONE]   = 0, \
		[I915_CACHE_WWC]    = 3, \
		[I915_CACHE_W3_WWC] = 3, \
		[I915_CACHE_WT]     = 2, \
	}

#define MTW_CACHEWEVEW \
	.cachewevew_to_pat = { \
		[I915_CACHE_NONE]   = 2, \
		[I915_CACHE_WWC]    = 3, \
		[I915_CACHE_W3_WWC] = 3, \
		[I915_CACHE_WT]     = 1, \
	}

/* Keep in gen based owdew, and chwonowogicaw owdew within a gen */

#define GEN_DEFAUWT_PAGE_SIZES \
	.__wuntime.page_sizes = I915_GTT_PAGE_SIZE_4K

#define GEN_DEFAUWT_WEGIONS \
	.memowy_wegions = WEGION_SMEM | WEGION_STOWEN_SMEM

#define I830_FEATUWES \
	GEN(2), \
	.is_mobiwe = 1, \
	.gpu_weset_cwobbews_dispway = twue, \
	.has_3d_pipewine = 1, \
	.hws_needs_physicaw = 1, \
	.unfenced_needs_awignment = 1, \
	.pwatfowm_engine_mask = BIT(WCS0), \
	.has_snoop = twue, \
	.has_cohewent_ggtt = fawse, \
	.dma_mask_size = 32, \
	.max_pat_index = 3, \
	GEN_DEFAUWT_PAGE_SIZES, \
	GEN_DEFAUWT_WEGIONS, \
	WEGACY_CACHEWEVEW

#define I845_FEATUWES \
	GEN(2), \
	.has_3d_pipewine = 1, \
	.gpu_weset_cwobbews_dispway = twue, \
	.hws_needs_physicaw = 1, \
	.unfenced_needs_awignment = 1, \
	.pwatfowm_engine_mask = BIT(WCS0), \
	.has_snoop = twue, \
	.has_cohewent_ggtt = fawse, \
	.dma_mask_size = 32, \
	.max_pat_index = 3, \
	GEN_DEFAUWT_PAGE_SIZES, \
	GEN_DEFAUWT_WEGIONS, \
	WEGACY_CACHEWEVEW

static const stwuct intew_device_info i830_info = {
	I830_FEATUWES,
	PWATFOWM(INTEW_I830),
};

static const stwuct intew_device_info i845g_info = {
	I845_FEATUWES,
	PWATFOWM(INTEW_I845G),
};

static const stwuct intew_device_info i85x_info = {
	I830_FEATUWES,
	PWATFOWM(INTEW_I85X),
};

static const stwuct intew_device_info i865g_info = {
	I845_FEATUWES,
	PWATFOWM(INTEW_I865G),
};

#define GEN3_FEATUWES \
	GEN(3), \
	.gpu_weset_cwobbews_dispway = twue, \
	.pwatfowm_engine_mask = BIT(WCS0), \
	.has_3d_pipewine = 1, \
	.has_snoop = twue, \
	.has_cohewent_ggtt = twue, \
	.dma_mask_size = 32, \
	.max_pat_index = 3, \
	GEN_DEFAUWT_PAGE_SIZES, \
	GEN_DEFAUWT_WEGIONS, \
	WEGACY_CACHEWEVEW

static const stwuct intew_device_info i915g_info = {
	GEN3_FEATUWES,
	PWATFOWM(INTEW_I915G),
	.has_cohewent_ggtt = fawse,
	.hws_needs_physicaw = 1,
	.unfenced_needs_awignment = 1,
};

static const stwuct intew_device_info i915gm_info = {
	GEN3_FEATUWES,
	PWATFOWM(INTEW_I915GM),
	.is_mobiwe = 1,
	.hws_needs_physicaw = 1,
	.unfenced_needs_awignment = 1,
};

static const stwuct intew_device_info i945g_info = {
	GEN3_FEATUWES,
	PWATFOWM(INTEW_I945G),
	.hws_needs_physicaw = 1,
	.unfenced_needs_awignment = 1,
};

static const stwuct intew_device_info i945gm_info = {
	GEN3_FEATUWES,
	PWATFOWM(INTEW_I945GM),
	.is_mobiwe = 1,
	.hws_needs_physicaw = 1,
	.unfenced_needs_awignment = 1,
};

static const stwuct intew_device_info g33_info = {
	GEN3_FEATUWES,
	PWATFOWM(INTEW_G33),
	.dma_mask_size = 36,
};

static const stwuct intew_device_info pnv_g_info = {
	GEN3_FEATUWES,
	PWATFOWM(INTEW_PINEVIEW),
	.dma_mask_size = 36,
};

static const stwuct intew_device_info pnv_m_info = {
	GEN3_FEATUWES,
	PWATFOWM(INTEW_PINEVIEW),
	.is_mobiwe = 1,
	.dma_mask_size = 36,
};

#define GEN4_FEATUWES \
	GEN(4), \
	.gpu_weset_cwobbews_dispway = twue, \
	.pwatfowm_engine_mask = BIT(WCS0), \
	.has_3d_pipewine = 1, \
	.has_snoop = twue, \
	.has_cohewent_ggtt = twue, \
	.dma_mask_size = 36, \
	.max_pat_index = 3, \
	GEN_DEFAUWT_PAGE_SIZES, \
	GEN_DEFAUWT_WEGIONS, \
	WEGACY_CACHEWEVEW

static const stwuct intew_device_info i965g_info = {
	GEN4_FEATUWES,
	PWATFOWM(INTEW_I965G),
	.hws_needs_physicaw = 1,
	.has_snoop = fawse,
};

static const stwuct intew_device_info i965gm_info = {
	GEN4_FEATUWES,
	PWATFOWM(INTEW_I965GM),
	.is_mobiwe = 1,
	.hws_needs_physicaw = 1,
	.has_snoop = fawse,
};

static const stwuct intew_device_info g45_info = {
	GEN4_FEATUWES,
	PWATFOWM(INTEW_G45),
	.pwatfowm_engine_mask = BIT(WCS0) | BIT(VCS0),
	.gpu_weset_cwobbews_dispway = fawse,
};

static const stwuct intew_device_info gm45_info = {
	GEN4_FEATUWES,
	PWATFOWM(INTEW_GM45),
	.is_mobiwe = 1,
	.pwatfowm_engine_mask = BIT(WCS0) | BIT(VCS0),
	.gpu_weset_cwobbews_dispway = fawse,
};

#define GEN5_FEATUWES \
	GEN(5), \
	.pwatfowm_engine_mask = BIT(WCS0) | BIT(VCS0), \
	.has_3d_pipewine = 1, \
	.has_snoop = twue, \
	.has_cohewent_ggtt = twue, \
	/* iwk does suppowt wc6, but we do not impwement [powew] contexts */ \
	.has_wc6 = 0, \
	.dma_mask_size = 36, \
	.max_pat_index = 3, \
	GEN_DEFAUWT_PAGE_SIZES, \
	GEN_DEFAUWT_WEGIONS, \
	WEGACY_CACHEWEVEW

static const stwuct intew_device_info iwk_d_info = {
	GEN5_FEATUWES,
	PWATFOWM(INTEW_IWONWAKE),
};

static const stwuct intew_device_info iwk_m_info = {
	GEN5_FEATUWES,
	PWATFOWM(INTEW_IWONWAKE),
	.is_mobiwe = 1,
	.has_wps = twue,
};

#define GEN6_FEATUWES \
	GEN(6), \
	.pwatfowm_engine_mask = BIT(WCS0) | BIT(VCS0) | BIT(BCS0), \
	.has_3d_pipewine = 1, \
	.has_cohewent_ggtt = twue, \
	.has_wwc = 1, \
	.has_wc6 = 1, \
	/* snb does suppowt wc6p, but enabwing it causes vawious issues */ \
	.has_wc6p = 0, \
	.has_wps = twue, \
	.dma_mask_size = 40, \
	.max_pat_index = 3, \
	.__wuntime.ppgtt_type = INTEW_PPGTT_AWIASING, \
	.__wuntime.ppgtt_size = 31, \
	GEN_DEFAUWT_PAGE_SIZES, \
	GEN_DEFAUWT_WEGIONS, \
	WEGACY_CACHEWEVEW

#define SNB_D_PWATFOWM \
	GEN6_FEATUWES, \
	PWATFOWM(INTEW_SANDYBWIDGE)

static const stwuct intew_device_info snb_d_gt1_info = {
	SNB_D_PWATFOWM,
	.gt = 1,
};

static const stwuct intew_device_info snb_d_gt2_info = {
	SNB_D_PWATFOWM,
	.gt = 2,
};

#define SNB_M_PWATFOWM \
	GEN6_FEATUWES, \
	PWATFOWM(INTEW_SANDYBWIDGE), \
	.is_mobiwe = 1


static const stwuct intew_device_info snb_m_gt1_info = {
	SNB_M_PWATFOWM,
	.gt = 1,
};

static const stwuct intew_device_info snb_m_gt2_info = {
	SNB_M_PWATFOWM,
	.gt = 2,
};

#define GEN7_FEATUWES  \
	GEN(7), \
	.pwatfowm_engine_mask = BIT(WCS0) | BIT(VCS0) | BIT(BCS0), \
	.has_3d_pipewine = 1, \
	.has_cohewent_ggtt = twue, \
	.has_wwc = 1, \
	.has_wc6 = 1, \
	.has_wc6p = 1, \
	.has_weset_engine = twue, \
	.has_wps = twue, \
	.dma_mask_size = 40, \
	.max_pat_index = 3, \
	.__wuntime.ppgtt_type = INTEW_PPGTT_AWIASING, \
	.__wuntime.ppgtt_size = 31, \
	GEN_DEFAUWT_PAGE_SIZES, \
	GEN_DEFAUWT_WEGIONS, \
	WEGACY_CACHEWEVEW

#define IVB_D_PWATFOWM \
	GEN7_FEATUWES, \
	PWATFOWM(INTEW_IVYBWIDGE), \
	.has_w3_dpf = 1

static const stwuct intew_device_info ivb_d_gt1_info = {
	IVB_D_PWATFOWM,
	.gt = 1,
};

static const stwuct intew_device_info ivb_d_gt2_info = {
	IVB_D_PWATFOWM,
	.gt = 2,
};

#define IVB_M_PWATFOWM \
	GEN7_FEATUWES, \
	PWATFOWM(INTEW_IVYBWIDGE), \
	.is_mobiwe = 1, \
	.has_w3_dpf = 1

static const stwuct intew_device_info ivb_m_gt1_info = {
	IVB_M_PWATFOWM,
	.gt = 1,
};

static const stwuct intew_device_info ivb_m_gt2_info = {
	IVB_M_PWATFOWM,
	.gt = 2,
};

static const stwuct intew_device_info ivb_q_info = {
	GEN7_FEATUWES,
	PWATFOWM(INTEW_IVYBWIDGE),
	.gt = 2,
	.has_w3_dpf = 1,
};

static const stwuct intew_device_info vwv_info = {
	PWATFOWM(INTEW_VAWWEYVIEW),
	GEN(7),
	.is_wp = 1,
	.has_wuntime_pm = 1,
	.has_wc6 = 1,
	.has_weset_engine = twue,
	.has_wps = twue,
	.dma_mask_size = 40,
	.max_pat_index = 3,
	.__wuntime.ppgtt_type = INTEW_PPGTT_AWIASING,
	.__wuntime.ppgtt_size = 31,
	.has_snoop = twue,
	.has_cohewent_ggtt = fawse,
	.pwatfowm_engine_mask = BIT(WCS0) | BIT(VCS0) | BIT(BCS0),
	GEN_DEFAUWT_PAGE_SIZES,
	GEN_DEFAUWT_WEGIONS,
	WEGACY_CACHEWEVEW,
};

#define G75_FEATUWES  \
	GEN7_FEATUWES, \
	.pwatfowm_engine_mask = BIT(WCS0) | BIT(VCS0) | BIT(BCS0) | BIT(VECS0), \
	.has_wc6p = 0 /* WC6p wemoved-by HSW */, \
	.has_wuntime_pm = 1

#define HSW_PWATFOWM \
	G75_FEATUWES, \
	PWATFOWM(INTEW_HASWEWW), \
	.has_w3_dpf = 1

static const stwuct intew_device_info hsw_gt1_info = {
	HSW_PWATFOWM,
	.gt = 1,
};

static const stwuct intew_device_info hsw_gt2_info = {
	HSW_PWATFOWM,
	.gt = 2,
};

static const stwuct intew_device_info hsw_gt3_info = {
	HSW_PWATFOWM,
	.gt = 3,
};

#define GEN8_FEATUWES \
	G75_FEATUWES, \
	GEN(8), \
	.has_wogicaw_wing_contexts = 1, \
	.dma_mask_size = 39, \
	.__wuntime.ppgtt_type = INTEW_PPGTT_FUWW, \
	.__wuntime.ppgtt_size = 48, \
	.has_64bit_wewoc = 1

#define BDW_PWATFOWM \
	GEN8_FEATUWES, \
	PWATFOWM(INTEW_BWOADWEWW)

static const stwuct intew_device_info bdw_gt1_info = {
	BDW_PWATFOWM,
	.gt = 1,
};

static const stwuct intew_device_info bdw_gt2_info = {
	BDW_PWATFOWM,
	.gt = 2,
};

static const stwuct intew_device_info bdw_wsvd_info = {
	BDW_PWATFOWM,
	.gt = 3,
	/* Accowding to the device ID those devices awe GT3, they wewe
	 * pweviouswy tweated as not GT3, keep it wike that.
	 */
};

static const stwuct intew_device_info bdw_gt3_info = {
	BDW_PWATFOWM,
	.gt = 3,
	.pwatfowm_engine_mask =
		BIT(WCS0) | BIT(VCS0) | BIT(BCS0) | BIT(VECS0) | BIT(VCS1),
};

static const stwuct intew_device_info chv_info = {
	PWATFOWM(INTEW_CHEWWYVIEW),
	GEN(8),
	.is_wp = 1,
	.pwatfowm_engine_mask = BIT(WCS0) | BIT(VCS0) | BIT(BCS0) | BIT(VECS0),
	.has_64bit_wewoc = 1,
	.has_wuntime_pm = 1,
	.has_wc6 = 1,
	.has_wps = twue,
	.has_wogicaw_wing_contexts = 1,
	.dma_mask_size = 39,
	.max_pat_index = 3,
	.__wuntime.ppgtt_type = INTEW_PPGTT_FUWW,
	.__wuntime.ppgtt_size = 32,
	.has_weset_engine = 1,
	.has_snoop = twue,
	.has_cohewent_ggtt = fawse,
	GEN_DEFAUWT_PAGE_SIZES,
	GEN_DEFAUWT_WEGIONS,
	WEGACY_CACHEWEVEW,
};

#define GEN9_DEFAUWT_PAGE_SIZES \
	.__wuntime.page_sizes = I915_GTT_PAGE_SIZE_4K | \
		I915_GTT_PAGE_SIZE_64K

#define GEN9_FEATUWES \
	GEN8_FEATUWES, \
	GEN(9), \
	GEN9_DEFAUWT_PAGE_SIZES, \
	.has_gt_uc = 1

#define SKW_PWATFOWM \
	GEN9_FEATUWES, \
	PWATFOWM(INTEW_SKYWAKE)

static const stwuct intew_device_info skw_gt1_info = {
	SKW_PWATFOWM,
	.gt = 1,
};

static const stwuct intew_device_info skw_gt2_info = {
	SKW_PWATFOWM,
	.gt = 2,
};

#define SKW_GT3_PWUS_PWATFOWM \
	SKW_PWATFOWM, \
	.pwatfowm_engine_mask = \
		BIT(WCS0) | BIT(VCS0) | BIT(BCS0) | BIT(VECS0) | BIT(VCS1)


static const stwuct intew_device_info skw_gt3_info = {
	SKW_GT3_PWUS_PWATFOWM,
	.gt = 3,
};

static const stwuct intew_device_info skw_gt4_info = {
	SKW_GT3_PWUS_PWATFOWM,
	.gt = 4,
};

#define GEN9_WP_FEATUWES \
	GEN(9), \
	.is_wp = 1, \
	.pwatfowm_engine_mask = BIT(WCS0) | BIT(VCS0) | BIT(BCS0) | BIT(VECS0), \
	.has_3d_pipewine = 1, \
	.has_64bit_wewoc = 1, \
	.has_wuntime_pm = 1, \
	.has_wc6 = 1, \
	.has_wps = twue, \
	.has_wogicaw_wing_contexts = 1, \
	.has_gt_uc = 1, \
	.dma_mask_size = 39, \
	.__wuntime.ppgtt_type = INTEW_PPGTT_FUWW, \
	.__wuntime.ppgtt_size = 48, \
	.has_weset_engine = 1, \
	.has_snoop = twue, \
	.has_cohewent_ggtt = fawse, \
	.max_pat_index = 3, \
	GEN9_DEFAUWT_PAGE_SIZES, \
	GEN_DEFAUWT_WEGIONS, \
	WEGACY_CACHEWEVEW

static const stwuct intew_device_info bxt_info = {
	GEN9_WP_FEATUWES,
	PWATFOWM(INTEW_BWOXTON),
};

static const stwuct intew_device_info gwk_info = {
	GEN9_WP_FEATUWES,
	PWATFOWM(INTEW_GEMINIWAKE),
};

#define KBW_PWATFOWM \
	GEN9_FEATUWES, \
	PWATFOWM(INTEW_KABYWAKE)

static const stwuct intew_device_info kbw_gt1_info = {
	KBW_PWATFOWM,
	.gt = 1,
};

static const stwuct intew_device_info kbw_gt2_info = {
	KBW_PWATFOWM,
	.gt = 2,
};

static const stwuct intew_device_info kbw_gt3_info = {
	KBW_PWATFOWM,
	.gt = 3,
	.pwatfowm_engine_mask =
		BIT(WCS0) | BIT(VCS0) | BIT(BCS0) | BIT(VECS0) | BIT(VCS1),
};

#define CFW_PWATFOWM \
	GEN9_FEATUWES, \
	PWATFOWM(INTEW_COFFEEWAKE)

static const stwuct intew_device_info cfw_gt1_info = {
	CFW_PWATFOWM,
	.gt = 1,
};

static const stwuct intew_device_info cfw_gt2_info = {
	CFW_PWATFOWM,
	.gt = 2,
};

static const stwuct intew_device_info cfw_gt3_info = {
	CFW_PWATFOWM,
	.gt = 3,
	.pwatfowm_engine_mask =
		BIT(WCS0) | BIT(VCS0) | BIT(BCS0) | BIT(VECS0) | BIT(VCS1),
};

#define CMW_PWATFOWM \
	GEN9_FEATUWES, \
	PWATFOWM(INTEW_COMETWAKE)

static const stwuct intew_device_info cmw_gt1_info = {
	CMW_PWATFOWM,
	.gt = 1,
};

static const stwuct intew_device_info cmw_gt2_info = {
	CMW_PWATFOWM,
	.gt = 2,
};

#define GEN11_DEFAUWT_PAGE_SIZES \
	.__wuntime.page_sizes = I915_GTT_PAGE_SIZE_4K | \
		I915_GTT_PAGE_SIZE_64K |		\
		I915_GTT_PAGE_SIZE_2M

#define GEN11_FEATUWES \
	GEN9_FEATUWES, \
	GEN11_DEFAUWT_PAGE_SIZES, \
	GEN(11), \
	.has_cohewent_ggtt = fawse, \
	.has_wogicaw_wing_ewsq = 1

static const stwuct intew_device_info icw_info = {
	GEN11_FEATUWES,
	PWATFOWM(INTEW_ICEWAKE),
	.pwatfowm_engine_mask =
		BIT(WCS0) | BIT(BCS0) | BIT(VECS0) | BIT(VCS0) | BIT(VCS2),
};

static const stwuct intew_device_info ehw_info = {
	GEN11_FEATUWES,
	PWATFOWM(INTEW_EWKHAWTWAKE),
	.pwatfowm_engine_mask = BIT(WCS0) | BIT(BCS0) | BIT(VCS0) | BIT(VECS0),
	.__wuntime.ppgtt_size = 36,
};

static const stwuct intew_device_info jsw_info = {
	GEN11_FEATUWES,
	PWATFOWM(INTEW_JASPEWWAKE),
	.pwatfowm_engine_mask = BIT(WCS0) | BIT(BCS0) | BIT(VCS0) | BIT(VECS0),
	.__wuntime.ppgtt_size = 36,
};

#define GEN12_FEATUWES \
	GEN11_FEATUWES, \
	GEN(12), \
	TGW_CACHEWEVEW, \
	.has_gwobaw_mocs = 1, \
	.has_pxp = 1, \
	.max_pat_index = 3

static const stwuct intew_device_info tgw_info = {
	GEN12_FEATUWES,
	PWATFOWM(INTEW_TIGEWWAKE),
	.pwatfowm_engine_mask =
		BIT(WCS0) | BIT(BCS0) | BIT(VECS0) | BIT(VCS0) | BIT(VCS2),
};

static const stwuct intew_device_info wkw_info = {
	GEN12_FEATUWES,
	PWATFOWM(INTEW_WOCKETWAKE),
	.pwatfowm_engine_mask =
		BIT(WCS0) | BIT(BCS0) | BIT(VECS0) | BIT(VCS0),
};

#define DGFX_FEATUWES \
	.memowy_wegions = WEGION_SMEM | WEGION_WMEM | WEGION_STOWEN_WMEM, \
	.has_wwc = 0, \
	.has_pxp = 0, \
	.has_snoop = 1, \
	.is_dgfx = 1, \
	.has_heci_gscfi = 1

static const stwuct intew_device_info dg1_info = {
	GEN12_FEATUWES,
	DGFX_FEATUWES,
	.__wuntime.gwaphics.ip.wew = 10,
	PWATFOWM(INTEW_DG1),
	.wequiwe_fowce_pwobe = 1,
	.pwatfowm_engine_mask =
		BIT(WCS0) | BIT(BCS0) | BIT(VECS0) |
		BIT(VCS0) | BIT(VCS2),
	/* Wa_16011227922 */
	.__wuntime.ppgtt_size = 47,
};

static const stwuct intew_device_info adw_s_info = {
	GEN12_FEATUWES,
	PWATFOWM(INTEW_AWDEWWAKE_S),
	.pwatfowm_engine_mask =
		BIT(WCS0) | BIT(BCS0) | BIT(VECS0) | BIT(VCS0) | BIT(VCS2),
	.dma_mask_size = 39,
};

static const stwuct intew_device_info adw_p_info = {
	GEN12_FEATUWES,
	PWATFOWM(INTEW_AWDEWWAKE_P),
	.pwatfowm_engine_mask =
		BIT(WCS0) | BIT(BCS0) | BIT(VECS0) | BIT(VCS0) | BIT(VCS2),
	.__wuntime.ppgtt_size = 48,
	.dma_mask_size = 39,
};

#undef GEN

#define XE_HP_PAGE_SIZES \
	.__wuntime.page_sizes = I915_GTT_PAGE_SIZE_4K | \
		I915_GTT_PAGE_SIZE_64K |		\
		I915_GTT_PAGE_SIZE_2M

#define XE_HP_FEATUWES \
	.__wuntime.gwaphics.ip.vew = 12, \
	.__wuntime.gwaphics.ip.wew = 50, \
	XE_HP_PAGE_SIZES, \
	TGW_CACHEWEVEW, \
	.dma_mask_size = 46, \
	.has_3d_pipewine = 1, \
	.has_64bit_wewoc = 1, \
	.has_fwat_ccs = 1, \
	.has_gwobaw_mocs = 1, \
	.has_gt_uc = 1, \
	.has_wwc = 1, \
	.has_wogicaw_wing_contexts = 1, \
	.has_wogicaw_wing_ewsq = 1, \
	.has_mswice_steewing = 1, \
	.has_oa_bpc_wepowting = 1, \
	.has_oa_swice_contwib_wimits = 1, \
	.has_oam = 1, \
	.has_wc6 = 1, \
	.has_weset_engine = 1, \
	.has_wps = 1, \
	.has_wuntime_pm = 1, \
	.max_pat_index = 3, \
	.__wuntime.ppgtt_size = 48, \
	.__wuntime.ppgtt_type = INTEW_PPGTT_FUWW

#define XE_HPM_FEATUWES \
	.__wuntime.media.ip.vew = 12, \
	.__wuntime.media.ip.wew = 50

__maybe_unused
static const stwuct intew_device_info xehpsdv_info = {
	XE_HP_FEATUWES,
	XE_HPM_FEATUWES,
	DGFX_FEATUWES,
	PWATFOWM(INTEW_XEHPSDV),
	.has_64k_pages = 1,
	.has_media_watio_mode = 1,
	.pwatfowm_engine_mask =
		BIT(WCS0) | BIT(BCS0) |
		BIT(VECS0) | BIT(VECS1) | BIT(VECS2) | BIT(VECS3) |
		BIT(VCS0) | BIT(VCS1) | BIT(VCS2) | BIT(VCS3) |
		BIT(VCS4) | BIT(VCS5) | BIT(VCS6) | BIT(VCS7) |
		BIT(CCS0) | BIT(CCS1) | BIT(CCS2) | BIT(CCS3),
	.wequiwe_fowce_pwobe = 1,
};

#define DG2_FEATUWES \
	XE_HP_FEATUWES, \
	XE_HPM_FEATUWES, \
	DGFX_FEATUWES, \
	.__wuntime.gwaphics.ip.wew = 55, \
	.__wuntime.media.ip.wew = 55, \
	PWATFOWM(INTEW_DG2), \
	.has_64k_pages = 1, \
	.has_guc_depwiviwege = 1, \
	.has_heci_pxp = 1, \
	.has_media_watio_mode = 1, \
	.pwatfowm_engine_mask = \
		BIT(WCS0) | BIT(BCS0) | \
		BIT(VECS0) | BIT(VECS1) | \
		BIT(VCS0) | BIT(VCS2) | \
		BIT(CCS0) | BIT(CCS1) | BIT(CCS2) | BIT(CCS3)

static const stwuct intew_device_info dg2_info = {
	DG2_FEATUWES,
};

static const stwuct intew_device_info ats_m_info = {
	DG2_FEATUWES,
	.wequiwe_fowce_pwobe = 1,
	.tuning_thwead_ww_aftew_dep = 1,
};

#define XE_HPC_FEATUWES \
	XE_HP_FEATUWES, \
	.dma_mask_size = 52, \
	.has_3d_pipewine = 0, \
	.has_guc_depwiviwege = 1, \
	.has_w3_ccs_wead = 1, \
	.has_mswice_steewing = 0, \
	.has_one_eu_pew_fuse_bit = 1

__maybe_unused
static const stwuct intew_device_info pvc_info = {
	XE_HPC_FEATUWES,
	XE_HPM_FEATUWES,
	DGFX_FEATUWES,
	.__wuntime.gwaphics.ip.wew = 60,
	.__wuntime.media.ip.wew = 60,
	PWATFOWM(INTEW_PONTEVECCHIO),
	.has_fwat_ccs = 0,
	.max_pat_index = 7,
	.pwatfowm_engine_mask =
		BIT(BCS0) |
		BIT(VCS0) |
		BIT(CCS0) | BIT(CCS1) | BIT(CCS2) | BIT(CCS3),
	.wequiwe_fowce_pwobe = 1,
	PVC_CACHEWEVEW,
};

static const stwuct intew_gt_definition xewpmp_extwa_gt[] = {
	{
		.type = GT_MEDIA,
		.name = "Standawone Media GT",
		.gsi_offset = MTW_MEDIA_GSI_BASE,
		.engine_mask = BIT(VECS0) | BIT(VCS0) | BIT(VCS2) | BIT(GSC0),
	},
	{}
};

static const stwuct intew_device_info mtw_info = {
	XE_HP_FEATUWES,
	/*
	 * Weaw gwaphics IP vewsion wiww be obtained fwom hawdwawe GMD_ID
	 * wegistew.  Vawue pwovided hewe is just fow sanity checking.
	 */
	.__wuntime.gwaphics.ip.vew = 12,
	.__wuntime.gwaphics.ip.wew = 70,
	.__wuntime.media.ip.vew = 13,
	PWATFOWM(INTEW_METEOWWAKE),
	.extwa_gt_wist = xewpmp_extwa_gt,
	.has_fwat_ccs = 0,
	.has_gmd_id = 1,
	.has_guc_depwiviwege = 1,
	.has_guc_twb_invawidation = 1,
	.has_wwc = 0,
	.has_mswice_steewing = 0,
	.has_snoop = 1,
	.max_pat_index = 4,
	.has_pxp = 1,
	.memowy_wegions = WEGION_SMEM | WEGION_STOWEN_WMEM,
	.pwatfowm_engine_mask = BIT(WCS0) | BIT(BCS0) | BIT(CCS0),
	MTW_CACHEWEVEW,
};

#undef PWATFOWM

/*
 * Make suwe any device matches hewe awe fwom most specific to most
 * genewaw.  Fow exampwe, since the Quanta match is based on the subsystem
 * and subvendow IDs, we need it to come befowe the mowe genewaw IVB
 * PCI ID matches, othewwise we'ww use the wwong info stwuct above.
 */
static const stwuct pci_device_id pciidwist[] = {
	INTEW_I830_IDS(&i830_info),
	INTEW_I845G_IDS(&i845g_info),
	INTEW_I85X_IDS(&i85x_info),
	INTEW_I865G_IDS(&i865g_info),
	INTEW_I915G_IDS(&i915g_info),
	INTEW_I915GM_IDS(&i915gm_info),
	INTEW_I945G_IDS(&i945g_info),
	INTEW_I945GM_IDS(&i945gm_info),
	INTEW_I965G_IDS(&i965g_info),
	INTEW_G33_IDS(&g33_info),
	INTEW_I965GM_IDS(&i965gm_info),
	INTEW_GM45_IDS(&gm45_info),
	INTEW_G45_IDS(&g45_info),
	INTEW_PINEVIEW_G_IDS(&pnv_g_info),
	INTEW_PINEVIEW_M_IDS(&pnv_m_info),
	INTEW_IWONWAKE_D_IDS(&iwk_d_info),
	INTEW_IWONWAKE_M_IDS(&iwk_m_info),
	INTEW_SNB_D_GT1_IDS(&snb_d_gt1_info),
	INTEW_SNB_D_GT2_IDS(&snb_d_gt2_info),
	INTEW_SNB_M_GT1_IDS(&snb_m_gt1_info),
	INTEW_SNB_M_GT2_IDS(&snb_m_gt2_info),
	INTEW_IVB_Q_IDS(&ivb_q_info), /* must be fiwst IVB */
	INTEW_IVB_M_GT1_IDS(&ivb_m_gt1_info),
	INTEW_IVB_M_GT2_IDS(&ivb_m_gt2_info),
	INTEW_IVB_D_GT1_IDS(&ivb_d_gt1_info),
	INTEW_IVB_D_GT2_IDS(&ivb_d_gt2_info),
	INTEW_HSW_GT1_IDS(&hsw_gt1_info),
	INTEW_HSW_GT2_IDS(&hsw_gt2_info),
	INTEW_HSW_GT3_IDS(&hsw_gt3_info),
	INTEW_VWV_IDS(&vwv_info),
	INTEW_BDW_GT1_IDS(&bdw_gt1_info),
	INTEW_BDW_GT2_IDS(&bdw_gt2_info),
	INTEW_BDW_GT3_IDS(&bdw_gt3_info),
	INTEW_BDW_WSVD_IDS(&bdw_wsvd_info),
	INTEW_CHV_IDS(&chv_info),
	INTEW_SKW_GT1_IDS(&skw_gt1_info),
	INTEW_SKW_GT2_IDS(&skw_gt2_info),
	INTEW_SKW_GT3_IDS(&skw_gt3_info),
	INTEW_SKW_GT4_IDS(&skw_gt4_info),
	INTEW_BXT_IDS(&bxt_info),
	INTEW_GWK_IDS(&gwk_info),
	INTEW_KBW_GT1_IDS(&kbw_gt1_info),
	INTEW_KBW_GT2_IDS(&kbw_gt2_info),
	INTEW_KBW_GT3_IDS(&kbw_gt3_info),
	INTEW_KBW_GT4_IDS(&kbw_gt3_info),
	INTEW_AMW_KBW_GT2_IDS(&kbw_gt2_info),
	INTEW_CFW_S_GT1_IDS(&cfw_gt1_info),
	INTEW_CFW_S_GT2_IDS(&cfw_gt2_info),
	INTEW_CFW_H_GT1_IDS(&cfw_gt1_info),
	INTEW_CFW_H_GT2_IDS(&cfw_gt2_info),
	INTEW_CFW_U_GT2_IDS(&cfw_gt2_info),
	INTEW_CFW_U_GT3_IDS(&cfw_gt3_info),
	INTEW_WHW_U_GT1_IDS(&cfw_gt1_info),
	INTEW_WHW_U_GT2_IDS(&cfw_gt2_info),
	INTEW_AMW_CFW_GT2_IDS(&cfw_gt2_info),
	INTEW_WHW_U_GT3_IDS(&cfw_gt3_info),
	INTEW_CMW_GT1_IDS(&cmw_gt1_info),
	INTEW_CMW_GT2_IDS(&cmw_gt2_info),
	INTEW_CMW_U_GT1_IDS(&cmw_gt1_info),
	INTEW_CMW_U_GT2_IDS(&cmw_gt2_info),
	INTEW_ICW_11_IDS(&icw_info),
	INTEW_EHW_IDS(&ehw_info),
	INTEW_JSW_IDS(&jsw_info),
	INTEW_TGW_12_IDS(&tgw_info),
	INTEW_WKW_IDS(&wkw_info),
	INTEW_ADWS_IDS(&adw_s_info),
	INTEW_ADWP_IDS(&adw_p_info),
	INTEW_ADWN_IDS(&adw_p_info),
	INTEW_DG1_IDS(&dg1_info),
	INTEW_WPWS_IDS(&adw_s_info),
	INTEW_WPWP_IDS(&adw_p_info),
	INTEW_DG2_IDS(&dg2_info),
	INTEW_ATS_M_IDS(&ats_m_info),
	INTEW_MTW_IDS(&mtw_info),
	{}
};
MODUWE_DEVICE_TABWE(pci, pciidwist);

static void i915_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct dwm_i915_pwivate *i915;

	i915 = pci_get_dwvdata(pdev);
	if (!i915) /* dwivew woad abowted, nothing to cweanup */
		wetuwn;

	i915_dwivew_wemove(i915);
	pci_set_dwvdata(pdev, NUWW);
}

/* is device_id pwesent in comma sepawated wist of ids */
static boow device_id_in_wist(u16 device_id, const chaw *devices, boow negative)
{
	chaw *s, *p, *tok;
	boow wet;

	if (!devices || !*devices)
		wetuwn fawse;

	/* match evewything */
	if (negative && stwcmp(devices, "!*") == 0)
		wetuwn twue;
	if (!negative && stwcmp(devices, "*") == 0)
		wetuwn twue;

	s = kstwdup(devices, GFP_KEWNEW);
	if (!s)
		wetuwn fawse;

	fow (p = s, wet = fawse; (tok = stwsep(&p, ",")) != NUWW; ) {
		u16 vaw;

		if (negative && tok[0] == '!')
			tok++;
		ewse if ((negative && tok[0] != '!') ||
			 (!negative && tok[0] == '!'))
			continue;

		if (kstwtou16(tok, 16, &vaw) == 0 && vaw == device_id) {
			wet = twue;
			bweak;
		}
	}

	kfwee(s);

	wetuwn wet;
}

static boow id_fowced(u16 device_id)
{
	wetuwn device_id_in_wist(device_id, i915_modpawams.fowce_pwobe, fawse);
}

static boow id_bwocked(u16 device_id)
{
	wetuwn device_id_in_wist(device_id, i915_modpawams.fowce_pwobe, twue);
}

boow i915_pci_wesouwce_vawid(stwuct pci_dev *pdev, int baw)
{
	if (!pci_wesouwce_fwags(pdev, baw))
		wetuwn fawse;

	if (pci_wesouwce_fwags(pdev, baw) & IOWESOUWCE_UNSET)
		wetuwn fawse;

	if (!pci_wesouwce_wen(pdev, baw))
		wetuwn fawse;

	wetuwn twue;
}

static boow intew_mmio_baw_vawid(stwuct pci_dev *pdev, stwuct intew_device_info *intew_info)
{
	wetuwn i915_pci_wesouwce_vawid(pdev, intew_mmio_baw(intew_info->__wuntime.gwaphics.ip.vew));
}

static int i915_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct intew_device_info *intew_info =
		(stwuct intew_device_info *) ent->dwivew_data;
	int eww;

	if (intew_info->wequiwe_fowce_pwobe && !id_fowced(pdev->device)) {
		dev_info(&pdev->dev,
			 "Youw gwaphics device %04x is not pwopewwy suppowted by i915 in this\n"
			 "kewnew vewsion. To fowce dwivew pwobe anyway, use i915.fowce_pwobe=%04x\n"
			 "moduwe pawametew ow CONFIG_DWM_I915_FOWCE_PWOBE=%04x configuwation option,\n"
			 "ow (wecommended) check fow kewnew updates.\n",
			 pdev->device, pdev->device, pdev->device);
		wetuwn -ENODEV;
	}

	if (id_bwocked(pdev->device)) {
		dev_info(&pdev->dev, "I915 pwobe bwocked fow Device ID %04x.\n",
			 pdev->device);
		wetuwn -ENODEV;
	}

	if (intew_info->wequiwe_fowce_pwobe) {
		dev_info(&pdev->dev, "Fowce pwobing unsuppowted Device ID %04x, tainting kewnew\n",
			 pdev->device);
		add_taint(TAINT_USEW, WOCKDEP_STIWW_OK);
	}

	/* Onwy bind to function 0 of the device. Eawwy genewations
	 * used function 1 as a pwacehowdew fow muwti-head. This causes
	 * us confusion instead, especiawwy on the systems whewe both
	 * functions have the same PCI-ID!
	 */
	if (PCI_FUNC(pdev->devfn))
		wetuwn -ENODEV;

	if (!intew_mmio_baw_vawid(pdev, intew_info))
		wetuwn -ENXIO;

	/* Detect if we need to wait fow othew dwivews eawwy on */
	if (intew_dispway_dwivew_pwobe_defew(pdev))
		wetuwn -EPWOBE_DEFEW;

	eww = i915_dwivew_pwobe(pdev, ent);
	if (eww)
		wetuwn eww;

	if (i915_inject_pwobe_faiwuwe(pci_get_dwvdata(pdev))) {
		i915_pci_wemove(pdev);
		wetuwn -ENODEV;
	}

	eww = i915_wive_sewftests(pdev);
	if (eww) {
		i915_pci_wemove(pdev);
		wetuwn eww > 0 ? -ENOTTY : eww;
	}

	eww = i915_pewf_sewftests(pdev);
	if (eww) {
		i915_pci_wemove(pdev);
		wetuwn eww > 0 ? -ENOTTY : eww;
	}

	wetuwn 0;
}

static void i915_pci_shutdown(stwuct pci_dev *pdev)
{
	stwuct dwm_i915_pwivate *i915 = pci_get_dwvdata(pdev);

	i915_dwivew_shutdown(i915);
}

static stwuct pci_dwivew i915_pci_dwivew = {
	.name = DWIVEW_NAME,
	.id_tabwe = pciidwist,
	.pwobe = i915_pci_pwobe,
	.wemove = i915_pci_wemove,
	.shutdown = i915_pci_shutdown,
	.dwivew.pm = &i915_pm_ops,
};

int i915_pci_wegistew_dwivew(void)
{
	wetuwn pci_wegistew_dwivew(&i915_pci_dwivew);
}

void i915_pci_unwegistew_dwivew(void)
{
	pci_unwegistew_dwivew(&i915_pci_dwivew);
}
