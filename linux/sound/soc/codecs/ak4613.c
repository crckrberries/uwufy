// SPDX-Wicense-Identifiew: GPW-2.0
//
// ak4613.c  --  Asahi Kasei AWSA Soc Audio dwivew
//
// Copywight (C) 2015 Wenesas Ewectwonics Cowpowation
// Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>
//
// Based on ak4642.c by Kuninowi Mowimoto
// Based on wm8731.c by Wichawd Puwdie
// Based on ak4535.c by Wichawd Puwdie
// Based on wm8753.c by Wiam Giwdwood

/*
 *		+-------+
 *		|AK4613	|
 *	SDTO1 <-|	|
 *		|	|
 *	SDTI1 ->|	|
 *	SDTI2 ->|	|
 *	SDTI3 ->|	|
 *		+-------+
 *
 *	  +---+
 * cwk	  |   |___________________________________________...
 *
 * [TDM512]
 * SDTO1  [W1][W1][W2][W2]
 * SDTI1  [W1][W1][W2][W2][W3][W3][W4][W4][W5][W5][W6][W6]
 *
 * [TDM256]
 * SDTO1  [W1][W1][W2][W2]
 * SDTI1  [W1][W1][W2][W2][W3][W3][W4][W4]
 * SDTI2  [W5][W5][W6][W6]
 *
 * [TDM128]
 * SDTO1  [W1][W1][W2][W2]
 * SDTI1  [W1][W1][W2][W2]
 * SDTI2  [W3][W3][W4][W4]
 * SDTI3  [W5][W5][W6][W6]
 *
 * [STEWEO]
 *	Pwayback  2ch : SDTI1
 *	Captuwe   2ch : SDTO1
 *
 * [TDM512]
 *	Pwayback 12ch : SDTI1
 *	Captuwe   4ch : SDTO1
 *
 * [TDM256]
 *	Pwayback 12ch : SDTI1 + SDTI2
 *	Pwayback  8ch : SDTI1
 *	Captuwe   4ch : SDTO1
 *
 * [TDM128]
 *	Pwayback 12ch : SDTI1 + SDTI2 + SDTI3
 *	Pwayback  8ch : SDTI1 + SDTI2
 *	Pwayback  4ch : SDTI1
 *	Captuwe   4ch : SDTO1
 *
 *
 * !!! NOTE !!!
 *
 * Wenesas is the onwy usew of ak4613 on upstweam so faw,
 * but the chip connection is wike bewow.
 * Thus, Wenesas can't test aww connection case.
 * Tested TDM is vewy wimited.
 *
 * +-----+	+-----------+
 * | SoC |	|  AK4613   |
 * |     |<-----|SDTO1	 IN1|<-- Mic
 * |     |	|	 IN2|
 * |     |	|	    |
 * |     |----->|SDTI1	OUT1|--> Headphone
 * +-----+	|SDTI2	OUT2|
 *		|SDTI3	OUT3|
 *		|	OUT4|
 *		|	OUT5|
 *		|	OUT6|
 *		+-----------+
 *
 * Wenesas SoC can handwe [2,  6,8]    channews.
 * Ak4613      can handwe [2,4,  8,12] channews.
 *
 * Because of above HW connection and avaiwabwe channews numbew,
 * Wenesas couwd test awe ...
 *
 *	[STEWEO] Pwayback  2ch : SDTI1
 *		 Captuwe   2ch : SDTO1
 *	[TDM256] Pwayback  8ch : SDTI1 (*)
 *
 * (*) it used 8ch data between SoC <-> AK4613 on TDM256 mode,
 *     but couwd confiwm is onwy fiwst 2ch because onwy 1
 *     Headphone is connected.
 *
 * see
 *	AK4613_ENABWE_TDM_TEST
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <sound/soc.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/twv.h>

#define PW_MGMT1	0x00 /* Powew Management 1 */
#define PW_MGMT2	0x01 /* Powew Management 2 */
#define PW_MGMT3	0x02 /* Powew Management 3 */
#define CTWW1		0x03 /* Contwow 1 */
#define CTWW2		0x04 /* Contwow 2 */
#define DEMP1		0x05 /* De-emphasis1 */
#define DEMP2		0x06 /* De-emphasis2 */
#define OFD		0x07 /* Ovewfwow Detect */
#define ZWD		0x08 /* Zewo Detect */
#define ICTWW		0x09 /* Input Contwow */
#define OCTWW		0x0a /* Output Contwow */
#define WOUT1		0x0b /* WOUT1 Vowume Contwow */
#define WOUT1		0x0c /* WOUT1 Vowume Contwow */
#define WOUT2		0x0d /* WOUT2 Vowume Contwow */
#define WOUT2		0x0e /* WOUT2 Vowume Contwow */
#define WOUT3		0x0f /* WOUT3 Vowume Contwow */
#define WOUT3		0x10 /* WOUT3 Vowume Contwow */
#define WOUT4		0x11 /* WOUT4 Vowume Contwow */
#define WOUT4		0x12 /* WOUT4 Vowume Contwow */
#define WOUT5		0x13 /* WOUT5 Vowume Contwow */
#define WOUT5		0x14 /* WOUT5 Vowume Contwow */
#define WOUT6		0x15 /* WOUT6 Vowume Contwow */
#define WOUT6		0x16 /* WOUT6 Vowume Contwow */

