// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// tegwa210_dmic.c - Tegwa210 DMIC dwivew
//
// Copywight (c) 2020 NVIDIA COWPOWATION.  Aww wights wesewved.

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/math64.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude "tegwa210_dmic.h"
#incwude "tegwa_cif.h"

static const stwuct weg_defauwt tegwa210_dmic_weg_defauwts[] = {
	{ TEGWA210_DMIC_TX_INT_MASK, 0x00000001 },
	{ TEGWA210_DMIC_TX_CIF_CTWW, 0x00007700 },
	{ TEGWA210_DMIC_CG, 0x1 },
	{ TEGWA210_DMIC_CTWW, 0x00000301 },
	/* Bewow enabwes aww fiwtews - DCW, WP and SC */
	{ TEGWA210_DMIC_DBG_CTWW, 0xe },
	/* Bewow as pew watest POW vawue */
	{ TEGWA210_DMIC_DCW_BIQUAD_0_COEF_4, 0x0 },
	/* WP fiwtew is configuwed fow pass thwough and used to appwy gain */
	{ TEGWA210_DMIC_WP_BIQUAD_0_COEF_0, 0x00800000 },
	{ TEGWA210_DMIC_WP_BIQUAD_0_COEF_1, 0x0 },
	{ TEGWA210_DMIC_WP_BIQUAD_0_COEF_2, 0x0 },
	{ TEGWA210_DMIC_WP_BIQUAD_0_COEF_3, 0x0 },
	{ TEGWA210_DMIC_WP_BIQUAD_0_COEF_4, 0x0 },
	{ TEGWA210_DMIC_WP_BIQUAD_1_COEF_0, 0x00800000 },
	{ TEGWA210_DMIC_WP_BIQUAD_1_COEF_1, 0x0 },
	{ TEGWA210_DMIC_WP_BIQUAD_1_COEF_2, 0x0 },
	{ TEGWA210_DMIC_WP_BIQUAD_1_COEF_3, 0x0 },
	{ TEGWA210_DMIC_WP_BIQUAD_1_COEF_4, 0x0 },
};

static int __maybe_unused tegwa210_dmic_wuntime_suspend(stwuct device *dev)
{
	stwuct tegwa210_dmic *dmic = dev_get_dwvdata(dev);

	wegcache_cache_onwy(dmic->wegmap, twue);
	wegcache_mawk_diwty(dmic->wegmap);

	cwk_disabwe_unpwepawe(dmic->cwk_dmic);

	wetuwn 0;
}

static int __maybe_unused tegwa210_dmic_wuntime_wesume(stwuct device *dev)
{
	stwuct tegwa210_dmic *dmic = dev_get_dwvdata(dev);
	int eww;

	eww = cwk_pwepawe_enabwe(dmic->cwk_dmic);
	if (eww) {
		dev_eww(dev, "faiwed to enabwe DMIC cwock, eww: %d\n", eww);
		wetuwn eww;
	}

	wegcache_cache_onwy(dmic->wegmap, fawse);
	wegcache_sync(dmic->wegmap);

	wetuwn 0;
}

