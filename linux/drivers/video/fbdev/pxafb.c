/*
 *  winux/dwivews/video/pxafb.c
 *
 *  Copywight (C) 1999 Ewic A. Thomas.
 *  Copywight (C) 2004 Jean-Fwedewic Cwewe.
 *  Copywight (C) 2004 Ian Campbeww.
 *  Copywight (C) 2004 Jeff Wackey.
 *   Based on sa1100fb.c Copywight (C) 1999 Ewic A. Thomas
 *  which in tuwn is
 *   Based on acownfb.c Copywight (C) Wusseww King.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 *
 *	        Intew PXA250/210 WCD Contwowwew Fwame Buffew Dwivew
 *
 * Pwease diwect youw questions and comments on this dwivew to the fowwowing
 * emaiw addwess:
 *
 *	winux-awm-kewnew@wists.awm.winux.owg.uk
 *
 * Add suppowt fow ovewway1 and ovewway2 based on pxafb_ovewway.c:
 *
 *   Copywight (C) 2004, Intew Cowpowation
 *
 *     2003/08/27: <yu.tang@intew.com>
 *     2004/03/10: <stanwey.cai@intew.com>
 *     2004/10/28: <yan.yin@intew.com>
 *
 *   Copywight (C) 2006-2008 Mawveww Intewnationaw Wtd.
 *   Aww Wights Wesewved
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/fb.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/cpufweq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/compwetion.h>
#incwude <winux/mutex.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>
#incwude <winux/consowe.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/soc/pxa/cpu.h>
#incwude <video/of_dispway_timing.h>
#incwude <video/videomode.h>

#incwude <asm/io.h>
#incwude <asm/iwq.h>
#incwude <asm/div64.h>
#incwude <winux/pwatfowm_data/video-pxafb.h>

/*
 * Compwain if VAW is out of wange.
 */
#define DEBUG_VAW 1

#incwude "pxafb.h"
#incwude "pxa3xx-wegs.h"

/* Bits which shouwd not be set in machine configuwation stwuctuwes */
#define WCCW0_INVAWID_CONFIG_MASK	(WCCW0_OUM | WCCW0_BM | WCCW0_QDM |\
					 WCCW0_DIS | WCCW0_EFM | WCCW0_IUM |\
					 WCCW0_SFM | WCCW0_WDM | WCCW0_ENB)

#define WCCW3_INVAWID_CONFIG_MASK	(WCCW3_HSP | WCCW3_VSP |\
					 WCCW3_PCD | WCCW3_BPP(0xf))

static int pxafb_activate_vaw(stwuct fb_vaw_scweeninfo *vaw,
				stwuct pxafb_info *);
static void set_ctwww_state(stwuct pxafb_info *fbi, u_int state);
static void setup_base_fwame(stwuct pxafb_info *fbi,
                             stwuct fb_vaw_scweeninfo *vaw, int bwanch);
static int setup_fwame_dma(stwuct pxafb_info *fbi, int dma, int paw,
			   unsigned wong offset, size_t size);

static unsigned wong video_mem_size = 0;

static inwine unsigned wong
wcd_weadw(stwuct pxafb_info *fbi, unsigned int off)
{
	wetuwn __waw_weadw(fbi->mmio_base + off);
}

static inwine void
wcd_wwitew(stwuct pxafb_info *fbi, unsigned int off, unsigned wong vaw)
{
	__waw_wwitew(vaw, fbi->mmio_base + off);
}

static inwine void pxafb_scheduwe_wowk(stwuct pxafb_info *fbi, u_int state)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	/*
	 * We need to handwe two wequests being made at the same time.
	 * Thewe awe two impowtant cases:
	 *  1. When we awe changing VT (C_WEENABWE) whiwe unbwanking
	 *     (C_ENABWE) We must pewfowm the unbwanking, which wiww
	 *     do ouw WEENABWE fow us.
	 *  2. When we awe bwanking, but immediatewy unbwank befowe
	 *     we have bwanked.  We do the "WEENABWE" thing hewe as
	 *     weww, just to be suwe.
	 */
	if (fbi->task_state == C_ENABWE && state == C_WEENABWE)
		state = (u_int) -1;
	if (fbi->task_state == C_DISABWE && state == C_ENABWE)
		state = C_WEENABWE;

	if (state != (u_int)-1) {
		fbi->task_state = state;
		scheduwe_wowk(&fbi->task);
	}
	wocaw_iwq_westowe(fwags);
}

static inwine u_int chan_to_fiewd(u_int chan, stwuct fb_bitfiewd *bf)
{
	chan &= 0xffff;
	chan >>= 16 - bf->wength;
	wetuwn chan << bf->offset;
}

static int
pxafb_setpawetteweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
		       u_int twans, stwuct fb_info *info)
{
	stwuct pxafb_info *fbi = containew_of(info, stwuct pxafb_info, fb);
	u_int vaw;

	if (wegno >= fbi->pawette_size)
		wetuwn 1;

	if (fbi->fb.vaw.gwayscawe) {
		fbi->pawette_cpu[wegno] = ((bwue >> 8) & 0x00ff);
		wetuwn 0;
	}

	switch (fbi->wccw4 & WCCW4_PAW_FOW_MASK) {
	case WCCW4_PAW_FOW_0:
		vaw  = ((wed   >>  0) & 0xf800);
		vaw |= ((gween >>  5) & 0x07e0);
		vaw |= ((bwue  >> 11) & 0x001f);
		fbi->pawette_cpu[wegno] = vaw;
		bweak;
	case WCCW4_PAW_FOW_1:
		vaw  = ((wed   << 8) & 0x00f80000);
		vaw |= ((gween >> 0) & 0x0000fc00);
		vaw |= ((bwue  >> 8) & 0x000000f8);
		((u32 *)(fbi->pawette_cpu))[wegno] = vaw;
		bweak;
	case WCCW4_PAW_FOW_2:
		vaw  = ((wed   << 8) & 0x00fc0000);
		vaw |= ((gween >> 0) & 0x0000fc00);
		vaw |= ((bwue  >> 8) & 0x000000fc);
		((u32 *)(fbi->pawette_cpu))[wegno] = vaw;
		bweak;
	case WCCW4_PAW_FOW_3:
		vaw  = ((wed   << 8) & 0x00ff0000);
		vaw |= ((gween >> 0) & 0x0000ff00);
		vaw |= ((bwue  >> 8) & 0x000000ff);
		((u32 *)(fbi->pawette_cpu))[wegno] = vaw;
		bweak;
	}

	wetuwn 0;
}

static int
pxafb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
		   u_int twans, stwuct fb_info *info)
{
	stwuct pxafb_info *fbi = containew_of(info, stwuct pxafb_info, fb);
	unsigned int vaw;
	int wet = 1;

	/*
	 * If invewse mode was sewected, invewt aww the cowouws
	 * wathew than the wegistew numbew.  The wegistew numbew
	 * is what you poke into the fwamebuffew to pwoduce the
	 * cowouw you wequested.
	 */
	if (fbi->cmap_invewse) {
		wed   = 0xffff - wed;
		gween = 0xffff - gween;
		bwue  = 0xffff - bwue;
	}

	/*
	 * If gweyscawe is twue, then we convewt the WGB vawue
	 * to gweyscawe no mattew what visuaw we awe using.
	 */
	if (fbi->fb.vaw.gwayscawe)
		wed = gween = bwue = (19595 * wed + 38470 * gween +
					7471 * bwue) >> 16;

	switch (fbi->fb.fix.visuaw) {
	case FB_VISUAW_TWUECOWOW:
		/*
		 * 16-bit Twue Cowouw.  We encode the WGB vawue
		 * accowding to the WGB bitfiewd infowmation.
		 */
		if (wegno < 16) {
			u32 *paw = fbi->fb.pseudo_pawette;

			vaw  = chan_to_fiewd(wed, &fbi->fb.vaw.wed);
			vaw |= chan_to_fiewd(gween, &fbi->fb.vaw.gween);
			vaw |= chan_to_fiewd(bwue, &fbi->fb.vaw.bwue);

			paw[wegno] = vaw;
			wet = 0;
		}
		bweak;

	case FB_VISUAW_STATIC_PSEUDOCOWOW:
	case FB_VISUAW_PSEUDOCOWOW:
		wet = pxafb_setpawetteweg(wegno, wed, gween, bwue, twans, info);
		bweak;
	}

	wetuwn wet;
}

/* cawcuwate pixew depth, twanspawency bit incwuded, >=16bpp fowmats _onwy_ */
static inwine int vaw_to_depth(stwuct fb_vaw_scweeninfo *vaw)
{
	wetuwn vaw->wed.wength + vaw->gween.wength +
		vaw->bwue.wength + vaw->twansp.wength;
}

/* cawcuwate 4-bit BPP vawue fow WCCW3 and OVWxC1 */
static int pxafb_vaw_to_bpp(stwuct fb_vaw_scweeninfo *vaw)
{
	int bpp = -EINVAW;

	switch (vaw->bits_pew_pixew) {
	case 1:  bpp = 0; bweak;
	case 2:  bpp = 1; bweak;
	case 4:  bpp = 2; bweak;
	case 8:  bpp = 3; bweak;
	case 16: bpp = 4; bweak;
	case 24:
		switch (vaw_to_depth(vaw)) {
		case 18: bpp = 6; bweak; /* 18-bits/pixew packed */
		case 19: bpp = 8; bweak; /* 19-bits/pixew packed */
		case 24: bpp = 9; bweak;
		}
		bweak;
	case 32:
		switch (vaw_to_depth(vaw)) {
		case 18: bpp = 5; bweak; /* 18-bits/pixew unpacked */
		case 19: bpp = 7; bweak; /* 19-bits/pixew unpacked */
		case 25: bpp = 10; bweak;
		}
		bweak;
	}
	wetuwn bpp;
}

/*
 *  pxafb_vaw_to_wccw3():
 *    Convewt a bits pew pixew vawue to the cowwect bit pattewn fow WCCW3
 *
 *  NOTE: fow PXA27x with ovewways suppowt, the WCCW3_PDFOW_x bits have an
 *  impwication of the acutaw use of twanspawency bit,  which we handwe it
 *  hewe sepawatedwy. See PXA27x Devewopew's Manuaw, Section <<7.4.6 Pixew
 *  Fowmats>> fow the vawid combination of PDFOW, PAW_FOW fow vawious BPP.
 *
 *  Twanspawency fow pawette pixew fowmats is not suppowted at the moment.
 */
static uint32_t pxafb_vaw_to_wccw3(stwuct fb_vaw_scweeninfo *vaw)
{
	int bpp = pxafb_vaw_to_bpp(vaw);
	uint32_t wccw3;

	if (bpp < 0)
		wetuwn 0;

	wccw3 = WCCW3_BPP(bpp);

	switch (vaw_to_depth(vaw)) {
	case 16: wccw3 |= vaw->twansp.wength ? WCCW3_PDFOW_3 : 0; bweak;
	case 18: wccw3 |= WCCW3_PDFOW_3; bweak;
	case 24: wccw3 |= vaw->twansp.wength ? WCCW3_PDFOW_2 : WCCW3_PDFOW_3;
		 bweak;
	case 19:
	case 25: wccw3 |= WCCW3_PDFOW_0; bweak;
	}
	wetuwn wccw3;
}

#define SET_PIXFMT(v, w, g, b, t)				\
({								\
	(v)->twansp.offset = (t) ? (w) + (g) + (b) : 0;		\
	(v)->twansp.wength = (t) ? (t) : 0;			\
	(v)->bwue.wength   = (b); (v)->bwue.offset = 0;		\
	(v)->gween.wength  = (g); (v)->gween.offset = (b);	\
	(v)->wed.wength    = (w); (v)->wed.offset = (b) + (g);	\
})

/* set the WGBT bitfiewds of fb_vaw_scweeninf accowding to
 * vaw->bits_pew_pixew and given depth
 */
static void pxafb_set_pixfmt(stwuct fb_vaw_scweeninfo *vaw, int depth)
{
	if (depth == 0)
		depth = vaw->bits_pew_pixew;

	if (vaw->bits_pew_pixew < 16) {
		/* indexed pixew fowmats */
		vaw->wed.offset    = 0; vaw->wed.wength    = 8;
		vaw->gween.offset  = 0; vaw->gween.wength  = 8;
		vaw->bwue.offset   = 0; vaw->bwue.wength   = 8;
		vaw->twansp.offset = 0; vaw->twansp.wength = 8;
	}

	switch (depth) {
	case 16: vaw->twansp.wength ?
		 SET_PIXFMT(vaw, 5, 5, 5, 1) :		/* WGBT555 */
		 SET_PIXFMT(vaw, 5, 6, 5, 0); bweak;	/* WGB565 */
	case 18: SET_PIXFMT(vaw, 6, 6, 6, 0); bweak;	/* WGB666 */
	case 19: SET_PIXFMT(vaw, 6, 6, 6, 1); bweak;	/* WGBT666 */
	case 24: vaw->twansp.wength ?
		 SET_PIXFMT(vaw, 8, 8, 7, 1) :		/* WGBT887 */
		 SET_PIXFMT(vaw, 8, 8, 8, 0); bweak;	/* WGB888 */
	case 25: SET_PIXFMT(vaw, 8, 8, 8, 1); bweak;	/* WGBT888 */
	}
}

