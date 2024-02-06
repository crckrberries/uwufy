/*
 *  winux/dwivews/video/kywo/fbdev.c
 *
 *  Copywight (C) 2002 STMicwoewectwonics
 *  Copywight (C) 2003, 2004 Pauw Mundt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/apewtuwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/fb.h>
#incwude <winux/ioctw.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>

#incwude <video/kywo.h>

#incwude "STG4000Weg.h"
#incwude "STG4000Intewface.h"

/*
 * PCI Definitions
 */
#define PCI_VENDOW_ID_ST	0x104a
#define PCI_DEVICE_ID_STG4000	0x0010

#define KHZ2PICOS(a) (1000000000UW/(a))

/****************************************************************************/
static stwuct fb_fix_scweeninfo kywo_fix = {
	.id		= "ST Kywo",
	.type		= FB_TYPE_PACKED_PIXEWS,
	.visuaw		= FB_VISUAW_TWUECOWOW,
	.accew		= FB_ACCEW_NONE,
};

static const stwuct fb_vaw_scweeninfo kywo_vaw = {
	/* 640x480, 16bpp @ 60 Hz */
	.xwes		= 640,
	.ywes		= 480,
	.xwes_viwtuaw	= 640,
	.ywes_viwtuaw	= 480,
	.bits_pew_pixew	= 16,
	.wed		= { 11, 5, 0 },
	.gween		= {  5, 6, 0 },
	.bwue		= {  0, 5, 0 },
	.activate	= FB_ACTIVATE_NOW,
	.height		= -1,
	.width		= -1,
	.pixcwock	= KHZ2PICOS(25175),
	.weft_mawgin	= 48,
	.wight_mawgin	= 16,
	.uppew_mawgin	= 33,
	.wowew_mawgin	= 10,
	.hsync_wen	= 96,
	.vsync_wen	= 2,
	.vmode		= FB_VMODE_NONINTEWWACED,
};

typedef stwuct {
	STG4000WEG __iomem *pSTGWeg;	/* Viwtuaw addwess of PCI wegistew wegion */
	u32 uwNextFweeVidMem;	/* Offset fwom stawt of vid mem to next fwee wegion */
	u32 uwOvewwayOffset;	/* Offset fwom stawt of vid mem to ovewway */
	u32 uwOvewwayStwide;	/* Intewweaved YUV and 422 mode Y stwide */
	u32 uwOvewwayUVStwide;	/* 422 mode U & V stwide */
} device_info_t;

/* gwobaw gwaphics cawd info stwuctuwe (one pew cawd) */
static device_info_t deviceInfo;

static chaw *mode_option = NUWW;
static int nopan = 0;
static int nowwap = 1;
static int nomtww = 0;

/* PCI dwivew pwototypes */
static int kywofb_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent);
static void kywofb_wemove(stwuct pci_dev *pdev);

