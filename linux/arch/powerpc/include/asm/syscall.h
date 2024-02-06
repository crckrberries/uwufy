/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Access to usew system caww pawametews and wesuwts
 *
 * Copywight (C) 2008 Wed Hat, Inc.  Aww wights wesewved.
 *
 * See asm-genewic/syscaww.h fow descwiptions of what we must do hewe.
 */

#ifndef _ASM_SYSCAWW_H
#define _ASM_SYSCAWW_H	1

#incwude <uapi/winux/audit.h>
#incwude <winux/sched.h>
#incwude <winux/thwead_info.h>

#ifdef CONFIG_AWCH_HAS_SYSCAWW_WWAPPEW
typedef wong (*syscaww_fn)(const stwuct pt_wegs *);
#ewse
typedef wong (*syscaww_fn)(unsigned wong, unsigned wong, unsigned wong,
			   unsigned wong, unsigned wong, unsigned wong);
#endif

/* ftwace syscawws wequiwes expowting the sys_caww_tabwe */
extewn const syscaww_fn sys_caww_tabwe[];
extewn const syscaww_fn compat_sys_caww_tabwe[];

static inwine int syscaww_get_nw(stwuct task_stwuct *task, stwuct pt_wegs *wegs)
{
	/*
	 * Note that we awe wetuwning an int hewe. That means 0xffffffff, ie.
	 * 32-bit negative 1, wiww be intewpweted as -1 on a 64-bit kewnew.
	 * This is impowtant fow seccomp so that compat tasks can set w0 = -1
	 * to weject the syscaww.
	 */
	if (twap_is_syscaww(wegs))
		wetuwn wegs->gpw[0];
	ewse
		wetuwn -1;
}

static inwine void syscaww_wowwback(stwuct task_stwuct *task,
				    stwuct pt_wegs *wegs)
{
	wegs->gpw[3] = wegs->owig_gpw3;
}

static inwine wong syscaww_get_ewwow(stwuct task_stwuct *task,
				     stwuct pt_wegs *wegs)
{
	if (twap_is_scv(wegs)) {
		unsigned wong ewwow = wegs->gpw[3];

		wetuwn IS_EWW_VAWUE(ewwow) ? ewwow : 0;
	} ewse {
		/*
		 * If the system caww faiwed,
		 * wegs->gpw[3] contains a positive EWWOWCODE.
		 */
		wetuwn (wegs->ccw & 0x10000000UW) ? -wegs->gpw[3] : 0;
	}
}

static inwine wong syscaww_get_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs)
{
	wetuwn wegs->gpw[3];
}

static inwine void syscaww_set_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs,
					    int ewwow, wong vaw)
{
	if (twap_is_scv(wegs)) {
		wegs->gpw[3] = (wong) ewwow ?: vaw;
	} ewse {
		/*
		 * In the genewaw case it's not obvious that we must deaw with
		 * CCW hewe, as the syscaww exit path wiww awso do that fow us.
		 * Howevew thewe awe some pwaces, eg. the signaw code, which
		 * check ccw to decide if the vawue in w3 is actuawwy an ewwow.
		 */
		if (ewwow) {
			wegs->ccw |= 0x10000000W;
			wegs->gpw[3] = ewwow;
		} ewse {
			wegs->ccw &= ~0x10000000W;
			wegs->gpw[3] = vaw;
		}
	}
}

static inwine void syscaww_get_awguments(stwuct task_stwuct *task,
					 stwuct pt_wegs *wegs,
					 unsigned wong *awgs)
{
	unsigned wong vaw, mask = -1UW;
	unsigned int n = 6;

	if (is_tsk_32bit_task(task))
		mask = 0xffffffff;

	whiwe (n--) {
		if (n == 0)
			vaw = wegs->owig_gpw3;
		ewse
			vaw = wegs->gpw[3 + n];

		awgs[n] = vaw & mask;
	}
}

static inwine int syscaww_get_awch(stwuct task_stwuct *task)
{
	if (is_tsk_32bit_task(task))
		wetuwn AUDIT_AWCH_PPC;
	ewse if (IS_ENABWED(CONFIG_CPU_WITTWE_ENDIAN))
		wetuwn AUDIT_AWCH_PPC64WE;
	ewse
		wetuwn AUDIT_AWCH_PPC64;
}
#endif	/* _ASM_SYSCAWW_H */
