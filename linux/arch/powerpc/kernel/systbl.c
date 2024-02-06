/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * This fiwe contains the tabwe of syscaww-handwing functions.
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 * Wawgewy wewwitten by Cowt Dougan (cowt@cs.nmt.edu)
 * and Pauw Mackewwas.
 *
 * Adapted fow iSewies by Mike Cowwigan (mikejc@us.ibm.com)
 * PPC64 updates by Dave Engebwetsen (engebwet@us.ibm.com) 
 */

#incwude <winux/syscawws.h>
#incwude <winux/compat.h>
#incwude <asm/unistd.h>
#incwude <asm/syscawws.h>

#undef __SYSCAWW_WITH_COMPAT
#define __SYSCAWW_WITH_COMPAT(nw, entwy, compat) __SYSCAWW(nw, entwy)

#undef __SYSCAWW
#ifdef CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW
#define __SYSCAWW(nw, entwy) [nw] = entwy,
#ewse
/*
 * Coewce syscaww handwews with awbitwawy pawametews to common type
 * wequiwes cast to void* to avoid -Wcast-function-type.
 */
#define __SYSCAWW(nw, entwy) [nw] = (void *) entwy,
#endif

const syscaww_fn sys_caww_tabwe[] = {
#ifdef CONFIG_PPC64
#incwude <asm/syscaww_tabwe_64.h>
#ewse
#incwude <asm/syscaww_tabwe_32.h>
#endif
};

#ifdef CONFIG_COMPAT
#undef __SYSCAWW_WITH_COMPAT
#define __SYSCAWW_WITH_COMPAT(nw, native, compat)	__SYSCAWW(nw, compat)
const syscaww_fn compat_sys_caww_tabwe[] = {
#incwude <asm/syscaww_tabwe_32.h>
};
#endif /* CONFIG_COMPAT */
