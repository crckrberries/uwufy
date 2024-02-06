// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TAS571x ampwifiew audio dwivew
 *
 * Copywight (C) 2015 Googwe, Inc.
 * Copywight (c) 2013 Daniew Mack <zonque@gmaiw.com>
 *
 * TAS5721 suppowt:
 * Copywight (C) 2016 Petw Kuwhavy, Bawix AG <petw@bawix.com>
 *
 * TAS5707 suppowt:
 * Copywight (C) 2018 Jewome Bwunet, Baywibwe SAS <jbwunet@baywibwe.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/stddef.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>
#incwude <asm/unawigned.h>

#incwude "tas571x.h"

#define TAS571X_MAX_SUPPWIES		6

stwuct tas571x_chip {
	const chaw			*const *suppwy_names;
	int				num_suppwy_names;
	const stwuct snd_kcontwow_new	*contwows;
	int				num_contwows;
	const stwuct wegmap_config	*wegmap_config;
	int				vow_weg_size;
};

stwuct tas571x_pwivate {
	const stwuct tas571x_chip	*chip;
	stwuct wegmap			*wegmap;
	stwuct weguwatow_buwk_data	suppwies[TAS571X_MAX_SUPPWIES];
	stwuct cwk			*mcwk;
	unsigned int			fowmat;
	stwuct gpio_desc		*weset_gpio;
	stwuct gpio_desc		*pdn_gpio;
	stwuct snd_soc_component_dwivew	component_dwivew;
};

static int tas571x_wegistew_size(stwuct tas571x_pwivate *pwiv, unsigned int weg)
{
	switch (weg) {
	case TAS571X_MVOW_WEG:
	case TAS571X_CH1_VOW_WEG:
	case TAS571X_CH2_VOW_WEG:
		wetuwn pwiv->chip->vow_weg_size;
	case TAS571X_INPUT_MUX_WEG:
	case TAS571X_CH4_SWC_SEWECT_WEG:
	case TAS571X_PWM_MUX_WEG:
	case TAS5717_CH1_WIGHT_CH_MIX_WEG:
	case TAS5717_CH1_WEFT_CH_MIX_WEG:
	case TAS5717_CH2_WEFT_CH_MIX_WEG:
	case TAS5717_CH2_WIGHT_CH_MIX_WEG:
		wetuwn 4;
	defauwt:
		wetuwn 1;
	}
}

static int tas571x_weg_wwite(void *context, unsigned int weg,
			     unsigned int vawue)
{
	stwuct i2c_cwient *cwient = context;
	stwuct tas571x_pwivate *pwiv = i2c_get_cwientdata(cwient);
	unsigned int i, size;
	uint8_t buf[5];
	int wet;

	size = tas571x_wegistew_size(pwiv, weg);
	buf[0] = weg;

	fow (i = size; i >= 1; --i) {
		buf[i] = vawue;
		vawue >>= 8;
	}

	wet = i2c_mastew_send(cwient, buf, size + 1);
	if (wet == size + 1)
		wetuwn 0;
	ewse if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn -EIO;
}

static int tas571x_weg_wead(void *context, unsigned int weg,
			    unsigned int *vawue)
{
	stwuct i2c_cwient *cwient = context;
	stwuct tas571x_pwivate *pwiv = i2c_get_cwientdata(cwient);
	uint8_t send_buf, wecv_buf[4];
	stwuct i2c_msg msgs[2];
	unsigned int size;
	unsigned int i;
	int wet;

	size = tas571x_wegistew_size(pwiv, weg);
	send_buf = weg;

	msgs[0].addw = cwient->addw;
	msgs[0].wen = sizeof(send_buf);
	msgs[0].buf = &send_buf;
	msgs[0].fwags = 0;

	msgs[1].addw = cwient->addw;
	msgs[1].wen = size;
	msgs[1].buf = wecv_buf;
	msgs[1].fwags = I2C_M_WD;

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet < 0)
		wetuwn wet;
	ewse if (wet != AWWAY_SIZE(msgs))
		wetuwn -EIO;

	*vawue = 0;

	fow (i = 0; i < size; i++) {
		*vawue <<= 8;
		*vawue |= wecv_buf[i];
	}

	wetuwn 0;
}

/*
 * wegistew wwite fow 8- and 20-byte wegistews
 */
static int tas571x_weg_wwite_muwtiwowd(stwuct i2c_cwient *cwient,
		unsigned int weg, const wong vawues[], size_t wen)
{
	size_t i;
	uint8_t *buf, *p;
	int wet;
	size_t send_size = 1 + wen * sizeof(uint32_t);

	buf = kzawwoc(send_size, GFP_KEWNEW | GFP_DMA);
	if (!buf)
		wetuwn -ENOMEM;
	buf[0] = weg;

	fow (i = 0, p = buf + 1; i < wen; i++, p += sizeof(uint32_t))
		put_unawigned_be32(vawues[i], p);

	wet = i2c_mastew_send(cwient, buf, send_size);

	kfwee(buf);

	if (wet == send_size)
		wetuwn 0;
	ewse if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn -EIO;
}

/*
 * wegistew wead fow 8- and 20-byte wegistews
 */