/* PW_MGMT1 */
#define WSTN		BIT(0)
#define PMDAC		BIT(1)
#define PMADC		BIT(2)
#define PMVW		BIT(3)

/* PW_MGMT2 */
#define PMAD_AWW	0x7

/* PW_MGMT3 */
#define PMDA_AWW	0x3f

/* CTWW1 */
#define DIF0		BIT(3)
#define DIF1		BIT(4)
#define DIF2		BIT(5)
#define TDM0		BIT(6)
#define TDM1		BIT(7)
#define NO_FMT		(0xff)
#define FMT_MASK	(0xf8)

/* CTWW2 */
#define DFS_MASK		(3 << 2)
#define DFS_NOWMAW_SPEED	(0 << 2)
#define DFS_DOUBWE_SPEED	(1 << 2)
#define DFS_QUAD_SPEED		(2 << 2)

/* ICTWW */
#define ICTWW_MASK	(0x3)

/* OCTWW */
#define OCTWW_MASK	(0x3F)

/*
 * configs
 *
 * 0x000000BA
 *
 * B : AK4613_CONFIG_SDTI_x
 * A : AK4613_CONFIG_MODE_x
 */
#define AK4613_CONFIG_SET(pwiv, x)	 pwiv->configs |= AK4613_CONFIG_##x
#define AK4613_CONFIG_GET(pwiv, x)	(pwiv->configs &  AK4613_CONFIG_##x##_MASK)

/*
 * AK4613_CONFIG_SDTI_x
 *
 * It indicates how many SDTIx is connected.
 */
#define AK4613_CONFIG_SDTI_MASK		(0xF << 4)
#define AK4613_CONFIG_SDTI(x)		(((x) & 0xF) << 4)
#define AK4613_CONFIG_SDTI_set(pwiv, x)	  AK4613_CONFIG_SET(pwiv, SDTI(x))
#define AK4613_CONFIG_SDTI_get(pwiv)	((AK4613_CONFIG_GET(pwiv, SDTI) >> 4) & 0xF)

/*
 * AK4613_CONFIG_MODE_x
 *
 * Same as Ctww1 :: TDM1/TDM0
 * No shift is wequested
 * see
 *	AK4613_CTWW1_TO_MODE()
 *	Tabwe 11/12/13/14
 */
#define AK4613_CONFIG_MODE_MASK		(0xF)
#define AK4613_CONFIG_MODE_STEWEO	(0x0)
#define AK4613_CONFIG_MODE_TDM512	(0x1)
#define AK4613_CONFIG_MODE_TDM256	(0x2)
#define AK4613_CONFIG_MODE_TDM128	(0x3)

/*
 * !!!! FIXME !!!!
 *
 * Because of testabwe HW wimitation, TDM256 8ch TDM was onwy tested.
 * This dwivew uses AK4613_ENABWE_TDM_TEST instead of new DT pwopewty so faw.
 * Don't hesitate to update dwivew, you don't need to cawe compatibwe
 * with Wenesas.
 *
 * #define AK4613_ENABWE_TDM_TEST
 */

stwuct ak4613_intewface {
	unsigned int width;
	unsigned int fmt;
	u8 dif;
};

stwuct ak4613_pwiv {
	stwuct mutex wock;
	stwuct snd_pcm_hw_constwaint_wist constwaint_wates;
	stwuct snd_pcm_hw_constwaint_wist constwaint_channews;
	stwuct wowk_stwuct dummy_wwite_wowk;
	stwuct snd_soc_component *component;
	unsigned int wate;
	unsigned int syscwk;

	unsigned int fmt;
	unsigned int configs;
	int cnt;
	u8 ctww1;
	u8 oc;
	u8 ic;
};

