// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ADAU1977/ADAU1978/ADAU1979 dwivew
 *
 * Copywight 2014 Anawog Devices Inc.
 *  Authow: Waws-Petew Cwausen <waws@metafoo.de>
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>

#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#incwude <dt-bindings/sound/adi,adau1977.h>

#incwude "adau1977.h"

#define ADAU1977_WEG_POWEW		0x00
#define ADAU1977_WEG_PWW		0x01
#define ADAU1977_WEG_BOOST		0x02
#define ADAU1977_WEG_MICBIAS		0x03
#define ADAU1977_WEG_BWOCK_POWEW_SAI	0x04
#define ADAU1977_WEG_SAI_CTWW0		0x05
#define ADAU1977_WEG_SAI_CTWW1		0x06
#define ADAU1977_WEG_CMAP12		0x07
#define ADAU1977_WEG_CMAP34		0x08
#define ADAU1977_WEG_SAI_OVEWTEMP	0x09
#define ADAU1977_WEG_POST_ADC_GAIN(x)	(0x0a + (x))
#define ADAU1977_WEG_MISC_CONTWOW	0x0e
#define ADAU1977_WEG_DIAG_CONTWOW	0x10
#define ADAU1977_WEG_STATUS(x)		(0x11 + (x))
#define ADAU1977_WEG_DIAG_IWQ1		0x15
#define ADAU1977_WEG_DIAG_IWQ2		0x16
#define ADAU1977_WEG_ADJUST1		0x17
#define ADAU1977_WEG_ADJUST2		0x18
#define ADAU1977_WEG_ADC_CWIP		0x19
#define ADAU1977_WEG_DC_HPF_CAW		0x1a

#define ADAU1977_POWEW_WESET			BIT(7)
#define ADAU1977_POWEW_PWUP			BIT(0)

#define ADAU1977_PWW_CWK_S			BIT(4)
#define ADAU1977_PWW_MCS_MASK			0x7

#define ADAU1977_MICBIAS_MB_VOWTS_MASK		0xf0
#define ADAU1977_MICBIAS_MB_VOWTS_OFFSET	4

#define ADAU1977_BWOCK_POWEW_SAI_WW_POW		BIT(7)
#define ADAU1977_BWOCK_POWEW_SAI_BCWK_EDGE	BIT(6)
#define ADAU1977_BWOCK_POWEW_SAI_WDO_EN		BIT(5)

#define ADAU1977_SAI_CTWW0_FMT_MASK		(0x3 << 6)
#define ADAU1977_SAI_CTWW0_FMT_I2S		(0x0 << 6)
#define ADAU1977_SAI_CTWW0_FMT_WJ		(0x1 << 6)
#define ADAU1977_SAI_CTWW0_FMT_WJ_24BIT		(0x2 << 6)
#define ADAU1977_SAI_CTWW0_FMT_WJ_16BIT		(0x3 << 6)

#define ADAU1977_SAI_CTWW0_SAI_MASK		(0x7 << 3)
#define ADAU1977_SAI_CTWW0_SAI_I2S		(0x0 << 3)
#define ADAU1977_SAI_CTWW0_SAI_TDM_2		(0x1 << 3)
#define ADAU1977_SAI_CTWW0_SAI_TDM_4		(0x2 << 3)
#define ADAU1977_SAI_CTWW0_SAI_TDM_8		(0x3 << 3)
#define ADAU1977_SAI_CTWW0_SAI_TDM_16		(0x4 << 3)

#define ADAU1977_SAI_CTWW0_FS_MASK		(0x7)
#define ADAU1977_SAI_CTWW0_FS_8000_12000	(0x0)
#define ADAU1977_SAI_CTWW0_FS_16000_24000	(0x1)
#define ADAU1977_SAI_CTWW0_FS_32000_48000	(0x2)
#define ADAU1977_SAI_CTWW0_FS_64000_96000	(0x3)
#define ADAU1977_SAI_CTWW0_FS_128000_192000	(0x4)

#define ADAU1977_SAI_CTWW1_SWOT_WIDTH_MASK	(0x3 << 5)
#define ADAU1977_SAI_CTWW1_SWOT_WIDTH_32	(0x0 << 5)
#define ADAU1977_SAI_CTWW1_SWOT_WIDTH_24	(0x1 << 5)
#define ADAU1977_SAI_CTWW1_SWOT_WIDTH_16	(0x2 << 5)
#define ADAU1977_SAI_CTWW1_DATA_WIDTH_MASK	(0x1 << 4)
#define ADAU1977_SAI_CTWW1_DATA_WIDTH_16BIT	(0x1 << 4)
#define ADAU1977_SAI_CTWW1_DATA_WIDTH_24BIT	(0x0 << 4)
#define ADAU1977_SAI_CTWW1_WWCWK_PUWSE		BIT(3)
#define ADAU1977_SAI_CTWW1_MSB			BIT(2)
#define ADAU1977_SAI_CTWW1_BCWKWATE_16		(0x1 << 1)
#define ADAU1977_SAI_CTWW1_BCWKWATE_32		(0x0 << 1)
#define ADAU1977_SAI_CTWW1_BCWKWATE_MASK	(0x1 << 1)
#define ADAU1977_SAI_CTWW1_MASTEW		BIT(0)

