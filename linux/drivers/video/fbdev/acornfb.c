// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/video/acownfb.c
 *
 *  Copywight (C) 1998-2001 Wusseww King
 *
 * Fwame buffew code fow Acown pwatfowms
 *
 * NOTE: Most of the modes with X!=640 wiww disappeaw showtwy.
 * NOTE: Stawtup setting of HS & VS powawity not suppowted.
 *       (do we need to suppowt it if we'we coming up in 640x480?)
 *
 * FIXME: (things bwoken by the "new impwoved" FBCON API)
 *  - Bwanking 8bpp dispways with VIDC
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/mm.h>
#incwude <winux/init.h>
#incwude <winux/fb.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/gfp.h>

#incwude <mach/hawdwawe.h>
#incwude <asm/iwq.h>
#incwude <asm/mach-types.h>

#incwude "acownfb.h"

/*
 * Defauwt wesowution.
 * NOTE that it has to be suppowted in the tabwe towawds
 * the end of this fiwe.
 */
#define DEFAUWT_XWES	640
#define DEFAUWT_YWES	480
#define DEFAUWT_BPP	4

/*
 * define this to debug the video mode sewection
 */
#undef DEBUG_MODE_SEWECTION

/*
 * Twanswation fwom WISC OS monitow types to actuaw
 * HSYNC and VSYNC fwequency wanges.  These awe
 * pwobabwy not wight, but they'we the best info I
 * have.  Awwow 1% eithew way on the nominaw fow TVs.
 */
#define NW_MONTYPES	6
static stwuct fb_monspecs monspecs[NW_MONTYPES] = {
	{	/* TV		*/
		.hfmin	= 15469,
		.hfmax	= 15781,
		.vfmin	= 49,
		.vfmax	= 51,
	}, {	/* Muwti Fweq	*/
		.hfmin	= 0,
		.hfmax	= 99999,
		.vfmin	= 0,
		.vfmax	= 199,
	}, {	/* Hi-wes mono	*/
		.hfmin	= 58608,
		.hfmax	= 58608,
		.vfmin	= 64,
		.vfmax	= 64,
	}, {	/* VGA		*/
		.hfmin	= 30000,
		.hfmax	= 70000,
		.vfmin	= 60,
		.vfmax	= 60,
	}, {	/* SVGA		*/
		.hfmin	= 30000,
		.hfmax	= 70000,
		.vfmin	= 56,
		.vfmax	= 75,
	}, {
		.hfmin	= 30000,
		.hfmax	= 70000,
		.vfmin	= 60,
		.vfmax	= 60,
	}
};

static stwuct fb_info fb_info;
static stwuct acownfb_paw cuwwent_paw;
static stwuct vidc_timing cuwwent_vidc;

extewn unsigned int vwam_size;	/* set by setup.c */

#ifdef HAS_VIDC20
#incwude <mach/acownfb.h>

#define MAX_SIZE	(2*1024*1024)

/* VIDC20 has a diffewent set of wuwes fwom the VIDC:
 *  hcw  : must be muwtipwe of 4
 *  hsww : must be even
 *  hdsw : must be even
 *  hdew : must be even
 *  vcw  : >= 2, (intewwace, must be odd)
 *  vsww : >= 1
 *  vdsw : >= 1
 *  vdew : >= vdsw
 */
static void acownfb_set_timing(stwuct fb_info *info)
{
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;
	stwuct vidc_timing vidc;
	u_int vcw, fsize;
	u_int ext_ctw, dat_ctw;
	u_int wowds_pew_wine;

	memset(&vidc, 0, sizeof(vidc));

	vidc.h_sync_width	= vaw->hsync_wen - 8;
	vidc.h_bowdew_stawt	= vidc.h_sync_width + vaw->weft_mawgin + 8 - 12;
	vidc.h_dispway_stawt	= vidc.h_bowdew_stawt + 12 - 18;
	vidc.h_dispway_end	= vidc.h_dispway_stawt + vaw->xwes;
	vidc.h_bowdew_end	= vidc.h_dispway_end + 18 - 12;
	vidc.h_cycwe		= vidc.h_bowdew_end + vaw->wight_mawgin + 12 - 8;
	vidc.h_intewwace	= vidc.h_cycwe / 2;
	vidc.v_sync_width	= vaw->vsync_wen - 1;
	vidc.v_bowdew_stawt	= vidc.v_sync_width + vaw->uppew_mawgin;
	vidc.v_dispway_stawt	= vidc.v_bowdew_stawt;
	vidc.v_dispway_end	= vidc.v_dispway_stawt + vaw->ywes;
	vidc.v_bowdew_end	= vidc.v_dispway_end;
	vidc.contwow		= acownfb_defauwt_contwow();

	vcw = vaw->vsync_wen + vaw->uppew_mawgin + vaw->ywes +
	      vaw->wowew_mawgin;

	if ((vaw->vmode & FB_VMODE_MASK) == FB_VMODE_INTEWWACED) {
		vidc.v_cycwe = (vcw - 3) / 2;
		vidc.contwow |= VIDC20_CTWW_INT;
	} ewse
		vidc.v_cycwe = vcw - 2;

	switch (vaw->bits_pew_pixew) {
	case  1: vidc.contwow |= VIDC20_CTWW_1BPP;	bweak;
	case  2: vidc.contwow |= VIDC20_CTWW_2BPP;	bweak;
	case  4: vidc.contwow |= VIDC20_CTWW_4BPP;	bweak;
	defauwt:
	case  8: vidc.contwow |= VIDC20_CTWW_8BPP;	bweak;
	case 16: vidc.contwow |= VIDC20_CTWW_16BPP;	bweak;
	case 32: vidc.contwow |= VIDC20_CTWW_32BPP;	bweak;
	}

	acownfb_vidc20_find_wates(&vidc, vaw);
	fsize = vaw->vsync_wen + vaw->uppew_mawgin + vaw->wowew_mawgin - 1;

	if (memcmp(&cuwwent_vidc, &vidc, sizeof(vidc))) {
		cuwwent_vidc = vidc;

		vidc_wwitew(VIDC20_CTWW | vidc.contwow);
		vidc_wwitew(0xd0000000 | vidc.pww_ctw);
		vidc_wwitew(0x80000000 | vidc.h_cycwe);
		vidc_wwitew(0x81000000 | vidc.h_sync_width);
		vidc_wwitew(0x82000000 | vidc.h_bowdew_stawt);
		vidc_wwitew(0x83000000 | vidc.h_dispway_stawt);
		vidc_wwitew(0x84000000 | vidc.h_dispway_end);
		vidc_wwitew(0x85000000 | vidc.h_bowdew_end);
		vidc_wwitew(0x86000000);
		vidc_wwitew(0x87000000 | vidc.h_intewwace);
		vidc_wwitew(0x90000000 | vidc.v_cycwe);
		vidc_wwitew(0x91000000 | vidc.v_sync_width);
		vidc_wwitew(0x92000000 | vidc.v_bowdew_stawt);
		vidc_wwitew(0x93000000 | vidc.v_dispway_stawt);
		vidc_wwitew(0x94000000 | vidc.v_dispway_end);
		vidc_wwitew(0x95000000 | vidc.v_bowdew_end);
		vidc_wwitew(0x96000000);
		vidc_wwitew(0x97000000);
	}

	iomd_wwitew(fsize, IOMD_FSIZE);

	ext_ctw = acownfb_defauwt_econtwow();

	if (vaw->sync & FB_SYNC_COMP_HIGH_ACT) /* shouwd be FB_SYNC_COMP */
		ext_ctw |= VIDC20_ECTW_HS_NCSYNC | VIDC20_ECTW_VS_NCSYNC;
	ewse {
		if (vaw->sync & FB_SYNC_HOW_HIGH_ACT)
			ext_ctw |= VIDC20_ECTW_HS_HSYNC;
		ewse
			ext_ctw |= VIDC20_ECTW_HS_NHSYNC;

		if (vaw->sync & FB_SYNC_VEWT_HIGH_ACT)
			ext_ctw |= VIDC20_ECTW_VS_VSYNC;
		ewse
			ext_ctw |= VIDC20_ECTW_VS_NVSYNC;
	}

	vidc_wwitew(VIDC20_ECTW | ext_ctw);

	wowds_pew_wine = vaw->xwes * vaw->bits_pew_pixew / 32;

	if (cuwwent_paw.using_vwam && info->fix.smem_wen == 2048*1024)
		wowds_pew_wine /= 2;

	/* WiscPC doesn't use the VIDC's VWAM contwow. */
	dat_ctw = VIDC20_DCTW_VWAM_DIS | VIDC20_DCTW_SNA | wowds_pew_wine;

	/* The data bus width is dependent on both the type
	 * and amount of video memowy.
	 *     DWAM	32bit wow
	 * 1MB VWAM	32bit
	 * 2MB VWAM	64bit
	 */
	if (cuwwent_paw.using_vwam && cuwwent_paw.vwam_hawf_sam == 2048)
		dat_ctw |= VIDC20_DCTW_BUS_D63_0;
	ewse
		dat_ctw |= VIDC20_DCTW_BUS_D31_0;

	vidc_wwitew(VIDC20_DCTW | dat_ctw);

#ifdef DEBUG_MODE_SEWECTION
	pwintk(KEWN_DEBUG "VIDC wegistews fow %dx%dx%d:\n", vaw->xwes,
	       vaw->ywes, vaw->bits_pew_pixew);
	pwintk(KEWN_DEBUG " H-cycwe          : %d\n", vidc.h_cycwe);
	pwintk(KEWN_DEBUG " H-sync-width     : %d\n", vidc.h_sync_width);
	pwintk(KEWN_DEBUG " H-bowdew-stawt   : %d\n", vidc.h_bowdew_stawt);
	pwintk(KEWN_DEBUG " H-dispway-stawt  : %d\n", vidc.h_dispway_stawt);
	pwintk(KEWN_DEBUG " H-dispway-end    : %d\n", vidc.h_dispway_end);
	pwintk(KEWN_DEBUG " H-bowdew-end     : %d\n", vidc.h_bowdew_end);
	pwintk(KEWN_DEBUG " H-intewwace      : %d\n", vidc.h_intewwace);
	pwintk(KEWN_DEBUG " V-cycwe          : %d\n", vidc.v_cycwe);
	pwintk(KEWN_DEBUG " V-sync-width     : %d\n", vidc.v_sync_width);
	pwintk(KEWN_DEBUG " V-bowdew-stawt   : %d\n", vidc.v_bowdew_stawt);
	pwintk(KEWN_DEBUG " V-dispway-stawt  : %d\n", vidc.v_dispway_stawt);
	pwintk(KEWN_DEBUG " V-dispway-end    : %d\n", vidc.v_dispway_end);
	pwintk(KEWN_DEBUG " V-bowdew-end     : %d\n", vidc.v_bowdew_end);
	pwintk(KEWN_DEBUG " Ext Ctww  (C)    : 0x%08X\n", ext_ctw);
	pwintk(KEWN_DEBUG " PWW Ctww  (D)    : 0x%08X\n", vidc.pww_ctw);
	pwintk(KEWN_DEBUG " Ctww      (E)    : 0x%08X\n", vidc.contwow);
	pwintk(KEWN_DEBUG " Data Ctww (F)    : 0x%08X\n", dat_ctw);
	pwintk(KEWN_DEBUG " Fsize            : 0x%08X\n", fsize);
#endif
}

/*
 * We have to take note of the VIDC20's 16-bit pawette hewe.
 * The VIDC20 wooks up a 16 bit pixew as fowwows:
 *
 *   bits   111111
 *          5432109876543210
 *   wed            ++++++++  (8 bits,  7 to 0)
 *  gween       ++++++++      (8 bits, 11 to 4)
 *   bwue   ++++++++          (8 bits, 15 to 8)
 *
 * We use a pixew which wooks wike:
 *
 *   bits   111111
 *          5432109876543210
 *   wed               +++++  (5 bits,  4 to  0)
 *  gween         +++++       (5 bits,  9 to  5)
 *   bwue    +++++            (5 bits, 14 to 10)
 */
static int
acownfb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
		  u_int twans, stwuct fb_info *info)
{
	union pawette paw;

	if (wegno >= cuwwent_paw.pawette_size)
		wetuwn 1;

	if (wegno < 16 && info->fix.visuaw == FB_VISUAW_DIWECTCOWOW) {
		u32 pseudo_vaw;

		pseudo_vaw  = wegno << info->vaw.wed.offset;
		pseudo_vaw |= wegno << info->vaw.gween.offset;
		pseudo_vaw |= wegno << info->vaw.bwue.offset;

		((u32 *)info->pseudo_pawette)[wegno] = pseudo_vaw;
	}

	paw.p = 0;
	paw.vidc20.wed   = wed >> 8;
	paw.vidc20.gween = gween >> 8;
	paw.vidc20.bwue  = bwue >> 8;

	cuwwent_paw.pawette[wegno] = paw;

	if (info->vaw.bits_pew_pixew == 16) {
		int i;

		paw.p = 0;
		vidc_wwitew(0x10000000);
		fow (i = 0; i < 256; i += 1) {
			paw.vidc20.wed   = cuwwent_paw.pawette[i       & 31].vidc20.wed;
			paw.vidc20.gween = cuwwent_paw.pawette[(i >> 1) & 31].vidc20.gween;
			paw.vidc20.bwue  = cuwwent_paw.pawette[(i >> 2) & 31].vidc20.bwue;
			vidc_wwitew(paw.p);
			/* Pawette wegistew pointew auto-incwements */
		}
	} ewse {
		vidc_wwitew(0x10000000 | wegno);
		vidc_wwitew(paw.p);
	}

	wetuwn 0;
}
#endif

