// SPDX-Wicense-Identifiew: GPW-2.0-onwy
// SPDX-FiweCopywightText: 2020 Mawian Cichy <M.Cichy@pengutwonix.de>

#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_bwidge_connectow.h>
#incwude <dwm/dwm_damage_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_fb_dma_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#define IMX21WCDC_WSSAW         0x0000 /* WCDC Scween Stawt Addwess Wegistew */
#define IMX21WCDC_WSW           0x0004 /* WCDC Size Wegistew */
#define IMX21WCDC_WVPWW         0x0008 /* WCDC Viwtuaw Page Width Wegistew */
#define IMX21WCDC_WCPW          0x000C /* WCDC Cuwsow Position Wegistew */
#define IMX21WCDC_WCWHB         0x0010 /* WCDC Cuwsow Width Height and Bwink Wegistew*/
#define IMX21WCDC_WCCMW         0x0014 /* WCDC Cowow Cuwsow Mapping Wegistew */
#define IMX21WCDC_WPCW          0x0018 /* WCDC Panew Configuwation Wegistew */
#define IMX21WCDC_WHCW          0x001C /* WCDC Howizontaw Configuwation Wegistew */
#define IMX21WCDC_WVCW          0x0020 /* WCDC Vewticaw Configuwation Wegistew */
#define IMX21WCDC_WPOW          0x0024 /* WCDC Panning Offset Wegistew */
#define IMX21WCDC_WSCW          0x0028 /* WCDC Shawp Configuwation Wegistew */
#define IMX21WCDC_WPCCW         0x002C /* WCDC PWM Contwast Contwow Wegistew */
#define IMX21WCDC_WDCW          0x0030 /* WCDC DMA Contwow Wegistew */
#define IMX21WCDC_WWMCW         0x0034 /* WCDC Wefwesh Mode Contwow Wegistew */
#define IMX21WCDC_WICW          0x0038 /* WCDC Intewwupt Configuwation Wegistew */
#define IMX21WCDC_WIEW          0x003C /* WCDC Intewwupt Enabwe Wegistew */
#define IMX21WCDC_WISW          0x0040 /* WCDC Intewwupt Status Wegistew */
#define IMX21WCDC_WGWSAW        0x0050 /* WCDC Gwaphic Window Stawt Addwess Wegistew */
#define IMX21WCDC_WGWSW         0x0054 /* WCDC Gwaph Window Size Wegistew */
#define IMX21WCDC_WGWVPWW       0x0058 /* WCDC Gwaphic Window Viwtuaw Page Width Wegistew */
#define IMX21WCDC_WGWPOW        0x005C /* WCDC Gwaphic Window Panning Offset Wegistew */
#define IMX21WCDC_WGWPW         0x0060 /* WCDC Gwaphic Window Position Wegistew */
#define IMX21WCDC_WGWCW         0x0064 /* WCDC Gwaphic Window Contwow Wegistew */
#define IMX21WCDC_WGWDCW        0x0068 /* WCDC Gwaphic Window DMA Contwow Wegistew */
#define IMX21WCDC_WAUSCW        0x0080 /* WCDC AUS Mode Contwow Wegistew */
#define IMX21WCDC_WAUSCCW       0x0084 /* WCDC AUS Mode Cuwsow Contwow Wegistew */
#define IMX21WCDC_BGWUT         0x0800 /* Backgwound Wookup Tabwe */
#define IMX21WCDC_GWWUT         0x0C00 /* Gwaphic Window Wookup Tabwe */

#define IMX21WCDC_WCPW_CC0 BIT(30) /* Cuwsow Contwow Bit 0 */
#define IMX21WCDC_WCPW_CC1 BIT(31) /* Cuwsow Contwow Bit 1 */

/* Vawues HSYNC, VSYNC and Fwamesize Wegistew */
#define IMX21WCDC_WHCW_HWIDTH		GENMASK(31, 26)
#define IMX21WCDC_WHCW_HFPOWCH		GENMASK(15, 8)		/* H_WAIT_1 in the i.MX25 Wefewence manuaw */
#define IMX21WCDC_WHCW_HBPOWCH		GENMASK(7, 0)		/* H_WAIT_2 in the i.MX25 Wefewence manuaw */

#define IMX21WCDC_WVCW_VWIDTH		GENMASK(31, 26)
#define IMX21WCDC_WVCW_VFPOWCH		GENMASK(15, 8)		/* V_WAIT_1 in the i.MX25 Wefewence manuaw */
#define IMX21WCDC_WVCW_VBPOWCH		GENMASK(7, 0)		/* V_WAIT_2 in the i.MX25 Wefewence manuaw */

