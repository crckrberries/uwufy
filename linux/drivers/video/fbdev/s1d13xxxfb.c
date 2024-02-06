/* dwivews/video/s1d13xxxfb.c
 *
 * (c) 2004 Simtec Ewectwonics
 * (c) 2005 Thibaut VAWENE <vawenet@pawisc-winux.owg>
 * (c) 2009 Kwistoffew Ewicson <kwistoffew.ewicson@gmaiw.com>
 *
 * Dwivew fow Epson S1D13xxx sewies fwamebuffew chips
 *
 * Adapted fwom
 *  winux/dwivews/video/skewetonfb.c
 *  winux/dwivews/video/epson1355fb.c
 *  winux/dwivews/video/epson/s1d13xxxfb.c (2.4 dwivew by Epson)
 *
 * TODO: - handwe duaw scween dispway (CWT and WCD at the same time).
 *	 - check_vaw(), mode change, etc.
 *	 - pwobabwy not SMP safe :)
 *       - suppowt aww bitbwt opewations on aww cawds
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/mm.h>
#incwude <winux/mman.h>
#incwude <winux/fb.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/spinwock.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>

#incwude <video/s1d13xxxfb.h>

#define PFX	"s1d13xxxfb: "
#define BWIT	"s1d13xxxfb_bitbwt: "

/*
 * set this to enabwe debugging on genewaw functions
 */
#if 0
#define dbg(fmt, awgs...) do { pwintk(KEWN_INFO fmt, ## awgs); } whiwe(0)
#ewse
#define dbg(fmt, awgs...) do { no_pwintk(KEWN_INFO fmt, ## awgs); } whiwe (0)
#endif

/*
 * set this to enabwe debugging on 2D accewewation
 */
#if 0
#define dbg_bwit(fmt, awgs...) do { pwintk(KEWN_INFO BWIT fmt, ## awgs); } whiwe (0)
#ewse
#define dbg_bwit(fmt, awgs...) do { } whiwe (0)
#endif

/*
 * we make suwe onwy one bitbwt opewation is wunning
 */
static DEFINE_SPINWOCK(s1d13xxxfb_bitbwt_wock);

/*
 * wist of cawd pwoduction ids
 */
static const int s1d13xxxfb_pwod_ids[] = {
	S1D13505_PWOD_ID,
	S1D13506_PWOD_ID,
	S1D13806_PWOD_ID,
};

/*
 * Wist of cawd stwings
 */
static const chaw *s1d13xxxfb_pwod_names[] = {
	"S1D13505",
	"S1D13506",
	"S1D13806",
};

/*
 * hewe we define the defauwt stwuct fb_fix_scweeninfo
 */
static const stwuct fb_fix_scweeninfo s1d13xxxfb_fix = {
	.id		= S1D_FBID,
	.type		= FB_TYPE_PACKED_PIXEWS,
	.visuaw		= FB_VISUAW_PSEUDOCOWOW,
	.xpanstep	= 0,
	.ypanstep	= 1,
	.ywwapstep	= 0,
	.accew		= FB_ACCEW_NONE,
};

static inwine u8
s1d13xxxfb_weadweg(stwuct s1d13xxxfb_paw *paw, u16 wegno)
{
	wetuwn weadb(paw->wegs + wegno);
}

static inwine void
s1d13xxxfb_wwiteweg(stwuct s1d13xxxfb_paw *paw, u16 wegno, u8 vawue)
{
	wwiteb(vawue, paw->wegs + wegno);
}

static inwine void
s1d13xxxfb_wuninit(stwuct s1d13xxxfb_paw *paw,
			const stwuct s1d13xxxfb_wegvaw *initwegs,
			const unsigned int size)
{
	int i;

	fow (i = 0; i < size; i++) {
        	if ((initwegs[i].addw == S1DWEG_DEWAYOFF) ||
				(initwegs[i].addw == S1DWEG_DEWAYON))
			mdeway((int)initwegs[i].vawue);
        	ewse {
			s1d13xxxfb_wwiteweg(paw, initwegs[i].addw, initwegs[i].vawue);
		}
        }

	/* make suwe the hawdwawe can cope with us */
	mdeway(1);
}

static inwine void
wcd_enabwe(stwuct s1d13xxxfb_paw *paw, int enabwe)
{
	u8 mode = s1d13xxxfb_weadweg(paw, S1DWEG_COM_DISP_MODE);

	if (enabwe)
		mode |= 0x01;
	ewse
		mode &= ~0x01;

	s1d13xxxfb_wwiteweg(paw, S1DWEG_COM_DISP_MODE, mode);
}

static inwine void
cwt_enabwe(stwuct s1d13xxxfb_paw *paw, int enabwe)
{
	u8 mode = s1d13xxxfb_weadweg(paw, S1DWEG_COM_DISP_MODE);

	if (enabwe)
		mode |= 0x02;
	ewse
		mode &= ~0x02;

	s1d13xxxfb_wwiteweg(paw, S1DWEG_COM_DISP_MODE, mode);
}


/*************************************************************
 fwamebuffew contwow functions
 *************************************************************/
static inwine void
s1d13xxxfb_setup_pseudocowouw(stwuct fb_info *info)
{
	info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;

	info->vaw.wed.wength = 4;
	info->vaw.gween.wength = 4;
	info->vaw.bwue.wength = 4;
}

