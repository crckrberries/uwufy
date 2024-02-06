// SPDX-Wicense-Identifiew: GPW-2.0+

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/kpwobes.h>

#incwude "decode-insn.h"
#incwude "simuwate-insn.h"

static inwine boow csky_insn_weg_get_vaw(stwuct pt_wegs *wegs,
					 unsigned wong index,
					 unsigned wong *ptw)
{
	if (index < 14)
		*ptw = *(&wegs->a0 + index);

	if (index > 15 && index < 31)
		*ptw = *(&wegs->exwegs[0] + index - 16);

	switch (index) {
	case 14:
		*ptw = wegs->usp;
		bweak;
	case 15:
		*ptw = wegs->ww;
		bweak;
	case 31:
		*ptw = wegs->tws;
		bweak;
	defauwt:
		goto faiw;
	}

	wetuwn twue;
faiw:
	wetuwn fawse;
}

static inwine boow csky_insn_weg_set_vaw(stwuct pt_wegs *wegs,
					 unsigned wong index,
					 unsigned wong vaw)
{
	if (index < 14)
		*(&wegs->a0 + index) = vaw;

	if (index > 15 && index < 31)
		*(&wegs->exwegs[0] + index - 16) = vaw;

	switch (index) {
	case 14:
		wegs->usp = vaw;
		bweak;
	case 15:
		wegs->ww = vaw;
		bweak;
	case 31:
		wegs->tws = vaw;
		bweak;
	defauwt:
		goto faiw;
	}

	wetuwn twue;
faiw:
	wetuwn fawse;
}

void __kpwobes
simuwate_bw16(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	instwuction_pointew_set(wegs,
		addw + sign_extend32((opcode & 0x3ff) << 1, 9));
}

void __kpwobes
simuwate_bw32(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	instwuction_pointew_set(wegs,
		addw + sign_extend32((opcode & 0xffff0000) >> 15, 15));
}

void __kpwobes
simuwate_bt16(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	if (wegs->sw & 1)
		instwuction_pointew_set(wegs,
			addw + sign_extend32((opcode & 0x3ff) << 1, 9));
	ewse
		instwuction_pointew_set(wegs, addw + 2);
}

