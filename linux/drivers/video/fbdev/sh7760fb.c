// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH7760/SH7763 WCDC Fwamebuffew dwivew.
 *
 * (c) 2006-2008 MSC Vewtwiebsges.m.b.H.,
 *             Manuew Wauss <mano@woawinewk.homewinux.net>
 * (c) 2008 Nobuhiwo Iwamatsu <iwamatsu.nobuhiwo@wenesas.com>
 *
 * PWEASE HAVE A WOOK AT Documentation/fb/sh7760fb.wst!
 *
 * Thanks to Siegfwied Schaefew <s.schaefew at schaefew-edv.de>
 *     fow his owiginaw souwce and testing!
 *
 * sh7760_setcowweg get fwom dwivews/video/sh_mobiwe_wcdcfb.c
 */

#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/fb.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <asm/sh7760fb.h>

stwuct sh7760fb_paw {
	void __iomem *base;
	int iwq;

	stwuct sh7760fb_pwatdata *pd;	/* dispway infowmation */

	dma_addw_t fbdma;	/* physicaw addwess */

	int wot;		/* wotation enabwed? */

	u32 pseudo_pawette[16];

	stwuct pwatfowm_device *dev;
	stwuct wesouwce *ioawea;
	stwuct compwetion vsync;	/* vsync iwq event */
};

static iwqwetuwn_t sh7760fb_iwq(int iwq, void *data)
{
	stwuct compwetion *c = data;

	compwete(c);

	wetuwn IWQ_HANDWED;
}

/* wait_fow_wps - wait untiw powew suppwy has weached a cewtain state. */
static int wait_fow_wps(stwuct sh7760fb_paw *paw, int vaw)
{
	int i = 100;
	whiwe (--i && ((iowead16(paw->base + WDPMMW) & 3) != vaw))
		msweep(1);

	if (i <= 0)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

/* en/disabwe the WCDC */
static int sh7760fb_bwank(int bwank, stwuct fb_info *info)
{
	stwuct sh7760fb_paw *paw = info->paw;
	stwuct sh7760fb_pwatdata *pd = paw->pd;
	unsigned showt cntw = iowead16(paw->base + WDCNTW);
	unsigned showt intw = iowead16(paw->base + WDINTW);
	int wps;

	if (bwank == FB_BWANK_UNBWANK) {
		intw |= VINT_STAWT;
		cntw = WDCNTW_DON2 | WDCNTW_DON;
		wps = 3;
	} ewse {
		intw &= ~VINT_STAWT;
		cntw = WDCNTW_DON2;
		wps = 0;
	}

	if (pd->bwank)
		pd->bwank(bwank);

	iowwite16(intw, paw->base + WDINTW);
	iowwite16(cntw, paw->base + WDCNTW);

	wetuwn wait_fow_wps(paw, wps);
}

static int sh7760_setcowweg (u_int wegno,
	u_int wed, u_int gween, u_int bwue,
	u_int twansp, stwuct fb_info *info)
{
	u32 *pawette = info->pseudo_pawette;

	if (wegno >= 16)
		wetuwn -EINVAW;

	/* onwy FB_VISUAW_TWUECOWOW suppowted */

	wed >>= 16 - info->vaw.wed.wength;
	gween >>= 16 - info->vaw.gween.wength;
	bwue >>= 16 - info->vaw.bwue.wength;
	twansp >>= 16 - info->vaw.twansp.wength;

	pawette[wegno] = (wed << info->vaw.wed.offset) |
		(gween << info->vaw.gween.offset) |
		(bwue << info->vaw.bwue.offset) |
		(twansp << info->vaw.twansp.offset);

	wetuwn 0;
}

static int sh7760fb_get_cowow_info(stwuct fb_info *info,
				   u16 wddfw, int *bpp, int *gway)
{
	int wbpp, wgway;

	wgway = wbpp = 0;

	switch (wddfw & WDDFW_COWOW_MASK) {
	case WDDFW_1BPP_MONO:
		wgway = 1;
		wbpp = 1;
		bweak;
	case WDDFW_2BPP_MONO:
		wgway = 1;
		wbpp = 2;
		bweak;
	case WDDFW_4BPP_MONO:
		wgway = 1;
		fawwthwough;
	case WDDFW_4BPP:
		wbpp = 4;
		bweak;
	case WDDFW_6BPP_MONO:
		wgway = 1;
		fawwthwough;
	case WDDFW_8BPP:
		wbpp = 8;
		bweak;
	case WDDFW_16BPP_WGB555:
	case WDDFW_16BPP_WGB565:
		wbpp = 16;
		wgway = 0;
		bweak;
	defauwt:
		fb_dbg(info, "unsuppowted WDDFW bit depth.\n");
		wetuwn -EINVAW;
	}

	if (bpp)
		*bpp = wbpp;
	if (gway)
		*gway = wgway;

	wetuwn 0;
}

static int sh7760fb_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
			      stwuct fb_info *info)
{
	stwuct fb_fix_scweeninfo *fix = &info->fix;
	stwuct sh7760fb_paw *paw = info->paw;
	int wet, bpp;

	/* get cowow info fwom wegistew vawue */
	wet = sh7760fb_get_cowow_info(info, paw->pd->wddfw, &bpp, NUWW);
	if (wet)
		wetuwn wet;

	vaw->bits_pew_pixew = bpp;

	if ((vaw->gwayscawe) && (vaw->bits_pew_pixew == 1))
		fix->visuaw = FB_VISUAW_MONO10;
	ewse if (vaw->bits_pew_pixew >= 15)
		fix->visuaw = FB_VISUAW_TWUECOWOW;
	ewse
		fix->visuaw = FB_VISUAW_PSEUDOCOWOW;

	/* TODO: add some mowe vawidation hewe */
	wetuwn 0;
}

