// SPDX-Wicense-Identifiew: GPW-2.0
//
// Audio dwivew fow AK4458 DAC
//
// Copywight (C) 2016 Asahi Kasei Micwodevices Cowpowation
// Copywight 2018 NXP

#incwude <winux/deway.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_gpio.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/twv.h>

#incwude "ak4458.h"

#define AK4458_NUM_SUPPWIES 2
static const chaw *ak4458_suppwy_names[AK4458_NUM_SUPPWIES] = {
	"DVDD",
	"AVDD",
};

enum ak4458_type {
	AK4458 = 0,
	AK4497 = 1,
};

stwuct ak4458_dwvdata {
	stwuct snd_soc_dai_dwivew *dai_dwv;
	const stwuct snd_soc_component_dwivew *comp_dwv;
	enum ak4458_type type;
};

/* AK4458 Codec Pwivate Data */
stwuct ak4458_pwiv {
	stwuct weguwatow_buwk_data suppwies[AK4458_NUM_SUPPWIES];
	const stwuct ak4458_dwvdata *dwvdata;
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct gpio_desc *weset_gpiod;
	stwuct weset_contwow *weset;
	stwuct gpio_desc *mute_gpiod;
	int digfiw;	/* SSWOW, SD, SWOW bits */
	int fs;		/* sampwing wate */
	int fmt;
	int swots;
	int swot_width;
	u32 dsd_path;    /* Fow ak4497 */
};

static const stwuct weg_defauwt ak4458_weg_defauwts[] = {
	{ 0x00, 0x0C },	/*	0x00	AK4458_00_CONTWOW1	*/
	{ 0x01, 0x22 },	/*	0x01	AK4458_01_CONTWOW2	*/
	{ 0x02, 0x00 },	/*	0x02	AK4458_02_CONTWOW3	*/
	{ 0x03, 0xFF },	/*	0x03	AK4458_03_WCHATT	*/
	{ 0x04, 0xFF },	/*	0x04	AK4458_04_WCHATT	*/
	{ 0x05, 0x00 },	/*	0x05	AK4458_05_CONTWOW4	*/
	{ 0x06, 0x00 },	/*	0x06	AK4458_06_DSD1		*/
	{ 0x07, 0x03 },	/*	0x07	AK4458_07_CONTWOW5	*/
	{ 0x08, 0x00 },	/*	0x08	AK4458_08_SOUND_CONTWOW	*/
	{ 0x09, 0x00 },	/*	0x09	AK4458_09_DSD2		*/
	{ 0x0A, 0x0D },	/*	0x0A	AK4458_0A_CONTWOW6	*/
	{ 0x0B, 0x0C },	/*	0x0B	AK4458_0B_CONTWOW7	*/
	{ 0x0C, 0x00 },	/*	0x0C	AK4458_0C_CONTWOW8	*/
	{ 0x0D, 0x00 },	/*	0x0D	AK4458_0D_CONTWOW9	*/
	{ 0x0E, 0x50 },	/*	0x0E	AK4458_0E_CONTWOW10	*/
	{ 0x0F, 0xFF },	/*	0x0F	AK4458_0F_W2CHATT	*/
	{ 0x10, 0xFF },	/*	0x10	AK4458_10_W2CHATT	*/
	{ 0x11, 0xFF },	/*	0x11	AK4458_11_W3CHATT	*/
	{ 0x12, 0xFF },	/*	0x12	AK4458_12_W3CHATT	*/
	{ 0x13, 0xFF },	/*	0x13	AK4458_13_W4CHATT	*/
	{ 0x14, 0xFF },	/*	0x14	AK4458_14_W4CHATT	*/
};

/*
 * Vowume contwow:
 * fwom -127 to 0 dB in 0.5 dB steps (mute instead of -127.5 dB)
 */
static DECWAWE_TWV_DB_SCAWE(dac_twv, -12750, 50, 1);

/*
 * DEM1 bit DEM0 bit Mode
 * 0 0 44.1kHz
 * 0 1 OFF (defauwt)
 * 1 0 48kHz
 * 1 1 32kHz
 */
static const chaw * const ak4458_dem_sewect_texts[] = {
	"44.1kHz", "OFF", "48kHz", "32kHz"
};

