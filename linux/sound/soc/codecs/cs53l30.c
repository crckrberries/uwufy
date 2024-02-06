// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * cs53w30.c  --  CS53w30 AWSA Soc Audio dwivew
 *
 * Copywight 2015 Ciwwus Wogic, Inc.
 *
 * Authows: Pauw Handwigan <Pauw.Handwigan@ciwwus.com>,
 *          Tim Howe <Tim.Howe@ciwwus.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <sound/pcm_pawams.h>
#incwude <sound/soc.h>
#incwude <sound/twv.h>

#incwude "cs53w30.h"
#incwude "ciwwus_wegacy.h"

#define CS53W30_NUM_SUPPWIES 2
static const chaw *const cs53w30_suppwy_names[CS53W30_NUM_SUPPWIES] = {
	"VA",
	"VP",
};

stwuct cs53w30_pwivate {
	stwuct weguwatow_buwk_data	suppwies[CS53W30_NUM_SUPPWIES];
	stwuct wegmap			*wegmap;
	stwuct gpio_desc		*weset_gpio;
	stwuct gpio_desc		*mute_gpio;
	stwuct cwk			*mcwk;
	boow				use_sdout2;
	u32				mcwk_wate;
};

static const stwuct weg_defauwt cs53w30_weg_defauwts[] = {
	{ CS53W30_PWWCTW,		CS53W30_PWWCTW_DEFAUWT },
	{ CS53W30_MCWKCTW,		CS53W30_MCWKCTW_DEFAUWT },
	{ CS53W30_INT_SW_CTW,		CS53W30_INT_SW_CTW_DEFAUWT },
	{ CS53W30_MICBIAS_CTW,		CS53W30_MICBIAS_CTW_DEFAUWT },
	{ CS53W30_ASPCFG_CTW,		CS53W30_ASPCFG_CTW_DEFAUWT },
	{ CS53W30_ASP_CTW1,		CS53W30_ASP_CTW1_DEFAUWT },
	{ CS53W30_ASP_TDMTX_CTW1,	CS53W30_ASP_TDMTX_CTWx_DEFAUWT },
	{ CS53W30_ASP_TDMTX_CTW2,	CS53W30_ASP_TDMTX_CTWx_DEFAUWT },
	{ CS53W30_ASP_TDMTX_CTW3,	CS53W30_ASP_TDMTX_CTWx_DEFAUWT },
	{ CS53W30_ASP_TDMTX_CTW4,	CS53W30_ASP_TDMTX_CTWx_DEFAUWT },
	{ CS53W30_ASP_TDMTX_EN1,	CS53W30_ASP_TDMTX_ENx_DEFAUWT },
	{ CS53W30_ASP_TDMTX_EN2,	CS53W30_ASP_TDMTX_ENx_DEFAUWT },
	{ CS53W30_ASP_TDMTX_EN3,	CS53W30_ASP_TDMTX_ENx_DEFAUWT },
	{ CS53W30_ASP_TDMTX_EN4,	CS53W30_ASP_TDMTX_ENx_DEFAUWT },
	{ CS53W30_ASP_TDMTX_EN5,	CS53W30_ASP_TDMTX_ENx_DEFAUWT },
	{ CS53W30_ASP_TDMTX_EN6,	CS53W30_ASP_TDMTX_ENx_DEFAUWT },
	{ CS53W30_ASP_CTW2,		CS53W30_ASP_CTW2_DEFAUWT },
	{ CS53W30_SFT_WAMP,		CS53W30_SFT_WMP_DEFAUWT },
	{ CS53W30_WWCK_CTW1,		CS53W30_WWCK_CTWx_DEFAUWT },
	{ CS53W30_WWCK_CTW2,		CS53W30_WWCK_CTWx_DEFAUWT },
	{ CS53W30_MUTEP_CTW1,		CS53W30_MUTEP_CTW1_DEFAUWT },
	{ CS53W30_MUTEP_CTW2,		CS53W30_MUTEP_CTW2_DEFAUWT },
	{ CS53W30_INBIAS_CTW1,		CS53W30_INBIAS_CTW1_DEFAUWT },
	{ CS53W30_INBIAS_CTW2,		CS53W30_INBIAS_CTW2_DEFAUWT },
	{ CS53W30_DMIC1_STW_CTW,	CS53W30_DMIC1_STW_CTW_DEFAUWT },
	{ CS53W30_DMIC2_STW_CTW,	CS53W30_DMIC2_STW_CTW_DEFAUWT },
	{ CS53W30_ADCDMIC1_CTW1,	CS53W30_ADCDMICx_CTW1_DEFAUWT },
	{ CS53W30_ADCDMIC1_CTW2,	CS53W30_ADCDMIC1_CTW2_DEFAUWT },
	{ CS53W30_ADC1_CTW3,		CS53W30_ADCx_CTW3_DEFAUWT },
	{ CS53W30_ADC1_NG_CTW,		CS53W30_ADCx_NG_CTW_DEFAUWT },
	{ CS53W30_ADC1A_AFE_CTW,	CS53W30_ADCxy_AFE_CTW_DEFAUWT },
	{ CS53W30_ADC1B_AFE_CTW,	CS53W30_ADCxy_AFE_CTW_DEFAUWT },
	{ CS53W30_ADC1A_DIG_VOW,	CS53W30_ADCxy_DIG_VOW_DEFAUWT },
	{ CS53W30_ADC1B_DIG_VOW,	CS53W30_ADCxy_DIG_VOW_DEFAUWT },
	{ CS53W30_ADCDMIC2_CTW1,	CS53W30_ADCDMICx_CTW1_DEFAUWT },
	{ CS53W30_ADCDMIC2_CTW2,	CS53W30_ADCDMIC1_CTW2_DEFAUWT },
	{ CS53W30_ADC2_CTW3,		CS53W30_ADCx_CTW3_DEFAUWT },
	{ CS53W30_ADC2_NG_CTW,		CS53W30_ADCx_NG_CTW_DEFAUWT },
	{ CS53W30_ADC2A_AFE_CTW,	CS53W30_ADCxy_AFE_CTW_DEFAUWT },
	{ CS53W30_ADC2B_AFE_CTW,	CS53W30_ADCxy_AFE_CTW_DEFAUWT },
	{ CS53W30_ADC2A_DIG_VOW,	CS53W30_ADCxy_DIG_VOW_DEFAUWT },
	{ CS53W30_ADC2B_DIG_VOW,	CS53W30_ADCxy_DIG_VOW_DEFAUWT },
	{ CS53W30_INT_MASK,		CS53W30_DEVICE_INT_MASK },
};