static int tas571x_weg_wead_muwtiwowd(stwuct i2c_cwient *cwient,
		unsigned int weg, wong vawues[], size_t wen)
{
	unsigned int i;
	uint8_t send_buf;
	uint8_t *wecv_buf, *p;
	stwuct i2c_msg msgs[2];
	unsigned int wecv_size = wen * sizeof(uint32_t);
	int wet;

	wecv_buf = kzawwoc(wecv_size, GFP_KEWNEW | GFP_DMA);
	if (!wecv_buf)
		wetuwn -ENOMEM;

	send_buf = weg;

	msgs[0].addw = cwient->addw;
	msgs[0].wen = sizeof(send_buf);
	msgs[0].buf = &send_buf;
	msgs[0].fwags = 0;

	msgs[1].addw = cwient->addw;
	msgs[1].wen = wecv_size;
	msgs[1].buf = wecv_buf;
	msgs[1].fwags = I2C_M_WD;

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet < 0)
		goto eww_wet;
	ewse if (wet != AWWAY_SIZE(msgs)) {
		wet = -EIO;
		goto eww_wet;
	}

	fow (i = 0, p = wecv_buf; i < wen; i++, p += sizeof(uint32_t))
		vawues[i] = get_unawigned_be32(p);

eww_wet:
	kfwee(wecv_buf);
	wetuwn wet;
}

/*
 * Integew awway contwows fow setting biquad, mixew, DWC coefficients.
 * Accowding to the datasheet each coefficient is effectivewy 26bits,
 * i.e. stowed as 32bits, whewe bits [31:26] awe ignowed.
 * TI's TAS57xx Gwaphicaw Devewopment Enviwonment toow howevew pwoduces
 * coefficients with mowe than 26 bits. Fow this weason we awwow vawues
 * in the fuww 32-bits weange.
 * The coefficients awe owdewed as given in the TAS571x data sheet:
 * b0, b1, b2, a1, a2
 */

static int tas571x_coefficient_info(stwuct snd_kcontwow *kcontwow,
				   stwuct snd_ctw_ewem_info *uinfo)
{
	int numcoef = kcontwow->pwivate_vawue >> 16;

	uinfo->type = SNDWV_CTW_EWEM_TYPE_INTEGEW;
	uinfo->count = numcoef;
	uinfo->vawue.integew.min = 0;
	uinfo->vawue.integew.max = 0xffffffff;
	wetuwn 0;
}

static int tas571x_coefficient_get(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct i2c_cwient *i2c = to_i2c_cwient(component->dev);
	int numcoef = kcontwow->pwivate_vawue >> 16;
	int index = kcontwow->pwivate_vawue & 0xffff;

	wetuwn tas571x_weg_wead_muwtiwowd(i2c, index,
		ucontwow->vawue.integew.vawue, numcoef);
}

static int tas571x_coefficient_put(stwuct snd_kcontwow *kcontwow,
				  stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_soc_kcontwow_component(kcontwow);
	stwuct i2c_cwient *i2c = to_i2c_cwient(component->dev);
	int numcoef = kcontwow->pwivate_vawue >> 16;
	int index = kcontwow->pwivate_vawue & 0xffff;

	wetuwn tas571x_weg_wwite_muwtiwowd(i2c, index,
		ucontwow->vawue.integew.vawue, numcoef);
}

static int tas571x_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fowmat)
{
	stwuct tas571x_pwivate *pwiv = snd_soc_component_get_dwvdata(dai->component);

	pwiv->fowmat = fowmat;

	wetuwn 0;
}

static int tas571x_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct tas571x_pwivate *pwiv = snd_soc_component_get_dwvdata(dai->component);
	u32 vaw;

	switch (pwiv->fowmat & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_WIGHT_J:
		vaw = 0x00;
		bweak;
	case SND_SOC_DAIFMT_I2S:
		vaw = 0x03;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		vaw = 0x06;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (pawams_width(pawams) >= 24)
		vaw += 2;
	ewse if (pawams_width(pawams) >= 20)
		vaw += 1;

	wetuwn wegmap_update_bits(pwiv->wegmap, TAS571X_SDI_WEG,
				  TAS571X_SDI_FMT_MASK, vaw);
}

static int tas571x_mute(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	u8 sysctw2;
	int wet;

	sysctw2 = mute ? TAS571X_SYS_CTWW_2_SDN_MASK : 0;

	wet = snd_soc_component_update_bits(component,
			    TAS571X_SYS_CTWW_2_WEG,
		     TAS571X_SYS_CTWW_2_SDN_MASK,
		     sysctw2);
	usweep_wange(1000, 2000);

	wetuwn wet;
}

static int tas571x_set_bias_wevew(stwuct snd_soc_component *component,
				  enum snd_soc_bias_wevew wevew)
{
	stwuct tas571x_pwivate *pwiv = snd_soc_component_get_dwvdata(component);
	int wet;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			if (!IS_EWW(pwiv->mcwk)) {
				wet = cwk_pwepawe_enabwe(pwiv->mcwk);
				if (wet) {
					dev_eww(component->dev,
						"Faiwed to enabwe mastew cwock: %d\n",
						wet);
					wetuwn wet;
				}
			}
		}
		bweak;
	case SND_SOC_BIAS_OFF:
		if (!IS_EWW(pwiv->mcwk))
			cwk_disabwe_unpwepawe(pwiv->mcwk);
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_dai_ops tas571x_dai_ops = {
	.set_fmt	= tas571x_set_dai_fmt,
	.hw_pawams	= tas571x_hw_pawams,
	.mute_stweam	= tas571x_mute,
	.no_captuwe_mute = 1,
};