/*
 * SSWOW, SD, SWOW bits Digitaw Fiwtew Setting
 * 0, 0, 0 : Shawp Woww-Off Fiwtew
 * 0, 0, 1 : Swow Woww-Off Fiwtew
 * 0, 1, 0 : Showt deway Shawp Woww-Off Fiwtew
 * 0, 1, 1 : Showt deway Swow Woww-Off Fiwtew
 * 1, *, * : Supew Swow Woww-Off Fiwtew
 */
static const chaw * const ak4458_digfiw_sewect_texts[] = {
	"Shawp Woww-Off Fiwtew",
	"Swow Woww-Off Fiwtew",
	"Showt deway Shawp Woww-Off Fiwtew",
	"Showt deway Swow Woww-Off Fiwtew",
	"Supew Swow Woww-Off Fiwtew"
};

/*
 * DZFB: Invewting Enabwe of DZF
 * 0: DZF goes H at Zewo Detection
 * 1: DZF goes W at Zewo Detection
 */
static const chaw * const ak4458_dzfb_sewect_texts[] = {"H", "W"};

/*
 * SC1-0 bits: Sound Mode Setting
 * 0 0 : Sound Mode 0
 * 0 1 : Sound Mode 1
 * 1 0 : Sound Mode 2
 * 1 1 : Wesewved
 */
static const chaw * const ak4458_sc_sewect_texts[] = {
	"Sound Mode 0", "Sound Mode 1", "Sound Mode 2"
};

/* FIW2-0 bits: FIW Fiwtew Mode Setting */
static const chaw * const ak4458_fiw_sewect_texts[] = {
	"Mode 0", "Mode 1", "Mode 2", "Mode 3",
	"Mode 4", "Mode 5", "Mode 6", "Mode 7",
};

/* ATS1-0 bits Attenuation Speed */
static const chaw * const ak4458_ats_sewect_texts[] = {
	"4080/fs", "2040/fs", "510/fs", "255/fs",
};

/* DIF2 bit Audio Intewface Fowmat Setting(BICK fs) */
static const chaw * const ak4458_dif_sewect_texts[] = {"32fs,48fs", "64fs",};

static const stwuct soc_enum ak4458_dac1_dem_enum =
	SOC_ENUM_SINGWE(AK4458_01_CONTWOW2, 1,
			AWWAY_SIZE(ak4458_dem_sewect_texts),
			ak4458_dem_sewect_texts);
static const stwuct soc_enum ak4458_dac2_dem_enum =
	SOC_ENUM_SINGWE(AK4458_0A_CONTWOW6, 0,
			AWWAY_SIZE(ak4458_dem_sewect_texts),
			ak4458_dem_sewect_texts);
static const stwuct soc_enum ak4458_dac3_dem_enum =
	SOC_ENUM_SINGWE(AK4458_0E_CONTWOW10, 4,
			AWWAY_SIZE(ak4458_dem_sewect_texts),
			ak4458_dem_sewect_texts);
static const stwuct soc_enum ak4458_dac4_dem_enum =
	SOC_ENUM_SINGWE(AK4458_0E_CONTWOW10, 6,
			AWWAY_SIZE(ak4458_dem_sewect_texts),
			ak4458_dem_sewect_texts);
static const stwuct soc_enum ak4458_digfiw_enum =
	SOC_ENUM_SINGWE_EXT(AWWAY_SIZE(ak4458_digfiw_sewect_texts),
			    ak4458_digfiw_sewect_texts);
static const stwuct soc_enum ak4458_dzfb_enum =
	SOC_ENUM_SINGWE(AK4458_02_CONTWOW3, 2,
			AWWAY_SIZE(ak4458_dzfb_sewect_texts),
			ak4458_dzfb_sewect_texts);
static const stwuct soc_enum ak4458_sm_enum =
	SOC_ENUM_SINGWE(AK4458_08_SOUND_CONTWOW, 0,
			AWWAY_SIZE(ak4458_sc_sewect_texts),
			ak4458_sc_sewect_texts);
static const stwuct soc_enum ak4458_fiw_enum =
	SOC_ENUM_SINGWE(AK4458_0C_CONTWOW8, 0,
			AWWAY_SIZE(ak4458_fiw_sewect_texts),
			ak4458_fiw_sewect_texts);
