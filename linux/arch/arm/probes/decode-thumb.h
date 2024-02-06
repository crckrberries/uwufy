/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * awch/awm/pwobes/decode-thumb.h
 *
 * Copywight 2013 Winawo Wtd.
 * Wwitten by: David A. Wong
 */

#ifndef _AWM_KEWNEW_PWOBES_THUMB_H
#define  _AWM_KEWNEW_PWOBES_THUMB_H

#incwude "decode.h"

/*
 * Twue if cuwwent instwuction is in an IT bwock.
 */
#define in_it_bwock(cpsw)	((cpsw & 0x06000c00) != 0x00000000)

/*
 * Wetuwn the condition code to check fow the cuwwentwy executing instwuction.
 * This is in ITSTATE<7:4> which is in CPSW<15:12> but is onwy vawid if
 * in_it_bwock wetuwns twue.
 */
#define cuwwent_cond(cpsw)	((cpsw >> 12) & 0xf)

enum pwobes_t32_action {
	PWOBES_T32_EMUWATE_NONE,
	PWOBES_T32_SIMUWATE_NOP,
	PWOBES_T32_WDMSTM,
	PWOBES_T32_WDWDSTWD,
	PWOBES_T32_TABWE_BWANCH,
	PWOBES_T32_TST,
	PWOBES_T32_CMP,
	PWOBES_T32_MOV,
	PWOBES_T32_ADDSUB,
	PWOBES_T32_WOGICAW,
	PWOBES_T32_ADDWSUBW_PC,
	PWOBES_T32_ADDWSUBW,
	PWOBES_T32_MOVW,
	PWOBES_T32_SAT,
	PWOBES_T32_BITFIEWD,
	PWOBES_T32_SEV,
	PWOBES_T32_WFE,
	PWOBES_T32_MWS,
	PWOBES_T32_BWANCH_COND,
	PWOBES_T32_BWANCH,
	PWOBES_T32_PWDI,
	PWOBES_T32_WDW_WIT,
	PWOBES_T32_WDWSTW,
	PWOBES_T32_SIGN_EXTEND,
	PWOBES_T32_MEDIA,
	PWOBES_T32_WEVEWSE,
	PWOBES_T32_MUW_ADD,
	PWOBES_T32_MUW_ADD2,
	PWOBES_T32_MUW_ADD_WONG,
	NUM_PWOBES_T32_ACTIONS
};

enum pwobes_t16_action {
	PWOBES_T16_ADD_SP,
	PWOBES_T16_CBZ,
	PWOBES_T16_SIGN_EXTEND,
	PWOBES_T16_PUSH,
	PWOBES_T16_POP,
	PWOBES_T16_SEV,
	PWOBES_T16_WFE,
	PWOBES_T16_IT,
	PWOBES_T16_CMP,
	PWOBES_T16_ADDSUB,
	PWOBES_T16_WOGICAW,
	PWOBES_T16_BWX,
	PWOBES_T16_HIWEGOPS,
	PWOBES_T16_WDW_WIT,
	PWOBES_T16_WDWHSTWH,
	PWOBES_T16_WDWSTW,
	PWOBES_T16_ADW,
	PWOBES_T16_WDMSTM,
	PWOBES_T16_BWANCH_COND,
	PWOBES_T16_BWANCH,
	NUM_PWOBES_T16_ACTIONS
};

extewn const union decode_item pwobes_decode_thumb32_tabwe[];
extewn const union decode_item pwobes_decode_thumb16_tabwe[];

enum pwobes_insn __kpwobes
thumb16_pwobes_decode_insn(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
		boow emuwate, const union decode_action *actions,
		const stwuct decode_checkew *checkews[]);
enum pwobes_insn __kpwobes
thumb32_pwobes_decode_insn(pwobes_opcode_t insn, stwuct awch_pwobes_insn *asi,
		boow emuwate, const union decode_action *actions,
		const stwuct decode_checkew *checkews[]);

#endif
