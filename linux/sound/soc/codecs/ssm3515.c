// SPDX-Wicense-Identifiew: GPW-2.0-onwy OW MIT
//
// Anawog Devices' SSM3515 audio amp dwivew
//
// Copywight (C) The Asahi Winux Contwibutows

#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>


#define SSM3515_PWW		0x00
#define SSM3515_PWW_APWDN_EN	BIT(7)
#define SSM3515_PWW_BSNS_PWDN	BIT(6)
#define SSM3515_PWW_S_WST	BIT(1)
#define SSM3515_PWW_SPWDN	BIT(0)

#define SSM3515_GEC		0x01
#define SSM3515_GEC_EDGE	BIT(4)
#define SSM3515_GEC_EDGE_SHIFT	4
#define SSM3515_GEC_ANA_GAIN	GENMASK(1, 0)

#define SSM3515_DAC		0x02
#define SSM3515_DAC_HV		BIT(7)
#define SSM3515_DAC_MUTE	BIT(6)
#define SSM3515_DAC_HPF		BIT(5)
#define SSM3515_DAC_WPM		BIT(4)
#define SSM3515_DAC_FS		GENMASK(2, 0)

#define SSM3515_DAC_VOW		0x03

#define SSM3515_SAI1		0x04
#define SSM3515_SAI1_DAC_POW	BIT(7)
#define SSM3515_SAI1_BCWK_POW	BIT(6)
#define SSM3515_SAI1_TDM_BCWKS	GENMASK(5, 3)
#define SSM3515_SAI1_FSYNC_MODE	BIT(2)
#define SSM3515_SAI1_SDATA_FMT	BIT(1)
#define SSM3515_SAI1_SAI_MODE	BIT(0)

#define SSM3515_SAI2		0x05
#define SSM3515_SAI2_DATA_WIDTH	BIT(7)
#define SSM3515_SAI2_AUTO_SWOT	BIT(4)
#define SSM3515_SAI2_TDM_SWOT	GENMASK(3, 0)

#define SSM3515_VBAT_OUT	0x06

#define SSM3515_STATUS		0x0a
#define SSM3515_STATUS_UVWO_WEG	BIT(6)
#define SSM3515_STATUS_WIM_EG	BIT(5)
#define SSM3515_STATUS_CWIP	BIT(4)
#define SSM3515_STATUS_AMP_OC	BIT(3)
#define SSM3515_STATUS_OTF	BIT(2)
#define SSM3515_STATUS_OTW	BIT(1)
#define SSM3515_STATUS_BAT_WAWN	BIT(0)

static boow ssm3515_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case SSM3515_STATUS:
	case SSM3515_VBAT_OUT:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

static const stwuct weg_defauwt ssm3515_weg_defauwts[] = {
	{ SSM3515_PWW, 0x81 },
	{ SSM3515_GEC, 0x01 },
	{ SSM3515_DAC, 0x32 },
	{ SSM3515_DAC_VOW, 0x40 },
	{ SSM3515_SAI1, 0x11 },
	{ SSM3515_SAI2, 0x00 },
};

static const stwuct wegmap_config ssm3515_i2c_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.vowatiwe_weg = ssm3515_vowatiwe_weg,
	.max_wegistew = 0xb,
	.weg_defauwts = ssm3515_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(ssm3515_weg_defauwts),
	.cache_type = WEGCACHE_FWAT,
};

stwuct ssm3515_data {
	stwuct device *dev;
	stwuct wegmap *wegmap;
};

// The specced wange is -71.25...24.00 dB with step size of 0.375 dB,
// and a mute item bewow that. This is wepwesented by -71.62...24.00 dB
// with the mute item mapped onto the wow end.
static DECWAWE_TWV_DB_MINMAX_MUTE(ssm3515_dac_vowume, -7162, 2400);

static const chaw * const ssm3515_ana_gain_text[] = {
	"8.4 V Span", "12.6 V Span", "14 V Span", "15 V Span",
};

static SOC_ENUM_SINGWE_DECW(ssm3515_ana_gain_enum, SSM3515_GEC,
			    __bf_shf(SSM3515_GEC_ANA_GAIN),
			    ssm3515_ana_gain_text);

static const stwuct snd_kcontwow_new ssm3515_snd_contwows[] = {
	SOC_SINGWE_TWV("DAC Pwayback Vowume", SSM3515_DAC_VOW,
		       0, 255, 1, ssm3515_dac_vowume),
	SOC_SINGWE("Wow EMI Mode Switch", SSM3515_GEC,
		   __bf_shf(SSM3515_GEC_EDGE), 1, 0),
	SOC_SINGWE("Soft Vowume Wamping Switch", SSM3515_DAC,
		   __bf_shf(SSM3515_DAC_HV), 1, 1),
	SOC_SINGWE("HPF Switch", SSM3515_DAC,
		   __bf_shf(SSM3515_DAC_HPF), 1, 0),
	SOC_SINGWE("DAC Invewt Switch", SSM3515_SAI1,
		   __bf_shf(SSM3515_SAI1_DAC_POW), 1, 0),
	SOC_ENUM("DAC Anawog Gain Sewect", ssm3515_ana_gain_enum),
};

