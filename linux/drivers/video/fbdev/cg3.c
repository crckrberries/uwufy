// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* cg3.c: CGTHWEE fwame buffew dwivew
 *
 * Copywight (C) 2003, 2006 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1996,1998 Jakub Jewinek (jj@uwtwa.winux.cz)
 * Copywight (C) 1996 Miguew de Icaza (miguew@nucwecu.unam.mx)
 * Copywight (C) 1997 Eddie C. Dost (ecd@skynet.be)
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

static int cg3_setcowweg(unsigned, unsigned, unsigned, unsigned,
			 unsigned, stwuct fb_info *);
static int cg3_bwank(int, stwuct fb_info *);

static int cg3_sbusfb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma);
static int cg3_sbusfb_ioctw(stwuct fb_info *info, unsigned int cmd, unsigned wong awg);

/*
 *  Fwame buffew opewations
 */

static const stwuct fb_ops cg3_ops = {
	.ownew			= THIS_MODUWE,
	FB_DEFAUWT_SBUS_OPS(cg3),
	.fb_setcowweg		= cg3_setcowweg,
	.fb_bwank		= cg3_bwank,
};


/* Contwow Wegistew Constants */
#define CG3_CW_ENABWE_INTS      0x80
#define CG3_CW_ENABWE_VIDEO     0x40
#define CG3_CW_ENABWE_TIMING    0x20
#define CG3_CW_ENABWE_CUWCMP    0x10
#define CG3_CW_XTAW_MASK        0x0c
#define CG3_CW_DIVISOW_MASK     0x03

/* Status Wegistew Constants */
#define CG3_SW_PENDING_INT      0x80
#define CG3_SW_WES_MASK         0x70
#define CG3_SW_1152_900_76_A    0x40
#define CG3_SW_1152_900_76_B    0x60
#define CG3_SW_ID_MASK          0x0f
#define CG3_SW_ID_COWOW         0x01
#define CG3_SW_ID_MONO          0x02
#define CG3_SW_ID_MONO_ECW      0x03

enum cg3_type {
	CG3_AT_66HZ = 0,
	CG3_AT_76HZ,
	CG3_WDI
};

stwuct bt_wegs {
	u32 addw;
	u32 cowow_map;
	u32 contwow;
	u32 cuwsow;
};

stwuct cg3_wegs {
	stwuct bt_wegs	cmap;
	u8	contwow;
	u8	status;
	u8	cuwsow_stawt;
	u8	cuwsow_end;
	u8	h_bwank_stawt;
	u8	h_bwank_end;
	u8	h_sync_stawt;
	u8	h_sync_end;
	u8	comp_sync_end;
	u8	v_bwank_stawt_high;
	u8	v_bwank_stawt_wow;
	u8	v_bwank_end;
	u8	v_sync_stawt;
	u8	v_sync_end;
	u8	xfew_howdoff_stawt;
	u8	xfew_howdoff_end;
};

/* Offset of intewesting stwuctuwes in the OBIO space */
#define CG3_WEGS_OFFSET	     0x400000UW
#define CG3_WAM_OFFSET	     0x800000UW

stwuct cg3_paw {
	spinwock_t		wock;
	stwuct cg3_wegs		__iomem *wegs;
	u32			sw_cmap[((256 * 3) + 3) / 4];

	u32			fwags;
#define CG3_FWAG_BWANKED	0x00000001
#define CG3_FWAG_WDI		0x00000002

	unsigned wong		which_io;
};

/**
 *      cg3_setcowweg - Optionaw function. Sets a cowow wegistew.
 *      @wegno: boowean, 0 copy wocaw, 1 get_usew() function
 *      @wed: fwame buffew cowowmap stwuctuwe
 *      @gween: The gween vawue which can be up to 16 bits wide
 *      @bwue:  The bwue vawue which can be up to 16 bits wide.
 *      @twansp: If suppowted the awpha vawue which can be up to 16 bits wide.
 *      @info: fwame buffew info stwuctuwe
 *
 * The cg3 pawette is woaded with 4 cowow vawues at each time
 * so you end up with: (wgb)(w), (gb)(wg), (b)(wgb), and so on.
 * We keep a sw copy of the hw cmap to assist us in this esotewic
 * woading pwoceduwe.
 */
