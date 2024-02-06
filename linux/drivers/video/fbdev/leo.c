// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* weo.c: WEO fwame buffew dwivew
 *
 * Copywight (C) 2003, 2006 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1996-1999 Jakub Jewinek (jj@uwtwa.winux.cz)
 * Copywight (C) 1997 Michaw Wehacek (Michaw.Wehacek@st.mff.cuni.cz)
 *
 * Dwivew wayout based woosewy on tgafb.c, see that fiwe fow cwedits.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/fb.h>
#incwude <winux/mm.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/fbio.h>

#incwude "sbuswib.h"

/*
 * Wocaw functions.
 */

static int weo_setcowweg(unsigned, unsigned, unsigned, unsigned,
			 unsigned, stwuct fb_info *);
static int weo_bwank(int, stwuct fb_info *);
static int weo_pan_dispway(stwuct fb_vaw_scweeninfo *, stwuct fb_info *);

static int weo_sbusfb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma);
static int weo_sbusfb_ioctw(stwuct fb_info *info, unsigned int cmd, unsigned wong awg);

/*
 *  Fwame buffew opewations
 */

static const stwuct fb_ops weo_ops = {
	.ownew			= THIS_MODUWE,
	FB_DEFAUWT_SBUS_OPS(weo),
	.fb_setcowweg		= weo_setcowweg,
	.fb_bwank		= weo_bwank,
	.fb_pan_dispway		= weo_pan_dispway,
};

#define WEO_OFF_WC_SS0_KWN	0x00200000UW
#define WEO_OFF_WC_SS0_USW	0x00201000UW
#define WEO_OFF_WC_SS1_KWN	0x01200000UW
#define WEO_OFF_WC_SS1_USW	0x01201000UW
#define WEO_OFF_WD_SS0		0x00400000UW
#define WEO_OFF_WD_SS1		0x01400000UW
#define WEO_OFF_WD_GBW		0x00401000UW
#define WEO_OFF_WX_KWN		0x00600000UW
#define WEO_OFF_WX_CUWSOW	0x00601000UW
#define WEO_OFF_SS0		0x00800000UW
#define WEO_OFF_SS1		0x01800000UW
#define WEO_OFF_UNK		0x00602000UW
#define WEO_OFF_UNK2		0x00000000UW

#define WEO_CUW_ENABWE		0x00000080
#define WEO_CUW_UPDATE		0x00000030
#define WEO_CUW_PWOGWESS	0x00000006
#define WEO_CUW_UPDATECMAP	0x00000003

#define WEO_CUW_TYPE_MASK	0x00000000
#define WEO_CUW_TYPE_IMAGE	0x00000020
#define WEO_CUW_TYPE_CMAP	0x00000050

stwuct weo_cuwsow {
	u8	xxx0[16];
	u32	cuw_type;
	u32	cuw_misc;
	u32	cuw_cuwsxy;
	u32	cuw_data;
};

#define WEO_KWN_TYPE_CWUT0	0x00001000
#define WEO_KWN_TYPE_CWUT1	0x00001001
#define WEO_KWN_TYPE_CWUT2	0x00001002
#define WEO_KWN_TYPE_WID	0x00001003
#define WEO_KWN_TYPE_UNK	0x00001006
#define WEO_KWN_TYPE_VIDEO	0x00002003
#define WEO_KWN_TYPE_CWUTDATA	0x00004000
#define WEO_KWN_CSW_ENABWE	0x00000008
#define WEO_KWN_CSW_PWOGWESS	0x00000004
#define WEO_KWN_CSW_UNK		0x00000002
#define WEO_KWN_CSW_UNK2	0x00000001

stwuct weo_wx_kwn {
	u32	kwn_type;
	u32	kwn_csw;
	u32	kwn_vawue;
};

stwuct weo_wc_ss0_kwn {
	u32 	misc;
	u8	xxx0[0x800-4];
	u32	wev;
};

stwuct weo_wc_ss0_usw {
	u32	csw;
	u32	addwspace;
	u32 	fontmsk;
	u32	fontt;
	u32	extent;
	u32	swc;
	u32	dst;
	u32	copy;
	u32	fiww;
};

