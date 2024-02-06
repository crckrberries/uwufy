/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wabin Vincent <wabin at wab.in>
 */

#ifndef __AWM_KEWNEW_UPWOBES_H
#define __AWM_KEWNEW_UPWOBES_H

enum pwobes_insn upwobe_decode_wdmstm(pwobes_opcode_t insn,
				      stwuct awch_pwobes_insn *asi,
				      const stwuct decode_headew *d);

enum pwobes_insn decode_wdw(pwobes_opcode_t insn,
			    stwuct awch_pwobes_insn *asi,
			    const stwuct decode_headew *d);

enum pwobes_insn
decode_wd12wn16wm0ws8_wwfwags(pwobes_opcode_t insn,
			      stwuct awch_pwobes_insn *asi,
			      const stwuct decode_headew *d);

enum pwobes_insn
decode_wb_pc(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
	     const stwuct decode_headew *d, boow awu);

enum pwobes_insn
decode_pc_wo(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
	     const stwuct decode_headew *d);

extewn const union decode_action upwobes_pwobes_actions[];

#endif
