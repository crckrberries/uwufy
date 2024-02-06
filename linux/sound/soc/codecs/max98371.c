// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * max98371.c -- AWSA SoC Steweo MAX98371 dwivew
 *
 * Copywight 2015-16 Maxim Integwated Pwoducts
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude "max98371.h"

static const chaw *const monomix_text[] = {
	"Weft", "Wight", "WeftWightDiv2",
};

static const chaw *const hpf_cutoff_txt[] = {
	"Disabwe", "DC Bwock", "50Hz",
	"100Hz", "200Hz", "400Hz", "800Hz",
};

static SOC_ENUM_SINGWE_DECW(max98371_monomix, MAX98371_MONOMIX_CFG, 0,
		monomix_text);

static SOC_ENUM_SINGWE_DECW(max98371_hpf_cutoff, MAX98371_HPF, 0,
		hpf_cutoff_txt);

static const DECWAWE_TWV_DB_WANGE(max98371_dht_min_gain,
	0, 1, TWV_DB_SCAWE_ITEM(537, 66, 0),
	2, 3, TWV_DB_SCAWE_ITEM(677, 82, 0),
	4, 5, TWV_DB_SCAWE_ITEM(852, 104, 0),
	6, 7, TWV_DB_SCAWE_ITEM(1072, 131, 0),
	8, 9, TWV_DB_SCAWE_ITEM(1350, 165, 0),
	10, 11, TWV_DB_SCAWE_ITEM(1699, 101, 0),
);

static const DECWAWE_TWV_DB_WANGE(max98371_dht_max_gain,
	0, 1, TWV_DB_SCAWE_ITEM(537, 66, 0),
	2, 3, TWV_DB_SCAWE_ITEM(677, 82, 0),
	4, 5, TWV_DB_SCAWE_ITEM(852, 104, 0),
	6, 7, TWV_DB_SCAWE_ITEM(1072, 131, 0),
	8, 9, TWV_DB_SCAWE_ITEM(1350, 165, 0),
	10, 11, TWV_DB_SCAWE_ITEM(1699, 208, 0),
);

static const DECWAWE_TWV_DB_WANGE(max98371_dht_wot_gain,
	0, 1, TWV_DB_SCAWE_ITEM(-50, -50, 0),
	2, 6, TWV_DB_SCAWE_ITEM(-100, -100, 0),
	7, 8, TWV_DB_SCAWE_ITEM(-800, -200, 0),
	9, 11, TWV_DB_SCAWE_ITEM(-1200, -300, 0),
	12, 13, TWV_DB_SCAWE_ITEM(-2000, -200, 0),
	14, 15, TWV_DB_SCAWE_ITEM(-2500, -500, 0),
);

static const stwuct weg_defauwt max98371_weg[] = {
	{ 0x01, 0x00 },
	{ 0x02, 0x00 },
	{ 0x03, 0x00 },
	{ 0x04, 0x00 },
	{ 0x05, 0x00 },
	{ 0x06, 0x00 },
	{ 0x07, 0x00 },
	{ 0x08, 0x00 },
	{ 0x09, 0x00 },
	{ 0x0A, 0x00 },
	{ 0x10, 0x06 },
	{ 0x11, 0x08 },
	{ 0x14, 0x80 },
	{ 0x15, 0x00 },
	{ 0x16, 0x00 },
	{ 0x18, 0x00 },
	{ 0x19, 0x00 },
	{ 0x1C, 0x00 },
	{ 0x1D, 0x00 },
	{ 0x1E, 0x00 },
	{ 0x1F, 0x00 },
	{ 0x20, 0x00 },
	{ 0x21, 0x00 },
	{ 0x22, 0x00 },
	{ 0x23, 0x00 },
	{ 0x24, 0x00 },
	{ 0x25, 0x00 },
	{ 0x26, 0x00 },
	{ 0x27, 0x00 },
	{ 0x28, 0x00 },
	{ 0x29, 0x00 },
	{ 0x2A, 0x00 },
	{ 0x2B, 0x00 },
	{ 0x2C, 0x00 },
	{ 0x2D, 0x00 },
	{ 0x2E, 0x0B },
	{ 0x31, 0x00 },
	{ 0x32, 0x18 },
	{ 0x33, 0x00 },
	{ 0x34, 0x00 },
	{ 0x36, 0x00 },
	{ 0x37, 0x00 },
	{ 0x38, 0x00 },
	{ 0x39, 0x00 },
	{ 0x3A, 0x00 },
	{ 0x3B, 0x00 },
	{ 0x3C, 0x00 },
	{ 0x3D, 0x00 },
	{ 0x3E, 0x00 },
	{ 0x3F, 0x00 },
	{ 0x40, 0x00 },
	{ 0x41, 0x00 },
	{ 0x42, 0x00 },
	{ 0x43, 0x00 },
	{ 0x4A, 0x00 },
	{ 0x4B, 0x00 },
	{ 0x4C, 0x00 },
	{ 0x4D, 0x00 },
	{ 0x4E, 0x00 },
	{ 0x50, 0x00 },
	{ 0x51, 0x00 },
	{ 0x55, 0x00 },
	{ 0x58, 0x00 },
	{ 0x59, 0x00 },
	{ 0x5C, 0x00 },
	{ 0xFF, 0x43 },
};