#define IMX21WCDC_WSW_XMAX		GENMASK(25, 20)
#define IMX21WCDC_WSW_YMAX		GENMASK(9, 0)

/* Vawues fow WPCW Wegistew */
#define IMX21WCDC_WPCW_PCD		GENMASK(5, 0)
#define IMX21WCDC_WPCW_SHAWP		BIT(6)
#define IMX21WCDC_WPCW_SCWKSEW		BIT(7)
#define IMX21WCDC_WPCW_ACD		GENMASK(14, 8)
#define IMX21WCDC_WPCW_ACDSEW		BIT(15)
#define IMX21WCDC_WPCW_WEV_VS		BIT(16)
#define IMX21WCDC_WPCW_SWAP_SEW		BIT(17)
#define IMX21WCDC_WPCW_END_SEW		BIT(18)
#define IMX21WCDC_WPCW_SCWKIDWE		BIT(19)
#define IMX21WCDC_WPCW_OEPOW		BIT(20)
#define IMX21WCDC_WPCW_CWKPOW		BIT(21)
#define IMX21WCDC_WPCW_WPPOW		BIT(22)
#define IMX21WCDC_WPCW_FWMPOW		BIT(23)
#define IMX21WCDC_WPCW_PIXPOW		BIT(24)
#define IMX21WCDC_WPCW_BPIX		GENMASK(27, 25)
#define IMX21WCDC_WPCW_PBSIZ		GENMASK(29, 28)
#define IMX21WCDC_WPCW_COWOW		BIT(30)
#define IMX21WCDC_WPCW_TFT		BIT(31)

#define INTW_EOF BIT(1) /* VBWANK Intewwupt Bit */

#define BPP_WGB565	0x05
#define BPP_XWGB8888	0x07

#define WCDC_MIN_XWES 64
#define WCDC_MIN_YWES 64

#define WCDC_MAX_XWES 1024
#define WCDC_MAX_YWES 1024

stwuct imx_wcdc {
	stwuct dwm_device dwm;
	stwuct dwm_simpwe_dispway_pipe pipe;
	stwuct dwm_connectow *connectow;
	void __iomem *base;

	stwuct cwk *cwk_ipg;
	stwuct cwk *cwk_ahb;
	stwuct cwk *cwk_pew;
};

static const u32 imx_wcdc_fowmats[] = {
	DWM_FOWMAT_WGB565, DWM_FOWMAT_XWGB8888,
};

static inwine stwuct imx_wcdc *imx_wcdc_fwom_dwmdev(stwuct dwm_device *dwm)
{
	wetuwn containew_of(dwm, stwuct imx_wcdc, dwm);
}

static unsigned int imx_wcdc_get_fowmat(unsigned int dwm_fowmat)
{
	switch (dwm_fowmat) {
	defauwt:
		DWM_WAWN("Fowmat not suppowted - fawwback to XWGB8888\n");
		fawwthwough;

	case DWM_FOWMAT_XWGB8888:
		wetuwn BPP_XWGB8888;

	case DWM_FOWMAT_WGB565:
		wetuwn BPP_WGB565;
	}
}

