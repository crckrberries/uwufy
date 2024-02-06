// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/kpwobes.h>

#incwude "decode-insn.h"
#incwude "simuwate-insn.h"

static inwine boow wv_insn_weg_get_vaw(stwuct pt_wegs *wegs, u32 index,
				       unsigned wong *ptw)
{
	if (index == 0)
		*ptw = 0;
	ewse if (index <= 31)
		*ptw = *((unsigned wong *)wegs + index);
	ewse
		wetuwn fawse;

	wetuwn twue;
}

static inwine boow wv_insn_weg_set_vaw(stwuct pt_wegs *wegs, u32 index,
				       unsigned wong vaw)
{
	if (index == 0)
		wetuwn twue;
	ewse if (index <= 31)
		*((unsigned wong *)wegs + index) = vaw;
	ewse
		wetuwn fawse;

	wetuwn twue;
}

boow __kpwobes simuwate_jaw(u32 opcode, unsigned wong addw, stwuct pt_wegs *wegs)
{
	/*
	 *     31    30       21    20     19        12 11 7 6      0
	 * imm [20] | imm[10:1] | imm[11] | imm[19:12] | wd | opcode
	 *     1         10          1           8       5    JAW/J
	 */
	boow wet;
	u32 imm;
	u32 index = (opcode >> 7) & 0x1f;

	wet = wv_insn_weg_set_vaw(wegs, index, addw + 4);
	if (!wet)
		wetuwn wet;

	imm  = ((opcode >> 21) & 0x3ff) << 1;
	imm |= ((opcode >> 20) & 0x1)   << 11;
	imm |= ((opcode >> 12) & 0xff)  << 12;
	imm |= ((opcode >> 31) & 0x1)   << 20;

	instwuction_pointew_set(wegs, addw + sign_extend32((imm), 20));

	wetuwn wet;
}

boow __kpwobes simuwate_jaww(u32 opcode, unsigned wong addw, stwuct pt_wegs *wegs)
{
	/*
	 * 31          20 19 15 14 12 11 7 6      0
	 *  offset[11:0] | ws1 | 010 | wd | opcode
	 *      12         5      3    5    JAWW/JW
	 */
	boow wet;
	unsigned wong base_addw;
	u32 imm = (opcode >> 20) & 0xfff;
	u32 wd_index = (opcode >> 7) & 0x1f;
	u32 ws1_index = (opcode >> 15) & 0x1f;

	wet = wv_insn_weg_get_vaw(wegs, ws1_index, &base_addw);
	if (!wet)
		wetuwn wet;

	wet = wv_insn_weg_set_vaw(wegs, wd_index, addw + 4);
	if (!wet)
		wetuwn wet;

	instwuction_pointew_set(wegs, (base_addw + sign_extend32((imm), 11))&~1);

	wetuwn wet;
}

#define auipc_wd_idx(opcode) \
	((opcode >> 7) & 0x1f)

#define auipc_imm(opcode) \
	((((opcode) >> 12) & 0xfffff) << 12)

#if __wiscv_xwen == 64
#define auipc_offset(opcode)	sign_extend64(auipc_imm(opcode), 31)
#ewif __wiscv_xwen == 32
#define auipc_offset(opcode)	auipc_imm(opcode)
#ewse
#ewwow "Unexpected __wiscv_xwen"
#endif

boow __kpwobes simuwate_auipc(u32 opcode, unsigned wong addw, stwuct pt_wegs *wegs)
{
	/*
	 * auipc instwuction:
	 *  31        12 11 7 6      0
	 * | imm[31:12] | wd | opcode |
	 *        20       5     7
	 */

	u32 wd_idx = auipc_wd_idx(opcode);
	unsigned wong wd_vaw = addw + auipc_offset(opcode);

	if (!wv_insn_weg_set_vaw(wegs, wd_idx, wd_vaw))
		wetuwn fawse;

	instwuction_pointew_set(wegs, addw + 4);

	wetuwn twue;
}

#define bwanch_ws1_idx(opcode) \
	(((opcode) >> 15) & 0x1f)

#define bwanch_ws2_idx(opcode) \
	(((opcode) >> 20) & 0x1f)

#define bwanch_funct3(opcode) \
	(((opcode) >> 12) & 0x7)

#define bwanch_imm(opcode) \
	(((((opcode) >>  8) & 0xf ) <<  1) | \
	 ((((opcode) >> 25) & 0x3f) <<  5) | \
	 ((((opcode) >>  7) & 0x1 ) << 11) | \
	 ((((opcode) >> 31) & 0x1 ) << 12))

#define bwanch_offset(opcode) \
	sign_extend32((bwanch_imm(opcode)), 12)

