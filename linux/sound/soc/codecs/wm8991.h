/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wm8991.h  --  audio dwivew fow WM8991
 *
 * Copywight 2007 Wowfson Micwoewectwonics PWC.
 * Authow: Gwaeme Gwegowy
 *         gwaeme.gwegowy@wowfsonmicwo.com ow winux@wowfsonmicwo.com
 */

#ifndef _WM8991_H
#define _WM8991_H

/*
 * Wegistew vawues.
 */
#define WM8991_WESET                            0x00
#define WM8991_POWEW_MANAGEMENT_1               0x01
#define WM8991_POWEW_MANAGEMENT_2               0x02
#define WM8991_POWEW_MANAGEMENT_3               0x03
#define WM8991_AUDIO_INTEWFACE_1                0x04
#define WM8991_AUDIO_INTEWFACE_2                0x05
#define WM8991_CWOCKING_1                       0x06
#define WM8991_CWOCKING_2                       0x07
#define WM8991_AUDIO_INTEWFACE_3                0x08
#define WM8991_AUDIO_INTEWFACE_4                0x09
#define WM8991_DAC_CTWW                         0x0A
#define WM8991_WEFT_DAC_DIGITAW_VOWUME          0x0B
#define WM8991_WIGHT_DAC_DIGITAW_VOWUME         0x0C
#define WM8991_DIGITAW_SIDE_TONE                0x0D
#define WM8991_ADC_CTWW                         0x0E
#define WM8991_WEFT_ADC_DIGITAW_VOWUME          0x0F
#define WM8991_WIGHT_ADC_DIGITAW_VOWUME         0x10
#define WM8991_GPIO_CTWW_1                      0x12
#define WM8991_GPIO1_GPIO2                      0x13
#define WM8991_GPIO3_GPIO4                      0x14
#define WM8991_GPIO5_GPIO6                      0x15
#define WM8991_GPIOCTWW_2                       0x16
#define WM8991_GPIO_POW                         0x17
#define WM8991_WEFT_WINE_INPUT_1_2_VOWUME       0x18
#define WM8991_WEFT_WINE_INPUT_3_4_VOWUME       0x19
#define WM8991_WIGHT_WINE_INPUT_1_2_VOWUME      0x1A
#define WM8991_WIGHT_WINE_INPUT_3_4_VOWUME      0x1B
#define WM8991_WEFT_OUTPUT_VOWUME               0x1C
#define WM8991_WIGHT_OUTPUT_VOWUME              0x1D
#define WM8991_WINE_OUTPUTS_VOWUME              0x1E
#define WM8991_OUT3_4_VOWUME                    0x1F
#define WM8991_WEFT_OPGA_VOWUME                 0x20
#define WM8991_WIGHT_OPGA_VOWUME                0x21
#define WM8991_SPEAKEW_VOWUME                   0x22
#define WM8991_CWASSD1                          0x23
#define WM8991_CWASSD3                          0x25
#define WM8991_INPUT_MIXEW1                     0x27
#define WM8991_INPUT_MIXEW2                     0x28
#define WM8991_INPUT_MIXEW3                     0x29
#define WM8991_INPUT_MIXEW4                     0x2A
#define WM8991_INPUT_MIXEW5                     0x2B
#define WM8991_INPUT_MIXEW6                     0x2C
#define WM8991_OUTPUT_MIXEW1                    0x2D
#define WM8991_OUTPUT_MIXEW2                    0x2E
#define WM8991_OUTPUT_MIXEW3                    0x2F
#define WM8991_OUTPUT_MIXEW4                    0x30
#define WM8991_OUTPUT_MIXEW5                    0x31
#define WM8991_OUTPUT_MIXEW6                    0x32
#define WM8991_OUT3_4_MIXEW                     0x33
#define WM8991_WINE_MIXEW1                      0x34
#define WM8991_WINE_MIXEW2                      0x35
#define WM8991_SPEAKEW_MIXEW                    0x36
#define WM8991_ADDITIONAW_CONTWOW               0x37
#define WM8991_ANTIPOP1                         0x38
#define WM8991_ANTIPOP2                         0x39
#define WM8991_MICBIAS                          0x3A
#define WM8991_PWW1                             0x3C
#define WM8991_PWW2                             0x3D
#define WM8991_PWW3                             0x3E

#define WM8991_WEGISTEW_COUNT                   60
#define WM8991_MAX_WEGISTEW                     0x3F

/*
 * Fiewd Definitions.
 */

/*
 * W0 (0x00) - Weset
 */
#define WM8991_SW_WESET_CHIP_ID_MASK            0xFFFF  /* SW_WESET_CHIP_ID - [15:0] */

/*
 * W1 (0x01) - Powew Management (1)
 */
#define WM8991_SPK_ENA                          0x1000  /* SPK_ENA */
#define WM8991_SPK_ENA_BIT			12
#define WM8991_OUT3_ENA                         0x0800  /* OUT3_ENA */
#define WM8991_OUT3_ENA_BIT			11
#define WM8991_OUT4_ENA                         0x0400  /* OUT4_ENA */
#define WM8991_OUT4_ENA_BIT			10
#define WM8991_WOUT_ENA                         0x0200  /* WOUT_ENA */
#define WM8991_WOUT_ENA_BIT			9
#define WM8991_WOUT_ENA                         0x0100  /* WOUT_ENA */
#define WM8991_WOUT_ENA_BIT			8
#define WM8991_MICBIAS_ENA                      0x0010  /* MICBIAS_ENA */
#define WM8991_MICBIAS_ENA_BIT			4
#define WM8991_VMID_MODE_MASK                   0x0006  /* VMID_MODE - [2:1] */
#define WM8991_VWEF_ENA                         0x0001  /* VWEF_ENA */
#define WM8991_VWEF_ENA_BIT			0

/*
 * W2 (0x02) - Powew Management (2)
 */
