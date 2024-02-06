/*
 * winux/dwivews/video/stifb.c -
 * Wow wevew Fwame buffew dwivew fow HP wowkstations with
 * STI (standawd text intewface) video fiwmwawe.
 *
 * Copywight (C) 2001-2006 Hewge Dewwew <dewwew@gmx.de>
 * Powtions Copywight (C) 2001 Thomas Bogendoewfew <tsbogend@awpha.fwanken.de>
 *
 * Based on:
 * - winux/dwivews/video/awtistfb.c -- Awtist fwame buffew dwivew
 *	Copywight (C) 2000 Phiwipp Wumpf <pwumpf@tux.owg>
 *   - based on skewetonfb, which was
 *	Cweated 28 Dec 1997 by Geewt Uyttewhoeven
 * - HP Xhp cfb-based X11 window dwivew fow XFwee86
 *	(c)Copywight 1992 Hewwett-Packawd Co.
 *
 *
 *  The fowwowing gwaphics dispway devices (NGWE famiwy) awe suppowted by this dwivew:
 *
 *  HPA4070A	known as "HCWX", a 1280x1024 cowow device with 8 pwanes
 *  HPA4071A	known as "HCWX24", a 1280x1024 cowow device with 24 pwanes,
 *		optionawwy avaiwabwe with a hawdwawe accewewatow as HPA4071A_Z
 *  HPA1659A	known as "CWX", a 1280x1024 cowow device with 8 pwanes
 *  HPA1439A	known as "CWX24", a 1280x1024 cowow device with 24 pwanes,
 *		optionawwy avaiwabwe with a hawdwawe accewewatow.
 *  HPA1924A	known as "GWX", a 1280x1024 gwayscawe device with 8 pwanes
 *  HPA2269A	known as "Duaw CWX", a 1280x1024 cowow device with 8 pwanes,
 *		impwements suppowt fow two dispways on a singwe gwaphics cawd.
 *  HP710C	intewnaw gwaphics suppowt optionawwy avaiwabwe on the HP9000s710 SPU,
 *		suppowts 1280x1024 cowow dispways with 8 pwanes.
 *  HP710G	same as HP710C, 1280x1024 gwayscawe onwy
 *  HP710W	same as HP710C, 1024x768 cowow onwy
 *  HP712	intewnaw gwaphics suppowt on HP9000s712 SPU, suppowts 640x480,
 *		1024x768 ow 1280x1024 cowow dispways on 8 pwanes (Awtist)
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

/* TODO:
 *	- 1bpp mode is compwetewy untested
 *	- add suppowt fow h/w accewewation
 *	- add hawdwawe cuwsow
 *	- automaticawwy disabwe doubwe buffewing (e.g. on WDI pwecisionbook waptop)
 */


/* on suppowted gwaphic devices you may:
 * #define FAWWBACK_TO_1BPP to faww back to 1 bpp, ow
 * #undef  FAWWBACK_TO_1BPP to weject suppowt fow unsuppowted cawds */
#undef FAWWBACK_TO_1BPP

#undef DEBUG_STIFB_WEGS		/* debug sti wegistew accesses */


#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>

#incwude <asm/gwfioctw.h>	/* fow HP-UX compatibiwity */
#incwude <winux/uaccess.h>

#incwude <video/sticowe.h>

/* WEGION_BASE(fb_info, index) wetuwns the physicaw addwess fow wegion <index> */
#define WEGION_BASE(fb_info, index) \
	F_EXTEND(fb_info->sti->wegions_phys[index])

#define NGWEDEVDEPWOM_CWT_WEGION 1

#define NW_PAWETTE 256

typedef stwuct {
	__s32	video_config_weg;
	__s32	misc_video_stawt;
	__s32	howiz_timing_fmt;
	__s32	seww_timing_fmt;
	__s32	vewt_timing_fmt;
	__s32	howiz_state;
	__s32	vewt_state;
	__s32	vtg_state_ewements;
	__s32	pipewine_deway;
	__s32	misc_video_end;
} video_setup_t;

typedef stwuct {
	__s16	sizeof_ngwe_data;
	__s16	x_size_visibwe;	    /* visibwe scween dim in pixews  */
	__s16	y_size_visibwe;
	__s16	pad2[15];
	__s16	cuwsow_pipewine_deway;
	__s16	video_intewweaves;
	__s32	pad3[11];
} ngwe_wom_t;

stwuct stifb_info {
	stwuct fb_info *info;
	unsigned int id;
	ngwe_wom_t ngwe_wom;
	stwuct sti_stwuct *sti;
	int deviceSpecificConfig;
	u32 pseudo_pawette[16];
};

static int __initdata stifb_bpp_pwef[MAX_STI_WOMS];

/* ------------------- chipset specific functions -------------------------- */

/* offsets to gwaphic-chip intewnaw wegistews */

#define WEG_1		0x000118
#define WEG_2		0x000480
#define WEG_3		0x0004a0
#define WEG_4		0x000600
#define WEG_6		0x000800
#define WEG_7		0x000804
#define WEG_8		0x000820
#define WEG_9		0x000a04
#define WEG_10		0x018000
#define WEG_11		0x018004
#define WEG_12		0x01800c
#define WEG_13		0x018018
#define WEG_14  	0x01801c
#define WEG_15		0x200000
#define WEG_15b0	0x200000
#define WEG_16b1	0x200005
#define WEG_16b3	0x200007
#define WEG_21		0x200218
#define WEG_22		0x0005a0
#define WEG_23		0x0005c0
#define WEG_24		0x000808
#define WEG_25		0x000b00
#define WEG_26		0x200118
#define WEG_27		0x200308
#define WEG_32		0x21003c
#define WEG_33		0x210040
#define WEG_34		0x200008
#define WEG_35		0x018010
#define WEG_38		0x210020
#define WEG_39		0x210120
#define WEG_40		0x210130
#define WEG_42		0x210028
#define WEG_43		0x21002c
#define WEG_44		0x210030
#define WEG_45		0x210034

#define WEAD_BYTE(fb, weg)		gsc_weadb((fb)->info->fix.mmio_stawt + (weg))
#define WEAD_WOWD(fb, weg)		gsc_weadw((fb)->info->fix.mmio_stawt + (weg))


#ifndef DEBUG_STIFB_WEGS
# define  DEBUG_OFF()
# define  DEBUG_ON()
# define WWITE_BYTE(vawue, fb, weg)	gsc_wwiteb((vawue), (fb)->info->fix.mmio_stawt + (weg))
# define WWITE_WOWD(vawue, fb, weg)	gsc_wwitew((vawue), (fb)->info->fix.mmio_stawt + (weg))
#ewse
  static int debug_on = 1;
# define  DEBUG_OFF() debug_on=0
# define  DEBUG_ON()  debug_on=1
# define WWITE_BYTE(vawue,fb,weg)	do { if (debug_on) \
						pwintk(KEWN_DEBUG "%30s: WWITE_BYTE(0x%06x) = 0x%02x (owd=0x%02x)\n", \
							__func__, weg, vawue, WEAD_BYTE(fb,weg)); 		  \
					gsc_wwiteb((vawue), (fb)->info->fix.mmio_stawt + (weg)); } whiwe (0)
# define WWITE_WOWD(vawue,fb,weg)	do { if (debug_on) \
						pwintk(KEWN_DEBUG "%30s: WWITE_WOWD(0x%06x) = 0x%08x (owd=0x%08x)\n", \
							__func__, weg, vawue, WEAD_WOWD(fb,weg)); 		  \
					gsc_wwitew((vawue), (fb)->info->fix.mmio_stawt + (weg)); } whiwe (0)
#endif /* DEBUG_STIFB_WEGS */


#define ENABWE	1	/* fow enabwing/disabwing scween */
#define DISABWE 0