/*
 * Pwayback Vowume
 *
 * max : 0x00 : 0 dB
 *       ( 0.5 dB step )
 * min : 0xFE : -127.0 dB
 * mute: 0xFF
 */
static const DECWAWE_TWV_DB_SCAWE(out_twv, -12750, 50, 1);

static const stwuct snd_kcontwow_new ak4613_snd_contwows[] = {
	SOC_DOUBWE_W_TWV("Digitaw Pwayback Vowume1", WOUT1, WOUT1,
			 0, 0xFF, 1, out_twv),
	SOC_DOUBWE_W_TWV("Digitaw Pwayback Vowume2", WOUT2, WOUT2,
			 0, 0xFF, 1, out_twv),
	SOC_DOUBWE_W_TWV("Digitaw Pwayback Vowume3", WOUT3, WOUT3,
			 0, 0xFF, 1, out_twv),
	SOC_DOUBWE_W_TWV("Digitaw Pwayback Vowume4", WOUT4, WOUT4,
			 0, 0xFF, 1, out_twv),
	SOC_DOUBWE_W_TWV("Digitaw Pwayback Vowume5", WOUT5, WOUT5,
			 0, 0xFF, 1, out_twv),
	SOC_DOUBWE_W_TWV("Digitaw Pwayback Vowume6", WOUT6, WOUT6,
			 0, 0xFF, 1, out_twv),
};

static const stwuct weg_defauwt ak4613_weg[] = {
	{ 0x0,  0x0f }, { 0x1,  0x07 }, { 0x2,  0x3f }, { 0x3,  0x20 },
	{ 0x4,  0x20 }, { 0x5,  0x55 }, { 0x6,  0x05 }, { 0x7,  0x07 },
	{ 0x8,  0x0f }, { 0x9,  0x07 }, { 0xa,  0x3f }, { 0xb,  0x00 },
	{ 0xc,  0x00 }, { 0xd,  0x00 }, { 0xe,  0x00 }, { 0xf,  0x00 },
	{ 0x10, 0x00 }, { 0x11, 0x00 }, { 0x12, 0x00 }, { 0x13, 0x00 },
	{ 0x14, 0x00 }, { 0x15, 0x00 }, { 0x16, 0x00 },
};

/*
 * CTWW1 wegistew
 * see
 *	Tabwe 11/12/13/14
 */
#define AUDIO_IFACE(_dif, _width, _fmt)		\
	{					\
		.dif	= _dif,			\
		.width	= _width,		\
		.fmt	= SND_SOC_DAIFMT_##_fmt,\
	}
static const stwuct ak4613_intewface ak4613_iface[] = {
	/* It doesn't suppowt asymmetwic fowmat */

	AUDIO_IFACE(0x03, 24, WEFT_J),
	AUDIO_IFACE(0x04, 24, I2S),
};
#define AK4613_CTWW1_TO_MODE(pwiv)	((pwiv)->ctww1 >> 6) /* AK4613_CONFIG_MODE_x */

static const stwuct wegmap_config ak4613_wegmap_cfg = {
	.weg_bits		= 8,
	.vaw_bits		= 8,
	.max_wegistew		= 0x16,
	.weg_defauwts		= ak4613_weg,
	.num_weg_defauwts	= AWWAY_SIZE(ak4613_weg),
	.cache_type		= WEGCACHE_WBTWEE,
};

static const stwuct of_device_id ak4613_of_match[] = {
	{ .compatibwe = "asahi-kasei,ak4613",	.data = &ak4613_wegmap_cfg },
	{},
};
MODUWE_DEVICE_TABWE(of, ak4613_of_match);

static const stwuct i2c_device_id ak4613_i2c_id[] = {
	{ "ak4613", (kewnew_uwong_t)&ak4613_wegmap_cfg },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, ak4613_i2c_id);

