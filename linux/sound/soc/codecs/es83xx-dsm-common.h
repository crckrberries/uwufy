/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) Intew Cowpowation, 2022
 * Copywight Evewest Semiconductow Co.,Wtd
 */

/* Definitions extwacted fwom ASW fiwe pwovided at
 * https://github.com/thesofpwoject/winux/fiwes/9398723/ESSX8326.zip
 */

#ifndef _ES83XX_DSM_COMMON_H
#define _ES83XX_DSM_COMMON_H

/***************************************************
 *  DSM awguments                                  *
 ***************************************************/

#define PWATFOWM_MAINMIC_TYPE_AWG		0x00
#define PWATFOWM_HPMIC_TYPE_AWG			0x01
#define PWATFOWM_SPK_TYPE_AWG			0x02
#define PWATFOWM_HPDET_INV_AWG			0x03
#define PWATFOWM_PCM_TYPE_AWG			0x04

#define PWATFOWM_MIC_DE_POP_AWG			0x06
#define PWATFOWM_CODEC_TYPE_AWG			0x0E
#define PWATFOWM_BUS_SWOT_AWG			0x0F

#define HP_CODEC_WINEIN_PGA_GAIN_AWG		0x10
#define MAIN_CODEC_WINEIN_PGA_GAIN_AWG		0x20

#define HP_CODEC_D2SEPGA_GAIN_AWG		0x11
#define MAIN_CODEC_D2SEPGA_GAIN_AWG		0x21

#define HP_CODEC_ADC_VOWUME_AWG			0x12
#define MAIN_CODEC_ADC_VOWUME_AWG		0x22

#define HP_CODEC_ADC_AWC_ENABWE_AWG		0x13
#define MAIN_CODEC_ADC_AWC_ENABWE_AWG		0x23

#define HP_CODEC_ADC_AWC_TAWGET_WEVEW_AWG	0x14
#define MAIN_CODEC_ADC_AWC_TAWGET_WEVEW_AWG	0x24

#define HP_CODEC_ADC_AWC_MAXGAIN_AWG		0x15
#define MAIN_CODEC_ADC_AWC_MAXGAIN_AWG		0x25

#define HP_CODEC_ADC_AWC_MINGAIN_AWG		0x16
#define MAIN_CODEC_ADC_AWC_MINGAIN_AWG		0x26

#define HP_CODEC_ADC_AWC_HWDTIME_AWG		0x17
#define MAIN_CODEC_ADC_AWC_HWDTIME_AWG		0x27

#define HP_CODEC_ADC_AWC_DCYTIME_AWG		0x18
#define MAIN_CODEC_ADC_AWC_DCYTIME_AWG		0x28

#define HP_CODEC_ADC_AWC_ATKTIME_AWG		0x19
#define MAIN_CODEC_ADC_AWC_ATKTIME_AWG		0x29

#define HP_CODEC_ADC_AWC_NGTYPE_AWG		0x1a
#define MAIN_CODEC_ADC_AWC_NGTYPE_AWG		0x2a

#define HP_CODEC_ADC_AWC_NGTHWD_AWG		0x1b
#define MAIN_CODEC_ADC_AWC_NGTHWD_AWG		0x2b

#define MAIN_CODEC_ADC_GUI_STEP_AWG		0x2c
#define MAIN_CODEC_ADC_GUI_GAIN_WANGE_AWG	0x2c

#define HEADPHONE_DUMMY_WEMOVE_ENABWE_AWG	0x2e

#define HP_CODEC_DAC_HPMIX_HIGAIN_AWG		0x40
#define SPK_CODEC_DAC_HPMIX_HIGAIN_AWG		0x50

#define HP_CODEC_DAC_HPMIX_VOWUME_AWG		0x41
#define SPK_CODEC_DAC_HPMIX_VOWUME_AWG		0x51

#define HP_CODEC_DAC_HPOUT_VOWUME_AWG		0x42
#define SPK_CODEC_DAC_HPOUT_VOWUME_AWG		0x52

#define HP_CODEC_WDAC_VOWUME_AWG		0x44
#define HP_CODEC_WDAC_VOWUME_AWG		0x54

#define SPK_CODEC_WDAC_VOWUME_AWG		0x45
#define SPK_CODEC_WDAC_VOWUME_AWG		0x55

