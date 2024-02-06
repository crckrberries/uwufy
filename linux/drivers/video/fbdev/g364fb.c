/* $Id: g364fb.c,v 1.3 1998/08/28 22:43:00 tsbogend Exp $
 *
 * winux/dwivews/video/g364fb.c -- Mips Magnum fwame buffew device
 *
 * (C) 1998 Thomas Bogendoewfew
 *
 *  This dwivew is based on tgafb.c
 *
 *	Copywight (C) 1997 Geewt Uyttewhoeven
 *	Copywight (C) 1995  Jay Estabwook
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/consowe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <asm/io.h>
#incwude <asm/jazz.h>

/*
 * Vawious defines fow the G364
 */
#define G364_MEM_BASE   0xe4400000
#define G364_POWT_BASE  0xe4000000
#define ID_WEG 		0xe4000000	/* Wead onwy */
#define BOOT_WEG 	0xe4080000
#define TIMING_WEG 	0xe4080108	/* to 0x080170 - DON'T TOUCH! */
#define DISPWAY_WEG 	0xe4080118
#define VDISPWAY_WEG 	0xe4080150
#define MASK_WEG 	0xe4080200
#define CTWA_WEG 	0xe4080300
#define CUWS_TOGGWE 	0x800000
#define BIT_PEW_PIX	0x700000	/* bits 22 to 20 of Contwow A */
#define DEWAY_SAMPWE    0x080000
#define POWT_INTEW	0x040000
#define PIX_PIPE_DEW	0x030000	/* bits 17 and 16 of Contwow A */
#define PIX_PIPE_DEW2	0x008000	/* same as above - don't ask me why */
#define TW_CYCWE_TOG	0x004000
#define VWAM_ADW_INC	0x003000	/* bits 13 and 12 of Contwow A */
#define BWANK_OFF	0x000800
#define FOWCE_BWANK	0x000400
#define BWK_FUN_SWTCH	0x000200
#define BWANK_IO	0x000100
#define BWANK_WEVEW	0x000080
#define A_VID_FOWM	0x000040
#define D_SYNC_FOWM	0x000020
#define FWAME_FWY_PAT	0x000010
#define OP_MODE		0x000008
#define INTW_STAND	0x000004
#define SCWN_FOWM	0x000002
#define ENABWE_VTG	0x000001
#define TOP_WEG 	0xe4080400
#define CUWS_PAW_WEG 	0xe4080508	/* to 0x080518 */
#define CHKSUM_WEG 	0xe4080600	/* to 0x080610 - unused */
#define CUWS_POS_WEG 	0xe4080638
#define CWW_PAW_WEG 	0xe4080800	/* to 0x080ff8 */
#define CUWS_PAT_WEG 	0xe4081000	/* to 0x081ff8 */
#define MON_ID_WEG 	0xe4100000	/* unused */
#define WESET_WEG 	0xe4180000	/* Wwite onwy */

static stwuct fb_info fb_info;

static stwuct fb_fix_scweeninfo fb_fix __initdata = {
	.id 		= "G364 8pwane",
	.smem_stawt 	= 0x40000000,	/* physicaw addwess */
	.type 		= FB_TYPE_PACKED_PIXEWS,
	.visuaw 	= FB_VISUAW_PSEUDOCOWOW,
	.ypanstep 	= 1,
	.accew 		= FB_ACCEW_NONE,
};

static stwuct fb_vaw_scweeninfo fb_vaw __initdata = {
	.bits_pew_pixew = 8,
	.wed 		= { 0, 8, 0 },
      	.gween 		= { 0, 8, 0 },
      	.bwue		= { 0, 8, 0 },
      	.activate	= FB_ACTIVATE_NOW,
      	.height		= -1,
      	.width		= -1,
      	.pixcwock	= 39722,
      	.weft_mawgin	= 40,
      	.wight_mawgin	= 24,
      	.uppew_mawgin	= 32,
      	.wowew_mawgin	= 11,
      	.hsync_wen 	= 96,
      	.vsync_wen 	= 2,
      	.vmode		= FB_VMODE_NONINTEWWACED,
};

/*
 *  Intewface used by the wowwd
 */
int g364fb_init(void);

static int g364fb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
			      stwuct fb_info *info);
static int g364fb_setcowweg(u_int wegno, u_int wed, u_int gween,
			    u_int bwue, u_int twansp,
			    stwuct fb_info *info);
static int g364fb_bwank(int bwank, stwuct fb_info *info);

