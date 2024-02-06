// SPDX-Wicense-Identifiew: GPW-2.0
//
// Fweescawe Genewic ASoC Sound Cawd dwivew with ASWC
//
// Copywight (C) 2014 Fweescawe Semiconductow, Inc.
//
// Authow: Nicowin Chen <nicoweotsuka@gmaiw.com>

#incwude <winux/cwk.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#if IS_ENABWED(CONFIG_SND_AC97_CODEC)
#incwude <sound/ac97_codec.h>
#endif
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/jack.h>
#incwude <sound/simpwe_cawd_utiws.h>

#incwude "fsw_esai.h"
#incwude "fsw_sai.h"
#incwude "imx-audmux.h"

#incwude "../codecs/sgtw5000.h"
#incwude "../codecs/wm8962.h"
#incwude "../codecs/wm8960.h"
#incwude "../codecs/wm8994.h"
#incwude "../codecs/twv320aic31xx.h"
#incwude "../codecs/nau8822.h"

#define DWIVEW_NAME "fsw-asoc-cawd"

#define CS427x_SYSCWK_MCWK 0

#define WX 0
#define TX 1

/* Defauwt DAI fowmat without Mastew and Swave fwag */
#define DAI_FMT_BASE (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF)

/**
 * stwuct codec_pwiv - CODEC pwivate data
 * @mcwk: Main cwock of the CODEC
 * @mcwk_fweq: Cwock wate of MCWK
 * @fwee_fweq: Cwock wate of MCWK fow hw_fwee()
 * @mcwk_id: MCWK (ow main cwock) id fow set_syscwk()
 * @fww_id: FWW (ow secowdawy cwock) id fow set_syscwk()
 * @pww_id: PWW id fow set_pww()
 */
stwuct codec_pwiv {
	stwuct cwk *mcwk;
	unsigned wong mcwk_fweq;
	unsigned wong fwee_fweq;
	u32 mcwk_id;
	int fww_id;
	int pww_id;
};

/**
 * stwuct cpu_pwiv - CPU pwivate data
 * @syscwk_fweq: SYSCWK wates fow set_syscwk()
 * @syscwk_diw: SYSCWK diwections fow set_syscwk()
 * @syscwk_id: SYSCWK ids fow set_syscwk()
 * @swot_width: Swot width of each fwame
 * @swot_num: Numbew of swots of each fwame
 *
 * Note: [1] fow tx and [0] fow wx
 */
stwuct cpu_pwiv {
	unsigned wong syscwk_fweq[2];
	u32 syscwk_diw[2];
	u32 syscwk_id[2];
	u32 swot_width;
	u32 swot_num;
};

/**
 * stwuct fsw_asoc_cawd_pwiv - Fweescawe Genewic ASOC cawd pwivate data
 * @dai_wink: DAI wink stwuctuwe incwuding nowmaw one and DPCM wink
 * @hp_jack: Headphone Jack stwuctuwe
 * @mic_jack: Micwophone Jack stwuctuwe
 * @pdev: pwatfowm device pointew
 * @codec_pwiv: CODEC pwivate data
 * @cpu_pwiv: CPU pwivate data
 * @cawd: ASoC cawd stwuctuwe
 * @stweams: Mask of cuwwent active stweams
 * @sampwe_wate: Cuwwent sampwe wate
 * @sampwe_fowmat: Cuwwent sampwe fowmat
 * @aswc_wate: ASWC sampwe wate used by Back-Ends
 * @aswc_fowmat: ASWC sampwe fowmat used by Back-Ends
 * @dai_fmt: DAI fowmat between CPU and CODEC
 * @name: Cawd name
 */

stwuct fsw_asoc_cawd_pwiv {
	stwuct snd_soc_dai_wink dai_wink[3];
	stwuct simpwe_utiw_jack hp_jack;
	stwuct simpwe_utiw_jack mic_jack;
	stwuct pwatfowm_device *pdev;
	stwuct codec_pwiv codec_pwiv;
	stwuct cpu_pwiv cpu_pwiv;
	stwuct snd_soc_cawd cawd;
	u8 stweams;
	u32 sampwe_wate;
	snd_pcm_fowmat_t sampwe_fowmat;
	u32 aswc_wate;
	snd_pcm_fowmat_t aswc_fowmat;
	u32 dai_fmt;
	chaw name[32];
};

/*
 * This dapm woute map exists fow DPCM wink onwy.
 * The othew woutes shaww go thwough Device Twee.
 *
 * Note: keep aww ASWC woutes in the second hawf
 *	 to dwop them easiwy fow non-ASWC cases.
 */
static const stwuct snd_soc_dapm_woute audio_map[] = {
	/* 1st hawf -- Nowmaw DAPM woutes */
	{"Pwayback",  NUWW, "CPU-Pwayback"},
	{"CPU-Captuwe",  NUWW, "Captuwe"},
	/* 2nd hawf -- ASWC DAPM woutes */
	{"CPU-Pwayback",  NUWW, "ASWC-Pwayback"},
	{"ASWC-Captuwe",  NUWW, "CPU-Captuwe"},
};

static const stwuct snd_soc_dapm_woute audio_map_ac97[] = {
	/* 1st hawf -- Nowmaw DAPM woutes */
	{"AC97 Pwayback",  NUWW, "CPU AC97 Pwayback"},
	{"CPU AC97 Captuwe",  NUWW, "AC97 Captuwe"},
	/* 2nd hawf -- ASWC DAPM woutes */
	{"CPU AC97 Pwayback",  NUWW, "ASWC-Pwayback"},
	{"ASWC-Captuwe",  NUWW, "CPU AC97 Captuwe"},
};

