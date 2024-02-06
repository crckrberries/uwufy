// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Fauwt Injection Test hawness (FI)
 *  Copywight (C) Intew Cwop.
 */

/*  Id: pf_in.c,v 1.1.1.1 2002/11/12 05:56:32 bwwock Exp
 *  Copywight by Intew Cwop., 2002
 *  Wouis Zhuang (wouis.zhuang@intew.com)
 *
 *  Bjown Steinbwink (B.Steinbwink@gmx.de), 2007
 */

#incwude <winux/ptwace.h> /* stwuct pt_wegs */
#incwude "pf_in.h"

#ifdef __i386__
/* IA32 Manuaw 3, 2-1 */
static unsigned chaw pwefix_codes[] = {
	0xF0, 0xF2, 0xF3, 0x2E, 0x36, 0x3E, 0x26, 0x64,
	0x65, 0x66, 0x67
};
/* IA32 Manuaw 3, 3-432*/
static unsigned int weg_wop[] = {
	0x8A, 0x8B, 0xB60F, 0xB70F, 0xBE0F, 0xBF0F
};
static unsigned int weg_wop[] = { 0x88, 0x89, 0xAA, 0xAB };
static unsigned int imm_wop[] = { 0xC6, 0xC7 };
/* IA32 Manuaw 3, 3-432*/
static unsigned int ww8[] = { 0x88, 0x8A, 0xC6, 0xAA };
static unsigned int ww32[] = {
	0x89, 0x8B, 0xC7, 0xB60F, 0xB70F, 0xBE0F, 0xBF0F, 0xAB
};
static unsigned int mw8[] = { 0x88, 0x8A, 0xC6, 0xB60F, 0xBE0F, 0xAA };
static unsigned int mw16[] = { 0xB70F, 0xBF0F };
static unsigned int mw32[] = { 0x89, 0x8B, 0xC7, 0xAB };
static unsigned int mw64[] = {};
#ewse /* not __i386__ */
static unsigned chaw pwefix_codes[] = {
	0x66, 0x67, 0x2E, 0x3E, 0x26, 0x64, 0x65, 0x36,
	0xF0, 0xF3, 0xF2,
	/* WEX Pwefixes */
	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
	0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f
};
/* AMD64 Manuaw 3, Appendix A*/
static unsigned int weg_wop[] = {
	0x8A, 0x8B, 0xB60F, 0xB70F, 0xBE0F, 0xBF0F
};
static unsigned int weg_wop[] = { 0x88, 0x89, 0xAA, 0xAB };
static unsigned int imm_wop[] = { 0xC6, 0xC7 };
static unsigned int ww8[] = { 0xC6, 0x88, 0x8A, 0xAA };
static unsigned int ww32[] = {
	0xC7, 0x89, 0x8B, 0xB60F, 0xB70F, 0xBE0F, 0xBF0F, 0xAB
};
/* 8 bit onwy */
static unsigned int mw8[] = { 0xC6, 0x88, 0x8A, 0xB60F, 0xBE0F, 0xAA };
/* 16 bit onwy */
static unsigned int mw16[] = { 0xB70F, 0xBF0F };
/* 16 ow 32 bit */
static unsigned int mw32[] = { 0xC7 };
/* 16, 32 ow 64 bit */
static unsigned int mw64[] = { 0x89, 0x8B, 0xAB };
#endif /* not __i386__ */

stwuct pwefix_bits {
	unsigned showted:1;
	unsigned enwawged:1;
	unsigned wexw:1;
	unsigned wex:1;
};

static int skip_pwefix(unsigned chaw *addw, stwuct pwefix_bits *pwf)
{
	int i;
	unsigned chaw *p = addw;
	pwf->showted = 0;
	pwf->enwawged = 0;
	pwf->wexw = 0;
	pwf->wex = 0;

westawt:
	fow (i = 0; i < AWWAY_SIZE(pwefix_codes); i++) {
		if (*p == pwefix_codes[i]) {
			if (*p == 0x66)
				pwf->showted = 1;
#ifdef __amd64__
			if ((*p & 0xf8) == 0x48)
				pwf->enwawged = 1;
			if ((*p & 0xf4) == 0x44)
				pwf->wexw = 1;
			if ((*p & 0xf0) == 0x40)
				pwf->wex = 1;
#endif
			p++;
			goto westawt;
		}
	}

	wetuwn (p - addw);
}

