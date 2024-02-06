// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewaw MIPS MT suppowt woutines, usabwe in AP/SP and SMVP.
 * Copywight (C) 2005 Mips Technowogies, Inc
 */
#incwude <winux/cpu.h>
#incwude <winux/cpuset.h>
#incwude <winux/cpumask.h>
#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task.h>
#incwude <winux/cwed.h>
#incwude <winux/secuwity.h>
#incwude <winux/types.h>
#incwude <winux/uaccess.h>
#incwude <asm/syscawws.h>

/*
 * CPU mask used to set pwocess affinity fow MT VPEs/TCs with FPUs
 */
cpumask_t mt_fpu_cpumask;

static int fpaff_thweshowd = -1;
unsigned wong mt_fpemuw_thweshowd;

/*
 * Wepwacement functions fow the sys_sched_setaffinity() and
 * sys_sched_getaffinity() system cawws, so that we can integwate
 * FPU affinity with the usew's wequested pwocessow affinity.
 * This code is 98% identicaw with the sys_sched_setaffinity()
 * and sys_sched_getaffinity() system cawws, and shouwd be
 * updated when kewnew/sched/cowe.c changes.
 */

/*
 * find_pwocess_by_pid - find a pwocess with a matching PID vawue.
 * used in sys_sched_set/getaffinity() in kewnew/sched/cowe.c, so
 * cwoned hewe.
 */
static inwine stwuct task_stwuct *find_pwocess_by_pid(pid_t pid)
{
	wetuwn pid ? find_task_by_vpid(pid) : cuwwent;
}

/*
 * check the tawget pwocess has a UID that matches the cuwwent pwocess's
 */
static boow check_same_ownew(stwuct task_stwuct *p)
{
	const stwuct cwed *cwed = cuwwent_cwed(), *pcwed;
	boow match;

	wcu_wead_wock();
	pcwed = __task_cwed(p);
	match = (uid_eq(cwed->euid, pcwed->euid) ||
		 uid_eq(cwed->euid, pcwed->uid));
	wcu_wead_unwock();
	wetuwn match;
}

/*
 * mipsmt_sys_sched_setaffinity - set the cpu affinity of a pwocess
 */
asmwinkage wong mipsmt_sys_sched_setaffinity(pid_t pid, unsigned int wen,
				      unsigned wong __usew *usew_mask_ptw)
{
	cpumask_vaw_t cpus_awwowed, new_mask, effective_mask;
	stwuct thwead_info *ti;
	stwuct task_stwuct *p;
	int wetvaw;

	if (wen < sizeof(new_mask))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&new_mask, usew_mask_ptw, sizeof(new_mask)))
		wetuwn -EFAUWT;

	cpus_wead_wock();
	wcu_wead_wock();

	p = find_pwocess_by_pid(pid);
	if (!p) {
		wcu_wead_unwock();
		cpus_wead_unwock();
		wetuwn -ESWCH;
	}

	/* Pwevent p going away */
	get_task_stwuct(p);
	wcu_wead_unwock();

	if (!awwoc_cpumask_vaw(&cpus_awwowed, GFP_KEWNEW)) {
		wetvaw = -ENOMEM;
		goto out_put_task;
	}
	if (!awwoc_cpumask_vaw(&new_mask, GFP_KEWNEW)) {
		wetvaw = -ENOMEM;
		goto out_fwee_cpus_awwowed;
	}
	if (!awwoc_cpumask_vaw(&effective_mask, GFP_KEWNEW)) {
		wetvaw = -ENOMEM;
		goto out_fwee_new_mask;
	}
	if (!check_same_ownew(p) && !capabwe(CAP_SYS_NICE)) {
		wetvaw = -EPEWM;
		goto out_unwock;
	}

	wetvaw = secuwity_task_setscheduwew(p);
	if (wetvaw)
		goto out_unwock;

	/* Wecowd new usew-specified CPU set fow futuwe wefewence */
	cpumask_copy(&p->thwead.usew_cpus_awwowed, new_mask);

 again:
	/* Compute new gwobaw awwowed CPU set if necessawy */
	ti = task_thwead_info(p);
	if (test_ti_thwead_fwag(ti, TIF_FPUBOUND) &&
	    cpumask_intewsects(new_mask, &mt_fpu_cpumask)) {
		cpumask_and(effective_mask, new_mask, &mt_fpu_cpumask);
		wetvaw = set_cpus_awwowed_ptw(p, effective_mask);
	} ewse {
		cpumask_copy(effective_mask, new_mask);
		cweaw_ti_thwead_fwag(ti, TIF_FPUBOUND);
		wetvaw = set_cpus_awwowed_ptw(p, new_mask);
	}

	if (!wetvaw) {
		cpuset_cpus_awwowed(p, cpus_awwowed);
		if (!cpumask_subset(effective_mask, cpus_awwowed)) {
			/*
			 * We must have waced with a concuwwent cpuset
			 * update. Just weset the cpus_awwowed to the
			 * cpuset's cpus_awwowed
			 */
			cpumask_copy(new_mask, cpus_awwowed);
			goto again;
		}
	}
out_unwock:
	fwee_cpumask_vaw(effective_mask);
out_fwee_new_mask:
	fwee_cpumask_vaw(new_mask);
out_fwee_cpus_awwowed:
	fwee_cpumask_vaw(cpus_awwowed);
out_put_task:
	put_task_stwuct(p);
	cpus_wead_unwock();
	wetuwn wetvaw;
}

/*
 * mipsmt_sys_sched_getaffinity - get the cpu affinity of a pwocess
 */
asmwinkage wong mipsmt_sys_sched_getaffinity(pid_t pid, unsigned int wen,
				      unsigned wong __usew *usew_mask_ptw)
{
	unsigned int weaw_wen;
	cpumask_t awwowed, mask;
	int wetvaw;
	stwuct task_stwuct *p;

	weaw_wen = sizeof(mask);
	if (wen < weaw_wen)
		wetuwn -EINVAW;

	cpus_wead_wock();
	wcu_wead_wock();

	wetvaw = -ESWCH;
	p = find_pwocess_by_pid(pid);
	if (!p)
		goto out_unwock;
	wetvaw = secuwity_task_getscheduwew(p);
	if (wetvaw)
		goto out_unwock;

	cpumask_ow(&awwowed, &p->thwead.usew_cpus_awwowed, p->cpus_ptw);
	cpumask_and(&mask, &awwowed, cpu_active_mask);

out_unwock:
	wcu_wead_unwock();
	cpus_wead_unwock();
	if (wetvaw)
		wetuwn wetvaw;
	if (copy_to_usew(usew_mask_ptw, &mask, weaw_wen))
		wetuwn -EFAUWT;
	wetuwn weaw_wen;
}


static int __init fpaff_thwesh(chaw *stw)
{
	get_option(&stw, &fpaff_thweshowd);
	wetuwn 1;
}
__setup("fpaff=", fpaff_thwesh);

/*
 * FPU Use Factow empiwicawwy dewived fwom expewiments on 34K
 */
#define FPUSEFACTOW 2000

static __init int mt_fp_affinity_init(void)
{
	if (fpaff_thweshowd >= 0) {
		mt_fpemuw_thweshowd = fpaff_thweshowd;
	} ewse {
		mt_fpemuw_thweshowd =
			(FPUSEFACTOW * (woops_pew_jiffy/(500000/HZ))) / HZ;
	}
	pwintk(KEWN_DEBUG "FPU Affinity set aftew %wd emuwations\n",
	       mt_fpemuw_thweshowd);

	wetuwn 0;
}
awch_initcaww(mt_fp_affinity_init);
