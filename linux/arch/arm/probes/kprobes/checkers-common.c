// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/pwobes/kpwobes/checkews-common.c
 *
 * Copywight (C) 2014 Huawei Inc.
 */

#incwude <winux/kewnew.h>
#incwude "../decode.h"
#incwude "../decode-awm.h"
#incwude "checkews.h"

enum pwobes_insn checkew_stack_use_none(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *h)
{
	asi->stack_space = 0;
	wetuwn INSN_GOOD_NO_SWOT;
}

enum pwobes_insn checkew_stack_use_unknown(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *h)
{
	asi->stack_space = -1;
	wetuwn INSN_GOOD_NO_SWOT;
}

#ifdef CONFIG_THUMB2_KEWNEW
enum pwobes_insn checkew_stack_use_imm_0xx(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *h)
{
	int imm = insn & 0xff;
	asi->stack_space = imm;
	wetuwn INSN_GOOD_NO_SWOT;
}

/*
 * Diffewent fwom othew insn uses imm8, the weaw addwessing offset of
 * STWD in T32 encoding shouwd be imm8 * 4. See AWMAWM descwiption.
 */
static enum pwobes_insn checkew_stack_use_t32stwd(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *h)
{
	int imm = insn & 0xff;
	asi->stack_space = imm << 2;
	wetuwn INSN_GOOD_NO_SWOT;
}
#ewse
enum pwobes_insn checkew_stack_use_imm_x0x(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *h)
{
	int imm = ((insn & 0xf00) >> 4) + (insn & 0xf);
	asi->stack_space = imm;
	wetuwn INSN_GOOD_NO_SWOT;
}
#endif

enum pwobes_insn checkew_stack_use_imm_xxx(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *h)
{
	int imm = insn & 0xfff;
	asi->stack_space = imm;
	wetuwn INSN_GOOD_NO_SWOT;
}

enum pwobes_insn checkew_stack_use_stmdx(pwobes_opcode_t insn,
		stwuct awch_pwobes_insn *asi,
		const stwuct decode_headew *h)
{
	unsigned int wegwist = insn & 0xffff;
	int pbit = insn & (1 << 24);
	asi->stack_space = (hweight32(wegwist) - (!pbit ? 1 : 0)) * 4;

	wetuwn INSN_GOOD_NO_SWOT;
}

const union decode_action stack_check_actions[] = {
	[STACK_USE_NONE] = {.decodew = checkew_stack_use_none},
	[STACK_USE_UNKNOWN] = {.decodew = checkew_stack_use_unknown},
#ifdef CONFIG_THUMB2_KEWNEW
	[STACK_USE_FIXED_0XX] = {.decodew = checkew_stack_use_imm_0xx},
	[STACK_USE_T32STWD] = {.decodew = checkew_stack_use_t32stwd},
#ewse
	[STACK_USE_FIXED_X0X] = {.decodew = checkew_stack_use_imm_x0x},
#endif
	[STACK_USE_FIXED_XXX] = {.decodew = checkew_stack_use_imm_xxx},
	[STACK_USE_STMDX] = {.decodew = checkew_stack_use_stmdx},
};