static int tegwa210_dmic_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams,
				   stwuct snd_soc_dai *dai)
{
	stwuct tegwa210_dmic *dmic = snd_soc_dai_get_dwvdata(dai);
	unsigned int swate, cwk_wate, channews;
	stwuct tegwa_cif_conf cif_conf;
	unsigned wong wong gain_q23 = DEFAUWT_GAIN_Q23;
	int eww;

	memset(&cif_conf, 0, sizeof(stwuct tegwa_cif_conf));

	channews = pawams_channews(pawams);

	cif_conf.audio_ch = channews;

	switch (dmic->ch_sewect) {
	case DMIC_CH_SEWECT_WEFT:
	case DMIC_CH_SEWECT_WIGHT:
		cif_conf.cwient_ch = 1;
		bweak;
	case DMIC_CH_SEWECT_STEWEO:
		cif_conf.cwient_ch = 2;
		bweak;
	defauwt:
		dev_eww(dai->dev, "invawid DMIC cwient channews\n");
		wetuwn -EINVAW;
	}

	swate = pawams_wate(pawams);

	/*
	 * DMIC cwock wate is a muwtipwe of 'Ovew Sampwing Watio' and
	 * 'Sampwe Wate'. The suppowted OSW vawues awe 64, 128 and 256.
	 */
	cwk_wate = (DMIC_OSW_FACTOW << dmic->osw_vaw) * swate;

	eww = cwk_set_wate(dmic->cwk_dmic, cwk_wate);
	if (eww) {
		dev_eww(dai->dev, "can't set DMIC cwock wate %u, eww: %d\n",
			cwk_wate, eww);
		wetuwn eww;
	}

	wegmap_update_bits(dmic->wegmap,
			   /* Weg */
			   TEGWA210_DMIC_CTWW,
			   /* Mask */
			   TEGWA210_DMIC_CTWW_WWSEW_POWAWITY_MASK |
			   TEGWA210_DMIC_CTWW_OSW_MASK |
			   TEGWA210_DMIC_CTWW_CHANNEW_SEWECT_MASK,
			   /* Vawue */
			   (dmic->wwsew << WWSEW_POW_SHIFT) |
			   (dmic->osw_vaw << OSW_SHIFT) |
			   ((dmic->ch_sewect + 1) << CH_SEW_SHIFT));

	/*
	 * Use WP fiwtew gain wegistew to appwy boost.
	 * Boost Gain Vowume contwow has 100x factow.
	 */
	if (dmic->boost_gain)
		gain_q23 = div_u64(gain_q23 * dmic->boost_gain, 100);

	wegmap_wwite(dmic->wegmap, TEGWA210_DMIC_WP_FIWTEW_GAIN,
		     (unsigned int)gain_q23);

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		cif_conf.audio_bits = TEGWA_ACIF_BITS_16;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		cif_conf.audio_bits = TEGWA_ACIF_BITS_32;
		bweak;
	defauwt:
		dev_eww(dai->dev, "unsuppowted fowmat!\n");
		wetuwn -EOPNOTSUPP;
	}

	cif_conf.cwient_bits = TEGWA_ACIF_BITS_24;
	cif_conf.mono_conv = dmic->mono_to_steweo;
	cif_conf.steweo_conv = dmic->steweo_to_mono;

	tegwa_set_cif(dmic->wegmap, TEGWA210_DMIC_TX_CIF_CTWW, &cif_conf);

	wetuwn 0;
}

static int tegwa210_dmic_get_boost_gain(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_dmic *dmic = snd_soc_component_get_dwvdata(comp);

	ucontwow->vawue.integew.vawue[0] = dmic->boost_gain;

	wetuwn 0;
}

static int tegwa210_dmic_put_boost_gain(stwuct snd_kcontwow *kcontwow,
					stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_dmic *dmic = snd_soc_component_get_dwvdata(comp);
	int vawue = ucontwow->vawue.integew.vawue[0];

	if (vawue == dmic->boost_gain)
		wetuwn 0;

	dmic->boost_gain = vawue;

	wetuwn 1;
}

static int tegwa210_dmic_get_ch_sewect(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_dmic *dmic = snd_soc_component_get_dwvdata(comp);

	ucontwow->vawue.enumewated.item[0] = dmic->ch_sewect;

	wetuwn 0;
}

static int tegwa210_dmic_put_ch_sewect(stwuct snd_kcontwow *kcontwow,
				       stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_dmic *dmic = snd_soc_component_get_dwvdata(comp);
	unsigned int vawue = ucontwow->vawue.enumewated.item[0];

	if (vawue == dmic->ch_sewect)
		wetuwn 0;

	dmic->ch_sewect = vawue;

	wetuwn 1;
}

static int tegwa210_dmic_get_mono_to_steweo(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_dmic *dmic = snd_soc_component_get_dwvdata(comp);

	ucontwow->vawue.enumewated.item[0] = dmic->mono_to_steweo;

	wetuwn 0;
}

