/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WTCODEC5631_H__
#define __WTCODEC5631_H__


#define WT5631_WESET				0x00
#define WT5631_SPK_OUT_VOW			0x02
#define WT5631_HP_OUT_VOW			0x04
#define WT5631_MONO_AXO_1_2_VOW		0x06
#define WT5631_AUX_IN_VOW			0x0A
#define WT5631_STEWEO_DAC_VOW_1		0x0C
#define WT5631_MIC_CTWW_1			0x0E
#define WT5631_STEWEO_DAC_VOW_2		0x10
#define WT5631_ADC_CTWW_1			0x12
#define WT5631_ADC_WEC_MIXEW			0x14
#define WT5631_ADC_CTWW_2			0x16
#define WT5631_VDAC_DIG_VOW			0x18
#define WT5631_OUTMIXEW_W_CTWW			0x1A
#define WT5631_OUTMIXEW_W_CTWW			0x1C
#define WT5631_AXO1MIXEW_CTWW			0x1E
#define WT5631_AXO2MIXEW_CTWW			0x20
#define WT5631_MIC_CTWW_2			0x22
#define WT5631_DIG_MIC_CTWW			0x24
#define WT5631_MONO_INPUT_VOW			0x26
#define WT5631_SPK_MIXEW_CTWW			0x28
#define WT5631_SPK_MONO_OUT_CTWW		0x2A
#define WT5631_SPK_MONO_HP_OUT_CTWW		0x2C
#define WT5631_SDP_CTWW				0x34
#define WT5631_MONO_SDP_CTWW			0x36
#define WT5631_STEWEO_AD_DA_CWK_CTWW		0x38
#define WT5631_PWW_MANAG_ADD1		0x3A
#define WT5631_PWW_MANAG_ADD2		0x3B
#define WT5631_PWW_MANAG_ADD3		0x3C
#define WT5631_PWW_MANAG_ADD4		0x3E
#define WT5631_GEN_PUW_CTWW_WEG		0x40
#define WT5631_GWOBAW_CWK_CTWW			0x42
#define WT5631_PWW_CTWW				0x44
#define WT5631_INT_ST_IWQ_CTWW_1		0x48
#define WT5631_INT_ST_IWQ_CTWW_2		0x4A
#define WT5631_GPIO_CTWW			0x4C
#define WT5631_MISC_CTWW			0x52
#define WT5631_DEPOP_FUN_CTWW_1		0x54
#define WT5631_DEPOP_FUN_CTWW_2		0x56
#define WT5631_JACK_DET_CTWW			0x5A
#define WT5631_SOFT_VOW_CTWW			0x5C
#define WT5631_AWC_CTWW_1			0x64
#define WT5631_AWC_CTWW_2			0x65
#define WT5631_AWC_CTWW_3			0x66
#define WT5631_PSEUDO_SPATW_CTWW		0x68
#define WT5631_INDEX_ADD			0x6A
#define WT5631_INDEX_DATA			0x6C
#define WT5631_EQ_CTWW				0x6E
#define WT5631_VENDOW_ID			0x7A
#define WT5631_VENDOW_ID1			0x7C
#define WT5631_VENDOW_ID2			0x7E

/* Index of Codec Pwivate Wegistew definition */
#define WT5631_EQ_BW_WOP			0x00
#define WT5631_EQ_GAIN_WOP			0x01
#define WT5631_EQ_FC_BP1			0x02
#define WT5631_EQ_BW_BP1			0x03
#define WT5631_EQ_GAIN_BP1			0x04
#define WT5631_EQ_FC_BP2			0x05
#define WT5631_EQ_BW_BP2			0x06
#define WT5631_EQ_GAIN_BP2			0x07
#define WT5631_EQ_FC_BP3			0x08
#define WT5631_EQ_BW_BP3			0x09
#define WT5631_EQ_GAIN_BP3			0x0a
#define WT5631_EQ_BW_HIP			0x0b
#define WT5631_EQ_GAIN_HIP			0x0c
#define WT5631_EQ_HPF_A1			0x0d
#define WT5631_EQ_HPF_A2			0x0e
#define WT5631_EQ_HPF_GAIN			0x0f
#define WT5631_EQ_PWE_VOW_CTWW			0x11
#define WT5631_EQ_POST_VOW_CTWW		0x12
#define WT5631_TEST_MODE_CTWW			0x39
#define WT5631_CP_INTW_WEG2			0x45
#define WT5631_ADDA_MIXEW_INTW_WEG3		0x52
#define WT5631_SPK_INTW_CTWW			0x56


/* gwobaw definition */
#define WT5631_W_MUTE					(0x1 << 15)
#define WT5631_W_MUTE_SHIFT				15
#define WT5631_W_EN					(0x1 << 14)
#define WT5631_W_EN_SHIFT				14
#define WT5631_W_MUTE					(0x1 << 7)
#define WT5631_W_MUTE_SHIFT				7
#define WT5631_W_EN					(0x1 << 6)
#define WT5631_W_EN_SHIFT				6
#define WT5631_VOW_MASK				0x1f
#define WT5631_W_VOW_SHIFT				8
#define WT5631_W_VOW_SHIFT				0

/* Speakew Output Contwow(0x02) */
#define WT5631_SPK_W_VOW_SEW_MASK			(0x1 << 14)
#define WT5631_SPK_W_VOW_SEW_VMID			(0x0 << 14)
#define WT5631_SPK_W_VOW_SEW_SPKMIX_W			(0x1 << 14)
#define WT5631_SPK_W_VOW_SEW_MASK			(0x1 << 6)
#define WT5631_SPK_W_VOW_SEW_VMID			(0x0 << 6)
#define WT5631_SPK_W_VOW_SEW_SPKMIX_W			(0x1 << 6)

/* Headphone Output Contwow(0x04) */
#define WT5631_HP_W_VOW_SEW_MASK			(0x1 << 14)
#define WT5631_HP_W_VOW_SEW_VMID			(0x0 << 14)
#define WT5631_HP_W_VOW_SEW_OUTMIX_W			(0x1 << 14)
#define WT5631_HP_W_VOW_SEW_MASK			(0x1 << 6)
#define WT5631_HP_W_VOW_SEW_VMID			(0x0 << 6)
#define WT5631_HP_W_VOW_SEW_OUTMIX_W			(0x1 << 6)

