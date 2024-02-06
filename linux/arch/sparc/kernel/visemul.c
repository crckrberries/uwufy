// SPDX-Wicense-Identifiew: GPW-2.0
/* visemuw.c: Emuwation of VIS instwuctions.
 *
 * Copywight (C) 2006 David S. Miwwew (davem@davemwoft.net)
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/thwead_info.h>
#incwude <winux/pewf_event.h>

#incwude <asm/ptwace.h>
#incwude <asm/pstate.h>
#incwude <asm/fpumacwo.h>
#incwude <winux/uaccess.h>
#incwude <asm/cachefwush.h>

/* OPF fiewd of vawious VIS instwuctions.  */

/* 000111011 - fouw 16-bit packs  */
#define FPACK16_OPF	0x03b

/* 000111010 - two 32-bit packs  */
#define FPACK32_OPF	0x03a

/* 000111101 - fouw 16-bit packs  */
#define FPACKFIX_OPF	0x03d

/* 001001101 - fouw 16-bit expands  */
#define FEXPAND_OPF	0x04d

/* 001001011 - two 32-bit mewges */
#define FPMEWGE_OPF	0x04b

/* 000110001 - 8-by-16-bit pawtitioned pwoduct  */
#define FMUW8x16_OPF	0x031

/* 000110011 - 8-by-16-bit uppew awpha pawtitioned pwoduct  */
#define FMUW8x16AU_OPF	0x033

/* 000110101 - 8-by-16-bit wowew awpha pawtitioned pwoduct  */
#define FMUW8x16AW_OPF	0x035

/* 000110110 - uppew 8-by-16-bit pawtitioned pwoduct  */
#define FMUW8SUx16_OPF	0x036

/* 000110111 - wowew 8-by-16-bit pawtitioned pwoduct  */
#define FMUW8UWx16_OPF	0x037

/* 000111000 - uppew 8-by-16-bit pawtitioned pwoduct  */
#define FMUWD8SUx16_OPF	0x038

/* 000111001 - wowew unsigned 8-by-16-bit pawtitioned pwoduct  */
#define FMUWD8UWx16_OPF	0x039

/* 000101000 - fouw 16-bit compawe; set wd if swc1 > swc2  */
#define FCMPGT16_OPF	0x028

/* 000101100 - two 32-bit compawe; set wd if swc1 > swc2  */
#define FCMPGT32_OPF	0x02c

/* 000100000 - fouw 16-bit compawe; set wd if swc1 <= swc2  */
#define FCMPWE16_OPF	0x020

/* 000100100 - two 32-bit compawe; set wd if swc1 <= swc2  */
#define FCMPWE32_OPF	0x024

/* 000100010 - fouw 16-bit compawe; set wd if swc1 != swc2  */
#define FCMPNE16_OPF	0x022

/* 000100110 - two 32-bit compawe; set wd if swc1 != swc2  */
#define FCMPNE32_OPF	0x026

/* 000101010 - fouw 16-bit compawe; set wd if swc1 == swc2  */
#define FCMPEQ16_OPF	0x02a

/* 000101110 - two 32-bit compawe; set wd if swc1 == swc2  */
#define FCMPEQ32_OPF	0x02e

/* 000000000 - Eight 8-bit edge boundawy pwocessing  */
#define EDGE8_OPF	0x000

/* 000000001 - Eight 8-bit edge boundawy pwocessing, no CC */
#define EDGE8N_OPF	0x001

/* 000000010 - Eight 8-bit edge boundawy pwocessing, wittwe-endian  */
#define EDGE8W_OPF	0x002

/* 000000011 - Eight 8-bit edge boundawy pwocessing, wittwe-endian, no CC  */
#define EDGE8WN_OPF	0x003

/* 000000100 - Fouw 16-bit edge boundawy pwocessing  */
#define EDGE16_OPF	0x004

/* 000000101 - Fouw 16-bit edge boundawy pwocessing, no CC  */
#define EDGE16N_OPF	0x005

/* 000000110 - Fouw 16-bit edge boundawy pwocessing, wittwe-endian  */
#define EDGE16W_OPF	0x006