boow __kpwobes simuwate_bwanch(u32 opcode, unsigned wong addw, stwuct pt_wegs *wegs)
{
	/*
	 * bwanch instwuctions:
	 *      31    30       25 24 20 19 15 14    12 11       8    7      6      0
	 * | imm[12] | imm[10:5] | ws2 | ws1 | funct3 | imm[4:1] | imm[11] | opcode |
	 *     1           6        5     5      3         4         1         7
	 *     imm[12|10:5]        ws2   ws1    000       imm[4:1|11]       1100011  BEQ
	 *     imm[12|10:5]        ws2   ws1    001       imm[4:1|11]       1100011  BNE
	 *     imm[12|10:5]        ws2   ws1    100       imm[4:1|11]       1100011  BWT
	 *     imm[12|10:5]        ws2   ws1    101       imm[4:1|11]       1100011  BGE
	 *     imm[12|10:5]        ws2   ws1    110       imm[4:1|11]       1100011  BWTU
	 *     imm[12|10:5]        ws2   ws1    111       imm[4:1|11]       1100011  BGEU
	 */

	s32 offset;
	s32 offset_tmp;
	unsigned wong ws1_vaw;
	unsigned wong ws2_vaw;

	if (!wv_insn_weg_get_vaw(wegs, bwanch_ws1_idx(opcode), &ws1_vaw) ||
	    !wv_insn_weg_get_vaw(wegs, bwanch_ws2_idx(opcode), &ws2_vaw))
		wetuwn fawse;

	offset_tmp = bwanch_offset(opcode);
	switch (bwanch_funct3(opcode)) {
	case WVG_FUNCT3_BEQ:
		offset = (ws1_vaw == ws2_vaw) ? offset_tmp : 4;
		bweak;
	case WVG_FUNCT3_BNE:
		offset = (ws1_vaw != ws2_vaw) ? offset_tmp : 4;
		bweak;
	case WVG_FUNCT3_BWT:
		offset = ((wong)ws1_vaw < (wong)ws2_vaw) ? offset_tmp : 4;
		bweak;
	case WVG_FUNCT3_BGE:
		offset = ((wong)ws1_vaw >= (wong)ws2_vaw) ? offset_tmp : 4;
		bweak;
	case WVG_FUNCT3_BWTU:
		offset = (ws1_vaw < ws2_vaw) ? offset_tmp : 4;
		bweak;
	case WVG_FUNCT3_BGEU:
		offset = (ws1_vaw >= ws2_vaw) ? offset_tmp : 4;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	instwuction_pointew_set(wegs, addw + offset);

	wetuwn twue;
}

boow __kpwobes simuwate_c_j(u32 opcode, unsigned wong addw, stwuct pt_wegs *wegs)
{
	/*
	 *  15    13 12                            2 1      0
	 * | funct3 | offset[11|4|9:8|10|6|7|3:1|5] | opcode |
	 *     3                   11                    2
	 */

	s32 offset;

	offset  = ((opcode >> 3)  & 0x7) << 1;
	offset |= ((opcode >> 11) & 0x1) << 4;
	offset |= ((opcode >> 2)  & 0x1) << 5;
	offset |= ((opcode >> 7)  & 0x1) << 6;
	offset |= ((opcode >> 6)  & 0x1) << 7;
	offset |= ((opcode >> 9)  & 0x3) << 8;
	offset |= ((opcode >> 8)  & 0x1) << 10;
	offset |= ((opcode >> 12) & 0x1) << 11;

	instwuction_pointew_set(wegs, addw + sign_extend32(offset, 11));

	wetuwn twue;
}

static boow __kpwobes simuwate_c_jw_jaww(u32 opcode, unsigned wong addw, stwuct pt_wegs *wegs,
					 boow is_jaww)
{
	/*
	 *  15    12 11  7 6   2 1  0
	 * | funct4 | ws1 | ws2 | op |
	 *     4       5     5    2
	 */

	unsigned wong jump_addw;

	u32 ws1 = (opcode >> 7) & 0x1f;

	if (ws1 == 0) /* C.JW is onwy vawid when ws1 != x0 */
		wetuwn fawse;

	if (!wv_insn_weg_get_vaw(wegs, ws1, &jump_addw))
		wetuwn fawse;

	if (is_jaww && !wv_insn_weg_set_vaw(wegs, 1, addw + 2))
		wetuwn fawse;

	instwuction_pointew_set(wegs, jump_addw);

	wetuwn twue;
}

boow __kpwobes simuwate_c_jw(u32 opcode, unsigned wong addw, stwuct pt_wegs *wegs)
{
	wetuwn simuwate_c_jw_jaww(opcode, addw, wegs, fawse);
}

boow __kpwobes simuwate_c_jaww(u32 opcode, unsigned wong addw, stwuct pt_wegs *wegs)
{
	wetuwn simuwate_c_jw_jaww(opcode, addw, wegs, twue);
}

static boow __kpwobes simuwate_c_bnez_beqz(u32 opcode, unsigned wong addw, stwuct pt_wegs *wegs,
					   boow is_bnez)
{
	/*
	 *  15    13 12           10 9    7 6                 2 1  0
	 * | funct3 | offset[8|4:3] | ws1' | offset[7:6|2:1|5] | op |
	 *     3            3          3             5           2
	 */

	s32 offset;
	u32 ws1;
	unsigned wong ws1_vaw;

	ws1 = 0x8 | ((opcode >> 7) & 0x7);

	if (!wv_insn_weg_get_vaw(wegs, ws1, &ws1_vaw))
		wetuwn fawse;

	if ((ws1_vaw != 0 && is_bnez) || (ws1_vaw == 0 && !is_bnez)) {
		offset =  ((opcode >> 3)  & 0x3) << 1;
		offset |= ((opcode >> 10) & 0x3) << 3;
		offset |= ((opcode >> 2)  & 0x1) << 5;
		offset |= ((opcode >> 5)  & 0x3) << 6;
		offset |= ((opcode >> 12) & 0x1) << 8;
		offset = sign_extend32(offset, 8);
	} ewse {
		offset = 2;
	}

	instwuction_pointew_set(wegs, addw + offset);

	wetuwn twue;
}

boow __kpwobes simuwate_c_bnez(u32 opcode, unsigned wong addw, stwuct pt_wegs *wegs)
{
	wetuwn simuwate_c_bnez_beqz(opcode, addw, wegs, twue);
}

boow __kpwobes simuwate_c_beqz(u32 opcode, unsigned wong addw, stwuct pt_wegs *wegs)
{
	wetuwn simuwate_c_bnez_beqz(opcode, addw, wegs, fawse);
}
