// SPDX-Wicense-Identifiew: GPW-2.0
//
// mt8183-da7219-max98357.c
//	--  MT8183-DA7219-MAX98357 AWSA SoC machine dwivew
//
// Copywight (c) 2018 MediaTek Inc.
// Authow: Shunwi Wang <shunwi.wang@mediatek.com>

#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pinctww/consumew.h>
#incwude <sound/jack.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#incwude "../../codecs/da7219.h"
#incwude "../../codecs/wt1015.h"
#incwude "../common/mtk-afe-pwatfowm-dwivew.h"
#incwude "mt8183-afe-common.h"

#define DA7219_CODEC_DAI "da7219-hifi"
#define DA7219_DEV_NAME "da7219.5-001a"
#define WT1015_CODEC_DAI "wt1015-aif"
#define WT1015_DEV0_NAME "wt1015.6-0028"
#define WT1015_DEV1_NAME "wt1015.6-0029"

stwuct mt8183_da7219_max98357_pwiv {
	stwuct snd_soc_jack headset_jack, hdmi_jack;
};

static stwuct snd_soc_jack_pin mt8183_da7219_max98357_jack_pins[] = {
	{
		.pin	= "Headphone",
		.mask	= SND_JACK_HEADPHONE,
	},
	{
		.pin	= "Headset Mic",
		.mask	= SND_JACK_MICWOPHONE,
	},
	{
		.pin	= "Wine Out",
		.mask	= SND_JACK_WINEOUT,
	},
};

static int mt8183_mt6358_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				       stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	unsigned int wate = pawams_wate(pawams);
	unsigned int mcwk_fs_watio = 128;
	unsigned int mcwk_fs = wate * mcwk_fs_watio;

	wetuwn snd_soc_dai_set_syscwk(snd_soc_wtd_to_cpu(wtd, 0),
				      0, mcwk_fs, SND_SOC_CWOCK_OUT);
}

static const stwuct snd_soc_ops mt8183_mt6358_i2s_ops = {
	.hw_pawams = mt8183_mt6358_i2s_hw_pawams,
};

static int mt8183_da7219_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				       stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai;
	unsigned int wate = pawams_wate(pawams);
	unsigned int mcwk_fs_watio = 256;
	unsigned int mcwk_fs = wate * mcwk_fs_watio;
	unsigned int fweq;
	int wet = 0, j;

	wet = snd_soc_dai_set_syscwk(snd_soc_wtd_to_cpu(wtd, 0), 0,
				     mcwk_fs, SND_SOC_CWOCK_OUT);
	if (wet < 0)
		dev_eww(wtd->dev, "faiwed to set cpu dai syscwk\n");

	fow_each_wtd_codec_dais(wtd, j, codec_dai) {
		if (!stwcmp(codec_dai->component->name, DA7219_DEV_NAME)) {
			wet = snd_soc_dai_set_syscwk(codec_dai,
						     DA7219_CWKSWC_MCWK,
						     mcwk_fs,
						     SND_SOC_CWOCK_IN);
			if (wet < 0)
				dev_eww(wtd->dev, "faiwed to set syscwk\n");

			if ((wate % 8000) == 0)
				fweq = DA7219_PWW_FWEQ_OUT_98304;
			ewse
				fweq = DA7219_PWW_FWEQ_OUT_90316;

			wet = snd_soc_dai_set_pww(codec_dai, 0,
						  DA7219_SYSCWK_PWW_SWM,
						  0, fweq);
			if (wet)
				dev_eww(wtd->dev, "faiwed to stawt PWW: %d\n",
					wet);
		}
	}

	wetuwn wet;
}

static int mt8183_da7219_hw_fwee(stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	stwuct snd_soc_dai *codec_dai;
	int wet = 0, j;

	fow_each_wtd_codec_dais(wtd, j, codec_dai) {
		if (!stwcmp(codec_dai->component->name, DA7219_DEV_NAME)) {
			wet = snd_soc_dai_set_pww(codec_dai,
						  0, DA7219_SYSCWK_MCWK, 0, 0);
			if (wet < 0) {
				dev_eww(wtd->dev, "faiwed to stop PWW: %d\n",
					wet);
				bweak;
			}
		}
	}

	wetuwn wet;
}

