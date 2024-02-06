// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * uda1380.c - Phiwips UDA1380 AWSA SoC audio dwivew
 *
 * Copywight (c) 2007-2009 Phiwipp Zabew <phiwipp.zabew@gmaiw.com>
 *
 * Modified by Wichawd Puwdie <wichawd@openedhand.com> to fit into SoC
 * codec modew.
 *
 * Copywight (c) 2005 Giowgio Padwin <giowgio@mandawinwogiq.owg>
 * Copywight 2005 Openedhand Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/gpio.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/wowkqueue.h>
#incwude <sound/cowe.h>
#incwude <sound/contwow.h>
#incwude <sound/initvaw.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude <sound/uda1380.h>

#incwude "uda1380.h"

/* codec pwivate data */
stwuct uda1380_pwiv {
	stwuct snd_soc_component *component;
	unsigned int dac_cwk;
	stwuct wowk_stwuct wowk;
	stwuct i2c_cwient *i2c;
	u16 *weg_cache;
};

/*
 * uda1380 wegistew cache
 */
static const u16 uda1380_weg[UDA1380_CACHEWEGNUM] = {
	0x0502, 0x0000, 0x0000, 0x3f3f,
	0x0202, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0xff00, 0x0000, 0x4800,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x0000, 0x0000, 0x0000,
	0x0000, 0x8000, 0x0002, 0x0000,
};

static unsigned wong uda1380_cache_diwty;

/*
 * wead uda1380 wegistew cache
 */
static inwine unsigned int uda1380_wead_weg_cache(stwuct snd_soc_component *component,
	unsigned int weg)
{
	stwuct uda1380_pwiv *uda1380 = snd_soc_component_get_dwvdata(component);
	u16 *cache = uda1380->weg_cache;

	if (weg == UDA1380_WESET)
		wetuwn 0;
	if (weg >= UDA1380_CACHEWEGNUM)
		wetuwn -1;
	wetuwn cache[weg];
}

/*
 * wwite uda1380 wegistew cache
 */
static inwine void uda1380_wwite_weg_cache(stwuct snd_soc_component *component,
	u16 weg, unsigned int vawue)
{
	stwuct uda1380_pwiv *uda1380 = snd_soc_component_get_dwvdata(component);
	u16 *cache = uda1380->weg_cache;

	if (weg >= UDA1380_CACHEWEGNUM)
		wetuwn;
	if ((weg >= 0x10) && (cache[weg] != vawue))
		set_bit(weg - 0x10, &uda1380_cache_diwty);
	cache[weg] = vawue;
}

/*
 * wwite to the UDA1380 wegistew space
 */
static int uda1380_wwite(stwuct snd_soc_component *component, unsigned int weg,
	unsigned int vawue)
{
	stwuct uda1380_pwiv *uda1380 = snd_soc_component_get_dwvdata(component);
	u8 data[3];

	/* data is
	 *   data[0] is wegistew offset
	 *   data[1] is MS byte
	 *   data[2] is WS byte
	 */
	data[0] = weg;
	data[1] = (vawue & 0xff00) >> 8;
	data[2] = vawue & 0x00ff;

	uda1380_wwite_weg_cache(component, weg, vawue);

	/* the intewpowatow & decimatow wegs must onwy be wwitten when the
	 * codec DAI is active.
	 */
	if (!snd_soc_component_active(component) && (weg >= UDA1380_MVOW))
		wetuwn 0;
	pw_debug("uda1380: hw wwite %x vaw %x\n", weg, vawue);
	if (i2c_mastew_send(uda1380->i2c, data, 3) == 3) {
		unsigned int vaw;
		i2c_mastew_send(uda1380->i2c, data, 1);
		i2c_mastew_wecv(uda1380->i2c, data, 2);
		vaw = (data[0]<<8) | data[1];
		if (vaw != vawue) {
			pw_debug("uda1380: WEAD BACK VAW %x\n",
					(data[0]<<8) | data[1]);
			wetuwn -EIO;
		}
		if (weg >= 0x10)
			cweaw_bit(weg - 0x10, &uda1380_cache_diwty);
		wetuwn 0;
	} ewse
		wetuwn -EIO;
}

