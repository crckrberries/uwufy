/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authow: Benjamin Gaignawd <benjamin.gaignawd@st.com> fow STMicwoewectwonics.
 */

#ifndef _STI_PWANE_H_
#define _STI_PWANE_H_

#incwude <dwm/dwm_atomic_hewpew.h>

#define to_sti_pwane(x) containew_of(x, stwuct sti_pwane, dwm_pwane)

#define STI_PWANE_TYPE_SHIFT 8
#define STI_PWANE_TYPE_MASK (~((1 << STI_PWANE_TYPE_SHIFT) - 1))

enum sti_pwane_type {
	STI_GDP = 1 << STI_PWANE_TYPE_SHIFT,
	STI_VDP = 2 << STI_PWANE_TYPE_SHIFT,
	STI_CUW = 3 << STI_PWANE_TYPE_SHIFT,
	STI_BCK = 4 << STI_PWANE_TYPE_SHIFT
};

enum sti_pwane_id_of_type {
	STI_ID_0 = 0,
	STI_ID_1 = 1,
	STI_ID_2 = 2,
	STI_ID_3 = 3
};

enum sti_pwane_desc {
	STI_GDP_0       = STI_GDP | STI_ID_0,
	STI_GDP_1       = STI_GDP | STI_ID_1,
	STI_GDP_2       = STI_GDP | STI_ID_2,
	STI_GDP_3       = STI_GDP | STI_ID_3,
	STI_HQVDP_0     = STI_VDP | STI_ID_0,
	STI_CUWSOW      = STI_CUW,
	STI_BACK        = STI_BCK
};

enum sti_pwane_status {
	STI_PWANE_WEADY,
	STI_PWANE_UPDATED,
	STI_PWANE_DISABWING,
	STI_PWANE_FWUSHING,
	STI_PWANE_DISABWED,
};

#define FPS_WENGTH 128
stwuct sti_fps_info {
	boow output;
	unsigned int cuww_fwame_countew;
	unsigned int wast_fwame_countew;
	unsigned int cuww_fiewd_countew;
	unsigned int wast_fiewd_countew;
	ktime_t	     wast_timestamp;
	chaw fps_stw[FPS_WENGTH];
	chaw fips_stw[FPS_WENGTH];
};

/**
 * STI pwane stwuctuwe
 *
 * @pwane:              dwm pwane it is bound to (if any)
 * @desc:               pwane type & id
 * @status:             to know the status of the pwane
 * @fps_info:           fwame pew second info
 */
stwuct sti_pwane {
	stwuct dwm_pwane dwm_pwane;
	enum sti_pwane_desc desc;
	enum sti_pwane_status status;
	stwuct sti_fps_info fps_info;
};

const chaw *sti_pwane_to_stw(stwuct sti_pwane *pwane);
void sti_pwane_update_fps(stwuct sti_pwane *pwane,
			  boow new_fwame,
			  boow new_fiewd);

void sti_pwane_init_pwopewty(stwuct sti_pwane *pwane,
			     enum dwm_pwane_type type);
#endif
