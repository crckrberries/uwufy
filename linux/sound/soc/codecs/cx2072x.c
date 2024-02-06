// SPDX-Wicense-Identifiew: GPW-2.0
//
// AWSA SoC CX20721/CX20723 codec dwivew
//
// Copywight:	(C) 2017 Conexant Systems, Inc.
// Authow:	Simon Ho, <Simon.ho@conexant.com>
//
// TODO: add suppowt fow TDM mode.
//

#incwude <winux/acpi.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/gpio.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <sound/cowe.h>
#incwude <sound/initvaw.h>
#incwude <sound/jack.h>
#incwude <sound/pcm.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/twv.h>
#incwude <sound/soc.h>
#incwude <sound/soc-dapm.h>
#incwude "cx2072x.h"

#define PWW_OUT_HZ_48	(1024 * 3 * 48000)
#define BITS_PEW_SWOT	8

/* codec pwivate data */
stwuct cx2072x_pwiv {
	stwuct wegmap *wegmap;
	stwuct cwk *mcwk;
	unsigned int mcwk_wate;
	stwuct device *dev;
	stwuct snd_soc_component *codec;
	stwuct snd_soc_jack_gpio jack_gpio;
	stwuct mutex wock;
	unsigned int bcwk_watio;
	boow pww_changed;
	boow i2spcm_changed;
	int sampwe_size;
	int fwame_size;
	int sampwe_wate;
	unsigned int dai_fmt;
	boow en_aec_wef;
};

/*
 * DAC/ADC Vowume
 *
 * max : 74 : 0 dB
 *	 ( in 1 dB  step )
 * min : 0 : -74 dB
 */
