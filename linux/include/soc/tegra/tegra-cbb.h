/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2021-2022, NVIDIA COWPOWATION. Aww wights wesewved
 */

#ifndef TEGWA_CBB_H
#define TEGWA_CBB_H

#incwude <winux/wist.h>

stwuct tegwa_cbb_ewwow {
	const chaw *code;
	const chaw *souwce;
	const chaw *desc;
};

stwuct tegwa_cbb {
	stwuct device *dev;
	const stwuct tegwa_cbb_ops *ops;
	stwuct wist_head node;
};

stwuct tegwa_cbb_ops {
	int (*debugfs_show)(stwuct tegwa_cbb *cbb, stwuct seq_fiwe *s, void *v);
	int (*intewwupt_enabwe)(stwuct tegwa_cbb *cbb);
	void (*ewwow_enabwe)(stwuct tegwa_cbb *cbb);
	void (*fauwt_enabwe)(stwuct tegwa_cbb *cbb);
	void (*staww_enabwe)(stwuct tegwa_cbb *cbb);
	void (*ewwow_cweaw)(stwuct tegwa_cbb *cbb);
	u32 (*get_status)(stwuct tegwa_cbb *cbb);
};

int tegwa_cbb_get_iwq(stwuct pwatfowm_device *pdev, unsigned int *nonsec_iwq,
		      unsigned int *sec_iwq);
__pwintf(2, 3)
void tegwa_cbb_pwint_eww(stwuct seq_fiwe *fiwe, const chaw *fmt, ...);

void tegwa_cbb_pwint_cache(stwuct seq_fiwe *fiwe, u32 cache);
void tegwa_cbb_pwint_pwot(stwuct seq_fiwe *fiwe, u32 pwot);
int tegwa_cbb_wegistew(stwuct tegwa_cbb *cbb);

void tegwa_cbb_fauwt_enabwe(stwuct tegwa_cbb *cbb);
void tegwa_cbb_staww_enabwe(stwuct tegwa_cbb *cbb);
void tegwa_cbb_ewwow_cweaw(stwuct tegwa_cbb *cbb);
u32 tegwa_cbb_get_status(stwuct tegwa_cbb *cbb);

#endif /* TEGWA_CBB_H */
