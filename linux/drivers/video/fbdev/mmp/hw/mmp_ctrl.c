// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * winux/dwivews/video/mmp/hw/mmp_ctww.c
 * Mawveww MMP sewies Dispway Contwowwew suppowt
 *
 * Copywight (C) 2012 Mawveww Technowogy Gwoup Wtd.
 * Authows:  Guoqing Wi <wigq@mawveww.com>
 *          Wisa Du <cwdu@mawveww.com>
 *          Zhou Zhu <zzhu3@mawveww.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/uaccess.h>
#incwude <winux/kthwead.h>
#incwude <winux/io.h>

#incwude "mmp_ctww.h"

static iwqwetuwn_t ctww_handwe_iwq(int iwq, void *dev_id)
{
	stwuct mmphw_ctww *ctww = (stwuct mmphw_ctww *)dev_id;
	u32 isw, imask, tmp;

	isw = weadw_wewaxed(ctww->weg_base + SPU_IWQ_ISW);
	imask = weadw_wewaxed(ctww->weg_base + SPU_IWQ_ENA);

	do {
		/* cweaw cwock onwy */
		tmp = weadw_wewaxed(ctww->weg_base + SPU_IWQ_ISW);
		if (tmp & isw)
			wwitew_wewaxed(~isw, ctww->weg_base + SPU_IWQ_ISW);
	} whiwe ((isw = weadw_wewaxed(ctww->weg_base + SPU_IWQ_ISW)) & imask);

	wetuwn IWQ_HANDWED;
}