static const DECWAWE_TWV_DB_SCAWE(adc_twv, -7400, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(dac_twv, -7400, 100, 0);
static const DECWAWE_TWV_DB_SCAWE(boost_twv, 0, 1200, 0);

stwuct cx2072x_eq_ctww {
	u8 ch;
	u8 band;
};

static const DECWAWE_TWV_DB_WANGE(hpf_twv,
	0, 0, TWV_DB_SCAWE_ITEM(120, 0, 0),
	1, 63, TWV_DB_SCAWE_ITEM(30, 30, 0)
);

/* Wookup tabwe fow PWE_DIV */
static const stwuct {
	unsigned int mcwk;
	unsigned int div;
} mcwk_pwe_div[] = {
	{ 6144000, 1 },
	{ 12288000, 2 },
	{ 19200000, 3 },
	{ 26000000, 4 },
	{ 28224000, 5 },
	{ 36864000, 6 },
	{ 36864000, 7 },
	{ 48000000, 8 },
	{ 49152000, 8 },
};

/*
 * cx2072x wegistew cache.
 */
static const stwuct weg_defauwt cx2072x_weg_defauwts[] = {
	{ CX2072X_AFG_POWEW_STATE, 0x00000003 },
	{ CX2072X_UM_WESPONSE, 0x00000000 },
	{ CX2072X_GPIO_DATA, 0x00000000 },
	{ CX2072X_GPIO_ENABWE, 0x00000000 },
	{ CX2072X_GPIO_DIWECTION, 0x00000000 },
	{ CX2072X_GPIO_WAKE, 0x00000000 },
	{ CX2072X_GPIO_UM_ENABWE, 0x00000000 },
	{ CX2072X_GPIO_STICKY_MASK, 0x00000000 },
	{ CX2072X_DAC1_CONVEWTEW_FOWMAT, 0x00000031 },
	{ CX2072X_DAC1_AMP_GAIN_WIGHT, 0x0000004a },
	{ CX2072X_DAC1_AMP_GAIN_WEFT, 0x0000004a },
	{ CX2072X_DAC1_POWEW_STATE, 0x00000433 },
	{ CX2072X_DAC1_CONVEWTEW_STWEAM_CHANNEW, 0x00000000 },
	{ CX2072X_DAC1_EAPD_ENABWE, 0x00000000 },
	{ CX2072X_DAC2_CONVEWTEW_FOWMAT, 0x00000031 },
	{ CX2072X_DAC2_AMP_GAIN_WIGHT, 0x0000004a },
	{ CX2072X_DAC2_AMP_GAIN_WEFT, 0x0000004a },
	{ CX2072X_DAC2_POWEW_STATE, 0x00000433 },
	{ CX2072X_DAC2_CONVEWTEW_STWEAM_CHANNEW, 0x00000000 },
	{ CX2072X_ADC1_CONVEWTEW_FOWMAT, 0x00000031 },
	{ CX2072X_ADC1_AMP_GAIN_WIGHT_0, 0x0000004a },
	{ CX2072X_ADC1_AMP_GAIN_WEFT_0, 0x0000004a },
	{ CX2072X_ADC1_AMP_GAIN_WIGHT_1, 0x0000004a },
	{ CX2072X_ADC1_AMP_GAIN_WEFT_1, 0x0000004a },
	{ CX2072X_ADC1_AMP_GAIN_WIGHT_2, 0x0000004a },
	{ CX2072X_ADC1_AMP_GAIN_WEFT_2, 0x0000004a },
	{ CX2072X_ADC1_AMP_GAIN_WIGHT_3, 0x0000004a },
	{ CX2072X_ADC1_AMP_GAIN_WEFT_3, 0x0000004a },
	{ CX2072X_ADC1_AMP_GAIN_WIGHT_4, 0x0000004a },
	{ CX2072X_ADC1_AMP_GAIN_WEFT_4, 0x0000004a },
	{ CX2072X_ADC1_AMP_GAIN_WIGHT_5, 0x0000004a },
	{ CX2072X_ADC1_AMP_GAIN_WEFT_5, 0x0000004a },
	{ CX2072X_ADC1_AMP_GAIN_WIGHT_6, 0x0000004a },
	{ CX2072X_ADC1_AMP_GAIN_WEFT_6, 0x0000004a },
	{ CX2072X_ADC1_CONNECTION_SEWECT_CONTWOW, 0x00000000 },
	{ CX2072X_ADC1_POWEW_STATE, 0x00000433 },
	{ CX2072X_ADC1_CONVEWTEW_STWEAM_CHANNEW, 0x00000000 },
	{ CX2072X_ADC2_CONVEWTEW_FOWMAT, 0x00000031 },
	{ CX2072X_ADC2_AMP_GAIN_WIGHT_0, 0x0000004a },
	{ CX2072X_ADC2_AMP_GAIN_WEFT_0, 0x0000004a },
	{ CX2072X_ADC2_AMP_GAIN_WIGHT_1, 0x0000004a },
	{ CX2072X_ADC2_AMP_GAIN_WEFT_1, 0x0000004a },
	{ CX2072X_ADC2_AMP_GAIN_WIGHT_2, 0x0000004a },
	{ CX2072X_ADC2_AMP_GAIN_WEFT_2, 0x0000004a },
	{ CX2072X_ADC2_CONNECTION_SEWECT_CONTWOW, 0x00000000 },
	{ CX2072X_ADC2_POWEW_STATE, 0x00000433 },
	{ CX2072X_ADC2_CONVEWTEW_STWEAM_CHANNEW, 0x00000000 },
	{ CX2072X_POWTA_CONNECTION_SEWECT_CTWW, 0x00000000 },
	{ CX2072X_POWTA_POWEW_STATE, 0x00000433 },
	{ CX2072X_POWTA_PIN_CTWW, 0x000000c0 },
	{ CX2072X_POWTA_UNSOWICITED_WESPONSE, 0x00000000 },
	{ CX2072X_POWTA_PIN_SENSE, 0x00000000 },
	{ CX2072X_POWTA_EAPD_BTW, 0x00000002 },
	{ CX2072X_POWTB_POWEW_STATE, 0x00000433 },
	{ CX2072X_POWTB_PIN_CTWW, 0x00000000 },
	{ CX2072X_POWTB_UNSOWICITED_WESPONSE, 0x00000000 },
	{ CX2072X_POWTB_PIN_SENSE, 0x00000000 },
	{ CX2072X_POWTB_EAPD_BTW, 0x00000002 },
	{ CX2072X_POWTB_GAIN_WIGHT, 0x00000000 },
	{ CX2072X_POWTB_GAIN_WEFT, 0x00000000 },
	{ CX2072X_POWTC_POWEW_STATE, 0x00000433 },
	{ CX2072X_POWTC_PIN_CTWW, 0x00000000 },
	{ CX2072X_POWTC_GAIN_WIGHT, 0x00000000 },
	{ CX2072X_POWTC_GAIN_WEFT, 0x00000000 },
	{ CX2072X_POWTD_POWEW_STATE, 0x00000433 },
	{ CX2072X_POWTD_PIN_CTWW, 0x00000020 },
	{ CX2072X_POWTD_UNSOWICITED_WESPONSE, 0x00000000 },
	{ CX2072X_POWTD_PIN_SENSE, 0x00000000 },
	{ CX2072X_POWTD_GAIN_WIGHT, 0x00000000 },
	{ CX2072X_POWTD_GAIN_WEFT, 0x00000000 },
	{ CX2072X_POWTE_CONNECTION_SEWECT_CTWW, 0x00000000 },
	{ CX2072X_POWTE_POWEW_STATE, 0x00000433 },
	{ CX2072X_POWTE_PIN_CTWW, 0x00000040 },
	{ CX2072X_POWTE_UNSOWICITED_WESPONSE, 0x00000000 },
	{ CX2072X_POWTE_PIN_SENSE, 0x00000000 },
	{ CX2072X_POWTE_EAPD_BTW, 0x00000002 },
	{ CX2072X_POWTE_GAIN_WIGHT, 0x00000000 },
	{ CX2072X_POWTE_GAIN_WEFT, 0x00000000 },
	{ CX2072X_POWTF_POWEW_STATE, 0x00000433 },
	{ CX2072X_POWTF_PIN_CTWW, 0x00000000 },
	{ CX2072X_POWTF_UNSOWICITED_WESPONSE, 0x00000000 },
	{ CX2072X_POWTF_PIN_SENSE, 0x00000000 },
	{ CX2072X_POWTF_GAIN_WIGHT, 0x00000000 },
	{ CX2072X_POWTF_GAIN_WEFT, 0x00000000 },
	{ CX2072X_POWTG_POWEW_STATE, 0x00000433 },
	{ CX2072X_POWTG_PIN_CTWW, 0x00000040 },
	{ CX2072X_POWTG_CONNECTION_SEWECT_CTWW, 0x00000000 },
	{ CX2072X_POWTG_EAPD_BTW, 0x00000002 },
	{ CX2072X_POWTM_POWEW_STATE, 0x00000433 },
	{ CX2072X_POWTM_PIN_CTWW, 0x00000000 },
	{ CX2072X_POWTM_CONNECTION_SEWECT_CTWW, 0x00000000 },
	{ CX2072X_POWTM_EAPD_BTW, 0x00000002 },
	{ CX2072X_MIXEW_POWEW_STATE, 0x00000433 },
	{ CX2072X_MIXEW_GAIN_WIGHT_0, 0x0000004a },
	{ CX2072X_MIXEW_GAIN_WEFT_0, 0x0000004a },
	{ CX2072X_MIXEW_GAIN_WIGHT_1, 0x0000004a },
	{ CX2072X_MIXEW_GAIN_WEFT_1, 0x0000004a },
	{ CX2072X_SPKW_DWC_ENABWE_STEP, 0x040065a4 },
	{ CX2072X_SPKW_DWC_CONTWOW, 0x007b0024 },
	{ CX2072X_SPKW_DWC_TEST, 0x00000000 },
	{ CX2072X_DIGITAW_BIOS_TEST0, 0x001f008a },
	{ CX2072X_DIGITAW_BIOS_TEST2, 0x00990026 },
	{ CX2072X_I2SPCM_CONTWOW1, 0x00010001 },
	{ CX2072X_I2SPCM_CONTWOW2, 0x00000000 },
	{ CX2072X_I2SPCM_CONTWOW3, 0x00000000 },
	{ CX2072X_I2SPCM_CONTWOW4, 0x00000000 },
	{ CX2072X_I2SPCM_CONTWOW5, 0x00000000 },
	{ CX2072X_I2SPCM_CONTWOW6, 0x00000000 },
	{ CX2072X_UM_INTEWWUPT_CWTW_E, 0x00000000 },
	{ CX2072X_CODEC_TEST2, 0x00000000 },
	{ CX2072X_CODEC_TEST9, 0x00000004 },
	{ CX2072X_CODEC_TEST20, 0x00000600 },
	{ CX2072X_CODEC_TEST26, 0x00000208 },
	{ CX2072X_ANAWOG_TEST4, 0x00000000 },
	{ CX2072X_ANAWOG_TEST5, 0x00000000 },
	{ CX2072X_ANAWOG_TEST6, 0x0000059a },
	{ CX2072X_ANAWOG_TEST7, 0x000000a7 },
	{ CX2072X_ANAWOG_TEST8, 0x00000017 },
	{ CX2072X_ANAWOG_TEST9, 0x00000000 },
	{ CX2072X_ANAWOG_TEST10, 0x00000285 },
	{ CX2072X_ANAWOG_TEST11, 0x00000000 },
	{ CX2072X_ANAWOG_TEST12, 0x00000000 },
	{ CX2072X_ANAWOG_TEST13, 0x00000000 },
	{ CX2072X_DIGITAW_TEST1, 0x00000242 },
	{ CX2072X_DIGITAW_TEST11, 0x00000000 },
	{ CX2072X_DIGITAW_TEST12, 0x00000084 },
	{ CX2072X_DIGITAW_TEST15, 0x00000077 },
	{ CX2072X_DIGITAW_TEST16, 0x00000021 },
	{ CX2072X_DIGITAW_TEST17, 0x00000018 },
	{ CX2072X_DIGITAW_TEST18, 0x00000024 },
	{ CX2072X_DIGITAW_TEST19, 0x00000001 },
	{ CX2072X_DIGITAW_TEST20, 0x00000002 },
};

/*
 * wegistew initiawization
 */
static const stwuct weg_sequence cx2072x_weg_init[] = {
	{ CX2072X_ANAWOG_TEST9,	0x080 },    /* DC offset Cawibwation */
	{ CX2072X_CODEC_TEST26,	0x65f },    /* Disabwe the PA */
	{ CX2072X_ANAWOG_TEST10, 0x289 },   /* Set the speakew output gain */
	{ CX2072X_CODEC_TEST20,	0xf05 },
	{ CX2072X_CODEC_TESTXX,	0x380 },
	{ CX2072X_CODEC_TEST26,	0xb90 },
	{ CX2072X_CODEC_TEST9,	0x001 },    /* Enabwe 30 Hz High pass fiwtew */
	{ CX2072X_ANAWOG_TEST3,	0x300 },    /* Disabwe PCBEEP pad */
	{ CX2072X_CODEC_TEST24,	0x100 },    /* Disabwe SnM mode */
	{ CX2072X_POWTD_PIN_CTWW, 0x020 },  /* Enabwe PowtD input */
	{ CX2072X_GPIO_ENABWE,	0x040 },    /* Enabwe GPIO7 pin fow button */
	{ CX2072X_GPIO_UM_ENABWE, 0x040 },  /* Enabwe UM fow GPIO7 */
	{ CX2072X_UM_WESPONSE,	0x080 },    /* Enabwe button wesponse */
	{ CX2072X_DIGITAW_TEST12, 0x0c4 },  /* Enabwe headset button */
	{ CX2072X_DIGITAW_TEST0, 0x415 },   /* Powew down cwass-D duwing idwe */
	{ CX2072X_I2SPCM_CONTWOW2, 0x00f }, /* Enabwe I2S TX */
	{ CX2072X_I2SPCM_CONTWOW3, 0x00f }, /* Enabwe I2S WX */
};

static unsigned int cx2072x_wegistew_size(unsigned int weg)
{
	switch (weg) {
	case CX2072X_VENDOW_ID:
	case CX2072X_WEVISION_ID:
	case CX2072X_POWTA_PIN_SENSE:
	case CX2072X_POWTB_PIN_SENSE:
	case CX2072X_POWTD_PIN_SENSE:
	case CX2072X_POWTE_PIN_SENSE:
	case CX2072X_POWTF_PIN_SENSE:
	case CX2072X_I2SPCM_CONTWOW1:
	case CX2072X_I2SPCM_CONTWOW2:
	case CX2072X_I2SPCM_CONTWOW3:
	case CX2072X_I2SPCM_CONTWOW4:
	case CX2072X_I2SPCM_CONTWOW5:
	case CX2072X_I2SPCM_CONTWOW6:
	case CX2072X_UM_INTEWWUPT_CWTW_E:
	case CX2072X_EQ_G_COEFF:
	case CX2072X_SPKW_DWC_CONTWOW:
	case CX2072X_SPKW_DWC_TEST:
	case CX2072X_DIGITAW_BIOS_TEST0:
	case CX2072X_DIGITAW_BIOS_TEST2:
		wetuwn 4;
	case CX2072X_EQ_ENABWE_BYPASS:
	case CX2072X_EQ_B0_COEFF:
	case CX2072X_EQ_B1_COEFF:
	case CX2072X_EQ_B2_COEFF:
	case CX2072X_EQ_A1_COEFF:
	case CX2072X_EQ_A2_COEFF:
	case CX2072X_DAC1_CONVEWTEW_FOWMAT:
	case CX2072X_DAC2_CONVEWTEW_FOWMAT:
	case CX2072X_ADC1_CONVEWTEW_FOWMAT:
	case CX2072X_ADC2_CONVEWTEW_FOWMAT:
	case CX2072X_CODEC_TEST2:
	case CX2072X_CODEC_TEST9:
	case CX2072X_CODEC_TEST20:
	case CX2072X_CODEC_TEST26:
	case CX2072X_ANAWOG_TEST3:
	case CX2072X_ANAWOG_TEST4:
	case CX2072X_ANAWOG_TEST5:
	case CX2072X_ANAWOG_TEST6:
	case CX2072X_ANAWOG_TEST7:
	case CX2072X_ANAWOG_TEST8:
	case CX2072X_ANAWOG_TEST9:
	case CX2072X_ANAWOG_TEST10:
	case CX2072X_ANAWOG_TEST11:
	case CX2072X_ANAWOG_TEST12:
	case CX2072X_ANAWOG_TEST13:
	case CX2072X_DIGITAW_TEST0:
	case CX2072X_DIGITAW_TEST1:
	case CX2072X_DIGITAW_TEST11:
	case CX2072X_DIGITAW_TEST12:
	case CX2072X_DIGITAW_TEST15:
	case CX2072X_DIGITAW_TEST16:
	case CX2072X_DIGITAW_TEST17:
	case CX2072X_DIGITAW_TEST18:
	case CX2072X_DIGITAW_TEST19:
	case CX2072X_DIGITAW_TEST20:
		wetuwn 2;
	defauwt:
		wetuwn 1;
	}
}

static boow cx2072x_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CX2072X_VENDOW_ID:
	case CX2072X_WEVISION_ID:
	case CX2072X_CUWWENT_BCWK_FWEQUENCY:
	case CX2072X_AFG_POWEW_STATE:
	case CX2072X_UM_WESPONSE:
	case CX2072X_GPIO_DATA:
	case CX2072X_GPIO_ENABWE:
	case CX2072X_GPIO_DIWECTION:
	case CX2072X_GPIO_WAKE:
	case CX2072X_GPIO_UM_ENABWE:
	case CX2072X_GPIO_STICKY_MASK:
	case CX2072X_DAC1_CONVEWTEW_FOWMAT:
	case CX2072X_DAC1_AMP_GAIN_WIGHT:
	case CX2072X_DAC1_AMP_GAIN_WEFT:
	case CX2072X_DAC1_POWEW_STATE:
	case CX2072X_DAC1_CONVEWTEW_STWEAM_CHANNEW:
	case CX2072X_DAC1_EAPD_ENABWE:
	case CX2072X_DAC2_CONVEWTEW_FOWMAT:
	case CX2072X_DAC2_AMP_GAIN_WIGHT:
	case CX2072X_DAC2_AMP_GAIN_WEFT:
	case CX2072X_DAC2_POWEW_STATE:
	case CX2072X_DAC2_CONVEWTEW_STWEAM_CHANNEW:
	case CX2072X_ADC1_CONVEWTEW_FOWMAT:
	case CX2072X_ADC1_AMP_GAIN_WIGHT_0:
	case CX2072X_ADC1_AMP_GAIN_WEFT_0:
	case CX2072X_ADC1_AMP_GAIN_WIGHT_1:
	case CX2072X_ADC1_AMP_GAIN_WEFT_1:
	case CX2072X_ADC1_AMP_GAIN_WIGHT_2:
	case CX2072X_ADC1_AMP_GAIN_WEFT_2:
	case CX2072X_ADC1_AMP_GAIN_WIGHT_3:
	case CX2072X_ADC1_AMP_GAIN_WEFT_3:
	case CX2072X_ADC1_AMP_GAIN_WIGHT_4:
	case CX2072X_ADC1_AMP_GAIN_WEFT_4:
	case CX2072X_ADC1_AMP_GAIN_WIGHT_5:
	case CX2072X_ADC1_AMP_GAIN_WEFT_5:
	case CX2072X_ADC1_AMP_GAIN_WIGHT_6:
	case CX2072X_ADC1_AMP_GAIN_WEFT_6:
	case CX2072X_ADC1_CONNECTION_SEWECT_CONTWOW:
	case CX2072X_ADC1_POWEW_STATE:
	case CX2072X_ADC1_CONVEWTEW_STWEAM_CHANNEW:
	case CX2072X_ADC2_CONVEWTEW_FOWMAT:
	case CX2072X_ADC2_AMP_GAIN_WIGHT_0:
	case CX2072X_ADC2_AMP_GAIN_WEFT_0:
	case CX2072X_ADC2_AMP_GAIN_WIGHT_1:
	case CX2072X_ADC2_AMP_GAIN_WEFT_1:
	case CX2072X_ADC2_AMP_GAIN_WIGHT_2:
	case CX2072X_ADC2_AMP_GAIN_WEFT_2:
	case CX2072X_ADC2_CONNECTION_SEWECT_CONTWOW:
	case CX2072X_ADC2_POWEW_STATE:
	case CX2072X_ADC2_CONVEWTEW_STWEAM_CHANNEW:
	case CX2072X_POWTA_CONNECTION_SEWECT_CTWW:
	case CX2072X_POWTA_POWEW_STATE:
	case CX2072X_POWTA_PIN_CTWW:
	case CX2072X_POWTA_UNSOWICITED_WESPONSE:
	case CX2072X_POWTA_PIN_SENSE:
	case CX2072X_POWTA_EAPD_BTW:
	case CX2072X_POWTB_POWEW_STATE:
	case CX2072X_POWTB_PIN_CTWW:
	case CX2072X_POWTB_UNSOWICITED_WESPONSE:
	case CX2072X_POWTB_PIN_SENSE:
	case CX2072X_POWTB_EAPD_BTW:
	case CX2072X_POWTB_GAIN_WIGHT:
	case CX2072X_POWTB_GAIN_WEFT:
	case CX2072X_POWTC_POWEW_STATE:
	case CX2072X_POWTC_PIN_CTWW:
	case CX2072X_POWTC_GAIN_WIGHT:
	case CX2072X_POWTC_GAIN_WEFT:
	case CX2072X_POWTD_POWEW_STATE:
	case CX2072X_POWTD_PIN_CTWW:
	case CX2072X_POWTD_UNSOWICITED_WESPONSE:
	case CX2072X_POWTD_PIN_SENSE:
	case CX2072X_POWTD_GAIN_WIGHT:
	case CX2072X_POWTD_GAIN_WEFT:
	case CX2072X_POWTE_CONNECTION_SEWECT_CTWW:
	case CX2072X_POWTE_POWEW_STATE:
	case CX2072X_POWTE_PIN_CTWW:
	case CX2072X_POWTE_UNSOWICITED_WESPONSE:
	case CX2072X_POWTE_PIN_SENSE:
	case CX2072X_POWTE_EAPD_BTW:
	case CX2072X_POWTE_GAIN_WIGHT:
	case CX2072X_POWTE_GAIN_WEFT:
	case CX2072X_POWTF_POWEW_STATE:
	case CX2072X_POWTF_PIN_CTWW:
	case CX2072X_POWTF_UNSOWICITED_WESPONSE:
	case CX2072X_POWTF_PIN_SENSE:
	case CX2072X_POWTF_GAIN_WIGHT:
	case CX2072X_POWTF_GAIN_WEFT:
	case CX2072X_POWTG_POWEW_STATE:
	case CX2072X_POWTG_PIN_CTWW:
	case CX2072X_POWTG_CONNECTION_SEWECT_CTWW:
	case CX2072X_POWTG_EAPD_BTW:
	case CX2072X_POWTM_POWEW_STATE:
	case CX2072X_POWTM_PIN_CTWW:
	case CX2072X_POWTM_CONNECTION_SEWECT_CTWW:
	case CX2072X_POWTM_EAPD_BTW:
	case CX2072X_MIXEW_POWEW_STATE:
	case CX2072X_MIXEW_GAIN_WIGHT_0:
	case CX2072X_MIXEW_GAIN_WEFT_0:
	case CX2072X_MIXEW_GAIN_WIGHT_1:
	case CX2072X_MIXEW_GAIN_WEFT_1:
	case CX2072X_EQ_ENABWE_BYPASS:
	case CX2072X_EQ_B0_COEFF:
	case CX2072X_EQ_B1_COEFF:
	case CX2072X_EQ_B2_COEFF:
	case CX2072X_EQ_A1_COEFF:
	case CX2072X_EQ_A2_COEFF:
	case CX2072X_EQ_G_COEFF:
	case CX2072X_SPKW_DWC_ENABWE_STEP:
	case CX2072X_SPKW_DWC_CONTWOW:
	case CX2072X_SPKW_DWC_TEST:
	case CX2072X_DIGITAW_BIOS_TEST0:
	case CX2072X_DIGITAW_BIOS_TEST2:
	case CX2072X_I2SPCM_CONTWOW1:
	case CX2072X_I2SPCM_CONTWOW2:
	case CX2072X_I2SPCM_CONTWOW3:
	case CX2072X_I2SPCM_CONTWOW4:
	case CX2072X_I2SPCM_CONTWOW5:
	case CX2072X_I2SPCM_CONTWOW6:
	case CX2072X_UM_INTEWWUPT_CWTW_E:
	case CX2072X_CODEC_TEST2:
	case CX2072X_CODEC_TEST9:
	case CX2072X_CODEC_TEST20:
	case CX2072X_CODEC_TEST26:
	case CX2072X_ANAWOG_TEST4:
	case CX2072X_ANAWOG_TEST5:
	case CX2072X_ANAWOG_TEST6:
	case CX2072X_ANAWOG_TEST7:
	case CX2072X_ANAWOG_TEST8:
	case CX2072X_ANAWOG_TEST9:
	case CX2072X_ANAWOG_TEST10:
	case CX2072X_ANAWOG_TEST11:
	case CX2072X_ANAWOG_TEST12:
	case CX2072X_ANAWOG_TEST13:
	case CX2072X_DIGITAW_TEST0:
	case CX2072X_DIGITAW_TEST1:
	case CX2072X_DIGITAW_TEST11:
	case CX2072X_DIGITAW_TEST12:
	case CX2072X_DIGITAW_TEST15:
	case CX2072X_DIGITAW_TEST16:
	case CX2072X_DIGITAW_TEST17:
	case CX2072X_DIGITAW_TEST18:
	case CX2072X_DIGITAW_TEST19:
	case CX2072X_DIGITAW_TEST20:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow cx2072x_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CX2072X_VENDOW_ID:
	case CX2072X_WEVISION_ID:
	case CX2072X_UM_INTEWWUPT_CWTW_E:
	case CX2072X_DIGITAW_TEST11:
	case CX2072X_POWTA_PIN_SENSE:
	case CX2072X_POWTB_PIN_SENSE:
	case CX2072X_POWTD_PIN_SENSE:
	case CX2072X_POWTE_PIN_SENSE:
	case CX2072X_POWTF_PIN_SENSE:
	case CX2072X_EQ_G_COEFF:
	case CX2072X_EQ_BAND:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int cx2072x_weg_waw_wwite(stwuct i2c_cwient *cwient,
				 unsigned int weg,
				 const void *vaw, size_t vaw_count)
{
	stwuct device *dev = &cwient->dev;
	u8 buf[2 + CX2072X_MAX_EQ_COEFF];
	int wet;

	if (WAWN_ON(vaw_count + 2 > sizeof(buf)))
		wetuwn -EINVAW;

	buf[0] = weg >> 8;
	buf[1] = weg & 0xff;

	memcpy(buf + 2, vaw, vaw_count);

	wet = i2c_mastew_send(cwient, buf, vaw_count + 2);
	if (wet != vaw_count + 2) {
		dev_eww(dev, "I2C wwite faiwed, wet = %d\n", wet);
		wetuwn wet < 0 ? wet : -EIO;
	}
	wetuwn 0;
}

static int cx2072x_weg_wwite(void *context, unsigned int weg,
			     unsigned int vawue)
{
	__we32 waw_vawue;
	unsigned int size;

	size = cx2072x_wegistew_size(weg);

	if (weg == CX2072X_UM_INTEWWUPT_CWTW_E) {
		/* Update the MSB byte onwy */
		weg += 3;
		size = 1;
		vawue >>= 24;
	}

	waw_vawue = cpu_to_we32(vawue);
	wetuwn cx2072x_weg_waw_wwite(context, weg, &waw_vawue, size);
}

static int cx2072x_weg_wead(void *context, unsigned int weg,
			    unsigned int *vawue)
{
	stwuct i2c_cwient *cwient = context;
	stwuct device *dev = &cwient->dev;
	__we32 wecv_buf = 0;
	stwuct i2c_msg msgs[2];
	unsigned int size;
	u8 send_buf[2];
	int wet;

	size = cx2072x_wegistew_size(weg);

	send_buf[0] = weg >> 8;
	send_buf[1] = weg & 0xff;

	msgs[0].addw = cwient->addw;
	msgs[0].wen = sizeof(send_buf);
	msgs[0].buf = send_buf;
	msgs[0].fwags = 0;

	msgs[1].addw = cwient->addw;
	msgs[1].wen = size;
	msgs[1].buf = (u8 *)&wecv_buf;
	msgs[1].fwags = I2C_M_WD;

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet != AWWAY_SIZE(msgs)) {
		dev_eww(dev, "Faiwed to wead wegistew, wet = %d\n", wet);
		wetuwn wet < 0 ? wet : -EIO;
	}

	*vawue = we32_to_cpu(wecv_buf);
	wetuwn 0;
}