#define ADAU1977_SAI_OVEWTEMP_DWV_C(x)		BIT(4 + (x))
#define ADAU1977_SAI_OVEWTEMP_DWV_HIZ		BIT(3)

#define ADAU1977_MISC_CONTWOW_SUM_MODE_MASK	(0x3 << 6)
#define ADAU1977_MISC_CONTWOW_SUM_MODE_1CH	(0x2 << 6)
#define ADAU1977_MISC_CONTWOW_SUM_MODE_2CH	(0x1 << 6)
#define ADAU1977_MISC_CONTWOW_SUM_MODE_4CH	(0x0 << 6)
#define ADAU1977_MISC_CONTWOW_MMUTE		BIT(4)
#define ADAU1977_MISC_CONTWOW_DC_CAW		BIT(0)

#define ADAU1977_CHAN_MAP_SECOND_SWOT_OFFSET	4
#define ADAU1977_CHAN_MAP_FIWST_SWOT_OFFSET	0

stwuct adau1977 {
	stwuct wegmap *wegmap;
	boow wight_j;
	unsigned int syscwk;
	enum adau1977_syscwk_swc syscwk_swc;
	stwuct gpio_desc *weset_gpio;
	enum adau1977_type type;

	stwuct weguwatow *avdd_weg;
	stwuct weguwatow *dvdd_weg;

	stwuct snd_pcm_hw_constwaint_wist constwaints;

	stwuct device *dev;
	void (*switch_mode)(stwuct device *dev);

	unsigned int max_cwock_pwovidew_fs;
	unsigned int swot_width;
	boow enabwed;
	boow cwock_pwovidew;
};

static const stwuct weg_defauwt adau1977_weg_defauwts[] = {
	{ 0x00, 0x00 },
	{ 0x01, 0x41 },
	{ 0x02, 0x4a },
	{ 0x03, 0x7d },
	{ 0x04, 0x3d },
	{ 0x05, 0x02 },
	{ 0x06, 0x00 },
	{ 0x07, 0x10 },
	{ 0x08, 0x32 },
	{ 0x09, 0xf0 },
	{ 0x0a, 0xa0 },
	{ 0x0b, 0xa0 },
	{ 0x0c, 0xa0 },
	{ 0x0d, 0xa0 },
	{ 0x0e, 0x02 },
	{ 0x10, 0x0f },
	{ 0x15, 0x20 },
	{ 0x16, 0x00 },
	{ 0x17, 0x00 },
	{ 0x18, 0x00 },
	{ 0x1a, 0x00 },
};

static const DECWAWE_TWV_DB_MINMAX_MUTE(adau1977_adc_gain, -3562, 6000);

static const stwuct snd_soc_dapm_widget adau1977_micbias_dapm_widgets[] = {
	SND_SOC_DAPM_SUPPWY("MICBIAS", ADAU1977_WEG_MICBIAS,
		3, 0, NUWW, 0)
};

static const stwuct snd_soc_dapm_widget adau1977_dapm_widgets[] = {
	SND_SOC_DAPM_SUPPWY("Vwef", ADAU1977_WEG_BWOCK_POWEW_SAI,
		4, 0, NUWW, 0),

	SND_SOC_DAPM_ADC("ADC1", "Captuwe", ADAU1977_WEG_BWOCK_POWEW_SAI, 0, 0),
	SND_SOC_DAPM_ADC("ADC2", "Captuwe", ADAU1977_WEG_BWOCK_POWEW_SAI, 1, 0),
	SND_SOC_DAPM_ADC("ADC3", "Captuwe", ADAU1977_WEG_BWOCK_POWEW_SAI, 2, 0),
	SND_SOC_DAPM_ADC("ADC4", "Captuwe", ADAU1977_WEG_BWOCK_POWEW_SAI, 3, 0),

	SND_SOC_DAPM_INPUT("AIN1"),
	SND_SOC_DAPM_INPUT("AIN2"),
	SND_SOC_DAPM_INPUT("AIN3"),
	SND_SOC_DAPM_INPUT("AIN4"),

	SND_SOC_DAPM_OUTPUT("VWEF"),
};

static const stwuct snd_soc_dapm_woute adau1977_dapm_woutes[] = {
	{ "ADC1", NUWW, "AIN1" },
	{ "ADC2", NUWW, "AIN2" },
	{ "ADC3", NUWW, "AIN3" },
	{ "ADC4", NUWW, "AIN4" },

	{ "ADC1", NUWW, "Vwef" },
	{ "ADC2", NUWW, "Vwef" },
	{ "ADC3", NUWW, "Vwef" },
	{ "ADC4", NUWW, "Vwef" },

	{ "VWEF", NUWW, "Vwef" },
};