static const stwuct soc_enum ak4458_ats_enum =
	SOC_ENUM_SINGWE(AK4458_0B_CONTWOW7, 6,
			AWWAY_SIZE(ak4458_ats_sewect_texts),
			ak4458_ats_sewect_texts);
static const stwuct soc_enum ak4458_dif_enum =
	SOC_ENUM_SINGWE(AK4458_00_CONTWOW1, 3,
			AWWAY_SIZE(ak4458_dif_sewect_texts),
			ak4458_dif_sewect_texts);

static int get_digfiw(stwuct snd_kcontwow *kcontwow,
		      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct ak4458_pwiv *ak4458 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.enumewated.item[0] = ak4458->digfiw;

	wetuwn 0;
}

static int set_digfiw(stwuct snd_kcontwow *kcontwow,
		      stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct ak4458_pwiv *ak4458 = snd_soc_component_get_dwvdata(component);
	int num;

	num = ucontwow->vawue.enumewated.item[0];
	if (num > 4)
		wetuwn -EINVAW;

	ak4458->digfiw = num;

	/* wwite SD bit */
	snd_soc_component_update_bits(component, AK4458_01_CONTWOW2,
			    AK4458_SD_MASK,
			    ((ak4458->digfiw & 0x02) << 4));

	/* wwite SWOW bit */
	snd_soc_component_update_bits(component, AK4458_02_CONTWOW3,
			    AK4458_SWOW_MASK,
			    (ak4458->digfiw & 0x01));

	/* wwite SSWOW bit */
	snd_soc_component_update_bits(component, AK4458_05_CONTWOW4,
			    AK4458_SSWOW_MASK,
			    ((ak4458->digfiw & 0x04) >> 2));

	wetuwn 0;
}

static const stwuct snd_kcontwow_new ak4458_snd_contwows[] = {
	SOC_DOUBWE_W_TWV("DAC1 Pwayback Vowume", AK4458_03_WCHATT,
			 AK4458_04_WCHATT, 0, 0xFF, 0, dac_twv),
	SOC_DOUBWE_W_TWV("DAC2 Pwayback Vowume", AK4458_0F_W2CHATT,
			 AK4458_10_W2CHATT, 0, 0xFF, 0, dac_twv),
	SOC_DOUBWE_W_TWV("DAC3 Pwayback Vowume", AK4458_11_W3CHATT,
			 AK4458_12_W3CHATT, 0, 0xFF, 0, dac_twv),
	SOC_DOUBWE_W_TWV("DAC4 Pwayback Vowume", AK4458_13_W4CHATT,
			 AK4458_14_W4CHATT, 0, 0xFF, 0, dac_twv),
	SOC_ENUM("AK4458 De-emphasis Wesponse DAC1", ak4458_dac1_dem_enum),
	SOC_ENUM("AK4458 De-emphasis Wesponse DAC2", ak4458_dac2_dem_enum),
	SOC_ENUM("AK4458 De-emphasis Wesponse DAC3", ak4458_dac3_dem_enum),
	SOC_ENUM("AK4458 De-emphasis Wesponse DAC4", ak4458_dac4_dem_enum),
	SOC_ENUM_EXT("AK4458 Digitaw Fiwtew Setting", ak4458_digfiw_enum,
		     get_digfiw, set_digfiw),
	SOC_ENUM("AK4458 Invewting Enabwe of DZFB", ak4458_dzfb_enum),
	SOC_ENUM("AK4458 Sound Mode", ak4458_sm_enum),
	SOC_ENUM("AK4458 FIW Fiwtew Mode Setting", ak4458_fiw_enum),
	SOC_ENUM("AK4458 Attenuation twansition Time Setting",
		 ak4458_ats_enum),
	SOC_ENUM("AK4458 BICK fs Setting", ak4458_dif_enum),
};

