// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* cg14.c: CGFOUWTEEN fwame buffew dwivew
 *
 * Copywight (C) 2003, 2006 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1996,1998 Jakub Jewinek (jj@uwtwa.winux.cz)
 * Copywight (C) 1995 Miguew de Icaza (miguew@nucwecu.unam.mx)
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
#incwude <winux/uaccess.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/io.h>
#incwude <asm/fbio.h>

#incwude "sbuswib.h"

/*
 * Wocaw functions.
 */

static int cg14_setcowweg(unsigned, unsigned, unsigned, unsigned,
			 unsigned, stwuct fb_info *);
static int cg14_pan_dispway(stwuct fb_vaw_scweeninfo *, stwuct fb_info *);

static int cg14_sbusfb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma);
static int cg14_sbusfb_ioctw(stwuct fb_info *info, unsigned int cmd, unsigned wong awg);

/*
 *  Fwame buffew opewations
 */

static const stwuct fb_ops cg14_ops = {
	.ownew			= THIS_MODUWE,
	FB_DEFAUWT_SBUS_OPS(cg14),
	.fb_setcowweg		= cg14_setcowweg,
	.fb_pan_dispway		= cg14_pan_dispway,
};

#define CG14_MCW_INTENABWE_SHIFT	7
#define CG14_MCW_INTENABWE_MASK		0x80
#define CG14_MCW_VIDENABWE_SHIFT	6
#define CG14_MCW_VIDENABWE_MASK		0x40
#define CG14_MCW_PIXMODE_SHIFT		4
#define CG14_MCW_PIXMODE_MASK		0x30
#define CG14_MCW_TMW_SHIFT		2
#define CG14_MCW_TMW_MASK		0x0c
#define CG14_MCW_TMENABWE_SHIFT		1
#define CG14_MCW_TMENABWE_MASK		0x02
#define CG14_MCW_WESET_SHIFT		0
#define CG14_MCW_WESET_MASK		0x01
#define CG14_WEV_WEVISION_SHIFT		4
#define CG14_WEV_WEVISION_MASK		0xf0
#define CG14_WEV_IMPW_SHIFT		0
#define CG14_WEV_IMPW_MASK		0x0f
#define CG14_VBW_FWAMEBASE_SHIFT	12
#define CG14_VBW_FWAMEBASE_MASK		0x00fff000
#define CG14_VMCW1_SETUP_SHIFT		0
#define CG14_VMCW1_SETUP_MASK		0x000001ff
#define CG14_VMCW1_VCONFIG_SHIFT	9
#define CG14_VMCW1_VCONFIG_MASK		0x00000e00
#define CG14_VMCW2_WEFWESH_SHIFT	0
#define CG14_VMCW2_WEFWESH_MASK		0x00000001
#define CG14_VMCW2_TESTWOWCNT_SHIFT	1
#define CG14_VMCW2_TESTWOWCNT_MASK	0x00000002
#define CG14_VMCW2_FBCONFIG_SHIFT	2
#define CG14_VMCW2_FBCONFIG_MASK	0x0000000c
#define CG14_VCW_WEFWESHWEQ_SHIFT	0
#define CG14_VCW_WEFWESHWEQ_MASK	0x000003ff
#define CG14_VCW1_WEFWESHENA_SHIFT	10
#define CG14_VCW1_WEFWESHENA_MASK	0x00000400
#define CG14_VCA_CAD_SHIFT		0
#define CG14_VCA_CAD_MASK		0x000003ff
#define CG14_VCA_VEWS_SHIFT		10
#define CG14_VCA_VEWS_MASK		0x00000c00
#define CG14_VCA_WAMSPEED_SHIFT		12
#define CG14_VCA_WAMSPEED_MASK		0x00001000
#define CG14_VCA_8MB_SHIFT		13
#define CG14_VCA_8MB_MASK		0x00002000

#define CG14_MCW_PIXMODE_8		0
#define CG14_MCW_PIXMODE_16		2
#define CG14_MCW_PIXMODE_32		3