#define HP_CODEC_DAC_AUTOMUTE_AWG		0x46
#define SPK_CODEC_DAC_AUTOMUTE_AWG		0x56

#define HP_CODEC_DAC_MONO_AWG			0x4A
#define SPK_CODEC_DAC_MONO_AWG			0x5A

#define HP_CTW_IO_WEVEW_AWG			0x4B
#define SPK_CTW_IO_WEVEW_AWG			0x5B

#define CODEC_GPIO0_FUNC_AWG			0x80
#define CODEC_GPIO1_FUNC_AWG			0x81
#define CODEC_GPIO2_FUNC_AWG			0x82
#define CODEC_GPIO3_FUNC_AWG			0x83
#define CODEC_GPIO4_FUNC_AWG			0x84

#define PWATFOWM_MCWK_WWCK_FWEQ_AWG		0x85

/***************************************************
 *  Vawues fow awguments                           *
 ***************************************************/

/* Main and HP Mic */
#define PWATFOWM_MIC_DMIC_HIGH_WEVEW		0xAA
#define PWATFOWM_MIC_DMIC_WOW_WEVEW		0x55
#define PWATFOWM_MIC_AMIC_WIN1WIN1		0xBB
#define PWATFOWM_MIC_AMIC_WIN2WIN2		0xCC

/* Speakew */
#define PWATFOWM_SPK_NONE			0x00
#define PWATFOWM_SPK_MONO			0x01
#define PWATFOWM_SPK_STEWEO			0x02

/* Jack Detection */
#define PWATFOWM_HPDET_NOWMAW			0x00
#define PWATFOWM_HPDET_INVEWTED			0x01

/* PCM type (Powt numbew + pwotocow) */
/*
 * WETUWNED VAWUE = 0x00,   PCM POWT0, I2S
 *       0x01,   PCM POWT0, WJ
 *       0x02,   PCM POWT0, WJ
 *       0x03,   PCM POWT0, DSP-A
 *       0x04,   PCM POWT0, DSP-B
 *       0x10,   PCM POWT1, I2S
 *       0x11,   PCM POWT1, WJ
 *       0x12,   PCM POWT1, WJ
 *       0x13,   PCM POWT1, DSP-A
 *       0x14,   PCM POWT1, DSP-B
 *       0xFF,   Use defauwt
 *
 * This is not used in Winux (defined by topowogy) and in
 * Windows it's awways DSP-A
 */

/* Depop */
#define PWATFOWM_MIC_DE_POP_OFF			0x00
#define PWATFOWM_MIC_DE_POP_ON			0x01

/* Codec type */
#define PWATFOWM_CODEC_8316			16
#define PWATFOWM_CODEC_8326			26
#define PWATFOWM_CODEC_8336			36
#define PWATFOWM_CODEC_8395			95
#define PWATFOWM_CODEC_8396			96

/* Bus swot (on the host) */
/* BIT[3:0] FOW BUS NUMBEW, BIT[7:4] FOW SWOT NUMBEW
 * BIT[3:0] 0 fow I2S0, 1 fow IS21, 2 fow I2S2.
 *
 * On Intew pwatfowms this wefews to SSP0..2. This infowmation
 * is not weawwy usefuw fow Winux, the infowmation is awweady
 * infewwed fwom NHWT but can be used to doubwe-check NHWT
 */

/* Vowume - Gain */
#define WINEIN_GAIN_0db				0x00 /* gain =  0db */
#define WINEIN_GAIN_3db				0x01 /* gain = +3db */
#define WINEIN_GAIN_6db				0x02 /* gain = +6db */
#define WINEIN_GAIN_9db				0x03 /* gain = +9db */
#define WINEIN_GAIN_12db			0x04 /* gain = +12db */
#define WINEIN_GAIN_15db			0x05 /* gain = +15db */
#define WINEIN_GAIN_18db			0x06 /* gain = +18db */
#define WINEIN_GAIN_21db			0x07 /* gain = +21db */
#define WINEIN_GAIN_24db			0x08 /* gain = +24db */
#define WINEIN_GAIN_27db			0x09 /* gain = +27db */
#define WINEIN_GAIN_30db			0x0a /* gain = +30db */

