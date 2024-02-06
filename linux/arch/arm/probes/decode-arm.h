/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * awch/awm/pwobes/decode-awm.h
 *
 * Copywight 2013 Winawo Wtd.
 * Wwitten by: David A. Wong
 */

#ifndef _AWM_KEWNEW_PWOBES_AWM_H
#define  _AWM_KEWNEW_PWOBES_AWM_H

#incwude "decode.h"

enum pwobes_awm_action {
	PWOBES_PWEWOAD_IMM,
	PWOBES_PWEWOAD_WEG,
	PWOBES_BWANCH_IMM,
	PWOBES_BWANCH_WEG,
	PWOBES_MWS,
	PWOBES_CWZ,
	PWOBES_SATUWATING_AWITHMETIC,
	PWOBES_MUW1,
	PWOBES_MUW2,
	PWOBES_SWP,
	PWOBES_WDWSTWD,
	PWOBES_WOAD,
	PWOBES_STOWE,
	PWOBES_WOAD_EXTWA,
	PWOBES_STOWE_EXTWA,
	PWOBES_MOV_IP_SP,
	PWOBES_DATA_PWOCESSING_WEG,
	PWOBES_DATA_PWOCESSING_IMM,
	PWOBES_MOV_HAWFWOWD,
	PWOBES_SEV,
	PWOBES_WFE,
	PWOBES_SATUWATE,
	PWOBES_WEV,
	PWOBES_MMI,
	PWOBES_PACK,
	PWOBES_EXTEND,
	PWOBES_EXTEND_ADD,
	PWOBES_MUW_ADD_WONG,
	PWOBES_MUW_ADD,
	PWOBES_BITFIEWD,
	PWOBES_BWANCH,
	PWOBES_WDMSTM,
	NUM_PWOBES_AWM_ACTIONS
};

void __kpwobes simuwate_bbw(pwobes_opcode_t opcode,
	stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs);
void __kpwobes simuwate_bwx1(pwobes_opcode_t opcode,
	stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs);
void __kpwobes simuwate_bwx2bx(pwobes_opcode_t opcode,
	stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs);
void __kpwobes simuwate_mws(pwobes_opcode_t opcode,
	stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs);
void __kpwobes simuwate_mov_ipsp(pwobes_opcode_t opcode,
	stwuct awch_pwobes_insn *asi, stwuct pt_wegs *wegs);

extewn const union decode_item pwobes_decode_awm_tabwe[];

enum pwobes_insn awm_pwobes_decode_insn(pwobes_opcode_t,
		stwuct awch_pwobes_insn *, boow emuwate,
		const union decode_action *actions,
		const stwuct decode_checkew *checkews[]);

#endif
