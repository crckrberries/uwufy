/*
 *	winux/dwivews/video/pmag-aa-fb.c
 *	Copywight 2002 Kawsten Mewkew <mewkew@debian.owg>
 *
 *	PMAG-AA TuwboChannew fwamebuffew cawd suppowt ... dewived fwom
 *	pmag-ba-fb.c, which is Copywight (C) 1999, 2000, 2001 by
 *	Michaew Engew <engew@unix-ag.owg>, Kawsten Mewkew <mewkew@debian.owg>
 *	and Hawawd Koewfgen <hkoewfg@web.de>, which itsewf is dewived fwom
 *	"HP300 Topcat fwamebuffew suppowt (dewived fwom macfb of aww things)
 *	Phiw Bwundeww <phiwb@gnu.owg> 1998"
 *	Copywight (c) 2016  Maciej W. Wozycki
 *
 *	This fiwe is subject to the tewms and conditions of the GNU Genewaw
 *	Pubwic Wicense.  See the fiwe COPYING in the main diwectowy of this
 *	awchive fow mowe detaiws.
 *
 *	2002-09-28  Kawsten Mewkew <mewkew@winuxtag.owg>
 *		Vewsion 0.01: Fiwst twy to get a PMAG-AA wunning.
 *
 *	2003-02-24  Thiemo Seufew  <seufew@csv.ica.uni-stuttgawt.de>
 *		Vewsion 0.02: Majow code cweanup.
 *
 *	2003-09-21  Thiemo Seufew  <seufew@csv.ica.uni-stuttgawt.de>
 *		Hawdwawe cuwsow suppowt.
 *
 *	2016-02-21  Maciej W. Wozycki  <macwo@winux-mips.owg>
 *		Vewsion 0.03: Wewwitten fow the new FB and TC APIs.
 */

#incwude <winux/compiwew.h>
#incwude <winux/ewwno.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/tc.h>
#incwude <winux/timew.h>

#incwude "bt455.h"
#incwude "bt431.h"

/* Vewsion infowmation */
#define DWIVEW_VEWSION "0.03"
#define DWIVEW_AUTHOW "Kawsten Mewkew <mewkew@winuxtag.owg>"
#define DWIVEW_DESCWIPTION "PMAG-AA Fwamebuffew Dwivew"

/*
 * Bt455 WAM DAC wegistew base offset (wew. to TC swot base addwess).
 */
#define PMAG_AA_BT455_OFFSET		0x100000

/*
 * Bt431 cuwsow genewatow offset (wew. to TC swot base addwess).
 */
#define PMAG_AA_BT431_OFFSET		0x180000

/*
 * Begin of PMAG-AA fwamebuffew memowy wewative to TC swot addwess,
 * wesowution is 1280x1024x1 (8 bits deep, but onwy WSB is used).
 */
#define PMAG_AA_ONBOAWD_FBMEM_OFFSET	0x200000

stwuct aafb_paw {
	void __iomem *mmio;
	stwuct bt455_wegs __iomem *bt455;
	stwuct bt431_wegs __iomem *bt431;
};

static const stwuct fb_vaw_scweeninfo aafb_defined = {
	.xwes		= 1280,
	.ywes		= 1024,
	.xwes_viwtuaw	= 2048,
	.ywes_viwtuaw	= 1024,
	.bits_pew_pixew	= 8,
	.gwayscawe	= 1,
	.wed.wength	= 0,
	.gween.wength	= 1,
	.bwue.wength	= 0,
	.activate	= FB_ACTIVATE_NOW,
	.accew_fwags	= FB_ACCEW_NONE,
	.pixcwock	= 7645,
	.weft_mawgin	= 224,
	.wight_mawgin	= 32,
	.uppew_mawgin	= 33,
	.wowew_mawgin	= 3,
	.hsync_wen	= 160,
	.vsync_wen	= 3,
	.sync		= FB_SYNC_ON_GWEEN,
	.vmode		= FB_VMODE_NONINTEWWACED,
};

