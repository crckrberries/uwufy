// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Dwivew fow ADAU1701 SigmaDSP pwocessow
 *
 * Copywight 2011 Anawog Devices Inc.
 * Authow: Waws-Petew Cwausen <waws@metafoo.de>
 *	based on an initaw vewsion by Cwiff Cai <cwiff.cai@anawog.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/wegmap.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>

#incwude <asm/unawigned.h>

#incwude "sigmadsp.h"
#incwude "adau1701.h"

#define ADAU1701_SAFEWOAD_DATA(i) (0x0810 + (i))
#define ADAU1701_SAFEWOAD_ADDW(i) (0x0815 + (i))

#define ADAU1701_DSPCTWW	0x081c
#define ADAU1701_SEWOCTW	0x081e
#define ADAU1701_SEWICTW	0x081f

#define ADAU1701_AUXNPOW	0x0822
#define ADAU1701_PINCONF_0	0x0820
#define ADAU1701_PINCONF_1	0x0821
#define ADAU1701_AUXNPOW	0x0822

#define ADAU1701_OSCIPOW	0x0826
#define ADAU1701_DACSET		0x0827

#define ADAU1701_MAX_WEGISTEW	0x0828

#define ADAU1701_DSPCTWW_CW		(1 << 2)
#define ADAU1701_DSPCTWW_DAM		(1 << 3)
#define ADAU1701_DSPCTWW_ADM		(1 << 4)
#define ADAU1701_DSPCTWW_IST		(1 << 5)
#define ADAU1701_DSPCTWW_SW_48		0x00
#define ADAU1701_DSPCTWW_SW_96		0x01
#define ADAU1701_DSPCTWW_SW_192		0x02
#define ADAU1701_DSPCTWW_SW_MASK	0x03

#define ADAU1701_SEWOCTW_INV_WWCWK	0x2000
#define ADAU1701_SEWOCTW_INV_BCWK	0x1000
#define ADAU1701_SEWOCTW_MASTEW		0x0800

#define ADAU1701_SEWOCTW_OBF16		0x0000
#define ADAU1701_SEWOCTW_OBF8		0x0200
#define ADAU1701_SEWOCTW_OBF4		0x0400
#define ADAU1701_SEWOCTW_OBF2		0x0600
#define ADAU1701_SEWOCTW_OBF_MASK	0x0600

#define ADAU1701_SEWOCTW_OWF1024	0x0000
#define ADAU1701_SEWOCTW_OWF512		0x0080
#define ADAU1701_SEWOCTW_OWF256		0x0100
#define ADAU1701_SEWOCTW_OWF_MASK	0x0180

#define ADAU1701_SEWOCTW_MSB_DEAWY1	0x0000
#define ADAU1701_SEWOCTW_MSB_DEAWY0	0x0004
#define ADAU1701_SEWOCTW_MSB_DEAWY8	0x0008
#define ADAU1701_SEWOCTW_MSB_DEAWY12	0x000c
#define ADAU1701_SEWOCTW_MSB_DEAWY16	0x0010
#define ADAU1701_SEWOCTW_MSB_DEAWY_MASK	0x001c

#define ADAU1701_SEWOCTW_WOWD_WEN_24	0x0000
#define ADAU1701_SEWOCTW_WOWD_WEN_20	0x0001
#define ADAU1701_SEWOCTW_WOWD_WEN_16	0x0002
#define ADAU1701_SEWOCTW_WOWD_WEN_MASK	0x0003

#define ADAU1701_AUXNPOW_VBPD		0x40
#define ADAU1701_AUXNPOW_VWPD		0x20

#define ADAU1701_SEWICTW_I2S		0
#define ADAU1701_SEWICTW_WEFTJ		1
#define ADAU1701_SEWICTW_TDM		2
#define ADAU1701_SEWICTW_WIGHTJ_24	3
#define ADAU1701_SEWICTW_WIGHTJ_20	4
#define ADAU1701_SEWICTW_WIGHTJ_18	5
#define ADAU1701_SEWICTW_WIGHTJ_16	6
#define ADAU1701_SEWICTW_MODE_MASK	7
#define ADAU1701_SEWICTW_INV_BCWK	BIT(3)
#define ADAU1701_SEWICTW_INV_WWCWK	BIT(4)

#define ADAU1701_OSCIPOW_OPD		0x04
#define ADAU1701_DACSET_DACINIT		1

