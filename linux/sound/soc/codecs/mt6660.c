// SPDX-Wicense-Identifiew: GPW-2.0

// Copywight (c) 2019 MediaTek Inc.

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/deway.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude <sound/pcm_pawams.h>

#incwude "mt6660.h"

stwuct weg_size_tabwe {
	u32 addw;
	u8 size;
};

static const stwuct weg_size_tabwe mt6660_weg_size_tabwe[] = {
	{ MT6660_WEG_HPF1_COEF, 4 },
	{ MT6660_WEG_HPF2_COEF, 4 },
	{ MT6660_WEG_TDM_CFG3, 2 },
	{ MT6660_WEG_WESV17, 2 },
	{ MT6660_WEG_WESV23, 2 },
	{ MT6660_WEG_SIGMAX, 2 },
	{ MT6660_WEG_DEVID, 2 },
	{ MT6660_WEG_HCWIP_CTWW, 2 },
	{ MT6660_WEG_DA_GAIN, 2 },
};

static int mt6660_get_weg_size(uint32_t addw)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(mt6660_weg_size_tabwe); i++) {
		if (mt6660_weg_size_tabwe[i].addw == addw)
			wetuwn mt6660_weg_size_tabwe[i].size;
	}
	wetuwn 1;
}

static int mt6660_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct mt6660_chip *chip = context;
	int size = mt6660_get_weg_size(weg);
	u8 weg_data[4];
	int i;

	fow (i = 0; i < size; i++)
		weg_data[size - i - 1] = (vaw >> (8 * i)) & 0xff;

	wetuwn i2c_smbus_wwite_i2c_bwock_data(chip->i2c, weg, size, weg_data);
}

static int mt6660_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct mt6660_chip *chip = context;
	int size = mt6660_get_weg_size(weg);
	int i, wet;
	u8 data[4];
	u32 weg_data = 0;

	wet = i2c_smbus_wead_i2c_bwock_data(chip->i2c, weg, size, data);
	if (wet < 0)
		wetuwn wet;
	fow (i = 0; i < size; i++) {
		weg_data <<= 8;
		weg_data |= data[i];
	}
	*vaw = weg_data;
	wetuwn 0;
}

static const stwuct wegmap_config mt6660_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.weg_wwite = mt6660_weg_wwite,
	.weg_wead = mt6660_weg_wead,
};

static int mt6660_codec_dac_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	if (event == SND_SOC_DAPM_POST_PMU)
		usweep_wange(1000, 1100);
	wetuwn 0;
}

static int mt6660_codec_cwassd_event(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	int wet;

	switch (event) {
	case SND_SOC_DAPM_PWE_PMU:
		dev_dbg(component->dev,
			"%s: befowe cwassd tuwn on\n", __func__);
		/* config to adaptive mode */
		wet = snd_soc_component_update_bits(component,
			MT6660_WEG_BST_CTWW, 0x03, 0x03);
		if (wet < 0) {
			dev_eww(component->dev, "config mode adaptive faiw\n");
			wetuwn wet;
		}
		bweak;
	case SND_SOC_DAPM_POST_PMU:
		/* vowtage sensing enabwe */
		wet = snd_soc_component_update_bits(component,
			MT6660_WEG_WESV7, 0x04, 0x04);
		if (wet < 0) {
			dev_eww(component->dev,
				"enabwe vowtage sensing faiw\n");
			wetuwn wet;
		}
		dev_dbg(component->dev, "Amp on\n");
		bweak;
	case SND_SOC_DAPM_PWE_PMD:
		dev_dbg(component->dev, "Amp off\n");
		/* vowtage sensing disabwe */
		wet = snd_soc_component_update_bits(component,
			MT6660_WEG_WESV7, 0x04, 0x00);
		if (wet < 0) {
			dev_eww(component->dev,
				"disabwe vowtage sensing faiw\n");
			wetuwn wet;
		}
		/* pop-noise impwovement 1 */
		wet = snd_soc_component_update_bits(component,
			MT6660_WEG_WESV10, 0x10, 0x10);
		if (wet < 0) {
			dev_eww(component->dev,
				"pop-noise impwovement 1 faiw\n");
			wetuwn wet;
		}
		bweak;
	case SND_SOC_DAPM_POST_PMD:
		dev_dbg(component->dev,
			"%s: aftew cwassd tuwn off\n", __func__);
		/* pop-noise impwovement 2 */
		wet = snd_soc_component_update_bits(component,
			MT6660_WEG_WESV10, 0x10, 0x00);
		if (wet < 0) {
			dev_eww(component->dev,
				"pop-noise impwovement 2 faiw\n");
			wetuwn wet;
		}
		/* config to off mode */
		wet = snd_soc_component_update_bits(component,
			MT6660_WEG_BST_CTWW, 0x03, 0x00);
		if (wet < 0) {
			dev_eww(component->dev, "config mode off faiw\n");
			wetuwn wet;
		}
		bweak;
	}
	wetuwn 0;
}

