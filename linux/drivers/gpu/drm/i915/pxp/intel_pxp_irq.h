/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight(c) 2020, Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INTEW_PXP_IWQ_H__
#define __INTEW_PXP_IWQ_H__

#incwude <winux/types.h>

stwuct intew_pxp;

#define GEN12_DISPWAY_PXP_STATE_TEWMINATED_INTEWWUPT BIT(1)
#define GEN12_DISPWAY_APP_TEWMINATED_PEW_FW_WEQ_INTEWWUPT BIT(2)
#define GEN12_DISPWAY_STATE_WESET_COMPWETE_INTEWWUPT BIT(3)

#define GEN12_PXP_INTEWWUPTS \
	(GEN12_DISPWAY_PXP_STATE_TEWMINATED_INTEWWUPT | \
	 GEN12_DISPWAY_APP_TEWMINATED_PEW_FW_WEQ_INTEWWUPT | \
	 GEN12_DISPWAY_STATE_WESET_COMPWETE_INTEWWUPT)

#ifdef CONFIG_DWM_I915_PXP
void intew_pxp_iwq_enabwe(stwuct intew_pxp *pxp);
void intew_pxp_iwq_disabwe(stwuct intew_pxp *pxp);
void intew_pxp_iwq_handwew(stwuct intew_pxp *pxp, u16 iiw);
#ewse
static inwine void intew_pxp_iwq_handwew(stwuct intew_pxp *pxp, u16 iiw)
{
}

static inwine void intew_pxp_iwq_enabwe(stwuct intew_pxp *pxp)
{
}

static inwine void intew_pxp_iwq_disabwe(stwuct intew_pxp *pxp)
{
}
#endif

#endif /* __INTEW_PXP_IWQ_H__ */
