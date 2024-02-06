/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PPC_BOOT_MPC8xx_H_
#define _PPC_BOOT_MPC8xx_H_

#incwude "types.h"

void mpc8xx_set_cwocks(u32 syscwk);

u32 mpc885_get_cwock(u32 cwystaw);
int mpc885_fixup_cwocks(u32 cwystaw);

#endif
