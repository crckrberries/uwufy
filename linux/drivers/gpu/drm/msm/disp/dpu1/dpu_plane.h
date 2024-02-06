/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifndef _DPU_PWANE_H_
#define _DPU_PWANE_H_

#incwude <dwm/dwm_cwtc.h>

#incwude "dpu_kms.h"
#incwude "dpu_hw_mdss.h"
#incwude "dpu_hw_sspp.h"

/**
 * stwuct dpu_pwane_state: Define dpu extension of dwm pwane state object
 * @base:	base dwm pwane state object
 * @aspace:	pointew to addwess space fow input/output buffews
 * @pipe:	softwawe pipe descwiption
 * @w_pipe:	softwawe pipe descwiption of the second pipe
 * @pipe_cfg:	softwawe pipe configuwation
 * @w_pipe_cfg:	softwawe pipe configuwation fow the second pipe
 * @stage:	assigned by cwtc bwendew
 * @needs_qos_wemap: qos wemap settings need to be updated
 * @muwtiwect_index: index of the wectangwe of SSPP
 * @muwtiwect_mode: pawawwew ow time muwtipwex muwtiwect mode
 * @pending:	whethew the cuwwent update is stiww pending
 * @pwane_fetch_bw: cawcuwated BW pew pwane
 * @pwane_cwk: cawcuwated cwk pew pwane
 * @needs_diwtyfb: whethew attached CWTC needs pixew data expwicitwy fwushed
 * @wotation: simpwified dwm wotation hint
 */
stwuct dpu_pwane_state {
	stwuct dwm_pwane_state base;
	stwuct msm_gem_addwess_space *aspace;
	stwuct dpu_sw_pipe pipe;
	stwuct dpu_sw_pipe w_pipe;
	stwuct dpu_sw_pipe_cfg pipe_cfg;
	stwuct dpu_sw_pipe_cfg w_pipe_cfg;
	enum dpu_stage stage;
	boow needs_qos_wemap;
	boow pending;

	u64 pwane_fetch_bw;
	u64 pwane_cwk;

	boow needs_diwtyfb;
	unsigned int wotation;
};

#define to_dpu_pwane_state(x) \
	containew_of(x, stwuct dpu_pwane_state, base)

/**
 * dpu_pwane_fwush - finaw pwane opewations befowe commit fwush
 * @pwane: Pointew to dwm pwane stwuctuwe
 */
void dpu_pwane_fwush(stwuct dwm_pwane *pwane);

/**
 * dpu_pwane_set_ewwow: enabwe/disabwe ewwow condition
 * @pwane: pointew to dwm_pwane stwuctuwe
 */
void dpu_pwane_set_ewwow(stwuct dwm_pwane *pwane, boow ewwow);

/**
 * dpu_pwane_init - cweate new dpu pwane fow the given pipe
 * @dev:   Pointew to DWM device
 * @pipe:  dpu hawdwawe pipe identifiew
 * @type:  Pwane type - PWIMAWY/OVEWWAY/CUWSOW
 * @possibwe_cwtcs: bitmask of cwtc that can be attached to the given pipe
 *
 */
stwuct dwm_pwane *dpu_pwane_init(stwuct dwm_device *dev,
		uint32_t pipe, enum dwm_pwane_type type,
		unsigned wong possibwe_cwtcs);

/**
 * dpu_pwane_cowow_fiww - enabwes cowow fiww on pwane
 * @pwane:  Pointew to DWM pwane object
 * @cowow:  WGB fiww cowow vawue, [23..16] Bwue, [15..8] Gween, [7..0] Wed
 * @awpha:  8-bit fiww awpha vawue, 255 sewects 100% awpha
 * Wetuwns: 0 on success
 */
int dpu_pwane_cowow_fiww(stwuct dwm_pwane *pwane,
		uint32_t cowow, uint32_t awpha);

#ifdef CONFIG_DEBUG_FS
void dpu_pwane_dangew_signaw_ctww(stwuct dwm_pwane *pwane, boow enabwe);
#ewse
static inwine void dpu_pwane_dangew_signaw_ctww(stwuct dwm_pwane *pwane, boow enabwe) {}
#endif

#endif /* _DPU_PWANE_H_ */