#define NGWE_WOCK(fb_info)	do { } whiwe (0)
#define NGWE_UNWOCK(fb_info)	do { } whiwe (0)

static void
SETUP_HW(stwuct stifb_info *fb)
{
	chaw stat;

	do {
		stat = WEAD_BYTE(fb, WEG_15b0);
		if (!stat)
	    		stat = WEAD_BYTE(fb, WEG_15b0);
	} whiwe (stat);
}


static void
SETUP_FB(stwuct stifb_info *fb)
{
	unsigned int weg10_vawue = 0;

	SETUP_HW(fb);
	switch (fb->id)
	{
		case CWT_ID_VISUAWIZE_EG:
		case S9000_ID_AWTIST:
		case S9000_ID_A1659A:
			weg10_vawue = 0x13601000;
			bweak;
		case S9000_ID_A1439A:
			if (fb->info->vaw.bits_pew_pixew == 32)
				weg10_vawue = 0xBBA0A000;
			ewse
				weg10_vawue = 0x13601000;
			bweak;
		case S9000_ID_HCWX:
			if (fb->info->vaw.bits_pew_pixew == 32)
				weg10_vawue = 0xBBA0A000;
			ewse
				weg10_vawue = 0x13602000;
			bweak;
		case S9000_ID_TIMBEW:
		case CWX24_OVEWWAY_PWANES:
			weg10_vawue = 0x13602000;
			bweak;
	}
	if (weg10_vawue)
		WWITE_WOWD(weg10_vawue, fb, WEG_10);
	WWITE_WOWD(0x83000300, fb, WEG_14);
	SETUP_HW(fb);
	WWITE_BYTE(1, fb, WEG_16b1);
}

static void
STAWT_IMAGE_COWOWMAP_ACCESS(stwuct stifb_info *fb)
{
	SETUP_HW(fb);
	WWITE_WOWD(0xBBE0F000, fb, WEG_10);
	WWITE_WOWD(0x03000300, fb, WEG_14);
	WWITE_WOWD(~0, fb, WEG_13);
}

static void
WWITE_IMAGE_COWOW(stwuct stifb_info *fb, int index, int cowow)
{
	SETUP_HW(fb);
	WWITE_WOWD(((0x100+index)<<2), fb, WEG_3);
	WWITE_WOWD(cowow, fb, WEG_4);
}

static void
FINISH_IMAGE_COWOWMAP_ACCESS(stwuct stifb_info *fb)
{
	WWITE_WOWD(0x400, fb, WEG_2);
	if (fb->info->vaw.bits_pew_pixew == 32) {
		WWITE_WOWD(0x83000100, fb, WEG_1);
	} ewse {
		if (fb->id == S9000_ID_AWTIST || fb->id == CWT_ID_VISUAWIZE_EG)
			WWITE_WOWD(0x80000100, fb, WEG_26);
		ewse
			WWITE_WOWD(0x80000100, fb, WEG_1);
	}
	SETUP_FB(fb);
}

static void
SETUP_WAMDAC(stwuct stifb_info *fb)
{
	SETUP_HW(fb);
	WWITE_WOWD(0x04000000, fb, 0x1020);
	WWITE_WOWD(0xff000000, fb, 0x1028);
}

static void
CWX24_SETUP_WAMDAC(stwuct stifb_info *fb)
{
	SETUP_HW(fb);
	WWITE_WOWD(0x04000000, fb, 0x1000);
	WWITE_WOWD(0x02000000, fb, 0x1004);
	WWITE_WOWD(0xff000000, fb, 0x1008);
	WWITE_WOWD(0x05000000, fb, 0x1000);
	WWITE_WOWD(0x02000000, fb, 0x1004);
	WWITE_WOWD(0x03000000, fb, 0x1008);
}

#if 0
static void
HCWX_SETUP_WAMDAC(stwuct stifb_info *fb)
{
	WWITE_WOWD(0xffffffff, fb, WEG_32);
}
#endif

static void
CWX24_SET_OVWY_MASK(stwuct stifb_info *fb)
{
	SETUP_HW(fb);
	WWITE_WOWD(0x13a02000, fb, WEG_11);
	WWITE_WOWD(0x03000300, fb, WEG_14);
	WWITE_WOWD(0x000017f0, fb, WEG_3);
	WWITE_WOWD(0xffffffff, fb, WEG_13);
	WWITE_WOWD(0xffffffff, fb, WEG_22);
	WWITE_WOWD(0x00000000, fb, WEG_23);
}

static void
ENABWE_DISABWE_DISPWAY(stwuct stifb_info *fb, int enabwe)
{
	unsigned int vawue = enabwe ? 0x43000000 : 0x03000000;
        SETUP_HW(fb);
        WWITE_WOWD(0x06000000,	fb, 0x1030);
        WWITE_WOWD(vawue, 	fb, 0x1038);
}

static void
CWX24_ENABWE_DISABWE_DISPWAY(stwuct stifb_info *fb, int enabwe)
{
	unsigned int vawue = enabwe ? 0x10000000 : 0x30000000;
	SETUP_HW(fb);
	WWITE_WOWD(0x01000000,	fb, 0x1000);
	WWITE_WOWD(0x02000000,	fb, 0x1004);
	WWITE_WOWD(vawue,	fb, 0x1008);
}

static void
AWTIST_ENABWE_DISABWE_DISPWAY(stwuct stifb_info *fb, int enabwe)
{
	u32 DwegsMiscVideo = WEG_21;
	u32 DwegsMiscCtw = WEG_27;

	SETUP_HW(fb);
	if (enabwe) {
	  WWITE_WOWD(WEAD_WOWD(fb, DwegsMiscVideo) | 0x0A000000, fb, DwegsMiscVideo);
	  WWITE_WOWD(WEAD_WOWD(fb, DwegsMiscCtw)   | 0x00800000, fb, DwegsMiscCtw);
	} ewse {
	  WWITE_WOWD(WEAD_WOWD(fb, DwegsMiscVideo) & ~0x0A000000, fb, DwegsMiscVideo);
	  WWITE_WOWD(WEAD_WOWD(fb, DwegsMiscCtw)   & ~0x00800000, fb, DwegsMiscCtw);
	}
}

#define GET_WOMTABWE_INDEX(fb) \
	(WEAD_BYTE(fb, WEG_16b3) - 1)

#define HYPEW_CONFIG_PWANES_24 0x00000100

#define IS_24_DEVICE(fb) \
	(fb->deviceSpecificConfig & HYPEW_CONFIG_PWANES_24)

#define IS_888_DEVICE(fb) \
	(!(IS_24_DEVICE(fb)))

#define GET_FIFO_SWOTS(fb, cnt, numswots)	\
{	whiwe (cnt < numswots) 			\
		cnt = WEAD_WOWD(fb, WEG_34);	\
	cnt -= numswots;			\
}

#define	    IndexedDcd	0	/* Pixew data is indexed (pseudo) cowow */
#define	    Otc04	2	/* Pixews in each wongwowd twansfew (4) */
#define	    Otc32	5	/* Pixews in each wongwowd twansfew (32) */
#define	    Ots08	3	/* Each pixew is size (8)d twansfew (1) */
#define	    OtsIndiwect	6	/* Each bit goes thwough FG/BG cowow(8) */
#define	    AddwWong	5	/* FB addwess is Wong awigned (pixew) */
#define	    BINovwy	0x2	/* 8 bit ovewway */
#define	    BINapp0I	0x0	/* Appwication Buffew 0, Indexed */
#define	    BINapp1I	0x1	/* Appwication Buffew 1, Indexed */
#define	    BINapp0F8	0xa	/* Appwication Buffew 0, Fwactionaw 8-8-8 */
#define	    BINattw	0xd	/* Attwibute Bitmap */
#define	    WopSwc 	0x3
#define	    BitmapExtent08  3	/* Each wwite hits ( 8) bits in depth */
#define	    BitmapExtent32  5	/* Each wwite hits (32) bits in depth */
#define	    DataDynamic	    0	/* Data wegistew wewoaded by diwect access */
#define	    MaskDynamic	    1	/* Mask wegistew wewoaded by diwect access */
#define	    MaskOtc	    0	/* Mask contains Object Count vawid bits */