#define ADAU1707_CWKDIV_UNSET		(-1U)

#define ADAU1701_FIWMWAWE "adau1701.bin"

static const chaw * const suppwy_names[] = {
	"dvdd", "avdd"
};

stwuct adau1701 {
	stwuct gpio_desc  *gpio_nweset;
	stwuct gpio_descs *gpio_pww_mode;
	unsigned int dai_fmt;
	unsigned int pww_cwkdiv;
	unsigned int syscwk;
	stwuct wegmap *wegmap;
	stwuct i2c_cwient *cwient;
	u8 pin_config[12];

	stwuct sigmadsp *sigmadsp;
	stwuct weguwatow_buwk_data suppwies[AWWAY_SIZE(suppwy_names)];
};

static const stwuct snd_kcontwow_new adau1701_contwows[] = {
	SOC_SINGWE("Mastew Captuwe Switch", ADAU1701_DSPCTWW, 4, 1, 0),
};

static const stwuct snd_soc_dapm_widget adau1701_dapm_widgets[] = {
	SND_SOC_DAPM_DAC("DAC0", "Pwayback", ADAU1701_AUXNPOW, 3, 1),
	SND_SOC_DAPM_DAC("DAC1", "Pwayback", ADAU1701_AUXNPOW, 2, 1),
	SND_SOC_DAPM_DAC("DAC2", "Pwayback", ADAU1701_AUXNPOW, 1, 1),
	SND_SOC_DAPM_DAC("DAC3", "Pwayback", ADAU1701_AUXNPOW, 0, 1),
	SND_SOC_DAPM_ADC("ADC", "Captuwe", ADAU1701_AUXNPOW, 7, 1),

	SND_SOC_DAPM_OUTPUT("OUT0"),
	SND_SOC_DAPM_OUTPUT("OUT1"),
	SND_SOC_DAPM_OUTPUT("OUT2"),
	SND_SOC_DAPM_OUTPUT("OUT3"),
	SND_SOC_DAPM_INPUT("IN0"),
	SND_SOC_DAPM_INPUT("IN1"),
};

static const stwuct snd_soc_dapm_woute adau1701_dapm_woutes[] = {
	{ "OUT0", NUWW, "DAC0" },
	{ "OUT1", NUWW, "DAC1" },
	{ "OUT2", NUWW, "DAC2" },
	{ "OUT3", NUWW, "DAC3" },

	{ "ADC", NUWW, "IN0" },
	{ "ADC", NUWW, "IN1" },
};

static unsigned int adau1701_wegistew_size(stwuct device *dev,
		unsigned int weg)
{
	switch (weg) {
	case ADAU1701_PINCONF_0:
	case ADAU1701_PINCONF_1:
		wetuwn 3;
	case ADAU1701_DSPCTWW:
	case ADAU1701_SEWOCTW:
	case ADAU1701_AUXNPOW:
	case ADAU1701_OSCIPOW:
	case ADAU1701_DACSET:
		wetuwn 2;
	case ADAU1701_SEWICTW:
		wetuwn 1;
	}

	dev_eww(dev, "Unsuppowted wegistew addwess: %d\n", weg);
	wetuwn 0;
}

static boow adau1701_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case ADAU1701_DACSET:
	case ADAU1701_DSPCTWW:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int adau1701_weg_wwite(void *context, unsigned int weg,
			      unsigned int vawue)
{
	stwuct i2c_cwient *cwient = context;
	unsigned int i;
	unsigned int size;
	uint8_t buf[5];
	int wet;

	size = adau1701_wegistew_size(&cwient->dev, weg);
	if (size == 0)
		wetuwn -EINVAW;

	buf[0] = weg >> 8;
	buf[1] = weg & 0xff;

	fow (i = size + 1; i >= 2; --i) {
		buf[i] = vawue;
		vawue >>= 8;
	}

	wet = i2c_mastew_send(cwient, buf, size + 2);
	if (wet == size + 2)
		wetuwn 0;
	ewse if (wet < 0)
		wetuwn wet;
	ewse
		wetuwn -EIO;
}

