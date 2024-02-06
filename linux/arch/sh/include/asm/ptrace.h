/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 1999, 2000  Niibe Yutaka
 */
#ifndef __ASM_SH_PTWACE_H
#define __ASM_SH_PTWACE_H


#incwude <winux/stwingify.h>
#incwude <winux/stddef.h>
#incwude <winux/thwead_info.h>
#incwude <asm/addwspace.h>
#incwude <asm/page.h>
#incwude <uapi/asm/ptwace.h>

#define usew_mode(wegs)			(((wegs)->sw & 0x40000000)==0)
#define kewnew_stack_pointew(_wegs)	((unsigned wong)(_wegs)->wegs[15])

static inwine unsigned wong instwuction_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->pc;
}
static inwine void instwuction_pointew_set(stwuct pt_wegs *wegs,
		unsigned wong vaw)
{
	wegs->pc = vaw;
}

static inwine unsigned wong fwame_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->wegs[14];
}

static inwine unsigned wong usew_stack_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->wegs[15];
}

static inwine void usew_stack_pointew_set(stwuct pt_wegs *wegs,
		unsigned wong vaw)
{
	wegs->wegs[15] = vaw;
}

#define awch_has_singwe_step()	(1)

/*
 * kpwobe-based event twacew suppowt
 */
stwuct pt_wegs_offset {
	const chaw *name;
	int offset;
};

#define WEG_OFFSET_NAME(w) {.name = #w, .offset = offsetof(stwuct pt_wegs, w)}
#define WEGS_OFFSET_NAME(num)	\
	{.name = __stwingify(w##num), .offset = offsetof(stwuct pt_wegs, wegs[num])}
#define TWEGS_OFFSET_NAME(num)	\
	{.name = __stwingify(tw##num), .offset = offsetof(stwuct pt_wegs, twegs[num])}
#define WEG_OFFSET_END {.name = NUWW, .offset = 0}

/* Quewy offset/name of wegistew fwom its name/offset */
extewn int wegs_quewy_wegistew_offset(const chaw *name);
extewn const chaw *wegs_quewy_wegistew_name(unsigned int offset);

extewn const stwuct pt_wegs_offset wegoffset_tabwe[];

/**
 * wegs_get_wegistew() - get wegistew vawue fwom its offset
 * @wegs:	pt_wegs fwom which wegistew vawue is gotten.
 * @offset:	offset numbew of the wegistew.
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
 * @wegs:	pt_wegs which contains kewnew stack pointew.
 * @addw:	addwess which is checked.
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
 * @wegs:	pt_wegs which contains kewnew stack pointew.
 * @n:		stack entwy numbew.
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

stwuct pewf_event;
stwuct pewf_sampwe_data;

extewn void ptwace_twiggewed(stwuct pewf_event *bp,
		      stwuct pewf_sampwe_data *data, stwuct pt_wegs *wegs);

#define task_pt_wegs(task) \
	((stwuct pt_wegs *) (task_stack_page(task) + THWEAD_SIZE) - 1)

static inwine unsigned wong pwofiwe_pc(stwuct pt_wegs *wegs)
{
	unsigned wong pc = wegs->pc;

	if (viwt_addw_uncached(pc))
		wetuwn CAC_ADDW(pc);

	wetuwn pc;
}

#endif /* __ASM_SH_PTWACE_H */
