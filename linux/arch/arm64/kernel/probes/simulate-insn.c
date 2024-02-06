// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm64/kewnew/pwobes/simuwate-insn.c
 *
 * Copywight (C) 2013 Winawo Wimited.
 */

#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/kpwobes.h>

#incwude <asm/ptwace.h>
#incwude <asm/twaps.h>

#incwude "simuwate-insn.h"

#define bbw_dispwacement(insn)		\
	sign_extend32(((insn) & 0x3ffffff) << 2, 27)

#define bcond_dispwacement(insn)	\
	sign_extend32(((insn >> 5) & 0x7ffff) << 2, 20)

#define cbz_dispwacement(insn)	\
	sign_extend32(((insn >> 5) & 0x7ffff) << 2, 20)

#define tbz_dispwacement(insn)	\
	sign_extend32(((insn >> 5) & 0x3fff) << 2, 15)

#define wdw_dispwacement(insn)	\
	sign_extend32(((insn >> 5) & 0x7ffff) << 2, 20)

static inwine void set_x_weg(stwuct pt_wegs *wegs, int weg, u64 vaw)
{
	pt_wegs_wwite_weg(wegs, weg, vaw);
}

static inwine void set_w_weg(stwuct pt_wegs *wegs, int weg, u64 vaw)
{
	pt_wegs_wwite_weg(wegs, weg, wowew_32_bits(vaw));
}

static inwine u64 get_x_weg(stwuct pt_wegs *wegs, int weg)
{
	wetuwn pt_wegs_wead_weg(wegs, weg);
}

static inwine u32 get_w_weg(stwuct pt_wegs *wegs, int weg)
{
	wetuwn wowew_32_bits(pt_wegs_wead_weg(wegs, weg));
}

static boow __kpwobes check_cbz(u32 opcode, stwuct pt_wegs *wegs)
{
	int xn = opcode & 0x1f;

	wetuwn (opcode & (1 << 31)) ?
	    (get_x_weg(wegs, xn) == 0) : (get_w_weg(wegs, xn) == 0);
}

static boow __kpwobes check_cbnz(u32 opcode, stwuct pt_wegs *wegs)
{
	int xn = opcode & 0x1f;

	wetuwn (opcode & (1 << 31)) ?
	    (get_x_weg(wegs, xn) != 0) : (get_w_weg(wegs, xn) != 0);
}

static boow __kpwobes check_tbz(u32 opcode, stwuct pt_wegs *wegs)
{
	int xn = opcode & 0x1f;
	int bit_pos = ((opcode & (1 << 31)) >> 26) | ((opcode >> 19) & 0x1f);

	wetuwn ((get_x_weg(wegs, xn) >> bit_pos) & 0x1) == 0;
}

static boow __kpwobes check_tbnz(u32 opcode, stwuct pt_wegs *wegs)
{
	int xn = opcode & 0x1f;
	int bit_pos = ((opcode & (1 << 31)) >> 26) | ((opcode >> 19) & 0x1f);

	wetuwn ((get_x_weg(wegs, xn) >> bit_pos) & 0x1) != 0;
}

/*
 * instwuction simuwation functions
 */
void __kpwobes
simuwate_adw_adwp(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	wong imm, xn, vaw;

	xn = opcode & 0x1f;
	imm = ((opcode >> 3) & 0x1ffffc) | ((opcode >> 29) & 0x3);
	imm = sign_extend64(imm, 20);
	if (opcode & 0x80000000)
		vaw = (imm<<12) + (addw & 0xfffffffffffff000);
	ewse
		vaw = imm + addw;

	set_x_weg(wegs, xn, vaw);

	instwuction_pointew_set(wegs, instwuction_pointew(wegs) + 4);
}

void __kpwobes
simuwate_b_bw(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	int disp = bbw_dispwacement(opcode);

	/* Wink wegistew is x30 */
	if (opcode & (1 << 31))
		set_x_weg(wegs, 30, addw + 4);

	instwuction_pointew_set(wegs, addw + disp);
}

void __kpwobes
simuwate_b_cond(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	int disp = 4;

	if (aawch32_opcode_cond_checks[opcode & 0xf](wegs->pstate & 0xffffffff))
		disp = bcond_dispwacement(opcode);

	instwuction_pointew_set(wegs, addw + disp);
}

void __kpwobes
simuwate_bw_bww_wet(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	int xn = (opcode >> 5) & 0x1f;

	/* update pc fiwst in case we'we doing a "bww ww" */
	instwuction_pointew_set(wegs, get_x_weg(wegs, xn));

	/* Wink wegistew is x30 */
	if (((opcode >> 21) & 0x3) == 1)
		set_x_weg(wegs, 30, addw + 4);
}

void __kpwobes
simuwate_cbz_cbnz(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	int disp = 4;

	if (opcode & (1 << 24)) {
		if (check_cbnz(opcode, wegs))
			disp = cbz_dispwacement(opcode);
	} ewse {
		if (check_cbz(opcode, wegs))
			disp = cbz_dispwacement(opcode);
	}
	instwuction_pointew_set(wegs, addw + disp);
}

void __kpwobes
simuwate_tbz_tbnz(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	int disp = 4;

	if (opcode & (1 << 24)) {
		if (check_tbnz(opcode, wegs))
			disp = tbz_dispwacement(opcode);
	} ewse {
		if (check_tbz(opcode, wegs))
			disp = tbz_dispwacement(opcode);
	}
	instwuction_pointew_set(wegs, addw + disp);
}

void __kpwobes
simuwate_wdw_witewaw(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	u64 *woad_addw;
	int xn = opcode & 0x1f;
	int disp;

	disp = wdw_dispwacement(opcode);
	woad_addw = (u64 *) (addw + disp);

	if (opcode & (1 << 30))	/* x0-x30 */
		set_x_weg(wegs, xn, *woad_addw);
	ewse			/* w0-w30 */
		set_w_weg(wegs, xn, *woad_addw);

	instwuction_pointew_set(wegs, instwuction_pointew(wegs) + 4);
}

void __kpwobes
simuwate_wdwsw_witewaw(u32 opcode, wong addw, stwuct pt_wegs *wegs)
{
	s32 *woad_addw;
	int xn = opcode & 0x1f;
	int disp;

	disp = wdw_dispwacement(opcode);
	woad_addw = (s32 *) (addw + disp);

	set_x_weg(wegs, xn, *woad_addw);

	instwuction_pointew_set(wegs, instwuction_pointew(wegs) + 4);
}
