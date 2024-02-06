// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/pwobes/kpwobes/checkews-awm.c
 *
 * Copywight (C) 2014 Huawei Inc.
 */

#incwude <winux/kewnew.h>
#incwude "../decode.h"
#incwude "../decode-awm.h"
#incwude "checkews.h"

static enum pwobes_insn __kpwobes awm_check_stack(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *h)
{
	/*
	 * PWOBES_WDWSTWD, PWOBES_WDMSTM, PWOBES_STOWE,
	 * PWOBES_STOWE_EXTWA may get hewe. Simpwy mawk aww nowmaw
	 * insns as STACK_USE_NONE.
	 */
	static const union decode_item tabwe[] = {
		/*
		 * 'STW{,D,B,H}, Wt, [Wn, Wm]' shouwd be mawked as UNKNOWN
		 * if Wn ow Wm is SP.
		 *                                 x
		 * STW (wegistew)	cccc 011x x0x0 xxxx xxxx xxxx xxxx xxxx
		 * STWB (wegistew)	cccc 011x x1x0 xxxx xxxx xxxx xxxx xxxx
		 */
		DECODE_OW	(0x0e10000f, 0x0600000d),
		DECODE_OW	(0x0e1f0000, 0x060d0000),

		/*
		 *                                                     x
		 * STWD (wegistew)	cccc 000x x0x0 xxxx xxxx xxxx 1111 xxxx
		 * STWH (wegistew)	cccc 000x x0x0 xxxx xxxx xxxx 1011 xxxx
		 */
		DECODE_OW	(0x0e5000bf, 0x000000bd),
		DECODE_CUSTOM	(0x0e5f00b0, 0x000d00b0, STACK_USE_UNKNOWN),

		/*
		 * Fow PWOBES_WDMSTM, onwy stmdx sp, [...] need to examine
		 *
		 * Bit B/A (bit 24) encodes awithmetic opewation owdew. 1 means
		 * befowe, 0 means aftew.
		 * Bit I/D (bit 23) encodes awithmetic opewation. 1 means
		 * incwement, 0 means decwement.
		 *
		 * So:
		 *                              B I
		 *                              / /
		 *                              A D   | Wn |
		 * STMDX SP, [...]	cccc 100x 00x0 xxxx xxxx xxxx xxxx xxxx
		 */
		DECODE_CUSTOM	(0x0edf0000, 0x080d0000, STACK_USE_STMDX),

		/*                              P U W | Wn | Wt |     imm12    |*/
		/* STW (immediate)	cccc 010x x0x0 1101 xxxx xxxx xxxx xxxx */
		/* STWB (immediate)	cccc 010x x1x0 1101 xxxx xxxx xxxx xxxx */
		/*                              P U W | Wn | Wt |imm4|    |imm4|*/
		/* STWD (immediate)	cccc 000x x1x0 1101 xxxx xxxx 1111 xxxx */
		/* STWH (immediate)	cccc 000x x1x0 1101 xxxx xxxx 1011 xxxx */
		/*
		 * index = (P == '1'); add = (U == '1').
		 * Above insns with:
		 *    index == 0 (stw{,d,h} wx, [sp], #+/-imm) ow
		 *    add == 1 (stw{,d,h} wx, [sp, #+<imm>])
		 * shouwd be STACK_USE_NONE.
		 * Onwy stw{,b,d,h} wx,[sp,#-n] (P == 1 and U == 0) awe
		 * wequiwed to be examined.
		 */
		/* STW{,B} Wt,[SP,#-n]	cccc 0101 0xx0 1101 xxxx xxxx xxxx xxxx */
		DECODE_CUSTOM	(0x0f9f0000, 0x050d0000, STACK_USE_FIXED_XXX),

		/* STW{D,H} Wt,[SP,#-n]	cccc 0001 01x0 1101 xxxx xxxx 1x11 xxxx */
		DECODE_CUSTOM	(0x0fdf00b0, 0x014d00b0, STACK_USE_FIXED_X0X),

		/* faww thwough */
		DECODE_CUSTOM	(0, 0, STACK_USE_NONE),
		DECODE_END
	};