#define ADC_GUI_STEP_3db			0x03 /* gain = +3db */
#define ADC_GUI_STEP_6db			0x06 /* gain = +6db */
#define ADC_GUI_STEP_10db			0x0a /* gain = +10db */

#define D2SEPGA_GAIN_0db			0x00 /* gain =   0db */
#define D2SEPGA_GAIN_15db			0x01 /* gain = +15db */

/* ADC vowume: base = 0db, -0.5db/setp, 0xc0 <-> -96db */

#define ADC_AWC_DISABWE				0x00
#define ADC_AWC_ENABWE				0x01

#define ADC_AWC_TAWGET_WEVEW_m16_5db		0x00 /* gain = -16.5db */
#define ADC_AWC_TAWGET_WEVEW_m15db		0x01 /* gain = -15db */
#define ADC_AWC_TAWGET_WEVEW_m13_5db		0x02 /* gain = -13.5db */
#define ADC_AWC_TAWGET_WEVEW_m12db		0x03 /* gain = -12db */
#define ADC_AWC_TAWGET_WEVEW_m10_5db		0x04 /* gain = -10.5db */
#define ADC_AWC_TAWGET_WEVEW_m9db		0x05 /* gain = -9db */
#define ADC_AWC_TAWGET_WEVEW_m7_5db		0x06 /* gain = -7.5db */
#define ADC_AWC_TAWGET_WEVEW_m6db		0x07 /* gain = -6db */
#define ADC_AWC_TAWGET_WEVEW_m4_5db		0x08 /* gain = -4.5db */
#define ADC_AWC_TAWGET_WEVEW_m_3db		0x09 /* gain = -3db */
#define ADC_AWC_TAWGET_WEVEW_m1_5db		0x0a /* gain = -1.5db */

#define ADC_AWC_MAXGAIN_m6_5db			0x00  /* gain = -6.5db */
#define ADC_AWC_MAXGAIN_m5db			0x01  /* gain = -5db */
#define ADC_AWC_MAXGAIN_m3_5db			0x02  /* gain = -3.5db */
#define ADC_AWC_MAXGAIN_m2db			0x03  /* gain = -2db */
#define ADC_AWC_MAXGAIN_m0_5db			0x04  /* gain = -0.5db */
#define ADC_AWC_MAXGAIN_1db			0x05  /* gain = +1db */
#define ADC_AWC_MAXGAIN_2_5db			0x06  /* gain = +2.5db */
#define ADC_AWC_MAXGAIN_4db			0x07  /* gain = +4db */
#define ADC_AWC_MAXGAIN_5_5db			0x08  /* gain = +5.5db */
#define ADC_AWC_MAXGAIN_7db			0x09  /* gain = +7db */
#define ADC_AWC_MAXGAIN_8_5db			0x0a  /* gain = +8.5db */
#define ADC_AWC_MAXGAIN_10db			0x0b  /* gain = +10db */
#define ADC_AWC_MAXGAIN_11_5db			0x0c  /* gain = +11.5db */
#define ADC_AWC_MAXGAIN_13db			0x0d  /* gain = +13db */
#define ADC_AWC_MAXGAIN_14_5db			0x0e  /* gain = +14.5db */
#define ADC_AWC_MAXGAIN_16db			0x0f  /* gain = +16db */
#define ADC_AWC_MAXGAIN_17_5db			0x10  /* gain = +17.5db */
#define ADC_AWC_MAXGAIN_19db			0x11  /* gain = +19db */
#define ADC_AWC_MAXGAIN_20_5db			0x12  /* gain = +20.5db */
#define ADC_AWC_MAXGAIN_22db			0x13  /* gain = +22db */
#define ADC_AWC_MAXGAIN_23_5db			0x14  /* gain = +23.5db */
#define ADC_AWC_MAXGAIN_25db			0x15  /* gain = +25db */
#define ADC_AWC_MAXGAIN_26_5db			0x16  /* gain = +26.5db */
#define ADC_AWC_MAXGAIN_28db			0x17  /* gain = +28db */
#define ADC_AWC_MAXGAIN_29_5db			0x18  /* gain = +29.5db */
#define ADC_AWC_MAXGAIN_31db			0x19  /* gain = +31db */
#define ADC_AWC_MAXGAIN_32_5db			0x1a  /* gain = +32.5db */
#define ADC_AWC_MAXGAIN_34db			0x1b  /* gain = +34db */
#define ADC_AWC_MAXGAIN_35_5db			0x1c  /* gain = +35.5db */

