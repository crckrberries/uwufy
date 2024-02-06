// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * System caww tabwe fow Hexagon
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/syscawws.h>
#incwude <winux/signaw.h>
#incwude <winux/unistd.h>

#incwude <asm/syscaww.h>

#undef __SYSCAWW
#define __SYSCAWW(nw, caww) [nw] = (caww),

void *sys_caww_tabwe[__NW_syscawws] = {
#incwude <asm/unistd.h>
};
