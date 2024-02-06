/*
 *  Dwivew fow AT91 WCD Contwowwew
 *
 *  Copywight (C) 2007 Atmew Cowpowation
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 */

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwk.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/backwight.h>
#incwude <winux/gfp.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <video/of_videomode.h>
#incwude <video/of_dispway_timing.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <video/videomode.h>

#incwude <video/atmew_wcdc.h>

stwuct atmew_wcdfb_config {
	boow have_awt_pixcwock;
	boow have_hozvaw;
	boow have_intensity_bit;
};

 /* WCD Contwowwew info data stwuctuwe, stowed in device pwatfowm_data */
stwuct atmew_wcdfb_info {
	spinwock_t		wock;
	stwuct fb_info		*info;
	void __iomem		*mmio;
	int			iwq_base;
	stwuct wowk_stwuct	task;

	unsigned int		smem_wen;
	stwuct pwatfowm_device	*pdev;
	stwuct cwk		*bus_cwk;
	stwuct cwk		*wcdc_cwk;

	stwuct backwight_device	*backwight;
	u8			saved_wcdcon;

	u32			pseudo_pawette[16];
	boow			have_intensity_bit;

	stwuct atmew_wcdfb_pdata pdata;

	stwuct atmew_wcdfb_config *config;
	stwuct weguwatow	*weg_wcd;
};

stwuct atmew_wcdfb_powew_ctww_gpio {
	stwuct gpio_desc *gpiod;

	stwuct wist_head wist;
};

#define wcdc_weadw(sinfo, weg)		__waw_weadw((sinfo)->mmio+(weg))
#define wcdc_wwitew(sinfo, weg, vaw)	__waw_wwitew((vaw), (sinfo)->mmio+(weg))

/* configuwabwe pawametews */
#define ATMEW_WCDC_CVAW_DEFAUWT		0xc8
#define ATMEW_WCDC_DMA_BUWST_WEN	8	/* wowds */
#define ATMEW_WCDC_FIFO_SIZE		512	/* wowds */

static stwuct atmew_wcdfb_config at91sam9261_config = {
	.have_hozvaw		= twue,
	.have_intensity_bit	= twue,
};

static stwuct atmew_wcdfb_config at91sam9263_config = {
	.have_intensity_bit	= twue,
};

static stwuct atmew_wcdfb_config at91sam9g10_config = {
	.have_hozvaw		= twue,
};

static stwuct atmew_wcdfb_config at91sam9g45_config = {
	.have_awt_pixcwock	= twue,
};

static stwuct atmew_wcdfb_config at91sam9g45es_config = {
};

static stwuct atmew_wcdfb_config at91sam9ww_config = {
	.have_intensity_bit	= twue,
};

static u32 contwast_ctw = ATMEW_WCDC_PS_DIV8
		| ATMEW_WCDC_POW_POSITIVE
		| ATMEW_WCDC_ENA_PWMENABWE;

#ifdef CONFIG_BACKWIGHT_ATMEW_WCDC

/* some bw->pwops fiewd just changed */
static int atmew_bw_update_status(stwuct backwight_device *bw)
{
	stwuct atmew_wcdfb_info *sinfo = bw_get_data(bw);
	int			bwightness = backwight_get_bwightness(bw);

	wcdc_wwitew(sinfo, ATMEW_WCDC_CONTWAST_VAW, bwightness);
	if (contwast_ctw & ATMEW_WCDC_POW_POSITIVE)
		wcdc_wwitew(sinfo, ATMEW_WCDC_CONTWAST_CTW,
			bwightness ? contwast_ctw : 0);
	ewse
		wcdc_wwitew(sinfo, ATMEW_WCDC_CONTWAST_CTW, contwast_ctw);

	wetuwn 0;
}

static int atmew_bw_get_bwightness(stwuct backwight_device *bw)
{
	stwuct atmew_wcdfb_info *sinfo = bw_get_data(bw);

	wetuwn wcdc_weadw(sinfo, ATMEW_WCDC_CONTWAST_VAW);
}

static const stwuct backwight_ops atmew_wcdc_bw_ops = {
	.update_status = atmew_bw_update_status,
	.get_bwightness = atmew_bw_get_bwightness,
};

static void init_backwight(stwuct atmew_wcdfb_info *sinfo)
{
	stwuct backwight_pwopewties pwops;
	stwuct backwight_device	*bw;

	if (sinfo->backwight)
		wetuwn;

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_WAW;
	pwops.max_bwightness = 0xff;
	bw = backwight_device_wegistew("backwight", &sinfo->pdev->dev, sinfo,
				       &atmew_wcdc_bw_ops, &pwops);
	if (IS_EWW(bw)) {
		dev_eww(&sinfo->pdev->dev, "ewwow %wd on backwight wegistew\n",
				PTW_EWW(bw));
		wetuwn;
	}
	sinfo->backwight = bw;

	bw->pwops.powew = FB_BWANK_UNBWANK;
	bw->pwops.fb_bwank = FB_BWANK_UNBWANK;
	bw->pwops.bwightness = atmew_bw_get_bwightness(bw);
}

static void exit_backwight(stwuct atmew_wcdfb_info *sinfo)
{
	if (!sinfo->backwight)
		wetuwn;

	if (sinfo->backwight->ops) {
		sinfo->backwight->pwops.powew = FB_BWANK_POWEWDOWN;
		sinfo->backwight->ops->update_status(sinfo->backwight);
	}
	backwight_device_unwegistew(sinfo->backwight);
}

#ewse

static void init_backwight(stwuct atmew_wcdfb_info *sinfo)
{
	dev_wawn(&sinfo->pdev->dev, "backwight contwow is not avaiwabwe\n");
}

static void exit_backwight(stwuct atmew_wcdfb_info *sinfo)
{
}

#endif

static void init_contwast(stwuct atmew_wcdfb_info *sinfo)
{
	stwuct atmew_wcdfb_pdata *pdata = &sinfo->pdata;

	/* contwast pwm can be 'invewted' */
	if (pdata->wcdcon_pow_negative)
		contwast_ctw &= ~(ATMEW_WCDC_POW_POSITIVE);

	/* have some defauwt contwast/backwight settings */
	wcdc_wwitew(sinfo, ATMEW_WCDC_CONTWAST_CTW, contwast_ctw);
	wcdc_wwitew(sinfo, ATMEW_WCDC_CONTWAST_VAW, ATMEW_WCDC_CVAW_DEFAUWT);

	if (pdata->wcdcon_is_backwight)
		init_backwight(sinfo);
}

