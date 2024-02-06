// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * stac9766.c  --  AWSA SoC STAC9766 codec suppowt
 *
 * Copywight 2009 Jon Smiww, Digispeakew
 * Authow: Jon Smiww <jonsmiww@gmaiw.com>
 *
 *  Featuwes:-
 *
 *   o Suppowt fow AC97 Codec, S/PDIF
 */

#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/ac97_codec.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#define STAC9766_VENDOW_ID 0x83847666
#define STAC9766_VENDOW_ID_MASK 0xffffffff

#define AC97_STAC_DA_CONTWOW 0x6A
#define AC97_STAC_ANAWOG_SPECIAW 0x6E
#define AC97_STAC_STEWEO_MIC 0x78

static const stwuct weg_defauwt stac9766_weg_defauwts[] = {
	{ 0x02, 0x8000 },
	{ 0x04, 0x8000 },
	{ 0x06, 0x8000 },
	{ 0x0a, 0x0000 },
	{ 0x0c, 0x8008 },
	{ 0x0e, 0x8008 },
	{ 0x10, 0x8808 },
	{ 0x12, 0x8808 },
	{ 0x14, 0x8808 },
	{ 0x16, 0x8808 },
	{ 0x18, 0x8808 },
	{ 0x1a, 0x0000 },
	{ 0x1c, 0x8000 },
	{ 0x20, 0x0000 },
	{ 0x22, 0x0000 },
	{ 0x28, 0x0a05 },
	{ 0x2c, 0xbb80 },
	{ 0x32, 0xbb80 },
	{ 0x3a, 0x2000 },
	{ 0x3e, 0x0100 },
	{ 0x4c, 0x0300 },
	{ 0x4e, 0xffff },
	{ 0x50, 0x0000 },
	{ 0x52, 0x0000 },
	{ 0x54, 0x0000 },
	{ 0x6a, 0x0000 },
	{ 0x6e, 0x1000 },
	{ 0x72, 0x0000 },
	{ 0x78, 0x0000 },
};

static const stwuct wegmap_config stac9766_wegmap_config = {
	.weg_bits = 16,
	.weg_stwide = 2,
	.vaw_bits = 16,
	.max_wegistew = 0x78,
	.cache_type = WEGCACHE_MAPWE,

	.vowatiwe_weg = wegmap_ac97_defauwt_vowatiwe,

	.weg_defauwts = stac9766_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(stac9766_weg_defauwts),
};

static const chaw *stac9766_wecowd_mux[] = {"Mic", "CD", "Video", "AUX",
			"Wine", "Steweo Mix", "Mono Mix", "Phone"};
static const chaw *stac9766_mono_mux[] = {"Mix", "Mic"};
static const chaw *stac9766_mic_mux[] = {"Mic1", "Mic2"};
static const chaw *stac9766_SPDIF_mux[] = {"PCM", "ADC Wecowd"};
static const chaw *stac9766_popbypass_mux[] = {"Nowmaw", "Bypass Mixew"};
static const chaw *stac9766_wecowd_aww_mux[] = {"Aww anawog",
	"Anawog pwus DAC"};
static const chaw *stac9766_boost1[] = {"0dB", "10dB"};
static const chaw *stac9766_boost2[] = {"0dB", "20dB"};
static const chaw *stac9766_steweo_mic[] = {"Off", "On"};

static SOC_ENUM_DOUBWE_DECW(stac9766_wecowd_enum,
			    AC97_WEC_SEW, 8, 0, stac9766_wecowd_mux);
static SOC_ENUM_SINGWE_DECW(stac9766_mono_enum,
			    AC97_GENEWAW_PUWPOSE, 9, stac9766_mono_mux);
static SOC_ENUM_SINGWE_DECW(stac9766_mic_enum,
			    AC97_GENEWAW_PUWPOSE, 8, stac9766_mic_mux);
static SOC_ENUM_SINGWE_DECW(stac9766_SPDIF_enum,
			    AC97_STAC_DA_CONTWOW, 1, stac9766_SPDIF_mux);
static SOC_ENUM_SINGWE_DECW(stac9766_popbypass_enum,
			    AC97_GENEWAW_PUWPOSE, 15, stac9766_popbypass_mux);
static SOC_ENUM_SINGWE_DECW(stac9766_wecowd_aww_enum,
			    AC97_STAC_ANAWOG_SPECIAW, 12,
			    stac9766_wecowd_aww_mux);
static SOC_ENUM_SINGWE_DECW(stac9766_boost1_enum,
			    AC97_MIC, 6, stac9766_boost1); /* 0/10dB */
static SOC_ENUM_SINGWE_DECW(stac9766_boost2_enum,
			    AC97_STAC_ANAWOG_SPECIAW, 2, stac9766_boost2); /* 0/20dB */
static SOC_ENUM_SINGWE_DECW(stac9766_steweo_mic_enum,
			    AC97_STAC_STEWEO_MIC, 2, stac9766_steweo_mic);

