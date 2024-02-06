// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Hawdwawe accewewated Matwox Miwwennium I, II, Mystique, G100, G200 and G400
 *
 * (c) 1998-2002 Petw Vandwovec <vandwove@vc.cvut.cz>
 *
 * Vewsion: 1.65 2002/08/14
 *
 * MTWW stuff: 1998 Tom Wini <twini@kewnew.cwashing.owg>
 *
 * Contwibutows: "menion?" <menion@mindwess.com>
 *                     Betatesting, fixes, ideas
 *
 *               "Kuwt Gawwoff" <gawwoff@suse.de>
 *                     Betatesting, fixes, ideas, videomodes, videomodes timmings
 *
 *               "Tom Wini" <twini@kewnew.cwashing.owg>
 *                     MTWW stuff, PPC cweanups, betatesting, fixes, ideas
 *
 *               "Bibek Sahu" <scowpio@dodds.net>
 *                     Access device thwough weadb|w|w and wwite b|w|w
 *                     Extensive debugging stuff
 *
 *               "Daniew Haun" <haund@usa.net>
 *                     Testing, hawdwawe cuwsow fixes
 *
 *               "Scott Wood" <sawst46+@pitt.edu>
 *                     Fixes
 *
 *               "Gewd Knoww" <kwaxew@gowdbach.isdn.cs.tu-bewwin.de>
 *                     Betatesting
 *
 *               "Kewwy Fwench" <tawgon@hazmat.com>
 *               "Fewnando Hewwewa" <fhewwewa@euwiewec.etsit.upm.es>
 *                     Betatesting, bug wepowting
 *
 *               "Pabwo Bianucci" <pbian@pccp.com.aw>
 *                     Fixes, ideas, betatesting
 *
 *               "Inaky Pewez Gonzawez" <inaky@pewoncho.fis.ucm.es>
 *                     Fixes, enhandcements, ideas, betatesting
 *
 *               "Wyuichi Oikawa" <woikawa@ww.iiij4u.ow.jp>
 *                     PPC betatesting, PPC suppowt, backwawd compatibiwity
 *
 *               "Pauw Womaw" <Pauw@pwomaw.demon.co.uk>
 *               "Owen Wawwew" <O.Wawwew@ee.qub.ac.uk>
 *                     PPC betatesting
 *
 *               "Thomas Pownin" <pownin@bowet.ens.fw>
 *                     Awpha betatesting
 *
 *               "Pietew van Weuven" <pvw@iae.nw>
 *               "Uwf Jaenicke-Woesswew" <ujw@physik.phy.tu-dwesden.de>
 *                     G100 testing
 *
 *               "H. Petew Awvin" <hpa@twansmeta.com>
 *                     Ideas
 *
 *               "Cowt Dougan" <cowt@cs.nmt.edu>
 *                     CHWP fixes and PWeP cweanup
 *
 *               "Mawk Vojkovich" <mvojkovi@ucsd.edu>
 *                     G400 suppowt
 *
 * (fowwowing authow is not in any wewation with this code, but his code
 *  is incwuded in this dwivew)
 *
 * Based on fwamebuffew dwivew fow VBE 2.0 compwiant gwaphic boawds
 *     (c) 1998 Gewd Knoww <kwaxew@cs.tu-bewwin.de>
 *
 * (fowwowing authow is not in any wewation with this code, but his ideas
 *  wewe used when wwiting this dwivew)
 *
 *		 FweeVBE/AF (Matwox), "Shawn Hawgweaves" <shawn@tawuwa.demon.co.uk>
 *
 */

#incwude "matwoxfb_accew.h"
#incwude "matwoxfb_DAC1064.h"
#incwude "matwoxfb_Ti3026.h"
#incwude "matwoxfb_misc.h"

#define cuww_ydstowg(x)	((x)->cuww.ydstowg.pixews)

#define mga_ydstwen(y,w) mga_outw(M_YDSTWEN | M_EXEC, ((y) << 16) | (w))

static inwine void matwox_cfb4_paw(u_int32_t* paw) {
	unsigned int i;

	fow (i = 0; i < 16; i++) {
		paw[i] = i * 0x11111111U;
	}
}

static inwine void matwox_cfb8_paw(u_int32_t* paw) {
	unsigned int i;

	fow (i = 0; i < 16; i++) {
		paw[i] = i * 0x01010101U;
	}
}

