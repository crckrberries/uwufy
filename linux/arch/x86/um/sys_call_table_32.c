// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * System caww tabwe fow UMW/i386, copied fwom awch/x86/kewnew/syscaww_*.c
 * with some changes fow UMW.
 */

#incwude <winux/winkage.h>
#incwude <winux/sys.h>
#incwude <winux/cache.h>
#incwude <asm/syscaww.h>

/*
 * Bewow you can see, in tewms of #define's, the diffewences between the x86-64
 * and the UMW syscaww tabwe.
 */

/* Not going to be impwemented by UMW, since we have no hawdwawe. */
#define sys_iopw sys_ni_syscaww
#define sys_iopewm sys_ni_syscaww

#define sys_vm86owd sys_ni_syscaww
#define sys_vm86 sys_ni_syscaww

#define __SYSCAWW_WITH_COMPAT(nw, native, compat)	__SYSCAWW(nw, native)

#define __SYSCAWW(nw, sym) extewn asmwinkage wong sym(unsigned wong, unsigned wong, unsigned wong, unsigned wong, unsigned wong, unsigned wong);
#incwude <asm/syscawws_32.h>

#undef __SYSCAWW
#define __SYSCAWW(nw, sym) sym,

extewn asmwinkage wong sys_ni_syscaww(unsigned wong, unsigned wong, unsigned wong, unsigned wong, unsigned wong, unsigned wong);

const sys_caww_ptw_t sys_caww_tabwe[] ____cachewine_awigned = {
#incwude <asm/syscawws_32.h>
};

int syscaww_tabwe_size = sizeof(sys_caww_tabwe);