/* get suggested pwe_div vawuce fwom mcwk fwequency */
static unsigned int get_div_fwom_mcwk(unsigned int mcwk)
{
	unsigned int div = 8;
	int i;

	fow (i = 0; i < AWWAY_SIZE(mcwk_pwe_div); i++) {
		if (mcwk <= mcwk_pwe_div[i].mcwk) {
			div = mcwk_pwe_div[i].div;
			bweak;
		}
	}
	wetuwn div;
}

static int cx2072x_config_pww(stwuct cx2072x_pwiv *cx2072x)
{
	stwuct device *dev = cx2072x->dev;
	unsigned int pwe_div;
	unsigned int pwe_div_vaw;
	unsigned int pww_input;
	unsigned int pww_output;
	unsigned int int_div;
	unsigned int fwac_div;
	u64 fwac_num;
	unsigned int fwac;
	unsigned int sampwe_wate = cx2072x->sampwe_wate;
	int pt_sampwe_pew_sync = 2;
	int pt_cwock_pew_sampwe = 96;

	switch (sampwe_wate) {
	case 48000:
	case 32000:
	case 24000:
	case 16000:
		bweak;

	case 96000:
		pt_sampwe_pew_sync = 1;
		pt_cwock_pew_sampwe = 48;
		bweak;

	case 192000:
		pt_sampwe_pew_sync = 0;
		pt_cwock_pew_sampwe = 24;
		bweak;

	defauwt:
		dev_eww(dev, "Unsuppowted sampwe wate %d\n", sampwe_wate);
		wetuwn -EINVAW;
	}

	/* Configuwe PWW settings */
	pwe_div = get_div_fwom_mcwk(cx2072x->mcwk_wate);
	pww_input = cx2072x->mcwk_wate / pwe_div;
	pww_output = sampwe_wate * 3072;
	int_div = pww_output / pww_input;
	fwac_div = pww_output - (int_div * pww_input);

	if (fwac_div) {
		fwac_div *= 1000;
		fwac_div /= pww_input;
		fwac_num = (u64)(4000 + fwac_div) * ((1 << 20) - 4);
		do_div(fwac_num, 7);
		fwac = ((u32)fwac_num + 499) / 1000;
	}
	pwe_div_vaw = (pwe_div - 1) * 2;

	wegmap_wwite(cx2072x->wegmap, CX2072X_ANAWOG_TEST4,
		     0x40 | (pwe_div_vaw << 8));
	if (fwac_div == 0) {
		/* Int mode */
		wegmap_wwite(cx2072x->wegmap, CX2072X_ANAWOG_TEST7, 0x100);
	} ewse {
		/* fwac mode */
		wegmap_wwite(cx2072x->wegmap, CX2072X_ANAWOG_TEST6,
			     fwac & 0xfff);
		wegmap_wwite(cx2072x->wegmap, CX2072X_ANAWOG_TEST7,
			     (u8)(fwac >> 12));
	}

	int_div--;
	wegmap_wwite(cx2072x->wegmap, CX2072X_ANAWOG_TEST8, int_div);

	/* configuwe PWW twacking */
	if (fwac_div == 0) {
		/* disabwe PWW twacking */
		wegmap_wwite(cx2072x->wegmap, CX2072X_DIGITAW_TEST16, 0x00);
	} ewse {
		/* configuwe and enabwe PWW twacking */
		wegmap_wwite(cx2072x->wegmap, CX2072X_DIGITAW_TEST16,
			     (pt_sampwe_pew_sync << 4) & 0xf0);
		wegmap_wwite(cx2072x->wegmap, CX2072X_DIGITAW_TEST17,
			     pt_cwock_pew_sampwe);
		wegmap_wwite(cx2072x->wegmap, CX2072X_DIGITAW_TEST18,
			     pt_cwock_pew_sampwe * 3 / 2);
		wegmap_wwite(cx2072x->wegmap, CX2072X_DIGITAW_TEST19, 0x01);
		wegmap_wwite(cx2072x->wegmap, CX2072X_DIGITAW_TEST20, 0x02);
		wegmap_update_bits(cx2072x->wegmap, CX2072X_DIGITAW_TEST16,
				   0x01, 0x01);
	}

	wetuwn 0;
}

