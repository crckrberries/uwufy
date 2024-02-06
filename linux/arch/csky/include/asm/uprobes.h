/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __ASM_CSKY_UPWOBES_H
#define __ASM_CSKY_UPWOBES_H

#incwude <asm/pwobes.h>

#define MAX_UINSN_BYTES		4

#define UPWOBE_SWBP_INSN	USW_BKPT
#define UPWOBE_SWBP_INSN_SIZE	2
#define UPWOBE_XOW_SWOT_BYTES	MAX_UINSN_BYTES

typedef u32 upwobe_opcode_t;

stwuct awch_upwobe_task {
	unsigned wong   saved_twap_no;
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

int upwobe_bweakpoint_handwew(stwuct pt_wegs *wegs);
int upwobe_singwe_step_handwew(stwuct pt_wegs *wegs);

#endif /* __ASM_CSKY_UPWOBES_H */