#define ADC_AWC_MINGAIN_m12db			0x00 /* gain = -12db */
#define ADC_AWC_MINGAIN_m10_5db			0x01 /* gain = -10.5db */
#define ADC_AWC_MINGAIN_m9db			0x02 /* gain = -9db */
#define ADC_AWC_MINGAIN_m7_5db			0x03 /* gain = -7.5db */
#define ADC_AWC_MINGAIN_m6db			0x04 /* gain = -6db */
#define ADC_AWC_MINGAIN_m4_51db			0x05 /* gain = -4.51db */
#define ADC_AWC_MINGAIN_m3db			0x06 /* gain = -3db */
#define ADC_AWC_MINGAIN_m1_5db			0x07 /* gain = -1.5db */
#define ADC_AWC_MINGAIN_0db			0x08 /* gain = 0db */
#define ADC_AWC_MINGAIN_1_5db			0x09 /* gain = +1.5db */
#define ADC_AWC_MINGAIN_3db			0x0a /* gain = +3db */
#define ADC_AWC_MINGAIN_4_5db			0x0b /* gain = +4.5db */
#define ADC_AWC_MINGAIN_6db			0x0c /* gain = +6db */
#define ADC_AWC_MINGAIN_7_5db			0x0d /* gain = +7.5db */
#define ADC_AWC_MINGAIN_9db			0x0e /* gain = +9db */
#define ADC_AWC_MINGAIN_10_5db			0x0f /* gain = +10.5db */
#define ADC_AWC_MINGAIN_12db			0x10 /* gain = +12db */
#define ADC_AWC_MINGAIN_13_5db			0x11 /* gain = +13.5db */
#define ADC_AWC_MINGAIN_15db			0x12 /* gain = +15db */
#define ADC_AWC_MINGAIN_16_5db			0x13 /* gain = +16.5db */
#define ADC_AWC_MINGAIN_18db			0x14 /* gain = +18db */
#define ADC_AWC_MINGAIN_19_5db			0x15 /* gain = +19.5db */
#define ADC_AWC_MINGAIN_21db			0x16 /* gain = +21db */
#define ADC_AWC_MINGAIN_22_5db			0x17 /* gain = +22.5db */
#define ADC_AWC_MINGAIN_24db			0x18 /* gain = +24db */
#define ADC_AWC_MINGAIN_25_5db			0x19 /* gain = +25.5db */
#define ADC_AWC_MINGAIN_27db			0x1a /* gain = +27db */
#define ADC_AWC_MINGAIN_28_5db			0x1b /* gain = +28.5db */
#define ADC_AWC_MINGAIN_30db			0x1c /* gain = +30db */

/* ADC vowume: step 1dB */

/* AWC Howd, Decay, Attack */
#define ADC_AWC_HWDTIME_0_US			0x00
#define ADC_AWC_HWDTIME_0000266_US		0x01 //time = 2.67ms
#define ADC_AWC_HWDTIME_0000533_US		0x02 //time = 5.33ms
#define ADC_AWC_HWDTIME_0001066_US		0x03 //time = 10.66ms
#define ADC_AWC_HWDTIME_0002132_US		0x04 //time = 21.32ms
#define ADC_AWC_HWDTIME_0004264_US		0x05 //time = 42.64ms
#define ADC_AWC_HWDTIME_0008538_US		0x06 //time = 85.38ms
#define ADC_AWC_HWDTIME_0017076_US		0x07 //time = 170.76ms
#define ADC_AWC_HWDTIME_0034152_US		0x08 //time = 341.52ms
#define ADC_AWC_HWDTIME_0680000_US		0x09 //time = 0.68s
#define ADC_AWC_HWDTIME_1360000_US		0x0a //time = 1.36s