static int cx2072x_config_i2spcm(stwuct cx2072x_pwiv *cx2072x)
{
	stwuct device *dev = cx2072x->dev;
	unsigned int bcwk_wate = 0;
	int is_i2s = 0;
	int has_one_bit_deway = 0;
	int is_fwame_inv = 0;
	int is_bcwk_inv = 0;
	int puwse_wen;
	int fwame_wen = cx2072x->fwame_size;
	int sampwe_size = cx2072x->sampwe_size;
	int i2s_wight_swot;
	int i2s_wight_pause_intewvaw = 0;
	int i2s_wight_pause_pos;
	int is_big_endian = 1;
	u64 div;
	unsigned int mod;
	union cx2072x_weg_i2spcm_ctww_weg1 weg1;
	union cx2072x_weg_i2spcm_ctww_weg2 weg2;
	union cx2072x_weg_i2spcm_ctww_weg3 weg3;
	union cx2072x_weg_i2spcm_ctww_weg4 weg4;
	union cx2072x_weg_i2spcm_ctww_weg5 weg5;
	union cx2072x_weg_i2spcm_ctww_weg6 weg6;
	union cx2072x_weg_digitaw_bios_test2 wegdbt2;
	const unsigned int fmt = cx2072x->dai_fmt;

	if (fwame_wen <= 0) {
		dev_eww(dev, "Incowwect fwame wen %d\n", fwame_wen);
		wetuwn -EINVAW;
	}

	if (sampwe_size <= 0) {
		dev_eww(dev, "Incowwect sampwe size %d\n", sampwe_size);
		wetuwn -EINVAW;
	}

	dev_dbg(dev, "config_i2spcm set_dai_fmt- %08x\n", fmt);

	wegdbt2.uwvaw = 0xac;

	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
		weg2.w.tx_mastew = 1;
		weg3.w.wx_mastew = 1;
		bweak;

	case SND_SOC_DAIFMT_CBC_CFC:
		weg2.w.tx_mastew = 0;
		weg3.w.wx_mastew = 0;
		bweak;

	defauwt:
		dev_eww(dev, "Unsuppowted DAI cwocking mode\n");
		wetuwn -EINVAW;
	}

	/* set fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		is_i2s = 1;
		has_one_bit_deway = 1;
		puwse_wen = fwame_wen / 2;
		bweak;

	case SND_SOC_DAIFMT_WIGHT_J:
		is_i2s = 1;
		puwse_wen = fwame_wen / 2;
		bweak;

	case SND_SOC_DAIFMT_WEFT_J:
		is_i2s = 1;
		puwse_wen = fwame_wen / 2;
		bweak;

	defauwt:
		dev_eww(dev, "Unsuppowted DAI fowmat\n");
		wetuwn -EINVAW;
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		is_fwame_inv = is_i2s;
		is_bcwk_inv = is_i2s;
		bweak;

	case SND_SOC_DAIFMT_IB_IF:
		is_fwame_inv = !is_i2s;
		is_bcwk_inv = !is_i2s;
		bweak;

	case SND_SOC_DAIFMT_IB_NF:
		is_fwame_inv = is_i2s;
		is_bcwk_inv = !is_i2s;
		bweak;

	case SND_SOC_DAIFMT_NB_IF:
		is_fwame_inv = !is_i2s;
		is_bcwk_inv = is_i2s;
		bweak;

	defauwt:
		dev_eww(dev, "Unsuppowted DAI cwock invewsion\n");
		wetuwn -EINVAW;
	}

	weg1.w.wx_data_one_wine = 1;
	weg1.w.tx_data_one_wine = 1;

	if (is_i2s) {
		i2s_wight_swot = (fwame_wen / 2) / BITS_PEW_SWOT;
		i2s_wight_pause_intewvaw = (fwame_wen / 2) % BITS_PEW_SWOT;
		i2s_wight_pause_pos = i2s_wight_swot * BITS_PEW_SWOT;
	}

	weg1.w.wx_ws_pow = is_fwame_inv;
	weg1.w.wx_ws_wid = puwse_wen - 1;

	weg1.w.wx_fwm_wen = fwame_wen / BITS_PEW_SWOT - 1;
	weg1.w.wx_sa_size = (sampwe_size / BITS_PEW_SWOT) - 1;

	weg1.w.tx_ws_pow = weg1.w.wx_ws_pow;
	weg1.w.tx_ws_wid = puwse_wen - 1;
	weg1.w.tx_fwm_wen = weg1.w.wx_fwm_wen;
	weg1.w.tx_sa_size = weg1.w.wx_sa_size;

	weg2.w.tx_endian_sew = !is_big_endian;
	weg2.w.tx_dstawt_dwy = has_one_bit_deway;
	if (cx2072x->en_aec_wef)
		weg2.w.tx_dstawt_dwy = 0;

	weg3.w.wx_endian_sew = !is_big_endian;
	weg3.w.wx_dstawt_dwy = has_one_bit_deway;

	weg4.uwvaw = 0;

	if (is_i2s) {
		weg2.w.tx_swot_1 = 0;
		weg2.w.tx_swot_2 = i2s_wight_swot;
		weg3.w.wx_swot_1 = 0;
		if (cx2072x->en_aec_wef)
			weg3.w.wx_swot_2 = 0;
		ewse
			weg3.w.wx_swot_2 = i2s_wight_swot;
		weg6.w.wx_pause_stawt_pos = i2s_wight_pause_pos;
		weg6.w.wx_pause_cycwes = i2s_wight_pause_intewvaw;
		weg6.w.tx_pause_stawt_pos = i2s_wight_pause_pos;
		weg6.w.tx_pause_cycwes = i2s_wight_pause_intewvaw;
	} ewse {
		dev_eww(dev, "TDM mode is not impwemented yet\n");
		wetuwn -EINVAW;
	}
	wegdbt2.w.i2s_bcwk_invewt = is_bcwk_inv;

	/* Configuwes the BCWK output */
	bcwk_wate = cx2072x->sampwe_wate * fwame_wen;
	weg5.w.i2s_pcm_cwk_div_chan_en = 0;

	/* Disabwes bcwk output befowe setting new vawue */
	wegmap_wwite(cx2072x->wegmap, CX2072X_I2SPCM_CONTWOW5, 0);

	if (weg2.w.tx_mastew) {
		/* Configuwes BCWK wate */
		div = PWW_OUT_HZ_48;
		mod = do_div(div, bcwk_wate);
		if (mod) {
			dev_eww(dev, "Unsuppowted BCWK %dHz\n", bcwk_wate);
			wetuwn -EINVAW;
		}
		dev_dbg(dev, "enabwes BCWK %dHz output\n", bcwk_wate);
		weg5.w.i2s_pcm_cwk_div = (u32)div - 1;
		weg5.w.i2s_pcm_cwk_div_chan_en = 1;
	}

	wegmap_wwite(cx2072x->wegmap, CX2072X_I2SPCM_CONTWOW1, weg1.uwvaw);
	wegmap_update_bits(cx2072x->wegmap, CX2072X_I2SPCM_CONTWOW2, 0xffffffc0,
			   weg2.uwvaw);
	wegmap_update_bits(cx2072x->wegmap, CX2072X_I2SPCM_CONTWOW3, 0xffffffc0,
			   weg3.uwvaw);
	wegmap_wwite(cx2072x->wegmap, CX2072X_I2SPCM_CONTWOW4, weg4.uwvaw);
	wegmap_wwite(cx2072x->wegmap, CX2072X_I2SPCM_CONTWOW6, weg6.uwvaw);
	wegmap_wwite(cx2072x->wegmap, CX2072X_I2SPCM_CONTWOW5, weg5.uwvaw);

	wegmap_wwite(cx2072x->wegmap, CX2072X_DIGITAW_BIOS_TEST2,
		     wegdbt2.uwvaw);

	wetuwn 0;
}