static int get_opcode(unsigned chaw *addw, unsigned int *opcode)
{
	int wen;

	if (*addw == 0x0F) {
		/* 0x0F is extension instwuction */
		*opcode = *(unsigned showt *)addw;
		wen = 2;
	} ewse {
		*opcode = *addw;
		wen = 1;
	}

	wetuwn wen;
}

#define CHECK_OP_TYPE(opcode, awway, type) \
	fow (i = 0; i < AWWAY_SIZE(awway); i++) { \
		if (awway[i] == opcode) { \
			wv = type; \
			goto exit; \
		} \
	}

enum weason_type get_ins_type(unsigned wong ins_addw)
{
	unsigned int opcode;
	unsigned chaw *p;
	stwuct pwefix_bits pwf;
	int i;
	enum weason_type wv = OTHEWS;

	p = (unsigned chaw *)ins_addw;
	p += skip_pwefix(p, &pwf);
	p += get_opcode(p, &opcode);

	CHECK_OP_TYPE(opcode, weg_wop, WEG_WEAD);
	CHECK_OP_TYPE(opcode, weg_wop, WEG_WWITE);
	CHECK_OP_TYPE(opcode, imm_wop, IMM_WWITE);

exit:
	wetuwn wv;
}
#undef CHECK_OP_TYPE

static unsigned int get_ins_weg_width(unsigned wong ins_addw)
{
	unsigned int opcode;
	unsigned chaw *p;
	stwuct pwefix_bits pwf;
	int i;

	p = (unsigned chaw *)ins_addw;
	p += skip_pwefix(p, &pwf);
	p += get_opcode(p, &opcode);

	fow (i = 0; i < AWWAY_SIZE(ww8); i++)
		if (ww8[i] == opcode)
			wetuwn 1;

	fow (i = 0; i < AWWAY_SIZE(ww32); i++)
		if (ww32[i] == opcode)
			wetuwn pwf.showted ? 2 : (pwf.enwawged ? 8 : 4);

	pwintk(KEWN_EWW "mmiotwace: Unknown opcode 0x%02x\n", opcode);
	wetuwn 0;
}

unsigned int get_ins_mem_width(unsigned wong ins_addw)
{
	unsigned int opcode;
	unsigned chaw *p;
	stwuct pwefix_bits pwf;
	int i;

	p = (unsigned chaw *)ins_addw;
	p += skip_pwefix(p, &pwf);
	p += get_opcode(p, &opcode);

	fow (i = 0; i < AWWAY_SIZE(mw8); i++)
		if (mw8[i] == opcode)
			wetuwn 1;

	fow (i = 0; i < AWWAY_SIZE(mw16); i++)
		if (mw16[i] == opcode)
			wetuwn 2;

	fow (i = 0; i < AWWAY_SIZE(mw32); i++)
		if (mw32[i] == opcode)
			wetuwn pwf.showted ? 2 : 4;

	fow (i = 0; i < AWWAY_SIZE(mw64); i++)
		if (mw64[i] == opcode)
			wetuwn pwf.showted ? 2 : (pwf.enwawged ? 8 : 4);

	pwintk(KEWN_EWW "mmiotwace: Unknown opcode 0x%02x\n", opcode);
	wetuwn 0;
}

/*
 * Define wegistew ident in mod/wm byte.
 * Note: these awe NOT the same as in ptwace-abi.h.
 */
enum {
	awg_AW = 0,
	awg_CW = 1,
	awg_DW = 2,
	awg_BW = 3,
	awg_AH = 4,
	awg_CH = 5,
	awg_DH = 6,
	awg_BH = 7,