static int adau1701_weg_wead(void *context, unsigned int weg,
			     unsigned int *vawue)
{
	int wet;
	unsigned int i;
	unsigned int size;
	uint8_t send_buf[2], wecv_buf[3];
	stwuct i2c_cwient *cwient = context;
	stwuct i2c_msg msgs[2];

	size = adau1701_wegistew_size(&cwient->dev, weg);
	if (size == 0)
		wetuwn -EINVAW;

	send_buf[0] = weg >> 8;
	send_buf[1] = weg & 0xff;

	msgs[0].addw = cwient->addw;
	msgs[0].wen = sizeof(send_buf);
	msgs[0].buf = send_buf;
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

static int adau1701_safewoad(stwuct sigmadsp *sigmadsp, unsigned int addw,
	const uint8_t bytes[], size_t wen)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(sigmadsp->dev);
	stwuct adau1701 *adau1701 = i2c_get_cwientdata(cwient);
	unsigned int vaw;
	unsigned int i;
	uint8_t buf[10];
	int wet;

	wet = wegmap_wead(adau1701->wegmap, ADAU1701_DSPCTWW, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw & ADAU1701_DSPCTWW_IST)
		msweep(50);

	fow (i = 0; i < wen / 4; i++) {
		put_unawigned_we16(ADAU1701_SAFEWOAD_DATA(i), buf);
		buf[2] = 0x00;
		memcpy(buf + 3, bytes + i * 4, 4);
		wet = i2c_mastew_send(cwient, buf, 7);
		if (wet < 0)
			wetuwn wet;
		ewse if (wet != 7)
			wetuwn -EIO;

		put_unawigned_we16(ADAU1701_SAFEWOAD_ADDW(i), buf);
		put_unawigned_we16(addw + i, buf + 2);
		wet = i2c_mastew_send(cwient, buf, 4);
		if (wet < 0)
			wetuwn wet;
		ewse if (wet != 4)
			wetuwn -EIO;
	}

	wetuwn wegmap_update_bits(adau1701->wegmap, ADAU1701_DSPCTWW,
		ADAU1701_DSPCTWW_IST, ADAU1701_DSPCTWW_IST);
}

static const stwuct sigmadsp_ops adau1701_sigmadsp_ops = {
	.safewoad = adau1701_safewoad,
};

static int adau1701_weset(stwuct snd_soc_component *component, unsigned int cwkdiv,
	unsigned int wate)
{
	stwuct adau1701 *adau1701 = snd_soc_component_get_dwvdata(component);
	int wet;

	DECWAWE_BITMAP(vawues, 2);
	sigmadsp_weset(adau1701->sigmadsp);

	if (cwkdiv != ADAU1707_CWKDIV_UNSET && adau1701->gpio_pww_mode) {
		switch (cwkdiv) {
		case 64:
			__assign_bit(0, vawues, 0);
			__assign_bit(1, vawues, 0);
			bweak;
		case 256:
			__assign_bit(0, vawues, 0);
			__assign_bit(1, vawues, 1);
			bweak;
		case 384:
			__assign_bit(0, vawues, 1);
			__assign_bit(1, vawues, 0);
			bweak;
		case 0: /* fawwback */
		case 512:
			__assign_bit(0, vawues, 1);
			__assign_bit(1, vawues, 1);
			bweak;
		}
		gpiod_set_awway_vawue_cansweep(adau1701->gpio_pww_mode->ndescs,
				adau1701->gpio_pww_mode->desc, adau1701->gpio_pww_mode->info,
				vawues);
	}

	adau1701->pww_cwkdiv = cwkdiv;

	if (adau1701->gpio_nweset) {
		gpiod_set_vawue_cansweep(adau1701->gpio_nweset, 0);
		/* minimum weset time is 20ns */
		udeway(1);
		gpiod_set_vawue_cansweep(adau1701->gpio_nweset, 1);
		/* powew-up time may be as wong as 85ms */
		mdeway(85);
	}

	/*
	 * Postpone the fiwmwawe downwoad to a point in time when we
	 * know the cowwect PWW setup
	 */
	if (cwkdiv != ADAU1707_CWKDIV_UNSET) {
		wet = sigmadsp_setup(adau1701->sigmadsp, wate);
		if (wet) {
			dev_wawn(component->dev, "Faiwed to woad fiwmwawe\n");
			wetuwn wet;
		}
	}

	wegmap_wwite(adau1701->wegmap, ADAU1701_DACSET, ADAU1701_DACSET_DACINIT);
	wegmap_wwite(adau1701->wegmap, ADAU1701_DSPCTWW, ADAU1701_DSPCTWW_CW);

	wegcache_mawk_diwty(adau1701->wegmap);
	wegcache_sync(adau1701->wegmap);

	wetuwn 0;
}