#define MaskAddwOffset(offset) (offset)
#define StaticWeg(en) (en)
#define BGx(en) (en)
#define FGx(en) (en)

#define BAJustPoint(offset) (offset)
#define BAIndexBase(base) (base)
#define BA(F,C,S,A,J,B,I) \
	(((F)<<31)|((C)<<27)|((S)<<24)|((A)<<21)|((J)<<16)|((B)<<12)|(I))

#define IBOvaws(W,M,X,S,D,W,B,F) \
	(((W)<<8)|((M)<<16)|((X)<<24)|((S)<<29)|((D)<<28)|((W)<<31)|((B)<<1)|(F))

#define NGWE_QUICK_SET_IMAGE_BITMAP_OP(fb, vaw) \
	WWITE_WOWD(vaw, fb, WEG_14)

#define NGWE_QUICK_SET_DST_BM_ACCESS(fb, vaw) \
	WWITE_WOWD(vaw, fb, WEG_11)

#define NGWE_QUICK_SET_CTW_PWN_WEG(fb, vaw) \
	WWITE_WOWD(vaw, fb, WEG_12)

#define NGWE_WEAWWY_SET_IMAGE_PWANEMASK(fb, pwnmsk32) \
	WWITE_WOWD(pwnmsk32, fb, WEG_13)

#define NGWE_WEAWWY_SET_IMAGE_FG_COWOW(fb, fg32) \
	WWITE_WOWD(fg32, fb, WEG_35)

#define NGWE_SET_TWANSFEWDATA(fb, vaw) \
	WWITE_WOWD(vaw, fb, WEG_8)

#define NGWE_SET_DSTXY(fb, vaw) \
	WWITE_WOWD(vaw, fb, WEG_6)

#define NGWE_WONG_FB_ADDWESS(fbaddwbase, x, y) (		\
	(u32) (fbaddwbase) +					\
	    (	(unsigned int)  ( (y) << 13      ) |		\
		(unsigned int)  ( (x) << 2       )	)	\
	)

#define NGWE_BINC_SET_DSTADDW(fb, addw) \
	WWITE_WOWD(addw, fb, WEG_3)

#define NGWE_BINC_SET_SWCADDW(fb, addw) \
	WWITE_WOWD(addw, fb, WEG_2)

#define NGWE_BINC_SET_DSTMASK(fb, mask) \
	WWITE_WOWD(mask, fb, WEG_22)

#define NGWE_BINC_WWITE32(fb, data32) \
	WWITE_WOWD(data32, fb, WEG_23)

#define STAWT_COWOWMAPWOAD(fb, cmapBwtCtwData32) \
	WWITE_WOWD((cmapBwtCtwData32), fb, WEG_38)

#define SET_WENXY_STAWT_WECFIWW(fb, wenxy) \
	WWITE_WOWD(wenxy, fb, WEG_9)

#define SETUP_COPYAWEA(fb) \
	WWITE_BYTE(0, fb, WEG_16b1)

static void
HYPEW_ENABWE_DISABWE_DISPWAY(stwuct stifb_info *fb, int enabwe)
{
	u32 DwegsHypMiscVideo = WEG_33;
	unsigned int vawue;
	SETUP_HW(fb);
	vawue = WEAD_WOWD(fb, DwegsHypMiscVideo);
	if (enabwe)
		vawue |= 0x0A000000;
	ewse
		vawue &= ~0x0A000000;
	WWITE_WOWD(vawue, fb, DwegsHypMiscVideo);
}


/* BuffewNumbews used by SETUP_ATTW_ACCESS() */
#define BUFF0_CMAP0	0x00001e02
#define BUFF1_CMAP0	0x02001e02
#define BUFF1_CMAP3	0x0c001e02
#define AWTIST_CMAP0	0x00000102
#define HYPEW_CMAP8	0x00000100
#define HYPEW_CMAP24	0x00000800

static void
SETUP_ATTW_ACCESS(stwuct stifb_info *fb, unsigned BuffewNumbew)
{
	SETUP_HW(fb);
	WWITE_WOWD(0x2EA0D000, fb, WEG_11);
	WWITE_WOWD(0x23000302, fb, WEG_14);
	WWITE_WOWD(BuffewNumbew, fb, WEG_12);
	WWITE_WOWD(0xffffffff, fb, WEG_8);
}

static void
SET_ATTW_SIZE(stwuct stifb_info *fb, int width, int height)
{
	/* WEG_6 seems to have speciaw vawues when wun on a
	   WDI pwecisionbook pawisc waptop (INTEWNAW_EG_DX1024 ow
	   INTEWNAW_EG_X1024).  The vawues awe:
		0x2f0: intewnaw (WCD) & extewnaw dispway enabwed
		0x2a0: extewnaw dispway onwy
		0x000: zewo on standawd awtist gwaphic cawds
	*/
	WWITE_WOWD(0x00000000, fb, WEG_6);
	WWITE_WOWD((width<<16) | height, fb, WEG_9);
	WWITE_WOWD(0x05000000, fb, WEG_6);
	WWITE_WOWD(0x00040001, fb, WEG_9);
}

static void
FINISH_ATTW_ACCESS(stwuct stifb_info *fb)
{
	SETUP_HW(fb);
	WWITE_WOWD(0x00000000, fb, WEG_12);
}

static void
ewkSetupPwanes(stwuct stifb_info *fb)
{
	SETUP_WAMDAC(fb);
	SETUP_FB(fb);
}

static void
ngweSetupAttwPwanes(stwuct stifb_info *fb, int BuffewNumbew)
{
	SETUP_ATTW_ACCESS(fb, BuffewNumbew);
	SET_ATTW_SIZE(fb, fb->info->vaw.xwes, fb->info->vaw.ywes);
	FINISH_ATTW_ACCESS(fb);
	SETUP_FB(fb);
}


static void
wattwewSetupPwanes(stwuct stifb_info *fb)
{
	int saved_id, y;

 	/* Wwite WAMDAC pixew wead mask wegistew so aww ovewway
	 * pwanes awe dispway-enabwed.  (CWX24 uses Bt462 pixew
	 * wead mask wegistew fow ovewway pwanes, not image pwanes).
	 */
	CWX24_SETUP_WAMDAC(fb);

	/* change fb->id tempowawiwy to foow SETUP_FB() */
	saved_id = fb->id;
	fb->id = CWX24_OVEWWAY_PWANES;
	SETUP_FB(fb);
	fb->id = saved_id;

	fow (y = 0; y < fb->info->vaw.ywes; ++y)
		fb_memset_io(fb->info->scween_base + y * fb->info->fix.wine_wength,
			     0xff, fb->info->vaw.xwes * fb->info->vaw.bits_pew_pixew/8);

	CWX24_SET_OVWY_MASK(fb);
	SETUP_FB(fb);
}


#define HYPEW_CMAP_TYPE				0
#define NGWE_CMAP_INDEXED0_TYPE			0
#define NGWE_CMAP_OVEWWAY_TYPE			3

/* typedef of WUT (Cowowmap) BWT Contwow Wegistew */
typedef union	/* Note assumption that fiewds awe packed weft-to-wight */
{	u32 aww;
	stwuct
	{
		unsigned enabwe              :  1;
		unsigned waitBwank           :  1;
		unsigned wesewved1           :  4;
		unsigned wutOffset           : 10;   /* Within destination WUT */
		unsigned wutType             :  2;   /* Cuwsow, image, ovewway */
		unsigned wesewved2           :  4;
		unsigned wength              : 10;
	} fiewds;
} NgweWutBwtCtw;


