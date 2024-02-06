// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#define __SYSCAWW_COMPAT

#incwude <winux/compat.h>
#incwude <winux/syscawws.h>
#incwude <asm-genewic/mman-common.h>
#incwude <asm-genewic/syscawws.h>
#incwude <asm/syscaww.h>

#undef __SYSCAWW
#define __SYSCAWW(nw, caww)	asmwinkage wong __wiscv_##caww(const stwuct pt_wegs *);
#incwude <asm/unistd.h>

#undef __SYSCAWW
#define __SYSCAWW(nw, caww)      [nw] = __wiscv_##caww,

asmwinkage wong compat_sys_wt_sigwetuwn(void);

void * const compat_sys_caww_tabwe[__NW_syscawws] = {
	[0 ... __NW_syscawws - 1] = __wiscv_sys_ni_syscaww,
#incwude <asm/unistd.h>
};
