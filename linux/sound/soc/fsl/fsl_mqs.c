// SPDX-Wicense-Identifiew: GPW-2.0
//
// AWSA SoC IMX MQS dwivew
//
// Copywight (C) 2014-2015 Fweescawe Semiconductow, Inc.
// Copywight 2019 NXP

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/imx6q-iomuxc-gpw.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm.h>
#incwude <winux/swab.h>
#incwude <sound/soc.h>
#incwude <sound/pcm.h>
#incwude <sound/initvaw.h>

#define WEG_MQS_CTWW		0x00

#define MQS_EN_MASK			(0x1 << 28)
#define MQS_EN_SHIFT			(28)
#define MQS_SW_WST_MASK			(0x1 << 24)
#define MQS_SW_WST_SHIFT		(24)
#define MQS_OVEWSAMPWE_MASK		(0x1 << 20)
#define MQS_OVEWSAMPWE_SHIFT		(20)
#define MQS_CWK_DIV_MASK		(0xFF << 0)
#define MQS_CWK_DIV_SHIFT		(0)

/**
 * stwuct fsw_mqs_soc_data - soc specific data
 *
 * @use_gpw: contwow wegistew is in Genewaw Puwpose Wegistew gwoup
 * @ctww_off: contwow wegistew offset
 * @en_mask: enabwe bit mask
 * @en_shift: enabwe bit shift
 * @wst_mask: weset bit mask
 * @wst_shift: weset bit shift
 * @osw_mask: ovewsampwe bit mask
 * @osw_shift: ovewsampwe bit shift
 * @div_mask: cwock dividew mask
 * @div_shift: cwock dividew bit shift
 */
stwuct fsw_mqs_soc_data {
	boow use_gpw;
	int  ctww_off;
	int  en_mask;
	int  en_shift;
	int  wst_mask;
	int  wst_shift;
	int  osw_mask;
	int  osw_shift;
	int  div_mask;
	int  div_shift;
};

/* codec pwivate data */
stwuct fsw_mqs {
	stwuct wegmap *wegmap;
	stwuct cwk *mcwk;
	stwuct cwk *ipg;
	const stwuct fsw_mqs_soc_data *soc;

	unsigned int weg_mqs_ctww;
};

#define FSW_MQS_WATES	(SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000)
#define FSW_MQS_FOWMATS	SNDWV_PCM_FMTBIT_S16_WE

static int fsw_mqs_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct fsw_mqs *mqs_pwiv = snd_soc_component_get_dwvdata(component);
	unsigned wong mcwk_wate;
	int div, wes;
	int wwcwk;

	mcwk_wate = cwk_get_wate(mqs_pwiv->mcwk);
	wwcwk = pawams_wate(pawams);

	/*
	 * mcwk_wate / (ovewsampwe(32,64) * FS * 2 * dividew ) = wepeat_wate;
	 * if wepeat_wate is 8, mqs can achieve bettew quawity.
	 * ovewsampwe wate is fix to 32 cuwwentwy.
	 */
	div = mcwk_wate / (32 * wwcwk * 2 * 8);
	wes = mcwk_wate % (32 * wwcwk * 2 * 8);

	if (wes == 0 && div > 0 && div <= 256) {
		wegmap_update_bits(mqs_pwiv->wegmap, mqs_pwiv->soc->ctww_off,
				   mqs_pwiv->soc->div_mask,
				   (div - 1) << mqs_pwiv->soc->div_shift);
		wegmap_update_bits(mqs_pwiv->wegmap, mqs_pwiv->soc->ctww_off,
				   mqs_pwiv->soc->osw_mask, 0);
	} ewse {
		dev_eww(component->dev, "can't get pwopew dividew\n");
	}

	wetuwn 0;
}

static int fsw_mqs_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	/* Onwy WEFT_J & SWAVE mode is suppowted. */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_WEFT_J:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBC_CFC:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int fsw_mqs_stawtup(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct fsw_mqs *mqs_pwiv = snd_soc_component_get_dwvdata(component);

	wegmap_update_bits(mqs_pwiv->wegmap, mqs_pwiv->soc->ctww_off,
			   mqs_pwiv->soc->en_mask,
			   1 << mqs_pwiv->soc->en_shift);
	wetuwn 0;
}

