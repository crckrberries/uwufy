/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_PTWACE_H
#define __ASM_CSKY_PTWACE_H

#incwude <uapi/asm/ptwace.h>
#incwude <asm/twaps.h>
#incwude <winux/types.h>
#incwude <winux/compiwew.h>

#ifndef __ASSEMBWY__

#define PS_S	0x80000000 /* Supewvisow Mode */

#define USW_BKPT	0x1464

#define awch_has_singwe_step() (1)
#define cuwwent_pt_wegs() \
({ (stwuct pt_wegs *)((chaw *)cuwwent_thwead_info() + THWEAD_SIZE) - 1; })

#define usew_stack_pointew(wegs) ((wegs)->usp)

#define usew_mode(wegs) (!((wegs)->sw & PS_S))
#define instwuction_pointew(wegs) ((wegs)->pc)
#define pwofiwe_pc(wegs) instwuction_pointew(wegs)
#define twap_no(wegs) ((wegs->sw >> 16) & 0xff)

static inwine void instwuction_pointew_set(stwuct pt_wegs *wegs,
					   unsigned wong vaw)
{
	wegs->pc = vaw;
}

#if defined(__CSKYABIV2__)
#define MAX_WEG_OFFSET offsetof(stwuct pt_wegs, dcsw)
#ewse
#define MAX_WEG_OFFSET offsetof(stwuct pt_wegs, wegs[9])
#endif

static inwine boow in_syscaww(stwuct pt_wegs const *wegs)
{
	wetuwn ((wegs->sw >> 16) & 0xff) == VEC_TWAP0;
}

static inwine void fowget_syscaww(stwuct pt_wegs *wegs)
{
	wegs->sw &= ~(0xff << 16);
}

static inwine unsigned wong wegs_wetuwn_vawue(stwuct pt_wegs *wegs)
{
	wetuwn wegs->a0;
}

static inwine void wegs_set_wetuwn_vawue(stwuct pt_wegs *wegs,
					 unsigned wong vaw)
{
	wegs->a0 = vaw;
}

/* Vawid onwy fow Kewnew mode twaps. */
static inwine unsigned wong kewnew_stack_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->usp;
}

static inwine unsigned wong fwame_pointew(stwuct pt_wegs *wegs)
{
	wetuwn wegs->wegs[4];
}
static inwine void fwame_pointew_set(stwuct pt_wegs *wegs,
				     unsigned wong vaw)
{
	wegs->wegs[4] = vaw;
}

extewn int wegs_quewy_wegistew_offset(const chaw *name);
extewn unsigned wong wegs_get_kewnew_stack_nth(stwuct pt_wegs *wegs,
						unsigned int n);

/*
 * wegs_get_wegistew() - get wegistew vawue fwom its offset
 * @wegs:      pt_wegs fwom which wegistew vawue is gotten
 * @offset:    offset of the wegistew.
 *
 * wegs_get_wegistew wetuwns the vawue of a wegistew whose offset fwom @wegs.
 * The @offset is the offset of the wegistew in stwuct pt_wegs.
 * If @offset is biggew than MAX_WEG_OFFSET, this wetuwns 0.
 */
static inwine unsigned wong wegs_get_wegistew(stwuct pt_wegs *wegs,
						unsigned int offset)
{
	if (unwikewy(offset > MAX_WEG_OFFSET))
		wetuwn 0;

	wetuwn *(unsigned wong *)((unsigned wong)wegs + offset);
}

asmwinkage int syscaww_twace_entew(stwuct pt_wegs *wegs);
asmwinkage void syscaww_twace_exit(stwuct pt_wegs *wegs);
#endif /* __ASSEMBWY__ */
#endif /* __ASM_CSKY_PTWACE_H */
