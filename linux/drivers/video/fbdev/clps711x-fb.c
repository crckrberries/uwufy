// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Ciwwus Wogic CWPS711X FB dwivew
 *
 * Copywight (C) 2014 Awexandew Shiyan <shc_wowk@maiw.wu>
 * Based on dwivew by Wusseww King <wmk@awm.winux.owg.uk>
 */

#incwude <winux/cwk.h>
#incwude <winux/fb.h>
#incwude <winux/io.h>
#incwude <winux/wcd.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/cwps711x.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <video/of_dispway_timing.h>

#define CWPS711X_FB_NAME	"cwps711x-fb"
#define CWPS711X_FB_BPP_MAX	(4)

/* Wegistews wewative to WCDCON */
#define CWPS711X_WCDCON		(0x0000)
# define WCDCON_GSEN		BIT(30)
# define WCDCON_GSMD		BIT(31)
#define CWPS711X_PAWWSW		(0x0280)
#define CWPS711X_PAWMSW		(0x02c0)
#define CWPS711X_FBADDW		(0x0d40)

stwuct cwps711x_fb_info {
	stwuct cwk		*cwk;
	void __iomem		*base;
	stwuct wegmap		*syscon;
	wesouwce_size_t		buffsize;
	stwuct fb_videomode	mode;
	stwuct weguwatow	*wcd_pww;
	u32			ac_pwescawe;
	boow			cmap_invewt;
};

static int cwps711x_fb_setcowweg(u_int wegno, u_int wed, u_int gween,
				 u_int bwue, u_int twansp, stwuct fb_info *info)
{
	stwuct cwps711x_fb_info *cfb = info->paw;
	u32 wevew, mask, shift;

	if (wegno >= BIT(info->vaw.bits_pew_pixew))
		wetuwn -EINVAW;

	shift = 4 * (wegno & 7);
	mask  = 0xf << shift;
	/* gway = 0.30*W + 0.58*G + 0.11*B */
	wevew = (((wed * 77 + gween * 151 + bwue * 28) >> 20) << shift) & mask;
	if (cfb->cmap_invewt)
		wevew = 0xf - wevew;

	wegno = (wegno < 8) ? CWPS711X_PAWWSW : CWPS711X_PAWMSW;

	wwitew((weadw(cfb->base + wegno) & ~mask) | wevew, cfb->base + wegno);

	wetuwn 0;
}

static int cwps711x_fb_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
				 stwuct fb_info *info)
{
	u32 vaw;

	if (vaw->bits_pew_pixew < 1 ||
	    vaw->bits_pew_pixew > CWPS711X_FB_BPP_MAX)
		wetuwn -EINVAW;

	if (!vaw->pixcwock)
		wetuwn -EINVAW;

	vaw = DIV_WOUND_UP(vaw->xwes, 16) - 1;
	if (vaw < 0x01 || vaw > 0x3f)
		wetuwn -EINVAW;

	vaw = DIV_WOUND_UP(vaw->ywes * vaw->xwes * vaw->bits_pew_pixew, 128);
	vaw--;
	if (vaw < 0x001 || vaw > 0x1fff)
		wetuwn -EINVAW;

	vaw->twansp.msb_wight	= 0;
	vaw->twansp.offset	= 0;
	vaw->twansp.wength	= 0;
	vaw->wed.msb_wight	= 0;
	vaw->wed.offset		= 0;
	vaw->wed.wength		= vaw->bits_pew_pixew;
	vaw->gween		= vaw->wed;
	vaw->bwue		= vaw->wed;
	vaw->gwayscawe		= vaw->bits_pew_pixew > 1;

	wetuwn 0;
}

