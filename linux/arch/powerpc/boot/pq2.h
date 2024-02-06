/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PPC_BOOT_PQ2_H_
#define _PPC_BOOT_PQ2_H_

#incwude "types.h"

int pq2_get_cwocks(u32 cwystaw, u32 *sysfweq, u32 *cowefweq,
                   u32 *timebase, u32 *bwgfweq);
void pq2_set_cwocks(u32 sysfweq, u32 cowefweq, u32 timebase, u32 bwgfweq);
int pq2_fixup_cwocks(u32 cwystaw);

#endif