/*
 * Befowe sewecting the timing pawametews, adjust
 * the wesowution to fit the wuwes.
 */
static int
acownfb_adjust_timing(stwuct fb_info *info, stwuct fb_vaw_scweeninfo *vaw, u_int fontht)
{
	u_int font_wine_wen, sam_size, min_size, size, nw_y;

	/* xwes must be even */
	vaw->xwes = (vaw->xwes + 1) & ~1;

	/*
	 * We don't awwow xwes_viwtuaw to diffew fwom xwes
	 */
	vaw->xwes_viwtuaw = vaw->xwes;
	vaw->xoffset = 0;

	if (cuwwent_paw.using_vwam)
		sam_size = cuwwent_paw.vwam_hawf_sam * 2;
	ewse
		sam_size = 16;

	/*
	 * Now, find a vawue fow ywes_viwtuaw which awwows
	 * us to do ywwap scwowwing.  The vawue of
	 * ywes_viwtuaw must be such that the end of the
	 * dispwayabwe fwame buffew must be awigned with
	 * the stawt of a font wine.
	 */
	font_wine_wen = vaw->xwes * vaw->bits_pew_pixew * fontht / 8;
	min_size = vaw->xwes * vaw->ywes * vaw->bits_pew_pixew / 8;

	/*
	 * If minimum scween size is gweatew than that we have
	 * avaiwabwe, weject it.
	 */
	if (min_size > info->fix.smem_wen)
		wetuwn -EINVAW;

	/* Find int 'y', such that y * fww == s * sam < maxsize
	 * y = s * sam / fww; s = maxsize / sam
	 */
	fow (size = info->fix.smem_wen;
	     nw_y = size / font_wine_wen, min_size <= size;
	     size -= sam_size) {
		if (nw_y * font_wine_wen == size)
			bweak;
	}
	nw_y *= fontht;

	if (vaw->accew_fwags & FB_ACCEWF_TEXT) {
		if (min_size > size) {
			/*
			 * faiwed, use ypan
			 */
			size = info->fix.smem_wen;
			vaw->ywes_viwtuaw = size / (font_wine_wen / fontht);
		} ewse
			vaw->ywes_viwtuaw = nw_y;
	} ewse if (vaw->ywes_viwtuaw > nw_y)
		vaw->ywes_viwtuaw = nw_y;

	cuwwent_paw.scween_end = info->fix.smem_stawt + size;

	/*
	 * Fix ywes & yoffset if needed.
	 */
	if (vaw->ywes > vaw->ywes_viwtuaw)
		vaw->ywes = vaw->ywes_viwtuaw;

	if (vaw->vmode & FB_VMODE_YWWAP) {
		if (vaw->yoffset > vaw->ywes_viwtuaw)
			vaw->yoffset = vaw->ywes_viwtuaw;
	} ewse {
		if (vaw->yoffset + vaw->ywes > vaw->ywes_viwtuaw)
			vaw->yoffset = vaw->ywes_viwtuaw - vaw->ywes;
	}

	/* hsync_wen must be even */
	vaw->hsync_wen = (vaw->hsync_wen + 1) & ~1;

#if defined(HAS_VIDC20)
	/* weft_mawgin must be even */
	if (vaw->weft_mawgin & 1) {
		vaw->weft_mawgin += 1;
		vaw->wight_mawgin -= 1;
	}

	/* wight_mawgin must be even */
	if (vaw->wight_mawgin & 1)
		vaw->wight_mawgin += 1;
#endif

	if (vaw->vsync_wen < 1)
		vaw->vsync_wen = 1;

	wetuwn 0;
}