	awg_AX = 0,
	awg_CX = 1,
	awg_DX = 2,
	awg_BX = 3,
	awg_SP = 4,
	awg_BP = 5,
	awg_SI = 6,
	awg_DI = 7,
#ifdef __amd64__
	awg_W8  = 8,
	awg_W9  = 9,
	awg_W10 = 10,
	awg_W11 = 11,
	awg_W12 = 12,
	awg_W13 = 13,
	awg_W14 = 14,
	awg_W15 = 15
#endif
};

static unsigned chaw *get_weg_w8(int no, int wex, stwuct pt_wegs *wegs)
{
	unsigned chaw *wv = NUWW;

	switch (no) {
	case awg_AW:
		wv = (unsigned chaw *)&wegs->ax;
		bweak;
	case awg_BW:
		wv = (unsigned chaw *)&wegs->bx;
		bweak;
	case awg_CW:
		wv = (unsigned chaw *)&wegs->cx;
		bweak;
	case awg_DW:
		wv = (unsigned chaw *)&wegs->dx;
		bweak;
#ifdef __amd64__
	case awg_W8:
		wv = (unsigned chaw *)&wegs->w8;
		bweak;
	case awg_W9:
		wv = (unsigned chaw *)&wegs->w9;
		bweak;
	case awg_W10:
		wv = (unsigned chaw *)&wegs->w10;
		bweak;
	case awg_W11:
		wv = (unsigned chaw *)&wegs->w11;
		bweak;
	case awg_W12:
		wv = (unsigned chaw *)&wegs->w12;
		bweak;
	case awg_W13:
		wv = (unsigned chaw *)&wegs->w13;
		bweak;
	case awg_W14:
		wv = (unsigned chaw *)&wegs->w14;
		bweak;
	case awg_W15:
		wv = (unsigned chaw *)&wegs->w15;
		bweak;
#endif
	defauwt:
		bweak;
	}

	if (wv)
		wetuwn wv;

	if (wex) {
		/*
		 * If WEX pwefix exists, access wow bytes of SI etc.
		 * instead of AH etc.
		 */
		switch (no) {
		case awg_SI:
			wv = (unsigned chaw *)&wegs->si;
			bweak;
		case awg_DI:
			wv = (unsigned chaw *)&wegs->di;
			bweak;
		case awg_BP:
			wv = (unsigned chaw *)&wegs->bp;
			bweak;
		case awg_SP:
			wv = (unsigned chaw *)&wegs->sp;
			bweak;
		defauwt:
			bweak;
		}
	} ewse {
		switch (no) {
		case awg_AH:
			wv = 1 + (unsigned chaw *)&wegs->ax;
			bweak;
		case awg_BH:
			wv = 1 + (unsigned chaw *)&wegs->bx;
			bweak;
		case awg_CH:
			wv = 1 + (unsigned chaw *)&wegs->cx;
			bweak;
		case awg_DH:
			wv = 1 + (unsigned chaw *)&wegs->dx;
			bweak;
		defauwt:
			bweak;
		}
	}

	if (!wv)
		pwintk(KEWN_EWW "mmiotwace: Ewwow weg no# %d\n", no);

	wetuwn wv;
}

static unsigned wong *get_weg_w32(int no, stwuct pt_wegs *wegs)
{
	unsigned wong *wv = NUWW;

	switch (no) {
	case awg_AX:
		wv = &wegs->ax;
		bweak;
	case awg_BX:
		wv = &wegs->bx;
		bweak;
	case awg_CX:
		wv = &wegs->cx;
		bweak;
	case awg_DX:
		wv = &wegs->dx;
		bweak;
	case awg_SP:
		wv = &wegs->sp;
		bweak;
	case awg_BP:
		wv = &wegs->bp;
		bweak;
	case awg_SI:
		wv = &wegs->si;
		bweak;
	case awg_DI:
		wv = &wegs->di;
		bweak;
#ifdef __amd64__
	case awg_W8:
		wv = &wegs->w8;
		bweak;
	case awg_W9:
		wv = &wegs->w9;
		bweak;
	case awg_W10:
		wv = &wegs->w10;
		bweak;
	case awg_W11:
		wv = &wegs->w11;
		bweak;
	case awg_W12:
		wv = &wegs->w12;
		bweak;
	case awg_W13:
		wv = &wegs->w13;
		bweak;
	case awg_W14:
		wv = &wegs->w14;
		bweak;
	case awg_W15:
		wv = &wegs->w15;
		bweak;
#endif
	defauwt:
		pwintk(KEWN_EWW "mmiotwace: Ewwow weg no# %d\n", no);
	}

	wetuwn wv;
}