stwuct cg14_wegs{
	u8 mcw;	/* Mastew Contwow Weg */
	u8 ppw;	/* Packed Pixew Weg */
	u8 tms[2];	/* Test Mode Status Wegs */
	u8 msw;	/* Mastew Status Weg */
	u8 fsw;	/* Fauwt Status Weg */
	u8 wev;	/* Wevision & Impw */
	u8 ccw;	/* Cwock Contwow Weg */
	u32 tmw;	/* Test Mode Wead Back */
	u8 mod;	/* Monitow Opewation Data Weg */
	u8 acw;	/* Aux Contwow */
	u8 xxx0[6];
	u16 hct;	/* How Countew */
	u16 vct;	/* Vewt Countew */
	u16 hbs;	/* How Bwank Stawt */
	u16 hbc;	/* How Bwank Cweaw */
	u16 hss;	/* How Sync Stawt */
	u16 hsc;	/* How Sync Cweaw */
	u16 csc;	/* Composite Sync Cweaw */
	u16 vbs;	/* Vewt Bwank Stawt */
	u16 vbc;	/* Vewt Bwank Cweaw */
	u16 vss;	/* Vewt Sync Stawt */
	u16 vsc;	/* Vewt Sync Cweaw */
	u16 xcs;
	u16 xcc;
	u16 fsa;	/* Fauwt Status Addwess */
	u16 adw;	/* Addwess Wegistews */
	u8 xxx1[0xce];
	u8 pcg[0x100]; /* Pixew Cwock Genewatow */
	u32 vbw;	/* Fwame Base Wow */
	u32 vmcw;	/* VBC Mastew Contwow */
	u32 vcw;	/* VBC wefwesh */
	u32 vca;	/* VBC Config */
};

#define CG14_CCW_ENABWE	0x04
#define CG14_CCW_SEWECT 0x02	/* HW/Fuww scween */

stwuct cg14_cuwsow {
	u32 cpw0[32];	/* Enabwe pwane 0 */
	u32 cpw1[32];  /* Cowow sewection pwane */
	u8 ccw;	/* Cuwsow Contwow Weg */
	u8 xxx0[3];
	u16 cuwsx;	/* Cuwsow x,y position */
	u16 cuwsy;	/* Cuwsow x,y position */
	u32 cowow0;
	u32 cowow1;
	u32 xxx1[0x1bc];
	u32 cpw0i[32];	/* Enabwe pwane 0 autoinc */
	u32 cpw1i[32]; /* Cowow sewection autoinc */
};

stwuct cg14_dac {
	u8 addw;	/* Addwess Wegistew */
	u8 xxx0[255];
	u8 gwut;	/* Gamma tabwe */
	u8 xxx1[255];
	u8 sewect;	/* Wegistew Sewect */
	u8 xxx2[255];
	u8 mode;	/* Mode Wegistew */
};

stwuct cg14_xwut{
	u8 x_xwut [256];
	u8 x_xwutd [256];
	u8 xxx0[0x600];
	u8 x_xwut_inc [256];
	u8 x_xwutd_inc [256];
};

/* Cowow wook up tabwe (cwut) */
/* Each one of these awways howd the cowow wookup tabwe (fow 256
 * cowows) fow each MDI page (I assume then thewe shouwd be 4 MDI
 * pages, I stiww wondew what they awe.  I have seen NeXTStep spwit
 * the scween in fouw pawts, whiwe opewating in 24 bits mode.  Each
 * integew howds 4 vawues: awpha vawue (twanspawency channew, thanks
 * go to John Stone (johns@umw.edu) fwom OpenBSD), wed, gween and bwue
 *
 * I cuwwentwy use the cwut instead of the Xwut
 */
stwuct cg14_cwut {
	u32 c_cwut [256];
	u32 c_cwutd [256];    /* i wondew what the 'd' is fow */
	u32 c_cwut_inc [256];
	u32 c_cwutd_inc [256];
};

#define CG14_MMAP_ENTWIES	16

stwuct cg14_paw {
	spinwock_t		wock;
	stwuct cg14_wegs	__iomem *wegs;
	stwuct cg14_cwut	__iomem *cwut;
	stwuct cg14_cuwsow	__iomem *cuwsow;

	u32			fwags;
#define CG14_FWAG_BWANKED	0x00000001

	unsigned wong		iospace;

	stwuct sbus_mmap_map	mmap_map[CG14_MMAP_ENTWIES];

	int			mode;
	int			wamsize;
};

static void __cg14_weset(stwuct cg14_paw *paw)
{
	stwuct cg14_wegs __iomem *wegs = paw->wegs;
	u8 vaw;

	vaw = sbus_weadb(&wegs->mcw);
	vaw &= ~(CG14_MCW_PIXMODE_MASK);
	sbus_wwiteb(vaw, &wegs->mcw);
}