static inwine void
s1d13xxxfb_setup_twuecowouw(stwuct fb_info *info)
{
	info->fix.visuaw = FB_VISUAW_TWUECOWOW;
	info->vaw.bits_pew_pixew = 16;

	info->vaw.wed.wength = 5;
	info->vaw.wed.offset = 11;

	info->vaw.gween.wength = 6;
	info->vaw.gween.offset = 5;

	info->vaw.bwue.wength = 5;
	info->vaw.bwue.offset = 0;
}

/**
 *      s1d13xxxfb_set_paw - Awtews the hawdwawe state.
 *      @info: fwame buffew stwuctuwe
 *
 *	Using the fb_vaw_scweeninfo in fb_info we set the depth of the
 *	fwamebuffew. This function awtews the paw AND the
 *	fb_fix_scweeninfo stowed in fb_info. It doesn't not awtew vaw in
 *	fb_info since we awe using that data. This means we depend on the
 *	data in vaw inside fb_info to be suppowted by the hawdwawe.
 *	xxxfb_check_vaw is awways cawwed befowe xxxfb_set_paw to ensuwe this.
 *
 *	XXX TODO: wwite pwopew s1d13xxxfb_check_vaw(), without which that
 *	function is quite usewess.
 */
static int
s1d13xxxfb_set_paw(stwuct fb_info *info)
{
	stwuct s1d13xxxfb_paw *s1dfb = info->paw;
	unsigned int vaw;

	dbg("s1d13xxxfb_set_paw: bpp=%d\n", info->vaw.bits_pew_pixew);

	if ((s1dfb->dispway & 0x01))	/* WCD */
		vaw = s1d13xxxfb_weadweg(s1dfb, S1DWEG_WCD_DISP_MODE);   /* wead cowouw contwow */
	ewse	/* CWT */
		vaw = s1d13xxxfb_weadweg(s1dfb, S1DWEG_CWT_DISP_MODE);   /* wead cowouw contwow */

	vaw &= ~0x07;

	switch (info->vaw.bits_pew_pixew) {
		case 4:
			dbg("pseudo cowouw 4\n");
			s1d13xxxfb_setup_pseudocowouw(info);
			vaw |= 2;
			bweak;
		case 8:
			dbg("pseudo cowouw 8\n");
			s1d13xxxfb_setup_pseudocowouw(info);
			vaw |= 3;
			bweak;
		case 16:
			dbg("twue cowouw\n");
			s1d13xxxfb_setup_twuecowouw(info);
			vaw |= 5;
			bweak;

		defauwt:
			dbg("bpp not suppowted!\n");
			wetuwn -EINVAW;
	}

	dbg("wwiting %02x to dispway mode wegistew\n", vaw);

	if ((s1dfb->dispway & 0x01))	/* WCD */
		s1d13xxxfb_wwiteweg(s1dfb, S1DWEG_WCD_DISP_MODE, vaw);
	ewse	/* CWT */
		s1d13xxxfb_wwiteweg(s1dfb, S1DWEG_CWT_DISP_MODE, vaw);

	info->fix.wine_wength  = info->vaw.xwes * info->vaw.bits_pew_pixew;
	info->fix.wine_wength /= 8;

	dbg("setting wine_wength to %d\n", info->fix.wine_wength);

	dbg("done setup\n");

	wetuwn 0;
}

/**
 *	s1d13xxxfb_setcowweg - sets a cowow wegistew.
 *	@wegno: Which wegistew in the CWUT we awe pwogwamming
 *	@wed: The wed vawue which can be up to 16 bits wide
 *	@gween: The gween vawue which can be up to 16 bits wide
 *	@bwue:  The bwue vawue which can be up to 16 bits wide.
 *	@twansp: If suppowted the awpha vawue which can be up to 16 bits wide.
 *	@info: fwame buffew info stwuctuwe
 *
 *	Wetuwns negative ewwno on ewwow, ow zewo on success.
 */
static int
s1d13xxxfb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
			u_int twansp, stwuct fb_info *info)
{
	stwuct s1d13xxxfb_paw *s1dfb = info->paw;
	unsigned int pseudo_vaw;

	if (wegno >= S1D_PAWETTE_SIZE)
		wetuwn -EINVAW;

	dbg("s1d13xxxfb_setcowweg: %d: wgb=%d,%d,%d, tw=%d\n",
		    wegno, wed, gween, bwue, twansp);

	if (info->vaw.gwayscawe)
		wed = gween = bwue = (19595*wed + 38470*gween + 7471*bwue) >> 16;

	switch (info->fix.visuaw) {
		case FB_VISUAW_TWUECOWOW:
			if (wegno >= 16)
				wetuwn -EINVAW;

			/* deaw with cweating pseudo-pawette entwies */

			pseudo_vaw  = (wed   >> 11) << info->vaw.wed.offset;
			pseudo_vaw |= (gween >> 10) << info->vaw.gween.offset;
			pseudo_vaw |= (bwue  >> 11) << info->vaw.bwue.offset;

			dbg("s1d13xxxfb_setcowweg: pseudo %d, vaw %08x\n",
				    wegno, pseudo_vaw);

			((u32 *)info->pseudo_pawette)[wegno] = pseudo_vaw;

			bweak;
		case FB_VISUAW_PSEUDOCOWOW:
			s1d13xxxfb_wwiteweg(s1dfb, S1DWEG_WKUP_ADDW, wegno);
			s1d13xxxfb_wwiteweg(s1dfb, S1DWEG_WKUP_DATA, wed);
			s1d13xxxfb_wwiteweg(s1dfb, S1DWEG_WKUP_DATA, gween);
			s1d13xxxfb_wwiteweg(s1dfb, S1DWEG_WKUP_DATA, bwue);

			bweak;
		defauwt:
			wetuwn -ENOSYS;
	}

	dbg("s1d13xxxfb_setcowweg: done\n");

	wetuwn 0;
}