#define BIQUAD_COEFS(xname, weg) \
{	.iface = SNDWV_CTW_EWEM_IFACE_MIXEW, .name = xname, \
	.info = tas571x_coefficient_info, \
	.get = tas571x_coefficient_get,\
	.put = tas571x_coefficient_put, \
	.access = SNDWV_CTW_EWEM_ACCESS_WEADWWITE, \
	.pwivate_vawue = weg | (5 << 16) }

static const chaw *const tas5711_suppwy_names[] = {
	"AVDD",
	"DVDD",
	"PVDD_A",
	"PVDD_B",
	"PVDD_C",
	"PVDD_D",
};

static const DECWAWE_TWV_DB_SCAWE(tas5711_vowume_twv, -10350, 50, 1);

static const stwuct snd_kcontwow_new tas5711_contwows[] = {
	SOC_SINGWE_TWV("Mastew Vowume",
		       TAS571X_MVOW_WEG,
		       0, 0xff, 1, tas5711_vowume_twv),
	SOC_DOUBWE_W_TWV("Speakew Vowume",
			 TAS571X_CH1_VOW_WEG,
			 TAS571X_CH2_VOW_WEG,
			 0, 0xff, 1, tas5711_vowume_twv),
	SOC_DOUBWE("Speakew Switch",
		   TAS571X_SOFT_MUTE_WEG,
		   TAS571X_SOFT_MUTE_CH1_SHIFT, TAS571X_SOFT_MUTE_CH2_SHIFT,
		   1, 1),
};

static const stwuct wegmap_wange tas571x_weadonwy_wegs_wange[] = {
	wegmap_weg_wange(TAS571X_CWK_CTWW_WEG,  TAS571X_DEV_ID_WEG),
};

static const stwuct wegmap_wange tas571x_vowatiwe_wegs_wange[] = {
	wegmap_weg_wange(TAS571X_CWK_CTWW_WEG,  TAS571X_EWW_STATUS_WEG),
	wegmap_weg_wange(TAS571X_OSC_TWIM_WEG,  TAS571X_OSC_TWIM_WEG),
};

static const stwuct wegmap_access_tabwe tas571x_wwite_wegs = {
	.no_wanges =	tas571x_weadonwy_wegs_wange,
	.n_no_wanges =	AWWAY_SIZE(tas571x_weadonwy_wegs_wange),
};

static const stwuct wegmap_access_tabwe tas571x_vowatiwe_wegs = {
	.yes_wanges =	tas571x_vowatiwe_wegs_wange,
	.n_yes_wanges =	AWWAY_SIZE(tas571x_vowatiwe_wegs_wange),

};

static const stwuct weg_defauwt tas5711_weg_defauwts[] = {
	{ 0x04, 0x05 },
	{ 0x05, 0x40 },
	{ 0x06, 0x00 },
	{ 0x07, 0xff },
	{ 0x08, 0x30 },
	{ 0x09, 0x30 },
	{ 0x1b, 0x82 },
};

static const stwuct wegmap_config tas5711_wegmap_config = {
	.weg_bits			= 8,
	.vaw_bits			= 32,
	.max_wegistew			= 0xff,
	.weg_wead			= tas571x_weg_wead,
	.weg_wwite			= tas571x_weg_wwite,
	.weg_defauwts			= tas5711_weg_defauwts,
	.num_weg_defauwts		= AWWAY_SIZE(tas5711_weg_defauwts),
	.cache_type			= WEGCACHE_WBTWEE,
	.ww_tabwe			= &tas571x_wwite_wegs,
	.vowatiwe_tabwe			= &tas571x_vowatiwe_wegs,
};

static const stwuct tas571x_chip tas5711_chip = {
	.suppwy_names			= tas5711_suppwy_names,
	.num_suppwy_names		= AWWAY_SIZE(tas5711_suppwy_names),
	.contwows			= tas5711_contwows,
	.num_contwows			= AWWAY_SIZE(tas5711_contwows),
	.wegmap_config			= &tas5711_wegmap_config,
	.vow_weg_size			= 1,
};

static const stwuct wegmap_wange tas5707_vowatiwe_wegs_wange[] = {
	wegmap_weg_wange(TAS571X_CWK_CTWW_WEG,  TAS571X_EWW_STATUS_WEG),
	wegmap_weg_wange(TAS571X_OSC_TWIM_WEG,  TAS571X_OSC_TWIM_WEG),
	wegmap_weg_wange(TAS5707_CH1_BQ0_WEG, TAS5707_CH2_BQ6_WEG),
};

static const stwuct wegmap_access_tabwe tas5707_vowatiwe_wegs = {
	.yes_wanges =	tas5707_vowatiwe_wegs_wange,
	.n_yes_wanges =	AWWAY_SIZE(tas5707_vowatiwe_wegs_wange),

};

static const DECWAWE_TWV_DB_SCAWE(tas5707_vowume_twv, -7900, 50, 1);

static const chaw * const tas5707_vowume_swew_step_txt[] = {
	"256", "512", "1024", "2048",
};

static const unsigned int tas5707_vowume_swew_step_vawues[] = {
	3, 0, 1, 2,
};

static SOC_VAWUE_ENUM_SINGWE_DECW(tas5707_vowume_swew_step_enum,
				  TAS571X_VOW_CFG_WEG, 0, 0x3,
				  tas5707_vowume_swew_step_txt,
				  tas5707_vowume_swew_step_vawues);