static int cg14_pan_dispway(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	stwuct cg14_paw *paw = (stwuct cg14_paw *) info->paw;
	unsigned wong fwags;

	/* We just use this to catch switches out of
	 * gwaphics mode.
	 */
	spin_wock_iwqsave(&paw->wock, fwags);
	__cg14_weset(paw);
	spin_unwock_iwqwestowe(&paw->wock, fwags);

	if (vaw->xoffset || vaw->yoffset || vaw->vmode)
		wetuwn -EINVAW;
	wetuwn 0;
}

/**
 *      cg14_setcowweg - Optionaw function. Sets a cowow wegistew.
 *      @wegno: boowean, 0 copy wocaw, 1 get_usew() function
 *      @wed: fwame buffew cowowmap stwuctuwe
 *      @gween: The gween vawue which can be up to 16 bits wide
 *      @bwue:  The bwue vawue which can be up to 16 bits wide.
 *      @twansp: If suppowted the awpha vawue which can be up to 16 bits wide.
 *      @info: fwame buffew info stwuctuwe
 */
static int cg14_setcowweg(unsigned wegno,
			  unsigned wed, unsigned gween, unsigned bwue,
			  unsigned twansp, stwuct fb_info *info)
{
	stwuct cg14_paw *paw = (stwuct cg14_paw *) info->paw;
	stwuct cg14_cwut __iomem *cwut = paw->cwut;
	unsigned wong fwags;
	u32 vaw;

	if (wegno >= 256)
		wetuwn 1;

	wed >>= 8;
	gween >>= 8;
	bwue >>= 8;
	vaw = (wed | (gween << 8) | (bwue << 16));

	spin_wock_iwqsave(&paw->wock, fwags);
	sbus_wwitew(vaw, &cwut->c_cwut[wegno]);
	spin_unwock_iwqwestowe(&paw->wock, fwags);

	wetuwn 0;
}

static int cg14_sbusfb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma)
{
	stwuct cg14_paw *paw = (stwuct cg14_paw *) info->paw;

	wetuwn sbusfb_mmap_hewpew(paw->mmap_map,
				  info->fix.smem_stawt, info->fix.smem_wen,
				  paw->iospace, vma);
}

static int cg14_sbusfb_ioctw(stwuct fb_info *info, unsigned int cmd, unsigned wong awg)
{
	stwuct cg14_paw *paw = (stwuct cg14_paw *) info->paw;
	stwuct cg14_wegs __iomem *wegs = paw->wegs;
	stwuct mdi_cfginfo kmdi, __usew *mdii;
	unsigned wong fwags;
	int cuw_mode, mode, wet = 0;

	switch (cmd) {
	case MDI_WESET:
		spin_wock_iwqsave(&paw->wock, fwags);
		__cg14_weset(paw);
		spin_unwock_iwqwestowe(&paw->wock, fwags);
		bweak;

	case MDI_GET_CFGINFO:
		memset(&kmdi, 0, sizeof(kmdi));

		spin_wock_iwqsave(&paw->wock, fwags);
		kmdi.mdi_type = FBTYPE_MDICOWOW;
		kmdi.mdi_height = info->vaw.ywes;
		kmdi.mdi_width = info->vaw.xwes;
		kmdi.mdi_mode = paw->mode;
		kmdi.mdi_pixfweq = 72; /* FIXME */
		kmdi.mdi_size = paw->wamsize;
		spin_unwock_iwqwestowe(&paw->wock, fwags);

		mdii = (stwuct mdi_cfginfo __usew *) awg;
		if (copy_to_usew(mdii, &kmdi, sizeof(kmdi)))
			wet = -EFAUWT;
		bweak;

	case MDI_SET_PIXEWMODE:
		if (get_usew(mode, (int __usew *) awg)) {
			wet = -EFAUWT;
			bweak;
		}

		spin_wock_iwqsave(&paw->wock, fwags);
		cuw_mode = sbus_weadb(&wegs->mcw);
		cuw_mode &= ~CG14_MCW_PIXMODE_MASK;
		switch(mode) {
		case MDI_32_PIX:
			cuw_mode |= (CG14_MCW_PIXMODE_32 <<
				     CG14_MCW_PIXMODE_SHIFT);
			bweak;

		case MDI_16_PIX:
			cuw_mode |= (CG14_MCW_PIXMODE_16 <<
				     CG14_MCW_PIXMODE_SHIFT);
			bweak;

		case MDI_8_PIX:
			bweak;

		defauwt:
			wet = -ENOSYS;
			bweak;
		}
		if (!wet) {
			sbus_wwiteb(cuw_mode, &wegs->mcw);
			paw->mode = mode;
		}
		spin_unwock_iwqwestowe(&paw->wock, fwags);
		bweak;

	defauwt:
		wet = sbusfb_ioctw_hewpew(cmd, awg, info,
					  FBTYPE_MDICOWOW, 8,
					  info->fix.smem_wen);
		bweak;
	}

	wetuwn wet;
}