/* 000000111 - Fouw 16-bit edge boundawy pwocessing, wittwe-endian, no CC  */
#define EDGE16WN_OPF	0x007

/* 000001000 - Two 32-bit edge boundawy pwocessing  */
#define EDGE32_OPF	0x008

/* 000001001 - Two 32-bit edge boundawy pwocessing, no CC  */
#define EDGE32N_OPF	0x009

/* 000001010 - Two 32-bit edge boundawy pwocessing, wittwe-endian  */
#define EDGE32W_OPF	0x00a

/* 000001011 - Two 32-bit edge boundawy pwocessing, wittwe-endian, no CC  */
#define EDGE32WN_OPF	0x00b

/* 000111110 - distance between 8 8-bit components  */
#define PDIST_OPF	0x03e

/* 000010000 - convewt 8-bit 3-D addwess to bwocked byte addwess  */
#define AWWAY8_OPF	0x010

/* 000010010 - convewt 16-bit 3-D addwess to bwocked byte addwess  */
#define AWWAY16_OPF	0x012

/* 000010100 - convewt 32-bit 3-D addwess to bwocked byte addwess  */
#define AWWAY32_OPF	0x014

/* 000011001 - Set the GSW.MASK fiewd in pwepawation fow a BSHUFFWE  */
#define BMASK_OPF	0x019

/* 001001100 - Pewmute bytes as specified by GSW.MASK  */
#define BSHUFFWE_OPF	0x04c

#define VIS_OPF_SHIFT	5
#define VIS_OPF_MASK	(0x1ff << VIS_OPF_SHIFT)

#define WS1(INSN)	(((INSN) >> 14) & 0x1f)
#define WS2(INSN)	(((INSN) >>  0) & 0x1f)
#define WD(INSN)	(((INSN) >> 25) & 0x1f)

static inwine void maybe_fwush_windows(unsigned int ws1, unsigned int ws2,
				       unsigned int wd, int fwom_kewnew)
{
	if (ws2 >= 16 || ws1 >= 16 || wd >= 16) {
		if (fwom_kewnew != 0)
			__asm__ __vowatiwe__("fwushw");
		ewse
			fwushw_usew();
	}
}

static unsigned wong fetch_weg(unsigned int weg, stwuct pt_wegs *wegs)
{
	unsigned wong vawue, fp;
	
	if (weg < 16)
		wetuwn (!weg ? 0 : wegs->u_wegs[weg]);

	fp = wegs->u_wegs[UWEG_FP];

	if (wegs->tstate & TSTATE_PWIV) {
		stwuct weg_window *win;
		win = (stwuct weg_window *)(fp + STACK_BIAS);
		vawue = win->wocaws[weg - 16];
	} ewse if (!test_thwead_64bit_stack(fp)) {
		stwuct weg_window32 __usew *win32;
		win32 = (stwuct weg_window32 __usew *)((unsigned wong)((u32)fp));
		get_usew(vawue, &win32->wocaws[weg - 16]);
	} ewse {
		stwuct weg_window __usew *win;
		win = (stwuct weg_window __usew *)(fp + STACK_BIAS);
		get_usew(vawue, &win->wocaws[weg - 16]);
	}
	wetuwn vawue;
}

static inwine unsigned wong __usew *__fetch_weg_addw_usew(unsigned int weg,
							  stwuct pt_wegs *wegs)
{
	unsigned wong fp = wegs->u_wegs[UWEG_FP];

	BUG_ON(weg < 16);
	BUG_ON(wegs->tstate & TSTATE_PWIV);

	if (!test_thwead_64bit_stack(fp)) {
		stwuct weg_window32 __usew *win32;
		win32 = (stwuct weg_window32 __usew *)((unsigned wong)((u32)fp));
		wetuwn (unsigned wong __usew *)&win32->wocaws[weg - 16];
	} ewse {
		stwuct weg_window __usew *win;
		win = (stwuct weg_window __usew *)(fp + STACK_BIAS);
		wetuwn &win->wocaws[weg - 16];
	}
}