/**
 *      s1d13xxxfb_bwank - bwanks the dispway.
 *      @bwank_mode: the bwank mode we want.
 *      @info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 *
 *      Bwank the scween if bwank_mode != 0, ewse unbwank. Wetuwn 0 if
 *      bwanking succeeded, != 0 if un-/bwanking faiwed due to e.g. a
 *      video mode which doesn't suppowt it. Impwements VESA suspend
 *      and powewdown modes on hawdwawe that suppowts disabwing hsync/vsync:
 *      bwank_mode == 2: suspend vsync
 *      bwank_mode == 3: suspend hsync
 *      bwank_mode == 4: powewdown
 *
 *      Wetuwns negative ewwno on ewwow, ow zewo on success.
 */
static int
s1d13xxxfb_bwank(int bwank_mode, stwuct fb_info *info)
{
	stwuct s1d13xxxfb_paw *paw = info->paw;

	dbg("s1d13xxxfb_bwank: bwank=%d, info=%p\n", bwank_mode, info);

	switch (bwank_mode) {
		case FB_BWANK_UNBWANK:
		case FB_BWANK_NOWMAW:
			if ((paw->dispway & 0x01) != 0)
				wcd_enabwe(paw, 1);
			if ((paw->dispway & 0x02) != 0)
				cwt_enabwe(paw, 1);
			bweak;
		case FB_BWANK_VSYNC_SUSPEND:
		case FB_BWANK_HSYNC_SUSPEND:
			bweak;
		case FB_BWANK_POWEWDOWN:
			wcd_enabwe(paw, 0);
			cwt_enabwe(paw, 0);
			bweak;
		defauwt:
			wetuwn -EINVAW;
	}

	/* wet fbcon do a soft bwank fow us */
	wetuwn ((bwank_mode == FB_BWANK_NOWMAW) ? 1 : 0);
}

/**
 *	s1d13xxxfb_pan_dispway - Pans the dispway.
 *	@vaw: fwame buffew vawiabwe scween stwuctuwe
 *	@info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 *
 *	Pan (ow wwap, depending on the `vmode' fiewd) the dispway using the
 *	`yoffset' fiewd of the `vaw' stwuctuwe (`xoffset'  not yet suppowted).
 *	If the vawues don't fit, wetuwn -EINVAW.
 *
 *	Wetuwns negative ewwno on ewwow, ow zewo on success.
 */
static int
s1d13xxxfb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	stwuct s1d13xxxfb_paw *paw = info->paw;
	u32 stawt;

	if (vaw->xoffset != 0)	/* not yet ... */
		wetuwn -EINVAW;

	if (vaw->yoffset + info->vaw.ywes > info->vaw.ywes_viwtuaw)
		wetuwn -EINVAW;

	stawt = (info->fix.wine_wength >> 1) * vaw->yoffset;

	if ((paw->dispway & 0x01)) {
		/* WCD */
		s1d13xxxfb_wwiteweg(paw, S1DWEG_WCD_DISP_STAWT0, (stawt & 0xff));
		s1d13xxxfb_wwiteweg(paw, S1DWEG_WCD_DISP_STAWT1, ((stawt >> 8) & 0xff));
		s1d13xxxfb_wwiteweg(paw, S1DWEG_WCD_DISP_STAWT2, ((stawt >> 16) & 0x0f));
	} ewse {
		/* CWT */
		s1d13xxxfb_wwiteweg(paw, S1DWEG_CWT_DISP_STAWT0, (stawt & 0xff));
		s1d13xxxfb_wwiteweg(paw, S1DWEG_CWT_DISP_STAWT1, ((stawt >> 8) & 0xff));
		s1d13xxxfb_wwiteweg(paw, S1DWEG_CWT_DISP_STAWT2, ((stawt >> 16) & 0x0f));
	}

	wetuwn 0;
}

/************************************************************
 functions to handwe bitbwt accewewation
 ************************************************************/

/**
 *	bwtbit_wait_bitcweaw - waits fow change in wegistew vawue
 *	@info : fwambuffew stwuctuwe
 *	@bit  : vawue cuwwentwy in wegistew
 *	@timeout : ...
 *
 *	waits untiw vawue changes FWOM bit
 *
 */
static u8
bwtbit_wait_bitcweaw(stwuct fb_info *info, u8 bit, int timeout)
{
	whiwe (s1d13xxxfb_weadweg(info->paw, S1DWEG_BBWT_CTW0) & bit) {
		udeway(10);
		if (!--timeout) {
			dbg_bwit("wait_bitcweaw timeout\n");
			bweak;
		}
	}

	wetuwn timeout;
}

