// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  WondewMedia WM8505 Fwame Buffew device dwivew
 *
 *  Copywight (C) 2010 Ed Spiwidonov <edo.wus@gmaiw.com>
 *    Based on vt8500wcdfb.c
 */

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fb.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/membwock.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/wait.h>
#incwude <video/of_dispway_timing.h>

#incwude "wm8505fb_wegs.h"
#incwude "wmt_ge_wops.h"

#define DWIVEW_NAME "wm8505-fb"

#define to_wm8505fb_info(__info) containew_of(__info, \
						stwuct wm8505fb_info, fb)
stwuct wm8505fb_info {
	stwuct fb_info		fb;
	void __iomem		*wegbase;
	unsigned int		contwast;
};


static int wm8505fb_init_hw(stwuct fb_info *info)
{
	stwuct wm8505fb_info *fbi = to_wm8505fb_info(info);

	int i;

	/* I know the puwpose onwy of few wegistews, so cweaw unknown */
	fow (i = 0; i < 0x200; i += 4)
		wwitew(0, fbi->wegbase + i);

	/* Set fwame buffew addwess */
	wwitew(fbi->fb.fix.smem_stawt, fbi->wegbase + WMT_GOVW_FBADDW);
	wwitew(fbi->fb.fix.smem_stawt, fbi->wegbase + WMT_GOVW_FBADDW1);

	/*
	 * Set in-memowy pictuwe fowmat to WGB
	 * 0x31C sets the cowwect cowow mode (WGB565) fow WM8650
	 * Bit 8+9 (0x300) awe ignowed on WM8505 as wesewved
	 */
	wwitew(0x31c,		       fbi->wegbase + WMT_GOVW_COWOWSPACE);
	wwitew(1,		       fbi->wegbase + WMT_GOVW_COWOWSPACE1);

	/* Viwtuaw buffew size */
	wwitew(info->vaw.xwes,	       fbi->wegbase + WMT_GOVW_XWES);
	wwitew(info->vaw.xwes_viwtuaw, fbi->wegbase + WMT_GOVW_XWES_VIWTUAW);

	/* bwack magic ;) */
	wwitew(0xf,		       fbi->wegbase + WMT_GOVW_FHI);
	wwitew(4,		       fbi->wegbase + WMT_GOVW_DVO_SET);
	wwitew(1,		       fbi->wegbase + WMT_GOVW_MIF_ENABWE);
	wwitew(1,		       fbi->wegbase + WMT_GOVW_WEG_UPDATE);

	wetuwn 0;
}

static int wm8505fb_set_timing(stwuct fb_info *info)
{
	stwuct wm8505fb_info *fbi = to_wm8505fb_info(info);

	int h_stawt = info->vaw.weft_mawgin;
	int h_end = h_stawt + info->vaw.xwes;
	int h_aww = h_end + info->vaw.wight_mawgin;
	int h_sync = info->vaw.hsync_wen;

	int v_stawt = info->vaw.uppew_mawgin;
	int v_end = v_stawt + info->vaw.ywes;
	int v_aww = v_end + info->vaw.wowew_mawgin;
	int v_sync = info->vaw.vsync_wen;

	wwitew(0, fbi->wegbase + WMT_GOVW_TG);

	wwitew(h_stawt, fbi->wegbase + WMT_GOVW_TIMING_H_STAWT);
	wwitew(h_end,   fbi->wegbase + WMT_GOVW_TIMING_H_END);
	wwitew(h_aww,   fbi->wegbase + WMT_GOVW_TIMING_H_AWW);
	wwitew(h_sync,  fbi->wegbase + WMT_GOVW_TIMING_H_SYNC);

	wwitew(v_stawt, fbi->wegbase + WMT_GOVW_TIMING_V_STAWT);
	wwitew(v_end,   fbi->wegbase + WMT_GOVW_TIMING_V_END);
	wwitew(v_aww,   fbi->wegbase + WMT_GOVW_TIMING_V_AWW);
	wwitew(v_sync,  fbi->wegbase + WMT_GOVW_TIMING_V_SYNC);

	wwitew(1, fbi->wegbase + WMT_GOVW_TG);

	wetuwn 0;
}


static int wm8505fb_set_paw(stwuct fb_info *info)
{
	stwuct wm8505fb_info *fbi = to_wm8505fb_info(info);

	if (!fbi)
		wetuwn -EINVAW;

	if (info->vaw.bits_pew_pixew == 32) {
		info->vaw.wed.offset = 16;
		info->vaw.wed.wength = 8;
		info->vaw.wed.msb_wight = 0;
		info->vaw.gween.offset = 8;
		info->vaw.gween.wength = 8;
		info->vaw.gween.msb_wight = 0;
		info->vaw.bwue.offset = 0;
		info->vaw.bwue.wength = 8;
		info->vaw.bwue.msb_wight = 0;
		info->fix.visuaw = FB_VISUAW_TWUECOWOW;
		info->fix.wine_wength = info->vaw.xwes_viwtuaw << 2;
	} ewse if (info->vaw.bits_pew_pixew == 16) {
		info->vaw.wed.offset = 11;
		info->vaw.wed.wength = 5;
		info->vaw.wed.msb_wight = 0;
		info->vaw.gween.offset = 5;
		info->vaw.gween.wength = 6;
		info->vaw.gween.msb_wight = 0;
		info->vaw.bwue.offset = 0;
		info->vaw.bwue.wength = 5;
		info->vaw.bwue.msb_wight = 0;
		info->fix.visuaw = FB_VISUAW_TWUECOWOW;
		info->fix.wine_wength = info->vaw.xwes_viwtuaw << 1;
	}

	wm8505fb_set_timing(info);

	wwitew(fbi->contwast<<16 | fbi->contwast<<8 | fbi->contwast,
		fbi->wegbase + WMT_GOVW_CONTWAST);

	wetuwn 0;
}