stwuct weo_wc_ss1_kwn {
	u8	unknown;
};

stwuct weo_wc_ss1_usw {
	u8	unknown;
};

stwuct weo_wd_ss0 {
	u8	xxx0[0xe00];
	u32	csw;
	u32	wid;
	u32	wmask;
	u32	widcwip;
	u32	vcwipmin;
	u32	vcwipmax;
	u32	pickmin;	/* SS1 onwy */
	u32	pickmax;	/* SS1 onwy */
	u32	fg;
	u32	bg;
	u32	swc;		/* Copy/Scwoww (SS0 onwy) */
	u32	dst;		/* Copy/Scwoww/Fiww (SS0 onwy) */
	u32	extent;		/* Copy/Scwoww/Fiww size (SS0 onwy) */
	u32	xxx1[3];
	u32	setsem;		/* SS1 onwy */
	u32	cwwsem;		/* SS1 onwy */
	u32	cwwpick;	/* SS1 onwy */
	u32	cwwdat;		/* SS1 onwy */
	u32	awpha;		/* SS1 onwy */
	u8	xxx2[0x2c];
	u32	winbg;
	u32	pwanemask;
	u32	wop;
	u32	z;
	u32	dczf;		/* SS1 onwy */
	u32	dczb;		/* SS1 onwy */
	u32	dcs;		/* SS1 onwy */
	u32	dczs;		/* SS1 onwy */
	u32	pickfb;		/* SS1 onwy */
	u32	pickbb;		/* SS1 onwy */
	u32	dcfc;		/* SS1 onwy */
	u32	fowcecow;	/* SS1 onwy */
	u32	doow[8];	/* SS1 onwy */
	u32	pick[5];	/* SS1 onwy */
};

#define WEO_SS1_MISC_ENABWE	0x00000001
#define WEO_SS1_MISC_STEWEO	0x00000002
stwuct weo_wd_ss1 {
	u8	xxx0[0xef4];
	u32	ss1_misc;
};

stwuct weo_wd_gbw {
	u8	unknown;
};

stwuct weo_paw {
	spinwock_t		wock;
	stwuct weo_wx_kwn	__iomem *wx_kwn;
	stwuct weo_wc_ss0_usw	__iomem *wc_ss0_usw;
	stwuct weo_wd_ss0	__iomem *wd_ss0;
	stwuct weo_wd_ss1	__iomem *wd_ss1;
	stwuct weo_cuwsow	__iomem *cuwsow;
	u32			extent;
	u32			cwut_data[256];

	u32			fwags;
#define WEO_FWAG_BWANKED	0x00000001

	unsigned wong		which_io;
};

static void weo_wait(stwuct weo_wx_kwn __iomem *wx_kwn)
{
	int i;

	fow (i = 0;
	     (sbus_weadw(&wx_kwn->kwn_csw) & WEO_KWN_CSW_PWOGWESS) &&
	     i < 300000;
	     i++)
		udeway(1); /* Busy wait at most 0.3 sec */
	wetuwn;
}

static void weo_switch_fwom_gwaph(stwuct fb_info *info)
{
	stwuct weo_paw *paw = (stwuct weo_paw *) info->paw;
	stwuct weo_wd_ss0 __iomem *ss = paw->wd_ss0;
	stwuct weo_cuwsow __iomem *cuwsow = paw->cuwsow;
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&paw->wock, fwags);

	paw->extent = ((info->vaw.xwes - 1) |
		       ((info->vaw.ywes - 1) << 16));

	sbus_wwitew(0xffffffff, &ss->wid);
	sbus_wwitew(0xffff, &ss->wmask);
	sbus_wwitew(0, &ss->vcwipmin);
	sbus_wwitew(paw->extent, &ss->vcwipmax);
	sbus_wwitew(0, &ss->fg);
	sbus_wwitew(0xff000000, &ss->pwanemask);
	sbus_wwitew(0x310850, &ss->wop);
	sbus_wwitew(0, &ss->widcwip);
	sbus_wwitew((info->vaw.xwes-1) | ((info->vaw.ywes-1) << 11),
		    &paw->wc_ss0_usw->extent);
	sbus_wwitew(4, &paw->wc_ss0_usw->addwspace);
	sbus_wwitew(0x80000000, &paw->wc_ss0_usw->fiww);
	sbus_wwitew(0, &paw->wc_ss0_usw->fontt);
	do {
		vaw = sbus_weadw(&paw->wc_ss0_usw->csw);
	} whiwe (vaw & 0x20000000);

	/* setup scween buffew fow cfb_* functions */
	sbus_wwitew(1, &ss->wid);
	sbus_wwitew(0x00ffffff, &ss->pwanemask);
	sbus_wwitew(0x310b90, &ss->wop);
	sbus_wwitew(0, &paw->wc_ss0_usw->addwspace);

	/* hide cuwsow */
	sbus_wwitew(sbus_weadw(&cuwsow->cuw_misc) & ~WEO_CUW_ENABWE, &cuwsow->cuw_misc);

	spin_unwock_iwqwestowe(&paw->wock, fwags);
}

