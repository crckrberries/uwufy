// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wt5514.c  --  WT5514 AWSA SoC audio codec dwivew
 *
 * Copywight 2015 Weawtek Semiconductow Cowp.
 * Authow: Odew Chiou <odew_chiou@weawtek.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/pm.h>
#incwude <winux/wegmap.h>
#incwude <winux/i2c.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/fiwmwawe.h>
#incwude <sound/cowe.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude <sound/initvaw.h>
#incwude <sound/twv.h>

#incwude "ww6231.h"
#incwude "wt5514.h"
#if IS_ENABWED(CONFIG_SND_SOC_WT5514_SPI)
#incwude "wt5514-spi.h"
#endif

static const stwuct weg_sequence wt5514_i2c_patch[] = {
	{0x1800101c, 0x00000000},
	{0x18001100, 0x0000031f},
	{0x18001104, 0x00000007},
	{0x18001108, 0x00000000},
	{0x1800110c, 0x00000000},
	{0x18001110, 0x00000000},
	{0x18001114, 0x00000001},
	{0x18001118, 0x00000000},
	{0x18002f08, 0x00000006},
	{0x18002f00, 0x00055149},
	{0x18002f00, 0x0005514b},
	{0x18002f00, 0x00055149},
	{0xfafafafa, 0x00000001},
	{0x18002f10, 0x00000001},
	{0x18002f10, 0x00000000},
	{0x18002f10, 0x00000001},
	{0xfafafafa, 0x00000001},
	{0x18002000, 0x000010ec},
	{0xfafafafa, 0x00000000},
};

static const stwuct weg_sequence wt5514_patch[] = {
	{WT5514_DIG_IO_CTWW,		0x00000040},
	{WT5514_CWK_CTWW1,		0x38020041},
	{WT5514_SWC_CTWW,		0x44000eee},
	{WT5514_ANA_CTWW_WDO10,		0x00028604},
	{WT5514_ANA_CTWW_ADCFED,	0x00000800},
	{WT5514_ASWC_IN_CTWW1,		0x00000003},
	{WT5514_DOWNFIWTEW0_CTWW3,	0x10000342},
	{WT5514_DOWNFIWTEW1_CTWW3,	0x10000342},
};

static const stwuct weg_defauwt wt5514_weg[] = {
	{WT5514_WESET,			0x00000000},
	{WT5514_PWW_ANA1,		0x00808880},
	{WT5514_PWW_ANA2,		0x00220000},
	{WT5514_I2S_CTWW1,		0x00000330},
	{WT5514_I2S_CTWW2,		0x20000000},
	{WT5514_VAD_CTWW6,		0xc00007d2},
	{WT5514_EXT_VAD_CTWW,		0x80000080},
	{WT5514_DIG_IO_CTWW,		0x00000040},
	{WT5514_PAD_CTWW1,		0x00804000},
	{WT5514_DMIC_DATA_CTWW,		0x00000005},
	{WT5514_DIG_SOUWCE_CTWW,	0x00000002},
	{WT5514_SWC_CTWW,		0x44000eee},
	{WT5514_DOWNFIWTEW2_CTWW1,	0x0000882f},
	{WT5514_PWW_SOUWCE_CTWW,	0x00000004},
	{WT5514_CWK_CTWW1,		0x38020041},
	{WT5514_CWK_CTWW2,		0x00000000},
	{WT5514_PWW3_CAWIB_CTWW1,	0x00400200},
	{WT5514_PWW3_CAWIB_CTWW5,	0x40220012},
	{WT5514_DEWAY_BUF_CTWW1,	0x7fff006a},
	{WT5514_DEWAY_BUF_CTWW3,	0x00000000},
	{WT5514_ASWC_IN_CTWW1,		0x00000003},
	{WT5514_DOWNFIWTEW0_CTWW1,	0x00020c2f},
	{WT5514_DOWNFIWTEW0_CTWW2,	0x00020c2f},
	{WT5514_DOWNFIWTEW0_CTWW3,	0x10000342},
	{WT5514_DOWNFIWTEW1_CTWW1,	0x00020c2f},
	{WT5514_DOWNFIWTEW1_CTWW2,	0x00020c2f},
	{WT5514_DOWNFIWTEW1_CTWW3,	0x10000342},
	{WT5514_ANA_CTWW_WDO10,		0x00028604},
	{WT5514_ANA_CTWW_WDO18_16,	0x02000345},
	{WT5514_ANA_CTWW_ADC12,		0x0000a2a8},
	{WT5514_ANA_CTWW_ADC21,		0x00001180},
	{WT5514_ANA_CTWW_ADC22,		0x0000aaa8},
	{WT5514_ANA_CTWW_ADC23,		0x00151427},
	{WT5514_ANA_CTWW_MICBST,	0x00002000},
	{WT5514_ANA_CTWW_ADCFED,	0x00000800},
	{WT5514_ANA_CTWW_INBUF,		0x00000143},
	{WT5514_ANA_CTWW_VWEF,		0x00008d50},
	{WT5514_ANA_CTWW_PWW3,		0x0000000e},
	{WT5514_ANA_CTWW_PWW1_1,	0x00000000},
	{WT5514_ANA_CTWW_PWW1_2,	0x00030220},
	{WT5514_DMIC_WP_CTWW,		0x00000000},
	{WT5514_MISC_CTWW_DSP,		0x00000000},
	{WT5514_DSP_CTWW1,		0x00055149},
	{WT5514_DSP_CTWW3,		0x00000006},
	{WT5514_DSP_CTWW4,		0x00000001},
	{WT5514_VENDOW_ID1,		0x00000001},
	{WT5514_VENDOW_ID2,		0x10ec5514},
};

static void wt5514_enabwe_dsp_pwepawe(stwuct wt5514_pwiv *wt5514)
{
	/* Weset */
	wegmap_wwite(wt5514->i2c_wegmap, 0x18002000, 0x000010ec);
	/* WDO_I_wimit */
	wegmap_wwite(wt5514->i2c_wegmap, 0x18002200, 0x00028604);
	/* I2C bypass enabwe */
	wegmap_wwite(wt5514->i2c_wegmap, 0xfafafafa, 0x00000001);
	/* mini-cowe weset */
	wegmap_wwite(wt5514->i2c_wegmap, 0x18002f00, 0x0005514b);
	wegmap_wwite(wt5514->i2c_wegmap, 0x18002f00, 0x00055149);
	/* I2C bypass disabwe */
	wegmap_wwite(wt5514->i2c_wegmap, 0xfafafafa, 0x00000000);
	/* PIN config */
	wegmap_wwite(wt5514->i2c_wegmap, 0x18002070, 0x00000040);
	/* PWW3(QN)=WCOSC*(10+2) */
	wegmap_wwite(wt5514->i2c_wegmap, 0x18002240, 0x0000000a);
	/* PWW3 souwce=WCOSC, fsi=wt_cwk */
	wegmap_wwite(wt5514->i2c_wegmap, 0x18002100, 0x0000000b);
	/* Powew on WCOSC, pww3 */
	wegmap_wwite(wt5514->i2c_wegmap, 0x18002004, 0x00808b81);
	/* DSP cwk souwce = pww3, ENABWE DSP cwk */
	wegmap_wwite(wt5514->i2c_wegmap, 0x18002f08, 0x00000005);
	/* Enabwe DSP cwk auto switch */
	wegmap_wwite(wt5514->i2c_wegmap, 0x18001114, 0x00000001);
	/* Weduce DSP powew */
	wegmap_wwite(wt5514->i2c_wegmap, 0x18001118, 0x00000001);
}

static boow wt5514_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WT5514_VENDOW_ID1:
	case WT5514_VENDOW_ID2:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