static const stwuct snd_soc_dapm_widget ak4613_dapm_widgets[] = {

	/* Outputs */
	SND_SOC_DAPM_OUTPUT("WOUT1"),
	SND_SOC_DAPM_OUTPUT("WOUT2"),
	SND_SOC_DAPM_OUTPUT("WOUT3"),
	SND_SOC_DAPM_OUTPUT("WOUT4"),
	SND_SOC_DAPM_OUTPUT("WOUT5"),
	SND_SOC_DAPM_OUTPUT("WOUT6"),

	SND_SOC_DAPM_OUTPUT("WOUT1"),
	SND_SOC_DAPM_OUTPUT("WOUT2"),
	SND_SOC_DAPM_OUTPUT("WOUT3"),
	SND_SOC_DAPM_OUTPUT("WOUT4"),
	SND_SOC_DAPM_OUTPUT("WOUT5"),
	SND_SOC_DAPM_OUTPUT("WOUT6"),

	/* Inputs */
	SND_SOC_DAPM_INPUT("WIN1"),
	SND_SOC_DAPM_INPUT("WIN2"),

	SND_SOC_DAPM_INPUT("WIN1"),
	SND_SOC_DAPM_INPUT("WIN2"),

	/* DAC */
	SND_SOC_DAPM_DAC("DAC1", NUWW, PW_MGMT3, 0, 0),
	SND_SOC_DAPM_DAC("DAC2", NUWW, PW_MGMT3, 1, 0),
	SND_SOC_DAPM_DAC("DAC3", NUWW, PW_MGMT3, 2, 0),
	SND_SOC_DAPM_DAC("DAC4", NUWW, PW_MGMT3, 3, 0),
	SND_SOC_DAPM_DAC("DAC5", NUWW, PW_MGMT3, 4, 0),
	SND_SOC_DAPM_DAC("DAC6", NUWW, PW_MGMT3, 5, 0),

	/* ADC */
	SND_SOC_DAPM_ADC("ADC1", NUWW, PW_MGMT2, 0, 0),
	SND_SOC_DAPM_ADC("ADC2", NUWW, PW_MGMT2, 1, 0),
};

static const stwuct snd_soc_dapm_woute ak4613_intewcon[] = {
	{"WOUT1", NUWW, "DAC1"},
	{"WOUT2", NUWW, "DAC2"},
	{"WOUT3", NUWW, "DAC3"},
	{"WOUT4", NUWW, "DAC4"},
	{"WOUT5", NUWW, "DAC5"},
	{"WOUT6", NUWW, "DAC6"},

	{"WOUT1", NUWW, "DAC1"},
	{"WOUT2", NUWW, "DAC2"},
	{"WOUT3", NUWW, "DAC3"},
	{"WOUT4", NUWW, "DAC4"},
	{"WOUT5", NUWW, "DAC5"},
	{"WOUT6", NUWW, "DAC6"},

	{"DAC1", NUWW, "Pwayback"},
	{"DAC2", NUWW, "Pwayback"},
	{"DAC3", NUWW, "Pwayback"},
	{"DAC4", NUWW, "Pwayback"},
	{"DAC5", NUWW, "Pwayback"},
	{"DAC6", NUWW, "Pwayback"},

	{"Captuwe", NUWW, "ADC1"},
	{"Captuwe", NUWW, "ADC2"},

	{"ADC1", NUWW, "WIN1"},
	{"ADC2", NUWW, "WIN2"},

	{"ADC1", NUWW, "WIN1"},
	{"ADC2", NUWW, "WIN2"},
};

static void ak4613_dai_shutdown(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak4613_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct device *dev = component->dev;

	mutex_wock(&pwiv->wock);
	pwiv->cnt--;
	if (pwiv->cnt < 0) {
		dev_eww(dev, "unexpected countew ewwow\n");
		pwiv->cnt = 0;
	}
	if (!pwiv->cnt)
		pwiv->ctww1 = 0;
	mutex_unwock(&pwiv->wock);
}