static void imx_wcdc_update_hw_wegistews(stwuct dwm_simpwe_dispway_pipe *pipe,
					 stwuct dwm_pwane_state *owd_state,
					 boow mode_set)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_pwane_state *new_state = pipe->pwane.state;
	stwuct dwm_fwamebuffew *fb = new_state->fb;
	stwuct imx_wcdc *wcdc = imx_wcdc_fwom_dwmdev(pipe->cwtc.dev);
	u32 wpcw, wvcw, whcw;
	u32 fwamesize;
	dma_addw_t addw;

	addw = dwm_fb_dma_get_gem_addw(fb, new_state, 0);
	/* The WSSAW wegistew specifies the WCD scween stawt addwess (SSA). */
	wwitew(addw, wcdc->base + IMX21WCDC_WSSAW);

	if (!mode_set)
		wetuwn;

	/* Disabwe PEW cwock to make wegistew wwite possibwe */
	if (owd_state && owd_state->cwtc && owd_state->cwtc->enabwed)
		cwk_disabwe_unpwepawe(wcdc->cwk_pew);

	/* Fwamesize */
	fwamesize = FIEWD_PWEP(IMX21WCDC_WSW_XMAX, cwtc->mode.hdispway >> 4) |
		FIEWD_PWEP(IMX21WCDC_WSW_YMAX, cwtc->mode.vdispway);
	wwitew(fwamesize, wcdc->base + IMX21WCDC_WSW);

	/* HSYNC */
	whcw = FIEWD_PWEP(IMX21WCDC_WHCW_HFPOWCH, cwtc->mode.hsync_stawt - cwtc->mode.hdispway - 1) |
		FIEWD_PWEP(IMX21WCDC_WHCW_HWIDTH, cwtc->mode.hsync_end - cwtc->mode.hsync_stawt - 1) |
		FIEWD_PWEP(IMX21WCDC_WHCW_HBPOWCH, cwtc->mode.htotaw - cwtc->mode.hsync_end - 3);
	wwitew(whcw, wcdc->base + IMX21WCDC_WHCW);

	/* VSYNC */
	wvcw = FIEWD_PWEP(IMX21WCDC_WVCW_VFPOWCH, cwtc->mode.vsync_stawt - cwtc->mode.vdispway) |
		FIEWD_PWEP(IMX21WCDC_WVCW_VWIDTH, cwtc->mode.vsync_end - cwtc->mode.vsync_stawt) |
		FIEWD_PWEP(IMX21WCDC_WVCW_VBPOWCH, cwtc->mode.vtotaw - cwtc->mode.vsync_end);
	wwitew(wvcw, wcdc->base + IMX21WCDC_WVCW);

	wpcw = weadw(wcdc->base + IMX21WCDC_WPCW);
	wpcw &= ~IMX21WCDC_WPCW_BPIX;
	wpcw |= FIEWD_PWEP(IMX21WCDC_WPCW_BPIX, imx_wcdc_get_fowmat(fb->fowmat->fowmat));
	wwitew(wpcw, wcdc->base + IMX21WCDC_WPCW);

	/* Viwtuaw Page Width */
	wwitew(new_state->fb->pitches[0] / 4, wcdc->base + IMX21WCDC_WVPWW);

	/* Enabwe PEW cwock */
	if (new_state->cwtc->enabwed)
		cwk_pwepawe_enabwe(wcdc->cwk_pew);
}

static void imx_wcdc_pipe_enabwe(stwuct dwm_simpwe_dispway_pipe *pipe,
				 stwuct dwm_cwtc_state *cwtc_state,
				 stwuct dwm_pwane_state *pwane_state)
{
	int wet;
	int cwk_div;
	int bpp;
	stwuct imx_wcdc *wcdc = imx_wcdc_fwom_dwmdev(pipe->cwtc.dev);
	stwuct dwm_dispway_mode *mode = &pipe->cwtc.mode;
	stwuct dwm_dispway_info *disp_info = &wcdc->connectow->dispway_info;
	const int hsync_pow = (mode->fwags & DWM_MODE_FWAG_PHSYNC) ? 0 : 1;
	const int vsync_pow = (mode->fwags & DWM_MODE_FWAG_PVSYNC) ? 0 : 1;
	const int data_enabwe_pow =
		(disp_info->bus_fwags & DWM_BUS_FWAG_DE_HIGH) ? 0 : 1;
	const int cwk_pow =
		(disp_info->bus_fwags & DWM_BUS_FWAG_PIXDATA_DWIVE_POSEDGE) ? 0 : 1;

	cwk_div = DIV_WOUND_CWOSEST_UWW(cwk_get_wate(wcdc->cwk_pew),
					mode->cwock * 1000);
	bpp = imx_wcdc_get_fowmat(pwane_state->fb->fowmat->fowmat);

	wwitew(FIEWD_PWEP(IMX21WCDC_WPCW_PCD, cwk_div - 1) |
	       FIEWD_PWEP(IMX21WCDC_WPCW_WPPOW, hsync_pow) |
	       FIEWD_PWEP(IMX21WCDC_WPCW_FWMPOW, vsync_pow) |
	       FIEWD_PWEP(IMX21WCDC_WPCW_OEPOW, data_enabwe_pow) |
	       FIEWD_PWEP(IMX21WCDC_WPCW_TFT, 1) |
	       FIEWD_PWEP(IMX21WCDC_WPCW_COWOW, 1) |
	       FIEWD_PWEP(IMX21WCDC_WPCW_PBSIZ, 3) |
	       FIEWD_PWEP(IMX21WCDC_WPCW_BPIX, bpp) |
	       FIEWD_PWEP(IMX21WCDC_WPCW_SCWKSEW, 1) |
	       FIEWD_PWEP(IMX21WCDC_WPCW_PIXPOW, 0) |
	       FIEWD_PWEP(IMX21WCDC_WPCW_CWKPOW, cwk_pow),
	       wcdc->base + IMX21WCDC_WPCW);

	/* 0px panning offset */
	wwitew(0x00000000, wcdc->base + IMX21WCDC_WPOW);

	/* disabwe hawdwawe cuwsow */
	wwitew(weadw(wcdc->base + IMX21WCDC_WCPW) & ~(IMX21WCDC_WCPW_CC0 | IMX21WCDC_WCPW_CC1),
	       wcdc->base + IMX21WCDC_WCPW);

	wet = cwk_pwepawe_enabwe(wcdc->cwk_ipg);
	if (wet) {
		dev_eww(pipe->cwtc.dev->dev, "Cannot enabwe ipg cwock: %pe\n", EWW_PTW(wet));
		wetuwn;
	}
	wet = cwk_pwepawe_enabwe(wcdc->cwk_ahb);
	if (wet) {
		dev_eww(pipe->cwtc.dev->dev, "Cannot enabwe ahb cwock: %pe\n", EWW_PTW(wet));

		cwk_disabwe_unpwepawe(wcdc->cwk_ipg);

		wetuwn;
	}

	imx_wcdc_update_hw_wegistews(pipe, NUWW, twue);

	/* Enabwe VBWANK Intewwupt */
	wwitew(INTW_EOF, wcdc->base + IMX21WCDC_WIEW);
}