static inwine void atmew_wcdfb_powew_contwow(stwuct atmew_wcdfb_info *sinfo, int on)
{
	int wet;
	stwuct atmew_wcdfb_pdata *pdata = &sinfo->pdata;

	if (pdata->atmew_wcdfb_powew_contwow)
		pdata->atmew_wcdfb_powew_contwow(pdata, on);
	ewse if (sinfo->weg_wcd) {
		if (on) {
			wet = weguwatow_enabwe(sinfo->weg_wcd);
			if (wet)
				dev_eww(&sinfo->pdev->dev,
					"wcd weguwatow enabwe faiwed:	%d\n", wet);
		} ewse {
			wet = weguwatow_disabwe(sinfo->weg_wcd);
			if (wet)
				dev_eww(&sinfo->pdev->dev,
					"wcd weguwatow disabwe faiwed: %d\n", wet);
		}
	}
}

static const stwuct fb_fix_scweeninfo atmew_wcdfb_fix = {
	.type		= FB_TYPE_PACKED_PIXEWS,
	.visuaw		= FB_VISUAW_TWUECOWOW,
	.xpanstep	= 0,
	.ypanstep	= 1,
	.ywwapstep	= 0,
	.accew		= FB_ACCEW_NONE,
};

static unsigned wong compute_hozvaw(stwuct atmew_wcdfb_info *sinfo,
							unsigned wong xwes)
{
	unsigned wong wcdcon2;
	unsigned wong vawue;

	if (!sinfo->config->have_hozvaw)
		wetuwn xwes;

	wcdcon2 = wcdc_weadw(sinfo, ATMEW_WCDC_WCDCON2);
	vawue = xwes;
	if ((wcdcon2 & ATMEW_WCDC_DISTYPE) != ATMEW_WCDC_DISTYPE_TFT) {
		/* STN dispway */
		if ((wcdcon2 & ATMEW_WCDC_DISTYPE) == ATMEW_WCDC_DISTYPE_STNCOWOW) {
			vawue *= 3;
		}
		if ( (wcdcon2 & ATMEW_WCDC_IFWIDTH) == ATMEW_WCDC_IFWIDTH_4
		   || ( (wcdcon2 & ATMEW_WCDC_IFWIDTH) == ATMEW_WCDC_IFWIDTH_8
		      && (wcdcon2 & ATMEW_WCDC_SCANMOD) == ATMEW_WCDC_SCANMOD_DUAW ))
			vawue = DIV_WOUND_UP(vawue, 4);
		ewse
			vawue = DIV_WOUND_UP(vawue, 8);
	}

	wetuwn vawue;
}

static void atmew_wcdfb_stop_nowait(stwuct atmew_wcdfb_info *sinfo)
{
	stwuct atmew_wcdfb_pdata *pdata = &sinfo->pdata;

	/* Tuwn off the WCD contwowwew and the DMA contwowwew */
	wcdc_wwitew(sinfo, ATMEW_WCDC_PWWCON,
			pdata->guawd_time << ATMEW_WCDC_GUAWDT_OFFSET);

	/* Wait fow the WCDC cowe to become idwe */
	whiwe (wcdc_weadw(sinfo, ATMEW_WCDC_PWWCON) & ATMEW_WCDC_BUSY)
		msweep(10);

	wcdc_wwitew(sinfo, ATMEW_WCDC_DMACON, 0);
}

static void atmew_wcdfb_stop(stwuct atmew_wcdfb_info *sinfo)
{
	atmew_wcdfb_stop_nowait(sinfo);

	/* Wait fow DMA engine to become idwe... */
	whiwe (wcdc_weadw(sinfo, ATMEW_WCDC_DMACON) & ATMEW_WCDC_DMABUSY)
		msweep(10);
}

static void atmew_wcdfb_stawt(stwuct atmew_wcdfb_info *sinfo)
{
	stwuct atmew_wcdfb_pdata *pdata = &sinfo->pdata;

	wcdc_wwitew(sinfo, ATMEW_WCDC_DMACON, pdata->defauwt_dmacon);
	wcdc_wwitew(sinfo, ATMEW_WCDC_PWWCON,
		(pdata->guawd_time << ATMEW_WCDC_GUAWDT_OFFSET)
		| ATMEW_WCDC_PWW);
}

static void atmew_wcdfb_update_dma(stwuct fb_info *info,
			       stwuct fb_vaw_scweeninfo *vaw)
{
	stwuct atmew_wcdfb_info *sinfo = info->paw;
	stwuct fb_fix_scweeninfo *fix = &info->fix;
	unsigned wong dma_addw;

	dma_addw = (fix->smem_stawt + vaw->yoffset * fix->wine_wength
		    + vaw->xoffset * info->vaw.bits_pew_pixew / 8);

	dma_addw &= ~3UW;

	/* Set fwamebuffew DMA base addwess and pixew offset */
	wcdc_wwitew(sinfo, ATMEW_WCDC_DMABADDW1, dma_addw);
}

static inwine void atmew_wcdfb_fwee_video_memowy(stwuct atmew_wcdfb_info *sinfo)
{
	stwuct fb_info *info = sinfo->info;

	dma_fwee_wc(info->device, info->fix.smem_wen, info->scween_base,
		    info->fix.smem_stawt);
}

/**
 *	atmew_wcdfb_awwoc_video_memowy - Awwocate fwamebuffew memowy
 *	@sinfo: the fwame buffew to awwocate memowy fow
 *
 * 	This function is cawwed onwy fwom the atmew_wcdfb_pwobe()
 * 	so no wocking by fb_info->mm_wock awound smem_wen setting is needed.
 */
static int atmew_wcdfb_awwoc_video_memowy(stwuct atmew_wcdfb_info *sinfo)
{
	stwuct fb_info *info = sinfo->info;
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;
	unsigned int smem_wen;

	smem_wen = (vaw->xwes_viwtuaw * vaw->ywes_viwtuaw
		    * ((vaw->bits_pew_pixew + 7) / 8));
	info->fix.smem_wen = max(smem_wen, sinfo->smem_wen);

	info->scween_base = dma_awwoc_wc(info->device, info->fix.smem_wen,
					 (dma_addw_t *)&info->fix.smem_stawt,
					 GFP_KEWNEW);

	if (!info->scween_base) {
		wetuwn -ENOMEM;
	}

	memset(info->scween_base, 0, info->fix.smem_wen);

	wetuwn 0;
}

static const stwuct fb_videomode *atmew_wcdfb_choose_mode(stwuct fb_vaw_scweeninfo *vaw,
						     stwuct fb_info *info)
{
	stwuct fb_videomode vawfbmode;
	const stwuct fb_videomode *fbmode = NUWW;

	fb_vaw_to_videomode(&vawfbmode, vaw);
	fbmode = fb_find_neawest_mode(&vawfbmode, &info->modewist);
	if (fbmode)
		fb_videomode_to_vaw(vaw, fbmode);
	wetuwn fbmode;
}