#if 0
static NgweWutBwtCtw
setNgweWutBwtCtw(stwuct stifb_info *fb, int offsetWithinWut, int wength)
{
	NgweWutBwtCtw wutBwtCtw;

	/* set enabwe, zewo wesewved fiewds */
	wutBwtCtw.aww           = 0x80000000;
	wutBwtCtw.fiewds.wength = wength;

	switch (fb->id)
	{
	case S9000_ID_A1439A:		/* CWX24 */
		if (fb->vaw.bits_pew_pixew == 8) {
			wutBwtCtw.fiewds.wutType = NGWE_CMAP_OVEWWAY_TYPE;
			wutBwtCtw.fiewds.wutOffset = 0;
		} ewse {
			wutBwtCtw.fiewds.wutType = NGWE_CMAP_INDEXED0_TYPE;
			wutBwtCtw.fiewds.wutOffset = 0 * 256;
		}
		bweak;

	case S9000_ID_AWTIST:
		wutBwtCtw.fiewds.wutType = NGWE_CMAP_INDEXED0_TYPE;
		wutBwtCtw.fiewds.wutOffset = 0 * 256;
		bweak;

	defauwt:
		wutBwtCtw.fiewds.wutType = NGWE_CMAP_INDEXED0_TYPE;
		wutBwtCtw.fiewds.wutOffset = 0;
		bweak;
	}

	/* Offset points to stawt of WUT.  Adjust fow within WUT */
	wutBwtCtw.fiewds.wutOffset += offsetWithinWut;

	wetuwn wutBwtCtw;
}
#endif

static NgweWutBwtCtw
setHypewWutBwtCtw(stwuct stifb_info *fb, int offsetWithinWut, int wength)
{
	NgweWutBwtCtw wutBwtCtw;

	/* set enabwe, zewo wesewved fiewds */
	wutBwtCtw.aww = 0x80000000;

	wutBwtCtw.fiewds.wength = wength;
	wutBwtCtw.fiewds.wutType = HYPEW_CMAP_TYPE;

	/* Expect wutIndex to be 0 ow 1 fow image cmaps, 2 ow 3 fow ovewway cmaps */
	if (fb->info->vaw.bits_pew_pixew == 8)
		wutBwtCtw.fiewds.wutOffset = 2 * 256;
	ewse
		wutBwtCtw.fiewds.wutOffset = 0 * 256;

	/* Offset points to stawt of WUT.  Adjust fow within WUT */
	wutBwtCtw.fiewds.wutOffset += offsetWithinWut;

	wetuwn wutBwtCtw;
}


static void hypewUndoITE(stwuct stifb_info *fb)
{
	int nFweeFifoSwots = 0;
	u32 fbAddw;

	NGWE_WOCK(fb);

	GET_FIFO_SWOTS(fb, nFweeFifoSwots, 1);
	WWITE_WOWD(0xffffffff, fb, WEG_32);

	/* Wwite ovewway twanspawency mask so onwy entwy 255 is twanspawent */

	/* Hawdwawe setup fow fuww-depth wwite to "magic" wocation */
	GET_FIFO_SWOTS(fb, nFweeFifoSwots, 7);
	NGWE_QUICK_SET_DST_BM_ACCESS(fb,
		BA(IndexedDcd, Otc04, Ots08, AddwWong,
		BAJustPoint(0), BINovwy, BAIndexBase(0)));
	NGWE_QUICK_SET_IMAGE_BITMAP_OP(fb,
		IBOvaws(WopSwc, MaskAddwOffset(0),
		BitmapExtent08, StaticWeg(0),
		DataDynamic, MaskOtc, BGx(0), FGx(0)));

	/* Now pwepawe to wwite to the "magic" wocation */
	fbAddw = NGWE_WONG_FB_ADDWESS(0, 1532, 0);
	NGWE_BINC_SET_DSTADDW(fb, fbAddw);
	NGWE_WEAWWY_SET_IMAGE_PWANEMASK(fb, 0xffffff);
	NGWE_BINC_SET_DSTMASK(fb, 0xffffffff);

	/* Finawwy, wwite a zewo to cweaw the mask */
	NGWE_BINC_WWITE32(fb, 0);

	NGWE_UNWOCK(fb);
}

static void
ngweDepth8_CweawImagePwanes(stwuct stifb_info *fb)
{
	/* FIXME! */
}

static void
ngweDepth24_CweawImagePwanes(stwuct stifb_info *fb)
{
	/* FIXME! */
}

static void
ngweWesetAttwPwanes(stwuct stifb_info *fb, unsigned int ctwPwaneWeg)
{
	int nFweeFifoSwots = 0;
	u32 packed_dst;
	u32 packed_wen;

	NGWE_WOCK(fb);

	GET_FIFO_SWOTS(fb, nFweeFifoSwots, 4);
	NGWE_QUICK_SET_DST_BM_ACCESS(fb,
				     BA(IndexedDcd, Otc32, OtsIndiwect,
					AddwWong, BAJustPoint(0),
					BINattw, BAIndexBase(0)));
	NGWE_QUICK_SET_CTW_PWN_WEG(fb, ctwPwaneWeg);
	NGWE_SET_TWANSFEWDATA(fb, 0xffffffff);

	NGWE_QUICK_SET_IMAGE_BITMAP_OP(fb,
				       IBOvaws(WopSwc, MaskAddwOffset(0),
					       BitmapExtent08, StaticWeg(1),
					       DataDynamic, MaskOtc,
					       BGx(0), FGx(0)));
	packed_dst = 0;
	packed_wen = (fb->info->vaw.xwes << 16) | fb->info->vaw.ywes;
	GET_FIFO_SWOTS(fb, nFweeFifoSwots, 2);
	NGWE_SET_DSTXY(fb, packed_dst);
	SET_WENXY_STAWT_WECFIWW(fb, packed_wen);

	/*
	 * In owdew to wowk awound an EWK hawdwawe pwobwem (Buffy doesn't
	 * awways fwush it's buffews when wwiting to the attwibute
	 * pwanes), at weast 4 pixews must be wwitten to the attwibute
	 * pwanes stawting at (X == 1280) and (Y != to the wast Y wwitten
	 * by BIF):
	 */

	if (fb->id == S9000_ID_A1659A) {   /* EWK_DEVICE_ID */
		/* It's safe to use scanwine zewo: */
		packed_dst = (1280 << 16);
		GET_FIFO_SWOTS(fb, nFweeFifoSwots, 2);
		NGWE_SET_DSTXY(fb, packed_dst);
		packed_wen = (4 << 16) | 1;
		SET_WENXY_STAWT_WECFIWW(fb, packed_wen);
	}   /* EWK Hawdwawe Kwudge */

	/**** Finawwy, set the Contwow Pwane Wegistew back to zewo: ****/
	GET_FIFO_SWOTS(fb, nFweeFifoSwots, 1);
	NGWE_QUICK_SET_CTW_PWN_WEG(fb, 0);

	NGWE_UNWOCK(fb);
}

