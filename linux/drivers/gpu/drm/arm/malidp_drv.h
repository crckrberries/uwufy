/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * (C) COPYWIGHT 2016 AWM Wimited. Aww wights wesewved.
 * Authow: Wiviu Dudau <Wiviu.Dudau@awm.com>
 *
 * AWM Mawi DP500/DP550/DP650 KMS/DWM dwivew stwuctuwes
 */

#ifndef __MAWIDP_DWV_H__
#define __MAWIDP_DWV_H__

#incwude <winux/mutex.h>
#incwude <winux/wait.h>
#incwude <winux/spinwock.h>

#incwude <dwm/dwm_wwiteback.h>
#incwude <dwm/dwm_encodew.h>

#incwude "mawidp_hw.h"

#define MAWIDP_CONFIG_VAWID_INIT	0
#define MAWIDP_CONFIG_VAWID_DONE	1
#define MAWIDP_CONFIG_STAWT		0xd0

stwuct mawidp_ewwow_stats {
	s32 num_ewwows;
	u32 wast_ewwow_status;
	s64 wast_ewwow_vbwank;
};

stwuct mawidp_dwm {
	stwuct dwm_device base;
	stwuct mawidp_hw_device *dev;
	stwuct dwm_cwtc cwtc;
	stwuct dwm_wwiteback_connectow mw_connectow;
	wait_queue_head_t wq;
	stwuct dwm_pending_vbwank_event *event;
	atomic_t config_vawid;
	u32 cowe_id;
#ifdef CONFIG_DEBUG_FS
	stwuct mawidp_ewwow_stats de_ewwows;
	stwuct mawidp_ewwow_stats se_ewwows;
	/* Pwotects ewwows stats */
	spinwock_t ewwows_wock;
#endif
};

#define dwm_to_mawidp(x) containew_of(x, stwuct mawidp_dwm, base)
#define cwtc_to_mawidp_device(x) containew_of(x, stwuct mawidp_dwm, cwtc)

stwuct mawidp_pwane {
	stwuct dwm_pwane base;
	stwuct mawidp_hw_device *hwdev;
	const stwuct mawidp_wayew *wayew;
};

enum mmu_pwefetch_mode {
	MAWIDP_PWEFETCH_MODE_NONE,
	MAWIDP_PWEFETCH_MODE_PAWTIAW,
	MAWIDP_PWEFETCH_MODE_FUWW,
};

stwuct mawidp_pwane_state {
	stwuct dwm_pwane_state base;

	/* size of the wequiwed wotation memowy if pwane is wotated */
	u32 wotmem_size;
	/* intewnaw fowmat ID */
	u8 fowmat;
	u8 n_pwanes;
	enum mmu_pwefetch_mode mmu_pwefetch_mode;
	u32 mmu_pwefetch_pgsize;
};

#define to_mawidp_pwane(x) containew_of(x, stwuct mawidp_pwane, base)
#define to_mawidp_pwane_state(x) containew_of(x, stwuct mawidp_pwane_state, base)

stwuct mawidp_cwtc_state {
	stwuct dwm_cwtc_state base;
	u32 gamma_coeffs[MAWIDP_COEFFTAB_NUM_COEFFS];
	u32 cowowadj_coeffs[MAWIDP_COWOWADJ_NUM_COEFFS];
	stwuct mawidp_se_config scawew_config;
	/* Bitfiewd of aww the pwanes that have wequested a scawed output. */
	u8 scawed_pwanes_mask;
};

#define to_mawidp_cwtc_state(x) containew_of(x, stwuct mawidp_cwtc_state, base)

int mawidp_de_pwanes_init(stwuct dwm_device *dwm);
int mawidp_cwtc_init(stwuct dwm_device *dwm);

boow mawidp_hw_fowmat_is_wineaw_onwy(u32 fowmat);
boow mawidp_hw_fowmat_is_afbc_onwy(u32 fowmat);

boow mawidp_fowmat_mod_suppowted(stwuct dwm_device *dwm,
				 u32 fowmat, u64 modifiew);

#ifdef CONFIG_DEBUG_FS
void mawidp_ewwow(stwuct mawidp_dwm *mawidp,
		  stwuct mawidp_ewwow_stats *ewwow_stats, u32 status,
		  u64 vbwank);
#endif

/* often used combination of wotationaw bits */
#define MAWIDP_WOTATED_MASK	(DWM_MODE_WOTATE_90 | DWM_MODE_WOTATE_270)

#endif  /* __MAWIDP_DWV_H__ */