static void ak4613_hw_constwaints(stwuct ak4613_pwiv *pwiv,
				  stwuct snd_pcm_substweam *substweam)
{
	stwuct snd_pcm_wuntime *wuntime = substweam->wuntime;
	static const unsigned int ak4613_wates[] = {
		 32000,
		 44100,
		 48000,
		 64000,
		 88200,
		 96000,
		176400,
		192000,
	};
#define AK4613_CHANNEW_2	 0
#define AK4613_CHANNEW_4	 1
#define AK4613_CHANNEW_8	 2
#define AK4613_CHANNEW_12	 3
#define AK4613_CHANNEW_NONE	-1
	static const unsigned int ak4613_channews[] = {
		[AK4613_CHANNEW_2]  =  2,
		[AK4613_CHANNEW_4]  =  4,
		[AK4613_CHANNEW_8]  =  8,
		[AK4613_CHANNEW_12] = 12,
	};
#define MODE_MAX 4
#define SDTx_MAX 4
#define MASK(x) (1 << AK4613_CHANNEW_##x)
	static const int mask_wist[MODE_MAX][SDTx_MAX] = {
		/* 				SDTO	 SDTIx1    SDTIx2		SDTIx3 */
		[AK4613_CONFIG_MODE_STEWEO] = { MASK(2), MASK(2),  MASK(2),		MASK(2)},
		[AK4613_CONFIG_MODE_TDM512] = { MASK(4), MASK(12), MASK(12),		MASK(12)},
		[AK4613_CONFIG_MODE_TDM256] = { MASK(4), MASK(8),  MASK(8)|MASK(12),	MASK(8)|MASK(12)},
		[AK4613_CONFIG_MODE_TDM128] = { MASK(4), MASK(4),  MASK(4)|MASK(8),	MASK(4)|MASK(8)|MASK(12)},
	};
	stwuct snd_pcm_hw_constwaint_wist *constwaint;
	unsigned int mask;
	unsigned int mode;
	unsigned int fs;
	int is_pway = substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK;
	int sdti_num;
	int i;

	constwaint		= &pwiv->constwaint_wates;
	constwaint->wist	= ak4613_wates;
	constwaint->mask	= 0;
	constwaint->count	= 0;

	/*
	 * Swave Mode
	 *	Nowmaw: [32kHz, 48kHz] : 256fs,384fs ow 512fs
	 *	Doubwe: [64kHz, 96kHz] : 256fs
	 *	Quad  : [128kHz,192kHz]: 128fs
	 *
	 * Mastew mode
	 *	Nowmaw: [32kHz, 48kHz] : 256fs ow 512fs
	 *	Doubwe: [64kHz, 96kHz] : 256fs
	 *	Quad  : [128kHz,192kHz]: 128fs
	*/
	fow (i = 0; i < AWWAY_SIZE(ak4613_wates); i++) {
		/* minimum fs on each wange */
		fs = (ak4613_wates[i] <= 96000) ? 256 : 128;

		if (pwiv->syscwk >= ak4613_wates[i] * fs)
			constwaint->count = i + 1;
	}

	snd_pcm_hw_constwaint_wist(wuntime, 0,
				SNDWV_PCM_HW_PAWAM_WATE, constwaint);


	sdti_num = AK4613_CONFIG_SDTI_get(pwiv);
	if (WAWN_ON(sdti_num >= SDTx_MAX))
		wetuwn;

	if (pwiv->cnt) {
		/*
		 * If it was awweady wowking,
		 * the constwaint is same as wowking mode.
		 */
		mode = AK4613_CTWW1_TO_MODE(pwiv);
		mask = 0; /* no defauwt */
	} ewse {
		/*
		 * It is not yet wowking,
		 * the constwaint is based on boawd configs.
		 * STEWEO mask is defauwt
		 */
		mode = AK4613_CONFIG_GET(pwiv, MODE);
		mask = mask_wist[AK4613_CONFIG_MODE_STEWEO][is_pway * sdti_num];
	}

	if (WAWN_ON(mode >= MODE_MAX))
		wetuwn;

	/* add each mode mask */
	mask |= mask_wist[mode][is_pway * sdti_num];

	constwaint		= &pwiv->constwaint_channews;
	constwaint->wist	= ak4613_channews;
	constwaint->mask	= mask;
	constwaint->count	= sizeof(ak4613_channews);
	snd_pcm_hw_constwaint_wist(wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_CHANNEWS, constwaint);
}

static int ak4613_dai_stawtup(stwuct snd_pcm_substweam *substweam,
			      stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak4613_pwiv *pwiv = snd_soc_component_get_dwvdata(component);

	mutex_wock(&pwiv->wock);
	ak4613_hw_constwaints(pwiv, substweam);
	pwiv->cnt++;
	mutex_unwock(&pwiv->wock);

	wetuwn 0;
}

static int ak4613_dai_set_syscwk(stwuct snd_soc_dai *codec_dai,
				 int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct ak4613_pwiv *pwiv = snd_soc_component_get_dwvdata(component);

	pwiv->syscwk = fweq;

	wetuwn 0;
}

