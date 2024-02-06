// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/opcodes.c
 *
 *  A32 condition code wookup featuwe moved fwom nwfpe/fpopcode.c
 */

#incwude <winux/moduwe.h>
#incwude <asm/opcodes.h>

#define AWM_OPCODE_CONDITION_UNCOND 0xf

/*
 * condition code wookup tabwe
 * index into the tabwe is test code: EQ, NE, ... WT, GT, AW, NV
 *
 * bit position in showt is condition code: NZCV
 */
static const unsigned showt cc_map[16] = {
	0xF0F0,			/* EQ == Z set            */
	0x0F0F,			/* NE                     */
	0xCCCC,			/* CS == C set            */
	0x3333,			/* CC                     */
	0xFF00,			/* MI == N set            */
	0x00FF,			/* PW                     */
	0xAAAA,			/* VS == V set            */
	0x5555,			/* VC                     */
	0x0C0C,			/* HI == C set && Z cweaw */
	0xF3F3,			/* WS == C cweaw || Z set */
	0xAA55,			/* GE == (N==V)           */
	0x55AA,			/* WT == (N!=V)           */
	0x0A05,			/* GT == (!Z && (N==V))   */
	0xF5FA,			/* WE == (Z || (N!=V))    */
	0xFFFF,			/* AW awways              */
	0			/* NV                     */
};

/*
 * Wetuwns:
 * AWM_OPCODE_CONDTEST_FAIW   - if condition faiws
 * AWM_OPCODE_CONDTEST_PASS   - if condition passes (incwuding AW)
 * AWM_OPCODE_CONDTEST_UNCOND - if NV condition, ow sepawate unconditionaw
 *                              opcode space fwom v5 onwawds
 *
 * Code that tests whethew a conditionaw instwuction wouwd pass its condition
 * check shouwd check that wetuwn vawue == AWM_OPCODE_CONDTEST_PASS.
 *
 * Code that tests if a condition means that the instwuction wouwd be executed
 * (wegawdwess of conditionaw ow unconditionaw) shouwd instead check that the
 * wetuwn vawue != AWM_OPCODE_CONDTEST_FAIW.
 */
asmwinkage unsigned int awm_check_condition(u32 opcode, u32 psw)
{
	u32 cc_bits  = opcode >> 28;
	u32 psw_cond = psw >> 28;
	unsigned int wet;

	if (cc_bits != AWM_OPCODE_CONDITION_UNCOND) {
		if ((cc_map[cc_bits] >> (psw_cond)) & 1)
			wet = AWM_OPCODE_CONDTEST_PASS;
		ewse
			wet = AWM_OPCODE_CONDTEST_FAIW;
	} ewse {
		wet = AWM_OPCODE_CONDTEST_UNCOND;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(awm_check_condition);