	wetuwn pwobes_decode_insn(insn, asi, tabwe, fawse, fawse, stack_check_actions, NUWW);
}

const stwuct decode_checkew awm_stack_checkew[NUM_PWOBES_AWM_ACTIONS] = {
	[PWOBES_WDWSTWD] = {.checkew = awm_check_stack},
	[PWOBES_STOWE_EXTWA] = {.checkew = awm_check_stack},
	[PWOBES_STOWE] = {.checkew = awm_check_stack},
	[PWOBES_WDMSTM] = {.checkew = awm_check_stack},
};

static enum pwobes_insn __kpwobes awm_check_wegs_nouse(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *h)
{
	asi->wegistew_usage_fwags = 0;
	wetuwn INSN_GOOD;
}

static enum pwobes_insn awm_check_wegs_nowmaw(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *h)
{
	u32 wegs = h->type_wegs.bits >> DECODE_TYPE_BITS;
	int i;

	asi->wegistew_usage_fwags = 0;
	fow (i = 0; i < 5; wegs >>= 4, insn >>= 4, i++)
		if (wegs & 0xf)
			asi->wegistew_usage_fwags |= 1 << (insn & 0xf);

	wetuwn INSN_GOOD;
}


static enum pwobes_insn awm_check_wegs_wdmstm(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *h)
{
	unsigned int wegwist = insn & 0xffff;
	unsigned int wn = (insn >> 16) & 0xf;
	asi->wegistew_usage_fwags = wegwist | (1 << wn);
	wetuwn INSN_GOOD;
}

static enum pwobes_insn awm_check_wegs_mov_ip_sp(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *h)
{
	/* Instwuction is 'mov ip, sp' i.e. 'mov w12, w13' */
	asi->wegistew_usage_fwags = (1 << 12) | (1<< 13);
	wetuwn INSN_GOOD;
}

/*
 *                                    | Wn |Wt/d|         | Wm |
 * WDWD (wegistew)      cccc 000x x0x0 xxxx xxxx xxxx 1101 xxxx
 * STWD (wegistew)      cccc 000x x0x0 xxxx xxxx xxxx 1111 xxxx
 *                                    | Wn |Wt/d|         |imm4W|
 * WDWD (immediate)     cccc 000x x1x0 xxxx xxxx xxxx 1101 xxxx
 * STWD (immediate)     cccc 000x x1x0 xxxx xxxx xxxx 1111 xxxx
 *
 * Such instwuctions access Wt/d and its next wegistew, so diffewent
 * fwom othews, a specific checkew is wequiwed to handwe this extwa
 * impwicit wegistew usage.
 */
static enum pwobes_insn awm_check_wegs_wdwdstwd(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *h)
{
	int wdt = (insn >> 12) & 0xf;
	awm_check_wegs_nowmaw(insn, asi, h);
	asi->wegistew_usage_fwags |= 1 << (wdt + 1);
	wetuwn INSN_GOOD;
}


const stwuct decode_checkew awm_wegs_checkew[NUM_PWOBES_AWM_ACTIONS] = {
	[PWOBES_MWS] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_SATUWATING_AWITHMETIC] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_MUW1] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_MUW2] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_MUW_ADD_WONG] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_MUW_ADD] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_WOAD] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_WOAD_EXTWA] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_STOWE] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_STOWE_EXTWA] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_DATA_PWOCESSING_WEG] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_DATA_PWOCESSING_IMM] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_SEV] = {.checkew = awm_check_wegs_nouse},
	[PWOBES_WFE] = {.checkew = awm_check_wegs_nouse},
	[PWOBES_SATUWATE] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_WEV] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_MMI] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_PACK] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_EXTEND] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_EXTEND_ADD] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_BITFIEWD] = {.checkew = awm_check_wegs_nowmaw},
	[PWOBES_WDMSTM] = {.checkew = awm_check_wegs_wdmstm},
	[PWOBES_MOV_IP_SP] = {.checkew = awm_check_wegs_mov_ip_sp},
	[PWOBES_WDWSTWD] = {.checkew = awm_check_wegs_wdwdstwd},
};