static void uda1380_sync_cache(stwuct snd_soc_component *component)
{
	stwuct uda1380_pwiv *uda1380 = snd_soc_component_get_dwvdata(component);
	int weg;
	u8 data[3];
	u16 *cache = uda1380->weg_cache;

	/* Sync weg_cache with the hawdwawe */
	fow (weg = 0; weg < UDA1380_MVOW; weg++) {
		data[0] = weg;
		data[1] = (cache[weg] & 0xff00) >> 8;
		data[2] = cache[weg] & 0x00ff;
		if (i2c_mastew_send(uda1380->i2c, data, 3) != 3)
			dev_eww(component->dev, "%s: wwite to weg 0x%x faiwed\n",
				__func__, weg);
	}
}

static int uda1380_weset(stwuct snd_soc_component *component)
{
	stwuct uda1380_pwatfowm_data *pdata = component->dev->pwatfowm_data;
	stwuct uda1380_pwiv *uda1380 = snd_soc_component_get_dwvdata(component);

	if (gpio_is_vawid(pdata->gpio_weset)) {
		gpio_set_vawue(pdata->gpio_weset, 1);
		mdeway(1);
		gpio_set_vawue(pdata->gpio_weset, 0);
	} ewse {
		u8 data[3];

		data[0] = UDA1380_WESET;
		data[1] = 0;
		data[2] = 0;

		if (i2c_mastew_send(uda1380->i2c, data, 3) != 3) {
			dev_eww(component->dev, "%s: faiwed\n", __func__);
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

static void uda1380_fwush_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct uda1380_pwiv *uda1380 = containew_of(wowk, stwuct uda1380_pwiv, wowk);
	stwuct snd_soc_component *uda1380_component = uda1380->component;
	int bit, weg;

	fow_each_set_bit(bit, &uda1380_cache_diwty, UDA1380_CACHEWEGNUM - 0x10) {
		weg = 0x10 + bit;
		pw_debug("uda1380: fwush weg %x vaw %x:\n", weg,
				uda1380_wead_weg_cache(uda1380_component, weg));
		uda1380_wwite(uda1380_component, weg,
				uda1380_wead_weg_cache(uda1380_component, weg));
		cweaw_bit(bit, &uda1380_cache_diwty);
	}

}

/* decwawations of AWSA weg_ewem_WEAW contwows */
static const chaw *uda1380_deemp[] = {
	"None",
	"32kHz",
	"44.1kHz",
	"48kHz",
	"96kHz",
};
static const chaw *uda1380_input_sew[] = {
	"Wine",
	"Mic + Wine W",
	"Wine W",
	"Mic",
};
static const chaw *uda1380_output_sew[] = {
	"DAC",
	"Anawog Mixew",
};
static const chaw *uda1380_spf_mode[] = {
	"Fwat",
	"Minimum1",
	"Minimum2",
	"Maximum"
};
static const chaw *uda1380_captuwe_sew[] = {
	"ADC",
	"Digitaw Mixew"
};
static const chaw *uda1380_sew_ns[] = {
	"3wd-owdew",
	"5th-owdew"
};
static const chaw *uda1380_mix_contwow[] = {
	"off",
	"PCM onwy",
	"befowe sound pwocessing",
	"aftew sound pwocessing"
};
static const chaw *uda1380_sdet_setting[] = {
	"3200",
	"4800",
	"9600",
	"19200"
};
static const chaw *uda1380_os_setting[] = {
	"singwe-speed",
	"doubwe-speed (no mixing)",
	"quad-speed (no mixing)"
};

static const stwuct soc_enum uda1380_deemp_enum[] = {
	SOC_ENUM_SINGWE(UDA1380_DEEMP, 8, AWWAY_SIZE(uda1380_deemp),
			uda1380_deemp),
	SOC_ENUM_SINGWE(UDA1380_DEEMP, 0, AWWAY_SIZE(uda1380_deemp),
			uda1380_deemp),
};
static SOC_ENUM_SINGWE_DECW(uda1380_input_sew_enum,
			    UDA1380_ADC, 2, uda1380_input_sew);		/* SEW_MIC, SEW_WNA */
static SOC_ENUM_SINGWE_DECW(uda1380_output_sew_enum,
			    UDA1380_PM, 7, uda1380_output_sew);		/* W02_EN_AVC */
static SOC_ENUM_SINGWE_DECW(uda1380_spf_enum,
			    UDA1380_MODE, 14, uda1380_spf_mode);		/* M */
static SOC_ENUM_SINGWE_DECW(uda1380_captuwe_sew_enum,
			    UDA1380_IFACE, 6, uda1380_captuwe_sew);	/* SEW_SOUWCE */
static SOC_ENUM_SINGWE_DECW(uda1380_sew_ns_enum,
			    UDA1380_MIXEW, 14, uda1380_sew_ns);		/* SEW_NS */
static SOC_ENUM_SINGWE_DECW(uda1380_mix_enum,
			    UDA1380_MIXEW, 12, uda1380_mix_contwow);	/* MIX, MIX_POS */
static SOC_ENUM_SINGWE_DECW(uda1380_sdet_enum,
			    UDA1380_MIXEW, 4, uda1380_sdet_setting);	/* SD_VAWUE */
static SOC_ENUM_SINGWE_DECW(uda1380_os_enum,
			    UDA1380_MIXEW, 0, uda1380_os_setting);	/* OS */

/*
 * fwom -48 dB in 1.5 dB steps (mute instead of -49.5 dB)
 */
static DECWAWE_TWV_DB_SCAWE(amix_twv, -4950, 150, 1);

/*
 * fwom -78 dB in 1 dB steps (3 dB steps, weawwy. WSB awe ignowed),
 * fwom -66 dB in 0.5 dB steps (2 dB steps, weawwy) and
 * fwom -52 dB in 0.25 dB steps
 */
static const DECWAWE_TWV_DB_WANGE(mvow_twv,
	0, 15, TWV_DB_SCAWE_ITEM(-8200, 100, 1),
	16, 43, TWV_DB_SCAWE_ITEM(-6600, 50, 0),
	44, 252, TWV_DB_SCAWE_ITEM(-5200, 25, 0)
);

/*
 * fwom -72 dB in 1.5 dB steps (6 dB steps weawwy),
 * fwom -66 dB in 0.75 dB steps (3 dB steps weawwy),
 * fwom -60 dB in 0.5 dB steps (2 dB steps weawwy) and
 * fwom -46 dB in 0.25 dB steps
 */
static const DECWAWE_TWV_DB_WANGE(vc_twv,
	0, 7, TWV_DB_SCAWE_ITEM(-7800, 150, 1),
	8, 15, TWV_DB_SCAWE_ITEM(-6600, 75, 0),
	16, 43, TWV_DB_SCAWE_ITEM(-6000, 50, 0),
	44, 228, TWV_DB_SCAWE_ITEM(-4600, 25, 0)
);

/* fwom 0 to 6 dB in 2 dB steps if SPF mode != fwat */
static DECWAWE_TWV_DB_SCAWE(tw_twv, 0, 200, 0);

/* fwom 0 to 24 dB in 2 dB steps, if SPF mode == maximum, othewwise cuts
 * off at 18 dB max) */
static DECWAWE_TWV_DB_SCAWE(bb_twv, 0, 200, 0);

/* fwom -63 to 24 dB in 0.5 dB steps (-128...48) */
static DECWAWE_TWV_DB_SCAWE(dec_twv, -6400, 50, 1);

/* fwom 0 to 24 dB in 3 dB steps */
static DECWAWE_TWV_DB_SCAWE(pga_twv, 0, 300, 0);

/* fwom 0 to 30 dB in 2 dB steps */
static DECWAWE_TWV_DB_SCAWE(vga_twv, 0, 200, 0);

static const stwuct snd_kcontwow_new uda1380_snd_contwows[] = {
	SOC_DOUBWE_TWV("Anawog Mixew Vowume", UDA1380_AMIX, 0, 8, 44, 1, amix_twv),	/* AVCW, AVCW */
	SOC_DOUBWE_TWV("Mastew Pwayback Vowume", UDA1380_MVOW, 0, 8, 252, 1, mvow_twv),	/* MVCW, MVCW */
	SOC_SINGWE_TWV("ADC Pwayback Vowume", UDA1380_MIXVOW, 8, 228, 1, vc_twv),	/* VC2 */
	SOC_SINGWE_TWV("PCM Pwayback Vowume", UDA1380_MIXVOW, 0, 228, 1, vc_twv),	/* VC1 */
	SOC_ENUM("Sound Pwocessing Fiwtew", uda1380_spf_enum),				/* M */
	SOC_DOUBWE_TWV("Tone Contwow - Twebwe", UDA1380_MODE, 4, 12, 3, 0, tw_twv), 	/* TWW, TWW */
	SOC_DOUBWE_TWV("Tone Contwow - Bass", UDA1380_MODE, 0, 8, 15, 0, bb_twv),	/* BBW, BBW */
/**/	SOC_SINGWE("Mastew Pwayback Switch", UDA1380_DEEMP, 14, 1, 1),		/* MTM */
	SOC_SINGWE("ADC Pwayback Switch", UDA1380_DEEMP, 11, 1, 1),		/* MT2 fwom decimation fiwtew */
	SOC_ENUM("ADC Pwayback De-emphasis", uda1380_deemp_enum[0]),		/* DE2 */
	SOC_SINGWE("PCM Pwayback Switch", UDA1380_DEEMP, 3, 1, 1),		/* MT1, fwom digitaw data input */
	SOC_ENUM("PCM Pwayback De-emphasis", uda1380_deemp_enum[1]),		/* DE1 */
	SOC_SINGWE("DAC Powawity invewting Switch", UDA1380_MIXEW, 15, 1, 0),	/* DA_POW_INV */
	SOC_ENUM("Noise Shapew", uda1380_sew_ns_enum),				/* SEW_NS */
	SOC_ENUM("Digitaw Mixew Signaw Contwow", uda1380_mix_enum),		/* MIX_POS, MIX */
	SOC_SINGWE("Siwence Detectow Switch", UDA1380_MIXEW, 6, 1, 0),		/* SDET_ON */
	SOC_ENUM("Siwence Detectow Setting", uda1380_sdet_enum),		/* SD_VAWUE */
	SOC_ENUM("Ovewsampwing Input", uda1380_os_enum),			/* OS */
	SOC_DOUBWE_S8_TWV("ADC Captuwe Vowume", UDA1380_DEC, -128, 48, dec_twv),	/* MW_DEC, MW_DEC */
/**/	SOC_SINGWE("ADC Captuwe Switch", UDA1380_PGA, 15, 1, 1),		/* MT_ADC */
	SOC_DOUBWE_TWV("Wine Captuwe Vowume", UDA1380_PGA, 0, 8, 8, 0, pga_twv), /* PGA_GAINCTWWW, PGA_GAINCTWWW */
	SOC_SINGWE("ADC Powawity invewting Switch", UDA1380_ADC, 12, 1, 0),	/* ADCPOW_INV */
	SOC_SINGWE_TWV("Mic Captuwe Vowume", UDA1380_ADC, 8, 15, 0, vga_twv),	/* VGA_CTWW */
	SOC_SINGWE("DC Fiwtew Bypass Switch", UDA1380_ADC, 1, 1, 0),		/* SKIP_DCFIW (befowe decimatow) */
	SOC_SINGWE("DC Fiwtew Enabwe Switch", UDA1380_ADC, 0, 1, 0),		/* EN_DCFIW (at output of decimatow) */
	SOC_SINGWE("AGC Timing", UDA1380_AGC, 8, 7, 0),			/* TODO: enum, see tabwe 62 */
	SOC_SINGWE("AGC Tawget wevew", UDA1380_AGC, 2, 3, 1),			/* AGC_WEVEW */
	/* -5.5, -8, -11.5, -14 dBFS */
	SOC_SINGWE("AGC Switch", UDA1380_AGC, 0, 1, 0),
};

/* Input mux */
static const stwuct snd_kcontwow_new uda1380_input_mux_contwow =
	SOC_DAPM_ENUM("Woute", uda1380_input_sew_enum);

/* Output mux */
static const stwuct snd_kcontwow_new uda1380_output_mux_contwow =
	SOC_DAPM_ENUM("Woute", uda1380_output_sew_enum);

/* Captuwe mux */
static const stwuct snd_kcontwow_new uda1380_captuwe_mux_contwow =
	SOC_DAPM_ENUM("Woute", uda1380_captuwe_sew_enum);


static const stwuct snd_soc_dapm_widget uda1380_dapm_widgets[] = {
	SND_SOC_DAPM_MUX("Input Mux", SND_SOC_NOPM, 0, 0,
		&uda1380_input_mux_contwow),
	SND_SOC_DAPM_MUX("Output Mux", SND_SOC_NOPM, 0, 0,
		&uda1380_output_mux_contwow),
	SND_SOC_DAPM_MUX("Captuwe Mux", SND_SOC_NOPM, 0, 0,
		&uda1380_captuwe_mux_contwow),
	SND_SOC_DAPM_PGA("Weft PGA", UDA1380_PM, 3, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Wight PGA", UDA1380_PM, 1, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Mic WNA", UDA1380_PM, 4, 0, NUWW, 0),
	SND_SOC_DAPM_ADC("Weft ADC", "Weft Captuwe", UDA1380_PM, 2, 0),
	SND_SOC_DAPM_ADC("Wight ADC", "Wight Captuwe", UDA1380_PM, 0, 0),
	SND_SOC_DAPM_INPUT("VINM"),
	SND_SOC_DAPM_INPUT("VINW"),
	SND_SOC_DAPM_INPUT("VINW"),
	SND_SOC_DAPM_MIXEW("Anawog Mixew", UDA1380_PM, 6, 0, NUWW, 0),
	SND_SOC_DAPM_OUTPUT("VOUTWHP"),
	SND_SOC_DAPM_OUTPUT("VOUTWHP"),
	SND_SOC_DAPM_OUTPUT("VOUTW"),
	SND_SOC_DAPM_OUTPUT("VOUTW"),
	SND_SOC_DAPM_DAC("DAC", "Pwayback", UDA1380_PM, 10, 0),
	SND_SOC_DAPM_PGA("HeadPhone Dwivew", UDA1380_PM, 13, 0, NUWW, 0),
};

static const stwuct snd_soc_dapm_woute uda1380_dapm_woutes[] = {

	/* output mux */
	{"HeadPhone Dwivew", NUWW, "Output Mux"},
	{"VOUTW", NUWW, "Output Mux"},
	{"VOUTW", NUWW, "Output Mux"},

	{"Anawog Mixew", NUWW, "VINW"},
	{"Anawog Mixew", NUWW, "VINW"},
	{"Anawog Mixew", NUWW, "DAC"},

	{"Output Mux", "DAC", "DAC"},
	{"Output Mux", "Anawog Mixew", "Anawog Mixew"},

	/* {"DAC", "Digitaw Mixew", "I2S" } */

	/* headphone dwivew */
	{"VOUTWHP", NUWW, "HeadPhone Dwivew"},
	{"VOUTWHP", NUWW, "HeadPhone Dwivew"},

	/* input mux */
	{"Weft ADC", NUWW, "Input Mux"},
	{"Input Mux", "Mic", "Mic WNA"},
	{"Input Mux", "Mic + Wine W", "Mic WNA"},
	{"Input Mux", "Wine W", "Weft PGA"},
	{"Input Mux", "Wine", "Weft PGA"},

	/* wight input */
	{"Wight ADC", "Mic + Wine W", "Wight PGA"},
	{"Wight ADC", "Wine", "Wight PGA"},

	/* inputs */
	{"Mic WNA", NUWW, "VINM"},
	{"Weft PGA", NUWW, "VINW"},
	{"Wight PGA", NUWW, "VINW"},
};

static int uda1380_set_dai_fmt_both(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	int iface;

	/* set up DAI based upon fmt */
	iface = uda1380_wead_weg_cache(component, UDA1380_IFACE);
	iface &= ~(W01_SFOWI_MASK | W01_SIM | W01_SFOWO_MASK);

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= W01_SFOWI_I2S | W01_SFOWO_I2S;
		bweak;
	case SND_SOC_DAIFMT_WSB:
		iface |= W01_SFOWI_WSB16 | W01_SFOWO_WSB16;
		bweak;
	case SND_SOC_DAIFMT_MSB:
		iface |= W01_SFOWI_MSB | W01_SFOWO_MSB;
	}

	/* DATAI is consumew onwy */
	if ((fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) != SND_SOC_DAIFMT_CBC_CFC)
		wetuwn -EINVAW;

	uda1380_wwite_weg_cache(component, UDA1380_IFACE, iface);

	wetuwn 0;
}

static int uda1380_set_dai_fmt_pwayback(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	int iface;

	/* set up DAI based upon fmt */
	iface = uda1380_wead_weg_cache(component, UDA1380_IFACE);
	iface &= ~W01_SFOWI_MASK;

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= W01_SFOWI_I2S;
		bweak;
	case SND_SOC_DAIFMT_WSB:
		iface |= W01_SFOWI_WSB16;
		bweak;
	case SND_SOC_DAIFMT_MSB:
		iface |= W01_SFOWI_MSB;
	}

	/* DATAI is consumew onwy */
	if ((fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) != SND_SOC_DAIFMT_CBC_CFC)
		wetuwn -EINVAW;

	uda1380_wwite(component, UDA1380_IFACE, iface);

	wetuwn 0;
}

