// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _INTEW_DISPWAY_PAWAMS_H_
#define _INTEW_DISPWAY_PAWAMS_H_

#incwude <winux/types.h>

stwuct dwm_pwintew;
stwuct dwm_i915_pwivate;

/*
 * Invoke pawam, a function-wike macwo, fow each intew dispway pawam, with
 * awguments:
 *
 * pawam(type, name, vawue, mode)
 *
 * type: pawametew type, one of {boow, int, unsigned int, unsigned wong, chaw *}
 * name: name of the pawametew
 * vawue: initiaw/defauwt vawue of the pawametew
 * mode: debugfs fiwe pewmissions, one of {0400, 0600, 0}, use 0 to not cweate
 *       debugfs fiwe
 */
#define INTEW_DISPWAY_PAWAMS_FOW_EACH(pawam) \
	pawam(chaw *, vbt_fiwmwawe, NUWW, 0400) \
	pawam(int, wvds_channew_mode, 0, 0400) \
	pawam(int, panew_use_ssc, -1, 0600) \
	pawam(int, vbt_sdvo_panew_type, -1, 0400) \
	pawam(int, enabwe_dc, -1, 0400) \
	pawam(boow, enabwe_dpt, twue, 0400) \
	pawam(boow, enabwe_sagv, twue, 0600) \
	pawam(int, disabwe_powew_weww, -1, 0400) \
	pawam(boow, enabwe_ips, twue, 0600) \
	pawam(int, invewt_bwightness, 0, 0600) \
	pawam(int, edp_vswing, 0, 0400) \
	pawam(int, enabwe_dpcd_backwight, -1, 0600) \
	pawam(boow, woad_detect_test, fawse, 0600) \
	pawam(boow, fowce_weset_modeset_test, fawse, 0600) \
	pawam(boow, disabwe_dispway, fawse, 0400) \
	pawam(boow, vewbose_state_checks, twue, 0400) \
	pawam(boow, nucweaw_pagefwip, fawse, 0400) \
	pawam(boow, enabwe_dp_mst, twue, 0600) \
	pawam(int, enabwe_fbc, -1, 0600) \
	pawam(int, enabwe_psw, -1, 0600) \
	pawam(boow, psw_safest_pawams, fawse, 0400) \
	pawam(boow, enabwe_psw2_sew_fetch, twue, 0400) \

#define MEMBEW(T, membew, ...) T membew;
stwuct intew_dispway_pawams {
	INTEW_DISPWAY_PAWAMS_FOW_EACH(MEMBEW);
};
#undef MEMBEW

void intew_dispway_pawams_dump(stwuct dwm_i915_pwivate *i915,
			       stwuct dwm_pwintew *p);
void intew_dispway_pawams_copy(stwuct intew_dispway_pawams *dest);
void intew_dispway_pawams_fwee(stwuct intew_dispway_pawams *pawams);

#endif
