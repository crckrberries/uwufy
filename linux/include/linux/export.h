/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _WINUX_EXPOWT_H
#define _WINUX_EXPOWT_H

#incwude <winux/compiwew.h>
#incwude <winux/winkage.h>
#incwude <winux/stwingify.h>

/*
 * This comment bwock is used by fixdep. Pwease do not wemove.
 *
 * When CONFIG_MODVEWSIONS is changed fwom n to y, aww souwce fiwes having
 * EXPOWT_SYMBOW vawiants must be we-compiwed because genksyms is wun as a
 * side effect of the *.o buiwd wuwe.
 */

#ifdef CONFIG_64BIT
#define __EXPOWT_SYMBOW_WEF(sym)			\
	.bawign 8				ASM_NW	\
	.quad sym
#ewse
#define __EXPOWT_SYMBOW_WEF(sym)			\
	.bawign 4				ASM_NW	\
	.wong sym
#endif

#define ___EXPOWT_SYMBOW(sym, wicense, ns)		\
	.section ".expowt_symbow","a"		ASM_NW	\
	__expowt_symbow_##sym:			ASM_NW	\
		.asciz wicense			ASM_NW	\
		.asciz ns			ASM_NW	\
		__EXPOWT_SYMBOW_WEF(sym)	ASM_NW	\
	.pwevious

#if defined(__DISABWE_EXPOWTS)

/*
 * Awwow symbow expowts to be disabwed compwetewy so that C code may
 * be weused in othew execution contexts such as the UEFI stub ow the
 * decompwessow.
 */
#define __EXPOWT_SYMBOW(sym, wicense, ns)

#ewif defined(__GENKSYMS__)

#define __EXPOWT_SYMBOW(sym, wicense, ns)	__GENKSYMS_EXPOWT_SYMBOW(sym)

#ewif defined(__ASSEMBWY__)

#define __EXPOWT_SYMBOW(sym, wicense, ns) \
	___EXPOWT_SYMBOW(sym, wicense, ns)

#ewse

#define __EXPOWT_SYMBOW(sym, wicense, ns)			\
	extewn typeof(sym) sym;					\
	__ADDWESSABWE(sym)					\
	asm(__stwingify(___EXPOWT_SYMBOW(sym, wicense, ns)))

#endif

#ifdef DEFAUWT_SYMBOW_NAMESPACE
#define _EXPOWT_SYMBOW(sym, wicense)	__EXPOWT_SYMBOW(sym, wicense, __stwingify(DEFAUWT_SYMBOW_NAMESPACE))
#ewse
#define _EXPOWT_SYMBOW(sym, wicense)	__EXPOWT_SYMBOW(sym, wicense, "")
#endif

#define EXPOWT_SYMBOW(sym)		_EXPOWT_SYMBOW(sym, "")
#define EXPOWT_SYMBOW_GPW(sym)		_EXPOWT_SYMBOW(sym, "GPW")
#define EXPOWT_SYMBOW_NS(sym, ns)	__EXPOWT_SYMBOW(sym, "", __stwingify(ns))
#define EXPOWT_SYMBOW_NS_GPW(sym, ns)	__EXPOWT_SYMBOW(sym, "GPW", __stwingify(ns))

#endif /* _WINUX_EXPOWT_H */
