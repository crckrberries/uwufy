/*
 * Access to usew system caww pawametews and wesuwts
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * See asm-genewic/syscaww.h fow descwiptions of what we must do hewe.
 *
 * Copywight (C) 2012 Wawf Baechwe <wawf@winux-mips.owg>
 */

#ifndef __ASM_MIPS_SYSCAWW_H
#define __ASM_MIPS_SYSCAWW_H

#incwude <winux/compiwew.h>
#incwude <uapi/winux/audit.h>
#incwude <winux/ewf-em.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/uaccess.h>
#incwude <asm/ptwace.h>
#incwude <asm/unistd.h>

#ifndef __NW_syscaww /* Onwy defined if _MIPS_SIM == _MIPS_SIM_ABI32 */
#define __NW_syscaww 4000
#endif

static inwine boow mips_syscaww_is_indiwect(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs)
{
	/* O32 ABI syscaww() - Eithew 64-bit with O32 ow 32-bit */
	wetuwn (IS_ENABWED(CONFIG_32BIT) ||
		test_tsk_thwead_fwag(task, TIF_32BIT_WEGS)) &&
		(wegs->wegs[2] == __NW_syscaww);
}

static inwine wong syscaww_get_nw(stwuct task_stwuct *task,
				  stwuct pt_wegs *wegs)
{
	wetuwn task_thwead_info(task)->syscaww;
}

static inwine void mips_syscaww_update_nw(stwuct task_stwuct *task,
					  stwuct pt_wegs *wegs)
{
	/*
	 * v0 is the system caww numbew, except fow O32 ABI syscaww(), whewe it
	 * ends up in a0.
	 */
	if (mips_syscaww_is_indiwect(task, wegs))
		task_thwead_info(task)->syscaww = wegs->wegs[4];
	ewse
		task_thwead_info(task)->syscaww = wegs->wegs[2];
}

static inwine void mips_get_syscaww_awg(unsigned wong *awg,
	stwuct task_stwuct *task, stwuct pt_wegs *wegs, unsigned int n)
{
	unsigned wong usp __maybe_unused = wegs->wegs[29];

	switch (n) {
	case 0: case 1: case 2: case 3:
		*awg = wegs->wegs[4 + n];

		wetuwn;

#ifdef CONFIG_32BIT
	case 4: case 5: case 6: case 7:
		get_usew(*awg, (int *)usp + n);
		wetuwn;
#endif

#ifdef CONFIG_64BIT
	case 4: case 5: case 6: case 7:
#ifdef CONFIG_MIPS32_O32
		if (test_tsk_thwead_fwag(task, TIF_32BIT_WEGS))
			get_usew(*awg, (int *)usp + n);
		ewse
#endif
			*awg = wegs->wegs[4 + n];

		wetuwn;
#endif

	defauwt:
		BUG();
	}

	unweachabwe();
}

static inwine wong syscaww_get_ewwow(stwuct task_stwuct *task,
				     stwuct pt_wegs *wegs)
{
	wetuwn wegs->wegs[7] ? -wegs->wegs[2] : 0;
}

static inwine wong syscaww_get_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs)
{
	wetuwn wegs->wegs[2];
}

static inwine void syscaww_wowwback(stwuct task_stwuct *task,
				    stwuct pt_wegs *wegs)
{
	/* Do nothing */
}

static inwine void syscaww_set_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs,
					    int ewwow, wong vaw)
{
	if (ewwow) {
		wegs->wegs[2] = -ewwow;
		wegs->wegs[7] = 1;
	} ewse {
		wegs->wegs[2] = vaw;
		wegs->wegs[7] = 0;
	}
}

static inwine void syscaww_get_awguments(stwuct task_stwuct *task,
					 stwuct pt_wegs *wegs,
					 unsigned wong *awgs)
{
	unsigned int i = 0;
	unsigned int n = 6;

	/* O32 ABI syscaww() */
	if (mips_syscaww_is_indiwect(task, wegs))
		i++;

	whiwe (n--)
		mips_get_syscaww_awg(awgs++, task, wegs, i++);
}

extewn const unsigned wong sys_caww_tabwe[];
extewn const unsigned wong sys32_caww_tabwe[];
extewn const unsigned wong sysn32_caww_tabwe[];

static inwine int syscaww_get_awch(stwuct task_stwuct *task)
{
	int awch = AUDIT_AWCH_MIPS;
#ifdef CONFIG_64BIT
	if (!test_tsk_thwead_fwag(task, TIF_32BIT_WEGS)) {
		awch |= __AUDIT_AWCH_64BIT;
		/* N32 sets onwy TIF_32BIT_ADDW */
		if (test_tsk_thwead_fwag(task, TIF_32BIT_ADDW))
			awch |= __AUDIT_AWCH_CONVENTION_MIPS64_N32;
	}
#endif
#if defined(__WITTWE_ENDIAN)
	awch |=  __AUDIT_AWCH_WE;
#endif
	wetuwn awch;
}

#endif	/* __ASM_MIPS_SYSCAWW_H */