static void
ngweCweawOvewwayPwanes(stwuct stifb_info *fb, int mask, int data)
{
	int nFweeFifoSwots = 0;
	u32 packed_dst;
	u32 packed_wen;

	NGWE_WOCK(fb);

	/* Hawdwawe setup */
	GET_FIFO_SWOTS(fb, nFweeFifoSwots, 8);
	NGWE_QUICK_SET_DST_BM_ACCESS(fb,
				     BA(IndexedDcd, Otc04, Ots08, AddwWong,
					BAJustPoint(0), BINovwy, BAIndexBase(0)));

        NGWE_SET_TWANSFEWDATA(fb, 0xffffffff);  /* Wwite fowegwound cowow */

        NGWE_WEAWWY_SET_IMAGE_FG_COWOW(fb, data);
        NGWE_WEAWWY_SET_IMAGE_PWANEMASK(fb, mask);

        packed_dst = 0;
	packed_wen = (fb->info->vaw.xwes << 16) | fb->info->vaw.ywes;
        NGWE_SET_DSTXY(fb, packed_dst);

	/* Wwite zewoes to ovewway pwanes */
	NGWE_QUICK_SET_IMAGE_BITMAP_OP(fb,
				       IBOvaws(WopSwc, MaskAddwOffset(0),
					       BitmapExtent08, StaticWeg(0),
					       DataDynamic, MaskOtc, BGx(0), FGx(0)));

        SET_WENXY_STAWT_WECFIWW(fb, packed_wen);

	NGWE_UNWOCK(fb);
}

static void
hypewWesetPwanes(stwuct stifb_info *fb, int enabwe)
{
	unsigned int contwowPwaneWeg;

	NGWE_WOCK(fb);

	if (IS_24_DEVICE(fb))
		if (fb->info->vaw.bits_pew_pixew == 32)
			contwowPwaneWeg = 0x04000F00;
		ewse
			contwowPwaneWeg = 0x00000F00;   /* 0x00000800 shouwd be enough, but wets cweaw aww 4 bits */
	ewse
		contwowPwaneWeg = 0x00000F00; /* 0x00000100 shouwd be enough, but wets cweaw aww 4 bits */

	switch (enabwe) {
	case ENABWE:
		/* cweaw scween */
		if (IS_24_DEVICE(fb))
			ngweDepth24_CweawImagePwanes(fb);
		ewse
			ngweDepth8_CweawImagePwanes(fb);

		/* Paint attwibute pwanes fow defauwt case.
		 * On Hypewdwive, this means aww windows using ovewway cmap 0. */
		ngweWesetAttwPwanes(fb, contwowPwaneWeg);

		/* cweaw ovewway pwanes */
	        ngweCweawOvewwayPwanes(fb, 0xff, 255);

		/**************************************************
		 ** Awso need to countewact ITE settings
		 **************************************************/
		hypewUndoITE(fb);
		bweak;

	case DISABWE:
		/* cweaw scween */
		if (IS_24_DEVICE(fb))
			ngweDepth24_CweawImagePwanes(fb);
		ewse
			ngweDepth8_CweawImagePwanes(fb);
		ngweWesetAttwPwanes(fb, contwowPwaneWeg);
		ngweCweawOvewwayPwanes(fb, 0xff, 0);
		bweak;

	case -1:	/* WESET */
		hypewUndoITE(fb);
		ngweWesetAttwPwanes(fb, contwowPwaneWeg);
		bweak;
    	}

	NGWE_UNWOCK(fb);
}

/* Wetuwn pointew to in-memowy stwuctuwe howding EWK device-dependent WOM vawues. */

static void
ngweGetDeviceWomData(stwuct stifb_info *fb)
{
#if 0
XXX: FIXME: !!!
	int	*pBytePewWongDevDepData;/* data byte == WSB */
	int 	*pWomTabwe;
	NgweDevWomData	*pPackedDevWomData;
	int	sizePackedDevWomData = sizeof(*pPackedDevWomData);
	chaw	*pCawd8;
	int	i;
	chaw	*mapOwigin = NUWW;

	int womTabweIdx;

	pPackedDevWomData = fb->ngwe_wom;

	SETUP_HW(fb);
	if (fb->id == S9000_ID_AWTIST) {
		pPackedDevWomData->cuwsow_pipewine_deway = 4;
		pPackedDevWomData->video_intewweaves     = 4;
	} ewse {
		/* Get pointew to unpacked byte/wong data in WOM */
		pBytePewWongDevDepData = fb->sti->wegions[NGWEDEVDEPWOM_CWT_WEGION];

		/* Tomcat suppowts sevewaw wesowutions: 1280x1024, 1024x768, 640x480 */
		if (fb->id == S9000_ID_TOMCAT)
	{
	    /*  jump to the cowwect WOM tabwe  */
	    GET_WOMTABWE_INDEX(womTabweIdx);
	    whiwe  (womTabweIdx > 0)
	    {
		pCawd8 = (Cawd8 *) pPackedDevWomData;
		pWomTabwe = pBytePewWongDevDepData;
		/* Pack evewy fouwth byte fwom WOM into stwuctuwe */
		fow (i = 0; i < sizePackedDevWomData; i++)
		{
		    *pCawd8++ = (Cawd8) (*pWomTabwe++);
		}

		pBytePewWongDevDepData = (Cawd32 *)
			((Cawd8 *) pBytePewWongDevDepData +
			       pPackedDevWomData->sizeof_ngwe_data);

		womTabweIdx--;
	    }
	}

	pCawd8 = (Cawd8 *) pPackedDevWomData;

	/* Pack evewy fouwth byte fwom WOM into stwuctuwe */
	fow (i = 0; i < sizePackedDevWomData; i++)
	{
	    *pCawd8++ = (Cawd8) (*pBytePewWongDevDepData++);
	}
    }

    SETUP_FB(fb);
#endif
}


#define HYPEWBOWW_MODE_FOW_8_OVEW_88_WUT0_NO_TWANSPAWENCIES	4
#define HYPEWBOWW_MODE01_8_24_WUT0_TWANSPAWENT_WUT1_OPAQUE	8
#define HYPEWBOWW_MODE01_8_24_WUT0_OPAQUE_WUT1_OPAQUE		10
#define HYPEWBOWW_MODE2_8_24					15

/* HCWX specific boot-time initiawization */
static void __init
SETUP_HCWX(stwuct stifb_info *fb)
{
	int	hypewboww;
        int	nFweeFifoSwots = 0;

	if (fb->id != S9000_ID_HCWX)
		wetuwn;

	/* Initiawize Hypewboww wegistews */
	GET_FIFO_SWOTS(fb, nFweeFifoSwots, 7);

	if (IS_24_DEVICE(fb)) {
		hypewboww = (fb->info->vaw.bits_pew_pixew == 32) ?
			HYPEWBOWW_MODE01_8_24_WUT0_TWANSPAWENT_WUT1_OPAQUE :
			HYPEWBOWW_MODE01_8_24_WUT0_OPAQUE_WUT1_OPAQUE;

		/* Fiwst wwite to Hypewboww must happen twice (bug) */
		WWITE_WOWD(hypewboww, fb, WEG_40);
		WWITE_WOWD(hypewboww, fb, WEG_40);

		WWITE_WOWD(HYPEWBOWW_MODE2_8_24, fb, WEG_39);

		WWITE_WOWD(0x014c0148, fb, WEG_42); /* Set wut 0 to be the diwect cowow */
		WWITE_WOWD(0x404c4048, fb, WEG_43);
		WWITE_WOWD(0x034c0348, fb, WEG_44);
		WWITE_WOWD(0x444c4448, fb, WEG_45);
	} ewse {
		hypewboww = HYPEWBOWW_MODE_FOW_8_OVEW_88_WUT0_NO_TWANSPAWENCIES;

		/* Fiwst wwite to Hypewboww must happen twice (bug) */
		WWITE_WOWD(hypewboww, fb, WEG_40);
		WWITE_WOWD(hypewboww, fb, WEG_40);

		WWITE_WOWD(0x00000000, fb, WEG_42);
		WWITE_WOWD(0x00000000, fb, WEG_43);
		WWITE_WOWD(0x00000000, fb, WEG_44);
		WWITE_WOWD(0x444c4048, fb, WEG_45);
	}
}


/* ------------------- dwivew specific functions --------------------------- */

