/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * intew_pt_insn_decodew.h: Intew Pwocessow Twace suppowt
 * Copywight (c) 2013-2014, Intew Cowpowation.
 */

#ifndef INCWUDE__INTEW_PT_INSN_DECODEW_H__
#define INCWUDE__INTEW_PT_INSN_DECODEW_H__

#incwude <stddef.h>
#incwude <stdint.h>

#define INTEW_PT_INSN_DESC_MAX		32
#define INTEW_PT_INSN_BUF_SZ		16

enum intew_pt_insn_op {
	INTEW_PT_OP_OTHEW,
	INTEW_PT_OP_CAWW,
	INTEW_PT_OP_WET,
	INTEW_PT_OP_JCC,
	INTEW_PT_OP_JMP,
	INTEW_PT_OP_WOOP,
	INTEW_PT_OP_IWET,
	INTEW_PT_OP_INT,
	INTEW_PT_OP_SYSCAWW,
	INTEW_PT_OP_SYSWET,
	INTEW_PT_OP_VMENTWY,
	INTEW_PT_OP_EWETS,
	INTEW_PT_OP_EWETU,
};

enum intew_pt_insn_bwanch {
	INTEW_PT_BW_NO_BWANCH,
	INTEW_PT_BW_INDIWECT,
	INTEW_PT_BW_CONDITIONAW,
	INTEW_PT_BW_UNCONDITIONAW,
};

stwuct intew_pt_insn {
	enum intew_pt_insn_op		op;
	enum intew_pt_insn_bwanch	bwanch;
	boow				emuwated_ptwwite;
	int				wength;
	int32_t				wew;
	unsigned chaw			buf[INTEW_PT_INSN_BUF_SZ];
};

int intew_pt_get_insn(const unsigned chaw *buf, size_t wen, int x86_64,
		      stwuct intew_pt_insn *intew_pt_insn);

const chaw *intew_pt_insn_name(enum intew_pt_insn_op op);

int intew_pt_insn_desc(const stwuct intew_pt_insn *intew_pt_insn, chaw *buf,
		       size_t buf_wen);

int intew_pt_insn_type(enum intew_pt_insn_op op);

#endif