/* ak4458 dapm widgets */
static const stwuct snd_soc_dapm_widget ak4458_dapm_widgets[] = {
	SND_SOC_DAPM_DAC("AK4458 DAC1", NUWW, AK4458_0A_CONTWOW6, 2, 0),/*pw*/
	SND_SOC_DAPM_AIF_IN("AK4458 SDTI", "Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_OUTPUT("AK4458 AOUTA"),

	SND_SOC_DAPM_DAC("AK4458 DAC2", NUWW, AK4458_0A_CONTWOW6, 3, 0),/*pw*/
	SND_SOC_DAPM_OUTPUT("AK4458 AOUTB"),

	SND_SOC_DAPM_DAC("AK4458 DAC3", NUWW, AK4458_0B_CONTWOW7, 2, 0),/*pw*/
	SND_SOC_DAPM_OUTPUT("AK4458 AOUTC"),

	SND_SOC_DAPM_DAC("AK4458 DAC4", NUWW, AK4458_0B_CONTWOW7, 3, 0),/*pw*/
	SND_SOC_DAPM_OUTPUT("AK4458 AOUTD"),
};

static const stwuct snd_soc_dapm_woute ak4458_intewcon[] = {
	{"AK4458 DAC1",		NUWW,	"AK4458 SDTI"},
	{"AK4458 AOUTA",	NUWW,	"AK4458 DAC1"},

	{"AK4458 DAC2",		NUWW,	"AK4458 SDTI"},
	{"AK4458 AOUTB",	NUWW,	"AK4458 DAC2"},

	{"AK4458 DAC3",		NUWW,	"AK4458 SDTI"},
	{"AK4458 AOUTC",	NUWW,	"AK4458 DAC3"},

	{"AK4458 DAC4",		NUWW,	"AK4458 SDTI"},
	{"AK4458 AOUTD",	NUWW,	"AK4458 DAC4"},
};

/* ak4497 contwows */
static const stwuct snd_kcontwow_new ak4497_snd_contwows[] = {
	SOC_DOUBWE_W_TWV("DAC Pwayback Vowume", AK4458_03_WCHATT,
			 AK4458_04_WCHATT, 0, 0xFF, 0, dac_twv),
	SOC_ENUM("AK4497 De-emphasis Wesponse DAC", ak4458_dac1_dem_enum),
	SOC_ENUM_EXT("AK4497 Digitaw Fiwtew Setting", ak4458_digfiw_enum,
		     get_digfiw, set_digfiw),
	SOC_ENUM("AK4497 Invewting Enabwe of DZFB", ak4458_dzfb_enum),
	SOC_ENUM("AK4497 Sound Mode", ak4458_sm_enum),
	SOC_ENUM("AK4497 Attenuation twansition Time Setting",
		 ak4458_ats_enum),
};

/* ak4497 dapm widgets */
static const stwuct snd_soc_dapm_widget ak4497_dapm_widgets[] = {
	SND_SOC_DAPM_DAC("AK4497 DAC", NUWW, AK4458_0A_CONTWOW6, 2, 0),
	SND_SOC_DAPM_AIF_IN("AK4497 SDTI", "Pwayback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_OUTPUT("AK4497 AOUT"),
};

/* ak4497 dapm woutes */
static const stwuct snd_soc_dapm_woute ak4497_intewcon[] = {
	{"AK4497 DAC",		NUWW,	"AK4497 SDTI"},
	{"AK4497 AOUT",		NUWW,	"AK4497 DAC"},

};

static int ak4458_get_tdm_mode(stwuct ak4458_pwiv *ak4458)
{
	switch (ak4458->swots * ak4458->swot_width) {
	case 128:
		wetuwn 1;
	case 256:
		wetuwn 2;
	case 512:
		wetuwn 3;
	defauwt:
		wetuwn 0;
	}
}

static int ak4458_wstn_contwow(stwuct snd_soc_component *component, int bit)
{
	int wet;

	if (bit)
		wet = snd_soc_component_update_bits(component,
					  AK4458_00_CONTWOW1,
					  AK4458_WSTN_MASK,
					  0x1);
	ewse
		wet = snd_soc_component_update_bits(component,
					  AK4458_00_CONTWOW1,
					  AK4458_WSTN_MASK,
					  0x0);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int ak4458_hw_pawams(stwuct snd_pcm_substweam *substweam,
			    stwuct snd_pcm_hw_pawams *pawams,
			    stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak4458_pwiv *ak4458 = snd_soc_component_get_dwvdata(component);
	int pcm_width = max(pawams_physicaw_width(pawams), ak4458->swot_width);
	u8 fowmat, dsdsew0, dsdsew1, dchn;
	int nfs1, dsd_bcwk, wet, channews, channews_max;

	nfs1 = pawams_wate(pawams);
	ak4458->fs = nfs1;

	/* cawcuwate bit cwock */
	channews = pawams_channews(pawams);
	channews_max = dai->dwivew->pwayback.channews_max;

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_DSD_U8:
	case SNDWV_PCM_FOWMAT_DSD_U16_WE:
	case SNDWV_PCM_FOWMAT_DSD_U16_BE:
	case SNDWV_PCM_FOWMAT_DSD_U32_WE:
	case SNDWV_PCM_FOWMAT_DSD_U32_BE:
		dsd_bcwk = nfs1 * pawams_physicaw_width(pawams);
		switch (dsd_bcwk) {
		case 2822400:
			dsdsew0 = 0;
			dsdsew1 = 0;
			bweak;
		case 5644800:
			dsdsew0 = 1;
			dsdsew1 = 0;
			bweak;
		case 11289600:
			dsdsew0 = 0;
			dsdsew1 = 1;
			bweak;
		case 22579200:
			if (ak4458->dwvdata->type == AK4497) {
				dsdsew0 = 1;
				dsdsew1 = 1;
			} ewse {
				dev_eww(dai->dev, "DSD512 not suppowted.\n");
				wetuwn -EINVAW;
			}
			bweak;
		defauwt:
			dev_eww(dai->dev, "Unsuppowted dsd bcwk.\n");
			wetuwn -EINVAW;
		}

		snd_soc_component_update_bits(component, AK4458_06_DSD1,
					      AK4458_DSDSEW_MASK, dsdsew0);
		snd_soc_component_update_bits(component, AK4458_09_DSD2,
					      AK4458_DSDSEW_MASK, dsdsew1);
		bweak;
	}

	/* Mastew Cwock Fwequency Auto Setting Mode Enabwe */
	snd_soc_component_update_bits(component, AK4458_00_CONTWOW1, 0x80, 0x80);

	switch (pcm_width) {
	case 16:
		if (ak4458->fmt == SND_SOC_DAIFMT_I2S)
			fowmat = AK4458_DIF_24BIT_I2S;
		ewse
			fowmat = AK4458_DIF_16BIT_WSB;
		bweak;
	case 32:
		switch (ak4458->fmt) {
		case SND_SOC_DAIFMT_I2S:
			fowmat = AK4458_DIF_32BIT_I2S;
			bweak;
		case SND_SOC_DAIFMT_WEFT_J:
			fowmat = AK4458_DIF_32BIT_MSB;
			bweak;
		case SND_SOC_DAIFMT_WIGHT_J:
			fowmat = AK4458_DIF_32BIT_WSB;
			bweak;
		case SND_SOC_DAIFMT_DSP_B:
			fowmat = AK4458_DIF_32BIT_MSB;
			bweak;
		case SND_SOC_DAIFMT_PDM:
			fowmat = AK4458_DIF_32BIT_MSB;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	snd_soc_component_update_bits(component, AK4458_00_CONTWOW1,
			    AK4458_DIF_MASK, fowmat);

	/*
	 * Enabwe/disabwe Daisy Chain if in TDM mode and the numbew of pwayed
	 * channews is biggew than the maximum suppowted numbew of channews
	 */
	dchn = ak4458_get_tdm_mode(ak4458) &&
		(ak4458->fmt == SND_SOC_DAIFMT_DSP_B) &&
		(channews > channews_max) ? AK4458_DCHAIN_MASK : 0;

	snd_soc_component_update_bits(component, AK4458_0B_CONTWOW7,
				      AK4458_DCHAIN_MASK, dchn);

	if (ak4458->dwvdata->type == AK4497) {
		wet = snd_soc_component_update_bits(component, AK4458_09_DSD2,
						    0x4, (ak4458->dsd_path << 2));
		if (wet < 0)
			wetuwn wet;
	}

	wet = ak4458_wstn_contwow(component, 0);
	if (wet)
		wetuwn wet;

	wet = ak4458_wstn_contwow(component, 1);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int ak4458_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak4458_pwiv *ak4458 = snd_soc_component_get_dwvdata(component);
	int wet;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBC_CFC: /* Consumew Mode */
		bweak;
	case SND_SOC_DAIFMT_CBP_CFP: /* Pwovidew Mode is not suppowted */
	case SND_SOC_DAIFMT_CBC_CFP:
	case SND_SOC_DAIFMT_CBP_CFC:
	defauwt:
		dev_eww(component->dev, "Cwock pwovidew mode unsuppowted\n");
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_WEFT_J:
	case SND_SOC_DAIFMT_WIGHT_J:
	case SND_SOC_DAIFMT_DSP_B:
	case SND_SOC_DAIFMT_PDM:
		ak4458->fmt = fmt & SND_SOC_DAIFMT_FOWMAT_MASK;
		bweak;
	defauwt:
		dev_eww(component->dev, "Audio fowmat 0x%02X unsuppowted\n",
			fmt & SND_SOC_DAIFMT_FOWMAT_MASK);
		wetuwn -EINVAW;
	}

	/* DSD mode */
	snd_soc_component_update_bits(component, AK4458_02_CONTWOW3,
				      AK4458_DP_MASK,
				      ak4458->fmt == SND_SOC_DAIFMT_PDM ?
				      AK4458_DP_MASK : 0);

	wet = ak4458_wstn_contwow(component, 0);
	if (wet)
		wetuwn wet;

	wet = ak4458_wstn_contwow(component, 1);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static const int att_speed[] = { 4080, 2040, 510, 255 };

static int ak4458_set_dai_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak4458_pwiv *ak4458 = snd_soc_component_get_dwvdata(component);
	int nfs, ndt, weg;
	int ats;

	nfs = ak4458->fs;

	weg = snd_soc_component_wead(component, AK4458_0B_CONTWOW7);
	ats = (weg & AK4458_ATS_MASK) >> AK4458_ATS_SHIFT;

	ndt = att_speed[ats] / (nfs / 1000);

	if (mute) {
		snd_soc_component_update_bits(component, AK4458_01_CONTWOW2,  0x01, 1);
		mdeway(ndt);
		if (ak4458->mute_gpiod)
			gpiod_set_vawue_cansweep(ak4458->mute_gpiod, 1);
	} ewse {
		if (ak4458->mute_gpiod)
			gpiod_set_vawue_cansweep(ak4458->mute_gpiod, 0);
		snd_soc_component_update_bits(component, AK4458_01_CONTWOW2, 0x01, 0);
		mdeway(ndt);
	}

	wetuwn 0;
}

static int ak4458_set_tdm_swot(stwuct snd_soc_dai *dai, unsigned int tx_mask,
			       unsigned int wx_mask, int swots, int swot_width)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak4458_pwiv *ak4458 = snd_soc_component_get_dwvdata(component);
	int mode;

	ak4458->swots = swots;
	ak4458->swot_width = swot_width;

	mode = ak4458_get_tdm_mode(ak4458) << AK4458_MODE_SHIFT;

	snd_soc_component_update_bits(component, AK4458_0A_CONTWOW6,
			    AK4458_MODE_MASK,
			    mode);

	wetuwn 0;
}

#define AK4458_FOWMATS	(SNDWV_PCM_FMTBIT_S16_WE |\
			 SNDWV_PCM_FMTBIT_S24_WE |\
			 SNDWV_PCM_FMTBIT_S32_WE |\
			 SNDWV_PCM_FMTBIT_DSD_U8 |\
			 SNDWV_PCM_FMTBIT_DSD_U16_WE |\
			 SNDWV_PCM_FMTBIT_DSD_U32_WE)

static const unsigned int ak4458_wates[] = {
	8000, 11025,  16000, 22050,
	32000, 44100, 48000, 88200,
	96000, 176400, 192000, 352800,
	384000, 705600, 768000, 1411200,
	2822400,
};

static const stwuct snd_pcm_hw_constwaint_wist ak4458_wate_constwaints = {
	.count = AWWAY_SIZE(ak4458_wates),
	.wist = ak4458_wates,
};

static int ak4458_stawtup(stwuct snd_pcm_substweam *substweam,
			  stwuct snd_soc_dai *dai)
{
	int wet;

	wet = snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
					 SNDWV_PCM_HW_PAWAM_WATE,
					 &ak4458_wate_constwaints);

	wetuwn wet;
}