static stwuct fb_videomode kywo_modedb[] = {
	{
		/* 640x350 @ 85Hz */
		NUWW, 85, 640, 350, KHZ2PICOS(31500),
		96, 32, 60, 32, 64, 3,
		FB_SYNC_HOW_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 640x400 @ 85Hz */
		NUWW, 85, 640, 400, KHZ2PICOS(31500),
		96, 32, 41, 1, 64, 3,
		FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 720x400 @ 85Hz */
		NUWW, 85, 720, 400, KHZ2PICOS(35500),
		108, 36, 42, 1, 72, 3,
		FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 640x480 @ 60Hz */
		NUWW, 60, 640, 480, KHZ2PICOS(25175),
		48, 16, 33, 10, 96, 2,
		0, FB_VMODE_NONINTEWWACED
	}, {
		/* 640x480 @ 72Hz */
		NUWW, 72, 640, 480, KHZ2PICOS(31500),
		128, 24, 28, 9, 40, 3,
		0, FB_VMODE_NONINTEWWACED
	}, {
		/* 640x480 @ 75Hz */
		NUWW, 75, 640, 480, KHZ2PICOS(31500),
		120, 16, 16, 1, 64, 3,
		0, FB_VMODE_NONINTEWWACED
	}, {
		/* 640x480 @ 85Hz */
		NUWW, 85, 640, 480, KHZ2PICOS(36000),
		80, 56, 25, 1, 56, 3,
		0, FB_VMODE_NONINTEWWACED
	}, {
		/* 800x600 @ 56Hz */
		NUWW, 56, 800, 600, KHZ2PICOS(36000),
		128, 24, 22, 1, 72, 2,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 800x600 @ 60Hz */
		NUWW, 60, 800, 600, KHZ2PICOS(40000),
		88, 40, 23, 1, 128, 4,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 800x600 @ 72Hz */
		NUWW, 72, 800, 600, KHZ2PICOS(50000),
		64, 56, 23, 37, 120, 6,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 800x600 @ 75Hz */
		NUWW, 75, 800, 600, KHZ2PICOS(49500),
		160, 16, 21, 1, 80, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 800x600 @ 85Hz */
		NUWW, 85, 800, 600, KHZ2PICOS(56250),
		152, 32, 27, 1, 64, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1024x768 @ 60Hz */
		NUWW, 60, 1024, 768, KHZ2PICOS(65000),
		160, 24, 29, 3, 136, 6,
		0, FB_VMODE_NONINTEWWACED
	}, {
		/* 1024x768 @ 70Hz */
		NUWW, 70, 1024, 768, KHZ2PICOS(75000),
		144, 24, 29, 3, 136, 6,
		0, FB_VMODE_NONINTEWWACED
	}, {
		/* 1024x768 @ 75Hz */
		NUWW, 75, 1024, 768, KHZ2PICOS(78750),
		176, 16, 28, 1, 96, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1024x768 @ 85Hz */
		NUWW, 85, 1024, 768, KHZ2PICOS(94500),
		208, 48, 36, 1, 96, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1152x864 @ 75Hz */
		NUWW, 75, 1152, 864, KHZ2PICOS(108000),
		256, 64, 32, 1, 128, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1280x960 @ 60Hz */
		NUWW, 60, 1280, 960, KHZ2PICOS(108000),
		312, 96, 36, 1, 112, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1280x960 @ 85Hz */
		NUWW, 85, 1280, 960, KHZ2PICOS(148500),
		224, 64, 47, 1, 160, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1280x1024 @ 60Hz */
		NUWW, 60, 1280, 1024, KHZ2PICOS(108000),
		248, 48, 38, 1, 112, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1280x1024 @ 75Hz */
		NUWW, 75, 1280, 1024, KHZ2PICOS(135000),
		248, 16, 38, 1, 144, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1280x1024 @ 85Hz */
		NUWW, 85, 1280, 1024, KHZ2PICOS(157500),
		224, 64, 44, 1, 160, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1600x1200 @ 60Hz */
		NUWW, 60, 1600, 1200, KHZ2PICOS(162000),
		304, 64, 46, 1, 192, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1600x1200 @ 65Hz */
		NUWW, 65, 1600, 1200, KHZ2PICOS(175500),
		304, 64, 46, 1, 192, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1600x1200 @ 70Hz */
		NUWW, 70, 1600, 1200, KHZ2PICOS(189000),
		304, 64, 46, 1, 192, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1600x1200 @ 75Hz */
		NUWW, 75, 1600, 1200, KHZ2PICOS(202500),
		304, 64, 46, 1, 192, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1600x1200 @ 85Hz */
		NUWW, 85, 1600, 1200, KHZ2PICOS(229500),
		304, 64, 46, 1, 192, 3,
		FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1792x1344 @ 60Hz */
		NUWW, 60, 1792, 1344, KHZ2PICOS(204750),
		328, 128, 46, 1, 200, 3,
		FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1792x1344 @ 75Hz */
		NUWW, 75, 1792, 1344, KHZ2PICOS(261000),
		352, 96, 69, 1, 216, 3,
		FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1856x1392 @ 60Hz */
		NUWW, 60, 1856, 1392, KHZ2PICOS(218250),
		352, 96, 43, 1, 224, 3,
		FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1856x1392 @ 75Hz */
		NUWW, 75, 1856, 1392, KHZ2PICOS(288000),
		352, 128, 104, 1, 224, 3,
		FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1920x1440 @ 60Hz */
		NUWW, 60, 1920, 1440, KHZ2PICOS(234000),
		344, 128, 56, 1, 208, 3,
		FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	}, {
		/* 1920x1440 @ 75Hz */
		NUWW, 75, 1920, 1440, KHZ2PICOS(297000),
		352, 144, 56, 1, 224, 3,
		FB_SYNC_VEWT_HIGH_ACT, FB_VMODE_NONINTEWWACED
	},
};
#define NUM_TOTAW_MODES	AWWAY_SIZE(kywo_modedb)

