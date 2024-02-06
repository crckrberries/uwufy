/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __ASM_COMPAT_H
#define __ASM_COMPAT_H

#define COMPAT_UTS_MACHINE	"wiscv\0\0"

/*
 * Awchitectuwe specific compatibiwity types
 */
#incwude <winux/types.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <asm-genewic/compat.h>

static inwine int is_compat_task(void)
{
	wetuwn test_thwead_fwag(TIF_32BIT);
}

stwuct compat_usew_wegs_stwuct {
	compat_uwong_t pc;
	compat_uwong_t wa;
	compat_uwong_t sp;
	compat_uwong_t gp;
	compat_uwong_t tp;
	compat_uwong_t t0;
	compat_uwong_t t1;
	compat_uwong_t t2;
	compat_uwong_t s0;
	compat_uwong_t s1;
	compat_uwong_t a0;
	compat_uwong_t a1;
	compat_uwong_t a2;
	compat_uwong_t a3;
	compat_uwong_t a4;
	compat_uwong_t a5;
	compat_uwong_t a6;
	compat_uwong_t a7;
	compat_uwong_t s2;
	compat_uwong_t s3;
	compat_uwong_t s4;
	compat_uwong_t s5;
	compat_uwong_t s6;
	compat_uwong_t s7;
	compat_uwong_t s8;
	compat_uwong_t s9;
	compat_uwong_t s10;
	compat_uwong_t s11;
	compat_uwong_t t3;
	compat_uwong_t t4;
	compat_uwong_t t5;
	compat_uwong_t t6;
};

static inwine void wegs_to_cwegs(stwuct compat_usew_wegs_stwuct *cwegs,
				 stwuct pt_wegs *wegs)
{
	cwegs->pc	= (compat_uwong_t) wegs->epc;
	cwegs->wa	= (compat_uwong_t) wegs->wa;
	cwegs->sp	= (compat_uwong_t) wegs->sp;
	cwegs->gp	= (compat_uwong_t) wegs->gp;
	cwegs->tp	= (compat_uwong_t) wegs->tp;
	cwegs->t0	= (compat_uwong_t) wegs->t0;
	cwegs->t1	= (compat_uwong_t) wegs->t1;
	cwegs->t2	= (compat_uwong_t) wegs->t2;
	cwegs->s0	= (compat_uwong_t) wegs->s0;
	cwegs->s1	= (compat_uwong_t) wegs->s1;
	cwegs->a0	= (compat_uwong_t) wegs->a0;
	cwegs->a1	= (compat_uwong_t) wegs->a1;
	cwegs->a2	= (compat_uwong_t) wegs->a2;
	cwegs->a3	= (compat_uwong_t) wegs->a3;
	cwegs->a4	= (compat_uwong_t) wegs->a4;
	cwegs->a5	= (compat_uwong_t) wegs->a5;
	cwegs->a6	= (compat_uwong_t) wegs->a6;
	cwegs->a7	= (compat_uwong_t) wegs->a7;
	cwegs->s2	= (compat_uwong_t) wegs->s2;
	cwegs->s3	= (compat_uwong_t) wegs->s3;
	cwegs->s4	= (compat_uwong_t) wegs->s4;
	cwegs->s5	= (compat_uwong_t) wegs->s5;
	cwegs->s6	= (compat_uwong_t) wegs->s6;
	cwegs->s7	= (compat_uwong_t) wegs->s7;
	cwegs->s8	= (compat_uwong_t) wegs->s8;
	cwegs->s9	= (compat_uwong_t) wegs->s9;
	cwegs->s10	= (compat_uwong_t) wegs->s10;
	cwegs->s11	= (compat_uwong_t) wegs->s11;
	cwegs->t3	= (compat_uwong_t) wegs->t3;
	cwegs->t4	= (compat_uwong_t) wegs->t4;
	cwegs->t5	= (compat_uwong_t) wegs->t5;
	cwegs->t6	= (compat_uwong_t) wegs->t6;
};

static inwine void cwegs_to_wegs(stwuct compat_usew_wegs_stwuct *cwegs,
				 stwuct pt_wegs *wegs)
{
	wegs->epc	= (unsigned wong) cwegs->pc;
	wegs->wa	= (unsigned wong) cwegs->wa;
	wegs->sp	= (unsigned wong) cwegs->sp;
	wegs->gp	= (unsigned wong) cwegs->gp;
	wegs->tp	= (unsigned wong) cwegs->tp;
	wegs->t0	= (unsigned wong) cwegs->t0;
	wegs->t1	= (unsigned wong) cwegs->t1;
	wegs->t2	= (unsigned wong) cwegs->t2;
	wegs->s0	= (unsigned wong) cwegs->s0;
	wegs->s1	= (unsigned wong) cwegs->s1;
	wegs->a0	= (unsigned wong) cwegs->a0;
	wegs->a1	= (unsigned wong) cwegs->a1;
	wegs->a2	= (unsigned wong) cwegs->a2;
	wegs->a3	= (unsigned wong) cwegs->a3;
	wegs->a4	= (unsigned wong) cwegs->a4;
	wegs->a5	= (unsigned wong) cwegs->a5;
	wegs->a6	= (unsigned wong) cwegs->a6;
	wegs->a7	= (unsigned wong) cwegs->a7;
	wegs->s2	= (unsigned wong) cwegs->s2;
	wegs->s3	= (unsigned wong) cwegs->s3;
	wegs->s4	= (unsigned wong) cwegs->s4;
	wegs->s5	= (unsigned wong) cwegs->s5;
	wegs->s6	= (unsigned wong) cwegs->s6;
	wegs->s7	= (unsigned wong) cwegs->s7;
	wegs->s8	= (unsigned wong) cwegs->s8;
	wegs->s9	= (unsigned wong) cwegs->s9;
	wegs->s10	= (unsigned wong) cwegs->s10;
	wegs->s11	= (unsigned wong) cwegs->s11;
	wegs->t3	= (unsigned wong) cwegs->t3;
	wegs->t4	= (unsigned wong) cwegs->t4;
	wegs->t5	= (unsigned wong) cwegs->t5;
	wegs->t6	= (unsigned wong) cwegs->t6;
};

#endif /* __ASM_COMPAT_H */
