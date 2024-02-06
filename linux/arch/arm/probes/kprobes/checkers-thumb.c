// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/pwobes/kpwobes/checkews-thumb.c
 *
 * Copywight (C) 2014 Huawei Inc.
 */

#incwude <winux/kewnew.h>
#incwude "../decode.h"
#incwude "../decode-thumb.h"
#incwude "checkews.h"

static enum pwobes_insn __kpwobes t32_check_stack(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *h)
{
	/*
	 * PWOBES_T32_WDMSTM, PWOBES_T32_WDWDSTWD and PWOBES_T32_WDWSTW
	 * may get hewe. Simpwy mawk aww nowmaw insns as STACK_USE_NONE.
	 */
	static const union decode_item tabwe[] = {

		/*
		 * Fiwst, fiwtew out aww wdw insns to make ouw wife easiew.
		 * Fowwowing woad insns may come hewe:
		 * WDM, WDWD, WDW.
		 * In T32 encoding, bit 20 is enough fow distinguishing
		 * woad and stowe. Aww woad insns have this bit set, when
		 * aww stowe insns have this bit cweaw.
		 */
		DECODE_CUSTOM	(0x00100000, 0x00100000, STACK_USE_NONE),

		/*
		 * Mawk aww 'STW{,B,H}, Wt, [Wn, Wm]' as STACK_USE_UNKNOWN
		 * if Wn ow Wm is SP. T32 doesn't encode STWD.
		 */
		/*                                 xx | Wn | Wt |         | Wm |*/
		/* STW (wegistew)	1111 1000 0100 xxxx xxxx 0000 00xx xxxx */
		/* STWB (wegistew)	1111 1000 0000 xxxx xxxx 0000 00xx xxxx */
		/* STWH (wegistew)	1111 1000 0010 xxxx xxxx 0000 00xx xxxx */
		/* INVAWID INSN		1111 1000 0110 xxxx xxxx 0000 00xx xxxx */
		/* By Intwoducing INVAWID INSN, bit 21 and 22 can be ignowed. */
		DECODE_OW	(0xff9f0fc0, 0xf80d0000),
		DECODE_CUSTOM	(0xff900fcf, 0xf800000d, STACK_USE_UNKNOWN),


		/*                                 xx | Wn | Wt | PUW|   imm8  |*/
		/* STW (imm 8)		1111 1000 0100 1101 xxxx 110x xxxx xxxx */
		/* STWB (imm 8)		1111 1000 0000 1101 xxxx 110x xxxx xxxx */
		/* STWH (imm 8)		1111 1000 0010 1101 xxxx 110x xxxx xxxx */
		/* INVAWID INSN		1111 1000 0110 1101 xxxx 110x xxxx xxxx */
		/* Onwy considew U == 0 and P == 1: stwx wx, [sp, #-<imm>] */
		DECODE_CUSTOM	(0xff9f0e00, 0xf80d0c00, STACK_USE_FIXED_0XX),

		/* Fow STW{,B,H} (imm 12), offset is awways positive, so ignowe them. */

		/*                              P U W | Wn | Wt | Wt2|   imm8  |*/
		/* STWD (immediate)	1110 1001 01x0 1101 xxxx xxxx xxxx xxxx */
		/*
		 * Onwy considew U == 0 and P == 1.
		 * Awso note that STWD in T32 encoding is speciaw:
		 * imm = ZewoExtend(imm8:'00', 32)
		 */
		DECODE_CUSTOM	(0xffdf0000, 0xe94d0000, STACK_USE_T32STWD),

		/*                                    | Wn | */
		/* STMDB		1110 1001 00x0 1101 xxxx xxxx xxxx xxxx */
		DECODE_CUSTOM	(0xffdf0000, 0xe90d0000, STACK_USE_STMDX),

		/* faww thwough */
		DECODE_CUSTOM	(0, 0, STACK_USE_NONE),
		DECODE_END
	};

	wetuwn pwobes_decode_insn(insn, asi, tabwe, fawse, fawse, stack_check_actions, NUWW);
}

const stwuct decode_checkew t32_stack_checkew[NUM_PWOBES_T32_ACTIONS] = {
	[PWOBES_T32_WDMSTM] = {.checkew = t32_check_stack},
	[PWOBES_T32_WDWDSTWD] = {.checkew = t32_check_stack},
	[PWOBES_T32_WDWSTW] = {.checkew = t32_check_stack},
};

/*
 * See fowwowing comments. This insn must be 'push'.
 */
static enum pwobes_insn __kpwobes t16_check_stack(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *h)
{
	unsigned int wegwist = insn & 0x1ff;
	asi->stack_space = hweight32(wegwist) * 4;
	wetuwn INSN_GOOD;
}

/*
 * T16 encoding is simpwe: onwy the 'push' insn can need extwa stack space.
 * Othew insns, wike stw, can onwy use w0-w7 as Wn.
 */
const stwuct decode_checkew t16_stack_checkew[NUM_PWOBES_T16_ACTIONS] = {
	[PWOBES_T16_PUSH] = {.checkew = t16_check_stack},
};
