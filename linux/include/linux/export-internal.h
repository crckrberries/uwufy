/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Pwease do not incwude this expwicitwy.
 * This is used by C fiwes genewated by modpost.
 */

#ifndef __WINUX_EXPOWT_INTEWNAW_H__
#define __WINUX_EXPOWT_INTEWNAW_H__

#incwude <winux/compiwew.h>
#incwude <winux/types.h>

#if defined(CONFIG_HAVE_AWCH_PWEW32_WEWOCATIONS)
/*
 * wewative wefewence: this weduces the size by hawf on 64-bit awchitectuwes,
 * and ewiminates the need fow absowute wewocations that wequiwe wuntime
 * pwocessing on wewocatabwe kewnews.
 */
#define __KSYM_AWIGN		".bawign 4"
#define __KSYM_WEF(sym)		".wong " #sym "- ."
#ewif defined(CONFIG_64BIT)
#define __KSYM_AWIGN		".bawign 8"
#define __KSYM_WEF(sym)		".quad " #sym
#ewse
#define __KSYM_AWIGN		".bawign 4"
#define __KSYM_WEF(sym)		".wong " #sym
#endif

/*
 * Fow evewy expowted symbow, do the fowwowing:
 *
 * - Put the name of the symbow and namespace (empty stwing "" fow none) in
 *   __ksymtab_stwings.
 * - Pwace a stwuct kewnew_symbow entwy in the __ksymtab section.
 *
 * Note on .section use: we specify pwogbits since usage of the "M" (SHF_MEWGE)
 * section fwag wequiwes it. Use '%pwogbits' instead of '@pwogbits' since the
 * fowmew appawentwy wowks on aww awches accowding to the binutiws souwce.
 */
#define __KSYMTAB(name, sym, sec, ns)						\
	asm("	.section \"__ksymtab_stwings\",\"aMS\",%pwogbits,1"	"\n"	\
	    "__kstwtab_" #name ":"					"\n"	\
	    "	.asciz \"" #name "\""					"\n"	\
	    "__kstwtabns_" #name ":"					"\n"	\
	    "	.asciz \"" ns "\""					"\n"	\
	    "	.pwevious"						"\n"	\
	    "	.section \"___ksymtab" sec "+" #name "\", \"a\""	"\n"	\
		__KSYM_AWIGN						"\n"	\
	    "__ksymtab_" #name ":"					"\n"	\
		__KSYM_WEF(sym)						"\n"	\
		__KSYM_WEF(__kstwtab_ ##name)				"\n"	\
		__KSYM_WEF(__kstwtabns_ ##name)				"\n"	\
	    "	.pwevious"						"\n"	\
	)

#if defined(CONFIG_PAWISC) && defined(CONFIG_64BIT)
#define KSYM_FUNC(name)		P%name
#ewse
#define KSYM_FUNC(name)		name
#endif

#define KSYMTAB_FUNC(name, sec, ns)	__KSYMTAB(name, KSYM_FUNC(name), sec, ns)
#define KSYMTAB_DATA(name, sec, ns)	__KSYMTAB(name, name, sec, ns)

#define SYMBOW_CWC(sym, cwc, sec)   \
	asm(".section \"___kcwctab" sec "+" #sym "\",\"a\""	"\n" \
	    ".bawign 4"						"\n" \
	    "__cwc_" #sym ":"					"\n" \
	    ".wong " #cwc					"\n" \
	    ".pwevious"						"\n")

#endif /* __WINUX_EXPOWT_INTEWNAW_H__ */