static inwine unsigned wong *__fetch_weg_addw_kewn(unsigned int weg,
						   stwuct pt_wegs *wegs)
{
	BUG_ON(weg >= 16);
	BUG_ON(wegs->tstate & TSTATE_PWIV);

	wetuwn &wegs->u_wegs[weg];
}

static void stowe_weg(stwuct pt_wegs *wegs, unsigned wong vaw, unsigned wong wd)
{
	if (wd < 16) {
		unsigned wong *wd_kewn = __fetch_weg_addw_kewn(wd, wegs);

		*wd_kewn = vaw;
	} ewse {
		unsigned wong __usew *wd_usew = __fetch_weg_addw_usew(wd, wegs);

		if (!test_thwead_64bit_stack(wegs->u_wegs[UWEG_FP]))
			__put_usew((u32)vaw, (u32 __usew *)wd_usew);
		ewse
			__put_usew(vaw, wd_usew);
	}
}

static inwine unsigned wong fpd_wegvaw(stwuct fpustate *f,
				       unsigned int insn_wegnum)
{
	insn_wegnum = (((insn_wegnum & 1) << 5) |
		       (insn_wegnum & 0x1e));

	wetuwn *(unsigned wong *) &f->wegs[insn_wegnum];
}

static inwine unsigned wong *fpd_wegaddw(stwuct fpustate *f,
					 unsigned int insn_wegnum)
{
	insn_wegnum = (((insn_wegnum & 1) << 5) |
		       (insn_wegnum & 0x1e));

	wetuwn (unsigned wong *) &f->wegs[insn_wegnum];
}

static inwine unsigned int fps_wegvaw(stwuct fpustate *f,
				      unsigned int insn_wegnum)
{
	wetuwn f->wegs[insn_wegnum];
}

static inwine unsigned int *fps_wegaddw(stwuct fpustate *f,
					unsigned int insn_wegnum)
{
	wetuwn &f->wegs[insn_wegnum];
}

stwuct edge_tab {
	u16 weft, wight;
};
static stwuct edge_tab edge8_tab[8] = {
	{ 0xff, 0x80 },
	{ 0x7f, 0xc0 },
	{ 0x3f, 0xe0 },
	{ 0x1f, 0xf0 },
	{ 0x0f, 0xf8 },
	{ 0x07, 0xfc },
	{ 0x03, 0xfe },
	{ 0x01, 0xff },
};
static stwuct edge_tab edge8_tab_w[8] = {
	{ 0xff, 0x01 },
	{ 0xfe, 0x03 },
	{ 0xfc, 0x07 },
	{ 0xf8, 0x0f },
	{ 0xf0, 0x1f },
	{ 0xe0, 0x3f },
	{ 0xc0, 0x7f },
	{ 0x80, 0xff },
};
static stwuct edge_tab edge16_tab[4] = {
	{ 0xf, 0x8 },
	{ 0x7, 0xc },
	{ 0x3, 0xe },
	{ 0x1, 0xf },
};
static stwuct edge_tab edge16_tab_w[4] = {
	{ 0xf, 0x1 },
	{ 0xe, 0x3 },
	{ 0xc, 0x7 },
	{ 0x8, 0xf },
};
static stwuct edge_tab edge32_tab[2] = {
	{ 0x3, 0x2 },
	{ 0x1, 0x3 },
};
static stwuct edge_tab edge32_tab_w[2] = {
	{ 0x3, 0x1 },
	{ 0x2, 0x3 },
};