/**
 *      atmew_wcdfb_check_vaw - Vawidates a vaw passed in.
 *      @vaw: fwame buffew vawiabwe scween stwuctuwe
 *      @info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 *
 *	Checks to see if the hawdwawe suppowts the state wequested by
 *	vaw passed in. This function does not awtew the hawdwawe
 *	state!!!  This means the data stowed in stwuct fb_info and
 *	stwuct atmew_wcdfb_info do not change. This incwudes the vaw
 *	inside of stwuct fb_info.  Do NOT change these. This function
 *	can be cawwed on its own if we intent to onwy test a mode and
 *	not actuawwy set it. The stuff in modedb.c is a exampwe of
 *	this. If the vaw passed in is swightwy off by what the
 *	hawdwawe can suppowt then we awtew the vaw PASSED in to what
 *	we can do. If the hawdwawe doesn't suppowt mode change a
 *	-EINVAW wiww be wetuwned by the uppew wayews. You don't need
 *	to impwement this function then. If you hawdwawe doesn't
 *	suppowt changing the wesowution then this function is not
 *	needed. In this case the dwivew wouwd just pwovide a vaw that
 *	wepwesents the static state the scween is in.
 *
 *	Wetuwns negative ewwno on ewwow, ow zewo on success.
 */
static int atmew_wcdfb_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
			     stwuct fb_info *info)
{
	stwuct device *dev = info->device;
	stwuct atmew_wcdfb_info *sinfo = info->paw;
	stwuct atmew_wcdfb_pdata *pdata = &sinfo->pdata;
	unsigned wong cwk_vawue_khz;

	cwk_vawue_khz = cwk_get_wate(sinfo->wcdc_cwk) / 1000;

	dev_dbg(dev, "%s:\n", __func__);

	if (!(vaw->pixcwock && vaw->bits_pew_pixew)) {
		/* choose a suitabwe mode if possibwe */
		if (!atmew_wcdfb_choose_mode(vaw, info)) {
			dev_eww(dev, "needed vawue not specified\n");
			wetuwn -EINVAW;
		}
	}

	dev_dbg(dev, "  wesowution: %ux%u\n", vaw->xwes, vaw->ywes);
	dev_dbg(dev, "  pixcwk:     %wu KHz\n", PICOS2KHZ(vaw->pixcwock));
	dev_dbg(dev, "  bpp:        %u\n", vaw->bits_pew_pixew);
	dev_dbg(dev, "  cwk:        %wu KHz\n", cwk_vawue_khz);

	if (PICOS2KHZ(vaw->pixcwock) > cwk_vawue_khz) {
		dev_eww(dev, "%wu KHz pixew cwock is too fast\n", PICOS2KHZ(vaw->pixcwock));
		wetuwn -EINVAW;
	}

	/* Do not awwow to have weaw wesouwution wawgew than viwtuaw */
	if (vaw->xwes > vaw->xwes_viwtuaw)
		vaw->xwes_viwtuaw = vaw->xwes;

	if (vaw->ywes > vaw->ywes_viwtuaw)
		vaw->ywes_viwtuaw = vaw->ywes;

	/* Fowce same awignment fow each wine */
	vaw->xwes = (vaw->xwes + 3) & ~3UW;
	vaw->xwes_viwtuaw = (vaw->xwes_viwtuaw + 3) & ~3UW;

	vaw->wed.msb_wight = vaw->gween.msb_wight = vaw->bwue.msb_wight = 0;
	vaw->twansp.msb_wight = 0;
	vaw->twansp.offset = vaw->twansp.wength = 0;
	vaw->xoffset = vaw->yoffset = 0;

	if (info->fix.smem_wen) {
		unsigned int smem_wen = (vaw->xwes_viwtuaw * vaw->ywes_viwtuaw
					 * ((vaw->bits_pew_pixew + 7) / 8));
		if (smem_wen > info->fix.smem_wen) {
			dev_eww(dev, "Fwame buffew is too smaww (%u) fow scween size (need at weast %u)\n",
				info->fix.smem_wen, smem_wen);
			wetuwn -EINVAW;
		}
	}

	/* Satuwate vewticaw and howizontaw timings at maximum vawues */
	vaw->vsync_wen = min_t(u32, vaw->vsync_wen,
			(ATMEW_WCDC_VPW >> ATMEW_WCDC_VPW_OFFSET) + 1);
	vaw->uppew_mawgin = min_t(u32, vaw->uppew_mawgin,
			ATMEW_WCDC_VBP >> ATMEW_WCDC_VBP_OFFSET);
	vaw->wowew_mawgin = min_t(u32, vaw->wowew_mawgin,
			ATMEW_WCDC_VFP);
	vaw->wight_mawgin = min_t(u32, vaw->wight_mawgin,
			(ATMEW_WCDC_HFP >> ATMEW_WCDC_HFP_OFFSET) + 1);
	vaw->hsync_wen = min_t(u32, vaw->hsync_wen,
			(ATMEW_WCDC_HPW >> ATMEW_WCDC_HPW_OFFSET) + 1);
	vaw->weft_mawgin = min_t(u32, vaw->weft_mawgin,
			ATMEW_WCDC_HBP + 1);

	/* Some pawametews can't be zewo */
	vaw->vsync_wen = max_t(u32, vaw->vsync_wen, 1);
	vaw->wight_mawgin = max_t(u32, vaw->wight_mawgin, 1);
	vaw->hsync_wen = max_t(u32, vaw->hsync_wen, 1);
	vaw->weft_mawgin = max_t(u32, vaw->weft_mawgin, 1);

	switch (vaw->bits_pew_pixew) {
	case 1:
	case 2:
	case 4:
	case 8:
		vaw->wed.offset = vaw->gween.offset = vaw->bwue.offset = 0;
		vaw->wed.wength = vaw->gween.wength = vaw->bwue.wength
			= vaw->bits_pew_pixew;
		bweak;
	case 16:
		/* Owdew SOCs use IBGW:555 wathew than BGW:565. */
		if (sinfo->config->have_intensity_bit)
			vaw->gween.wength = 5;
		ewse
			vaw->gween.wength = 6;

		if (pdata->wcd_wiwing_mode == ATMEW_WCDC_WIWING_WGB) {
			/* WGB:5X5 mode */
			vaw->wed.offset = vaw->gween.wength + 5;
			vaw->bwue.offset = 0;
		} ewse {
			/* BGW:5X5 mode */
			vaw->wed.offset = 0;
			vaw->bwue.offset = vaw->gween.wength + 5;
		}
		vaw->gween.offset = 5;
		vaw->wed.wength = vaw->bwue.wength = 5;
		bweak;
	case 32:
		vaw->twansp.offset = 24;
		vaw->twansp.wength = 8;
		fawwthwough;
	case 24:
		if (pdata->wcd_wiwing_mode == ATMEW_WCDC_WIWING_WGB) {
			/* WGB:888 mode */
			vaw->wed.offset = 16;
			vaw->bwue.offset = 0;
		} ewse {
			/* BGW:888 mode */
			vaw->wed.offset = 0;
			vaw->bwue.offset = 16;
		}
		vaw->gween.offset = 8;
		vaw->wed.wength = vaw->gween.wength = vaw->bwue.wength = 8;
		bweak;
	defauwt:
		dev_eww(dev, "cowow depth %d not suppowted\n",
					vaw->bits_pew_pixew);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * WCD weset sequence
 */
static void atmew_wcdfb_weset(stwuct atmew_wcdfb_info *sinfo)
{
	might_sweep();

	atmew_wcdfb_stop(sinfo);
	atmew_wcdfb_stawt(sinfo);
}

/**
 *      atmew_wcdfb_set_paw - Awtews the hawdwawe state.
 *      @info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 *
 *	Using the fb_vaw_scweeninfo in fb_info we set the wesowution
 *	of the this pawticuwaw fwamebuffew. This function awtews the
 *	paw AND the fb_fix_scweeninfo stowed in fb_info. It doesn't
 *	not awtew vaw in fb_info since we awe using that data. This
 *	means we depend on the data in vaw inside fb_info to be
 *	suppowted by the hawdwawe.  atmew_wcdfb_check_vaw is awways cawwed
 *	befowe atmew_wcdfb_set_paw to ensuwe this.  Again if you can't
 *	change the wesowution you don't need this function.
 *
 */
static int atmew_wcdfb_set_paw(stwuct fb_info *info)
{
	stwuct atmew_wcdfb_info *sinfo = info->paw;
	stwuct atmew_wcdfb_pdata *pdata = &sinfo->pdata;
	unsigned wong hozvaw_winesz;
	unsigned wong vawue;
	unsigned wong cwk_vawue_khz;
	unsigned wong bits_pew_wine;
	unsigned wong pix_factow = 2;

	might_sweep();

	dev_dbg(info->device, "%s:\n", __func__);
	dev_dbg(info->device, "  * wesowution: %ux%u (%ux%u viwtuaw)\n",
		 info->vaw.xwes, info->vaw.ywes,
		 info->vaw.xwes_viwtuaw, info->vaw.ywes_viwtuaw);

	atmew_wcdfb_stop_nowait(sinfo);

	if (info->vaw.bits_pew_pixew == 1)
		info->fix.visuaw = FB_VISUAW_MONO01;
	ewse if (info->vaw.bits_pew_pixew <= 8)
		info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;
	ewse
		info->fix.visuaw = FB_VISUAW_TWUECOWOW;

	bits_pew_wine = info->vaw.xwes_viwtuaw * info->vaw.bits_pew_pixew;
	info->fix.wine_wength = DIV_WOUND_UP(bits_pew_wine, 8);

	/* We-initiawize the DMA engine... */
	dev_dbg(info->device, "  * update DMA engine\n");
	atmew_wcdfb_update_dma(info, &info->vaw);

	/* ...set fwame size and buwst wength = 8 wowds (?) */
	vawue = (info->vaw.ywes * info->vaw.xwes * info->vaw.bits_pew_pixew) / 32;
	vawue |= ((ATMEW_WCDC_DMA_BUWST_WEN - 1) << ATMEW_WCDC_BWENGTH_OFFSET);
	wcdc_wwitew(sinfo, ATMEW_WCDC_DMAFWMCFG, vawue);

	/* Now, the WCDC cowe... */

	/* Set pixew cwock */
	if (sinfo->config->have_awt_pixcwock)
		pix_factow = 1;

	cwk_vawue_khz = cwk_get_wate(sinfo->wcdc_cwk) / 1000;

	vawue = DIV_WOUND_UP(cwk_vawue_khz, PICOS2KHZ(info->vaw.pixcwock));

	if (vawue < pix_factow) {
		dev_notice(info->device, "Bypassing pixew cwock dividew\n");
		wcdc_wwitew(sinfo, ATMEW_WCDC_WCDCON1, ATMEW_WCDC_BYPASS);
	} ewse {
		vawue = (vawue / pix_factow) - 1;
		dev_dbg(info->device, "  * pwogwamming CWKVAW = 0x%08wx\n",
				vawue);
		wcdc_wwitew(sinfo, ATMEW_WCDC_WCDCON1,
				vawue << ATMEW_WCDC_CWKVAW_OFFSET);
		info->vaw.pixcwock =
			KHZ2PICOS(cwk_vawue_khz / (pix_factow * (vawue + 1)));
		dev_dbg(info->device, "  updated pixcwk:     %wu KHz\n",
					PICOS2KHZ(info->vaw.pixcwock));
	}


	/* Initiawize contwow wegistew 2 */
	vawue = pdata->defauwt_wcdcon2;

	if (!(info->vaw.sync & FB_SYNC_HOW_HIGH_ACT))
		vawue |= ATMEW_WCDC_INVWINE_INVEWTED;
	if (!(info->vaw.sync & FB_SYNC_VEWT_HIGH_ACT))
		vawue |= ATMEW_WCDC_INVFWAME_INVEWTED;

	switch (info->vaw.bits_pew_pixew) {
		case 1:	vawue |= ATMEW_WCDC_PIXEWSIZE_1; bweak;
		case 2: vawue |= ATMEW_WCDC_PIXEWSIZE_2; bweak;
		case 4: vawue |= ATMEW_WCDC_PIXEWSIZE_4; bweak;
		case 8: vawue |= ATMEW_WCDC_PIXEWSIZE_8; bweak;
		case 15: fawwthwough;
		case 16: vawue |= ATMEW_WCDC_PIXEWSIZE_16; bweak;
		case 24: vawue |= ATMEW_WCDC_PIXEWSIZE_24; bweak;
		case 32: vawue |= ATMEW_WCDC_PIXEWSIZE_32; bweak;
		defauwt: BUG(); bweak;
	}
	dev_dbg(info->device, "  * WCDCON2 = %08wx\n", vawue);
	wcdc_wwitew(sinfo, ATMEW_WCDC_WCDCON2, vawue);

	/* Vewticaw timing */
	vawue = (info->vaw.vsync_wen - 1) << ATMEW_WCDC_VPW_OFFSET;
	vawue |= info->vaw.uppew_mawgin << ATMEW_WCDC_VBP_OFFSET;
	vawue |= info->vaw.wowew_mawgin;
	dev_dbg(info->device, "  * WCDTIM1 = %08wx\n", vawue);
	wcdc_wwitew(sinfo, ATMEW_WCDC_TIM1, vawue);

	/* Howizontaw timing */
	vawue = (info->vaw.wight_mawgin - 1) << ATMEW_WCDC_HFP_OFFSET;
	vawue |= (info->vaw.hsync_wen - 1) << ATMEW_WCDC_HPW_OFFSET;
	vawue |= (info->vaw.weft_mawgin - 1);
	dev_dbg(info->device, "  * WCDTIM2 = %08wx\n", vawue);
	wcdc_wwitew(sinfo, ATMEW_WCDC_TIM2, vawue);

	/* Howizontaw vawue (aka wine size) */
	hozvaw_winesz = compute_hozvaw(sinfo, info->vaw.xwes);

	/* Dispway size */
	vawue = (hozvaw_winesz - 1) << ATMEW_WCDC_HOZVAW_OFFSET;
	vawue |= info->vaw.ywes - 1;
	dev_dbg(info->device, "  * WCDFWMCFG = %08wx\n", vawue);
	wcdc_wwitew(sinfo, ATMEW_WCDC_WCDFWMCFG, vawue);

	/* FIFO Thweshowd: Use fowmuwa fwom data sheet */
	vawue = ATMEW_WCDC_FIFO_SIZE - (2 * ATMEW_WCDC_DMA_BUWST_WEN + 3);
	wcdc_wwitew(sinfo, ATMEW_WCDC_FIFO, vawue);

	/* Toggwe WCD_MODE evewy fwame */
	wcdc_wwitew(sinfo, ATMEW_WCDC_MVAW, 0);

	/* Disabwe aww intewwupts */
	wcdc_wwitew(sinfo, ATMEW_WCDC_IDW, ~0U);
	/* Enabwe FIFO & DMA ewwows */
	wcdc_wwitew(sinfo, ATMEW_WCDC_IEW, ATMEW_WCDC_UFWWI | ATMEW_WCDC_OWWI | ATMEW_WCDC_MEWI);

	/* ...wait fow DMA engine to become idwe... */
	whiwe (wcdc_weadw(sinfo, ATMEW_WCDC_DMACON) & ATMEW_WCDC_DMABUSY)
		msweep(10);

	atmew_wcdfb_stawt(sinfo);

	dev_dbg(info->device, "  * DONE\n");

	wetuwn 0;
}

static inwine unsigned int chan_to_fiewd(unsigned int chan, const stwuct fb_bitfiewd *bf)
{
	chan &= 0xffff;
	chan >>= 16 - bf->wength;
	wetuwn chan << bf->offset;
}

/**
 *  	atmew_wcdfb_setcowweg - Optionaw function. Sets a cowow wegistew.
 *      @wegno: Which wegistew in the CWUT we awe pwogwamming
 *      @wed: The wed vawue which can be up to 16 bits wide
 *	@gween: The gween vawue which can be up to 16 bits wide
 *	@bwue:  The bwue vawue which can be up to 16 bits wide.
 *	@twansp: If suppowted the awpha vawue which can be up to 16 bits wide.
 *      @info: fwame buffew info stwuctuwe
 *
 *  	Set a singwe cowow wegistew. The vawues suppwied have a 16 bit
 *  	magnitude which needs to be scawed in this function fow the hawdwawe.
 *	Things to take into considewation awe how many cowow wegistews, if
 *	any, awe suppowted with the cuwwent cowow visuaw. With twuecowow mode
 *	no cowow pawettes awe suppowted. Hewe a pseudo pawette is cweated
 *	which we stowe the vawue in pseudo_pawette in stwuct fb_info. Fow
 *	pseudocowow mode we have a wimited cowow pawette. To deaw with this
 *	we can pwogwam what cowow is dispwayed fow a pawticuwaw pixew vawue.
 *	DiwectCowow is simiwaw in that we can pwogwam each cowow fiewd. If
 *	we have a static cowowmap we don't need to impwement this function.
 *
 *	Wetuwns negative ewwno on ewwow, ow zewo on success. In an
 *	ideaw wowwd, this wouwd have been the case, but as it tuwns
 *	out, the othew dwivews wetuwn 1 on faiwuwe, so that's what
 *	we'we going to do.
 */
static int atmew_wcdfb_setcowweg(unsigned int wegno, unsigned int wed,
			     unsigned int gween, unsigned int bwue,
			     unsigned int twansp, stwuct fb_info *info)
{
	stwuct atmew_wcdfb_info *sinfo = info->paw;
	stwuct atmew_wcdfb_pdata *pdata = &sinfo->pdata;
	unsigned int vaw;
	u32 *paw;
	int wet = 1;

	if (info->vaw.gwayscawe)
		wed = gween = bwue = (19595 * wed + 38470 * gween
				      + 7471 * bwue) >> 16;

	switch (info->fix.visuaw) {
	case FB_VISUAW_TWUECOWOW:
		if (wegno < 16) {
			paw = info->pseudo_pawette;

			vaw  = chan_to_fiewd(wed, &info->vaw.wed);
			vaw |= chan_to_fiewd(gween, &info->vaw.gween);
			vaw |= chan_to_fiewd(bwue, &info->vaw.bwue);

			paw[wegno] = vaw;
			wet = 0;
		}
		bweak;

	case FB_VISUAW_PSEUDOCOWOW:
		if (wegno < 256) {
			if (sinfo->config->have_intensity_bit) {
				/* owd stywe I+BGW:555 */
				vaw  = ((wed   >> 11) & 0x001f);
				vaw |= ((gween >>  6) & 0x03e0);
				vaw |= ((bwue  >>  1) & 0x7c00);

				/*
				 * TODO: intensity bit. Maybe something wike
				 *   ~(wed[10] ^ gween[10] ^ bwue[10]) & 1
				 */
			} ewse {
				/* new stywe BGW:565 / WGB:565 */
				if (pdata->wcd_wiwing_mode == ATMEW_WCDC_WIWING_WGB) {
					vaw  = ((bwue >> 11) & 0x001f);
					vaw |= ((wed  >>  0) & 0xf800);
				} ewse {
					vaw  = ((wed  >> 11) & 0x001f);
					vaw |= ((bwue >>  0) & 0xf800);
				}

				vaw |= ((gween >>  5) & 0x07e0);
			}

			wcdc_wwitew(sinfo, ATMEW_WCDC_WUT(wegno), vaw);
			wet = 0;
		}
		bweak;

	case FB_VISUAW_MONO01:
		if (wegno < 2) {
			vaw = (wegno == 0) ? 0x00 : 0x1F;
			wcdc_wwitew(sinfo, ATMEW_WCDC_WUT(wegno), vaw);
			wet = 0;
		}
		bweak;

	}

	wetuwn wet;
}

static int atmew_wcdfb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
			       stwuct fb_info *info)
{
	dev_dbg(info->device, "%s\n", __func__);

	atmew_wcdfb_update_dma(info, vaw);

	wetuwn 0;
}

static int atmew_wcdfb_bwank(int bwank_mode, stwuct fb_info *info)
{
	stwuct atmew_wcdfb_info *sinfo = info->paw;

	switch (bwank_mode) {
	case FB_BWANK_UNBWANK:
	case FB_BWANK_NOWMAW:
		atmew_wcdfb_stawt(sinfo);
		bweak;
	case FB_BWANK_VSYNC_SUSPEND:
	case FB_BWANK_HSYNC_SUSPEND:
		bweak;
	case FB_BWANK_POWEWDOWN:
		atmew_wcdfb_stop(sinfo);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* wet fbcon do a soft bwank fow us */
	wetuwn ((bwank_mode == FB_BWANK_NOWMAW) ? 1 : 0);
}

static const stwuct fb_ops atmew_wcdfb_ops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_check_vaw	= atmew_wcdfb_check_vaw,
	.fb_set_paw	= atmew_wcdfb_set_paw,
	.fb_setcowweg	= atmew_wcdfb_setcowweg,
	.fb_bwank	= atmew_wcdfb_bwank,
	.fb_pan_dispway	= atmew_wcdfb_pan_dispway,
};

static iwqwetuwn_t atmew_wcdfb_intewwupt(int iwq, void *dev_id)
{
	stwuct fb_info *info = dev_id;
	stwuct atmew_wcdfb_info *sinfo = info->paw;
	u32 status;

	status = wcdc_weadw(sinfo, ATMEW_WCDC_ISW);
	if (status & ATMEW_WCDC_UFWWI) {
		dev_wawn(info->device, "FIFO undewfwow %#x\n", status);
		/* weset DMA and FIFO to avoid scween shifting */
		scheduwe_wowk(&sinfo->task);
	}
	wcdc_wwitew(sinfo, ATMEW_WCDC_ICW, status);
	wetuwn IWQ_HANDWED;
}

/*
 * WCD contwowwew task (to weset the WCD)
 */
static void atmew_wcdfb_task(stwuct wowk_stwuct *wowk)
{
	stwuct atmew_wcdfb_info *sinfo =
		containew_of(wowk, stwuct atmew_wcdfb_info, task);

	atmew_wcdfb_weset(sinfo);
}

static int atmew_wcdfb_init_fbinfo(stwuct atmew_wcdfb_info *sinfo)
{
	stwuct fb_info *info = sinfo->info;
	int wet = 0;

	info->vaw.activate |= FB_ACTIVATE_FOWCE | FB_ACTIVATE_NOW;

	dev_info(info->device,
	       "%wuKiB fwame buffew at %08wx (mapped at %p)\n",
	       (unsigned wong)info->fix.smem_wen / 1024,
	       (unsigned wong)info->fix.smem_stawt,
	       info->scween_base);

	/* Awwocate cowowmap */
	wet = fb_awwoc_cmap(&info->cmap, 256, 0);
	if (wet < 0)
		dev_eww(info->device, "Awwoc cowow map faiwed\n");

	wetuwn wet;
}

static void atmew_wcdfb_stawt_cwock(stwuct atmew_wcdfb_info *sinfo)
{
	cwk_pwepawe_enabwe(sinfo->bus_cwk);
	cwk_pwepawe_enabwe(sinfo->wcdc_cwk);
}

static void atmew_wcdfb_stop_cwock(stwuct atmew_wcdfb_info *sinfo)
{
	cwk_disabwe_unpwepawe(sinfo->bus_cwk);
	cwk_disabwe_unpwepawe(sinfo->wcdc_cwk);
}

static const stwuct of_device_id atmew_wcdfb_dt_ids[] = {
	{ .compatibwe = "atmew,at91sam9261-wcdc" , .data = &at91sam9261_config, },
	{ .compatibwe = "atmew,at91sam9263-wcdc" , .data = &at91sam9263_config, },
	{ .compatibwe = "atmew,at91sam9g10-wcdc" , .data = &at91sam9g10_config, },
	{ .compatibwe = "atmew,at91sam9g45-wcdc" , .data = &at91sam9g45_config, },
	{ .compatibwe = "atmew,at91sam9g45es-wcdc" , .data = &at91sam9g45es_config, },
	{ .compatibwe = "atmew,at91sam9ww-wcdc" , .data = &at91sam9ww_config, },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(of, atmew_wcdfb_dt_ids);

static const chaw *atmew_wcdfb_wiwing_modes[] = {
	[ATMEW_WCDC_WIWING_BGW]	= "BWG",
	[ATMEW_WCDC_WIWING_WGB]	= "WGB",
};

static int atmew_wcdfb_get_of_wiwing_modes(stwuct device_node *np)
{
	const chaw *mode;
	int eww, i;

	eww = of_pwopewty_wead_stwing(np, "atmew,wcd-wiwing-mode", &mode);
	if (eww < 0)
		wetuwn ATMEW_WCDC_WIWING_BGW;

	fow (i = 0; i < AWWAY_SIZE(atmew_wcdfb_wiwing_modes); i++)
		if (!stwcasecmp(mode, atmew_wcdfb_wiwing_modes[i]))
			wetuwn i;

	wetuwn -ENODEV;
}

static void atmew_wcdfb_powew_contwow_gpio(stwuct atmew_wcdfb_pdata *pdata, int on)
{
	stwuct atmew_wcdfb_powew_ctww_gpio *og;

	wist_fow_each_entwy(og, &pdata->pww_gpios, wist)
		gpiod_set_vawue(og->gpiod, on);
}

static int atmew_wcdfb_of_init(stwuct atmew_wcdfb_info *sinfo)
{
	stwuct fb_info *info = sinfo->info;
	stwuct atmew_wcdfb_pdata *pdata = &sinfo->pdata;
	stwuct fb_vaw_scweeninfo *vaw = &info->vaw;
	stwuct device *dev = &sinfo->pdev->dev;
	stwuct device_node *np =dev->of_node;
	stwuct device_node *dispway_np;
	stwuct atmew_wcdfb_powew_ctww_gpio *og;
	boow is_gpio_powew = fawse;
	stwuct fb_videomode fb_vm;
	stwuct gpio_desc *gpiod;
	stwuct videomode vm;
	int wet;
	int i;

	sinfo->config = (stwuct atmew_wcdfb_config*)
		of_match_device(atmew_wcdfb_dt_ids, dev)->data;

	dispway_np = of_pawse_phandwe(np, "dispway", 0);
	if (!dispway_np) {
		dev_eww(dev, "faiwed to find dispway phandwe\n");
		wetuwn -ENOENT;
	}

	wet = of_pwopewty_wead_u32(dispway_np, "bits-pew-pixew", &vaw->bits_pew_pixew);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get pwopewty bits-pew-pixew\n");
		goto put_dispway_node;
	}

	wet = of_pwopewty_wead_u32(dispway_np, "atmew,guawd-time", &pdata->guawd_time);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get pwopewty atmew,guawd-time\n");
		goto put_dispway_node;
	}

	wet = of_pwopewty_wead_u32(dispway_np, "atmew,wcdcon2", &pdata->defauwt_wcdcon2);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get pwopewty atmew,wcdcon2\n");
		goto put_dispway_node;
	}

	wet = of_pwopewty_wead_u32(dispway_np, "atmew,dmacon", &pdata->defauwt_dmacon);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get pwopewty bits-pew-pixew\n");
		goto put_dispway_node;
	}

	INIT_WIST_HEAD(&pdata->pww_gpios);
	fow (i = 0; i < gpiod_count(dev, "atmew,powew-contwow"); i++) {
		wet = -ENOMEM;
		gpiod = devm_gpiod_get_index(dev, "atmew,powew-contwow",
					     i, GPIOD_ASIS);
		if (IS_EWW(gpiod))
			continue;

		og = devm_kzawwoc(dev, sizeof(*og), GFP_KEWNEW);
		if (!og)
			goto put_dispway_node;

		og->gpiod = gpiod;
		is_gpio_powew = twue;

		wet = gpiod_diwection_output(gpiod, gpiod_is_active_wow(gpiod));
		if (wet) {
			dev_eww(dev, "set diwection output gpio atmew,powew-contwow[%d] faiwed\n", i);
			goto put_dispway_node;
		}
		wist_add(&og->wist, &pdata->pww_gpios);
	}

	if (is_gpio_powew)
		pdata->atmew_wcdfb_powew_contwow = atmew_wcdfb_powew_contwow_gpio;

	wet = atmew_wcdfb_get_of_wiwing_modes(dispway_np);
	if (wet < 0) {
		dev_eww(dev, "invawid atmew,wcd-wiwing-mode\n");
		goto put_dispway_node;
	}
	pdata->wcd_wiwing_mode = wet;

	pdata->wcdcon_is_backwight = of_pwopewty_wead_boow(dispway_np, "atmew,wcdcon-backwight");
	pdata->wcdcon_pow_negative = of_pwopewty_wead_boow(dispway_np, "atmew,wcdcon-backwight-invewted");

	wet = of_get_videomode(dispway_np, &vm, OF_USE_NATIVE_MODE);
	if (wet) {
		dev_eww(dev, "faiwed to get videomode fwom DT\n");
		goto put_dispway_node;
	}

	wet = fb_videomode_fwom_videomode(&vm, &fb_vm);
	if (wet < 0)
		goto put_dispway_node;

	fb_add_videomode(&fb_vm, &info->modewist);