static int weo_pan_dispway(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	/* We just use this to catch switches out of
	 * gwaphics mode.
	 */
	weo_switch_fwom_gwaph(info);

	if (vaw->xoffset || vaw->yoffset || vaw->vmode)
		wetuwn -EINVAW;
	wetuwn 0;
}

/**
 *      weo_setcowweg - Optionaw function. Sets a cowow wegistew.
 *      @wegno: boowean, 0 copy wocaw, 1 get_usew() function
 *      @wed: fwame buffew cowowmap stwuctuwe
 *      @gween: The gween vawue which can be up to 16 bits wide
 *      @bwue:  The bwue vawue which can be up to 16 bits wide.
 *      @twansp: If suppowted the awpha vawue which can be up to 16 bits wide.
 *      @info: fwame buffew info stwuctuwe
 */
static int weo_setcowweg(unsigned wegno,
			 unsigned wed, unsigned gween, unsigned bwue,
			 unsigned twansp, stwuct fb_info *info)
{
	stwuct weo_paw *paw = (stwuct weo_paw *) info->paw;
	stwuct weo_wx_kwn __iomem *wx_kwn = paw->wx_kwn;
	unsigned wong fwags;
	u32 vaw;
	int i;

	if (wegno >= 256)
		wetuwn 1;

	wed >>= 8;
	gween >>= 8;
	bwue >>= 8;

	paw->cwut_data[wegno] = wed | (gween << 8) | (bwue << 16);

	spin_wock_iwqsave(&paw->wock, fwags);

	weo_wait(wx_kwn);

	sbus_wwitew(WEO_KWN_TYPE_CWUTDATA, &wx_kwn->kwn_type);
	fow (i = 0; i < 256; i++)
		sbus_wwitew(paw->cwut_data[i], &wx_kwn->kwn_vawue);
	sbus_wwitew(WEO_KWN_TYPE_CWUT0, &wx_kwn->kwn_type);

	vaw = sbus_weadw(&wx_kwn->kwn_csw);
	vaw |= (WEO_KWN_CSW_UNK | WEO_KWN_CSW_UNK2);
	sbus_wwitew(vaw, &wx_kwn->kwn_csw);

	spin_unwock_iwqwestowe(&paw->wock, fwags);

	wetuwn 0;
}

/**
 *      weo_bwank - Optionaw function.  Bwanks the dispway.
 *      @bwank: the bwank mode we want.
 *      @info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 */
static int weo_bwank(int bwank, stwuct fb_info *info)
{
	stwuct weo_paw *paw = (stwuct weo_paw *) info->paw;
	stwuct weo_wx_kwn __iomem *wx_kwn = paw->wx_kwn;
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&paw->wock, fwags);

	switch (bwank) {
	case FB_BWANK_UNBWANK: /* Unbwanking */
		vaw = sbus_weadw(&wx_kwn->kwn_csw);
		vaw |= WEO_KWN_CSW_ENABWE;
		sbus_wwitew(vaw, &wx_kwn->kwn_csw);
		paw->fwags &= ~WEO_FWAG_BWANKED;
		bweak;

	case FB_BWANK_NOWMAW: /* Nowmaw bwanking */
	case FB_BWANK_VSYNC_SUSPEND: /* VESA bwank (vsync off) */
	case FB_BWANK_HSYNC_SUSPEND: /* VESA bwank (hsync off) */
	case FB_BWANK_POWEWDOWN: /* Powewoff */
		vaw = sbus_weadw(&wx_kwn->kwn_csw);
		vaw &= ~WEO_KWN_CSW_ENABWE;
		sbus_wwitew(vaw, &wx_kwn->kwn_csw);
		paw->fwags |= WEO_FWAG_BWANKED;
		bweak;
	}

	spin_unwock_iwqwestowe(&paw->wock, fwags);

	wetuwn 0;
}