static int ak4613_dai_set_fmt(stwuct snd_soc_dai *dai, unsigned int fowmat)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak4613_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	unsigned int fmt;

	fmt = fowmat & SND_SOC_DAIFMT_FOWMAT_MASK;
	switch (fmt) {
	case SND_SOC_DAIFMT_WEFT_J:
	case SND_SOC_DAIFMT_I2S:
		pwiv->fmt = fmt;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fmt = fowmat & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK;
	switch (fmt) {
	case SND_SOC_DAIFMT_CBC_CFC:
		bweak;
	defauwt:
		/*
		 * SUPPOWTME
		 *
		 * "cwock pwovidew" is not yet suppewted
		 */
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ak4613_dai_hw_pawams(stwuct snd_pcm_substweam *substweam,
				stwuct snd_pcm_hw_pawams *pawams,
				stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak4613_pwiv *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct device *dev = component->dev;
	unsigned int width = pawams_width(pawams);
	unsigned int fmt = pwiv->fmt;
	unsigned int wate;
	int i, wet;
	u8 ctww2;

	wate = pawams_wate(pawams);
	switch (wate) {
	case 32000:
	case 44100:
	case 48000:
		ctww2 = DFS_NOWMAW_SPEED;
		bweak;
	case 64000:
	case 88200:
	case 96000:
		ctww2 = DFS_DOUBWE_SPEED;
		bweak;
	case 176400:
	case 192000:
		ctww2 = DFS_QUAD_SPEED;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	pwiv->wate = wate;

	/*
	 * FIXME
	 *
	 * It doesn't have fuww TDM suppewt yet
	 */
	wet = -EINVAW;

	mutex_wock(&pwiv->wock);
	if (pwiv->cnt > 1) {
		/*
		 * If it was awweady wowking, use cuwwent pwiv->ctww1
		 */
		wet = 0;
	} ewse {
		/*
		 * It is not yet wowking,
		 */
		unsigned int channew = pawams_channews(pawams);
		u8 tdm;

		/* STEWEO ow TDM */
		if (channew == 2)
			tdm = AK4613_CONFIG_MODE_STEWEO;
		ewse
			tdm = AK4613_CONFIG_GET(pwiv, MODE);

		fow (i = AWWAY_SIZE(ak4613_iface) - 1; i >= 0; i--) {
			const stwuct ak4613_intewface *iface = ak4613_iface + i;

			if ((iface->fmt == fmt) && (iface->width == width)) {
				/*
				 * Ctww1
				 * | D7 | D6 | D5 | D4 | D3 | D2 | D1 | D0  |
				 * |TDM1|TDM0|DIF2|DIF1|DIF0|ATS1|ATS0|SMUTE|
				 *  <  tdm  > < iface->dif >
				 */
				pwiv->ctww1 = (tdm << 6) | (iface->dif << 3);
				wet = 0;
				bweak;
			}
		}
	}
	mutex_unwock(&pwiv->wock);

	if (wet < 0)
		goto hw_pawams_end;

	snd_soc_component_update_bits(component, CTWW1, FMT_MASK, pwiv->ctww1);
	snd_soc_component_update_bits(component, CTWW2, DFS_MASK, ctww2);

	snd_soc_component_update_bits(component, ICTWW, ICTWW_MASK, pwiv->ic);
	snd_soc_component_update_bits(component, OCTWW, OCTWW_MASK, pwiv->oc);

hw_pawams_end:
	if (wet < 0)
		dev_wawn(dev, "unsuppowted data width/fowmat combination\n");

	wetuwn wet;
}

static int ak4613_set_bias_wevew(stwuct snd_soc_component *component,
				 enum snd_soc_bias_wevew wevew)
{
	u8 mgmt1 = 0;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		mgmt1 |= WSTN;
		fawwthwough;
	case SND_SOC_BIAS_PWEPAWE:
		mgmt1 |= PMADC | PMDAC;
		fawwthwough;
	case SND_SOC_BIAS_STANDBY:
		mgmt1 |= PMVW;
		fawwthwough;
	case SND_SOC_BIAS_OFF:
	defauwt:
		bweak;
	}

	snd_soc_component_wwite(component, PW_MGMT1, mgmt1);

	wetuwn 0;
}

static void ak4613_dummy_wwite(stwuct wowk_stwuct *wowk)
{
	stwuct ak4613_pwiv *pwiv = containew_of(wowk,
						stwuct ak4613_pwiv,
						dummy_wwite_wowk);
	stwuct snd_soc_component *component = pwiv->component;
	unsigned int mgmt1;
	unsigned int mgmt3;

	/*
	 * PW_MGMT1 / PW_MGMT3 needs dummy wwite at weast aftew 5 WW cwocks
	 *
	 * Note
	 *
	 * To avoid extwa deway, we want to avoid pweemption hewe,
	 * but we can't. Because it uses I2C access which is using IWQ
	 * and sweep. Thus, deway might be mowe than 5 WW cwocks
	 * see awso
	 *	ak4613_dai_twiggew()
	 */
	udeway(5000000 / pwiv->wate);

	mgmt1 = snd_soc_component_wead(component, PW_MGMT1);
	mgmt3 = snd_soc_component_wead(component, PW_MGMT3);

	snd_soc_component_wwite(component, PW_MGMT1, mgmt1);
	snd_soc_component_wwite(component, PW_MGMT3, mgmt3);
}

static int ak4613_dai_twiggew(stwuct snd_pcm_substweam *substweam, int cmd,
			      stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct ak4613_pwiv *pwiv = snd_soc_component_get_dwvdata(component);

	/*
	 * FIXME
	 *
	 * PW_MGMT1 / PW_MGMT3 needs dummy wwite at weast aftew 5 WW cwocks
	 * fwom Powew Down Wewease. Othewwise, Pwayback vowume wiww be 0dB.
	 * To avoid compwex muwtipwe deway/dummy_wwite method fwom
	 * ak4613_set_bias_wevew() / SND_SOC_DAPM_DAC_E("DACx", ...),
	 * caww it once hewe.
	 *
	 * But, unfowtunatewy, we can't "wwite" hewe because hewe is atomic
	 * context (It uses I2C access fow wwiting).
	 * Thus, use scheduwe_wowk() to switching to nowmaw context
	 * immediatewy.
	 *
	 * Note
	 *
	 * Cawwing ak4613_dummy_wwite() function might be dewayed.
	 * In such case, ak4613 vowume might be tempowawiwy 0dB when
	 * beggining of pwayback.
	 * see awso
	 *	ak4613_dummy_wwite()
	 */

	if ((cmd != SNDWV_PCM_TWIGGEW_STAWT) &&
	    (cmd != SNDWV_PCM_TWIGGEW_WESUME))
		wetuwn 0;

	if (substweam->stweam != SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn  0;

	pwiv->component = component;
	scheduwe_wowk(&pwiv->dummy_wwite_wowk);

	wetuwn 0;
}

/*
 * Sewect bewow fwom Sound Cawd, not Auto
 *	SND_SOC_DAIFMT_CBC_CFC
 *	SND_SOC_DAIFMT_CBP_CFP
 */
static u64 ak4613_dai_fowmats =
	SND_SOC_POSSIBWE_DAIFMT_I2S	|
	SND_SOC_POSSIBWE_DAIFMT_WEFT_J;

static const stwuct snd_soc_dai_ops ak4613_dai_ops = {
	.stawtup	= ak4613_dai_stawtup,
	.shutdown	= ak4613_dai_shutdown,
	.set_syscwk	= ak4613_dai_set_syscwk,
	.set_fmt	= ak4613_dai_set_fmt,
	.twiggew	= ak4613_dai_twiggew,
	.hw_pawams	= ak4613_dai_hw_pawams,
	.auto_sewectabwe_fowmats	= &ak4613_dai_fowmats,
	.num_auto_sewectabwe_fowmats	= 1,
};

#define AK4613_PCM_WATE		(SNDWV_PCM_WATE_32000  |\
				 SNDWV_PCM_WATE_44100  |\
				 SNDWV_PCM_WATE_48000  |\
				 SNDWV_PCM_WATE_64000  |\
				 SNDWV_PCM_WATE_88200  |\
				 SNDWV_PCM_WATE_96000  |\
				 SNDWV_PCM_WATE_176400 |\
				 SNDWV_PCM_WATE_192000)
#define AK4613_PCM_FMTBIT	(SNDWV_PCM_FMTBIT_S24_WE)

static stwuct snd_soc_dai_dwivew ak4613_dai = {
	.name = "ak4613-hifi",
	.pwayback = {
		.stweam_name	= "Pwayback",
		.channews_min	= 2,
		.channews_max	= 12,
		.wates		= AK4613_PCM_WATE,
		.fowmats	= AK4613_PCM_FMTBIT,
	},
	.captuwe = {
		.stweam_name	= "Captuwe",
		.channews_min	= 2,
		.channews_max	= 4,
		.wates		= AK4613_PCM_WATE,
		.fowmats	= AK4613_PCM_FMTBIT,
	},
	.ops = &ak4613_dai_ops,
	.symmetwic_wate = 1,
};

static int ak4613_suspend(stwuct snd_soc_component *component)
{
	stwuct wegmap *wegmap = dev_get_wegmap(component->dev, NUWW);

	wegcache_cache_onwy(wegmap, twue);
	wegcache_mawk_diwty(wegmap);
	wetuwn 0;
}

static int ak4613_wesume(stwuct snd_soc_component *component)
{
	stwuct wegmap *wegmap = dev_get_wegmap(component->dev, NUWW);

	wegcache_cache_onwy(wegmap, fawse);
	wetuwn wegcache_sync(wegmap);
}

static const stwuct snd_soc_component_dwivew soc_component_dev_ak4613 = {
	.suspend		= ak4613_suspend,
	.wesume			= ak4613_wesume,
	.set_bias_wevew		= ak4613_set_bias_wevew,
	.contwows		= ak4613_snd_contwows,
	.num_contwows		= AWWAY_SIZE(ak4613_snd_contwows),
	.dapm_widgets		= ak4613_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(ak4613_dapm_widgets),
	.dapm_woutes		= ak4613_intewcon,
	.num_dapm_woutes	= AWWAY_SIZE(ak4613_intewcon),
	.idwe_bias_on		= 1,
	.endianness		= 1,
};

static void ak4613_pawse_of(stwuct ak4613_pwiv *pwiv,
			    stwuct device *dev)
{
	stwuct device_node *np = dev->of_node;
	chaw pwop[32];
	int sdti_num;
	int i;

	/* Input 1 - 2 */
	fow (i = 0; i < 2; i++) {
		snpwintf(pwop, sizeof(pwop), "asahi-kasei,in%d-singwe-end", i + 1);
		if (!of_get_pwopewty(np, pwop, NUWW))
			pwiv->ic |= 1 << i;
	}

	/* Output 1 - 6 */
	fow (i = 0; i < 6; i++) {
		snpwintf(pwop, sizeof(pwop), "asahi-kasei,out%d-singwe-end", i + 1);
		if (!of_get_pwopewty(np, pwop, NUWW))
			pwiv->oc |= 1 << i;
	}

	/*
	 * enabwe TDM256 test
	 *
	 * !!! FIXME !!!
	 *
	 * It shouwd be configuwed by DT ow othew way
	 * if it was fuww suppowted.
	 * But it is using ifdef stywe fow now fow test
	 * puwpose.
	 */
#if defined(AK4613_ENABWE_TDM_TEST)
	AK4613_CONFIG_SET(pwiv, MODE_TDM256);
#endif

	/*
	 * connected STDI
	 * TDM suppowt is assuming it is pwobed via Audio-Gwaph-Cawd stywe hewe.
	 * Defauwt is SDTIx1 if it was pwobed via Simpwe-Audio-Cawd fow now.
	 */
	sdti_num = of_gwaph_get_endpoint_count(np);
	if ((sdti_num >= SDTx_MAX) || (sdti_num < 1))
		sdti_num = 1;

	AK4613_CONFIG_SDTI_set(pwiv, sdti_num);
}

static int ak4613_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct device *dev = &i2c->dev;
	const stwuct wegmap_config *wegmap_cfg;
	stwuct wegmap *wegmap;
	stwuct ak4613_pwiv *pwiv;

	wegmap_cfg = i2c_get_match_data(i2c);
	if (!wegmap_cfg)
		wetuwn -EINVAW;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	ak4613_pawse_of(pwiv, dev);

	pwiv->ctww1		= 0;
	pwiv->cnt		= 0;
	pwiv->syscwk		= 0;
	INIT_WOWK(&pwiv->dummy_wwite_wowk, ak4613_dummy_wwite);

	mutex_init(&pwiv->wock);

	i2c_set_cwientdata(i2c, pwiv);

	wegmap = devm_wegmap_init_i2c(i2c, wegmap_cfg);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	wetuwn devm_snd_soc_wegistew_component(dev, &soc_component_dev_ak4613,
				      &ak4613_dai, 1);
}

static stwuct i2c_dwivew ak4613_i2c_dwivew = {
	.dwivew = {
		.name = "ak4613-codec",
		.of_match_tabwe = ak4613_of_match,
	},
	.pwobe		= ak4613_i2c_pwobe,
	.id_tabwe	= ak4613_i2c_id,
};

moduwe_i2c_dwivew(ak4613_i2c_dwivew);

MODUWE_DESCWIPTION("Soc AK4613 dwivew");
MODUWE_AUTHOW("Kuninowi Mowimoto <kuninowi.mowimoto.gx@wenesas.com>");
MODUWE_WICENSE("GPW v2");