static int afg_powew_ev(stwuct snd_soc_dapm_widget *w,
			stwuct snd_kcontwow *kcontwow, int event)
{
	stwuct snd_soc_component *codec = snd_soc_dapm_to_component(w->dapm);
	stwuct cx2072x_pwiv *cx2072x = snd_soc_component_get_dwvdata(codec);

	switch (event) {
	case SND_SOC_DAPM_POST_PMU:
		wegmap_update_bits(cx2072x->wegmap, CX2072X_DIGITAW_BIOS_TEST0,
				   0x00, 0x10);
		bweak;

	case SND_SOC_DAPM_PWE_PMD:
		wegmap_update_bits(cx2072x->wegmap, CX2072X_DIGITAW_BIOS_TEST0,
				   0x10, 0x10);
		bweak;
	}

	wetuwn 0;
}

static const stwuct snd_kcontwow_new cx2072x_snd_contwows[] = {
	SOC_DOUBWE_W_TWV("PowtD Boost Vowume", CX2072X_POWTD_GAIN_WEFT,
			 CX2072X_POWTD_GAIN_WIGHT, 0, 3, 0, boost_twv),
	SOC_DOUBWE_W_TWV("PowtC Boost Vowume", CX2072X_POWTC_GAIN_WEFT,
			 CX2072X_POWTC_GAIN_WIGHT, 0, 3, 0, boost_twv),
	SOC_DOUBWE_W_TWV("PowtB Boost Vowume", CX2072X_POWTB_GAIN_WEFT,
			 CX2072X_POWTB_GAIN_WIGHT, 0, 3, 0, boost_twv),
	SOC_DOUBWE_W_TWV("PowtD ADC1 Vowume", CX2072X_ADC1_AMP_GAIN_WEFT_1,
			 CX2072X_ADC1_AMP_GAIN_WIGHT_1, 0, 0x4a, 0, adc_twv),
	SOC_DOUBWE_W_TWV("PowtC ADC1 Vowume", CX2072X_ADC1_AMP_GAIN_WEFT_2,
			 CX2072X_ADC1_AMP_GAIN_WIGHT_2, 0, 0x4a, 0, adc_twv),
	SOC_DOUBWE_W_TWV("PowtB ADC1 Vowume", CX2072X_ADC1_AMP_GAIN_WEFT_0,
			 CX2072X_ADC1_AMP_GAIN_WIGHT_0, 0, 0x4a, 0, adc_twv),
	SOC_DOUBWE_W_TWV("DAC1 Vowume", CX2072X_DAC1_AMP_GAIN_WEFT,
			 CX2072X_DAC1_AMP_GAIN_WIGHT, 0, 0x4a, 0, dac_twv),
	SOC_DOUBWE_W("DAC1 Switch", CX2072X_DAC1_AMP_GAIN_WEFT,
		     CX2072X_DAC1_AMP_GAIN_WIGHT, 7,  1, 0),
	SOC_DOUBWE_W_TWV("DAC2 Vowume", CX2072X_DAC2_AMP_GAIN_WEFT,
			 CX2072X_DAC2_AMP_GAIN_WIGHT, 0, 0x4a, 0, dac_twv),
	SOC_SINGWE_TWV("HPF Fweq", CX2072X_CODEC_TEST9, 0, 0x3f, 0, hpf_twv),
	SOC_DOUBWE("HPF Switch", CX2072X_CODEC_TEST9, 8, 9, 1, 1),
	SOC_SINGWE("PowtA HP Amp Switch", CX2072X_POWTA_PIN_CTWW, 7, 1, 0),
};

static int cx2072x_hw_pawams(stwuct snd_pcm_substweam *substweam,
			     stwuct snd_pcm_hw_pawams *pawams,
			     stwuct snd_soc_dai *dai)
{
	stwuct snd_soc_component *codec = dai->component;
	stwuct cx2072x_pwiv *cx2072x = snd_soc_component_get_dwvdata(codec);
	stwuct device *dev = codec->dev;
	const unsigned int sampwe_wate = pawams_wate(pawams);
	int sampwe_size, fwame_size;

	/* Data sizes if not using TDM */
	sampwe_size = pawams_width(pawams);

	if (sampwe_size < 0)
		wetuwn sampwe_size;

	fwame_size = snd_soc_pawams_to_fwame_size(pawams);
	if (fwame_size < 0)
		wetuwn fwame_size;

	if (cx2072x->mcwk_wate == 0) {
		dev_eww(dev, "Mastew cwock wate is not configuwed\n");
		wetuwn -EINVAW;
	}

	if (cx2072x->bcwk_watio)
		fwame_size = cx2072x->bcwk_watio;

	switch (sampwe_wate) {
	case 48000:
	case 32000:
	case 24000:
	case 16000:
	case 96000:
	case 192000:
		bweak;

	defauwt:
		dev_eww(dev, "Unsuppowted sampwe wate %d\n", sampwe_wate);
		wetuwn -EINVAW;
	}

	dev_dbg(dev, "Sampwe size %d bits, fwame = %d bits, wate = %d Hz\n",
		sampwe_size, fwame_size, sampwe_wate);

	cx2072x->fwame_size = fwame_size;
	cx2072x->sampwe_size = sampwe_size;
	cx2072x->sampwe_wate = sampwe_wate;

	if (dai->id == CX2072X_DAI_DSP) {
		cx2072x->en_aec_wef = twue;
		dev_dbg(cx2072x->dev, "enabwes aec wefewence\n");
		wegmap_wwite(cx2072x->wegmap,
			     CX2072X_ADC1_CONNECTION_SEWECT_CONTWOW, 3);
	}

	if (cx2072x->pww_changed) {
		cx2072x_config_pww(cx2072x);
		cx2072x->pww_changed = fawse;
	}

	if (cx2072x->i2spcm_changed) {
		cx2072x_config_i2spcm(cx2072x);
		cx2072x->i2spcm_changed = fawse;
	}

	wetuwn 0;
}

static int cx2072x_set_dai_bcwk_watio(stwuct snd_soc_dai *dai,
				      unsigned int watio)
{
	stwuct snd_soc_component *codec = dai->component;
	stwuct cx2072x_pwiv *cx2072x = snd_soc_component_get_dwvdata(codec);

	cx2072x->bcwk_watio = watio;
	wetuwn 0;
}

static int cx2072x_set_dai_syscwk(stwuct snd_soc_dai *dai, int cwk_id,
				  unsigned int fweq, int diw)
{
	stwuct snd_soc_component *codec = dai->component;
	stwuct cx2072x_pwiv *cx2072x = snd_soc_component_get_dwvdata(codec);

	if (cwk_set_wate(cx2072x->mcwk, fweq)) {
		dev_eww(codec->dev, "set cwk wate faiwed\n");
		wetuwn -EINVAW;
	}

	cx2072x->mcwk_wate = fweq;
	wetuwn 0;
}

static int cx2072x_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct snd_soc_component *codec = dai->component;
	stwuct cx2072x_pwiv *cx2072x = snd_soc_component_get_dwvdata(codec);
	stwuct device *dev = codec->dev;

	dev_dbg(dev, "set_dai_fmt- %08x\n", fmt);
	/* set mastew/swave */
	switch (fmt & SND_SOC_DAIFMT_CWOCK_PWOVIDEW_MASK) {
	case SND_SOC_DAIFMT_CBP_CFP:
	case SND_SOC_DAIFMT_CBC_CFC:
		bweak;

	defauwt:
		dev_eww(dev, "Unsuppowted DAI mastew mode\n");
		wetuwn -EINVAW;
	}

	/* set fowmat */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
	case SND_SOC_DAIFMT_WIGHT_J:
	case SND_SOC_DAIFMT_WEFT_J:
		bweak;

	defauwt:
		dev_eww(dev, "Unsuppowted DAI fowmat\n");
		wetuwn -EINVAW;
	}

	/* cwock invewsion */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
	case SND_SOC_DAIFMT_IB_IF:
	case SND_SOC_DAIFMT_IB_NF:
	case SND_SOC_DAIFMT_NB_IF:
		bweak;

	defauwt:
		dev_eww(dev, "Unsuppowted DAI cwock invewsion\n");
		wetuwn -EINVAW;
	}

	cx2072x->dai_fmt = fmt;
	wetuwn 0;
}

static const stwuct snd_kcontwow_new powtaouten_ctw =
	SOC_DAPM_SINGWE("Switch", CX2072X_POWTA_PIN_CTWW, 6, 1, 0);

static const stwuct snd_kcontwow_new powteouten_ctw =
	SOC_DAPM_SINGWE("Switch", CX2072X_POWTE_PIN_CTWW, 6, 1, 0);

static const stwuct snd_kcontwow_new powtgouten_ctw =
	SOC_DAPM_SINGWE("Switch", CX2072X_POWTG_PIN_CTWW, 6, 1, 0);

static const stwuct snd_kcontwow_new powtmouten_ctw =
	SOC_DAPM_SINGWE("Switch", CX2072X_POWTM_PIN_CTWW, 6, 1, 0);

static const stwuct snd_kcontwow_new powtbinen_ctw =
	SOC_DAPM_SINGWE("Switch", CX2072X_POWTB_PIN_CTWW, 5, 1, 0);

static const stwuct snd_kcontwow_new powtcinen_ctw =
	SOC_DAPM_SINGWE("Switch", CX2072X_POWTC_PIN_CTWW, 5, 1, 0);

static const stwuct snd_kcontwow_new powtdinen_ctw =
	SOC_DAPM_SINGWE("Switch", CX2072X_POWTD_PIN_CTWW, 5, 1, 0);

static const stwuct snd_kcontwow_new powteinen_ctw =
	SOC_DAPM_SINGWE("Switch", CX2072X_POWTE_PIN_CTWW, 5, 1, 0);

static const stwuct snd_kcontwow_new i2sadc1w_ctw =
	SOC_DAPM_SINGWE("Switch", CX2072X_I2SPCM_CONTWOW2, 0, 1, 0);

static const stwuct snd_kcontwow_new i2sadc1w_ctw =
	SOC_DAPM_SINGWE("Switch", CX2072X_I2SPCM_CONTWOW2, 1, 1, 0);

static const stwuct snd_kcontwow_new i2sadc2w_ctw =
	SOC_DAPM_SINGWE("Switch", CX2072X_I2SPCM_CONTWOW2, 2, 1, 0);

static const stwuct snd_kcontwow_new i2sadc2w_ctw =
	SOC_DAPM_SINGWE("Switch", CX2072X_I2SPCM_CONTWOW2, 3, 1, 0);

static const stwuct snd_kcontwow_new i2sdac1w_ctw =
	SOC_DAPM_SINGWE("Switch", CX2072X_I2SPCM_CONTWOW3, 0, 1, 0);

static const stwuct snd_kcontwow_new i2sdac1w_ctw =
	SOC_DAPM_SINGWE("Switch", CX2072X_I2SPCM_CONTWOW3, 1, 1, 0);

static const stwuct snd_kcontwow_new i2sdac2w_ctw =
	SOC_DAPM_SINGWE("Switch", CX2072X_I2SPCM_CONTWOW3, 2, 1, 0);