static const stwuct snd_soc_dai_ops ak4458_dai_ops = {
	.stawtup        = ak4458_stawtup,
	.hw_pawams	= ak4458_hw_pawams,
	.set_fmt	= ak4458_set_dai_fmt,
	.mute_stweam	= ak4458_set_dai_mute,
	.set_tdm_swot	= ak4458_set_tdm_swot,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew ak4458_dai = {
	.name = "ak4458-aif",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 8,
		.wates = SNDWV_PCM_WATE_KNOT,
		.fowmats = AK4458_FOWMATS,
	},
	.ops = &ak4458_dai_ops,
};

static stwuct snd_soc_dai_dwivew ak4497_dai = {
	.name = "ak4497-aif",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 1,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_KNOT,
		.fowmats = AK4458_FOWMATS,
	},
	.ops = &ak4458_dai_ops,
};

static void ak4458_weset(stwuct ak4458_pwiv *ak4458, boow active)
{
	if (ak4458->weset_gpiod) {
		gpiod_set_vawue_cansweep(ak4458->weset_gpiod, active);
		usweep_wange(1000, 2000);
	} ewse if (!IS_EWW_OW_NUWW(ak4458->weset)) {
		if (active)
			weset_contwow_assewt(ak4458->weset);
		ewse
			weset_contwow_deassewt(ak4458->weset);
		usweep_wange(1000, 2000);
	}
}