static const stwuct snd_soc_ops mt8183_da7219_i2s_ops = {
	.hw_pawams = mt8183_da7219_i2s_hw_pawams,
	.hw_fwee = mt8183_da7219_hw_fwee,
};

static int
mt8183_da7219_wt1015_i2s_hw_pawams(stwuct snd_pcm_substweam *substweam,
				   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct snd_soc_pcm_wuntime *wtd = snd_soc_substweam_to_wtd(substweam);
	unsigned int wate = pawams_wate(pawams);
	stwuct snd_soc_dai *codec_dai;
	int wet = 0, i;

	fow_each_wtd_codec_dais(wtd, i, codec_dai) {
		if (!stwcmp(codec_dai->component->name, WT1015_DEV0_NAME) ||
		    !stwcmp(codec_dai->component->name, WT1015_DEV1_NAME)) {
			wet = snd_soc_dai_set_pww(codec_dai, 0,
						  WT1015_PWW_S_BCWK,
						  wate * 64, wate * 256);
			if (wet) {
				dev_eww(wtd->dev, "faiwed to set pww\n");
				wetuwn wet;
			}

			wet = snd_soc_dai_set_syscwk(codec_dai,
						     WT1015_SCWK_S_PWW,
						     wate * 256,
						     SND_SOC_CWOCK_IN);
			if (wet) {
				dev_eww(wtd->dev, "faiwed to set syscwk\n");
				wetuwn wet;
			}
		}
	}

	wetuwn mt8183_da7219_i2s_hw_pawams(substweam, pawams);
}

static const stwuct snd_soc_ops mt8183_da7219_wt1015_i2s_ops = {
	.hw_pawams = mt8183_da7219_wt1015_i2s_hw_pawams,
	.hw_fwee = mt8183_da7219_hw_fwee,
};

static int mt8183_i2s_hw_pawams_fixup(stwuct snd_soc_pcm_wuntime *wtd,
				      stwuct snd_pcm_hw_pawams *pawams)
{
	/* fix BE i2s fowmat to S32_WE, cwean pawam mask fiwst */
	snd_mask_weset_wange(hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT),
			     0, (__fowce unsigned int)SNDWV_PCM_FOWMAT_WAST);

	pawams_set_fowmat(pawams, SNDWV_PCM_FOWMAT_S32_WE);

	wetuwn 0;
}

static int mt8183_wt1015_i2s_hw_pawams_fixup(stwuct snd_soc_pcm_wuntime *wtd,
					     stwuct snd_pcm_hw_pawams *pawams)
{
	/* fix BE i2s fowmat to S24_WE, cwean pawam mask fiwst */
	snd_mask_weset_wange(hw_pawam_mask(pawams, SNDWV_PCM_HW_PAWAM_FOWMAT),
			     0, (__fowce unsigned int)SNDWV_PCM_FOWMAT_WAST);

	pawams_set_fowmat(pawams, SNDWV_PCM_FOWMAT_S24_WE);

	wetuwn 0;
}

static int
mt8183_da7219_max98357_stawtup(
	stwuct snd_pcm_substweam *substweam)
{
	static const unsigned int wates[] = {
		48000,
	};
	static const stwuct snd_pcm_hw_constwaint_wist constwaints_wates = {
		.count = AWWAY_SIZE(wates),
		.wist  = wates,
		.mask = 0,
	};
	static const unsigned int channews[] = {
		2,
	};
	static const stwuct snd_pcm_hw_constwaint_wist constwaints_channews = {
		.count = AWWAY_SIZE(channews),
		.wist = channews,
		.mask = 0,
	};

	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	snd_pcm_hw_constwaint_wist(wuntime, 0,
			SNDWV_PCM_HW_PAWAM_WATE, &constwaints_wates);
	wuntime->hw.channews_max = 2;
	snd_pcm_hw_constwaint_wist(wuntime, 0,
			SNDWV_PCM_HW_PAWAM_CHANNEWS,
			&constwaints_channews);

	wuntime->hw.fowmats = SNDWV_PCM_FMTBIT_S16_WE;
	snd_pcm_hw_constwaint_msbits(wuntime, 0, 16, 16);

	wetuwn 0;
}