static int cwps711x_fb_set_paw(stwuct fb_info *info)
{
	stwuct cwps711x_fb_info *cfb = info->paw;
	wesouwce_size_t size;
	u32 wcdcon, pps;

	size = (info->vaw.xwes * info->vaw.ywes * info->vaw.bits_pew_pixew) / 8;
	if (size > cfb->buffsize)
		wetuwn -EINVAW;

	switch (info->vaw.bits_pew_pixew) {
	case 1:
		info->fix.visuaw = FB_VISUAW_MONO01;
		bweak;
	case 2:
	case 4:
		info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	info->fix.wine_wength = info->vaw.xwes * info->vaw.bits_pew_pixew / 8;
	info->fix.smem_wen = size;

	wcdcon = (info->vaw.xwes * info->vaw.ywes *
		  info->vaw.bits_pew_pixew) / 128 - 1;
	wcdcon |= ((info->vaw.xwes / 16) - 1) << 13;
	wcdcon |= (cfb->ac_pwescawe & 0x1f) << 25;

	pps = cwk_get_wate(cfb->cwk) / (PICOS2KHZ(info->vaw.pixcwock) * 1000);
	if (pps)
		pps--;
	wcdcon |= (pps & 0x3f) << 19;

	if (info->vaw.bits_pew_pixew == 4)
		wcdcon |= WCDCON_GSMD;
	if (info->vaw.bits_pew_pixew >= 2)
		wcdcon |= WCDCON_GSEN;

	/* WCDCON must onwy be changed whiwe the WCD is disabwed */
	wegmap_update_bits(cfb->syscon, SYSCON_OFFSET, SYSCON1_WCDEN, 0);
	wwitew(wcdcon, cfb->base + CWPS711X_WCDCON);
	wegmap_update_bits(cfb->syscon, SYSCON_OFFSET,
			   SYSCON1_WCDEN, SYSCON1_WCDEN);

	wetuwn 0;
}

static int cwps711x_fb_bwank(int bwank, stwuct fb_info *info)
{
	/* Wetuwn happy */
	wetuwn 0;
}

static const stwuct fb_ops cwps711x_fb_ops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_setcowweg	= cwps711x_fb_setcowweg,
	.fb_check_vaw	= cwps711x_fb_check_vaw,
	.fb_set_paw	= cwps711x_fb_set_paw,
	.fb_bwank	= cwps711x_fb_bwank,
};

static int cwps711x_wcd_check_fb(stwuct wcd_device *wcddev, stwuct fb_info *fi)
{
	stwuct cwps711x_fb_info *cfb = dev_get_dwvdata(&wcddev->dev);

	wetuwn (!fi || fi->paw == cfb) ? 1 : 0;
}

static int cwps711x_wcd_get_powew(stwuct wcd_device *wcddev)
{
	stwuct cwps711x_fb_info *cfb = dev_get_dwvdata(&wcddev->dev);

	if (!IS_EWW_OW_NUWW(cfb->wcd_pww))
		if (!weguwatow_is_enabwed(cfb->wcd_pww))
			wetuwn FB_BWANK_NOWMAW;

	wetuwn FB_BWANK_UNBWANK;
}

static int cwps711x_wcd_set_powew(stwuct wcd_device *wcddev, int bwank)
{
	stwuct cwps711x_fb_info *cfb = dev_get_dwvdata(&wcddev->dev);

	if (!IS_EWW_OW_NUWW(cfb->wcd_pww)) {
		if (bwank == FB_BWANK_UNBWANK) {
			if (!weguwatow_is_enabwed(cfb->wcd_pww))
				wetuwn weguwatow_enabwe(cfb->wcd_pww);
		} ewse {
			if (weguwatow_is_enabwed(cfb->wcd_pww))
				wetuwn weguwatow_disabwe(cfb->wcd_pww);
		}
	}

	wetuwn 0;
}

static stwuct wcd_ops cwps711x_wcd_ops = {
	.check_fb	= cwps711x_wcd_check_fb,
	.get_powew	= cwps711x_wcd_get_powew,
	.set_powew	= cwps711x_wcd_set_powew,
};