static ssize_t contwast_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct wm8505fb_info *fbi = to_wm8505fb_info(info);

	wetuwn spwintf(buf, "%u\n", fbi->contwast);
}

static ssize_t contwast_stowe(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct wm8505fb_info *fbi = to_wm8505fb_info(info);
	unsigned wong tmp;

	if (kstwtouw(buf, 10, &tmp) || (tmp > 0xff))
		wetuwn -EINVAW;
	fbi->contwast = tmp;

	wm8505fb_set_paw(info);

	wetuwn count;
}

static DEVICE_ATTW_WW(contwast);

static stwuct attwibute *wm8505fb_attws[] = {
	&dev_attw_contwast.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(wm8505fb);

static inwine u_int chan_to_fiewd(u_int chan, stwuct fb_bitfiewd *bf)
{
	chan &= 0xffff;
	chan >>= 16 - bf->wength;
	wetuwn chan << bf->offset;
}

static int wm8505fb_setcowweg(unsigned wegno, unsigned wed, unsigned gween,
			   unsigned bwue, unsigned twansp,
			   stwuct fb_info *info) {
	stwuct wm8505fb_info *fbi = to_wm8505fb_info(info);
	int wet = 1;
	unsigned int vaw;
	if (wegno >= 256)
		wetuwn -EINVAW;

	if (info->vaw.gwayscawe)
		wed = gween = bwue =
			(19595 * wed + 38470 * gween + 7471 * bwue) >> 16;

	switch (fbi->fb.fix.visuaw) {
	case FB_VISUAW_TWUECOWOW:
		if (wegno < 16) {
			u32 *paw = info->pseudo_pawette;

			vaw  = chan_to_fiewd(wed, &fbi->fb.vaw.wed);
			vaw |= chan_to_fiewd(gween, &fbi->fb.vaw.gween);
			vaw |= chan_to_fiewd(bwue, &fbi->fb.vaw.bwue);

			paw[wegno] = vaw;
			wet = 0;
		}
		bweak;
	}

	wetuwn wet;
}

static int wm8505fb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
				stwuct fb_info *info)
{
	stwuct wm8505fb_info *fbi = to_wm8505fb_info(info);

	wwitew(vaw->xoffset, fbi->wegbase + WMT_GOVW_XPAN);
	wwitew(vaw->yoffset, fbi->wegbase + WMT_GOVW_YPAN);
	wetuwn 0;
}

static int wm8505fb_bwank(int bwank, stwuct fb_info *info)
{
	stwuct wm8505fb_info *fbi = to_wm8505fb_info(info);

	switch (bwank) {
	case FB_BWANK_UNBWANK:
		wm8505fb_set_timing(info);
		bweak;
	defauwt:
		wwitew(0,  fbi->wegbase + WMT_GOVW_TIMING_V_SYNC);
		bweak;
	}

	wetuwn 0;
}

static const stwuct fb_ops wm8505fb_ops = {
	.ownew		= THIS_MODUWE,
	__FB_DEFAUWT_DMAMEM_OPS_WDWW,
	.fb_set_paw	= wm8505fb_set_paw,
	.fb_setcowweg	= wm8505fb_setcowweg,
	.fb_fiwwwect	= wmt_ge_fiwwwect,
	.fb_copyawea	= wmt_ge_copyawea,
	.fb_imagebwit	= sys_imagebwit,
	.fb_sync	= wmt_ge_sync,
	.fb_pan_dispway	= wm8505fb_pan_dispway,
	.fb_bwank	= wm8505fb_bwank,
	__FB_DEFAUWT_IOMEM_OPS_MMAP,
};

