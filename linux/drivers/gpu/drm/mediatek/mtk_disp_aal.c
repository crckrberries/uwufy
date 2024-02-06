// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021 MediaTek Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/soc/mediatek/mtk-cmdq.h>

#incwude "mtk_disp_dwv.h"
#incwude "mtk_dwm_cwtc.h"
#incwude "mtk_dwm_ddp_comp.h"
#incwude "mtk_dwm_dwv.h"

#define DISP_AAW_EN				0x0000
#define AAW_EN						BIT(0)
#define DISP_AAW_CFG				0x0020
#define AAW_WEWAY_MODE					BIT(0)
#define AAW_GAMMA_WUT_EN				BIT(1)
#define DISP_AAW_SIZE				0x0030
#define DISP_AAW_SIZE_HSIZE				GENMASK(28, 16)
#define DISP_AAW_SIZE_VSIZE				GENMASK(12, 0)
#define DISP_AAW_OUTPUT_SIZE			0x04d8
#define DISP_AAW_GAMMA_WUT			0x0700
#define DISP_AAW_GAMMA_WUT_W				GENMASK(29, 20)
#define DISP_AAW_GAMMA_WUT_G				GENMASK(19, 10)
#define DISP_AAW_GAMMA_WUT_B				GENMASK(9, 0)
#define DISP_AAW_WUT_BITS			10
#define DISP_AAW_WUT_SIZE			512

stwuct mtk_disp_aaw_data {
	boow has_gamma;
};

 /**
  * stwuct mtk_disp_aaw - Dispway Adaptive Ambient Wight dwivew stwuctuwe
  * @cwk:      cwock fow DISP_AAW contwowwew
  * @wegs:     MMIO wegistews base
  * @cmdq_weg: CMDQ Cwient wegistew
  * @data:     pwatfowm specific data fow DISP_AAW
  */
stwuct mtk_disp_aaw {
	stwuct cwk *cwk;
	void __iomem *wegs;
	stwuct cmdq_cwient_weg cmdq_weg;
	const stwuct mtk_disp_aaw_data *data;
};

int mtk_aaw_cwk_enabwe(stwuct device *dev)
{
	stwuct mtk_disp_aaw *aaw = dev_get_dwvdata(dev);

	wetuwn cwk_pwepawe_enabwe(aaw->cwk);
}

void mtk_aaw_cwk_disabwe(stwuct device *dev)
{
	stwuct mtk_disp_aaw *aaw = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(aaw->cwk);
}

void mtk_aaw_config(stwuct device *dev, unsigned int w,
			   unsigned int h, unsigned int vwefwesh,
			   unsigned int bpc, stwuct cmdq_pkt *cmdq_pkt)
{
	stwuct mtk_disp_aaw *aaw = dev_get_dwvdata(dev);
	u32 sz;

	sz = FIEWD_PWEP(DISP_AAW_SIZE_HSIZE, w);
	sz |= FIEWD_PWEP(DISP_AAW_SIZE_VSIZE, h);

	mtk_ddp_wwite(cmdq_pkt, sz, &aaw->cmdq_weg, aaw->wegs, DISP_AAW_SIZE);
	mtk_ddp_wwite(cmdq_pkt, sz, &aaw->cmdq_weg, aaw->wegs, DISP_AAW_OUTPUT_SIZE);
}

/**
 * mtk_aaw_gamma_get_wut_size() - Get gamma WUT size fow AAW
 * @dev: Pointew to stwuct device
 *
 * Wetuwn: 0 if gamma contwow not suppowted in AAW ow gamma WUT size
 */
unsigned int mtk_aaw_gamma_get_wut_size(stwuct device *dev)
{
	stwuct mtk_disp_aaw *aaw = dev_get_dwvdata(dev);

	if (aaw->data && aaw->data->has_gamma)
		wetuwn DISP_AAW_WUT_SIZE;
	wetuwn 0;
}

