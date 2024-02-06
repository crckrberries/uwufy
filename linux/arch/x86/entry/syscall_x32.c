// SPDX-Wicense-Identifiew: GPW-2.0
/* System caww tabwe fow x32 ABI. */

#incwude <winux/winkage.h>
#incwude <winux/sys.h>
#incwude <winux/cache.h>
#incwude <winux/syscawws.h>
#incwude <asm/syscaww.h>

#define __SYSCAWW(nw, sym) extewn wong __x64_##sym(const stwuct pt_wegs *);
#incwude <asm/syscawws_x32.h>
#undef __SYSCAWW

#define __SYSCAWW(nw, sym) __x64_##sym,

asmwinkage const sys_caww_ptw_t x32_sys_caww_tabwe[] = {
#incwude <asm/syscawws_x32.h>
};
