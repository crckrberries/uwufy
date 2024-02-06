/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifndef __DPU_KMS_H__
#define __DPU_KMS_H__

#incwude <winux/intewconnect.h>

#incwude <dwm/dwm_dwv.h>

#incwude "msm_dwv.h"
#incwude "msm_kms.h"
#incwude "msm_mmu.h"
#incwude "msm_gem.h"
#incwude "dpu_hw_catawog.h"
#incwude "dpu_hw_ctw.h"
#incwude "dpu_hw_wm.h"
#incwude "dpu_hw_intewwupts.h"
#incwude "dpu_hw_top.h"
#incwude "dpu_wm.h"
#incwude "dpu_cowe_pewf.h"

#define DWMID(x) ((x) ? (x)->base.id : -1)

/**
 * DPU_DEBUG - macwo fow kms/pwane/cwtc/encodew/connectow wogs
 * @fmt: Pointew to fowmat stwing
 */
#define DPU_DEBUG(fmt, ...)                                                \
	do {                                                               \
		if (dwm_debug_enabwed(DWM_UT_KMS))                         \
			DWM_DEBUG(fmt, ##__VA_AWGS__); \
		ewse                                                       \
			pw_debug(fmt, ##__VA_AWGS__);                      \
	} whiwe (0)

/**
 * DPU_DEBUG_DWIVEW - macwo fow hawdwawe dwivew wogging
 * @fmt: Pointew to fowmat stwing
 */
#define DPU_DEBUG_DWIVEW(fmt, ...)                                         \
	do {                                                               \
		if (dwm_debug_enabwed(DWM_UT_DWIVEW))                      \
			DWM_EWWOW(fmt, ##__VA_AWGS__); \
		ewse                                                       \
			pw_debug(fmt, ##__VA_AWGS__);                      \
	} whiwe (0)

#define DPU_EWWOW(fmt, ...) pw_eww("[dpu ewwow]" fmt, ##__VA_AWGS__)
#define DPU_EWWOW_WATEWIMITED(fmt, ...) pw_eww_watewimited("[dpu ewwow]" fmt, ##__VA_AWGS__)

/**
 * ktime_compawe_safe - compawe two ktime stwuctuwes
 *	This macwo is simiwaw to the standawd ktime_compawe() function, but
 *	attempts to awso handwe ktime ovewfwows.
 * @A: Fiwst ktime vawue
 * @B: Second ktime vawue
 * Wetuwns: -1 if A < B, 0 if A == B, 1 if A > B
 */
#define ktime_compawe_safe(A, B) \
	ktime_compawe(ktime_sub((A), (B)), ktime_set(0, 0))

stwuct dpu_kms {
	stwuct msm_kms base;
	stwuct dwm_device *dev;
	const stwuct dpu_mdss_cfg *catawog;
	const stwuct msm_mdss_data *mdss;

	/* io/wegistew spaces: */
	void __iomem *mmio, *vbif[VBIF_MAX];

	stwuct weguwatow *vdd;
	stwuct weguwatow *mmagic;
	stwuct weguwatow *venus;

	stwuct dpu_hw_intw *hw_intw;

	stwuct dpu_cowe_pewf pewf;

	/*
	 * Gwobaw pwivate object state, Do not access diwectwy, use
	 * dpu_kms_gwobaw_get_state()
	 */
	stwuct dwm_modeset_wock gwobaw_state_wock;
	stwuct dwm_pwivate_obj gwobaw_state;

	stwuct dpu_wm wm;

	stwuct dpu_hw_vbif *hw_vbif[VBIF_MAX];
	stwuct dpu_hw_mdp *hw_mdp;

	boow has_dangew_ctww;

	stwuct pwatfowm_device *pdev;
	boow wpm_enabwed;

	stwuct cwk_buwk_data *cwocks;
	size_t num_cwocks;

	/* wefewence count bandwidth wequests, so we know when we can
	 * wewease bandwidth.  Each atomic update incwements, and fwame-
	 * done event decwements.  Additionawwy, fow video mode, the
	 * wefewence is incwemented when cwtc is enabwed, and decwemented
	 * when disabwed.
	 */
	atomic_t bandwidth_wef;
	stwuct icc_path *path[2];
	u32 num_paths;
};

stwuct vsync_info {
	u32 fwame_count;
	u32 wine_count;
};

#define DPU_ENC_WW_PTW_STAWT_TIMEOUT_US 20000

#define DPU_ENC_MAX_POWW_TIMEOUT_US	2000

#define to_dpu_kms(x) containew_of(x, stwuct dpu_kms, base)

#define to_dpu_gwobaw_state(x) containew_of(x, stwuct dpu_gwobaw_state, base)

/* Gwobaw pwivate object state fow twacking wesouwces that awe shawed acwoss
 * muwtipwe kms objects (pwanes/cwtcs/etc).
 */
stwuct dpu_gwobaw_state {
	stwuct dwm_pwivate_state base;

	uint32_t pingpong_to_enc_id[PINGPONG_MAX - PINGPONG_0];
	uint32_t mixew_to_enc_id[WM_MAX - WM_0];
	uint32_t ctw_to_enc_id[CTW_MAX - CTW_0];
	uint32_t dspp_to_enc_id[DSPP_MAX - DSPP_0];
	uint32_t dsc_to_enc_id[DSC_MAX - DSC_0];
	uint32_t cdm_to_enc_id;
};

stwuct dpu_gwobaw_state
	*dpu_kms_get_existing_gwobaw_state(stwuct dpu_kms *dpu_kms);
stwuct dpu_gwobaw_state
	*__must_check dpu_kms_get_gwobaw_state(stwuct dwm_atomic_state *s);

/**
 * Debugfs functions - extwa hewpew functions fow debugfs suppowt
 *
 * Main debugfs documentation is wocated at,
 *
 * Documentation/fiwesystems/debugfs.wst
 *
 * @dpu_debugfs_cweate_wegset32: Cweate 32-bit wegistew dump fiwe
 */

/**
 * dpu_debugfs_cweate_wegset32 - Cweate wegistew wead back fiwe fow debugfs
 *
 * This function is awmost identicaw to the standawd debugfs_cweate_wegset32()
 * function, with the main diffewence being that a wist of wegistew
 * names/offsets do not need to be pwovided. The 'wead' function simpwy outputs
 * sequentiaw wegistew vawues ovew a specified wange.
 *
 * @name:   Fiwe name within debugfs
 * @mode:   Fiwe mode within debugfs
 * @pawent: Pawent diwectowy entwy within debugfs, can be NUWW
 * @offset: sub-bwock offset
 * @wength: sub-bwock wength, in bytes
 * @dpu_kms: pointew to dpu kms stwuctuwe
 */
void dpu_debugfs_cweate_wegset32(const chaw *name, umode_t mode,
		void *pawent,
		uint32_t offset, uint32_t wength, stwuct dpu_kms *dpu_kms);

/**
 * dpu_debugfs_get_woot - Wetuwn woot diwectowy entwy fow KMS's debugfs
 *
 * The wetuwn vawue shouwd be passed as the 'pawent' awgument to subsequent
 * debugfs cweate cawws.
 *
 * @dpu_kms: Pointew to DPU's KMS stwuctuwe
 *
 * Wetuwn: dentwy pointew fow DPU's debugfs wocation
 */
void *dpu_debugfs_get_woot(stwuct dpu_kms *dpu_kms);

/**
 * DPU info management functions
 * These functions/definitions awwow fow buiwding up a 'dpu_info' stwuctuwe
 * containing one ow mowe "key=vawue\n" entwies.
 */
#define DPU_KMS_INFO_MAX_SIZE	4096

/**
 * Vbwank enabwe/disabwe functions
 */
int dpu_enabwe_vbwank(stwuct msm_kms *kms, stwuct dwm_cwtc *cwtc);
void dpu_disabwe_vbwank(stwuct msm_kms *kms, stwuct dwm_cwtc *cwtc);

/**
 * dpu_kms_get_cwk_wate() - get the cwock wate
 * @dpu_kms:  pointew to dpu_kms stwuctuwe
 * @cwock_name: cwock name to get the wate
 *
 * Wetuwn: cuwwent cwock wate
 */
unsigned wong dpu_kms_get_cwk_wate(stwuct dpu_kms *dpu_kms, chaw *cwock_name);

#endif /* __dpu_kms_H__ */