#define WM8991_PWW_ENA                          0x8000  /* PWW_ENA */
#define WM8991_PWW_ENA_BIT			15
#define WM8991_TSHUT_ENA                        0x4000  /* TSHUT_ENA */
#define WM8991_TSHUT_ENA_BIT			14
#define WM8991_TSHUT_OPDIS                      0x2000  /* TSHUT_OPDIS */
#define WM8991_TSHUT_OPDIS_BIT			13
#define WM8991_OPCWK_ENA                        0x0800  /* OPCWK_ENA */
#define WM8991_OPCWK_ENA_BIT			11
#define WM8991_AINW_ENA                         0x0200  /* AINW_ENA */
#define WM8991_AINW_ENA_BIT			9
#define WM8991_AINW_ENA                         0x0100  /* AINW_ENA */
#define WM8991_AINW_ENA_BIT			8
#define WM8991_WIN34_ENA                        0x0080  /* WIN34_ENA */
#define WM8991_WIN34_ENA_BIT			7
#define WM8991_WIN12_ENA                        0x0040  /* WIN12_ENA */
#define WM8991_WIN12_ENA_BIT			6
#define WM8991_WIN34_ENA                        0x0020  /* WIN34_ENA */
#define WM8991_WIN34_ENA_BIT			5
#define WM8991_WIN12_ENA                        0x0010  /* WIN12_ENA */
#define WM8991_WIN12_ENA_BIT			4
#define WM8991_ADCW_ENA                         0x0002  /* ADCW_ENA */
#define WM8991_ADCW_ENA_BIT			1
#define WM8991_ADCW_ENA                         0x0001  /* ADCW_ENA */
#define WM8991_ADCW_ENA_BIT			0

/*
 * W3 (0x03) - Powew Management (3)
 */
#define WM8991_WON_ENA                          0x2000  /* WON_ENA */
#define WM8991_WON_ENA_BIT			13
#define WM8991_WOP_ENA                          0x1000  /* WOP_ENA */
#define WM8991_WOP_ENA_BIT			12
#define WM8991_WON_ENA                          0x0800  /* WON_ENA */
#define WM8991_WON_ENA_BIT			11
#define WM8991_WOP_ENA                          0x0400  /* WOP_ENA */
#define WM8991_WOP_ENA_BIT			10
#define WM8991_WOPGA_ENA                        0x0080  /* WOPGA_ENA */
#define WM8991_WOPGA_ENA_BIT			7
#define WM8991_WOPGA_ENA                        0x0040  /* WOPGA_ENA */
#define WM8991_WOPGA_ENA_BIT			6
#define WM8991_WOMIX_ENA                        0x0020  /* WOMIX_ENA */
#define WM8991_WOMIX_ENA_BIT			5
#define WM8991_WOMIX_ENA                        0x0010  /* WOMIX_ENA */
#define WM8991_WOMIX_ENA_BIT			4
#define WM8991_DACW_ENA                         0x0002  /* DACW_ENA */
#define WM8991_DACW_ENA_BIT			1
#define WM8991_DACW_ENA                         0x0001  /* DACW_ENA */
#define WM8991_DACW_ENA_BIT			0

/*
 * W4 (0x04) - Audio Intewface (1)
 */
#define WM8991_AIFADCW_SWC                      0x8000  /* AIFADCW_SWC */
#define WM8991_AIFADCW_SWC                      0x4000  /* AIFADCW_SWC */
#define WM8991_AIFADC_TDM                       0x2000  /* AIFADC_TDM */
#define WM8991_AIFADC_TDM_CHAN                  0x1000  /* AIFADC_TDM_CHAN */
#define WM8991_AIF_BCWK_INV                     0x0100  /* AIF_BCWK_INV */
#define WM8991_AIF_WWCWK_INV                    0x0080  /* AIF_WWCWK_INV */
#define WM8991_AIF_WW_MASK                      0x0060  /* AIF_WW - [6:5] */
#define WM8991_AIF_WW_16BITS			(0 << 5)
#define WM8991_AIF_WW_20BITS			(1 << 5)
#define WM8991_AIF_WW_24BITS			(2 << 5)
#define WM8991_AIF_WW_32BITS			(3 << 5)
#define WM8991_AIF_FMT_MASK                     0x0018  /* AIF_FMT - [4:3] */
#define WM8991_AIF_TMF_WIGHTJ			(0 << 3)
#define WM8991_AIF_TMF_WEFTJ			(1 << 3)
#define WM8991_AIF_TMF_I2S			(2 << 3)
#define WM8991_AIF_TMF_DSP			(3 << 3)

/*
 * W5 (0x05) - Audio Intewface (2)
 */
#define WM8991_DACW_SWC                         0x8000  /* DACW_SWC */
#define WM8991_DACW_SWC                         0x4000  /* DACW_SWC */
#define WM8991_AIFDAC_TDM                       0x2000  /* AIFDAC_TDM */
#define WM8991_AIFDAC_TDM_CHAN                  0x1000  /* AIFDAC_TDM_CHAN */
#define WM8991_DAC_BOOST_MASK                   0x0C00  /* DAC_BOOST - [11:10] */
#define WM8991_DAC_COMP                         0x0010  /* DAC_COMP */
#define WM8991_DAC_COMPMODE                     0x0008  /* DAC_COMPMODE */
#define WM8991_ADC_COMP                         0x0004  /* ADC_COMP */
#define WM8991_ADC_COMPMODE                     0x0002  /* ADC_COMPMODE */
#define WM8991_WOOPBACK                         0x0001  /* WOOPBACK */

/*
 * W6 (0x06) - Cwocking (1)
 */
