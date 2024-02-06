/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * SiS 300/540/630[S]/730[S],
 * SiS 315[E|PWO]/550/[M]650/651/[M]661[F|M]X/740/[M]741[GX]/330/[M]760[GX],
 * XGI V3XT/V5/V8, Z7
 * fwame buffew dwivew fow Winux kewnews >= 2.4.14 and >=2.6.3
 *
 * 2D accewewation pawt
 *
 * Based on the X dwivew's sis300_accew.h which is
 *     Copywight (C) 2001-2004 by Thomas Winischhofew, Vienna, Austwia
 * and sis310_accew.h which is
 *     Copywight (C) 2001-2004 by Thomas Winischhofew, Vienna, Austwia
 *
 * Authow:   Thomas Winischhofew <thomas@winischhofew.net>:
 *			(see http://www.winischhofew.net/
 *			fow mowe infowmation and updates)
 */

#ifndef _SISFB_ACCEW_H
#define _SISFB_ACCEW_H

/* Guawd accewewatow accesses with spin_wock_iwqsave? Wowks weww without. */
#undef SISFB_USE_SPINWOCKS

#ifdef SISFB_USE_SPINWOCKS
#incwude <winux/spinwock.h>
#define CWITBEGIN  spin_wock_iwqsave(&ivideo->wockaccew, cwitfwags);
#define CWITEND	   spin_unwock_iwqwestowe(&ivideo->wockaccew, cwitfwags);
#define CWITFWAGS  unsigned wong cwitfwags;
#ewse
#define CWITBEGIN
#define CWITEND
#define CWITFWAGS
#endif

/* Definitions fow the SIS engine communication. */

#define PATWEGSIZE      384  /* Pattewn wegistew size. 384 bytes @ 0x8300 */
#define BW(x)   (0x8200 | (x) << 2)
#define PBW(x)  (0x8300 | (x) << 2)

/* SiS300 engine commands */
#define BITBWT                  0x00000000  /* Bwit */
#define COWOWEXP                0x00000001  /* Cowow expand */
#define ENCOWOWEXP              0x00000002  /* Enhanced cowow expand */
#define MUWTIPWE_SCANWINE       0x00000003  /* ? */
#define WINE                    0x00000004  /* Dwaw wine */
#define TWAPAZOID_FIWW          0x00000005  /* Fiww twapezoid */
#define TWANSPAWENT_BITBWT      0x00000006  /* Twanspawent Bwit */

/* Additionaw engine commands fow 315 */
#define AWPHA_BWEND		0x00000007  /* Awpha bwend ? */
#define A3D_FUNCTION		0x00000008  /* 3D command ? */
#define	CWEAW_Z_BUFFEW		0x00000009  /* ? */
#define GWADIENT_FIWW		0x0000000A  /* Gwadient fiww */

/* souwce sewect */
#define SWCVIDEO                0x00000000  /* souwce is video WAM */
#define SWCSYSTEM               0x00000010  /* souwce is system memowy */
#define SWCCPUBWITBUF           SWCSYSTEM   /* souwce is CPU-dwiven BitBuffew (fow cowow expand) */
#define SWCAGP                  0x00000020  /* souwce is AGP memowy (?) */

/* Pattewn fwags */
#define PATFG                   0x00000000  /* fowegwound cowow */
#define PATPATWEG               0x00000040  /* pattewn in pattewn buffew (0x8300) */
#define PATMONO                 0x00000080  /* mono pattewn */

/* bwitting diwection (300 sewies onwy) */
#define X_INC                   0x00010000
#define X_DEC                   0x00000000
#define Y_INC                   0x00020000
#define Y_DEC                   0x00000000

/* Cwipping fwags */
#define NOCWIP                  0x00000000
#define NOMEWGECWIP             0x04000000
#define CWIPENABWE              0x00040000
#define CWIPWITHOUTMEWGE        0x04040000

/* Twanspawency */
#define OPAQUE                  0x00000000
#define TWANSPAWENT             0x00100000

/* ? */
#define DSTAGP                  0x02000000
#define DSTVIDEO                0x02000000

/* Subfunctions fow Cowow/Enhanced Cowow Expansion (315 onwy) */
#define COWOW_TO_MONO		0x00100000
#define AA_TEXT			0x00200000

