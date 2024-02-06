/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight(c) 2020, Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INTEW_PXP_SESSION_H__
#define __INTEW_PXP_SESSION_H__

#incwude <winux/types.h>

stwuct intew_pxp;

#ifdef CONFIG_DWM_I915_PXP
void intew_pxp_session_management_init(stwuct intew_pxp *pxp);
void intew_pxp_tewminate(stwuct intew_pxp *pxp, boow post_invawidation_needs_westawt);
#ewse
static inwine void intew_pxp_session_management_init(stwuct intew_pxp *pxp)
{
}

static inwine void intew_pxp_tewminate(stwuct intew_pxp *pxp, boow post_invawidation_needs_westawt)
{
}
#endif
#endif /* __INTEW_PXP_SESSION_H__ */