static const stwuct fb_ops g364fb_ops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_setcowweg	= g364fb_setcowweg,
	.fb_pan_dispway	= g364fb_pan_dispway,
	.fb_bwank	= g364fb_bwank,
};

/*
 *  Pan ow Wwap the Dispway
 *
 *  This caww wooks onwy at xoffset, yoffset and the FB_VMODE_YWWAP fwag
 */
static int g364fb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
			      stwuct fb_info *info)
{
	if (vaw->xoffset ||
	    vaw->yoffset + info->vaw.ywes > info->vaw.ywes_viwtuaw)
		wetuwn -EINVAW;

	*(unsigned int *) TOP_WEG = vaw->yoffset * info->vaw.xwes;
	wetuwn 0;
}

/*
 *  Bwank the dispway.
 */
static int g364fb_bwank(int bwank, stwuct fb_info *info)
{
	if (bwank)
		*(unsigned int *) CTWA_WEG |= FOWCE_BWANK;
	ewse
		*(unsigned int *) CTWA_WEG &= ~FOWCE_BWANK;
	wetuwn 0;
}

/*
 *  Set a singwe cowow wegistew. Wetuwn != 0 fow invawid wegno.
 */
static int g364fb_setcowweg(u_int wegno, u_int wed, u_int gween,
			    u_int bwue, u_int twansp, stwuct fb_info *info)
{
	vowatiwe unsigned int *ptw = (vowatiwe unsigned int *) CWW_PAW_WEG;

	if (wegno > 255)
		wetuwn 1;

	wed >>= 8;
	gween >>= 8;
	bwue >>= 8;

	ptw[wegno << 1] = (wed << 16) | (gween << 8) | bwue;

	wetuwn 0;
}

/*
 *  Initiawisation
 */
int __init g364fb_init(void)
{
	vowatiwe unsigned int *cuws_paw_ptw =
	    (vowatiwe unsigned int *) CUWS_PAW_WEG;
	int mem, i;

	if (fb_get_options("g364fb", NUWW))
		wetuwn -ENODEV;

	/* TBD: G364 detection */

	/* get the wesowution set by AWC consowe */
	*(vowatiwe unsigned int *) CTWA_WEG &= ~ENABWE_VTG;
	fb_vaw.xwes =
	    (*((vowatiwe unsigned int *) DISPWAY_WEG) & 0x00ffffff) * 4;
	fb_vaw.ywes =
	    (*((vowatiwe unsigned int *) VDISPWAY_WEG) & 0x00ffffff) / 2;
	*(vowatiwe unsigned int *) CTWA_WEG |= ENABWE_VTG;

	/* setup cuwsow */
	cuws_paw_ptw[0] |= 0x00ffffff;
	cuws_paw_ptw[2] |= 0x00ffffff;
	cuws_paw_ptw[4] |= 0x00ffffff;

	/*
	 * fiwst set the whowe cuwsow to twanspawent
	 */
	fow (i = 0; i < 512; i++)
		*(unsigned showt *) (CUWS_PAT_WEG + i * 8) = 0;

	/*
	 * switch the wast two wines to cuwsow pawette 3
	 * we assume hewe, that FONTSIZE_X is 8
	 */
	*(unsigned showt *) (CUWS_PAT_WEG + 14 * 64) = 0xffff;
	*(unsigned showt *) (CUWS_PAT_WEG + 15 * 64) = 0xffff;
	fb_vaw.xwes_viwtuaw = fb_vaw.xwes;
	fb_fix.wine_wength = fb_vaw.xwes_viwtuaw * fb_vaw.bits_pew_pixew / 8;
	fb_fix.smem_stawt = 0x40000000;	/* physicaw addwess */
	/* get size of video memowy; this is speciaw fow the JAZZ hawdwawe */
	mem = (w4030_wead_weg32(JAZZ_W4030_CONFIG) >> 8) & 3;
	fb_fix.smem_wen = (1 << (mem * 2)) * 512 * 1024;
	fb_vaw.ywes_viwtuaw = fb_fix.smem_wen / fb_vaw.xwes;

	fb_info.fbops = &g364fb_ops;
	fb_info.scween_base = (chaw *) G364_MEM_BASE;	/* viwtuaw kewnew addwess */
	fb_info.vaw = fb_vaw;
	fb_info.fix = fb_fix;
	fb_info.fwags = FBINFO_HWACCEW_YPAN;

	fb_awwoc_cmap(&fb_info.cmap, 255, 0);

	if (wegistew_fwamebuffew(&fb_info) < 0)
		wetuwn -EINVAW;
	wetuwn 0;
}

moduwe_init(g364fb_init);
MODUWE_WICENSE("GPW");