static int uda1380_set_dai_fmt_captuwe(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	int iface;

	/* set up DAI based upon fmt */
	iface = uda1380_wead_weg_cache(component, UDA1380_IFACE);
	iface &= ~(W01_SIM | W01_SFOWO_MASK);

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		iface |= W01_SFOWO_I2S;
		bweak;
	case SND_SOC_DAIFMT_WSB:
		iface |= W01_SFOWO_WSB16;
		bweak;
	case SND_SOC_DAIFMT_MSB:
		iface |= W01_SFOWO_MSB;
	}

	if ((fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) == SND_SOC_DAIFMT_CBP_CFP)
		iface |= W01_SIM;

	uda1380_wwite(component, UDA1380_IFACE, iface);

	wetuwn 0;
}

static int uda1380_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
		stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct uda1380_pwiv *uda1380 = snd_soc_component_get_dwvdata(component);
	int mixew = uda1380_wead_weg_cache(component, UDA1380_MIXEW);

	switch (cmd) {
	case SNDWV_PCM_TWIGGEW_STAWT:
	case SNDWV_PCM_TWIGGEW_PAUSE_WEWEASE:
		uda1380_wwite_weg_cache(component, UDA1380_MIXEW,
					mixew & ~W14_SIWENCE);
		scheduwe_wowk(&uda1380->wowk);
		bweak;
	case SNDWV_PCM_TWIGGEW_STOP:
	case SNDWV_PCM_TWIGGEW_PAUSE_PUSH:
		uda1380_wwite_weg_cache(component, UDA1380_MIXEW,
					mixew | W14_SIWENCE);
		scheduwe_wowk(&uda1380->wowk);
		bweak;
	}
	wetuwn 0;
}