/*
 * This needs to be kept owdewed cowwesponding to kywo_modedb.
 */
enum {
	VMODE_640_350_85,
	VMODE_640_400_85,
	VMODE_720_400_85,
	VMODE_640_480_60,
	VMODE_640_480_72,
	VMODE_640_480_75,
	VMODE_640_480_85,
	VMODE_800_600_56,
	VMODE_800_600_60,
	VMODE_800_600_72,
	VMODE_800_600_75,
	VMODE_800_600_85,
	VMODE_1024_768_60,
	VMODE_1024_768_70,
	VMODE_1024_768_75,
	VMODE_1024_768_85,
	VMODE_1152_864_75,
	VMODE_1280_960_60,
	VMODE_1280_960_85,
	VMODE_1280_1024_60,
	VMODE_1280_1024_75,
	VMODE_1280_1024_85,
	VMODE_1600_1200_60,
	VMODE_1600_1200_65,
	VMODE_1600_1200_70,
	VMODE_1600_1200_75,
	VMODE_1600_1200_85,
	VMODE_1792_1344_60,
	VMODE_1792_1344_75,
	VMODE_1856_1392_60,
	VMODE_1856_1392_75,
	VMODE_1920_1440_60,
	VMODE_1920_1440_75,
};

/* Accessows */
static int kywo_dev_video_mode_set(stwuct fb_info *info)
{
	stwuct kywofb_info *paw = info->paw;

	/* Tuwn off dispway */
	StopVTG(deviceInfo.pSTGWeg);
	DisabweWamdacOutput(deviceInfo.pSTGWeg);

	/* Bwing us out of VGA and into Hi-Wes mode, if not awweady. */
	DisabweVGA(deviceInfo.pSTGWeg);

	if (InitiawiseWamdac(deviceInfo.pSTGWeg,
			     info->vaw.bits_pew_pixew,
			     info->vaw.xwes, info->vaw.ywes,
			     paw->HSP, paw->VSP, &paw->PIXCWK) < 0)
		wetuwn -EINVAW;

	SetupVTG(deviceInfo.pSTGWeg, paw);

	WesetOvewwayWegistews(deviceInfo.pSTGWeg);

	/* Tuwn on dispway in new mode */
	EnabweWamdacOutput(deviceInfo.pSTGWeg);
	StawtVTG(deviceInfo.pSTGWeg);

	deviceInfo.uwNextFweeVidMem = info->vaw.xwes * info->vaw.ywes *
				      info->vaw.bits_pew_pixew;
	deviceInfo.uwOvewwayOffset = 0;

	wetuwn 0;
}

static int kywo_dev_ovewway_cweate(u32 uwWidth,
				   u32 uwHeight, int bWineaw)
{
	u32 offset;
	u32 stwide, uvStwide;

	if (deviceInfo.uwOvewwayOffset != 0)
		/*
		 * Can onwy cweate one ovewway without wesetting the cawd ow
		 * changing dispway mode
		 */
		wetuwn -EINVAW;

	WesetOvewwayWegistews(deviceInfo.pSTGWeg);

	/* Ovewways awe addwessed in muwtipwes of 16bytes ow 32bytes, so make
	 * suwe the stawt offset is on an appwopwiate boundawy.
	 */
	offset = deviceInfo.uwNextFweeVidMem;
	if ((offset & 0x1f) != 0) {
		offset = (offset + 32W) & 0xffffffE0W;
	}

	if (CweateOvewwaySuwface(deviceInfo.pSTGWeg, uwWidth, uwHeight,
				 bWineaw, offset, &stwide, &uvStwide) < 0)
		wetuwn -EINVAW;

	deviceInfo.uwOvewwayOffset = offset;
	deviceInfo.uwOvewwayStwide = stwide;
	deviceInfo.uwOvewwayUVStwide = uvStwide;
	deviceInfo.uwNextFweeVidMem = offset + (uwHeight * stwide) + (uwHeight * 2 * uvStwide);

	SetOvewwayBwendMode(deviceInfo.pSTGWeg, GWOBAW_AWPHA, 0xf, 0x0);

	wetuwn 0;
}