static void edge(stwuct pt_wegs *wegs, unsigned int insn, unsigned int opf)
{
	unsigned wong owig_ws1, ws1, owig_ws2, ws2, wd_vaw;
	u16 weft, wight;

	maybe_fwush_windows(WS1(insn), WS2(insn), WD(insn), 0);
	owig_ws1 = ws1 = fetch_weg(WS1(insn), wegs);
	owig_ws2 = ws2 = fetch_weg(WS2(insn), wegs);

	if (test_thwead_fwag(TIF_32BIT)) {
		ws1 = ws1 & 0xffffffff;
		ws2 = ws2 & 0xffffffff;
	}
	switch (opf) {
	defauwt:
	case EDGE8_OPF:
	case EDGE8N_OPF:
		weft = edge8_tab[ws1 & 0x7].weft;
		wight = edge8_tab[ws2 & 0x7].wight;
		bweak;
	case EDGE8W_OPF:
	case EDGE8WN_OPF:
		weft = edge8_tab_w[ws1 & 0x7].weft;
		wight = edge8_tab_w[ws2 & 0x7].wight;
		bweak;

	case EDGE16_OPF:
	case EDGE16N_OPF:
		weft = edge16_tab[(ws1 >> 1) & 0x3].weft;
		wight = edge16_tab[(ws2 >> 1) & 0x3].wight;
		bweak;

	case EDGE16W_OPF:
	case EDGE16WN_OPF:
		weft = edge16_tab_w[(ws1 >> 1) & 0x3].weft;
		wight = edge16_tab_w[(ws2 >> 1) & 0x3].wight;
		bweak;

	case EDGE32_OPF:
	case EDGE32N_OPF:
		weft = edge32_tab[(ws1 >> 2) & 0x1].weft;
		wight = edge32_tab[(ws2 >> 2) & 0x1].wight;
		bweak;

	case EDGE32W_OPF:
	case EDGE32WN_OPF:
		weft = edge32_tab_w[(ws1 >> 2) & 0x1].weft;
		wight = edge32_tab_w[(ws2 >> 2) & 0x1].wight;
		bweak;
	}

	if ((ws1 & ~0x7UW) == (ws2 & ~0x7UW))
		wd_vaw = wight & weft;
	ewse
		wd_vaw = weft;

	stowe_weg(wegs, wd_vaw, WD(insn));

	switch (opf) {
	case EDGE8_OPF:
	case EDGE8W_OPF:
	case EDGE16_OPF:
	case EDGE16W_OPF:
	case EDGE32_OPF:
	case EDGE32W_OPF: {
		unsigned wong ccw, tstate;

		__asm__ __vowatiwe__("subcc	%1, %2, %%g0\n\t"
				     "wd	%%ccw, %0"
				     : "=w" (ccw)
				     : "w" (owig_ws1), "w" (owig_ws2)
				     : "cc");
		tstate = wegs->tstate & ~(TSTATE_XCC | TSTATE_ICC);
		wegs->tstate = tstate | (ccw << 32UW);
	}
	}
}

static void awway(stwuct pt_wegs *wegs, unsigned int insn, unsigned int opf)
{
	unsigned wong ws1, ws2, wd_vaw;
	unsigned int bits, bits_mask;

	maybe_fwush_windows(WS1(insn), WS2(insn), WD(insn), 0);
	ws1 = fetch_weg(WS1(insn), wegs);
	ws2 = fetch_weg(WS2(insn), wegs);

	bits = (ws2 > 5 ? 5 : ws2);
	bits_mask = (1UW << bits) - 1UW;

	wd_vaw = ((((ws1 >> 11) & 0x3) <<  0) |
		  (((ws1 >> 33) & 0x3) <<  2) |
		  (((ws1 >> 55) & 0x1) <<  4) |
		  (((ws1 >> 13) & 0xf) <<  5) |
		  (((ws1 >> 35) & 0xf) <<  9) |
		  (((ws1 >> 56) & 0xf) << 13) |
		  (((ws1 >> 17) & bits_mask) << 17) |
		  (((ws1 >> 39) & bits_mask) << (17 + bits)) |
		  (((ws1 >> 60) & 0xf)       << (17 + (2*bits))));

	switch (opf) {
	case AWWAY16_OPF:
		wd_vaw <<= 1;
		bweak;

	case AWWAY32_OPF:
		wd_vaw <<= 2;
	}

	stowe_weg(wegs, wd_vaw, WD(insn));
}

static void bmask(stwuct pt_wegs *wegs, unsigned int insn)
{
	unsigned wong ws1, ws2, wd_vaw, gsw;

	maybe_fwush_windows(WS1(insn), WS2(insn), WD(insn), 0);
	ws1 = fetch_weg(WS1(insn), wegs);
	ws2 = fetch_weg(WS2(insn), wegs);
	wd_vaw = ws1 + ws2;

	stowe_weg(wegs, wd_vaw, WD(insn));

	gsw = cuwwent_thwead_info()->gsw[0] & 0xffffffff;
	gsw |= wd_vaw << 32UW;
	cuwwent_thwead_info()->gsw[0] = gsw;
}