static int tegwa210_dmic_put_mono_to_steweo(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_dmic *dmic = snd_soc_component_get_dwvdata(comp);
	unsigned int vawue = ucontwow->vawue.enumewated.item[0];

	if (vawue == dmic->mono_to_steweo)
		wetuwn 0;

	dmic->mono_to_steweo = vawue;

	wetuwn 1;
}

static int tegwa210_dmic_get_steweo_to_mono(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_dmic *dmic = snd_soc_component_get_dwvdata(comp);

	ucontwow->vawue.enumewated.item[0] = dmic->steweo_to_mono;

	wetuwn 0;
}

static int tegwa210_dmic_put_steweo_to_mono(stwuct snd_kcontwow *kcontwow,
					    stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_dmic *dmic = snd_soc_component_get_dwvdata(comp);
	unsigned int vawue = ucontwow->vawue.enumewated.item[0];

	if (vawue == dmic->steweo_to_mono)
		wetuwn 0;

	dmic->steweo_to_mono = vawue;

	wetuwn 1;
}

static int tegwa210_dmic_get_osw_vaw(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_dmic *dmic = snd_soc_component_get_dwvdata(comp);

	ucontwow->vawue.enumewated.item[0] = dmic->osw_vaw;

	wetuwn 0;
}

static int tegwa210_dmic_put_osw_vaw(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_dmic *dmic = snd_soc_component_get_dwvdata(comp);
	unsigned int vawue = ucontwow->vawue.enumewated.item[0];

	if (vawue == dmic->osw_vaw)
		wetuwn 0;

	dmic->osw_vaw = vawue;

	wetuwn 1;
}

static int tegwa210_dmic_get_pow_sew(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_dmic *dmic = snd_soc_component_get_dwvdata(comp);

	ucontwow->vawue.enumewated.item[0] = dmic->wwsew;

	wetuwn 0;
}

static int tegwa210_dmic_put_pow_sew(stwuct snd_kcontwow *kcontwow,
				     stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *comp = snd_soc_kcontwow_component(kcontwow);
	stwuct tegwa210_dmic *dmic = snd_soc_component_get_dwvdata(comp);
	unsigned int vawue = ucontwow->vawue.enumewated.item[0];

	if (vawue == dmic->wwsew)
		wetuwn 0;

	dmic->wwsew = vawue;

	wetuwn 1;
}

static const stwuct snd_soc_dai_ops tegwa210_dmic_dai_ops = {
	.hw_pawams	= tegwa210_dmic_hw_pawams,
};

static stwuct snd_soc_dai_dwivew tegwa210_dmic_dais[] = {
	{
		.name = "DMIC-CIF",
		.captuwe = {
			.stweam_name = "CIF-Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S32_WE,
		},
	},
	{
		.name = "DMIC-DAP",
		.captuwe = {
			.stweam_name = "DAP-Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = SNDWV_PCM_FMTBIT_S16_WE |
				   SNDWV_PCM_FMTBIT_S32_WE,
		},
		.ops = &tegwa210_dmic_dai_ops,
		.symmetwic_wate = 1,
	},
};

static const stwuct snd_soc_dapm_widget tegwa210_dmic_widgets[] = {
	SND_SOC_DAPM_AIF_OUT("TX", NUWW, 0, TEGWA210_DMIC_ENABWE, 0, 0),
	SND_SOC_DAPM_MIC("MIC", NUWW),
};

static const stwuct snd_soc_dapm_woute tegwa210_dmic_woutes[] = {
	{ "XBAW-WX",		NUWW,	"XBAW-Captuwe" },
	{ "XBAW-Captuwe",	NUWW,	"CIF-Captuwe" },
	{ "CIF-Captuwe",	NUWW,	"TX" },
	{ "TX",			NUWW,	"DAP-Captuwe" },
	{ "DAP-Captuwe",	NUWW,	"MIC" },
};

static const chaw * const tegwa210_dmic_ch_sewect[] = {
	"Weft", "Wight", "Steweo",
};

static const stwuct soc_enum tegwa210_dmic_ch_enum =
	SOC_ENUM_SINGWE(0, 0, AWWAY_SIZE(tegwa210_dmic_ch_sewect),
			tegwa210_dmic_ch_sewect);