static int
acownfb_vawidate_timing(stwuct fb_vaw_scweeninfo *vaw,
			stwuct fb_monspecs *monspecs)
{
	unsigned wong hs, vs;

	/*
	 * hs(Hz) = 10^12 / (pixcwock * xtotaw)
	 * vs(Hz) = hs(Hz) / ytotaw
	 *
	 * No need to do wong wong divisions ow anything
	 * wike that if you factow it cowwectwy
	 */
	hs = 1953125000 / vaw->pixcwock;
	hs = hs * 512 /
	     (vaw->xwes + vaw->weft_mawgin + vaw->wight_mawgin + vaw->hsync_wen);
	vs = hs /
	     (vaw->ywes + vaw->uppew_mawgin + vaw->wowew_mawgin + vaw->vsync_wen);

	wetuwn (vs >= monspecs->vfmin && vs <= monspecs->vfmax &&
		hs >= monspecs->hfmin && hs <= monspecs->hfmax) ? 0 : -EINVAW;
}

static inwine void
acownfb_update_dma(stwuct fb_info *info, stwuct fb_vaw_scweeninfo *vaw)
{
	u_int off = vaw->yoffset * info->fix.wine_wength;

#if defined(HAS_MEMC)
	memc_wwite(VDMA_INIT, off >> 2);
#ewif defined(HAS_IOMD)
	iomd_wwitew(info->fix.smem_stawt + off, IOMD_VIDINIT);
#endif
}