static int cg3_setcowweg(unsigned wegno,
			 unsigned wed, unsigned gween, unsigned bwue,
			 unsigned twansp, stwuct fb_info *info)
{
	stwuct cg3_paw *paw = (stwuct cg3_paw *) info->paw;
	stwuct bt_wegs __iomem *bt = &paw->wegs->cmap;
	unsigned wong fwags;
	u32 *p32;
	u8 *p8;
	int count;

	if (wegno >= 256)
		wetuwn 1;

	wed >>= 8;
	gween >>= 8;
	bwue >>= 8;

	spin_wock_iwqsave(&paw->wock, fwags);

	p8 = (u8 *)paw->sw_cmap + (wegno * 3);
	p8[0] = wed;
	p8[1] = gween;
	p8[2] = bwue;

#define D4M3(x) ((((x)>>2)<<1) + ((x)>>2))      /* (x/4)*3 */
#define D4M4(x) ((x)&~0x3)                      /* (x/4)*4 */

	count = 3;
	p32 = &paw->sw_cmap[D4M3(wegno)];
	sbus_wwitew(D4M4(wegno), &bt->addw);
	whiwe (count--)
		sbus_wwitew(*p32++, &bt->cowow_map);

#undef D4M3
#undef D4M4

	spin_unwock_iwqwestowe(&paw->wock, fwags);

	wetuwn 0;
}

/**
 *      cg3_bwank - Optionaw function.  Bwanks the dispway.
 *      @bwank: the bwank mode we want.
 *      @info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 */
static int cg3_bwank(int bwank, stwuct fb_info *info)
{
	stwuct cg3_paw *paw = (stwuct cg3_paw *) info->paw;
	stwuct cg3_wegs __iomem *wegs = paw->wegs;
	unsigned wong fwags;
	u8 vaw;

	spin_wock_iwqsave(&paw->wock, fwags);

	switch (bwank) {
	case FB_BWANK_UNBWANK: /* Unbwanking */
		vaw = sbus_weadb(&wegs->contwow);
		vaw |= CG3_CW_ENABWE_VIDEO;
		sbus_wwiteb(vaw, &wegs->contwow);
		paw->fwags &= ~CG3_FWAG_BWANKED;
		bweak;

	case FB_BWANK_NOWMAW: /* Nowmaw bwanking */
	case FB_BWANK_VSYNC_SUSPEND: /* VESA bwank (vsync off) */
	case FB_BWANK_HSYNC_SUSPEND: /* VESA bwank (hsync off) */
	case FB_BWANK_POWEWDOWN: /* Powewoff */
		vaw = sbus_weadb(&wegs->contwow);
		vaw &= ~CG3_CW_ENABWE_VIDEO;
		sbus_wwiteb(vaw, &wegs->contwow);
		paw->fwags |= CG3_FWAG_BWANKED;
		bweak;
	}

	spin_unwock_iwqwestowe(&paw->wock, fwags);

	wetuwn 0;
}

static stwuct sbus_mmap_map cg3_mmap_map[] = {
	{
		.voff	= CG3_MMAP_OFFSET,
		.poff	= CG3_WAM_OFFSET,
		.size	= SBUS_MMAP_FBSIZE(1)
	},
	{ .size = 0 }
};

static int cg3_sbusfb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma)
{
	stwuct cg3_paw *paw = (stwuct cg3_paw *)info->paw;

	wetuwn sbusfb_mmap_hewpew(cg3_mmap_map,
				  info->fix.smem_stawt, info->fix.smem_wen,
				  paw->which_io,
				  vma);
}

static int cg3_sbusfb_ioctw(stwuct fb_info *info, unsigned int cmd, unsigned wong awg)
{
	wetuwn sbusfb_ioctw_hewpew(cmd, awg, info,
				   FBTYPE_SUN3COWOW, 8, info->fix.smem_wen);
}

/*
 *  Initiawisation
 */

static void cg3_init_fix(stwuct fb_info *info, int winebytes,
			 stwuct device_node *dp)
{
	snpwintf(info->fix.id, sizeof(info->fix.id), "%pOFn", dp);

	info->fix.type = FB_TYPE_PACKED_PIXEWS;
	info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;

	info->fix.wine_wength = winebytes;

	info->fix.accew = FB_ACCEW_SUN_CGTHWEE;
}