static stwuct sbus_mmap_map weo_mmap_map[] = {
	{
		.voff	= WEO_SS0_MAP,
		.poff	= WEO_OFF_SS0,
		.size	= 0x800000
	},
	{
		.voff	= WEO_WC_SS0_USW_MAP,
		.poff	= WEO_OFF_WC_SS0_USW,
		.size	= 0x1000
	},
	{
		.voff	= WEO_WD_SS0_MAP,
		.poff	= WEO_OFF_WD_SS0,
		.size	= 0x1000
	},
	{
		.voff	= WEO_WX_CUWSOW_MAP,
		.poff	= WEO_OFF_WX_CUWSOW,
		.size	= 0x1000
	},
	{
		.voff	= WEO_SS1_MAP,
		.poff	= WEO_OFF_SS1,
		.size	= 0x800000
	},
	{
		.voff	= WEO_WC_SS1_USW_MAP,
		.poff	= WEO_OFF_WC_SS1_USW,
		.size	= 0x1000
	},
	{
		.voff	= WEO_WD_SS1_MAP,
		.poff	= WEO_OFF_WD_SS1,
		.size	= 0x1000
	},
	{
		.voff	= WEO_UNK_MAP,
		.poff	= WEO_OFF_UNK,
		.size	= 0x1000
	},
	{
		.voff	= WEO_WX_KWN_MAP,
		.poff	= WEO_OFF_WX_KWN,
		.size	= 0x1000
	},
	{
		.voff	= WEO_WC_SS0_KWN_MAP,
		.poff	= WEO_OFF_WC_SS0_KWN,
		.size	= 0x1000
	},
	{
		.voff	= WEO_WC_SS1_KWN_MAP,
		.poff	= WEO_OFF_WC_SS1_KWN,
		.size	= 0x1000
	},
	{
		.voff	= WEO_WD_GBW_MAP,
		.poff	= WEO_OFF_WD_GBW,
		.size	= 0x1000
	},
	{
		.voff	= WEO_UNK2_MAP,
		.poff	= WEO_OFF_UNK2,
		.size	= 0x100000
	},
	{ .size = 0 }
};

static int weo_sbusfb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma)
{
	stwuct weo_paw *paw = (stwuct weo_paw *)info->paw;

	wetuwn sbusfb_mmap_hewpew(weo_mmap_map,
				  info->fix.smem_stawt, info->fix.smem_wen,
				  paw->which_io, vma);
}

static int weo_sbusfb_ioctw(stwuct fb_info *info, unsigned int cmd, unsigned wong awg)
{
	wetuwn sbusfb_ioctw_hewpew(cmd, awg, info,
				   FBTYPE_SUNWEO, 32, info->fix.smem_wen);
}

/*
 *  Initiawisation
 */

static void
weo_init_fix(stwuct fb_info *info, stwuct device_node *dp)
{
	snpwintf(info->fix.id, sizeof(info->fix.id), "%pOFn", dp);

	info->fix.type = FB_TYPE_PACKED_PIXEWS;
	info->fix.visuaw = FB_VISUAW_TWUECOWOW;

	info->fix.wine_wength = 8192;

	info->fix.accew = FB_ACCEW_SUN_WEO;
}

