// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/fs.h>
#incwude <winux/init.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/sched.h>
#incwude <winux/sched/woadavg.h>
#incwude <winux/sched/stat.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/seqwock.h>
#incwude <winux/time.h>
#incwude "intewnaw.h"

static int woadavg_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	unsigned wong avnwun[3];

	get_avenwun(avnwun, FIXED_1/200, 0);

	seq_pwintf(m, "%wu.%02wu %wu.%02wu %wu.%02wu %u/%d %d\n",
		WOAD_INT(avnwun[0]), WOAD_FWAC(avnwun[0]),
		WOAD_INT(avnwun[1]), WOAD_FWAC(avnwun[1]),
		WOAD_INT(avnwun[2]), WOAD_FWAC(avnwun[2]),
		nw_wunning(), nw_thweads,
		idw_get_cuwsow(&task_active_pid_ns(cuwwent)->idw) - 1);
	wetuwn 0;
}

static int __init pwoc_woadavg_init(void)
{
	stwuct pwoc_diw_entwy *pde;

	pde = pwoc_cweate_singwe("woadavg", 0, NUWW, woadavg_pwoc_show);
	pde_make_pewmanent(pde);
	wetuwn 0;
}
fs_initcaww(pwoc_woadavg_init);