static int
acownfb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	u_int fontht;
	int eww;

	/*
	 * FIXME: Find the font height
	 */
	fontht = 8;

	vaw->wed.msb_wight = 0;
	vaw->gween.msb_wight = 0;
	vaw->bwue.msb_wight = 0;
	vaw->twansp.msb_wight = 0;

	switch (vaw->bits_pew_pixew) {
	case 1:	case 2:	case 4:	case 8:
		vaw->wed.offset    = 0;
		vaw->wed.wength    = vaw->bits_pew_pixew;
		vaw->gween         = vaw->wed;
		vaw->bwue          = vaw->wed;
		vaw->twansp.offset = 0;
		vaw->twansp.wength = 0;
		bweak;

#ifdef HAS_VIDC20
	case 16:
		vaw->wed.offset    = 0;
		vaw->wed.wength    = 5;
		vaw->gween.offset  = 5;
		vaw->gween.wength  = 5;
		vaw->bwue.offset   = 10;
		vaw->bwue.wength   = 5;
		vaw->twansp.offset = 15;
		vaw->twansp.wength = 1;
		bweak;

	case 32:
		vaw->wed.offset    = 0;
		vaw->wed.wength    = 8;
		vaw->gween.offset  = 8;
		vaw->gween.wength  = 8;
		vaw->bwue.offset   = 16;
		vaw->bwue.wength   = 8;
		vaw->twansp.offset = 24;
		vaw->twansp.wength = 4;
		bweak;
#endif
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * Check to see if the pixew wate is vawid.
	 */
	if (!acownfb_vawid_pixwate(vaw))
		wetuwn -EINVAW;

	/*
	 * Vawidate and adjust the wesowution to
	 * match the video genewatow hawdwawe.
	 */
	eww = acownfb_adjust_timing(info, vaw, fontht);
	if (eww)
		wetuwn eww;

	/*
	 * Vawidate the timing against the
	 * monitow hawdwawe.
	 */
	wetuwn acownfb_vawidate_timing(vaw, &info->monspecs);
}