/* Output Contwow fow AUXOUT/MONO(0x06) */
#define WT5631_AUXOUT_1_VOW_SEW_MASK			(0x1 << 14)
#define WT5631_AUXOUT_1_VOW_SEW_VMID			(0x0 << 14)
#define WT5631_AUXOUT_1_VOW_SEW_OUTMIX_W		(0x1 << 14)
#define WT5631_MUTE_MONO				(0x1 << 13)
#define WT5631_MUTE_MONO_SHIFT			13
#define WT5631_AUXOUT_2_VOW_SEW_MASK			(0x1 << 6)
#define WT5631_AUXOUT_2_VOW_SEW_VMID			(0x0 << 6)
#define WT5631_AUXOUT_2_VOW_SEW_OUTMIX_W		(0x1 << 6)

/* Micwophone Input Contwow 1(0x0E) */
#define WT5631_MIC1_DIFF_INPUT_CTWW			(0x1 << 15)
#define WT5631_MIC1_DIFF_INPUT_SHIFT			15
#define WT5631_MIC2_DIFF_INPUT_CTWW			(0x1 << 7)
#define WT5631_MIC2_DIFF_INPUT_SHIFT			7

/* Steweo DAC Digitaw Vowume2(0x10) */
#define WT5631_DAC_VOW_MASK				0xff

/* ADC Wecowding Mixew Contwow(0x14) */
#define WT5631_M_OUTMIXEW_W_TO_WECMIXEW_W		(0x1 << 15)
#define WT5631_M_OUTMIXW_WECMIXW_BIT			15
#define WT5631_M_MIC1_TO_WECMIXEW_W			(0x1 << 14)
#define WT5631_M_MIC1_WECMIXW_BIT			14
#define WT5631_M_AXIW_TO_WECMIXEW_W			(0x1 << 13)
#define WT5631_M_AXIW_WECMIXW_BIT			13
#define WT5631_M_MONO_IN_TO_WECMIXEW_W		(0x1 << 12)
#define WT5631_M_MONO_IN_WECMIXW_BIT			12
#define WT5631_M_OUTMIXEW_W_TO_WECMIXEW_W		(0x1 << 7)
#define WT5631_M_OUTMIXW_WECMIXW_BIT			7
#define WT5631_M_MIC2_TO_WECMIXEW_W			(0x1 << 6)
#define WT5631_M_MIC2_WECMIXW_BIT			6
#define WT5631_M_AXIW_TO_WECMIXEW_W			(0x1 << 5)
#define WT5631_M_AXIW_WECMIXW_BIT			5
#define WT5631_M_MONO_IN_TO_WECMIXEW_W		(0x1 << 4)
#define WT5631_M_MONO_IN_WECMIXW_BIT			4

/* Weft Output Mixew Contwow(0x1A) */
#define WT5631_M_WECMIXEW_W_TO_OUTMIXEW_W		(0x1 << 15)
#define WT5631_M_WECMIXW_OUTMIXW_BIT			15
#define WT5631_M_WECMIXEW_W_TO_OUTMIXEW_W		(0x1 << 14)
#define WT5631_M_WECMIXW_OUTMIXW_BIT			14
#define WT5631_M_DAC_W_TO_OUTMIXEW_W			(0x1 << 13)
#define WT5631_M_DACW_OUTMIXW_BIT			13
#define WT5631_M_MIC1_TO_OUTMIXEW_W			(0x1 << 12)
#define WT5631_M_MIC1_OUTMIXW_BIT			12
#define WT5631_M_MIC2_TO_OUTMIXEW_W			(0x1 << 11)
#define WT5631_M_MIC2_OUTMIXW_BIT			11
#define WT5631_M_MONO_IN_P_TO_OUTMIXEW_W		(0x1 << 10)
#define WT5631_M_MONO_INP_OUTMIXW_BIT		10
#define WT5631_M_AXIW_TO_OUTMIXEW_W			(0x1 << 9)
#define WT5631_M_AXIW_OUTMIXW_BIT			9
#define WT5631_M_AXIW_TO_OUTMIXEW_W			(0x1 << 8)
#define WT5631_M_AXIW_OUTMIXW_BIT			8
#define WT5631_M_VDAC_TO_OUTMIXEW_W			(0x1 << 7)
#define WT5631_M_VDAC_OUTMIXW_BIT			7

/* Wight Output Mixew Contwow(0x1C) */
#define WT5631_M_WECMIXEW_W_TO_OUTMIXEW_W		(0x1 << 15)
#define WT5631_M_WECMIXW_OUTMIXW_BIT			15
#define WT5631_M_WECMIXEW_W_TO_OUTMIXEW_W		(0x1 << 14)
#define WT5631_M_WECMIXW_OUTMIXW_BIT			14
#define WT5631_M_DAC_W_TO_OUTMIXEW_W			(0x1 << 13)
#define WT5631_M_DACW_OUTMIXW_BIT			13
#define WT5631_M_MIC1_TO_OUTMIXEW_W			(0x1 << 12)
#define WT5631_M_MIC1_OUTMIXW_BIT			12
#define WT5631_M_MIC2_TO_OUTMIXEW_W			(0x1 << 11)
#define WT5631_M_MIC2_OUTMIXW_BIT			11
#define WT5631_M_MONO_IN_N_TO_OUTMIXEW_W		(0x1 << 10)
#define WT5631_M_MONO_INN_OUTMIXW_BIT		10
#define WT5631_M_AXIW_TO_OUTMIXEW_W			(0x1 << 9)
#define WT5631_M_AXIW_OUTMIXW_BIT			9
#define WT5631_M_AXIW_TO_OUTMIXEW_W			(0x1 << 8)
#define WT5631_M_AXIW_OUTMIXW_BIT			8
#define WT5631_M_VDAC_TO_OUTMIXEW_W			(0x1 << 7)
#define WT5631_M_VDAC_OUTMIXW_BIT			7