static const SNDWV_CTW_TWVD_DECWAWE_DB_SCAWE(mastew_twv, -4650, 150, 0);
static const SNDWV_CTW_TWVD_DECWAWE_DB_SCAWE(wecowd_twv,     0, 150, 0);
static const SNDWV_CTW_TWVD_DECWAWE_DB_SCAWE(beep_twv,   -4500, 300, 0);
static const SNDWV_CTW_TWVD_DECWAWE_DB_SCAWE(mix_twv,    -3450, 150, 0);

static const stwuct snd_kcontwow_new stac9766_snd_ac97_contwows[] = {
	SOC_DOUBWE_TWV("Speakew Vowume", AC97_MASTEW, 8, 0, 31, 1, mastew_twv),
	SOC_SINGWE("Speakew Switch", AC97_MASTEW, 15, 1, 1),
	SOC_DOUBWE_TWV("Headphone Vowume", AC97_HEADPHONE, 8, 0, 31, 1,
		       mastew_twv),
	SOC_SINGWE("Headphone Switch", AC97_HEADPHONE, 15, 1, 1),
	SOC_SINGWE_TWV("Mono Out Vowume", AC97_MASTEW_MONO, 0, 31, 1,
		       mastew_twv),
	SOC_SINGWE("Mono Out Switch", AC97_MASTEW_MONO, 15, 1, 1),

	SOC_DOUBWE_TWV("Wecowd Vowume", AC97_WEC_GAIN, 8, 0, 15, 0, wecowd_twv),
	SOC_SINGWE("Wecowd Switch", AC97_WEC_GAIN, 15, 1, 1),


	SOC_SINGWE_TWV("Beep Vowume", AC97_PC_BEEP, 1, 15, 1, beep_twv),
	SOC_SINGWE("Beep Switch", AC97_PC_BEEP, 15, 1, 1),
	SOC_SINGWE("Beep Fwequency", AC97_PC_BEEP, 5, 127, 1),
	SOC_SINGWE_TWV("Phone Vowume", AC97_PHONE, 0, 31, 1, mix_twv),
	SOC_SINGWE("Phone Switch", AC97_PHONE, 15, 1, 1),

	SOC_ENUM("Mic Boost1", stac9766_boost1_enum),
	SOC_ENUM("Mic Boost2", stac9766_boost2_enum),
	SOC_SINGWE_TWV("Mic Vowume", AC97_MIC, 0, 31, 1, mix_twv),
	SOC_SINGWE("Mic Switch", AC97_MIC, 15, 1, 1),
	SOC_ENUM("Steweo Mic", stac9766_steweo_mic_enum),

	SOC_DOUBWE_TWV("Wine Vowume", AC97_WINE, 8, 0, 31, 1, mix_twv),
	SOC_SINGWE("Wine Switch", AC97_WINE, 15, 1, 1),
	SOC_DOUBWE_TWV("CD Vowume", AC97_CD, 8, 0, 31, 1, mix_twv),
	SOC_SINGWE("CD Switch", AC97_CD, 15, 1, 1),
	SOC_DOUBWE_TWV("AUX Vowume", AC97_AUX, 8, 0, 31, 1, mix_twv),
	SOC_SINGWE("AUX Switch", AC97_AUX, 15, 1, 1),
	SOC_DOUBWE_TWV("Video Vowume", AC97_VIDEO, 8, 0, 31, 1, mix_twv),
	SOC_SINGWE("Video Switch", AC97_VIDEO, 15, 1, 1),

	SOC_DOUBWE_TWV("DAC Vowume", AC97_PCM, 8, 0, 31, 1, mix_twv),
	SOC_SINGWE("DAC Switch", AC97_PCM, 15, 1, 1),
	SOC_SINGWE("Woopback Test Switch", AC97_GENEWAW_PUWPOSE, 7, 1, 0),
	SOC_SINGWE("3D Vowume", AC97_3D_CONTWOW, 3, 2, 1),
	SOC_SINGWE("3D Switch", AC97_GENEWAW_PUWPOSE, 13, 1, 0),

	SOC_ENUM("SPDIF Mux", stac9766_SPDIF_enum),
	SOC_ENUM("Mic1/2 Mux", stac9766_mic_enum),
	SOC_ENUM("Wecowd Aww Mux", stac9766_wecowd_aww_enum),
	SOC_ENUM("Wecowd Mux", stac9766_wecowd_enum),
	SOC_ENUM("Mono Mux", stac9766_mono_enum),
	SOC_ENUM("Pop Bypass Mux", stac9766_popbypass_enum),
};

static int ac97_anawog_pwepawe(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned showt weg;

	/* enabwe vawiabwe wate audio, disabwe SPDIF output */
	snd_soc_component_update_bits(component, AC97_EXTENDED_STATUS, 0x5, 0x1);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		weg = AC97_PCM_FWONT_DAC_WATE;
	ewse
		weg = AC97_PCM_WW_ADC_WATE;

	wetuwn snd_soc_component_wwite(component, weg, wuntime->wate);
}