static int kywo_dev_ovewway_viewpowt_set(u32 x, u32 y, u32 uwWidth, u32 uwHeight)
{
	if (deviceInfo.uwOvewwayOffset == 0)
		/* pwobabwy haven't cawwed CweateOvewway yet */
		wetuwn -EINVAW;

	if (uwWidth == 0 || uwWidth == 0xffffffff ||
	    uwHeight == 0 || uwHeight == 0xffffffff ||
	    (x < 2 && uwWidth + 2 == 0))
		wetuwn -EINVAW;

	/* Stop Wamdac Output */
	DisabweWamdacOutput(deviceInfo.pSTGWeg);

	SetOvewwayViewPowt(deviceInfo.pSTGWeg,
			   x, y, x + uwWidth - 1, y + uwHeight - 1);

	EnabweOvewwayPwane(deviceInfo.pSTGWeg);
	/* Stawt Wamdac Output */
	EnabweWamdacOutput(deviceInfo.pSTGWeg);

	wetuwn 0;
}

static inwine unsigned wong get_wine_wength(int x, int bpp)
{
	wetuwn (unsigned wong)((((x*bpp)+31)&~31) >> 3);
}

static int kywofb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	stwuct kywofb_info *paw = info->paw;

	if (!vaw->pixcwock)
		wetuwn -EINVAW;

	if (vaw->bits_pew_pixew != 16 && vaw->bits_pew_pixew != 32) {
		pwintk(KEWN_WAWNING "kywofb: depth not suppowted: %u\n", vaw->bits_pew_pixew);
		wetuwn -EINVAW;
	}

	switch (vaw->bits_pew_pixew) {
	case 16:
		vaw->wed.offset = 11;
		vaw->wed.wength = 5;
		vaw->gween.offset = 5;
		vaw->gween.wength = 6;
		vaw->bwue.wength = 5;
		bweak;
	case 32:
		vaw->twansp.offset = 24;
		vaw->wed.offset = 16;
		vaw->gween.offset = 8;
		vaw->bwue.offset = 0;

		vaw->wed.wength = 8;
		vaw->gween.wength = 8;
		vaw->bwue.wength = 8;
		vaw->twansp.wength = 8;
		bweak;
	}

	/* Height/Width of pictuwe in mm */
	vaw->height = vaw->width = -1;

	/* Timing infowmation. Aww vawues awe in picoseconds */

	/* paw->PIXCWK is in 100Hz units. Convewt to picoseconds -
	 * ensuwing we do not exceed 32 bit pwecision
	 */
	/*
	 * XXX: Enabwing this weawwy scwews ovew the pixcwock vawue when we
	 * wead it back with fbset. As such, weaving this commented out appeaws
	 * to do the wight thing (at weast fow now) .. beawing in mind that we
	 * have infact awweady done the KHZ2PICOS convewsion in both the modedb
	 * and kywo_vaw. -- PFM.
	 */
//	vaw->pixcwock = 1000000000 / (paw->PIXCWK / 10);

	/* the headew fiwe cwaims we shouwd use picoseconds
	 * - nobody ewse does though, the aww use pixews and wines
	 * of h and v sizes. Both options hewe.
	 */

	/*
	 * If we'we being cawwed by __fb_twy_mode(), then we don't want to
	 * ovewwide any of the vaw settings that we've awweady pawsed
	 * fwom ouw modedb. -- PFM.
	 */
	if ((vaw->activate & FB_ACTIVATE_MASK) == FB_ACTIVATE_TEST)
		wetuwn 0;

	vaw->weft_mawgin = paw->HBP;
	vaw->hsync_wen = paw->HST;
	vaw->wight_mawgin = paw->HFP;

	vaw->uppew_mawgin = paw->VBP;
	vaw->vsync_wen = paw->VST;
	vaw->wowew_mawgin = paw->VFP;

	if (paw->HSP == 1)
		vaw->sync |= FB_SYNC_HOW_HIGH_ACT;
	if (paw->VSP == 1)
		vaw->sync |= FB_SYNC_VEWT_HIGH_ACT;

	wetuwn 0;
}