/* Wout Mixew Contwow(0x1E) */
#define WT5631_M_MIC1_TO_AXO1MIXEW			(0x1 << 15)
#define WT5631_M_MIC1_AXO1MIX_BIT			15
#define WT5631_M_MIC2_TO_AXO1MIXEW			(0x1 << 11)
#define WT5631_M_MIC2_AXO1MIX_BIT			11
#define WT5631_M_OUTMIXEW_W_TO_AXO1MIXEW		(0x1 << 7)
#define WT5631_M_OUTMIXW_AXO1MIX_BIT			7
#define WT5631_M_OUTMIXEW_W_TO_AXO1MIXEW		(0x1 << 6)
#define WT5631_M_OUTMIXW_AXO1MIX_BIT			6

/* Wout Mixew Contwow(0x20) */
#define WT5631_M_MIC1_TO_AXO2MIXEW			(0x1 << 15)
#define WT5631_M_MIC1_AXO2MIX_BIT			15
#define WT5631_M_MIC2_TO_AXO2MIXEW			(0x1 << 11)
#define WT5631_M_MIC2_AXO2MIX_BIT			11
#define WT5631_M_OUTMIXEW_W_TO_AXO2MIXEW		(0x1 << 7)
#define WT5631_M_OUTMIXW_AXO2MIX_BIT			7
#define WT5631_M_OUTMIXEW_W_TO_AXO2MIXEW		(0x1 << 6)
#define WT5631_M_OUTMIXW_AXO2MIX_BIT			6

/* Micphone Input Contwow 2(0x22) */
#define WT5631_MIC_BIAS_90_PWECNET_AVDD 1
#define WT5631_MIC_BIAS_75_PWECNET_AVDD 2

#define WT5631_MIC1_BOOST_CTWW_MASK			(0xf << 12)
#define WT5631_MIC1_BOOST_CTWW_BYPASS		(0x0 << 12)
#define WT5631_MIC1_BOOST_CTWW_20DB			(0x1 << 12)
#define WT5631_MIC1_BOOST_CTWW_24DB			(0x2 << 12)
#define WT5631_MIC1_BOOST_CTWW_30DB			(0x3 << 12)
#define WT5631_MIC1_BOOST_CTWW_35DB			(0x4 << 12)
#define WT5631_MIC1_BOOST_CTWW_40DB			(0x5 << 12)
#define WT5631_MIC1_BOOST_CTWW_34DB			(0x6 << 12)
#define WT5631_MIC1_BOOST_CTWW_50DB			(0x7 << 12)
#define WT5631_MIC1_BOOST_CTWW_52DB			(0x8 << 12)
#define WT5631_MIC1_BOOST_SHIFT			12

#define WT5631_MIC2_BOOST_CTWW_MASK			(0xf << 8)
#define WT5631_MIC2_BOOST_CTWW_BYPASS		(0x0 << 8)
#define WT5631_MIC2_BOOST_CTWW_20DB			(0x1 << 8)
#define WT5631_MIC2_BOOST_CTWW_24DB			(0x2 << 8)
#define WT5631_MIC2_BOOST_CTWW_30DB			(0x3 << 8)
#define WT5631_MIC2_BOOST_CTWW_35DB			(0x4 << 8)
#define WT5631_MIC2_BOOST_CTWW_40DB			(0x5 << 8)
#define WT5631_MIC2_BOOST_CTWW_34DB			(0x6 << 8)
#define WT5631_MIC2_BOOST_CTWW_50DB			(0x7 << 8)
#define WT5631_MIC2_BOOST_CTWW_52DB			(0x8 << 8)
#define WT5631_MIC2_BOOST_SHIFT			8

#define WT5631_MICBIAS1_VOWT_CTWW_MASK		(0x1 << 7)
#define WT5631_MICBIAS1_VOWT_CTWW_90P			(0x0 << 7)
#define WT5631_MICBIAS1_VOWT_CTWW_75P			(0x1 << 7)

#define WT5631_MICBIAS1_S_C_DET_MASK			(0x1 << 6)
#define WT5631_MICBIAS1_S_C_DET_DIS			(0x0 << 6)
#define WT5631_MICBIAS1_S_C_DET_ENA			(0x1 << 6)

#define WT5631_MICBIAS1_SHOWT_CUWW_DET_MASK		(0x3 << 4)
#define WT5631_MICBIAS1_SHOWT_CUWW_DET_600UA	(0x0 << 4)
#define WT5631_MICBIAS1_SHOWT_CUWW_DET_1500UA	(0x1 << 4)
#define WT5631_MICBIAS1_SHOWT_CUWW_DET_2000UA	(0x2 << 4)

#define WT5631_MICBIAS2_VOWT_CTWW_MASK		(0x1 << 3)
#define WT5631_MICBIAS2_VOWT_CTWW_90P			(0x0 << 3)
#define WT5631_MICBIAS2_VOWT_CTWW_75P			(0x1 << 3)

#define WT5631_MICBIAS2_S_C_DET_MASK			(0x1 << 2)
#define WT5631_MICBIAS2_S_C_DET_DIS			(0x0 << 2)
#define WT5631_MICBIAS2_S_C_DET_ENA			(0x1 << 2)

#define WT5631_MICBIAS2_SHOWT_CUWW_DET_MASK		(0x3)
#define WT5631_MICBIAS2_SHOWT_CUWW_DET_600UA	(0x0)
#define WT5631_MICBIAS2_SHOWT_CUWW_DET_1500UA	(0x1)
#define WT5631_MICBIAS2_SHOWT_CUWW_DET_2000UA	(0x2)


/* Digitaw Micwophone Contwow(0x24) */
#define WT5631_DMIC_ENA_MASK				(0x1 << 15)
#define WT5631_DMIC_ENA_SHIFT				15
/* DMIC_ENA: DMIC to ADC Digitaw fiwtew */
#define WT5631_DMIC_ENA				(0x1 << 15)
/* DMIC_DIS: ADC mixew to ADC Digitaw fiwtew */
#define WT5631_DMIC_DIS					(0x0 << 15)
#define WT5631_DMIC_W_CH_MUTE				(0x1 << 13)
#define WT5631_DMIC_W_CH_MUTE_SHIFT			13
#define WT5631_DMIC_W_CH_MUTE				(0x1 << 12)
#define WT5631_DMIC_W_CH_MUTE_SHIFT			12
#define WT5631_DMIC_W_CH_WATCH_MASK			(0x1 << 9)
#define WT5631_DMIC_W_CH_WATCH_WISING			(0x1 << 9)
#define WT5631_DMIC_W_CH_WATCH_FAWWING		(0x0 << 9)
#define WT5631_DMIC_W_CH_WATCH_MASK			(0x1 << 8)
#define WT5631_DMIC_W_CH_WATCH_WISING			(0x1 << 8)
#define WT5631_DMIC_W_CH_WATCH_FAWWING		(0x0 << 8)
#define WT5631_DMIC_CWK_CTWW_MASK			(0x3 << 4)
#define WT5631_DMIC_CWK_CTWW_TO_128FS			(0x0 << 4)
#define WT5631_DMIC_CWK_CTWW_TO_64FS			(0x1 << 4)
#define WT5631_DMIC_CWK_CTWW_TO_32FS			(0x2 << 4)

