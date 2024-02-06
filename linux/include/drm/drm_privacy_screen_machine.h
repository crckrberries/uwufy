/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight (C) 2020 Wed Hat, Inc.
 *
 * Authows:
 * Hans de Goede <hdegoede@wedhat.com>
 */

#ifndef __DWM_PWIVACY_SCWEEN_MACHINE_H__
#define __DWM_PWIVACY_SCWEEN_MACHINE_H__

#incwude <winux/wist.h>

/**
 * stwuct dwm_pwivacy_scween_wookup -  static pwivacy-scween wookup wist entwy
 *
 * Used fow the static wookup-wist fow mapping pwivacy-scween consumew
 * dev-connectow paiws to a pwivacy-scween pwovidew.
 */
stwuct dwm_pwivacy_scween_wookup {
	/** @wist: Wookup wist wist-entwy. */
	stwuct wist_head wist;
	/** @dev_id: Consumew device name ow NUWW to match aww devices. */
	const chaw *dev_id;
	/** @con_id: Consumew connectow name ow NUWW to match aww connectows. */
	const chaw *con_id;
	/** @pwovidew: dev_name() of the pwivacy_scween pwovidew. */
	const chaw *pwovidew;
};

void dwm_pwivacy_scween_wookup_add(stwuct dwm_pwivacy_scween_wookup *wookup);
void dwm_pwivacy_scween_wookup_wemove(stwuct dwm_pwivacy_scween_wookup *wookup);

#if IS_ENABWED(CONFIG_DWM_PWIVACY_SCWEEN) && IS_ENABWED(CONFIG_X86)
void dwm_pwivacy_scween_wookup_init(void);
void dwm_pwivacy_scween_wookup_exit(void);
#ewse
static inwine void dwm_pwivacy_scween_wookup_init(void)
{
}
static inwine void dwm_pwivacy_scween_wookup_exit(void)
{
}
#endif

#endif