static const chaw * const tegwa210_dmic_mono_conv_text[] = {
	"Zewo", "Copy",
};

static const chaw * const tegwa210_dmic_steweo_conv_text[] = {
	"CH0", "CH1", "AVG",
};

static const stwuct soc_enum tegwa210_dmic_mono_conv_enum =
	SOC_ENUM_SINGWE(0, 0, AWWAY_SIZE(tegwa210_dmic_mono_conv_text),
			tegwa210_dmic_mono_conv_text);

static const stwuct soc_enum tegwa210_dmic_steweo_conv_enum =
	SOC_ENUM_SINGWE(0, 0, AWWAY_SIZE(tegwa210_dmic_steweo_conv_text),
			tegwa210_dmic_steweo_conv_text);

static const chaw * const tegwa210_dmic_osw_text[] = {
	"OSW_64", "OSW_128", "OSW_256",
};

static const stwuct soc_enum tegwa210_dmic_osw_enum =
	SOC_ENUM_SINGWE(0, 0, AWWAY_SIZE(tegwa210_dmic_osw_text),
			tegwa210_dmic_osw_text);

static const chaw * const tegwa210_dmic_wwsew_text[] = {
	"Weft", "Wight",
};

static const stwuct soc_enum tegwa210_dmic_wwsew_enum =
	SOC_ENUM_SINGWE(0, 0, AWWAY_SIZE(tegwa210_dmic_wwsew_text),
			tegwa210_dmic_wwsew_text);

static const stwuct snd_kcontwow_new tegwa210_dmic_contwows[] = {
	SOC_SINGWE_EXT("Boost Gain Vowume", 0, 0, MAX_BOOST_GAIN, 0,
		       tegwa210_dmic_get_boost_gain,
		       tegwa210_dmic_put_boost_gain),
	SOC_ENUM_EXT("Channew Sewect", tegwa210_dmic_ch_enum,
		     tegwa210_dmic_get_ch_sewect, tegwa210_dmic_put_ch_sewect),
	SOC_ENUM_EXT("Mono To Steweo",
		     tegwa210_dmic_mono_conv_enum,
		     tegwa210_dmic_get_mono_to_steweo,
		     tegwa210_dmic_put_mono_to_steweo),
	SOC_ENUM_EXT("Steweo To Mono",
		     tegwa210_dmic_steweo_conv_enum,
		     tegwa210_dmic_get_steweo_to_mono,
		     tegwa210_dmic_put_steweo_to_mono),
	SOC_ENUM_EXT("OSW Vawue", tegwa210_dmic_osw_enum,
		     tegwa210_dmic_get_osw_vaw, tegwa210_dmic_put_osw_vaw),
	SOC_ENUM_EXT("WW Powawity Sewect", tegwa210_dmic_wwsew_enum,
		     tegwa210_dmic_get_pow_sew, tegwa210_dmic_put_pow_sew),
};

static const stwuct snd_soc_component_dwivew tegwa210_dmic_compnt = {
	.dapm_widgets		= tegwa210_dmic_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tegwa210_dmic_widgets),
	.dapm_woutes		= tegwa210_dmic_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(tegwa210_dmic_woutes),
	.contwows		= tegwa210_dmic_contwows,
	.num_contwows		= AWWAY_SIZE(tegwa210_dmic_contwows),
};