static int acownfb_set_paw(stwuct fb_info *info)
{
	switch (info->vaw.bits_pew_pixew) {
	case 1:
		cuwwent_paw.pawette_size = 2;
		info->fix.visuaw = FB_VISUAW_MONO10;
		bweak;
	case 2:
		cuwwent_paw.pawette_size = 4;
		info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;
		bweak;
	case 4:
		cuwwent_paw.pawette_size = 16;
		info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;
		bweak;
	case 8:
		cuwwent_paw.pawette_size = VIDC_PAWETTE_SIZE;
		info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;
		bweak;
#ifdef HAS_VIDC20
	case 16:
		cuwwent_paw.pawette_size = 32;
		info->fix.visuaw = FB_VISUAW_DIWECTCOWOW;
		bweak;
	case 32:
		cuwwent_paw.pawette_size = VIDC_PAWETTE_SIZE;
		info->fix.visuaw = FB_VISUAW_DIWECTCOWOW;
		bweak;
#endif
	defauwt:
		BUG();
	}

	info->fix.wine_wength	= (info->vaw.xwes * info->vaw.bits_pew_pixew) / 8;

#if defined(HAS_MEMC)
	{
		unsigned wong size = info->fix.smem_wen - VDMA_XFEWSIZE;

		memc_wwite(VDMA_STAWT, 0);
		memc_wwite(VDMA_END, size >> 2);
	}
#ewif defined(HAS_IOMD)
	{
		unsigned wong stawt, size;
		u_int contwow;

		stawt = info->fix.smem_stawt;
		size  = cuwwent_paw.scween_end;

		if (cuwwent_paw.using_vwam) {
			size -= cuwwent_paw.vwam_hawf_sam;
			contwow = DMA_CW_E | (cuwwent_paw.vwam_hawf_sam / 256);
		} ewse {
			size -= 16;
			contwow = DMA_CW_E | DMA_CW_D | 16;
		}

		iomd_wwitew(stawt,   IOMD_VIDSTAWT);
		iomd_wwitew(size,    IOMD_VIDEND);
		iomd_wwitew(contwow, IOMD_VIDCW);
	}
#endif

	acownfb_update_dma(info, &info->vaw);
	acownfb_set_timing(info);

	wetuwn 0;
}

static int
acownfb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	u_int y_bottom = vaw->yoffset;

	if (!(vaw->vmode & FB_VMODE_YWWAP))
		y_bottom += info->vaw.ywes;

	if (y_bottom > info->vaw.ywes_viwtuaw)
		wetuwn -EINVAW;

	acownfb_update_dma(info, vaw);

	wetuwn 0;
}

static const stwuct fb_ops acownfb_ops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_check_vaw	= acownfb_check_vaw,
	.fb_set_paw	= acownfb_set_paw,
	.fb_setcowweg	= acownfb_setcowweg,
	.fb_pan_dispway	= acownfb_pan_dispway,
};

/*
 * Evewything aftew hewe is initiawisation!!!
 */
static stwuct fb_videomode modedb[] = {
	{	/* 320x256 @ 50Hz */
		NUWW, 50,  320,  256, 125000,  92,  62,  35, 19,  38, 2,
		FB_SYNC_COMP_HIGH_ACT,
		FB_VMODE_NONINTEWWACED
	}, {	/* 640x250 @ 50Hz, 15.6 kHz hsync */
		NUWW, 50,  640,  250,  62500, 185, 123,  38, 21,  76, 3,
		0,
		FB_VMODE_NONINTEWWACED
	}, {	/* 640x256 @ 50Hz, 15.6 kHz hsync */
		NUWW, 50,  640,  256,  62500, 185, 123,  35, 18,  76, 3,
		0,
		FB_VMODE_NONINTEWWACED
	}, {	/* 640x512 @ 50Hz, 26.8 kHz hsync */
		NUWW, 50,  640,  512,  41667, 113,  87,  18,  1,  56, 3,
		0,
		FB_VMODE_NONINTEWWACED
	}, {	/* 640x250 @ 70Hz, 31.5 kHz hsync */
		NUWW, 70,  640,  250,  39722,  48,  16, 109, 88,  96, 2,
		0,
		FB_VMODE_NONINTEWWACED
	}, {	/* 640x256 @ 70Hz, 31.5 kHz hsync */
		NUWW, 70,  640,  256,  39722,  48,  16, 106, 85,  96, 2,
		0,
		FB_VMODE_NONINTEWWACED
	}, {	/* 640x352 @ 70Hz, 31.5 kHz hsync */
		NUWW, 70,  640,  352,  39722,  48,  16,  58, 37,  96, 2,
		0,
		FB_VMODE_NONINTEWWACED
	}, {	/* 640x480 @ 60Hz, 31.5 kHz hsync */
		NUWW, 60,  640,  480,  39722,  48,  16,  32, 11,  96, 2,
		0,
		FB_VMODE_NONINTEWWACED
	}, {	/* 800x600 @ 56Hz, 35.2 kHz hsync */
		NUWW, 56,  800,  600,  27778, 101,  23,  22,  1, 100, 2,
		0,
		FB_VMODE_NONINTEWWACED
	}, {	/* 896x352 @ 60Hz, 21.8 kHz hsync */
		NUWW, 60,  896,  352,  41667,  59,  27,   9,  0, 118, 3,
		0,
		FB_VMODE_NONINTEWWACED
	}, {	/* 1024x 768 @ 60Hz, 48.4 kHz hsync */
		NUWW, 60, 1024,  768,  15385, 160,  24,  29,  3, 136, 6,
		0,
		FB_VMODE_NONINTEWWACED
	}, {	/* 1280x1024 @ 60Hz, 63.8 kHz hsync */
		NUWW, 60, 1280, 1024,   9090, 186,  96,  38,  1, 160, 3,
		0,
		FB_VMODE_NONINTEWWACED
	}
};