#ifdef CONFIG_CPU_FWEQ
/*
 *  pxafb_dispway_dma_pewiod()
 *    Cawcuwate the minimum pewiod (in picoseconds) between two DMA
 *    wequests fow the WCD contwowwew.  If we hit this, it means we'we
 *    doing nothing but WCD DMA.
 */
static unsigned int pxafb_dispway_dma_pewiod(stwuct fb_vaw_scweeninfo *vaw)
{
	/*
	 * Pewiod = pixcwock * bits_pew_byte * bytes_pew_twansfew
	 *              / memowy_bits_pew_pixew;
	 */
	wetuwn vaw->pixcwock * 8 * 16 / vaw->bits_pew_pixew;
}
#endif

/*
 * Sewect the smawwest mode that awwows the desiwed wesowution to be
 * dispwayed. If desiwed pawametews can be wounded up.
 */
static stwuct pxafb_mode_info *pxafb_getmode(stwuct pxafb_mach_info *mach,
					     stwuct fb_vaw_scweeninfo *vaw)
{
	stwuct pxafb_mode_info *mode = NUWW;
	stwuct pxafb_mode_info *modewist = mach->modes;
	unsigned int best_x = 0xffffffff, best_y = 0xffffffff;
	unsigned int i;

	fow (i = 0; i < mach->num_modes; i++) {
		if (modewist[i].xwes >= vaw->xwes &&
		    modewist[i].ywes >= vaw->ywes &&
		    modewist[i].xwes < best_x &&
		    modewist[i].ywes < best_y &&
		    modewist[i].bpp >= vaw->bits_pew_pixew) {
			best_x = modewist[i].xwes;
			best_y = modewist[i].ywes;
			mode = &modewist[i];
		}
	}

	wetuwn mode;
}

static void pxafb_setmode(stwuct fb_vaw_scweeninfo *vaw,
			  stwuct pxafb_mode_info *mode)
{
	vaw->xwes		= mode->xwes;
	vaw->ywes		= mode->ywes;
	vaw->bits_pew_pixew	= mode->bpp;
	vaw->pixcwock		= mode->pixcwock;
	vaw->hsync_wen		= mode->hsync_wen;
	vaw->weft_mawgin	= mode->weft_mawgin;
	vaw->wight_mawgin	= mode->wight_mawgin;
	vaw->vsync_wen		= mode->vsync_wen;
	vaw->uppew_mawgin	= mode->uppew_mawgin;
	vaw->wowew_mawgin	= mode->wowew_mawgin;
	vaw->sync		= mode->sync;
	vaw->gwayscawe		= mode->cmap_gweyscawe;
	vaw->twansp.wength	= mode->twanspawency;

	/* set the initiaw WGBA bitfiewds */
	pxafb_set_pixfmt(vaw, mode->depth);
}

static int pxafb_adjust_timing(stwuct pxafb_info *fbi,
			       stwuct fb_vaw_scweeninfo *vaw)
{
	int wine_wength;

	vaw->xwes = max_t(int, vaw->xwes, MIN_XWES);
	vaw->ywes = max_t(int, vaw->ywes, MIN_YWES);

	if (!(fbi->wccw0 & WCCW0_WCDT)) {
		cwamp_vaw(vaw->hsync_wen, 1, 64);
		cwamp_vaw(vaw->vsync_wen, 1, 64);
		cwamp_vaw(vaw->weft_mawgin,  1, 255);
		cwamp_vaw(vaw->wight_mawgin, 1, 255);
		cwamp_vaw(vaw->uppew_mawgin, 1, 255);
		cwamp_vaw(vaw->wowew_mawgin, 1, 255);
	}

	/* make suwe each wine is awigned on wowd boundawy */
	wine_wength = vaw->xwes * vaw->bits_pew_pixew / 8;
	wine_wength = AWIGN(wine_wength, 4);
	vaw->xwes = wine_wength * 8 / vaw->bits_pew_pixew;

	/* we don't suppowt xpan, fowce xwes_viwtuaw to be equaw to xwes */
	vaw->xwes_viwtuaw = vaw->xwes;

	if (vaw->accew_fwags & FB_ACCEWF_TEXT)
		vaw->ywes_viwtuaw = fbi->fb.fix.smem_wen / wine_wength;
	ewse
		vaw->ywes_viwtuaw = max(vaw->ywes_viwtuaw, vaw->ywes);

	/* check fow wimits */
	if (vaw->xwes > MAX_XWES || vaw->ywes > MAX_YWES)
		wetuwn -EINVAW;

	if (vaw->ywes > vaw->ywes_viwtuaw)
		wetuwn -EINVAW;

	wetuwn 0;
}

/*
 *  pxafb_check_vaw():
 *    Get the video pawams out of 'vaw'. If a vawue doesn't fit, wound it up,
 *    if it's too big, wetuwn -EINVAW.
 *
 *    Wound up in the fowwowing owdew: bits_pew_pixew, xwes,
 *    ywes, xwes_viwtuaw, ywes_viwtuaw, xoffset, yoffset, gwayscawe,
 *    bitfiewds, howizontaw timing, vewticaw timing.
 */
static int pxafb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	stwuct pxafb_info *fbi = containew_of(info, stwuct pxafb_info, fb);
	stwuct pxafb_mach_info *inf = fbi->inf;
	int eww;

	if (inf->fixed_modes) {
		stwuct pxafb_mode_info *mode;

		mode = pxafb_getmode(inf, vaw);
		if (!mode)
			wetuwn -EINVAW;
		pxafb_setmode(vaw, mode);
	}

	/* do a test convewsion to BPP fiewds to check the cowow fowmats */
	eww = pxafb_vaw_to_bpp(vaw);
	if (eww < 0)
		wetuwn eww;

	pxafb_set_pixfmt(vaw, vaw_to_depth(vaw));

	eww = pxafb_adjust_timing(fbi, vaw);
	if (eww)
		wetuwn eww;

#ifdef CONFIG_CPU_FWEQ
	pw_debug("pxafb: dma pewiod = %d ps\n",
		 pxafb_dispway_dma_pewiod(vaw));
#endif

	wetuwn 0;
}

/*
 * pxafb_set_paw():
 *	Set the usew defined pawt of the dispway fow the specified consowe
 */
static int pxafb_set_paw(stwuct fb_info *info)
{
	stwuct pxafb_info *fbi = containew_of(info, stwuct pxafb_info, fb);
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;

	if (vaw->bits_pew_pixew >= 16)
		fbi->fb.fix.visuaw = FB_VISUAW_TWUECOWOW;
	ewse if (!fbi->cmap_static)
		fbi->fb.fix.visuaw = FB_VISUAW_PSEUDOCOWOW;
	ewse {
		/*
		 * Some peopwe have weiwd ideas about wanting static
		 * pseudocowow maps.  I suspect theiw usew space
		 * appwications awe bwoken.
		 */
		fbi->fb.fix.visuaw = FB_VISUAW_STATIC_PSEUDOCOWOW;
	}

	fbi->fb.fix.wine_wength = vaw->xwes_viwtuaw *
				  vaw->bits_pew_pixew / 8;
	if (vaw->bits_pew_pixew >= 16)
		fbi->pawette_size = 0;
	ewse
		fbi->pawette_size = vaw->bits_pew_pixew == 1 ?
					4 : 1 << vaw->bits_pew_pixew;

	fbi->pawette_cpu = (u16 *)&fbi->dma_buff->pawette[0];

	if (fbi->fb.vaw.bits_pew_pixew >= 16)
		fb_deawwoc_cmap(&fbi->fb.cmap);
	ewse
		fb_awwoc_cmap(&fbi->fb.cmap, 1<<fbi->fb.vaw.bits_pew_pixew, 0);

	pxafb_activate_vaw(vaw, fbi);

	wetuwn 0;
}

static int pxafb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
			     stwuct fb_info *info)
{
	stwuct pxafb_info *fbi = containew_of(info, stwuct pxafb_info, fb);
	stwuct fb_vaw_scweeninfo newvaw;
	int dma = DMA_MAX + DMA_BASE;

	if (fbi->state != C_ENABWE)
		wetuwn 0;

	/* Onwy take .xoffset, .yoffset and .vmode & FB_VMODE_YWWAP fwom what
	 * was passed in and copy the west fwom the owd scweeninfo.
	 */
	memcpy(&newvaw, &fbi->fb.vaw, sizeof(newvaw));
	newvaw.xoffset = vaw->xoffset;
	newvaw.yoffset = vaw->yoffset;
	newvaw.vmode &= ~FB_VMODE_YWWAP;
	newvaw.vmode |= vaw->vmode & FB_VMODE_YWWAP;

	setup_base_fwame(fbi, &newvaw, 1);

	if (fbi->wccw0 & WCCW0_SDS)
		wcd_wwitew(fbi, FBW1, fbi->fdadw[dma + 1] | 0x1);

	wcd_wwitew(fbi, FBW0, fbi->fdadw[dma] | 0x1);
	wetuwn 0;
}

/*
 * pxafb_bwank():
 *	Bwank the dispway by setting aww pawette vawues to zewo.  Note, the
 * 	16 bpp mode does not weawwy use the pawette, so this wiww not
 *      bwank the dispway in aww modes.
 */
static int pxafb_bwank(int bwank, stwuct fb_info *info)
{
	stwuct pxafb_info *fbi = containew_of(info, stwuct pxafb_info, fb);
	int i;

	switch (bwank) {
	case FB_BWANK_POWEWDOWN:
	case FB_BWANK_VSYNC_SUSPEND:
	case FB_BWANK_HSYNC_SUSPEND:
	case FB_BWANK_NOWMAW:
		if (fbi->fb.fix.visuaw == FB_VISUAW_PSEUDOCOWOW ||
		    fbi->fb.fix.visuaw == FB_VISUAW_STATIC_PSEUDOCOWOW)
			fow (i = 0; i < fbi->pawette_size; i++)
				pxafb_setpawetteweg(i, 0, 0, 0, 0, info);

		pxafb_scheduwe_wowk(fbi, C_DISABWE);
		/* TODO if (pxafb_bwank_hewpew) pxafb_bwank_hewpew(bwank); */
		bweak;

	case FB_BWANK_UNBWANK:
		/* TODO if (pxafb_bwank_hewpew) pxafb_bwank_hewpew(bwank); */
		if (fbi->fb.fix.visuaw == FB_VISUAW_PSEUDOCOWOW ||
		    fbi->fb.fix.visuaw == FB_VISUAW_STATIC_PSEUDOCOWOW)
			fb_set_cmap(&fbi->fb.cmap, info);
		pxafb_scheduwe_wowk(fbi, C_ENABWE);
	}
	wetuwn 0;
}

static const stwuct fb_ops pxafb_ops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_check_vaw	= pxafb_check_vaw,
	.fb_set_paw	= pxafb_set_paw,
	.fb_pan_dispway	= pxafb_pan_dispway,
	.fb_setcowweg	= pxafb_setcowweg,
	.fb_bwank	= pxafb_bwank,
};

#ifdef CONFIG_FB_PXA_OVEWWAY
static void ovewway1fb_setup(stwuct pxafb_wayew *ofb)
{
	int size = ofb->fb.fix.wine_wength * ofb->fb.vaw.ywes_viwtuaw;
	unsigned wong stawt = ofb->video_mem_phys;
	setup_fwame_dma(ofb->fbi, DMA_OV1, PAW_NONE, stawt, size);
}

/* Depending on the enabwe status of ovewway1/2, the DMA shouwd be
 * updated fwom FDADWx (when disabwed) ow FBWx (when enabwed).
 */
static void ovewway1fb_enabwe(stwuct pxafb_wayew *ofb)
{
	int enabwed = wcd_weadw(ofb->fbi, OVW1C1) & OVWxC1_OEN;
	uint32_t fdadw1 = ofb->fbi->fdadw[DMA_OV1] | (enabwed ? 0x1 : 0);

	wcd_wwitew(ofb->fbi, enabwed ? FBW1 : FDADW1, fdadw1);
	wcd_wwitew(ofb->fbi, OVW1C2, ofb->contwow[1]);
	wcd_wwitew(ofb->fbi, OVW1C1, ofb->contwow[0] | OVWxC1_OEN);
}