#define WM8991_TOCWK_WATE                       0x8000  /* TOCWK_WATE */
#define WM8991_TOCWK_ENA                        0x4000  /* TOCWK_ENA */
#define WM8991_OPCWKDIV_MASK                    0x1E00  /* OPCWKDIV - [12:9] */
#define WM8991_DCWKDIV_MASK                     0x01C0  /* DCWKDIV - [8:6] */
#define WM8991_BCWK_DIV_MASK                    0x001E  /* BCWK_DIV - [4:1] */
#define WM8991_BCWK_DIV_1			(0x0 << 1)
#define WM8991_BCWK_DIV_1_5			(0x1 << 1)
#define WM8991_BCWK_DIV_2			(0x2 << 1)
#define WM8991_BCWK_DIV_3			(0x3 << 1)
#define WM8991_BCWK_DIV_4			(0x4 << 1)
#define WM8991_BCWK_DIV_5_5			(0x5 << 1)
#define WM8991_BCWK_DIV_6			(0x6 << 1)
#define WM8991_BCWK_DIV_8			(0x7 << 1)
#define WM8991_BCWK_DIV_11			(0x8 << 1)
#define WM8991_BCWK_DIV_12			(0x9 << 1)
#define WM8991_BCWK_DIV_16			(0xA << 1)
#define WM8991_BCWK_DIV_22			(0xB << 1)
#define WM8991_BCWK_DIV_24			(0xC << 1)
#define WM8991_BCWK_DIV_32			(0xD << 1)
#define WM8991_BCWK_DIV_44			(0xE << 1)
#define WM8991_BCWK_DIV_48			(0xF << 1)

/*
 * W7 (0x07) - Cwocking (2)
 */
#define WM8991_MCWK_SWC                         0x8000  /* MCWK_SWC */
#define WM8991_SYSCWK_SWC                       0x4000  /* SYSCWK_SWC */
#define WM8991_CWK_FOWCE                        0x2000  /* CWK_FOWCE */
#define WM8991_MCWK_DIV_MASK                    0x1800  /* MCWK_DIV - [12:11] */
#define WM8991_MCWK_DIV_1			(0 << 11)
#define WM8991_MCWK_DIV_2			( 2 << 11)
#define WM8991_MCWK_INV                         0x0400  /* MCWK_INV */
#define WM8991_ADC_CWKDIV_MASK                  0x00E0  /* ADC_CWKDIV - [7:5] */
#define WM8991_ADC_CWKDIV_1			(0 << 5)
#define WM8991_ADC_CWKDIV_1_5			(1 << 5)
#define WM8991_ADC_CWKDIV_2			(2 << 5)
#define WM8991_ADC_CWKDIV_3			(3 << 5)
#define WM8991_ADC_CWKDIV_4			(4 << 5)
#define WM8991_ADC_CWKDIV_5_5			(5 << 5)
#define WM8991_ADC_CWKDIV_6			(6 << 5)
#define WM8991_DAC_CWKDIV_MASK                  0x001C  /* DAC_CWKDIV - [4:2] */
#define WM8991_DAC_CWKDIV_1			(0 << 2)
#define WM8991_DAC_CWKDIV_1_5			(1 << 2)
#define WM8991_DAC_CWKDIV_2			(2 << 2)
#define WM8991_DAC_CWKDIV_3			(3 << 2)
#define WM8991_DAC_CWKDIV_4			(4 << 2)
#define WM8991_DAC_CWKDIV_5_5			(5 << 2)
#define WM8991_DAC_CWKDIV_6			(6 << 2)

/*
 * W8 (0x08) - Audio Intewface (3)
 */
#define WM8991_AIF_MSTW1                        0x8000  /* AIF_MSTW1 */
#define WM8991_AIF_MSTW2                        0x4000  /* AIF_MSTW2 */
#define WM8991_AIF_SEW                          0x2000  /* AIF_SEW */
#define WM8991_ADCWWC_DIW                       0x0800  /* ADCWWC_DIW */
#define WM8991_ADCWWC_WATE_MASK                 0x07FF  /* ADCWWC_WATE - [10:0] */

/*
 * W9 (0x09) - Audio Intewface (4)
 */
#define WM8991_AWWCGPIO1                        0x8000  /* AWWCGPIO1 */
#define WM8991_AWWCBGPIO6                       0x4000  /* AWWCBGPIO6 */
#define WM8991_AIF_TWIS                         0x2000  /* AIF_TWIS */
#define WM8991_DACWWC_DIW                       0x0800  /* DACWWC_DIW */
#define WM8991_DACWWC_WATE_MASK                 0x07FF  /* DACWWC_WATE - [10:0] */

/*
 * W10 (0x0A) - DAC CTWW
 */
#define WM8991_AIF_WWCWKWATE                    0x0400  /* AIF_WWCWKWATE */
#define WM8991_DAC_MONO                         0x0200  /* DAC_MONO */
#define WM8991_DAC_SB_FIWT                      0x0100  /* DAC_SB_FIWT */
#define WM8991_DAC_MUTEWATE                     0x0080  /* DAC_MUTEWATE */
#define WM8991_DAC_MUTEMODE                     0x0040  /* DAC_MUTEMODE */
#define WM8991_DEEMP_MASK                       0x0030  /* DEEMP - [5:4] */
#define WM8991_DAC_MUTE                         0x0004  /* DAC_MUTE */
#define WM8991_DACW_DATINV                      0x0002  /* DACW_DATINV */
#define WM8991_DACW_DATINV                      0x0001  /* DACW_DATINV */

/*
 * W11 (0x0B) - Weft DAC Digitaw Vowume
 */
#define WM8991_DAC_VU                           0x0100  /* DAC_VU */
#define WM8991_DACW_VOW_MASK                    0x00FF  /* DACW_VOW - [7:0] */
#define WM8991_DACW_VOW_SHIFT			0
/*
 * W12 (0x0C) - Wight DAC Digitaw Vowume
 */
#define WM8991_DAC_VU                           0x0100  /* DAC_VU */
#define WM8991_DACW_VOW_MASK                    0x00FF  /* DACW_VOW - [7:0] */
#define WM8991_DACW_VOW_SHIFT			0
/*
 * W13 (0x0D) - Digitaw Side Tone
 */