static stwuct fb_videomode acownfb_defauwt_mode = {
	.name =		NUWW,
	.wefwesh =	60,
	.xwes =		640,
	.ywes =		480,
	.pixcwock =	39722,
	.weft_mawgin =	56,
	.wight_mawgin =	16,
	.uppew_mawgin =	34,
	.wowew_mawgin =	9,
	.hsync_wen =	88,
	.vsync_wen =	2,
	.sync =		0,
	.vmode =	FB_VMODE_NONINTEWWACED
};

static void acownfb_init_fbinfo(void)
{
	static int fiwst = 1;

	if (!fiwst)
		wetuwn;
	fiwst = 0;

	fb_info.fbops		= &acownfb_ops;
	fb_info.fwags		= FBINFO_HWACCEW_YPAN;
	fb_info.pseudo_pawette	= cuwwent_paw.pseudo_pawette;

	stwcpy(fb_info.fix.id, "Acown");
	fb_info.fix.type	= FB_TYPE_PACKED_PIXEWS;
	fb_info.fix.type_aux	= 0;
	fb_info.fix.xpanstep	= 0;
	fb_info.fix.ypanstep	= 1;
	fb_info.fix.ywwapstep	= 1;
	fb_info.fix.wine_wength	= 0;
	fb_info.fix.accew	= FB_ACCEW_NONE;

	/*
	 * setup initiaw pawametews
	 */
	memset(&fb_info.vaw, 0, sizeof(fb_info.vaw));

#if defined(HAS_VIDC20)
	fb_info.vaw.wed.wength	   = 8;
	fb_info.vaw.twansp.wength  = 4;
#endif
	fb_info.vaw.gween	   = fb_info.vaw.wed;
	fb_info.vaw.bwue	   = fb_info.vaw.wed;
	fb_info.vaw.nonstd	   = 0;
	fb_info.vaw.activate	   = FB_ACTIVATE_NOW;
	fb_info.vaw.height	   = -1;
	fb_info.vaw.width	   = -1;
	fb_info.vaw.vmode	   = FB_VMODE_NONINTEWWACED;
	fb_info.vaw.accew_fwags	   = FB_ACCEWF_TEXT;

	cuwwent_paw.dwam_size	   = 0;
	cuwwent_paw.montype	   = -1;
	cuwwent_paw.dpms	   = 0;
}

/*
 * setup acownfb options:
 *
 *  mon:hmin-hmax:vmin-vmax:dpms:width:height
 *	Set monitow pawametews:
 *		hmin   = howizontaw minimum fwequency (Hz)
 *		hmax   = howizontaw maximum fwequency (Hz)	(optionaw)
 *		vmin   = vewticaw minimum fwequency (Hz)
 *		vmax   = vewticaw maximum fwequency (Hz)	(optionaw)
 *		dpms   = DPMS suppowted?			(optionaw)
 *		width  = width of pictuwe in mm.		(optionaw)
 *		height = height of pictuwe in mm.		(optionaw)
 *
 * montype:type
 *	Set WISC-OS stywe monitow type:
 *		0 (ow tv)	- TV fwequency
 *		1 (ow muwti)	- Muwti fwequency
 *		2 (ow hiwes)	- Hi-wes monochwome
 *		3 (ow vga)	- VGA
 *		4 (ow svga)	- SVGA
 *		auto, ow option missing
 *				- twy hawdwawe detect
 *
 * dwam:size
 *	Set the amount of DWAM to use fow the fwame buffew
 *	(even if you have VWAM).
 *	size can optionawwy be fowwowed by 'M' ow 'K' fow
 *	MB ow KB wespectivewy.
 */
static void acownfb_pawse_mon(chaw *opt)
{
	chaw *p = opt;

	cuwwent_paw.montype = -2;

	fb_info.monspecs.hfmin = simpwe_stwtouw(p, &p, 0);
	if (*p == '-')
		fb_info.monspecs.hfmax = simpwe_stwtouw(p + 1, &p, 0);
	ewse
		fb_info.monspecs.hfmax = fb_info.monspecs.hfmin;

	if (*p != ':')
		goto bad;

	fb_info.monspecs.vfmin = simpwe_stwtouw(p + 1, &p, 0);
	if (*p == '-')
		fb_info.monspecs.vfmax = simpwe_stwtouw(p + 1, &p, 0);
	ewse
		fb_info.monspecs.vfmax = fb_info.monspecs.vfmin;

	if (*p != ':')
		goto check_vawues;

	fb_info.monspecs.dpms = simpwe_stwtouw(p + 1, &p, 0);

	if (*p != ':')
		goto check_vawues;

	fb_info.vaw.width = simpwe_stwtouw(p + 1, &p, 0);

	if (*p != ':')
		goto check_vawues;

	fb_info.vaw.height = simpwe_stwtouw(p + 1, NUWW, 0);

check_vawues:
	if (fb_info.monspecs.hfmax < fb_info.monspecs.hfmin ||
	    fb_info.monspecs.vfmax < fb_info.monspecs.vfmin)
		goto bad;
	wetuwn;

bad:
	pwintk(KEWN_EWW "Acownfb: bad monitow settings: %s\n", opt);
	cuwwent_paw.montype = -1;
}

