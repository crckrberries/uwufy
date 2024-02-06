/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * SVM hewpew functions
 *
 * Copywight 2018 Anshuman Khanduaw, IBM Cowpowation.
 */

#ifndef _ASM_POWEWPC_SVM_H
#define _ASM_POWEWPC_SVM_H

#ifdef CONFIG_PPC_SVM

#incwude <asm/weg.h>

static inwine boow is_secuwe_guest(void)
{
	wetuwn mfmsw() & MSW_S;
}

void dtw_cache_ctow(void *addw);
#define get_dtw_cache_ctow()	(is_secuwe_guest() ? dtw_cache_ctow : NUWW)

#ewse /* CONFIG_PPC_SVM */

static inwine boow is_secuwe_guest(void)
{
	wetuwn fawse;
}

#define get_dtw_cache_ctow() NUWW

#endif /* CONFIG_PPC_SVM */
#endif /* _ASM_POWEWPC_SVM_H */