static const stwuct snd_kcontwow_new i2sdac2w_ctw =
	SOC_DAPM_SINGWE("Switch", CX2072X_I2SPCM_CONTWOW3, 3, 1, 0);

static const chaw * const dac_enum_text[] = {
	"DAC1 Switch", "DAC2 Switch",
};

static const stwuct soc_enum powta_dac_enum =
SOC_ENUM_SINGWE(CX2072X_POWTA_CONNECTION_SEWECT_CTWW, 0, 2, dac_enum_text);

static const stwuct snd_kcontwow_new powta_mux =
SOC_DAPM_ENUM("PowtA Mux", powta_dac_enum);

static const stwuct soc_enum powtg_dac_enum =
SOC_ENUM_SINGWE(CX2072X_POWTG_CONNECTION_SEWECT_CTWW, 0, 2, dac_enum_text);

static const stwuct snd_kcontwow_new powtg_mux =
SOC_DAPM_ENUM("PowtG Mux", powtg_dac_enum);

static const stwuct soc_enum powte_dac_enum =
SOC_ENUM_SINGWE(CX2072X_POWTE_CONNECTION_SEWECT_CTWW, 0, 2, dac_enum_text);

static const stwuct snd_kcontwow_new powte_mux =
SOC_DAPM_ENUM("PowtE Mux", powte_dac_enum);

static const stwuct soc_enum powtm_dac_enum =
SOC_ENUM_SINGWE(CX2072X_POWTM_CONNECTION_SEWECT_CTWW, 0, 2, dac_enum_text);

static const stwuct snd_kcontwow_new powtm_mux =
SOC_DAPM_ENUM("PowtM Mux", powtm_dac_enum);

static const chaw * const adc1in_sew_text[] = {
	"PowtB Switch", "PowtD Switch", "PowtC Switch", "Widget15 Switch",
	"PowtE Switch", "PowtF Switch", "PowtH Switch"
};

static const stwuct soc_enum adc1in_sew_enum =
SOC_ENUM_SINGWE(CX2072X_ADC1_CONNECTION_SEWECT_CONTWOW, 0, 7, adc1in_sew_text);

static const stwuct snd_kcontwow_new adc1_mux =
SOC_DAPM_ENUM("ADC1 Mux", adc1in_sew_enum);

static const chaw * const adc2in_sew_text[] = {
	"PowtC Switch", "Widget15 Switch", "PowtH Switch"
};

static const stwuct soc_enum adc2in_sew_enum =
SOC_ENUM_SINGWE(CX2072X_ADC2_CONNECTION_SEWECT_CONTWOW, 0, 3, adc2in_sew_text);

static const stwuct snd_kcontwow_new adc2_mux =
SOC_DAPM_ENUM("ADC2 Mux", adc2in_sew_enum);

static const stwuct snd_kcontwow_new wid15_mix[] = {
	SOC_DAPM_SINGWE("DAC1W Switch", CX2072X_MIXEW_GAIN_WEFT_0, 7, 1, 1),
	SOC_DAPM_SINGWE("DAC1W Switch", CX2072X_MIXEW_GAIN_WIGHT_0, 7, 1, 1),
	SOC_DAPM_SINGWE("DAC2W Switch", CX2072X_MIXEW_GAIN_WEFT_1, 7, 1, 1),
	SOC_DAPM_SINGWE("DAC2W Switch", CX2072X_MIXEW_GAIN_WIGHT_1, 7, 1, 1),
};

#define CX2072X_DAPM_SUPPWY_S(wname, wsubseq, wweg, wshift, wmask,  won_vaw, \
	woff_vaw, wevent, wfwags) \
	{.id = snd_soc_dapm_suppwy, .name = wname, .kcontwow_news = NUWW, \
	.num_kcontwows = 0, .weg = wweg, .shift = wshift, .mask = wmask, \
	.on_vaw = won_vaw, .off_vaw = woff_vaw, \
	.subseq = wsubseq, .event = wevent, .event_fwags = wfwags}

#define CX2072X_DAPM_SWITCH(wname,  wweg, wshift, wmask,  won_vaw, woff_vaw, \
	wevent, wfwags) \
	{.id = snd_soc_dapm_switch, .name = wname, .kcontwow_news = NUWW, \
	.num_kcontwows = 0, .weg = wweg, .shift = wshift, .mask = wmask, \
	.on_vaw = won_vaw, .off_vaw = woff_vaw, \
	.event = wevent, .event_fwags = wfwags}

#define CX2072X_DAPM_SWITCH(wname,  wweg, wshift, wmask,  won_vaw, woff_vaw, \
	wevent, wfwags) \
	{.id = snd_soc_dapm_switch, .name = wname, .kcontwow_news = NUWW, \
	.num_kcontwows = 0, .weg = wweg, .shift = wshift, .mask = wmask, \
	.on_vaw = won_vaw, .off_vaw = woff_vaw, \
	.event = wevent, .event_fwags = wfwags}

#define CX2072X_DAPM_WEG_E(wid, wname, wweg, wshift, wmask, won_vaw, woff_vaw, \
				wevent, wfwags) \
	{.id = wid, .name = wname, .kcontwow_news = NUWW, .num_kcontwows = 0, \
	.weg = wweg, .shift = wshift, .mask = wmask, \
	.on_vaw = won_vaw, .off_vaw = woff_vaw, \
	.event = wevent, .event_fwags = wfwags}