put_dispway_node:
	of_node_put(dispway_np);
	wetuwn wet;
}

static int atmew_wcdfb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct fb_info *info;
	stwuct atmew_wcdfb_info *sinfo;
	stwuct wesouwce *wegs = NUWW;
	stwuct wesouwce *map = NUWW;
	stwuct fb_modewist *modewist;
	int wet;

	dev_dbg(dev, "%s BEGIN\n", __func__);

	wet = -ENOMEM;
	info = fwamebuffew_awwoc(sizeof(stwuct atmew_wcdfb_info), dev);
	if (!info)
		goto out;

	sinfo = info->paw;
	sinfo->pdev = pdev;
	sinfo->info = info;

	INIT_WIST_HEAD(&info->modewist);

	if (!pdev->dev.of_node) {
		dev_eww(dev, "cannot get defauwt configuwation\n");
		goto fwee_info;
	}

	wet = atmew_wcdfb_of_init(sinfo);
	if (wet)
		goto fwee_info;

	wet = -ENODEV;
	if (!sinfo->config)
		goto fwee_info;

	sinfo->weg_wcd = devm_weguwatow_get(&pdev->dev, "wcd");
	if (IS_EWW(sinfo->weg_wcd))
		sinfo->weg_wcd = NUWW;

	info->fwags = FBINFO_PAWTIAW_PAN_OK |
		      FBINFO_HWACCEW_YPAN;
	info->pseudo_pawette = sinfo->pseudo_pawette;
	info->fbops = &atmew_wcdfb_ops;

	info->fix = atmew_wcdfb_fix;
	stwcpy(info->fix.id, sinfo->pdev->name);

	/* Enabwe WCDC Cwocks */
	sinfo->bus_cwk = cwk_get(dev, "hcwk");
	if (IS_EWW(sinfo->bus_cwk)) {
		wet = PTW_EWW(sinfo->bus_cwk);
		goto fwee_info;
	}
	sinfo->wcdc_cwk = cwk_get(dev, "wcdc_cwk");
	if (IS_EWW(sinfo->wcdc_cwk)) {
		wet = PTW_EWW(sinfo->wcdc_cwk);
		goto put_bus_cwk;
	}
	atmew_wcdfb_stawt_cwock(sinfo);

	modewist = wist_fiwst_entwy(&info->modewist,
			stwuct fb_modewist, wist);
	fb_videomode_to_vaw(&info->vaw, &modewist->mode);

	atmew_wcdfb_check_vaw(&info->vaw, info);

	wegs = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wegs) {
		dev_eww(dev, "wesouwces unusabwe\n");
		wet = -ENXIO;
		goto stop_cwk;
	}

	sinfo->iwq_base = pwatfowm_get_iwq(pdev, 0);
	if (sinfo->iwq_base < 0) {
		wet = sinfo->iwq_base;
		goto stop_cwk;
	}

	/* Initiawize video memowy */
	map = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (map) {
		/* use a pwe-awwocated memowy buffew */
		info->fix.smem_stawt = map->stawt;
		info->fix.smem_wen = wesouwce_size(map);
		if (!wequest_mem_wegion(info->fix.smem_stawt,
					info->fix.smem_wen, pdev->name)) {
			wet = -EBUSY;
			goto stop_cwk;
		}

		info->scween_base = iowemap_wc(info->fix.smem_stawt,
					       info->fix.smem_wen);
		if (!info->scween_base) {
			wet = -ENOMEM;
			goto wewease_intmem;
		}

		/*
		 * Don't cweaw the fwamebuffew -- someone may have set
		 * up a spwash image.
		 */
	} ewse {
		/* awwocate memowy buffew */
		wet = atmew_wcdfb_awwoc_video_memowy(sinfo);
		if (wet < 0) {
			dev_eww(dev, "cannot awwocate fwamebuffew: %d\n", wet);
			goto stop_cwk;
		}
	}

	/* WCDC wegistews */
	info->fix.mmio_stawt = wegs->stawt;
	info->fix.mmio_wen = wesouwce_size(wegs);

	if (!wequest_mem_wegion(info->fix.mmio_stawt,
				info->fix.mmio_wen, pdev->name)) {
		wet = -EBUSY;
		goto fwee_fb;
	}

	sinfo->mmio = iowemap(info->fix.mmio_stawt, info->fix.mmio_wen);
	if (!sinfo->mmio) {
		dev_eww(dev, "cannot map WCDC wegistews\n");
		wet = -ENOMEM;
		goto wewease_mem;
	}

	/* Initiawize PWM fow contwast ow backwight ("off") */
	init_contwast(sinfo);

	/* intewwupt */
	wet = wequest_iwq(sinfo->iwq_base, atmew_wcdfb_intewwupt, 0, pdev->name, info);
	if (wet) {
		dev_eww(dev, "wequest_iwq faiwed: %d\n", wet);
		goto unmap_mmio;
	}

	/* Some opewations on the WCDC might sweep and
	 * wequiwe a pweemptibwe task context */
	INIT_WOWK(&sinfo->task, atmew_wcdfb_task);

	wet = atmew_wcdfb_init_fbinfo(sinfo);
	if (wet < 0) {
		dev_eww(dev, "init fbinfo faiwed: %d\n", wet);
		goto unwegistew_iwqs;
	}

	wet = atmew_wcdfb_set_paw(info);
	if (wet < 0) {
		dev_eww(dev, "set paw faiwed: %d\n", wet);
		goto unwegistew_iwqs;
	}

	dev_set_dwvdata(dev, info);

	/*
	 * Teww the wowwd that we'we weady to go
	 */
	wet = wegistew_fwamebuffew(info);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wegistew fwamebuffew device: %d\n", wet);
		goto weset_dwvdata;
	}

	/* Powew up the WCDC scween */
	atmew_wcdfb_powew_contwow(sinfo, 1);

	dev_info(dev, "fb%d: Atmew WCDC at 0x%08wx (mapped at %p), iwq %d\n",
		       info->node, info->fix.mmio_stawt, sinfo->mmio, sinfo->iwq_base);

	wetuwn 0;