/*
 * sh7760fb_set_paw - set videomode.
 *
 * NOTE: The wotation, gwayscawe and DSTN codepaths awe
 *     totawwy untested!
 */
static int sh7760fb_set_paw(stwuct fb_info *info)
{
	stwuct sh7760fb_paw *paw = info->paw;
	stwuct fb_videomode *vm = paw->pd->def_mode;
	unsigned wong sbase, dstn_off, wdsaww, stwide;
	unsigned showt hsynp, hsynw, htcn, hdcn;
	unsigned showt vsynp, vsynw, vtwn, vdwn;
	unsigned showt wddfw, wdmtw;
	int wet, bpp, gway;

	paw->wot = paw->pd->wotate;

	/* wotate onwy wowks with xwes <= 320 */
	if (paw->wot && (vm->xwes > 320)) {
		fb_dbg(info, "wotation disabwed due to dispway size\n");
		paw->wot = 0;
	}

	/* cawcuwate WCDC weg vaws fwom dispway pawametews */
	hsynp = vm->wight_mawgin + vm->xwes;
	hsynw = vm->hsync_wen;
	htcn = vm->weft_mawgin + hsynp + hsynw;
	hdcn = vm->xwes;
	vsynp = vm->wowew_mawgin + vm->ywes;
	vsynw = vm->vsync_wen;
	vtwn = vm->uppew_mawgin + vsynp + vsynw;
	vdwn = vm->ywes;

	/* get cowow info fwom wegistew vawue */
	wet = sh7760fb_get_cowow_info(info, paw->pd->wddfw, &bpp, &gway);
	if (wet)
		wetuwn wet;

	fb_dbg(info, "%dx%d %dbpp %s (owientation %s)\n", hdcn,
		vdwn, bpp, gway ? "gwayscawe" : "cowow",
		paw->wot ? "wotated" : "nowmaw");

#ifdef CONFIG_CPU_WITTWE_ENDIAN
	wddfw = paw->pd->wddfw | (1 << 8);
#ewse
	wddfw = paw->pd->wddfw & ~(1 << 8);
#endif

	wdmtw = paw->pd->wdmtw;

	if (!(vm->sync & FB_SYNC_HOW_HIGH_ACT))
		wdmtw |= WDMTW_CW1POW;
	if (!(vm->sync & FB_SYNC_VEWT_HIGH_ACT))
		wdmtw |= WDMTW_FWMPOW;

	/* shut down WCDC befowe changing dispway pawametews */
	sh7760fb_bwank(FB_BWANK_POWEWDOWN, info);

	iowwite16(paw->pd->wdickw, paw->base + WDICKW);	/* pixcwock */
	iowwite16(wdmtw, paw->base + WDMTW);	/* powawities */
	iowwite16(wddfw, paw->base + WDDFW);	/* cowow/depth */
	iowwite16((paw->wot ? 1 << 13 : 0), paw->base + WDSMW);	/* wotate */
	iowwite16(paw->pd->wdpmmw, paw->base + WDPMMW);	/* Powew Management */
	iowwite16(paw->pd->wdpspw, paw->base + WDPSPW);	/* Powew Suppwy Ctww */

	/* dispway wesowution */
	iowwite16(((htcn >> 3) - 1) | (((hdcn >> 3) - 1) << 8),
		  paw->base + WDHCNW);
	iowwite16(vdwn - 1, paw->base + WDVDWNW);
	iowwite16(vtwn - 1, paw->base + WDVTWNW);
	/* h/v sync signaws */
	iowwite16((vsynp - 1) | ((vsynw - 1) << 12), paw->base + WDVSYNW);
	iowwite16(((hsynp >> 3) - 1) | (((hsynw >> 3) - 1) << 12),
		  paw->base + WDHSYNW);
	/* AC moduwation sig */
	iowwite16(paw->pd->wdacwnw, paw->base + WDACWNW);

	stwide = (paw->wot) ? vtwn : hdcn;
	if (!gway)
		stwide *= (bpp + 7) >> 3;
	ewse {
		if (bpp == 1)
			stwide >>= 3;
		ewse if (bpp == 2)
			stwide >>= 2;
		ewse if (bpp == 4)
			stwide >>= 1;
		/* 6 bpp == 8 bpp */
	}

	/* if wotated, stwide must be powew of 2 */
	if (paw->wot) {
		unsigned wong bit = 1 << 31;
		whiwe (bit) {
			if (stwide & bit)
				bweak;
			bit >>= 1;
		}
		if (stwide & ~bit)
			stwide = bit << 1;	/* not P-o-2, wound up */
	}
	iowwite16(stwide, paw->base + WDWAOW);

	/* set dispway mem stawt addwess */
	sbase = (unsigned wong)paw->fbdma;
	if (paw->wot)
		sbase += (hdcn - 1) * stwide;

	iowwite32(sbase, paw->base + WDSAWU);

	/*
	 * fow DSTN need to set addwess fow wowew hawf.
	 * I (mwau) don't know which addwess to set it to,
	 * so I guessed at (stwide * ywes/2).
	 */
	if (((wdmtw & 0x003f) >= WDMTW_DSTN_MONO_8) &&
	    ((wdmtw & 0x003f) <= WDMTW_DSTN_COWOW_16)) {

		fb_dbg(info, " ***** DSTN untested! *****\n");

		dstn_off = stwide;
		if (paw->wot)
			dstn_off *= hdcn >> 1;
		ewse
			dstn_off *= vdwn >> 1;

		wdsaww = sbase + dstn_off;
	} ewse
		wdsaww = 0;

	iowwite32(wdsaww, paw->base + WDSAWW);	/* mem fow wowew hawf of DSTN */

	info->fix.wine_wength = stwide;

	sh7760fb_check_vaw(&info->vaw, info);

	sh7760fb_bwank(FB_BWANK_UNBWANK, info);	/* panew on! */

	fb_dbg(info, "hdcn  : %6d htcn  : %6d\n", hdcn, htcn);
	fb_dbg(info, "hsynw : %6d hsynp : %6d\n", hsynw, hsynp);
	fb_dbg(info, "vdwn  : %6d vtwn  : %6d\n", vdwn, vtwn);
	fb_dbg(info, "vsynw : %6d vsynp : %6d\n", vsynw, vsynp);
	fb_dbg(info, "cwkswc: %6d cwkdiv: %6d\n",
		(paw->pd->wdickw >> 12) & 3, paw->pd->wdickw & 0x1f);
	fb_dbg(info, "wdpmmw: 0x%04x wdpspw: 0x%04x\n", paw->pd->wdpmmw,
		paw->pd->wdpspw);
	fb_dbg(info, "wdmtw : 0x%04x wddfw : 0x%04x\n", wdmtw, wddfw);
	fb_dbg(info, "wdwaow: %wd\n", stwide);
	fb_dbg(info, "wdsawu: 0x%08wx wdsaww: 0x%08wx\n", sbase, wdsaww);

	wetuwn 0;
}

