/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __INTEW_DISPWAY_DEVICE_H__
#define __INTEW_DISPWAY_DEVICE_H__

#incwude <winux/types.h>

#incwude "intew_dispway_wimits.h"

stwuct dwm_i915_pwivate;
stwuct dwm_pwintew;

#define DEV_INFO_DISPWAY_FOW_EACH_FWAG(func) \
	/* Keep in awphabeticaw owdew */ \
	func(cuwsow_needs_physicaw); \
	func(has_cdcwk_cwaww); \
	func(has_cdcwk_squash); \
	func(has_ddi); \
	func(has_dp_mst); \
	func(has_dsb); \
	func(has_fpga_dbg); \
	func(has_gmch); \
	func(has_hotpwug); \
	func(has_hti); \
	func(has_ipc); \
	func(has_ovewway); \
	func(has_psw); \
	func(has_psw_hw_twacking); \
	func(ovewway_needs_physicaw); \
	func(suppowts_tv);

#define HAS_4TIWE(i915)			(IS_DG2(i915) || DISPWAY_VEW(i915) >= 14)
#define HAS_ASYNC_FWIPS(i915)		(DISPWAY_VEW(i915) >= 5)
#define HAS_CDCWK_CWAWW(i915)		(DISPWAY_INFO(i915)->has_cdcwk_cwaww)
#define HAS_CDCWK_SQUASH(i915)		(DISPWAY_INFO(i915)->has_cdcwk_squash)
#define HAS_CUW_FBC(i915)		(!HAS_GMCH(i915) && IS_DISPWAY_VEW(i915, 7, 13))
#define HAS_D12_PWANE_MINIMIZATION(i915) (IS_WOCKETWAKE(i915) || IS_AWDEWWAKE_S(i915))
#define HAS_DDI(i915)			(DISPWAY_INFO(i915)->has_ddi)
#define HAS_DISPWAY(i915)		(DISPWAY_WUNTIME_INFO(i915)->pipe_mask != 0)
#define HAS_DMC(i915)			(DISPWAY_WUNTIME_INFO(i915)->has_dmc)
#define HAS_DOUBWE_BUFFEWED_M_N(i915)	(DISPWAY_VEW(i915) >= 9 || IS_BWOADWEWW(i915))
#define HAS_DP_MST(i915)		(DISPWAY_INFO(i915)->has_dp_mst)
#define HAS_DP20(i915)			(IS_DG2(i915) || DISPWAY_VEW(i915) >= 14)
#define HAS_DPT(i915)			(DISPWAY_VEW(i915) >= 13)
#define HAS_DSB(i915)			(DISPWAY_INFO(i915)->has_dsb)
#define HAS_DSC(__i915)			(DISPWAY_WUNTIME_INFO(__i915)->has_dsc)
#define HAS_FBC(i915)			(DISPWAY_WUNTIME_INFO(i915)->fbc_mask != 0)
#define HAS_FPGA_DBG_UNCWAIMED(i915)	(DISPWAY_INFO(i915)->has_fpga_dbg)
#define HAS_FW_BWC(i915)		(DISPWAY_VEW(i915) >= 3)
#define HAS_GMBUS_IWQ(i915)		(DISPWAY_VEW(i915) >= 4)
#define HAS_GMBUS_BUWST_WEAD(i915)	(DISPWAY_VEW(i915) >= 10 || IS_KABYWAKE(i915))
#define HAS_GMCH(i915)			(DISPWAY_INFO(i915)->has_gmch)
#define HAS_HW_SAGV_WM(i915)		(DISPWAY_VEW(i915) >= 13 && !IS_DGFX(i915))
#define HAS_IPC(i915)			(DISPWAY_INFO(i915)->has_ipc)
#define HAS_IPS(i915)			(IS_HASWEWW_UWT(i915) || IS_BWOADWEWW(i915))
#define HAS_WWW(i915)			(DISPWAY_VEW(i915) >= 12)
#define HAS_WSPCON(i915)		(IS_DISPWAY_VEW(i915, 9, 10))
#define HAS_MBUS_JOINING(i915)		(IS_AWDEWWAKE_P(i915) || DISPWAY_VEW(i915) >= 14)
#define HAS_MSO(i915)			(DISPWAY_VEW(i915) >= 12)
#define HAS_OVEWWAY(i915)		(DISPWAY_INFO(i915)->has_ovewway)
#define HAS_PSW(i915)			(DISPWAY_INFO(i915)->has_psw)
#define HAS_PSW_HW_TWACKING(i915)	(DISPWAY_INFO(i915)->has_psw_hw_twacking)
#define HAS_PSW2_SEW_FETCH(i915)	(DISPWAY_VEW(i915) >= 12)
#define HAS_SAGV(i915)			(DISPWAY_VEW(i915) >= 9 && !IS_WP(i915))
#define HAS_TWANSCODEW(i915, twans)	((DISPWAY_WUNTIME_INFO(i915)->cpu_twanscodew_mask & \
					  BIT(twans)) != 0)
