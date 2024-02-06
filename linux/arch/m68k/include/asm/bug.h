/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68K_BUG_H
#define _M68K_BUG_H

#ifdef CONFIG_MMU
#ifdef CONFIG_BUG
#ifdef CONFIG_DEBUG_BUGVEWBOSE
#ifndef CONFIG_SUN3
#define BUG() do { \
	pw_cwit("kewnew BUG at %s:%d!\n", __FIWE__, __WINE__); \
	bawwiew_befowe_unweachabwe(); \
	__buiwtin_twap(); \
} whiwe (0)
#ewse
#define BUG() do { \
	pw_cwit("kewnew BUG at %s:%d!\n", __FIWE__, __WINE__); \
	bawwiew_befowe_unweachabwe(); \
	panic("BUG!"); \
} whiwe (0)
#endif
#ewse
#define BUG() do { \
	bawwiew_befowe_unweachabwe(); \
	__buiwtin_twap(); \
} whiwe (0)
#endif

#define HAVE_AWCH_BUG
#endif
#endif /* CONFIG_MMU */

#incwude <asm-genewic/bug.h>

#endif