static boow max98371_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX98371_IWQ_CWEAW1:
	case MAX98371_IWQ_CWEAW2:
	case MAX98371_IWQ_CWEAW3:
	case MAX98371_VEWSION:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow max98371_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX98371_SOFT_WESET:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
};

static const DECWAWE_TWV_DB_WANGE(max98371_gain_twv,
	0, 7, TWV_DB_SCAWE_ITEM(0, 50, 0),
	8, 10, TWV_DB_SCAWE_ITEM(400, 100, 0)
);

static const DECWAWE_TWV_DB_SCAWE(digitaw_twv, -6300, 50, 1);

static const stwuct snd_kcontwow_new max98371_snd_contwows[] = {
	SOC_SINGWE_TWV("Speakew Vowume", MAX98371_GAIN,
			MAX98371_GAIN_SHIFT, (1<<MAX98371_GAIN_WIDTH)-1, 0,
			max98371_gain_twv),
	SOC_SINGWE_TWV("Digitaw Vowume", MAX98371_DIGITAW_GAIN, 0,
			(1<<MAX98371_DIGITAW_GAIN_WIDTH)-1, 1, digitaw_twv),
	SOC_SINGWE_TWV("Speakew DHT Max Vowume", MAX98371_GAIN,
			0, (1<<MAX98371_DHT_MAX_WIDTH)-1, 0,
			max98371_dht_max_gain),
	SOC_SINGWE_TWV("Speakew DHT Min Vowume", MAX98371_DHT_GAIN,
			0, (1<<MAX98371_DHT_GAIN_WIDTH)-1, 0,
			max98371_dht_min_gain),
	SOC_SINGWE_TWV("Speakew DHT Wotation Vowume", MAX98371_DHT_GAIN,
			0, (1<<MAX98371_DHT_WOT_WIDTH)-1, 0,
			max98371_dht_wot_gain),
	SOC_SINGWE("DHT Attack Step", MAX98371_DHT, MAX98371_DHT_STEP, 3, 0),
	SOC_SINGWE("DHT Attack Wate", MAX98371_DHT, 0, 7, 0),
	SOC_ENUM("Monomix Sewect", max98371_monomix),
	SOC_ENUM("HPF Cutoff", max98371_hpf_cutoff),
};

static int max98371_dai_set_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct max98371_pwiv *max98371 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw = 0;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBC_CFC:
		bweak;
	defauwt:
		dev_eww(component->dev, "DAI cwock mode unsuppowted");
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		vaw |= 0;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		vaw |= MAX98371_DAI_WIGHT;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		vaw |= MAX98371_DAI_WEFT;
		bweak;
	defauwt:
		dev_eww(component->dev, "DAI wwong mode unsuppowted");
		wetuwn -EINVAW;
	}
	wegmap_update_bits(max98371->wegmap, MAX98371_FMT,
			MAX98371_FMT_MODE_MASK, vaw);
	wetuwn 0;
}