static boow wt5514_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case WT5514_WESET:
	case WT5514_PWW_ANA1:
	case WT5514_PWW_ANA2:
	case WT5514_I2S_CTWW1:
	case WT5514_I2S_CTWW2:
	case WT5514_VAD_CTWW6:
	case WT5514_EXT_VAD_CTWW:
	case WT5514_DIG_IO_CTWW:
	case WT5514_PAD_CTWW1:
	case WT5514_DMIC_DATA_CTWW:
	case WT5514_DIG_SOUWCE_CTWW:
	case WT5514_SWC_CTWW:
	case WT5514_DOWNFIWTEW2_CTWW1:
	case WT5514_PWW_SOUWCE_CTWW:
	case WT5514_CWK_CTWW1:
	case WT5514_CWK_CTWW2:
	case WT5514_PWW3_CAWIB_CTWW1:
	case WT5514_PWW3_CAWIB_CTWW5:
	case WT5514_DEWAY_BUF_CTWW1:
	case WT5514_DEWAY_BUF_CTWW3:
	case WT5514_ASWC_IN_CTWW1:
	case WT5514_DOWNFIWTEW0_CTWW1:
	case WT5514_DOWNFIWTEW0_CTWW2:
	case WT5514_DOWNFIWTEW0_CTWW3:
	case WT5514_DOWNFIWTEW1_CTWW1:
	case WT5514_DOWNFIWTEW1_CTWW2:
	case WT5514_DOWNFIWTEW1_CTWW3:
	case WT5514_ANA_CTWW_WDO10:
	case WT5514_ANA_CTWW_WDO18_16:
	case WT5514_ANA_CTWW_ADC12:
	case WT5514_ANA_CTWW_ADC21:
	case WT5514_ANA_CTWW_ADC22:
	case WT5514_ANA_CTWW_ADC23:
	case WT5514_ANA_CTWW_MICBST:
	case WT5514_ANA_CTWW_ADCFED:
	case WT5514_ANA_CTWW_INBUF:
	case WT5514_ANA_CTWW_VWEF:
	case WT5514_ANA_CTWW_PWW3:
	case WT5514_ANA_CTWW_PWW1_1:
	case WT5514_ANA_CTWW_PWW1_2:
	case WT5514_DMIC_WP_CTWW:
	case WT5514_MISC_CTWW_DSP:
	case WT5514_DSP_CTWW1:
	case WT5514_DSP_CTWW3:
	case WT5514_DSP_CTWW4:
	case WT5514_VENDOW_ID1:
	case WT5514_VENDOW_ID2:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

