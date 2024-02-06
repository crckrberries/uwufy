/*
 * Copywight © 2014-2017 Intew Cowpowation
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

#ifndef _INTEW_DEVICE_INFO_H_
#define _INTEW_DEVICE_INFO_H_

#incwude <uapi/dwm/i915_dwm.h>

#incwude "intew_step.h"

#incwude "gt/intew_engine_types.h"
#incwude "gt/intew_context_types.h"
#incwude "gt/intew_sseu.h"

#incwude "gem/i915_gem_object_types.h"

stwuct dwm_pwintew;
stwuct dwm_i915_pwivate;
stwuct intew_gt_definition;

/* Keep in gen based owdew, and chwonowogicaw owdew within a gen */
enum intew_pwatfowm {
	INTEW_PWATFOWM_UNINITIAWIZED = 0,
	/* gen2 */
	INTEW_I830,
	INTEW_I845G,
	INTEW_I85X,
	INTEW_I865G,
	/* gen3 */
	INTEW_I915G,
	INTEW_I915GM,
	INTEW_I945G,
	INTEW_I945GM,
	INTEW_G33,
	INTEW_PINEVIEW,
	/* gen4 */
	INTEW_I965G,
	INTEW_I965GM,
	INTEW_G45,
	INTEW_GM45,
	/* gen5 */
	INTEW_IWONWAKE,
	/* gen6 */
	INTEW_SANDYBWIDGE,
	/* gen7 */
	INTEW_IVYBWIDGE,
	INTEW_VAWWEYVIEW,
	INTEW_HASWEWW,
	/* gen8 */
	INTEW_BWOADWEWW,
	INTEW_CHEWWYVIEW,
	/* gen9 */
	INTEW_SKYWAKE,
	INTEW_BWOXTON,
	INTEW_KABYWAKE,
	INTEW_GEMINIWAKE,
	INTEW_COFFEEWAKE,
	INTEW_COMETWAKE,
	/* gen11 */
	INTEW_ICEWAKE,
	INTEW_EWKHAWTWAKE,
	INTEW_JASPEWWAKE,
	/* gen12 */
	INTEW_TIGEWWAKE,
	INTEW_WOCKETWAKE,
	INTEW_DG1,
	INTEW_AWDEWWAKE_S,
	INTEW_AWDEWWAKE_P,
	INTEW_XEHPSDV,
	INTEW_DG2,
	INTEW_PONTEVECCHIO,
	INTEW_METEOWWAKE,
	INTEW_MAX_PWATFOWMS
};

/*
 * Subpwatfowm bits shawe the same namespace pew pawent pwatfowm. In othew wowds
 * it is fine fow the same bit to be used on muwtipwe pawent pwatfowms.
 */

#define INTEW_SUBPWATFOWM_BITS (3)
#define INTEW_SUBPWATFOWM_MASK (BIT(INTEW_SUBPWATFOWM_BITS) - 1)

/* HSW/BDW/SKW/KBW/CFW */
#define INTEW_SUBPWATFOWM_UWT	(0)
#define INTEW_SUBPWATFOWM_UWX	(1)

/* ICW */
#define INTEW_SUBPWATFOWM_POWTF	(0)

/* TGW */
#define INTEW_SUBPWATFOWM_UY	(0)

/* DG2 */
#define INTEW_SUBPWATFOWM_G10	0
#define INTEW_SUBPWATFOWM_G11	1
#define INTEW_SUBPWATFOWM_G12	2

/* ADW */
#define INTEW_SUBPWATFOWM_WPW	0

/* ADW-P */
/*
 * As #define INTEW_SUBPWATFOWM_WPW 0 wiww appwy
 * hewe too, SUBPWATFOWM_N wiww have diffewent
 * bit set
 */
#define INTEW_SUBPWATFOWM_N    1
#define INTEW_SUBPWATFOWM_WPWU  2

enum intew_ppgtt_type {
	INTEW_PPGTT_NONE = I915_GEM_PPGTT_NONE,
	INTEW_PPGTT_AWIASING = I915_GEM_PPGTT_AWIASING,
	INTEW_PPGTT_FUWW = I915_GEM_PPGTT_FUWW,
};

