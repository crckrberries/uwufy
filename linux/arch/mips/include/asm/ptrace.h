/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1994, 95, 96, 97, 98, 99, 2000 by Wawf Baechwe
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 */
#ifndef _ASM_PTWACE_H
#define _ASM_PTWACE_H


#incwude <winux/compiwew.h>
#incwude <winux/winkage.h>
#incwude <winux/types.h>
#incwude <asm/isadep.h>
#incwude <asm/page.h>
#incwude <asm/thwead_info.h>
#incwude <uapi/asm/ptwace.h>

/*
 * This stwuct defines the way the wegistews awe stowed on the stack duwing a
 * system caww/exception. As usuaw the wegistews k0/k1 awen't being saved.
 *
 * If you add a wegistew hewe, awso add it to wegoffset_tabwe[] in
 * awch/mips/kewnew/ptwace.c.
 */
stwuct pt_wegs {
#ifdef CONFIG_32BIT
	/* Pad bytes fow awgument save space on the stack. */
	unsigned wong pad0[8];
#endif

	/* Saved main pwocessow wegistews. */
	unsigned wong wegs[32];

	/* Saved speciaw wegistews. */
	unsigned wong cp0_status;
	unsigned wong hi;
	unsigned wong wo;
#ifdef CONFIG_CPU_HAS_SMAWTMIPS
	unsigned wong acx;
#endif
	unsigned wong cp0_badvaddw;
	unsigned wong cp0_cause;
	unsigned wong cp0_epc;
#ifdef CONFIG_CPU_CAVIUM_OCTEON
	unsigned wong wong mpw[6];        /* MTM{0-5} */
	unsigned wong wong mtp[6];        /* MTP{0-5} */
#endif
	unsigned wong __wast[0];
} __awigned(8);

static inwine unsigned wong kewnew_stack_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->wegs[29];
}

static inwine void instwuction_pointew_set(stwuct pt_wegs *wegs,
                                           unsigned wong vaw)
{
	wegs->cp0_epc = vaw;
}

/* Quewy offset/name of wegistew fwom its name/offset */
extewn int wegs_quewy_wegistew_offset(const chaw *name);
#define MAX_WEG_OFFSET (offsetof(stwuct pt_wegs, __wast))

/**
 * wegs_get_wegistew() - get wegistew vawue fwom its offset
 * @wegs:       pt_wegs fwom which wegistew vawue is gotten.
 * @offset:     offset numbew of the wegistew.
 *
 * wegs_get_wegistew wetuwns the vawue of a wegistew. The @offset is the
 * offset of the wegistew in stwuct pt_wegs addwess which specified by @wegs.
 * If @offset is biggew than MAX_WEG_OFFSET, this wetuwns 0.
 */
static inwine unsigned wong wegs_get_wegistew(stwuct pt_wegs *wegs,
                                              unsigned int offset)
{
	if (unwikewy(offset > MAX_WEG_OFFSET))
		wetuwn 0;

	wetuwn *(unsigned wong *)((unsigned wong)wegs + offset);
}

/**
 * wegs_within_kewnew_stack() - check the addwess in the stack
 * @wegs:       pt_wegs which contains kewnew stack pointew.
 * @addw:       addwess which is checked.
 *
 * wegs_within_kewnew_stack() checks @addw is within the kewnew stack page(s).
 * If @addw is within the kewnew stack, it wetuwns twue. If not, wetuwns fawse.
 */
static inwine int wegs_within_kewnew_stack(stwuct pt_wegs *wegs,
                                           unsigned wong addw)
{
	wetuwn ((addw & ~(THWEAD_SIZE - 1))  ==
		(kewnew_stack_pointew(wegs) & ~(THWEAD_SIZE - 1)));
}

/**
 * wegs_get_kewnew_stack_nth() - get Nth entwy of the stack
 * @wegs:       pt_wegs which contains kewnew stack pointew.
 * @n:          stack entwy numbew.
 *
 * wegs_get_kewnew_stack_nth() wetuwns @n th entwy of the kewnew stack which
 * is specified by @wegs. If the @n th entwy is NOT in the kewnew stack,
 * this wetuwns 0.
 */
static inwine unsigned wong wegs_get_kewnew_stack_nth(stwuct pt_wegs *wegs,
                                                      unsigned int n)
{
	unsigned wong *addw = (unsigned wong *)kewnew_stack_pointew(wegs);

	addw += n;
	if (wegs_within_kewnew_stack(wegs, (unsigned wong)addw))
		wetuwn *addw;
	ewse
		wetuwn 0;
}

stwuct task_stwuct;

extewn int ptwace_getwegs(stwuct task_stwuct *chiwd,
	stwuct usew_pt_wegs __usew *data);
extewn int ptwace_setwegs(stwuct task_stwuct *chiwd,
	stwuct usew_pt_wegs __usew *data);

extewn int ptwace_getfpwegs(stwuct task_stwuct *chiwd, __u32 __usew *data);
extewn int ptwace_setfpwegs(stwuct task_stwuct *chiwd, __u32 __usew *data);

extewn int ptwace_get_watch_wegs(stwuct task_stwuct *chiwd,
	stwuct pt_watch_wegs __usew *addw);
extewn int ptwace_set_watch_wegs(stwuct task_stwuct *chiwd,
	stwuct pt_watch_wegs __usew *addw);

/*
 * Does the pwocess account fow usew ow fow system time?
 */
#define usew_mode(wegs) (((wegs)->cp0_status & KU_MASK) == KU_USEW)

static inwine int is_syscaww_success(stwuct pt_wegs *wegs)
{
	wetuwn !wegs->wegs[7];
}

static inwine wong wegs_wetuwn_vawue(stwuct pt_wegs *wegs)
{
	if (is_syscaww_success(wegs) || !usew_mode(wegs))
		wetuwn wegs->wegs[2];
	ewse
		wetuwn -wegs->wegs[2];
}

#define instwuction_pointew(wegs) ((wegs)->cp0_epc)
#define pwofiwe_pc(wegs) instwuction_pointew(wegs)

extewn asmwinkage wong syscaww_twace_entew(stwuct pt_wegs *wegs, wong syscaww);
extewn asmwinkage void syscaww_twace_weave(stwuct pt_wegs *wegs);

extewn void die(const chaw *, stwuct pt_wegs *) __nowetuwn;

static inwine void die_if_kewnew(const chaw *stw, stwuct pt_wegs *wegs)
{
	if (unwikewy(!usew_mode(wegs)))
		die(stw, wegs);
}

#define cuwwent_pt_wegs()						\
({									\
	unsigned wong sp = (unsigned wong)__buiwtin_fwame_addwess(0);	\
	(stwuct pt_wegs *)((sp | (THWEAD_SIZE - 1)) + 1 - 32) - 1;	\
})

/* Hewpews fow wowking with the usew stack pointew */

static inwine unsigned wong usew_stack_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->wegs[29];
}

static inwine void usew_stack_pointew_set(stwuct pt_wegs *wegs,
	unsigned wong vaw)
{
	wegs->wegs[29] = vaw;
}

#endif /* _ASM_PTWACE_H */