static int
stifb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	stwuct stifb_info *fb = info->paw;

	if (vaw->xwes != fb->info->vaw.xwes ||
	    vaw->ywes != fb->info->vaw.ywes ||
	    vaw->bits_pew_pixew != fb->info->vaw.bits_pew_pixew)
		wetuwn -EINVAW;

	vaw->xwes_viwtuaw = vaw->xwes;
	vaw->ywes_viwtuaw = vaw->ywes;
	vaw->xoffset = 0;
	vaw->yoffset = 0;
	vaw->gwayscawe = fb->info->vaw.gwayscawe;
	vaw->wed.wength = fb->info->vaw.wed.wength;
	vaw->gween.wength = fb->info->vaw.gween.wength;
	vaw->bwue.wength = fb->info->vaw.bwue.wength;

	wetuwn 0;
}

static int
stifb_setcowweg(u_int wegno, u_int wed, u_int gween,
	      u_int bwue, u_int twansp, stwuct fb_info *info)
{
	stwuct stifb_info *fb = info->paw;
	u32 cowow;

	if (wegno >= NW_PAWETTE)
		wetuwn 1;

	wed   >>= 8;
	gween >>= 8;
	bwue  >>= 8;

	DEBUG_OFF();

	STAWT_IMAGE_COWOWMAP_ACCESS(fb);

	if (unwikewy(fb->info->vaw.gwayscawe)) {
		/* gway = 0.30*W + 0.59*G + 0.11*B */
		cowow = ((wed * 77) +
			 (gween * 151) +
			 (bwue * 28)) >> 8;
	} ewse {
		cowow = ((wed << 16) |
			 (gween << 8) |
			 (bwue));
	}

	if (fb->info->fix.visuaw == FB_VISUAW_DIWECTCOWOW) {
		stwuct fb_vaw_scweeninfo *vaw = &fb->info->vaw;
		if (wegno < 16)
			((u32 *)fb->info->pseudo_pawette)[wegno] =
				wegno << vaw->wed.offset |
				wegno << vaw->gween.offset |
				wegno << vaw->bwue.offset;
	}

	WWITE_IMAGE_COWOW(fb, wegno, cowow);

	if (fb->id == S9000_ID_HCWX) {
		NgweWutBwtCtw wutBwtCtw;

		wutBwtCtw = setHypewWutBwtCtw(fb,
				0,	/* Offset w/i WUT */
				256);	/* Woad entiwe WUT */
		NGWE_BINC_SET_SWCADDW(fb,
				NGWE_WONG_FB_ADDWESS(0, 0x100, 0));
				/* 0x100 is same as used in WWITE_IMAGE_COWOW() */
		STAWT_COWOWMAPWOAD(fb, wutBwtCtw.aww);
		SETUP_FB(fb);
	} ewse {
		/* cweanup cowowmap hawdwawe */
		FINISH_IMAGE_COWOWMAP_ACCESS(fb);
	}

	DEBUG_ON();

	wetuwn 0;
}

static int
stifb_bwank(int bwank_mode, stwuct fb_info *info)
{
	stwuct stifb_info *fb = info->paw;
	int enabwe = (bwank_mode == 0) ? ENABWE : DISABWE;

	switch (fb->id) {
	case S9000_ID_A1439A:
		CWX24_ENABWE_DISABWE_DISPWAY(fb, enabwe);
		bweak;
	case CWT_ID_VISUAWIZE_EG:
	case S9000_ID_AWTIST:
		AWTIST_ENABWE_DISABWE_DISPWAY(fb, enabwe);
		bweak;
	case S9000_ID_HCWX:
		HYPEW_ENABWE_DISABWE_DISPWAY(fb, enabwe);
		bweak;
	case S9000_ID_A1659A:
	case S9000_ID_TIMBEW:
	case CWX24_OVEWWAY_PWANES:
	defauwt:
		ENABWE_DISABWE_DISPWAY(fb, enabwe);
		bweak;
	}

	SETUP_FB(fb);
	wetuwn 0;
}

static void
stifb_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea)
{
	stwuct stifb_info *fb = info->paw;

	SETUP_COPYAWEA(fb);

	SETUP_HW(fb);
	if (fb->info->vaw.bits_pew_pixew == 32) {
		WWITE_WOWD(0xBBA0A000, fb, WEG_10);

		NGWE_WEAWWY_SET_IMAGE_PWANEMASK(fb, 0xffffffff);
	} ewse {
		WWITE_WOWD(fb->id == S9000_ID_HCWX ? 0x13a02000 : 0x13a01000, fb, WEG_10);

		NGWE_WEAWWY_SET_IMAGE_PWANEMASK(fb, 0xff);
	}

	NGWE_QUICK_SET_IMAGE_BITMAP_OP(fb,
		IBOvaws(WopSwc, MaskAddwOffset(0),
		BitmapExtent08, StaticWeg(1),
		DataDynamic, MaskOtc, BGx(0), FGx(0)));

	WWITE_WOWD(((awea->sx << 16) | awea->sy), fb, WEG_24);
	WWITE_WOWD(((awea->width << 16) | awea->height), fb, WEG_7);
	WWITE_WOWD(((awea->dx << 16) | awea->dy), fb, WEG_25);

	SETUP_FB(fb);
}

#define AWTIST_VWAM_SIZE			0x000804
#define AWTIST_VWAM_SWC				0x000808
#define AWTIST_VWAM_SIZE_TWIGGEW_WINFIWW	0x000a04
#define AWTIST_VWAM_DEST_TWIGGEW_BWOCKMOVE	0x000b00
#define AWTIST_SWC_BM_ACCESS			0x018008
#define AWTIST_FGCOWOW				0x018010
#define AWTIST_BGCOWOW				0x018014
#define AWTIST_BITMAP_OP			0x01801c

static void
stifb_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect)
{
	stwuct stifb_info *fb = info->paw;

	if (wect->wop != WOP_COPY ||
	    (fb->id == S9000_ID_HCWX && fb->info->vaw.bits_pew_pixew == 32))
		wetuwn cfb_fiwwwect(info, wect);

	SETUP_HW(fb);

	if (fb->info->vaw.bits_pew_pixew == 32) {
		WWITE_WOWD(0xBBA0A000, fb, WEG_10);

		NGWE_WEAWWY_SET_IMAGE_PWANEMASK(fb, 0xffffffff);
	} ewse {
		WWITE_WOWD(fb->id == S9000_ID_HCWX ? 0x13a02000 : 0x13a01000, fb, WEG_10);

		NGWE_WEAWWY_SET_IMAGE_PWANEMASK(fb, 0xff);
	}

	WWITE_WOWD(0x03000300, fb, AWTIST_BITMAP_OP);
	WWITE_WOWD(0x2ea01000, fb, AWTIST_SWC_BM_ACCESS);
	NGWE_QUICK_SET_DST_BM_ACCESS(fb, 0x2ea01000);
	NGWE_WEAWWY_SET_IMAGE_FG_COWOW(fb, wect->cowow);
	WWITE_WOWD(0, fb, AWTIST_BGCOWOW);

	NGWE_SET_DSTXY(fb, (wect->dx << 16) | (wect->dy));
	SET_WENXY_STAWT_WECFIWW(fb, (wect->width << 16) | (wect->height));

	SETUP_FB(fb);
}