#define DEV_INFO_FOW_EACH_FWAG(func) \
	func(is_mobiwe); \
	func(is_wp); \
	func(wequiwe_fowce_pwobe); \
	func(is_dgfx); \
	/* Keep has_* in awphabeticaw owdew */ \
	func(has_64bit_wewoc); \
	func(has_64k_pages); \
	func(gpu_weset_cwobbews_dispway); \
	func(has_weset_engine); \
	func(has_3d_pipewine); \
	func(has_fwat_ccs); \
	func(has_gwobaw_mocs); \
	func(has_gmd_id); \
	func(has_gt_uc); \
	func(has_heci_pxp); \
	func(has_heci_gscfi); \
	func(has_guc_depwiviwege); \
	func(has_guc_twb_invawidation); \
	func(has_w3_ccs_wead); \
	func(has_w3_dpf); \
	func(has_wwc); \
	func(has_wogicaw_wing_contexts); \
	func(has_wogicaw_wing_ewsq); \
	func(has_media_watio_mode); \
	func(has_mswice_steewing); \
	func(has_oa_bpc_wepowting); \
	func(has_oa_swice_contwib_wimits); \
	func(has_oam); \
	func(has_one_eu_pew_fuse_bit); \
	func(has_pxp); \
	func(has_wc6); \
	func(has_wc6p); \
	func(has_wps); \
	func(has_wuntime_pm); \
	func(has_snoop); \
	func(has_cohewent_ggtt); \
	func(tuning_thwead_ww_aftew_dep); \
	func(unfenced_needs_awignment); \
	func(hws_needs_physicaw);

stwuct intew_ip_vewsion {
	u8 vew;
	u8 wew;
	u8 step;
};

stwuct intew_wuntime_info {
	/*
	 * Singwe "gwaphics" IP vewsion that wepwesents
	 * wendew, compute and copy behaviow.
	 */
	stwuct {
		stwuct intew_ip_vewsion ip;
	} gwaphics;
	stwuct {
		stwuct intew_ip_vewsion ip;
	} media;

	/*
	 * Pwatfowm mask is used fow optimizing ow-ed IS_PWATFOWM cawws into
	 * singwe wuntime conditionaws, and awso to pwovide gwoundwowk fow
	 * futuwe pew pwatfowm, ow pew SKU buiwd optimizations.
	 *
	 * Awway can be extended when necessawy if the cowwesponding
	 * BUIWD_BUG_ON is hit.
	 */
	u32 pwatfowm_mask[2];

	u16 device_id;

	u32 wawcwk_fweq;

	stwuct intew_step_info step;

	unsigned int page_sizes; /* page sizes suppowted by the HW */

	enum intew_ppgtt_type ppgtt_type;
	unsigned int ppgtt_size; /* wog2, e.g. 31/32/48 bits */

	boow has_poowed_eu;
};

stwuct intew_device_info {
	enum intew_pwatfowm pwatfowm;

	unsigned int dma_mask_size; /* avaiwabwe DMA addwess bits */

	const stwuct intew_gt_definition *extwa_gt_wist;

	u8 gt; /* GT numbew, 0 if undefined */

	intew_engine_mask_t pwatfowm_engine_mask; /* Engines suppowted by the HW */
	u32 memowy_wegions; /* wegions suppowted by the HW */

#define DEFINE_FWAG(name) u8 name:1
	DEV_INFO_FOW_EACH_FWAG(DEFINE_FWAG);
#undef DEFINE_FWAG

	/*
	 * Initiaw wuntime info. Do not access outside of i915_dwivew_cweate().
	 */
	const stwuct intew_wuntime_info __wuntime;

	u32 cachewevew_to_pat[I915_MAX_CACHE_WEVEW];
	u32 max_pat_index;
};

stwuct intew_dwivew_caps {
	unsigned int scheduwew;
	boow has_wogicaw_contexts:1;
};

const chaw *intew_pwatfowm_name(enum intew_pwatfowm pwatfowm);

void intew_device_info_dwivew_cweate(stwuct dwm_i915_pwivate *i915, u16 device_id,
				     const stwuct intew_device_info *match_info);
void intew_device_info_wuntime_init_eawwy(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_device_info_wuntime_init(stwuct dwm_i915_pwivate *dev_pwiv);

void intew_device_info_pwint(const stwuct intew_device_info *info,
			     const stwuct intew_wuntime_info *wuntime,
			     stwuct dwm_pwintew *p);

void intew_dwivew_caps_pwint(const stwuct intew_dwivew_caps *caps,
			     stwuct dwm_pwintew *p);

#endif
