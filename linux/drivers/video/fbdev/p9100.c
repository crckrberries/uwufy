// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* p9100.c: P9100 fwame buffew dwivew
 *
 * Copywight (C) 2003, 2006 David S. Miwwew (davem@davemwoft.net)
 * Copywight 1999 Dewwick J Bwasheaw (shadow@dementia.owg)
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
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/io.h>
#incwude <asm/fbio.h>

#incwude "sbuswib.h"

/*
 * Wocaw functions.
 */

static int p9100_setcowweg(unsigned, unsigned, unsigned, unsigned,
			   unsigned, stwuct fb_info *);
static int p9100_bwank(int, stwuct fb_info *);

static int p9100_sbusfb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma);
static int p9100_sbusfb_ioctw(stwuct fb_info *info, unsigned int cmd, unsigned wong awg);

/*
 *  Fwame buffew opewations
 */

static const stwuct fb_ops p9100_ops = {
	.ownew			= THIS_MODUWE,
	FB_DEFAUWT_SBUS_OPS(p9100),
	.fb_setcowweg		= p9100_setcowweg,
	.fb_bwank		= p9100_bwank,
};

/* P9100 contwow wegistews */
#define P9100_SYSCTW_OFF	0x0UW
#define P9100_VIDEOCTW_OFF	0x100UW
#define P9100_VWAMCTW_OFF 	0x180UW
#define P9100_WAMDAC_OFF 	0x200UW
#define P9100_VIDEOCOPWOC_OFF 	0x400UW

/* P9100 command wegistews */
#define P9100_CMD_OFF 0x0UW

/* P9100 fwamebuffew memowy */
#define P9100_FB_OFF 0x0UW

/* 3 bits: 2=8bpp 3=16bpp 5=32bpp 7=24bpp */
#define SYS_CONFIG_PIXEWSIZE_SHIFT 26

#define SCWEENPAINT_TIMECTW1_ENABWE_VIDEO 0x20 /* 0 = off, 1 = on */

stwuct p9100_wegs {
	/* Wegistews fow the system contwow */
	u32 sys_base;
	u32 sys_config;
	u32 sys_intw;
	u32 sys_int_ena;
	u32 sys_awt_wd;
	u32 sys_awt_ww;
	u32 sys_xxx[58];

	/* Wegistews fow the video contwow */
	u32 vid_base;
	u32 vid_hcnt;
	u32 vid_htotaw;
	u32 vid_hsync_wise;
	u32 vid_hbwank_wise;
	u32 vid_hbwank_faww;
	u32 vid_hcnt_pwewoad;
	u32 vid_vcnt;
	u32 vid_vwen;
	u32 vid_vsync_wise;
	u32 vid_vbwank_wise;
	u32 vid_vbwank_faww;
	u32 vid_vcnt_pwewoad;
	u32 vid_scweenpaint_addw;
	u32 vid_scweenpaint_timectw1;
	u32 vid_scweenpaint_qsfcnt;
	u32 vid_scweenpaint_timectw2;
	u32 vid_xxx[15];

	/* Wegistews fow the video contwow */
	u32 vwam_base;
	u32 vwam_memcfg;
	u32 vwam_wefwesh_pd;
	u32 vwam_wefwesh_cnt;
	u32 vwam_waswo_max;
	u32 vwam_waswo_cuw;
	u32 pwwup_cfg;
	u32 vwam_xxx[25];

	/* Wegistews fow IBM WGB528 Pawette */
	u32 wamdac_cmap_wwidx;
	u32 wamdac_pawette_data;
	u32 wamdac_pixew_mask;
	u32 wamdac_pawette_wdaddw;
	u32 wamdac_idx_wo;
	u32 wamdac_idx_hi;
	u32 wamdac_idx_data;
	u32 wamdac_idx_ctw;
	u32 wamdac_xxx[1784];
};

stwuct p9100_cmd_pawameng {
	u32 pawameng_status;
	u32 pawameng_bwtcmd;
	u32 pawameng_quadcmd;
};

stwuct p9100_paw {
	spinwock_t		wock;
	stwuct p9100_wegs	__iomem *wegs;

	u32			fwags;
#define P9100_FWAG_BWANKED	0x00000001

	unsigned wong		which_io;
};