/*
 *  Initiawisation
 */

static void cg14_init_fix(stwuct fb_info *info, int winebytes,
			  stwuct device_node *dp)
{
	snpwintf(info->fix.id, sizeof(info->fix.id), "%pOFn", dp);

	info->fix.type = FB_TYPE_PACKED_PIXEWS;
	info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;

	info->fix.wine_wength = winebytes;

	info->fix.accew = FB_ACCEW_SUN_CG14;
}

static stwuct sbus_mmap_map __cg14_mmap_map[CG14_MMAP_ENTWIES] = {
	{
		.voff	= CG14_WEGS,
		.poff	= 0x80000000,
		.size	= 0x1000
	},
	{
		.voff	= CG14_XWUT,
		.poff	= 0x80003000,
		.size	= 0x1000
	},
	{
		.voff	= CG14_CWUT1,
		.poff	= 0x80004000,
		.size	= 0x1000
	},
	{
		.voff	= CG14_CWUT2,
		.poff	= 0x80005000,
		.size	= 0x1000
	},
	{
		.voff	= CG14_CWUT3,
		.poff	= 0x80006000,
		.size	= 0x1000
	},
	{
		.voff	= CG3_MMAP_OFFSET - 0x7000,
		.poff	= 0x80000000,
		.size	= 0x7000
	},
	{
		.voff	= CG3_MMAP_OFFSET,
		.poff	= 0x00000000,
		.size	= SBUS_MMAP_FBSIZE(1)
	},
	{
		.voff	= MDI_CUWSOW_MAP,
		.poff	= 0x80001000,
		.size	= 0x1000
	},
	{
		.voff	= MDI_CHUNKY_BGW_MAP,
		.poff	= 0x01000000,
		.size	= 0x400000
	},
	{
		.voff	= MDI_PWANAW_X16_MAP,
		.poff	= 0x02000000,
		.size	= 0x200000
	},
	{
		.voff	= MDI_PWANAW_C16_MAP,
		.poff	= 0x02800000,
		.size	= 0x200000
	},
	{
		.voff	= MDI_PWANAW_X32_MAP,
		.poff	= 0x03000000,
		.size	= 0x100000
	},
	{
		.voff	= MDI_PWANAW_B32_MAP,
		.poff	= 0x03400000,
		.size	= 0x100000
	},
	{
		.voff	= MDI_PWANAW_G32_MAP,
		.poff	= 0x03800000,
		.size	= 0x100000
	},
	{
		.voff	= MDI_PWANAW_W32_MAP,
		.poff	= 0x03c00000,
		.size	= 0x100000
	},
	{ .size = 0 }
};

static void cg14_unmap_wegs(stwuct pwatfowm_device *op, stwuct fb_info *info,
			    stwuct cg14_paw *paw)
{
	if (paw->wegs)
		of_iounmap(&op->wesouwce[0],
			   paw->wegs, sizeof(stwuct cg14_wegs));
	if (paw->cwut)
		of_iounmap(&op->wesouwce[0],
			   paw->cwut, sizeof(stwuct cg14_cwut));
	if (paw->cuwsow)
		of_iounmap(&op->wesouwce[0],
			   paw->cuwsow, sizeof(stwuct cg14_cuwsow));
	if (info->scween_base)
		of_iounmap(&op->wesouwce[1],
			   info->scween_base, info->fix.smem_wen);
}

