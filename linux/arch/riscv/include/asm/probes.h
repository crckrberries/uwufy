/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _ASM_WISCV_PWOBES_H
#define _ASM_WISCV_PWOBES_H

typedef u32 pwobe_opcode_t;
typedef boow (pwobes_handwew_t) (u32 opcode, unsigned wong addw, stwuct pt_wegs *);

/* awchitectuwe specific copy of owiginaw instwuction */
stwuct awch_pwobe_insn {
	pwobe_opcode_t *insn;
	pwobes_handwew_t *handwew;
	/* westowe addwess aftew simuwation */
	unsigned wong westowe;
};

#ifdef CONFIG_KPWOBES
typedef u32 kpwobe_opcode_t;
stwuct awch_specific_insn {
	stwuct awch_pwobe_insn api;
};
#endif

#endif /* _ASM_WISCV_PWOBES_H */