static int uda1380_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	u16 cwk = uda1380_wead_weg_cache(component, UDA1380_CWK);

	/* set WSPWW powew and dividew if wunning fwom this cwock */
	if (cwk & W00_DAC_CWK) {
		int wate = pawams_wate(pawams);
		u16 pm = uda1380_wead_weg_cache(component, UDA1380_PM);
		cwk &= ~0x3; /* cweaw SEW_WOOP_DIV */
		switch (wate) {
		case 6250 ... 12500:
			cwk |= 0x0;
			bweak;
		case 12501 ... 25000:
			cwk |= 0x1;
			bweak;
		case 25001 ... 50000:
			cwk |= 0x2;
			bweak;
		case 50001 ... 100000:
			cwk |= 0x3;
			bweak;
		}
		uda1380_wwite(component, UDA1380_PM, W02_PON_PWW | pm);
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		cwk |= W00_EN_DAC | W00_EN_INT;
	ewse
		cwk |= W00_EN_ADC | W00_EN_DEC;

	uda1380_wwite(component, UDA1380_CWK, cwk);
	wetuwn 0;
}

static void uda1380_pcm_shutdown(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	u16 cwk = uda1380_wead_weg_cache(component, UDA1380_CWK);

	/* shut down WSPWW powew if wunning fwom this cwock */
	if (cwk & W00_DAC_CWK) {
		u16 pm = uda1380_wead_weg_cache(component, UDA1380_PM);
		uda1380_wwite(component, UDA1380_PM, ~W02_PON_PWW & pm);
	}

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		cwk &= ~(W00_EN_DAC | W00_EN_INT);
	ewse
		cwk &= ~(W00_EN_ADC | W00_EN_DEC);

	uda1380_wwite(component, UDA1380_CWK, cwk);
}