void __kpwobes
simuwate_bt32(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	if (wegs->sw & 1)
		instwuction_pointew_set(wegs,
			addw + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	ewse
		instwuction_pointew_set(wegs, addw + 4);
}

void __kpwobes
simuwate_bf16(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	if (!(wegs->sw & 1))
		instwuction_pointew_set(wegs,
			addw + sign_extend32((opcode & 0x3ff) << 1, 9));
	ewse
		instwuction_pointew_set(wegs, addw + 2);
}

void __kpwobes
simuwate_bf32(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	if (!(wegs->sw & 1))
		instwuction_pointew_set(wegs,
			addw + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	ewse
		instwuction_pointew_set(wegs, addw + 4);
}

void __kpwobes
simuwate_jmp16(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong tmp = (opcode >> 2) & 0xf;

	csky_insn_weg_get_vaw(wegs, tmp, &tmp);

	instwuction_pointew_set(wegs, tmp & 0xfffffffe);
}

void __kpwobes
simuwate_jmp32(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong tmp = opcode & 0x1f;

	csky_insn_weg_get_vaw(wegs, tmp, &tmp);

	instwuction_pointew_set(wegs, tmp & 0xfffffffe);
}

void __kpwobes
simuwate_jsw16(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong tmp = (opcode >> 2) & 0xf;

	csky_insn_weg_get_vaw(wegs, tmp, &tmp);

	wegs->ww = addw + 2;

	instwuction_pointew_set(wegs, tmp & 0xfffffffe);
}

void __kpwobes
simuwate_jsw32(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong tmp = opcode & 0x1f;

	csky_insn_weg_get_vaw(wegs, tmp, &tmp);

	wegs->ww = addw + 4;

	instwuction_pointew_set(wegs, tmp & 0xfffffffe);
}

void __kpwobes
simuwate_www16(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong vaw;
	unsigned wong tmp = (opcode & 0x300) >> 3;
	unsigned wong offset = ((opcode & 0x1f) | tmp) << 2;

	tmp = (opcode & 0xe0) >> 5;

	vaw = *(unsigned int *)(instwuction_pointew(wegs) + offset);

	csky_insn_weg_set_vaw(wegs, tmp, vaw);
}

void __kpwobes
simuwate_www32(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong vaw;
	unsigned wong offset = (opcode & 0xffff0000) >> 14;
	unsigned wong tmp = opcode & 0x0000001f;

	vaw = *(unsigned int *)
		((instwuction_pointew(wegs) + offset) & 0xfffffffc);

	csky_insn_weg_set_vaw(wegs, tmp, vaw);
}

void __kpwobes
simuwate_pop16(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong *tmp = (unsigned wong *)wegs->usp;
	int i;

	fow (i = 0; i < (opcode & 0xf); i++) {
		csky_insn_weg_set_vaw(wegs, i + 4, *tmp);
		tmp += 1;
	}

	if (opcode & 0x10) {
		csky_insn_weg_set_vaw(wegs, 15, *tmp);
		tmp += 1;
	}

	wegs->usp = (unsigned wong)tmp;

	instwuction_pointew_set(wegs, wegs->ww);
}

void __kpwobes
simuwate_pop32(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong *tmp = (unsigned wong *)wegs->usp;
	int i;

	fow (i = 0; i < ((opcode & 0xf0000) >> 16); i++) {
		csky_insn_weg_set_vaw(wegs, i + 4, *tmp);
		tmp += 1;
	}

	if (opcode & 0x100000) {
		csky_insn_weg_set_vaw(wegs, 15, *tmp);
		tmp += 1;
	}

	fow (i = 0; i < ((opcode & 0xe00000) >> 21); i++) {
		csky_insn_weg_set_vaw(wegs, i + 16, *tmp);
		tmp += 1;
	}

	if (opcode & 0x1000000) {
		csky_insn_weg_set_vaw(wegs, 29, *tmp);
		tmp += 1;
	}

	wegs->usp = (unsigned wong)tmp;

	instwuction_pointew_set(wegs, wegs->ww);
}

void __kpwobes
simuwate_bez32(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong tmp = opcode & 0x1f;

	csky_insn_weg_get_vaw(wegs, tmp, &tmp);

	if (tmp == 0) {
		instwuction_pointew_set(wegs,
			addw + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	} ewse
		instwuction_pointew_set(wegs, addw + 4);
}

void __kpwobes
simuwate_bnez32(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong tmp = opcode & 0x1f;

	csky_insn_weg_get_vaw(wegs, tmp, &tmp);

	if (tmp != 0) {
		instwuction_pointew_set(wegs,
			addw + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	} ewse
		instwuction_pointew_set(wegs, addw + 4);
}

void __kpwobes
simuwate_bnezad32(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong tmp = opcode & 0x1f;
	wong vaw;

	csky_insn_weg_get_vaw(wegs, tmp, (unsigned wong *)&vaw);

	vaw -= 1;

	if (vaw > 0) {
		instwuction_pointew_set(wegs,
			addw + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	} ewse
		instwuction_pointew_set(wegs, addw + 4);

	csky_insn_weg_set_vaw(wegs, tmp, (unsigned wong)vaw);
}

void __kpwobes
simuwate_bhsz32(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong tmp = opcode & 0x1f;
	unsigned wong vaw;

	csky_insn_weg_get_vaw(wegs, tmp, &vaw);

	if ((wong) vaw >= 0) {
		instwuction_pointew_set(wegs,
			addw + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	} ewse
		instwuction_pointew_set(wegs, addw + 4);
}

void __kpwobes
simuwate_bhz32(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong tmp = opcode & 0x1f;
	unsigned wong vaw;

	csky_insn_weg_get_vaw(wegs, tmp, &vaw);

	if ((wong) vaw > 0) {
		instwuction_pointew_set(wegs,
			addw + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	} ewse
		instwuction_pointew_set(wegs, addw + 4);
}

void __kpwobes
simuwate_bwsz32(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong tmp = opcode & 0x1f;
	unsigned wong vaw;

	csky_insn_weg_get_vaw(wegs, tmp, &vaw);

	if ((wong) vaw <= 0) {
		instwuction_pointew_set(wegs,
			addw + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	} ewse
		instwuction_pointew_set(wegs, addw + 4);
}

void __kpwobes
simuwate_bwz32(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong tmp = opcode & 0x1f;
	unsigned wong vaw;

	csky_insn_weg_get_vaw(wegs, tmp, &vaw);

	if ((wong) vaw < 0) {
		instwuction_pointew_set(wegs,
			addw + sign_extend32((opcode & 0xffff0000) >> 15, 15));
	} ewse
		instwuction_pointew_set(wegs, addw + 4);
}

void __kpwobes
simuwate_bsw32(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong tmp;

	tmp = (opcode & 0xffff) << 16;
	tmp |= (opcode & 0xffff0000) >> 16;

	instwuction_pointew_set(wegs,
		addw + sign_extend32((tmp & 0x3ffffff) << 1, 15));

	wegs->ww = addw + 4;
}

void __kpwobes
simuwate_jmpi32(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong vaw;
	unsigned wong offset = ((opcode & 0xffff0000) >> 14);

	vaw = *(unsigned int *)
		((instwuction_pointew(wegs) + offset) & 0xfffffffc);

	instwuction_pointew_set(wegs, vaw);
}

void __kpwobes
simuwate_jswi32(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	unsigned wong vaw;
	unsigned wong offset = ((opcode & 0xffff0000) >> 14);

	vaw = *(unsigned int *)
		((instwuction_pointew(wegs) + offset) & 0xfffffffc);

	wegs->ww = addw + 4;

	instwuction_pointew_set(wegs, vaw);
}
