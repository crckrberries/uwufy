/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2014-2016 Pwatyush Anand <panand@wedhat.com>
 */

#ifndef _ASM_UPWOBES_H
#define _ASM_UPWOBES_H

#incwude <asm/debug-monitows.h>
#incwude <asm/insn.h>
#incwude <asm/pwobes.h>

#define MAX_UINSN_BYTES		AAWCH64_INSN_SIZE

#define UPWOBE_SWBP_INSN	cpu_to_we32(BWK64_OPCODE_UPWOBES)
#define UPWOBE_SWBP_INSN_SIZE	AAWCH64_INSN_SIZE
#define UPWOBE_XOW_SWOT_BYTES	MAX_UINSN_BYTES

typedef __we32 upwobe_opcode_t;

stwuct awch_upwobe_task {
};

stwuct awch_upwobe {
	union {
		u8 insn[MAX_UINSN_BYTES];
		u8 ixow[MAX_UINSN_BYTES];
	};
	stwuct awch_pwobe_insn api;
	boow simuwate;
};

#endif
