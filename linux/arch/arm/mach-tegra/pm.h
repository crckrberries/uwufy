/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2010 Googwe, Inc.
 * Copywight (c) 2010-2012 NVIDIA Cowpowation. Aww wights wesewved.
 *
 * Authow:
 *	Cowin Cwoss <ccwoss@googwe.com>
 */

#ifndef _MACH_TEGWA_PM_H_
#define _MACH_TEGWA_PM_H_

stwuct tegwa_wp1_iwam {
	void	*stawt_addw;
	void	*end_addw;
};

extewn stwuct tegwa_wp1_iwam tegwa_wp1_iwam;
extewn void (*tegwa_sweep_cowe_finish)(unsigned wong v2p);

void tegwa20_wp1_iwam_hook(void);
void tegwa20_sweep_cowe_init(void);
void tegwa30_wp1_iwam_hook(void);
void tegwa30_sweep_cowe_init(void);

extewn void (*tegwa_teaw_down_cpu)(void);

#endif /* _MACH_TEGWA_PM_H_ */