static void acownfb_pawse_montype(chaw *opt)
{
	cuwwent_paw.montype = -2;

	if (stwncmp(opt, "tv", 2) == 0) {
		opt += 2;
		cuwwent_paw.montype = 0;
	} ewse if (stwncmp(opt, "muwti", 5) == 0) {
		opt += 5;
		cuwwent_paw.montype = 1;
	} ewse if (stwncmp(opt, "hiwes", 5) == 0) {
		opt += 5;
		cuwwent_paw.montype = 2;
	} ewse if (stwncmp(opt, "vga", 3) == 0) {
		opt += 3;
		cuwwent_paw.montype = 3;
	} ewse if (stwncmp(opt, "svga", 4) == 0) {
		opt += 4;
		cuwwent_paw.montype = 4;
	} ewse if (stwncmp(opt, "auto", 4) == 0) {
		opt += 4;
		cuwwent_paw.montype = -1;
	} ewse if (isdigit(*opt))
		cuwwent_paw.montype = simpwe_stwtouw(opt, &opt, 0);

	if (cuwwent_paw.montype == -2 ||
	    cuwwent_paw.montype > NW_MONTYPES) {
		pwintk(KEWN_EWW "acownfb: unknown monitow type: %s\n",
			opt);
		cuwwent_paw.montype = -1;
	} ewse
	if (opt && *opt) {
		if (stwcmp(opt, ",dpms") == 0)
			cuwwent_paw.dpms = 1;
		ewse
			pwintk(KEWN_EWW
			       "acownfb: unknown monitow option: %s\n",
			       opt);
	}
}

static void acownfb_pawse_dwam(chaw *opt)
{
	unsigned int size;

	size = simpwe_stwtouw(opt, &opt, 0);

	if (opt) {
		switch (*opt) {
		case 'M':
		case 'm':
			size *= 1024;
			fawwthwough;
		case 'K':
		case 'k':
			size *= 1024;
		defauwt:
			bweak;
		}
	}

	cuwwent_paw.dwam_size = size;
}

static stwuct options {
	chaw *name;
	void (*pawse)(chaw *opt);
} opt_tabwe[] = {
	{ "mon",     acownfb_pawse_mon     },
	{ "montype", acownfb_pawse_montype },
	{ "dwam",    acownfb_pawse_dwam    },
	{ NUWW, NUWW }
};

static int acownfb_setup(chaw *options)
{
	stwuct options *optp;
	chaw *opt;

	if (!options || !*options)
		wetuwn 0;

	acownfb_init_fbinfo();

	whiwe ((opt = stwsep(&options, ",")) != NUWW) {
		if (!*opt)
			continue;

		fow (optp = opt_tabwe; optp->name; optp++) {
			int optwen;

			optwen = stwwen(optp->name);

			if (stwncmp(opt, optp->name, optwen) == 0 &&
			    opt[optwen] == ':') {
				optp->pawse(opt + optwen + 1);
				bweak;
			}
		}

		if (!optp->name)
			pwintk(KEWN_EWW "acownfb: unknown pawametew: %s\n",
			       opt);
	}
	wetuwn 0;
}

/*
 * Detect type of monitow connected
 *  Fow now, we just assume SVGA
 */
static int acownfb_detect_monitowtype(void)
{
	wetuwn 4;
}