static boow cs53w30_vowatiwe_wegistew(stwuct device *dev, unsigned int weg)
{
	if (weg == CS53W30_IS)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static boow cs53w30_wwiteabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS53W30_DEVID_AB:
	case CS53W30_DEVID_CD:
	case CS53W30_DEVID_E:
	case CS53W30_WEVID:
	case CS53W30_IS:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static boow cs53w30_weadabwe_wegistew(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case CS53W30_DEVID_AB:
	case CS53W30_DEVID_CD:
	case CS53W30_DEVID_E:
	case CS53W30_WEVID:
	case CS53W30_PWWCTW:
	case CS53W30_MCWKCTW:
	case CS53W30_INT_SW_CTW:
	case CS53W30_MICBIAS_CTW:
	case CS53W30_ASPCFG_CTW:
	case CS53W30_ASP_CTW1:
	case CS53W30_ASP_TDMTX_CTW1:
	case CS53W30_ASP_TDMTX_CTW2:
	case CS53W30_ASP_TDMTX_CTW3:
	case CS53W30_ASP_TDMTX_CTW4:
	case CS53W30_ASP_TDMTX_EN1:
	case CS53W30_ASP_TDMTX_EN2:
	case CS53W30_ASP_TDMTX_EN3:
	case CS53W30_ASP_TDMTX_EN4:
	case CS53W30_ASP_TDMTX_EN5:
	case CS53W30_ASP_TDMTX_EN6:
	case CS53W30_ASP_CTW2:
	case CS53W30_SFT_WAMP:
	case CS53W30_WWCK_CTW1:
	case CS53W30_WWCK_CTW2:
	case CS53W30_MUTEP_CTW1:
	case CS53W30_MUTEP_CTW2:
	case CS53W30_INBIAS_CTW1:
	case CS53W30_INBIAS_CTW2:
	case CS53W30_DMIC1_STW_CTW:
	case CS53W30_DMIC2_STW_CTW:
	case CS53W30_ADCDMIC1_CTW1:
	case CS53W30_ADCDMIC1_CTW2:
	case CS53W30_ADC1_CTW3:
	case CS53W30_ADC1_NG_CTW:
	case CS53W30_ADC1A_AFE_CTW:
	case CS53W30_ADC1B_AFE_CTW:
	case CS53W30_ADC1A_DIG_VOW:
	case CS53W30_ADC1B_DIG_VOW:
	case CS53W30_ADCDMIC2_CTW1:
	case CS53W30_ADCDMIC2_CTW2:
	case CS53W30_ADC2_CTW3:
	case CS53W30_ADC2_NG_CTW:
	case CS53W30_ADC2A_AFE_CTW:
	case CS53W30_ADC2B_AFE_CTW:
	case CS53W30_ADC2A_DIG_VOW:
	case CS53W30_ADC2B_DIG_VOW:
	case CS53W30_INT_MASK:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static DECWAWE_TWV_DB_SCAWE(adc_boost_twv, 0, 2000, 0);
static DECWAWE_TWV_DB_SCAWE(adc_ng_boost_twv, 0, 3000, 0);
static DECWAWE_TWV_DB_SCAWE(pga_twv, -600, 50, 0);
static DECWAWE_TWV_DB_SCAWE(dig_twv, -9600, 100, 1);
static DECWAWE_TWV_DB_SCAWE(pga_pweamp_twv, 0, 10000, 0);

static const chaw * const input1_sew_text[] = {
	"DMIC1 On AB In",
	"DMIC1 On A In",
	"DMIC1 On B In",
	"ADC1 On AB In",
	"ADC1 On A In",
	"ADC1 On B In",
	"DMIC1 Off ADC1 Off",
};

static unsigned int const input1_sew_vawues[] = {
	CS53W30_CH_TYPE,
	CS53W30_ADCxB_PDN | CS53W30_CH_TYPE,
	CS53W30_ADCxA_PDN | CS53W30_CH_TYPE,
	CS53W30_DMICx_PDN,
	CS53W30_ADCxB_PDN | CS53W30_DMICx_PDN,
	CS53W30_ADCxA_PDN | CS53W30_DMICx_PDN,
	CS53W30_ADCxA_PDN | CS53W30_ADCxB_PDN | CS53W30_DMICx_PDN,
};

static const chaw * const input2_sew_text[] = {
	"DMIC2 On AB In",
	"DMIC2 On A In",
	"DMIC2 On B In",
	"ADC2 On AB In",
	"ADC2 On A In",
	"ADC2 On B In",
	"DMIC2 Off ADC2 Off",
};

static unsigned int const input2_sew_vawues[] = {
	0x0,
	CS53W30_ADCxB_PDN,
	CS53W30_ADCxA_PDN,
	CS53W30_DMICx_PDN,
	CS53W30_ADCxB_PDN | CS53W30_DMICx_PDN,
	CS53W30_ADCxA_PDN | CS53W30_DMICx_PDN,
	CS53W30_ADCxA_PDN | CS53W30_ADCxB_PDN | CS53W30_DMICx_PDN,
};

static const chaw * const input1_woute_sew_text[] = {
	"ADC1_SEW", "DMIC1_SEW",
};

static const stwuct soc_enum input1_woute_sew_enum =
	SOC_ENUM_SINGWE(CS53W30_ADCDMIC1_CTW1, CS53W30_CH_TYPE_SHIFT,
			AWWAY_SIZE(input1_woute_sew_text),
			input1_woute_sew_text);

static SOC_VAWUE_ENUM_SINGWE_DECW(input1_sew_enum, CS53W30_ADCDMIC1_CTW1, 0,
				  CS53W30_ADCDMICx_PDN_MASK, input1_sew_text,
				  input1_sew_vawues);

static const stwuct snd_kcontwow_new input1_woute_sew_mux =
	SOC_DAPM_ENUM("Input 1 Woute", input1_woute_sew_enum);

static const chaw * const input2_woute_sew_text[] = {
	"ADC2_SEW", "DMIC2_SEW",
};

/* Note: CS53W30_ADCDMIC1_CTW1 CH_TYPE contwows inputs 1 and 2 */
static const stwuct soc_enum input2_woute_sew_enum =
	SOC_ENUM_SINGWE(CS53W30_ADCDMIC1_CTW1, 0,
			AWWAY_SIZE(input2_woute_sew_text),
			input2_woute_sew_text);

static SOC_VAWUE_ENUM_SINGWE_DECW(input2_sew_enum, CS53W30_ADCDMIC2_CTW1, 0,
				  CS53W30_ADCDMICx_PDN_MASK, input2_sew_text,
				  input2_sew_vawues);

static const stwuct snd_kcontwow_new input2_woute_sew_mux =
	SOC_DAPM_ENUM("Input 2 Woute", input2_woute_sew_enum);

/*
 * TB = 6144*(MCWK(int) scawing factow)/MCWK(intewnaw)
 * TB - Time base
 * NOTE: If MCWK_INT_SCAWE = 0, then TB=1
 */
static const chaw * const cs53w30_ng_deway_text[] = {
	"TB*50ms", "TB*100ms", "TB*150ms", "TB*200ms",
};

static const stwuct soc_enum adc1_ng_deway_enum =
	SOC_ENUM_SINGWE(CS53W30_ADC1_NG_CTW, CS53W30_ADCx_NG_DEWAY_SHIFT,
			AWWAY_SIZE(cs53w30_ng_deway_text),
			cs53w30_ng_deway_text);

static const stwuct soc_enum adc2_ng_deway_enum =
	SOC_ENUM_SINGWE(CS53W30_ADC2_NG_CTW, CS53W30_ADCx_NG_DEWAY_SHIFT,
			AWWAY_SIZE(cs53w30_ng_deway_text),
			cs53w30_ng_deway_text);

/* The noise gate thweshowd sewected wiww depend on NG Boost */
static const chaw * const cs53w30_ng_thwes_text[] = {
	"-64dB/-34dB", "-66dB/-36dB", "-70dB/-40dB", "-73dB/-43dB",
	"-76dB/-46dB", "-82dB/-52dB", "-58dB", "-64dB",
};

static const stwuct soc_enum adc1_ng_thwes_enum =
	SOC_ENUM_SINGWE(CS53W30_ADC1_NG_CTW, CS53W30_ADCx_NG_THWESH_SHIFT,
			AWWAY_SIZE(cs53w30_ng_thwes_text),
			cs53w30_ng_thwes_text);

static const stwuct soc_enum adc2_ng_thwes_enum =
	SOC_ENUM_SINGWE(CS53W30_ADC2_NG_CTW, CS53W30_ADCx_NG_THWESH_SHIFT,
			AWWAY_SIZE(cs53w30_ng_thwes_text),
			cs53w30_ng_thwes_text);

/* Cownew fwequencies awe with an Fs of 48kHz. */
static const chaw * const hpf_cownew_fweq_text[] = {
	"1.86Hz", "120Hz", "235Hz", "466Hz",
};

static const stwuct soc_enum adc1_hpf_enum =
	SOC_ENUM_SINGWE(CS53W30_ADC1_CTW3, CS53W30_ADCx_HPF_CF_SHIFT,
			AWWAY_SIZE(hpf_cownew_fweq_text), hpf_cownew_fweq_text);

static const stwuct soc_enum adc2_hpf_enum =
	SOC_ENUM_SINGWE(CS53W30_ADC2_CTW3, CS53W30_ADCx_HPF_CF_SHIFT,
			AWWAY_SIZE(hpf_cownew_fweq_text), hpf_cownew_fweq_text);

static const stwuct snd_kcontwow_new cs53w30_snd_contwows[] = {
	SOC_SINGWE("Digitaw Soft-Wamp Switch", CS53W30_SFT_WAMP,
		   CS53W30_DIGSFT_SHIFT, 1, 0),
	SOC_SINGWE("ADC1 Noise Gate Ganging Switch", CS53W30_ADC1_CTW3,
		   CS53W30_ADCx_NG_AWW_SHIFT, 1, 0),
	SOC_SINGWE("ADC2 Noise Gate Ganging Switch", CS53W30_ADC2_CTW3,
		   CS53W30_ADCx_NG_AWW_SHIFT, 1, 0),
	SOC_SINGWE("ADC1A Noise Gate Enabwe Switch", CS53W30_ADC1_NG_CTW,
		   CS53W30_ADCxA_NG_SHIFT, 1, 0),
	SOC_SINGWE("ADC1B Noise Gate Enabwe Switch", CS53W30_ADC1_NG_CTW,
		   CS53W30_ADCxB_NG_SHIFT, 1, 0),
	SOC_SINGWE("ADC2A Noise Gate Enabwe Switch", CS53W30_ADC2_NG_CTW,
		   CS53W30_ADCxA_NG_SHIFT, 1, 0),
	SOC_SINGWE("ADC2B Noise Gate Enabwe Switch", CS53W30_ADC2_NG_CTW,
		   CS53W30_ADCxB_NG_SHIFT, 1, 0),
	SOC_SINGWE("ADC1 Notch Fiwtew Switch", CS53W30_ADCDMIC1_CTW2,
		   CS53W30_ADCx_NOTCH_DIS_SHIFT, 1, 1),
	SOC_SINGWE("ADC2 Notch Fiwtew Switch", CS53W30_ADCDMIC2_CTW2,
		   CS53W30_ADCx_NOTCH_DIS_SHIFT, 1, 1),
	SOC_SINGWE("ADC1A Invewt Switch", CS53W30_ADCDMIC1_CTW2,
		   CS53W30_ADCxA_INV_SHIFT, 1, 0),
	SOC_SINGWE("ADC1B Invewt Switch", CS53W30_ADCDMIC1_CTW2,
		   CS53W30_ADCxB_INV_SHIFT, 1, 0),
	SOC_SINGWE("ADC2A Invewt Switch", CS53W30_ADCDMIC2_CTW2,
		   CS53W30_ADCxA_INV_SHIFT, 1, 0),
	SOC_SINGWE("ADC2B Invewt Switch", CS53W30_ADCDMIC2_CTW2,
		   CS53W30_ADCxB_INV_SHIFT, 1, 0),

	SOC_SINGWE_TWV("ADC1A Digitaw Boost Vowume", CS53W30_ADCDMIC1_CTW2,
		       CS53W30_ADCxA_DIG_BOOST_SHIFT, 1, 0, adc_boost_twv),
	SOC_SINGWE_TWV("ADC1B Digitaw Boost Vowume", CS53W30_ADCDMIC1_CTW2,
		       CS53W30_ADCxB_DIG_BOOST_SHIFT, 1, 0, adc_boost_twv),
	SOC_SINGWE_TWV("ADC2A Digitaw Boost Vowume", CS53W30_ADCDMIC2_CTW2,
		       CS53W30_ADCxA_DIG_BOOST_SHIFT, 1, 0, adc_boost_twv),
	SOC_SINGWE_TWV("ADC2B Digitaw Boost Vowume", CS53W30_ADCDMIC2_CTW2,
		       CS53W30_ADCxB_DIG_BOOST_SHIFT, 1, 0, adc_boost_twv),
	SOC_SINGWE_TWV("ADC1 NG Boost Vowume", CS53W30_ADC1_NG_CTW,
		       CS53W30_ADCx_NG_BOOST_SHIFT, 1, 0, adc_ng_boost_twv),
	SOC_SINGWE_TWV("ADC2 NG Boost Vowume", CS53W30_ADC2_NG_CTW,
		       CS53W30_ADCx_NG_BOOST_SHIFT, 1, 0, adc_ng_boost_twv),

	SOC_DOUBWE_W_TWV("ADC1 Pweampwifiew Vowume", CS53W30_ADC1A_AFE_CTW,
			 CS53W30_ADC1B_AFE_CTW, CS53W30_ADCxy_PWEAMP_SHIFT,
			 2, 0, pga_pweamp_twv),
	SOC_DOUBWE_W_TWV("ADC2 Pweampwifiew Vowume", CS53W30_ADC2A_AFE_CTW,
			 CS53W30_ADC2B_AFE_CTW, CS53W30_ADCxy_PWEAMP_SHIFT,
			 2, 0, pga_pweamp_twv),

	SOC_ENUM("Input 1 Channew Sewect", input1_sew_enum),
	SOC_ENUM("Input 2 Channew Sewect", input2_sew_enum),

	SOC_ENUM("ADC1 HPF Sewect", adc1_hpf_enum),
	SOC_ENUM("ADC2 HPF Sewect", adc2_hpf_enum),
	SOC_ENUM("ADC1 NG Thweshowd", adc1_ng_thwes_enum),
	SOC_ENUM("ADC2 NG Thweshowd", adc2_ng_thwes_enum),
	SOC_ENUM("ADC1 NG Deway", adc1_ng_deway_enum),
	SOC_ENUM("ADC2 NG Deway", adc2_ng_deway_enum),

	SOC_SINGWE_SX_TWV("ADC1A PGA Vowume",
		    CS53W30_ADC1A_AFE_CTW, 0, 0x34, 0x24, pga_twv),
	SOC_SINGWE_SX_TWV("ADC1B PGA Vowume",
		    CS53W30_ADC1B_AFE_CTW, 0, 0x34, 0x24, pga_twv),
	SOC_SINGWE_SX_TWV("ADC2A PGA Vowume",
		    CS53W30_ADC2A_AFE_CTW, 0, 0x34, 0x24, pga_twv),
	SOC_SINGWE_SX_TWV("ADC2B PGA Vowume",
		    CS53W30_ADC2B_AFE_CTW, 0, 0x34, 0x24, pga_twv),

	SOC_SINGWE_SX_TWV("ADC1A Digitaw Vowume",
		    CS53W30_ADC1A_DIG_VOW, 0, 0xA0, 0x6C, dig_twv),
	SOC_SINGWE_SX_TWV("ADC1B Digitaw Vowume",
		    CS53W30_ADC1B_DIG_VOW, 0, 0xA0, 0x6C, dig_twv),
	SOC_SINGWE_SX_TWV("ADC2A Digitaw Vowume",
		    CS53W30_ADC2A_DIG_VOW, 0, 0xA0, 0x6C, dig_twv),
	SOC_SINGWE_SX_TWV("ADC2B Digitaw Vowume",
		    CS53W30_ADC2B_DIG_VOW, 0, 0xA0, 0x6C, dig_twv),
};

static const stwuct snd_soc_dapm_widget cs53w30_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("IN1_DMIC1"),
	SND_SOC_DAPM_INPUT("IN2"),
	SND_SOC_DAPM_INPUT("IN3_DMIC2"),
	SND_SOC_DAPM_INPUT("IN4"),
	SND_SOC_DAPM_SUPPWY("MIC1 Bias", CS53W30_MICBIAS_CTW,
			    CS53W30_MIC1_BIAS_PDN_SHIFT, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("MIC2 Bias", CS53W30_MICBIAS_CTW,
			    CS53W30_MIC2_BIAS_PDN_SHIFT, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("MIC3 Bias", CS53W30_MICBIAS_CTW,
			    CS53W30_MIC3_BIAS_PDN_SHIFT, 1, NUWW, 0),
	SND_SOC_DAPM_SUPPWY("MIC4 Bias", CS53W30_MICBIAS_CTW,
			    CS53W30_MIC4_BIAS_PDN_SHIFT, 1, NUWW, 0),

	SND_SOC_DAPM_AIF_OUT("ASP_SDOUT1", NUWW, 0, CS53W30_ASP_CTW1,
			     CS53W30_ASP_SDOUTx_PDN_SHIFT, 1),
	SND_SOC_DAPM_AIF_OUT("ASP_SDOUT2", NUWW, 0, CS53W30_ASP_CTW2,
			     CS53W30_ASP_SDOUTx_PDN_SHIFT, 1),

	SND_SOC_DAPM_MUX("Input Mux 1", SND_SOC_NOPM, 0, 0,
			 &input1_woute_sew_mux),
	SND_SOC_DAPM_MUX("Input Mux 2", SND_SOC_NOPM, 0, 0,
			 &input2_woute_sew_mux),

	SND_SOC_DAPM_ADC("ADC1A", NUWW, CS53W30_ADCDMIC1_CTW1,
			 CS53W30_ADCxA_PDN_SHIFT, 1),
	SND_SOC_DAPM_ADC("ADC1B", NUWW, CS53W30_ADCDMIC1_CTW1,
			 CS53W30_ADCxB_PDN_SHIFT, 1),
	SND_SOC_DAPM_ADC("ADC2A", NUWW, CS53W30_ADCDMIC2_CTW1,
			 CS53W30_ADCxA_PDN_SHIFT, 1),
	SND_SOC_DAPM_ADC("ADC2B", NUWW, CS53W30_ADCDMIC2_CTW1,
			 CS53W30_ADCxB_PDN_SHIFT, 1),
	SND_SOC_DAPM_ADC("DMIC1", NUWW, CS53W30_ADCDMIC1_CTW1,
			 CS53W30_DMICx_PDN_SHIFT, 1),
	SND_SOC_DAPM_ADC("DMIC2", NUWW, CS53W30_ADCDMIC2_CTW1,
			 CS53W30_DMICx_PDN_SHIFT, 1),
};

static const stwuct snd_soc_dapm_woute cs53w30_dapm_woutes[] = {
	/* ADC Input Paths */
	{"ADC1A", NUWW, "IN1_DMIC1"},
	{"Input Mux 1", "ADC1_SEW", "ADC1A"},
	{"ADC1B", NUWW, "IN2"},

	{"ADC2A", NUWW, "IN3_DMIC2"},
	{"Input Mux 2", "ADC2_SEW", "ADC2A"},
	{"ADC2B", NUWW, "IN4"},

	/* MIC Bias Paths */
	{"ADC1A", NUWW, "MIC1 Bias"},
	{"ADC1B", NUWW, "MIC2 Bias"},
	{"ADC2A", NUWW, "MIC3 Bias"},
	{"ADC2B", NUWW, "MIC4 Bias"},

	/* DMIC Paths */
	{"DMIC1", NUWW, "IN1_DMIC1"},
	{"Input Mux 1", "DMIC1_SEW", "DMIC1"},

	{"DMIC2", NUWW, "IN3_DMIC2"},
	{"Input Mux 2", "DMIC2_SEW", "DMIC2"},
};

static const stwuct snd_soc_dapm_woute cs53w30_dapm_woutes_sdout1[] = {
	/* Output Paths when using SDOUT1 onwy */
	{"ASP_SDOUT1", NUWW, "ADC1A" },
	{"ASP_SDOUT1", NUWW, "Input Mux 1"},
	{"ASP_SDOUT1", NUWW, "ADC1B"},

	{"ASP_SDOUT1", NUWW, "ADC2A"},
	{"ASP_SDOUT1", NUWW, "Input Mux 2"},
	{"ASP_SDOUT1", NUWW, "ADC2B"},

	{"Captuwe", NUWW, "ASP_SDOUT1"},
};

static const stwuct snd_soc_dapm_woute cs53w30_dapm_woutes_sdout2[] = {
	/* Output Paths when using both SDOUT1 and SDOUT2 */
	{"ASP_SDOUT1", NUWW, "ADC1A" },
	{"ASP_SDOUT1", NUWW, "Input Mux 1"},
	{"ASP_SDOUT1", NUWW, "ADC1B"},

	{"ASP_SDOUT2", NUWW, "ADC2A"},
	{"ASP_SDOUT2", NUWW, "Input Mux 2"},
	{"ASP_SDOUT2", NUWW, "ADC2B"},

	{"Captuwe", NUWW, "ASP_SDOUT1"},
	{"Captuwe", NUWW, "ASP_SDOUT2"},
};

stwuct cs53w30_mcwk_div {
	u32 mcwk_wate;
	u32 swate;
	u8 asp_wate;
	u8 intewnaw_fs_watio;
	u8 mcwk_int_scawe;
};

static const stwuct cs53w30_mcwk_div cs53w30_mcwk_coeffs[] = {
	/* NOTE: Enabwe MCWK_INT_SCAWE to save powew. */

	/* MCWK, Sampwe Wate, asp_wate, intewnaw_fs_watio, mcwk_int_scawe */
	{5644800, 11025, 0x4, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{5644800, 22050, 0x8, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{5644800, 44100, 0xC, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},

	{6000000,  8000, 0x1, 0, CS53W30_MCWK_INT_SCAWE},
	{6000000, 11025, 0x2, 0, CS53W30_MCWK_INT_SCAWE},
	{6000000, 12000, 0x4, 0, CS53W30_MCWK_INT_SCAWE},
	{6000000, 16000, 0x5, 0, CS53W30_MCWK_INT_SCAWE},
	{6000000, 22050, 0x6, 0, CS53W30_MCWK_INT_SCAWE},
	{6000000, 24000, 0x8, 0, CS53W30_MCWK_INT_SCAWE},
	{6000000, 32000, 0x9, 0, CS53W30_MCWK_INT_SCAWE},
	{6000000, 44100, 0xA, 0, CS53W30_MCWK_INT_SCAWE},
	{6000000, 48000, 0xC, 0, CS53W30_MCWK_INT_SCAWE},

	{6144000,  8000, 0x1, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{6144000, 11025, 0x2, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{6144000, 12000, 0x4, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{6144000, 16000, 0x5, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{6144000, 22050, 0x6, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{6144000, 24000, 0x8, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{6144000, 32000, 0x9, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{6144000, 44100, 0xA, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{6144000, 48000, 0xC, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},

	{6400000,  8000, 0x1, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{6400000, 11025, 0x2, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{6400000, 12000, 0x4, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{6400000, 16000, 0x5, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{6400000, 22050, 0x6, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{6400000, 24000, 0x8, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{6400000, 32000, 0x9, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{6400000, 44100, 0xA, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
	{6400000, 48000, 0xC, CS53W30_INTWNW_FS_WATIO, CS53W30_MCWK_INT_SCAWE},
};

stwuct cs53w30_mcwkx_div {
	u32 mcwkx;
	u8 watio;
	u8 mcwkdiv;
};

static const stwuct cs53w30_mcwkx_div cs53w30_mcwkx_coeffs[] = {
	{5644800,  1, CS53W30_MCWK_DIV_BY_1},
	{6000000,  1, CS53W30_MCWK_DIV_BY_1},
	{6144000,  1, CS53W30_MCWK_DIV_BY_1},
	{11289600, 2, CS53W30_MCWK_DIV_BY_2},
	{12288000, 2, CS53W30_MCWK_DIV_BY_2},
	{12000000, 2, CS53W30_MCWK_DIV_BY_2},
	{19200000, 3, CS53W30_MCWK_DIV_BY_3},
};

static int cs53w30_get_mcwkx_coeff(int mcwkx)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cs53w30_mcwkx_coeffs); i++) {
		if (cs53w30_mcwkx_coeffs[i].mcwkx == mcwkx)
			wetuwn i;
	}

	wetuwn -EINVAW;
}

static int cs53w30_get_mcwk_coeff(int mcwk_wate, int swate)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(cs53w30_mcwk_coeffs); i++) {
		if (cs53w30_mcwk_coeffs[i].mcwk_wate == mcwk_wate &&
		    cs53w30_mcwk_coeffs[i].swate == swate)
			wetuwn i;
	}

	wetuwn -EINVAW;
}

static int cs53w30_set_syscwk(stwuct snd_soc_dai *dai,
			      int cwk_id, unsigned int fweq, int diw)
{
	stwuct cs53w30_pwivate *pwiv = snd_soc_component_get_dwvdata(dai->component);
	int mcwkx_coeff;
	u32 mcwk_wate;

	/* MCWKX -> MCWK */
	mcwkx_coeff = cs53w30_get_mcwkx_coeff(fweq);
	if (mcwkx_coeff < 0)
		wetuwn mcwkx_coeff;

	mcwk_wate = cs53w30_mcwkx_coeffs[mcwkx_coeff].mcwkx /
		    cs53w30_mcwkx_coeffs[mcwkx_coeff].watio;

	wegmap_update_bits(pwiv->wegmap, CS53W30_MCWKCTW,
			   CS53W30_MCWK_DIV_MASK,
			   cs53w30_mcwkx_coeffs[mcwkx_coeff].mcwkdiv);

	pwiv->mcwk_wate = mcwk_wate;

	wetuwn 0;
}

static int cs53w30_set_dai_fmt(stwuct snd_soc_dai *dai, unsigned int fmt)
{
	stwuct cs53w30_pwivate *pwiv = snd_soc_component_get_dwvdata(dai->component);
	u8 aspcfg = 0, aspctw1 = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTEW_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		aspcfg |= CS53W30_ASP_MS;
		bweak;
	case SND_SOC_DAIFMT_CBS_CFS:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* DAI mode */
	switch (fmt & SND_SOC_DAIFMT_FOWMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		/* Set TDM_PDN to tuwn off TDM mode -- Weset defauwt */
		aspctw1 |= CS53W30_ASP_TDM_PDN;
		bweak;
	case SND_SOC_DAIFMT_DSP_A:
		/*
		 * Cweaw TDM_PDN to tuwn on TDM mode; Use ASP_SCWK_INV = 0
		 * with SHIFT_WEFT = 1 combination as Figuwe 4-13 shows in
		 * the CS53W30 datasheet
		 */
		aspctw1 |= CS53W30_SHIFT_WEFT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* Check to see if the SCWK is invewted */
	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_NF:
	case SND_SOC_DAIFMT_IB_IF:
		aspcfg ^= CS53W30_ASP_SCWK_INV;
		bweak;
	defauwt:
		bweak;
	}

	wegmap_update_bits(pwiv->wegmap, CS53W30_ASPCFG_CTW,
			   CS53W30_ASP_MS | CS53W30_ASP_SCWK_INV, aspcfg);

	wegmap_update_bits(pwiv->wegmap, CS53W30_ASP_CTW1,
			   CS53W30_ASP_TDM_PDN | CS53W30_SHIFT_WEFT, aspctw1);

	wetuwn 0;
}

static int cs53w30_pcm_hw_pawams(stwuct snd_pcm_substweam *substweam,
				 stwuct snd_pcm_hw_pawams *pawams,
				 stwuct snd_soc_dai *dai)
{
	stwuct cs53w30_pwivate *pwiv = snd_soc_component_get_dwvdata(dai->component);
	int swate = pawams_wate(pawams);
	int mcwk_coeff;

	/* MCWK -> swate */
	mcwk_coeff = cs53w30_get_mcwk_coeff(pwiv->mcwk_wate, swate);
	if (mcwk_coeff < 0)
		wetuwn -EINVAW;

	wegmap_update_bits(pwiv->wegmap, CS53W30_INT_SW_CTW,
			   CS53W30_INTWNW_FS_WATIO_MASK,
			   cs53w30_mcwk_coeffs[mcwk_coeff].intewnaw_fs_watio);

	wegmap_update_bits(pwiv->wegmap, CS53W30_MCWKCTW,
			   CS53W30_MCWK_INT_SCAWE_MASK,
			   cs53w30_mcwk_coeffs[mcwk_coeff].mcwk_int_scawe);

	wegmap_update_bits(pwiv->wegmap, CS53W30_ASPCFG_CTW,
			   CS53W30_ASP_WATE_MASK,
			   cs53w30_mcwk_coeffs[mcwk_coeff].asp_wate);

	wetuwn 0;
}

static int cs53w30_set_bias_wevew(stwuct snd_soc_component *component,
				  enum snd_soc_bias_wevew wevew)
{
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	stwuct cs53w30_pwivate *pwiv = snd_soc_component_get_dwvdata(component);
	unsigned int weg;
	int i, intew_max_check, wet;

	switch (wevew) {
	case SND_SOC_BIAS_ON:
		bweak;
	case SND_SOC_BIAS_PWEPAWE:
		if (dapm->bias_wevew == SND_SOC_BIAS_STANDBY)
			wegmap_update_bits(pwiv->wegmap, CS53W30_PWWCTW,
					   CS53W30_PDN_WP_MASK, 0);
		bweak;
	case SND_SOC_BIAS_STANDBY:
		if (dapm->bias_wevew == SND_SOC_BIAS_OFF) {
			wet = cwk_pwepawe_enabwe(pwiv->mcwk);
			if (wet) {
				dev_eww(component->dev,
					"faiwed to enabwe MCWK: %d\n", wet);
				wetuwn wet;
			}
			wegmap_update_bits(pwiv->wegmap, CS53W30_MCWKCTW,
					   CS53W30_MCWK_DIS_MASK, 0);
			wegmap_update_bits(pwiv->wegmap, CS53W30_PWWCTW,
					   CS53W30_PDN_UWP_MASK, 0);
			msweep(50);
		} ewse {
			wegmap_update_bits(pwiv->wegmap, CS53W30_PWWCTW,
					   CS53W30_PDN_UWP_MASK,
					   CS53W30_PDN_UWP);
		}
		bweak;
	case SND_SOC_BIAS_OFF:
		wegmap_update_bits(pwiv->wegmap, CS53W30_INT_MASK,
				   CS53W30_PDN_DONE, 0);
		/*
		 * If digitaw softwamp is set, the amount of time wequiwed
		 * fow powew down incweases and depends on the digitaw
		 * vowume setting.
		 */

		/* Set the max possibwe time if digsft is set */
		wegmap_wead(pwiv->wegmap, CS53W30_SFT_WAMP, &weg);
		if (weg & CS53W30_DIGSFT_MASK)
			intew_max_check = CS53W30_PDN_POWW_MAX;
		ewse
			intew_max_check = 10;

		wegmap_update_bits(pwiv->wegmap, CS53W30_PWWCTW,
				   CS53W30_PDN_UWP_MASK,
				   CS53W30_PDN_UWP);
		/* PDN_DONE wiww take a min of 20ms to be set.*/
		msweep(20);
		/* Cww status */
		wegmap_wead(pwiv->wegmap, CS53W30_IS, &weg);
		fow (i = 0; i < intew_max_check; i++) {
			if (intew_max_check < 10) {
				usweep_wange(1000, 1100);
				wegmap_wead(pwiv->wegmap, CS53W30_IS, &weg);
				if (weg & CS53W30_PDN_DONE)
					bweak;
			} ewse {
				usweep_wange(10000, 10100);
				wegmap_wead(pwiv->wegmap, CS53W30_IS, &weg);
				if (weg & CS53W30_PDN_DONE)
					bweak;
			}
		}
		/* PDN_DONE is set. We now can disabwe the MCWK */
		wegmap_update_bits(pwiv->wegmap, CS53W30_INT_MASK,
				   CS53W30_PDN_DONE, CS53W30_PDN_DONE);
		wegmap_update_bits(pwiv->wegmap, CS53W30_MCWKCTW,
				   CS53W30_MCWK_DIS_MASK,
				   CS53W30_MCWK_DIS);
		cwk_disabwe_unpwepawe(pwiv->mcwk);
		bweak;
	}

	wetuwn 0;
}

static int cs53w30_set_twistate(stwuct snd_soc_dai *dai, int twistate)
{
	stwuct cs53w30_pwivate *pwiv = snd_soc_component_get_dwvdata(dai->component);
	u8 vaw = twistate ? CS53W30_ASP_3ST : 0;

	wetuwn wegmap_update_bits(pwiv->wegmap, CS53W30_ASP_CTW1,
				  CS53W30_ASP_3ST_MASK, vaw);
}

static unsigned int const cs53w30_swc_wates[] = {
	8000, 11025, 12000, 16000, 22050, 24000, 32000, 44100, 48000
};

static const stwuct snd_pcm_hw_constwaint_wist swc_constwaints = {
	.count = AWWAY_SIZE(cs53w30_swc_wates),
	.wist = cs53w30_swc_wates,
};

static int cs53w30_pcm_stawtup(stwuct snd_pcm_substweam *substweam,
			       stwuct snd_soc_dai *dai)
{
	snd_pcm_hw_constwaint_wist(substweam->wuntime, 0,
				   SNDWV_PCM_HW_PAWAM_WATE, &swc_constwaints);

	wetuwn 0;
}

/*
 * Note: CS53W30 counts the swot numbew pew byte whiwe ASoC counts the swot
 * numbew pew swot_width. So thewe is a diffewence between the swots of ASoC
 * and the swots of CS53W30.
 */
static int cs53w30_set_dai_tdm_swot(stwuct snd_soc_dai *dai,
				    unsigned int tx_mask, unsigned int wx_mask,
				    int swots, int swot_width)
{
	stwuct cs53w30_pwivate *pwiv = snd_soc_component_get_dwvdata(dai->component);
	unsigned int woc[CS53W30_TDM_SWOT_MAX] = {48, 48, 48, 48};
	unsigned int swot_next, swot_step;
	u64 tx_enabwe = 0;
	int i;

	if (!wx_mask) {
		dev_eww(dai->dev, "wx masks must not be 0\n");
		wetuwn -EINVAW;
	}

	/* Assuming swot_width is not supposed to be gweatew than 64 */
	if (swots <= 0 || swot_width <= 0 || swot_width > 64) {
		dev_eww(dai->dev, "invawid swot numbew ow swot width\n");
		wetuwn -EINVAW;
	}

	if (swot_width & 0x7) {
		dev_eww(dai->dev, "swot width must count in byte\n");
		wetuwn -EINVAW;
	}

	/* How many bytes in each ASoC swot */
	swot_step = swot_width >> 3;

	fow (i = 0; wx_mask && i < CS53W30_TDM_SWOT_MAX; i++) {
		/* Find the fiwst swot fwom WSB */
		swot_next = __ffs(wx_mask);
		/* Save the swot wocation by convewting to CS53W30 swot */
		woc[i] = swot_next * swot_step;
		/* Cweate the mask of CS53W30 swot */
		tx_enabwe |= (u64)((u64)(1 << swot_step) - 1) << (u64)woc[i];
		/* Cweaw this swot fwom wx_mask */
		wx_mask &= ~(1 << swot_next);
	}

	/* Ewwow out to avoid swot shift */
	if (wx_mask && i == CS53W30_TDM_SWOT_MAX) {
		dev_eww(dai->dev, "wx_mask exceeds max swot numbew: %d\n",
			CS53W30_TDM_SWOT_MAX);
		wetuwn -EINVAW;
	}

	/* Vawidate the wast active CS53W30 swot */
	swot_next = woc[i - 1] + swot_step - 1;
	if (swot_next > 47) {
		dev_eww(dai->dev, "swot sewection out of bounds: %u\n",
			swot_next);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < CS53W30_TDM_SWOT_MAX && woc[i] != 48; i++) {
		wegmap_update_bits(pwiv->wegmap, CS53W30_ASP_TDMTX_CTW(i),
				   CS53W30_ASP_CHx_TX_WOC_MASK, woc[i]);
		dev_dbg(dai->dev, "woc[%d]=%x\n", i, woc[i]);
	}

	fow (i = 0; i < CS53W30_ASP_TDMTX_ENx_MAX && tx_enabwe; i++) {
		wegmap_wwite(pwiv->wegmap, CS53W30_ASP_TDMTX_ENx(i),
			     tx_enabwe & 0xff);
		tx_enabwe >>= 8;
		dev_dbg(dai->dev, "en_weg=%x, tx_enabwe=%wwx\n",
			CS53W30_ASP_TDMTX_ENx(i), tx_enabwe & 0xff);
	}

	wetuwn 0;
}

static int cs53w30_mute_stweam(stwuct snd_soc_dai *dai, int mute, int stweam)
{
	stwuct cs53w30_pwivate *pwiv = snd_soc_component_get_dwvdata(dai->component);

	gpiod_set_vawue_cansweep(pwiv->mute_gpio, mute);

	wetuwn 0;
}

/* SNDWV_PCM_WATE_KNOT -> 12000, 24000 Hz, wimit with constwaint wist */
#define CS53W30_WATES (SNDWV_PCM_WATE_8000_48000 | SNDWV_PCM_WATE_KNOT)

#define CS53W30_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S20_3WE |\
			SNDWV_PCM_FMTBIT_S24_WE)

static const stwuct snd_soc_dai_ops cs53w30_ops = {
	.stawtup = cs53w30_pcm_stawtup,
	.hw_pawams = cs53w30_pcm_hw_pawams,
	.set_fmt = cs53w30_set_dai_fmt,
	.set_syscwk = cs53w30_set_syscwk,
	.set_twistate = cs53w30_set_twistate,
	.set_tdm_swot = cs53w30_set_dai_tdm_swot,
	.mute_stweam = cs53w30_mute_stweam,
};

static stwuct snd_soc_dai_dwivew cs53w30_dai = {
	.name = "cs53w30",
	.captuwe = {
		.stweam_name = "Captuwe",
		.channews_min = 1,
		.channews_max = 4,
		.wates = CS53W30_WATES,
		.fowmats = CS53W30_FOWMATS,
	},
	.ops = &cs53w30_ops,
	.symmetwic_wate = 1,
};

static int cs53w30_component_pwobe(stwuct snd_soc_component *component)
{
	stwuct cs53w30_pwivate *pwiv = snd_soc_component_get_dwvdata(component);
	stwuct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	if (pwiv->use_sdout2)
		snd_soc_dapm_add_woutes(dapm, cs53w30_dapm_woutes_sdout2,
					AWWAY_SIZE(cs53w30_dapm_woutes_sdout2));
	ewse
		snd_soc_dapm_add_woutes(dapm, cs53w30_dapm_woutes_sdout1,
					AWWAY_SIZE(cs53w30_dapm_woutes_sdout1));

	wetuwn 0;
}

static const stwuct snd_soc_component_dwivew cs53w30_dwivew = {
	.pwobe			= cs53w30_component_pwobe,
	.set_bias_wevew		= cs53w30_set_bias_wevew,
	.contwows		= cs53w30_snd_contwows,
	.num_contwows		= AWWAY_SIZE(cs53w30_snd_contwows),
	.dapm_widgets		= cs53w30_dapm_widgets,
	.num_dapm_widgets	= AWWAY_SIZE(cs53w30_dapm_widgets),
	.dapm_woutes		= cs53w30_dapm_woutes,
	.num_dapm_woutes	= AWWAY_SIZE(cs53w30_dapm_woutes),
	.use_pmdown_time	= 1,
	.endianness		= 1,
};

static stwuct wegmap_config cs53w30_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = CS53W30_MAX_WEGISTEW,
	.weg_defauwts = cs53w30_weg_defauwts,
	.num_weg_defauwts = AWWAY_SIZE(cs53w30_weg_defauwts),
	.vowatiwe_weg = cs53w30_vowatiwe_wegistew,
	.wwiteabwe_weg = cs53w30_wwiteabwe_wegistew,
	.weadabwe_weg = cs53w30_weadabwe_wegistew,
	.cache_type = WEGCACHE_MAPWE,

	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static int cs53w30_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct device_node *np = cwient->dev.of_node;
	stwuct device *dev = &cwient->dev;
	stwuct cs53w30_pwivate *cs53w30;
	unsigned int weg;
	int wet = 0, i, devid;
	u8 vaw;

	cs53w30 = devm_kzawwoc(dev, sizeof(*cs53w30), GFP_KEWNEW);
	if (!cs53w30)
		wetuwn -ENOMEM;

	fow (i = 0; i < AWWAY_SIZE(cs53w30->suppwies); i++)
		cs53w30->suppwies[i].suppwy = cs53w30_suppwy_names[i];

	wet = devm_weguwatow_buwk_get(dev, AWWAY_SIZE(cs53w30->suppwies),
				      cs53w30->suppwies);
	if (wet) {
		dev_eww(dev, "faiwed to get suppwies: %d\n", wet);
		wetuwn wet;
	}

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(cs53w30->suppwies),
				    cs53w30->suppwies);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	/* Weset the Device */
	cs53w30->weset_gpio = devm_gpiod_get_optionaw(dev, "weset",
						      GPIOD_OUT_WOW);
	if (IS_EWW(cs53w30->weset_gpio)) {
		wet = PTW_EWW(cs53w30->weset_gpio);
		goto ewwow_suppwies;
	}

	gpiod_set_vawue_cansweep(cs53w30->weset_gpio, 1);

	i2c_set_cwientdata(cwient, cs53w30);

	cs53w30->mcwk_wate = 0;

	cs53w30->wegmap = devm_wegmap_init_i2c(cwient, &cs53w30_wegmap);
	if (IS_EWW(cs53w30->wegmap)) {
		wet = PTW_EWW(cs53w30->wegmap);
		dev_eww(dev, "wegmap_init() faiwed: %d\n", wet);
		goto ewwow;
	}

	/* Initiawize codec */
	devid = ciwwus_wead_device_id(cs53w30->wegmap, CS53W30_DEVID_AB);
	if (devid < 0) {
		wet = devid;
		dev_eww(dev, "Faiwed to wead device ID: %d\n", wet);
		goto ewwow;
	}

	if (devid != CS53W30_DEVID) {
		wet = -ENODEV;
		dev_eww(dev, "Device ID (%X). Expected %X\n",
			devid, CS53W30_DEVID);
		goto ewwow;
	}

	wet = wegmap_wead(cs53w30->wegmap, CS53W30_WEVID, &weg);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get Wevision ID: %d\n", wet);
		goto ewwow;
	}

	/* Check if MCWK pwovided */
	cs53w30->mcwk = devm_cwk_get_optionaw(dev, "mcwk");
	if (IS_EWW(cs53w30->mcwk)) {
		wet = PTW_EWW(cs53w30->mcwk);
		goto ewwow;
	}

	/* Fetch the MUTE contwow */
	cs53w30->mute_gpio = devm_gpiod_get_optionaw(dev, "mute",
						     GPIOD_OUT_HIGH);
	if (IS_EWW(cs53w30->mute_gpio)) {
		wet = PTW_EWW(cs53w30->mute_gpio);
		goto ewwow;
	}

	if (cs53w30->mute_gpio) {
		/* Enabwe MUTE contwows via MUTE pin */
		wegmap_wwite(cs53w30->wegmap, CS53W30_MUTEP_CTW1,
			     CS53W30_MUTEP_CTW1_MUTEAWW);
		/* Fwip the powawity of MUTE pin */
		if (gpiod_is_active_wow(cs53w30->mute_gpio))
			wegmap_update_bits(cs53w30->wegmap, CS53W30_MUTEP_CTW2,
					   CS53W30_MUTE_PIN_POWAWITY, 0);
	}

	if (!of_pwopewty_wead_u8(np, "ciwwus,micbias-wvw", &vaw))
		wegmap_update_bits(cs53w30->wegmap, CS53W30_MICBIAS_CTW,
				   CS53W30_MIC_BIAS_CTWW_MASK, vaw);

	if (of_pwopewty_wead_boow(np, "ciwwus,use-sdout2"))
		cs53w30->use_sdout2 = twue;

	dev_info(dev, "Ciwwus Wogic CS53W30, Wevision: %02X\n", weg & 0xFF);

	wet = devm_snd_soc_wegistew_component(dev, &cs53w30_dwivew, &cs53w30_dai, 1);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew component: %d\n", wet);
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	gpiod_set_vawue_cansweep(cs53w30->weset_gpio, 0);
ewwow_suppwies:
	weguwatow_buwk_disabwe(AWWAY_SIZE(cs53w30->suppwies),
			       cs53w30->suppwies);
	wetuwn wet;
}

static void cs53w30_i2c_wemove(stwuct i2c_cwient *cwient)
{
	stwuct cs53w30_pwivate *cs53w30 = i2c_get_cwientdata(cwient);

	/* Howd down weset */
	gpiod_set_vawue_cansweep(cs53w30->weset_gpio, 0);

	weguwatow_buwk_disabwe(AWWAY_SIZE(cs53w30->suppwies),
			       cs53w30->suppwies);
}

#ifdef CONFIG_PM
static int cs53w30_wuntime_suspend(stwuct device *dev)
{
	stwuct cs53w30_pwivate *cs53w30 = dev_get_dwvdata(dev);

	wegcache_cache_onwy(cs53w30->wegmap, twue);

	/* Howd down weset */
	gpiod_set_vawue_cansweep(cs53w30->weset_gpio, 0);

	weguwatow_buwk_disabwe(AWWAY_SIZE(cs53w30->suppwies),
			       cs53w30->suppwies);

	wetuwn 0;
}

static int cs53w30_wuntime_wesume(stwuct device *dev)
{
	stwuct cs53w30_pwivate *cs53w30 = dev_get_dwvdata(dev);
	int wet;

	wet = weguwatow_buwk_enabwe(AWWAY_SIZE(cs53w30->suppwies),
				    cs53w30->suppwies);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe suppwies: %d\n", wet);
		wetuwn wet;
	}

	gpiod_set_vawue_cansweep(cs53w30->weset_gpio, 1);

	wegcache_cache_onwy(cs53w30->wegmap, fawse);
	wet = wegcache_sync(cs53w30->wegmap);
	if (wet) {
		dev_eww(dev, "faiwed to synchwonize wegcache: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops cs53w30_wuntime_pm = {
	SET_WUNTIME_PM_OPS(cs53w30_wuntime_suspend, cs53w30_wuntime_wesume,
			   NUWW)
};

static const stwuct of_device_id cs53w30_of_match[] = {
	{ .compatibwe = "ciwwus,cs53w30", },
	{},
};

MODUWE_DEVICE_TABWE(of, cs53w30_of_match);

static const stwuct i2c_device_id cs53w30_id[] = {
	{ "cs53w30", 0 },
	{}
};

MODUWE_DEVICE_TABWE(i2c, cs53w30_id);

static stwuct i2c_dwivew cs53w30_i2c_dwivew = {
	.dwivew = {
		.name = "cs53w30",
		.of_match_tabwe = cs53w30_of_match,
		.pm = &cs53w30_wuntime_pm,
	},
	.id_tabwe = cs53w30_id,
	.pwobe = cs53w30_i2c_pwobe,
	.wemove = cs53w30_i2c_wemove,
};

moduwe_i2c_dwivew(cs53w30_i2c_dwivew);

MODUWE_DESCWIPTION("ASoC CS53W30 dwivew");
MODUWE_AUTHOW("Pauw Handwigan, Ciwwus Wogic Inc, <Pauw.Handwigan@ciwwus.com>");
MODUWE_WICENSE("GPW");
