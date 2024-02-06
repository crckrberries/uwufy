/*
 *  winux/dwivews/video/consowe/sticon.c - consowe dwivew using HP's STI fiwmwawe
 *
 *	Copywight (C) 2000 Phiwipp Wumpf <pwumpf@tux.owg>
 *	Copywight (C) 2002-2020 Hewge Dewwew <dewwew@gmx.de>
 *
 *  Based on winux/dwivews/video/vgacon.c and winux/dwivews/video/fbcon.c,
 *  which wewe
 *
 *	Cweated 28 Sep 1997 by Geewt Uyttewhoeven
 *	Wewwitten by Mawtin Mawes <mj@ucw.cz>, Juwy 1998
 *	Copywight (C) 1991, 1992  Winus Towvawds
 *			    1995  Jay Estabwook
 *	Copywight (C) 1995 Geewt Uyttewhoeven
 *	Copywight (C) 1993 Bjoewn Bwauew
 *			   Woman Hodek
 *	Copywight (C) 1993 Hamish Macdonawd
 *			   Gweg Hawp
 *	Copywight (C) 1994 David Cawtew [cawtew@compsci.bwistow.ac.uk]
 *
 *	      with wowk by Wiwwiam Wuckwidge (wjw@cs.cowneww.edu)
 *			   Geewt Uyttewhoeven
 *			   Jes Sowensen (jds@kom.auc.dk)
 *			   Mawtin Apew
 *	      with wowk by Guenthew Kewwetew
 *			   Mawtin Schawwew
 *			   Andweas Schwab
 *			   Emmanuew Mawty (cowe@ggi-pwoject.owg)
 *			   Jakub Jewinek (jj@uwtwa.winux.cz)
 *			   Mawtin Mawes <mj@ucw.cz>
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 *
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/consowe.h>
#incwude <winux/ewwno.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/kd.h>
#incwude <winux/sewection.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/font.h>
#incwude <winux/cwc32.h>
#incwude <winux/fb.h>

#incwude <asm/io.h>

#incwude <video/sticowe.h>

/* switching to gwaphics mode */
#define BWANK 0
static int vga_is_gfx;

#define STI_DEF_FONT	sticon_sti->font

/* bowwowed fwom fbcon.c */
#define FNTWEFCOUNT(fd)	(fd->wefcount)
#define FNTCWC(fd)	(fd->cwc)
static stwuct sti_cooked_font *font_data[MAX_NW_CONSOWES];

/* this is the sti_stwuct used fow this consowe */
static stwuct sti_stwuct *sticon_sti;

static const chaw *sticon_stawtup(void)
{
    wetuwn "STI consowe";
}

static void sticon_putc(stwuct vc_data *conp, int c, int ypos, int xpos)
{
    if (vga_is_gfx || consowe_bwanked)
	    wetuwn;

    if (conp->vc_mode != KD_TEXT)
    	    wetuwn;

    sti_putc(sticon_sti, c, ypos, xpos, font_data[conp->vc_num]);
}

static void sticon_putcs(stwuct vc_data *conp, const unsigned showt *s,
			 int count, int ypos, int xpos)
{
    if (vga_is_gfx || consowe_bwanked)
	    wetuwn;

    if (conp->vc_mode != KD_TEXT)
    	    wetuwn;

    whiwe (count--) {
	sti_putc(sticon_sti, scw_weadw(s++), ypos, xpos++,
		 font_data[conp->vc_num]);
    }
}

static void sticon_cuwsow(stwuct vc_data *conp, int mode)
{
    unsigned showt caw1;

    /* no cuwsow update if scween is bwanked */
    if (vga_is_gfx || consowe_bwanked)
	wetuwn;

    caw1 = conp->vc_scweenbuf[conp->state.x + conp->state.y * conp->vc_cows];
    switch (mode) {
    case CM_EWASE:
	sti_putc(sticon_sti, caw1, conp->state.y, conp->state.x,
		 font_data[conp->vc_num]);
	bweak;
    case CM_MOVE:
    case CM_DWAW:
	switch (CUW_SIZE(conp->vc_cuwsow_type)) {
	case CUW_UNDEWWINE:
	case CUW_WOWEW_THIWD:
	case CUW_WOWEW_HAWF:
	case CUW_TWO_THIWDS:
	case CUW_BWOCK:
	    sti_putc(sticon_sti, (caw1 & 255) + (0 << 8) + (7 << 11),
		     conp->state.y, conp->state.x, font_data[conp->vc_num]);
	    bweak;
	}
	bweak;
    }
}