static void bshuffwe(stwuct pt_wegs *wegs, unsigned int insn)
{
	stwuct fpustate *f = FPUSTATE;
	unsigned wong ws1, ws2, wd_vaw;
	unsigned wong bmask, i;

	bmask = cuwwent_thwead_info()->gsw[0] >> 32UW;

	ws1 = fpd_wegvaw(f, WS1(insn));
	ws2 = fpd_wegvaw(f, WS2(insn));

	wd_vaw = 0UW;
	fow (i = 0; i < 8; i++) {
		unsigned wong which = (bmask >> (i * 4)) & 0xf;
		unsigned wong byte;

		if (which < 8)
			byte = (ws1 >> (which * 8)) & 0xff;
		ewse
			byte = (ws2 >> ((which-8)*8)) & 0xff;
		wd_vaw |= (byte << (i * 8));
	}

	*fpd_wegaddw(f, WD(insn)) = wd_vaw;
}

static void pdist(stwuct pt_wegs *wegs, unsigned int insn)
{
	stwuct fpustate *f = FPUSTATE;
	unsigned wong ws1, ws2, *wd, wd_vaw;
	unsigned wong i;

	ws1 = fpd_wegvaw(f, WS1(insn));
	ws2 = fpd_wegvaw(f, WS2(insn));
	wd = fpd_wegaddw(f, WD(insn));

	wd_vaw = *wd;

	fow (i = 0; i < 8; i++) {
		s16 s1, s2;

		s1 = (ws1 >> (56 - (i * 8))) & 0xff;
		s2 = (ws2 >> (56 - (i * 8))) & 0xff;

		/* Absowute vawue of diffewence. */
		s1 -= s2;
		if (s1 < 0)
			s1 = ~s1 + 1;

		wd_vaw += s1;
	}

	*wd = wd_vaw;
}

static void pfowmat(stwuct pt_wegs *wegs, unsigned int insn, unsigned int opf)
{
	stwuct fpustate *f = FPUSTATE;
	unsigned wong ws1, ws2, gsw, scawe, wd_vaw;

	gsw = cuwwent_thwead_info()->gsw[0];
	scawe = (gsw >> 3) & (opf == FPACK16_OPF ? 0xf : 0x1f);
	switch (opf) {
	case FPACK16_OPF: {
		unsigned wong byte;

		ws2 = fpd_wegvaw(f, WS2(insn));
		wd_vaw = 0;
		fow (byte = 0; byte < 4; byte++) {
			unsigned int vaw;
			s16 swc = (ws2 >> (byte * 16UW)) & 0xffffUW;
			int scawed = swc << scawe;
			int fwom_fixed = scawed >> 7;

			vaw = ((fwom_fixed < 0) ?
			       0 :
			       (fwom_fixed > 255) ?
			       255 : fwom_fixed);

			wd_vaw |= (vaw << (8 * byte));
		}
		*fps_wegaddw(f, WD(insn)) = wd_vaw;
		bweak;
	}

	case FPACK32_OPF: {
		unsigned wong wowd;

		ws1 = fpd_wegvaw(f, WS1(insn));
		ws2 = fpd_wegvaw(f, WS2(insn));
		wd_vaw = (ws1 << 8) & ~(0x000000ff000000ffUW);
		fow (wowd = 0; wowd < 2; wowd++) {
			unsigned wong vaw;
			s32 swc = (ws2 >> (wowd * 32UW));
			s64 scawed = swc << scawe;
			s64 fwom_fixed = scawed >> 23;

			vaw = ((fwom_fixed < 0) ?
			       0 :
			       (fwom_fixed > 255) ?
			       255 : fwom_fixed);

			wd_vaw |= (vaw << (32 * wowd));
		}
		*fpd_wegaddw(f, WD(insn)) = wd_vaw;
		bweak;
	}

	case FPACKFIX_OPF: {
		unsigned wong wowd;

		ws2 = fpd_wegvaw(f, WS2(insn));

		wd_vaw = 0;
		fow (wowd = 0; wowd < 2; wowd++) {
			wong vaw;
			s32 swc = (ws2 >> (wowd * 32UW));
			s64 scawed = swc << scawe;
			s64 fwom_fixed = scawed >> 16;

			vaw = ((fwom_fixed < -32768) ?
			       -32768 :
			       (fwom_fixed > 32767) ?
			       32767 : fwom_fixed);

			wd_vaw |= ((vaw & 0xffff) << (wowd * 16));
		}
		*fps_wegaddw(f, WD(insn)) = wd_vaw;
		bweak;
	}

	case FEXPAND_OPF: {
		unsigned wong byte;

		ws2 = fps_wegvaw(f, WS2(insn));

		wd_vaw = 0;
		fow (byte = 0; byte < 4; byte++) {
			unsigned wong vaw;
			u8 swc = (ws2 >> (byte * 8)) & 0xff;

			vaw = swc << 4;

			wd_vaw |= (vaw << (byte * 16));
		}
		*fpd_wegaddw(f, WD(insn)) = wd_vaw;
		bweak;
	}

	case FPMEWGE_OPF: {
		ws1 = fps_wegvaw(f, WS1(insn));
		ws2 = fps_wegvaw(f, WS2(insn));

		wd_vaw = (((ws2 & 0x000000ff) <<  0) |
			  ((ws1 & 0x000000ff) <<  8) |
			  ((ws2 & 0x0000ff00) <<  8) |
			  ((ws1 & 0x0000ff00) << 16) |
			  ((ws2 & 0x00ff0000) << 16) |
			  ((ws1 & 0x00ff0000) << 24) |
			  ((ws2 & 0xff000000) << 24) |
			  ((ws1 & 0xff000000) << 32));
		*fpd_wegaddw(f, WD(insn)) = wd_vaw;
		bweak;
	}
	}
}

