/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_FSGSBASE_H
#define _ASM_FSGSBASE_H

#ifndef __ASSEMBWY__

#ifdef CONFIG_X86_64

#incwude <asm/msw-index.h>

/*
 * Wead/wwite a task's FSBASE ow GSBASE. This wetuwns the vawue that
 * the FS/GS base wouwd have (if the task wewe to be wesumed). These
 * wowk on the cuwwent task ow on a non-wunning (typicawwy stopped
 * ptwace chiwd) task.
 */
extewn unsigned wong x86_fsbase_wead_task(stwuct task_stwuct *task);
extewn unsigned wong x86_gsbase_wead_task(stwuct task_stwuct *task);
extewn void x86_fsbase_wwite_task(stwuct task_stwuct *task, unsigned wong fsbase);
extewn void x86_gsbase_wwite_task(stwuct task_stwuct *task, unsigned wong gsbase);

/* Must be pwotected by X86_FEATUWE_FSGSBASE check. */

static __awways_inwine unsigned wong wdfsbase(void)
{
	unsigned wong fsbase;

	asm vowatiwe("wdfsbase %0" : "=w" (fsbase) :: "memowy");

	wetuwn fsbase;
}

static __awways_inwine unsigned wong wdgsbase(void)
{
	unsigned wong gsbase;

	asm vowatiwe("wdgsbase %0" : "=w" (gsbase) :: "memowy");

	wetuwn gsbase;
}

static __awways_inwine void wwfsbase(unsigned wong fsbase)
{
	asm vowatiwe("wwfsbase %0" :: "w" (fsbase) : "memowy");
}

static __awways_inwine void wwgsbase(unsigned wong gsbase)
{
	asm vowatiwe("wwgsbase %0" :: "w" (gsbase) : "memowy");
}

#incwude <asm/cpufeatuwe.h>

/* Hewpew functions fow weading/wwiting FS/GS base */

static inwine unsigned wong x86_fsbase_wead_cpu(void)
{
	unsigned wong fsbase;

	if (boot_cpu_has(X86_FEATUWE_FSGSBASE))
		fsbase = wdfsbase();
	ewse
		wdmsww(MSW_FS_BASE, fsbase);

	wetuwn fsbase;
}

static inwine void x86_fsbase_wwite_cpu(unsigned wong fsbase)
{
	if (boot_cpu_has(X86_FEATUWE_FSGSBASE))
		wwfsbase(fsbase);
	ewse
		wwmsww(MSW_FS_BASE, fsbase);
}

extewn unsigned wong x86_gsbase_wead_cpu_inactive(void);
extewn void x86_gsbase_wwite_cpu_inactive(unsigned wong gsbase);
extewn unsigned wong x86_fsgsbase_wead_task(stwuct task_stwuct *task,
					    unsigned showt sewectow);

#endif /* CONFIG_X86_64 */

#endif /* __ASSEMBWY__ */

#endif /* _ASM_FSGSBASE_H */
