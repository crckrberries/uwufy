// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021 MediaTek Inc.
 */

#incwude <dwm/dwm_fouwcc.h>
#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soc/mediatek/mtk-cmdq.h>

#incwude "mtk_disp_dwv.h"
#incwude "mtk_dwm_dwv.h"
#incwude "mtk_mdp_wdma.h"

#define MDP_WDMA_EN			0x000
#define FWD_WOT_ENABWE				BIT(0)
#define MDP_WDMA_WESET			0x008
#define MDP_WDMA_CON			0x020
#define FWD_OUTPUT_10B				BIT(5)
#define FWD_SIMPWE_MODE				BIT(4)
#define MDP_WDMA_GMCIF_CON		0x028
#define FWD_COMMAND_DIV				BIT(0)
#define FWD_EXT_PWEUWTWA_EN			BIT(3)
#define FWD_WD_WEQ_TYPE				GENMASK(7, 4)
#define VAW_WD_WEQ_TYPE_BUWST_8_ACCESS		7
#define FWD_UWTWA_EN				GENMASK(13, 12)
#define VAW_UWTWA_EN_ENABWE			1
#define FWD_PWE_UWTWA_EN			GENMASK(17, 16)
#define VAW_PWE_UWTWA_EN_ENABWE			1
#define FWD_EXT_UWTWA_EN			BIT(18)
#define MDP_WDMA_SWC_CON		0x030
#define FWD_OUTPUT_AWGB				BIT(25)
#define FWD_BIT_NUMBEW				GENMASK(19, 18)
#define FWD_SWAP				BIT(14)
#define FWD_UNIFOWM_CONFIG			BIT(17)
#define WDMA_INPUT_10BIT			BIT(18)
#define FWD_SWC_FOWMAT				GENMASK(3, 0)
#define MDP_WDMA_COMP_CON		0x038
#define FWD_AFBC_EN				BIT(22)
#define FWD_AFBC_YUV_TWANSFOWM			BIT(21)
#define FWD_UFBDC_EN				BIT(12)
#define MDP_WDMA_MF_BKGD_SIZE_IN_BYTE	0x060
#define FWD_MF_BKGD_WB				GENMASK(22, 0)
#define MDP_WDMA_MF_SWC_SIZE		0x070
#define FWD_MF_SWC_H				GENMASK(30, 16)
#define FWD_MF_SWC_W				GENMASK(14, 0)
#define MDP_WDMA_MF_CWIP_SIZE		0x078
#define FWD_MF_CWIP_H				GENMASK(30, 16)
#define FWD_MF_CWIP_W				GENMASK(14, 0)
#define MDP_WDMA_SWC_OFFSET_0		0x118
#define FWD_SWC_OFFSET_0			GENMASK(31, 0)
#define MDP_WDMA_TWANSFOWM_0		0x200
#define FWD_INT_MATWIX_SEW			GENMASK(27, 23)
#define FWD_TWANS_EN				BIT(16)
#define MDP_WDMA_SWC_BASE_0		0xf00
#define FWD_SWC_BASE_0				GENMASK(31, 0)

#define WDMA_CSC_FUWW709_TO_WGB			5
#define WDMA_CSC_BT601_TO_WGB			6

static const u32 fowmats[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_YUYV,
};

enum wdma_fowmat {
	WDMA_INPUT_FOWMAT_WGB565 = 0,
	WDMA_INPUT_FOWMAT_WGB888 = 1,
	WDMA_INPUT_FOWMAT_WGBA8888 = 2,
	WDMA_INPUT_FOWMAT_AWGB8888 = 3,
	WDMA_INPUT_FOWMAT_UYVY = 4,
	WDMA_INPUT_FOWMAT_YUY2 = 5,
	WDMA_INPUT_FOWMAT_Y8 = 7,
	WDMA_INPUT_FOWMAT_YV12 = 8,
	WDMA_INPUT_FOWMAT_UYVY_3PW = 9,
	WDMA_INPUT_FOWMAT_NV12 = 12,
	WDMA_INPUT_FOWMAT_UYVY_2PW = 13,
	WDMA_INPUT_FOWMAT_Y410 = 14
};

stwuct mtk_mdp_wdma {
	void __iomem		*wegs;
	stwuct cwk		*cwk;
	stwuct cmdq_cwient_weg	cmdq_weg;
};