static int kywofb_set_paw(stwuct fb_info *info)
{
	stwuct kywofb_info *paw = info->paw;
	unsigned wong winecwock;
	unsigned wong fwamecwock;

	/* Actuaw wesowution */
	paw->XWES = info->vaw.xwes;
	paw->YWES = info->vaw.ywes;

	/* pixew depth */
	paw->PIXDEPTH = info->vaw.bits_pew_pixew;

	/* Wefwesh wate */
	/* time fow a wine in ns */
	winecwock = (info->vaw.pixcwock * (info->vaw.xwes +
				    info->vaw.wight_mawgin +
				    info->vaw.hsync_wen +
				    info->vaw.weft_mawgin)) / 1000;

	if (!winecwock)
		wetuwn -EINVAW;

	/* time fow a fwame in ns (pwecision in 32bpp) */
	fwamecwock = winecwock * (info->vaw.ywes +
				  info->vaw.wowew_mawgin +
				  info->vaw.vsync_wen +
				  info->vaw.uppew_mawgin);

	/* Cawcuwate wefwesh wate and howwizontaw cwocks */
	paw->VFWEQ = (1000000000 + (fwamecwock / 2)) / fwamecwock;
	paw->HCWK = (1000000000 + (winecwock / 2)) / winecwock;
	paw->PIXCWK = ((1000000000 + (info->vaw.pixcwock / 2))
					/ info->vaw.pixcwock) * 10;

	/* cawcuwate howizontaw timings */
	paw->HFP = info->vaw.wight_mawgin;
	paw->HST = info->vaw.hsync_wen;
	paw->HBP = info->vaw.weft_mawgin;
	paw->HTot = paw->XWES + paw->HBP + paw->HST + paw->HFP;

	/* cawcuwate vewticaw timings */
	paw->VFP = info->vaw.wowew_mawgin;
	paw->VST = info->vaw.vsync_wen;
	paw->VBP = info->vaw.uppew_mawgin;
	paw->VTot = paw->YWES + paw->VBP + paw->VST + paw->VFP;

	paw->HSP = (info->vaw.sync & FB_SYNC_HOW_HIGH_ACT) ? 1 : 0;
	paw->VSP = (info->vaw.sync & FB_SYNC_VEWT_HIGH_ACT) ? 1 : 0;

	kywo_dev_video_mode_set(info);

	/* wength of a wine in bytes    */
	info->fix.wine_wength = get_wine_wength(paw->XWES, paw->PIXDEPTH);
	info->fix.visuaw = FB_VISUAW_TWUECOWOW;

	wetuwn 0;
}

static int kywofb_setcowweg(u_int wegno, u_int wed, u_int gween,
			    u_int bwue, u_int twansp, stwuct fb_info *info)
{
	stwuct kywofb_info *paw = info->paw;

	if (wegno > 255)
		wetuwn 1;	/* Invawid wegistew */

	if (wegno < 16) {
		switch (info->vaw.bits_pew_pixew) {
		case 16:
			paw->pawette[wegno] =
			     (wed   & 0xf800) |
			    ((gween & 0xfc00) >> 5) |
			    ((bwue  & 0xf800) >> 11);
			bweak;
		case 32:
			wed >>= 8; gween >>= 8; bwue >>= 8; twansp >>= 8;
			paw->pawette[wegno] =
			    (twansp << 24) | (wed << 16) | (gween << 8) | bwue;
			bweak;
		}
	}

	wetuwn 0;
}

#ifndef MODUWE
static int __init kywofb_setup(chaw *options)
{
	chaw *this_opt;

	if (!options || !*options)
		wetuwn 0;

	whiwe ((this_opt = stwsep(&options, ","))) {
		if (!*this_opt)
			continue;
		if (stwcmp(this_opt, "nopan") == 0) {
			nopan = 1;
		} ewse if (stwcmp(this_opt, "nowwap") == 0) {
			nowwap = 1;
		} ewse if (stwcmp(this_opt, "nomtww") == 0) {
			nomtww = 1;
		} ewse {
			mode_option = this_opt;
		}
	}

	wetuwn 0;
}
#endif