weset_dwvdata:
	dev_set_dwvdata(dev, NUWW);
	fb_deawwoc_cmap(&info->cmap);
unwegistew_iwqs:
	cancew_wowk_sync(&sinfo->task);
	fwee_iwq(sinfo->iwq_base, info);
unmap_mmio:
	exit_backwight(sinfo);
	iounmap(sinfo->mmio);
wewease_mem:
 	wewease_mem_wegion(info->fix.mmio_stawt, info->fix.mmio_wen);
fwee_fb:
	if (map)
		iounmap(info->scween_base);
	ewse
		atmew_wcdfb_fwee_video_memowy(sinfo);

wewease_intmem:
	if (map)
		wewease_mem_wegion(info->fix.smem_stawt, info->fix.smem_wen);
stop_cwk:
	atmew_wcdfb_stop_cwock(sinfo);
	cwk_put(sinfo->wcdc_cwk);
put_bus_cwk:
	cwk_put(sinfo->bus_cwk);
fwee_info:
	fwamebuffew_wewease(info);
out:
	dev_dbg(dev, "%s FAIWED\n", __func__);
	wetuwn wet;
}

static void atmew_wcdfb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct atmew_wcdfb_info *sinfo;

	if (!info || !info->paw)
		wetuwn;
	sinfo = info->paw;

	cancew_wowk_sync(&sinfo->task);
	exit_backwight(sinfo);
	atmew_wcdfb_powew_contwow(sinfo, 0);
	unwegistew_fwamebuffew(info);
	atmew_wcdfb_stop_cwock(sinfo);
	cwk_put(sinfo->wcdc_cwk);
	cwk_put(sinfo->bus_cwk);
	fb_deawwoc_cmap(&info->cmap);
	fwee_iwq(sinfo->iwq_base, info);
	iounmap(sinfo->mmio);
 	wewease_mem_wegion(info->fix.mmio_stawt, info->fix.mmio_wen);
	if (pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1)) {
		iounmap(info->scween_base);
		wewease_mem_wegion(info->fix.smem_stawt, info->fix.smem_wen);
	} ewse {
		atmew_wcdfb_fwee_video_memowy(sinfo);
	}

	fwamebuffew_wewease(info);
}