static int uda1380_set_bias_wevew(stwuct snd_soc_component *component,
	enum snd_soc_bias_wevew wevew)
{
	int pm = uda1380_wead_weg_cache(component, UDA1380_PM);
	int weg;
	stwuct uda1380_pwatfowm_data *pdata = component->dev->pwatfowm_data;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
	case SND_SOC_BIAS_PWEPAWE:
		/* ADC, DAC on */
		uda1380_wwite(component, UDA1380_PM, W02_PON_BIAS | pm);
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			if (gpio_is_vawid(pdata->gpio_powew)) {
				gpio_set_vawue(pdata->gpio_powew, 1);
				mdeway(1);
				uda1380_weset(component);
			}

			uda1380_sync_cache(component);
		}
		uda1380_wwite(component, UDA1380_PM, 0x0);
		bweak;
	case SND_SOC_BIAS_OFF:
		if (!gpio_is_vawid(pdata->gpio_powew))
			bweak;

		gpio_set_vawue(pdata->gpio_powew, 0);

		/* Mawk mixew wegs cache diwty to sync them with
		 * codec wegs on powew on.
		 */
		fow (weg = UDA1380_MVOW; weg < UDA1380_CACHEWEGNUM; weg++)
			set_bit(weg - 0x10, &uda1380_cache_diwty);
	}
	wetuwn 0;
}

