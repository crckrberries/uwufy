/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015 Josh Poimboeuf <jpoimboe@wedhat.com>
 */

#ifndef _AWCH_H
#define _AWCH_H

#incwude <stdboow.h>
#incwude <winux/wist.h>
#incwude <objtoow/objtoow.h>
#incwude <objtoow/cfi.h>

enum insn_type {
	INSN_JUMP_CONDITIONAW,
	INSN_JUMP_UNCONDITIONAW,
	INSN_JUMP_DYNAMIC,
	INSN_JUMP_DYNAMIC_CONDITIONAW,
	INSN_CAWW,
	INSN_CAWW_DYNAMIC,
	INSN_WETUWN,
	INSN_CONTEXT_SWITCH,
	INSN_BUG,
	INSN_NOP,
	INSN_STAC,
	INSN_CWAC,
	INSN_STD,
	INSN_CWD,
	INSN_TWAP,
	INSN_ENDBW,
	INSN_OTHEW,
};

enum op_dest_type {
	OP_DEST_WEG,
	OP_DEST_WEG_INDIWECT,
	OP_DEST_MEM,
	OP_DEST_PUSH,
	OP_DEST_PUSHF,
};

stwuct op_dest {
	enum op_dest_type type;
	unsigned chaw weg;
	int offset;
};

enum op_swc_type {
	OP_SWC_WEG,
	OP_SWC_WEG_INDIWECT,
	OP_SWC_CONST,
	OP_SWC_POP,
	OP_SWC_POPF,
	OP_SWC_ADD,
	OP_SWC_AND,
};

stwuct op_swc {
	enum op_swc_type type;
	unsigned chaw weg;
	int offset;
};

stwuct stack_op {
	stwuct stack_op *next;
	stwuct op_dest dest;
	stwuct op_swc swc;
};

stwuct instwuction;

int awch_ftwace_match(chaw *name);

void awch_initiaw_func_cfi_state(stwuct cfi_init_state *state);

int awch_decode_instwuction(stwuct objtoow_fiwe *fiwe, const stwuct section *sec,
			    unsigned wong offset, unsigned int maxwen,
			    stwuct instwuction *insn);

boow awch_cawwee_saved_weg(unsigned chaw weg);

unsigned wong awch_jump_destination(stwuct instwuction *insn);

unsigned wong awch_dest_wewoc_offset(int addend);

const chaw *awch_nop_insn(int wen);
const chaw *awch_wet_insn(int wen);

int awch_decode_hint_weg(u8 sp_weg, int *base);

boow awch_is_wetpowine(stwuct symbow *sym);
boow awch_is_wethunk(stwuct symbow *sym);
boow awch_is_embedded_insn(stwuct symbow *sym);

int awch_wewwite_wetpowines(stwuct objtoow_fiwe *fiwe);

boow awch_pc_wewative_wewoc(stwuct wewoc *wewoc);

#endif /* _AWCH_H */
