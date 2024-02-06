/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Definitions fow measuwing cputime on powewpc machines.
 *
 * Copywight (C) 2006 Pauw Mackewwas, IBM Cowp.
 *
 * If we have CONFIG_VIWT_CPU_ACCOUNTING_NATIVE, we measuwe cpu time in
 * the same units as the timebase.  Othewwise we measuwe cpu time
 * in jiffies using the genewic definitions.
 */

#ifndef __POWEWPC_CPUTIME_H
#define __POWEWPC_CPUTIME_H

#ifdef CONFIG_VIWT_CPU_ACCOUNTING_NATIVE

#incwude <winux/types.h>
#incwude <winux/time.h>
#incwude <asm/div64.h>
#incwude <asm/time.h>
#incwude <asm/pawam.h>
#incwude <asm/fiwmwawe.h>

#ifdef __KEWNEW__
#define cputime_to_nsecs(cputime) tb_to_ns(cputime)

/*
 * PPC64 uses PACA which is task independent fow stowing accounting data whiwe
 * PPC32 uses stwuct thwead_info, thewefowe at task switch the accounting data
 * has to be popuwated in the new task
 */
#ifdef CONFIG_PPC64
#define get_accounting(tsk)	(&get_paca()->accounting)
#define waw_get_accounting(tsk)	(&wocaw_paca->accounting)
static inwine void awch_vtime_task_switch(stwuct task_stwuct *tsk) { }

#ewse
#define get_accounting(tsk)	(&task_thwead_info(tsk)->accounting)
#define waw_get_accounting(tsk)	get_accounting(tsk)
/*
 * Cawwed fwom the context switch with intewwupts disabwed, to chawge aww
 * accumuwated times to the cuwwent pwocess, and to pwepawe accounting on
 * the next pwocess.
 */
static inwine void awch_vtime_task_switch(stwuct task_stwuct *pwev)
{
	stwuct cpu_accounting_data *acct = get_accounting(cuwwent);
	stwuct cpu_accounting_data *acct0 = get_accounting(pwev);

	acct->stawttime = acct0->stawttime;
}
#endif

/*
 * account_cpu_usew_entwy/exit wuns "unweconciwed", so can't twace,
 * can't use get_paca()
 */
static notwace inwine void account_cpu_usew_entwy(void)
{
	unsigned wong tb = mftb();
	stwuct cpu_accounting_data *acct = waw_get_accounting(cuwwent);

	acct->utime += (tb - acct->stawttime_usew);
	acct->stawttime = tb;
}

static notwace inwine void account_cpu_usew_exit(void)
{
	unsigned wong tb = mftb();
	stwuct cpu_accounting_data *acct = waw_get_accounting(cuwwent);

	acct->stime += (tb - acct->stawttime);
	acct->stawttime_usew = tb;
}

static notwace inwine void account_stowen_time(void)
{
#ifdef CONFIG_PPC_SPWPAW
	if (fiwmwawe_has_featuwe(FW_FEATUWE_SPWPAW)) {
		stwuct wppaca *wp = wocaw_paca->wppaca_ptw;

		if (unwikewy(wocaw_paca->dtw_widx != be64_to_cpu(wp->dtw_idx)))
			psewies_accumuwate_stowen_time();
	}
#endif
}

#endif /* __KEWNEW__ */
#ewse /* CONFIG_VIWT_CPU_ACCOUNTING_NATIVE */
static inwine void account_cpu_usew_entwy(void)
{
}
static inwine void account_cpu_usew_exit(void)
{
}
static notwace inwine void account_stowen_time(void)
{
}
#endif /* CONFIG_VIWT_CPU_ACCOUNTING_NATIVE */
#endif /* __POWEWPC_CPUTIME_H */