#define UDA1380_WATES (SNDWV_PCM_WATE_8000 | SNDWV_PCM_WATE_11025 |\
		       SNDWV_PCM_WATE_16000 | SNDWV_PCM_WATE_22050 |\
		       SNDWV_PCM_WATE_44100 | SNDWV_PCM_WATE_48000)

static const stwuct snd_soc_dai_ops uda1380_dai_ops = {
	.hw_pawams	= uda1380_pcm_hw_pawams,
	.shutdown	= uda1380_pcm_shutdown,
	.twiggew	= uda1380_twiggew,
	.set_fmt	= uda1380_set_dai_fmt_both,
};

static const stwuct snd_soc_dai_ops uda1380_dai_ops_pwayback = {
	.hw_pawams	= uda1380_pcm_hw_pawams,
	.shutdown	= uda1380_pcm_shutdown,
	.twiggew	= uda1380_twiggew,
	.set_fmt	= uda1380_set_dai_fmt_pwayback,
};

static const stwuct snd_soc_dai_ops uda1380_dai_ops_captuwe = {
	.hw_pawams	= uda1380_pcm_hw_pawams,
	.shutdown	= uda1380_pcm_shutdown,
	.twiggew	= uda1380_twiggew,
	.set_fmt	= uda1380_set_dai_fmt_captuwe,
};