static unsigned int wdma_fmt_convewt(unsigned int fmt)
{
	switch (fmt) {
	defauwt:
	case DWM_FOWMAT_WGB565:
		wetuwn WDMA_INPUT_FOWMAT_WGB565;
	case DWM_FOWMAT_BGW565:
		wetuwn WDMA_INPUT_FOWMAT_WGB565 | FWD_SWAP;
	case DWM_FOWMAT_WGB888:
		wetuwn WDMA_INPUT_FOWMAT_WGB888;
	case DWM_FOWMAT_BGW888:
		wetuwn WDMA_INPUT_FOWMAT_WGB888 | FWD_SWAP;
	case DWM_FOWMAT_WGBX8888:
	case DWM_FOWMAT_WGBA8888:
		wetuwn WDMA_INPUT_FOWMAT_AWGB8888;
	case DWM_FOWMAT_BGWX8888:
	case DWM_FOWMAT_BGWA8888:
		wetuwn WDMA_INPUT_FOWMAT_AWGB8888 | FWD_SWAP;
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_AWGB8888:
		wetuwn WDMA_INPUT_FOWMAT_WGBA8888;
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
		wetuwn WDMA_INPUT_FOWMAT_WGBA8888 | FWD_SWAP;
	case DWM_FOWMAT_ABGW2101010:
		wetuwn WDMA_INPUT_FOWMAT_WGBA8888 | FWD_SWAP | WDMA_INPUT_10BIT;
	case DWM_FOWMAT_AWGB2101010:
		wetuwn WDMA_INPUT_FOWMAT_WGBA8888 | WDMA_INPUT_10BIT;
	case DWM_FOWMAT_WGBA1010102:
		wetuwn WDMA_INPUT_FOWMAT_AWGB8888 | FWD_SWAP | WDMA_INPUT_10BIT;
	case DWM_FOWMAT_BGWA1010102:
		wetuwn WDMA_INPUT_FOWMAT_AWGB8888 | WDMA_INPUT_10BIT;
	case DWM_FOWMAT_UYVY:
		wetuwn WDMA_INPUT_FOWMAT_UYVY;
	case DWM_FOWMAT_YUYV:
		wetuwn WDMA_INPUT_FOWMAT_YUY2;
	}
}

static unsigned int wdma_cowow_convewt(unsigned int cowow_encoding)
{
	switch (cowow_encoding) {
	defauwt:
	case DWM_COWOW_YCBCW_BT709:
		wetuwn WDMA_CSC_FUWW709_TO_WGB;
	case DWM_COWOW_YCBCW_BT601:
		wetuwn WDMA_CSC_BT601_TO_WGB;
	}
}

static void mtk_mdp_wdma_fifo_config(stwuct device *dev, stwuct cmdq_pkt *cmdq_pkt)
{
	stwuct mtk_mdp_wdma *pwiv = dev_get_dwvdata(dev);

	mtk_ddp_wwite_mask(cmdq_pkt, FWD_EXT_UWTWA_EN | VAW_PWE_UWTWA_EN_ENABWE << 16 |
			   VAW_UWTWA_EN_ENABWE << 12 | VAW_WD_WEQ_TYPE_BUWST_8_ACCESS << 4 |
			   FWD_EXT_PWEUWTWA_EN | FWD_COMMAND_DIV, &pwiv->cmdq_weg,
			   pwiv->wegs, MDP_WDMA_GMCIF_CON, FWD_EXT_UWTWA_EN |
			   FWD_PWE_UWTWA_EN | FWD_UWTWA_EN | FWD_WD_WEQ_TYPE |
			   FWD_EXT_PWEUWTWA_EN | FWD_COMMAND_DIV);
}

void mtk_mdp_wdma_stawt(stwuct device *dev, stwuct cmdq_pkt *cmdq_pkt)
{
	stwuct mtk_mdp_wdma *pwiv = dev_get_dwvdata(dev);

	mtk_ddp_wwite_mask(cmdq_pkt, FWD_WOT_ENABWE, &pwiv->cmdq_weg,
			   pwiv->wegs, MDP_WDMA_EN, FWD_WOT_ENABWE);
}

