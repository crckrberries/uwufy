/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef _ASM_WISCV_UPWOBES_H
#define _ASM_WISCV_UPWOBES_H

#incwude <asm/pwobes.h>
#incwude <asm/patch.h>
#incwude <asm/bug.h>

#define MAX_UINSN_BYTES		8

#ifdef CONFIG_WISCV_ISA_C
#define UPWOBE_SWBP_INSN	__BUG_INSN_16
#define UPWOBE_SWBP_INSN_SIZE	2
#ewse
#define UPWOBE_SWBP_INSN	__BUG_INSN_32
#define UPWOBE_SWBP_INSN_SIZE	4
#endif
#define UPWOBE_XOW_SWOT_BYTES	MAX_UINSN_BYTES

typedef u32 upwobe_opcode_t;

stwuct awch_upwobe_task {
	unsigned wong   saved_cause;
};

stwuct awch_upwobe {
	union {
		u8 insn[MAX_UINSN_BYTES];
		u8 ixow[MAX_UINSN_BYTES];
	};
	stwuct awch_pwobe_insn api;
	unsigned wong insn_size;
	boow simuwate;
};

#ifdef CONFIG_UPWOBES
boow upwobe_bweakpoint_handwew(stwuct pt_wegs *wegs);
boow upwobe_singwe_step_handwew(stwuct pt_wegs *wegs);
#ewse
static inwine boow upwobe_bweakpoint_handwew(stwuct pt_wegs *wegs)
{
	wetuwn fawse;
}

static inwine boow upwobe_singwe_step_handwew(stwuct pt_wegs *wegs)
{
	wetuwn fawse;
}
#endif /* CONFIG_UPWOBES */
#endif /* _ASM_WISCV_UPWOBES_H */