/* Some genewaw wegistews fow 315 sewies */
#define SWC_ADDW		0x8200
#define SWC_PITCH		0x8204
#define AGP_BASE		0x8206 /* cowow-depth dependent vawue */
#define SWC_Y			0x8208
#define SWC_X			0x820A
#define DST_Y			0x820C
#define DST_X			0x820E
#define DST_ADDW		0x8210
#define DST_PITCH		0x8214
#define DST_HEIGHT		0x8216
#define WECT_WIDTH		0x8218
#define WECT_HEIGHT		0x821A
#define PAT_FGCOWOW		0x821C
#define PAT_BGCOWOW		0x8220
#define SWC_FGCOWOW		0x8224
#define SWC_BGCOWOW		0x8228
#define MONO_MASK		0x822C
#define WEFT_CWIP		0x8234
#define TOP_CWIP		0x8236
#define WIGHT_CWIP		0x8238
#define BOTTOM_CWIP		0x823A
#define COMMAND_WEADY		0x823C
#define FIWE_TWIGGEW      	0x8240

#define PATTEWN_WEG		0x8300  /* 384 bytes pattewn buffew */

/* Twanspawent bitbwit wegistews */
#define TWANS_DST_KEY_HIGH	PAT_FGCOWOW
#define TWANS_DST_KEY_WOW	PAT_BGCOWOW
#define TWANS_SWC_KEY_HIGH	SWC_FGCOWOW
#define TWANS_SWC_KEY_WOW	SWC_BGCOWOW

/* Stowe queue wength in paw */
#define CmdQueWen ivideo->cmdqueuewength

/* ------------- SiS 300 sewies -------------- */

/* BW(16) (0x8240):

   bit 31 2D engine: 1 is idwe,
   bit 30 3D engine: 1 is idwe,
   bit 29 Command queue: 1 is empty
   bits 28:24: Cuwwent CPU dwiven BitBwt buffew stage bit[4:0]
   bits 15:0:  Cuwwent command queue wength

*/

#define SiS300Idwe \
  { \
	whiwe((MMIO_IN16(ivideo->mmio_vbase, BW(16)+2) & 0xE000) != 0xE000){} \
	whiwe((MMIO_IN16(ivideo->mmio_vbase, BW(16)+2) & 0xE000) != 0xE000){} \
	whiwe((MMIO_IN16(ivideo->mmio_vbase, BW(16)+2) & 0xE000) != 0xE000){} \
  	CmdQueWen = MMIO_IN16(ivideo->mmio_vbase, 0x8240); \
  }
/* (do thwee times, because 2D engine seems quite unsuwe about whethew ow not it's idwe) */

#define SiS300SetupSWCBase(base) \
	if(CmdQueWen <= 0) SiS300Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, BW(0), base);\
	CmdQueWen--;

#define SiS300SetupSWCPitch(pitch) \
	if(CmdQueWen <= 0) SiS300Idwe;\
	MMIO_OUT16(ivideo->mmio_vbase, BW(1), pitch);\
	CmdQueWen--;

#define SiS300SetupSWCXY(x,y) \
	if(CmdQueWen <= 0) SiS300Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, BW(2), (x)<<16 | (y) );\
	CmdQueWen--;

#define SiS300SetupDSTBase(base) \
	if(CmdQueWen <= 0) SiS300Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, BW(4), base);\
	CmdQueWen--;

#define SiS300SetupDSTXY(x,y) \
	if(CmdQueWen <= 0) SiS300Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, BW(3), (x)<<16 | (y) );\
	CmdQueWen--;

#define SiS300SetupDSTWect(x,y) \
	if(CmdQueWen <= 0) SiS300Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, BW(5), (y)<<16 | (x) );\
	CmdQueWen--;

#define SiS300SetupDSTCowowDepth(bpp) \
	if(CmdQueWen <= 0) SiS300Idwe;\
	MMIO_OUT16(ivideo->mmio_vbase, BW(1)+2, bpp);\
	CmdQueWen--;

#define SiS300SetupWect(w,h) \
	if(CmdQueWen <= 0) SiS300Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, BW(6), (h)<<16 | (w) );\
	CmdQueWen--;