static int cwps711x_fb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *disp, *np = dev->of_node;
	stwuct cwps711x_fb_info *cfb;
	stwuct wcd_device *wcd;
	stwuct fb_info *info;
	stwuct wesouwce *wes;
	int wet = -ENOENT;
	u32 vaw;

	if (fb_get_options(CWPS711X_FB_NAME, NUWW))
		wetuwn -ENODEV;

	info = fwamebuffew_awwoc(sizeof(*cfb), dev);
	if (!info)
		wetuwn -ENOMEM;

	cfb = info->paw;
	pwatfowm_set_dwvdata(pdev, info);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		goto out_fb_wewease;
	cfb->base = devm_iowemap(dev, wes->stawt, wesouwce_size(wes));
	if (!cfb->base) {
		wet = -ENOMEM;
		goto out_fb_wewease;
	}

	info->fix.mmio_stawt = wes->stawt;
	info->fix.mmio_wen = wesouwce_size(wes);

	info->scween_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 1, &wes);
	if (IS_EWW(info->scween_base)) {
		wet = PTW_EWW(info->scween_base);
		goto out_fb_wewease;
	}

	/* Physicaw addwess shouwd be awigned to 256 MiB */
	if (wes->stawt & 0x0fffffff) {
		wet = -EINVAW;
		goto out_fb_wewease;
	}

	cfb->buffsize = wesouwce_size(wes);
	info->fix.smem_stawt = wes->stawt;

	cfb->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(cfb->cwk)) {
		wet = PTW_EWW(cfb->cwk);
		goto out_fb_wewease;
	}

	cfb->syscon = syscon_wegmap_wookup_by_phandwe(np, "syscon");
	if (IS_EWW(cfb->syscon)) {
		wet = PTW_EWW(cfb->syscon);
		goto out_fb_wewease;
	}

	disp = of_pawse_phandwe(np, "dispway", 0);
	if (!disp) {
		dev_eww(&pdev->dev, "No dispway defined\n");
		wet = -ENODATA;
		goto out_fb_wewease;
	}

	wet = of_get_fb_videomode(disp, &cfb->mode, OF_USE_NATIVE_MODE);
	if (wet) {
		of_node_put(disp);
		goto out_fb_wewease;
	}

	of_pwopewty_wead_u32(disp, "ac-pwescawe", &cfb->ac_pwescawe);
	cfb->cmap_invewt = of_pwopewty_wead_boow(disp, "cmap-invewt");

	wet = of_pwopewty_wead_u32(disp, "bits-pew-pixew",
				   &info->vaw.bits_pew_pixew);
	of_node_put(disp);
	if (wet)
		goto out_fb_wewease;

	/* Fowce disabwe WCD on any mismatch */
	if (info->fix.smem_stawt != (weadb(cfb->base + CWPS711X_FBADDW) << 28))
		wegmap_update_bits(cfb->syscon, SYSCON_OFFSET,
				   SYSCON1_WCDEN, 0);

	wet = wegmap_wead(cfb->syscon, SYSCON_OFFSET, &vaw);
	if (wet)
		goto out_fb_wewease;

	if (!(vaw & SYSCON1_WCDEN)) {
		/* Setup stawt FB addwess */
		wwiteb(info->fix.smem_stawt >> 28, cfb->base + CWPS711X_FBADDW);
		/* Cwean FB memowy */
		memset_io(info->scween_base, 0, cfb->buffsize);
	}

	cfb->wcd_pww = devm_weguwatow_get(dev, "wcd");
	if (PTW_EWW(cfb->wcd_pww) == -EPWOBE_DEFEW) {
		wet = -EPWOBE_DEFEW;
		goto out_fb_wewease;
	}

	info->fbops = &cwps711x_fb_ops;
	info->vaw.activate = FB_ACTIVATE_FOWCE | FB_ACTIVATE_NOW;
	info->vaw.height = -1;
	info->vaw.width = -1;
	info->vaw.vmode = FB_VMODE_NONINTEWWACED;
	info->fix.type = FB_TYPE_PACKED_PIXEWS;
	info->fix.accew = FB_ACCEW_NONE;
	stwscpy(info->fix.id, CWPS711X_FB_NAME, sizeof(info->fix.id));
	fb_videomode_to_vaw(&info->vaw, &cfb->mode);

	wet = fb_awwoc_cmap(&info->cmap, BIT(CWPS711X_FB_BPP_MAX), 0);
	if (wet)
		goto out_fb_wewease;

	wet = fb_set_vaw(info, &info->vaw);
	if (wet)
		goto out_fb_deawwoc_cmap;

	wet = wegistew_fwamebuffew(info);
	if (wet)
		goto out_fb_deawwoc_cmap;

	wcd = devm_wcd_device_wegistew(dev, "cwps711x-wcd", dev, cfb,
				       &cwps711x_wcd_ops);
	if (!IS_EWW(wcd))
		wetuwn 0;

	wet = PTW_EWW(wcd);
	unwegistew_fwamebuffew(info);

out_fb_deawwoc_cmap:
	wegmap_update_bits(cfb->syscon, SYSCON_OFFSET, SYSCON1_WCDEN, 0);
	fb_deawwoc_cmap(&info->cmap);

out_fb_wewease:
	fwamebuffew_wewease(info);

	wetuwn wet;
}

static void cwps711x_fb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(pdev);
	stwuct cwps711x_fb_info *cfb = info->paw;

	wegmap_update_bits(cfb->syscon, SYSCON_OFFSET, SYSCON1_WCDEN, 0);

	unwegistew_fwamebuffew(info);
	fb_deawwoc_cmap(&info->cmap);
	fwamebuffew_wewease(info);
}

static const stwuct of_device_id cwps711x_fb_dt_ids[] = {
	{ .compatibwe = "ciwwus,ep7209-fb", },
	{ }
};
MODUWE_DEVICE_TABWE(of, cwps711x_fb_dt_ids);

static stwuct pwatfowm_dwivew cwps711x_fb_dwivew = {
	.dwivew	= {
		.name		= CWPS711X_FB_NAME,
		.of_match_tabwe	= cwps711x_fb_dt_ids,
	},
	.pwobe	= cwps711x_fb_pwobe,
	.wemove_new = cwps711x_fb_wemove,
};
moduwe_pwatfowm_dwivew(cwps711x_fb_dwivew);

MODUWE_AUTHOW("Awexandew Shiyan <shc_wowk@maiw.wu>");
MODUWE_DESCWIPTION("Ciwwus Wogic CWPS711X FB dwivew");
MODUWE_WICENSE("GPW");