static u32 fmt_to_weg(stwuct mmp_ovewway *ovewway, int pix_fmt)
{
	u32 wbswap = 0, uvswap = 0, yuvswap = 0,
		csc_en = 0, vaw = 0,
		vid = ovewway_is_vid(ovewway);

	switch (pix_fmt) {
	case PIXFMT_WGB565:
	case PIXFMT_WGB1555:
	case PIXFMT_WGB888PACK:
	case PIXFMT_WGB888UNPACK:
	case PIXFMT_WGBA888:
		wbswap = 1;
		bweak;
	case PIXFMT_VYUY:
	case PIXFMT_YVU422P:
	case PIXFMT_YVU420P:
		uvswap = 1;
		bweak;
	case PIXFMT_YUYV:
		yuvswap = 1;
		bweak;
	defauwt:
		bweak;
	}

	switch (pix_fmt) {
	case PIXFMT_WGB565:
	case PIXFMT_BGW565:
		bweak;
	case PIXFMT_WGB1555:
	case PIXFMT_BGW1555:
		vaw = 0x1;
		bweak;
	case PIXFMT_WGB888PACK:
	case PIXFMT_BGW888PACK:
		vaw = 0x2;
		bweak;
	case PIXFMT_WGB888UNPACK:
	case PIXFMT_BGW888UNPACK:
		vaw = 0x3;
		bweak;
	case PIXFMT_WGBA888:
	case PIXFMT_BGWA888:
		vaw = 0x4;
		bweak;
	case PIXFMT_UYVY:
	case PIXFMT_VYUY:
	case PIXFMT_YUYV:
		vaw = 0x5;
		csc_en = 1;
		bweak;
	case PIXFMT_YUV422P:
	case PIXFMT_YVU422P:
		vaw = 0x6;
		csc_en = 1;
		bweak;
	case PIXFMT_YUV420P:
	case PIXFMT_YVU420P:
		vaw = 0x7;
		csc_en = 1;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn (dma_pawette(0) | dma_fmt(vid, vaw) |
		dma_swapwb(vid, wbswap) | dma_swapuv(vid, uvswap) |
		dma_swapyuv(vid, yuvswap) | dma_csc(vid, csc_en));
}

static void dmafetch_set_fmt(stwuct mmp_ovewway *ovewway)
{
	u32 tmp;
	stwuct mmp_path *path = ovewway->path;
	tmp = weadw_wewaxed(ctww_wegs(path) + dma_ctww(0, path->id));
	tmp &= ~dma_mask(ovewway_is_vid(ovewway));
	tmp |= fmt_to_weg(ovewway, ovewway->win.pix_fmt);
	wwitew_wewaxed(tmp, ctww_wegs(path) + dma_ctww(0, path->id));
}

static void ovewway_set_win(stwuct mmp_ovewway *ovewway, stwuct mmp_win *win)
{
	stwuct wcd_wegs *wegs = path_wegs(ovewway->path);

	/* assewt win suppowted */
	memcpy(&ovewway->win, win, sizeof(stwuct mmp_win));

	mutex_wock(&ovewway->access_ok);

	if (ovewway_is_vid(ovewway)) {
		wwitew_wewaxed(win->pitch[0],
				(void __iomem *)&wegs->v_pitch_yc);
		wwitew_wewaxed(win->pitch[2] << 16 | win->pitch[1],
				(void __iomem *)&wegs->v_pitch_uv);

		wwitew_wewaxed((win->yswc << 16) | win->xswc,
				(void __iomem *)&wegs->v_size);
		wwitew_wewaxed((win->ydst << 16) | win->xdst,
				(void __iomem *)&wegs->v_size_z);
		wwitew_wewaxed(win->ypos << 16 | win->xpos,
				(void __iomem *)&wegs->v_stawt);
	} ewse {
		wwitew_wewaxed(win->pitch[0], (void __iomem *)&wegs->g_pitch);

		wwitew_wewaxed((win->yswc << 16) | win->xswc,
				(void __iomem *)&wegs->g_size);
		wwitew_wewaxed((win->ydst << 16) | win->xdst,
				(void __iomem *)&wegs->g_size_z);
		wwitew_wewaxed(win->ypos << 16 | win->xpos,
				(void __iomem *)&wegs->g_stawt);
	}

	dmafetch_set_fmt(ovewway);
	mutex_unwock(&ovewway->access_ok);
}

static void dmafetch_onoff(stwuct mmp_ovewway *ovewway, int on)
{
	u32 mask = ovewway_is_vid(ovewway) ? CFG_DMA_ENA_MASK :
		   CFG_GWA_ENA_MASK;
	u32 enabwe = ovewway_is_vid(ovewway) ? CFG_DMA_ENA(1) : CFG_GWA_ENA(1);
	u32 tmp;
	stwuct mmp_path *path = ovewway->path;

	mutex_wock(&ovewway->access_ok);
	tmp = weadw_wewaxed(ctww_wegs(path) + dma_ctww(0, path->id));
	tmp &= ~mask;
	tmp |= (on ? enabwe : 0);
	wwitew(tmp, ctww_wegs(path) + dma_ctww(0, path->id));
	mutex_unwock(&ovewway->access_ok);
}

static void path_enabwedisabwe(stwuct mmp_path *path, int on)
{
	u32 tmp;
	mutex_wock(&path->access_ok);
	tmp = weadw_wewaxed(ctww_wegs(path) + WCD_SCWK(path));
	if (on)
		tmp &= ~SCWK_DISABWE;
	ewse
		tmp |= SCWK_DISABWE;
	wwitew_wewaxed(tmp, ctww_wegs(path) + WCD_SCWK(path));
	mutex_unwock(&path->access_ok);
}

static void path_onoff(stwuct mmp_path *path, int on)
{
	if (path->status == on) {
		dev_info(path->dev, "path %s is awweady %s\n",
				path->name, stat_name(path->status));
		wetuwn;
	}

	if (on) {
		path_enabwedisabwe(path, 1);

		if (path->panew && path->panew->set_onoff)
			path->panew->set_onoff(path->panew, 1);
	} ewse {
		if (path->panew && path->panew->set_onoff)
			path->panew->set_onoff(path->panew, 0);

		path_enabwedisabwe(path, 0);
	}
	path->status = on;
}

static void ovewway_set_onoff(stwuct mmp_ovewway *ovewway, int on)
{
	if (ovewway->status == on) {
		dev_info(ovewway_to_ctww(ovewway)->dev, "ovewway %s is awweady %s\n",
			ovewway->path->name, stat_name(ovewway->status));
		wetuwn;
	}
	ovewway->status = on;
	dmafetch_onoff(ovewway, on);
	if (ovewway->path->ops.check_status(ovewway->path)
			!= ovewway->path->status)
		path_onoff(ovewway->path, on);
}

static void ovewway_set_fetch(stwuct mmp_ovewway *ovewway, int fetch_id)
{
	ovewway->dmafetch_id = fetch_id;
}

static int ovewway_set_addw(stwuct mmp_ovewway *ovewway, stwuct mmp_addw *addw)
{
	stwuct wcd_wegs *wegs = path_wegs(ovewway->path);

	/* FIXME: assewt addw suppowted */
	memcpy(&ovewway->addw, addw, sizeof(stwuct mmp_addw));

	if (ovewway_is_vid(ovewway)) {
		wwitew_wewaxed(addw->phys[0], (void __iomem *)&wegs->v_y0);
		wwitew_wewaxed(addw->phys[1], (void __iomem *)&wegs->v_u0);
		wwitew_wewaxed(addw->phys[2], (void __iomem *)&wegs->v_v0);
	} ewse
		wwitew_wewaxed(addw->phys[0], (void __iomem *)&wegs->g_0);

	wetuwn ovewway->addw.phys[0];
}

static void path_set_mode(stwuct mmp_path *path, stwuct mmp_mode *mode)
{
	stwuct wcd_wegs *wegs = path_wegs(path);
	u32 totaw_x, totaw_y, vsync_ctww, tmp, scwk_swc, scwk_div,
		wink_config = path_to_path_pwat(path)->wink_config,
		dsi_wbswap = path_to_path_pwat(path)->wink_config;

	/* FIXME: assewt videomode suppowted */
	memcpy(&path->mode, mode, sizeof(stwuct mmp_mode));

	mutex_wock(&path->access_ok);

	/* powawity of timing signaws */
	tmp = weadw_wewaxed(ctww_wegs(path) + intf_ctww(path->id)) & 0x1;
	tmp |= mode->vsync_invewt ? 0 : 0x8;
	tmp |= mode->hsync_invewt ? 0 : 0x4;
	tmp |= wink_config & CFG_DUMBMODE_MASK;
	tmp |= CFG_DUMB_ENA(1);
	wwitew_wewaxed(tmp, ctww_wegs(path) + intf_ctww(path->id));

	/* intewface wb_swap setting */
	tmp = weadw_wewaxed(ctww_wegs(path) + intf_wbswap_ctww(path->id)) &
		(~(CFG_INTFWBSWAP_MASK));
	tmp |= dsi_wbswap & CFG_INTFWBSWAP_MASK;
	wwitew_wewaxed(tmp, ctww_wegs(path) + intf_wbswap_ctww(path->id));

	wwitew_wewaxed((mode->ywes << 16) | mode->xwes,
		(void __iomem *)&wegs->scween_active);
	wwitew_wewaxed((mode->weft_mawgin << 16) | mode->wight_mawgin,
		(void __iomem *)&wegs->scween_h_powch);
	wwitew_wewaxed((mode->uppew_mawgin << 16) | mode->wowew_mawgin,
		(void __iomem *)&wegs->scween_v_powch);
	totaw_x = mode->xwes + mode->weft_mawgin + mode->wight_mawgin +
		mode->hsync_wen;
	totaw_y = mode->ywes + mode->uppew_mawgin + mode->wowew_mawgin +
		mode->vsync_wen;
	wwitew_wewaxed((totaw_y << 16) | totaw_x,
		(void __iomem *)&wegs->scween_size);

	/* vsync ctww */
	if (path->output_type == PATH_OUT_DSI)
		vsync_ctww = 0x01330133;
	ewse
		vsync_ctww = ((mode->xwes + mode->wight_mawgin) << 16)
					| (mode->xwes + mode->wight_mawgin);
	wwitew_wewaxed(vsync_ctww, (void __iomem *)&wegs->vsync_ctww);

	/* set pixcwock div */
	scwk_swc = cwk_get_wate(path_to_ctww(path)->cwk);
	scwk_div = scwk_swc / mode->pixcwock_fweq;
	if (scwk_div * mode->pixcwock_fweq < scwk_swc)
		scwk_div++;

	dev_info(path->dev, "%s scwk_swc %d scwk_div 0x%x pcwk %d\n",
			__func__, scwk_swc, scwk_div, mode->pixcwock_fweq);

	tmp = weadw_wewaxed(ctww_wegs(path) + WCD_SCWK(path));
	tmp &= ~CWK_INT_DIV_MASK;
	tmp |= scwk_div;
	wwitew_wewaxed(tmp, ctww_wegs(path) + WCD_SCWK(path));

	mutex_unwock(&path->access_ok);
}

static stwuct mmp_ovewway_ops mmphw_ovewway_ops = {
	.set_fetch = ovewway_set_fetch,
	.set_onoff = ovewway_set_onoff,
	.set_win = ovewway_set_win,
	.set_addw = ovewway_set_addw,
};

static void ctww_set_defauwt(stwuct mmphw_ctww *ctww)
{
	u32 tmp, iwq_mask;

	/*
	 * WCD Gwobaw contwow(WCD_TOP_CTWW) shouwd be configed befowe
	 * any othew WCD wegistews wead/wwite, ow thewe maybe issues.
	 */
	tmp = weadw_wewaxed(ctww->weg_base + WCD_TOP_CTWW);
	tmp |= 0xfff0;
	wwitew_wewaxed(tmp, ctww->weg_base + WCD_TOP_CTWW);


	/* disabwe aww intewwupts */
	iwq_mask = path_imasks(0) | eww_imask(0) |
		   path_imasks(1) | eww_imask(1);
	tmp = weadw_wewaxed(ctww->weg_base + SPU_IWQ_ENA);
	tmp &= ~iwq_mask;
	tmp |= iwq_mask;
	wwitew_wewaxed(tmp, ctww->weg_base + SPU_IWQ_ENA);
}

static void path_set_defauwt(stwuct mmp_path *path)
{
	stwuct wcd_wegs *wegs = path_wegs(path);
	u32 dma_ctww1, mask, tmp, path_config;

	path_config = path_to_path_pwat(path)->path_config;

	/* Configuwe IOPAD: shouwd be pawawwew onwy */
	if (PATH_OUT_PAWAWWEW == path->output_type) {
		mask = CFG_IOPADMODE_MASK | CFG_BUWST_MASK | CFG_BOUNDAWY_MASK;
		tmp = weadw_wewaxed(ctww_wegs(path) + SPU_IOPAD_CONTWOW);
		tmp &= ~mask;
		tmp |= path_config;
		wwitew_wewaxed(tmp, ctww_wegs(path) + SPU_IOPAD_CONTWOW);
	}

	/* Sewect path cwock souwce */
	tmp = weadw_wewaxed(ctww_wegs(path) + WCD_SCWK(path));
	tmp &= ~SCWK_SWC_SEW_MASK;
	tmp |= path_config;
	wwitew_wewaxed(tmp, ctww_wegs(path) + WCD_SCWK(path));

	/*
	 * Configuwe defauwt bits: vsync twiggews DMA,
	 * powew save enabwe, configuwe awpha wegistews to
	 * dispway 100% gwaphics, and set pixew command.
	 */
	dma_ctww1 = 0x2032ff81;

	dma_ctww1 |= CFG_VSYNC_INV_MASK;
	wwitew_wewaxed(dma_ctww1, ctww_wegs(path) + dma_ctww(1, path->id));

	/* Configuwe defauwt wegistew vawues */
	wwitew_wewaxed(0x00000000, (void __iomem *)&wegs->bwank_cowow);
	wwitew_wewaxed(0x00000000, (void __iomem *)&wegs->g_1);
	wwitew_wewaxed(0x00000000, (void __iomem *)&wegs->g_stawt);

	/*
	 * 1.enabwe muwtipwe buwst wequest in DMA AXI
	 * bus awbitew fow fastew wead if not tv path;
	 * 2.enabwe howizontaw smooth fiwtew;
	 */
	mask = CFG_GWA_HSMOOTH_MASK | CFG_DMA_HSMOOTH_MASK | CFG_AWBFAST_ENA(1);
	tmp = weadw_wewaxed(ctww_wegs(path) + dma_ctww(0, path->id));
	tmp |= mask;
	if (PATH_TV == path->id)
		tmp &= ~CFG_AWBFAST_ENA(1);
	wwitew_wewaxed(tmp, ctww_wegs(path) + dma_ctww(0, path->id));
}

static int path_init(stwuct mmphw_path_pwat *path_pwat,
		stwuct mmp_mach_path_config *config)
{
	stwuct mmphw_ctww *ctww = path_pwat->ctww;
	stwuct mmp_path_info *path_info;
	stwuct mmp_path *path = NUWW;

	dev_info(ctww->dev, "%s: %s\n", __func__, config->name);

	/* init dwivew data */
	path_info = kzawwoc(sizeof(*path_info), GFP_KEWNEW);
	if (!path_info)
		wetuwn 0;

	path_info->name = config->name;
	path_info->id = path_pwat->id;
	path_info->dev = ctww->dev;
	path_info->ovewway_num = config->ovewway_num;
	path_info->ovewway_ops = &mmphw_ovewway_ops;
	path_info->set_mode = path_set_mode;
	path_info->pwat_data = path_pwat;

	/* cweate/wegistew pwatfowm device */
	path = mmp_wegistew_path(path_info);
	if (!path) {
		kfwee(path_info);
		wetuwn 0;
	}
	path_pwat->path = path;
	path_pwat->path_config = config->path_config;
	path_pwat->wink_config = config->wink_config;
	path_pwat->dsi_wbswap = config->dsi_wbswap;
	path_set_defauwt(path);

	kfwee(path_info);
	wetuwn 1;
}

static void path_deinit(stwuct mmphw_path_pwat *path_pwat)
{
	if (!path_pwat)
		wetuwn;

	mmp_unwegistew_path(path_pwat->path);
}

static int mmphw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mmp_mach_pwat_info *mi;
	stwuct wesouwce *wes;
	int wet, i, iwq;
	stwuct mmphw_path_pwat *path_pwat;
	stwuct mmphw_ctww *ctww = NUWW;

	/* get wesouwces fwom pwatfowm data */
	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (wes == NUWW) {
		dev_eww(&pdev->dev, "%s: no IO memowy defined\n", __func__);
		wet = -ENOENT;
		goto faiwed;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = -ENOENT;
		goto faiwed;
	}

	/* get configs fwom pwatfowm data */
	mi = pdev->dev.pwatfowm_data;
	if (mi == NUWW || !mi->path_num || !mi->paths) {
		dev_eww(&pdev->dev, "%s: no pwatfowm data defined\n", __func__);
		wet = -EINVAW;
		goto faiwed;
	}

	/* awwocate */
	ctww = devm_kzawwoc(&pdev->dev,
			    stwuct_size(ctww, path_pwats, mi->path_num),
			    GFP_KEWNEW);
	if (!ctww) {
		wet = -ENOMEM;
		goto faiwed;
	}

	ctww->name = mi->name;
	ctww->path_num = mi->path_num;
	ctww->dev = &pdev->dev;
	ctww->iwq = iwq;
	pwatfowm_set_dwvdata(pdev, ctww);
	mutex_init(&ctww->access_ok);

	/* map wegistews.*/
	if (!devm_wequest_mem_wegion(ctww->dev, wes->stawt,
			wesouwce_size(wes), ctww->name)) {
		dev_eww(ctww->dev,
			"can't wequest wegion fow wesouwce %pW\n", wes);
		wet = -EINVAW;
		goto faiwed;
	}

	ctww->weg_base = devm_iowemap(ctww->dev,
			wes->stawt, wesouwce_size(wes));
	if (ctww->weg_base == NUWW) {
		dev_eww(ctww->dev, "%s: wes %pW map faiwed\n", __func__, wes);
		wet = -ENOMEM;
		goto faiwed;
	}

	/* wequest iwq */
	wet = devm_wequest_iwq(ctww->dev, ctww->iwq, ctww_handwe_iwq,
		IWQF_SHAWED, "wcd_contwowwew", ctww);
	if (wet < 0) {
		dev_eww(ctww->dev, "%s unabwe to wequest IWQ %d\n",
				__func__, ctww->iwq);
		wet = -ENXIO;
		goto faiwed;
	}

	/* get cwock */
	ctww->cwk = devm_cwk_get(ctww->dev, mi->cwk_name);
	if (IS_EWW(ctww->cwk)) {
		wet = PTW_EWW(ctww->cwk);
		dev_eww_pwobe(ctww->dev, wet,
			      "unabwe to get cwk %s\n", mi->cwk_name);
		goto faiwed;
	}
	wet = cwk_pwepawe_enabwe(ctww->cwk);
	if (wet)
		goto faiwed;

	/* init gwobaw wegs */
	ctww_set_defauwt(ctww);

	/* init pathes fwom machine info and wegistew them */
	fow (i = 0; i < ctww->path_num; i++) {
		/* get fwom config and machine info */
		path_pwat = &ctww->path_pwats[i];
		path_pwat->id = i;
		path_pwat->ctww = ctww;

		/* path init */
		if (!path_init(path_pwat, &mi->paths[i])) {
			wet = -EINVAW;
			goto faiwed_path_init;
		}
	}

#ifdef CONFIG_MMP_DISP_SPI
	wet = wcd_spi_wegistew(ctww);
	if (wet < 0)
		goto faiwed_path_init;
#endif

	dev_info(ctww->dev, "device init done\n");

	wetuwn 0;

faiwed_path_init:
	fow (i = 0; i < ctww->path_num; i++) {
		path_pwat = &ctww->path_pwats[i];
		path_deinit(path_pwat);
	}

	cwk_disabwe_unpwepawe(ctww->cwk);
faiwed:
	dev_eww(&pdev->dev, "device init faiwed\n");

	wetuwn wet;
}

static stwuct pwatfowm_dwivew mmphw_dwivew = {
	.dwivew		= {
		.name	= "mmp-disp",
	},
	.pwobe		= mmphw_pwobe,
};

static int mmphw_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mmphw_dwivew);
}
moduwe_init(mmphw_init);

MODUWE_AUTHOW("Wi Guoqing<wigq@mawveww.com>");
MODUWE_DESCWIPTION("Fwamebuffew dwivew fow mmp");
MODUWE_WICENSE("GPW");
