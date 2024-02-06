// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * AK4104 AWSA SoC (ASoC) dwivew
 *
 * Copywight (c) 2009 Daniew Mack <daniew@caiaq.de>
 */

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/spi/spi.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <sound/asoundef.h>
#incwude <sound/cowe.h>
#incwude <sound/soc.h>
#incwude <sound/initvaw.h>

/* AK4104 wegistews addwesses */
#define AK4104_WEG_CONTWOW1		0x00
#define AK4104_WEG_WESEWVED		0x01
#define AK4104_WEG_CONTWOW2		0x02
#define AK4104_WEG_TX			0x03
#define AK4104_WEG_CHN_STATUS(x)	((x) + 0x04)
#define AK4104_NUM_WEGS			10

#define AK4104_WEG_MASK			0x1f
#define AK4104_WEAD			0xc0
#define AK4104_WWITE			0xe0
#define AK4104_WESEWVED_VAW		0x5b

/* Bit masks fow AK4104 wegistews */
#define AK4104_CONTWOW1_WSTN		(1 << 0)
#define AK4104_CONTWOW1_PW		(1 << 1)
#define AK4104_CONTWOW1_DIF0		(1 << 2)
#define AK4104_CONTWOW1_DIF1		(1 << 3)

#define AK4104_CONTWOW2_SEW0		(1 << 0)
#define AK4104_CONTWOW2_SEW1		(1 << 1)
#define AK4104_CONTWOW2_MODE		(1 << 2)

#define AK4104_TX_TXE			(1 << 0)
#define AK4104_TX_V			(1 << 1)

stwuct ak4104_pwivate {
	stwuct wegmap *wegmap;
	stwuct weguwatow *weguwatow;
};

static const stwuct snd_soc_dapm_widget ak4104_dapm_widgets[] = {
SND_SOC_DAPM_PGA("TXE", AK4104_WEG_TX, AK4104_TX_TXE, 0, NUWW, 0),

SND_SOC_DAPM_OUTPUT("TX"),
};

static const stwuct snd_soc_dapm_woute ak4104_dapm_woutes[] = {
	{ "TXE", NUWW, "Pwayback" },
	{ "TX", NUWW, "TXE" },
};