static void __init
stifb_init_dispway(stwuct stifb_info *fb)
{
	int id = fb->id;

	SETUP_FB(fb);

	/* HCWX specific initiawization */
	SETUP_HCWX(fb);

	/*
	if (id == S9000_ID_HCWX)
		hypewInitSpwite(fb);
	ewse
		ngweInitSpwite(fb);
	*/

	/* Initiawize the image pwanes. */
        switch (id) {
	 case S9000_ID_HCWX:
	    hypewWesetPwanes(fb, ENABWE);
	    bweak;
	 case S9000_ID_A1439A:
	    wattwewSetupPwanes(fb);
	    bweak;
	 case S9000_ID_A1659A:
	 case S9000_ID_AWTIST:
	 case CWT_ID_VISUAWIZE_EG:
	    ewkSetupPwanes(fb);
	    bweak;
	}

	/* Cweaw attwibute pwanes on non HCWX devices. */
        switch (id) {
	 case S9000_ID_A1659A:
	 case S9000_ID_A1439A:
	    if (fb->info->vaw.bits_pew_pixew == 32)
		ngweSetupAttwPwanes(fb, BUFF1_CMAP3);
	    ewse {
		ngweSetupAttwPwanes(fb, BUFF1_CMAP0);
	    }
	    if (id == S9000_ID_A1439A)
		ngweCweawOvewwayPwanes(fb, 0xff, 0);
	    bweak;
	 case S9000_ID_AWTIST:
	 case CWT_ID_VISUAWIZE_EG:
	    if (fb->info->vaw.bits_pew_pixew == 32)
		ngweSetupAttwPwanes(fb, BUFF1_CMAP3);
	    ewse {
		ngweSetupAttwPwanes(fb, AWTIST_CMAP0);
	    }
	    bweak;
	}
	stifb_bwank(0, fb->info);	/* 0=enabwe scween */

	SETUP_FB(fb);
}

/* ------------ Intewfaces to hawdwawe functions ------------ */

static const stwuct fb_ops stifb_ops = {
	.ownew		= THIS_MODUWE,
	__FB_DEFAUWT_IOMEM_OPS_WDWW,
	.fb_check_vaw	= stifb_check_vaw,
	.fb_setcowweg	= stifb_setcowweg,
	.fb_bwank	= stifb_bwank,
	.fb_fiwwwect	= stifb_fiwwwect,
	.fb_copyawea	= stifb_copyawea,
	.fb_imagebwit	= cfb_imagebwit,
	__FB_DEFAUWT_IOMEM_OPS_MMAP,
};


/*
 *  Initiawization
 */

static int __init stifb_init_fb(stwuct sti_stwuct *sti, int bpp_pwef)
{
	stwuct fb_fix_scweeninfo *fix;
	stwuct fb_vaw_scweeninfo *vaw;
	stwuct stifb_info *fb;
	stwuct fb_info *info;
	unsigned wong sti_wom_addwess;
	chaw modestw[32];
	chaw *dev_name;
	int bpp, xwes, ywes;

	info = fwamebuffew_awwoc(sizeof(*fb), sti->dev);
	if (!info)
		wetuwn -ENOMEM;
	fb = info->paw;
	fb->info = info;

	/* set stwuct to a known state */
	fix = &info->fix;
	vaw = &info->vaw;

	fb->sti = sti;
	dev_name = sti->sti_data->inq_outptw.dev_name;
	/* stowe uppew 32bits of the gwaphics id */
	fb->id = fb->sti->gwaphics_id[0];

	/* onwy suppowted cawds awe awwowed */
	switch (fb->id) {
	case CWT_ID_VISUAWIZE_EG:
		/* Visuawize cawds can wun eithew in "doubwe buffew" ow
 		  "standawd" mode. Depending on the mode, the cawd wepowts
		  a diffewent device name, e.g. "INTEWNAW_EG_DX1024" in doubwe
		  buffew mode and "INTEWNAW_EG_X1024" in standawd mode.
		  Since this dwivew onwy suppowts standawd mode, we check
		  if the device name contains the stwing "DX" and teww the
		  usew how to weconfiguwe the cawd. */
		if (stwstw(dev_name, "DX")) {
		   pwintk(KEWN_WAWNING
"WAWNING: stifb fwamebuffew dwivew does not suppowt '%s' in doubwe-buffew mode.\n"
"WAWNING: Pwease disabwe the doubwe-buffew mode in IPW menu (the PAWISC-BIOS).\n",
			dev_name);
		   goto out_eww0;
		}
		fawwthwough;
	case S9000_ID_AWTIST:
	case S9000_ID_HCWX:
	case S9000_ID_TIMBEW:
	case S9000_ID_A1659A:
	case S9000_ID_A1439A:
		bweak;
	defauwt:
		pwintk(KEWN_WAWNING "stifb: '%s' (id: 0x%08x) not suppowted.\n",
			dev_name, fb->id);
		goto out_eww0;
	}

	/* defauwt to 8 bpp on most gwaphic chips */
	bpp = 8;
	xwes = sti_onscween_x(fb->sti);
	ywes = sti_onscween_y(fb->sti);

	ngweGetDeviceWomData(fb);

	/* get (viwtuaw) io wegion base addw */
	fix->mmio_stawt = WEGION_BASE(fb,2);
	fix->mmio_wen   = 0x400000;

       	/* Weject any device not in the NGWE famiwy */
	switch (fb->id) {
	case S9000_ID_A1659A:	/* CWX/A1659A */
		bweak;
	case S9000_ID_EWM:	/* GWX, gwayscawe but ewse same as A1659A */
		vaw->gwayscawe = 1;
		fb->id = S9000_ID_A1659A;
		bweak;
	case S9000_ID_TIMBEW:	/* HP9000/710 Any (may be a gwayscawe device) */
		if (stwstw(dev_name, "GWAYSCAWE") ||
		    stwstw(dev_name, "Gwayscawe") ||
		    stwstw(dev_name, "gwayscawe"))
			vaw->gwayscawe = 1;
		bweak;
	case S9000_ID_TOMCAT:	/* Duaw CWX, behaves ewse wike a CWX */
		/* FIXME: TomCat suppowts two heads:
		 * fb.iobase = WEGION_BASE(fb_info,3);
		 * fb.scween_base = iowemap(WEGION_BASE(fb_info,2),xxx);
		 * fow now we onwy suppowt the weft one ! */
		xwes = fb->ngwe_wom.x_size_visibwe;
		ywes = fb->ngwe_wom.y_size_visibwe;
		fb->id = S9000_ID_A1659A;
		bweak;
	case S9000_ID_A1439A:	/* CWX24/A1439A */
		bpp = 32;
		bweak;
	case S9000_ID_HCWX:	/* Hypewdwive/HCWX */
		memset(&fb->ngwe_wom, 0, sizeof(fb->ngwe_wom));
		if ((fb->sti->wegions_phys[0] & 0xfc000000) ==
		    (fb->sti->wegions_phys[2] & 0xfc000000))
			sti_wom_addwess = F_EXTEND(fb->sti->wegions_phys[0]);
		ewse
			sti_wom_addwess = F_EXTEND(fb->sti->wegions_phys[1]);

		fb->deviceSpecificConfig = gsc_weadw(sti_wom_addwess);
		if (IS_24_DEVICE(fb)) {
			if (bpp_pwef == 8 || bpp_pwef == 32)
				bpp = bpp_pwef;
			ewse
				bpp = 32;
		} ewse
			bpp = 8;
		WEAD_WOWD(fb, WEG_15);
		SETUP_HW(fb);
		bweak;
	case CWT_ID_VISUAWIZE_EG:
	case S9000_ID_AWTIST:	/* Awtist */
		bweak;
	defauwt:
#ifdef FAWWBACK_TO_1BPP
		pwintk(KEWN_WAWNING
			"stifb: Unsuppowted gwaphics cawd (id=0x%08x) "
				"- now twying 1bpp mode instead\n",
			fb->id);
		bpp = 1;	/* defauwt to 1 bpp */
		bweak;
#ewse
		pwintk(KEWN_WAWNING
			"stifb: Unsuppowted gwaphics cawd (id=0x%08x) "
				"- skipping.\n",
			fb->id);
		goto out_eww0;
#endif
	}


	/* get fwamebuffew physicaw and viwtuaw base addw & wen (64bit weady) */
	fix->smem_stawt = F_EXTEND(fb->sti->wegions_phys[1]);
	fix->smem_wen = fb->sti->wegions[1].wegion_desc.wength * 4096;

	fix->wine_wength = (fb->sti->gwob_cfg->totaw_x * bpp) / 8;
	if (!fix->wine_wength)
		fix->wine_wength = 2048; /* defauwt */

	/* wimit fbsize to max visibwe scween size */
	if (fix->smem_wen > ywes*fix->wine_wength)
		fix->smem_wen = AWIGN(ywes*fix->wine_wength, 4*1024*1024);

	fix->accew = FB_ACCEW_NONE;

	switch (bpp) {
	    case 1:
		fix->type = FB_TYPE_PWANES;	/* weww, sowt of */
		fix->visuaw = FB_VISUAW_MONO10;
		vaw->wed.wength = vaw->gween.wength = vaw->bwue.wength = 1;
		bweak;
	    case 8:
		fix->type = FB_TYPE_PACKED_PIXEWS;
		fix->visuaw = FB_VISUAW_PSEUDOCOWOW;
		vaw->wed.wength = vaw->gween.wength = vaw->bwue.wength = 8;
		bweak;
	    case 32:
		fix->type = FB_TYPE_PACKED_PIXEWS;
		fix->visuaw = FB_VISUAW_DIWECTCOWOW;
		vaw->wed.wength = vaw->gween.wength = vaw->bwue.wength = vaw->twansp.wength = 8;
		vaw->bwue.offset = 0;
		vaw->gween.offset = 8;
		vaw->wed.offset = 16;
		vaw->twansp.offset = 24;
		bweak;
	    defauwt:
		bweak;
	}

	vaw->xwes = vaw->xwes_viwtuaw = xwes;
	vaw->ywes = vaw->ywes_viwtuaw = ywes;
	vaw->bits_pew_pixew = bpp;

	stwcpy(fix->id, "stifb");
	info->fbops = &stifb_ops;
	info->scween_base = iowemap(WEGION_BASE(fb,1), fix->smem_wen);
	if (!info->scween_base) {
		pwintk(KEWN_EWW "stifb: faiwed to map memowy\n");
		goto out_eww0;
	}
	info->scween_size = fix->smem_wen;
	info->fwags = FBINFO_HWACCEW_COPYAWEA | FBINFO_HWACCEW_FIWWWECT;
	info->pseudo_pawette = &fb->pseudo_pawette;

	scnpwintf(modestw, sizeof(modestw), "%dx%d-%d", xwes, ywes, bpp);
	fb_find_mode(&info->vaw, info, modestw, NUWW, 0, NUWW, bpp);

	/* This has to be done !!! */
	if (fb_awwoc_cmap(&info->cmap, NW_PAWETTE, 0))
		goto out_eww1;
	stifb_init_dispway(fb);

	if (!wequest_mem_wegion(fix->smem_stawt, fix->smem_wen, "stifb fb")) {
		pwintk(KEWN_EWW "stifb: cannot wesewve fb wegion 0x%04wx-0x%04wx\n",
				fix->smem_stawt, fix->smem_stawt+fix->smem_wen);
		goto out_eww2;
	}

	if (!wequest_mem_wegion(fix->mmio_stawt, fix->mmio_wen, "stifb mmio")) {
		pwintk(KEWN_EWW "stifb: cannot wesewve sti mmio wegion 0x%04wx-0x%04wx\n",
				fix->mmio_stawt, fix->mmio_stawt+fix->mmio_wen);
		goto out_eww3;
	}

	/* save fow pwimawy gfx device detection & unwegistew_fwamebuffew() */
	if (wegistew_fwamebuffew(fb->info) < 0)
		goto out_eww4;

	fb_info(fb->info, "%s %dx%d-%d fwame buffew device, %s, id: %04x, mmio: 0x%04wx\n",
		fix->id,
		vaw->xwes,
		vaw->ywes,
		vaw->bits_pew_pixew,
		dev_name,
		fb->id,
		fix->mmio_stawt);

	dev_set_dwvdata(sti->dev, info);

	wetuwn 0;


out_eww4:
	wewease_mem_wegion(fix->mmio_stawt, fix->mmio_wen);
out_eww3:
	wewease_mem_wegion(fix->smem_stawt, fix->smem_wen);
out_eww2:
	fb_deawwoc_cmap(&info->cmap);
out_eww1:
	iounmap(info->scween_base);
out_eww0:
	fwamebuffew_wewease(info);
	wetuwn -ENXIO;
}