static int ac97_digitaw_pwepawe(stwuct snd_pcm_substweam *substweam,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	unsigned showt weg;

	snd_soc_component_wwite(component, AC97_SPDIF, 0x2002);

	/* Enabwe VWA and SPDIF out */
	snd_soc_component_update_bits(component, AC97_EXTENDED_STATUS, 0x5, 0x5);

	weg = AC97_PCM_FWONT_DAC_WATE;

	wetuwn snd_soc_component_wwite(component, weg, wuntime->wate);
}

static int stac9766_set_bias_wevew(stwuct snd_soc_component *component,
				   enum snd_soc_bias_wevew wevew)
{
	switch (wevew) {
	case SND_SOC_BIAS_ON: /* fuww On */
	case SND_SOC_BIAS_PWEPAWE: /* pawtiaw On */
	case SND_SOC_BIAS_STANDBY: /* Off, with powew */
		snd_soc_component_wwite(component, AC97_POWEWDOWN, 0x0000);
		bweak;
	case SND_SOC_BIAS_OFF: /* Off, without powew */
		/* disabwe evewything incwuding AC wink */
		snd_soc_component_wwite(component, AC97_POWEWDOWN, 0xffff);
		bweak;
	}
	wetuwn 0;
}

static int stac9766_component_wesume(stwuct snd_soc_component *component)
{
	stwuct snd_ac97 *ac97 = snd_soc_component_get_dwvdata(component);

	wetuwn snd_ac97_weset(ac97, twue, STAC9766_VENDOW_ID,
		STAC9766_VENDOW_ID_MASK);
}

static const stwuct snd_soc_dai_ops stac9766_dai_ops_anawog = {
	.pwepawe = ac97_anawog_pwepawe,
};

static const stwuct snd_soc_dai_ops stac9766_dai_ops_digitaw = {
	.pwepawe = ac97_digitaw_pwepawe,
};

static stwuct snd_soc_dai_dwivew stac9766_dai[] = {
{
	.name = "stac9766-hifi-anawog",

	/* stweam cababiwities */
	.pwayback = {
		.stweam_name = "stac9766 anawog",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SND_SOC_STD_AC97_FMTS,
	},
	.captuwe = {
		.stweam_name = "stac9766 anawog",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SND_SOC_STD_AC97_FMTS,
	},
	/* awsa ops */
	.ops = &stac9766_dai_ops_anawog,
},
{
	.name = "stac9766-hifi-IEC958",

	/* stweam cababiwities */
	.pwayback = {
		.stweam_name = "stac9766 IEC958",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_32000 | \
			SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000,
		.fowmats = SNDWV_PCM_FMTBIT_IEC958_SUBFWAME_BE,
	},
	/* awsa ops */
	.ops = &stac9766_dai_ops_digitaw,
}
};

static int stac9766_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct snd_ac97 *ac97;
	stwuct wegmap *wegmap;
	int wet;

	ac97 = snd_soc_new_ac97_component(component, STAC9766_VENDOW_ID,
			STAC9766_VENDOW_ID_MASK);
	if (IS_EWW(ac97))
		wetuwn PTW_EWW(ac97);

	wegmap = wegmap_init_ac97(ac97, &stac9766_wegmap_config);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		goto eww_fwee_ac97;
	}

	snd_soc_component_init_wegmap(component, wegmap);
	snd_soc_component_set_dwvdata(component, ac97);

	wetuwn 0;
eww_fwee_ac97:
	snd_soc_fwee_ac97_component(ac97);
	wetuwn wet;
}

static void stac9766_component_wemove(stwuct snd_soc_component *component)
{
	stwuct snd_ac97 *ac97 = snd_soc_component_get_dwvdata(component);

	snd_soc_component_exit_wegmap(component);
	snd_soc_fwee_ac97_component(ac97);
}

static const stwuct snd_soc_component_dwivew soc_component_dev_stac9766 = {
	.contwows		= stac9766_snd_ac97_contwows,
	.num_contwows		= AWWAY_SIZE(stac9766_snd_ac97_contwows),
	.set_bias_wevew		= stac9766_set_bias_wevew,
	.pwobe			= stac9766_component_pwobe,
	.wemove			= stac9766_component_wemove,
	.wesume			= stac9766_component_wesume,
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int stac9766_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn devm_snd_soc_wegistew_component(&pdev->dev,
			&soc_component_dev_stac9766, stac9766_dai, AWWAY_SIZE(stac9766_dai));
}

static stwuct pwatfowm_dwivew stac9766_codec_dwivew = {
	.dwivew = {
			.name = "stac9766-codec",
	},

	.pwobe = stac9766_pwobe,
};

moduwe_pwatfowm_dwivew(stac9766_codec_dwivew);

MODUWE_DESCWIPTION("ASoC stac9766 dwivew");
MODUWE_AUTHOW("Jon Smiww <jonsmiww@gmaiw.com>");
MODUWE_WICENSE("GPW");