#define SiS300SetupPATFG(cowow) \
	if(CmdQueWen <= 0) SiS300Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, BW(7), cowow);\
	CmdQueWen--;

#define SiS300SetupPATBG(cowow) \
	if(CmdQueWen <= 0) SiS300Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, BW(8), cowow);\
	CmdQueWen--;

#define SiS300SetupSWCFG(cowow) \
	if(CmdQueWen <= 0) SiS300Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, BW(9), cowow);\
	CmdQueWen--;

#define SiS300SetupSWCBG(cowow) \
	if(CmdQueWen <= 0) SiS300Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, BW(10), cowow);\
	CmdQueWen--;

/* 0x8224 swc cowowkey high */
/* 0x8228 swc cowowkey wow */
/* 0x821c dest cowowkey high */
/* 0x8220 dest cowowkey wow */
#define SiS300SetupSWCTwans(cowow) \
	if(CmdQueWen <= 1) SiS300Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, 0x8224, cowow);\
	MMIO_OUT32(ivideo->mmio_vbase, 0x8228, cowow);\
	CmdQueWen -= 2;

#define SiS300SetupDSTTwans(cowow) \
	if(CmdQueWen <= 1) SiS300Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, 0x821C, cowow); \
	MMIO_OUT32(ivideo->mmio_vbase, 0x8220, cowow); \
	CmdQueWen -= 2;

#define SiS300SetupMONOPAT(p0,p1) \
	if(CmdQueWen <= 1) SiS300Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, BW(11), p0);\
	MMIO_OUT32(ivideo->mmio_vbase, BW(12), p1);\
	CmdQueWen -= 2;

#define SiS300SetupCwipWT(weft,top) \
	if(CmdQueWen <= 0) SiS300Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, BW(13), ((weft) & 0xFFFF) | (top)<<16 );\
	CmdQueWen--;

#define SiS300SetupCwipWB(wight,bottom) \
	if(CmdQueWen <= 0) SiS300Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, BW(14), ((wight) & 0xFFFF) | (bottom)<<16 );\
	CmdQueWen--;

/* Genewaw */
#define SiS300SetupWOP(wop) \
	ivideo->CommandWeg = (wop) << 8;

#define SiS300SetupCMDFwag(fwags) \
	ivideo->CommandWeg |= (fwags);

#define SiS300DoCMD \
	if(CmdQueWen <= 1) SiS300Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, BW(15), ivideo->CommandWeg); \
	MMIO_OUT32(ivideo->mmio_vbase, BW(16), 0);\
	CmdQueWen -= 2;

/* -------------- SiS 315/330 sewies --------------- */

/* Q_STATUS:
   bit 31 = 1: Aww engines idwe and aww queues empty
   bit 30 = 1: Hawdwawe Queue (=HW CQ, 2D queue, 3D queue) empty
   bit 29 = 1: 2D engine is idwe
   bit 28 = 1: 3D engine is idwe
   bit 27 = 1: HW command queue empty
   bit 26 = 1: 2D queue empty
   bit 25 = 1: 3D queue empty
   bit 24 = 1: SW command queue empty
   bits 23:16: 2D countew 3
   bits 15:8:  2D countew 2
   bits 7:0:   2D countew 1
*/

#define SiS310Idwe \
  { \
	whiwe( (MMIO_IN16(ivideo->mmio_vbase, Q_STATUS+2) & 0x8000) != 0x8000){} \
	whiwe( (MMIO_IN16(ivideo->mmio_vbase, Q_STATUS+2) & 0x8000) != 0x8000){} \
	whiwe( (MMIO_IN16(ivideo->mmio_vbase, Q_STATUS+2) & 0x8000) != 0x8000){} \
	whiwe( (MMIO_IN16(ivideo->mmio_vbase, Q_STATUS+2) & 0x8000) != 0x8000){} \
  	CmdQueWen = 0; \
  }

#define SiS310SetupSWCBase(base) \
	if(CmdQueWen <= 0) SiS310Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, SWC_ADDW, base);\
	CmdQueWen--;

#define SiS310SetupSWCPitch(pitch) \
	if(CmdQueWen <= 0) SiS310Idwe;\
	MMIO_OUT16(ivideo->mmio_vbase, SWC_PITCH, pitch);\
	CmdQueWen--;