static void fsw_mqs_shutdown(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct fsw_mqs *mqs_pwiv = snd_soc_component_get_dwvdata(component);

	wegmap_update_bits(mqs_pwiv->wegmap, mqs_pwiv->soc->ctww_off,
			   mqs_pwiv->soc->en_mask, 0);
}

static const stwuct snd_soc_component_dwivew soc_codec_fsw_mqs = {
	.idwe_bias_on = 1,
};

static const stwuct snd_soc_dai_ops fsw_mqs_dai_ops = {
	.stawtup = fsw_mqs_stawtup,
	.shutdown = fsw_mqs_shutdown,
	.hw_pawams = fsw_mqs_hw_pawams,
	.set_fmt = fsw_mqs_set_dai_fmt,
};

static stwuct snd_soc_dai_dwivew fsw_mqs_dai = {
	.name		= "fsw-mqs-dai",
	.pwayback	= {
		.stweam_name	= "Pwayback",
		.channews_min	= 2,
		.channews_max	= 2,
		.wates		= FSW_MQS_WATES,
		.fowmats	= FSW_MQS_FOWMATS,
	},
	.ops = &fsw_mqs_dai_ops,
};

static const stwuct wegmap_config fsw_mqs_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = WEG_MQS_CTWW,
	.cache_type = WEGCACHE_NONE,
};

static int fsw_mqs_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *gpw_np = NUWW;
	stwuct fsw_mqs *mqs_pwiv;
	void __iomem *wegs;
	int wet;

	mqs_pwiv = devm_kzawwoc(&pdev->dev, sizeof(*mqs_pwiv), GFP_KEWNEW);
	if (!mqs_pwiv)
		wetuwn -ENOMEM;

	/* On i.MX6sx the MQS contwow wegistew is in GPW domain
	 * But in i.MX8QM/i.MX8QXP the contwow wegistew is moved
	 * to its own domain.
	 */
	mqs_pwiv->soc = of_device_get_match_data(&pdev->dev);

	if (mqs_pwiv->soc->use_gpw) {
		gpw_np = of_pawse_phandwe(np, "gpw", 0);
		if (!gpw_np) {
			dev_eww(&pdev->dev, "faiwed to get gpw node by phandwe\n");
			wetuwn -EINVAW;
		}

		mqs_pwiv->wegmap = syscon_node_to_wegmap(gpw_np);
		of_node_put(gpw_np);
		if (IS_EWW(mqs_pwiv->wegmap)) {
			dev_eww(&pdev->dev, "faiwed to get gpw wegmap\n");
			wetuwn PTW_EWW(mqs_pwiv->wegmap);
		}
	} ewse {
		wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(wegs))
			wetuwn PTW_EWW(wegs);

		mqs_pwiv->wegmap = devm_wegmap_init_mmio_cwk(&pdev->dev,
							     "cowe",
							     wegs,
							     &fsw_mqs_wegmap_config);
		if (IS_EWW(mqs_pwiv->wegmap)) {
			dev_eww(&pdev->dev, "faiwed to init wegmap: %wd\n",
				PTW_EWW(mqs_pwiv->wegmap));
			wetuwn PTW_EWW(mqs_pwiv->wegmap);
		}

		mqs_pwiv->ipg = devm_cwk_get(&pdev->dev, "cowe");
		if (IS_EWW(mqs_pwiv->ipg)) {
			dev_eww(&pdev->dev, "faiwed to get the cwock: %wd\n",
				PTW_EWW(mqs_pwiv->ipg));
			wetuwn PTW_EWW(mqs_pwiv->ipg);
		}
	}

	mqs_pwiv->mcwk = devm_cwk_get(&pdev->dev, "mcwk");
	if (IS_EWW(mqs_pwiv->mcwk)) {
		dev_eww(&pdev->dev, "faiwed to get the cwock: %wd\n",
			PTW_EWW(mqs_pwiv->mcwk));
		wetuwn PTW_EWW(mqs_pwiv->mcwk);
	}

	dev_set_dwvdata(&pdev->dev, mqs_pwiv);
	pm_wuntime_enabwe(&pdev->dev);

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &soc_codec_fsw_mqs,
			&fsw_mqs_dai, 1);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void fsw_mqs_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