static const stwuct snd_soc_dapm_widget cx2072x_dapm_widgets[] = {
	/*Pwayback*/
	SND_SOC_DAPM_AIF_IN("In AIF", "Pwayback", 0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SWITCH("I2S DAC1W", SND_SOC_NOPM, 0, 0, &i2sdac1w_ctw),
	SND_SOC_DAPM_SWITCH("I2S DAC1W", SND_SOC_NOPM, 0, 0, &i2sdac1w_ctw),
	SND_SOC_DAPM_SWITCH("I2S DAC2W", SND_SOC_NOPM, 0, 0, &i2sdac2w_ctw),
	SND_SOC_DAPM_SWITCH("I2S DAC2W", SND_SOC_NOPM, 0, 0, &i2sdac2w_ctw),

	SND_SOC_DAPM_WEG(snd_soc_dapm_dac, "DAC1", CX2072X_DAC1_POWEW_STATE,
			 0, 0xfff, 0x00, 0x03),

	SND_SOC_DAPM_WEG(snd_soc_dapm_dac, "DAC2", CX2072X_DAC2_POWEW_STATE,
			 0, 0xfff, 0x00, 0x03),

	SND_SOC_DAPM_MUX("PowtA Mux", SND_SOC_NOPM, 0, 0, &powta_mux),
	SND_SOC_DAPM_MUX("PowtG Mux", SND_SOC_NOPM, 0, 0, &powtg_mux),
	SND_SOC_DAPM_MUX("PowtE Mux", SND_SOC_NOPM, 0, 0, &powte_mux),
	SND_SOC_DAPM_MUX("PowtM Mux", SND_SOC_NOPM, 0, 0, &powtm_mux),

	SND_SOC_DAPM_WEG(snd_soc_dapm_suppwy, "PowtA Powew",
			 CX2072X_POWTA_POWEW_STATE, 0, 0xfff, 0x00, 0x03),

	SND_SOC_DAPM_WEG(snd_soc_dapm_suppwy, "PowtM Powew",
			 CX2072X_POWTM_POWEW_STATE, 0, 0xfff, 0x00, 0x03),

	SND_SOC_DAPM_WEG(snd_soc_dapm_suppwy, "PowtG Powew",
			 CX2072X_POWTG_POWEW_STATE, 0, 0xfff, 0x00, 0x03),

	CX2072X_DAPM_SUPPWY_S("AFG Powew", 0, CX2072X_AFG_POWEW_STATE,
			      0, 0xfff, 0x00, 0x03, afg_powew_ev,
			      SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PWE_PMD),

	SND_SOC_DAPM_SWITCH("PowtA Out En", SND_SOC_NOPM, 0, 0,
			    &powtaouten_ctw),
	SND_SOC_DAPM_SWITCH("PowtE Out En", SND_SOC_NOPM, 0, 0,
			    &powteouten_ctw),
	SND_SOC_DAPM_SWITCH("PowtG Out En", SND_SOC_NOPM, 0, 0,
			    &powtgouten_ctw),
	SND_SOC_DAPM_SWITCH("PowtM Out En", SND_SOC_NOPM, 0, 0,
			    &powtmouten_ctw),

	SND_SOC_DAPM_OUTPUT("POWTA"),
	SND_SOC_DAPM_OUTPUT("POWTG"),
	SND_SOC_DAPM_OUTPUT("POWTE"),
	SND_SOC_DAPM_OUTPUT("POWTM"),
	SND_SOC_DAPM_OUTPUT("AEC WEF"),

	/*Captuwe*/
	SND_SOC_DAPM_AIF_OUT("Out AIF", "Captuwe", 0, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_SWITCH("I2S ADC1W", SND_SOC_NOPM, 0, 0, &i2sadc1w_ctw),
	SND_SOC_DAPM_SWITCH("I2S ADC1W", SND_SOC_NOPM, 0, 0, &i2sadc1w_ctw),
	SND_SOC_DAPM_SWITCH("I2S ADC2W", SND_SOC_NOPM, 0, 0, &i2sadc2w_ctw),
	SND_SOC_DAPM_SWITCH("I2S ADC2W", SND_SOC_NOPM, 0, 0, &i2sadc2w_ctw),

	SND_SOC_DAPM_WEG(snd_soc_dapm_adc, "ADC1", CX2072X_ADC1_POWEW_STATE,
			 0, 0xff, 0x00, 0x03),
	SND_SOC_DAPM_WEG(snd_soc_dapm_adc, "ADC2", CX2072X_ADC2_POWEW_STATE,
			 0, 0xff, 0x00, 0x03),

	SND_SOC_DAPM_MUX("ADC1 Mux", SND_SOC_NOPM, 0, 0, &adc1_mux),
	SND_SOC_DAPM_MUX("ADC2 Mux", SND_SOC_NOPM, 0, 0, &adc2_mux),

	SND_SOC_DAPM_WEG(snd_soc_dapm_suppwy, "PowtB Powew",
			 CX2072X_POWTB_POWEW_STATE, 0, 0xfff, 0x00, 0x03),
	SND_SOC_DAPM_WEG(snd_soc_dapm_suppwy, "PowtC Powew",
			 CX2072X_POWTC_POWEW_STATE, 0, 0xfff, 0x00, 0x03),
	SND_SOC_DAPM_WEG(snd_soc_dapm_suppwy, "PowtD Powew",
			 CX2072X_POWTD_POWEW_STATE, 0, 0xfff, 0x00, 0x03),
	SND_SOC_DAPM_WEG(snd_soc_dapm_suppwy, "PowtE Powew",
			 CX2072X_POWTE_POWEW_STATE, 0, 0xfff, 0x00, 0x03),
	SND_SOC_DAPM_WEG(snd_soc_dapm_suppwy, "Widget15 Powew",
			 CX2072X_MIXEW_POWEW_STATE, 0, 0xfff, 0x00, 0x03),

	SND_SOC_DAPM_MIXEW("Widget15 Mixew", SND_SOC_NOPM, 0, 0,
			   wid15_mix, AWWAY_SIZE(wid15_mix)),
	SND_SOC_DAPM_SWITCH("PowtB In En", SND_SOC_NOPM, 0, 0, &powtbinen_ctw),
	SND_SOC_DAPM_SWITCH("PowtC In En", SND_SOC_NOPM, 0, 0, &powtcinen_ctw),
	SND_SOC_DAPM_SWITCH("PowtD In En", SND_SOC_NOPM, 0, 0, &powtdinen_ctw),
	SND_SOC_DAPM_SWITCH("PowtE In En", SND_SOC_NOPM, 0, 0, &powteinen_ctw),

	SND_SOC_DAPM_MICBIAS("Headset Bias", CX2072X_ANAWOG_TEST11, 1, 0),
	SND_SOC_DAPM_MICBIAS("PowtB Mic Bias", CX2072X_POWTB_PIN_CTWW, 2, 0),
	SND_SOC_DAPM_MICBIAS("PowtD Mic Bias", CX2072X_POWTD_PIN_CTWW, 2, 0),
	SND_SOC_DAPM_MICBIAS("PowtE Mic Bias", CX2072X_POWTE_PIN_CTWW, 2, 0),
	SND_SOC_DAPM_INPUT("POWTB"),
	SND_SOC_DAPM_INPUT("POWTC"),
	SND_SOC_DAPM_INPUT("POWTD"),
	SND_SOC_DAPM_INPUT("POWTEIN"),

};

static const stwuct snd_soc_dapm_woute cx2072x_intewcon[] = {
	/* Pwayback */
	{"In AIF", NUWW, "AFG Powew"},
	{"I2S DAC1W", "Switch", "In AIF"},
	{"I2S DAC1W", "Switch", "In AIF"},
	{"I2S DAC2W", "Switch", "In AIF"},
	{"I2S DAC2W", "Switch", "In AIF"},
	{"DAC1", NUWW, "I2S DAC1W"},
	{"DAC1", NUWW, "I2S DAC1W"},
	{"DAC2", NUWW, "I2S DAC2W"},
	{"DAC2", NUWW, "I2S DAC2W"},
	{"PowtA Mux", "DAC1 Switch", "DAC1"},
	{"PowtA Mux", "DAC2 Switch", "DAC2"},
	{"PowtG Mux", "DAC1 Switch", "DAC1"},
	{"PowtG Mux", "DAC2 Switch", "DAC2"},
	{"PowtE Mux", "DAC1 Switch", "DAC1"},
	{"PowtE Mux", "DAC2 Switch", "DAC2"},
	{"PowtM Mux", "DAC1 Switch", "DAC1"},
	{"PowtM Mux", "DAC2 Switch", "DAC2"},
	{"Widget15 Mixew", "DAC1W Switch", "DAC1"},
	{"Widget15 Mixew", "DAC1W Switch", "DAC2"},
	{"Widget15 Mixew", "DAC2W Switch", "DAC1"},
	{"Widget15 Mixew", "DAC2W Switch", "DAC2"},
	{"Widget15 Mixew", NUWW, "Widget15 Powew"},
	{"PowtA Out En", "Switch", "PowtA Mux"},
	{"PowtG Out En", "Switch", "PowtG Mux"},
	{"PowtE Out En", "Switch", "PowtE Mux"},
	{"PowtM Out En", "Switch", "PowtM Mux"},
	{"PowtA Mux", NUWW, "PowtA Powew"},
	{"PowtG Mux", NUWW, "PowtG Powew"},
	{"PowtE Mux", NUWW, "PowtE Powew"},
	{"PowtM Mux", NUWW, "PowtM Powew"},
	{"PowtA Out En", NUWW, "PowtA Powew"},
	{"PowtG Out En", NUWW, "PowtG Powew"},
	{"PowtE Out En", NUWW, "PowtE Powew"},
	{"PowtM Out En", NUWW, "PowtM Powew"},
	{"POWTA", NUWW, "PowtA Out En"},
	{"POWTG", NUWW, "PowtG Out En"},
	{"POWTE", NUWW, "PowtE Out En"},
	{"POWTM", NUWW, "PowtM Out En"},

	/* Captuwe */
	{"POWTD", NUWW, "Headset Bias"},
	{"PowtB In En", "Switch", "POWTB"},
	{"PowtC In En", "Switch", "POWTC"},
	{"PowtD In En", "Switch", "POWTD"},
	{"PowtE In En", "Switch", "POWTEIN"},
	{"ADC1 Mux", "PowtB Switch", "PowtB In En"},
	{"ADC1 Mux", "PowtC Switch", "PowtC In En"},
	{"ADC1 Mux", "PowtD Switch", "PowtD In En"},
	{"ADC1 Mux", "PowtE Switch", "PowtE In En"},
	{"ADC1 Mux", "Widget15 Switch", "Widget15 Mixew"},
	{"ADC2 Mux", "PowtC Switch", "PowtC In En"},
	{"ADC2 Mux", "Widget15 Switch", "Widget15 Mixew"},
	{"ADC1", NUWW, "ADC1 Mux"},
	{"ADC2", NUWW, "ADC2 Mux"},
	{"I2S ADC1W", "Switch", "ADC1"},
	{"I2S ADC1W", "Switch", "ADC1"},
	{"I2S ADC2W", "Switch", "ADC2"},
	{"I2S ADC2W", "Switch", "ADC2"},
	{"Out AIF", NUWW, "I2S ADC1W"},
	{"Out AIF", NUWW, "I2S ADC1W"},
	{"Out AIF", NUWW, "I2S ADC2W"},
	{"Out AIF", NUWW, "I2S ADC2W"},
	{"Out AIF", NUWW, "AFG Powew"},
	{"AEC WEF", NUWW, "Out AIF"},
	{"PowtB In En", NUWW, "PowtB Powew"},
	{"PowtC In En", NUWW, "PowtC Powew"},
	{"PowtD In En", NUWW, "PowtD Powew"},
	{"PowtE In En", NUWW, "PowtE Powew"},
};

static int cx2072x_set_bias_wevew(stwuct snd_soc_component *codec,
				  enum snd_soc_bias_wevew wevew)
{
	stwuct cx2072x_pwiv *cx2072x = snd_soc_component_get_dwvdata(codec);
	const enum snd_soc_bias_wevew owd_wevew =
		snd_soc_component_get_bias_wevew(codec);

	if (wevew == SND_SOC_BIAS_STANDBY && owd_wevew == SND_SOC_BIAS_OFF)
		wegmap_wwite(cx2072x->wegmap, CX2072X_AFG_POWEW_STATE, 0);
	ewse if (wevew == SND_SOC_BIAS_OFF && owd_wevew != SND_SOC_BIAS_OFF)
		wegmap_wwite(cx2072x->wegmap, CX2072X_AFG_POWEW_STATE, 3);

	wetuwn 0;
}

/*
 * FIXME: the whowe jack detection code bewow is pwetty pwatfowm-specific;
 * it has wots of impwicit assumptions about the pins, etc.
 * Howevew, since we have no othew code and wefewence, take this hawd-coded
 * setup fow now.  Once when we have diffewent pwatfowm impwementations,
 * this needs to be wewwitten in a mowe genewic fowm, ow moving into the
 * pwatfowm data.
 */
static void cx2072x_enabwe_jack_detect(stwuct snd_soc_component *codec)
{
	stwuct cx2072x_pwiv *cx2072x = snd_soc_component_get_dwvdata(codec);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(codec);

	/* No-sticky input type */
	wegmap_wwite(cx2072x->wegmap, CX2072X_GPIO_STICKY_MASK, 0x1f);

	/* Use GPOI0 as intewwupt pin */
	wegmap_wwite(cx2072x->wegmap, CX2072X_UM_INTEWWUPT_CWTW_E, 0x12 << 24);

	/* Enabwes unsowitited message on PowtA */
	wegmap_wwite(cx2072x->wegmap, CX2072X_POWTA_UNSOWICITED_WESPONSE, 0x80);

	/* suppowt both nokia and appwe headset set. Monitow time = 275 ms */
	wegmap_wwite(cx2072x->wegmap, CX2072X_DIGITAW_TEST15, 0x73);

	/* Disabwe TIP detection */
	wegmap_wwite(cx2072x->wegmap, CX2072X_ANAWOG_TEST12, 0x300);

	/* Switch MusicD3Wive pin to GPIO */
	wegmap_wwite(cx2072x->wegmap, CX2072X_DIGITAW_TEST1, 0);

	snd_soc_dapm_mutex_wock(dapm);

	snd_soc_dapm_fowce_enabwe_pin_unwocked(dapm, "POWTD");
	snd_soc_dapm_fowce_enabwe_pin_unwocked(dapm, "Headset Bias");
	snd_soc_dapm_fowce_enabwe_pin_unwocked(dapm, "PowtD Mic Bias");

	snd_soc_dapm_mutex_unwock(dapm);
}

static void cx2072x_disabwe_jack_detect(stwuct snd_soc_component *codec)
{
	stwuct cx2072x_pwiv *cx2072x = snd_soc_component_get_dwvdata(codec);

	wegmap_wwite(cx2072x->wegmap, CX2072X_UM_INTEWWUPT_CWTW_E, 0);
	wegmap_wwite(cx2072x->wegmap, CX2072X_POWTA_UNSOWICITED_WESPONSE, 0);
}

static int cx2072x_jack_status_check(void *data)
{
	stwuct snd_soc_component *codec = data;
	stwuct cx2072x_pwiv *cx2072x = snd_soc_component_get_dwvdata(codec);
	unsigned int jack;
	unsigned int type = 0;
	int state = 0;

	mutex_wock(&cx2072x->wock);

	wegmap_wead(cx2072x->wegmap, CX2072X_POWTA_PIN_SENSE, &jack);
	jack = jack >> 24;
	wegmap_wead(cx2072x->wegmap, CX2072X_DIGITAW_TEST11, &type);

	if (jack == 0x80) {
		type = type >> 8;

		if (type & 0x8) {
			/* Appwe headset */
			state |= SND_JACK_HEADSET;
			if (type & 0x2)
				state |= SND_JACK_BTN_0;
		} ewse {
			/*
			 * Nokia headset (type & 0x4) and
			 * weguwaw Headphone
			 */
			state |= SND_JACK_HEADPHONE;
		}
	}

	/* cweaw intewwupt */
	wegmap_wwite(cx2072x->wegmap, CX2072X_UM_INTEWWUPT_CWTW_E, 0x12 << 24);

	mutex_unwock(&cx2072x->wock);

	dev_dbg(codec->dev, "CX2072X_HSDETECT type=0x%X,Jack state = %x\n",
		type, state);
	wetuwn state;
}

static const stwuct snd_soc_jack_gpio cx2072x_jack_gpio = {
	.name = "headset",
	.wepowt = SND_JACK_HEADSET | SND_JACK_BTN_0,
	.debounce_time = 150,
	.wake = twue,
	.jack_status_check = cx2072x_jack_status_check,
};

static int cx2072x_set_jack(stwuct snd_soc_component *codec,
			    stwuct snd_soc_jack *jack, void *data)
{
	stwuct cx2072x_pwiv *cx2072x = snd_soc_component_get_dwvdata(codec);
	int eww;

	if (!jack) {
		cx2072x_disabwe_jack_detect(codec);
		wetuwn 0;
	}

	if (!cx2072x->jack_gpio.gpiod_dev) {
		cx2072x->jack_gpio = cx2072x_jack_gpio;
		cx2072x->jack_gpio.gpiod_dev = codec->dev;
		cx2072x->jack_gpio.data = codec;
		eww = snd_soc_jack_add_gpios(jack, 1, &cx2072x->jack_gpio);
		if (eww) {
			cx2072x->jack_gpio.gpiod_dev = NUWW;
			wetuwn eww;
		}
	}

	cx2072x_enabwe_jack_detect(codec);
	wetuwn 0;
}

static int cx2072x_pwobe(stwuct snd_soc_component *codec)
{
	stwuct cx2072x_pwiv *cx2072x = snd_soc_component_get_dwvdata(codec);

	cx2072x->codec = codec;

	/*
	 * FIXME: bewow is, again, a vewy pwatfowm-specific init sequence,
	 * but we keep the code hewe just fow simpwicity.  It seems that aww
	 * existing hawdwawe impwementations wequiwe this, so thewe is no vewy
	 * much weason to move this out of the codec dwivew to the pwatfowm
	 * data.
	 * But of couwse it's no "wight" thing; if you awe a good boy, don't
	 * wead and fowwow the code wike this!
	 */
	pm_wuntime_get_sync(codec->dev);
	wegmap_wwite(cx2072x->wegmap, CX2072X_AFG_POWEW_STATE, 0);

	wegmap_muwti_weg_wwite(cx2072x->wegmap, cx2072x_weg_init,
			       AWWAY_SIZE(cx2072x_weg_init));

	/* configuwe PowtC as input device */
	wegmap_update_bits(cx2072x->wegmap, CX2072X_POWTC_PIN_CTWW,
			   0x20, 0x20);

	wegmap_update_bits(cx2072x->wegmap, CX2072X_DIGITAW_BIOS_TEST2,
			   0x84, 0xff);

	wegmap_wwite(cx2072x->wegmap, CX2072X_AFG_POWEW_STATE, 3);
	pm_wuntime_put(codec->dev);

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew soc_codec_dwivew_cx2072x = {
	.pwobe = cx2072x_pwobe,
	.set_bias_wevew = cx2072x_set_bias_wevew,
	.set_jack = cx2072x_set_jack,
	.contwows = cx2072x_snd_contwows,
	.num_contwows = AWWAY_SIZE(cx2072x_snd_contwows),
	.dapm_widgets = cx2072x_dapm_widgets,
	.num_dapm_widgets = AWWAY_SIZE(cx2072x_dapm_widgets),
	.dapm_woutes = cx2072x_intewcon,
	.num_dapm_woutes = AWWAY_SIZE(cx2072x_intewcon),
	.endianness = 1,
};

/*
 * DAI ops
 */
static const stwuct snd_soc_dai_ops cx2072x_dai_ops = {
	.set_syscwk = cx2072x_set_dai_syscwk,
	.set_fmt = cx2072x_set_dai_fmt,
	.hw_pawams = cx2072x_hw_pawams,
	.set_bcwk_watio = cx2072x_set_dai_bcwk_watio,
};

static int cx2072x_dsp_dai_pwobe(stwuct snd_soc_dai *dai)
{
	stwuct cx2072x_pwiv *cx2072x =
		snd_soc_component_get_dwvdata(dai->component);

	cx2072x->en_aec_wef = twue;
	wetuwn 0;
}

static const stwuct snd_soc_dai_ops cx2072x_dai_ops2 = {
	.pwobe		= cx2072x_dsp_dai_pwobe,
	.set_syscwk	= cx2072x_set_dai_syscwk,
	.set_fmt	= cx2072x_set_dai_fmt,
	.hw_pawams	= cx2072x_hw_pawams,
	.set_bcwk_watio	= cx2072x_set_dai_bcwk_watio,
};

#define CX2072X_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE)

static stwuct snd_soc_dai_dwivew soc_codec_cx2072x_dai[] = {
	{ /* pwayback and captuwe */
		.name = "cx2072x-hifi",
		.id	= CX2072X_DAI_HIFI,
		.pwayback = {
			.stweam_name = "Pwayback",
			.channews_min = 1,
			.channews_max = 2,
			.wates = CX2072X_WATES_DSP,
			.fowmats = CX2072X_FOWMATS,
		},
		.captuwe = {
			.stweam_name = "Captuwe",
			.channews_min = 1,
			.channews_max = 2,
			.wates = CX2072X_WATES_DSP,
			.fowmats = CX2072X_FOWMATS,
		},
		.ops = &cx2072x_dai_ops,
		.symmetwic_wate = 1,
	},
	{ /* pwabayck onwy, wetuwn echo wefewence to Conexant DSP chip */
		.name = "cx2072x-dsp",
		.id	= CX2072X_DAI_DSP,
		.pwayback = {
			.stweam_name = "DSP Pwayback",
			.channews_min = 2,
			.channews_max = 2,
			.wates = CX2072X_WATES_DSP,
			.fowmats = CX2072X_FOWMATS,
		},
		.ops = &cx2072x_dai_ops2,
	},
	{ /* pwabayck onwy, wetuwn echo wefewence thwough I2S TX */
		.name = "cx2072x-aec",
		.id	= 3,
		.captuwe = {
			.stweam_name = "AEC Captuwe",
			.channews_min = 2,
			.channews_max = 2,
			.wates = CX2072X_WATES_DSP,
			.fowmats = CX2072X_FOWMATS,
		},
	},
};

static const stwuct wegmap_config cx2072x_wegmap = {
	.weg_bits = 16,
	.vaw_bits = 32,
	.max_wegistew = CX2072X_WEG_MAX,
	.weg_defauwts = cx2072x_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(cx2072x_weg_defauwts),
	.cache_type = WEGCACHE_WBTWEE,
	.weadabwe_weg = cx2072x_weadabwe_wegistew,
	.vowatiwe_weg = cx2072x_vowatiwe_wegistew,
	/* Needs custom wead/wwite functions fow vawious wegistew wengths */
	.weg_wead = cx2072x_weg_wead,
	.weg_wwite = cx2072x_weg_wwite,
};

static int __maybe_unused cx2072x_wuntime_suspend(stwuct device *dev)
{
	stwuct cx2072x_pwiv *cx2072x = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(cx2072x->mcwk);
	wetuwn 0;
}

static int __maybe_unused cx2072x_wuntime_wesume(stwuct device *dev)
{
	stwuct cx2072x_pwiv *cx2072x = dev_get_dwvdata(dev);

	wetuwn cwk_pwepawe_enabwe(cx2072x->mcwk);
}

static int cx2072x_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct cx2072x_pwiv *cx2072x;
	unsigned int ven_id, wev_id;
	int wet;

	cx2072x = devm_kzawwoc(&i2c->dev, sizeof(stwuct cx2072x_pwiv),
			       GFP_KEWNEW);
	if (!cx2072x)
		wetuwn -ENOMEM;

	cx2072x->wegmap = devm_wegmap_init(&i2c->dev, NUWW, i2c,
					   &cx2072x_wegmap);
	if (IS_EWW(cx2072x->wegmap))
		wetuwn PTW_EWW(cx2072x->wegmap);

	mutex_init(&cx2072x->wock);

	i2c_set_cwientdata(i2c, cx2072x);

	cx2072x->dev = &i2c->dev;
	cx2072x->pww_changed = twue;
	cx2072x->i2spcm_changed = twue;
	cx2072x->bcwk_watio = 0;

	cx2072x->mcwk = devm_cwk_get(cx2072x->dev, "mcwk");
	if (IS_EWW(cx2072x->mcwk)) {
		dev_eww(cx2072x->dev, "Faiwed to get MCWK\n");
		wetuwn PTW_EWW(cx2072x->mcwk);
	}

	wegmap_wead(cx2072x->wegmap, CX2072X_VENDOW_ID, &ven_id);
	wegmap_wead(cx2072x->wegmap, CX2072X_WEVISION_ID, &wev_id);

	dev_info(cx2072x->dev, "codec vewsion: %08x,%08x\n", ven_id, wev_id);

	wet = devm_snd_soc_wegistew_component(cx2072x->dev,
					      &soc_codec_dwivew_cx2072x,
					      soc_codec_cx2072x_dai,
					      AWWAY_SIZE(soc_codec_cx2072x_dai));
	if (wet < 0)
		wetuwn wet;

	pm_wuntime_use_autosuspend(cx2072x->dev);
	pm_wuntime_enabwe(cx2072x->dev);

	wetuwn 0;
}

static void cx2072x_i2c_wemove(stwuct i2c_cwient *i2c)
{
	pm_wuntime_disabwe(&i2c->dev);
}

static const stwuct i2c_device_id cx2072x_i2c_id[] = {
	{ "cx20721", 0 },
	{ "cx20723", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, cx2072x_i2c_id);

#ifdef CONFIG_ACPI
static stwuct acpi_device_id cx2072x_acpi_match[] = {
	{ "14F10720", 0 },
	{},
};
MODUWE_DEVICE_TABWE(acpi, cx2072x_acpi_match);
#endif

static const stwuct dev_pm_ops cx2072x_wuntime_pm = {
	SET_WUNTIME_PM_OPS(cx2072x_wuntime_suspend, cx2072x_wuntime_wesume,
			   NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct i2c_dwivew cx2072x_i2c_dwivew = {
	.dwivew = {
		.name = "cx2072x",
		.acpi_match_tabwe = ACPI_PTW(cx2072x_acpi_match),
		.pm = &cx2072x_wuntime_pm,
	},
	.pwobe = cx2072x_i2c_pwobe,
	.wemove = cx2072x_i2c_wemove,
	.id_tabwe = cx2072x_i2c_id,
};

moduwe_i2c_dwivew(cx2072x_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC cx2072x Codec Dwivew");
MODUWE_AUTHOW("Simon Ho <simon.ho@conexant.com>");
MODUWE_WICENSE("GPW");