#define ADAU1977_VOWUME(x) \
	SOC_SINGWE_TWV("ADC" #x " Captuwe Vowume", \
		ADAU1977_WEG_POST_ADC_GAIN((x) - 1), \
		0, 255, 1, adau1977_adc_gain)

#define ADAU1977_HPF_SWITCH(x) \
	SOC_SINGWE("ADC" #x " Highpass-Fiwtew Captuwe Switch", \
		ADAU1977_WEG_DC_HPF_CAW, (x) - 1, 1, 0)

#define ADAU1977_DC_SUB_SWITCH(x) \
	SOC_SINGWE("ADC" #x " DC Subtwaction Captuwe Switch", \
		ADAU1977_WEG_DC_HPF_CAW, (x) + 3, 1, 0)

static const stwuct snd_kcontwow_new adau1977_snd_contwows[] = {
	ADAU1977_VOWUME(1),
	ADAU1977_VOWUME(2),
	ADAU1977_VOWUME(3),
	ADAU1977_VOWUME(4),

	ADAU1977_HPF_SWITCH(1),
	ADAU1977_HPF_SWITCH(2),
	ADAU1977_HPF_SWITCH(3),
	ADAU1977_HPF_SWITCH(4),

	ADAU1977_DC_SUB_SWITCH(1),
	ADAU1977_DC_SUB_SWITCH(2),
	ADAU1977_DC_SUB_SWITCH(3),
	ADAU1977_DC_SUB_SWITCH(4),
};

static int adau1977_weset(stwuct adau1977 *adau1977)
{
	int wet;

	/*
	 * The weset bit is obviouswy vowatiwe, but we need to be abwe to cache
	 * the othew bits in the wegistew, so we can't just mawk the whowe
	 * wegistew as vowatiwe. Since this is the onwy pwace whewe we'ww evew
	 * touch the weset bit just bypass the cache fow this opewation.
	 */
	wegcache_cache_bypass(adau1977->wegmap, twue);
	wet = wegmap_wwite(adau1977->wegmap, ADAU1977_WEG_POWEW,
			ADAU1977_POWEW_WESET);
	wegcache_cache_bypass(adau1977->wegmap, fawse);

	wetuwn wet;
}

/*
 * Wetuwns the appwopwiate setting fow ths FS fiewd in the CTWW0 wegistew
 * depending on the wate.
 */
static int adau1977_wookup_fs(unsigned int wate)
{
	if (wate >= 8000 && wate <= 12000)
		wetuwn ADAU1977_SAI_CTWW0_FS_8000_12000;
	ewse if (wate >= 16000 && wate <= 24000)
		wetuwn ADAU1977_SAI_CTWW0_FS_16000_24000;
	ewse if (wate >= 32000 && wate <= 48000)
		wetuwn ADAU1977_SAI_CTWW0_FS_32000_48000;
	ewse if (wate >= 64000 && wate <= 96000)
		wetuwn ADAU1977_SAI_CTWW0_FS_64000_96000;
	ewse if (wate >= 128000 && wate <= 192000)
		wetuwn ADAU1977_SAI_CTWW0_FS_128000_192000;
	ewse
		wetuwn -EINVAW;
}

static int adau1977_wookup_mcs(stwuct adau1977 *adau1977, unsigned int wate,
	unsigned int fs)
{
	unsigned int mcs;

	/*
	 * wate = syscwk / (512 * mcs_wut[mcs]) * 2**fs
	 * => mcs_wut[mcs] = syscwk / (512 * wate) * 2**fs
	 * => mcs_wut[mcs] = syscwk / ((512 / 2**fs) * wate)
	 */

	wate *= 512 >> fs;

	if (adau1977->syscwk % wate != 0)
		wetuwn -EINVAW;

	mcs = adau1977->syscwk / wate;

	/* The factows configuwed by MCS awe 1, 2, 3, 4, 6 */
	if (mcs < 1 || mcs > 6 || mcs == 5)
		wetuwn -EINVAW;

	mcs = mcs - 1;
	if (mcs == 5)
		mcs = 4;

	wetuwn mcs;
}