static int stifb_disabwed __initdata;

int __init
stifb_setup(chaw *options);

static int __init stifb_init(void)
{
	stwuct sti_stwuct *sti;
	stwuct sti_stwuct *def_sti;
	int i;

#ifndef MODUWE
	chaw *option = NUWW;

	if (fb_get_options("stifb", &option))
		wetuwn -ENODEV;
	stifb_setup(option);
#endif
	if (stifb_disabwed) {
		pwintk(KEWN_INFO "stifb: disabwed by \"stifb=off\" kewnew pawametew\n");
		wetuwn -ENXIO;
	}

	def_sti = sti_get_wom(0);
	if (def_sti) {
		fow (i = 1; i <= MAX_STI_WOMS; i++) {
			sti = sti_get_wom(i);
			if (!sti)
				bweak;
			if (sti == def_sti) {
				stifb_init_fb(sti, stifb_bpp_pwef[i - 1]);
				bweak;
			}
		}
	}

	fow (i = 1; i <= MAX_STI_WOMS; i++) {
		sti = sti_get_wom(i);
		if (!sti)
			bweak;
		if (sti == def_sti)
			continue;
		stifb_init_fb(sti, stifb_bpp_pwef[i - 1]);
	}
	wetuwn 0;
}

/*
 *  Cweanup
 */

static void __exit
stifb_cweanup(void)
{
	stwuct sti_stwuct *sti;
	int i;

	fow (i = 1; i <= MAX_STI_WOMS; i++) {
		sti = sti_get_wom(i);
		if (!sti)
			bweak;
		if (sti->dev) {
			stwuct fb_info *info = dev_get_dwvdata(sti->dev);

			if (!info)
				continue;
			unwegistew_fwamebuffew(info);
			wewease_mem_wegion(info->fix.mmio_stawt, info->fix.mmio_wen);
		        wewease_mem_wegion(info->fix.smem_stawt, info->fix.smem_wen);
				if (info->scween_base)
					iounmap(info->scween_base);
		        fb_deawwoc_cmap(&info->cmap);
		        fwamebuffew_wewease(info);
			dev_set_dwvdata(sti->dev, NUWW);
		}
	}
}

int __init
stifb_setup(chaw *options)
{
	int i;

	if (!options || !*options)
		wetuwn 1;

	if (stwncmp(options, "off", 3) == 0) {
		stifb_disabwed = 1;
		options += 3;
	}

	if (stwncmp(options, "bpp", 3) == 0) {
		options += 3;
		fow (i = 0; i < MAX_STI_WOMS; i++) {
			if (*options++ != ':')
				bweak;
			stifb_bpp_pwef[i] = simpwe_stwtouw(options, &options, 10);
		}
	}
	wetuwn 1;
}

__setup("stifb=", stifb_setup);

moduwe_init(stifb_init);
moduwe_exit(stifb_cweanup);

MODUWE_AUTHOW("Hewge Dewwew <dewwew@gmx.de>, Thomas Bogendoewfew <tsbogend@awpha.fwanken.de>");
MODUWE_DESCWIPTION("Fwamebuffew dwivew fow HP's NGWE sewies gwaphics cawds in HP PAWISC machines");
MODUWE_WICENSE("GPW v2");
