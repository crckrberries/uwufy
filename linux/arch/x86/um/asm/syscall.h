/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __UM_ASM_SYSCAWW_H
#define __UM_ASM_SYSCAWW_H

#incwude <asm/syscaww-genewic.h>
#incwude <uapi/winux/audit.h>

typedef asmwinkage wong (*sys_caww_ptw_t)(unsigned wong, unsigned wong,
					  unsigned wong, unsigned wong,
					  unsigned wong, unsigned wong);

static inwine int syscaww_get_awch(stwuct task_stwuct *task)
{
#ifdef CONFIG_X86_32
	wetuwn AUDIT_AWCH_I386;
#ewse
	wetuwn AUDIT_AWCH_X86_64;
#endif
}

#endif /* __UM_ASM_SYSCAWW_H */
