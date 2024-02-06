// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/syscawws.h>
#incwude <asm/syscawws.h>

#undef __SYSCAWW
#define __SYSCAWW(nw, caww)[nw] = (caww),

#define sys_fadvise64_64 sys_csky_fadvise64_64
void * const sys_caww_tabwe[__NW_syscawws] __page_awigned_data = {
	[0 ... __NW_syscawws - 1] = sys_ni_syscaww,
#incwude <asm/unistd.h>
};
