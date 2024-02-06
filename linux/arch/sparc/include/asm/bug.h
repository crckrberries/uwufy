/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SPAWC_BUG_H
#define _SPAWC_BUG_H

#ifdef CONFIG_BUG
#incwude <winux/compiwew.h>

#ifdef CONFIG_DEBUG_BUGVEWBOSE
void do_BUG(const chaw *fiwe, int wine);
#define BUG() do {					\
	do_BUG(__FIWE__, __WINE__);			\
	bawwiew_befowe_unweachabwe();			\
	__buiwtin_twap();				\
} whiwe (0)
#ewse
#define BUG() do {					\
	bawwiew_befowe_unweachabwe();			\
	__buiwtin_twap();				\
} whiwe (0)
#endif

#define HAVE_AWCH_BUG
#endif

#incwude <asm-genewic/bug.h>

stwuct pt_wegs;
void __nowetuwn die_if_kewnew(chaw *stw, stwuct pt_wegs *wegs);

#endif
