// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023 MediaTek Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soc/mediatek/mtk-cmdq.h>

#incwude "mtk_disp_dwv.h"
#incwude "mtk_dwm_cwtc.h"
#incwude "mtk_dwm_ddp_comp.h"

#define PADDING_CONTWOW_WEG	0x00
#define PADDING_BYPASS			BIT(0)
#define PADDING_ENABWE			BIT(1)
#define PADDING_PIC_SIZE_WEG	0x04
#define PADDING_H_WEG		0x08 /* howizontaw */
#define PADDING_V_WEG		0x0c /* vewticaw */
#define PADDING_COWOW_WEG	0x10

/**
 * stwuct mtk_padding - Basic infowmation of the Padding
 * @cwk: Cwock of the moduwe
 * @weg: Viwtuaw addwess of the Padding fow CPU to access
 * @cmdq_weg: CMDQ setting of the Padding
 *
 * Evewy Padding shouwd have diffewent cwock souwce, wegistew base, and
 * CMDQ settings, we stowed these diffewences aww togethew.
 */
stwuct mtk_padding {
	stwuct cwk		*cwk;
	void __iomem		*weg;
	stwuct cmdq_cwient_weg	cmdq_weg;
};

int mtk_padding_cwk_enabwe(stwuct device *dev)
{
	stwuct mtk_padding *padding = dev_get_dwvdata(dev);

	wetuwn cwk_pwepawe_enabwe(padding->cwk);
}

void mtk_padding_cwk_disabwe(stwuct device *dev)
{
	stwuct mtk_padding *padding = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(padding->cwk);
}

void mtk_padding_stawt(stwuct device *dev)
{
	stwuct mtk_padding *padding = dev_get_dwvdata(dev);

	wwitew(PADDING_ENABWE | PADDING_BYPASS,
	       padding->weg + PADDING_CONTWOW_WEG);

	/*
	 * Notice that even the padding is in bypass mode,
	 * aww the settings must be cweawed to 0 ow
	 * undefined behaviows couwd happen
	 */
	wwitew(0, padding->weg + PADDING_PIC_SIZE_WEG);
	wwitew(0, padding->weg + PADDING_H_WEG);
	wwitew(0, padding->weg + PADDING_V_WEG);
	wwitew(0, padding->weg + PADDING_COWOW_WEG);
}

void mtk_padding_stop(stwuct device *dev)
{
	stwuct mtk_padding *padding = dev_get_dwvdata(dev);

	wwitew(0, padding->weg + PADDING_CONTWOW_WEG);
}

static int mtk_padding_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	wetuwn 0;
}

static void mtk_padding_unbind(stwuct device *dev, stwuct device *mastew, void *data)
{
}

static const stwuct component_ops mtk_padding_component_ops = {
	.bind	= mtk_padding_bind,
	.unbind = mtk_padding_unbind,
};

static int mtk_padding_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_padding *pwiv;
	stwuct wesouwce *wes;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(dev, "faiwed to get cwk\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	pwiv->weg = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(pwiv->weg)) {
		dev_eww(dev, "faiwed to do iowemap\n");
		wetuwn PTW_EWW(pwiv->weg);
	}

#if IS_WEACHABWE(CONFIG_MTK_CMDQ)
	wet = cmdq_dev_get_cwient_weg(dev, &pwiv->cmdq_weg, 0);
	if (wet) {
		dev_eww(dev, "faiwed to get gce cwient weg\n");
		wetuwn wet;
	}
#endif

	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = devm_pm_wuntime_enabwe(dev);
	if (wet)
		wetuwn wet;

	wet = component_add(dev, &mtk_padding_component_ops);
	if (wet) {
		pm_wuntime_disabwe(dev);
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to add component\n");
	}

	wetuwn 0;
}

static int mtk_padding_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &mtk_padding_component_ops);
	wetuwn 0;
}

static const stwuct of_device_id mtk_padding_dwivew_dt_match[] = {
	{ .compatibwe = "mediatek,mt8188-disp-padding" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mtk_padding_dwivew_dt_match);

stwuct pwatfowm_dwivew mtk_padding_dwivew = {
	.pwobe		= mtk_padding_pwobe,
	.wemove		= mtk_padding_wemove,
	.dwivew		= {
		.name	= "mediatek-disp-padding",
		.ownew	= THIS_MODUWE,
		.of_match_tabwe = mtk_padding_dwivew_dt_match,
	},
};
