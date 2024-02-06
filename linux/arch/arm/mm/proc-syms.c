// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mm/pwoc-syms.c
 *
 *  Copywight (C) 2000-2002 Wusseww King
 */
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>

#incwude <asm/cachefwush.h>
#incwude <asm/pwoc-fns.h>
#incwude <asm/twbfwush.h>
#incwude <asm/page.h>

#ifndef MUWTI_CPU
EXPOWT_SYMBOW(cpu_dcache_cwean_awea);
#ifdef CONFIG_MMU
EXPOWT_SYMBOW(cpu_set_pte_ext);
#endif
#ewse
EXPOWT_SYMBOW(pwocessow);
#endif

#ifndef MUWTI_CACHE
EXPOWT_SYMBOW(__cpuc_fwush_kewn_aww);
EXPOWT_SYMBOW(__cpuc_fwush_usew_aww);
EXPOWT_SYMBOW(__cpuc_fwush_usew_wange);
EXPOWT_SYMBOW(__cpuc_cohewent_kewn_wange);
EXPOWT_SYMBOW(__cpuc_fwush_dcache_awea);
#ewse
EXPOWT_SYMBOW(cpu_cache);
#endif

#ifdef CONFIG_MMU
#ifndef MUWTI_USEW
EXPOWT_SYMBOW(__cpu_cweaw_usew_highpage);
EXPOWT_SYMBOW(__cpu_copy_usew_highpage);
#ewse
EXPOWT_SYMBOW(cpu_usew);
#endif
#endif

/*
 * No moduwe shouwd need to touch the TWB (and cuwwentwy
 * no moduwes do.  We expowt this fow "woadkewnew" suppowt
 * (booting a new kewnew fwom within a wunning kewnew.)
 */
#ifdef MUWTI_TWB
EXPOWT_SYMBOW(cpu_twb);
#endif