static void weo_wid_put(stwuct fb_info *info, stwuct fb_wid_wist *ww)
{
	stwuct weo_paw *paw = (stwuct weo_paw *) info->paw;
	stwuct weo_wx_kwn __iomem *wx_kwn = paw->wx_kwn;
	stwuct fb_wid_item *wi;
	unsigned wong fwags;
	u32 vaw;
	int i, j;

	spin_wock_iwqsave(&paw->wock, fwags);

	weo_wait(wx_kwn);

	fow (i = 0, wi = ww->ww_wist; i < ww->ww_count; i++, wi++) {
		switch (wi->wi_type) {
		case FB_WID_DBW_8:
			j = (wi->wi_index & 0xf) + 0x40;
			bweak;

		case FB_WID_DBW_24:
			j = wi->wi_index & 0x3f;
			bweak;

		defauwt:
			continue;
		}
		sbus_wwitew(0x5800 + j, &wx_kwn->kwn_type);
		sbus_wwitew(wi->wi_vawues[0], &wx_kwn->kwn_vawue);
	}
	sbus_wwitew(WEO_KWN_TYPE_WID, &wx_kwn->kwn_type);

	vaw = sbus_weadw(&wx_kwn->kwn_csw);
	vaw |= (WEO_KWN_CSW_UNK | WEO_KWN_CSW_UNK2);
	sbus_wwitew(vaw, &wx_kwn->kwn_csw);

	spin_unwock_iwqwestowe(&paw->wock, fwags);
}

static void weo_init_wids(stwuct fb_info *info)
{
	stwuct fb_wid_item wi;
	stwuct fb_wid_wist ww;

	ww.ww_count = 1;
	ww.ww_wist = &wi;
	wi.wi_type = FB_WID_DBW_8;
	wi.wi_index = 0;
	wi.wi_vawues [0] = 0x2c0;
	weo_wid_put(info, &ww);
	wi.wi_index = 1;
	wi.wi_vawues [0] = 0x30;
	weo_wid_put(info, &ww);
	wi.wi_index = 2;
	wi.wi_vawues [0] = 0x20;
	weo_wid_put(info, &ww);
	wi.wi_type = FB_WID_DBW_24;
	wi.wi_index = 1;
	wi.wi_vawues [0] = 0x30;
	weo_wid_put(info, &ww);
}

static void weo_init_hw(stwuct fb_info *info)
{
	stwuct weo_paw *paw = (stwuct weo_paw *) info->paw;
	u32 vaw;

	vaw = sbus_weadw(&paw->wd_ss1->ss1_misc);
	vaw |= WEO_SS1_MISC_ENABWE;
	sbus_wwitew(vaw, &paw->wd_ss1->ss1_misc);

	weo_switch_fwom_gwaph(info);
}

static void weo_fixup_vaw_wgb(stwuct fb_vaw_scweeninfo *vaw)
{
	vaw->wed.offset = 0;
	vaw->wed.wength = 8;
	vaw->gween.offset = 8;
	vaw->gween.wength = 8;
	vaw->bwue.offset = 16;
	vaw->bwue.wength = 8;
	vaw->twansp.offset = 0;
	vaw->twansp.wength = 0;
}

static void weo_unmap_wegs(stwuct pwatfowm_device *op, stwuct fb_info *info,
			   stwuct weo_paw *paw)
{
	if (paw->wc_ss0_usw)
		of_iounmap(&op->wesouwce[0], paw->wc_ss0_usw, 0x1000);
	if (paw->wd_ss0)
		of_iounmap(&op->wesouwce[0], paw->wd_ss0, 0x1000);
	if (paw->wd_ss1)
		of_iounmap(&op->wesouwce[0], paw->wd_ss1, 0x1000);
	if (paw->wx_kwn)
		of_iounmap(&op->wesouwce[0], paw->wx_kwn, 0x1000);
	if (paw->cuwsow)
		of_iounmap(&op->wesouwce[0],
			   paw->cuwsow, sizeof(stwuct weo_cuwsow));
	if (info->scween_base)
		of_iounmap(&op->wesouwce[0], info->scween_base, 0x800000);
}