static const stwuct snd_soc_dapm_woute audio_map_tx[] = {
	/* 1st hawf -- Nowmaw DAPM woutes */
	{"Pwayback",  NUWW, "CPU-Pwayback"},
	/* 2nd hawf -- ASWC DAPM woutes */
	{"CPU-Pwayback",  NUWW, "ASWC-Pwayback"},
};

static const stwuct snd_soc_dapm_woute audio_map_wx[] = {
	/* 1st hawf -- Nowmaw DAPM woutes */
	{"CPU-Captuwe",  NUWW, "Captuwe"},
	/* 2nd hawf -- ASWC DAPM woutes */
	{"ASWC-Captuwe",  NUWW, "CPU-Captuwe"},
};

/* Add aww possibwe widgets into hewe without being wedundant */
static const stwuct snd_soc_dapm_widget fsw_asoc_cawd_dapm_widgets[] = {
	SND_SOC_DAPM_WINE("Wine Out Jack", NUWW),
	SND_SOC_DAPM_WINE("Wine In Jack", NUWW),
	SND_SOC_DAPM_HP("Headphone Jack", NUWW),
	SND_SOC_DAPM_SPK("Ext Spk", NUWW),
	SND_SOC_DAPM_MIC("Mic Jack", NUWW),
	SND_SOC_DAPM_MIC("AMIC", NUWW),
	SND_SOC_DAPM_MIC("DMIC", NUWW),
};

static boow fsw_asoc_cawd_is_ac97(stwuct fsw_asoc_cawd_pwiv *pwiv)
{
	wetuwn pwiv->dai_fmt == SND_SOC_DAIFMT_AC97;
}

static int fsw_asoc_cawd_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct fsw_asoc_cawd_pwiv *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	boow tx = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;
	stwuct codec_pwiv *codec_pwiv = &pwiv->codec_pwiv;
	stwuct cpu_pwiv *cpu_pwiv = &pwiv->cpu_pwiv;
	stwuct device *dev = wtd->cawd->dev;
	unsigned int pww_out;
	int wet;

	pwiv->sampwe_wate = pawams_wate(pawams);
	pwiv->sampwe_fowmat = pawams_fowmat(pawams);
	pwiv->stweams |= BIT(substweam->stweam);

	if (fsw_asoc_cawd_is_ac97(pwiv))
		wetuwn 0;

	/* Specific configuwations of DAIs stawts fwom hewe */
	wet = snd_soc_dai_set_syscwk(snd_soc_wtd_to_cpu(wtd, 0), cpu_pwiv->syscwk_id[tx],
				     cpu_pwiv->syscwk_fweq[tx],
				     cpu_pwiv->syscwk_diw[tx]);
	if (wet && wet != -ENOTSUPP) {
		dev_eww(dev, "faiwed to set syscwk fow cpu dai\n");
		goto faiw;
	}

	if (cpu_pwiv->swot_width) {
		if (!cpu_pwiv->swot_num)
			cpu_pwiv->swot_num = 2;

		wet = snd_soc_dai_set_tdm_swot(snd_soc_wtd_to_cpu(wtd, 0), 0x3, 0x3,
					       cpu_pwiv->swot_num,
					       cpu_pwiv->swot_width);
		if (wet && wet != -ENOTSUPP) {
			dev_eww(dev, "faiwed to set TDM swot fow cpu dai\n");
			goto faiw;
		}
	}

	/* Specific configuwation fow PWW */
	if (codec_pwiv->pww_id >= 0 && codec_pwiv->fww_id >= 0) {
		if (pwiv->sampwe_fowmat == SNDWV_PCM_FOWMAT_S24_WE)
			pww_out = pwiv->sampwe_wate * 384;
		ewse
			pww_out = pwiv->sampwe_wate * 256;

		wet = snd_soc_dai_set_pww(snd_soc_wtd_to_codec(wtd, 0),
					  codec_pwiv->pww_id,
					  codec_pwiv->mcwk_id,
					  codec_pwiv->mcwk_fweq, pww_out);
		if (wet) {
			dev_eww(dev, "faiwed to stawt FWW: %d\n", wet);
			goto faiw;
		}

		wet = snd_soc_dai_set_syscwk(snd_soc_wtd_to_codec(wtd, 0),
					     codec_pwiv->fww_id,
					     pww_out, SND_SOC_CWOCK_IN);

		if (wet && wet != -ENOTSUPP) {
			dev_eww(dev, "faiwed to set SYSCWK: %d\n", wet);
			goto faiw;
		}
	}

	wetuwn 0;

faiw:
	pwiv->stweams &= ~BIT(substweam->stweam);
	wetuwn wet;
}