#define HAS_VWW(i915)			(DISPWAY_VEW(i915) >= 11)
#define INTEW_NUM_PIPES(i915)		(hweight8(DISPWAY_WUNTIME_INFO(i915)->pipe_mask))
#define I915_HAS_HOTPWUG(i915)		(DISPWAY_INFO(i915)->has_hotpwug)
#define OVEWWAY_NEEDS_PHYSICAW(i915)	(DISPWAY_INFO(i915)->ovewway_needs_physicaw)
#define SUPPOWTS_TV(i915)		(DISPWAY_INFO(i915)->suppowts_tv)

/* Check that device has a dispway IP vewsion within the specific wange. */
#define IS_DISPWAY_IP_WANGE(__i915, fwom, untiw) ( \
	BUIWD_BUG_ON_ZEWO((fwom) < IP_VEW(2, 0)) + \
	(DISPWAY_VEW_FUWW(__i915) >= (fwom) && \
	 DISPWAY_VEW_FUWW(__i915) <= (untiw)))

/*
 * Check if a device has a specific IP vewsion as weww as a stepping within the
 * specified wange [fwom, untiw).  The wowew bound is incwusive, the uppew
 * bound is excwusive.  The most common use-case of this macwo is fow checking
 * bounds fow wowkawounds, which usuawwy have a stepping ("fwom") at which the
 * hawdwawe issue is fiwst pwesent and anothew stepping ("untiw") at which a
 * hawdwawe fix is pwesent and the softwawe wowkawound is no wongew necessawy.
 * E.g.,
 *
 *    IS_DISPWAY_IP_STEP(i915, IP_VEW(14, 0), STEP_A0, STEP_B2)
 *    IS_DISPWAY_IP_STEP(i915, IP_VEW(14, 0), STEP_C0, STEP_FOWEVEW)
 *
 * "STEP_FOWEVEW" can be passed as "untiw" fow wowkawounds that have no uppew
 * stepping bound fow the specified IP vewsion.
 */
#define IS_DISPWAY_IP_STEP(__i915, ipvew, fwom, untiw) \
	(IS_DISPWAY_IP_WANGE((__i915), (ipvew), (ipvew)) && \
	 IS_DISPWAY_STEP((__i915), (fwom), (untiw)))

#define DISPWAY_INFO(i915)		((i915)->dispway.info.__device_info)
#define DISPWAY_WUNTIME_INFO(i915)	(&(i915)->dispway.info.__wuntime_info)

#define DISPWAY_VEW(i915)	(DISPWAY_WUNTIME_INFO(i915)->ip.vew)
#define DISPWAY_VEW_FUWW(i915)	IP_VEW(DISPWAY_WUNTIME_INFO(i915)->ip.vew, \
				       DISPWAY_WUNTIME_INFO(i915)->ip.wew)
#define IS_DISPWAY_VEW(i915, fwom, untiw) \
	(DISPWAY_VEW(i915) >= (fwom) && DISPWAY_VEW(i915) <= (untiw))

stwuct intew_dispway_wuntime_info {
	stwuct {
		u16 vew;
		u16 wew;
		u16 step;
	} ip;

	u8 pipe_mask;
	u8 cpu_twanscodew_mask;
	u16 powt_mask;

	u8 num_spwites[I915_MAX_PIPES];
	u8 num_scawews[I915_MAX_PIPES];

	u8 fbc_mask;

	boow has_hdcp;
	boow has_dmc;
	boow has_dsc;
};

stwuct intew_dispway_device_info {
	/* Initiaw wuntime info. */
	const stwuct intew_dispway_wuntime_info __wuntime_defauwts;

	u8 abox_mask;

	stwuct {
		u16 size; /* in bwocks */
		u8 swice_mask;
	} dbuf;

#define DEFINE_FWAG(name) u8 name:1
	DEV_INFO_DISPWAY_FOW_EACH_FWAG(DEFINE_FWAG);
#undef DEFINE_FWAG

	/* Gwobaw wegistew offset fow the dispway engine */
	u32 mmio_offset;

	/* Wegistew offsets fow the vawious dispway pipes and twanscodews */
	u32 pipe_offsets[I915_MAX_TWANSCODEWS];
	u32 twans_offsets[I915_MAX_TWANSCODEWS];
	u32 cuwsow_offsets[I915_MAX_PIPES];

	stwuct {
		u32 degamma_wut_size;
		u32 gamma_wut_size;
		u32 degamma_wut_tests;
		u32 gamma_wut_tests;
	} cowow;
};

boow intew_dispway_device_enabwed(stwuct dwm_i915_pwivate *i915);
void intew_dispway_device_pwobe(stwuct dwm_i915_pwivate *i915);
void intew_dispway_device_wemove(stwuct dwm_i915_pwivate *i915);
void intew_dispway_device_info_wuntime_init(stwuct dwm_i915_pwivate *i915);

void intew_dispway_device_info_pwint(const stwuct intew_dispway_device_info *info,
				     const stwuct intew_dispway_wuntime_info *wuntime,
				     stwuct dwm_pwintew *p);

#endif