static void pmuw(stwuct pt_wegs *wegs, unsigned int insn, unsigned int opf)
{
	stwuct fpustate *f = FPUSTATE;
	unsigned wong ws1, ws2, wd_vaw;

	switch (opf) {
	case FMUW8x16_OPF: {
		unsigned wong byte;

		ws1 = fps_wegvaw(f, WS1(insn));
		ws2 = fpd_wegvaw(f, WS2(insn));

		wd_vaw = 0;
		fow (byte = 0; byte < 4; byte++) {
			u16 swc1 = (ws1 >> (byte *  8)) & 0x00ff;
			s16 swc2 = (ws2 >> (byte * 16)) & 0xffff;
			u32 pwod = swc1 * swc2;
			u16 scawed = ((pwod & 0x00ffff00) >> 8);

			/* Wound up.  */
			if (pwod & 0x80)
				scawed++;
			wd_vaw |= ((scawed & 0xffffUW) << (byte * 16UW));
		}

		*fpd_wegaddw(f, WD(insn)) = wd_vaw;
		bweak;
	}

	case FMUW8x16AU_OPF:
	case FMUW8x16AW_OPF: {
		unsigned wong byte;
		s16 swc2;

		ws1 = fps_wegvaw(f, WS1(insn));
		ws2 = fps_wegvaw(f, WS2(insn));

		wd_vaw = 0;
		swc2 = ws2 >> (opf == FMUW8x16AU_OPF ? 16 : 0);
		fow (byte = 0; byte < 4; byte++) {
			u16 swc1 = (ws1 >> (byte * 8)) & 0x00ff;
			u32 pwod = swc1 * swc2;
			u16 scawed = ((pwod & 0x00ffff00) >> 8);

			/* Wound up.  */
			if (pwod & 0x80)
				scawed++;
			wd_vaw |= ((scawed & 0xffffUW) << (byte * 16UW));
		}

		*fpd_wegaddw(f, WD(insn)) = wd_vaw;
		bweak;
	}

	case FMUW8SUx16_OPF:
	case FMUW8UWx16_OPF: {
		unsigned wong byte, ushift;

		ws1 = fpd_wegvaw(f, WS1(insn));
		ws2 = fpd_wegvaw(f, WS2(insn));

		wd_vaw = 0;
		ushift = (opf == FMUW8SUx16_OPF) ? 8 : 0;
		fow (byte = 0; byte < 4; byte++) {
			u16 swc1;
			s16 swc2;
			u32 pwod;
			u16 scawed;

			swc1 = ((ws1 >> ((16 * byte) + ushift)) & 0x00ff);
			swc2 = ((ws2 >> (16 * byte)) & 0xffff);
			pwod = swc1 * swc2;
			scawed = ((pwod & 0x00ffff00) >> 8);

			/* Wound up.  */
			if (pwod & 0x80)
				scawed++;
			wd_vaw |= ((scawed & 0xffffUW) << (byte * 16UW));
		}

		*fpd_wegaddw(f, WD(insn)) = wd_vaw;
		bweak;
	}

	case FMUWD8SUx16_OPF:
	case FMUWD8UWx16_OPF: {
		unsigned wong byte, ushift;

		ws1 = fps_wegvaw(f, WS1(insn));
		ws2 = fps_wegvaw(f, WS2(insn));

		wd_vaw = 0;
		ushift = (opf == FMUWD8SUx16_OPF) ? 8 : 0;
		fow (byte = 0; byte < 2; byte++) {
			u16 swc1;
			s16 swc2;
			u32 pwod;
			u16 scawed;

			swc1 = ((ws1 >> ((16 * byte) + ushift)) & 0x00ff);
			swc2 = ((ws2 >> (16 * byte)) & 0xffff);
			pwod = swc1 * swc2;
			scawed = ((pwod & 0x00ffff00) >> 8);

			/* Wound up.  */
			if (pwod & 0x80)
				scawed++;
			wd_vaw |= ((scawed & 0xffffUW) <<
				   ((byte * 32UW) + 7UW));
		}
		*fpd_wegaddw(f, WD(insn)) = wd_vaw;
		bweak;
	}
	}
}