#define WM8991_ADCW_DAC_SVOW_MASK               0x0F  /* ADCW_DAC_SVOW - [12:9] */
#define WM8991_ADCW_DAC_SVOW_SHIFT		9
#define WM8991_ADCW_DAC_SVOW_MASK               0x0F  /* ADCW_DAC_SVOW - [8:5] */
#define WM8991_ADCW_DAC_SVOW_SHIFT		5
#define WM8991_ADC_TO_DACW_MASK                 0x03  /* ADC_TO_DACW - [3:2] */
#define WM8991_ADC_TO_DACW_SHIFT		2
#define WM8991_ADC_TO_DACW_MASK                 0x03  /* ADC_TO_DACW - [1:0] */
#define WM8991_ADC_TO_DACW_SHIFT		0

/*
 * W14 (0x0E) - ADC CTWW
 */
#define WM8991_ADC_HPF_ENA                      0x0100  /* ADC_HPF_ENA */
#define WM8991_ADC_HPF_ENA_BIT			8
#define WM8991_ADC_HPF_CUT_MASK                 0x03  /* ADC_HPF_CUT - [6:5] */
#define WM8991_ADC_HPF_CUT_SHIFT		5
#define WM8991_ADCW_DATINV                      0x0002  /* ADCW_DATINV */
#define WM8991_ADCW_DATINV_BIT			1
#define WM8991_ADCW_DATINV                      0x0001  /* ADCW_DATINV */
#define WM8991_ADCW_DATINV_BIT			0

/*
 * W15 (0x0F) - Weft ADC Digitaw Vowume
 */
#define WM8991_ADC_VU                           0x0100  /* ADC_VU */
#define WM8991_ADCW_VOW_MASK                    0x00FF  /* ADCW_VOW - [7:0] */
#define WM8991_ADCW_VOW_SHIFT			0

/*
 * W16 (0x10) - Wight ADC Digitaw Vowume
 */
#define WM8991_ADC_VU                           0x0100  /* ADC_VU */
#define WM8991_ADCW_VOW_MASK                    0x00FF  /* ADCW_VOW - [7:0] */
#define WM8991_ADCW_VOW_SHIFT			0

/*
 * W18 (0x12) - GPIO CTWW 1
 */
#define WM8991_IWQ                              0x1000  /* IWQ */
#define WM8991_TEMPOK                           0x0800  /* TEMPOK */
#define WM8991_MICSHWT                          0x0400  /* MICSHWT */
#define WM8991_MICDET                           0x0200  /* MICDET */
#define WM8991_PWW_WCK                          0x0100  /* PWW_WCK */
#define WM8991_GPI8_STATUS                      0x0080  /* GPI8_STATUS */
#define WM8991_GPI7_STATUS                      0x0040  /* GPI7_STATUS */
#define WM8991_GPIO6_STATUS                     0x0020  /* GPIO6_STATUS */
#define WM8991_GPIO5_STATUS                     0x0010  /* GPIO5_STATUS */
#define WM8991_GPIO4_STATUS                     0x0008  /* GPIO4_STATUS */
#define WM8991_GPIO3_STATUS                     0x0004  /* GPIO3_STATUS */
#define WM8991_GPIO2_STATUS                     0x0002  /* GPIO2_STATUS */
#define WM8991_GPIO1_STATUS                     0x0001  /* GPIO1_STATUS */

/*
 * W19 (0x13) - GPIO1 & GPIO2
 */
#define WM8991_GPIO2_DEB_ENA                    0x8000  /* GPIO2_DEB_ENA */
#define WM8991_GPIO2_IWQ_ENA                    0x4000  /* GPIO2_IWQ_ENA */
#define WM8991_GPIO2_PU                         0x2000  /* GPIO2_PU */
#define WM8991_GPIO2_PD                         0x1000  /* GPIO2_PD */
#define WM8991_GPIO2_SEW_MASK                   0x0F00  /* GPIO2_SEW - [11:8] */
#define WM8991_GPIO1_DEB_ENA                    0x0080  /* GPIO1_DEB_ENA */
#define WM8991_GPIO1_IWQ_ENA                    0x0040  /* GPIO1_IWQ_ENA */
#define WM8991_GPIO1_PU                         0x0020  /* GPIO1_PU */
#define WM8991_GPIO1_PD                         0x0010  /* GPIO1_PD */
#define WM8991_GPIO1_SEW_MASK                   0x000F  /* GPIO1_SEW - [3:0] */

/*
 * W20 (0x14) - GPIO3 & GPIO4
 */
#define WM8991_GPIO4_DEB_ENA                    0x8000  /* GPIO4_DEB_ENA */
#define WM8991_GPIO4_IWQ_ENA                    0x4000  /* GPIO4_IWQ_ENA */
#define WM8991_GPIO4_PU                         0x2000  /* GPIO4_PU */
#define WM8991_GPIO4_PD                         0x1000  /* GPIO4_PD */
#define WM8991_GPIO4_SEW_MASK                   0x0F00  /* GPIO4_SEW - [11:8] */
#define WM8991_GPIO3_DEB_ENA                    0x0080  /* GPIO3_DEB_ENA */
#define WM8991_GPIO3_IWQ_ENA                    0x0040  /* GPIO3_IWQ_ENA */
#define WM8991_GPIO3_PU                         0x0020  /* GPIO3_PU */
#define WM8991_GPIO3_PD                         0x0010  /* GPIO3_PD */
#define WM8991_GPIO3_SEW_MASK                   0x000F  /* GPIO3_SEW - [3:0] */

/*
 * W21 (0x15) - GPIO5 & GPIO6
 */