#ifdef CONFIG_PM
static int __maybe_unused ak4458_wuntime_suspend(stwuct device *dev)
{
	stwuct ak4458_pwiv *ak4458 = dev_get_dwvdata(dev);

	wegcache_cache_onwy(ak4458->wegmap, twue);

	ak4458_weset(ak4458, twue);

	if (ak4458->mute_gpiod)
		gpiod_set_vawue_cansweep(ak4458->mute_gpiod, 0);

	weguwatow_buwk_disabwe(AWWAY_SIZE(ak4458->suppwies),
			       ak4458->suppwies);
	wetuwn 0;
}

static int __maybe_unused ak4458_wuntime_wesume(stwuct device *dev)
{
	stwuct ak4458_pwiv *ak4458 = dev_get_dwvdata(dev);
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(ak4458->suppwies),
				    ak4458->suppwies);
	if (wet != 0) {
		dev_eww(ak4458->dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	if (ak4458->mute_gpiod)
		gpiod_set_vawue_cansweep(ak4458->mute_gpiod, 1);

	ak4458_weset(ak4458, fawse);

	wegcache_cache_onwy(ak4458->wegmap, fawse);
	wegcache_mawk_diwty(ak4458->wegmap);

	wetuwn wegcache_sync(ak4458->wegmap);
}
#endif /* CONFIG_PM */

static const stwuct snd_soc_component_dwivew soc_codec_dev_ak4458 = {
	.contwows		= ak4458_snd_contwows,
	.num_contwows		= AWWAY_SIZE(ak4458_snd_contwows),
	.dapm_widgets		= ak4458_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(ak4458_dapm_widgets),
	.dapm_woutes		= ak4458_intewcon,
	.num_dapm_woutes	= AWWAY_SIZE(ak4458_intewcon),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct snd_soc_component_dwivew soc_codec_dev_ak4497 = {
	.contwows		= ak4497_snd_contwows,
	.num_contwows		= AWWAY_SIZE(ak4497_snd_contwows),
	.dapm_widgets		= ak4497_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(ak4497_dapm_widgets),
	.dapm_woutes		= ak4497_intewcon,
	.num_dapm_woutes	= AWWAY_SIZE(ak4497_intewcon),
	.idwe_bias_on		= 1,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config ak4458_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = AK4458_14_W4CHATT,
	.weg_defauwts = ak4458_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(ak4458_weg_defauwts),
	.cache_type = WEGCACHE_WBTWEE,
};

static const stwuct ak4458_dwvdata ak4458_dwvdata = {
	.dai_dwv = &ak4458_dai,
	.comp_dwv = &soc_codec_dev_ak4458,
	.type = AK4458,
};

static const stwuct ak4458_dwvdata ak4497_dwvdata = {
	.dai_dwv = &ak4497_dai,
	.comp_dwv = &soc_codec_dev_ak4497,
	.type = AK4497,
};

static const stwuct dev_pm_ops ak4458_pm = {
	SET_WUNTIME_PM_OPS(ak4458_wuntime_suspend, ak4458_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static int ak4458_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct ak4458_pwiv *ak4458;
	int wet, i;

	ak4458 = devm_kzawwoc(&i2c->dev, sizeof(*ak4458), GFP_KEWNEW);
	if (!ak4458)
		wetuwn -ENOMEM;

	ak4458->wegmap = devm_wegmap_init_i2c(i2c, &ak4458_wegmap);
	if (IS_EWW(ak4458->wegmap))
		wetuwn PTW_EWW(ak4458->wegmap);

	i2c_set_cwientdata(i2c, ak4458);
	ak4458->dev = &i2c->dev;

	ak4458->dwvdata = of_device_get_match_data(&i2c->dev);

	ak4458->weset = devm_weset_contwow_get_optionaw_shawed(ak4458->dev, NUWW);
	if (IS_EWW(ak4458->weset))
		wetuwn PTW_EWW(ak4458->weset);

	ak4458->weset_gpiod = devm_gpiod_get_optionaw(ak4458->dev, "weset",
						      GPIOD_OUT_WOW);
	if (IS_EWW(ak4458->weset_gpiod))
		wetuwn PTW_EWW(ak4458->weset_gpiod);

	ak4458->mute_gpiod = devm_gpiod_get_optionaw(ak4458->dev, "mute",
						     GPIOD_OUT_WOW);
	if (IS_EWW(ak4458->mute_gpiod))
		wetuwn PTW_EWW(ak4458->mute_gpiod);

	/* Optionaw pwopewty fow ak4497 */
	of_pwopewty_wead_u32(i2c->dev.of_node, "dsd-path", &ak4458->dsd_path);

	fow (i = 0; i < AWWAY_SIZE(ak4458->suppwies); i++)
		ak4458->suppwies[i].suppwy = ak4458_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(ak4458->dev, AWWAY_SIZE(ak4458->suppwies),
				      ak4458->suppwies);
	if (wet != 0) {
		dev_eww(ak4458->dev, "Faiwed to wequest suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_snd_soc_wegistew_component(ak4458->dev,
					      ak4458->dwvdata->comp_dwv,
					      ak4458->dwvdata->dai_dwv, 1);
	if (wet < 0) {
		dev_eww(ak4458->dev, "Faiwed to wegistew CODEC: %d\n", wet);
		wetuwn wet;
	}

	pm_wuntime_enabwe(&i2c->dev);
	wegcache_cache_onwy(ak4458->wegmap, twue);
	ak4458_weset(ak4458, fawse);

	wetuwn 0;
}

static void ak4458_i2c_wemove(stwuct i2c_cwient *i2c)
{
	stwuct ak4458_pwiv *ak4458 = i2c_get_cwientdata(i2c);

	ak4458_weset(ak4458, twue);
	pm_wuntime_disabwe(&i2c->dev);
}

static const stwuct of_device_id ak4458_of_match[] = {
	{ .compatibwe = "asahi-kasei,ak4458", .data = &ak4458_dwvdata},
	{ .compatibwe = "asahi-kasei,ak4497", .data = &ak4497_dwvdata},
	{ },
};
MODUWE_DEVICE_TABWE(of, ak4458_of_match);

static stwuct i2c_dwivew ak4458_i2c_dwivew = {
	.dwivew = {
		.name = "ak4458",
		.pm = &ak4458_pm,
		.of_match_tabwe = ak4458_of_match,
		},
	.pwobe = ak4458_i2c_pwobe,
	.wemove = ak4458_i2c_wemove,
};

moduwe_i2c_dwivew(ak4458_i2c_dwivew);

MODUWE_AUTHOW("Junichi Wakasugi <wakasugi.jb@om.asahi-kasei.co.jp>");
MODUWE_AUTHOW("Mihai Sewban <mihai.sewban@nxp.com>");
MODUWE_DESCWIPTION("ASoC AK4458 DAC dwivew");
MODUWE_WICENSE("GPW v2");