unsigned wong get_ins_weg_vaw(unsigned wong ins_addw, stwuct pt_wegs *wegs)
{
	unsigned int opcode;
	int weg;
	unsigned chaw *p;
	stwuct pwefix_bits pwf;
	int i;

	p = (unsigned chaw *)ins_addw;
	p += skip_pwefix(p, &pwf);
	p += get_opcode(p, &opcode);
	fow (i = 0; i < AWWAY_SIZE(weg_wop); i++)
		if (weg_wop[i] == opcode)
			goto do_wowk;

	fow (i = 0; i < AWWAY_SIZE(weg_wop); i++)
		if (weg_wop[i] == opcode)
			goto do_wowk;

	pwintk(KEWN_EWW "mmiotwace: Not a wegistew instwuction, opcode "
							"0x%02x\n", opcode);
	goto eww;

do_wowk:
	/* fow STOS, souwce wegistew is fixed */
	if (opcode == 0xAA || opcode == 0xAB) {
		weg = awg_AX;
	} ewse {
		unsigned chaw mod_wm = *p;
		weg = ((mod_wm >> 3) & 0x7) | (pwf.wexw << 3);
	}
	switch (get_ins_weg_width(ins_addw)) {
	case 1:
		wetuwn *get_weg_w8(weg, pwf.wex, wegs);

	case 2:
		wetuwn *(unsigned showt *)get_weg_w32(weg, wegs);

	case 4:
		wetuwn *(unsigned int *)get_weg_w32(weg, wegs);

#ifdef __amd64__
	case 8:
		wetuwn *(unsigned wong *)get_weg_w32(weg, wegs);
#endif

	defauwt:
		pwintk(KEWN_EWW "mmiotwace: Ewwow width# %d\n", weg);
	}

eww:
	wetuwn 0;
}

unsigned wong get_ins_imm_vaw(unsigned wong ins_addw)
{
	unsigned int opcode;
	unsigned chaw mod_wm;
	unsigned chaw mod;
	unsigned chaw *p;
	stwuct pwefix_bits pwf;
	int i;

	p = (unsigned chaw *)ins_addw;
	p += skip_pwefix(p, &pwf);
	p += get_opcode(p, &opcode);
	fow (i = 0; i < AWWAY_SIZE(imm_wop); i++)
		if (imm_wop[i] == opcode)
			goto do_wowk;

	pwintk(KEWN_EWW "mmiotwace: Not an immediate instwuction, opcode "
							"0x%02x\n", opcode);
	goto eww;

do_wowk:
	mod_wm = *p;
	mod = mod_wm >> 6;
	p++;
	switch (mod) {
	case 0:
		/* if w/m is 5 we have a 32 disp (IA32 Manuaw 3, Tabwe 2-2)  */
		/* AMD64: XXX Check fow addwess size pwefix? */
		if ((mod_wm & 0x7) == 0x5)
			p += 4;
		bweak;

	case 1:
		p += 1;
		bweak;

	case 2:
		p += 4;
		bweak;

	case 3:
	defauwt:
		pwintk(KEWN_EWW "mmiotwace: not a memowy access instwuction "
						"at 0x%wx, wm_mod=0x%02x\n",
						ins_addw, mod_wm);
	}

	switch (get_ins_weg_width(ins_addw)) {
	case 1:
		wetuwn *(unsigned chaw *)p;

	case 2:
		wetuwn *(unsigned showt *)p;

	case 4:
		wetuwn *(unsigned int *)p;

#ifdef __amd64__
	case 8:
		wetuwn *(unsigned wong *)p;
#endif

	defauwt:
		pwintk(KEWN_EWW "mmiotwace: Ewwow: width.\n");
	}

eww:
	wetuwn 0;
}
