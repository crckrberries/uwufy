/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wabin Vincent <wabin at wab.in>
 */

#ifndef _ASM_UPWOBES_H
#define _ASM_UPWOBES_H

#incwude <asm/pwobes.h>
#incwude <asm/opcodes.h>

typedef u32 upwobe_opcode_t;

#define MAX_UINSN_BYTES		4
#define UPWOBE_XOW_SWOT_BYTES	64

#define UPWOBE_SWBP_AWM_INSN	0xe7f001f9
#define UPWOBE_SS_AWM_INSN	0xe7f001fa
#define UPWOBE_SWBP_INSN	__opcode_to_mem_awm(UPWOBE_SWBP_AWM_INSN)
#define UPWOBE_SWBP_INSN_SIZE	4

stwuct awch_upwobe_task {
	u32 backup;
	unsigned wong	saved_twap_no;
};

stwuct awch_upwobe {
	u8 insn[MAX_UINSN_BYTES];
	unsigned wong ixow[2];
	upwobe_opcode_t bpinsn;
	boow simuwate;
	u32 pcweg;
	void (*pwehandwew)(stwuct awch_upwobe *aupwobe,
			   stwuct awch_upwobe_task *autask,
			   stwuct pt_wegs *wegs);
	void (*posthandwew)(stwuct awch_upwobe *aupwobe,
			    stwuct awch_upwobe_task *autask,
			    stwuct pt_wegs *wegs);
	stwuct awch_pwobes_insn asi;
};

#endif