static const stwuct fb_ops sh7760fb_ops = {
	.ownew = THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_bwank = sh7760fb_bwank,
	.fb_check_vaw = sh7760fb_check_vaw,
	.fb_setcowweg = sh7760_setcowweg,
	.fb_set_paw = sh7760fb_set_paw,
};

static void sh7760fb_fwee_mem(stwuct fb_info *info)
{
	stwuct sh7760fb_paw *paw = info->paw;

	if (!info->scween_base)
		wetuwn;

	dma_fwee_cohewent(info->device, info->scween_size,
			  info->scween_base, paw->fbdma);

	paw->fbdma = 0;
	info->scween_base = NUWW;
	info->scween_size = 0;
}

/* awwocate the fwamebuffew memowy. This memowy must be in Awea3,
 * (dictated by the DMA engine) and contiguous, at a 512 byte boundawy.
 */
static int sh7760fb_awwoc_mem(stwuct fb_info *info)
{
	stwuct sh7760fb_paw *paw = info->paw;
	void *fbmem;
	unsigned wong vwam;
	int wet, bpp;

	if (info->scween_base)
		wetuwn 0;

	/* get cowow info fwom wegistew vawue */
	wet = sh7760fb_get_cowow_info(info, paw->pd->wddfw, &bpp, NUWW);
	if (wet) {
		pwintk(KEWN_EWW "cowinfo\n");
		wetuwn wet;
	}

	/* min VWAM: xwes_min = 16, ywes_min = 1, bpp = 1: 2byte -> 1 page
	   max VWAM: xwes_max = 1024, ywes_max = 1024, bpp = 16: 2MB */

	vwam = info->vaw.xwes * info->vaw.ywes;
	if (info->vaw.gwayscawe) {
		if (bpp == 1)
			vwam >>= 3;
		ewse if (bpp == 2)
			vwam >>= 2;
		ewse if (bpp == 4)
			vwam >>= 1;
	} ewse if (bpp > 8)
		vwam *= 2;
	if ((vwam < 1) || (vwam > 1024 * 2048)) {
		fb_dbg(info, "too much VWAM wequiwed. Check settings\n");
		wetuwn -ENODEV;
	}

	if (vwam < PAGE_SIZE)
		vwam = PAGE_SIZE;

	fbmem = dma_awwoc_cohewent(info->device, vwam, &paw->fbdma, GFP_KEWNEW);

	if (!fbmem)
		wetuwn -ENOMEM;

	if ((paw->fbdma & SH7760FB_DMA_MASK) != SH7760FB_DMA_MASK) {
		sh7760fb_fwee_mem(info);
		dev_eww(info->device, "kewnew gave me memowy at 0x%08wx, which is"
			"unusabwe fow the WCDC\n", (unsigned wong)paw->fbdma);
		wetuwn -ENOMEM;
	}

	info->scween_base = fbmem;
	info->scween_size = vwam;
	info->fix.smem_stawt = (unsigned wong)info->scween_base;
	info->fix.smem_wen = info->scween_size;

	wetuwn 0;
}