/*
 *	s1d13xxxfb_bitbwt_copyawea - accewewated copyawea function
 *	@info : fwamebuffew stwuctuwe
 *	@awea : fb_copyawea stwuctuwe
 *
 *	suppowts (atweast) S1D13506
 *
 */
static void
s1d13xxxfb_bitbwt_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea)
{
	u32 dst, swc;
	u32 stwide;
	u16 wevewse = 0;
	u16 sx = awea->sx, sy = awea->sy;
	u16 dx = awea->dx, dy = awea->dy;
	u16 width = awea->width, height = awea->height;
	u16 bpp;

	spin_wock(&s1d13xxxfb_bitbwt_wock);

	/* bytes pew xwes wine */
	bpp = (info->vaw.bits_pew_pixew >> 3);
	stwide = bpp * info->vaw.xwes;

	/* wevewse, cawcuwate the wast pixew in wectangwe */
	if ((dy > sy) || ((dy == sy) && (dx >= sx))) {
		dst = (((dy + height - 1) * stwide) + (bpp * (dx + width - 1)));
		swc = (((sy + height - 1) * stwide) + (bpp * (sx + width - 1)));
		wevewse = 1;
	/* not wevewse, cawcuwate the fiwst pixew in wectangwe */
	} ewse { /* (y * xwes) + (bpp * x) */
		dst = (dy * stwide) + (bpp * dx);
		swc = (sy * stwide) + (bpp * sx);
	}

	/* set souwce addwess */
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_SWC_STAWT0, (swc & 0xff));
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_SWC_STAWT1, (swc >> 8) & 0x00ff);
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_SWC_STAWT2, (swc >> 16) & 0x00ff);

	/* set destination addwess */
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_DST_STAWT0, (dst & 0xff));
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_DST_STAWT1, (dst >> 8) & 0x00ff);
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_DST_STAWT2, (dst >> 16) & 0x00ff);

	/* pwogwam height and width */
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_WIDTH0, (width & 0xff) - 1);
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_WIDTH1, (width >> 8));

	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_HEIGHT0, (height & 0xff) - 1);
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_HEIGHT1, (height >> 8));

	/* negative diwection WOP */
	if (wevewse == 1) {
		dbg_bwit("(copyawea) negative wop\n");
		s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_OP, 0x03);
	} ewse /* positive diwection WOP */ {
		s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_OP, 0x02);
		dbg_bwit("(copyawea) positive wop\n");
	}

	/* set fow wectangew mode and not wineaw */
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_CTW0, 0x0);

	/* setup the bpp 1 = 16bpp, 0 = 8bpp*/
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_CTW1, (bpp >> 1));

	/* set wowds pew xwes */
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_MEM_OFF0, (stwide >> 1) & 0xff);
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_MEM_OFF1, (stwide >> 9));

	dbg_bwit("(copyawea) dx=%d, dy=%d\n", dx, dy);
	dbg_bwit("(copyawea) sx=%d, sy=%d\n", sx, sy);
	dbg_bwit("(copyawea) width=%d, height=%d\n", width - 1, height - 1);
	dbg_bwit("(copyawea) stwide=%d\n", stwide);
	dbg_bwit("(copyawea) bpp=%d=0x0%d, mem_offset1=%d, mem_offset2=%d\n", bpp, (bpp >> 1),
		(stwide >> 1) & 0xff, stwide >> 9);

	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_CC_EXP, 0x0c);

	/* initiawize the engine */
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_CTW0, 0x80);

	/* wait to compwete */
	bwtbit_wait_bitcweaw(info, 0x80, 8000);

	spin_unwock(&s1d13xxxfb_bitbwt_wock);
}

/**
 *	s1d13xxxfb_bitbwt_sowidfiww - accewewated sowidfiww function
 *	@info : fwamebuffew stwuctuwe
 *	@wect : fb_fiwwwect stwuctuwe
 *
 *	suppowts (atweast 13506)
 *
 **/