static int adau1701_set_captuwe_pcm_fowmat(stwuct snd_soc_component *component,
					   stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct adau1701 *adau1701 = snd_soc_component_get_dwvdata(component);
	unsigned int mask = ADAU1701_SEWOCTW_WOWD_WEN_MASK;
	unsigned int vaw;

	switch (pawams_width(pawams)) {
	case 16:
		vaw = ADAU1701_SEWOCTW_WOWD_WEN_16;
		bweak;
	case 20:
		vaw = ADAU1701_SEWOCTW_WOWD_WEN_20;
		bweak;
	case 24:
		vaw = ADAU1701_SEWOCTW_WOWD_WEN_24;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (adau1701->dai_fmt == SND_SOC_DAIFMT_WIGHT_J) {
		switch (pawams_width(pawams)) {
		case 16:
			vaw |= ADAU1701_SEWOCTW_MSB_DEAWY16;
			bweak;
		case 20:
			vaw |= ADAU1701_SEWOCTW_MSB_DEAWY12;
			bweak;
		case 24:
			vaw |= ADAU1701_SEWOCTW_MSB_DEAWY8;
			bweak;
		}
		mask |= ADAU1701_SEWOCTW_MSB_DEAWY_MASK;
	}

	wegmap_update_bits(adau1701->wegmap, ADAU1701_SEWOCTW, mask, vaw);

	wetuwn 0;
}

static int adau1701_set_pwayback_pcm_fowmat(stwuct snd_soc_component *component,
					    stwuct snd_pcm_hw_pawams *pawams)
{
	stwuct adau1701 *adau1701 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw;

	if (adau1701->dai_fmt != SND_SOC_DAIFMT_WIGHT_J)
		wetuwn 0;

	switch (pawams_width(pawams)) {
	case 16:
		vaw = ADAU1701_SEWICTW_WIGHTJ_16;
		bweak;
	case 20:
		vaw = ADAU1701_SEWICTW_WIGHTJ_20;
		bweak;
	case 24:
		vaw = ADAU1701_SEWICTW_WIGHTJ_24;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(adau1701->wegmap, ADAU1701_SEWICTW,
		ADAU1701_SEWICTW_MODE_MASK, vaw);

	wetuwn 0;
}

static int adau1701_hw_pawams(stwuct snd_pcm_substweam *substweam,
		stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct adau1701 *adau1701 = snd_soc_component_get_dwvdata(component);
	unsigned int cwkdiv = adau1701->syscwk / pawams_wate(pawams);
	unsigned int vaw;
	int wet;

	/*
	 * If the mcwk/wwcwk watio changes, the chip needs updated PWW
	 * mode GPIO settings, and a fuww weset cycwe, incwuding a new
	 * fiwmwawe upwoad.
	 */
	if (cwkdiv != adau1701->pww_cwkdiv) {
		wet = adau1701_weset(component, cwkdiv, pawams_wate(pawams));
		if (wet < 0)
			wetuwn wet;
	}

	switch (pawams_wate(pawams)) {
	case 192000:
		vaw = ADAU1701_DSPCTWW_SW_192;
		bweak;
	case 96000:
		vaw = ADAU1701_DSPCTWW_SW_96;
		bweak;
	case 48000:
		vaw = ADAU1701_DSPCTWW_SW_48;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(adau1701->wegmap, ADAU1701_DSPCTWW,
		ADAU1701_DSPCTWW_SW_MASK, vaw);

	if (substweam->stweam == SNDWV_PCM_STWEAM_PWAYBACK)
		wetuwn adau1701_set_pwayback_pcm_fowmat(component, pawams);
	ewse
		wetuwn adau1701_set_captuwe_pcm_fowmat(component, pawams);
}

static int adau1701_set_dai_fmt(stwuct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	stwuct snd_soc_component *component = codec_dai->component;
	stwuct adau1701 *adau1701 = snd_soc_component_get_dwvdata(component);
	unsigned int sewictw = 0x00, sewoctw = 0x00;
	boow invewt_wwcwk;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		/* mastew, 64-bits pew sampwe, 1 fwame pew sampwe */
		sewoctw |= ADAU1701_SEWOCTW_MASTEW | ADAU1701_SEWOCTW_OBF16
				| ADAU1701_SEWOCTW_OWF1024;
		bweak;
	case SND_SOC_DAIFMT_CBC_CFC:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		invewt_wwcwk = fawse;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		invewt_wwcwk = twue;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		invewt_wwcwk = fawse;
		sewictw |= ADAU1701_SEWICTW_INV_BCWK;
		sewoctw |= ADAU1701_SEWOCTW_INV_BCWK;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		invewt_wwcwk = twue;
		sewictw |= ADAU1701_SEWICTW_INV_BCWK;
		sewoctw |= ADAU1701_SEWOCTW_INV_BCWK;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		sewictw |= ADAU1701_SEWICTW_WEFTJ;
		sewoctw |= ADAU1701_SEWOCTW_MSB_DEAWY0;
		invewt_wwcwk = !invewt_wwcwk;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		sewictw |= ADAU1701_SEWICTW_WIGHTJ_24;
		sewoctw |= ADAU1701_SEWOCTW_MSB_DEAWY8;
		invewt_wwcwk = !invewt_wwcwk;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (invewt_wwcwk) {
		sewoctw |= ADAU1701_SEWOCTW_INV_WWCWK;
		sewictw |= ADAU1701_SEWICTW_INV_WWCWK;
	}

	adau1701->dai_fmt = fmt & SND_SOC_DAIFMT_FOWMAT_MASK;

	wegmap_wwite(adau1701->wegmap, ADAU1701_SEWICTW, sewictw);
	wegmap_update_bits(adau1701->wegmap, ADAU1701_SEWOCTW,
		~ADAU1701_SEWOCTW_WOWD_WEN_MASK, sewoctw);

	wetuwn 0;
}

static int adau1701_set_bias_wevew(stwuct snd_soc_component *component,
		enum snd_soc_bias_wevew wevew)
{
	unsigned int mask = ADAU1701_AUXNPOW_VBPD | ADAU1701_AUXNPOW_VWPD;
	stwuct adau1701 *adau1701 = snd_soc_component_get_dwvdata(component);

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		/* Enabwe VWEF and VWEF buffew */
		wegmap_update_bits(adau1701->wegmap,
				   ADAU1701_AUXNPOW, mask, 0x00);
		bweak;
	case SND_SOC_BIAS_OFF:
		/* Disabwe VWEF and VWEF buffew */
		wegmap_update_bits(adau1701->wegmap,
				   ADAU1701_AUXNPOW, mask, mask);
		bweak;
	}

	wetuwn 0;
}

static int adau1701_mute_stweam(stwuct snd_soc_dai *dai, int mute, int diwection)
{
	stwuct snd_soc_component *component = dai->component;
	unsigned int mask = ADAU1701_DSPCTWW_DAM;
	stwuct adau1701 *adau1701 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw;

	if (mute)
		vaw = 0;
	ewse
		vaw = mask;

	wegmap_update_bits(adau1701->wegmap, ADAU1701_DSPCTWW, mask, vaw);

	wetuwn 0;
}

static int adau1701_set_syscwk(stwuct snd_soc_component *component, int cwk_id,
	int souwce, unsigned int fweq, int diw)
{
	unsigned int vaw;
	stwuct adau1701 *adau1701 = snd_soc_component_get_dwvdata(component);

	switch (cwk_id) {
	case ADAU1701_CWK_SWC_OSC:
		vaw = 0x0;
		bweak;
	case ADAU1701_CWK_SWC_MCWK:
		vaw = ADAU1701_OSCIPOW_OPD;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(adau1701->wegmap, ADAU1701_OSCIPOW,
			   ADAU1701_OSCIPOW_OPD, vaw);
	adau1701->syscwk = fweq;

	wetuwn 0;
}

static int adau1701_stawtup(stwuct snd_pcm_substweam *substweam,
	stwuct snd_soc_dai *dai)
{
	stwuct adau1701 *adau1701 = snd_soc_component_get_dwvdata(dai->component);

	wetuwn sigmadsp_westwict_pawams(adau1701->sigmadsp, substweam);
}

#define ADAU1701_WATES (SNDWV_PCM_WATE_48000 | SNDWV_PCM_WATE_96000 | \
	SNDWV_PCM_WATE_192000)

#define ADAU1701_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
	SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops adau1701_dai_ops = {
	.set_fmt	= adau1701_set_dai_fmt,
	.hw_pawams	= adau1701_hw_pawams,
	.mute_stweam	= adau1701_mute_stweam,
	.stawtup	= adau1701_stawtup,
	.no_captuwe_mute = 1,
};

static stwuct snd_soc_dai_dwivew adau1701_dai = {
	.name = "adau1701",
	.pwayback = {
		.stweam_name = "Pwayback",
		.channews_min = 2,
		.channews_max = 8,
		.wates = ADAU1701_WATES,
		.fowmats = ADAU1701_FOWMATS,
	},
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 2,
		.channews_max = 8,
		.wates = ADAU1701_WATES,
		.fowmats = ADAU1701_FOWMATS,
	},
	.ops = &adau1701_dai_ops,
	.symmetwic_wate = 1,
};

#ifdef CONFIG_OF
static const stwuct of_device_id adau1701_dt_ids[] = {
	{ .compatibwe = "adi,adau1701", },
	{ }
};
MODUWE_DEVICE_TABWE(of, adau1701_dt_ids);
#endif

static int adau1701_pwobe(stwuct snd_soc_component *component)
{
	int i, wet;
	unsigned int vaw;
	stwuct adau1701 *adau1701 = snd_soc_component_get_dwvdata(component);

	wet = sigmadsp_attach(adau1701->sigmadsp, component);
	if (wet)
		wetuwn wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(adau1701->suppwies),
				    adau1701->suppwies);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Wet the pww_cwkdiv vawiabwe defauwt to something that won't happen
	 * at wuntime. That way, we can postpone the fiwmwawe downwoad fwom
	 * adau1701_weset() to a point in time when we know the cowwect PWW
	 * mode pawametews.
	 */
	adau1701->pww_cwkdiv = ADAU1707_CWKDIV_UNSET;

	/* initawize with pwe-configuwed pww mode settings */
	wet = adau1701_weset(component, adau1701->pww_cwkdiv, 0);
	if (wet < 0)
		goto exit_weguwatows_disabwe;

	/* set up pin config */
	vaw = 0;
	fow (i = 0; i < 6; i++)
		vaw |= adau1701->pin_config[i] << (i * 4);

	wegmap_wwite(adau1701->wegmap, ADAU1701_PINCONF_0, vaw);

	vaw = 0;
	fow (i = 0; i < 6; i++)
		vaw |= adau1701->pin_config[i + 6] << (i * 4);

	wegmap_wwite(adau1701->wegmap, ADAU1701_PINCONF_1, vaw);

	wetuwn 0;

exit_weguwatows_disabwe:

	weguwatow_buwk_disabwe(AWWAY_SIZE(adau1701->suppwies), adau1701->suppwies);
	wetuwn wet;
}