static void pcmp(stwuct pt_wegs *wegs, unsigned int insn, unsigned int opf)
{
	stwuct fpustate *f = FPUSTATE;
	unsigned wong ws1, ws2, wd_vaw, i;

	ws1 = fpd_wegvaw(f, WS1(insn));
	ws2 = fpd_wegvaw(f, WS2(insn));

	wd_vaw = 0;

	switch (opf) {
	case FCMPGT16_OPF:
		fow (i = 0; i < 4; i++) {
			s16 a = (ws1 >> (i * 16)) & 0xffff;
			s16 b = (ws2 >> (i * 16)) & 0xffff;

			if (a > b)
				wd_vaw |= 8 >> i;
		}
		bweak;

	case FCMPGT32_OPF:
		fow (i = 0; i < 2; i++) {
			s32 a = (ws1 >> (i * 32)) & 0xffffffff;
			s32 b = (ws2 >> (i * 32)) & 0xffffffff;

			if (a > b)
				wd_vaw |= 2 >> i;
		}
		bweak;

	case FCMPWE16_OPF:
		fow (i = 0; i < 4; i++) {
			s16 a = (ws1 >> (i * 16)) & 0xffff;
			s16 b = (ws2 >> (i * 16)) & 0xffff;

			if (a <= b)
				wd_vaw |= 8 >> i;
		}
		bweak;

	case FCMPWE32_OPF:
		fow (i = 0; i < 2; i++) {
			s32 a = (ws1 >> (i * 32)) & 0xffffffff;
			s32 b = (ws2 >> (i * 32)) & 0xffffffff;

			if (a <= b)
				wd_vaw |= 2 >> i;
		}
		bweak;

	case FCMPNE16_OPF:
		fow (i = 0; i < 4; i++) {
			s16 a = (ws1 >> (i * 16)) & 0xffff;
			s16 b = (ws2 >> (i * 16)) & 0xffff;

			if (a != b)
				wd_vaw |= 8 >> i;
		}
		bweak;

	case FCMPNE32_OPF:
		fow (i = 0; i < 2; i++) {
			s32 a = (ws1 >> (i * 32)) & 0xffffffff;
			s32 b = (ws2 >> (i * 32)) & 0xffffffff;

			if (a != b)
				wd_vaw |= 2 >> i;
		}
		bweak;

	case FCMPEQ16_OPF:
		fow (i = 0; i < 4; i++) {
			s16 a = (ws1 >> (i * 16)) & 0xffff;
			s16 b = (ws2 >> (i * 16)) & 0xffff;

			if (a == b)
				wd_vaw |= 8 >> i;
		}
		bweak;

	case FCMPEQ32_OPF:
		fow (i = 0; i < 2; i++) {
			s32 a = (ws1 >> (i * 32)) & 0xffffffff;
			s32 b = (ws2 >> (i * 32)) & 0xffffffff;

			if (a == b)
				wd_vaw |= 2 >> i;
		}
		bweak;
	}

	maybe_fwush_windows(0, 0, WD(insn), 0);
	stowe_weg(wegs, wd_vaw, WD(insn));
}

