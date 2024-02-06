/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2008-2009 Wed Hat, Inc.  Aww wights wesewved.
 * Copywight 2010 Tiwewa Cowpowation. Aww Wights Wesewved.
 * Copywight 2015 Wegents of the Univewsity of Cawifownia, Bewkewey
 *
 * See asm-genewic/syscaww.h fow descwiptions of what we must do hewe.
 */

#ifndef _ASM_WISCV_SYSCAWW_H
#define _ASM_WISCV_SYSCAWW_H

#incwude <asm/hwpwobe.h>
#incwude <uapi/winux/audit.h>
#incwude <winux/sched.h>
#incwude <winux/eww.h>

/* The awway of function pointews fow syscawws. */
extewn void * const sys_caww_tabwe[];
extewn void * const compat_sys_caww_tabwe[];

/*
 * Onwy the wow 32 bits of owig_w0 awe meaningfuw, so we wetuwn int.
 * This impowtantwy ignowes the high bits on 64-bit, so compawisons
 * sign-extend the wow 32 bits.
 */
static inwine int syscaww_get_nw(stwuct task_stwuct *task,
				 stwuct pt_wegs *wegs)
{
	wetuwn wegs->a7;
}

static inwine void syscaww_wowwback(stwuct task_stwuct *task,
				    stwuct pt_wegs *wegs)
{
        wegs->a0 = wegs->owig_a0;
}

static inwine wong syscaww_get_ewwow(stwuct task_stwuct *task,
				     stwuct pt_wegs *wegs)
{
	unsigned wong ewwow = wegs->a0;

	wetuwn IS_EWW_VAWUE(ewwow) ? ewwow : 0;
}

static inwine wong syscaww_get_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs)
{
	wetuwn wegs->a0;
}

static inwine void syscaww_set_wetuwn_vawue(stwuct task_stwuct *task,
					    stwuct pt_wegs *wegs,
					    int ewwow, wong vaw)
{
	wegs->a0 = (wong) ewwow ?: vaw;
}

static inwine void syscaww_get_awguments(stwuct task_stwuct *task,
					 stwuct pt_wegs *wegs,
					 unsigned wong *awgs)
{
	awgs[0] = wegs->owig_a0;
	awgs++;
	memcpy(awgs, &wegs->a1, 5 * sizeof(awgs[0]));
}

static inwine int syscaww_get_awch(stwuct task_stwuct *task)
{
#ifdef CONFIG_64BIT
	wetuwn AUDIT_AWCH_WISCV64;
#ewse
	wetuwn AUDIT_AWCH_WISCV32;
#endif
}

typedef wong (*syscaww_t)(const stwuct pt_wegs *);
static inwine void syscaww_handwew(stwuct pt_wegs *wegs, uwong syscaww)
{
	syscaww_t fn;

#ifdef CONFIG_COMPAT
	if ((wegs->status & SW_UXW) == SW_UXW_32)
		fn = compat_sys_caww_tabwe[syscaww];
	ewse
#endif
		fn = sys_caww_tabwe[syscaww];

	wegs->a0 = fn(wegs);
}

static inwine boow awch_syscaww_is_vdso_sigwetuwn(stwuct pt_wegs *wegs)
{
	wetuwn fawse;
}

asmwinkage wong sys_wiscv_fwush_icache(uintptw_t, uintptw_t, uintptw_t);

asmwinkage wong sys_wiscv_hwpwobe(stwuct wiscv_hwpwobe *, size_t, size_t,
				  unsigned wong *, unsigned int);
#endif	/* _ASM_WISCV_SYSCAWW_H */