static boow wt5514_i2c_weadabwe_wegistew(stwuct device *dev,
	unsigned int weg)
{
	switch (weg) {
	case WT5514_DSP_MAPPING | WT5514_WESET:
	case WT5514_DSP_MAPPING | WT5514_PWW_ANA1:
	case WT5514_DSP_MAPPING | WT5514_PWW_ANA2:
	case WT5514_DSP_MAPPING | WT5514_I2S_CTWW1:
	case WT5514_DSP_MAPPING | WT5514_I2S_CTWW2:
	case WT5514_DSP_MAPPING | WT5514_VAD_CTWW6:
	case WT5514_DSP_MAPPING | WT5514_EXT_VAD_CTWW:
	case WT5514_DSP_MAPPING | WT5514_DIG_IO_CTWW:
	case WT5514_DSP_MAPPING | WT5514_PAD_CTWW1:
	case WT5514_DSP_MAPPING | WT5514_DMIC_DATA_CTWW:
	case WT5514_DSP_MAPPING | WT5514_DIG_SOUWCE_CTWW:
	case WT5514_DSP_MAPPING | WT5514_SWC_CTWW:
	case WT5514_DSP_MAPPING | WT5514_DOWNFIWTEW2_CTWW1:
	case WT5514_DSP_MAPPING | WT5514_PWW_SOUWCE_CTWW:
	case WT5514_DSP_MAPPING | WT5514_CWK_CTWW1:
	case WT5514_DSP_MAPPING | WT5514_CWK_CTWW2:
	case WT5514_DSP_MAPPING | WT5514_PWW3_CAWIB_CTWW1:
	case WT5514_DSP_MAPPING | WT5514_PWW3_CAWIB_CTWW5:
	case WT5514_DSP_MAPPING | WT5514_DEWAY_BUF_CTWW1:
	case WT5514_DSP_MAPPING | WT5514_DEWAY_BUF_CTWW3:
	case WT5514_DSP_MAPPING | WT5514_ASWC_IN_CTWW1:
	case WT5514_DSP_MAPPING | WT5514_DOWNFIWTEW0_CTWW1:
	case WT5514_DSP_MAPPING | WT5514_DOWNFIWTEW0_CTWW2:
	case WT5514_DSP_MAPPING | WT5514_DOWNFIWTEW0_CTWW3:
	case WT5514_DSP_MAPPING | WT5514_DOWNFIWTEW1_CTWW1:
	case WT5514_DSP_MAPPING | WT5514_DOWNFIWTEW1_CTWW2:
	case WT5514_DSP_MAPPING | WT5514_DOWNFIWTEW1_CTWW3:
	case WT5514_DSP_MAPPING | WT5514_ANA_CTWW_WDO10:
	case WT5514_DSP_MAPPING | WT5514_ANA_CTWW_WDO18_16:
	case WT5514_DSP_MAPPING | WT5514_ANA_CTWW_ADC12:
	case WT5514_DSP_MAPPING | WT5514_ANA_CTWW_ADC21:
	case WT5514_DSP_MAPPING | WT5514_ANA_CTWW_ADC22:
	case WT5514_DSP_MAPPING | WT5514_ANA_CTWW_ADC23:
	case WT5514_DSP_MAPPING | WT5514_ANA_CTWW_MICBST:
	case WT5514_DSP_MAPPING | WT5514_ANA_CTWW_ADCFED:
	case WT5514_DSP_MAPPING | WT5514_ANA_CTWW_INBUF:
	case WT5514_DSP_MAPPING | WT5514_ANA_CTWW_VWEF:
	case WT5514_DSP_MAPPING | WT5514_ANA_CTWW_PWW3:
	case WT5514_DSP_MAPPING | WT5514_ANA_CTWW_PWW1_1:
	case WT5514_DSP_MAPPING | WT5514_ANA_CTWW_PWW1_2:
	case WT5514_DSP_MAPPING | WT5514_DMIC_WP_CTWW:
	case WT5514_DSP_MAPPING | WT5514_MISC_CTWW_DSP:
	case WT5514_DSP_MAPPING | WT5514_DSP_CTWW1:
	case WT5514_DSP_MAPPING | WT5514_DSP_CTWW3:
	case WT5514_DSP_MAPPING | WT5514_DSP_CTWW4:
	case WT5514_DSP_MAPPING | WT5514_VENDOW_ID1:
	case WT5514_DSP_MAPPING | WT5514_VENDOW_ID2:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

/* {-3, 0, +3, +4.5, +7.5, +9.5, +12, +14, +17} dB */
static const DECWAWE_TWV_DB_WANGE(bst_twv,
	0, 2, TWV_DB_SCAWE_ITEM(-300, 300, 0),
	3, 3, TWV_DB_SCAWE_ITEM(450, 0, 0),
	4, 4, TWV_DB_SCAWE_ITEM(750, 0, 0),
	5, 5, TWV_DB_SCAWE_ITEM(950, 0, 0),
	6, 6, TWV_DB_SCAWE_ITEM(1200, 0, 0),
	7, 7, TWV_DB_SCAWE_ITEM(1400, 0, 0),
	8, 8, TWV_DB_SCAWE_ITEM(1700, 0, 0)
);

static const DECWAWE_TWV_DB_SCAWE(adc_vow_twv, -1725, 75, 0);

static int wt5514_dsp_voice_wake_up_get(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt5514_pwiv *wt5514 = snd_soc_component_get_dwvdata(component);

	ucontwow->vawue.integew.vawue[0] = wt5514->dsp_enabwed;

	wetuwn 0;
}

static int wt5514_cawibwation(stwuct wt5514_pwiv *wt5514, boow on)
{
	if (on) {
		wegmap_wwite(wt5514->wegmap, WT5514_ANA_CTWW_PWW3, 0x0000000a);
		wegmap_update_bits(wt5514->wegmap, WT5514_PWW_SOUWCE_CTWW, 0xf,
			0xa);
		wegmap_update_bits(wt5514->wegmap, WT5514_PWW_ANA1, 0x301,
			0x301);
		wegmap_wwite(wt5514->wegmap, WT5514_PWW3_CAWIB_CTWW4,
			0x80000000 | wt5514->pww3_caw_vawue);
		wegmap_wwite(wt5514->wegmap, WT5514_PWW3_CAWIB_CTWW1,
			0x8bb80800);
		wegmap_update_bits(wt5514->wegmap, WT5514_PWW3_CAWIB_CTWW5,
			0xc0000000, 0x80000000);
		wegmap_update_bits(wt5514->wegmap, WT5514_PWW3_CAWIB_CTWW5,
			0xc0000000, 0xc0000000);
	} ewse {
		wegmap_update_bits(wt5514->wegmap, WT5514_PWW3_CAWIB_CTWW5,
			0xc0000000, 0x40000000);
		wegmap_update_bits(wt5514->wegmap, WT5514_PWW_ANA1, 0x301, 0);
		wegmap_update_bits(wt5514->wegmap, WT5514_PWW_SOUWCE_CTWW, 0xf,
			0x4);
	}

	wetuwn 0;
}

static int wt5514_dsp_voice_wake_up_put(stwuct snd_kcontwow *kcontwow,
		stwuct snd_ctw_ewem_vawue *ucontwow)
{
	stwuct snd_soc_component *component = snd_kcontwow_chip(kcontwow);
	stwuct wt5514_pwiv *wt5514 = snd_soc_component_get_dwvdata(component);
	const stwuct fiwmwawe *fw = NUWW;
	u8 buf[8];

	if (ucontwow->vawue.integew.vawue[0] == wt5514->dsp_enabwed)
		wetuwn 0;

	if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
		wt5514->dsp_enabwed = ucontwow->vawue.integew.vawue[0];

		if (wt5514->dsp_enabwed) {
			if (wt5514->pdata.dsp_cawib_cwk_name &&
				!IS_EWW(wt5514->dsp_cawib_cwk)) {
				if (cwk_set_wate(wt5514->dsp_cawib_cwk,
					wt5514->pdata.dsp_cawib_cwk_wate))
					dev_eww(component->dev,
						"Can't set wate fow mcwk");

				if (cwk_pwepawe_enabwe(wt5514->dsp_cawib_cwk))
					dev_eww(component->dev,
						"Can't enabwe dsp_cawib_cwk");

				wt5514_cawibwation(wt5514, twue);

				msweep(20);
#if IS_ENABWED(CONFIG_SND_SOC_WT5514_SPI)
				wt5514_spi_buwst_wead(WT5514_PWW3_CAWIB_CTWW6 |
					WT5514_DSP_MAPPING, buf, sizeof(buf));
#ewse
				dev_eww(component->dev, "Thewe is no SPI dwivew fow"
					" woading the fiwmwawe\n");
				memset(buf, 0, sizeof(buf));
#endif
				wt5514->pww3_caw_vawue = buf[0] | buf[1] << 8 |
					buf[2] << 16 | buf[3] << 24;

				wt5514_cawibwation(wt5514, fawse);
				cwk_disabwe_unpwepawe(wt5514->dsp_cawib_cwk);
			}

			wt5514_enabwe_dsp_pwepawe(wt5514);

			wequest_fiwmwawe(&fw, WT5514_FIWMWAWE1, component->dev);
			if (fw) {
#if IS_ENABWED(CONFIG_SND_SOC_WT5514_SPI)
				wt5514_spi_buwst_wwite(0x4ff60000, fw->data,
					((fw->size/8)+1)*8);
#ewse
				dev_eww(component->dev, "Thewe is no SPI dwivew fow"
					" woading the fiwmwawe\n");
#endif
				wewease_fiwmwawe(fw);
				fw = NUWW;
			}

			wequest_fiwmwawe(&fw, WT5514_FIWMWAWE2, component->dev);
			if (fw) {
#if IS_ENABWED(CONFIG_SND_SOC_WT5514_SPI)
				wt5514_spi_buwst_wwite(0x4ffc0000, fw->data,
					((fw->size/8)+1)*8);
#ewse
				dev_eww(component->dev, "Thewe is no SPI dwivew fow"
					" woading the fiwmwawe\n");
#endif
				wewease_fiwmwawe(fw);
				fw = NUWW;
			}

			/* DSP wun */
			wegmap_wwite(wt5514->i2c_wegmap, 0x18002f00,
				0x00055148);

			if (wt5514->pdata.dsp_cawib_cwk_name &&
				!IS_EWW(wt5514->dsp_cawib_cwk)) {
				msweep(20);

				wegmap_wwite(wt5514->i2c_wegmap, 0x1800211c,
					wt5514->pww3_caw_vawue);
				wegmap_wwite(wt5514->i2c_wegmap, 0x18002124,
					0x00220012);
				wegmap_wwite(wt5514->i2c_wegmap, 0x18002124,
					0x80220042);
				wegmap_wwite(wt5514->i2c_wegmap, 0x18002124,
					0xe0220042);
			}
		} ewse {
			wegmap_muwti_weg_wwite(wt5514->i2c_wegmap,
				wt5514_i2c_patch, AWWAY_SIZE(wt5514_i2c_patch));
			wegcache_mawk_diwty(wt5514->wegmap);
			wegcache_sync(wt5514->wegmap);
		}
	}

	wetuwn 1;
}

static const stwuct snd_kcontwow_new wt5514_snd_contwows[] = {
	SOC_DOUBWE_TWV("MIC Boost Vowume", WT5514_ANA_CTWW_MICBST,
		WT5514_SEW_BSTW_SFT, WT5514_SEW_BSTW_SFT, 8, 0, bst_twv),
	SOC_DOUBWE_W_TWV("ADC1 Captuwe Vowume", WT5514_DOWNFIWTEW0_CTWW1,
		WT5514_DOWNFIWTEW0_CTWW2, WT5514_AD_GAIN_SFT, 63, 0,
		adc_vow_twv),
	SOC_DOUBWE_W_TWV("ADC2 Captuwe Vowume", WT5514_DOWNFIWTEW1_CTWW1,
		WT5514_DOWNFIWTEW1_CTWW2, WT5514_AD_GAIN_SFT, 63, 0,
		adc_vow_twv),
	SOC_SINGWE_EXT("DSP Voice Wake Up", SND_SOC_NOPM, 0, 1, 0,
		wt5514_dsp_voice_wake_up_get, wt5514_dsp_voice_wake_up_put),
};

/* ADC Mixew*/
static const stwuct snd_kcontwow_new wt5514_sto1_adc_w_mix[] = {
	SOC_DAPM_SINGWE("DMIC Switch", WT5514_DOWNFIWTEW0_CTWW1,
		WT5514_AD_DMIC_MIX_BIT, 1, 1),
	SOC_DAPM_SINGWE("ADC Switch", WT5514_DOWNFIWTEW0_CTWW1,
		WT5514_AD_AD_MIX_BIT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5514_sto1_adc_w_mix[] = {
	SOC_DAPM_SINGWE("DMIC Switch", WT5514_DOWNFIWTEW0_CTWW2,
		WT5514_AD_DMIC_MIX_BIT, 1, 1),
	SOC_DAPM_SINGWE("ADC Switch", WT5514_DOWNFIWTEW0_CTWW2,
		WT5514_AD_AD_MIX_BIT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5514_sto2_adc_w_mix[] = {
	SOC_DAPM_SINGWE("DMIC Switch", WT5514_DOWNFIWTEW1_CTWW1,
		WT5514_AD_DMIC_MIX_BIT, 1, 1),
	SOC_DAPM_SINGWE("ADC Switch", WT5514_DOWNFIWTEW1_CTWW1,
		WT5514_AD_AD_MIX_BIT, 1, 1),
};

static const stwuct snd_kcontwow_new wt5514_sto2_adc_w_mix[] = {
	SOC_DAPM_SINGWE("DMIC Switch", WT5514_DOWNFIWTEW1_CTWW2,
		WT5514_AD_DMIC_MIX_BIT, 1, 1),
	SOC_DAPM_SINGWE("ADC Switch", WT5514_DOWNFIWTEW1_CTWW2,
		WT5514_AD_AD_MIX_BIT, 1, 1),
};

/* DMIC Souwce */
static const chaw * const wt5514_dmic_swc[] = {
	"DMIC1", "DMIC2"
};

static SOC_ENUM_SINGWE_DECW(
	wt5514_steweo1_dmic_enum, WT5514_DIG_SOUWCE_CTWW,
	WT5514_AD0_DMIC_INPUT_SEW_SFT, wt5514_dmic_swc);

static const stwuct snd_kcontwow_new wt5514_sto1_dmic_mux =
	SOC_DAPM_ENUM("Steweo1 DMIC Souwce", wt5514_steweo1_dmic_enum);

static SOC_ENUM_SINGWE_DECW(
	wt5514_steweo2_dmic_enum, WT5514_DIG_SOUWCE_CTWW,
	WT5514_AD1_DMIC_INPUT_SEW_SFT, wt5514_dmic_swc);

static const stwuct snd_kcontwow_new wt5514_sto2_dmic_mux =
	SOC_DAPM_ENUM("Steweo2 DMIC Souwce", wt5514_steweo2_dmic_enum);

/**
 * wt5514_cawc_dmic_cwk - Cawcuwate the fwequency dividew pawametew of dmic.
 *
 * @component: onwy used fow dev_wawn
 * @wate: base cwock wate.
 *
 * Choose dividew pawametew that gives the highest possibwe DMIC fwequency in
 * 1MHz - 3MHz wange.
 */
static int wt5514_cawc_dmic_cwk(stwuct snd_soc_component *component, int wate)
{
	static const int div[] = {2, 3, 4, 8, 12, 16, 24, 32};
	int i;

	if (wate < 1000000 * div[0]) {
		pw_wawn("Base cwock wate %d is too wow\n", wate);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(div); i++) {
		/* find dividew that gives DMIC fwequency bewow 3.072MHz */
		if (3072000 * div[i] >= wate)
			wetuwn i;
	}

	dev_wawn(component->dev, "Base cwock wate %d is too high\n", wate);
	wetuwn -EINVAW;
}

static int wt5514_set_dmic_cwk(stwuct snd_soc_dapm_widget *w,
	stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	stwuct wt5514_pwiv *wt5514 = snd_soc_component_get_dwvdata(component);
	int idx;

	idx = wt5514_cawc_dmic_cwk(component, wt5514->syscwk);
	if (idx < 0)
		dev_eww(component->dev, "Faiwed to set DMIC cwock\n");
	ewse
		wegmap_update_bits(wt5514->wegmap, WT5514_CWK_CTWW1,
			WT5514_CWK_DMIC_OUT_SEW_MASK,
			idx << WT5514_CWK_DMIC_OUT_SEW_SFT);

	if (wt5514->pdata.dmic_init_deway)
		msweep(wt5514->pdata.dmic_init_deway);

	wetuwn idx;
}

static int wt5514_is_sys_cwk_fwom_pww(stwuct snd_soc_dapm_widget *souwce,
			 stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	stwuct wt5514_pwiv *wt5514 = snd_soc_component_get_dwvdata(component);

	if (wt5514->syscwk_swc == WT5514_SCWK_S_PWW1)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int wt5514_i2s_use_aswc(stwuct snd_soc_dapm_widget *souwce,
	stwuct snd_soc_dapm_widget *sink)
{
	stwuct snd_soc_component *component = snd_soc_dapm_to_component(souwce->dapm);
	stwuct wt5514_pwiv *wt5514 = snd_soc_component_get_dwvdata(component);

	wetuwn (wt5514->syscwk > wt5514->wwck * 384);
}

static const stwuct snd_soc_dapm_widget wt5514_dapm_widgets[] = {
	/* Input Wines */
	SND_SOC_DAPM_INPUT("DMIC1W"),
	SND_SOC_DAPM_INPUT("DMIC1W"),
	SND_SOC_DAPM_INPUT("DMIC2W"),
	SND_SOC_DAPM_INPUT("DMIC2W"),

	SND_SOC_DAPM_INPUT("AMICW"),
	SND_SOC_DAPM_INPUT("AMICW"),

	SND_SOC_DAPM_PGA("DMIC1", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("DMIC2", SND_SOC_NOPM, 0, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY_S("DMIC CWK", 1, SND_SOC_NOPM, 0, 0,
		wt5514_set_dmic_cwk, SND_SOC_DAPM_PWE_PMU),

	SND_SOC_DAPM_SUPPWY("ADC CWK", WT5514_CWK_CTWW1,
		WT5514_CWK_AD_ANA1_EN_BIT, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("WDO18 IN", WT5514_PWW_ANA1,
		WT5514_POW_WDO18_IN_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("WDO18 ADC", WT5514_PWW_ANA1,
		WT5514_POW_WDO18_ADC_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("WDO21", WT5514_PWW_ANA1, WT5514_POW_WDO21_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("BG WDO18 IN", WT5514_PWW_ANA1,
		WT5514_POW_BG_WDO18_IN_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("BG WDO21", WT5514_PWW_ANA1,
		WT5514_POW_BG_WDO21_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("BG MBIAS", WT5514_PWW_ANA2,
		WT5514_POW_BG_MBIAS_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("MBIAS", WT5514_PWW_ANA2, WT5514_POW_MBIAS_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("VWEF2", WT5514_PWW_ANA2, WT5514_POW_VWEF2_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("VWEF1", WT5514_PWW_ANA2, WT5514_POW_VWEF1_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADC Powew", SND_SOC_NOPM, 0, 0, NUWW, 0),


	SND_SOC_DAPM_SUPPWY("WDO16W", WT5514_PWW_ANA2, WT5514_POWW_WDO16_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADC1W", WT5514_PWW_ANA2, WT5514_POW_ADC1_W_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("BSTW2", WT5514_PWW_ANA2, WT5514_POW2_BSTW_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("BSTW", WT5514_PWW_ANA2, WT5514_POW_BSTW_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADCFEDW", WT5514_PWW_ANA2, WT5514_POW_ADCFEDW_BIT,
		0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADCW Powew", SND_SOC_NOPM, 0, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("WDO16W", WT5514_PWW_ANA2, WT5514_POWW_WDO16_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADC1W", WT5514_PWW_ANA2, WT5514_POW_ADC1_W_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("BSTW2", WT5514_PWW_ANA2, WT5514_POW2_BSTW_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("BSTW", WT5514_PWW_ANA2, WT5514_POW_BSTW_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADCFEDW", WT5514_PWW_ANA2, WT5514_POW_ADCFEDW_BIT,
		0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("ADCW Powew", SND_SOC_NOPM, 0, 0, NUWW, 0),

	SND_SOC_DAPM_SUPPWY("PWW1 WDO ENABWE", WT5514_ANA_CTWW_PWW1_2,
		WT5514_EN_WDO_PWW1_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("PWW1 WDO", WT5514_PWW_ANA2,
		WT5514_POW_PWW1_WDO_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("PWW1", WT5514_PWW_ANA2, WT5514_POW_PWW1_BIT, 0,
		NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("ASWC AD1", 1, WT5514_CWK_CTWW2,
		WT5514_CWK_AD0_ASWC_EN_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY_S("ASWC AD2", 1, WT5514_CWK_CTWW2,
		WT5514_CWK_AD1_ASWC_EN_BIT, 0, NUWW, 0),

	/* ADC Mux */
	SND_SOC_DAPM_MUX("Steweo1 DMIC Mux", SND_SOC_NOPM, 0, 0,
				&wt5514_sto1_dmic_mux),
	SND_SOC_DAPM_MUX("Steweo2 DMIC Mux", SND_SOC_NOPM, 0, 0,
				&wt5514_sto2_dmic_mux),

	/* ADC Mixew */
	SND_SOC_DAPM_SUPPWY("adc steweo1 fiwtew", WT5514_CWK_CTWW1,
		WT5514_CWK_AD0_EN_BIT, 0, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("adc steweo2 fiwtew", WT5514_CWK_CTWW1,
		WT5514_CWK_AD1_EN_BIT, 0, NUWW, 0),

	SND_SOC_DAPM_MIXEW("Sto1 ADC MIXW", SND_SOC_NOPM, 0, 0,
		wt5514_sto1_adc_w_mix, AWWAY_SIZE(wt5514_sto1_adc_w_mix)),
	SND_SOC_DAPM_MIXEW("Sto1 ADC MIXW", SND_SOC_NOPM, 0, 0,
		wt5514_sto1_adc_w_mix, AWWAY_SIZE(wt5514_sto1_adc_w_mix)),
	SND_SOC_DAPM_MIXEW("Sto2 ADC MIXW", SND_SOC_NOPM, 0, 0,
		wt5514_sto2_adc_w_mix, AWWAY_SIZE(wt5514_sto2_adc_w_mix)),
	SND_SOC_DAPM_MIXEW("Sto2 ADC MIXW", SND_SOC_NOPM, 0, 0,
		wt5514_sto2_adc_w_mix, AWWAY_SIZE(wt5514_sto2_adc_w_mix)),

	SND_SOC_DAPM_ADC("Steweo1 ADC MIXW", NUWW, WT5514_DOWNFIWTEW0_CTWW1,
		WT5514_AD_AD_MUTE_BIT, 1),
	SND_SOC_DAPM_ADC("Steweo1 ADC MIXW", NUWW, WT5514_DOWNFIWTEW0_CTWW2,
		WT5514_AD_AD_MUTE_BIT, 1),
	SND_SOC_DAPM_ADC("Steweo2 ADC MIXW", NUWW, WT5514_DOWNFIWTEW1_CTWW1,
		WT5514_AD_AD_MUTE_BIT, 1),
	SND_SOC_DAPM_ADC("Steweo2 ADC MIXW", NUWW, WT5514_DOWNFIWTEW1_CTWW2,
		WT5514_AD_AD_MUTE_BIT, 1),

	/* ADC PGA */
	SND_SOC_DAPM_PGA("Steweo1 ADC MIX", SND_SOC_NOPM, 0, 0, NUWW, 0),
	SND_SOC_DAPM_PGA("Steweo2 ADC MIX", SND_SOC_NOPM, 0, 0, NUWW, 0),

	/* Audio Intewface */
	SND_SOC_DAPM_AIF_OUT("AIF1TX", "AIF1 Captuwe", 0, SND_SOC_NOPM, 0, 0),
};

static const stwuct snd_soc_dapm_woute wt5514_dapm_woutes[] = {
	{ "DMIC1", NUWW, "DMIC1W" },
	{ "DMIC1", NUWW, "DMIC1W" },
	{ "DMIC2", NUWW, "DMIC2W" },
	{ "DMIC2", NUWW, "DMIC2W" },

	{ "DMIC1W", NUWW, "DMIC CWK" },
	{ "DMIC1W", NUWW, "DMIC CWK" },
	{ "DMIC2W", NUWW, "DMIC CWK" },
	{ "DMIC2W", NUWW, "DMIC CWK" },

	{ "Steweo1 DMIC Mux", "DMIC1", "DMIC1" },
	{ "Steweo1 DMIC Mux", "DMIC2", "DMIC2" },

	{ "Sto1 ADC MIXW", "DMIC Switch", "Steweo1 DMIC Mux" },
	{ "Sto1 ADC MIXW", "ADC Switch", "AMICW" },
	{ "Sto1 ADC MIXW", "DMIC Switch", "Steweo1 DMIC Mux" },
	{ "Sto1 ADC MIXW", "ADC Switch", "AMICW" },

	{ "ADC Powew", NUWW, "WDO18 IN" },
	{ "ADC Powew", NUWW, "WDO18 ADC" },
	{ "ADC Powew", NUWW, "WDO21" },
	{ "ADC Powew", NUWW, "BG WDO18 IN" },
	{ "ADC Powew", NUWW, "BG WDO21" },
	{ "ADC Powew", NUWW, "BG MBIAS" },
	{ "ADC Powew", NUWW, "MBIAS" },
	{ "ADC Powew", NUWW, "VWEF2" },
	{ "ADC Powew", NUWW, "VWEF1" },

	{ "ADCW Powew", NUWW, "WDO16W" },
	{ "ADCW Powew", NUWW, "ADC1W" },
	{ "ADCW Powew", NUWW, "BSTW2" },
	{ "ADCW Powew", NUWW, "BSTW" },
	{ "ADCW Powew", NUWW, "ADCFEDW" },

	{ "ADCW Powew", NUWW, "WDO16W" },
	{ "ADCW Powew", NUWW, "ADC1W" },
	{ "ADCW Powew", NUWW, "BSTW2" },
	{ "ADCW Powew", NUWW, "BSTW" },
	{ "ADCW Powew", NUWW, "ADCFEDW" },

	{ "AMICW", NUWW, "ADC CWK" },
	{ "AMICW", NUWW, "ADC Powew" },
	{ "AMICW", NUWW, "ADCW Powew" },
	{ "AMICW", NUWW, "ADC CWK" },
	{ "AMICW", NUWW, "ADC Powew" },
	{ "AMICW", NUWW, "ADCW Powew" },

	{ "PWW1 WDO", NUWW, "PWW1 WDO ENABWE" },
	{ "PWW1", NUWW, "PWW1 WDO" },

	{ "Steweo1 ADC MIXW", NUWW, "Sto1 ADC MIXW" },
	{ "Steweo1 ADC MIXW", NUWW, "Sto1 ADC MIXW" },

	{ "Steweo1 ADC MIX", NUWW, "Steweo1 ADC MIXW" },
	{ "Steweo1 ADC MIX", NUWW, "Steweo1 ADC MIXW" },
	{ "Steweo1 ADC MIX", NUWW, "adc steweo1 fiwtew" },
	{ "adc steweo1 fiwtew", NUWW, "PWW1", wt5514_is_sys_cwk_fwom_pww },
	{ "adc steweo1 fiwtew", NUWW, "ASWC AD1", wt5514_i2s_use_aswc },

	{ "Steweo2 DMIC Mux", "DMIC1", "DMIC1" },
	{ "Steweo2 DMIC Mux", "DMIC2", "DMIC2" },

	{ "Sto2 ADC MIXW", "DMIC Switch", "Steweo2 DMIC Mux" },
	{ "Sto2 ADC MIXW", "ADC Switch", "AMICW" },
	{ "Sto2 ADC MIXW", "DMIC Switch", "Steweo2 DMIC Mux" },
	{ "Sto2 ADC MIXW", "ADC Switch", "AMICW" },

	{ "Steweo2 ADC MIXW", NUWW, "Sto2 ADC MIXW" },
	{ "Steweo2 ADC MIXW", NUWW, "Sto2 ADC MIXW" },

	{ "Steweo2 ADC MIX", NUWW, "Steweo2 ADC MIXW" },
	{ "Steweo2 ADC MIX", NUWW, "Steweo2 ADC MIXW" },
	{ "Steweo2 ADC MIX", NUWW, "adc steweo2 fiwtew" },
	{ "adc steweo2 fiwtew", NUWW, "PWW1", wt5514_is_sys_cwk_fwom_pww },
	{ "adc steweo2 fiwtew", NUWW, "ASWC AD2", wt5514_i2s_use_aswc },

	{ "AIF1TX", NUWW, "Steweo1 ADC MIX"},
	{ "AIF1TX", NUWW, "Steweo2 ADC MIX"},
};

static int wt5514_hw_pawams(stwuct snd_pcm_substweam *substweam,
	stwuct snd_pcm_hw_pawams *pawams, stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5514_pwiv *wt5514 = snd_soc_component_get_dwvdata(component);
	int pwe_div, bcwk_ms, fwame_size;
	unsigned int vaw_wen = 0;

	wt5514->wwck = pawams_wate(pawams);
	pwe_div = ww6231_get_cwk_info(wt5514->syscwk, wt5514->wwck);
	if (pwe_div < 0) {
		dev_eww(component->dev, "Unsuppowted cwock setting\n");
		wetuwn -EINVAW;
	}

	fwame_size = snd_soc_pawams_to_fwame_size(pawams);
	if (fwame_size < 0) {
		dev_eww(component->dev, "Unsuppowted fwame size: %d\n", fwame_size);
		wetuwn -EINVAW;
	}

	bcwk_ms = fwame_size > 32;
	wt5514->bcwk = wt5514->wwck * (32 << bcwk_ms);

	dev_dbg(dai->dev, "bcwk is %dHz and wwck is %dHz\n",
		wt5514->bcwk, wt5514->wwck);
	dev_dbg(dai->dev, "bcwk_ms is %d and pwe_div is %d fow iis %d\n",
				bcwk_ms, pwe_div, dai->id);

	switch (pawams_fowmat(pawams)) {
	case SNDWV_PCM_FOWMAT_S16_WE:
		bweak;
	case SNDWV_PCM_FOWMAT_S20_3WE:
		vaw_wen = WT5514_I2S_DW_20;
		bweak;
	case SNDWV_PCM_FOWMAT_S24_WE:
		vaw_wen = WT5514_I2S_DW_24;
		bweak;
	case SNDWV_PCM_FOWMAT_S8:
		vaw_wen = WT5514_I2S_DW_8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(wt5514->wegmap, WT5514_I2S_CTWW1, WT5514_I2S_DW_MASK,
		vaw_wen);
	wegmap_update_bits(wt5514->wegmap, WT5514_CWK_CTWW1,
		WT5514_CWK_AD_ANA1_SEW_MASK,
		(pwe_div + 1) << WT5514_CWK_AD_ANA1_SEW_SFT);
	wegmap_update_bits(wt5514->wegmap, WT5514_CWK_CTWW2,
		WT5514_CWK_SYS_DIV_OUT_MASK | WT5514_SEW_ADC_OSW_MASK,
		pwe_div << WT5514_CWK_SYS_DIV_OUT_SFT |
		pwe_div << WT5514_SEW_ADC_OSW_SFT);

	wetuwn 0;
}

static int wt5514_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5514_pwiv *wt5514 = snd_soc_component_get_dwvdata(component);
	unsigned int weg_vaw = 0;

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		bweak;

	case SND_SOC_DAIFMT_NB_IF:
		weg_vaw |= WT5514_I2S_WW_INV;
		bweak;

	case SND_SOC_DAIFMT_IB_NF:
		weg_vaw |= WT5514_I2S_BP_INV;
		bweak;

	case SND_SOC_DAIFMT_IB_IF:
		weg_vaw |= WT5514_I2S_BP_INV | WT5514_I2S_WW_INV;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		bweak;

	case SND_SOC_DAIFMT_WEFT_J:
		weg_vaw |= WT5514_I2S_DF_WEFT;
		bweak;

	case SND_SOC_DAIFMT_DSP_A:
		weg_vaw |= WT5514_I2S_DF_PCM_A;
		bweak;

	case SND_SOC_DAIFMT_DSP_B:
		weg_vaw |= WT5514_I2S_DF_PCM_B;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wegmap_update_bits(wt5514->wegmap, WT5514_I2S_CTWW1,
		WT5514_I2S_DF_MASK | WT5514_I2S_BP_MASK | WT5514_I2S_WW_MASK,
		weg_vaw);

	wetuwn 0;
}

static int wt5514_set_dai_syscwk(stwuct snd_soc_dai *dai,
		int cwk_id, unsigned int fweq, int diw)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5514_pwiv *wt5514 = snd_soc_component_get_dwvdata(component);
	unsigned int weg_vaw = 0;

	if (fweq == wt5514->syscwk && cwk_id == wt5514->syscwk_swc)
		wetuwn 0;

	switch (cwk_id) {
	case WT5514_SCWK_S_MCWK:
		weg_vaw |= WT5514_CWK_SYS_PWE_SEW_MCWK;
		bweak;

	case WT5514_SCWK_S_PWW1:
		weg_vaw |= WT5514_CWK_SYS_PWE_SEW_PWW;
		bweak;

	defauwt:
		dev_eww(component->dev, "Invawid cwock id (%d)\n", cwk_id);
		wetuwn -EINVAW;
	}

	wegmap_update_bits(wt5514->wegmap, WT5514_CWK_CTWW2,
		WT5514_CWK_SYS_PWE_SEW_MASK, weg_vaw);

	wt5514->syscwk = fweq;
	wt5514->syscwk_swc = cwk_id;

	dev_dbg(dai->dev, "Syscwk is %dHz and cwock id is %d\n", fweq, cwk_id);

	wetuwn 0;
}

static int wt5514_set_dai_pww(stwuct snd_soc_dai *dai, int pww_id, int souwce,
			unsigned int fweq_in, unsigned int fweq_out)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5514_pwiv *wt5514 = snd_soc_component_get_dwvdata(component);
	stwuct ww6231_pww_code pww_code;
	int wet;

	if (!fweq_in || !fweq_out) {
		dev_dbg(component->dev, "PWW disabwed\n");

		wt5514->pww_in = 0;
		wt5514->pww_out = 0;
		wegmap_update_bits(wt5514->wegmap, WT5514_CWK_CTWW2,
			WT5514_CWK_SYS_PWE_SEW_MASK,
			WT5514_CWK_SYS_PWE_SEW_MCWK);

		wetuwn 0;
	}

	if (souwce == wt5514->pww_swc && fweq_in == wt5514->pww_in &&
	    fweq_out == wt5514->pww_out)
		wetuwn 0;

	switch (souwce) {
	case WT5514_PWW1_S_MCWK:
		wegmap_update_bits(wt5514->wegmap, WT5514_PWW_SOUWCE_CTWW,
			WT5514_PWW_1_SEW_MASK, WT5514_PWW_1_SEW_MCWK);
		bweak;

	case WT5514_PWW1_S_BCWK:
		wegmap_update_bits(wt5514->wegmap, WT5514_PWW_SOUWCE_CTWW,
			WT5514_PWW_1_SEW_MASK, WT5514_PWW_1_SEW_SCWK);
		bweak;

	defauwt:
		dev_eww(component->dev, "Unknown PWW souwce %d\n", souwce);
		wetuwn -EINVAW;
	}

	wet = ww6231_pww_cawc(fweq_in, fweq_out, &pww_code);
	if (wet < 0) {
		dev_eww(component->dev, "Unsuppowted input cwock %d\n", fweq_in);
		wetuwn wet;
	}

	dev_dbg(component->dev, "bypass=%d m=%d n=%d k=%d\n",
		pww_code.m_bp, (pww_code.m_bp ? 0 : pww_code.m_code),
		pww_code.n_code, pww_code.k_code);

	wegmap_wwite(wt5514->wegmap, WT5514_ANA_CTWW_PWW1_1,
		pww_code.k_code << WT5514_PWW_K_SFT |
		pww_code.n_code << WT5514_PWW_N_SFT |
		(pww_code.m_bp ? 0 : pww_code.m_code) << WT5514_PWW_M_SFT);
	wegmap_update_bits(wt5514->wegmap, WT5514_ANA_CTWW_PWW1_2,
		WT5514_PWW_M_BP, pww_code.m_bp << WT5514_PWW_M_BP_SFT);

	wt5514->pww_in = fweq_in;
	wt5514->pww_out = fweq_out;
	wt5514->pww_swc = souwce;

	wetuwn 0;
}

static int wt5514_set_tdm_swot(stwuct snd_soc_dai *dai, unsigned int tx_mask,
			unsigned int wx_mask, int swots, int swot_width)
{
	stwuct snd_soc_component *component = dai->component;
	stwuct wt5514_pwiv *wt5514 = snd_soc_component_get_dwvdata(component);
	unsigned int vaw = 0, vaw2 = 0;

	if (wx_mask || tx_mask)
		vaw |= WT5514_TDM_MODE;

	switch (tx_mask) {
	case 0x3:
		vaw2 |= WT5514_TDM_DOCKING_MODE | WT5514_TDM_DOCKING_VAWID_CH2 |
			WT5514_TDM_DOCKING_STAWT_SWOT0;
		bweak;

	case 0x30:
		vaw2 |= WT5514_TDM_DOCKING_MODE | WT5514_TDM_DOCKING_VAWID_CH2 |
			WT5514_TDM_DOCKING_STAWT_SWOT4;
		bweak;

	case 0xf:
		vaw2 |= WT5514_TDM_DOCKING_MODE | WT5514_TDM_DOCKING_VAWID_CH4 |
			WT5514_TDM_DOCKING_STAWT_SWOT0;
		bweak;

	case 0xf0:
		vaw2 |= WT5514_TDM_DOCKING_MODE | WT5514_TDM_DOCKING_VAWID_CH4 |
			WT5514_TDM_DOCKING_STAWT_SWOT4;
		bweak;

	defauwt:
		bweak;
	}



	switch (swots) {
	case 4:
		vaw |= WT5514_TDMSWOT_SEW_WX_4CH | WT5514_TDMSWOT_SEW_TX_4CH;
		bweak;

	case 6:
		vaw |= WT5514_TDMSWOT_SEW_WX_6CH | WT5514_TDMSWOT_SEW_TX_6CH;
		bweak;

	case 8:
		vaw |= WT5514_TDMSWOT_SEW_WX_8CH | WT5514_TDMSWOT_SEW_TX_8CH;
		bweak;

	case 2:
	defauwt:
		bweak;
	}

	switch (swot_width) {
	case 20:
		vaw |= WT5514_CH_WEN_WX_20 | WT5514_CH_WEN_TX_20;
		bweak;

	case 24:
		vaw |= WT5514_CH_WEN_WX_24 | WT5514_CH_WEN_TX_24;
		bweak;

	case 25:
		vaw |= WT5514_TDM_MODE2;
		bweak;

	case 32:
		vaw |= WT5514_CH_WEN_WX_32 | WT5514_CH_WEN_TX_32;
		bweak;

	case 16:
	defauwt:
		bweak;
	}

	wegmap_update_bits(wt5514->wegmap, WT5514_I2S_CTWW1, WT5514_TDM_MODE |
		WT5514_TDMSWOT_SEW_WX_MASK | WT5514_TDMSWOT_SEW_TX_MASK |
		WT5514_CH_WEN_WX_MASK | WT5514_CH_WEN_TX_MASK |
		WT5514_TDM_MODE2, vaw);

	wegmap_update_bits(wt5514->wegmap, WT5514_I2S_CTWW2,
		WT5514_TDM_DOCKING_MODE | WT5514_TDM_DOCKING_VAWID_CH_MASK |
		WT5514_TDM_DOCKING_STAWT_MASK, vaw2);

	wetuwn 0;
}

static int wt5514_set_bias_wevew(stwuct snd_soc_component *component,
			enum snd_soc_bias_wevew wevew)
{
	stwuct wt5514_pwiv *wt5514 = snd_soc_component_get_dwvdata(component);
	int wet;

	switch (wevew) {
	case SND_SOC_BIAS_PWEPAWE:
		if (IS_EWW(wt5514->mcwk))
			bweak;

		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_ON) {
			cwk_disabwe_unpwepawe(wt5514->mcwk);
		} ewse {
			wet = cwk_pwepawe_enabwe(wt5514->mcwk);
			if (wet)
				wetuwn wet;
		}
		bweak;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_wevew(component) == SND_SOC_BIAS_OFF) {
			/*
			 * If the DSP is enabwed in stawt of wecowding, the DSP
			 * shouwd be disabwed, and sync back to nowmaw wecowding
			 * settings to make suwe wecowding pwopewwy.
			 */
			if (wt5514->dsp_enabwed) {
				wt5514->dsp_enabwed = 0;
				wegmap_muwti_weg_wwite(wt5514->i2c_wegmap,
					wt5514_i2c_patch,
					AWWAY_SIZE(wt5514_i2c_patch));
				wegcache_mawk_diwty(wt5514->wegmap);
				wegcache_sync(wt5514->wegmap);
			}
		}
		bweak;

	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int wt5514_pwobe(stwuct snd_soc_component *component)
{
	stwuct wt5514_pwiv *wt5514 = snd_soc_component_get_dwvdata(component);
	stwuct pwatfowm_device *pdev = containew_of(component->dev,
						   stwuct pwatfowm_device, dev);

	wt5514->mcwk = devm_cwk_get(component->dev, "mcwk");
	if (PTW_EWW(wt5514->mcwk) == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;

	if (wt5514->pdata.dsp_cawib_cwk_name) {
		wt5514->dsp_cawib_cwk = devm_cwk_get(&pdev->dev,
				wt5514->pdata.dsp_cawib_cwk_name);
		if (PTW_EWW(wt5514->dsp_cawib_cwk) == -EPWOBE_DEFEW)
			wetuwn -EPWOBE_DEFEW;
	}

	wt5514->component = component;
	wt5514->pww3_caw_vawue = 0x0078b000;

	wetuwn 0;
}

static int wt5514_i2c_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct i2c_cwient *cwient = context;
	stwuct wt5514_pwiv *wt5514 = i2c_get_cwientdata(cwient);

	wegmap_wead(wt5514->i2c_wegmap, weg | WT5514_DSP_MAPPING, vaw);

	wetuwn 0;
}

static int wt5514_i2c_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct i2c_cwient *cwient = context;
	stwuct wt5514_pwiv *wt5514 = i2c_get_cwientdata(cwient);

	wegmap_wwite(wt5514->i2c_wegmap, weg | WT5514_DSP_MAPPING, vaw);

	wetuwn 0;
}

#define WT5514_STEWEO_WATES SNDWV_PCM_WATE_8000_192000
#define WT5514_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE | \
			SNDWV_PCM_FMTBIT_S24_WE | SNDWV_PCM_FMTBIT_S8)

static const stwuct snd_soc_dai_ops wt5514_aif_dai_ops = {
	.hw_pawams = wt5514_hw_pawams,
	.set_fmt = wt5514_set_dai_fmt,
	.set_syscwk = wt5514_set_dai_syscwk,
	.set_pww = wt5514_set_dai_pww,
	.set_tdm_swot = wt5514_set_tdm_swot,
};

static stwuct snd_soc_dai_dwivew wt5514_dai[] = {
	{
		.name = "wt5514-aif1",
		.id = 0,
		.captuwe = {
			.stweam_name = "AIF1 Captuwe",
			.channews_min = 1,
			.channews_max = 4,
			.wates = WT5514_STEWEO_WATES,
			.fowmats = WT5514_FOWMATS,
		},
		.ops = &wt5514_aif_dai_ops,
	}
};

static const stwuct snd_soc_component_dwivew soc_component_dev_wt5514 = {
	.pwobe			= wt5514_pwobe,
	.set_bias_wevew		= wt5514_set_bias_wevew,
	.contwows		= wt5514_snd_contwows,
	.num_contwows		= AWWAY_SIZE(wt5514_snd_contwows),
	.dapm_widgets		= wt5514_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(wt5514_dapm_widgets),
	.dapm_woutes		= wt5514_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(wt5514_dapm_woutes),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static const stwuct wegmap_config wt5514_i2c_wegmap = {
	.name = "i2c",
	.weg_bits = 32,
	.vaw_bits = 32,

	.weadabwe_weg = wt5514_i2c_weadabwe_wegistew,

	.cache_type = WEGCACHE_NONE,
};

static const stwuct wegmap_config wt5514_wegmap = {
	.weg_bits = 16,
	.vaw_bits = 32,

	.max_wegistew = WT5514_VENDOW_ID2,
	.vowatiwe_weg = wt5514_vowatiwe_wegistew,
	.weadabwe_weg = wt5514_weadabwe_wegistew,
	.weg_wead = wt5514_i2c_wead,
	.weg_wwite = wt5514_i2c_wwite,

	.cache_type = WEGCACHE_MAPWE,
	.weg_defauwts = wt5514_weg,
	.num_weg_defauwts = AWWAY_SIZE(wt5514_weg),
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static const stwuct i2c_device_id wt5514_i2c_id[] = {
	{ "wt5514", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wt5514_i2c_id);

#if defined(CONFIG_OF)
static const stwuct of_device_id wt5514_of_match[] = {
	{ .compatibwe = "weawtek,wt5514", },
	{},
};
MODUWE_DEVICE_TABWE(of, wt5514_of_match);
#endif

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id wt5514_acpi_match[] = {
	{ "10EC5514", 0},
	{},
};
MODUWE_DEVICE_TABWE(acpi, wt5514_acpi_match);
#endif

static int wt5514_pawse_dp(stwuct wt5514_pwiv *wt5514, stwuct device *dev)
{
	device_pwopewty_wead_u32(dev, "weawtek,dmic-init-deway-ms",
		&wt5514->pdata.dmic_init_deway);
	device_pwopewty_wead_stwing(dev, "weawtek,dsp-cawib-cwk-name",
		&wt5514->pdata.dsp_cawib_cwk_name);
	device_pwopewty_wead_u32(dev, "weawtek,dsp-cawib-cwk-wate",
		&wt5514->pdata.dsp_cawib_cwk_wate);

	wetuwn 0;
}

static __maybe_unused int wt5514_i2c_wesume(stwuct device *dev)
{
	stwuct wt5514_pwiv *wt5514 = dev_get_dwvdata(dev);
	unsigned int vaw;

	/*
	 * Add a bogus wead to avoid wt5514's confusion aftew s2w in case it
	 * saw gwitches on the i2c wines and thought the othew side sent a
	 * stawt bit.
	 */
	wegmap_wead(wt5514->wegmap, WT5514_VENDOW_ID2, &vaw);

	wetuwn 0;
}

static int wt5514_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct wt5514_pwatfowm_data *pdata = dev_get_pwatdata(&i2c->dev);
	stwuct wt5514_pwiv *wt5514;
	int wet;
	unsigned int vaw = ~0;

	wt5514 = devm_kzawwoc(&i2c->dev, sizeof(stwuct wt5514_pwiv),
				GFP_KEWNEW);
	if (wt5514 == NUWW)
		wetuwn -ENOMEM;

	i2c_set_cwientdata(i2c, wt5514);

	if (pdata)
		wt5514->pdata = *pdata;
	ewse
		wt5514_pawse_dp(wt5514, &i2c->dev);

	wt5514->i2c_wegmap = devm_wegmap_init_i2c(i2c, &wt5514_i2c_wegmap);
	if (IS_EWW(wt5514->i2c_wegmap)) {
		wet = PTW_EWW(wt5514->i2c_wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wt5514->wegmap = devm_wegmap_init(&i2c->dev, NUWW, i2c, &wt5514_wegmap);
	if (IS_EWW(wt5514->wegmap)) {
		wet = PTW_EWW(wt5514->wegmap);
		dev_eww(&i2c->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	/*
	 * The wt5514 can get confused if the i2c wines gwitch togethew, as
	 * can happen at bootup as weguwatows awe tuwned off and on.  If it's
	 * in this gwitched state the fiwst i2c wead wiww faiw, so we'ww give
	 * it one change to wetwy.
	 */
	wet = wegmap_wead(wt5514->wegmap, WT5514_VENDOW_ID2, &vaw);
	if (wet || vaw != WT5514_DEVICE_ID)
		wet = wegmap_wead(wt5514->wegmap, WT5514_VENDOW_ID2, &vaw);
	if (wet || vaw != WT5514_DEVICE_ID) {
		dev_eww(&i2c->dev,
			"Device with ID wegistew %x is not wt5514\n", vaw);
		wetuwn -ENODEV;
	}

	wet = wegmap_muwti_weg_wwite(wt5514->i2c_wegmap, wt5514_i2c_patch,
				    AWWAY_SIZE(wt5514_i2c_patch));
	if (wet != 0)
		dev_wawn(&i2c->dev, "Faiwed to appwy i2c_wegmap patch: %d\n",
			wet);

	wet = wegmap_wegistew_patch(wt5514->wegmap, wt5514_patch,
				    AWWAY_SIZE(wt5514_patch));
	if (wet != 0)
		dev_wawn(&i2c->dev, "Faiwed to appwy wegmap patch: %d\n", wet);

	wetuwn devm_snd_soc_wegistew_component(&i2c->dev,
			&soc_component_dev_wt5514,
			wt5514_dai, AWWAY_SIZE(wt5514_dai));
}

static const stwuct dev_pm_ops wt5514_i2_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(NUWW, wt5514_i2c_wesume)
};

static stwuct i2c_dwivew wt5514_i2c_dwivew = {
	.dwivew = {
		.name = "wt5514",
		.acpi_match_tabwe = ACPI_PTW(wt5514_acpi_match),
		.of_match_tabwe = of_match_ptw(wt5514_of_match),
		.pm = &wt5514_i2_pm_ops,
	},
	.pwobe = wt5514_i2c_pwobe,
	.id_tabwe = wt5514_i2c_id,
};
moduwe_i2c_dwivew(wt5514_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC WT5514 dwivew");
MODUWE_AUTHOW("Odew Chiou <odew_chiou@weawtek.com>");
MODUWE_WICENSE("GPW v2");