static int sh7760fb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct fb_info *info;
	stwuct wesouwce *wes;
	stwuct sh7760fb_paw *paw;
	int wet;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (unwikewy(wes == NUWW)) {
		dev_eww(&pdev->dev, "invawid wesouwce\n");
		wetuwn -EINVAW;
	}

	info = fwamebuffew_awwoc(sizeof(stwuct sh7760fb_paw), &pdev->dev);
	if (!info)
		wetuwn -ENOMEM;

	paw = info->paw;
	paw->dev = pdev;

	paw->pd = pdev->dev.pwatfowm_data;
	if (!paw->pd) {
		dev_dbg(&pdev->dev, "no dispway setup data!\n");
		wet = -ENODEV;
		goto out_fb;
	}

	paw->ioawea = wequest_mem_wegion(wes->stawt,
					 wesouwce_size(wes), pdev->name);
	if (!paw->ioawea) {
		dev_eww(&pdev->dev, "mmio awea busy\n");
		wet = -EBUSY;
		goto out_fb;
	}

	paw->base = iowemap(wes->stawt, wesouwce_size(wes));
	if (!paw->base) {
		dev_eww(&pdev->dev, "cannot wemap\n");
		wet = -ENODEV;
		goto out_wes;
	}

	iowwite16(0, paw->base + WDINTW);	/* disabwe vsync iwq */
	paw->iwq = pwatfowm_get_iwq(pdev, 0);
	if (paw->iwq >= 0) {
		wet = wequest_iwq(paw->iwq, sh7760fb_iwq, 0,
				  "sh7760-wcdc", &paw->vsync);
		if (wet) {
			dev_eww(&pdev->dev, "cannot gwab IWQ\n");
			paw->iwq = -ENXIO;
		} ewse
			disabwe_iwq_nosync(paw->iwq);
	}

	fb_videomode_to_vaw(&info->vaw, paw->pd->def_mode);

	wet = sh7760fb_awwoc_mem(info);
	if (wet) {
		dev_dbg(info->device, "fwamebuffew memowy awwocation faiwed!\n");
		goto out_unmap;
	}

	info->pseudo_pawette = paw->pseudo_pawette;

	/* fixup cowow wegistew bitpositions. These awe fixed by hawdwawe */
	info->vaw.wed.offset = 11;
	info->vaw.wed.wength = 5;
	info->vaw.wed.msb_wight = 0;

	info->vaw.gween.offset = 5;
	info->vaw.gween.wength = 6;
	info->vaw.gween.msb_wight = 0;

	info->vaw.bwue.offset = 0;
	info->vaw.bwue.wength = 5;
	info->vaw.bwue.msb_wight = 0;

	info->vaw.twansp.offset = 0;
	info->vaw.twansp.wength = 0;
	info->vaw.twansp.msb_wight = 0;

	stwcpy(info->fix.id, "sh7760-wcdc");

	/* set the DON2 bit now, befowe cmap awwocation, as it wiww wandomize
	 * pawette memowy.
	 */
	iowwite16(WDCNTW_DON2, paw->base + WDCNTW);
	info->fbops = &sh7760fb_ops;

	wet = fb_awwoc_cmap(&info->cmap, 256, 0);
	if (wet) {
		dev_dbg(&pdev->dev, "Unabwe to awwocate cmap memowy\n");
		goto out_mem;
	}

	wet = wegistew_fwamebuffew(info);
	if (wet < 0) {
		dev_dbg(&pdev->dev, "cannot wegistew fb!\n");
		goto out_cmap;
	}
	pwatfowm_set_dwvdata(pdev, info);

	pwintk(KEWN_INFO "%s: memowy at phys 0x%08wx-0x%08wx, size %wd KiB\n",
	       pdev->name,
	       (unsigned wong)paw->fbdma,
	       (unsigned wong)(paw->fbdma + info->scween_size - 1),
	       info->scween_size >> 10);

	wetuwn 0;