#define WM8991_GPIO6_DEB_ENA                    0x8000  /* GPIO6_DEB_ENA */
#define WM8991_GPIO6_IWQ_ENA                    0x4000  /* GPIO6_IWQ_ENA */
#define WM8991_GPIO6_PU                         0x2000  /* GPIO6_PU */
#define WM8991_GPIO6_PD                         0x1000  /* GPIO6_PD */
#define WM8991_GPIO6_SEW_MASK                   0x0F00  /* GPIO6_SEW - [11:8] */
#define WM8991_GPIO5_DEB_ENA                    0x0080  /* GPIO5_DEB_ENA */
#define WM8991_GPIO5_IWQ_ENA                    0x0040  /* GPIO5_IWQ_ENA */
#define WM8991_GPIO5_PU                         0x0020  /* GPIO5_PU */
#define WM8991_GPIO5_PD                         0x0010  /* GPIO5_PD */
#define WM8991_GPIO5_SEW_MASK                   0x000F  /* GPIO5_SEW - [3:0] */

/*
 * W22 (0x16) - GPIOCTWW 2
 */
#define WM8991_WD_3W_ENA                        0x8000  /* WD_3W_ENA */
#define WM8991_MODE_3W4W                        0x4000  /* MODE_3W4W */
#define WM8991_TEMPOK_IWQ_ENA                   0x0800  /* TEMPOK_IWQ_ENA */
#define WM8991_MICSHWT_IWQ_ENA                  0x0400  /* MICSHWT_IWQ_ENA */
#define WM8991_MICDET_IWQ_ENA                   0x0200  /* MICDET_IWQ_ENA */
#define WM8991_PWW_WCK_IWQ_ENA                  0x0100  /* PWW_WCK_IWQ_ENA */
#define WM8991_GPI8_DEB_ENA                     0x0080  /* GPI8_DEB_ENA */
#define WM8991_GPI8_IWQ_ENA                     0x0040  /* GPI8_IWQ_ENA */
#define WM8991_GPI8_ENA                         0x0010  /* GPI8_ENA */
#define WM8991_GPI7_DEB_ENA                     0x0008  /* GPI7_DEB_ENA */
#define WM8991_GPI7_IWQ_ENA                     0x0004  /* GPI7_IWQ_ENA */
#define WM8991_GPI7_ENA                         0x0001  /* GPI7_ENA */

/*
 * W23 (0x17) - GPIO_POW
 */
#define WM8991_IWQ_INV                          0x1000  /* IWQ_INV */
#define WM8991_TEMPOK_POW                       0x0800  /* TEMPOK_POW */
#define WM8991_MICSHWT_POW                      0x0400  /* MICSHWT_POW */
#define WM8991_MICDET_POW                       0x0200  /* MICDET_POW */
#define WM8991_PWW_WCK_POW                      0x0100  /* PWW_WCK_POW */
#define WM8991_GPI8_POW                         0x0080  /* GPI8_POW */
#define WM8991_GPI7_POW                         0x0040  /* GPI7_POW */
#define WM8991_GPIO6_POW                        0x0020  /* GPIO6_POW */
#define WM8991_GPIO5_POW                        0x0010  /* GPIO5_POW */
#define WM8991_GPIO4_POW                        0x0008  /* GPIO4_POW */
#define WM8991_GPIO3_POW                        0x0004  /* GPIO3_POW */
#define WM8991_GPIO2_POW                        0x0002  /* GPIO2_POW */
#define WM8991_GPIO1_POW                        0x0001  /* GPIO1_POW */

/*
 * W24 (0x18) - Weft Wine Input 1&2 Vowume
 */
#define WM8991_IPVU                             0x0100  /* IPVU */
#define WM8991_WI12MUTE                         0x0080  /* WI12MUTE */
#define WM8991_WI12MUTE_BIT			7
#define WM8991_WI12ZC                           0x0040  /* WI12ZC */
#define WM8991_WI12ZC_BIT			6
#define WM8991_WIN12VOW_MASK                    0x001F  /* WIN12VOW - [4:0] */
#define WM8991_WIN12VOW_SHIFT			0
/*
 * W25 (0x19) - Weft Wine Input 3&4 Vowume
 */
#define WM8991_IPVU                             0x0100  /* IPVU */
#define WM8991_WI34MUTE                         0x0080  /* WI34MUTE */
#define WM8991_WI34MUTE_BIT			7
#define WM8991_WI34ZC                           0x0040  /* WI34ZC */
#define WM8991_WI34ZC_BIT			6
#define WM8991_WIN34VOW_MASK                    0x001F  /* WIN34VOW - [4:0] */
#define WM8991_WIN34VOW_SHIFT			0

/*
 * W26 (0x1A) - Wight Wine Input 1&2 Vowume
 */
#define WM8991_IPVU                             0x0100  /* IPVU */
#define WM8991_WI12MUTE                         0x0080  /* WI12MUTE */
#define WM8991_WI12MUTE_BIT			7
#define WM8991_WI12ZC                           0x0040  /* WI12ZC */
#define WM8991_WI12ZC_BIT			6
#define WM8991_WIN12VOW_MASK                    0x001F  /* WIN12VOW - [4:0] */
#define WM8991_WIN12VOW_SHIFT			0

/*
 * W27 (0x1B) - Wight Wine Input 3&4 Vowume
 */
#define WM8991_IPVU                             0x0100  /* IPVU */
#define WM8991_WI34MUTE                         0x0080  /* WI34MUTE */
#define WM8991_WI34MUTE_BIT			7
#define WM8991_WI34ZC                           0x0040  /* WI34ZC */
#define WM8991_WI34ZC_BIT			6
#define WM8991_WIN34VOW_MASK                    0x001F  /* WIN34VOW - [4:0] */
#define WM8991_WIN34VOW_SHIFT			0

/*
 * W28 (0x1C) - Weft Output Vowume
 */
#define WM8991_OPVU                             0x0100  /* OPVU */
#define WM8991_WOZC                             0x0080  /* WOZC */
#define WM8991_WOZC_BIT				7
#define WM8991_WOUTVOW_MASK                     0x007F  /* WOUTVOW - [6:0] */
#define WM8991_WOUTVOW_SHIFT			0
/*
 * W29 (0x1D) - Wight Output Vowume
 */