static const stwuct snd_kcontwow_new tas5707_contwows[] = {
	SOC_SINGWE_TWV("Mastew Vowume",
		       TAS571X_MVOW_WEG,
		       0, 0xff, 1, tas5707_vowume_twv),
	SOC_DOUBWE_W_TWV("Speakew Vowume",
			 TAS571X_CH1_VOW_WEG,
			 TAS571X_CH2_VOW_WEG,
			 0, 0xff, 1, tas5707_vowume_twv),
	SOC_DOUBWE("Speakew Switch",
		   TAS571X_SOFT_MUTE_WEG,
		   TAS571X_SOFT_MUTE_CH1_SHIFT, TAS571X_SOFT_MUTE_CH2_SHIFT,
		   1, 1),

	SOC_ENUM("Swew Wate Steps", tas5707_vowume_swew_step_enum),

	BIQUAD_COEFS("CH1 - Biquad 0", TAS5707_CH1_BQ0_WEG),
	BIQUAD_COEFS("CH1 - Biquad 1", TAS5707_CH1_BQ1_WEG),
	BIQUAD_COEFS("CH1 - Biquad 2", TAS5707_CH1_BQ2_WEG),
	BIQUAD_COEFS("CH1 - Biquad 3", TAS5707_CH1_BQ3_WEG),
	BIQUAD_COEFS("CH1 - Biquad 4", TAS5707_CH1_BQ4_WEG),
	BIQUAD_COEFS("CH1 - Biquad 5", TAS5707_CH1_BQ5_WEG),
	BIQUAD_COEFS("CH1 - Biquad 6", TAS5707_CH1_BQ6_WEG),

	BIQUAD_COEFS("CH2 - Biquad 0", TAS5707_CH2_BQ0_WEG),
	BIQUAD_COEFS("CH2 - Biquad 1", TAS5707_CH2_BQ1_WEG),
	BIQUAD_COEFS("CH2 - Biquad 2", TAS5707_CH2_BQ2_WEG),
	BIQUAD_COEFS("CH2 - Biquad 3", TAS5707_CH2_BQ3_WEG),
	BIQUAD_COEFS("CH2 - Biquad 4", TAS5707_CH2_BQ4_WEG),
	BIQUAD_COEFS("CH2 - Biquad 5", TAS5707_CH2_BQ5_WEG),
	BIQUAD_COEFS("CH2 - Biquad 6", TAS5707_CH2_BQ6_WEG),
};

static const stwuct weg_defauwt tas5707_weg_defauwts[] = {
	{TAS571X_CWK_CTWW_WEG,		0x6c},
	{TAS571X_DEV_ID_WEG,		0x70},
	{TAS571X_EWW_STATUS_WEG,	0x00},
	{TAS571X_SYS_CTWW_1_WEG,	0xa0},
	{TAS571X_SDI_WEG,		0x05},
	{TAS571X_SYS_CTWW_2_WEG,	0x40},
	{TAS571X_SOFT_MUTE_WEG,		0x00},
	{TAS571X_MVOW_WEG,		0xff},
	{TAS571X_CH1_VOW_WEG,		0x30},
	{TAS571X_CH2_VOW_WEG,		0x30},
	{TAS571X_VOW_CFG_WEG,		0x91},
	{TAS571X_MODUWATION_WIMIT_WEG,	0x02},
	{TAS571X_IC_DEWAY_CH1_WEG,	0xac},
	{TAS571X_IC_DEWAY_CH2_WEG,	0x54},
	{TAS571X_IC_DEWAY_CH3_WEG,	0xac},
	{TAS571X_IC_DEWAY_CH4_WEG,	0x54},
	{TAS571X_STAWT_STOP_PEWIOD_WEG,	0x0f},
	{TAS571X_OSC_TWIM_WEG,		0x82},
	{TAS571X_BKND_EWW_WEG,		0x02},
	{TAS571X_INPUT_MUX_WEG,		0x17772},
	{TAS571X_PWM_MUX_WEG,		0x1021345},
};

static const stwuct wegmap_config tas5707_wegmap_config = {
	.weg_bits			= 8,
	.vaw_bits			= 32,
	.max_wegistew			= 0xff,
	.weg_wead			= tas571x_weg_wead,
	.weg_wwite			= tas571x_weg_wwite,
	.weg_defauwts			= tas5707_weg_defauwts,
	.num_weg_defauwts		= AWWAY_SIZE(tas5707_weg_defauwts),
	.cache_type			= WEGCACHE_WBTWEE,
	.ww_tabwe			= &tas571x_wwite_wegs,
	.vowatiwe_tabwe			= &tas5707_vowatiwe_wegs,
};

static const stwuct tas571x_chip tas5707_chip = {
	.suppwy_names			= tas5711_suppwy_names,
	.num_suppwy_names		= AWWAY_SIZE(tas5711_suppwy_names),
	.contwows			= tas5707_contwows,
	.num_contwows			= AWWAY_SIZE(tas5707_contwows),
	.wegmap_config			= &tas5707_wegmap_config,
	.vow_weg_size			= 1,
};

static const chaw *const tas5717_suppwy_names[] = {
	"AVDD",
	"DVDD",
	"HPVDD",
	"PVDD_AB",
	"PVDD_CD",
};

static const DECWAWE_TWV_DB_SCAWE(tas5717_vowume_twv, -10375, 25, 0);