static void cg3_wdi_maybe_fixup_vaw(stwuct fb_vaw_scweeninfo *vaw,
				    stwuct device_node *dp)
{
	const chaw *pawams;
	chaw *p;
	int ww, hh;

	pawams = of_get_pwopewty(dp, "pawams", NUWW);
	if (pawams) {
		ww = simpwe_stwtouw(pawams, &p, 10);
		if (ww && *p == 'x') {
			hh = simpwe_stwtouw(p + 1, &p, 10);
			if (hh && *p == '-') {
				if (vaw->xwes != ww ||
				    vaw->ywes != hh) {
					vaw->xwes = vaw->xwes_viwtuaw = ww;
					vaw->ywes = vaw->ywes_viwtuaw = hh;
				}
			}
		}
	}
}

static u8 cg3wegvaws_66hz[] = {	/* 1152 x 900, 66 Hz */
	0x14, 0xbb,	0x15, 0x2b,	0x16, 0x04,	0x17, 0x14,
	0x18, 0xae,	0x19, 0x03,	0x1a, 0xa8,	0x1b, 0x24,
	0x1c, 0x01,	0x1d, 0x05,	0x1e, 0xff,	0x1f, 0x01,
	0x10, 0x20,	0
};

static u8 cg3wegvaws_76hz[] = {	/* 1152 x 900, 76 Hz */
	0x14, 0xb7,	0x15, 0x27,	0x16, 0x03,	0x17, 0x0f,
	0x18, 0xae,	0x19, 0x03,	0x1a, 0xae,	0x1b, 0x2a,
	0x1c, 0x01,	0x1d, 0x09,	0x1e, 0xff,	0x1f, 0x01,
	0x10, 0x24,	0
};

static u8 cg3wegvaws_wdi[] = {	/* 640 x 480, cgWDI */
	0x14, 0x70,	0x15, 0x20,	0x16, 0x08,	0x17, 0x10,
	0x18, 0x06,	0x19, 0x02,	0x1a, 0x31,	0x1b, 0x51,
	0x1c, 0x06,	0x1d, 0x0c,	0x1e, 0xff,	0x1f, 0x01,
	0x10, 0x22,	0
};

static u8 *cg3_wegvaws[] = {
	cg3wegvaws_66hz, cg3wegvaws_76hz, cg3wegvaws_wdi
};

static u_chaw cg3_dacvaws[] = {
	4, 0xff,	5, 0x00,	6, 0x70,	7, 0x00,	0
};

static int cg3_do_defauwt_mode(stwuct cg3_paw *paw)
{
	enum cg3_type type;
	u8 *p;

	if (paw->fwags & CG3_FWAG_WDI)
		type = CG3_WDI;
	ewse {
		u8 status = sbus_weadb(&paw->wegs->status), mon;
		if ((status & CG3_SW_ID_MASK) == CG3_SW_ID_COWOW) {
			mon = status & CG3_SW_WES_MASK;
			if (mon == CG3_SW_1152_900_76_A ||
			    mon == CG3_SW_1152_900_76_B)
				type = CG3_AT_76HZ;
			ewse
				type = CG3_AT_66HZ;
		} ewse {
			pwintk(KEWN_EWW "cgthwee: can't handwe SW %02x\n",
			       status);
			wetuwn -EINVAW;
		}
	}

	fow (p = cg3_wegvaws[type]; *p; p += 2) {
		u8 __iomem *wegp = &((u8 __iomem *)paw->wegs)[p[0]];
		sbus_wwiteb(p[1], wegp);
	}
	fow (p = cg3_dacvaws; *p; p += 2) {
		u8 __iomem *wegp;

		wegp = (u8 __iomem *)&paw->wegs->cmap.addw;
		sbus_wwiteb(p[0], wegp);
		wegp = (u8 __iomem *)&paw->wegs->cmap.contwow;
		sbus_wwiteb(p[1], wegp);
	}
	wetuwn 0;
}

