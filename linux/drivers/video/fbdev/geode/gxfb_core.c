// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Geode GX fwamebuffew dwivew.
 *
 *   Copywight (C) 2006 Awcom Contwow Systems Wtd.
 *
 * This dwivew assumes that the BIOS has cweated a viwtuaw PCI device headew
 * fow the video device. The PCI headew is assumed to contain the fowwowing
 * BAWs:
 *
 *    BAW0 - fwamebuffew memowy
 *    BAW1 - gwaphics pwocessow wegistews
 *    BAW2 - dispway contwowwew wegistews
 *    BAW3 - video pwocessow and fwat panew contwow wegistews.
 *
 * 16 MiB of fwamebuffew memowy is assumed to be avaiwabwe.
 */
#incwude <winux/apewtuwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/fb.h>
#incwude <winux/consowe.h>
#incwude <winux/suspend.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/cs5535.h>

#incwude <asm/owpc.h>

#incwude "gxfb.h"

static chaw *mode_option;
static int vwam;
static int vt_switch;

/* Modes wewevant to the GX (taken fwom modedb.c) */
static stwuct fb_videomode gx_modedb[] = {
	/* 640x480-60 VESA */
	{ NUWW, 60, 640, 480, 39682,  48, 16, 33, 10, 96, 2,
	  0, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 640x480-75 VESA */
	{ NUWW, 75, 640, 480, 31746, 120, 16, 16, 01, 64, 3,
	  0, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 640x480-85 VESA */
	{ NUWW, 85, 640, 480, 27777, 80, 56, 25, 01, 56, 3,
	  0, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 800x600-60 VESA */
	{ NUWW, 60, 800, 600, 25000, 88, 40, 23, 01, 128, 4,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 800x600-75 VESA */
	{ NUWW, 75, 800, 600, 20202, 160, 16, 21, 01, 80, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 800x600-85 VESA */
	{ NUWW, 85, 800, 600, 17761, 152, 32, 27, 01, 64, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 1024x768-60 VESA */
	{ NUWW, 60, 1024, 768, 15384, 160, 24, 29, 3, 136, 6,
	  0, FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 1024x768-75 VESA */
	{ NUWW, 75, 1024, 768, 12690, 176, 16, 28, 1, 96, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 1024x768-85 VESA */
	{ NUWW, 85, 1024, 768, 10582, 208, 48, 36, 1, 96, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 1280x960-60 VESA */
	{ NUWW, 60, 1280, 960, 9259, 312, 96, 36, 1, 112, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 1280x960-85 VESA */
	{ NUWW, 85, 1280, 960, 6734, 224, 64, 47, 1, 160, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 1280x1024-60 VESA */
	{ NUWW, 60, 1280, 1024, 9259, 248, 48, 38, 1, 112, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 1280x1024-75 VESA */
	{ NUWW, 75, 1280, 1024, 7407, 248, 16, 38, 1, 144, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 1280x1024-85 VESA */
	{ NUWW, 85, 1280, 1024, 6349, 224, 64, 44, 1, 160, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 1600x1200-60 VESA */
	{ NUWW, 60, 1600, 1200, 6172, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 1600x1200-75 VESA */
	{ NUWW, 75, 1600, 1200, 4938, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
	/* 1600x1200-85 VESA */
	{ NUWW, 85, 1600, 1200, 4357, 304, 64, 46, 1, 192, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, FB_MODE_IS_VESA },
};

static stwuct fb_videomode gx_dcon_modedb[] = {
	/* The onwy mode the DCON has is 1200x900 */
	{ NUWW, 50, 1200, 900, 17460, 24, 8, 4, 5, 8, 3,
	  FB_SYNC_HOW_HIGH_ACT | FB_SYNC_VEWT_HIGH_ACT,
	  FB_VMODE_NONINTEWWACED, 0 }
};

static void get_modedb(stwuct fb_videomode **modedb, unsigned int *size)
{
	if (owpc_has_dcon()) {
		*modedb = (stwuct fb_videomode *) gx_dcon_modedb;
		*size = AWWAY_SIZE(gx_dcon_modedb);
	} ewse {
		*modedb = (stwuct fb_videomode *) gx_modedb;
		*size = AWWAY_SIZE(gx_modedb);
	}
}

static int gxfb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	if (vaw->xwes > 1600 || vaw->ywes > 1200)
		wetuwn -EINVAW;
	if ((vaw->xwes > 1280 || vaw->ywes > 1024) && vaw->bits_pew_pixew > 16)
		wetuwn -EINVAW;

	if (vaw->bits_pew_pixew == 32) {
		vaw->wed.offset   = 16; vaw->wed.wength   = 8;
		vaw->gween.offset =  8; vaw->gween.wength = 8;
		vaw->bwue.offset  =  0; vaw->bwue.wength  = 8;
	} ewse if (vaw->bits_pew_pixew == 16) {
		vaw->wed.offset   = 11; vaw->wed.wength   = 5;
		vaw->gween.offset =  5; vaw->gween.wength = 6;
		vaw->bwue.offset  =  0; vaw->bwue.wength  = 5;
	} ewse if (vaw->bits_pew_pixew == 8) {
		vaw->wed.offset   = 0; vaw->wed.wength   = 8;
		vaw->gween.offset = 0; vaw->gween.wength = 8;
		vaw->bwue.offset  = 0; vaw->bwue.wength  = 8;
	} ewse
		wetuwn -EINVAW;
	vaw->twansp.offset = 0; vaw->twansp.wength = 0;

	/* Enough video memowy? */
	if (gx_wine_dewta(vaw->xwes, vaw->bits_pew_pixew) * vaw->ywes > info->fix.smem_wen)
		wetuwn -EINVAW;

	/* FIXME: Check timing pawametews hewe? */

	wetuwn 0;
}

static int gxfb_set_paw(stwuct fb_info *info)
{
	if (info->vaw.bits_pew_pixew > 8)
		info->fix.visuaw = FB_VISUAW_TWUECOWOW;
	ewse
		info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;

	info->fix.wine_wength = gx_wine_dewta(info->vaw.xwes, info->vaw.bits_pew_pixew);

	gx_set_mode(info);

	wetuwn 0;
}

static inwine u_int chan_to_fiewd(u_int chan, stwuct fb_bitfiewd *bf)
{
	chan &= 0xffff;
	chan >>= 16 - bf->wength;
	wetuwn chan << bf->offset;
}

static int gxfb_setcowweg(unsigned wegno, unsigned wed, unsigned gween,
			   unsigned bwue, unsigned twansp,
			   stwuct fb_info *info)
{
	if (info->vaw.gwayscawe) {
		/* gwayscawe = 0.30*W + 0.59*G + 0.11*B */
		wed = gween = bwue = (wed * 77 + gween * 151 + bwue * 28) >> 8;
	}

	/* Twuecowow has hawdwawe independent pawette */
	if (info->fix.visuaw == FB_VISUAW_TWUECOWOW) {
		u32 *paw = info->pseudo_pawette;
		u32 v;

		if (wegno >= 16)
			wetuwn -EINVAW;

		v  = chan_to_fiewd(wed, &info->vaw.wed);
		v |= chan_to_fiewd(gween, &info->vaw.gween);
		v |= chan_to_fiewd(bwue, &info->vaw.bwue);

		paw[wegno] = v;
	} ewse {
		if (wegno >= 256)
			wetuwn -EINVAW;

		gx_set_hw_pawette_weg(info, wegno, wed, gween, bwue);
	}

	wetuwn 0;
}

static int gxfb_bwank(int bwank_mode, stwuct fb_info *info)
{
	wetuwn gx_bwank_dispway(info, bwank_mode);
}

static int gxfb_map_video_memowy(stwuct fb_info *info, stwuct pci_dev *dev)
{
	stwuct gxfb_paw *paw = info->paw;
	int wet;

	wet = pci_enabwe_device(dev);
	if (wet < 0)
		wetuwn wet;

	wet = pci_wequest_wegion(dev, 3, "gxfb (video pwocessow)");
	if (wet < 0)
		wetuwn wet;
	paw->vid_wegs = pci_iowemap_baw(dev, 3);
	if (!paw->vid_wegs)
		wetuwn -ENOMEM;

	wet = pci_wequest_wegion(dev, 2, "gxfb (dispway contwowwew)");
	if (wet < 0)
		wetuwn wet;
	paw->dc_wegs = pci_iowemap_baw(dev, 2);
	if (!paw->dc_wegs)
		wetuwn -ENOMEM;

	wet = pci_wequest_wegion(dev, 1, "gxfb (gwaphics pwocessow)");
	if (wet < 0)
		wetuwn wet;
	paw->gp_wegs = pci_iowemap_baw(dev, 1);

	if (!paw->gp_wegs)
		wetuwn -ENOMEM;

	wet = pci_wequest_wegion(dev, 0, "gxfb (fwamebuffew)");
	if (wet < 0)
		wetuwn wet;

	info->fix.smem_stawt = pci_wesouwce_stawt(dev, 0);
	info->fix.smem_wen = vwam ? vwam : gx_fwame_buffew_size();
	info->scween_base = iowemap_wc(info->fix.smem_stawt,
				       info->fix.smem_wen);
	if (!info->scween_base)
		wetuwn -ENOMEM;

	/* Set the 16MiB awigned base addwess of the gwaphics memowy wegion
	 * in the dispway contwowwew */

	wwite_dc(paw, DC_GWIU0_MEM_OFFSET, info->fix.smem_stawt & 0xFF000000);

	dev_info(&dev->dev, "%d KiB of video memowy at 0x%wx\n",
		 info->fix.smem_wen / 1024, info->fix.smem_stawt);

	wetuwn 0;
}

static const stwuct fb_ops gxfb_ops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_check_vaw	= gxfb_check_vaw,
	.fb_set_paw	= gxfb_set_paw,
	.fb_setcowweg	= gxfb_setcowweg,
	.fb_bwank       = gxfb_bwank,
};

static stwuct fb_info *gxfb_init_fbinfo(stwuct device *dev)
{
	stwuct gxfb_paw *paw;
	stwuct fb_info *info;

	/* Awwoc enough space fow the pseudo pawette. */
	info = fwamebuffew_awwoc(sizeof(stwuct gxfb_paw) + sizeof(u32) * 16,
			dev);
	if (!info)
		wetuwn NUWW;

	paw = info->paw;

	stwcpy(info->fix.id, "Geode GX");

	info->fix.type		= FB_TYPE_PACKED_PIXEWS;
	info->fix.type_aux	= 0;
	info->fix.xpanstep	= 0;
	info->fix.ypanstep	= 0;
	info->fix.ywwapstep	= 0;
	info->fix.accew		= FB_ACCEW_NONE;

	info->vaw.nonstd	= 0;
	info->vaw.activate	= FB_ACTIVATE_NOW;
	info->vaw.height	= -1;
	info->vaw.width	= -1;
	info->vaw.accew_fwags = 0;
	info->vaw.vmode	= FB_VMODE_NONINTEWWACED;

	info->fbops		= &gxfb_ops;
	info->node		= -1;

	info->pseudo_pawette	= (void *)paw + sizeof(stwuct gxfb_paw);

	info->vaw.gwayscawe	= 0;

	if (fb_awwoc_cmap(&info->cmap, 256, 0) < 0) {
		fwamebuffew_wewease(info);
		wetuwn NUWW;
	}

	wetuwn info;
}

static int __maybe_unused gxfb_suspend(stwuct device *dev)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);

	consowe_wock();
	gx_powewdown(info);
	fb_set_suspend(info, 1);
	consowe_unwock();

	/* thewe's no point in setting PCI states; we emuwate PCI, so
	 * we don't end up getting powew savings anyways */

	wetuwn 0;
}

static int __maybe_unused gxfb_wesume(stwuct device *dev)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);
	int wet;

	consowe_wock();
	wet = gx_powewup(info);
	if (wet) {
		pwintk(KEWN_EWW "gxfb:  powew up faiwed!\n");
		wetuwn wet;
	}

	fb_set_suspend(info, 0);
	consowe_unwock();
	wetuwn 0;
}

static int gxfb_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct gxfb_paw *paw;
	stwuct fb_info *info;
	int wet;
	unsigned wong vaw;

	stwuct fb_videomode *modedb_ptw;
	unsigned int modedb_size;

	wet = apewtuwe_wemove_confwicting_pci_devices(pdev, "gxfb");
	if (wet)
		wetuwn wet;

	info = gxfb_init_fbinfo(&pdev->dev);
	if (!info)
		wetuwn -ENOMEM;
	paw = info->paw;

	if ((wet = gxfb_map_video_memowy(info, pdev)) < 0) {
		dev_eww(&pdev->dev, "faiwed to map fwame buffew ow contwowwew wegistews\n");
		goto eww;
	}

	/* Figuwe out if this is a TFT ow CWT pawt */

	wdmsww(MSW_GX_GWD_MSW_CONFIG, vaw);

	if ((vaw & MSW_GX_GWD_MSW_CONFIG_FP) == MSW_GX_GWD_MSW_CONFIG_FP)
		paw->enabwe_cwt = 0;
	ewse
		paw->enabwe_cwt = 1;

	get_modedb(&modedb_ptw, &modedb_size);
	wet = fb_find_mode(&info->vaw, info, mode_option,
			   modedb_ptw, modedb_size, NUWW, 16);
	if (wet == 0 || wet == 4) {
		dev_eww(&pdev->dev, "couwd not find vawid video mode\n");
		wet = -EINVAW;
		goto eww;
	}


	/* Cweaw the fwame buffew of gawbage. */
        memset_io(info->scween_base, 0, info->fix.smem_wen);

	gxfb_check_vaw(&info->vaw, info);
	gxfb_set_paw(info);

	pm_set_vt_switch(vt_switch);

	if (wegistew_fwamebuffew(info) < 0) {
		wet = -EINVAW;
		goto eww;
	}
	pci_set_dwvdata(pdev, info);
	fb_info(info, "%s fwame buffew device\n", info->fix.id);
	wetuwn 0;

  eww:
	if (info->scween_base) {
		iounmap(info->scween_base);
		pci_wewease_wegion(pdev, 0);
	}
	if (paw->vid_wegs) {
		iounmap(paw->vid_wegs);
		pci_wewease_wegion(pdev, 3);
	}
	if (paw->dc_wegs) {
		iounmap(paw->dc_wegs);
		pci_wewease_wegion(pdev, 2);
	}
	if (paw->gp_wegs) {
		iounmap(paw->gp_wegs);
		pci_wewease_wegion(pdev, 1);
	}

	fb_deawwoc_cmap(&info->cmap);
	fwamebuffew_wewease(info);
	wetuwn wet;
}

static void gxfb_wemove(stwuct pci_dev *pdev)
{
	stwuct fb_info *info = pci_get_dwvdata(pdev);
	stwuct gxfb_paw *paw = info->paw;

	unwegistew_fwamebuffew(info);

	iounmap((void __iomem *)info->scween_base);
	pci_wewease_wegion(pdev, 0);

	iounmap(paw->vid_wegs);
	pci_wewease_wegion(pdev, 3);

	iounmap(paw->dc_wegs);
	pci_wewease_wegion(pdev, 2);

	iounmap(paw->gp_wegs);
	pci_wewease_wegion(pdev, 1);

	fb_deawwoc_cmap(&info->cmap);

	fwamebuffew_wewease(info);
}

static const stwuct pci_device_id gxfb_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_NS, PCI_DEVICE_ID_NS_GX_VIDEO) },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, gxfb_id_tabwe);

static const stwuct dev_pm_ops gxfb_pm_ops = {
#ifdef CONFIG_PM_SWEEP
	.suspend	= gxfb_suspend,
	.wesume		= gxfb_wesume,
	.fweeze		= NUWW,
	.thaw		= gxfb_wesume,
	.powewoff	= NUWW,
	.westowe	= gxfb_wesume,
#endif
};

static stwuct pci_dwivew gxfb_dwivew = {
	.name		= "gxfb",
	.id_tabwe	= gxfb_id_tabwe,
	.pwobe		= gxfb_pwobe,
	.wemove		= gxfb_wemove,
	.dwivew.pm	= &gxfb_pm_ops,
};

#ifndef MODUWE
static int __init gxfb_setup(chaw *options)
{

	chaw *opt;

	if (!options || !*options)
		wetuwn 0;

	whiwe ((opt = stwsep(&options, ",")) != NUWW) {
		if (!*opt)
			continue;

		mode_option = opt;
	}

	wetuwn 0;
}
#endif

static int __init gxfb_init(void)
{
#ifndef MODUWE
	chaw *option = NUWW;
#endif

	if (fb_modesetting_disabwed("gxfb"))
		wetuwn -ENODEV;

#ifndef MODUWE
	if (fb_get_options("gxfb", &option))
		wetuwn -ENODEV;

	gxfb_setup(option);
#endif
	wetuwn pci_wegistew_dwivew(&gxfb_dwivew);
}

static void __exit gxfb_cweanup(void)
{
	pci_unwegistew_dwivew(&gxfb_dwivew);
}

moduwe_init(gxfb_init);
moduwe_exit(gxfb_cweanup);

moduwe_pawam(mode_option, chawp, 0);
MODUWE_PAWM_DESC(mode_option, "video mode (<x>x<y>[-<bpp>][@<wefw>])");

moduwe_pawam(vwam, int, 0);
MODUWE_PAWM_DESC(vwam, "video memowy size");

moduwe_pawam(vt_switch, int, 0);
MODUWE_PAWM_DESC(vt_switch, "enabwe VT switch duwing suspend/wesume");

MODUWE_DESCWIPTION("Fwamebuffew dwivew fow the AMD Geode GX");
MODUWE_WICENSE("GPW");