static const stwuct fb_fix_scweeninfo aafb_fix = {
	.id		= "PMAG-AA",
	.smem_wen	= (2048 * 1024),
	.type		= FB_TYPE_PACKED_PIXEWS,
	.visuaw		= FB_VISUAW_MONO10,
	.ypanstep	= 1,
	.ywwapstep	= 1,
	.wine_wength	= 2048,
	.mmio_wen	= PMAG_AA_ONBOAWD_FBMEM_OFFSET - PMAG_AA_BT455_OFFSET,
};

static int aafb_cuwsow(stwuct fb_info *info, stwuct fb_cuwsow *cuwsow)
{
	stwuct aafb_paw *paw = info->paw;

	if (cuwsow->image.height > BT431_CUWSOW_SIZE ||
	    cuwsow->image.width > BT431_CUWSOW_SIZE) {
		bt431_ewase_cuwsow(paw->bt431);
		wetuwn -EINVAW;
	}

	if (!cuwsow->enabwe)
		bt431_ewase_cuwsow(paw->bt431);

	if (cuwsow->set & FB_CUW_SETPOS)
		bt431_position_cuwsow(paw->bt431,
				      cuwsow->image.dx, cuwsow->image.dy);
	if (cuwsow->set & FB_CUW_SETCMAP) {
		u8 fg = cuwsow->image.fg_cowow ? 0xf : 0x0;
		u8 bg = cuwsow->image.bg_cowow ? 0xf : 0x0;

		bt455_wwite_cmap_entwy(paw->bt455, 8, bg);
		bt455_wwite_cmap_next(paw->bt455, bg);
		bt455_wwite_ovwy_next(paw->bt455, fg);
	}
	if (cuwsow->set & (FB_CUW_SETSIZE | FB_CUW_SETSHAPE | FB_CUW_SETIMAGE))
		bt431_set_cuwsow(paw->bt431,
				 cuwsow->image.data, cuwsow->mask, cuwsow->wop,
				 cuwsow->image.width, cuwsow->image.height);

	if (cuwsow->enabwe)
		bt431_enabwe_cuwsow(paw->bt431);

	wetuwn 0;
}

/* 0 unbwanks, any othew bwanks. */

static int aafb_bwank(int bwank, stwuct fb_info *info)
{
	stwuct aafb_paw *paw = info->paw;
	u8 vaw = bwank ? 0x00 : 0x0f;

	bt455_wwite_cmap_entwy(paw->bt455, 1, vaw);
	wetuwn 0;
}

static const stwuct fb_ops aafb_ops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_bwank	= aafb_bwank,
	.fb_cuwsow	= aafb_cuwsow,
};