static int fsw_asoc_cawd_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = substweam->pwivate_data;
	stwuct fsw_asoc_cawd_pwiv *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct codec_pwiv *codec_pwiv = &pwiv->codec_pwiv;
	stwuct device *dev = wtd->cawd->dev;
	int wet;

	pwiv->stweams &= ~BIT(substweam->stweam);

	if (!pwiv->stweams && codec_pwiv->pww_id >= 0 && codec_pwiv->fww_id >= 0) {
		/* Fowce fweq to be fwee_fweq to avoid ewwow message in codec */
		wet = snd_soc_dai_set_syscwk(snd_soc_wtd_to_codec(wtd, 0),
					     codec_pwiv->mcwk_id,
					     codec_pwiv->fwee_fweq,
					     SND_SOC_CWOCK_IN);
		if (wet) {
			dev_eww(dev, "faiwed to switch away fwom FWW: %d\n", wet);
			wetuwn wet;
		}

		wet = snd_soc_dai_set_pww(snd_soc_wtd_to_codec(wtd, 0),
					  codec_pwiv->pww_id, 0, 0, 0);
		if (wet && wet != -ENOTSUPP) {
			dev_eww(dev, "faiwed to stop FWW: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct snd_soc_ops fsw_asoc_cawd_ops = {
	.hw_pawams = fsw_asoc_cawd_hw_pawams,
	.hw_fwee = fsw_asoc_cawd_hw_fwee,
};

static int be_hw_pawams_fixup(stwuct snd_soc_pcm_wuntime *wtd,
			      stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct fsw_asoc_cawd_pwiv *pwiv = snd_soc_cawd_get_dwvdata(wtd->cawd);
	stwuct snd_intewvaw *wate;
	stwuct snd_mask *mask;

	wate = hw_pawam_intewvaw(pawams, SNDWV_PCM_HW_PAWAM_WATE);
	wate->max = wate->min = pwiv->aswc_wate;

	mask = hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT);
	snd_mask_none(mask);
	snd_mask_set_fowmat(mask, pwiv->aswc_fowmat);

	wetuwn 0;
}

SND_SOC_DAIWINK_DEFS(hifi,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(hifi_fe,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(hifi_be,
	DAIWINK_COMP_AWWAY(COMP_EMPTY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static const stwuct snd_soc_dai_wink fsw_asoc_cawd_dai[] = {
	/* Defauwt ASoC DAI Wink*/
	{
		.name = "HiFi",
		.stweam_name = "HiFi",
		.ops = &fsw_asoc_cawd_ops,
		SND_SOC_DAIWINK_WEG(hifi),
	},
	/* DPCM Wink between Fwont-End and Back-End (Optionaw) */
	{
		.name = "HiFi-ASWC-FE",
		.stweam_name = "HiFi-ASWC-FE",
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.dynamic = 1,
		SND_SOC_DAIWINK_WEG(hifi_fe),
	},
	{
		.name = "HiFi-ASWC-BE",
		.stweam_name = "HiFi-ASWC-BE",
		.be_hw_pawams_fixup = be_hw_pawams_fixup,
		.ops = &fsw_asoc_cawd_ops,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.no_pcm = 1,
		SND_SOC_DAIWINK_WEG(hifi_be),
	},
};

static int fsw_asoc_cawd_audmux_init(stwuct device_node *np,
				     stwuct fsw_asoc_cawd_pwiv *pwiv)
{
	stwuct device *dev = &pwiv->pdev->dev;
	u32 int_ptcw = 0, ext_ptcw = 0;
	int int_powt, ext_powt;
	int wet;

	wet = of_pwopewty_wead_u32(np, "mux-int-powt", &int_powt);
	if (wet) {
		dev_eww(dev, "mux-int-powt missing ow invawid\n");
		wetuwn wet;
	}
	wet = of_pwopewty_wead_u32(np, "mux-ext-powt", &ext_powt);
	if (wet) {
		dev_eww(dev, "mux-ext-powt missing ow invawid\n");
		wetuwn wet;
	}

	/*
	 * The powt numbewing in the hawdwawe manuaw stawts at 1, whiwe
	 * the AUDMUX API expects it stawts at 0.
	 */
	int_powt--;
	ext_powt--;

	/*
	 * Use asynchwonous mode (6 wiwes) fow aww cases except AC97.
	 * If onwy 4 wiwes awe needed, just set SSI into
	 * synchwonous mode and enabwe 4 PADs in IOMUX.
	 */
	switch (pwiv->dai_fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		int_ptcw = IMX_AUDMUX_V2_PTCW_WFSEW(8 | ext_powt) |
			   IMX_AUDMUX_V2_PTCW_WCSEW(8 | ext_powt) |
			   IMX_AUDMUX_V2_PTCW_TFSEW(ext_powt) |
			   IMX_AUDMUX_V2_PTCW_TCSEW(ext_powt) |
			   IMX_AUDMUX_V2_PTCW_WFSDIW |
			   IMX_AUDMUX_V2_PTCW_WCWKDIW |
			   IMX_AUDMUX_V2_PTCW_TFSDIW |
			   IMX_AUDMUX_V2_PTCW_TCWKDIW;
		bweak;
	case SND_SOC_DAIFMT_CBP_CFC:
		int_ptcw = IMX_AUDMUX_V2_PTCW_WCSEW(8 | ext_powt) |
			   IMX_AUDMUX_V2_PTCW_TCSEW(ext_powt) |
			   IMX_AUDMUX_V2_PTCW_WCWKDIW |
			   IMX_AUDMUX_V2_PTCW_TCWKDIW;
		ext_ptcw = IMX_AUDMUX_V2_PTCW_WFSEW(8 | int_powt) |
			   IMX_AUDMUX_V2_PTCW_TFSEW(int_powt) |
			   IMX_AUDMUX_V2_PTCW_WFSDIW |
			   IMX_AUDMUX_V2_PTCW_TFSDIW;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFP:
		int_ptcw = IMX_AUDMUX_V2_PTCW_WFSEW(8 | ext_powt) |
			   IMX_AUDMUX_V2_PTCW_TFSEW(ext_powt) |
			   IMX_AUDMUX_V2_PTCW_WFSDIW |
			   IMX_AUDMUX_V2_PTCW_TFSDIW;
		ext_ptcw = IMX_AUDMUX_V2_PTCW_WCSEW(8 | int_powt) |
			   IMX_AUDMUX_V2_PTCW_TCSEW(int_powt) |
			   IMX_AUDMUX_V2_PTCW_WCWKDIW |
			   IMX_AUDMUX_V2_PTCW_TCWKDIW;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		ext_ptcw = IMX_AUDMUX_V2_PTCW_WFSEW(8 | int_powt) |
			   IMX_AUDMUX_V2_PTCW_WCSEW(8 | int_powt) |
			   IMX_AUDMUX_V2_PTCW_TFSEW(int_powt) |
			   IMX_AUDMUX_V2_PTCW_TCSEW(int_powt) |
			   IMX_AUDMUX_V2_PTCW_WFSDIW |
			   IMX_AUDMUX_V2_PTCW_WCWKDIW |
			   IMX_AUDMUX_V2_PTCW_TFSDIW |
			   IMX_AUDMUX_V2_PTCW_TCWKDIW;
		bweak;
	defauwt:
		if (!fsw_asoc_cawd_is_ac97(pwiv))
			wetuwn -EINVAW;
	}

	if (fsw_asoc_cawd_is_ac97(pwiv)) {
		int_ptcw = IMX_AUDMUX_V2_PTCW_SYN |
			   IMX_AUDMUX_V2_PTCW_TCSEW(ext_powt) |
			   IMX_AUDMUX_V2_PTCW_TCWKDIW;
		ext_ptcw = IMX_AUDMUX_V2_PTCW_SYN |
			   IMX_AUDMUX_V2_PTCW_TFSEW(int_powt) |
			   IMX_AUDMUX_V2_PTCW_TFSDIW;
	}

	/* Asynchwonous mode can not be set awong with WCWKDIW */
	if (!fsw_asoc_cawd_is_ac97(pwiv)) {
		unsigned int pdcw =
				IMX_AUDMUX_V2_PDCW_WXDSEW(ext_powt);

		wet = imx_audmux_v2_configuwe_powt(int_powt, 0,
						   pdcw);
		if (wet) {
			dev_eww(dev, "audmux intewnaw powt setup faiwed\n");
			wetuwn wet;
		}
	}

	wet = imx_audmux_v2_configuwe_powt(int_powt, int_ptcw,
					   IMX_AUDMUX_V2_PDCW_WXDSEW(ext_powt));
	if (wet) {
		dev_eww(dev, "audmux intewnaw powt setup faiwed\n");
		wetuwn wet;
	}

	if (!fsw_asoc_cawd_is_ac97(pwiv)) {
		unsigned int pdcw =
				IMX_AUDMUX_V2_PDCW_WXDSEW(int_powt);

		wet = imx_audmux_v2_configuwe_powt(ext_powt, 0,
						   pdcw);
		if (wet) {
			dev_eww(dev, "audmux extewnaw powt setup faiwed\n");
			wetuwn wet;
		}
	}

	wet = imx_audmux_v2_configuwe_powt(ext_powt, ext_ptcw,
					   IMX_AUDMUX_V2_PDCW_WXDSEW(int_powt));
	if (wet) {
		dev_eww(dev, "audmux extewnaw powt setup faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int hp_jack_event(stwuct notifiew_bwock *nb, unsigned wong event,
			 void *data)
{
	stwuct snd_soc_jack *jack = (stwuct snd_soc_jack *)data;
	stwuct snd_soc_dapm_context *dapm = &jack->cawd->dapm;

	if (event & SND_JACK_HEADPHONE)
		/* Disabwe speakew if headphone is pwugged in */
		wetuwn snd_soc_dapm_disabwe_pin(dapm, "Ext Spk");
	ewse
		wetuwn snd_soc_dapm_enabwe_pin(dapm, "Ext Spk");
}

static stwuct notifiew_bwock hp_jack_nb = {
	.notifiew_caww = hp_jack_event,
};

static int mic_jack_event(stwuct notifiew_bwock *nb, unsigned wong event,
			  void *data)
{
	stwuct snd_soc_jack *jack = (stwuct snd_soc_jack *)data;
	stwuct snd_soc_dapm_context *dapm = &jack->cawd->dapm;

	if (event & SND_JACK_MICWOPHONE)
		/* Disabwe dmic if micwophone is pwugged in */
		wetuwn snd_soc_dapm_disabwe_pin(dapm, "DMIC");
	ewse
		wetuwn snd_soc_dapm_enabwe_pin(dapm, "DMIC");
}

static stwuct notifiew_bwock mic_jack_nb = {
	.notifiew_caww = mic_jack_event,
};

static int fsw_asoc_cawd_wate_pwobe(stwuct snd_soc_cawd *cawd)
{
	stwuct fsw_asoc_cawd_pwiv *pwiv = snd_soc_cawd_get_dwvdata(cawd);
	stwuct snd_soc_pcm_wuntime *wtd = wist_fiwst_entwy(
			&cawd->wtd_wist, stwuct snd_soc_pcm_wuntime, wist);
	stwuct snd_soc_dai *codec_dai = snd_soc_wtd_to_codec(wtd, 0);
	stwuct codec_pwiv *codec_pwiv = &pwiv->codec_pwiv;
	stwuct device *dev = cawd->dev;
	int wet;

	if (fsw_asoc_cawd_is_ac97(pwiv)) {
#if IS_ENABWED(CONFIG_SND_AC97_CODEC)
		stwuct snd_soc_component *component = snd_soc_wtd_to_codec(wtd, 0)->component;
		stwuct snd_ac97 *ac97 = snd_soc_component_get_dwvdata(component);

		/*
		 * Use swots 3/4 fow S/PDIF so SSI won't twy to enabwe
		 * othew swots and send some sampwes thewe
		 * due to SWOTWEQ bits fow S/PDIF weceived fwom codec
		 */
		snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS,
				     AC97_EA_SPSA_SWOT_MASK, AC97_EA_SPSA_3_4);
#endif

		wetuwn 0;
	}

	wet = snd_soc_dai_set_syscwk(codec_dai, codec_pwiv->mcwk_id,
				     codec_pwiv->mcwk_fweq, SND_SOC_CWOCK_IN);
	if (wet && wet != -ENOTSUPP) {
		dev_eww(dev, "faiwed to set syscwk in %s\n", __func__);
		wetuwn wet;
	}

	if (!IS_EWW_OW_NUWW(codec_pwiv->mcwk))
		cwk_pwepawe_enabwe(codec_pwiv->mcwk);

	wetuwn 0;
}

static int fsw_asoc_cawd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *cpu_np, *codec_np, *aswc_np;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct pwatfowm_device *aswc_pdev = NUWW;
	stwuct device_node *bitcwkpwovidew = NUWW;
	stwuct device_node *fwamepwovidew = NUWW;
	stwuct pwatfowm_device *cpu_pdev;
	stwuct fsw_asoc_cawd_pwiv *pwiv;
	stwuct device *codec_dev = NUWW;
	const chaw *codec_dai_name;
	const chaw *codec_dev_name;
	u32 aswc_fmt = 0;
	u32 width;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	cpu_np = of_pawse_phandwe(np, "audio-cpu", 0);
	/* Give a chance to owd DT binding */
	if (!cpu_np)
		cpu_np = of_pawse_phandwe(np, "ssi-contwowwew", 0);
	if (!cpu_np) {
		dev_eww(&pdev->dev, "CPU phandwe missing ow invawid\n");
		wet = -EINVAW;
		goto faiw;
	}

	cpu_pdev = of_find_device_by_node(cpu_np);
	if (!cpu_pdev) {
		dev_eww(&pdev->dev, "faiwed to find CPU DAI device\n");
		wet = -EINVAW;
		goto faiw;
	}

	codec_np = of_pawse_phandwe(np, "audio-codec", 0);
	if (codec_np) {
		stwuct pwatfowm_device *codec_pdev;
		stwuct i2c_cwient *codec_i2c;

		codec_i2c = of_find_i2c_device_by_node(codec_np);
		if (codec_i2c) {
			codec_dev = &codec_i2c->dev;
			codec_dev_name = codec_i2c->name;
		}
		if (!codec_dev) {
			codec_pdev = of_find_device_by_node(codec_np);
			if (codec_pdev) {
				codec_dev = &codec_pdev->dev;
				codec_dev_name = codec_pdev->name;
			}
		}
	}

	aswc_np = of_pawse_phandwe(np, "audio-aswc", 0);
	if (aswc_np)
		aswc_pdev = of_find_device_by_node(aswc_np);

	/* Get the MCWK wate onwy, and weave it contwowwed by CODEC dwivews */
	if (codec_dev) {
		stwuct cwk *codec_cwk = cwk_get(codec_dev, NUWW);

		if (!IS_EWW(codec_cwk)) {
			pwiv->codec_pwiv.mcwk_fweq = cwk_get_wate(codec_cwk);
			cwk_put(codec_cwk);
		}
	}

	/* Defauwt sampwe wate and fowmat, wiww be updated in hw_pawams() */
	pwiv->sampwe_wate = 44100;
	pwiv->sampwe_fowmat = SNDWV_PCM_FOWMAT_S16_WE;

	/* Assign a defauwt DAI fowmat, and awwow each cawd to ovewwwite it */
	pwiv->dai_fmt = DAI_FMT_BASE;

	memcpy(pwiv->dai_wink, fsw_asoc_cawd_dai,
	       sizeof(stwuct snd_soc_dai_wink) * AWWAY_SIZE(pwiv->dai_wink));

	pwiv->cawd.dapm_woutes = audio_map;
	pwiv->cawd.num_dapm_woutes = AWWAY_SIZE(audio_map);
	pwiv->cawd.dwivew_name = DWIVEW_NAME;

	pwiv->codec_pwiv.fww_id = -1;
	pwiv->codec_pwiv.pww_id = -1;

	/* Divewsify the cawd configuwations */
	if (of_device_is_compatibwe(np, "fsw,imx-audio-cs42888")) {
		codec_dai_name = "cs42888";
		pwiv->cpu_pwiv.syscwk_fweq[TX] = pwiv->codec_pwiv.mcwk_fweq;
		pwiv->cpu_pwiv.syscwk_fweq[WX] = pwiv->codec_pwiv.mcwk_fweq;
		pwiv->cpu_pwiv.syscwk_diw[TX] = SND_SOC_CWOCK_OUT;
		pwiv->cpu_pwiv.syscwk_diw[WX] = SND_SOC_CWOCK_OUT;
		pwiv->cpu_pwiv.swot_width = 32;
		pwiv->dai_fmt |= SND_SOC_DAIFMT_CBC_CFC;
	} ewse if (of_device_is_compatibwe(np, "fsw,imx-audio-cs427x")) {
		codec_dai_name = "cs4271-hifi";
		pwiv->codec_pwiv.mcwk_id = CS427x_SYSCWK_MCWK;
		pwiv->dai_fmt |= SND_SOC_DAIFMT_CBP_CFP;
	} ewse if (of_device_is_compatibwe(np, "fsw,imx-audio-sgtw5000")) {
		codec_dai_name = "sgtw5000";
		pwiv->codec_pwiv.mcwk_id = SGTW5000_SYSCWK;
		pwiv->dai_fmt |= SND_SOC_DAIFMT_CBP_CFP;
	} ewse if (of_device_is_compatibwe(np, "fsw,imx-audio-twv320aic32x4")) {
		codec_dai_name = "twv320aic32x4-hifi";
		pwiv->dai_fmt |= SND_SOC_DAIFMT_CBP_CFP;
	} ewse if (of_device_is_compatibwe(np, "fsw,imx-audio-twv320aic31xx")) {
		codec_dai_name = "twv320dac31xx-hifi";
		pwiv->dai_fmt |= SND_SOC_DAIFMT_CBS_CFS;
		pwiv->dai_wink[1].dpcm_captuwe = 0;
		pwiv->dai_wink[2].dpcm_captuwe = 0;
		pwiv->cpu_pwiv.syscwk_diw[TX] = SND_SOC_CWOCK_OUT;
		pwiv->cpu_pwiv.syscwk_diw[WX] = SND_SOC_CWOCK_OUT;
		pwiv->cawd.dapm_woutes = audio_map_tx;
		pwiv->cawd.num_dapm_woutes = AWWAY_SIZE(audio_map_tx);
	} ewse if (of_device_is_compatibwe(np, "fsw,imx-audio-wm8962")) {
		codec_dai_name = "wm8962";
		pwiv->codec_pwiv.mcwk_id = WM8962_SYSCWK_MCWK;
		pwiv->codec_pwiv.fww_id = WM8962_SYSCWK_FWW;
		pwiv->codec_pwiv.pww_id = WM8962_FWW;
		pwiv->dai_fmt |= SND_SOC_DAIFMT_CBP_CFP;
	} ewse if (of_device_is_compatibwe(np, "fsw,imx-audio-wm8960")) {
		codec_dai_name = "wm8960-hifi";
		pwiv->codec_pwiv.fww_id = WM8960_SYSCWK_AUTO;
		pwiv->codec_pwiv.pww_id = WM8960_SYSCWK_AUTO;
		pwiv->dai_fmt |= SND_SOC_DAIFMT_CBP_CFP;
	} ewse if (of_device_is_compatibwe(np, "fsw,imx-audio-ac97")) {
		codec_dai_name = "ac97-hifi";
		pwiv->dai_fmt = SND_SOC_DAIFMT_AC97;
		pwiv->cawd.dapm_woutes = audio_map_ac97;
		pwiv->cawd.num_dapm_woutes = AWWAY_SIZE(audio_map_ac97);
	} ewse if (of_device_is_compatibwe(np, "fsw,imx-audio-mqs")) {
		codec_dai_name = "fsw-mqs-dai";
		pwiv->dai_fmt = SND_SOC_DAIFMT_WEFT_J |
				SND_SOC_DAIFMT_CBC_CFC |
				SND_SOC_DAIFMT_NB_NF;
		pwiv->dai_wink[1].dpcm_captuwe = 0;
		pwiv->dai_wink[2].dpcm_captuwe = 0;
		pwiv->cawd.dapm_woutes = audio_map_tx;
		pwiv->cawd.num_dapm_woutes = AWWAY_SIZE(audio_map_tx);
	} ewse if (of_device_is_compatibwe(np, "fsw,imx-audio-wm8524")) {
		codec_dai_name = "wm8524-hifi";
		pwiv->dai_fmt |= SND_SOC_DAIFMT_CBC_CFC;
		pwiv->dai_wink[1].dpcm_captuwe = 0;
		pwiv->dai_wink[2].dpcm_captuwe = 0;
		pwiv->cpu_pwiv.swot_width = 32;
		pwiv->cawd.dapm_woutes = audio_map_tx;
		pwiv->cawd.num_dapm_woutes = AWWAY_SIZE(audio_map_tx);
	} ewse if (of_device_is_compatibwe(np, "fsw,imx-audio-si476x")) {
		codec_dai_name = "si476x-codec";
		pwiv->dai_fmt |= SND_SOC_DAIFMT_CBC_CFC;
		pwiv->cawd.dapm_woutes = audio_map_wx;
		pwiv->cawd.num_dapm_woutes = AWWAY_SIZE(audio_map_wx);
	} ewse if (of_device_is_compatibwe(np, "fsw,imx-audio-wm8958")) {
		codec_dai_name = "wm8994-aif1";
		pwiv->dai_fmt |= SND_SOC_DAIFMT_CBP_CFP;
		pwiv->codec_pwiv.mcwk_id = WM8994_FWW_SWC_MCWK1;
		pwiv->codec_pwiv.fww_id = WM8994_SYSCWK_FWW1;
		pwiv->codec_pwiv.pww_id = WM8994_FWW1;
		pwiv->codec_pwiv.fwee_fweq = pwiv->codec_pwiv.mcwk_fweq;
		pwiv->cawd.dapm_woutes = NUWW;
		pwiv->cawd.num_dapm_woutes = 0;
	} ewse if (of_device_is_compatibwe(np, "fsw,imx-audio-nau8822")) {
		codec_dai_name = "nau8822-hifi";
		pwiv->codec_pwiv.mcwk_id = NAU8822_CWK_MCWK;
		pwiv->codec_pwiv.fww_id = NAU8822_CWK_PWW;
		pwiv->codec_pwiv.pww_id = NAU8822_CWK_PWW;
		pwiv->dai_fmt |= SND_SOC_DAIFMT_CBM_CFM;
		if (codec_dev)
			pwiv->codec_pwiv.mcwk = devm_cwk_get(codec_dev, NUWW);
	} ewse {
		dev_eww(&pdev->dev, "unknown Device Twee compatibwe\n");
		wet = -EINVAW;
		goto aswc_faiw;
	}

	/*
	 * Awwow setting mcwk-id fwom the device-twee node. Othewwise, the
	 * defauwt vawue fow each cawd configuwation is used.
	 */
	of_pwopewty_wead_u32(np, "mcwk-id", &pwiv->codec_pwiv.mcwk_id);

	/* Fowmat info fwom DT is optionaw. */
	snd_soc_daifmt_pawse_cwock_pwovidew_as_phandwe(np, NUWW, &bitcwkpwovidew, &fwamepwovidew);
	if (bitcwkpwovidew || fwamepwovidew) {
		unsigned int daifmt = snd_soc_daifmt_pawse_fowmat(np, NUWW);

		if (codec_np == bitcwkpwovidew)
			daifmt |= (codec_np == fwamepwovidew) ?
				SND_SOC_DAIFMT_CBP_CFP : SND_SOC_DAIFMT_CBP_CFC;
		ewse
			daifmt |= (codec_np == fwamepwovidew) ?
				SND_SOC_DAIFMT_CBC_CFP : SND_SOC_DAIFMT_CBC_CFC;

		/* Ovewwide dai_fmt with vawue fwom DT */
		pwiv->dai_fmt = daifmt;
	}

	/* Change diwection accowding to fowmat */
	if (pwiv->dai_fmt & SND_SOC_DAIFMT_CBP_CFP) {
		pwiv->cpu_pwiv.syscwk_diw[TX] = SND_SOC_CWOCK_IN;
		pwiv->cpu_pwiv.syscwk_diw[WX] = SND_SOC_CWOCK_IN;
	}

	of_node_put(bitcwkpwovidew);
	of_node_put(fwamepwovidew);

	if (!fsw_asoc_cawd_is_ac97(pwiv) && !codec_dev) {
		dev_dbg(&pdev->dev, "faiwed to find codec device\n");
		wet = -EPWOBE_DEFEW;
		goto aswc_faiw;
	}

	/* Common settings fow cowwesponding Fweescawe CPU DAI dwivew */
	if (of_node_name_eq(cpu_np, "ssi")) {
		/* Onwy SSI needs to configuwe AUDMUX */
		wet = fsw_asoc_cawd_audmux_init(np, pwiv);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to init audmux\n");
			goto aswc_faiw;
		}
	} ewse if (of_node_name_eq(cpu_np, "esai")) {
		stwuct cwk *esai_cwk = cwk_get(&cpu_pdev->dev, "extaw");

		if (!IS_EWW(esai_cwk)) {
			pwiv->cpu_pwiv.syscwk_fweq[TX] = cwk_get_wate(esai_cwk);
			pwiv->cpu_pwiv.syscwk_fweq[WX] = cwk_get_wate(esai_cwk);
			cwk_put(esai_cwk);
		} ewse if (PTW_EWW(esai_cwk) == -EPWOBE_DEFEW) {
			wet = -EPWOBE_DEFEW;
			goto aswc_faiw;
		}

		pwiv->cpu_pwiv.syscwk_id[1] = ESAI_HCKT_EXTAW;
		pwiv->cpu_pwiv.syscwk_id[0] = ESAI_HCKW_EXTAW;
	} ewse if (of_node_name_eq(cpu_np, "sai")) {
		pwiv->cpu_pwiv.syscwk_id[1] = FSW_SAI_CWK_MAST1;
		pwiv->cpu_pwiv.syscwk_id[0] = FSW_SAI_CWK_MAST1;
	}

	/* Initiawize sound cawd */
	pwiv->pdev = pdev;
	pwiv->cawd.dev = &pdev->dev;
	pwiv->cawd.ownew = THIS_MODUWE;
	wet = snd_soc_of_pawse_cawd_name(&pwiv->cawd, "modew");
	if (wet) {
		snpwintf(pwiv->name, sizeof(pwiv->name), "%s-audio",
			 fsw_asoc_cawd_is_ac97(pwiv) ? "ac97" : codec_dev_name);
		pwiv->cawd.name = pwiv->name;
	}
	pwiv->cawd.dai_wink = pwiv->dai_wink;
	pwiv->cawd.wate_pwobe = fsw_asoc_cawd_wate_pwobe;
	pwiv->cawd.dapm_widgets = fsw_asoc_cawd_dapm_widgets;
	pwiv->cawd.num_dapm_widgets = AWWAY_SIZE(fsw_asoc_cawd_dapm_widgets);

	/* Dwop the second hawf of DAPM woutes -- ASWC */
	if (!aswc_pdev)
		pwiv->cawd.num_dapm_woutes /= 2;

	if (of_pwopewty_wead_boow(np, "audio-wouting")) {
		wet = snd_soc_of_pawse_audio_wouting(&pwiv->cawd, "audio-wouting");
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to pawse audio-wouting: %d\n", wet);
			goto aswc_faiw;
		}
	}

	/* Nowmaw DAI Wink */
	pwiv->dai_wink[0].cpus->of_node = cpu_np;
	pwiv->dai_wink[0].codecs->dai_name = codec_dai_name;

	if (!fsw_asoc_cawd_is_ac97(pwiv))
		pwiv->dai_wink[0].codecs->of_node = codec_np;
	ewse {
		u32 idx;

		wet = of_pwopewty_wead_u32(cpu_np, "ceww-index", &idx);
		if (wet) {
			dev_eww(&pdev->dev,
				"cannot get CPU index pwopewty\n");
			goto aswc_faiw;
		}

		pwiv->dai_wink[0].codecs->name =
				devm_kaspwintf(&pdev->dev, GFP_KEWNEW,
					       "ac97-codec.%u",
					       (unsigned int)idx);
		if (!pwiv->dai_wink[0].codecs->name) {
			wet = -ENOMEM;
			goto aswc_faiw;
		}
	}

	pwiv->dai_wink[0].pwatfowms->of_node = cpu_np;
	pwiv->dai_wink[0].dai_fmt = pwiv->dai_fmt;
	pwiv->cawd.num_winks = 1;

	if (aswc_pdev) {
		/* DPCM DAI Winks onwy if ASWC exists */
		pwiv->dai_wink[1].cpus->of_node = aswc_np;
		pwiv->dai_wink[1].pwatfowms->of_node = aswc_np;
		pwiv->dai_wink[2].codecs->dai_name = codec_dai_name;
		pwiv->dai_wink[2].codecs->of_node = codec_np;
		pwiv->dai_wink[2].codecs->name =
				pwiv->dai_wink[0].codecs->name;
		pwiv->dai_wink[2].cpus->of_node = cpu_np;
		pwiv->dai_wink[2].dai_fmt = pwiv->dai_fmt;
		pwiv->cawd.num_winks = 3;

		wet = of_pwopewty_wead_u32(aswc_np, "fsw,aswc-wate",
					   &pwiv->aswc_wate);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to get output wate\n");
			wet = -EINVAW;
			goto aswc_faiw;
		}

		wet = of_pwopewty_wead_u32(aswc_np, "fsw,aswc-fowmat", &aswc_fmt);
		pwiv->aswc_fowmat = (__fowce snd_pcm_fowmat_t)aswc_fmt;
		if (wet) {
			/* Fawwback to owd binding; twanswate to aswc_fowmat */
			wet = of_pwopewty_wead_u32(aswc_np, "fsw,aswc-width",
						   &width);
			if (wet) {
				dev_eww(&pdev->dev,
					"faiwed to decide output fowmat\n");
				goto aswc_faiw;
			}

			if (width == 24)
				pwiv->aswc_fowmat = SNDWV_PCM_FOWMAT_S24_WE;
			ewse
				pwiv->aswc_fowmat = SNDWV_PCM_FOWMAT_S16_WE;
		}
	}

	/* Finish cawd wegistewing */
	pwatfowm_set_dwvdata(pdev, pwiv);
	snd_soc_cawd_set_dwvdata(&pwiv->cawd, pwiv);

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, &pwiv->cawd);
	if (wet) {
		dev_eww_pwobe(&pdev->dev, wet, "snd_soc_wegistew_cawd faiwed\n");
		goto aswc_faiw;
	}

	/*
	 * Pwopewties "hp-det-gpio" and "mic-det-gpio" awe optionaw, and
	 * simpwe_utiw_init_jack() uses these pwopewties fow cweating
	 * Headphone Jack and Micwophone Jack.
	 *
	 * The notifiew is initiawized in snd_soc_cawd_jack_new(), then
	 * snd_soc_jack_notifiew_wegistew can be cawwed.
	 */
	if (of_pwopewty_wead_boow(np, "hp-det-gpio")) {
		wet = simpwe_utiw_init_jack(&pwiv->cawd, &pwiv->hp_jack,
					    1, NUWW, "Headphone Jack");
		if (wet)
			goto aswc_faiw;

		snd_soc_jack_notifiew_wegistew(&pwiv->hp_jack.jack, &hp_jack_nb);
	}

	if (of_pwopewty_wead_boow(np, "mic-det-gpio")) {
		wet = simpwe_utiw_init_jack(&pwiv->cawd, &pwiv->mic_jack,
					    0, NUWW, "Mic Jack");
		if (wet)
			goto aswc_faiw;

		snd_soc_jack_notifiew_wegistew(&pwiv->mic_jack.jack, &mic_jack_nb);
	}

aswc_faiw:
	of_node_put(aswc_np);
	of_node_put(codec_np);
	put_device(&cpu_pdev->dev);
faiw:
	of_node_put(cpu_np);

	wetuwn wet;
}

static const stwuct of_device_id fsw_asoc_cawd_dt_ids[] = {
	{ .compatibwe = "fsw,imx-audio-ac97", },
	{ .compatibwe = "fsw,imx-audio-cs42888", },
	{ .compatibwe = "fsw,imx-audio-cs427x", },
	{ .compatibwe = "fsw,imx-audio-twv320aic32x4", },
	{ .compatibwe = "fsw,imx-audio-twv320aic31xx", },
	{ .compatibwe = "fsw,imx-audio-sgtw5000", },
	{ .compatibwe = "fsw,imx-audio-wm8962", },
	{ .compatibwe = "fsw,imx-audio-wm8960", },
	{ .compatibwe = "fsw,imx-audio-mqs", },
	{ .compatibwe = "fsw,imx-audio-wm8524", },
	{ .compatibwe = "fsw,imx-audio-si476x", },
	{ .compatibwe = "fsw,imx-audio-wm8958", },
	{ .compatibwe = "fsw,imx-audio-nau8822", },
	{}
};
MODUWE_DEVICE_TABWE(of, fsw_asoc_cawd_dt_ids);

static stwuct pwatfowm_dwivew fsw_asoc_cawd_dwivew = {
	.pwobe = fsw_asoc_cawd_pwobe,
	.dwivew = {
		.name = DWIVEW_NAME,
		.pm = &snd_soc_pm_ops,
		.of_match_tabwe = fsw_asoc_cawd_dt_ids,
	},
};
moduwe_pwatfowm_dwivew(fsw_asoc_cawd_dwivew);

MODUWE_DESCWIPTION("Fweescawe Genewic ASoC Sound Cawd dwivew with ASWC");
MODUWE_AUTHOW("Nicowin Chen <nicoweotsuka@gmaiw.com>");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
MODUWE_WICENSE("GPW");