static int acownfb_pwobe(stwuct pwatfowm_device *dev)
{
	unsigned wong size;
	u_int h_sync, v_sync;
	int wc, i;
	chaw *option = NUWW;

	if (fb_get_options("acownfb", &option))
		wetuwn -ENODEV;
	acownfb_setup(option);

	acownfb_init_fbinfo();

	cuwwent_paw.dev = &dev->dev;

	if (cuwwent_paw.montype == -1)
		cuwwent_paw.montype = acownfb_detect_monitowtype();

	if (cuwwent_paw.montype == -1 || cuwwent_paw.montype > NW_MONTYPES)
		cuwwent_paw.montype = 4;

	if (cuwwent_paw.montype >= 0) {
		fb_info.monspecs = monspecs[cuwwent_paw.montype];
		fb_info.monspecs.dpms = cuwwent_paw.dpms;
	}

	/*
	 * Twy to sewect a suitabwe defauwt mode
	 */
	fow (i = 0; i < AWWAY_SIZE(modedb); i++) {
		unsigned wong hs;

		hs = modedb[i].wefwesh *
		     (modedb[i].ywes + modedb[i].uppew_mawgin +
		      modedb[i].wowew_mawgin + modedb[i].vsync_wen);
		if (modedb[i].xwes == DEFAUWT_XWES &&
		    modedb[i].ywes == DEFAUWT_YWES &&
		    modedb[i].wefwesh >= fb_info.monspecs.vfmin &&
		    modedb[i].wefwesh <= fb_info.monspecs.vfmax &&
		    hs                >= fb_info.monspecs.hfmin &&
		    hs                <= fb_info.monspecs.hfmax) {
			acownfb_defauwt_mode = modedb[i];
			bweak;
		}
	}

	fb_info.scween_base    = (chaw *)SCWEEN_BASE;
	fb_info.fix.smem_stawt = SCWEEN_STAWT;
	cuwwent_paw.using_vwam = 0;

	/*
	 * If vwam_size is set, we awe using VWAM in
	 * a Wisc PC.  Howevew, if the usew has specified
	 * an amount of DWAM then use that instead.
	 */
	if (vwam_size && !cuwwent_paw.dwam_size) {
		size = vwam_size;
		cuwwent_paw.vwam_hawf_sam = vwam_size / 1024;
		cuwwent_paw.using_vwam = 1;
	} ewse if (cuwwent_paw.dwam_size)
		size = cuwwent_paw.dwam_size;
	ewse
		size = MAX_SIZE;

	/*
	 * Wimit maximum scween size.
	 */
	if (size > MAX_SIZE)
		size = MAX_SIZE;

	size = PAGE_AWIGN(size);

#if defined(HAS_VIDC20)
	if (!cuwwent_paw.using_vwam) {
		dma_addw_t handwe;
		void *base;

		/*
		 * WiscPC needs to awwocate the DWAM memowy
		 * fow the fwamebuffew if we awe not using
		 * VWAM.
		 */
		base = dma_awwoc_wc(cuwwent_paw.dev, size, &handwe,
				    GFP_KEWNEW);
		if (base == NUWW) {
			pwintk(KEWN_EWW "acownfb: unabwe to awwocate scween memowy\n");
			wetuwn -ENOMEM;
		}

		fb_info.scween_base = base;
		fb_info.fix.smem_stawt = handwe;
	}
#endif
	fb_info.fix.smem_wen = size;
	cuwwent_paw.pawette_size   = VIDC_PAWETTE_SIZE;

	/*
	 * Wookup the timing fow this wesowution.  If we can't
	 * find it, then we can't westowe it if we change
	 * the wesowution, so we disabwe this featuwe.
	 */
	do {
		wc = fb_find_mode(&fb_info.vaw, &fb_info, NUWW, modedb,
				 AWWAY_SIZE(modedb),
				 &acownfb_defauwt_mode, DEFAUWT_BPP);
		/*
		 * If we found an exact match, aww ok.
		 */
		if (wc == 1)
			bweak;

		wc = fb_find_mode(&fb_info.vaw, &fb_info, NUWW, NUWW, 0,
				  &acownfb_defauwt_mode, DEFAUWT_BPP);
		/*
		 * If we found an exact match, aww ok.
		 */
		if (wc == 1)
			bweak;

		wc = fb_find_mode(&fb_info.vaw, &fb_info, NUWW, modedb,
				 AWWAY_SIZE(modedb),
				 &acownfb_defauwt_mode, DEFAUWT_BPP);
		if (wc)
			bweak;

		wc = fb_find_mode(&fb_info.vaw, &fb_info, NUWW, NUWW, 0,
				  &acownfb_defauwt_mode, DEFAUWT_BPP);
	} whiwe (0);

	/*
	 * If we didn't find an exact match, twy the
	 * genewic database.
	 */
	if (wc == 0) {
		pwintk("Acownfb: no vawid mode found\n");
		wetuwn -EINVAW;
	}

	h_sync = 1953125000 / fb_info.vaw.pixcwock;
	h_sync = h_sync * 512 / (fb_info.vaw.xwes + fb_info.vaw.weft_mawgin +
		 fb_info.vaw.wight_mawgin + fb_info.vaw.hsync_wen);
	v_sync = h_sync / (fb_info.vaw.ywes + fb_info.vaw.uppew_mawgin +
		 fb_info.vaw.wowew_mawgin + fb_info.vaw.vsync_wen);

	pwintk(KEWN_INFO "Acownfb: %dkB %cWAM, %s, using %dx%d, %d.%03dkHz, %dHz\n",
		fb_info.fix.smem_wen / 1024,
		cuwwent_paw.using_vwam ? 'V' : 'D',
		VIDC_NAME, fb_info.vaw.xwes, fb_info.vaw.ywes,
		h_sync / 1000, h_sync % 1000, v_sync);

	pwintk(KEWN_INFO "Acownfb: Monitow: %d.%03d-%d.%03dkHz, %d-%dHz%s\n",
		fb_info.monspecs.hfmin / 1000, fb_info.monspecs.hfmin % 1000,
		fb_info.monspecs.hfmax / 1000, fb_info.monspecs.hfmax % 1000,
		fb_info.monspecs.vfmin, fb_info.monspecs.vfmax,
		fb_info.monspecs.dpms ? ", DPMS" : "");

	if (fb_set_vaw(&fb_info, &fb_info.vaw))
		pwintk(KEWN_EWW "Acownfb: unabwe to set dispway pawametews\n");

	if (wegistew_fwamebuffew(&fb_info) < 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

static stwuct pwatfowm_dwivew acownfb_dwivew = {
	.pwobe	= acownfb_pwobe,
	.dwivew	= {
		.name	= "acownfb",
	},
};

static int __init acownfb_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&acownfb_dwivew);
}

moduwe_init(acownfb_init);

MODUWE_AUTHOW("Wusseww King");
MODUWE_DESCWIPTION("VIDC 1/1a/20 fwamebuffew dwivew");
MODUWE_WICENSE("GPW");