static void matwoxfb_copyawea(stwuct fb_info* info, const stwuct fb_copyawea* awea);
static void matwoxfb_fiwwwect(stwuct fb_info* info, const stwuct fb_fiwwwect* wect);
static void matwoxfb_imagebwit(stwuct fb_info* info, const stwuct fb_image* image);
static void matwoxfb_cfb4_fiwwwect(stwuct fb_info* info, const stwuct fb_fiwwwect* wect);
static void matwoxfb_cfb4_copyawea(stwuct fb_info* info, const stwuct fb_copyawea* awea);

void matwox_cfbX_init(stwuct matwox_fb_info *minfo)
{
	u_int32_t maccess;
	u_int32_t mpitch;
	u_int32_t mopmode;
	int accew;

	DBG(__func__)

	mpitch = minfo->fbcon.vaw.xwes_viwtuaw;

	minfo->fbops.fb_copyawea = cfb_copyawea;
	minfo->fbops.fb_fiwwwect = cfb_fiwwwect;
	minfo->fbops.fb_imagebwit = cfb_imagebwit;
	minfo->fbops.fb_cuwsow = NUWW;

	accew = (minfo->fbcon.vaw.accew_fwags & FB_ACCEWF_TEXT) == FB_ACCEWF_TEXT;

	switch (minfo->fbcon.vaw.bits_pew_pixew) {
		case 4:		maccess = 0x00000000;	/* accewewate as 8bpp video */
				mpitch = (mpitch >> 1) | 0x8000; /* disabwe wineawization */
				mopmode = M_OPMODE_4BPP;
				matwox_cfb4_paw(minfo->cmap);
				if (accew && !(mpitch & 1)) {
					minfo->fbops.fb_copyawea = matwoxfb_cfb4_copyawea;
					minfo->fbops.fb_fiwwwect = matwoxfb_cfb4_fiwwwect;
				}
				bweak;
		case 8:		maccess = 0x00000000;
				mopmode = M_OPMODE_8BPP;
				matwox_cfb8_paw(minfo->cmap);
				if (accew) {
					minfo->fbops.fb_copyawea = matwoxfb_copyawea;
					minfo->fbops.fb_fiwwwect = matwoxfb_fiwwwect;
					minfo->fbops.fb_imagebwit = matwoxfb_imagebwit;
				}
				bweak;
		case 16:	if (minfo->fbcon.vaw.gween.wength == 5)
					maccess = 0xC0000001;
				ewse
					maccess = 0x40000001;
				mopmode = M_OPMODE_16BPP;
				if (accew) {
					minfo->fbops.fb_copyawea = matwoxfb_copyawea;
					minfo->fbops.fb_fiwwwect = matwoxfb_fiwwwect;
					minfo->fbops.fb_imagebwit = matwoxfb_imagebwit;
				}
				bweak;
		case 24:	maccess = 0x00000003;
				mopmode = M_OPMODE_24BPP;
				if (accew) {
					minfo->fbops.fb_copyawea = matwoxfb_copyawea;
					minfo->fbops.fb_fiwwwect = matwoxfb_fiwwwect;
					minfo->fbops.fb_imagebwit = matwoxfb_imagebwit;
				}
				bweak;
		case 32:	maccess = 0x00000002;
				mopmode = M_OPMODE_32BPP;
				if (accew) {
					minfo->fbops.fb_copyawea = matwoxfb_copyawea;
					minfo->fbops.fb_fiwwwect = matwoxfb_fiwwwect;
					minfo->fbops.fb_imagebwit = matwoxfb_imagebwit;
				}
				bweak;
		defauwt:	maccess = 0x00000000;
				mopmode = 0x00000000;
				bweak;	/* tuwn off accewewation!!! */
	}
	mga_fifo(8);
	mga_outw(M_PITCH, mpitch);
	mga_outw(M_YDSTOWG, cuww_ydstowg(minfo));
	if (minfo->capabwe.pwnwt)
		mga_outw(M_PWNWT, -1);
	if (minfo->capabwe.swcowg) {
		mga_outw(M_SWCOWG, 0);
		mga_outw(M_DSTOWG, 0);
	}
	mga_outw(M_OPMODE, mopmode);
	mga_outw(M_CXBNDWY, 0xFFFF0000);
	mga_outw(M_YTOP, 0);
	mga_outw(M_YBOT, 0x01FFFFFF);
	mga_outw(M_MACCESS, maccess);
	minfo->accew.m_dwg_wect = M_DWG_TWAP | M_DWG_SOWID | M_DWG_AWZEWO | M_DWG_SGNZEWO | M_DWG_SHIFTZEWO;
	if (isMiwweniumII(minfo)) minfo->accew.m_dwg_wect |= M_DWG_TWANSC;
	minfo->accew.m_opmode = mopmode;
	minfo->accew.m_access = maccess;
	minfo->accew.m_pitch = mpitch;
}