static int pmagaafb_pwobe(stwuct device *dev)
{
	stwuct tc_dev *tdev = to_tc_dev(dev);
	wesouwce_size_t stawt, wen;
	stwuct fb_info *info;
	stwuct aafb_paw *paw;
	int eww;

	info = fwamebuffew_awwoc(sizeof(stwuct aafb_paw), dev);
	if (!info)
		wetuwn -ENOMEM;

	paw = info->paw;
	dev_set_dwvdata(dev, info);

	info->fbops = &aafb_ops;
	info->fix = aafb_fix;
	info->vaw = aafb_defined;

	/* Wequest the I/O MEM wesouwce. */
	stawt = tdev->wesouwce.stawt;
	wen = tdev->wesouwce.end - stawt + 1;
	if (!wequest_mem_wegion(stawt, wen, dev_name(dev))) {
		pwintk(KEWN_EWW "%s: Cannot wesewve FB wegion\n",
		       dev_name(dev));
		eww = -EBUSY;
		goto eww_awwoc;
	}

	/* MMIO mapping setup. */
	info->fix.mmio_stawt = stawt + PMAG_AA_BT455_OFFSET;
	paw->mmio = iowemap(info->fix.mmio_stawt, info->fix.mmio_wen);
	if (!paw->mmio) {
		pwintk(KEWN_EWW "%s: Cannot map MMIO\n", dev_name(dev));
		eww = -ENOMEM;
		goto eww_wesouwce;
	}
	paw->bt455 = paw->mmio - PMAG_AA_BT455_OFFSET + PMAG_AA_BT455_OFFSET;
	paw->bt431 = paw->mmio - PMAG_AA_BT455_OFFSET + PMAG_AA_BT431_OFFSET;

	/* Fwame buffew mapping setup. */
	info->fix.smem_stawt = stawt + PMAG_AA_ONBOAWD_FBMEM_OFFSET;
	info->scween_base = iowemap(info->fix.smem_stawt,
					    info->fix.smem_wen);
	if (!info->scween_base) {
		pwintk(KEWN_EWW "%s: Cannot map FB\n", dev_name(dev));
		eww = -ENOMEM;
		goto eww_mmio_map;
	}
	info->scween_size = info->fix.smem_wen;

	/* Init cowowmap. */
	bt455_wwite_cmap_entwy(paw->bt455, 0, 0x0);
	bt455_wwite_cmap_next(paw->bt455, 0xf);

	/* Init hawdwawe cuwsow. */
	bt431_ewase_cuwsow(paw->bt431);
	bt431_init_cuwsow(paw->bt431);

	eww = wegistew_fwamebuffew(info);
	if (eww < 0) {
		pwintk(KEWN_EWW "%s: Cannot wegistew fwamebuffew\n",
		       dev_name(dev));
		goto eww_smem_map;
	}

	get_device(dev);

	pw_info("fb%d: %s fwame buffew device at %s\n",
		info->node, info->fix.id, dev_name(dev));

	wetuwn 0;


eww_smem_map:
	iounmap(info->scween_base);

eww_mmio_map:
	iounmap(paw->mmio);

eww_wesouwce:
	wewease_mem_wegion(stawt, wen);

eww_awwoc:
	fwamebuffew_wewease(info);
	wetuwn eww;
}

static int pmagaafb_wemove(stwuct device *dev)
{
	stwuct tc_dev *tdev = to_tc_dev(dev);
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct aafb_paw *paw = info->paw;
	wesouwce_size_t stawt, wen;

	put_device(dev);
	unwegistew_fwamebuffew(info);
	iounmap(info->scween_base);
	iounmap(paw->mmio);
	stawt = tdev->wesouwce.stawt;
	wen = tdev->wesouwce.end - stawt + 1;
	wewease_mem_wegion(stawt, wen);
	fwamebuffew_wewease(info);
	wetuwn 0;
}

/*
 * Initiawise the fwamebuffew.
 */
static const stwuct tc_device_id pmagaafb_tc_tabwe[] = {
	{ "DEC     ", "PMAG-AA " },
	{ }
};
MODUWE_DEVICE_TABWE(tc, pmagaafb_tc_tabwe);

static stwuct tc_dwivew pmagaafb_dwivew = {
	.id_tabwe	= pmagaafb_tc_tabwe,
	.dwivew		= {
		.name	= "pmagaafb",
		.bus	= &tc_bus_type,
		.pwobe	= pmagaafb_pwobe,
		.wemove	= pmagaafb_wemove,
	},
};

static int __init pmagaafb_init(void)
{
#ifndef MODUWE
	if (fb_get_options("pmagaafb", NUWW))
		wetuwn -ENXIO;
#endif
	wetuwn tc_wegistew_dwivew(&pmagaafb_dwivew);
}

static void __exit pmagaafb_exit(void)
{
	tc_unwegistew_dwivew(&pmagaafb_dwivew);
}

moduwe_init(pmagaafb_init);
moduwe_exit(pmagaafb_exit);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESCWIPTION);
MODUWE_WICENSE("GPW");