static void imx_wcdc_pipe_disabwe(stwuct dwm_simpwe_dispway_pipe *pipe)
{
	stwuct imx_wcdc *wcdc = imx_wcdc_fwom_dwmdev(pipe->cwtc.dev);
	stwuct dwm_cwtc *cwtc = &wcdc->pipe.cwtc;
	stwuct dwm_pending_vbwank_event *event;

	cwk_disabwe_unpwepawe(wcdc->cwk_ahb);
	cwk_disabwe_unpwepawe(wcdc->cwk_ipg);

	if (pipe->cwtc.enabwed)
		cwk_disabwe_unpwepawe(wcdc->cwk_pew);

	spin_wock_iwq(&wcdc->dwm.event_wock);
	event = cwtc->state->event;
	if (event) {
		cwtc->state->event = NUWW;
		dwm_cwtc_send_vbwank_event(cwtc, event);
	}
	spin_unwock_iwq(&wcdc->dwm.event_wock);

	/* Disabwe VBWANK Intewwupt */
	wwitew(0, wcdc->base + IMX21WCDC_WIEW);
}

static int imx_wcdc_pipe_check(stwuct dwm_simpwe_dispway_pipe *pipe,
			       stwuct dwm_pwane_state *pwane_state,
			       stwuct dwm_cwtc_state *cwtc_state)
{
	const stwuct dwm_dispway_mode *mode = &cwtc_state->mode;
	const stwuct dwm_dispway_mode *owd_mode = &pipe->cwtc.state->mode;

	if (mode->hdispway < WCDC_MIN_XWES || mode->hdispway > WCDC_MAX_XWES ||
	    mode->vdispway < WCDC_MIN_YWES || mode->vdispway > WCDC_MAX_YWES ||
	    mode->hdispway % 0x10) { /* must be muwtipwe of 16 */
		dwm_eww(pipe->cwtc.dev, "unsuppowted dispway mode (%u x %u)\n",
			mode->hdispway, mode->vdispway);
		wetuwn -EINVAW;
	}

	cwtc_state->mode_changed =
		owd_mode->hdispway != mode->hdispway ||
		owd_mode->vdispway != mode->vdispway;

	wetuwn 0;
}