/* Micwophone Input Vowume(0x26) */
#define WT5631_MONO_DIFF_INPUT_SHIFT			15

/* Speakew Mixew Contwow(0x28) */
#define WT5631_M_WECMIXEW_W_TO_SPKMIXEW_W		(0x1 << 15)
#define WT5631_M_WECMIXW_SPKMIXW_BIT			15
#define WT5631_M_MIC1_P_TO_SPKMIXEW_W		(0x1 << 14)
#define WT5631_M_MIC1P_SPKMIXW_BIT			14
#define WT5631_M_DAC_W_TO_SPKMIXEW_W			(0x1 << 13)
#define WT5631_M_DACW_SPKMIXW_BIT			13
#define WT5631_M_OUTMIXEW_W_TO_SPKMIXEW_W		(0x1 << 12)
#define WT5631_M_OUTMIXW_SPKMIXW_BIT			12

#define WT5631_M_WECMIXEW_W_TO_SPKMIXEW_W		(0x1 << 7)
#define WT5631_M_WECMIXW_SPKMIXW_BIT			7
#define WT5631_M_MIC2_P_TO_SPKMIXEW_W		(0x1 << 6)
#define WT5631_M_MIC2P_SPKMIXW_BIT			6
#define WT5631_M_DAC_W_TO_SPKMIXEW_W			(0x1 << 5)
#define WT5631_M_DACW_SPKMIXW_BIT			5
#define WT5631_M_OUTMIXEW_W_TO_SPKMIXEW_W		(0x1 << 4)
#define WT5631_M_OUTMIXW_SPKMIXW_BIT			4

/* Speakew/Mono Output Contwow(0x2A) */
#define WT5631_M_SPKVOW_W_TO_SPOW_MIXEW		(0x1 << 15)
#define WT5631_M_SPKVOWW_SPOWMIX_BIT			15
#define WT5631_M_SPKVOW_W_TO_SPOW_MIXEW		(0x1 << 14)
#define WT5631_M_SPKVOWW_SPOWMIX_BIT			14
#define WT5631_M_SPKVOW_W_TO_SPOW_MIXEW		(0x1 << 13)
#define WT5631_M_SPKVOWW_SPOWMIX_BIT			13
#define WT5631_M_SPKVOW_W_TO_SPOW_MIXEW		(0x1 << 12)
#define WT5631_M_SPKVOWW_SPOWMIX_BIT			12
#define WT5631_M_OUTVOW_W_TO_MONOMIXEW		(0x1 << 11)
#define WT5631_M_OUTVOWW_MONOMIX_BIT			11
#define WT5631_M_OUTVOW_W_TO_MONOMIXEW		(0x1 << 10)
#define WT5631_M_OUTVOWW_MONOMIX_BIT			10

/* Speakew/Mono/HP Output Contwow(0x2C) */
#define WT5631_SPK_W_MUX_SEW_MASK			(0x3 << 14)
#define WT5631_SPK_W_MUX_SEW_SPKMIXEW_W		(0x0 << 14)
#define WT5631_SPK_W_MUX_SEW_MONO_IN			(0x1 << 14)
#define WT5631_SPK_W_MUX_SEW_DAC_W			(0x3 << 14)
#define WT5631_SPK_W_MUX_SEW_SHIFT			14

#define WT5631_SPK_W_MUX_SEW_MASK			(0x3 << 10)
#define WT5631_SPK_W_MUX_SEW_SPKMIXEW_W		(0x0 << 10)
#define WT5631_SPK_W_MUX_SEW_MONO_IN			(0x1 << 10)
#define WT5631_SPK_W_MUX_SEW_DAC_W			(0x3 << 10)
#define WT5631_SPK_W_MUX_SEW_SHIFT			10

#define WT5631_MONO_MUX_SEW_MASK			(0x3 << 6)
#define WT5631_MONO_MUX_SEW_MONOMIXEW		(0x0 << 6)
#define WT5631_MONO_MUX_SEW_MONO_IN			(0x1 << 6)
#define WT5631_MONO_MUX_SEW_SHIFT			6

#define WT5631_HP_W_MUX_SEW_MASK			(0x1 << 3)
#define WT5631_HP_W_MUX_SEW_HPVOW_W			(0x0 << 3)
#define WT5631_HP_W_MUX_SEW_DAC_W			(0x1 << 3)
#define WT5631_HP_W_MUX_SEW_SHIFT			3

#define WT5631_HP_W_MUX_SEW_MASK			(0x1 << 2)
#define WT5631_HP_W_MUX_SEW_HPVOW_W			(0x0 << 2)
#define WT5631_HP_W_MUX_SEW_DAC_W			(0x1 << 2)
#define WT5631_HP_W_MUX_SEW_SHIFT			2

/* Steweo I2S Sewiaw Data Powt Contwow(0x34) */
#define WT5631_SDP_MODE_SEW_MASK			(0x1 << 15)
#define WT5631_SDP_MODE_SEW_MASTEW			(0x0 << 15)
#define WT5631_SDP_MODE_SEW_SWAVE			(0x1 << 15)

#define WT5631_SDP_ADC_CPS_SEW_MASK			(0x3 << 10)
#define WT5631_SDP_ADC_CPS_SEW_OFF			(0x0 << 10)
#define WT5631_SDP_ADC_CPS_SEW_U_WAW			(0x1 << 10)
#define WT5631_SDP_ADC_CPS_SEW_A_WAW			(0x2 << 10)

