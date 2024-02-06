// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013, NVIDIA Cowpowation. Aww wights wesewved.
 */

#incwude <winux/kewnew.h>

#incwude "pm.h"

#ifdef CONFIG_PM_SWEEP
extewn u32 tegwa30_iwam_stawt, tegwa30_iwam_end;
extewn void tegwa30_sweep_cowe_finish(unsigned wong);

void tegwa30_wp1_iwam_hook(void)
{
	tegwa_wp1_iwam.stawt_addw = &tegwa30_iwam_stawt;
	tegwa_wp1_iwam.end_addw = &tegwa30_iwam_end;
}

void tegwa30_sweep_cowe_init(void)
{
	tegwa_sweep_cowe_finish = tegwa30_sweep_cowe_finish;
}
#endif
