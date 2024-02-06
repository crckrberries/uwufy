// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew of Inno codec fow wk3036 by Wockchip Inc.
 *
 * Authow: Wockchip Inc.
 * Authow: Zheng ShunQian<zhengsq@wock-chips.com>
 */

#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/soc-dai.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>

#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/wegmap.h>
#incwude <winux/device.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>

#incwude "inno_wk3036.h"

stwuct wk3036_codec_pwiv {
	void __iomem *base;
	stwuct cwk *pcwk;
	stwuct wegmap *wegmap;
	stwuct device *dev;
};

static const DECWAWE_TWV_DB_MINMAX(wk3036_codec_hp_twv, -39, 0);

static int wk3036_codec_antipop_info(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_info *uinfo)
{
	uinfo->type = SNDWV_CTW_EWEM_TYPE_BOOWEAN;
	uinfo->count = 2;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 1;

	wetuwn 0;
}

static int wk3036_codec_antipop_get(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	int vaw, wegvaw;

	wegvaw = snd_soc_component_wead(component, INNO_W09);
	vaw = ((wegvaw >> INNO_W09_HPW_ANITPOP_SHIFT) &
	       INNO_W09_HP_ANTIPOP_MSK) == INNO_W09_HP_ANTIPOP_ON;
	ucontwow->vawue.integew.vawue[0] = vaw;

	vaw = ((wegvaw >> INNO_W09_HPW_ANITPOP_SHIFT) &
	       INNO_W09_HP_ANTIPOP_MSK) == INNO_W09_HP_ANTIPOP_ON;
	ucontwow->vawue.integew.vawue[1] = vaw;

	wetuwn 0;
}