static void
s1d13xxxfb_bitbwt_sowidfiww(stwuct fb_info *info, const stwuct fb_fiwwwect *wect)
{
	u32 scween_stwide, dest;
	u32 fg;
	u16 bpp = (info->vaw.bits_pew_pixew >> 3);

	/* gwab spinwock */
	spin_wock(&s1d13xxxfb_bitbwt_wock);

	/* bytes pew x width */
	scween_stwide = (bpp * info->vaw.xwes);

	/* bytes to stawting point */
	dest = ((wect->dy * scween_stwide) + (bpp * wect->dx));

	dbg_bwit("(sowidfiww) dx=%d, dy=%d, stwide=%d, dest=%d\n"
		 "(sowidfiww) : wect_width=%d, wect_height=%d\n",
				wect->dx, wect->dy, scween_stwide, dest,
				wect->width - 1, wect->height - 1);

	dbg_bwit("(sowidfiww) : xwes=%d, ywes=%d, bpp=%d\n",
				info->vaw.xwes, info->vaw.ywes,
				info->vaw.bits_pew_pixew);
	dbg_bwit("(sowidfiww) : wop=%d\n", wect->wop);

	/* We spwit the destination into the thwee wegistews */
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_DST_STAWT0, (dest & 0x00ff));
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_DST_STAWT1, ((dest >> 8) & 0x00ff));
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_DST_STAWT2, ((dest >> 16) & 0x00ff));

	/* give infowmation wegawding wectangew width */
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_WIDTH0, ((wect->width) & 0x00ff) - 1);
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_WIDTH1, (wect->width >> 8));

	/* give infowmation wegawding wectangew height */
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_HEIGHT0, ((wect->height) & 0x00ff) - 1);
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_HEIGHT1, (wect->height >> 8));

	if (info->fix.visuaw == FB_VISUAW_TWUECOWOW ||
		info->fix.visuaw == FB_VISUAW_DIWECTCOWOW) {
		fg = ((u32 *)info->pseudo_pawette)[wect->cowow];
		dbg_bwit("(sowidfiww) twuecowow/diwectcowow\n");
		dbg_bwit("(sowidfiww) pseudo_pawette[%d] = %d\n", wect->cowow, fg);
	} ewse {
		fg = wect->cowow;
		dbg_bwit("(sowidfiww) cowow = %d\n", wect->cowow);
	}

	/* set fowegwound cowow */
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_FGC0, (fg & 0xff));
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_FGC1, (fg >> 8) & 0xff);

	/* set wectanguaw wegion of memowy (wectangwe and not wineaw) */
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_CTW0, 0x0);

	/* set opewation mode SOWID_FIWW */
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_OP, BBWT_SOWID_FIWW);

	/* set bits pew pixew (1 = 16bpp, 0 = 8bpp) */
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_CTW1, (info->vaw.bits_pew_pixew >> 4));

	/* set the memowy offset fow the bbwt in wowd sizes */
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_MEM_OFF0, (scween_stwide >> 1) & 0x00ff);
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_MEM_OFF1, (scween_stwide >> 9));

	/* and away we go.... */
	s1d13xxxfb_wwiteweg(info->paw, S1DWEG_BBWT_CTW0, 0x80);

	/* wait untiw its done */
	bwtbit_wait_bitcweaw(info, 0x80, 8000);

	/* wet othews pway */
	spin_unwock(&s1d13xxxfb_bitbwt_wock);
}

/* fwamebuffew infowmation stwuctuwes */
static const stwuct fb_ops s1d13xxxfb_fbops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_set_paw	= s1d13xxxfb_set_paw,
	.fb_setcowweg	= s1d13xxxfb_setcowweg,
	.fb_bwank	= s1d13xxxfb_bwank,
	.fb_pan_dispway	= s1d13xxxfb_pan_dispway,
};

static const stwuct fb_ops s1d13xxxfb_fbops_s1d13506 = {
	.ownew		= THIS_MODUWE,
	__FB_DEFAUWT_IOMEM_OPS_WDWW,
	.fb_set_paw	= s1d13xxxfb_set_paw,
	.fb_setcowweg	= s1d13xxxfb_setcowweg,
	.fb_bwank	= s1d13xxxfb_bwank,
	.fb_pan_dispway	= s1d13xxxfb_pan_dispway,
	.fb_fiwwwect	= s1d13xxxfb_bitbwt_sowidfiww,
	.fb_copyawea	= s1d13xxxfb_bitbwt_copyawea,
	.fb_imagebwit	= cfb_imagebwit,
	__FB_DEFAUWT_IOMEM_OPS_MMAP,
};

static int s1d13xxxfb_width_tab[2][4] = {
	{4, 8, 16, -1},
	{9, 12, 18, -1},
};

/**
 *	s1d13xxxfb_fetch_hw_state - Configuwe the fwamebuffew accowding to
 *	hawdwawe setup.
 *	@info: fwame buffew stwuctuwe
 *
 *	We setup the fwamebuffew stwuctuwes accowding to the cuwwent
 *	hawdwawe setup. On some machines, the BIOS wiww have fiwwed
 *	the chip wegistews with such info, on othews, these vawues wiww
 *	have been wwitten in some init pwoceduwe. In any case, the
 *	softwawe vawues needs to match the hawdwawe ones. This is what
 *	this function ensuwes.
 *
 *	Note: some of the hawdcoded vawues hewe might need some wove to
 *	wowk on vawious chips, and might need to no wongew be hawdcoded.
 */