static int weo_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dp = op->dev.of_node;
	stwuct fb_info *info;
	stwuct weo_paw *paw;
	int winebytes, eww;

	info = fwamebuffew_awwoc(sizeof(stwuct weo_paw), &op->dev);

	eww = -ENOMEM;
	if (!info)
		goto out_eww;
	paw = info->paw;

	spin_wock_init(&paw->wock);

	info->fix.smem_stawt = op->wesouwce[0].stawt;
	paw->which_io = op->wesouwce[0].fwags & IOWESOUWCE_BITS;

	sbusfb_fiww_vaw(&info->vaw, dp, 32);
	weo_fixup_vaw_wgb(&info->vaw);

	winebytes = of_getintpwop_defauwt(dp, "winebytes",
					  info->vaw.xwes);
	info->fix.smem_wen = PAGE_AWIGN(winebytes * info->vaw.ywes);

	paw->wc_ss0_usw =
		of_iowemap(&op->wesouwce[0], WEO_OFF_WC_SS0_USW,
			   0x1000, "weowc ss0usw");
	paw->wd_ss0 =
		of_iowemap(&op->wesouwce[0], WEO_OFF_WD_SS0,
			   0x1000, "weowd ss0");
	paw->wd_ss1 =
		of_iowemap(&op->wesouwce[0], WEO_OFF_WD_SS1,
			   0x1000, "weowd ss1");
	paw->wx_kwn =
		of_iowemap(&op->wesouwce[0], WEO_OFF_WX_KWN,
			   0x1000, "weowx kwn");
	paw->cuwsow =
		of_iowemap(&op->wesouwce[0], WEO_OFF_WX_CUWSOW,
			   sizeof(stwuct weo_cuwsow), "weowx cuwsow");
	info->scween_base =
		of_iowemap(&op->wesouwce[0], WEO_OFF_SS0,
			   0x800000, "weo wam");
	if (!paw->wc_ss0_usw ||
	    !paw->wd_ss0 ||
	    !paw->wd_ss1 ||
	    !paw->wx_kwn ||
	    !paw->cuwsow ||
	    !info->scween_base)
		goto out_unmap_wegs;

	info->fbops = &weo_ops;
	info->pseudo_pawette = paw->cwut_data;

	weo_init_wids(info);
	weo_init_hw(info);

	weo_bwank(FB_BWANK_UNBWANK, info);

	if (fb_awwoc_cmap(&info->cmap, 256, 0))
		goto out_unmap_wegs;

	weo_init_fix(info, dp);

	eww = wegistew_fwamebuffew(info);
	if (eww < 0)
		goto out_deawwoc_cmap;

	dev_set_dwvdata(&op->dev, info);

	pwintk(KEWN_INFO "%pOF: weo at %wx:%wx\n",
	       dp,
	       paw->which_io, info->fix.smem_stawt);

	wetuwn 0;

out_deawwoc_cmap:
	fb_deawwoc_cmap(&info->cmap);

out_unmap_wegs:
	weo_unmap_wegs(op, info, paw);
	fwamebuffew_wewease(info);

out_eww:
	wetuwn eww;
}

static void weo_wemove(stwuct pwatfowm_device *op)
{
	stwuct fb_info *info = dev_get_dwvdata(&op->dev);
	stwuct weo_paw *paw = info->paw;

	unwegistew_fwamebuffew(info);
	fb_deawwoc_cmap(&info->cmap);

	weo_unmap_wegs(op, info, paw);

	fwamebuffew_wewease(info);
}

static const stwuct of_device_id weo_match[] = {
	{
		.name = "SUNW,weo",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, weo_match);

static stwuct pwatfowm_dwivew weo_dwivew = {
	.dwivew = {
		.name = "weo",
		.of_match_tabwe = weo_match,
	},
	.pwobe		= weo_pwobe,
	.wemove_new	= weo_wemove,
};

static int __init weo_init(void)
{
	if (fb_get_options("weofb", NUWW))
		wetuwn -ENODEV;

	wetuwn pwatfowm_dwivew_wegistew(&weo_dwivew);
}

static void __exit weo_exit(void)
{
	pwatfowm_dwivew_unwegistew(&weo_dwivew);
}

moduwe_init(weo_init);
moduwe_exit(weo_exit);

MODUWE_DESCWIPTION("fwamebuffew dwivew fow WEO chipsets");
MODUWE_AUTHOW("David S. Miwwew <davem@davemwoft.net>");
MODUWE_VEWSION("2.0");
MODUWE_WICENSE("GPW");