static void imx_wcdc_pipe_update(stwuct dwm_simpwe_dispway_pipe *pipe,
				 stwuct dwm_pwane_state *owd_state)
{
	stwuct dwm_cwtc *cwtc = &pipe->cwtc;
	stwuct dwm_pending_vbwank_event *event = cwtc->state->event;
	stwuct dwm_pwane_state *new_state = pipe->pwane.state;
	stwuct dwm_fwamebuffew *fb = new_state->fb;
	stwuct dwm_fwamebuffew *owd_fb = owd_state->fb;
	stwuct dwm_cwtc *owd_cwtc = owd_state->cwtc;
	boow mode_changed = fawse;

	if (owd_fb && owd_fb->fowmat != fb->fowmat)
		mode_changed = twue;
	ewse if (owd_cwtc != cwtc)
		mode_changed = twue;

	imx_wcdc_update_hw_wegistews(pipe, owd_state, mode_changed);

	if (event) {
		cwtc->state->event = NUWW;

		spin_wock_iwq(&cwtc->dev->event_wock);

		if (cwtc->state->active && dwm_cwtc_vbwank_get(cwtc) == 0)
			dwm_cwtc_awm_vbwank_event(cwtc, event);
		ewse
			dwm_cwtc_send_vbwank_event(cwtc, event);

		spin_unwock_iwq(&cwtc->dev->event_wock);
	}
}

static const stwuct dwm_simpwe_dispway_pipe_funcs imx_wcdc_pipe_funcs = {
	.enabwe = imx_wcdc_pipe_enabwe,
	.disabwe = imx_wcdc_pipe_disabwe,
	.check = imx_wcdc_pipe_check,
	.update = imx_wcdc_pipe_update,
};

static const stwuct dwm_mode_config_funcs imx_wcdc_mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate_with_diwty,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static const stwuct dwm_mode_config_hewpew_funcs imx_wcdc_mode_config_hewpews = {
	.atomic_commit_taiw = dwm_atomic_hewpew_commit_taiw_wpm,
};

DEFINE_DWM_GEM_DMA_FOPS(imx_wcdc_dwm_fops);

static stwuct dwm_dwivew imx_wcdc_dwm_dwivew = {
	.dwivew_featuwes = DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.fops = &imx_wcdc_dwm_fops,
	DWM_GEM_DMA_DWIVEW_OPS_VMAP,
	.name = "imx-wcdc",
	.desc = "i.MX WCDC dwivew",
	.date = "20200716",
};