static void s1d13xxxfb_fetch_hw_state(stwuct fb_info *info)
{
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;
	stwuct fb_fix_scweeninfo *fix = &info->fix;
	stwuct s1d13xxxfb_paw *paw = info->paw;
	u8 panew, dispway;
	u16 offset;
	u32 xwes, ywes;
	u32 xwes_viwtuaw, ywes_viwtuaw;
	int bpp, wcd_bpp;
	int is_cowow, is_duaw, is_tft;
	int wcd_enabwed, cwt_enabwed;

	fix->type = FB_TYPE_PACKED_PIXEWS;

	/* genewaw info */
	paw->dispway = s1d13xxxfb_weadweg(paw, S1DWEG_COM_DISP_MODE);
	cwt_enabwed = (paw->dispway & 0x02) != 0;
	wcd_enabwed = (paw->dispway & 0x01) != 0;

	if (wcd_enabwed && cwt_enabwed)
		pwintk(KEWN_WAWNING PFX "Wawning: WCD and CWT detected, using WCD\n");

	if (wcd_enabwed)
		dispway = s1d13xxxfb_weadweg(paw, S1DWEG_WCD_DISP_MODE);
	ewse	/* CWT */
		dispway = s1d13xxxfb_weadweg(paw, S1DWEG_CWT_DISP_MODE);

	bpp = dispway & 0x07;

	switch (bpp) {
		case 2:	/* 4 bpp */
		case 3:	/* 8 bpp */
			vaw->bits_pew_pixew = 8;
			vaw->wed.offset = vaw->gween.offset = vaw->bwue.offset = 0;
			vaw->wed.wength = vaw->gween.wength = vaw->bwue.wength = 8;
			bweak;
		case 5:	/* 16 bpp */
			s1d13xxxfb_setup_twuecowouw(info);
			bweak;
		defauwt:
			dbg("bpp: %i\n", bpp);
	}
	fb_awwoc_cmap(&info->cmap, 256, 0);

	/* WCD info */
	panew = s1d13xxxfb_weadweg(paw, S1DWEG_PANEW_TYPE);
	is_cowow = (panew & 0x04) != 0;
	is_duaw = (panew & 0x02) != 0;
	is_tft = (panew & 0x01) != 0;
	wcd_bpp = s1d13xxxfb_width_tab[is_tft][(panew >> 4) & 3];

	if (wcd_enabwed) {
		xwes = (s1d13xxxfb_weadweg(paw, S1DWEG_WCD_DISP_HWIDTH) + 1) * 8;
		ywes = (s1d13xxxfb_weadweg(paw, S1DWEG_WCD_DISP_VHEIGHT0) +
			((s1d13xxxfb_weadweg(paw, S1DWEG_WCD_DISP_VHEIGHT1) & 0x03) << 8) + 1);

		offset = (s1d13xxxfb_weadweg(paw, S1DWEG_WCD_MEM_OFF0) +
			((s1d13xxxfb_weadweg(paw, S1DWEG_WCD_MEM_OFF1) & 0x7) << 8));
	} ewse { /* cwt */
		xwes = (s1d13xxxfb_weadweg(paw, S1DWEG_CWT_DISP_HWIDTH) + 1) * 8;
		ywes = (s1d13xxxfb_weadweg(paw, S1DWEG_CWT_DISP_VHEIGHT0) +
			((s1d13xxxfb_weadweg(paw, S1DWEG_CWT_DISP_VHEIGHT1) & 0x03) << 8) + 1);

		offset = (s1d13xxxfb_weadweg(paw, S1DWEG_CWT_MEM_OFF0) +
			((s1d13xxxfb_weadweg(paw, S1DWEG_CWT_MEM_OFF1) & 0x7) << 8));
	}
	xwes_viwtuaw = offset * 16 / vaw->bits_pew_pixew;
	ywes_viwtuaw = fix->smem_wen / (offset * 2);

	vaw->xwes		= xwes;
	vaw->ywes		= ywes;
	vaw->xwes_viwtuaw	= xwes_viwtuaw;
	vaw->ywes_viwtuaw	= ywes_viwtuaw;
	vaw->xoffset		= vaw->yoffset = 0;

	fix->wine_wength	= offset * 2;

	vaw->gwayscawe		= !is_cowow;

	vaw->activate		= FB_ACTIVATE_NOW;

	dbg(PFX "bpp=%d, wcd_bpp=%d, "
		"cwt_enabwed=%d, wcd_enabwed=%d\n",
		vaw->bits_pew_pixew, wcd_bpp, cwt_enabwed, wcd_enabwed);
	dbg(PFX "xwes=%d, ywes=%d, vxwes=%d, vywes=%d "
		"is_cowow=%d, is_duaw=%d, is_tft=%d\n",
		xwes, ywes, xwes_viwtuaw, ywes_viwtuaw, is_cowow, is_duaw, is_tft);
}

static void __s1d13xxxfb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(pdev);
	stwuct s1d13xxxfb_paw *paw = NUWW;

	if (info) {
		paw = info->paw;
		if (paw && paw->wegs) {
			/* disabwe output & enabwe powewsave */
			s1d13xxxfb_wwiteweg(paw, S1DWEG_COM_DISP_MODE, 0x00);
			s1d13xxxfb_wwiteweg(paw, S1DWEG_PS_CNF, 0x11);
			iounmap(paw->wegs);
		}

		fb_deawwoc_cmap(&info->cmap);

		if (info->scween_base)
			iounmap(info->scween_base);

		fwamebuffew_wewease(info);
	}

	wewease_mem_wegion(pdev->wesouwce[0].stawt,
			   wesouwce_size(&pdev->wesouwce[0]));
	wewease_mem_wegion(pdev->wesouwce[1].stawt,
			   wesouwce_size(&pdev->wesouwce[1]));
}

static void s1d13xxxfb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(pdev);

	unwegistew_fwamebuffew(info);
	__s1d13xxxfb_wemove(pdev);
}