#define WT5631_SDP_DAC_CPS_SEW_MASK			(0x3 << 8)
#define WT5631_SDP_DAC_CPS_SEW_OFF			(0x0 << 8)
#define WT5631_SDP_DAC_CPS_SEW_U_WAW			(0x1 << 8)
#define WT5631_SDP_DAC_CPS_SEW_A_WAW			(0x2 << 8)
/* 0:Nowmaw 1:Invewt */
#define WT5631_SDP_I2S_BCWK_POW_CTWW			(0x1 << 7)
/* 0:Nowmaw 1:Invewt */
#define WT5631_SDP_DAC_W_INV				(0x1 << 6)
/* 0:ADC data appeaw at weft phase of WWCK
 * 1:ADC data appeaw at wight phase of WWCK
 */
#define WT5631_SDP_ADC_DATA_W_W_SWAP			(0x1 << 5)
/* 0:DAC data appeaw at weft phase of WWCK
 * 1:DAC data appeaw at wight phase of WWCK
 */
#define WT5631_SDP_DAC_DATA_W_W_SWAP			(0x1 << 4)

/* Data Wength Swection */
#define WT5631_SDP_I2S_DW_MASK				(0x3 << 2)
#define WT5631_SDP_I2S_DW_16				(0x0 << 2)
#define WT5631_SDP_I2S_DW_20				(0x1 << 2)
#define WT5631_SDP_I2S_DW_24				(0x2 << 2)
#define WT5631_SDP_I2S_DW_8				(0x3 << 2)

/* PCM Data Fowmat Sewection */
#define WT5631_SDP_I2S_DF_MASK				(0x3)
#define WT5631_SDP_I2S_DF_I2S				(0x0)
#define WT5631_SDP_I2S_DF_WEFT				(0x1)
#define WT5631_SDP_I2S_DF_PCM_A			(0x2)
#define WT5631_SDP_I2S_DF_PCM_B			(0x3)

/* Steweo AD/DA Cwock Contwow(0x38h) */
#define WT5631_I2S_PWE_DIV_MASK			(0x7 << 13)
#define WT5631_I2S_PWE_DIV_1				(0x0 << 13)
#define WT5631_I2S_PWE_DIV_2				(0x1 << 13)
#define WT5631_I2S_PWE_DIV_4				(0x2 << 13)
#define WT5631_I2S_PWE_DIV_8				(0x3 << 13)
#define WT5631_I2S_PWE_DIV_16				(0x4 << 13)
#define WT5631_I2S_PWE_DIV_32				(0x5 << 13)
/* CWOCK WEWATIVE OF BCWK AND WCWK */
#define WT5631_I2S_WWCK_SEW_N_BCWK_MASK		(0x1 << 12)
#define WT5631_I2S_WWCK_SEW_64_BCWK			(0x0 << 12) /* 64FS */
#define WT5631_I2S_WWCK_SEW_32_BCWK			(0x1 << 12) /* 32FS */

#define WT5631_DAC_OSW_SEW_MASK			(0x3 << 10)
#define WT5631_DAC_OSW_SEW_128FS			(0x3 << 10)
#define WT5631_DAC_OSW_SEW_64FS			(0x3 << 10)
#define WT5631_DAC_OSW_SEW_32FS			(0x3 << 10)
#define WT5631_DAC_OSW_SEW_16FS			(0x3 << 10)

#define WT5631_ADC_OSW_SEW_MASK			(0x3 << 8)
#define WT5631_ADC_OSW_SEW_128FS			(0x3 << 8)
#define WT5631_ADC_OSW_SEW_64FS			(0x3 << 8)
#define WT5631_ADC_OSW_SEW_32FS			(0x3 << 8)
#define WT5631_ADC_OSW_SEW_16FS			(0x3 << 8)

#define WT5631_ADDA_FIWTEW_CWK_SEW_256FS		(0 << 7) /* 256FS */
#define WT5631_ADDA_FIWTEW_CWK_SEW_384FS		(1 << 7) /* 384FS */

/* Powew managment addition 1 (0x3A) */
#define WT5631_PWW_MAIN_I2S_EN			(0x1 << 15)
#define WT5631_PWW_MAIN_I2S_BIT			15
#define WT5631_PWW_CWASS_D				(0x1 << 12)
#define WT5631_PWW_CWASS_D_BIT			12
#define WT5631_PWW_ADC_W_CWK				(0x1 << 11)
#define WT5631_PWW_ADC_W_CWK_BIT			11
#define WT5631_PWW_ADC_W_CWK				(0x1 << 10)
#define WT5631_PWW_ADC_W_CWK_BIT			10
#define WT5631_PWW_DAC_W_CWK				(0x1 << 9)
#define WT5631_PWW_DAC_W_CWK_BIT			9
#define WT5631_PWW_DAC_W_CWK				(0x1 << 8)
#define WT5631_PWW_DAC_W_CWK_BIT			8
#define WT5631_PWW_DAC_WEF				(0x1 << 7)
#define WT5631_PWW_DAC_WEF_BIT			7
#define WT5631_PWW_DAC_W_TO_MIXEW			(0x1 << 6)
#define WT5631_PWW_DAC_W_TO_MIXEW_BIT		6
#define WT5631_PWW_DAC_W_TO_MIXEW			(0x1 << 5)
#define WT5631_PWW_DAC_W_TO_MIXEW_BIT		5