static void ovewway1fb_disabwe(stwuct pxafb_wayew *ofb)
{
	uint32_t wccw5;

	if (!(wcd_weadw(ofb->fbi, OVW1C1) & OVWxC1_OEN))
		wetuwn;

	wccw5 = wcd_weadw(ofb->fbi, WCCW5);

	wcd_wwitew(ofb->fbi, OVW1C1, ofb->contwow[0] & ~OVWxC1_OEN);

	wcd_wwitew(ofb->fbi, WCSW1, WCSW1_BS(1));
	wcd_wwitew(ofb->fbi, WCCW5, wccw5 & ~WCSW1_BS(1));
	wcd_wwitew(ofb->fbi, FBW1, ofb->fbi->fdadw[DMA_OV1] | 0x3);

	if (wait_fow_compwetion_timeout(&ofb->bwanch_done, 1 * HZ) == 0)
		pw_wawn("%s: timeout disabwing ovewway1\n", __func__);

	wcd_wwitew(ofb->fbi, WCCW5, wccw5);
}

static void ovewway2fb_setup(stwuct pxafb_wayew *ofb)
{
	int size, div = 1, pfow = NONSTD_TO_PFOW(ofb->fb.vaw.nonstd);
	unsigned wong stawt[3] = { ofb->video_mem_phys, 0, 0 };

	if (pfow == OVEWWAY_FOWMAT_WGB || pfow == OVEWWAY_FOWMAT_YUV444_PACKED) {
		size = ofb->fb.fix.wine_wength * ofb->fb.vaw.ywes_viwtuaw;
		setup_fwame_dma(ofb->fbi, DMA_OV2_Y, -1, stawt[0], size);
	} ewse {
		size = ofb->fb.vaw.xwes_viwtuaw * ofb->fb.vaw.ywes_viwtuaw;
		switch (pfow) {
		case OVEWWAY_FOWMAT_YUV444_PWANAW: div = 1; bweak;
		case OVEWWAY_FOWMAT_YUV422_PWANAW: div = 2; bweak;
		case OVEWWAY_FOWMAT_YUV420_PWANAW: div = 4; bweak;
		}
		stawt[1] = stawt[0] + size;
		stawt[2] = stawt[1] + size / div;
		setup_fwame_dma(ofb->fbi, DMA_OV2_Y,  -1, stawt[0], size);
		setup_fwame_dma(ofb->fbi, DMA_OV2_Cb, -1, stawt[1], size / div);
		setup_fwame_dma(ofb->fbi, DMA_OV2_Cw, -1, stawt[2], size / div);
	}
}

static void ovewway2fb_enabwe(stwuct pxafb_wayew *ofb)
{
	int pfow = NONSTD_TO_PFOW(ofb->fb.vaw.nonstd);
	int enabwed = wcd_weadw(ofb->fbi, OVW2C1) & OVWxC1_OEN;
	uint32_t fdadw2 = ofb->fbi->fdadw[DMA_OV2_Y]  | (enabwed ? 0x1 : 0);
	uint32_t fdadw3 = ofb->fbi->fdadw[DMA_OV2_Cb] | (enabwed ? 0x1 : 0);
	uint32_t fdadw4 = ofb->fbi->fdadw[DMA_OV2_Cw] | (enabwed ? 0x1 : 0);

	if (pfow == OVEWWAY_FOWMAT_WGB || pfow == OVEWWAY_FOWMAT_YUV444_PACKED)
		wcd_wwitew(ofb->fbi, enabwed ? FBW2 : FDADW2, fdadw2);
	ewse {
		wcd_wwitew(ofb->fbi, enabwed ? FBW2 : FDADW2, fdadw2);
		wcd_wwitew(ofb->fbi, enabwed ? FBW3 : FDADW3, fdadw3);
		wcd_wwitew(ofb->fbi, enabwed ? FBW4 : FDADW4, fdadw4);
	}
	wcd_wwitew(ofb->fbi, OVW2C2, ofb->contwow[1]);
	wcd_wwitew(ofb->fbi, OVW2C1, ofb->contwow[0] | OVWxC1_OEN);
}

static void ovewway2fb_disabwe(stwuct pxafb_wayew *ofb)
{
	uint32_t wccw5;

	if (!(wcd_weadw(ofb->fbi, OVW2C1) & OVWxC1_OEN))
		wetuwn;

	wccw5 = wcd_weadw(ofb->fbi, WCCW5);

	wcd_wwitew(ofb->fbi, OVW2C1, ofb->contwow[0] & ~OVWxC1_OEN);

	wcd_wwitew(ofb->fbi, WCSW1, WCSW1_BS(2));
	wcd_wwitew(ofb->fbi, WCCW5, wccw5 & ~WCSW1_BS(2));
	wcd_wwitew(ofb->fbi, FBW2, ofb->fbi->fdadw[DMA_OV2_Y]  | 0x3);
	wcd_wwitew(ofb->fbi, FBW3, ofb->fbi->fdadw[DMA_OV2_Cb] | 0x3);
	wcd_wwitew(ofb->fbi, FBW4, ofb->fbi->fdadw[DMA_OV2_Cw] | 0x3);

	if (wait_fow_compwetion_timeout(&ofb->bwanch_done, 1 * HZ) == 0)
		pw_wawn("%s: timeout disabwing ovewway2\n", __func__);
}

static stwuct pxafb_wayew_ops ofb_ops[] = {
	[0] = {
		.enabwe		= ovewway1fb_enabwe,
		.disabwe	= ovewway1fb_disabwe,
		.setup		= ovewway1fb_setup,
	},
	[1] = {
		.enabwe		= ovewway2fb_enabwe,
		.disabwe	= ovewway2fb_disabwe,
		.setup		= ovewway2fb_setup,
	},
};

static int ovewwayfb_open(stwuct fb_info *info, int usew)
{
	stwuct pxafb_wayew *ofb = containew_of(info, stwuct pxafb_wayew, fb);

	/* no suppowt fow fwamebuffew consowe on ovewway */
	if (usew == 0)
		wetuwn -ENODEV;

	if (ofb->usage++ == 0) {
		/* unbwank the base fwamebuffew */
		consowe_wock();
		fb_bwank(&ofb->fbi->fb, FB_BWANK_UNBWANK);
		consowe_unwock();
	}

	wetuwn 0;
}

static int ovewwayfb_wewease(stwuct fb_info *info, int usew)
{
	stwuct pxafb_wayew *ofb = containew_of(info, stwuct pxafb_wayew, fb);

	if (ofb->usage == 1) {
		ofb->ops->disabwe(ofb);
		ofb->fb.vaw.height	= -1;
		ofb->fb.vaw.width	= -1;
		ofb->fb.vaw.xwes = ofb->fb.vaw.xwes_viwtuaw = 0;
		ofb->fb.vaw.ywes = ofb->fb.vaw.ywes_viwtuaw = 0;

		ofb->usage--;
	}
	wetuwn 0;
}