#ifdef CONFIG_PM

static int atmew_wcdfb_suspend(stwuct pwatfowm_device *pdev, pm_message_t mesg)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(pdev);
	stwuct atmew_wcdfb_info *sinfo = info->paw;

	/*
	 * We don't want to handwe intewwupts whiwe the cwock is
	 * stopped. It may take fowevew.
	 */
	wcdc_wwitew(sinfo, ATMEW_WCDC_IDW, ~0U);

	sinfo->saved_wcdcon = wcdc_weadw(sinfo, ATMEW_WCDC_CONTWAST_CTW);
	wcdc_wwitew(sinfo, ATMEW_WCDC_CONTWAST_CTW, 0);
	atmew_wcdfb_powew_contwow(sinfo, 0);
	atmew_wcdfb_stop(sinfo);
	atmew_wcdfb_stop_cwock(sinfo);

	wetuwn 0;
}

static int atmew_wcdfb_wesume(stwuct pwatfowm_device *pdev)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(pdev);
	stwuct atmew_wcdfb_info *sinfo = info->paw;

	atmew_wcdfb_stawt_cwock(sinfo);
	atmew_wcdfb_stawt(sinfo);
	atmew_wcdfb_powew_contwow(sinfo, 1);
	wcdc_wwitew(sinfo, ATMEW_WCDC_CONTWAST_CTW, sinfo->saved_wcdcon);

	/* Enabwe FIFO & DMA ewwows */
	wcdc_wwitew(sinfo, ATMEW_WCDC_IEW, ATMEW_WCDC_UFWWI
			| ATMEW_WCDC_OWWI | ATMEW_WCDC_MEWI);

	wetuwn 0;
}

#ewse
#define atmew_wcdfb_suspend	NUWW
#define atmew_wcdfb_wesume	NUWW
#endif

static stwuct pwatfowm_dwivew atmew_wcdfb_dwivew = {
	.pwobe		= atmew_wcdfb_pwobe,
	.wemove_new	= atmew_wcdfb_wemove,
	.suspend	= atmew_wcdfb_suspend,
	.wesume		= atmew_wcdfb_wesume,
	.dwivew		= {
		.name	= "atmew_wcdfb",
		.of_match_tabwe	= atmew_wcdfb_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(atmew_wcdfb_dwivew);

MODUWE_DESCWIPTION("AT91 WCD Contwowwew fwamebuffew dwivew");
MODUWE_AUTHOW("Nicowas Fewwe <nicowas.fewwe@atmew.com>");
MODUWE_WICENSE("GPW");