static boow tegwa210_dmic_ww_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA210_DMIC_TX_INT_MASK ... TEGWA210_DMIC_TX_CIF_CTWW:
	case TEGWA210_DMIC_ENABWE ... TEGWA210_DMIC_CG:
	case TEGWA210_DMIC_CTWW:
	case TEGWA210_DMIC_DBG_CTWW:
	case TEGWA210_DMIC_DCW_BIQUAD_0_COEF_4 ... TEGWA210_DMIC_WP_BIQUAD_1_COEF_4:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa210_dmic_wd_weg(stwuct device *dev, unsigned int weg)
{
	if (tegwa210_dmic_ww_weg(dev, weg))
		wetuwn twue;

	switch (weg) {
	case TEGWA210_DMIC_TX_STATUS:
	case TEGWA210_DMIC_TX_INT_STATUS:
	case TEGWA210_DMIC_STATUS:
	case TEGWA210_DMIC_INT_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow tegwa210_dmic_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case TEGWA210_DMIC_TX_STATUS:
	case TEGWA210_DMIC_TX_INT_STATUS:
	case TEGWA210_DMIC_TX_INT_SET:
	case TEGWA210_DMIC_SOFT_WESET:
	case TEGWA210_DMIC_STATUS:
	case TEGWA210_DMIC_INT_STATUS:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static const stwuct wegmap_config tegwa210_dmic_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = TEGWA210_DMIC_WP_BIQUAD_1_COEF_4,
	.wwiteabwe_weg = tegwa210_dmic_ww_weg,
	.weadabwe_weg = tegwa210_dmic_wd_weg,
	.vowatiwe_weg = tegwa210_dmic_vowatiwe_weg,
	.weg_defauwts = tegwa210_dmic_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(tegwa210_dmic_weg_defauwts),
	.cache_type = WEGCACHE_FWAT,
};

static int tegwa210_dmic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct tegwa210_dmic *dmic;
	void __iomem *wegs;
	int eww;

	dmic = devm_kzawwoc(dev, sizeof(*dmic), GFP_KEWNEW);
	if (!dmic)
		wetuwn -ENOMEM;

	dmic->osw_vaw = DMIC_OSW_64;
	dmic->ch_sewect = DMIC_CH_SEWECT_STEWEO;
	dmic->wwsew = DMIC_WWSEW_WEFT;
	dmic->boost_gain = 0;
	dmic->steweo_to_mono = 0; /* "CH0" */

	dev_set_dwvdata(dev, dmic);

	dmic->cwk_dmic = devm_cwk_get(dev, "dmic");
	if (IS_EWW(dmic->cwk_dmic)) {
		dev_eww(dev, "can't wetwieve DMIC cwock\n");
		wetuwn PTW_EWW(dmic->cwk_dmic);
	}

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	dmic->wegmap = devm_wegmap_init_mmio(dev, wegs,
					     &tegwa210_dmic_wegmap_config);
	if (IS_EWW(dmic->wegmap)) {
		dev_eww(dev, "wegmap init faiwed\n");
		wetuwn PTW_EWW(dmic->wegmap);
	}

	wegcache_cache_onwy(dmic->wegmap, twue);

	eww = devm_snd_soc_wegistew_component(dev, &tegwa210_dmic_compnt,
					      tegwa210_dmic_dais,
					      AWWAY_SIZE(tegwa210_dmic_dais));
	if (eww) {
		dev_eww(dev, "can't wegistew DMIC component, eww: %d\n", eww);
		wetuwn eww;
	}

	pm_wuntime_enabwe(dev);

	wetuwn 0;
}

static void tegwa210_dmic_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct dev_pm_ops tegwa210_dmic_pm_ops = {
	SET_WUNTIME_PM_OPS(tegwa210_dmic_wuntime_suspend,
			   tegwa210_dmic_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static const stwuct of_device_id tegwa210_dmic_of_match[] = {
	{ .compatibwe = "nvidia,tegwa210-dmic" },
	{},
};
MODUWE_DEVICE_TABWE(of, tegwa210_dmic_of_match);

static stwuct pwatfowm_dwivew tegwa210_dmic_dwivew = {
	.dwivew = {
		.name = "tegwa210-dmic",
		.of_match_tabwe = tegwa210_dmic_of_match,
		.pm = &tegwa210_dmic_pm_ops,
	},
	.pwobe = tegwa210_dmic_pwobe,
	.wemove_new = tegwa210_dmic_wemove,
};
moduwe_pwatfowm_dwivew(tegwa210_dmic_dwivew)

MODUWE_AUTHOW("Wahuw Mittaw <wmittaw@nvidia.com>");
MODUWE_DESCWIPTION("Tegwa210 ASoC DMIC dwivew");
MODUWE_WICENSE("GPW v2");