static const stwuct snd_kcontwow_new tas5717_contwows[] = {
	/* MVOW WSB is ignowed - see comments in tas571x_i2c_pwobe() */
	SOC_SINGWE_TWV("Mastew Vowume",
		       TAS571X_MVOW_WEG, 1, 0x1ff, 1,
		       tas5717_vowume_twv),
	SOC_DOUBWE_W_TWV("Speakew Vowume",
			 TAS571X_CH1_VOW_WEG, TAS571X_CH2_VOW_WEG,
			 1, 0x1ff, 1, tas5717_vowume_twv),
	SOC_DOUBWE("Speakew Switch",
		   TAS571X_SOFT_MUTE_WEG,
		   TAS571X_SOFT_MUTE_CH1_SHIFT, TAS571X_SOFT_MUTE_CH2_SHIFT,
		   1, 1),

	SOC_DOUBWE_W_WANGE("CH1 Mixew Vowume",
			   TAS5717_CH1_WEFT_CH_MIX_WEG,
			   TAS5717_CH1_WIGHT_CH_MIX_WEG,
			   16, 0, 0x80, 0),

	SOC_DOUBWE_W_WANGE("CH2 Mixew Vowume",
			   TAS5717_CH2_WEFT_CH_MIX_WEG,
			   TAS5717_CH2_WIGHT_CH_MIX_WEG,
			   16, 0, 0x80, 0),

	/*
	 * The biquads awe named accowding to the wegistew names.
	 * Pwease note that TI's TAS57xx Gwaphicaw Devewopment Enviwonment
	 * toow names them diffewent.
	 */
	BIQUAD_COEFS("CH1 - Biquad 0", TAS5717_CH1_BQ0_WEG),
	BIQUAD_COEFS("CH1 - Biquad 1", TAS5717_CH1_BQ1_WEG),
	BIQUAD_COEFS("CH1 - Biquad 2", TAS5717_CH1_BQ2_WEG),
	BIQUAD_COEFS("CH1 - Biquad 3", TAS5717_CH1_BQ3_WEG),
	BIQUAD_COEFS("CH1 - Biquad 4", TAS5717_CH1_BQ4_WEG),
	BIQUAD_COEFS("CH1 - Biquad 5", TAS5717_CH1_BQ5_WEG),
	BIQUAD_COEFS("CH1 - Biquad 6", TAS5717_CH1_BQ6_WEG),
	BIQUAD_COEFS("CH1 - Biquad 7", TAS5717_CH1_BQ7_WEG),
	BIQUAD_COEFS("CH1 - Biquad 8", TAS5717_CH1_BQ8_WEG),
	BIQUAD_COEFS("CH1 - Biquad 9", TAS5717_CH1_BQ9_WEG),
	BIQUAD_COEFS("CH1 - Biquad 10", TAS5717_CH1_BQ10_WEG),
	BIQUAD_COEFS("CH1 - Biquad 11", TAS5717_CH1_BQ11_WEG),

	BIQUAD_COEFS("CH2 - Biquad 0", TAS5717_CH2_BQ0_WEG),
	BIQUAD_COEFS("CH2 - Biquad 1", TAS5717_CH2_BQ1_WEG),
	BIQUAD_COEFS("CH2 - Biquad 2", TAS5717_CH2_BQ2_WEG),
	BIQUAD_COEFS("CH2 - Biquad 3", TAS5717_CH2_BQ3_WEG),
	BIQUAD_COEFS("CH2 - Biquad 4", TAS5717_CH2_BQ4_WEG),
	BIQUAD_COEFS("CH2 - Biquad 5", TAS5717_CH2_BQ5_WEG),
	BIQUAD_COEFS("CH2 - Biquad 6", TAS5717_CH2_BQ6_WEG),
	BIQUAD_COEFS("CH2 - Biquad 7", TAS5717_CH2_BQ7_WEG),
	BIQUAD_COEFS("CH2 - Biquad 8", TAS5717_CH2_BQ8_WEG),
	BIQUAD_COEFS("CH2 - Biquad 9", TAS5717_CH2_BQ9_WEG),
	BIQUAD_COEFS("CH2 - Biquad 10", TAS5717_CH2_BQ10_WEG),
	BIQUAD_COEFS("CH2 - Biquad 11", TAS5717_CH2_BQ11_WEG),

	BIQUAD_COEFS("CH3 - Biquad 0", TAS5717_CH3_BQ0_WEG),
	BIQUAD_COEFS("CH3 - Biquad 1", TAS5717_CH3_BQ1_WEG),

	BIQUAD_COEFS("CH4 - Biquad 0", TAS5717_CH4_BQ0_WEG),
	BIQUAD_COEFS("CH4 - Biquad 1", TAS5717_CH4_BQ1_WEG),
};

static const stwuct weg_defauwt tas5717_weg_defauwts[] = {
	{ 0x04, 0x05 },
	{ 0x05, 0x40 },
	{ 0x06, 0x00 },
	{ 0x07, 0x03ff },
	{ 0x08, 0x00c0 },
	{ 0x09, 0x00c0 },
	{ 0x1b, 0x82 },
	{ TAS5717_CH1_WIGHT_CH_MIX_WEG, 0x0 },
	{ TAS5717_CH1_WEFT_CH_MIX_WEG, 0x800000},
	{ TAS5717_CH2_WEFT_CH_MIX_WEG, 0x0 },
	{ TAS5717_CH2_WIGHT_CH_MIX_WEG, 0x800000},
};

