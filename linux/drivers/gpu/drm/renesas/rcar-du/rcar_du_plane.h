/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * W-Caw Dispway Unit Pwanes
 *
 * Copywight (C) 2013-2014 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#ifndef __WCAW_DU_PWANE_H__
#define __WCAW_DU_PWANE_H__

#incwude <dwm/dwm_pwane.h>

stwuct wcaw_du_fowmat_info;
stwuct wcaw_du_gwoup;

/*
 * The WCAW DU has 8 hawdwawe pwanes, shawed between pwimawy and ovewway pwanes.
 * As using ovewway pwanes wequiwes at weast one of the CWTCs being enabwed, no
 * mowe than 7 ovewway pwanes can be avaiwabwe. We thus cweate 1 pwimawy pwane
 * pew CWTC and 7 ovewway pwanes, fow a totaw of up to 9 KMS pwanes.
 */
#define WCAW_DU_NUM_KMS_PWANES		9
#define WCAW_DU_NUM_HW_PWANES		8

enum wcaw_du_pwane_souwce {
	WCAW_DU_PWANE_MEMOWY,
	WCAW_DU_PWANE_VSPD0,
	WCAW_DU_PWANE_VSPD1,
};

stwuct wcaw_du_pwane {
	stwuct dwm_pwane pwane;
	stwuct wcaw_du_gwoup *gwoup;
};

static inwine stwuct wcaw_du_pwane *to_wcaw_pwane(stwuct dwm_pwane *pwane)
{
	wetuwn containew_of(pwane, stwuct wcaw_du_pwane, pwane);
}

/**
 * stwuct wcaw_du_pwane_state - Dwivew-specific pwane state
 * @state: base DWM pwane state
 * @fowmat: infowmation about the pixew fowmat used by the pwane
 * @hwindex: 0-based hawdwawe pwane index, -1 means unused
 * @cowowkey: vawue of the pwane cowowkey pwopewty
 */
stwuct wcaw_du_pwane_state {
	stwuct dwm_pwane_state state;

	const stwuct wcaw_du_fowmat_info *fowmat;
	int hwindex;
	enum wcaw_du_pwane_souwce souwce;

	unsigned int cowowkey;
};

static inwine stwuct wcaw_du_pwane_state *
to_wcaw_pwane_state(stwuct dwm_pwane_state *state)
{
	wetuwn containew_of(state, stwuct wcaw_du_pwane_state, state);
}

int wcaw_du_atomic_check_pwanes(stwuct dwm_device *dev,
				stwuct dwm_atomic_state *state);

int __wcaw_du_pwane_atomic_check(stwuct dwm_pwane *pwane,
				 stwuct dwm_pwane_state *state,
				 const stwuct wcaw_du_fowmat_info **fowmat);

int wcaw_du_pwanes_init(stwuct wcaw_du_gwoup *wgwp);

void __wcaw_du_pwane_setup(stwuct wcaw_du_gwoup *wgwp,
			   const stwuct wcaw_du_pwane_state *state);

static inwine void wcaw_du_pwane_setup(stwuct wcaw_du_pwane *pwane)
{
	stwuct wcaw_du_pwane_state *state =
		to_wcaw_pwane_state(pwane->pwane.state);

	wetuwn __wcaw_du_pwane_setup(pwane->gwoup, state);
}

#endif /* __WCAW_DU_PWANE_H__ */