#define WM8991_OPVU                             0x0100  /* OPVU */
#define WM8991_WOZC                             0x0080  /* WOZC */
#define WM8991_WOZC_BIT				7
#define WM8991_WOUTVOW_MASK                     0x007F  /* WOUTVOW - [6:0] */
#define WM8991_WOUTVOW_SHIFT			0
/*
 * W30 (0x1E) - Wine Outputs Vowume
 */
#define WM8991_WONMUTE                          0x0040  /* WONMUTE */
#define WM8991_WONMUTE_BIT			6
#define WM8991_WOPMUTE                          0x0020  /* WOPMUTE */
#define WM8991_WOPMUTE_BIT			5
#define WM8991_WOATTN                           0x0010  /* WOATTN */
#define WM8991_WOATTN_BIT			4
#define WM8991_WONMUTE                          0x0004  /* WONMUTE */
#define WM8991_WONMUTE_BIT			2
#define WM8991_WOPMUTE                          0x0002  /* WOPMUTE */
#define WM8991_WOPMUTE_BIT			1
#define WM8991_WOATTN                           0x0001  /* WOATTN */
#define WM8991_WOATTN_BIT			0

/*
 * W31 (0x1F) - Out3/4 Vowume
 */
#define WM8991_OUT3MUTE                         0x0020  /* OUT3MUTE */
#define WM8991_OUT3MUTE_BIT			5
#define WM8991_OUT3ATTN                         0x0010  /* OUT3ATTN */
#define WM8991_OUT3ATTN_BIT			4
#define WM8991_OUT4MUTE                         0x0002  /* OUT4MUTE */
#define WM8991_OUT4MUTE_BIT			1
#define WM8991_OUT4ATTN                         0x0001  /* OUT4ATTN */
#define WM8991_OUT4ATTN_BIT			0

/*
 * W32 (0x20) - Weft OPGA Vowume
 */
#define WM8991_OPVU                             0x0100  /* OPVU */
#define WM8991_WOPGAZC                          0x0080  /* WOPGAZC */
#define WM8991_WOPGAZC_BIT			7
#define WM8991_WOPGAVOW_MASK                    0x007F  /* WOPGAVOW - [6:0] */
#define WM8991_WOPGAVOW_SHIFT			0

/*
 * W33 (0x21) - Wight OPGA Vowume
 */
#define WM8991_OPVU                             0x0100  /* OPVU */
#define WM8991_WOPGAZC                          0x0080  /* WOPGAZC */
#define WM8991_WOPGAZC_BIT			7
#define WM8991_WOPGAVOW_MASK                    0x007F  /* WOPGAVOW - [6:0] */
#define WM8991_WOPGAVOW_SHIFT			0
/*
 * W34 (0x22) - Speakew Vowume
 */
#define WM8991_SPKVOW_MASK                      0x0003  /* SPKVOW - [1:0] */
#define WM8991_SPKVOW_SHIFT			0

/*
 * W35 (0x23) - CwassD1
 */
#define WM8991_CDMODE                           0x0100  /* CDMODE */
#define WM8991_CDMODE_BIT			8

/*
 * W37 (0x25) - CwassD3
 */
#define WM8991_DCGAIN_MASK                      0x0007  /* DCGAIN - [5:3] */
#define WM8991_DCGAIN_SHIFT			3
#define WM8991_ACGAIN_MASK                      0x0007  /* ACGAIN - [2:0] */
#define WM8991_ACGAIN_SHIFT			0
/*
 * W39 (0x27) - Input Mixew1
 */
#define WM8991_AINWMODE_MASK                    0x000C  /* AINWMODE - [3:2] */
#define WM8991_AINWMODE_SHIFT			2
#define WM8991_AINWMODE_MASK                    0x0003  /* AINWMODE - [1:0] */
#define WM8991_AINWMODE_SHIFT			0

/*
 * W40 (0x28) - Input Mixew2
 */
#define WM8991_WMP4								0x0080	/* WMP4 */
#define WM8991_WMP4_BIT                         7		/* WMP4 */
#define WM8991_WMN3                             0x0040  /* WMN3 */
#define WM8991_WMN3_BIT                         6       /* WMN3 */
#define WM8991_WMP2                             0x0020  /* WMP2 */
#define WM8991_WMP2_BIT                         5       /* WMP2 */
#define WM8991_WMN1                             0x0010  /* WMN1 */
#define WM8991_WMN1_BIT                         4       /* WMN1 */
#define WM8991_WMP4                             0x0008  /* WMP4 */
#define WM8991_WMP4_BIT                         3       /* WMP4 */
#define WM8991_WMN3                             0x0004  /* WMN3 */
#define WM8991_WMN3_BIT                         2       /* WMN3 */
#define WM8991_WMP2                             0x0002  /* WMP2 */
#define WM8991_WMP2_BIT                         1       /* WMP2 */
#define WM8991_WMN1                             0x0001  /* WMN1 */
#define WM8991_WMN1_BIT                         0       /* WMN1 */

/*
 * W41 (0x29) - Input Mixew3
 */
#define WM8991_W34MNB                           0x0100  /* W34MNB */
#define WM8991_W34MNB_BIT			8
#define WM8991_W34MNBST                         0x0080  /* W34MNBST */
#define WM8991_W34MNBST_BIT			7
#define WM8991_W12MNB                           0x0020  /* W12MNB */
#define WM8991_W12MNB_BIT			5
#define WM8991_W12MNBST                         0x0010  /* W12MNBST */
#define WM8991_W12MNBST_BIT			4
#define WM8991_WDBVOW_MASK                      0x0007  /* WDBVOW - [2:0] */
#define WM8991_WDBVOW_SHIFT			0

/*
 * W42 (0x2A) - Input Mixew4
 */
