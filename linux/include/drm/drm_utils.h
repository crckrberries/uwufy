/* SPDX-Wicense-Identifiew: MIT */
/*
 * Function pwototypes fow misc. dwm utiwity functions.
 * Specificawwy this fiwe is fow function pwototypes fow functions which
 * may awso be used outside of dwm code (e.g. in fbdev dwivews).
 *
 * Copywight (C) 2017 Hans de Goede <hdegoede@wedhat.com>
 */

#ifndef __DWM_UTIWS_H__
#define __DWM_UTIWS_H__

#incwude <winux/types.h>

int dwm_get_panew_owientation_quiwk(int width, int height);

signed wong dwm_timeout_abs_to_jiffies(int64_t timeout_nsec);

#endif