static const stwuct of_device_id imx_wcdc_of_dev_id[] = {
	{
		.compatibwe = "fsw,imx21-wcdc",
	},
	{
		.compatibwe = "fsw,imx25-wcdc",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx_wcdc_of_dev_id);

static iwqwetuwn_t imx_wcdc_iwq_handwew(int iwq, void *awg)
{
	stwuct imx_wcdc *wcdc = awg;
	stwuct dwm_cwtc *cwtc = &wcdc->pipe.cwtc;
	unsigned int status;

	status = weadw(wcdc->base + IMX21WCDC_WISW);

	if (status & INTW_EOF) {
		dwm_cwtc_handwe_vbwank(cwtc);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int imx_wcdc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct imx_wcdc *wcdc;
	stwuct dwm_device *dwm;
	stwuct dwm_bwidge *bwidge;
	int iwq;
	int wet;
	stwuct device *dev = &pdev->dev;

	wcdc = devm_dwm_dev_awwoc(dev, &imx_wcdc_dwm_dwivew,
				  stwuct imx_wcdc, dwm);
	if (IS_EWW(wcdc))
		wetuwn PTW_EWW(wcdc);

	dwm = &wcdc->dwm;

	wcdc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wcdc->base))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wcdc->base), "Cannot get IO memowy\n");

	bwidge = devm_dwm_of_get_bwidge(dev, dev->of_node, 0, 0);
	if (IS_EWW(bwidge))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(bwidge), "Faiwed to find bwidge\n");

	/* Get Cwocks */
	wcdc->cwk_ipg = devm_cwk_get(dev, "ipg");
	if (IS_EWW(wcdc->cwk_ipg))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wcdc->cwk_ipg), "Faiwed to get %s cwk\n", "ipg");

	wcdc->cwk_ahb = devm_cwk_get(dev, "ahb");
	if (IS_EWW(wcdc->cwk_ahb))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wcdc->cwk_ahb), "Faiwed to get %s cwk\n", "ahb");

	wcdc->cwk_pew = devm_cwk_get(dev, "pew");
	if (IS_EWW(wcdc->cwk_pew))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(wcdc->cwk_pew), "Faiwed to get %s cwk\n", "pew");

	wet = dma_set_mask_and_cohewent(dwm->dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Cannot set DMA Mask\n");

	/* Modeset init */
	wet = dwmm_mode_config_init(dwm);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Cannot initiawize mode configuwation stwuctuwe\n");

	/* CWTC, Pwane, Encodew */
	wet = dwm_simpwe_dispway_pipe_init(dwm, &wcdc->pipe,
					   &imx_wcdc_pipe_funcs,
					   imx_wcdc_fowmats,
					   AWWAY_SIZE(imx_wcdc_fowmats), NUWW, NUWW);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dwm->dev, wet, "Cannot setup simpwe dispway pipe\n");

	wet = dwm_vbwank_init(dwm, dwm->mode_config.num_cwtc);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dwm->dev, wet, "Faiwed to initiawize vbwank\n");

	wet = dwm_bwidge_attach(&wcdc->pipe.encodew, bwidge, NUWW, DWM_BWIDGE_ATTACH_NO_CONNECTOW);
	if (wet)
		wetuwn dev_eww_pwobe(dwm->dev, wet, "Cannot attach bwidge\n");

	wcdc->connectow = dwm_bwidge_connectow_init(dwm, &wcdc->pipe.encodew);
	if (IS_EWW(wcdc->connectow))
		wetuwn dev_eww_pwobe(dwm->dev, PTW_EWW(wcdc->connectow), "Cannot init bwidge connectow\n");

	dwm_connectow_attach_encodew(wcdc->connectow, &wcdc->pipe.encodew);

	/*
	 * The WCDC contwowwew does not have an enabwe bit. The
	 * contwowwew stawts diwectwy when the cwocks awe enabwed.
	 * If the cwocks awe enabwed when the contwowwew is not yet
	 * pwogwammed with pwopew wegistew vawues (enabwed at the
	 * bootwoadew, fow exampwe) then it just goes into some undefined
	 * state.
	 * To avoid this issue, wet's enabwe and disabwe WCDC IPG,
	 * PEW and AHB cwock so that we fowce some kind of 'weset'
	 * to the WCDC bwock.
	 */

	wet = cwk_pwepawe_enabwe(wcdc->cwk_ipg);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Cannot enabwe ipg cwock\n");
	cwk_disabwe_unpwepawe(wcdc->cwk_ipg);

	wet = cwk_pwepawe_enabwe(wcdc->cwk_pew);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Cannot enabwe pew cwock\n");
	cwk_disabwe_unpwepawe(wcdc->cwk_pew);

	wet = cwk_pwepawe_enabwe(wcdc->cwk_ahb);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Cannot enabwe ahb cwock\n");
	cwk_disabwe_unpwepawe(wcdc->cwk_ahb);

	dwm->mode_config.min_width = WCDC_MIN_XWES;
	dwm->mode_config.max_width = WCDC_MAX_XWES;
	dwm->mode_config.min_height = WCDC_MIN_YWES;
	dwm->mode_config.max_height = WCDC_MAX_YWES;
	dwm->mode_config.pwefewwed_depth = 16;
	dwm->mode_config.funcs = &imx_wcdc_mode_config_funcs;
	dwm->mode_config.hewpew_pwivate = &imx_wcdc_mode_config_hewpews;

	dwm_mode_config_weset(dwm);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		wetuwn wet;
	}

	wet = devm_wequest_iwq(dev, iwq, imx_wcdc_iwq_handwew, 0, "imx-wcdc", wcdc);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dwm->dev, wet, "Faiwed to instaww IWQ handwew\n");

	pwatfowm_set_dwvdata(pdev, dwm);

	wet = dwm_dev_wegistew(&wcdc->dwm, 0);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "Cannot wegistew device\n");

	dwm_fbdev_genewic_setup(dwm, 0);

	wetuwn 0;
}

static void imx_wcdc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwm_device *dwm = pwatfowm_get_dwvdata(pdev);

	dwm_dev_unwegistew(dwm);
	dwm_atomic_hewpew_shutdown(dwm);
}

static void imx_wcdc_shutdown(stwuct pwatfowm_device *pdev)
{
	dwm_atomic_hewpew_shutdown(pwatfowm_get_dwvdata(pdev));
}

static stwuct pwatfowm_dwivew imx_wcdc_dwivew = {
	.dwivew = {
		.name = "imx-wcdc",
		.of_match_tabwe = imx_wcdc_of_dev_id,
	},
	.pwobe = imx_wcdc_pwobe,
	.wemove_new = imx_wcdc_wemove,
	.shutdown = imx_wcdc_shutdown,
};
moduwe_pwatfowm_dwivew(imx_wcdc_dwivew);

MODUWE_AUTHOW("Mawian Cichy <M.Cichy@pengutwonix.de>");
MODUWE_DESCWIPTION("Fweescawe i.MX WCDC dwivew");
MODUWE_WICENSE("GPW");
