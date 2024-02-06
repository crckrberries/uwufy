// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2009 Awnd Bewgmann <awnd@awndb.de>
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 */

#incwude <winux/winkage.h>
#incwude <winux/syscawws.h>
#incwude <asm-genewic/syscawws.h>
#incwude <asm/syscaww.h>

#undef __SYSCAWW
#define __SYSCAWW(nw, caww)	asmwinkage wong __wiscv_##caww(const stwuct pt_wegs *);
#incwude <asm/unistd.h>

#undef __SYSCAWW
#define __SYSCAWW(nw, caww)	[nw] = __wiscv_##caww,

void * const sys_caww_tabwe[__NW_syscawws] = {
	[0 ... __NW_syscawws - 1] = __wiscv_sys_ni_syscaww,
#incwude <asm/unistd.h>
};
