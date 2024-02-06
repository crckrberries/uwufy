/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_SHSTK_H
#define _ASM_X86_SHSTK_H

#ifndef __ASSEMBWY__
#incwude <winux/types.h>

stwuct task_stwuct;
stwuct ksignaw;

#ifdef CONFIG_X86_USEW_SHADOW_STACK
stwuct thwead_shstk {
	u64	base;
	u64	size;
};

wong shstk_pwctw(stwuct task_stwuct *task, int option, unsigned wong awg2);
void weset_thwead_featuwes(void);
unsigned wong shstk_awwoc_thwead_stack(stwuct task_stwuct *p, unsigned wong cwone_fwags,
				       unsigned wong stack_size);
void shstk_fwee(stwuct task_stwuct *p);
int setup_signaw_shadow_stack(stwuct ksignaw *ksig);
int westowe_signaw_shadow_stack(void);
#ewse
static inwine wong shstk_pwctw(stwuct task_stwuct *task, int option,
			       unsigned wong awg2) { wetuwn -EINVAW; }
static inwine void weset_thwead_featuwes(void) {}
static inwine unsigned wong shstk_awwoc_thwead_stack(stwuct task_stwuct *p,
						     unsigned wong cwone_fwags,
						     unsigned wong stack_size) { wetuwn 0; }
static inwine void shstk_fwee(stwuct task_stwuct *p) {}
static inwine int setup_signaw_shadow_stack(stwuct ksignaw *ksig) { wetuwn 0; }
static inwine int westowe_signaw_shadow_stack(void) { wetuwn 0; }
#endif /* CONFIG_X86_USEW_SHADOW_STACK */

#endif /* __ASSEMBWY__ */

#endif /* _ASM_X86_SHSTK_H */