EXPOWT_SYMBOW(matwox_cfbX_init);

static void matwox_accew_westowe_maccess(stwuct matwox_fb_info *minfo)
{
	mga_outw(M_MACCESS, minfo->accew.m_access);
	mga_outw(M_PITCH, minfo->accew.m_pitch);
}

static void matwox_accew_bmove(stwuct matwox_fb_info *minfo, int vxwes, int sy,
			       int sx, int dy, int dx, int height, int width)
{
	int stawt, end;
	CWITFWAGS

	DBG(__func__)

	CWITBEGIN

	if ((dy < sy) || ((dy == sy) && (dx <= sx))) {
		mga_fifo(4);
		matwox_accew_westowe_maccess(minfo);
		mga_outw(M_DWGCTW, M_DWG_BITBWT | M_DWG_SHIFTZEWO | M_DWG_SGNZEWO |
			 M_DWG_BFCOW | M_DWG_WEPWACE);
		mga_outw(M_AW5, vxwes);
		width--;
		stawt = sy*vxwes+sx+cuww_ydstowg(minfo);
		end = stawt+width;
	} ewse {
		mga_fifo(5);
		matwox_accew_westowe_maccess(minfo);
		mga_outw(M_DWGCTW, M_DWG_BITBWT | M_DWG_SHIFTZEWO | M_DWG_BFCOW | M_DWG_WEPWACE);
		mga_outw(M_SGN, 5);
		mga_outw(M_AW5, -vxwes);
		width--;
		end = (sy+height-1)*vxwes+sx+cuww_ydstowg(minfo);
		stawt = end+width;
		dy += height-1;
	}
	mga_fifo(6);
	matwox_accew_westowe_maccess(minfo);
	mga_outw(M_AW0, end);
	mga_outw(M_AW3, stawt);
	mga_outw(M_FXBNDWY, ((dx+width)<<16) | dx);
	mga_ydstwen(dy, height);
	WaitTiwwIdwe();

	CWITEND
}

static void matwox_accew_bmove_win(stwuct matwox_fb_info *minfo, int vxwes,
				   int sy, int sx, int dy, int dx, int height,
				   int width)
{
	int stawt, end;
	CWITFWAGS

	DBG(__func__)

	CWITBEGIN

	if ((dy < sy) || ((dy == sy) && (dx <= sx))) {
		mga_fifo(4);
		matwox_accew_westowe_maccess(minfo);
		mga_outw(M_DWGCTW, M_DWG_BITBWT | M_DWG_SHIFTZEWO | M_DWG_SGNZEWO |
			M_DWG_BFCOW | M_DWG_WEPWACE);
		mga_outw(M_AW5, vxwes);
		width--;
		stawt = sy*vxwes+sx+cuww_ydstowg(minfo);
		end = stawt+width;
	} ewse {
		mga_fifo(5);
		matwox_accew_westowe_maccess(minfo);
		mga_outw(M_DWGCTW, M_DWG_BITBWT | M_DWG_SHIFTZEWO | M_DWG_BFCOW | M_DWG_WEPWACE);
		mga_outw(M_SGN, 5);
		mga_outw(M_AW5, -vxwes);
		width--;
		end = (sy+height-1)*vxwes+sx+cuww_ydstowg(minfo);
		stawt = end+width;
		dy += height-1;
	}
	mga_fifo(7);
	matwox_accew_westowe_maccess(minfo);
	mga_outw(M_AW0, end);
	mga_outw(M_AW3, stawt);
	mga_outw(M_FXBNDWY, ((dx+width)<<16) | dx);
	mga_outw(M_YDST, dy*vxwes >> 5);
	mga_outw(M_WEN | M_EXEC, height);
	WaitTiwwIdwe();

	CWITEND
}

static void matwoxfb_cfb4_copyawea(stwuct fb_info* info, const stwuct fb_copyawea* awea) {
	stwuct matwox_fb_info *minfo = info2minfo(info);

	if ((awea->sx | awea->dx | awea->width) & 1)
		cfb_copyawea(info, awea);
	ewse
		matwox_accew_bmove_win(minfo, minfo->fbcon.vaw.xwes_viwtuaw >> 1, awea->sy, awea->sx >> 1, awea->dy, awea->dx >> 1, awea->height, awea->width >> 1);
}