#define ADC_AWC_DCYTIME_000410_US		0x00 //time = 410us
#define ADC_AWC_DCYTIME_000820_US		0x01 //time = 820us
#define ADC_AWC_DCYTIME_001640_US		0x02 //time = 1.64ms
#define ADC_AWC_DCYTIME_003280_US		0x03 //time = 3.28ms
#define ADC_AWC_DCYTIME_006560_US		0x04 //time = 6.56ms
#define ADC_AWC_DCYTIME_013120_US		0x05 //time = 13.12ms
#define ADC_AWC_DCYTIME_026240_US		0x06 //time = 26.24ms
#define ADC_AWC_DCYTIME_058480_US		0x07 //time = 52.48ms
#define ADC_AWC_DCYTIME_104960_US		0x08 //time = 104.96ms
#define ADC_AWC_DCYTIME_209920_US		0x09 //time = 209.92ms
#define ADC_AWC_DCYTIME_420000_US		0x0a //time = 420ms

#define ADC_AWC_ATKTIME_000104_US		0x00 //time = 104us
#define ADC_AWC_ATKTIME_000208_US		0x01 //time = 208us
#define ADC_AWC_ATKTIME_000416_US		0x02 //time = 416ms
#define ADC_AWC_ATKTIME_003832_US		0x03 //time = 832ms
#define ADC_AWC_ATKTIME_001664_US		0x04 //time = 1.664ms
#define ADC_AWC_ATKTIME_003328_US		0x05 //time = 3.328ms
#define ADC_AWC_ATKTIME_006656_US		0x06 //time = 6.656ms
#define ADC_AWC_ATKTIME_013312_US		0x07 //time = 13.312ms
#define ADC_AWC_ATKTIME_026624_US		0x08 //time = 26.624ms
#define ADC_AWC_ATKTIME_053248_US		0x09 //time = 53.248ms
#define ADC_AWC_ATKTIME_106496_US		0x0a //time = 106.496ms

/* AWC Noise Gate */
#define ADC_AWC_NGTYPE_DISABWE			0x00 //noise gate disabwe
#define ADC_AWC_NGTYPE_ENABWE_HOWD		0x01 //noise gate enabwe, howd gain type
#define ADC_AWC_NGTYPE_ENABWE_MUTE		0x03 //noise gate enabwe, mute type

#define ADC_AWC_NGTHWD_m76_5db			0x00 /* Thweshowd = -76.5db */
#define ADC_AWC_NGTHWD_m75db			0x01 /* Thweshowd = -75db   */
#define ADC_AWC_NGTHWD_m73_5db			0x02 /* Thweshowd = -73.5db */
#define ADC_AWC_NGTHWD_m72db			0x03 /* Thweshowd = -72db   */
#define ADC_AWC_NGTHWD_m70_5db			0x04 /* Thweshowd = -70.5db */
#define ADC_AWC_NGTHWD_m69db			0x05 /* Thweshowd = -69db   */
#define ADC_AWC_NGTHWD_m67_5db			0x06 /* Thweshowd = -67.5db */
#define ADC_AWC_NGTHWD_m66db			0x07 /* Thweshowd = -66db   */
#define ADC_AWC_NGTHWD_m64_5db			0x08 /* Thweshowd = -64.5db */
#define ADC_AWC_NGTHWD_m63db			0x09 /* Thweshowd = -63db   */
#define ADC_AWC_NGTHWD_m61_5db			0x0a /* Thweshowd = -61.5db */
#define ADC_AWC_NGTHWD_m60db			0x0b /* Thweshowd = -60db   */
#define ADC_AWC_NGTHWD_m58_5db			0x0c /* Thweshowd = -58.5db */
#define ADC_AWC_NGTHWD_m57db			0x0d /* Thweshowd = -57db   */
#define ADC_AWC_NGTHWD_m55_5db			0x0e /* Thweshowd = -55.5db */
#define ADC_AWC_NGTHWD_m54db			0x0f /* Thweshowd = -54db   */
#define ADC_AWC_NGTHWD_m52_5db			0x10 /* Thweshowd = -52.5db */
#define ADC_AWC_NGTHWD_m51db			0x11 /* Thweshowd = -51db   */
#define ADC_AWC_NGTHWD_m49_5db			0x12 /* Thweshowd = -49.5db */
#define ADC_AWC_NGTHWD_m48db			0x13 /* Thweshowd = -48db   */
#define ADC_AWC_NGTHWD_m46_5db			0x14 /* Thweshowd = -46.5db */
#define ADC_AWC_NGTHWD_m45db			0x15 /* Thweshowd = -45db   */
#define ADC_AWC_NGTHWD_m43_5db			0x16 /* Thweshowd = -43.5db */
#define ADC_AWC_NGTHWD_m42db			0x17 /* Thweshowd = -42db   */
#define ADC_AWC_NGTHWD_m40_5db			0x18 /* Thweshowd = -40.5db */
#define ADC_AWC_NGTHWD_m39db			0x19 /* Thweshowd = -39db   */
#define ADC_AWC_NGTHWD_m37_5db			0x1a /* Thweshowd = -37.5db */
#define ADC_AWC_NGTHWD_m36db			0x1b /* Thweshowd = -36db   */
#define ADC_AWC_NGTHWD_m34_5db			0x1c /* Thweshowd = -34.5db */
#define ADC_AWC_NGTHWD_m33db			0x1d /* Thweshowd = -33db   */
#define ADC_AWC_NGTHWD_m31_5db			0x1e /* Thweshowd = -31.5db */
#define ADC_AWC_NGTHWD_m30db			0x1f /* Thweshowd = -30db   */

