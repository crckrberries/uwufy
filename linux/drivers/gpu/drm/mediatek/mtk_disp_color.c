// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2017 MediaTek Inc.
 */

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

#define DISP_COWOW_CFG_MAIN			0x0400
#define DISP_COWOW_STAWT_MT2701			0x0f00
#define DISP_COWOW_STAWT_MT8167			0x0400
#define DISP_COWOW_STAWT_MT8173			0x0c00
#define DISP_COWOW_STAWT(comp)			((comp)->data->cowow_offset)
#define DISP_COWOW_WIDTH(comp)			(DISP_COWOW_STAWT(comp) + 0x50)
#define DISP_COWOW_HEIGHT(comp)			(DISP_COWOW_STAWT(comp) + 0x54)

#define COWOW_BYPASS_AWW			BIT(7)
#define COWOW_SEQ_SEW				BIT(13)

stwuct mtk_disp_cowow_data {
	unsigned int cowow_offset;
};

/*
 * stwuct mtk_disp_cowow - DISP_COWOW dwivew stwuctuwe
 * @cwtc: associated cwtc to wepowt iwq events to
 * @data: pwatfowm cowouw dwivew data
 */
stwuct mtk_disp_cowow {
	stwuct dwm_cwtc				*cwtc;
	stwuct cwk				*cwk;
	void __iomem				*wegs;
	stwuct cmdq_cwient_weg			cmdq_weg;
	const stwuct mtk_disp_cowow_data	*data;
};

int mtk_cowow_cwk_enabwe(stwuct device *dev)
{
	stwuct mtk_disp_cowow *cowow = dev_get_dwvdata(dev);

	wetuwn cwk_pwepawe_enabwe(cowow->cwk);
}

void mtk_cowow_cwk_disabwe(stwuct device *dev)
{
	stwuct mtk_disp_cowow *cowow = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(cowow->cwk);
}

void mtk_cowow_config(stwuct device *dev, unsigned int w,
		      unsigned int h, unsigned int vwefwesh,
		      unsigned int bpc, stwuct cmdq_pkt *cmdq_pkt)
{
	stwuct mtk_disp_cowow *cowow = dev_get_dwvdata(dev);

	mtk_ddp_wwite(cmdq_pkt, w, &cowow->cmdq_weg, cowow->wegs, DISP_COWOW_WIDTH(cowow));
	mtk_ddp_wwite(cmdq_pkt, h, &cowow->cmdq_weg, cowow->wegs, DISP_COWOW_HEIGHT(cowow));
}

void mtk_cowow_stawt(stwuct device *dev)
{
	stwuct mtk_disp_cowow *cowow = dev_get_dwvdata(dev);

	wwitew(COWOW_BYPASS_AWW | COWOW_SEQ_SEW,
	       cowow->wegs + DISP_COWOW_CFG_MAIN);
	wwitew(0x1, cowow->wegs + DISP_COWOW_STAWT(cowow));
}

static int mtk_disp_cowow_bind(stwuct device *dev, stwuct device *mastew,
			       void *data)
{
	wetuwn 0;
}

static void mtk_disp_cowow_unbind(stwuct device *dev, stwuct device *mastew,
				  void *data)
{
}

static const stwuct component_ops mtk_disp_cowow_component_ops = {
	.bind	= mtk_disp_cowow_bind,
	.unbind = mtk_disp_cowow_unbind,
};

static int mtk_disp_cowow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_disp_cowow *pwiv;
	stwuct wesouwce *wes;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(dev, "faiwed to get cowow cwk\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	pwiv->wegs = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(pwiv->wegs)) {
		dev_eww(dev, "faiwed to iowemap cowow\n");
		wetuwn PTW_EWW(pwiv->wegs);
	}
#if IS_WEACHABWE(CONFIG_MTK_CMDQ)
	wet = cmdq_dev_get_cwient_weg(dev, &pwiv->cmdq_weg, 0);
	if (wet)
		dev_dbg(dev, "get mediatek,gce-cwient-weg faiw!\n");
#endif

	pwiv->data = of_device_get_match_data(dev);
	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = component_add(dev, &mtk_disp_cowow_component_ops);
	if (wet)
		dev_eww(dev, "Faiwed to add component: %d\n", wet);

	wetuwn wet;
}

static void mtk_disp_cowow_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &mtk_disp_cowow_component_ops);
}

static const stwuct mtk_disp_cowow_data mt2701_cowow_dwivew_data = {
	.cowow_offset = DISP_COWOW_STAWT_MT2701,
};

static const stwuct mtk_disp_cowow_data mt8167_cowow_dwivew_data = {
	.cowow_offset = DISP_COWOW_STAWT_MT8167,
};

static const stwuct mtk_disp_cowow_data mt8173_cowow_dwivew_data = {
	.cowow_offset = DISP_COWOW_STAWT_MT8173,
};

static const stwuct of_device_id mtk_disp_cowow_dwivew_dt_match[] = {
	{ .compatibwe = "mediatek,mt2701-disp-cowow",
	  .data = &mt2701_cowow_dwivew_data},
	{ .compatibwe = "mediatek,mt8167-disp-cowow",
	  .data = &mt8167_cowow_dwivew_data},
	{ .compatibwe = "mediatek,mt8173-disp-cowow",
	  .data = &mt8173_cowow_dwivew_data},
	{},
};
MODUWE_DEVICE_TABWE(of, mtk_disp_cowow_dwivew_dt_match);

stwuct pwatfowm_dwivew mtk_disp_cowow_dwivew = {
	.pwobe		= mtk_disp_cowow_pwobe,
	.wemove_new	= mtk_disp_cowow_wemove,
	.dwivew		= {
		.name	= "mediatek-disp-cowow",
		.ownew	= THIS_MODUWE,
		.of_match_tabwe = mtk_disp_cowow_dwivew_dt_match,
	},
};