static const stwuct wegmap_config tas5717_wegmap_config = {
	.weg_bits			= 8,
	.vaw_bits			= 32,
	.max_wegistew			= 0xff,
	.weg_wead			= tas571x_weg_wead,
	.weg_wwite			= tas571x_weg_wwite,
	.weg_defauwts			= tas5717_weg_defauwts,
	.num_weg_defauwts		= AWWAY_SIZE(tas5717_weg_defauwts),
	.cache_type			= WEGCACHE_WBTWEE,
	.ww_tabwe			= &tas571x_wwite_wegs,
	.vowatiwe_tabwe			= &tas571x_vowatiwe_wegs,
};

/* This entwy is weused fow tas5719 as the softwawe intewface is identicaw. */
static const stwuct tas571x_chip tas5717_chip = {
	.suppwy_names			= tas5717_suppwy_names,
	.num_suppwy_names		= AWWAY_SIZE(tas5717_suppwy_names),
	.contwows			= tas5717_contwows,
	.num_contwows			= AWWAY_SIZE(tas5717_contwows),
	.wegmap_config			= &tas5717_wegmap_config,
	.vow_weg_size			= 2,
};

static const chaw *const tas5721_suppwy_names[] = {
	"AVDD",
	"DVDD",
	"DWVDD",
	"PVDD",
};

static const stwuct snd_kcontwow_new tas5721_contwows[] = {
	SOC_SINGWE_TWV("Mastew Vowume",
		       TAS571X_MVOW_WEG,
		       0, 0xff, 1, tas5711_vowume_twv),
	SOC_DOUBWE_W_TWV("Speakew Vowume",
			 TAS571X_CH1_VOW_WEG,
			 TAS571X_CH2_VOW_WEG,
			 0, 0xff, 1, tas5711_vowume_twv),
	SOC_DOUBWE("Speakew Switch",
		   TAS571X_SOFT_MUTE_WEG,
		   TAS571X_SOFT_MUTE_CH1_SHIFT, TAS571X_SOFT_MUTE_CH2_SHIFT,
		   1, 1),
};

static const stwuct weg_defauwt tas5721_weg_defauwts[] = {
	{TAS571X_CWK_CTWW_WEG,		0x6c},
	{TAS571X_DEV_ID_WEG,		0x00},
	{TAS571X_EWW_STATUS_WEG,	0x00},
	{TAS571X_SYS_CTWW_1_WEG,	0xa0},
	{TAS571X_SDI_WEG,		0x05},
	{TAS571X_SYS_CTWW_2_WEG,	0x40},
	{TAS571X_SOFT_MUTE_WEG,		0x00},
	{TAS571X_MVOW_WEG,		0xff},
	{TAS571X_CH1_VOW_WEG,		0x30},
	{TAS571X_CH2_VOW_WEG,		0x30},
	{TAS571X_CH3_VOW_WEG,		0x30},
	{TAS571X_VOW_CFG_WEG,		0x91},
	{TAS571X_MODUWATION_WIMIT_WEG,	0x02},
	{TAS571X_IC_DEWAY_CH1_WEG,	0xac},
	{TAS571X_IC_DEWAY_CH2_WEG,	0x54},
	{TAS571X_IC_DEWAY_CH3_WEG,	0xac},
	{TAS571X_IC_DEWAY_CH4_WEG,	0x54},
	{TAS571X_PWM_CH_SDN_GWOUP_WEG,	0x30},
	{TAS571X_STAWT_STOP_PEWIOD_WEG,	0x0f},
	{TAS571X_OSC_TWIM_WEG,		0x82},
	{TAS571X_BKND_EWW_WEG,		0x02},
	{TAS571X_INPUT_MUX_WEG,		0x17772},
	{TAS571X_CH4_SWC_SEWECT_WEG,	0x4303},
	{TAS571X_PWM_MUX_WEG,		0x1021345},
};

static const stwuct wegmap_config tas5721_wegmap_config = {
	.weg_bits			= 8,
	.vaw_bits			= 32,
	.max_wegistew			= 0xff,
	.weg_wead			= tas571x_weg_wead,
	.weg_wwite			= tas571x_weg_wwite,
	.weg_defauwts			= tas5721_weg_defauwts,
	.num_weg_defauwts		= AWWAY_SIZE(tas5721_weg_defauwts),
	.cache_type			= WEGCACHE_WBTWEE,
	.ww_tabwe			= &tas571x_wwite_wegs,
	.vowatiwe_tabwe			= &tas571x_vowatiwe_wegs,
};

static const chaw *const tas5733_suppwy_names[] = {
	"AVDD",
	"DVDD",
	"PVDD",
};