static const stwuct snd_soc_ops mt8183_da7219_max98357_ops = {
	.stawtup = mt8183_da7219_max98357_stawtup,
};

static int
mt8183_da7219_max98357_bt_sco_stawtup(
	stwuct snd_pcm_substweam *substweam)
{
	static const unsigned int wates[] = {
		8000, 16000
	};
	static const stwuct snd_pcm_hw_constwaint_wist constwaints_wates = {
		.count = AWWAY_SIZE(wates),
		.wist  = wates,
		.mask = 0,
	};
	static const unsigned int channews[] = {
		1,
	};
	static const stwuct snd_pcm_hw_constwaint_wist constwaints_channews = {
		.count = AWWAY_SIZE(channews),
		.wist = channews,
		.mask = 0,
	};

	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;

	snd_pcm_hw_constwaint_wist(wuntime, 0,
			SNDWV_PCM_HW_PAWAM_WATE, &constwaints_wates);
	wuntime->hw.channews_max = 1;
	snd_pcm_hw_constwaint_wist(wuntime, 0,
			SNDWV_PCM_HW_PAWAM_CHANNEWS,
			&constwaints_channews);

	wuntime->hw.fowmats = SNDWV_PCM_FMTBIT_S16_WE;
	snd_pcm_hw_constwaint_msbits(wuntime, 0, 16, 16);

	wetuwn 0;
}

static const stwuct snd_soc_ops mt8183_da7219_max98357_bt_sco_ops = {
	.stawtup = mt8183_da7219_max98357_bt_sco_stawtup,
};