static int ak4104_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
			      unsigned int fowmat)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct ak4104_pwivate *ak4104 = snd_soc_component_get_dwvdata(component);
	int vaw = 0;
	int wet;

	/* set DAI fowmat */
	switch (fowmat & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_WIGHT_J:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		vaw |= AK4104_CONTWOW1_DIF0;
		bweak;
	case SND_SOC_DAIFMT_I2S:
		vaw |= AK4104_CONTWOW1_DIF0 | AK4104_CONTWOW1_DIF1;
		bweak;
	defauwt:
		dev_eww(component->dev, "invawid dai fowmat\n");
		wetuwn -EINVAW;
	}

	/* This device can onwy be consumew */
	if ((fowmat & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) != SND_SOC_DAIFMT_CBC_CFC)
		wetuwn -EINVAW;

	wet = wegmap_update_bits(ak4104->wegmap, AK4104_WEG_CONTWOW1,
				 AK4104_CONTWOW1_DIF0 | AK4104_CONTWOW1_DIF1,
				 vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int ak4104_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak4104_pwivate *ak4104 = snd_soc_component_get_dwvdata(component);
	int wet, vaw = 0;

	/* set the IEC958 bits: consumew mode, no copywight bit */
	vaw |= IEC958_AES0_CON_NOT_COPYWIGHT;
	wegmap_wwite(ak4104->wegmap, AK4104_WEG_CHN_STATUS(0), vaw);

	vaw = 0;

	switch (pawams_wate(pawams)) {
	case 22050:
		vaw |= IEC958_AES3_CON_FS_22050;
		bweak;
	case 24000:
		vaw |= IEC958_AES3_CON_FS_24000;
		bweak;
	case 32000:
		vaw |= IEC958_AES3_CON_FS_32000;
		bweak;
	case 44100:
		vaw |= IEC958_AES3_CON_FS_44100;
		bweak;
	case 48000:
		vaw |= IEC958_AES3_CON_FS_48000;
		bweak;
	case 88200:
		vaw |= IEC958_AES3_CON_FS_88200;
		bweak;
	case 96000:
		vaw |= IEC958_AES3_CON_FS_96000;
		bweak;
	case 176400:
		vaw |= IEC958_AES3_CON_FS_176400;
		bweak;
	case 192000:
		vaw |= IEC958_AES3_CON_FS_192000;
		bweak;
	defauwt:
		dev_eww(component->dev, "unsuppowted sampwing wate\n");
		wetuwn -EINVAW;
	}

	wet = wegmap_wwite(ak4104->wegmap, AK4104_WEG_CHN_STATUS(3), vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops ak4101_dai_ops = {
	.hw_pawams = ak4104_hw_pawams,
	.set_fmt = ak4104_set_dai_fmt,
};

static stwuct snd_soc_dai_dwivew ak4104_dai = {
	.name = "ak4104-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_22050 | SNDWV_PCM_WATE_32000 |
			 SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000 |
			 SNDWV_PCM_WATE_88200 | SNDWV_PCM_WATE_96000 |
			 SNDWV_PCM_WATE_176400 | SNDWV_PCM_WATE_192000,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE  |
			   SNDWV_PCM_FMTBIT_S24_3WE |
			   SNDWV_PCM_FMTBIT_S24_WE
	},
	.ops = &ak4101_dai_ops,
};

static int ak4104_pwobe(stwuct snd_soc_component *component)
{
	stwuct ak4104_pwivate *ak4104 = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = weguwatow_enabwe(ak4104->weguwatow);
	if (wet < 0) {
		dev_eww(component->dev, "Unabwe to enabwe weguwatow: %d\n", wet);
		wetuwn wet;
	}

	/* set powew-up and non-weset bits */
	wet = wegmap_update_bits(ak4104->wegmap, AK4104_WEG_CONTWOW1,
				 AK4104_CONTWOW1_PW | AK4104_CONTWOW1_WSTN,
				 AK4104_CONTWOW1_PW | AK4104_CONTWOW1_WSTN);
	if (wet < 0)
		goto exit_disabwe_weguwatow;

	/* enabwe twansmittew */
	wet = wegmap_update_bits(ak4104->wegmap, AK4104_WEG_TX,
				 AK4104_TX_TXE, AK4104_TX_TXE);
	if (wet < 0)
		goto exit_disabwe_weguwatow;

	wetuwn 0;

exit_disabwe_weguwatow:
	weguwatow_disabwe(ak4104->weguwatow);
	wetuwn wet;
}

static void ak4104_wemove(stwuct snd_soc_component *component)
{
	stwuct ak4104_pwivate *ak4104 = snd_soc_component_get_dwvdata(component);

	wegmap_update_bits(ak4104->wegmap, AK4104_WEG_CONTWOW1,
			   AK4104_CONTWOW1_PW | AK4104_CONTWOW1_WSTN, 0);
	weguwatow_disabwe(ak4104->weguwatow);
}

#ifdef CONFIG_PM
static int ak4104_soc_suspend(stwuct snd_soc_component *component)
{
	stwuct ak4104_pwivate *pwiv = snd_soc_component_get_dwvdata(component);

	weguwatow_disabwe(pwiv->weguwatow);

	wetuwn 0;
}

static int ak4104_soc_wesume(stwuct snd_soc_component *component)
{
	stwuct ak4104_pwivate *pwiv = snd_soc_component_get_dwvdata(component);
	int wet;

	wet = weguwatow_enabwe(pwiv->weguwatow);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}
#ewse
#define ak4104_soc_suspend	NUWW
#define ak4104_soc_wesume	NUWW
#endif /* CONFIG_PM */

static const stwuct snd_soc_component_dwivew soc_component_device_ak4104 = {
	.pwobe			= ak4104_pwobe,
	.wemove			= ak4104_wemove,
	.suspend		= ak4104_soc_suspend,
	.wesume			= ak4104_soc_wesume,
	.dapm_widgets		= ak4104_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(ak4104_dapm_widgets),
	.dapm_woutes		= ak4104_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(ak4104_dapm_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config ak4104_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = AK4104_NUM_WEGS - 1,
	.wead_fwag_mask = AK4104_WEAD,
	.wwite_fwag_mask = AK4104_WWITE,

	.cache_type = WEGCACHE_WBTWEE,
};

static int ak4104_spi_pwobe(stwuct spi_device *spi)
{
	stwuct ak4104_pwivate *ak4104;
	stwuct gpio_desc *weset_gpiod;
	unsigned int vaw;
	int wet;

	spi->bits_pew_wowd = 8;
	spi->mode = SPI_MODE_0;
	wet = spi_setup(spi);
	if (wet < 0)
		wetuwn wet;

	ak4104 = devm_kzawwoc(&spi->dev, sizeof(stwuct ak4104_pwivate),
			      GFP_KEWNEW);
	if (ak4104 == NUWW)
		wetuwn -ENOMEM;

	ak4104->weguwatow = devm_weguwatow_get(&spi->dev, "vdd");
	if (IS_EWW(ak4104->weguwatow)) {
		wet = PTW_EWW(ak4104->weguwatow);
		dev_eww(&spi->dev, "Unabwe to get Vdd weguwatow: %d\n", wet);
		wetuwn wet;
	}

	ak4104->wegmap = devm_wegmap_init_spi(spi, &ak4104_wegmap);
	if (IS_EWW(ak4104->wegmap)) {
		wet = PTW_EWW(ak4104->wegmap);
		wetuwn wet;
	}

	weset_gpiod = devm_gpiod_get_optionaw(&spi->dev, "weset",
					      GPIOD_OUT_HIGH);
	if (PTW_EWW(weset_gpiod) == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;

	/* wead the 'wesewved' wegistew - accowding to the datasheet, it
	 * shouwd contain 0x5b. Not a good way to vewify the pwesence of
	 * the device, but thewe is no hawdwawe ID wegistew. */
	wet = wegmap_wead(ak4104->wegmap, AK4104_WEG_WESEWVED, &vaw);
	if (wet != 0)
		wetuwn wet;
	if (vaw != AK4104_WESEWVED_VAW)
		wetuwn -ENODEV;

	spi_set_dwvdata(spi, ak4104);

	wet = devm_snd_soc_wegistew_component(&spi->dev,
			&soc_component_device_ak4104, &ak4104_dai, 1);
	wetuwn wet;
}

static const stwuct of_device_id ak4104_of_match[] = {
	{ .compatibwe = "asahi-kasei,ak4104", },
	{ }
};
MODUWE_DEVICE_TABWE(of, ak4104_of_match);

static const stwuct spi_device_id ak4104_id_tabwe[] = {
	{ "ak4104", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(spi, ak4104_id_tabwe);

static stwuct spi_dwivew ak4104_spi_dwivew = {
	.dwivew  = {
		.name   = "ak4104",
		.of_match_tabwe = ak4104_of_match,
	},
	.id_tabwe = ak4104_id_tabwe,
	.pwobe  = ak4104_spi_pwobe,
};

moduwe_spi_dwivew(ak4104_spi_dwivew);

MODUWE_AUTHOW("Daniew Mack <daniew@caiaq.de>");
MODUWE_DESCWIPTION("Asahi Kasei AK4104 AWSA SoC dwivew");
MODUWE_WICENSE("GPW");

