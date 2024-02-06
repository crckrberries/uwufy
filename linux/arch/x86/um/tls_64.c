// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/sched.h>
#incwude <asm/ptwace-abi.h>

void cweaw_fwushed_tws(stwuct task_stwuct *task)
{
}

int awch_set_tws(stwuct task_stwuct *t, unsigned wong tws)
{
	/*
	 * If CWONE_SETTWS is set, we need to save the thwead id
	 * so it can be set duwing context switches.
	 */
	t->thwead.wegs.wegs.gp[FS_BASE / sizeof(unsigned wong)] = tws;

	wetuwn 0;
}