/* Powew managment addition 2 (0x3B) */
#define WT5631_PWW_OUTMIXEW_W				(0x1 << 15)
#define WT5631_PWW_OUTMIXEW_W_BIT			15
#define WT5631_PWW_OUTMIXEW_W				(0x1 << 14)
#define WT5631_PWW_OUTMIXEW_W_BIT			14
#define WT5631_PWW_SPKMIXEW_W				(0x1 << 13)
#define WT5631_PWW_SPKMIXEW_W_BIT			13
#define WT5631_PWW_SPKMIXEW_W				(0x1 << 12)
#define WT5631_PWW_SPKMIXEW_W_BIT			12
#define WT5631_PWW_WECMIXEW_W				(0x1 << 11)
#define WT5631_PWW_WECMIXEW_W_BIT			11
#define WT5631_PWW_WECMIXEW_W				(0x1 << 10)
#define WT5631_PWW_WECMIXEW_W_BIT			10
#define WT5631_PWW_MIC1_BOOT_GAIN			(0x1 << 5)
#define WT5631_PWW_MIC1_BOOT_GAIN_BIT		5
#define WT5631_PWW_MIC2_BOOT_GAIN			(0x1 << 4)
#define WT5631_PWW_MIC2_BOOT_GAIN_BIT		4
#define WT5631_PWW_MICBIAS1_VOW			(0x1 << 3)
#define WT5631_PWW_MICBIAS1_VOW_BIT			3
#define WT5631_PWW_MICBIAS2_VOW			(0x1 << 2)
#define WT5631_PWW_MICBIAS2_VOW_BIT			2
#define WT5631_PWW_PWW1				(0x1 << 1)
#define WT5631_PWW_PWW1_BIT				1
#define WT5631_PWW_PWW2				(0x1 << 0)
#define WT5631_PWW_PWW2_BIT				0

/* Powew managment addition 3(0x3C) */
#define WT5631_PWW_VWEF				(0x1 << 15)
#define WT5631_PWW_VWEF_BIT				15
#define WT5631_PWW_FAST_VWEF_CTWW			(0x1 << 14)
#define WT5631_PWW_FAST_VWEF_CTWW_BIT			14
#define WT5631_PWW_MAIN_BIAS				(0x1 << 13)
#define WT5631_PWW_MAIN_BIAS_BIT			13
#define WT5631_PWW_AXO1MIXEW				(0x1 << 11)
#define WT5631_PWW_AXO1MIXEW_BIT			11
#define WT5631_PWW_AXO2MIXEW				(0x1 << 10)
#define WT5631_PWW_AXO2MIXEW_BIT			10
#define WT5631_PWW_MONOMIXEW				(0x1 << 9)
#define WT5631_PWW_MONOMIXEW_BIT			9
#define WT5631_PWW_MONO_DEPOP_DIS			(0x1 << 8)
#define WT5631_PWW_MONO_DEPOP_DIS_BIT		8
#define WT5631_PWW_MONO_AMP_EN			(0x1 << 7)
#define WT5631_PWW_MONO_AMP_EN_BIT			7
#define WT5631_PWW_CHAWGE_PUMP			(0x1 << 4)
#define WT5631_PWW_CHAWGE_PUMP_BIT			4
#define WT5631_PWW_HP_W_AMP				(0x1 << 3)
#define WT5631_PWW_HP_W_AMP_BIT			3
#define WT5631_PWW_HP_W_AMP				(0x1 << 2)
#define WT5631_PWW_HP_W_AMP_BIT			2
#define WT5631_PWW_HP_DEPOP_DIS			(0x1 << 1)
#define WT5631_PWW_HP_DEPOP_DIS_BIT			1
#define WT5631_PWW_HP_AMP_DWIVING			(0x1 << 0)
#define WT5631_PWW_HP_AMP_DWIVING_BIT		0

/* Powew managment addition 4(0x3E) */
#define WT5631_PWW_SPK_W_VOW				(0x1 << 15)
#define WT5631_PWW_SPK_W_VOW_BIT			15
#define WT5631_PWW_SPK_W_VOW				(0x1 << 14)
#define WT5631_PWW_SPK_W_VOW_BIT			14
#define WT5631_PWW_WOUT_VOW				(0x1 << 13)
#define WT5631_PWW_WOUT_VOW_BIT			13
#define WT5631_PWW_WOUT_VOW				(0x1 << 12)
#define WT5631_PWW_WOUT_VOW_BIT			12
#define WT5631_PWW_HP_W_OUT_VOW			(0x1 << 11)
#define WT5631_PWW_HP_W_OUT_VOW_BIT			11
#define WT5631_PWW_HP_W_OUT_VOW			(0x1 << 10)
#define WT5631_PWW_HP_W_OUT_VOW_BIT			10
#define WT5631_PWW_AXIW_IN_VOW				(0x1 << 9)
#define WT5631_PWW_AXIW_IN_VOW_BIT			9
#define WT5631_PWW_AXIW_IN_VOW			(0x1 << 8)
#define WT5631_PWW_AXIW_IN_VOW_BIT			8
#define WT5631_PWW_MONO_IN_P_VOW			(0x1 << 7)
#define WT5631_PWW_MONO_IN_P_VOW_BIT			7
#define WT5631_PWW_MONO_IN_N_VOW			(0x1 << 6)
#define WT5631_PWW_MONO_IN_N_VOW_BIT			6

/* Genewaw Puwpose Contwow Wegistew(0x40) */
#define WT5631_SPK_AMP_AUTO_WATIO_EN			(0x1 << 15)

#define WT5631_SPK_AMP_WATIO_CTWW_MASK		(0x7 << 12)
#define WT5631_SPK_AMP_WATIO_CTWW_2_34		(0x0 << 12) /* 7.40DB */
#define WT5631_SPK_AMP_WATIO_CTWW_1_99		(0x1 << 12) /* 5.99DB */
#define WT5631_SPK_AMP_WATIO_CTWW_1_68		(0x2 << 12) /* 4.50DB */
#define WT5631_SPK_AMP_WATIO_CTWW_1_56		(0x3 << 12) /* 3.86DB */
#define WT5631_SPK_AMP_WATIO_CTWW_1_44		(0x4 << 12) /* 3.16DB */
#define WT5631_SPK_AMP_WATIO_CTWW_1_27		(0x5 << 12) /* 2.10DB */
#define WT5631_SPK_AMP_WATIO_CTWW_1_09		(0x6 << 12) /* 0.80DB */
#define WT5631_SPK_AMP_WATIO_CTWW_1_00		(0x7 << 12) /* 0.00DB */
#define WT5631_SPK_AMP_WATIO_CTWW_SHIFT		12