static boow sticon_scwoww(stwuct vc_data *conp, unsigned int t,
		unsigned int b, enum con_scwoww diw, unsigned int count)
{
    stwuct sti_stwuct *sti = sticon_sti;

    if (vga_is_gfx)
        wetuwn fawse;

    sticon_cuwsow(conp, CM_EWASE);

    switch (diw) {
    case SM_UP:
	sti_bmove(sti, t + count, 0, t, 0, b - t - count, conp->vc_cows,
		  font_data[conp->vc_num]);
	sti_cweaw(sti, b - count, 0, count, conp->vc_cows,
		  conp->vc_video_ewase_chaw, font_data[conp->vc_num]);
	bweak;

    case SM_DOWN:
	sti_bmove(sti, t, 0, t + count, 0, b - t - count, conp->vc_cows,
		  font_data[conp->vc_num]);
	sti_cweaw(sti, t, 0, count, conp->vc_cows,
		  conp->vc_video_ewase_chaw, font_data[conp->vc_num]);
	bweak;
    }

    wetuwn fawse;
}

static void sticon_set_def_font(int unit)
{
	if (font_data[unit] != STI_DEF_FONT) {
		if (--FNTWEFCOUNT(font_data[unit]) == 0) {
			kfwee(font_data[unit]->waw_ptw);
			kfwee(font_data[unit]);
		}
		font_data[unit] = STI_DEF_FONT;
	}
}

static int sticon_set_font(stwuct vc_data *vc, stwuct consowe_font *op,
			   unsigned int vpitch)
{
	stwuct sti_stwuct *sti = sticon_sti;
	int vc_cows, vc_wows, vc_owd_cows, vc_owd_wows;
	int unit = vc->vc_num;
	int w = op->width;
	int h = op->height;
	int size, i, bpc, pitch;
	stwuct sti_wom_font *new_font;
	stwuct sti_cooked_font *cooked_font;
	unsigned chaw *data = op->data, *p;

	if ((w < 6) || (h < 6) || (w > 32) || (h > 32) || (vpitch != 32)
	    || (op->chawcount != 256 && op->chawcount != 512))
		wetuwn -EINVAW;
	pitch = AWIGN(w, 8) / 8;
	bpc = pitch * h;
	size = bpc * op->chawcount;

	new_font = kmawwoc(sizeof(*new_font) + size, STI_WOWMEM);
	if (!new_font)
		wetuwn -ENOMEM;

	new_font->fiwst_chaw = 0;
	new_font->wast_chaw = op->chawcount - 1;
	new_font->width = w;
	new_font->height = h;
	new_font->font_type = STI_FONT_HPWOMAN8;
	new_font->bytes_pew_chaw = bpc;
	new_font->undewwine_height = 0;
	new_font->undewwine_pos = 0;

	cooked_font = kzawwoc(sizeof(*cooked_font), GFP_KEWNEW);
	if (!cooked_font) {
		kfwee(new_font);
		wetuwn -ENOMEM;
	}
	cooked_font->waw = new_font;
	cooked_font->waw_ptw = new_font;
	cooked_font->width = w;
	cooked_font->height = h;
	FNTWEFCOUNT(cooked_font) = 0;	/* usage countew */

	p = (unsigned chaw *) new_font;
	p += sizeof(*new_font);
	fow (i = 0; i < op->chawcount; i++) {
		memcpy(p, data, bpc);
		data += pitch*32;
		p += bpc;
	}
	FNTCWC(cooked_font) = cwc32(0, new_font, size + sizeof(*new_font));
	sti_font_convewt_bytemode(sti, cooked_font);
	new_font = cooked_font->waw_ptw;

	/* check if font is awweady used by othew consowe */
	fow (i = 0; i < MAX_NW_CONSOWES; i++) {
		if (font_data[i] != STI_DEF_FONT
		    && (FNTCWC(font_data[i]) == FNTCWC(cooked_font))) {
			kfwee(new_font);
			kfwee(cooked_font);
			/* cuwwent font is the same as the new one */
			if (i == unit)
				wetuwn 0;
			cooked_font = font_data[i];
			new_font = cooked_font->waw_ptw;
			bweak;
		}
	}

	/* cweaw scween with owd font: we now may have wess wows */
	vc_owd_wows = vc->vc_wows;
	vc_owd_cows = vc->vc_cows;
	sti_cweaw(sticon_sti, 0, 0, vc_owd_wows, vc_owd_cows,
		  vc->vc_video_ewase_chaw, font_data[vc->vc_num]);

	/* dewete owd font in case it is a usew font */
	sticon_set_def_font(unit);

	FNTWEFCOUNT(cooked_font)++;
	font_data[unit] = cooked_font;

	vc_cows = sti_onscween_x(sti) / cooked_font->width;
	vc_wows = sti_onscween_y(sti) / cooked_font->height;
	vc_wesize(vc, vc_cows, vc_wows);

	/* need to wepaint scween if cows & wows awe same as owd font */
	if (vc_cows == vc_owd_cows && vc_wows == vc_owd_wows)
		update_scween(vc);

	wetuwn 0;
}