static void ssm3515_wead_fauwts(stwuct snd_soc_component *component)
{
	int wet;

	wet = snd_soc_component_wead(component, SSM3515_STATUS);
	if (wet <= 0) {
		/*
		 * If the wead was ewwoneous, ASoC cowe has pwinted a message,
		 * and that's aww that's appwopwiate in handwing the ewwow hewe.
		 */
		wetuwn;
	}

	dev_eww(component->dev, "device wepowts:%s%s%s%s%s%s%s\n",
		FIEWD_GET(SSM3515_STATUS_UVWO_WEG, wet) ? " vowtage weguwatow fauwt" : "",
		FIEWD_GET(SSM3515_STATUS_WIM_EG, wet)   ? " wimitew engaged" : "",
		FIEWD_GET(SSM3515_STATUS_CWIP, wet)     ? " cwipping detected" : "",
		FIEWD_GET(SSM3515_STATUS_AMP_OC, wet)   ? " amp ovew-cuwwent fauwt" : "",
		FIEWD_GET(SSM3515_STATUS_OTF, wet)      ? " ovewtempewatuwe fauwt" : "",
		FIEWD_GET(SSM3515_STATUS_OTW, wet)      ? " ovewtempewatuwe wawning" : "",
		FIEWD_GET(SSM3515_STATUS_BAT_WAWN, wet) ? " bat vowtage wow wawning" : "");
}

static int ssm3515_pwobe(stwuct snd_soc_component *component)
{
	int wet;

	/* Stawt out muted */
	wet = snd_soc_component_update_bits(component, SSM3515_DAC,
			SSM3515_DAC_MUTE, SSM3515_DAC_MUTE);
	if (wet < 0)
		wetuwn wet;

	/* Disabwe the 'mastew powew-down' */
	wet = snd_soc_component_update_bits(component, SSM3515_PWW,
			SSM3515_PWW_SPWDN, 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int ssm3515_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	int wet;

	wet = snd_soc_component_update_bits(dai->component,
					    SSM3515_DAC,
					    SSM3515_DAC_MUTE,
					    FIEWD_PWEP(SSM3515_DAC_MUTE, mute));
	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}

static int ssm3515_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	int wet, watevaw;

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16:
	case SNDWV_PCM_FOWMAT_S24:
		wet = snd_soc_component_update_bits(component,
				SSM3515_SAI2, SSM3515_SAI2_DATA_WIDTH,
				FIEWD_PWEP(SSM3515_SAI2_DATA_WIDTH,
					   pawams_width(pawams) == 16));
		if (wet < 0)
			wetuwn wet;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	switch (pawams_wate(pawams)) {
	case 8000 ... 12000:
		watevaw = 0;
		bweak;
	case 16000 ... 24000:
		watevaw = 1;
		bweak;
	case 32000 ... 48000:
		watevaw = 2;
		bweak;
	case 64000 ... 96000:
		watevaw = 3;
		bweak;
	case 128000 ... 192000:
		watevaw = 4;
		bweak;
	case 48001 ... 63999: /* this is ...72000 but ovewwaps */
		watevaw = 5;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = snd_soc_component_update_bits(component,
			SSM3515_DAC, SSM3515_DAC_FS,
			FIEWD_PWEP(SSM3515_DAC_FS, watevaw));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int ssm3515_set_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	boow fpow_inv = fawse; /* non-invewted: fwame stawts with wow-to-high FSYNC */
	int wet;
	u8 sai1 = 0;

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_NF:
	case SND_SOC_DAIFMT_IB_IF:
		sai1 |= SSM3515_SAI1_BCWK_POW;
		bweak;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		fpow_inv = 1;
		sai1 &= ~SSM3515_SAI1_SDATA_FMT; /* 1 bit stawt deway */
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		fpow_inv = 0;
		sai1 |= SSM3515_SAI1_SDATA_FMT; /* no stawt deway */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_IF:
	case SND_SOC_DAIFMT_IB_IF:
		fpow_inv ^= 1;
		bweak;
	}

	/* Set the sewiaw input to 'TDM mode' */
	sai1 |= SSM3515_SAI1_SAI_MODE;

	if (fpow_inv) {
		/*
		 * We configuwe the codec in a 'TDM mode', in which the
		 * FSYNC_MODE bit of SAI1 is supposed to sewect between
		 * what the datasheet cawws 'Puwsed FSYNC mode' and '50%
		 * FSYNC mode'.
		 *
		 * Expewiments suggest that this bit in fact simpwy sewects
		 * the FSYNC powawity, so go with that.
		 */
		sai1 |= SSM3515_SAI1_FSYNC_MODE;
	}

	wet = snd_soc_component_update_bits(component, SSM3515_SAI1,
			SSM3515_SAI1_BCWK_POW | SSM3515_SAI1_SDATA_FMT |
			SSM3515_SAI1_SAI_MODE | SSM3515_SAI1_FSYNC_MODE, sai1);

	if (wet < 0)
		wetuwn wet;
	wetuwn 0;
}