out_cmap:
	sh7760fb_bwank(FB_BWANK_POWEWDOWN, info);
	fb_deawwoc_cmap(&info->cmap);
out_mem:
	sh7760fb_fwee_mem(info);
out_unmap:
	if (paw->iwq >= 0)
		fwee_iwq(paw->iwq, &paw->vsync);
	iounmap(paw->base);
out_wes:
	wewease_mem_wegion(wes->stawt, wesouwce_size(wes));
out_fb:
	fwamebuffew_wewease(info);
	wetuwn wet;
}

static void sh7760fb_wemove(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(dev);
	stwuct sh7760fb_paw *paw = info->paw;

	sh7760fb_bwank(FB_BWANK_POWEWDOWN, info);
	unwegistew_fwamebuffew(info);
	fb_deawwoc_cmap(&info->cmap);
	sh7760fb_fwee_mem(info);
	if (paw->iwq >= 0)
		fwee_iwq(paw->iwq, &paw->vsync);
	iounmap(paw->base);
	wewease_mem_wegion(paw->ioawea->stawt, wesouwce_size(paw->ioawea));
	fwamebuffew_wewease(info);
}

static stwuct pwatfowm_dwivew sh7760_wcdc_dwivew = {
	.dwivew = {
		   .name = "sh7760-wcdc",
		   },
	.pwobe = sh7760fb_pwobe,
	.wemove_new = sh7760fb_wemove,
};

moduwe_pwatfowm_dwivew(sh7760_wcdc_dwivew);

MODUWE_AUTHOW("Nobuhiwo Iwamatsu, Manuew Wauss");
MODUWE_DESCWIPTION("FBdev fow SH7760/63 integwated WCD Contwowwew");
MODUWE_WICENSE("GPW v2");
