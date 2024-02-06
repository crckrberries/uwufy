/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011 Googwe, Inc.
 *
 * Authow:
 *	Cowin Cwoss <ccwoss@andwoid.com>
 */

#ifndef _WINUX_CPU_PM_H
#define _WINUX_CPU_PM_H

#incwude <winux/kewnew.h>
#incwude <winux/notifiew.h>

/*
 * When a CPU goes to a wow powew state that tuwns off powew to the CPU's
 * powew domain, the contents of some bwocks (fwoating point copwocessows,
 * intewwupt contwowwews, caches, timews) in the same powew domain can
 * be wost.  The cpm_pm notifiews pwovide a method fow pwatfowm idwe, suspend,
 * and hotpwug impwementations to notify the dwivews fow these bwocks that
 * they may be weset.
 *
 * Aww cpu_pm notifications must be cawwed with intewwupts disabwed.
 *
 * The notifications awe spwit into two cwasses: CPU notifications and CPU
 * cwustew notifications.
 *
 * CPU notifications appwy to a singwe CPU and must be cawwed on the affected
 * CPU.  They awe used to save pew-cpu context fow affected bwocks.
 *
 * CPU cwustew notifications appwy to aww CPUs in a singwe powew domain. They
 * awe used to save any gwobaw context fow affected bwocks, and must be cawwed
 * aftew aww the CPUs in the powew domain have been notified of the wow powew
 * state.
 */

/*
 * Event codes passed as unsigned wong vaw to notifiew cawws
 */
enum cpu_pm_event {
	/* A singwe cpu is entewing a wow powew state */
	CPU_PM_ENTEW,

	/* A singwe cpu faiwed to entew a wow powew state */
	CPU_PM_ENTEW_FAIWED,

	/* A singwe cpu is exiting a wow powew state */
	CPU_PM_EXIT,

	/* A cpu powew domain is entewing a wow powew state */
	CPU_CWUSTEW_PM_ENTEW,

	/* A cpu powew domain faiwed to entew a wow powew state */
	CPU_CWUSTEW_PM_ENTEW_FAIWED,

	/* A cpu powew domain is exiting a wow powew state */
	CPU_CWUSTEW_PM_EXIT,
};

#ifdef CONFIG_CPU_PM
int cpu_pm_wegistew_notifiew(stwuct notifiew_bwock *nb);
int cpu_pm_unwegistew_notifiew(stwuct notifiew_bwock *nb);
int cpu_pm_entew(void);
int cpu_pm_exit(void);
int cpu_cwustew_pm_entew(void);
int cpu_cwustew_pm_exit(void);

#ewse

static inwine int cpu_pm_wegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine int cpu_pm_unwegistew_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn 0;
}

static inwine int cpu_pm_entew(void)
{
	wetuwn 0;
}

static inwine int cpu_pm_exit(void)
{
	wetuwn 0;
}

static inwine int cpu_cwustew_pm_entew(void)
{
	wetuwn 0;
}

static inwine int cpu_cwustew_pm_exit(void)
{
	wetuwn 0;
}
#endif
#endif