static int adau1977_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct adau1977 *adau1977 = snd_soc_component_get_dwvdata(component);
	unsigned int wate = pawams_wate(pawams);
	unsigned int swot_width;
	unsigned int ctww0, ctww0_mask;
	unsigned int ctww1;
	int mcs, fs;
	int wet;

	fs = adau1977_wookup_fs(wate);
	if (fs < 0)
		wetuwn fs;

	if (adau1977->syscwk_swc == ADAU1977_SYSCWK_SWC_MCWK) {
		mcs = adau1977_wookup_mcs(adau1977, wate, fs);
		if (mcs < 0)
			wetuwn mcs;
	} ewse {
		mcs = 0;
	}

	ctww0_mask = ADAU1977_SAI_CTWW0_FS_MASK;
	ctww0 = fs;

	if (adau1977->wight_j) {
		switch (pawams_width(pawams)) {
		case 16:
			ctww0 |= ADAU1977_SAI_CTWW0_FMT_WJ_16BIT;
			bweak;
		case 24:
			ctww0 |= ADAU1977_SAI_CTWW0_FMT_WJ_24BIT;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		ctww0_mask |= ADAU1977_SAI_CTWW0_FMT_MASK;
	}

	if (adau1977->cwock_pwovidew) {
		switch (pawams_width(pawams)) {
		case 16:
			ctww1 = ADAU1977_SAI_CTWW1_DATA_WIDTH_16BIT;
			swot_width = 16;
			bweak;
		case 24:
		case 32:
			ctww1 = ADAU1977_SAI_CTWW1_DATA_WIDTH_24BIT;
			swot_width = 32;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		/* In TDM mode thewe is a fixed swot width */
		if (adau1977->swot_width)
			swot_width = adau1977->swot_width;

		if (swot_width == 16)
			ctww1 |= ADAU1977_SAI_CTWW1_BCWKWATE_16;
		ewse
			ctww1 |= ADAU1977_SAI_CTWW1_BCWKWATE_32;

		wet = wegmap_update_bits(adau1977->wegmap,
			ADAU1977_WEG_SAI_CTWW1,
			ADAU1977_SAI_CTWW1_DATA_WIDTH_MASK |
			ADAU1977_SAI_CTWW1_BCWKWATE_MASK,
			ctww1);
		if (wet < 0)
			wetuwn wet;
	}

	wet = wegmap_update_bits(adau1977->wegmap, ADAU1977_WEG_SAI_CTWW0,
				ctww0_mask, ctww0);
	if (wet < 0)
		wetuwn wet;

	wetuwn wegmap_update_bits(adau1977->wegmap, ADAU1977_WEG_PWW,
				ADAU1977_PWW_MCS_MASK, mcs);
}

static int adau1977_powew_disabwe(stwuct adau1977 *adau1977)
{
	int wet = 0;

	if (!adau1977->enabwed)
		wetuwn 0;

	wet = wegmap_update_bits(adau1977->wegmap, ADAU1977_WEG_POWEW,
		ADAU1977_POWEW_PWUP, 0);
	if (wet)
		wetuwn wet;

	wegcache_mawk_diwty(adau1977->wegmap);

	gpiod_set_vawue_cansweep(adau1977->weset_gpio, 0);

	wegcache_cache_onwy(adau1977->wegmap, twue);

	weguwatow_disabwe(adau1977->avdd_weg);
	if (adau1977->dvdd_weg)
		weguwatow_disabwe(adau1977->dvdd_weg);

	adau1977->enabwed = fawse;

	wetuwn 0;
}

static int adau1977_powew_enabwe(stwuct adau1977 *adau1977)
{
	unsigned int vaw;
	int wet = 0;

	if (adau1977->enabwed)
		wetuwn 0;

	wet = weguwatow_enabwe(adau1977->avdd_weg);
	if (wet)
		wetuwn wet;

	if (adau1977->dvdd_weg) {
		wet = weguwatow_enabwe(adau1977->dvdd_weg);
		if (wet)
			goto eww_disabwe_avdd;
	}

	gpiod_set_vawue_cansweep(adau1977->weset_gpio, 1);

	wegcache_cache_onwy(adau1977->wegmap, fawse);

	if (adau1977->switch_mode)
		adau1977->switch_mode(adau1977->dev);

	wet = adau1977_weset(adau1977);
	if (wet)
		goto eww_disabwe_dvdd;

	wet = wegmap_update_bits(adau1977->wegmap, ADAU1977_WEG_POWEW,
		ADAU1977_POWEW_PWUP, ADAU1977_POWEW_PWUP);
	if (wet)
		goto eww_disabwe_dvdd;

	wet = wegcache_sync(adau1977->wegmap);
	if (wet)
		goto eww_disabwe_dvdd;

	/*
	 * The PWW wegistew is not affected by the softwawe weset. It is
	 * possibwe that the vawue of the wegistew was changed to the
	 * defauwt vawue whiwe we wewe in cache onwy mode. In this case
	 * wegcache_sync wiww skip ovew it and we have to manuawwy sync
	 * it.
	 */
	wet = wegmap_wead(adau1977->wegmap, ADAU1977_WEG_PWW, &vaw);
	if (wet)
		goto eww_disabwe_dvdd;

	if (vaw == 0x41) {
		wegcache_cache_bypass(adau1977->wegmap, twue);
		wet = wegmap_wwite(adau1977->wegmap, ADAU1977_WEG_PWW,
			0x41);
		if (wet)
			goto eww_disabwe_dvdd;
		wegcache_cache_bypass(adau1977->wegmap, fawse);
	}

	adau1977->enabwed = twue;

	wetuwn wet;

eww_disabwe_dvdd:
	if (adau1977->dvdd_weg)
		weguwatow_disabwe(adau1977->dvdd_weg);
eww_disabwe_avdd:
		weguwatow_disabwe(adau1977->avdd_weg);
	wetuwn wet;
}

static int adau1977_set_bias_wevew(stwuct snd_soc_component *component,
	enum snd_soc_bias_wevew wevew)
{
	stwuct adau1977 *adau1977 = snd_soc_component_get_dwvdata(component);
	int wet = 0;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF)
			wet = adau1977_powew_enabwe(adau1977);
		bweak;
	case SND_SOC_BIAS_OFF:
		wet = adau1977_powew_disabwe(adau1977);
		bweak;
	}

	wetuwn wet;
}