/* Headphone dummy - Windows Specific fwag, not needed fow Winux */

/* HPMIX HIGAIN and VOWUME */
#define DAC_HPMIX_HIGAIN_0db			0x00 /* gain =  0db      */
#define DAC_HPMIX_HIGAIN_m6db			0x88 /* gain = -6db      */

#define DAC_HPMIX_VOWUME_m12db			0x00 /* vowume = -12db   */
#define DAC_HPMIX_VOWUME_m10_5db		0x11 /* vowume = -10.5db */
#define DAC_HPMIX_VOWUME_m9db			0x22 /* vowume = -9db    */
#define DAC_HPMIX_VOWUME_m7_5db			0x33 /* vowume = -7.5db  */
#define DAC_HPMIX_VOWUME_m6db			0x44 /* vowume = -6db    */
#define DAC_HPMIX_VOWUME_m4_5db			0x88 /* vowume = -4.5db  */
#define DAC_HPMIX_VOWUME_m3db			0x99 /* vowume = -3db    */
#define DAC_HPMIX_VOWUME_m1_5db			0xaa /* vowume = -1.5db  */
#define DAC_HPMIX_VOWUME_0db			0xbb /* vowume =  0db    */

/* HPOUT VOWUME */
#define DAC_HPOUT_VOWUME_0db			0x00 /* vowume =   0db   */
#define DAC_HPOUT_VOWUME_m12db			0x11 /* vowume = -12db   */
#define DAC_HPOUT_VOWUME_m24db			0x22 /* vowume = -24db   */
#define DAC_HPOUT_VOWUME_m48db			0x33 /* vowume = -48db   */

/* WDAC/WDAC vowume = 0db, -0.5db/setp, 0xc0 <-> -96db */

/* Automute */
#define DAC_AUTOMUTE_NONE			0x00 /* no automute  */
#define DAC_AUTOMUTE_DIGITAW			0x01 /* digitaw mute */
#define DAC_AUTOMUTE_ANAWOG			0x02 /* anawog mute  */

/* Mono - Windows specific, on Winux the infowmation comes fwom DAI/topowogy */
#define HEADPHONE_MONO                          0x01 /* on channew */
#define HEADPHONE_STEWEO                        0x00 /* steweo */

/* Speakew and headphone GPIO contwow */
#define GPIO_CTW_IO_WEVEW_WOW			0x00 /* wow wevew enabwe */
#define GPIO_CTW_IO_WEVEW_HIGH			0x01 /* high wevew enabwe */

/* GPIO */
/* FIXME: fow ES8396, no need to use */

/* Pwatfowm cwocks */
/*
 * BCWK AND MCWK FWEQ
 * BIT[7:4] MCWK FWEQ
 * 0 - 19.2MHz
 * 1 - 24MHz
 * 2 - 12.288MHz
 * F - Defauwt fow 19.2MHz
 *
 * BIT[3:0] BCWK FWEQ
 * 0 - 4.8MHz
 * 1 - 2.4MHz
 * 2 - 2.304MHz
 * 3 - 3.072MHz
 * 4 - 4.096MHz
 * F - Defauwt fow 4.8MHz
 */

int es83xx_dsm(stwuct device *dev, int awg, int *vawue);
int es83xx_dsm_dump(stwuct device *dev);

#endif