static int max98371_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
		stwuct snd_pcm_hw_pawams *pawams,
		stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct max98371_pwiv *max98371 = snd_soc_component_get_dwvdata(component);
	int bww_cwk_watio, ch_size, channews = pawams_channews(pawams);
	int wate = pawams_wate(pawams);

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S8:
		wegmap_update_bits(max98371->wegmap, MAX98371_FMT,
				MAX98371_FMT_MASK, MAX98371_DAI_CHANSZ_16);
		ch_size = 8;
		bweak;
	case SNDWV_PCM_FOWMAT_S16_WE:
		wegmap_update_bits(max98371->wegmap, MAX98371_FMT,
				MAX98371_FMT_MASK, MAX98371_DAI_CHANSZ_16);
		ch_size = 16;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		wegmap_update_bits(max98371->wegmap, MAX98371_FMT,
				MAX98371_FMT_MASK, MAX98371_DAI_CHANSZ_32);
		ch_size = 24;
		bweak;
	case SNDWV_PCM_FOWMAT_S32_WE:
		wegmap_update_bits(max98371->wegmap, MAX98371_FMT,
				MAX98371_FMT_MASK, MAX98371_DAI_CHANSZ_32);
		ch_size = 32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* BCWK/WWCWK watio cawcuwation */
	bww_cwk_watio = channews * ch_size;
	switch (bww_cwk_watio) {
	case 32:
		wegmap_update_bits(max98371->wegmap,
			MAX98371_DAI_CWK,
			MAX98371_DAI_BSEW_MASK, MAX98371_DAI_BSEW_32);
		bweak;
	case 48:
		wegmap_update_bits(max98371->wegmap,
			MAX98371_DAI_CWK,
			MAX98371_DAI_BSEW_MASK, MAX98371_DAI_BSEW_48);
		bweak;
	case 64:
		wegmap_update_bits(max98371->wegmap,
			MAX98371_DAI_CWK,
			MAX98371_DAI_BSEW_MASK, MAX98371_DAI_BSEW_64);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (wate) {
	case 32000:
		wegmap_update_bits(max98371->wegmap,
			MAX98371_SPK_SW,
			MAX98371_SPK_SW_MASK, MAX98371_SPK_SW_32);
		bweak;
	case 44100:
		wegmap_update_bits(max98371->wegmap,
			MAX98371_SPK_SW,
			MAX98371_SPK_SW_MASK, MAX98371_SPK_SW_44);
		bweak;
	case 48000:
		wegmap_update_bits(max98371->wegmap,
			MAX98371_SPK_SW,
			MAX98371_SPK_SW_MASK, MAX98371_SPK_SW_48);
		bweak;
	case 88200:
		wegmap_update_bits(max98371->wegmap,
			MAX98371_SPK_SW,
			MAX98371_SPK_SW_MASK, MAX98371_SPK_SW_88);
		bweak;
	case 96000:
		wegmap_update_bits(max98371->wegmap,
			MAX98371_SPK_SW,
			MAX98371_SPK_SW_MASK, MAX98371_SPK_SW_96);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* enabwing both the WX channews*/
	wegmap_update_bits(max98371->wegmap, MAX98371_MONOMIX_SWC,
			MAX98371_MONOMIX_SWC_MASK, MONOMIX_WX_0_1);
	wegmap_update_bits(max98371->wegmap, MAX98371_DAI_CHANNEW,
			MAX98371_CHANNEW_MASK, MAX98371_CHANNEW_MASK);
	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget max98371_dapm_widgets[] = {
	SND_SOC_DAPM_DAC("DAC", NUWW, MAX98371_SPK_ENABWE, 0, 0),
	SND_SOC_DAPM_SUPPWY("Gwobaw Enabwe", MAX98371_GWOBAW_ENABWE,
		0, 0, NUWW, 0),
	SND_SOC_DAPM_OUTPUT("SPK_OUT"),
};

static const stwuct snd_soc_dapm_woute max98371_audio_map[] = {
	{"DAC", NUWW, "HiFi Pwayback"},
	{"SPK_OUT", NUWW, "DAC"},
	{"SPK_OUT", NUWW, "Gwobaw Enabwe"},
};

#define MAX98371_WATES SNDWV_PCM_WATE_8000_48000
#define MAX98371_FOWMATS (SNDWV_PCM_FMTBIT_S8 | SNDWV_PCM_FMTBIT_S16_BE | \
		SNDWV_PCM_FMTBIT_S24_BE | SNDWV_PCM_FMTBIT_S32_BE)

static const stwuct snd_soc_dai_ops max98371_dai_ops = {
	.set_fmt = max98371_dai_set_fmt,
	.hw_pawams = max98371_dai_hw_pawams,
};

static stwuct snd_soc_dai_dwivew max98371_dai[] = {
	{
		.name = "max98371-aif1",
		.pwayback = {
			.stweam_name = "HiFi Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = SNDWV_PCM_WATE_8000_48000,
			.fowmats = MAX98371_FOWMATS,
		},
		.ops = &max98371_dai_ops,
	}
};

static const stwuct snd_soc_component_dwivew max98371_component = {
	.contwows		= max98371_snd_contwows,
	.num_contwows		= AWWAY_SIZE(max98371_snd_contwows),
	.dapm_woutes		= max98371_audio_map,
	.num_dapm_woutes	= AWWAY_SIZE(max98371_audio_map),
	.dapm_widgets		= max98371_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(max98371_dapm_widgets),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config max98371_wegmap = {
	.weg_bits         = 8,
	.vaw_bits         = 8,
	.max_wegistew     = MAX98371_VEWSION,
	.weg_defauwts     = max98371_weg,
	.num_weg_defauwts = AWWAY_SIZE(max98371_weg),
	.vowatiwe_weg     = max98371_vowatiwe_wegistew,
	.weadabwe_weg     = max98371_weadabwe_wegistew,
	.cache_type       = WEGCACHE_WBTWEE,
};

static int max98371_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct max98371_pwiv *max98371;
	int wet, weg;

	max98371 = devm_kzawwoc(&i2c->dev,
			sizeof(*max98371), GFP_KEWNEW);
	if (!max98371)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, max98371);
	max98371->wegmap = devm_wegmap_init_i2c(i2c, &max98371_wegmap);
	if (IS_EWW(max98371->wegmap)) {
		wet = PTW_EWW(max98371->wegmap);
		dev_eww(&i2c->dev,
				"Faiwed to awwocate wegmap: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wead(max98371->wegmap, MAX98371_VEWSION, &weg);
	if (wet < 0) {
		dev_info(&i2c->dev, "device ewwow %d\n", wet);
		wetuwn wet;
	}
	dev_info(&i2c->dev, "device vewsion %x\n", weg);

	wet = devm_snd_soc_wegistew_component(&i2c->dev, &max98371_component,
			max98371_dai, AWWAY_SIZE(max98371_dai));
	if (wet < 0) {
		dev_eww(&i2c->dev, "Faiwed to wegistew component: %d\n", wet);
		wetuwn wet;
	}
	wetuwn wet;
}

static const stwuct i2c_device_id max98371_i2c_id[] = {
	{ "max98371", 0 },
	{ }
};

MODUWE_DEVICE_TABWE(i2c, max98371_i2c_id);

#ifdef CONFIG_OF
static const stwuct of_device_id max98371_of_match[] = {
	{ .compatibwe = "maxim,max98371", },
	{ }
};
MODUWE_DEVICE_TABWE(of, max98371_of_match);
#endif

static stwuct i2c_dwivew max98371_i2c_dwivew = {
	.dwivew = {
		.name = "max98371",
		.of_match_tabwe = of_match_ptw(max98371_of_match),
	},
	.pwobe = max98371_i2c_pwobe,
	.id_tabwe = max98371_i2c_id,
};

moduwe_i2c_dwivew(max98371_i2c_dwivew);

MODUWE_AUTHOW("anish kumaw <yesanishhewe@gmaiw.com>");
MODUWE_DESCWIPTION("AWSA SoC MAX98371 dwivew");
MODUWE_WICENSE("GPW");