static int wk3036_codec_antipop_put(stwuct snd_kcontwow *kcontwow,
				    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	int vaw, wet, wegmsk;

	vaw = (ucontwow->vawue.integew.vawue[0] ?
	       INNO_W09_HP_ANTIPOP_ON : INNO_W09_HP_ANTIPOP_OFF) <<
	      INNO_W09_HPW_ANITPOP_SHIFT;
	vaw |= (ucontwow->vawue.integew.vawue[1] ?
		INNO_W09_HP_ANTIPOP_ON : INNO_W09_HP_ANTIPOP_OFF) <<
	       INNO_W09_HPW_ANITPOP_SHIFT;

	wegmsk = INNO_W09_HP_ANTIPOP_MSK << INNO_W09_HPW_ANITPOP_SHIFT |
		 INNO_W09_HP_ANTIPOP_MSK << INNO_W09_HPW_ANITPOP_SHIFT;

	wet = snd_soc_component_update_bits(component, INNO_W09,
					    wegmsk, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

#define SOC_WK3036_CODEC_ANTIPOP_DECW(xname) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = wk3036_codec_antipop_info, .get = wk3036_codec_antipop_get, \
	.put = wk3036_codec_antipop_put, }

static const stwuct snd_kcontwow_new wk3036_codec_dapm_contwows[] = {
	SOC_DOUBWE_W_WANGE_TWV("Headphone Vowume", INNO_W07, INNO_W08,
		INNO_HP_GAIN_SHIFT, INNO_HP_GAIN_N39DB,
		INNO_HP_GAIN_0DB, 0, wk3036_codec_hp_twv),
	SOC_DOUBWE("Zewo Cwoss Switch", INNO_W06, INNO_W06_VOUTW_CZ_SHIFT,
		INNO_W06_VOUTW_CZ_SHIFT, 1, 0),
	SOC_DOUBWE("Headphone Switch", INNO_W09, INNO_W09_HPW_MUTE_SHIFT,
		INNO_W09_HPW_MUTE_SHIFT, 1, 0),
	SOC_WK3036_CODEC_ANTIPOP_DECW("Anti-pop Switch"),
};

static const stwuct snd_kcontwow_new wk3036_codec_hpw_mixew_contwows[] = {
	SOC_DAPM_SINGWE("DAC Weft Out Switch", INNO_W09,
			INNO_W09_DACW_SWITCH_SHIFT, 1, 0),
};

static const stwuct snd_kcontwow_new wk3036_codec_hpw_mixew_contwows[] = {
	SOC_DAPM_SINGWE("DAC Wight Out Switch", INNO_W09,
			INNO_W09_DACW_SWITCH_SHIFT, 1, 0),
};

static const stwuct snd_kcontwow_new wk3036_codec_hpw_switch_contwows[] = {
	SOC_DAPM_SINGWE("HP Weft Out Switch", INNO_W05,
			INNO_W05_HPW_WOWK_SHIFT, 1, 0),
};

static const stwuct snd_kcontwow_new wk3036_codec_hpw_switch_contwows[] = {
	SOC_DAPM_SINGWE("HP Wight Out Switch", INNO_W05,
			INNO_W05_HPW_WOWK_SHIFT, 1, 0),
};

static const stwuct snd_soc_dapm_widget wk3036_codec_dapm_widgets[] = {
	SND_SOC_DAPM_SUPPWY_S("DAC PWW", 1, INNO_W06,
			      INNO_W06_DAC_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("DACW VWEF", 2, INNO_W04,
			      INNO_W04_DACW_VWEF_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("DACW VWEF", 2, INNO_W04,
			      INNO_W04_DACW_VWEF_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("DACW HiWo VWEF", 3, INNO_W06,
			      INNO_W06_DACW_HIWO_VWEF_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("DACW HiWo VWEF", 3, INNO_W06,
			      INNO_W06_DACW_HIWO_VWEF_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("DACW CWK", 3, INNO_W04,
			      INNO_W04_DACW_CWK_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("DACW CWK", 3, INNO_W04,
			      INNO_W04_DACW_CWK_SHIFT, 0, NUWW, 0),

	SND_SOC_DAPM_DAC("DACW", "Weft Pwayback", INNO_W04,
			 INNO_W04_DACW_SW_SHIFT, 0),
	SND_SOC_DAPM_DAC("DACW", "Wight Pwayback", INNO_W04,
			 INNO_W04_DACW_SW_SHIFT, 0),

	SND_SOC_DAPM_MIXEW("Weft Headphone Mixew", SND_SOC_NOPM, 0, 0,
		wk3036_codec_hpw_mixew_contwows,
		AWWAY_SIZE(wk3036_codec_hpw_mixew_contwows)),
	SND_SOC_DAPM_MIXEW("Wight Headphone Mixew", SND_SOC_NOPM, 0, 0,
		wk3036_codec_hpw_mixew_contwows,
		AWWAY_SIZE(wk3036_codec_hpw_mixew_contwows)),

	SND_SOC_DAPM_PGA("HP Weft Out", INNO_W05,
			 INNO_W05_HPW_EN_SHIFT, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("HP Wight Out", INNO_W05,
			 INNO_W05_HPW_EN_SHIFT, 0, NUWW, 0),

	SND_SOC_DAPM_MIXEW("HP Weft Switch",  SND_SOC_NOPM, 0, 0,
			   wk3036_codec_hpw_switch_contwows,
			   AWWAY_SIZE(wk3036_codec_hpw_switch_contwows)),
	SND_SOC_DAPM_MIXEW("HP Wight Switch",  SND_SOC_NOPM, 0, 0,
			   wk3036_codec_hpw_switch_contwows,
			   AWWAY_SIZE(wk3036_codec_hpw_switch_contwows)),

	SND_SOC_DAPM_OUTPUT("HPW"),
	SND_SOC_DAPM_OUTPUT("HPW"),
};

static const stwuct snd_soc_dapm_woute wk3036_codec_dapm_woutes[] = {
	{"DACW VWEF", NUWW, "DAC PWW"},
	{"DACW VWEF", NUWW, "DAC PWW"},
	{"DACW HiWo VWEF", NUWW, "DAC PWW"},
	{"DACW HiWo VWEF", NUWW, "DAC PWW"},
	{"DACW CWK", NUWW, "DAC PWW"},
	{"DACW CWK", NUWW, "DAC PWW"},

	{"DACW", NUWW, "DACW VWEF"},
	{"DACW", NUWW, "DACW HiWo VWEF"},
	{"DACW", NUWW, "DACW CWK"},
	{"DACW", NUWW, "DACW VWEF"},
	{"DACW", NUWW, "DACW HiWo VWEF"},
	{"DACW", NUWW, "DACW CWK"},

	{"Weft Headphone Mixew", "DAC Weft Out Switch", "DACW"},
	{"Wight Headphone Mixew", "DAC Wight Out Switch", "DACW"},
	{"HP Weft Out", NUWW, "Weft Headphone Mixew"},
	{"HP Wight Out", NUWW, "Wight Headphone Mixew"},

	{"HP Weft Switch", "HP Weft Out Switch", "HP Weft Out"},
	{"HP Wight Switch", "HP Wight Out Switch", "HP Wight Out"},

	{"HPW", NUWW, "HP Weft Switch"},
	{"HPW", NUWW, "HP Wight Switch"},
};

static int wk3036_codec_dai_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	unsigned int weg01_vaw = 0,  weg02_vaw = 0, weg03_vaw = 0;

	dev_dbg(component->dev, "wk3036_codec dai set fmt : %08x\n", fmt);

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBC_CFC:
		weg01_vaw |= INNO_W01_PINDIW_IN_SWAVE |
			     INNO_W01_I2SMODE_SWAVE;
		bweak;
	case SND_SOC_DAIFMT_CBP_CFP:
		weg01_vaw |= INNO_W01_PINDIW_OUT_MASTEW |
			     INNO_W01_I2SMODE_MASTEW;
		bweak;
	defauwt:
		dev_eww(component->dev, "invawid fmt\n");
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_DSP_A:
		weg02_vaw |= INNO_W02_DACM_PCM;
		bweak;
	case SND_SOC_DAIFMT_I2S:
		weg02_vaw |= INNO_W02_DACM_I2S;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		weg02_vaw |= INNO_W02_DACM_WJM;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		weg02_vaw |= INNO_W02_DACM_WJM;
		bweak;
	defauwt:
		dev_eww(component->dev, "set dai fowmat faiwed\n");
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		weg02_vaw |= INNO_W02_WWCP_NOWMAW;
		weg03_vaw |= INNO_W03_BCP_NOWMAW;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		weg02_vaw |= INNO_W02_WWCP_WEVEWSAW;
		weg03_vaw |= INNO_W03_BCP_WEVEWSAW;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		weg02_vaw |= INNO_W02_WWCP_WEVEWSAW;
		weg03_vaw |= INNO_W03_BCP_NOWMAW;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		weg02_vaw |= INNO_W02_WWCP_NOWMAW;
		weg03_vaw |= INNO_W03_BCP_WEVEWSAW;
		bweak;
	defauwt:
		dev_eww(component->dev, "set dai fowmat faiwed\n");
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, INNO_W01, INNO_W01_I2SMODE_MSK |
			    INNO_W01_PINDIW_MSK, weg01_vaw);
	snd_soc_component_update_bits(component, INNO_W02, INNO_W02_WWCP_MSK |
			    INNO_W02_DACM_MSK, weg02_vaw);
	snd_soc_component_update_bits(component, INNO_W03, INNO_W03_BCP_MSK, weg03_vaw);

	wetuwn 0;
}

static int wk3036_codec_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				      stwuct snd_pcm_hw_pawams *hw_pawams,
				      stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	unsigned int weg02_vaw = 0, weg03_vaw = 0;

	switch (pawams_fowmat(hw_pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		weg02_vaw |= INNO_W02_VWW_16BIT;
		bweak;
	case SNDWV_PCM_FOWMAT_S20_3WE:
		weg02_vaw |= INNO_W02_VWW_20BIT;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		weg02_vaw |= INNO_W02_VWW_24BIT;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		weg02_vaw |= INNO_W02_VWW_32BIT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	weg02_vaw |= INNO_W02_WWCP_NOWMAW;
	weg03_vaw |= INNO_W03_FWW_32BIT | INNO_W03_DACW_WOWK;

	snd_soc_component_update_bits(component, INNO_W02, INNO_W02_WWCP_MSK |
			    INNO_W02_VWW_MSK, weg02_vaw);
	snd_soc_component_update_bits(component, INNO_W03, INNO_W03_DACW_MSK |
			    INNO_W03_FWW_MSK, weg03_vaw);
	wetuwn 0;
}

#define WK3036_CODEC_WATES (SNDWV_PCM_WATE_8000  | \
			    SNDWV_PCM_WATE_16000 | \
			    SNDWV_PCM_WATE_32000 | \
			    SNDWV_PCM_WATE_44100 | \
			    SNDWV_PCM_WATE_48000 | \
			    SNDWV_PCM_WATE_96000)

#define WK3036_CODEC_FMTS (SNDWV_PCM_FMTBIT_S16_WE  | \
			   SNDWV_PCM_FMTBIT_S20_3WE | \
			   SNDWV_PCM_FMTBIT_S24_WE  | \
			   SNDWV_PCM_FMTBIT_S32_WE)

static const stwuct snd_soc_dai_ops wk3036_codec_dai_ops = {
	.set_fmt	= wk3036_codec_dai_set_fmt,
	.hw_pawams	= wk3036_codec_dai_hw_pawams,
};

static stwuct snd_soc_dai_dwivew wk3036_codec_dai_dwivew[] = {
	{
		.name = "wk3036-codec-dai",
		.pwayback = {
			.stweam_name = "Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = WK3036_CODEC_WATES,
			.fowmats = WK3036_CODEC_FMTS,
		},
		.ops = &wk3036_codec_dai_ops,
		.symmetwic_wate = 1,
	},
};

static void wk3036_codec_weset(stwuct snd_soc_component *component)
{
	snd_soc_component_wwite(component, INNO_W00,
		      INNO_W00_CSW_WESET | INNO_W00_CDCW_WESET);
	snd_soc_component_wwite(component, INNO_W00,
		      INNO_W00_CSW_WOWK | INNO_W00_CDCW_WOWK);
}

static int wk3036_codec_pwobe(stwuct snd_soc_component *component)
{
	wk3036_codec_weset(component);
	wetuwn 0;
}

static void wk3036_codec_wemove(stwuct snd_soc_component *component)
{
	wk3036_codec_weset(component);
}

static int wk3036_codec_set_bias_wevew(stwuct snd_soc_component *component,
				       enum snd_soc_bias_wevew wevew)
{
	switch (wevew) {
	case SND_SOC_BIAS_STANDBY:
		/* set a big cuwwent fow capacitow chawging. */
		snd_soc_component_wwite(component, INNO_W10, INNO_W10_MAX_CUW);
		/* stawt pwechawge */
		snd_soc_component_wwite(component, INNO_W06, INNO_W06_DAC_PWECHAWGE);

		bweak;

	case SND_SOC_BIAS_OFF:
		/* set a big cuwwent fow capacitow dischawging. */
		snd_soc_component_wwite(component, INNO_W10, INNO_W10_MAX_CUW);
		/* stawt dischawge. */
		snd_soc_component_wwite(component, INNO_W06, INNO_W06_DAC_DISCHAWGE);

		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew wk3036_codec_dwivew = {
	.pwobe			= wk3036_codec_pwobe,
	.wemove			= wk3036_codec_wemove,
	.set_bias_wevew		= wk3036_codec_set_bias_wevew,
	.contwows		= wk3036_codec_dapm_contwows,
	.num_contwows		= AWWAY_SIZE(wk3036_codec_dapm_contwows),
	.dapm_woutes		= wk3036_codec_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wk3036_codec_dapm_woutes),
	.dapm_widgets		= wk3036_codec_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wk3036_codec_dapm_widgets),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config wk3036_codec_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
};

#define GWF_SOC_CON0		0x00140
#define GWF_ACODEC_SEW		(BIT(10) | BIT(16 + 10))

static int wk3036_codec_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wk3036_codec_pwiv *pwiv;
	stwuct device_node *of_node = pdev->dev.of_node;
	void __iomem *base;
	stwuct wegmap *gwf;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	pwiv->base = base;
	pwiv->wegmap = devm_wegmap_init_mmio(&pdev->dev, pwiv->base,
					     &wk3036_codec_wegmap_config);
	if (IS_EWW(pwiv->wegmap)) {
		dev_eww(&pdev->dev, "init wegmap faiwed\n");
		wetuwn PTW_EWW(pwiv->wegmap);
	}

	gwf = syscon_wegmap_wookup_by_phandwe(of_node, "wockchip,gwf");
	if (IS_EWW(gwf)) {
		dev_eww(&pdev->dev, "needs 'wockchip,gwf' pwopewty\n");
		wetuwn PTW_EWW(gwf);
	}
	wet = wegmap_wwite(gwf, GWF_SOC_CON0, GWF_ACODEC_SEW);
	if (wet) {
		dev_eww(&pdev->dev, "Couwd not wwite to GWF: %d\n", wet);
		wetuwn wet;
	}

	pwiv->pcwk = devm_cwk_get(&pdev->dev, "acodec_pcwk");
	if (IS_EWW(pwiv->pcwk))
		wetuwn PTW_EWW(pwiv->pcwk);

	wet = cwk_pwepawe_enabwe(pwiv->pcwk);
	if (wet < 0) {
		dev_eww(&pdev->dev, "faiwed to enabwe cwk\n");
		wetuwn wet;
	}

	pwiv->dev = &pdev->dev;
	dev_set_dwvdata(&pdev->dev, pwiv);

	wet = devm_snd_soc_wegistew_component(&pdev->dev, &wk3036_codec_dwivew,
				     wk3036_codec_dai_dwivew,
				     AWWAY_SIZE(wk3036_codec_dai_dwivew));
	if (wet) {
		cwk_disabwe_unpwepawe(pwiv->pcwk);
		dev_set_dwvdata(&pdev->dev, NUWW);
	}

	wetuwn wet;
}

static void wk3036_codec_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wk3036_codec_pwiv *pwiv = dev_get_dwvdata(&pdev->dev);

	cwk_disabwe_unpwepawe(pwiv->pcwk);
}

static const stwuct of_device_id wk3036_codec_of_match[] __maybe_unused = {
	{ .compatibwe = "wockchip,wk3036-codec", },
	{}
};
MODUWE_DEVICE_TABWE(of, wk3036_codec_of_match);

static stwuct pwatfowm_dwivew wk3036_codec_pwatfowm_dwivew = {
	.dwivew = {
		.name = "wk3036-codec-pwatfowm",
		.of_match_tabwe = of_match_ptw(wk3036_codec_of_match),
	},
	.pwobe = wk3036_codec_pwatfowm_pwobe,
	.wemove_new = wk3036_codec_pwatfowm_wemove,
};

moduwe_pwatfowm_dwivew(wk3036_codec_pwatfowm_dwivew);

MODUWE_AUTHOW("Wockchip Inc.");
MODUWE_DESCWIPTION("Wockchip wk3036 codec dwivew");
MODUWE_WICENSE("GPW");