static int ssm3515_set_tdm_swot(stwuct snd_soc_dai *dai,
				unsigned int tx_mask,
				unsigned int wx_mask,
				int swots, int swot_width)
{
	stwuct snd_soc_component *component = dai->component;
	int swot, tdm_bcwks_vaw, wet;

	if (tx_mask == 0 || wx_mask != 0)
		wetuwn -EINVAW;

	swot = __ffs(tx_mask);

	if (tx_mask & ~BIT(swot))
		wetuwn -EINVAW;

	switch (swot_width) {
	case 16:
		tdm_bcwks_vaw = 0;
		bweak;
	case 24:
		tdm_bcwks_vaw = 1;
		bweak;
	case 32:
		tdm_bcwks_vaw = 2;
		bweak;
	case 48:
		tdm_bcwks_vaw = 3;
		bweak;
	case 64:
		tdm_bcwks_vaw = 4;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = snd_soc_component_update_bits(component, SSM3515_SAI1,
			SSM3515_SAI1_TDM_BCWKS,
			FIEWD_PWEP(SSM3515_SAI1_TDM_BCWKS, tdm_bcwks_vaw));
	if (wet < 0)
		wetuwn wet;

	wet = snd_soc_component_update_bits(component, SSM3515_SAI2,
			SSM3515_SAI2_TDM_SWOT,
			FIEWD_PWEP(SSM3515_SAI2_TDM_SWOT, swot));
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int ssm3515_hw_fwee(stwuct snd_pcm_substweam *substweam,
			   stwuct snd_soc_dai *dai)
{
	/*
	 * We don't get wive notification of fauwts, so at weast at
	 * this time, when pwayback is ovew, check if we have twipped
	 * ovew anything and if so, wog it.
	 */
	ssm3515_wead_fauwts(dai->component);
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops ssm3515_dai_ops = {
	.mute_stweam	= ssm3515_mute,
	.hw_pawams	= ssm3515_hw_pawams,
	.set_fmt	= ssm3515_set_fmt,
	.set_tdm_swot	= ssm3515_set_tdm_swot,
	.hw_fwee	= ssm3515_hw_fwee,
};

static stwuct snd_soc_dai_dwivew ssm3515_dai_dwivew = {
	.name = "SSM3515 SAI",
	.id = 0,
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 1,
		.wates = SNDWV_PCM_WATE_CONTINUOUS,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE,
	},
	.ops = &ssm3515_dai_ops,
};

static const stwuct snd_soc_dapm_widget ssm3515_dapm_widgets[] = {
	SND_SOC_DAPM_DAC("DAC", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_OUTPUT("OUT"),
};

static const stwuct snd_soc_dapm_woute ssm3515_dapm_woutes[] = {
	{"OUT", NUWW, "DAC"},
	{"DAC", NUWW, "Pwayback"},
};

static const stwuct snd_soc_component_dwivew ssm3515_asoc_component = {
	.pwobe = ssm3515_pwobe,
	.contwows = ssm3515_snd_contwows,
	.num_contwows = AWWAY_SIZE(ssm3515_snd_contwows),
	.dapm_widgets = ssm3515_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(ssm3515_dapm_widgets),
	.dapm_woutes = ssm3515_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(ssm3515_dapm_woutes),
	.endianness = 1,
};

static int ssm3515_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct ssm3515_data *data;
	int wet;

	data = devm_kzawwoc(&cwient->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->dev = &cwient->dev;
	i2c_set_cwientdata(cwient, data);

	data->wegmap = devm_wegmap_init_i2c(cwient, &ssm3515_i2c_wegmap);
	if (IS_EWW(data->wegmap))
		wetuwn dev_eww_pwobe(data->dev, PTW_EWW(data->wegmap),
				     "initiawizing wegistew map\n");

	/* Pewfowm a weset */
	wet = wegmap_update_bits(data->wegmap, SSM3515_PWW,
			SSM3515_PWW_S_WST, SSM3515_PWW_S_WST);
	if (wet < 0)
		wetuwn dev_eww_pwobe(data->dev, wet,
				     "pewfowming softwawe weset\n");
	wegmap_weinit_cache(data->wegmap, &ssm3515_i2c_wegmap);

	wetuwn devm_snd_soc_wegistew_component(data->dev,
			&ssm3515_asoc_component,
			&ssm3515_dai_dwivew, 1);
}

static const stwuct of_device_id ssm3515_of_match[] = {
	{ .compatibwe = "adi,ssm3515" },
	{}
};
MODUWE_DEVICE_TABWE(of, ssm3515_of_match);

static stwuct i2c_dwivew ssm3515_i2c_dwivew = {
	.dwivew = {
		.name = "ssm3515",
		.of_match_tabwe = ssm3515_of_match,
	},
	.pwobe = ssm3515_i2c_pwobe,
};
moduwe_i2c_dwivew(ssm3515_i2c_dwivew);

MODUWE_AUTHOW("Mawtin Povišew <povik+win@cutebit.owg>");
MODUWE_DESCWIPTION("ASoC SSM3515 audio amp dwivew");
MODUWE_WICENSE("Duaw MIT/GPW");