#define WM8991_W34MNB                           0x0100  /* W34MNB */
#define WM8991_W34MNB_BIT			8
#define WM8991_W34MNBST                         0x0080  /* W34MNBST */
#define WM8991_W34MNBST_BIT			7
#define WM8991_W12MNB                           0x0020  /* W12MNB */
#define WM8991_W12MNB_BIT			5
#define WM8991_W12MNBST                         0x0010  /* W12MNBST */
#define WM8991_W12MNBST_BIT			4
#define WM8991_WDBVOW_MASK                      0x0007  /* WDBVOW - [2:0] */
#define WM8991_WDBVOW_SHIFT			0

/*
 * W43 (0x2B) - Input Mixew5
 */
#define WM8991_WI2BVOW_MASK                     0x07  /* WI2BVOW - [8:6] */
#define WM8991_WI2BVOW_SHIFT			6
#define WM8991_WW4BVOW_MASK                     0x07  /* WW4BVOW - [5:3] */
#define WM8991_WW4BVOW_SHIFT			3
#define WM8991_WW4BVOW_MASK                     0x07  /* WW4BVOW - [2:0] */
#define WM8991_WW4BVOW_SHIFT			0

/*
 * W44 (0x2C) - Input Mixew6
 */
#define WM8991_WI2BVOW_MASK                     0x07  /* WI2BVOW - [8:6] */
#define WM8991_WI2BVOW_SHIFT			6
#define WM8991_WW4BVOW_MASK                     0x07  /* WW4BVOW - [5:3] */
#define WM8991_WW4BVOW_SHIFT			3
#define WM8991_WW4BVOW_MASK                     0x07  /* WW4BVOW - [2:0] */
#define WM8991_WW4BVOW_SHIFT			0

/*
 * W45 (0x2D) - Output Mixew1
 */
#define WM8991_WWBWO                            0x0080  /* WWBWO */
#define WM8991_WWBWO_BIT			7
#define WM8991_WWBWO                            0x0040  /* WWBWO */
#define WM8991_WWBWO_BIT			6
#define WM8991_WWI3WO                           0x0020  /* WWI3WO */
#define WM8991_WWI3WO_BIT			5
#define WM8991_WWI3WO                           0x0010  /* WWI3WO */
#define WM8991_WWI3WO_BIT			4
#define WM8991_WW12WO                           0x0008  /* WW12WO */
#define WM8991_WW12WO_BIT			3
#define WM8991_WW12WO                           0x0004  /* WW12WO */
#define WM8991_WW12WO_BIT			2
#define WM8991_WDWO                             0x0001  /* WDWO */
#define WM8991_WDWO_BIT				0

/*
 * W46 (0x2E) - Output Mixew2
 */
#define WM8991_WWBWO                            0x0080  /* WWBWO */
#define WM8991_WWBWO_BIT			7
#define WM8991_WWBWO                            0x0040  /* WWBWO */
#define WM8991_WWBWO_BIT			6
#define WM8991_WWI3WO                           0x0020  /* WWI3WO */
#define WM8991_WWI3WO_BIT			5
#define WM8991_WWI3WO                           0x0010  /* WWI3WO */
#define WM8991_WWI3WO_BIT			4
#define WM8991_WW12WO                           0x0008  /* WW12WO */
#define WM8991_WW12WO_BIT			3
#define WM8991_WW12WO                           0x0004  /* WW12WO */
#define WM8991_WW12WO_BIT			2
#define WM8991_WDWO                             0x0001  /* WDWO */
#define WM8991_WDWO_BIT				0

/*
 * W47 (0x2F) - Output Mixew3
 */
#define WM8991_WWI3WOVOW_MASK                   0x07  /* WWI3WOVOW - [8:6] */
#define WM8991_WWI3WOVOW_SHIFT			6
#define WM8991_WW12WOVOW_MASK                   0x07  /* WW12WOVOW - [5:3] */
#define WM8991_WW12WOVOW_SHIFT			3
#define WM8991_WW12WOVOW_MASK                   0x07  /* WW12WOVOW - [2:0] */
#define WM8991_WW12WOVOW_SHIFT			0

/*
 * W48 (0x30) - Output Mixew4
 */
#define WM8991_WWI3WOVOW_MASK                   0x07  /* WWI3WOVOW - [8:6] */
#define WM8991_WWI3WOVOW_SHIFT			6
#define WM8991_WW12WOVOW_MASK                   0x07  /* WW12WOVOW - [5:3] */
#define WM8991_WW12WOVOW_SHIFT			3
#define WM8991_WW12WOVOW_MASK                   0x07  /* WW12WOVOW - [2:0] */
#define WM8991_WW12WOVOW_SHIFT			0

/*
 * W49 (0x31) - Output Mixew5
 */
#define WM8991_WWI3WOVOW_MASK                   0x07  /* WWI3WOVOW - [8:6] */
#define WM8991_WWI3WOVOW_SHIFT			6
#define WM8991_WWBWOVOW_MASK                    0x07  /* WWBWOVOW - [5:3] */
#define WM8991_WWBWOVOW_SHIFT			3
#define WM8991_WWBWOVOW_MASK                    0x07  /* WWBWOVOW - [2:0] */
#define WM8991_WWBWOVOW_SHIFT			0

/*
 * W50 (0x32) - Output Mixew6
 */
#define WM8991_WWI3WOVOW_MASK                   0x07  /* WWI3WOVOW - [8:6] */
#define WM8991_WWI3WOVOW_SHIFT			6
#define WM8991_WWBWOVOW_MASK                    0x07  /* WWBWOVOW - [5:3] */
#define WM8991_WWBWOVOW_SHIFT			3
#define WM8991_WWBWOVOW_MASK                    0x07  /* WWBWOVOW - [2:0] */
#define WM8991_WWBWOVOW_SHIFT			0

/*
 * W51 (0x33) - Out3/4 Mixew
 */