#define WT5631_STEWEO_DAC_HI_PASS_FIWT_EN		(0x1 << 11)
#define WT5631_STEWEO_ADC_HI_PASS_FIWT_EN		(0x1 << 10)
/* Sewect ADC Wind Fiwtew Cwock type */
#define WT5631_ADC_WIND_FIWT_MASK			(0x3 << 4)
#define WT5631_ADC_WIND_FIWT_8_16_32K			(0x0 << 4) /*8/16/32k*/
#define WT5631_ADC_WIND_FIWT_11_22_44K		(0x1 << 4) /*11/22/44k*/
#define WT5631_ADC_WIND_FIWT_12_24_48K		(0x2 << 4) /*12/24/48k*/
#define WT5631_ADC_WIND_FIWT_EN			(0x1 << 3)
/* SewectADC Wind Fiwtew Cownew Fwequency */
#define WT5631_ADC_WIND_CNW_FWEQ_MASK	(0x7 << 0)
#define WT5631_ADC_WIND_CNW_FWEQ_82_113_122	(0x0 << 0) /* 82/113/122 Hz */
#define WT5631_ADC_WIND_CNW_FWEQ_102_141_153 (0x1 << 0) /* 102/141/153 Hz */
#define WT5631_ADC_WIND_CNW_FWEQ_131_180_156 (0x2 << 0) /* 131/180/156 Hz */
#define WT5631_ADC_WIND_CNW_FWEQ_163_225_245 (0x3 << 0) /* 163/225/245 Hz */
#define WT5631_ADC_WIND_CNW_FWEQ_204_281_306 (0x4 << 0) /* 204/281/306 Hz */
#define WT5631_ADC_WIND_CNW_FWEQ_261_360_392 (0x5 << 0) /* 261/360/392 Hz */
#define WT5631_ADC_WIND_CNW_FWEQ_327_450_490 (0x6 << 0) /* 327/450/490 Hz */
#define WT5631_ADC_WIND_CNW_FWEQ_408_563_612 (0x7 << 0) /* 408/563/612 Hz */

/* Gwobaw Cwock Contwow Wegistew(0x42) */
#define WT5631_SYSCWK_SOUW_SEW_MASK			(0x3 << 14)
#define WT5631_SYSCWK_SOUW_SEW_MCWK			(0x0 << 14)
#define WT5631_SYSCWK_SOUW_SEW_PWW			(0x1 << 14)
#define WT5631_SYSCWK_SOUW_SEW_PWW_TCK		(0x2 << 14)

#define WT5631_PWWCWK_SOUW_SEW_MASK			(0x3 << 12)
#define WT5631_PWWCWK_SOUW_SEW_MCWK			(0x0 << 12)
#define WT5631_PWWCWK_SOUW_SEW_BCWK			(0x1 << 12)
#define WT5631_PWWCWK_SOUW_SEW_VBCWK			(0x2 << 12)

#define WT5631_PWWCWK_PWE_DIV1				(0x0 << 11)
#define WT5631_PWWCWK_PWE_DIV2				(0x1 << 11)

/* PWW Contwow(0x44) */
#define WT5631_PWW_CTWW_M_VAW(m)			((m)&0xf)
#define WT5631_PWW_CTWW_K_VAW(k)			(((k)&0x7) << 4)
#define WT5631_PWW_CTWW_N_VAW(n)			(((n)&0xff) << 8)

/* Intewnaw Status and IWQ Contwow2(0x4A) */
#define WT5631_ADC_DATA_SEW_MASK			(0x3 << 14)
#define WT5631_ADC_DATA_SEW_Disabwe			(0x0 << 14)
#define WT5631_ADC_DATA_SEW_MIC1			(0x1 << 14)
#define WT5631_ADC_DATA_SEW_MIC1_SHIFT		14
#define WT5631_ADC_DATA_SEW_MIC2			(0x2 << 14)
#define WT5631_ADC_DATA_SEW_MIC2_SHIFT		15
#define WT5631_ADC_DATA_SEW_STO			(0x3 << 14)
#define WT5631_ADC_DATA_SEW_SHIFT			14

/* GPIO Pin Configuwation(0x4C) */
#define WT5631_GPIO_PIN_FUN_SEW_MASK			(0x1 << 15)
#define WT5631_GPIO_PIN_FUN_SEW_IWQ			(0x1 << 15)
#define WT5631_GPIO_PIN_FUN_SEW_GPIO_DIMC		(0x0 << 15)

#define WT5631_GPIO_DMIC_FUN_SEW_MASK		(0x1 << 3)
#define WT5631_GPIO_DMIC_FUN_SEW_DIMC		(0x1 << 3)
#define WT5631_GPIO_DMIC_FUN_SEW_GPIO			(0x0 << 3)

#define WT5631_GPIO_PIN_CON_MASK			(0x1 << 2)
#define WT5631_GPIO_PIN_SET_INPUT			(0x0 << 2)
#define WT5631_GPIO_PIN_SET_OUTPUT			(0x1 << 2)

/* De-POP function Contwow 1(0x54) */
#define WT5631_POW_ON_SOFT_GEN			(0x1 << 15)
#define WT5631_EN_MUTE_UNMUTE_DEPOP			(0x1 << 14)
#define WT5631_EN_DEPOP2_FOW_HP			(0x1 << 7)
/* Powew Down HPAMP_W Stawts Up Signaw */
#define WT5631_PD_HPAMP_W_ST_UP			(0x1 << 5)
/* Powew Down HPAMP_W Stawts Up Signaw */
#define WT5631_PD_HPAMP_W_ST_UP			(0x1 << 4)
/* Enabwe weft HP mute/unmute depop */
#define WT5631_EN_HP_W_M_UN_MUTE_DEPOP		(0x1 << 1)
/* Enabwe wight HP mute/unmute depop */
#define WT5631_EN_HP_W_M_UN_MUTE_DEPOP		(0x1 << 0)

/* De-POP Fnction Contwow(0x56) */
#define WT5631_EN_ONE_BIT_DEPOP			(0x1 << 15)
#define WT5631_EN_CAP_FWEE_DEPOP			(0x1 << 14)