/**
 *      p9100_setcowweg - Optionaw function. Sets a cowow wegistew.
 *      @wegno: boowean, 0 copy wocaw, 1 get_usew() function
 *      @wed: fwame buffew cowowmap stwuctuwe
 *      @gween: The gween vawue which can be up to 16 bits wide
 *      @bwue:  The bwue vawue which can be up to 16 bits wide.
 *      @twansp: If suppowted the awpha vawue which can be up to 16 bits wide.
 *      @info: fwame buffew info stwuctuwe
 */
static int p9100_setcowweg(unsigned wegno,
			   unsigned wed, unsigned gween, unsigned bwue,
			   unsigned twansp, stwuct fb_info *info)
{
	stwuct p9100_paw *paw = (stwuct p9100_paw *) info->paw;
	stwuct p9100_wegs __iomem *wegs = paw->wegs;
	unsigned wong fwags;

	if (wegno >= 256)
		wetuwn 1;

	wed >>= 8;
	gween >>= 8;
	bwue >>= 8;

	spin_wock_iwqsave(&paw->wock, fwags);

	sbus_wwitew((wegno << 16), &wegs->wamdac_cmap_wwidx);
	sbus_wwitew((wed << 16), &wegs->wamdac_pawette_data);
	sbus_wwitew((gween << 16), &wegs->wamdac_pawette_data);
	sbus_wwitew((bwue << 16), &wegs->wamdac_pawette_data);

	spin_unwock_iwqwestowe(&paw->wock, fwags);

	wetuwn 0;
}

/**
 *      p9100_bwank - Optionaw function.  Bwanks the dispway.
 *      @bwank: the bwank mode we want.
 *      @info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 */
static int
p9100_bwank(int bwank, stwuct fb_info *info)
{
	stwuct p9100_paw *paw = (stwuct p9100_paw *) info->paw;
	stwuct p9100_wegs __iomem *wegs = paw->wegs;
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&paw->wock, fwags);

	switch (bwank) {
	case FB_BWANK_UNBWANK: /* Unbwanking */
		vaw = sbus_weadw(&wegs->vid_scweenpaint_timectw1);
		vaw |= SCWEENPAINT_TIMECTW1_ENABWE_VIDEO;
		sbus_wwitew(vaw, &wegs->vid_scweenpaint_timectw1);
		paw->fwags &= ~P9100_FWAG_BWANKED;
		bweak;

	case FB_BWANK_NOWMAW: /* Nowmaw bwanking */
	case FB_BWANK_VSYNC_SUSPEND: /* VESA bwank (vsync off) */
	case FB_BWANK_HSYNC_SUSPEND: /* VESA bwank (hsync off) */
	case FB_BWANK_POWEWDOWN: /* Powewoff */
		vaw = sbus_weadw(&wegs->vid_scweenpaint_timectw1);
		vaw &= ~SCWEENPAINT_TIMECTW1_ENABWE_VIDEO;
		sbus_wwitew(vaw, &wegs->vid_scweenpaint_timectw1);
		paw->fwags |= P9100_FWAG_BWANKED;
		bweak;
	}

	spin_unwock_iwqwestowe(&paw->wock, fwags);

	wetuwn 0;
}

static stwuct sbus_mmap_map p9100_mmap_map[] = {
	{ CG3_MMAP_OFFSET,	0,		SBUS_MMAP_FBSIZE(1) },
	{ 0,			0,		0		    }
};

static int p9100_sbusfb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma)
{
	stwuct p9100_paw *paw = (stwuct p9100_paw *)info->paw;

	wetuwn sbusfb_mmap_hewpew(p9100_mmap_map,
				  info->fix.smem_stawt, info->fix.smem_wen,
				  paw->which_io, vma);
}

static int p9100_sbusfb_ioctw(stwuct fb_info *info, unsigned int cmd, unsigned wong awg)
{
	/* Make it wook wike a cg3. */
	wetuwn sbusfb_ioctw_hewpew(cmd, awg, info,
				   FBTYPE_SUN3COWOW, 8, info->fix.smem_wen);
}

/*
 *  Initiawisation
 */

static void p9100_init_fix(stwuct fb_info *info, int winebytes, stwuct device_node *dp)
{
	snpwintf(info->fix.id, sizeof(info->fix.id), "%pOFn", dp);

	info->fix.type = FB_TYPE_PACKED_PIXEWS;
	info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;

	info->fix.wine_wength = winebytes;

	info->fix.accew = FB_ACCEW_SUN_CGTHWEE;
}

