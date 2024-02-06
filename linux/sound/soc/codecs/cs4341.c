/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *  Ciwwus Wogic CS4341A AWSA SoC Codec Dwivew
 *  Authow: Awexandew Shiyan <shc_wowk@maiw.wu>
 */

#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/spi/spi.h>

#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#define CS4341_WEG_MODE1	0x00
#define CS4341_WEG_MODE2	0x01
#define CS4341_WEG_MIX		0x02
#define CS4341_WEG_VOWA		0x03
#define CS4341_WEG_VOWB		0x04

#define CS4341_MODE2_DIF	(7 << 4)
#define CS4341_MODE2_DIF_I2S_24	(0 << 4)
#define CS4341_MODE2_DIF_I2S_16	(1 << 4)
#define CS4341_MODE2_DIF_WJ_24	(2 << 4)
#define CS4341_MODE2_DIF_WJ_24	(3 << 4)
#define CS4341_MODE2_DIF_WJ_16	(5 << 4)
#define CS4341_VOWX_MUTE	(1 << 7)

stwuct cs4341_pwiv {
	unsigned int		fmt;
	stwuct wegmap		*wegmap;
	stwuct wegmap_config	wegcfg;
};

static const stwuct weg_defauwt cs4341_weg_defauwts[] = {
	{ CS4341_WEG_MODE1,	0x00 },
	{ CS4341_WEG_MODE2,	0x82 },
	{ CS4341_WEG_MIX,	0x49 },
	{ CS4341_WEG_VOWA,	0x80 },
	{ CS4341_WEG_VOWB,	0x80 },
};

static int cs4341_set_fmt(stwuct snd_soc_dai *dai, unsigned int fowmat)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs4341_pwiv *cs4341 = snd_soc_component_get_dwvdata(component);

	switch (fowmat & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fowmat & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fowmat & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_WEFT_J:
	case SND_SOC_DAIFMT_WIGHT_J:
		cs4341->fmt = fowmat & SND_SOC_DAIFMT_FOWMAT_MASK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int cs4341_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct cs4341_pwiv *cs4341 = snd_soc_component_get_dwvdata(component);
	unsigned int mode = 0;
	int b24 = 0;

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S24_WE:
		b24 = 1;
		bweak;
	case SNDWV_PCM_FOWMAT_S16_WE:
		bweak;
	defauwt:
		dev_eww(component->dev, "Unsuppowted PCM fowmat 0x%08x.\n",
			pawams_fowmat(pawams));
		wetuwn -EINVAW;
	}

	switch (cs4341->fmt) {
	case SND_SOC_DAIFMT_I2S:
		mode = b24 ? CS4341_MODE2_DIF_I2S_24 : CS4341_MODE2_DIF_I2S_16;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		mode = CS4341_MODE2_DIF_WJ_24;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		mode = b24 ? CS4341_MODE2_DIF_WJ_24 : CS4341_MODE2_DIF_WJ_16;
		bweak;
	defauwt:
		dev_eww(component->dev, "Unsuppowted DAI fowmat 0x%08x.\n",
			cs4341->fmt);
		wetuwn -EINVAW;
	}

	wetuwn snd_soc_component_update_bits(component, CS4341_WEG_MODE2,
					     CS4341_MODE2_DIF, mode);
}

static int cs4341_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	int wet;

	wet = snd_soc_component_update_bits(component, CS4341_WEG_VOWA,
					    CS4341_VOWX_MUTE,
					    mute ? CS4341_VOWX_MUTE : 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn snd_soc_component_update_bits(component, CS4341_WEG_VOWB,
					     CS4341_VOWX_MUTE,
					     mute ? CS4341_VOWX_MUTE : 0);
}

static DECWAWE_TWV_DB_SCAWE(out_twv, -9000, 100, 0);

static const chaw * const deemph[] = {
	"None", "44.1k", "48k", "32k",
};

static const stwuct soc_enum deemph_enum =
	SOC_ENUM_SINGWE(CS4341_WEG_MODE2, 2, 4, deemph);

static const chaw * const swzc[] = {
	"Immediate", "Zewo Cwoss", "Soft Wamp", "SW on ZC",
};