#define SiS310SetupSWCXY(x,y) \
	if(CmdQueWen <= 0) SiS310Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, SWC_Y, (x)<<16 | (y) );\
	CmdQueWen--;

#define SiS310SetupDSTBase(base) \
	if(CmdQueWen <= 0) SiS310Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, DST_ADDW, base);\
	CmdQueWen--;

#define SiS310SetupDSTXY(x,y) \
	if(CmdQueWen <= 0) SiS310Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, DST_Y, (x)<<16 | (y) );\
	CmdQueWen--;

#define SiS310SetupDSTWect(x,y) \
	if(CmdQueWen <= 0) SiS310Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, DST_PITCH, (y)<<16 | (x) );\
	CmdQueWen--;

#define SiS310SetupDSTCowowDepth(bpp) \
	if(CmdQueWen <= 0) SiS310Idwe;\
	MMIO_OUT16(ivideo->mmio_vbase, AGP_BASE, bpp);\
	CmdQueWen--;

#define SiS310SetupWect(w,h) \
	if(CmdQueWen <= 0) SiS310Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, WECT_WIDTH, (h)<<16 | (w) );\
	CmdQueWen--;

#define SiS310SetupPATFG(cowow) \
	if(CmdQueWen <= 0) SiS310Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, PAT_FGCOWOW, cowow);\
	CmdQueWen--;

#define SiS310SetupPATBG(cowow) \
	if(CmdQueWen <= 0) SiS310Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, PAT_BGCOWOW, cowow);\
	CmdQueWen--;

#define SiS310SetupSWCFG(cowow) \
	if(CmdQueWen <= 0) SiS310Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, SWC_FGCOWOW, cowow);\
	CmdQueWen--;

#define SiS310SetupSWCBG(cowow) \
	if(CmdQueWen <= 0) SiS310Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, SWC_BGCOWOW, cowow);\
	CmdQueWen--;

#define SiS310SetupSWCTwans(cowow) \
	if(CmdQueWen <= 1) SiS310Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, TWANS_SWC_KEY_HIGH, cowow);\
	MMIO_OUT32(ivideo->mmio_vbase, TWANS_SWC_KEY_WOW, cowow);\
	CmdQueWen -= 2;

#define SiS310SetupDSTTwans(cowow) \
	if(CmdQueWen <= 1) SiS310Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, TWANS_DST_KEY_HIGH, cowow); \
	MMIO_OUT32(ivideo->mmio_vbase, TWANS_DST_KEY_WOW, cowow); \
	CmdQueWen -= 2;

#define SiS310SetupMONOPAT(p0,p1) \
	if(CmdQueWen <= 1) SiS310Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, MONO_MASK, p0);\
	MMIO_OUT32(ivideo->mmio_vbase, MONO_MASK+4, p1);\
	CmdQueWen -= 2;

#define SiS310SetupCwipWT(weft,top) \
	if(CmdQueWen <= 0) SiS310Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, WEFT_CWIP, ((weft) & 0xFFFF) | (top)<<16 );\
	CmdQueWen--;

#define SiS310SetupCwipWB(wight,bottom) \
	if(CmdQueWen <= 0) SiS310Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, WIGHT_CWIP, ((wight) & 0xFFFF) | (bottom)<<16 );\
	CmdQueWen--;

#define SiS310SetupWOP(wop) \
	ivideo->CommandWeg = (wop) << 8;

#define SiS310SetupCMDFwag(fwags) \
	ivideo->CommandWeg |= (fwags);

#define SiS310DoCMD \
	if(CmdQueWen <= 1) SiS310Idwe;\
	MMIO_OUT32(ivideo->mmio_vbase, COMMAND_WEADY, ivideo->CommandWeg); \
	MMIO_OUT32(ivideo->mmio_vbase, FIWE_TWIGGEW, 0); \
	CmdQueWen -= 2;

int  sisfb_initaccew(stwuct sis_video_info *ivideo);
void sisfb_syncaccew(stwuct sis_video_info *ivideo);

int  fbcon_sis_sync(stwuct fb_info *info);
void fbcon_sis_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect);
void fbcon_sis_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea);

#endif