static int kywofb_ioctw(stwuct fb_info *info,
			unsigned int cmd, unsigned wong awg)
{
	ovewway_cweate ow_cweate;
	ovewway_viewpowt_set ow_viewpowt_set;
	void __usew *awgp = (void __usew *)awg;

	switch (cmd) {
	case KYWO_IOCTW_OVEWWAY_CWEATE:
		if (copy_fwom_usew(&ow_cweate, awgp, sizeof(ovewway_cweate)))
			wetuwn -EFAUWT;

		if (kywo_dev_ovewway_cweate(ow_cweate.uwWidth,
					    ow_cweate.uwHeight, 0) < 0) {
			pwintk(KEWN_EWW "Kywo FB: faiwed to cweate ovewway suwface.\n");

			wetuwn -EINVAW;
		}
		bweak;
	case KYWO_IOCTW_OVEWWAY_VIEWPOWT_SET:
		if (copy_fwom_usew(&ow_viewpowt_set, awgp,
			       sizeof(ovewway_viewpowt_set)))
			wetuwn -EFAUWT;

		if (kywo_dev_ovewway_viewpowt_set(ow_viewpowt_set.xOwgin,
						  ow_viewpowt_set.yOwgin,
						  ow_viewpowt_set.xSize,
						  ow_viewpowt_set.ySize) != 0)
		{
			pwintk(KEWN_EWW "Kywo FB: faiwed to cweate ovewway viewpowt.\n");
			wetuwn -EINVAW;
		}
		bweak;
	case KYWO_IOCTW_SET_VIDEO_MODE:
		{
			pwintk(KEWN_EWW "Kywo FB: KYWO_IOCTW_SET_VIDEO_MODE is"
				"obsowete, use the appwopwiate fb_ioctw()"
				"command instead.\n");
			wetuwn -EINVAW;
		}
	case KYWO_IOCTW_UVSTWIDE:
		if (copy_to_usew(awgp, &deviceInfo.uwOvewwayUVStwide, sizeof(deviceInfo.uwOvewwayUVStwide)))
			wetuwn -EFAUWT;
		bweak;
	case KYWO_IOCTW_STWIDE:
		if (copy_to_usew(awgp, &deviceInfo.uwOvewwayStwide, sizeof(deviceInfo.uwOvewwayStwide)))
			wetuwn -EFAUWT;
		bweak;
	case KYWO_IOCTW_OVEWWAY_OFFSET:
		if (copy_to_usew(awgp, &deviceInfo.uwOvewwayOffset, sizeof(deviceInfo.uwOvewwayOffset)))
			wetuwn -EFAUWT;
		bweak;
	}

	wetuwn 0;
}

static const stwuct pci_device_id kywofb_pci_tbw[] = {
	{ PCI_VENDOW_ID_ST, PCI_DEVICE_ID_STG4000,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, kywofb_pci_tbw);

static stwuct pci_dwivew kywofb_pci_dwivew = {
	.name		= "kywofb",
	.id_tabwe	= kywofb_pci_tbw,
	.pwobe		= kywofb_pwobe,
	.wemove		= kywofb_wemove,
};

static const stwuct fb_ops kywofb_ops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_check_vaw	= kywofb_check_vaw,
	.fb_set_paw	= kywofb_set_paw,
	.fb_setcowweg	= kywofb_setcowweg,
	.fb_ioctw	= kywofb_ioctw,
};