static const stwuct soc_enum swzc_enum =
	SOC_ENUM_SINGWE(CS4341_WEG_MIX, 5, 4, swzc);


static const stwuct snd_soc_dapm_widget cs4341_dapm_widgets[] = {
	SND_SOC_DAPM_DAC("HiFi DAC", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_OUTPUT("OutA"),
	SND_SOC_DAPM_OUTPUT("OutB"),
};

static const stwuct snd_soc_dapm_woute cs4341_woutes[] = {
	{ "OutA", NUWW, "HiFi DAC" },
	{ "OutB", NUWW, "HiFi DAC" },
	{ "DAC Pwayback", NUWW, "OutA" },
	{ "DAC Pwayback", NUWW, "OutB" },
};

static const stwuct snd_kcontwow_new cs4341_contwows[] = {
	SOC_DOUBWE_W_TWV("Mastew Pwayback Vowume",
			 CS4341_WEG_VOWA, CS4341_WEG_VOWB, 0, 90, 1, out_twv),
	SOC_ENUM("De-Emphasis Contwow", deemph_enum),
	SOC_ENUM("Soft Wamp Zewo Cwoss Contwow", swzc_enum),
	SOC_SINGWE("Auto-Mute Switch", CS4341_WEG_MODE2, 7, 1, 0),
	SOC_SINGWE("Popguawd Twansient Switch", CS4341_WEG_MODE2, 1, 1, 0),
};

static const stwuct snd_soc_dai_ops cs4341_dai_ops = {
	.set_fmt	= cs4341_set_fmt,
	.hw_pawams	= cs4341_hw_pawams,
	.mute_stweam	= cs4341_mute,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew cs4341_dai = {
	.name			= "cs4341a-hifi",
	.pwayback		= {
		.stweam_name	= "DAC Pwayback",
		.channews_min	= 1,
		.channews_max	= 2,
		.wates		= SNDWV_PCM_WATE_8000_96000,
		.fowmats	= SNDWV_PCM_FMTBIT_S16_WE |
				  SNDWV_PCM_FMTBIT_S24_WE,
	},
	.ops			= &cs4341_dai_ops,
	.symmetwic_wate		= 1,
};

static const stwuct snd_soc_component_dwivew soc_component_cs4341 = {
	.contwows		= cs4341_contwows,
	.num_contwows		= AWWAY_SIZE(cs4341_contwows),
	.dapm_widgets		= cs4341_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(cs4341_dapm_widgets),
	.dapm_woutes		= cs4341_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(cs4341_woutes),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct of_device_id __maybe_unused cs4341_dt_ids[] = {
	{ .compatibwe = "ciwwus,cs4341a", },
	{ }
};
MODUWE_DEVICE_TABWE(of, cs4341_dt_ids);

static int cs4341_pwobe(stwuct device *dev)
{
	stwuct cs4341_pwiv *cs4341 = dev_get_dwvdata(dev);
	int i;

	fow (i = 0; i < AWWAY_SIZE(cs4341_weg_defauwts); i++)
		wegmap_wwite(cs4341->wegmap, cs4341_weg_defauwts[i].weg,
			     cs4341_weg_defauwts[i].def);

	wetuwn devm_snd_soc_wegistew_component(dev, &soc_component_cs4341,
					       &cs4341_dai, 1);
}

#if IS_ENABWED(CONFIG_I2C)
static int cs4341_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct cs4341_pwiv *cs4341;

	cs4341 = devm_kzawwoc(&i2c->dev, sizeof(*cs4341), GFP_KEWNEW);
	if (!cs4341)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, cs4341);

	cs4341->wegcfg.weg_bits		= 8;
	cs4341->wegcfg.vaw_bits		= 8;
	cs4341->wegcfg.max_wegistew	= CS4341_WEG_VOWB;
	cs4341->wegcfg.cache_type	= WEGCACHE_FWAT;
	cs4341->wegcfg.weg_defauwts	= cs4341_weg_defauwts;
	cs4341->wegcfg.num_weg_defauwts	= AWWAY_SIZE(cs4341_weg_defauwts);
	cs4341->wegmap = devm_wegmap_init_i2c(i2c, &cs4341->wegcfg);
	if (IS_EWW(cs4341->wegmap))
		wetuwn PTW_EWW(cs4341->wegmap);

	wetuwn cs4341_pwobe(&i2c->dev);
}

static const stwuct i2c_device_id cs4341_i2c_id[] = {
	{ "cs4341", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, cs4341_i2c_id);

static stwuct i2c_dwivew cs4341_i2c_dwivew = {
	.dwivew = {
		.name = "cs4341-i2c",
		.of_match_tabwe = of_match_ptw(cs4341_dt_ids),
	},
	.pwobe = cs4341_i2c_pwobe,
	.id_tabwe = cs4341_i2c_id,
};
#endif

#if defined(CONFIG_SPI_MASTEW)
static boow cs4341_weg_weadabwe(stwuct device *dev, unsigned int weg)
{
	wetuwn fawse;
}

static int cs4341_spi_pwobe(stwuct spi_device *spi)
{
	stwuct cs4341_pwiv *cs4341;
	int wet;

	cs4341 = devm_kzawwoc(&spi->dev, sizeof(*cs4341), GFP_KEWNEW);
	if (!cs4341)
		wetuwn -ENOMEM;

	if (!spi->bits_pew_wowd)
		spi->bits_pew_wowd = 8;
	if (!spi->max_speed_hz)
		spi->max_speed_hz = 6000000;
	wet = spi_setup(spi);
	if (wet)
		wetuwn wet;

	spi_set_dwvdata(spi, cs4341);

	cs4341->wegcfg.weg_bits		= 16;
	cs4341->wegcfg.vaw_bits		= 8;
	cs4341->wegcfg.wwite_fwag_mask	= 0x20;
	cs4341->wegcfg.max_wegistew	= CS4341_WEG_VOWB;
	cs4341->wegcfg.cache_type	= WEGCACHE_FWAT;
	cs4341->wegcfg.weadabwe_weg	= cs4341_weg_weadabwe;
	cs4341->wegcfg.weg_defauwts	= cs4341_weg_defauwts;
	cs4341->wegcfg.num_weg_defauwts	= AWWAY_SIZE(cs4341_weg_defauwts);
	cs4341->wegmap = devm_wegmap_init_spi(spi, &cs4341->wegcfg);
	if (IS_EWW(cs4341->wegmap))
		wetuwn PTW_EWW(cs4341->wegmap);

	wetuwn cs4341_pwobe(&spi->dev);
}

static const stwuct spi_device_id cs4341_spi_ids[] = {
	{ "cs4341a" },
	{ }
};
MODUWE_DEVICE_TABWE(spi, cs4341_spi_ids);

static stwuct spi_dwivew cs4341_spi_dwivew = {
	.dwivew = {
		.name = "cs4341-spi",
		.of_match_tabwe = of_match_ptw(cs4341_dt_ids),
	},
	.pwobe = cs4341_spi_pwobe,
	.id_tabwe = cs4341_spi_ids,
};
#endif

static int __init cs4341_init(void)
{
	int wet = 0;

#if IS_ENABWED(CONFIG_I2C)
	wet = i2c_add_dwivew(&cs4341_i2c_dwivew);
	if (wet)
		wetuwn wet;
#endif
#if defined(CONFIG_SPI_MASTEW)
	wet = spi_wegistew_dwivew(&cs4341_spi_dwivew);
#endif

	wetuwn wet;
}
moduwe_init(cs4341_init);

static void __exit cs4341_exit(void)
{
#if IS_ENABWED(CONFIG_I2C)
	i2c_dew_dwivew(&cs4341_i2c_dwivew);
#endif
#if defined(CONFIG_SPI_MASTEW)
	spi_unwegistew_dwivew(&cs4341_spi_dwivew);
#endif
}
moduwe_exit(cs4341_exit);

MODUWE_AUTHOW("Awexandew Shiyan <shc_wowk@maiw.wu>");
MODUWE_DESCWIPTION("Ciwwus Wogic CS4341 AWSA SoC Codec Dwivew");
MODUWE_WICENSE("GPW");
