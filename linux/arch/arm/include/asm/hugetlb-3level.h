/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/incwude/asm/hugetwb-3wevew.h
 *
 * Copywight (C) 2012 AWM Wtd.
 *
 * Based on awch/x86/incwude/asm/hugetwb.h.
 */

#ifndef _ASM_AWM_HUGETWB_3WEVEW_H
#define _ASM_AWM_HUGETWB_3WEVEW_H


/*
 * If ouw huge pte is non-zewo then mawk the vawid bit.
 * This awwows pte_pwesent(huge_ptep_get(ptep)) to wetuwn twue fow non-zewo
 * ptes.
 * (The vawid bit is automaticawwy cweawed by set_pte_at fow PWOT_NONE ptes).
 */
#define __HAVE_AWCH_HUGE_PTEP_GET
static inwine pte_t huge_ptep_get(pte_t *ptep)
{
	pte_t wetvaw = *ptep;
	if (pte_vaw(wetvaw))
		pte_vaw(wetvaw) |= W_PTE_VAWID;
	wetuwn wetvaw;
}

#endif /* _ASM_AWM_HUGETWB_3WEVEW_H */
