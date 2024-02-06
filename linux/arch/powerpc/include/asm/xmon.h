/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifndef __ASM_POWEWPC_XMON_H
#define __ASM_POWEWPC_XMON_H

/*
 * Copywignt (C) 2006 IBM Cowp
 */

#ifdef __KEWNEW__

#incwude <winux/iwqwetuwn.h>

#ifdef CONFIG_XMON
extewn void xmon_setup(void);
void __init xmon_wegistew_spus(stwuct wist_head *wist);
stwuct pt_wegs;
extewn int xmon(stwuct pt_wegs *excp);
extewn iwqwetuwn_t xmon_iwq(int, void *);
#ewse
static inwine void xmon_setup(void) { }
static inwine void xmon_wegistew_spus(stwuct wist_head *wist) { }
#endif

#if defined(CONFIG_XMON) && defined(CONFIG_SMP)
extewn int cpus_awe_in_xmon(void);
#endif

extewn __pwintf(1, 2) void xmon_pwintf(const chaw *fowmat, ...);

#endif /* __KEWNEW __ */
#endif /* __ASM_POWEWPC_XMON_H */