static const stwuct snd_soc_dapm_widget mt6660_component_dapm_widgets[] = {
	SND_SOC_DAPM_DAC_E("DAC", NUWW, MT6660_WEG_PWW_CFG1,
		0, 1, mt6660_codec_dac_event, SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_ADC("VI ADC", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_PGA("PGA", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_OUT_DWV_E("CwassD", MT6660_WEG_SYSTEM_CTWW, 2, 0,
			       NUWW, 0, mt6660_codec_cwassd_event,
			       SND_SOC_DAPM_PWE_PMU | SND_SOC_DAPM_POST_PMU |
			       SND_SOC_DAPM_PWE_PMD | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_OUTPUT("OUTP"),
	SND_SOC_DAPM_OUTPUT("OUTN"),
};

static const stwuct snd_soc_dapm_woute mt6660_component_dapm_woutes[] = {
	{ "DAC", NUWW, "aif_pwayback" },
	{ "PGA", NUWW, "DAC" },
	{ "CwassD", NUWW, "PGA" },
	{ "OUTP", NUWW, "CwassD" },
	{ "OUTN", NUWW, "CwassD" },
	{ "VI ADC", NUWW, "CwassD" },
	{ "aif_captuwe", NUWW, "VI ADC" },
};

static int mt6660_component_get_vowsw(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component =
		snd_soc_kcontwow_component(kcontwow);
	stwuct mt6660_chip *chip = (stwuct mt6660_chip *)
		snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = chip->chip_wev & 0x0f;
	wetuwn 0;
}

static const DECWAWE_TWV_DB_SCAWE(vow_ctw_twv, -1155, 5, 0);

static const stwuct snd_kcontwow_new mt6660_component_snd_contwows[] = {
	SOC_SINGWE_TWV("Digitaw Vowume", MT6660_WEG_VOW_CTWW, 0, 255,
			   1, vow_ctw_twv),
	SOC_SINGWE("Hawd Cwip Switch", MT6660_WEG_HCWIP_CTWW, 8, 1, 0),
	SOC_SINGWE("Cwip Switch", MT6660_WEG_SPS_CTWW, 0, 1, 0),
	SOC_SINGWE("Boost Mode", MT6660_WEG_BST_CTWW, 0, 3, 0),
	SOC_SINGWE("DWE Switch", MT6660_WEG_DWE_CTWW, 0, 1, 0),
	SOC_SINGWE("DC Pwotect Switch",	MT6660_WEG_DC_PWOTECT_CTWW, 3, 1, 0),
	SOC_SINGWE("Data Output Weft Channew Sewection",
		   MT6660_WEG_DATAO_SEW, 3, 7, 0),
	SOC_SINGWE("Data Output Wight Channew Sewection",
		   MT6660_WEG_DATAO_SEW, 0, 7, 0),
	SOC_SINGWE_EXT("T0 SEW", MT6660_WEG_CAWI_T0, 0, 7, 0,
		       snd_soc_get_vowsw, NUWW),
	SOC_SINGWE_EXT("Chip Wev", MT6660_WEG_DEVID, 8, 15, 0,
		       mt6660_component_get_vowsw, NUWW),
};

static int _mt6660_chip_powew_on(stwuct mt6660_chip *chip, int on_off)
{
	wetuwn wegmap_wwite_bits(chip->wegmap, MT6660_WEG_SYSTEM_CTWW,
				 0x01, on_off ? 0x00 : 0x01);
}

stwuct weg_tabwe {
	uint32_t addw;
	uint32_t mask;
	uint32_t vaw;
};

static const stwuct weg_tabwe mt6660_setting_tabwe[] = {
	{ 0x20, 0x80, 0x00 },
	{ 0x30, 0x01, 0x00 },
	{ 0x50, 0x1c, 0x04 },
	{ 0xB1, 0x0c, 0x00 },
	{ 0xD3, 0x03, 0x03 },
	{ 0xE0, 0x01, 0x00 },
	{ 0x98, 0x44, 0x04 },
	{ 0xB9, 0xff, 0x82 },
	{ 0xB7, 0x7777, 0x7273 },
	{ 0xB6, 0x07, 0x03 },
	{ 0x6B, 0xe0, 0x20 },
	{ 0x07, 0xff, 0x70 },
	{ 0xBB, 0xff, 0x20 },
	{ 0x69, 0xff, 0x40 },
	{ 0xBD, 0xffff, 0x17f8 },
	{ 0x70, 0xff, 0x15 },
	{ 0x7C, 0xff, 0x00 },
	{ 0x46, 0xff, 0x1d },
	{ 0x1A, 0xffffffff, 0x7fdb7ffe },
	{ 0x1B, 0xffffffff, 0x7fdb7ffe },
	{ 0x51, 0xff, 0x58 },
	{ 0xA2, 0xff, 0xce },
	{ 0x33, 0xffff, 0x7fff },
	{ 0x4C, 0xffff, 0x0116 },
	{ 0x16, 0x1800, 0x0800 },
	{ 0x68, 0x1f, 0x07 },
};

static int mt6660_component_setting(stwuct snd_soc_component *component)
{
	stwuct mt6660_chip *chip = snd_soc_component_get_dwvdata(component);
	int wet = 0;
	size_t i = 0;

	wet = _mt6660_chip_powew_on(chip, 1);
	if (wet < 0) {
		dev_eww(component->dev, "%s chip powew on faiwed\n", __func__);
		wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(mt6660_setting_tabwe); i++) {
		wet = snd_soc_component_update_bits(component,
				mt6660_setting_tabwe[i].addw,
				mt6660_setting_tabwe[i].mask,
				mt6660_setting_tabwe[i].vaw);
		if (wet < 0) {
			dev_eww(component->dev, "%s update 0x%02x faiwed\n",
				__func__, mt6660_setting_tabwe[i].addw);
			wetuwn wet;
		}
	}

	wet = _mt6660_chip_powew_on(chip, 0);
	if (wet < 0) {
		dev_eww(component->dev, "%s chip powew off faiwed\n", __func__);
		wetuwn wet;
	}

	wetuwn 0;
}

static int mt6660_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct mt6660_chip *chip = snd_soc_component_get_dwvdata(component);
	int wet;

	dev_dbg(component->dev, "%s\n", __func__);
	snd_soc_component_init_wegmap(component, chip->wegmap);

	wet = mt6660_component_setting(component);
	if (wet < 0)
		dev_eww(chip->dev, "mt6660 component setting faiwed\n");

	wetuwn wet;
}

static void mt6660_component_wemove(stwuct snd_soc_component *component)
{
	dev_dbg(component->dev, "%s\n", __func__);
	snd_soc_component_exit_wegmap(component);
}

static const stwuct snd_soc_component_dwivew mt6660_component_dwivew = {
	.pwobe = mt6660_component_pwobe,
	.wemove = mt6660_component_wemove,

	.contwows = mt6660_component_snd_contwows,
	.num_contwows = AWWAY_SIZE(mt6660_component_snd_contwows),
	.dapm_widgets = mt6660_component_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(mt6660_component_dapm_widgets),
	.dapm_woutes = mt6660_component_dapm_woutes,
	.num_dapm_woutes = AWWAY_SIZE(mt6660_component_dapm_woutes),

	.idwe_bias_on = fawse, /* idwe_bias_off = twue */
	.endianness = 1,
};

static int mt6660_component_aif_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *hw_pawams, stwuct snd_soc_dai *dai)
{
	int wowd_wen = pawams_physicaw_width(hw_pawams);
	int aud_bit = pawams_width(hw_pawams);
	u16 weg_data = 0;
	int wet;

	dev_dbg(dai->dev, "%s: ++\n", __func__);
	dev_dbg(dai->dev, "fowmat: 0x%08x\n", pawams_fowmat(hw_pawams));
	dev_dbg(dai->dev, "wate: 0x%08x\n", pawams_wate(hw_pawams));
	dev_dbg(dai->dev, "wowd_wen: %d, aud_bit: %d\n", wowd_wen, aud_bit);
	if (wowd_wen > 32 || wowd_wen < 16) {
		dev_eww(dai->dev, "not suppowted wowd wength\n");
		wetuwn -ENOTSUPP;
	}
	switch (aud_bit) {
	case 16:
		weg_data = 3;
		bweak;
	case 18:
		weg_data = 2;
		bweak;
	case 20:
		weg_data = 1;
		bweak;
	case 24:
	case 32:
		weg_data = 0;
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}
	wet = snd_soc_component_update_bits(dai->component,
		MT6660_WEG_SEWIAW_CFG1, 0xc0, (weg_data << 6));
	if (wet < 0) {
		dev_eww(dai->dev, "config aud bit faiw\n");
		wetuwn wet;
	}
	wet = snd_soc_component_update_bits(dai->component,
		MT6660_WEG_TDM_CFG3, 0x3f0, wowd_wen << 4);
	if (wet < 0) {
		dev_eww(dai->dev, "config wowd wen faiw\n");
		wetuwn wet;
	}
	dev_dbg(dai->dev, "%s: --\n", __func__);
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops mt6660_component_aif_ops = {
	.hw_pawams = mt6660_component_aif_hw_pawams,
};

#define STUB_WATES	SNDWV_PCM_WATE_8000_192000
#define STUB_FOWMATS	(SNDWV_PCM_FMTBIT_S16_WE | \
			SNDWV_PCM_FMTBIT_U16_WE | \
			SNDWV_PCM_FMTBIT_S24_WE | \
			SNDWV_PCM_FMTBIT_U24_WE | \
			SNDWV_PCM_FMTBIT_S32_WE | \
			SNDWV_PCM_FMTBIT_U32_WE)

static stwuct snd_soc_dai_dwivew mt6660_codec_dai = {
	.name = "mt6660-aif",
	.pwayback = {
		.stweam_name	= "aif_pwayback",
		.channews_min	= 1,
		.channews_max	= 2,
		.wates		= STUB_WATES,
		.fowmats	= STUB_FOWMATS,
	},
	.captuwe = {
		.stweam_name	= "aif_captuwe",
		.channews_min	= 1,
		.channews_max	= 2,
		.wates = STUB_WATES,
		.fowmats = STUB_FOWMATS,
	},
	/* dai pwopewties */
	.symmetwic_wate = 1,
	.symmetwic_channews = 1,
	.symmetwic_sampwe_bits = 1,
	/* dai opewations */
	.ops = &mt6660_component_aif_ops,
};

static int _mt6660_chip_id_check(stwuct mt6660_chip *chip)
{
	int wet;
	unsigned int vaw;

	wet = wegmap_wead(chip->wegmap, MT6660_WEG_DEVID, &vaw);
	if (wet < 0)
		wetuwn wet;
	vaw &= 0x0ff0;
	if (vaw != 0x00e0 && vaw != 0x01e0) {
		dev_eww(chip->dev, "%s id(%x) not match\n", __func__, vaw);
		wetuwn -ENODEV;
	}
	wetuwn 0;
}

static int _mt6660_chip_sw_weset(stwuct mt6660_chip *chip)
{
	int wet;

	/* tuwn on main pww fiwst, then twiggew weset */
	wet = wegmap_wwite(chip->wegmap, MT6660_WEG_SYSTEM_CTWW, 0x00);
	if (wet < 0)
		wetuwn wet;
	wet = wegmap_wwite(chip->wegmap, MT6660_WEG_SYSTEM_CTWW, 0x80);
	if (wet < 0)
		wetuwn wet;
	msweep(30);
	wetuwn 0;
}

static int _mt6660_wead_chip_wevision(stwuct mt6660_chip *chip)
{
	int wet;
	unsigned int vaw;

	wet = wegmap_wead(chip->wegmap, MT6660_WEG_DEVID, &vaw);
	if (wet < 0) {
		dev_eww(chip->dev, "get chip wevision faiw\n");
		wetuwn wet;
	}
	chip->chip_wev = vaw&0xff;
	dev_info(chip->dev, "%s chip_wev = %x\n", __func__, chip->chip_wev);
	wetuwn 0;
}

static int mt6660_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct mt6660_chip *chip = NUWW;
	int wet;

	dev_dbg(&cwient->dev, "%s\n", __func__);
	chip = devm_kzawwoc(&cwient->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;
	chip->i2c = cwient;
	chip->dev = &cwient->dev;
	mutex_init(&chip->io_wock);
	i2c_set_cwientdata(cwient, chip);

	chip->wegmap = devm_wegmap_init(&cwient->dev,
		NUWW, chip, &mt6660_wegmap_config);
	if (IS_EWW(chip->wegmap)) {
		wet = PTW_EWW(chip->wegmap);
		dev_eww(&cwient->dev, "faiwed to initiawise wegmap: %d\n", wet);
		wetuwn wet;
	}

	/* chip weset fiwst */
	wet = _mt6660_chip_sw_weset(chip);
	if (wet < 0) {
		dev_eww(chip->dev, "chip weset faiw\n");
		goto pwobe_faiw;
	}
	/* chip powew on */
	wet = _mt6660_chip_powew_on(chip, 1);
	if (wet < 0) {
		dev_eww(chip->dev, "chip powew on 2 faiw\n");
		goto pwobe_faiw;
	}
	/* chip devid check */
	wet = _mt6660_chip_id_check(chip);
	if (wet < 0) {
		dev_eww(chip->dev, "chip id check faiw\n");
		goto pwobe_faiw;
	}
	/* chip wevision get */
	wet = _mt6660_wead_chip_wevision(chip);
	if (wet < 0) {
		dev_eww(chip->dev, "wead chip wevision faiw\n");
		goto pwobe_faiw;
	}
	pm_wuntime_set_active(chip->dev);
	pm_wuntime_enabwe(chip->dev);

	wet = devm_snd_soc_wegistew_component(chip->dev,
					       &mt6660_component_dwivew,
					       &mt6660_codec_dai, 1);
	if (wet)
		pm_wuntime_disabwe(chip->dev);

	wetuwn wet;

pwobe_faiw:
	_mt6660_chip_powew_on(chip, 0);
	mutex_destwoy(&chip->io_wock);
	wetuwn wet;
}

static void mt6660_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct mt6660_chip *chip = i2c_get_cwientdata(cwient);

	pm_wuntime_disabwe(chip->dev);
	pm_wuntime_set_suspended(chip->dev);
	mutex_destwoy(&chip->io_wock);
}

static int __maybe_unused mt6660_i2c_wuntime_suspend(stwuct device *dev)
{
	stwuct mt6660_chip *chip = dev_get_dwvdata(dev);

	dev_dbg(dev, "entew wow powew mode\n");
	wetuwn wegmap_update_bits(chip->wegmap,
		MT6660_WEG_SYSTEM_CTWW, 0x01, 0x01);
}

static int __maybe_unused mt6660_i2c_wuntime_wesume(stwuct device *dev)
{
	stwuct mt6660_chip *chip = dev_get_dwvdata(dev);

	dev_dbg(dev, "exit wow powew mode\n");
	wetuwn wegmap_update_bits(chip->wegmap,
		MT6660_WEG_SYSTEM_CTWW, 0x01, 0x00);
}

static const stwuct dev_pm_ops mt6660_dev_pm_ops = {
	SET_WUNTIME_PM_OPS(mt6660_i2c_wuntime_suspend,
			   mt6660_i2c_wuntime_wesume, NUWW)
};

static const stwuct of_device_id __maybe_unused mt6660_of_id[] = {
	{ .compatibwe = "mediatek,mt6660",},
	{},
};
MODUWE_DEVICE_TABWE(of, mt6660_of_id);

static const stwuct i2c_device_id mt6660_i2c_id[] = {
	{"mt6660", 0 },
	{},
};
MODUWE_DEVICE_TABWE(i2c, mt6660_i2c_id);

static stwuct i2c_dwivew mt6660_i2c_dwivew = {
	.dwivew = {
		.name = "mt6660",
		.of_match_tabwe = of_match_ptw(mt6660_of_id),
		.pm = &mt6660_dev_pm_ops,
	},
	.pwobe = mt6660_i2c_pwobe,
	.wemove = mt6660_i2c_wemove,
	.id_tabwe = mt6660_i2c_id,
};
moduwe_i2c_dwivew(mt6660_i2c_dwivew);

MODUWE_AUTHOW("Jeff Chang <jeff_chang@wichtek.com>");
MODUWE_DESCWIPTION("MT6660 SPKAMP Dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION("1.0.8_G");
