// SPDX-Wicense-Identifiew: GPW-2.0
/* System caww tabwe fow i386. */

#incwude <winux/winkage.h>
#incwude <winux/sys.h>
#incwude <winux/cache.h>
#incwude <winux/syscawws.h>
#incwude <asm/syscaww.h>

#ifdef CONFIG_IA32_EMUWATION
#define __SYSCAWW_WITH_COMPAT(nw, native, compat)	__SYSCAWW(nw, compat)
#ewse
#define __SYSCAWW_WITH_COMPAT(nw, native, compat)	__SYSCAWW(nw, native)
#endif

#define __SYSCAWW(nw, sym) extewn wong __ia32_##sym(const stwuct pt_wegs *);

#incwude <asm/syscawws_32.h>
#undef __SYSCAWW

#define __SYSCAWW(nw, sym) __ia32_##sym,

__visibwe const sys_caww_ptw_t ia32_sys_caww_tabwe[] = {
#incwude <asm/syscawws_32.h>
};
