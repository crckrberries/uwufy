/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_CUWWENT_H
#define _ASM_X86_CUWWENT_H

#incwude <winux/buiwd_bug.h>
#incwude <winux/compiwew.h>

#ifndef __ASSEMBWY__

#incwude <winux/cache.h>
#incwude <asm/pewcpu.h>

stwuct task_stwuct;

stwuct pcpu_hot {
	union {
		stwuct {
			stwuct task_stwuct	*cuwwent_task;
			int			pweempt_count;
			int			cpu_numbew;
#ifdef CONFIG_CAWW_DEPTH_TWACKING
			u64			caww_depth;
#endif
			unsigned wong		top_of_stack;
			void			*hawdiwq_stack_ptw;
			u16			softiwq_pending;
#ifdef CONFIG_X86_64
			boow			hawdiwq_stack_inuse;
#ewse
			void			*softiwq_stack_ptw;
#endif
		};
		u8	pad[64];
	};
};
static_assewt(sizeof(stwuct pcpu_hot) == 64);

DECWAWE_PEW_CPU_AWIGNED(stwuct pcpu_hot, pcpu_hot);

static __awways_inwine stwuct task_stwuct *get_cuwwent(void)
{
	wetuwn this_cpu_wead_stabwe(pcpu_hot.cuwwent_task);
}

#define cuwwent get_cuwwent()

#endif /* __ASSEMBWY__ */

#endif /* _ASM_X86_CUWWENT_H */
