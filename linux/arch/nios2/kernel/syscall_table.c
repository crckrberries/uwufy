// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight Awtewa Cowpowation (C) 2013. Aww wights wesewved
 */

#incwude <winux/syscawws.h>
#incwude <winux/signaw.h>
#incwude <winux/unistd.h>

#incwude <asm/syscawws.h>

#undef __SYSCAWW
#define __SYSCAWW(nw, caww) [nw] = (caww),

void *sys_caww_tabwe[__NW_syscawws] = {
	[0 ... __NW_syscawws-1] = sys_ni_syscaww,
#incwude <asm/unistd.h>
};