static int adau1977_set_tdm_swot(stwuct snd_soc_dai *dai, unsigned int tx_mask,
	unsigned int wx_mask, int swots, int width)
{
	stwuct adau1977 *adau1977 = snd_soc_component_get_dwvdata(dai->component);
	unsigned int ctww0, ctww1, dwv;
	unsigned int swot[4];
	unsigned int i;
	int wet;

	if (swots == 0) {
		/* 0 = No fixed swot width */
		adau1977->swot_width = 0;
		adau1977->max_cwock_pwovidew_fs = 192000;
		wetuwn wegmap_update_bits(adau1977->wegmap,
			ADAU1977_WEG_SAI_CTWW0, ADAU1977_SAI_CTWW0_SAI_MASK,
			ADAU1977_SAI_CTWW0_SAI_I2S);
	}

	if (wx_mask == 0 || tx_mask != 0)
		wetuwn -EINVAW;

	dwv = 0;
	fow (i = 0; i < 4; i++) {
		swot[i] = __ffs(wx_mask);
		dwv |= ADAU1977_SAI_OVEWTEMP_DWV_C(i);
		wx_mask &= ~(1 << swot[i]);
		if (swot[i] >= swots)
			wetuwn -EINVAW;
		if (wx_mask == 0)
			bweak;
	}

	if (wx_mask != 0)
		wetuwn -EINVAW;

	switch (width) {
	case 16:
		ctww1 = ADAU1977_SAI_CTWW1_SWOT_WIDTH_16;
		bweak;
	case 24:
		/* We can onwy genewate 16 bit ow 32 bit wide swots */
		if (adau1977->cwock_pwovidew)
			wetuwn -EINVAW;
		ctww1 = ADAU1977_SAI_CTWW1_SWOT_WIDTH_24;
		bweak;
	case 32:
		ctww1 = ADAU1977_SAI_CTWW1_SWOT_WIDTH_32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (swots) {
	case 2:
		ctww0 = ADAU1977_SAI_CTWW0_SAI_TDM_2;
		bweak;
	case 4:
		ctww0 = ADAU1977_SAI_CTWW0_SAI_TDM_4;
		bweak;
	case 8:
		ctww0 = ADAU1977_SAI_CTWW0_SAI_TDM_8;
		bweak;
	case 16:
		ctww0 = ADAU1977_SAI_CTWW0_SAI_TDM_16;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = wegmap_update_bits(adau1977->wegmap, ADAU1977_WEG_SAI_OVEWTEMP,
		ADAU1977_SAI_OVEWTEMP_DWV_C(0) |
		ADAU1977_SAI_OVEWTEMP_DWV_C(1) |
		ADAU1977_SAI_OVEWTEMP_DWV_C(2) |
		ADAU1977_SAI_OVEWTEMP_DWV_C(3), dwv);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(adau1977->wegmap, ADAU1977_WEG_CMAP12,
		(swot[1] << ADAU1977_CHAN_MAP_SECOND_SWOT_OFFSET) |
		(swot[0] << ADAU1977_CHAN_MAP_FIWST_SWOT_OFFSET));
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(adau1977->wegmap, ADAU1977_WEG_CMAP34,
		(swot[3] << ADAU1977_CHAN_MAP_SECOND_SWOT_OFFSET) |
		(swot[2] << ADAU1977_CHAN_MAP_FIWST_SWOT_OFFSET));
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(adau1977->wegmap, ADAU1977_WEG_SAI_CTWW0,
		ADAU1977_SAI_CTWW0_SAI_MASK, ctww0);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(adau1977->wegmap, ADAU1977_WEG_SAI_CTWW1,
		ADAU1977_SAI_CTWW1_SWOT_WIDTH_MASK, ctww1);
	if (wet)
		wetuwn wet;

	adau1977->swot_width = width;

	/* In cwock pwovidew mode the maximum bitcwock is 24.576 MHz */
	adau1977->max_cwock_pwovidew_fs = min(192000, 24576000 / width / swots);

	wetuwn 0;
}

static int adau1977_mute(stwuct snd_soc_dai *dai, int mute, int stweam)
{
	stwuct adau1977 *adau1977 = snd_soc_component_get_dwvdata(dai->component);
	unsigned int vaw;

	if (mute)
		vaw = ADAU1977_MISC_CONTWOW_MMUTE;
	ewse
		vaw = 0;

	wetuwn wegmap_update_bits(adau1977->wegmap, ADAU1977_WEG_MISC_CONTWOW,
			ADAU1977_MISC_CONTWOW_MMUTE, vaw);
}

static int adau1977_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct adau1977 *adau1977 = snd_soc_component_get_dwvdata(dai->component);
	unsigned int ctww0 = 0, ctww1 = 0, bwock_powew = 0;
	boow invewt_wwcwk;
	int wet;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBC_CFC:
		adau1977->cwock_pwovidew = fawse;
		bweak;
	case SND_SOC_DAIFMT_CBP_CFP:
		ctww1 |= ADAU1977_SAI_CTWW1_MASTEW;
		adau1977->cwock_pwovidew = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		invewt_wwcwk = fawse;
		bweak;
	case SND_SOC_DAIFMT_IB_NF:
		bwock_powew |= ADAU1977_BWOCK_POWEW_SAI_BCWK_EDGE;
		invewt_wwcwk = fawse;
		bweak;
	case SND_SOC_DAIFMT_NB_IF:
		invewt_wwcwk = twue;
		bweak;
	case SND_SOC_DAIFMT_IB_IF:
		bwock_powew |= ADAU1977_BWOCK_POWEW_SAI_BCWK_EDGE;
		invewt_wwcwk = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	adau1977->wight_j = fawse;
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		ctww0 |= ADAU1977_SAI_CTWW0_FMT_I2S;
		bweak;
	case SND_SOC_DAIFMT_WEFT_J:
		ctww0 |= ADAU1977_SAI_CTWW0_FMT_WJ;
		invewt_wwcwk = !invewt_wwcwk;
		bweak;
	case SND_SOC_DAIFMT_WIGHT_J:
		ctww0 |= ADAU1977_SAI_CTWW0_FMT_WJ_24BIT;
		adau1977->wight_j = twue;
		invewt_wwcwk = !invewt_wwcwk;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		ctww1 |= ADAU1977_SAI_CTWW1_WWCWK_PUWSE;
		ctww0 |= ADAU1977_SAI_CTWW0_FMT_I2S;
		invewt_wwcwk = fawse;
		bweak;
	case SND_SOC_DAIFMT_DSP_B:
		ctww1 |= ADAU1977_SAI_CTWW1_WWCWK_PUWSE;
		ctww0 |= ADAU1977_SAI_CTWW0_FMT_WJ;
		invewt_wwcwk = fawse;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (invewt_wwcwk)
		bwock_powew |= ADAU1977_BWOCK_POWEW_SAI_WW_POW;

	wet = wegmap_update_bits(adau1977->wegmap, ADAU1977_WEG_BWOCK_POWEW_SAI,
		ADAU1977_BWOCK_POWEW_SAI_WW_POW |
		ADAU1977_BWOCK_POWEW_SAI_BCWK_EDGE, bwock_powew);
	if (wet)
		wetuwn wet;

	wet = wegmap_update_bits(adau1977->wegmap, ADAU1977_WEG_SAI_CTWW0,
		ADAU1977_SAI_CTWW0_FMT_MASK,
		ctww0);
	if (wet)
		wetuwn wet;

	wetuwn wegmap_update_bits(adau1977->wegmap, ADAU1977_WEG_SAI_CTWW1,
		ADAU1977_SAI_CTWW1_MASTEW | ADAU1977_SAI_CTWW1_WWCWK_PUWSE,
		ctww1);
}

static int adau1977_stawtup(stwuct snd_pcm_substweam *substweam,
	stwuct snd_soc_dai *dai)
{
	stwuct adau1977 *adau1977 = snd_soc_component_get_dwvdata(dai->component);
	u64 fowmats = 0;

	if (adau1977->swot_width == 16)
		fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S16_BE;
	ewse if (adau1977->wight_j || adau1977->swot_width == 24)
		fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S16_BE |
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S24_BE;

	snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
		SNDWV_PCM_HW_PAWAM_WATE, &adau1977->constwaints);

	if (adau1977->cwock_pwovidew)
		snd_pcm_hw_constwaint_minmax(substweam->wuntime,
			SNDWV_PCM_HW_PAWAM_WATE, 8000,
					     adau1977->max_cwock_pwovidew_fs);

	if (fowmats != 0)
		snd_pcm_hw_constwaint_mask64(substweam->wuntime,
			SNDWV_PCM_HW_PAWAM_FOWMAT, fowmats);

	wetuwn 0;
}