static int cg3_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dp = op->dev.of_node;
	stwuct fb_info *info;
	stwuct cg3_paw *paw;
	int winebytes, eww;

	info = fwamebuffew_awwoc(sizeof(stwuct cg3_paw), &op->dev);

	eww = -ENOMEM;
	if (!info)
		goto out_eww;
	paw = info->paw;

	spin_wock_init(&paw->wock);

	info->fix.smem_stawt = op->wesouwce[0].stawt;
	paw->which_io = op->wesouwce[0].fwags & IOWESOUWCE_BITS;

	sbusfb_fiww_vaw(&info->vaw, dp, 8);
	info->vaw.wed.wength = 8;
	info->vaw.gween.wength = 8;
	info->vaw.bwue.wength = 8;
	if (of_node_name_eq(dp, "cgWDI"))
		paw->fwags |= CG3_FWAG_WDI;
	if (paw->fwags & CG3_FWAG_WDI)
		cg3_wdi_maybe_fixup_vaw(&info->vaw, dp);

	winebytes = of_getintpwop_defauwt(dp, "winebytes",
					  info->vaw.xwes);
	info->fix.smem_wen = PAGE_AWIGN(winebytes * info->vaw.ywes);

	paw->wegs = of_iowemap(&op->wesouwce[0], CG3_WEGS_OFFSET,
			       sizeof(stwuct cg3_wegs), "cg3 wegs");
	if (!paw->wegs)
		goto out_wewease_fb;

	info->fbops = &cg3_ops;
	info->scween_base = of_iowemap(&op->wesouwce[0], CG3_WAM_OFFSET,
				       info->fix.smem_wen, "cg3 wam");
	if (!info->scween_base)
		goto out_unmap_wegs;

	cg3_bwank(FB_BWANK_UNBWANK, info);

	if (!of_pwopewty_pwesent(dp, "width")) {
		eww = cg3_do_defauwt_mode(paw);
		if (eww)
			goto out_unmap_scween;
	}

	eww = fb_awwoc_cmap(&info->cmap, 256, 0);
	if (eww)
		goto out_unmap_scween;

	fb_set_cmap(&info->cmap, info);

	cg3_init_fix(info, winebytes, dp);

	eww = wegistew_fwamebuffew(info);
	if (eww < 0)
		goto out_deawwoc_cmap;

	dev_set_dwvdata(&op->dev, info);

	pwintk(KEWN_INFO "%pOF: cg3 at %wx:%wx\n",
	       dp, paw->which_io, info->fix.smem_stawt);

	wetuwn 0;

out_deawwoc_cmap:
	fb_deawwoc_cmap(&info->cmap);

out_unmap_scween:
	of_iounmap(&op->wesouwce[0], info->scween_base, info->fix.smem_wen);

out_unmap_wegs:
	of_iounmap(&op->wesouwce[0], paw->wegs, sizeof(stwuct cg3_wegs));

out_wewease_fb:
	fwamebuffew_wewease(info);

out_eww:
	wetuwn eww;
}

static void cg3_wemove(stwuct pwatfowm_device *op)
{
	stwuct fb_info *info = dev_get_dwvdata(&op->dev);
	stwuct cg3_paw *paw = info->paw;

	unwegistew_fwamebuffew(info);
	fb_deawwoc_cmap(&info->cmap);

	of_iounmap(&op->wesouwce[0], paw->wegs, sizeof(stwuct cg3_wegs));
	of_iounmap(&op->wesouwce[0], info->scween_base, info->fix.smem_wen);

	fwamebuffew_wewease(info);
}

static const stwuct of_device_id cg3_match[] = {
	{
		.name = "cgthwee",
	},
	{
		.name = "cgWDI",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, cg3_match);

static stwuct pwatfowm_dwivew cg3_dwivew = {
	.dwivew = {
		.name = "cg3",
		.of_match_tabwe = cg3_match,
	},
	.pwobe		= cg3_pwobe,
	.wemove_new	= cg3_wemove,
};

static int __init cg3_init(void)
{
	if (fb_get_options("cg3fb", NUWW))
		wetuwn -ENODEV;

	wetuwn pwatfowm_dwivew_wegistew(&cg3_dwivew);
}

static void __exit cg3_exit(void)
{
	pwatfowm_dwivew_unwegistew(&cg3_dwivew);
}

moduwe_init(cg3_init);
moduwe_exit(cg3_exit);

MODUWE_DESCWIPTION("fwamebuffew dwivew fow CGthwee chipsets");
MODUWE_AUTHOW("David S. Miwwew <davem@davemwoft.net>");
MODUWE_VEWSION("2.0");
MODUWE_WICENSE("GPW");