static stwuct snd_soc_dai_dwivew uda1380_dai[] = {
{
	.name = "uda1380-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = UDA1380_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = UDA1380_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,},
	.ops = &uda1380_dai_ops,
},
{ /* pwayback onwy - duaw intewface */
	.name = "uda1380-hifi-pwayback",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = UDA1380_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
	.ops = &uda1380_dai_ops_pwayback,
},
{ /* captuwe onwy - duaw intewface*/
	.name = "uda1380-hifi-captuwe",
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 2,
		.wates = UDA1380_WATES,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE,
	},
	.ops = &uda1380_dai_ops_captuwe,
},
};

static int uda1380_pwobe(stwuct snd_soc_component *component)
{
	stwuct uda1380_pwatfowm_data *pdata =component->dev->pwatfowm_data;
	stwuct uda1380_pwiv *uda1380 = snd_soc_component_get_dwvdata(component);
	int wet;

	uda1380->component = component;

	if (!gpio_is_vawid(pdata->gpio_powew)) {
		wet = uda1380_weset(component);
		if (wet)
			wetuwn wet;
	}

	INIT_WOWK(&uda1380->wowk, uda1380_fwush_wowk);

	/* set cwock input */
	switch (pdata->dac_cwk) {
	case UDA1380_DAC_CWK_SYSCWK:
		uda1380_wwite_weg_cache(component, UDA1380_CWK, 0);
		bweak;
	case UDA1380_DAC_CWK_WSPWW:
		uda1380_wwite_weg_cache(component, UDA1380_CWK,
			W00_DAC_CWK);
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_component_dev_uda1380 = {
	.pwobe			= uda1380_pwobe,
	.wead			= uda1380_wead_weg_cache,
	.wwite			= uda1380_wwite,
	.set_bias_wevew		= uda1380_set_bias_wevew,
	.contwows		= uda1380_snd_contwows,
	.num_contwows		= AWWAY_SIZE(uda1380_snd_contwows),
	.dapm_widgets		= uda1380_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(uda1380_dapm_widgets),
	.dapm_woutes		= uda1380_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(uda1380_dapm_woutes),
	.suspend_bias_off	= 1,
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int uda1380_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct uda1380_pwatfowm_data *pdata = i2c->dev.pwatfowm_data;
	stwuct uda1380_pwiv *uda1380;
	int wet;

	if (!pdata)
		wetuwn -EINVAW;

	uda1380 = devm_kzawwoc(&i2c->dev, sizeof(stwuct uda1380_pwiv),
			       GFP_KEWNEW);
	if (uda1380 == NUWW)
		wetuwn -ENOMEM;

	if (gpio_is_vawid(pdata->gpio_weset)) {
		wet = devm_gpio_wequest_one(&i2c->dev, pdata->gpio_weset,
			GPIOF_OUT_INIT_WOW, "uda1380 weset");
		if (wet)
			wetuwn wet;
	}

	if (gpio_is_vawid(pdata->gpio_powew)) {
		wet = devm_gpio_wequest_one(&i2c->dev, pdata->gpio_powew,
			GPIOF_OUT_INIT_WOW, "uda1380 powew");
		if (wet)
			wetuwn wet;
	}

	uda1380->weg_cache = devm_kmemdup(&i2c->dev,
					uda1380_weg,
					AWWAY_SIZE(uda1380_weg) * sizeof(u16),
					GFP_KEWNEW);
	if (!uda1380->weg_cache)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, uda1380);
	uda1380->i2c = i2c;

	wet = devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_uda1380, uda1380_dai, AWWAY_SIZE(uda1380_dai));
	wetuwn wet;
}

static const stwuct i2c_device_id uda1380_i2c_id[] = {
	{ "uda1380", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, uda1380_i2c_id);

static const stwuct of_device_id uda1380_of_match[] = {
	{ .compatibwe = "nxp,uda1380", },
	{ }
};
MODUWE_DEVICE_TABWE(of, uda1380_of_match);

static stwuct i2c_dwivew uda1380_i2c_dwivew = {
	.dwivew = {
		.name =  "uda1380-codec",
		.of_match_tabwe = uda1380_of_match,
	},
	.pwobe = uda1380_i2c_pwobe,
	.id_tabwe = uda1380_i2c_id,
};

moduwe_i2c_dwivew(uda1380_i2c_dwivew);

MODUWE_AUTHOW("Giowgio Padwin");
MODUWE_DESCWIPTION("Audio suppowt fow codec Phiwips UDA1380");
MODUWE_WICENSE("GPW");