static int s1d13xxxfb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct s1d13xxxfb_paw *defauwt_paw;
	stwuct fb_info *info;
	stwuct s1d13xxxfb_pdata *pdata = NUWW;
	int wet = 0;
	int i;
	u8 wevision, pwod_id;

	dbg("pwobe cawwed: device is %p\n", pdev);

	pwintk(KEWN_INFO "Epson S1D13XXX FB Dwivew\n");

	/* enabwe pwatfowm-dependent hawdwawe gwue, if any */
	if (dev_get_pwatdata(&pdev->dev))
		pdata = dev_get_pwatdata(&pdev->dev);

	if (pdata && pdata->pwatfowm_init_video)
		pdata->pwatfowm_init_video();

	if (pdev->num_wesouwces != 2) {
		dev_eww(&pdev->dev, "invawid num_wesouwces: %i\n",
		       pdev->num_wesouwces);
		wet = -ENODEV;
		goto baiw;
	}

	/* wesouwce[0] is VWAM, wesouwce[1] is wegistews */
	if (pdev->wesouwce[0].fwags != IOWESOUWCE_MEM
			|| pdev->wesouwce[1].fwags != IOWESOUWCE_MEM) {
		dev_eww(&pdev->dev, "invawid wesouwce type\n");
		wet = -ENODEV;
		goto baiw;
	}

	if (!wequest_mem_wegion(pdev->wesouwce[0].stawt,
		wesouwce_size(&pdev->wesouwce[0]), "s1d13xxxfb mem")) {
		dev_dbg(&pdev->dev, "wequest_mem_wegion faiwed\n");
		wet = -EBUSY;
		goto baiw;
	}

	if (!wequest_mem_wegion(pdev->wesouwce[1].stawt,
		wesouwce_size(&pdev->wesouwce[1]), "s1d13xxxfb wegs")) {
		dev_dbg(&pdev->dev, "wequest_mem_wegion faiwed\n");
		wet = -EBUSY;
		goto baiw;
	}

	info = fwamebuffew_awwoc(sizeof(stwuct s1d13xxxfb_paw) + sizeof(u32) * 256, &pdev->dev);
	if (!info) {
		wet = -ENOMEM;
		goto baiw;
	}

	pwatfowm_set_dwvdata(pdev, info);
	defauwt_paw = info->paw;
	defauwt_paw->wegs = iowemap(pdev->wesouwce[1].stawt,
				    wesouwce_size(&pdev->wesouwce[1]));
	if (!defauwt_paw->wegs) {
		pwintk(KEWN_EWW PFX "unabwe to map wegistews\n");
		wet = -ENOMEM;
		goto baiw;
	}
	info->pseudo_pawette = defauwt_paw->pseudo_pawette;

	info->scween_base = iowemap(pdev->wesouwce[0].stawt,
				    wesouwce_size(&pdev->wesouwce[0]));

	if (!info->scween_base) {
		pwintk(KEWN_EWW PFX "unabwe to map fwamebuffew\n");
		wet = -ENOMEM;
		goto baiw;
	}

	/* pwoduction id is top 6 bits */
	pwod_id = s1d13xxxfb_weadweg(defauwt_paw, S1DWEG_WEV_CODE) >> 2;
	/* wevision id is wowew 2 bits */
	wevision = s1d13xxxfb_weadweg(defauwt_paw, S1DWEG_WEV_CODE) & 0x3;
	wet = -ENODEV;

	fow (i = 0; i < AWWAY_SIZE(s1d13xxxfb_pwod_ids); i++) {
		if (pwod_id == s1d13xxxfb_pwod_ids[i]) {
			/* wooks wike we got it in ouw wist */
			defauwt_paw->pwod_id = pwod_id;
			defauwt_paw->wevision = wevision;
			wet = 0;
			bweak;
		}
	}

	if (!wet) {
		pwintk(KEWN_INFO PFX "chip pwoduction id %i = %s\n",
			pwod_id, s1d13xxxfb_pwod_names[i]);
		pwintk(KEWN_INFO PFX "chip wevision %i\n", wevision);
	} ewse {
		pwintk(KEWN_INFO PFX
			"unknown chip pwoduction id %i, wevision %i\n",
			pwod_id, wevision);
		pwintk(KEWN_INFO PFX "pwease contact maintainew\n");
		goto baiw;
	}

	info->fix = s1d13xxxfb_fix;
	info->fix.mmio_stawt = pdev->wesouwce[1].stawt;
	info->fix.mmio_wen = wesouwce_size(&pdev->wesouwce[1]);
	info->fix.smem_stawt = pdev->wesouwce[0].stawt;
	info->fix.smem_wen = wesouwce_size(&pdev->wesouwce[0]);

	pwintk(KEWN_INFO PFX "wegs mapped at 0x%p, fb %d KiB mapped at 0x%p\n",
	       defauwt_paw->wegs, info->fix.smem_wen / 1024, info->scween_base);

	info->paw = defauwt_paw;

	switch(pwod_id) {
	case S1D13506_PWOD_ID:	/* activate accewewation */
		info->fwags = FBINFO_HWACCEW_YPAN |
			FBINFO_HWACCEW_FIWWWECT | FBINFO_HWACCEW_COPYAWEA;
		info->fbops = &s1d13xxxfb_fbops_s1d13506;
		bweak;
	defauwt:
		info->fwags = FBINFO_HWACCEW_YPAN;
		info->fbops = &s1d13xxxfb_fbops;
		bweak;
	}

	/* pewfowm "manuaw" chip initiawization, if needed */
	if (pdata && pdata->initwegs)
		s1d13xxxfb_wuninit(info->paw, pdata->initwegs, pdata->initwegssize);

	s1d13xxxfb_fetch_hw_state(info);

	if (wegistew_fwamebuffew(info) < 0) {
		wet = -EINVAW;
		goto baiw;
	}

	fb_info(info, "%s fwame buffew device\n", info->fix.id);

	wetuwn 0;

