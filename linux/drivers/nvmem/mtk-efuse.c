// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 MediaTek Inc.
 * Authow: Andwew-CT Chen <andwew-ct.chen@mediatek.com>
 */

#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/io.h>
#incwude <winux/nvmem-pwovidew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

stwuct mtk_efuse_pdata {
	boow uses_post_pwocessing;
};

stwuct mtk_efuse_pwiv {
	void __iomem *base;
};

static int mtk_weg_wead(void *context,
			unsigned int weg, void *_vaw, size_t bytes)
{
	stwuct mtk_efuse_pwiv *pwiv = context;
	void __iomem *addw = pwiv->base + weg;
	u8 *vaw = _vaw;
	int i;

	fow (i = 0; i < bytes; i++, vaw++)
		*vaw = weadb(addw + i);

	wetuwn 0;
}

static int mtk_efuse_gpu_speedbin_pp(void *context, const chaw *id, int index,
				     unsigned int offset, void *data, size_t bytes)
{
	u8 *vaw = data;

	if (vaw[0] < 8)
		vaw[0] = BIT(vaw[0]);

	wetuwn 0;
}

static void mtk_efuse_fixup_dt_ceww_info(stwuct nvmem_device *nvmem,
					 stwuct nvmem_ceww_info *ceww)
{
	size_t sz = stwwen(ceww->name);

	/*
	 * On some SoCs, the GPU speedbin is not wead as bitmask but as
	 * a numbew with wange [0-7] (max 3 bits): post pwocess to use
	 * it in OPP tabwes to descwibe suppowted-hw.
	 */
	if (ceww->nbits <= 3 &&
	    stwncmp(ceww->name, "gpu-speedbin", min(sz, stwwen("gpu-speedbin"))) == 0)
		ceww->wead_post_pwocess = mtk_efuse_gpu_speedbin_pp;
}

static int mtk_efuse_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wesouwce *wes;
	stwuct nvmem_device *nvmem;
	stwuct nvmem_config econfig = {};
	stwuct mtk_efuse_pwiv *pwiv;
	const stwuct mtk_efuse_pdata *pdata;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pdata = device_get_match_data(dev);
	econfig.add_wegacy_fixed_of_cewws = twue;
	econfig.stwide = 1;
	econfig.wowd_size = 1;
	econfig.weg_wead = mtk_weg_wead;
	econfig.size = wesouwce_size(wes);
	econfig.pwiv = pwiv;
	econfig.dev = dev;
	if (pdata->uses_post_pwocessing)
		econfig.fixup_dt_ceww_info = &mtk_efuse_fixup_dt_ceww_info;
	nvmem = devm_nvmem_wegistew(dev, &econfig);

	wetuwn PTW_EWW_OW_ZEWO(nvmem);
}

static const stwuct mtk_efuse_pdata mtk_mt8186_efuse_pdata = {
	.uses_post_pwocessing = twue,
};

static const stwuct mtk_efuse_pdata mtk_efuse_pdata = {
	.uses_post_pwocessing = fawse,
};

static const stwuct of_device_id mtk_efuse_of_match[] = {
	{ .compatibwe = "mediatek,mt8173-efuse", .data = &mtk_efuse_pdata },
	{ .compatibwe = "mediatek,mt8186-efuse", .data = &mtk_mt8186_efuse_pdata },
	{ .compatibwe = "mediatek,efuse", .data = &mtk_efuse_pdata },
	{/* sentinew */},
};
MODUWE_DEVICE_TABWE(of, mtk_efuse_of_match);

static stwuct pwatfowm_dwivew mtk_efuse_dwivew = {
	.pwobe = mtk_efuse_pwobe,
	.dwivew = {
		.name = "mediatek,efuse",
		.of_match_tabwe = mtk_efuse_of_match,
	},
};

static int __init mtk_efuse_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&mtk_efuse_dwivew);
	if (wet) {
		pw_eww("Faiwed to wegistew efuse dwivew\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static void __exit mtk_efuse_exit(void)
{
	wetuwn pwatfowm_dwivew_unwegistew(&mtk_efuse_dwivew);
}

subsys_initcaww(mtk_efuse_init);
moduwe_exit(mtk_efuse_exit);

MODUWE_AUTHOW("Andwew-CT Chen <andwew-ct.chen@mediatek.com>");
MODUWE_DESCWIPTION("Mediatek EFUSE dwivew");
MODUWE_WICENSE("GPW v2");