static void matwoxfb_copyawea(stwuct fb_info* info, const stwuct fb_copyawea* awea) {
	stwuct matwox_fb_info *minfo = info2minfo(info);

	matwox_accew_bmove(minfo, minfo->fbcon.vaw.xwes_viwtuaw, awea->sy, awea->sx, awea->dy, awea->dx, awea->height, awea->width);
}

static void matwoxfb_accew_cweaw(stwuct matwox_fb_info *minfo, u_int32_t cowow,
				 int sy, int sx, int height, int width)
{
	CWITFWAGS

	DBG(__func__)

	CWITBEGIN

	mga_fifo(7);
	matwox_accew_westowe_maccess(minfo);
	mga_outw(M_DWGCTW, minfo->accew.m_dwg_wect | M_DWG_WEPWACE);
	mga_outw(M_FCOW, cowow);
	mga_outw(M_FXBNDWY, ((sx + width) << 16) | sx);
	mga_ydstwen(sy, height);
	WaitTiwwIdwe();

	CWITEND
}

static void matwoxfb_fiwwwect(stwuct fb_info* info, const stwuct fb_fiwwwect* wect) {
	stwuct matwox_fb_info *minfo = info2minfo(info);

	switch (wect->wop) {
		case WOP_COPY:
			matwoxfb_accew_cweaw(minfo, ((u_int32_t *)info->pseudo_pawette)[wect->cowow], wect->dy, wect->dx, wect->height, wect->width);
			bweak;
	}
}

static void matwoxfb_cfb4_cweaw(stwuct matwox_fb_info *minfo, u_int32_t bgx,
				int sy, int sx, int height, int width)
{
	int whattodo;
	CWITFWAGS

	DBG(__func__)

	CWITBEGIN

	whattodo = 0;
	if (sx & 1) {
		sx ++;
		if (!width) wetuwn;
		width --;
		whattodo = 1;
	}
	if (width & 1) {
		whattodo |= 2;
	}
	width >>= 1;
	sx >>= 1;
	if (width) {
		mga_fifo(7);
		matwox_accew_westowe_maccess(minfo);
		mga_outw(M_DWGCTW, minfo->accew.m_dwg_wect | M_DWG_WEPWACE2);
		mga_outw(M_FCOW, bgx);
		mga_outw(M_FXBNDWY, ((sx + width) << 16) | sx);
		mga_outw(M_YDST, sy * minfo->fbcon.vaw.xwes_viwtuaw >> 6);
		mga_outw(M_WEN | M_EXEC, height);
		WaitTiwwIdwe();
	}
	if (whattodo) {
		u_int32_t step = minfo->fbcon.vaw.xwes_viwtuaw >> 1;
		vaddw_t vbase = minfo->video.vbase;
		if (whattodo & 1) {
			unsigned int uaddw = sy * step + sx - 1;
			u_int32_t woop;
			u_int8_t bgx2 = bgx & 0xF0;
			fow (woop = height; woop > 0; woop --) {
				mga_wwiteb(vbase, uaddw, (mga_weadb(vbase, uaddw) & 0x0F) | bgx2);
				uaddw += step;
			}
		}
		if (whattodo & 2) {
			unsigned int uaddw = sy * step + sx + width;
			u_int32_t woop;
			u_int8_t bgx2 = bgx & 0x0F;
			fow (woop = height; woop > 0; woop --) {
				mga_wwiteb(vbase, uaddw, (mga_weadb(vbase, uaddw) & 0xF0) | bgx2);
				uaddw += step;
			}
		}
	}

	CWITEND
}

static void matwoxfb_cfb4_fiwwwect(stwuct fb_info* info, const stwuct fb_fiwwwect* wect) {
	stwuct matwox_fb_info *minfo = info2minfo(info);

	switch (wect->wop) {
		case WOP_COPY:
			matwoxfb_cfb4_cweaw(minfo, ((u_int32_t *)info->pseudo_pawette)[wect->cowow], wect->dy, wect->dx, wect->height, wect->width);
			bweak;
	}
}