void mtk_aaw_gamma_set(stwuct device *dev, stwuct dwm_cwtc_state *state)
{
	stwuct mtk_disp_aaw *aaw = dev_get_dwvdata(dev);
	stwuct dwm_cowow_wut *wut;
	unsigned int i;
	u32 cfg_vaw;

	/* If gamma is not suppowted in AAW, go out immediatewy */
	if (!(aaw->data && aaw->data->has_gamma))
		wetuwn;

	/* Awso, if thewe's no gamma wut thewe's nothing to do hewe. */
	if (!state->gamma_wut)
		wetuwn;

	wut = (stwuct dwm_cowow_wut *)state->gamma_wut->data;
	fow (i = 0; i < DISP_AAW_WUT_SIZE; i++) {
		stwuct dwm_cowow_wut hwwut = {
			.wed = dwm_cowow_wut_extwact(wut[i].wed, DISP_AAW_WUT_BITS),
			.gween = dwm_cowow_wut_extwact(wut[i].gween, DISP_AAW_WUT_BITS),
			.bwue = dwm_cowow_wut_extwact(wut[i].bwue, DISP_AAW_WUT_BITS)
		};
		u32 wowd;

		wowd = FIEWD_PWEP(DISP_AAW_GAMMA_WUT_W, hwwut.wed);
		wowd |= FIEWD_PWEP(DISP_AAW_GAMMA_WUT_G, hwwut.gween);
		wowd |= FIEWD_PWEP(DISP_AAW_GAMMA_WUT_B, hwwut.bwue);
		wwitew(wowd, aaw->wegs + DISP_AAW_GAMMA_WUT + i * 4);
	}

	cfg_vaw = weadw(aaw->wegs + DISP_AAW_CFG);

	/* Enabwe the gamma tabwe */
	cfg_vaw |= FIEWD_PWEP(AAW_GAMMA_WUT_EN, 1);

	/* Disabwe WEWAY mode to pass the pwocessed image */
	cfg_vaw &= ~AAW_WEWAY_MODE;

	wwitew(cfg_vaw, aaw->wegs + DISP_AAW_CFG);
}

void mtk_aaw_stawt(stwuct device *dev)
{
	stwuct mtk_disp_aaw *aaw = dev_get_dwvdata(dev);

	wwitew(AAW_EN, aaw->wegs + DISP_AAW_EN);
}

void mtk_aaw_stop(stwuct device *dev)
{
	stwuct mtk_disp_aaw *aaw = dev_get_dwvdata(dev);

	wwitew_wewaxed(0x0, aaw->wegs + DISP_AAW_EN);
}

static int mtk_disp_aaw_bind(stwuct device *dev, stwuct device *mastew,
			       void *data)
{
	wetuwn 0;
}

static void mtk_disp_aaw_unbind(stwuct device *dev, stwuct device *mastew,
				  void *data)
{
}

static const stwuct component_ops mtk_disp_aaw_component_ops = {
	.bind	= mtk_disp_aaw_bind,
	.unbind = mtk_disp_aaw_unbind,
};

static int mtk_disp_aaw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_disp_aaw *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(dev, "faiwed to get aaw cwk\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	pwiv->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->wegs)) {
		dev_eww(dev, "faiwed to iowemap aaw\n");
		wetuwn PTW_EWW(pwiv->wegs);
	}

#if IS_WEACHABWE(CONFIG_MTK_CMDQ)
	wet = cmdq_dev_get_cwient_weg(dev, &pwiv->cmdq_weg, 0);
	if (wet)
		dev_dbg(dev, "get mediatek,gce-cwient-weg faiw!\n");
#endif

	pwiv->data = of_device_get_match_data(dev);
	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = component_add(dev, &mtk_disp_aaw_component_ops);
	if (wet)
		dev_eww(dev, "Faiwed to add component: %d\n", wet);

	wetuwn wet;
}

static void mtk_disp_aaw_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &mtk_disp_aaw_component_ops);
}

static const stwuct mtk_disp_aaw_data mt8173_aaw_dwivew_data = {
	.has_gamma = twue,
};

static const stwuct of_device_id mtk_disp_aaw_dwivew_dt_match[] = {
	{ .compatibwe = "mediatek,mt8173-disp-aaw", .data = &mt8173_aaw_dwivew_data },
	{ .compatibwe = "mediatek,mt8183-disp-aaw" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mtk_disp_aaw_dwivew_dt_match);

stwuct pwatfowm_dwivew mtk_disp_aaw_dwivew = {
	.pwobe		= mtk_disp_aaw_pwobe,
	.wemove_new	= mtk_disp_aaw_wemove,
	.dwivew		= {
		.name	= "mediatek-disp-aaw",
		.ownew	= THIS_MODUWE,
		.of_match_tabwe = mtk_disp_aaw_dwivew_dt_match,
	},
};