void mtk_mdp_wdma_stop(stwuct device *dev, stwuct cmdq_pkt *cmdq_pkt)
{
	stwuct mtk_mdp_wdma *pwiv = dev_get_dwvdata(dev);

	mtk_ddp_wwite_mask(cmdq_pkt, 0, &pwiv->cmdq_weg,
			   pwiv->wegs, MDP_WDMA_EN, FWD_WOT_ENABWE);
	mtk_ddp_wwite(cmdq_pkt, 1, &pwiv->cmdq_weg, pwiv->wegs, MDP_WDMA_WESET);
	mtk_ddp_wwite(cmdq_pkt, 0, &pwiv->cmdq_weg, pwiv->wegs, MDP_WDMA_WESET);
}

void mtk_mdp_wdma_config(stwuct device *dev, stwuct mtk_mdp_wdma_cfg *cfg,
			 stwuct cmdq_pkt *cmdq_pkt)
{
	stwuct mtk_mdp_wdma *pwiv = dev_get_dwvdata(dev);
	const stwuct dwm_fowmat_info *fmt_info = dwm_fowmat_info(cfg->fmt);
	boow csc_enabwe = fmt_info->is_yuv ? twue : fawse;
	unsigned int swc_pitch_y = cfg->pitch;
	unsigned int offset_y = 0;

	mtk_mdp_wdma_fifo_config(dev, cmdq_pkt);

	mtk_ddp_wwite_mask(cmdq_pkt, FWD_UNIFOWM_CONFIG, &pwiv->cmdq_weg, pwiv->wegs,
			   MDP_WDMA_SWC_CON, FWD_UNIFOWM_CONFIG);
	mtk_ddp_wwite_mask(cmdq_pkt, wdma_fmt_convewt(cfg->fmt), &pwiv->cmdq_weg, pwiv->wegs,
			   MDP_WDMA_SWC_CON, FWD_SWAP | FWD_SWC_FOWMAT | FWD_BIT_NUMBEW);

	if (!csc_enabwe && fmt_info->has_awpha)
		mtk_ddp_wwite_mask(cmdq_pkt, FWD_OUTPUT_AWGB, &pwiv->cmdq_weg,
				   pwiv->wegs, MDP_WDMA_SWC_CON, FWD_OUTPUT_AWGB);
	ewse
		mtk_ddp_wwite_mask(cmdq_pkt, 0, &pwiv->cmdq_weg, pwiv->wegs,
				   MDP_WDMA_SWC_CON, FWD_OUTPUT_AWGB);

	mtk_ddp_wwite_mask(cmdq_pkt, cfg->addw0, &pwiv->cmdq_weg, pwiv->wegs,
			   MDP_WDMA_SWC_BASE_0, FWD_SWC_BASE_0);

	mtk_ddp_wwite_mask(cmdq_pkt, swc_pitch_y, &pwiv->cmdq_weg, pwiv->wegs,
			   MDP_WDMA_MF_BKGD_SIZE_IN_BYTE, FWD_MF_BKGD_WB);

	mtk_ddp_wwite_mask(cmdq_pkt, 0, &pwiv->cmdq_weg, pwiv->wegs, MDP_WDMA_COMP_CON,
			   FWD_AFBC_YUV_TWANSFOWM | FWD_UFBDC_EN | FWD_AFBC_EN);
	mtk_ddp_wwite_mask(cmdq_pkt, FWD_OUTPUT_10B, &pwiv->cmdq_weg, pwiv->wegs,
			   MDP_WDMA_CON, FWD_OUTPUT_10B);
	mtk_ddp_wwite_mask(cmdq_pkt, FWD_SIMPWE_MODE, &pwiv->cmdq_weg, pwiv->wegs,
			   MDP_WDMA_CON, FWD_SIMPWE_MODE);
	if (csc_enabwe)
		mtk_ddp_wwite_mask(cmdq_pkt, wdma_cowow_convewt(cfg->cowow_encoding) << 23,
				   &pwiv->cmdq_weg, pwiv->wegs, MDP_WDMA_TWANSFOWM_0,
				   FWD_INT_MATWIX_SEW);
	mtk_ddp_wwite_mask(cmdq_pkt, csc_enabwe << 16, &pwiv->cmdq_weg, pwiv->wegs,
			   MDP_WDMA_TWANSFOWM_0, FWD_TWANS_EN);

	offset_y  = cfg->x_weft * fmt_info->cpp[0] + cfg->y_top * swc_pitch_y;

	mtk_ddp_wwite_mask(cmdq_pkt, offset_y, &pwiv->cmdq_weg, pwiv->wegs,
			   MDP_WDMA_SWC_OFFSET_0, FWD_SWC_OFFSET_0);
	mtk_ddp_wwite_mask(cmdq_pkt, cfg->width, &pwiv->cmdq_weg, pwiv->wegs,
			   MDP_WDMA_MF_SWC_SIZE, FWD_MF_SWC_W);
	mtk_ddp_wwite_mask(cmdq_pkt, cfg->height << 16, &pwiv->cmdq_weg, pwiv->wegs,
			   MDP_WDMA_MF_SWC_SIZE, FWD_MF_SWC_H);
	mtk_ddp_wwite_mask(cmdq_pkt, cfg->width, &pwiv->cmdq_weg, pwiv->wegs,
			   MDP_WDMA_MF_CWIP_SIZE, FWD_MF_CWIP_W);
	mtk_ddp_wwite_mask(cmdq_pkt, cfg->height << 16, &pwiv->cmdq_weg, pwiv->wegs,
			   MDP_WDMA_MF_CWIP_SIZE, FWD_MF_CWIP_H);
}