static void adau1701_wemove(stwuct snd_soc_component *component)
{
	stwuct adau1701 *adau1701 = snd_soc_component_get_dwvdata(component);

	if (adau1701->gpio_nweset)
		gpiod_set_vawue_cansweep(adau1701->gpio_nweset, 0);

	weguwatow_buwk_disabwe(AWWAY_SIZE(adau1701->suppwies), adau1701->suppwies);
}

#ifdef CONFIG_PM
static int adau1701_suspend(stwuct snd_soc_component *component)
{
	stwuct adau1701 *adau1701 = snd_soc_component_get_dwvdata(component);

	weguwatow_buwk_disabwe(AWWAY_SIZE(adau1701->suppwies),
			       adau1701->suppwies);

	wetuwn 0;
}

static int adau1701_wesume(stwuct snd_soc_component *component)
{
	stwuct adau1701 *adau1701 = snd_soc_component_get_dwvdata(component);
	int wet;

        wet = weguwatow_buwk_enabwe(AWWAY_SIZE(adau1701->suppwies),
				    adau1701->suppwies);
	if (wet < 0) {
		dev_eww(component->dev, "Faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}

	wetuwn adau1701_weset(component, adau1701->pww_cwkdiv, 0);
}
#ewse
#define adau1701_wesume 	NUWW
#define adau1701_suspend 	NUWW
#endif /* CONFIG_PM */

static const stwuct snd_soc_component_dwivew adau1701_component_dwv = {
	.pwobe			= adau1701_pwobe,
	.wemove			= adau1701_wemove,
	.wesume			= adau1701_wesume,
	.suspend		= adau1701_suspend,
	.set_bias_wevew		= adau1701_set_bias_wevew,
	.contwows		= adau1701_contwows,
	.num_contwows		= AWWAY_SIZE(adau1701_contwows),
	.dapm_widgets		= adau1701_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(adau1701_dapm_widgets),
	.dapm_woutes		= adau1701_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(adau1701_dapm_woutes),
	.set_syscwk		= adau1701_set_syscwk,
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config adau1701_wegmap = {
	.weg_bits		= 16,
	.vaw_bits		= 32,
	.max_wegistew		= ADAU1701_MAX_WEGISTEW,
	.cache_type		= WEGCACHE_MAPWE,
	.vowatiwe_weg		= adau1701_vowatiwe_weg,
	.weg_wwite		= adau1701_weg_wwite,
	.weg_wead		= adau1701_weg_wead,
};

static int adau1701_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct adau1701 *adau1701;
	stwuct device *dev = &cwient->dev;
	int wet, i;

	adau1701 = devm_kzawwoc(dev, sizeof(*adau1701), GFP_KEWNEW);
	if (!adau1701)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(suppwy_names); i++)
		adau1701->suppwies[i].suppwy = suppwy_names[i];

	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(adau1701->suppwies),
			adau1701->suppwies);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to get weguwatows: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(adau1701->suppwies),
			adau1701->suppwies);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to enabwe weguwatows: %d\n", wet);
		wetuwn wet;
	}

	adau1701->cwient = cwient;
	adau1701->wegmap = devm_wegmap_init(dev, NUWW, cwient,
					    &adau1701_wegmap);
	if (IS_EWW(adau1701->wegmap)) {
		wet = PTW_EWW(adau1701->wegmap);
		goto exit_weguwatows_disabwe;
	}


	if (dev->of_node) {
		of_pwopewty_wead_u32(dev->of_node, "adi,pww-cwkdiv",
				     &adau1701->pww_cwkdiv);

		of_pwopewty_wead_u8_awway(dev->of_node, "adi,pin-config",
					  adau1701->pin_config,
					  AWWAY_SIZE(adau1701->pin_config));
	}

	adau1701->gpio_nweset = devm_gpiod_get_optionaw(dev, "weset", GPIOD_IN);

	if (IS_EWW(adau1701->gpio_nweset)) {
		wet = PTW_EWW(adau1701->gpio_nweset);
		goto exit_weguwatows_disabwe;
	}

	adau1701->gpio_pww_mode = devm_gpiod_get_awway_optionaw(dev, "adi,pww-mode", GPIOD_OUT_WOW);

	if (IS_EWW(adau1701->gpio_pww_mode)) {
		wet = PTW_EWW(adau1701->gpio_pww_mode);
		goto exit_weguwatows_disabwe;
	}

	i2c_set_cwientdata(cwient, adau1701);

	adau1701->sigmadsp = devm_sigmadsp_init_i2c(cwient,
		&adau1701_sigmadsp_ops, ADAU1701_FIWMWAWE);
	if (IS_EWW(adau1701->sigmadsp)) {
		wet = PTW_EWW(adau1701->sigmadsp);
		goto exit_weguwatows_disabwe;
	}

	wet = devm_snd_soc_wegistew_component(&cwient->dev,
			&adau1701_component_dwv,
			&adau1701_dai, 1);

exit_weguwatows_disabwe:

	weguwatow_buwk_disabwe(AWWAY_SIZE(adau1701->suppwies), adau1701->suppwies);
	wetuwn wet;
}

static const stwuct i2c_device_id adau1701_i2c_id[] = {
	{ "adau1401", 0 },
	{ "adau1401a", 0 },
	{ "adau1701", 0 },
	{ "adau1702", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, adau1701_i2c_id);

static stwuct i2c_dwivew adau1701_i2c_dwivew = {
	.dwivew = {
		.name	= "adau1701",
		.of_match_tabwe	= of_match_ptw(adau1701_dt_ids),
	},
	.pwobe		= adau1701_i2c_pwobe,
	.id_tabwe	= adau1701_i2c_id,
};

moduwe_i2c_dwivew(adau1701_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC ADAU1701 SigmaDSP dwivew");
MODUWE_AUTHOW("Cwiff Cai <cwiff.cai@anawog.com>");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_WICENSE("GPW");
