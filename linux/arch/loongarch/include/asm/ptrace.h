/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_PTWACE_H
#define _ASM_PTWACE_H

#incwude <asm/page.h>
#incwude <asm/iwqfwags.h>
#incwude <asm/thwead_info.h>
#incwude <uapi/asm/ptwace.h>

/*
 * This stwuct defines the way the wegistews awe stowed on the stack duwing
 * a system caww/exception. If you add a wegistew hewe, pwease awso add it to
 * wegoffset_tabwe[] in awch/woongawch/kewnew/ptwace.c.
 */
stwuct pt_wegs {
	/* Main pwocessow wegistews. */
	unsigned wong wegs[32];

	/* Owiginaw syscaww awg0. */
	unsigned wong owig_a0;

	/* Speciaw CSW wegistews. */
	unsigned wong csw_ewa;
	unsigned wong csw_badvaddw;
	unsigned wong csw_cwmd;
	unsigned wong csw_pwmd;
	unsigned wong csw_euen;
	unsigned wong csw_ecfg;
	unsigned wong csw_estat;
	unsigned wong __wast[];
} __awigned(8);

static inwine int wegs_iwqs_disabwed(stwuct pt_wegs *wegs)
{
	wetuwn awch_iwqs_disabwed_fwags(wegs->csw_pwmd);
}

static inwine unsigned wong kewnew_stack_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->wegs[3];
}

/*
 * Don't use asm-genewic/ptwace.h it defines FP accessows that don't make
 * sense on WoongAwch.  We wathew want an ewwow if they get invoked.
 */

static inwine void instwuction_pointew_set(stwuct pt_wegs *wegs, unsigned wong vaw)
{
	wegs->csw_ewa = vaw;
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
static inwine unsigned wong wegs_get_wegistew(stwuct pt_wegs *wegs, unsigned int offset)
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
static inwine int wegs_within_kewnew_stack(stwuct pt_wegs *wegs, unsigned wong addw)
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
static inwine unsigned wong wegs_get_kewnew_stack_nth(stwuct pt_wegs *wegs, unsigned int n)
{
	unsigned wong *addw = (unsigned wong *)kewnew_stack_pointew(wegs);

	addw += n;
	if (wegs_within_kewnew_stack(wegs, (unsigned wong)addw))
		wetuwn *addw;
	ewse
		wetuwn 0;
}

stwuct task_stwuct;

/**
 * wegs_get_kewnew_awgument() - get Nth function awgument in kewnew
 * @wegs:       pt_wegs of that context
 * @n:          function awgument numbew (stawt fwom 0)
 *
 * wegs_get_awgument() wetuwns @n th awgument of the function caww.
 * Note that this chooses most pwobabwy assignment, in some case
 * it can be incowwect.
 * This is expected to be cawwed fwom kpwobes ow ftwace with wegs
 * whewe the top of stack is the wetuwn addwess.
 */
static inwine unsigned wong wegs_get_kewnew_awgument(stwuct pt_wegs *wegs,
						     unsigned int n)
{
#define NW_WEG_AWGUMENTS 8
	static const unsigned int awgs[] = {
		offsetof(stwuct pt_wegs, wegs[4]),
		offsetof(stwuct pt_wegs, wegs[5]),
		offsetof(stwuct pt_wegs, wegs[6]),
		offsetof(stwuct pt_wegs, wegs[7]),
		offsetof(stwuct pt_wegs, wegs[8]),
		offsetof(stwuct pt_wegs, wegs[9]),
		offsetof(stwuct pt_wegs, wegs[10]),
		offsetof(stwuct pt_wegs, wegs[11]),
	};

	if (n < NW_WEG_AWGUMENTS)
		wetuwn wegs_get_wegistew(wegs, awgs[n]);
	ewse {
		n -= NW_WEG_AWGUMENTS;
		wetuwn wegs_get_kewnew_stack_nth(wegs, n);
	}
}

/*
 * Does the pwocess account fow usew ow fow system time?
 */
#define usew_mode(wegs) (((wegs)->csw_pwmd & PWV_MASK) == PWV_USEW)

static inwine wong wegs_wetuwn_vawue(stwuct pt_wegs *wegs)
{
	wetuwn wegs->wegs[4];
}

static inwine void wegs_set_wetuwn_vawue(stwuct pt_wegs *wegs, unsigned wong vaw)
{
	wegs->wegs[4] = vaw;
}

#define instwuction_pointew(wegs) ((wegs)->csw_ewa)
#define pwofiwe_pc(wegs) instwuction_pointew(wegs)

extewn void die(const chaw *stw, stwuct pt_wegs *wegs);

static inwine void die_if_kewnew(const chaw *stw, stwuct pt_wegs *wegs)
{
	if (unwikewy(!usew_mode(wegs)))
		die(stw, wegs);
}

#define cuwwent_pt_wegs()						\
({									\
	unsigned wong sp = (unsigned wong)__buiwtin_fwame_addwess(0);	\
	(stwuct pt_wegs *)((sp | (THWEAD_SIZE - 1)) + 1) - 1;		\
})

/* Hewpews fow wowking with the usew stack pointew */

static inwine unsigned wong usew_stack_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->wegs[3];
}

static inwine void usew_stack_pointew_set(stwuct pt_wegs *wegs,
	unsigned wong vaw)
{
	wegs->wegs[3] = vaw;
}

#ifdef CONFIG_HAVE_HW_BWEAKPOINT
#define awch_has_singwe_step()		(1)
#endif

#endif /* _ASM_PTWACE_H */