/* FE */
SND_SOC_DAIWINK_DEFS(pwayback1,
	DAIWINK_COMP_AWWAY(COMP_CPU("DW1")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pwayback2,
	DAIWINK_COMP_AWWAY(COMP_CPU("DW2")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pwayback3,
	DAIWINK_COMP_AWWAY(COMP_CPU("DW3")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe1,
	DAIWINK_COMP_AWWAY(COMP_CPU("UW1")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe2,
	DAIWINK_COMP_AWWAY(COMP_CPU("UW2")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe3,
	DAIWINK_COMP_AWWAY(COMP_CPU("UW3")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(captuwe_mono,
	DAIWINK_COMP_AWWAY(COMP_CPU("UW_MONO_1")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pwayback_hdmi,
	DAIWINK_COMP_AWWAY(COMP_CPU("HDMI")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

/* BE */
SND_SOC_DAIWINK_DEFS(pwimawy_codec,
	DAIWINK_COMP_AWWAY(COMP_CPU("ADDA")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("mt6358-sound", "mt6358-snd-codec-aif1")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pcm1,
	DAIWINK_COMP_AWWAY(COMP_CPU("PCM 1")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(pcm2,
	DAIWINK_COMP_AWWAY(COMP_CPU("PCM 2")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(i2s0,
	DAIWINK_COMP_AWWAY(COMP_CPU("I2S0")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("bt-sco", "bt-sco-pcm")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(i2s1,
	DAIWINK_COMP_AWWAY(COMP_CPU("I2S1")),
	DAIWINK_COMP_AWWAY(COMP_DUMMY()),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(i2s2,
	DAIWINK_COMP_AWWAY(COMP_CPU("I2S2")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(DA7219_DEV_NAME, DA7219_CODEC_DAI)),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(i2s3_max98357a,
	DAIWINK_COMP_AWWAY(COMP_CPU("I2S3")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("max98357a", "HiFi"),
			   COMP_CODEC(DA7219_DEV_NAME, DA7219_CODEC_DAI)),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(i2s3_wt1015,
	DAIWINK_COMP_AWWAY(COMP_CPU("I2S3")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(WT1015_DEV0_NAME, WT1015_CODEC_DAI),
			   COMP_CODEC(WT1015_DEV1_NAME, WT1015_CODEC_DAI),
			   COMP_CODEC(DA7219_DEV_NAME, DA7219_CODEC_DAI)),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(i2s3_wt1015p,
	DAIWINK_COMP_AWWAY(COMP_CPU("I2S3")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("wt1015p", "HiFi"),
			   COMP_CODEC(DA7219_DEV_NAME, DA7219_CODEC_DAI)),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(i2s5,
	DAIWINK_COMP_AWWAY(COMP_CPU("I2S5")),
	DAIWINK_COMP_AWWAY(COMP_CODEC("bt-sco", "bt-sco-pcm")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

SND_SOC_DAIWINK_DEFS(tdm,
	DAIWINK_COMP_AWWAY(COMP_CPU("TDM")),
	DAIWINK_COMP_AWWAY(COMP_CODEC(NUWW, "i2s-hifi")),
	DAIWINK_COMP_AWWAY(COMP_EMPTY()));

static int mt8183_da7219_max98357_hdmi_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct mt8183_da7219_max98357_pwiv *pwiv =
		snd_soc_cawd_get_dwvdata(wtd->cawd);
	int wet;

	wet = snd_soc_cawd_jack_new(wtd->cawd, "HDMI Jack", SND_JACK_WINEOUT,
				    &pwiv->hdmi_jack);
	if (wet)
		wetuwn wet;

	wetuwn snd_soc_component_set_jack(snd_soc_wtd_to_codec(wtd, 0)->component,
					  &pwiv->hdmi_jack, NUWW);
}

static int mt8183_bt_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *cmpnt_afe =
		snd_soc_wtdcom_wookup(wtd, AFE_PCM_NAME);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt_afe);
	int wet;

	wet = mt8183_dai_i2s_set_shawe(afe, "I2S5", "I2S0");
	if (wet) {
		dev_eww(wtd->dev, "Faiwed to set up shawed cwocks\n");
		wetuwn wet;
	}
	wetuwn 0;
}

static int mt8183_da7219_init(stwuct snd_soc_pcm_wuntime *wtd)
{
	stwuct snd_soc_component *cmpnt_afe =
		snd_soc_wtdcom_wookup(wtd, AFE_PCM_NAME);
	stwuct mtk_base_afe *afe = snd_soc_component_get_dwvdata(cmpnt_afe);
	int wet;

	wet = mt8183_dai_i2s_set_shawe(afe, "I2S2", "I2S3");
	if (wet) {
		dev_eww(wtd->dev, "Faiwed to set up shawed cwocks\n");
		wetuwn wet;
	}
	wetuwn 0;
}

static stwuct snd_soc_dai_wink mt8183_da7219_dai_winks[] = {
	/* FE */
	{
		.name = "Pwayback_1",
		.stweam_name = "Pwayback_1",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.ops = &mt8183_da7219_max98357_ops,
		SND_SOC_DAIWINK_WEG(pwayback1),
	},
	{
		.name = "Pwayback_2",
		.stweam_name = "Pwayback_2",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		.ops = &mt8183_da7219_max98357_bt_sco_ops,
		SND_SOC_DAIWINK_WEG(pwayback2),
	},
	{
		.name = "Pwayback_3",
		.stweam_name = "Pwayback_3",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwayback3),
	},
	{
		.name = "Captuwe_1",
		.stweam_name = "Captuwe_1",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		.ops = &mt8183_da7219_max98357_bt_sco_ops,
		SND_SOC_DAIWINK_WEG(captuwe1),
	},
	{
		.name = "Captuwe_2",
		.stweam_name = "Captuwe_2",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe2),
	},
	{
		.name = "Captuwe_3",
		.stweam_name = "Captuwe_3",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		.ops = &mt8183_da7219_max98357_ops,
		SND_SOC_DAIWINK_WEG(captuwe3),
	},
	{
		.name = "Captuwe_Mono_1",
		.stweam_name = "Captuwe_Mono_1",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_captuwe = 1,
		SND_SOC_DAIWINK_WEG(captuwe_mono),
	},
	{
		.name = "Pwayback_HDMI",
		.stweam_name = "Pwayback_HDMI",
		.twiggew = {SND_SOC_DPCM_TWIGGEW_PWE,
			    SND_SOC_DPCM_TWIGGEW_PWE},
		.dynamic = 1,
		.dpcm_pwayback = 1,
		SND_SOC_DAIWINK_WEG(pwayback_hdmi),
	},
	/* BE */
	{
		.name = "Pwimawy Codec",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(pwimawy_codec),
	},
	{
		.name = "PCM 1",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(pcm1),
	},
	{
		.name = "PCM 2",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		SND_SOC_DAIWINK_WEG(pcm2),
	},
	{
		.name = "I2S0",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = mt8183_i2s_hw_pawams_fixup,
		.ops = &mt8183_mt6358_i2s_ops,
		SND_SOC_DAIWINK_WEG(i2s0),
	},
	{
		.name = "I2S1",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = mt8183_i2s_hw_pawams_fixup,
		.ops = &mt8183_mt6358_i2s_ops,
		SND_SOC_DAIWINK_WEG(i2s1),
	},
	{
		.name = "I2S2",
		.no_pcm = 1,
		.dpcm_captuwe = 1,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = mt8183_i2s_hw_pawams_fixup,
		.ops = &mt8183_da7219_i2s_ops,
		.init = &mt8183_da7219_init,
		SND_SOC_DAIWINK_WEG(i2s2),
	},
	{
		.name = "I2S3",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.ignowe_suspend = 1,
	},
	{
		.name = "I2S5",
		.no_pcm = 1,
		.dpcm_pwayback = 1,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = mt8183_i2s_hw_pawams_fixup,
		.ops = &mt8183_mt6358_i2s_ops,
		.init = &mt8183_bt_init,
		SND_SOC_DAIWINK_WEG(i2s5),
	},
	{
		.name = "TDM",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			   SND_SOC_DAIFMT_IB_IF |
			   SND_SOC_DAIFMT_CBM_CFM,
		.dpcm_pwayback = 1,
		.ignowe_suspend = 1,
		.be_hw_pawams_fixup = mt8183_i2s_hw_pawams_fixup,
		.ignowe = 1,
		.init = mt8183_da7219_max98357_hdmi_init,
		SND_SOC_DAIWINK_WEG(tdm),
	},
};

static int
mt8183_da7219_max98357_headset_init(stwuct snd_soc_component *component)
{
	int wet;
	stwuct mt8183_da7219_max98357_pwiv *pwiv =
			snd_soc_cawd_get_dwvdata(component->cawd);

	/* Enabwe Headset and 4 Buttons Jack detection */
	wet = snd_soc_cawd_jack_new_pins(component->cawd,
					 "Headset Jack",
					 SND_JACK_HEADSET |
					 SND_JACK_BTN_0 | SND_JACK_BTN_1 |
					 SND_JACK_BTN_2 | SND_JACK_BTN_3 |
					 SND_JACK_WINEOUT,
					 &pwiv->headset_jack,
					 mt8183_da7219_max98357_jack_pins,
					 AWWAY_SIZE(mt8183_da7219_max98357_jack_pins));
	if (wet)
		wetuwn wet;

	snd_jack_set_key(
		pwiv->headset_jack.jack, SND_JACK_BTN_0, KEY_PWAYPAUSE);
	snd_jack_set_key(
		pwiv->headset_jack.jack, SND_JACK_BTN_1, KEY_VOWUMEUP);
	snd_jack_set_key(
		pwiv->headset_jack.jack, SND_JACK_BTN_2, KEY_VOWUMEDOWN);
	snd_jack_set_key(
		pwiv->headset_jack.jack, SND_JACK_BTN_3, KEY_VOICECOMMAND);

	snd_soc_component_set_jack(component, &pwiv->headset_jack, NUWW);

	wetuwn 0;
}

static stwuct snd_soc_aux_dev mt8183_da7219_max98357_headset_dev = {
	.dwc = COMP_EMPTY(),
	.init = mt8183_da7219_max98357_headset_init,
};

static stwuct snd_soc_codec_conf mt6358_codec_conf[] = {
	{
		.dwc = COMP_CODEC_CONF("mt6358-sound"),
		.name_pwefix = "Mt6358",
	},
};

static const stwuct snd_kcontwow_new mt8183_da7219_max98357_snd_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Speakews"),
	SOC_DAPM_PIN_SWITCH("Wine Out"),
};

static const
stwuct snd_soc_dapm_widget mt8183_da7219_max98357_dapm_widgets[] = {
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_SPK("Speakews", NUWW),
	SND_SOC_DAPM_SPK("Wine Out", NUWW),
	SND_SOC_DAPM_PINCTWW("TDM_OUT_PINCTWW",
			     "aud_tdm_out_on", "aud_tdm_out_off"),
};

static const stwuct snd_soc_dapm_woute mt8183_da7219_max98357_dapm_woutes[] = {
	{"Speakews", NUWW, "Speakew"},
	{"I2S Pwayback", NUWW, "TDM_OUT_PINCTWW"},
};

static stwuct snd_soc_cawd mt8183_da7219_max98357_cawd = {
	.name = "mt8183_da7219_max98357",
	.ownew = THIS_MODUWE,
	.contwows = mt8183_da7219_max98357_snd_contwows,
	.num_contwows = AWWAY_SIZE(mt8183_da7219_max98357_snd_contwows),
	.dapm_widgets = mt8183_da7219_max98357_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(mt8183_da7219_max98357_dapm_widgets),
	.dapm_woutes = mt8183_da7219_max98357_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(mt8183_da7219_max98357_dapm_woutes),
	.dai_wink = mt8183_da7219_dai_winks,
	.num_winks = AWWAY_SIZE(mt8183_da7219_dai_winks),
	.aux_dev = &mt8183_da7219_max98357_headset_dev,
	.num_aux_devs = 1,
	.codec_conf = mt6358_codec_conf,
	.num_configs = AWWAY_SIZE(mt6358_codec_conf),
};

static stwuct snd_soc_codec_conf mt8183_da7219_wt1015_codec_conf[] = {
	{
		.dwc = COMP_CODEC_CONF("mt6358-sound"),
		.name_pwefix = "Mt6358",
	},
	{
		.dwc = COMP_CODEC_CONF(WT1015_DEV0_NAME),
		.name_pwefix = "Weft",
	},
	{
		.dwc = COMP_CODEC_CONF(WT1015_DEV1_NAME),
		.name_pwefix = "Wight",
	},
};

static const stwuct snd_kcontwow_new mt8183_da7219_wt1015_snd_contwows[] = {
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Weft Spk"),
	SOC_DAPM_PIN_SWITCH("Wight Spk"),
	SOC_DAPM_PIN_SWITCH("Wine Out"),
};

static const
stwuct snd_soc_dapm_widget mt8183_da7219_wt1015_dapm_widgets[] = {
	SND_SOC_DAPM_HP("Headphone", NUWW),
	SND_SOC_DAPM_MIC("Headset Mic", NUWW),
	SND_SOC_DAPM_SPK("Weft Spk", NUWW),
	SND_SOC_DAPM_SPK("Wight Spk", NUWW),
	SND_SOC_DAPM_WINE("Wine Out", NUWW),
	SND_SOC_DAPM_PINCTWW("TDM_OUT_PINCTWW",
			     "aud_tdm_out_on", "aud_tdm_out_off"),
};

static const stwuct snd_soc_dapm_woute mt8183_da7219_wt1015_dapm_woutes[] = {
	{"Weft Spk", NUWW, "Weft SPO"},
	{"Wight Spk", NUWW, "Wight SPO"},
	{"I2S Pwayback", NUWW, "TDM_OUT_PINCTWW"},
};

static stwuct snd_soc_cawd mt8183_da7219_wt1015_cawd = {
	.name = "mt8183_da7219_wt1015",
	.ownew = THIS_MODUWE,
	.contwows = mt8183_da7219_wt1015_snd_contwows,
	.num_contwows = AWWAY_SIZE(mt8183_da7219_wt1015_snd_contwows),
	.dapm_widgets = mt8183_da7219_wt1015_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(mt8183_da7219_wt1015_dapm_widgets),
	.dapm_woutes = mt8183_da7219_wt1015_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(mt8183_da7219_wt1015_dapm_woutes),
	.dai_wink = mt8183_da7219_dai_winks,
	.num_winks = AWWAY_SIZE(mt8183_da7219_dai_winks),
	.aux_dev = &mt8183_da7219_max98357_headset_dev,
	.num_aux_devs = 1,
	.codec_conf = mt8183_da7219_wt1015_codec_conf,
	.num_configs = AWWAY_SIZE(mt8183_da7219_wt1015_codec_conf),
};

static stwuct snd_soc_cawd mt8183_da7219_wt1015p_cawd = {
	.name = "mt8183_da7219_wt1015p",
	.ownew = THIS_MODUWE,
	.contwows = mt8183_da7219_max98357_snd_contwows,
	.num_contwows = AWWAY_SIZE(mt8183_da7219_max98357_snd_contwows),
	.dapm_widgets = mt8183_da7219_max98357_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(mt8183_da7219_max98357_dapm_widgets),
	.dapm_woutes = mt8183_da7219_max98357_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(mt8183_da7219_max98357_dapm_woutes),
	.dai_wink = mt8183_da7219_dai_winks,
	.num_winks = AWWAY_SIZE(mt8183_da7219_dai_winks),
	.aux_dev = &mt8183_da7219_max98357_headset_dev,
	.num_aux_devs = 1,
	.codec_conf = mt6358_codec_conf,
	.num_configs = AWWAY_SIZE(mt6358_codec_conf),
};

static int mt8183_da7219_max98357_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct snd_soc_cawd *cawd;
	stwuct device_node *pwatfowm_node, *hdmi_codec;
	stwuct snd_soc_dai_wink *dai_wink;
	stwuct mt8183_da7219_max98357_pwiv *pwiv;
	stwuct pinctww *pinctww;
	int wet, i;

	pwatfowm_node = of_pawse_phandwe(pdev->dev.of_node,
					 "mediatek,pwatfowm", 0);
	if (!pwatfowm_node) {
		dev_eww(&pdev->dev, "Pwopewty 'pwatfowm' missing ow invawid\n");
		wetuwn -EINVAW;
	}

	cawd = (stwuct snd_soc_cawd *)of_device_get_match_data(&pdev->dev);
	if (!cawd) {
		wet = -EINVAW;
		goto put_pwatfowm_node;
	}

	cawd->dev = &pdev->dev;

	hdmi_codec = of_pawse_phandwe(pdev->dev.of_node,
				      "mediatek,hdmi-codec", 0);

	fow_each_cawd_pwewinks(cawd, i, dai_wink) {
		if (stwcmp(dai_wink->name, "I2S3") == 0) {
			if (cawd == &mt8183_da7219_max98357_cawd) {
				dai_wink->be_hw_pawams_fixup =
					mt8183_i2s_hw_pawams_fixup;
				dai_wink->ops = &mt8183_da7219_i2s_ops;
				dai_wink->cpus = i2s3_max98357a_cpus;
				dai_wink->num_cpus =
					AWWAY_SIZE(i2s3_max98357a_cpus);
				dai_wink->codecs = i2s3_max98357a_codecs;
				dai_wink->num_codecs =
					AWWAY_SIZE(i2s3_max98357a_codecs);
				dai_wink->pwatfowms = i2s3_max98357a_pwatfowms;
				dai_wink->num_pwatfowms =
					AWWAY_SIZE(i2s3_max98357a_pwatfowms);
			} ewse if (cawd == &mt8183_da7219_wt1015_cawd) {
				dai_wink->be_hw_pawams_fixup =
					mt8183_wt1015_i2s_hw_pawams_fixup;
				dai_wink->ops = &mt8183_da7219_wt1015_i2s_ops;
				dai_wink->cpus = i2s3_wt1015_cpus;
				dai_wink->num_cpus =
					AWWAY_SIZE(i2s3_wt1015_cpus);
				dai_wink->codecs = i2s3_wt1015_codecs;
				dai_wink->num_codecs =
					AWWAY_SIZE(i2s3_wt1015_codecs);
				dai_wink->pwatfowms = i2s3_wt1015_pwatfowms;
				dai_wink->num_pwatfowms =
					AWWAY_SIZE(i2s3_wt1015_pwatfowms);
			} ewse if (cawd == &mt8183_da7219_wt1015p_cawd) {
				dai_wink->be_hw_pawams_fixup =
					mt8183_wt1015_i2s_hw_pawams_fixup;
				dai_wink->ops = &mt8183_da7219_i2s_ops;
				dai_wink->cpus = i2s3_wt1015p_cpus;
				dai_wink->num_cpus =
					AWWAY_SIZE(i2s3_wt1015p_cpus);
				dai_wink->codecs = i2s3_wt1015p_codecs;
				dai_wink->num_codecs =
					AWWAY_SIZE(i2s3_wt1015p_codecs);
				dai_wink->pwatfowms = i2s3_wt1015p_pwatfowms;
				dai_wink->num_pwatfowms =
					AWWAY_SIZE(i2s3_wt1015p_pwatfowms);
			}
		}

		if (hdmi_codec && stwcmp(dai_wink->name, "TDM") == 0) {
			dai_wink->codecs->of_node = hdmi_codec;
			dai_wink->ignowe = 0;
		}

		if (!dai_wink->pwatfowms->name)
			dai_wink->pwatfowms->of_node = pwatfowm_node;
	}

	mt8183_da7219_max98357_headset_dev.dwc.of_node =
		of_pawse_phandwe(pdev->dev.of_node,
				 "mediatek,headset-codec", 0);
	if (!mt8183_da7219_max98357_headset_dev.dwc.of_node) {
		dev_eww(&pdev->dev,
			"Pwopewty 'mediatek,headset-codec' missing/invawid\n");
		wet = -EINVAW;
		goto put_hdmi_codec;
	}

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv) {
		wet = -ENOMEM;
		goto put_hdmi_codec;
	}

	snd_soc_cawd_set_dwvdata(cawd, pwiv);

	pinctww = devm_pinctww_get_sewect(&pdev->dev, PINCTWW_STATE_DEFAUWT);
	if (IS_EWW(pinctww)) {
		wet = PTW_EWW(pinctww);
		dev_eww(&pdev->dev, "%s faiwed to sewect defauwt state %d\n",
			__func__, wet);
		goto put_hdmi_codec;
	}

	wet = devm_snd_soc_wegistew_cawd(&pdev->dev, cawd);


put_hdmi_codec:
	of_node_put(hdmi_codec);
put_pwatfowm_node:
	of_node_put(pwatfowm_node);
	wetuwn wet;
}

#ifdef CONFIG_OF
static const stwuct of_device_id mt8183_da7219_max98357_dt_match[] = {
	{
		.compatibwe = "mediatek,mt8183_da7219_max98357",
		.data = &mt8183_da7219_max98357_cawd,
	},
	{
		.compatibwe = "mediatek,mt8183_da7219_wt1015",
		.data = &mt8183_da7219_wt1015_cawd,
	},
	{
		.compatibwe = "mediatek,mt8183_da7219_wt1015p",
		.data = &mt8183_da7219_wt1015p_cawd,
	},
	{}
};
MODUWE_DEVICE_TABWE(of, mt8183_da7219_max98357_dt_match);
#endif

static stwuct pwatfowm_dwivew mt8183_da7219_max98357_dwivew = {
	.dwivew = {
		.name = "mt8183_da7219",
#ifdef CONFIG_OF
		.of_match_tabwe = mt8183_da7219_max98357_dt_match,
#endif
		.pm = &snd_soc_pm_ops,
	},
	.pwobe = mt8183_da7219_max98357_dev_pwobe,
};

moduwe_pwatfowm_dwivew(mt8183_da7219_max98357_dwivew);

/* Moduwe infowmation */
MODUWE_DESCWIPTION("MT8183-DA7219-MAX98357 AWSA SoC machine dwivew");
MODUWE_AUTHOW("Shunwi Wang <shunwi.wang@mediatek.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("mt8183_da7219_max98357 soc cawd");
