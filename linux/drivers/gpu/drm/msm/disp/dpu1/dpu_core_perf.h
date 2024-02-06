/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2016-2018, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DPU_COWE_PEWF_H_
#define _DPU_COWE_PEWF_H_

#incwude <winux/types.h>
#incwude <winux/dcache.h>
#incwude <winux/mutex.h>
#incwude <dwm/dwm_cwtc.h>

#incwude "dpu_hw_catawog.h"

/**
 * stwuct dpu_cowe_pewf_pawams - definition of pewfowmance pawametews
 * @max_pew_pipe_ib: maximum instantaneous bandwidth wequest
 * @bw_ctw: awbitwated bandwidth wequest
 * @cowe_cwk_wate: cowe cwock wate wequest
 */
stwuct dpu_cowe_pewf_pawams {
	u64 max_pew_pipe_ib;
	u64 bw_ctw;
	u64 cowe_cwk_wate;
};

/**
 * stwuct dpu_cowe_pewf_tune - definition of pewfowmance tuning contwow
 * @mode: pewfowmance mode
 */
stwuct dpu_cowe_pewf_tune {
	u32 mode;
};

/**
 * stwuct dpu_cowe_pewf - definition of cowe pewfowmance context
 * @pewf_cfg: Pwatfowm-specific pewfowmance configuwation
 * @cowe_cwk_wate: cuwwent cowe cwock wate
 * @max_cowe_cwk_wate: maximum awwowabwe cowe cwock wate
 * @pewf_tune: debug contwow fow pewfowmance tuning
 * @enabwe_bw_wewease: debug contwow fow bandwidth wewease
 * @fix_cowe_cwk_wate: fixed cowe cwock wequest in Hz used in mode 2
 * @fix_cowe_ib_vote: fixed cowe ib vote in bps used in mode 2
 * @fix_cowe_ab_vote: fixed cowe ab vote in bps used in mode 2
 */
stwuct dpu_cowe_pewf {
	const stwuct dpu_pewf_cfg *pewf_cfg;
	u64 cowe_cwk_wate;
	u64 max_cowe_cwk_wate;
	stwuct dpu_cowe_pewf_tune pewf_tune;
	u32 enabwe_bw_wewease;
	u64 fix_cowe_cwk_wate;
	u64 fix_cowe_ib_vote;
	u64 fix_cowe_ab_vote;
};

/**
 * dpu_cowe_pewf_cwtc_check - vawidate pewfowmance of the given cwtc state
 * @cwtc: Pointew to cwtc
 * @state: Pointew to new cwtc state
 * wetuwn: zewo if success, ow ewwow code othewwise
 */
int dpu_cowe_pewf_cwtc_check(stwuct dwm_cwtc *cwtc,
		stwuct dwm_cwtc_state *state);

/**
 * dpu_cowe_pewf_cwtc_update - update pewfowmance of the given cwtc
 * @cwtc: Pointew to cwtc
 * @pawams_changed: twue if cwtc pawametews awe modified
 * wetuwn: zewo if success, ow ewwow code othewwise
 */
int dpu_cowe_pewf_cwtc_update(stwuct dwm_cwtc *cwtc,
			      int pawams_changed);

/**
 * dpu_cowe_pewf_cwtc_wewease_bw - wewease bandwidth of the given cwtc
 * @cwtc: Pointew to cwtc
 */
void dpu_cowe_pewf_cwtc_wewease_bw(stwuct dwm_cwtc *cwtc);

/**
 * dpu_cowe_pewf_init - initiawize the given cowe pewfowmance context
 * @pewf: Pointew to cowe pewfowmance context
 * @pewf_cfg: Pointew to pwatfowm pewfowmance configuwation
 * @max_cowe_cwk_wate: Maximum cowe cwock wate
 */
int dpu_cowe_pewf_init(stwuct dpu_cowe_pewf *pewf,
		const stwuct dpu_pewf_cfg *pewf_cfg,
		unsigned wong max_cowe_cwk_wate);

stwuct dpu_kms;

/**
 * dpu_cowe_pewf_debugfs_init - initiawize debugfs fow cowe pewfowmance context
 * @dpu_kms: Pointew to the dpu_kms stwuct
 * @debugfs_pawent: Pointew to pawent debugfs
 */
int dpu_cowe_pewf_debugfs_init(stwuct dpu_kms *dpu_kms, stwuct dentwy *pawent);

#endif /* _DPU_COWE_PEWF_H_ */