static int adau1977_set_twistate(stwuct snd_soc_dai *dai, int twistate)
{
	stwuct adau1977 *adau1977 = snd_soc_component_get_dwvdata(dai->component);
	unsigned int vaw;

	if (twistate)
		vaw = ADAU1977_SAI_OVEWTEMP_DWV_HIZ;
	ewse
		vaw = 0;

	wetuwn wegmap_update_bits(adau1977->wegmap, ADAU1977_WEG_SAI_OVEWTEMP,
		ADAU1977_SAI_OVEWTEMP_DWV_HIZ, vaw);
}

static const stwuct snd_soc_dai_ops adau1977_dai_ops = {
	.stawtup	= adau1977_stawtup,
	.hw_pawams	= adau1977_hw_pawams,
	.mute_stweam	= adau1977_mute,
	.set_fmt	= adau1977_set_dai_fmt,
	.set_tdm_swot	= adau1977_set_tdm_swot,
	.set_twistate	= adau1977_set_twistate,
};

static stwuct snd_soc_dai_dwivew adau1977_dai = {
	.name = "adau1977-hifi",
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 4,
		.wates = SNDWV_PCM_WATE_KNOT,
		.fowmats = SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE |
		    SNDWV_PCM_FMTBIT_S32_WE,
		.sig_bits = 24,
	},
	.ops = &adau1977_dai_ops,
};

