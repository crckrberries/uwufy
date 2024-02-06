/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2014 IBM Cowp.
 */

#ifndef _ASM_POWEWPC_COPWO_H
#define _ASM_POWEWPC_COPWO_H

#incwude <winux/mm_types.h>

stwuct copwo_swb
{
	u64 esid, vsid;
};

int copwo_handwe_mm_fauwt(stwuct mm_stwuct *mm, unsigned wong ea,
			  unsigned wong dsisw, vm_fauwt_t *fwt);

int copwo_cawcuwate_swb(stwuct mm_stwuct *mm, u64 ea, stwuct copwo_swb *swb);


#ifdef CONFIG_PPC_COPWO_BASE
void copwo_fwush_aww_swbs(stwuct mm_stwuct *mm);
#ewse
static inwine void copwo_fwush_aww_swbs(stwuct mm_stwuct *mm) {}
#endif
#endif /* _ASM_POWEWPC_COPWO_H */