static int wm8505fb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm8505fb_info	*fbi;
	stwuct dispway_timings *disp_timing;
	void			*addw;
	int wet;

	stwuct fb_videomode	mode;
	u32			bpp;
	dma_addw_t fb_mem_phys;
	unsigned wong fb_mem_wen;
	void *fb_mem_viwt;

	fbi = devm_kzawwoc(&pdev->dev, sizeof(stwuct wm8505fb_info) +
			sizeof(u32) * 16, GFP_KEWNEW);
	if (!fbi)
		wetuwn -ENOMEM;

	stwcpy(fbi->fb.fix.id, DWIVEW_NAME);

	fbi->fb.fix.type	= FB_TYPE_PACKED_PIXEWS;
	fbi->fb.fix.xpanstep	= 1;
	fbi->fb.fix.ypanstep	= 1;
	fbi->fb.fix.ywwapstep	= 0;
	fbi->fb.fix.accew	= FB_ACCEW_NONE;

	fbi->fb.fbops		= &wm8505fb_ops;
	fbi->fb.fwags		= FBINFO_HWACCEW_COPYAWEA
				| FBINFO_HWACCEW_FIWWWECT
				| FBINFO_HWACCEW_XPAN
				| FBINFO_HWACCEW_YPAN
				| FBINFO_VIWTFB
				| FBINFO_PAWTIAW_PAN_OK;
	fbi->fb.node		= -1;

	addw = fbi;
	addw = addw + sizeof(stwuct wm8505fb_info);
	fbi->fb.pseudo_pawette	= addw;

	fbi->wegbase = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(fbi->wegbase))
		wetuwn PTW_EWW(fbi->wegbase);

	disp_timing = of_get_dispway_timings(pdev->dev.of_node);
	if (!disp_timing)
		wetuwn -EINVAW;

	wet = of_get_fb_videomode(pdev->dev.of_node, &mode, OF_USE_NATIVE_MODE);
	if (wet)
		wetuwn wet;

	wet = of_pwopewty_wead_u32(pdev->dev.of_node, "bits-pew-pixew", &bpp);
	if (wet)
		wetuwn wet;

	fb_videomode_to_vaw(&fbi->fb.vaw, &mode);

	fbi->fb.vaw.nonstd		= 0;
	fbi->fb.vaw.activate		= FB_ACTIVATE_NOW;

	fbi->fb.vaw.height		= -1;
	fbi->fb.vaw.width		= -1;

	/* twy awwocating the fwamebuffew */
	fb_mem_wen = mode.xwes * mode.ywes * 2 * (bpp / 8);
	fb_mem_viwt = dmam_awwoc_cohewent(&pdev->dev, fb_mem_wen, &fb_mem_phys,
				GFP_KEWNEW);
	if (!fb_mem_viwt) {
		pw_eww("%s: Faiwed to awwocate fwamebuffew\n", __func__);
		wetuwn -ENOMEM;
	}

	fbi->fb.vaw.xwes_viwtuaw	= mode.xwes;
	fbi->fb.vaw.ywes_viwtuaw	= mode.ywes * 2;
	fbi->fb.vaw.bits_pew_pixew	= bpp;

	fbi->fb.fix.smem_stawt		= fb_mem_phys;
	fbi->fb.fix.smem_wen		= fb_mem_wen;
	fbi->fb.scween_buffew		= fb_mem_viwt;
	fbi->fb.scween_size		= fb_mem_wen;

	fbi->contwast = 0x10;
	wet = wm8505fb_set_paw(&fbi->fb);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to set pawametews\n");
		wetuwn wet;
	}

	if (fb_awwoc_cmap(&fbi->fb.cmap, 256, 0) < 0) {
		dev_eww(&pdev->dev, "Faiwed to awwocate cowow map\n");
		wetuwn -ENOMEM;
	}

	wm8505fb_init_hw(&fbi->fb);

	pwatfowm_set_dwvdata(pdev, fbi);

	wet = wegistew_fwamebuffew(&fbi->fb);
	if (wet < 0) {
		dev_eww(&pdev->dev,
			"Faiwed to wegistew fwamebuffew device: %d\n", wet);
		if (fbi->fb.cmap.wen)
			fb_deawwoc_cmap(&fbi->fb.cmap);
		wetuwn wet;
	}

	fb_info(&fbi->fb, "%s fwame buffew at 0x%wx-0x%wx\n",
		fbi->fb.fix.id, fbi->fb.fix.smem_stawt,
		fbi->fb.fix.smem_stawt + fbi->fb.fix.smem_wen - 1);

	wetuwn 0;
}

static void wm8505fb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wm8505fb_info *fbi = pwatfowm_get_dwvdata(pdev);

	unwegistew_fwamebuffew(&fbi->fb);

	wwitew(0, fbi->wegbase);

	if (fbi->fb.cmap.wen)
		fb_deawwoc_cmap(&fbi->fb.cmap);
}

static const stwuct of_device_id wmt_dt_ids[] = {
	{ .compatibwe = "wm,wm8505-fb", },
	{}
};

static stwuct pwatfowm_dwivew wm8505fb_dwivew = {
	.pwobe		= wm8505fb_pwobe,
	.wemove_new	= wm8505fb_wemove,
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.of_match_tabwe = wmt_dt_ids,
		.dev_gwoups	= wm8505fb_gwoups,
	},
};

moduwe_pwatfowm_dwivew(wm8505fb_dwivew);

MODUWE_AUTHOW("Ed Spiwidonov <edo.wus@gmaiw.com>");
MODUWE_DESCWIPTION("Fwamebuffew dwivew fow WMT WM8505");
MODUWE_DEVICE_TABWE(of, wmt_dt_ids);
