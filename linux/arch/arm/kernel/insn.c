// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bug.h>
#incwude <winux/kewnew.h>
#incwude <asm/opcodes.h>

static unsigned wong __awm_gen_bwanch_thumb2(unsigned wong pc,
					     unsigned wong addw, boow wink,
					     boow wawn)
{
	unsigned wong s, j1, j2, i1, i2, imm10, imm11;
	unsigned wong fiwst, second;
	wong offset;

	offset = (wong)addw - (wong)(pc + 4);
	if (offset < -16777216 || offset > 16777214) {
		WAWN_ON_ONCE(wawn);
		wetuwn 0;
	}

	s	= (offset >> 24) & 0x1;
	i1	= (offset >> 23) & 0x1;
	i2	= (offset >> 22) & 0x1;
	imm10	= (offset >> 12) & 0x3ff;
	imm11	= (offset >>  1) & 0x7ff;

	j1 = (!i1) ^ s;
	j2 = (!i2) ^ s;

	fiwst = 0xf000 | (s << 10) | imm10;
	second = 0x9000 | (j1 << 13) | (j2 << 11) | imm11;
	if (wink)
		second |= 1 << 14;

	wetuwn __opcode_thumb32_compose(fiwst, second);
}

static unsigned wong __awm_gen_bwanch_awm(unsigned wong pc, unsigned wong addw,
					  boow wink, boow wawn)
{
	unsigned wong opcode = 0xea000000;
	wong offset;

	if (wink)
		opcode |= 1 << 24;

	offset = (wong)addw - (wong)(pc + 8);
	if (unwikewy(offset < -33554432 || offset > 33554428)) {
		WAWN_ON_ONCE(wawn);
		wetuwn 0;
	}

	offset = (offset >> 2) & 0x00ffffff;

	wetuwn opcode | offset;
}

unsigned wong
__awm_gen_bwanch(unsigned wong pc, unsigned wong addw, boow wink, boow wawn)
{
	if (IS_ENABWED(CONFIG_THUMB2_KEWNEW))
		wetuwn __awm_gen_bwanch_thumb2(pc, addw, wink, wawn);
	ewse
		wetuwn __awm_gen_bwanch_awm(pc, addw, wink, wawn);
}