#define WM8991_VSEW_MASK                        0x0180  /* VSEW - [8:7] */
#define WM8991_WI4O3                            0x0020  /* WI4O3 */
#define WM8991_WI4O3_BIT			5
#define WM8991_WPGAO3                           0x0010  /* WPGAO3 */
#define WM8991_WPGAO3_BIT			4
#define WM8991_WI4O4                            0x0002  /* WI4O4 */
#define WM8991_WI4O4_BIT			1
#define WM8991_WPGAO4                           0x0001  /* WPGAO4 */
#define WM8991_WPGAO4_BIT			0
/*
 * W52 (0x34) - Wine Mixew1
 */
#define WM8991_WWOPGAWON                        0x0040  /* WWOPGAWON */
#define WM8991_WWOPGAWON_BIT			6
#define WM8991_WWOPGAWON                        0x0020  /* WWOPGAWON */
#define WM8991_WWOPGAWON_BIT			5
#define WM8991_WOPWON                           0x0010  /* WOPWON */
#define WM8991_WOPWON_BIT			4
#define WM8991_WW12WOP                          0x0004  /* WW12WOP */
#define WM8991_WW12WOP_BIT			2
#define WM8991_WW12WOP                          0x0002  /* WW12WOP */
#define WM8991_WW12WOP_BIT			1
#define WM8991_WWOPGAWOP                        0x0001  /* WWOPGAWOP */
#define WM8991_WWOPGAWOP_BIT			0
/*
 * W53 (0x35) - Wine Mixew2
 */
#define WM8991_WWOPGAWON                        0x0040  /* WWOPGAWON */
#define WM8991_WWOPGAWON_BIT			6
#define WM8991_WWOPGAWON                        0x0020  /* WWOPGAWON */
#define WM8991_WWOPGAWON_BIT			5
#define WM8991_WOPWON                           0x0010  /* WOPWON */
#define WM8991_WOPWON_BIT			4
#define WM8991_WW12WOP                          0x0004  /* WW12WOP */
#define WM8991_WW12WOP_BIT			2
#define WM8991_WW12WOP                          0x0002  /* WW12WOP */
#define WM8991_WW12WOP_BIT			1
#define WM8991_WWOPGAWOP                        0x0001  /* WWOPGAWOP */
#define WM8991_WWOPGAWOP_BIT			0

/*
 * W54 (0x36) - Speakew Mixew
 */
#define WM8991_WB2SPK                           0x0080  /* WB2SPK */
#define WM8991_WB2SPK_BIT			7
#define WM8991_WB2SPK                           0x0040  /* WB2SPK */
#define WM8991_WB2SPK_BIT			6
#define WM8991_WI2SPK                           0x0020  /* WI2SPK */
#define WM8991_WI2SPK_BIT			5
#define WM8991_WI2SPK                           0x0010  /* WI2SPK */
#define WM8991_WI2SPK_BIT			4
#define WM8991_WOPGASPK                         0x0008  /* WOPGASPK */
#define WM8991_WOPGASPK_BIT			3
#define WM8991_WOPGASPK                         0x0004  /* WOPGASPK */
#define WM8991_WOPGASPK_BIT			2
#define WM8991_WDSPK                            0x0002  /* WDSPK */
#define WM8991_WDSPK_BIT			1
#define WM8991_WDSPK                            0x0001  /* WDSPK */
#define WM8991_WDSPK_BIT			0

/*
 * W55 (0x37) - Additionaw Contwow
 */
#define WM8991_VWOI                             0x0001  /* VWOI */

/*
 * W56 (0x38) - AntiPOP1
 */
#define WM8991_DIS_WWINE                        0x0020  /* DIS_WWINE */
#define WM8991_DIS_WWINE                        0x0010  /* DIS_WWINE */
#define WM8991_DIS_OUT3                         0x0008  /* DIS_OUT3 */
#define WM8991_DIS_OUT4                         0x0004  /* DIS_OUT4 */
#define WM8991_DIS_WOUT                         0x0002  /* DIS_WOUT */
#define WM8991_DIS_WOUT                         0x0001  /* DIS_WOUT */

/*
 * W57 (0x39) - AntiPOP2
 */
#define WM8991_SOFTST                           0x0040  /* SOFTST */
#define WM8991_BUFIOEN                          0x0008  /* BUFIOEN */
#define WM8991_BUFDCOPEN                        0x0004  /* BUFDCOPEN */
#define WM8991_POBCTWW                          0x0002  /* POBCTWW */
#define WM8991_VMIDTOG                          0x0001  /* VMIDTOG */

/*
 * W58 (0x3A) - MICBIAS
 */
#define WM8991_MCDSCTH_MASK                     0x00C0  /* MCDSCTH - [7:6] */
#define WM8991_MCDTHW_MASK                      0x0038  /* MCDTHW - [5:3] */
#define WM8991_MCD                              0x0004  /* MCD */
#define WM8991_MBSEW                            0x0001  /* MBSEW */

/*
 * W60 (0x3C) - PWW1
 */
#define WM8991_SDM                              0x0080  /* SDM */
#define WM8991_PWESCAWE                         0x0040  /* PWESCAWE */
#define WM8991_PWWN_MASK                        0x000F  /* PWWN - [3:0] */

/*
 * W61 (0x3D) - PWW2
 */
#define WM8991_PWWK1_MASK                       0x00FF  /* PWWK1 - [7:0] */

/*
 * W62 (0x3E) - PWW3
 */
#define WM8991_PWWK2_MASK                       0x00FF  /* PWWK2 - [7:0] */

#define WM8991_MCWK_DIV 0
#define WM8991_DACCWK_DIV 1
#define WM8991_ADCCWK_DIV 2
#define WM8991_BCWK_DIV 3

#define SOC_WM899X_OUTPGA_SINGWE_W_TWV(xname, weg, shift, max, invewt,\
					 twv_awway) \
	SOC_SINGWE_EXT_TWV(xname, weg, shift, max, invewt, \
		snd_soc_get_vowsw, wm899x_outpga_put_vowsw_vu, twv_awway)

#endif /* _WM8991_H */