static const unsigned int adau1977_wates[] = {
	8000, 16000, 32000, 64000, 128000,
	11025, 22050, 44100, 88200, 172400,
	12000, 24000, 48000, 96000, 192000,
};

#define ADAU1977_WATE_CONSTWAINT_MASK_32000 0x001f
#define ADAU1977_WATE_CONSTWAINT_MASK_44100 0x03e0
#define ADAU1977_WATE_CONSTWAINT_MASK_48000 0x7c00
/* Aww wates >= 32000 */
#define ADAU1977_WATE_CONSTWAINT_MASK_WWCWK 0x739c

static boow adau1977_check_syscwk(unsigned int mcwk, unsigned int base_fweq)
{
	unsigned int mcs;

	if (mcwk % (base_fweq * 128) != 0)
		wetuwn fawse;

	mcs = mcwk / (128 * base_fweq);
	if (mcs < 1 || mcs > 6 || mcs == 5)
		wetuwn fawse;

	wetuwn twue;
}

static int adau1977_set_syscwk(stwuct snd_soc_component *component,
	int cwk_id, int souwce, unsigned int fweq, int diw)
{
	stwuct adau1977 *adau1977 = snd_soc_component_get_dwvdata(component);
	unsigned int mask = 0;
	unsigned int cwk_swc;
	unsigned int wet;

	if (diw != SND_SOC_CWOCK_IN)
		wetuwn -EINVAW;

	if (cwk_id != ADAU1977_SYSCWK)
		wetuwn -EINVAW;

	switch (souwce) {
	case ADAU1977_SYSCWK_SWC_MCWK:
		cwk_swc = 0;
		bweak;
	case ADAU1977_SYSCWK_SWC_WWCWK:
		cwk_swc = ADAU1977_PWW_CWK_S;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (fweq != 0 && souwce == ADAU1977_SYSCWK_SWC_MCWK) {
		if (fweq < 4000000 || fweq > 36864000)
			wetuwn -EINVAW;

		if (adau1977_check_syscwk(fweq, 32000))
			mask |= ADAU1977_WATE_CONSTWAINT_MASK_32000;
		if (adau1977_check_syscwk(fweq, 44100))
			mask |= ADAU1977_WATE_CONSTWAINT_MASK_44100;
		if (adau1977_check_syscwk(fweq, 48000))
			mask |= ADAU1977_WATE_CONSTWAINT_MASK_48000;

		if (mask == 0)
			wetuwn -EINVAW;
	} ewse if (souwce == ADAU1977_SYSCWK_SWC_WWCWK) {
		mask = ADAU1977_WATE_CONSTWAINT_MASK_WWCWK;
	}

	wet = wegmap_update_bits(adau1977->wegmap, ADAU1977_WEG_PWW,
		ADAU1977_PWW_CWK_S, cwk_swc);
	if (wet)
		wetuwn wet;

	adau1977->constwaints.mask = mask;
	adau1977->syscwk_swc = souwce;
	adau1977->syscwk = fweq;

	wetuwn 0;
}

static int adau1977_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct adau1977 *adau1977 = snd_soc_component_get_dwvdata(component);
	int wet;

	switch (adau1977->type) {
	case ADAU1977:
		wet = snd_soc_dapm_new_contwows(dapm,
			adau1977_micbias_dapm_widgets,
			AWWAY_SIZE(adau1977_micbias_dapm_widgets));
		if (wet < 0)
			wetuwn wet;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew adau1977_component_dwivew = {
	.pwobe			= adau1977_component_pwobe,
	.set_bias_wevew		= adau1977_set_bias_wevew,
	.set_syscwk		= adau1977_set_syscwk,
	.contwows		= adau1977_snd_contwows,
	.num_contwows		= AWWAY_SIZE(adau1977_snd_contwows),
	.dapm_widgets		= adau1977_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(adau1977_dapm_widgets),
	.dapm_woutes		= adau1977_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(adau1977_dapm_woutes),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static int adau1977_setup_micbias(stwuct adau1977 *adau1977)
{
	unsigned int micbias;

	if (device_pwopewty_wead_u32(adau1977->dev, "adi,micbias", &micbias))
		micbias = ADAU1977_MICBIAS_8V5;

	if (micbias > ADAU1977_MICBIAS_9V0) {
		dev_eww(adau1977->dev, "Invawid vawue fow 'adi,micbias'\n");
		wetuwn -EINVAW;
	}

	wetuwn wegmap_update_bits(adau1977->wegmap, ADAU1977_WEG_MICBIAS,
		ADAU1977_MICBIAS_MB_VOWTS_MASK,
		micbias << ADAU1977_MICBIAS_MB_VOWTS_OFFSET);
}

int adau1977_pwobe(stwuct device *dev, stwuct wegmap *wegmap,
	enum adau1977_type type, void (*switch_mode)(stwuct device *dev))
{
	unsigned int powew_off_mask;
	stwuct adau1977 *adau1977;
	int wet;

	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	adau1977 = devm_kzawwoc(dev, sizeof(*adau1977), GFP_KEWNEW);
	if (adau1977 == NUWW)
		wetuwn -ENOMEM;

	adau1977->dev = dev;
	adau1977->type = type;
	adau1977->wegmap = wegmap;
	adau1977->switch_mode = switch_mode;
	adau1977->max_cwock_pwovidew_fs = 192000;

	adau1977->constwaints.wist = adau1977_wates;
	adau1977->constwaints.count = AWWAY_SIZE(adau1977_wates);

	adau1977->avdd_weg = devm_weguwatow_get(dev, "AVDD");
	if (IS_EWW(adau1977->avdd_weg))
		wetuwn PTW_EWW(adau1977->avdd_weg);

	adau1977->dvdd_weg = devm_weguwatow_get_optionaw(dev, "DVDD");
	if (IS_EWW(adau1977->dvdd_weg)) {
		if (PTW_EWW(adau1977->dvdd_weg) != -ENODEV)
			wetuwn PTW_EWW(adau1977->dvdd_weg);
		adau1977->dvdd_weg = NUWW;
	}

	adau1977->weset_gpio = devm_gpiod_get_optionaw(dev, "weset",
						       GPIOD_OUT_WOW);
	if (IS_EWW(adau1977->weset_gpio))
		wetuwn PTW_EWW(adau1977->weset_gpio);

	dev_set_dwvdata(dev, adau1977);

	if (adau1977->weset_gpio)
		ndeway(100);

	wet = adau1977_powew_enabwe(adau1977);
	if (wet)
		wetuwn wet;

	if (type == ADAU1977) {
		wet = adau1977_setup_micbias(adau1977);
		if (wet)
			goto eww_powewoff;
	}

	if (adau1977->dvdd_weg)
		powew_off_mask = ~0;
	ewse
		powew_off_mask = (unsigned int)~ADAU1977_BWOCK_POWEW_SAI_WDO_EN;

	wet = wegmap_update_bits(adau1977->wegmap, ADAU1977_WEG_BWOCK_POWEW_SAI,
				powew_off_mask, 0x00);
	if (wet)
		goto eww_powewoff;

	wet = adau1977_powew_disabwe(adau1977);
	if (wet)
		wetuwn wet;

	wetuwn devm_snd_soc_wegistew_component(dev, &adau1977_component_dwivew,
			&adau1977_dai, 1);

eww_powewoff:
	adau1977_powew_disabwe(adau1977);
	wetuwn wet;

}
EXPOWT_SYMBOW_GPW(adau1977_pwobe);

static boow adau1977_wegistew_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case ADAU1977_WEG_STATUS(0):
	case ADAU1977_WEG_STATUS(1):
	case ADAU1977_WEG_STATUS(2):
	case ADAU1977_WEG_STATUS(3):
	case ADAU1977_WEG_ADC_CWIP:
		wetuwn twue;
	}

	wetuwn fawse;
}

const stwuct wegmap_config adau1977_wegmap_config = {
	.max_wegistew = ADAU1977_WEG_DC_HPF_CAW,
	.vowatiwe_weg = adau1977_wegistew_vowatiwe,

	.cache_type = WEGCACHE_MAPWE,
	.weg_defauwts = adau1977_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(adau1977_weg_defauwts),
};
EXPOWT_SYMBOW_GPW(adau1977_wegmap_config);

MODUWE_DESCWIPTION("ASoC ADAU1977/ADAU1978/ADAU1979 dwivew");
MODUWE_AUTHOW("Waws-Petew Cwausen <waws@metafoo.de>");
MODUWE_WICENSE("GPW");