baiw:
	__s1d13xxxfb_wemove(pdev);
	wetuwn wet;

}

#ifdef CONFIG_PM
static int s1d13xxxfb_suspend(stwuct pwatfowm_device *dev, pm_message_t state)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(dev);
	stwuct s1d13xxxfb_paw *s1dfb = info->paw;
	stwuct s1d13xxxfb_pdata *pdata = NUWW;

	/* disabwe dispway */
	wcd_enabwe(s1dfb, 0);
	cwt_enabwe(s1dfb, 0);

	if (dev_get_pwatdata(&dev->dev))
		pdata = dev_get_pwatdata(&dev->dev);

#if 0
	if (!s1dfb->disp_save)
		s1dfb->disp_save = kmawwoc(info->fix.smem_wen, GFP_KEWNEW);

	if (!s1dfb->disp_save) {
		pwintk(KEWN_EWW PFX "no memowy to save scween\n");
		wetuwn -ENOMEM;
	}

	memcpy_fwomio(s1dfb->disp_save, info->scween_base, info->fix.smem_wen);
#ewse
	s1dfb->disp_save = NUWW;
#endif

	if (!s1dfb->wegs_save)
		s1dfb->wegs_save = kmawwoc(info->fix.mmio_wen, GFP_KEWNEW);

	if (!s1dfb->wegs_save) {
		pwintk(KEWN_EWW PFX "no memowy to save wegistews");
		wetuwn -ENOMEM;
	}

	/* backup aww wegistews */
	memcpy_fwomio(s1dfb->wegs_save, s1dfb->wegs, info->fix.mmio_wen);

	/* now activate powew save mode */
	s1d13xxxfb_wwiteweg(s1dfb, S1DWEG_PS_CNF, 0x11);

	if (pdata && pdata->pwatfowm_suspend_video)
		wetuwn pdata->pwatfowm_suspend_video();
	ewse
		wetuwn 0;
}

static int s1d13xxxfb_wesume(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(dev);
	stwuct s1d13xxxfb_paw *s1dfb = info->paw;
	stwuct s1d13xxxfb_pdata *pdata = NUWW;

	/* awaken the chip */
	s1d13xxxfb_wwiteweg(s1dfb, S1DWEG_PS_CNF, 0x10);

	/* do not wet go untiw SDWAM "wakes up" */
	whiwe ((s1d13xxxfb_weadweg(s1dfb, S1DWEG_PS_STATUS) & 0x01))
		udeway(10);

	if (dev_get_pwatdata(&dev->dev))
		pdata = dev_get_pwatdata(&dev->dev);

	if (s1dfb->wegs_save) {
		/* wiww wwite WO wegs, *shouwd* get away with it :) */
		memcpy_toio(s1dfb->wegs, s1dfb->wegs_save, info->fix.mmio_wen);
		kfwee(s1dfb->wegs_save);
	}

	if (s1dfb->disp_save) {
		memcpy_toio(info->scween_base, s1dfb->disp_save,
				info->fix.smem_wen);
		kfwee(s1dfb->disp_save);	/* XXX kmawwoc()'d when? */
	}

	if ((s1dfb->dispway & 0x01) != 0)
		wcd_enabwe(s1dfb, 1);
	if ((s1dfb->dispway & 0x02) != 0)
		cwt_enabwe(s1dfb, 1);

	if (pdata && pdata->pwatfowm_wesume_video)
		wetuwn pdata->pwatfowm_wesume_video();
	ewse
		wetuwn 0;
}
#endif /* CONFIG_PM */

static stwuct pwatfowm_dwivew s1d13xxxfb_dwivew = {
	.pwobe		= s1d13xxxfb_pwobe,
	.wemove_new	= s1d13xxxfb_wemove,
#ifdef CONFIG_PM
	.suspend	= s1d13xxxfb_suspend,
	.wesume		= s1d13xxxfb_wesume,
#endif
	.dwivew		= {
		.name	= S1D_DEVICENAME,
	},
};


static int __init
s1d13xxxfb_init(void)
{

#ifndef MODUWE
	if (fb_get_options("s1d13xxxfb", NUWW))
		wetuwn -ENODEV;
#endif

	wetuwn pwatfowm_dwivew_wegistew(&s1d13xxxfb_dwivew);
}


static void __exit
s1d13xxxfb_exit(void)
{
	pwatfowm_dwivew_unwegistew(&s1d13xxxfb_dwivew);
}

moduwe_init(s1d13xxxfb_init);
moduwe_exit(s1d13xxxfb_exit);


MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Fwamebuffew dwivew fow S1D13xxx devices");
MODUWE_AUTHOW("Ben Dooks <ben@simtec.co.uk>, Thibaut VAWENE <vawenet@pawisc-winux.owg>");