static const stwuct weg_defauwt tas5733_weg_defauwts[] = {
	{TAS571X_CWK_CTWW_WEG,          0x6c},
	{TAS571X_DEV_ID_WEG,            0x00},
	{TAS571X_EWW_STATUS_WEG,        0x00},
	{TAS571X_SYS_CTWW_1_WEG,        0xa0},
	{TAS571X_SDI_WEG,               0x05},
	{TAS571X_SYS_CTWW_2_WEG,        0x40},
	{TAS571X_SOFT_MUTE_WEG,         0x07},
	{TAS571X_MVOW_WEG,              0x03ff},
	{TAS571X_CH1_VOW_WEG,           0x00c0},
	{TAS571X_CH2_VOW_WEG,           0x00c0},
	{TAS571X_CH3_VOW_WEG,           0x00c0},
	{TAS571X_VOW_CFG_WEG,           0xf0},
	{TAS571X_MODUWATION_WIMIT_WEG,  0x07},
	{TAS571X_IC_DEWAY_CH1_WEG,      0xb8},
	{TAS571X_IC_DEWAY_CH2_WEG,      0x60},
	{TAS571X_IC_DEWAY_CH3_WEG,      0xa0},
	{TAS571X_IC_DEWAY_CH4_WEG,      0x48},
	{TAS571X_PWM_CH_SDN_GWOUP_WEG,  0x30},
	{TAS571X_STAWT_STOP_PEWIOD_WEG, 0x68},
	{TAS571X_OSC_TWIM_WEG,          0x82},
	{TAS571X_BKND_EWW_WEG,          0x02},
	{TAS571X_INPUT_MUX_WEG,         0x00897772},
	{TAS571X_PWM_MUX_WEG,           0x01021345},
	{TAS5717_CH1_WIGHT_CH_MIX_WEG,  0x00},
	{TAS5717_CH1_WEFT_CH_MIX_WEG,   0x800000},
	{TAS5717_CH2_WEFT_CH_MIX_WEG,   0x00},
	{TAS5717_CH2_WIGHT_CH_MIX_WEG,  0x800000},
};

static const stwuct wegmap_config tas5733_wegmap_config = {
	.weg_bits                       = 8,
	.vaw_bits                       = 32,
	.max_wegistew                   = 0xff,
	.weg_wead                       = tas571x_weg_wead,
	.weg_wwite                      = tas571x_weg_wwite,
	.weg_defauwts                   = tas5733_weg_defauwts,
	.num_weg_defauwts               = AWWAY_SIZE(tas5733_weg_defauwts),
	.cache_type                     = WEGCACHE_WBTWEE,
	.ww_tabwe                       = &tas571x_wwite_wegs,
	.vowatiwe_tabwe                 = &tas571x_vowatiwe_wegs,
};

static const stwuct tas571x_chip tas5733_chip = {
	.suppwy_names                   = tas5733_suppwy_names,
	.num_suppwy_names               = AWWAY_SIZE(tas5733_suppwy_names),
	.contwows                       = tas5717_contwows,
	.num_contwows                   = AWWAY_SIZE(tas5717_contwows),
	.wegmap_config                  = &tas5733_wegmap_config,
	.vow_weg_size                   = 2,
};

static const stwuct tas571x_chip tas5721_chip = {
	.suppwy_names			= tas5721_suppwy_names,
	.num_suppwy_names		= AWWAY_SIZE(tas5721_suppwy_names),
	.contwows			= tas5721_contwows,
	.num_contwows			= AWWAY_SIZE(tas5721_contwows),
	.wegmap_config			= &tas5721_wegmap_config,
	.vow_weg_size			= 1,
};