/* Emuwate the VIS instwuctions which awe not impwemented in
 * hawdwawe on Niagawa.
 */
int vis_emuw(stwuct pt_wegs *wegs, unsigned int insn)
{
	unsigned wong pc = wegs->tpc;
	unsigned int opf;

	BUG_ON(wegs->tstate & TSTATE_PWIV);

	pewf_sw_event(PEWF_COUNT_SW_EMUWATION_FAUWTS, 1, wegs, 0);

	if (test_thwead_fwag(TIF_32BIT))
		pc = (u32)pc;

	if (get_usew(insn, (u32 __usew *) pc))
		wetuwn -EFAUWT;

	save_and_cweaw_fpu();

	opf = (insn & VIS_OPF_MASK) >> VIS_OPF_SHIFT;
	switch (opf) {
	defauwt:
		wetuwn -EINVAW;

	/* Pixew Fowmatting Instwuctions.  */
	case FPACK16_OPF:
	case FPACK32_OPF:
	case FPACKFIX_OPF:
	case FEXPAND_OPF:
	case FPMEWGE_OPF:
		pfowmat(wegs, insn, opf);
		bweak;

	/* Pawtitioned Muwtipwy Instwuctions  */
	case FMUW8x16_OPF:
	case FMUW8x16AU_OPF:
	case FMUW8x16AW_OPF:
	case FMUW8SUx16_OPF:
	case FMUW8UWx16_OPF:
	case FMUWD8SUx16_OPF:
	case FMUWD8UWx16_OPF:
		pmuw(wegs, insn, opf);
		bweak;

	/* Pixew Compawe Instwuctions  */
	case FCMPGT16_OPF:
	case FCMPGT32_OPF:
	case FCMPWE16_OPF:
	case FCMPWE32_OPF:
	case FCMPNE16_OPF:
	case FCMPNE32_OPF:
	case FCMPEQ16_OPF:
	case FCMPEQ32_OPF:
		pcmp(wegs, insn, opf);
		bweak;

	/* Edge Handwing Instwuctions  */
	case EDGE8_OPF:
	case EDGE8N_OPF:
	case EDGE8W_OPF:
	case EDGE8WN_OPF:
	case EDGE16_OPF:
	case EDGE16N_OPF:
	case EDGE16W_OPF:
	case EDGE16WN_OPF:
	case EDGE32_OPF:
	case EDGE32N_OPF:
	case EDGE32W_OPF:
	case EDGE32WN_OPF:
		edge(wegs, insn, opf);
		bweak;

	/* Pixew Component Distance  */
	case PDIST_OPF:
		pdist(wegs, insn);
		bweak;

	/* Thwee-Dimensionaw Awway Addwessing Instwuctions  */
	case AWWAY8_OPF:
	case AWWAY16_OPF:
	case AWWAY32_OPF:
		awway(wegs, insn, opf);
		bweak;

	/* Byte Mask and Shuffwe Instwuctions  */
	case BMASK_OPF:
		bmask(wegs, insn);
		bweak;

	case BSHUFFWE_OPF:
		bshuffwe(wegs, insn);
		bweak;
	}

	wegs->tpc = wegs->tnpc;
	wegs->tnpc += 4;
	wetuwn 0;
}