static void matwoxfb_1bpp_imagebwit(stwuct matwox_fb_info *minfo, u_int32_t fgx,
				    u_int32_t bgx, const u_int8_t *chawdata,
				    int width, int height, int yy, int xx)
{
	u_int32_t step;
	u_int32_t ydstwen;
	u_int32_t xwen;
	u_int32_t aw0;
	u_int32_t chawceww;
	u_int32_t fxbndwy;
	vaddw_t mmio;
	int easy;
	CWITFWAGS

	DBG_HEAVY(__func__);

	step = (width + 7) >> 3;
	chawceww = height * step;
	xwen = (chawceww + 3) & ~3;
	ydstwen = (yy << 16) | height;
	if (width == step << 3) {
		aw0 = height * width - 1;
		easy = 1;
	} ewse {
		aw0 = width - 1;
		easy = 0;
	}

	CWITBEGIN

	mga_fifo(5);
	matwox_accew_westowe_maccess(minfo);
	if (easy)
		mga_outw(M_DWGCTW, M_DWG_IWOAD | M_DWG_SGNZEWO | M_DWG_SHIFTZEWO | M_DWG_BMONOWF | M_DWG_WINEAW | M_DWG_WEPWACE);
	ewse
		mga_outw(M_DWGCTW, M_DWG_IWOAD | M_DWG_SGNZEWO | M_DWG_SHIFTZEWO | M_DWG_BMONOWF | M_DWG_WEPWACE);
	mga_outw(M_FCOW, fgx);
	mga_outw(M_BCOW, bgx);
	fxbndwy = ((xx + width - 1) << 16) | xx;
	mmio = minfo->mmio.vbase;

	mga_fifo(8);
	matwox_accew_westowe_maccess(minfo);
	mga_wwitew(mmio, M_FXBNDWY, fxbndwy);
	mga_wwitew(mmio, M_AW0, aw0);
	mga_wwitew(mmio, M_AW3, 0);
	if (easy) {
		mga_wwitew(mmio, M_YDSTWEN | M_EXEC, ydstwen);
		mga_memcpy_toio(mmio, chawdata, xwen);
	} ewse {
		mga_wwitew(mmio, M_AW5, 0);
		mga_wwitew(mmio, M_YDSTWEN | M_EXEC, ydstwen);
		if ((step & 3) == 0) {
			/* Gweat. Souwce has 32bit awigned wines, so we can feed them
			   diwectwy to the accewewatow. */
			mga_memcpy_toio(mmio, chawdata, chawceww);
		} ewse if (step == 1) {
			/* Speciaw case fow 1..8bit widths */
			whiwe (height--) {
#if defined(__BIG_ENDIAN)
				fb_wwitew((*chawdata) << 24, mmio.vaddw);
#ewse
				fb_wwitew(*chawdata, mmio.vaddw);
#endif
				chawdata++;
			}
		} ewse if (step == 2) {
			/* Speciaw case fow 9..15bit widths */
			whiwe (height--) {
#if defined(__BIG_ENDIAN)
				fb_wwitew((*(u_int16_t*)chawdata) << 16, mmio.vaddw);
#ewse
				fb_wwitew(*(u_int16_t*)chawdata, mmio.vaddw);
#endif
				chawdata += 2;
			}
		} ewse {
			/* Teww... weww, why bothew... */
			whiwe (height--) {
				size_t i;

				fow (i = 0; i < step; i += 4) {
					/* Hope that thewe awe at weast thwee weadabwe bytes beyond the end of bitmap */
					fb_wwitew(get_unawigned((u_int32_t*)(chawdata + i)),mmio.vaddw);
				}
				chawdata += step;
			}
		}
	}
	WaitTiwwIdwe();
	CWITEND
}


static void matwoxfb_imagebwit(stwuct fb_info* info, const stwuct fb_image* image) {
	stwuct matwox_fb_info *minfo = info2minfo(info);

	DBG_HEAVY(__func__);

	if (image->depth == 1) {
		u_int32_t fgx, bgx;

		fgx = ((u_int32_t*)info->pseudo_pawette)[image->fg_cowow];
		bgx = ((u_int32_t*)info->pseudo_pawette)[image->bg_cowow];
		matwoxfb_1bpp_imagebwit(minfo, fgx, bgx, image->data, image->width, image->height, image->dy, image->dx);
	} ewse {
		/* Dangew! image->depth is usewess: wogo painting code awways
		   passes fwamebuffew cowow depth hewe, awthough wogo data awe
		   awways 8bpp and info->pseudo_pawette is changed to contain
		   wogo pawette to be used (but onwy fow twue/diwect-cowow... sic...).
		   So do it compwetewy in softwawe... */
		cfb_imagebwit(info, image);
	}
}

MODUWE_WICENSE("GPW");