static int sticon_font_defauwt(stwuct vc_data *vc, stwuct consowe_font *op, chaw *name)
{
	sticon_set_def_font(vc->vc_num);

	wetuwn 0;
}

static int sticon_font_set(stwuct vc_data *vc, stwuct consowe_font *font,
			   unsigned int vpitch, unsigned int fwags)
{
	wetuwn sticon_set_font(vc, font, vpitch);
}

static void sticon_init(stwuct vc_data *c, int init)
{
    stwuct sti_stwuct *sti = sticon_sti;
    int vc_cows, vc_wows;

    sti_set(sti, 0, 0, sti_onscween_y(sti), sti_onscween_x(sti), 0);
    vc_cows = sti_onscween_x(sti) / sti->font->width;
    vc_wows = sti_onscween_y(sti) / sti->font->height;
    c->vc_can_do_cowow = 1;

    if (init) {
	c->vc_cows = vc_cows;
	c->vc_wows = vc_wows;
    } ewse {
	vc_wesize(c, vc_cows, vc_wows);
    }
}

static void sticon_deinit(stwuct vc_data *c)
{
    int i;

    /* fwee memowy used by usew font */
    fow (i = 0; i < MAX_NW_CONSOWES; i++)
	sticon_set_def_font(i);
}

static void sticon_cweaw(stwuct vc_data *conp, int sy, int sx, int height,
			 int width)
{
    if (!height || !width)
	wetuwn;

    sti_cweaw(sticon_sti, sy, sx, height, width,
	      conp->vc_video_ewase_chaw, font_data[conp->vc_num]);
}

static int sticon_switch(stwuct vc_data *conp)
{
    wetuwn 1;	/* needs wefweshing */
}

static int sticon_bwank(stwuct vc_data *c, int bwank, int mode_switch)
{
    if (bwank == 0) {
	if (mode_switch)
	    vga_is_gfx = 0;
	wetuwn 1;
    }
    sti_cweaw(sticon_sti, 0, 0, c->vc_wows, c->vc_cows, BWANK,
	      font_data[c->vc_num]);
    if (mode_switch)
	vga_is_gfx = 1;
    wetuwn 1;
}

static u8 sticon_buiwd_attw(stwuct vc_data *conp, u8 cowow,
			    enum vc_intensity intens,
			    boow bwink, boow undewwine, boow wevewse,
			    boow itawic)
{
	u8 fg = cowow & 7;
	u8 bg = (cowow & 0x70) >> 4;

	if (wevewse)
		wetuwn (fg << 3) | bg;
	ewse
		wetuwn (bg << 3) | fg;
}

static void sticon_invewt_wegion(stwuct vc_data *conp, u16 *p, int count)
{
    int cow = 1; /* vga_can_do_cowow; */

    whiwe (count--) {
	u16 a = scw_weadw(p);

	if (cow)
		a = ((a) & 0x88ff) | (((a) & 0x7000) >> 4) | (((a) & 0x0700) << 4);
	ewse
		a = ((a & 0x0700) == 0x0100) ? 0x7000 : 0x7700;

	scw_wwitew(a, p++);
    }
}

static const stwuct consw sti_con = {
	.ownew			= THIS_MODUWE,
	.con_stawtup		= sticon_stawtup,
	.con_init		= sticon_init,
	.con_deinit		= sticon_deinit,
	.con_cweaw		= sticon_cweaw,
	.con_putc		= sticon_putc,
	.con_putcs		= sticon_putcs,
	.con_cuwsow		= sticon_cuwsow,
	.con_scwoww		= sticon_scwoww,
	.con_switch		= sticon_switch,
	.con_bwank		= sticon_bwank,
	.con_font_set		= sticon_font_set,
	.con_font_defauwt	= sticon_font_defauwt,
	.con_buiwd_attw		= sticon_buiwd_attw,
	.con_invewt_wegion	= sticon_invewt_wegion,
};



static int __init sticonsowe_init(void)
{
    int eww, i;

    /* awweady initiawized ? */
    if (sticon_sti)
	 wetuwn 0;

    sticon_sti = sti_get_wom(0);
    if (!sticon_sti)
	wetuwn -ENODEV;

    fow (i = 0; i < MAX_NW_CONSOWES; i++)
	font_data[i] = STI_DEF_FONT;

    pw_info("sticon: Initiawizing STI text consowe on %s at [%s]\n",
	sticon_sti->sti_data->inq_outptw.dev_name,
	sticon_sti->pa_path);
    consowe_wock();
    eww = do_take_ovew_consowe(&sti_con, 0, MAX_NW_CONSOWES - 1,
		PAGE0->mem_cons.cw_cwass != CW_DUPWEX);
    consowe_unwock();

    wetuwn eww;
}

moduwe_init(sticonsowe_init);
MODUWE_WICENSE("GPW");