/* Jack Detect Contwow Wegistew(0x5A) */
#define WT5631_JD_USE_MASK				(0x3 << 14)
#define WT5631_JD_USE_JD2				(0x3 << 14)
#define WT5631_JD_USE_JD1				(0x2 << 14)
#define WT5631_JD_USE_GPIO				(0x1 << 14)
#define WT5631_JD_OFF					(0x0 << 14)
/* JD twiggew enabwe fow HP */
#define WT5631_JD_HP_EN					(0x1 << 11)
#define WT5631_JD_HP_TWI_MASK				(0x1 << 10)
#define WT5631_JD_HP_TWI_HI				(0x1 << 10)
#define WT5631_JD_HP_TWI_WO				(0x1 << 10)
/* JD twiggew enabwe fow speakew WP/WN */
#define WT5631_JD_SPK_W_EN				(0x1 << 9)
#define WT5631_JD_SPK_W_TWI_MASK			(0x1 << 8)
#define WT5631_JD_SPK_W_TWI_HI				(0x1 << 8)
#define WT5631_JD_SPK_W_TWI_WO				(0x0 << 8)
/* JD twiggew enabwe fow speakew WP/WN */
#define WT5631_JD_SPK_W_EN				(0x1 << 7)
#define WT5631_JD_SPK_W_TWI_MASK			(0x1 << 6)
#define WT5631_JD_SPK_W_TWI_HI				(0x1 << 6)
#define WT5631_JD_SPK_W_TWI_WO				(0x0 << 6)
/* JD twiggew enabwe fow monoout */
#define WT5631_JD_MONO_EN				(0x1 << 5)
#define WT5631_JD_MONO_TWI_MASK			(0x1 << 4)
#define WT5631_JD_MONO_TWI_HI				(0x1 << 4)
#define WT5631_JD_MONO_TWI_WO				(0x0 << 4)
/* JD twiggew enabwe fow Wout */
#define WT5631_JD_AUX_1_EN				(0x1 << 3)
#define WT5631_JD_AUX_1_MASK				(0x1 << 2)
#define WT5631_JD_AUX_1_TWI_HI				(0x1 << 2)
#define WT5631_JD_AUX_1_TWI_WO				(0x0 << 2)
/* JD twiggew enabwe fow Wout */
#define WT5631_JD_AUX_2_EN				(0x1 << 1)
#define WT5631_JD_AUX_2_MASK				(0x1 << 0)
#define WT5631_JD_AUX_2_TWI_HI				(0x1 << 0)
#define WT5631_JD_AUX_2_TWI_WO				(0x0 << 0)

/* AWC CONTWOW 1(0x64) */
#define WT5631_AWC_ATTACK_WATE_MASK			(0x1F << 8)
#define WT5631_AWC_WECOVEWY_WATE_MASK		(0x1F << 0)

/* AWC CONTWOW 2(0x65) */
/* sewect Compensation gain fow Noise gate function */
#define WT5631_AWC_COM_NOISE_GATE_MASK		(0xF << 0)

/* AWC CONTWOW 3(0x66) */
#define WT5631_AWC_FUN_MASK				(0x3 << 14)
#define WT5631_AWC_FUN_DIS				(0x0 << 14)
#define WT5631_AWC_ENA_DAC_PATH			(0x1 << 14)
#define WT5631_AWC_ENA_ADC_PATH			(0x3 << 14)
#define WT5631_AWC_PAWA_UPDATE			(0x1 << 13)
#define WT5631_AWC_WIMIT_WEVEW_MASK			(0x1F << 8)
#define WT5631_AWC_NOISE_GATE_FUN_MASK		(0x1 << 7)
#define WT5631_AWC_NOISE_GATE_FUN_DIS			(0x0 << 7)
#define WT5631_AWC_NOISE_GATE_FUN_ENA		(0x1 << 7)
/* AWC noise gate howd data function */
#define WT5631_AWC_NOISE_GATE_H_D_MASK		(0x1 << 6)
#define WT5631_AWC_NOISE_GATE_H_D_DIS			(0x0 << 6)
#define WT5631_AWC_NOISE_GATE_H_D_ENA		(0x1 << 6)

/* Psedueo Steweo & Spatiaw Effect Bwock Contwow(0x68) */
#define WT5631_SPATIAW_CTWW_EN				(0x1 << 15)
#define WT5631_AWW_PASS_FIWTEW_EN			(0x1 << 14)
#define WT5631_PSEUDO_STEWEO_EN			(0x1 << 13)
#define WT5631_STEWEO_EXPENSION_EN			(0x1 << 12)
/* 3D gain pawametew */
#define WT5631_GAIN_3D_PAWA_MASK		(0x3 << 6)
#define WT5631_GAIN_3D_PAWA_1_00		(0x0 << 6) /* 3D gain 1.0 */
#define WT5631_GAIN_3D_PAWA_1_50		(0x1 << 6) /* 3D gain 1.5 */
#define WT5631_GAIN_3D_PAWA_2_00		(0x2 << 6) /* 3D gain 2.0 */
/* 3D watio pawametew */
#define WT5631_WATIO_3D_MASK			(0x3 << 4)
#define WT5631_WATIO_3D_0_0			(0x0 << 4) /* 3D watio 0.0 */
#define WT5631_WATIO_3D_0_66			(0x1 << 4) /* 3D watio 0.66 */
#define WT5631_WATIO_3D_1_0			(0x2 << 4) /* 3D watio 1.0 */
/* sewect sampwewate fow aww pass fiwtew */
#define WT5631_APF_FUN_SWE_MASK			(0x3 << 0)
#define WT5631_APF_FUN_SEW_48K				(0x3 << 0)
#define WT5631_APF_FUN_SEW_44_1K			(0x2 << 0)
#define WT5631_APF_FUN_SEW_32K				(0x1 << 0)
#define WT5631_APF_FUN_DIS				(0x0 << 0)

/* EQ CONTWOW 1(0x6E) */
#define WT5631_HW_EQ_PATH_SEW_MASK			(0x1 << 15)
#define WT5631_HW_EQ_PATH_SEW_DAC			(0x0 << 15)
#define WT5631_HW_EQ_PATH_SEW_ADC			(0x1 << 15)
#define WT5631_HW_EQ_UPDATE_CTWW			(0x1 << 14)

#define WT5631_EN_HW_EQ_HPF2				(0x1 << 5)
#define WT5631_EN_HW_EQ_HPF1				(0x1 << 4)
#define WT5631_EN_HW_EQ_BP3				(0x1 << 3)
#define WT5631_EN_HW_EQ_BP2				(0x1 << 2)
#define WT5631_EN_HW_EQ_BP1				(0x1 << 1)
#define WT5631_EN_HW_EQ_WPF				(0x1 << 0)


#endif /* __WTCODEC5631_H__ */