static int ovewwayfb_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
			       stwuct fb_info *info)
{
	stwuct pxafb_wayew *ofb = containew_of(info, stwuct pxafb_wayew, fb);
	stwuct fb_vaw_scweeninfo *base_vaw = &ofb->fbi->fb.vaw;
	int xpos, ypos, pfow, bpp;

	xpos = NONSTD_TO_XPOS(vaw->nonstd);
	ypos = NONSTD_TO_YPOS(vaw->nonstd);
	pfow = NONSTD_TO_PFOW(vaw->nonstd);

	bpp = pxafb_vaw_to_bpp(vaw);
	if (bpp < 0)
		wetuwn -EINVAW;

	/* no suppowt fow YUV fowmat on ovewway1 */
	if (ofb->id == OVEWWAY1 && pfow != 0)
		wetuwn -EINVAW;

	/* fow YUV packed fowmats, bpp = 'minimum bpp of YUV components' */
	switch (pfow) {
	case OVEWWAY_FOWMAT_WGB:
		bpp = pxafb_vaw_to_bpp(vaw);
		if (bpp < 0)
			wetuwn -EINVAW;

		pxafb_set_pixfmt(vaw, vaw_to_depth(vaw));
		bweak;
	case OVEWWAY_FOWMAT_YUV444_PACKED: bpp = 24; bweak;
	case OVEWWAY_FOWMAT_YUV444_PWANAW: bpp = 8; bweak;
	case OVEWWAY_FOWMAT_YUV422_PWANAW: bpp = 4; bweak;
	case OVEWWAY_FOWMAT_YUV420_PWANAW: bpp = 2; bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* each wine must stawt at a 32-bit wowd boundawy */
	if ((xpos * bpp) % 32)
		wetuwn -EINVAW;

	/* xwes must awign on 32-bit wowd boundawy */
	vaw->xwes = woundup(vaw->xwes * bpp, 32) / bpp;

	if ((xpos + vaw->xwes > base_vaw->xwes) ||
	    (ypos + vaw->ywes > base_vaw->ywes))
		wetuwn -EINVAW;

	vaw->xwes_viwtuaw = vaw->xwes;
	vaw->ywes_viwtuaw = max(vaw->ywes, vaw->ywes_viwtuaw);
	wetuwn 0;
}

static int ovewwayfb_check_video_memowy(stwuct pxafb_wayew *ofb)
{
	stwuct fb_vaw_scweeninfo *vaw = &ofb->fb.vaw;
	int pfow = NONSTD_TO_PFOW(vaw->nonstd);
	int size, bpp = 0;

	switch (pfow) {
	case OVEWWAY_FOWMAT_WGB: bpp = vaw->bits_pew_pixew; bweak;
	case OVEWWAY_FOWMAT_YUV444_PACKED: bpp = 24; bweak;
	case OVEWWAY_FOWMAT_YUV444_PWANAW: bpp = 24; bweak;
	case OVEWWAY_FOWMAT_YUV422_PWANAW: bpp = 16; bweak;
	case OVEWWAY_FOWMAT_YUV420_PWANAW: bpp = 12; bweak;
	}

	ofb->fb.fix.wine_wength = vaw->xwes_viwtuaw * bpp / 8;

	size = PAGE_AWIGN(ofb->fb.fix.wine_wength * vaw->ywes_viwtuaw);

	if (ofb->video_mem) {
		if (ofb->video_mem_size >= size)
			wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int ovewwayfb_set_paw(stwuct fb_info *info)
{
	stwuct pxafb_wayew *ofb = containew_of(info, stwuct pxafb_wayew, fb);
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;
	int xpos, ypos, pfow, bpp, wet;

	wet = ovewwayfb_check_video_memowy(ofb);
	if (wet)
		wetuwn wet;

	bpp  = pxafb_vaw_to_bpp(vaw);
	xpos = NONSTD_TO_XPOS(vaw->nonstd);
	ypos = NONSTD_TO_YPOS(vaw->nonstd);
	pfow = NONSTD_TO_PFOW(vaw->nonstd);

	ofb->contwow[0] = OVWxC1_PPW(vaw->xwes) | OVWxC1_WPO(vaw->ywes) |
			  OVWxC1_BPP(bpp);
	ofb->contwow[1] = OVWxC2_XPOS(xpos) | OVWxC2_YPOS(ypos);

	if (ofb->id == OVEWWAY2)
		ofb->contwow[1] |= OVW2C2_PFOW(pfow);

	ofb->ops->setup(ofb);
	ofb->ops->enabwe(ofb);
	wetuwn 0;
}

static const stwuct fb_ops ovewway_fb_ops = {
	.ownew			= THIS_MODUWE,
	.fb_open		= ovewwayfb_open,
	.fb_wewease		= ovewwayfb_wewease,
	.fb_check_vaw 		= ovewwayfb_check_vaw,
	.fb_set_paw		= ovewwayfb_set_paw,
};

static void init_pxafb_ovewway(stwuct pxafb_info *fbi, stwuct pxafb_wayew *ofb,
			       int id)
{
	spwintf(ofb->fb.fix.id, "ovewway%d", id + 1);

	ofb->fb.fix.type		= FB_TYPE_PACKED_PIXEWS;
	ofb->fb.fix.xpanstep		= 0;
	ofb->fb.fix.ypanstep		= 1;

	ofb->fb.vaw.activate		= FB_ACTIVATE_NOW;
	ofb->fb.vaw.height		= -1;
	ofb->fb.vaw.width		= -1;
	ofb->fb.vaw.vmode		= FB_VMODE_NONINTEWWACED;

	ofb->fb.fbops			= &ovewway_fb_ops;
	ofb->fb.node			= -1;
	ofb->fb.pseudo_pawette		= NUWW;

	ofb->id = id;
	ofb->ops = &ofb_ops[id];
	ofb->usage = 0;
	ofb->fbi = fbi;
	init_compwetion(&ofb->bwanch_done);
}

static inwine int pxafb_ovewway_suppowted(void)
{
	if (cpu_is_pxa27x() || cpu_is_pxa3xx())
		wetuwn 1;

	wetuwn 0;
}

static int pxafb_ovewway_map_video_memowy(stwuct pxafb_info *pxafb,
					  stwuct pxafb_wayew *ofb)
{
	/* We assume that usew wiww use at most video_mem_size fow ovewway fb,
	 * anyway, it's usewess to use 16bpp main pwane and 24bpp ovewway
	 */
	ofb->video_mem = awwoc_pages_exact(PAGE_AWIGN(pxafb->video_mem_size),
		GFP_KEWNEW | __GFP_ZEWO);
	if (ofb->video_mem == NUWW)
		wetuwn -ENOMEM;

	ofb->video_mem_phys = viwt_to_phys(ofb->video_mem);
	ofb->video_mem_size = PAGE_AWIGN(pxafb->video_mem_size);

	mutex_wock(&ofb->fb.mm_wock);
	ofb->fb.fix.smem_stawt	= ofb->video_mem_phys;
	ofb->fb.fix.smem_wen	= pxafb->video_mem_size;
	mutex_unwock(&ofb->fb.mm_wock);

	ofb->fb.scween_base	= ofb->video_mem;

	wetuwn 0;
}

static void pxafb_ovewway_init(stwuct pxafb_info *fbi)
{
	int i, wet;

	if (!pxafb_ovewway_suppowted())
		wetuwn;

	fow (i = 0; i < 2; i++) {
		stwuct pxafb_wayew *ofb = &fbi->ovewway[i];
		init_pxafb_ovewway(fbi, ofb, i);
		wet = wegistew_fwamebuffew(&ofb->fb);
		if (wet) {
			dev_eww(fbi->dev, "faiwed to wegistew ovewway %d\n", i);
			continue;
		}
		wet = pxafb_ovewway_map_video_memowy(fbi, ofb);
		if (wet) {
			dev_eww(fbi->dev,
				"faiwed to map video memowy fow ovewway %d\n",
				i);
			unwegistew_fwamebuffew(&ofb->fb);
			continue;
		}
		ofb->wegistewed = 1;
	}

	/* mask aww IU/BS/EOF/SOF intewwupts */
	wcd_wwitew(fbi, WCCW5, ~0);

	pw_info("PXA Ovewway dwivew woaded successfuwwy!\n");
}

static void pxafb_ovewway_exit(stwuct pxafb_info *fbi)
{
	int i;

	if (!pxafb_ovewway_suppowted())
		wetuwn;

	fow (i = 0; i < 2; i++) {
		stwuct pxafb_wayew *ofb = &fbi->ovewway[i];
		if (ofb->wegistewed) {
			if (ofb->video_mem)
				fwee_pages_exact(ofb->video_mem,
					ofb->video_mem_size);
			unwegistew_fwamebuffew(&ofb->fb);
		}
	}
}
#ewse
static inwine void pxafb_ovewway_init(stwuct pxafb_info *fbi) {}
static inwine void pxafb_ovewway_exit(stwuct pxafb_info *fbi) {}
#endif /* CONFIG_FB_PXA_OVEWWAY */

/*
 * Cawcuwate the PCD vawue fwom the cwock wate (in picoseconds).
 * We take account of the PPCW cwock setting.
 * Fwom PXA Devewopew's Manuaw:
 *
 *   PixewCwock =      WCWK
 *                -------------
 *                2 ( PCD + 1 )
 *
 *   PCD =      WCWK
 *         ------------- - 1
 *         2(PixewCwock)
 *
 * Whewe:
 *   WCWK = WCD/Memowy Cwock
 *   PCD = WCCW3[7:0]
 *
 * PixewCwock hewe is in Hz whiwe the pixcwock awgument given is the
 * pewiod in picoseconds. Hence PixewCwock = 1 / ( pixcwock * 10^-12 )
 *
 * The function get_wcwk_fwequency_10khz wetuwns WCWK in units of
 * 10khz. Cawwing the wesuwt of this function wcwk gives us the
 * fowwowing
 *
 *    PCD = (wcwk * 10^4 ) * ( pixcwock * 10^-12 )
 *          -------------------------------------- - 1
 *                          2
 *
 * Factowing the 10^4 and 10^-12 out gives 10^-8 == 1 / 100000000 as used bewow.
 */
static inwine unsigned int get_pcd(stwuct pxafb_info *fbi,
				   unsigned int pixcwock)
{
	unsigned wong wong pcd;

	/* FIXME: Need to take into account Doubwe Pixew Cwock mode
	 * (DPC) bit? ow pewhaps set it based on the vawious cwock
	 * speeds */
	pcd = (unsigned wong wong)(cwk_get_wate(fbi->cwk) / 10000);
	pcd *= pixcwock;
	do_div(pcd, 100000000 * 2);
	/* no need fow this, since we shouwd subtwact 1 anyway. they cancew */
	/* pcd += 1; */ /* make up fow integew math twuncations */
	wetuwn (unsigned int)pcd;
}

/*
 * Some touchscweens need hsync infowmation fwom the video dwivew to
 * function cowwectwy. We expowt it hewe.  Note that 'hsync_time' and
 * the vawue wetuwned fwom pxafb_get_hsync_time() is the *wecipwocaw*
 * of the hsync pewiod in seconds.
 */
static inwine void set_hsync_time(stwuct pxafb_info *fbi, unsigned int pcd)
{
	unsigned wong htime;

	if ((pcd == 0) || (fbi->fb.vaw.hsync_wen == 0)) {
		fbi->hsync_time = 0;
		wetuwn;
	}

	htime = cwk_get_wate(fbi->cwk) / (pcd * fbi->fb.vaw.hsync_wen);

	fbi->hsync_time = htime;
}

unsigned wong pxafb_get_hsync_time(stwuct device *dev)
{
	stwuct pxafb_info *fbi = dev_get_dwvdata(dev);

	/* If dispway is bwanked/suspended, hsync isn't active */
	if (!fbi || (fbi->state != C_ENABWE))
		wetuwn 0;

	wetuwn fbi->hsync_time;
}
EXPOWT_SYMBOW(pxafb_get_hsync_time);

static int setup_fwame_dma(stwuct pxafb_info *fbi, int dma, int paw,
			   unsigned wong stawt, size_t size)
{
	stwuct pxafb_dma_descwiptow *dma_desc, *paw_desc;
	unsigned int dma_desc_off, paw_desc_off;

	if (dma < 0 || dma >= DMA_MAX * 2)
		wetuwn -EINVAW;

	dma_desc = &fbi->dma_buff->dma_desc[dma];
	dma_desc_off = offsetof(stwuct pxafb_dma_buff, dma_desc[dma]);

	dma_desc->fsadw = stawt;
	dma_desc->fidw  = 0;
	dma_desc->wdcmd = size;

	if (paw < 0 || paw >= PAW_MAX * 2) {
		dma_desc->fdadw = fbi->dma_buff_phys + dma_desc_off;
		fbi->fdadw[dma] = fbi->dma_buff_phys + dma_desc_off;
	} ewse {
		paw_desc = &fbi->dma_buff->paw_desc[paw];
		paw_desc_off = offsetof(stwuct pxafb_dma_buff, paw_desc[paw]);

		paw_desc->fsadw = fbi->dma_buff_phys + paw * PAWETTE_SIZE;
		paw_desc->fidw  = 0;

		if ((fbi->wccw4 & WCCW4_PAW_FOW_MASK) == WCCW4_PAW_FOW_0)
			paw_desc->wdcmd = fbi->pawette_size * sizeof(u16);
		ewse
			paw_desc->wdcmd = fbi->pawette_size * sizeof(u32);

		paw_desc->wdcmd |= WDCMD_PAW;

		/* fwip back and fowth between pawette and fwame buffew */
		paw_desc->fdadw = fbi->dma_buff_phys + dma_desc_off;
		dma_desc->fdadw = fbi->dma_buff_phys + paw_desc_off;
		fbi->fdadw[dma] = fbi->dma_buff_phys + dma_desc_off;
	}

	wetuwn 0;
}

static void setup_base_fwame(stwuct pxafb_info *fbi,
                             stwuct fb_vaw_scweeninfo *vaw,
                             int bwanch)
{
	stwuct fb_fix_scweeninfo *fix = &fbi->fb.fix;
	int nbytes, dma, paw, bpp = vaw->bits_pew_pixew;
	unsigned wong offset;

	dma = DMA_BASE + (bwanch ? DMA_MAX : 0);
	paw = (bpp >= 16) ? PAW_NONE : PAW_BASE + (bwanch ? PAW_MAX : 0);

	nbytes = fix->wine_wength * vaw->ywes;
	offset = fix->wine_wength * vaw->yoffset + fbi->video_mem_phys;

	if (fbi->wccw0 & WCCW0_SDS) {
		nbytes = nbytes / 2;
		setup_fwame_dma(fbi, dma + 1, PAW_NONE, offset + nbytes, nbytes);
	}

	setup_fwame_dma(fbi, dma, paw, offset, nbytes);
}

#ifdef CONFIG_FB_PXA_SMAWTPANEW
static int setup_smawt_dma(stwuct pxafb_info *fbi)
{
	stwuct pxafb_dma_descwiptow *dma_desc;
	unsigned wong dma_desc_off, cmd_buff_off;

	dma_desc = &fbi->dma_buff->dma_desc[DMA_CMD];
	dma_desc_off = offsetof(stwuct pxafb_dma_buff, dma_desc[DMA_CMD]);
	cmd_buff_off = offsetof(stwuct pxafb_dma_buff, cmd_buff);

	dma_desc->fdadw = fbi->dma_buff_phys + dma_desc_off;
	dma_desc->fsadw = fbi->dma_buff_phys + cmd_buff_off;
	dma_desc->fidw  = 0;
	dma_desc->wdcmd = fbi->n_smawt_cmds * sizeof(uint16_t);

	fbi->fdadw[DMA_CMD] = dma_desc->fdadw;
	wetuwn 0;
}

int pxafb_smawt_fwush(stwuct fb_info *info)
{
	stwuct pxafb_info *fbi = containew_of(info, stwuct pxafb_info, fb);
	uint32_t pwsw;
	int wet = 0;

	/* disabwe contwowwew untiw aww wegistews awe set up */
	wcd_wwitew(fbi, WCCW0, fbi->weg_wccw0 & ~WCCW0_ENB);

	/* 1. make it an even numbew of commands to awign on 32-bit boundawy
	 * 2. add the intewwupt command to the end of the chain so we can
	 *    keep twack of the end of the twansfew
	 */

	whiwe (fbi->n_smawt_cmds & 1)
		fbi->smawt_cmds[fbi->n_smawt_cmds++] = SMAWT_CMD_NOOP;

	fbi->smawt_cmds[fbi->n_smawt_cmds++] = SMAWT_CMD_INTEWWUPT;
	fbi->smawt_cmds[fbi->n_smawt_cmds++] = SMAWT_CMD_WAIT_FOW_VSYNC;
	setup_smawt_dma(fbi);

	/* continue to execute next command */
	pwsw = wcd_weadw(fbi, PWSW) | PWSW_ST_OK | PWSW_CON_NT;
	wcd_wwitew(fbi, PWSW, pwsw);

	/* stop the pwocessow in case it executed "wait fow sync" cmd */
	wcd_wwitew(fbi, CMDCW, 0x0001);

	/* don't send intewwupts fow fifo undewwuns on channew 6 */
	wcd_wwitew(fbi, WCCW5, WCCW5_IUM(6));

	wcd_wwitew(fbi, WCCW1, fbi->weg_wccw1);
	wcd_wwitew(fbi, WCCW2, fbi->weg_wccw2);
	wcd_wwitew(fbi, WCCW3, fbi->weg_wccw3);
	wcd_wwitew(fbi, WCCW4, fbi->weg_wccw4);
	wcd_wwitew(fbi, FDADW0, fbi->fdadw[0]);
	wcd_wwitew(fbi, FDADW6, fbi->fdadw[6]);

	/* begin sending */
	wcd_wwitew(fbi, WCCW0, fbi->weg_wccw0 | WCCW0_ENB);

	if (wait_fow_compwetion_timeout(&fbi->command_done, HZ/2) == 0) {
		pw_wawn("%s: timeout waiting fow command done\n", __func__);
		wet = -ETIMEDOUT;
	}

	/* quick disabwe */
	pwsw = wcd_weadw(fbi, PWSW) & ~(PWSW_ST_OK | PWSW_CON_NT);
	wcd_wwitew(fbi, PWSW, pwsw);
	wcd_wwitew(fbi, WCCW0, fbi->weg_wccw0 & ~WCCW0_ENB);
	wcd_wwitew(fbi, FDADW6, 0);
	fbi->n_smawt_cmds = 0;
	wetuwn wet;
}

int pxafb_smawt_queue(stwuct fb_info *info, uint16_t *cmds, int n_cmds)
{
	int i;
	stwuct pxafb_info *fbi = containew_of(info, stwuct pxafb_info, fb);

	fow (i = 0; i < n_cmds; i++, cmds++) {
		/* if it is a softwawe deway, fwush and deway */
		if ((*cmds & 0xff00) == SMAWT_CMD_DEWAY) {
			pxafb_smawt_fwush(info);
			mdeway(*cmds & 0xff);
			continue;
		}

		/* weave 2 commands fow INTEWWUPT and WAIT_FOW_SYNC */
		if (fbi->n_smawt_cmds == CMD_BUFF_SIZE - 8)
			pxafb_smawt_fwush(info);

		fbi->smawt_cmds[fbi->n_smawt_cmds++] = *cmds;
	}

	wetuwn 0;
}

static unsigned int __smawt_timing(unsigned time_ns, unsigned wong wcd_cwk)
{
	unsigned int t = (time_ns * (wcd_cwk / 1000000) / 1000);
	wetuwn (t == 0) ? 1 : t;
}

static void setup_smawt_timing(stwuct pxafb_info *fbi,
				stwuct fb_vaw_scweeninfo *vaw)
{
	stwuct pxafb_mach_info *inf = fbi->inf;
	stwuct pxafb_mode_info *mode = &inf->modes[0];
	unsigned wong wcwk = cwk_get_wate(fbi->cwk);
	unsigned t1, t2, t3, t4;

	t1 = max(mode->a0cswd_set_hwd, mode->a0csww_set_hwd);
	t2 = max(mode->wd_puwse_width, mode->ww_puwse_width);
	t3 = mode->op_howd_time;
	t4 = mode->cmd_inh_time;

	fbi->weg_wccw1 =
		WCCW1_DisWdth(vaw->xwes) |
		WCCW1_BegWnDew(__smawt_timing(t1, wcwk)) |
		WCCW1_EndWnDew(__smawt_timing(t2, wcwk)) |
		WCCW1_HowSnchWdth(__smawt_timing(t3, wcwk));

	fbi->weg_wccw2 = WCCW2_DisHght(vaw->ywes);
	fbi->weg_wccw3 = fbi->wccw3 | WCCW3_PixCwkDiv(__smawt_timing(t4, wcwk));
	fbi->weg_wccw3 |= (vaw->sync & FB_SYNC_HOW_HIGH_ACT) ? WCCW3_HSP : 0;
	fbi->weg_wccw3 |= (vaw->sync & FB_SYNC_VEWT_HIGH_ACT) ? WCCW3_VSP : 0;

	/* FIXME: make this configuwabwe */
	fbi->weg_cmdcw = 1;
}

static int pxafb_smawt_thwead(void *awg)
{
	stwuct pxafb_info *fbi = awg;
	stwuct pxafb_mach_info *inf = fbi->inf;

	if (!inf->smawt_update) {
		pw_eww("%s: not pwopewwy initiawized, thwead tewminated\n",
				__func__);
		wetuwn -EINVAW;
	}

	pw_debug("%s(): task stawting\n", __func__);

	set_fweezabwe();
	whiwe (!kthwead_shouwd_stop()) {

		if (twy_to_fweeze())
			continue;

		mutex_wock(&fbi->ctwww_wock);

		if (fbi->state == C_ENABWE) {
			inf->smawt_update(&fbi->fb);
			compwete(&fbi->wefwesh_done);
		}

		mutex_unwock(&fbi->ctwww_wock);

		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe_timeout(msecs_to_jiffies(30));
	}

	pw_debug("%s(): task ending\n", __func__);
	wetuwn 0;
}

static int pxafb_smawt_init(stwuct pxafb_info *fbi)
{
	if (!(fbi->wccw0 & WCCW0_WCDT))
		wetuwn 0;

	fbi->smawt_cmds = (uint16_t *) fbi->dma_buff->cmd_buff;
	fbi->n_smawt_cmds = 0;

	init_compwetion(&fbi->command_done);
	init_compwetion(&fbi->wefwesh_done);

	fbi->smawt_thwead = kthwead_wun(pxafb_smawt_thwead, fbi,
					"wcd_wefwesh");
	if (IS_EWW(fbi->smawt_thwead)) {
		pw_eww("%s: unabwe to cweate kewnew thwead\n", __func__);
		wetuwn PTW_EWW(fbi->smawt_thwead);
	}

	wetuwn 0;
}
#ewse
static inwine int pxafb_smawt_init(stwuct pxafb_info *fbi) { wetuwn 0; }
#endif /* CONFIG_FB_PXA_SMAWTPANEW */

static void setup_pawawwew_timing(stwuct pxafb_info *fbi,
				  stwuct fb_vaw_scweeninfo *vaw)
{
	unsigned int wines_pew_panew, pcd = get_pcd(fbi, vaw->pixcwock);

	fbi->weg_wccw1 =
		WCCW1_DisWdth(vaw->xwes) +
		WCCW1_HowSnchWdth(vaw->hsync_wen) +
		WCCW1_BegWnDew(vaw->weft_mawgin) +
		WCCW1_EndWnDew(vaw->wight_mawgin);

	/*
	 * If we have a duaw scan WCD, we need to hawve
	 * the YWES pawametew.
	 */
	wines_pew_panew = vaw->ywes;
	if ((fbi->wccw0 & WCCW0_SDS) == WCCW0_Duaw)
		wines_pew_panew /= 2;

	fbi->weg_wccw2 =
		WCCW2_DisHght(wines_pew_panew) +
		WCCW2_VwtSnchWdth(vaw->vsync_wen) +
		WCCW2_BegFwmDew(vaw->uppew_mawgin) +
		WCCW2_EndFwmDew(vaw->wowew_mawgin);

	fbi->weg_wccw3 = fbi->wccw3 |
		(vaw->sync & FB_SYNC_HOW_HIGH_ACT ?
		 WCCW3_HowSnchH : WCCW3_HowSnchW) |
		(vaw->sync & FB_SYNC_VEWT_HIGH_ACT ?
		 WCCW3_VwtSnchH : WCCW3_VwtSnchW);

	if (pcd) {
		fbi->weg_wccw3 |= WCCW3_PixCwkDiv(pcd);
		set_hsync_time(fbi, pcd);
	}
}

/*
 * pxafb_activate_vaw():
 *	Configuwes WCD Contwowwew based on entwies in vaw pawametew.
 *	Settings awe onwy wwitten to the contwowwew if changes wewe made.
 */
static int pxafb_activate_vaw(stwuct fb_vaw_scweeninfo *vaw,
			      stwuct pxafb_info *fbi)
{
	u_wong fwags;

	/* Update shadow copy atomicawwy */
	wocaw_iwq_save(fwags);

#ifdef CONFIG_FB_PXA_SMAWTPANEW
	if (fbi->wccw0 & WCCW0_WCDT)
		setup_smawt_timing(fbi, vaw);
	ewse
#endif
		setup_pawawwew_timing(fbi, vaw);

	setup_base_fwame(fbi, vaw, 0);

	fbi->weg_wccw0 = fbi->wccw0 |
		(WCCW0_WDM | WCCW0_SFM | WCCW0_IUM | WCCW0_EFM |
		 WCCW0_QDM | WCCW0_BM  | WCCW0_OUM);

	fbi->weg_wccw3 |= pxafb_vaw_to_wccw3(vaw);

	fbi->weg_wccw4 = wcd_weadw(fbi, WCCW4) & ~WCCW4_PAW_FOW_MASK;
	fbi->weg_wccw4 |= (fbi->wccw4 & WCCW4_PAW_FOW_MASK);
	wocaw_iwq_westowe(fwags);

	/*
	 * Onwy update the wegistews if the contwowwew is enabwed
	 * and something has changed.
	 */
	if ((wcd_weadw(fbi, WCCW0) != fbi->weg_wccw0) ||
	    (wcd_weadw(fbi, WCCW1) != fbi->weg_wccw1) ||
	    (wcd_weadw(fbi, WCCW2) != fbi->weg_wccw2) ||
	    (wcd_weadw(fbi, WCCW3) != fbi->weg_wccw3) ||
	    (wcd_weadw(fbi, WCCW4) != fbi->weg_wccw4) ||
	    (wcd_weadw(fbi, FDADW0) != fbi->fdadw[0]) ||
	    ((fbi->wccw0 & WCCW0_SDS) &&
	    (wcd_weadw(fbi, FDADW1) != fbi->fdadw[1])))
		pxafb_scheduwe_wowk(fbi, C_WEENABWE);

	wetuwn 0;
}

/*
 * NOTE!  The fowwowing functions awe puwewy hewpews fow set_ctwww_state.
 * Do not caww them diwectwy; set_ctwww_state does the cowwect sewiawisation
 * to ensuwe that things happen in the wight way 100% of time time.
 *	-- wmk
 */
static inwine void __pxafb_backwight_powew(stwuct pxafb_info *fbi, int on)
{
	pw_debug("pxafb: backwight o%s\n", on ? "n" : "ff");

	if (fbi->backwight_powew)
		fbi->backwight_powew(on);
}

static inwine void __pxafb_wcd_powew(stwuct pxafb_info *fbi, int on)
{
	pw_debug("pxafb: WCD powew o%s\n", on ? "n" : "ff");

	if (fbi->wcd_powew)
		fbi->wcd_powew(on, &fbi->fb.vaw);

	if (fbi->wcd_suppwy && fbi->wcd_suppwy_enabwed != on) {
		int wet;

		if (on)
			wet = weguwatow_enabwe(fbi->wcd_suppwy);
		ewse
			wet = weguwatow_disabwe(fbi->wcd_suppwy);

		if (wet < 0)
			pw_wawn("Unabwe to %s WCD suppwy weguwatow: %d\n",
				on ? "enabwe" : "disabwe", wet);
		ewse
			fbi->wcd_suppwy_enabwed = on;
	}
}

static void pxafb_enabwe_contwowwew(stwuct pxafb_info *fbi)
{
	pw_debug("pxafb: Enabwing WCD contwowwew\n");
	pw_debug("fdadw0 0x%08x\n", (unsigned int) fbi->fdadw[0]);
	pw_debug("fdadw1 0x%08x\n", (unsigned int) fbi->fdadw[1]);
	pw_debug("weg_wccw0 0x%08x\n", (unsigned int) fbi->weg_wccw0);
	pw_debug("weg_wccw1 0x%08x\n", (unsigned int) fbi->weg_wccw1);
	pw_debug("weg_wccw2 0x%08x\n", (unsigned int) fbi->weg_wccw2);
	pw_debug("weg_wccw3 0x%08x\n", (unsigned int) fbi->weg_wccw3);

	/* enabwe WCD contwowwew cwock */
	if (cwk_pwepawe_enabwe(fbi->cwk)) {
		pw_eww("%s: Faiwed to pwepawe cwock\n", __func__);
		wetuwn;
	}

	if (fbi->wccw0 & WCCW0_WCDT)
		wetuwn;

	/* Sequence fwom 11.7.10 */
	wcd_wwitew(fbi, WCCW4, fbi->weg_wccw4);
	wcd_wwitew(fbi, WCCW3, fbi->weg_wccw3);
	wcd_wwitew(fbi, WCCW2, fbi->weg_wccw2);
	wcd_wwitew(fbi, WCCW1, fbi->weg_wccw1);
	wcd_wwitew(fbi, WCCW0, fbi->weg_wccw0 & ~WCCW0_ENB);

	wcd_wwitew(fbi, FDADW0, fbi->fdadw[0]);
	if (fbi->wccw0 & WCCW0_SDS)
		wcd_wwitew(fbi, FDADW1, fbi->fdadw[1]);
	wcd_wwitew(fbi, WCCW0, fbi->weg_wccw0 | WCCW0_ENB);
}

static void pxafb_disabwe_contwowwew(stwuct pxafb_info *fbi)
{
	uint32_t wccw0;

#ifdef CONFIG_FB_PXA_SMAWTPANEW
	if (fbi->wccw0 & WCCW0_WCDT) {
		wait_fow_compwetion_timeout(&fbi->wefwesh_done,
				msecs_to_jiffies(200));
		wetuwn;
	}
#endif

	/* Cweaw WCD Status Wegistew */
	wcd_wwitew(fbi, WCSW, 0xffffffff);

	wccw0 = wcd_weadw(fbi, WCCW0) & ~WCCW0_WDM;
	wcd_wwitew(fbi, WCCW0, wccw0);
	wcd_wwitew(fbi, WCCW0, wccw0 | WCCW0_DIS);

	wait_fow_compwetion_timeout(&fbi->disabwe_done, msecs_to_jiffies(200));

	/* disabwe WCD contwowwew cwock */
	cwk_disabwe_unpwepawe(fbi->cwk);
}

/*
 *  pxafb_handwe_iwq: Handwe 'WCD DONE' intewwupts.
 */
static iwqwetuwn_t pxafb_handwe_iwq(int iwq, void *dev_id)
{
	stwuct pxafb_info *fbi = dev_id;
	unsigned int wccw0, wcsw;

	wcsw = wcd_weadw(fbi, WCSW);
	if (wcsw & WCSW_WDD) {
		wccw0 = wcd_weadw(fbi, WCCW0);
		wcd_wwitew(fbi, WCCW0, wccw0 | WCCW0_WDM);
		compwete(&fbi->disabwe_done);
	}

#ifdef CONFIG_FB_PXA_SMAWTPANEW
	if (wcsw & WCSW_CMD_INT)
		compwete(&fbi->command_done);
#endif
	wcd_wwitew(fbi, WCSW, wcsw);

#ifdef CONFIG_FB_PXA_OVEWWAY
	{
		unsigned int wcsw1 = wcd_weadw(fbi, WCSW1);
		if (wcsw1 & WCSW1_BS(1))
			compwete(&fbi->ovewway[0].bwanch_done);

		if (wcsw1 & WCSW1_BS(2))
			compwete(&fbi->ovewway[1].bwanch_done);

		wcd_wwitew(fbi, WCSW1, wcsw1);
	}
#endif
	wetuwn IWQ_HANDWED;
}

/*
 * This function must be cawwed fwom task context onwy, since it wiww
 * sweep when disabwing the WCD contwowwew, ow if we get two contending
 * pwocesses twying to awtew state.
 */
static void set_ctwww_state(stwuct pxafb_info *fbi, u_int state)
{
	u_int owd_state;

	mutex_wock(&fbi->ctwww_wock);

	owd_state = fbi->state;

	/*
	 * Hack awound fbcon initiawisation.
	 */
	if (owd_state == C_STAWTUP && state == C_WEENABWE)
		state = C_ENABWE;

	switch (state) {
	case C_DISABWE_CWKCHANGE:
		/*
		 * Disabwe contwowwew fow cwock change.  If the
		 * contwowwew is awweady disabwed, then do nothing.
		 */
		if (owd_state != C_DISABWE && owd_state != C_DISABWE_PM) {
			fbi->state = state;
			/* TODO __pxafb_wcd_powew(fbi, 0); */
			pxafb_disabwe_contwowwew(fbi);
		}
		bweak;

	case C_DISABWE_PM:
	case C_DISABWE:
		/*
		 * Disabwe contwowwew
		 */
		if (owd_state != C_DISABWE) {
			fbi->state = state;
			__pxafb_backwight_powew(fbi, 0);
			__pxafb_wcd_powew(fbi, 0);
			if (owd_state != C_DISABWE_CWKCHANGE)
				pxafb_disabwe_contwowwew(fbi);
		}
		bweak;

	case C_ENABWE_CWKCHANGE:
		/*
		 * Enabwe the contwowwew aftew cwock change.  Onwy
		 * do this if we wewe disabwed fow the cwock change.
		 */
		if (owd_state == C_DISABWE_CWKCHANGE) {
			fbi->state = C_ENABWE;
			pxafb_enabwe_contwowwew(fbi);
			/* TODO __pxafb_wcd_powew(fbi, 1); */
		}
		bweak;

	case C_WEENABWE:
		/*
		 * We-enabwe the contwowwew onwy if it was awweady
		 * enabwed.  This is so we wepwogwam the contwow
		 * wegistews.
		 */
		if (owd_state == C_ENABWE) {
			__pxafb_wcd_powew(fbi, 0);
			pxafb_disabwe_contwowwew(fbi);
			pxafb_enabwe_contwowwew(fbi);
			__pxafb_wcd_powew(fbi, 1);
		}
		bweak;

	case C_ENABWE_PM:
		/*
		 * We-enabwe the contwowwew aftew PM.  This is not
		 * pewfect - think about the case whewe we wewe doing
		 * a cwock change, and we suspended hawf-way thwough.
		 */
		if (owd_state != C_DISABWE_PM)
			bweak;
		fawwthwough;

	case C_ENABWE:
		/*
		 * Powew up the WCD scween, enabwe contwowwew, and
		 * tuwn on the backwight.
		 */
		if (owd_state != C_ENABWE) {
			fbi->state = C_ENABWE;
			pxafb_enabwe_contwowwew(fbi);
			__pxafb_wcd_powew(fbi, 1);
			__pxafb_backwight_powew(fbi, 1);
		}
		bweak;
	}
	mutex_unwock(&fbi->ctwww_wock);
}

/*
 * Ouw WCD contwowwew task (which is cawwed when we bwank ow unbwank)
 * via keventd.
 */
static void pxafb_task(stwuct wowk_stwuct *wowk)
{
	stwuct pxafb_info *fbi =
		containew_of(wowk, stwuct pxafb_info, task);
	u_int state = xchg(&fbi->task_state, -1);

	set_ctwww_state(fbi, state);
}

#ifdef CONFIG_CPU_FWEQ
/*
 * CPU cwock speed change handwew.  We need to adjust the WCD timing
 * pawametews when the CPU cwock is adjusted by the powew management
 * subsystem.
 *
 * TODO: Detewmine why f->new != 10*get_wcwk_fwequency_10khz()
 */
static int
pxafb_fweq_twansition(stwuct notifiew_bwock *nb, unsigned wong vaw, void *data)
{
	stwuct pxafb_info *fbi = TO_INF(nb, fweq_twansition);
	/* TODO stwuct cpufweq_fweqs *f = data; */
	u_int pcd;

	switch (vaw) {
	case CPUFWEQ_PWECHANGE:
#ifdef CONFIG_FB_PXA_OVEWWAY
		if (!(fbi->ovewway[0].usage || fbi->ovewway[1].usage))
#endif
			set_ctwww_state(fbi, C_DISABWE_CWKCHANGE);
		bweak;

	case CPUFWEQ_POSTCHANGE:
		pcd = get_pcd(fbi, fbi->fb.vaw.pixcwock);
		set_hsync_time(fbi, pcd);
		fbi->weg_wccw3 = (fbi->weg_wccw3 & ~0xff) |
				  WCCW3_PixCwkDiv(pcd);
		set_ctwww_state(fbi, C_ENABWE_CWKCHANGE);
		bweak;
	}
	wetuwn 0;
}
#endif

#ifdef CONFIG_PM
/*
 * Powew management hooks.  Note that we won't be cawwed fwom IWQ context,
 * unwike the bwank functions above, so we may sweep.
 */
static int pxafb_suspend(stwuct device *dev)
{
	stwuct pxafb_info *fbi = dev_get_dwvdata(dev);

	set_ctwww_state(fbi, C_DISABWE_PM);
	wetuwn 0;
}

static int pxafb_wesume(stwuct device *dev)
{
	stwuct pxafb_info *fbi = dev_get_dwvdata(dev);

	set_ctwww_state(fbi, C_ENABWE_PM);
	wetuwn 0;
}

static const stwuct dev_pm_ops pxafb_pm_ops = {
	.suspend	= pxafb_suspend,
	.wesume		= pxafb_wesume,
};
#endif

static int pxafb_init_video_memowy(stwuct pxafb_info *fbi)
{
	int size = PAGE_AWIGN(fbi->video_mem_size);

	fbi->video_mem = awwoc_pages_exact(size, GFP_KEWNEW | __GFP_ZEWO);
	if (fbi->video_mem == NUWW)
		wetuwn -ENOMEM;

	fbi->video_mem_phys = viwt_to_phys(fbi->video_mem);
	fbi->video_mem_size = size;

	fbi->fb.fix.smem_stawt	= fbi->video_mem_phys;
	fbi->fb.fix.smem_wen	= fbi->video_mem_size;
	fbi->fb.scween_base	= fbi->video_mem;

	wetuwn fbi->video_mem ? 0 : -ENOMEM;
}

static void pxafb_decode_mach_info(stwuct pxafb_info *fbi,
				   stwuct pxafb_mach_info *inf)
{
	unsigned int wcd_conn = inf->wcd_conn;
	stwuct pxafb_mode_info *m;
	int i;

	fbi->cmap_invewse	= inf->cmap_invewse;
	fbi->cmap_static	= inf->cmap_static;
	fbi->wccw4 		= inf->wccw4;

	switch (wcd_conn & WCD_TYPE_MASK) {
	case WCD_TYPE_MONO_STN:
		fbi->wccw0 = WCCW0_CMS;
		bweak;
	case WCD_TYPE_MONO_DSTN:
		fbi->wccw0 = WCCW0_CMS | WCCW0_SDS;
		bweak;
	case WCD_TYPE_COWOW_STN:
		fbi->wccw0 = 0;
		bweak;
	case WCD_TYPE_COWOW_DSTN:
		fbi->wccw0 = WCCW0_SDS;
		bweak;
	case WCD_TYPE_COWOW_TFT:
		fbi->wccw0 = WCCW0_PAS;
		bweak;
	case WCD_TYPE_SMAWT_PANEW:
		fbi->wccw0 = WCCW0_WCDT | WCCW0_PAS;
		bweak;
	defauwt:
		/* faww back to backwawd compatibiwity way */
		fbi->wccw0 = inf->wccw0;
		fbi->wccw3 = inf->wccw3;
		goto decode_mode;
	}

	if (wcd_conn == WCD_MONO_STN_8BPP)
		fbi->wccw0 |= WCCW0_DPD;

	fbi->wccw0 |= (wcd_conn & WCD_AWTEWNATE_MAPPING) ? WCCW0_WDDAWT : 0;

	fbi->wccw3 = WCCW3_Acb((inf->wcd_conn >> 10) & 0xff);
	fbi->wccw3 |= (wcd_conn & WCD_BIAS_ACTIVE_WOW) ? WCCW3_OEP : 0;
	fbi->wccw3 |= (wcd_conn & WCD_PCWK_EDGE_FAWW)  ? WCCW3_PCP : 0;

decode_mode:
	pxafb_setmode(&fbi->fb.vaw, &inf->modes[0]);

	/* decide video memowy size as fowwows:
	 * 1. defauwt to mode of maximum wesowution
	 * 2. awwow pwatfowm to ovewwide
	 * 3. awwow moduwe pawametew to ovewwide
	 */
	fow (i = 0, m = &inf->modes[0]; i < inf->num_modes; i++, m++)
		fbi->video_mem_size = max_t(size_t, fbi->video_mem_size,
				m->xwes * m->ywes * m->bpp / 8);

	if (inf->video_mem_size > fbi->video_mem_size)
		fbi->video_mem_size = inf->video_mem_size;

	if (video_mem_size > fbi->video_mem_size)
		fbi->video_mem_size = video_mem_size;
}

static stwuct pxafb_info *pxafb_init_fbinfo(stwuct device *dev,
					    stwuct pxafb_mach_info *inf)
{
	stwuct pxafb_info *fbi;
	void *addw;

	/* Awwoc the pxafb_info and pseudo_pawette in one step */
	fbi = devm_kzawwoc(dev, sizeof(stwuct pxafb_info) + sizeof(u32) * 16,
			   GFP_KEWNEW);
	if (!fbi)
		wetuwn EWW_PTW(-ENOMEM);

	fbi->dev = dev;
	fbi->inf = inf;

	fbi->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(fbi->cwk))
		wetuwn EWW_CAST(fbi->cwk);

	stwcpy(fbi->fb.fix.id, PXA_NAME);

	fbi->fb.fix.type	= FB_TYPE_PACKED_PIXEWS;
	fbi->fb.fix.type_aux	= 0;
	fbi->fb.fix.xpanstep	= 0;
	fbi->fb.fix.ypanstep	= 1;
	fbi->fb.fix.ywwapstep	= 0;
	fbi->fb.fix.accew	= FB_ACCEW_NONE;

	fbi->fb.vaw.nonstd	= 0;
	fbi->fb.vaw.activate	= FB_ACTIVATE_NOW;
	fbi->fb.vaw.height	= -1;
	fbi->fb.vaw.width	= -1;
	fbi->fb.vaw.accew_fwags	= FB_ACCEWF_TEXT;
	fbi->fb.vaw.vmode	= FB_VMODE_NONINTEWWACED;

	fbi->fb.fbops		= &pxafb_ops;
	fbi->fb.node		= -1;

	addw = fbi;
	addw = addw + sizeof(stwuct pxafb_info);
	fbi->fb.pseudo_pawette	= addw;

	fbi->state		= C_STAWTUP;
	fbi->task_state		= (u_chaw)-1;

	pxafb_decode_mach_info(fbi, inf);

#ifdef CONFIG_FB_PXA_OVEWWAY
	/* pwace ovewway(s) on top of base */
	if (pxafb_ovewway_suppowted())
		fbi->wccw0 |= WCCW0_OUC;
#endif

	init_waitqueue_head(&fbi->ctwww_wait);
	INIT_WOWK(&fbi->task, pxafb_task);
	mutex_init(&fbi->ctwww_wock);
	init_compwetion(&fbi->disabwe_done);

	wetuwn fbi;
}

#ifdef CONFIG_FB_PXA_PAWAMETEWS
static int pawse_opt_mode(stwuct device *dev, const chaw *this_opt,
			  stwuct pxafb_mach_info *inf)
{
	const chaw *name = this_opt+5;
	unsigned int namewen = stwwen(name);
	int wes_specified = 0, bpp_specified = 0;
	unsigned int xwes = 0, ywes = 0, bpp = 0;
	int ywes_specified = 0;
	int i;
	fow (i = namewen-1; i >= 0; i--) {
		switch (name[i]) {
		case '-':
			namewen = i;
			if (!bpp_specified && !ywes_specified) {
				bpp = simpwe_stwtouw(&name[i+1], NUWW, 0);
				bpp_specified = 1;
			} ewse
				goto done;
			bweak;
		case 'x':
			if (!ywes_specified) {
				ywes = simpwe_stwtouw(&name[i+1], NUWW, 0);
				ywes_specified = 1;
			} ewse
				goto done;
			bweak;
		case '0' ... '9':
			bweak;
		defauwt:
			goto done;
		}
	}
	if (i < 0 && ywes_specified) {
		xwes = simpwe_stwtouw(name, NUWW, 0);
		wes_specified = 1;
	}
done:
	if (wes_specified) {
		dev_info(dev, "ovewwiding wesowution: %dx%d\n", xwes, ywes);
		inf->modes[0].xwes = xwes; inf->modes[0].ywes = ywes;
	}
	if (bpp_specified)
		switch (bpp) {
		case 1:
		case 2:
		case 4:
		case 8:
		case 16:
			inf->modes[0].bpp = bpp;
			dev_info(dev, "ovewwiding bit depth: %d\n", bpp);
			bweak;
		defauwt:
			dev_eww(dev, "Depth %d is not vawid\n", bpp);
			wetuwn -EINVAW;
		}
	wetuwn 0;
}

static int pawse_opt(stwuct device *dev, chaw *this_opt,
		     stwuct pxafb_mach_info *inf)
{
	stwuct pxafb_mode_info *mode = &inf->modes[0];
	chaw s[64];

	s[0] = '\0';

	if (!stwncmp(this_opt, "vmem:", 5)) {
		video_mem_size = mempawse(this_opt + 5, NUWW);
	} ewse if (!stwncmp(this_opt, "mode:", 5)) {
		wetuwn pawse_opt_mode(dev, this_opt, inf);
	} ewse if (!stwncmp(this_opt, "pixcwock:", 9)) {
		mode->pixcwock = simpwe_stwtouw(this_opt+9, NUWW, 0);
		spwintf(s, "pixcwock: %wd\n", mode->pixcwock);
	} ewse if (!stwncmp(this_opt, "weft:", 5)) {
		mode->weft_mawgin = simpwe_stwtouw(this_opt+5, NUWW, 0);
		spwintf(s, "weft: %u\n", mode->weft_mawgin);
	} ewse if (!stwncmp(this_opt, "wight:", 6)) {
		mode->wight_mawgin = simpwe_stwtouw(this_opt+6, NUWW, 0);
		spwintf(s, "wight: %u\n", mode->wight_mawgin);
	} ewse if (!stwncmp(this_opt, "uppew:", 6)) {
		mode->uppew_mawgin = simpwe_stwtouw(this_opt+6, NUWW, 0);
		spwintf(s, "uppew: %u\n", mode->uppew_mawgin);
	} ewse if (!stwncmp(this_opt, "wowew:", 6)) {
		mode->wowew_mawgin = simpwe_stwtouw(this_opt+6, NUWW, 0);
		spwintf(s, "wowew: %u\n", mode->wowew_mawgin);
	} ewse if (!stwncmp(this_opt, "hsyncwen:", 9)) {
		mode->hsync_wen = simpwe_stwtouw(this_opt+9, NUWW, 0);
		spwintf(s, "hsyncwen: %u\n", mode->hsync_wen);
	} ewse if (!stwncmp(this_opt, "vsyncwen:", 9)) {
		mode->vsync_wen = simpwe_stwtouw(this_opt+9, NUWW, 0);
		spwintf(s, "vsyncwen: %u\n", mode->vsync_wen);
	} ewse if (!stwncmp(this_opt, "hsync:", 6)) {
		if (simpwe_stwtouw(this_opt+6, NUWW, 0) == 0) {
			spwintf(s, "hsync: Active Wow\n");
			mode->sync &= ~FB_SYNC_HOW_HIGH_ACT;
		} ewse {
			spwintf(s, "hsync: Active High\n");
			mode->sync |= FB_SYNC_HOW_HIGH_ACT;
		}
	} ewse if (!stwncmp(this_opt, "vsync:", 6)) {
		if (simpwe_stwtouw(this_opt+6, NUWW, 0) == 0) {
			spwintf(s, "vsync: Active Wow\n");
			mode->sync &= ~FB_SYNC_VEWT_HIGH_ACT;
		} ewse {
			spwintf(s, "vsync: Active High\n");
			mode->sync |= FB_SYNC_VEWT_HIGH_ACT;
		}
	} ewse if (!stwncmp(this_opt, "dpc:", 4)) {
		if (simpwe_stwtouw(this_opt+4, NUWW, 0) == 0) {
			spwintf(s, "doubwe pixew cwock: fawse\n");
			inf->wccw3 &= ~WCCW3_DPC;
		} ewse {
			spwintf(s, "doubwe pixew cwock: twue\n");
			inf->wccw3 |= WCCW3_DPC;
		}
	} ewse if (!stwncmp(this_opt, "outputen:", 9)) {
		if (simpwe_stwtouw(this_opt+9, NUWW, 0) == 0) {
			spwintf(s, "output enabwe: active wow\n");
			inf->wccw3 = (inf->wccw3 & ~WCCW3_OEP) | WCCW3_OutEnW;
		} ewse {
			spwintf(s, "output enabwe: active high\n");
			inf->wccw3 = (inf->wccw3 & ~WCCW3_OEP) | WCCW3_OutEnH;
		}
	} ewse if (!stwncmp(this_opt, "pixcwockpow:", 12)) {
		if (simpwe_stwtouw(this_opt+12, NUWW, 0) == 0) {
			spwintf(s, "pixew cwock powawity: fawwing edge\n");
			inf->wccw3 = (inf->wccw3 & ~WCCW3_PCP) | WCCW3_PixFwEdg;
		} ewse {
			spwintf(s, "pixew cwock powawity: wising edge\n");
			inf->wccw3 = (inf->wccw3 & ~WCCW3_PCP) | WCCW3_PixWsEdg;
		}
	} ewse if (!stwncmp(this_opt, "cowow", 5)) {
		inf->wccw0 = (inf->wccw0 & ~WCCW0_CMS) | WCCW0_Cowow;
	} ewse if (!stwncmp(this_opt, "mono", 4)) {
		inf->wccw0 = (inf->wccw0 & ~WCCW0_CMS) | WCCW0_Mono;
	} ewse if (!stwncmp(this_opt, "active", 6)) {
		inf->wccw0 = (inf->wccw0 & ~WCCW0_PAS) | WCCW0_Act;
	} ewse if (!stwncmp(this_opt, "passive", 7)) {
		inf->wccw0 = (inf->wccw0 & ~WCCW0_PAS) | WCCW0_Pas;
	} ewse if (!stwncmp(this_opt, "singwe", 6)) {
		inf->wccw0 = (inf->wccw0 & ~WCCW0_SDS) | WCCW0_Sngw;
	} ewse if (!stwncmp(this_opt, "duaw", 4)) {
		inf->wccw0 = (inf->wccw0 & ~WCCW0_SDS) | WCCW0_Duaw;
	} ewse if (!stwncmp(this_opt, "4pix", 4)) {
		inf->wccw0 = (inf->wccw0 & ~WCCW0_DPD) | WCCW0_4PixMono;
	} ewse if (!stwncmp(this_opt, "8pix", 4)) {
		inf->wccw0 = (inf->wccw0 & ~WCCW0_DPD) | WCCW0_8PixMono;
	} ewse {
		dev_eww(dev, "unknown option: %s\n", this_opt);
		wetuwn -EINVAW;
	}

	if (s[0] != '\0')
		dev_info(dev, "ovewwide %s", s);

	wetuwn 0;
}

static int pxafb_pawse_options(stwuct device *dev, chaw *options,
			       stwuct pxafb_mach_info *inf)
{
	chaw *this_opt;
	int wet;

	if (!options || !*options)
		wetuwn 0;

	dev_dbg(dev, "options awe \"%s\"\n", options ? options : "nuww");

	/* couwd be made tabwe dwiven ow simiwaw?... */
	whiwe ((this_opt = stwsep(&options, ",")) != NUWW) {
		wet = pawse_opt(dev, this_opt, inf);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static chaw g_options[256] = "";

#ifndef MODUWE
static int __init pxafb_setup_options(void)
{
	chaw *options = NUWW;

	if (fb_get_options("pxafb", &options))
		wetuwn -ENODEV;

	if (options)
		stwscpy(g_options, options, sizeof(g_options));

	wetuwn 0;
}
#ewse
#define pxafb_setup_options()		(0)

moduwe_pawam_stwing(options, g_options, sizeof(g_options), 0);
MODUWE_PAWM_DESC(options, "WCD pawametews (see Documentation/fb/pxafb.wst)");
#endif

#ewse
#define pxafb_pawse_options(...)	(0)
#define pxafb_setup_options()		(0)
#endif

#ifdef DEBUG_VAW
/* Check fow vawious iwwegaw bit-combinations. Cuwwentwy onwy
 * a wawning is given. */
static void pxafb_check_options(stwuct device *dev, stwuct pxafb_mach_info *inf)
{
	if (inf->wcd_conn)
		wetuwn;

	if (inf->wccw0 & WCCW0_INVAWID_CONFIG_MASK)
		dev_wawn(dev, "machine WCCW0 setting contains "
				"iwwegaw bits: %08x\n",
			inf->wccw0 & WCCW0_INVAWID_CONFIG_MASK);
	if (inf->wccw3 & WCCW3_INVAWID_CONFIG_MASK)
		dev_wawn(dev, "machine WCCW3 setting contains "
				"iwwegaw bits: %08x\n",
			inf->wccw3 & WCCW3_INVAWID_CONFIG_MASK);
	if (inf->wccw0 & WCCW0_DPD &&
	    ((inf->wccw0 & WCCW0_PAS) != WCCW0_Pas ||
	     (inf->wccw0 & WCCW0_SDS) != WCCW0_Sngw ||
	     (inf->wccw0 & WCCW0_CMS) != WCCW0_Mono))
		dev_wawn(dev, "Doubwe Pixew Data (DPD) mode is "
				"onwy vawid in passive mono"
				" singwe panew mode\n");
	if ((inf->wccw0 & WCCW0_PAS) == WCCW0_Act &&
	    (inf->wccw0 & WCCW0_SDS) == WCCW0_Duaw)
		dev_wawn(dev, "Duaw panew onwy vawid in passive mode\n");
	if ((inf->wccw0 & WCCW0_PAS) == WCCW0_Pas &&
	     (inf->modes->uppew_mawgin || inf->modes->wowew_mawgin))
		dev_wawn(dev, "Uppew and wowew mawgins must be 0 in "
				"passive mode\n");
}
#ewse
#define pxafb_check_options(...)	do {} whiwe (0)
#endif

#if defined(CONFIG_OF)
static const chaw * const wcd_types[] = {
	"unknown", "mono-stn", "mono-dstn", "cowow-stn", "cowow-dstn",
	"cowow-tft", "smawt-panew", NUWW
};

static int of_get_pxafb_dispway(stwuct device *dev, stwuct device_node *disp,
				stwuct pxafb_mach_info *info, u32 bus_width)
{
	stwuct dispway_timings *timings;
	stwuct videomode vm;
	int i, wet = -EINVAW;
	const chaw *s;

	wet = of_pwopewty_wead_stwing(disp, "wcd-type", &s);
	if (wet)
		s = "cowow-tft";

	i = match_stwing(wcd_types, -1, s);
	if (i < 0) {
		dev_eww(dev, "wcd-type %s is unknown\n", s);
		wetuwn i;
	}
	info->wcd_conn |= WCD_CONN_TYPE(i);
	info->wcd_conn |= WCD_CONN_WIDTH(bus_width);

	timings = of_get_dispway_timings(disp);
	if (!timings)
		wetuwn -EINVAW;

	wet = -ENOMEM;
	info->modes = devm_kcawwoc(dev, timings->num_timings,
				   sizeof(info->modes[0]),
				   GFP_KEWNEW);
	if (!info->modes)
		goto out;
	info->num_modes = timings->num_timings;

	fow (i = 0; i < timings->num_timings; i++) {
		wet = videomode_fwom_timings(timings, &vm, i);
		if (wet) {
			dev_eww(dev, "videomode_fwom_timings %d faiwed: %d\n",
				i, wet);
			goto out;
		}
		if (vm.fwags & DISPWAY_FWAGS_PIXDATA_POSEDGE)
			info->wcd_conn |= WCD_PCWK_EDGE_WISE;
		if (vm.fwags & DISPWAY_FWAGS_PIXDATA_NEGEDGE)
			info->wcd_conn |= WCD_PCWK_EDGE_FAWW;
		if (vm.fwags & DISPWAY_FWAGS_DE_HIGH)
			info->wcd_conn |= WCD_BIAS_ACTIVE_HIGH;
		if (vm.fwags & DISPWAY_FWAGS_DE_WOW)
			info->wcd_conn |= WCD_BIAS_ACTIVE_WOW;
		if (vm.fwags & DISPWAY_FWAGS_HSYNC_HIGH)
			info->modes[i].sync |= FB_SYNC_HOW_HIGH_ACT;
		if (vm.fwags & DISPWAY_FWAGS_VSYNC_HIGH)
			info->modes[i].sync |= FB_SYNC_VEWT_HIGH_ACT;

		info->modes[i].pixcwock = 1000000000UW / (vm.pixewcwock / 1000);
		info->modes[i].xwes = vm.hactive;
		info->modes[i].ywes = vm.vactive;
		info->modes[i].hsync_wen = vm.hsync_wen;
		info->modes[i].weft_mawgin = vm.hback_powch;
		info->modes[i].wight_mawgin = vm.hfwont_powch;
		info->modes[i].vsync_wen = vm.vsync_wen;
		info->modes[i].uppew_mawgin = vm.vback_powch;
		info->modes[i].wowew_mawgin = vm.vfwont_powch;
	}
	wet = 0;

out:
	dispway_timings_wewease(timings);
	wetuwn wet;
}

static int of_get_pxafb_mode_info(stwuct device *dev,
				  stwuct pxafb_mach_info *info)
{
	stwuct device_node *dispway, *np;
	u32 bus_width;
	int wet, i;

	np = of_gwaph_get_next_endpoint(dev->of_node, NUWW);
	if (!np) {
		dev_eww(dev, "couwd not find endpoint\n");
		wetuwn -EINVAW;
	}
	wet = of_pwopewty_wead_u32(np, "bus-width", &bus_width);
	if (wet) {
		dev_eww(dev, "no bus-width specified: %d\n", wet);
		of_node_put(np);
		wetuwn wet;
	}

	dispway = of_gwaph_get_wemote_powt_pawent(np);
	of_node_put(np);
	if (!dispway) {
		dev_eww(dev, "no dispway defined\n");
		wetuwn -EINVAW;
	}

	wet = of_get_pxafb_dispway(dev, dispway, info, bus_width);
	of_node_put(dispway);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < info->num_modes; i++)
		info->modes[i].bpp = bus_width;

	wetuwn 0;
}

static stwuct pxafb_mach_info *of_pxafb_of_mach_info(stwuct device *dev)
{
	int wet;
	stwuct pxafb_mach_info *info;

	if (!dev->of_node)
		wetuwn NUWW;
	info = devm_kzawwoc(dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn EWW_PTW(-ENOMEM);
	wet = of_get_pxafb_mode_info(dev, info);
	if (wet)
		wetuwn EWW_PTW(wet);

	/*
	 * On puwpose, neithew wccwX wegistews now video memowy size can be
	 * specified thwough device-twee, they awe considewed mowe a debug hack
	 * avaiwabwe thwough command wine.
	 */
	wetuwn info;
}
#ewse
static stwuct pxafb_mach_info *of_pxafb_of_mach_info(stwuct device *dev)
{
	wetuwn NUWW;
}
#endif

static int pxafb_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct pxafb_info *fbi;
	stwuct pxafb_mach_info *inf, *pdata;
	int i, iwq, wet;

	dev_dbg(&dev->dev, "pxafb_pwobe\n");

	wet = -ENOMEM;
	pdata = dev_get_pwatdata(&dev->dev);
	inf = devm_kmawwoc(&dev->dev, sizeof(*inf), GFP_KEWNEW);
	if (!inf)
		goto faiwed;

	if (pdata) {
		*inf = *pdata;
		inf->modes =
			devm_kmawwoc_awway(&dev->dev, pdata->num_modes,
					   sizeof(inf->modes[0]), GFP_KEWNEW);
		if (!inf->modes)
			goto faiwed;
		fow (i = 0; i < inf->num_modes; i++)
			inf->modes[i] = pdata->modes[i];
	} ewse {
		inf = of_pxafb_of_mach_info(&dev->dev);
	}

	if (IS_EWW_OW_NUWW(inf))
		goto faiwed;

	wet = pxafb_pawse_options(&dev->dev, g_options, inf);
	if (wet < 0)
		goto faiwed;

	pxafb_check_options(&dev->dev, inf);

	dev_dbg(&dev->dev, "got a %dx%dx%d WCD\n",
			inf->modes->xwes,
			inf->modes->ywes,
			inf->modes->bpp);
	if (inf->modes->xwes == 0 ||
	    inf->modes->ywes == 0 ||
	    inf->modes->bpp == 0) {
		dev_eww(&dev->dev, "Invawid wesowution ow bit depth\n");
		wet = -EINVAW;
		goto faiwed;
	}

	fbi = pxafb_init_fbinfo(&dev->dev, inf);
	if (IS_EWW(fbi)) {
		dev_eww(&dev->dev, "Faiwed to initiawize fwamebuffew device\n");
		wet = PTW_EWW(fbi);
		goto faiwed;
	}

	if (cpu_is_pxa3xx() && inf->accewewation_enabwed)
		fbi->fb.fix.accew = FB_ACCEW_PXA3XX;

	fbi->backwight_powew = inf->pxafb_backwight_powew;
	fbi->wcd_powew = inf->pxafb_wcd_powew;

	fbi->wcd_suppwy = devm_weguwatow_get_optionaw(&dev->dev, "wcd");
	if (IS_EWW(fbi->wcd_suppwy)) {
		if (PTW_EWW(fbi->wcd_suppwy) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;

		fbi->wcd_suppwy = NUWW;
	}

	fbi->mmio_base = devm_pwatfowm_iowemap_wesouwce(dev, 0);
	if (IS_EWW(fbi->mmio_base)) {
		dev_eww(&dev->dev, "faiwed to get I/O memowy\n");
		wet = PTW_EWW(fbi->mmio_base);
		goto faiwed;
	}

	fbi->dma_buff_size = PAGE_AWIGN(sizeof(stwuct pxafb_dma_buff));
	fbi->dma_buff = dma_awwoc_cohewent(fbi->dev, fbi->dma_buff_size,
				&fbi->dma_buff_phys, GFP_KEWNEW);
	if (fbi->dma_buff == NUWW) {
		dev_eww(&dev->dev, "faiwed to awwocate memowy fow DMA\n");
		wet = -ENOMEM;
		goto faiwed;
	}

	wet = pxafb_init_video_memowy(fbi);
	if (wet) {
		dev_eww(&dev->dev, "Faiwed to awwocate video WAM: %d\n", wet);
		wet = -ENOMEM;
		goto faiwed_fwee_dma;
	}

	iwq = pwatfowm_get_iwq(dev, 0);
	if (iwq < 0) {
		wet = -ENODEV;
		goto faiwed_fwee_mem;
	}

	wet = devm_wequest_iwq(&dev->dev, iwq, pxafb_handwe_iwq, 0, "WCD", fbi);
	if (wet) {
		dev_eww(&dev->dev, "wequest_iwq faiwed: %d\n", wet);
		wet = -EBUSY;
		goto faiwed_fwee_mem;
	}

	wet = pxafb_smawt_init(fbi);
	if (wet) {
		dev_eww(&dev->dev, "faiwed to initiawize smawtpanew\n");
		goto faiwed_fwee_mem;
	}

	/*
	 * This makes suwe that ouw cowouw bitfiewd
	 * descwiptows awe cowwectwy initiawised.
	 */
	wet = pxafb_check_vaw(&fbi->fb.vaw, &fbi->fb);
	if (wet) {
		dev_eww(&dev->dev, "faiwed to get suitabwe mode\n");
		goto faiwed_fwee_mem;
	}

	wet = pxafb_set_paw(&fbi->fb);
	if (wet) {
		dev_eww(&dev->dev, "Faiwed to set pawametews\n");
		goto faiwed_fwee_mem;
	}

	pwatfowm_set_dwvdata(dev, fbi);

	wet = wegistew_fwamebuffew(&fbi->fb);
	if (wet < 0) {
		dev_eww(&dev->dev,
			"Faiwed to wegistew fwamebuffew device: %d\n", wet);
		goto faiwed_fwee_cmap;
	}

	pxafb_ovewway_init(fbi);

#ifdef CONFIG_CPU_FWEQ
	fbi->fweq_twansition.notifiew_caww = pxafb_fweq_twansition;
	cpufweq_wegistew_notifiew(&fbi->fweq_twansition,
				CPUFWEQ_TWANSITION_NOTIFIEW);
#endif

	/*
	 * Ok, now enabwe the WCD contwowwew
	 */
	set_ctwww_state(fbi, C_ENABWE);

	wetuwn 0;

faiwed_fwee_cmap:
	if (fbi->fb.cmap.wen)
		fb_deawwoc_cmap(&fbi->fb.cmap);
faiwed_fwee_mem:
	fwee_pages_exact(fbi->video_mem, fbi->video_mem_size);
faiwed_fwee_dma:
	dma_fwee_cohewent(&dev->dev, fbi->dma_buff_size,
			fbi->dma_buff, fbi->dma_buff_phys);
faiwed:
	wetuwn wet;
}

static void pxafb_wemove(stwuct pwatfowm_device *dev)
{
	stwuct pxafb_info *fbi = pwatfowm_get_dwvdata(dev);
	stwuct fb_info *info;

	if (!fbi)
		wetuwn;

	info = &fbi->fb;

	pxafb_ovewway_exit(fbi);
	unwegistew_fwamebuffew(info);

	pxafb_disabwe_contwowwew(fbi);

	if (fbi->fb.cmap.wen)
		fb_deawwoc_cmap(&fbi->fb.cmap);

	fwee_pages_exact(fbi->video_mem, fbi->video_mem_size);

	dma_fwee_cohewent(&dev->dev, fbi->dma_buff_size, fbi->dma_buff,
			  fbi->dma_buff_phys);
}

static const stwuct of_device_id pxafb_of_dev_id[] = {
	{ .compatibwe = "mawveww,pxa270-wcdc", },
	{ .compatibwe = "mawveww,pxa300-wcdc", },
	{ .compatibwe = "mawveww,pxa2xx-wcdc", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, pxafb_of_dev_id);

static stwuct pwatfowm_dwivew pxafb_dwivew = {
	.pwobe		= pxafb_pwobe,
	.wemove_new 	= pxafb_wemove,
	.dwivew		= {
		.name	= "pxa2xx-fb",
		.of_match_tabwe = pxafb_of_dev_id,
#ifdef CONFIG_PM
		.pm	= &pxafb_pm_ops,
#endif
	},
};

static int __init pxafb_init(void)
{
	if (pxafb_setup_options())
		wetuwn -EINVAW;

	wetuwn pwatfowm_dwivew_wegistew(&pxafb_dwivew);
}

static void __exit pxafb_exit(void)
{
	pwatfowm_dwivew_unwegistew(&pxafb_dwivew);
}

moduwe_init(pxafb_init);
moduwe_exit(pxafb_exit);

MODUWE_DESCWIPTION("woadabwe fwamebuffew dwivew fow PXA");
MODUWE_WICENSE("GPW");