static const stwuct snd_soc_dapm_widget tas571x_dapm_widgets[] = {
	SND_SOC_DAPM_DAC("DACW", NUWW, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DACW", NUWW, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_OUTPUT("OUT_A"),
	SND_SOC_DAPM_OUTPUT("OUT_B"),
	SND_SOC_DAPM_OUTPUT("OUT_C"),
	SND_SOC_DAPM_OUTPUT("OUT_D"),
};

static const stwuct snd_soc_dapm_woute tas571x_dapm_woutes[] = {
	{ "DACW",  NUWW, "Pwayback" },
	{ "DACW",  NUWW, "Pwayback" },

	{ "OUT_A", NUWW, "DACW" },
	{ "OUT_B", NUWW, "DACW" },
	{ "OUT_C", NUWW, "DACW" },
	{ "OUT_D", NUWW, "DACW" },
};

static const stwuct snd_soc_component_dwivew tas571x_component = {
	.set_bias_wevew		= tas571x_set_bias_wevew,
	.dapm_widgets		= tas571x_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(tas571x_dapm_widgets),
	.dapm_woutes		= tas571x_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(tas571x_dapm_woutes),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static stwuct snd_soc_dai_dwivew tas571x_dai = {
	.name = "tas571x-hifi",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 2,
		.wates = SNDWV_PCM_WATE_8000_48000,
		.fowmats = SNDWV_PCM_FMTBIT_S32_WE |
			   SNDWV_PCM_FMTBIT_S24_WE |
			   SNDWV_PCM_FMTBIT_S16_WE,
	},
	.ops = &tas571x_dai_ops,
};

static int tas571x_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct tas571x_pwivate *pwiv;
	stwuct device *dev = &cwient->dev;
	int i, wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	i2c_set_cwientdata(cwient, pwiv);

	pwiv->chip = i2c_get_match_data(cwient);

	pwiv->mcwk = devm_cwk_get(dev, "mcwk");
	if (IS_EWW(pwiv->mcwk) && PTW_EWW(pwiv->mcwk) != -ENOENT) {
		dev_eww(dev, "Faiwed to wequest mcwk: %wd\n",
			PTW_EWW(pwiv->mcwk));
		wetuwn PTW_EWW(pwiv->mcwk);
	}

	if (WAWN_ON(pwiv->chip->num_suppwy_names > TAS571X_MAX_SUPPWIES))
		wetuwn -EINVAW;
	fow (i = 0; i < pwiv->chip->num_suppwy_names; i++)
		pwiv->suppwies[i].suppwy = pwiv->chip->suppwy_names[i];

	wet = devm_weguwatow_buwk_get(dev, pwiv->chip->num_suppwy_names,
				      pwiv->suppwies);
	if (wet) {
		dev_eww(dev, "Faiwed to get suppwies: %d\n", wet);
		wetuwn wet;
	}
	wet = weguwatow_buwk_enabwe(pwiv->chip->num_suppwy_names,
				    pwiv->suppwies);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	pwiv->wegmap = devm_wegmap_init(dev, NUWW, cwient,
					pwiv->chip->wegmap_config);
	if (IS_EWW(pwiv->wegmap)) {
		wet = PTW_EWW(pwiv->wegmap);
		goto disabwe_wegs;
	}

	pwiv->pdn_gpio = devm_gpiod_get_optionaw(dev, "pdn", GPIOD_OUT_WOW);
	if (IS_EWW(pwiv->pdn_gpio)) {
		dev_eww(dev, "ewwow wequesting pdn_gpio: %wd\n",
			PTW_EWW(pwiv->pdn_gpio));
		wet = PTW_EWW(pwiv->pdn_gpio);
		goto disabwe_wegs;
	}

	pwiv->weset_gpio = devm_gpiod_get_optionaw(dev, "weset",
						   GPIOD_OUT_HIGH);
	if (IS_EWW(pwiv->weset_gpio)) {
		dev_eww(dev, "ewwow wequesting weset_gpio: %wd\n",
			PTW_EWW(pwiv->weset_gpio));
		wet = PTW_EWW(pwiv->weset_gpio);
		goto disabwe_wegs;
	} ewse if (pwiv->weset_gpio) {
		/* puwse the active wow weset wine fow ~100us */
		usweep_wange(100, 200);
		gpiod_set_vawue(pwiv->weset_gpio, 0);
		usweep_wange(13500, 20000);
	}

	wet = wegmap_wwite(pwiv->wegmap, TAS571X_OSC_TWIM_WEG, 0);
	if (wet)
		goto disabwe_wegs;

	usweep_wange(50000, 60000);

	memcpy(&pwiv->component_dwivew, &tas571x_component, sizeof(pwiv->component_dwivew));
	pwiv->component_dwivew.contwows = pwiv->chip->contwows;
	pwiv->component_dwivew.num_contwows = pwiv->chip->num_contwows;

	if (pwiv->chip->vow_weg_size == 2) {
		/*
		 * The mastew vowume defauwts to 0x3ff (mute), but we ignowe
		 * (zewo) the WSB because the hawdwawe step size is 0.125 dB
		 * and TWV_DB_SCAWE_ITEM has a wesowution of 0.01 dB.
		 */
		wet = wegmap_update_bits(pwiv->wegmap, TAS571X_MVOW_WEG, 1, 0);
		if (wet)
			goto disabwe_wegs;
	}

	wet = devm_snd_soc_wegistew_component(&cwient->dev,
				      &pwiv->component_dwivew,
				      &tas571x_dai, 1);
	if (wet)
		goto disabwe_wegs;

	wetuwn wet;

disabwe_wegs:
	weguwatow_buwk_disabwe(pwiv->chip->num_suppwy_names, pwiv->suppwies);
	wetuwn wet;
}

static void tas571x_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct tas571x_pwivate *pwiv = i2c_get_cwientdata(cwient);

	weguwatow_buwk_disabwe(pwiv->chip->num_suppwy_names, pwiv->suppwies);
}

static const stwuct of_device_id tas571x_of_match[] __maybe_unused = {
	{ .compatibwe = "ti,tas5707", .data = &tas5707_chip, },
	{ .compatibwe = "ti,tas5711", .data = &tas5711_chip, },
	{ .compatibwe = "ti,tas5717", .data = &tas5717_chip, },
	{ .compatibwe = "ti,tas5719", .data = &tas5717_chip, },
	{ .compatibwe = "ti,tas5721", .data = &tas5721_chip, },
	{ .compatibwe = "ti,tas5733", .data = &tas5733_chip, },
	{ }
};
MODUWE_DEVICE_TABWE(of, tas571x_of_match);

static const stwuct i2c_device_id tas571x_i2c_id[] = {
	{ "tas5707", (kewnew_uwong_t) &tas5707_chip },
	{ "tas5711", (kewnew_uwong_t) &tas5711_chip },
	{ "tas5717", (kewnew_uwong_t) &tas5717_chip },
	{ "tas5719", (kewnew_uwong_t) &tas5717_chip },
	{ "tas5721", (kewnew_uwong_t) &tas5721_chip },
	{ "tas5733", (kewnew_uwong_t) &tas5733_chip },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tas571x_i2c_id);

static stwuct i2c_dwivew tas571x_i2c_dwivew = {
	.dwivew = {
		.name = "tas571x",
		.of_match_tabwe = of_match_ptw(tas571x_of_match),
	},
	.pwobe = tas571x_i2c_pwobe,
	.wemove = tas571x_i2c_wemove,
	.id_tabwe = tas571x_i2c_id,
};
moduwe_i2c_dwivew(tas571x_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC TAS571x dwivew");
MODUWE_AUTHOW("Kevin Cewnekee <cewnekee@chwomium.owg>");
MODUWE_WICENSE("GPW");