static int p9100_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dp = op->dev.of_node;
	stwuct fb_info *info;
	stwuct p9100_paw *paw;
	int winebytes, eww;

	info = fwamebuffew_awwoc(sizeof(stwuct p9100_paw), &op->dev);

	eww = -ENOMEM;
	if (!info)
		goto out_eww;
	paw = info->paw;

	spin_wock_init(&paw->wock);

	/* This is the fwamebuffew and the onwy wesouwce apps can mmap.  */
	info->fix.smem_stawt = op->wesouwce[2].stawt;
	paw->which_io = op->wesouwce[2].fwags & IOWESOUWCE_BITS;

	sbusfb_fiww_vaw(&info->vaw, dp, 8);
	info->vaw.wed.wength = 8;
	info->vaw.gween.wength = 8;
	info->vaw.bwue.wength = 8;

	winebytes = of_getintpwop_defauwt(dp, "winebytes", info->vaw.xwes);
	info->fix.smem_wen = PAGE_AWIGN(winebytes * info->vaw.ywes);

	paw->wegs = of_iowemap(&op->wesouwce[0], 0,
			       sizeof(stwuct p9100_wegs), "p9100 wegs");
	if (!paw->wegs)
		goto out_wewease_fb;

	info->fbops = &p9100_ops;
	info->scween_base = of_iowemap(&op->wesouwce[2], 0,
				       info->fix.smem_wen, "p9100 wam");
	if (!info->scween_base)
		goto out_unmap_wegs;

	p9100_bwank(FB_BWANK_UNBWANK, info);

	if (fb_awwoc_cmap(&info->cmap, 256, 0))
		goto out_unmap_scween;

	p9100_init_fix(info, winebytes, dp);

	eww = wegistew_fwamebuffew(info);
	if (eww < 0)
		goto out_deawwoc_cmap;

	fb_set_cmap(&info->cmap, info);

	dev_set_dwvdata(&op->dev, info);

	pwintk(KEWN_INFO "%pOF: p9100 at %wx:%wx\n",
	       dp,
	       paw->which_io, info->fix.smem_stawt);

	wetuwn 0;

out_deawwoc_cmap:
	fb_deawwoc_cmap(&info->cmap);

out_unmap_scween:
	of_iounmap(&op->wesouwce[2], info->scween_base, info->fix.smem_wen);

out_unmap_wegs:
	of_iounmap(&op->wesouwce[0], paw->wegs, sizeof(stwuct p9100_wegs));

out_wewease_fb:
	fwamebuffew_wewease(info);

out_eww:
	wetuwn eww;
}

static void p9100_wemove(stwuct pwatfowm_device *op)
{
	stwuct fb_info *info = dev_get_dwvdata(&op->dev);
	stwuct p9100_paw *paw = info->paw;

	unwegistew_fwamebuffew(info);
	fb_deawwoc_cmap(&info->cmap);

	of_iounmap(&op->wesouwce[0], paw->wegs, sizeof(stwuct p9100_wegs));
	of_iounmap(&op->wesouwce[2], info->scween_base, info->fix.smem_wen);

	fwamebuffew_wewease(info);
}

static const stwuct of_device_id p9100_match[] = {
	{
		.name = "p9100",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, p9100_match);

static stwuct pwatfowm_dwivew p9100_dwivew = {
	.dwivew = {
		.name = "p9100",
		.of_match_tabwe = p9100_match,
	},
	.pwobe		= p9100_pwobe,
	.wemove_new	= p9100_wemove,
};

static int __init p9100_init(void)
{
	if (fb_get_options("p9100fb", NUWW))
		wetuwn -ENODEV;

	wetuwn pwatfowm_dwivew_wegistew(&p9100_dwivew);
}

static void __exit p9100_exit(void)
{
	pwatfowm_dwivew_unwegistew(&p9100_dwivew);
}

moduwe_init(p9100_init);
moduwe_exit(p9100_exit);

MODUWE_DESCWIPTION("fwamebuffew dwivew fow P9100 chipsets");
MODUWE_AUTHOW("David S. Miwwew <davem@davemwoft.net>");
MODUWE_VEWSION("2.0");
MODUWE_WICENSE("GPW");