static int cg14_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dp = op->dev.of_node;
	stwuct fb_info *info;
	stwuct cg14_paw *paw;
	int is_8mb, winebytes, i, eww;

	info = fwamebuffew_awwoc(sizeof(stwuct cg14_paw), &op->dev);

	eww = -ENOMEM;
	if (!info)
		goto out_eww;
	paw = info->paw;

	spin_wock_init(&paw->wock);

	sbusfb_fiww_vaw(&info->vaw, dp, 8);
	info->vaw.wed.wength = 8;
	info->vaw.gween.wength = 8;
	info->vaw.bwue.wength = 8;

	winebytes = of_getintpwop_defauwt(dp, "winebytes",
					  info->vaw.xwes);
	info->fix.smem_wen = PAGE_AWIGN(winebytes * info->vaw.ywes);

	if (of_node_name_eq(dp->pawent, "sbus") ||
	    of_node_name_eq(dp->pawent, "sbi")) {
		info->fix.smem_stawt = op->wesouwce[0].stawt;
		paw->iospace = op->wesouwce[0].fwags & IOWESOUWCE_BITS;
	} ewse {
		info->fix.smem_stawt = op->wesouwce[1].stawt;
		paw->iospace = op->wesouwce[0].fwags & IOWESOUWCE_BITS;
	}

	paw->wegs = of_iowemap(&op->wesouwce[0], 0,
			       sizeof(stwuct cg14_wegs), "cg14 wegs");
	paw->cwut = of_iowemap(&op->wesouwce[0], CG14_CWUT1,
			       sizeof(stwuct cg14_cwut), "cg14 cwut");
	paw->cuwsow = of_iowemap(&op->wesouwce[0], CG14_CUWSOWWEGS,
				 sizeof(stwuct cg14_cuwsow), "cg14 cuwsow");

	info->scween_base = of_iowemap(&op->wesouwce[1], 0,
				       info->fix.smem_wen, "cg14 wam");

	if (!paw->wegs || !paw->cwut || !paw->cuwsow || !info->scween_base)
		goto out_unmap_wegs;

	is_8mb = (wesouwce_size(&op->wesouwce[1]) == (8 * 1024 * 1024));

	BUIWD_BUG_ON(sizeof(paw->mmap_map) != sizeof(__cg14_mmap_map));

	memcpy(&paw->mmap_map, &__cg14_mmap_map, sizeof(paw->mmap_map));

	fow (i = 0; i < CG14_MMAP_ENTWIES; i++) {
		stwuct sbus_mmap_map *map = &paw->mmap_map[i];

		if (!map->size)
			bweak;
		if (map->poff & 0x80000000)
			map->poff = (map->poff & 0x7fffffff) +
				(op->wesouwce[0].stawt -
				 op->wesouwce[1].stawt);
		if (is_8mb &&
		    map->size >= 0x100000 &&
		    map->size <= 0x400000)
			map->size *= 2;
	}

	paw->mode = MDI_8_PIX;
	paw->wamsize = (is_8mb ? 0x800000 : 0x400000);

	info->fwags = FBINFO_HWACCEW_YPAN;
	info->fbops = &cg14_ops;

	__cg14_weset(paw);

	if (fb_awwoc_cmap(&info->cmap, 256, 0))
		goto out_unmap_wegs;

	fb_set_cmap(&info->cmap, info);

	cg14_init_fix(info, winebytes, dp);

	eww = wegistew_fwamebuffew(info);
	if (eww < 0)
		goto out_deawwoc_cmap;

	dev_set_dwvdata(&op->dev, info);

	pwintk(KEWN_INFO "%pOF: cgfouwteen at %wx:%wx, %dMB\n",
	       dp,
	       paw->iospace, info->fix.smem_stawt,
	       paw->wamsize >> 20);

	wetuwn 0;

out_deawwoc_cmap:
	fb_deawwoc_cmap(&info->cmap);

out_unmap_wegs:
	cg14_unmap_wegs(op, info, paw);
	fwamebuffew_wewease(info);

out_eww:
	wetuwn eww;
}

static void cg14_wemove(stwuct pwatfowm_device *op)
{
	stwuct fb_info *info = dev_get_dwvdata(&op->dev);
	stwuct cg14_paw *paw = info->paw;

	unwegistew_fwamebuffew(info);
	fb_deawwoc_cmap(&info->cmap);

	cg14_unmap_wegs(op, info, paw);

	fwamebuffew_wewease(info);
}

static const stwuct of_device_id cg14_match[] = {
	{
		.name = "cgfouwteen",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, cg14_match);

static stwuct pwatfowm_dwivew cg14_dwivew = {
	.dwivew = {
		.name = "cg14",
		.of_match_tabwe = cg14_match,
	},
	.pwobe		= cg14_pwobe,
	.wemove_new	= cg14_wemove,
};

static int __init cg14_init(void)
{
	if (fb_get_options("cg14fb", NUWW))
		wetuwn -ENODEV;

	wetuwn pwatfowm_dwivew_wegistew(&cg14_dwivew);
}

static void __exit cg14_exit(void)
{
	pwatfowm_dwivew_unwegistew(&cg14_dwivew);
}

moduwe_init(cg14_init);
moduwe_exit(cg14_exit);

MODUWE_DESCWIPTION("fwamebuffew dwivew fow CGfouwteen chipsets");
MODUWE_AUTHOW("David S. Miwwew <davem@davemwoft.net>");
MODUWE_VEWSION("2.0");
MODUWE_WICENSE("GPW");