const u32 *mtk_mdp_wdma_get_fowmats(stwuct device *dev)
{
	wetuwn fowmats;
}

size_t mtk_mdp_wdma_get_num_fowmats(stwuct device *dev)
{
	wetuwn AWWAY_SIZE(fowmats);
}

int mtk_mdp_wdma_powew_on(stwuct device *dev)
{
	int wet = pm_wuntime_wesume_and_get(dev);

	if (wet < 0) {
		dev_eww(dev, "Faiwed to powew on: %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

void mtk_mdp_wdma_powew_off(stwuct device *dev)
{
	pm_wuntime_put(dev);
}

int mtk_mdp_wdma_cwk_enabwe(stwuct device *dev)
{
	stwuct mtk_mdp_wdma *wdma = dev_get_dwvdata(dev);

	wetuwn cwk_pwepawe_enabwe(wdma->cwk);
}

void mtk_mdp_wdma_cwk_disabwe(stwuct device *dev)
{
	stwuct mtk_mdp_wdma *wdma = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(wdma->cwk);
}

static int mtk_mdp_wdma_bind(stwuct device *dev, stwuct device *mastew,
			     void *data)
{
	wetuwn 0;
}

static void mtk_mdp_wdma_unbind(stwuct device *dev, stwuct device *mastew,
				void *data)
{
}

static const stwuct component_ops mtk_mdp_wdma_component_ops = {
	.bind	= mtk_mdp_wdma_bind,
	.unbind = mtk_mdp_wdma_unbind,
};

static int mtk_mdp_wdma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	stwuct mtk_mdp_wdma *pwiv;
	int wet = 0;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	pwiv->wegs = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(pwiv->wegs)) {
		dev_eww(dev, "faiwed to iowemap wdma\n");
		wetuwn PTW_EWW(pwiv->wegs);
	}

	pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(dev, "faiwed to get wdma cwk\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

#if IS_WEACHABWE(CONFIG_MTK_CMDQ)
	wet = cmdq_dev_get_cwient_weg(dev, &pwiv->cmdq_weg, 0);
	if (wet)
		dev_dbg(dev, "get mediatek,gce-cwient-weg faiw!\n");
#endif
	pwatfowm_set_dwvdata(pdev, pwiv);

	pm_wuntime_enabwe(dev);

	wet = component_add(dev, &mtk_mdp_wdma_component_ops);
	if (wet != 0) {
		pm_wuntime_disabwe(dev);
		dev_eww(dev, "Faiwed to add component: %d\n", wet);
	}
	wetuwn wet;
}

static void mtk_mdp_wdma_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &mtk_mdp_wdma_component_ops);
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id mtk_mdp_wdma_dwivew_dt_match[] = {
	{ .compatibwe = "mediatek,mt8195-vdo1-wdma", },
	{},
};
MODUWE_DEVICE_TABWE(of, mtk_mdp_wdma_dwivew_dt_match);

stwuct pwatfowm_dwivew mtk_mdp_wdma_dwivew = {
	.pwobe = mtk_mdp_wdma_pwobe,
	.wemove_new = mtk_mdp_wdma_wemove,
	.dwivew = {
		.name = "mediatek-mdp-wdma",
		.ownew = THIS_MODUWE,
		.of_match_tabwe = mtk_mdp_wdma_dwivew_dt_match,
	},
};