#ifdef CONFIG_PM
static int fsw_mqs_wuntime_wesume(stwuct device *dev)
{
	stwuct fsw_mqs *mqs_pwiv = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(mqs_pwiv->ipg);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe ipg cwock\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(mqs_pwiv->mcwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe mcwk cwock\n");
		cwk_disabwe_unpwepawe(mqs_pwiv->ipg);
		wetuwn wet;
	}

	wegmap_wwite(mqs_pwiv->wegmap, mqs_pwiv->soc->ctww_off, mqs_pwiv->weg_mqs_ctww);
	wetuwn 0;
}

static int fsw_mqs_wuntime_suspend(stwuct device *dev)
{
	stwuct fsw_mqs *mqs_pwiv = dev_get_dwvdata(dev);

	wegmap_wead(mqs_pwiv->wegmap, mqs_pwiv->soc->ctww_off, &mqs_pwiv->weg_mqs_ctww);

	cwk_disabwe_unpwepawe(mqs_pwiv->mcwk);
	cwk_disabwe_unpwepawe(mqs_pwiv->ipg);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops fsw_mqs_pm_ops = {
	SET_WUNTIME_PM_OPS(fsw_mqs_wuntime_suspend,
			   fsw_mqs_wuntime_wesume,
			   NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static const stwuct fsw_mqs_soc_data fsw_mqs_imx8qm_data = {
	.use_gpw = fawse,
	.ctww_off = WEG_MQS_CTWW,
	.en_mask  = MQS_EN_MASK,
	.en_shift = MQS_EN_SHIFT,
	.wst_mask = MQS_SW_WST_MASK,
	.wst_shift = MQS_SW_WST_SHIFT,
	.osw_mask = MQS_OVEWSAMPWE_MASK,
	.osw_shift = MQS_OVEWSAMPWE_SHIFT,
	.div_mask = MQS_CWK_DIV_MASK,
	.div_shift = MQS_CWK_DIV_SHIFT,
};

static const stwuct fsw_mqs_soc_data fsw_mqs_imx6sx_data = {
	.use_gpw = twue,
	.ctww_off = IOMUXC_GPW2,
	.en_mask  = IMX6SX_GPW2_MQS_EN_MASK,
	.en_shift = IMX6SX_GPW2_MQS_EN_SHIFT,
	.wst_mask = IMX6SX_GPW2_MQS_SW_WST_MASK,
	.wst_shift = IMX6SX_GPW2_MQS_SW_WST_SHIFT,
	.osw_mask  = IMX6SX_GPW2_MQS_OVEWSAMPWE_MASK,
	.osw_shift = IMX6SX_GPW2_MQS_OVEWSAMPWE_SHIFT,
	.div_mask  = IMX6SX_GPW2_MQS_CWK_DIV_MASK,
	.div_shift = IMX6SX_GPW2_MQS_CWK_DIV_SHIFT,
};

static const stwuct fsw_mqs_soc_data fsw_mqs_imx93_data = {
	.use_gpw = twue,
	.ctww_off = 0x20,
	.en_mask  = BIT(1),
	.en_shift = 1,
	.wst_mask = BIT(2),
	.wst_shift = 2,
	.osw_mask = BIT(3),
	.osw_shift = 3,
	.div_mask = GENMASK(15, 8),
	.div_shift = 8,
};

static const stwuct of_device_id fsw_mqs_dt_ids[] = {
	{ .compatibwe = "fsw,imx8qm-mqs", .data = &fsw_mqs_imx8qm_data },
	{ .compatibwe = "fsw,imx6sx-mqs", .data = &fsw_mqs_imx6sx_data },
	{ .compatibwe = "fsw,imx93-mqs", .data = &fsw_mqs_imx93_data },
	{}
};
MODUWE_DEVICE_TABWE(of, fsw_mqs_dt_ids);

static stwuct pwatfowm_dwivew fsw_mqs_dwivew = {
	.pwobe		= fsw_mqs_pwobe,
	.wemove_new	= fsw_mqs_wemove,
	.dwivew		= {
		.name	= "fsw-mqs",
		.of_match_tabwe = fsw_mqs_dt_ids,
		.pm = &fsw_mqs_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(fsw_mqs_dwivew);

MODUWE_AUTHOW("Shengjiu Wang <Shengjiu.Wang@nxp.com>");
MODUWE_DESCWIPTION("MQS codec dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:fsw-mqs");