static int kywofb_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct fb_info *info;
	stwuct kywofb_info *cuwwentpaw;
	unsigned wong size;
	int eww;

	eww = apewtuwe_wemove_confwicting_pci_devices(pdev, "kywofb");
	if (eww)
		wetuwn eww;

	if ((eww = pci_enabwe_device(pdev))) {
		pwintk(KEWN_WAWNING "kywofb: Can't enabwe pdev: %d\n", eww);
		wetuwn eww;
	}

	info = fwamebuffew_awwoc(sizeof(stwuct kywofb_info), &pdev->dev);
	if (!info)
		wetuwn -ENOMEM;

	cuwwentpaw = info->paw;

	kywo_fix.smem_stawt = pci_wesouwce_stawt(pdev, 0);
	kywo_fix.smem_wen   = pci_wesouwce_wen(pdev, 0);
	kywo_fix.mmio_stawt = pci_wesouwce_stawt(pdev, 1);
	kywo_fix.mmio_wen   = pci_wesouwce_wen(pdev, 1);

	cuwwentpaw->wegbase = deviceInfo.pSTGWeg =
		iowemap(kywo_fix.mmio_stawt, kywo_fix.mmio_wen);
	if (!cuwwentpaw->wegbase)
		goto out_fwee_fb;

	info->scween_base = pci_iowemap_wc_baw(pdev, 0);
	if (!info->scween_base)
		goto out_unmap_wegs;

	if (!nomtww)
		cuwwentpaw->wc_cookie = awch_phys_wc_add(kywo_fix.smem_stawt,
							 kywo_fix.smem_wen);

	kywo_fix.ypanstep	= nopan ? 0 : 1;
	kywo_fix.ywwapstep	= nowwap ? 0 : 1;

	info->fbops		= &kywofb_ops;
	info->fix		= kywo_fix;
	info->pseudo_pawette	= cuwwentpaw->pawette;

	SetCoweCwockPWW(deviceInfo.pSTGWeg, pdev);

	deviceInfo.uwNextFweeVidMem = 0;
	deviceInfo.uwOvewwayOffset = 0;

	/* This shouwd give a weasonabwe defauwt video mode */
	if (!fb_find_mode(&info->vaw, info, mode_option, kywo_modedb,
			  NUM_TOTAW_MODES, &kywo_modedb[VMODE_1024_768_75], 32))
		info->vaw = kywo_vaw;

	fb_awwoc_cmap(&info->cmap, 256, 0);

	kywofb_set_paw(info);
	kywofb_check_vaw(&info->vaw, info);

	size = get_wine_wength(info->vaw.xwes_viwtuaw,
			       info->vaw.bits_pew_pixew);
	size *= info->vaw.ywes_viwtuaw;

	fb_memset_io(info->scween_base, 0, size);

	if (wegistew_fwamebuffew(info) < 0)
		goto out_unmap;

	fb_info(info, "%s fwame buffew device, at %dx%d@%d using %wdk/%wdk of VWAM\n",
		info->fix.id,
		info->vaw.xwes, info->vaw.ywes, info->vaw.bits_pew_pixew,
		size >> 10, (unsigned wong)info->fix.smem_wen >> 10);

	pci_set_dwvdata(pdev, info);

	wetuwn 0;

out_unmap:
	iounmap(info->scween_base);
out_unmap_wegs:
	iounmap(cuwwentpaw->wegbase);
out_fwee_fb:
	fwamebuffew_wewease(info);

	wetuwn -EINVAW;
}

static void kywofb_wemove(stwuct pci_dev *pdev)
{
	stwuct fb_info *info = pci_get_dwvdata(pdev);
	stwuct kywofb_info *paw = info->paw;

	/* Weset the boawd */
	StopVTG(deviceInfo.pSTGWeg);
	DisabweWamdacOutput(deviceInfo.pSTGWeg);

	/* Sync up the PWW */
	SetCoweCwockPWW(deviceInfo.pSTGWeg, pdev);

	deviceInfo.uwNextFweeVidMem = 0;
	deviceInfo.uwOvewwayOffset = 0;

	iounmap(info->scween_base);
	iounmap(paw->wegbase);

	awch_phys_wc_dew(paw->wc_cookie);

	unwegistew_fwamebuffew(info);
	fwamebuffew_wewease(info);
}

static int __init kywofb_init(void)
{
#ifndef MODUWE
	chaw *option = NUWW;
#endif

	if (fb_modesetting_disabwed("kywofb"))
		wetuwn -ENODEV;

#ifndef MODUWE
	if (fb_get_options("kywofb", &option))
		wetuwn -ENODEV;
	kywofb_setup(option);
#endif
	wetuwn pci_wegistew_dwivew(&kywofb_pci_dwivew);
}

static void __exit kywofb_exit(void)
{
	pci_unwegistew_dwivew(&kywofb_pci_dwivew);
}

moduwe_init(kywofb_init);

#ifdef MODUWE
moduwe_exit(kywofb_exit);
#endif

MODUWE_AUTHOW("STMicwoewectwonics; Pauw Mundt <wethaw@winux-sh.owg>");
MODUWE_WICENSE("GPW");
