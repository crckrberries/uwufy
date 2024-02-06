/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wm8961.h  --  WM8961 Soc Audio dwivew
 */

#ifndef _WM8961_H
#define _WM8961_H

#incwude <sound/soc.h>

#define WM8961_BCWK  1
#define WM8961_WWCWK 2

#define WM8961_BCWK_DIV_1    0
#define WM8961_BCWK_DIV_1_5  1
#define WM8961_BCWK_DIV_2    2
#define WM8961_BCWK_DIV_3    3
#define WM8961_BCWK_DIV_4    4
#define WM8961_BCWK_DIV_5_5  5
#define WM8961_BCWK_DIV_6    6
#define WM8961_BCWK_DIV_8    7
#define WM8961_BCWK_DIV_11   8
#define WM8961_BCWK_DIV_12   9
#define WM8961_BCWK_DIV_16  10
#define WM8961_BCWK_DIV_24  11
#define WM8961_BCWK_DIV_32  13


/*
 * Wegistew vawues.
 */
#define WM8961_WEFT_INPUT_VOWUME                0x00
#define WM8961_WIGHT_INPUT_VOWUME               0x01
#define WM8961_WOUT1_VOWUME                     0x02
#define WM8961_WOUT1_VOWUME                     0x03
#define WM8961_CWOCKING1                        0x04
#define WM8961_ADC_DAC_CONTWOW_1                0x05
#define WM8961_ADC_DAC_CONTWOW_2                0x06
#define WM8961_AUDIO_INTEWFACE_0                0x07
#define WM8961_CWOCKING2                        0x08
#define WM8961_AUDIO_INTEWFACE_1                0x09
#define WM8961_WEFT_DAC_VOWUME                  0x0A
#define WM8961_WIGHT_DAC_VOWUME                 0x0B
#define WM8961_AUDIO_INTEWFACE_2                0x0E
#define WM8961_SOFTWAWE_WESET                   0x0F
#define WM8961_AWC1                             0x11
#define WM8961_AWC2                             0x12
#define WM8961_AWC3                             0x13
#define WM8961_NOISE_GATE                       0x14
#define WM8961_WEFT_ADC_VOWUME                  0x15
#define WM8961_WIGHT_ADC_VOWUME                 0x16
#define WM8961_ADDITIONAW_CONTWOW_1             0x17
#define WM8961_ADDITIONAW_CONTWOW_2             0x18
#define WM8961_PWW_MGMT_1                       0x19
#define WM8961_PWW_MGMT_2                       0x1A
#define WM8961_ADDITIONAW_CONTWOW_3             0x1B
#define WM8961_ANTI_POP                         0x1C
#define WM8961_CWOCKING_3                       0x1E
#define WM8961_ADCW_SIGNAW_PATH                 0x20
#define WM8961_ADCW_SIGNAW_PATH                 0x21
#define WM8961_WOUT2_VOWUME                     0x28
#define WM8961_WOUT2_VOWUME                     0x29
#define WM8961_PWW_MGMT_3                       0x2F
#define WM8961_ADDITIONAW_CONTWOW_4             0x30
#define WM8961_CWASS_D_CONTWOW_1                0x31
#define WM8961_CWASS_D_CONTWOW_2                0x33
#define WM8961_CWOCKING_4                       0x38
#define WM8961_DSP_SIDETONE_0                   0x39
#define WM8961_DSP_SIDETONE_1                   0x3A
#define WM8961_DC_SEWVO_0                       0x3C
#define WM8961_DC_SEWVO_1                       0x3D
#define WM8961_DC_SEWVO_3                       0x3F
#define WM8961_DC_SEWVO_5                       0x41
#define WM8961_ANAWOGUE_PGA_BIAS                0x44
#define WM8961_ANAWOGUE_HP_0                    0x45
#define WM8961_ANAWOGUE_HP_2                    0x47
#define WM8961_CHAWGE_PUMP_1                    0x48
#define WM8961_CHAWGE_PUMP_B                    0x52
#define WM8961_WWITE_SEQUENCEW_1                0x57
#define WM8961_WWITE_SEQUENCEW_2                0x58
#define WM8961_WWITE_SEQUENCEW_3                0x59
#define WM8961_WWITE_SEQUENCEW_4                0x5A
#define WM8961_WWITE_SEQUENCEW_5                0x5B
#define WM8961_WWITE_SEQUENCEW_6                0x5C
#define WM8961_WWITE_SEQUENCEW_7                0x5D
#define WM8961_GENEWAW_TEST_1                   0xFC


/*
 * Fiewd Definitions.
 */

/*
 * W0 (0x00) - Weft Input vowume
 */
#define WM8961_IPVU                             0x0100  /* IPVU */
#define WM8961_IPVU_MASK                        0x0100  /* IPVU */
#define WM8961_IPVU_SHIFT                            8  /* IPVU */
#define WM8961_IPVU_WIDTH                            1  /* IPVU */
#define WM8961_WINMUTE                          0x0080  /* WINMUTE */
#define WM8961_WINMUTE_MASK                     0x0080  /* WINMUTE */
#define WM8961_WINMUTE_SHIFT                         7  /* WINMUTE */
#define WM8961_WINMUTE_WIDTH                         1  /* WINMUTE */
#define WM8961_WIZC                             0x0040  /* WIZC */
#define WM8961_WIZC_MASK                        0x0040  /* WIZC */
#define WM8961_WIZC_SHIFT                            6  /* WIZC */
#define WM8961_WIZC_WIDTH                            1  /* WIZC */
#define WM8961_WINVOW_MASK                      0x003F  /* WINVOW - [5:0] */
#define WM8961_WINVOW_SHIFT                          0  /* WINVOW - [5:0] */
#define WM8961_WINVOW_WIDTH                          6  /* WINVOW - [5:0] */

/*
 * W1 (0x01) - Wight Input vowume
 */
#define WM8961_DEVICE_ID_MASK                   0xF000  /* DEVICE_ID - [15:12] */
#define WM8961_DEVICE_ID_SHIFT                      12  /* DEVICE_ID - [15:12] */
#define WM8961_DEVICE_ID_WIDTH                       4  /* DEVICE_ID - [15:12] */
#define WM8961_CHIP_WEV_MASK                    0x0E00  /* CHIP_WEV - [11:9] */
#define WM8961_CHIP_WEV_SHIFT                        9  /* CHIP_WEV - [11:9] */
#define WM8961_CHIP_WEV_WIDTH                        3  /* CHIP_WEV - [11:9] */
#define WM8961_IPVU                             0x0100  /* IPVU */
#define WM8961_IPVU_MASK                        0x0100  /* IPVU */
#define WM8961_IPVU_SHIFT                            8  /* IPVU */
#define WM8961_IPVU_WIDTH                            1  /* IPVU */
#define WM8961_WINMUTE                          0x0080  /* WINMUTE */
#define WM8961_WINMUTE_MASK                     0x0080  /* WINMUTE */
#define WM8961_WINMUTE_SHIFT                         7  /* WINMUTE */
#define WM8961_WINMUTE_WIDTH                         1  /* WINMUTE */
#define WM8961_WIZC                             0x0040  /* WIZC */
#define WM8961_WIZC_MASK                        0x0040  /* WIZC */
#define WM8961_WIZC_SHIFT                            6  /* WIZC */
#define WM8961_WIZC_WIDTH                            1  /* WIZC */
#define WM8961_WINVOW_MASK                      0x003F  /* WINVOW - [5:0] */
#define WM8961_WINVOW_SHIFT                          0  /* WINVOW - [5:0] */
#define WM8961_WINVOW_WIDTH                          6  /* WINVOW - [5:0] */

/*
 * W2 (0x02) - WOUT1 vowume
 */
#define WM8961_OUT1VU                           0x0100  /* OUT1VU */
#define WM8961_OUT1VU_MASK                      0x0100  /* OUT1VU */
#define WM8961_OUT1VU_SHIFT                          8  /* OUT1VU */
#define WM8961_OUT1VU_WIDTH                          1  /* OUT1VU */
#define WM8961_WO1ZC                            0x0080  /* WO1ZC */
#define WM8961_WO1ZC_MASK                       0x0080  /* WO1ZC */
#define WM8961_WO1ZC_SHIFT                           7  /* WO1ZC */
#define WM8961_WO1ZC_WIDTH                           1  /* WO1ZC */
#define WM8961_WOUT1VOW_MASK                    0x007F  /* WOUT1VOW - [6:0] */
#define WM8961_WOUT1VOW_SHIFT                        0  /* WOUT1VOW - [6:0] */
#define WM8961_WOUT1VOW_WIDTH                        7  /* WOUT1VOW - [6:0] */

/*
 * W3 (0x03) - WOUT1 vowume
 */
#define WM8961_OUT1VU                           0x0100  /* OUT1VU */
#define WM8961_OUT1VU_MASK                      0x0100  /* OUT1VU */
#define WM8961_OUT1VU_SHIFT                          8  /* OUT1VU */
#define WM8961_OUT1VU_WIDTH                          1  /* OUT1VU */
#define WM8961_WO1ZC                            0x0080  /* WO1ZC */
#define WM8961_WO1ZC_MASK                       0x0080  /* WO1ZC */
#define WM8961_WO1ZC_SHIFT                           7  /* WO1ZC */
#define WM8961_WO1ZC_WIDTH                           1  /* WO1ZC */
#define WM8961_WOUT1VOW_MASK                    0x007F  /* WOUT1VOW - [6:0] */
#define WM8961_WOUT1VOW_SHIFT                        0  /* WOUT1VOW - [6:0] */
#define WM8961_WOUT1VOW_WIDTH                        7  /* WOUT1VOW - [6:0] */

/*
 * W4 (0x04) - Cwocking1
 */
#define WM8961_ADCDIV_MASK                      0x01C0  /* ADCDIV - [8:6] */
#define WM8961_ADCDIV_SHIFT                          6  /* ADCDIV - [8:6] */
#define WM8961_ADCDIV_WIDTH                          3  /* ADCDIV - [8:6] */
#define WM8961_DACDIV_MASK                      0x0038  /* DACDIV - [5:3] */
#define WM8961_DACDIV_SHIFT                          3  /* DACDIV - [5:3] */
#define WM8961_DACDIV_WIDTH                          3  /* DACDIV - [5:3] */
#define WM8961_MCWKDIV                          0x0004  /* MCWKDIV */
#define WM8961_MCWKDIV_MASK                     0x0004  /* MCWKDIV */
#define WM8961_MCWKDIV_SHIFT                         2  /* MCWKDIV */
#define WM8961_MCWKDIV_WIDTH                         1  /* MCWKDIV */

/*
 * W5 (0x05) - ADC & DAC Contwow 1
 */
#define WM8961_ADCPOW_MASK                      0x0060  /* ADCPOW - [6:5] */
#define WM8961_ADCPOW_SHIFT                          5  /* ADCPOW - [6:5] */
#define WM8961_ADCPOW_WIDTH                          2  /* ADCPOW - [6:5] */
#define WM8961_DACMU                            0x0008  /* DACMU */
#define WM8961_DACMU_MASK                       0x0008  /* DACMU */
#define WM8961_DACMU_SHIFT                           3  /* DACMU */
#define WM8961_DACMU_WIDTH                           1  /* DACMU */
#define WM8961_DEEMPH_MASK                      0x0006  /* DEEMPH - [2:1] */
#define WM8961_DEEMPH_SHIFT                          1  /* DEEMPH - [2:1] */
#define WM8961_DEEMPH_WIDTH                          2  /* DEEMPH - [2:1] */
#define WM8961_ADCHPD                           0x0001  /* ADCHPD */
#define WM8961_ADCHPD_MASK                      0x0001  /* ADCHPD */
#define WM8961_ADCHPD_SHIFT                          0  /* ADCHPD */
#define WM8961_ADCHPD_WIDTH                          1  /* ADCHPD */

/*
 * W6 (0x06) - ADC & DAC Contwow 2
 */
#define WM8961_ADC_HPF_CUT_MASK                 0x0180  /* ADC_HPF_CUT - [8:7] */
#define WM8961_ADC_HPF_CUT_SHIFT                     7  /* ADC_HPF_CUT - [8:7] */
#define WM8961_ADC_HPF_CUT_WIDTH                     2  /* ADC_HPF_CUT - [8:7] */
#define WM8961_DACPOW_MASK                      0x0060  /* DACPOW - [6:5] */
#define WM8961_DACPOW_SHIFT                          5  /* DACPOW - [6:5] */
#define WM8961_DACPOW_WIDTH                          2  /* DACPOW - [6:5] */
#define WM8961_DACSMM                           0x0008  /* DACSMM */
#define WM8961_DACSMM_MASK                      0x0008  /* DACSMM */
#define WM8961_DACSMM_SHIFT                          3  /* DACSMM */
#define WM8961_DACSMM_WIDTH                          1  /* DACSMM */
#define WM8961_DACMW                            0x0004  /* DACMW */
#define WM8961_DACMW_MASK                       0x0004  /* DACMW */
#define WM8961_DACMW_SHIFT                           2  /* DACMW */
#define WM8961_DACMW_WIDTH                           1  /* DACMW */
#define WM8961_DACSWOPE                         0x0002  /* DACSWOPE */
#define WM8961_DACSWOPE_MASK                    0x0002  /* DACSWOPE */
#define WM8961_DACSWOPE_SHIFT                        1  /* DACSWOPE */
#define WM8961_DACSWOPE_WIDTH                        1  /* DACSWOPE */
#define WM8961_DAC_OSW128                       0x0001  /* DAC_OSW128 */
#define WM8961_DAC_OSW128_MASK                  0x0001  /* DAC_OSW128 */
#define WM8961_DAC_OSW128_SHIFT                      0  /* DAC_OSW128 */
#define WM8961_DAC_OSW128_WIDTH                      1  /* DAC_OSW128 */

/*
 * W7 (0x07) - Audio Intewface 0
 */
#define WM8961_AWWSWAP                          0x0100  /* AWWSWAP */
#define WM8961_AWWSWAP_MASK                     0x0100  /* AWWSWAP */
#define WM8961_AWWSWAP_SHIFT                         8  /* AWWSWAP */
#define WM8961_AWWSWAP_WIDTH                         1  /* AWWSWAP */
#define WM8961_BCWKINV                          0x0080  /* BCWKINV */
#define WM8961_BCWKINV_MASK                     0x0080  /* BCWKINV */
#define WM8961_BCWKINV_SHIFT                         7  /* BCWKINV */
#define WM8961_BCWKINV_WIDTH                         1  /* BCWKINV */
#define WM8961_MS                               0x0040  /* MS */
#define WM8961_MS_MASK                          0x0040  /* MS */
#define WM8961_MS_SHIFT                              6  /* MS */
#define WM8961_MS_WIDTH                              1  /* MS */
#define WM8961_DWWSWAP                          0x0020  /* DWWSWAP */
#define WM8961_DWWSWAP_MASK                     0x0020  /* DWWSWAP */
#define WM8961_DWWSWAP_SHIFT                         5  /* DWWSWAP */
#define WM8961_DWWSWAP_WIDTH                         1  /* DWWSWAP */
#define WM8961_WWP                              0x0010  /* WWP */
#define WM8961_WWP_MASK                         0x0010  /* WWP */
#define WM8961_WWP_SHIFT                             4  /* WWP */
#define WM8961_WWP_WIDTH                             1  /* WWP */
#define WM8961_WW_MASK                          0x000C  /* WW - [3:2] */
#define WM8961_WW_SHIFT                              2  /* WW - [3:2] */
#define WM8961_WW_WIDTH                              2  /* WW - [3:2] */
#define WM8961_FOWMAT_MASK                      0x0003  /* FOWMAT - [1:0] */
#define WM8961_FOWMAT_SHIFT                          0  /* FOWMAT - [1:0] */
#define WM8961_FOWMAT_WIDTH                          2  /* FOWMAT - [1:0] */

/*
 * W8 (0x08) - Cwocking2
 */
#define WM8961_DCWKDIV_MASK                     0x01C0  /* DCWKDIV - [8:6] */
#define WM8961_DCWKDIV_SHIFT                         6  /* DCWKDIV - [8:6] */
#define WM8961_DCWKDIV_WIDTH                         3  /* DCWKDIV - [8:6] */
#define WM8961_CWK_SYS_ENA                      0x0020  /* CWK_SYS_ENA */
#define WM8961_CWK_SYS_ENA_MASK                 0x0020  /* CWK_SYS_ENA */
#define WM8961_CWK_SYS_ENA_SHIFT                     5  /* CWK_SYS_ENA */
#define WM8961_CWK_SYS_ENA_WIDTH                     1  /* CWK_SYS_ENA */
#define WM8961_CWK_DSP_ENA                      0x0010  /* CWK_DSP_ENA */
#define WM8961_CWK_DSP_ENA_MASK                 0x0010  /* CWK_DSP_ENA */
#define WM8961_CWK_DSP_ENA_SHIFT                     4  /* CWK_DSP_ENA */
#define WM8961_CWK_DSP_ENA_WIDTH                     1  /* CWK_DSP_ENA */
#define WM8961_BCWKDIV_MASK                     0x000F  /* BCWKDIV - [3:0] */
#define WM8961_BCWKDIV_SHIFT                         0  /* BCWKDIV - [3:0] */
#define WM8961_BCWKDIV_WIDTH                         4  /* BCWKDIV - [3:0] */

/*
 * W9 (0x09) - Audio Intewface 1
 */
#define WM8961_DACCOMP_MASK                     0x0018  /* DACCOMP - [4:3] */
#define WM8961_DACCOMP_SHIFT                         3  /* DACCOMP - [4:3] */
#define WM8961_DACCOMP_WIDTH                         2  /* DACCOMP - [4:3] */
#define WM8961_ADCCOMP_MASK                     0x0006  /* ADCCOMP - [2:1] */
#define WM8961_ADCCOMP_SHIFT                         1  /* ADCCOMP - [2:1] */
#define WM8961_ADCCOMP_WIDTH                         2  /* ADCCOMP - [2:1] */
#define WM8961_WOOPBACK                         0x0001  /* WOOPBACK */
#define WM8961_WOOPBACK_MASK                    0x0001  /* WOOPBACK */
#define WM8961_WOOPBACK_SHIFT                        0  /* WOOPBACK */
#define WM8961_WOOPBACK_WIDTH                        1  /* WOOPBACK */

/*
 * W10 (0x0A) - Weft DAC vowume
 */
#define WM8961_DACVU                            0x0100  /* DACVU */
#define WM8961_DACVU_MASK                       0x0100  /* DACVU */
#define WM8961_DACVU_SHIFT                           8  /* DACVU */
#define WM8961_DACVU_WIDTH                           1  /* DACVU */
#define WM8961_WDACVOW_MASK                     0x00FF  /* WDACVOW - [7:0] */
#define WM8961_WDACVOW_SHIFT                         0  /* WDACVOW - [7:0] */
#define WM8961_WDACVOW_WIDTH                         8  /* WDACVOW - [7:0] */

/*
 * W11 (0x0B) - Wight DAC vowume
 */
#define WM8961_DACVU                            0x0100  /* DACVU */
#define WM8961_DACVU_MASK                       0x0100  /* DACVU */
#define WM8961_DACVU_SHIFT                           8  /* DACVU */
#define WM8961_DACVU_WIDTH                           1  /* DACVU */
#define WM8961_WDACVOW_MASK                     0x00FF  /* WDACVOW - [7:0] */
#define WM8961_WDACVOW_SHIFT                         0  /* WDACVOW - [7:0] */
#define WM8961_WDACVOW_WIDTH                         8  /* WDACVOW - [7:0] */

/*
 * W14 (0x0E) - Audio Intewface 2
 */
#define WM8961_WWCWK_WATE_MASK                  0x01FF  /* WWCWK_WATE - [8:0] */
#define WM8961_WWCWK_WATE_SHIFT                      0  /* WWCWK_WATE - [8:0] */
#define WM8961_WWCWK_WATE_WIDTH                      9  /* WWCWK_WATE - [8:0] */

/*
 * W15 (0x0F) - Softwawe Weset
 */
#define WM8961_SW_WST_DEV_ID1_MASK              0xFFFF  /* SW_WST_DEV_ID1 - [15:0] */
#define WM8961_SW_WST_DEV_ID1_SHIFT                  0  /* SW_WST_DEV_ID1 - [15:0] */
#define WM8961_SW_WST_DEV_ID1_WIDTH                 16  /* SW_WST_DEV_ID1 - [15:0] */

/*
 * W17 (0x11) - AWC1
 */
#define WM8961_AWCSEW_MASK                      0x0180  /* AWCSEW - [8:7] */
#define WM8961_AWCSEW_SHIFT                          7  /* AWCSEW - [8:7] */
#define WM8961_AWCSEW_WIDTH                          2  /* AWCSEW - [8:7] */
#define WM8961_MAXGAIN_MASK                     0x0070  /* MAXGAIN - [6:4] */
#define WM8961_MAXGAIN_SHIFT                         4  /* MAXGAIN - [6:4] */
#define WM8961_MAXGAIN_WIDTH                         3  /* MAXGAIN - [6:4] */
#define WM8961_AWCW_MASK                        0x000F  /* AWCW - [3:0] */
#define WM8961_AWCW_SHIFT                            0  /* AWCW - [3:0] */
#define WM8961_AWCW_WIDTH                            4  /* AWCW - [3:0] */

/*
 * W18 (0x12) - AWC2
 */
#define WM8961_AWCZC                            0x0080  /* AWCZC */
#define WM8961_AWCZC_MASK                       0x0080  /* AWCZC */
#define WM8961_AWCZC_SHIFT                           7  /* AWCZC */
#define WM8961_AWCZC_WIDTH                           1  /* AWCZC */
#define WM8961_MINGAIN_MASK                     0x0070  /* MINGAIN - [6:4] */
#define WM8961_MINGAIN_SHIFT                         4  /* MINGAIN - [6:4] */
#define WM8961_MINGAIN_WIDTH                         3  /* MINGAIN - [6:4] */
#define WM8961_HWD_MASK                         0x000F  /* HWD - [3:0] */
#define WM8961_HWD_SHIFT                             0  /* HWD - [3:0] */
#define WM8961_HWD_WIDTH                             4  /* HWD - [3:0] */

/*
 * W19 (0x13) - AWC3
 */
#define WM8961_AWCMODE                          0x0100  /* AWCMODE */
#define WM8961_AWCMODE_MASK                     0x0100  /* AWCMODE */
#define WM8961_AWCMODE_SHIFT                         8  /* AWCMODE */
#define WM8961_AWCMODE_WIDTH                         1  /* AWCMODE */
#define WM8961_DCY_MASK                         0x00F0  /* DCY - [7:4] */
#define WM8961_DCY_SHIFT                             4  /* DCY - [7:4] */
#define WM8961_DCY_WIDTH                             4  /* DCY - [7:4] */
#define WM8961_ATK_MASK                         0x000F  /* ATK - [3:0] */
#define WM8961_ATK_SHIFT                             0  /* ATK - [3:0] */
#define WM8961_ATK_WIDTH                             4  /* ATK - [3:0] */

/*
 * W20 (0x14) - Noise Gate
 */
#define WM8961_NGTH_MASK                        0x00F8  /* NGTH - [7:3] */
#define WM8961_NGTH_SHIFT                            3  /* NGTH - [7:3] */
#define WM8961_NGTH_WIDTH                            5  /* NGTH - [7:3] */
#define WM8961_NGG                              0x0002  /* NGG */
#define WM8961_NGG_MASK                         0x0002  /* NGG */
#define WM8961_NGG_SHIFT                             1  /* NGG */
#define WM8961_NGG_WIDTH                             1  /* NGG */
#define WM8961_NGAT                             0x0001  /* NGAT */
#define WM8961_NGAT_MASK                        0x0001  /* NGAT */
#define WM8961_NGAT_SHIFT                            0  /* NGAT */
#define WM8961_NGAT_WIDTH                            1  /* NGAT */

/*
 * W21 (0x15) - Weft ADC vowume
 */
#define WM8961_ADCVU                            0x0100  /* ADCVU */
#define WM8961_ADCVU_MASK                       0x0100  /* ADCVU */
#define WM8961_ADCVU_SHIFT                           8  /* ADCVU */
#define WM8961_ADCVU_WIDTH                           1  /* ADCVU */
#define WM8961_WADCVOW_MASK                     0x00FF  /* WADCVOW - [7:0] */
#define WM8961_WADCVOW_SHIFT                         0  /* WADCVOW - [7:0] */
#define WM8961_WADCVOW_WIDTH                         8  /* WADCVOW - [7:0] */

/*
 * W22 (0x16) - Wight ADC vowume
 */
#define WM8961_ADCVU                            0x0100  /* ADCVU */
#define WM8961_ADCVU_MASK                       0x0100  /* ADCVU */
#define WM8961_ADCVU_SHIFT                           8  /* ADCVU */
#define WM8961_ADCVU_WIDTH                           1  /* ADCVU */
#define WM8961_WADCVOW_MASK                     0x00FF  /* WADCVOW - [7:0] */
#define WM8961_WADCVOW_SHIFT                         0  /* WADCVOW - [7:0] */
#define WM8961_WADCVOW_WIDTH                         8  /* WADCVOW - [7:0] */

/*
 * W23 (0x17) - Additionaw contwow(1)
 */
#define WM8961_TSDEN                            0x0100  /* TSDEN */
#define WM8961_TSDEN_MASK                       0x0100  /* TSDEN */
#define WM8961_TSDEN_SHIFT                           8  /* TSDEN */
#define WM8961_TSDEN_WIDTH                           1  /* TSDEN */
#define WM8961_DMONOMIX                         0x0010  /* DMONOMIX */
#define WM8961_DMONOMIX_MASK                    0x0010  /* DMONOMIX */
#define WM8961_DMONOMIX_SHIFT                        4  /* DMONOMIX */
#define WM8961_DMONOMIX_WIDTH                        1  /* DMONOMIX */
#define WM8961_TOEN                             0x0001  /* TOEN */
#define WM8961_TOEN_MASK                        0x0001  /* TOEN */
#define WM8961_TOEN_SHIFT                            0  /* TOEN */
#define WM8961_TOEN_WIDTH                            1  /* TOEN */

/*
 * W24 (0x18) - Additionaw contwow(2)
 */
#define WM8961_TWIS                             0x0008  /* TWIS */
#define WM8961_TWIS_MASK                        0x0008  /* TWIS */
#define WM8961_TWIS_SHIFT                            3  /* TWIS */
#define WM8961_TWIS_WIDTH                            1  /* TWIS */

/*
 * W25 (0x19) - Pww Mgmt (1)
 */
#define WM8961_VMIDSEW_MASK                     0x0180  /* VMIDSEW - [8:7] */
#define WM8961_VMIDSEW_SHIFT                         7  /* VMIDSEW - [8:7] */
#define WM8961_VMIDSEW_WIDTH                         2  /* VMIDSEW - [8:7] */
#define WM8961_VWEF                             0x0040  /* VWEF */
#define WM8961_VWEF_MASK                        0x0040  /* VWEF */
#define WM8961_VWEF_SHIFT                            6  /* VWEF */
#define WM8961_VWEF_WIDTH                            1  /* VWEF */
#define WM8961_AINW                             0x0020  /* AINW */
#define WM8961_AINW_MASK                        0x0020  /* AINW */
#define WM8961_AINW_SHIFT                            5  /* AINW */
#define WM8961_AINW_WIDTH                            1  /* AINW */
#define WM8961_AINW                             0x0010  /* AINW */
#define WM8961_AINW_MASK                        0x0010  /* AINW */
#define WM8961_AINW_SHIFT                            4  /* AINW */
#define WM8961_AINW_WIDTH                            1  /* AINW */
#define WM8961_ADCW                             0x0008  /* ADCW */
#define WM8961_ADCW_MASK                        0x0008  /* ADCW */
#define WM8961_ADCW_SHIFT                            3  /* ADCW */
#define WM8961_ADCW_WIDTH                            1  /* ADCW */
#define WM8961_ADCW                             0x0004  /* ADCW */
#define WM8961_ADCW_MASK                        0x0004  /* ADCW */
#define WM8961_ADCW_SHIFT                            2  /* ADCW */
#define WM8961_ADCW_WIDTH                            1  /* ADCW */
#define WM8961_MICB                             0x0002  /* MICB */
#define WM8961_MICB_MASK                        0x0002  /* MICB */
#define WM8961_MICB_SHIFT                            1  /* MICB */
#define WM8961_MICB_WIDTH                            1  /* MICB */

/*
 * W26 (0x1A) - Pww Mgmt (2)
 */
#define WM8961_DACW                             0x0100  /* DACW */
#define WM8961_DACW_MASK                        0x0100  /* DACW */
#define WM8961_DACW_SHIFT                            8  /* DACW */
#define WM8961_DACW_WIDTH                            1  /* DACW */
#define WM8961_DACW                             0x0080  /* DACW */
#define WM8961_DACW_MASK                        0x0080  /* DACW */
#define WM8961_DACW_SHIFT                            7  /* DACW */
#define WM8961_DACW_WIDTH                            1  /* DACW */
#define WM8961_WOUT1_PGA                        0x0040  /* WOUT1_PGA */
#define WM8961_WOUT1_PGA_MASK                   0x0040  /* WOUT1_PGA */
#define WM8961_WOUT1_PGA_SHIFT                       6  /* WOUT1_PGA */
#define WM8961_WOUT1_PGA_WIDTH                       1  /* WOUT1_PGA */
#define WM8961_WOUT1_PGA                        0x0020  /* WOUT1_PGA */
#define WM8961_WOUT1_PGA_MASK                   0x0020  /* WOUT1_PGA */
#define WM8961_WOUT1_PGA_SHIFT                       5  /* WOUT1_PGA */
#define WM8961_WOUT1_PGA_WIDTH                       1  /* WOUT1_PGA */
#define WM8961_SPKW_PGA                         0x0010  /* SPKW_PGA */
#define WM8961_SPKW_PGA_MASK                    0x0010  /* SPKW_PGA */
#define WM8961_SPKW_PGA_SHIFT                        4  /* SPKW_PGA */
#define WM8961_SPKW_PGA_WIDTH                        1  /* SPKW_PGA */
#define WM8961_SPKW_PGA                         0x0008  /* SPKW_PGA */
#define WM8961_SPKW_PGA_MASK                    0x0008  /* SPKW_PGA */
#define WM8961_SPKW_PGA_SHIFT                        3  /* SPKW_PGA */
#define WM8961_SPKW_PGA_WIDTH                        1  /* SPKW_PGA */

/*
 * W27 (0x1B) - Additionaw Contwow (3)
 */
#define WM8961_SAMPWE_WATE_MASK                 0x0007  /* SAMPWE_WATE - [2:0] */
#define WM8961_SAMPWE_WATE_SHIFT                     0  /* SAMPWE_WATE - [2:0] */
#define WM8961_SAMPWE_WATE_WIDTH                     3  /* SAMPWE_WATE - [2:0] */

/*
 * W28 (0x1C) - Anti-pop
 */
#define WM8961_BUFDCOPEN                        0x0010  /* BUFDCOPEN */
#define WM8961_BUFDCOPEN_MASK                   0x0010  /* BUFDCOPEN */
#define WM8961_BUFDCOPEN_SHIFT                       4  /* BUFDCOPEN */
#define WM8961_BUFDCOPEN_WIDTH                       1  /* BUFDCOPEN */
#define WM8961_BUFIOEN                          0x0008  /* BUFIOEN */
#define WM8961_BUFIOEN_MASK                     0x0008  /* BUFIOEN */
#define WM8961_BUFIOEN_SHIFT                         3  /* BUFIOEN */
#define WM8961_BUFIOEN_WIDTH                         1  /* BUFIOEN */
#define WM8961_SOFT_ST                          0x0004  /* SOFT_ST */
#define WM8961_SOFT_ST_MASK                     0x0004  /* SOFT_ST */
#define WM8961_SOFT_ST_SHIFT                         2  /* SOFT_ST */
#define WM8961_SOFT_ST_WIDTH                         1  /* SOFT_ST */

/*
 * W30 (0x1E) - Cwocking 3
 */
#define WM8961_CWK_TO_DIV_MASK                  0x0180  /* CWK_TO_DIV - [8:7] */
#define WM8961_CWK_TO_DIV_SHIFT                      7  /* CWK_TO_DIV - [8:7] */
#define WM8961_CWK_TO_DIV_WIDTH                      2  /* CWK_TO_DIV - [8:7] */
#define WM8961_CWK_256K_DIV_MASK                0x007E  /* CWK_256K_DIV - [6:1] */
#define WM8961_CWK_256K_DIV_SHIFT                    1  /* CWK_256K_DIV - [6:1] */
#define WM8961_CWK_256K_DIV_WIDTH                    6  /* CWK_256K_DIV - [6:1] */
#define WM8961_MANUAW_MODE                      0x0001  /* MANUAW_MODE */
#define WM8961_MANUAW_MODE_MASK                 0x0001  /* MANUAW_MODE */
#define WM8961_MANUAW_MODE_SHIFT                     0  /* MANUAW_MODE */
#define WM8961_MANUAW_MODE_WIDTH                     1  /* MANUAW_MODE */

/*
 * W32 (0x20) - ADCW signaw path
 */
#define WM8961_WMICBOOST_MASK                   0x0030  /* WMICBOOST - [5:4] */
#define WM8961_WMICBOOST_SHIFT                       4  /* WMICBOOST - [5:4] */
#define WM8961_WMICBOOST_WIDTH                       2  /* WMICBOOST - [5:4] */

/*
 * W33 (0x21) - ADCW signaw path
 */
#define WM8961_WMICBOOST_MASK                   0x0030  /* WMICBOOST - [5:4] */
#define WM8961_WMICBOOST_SHIFT                       4  /* WMICBOOST - [5:4] */
#define WM8961_WMICBOOST_WIDTH                       2  /* WMICBOOST - [5:4] */

/*
 * W40 (0x28) - WOUT2 vowume
 */
#define WM8961_SPKVU                            0x0100  /* SPKVU */
#define WM8961_SPKVU_MASK                       0x0100  /* SPKVU */
#define WM8961_SPKVU_SHIFT                           8  /* SPKVU */
#define WM8961_SPKVU_WIDTH                           1  /* SPKVU */
#define WM8961_SPKWZC                           0x0080  /* SPKWZC */
#define WM8961_SPKWZC_MASK                      0x0080  /* SPKWZC */
#define WM8961_SPKWZC_SHIFT                          7  /* SPKWZC */
#define WM8961_SPKWZC_WIDTH                          1  /* SPKWZC */
#define WM8961_SPKWVOW_MASK                     0x007F  /* SPKWVOW - [6:0] */
#define WM8961_SPKWVOW_SHIFT                         0  /* SPKWVOW - [6:0] */
#define WM8961_SPKWVOW_WIDTH                         7  /* SPKWVOW - [6:0] */

/*
 * W41 (0x29) - WOUT2 vowume
 */
#define WM8961_SPKVU                            0x0100  /* SPKVU */
#define WM8961_SPKVU_MASK                       0x0100  /* SPKVU */
#define WM8961_SPKVU_SHIFT                           8  /* SPKVU */
#define WM8961_SPKVU_WIDTH                           1  /* SPKVU */
#define WM8961_SPKWZC                           0x0080  /* SPKWZC */
#define WM8961_SPKWZC_MASK                      0x0080  /* SPKWZC */
#define WM8961_SPKWZC_SHIFT                          7  /* SPKWZC */
#define WM8961_SPKWZC_WIDTH                          1  /* SPKWZC */
#define WM8961_SPKWVOW_MASK                     0x007F  /* SPKWVOW - [6:0] */
#define WM8961_SPKWVOW_SHIFT                         0  /* SPKWVOW - [6:0] */
#define WM8961_SPKWVOW_WIDTH                         7  /* SPKWVOW - [6:0] */

/*
 * W47 (0x2F) - Pww Mgmt (3)
 */
#define WM8961_TEMP_SHUT                        0x0002  /* TEMP_SHUT */
#define WM8961_TEMP_SHUT_MASK                   0x0002  /* TEMP_SHUT */
#define WM8961_TEMP_SHUT_SHIFT                       1  /* TEMP_SHUT */
#define WM8961_TEMP_SHUT_WIDTH                       1  /* TEMP_SHUT */
#define WM8961_TEMP_WAWN                        0x0001  /* TEMP_WAWN */
#define WM8961_TEMP_WAWN_MASK                   0x0001  /* TEMP_WAWN */
#define WM8961_TEMP_WAWN_SHIFT                       0  /* TEMP_WAWN */
#define WM8961_TEMP_WAWN_WIDTH                       1  /* TEMP_WAWN */

/*
 * W48 (0x30) - Additionaw Contwow (4)
 */
#define WM8961_TSENSEN                          0x0002  /* TSENSEN */
#define WM8961_TSENSEN_MASK                     0x0002  /* TSENSEN */
#define WM8961_TSENSEN_SHIFT                         1  /* TSENSEN */
#define WM8961_TSENSEN_WIDTH                         1  /* TSENSEN */
#define WM8961_MBSEW                            0x0001  /* MBSEW */
#define WM8961_MBSEW_MASK                       0x0001  /* MBSEW */
#define WM8961_MBSEW_SHIFT                           0  /* MBSEW */
#define WM8961_MBSEW_WIDTH                           1  /* MBSEW */

/*
 * W49 (0x31) - Cwass D Contwow 1
 */
#define WM8961_SPKW_ENA                         0x0080  /* SPKW_ENA */
#define WM8961_SPKW_ENA_MASK                    0x0080  /* SPKW_ENA */
#define WM8961_SPKW_ENA_SHIFT                        7  /* SPKW_ENA */
#define WM8961_SPKW_ENA_WIDTH                        1  /* SPKW_ENA */
#define WM8961_SPKW_ENA                         0x0040  /* SPKW_ENA */
#define WM8961_SPKW_ENA_MASK                    0x0040  /* SPKW_ENA */
#define WM8961_SPKW_ENA_SHIFT                        6  /* SPKW_ENA */
#define WM8961_SPKW_ENA_WIDTH                        1  /* SPKW_ENA */

/*
 * W51 (0x33) - Cwass D Contwow 2
 */
#define WM8961_CWASSD_ACGAIN_MASK               0x0007  /* CWASSD_ACGAIN - [2:0] */
#define WM8961_CWASSD_ACGAIN_SHIFT                   0  /* CWASSD_ACGAIN - [2:0] */
#define WM8961_CWASSD_ACGAIN_WIDTH                   3  /* CWASSD_ACGAIN - [2:0] */

/*
 * W56 (0x38) - Cwocking 4
 */
#define WM8961_CWK_DCS_DIV_MASK                 0x01E0  /* CWK_DCS_DIV - [8:5] */
#define WM8961_CWK_DCS_DIV_SHIFT                     5  /* CWK_DCS_DIV - [8:5] */
#define WM8961_CWK_DCS_DIV_WIDTH                     4  /* CWK_DCS_DIV - [8:5] */
#define WM8961_CWK_SYS_WATE_MASK                0x001E  /* CWK_SYS_WATE - [4:1] */
#define WM8961_CWK_SYS_WATE_SHIFT                    1  /* CWK_SYS_WATE - [4:1] */
#define WM8961_CWK_SYS_WATE_WIDTH                    4  /* CWK_SYS_WATE - [4:1] */

/*
 * W57 (0x39) - DSP Sidetone 0
 */
#define WM8961_ADCW_DAC_SVOW_MASK               0x00F0  /* ADCW_DAC_SVOW - [7:4] */
#define WM8961_ADCW_DAC_SVOW_SHIFT                   4  /* ADCW_DAC_SVOW - [7:4] */
#define WM8961_ADCW_DAC_SVOW_WIDTH                   4  /* ADCW_DAC_SVOW - [7:4] */
#define WM8961_ADC_TO_DACW_MASK                 0x000C  /* ADC_TO_DACW - [3:2] */
#define WM8961_ADC_TO_DACW_SHIFT                     2  /* ADC_TO_DACW - [3:2] */
#define WM8961_ADC_TO_DACW_WIDTH                     2  /* ADC_TO_DACW - [3:2] */

/*
 * W58 (0x3A) - DSP Sidetone 1
 */
#define WM8961_ADCW_DAC_SVOW_MASK               0x00F0  /* ADCW_DAC_SVOW - [7:4] */
#define WM8961_ADCW_DAC_SVOW_SHIFT                   4  /* ADCW_DAC_SVOW - [7:4] */
#define WM8961_ADCW_DAC_SVOW_WIDTH                   4  /* ADCW_DAC_SVOW - [7:4] */
#define WM8961_ADC_TO_DACW_MASK                 0x000C  /* ADC_TO_DACW - [3:2] */
#define WM8961_ADC_TO_DACW_SHIFT                     2  /* ADC_TO_DACW - [3:2] */
#define WM8961_ADC_TO_DACW_WIDTH                     2  /* ADC_TO_DACW - [3:2] */

/*
 * W60 (0x3C) - DC Sewvo 0
 */
#define WM8961_DCS_ENA_CHAN_INW                 0x0080  /* DCS_ENA_CHAN_INW */
#define WM8961_DCS_ENA_CHAN_INW_MASK            0x0080  /* DCS_ENA_CHAN_INW */
#define WM8961_DCS_ENA_CHAN_INW_SHIFT                7  /* DCS_ENA_CHAN_INW */
#define WM8961_DCS_ENA_CHAN_INW_WIDTH                1  /* DCS_ENA_CHAN_INW */
#define WM8961_DCS_TWIG_STAWTUP_INW             0x0040  /* DCS_TWIG_STAWTUP_INW */
#define WM8961_DCS_TWIG_STAWTUP_INW_MASK        0x0040  /* DCS_TWIG_STAWTUP_INW */
#define WM8961_DCS_TWIG_STAWTUP_INW_SHIFT            6  /* DCS_TWIG_STAWTUP_INW */
#define WM8961_DCS_TWIG_STAWTUP_INW_WIDTH            1  /* DCS_TWIG_STAWTUP_INW */
#define WM8961_DCS_TWIG_SEWIES_INW              0x0010  /* DCS_TWIG_SEWIES_INW */
#define WM8961_DCS_TWIG_SEWIES_INW_MASK         0x0010  /* DCS_TWIG_SEWIES_INW */
#define WM8961_DCS_TWIG_SEWIES_INW_SHIFT             4  /* DCS_TWIG_SEWIES_INW */
#define WM8961_DCS_TWIG_SEWIES_INW_WIDTH             1  /* DCS_TWIG_SEWIES_INW */
#define WM8961_DCS_ENA_CHAN_INW                 0x0008  /* DCS_ENA_CHAN_INW */
#define WM8961_DCS_ENA_CHAN_INW_MASK            0x0008  /* DCS_ENA_CHAN_INW */
#define WM8961_DCS_ENA_CHAN_INW_SHIFT                3  /* DCS_ENA_CHAN_INW */
#define WM8961_DCS_ENA_CHAN_INW_WIDTH                1  /* DCS_ENA_CHAN_INW */
#define WM8961_DCS_TWIG_STAWTUP_INW             0x0004  /* DCS_TWIG_STAWTUP_INW */
#define WM8961_DCS_TWIG_STAWTUP_INW_MASK        0x0004  /* DCS_TWIG_STAWTUP_INW */
#define WM8961_DCS_TWIG_STAWTUP_INW_SHIFT            2  /* DCS_TWIG_STAWTUP_INW */
#define WM8961_DCS_TWIG_STAWTUP_INW_WIDTH            1  /* DCS_TWIG_STAWTUP_INW */
#define WM8961_DCS_TWIG_SEWIES_INW              0x0001  /* DCS_TWIG_SEWIES_INW */
#define WM8961_DCS_TWIG_SEWIES_INW_MASK         0x0001  /* DCS_TWIG_SEWIES_INW */
#define WM8961_DCS_TWIG_SEWIES_INW_SHIFT             0  /* DCS_TWIG_SEWIES_INW */
#define WM8961_DCS_TWIG_SEWIES_INW_WIDTH             1  /* DCS_TWIG_SEWIES_INW */

/*
 * W61 (0x3D) - DC Sewvo 1
 */
#define WM8961_DCS_ENA_CHAN_HPW                 0x0080  /* DCS_ENA_CHAN_HPW */
#define WM8961_DCS_ENA_CHAN_HPW_MASK            0x0080  /* DCS_ENA_CHAN_HPW */
#define WM8961_DCS_ENA_CHAN_HPW_SHIFT                7  /* DCS_ENA_CHAN_HPW */
#define WM8961_DCS_ENA_CHAN_HPW_WIDTH                1  /* DCS_ENA_CHAN_HPW */
#define WM8961_DCS_TWIG_STAWTUP_HPW             0x0040  /* DCS_TWIG_STAWTUP_HPW */
#define WM8961_DCS_TWIG_STAWTUP_HPW_MASK        0x0040  /* DCS_TWIG_STAWTUP_HPW */
#define WM8961_DCS_TWIG_STAWTUP_HPW_SHIFT            6  /* DCS_TWIG_STAWTUP_HPW */
#define WM8961_DCS_TWIG_STAWTUP_HPW_WIDTH            1  /* DCS_TWIG_STAWTUP_HPW */
#define WM8961_DCS_TWIG_SEWIES_HPW              0x0010  /* DCS_TWIG_SEWIES_HPW */
#define WM8961_DCS_TWIG_SEWIES_HPW_MASK         0x0010  /* DCS_TWIG_SEWIES_HPW */
#define WM8961_DCS_TWIG_SEWIES_HPW_SHIFT             4  /* DCS_TWIG_SEWIES_HPW */
#define WM8961_DCS_TWIG_SEWIES_HPW_WIDTH             1  /* DCS_TWIG_SEWIES_HPW */
#define WM8961_DCS_ENA_CHAN_HPW                 0x0008  /* DCS_ENA_CHAN_HPW */
#define WM8961_DCS_ENA_CHAN_HPW_MASK            0x0008  /* DCS_ENA_CHAN_HPW */
#define WM8961_DCS_ENA_CHAN_HPW_SHIFT                3  /* DCS_ENA_CHAN_HPW */
#define WM8961_DCS_ENA_CHAN_HPW_WIDTH                1  /* DCS_ENA_CHAN_HPW */
#define WM8961_DCS_TWIG_STAWTUP_HPW             0x0004  /* DCS_TWIG_STAWTUP_HPW */
#define WM8961_DCS_TWIG_STAWTUP_HPW_MASK        0x0004  /* DCS_TWIG_STAWTUP_HPW */
#define WM8961_DCS_TWIG_STAWTUP_HPW_SHIFT            2  /* DCS_TWIG_STAWTUP_HPW */
#define WM8961_DCS_TWIG_STAWTUP_HPW_WIDTH            1  /* DCS_TWIG_STAWTUP_HPW */
#define WM8961_DCS_TWIG_SEWIES_HPW              0x0001  /* DCS_TWIG_SEWIES_HPW */
#define WM8961_DCS_TWIG_SEWIES_HPW_MASK         0x0001  /* DCS_TWIG_SEWIES_HPW */
#define WM8961_DCS_TWIG_SEWIES_HPW_SHIFT             0  /* DCS_TWIG_SEWIES_HPW */
#define WM8961_DCS_TWIG_SEWIES_HPW_WIDTH             1  /* DCS_TWIG_SEWIES_HPW */

/*
 * W63 (0x3F) - DC Sewvo 3
 */
#define WM8961_DCS_FIWT_BW_SEWIES_MASK          0x0030  /* DCS_FIWT_BW_SEWIES - [5:4] */
#define WM8961_DCS_FIWT_BW_SEWIES_SHIFT              4  /* DCS_FIWT_BW_SEWIES - [5:4] */
#define WM8961_DCS_FIWT_BW_SEWIES_WIDTH              2  /* DCS_FIWT_BW_SEWIES - [5:4] */

/*
 * W65 (0x41) - DC Sewvo 5
 */
#define WM8961_DCS_SEWIES_NO_HP_MASK            0x007F  /* DCS_SEWIES_NO_HP - [6:0] */
#define WM8961_DCS_SEWIES_NO_HP_SHIFT                0  /* DCS_SEWIES_NO_HP - [6:0] */
#define WM8961_DCS_SEWIES_NO_HP_WIDTH                7  /* DCS_SEWIES_NO_HP - [6:0] */

/*
 * W68 (0x44) - Anawogue PGA Bias
 */
#define WM8961_HP_PGAS_BIAS_MASK                0x0007  /* HP_PGAS_BIAS - [2:0] */
#define WM8961_HP_PGAS_BIAS_SHIFT                    0  /* HP_PGAS_BIAS - [2:0] */
#define WM8961_HP_PGAS_BIAS_WIDTH                    3  /* HP_PGAS_BIAS - [2:0] */

/*
 * W69 (0x45) - Anawogue HP 0
 */
#define WM8961_HPW_WMV_SHOWT                    0x0080  /* HPW_WMV_SHOWT */
#define WM8961_HPW_WMV_SHOWT_MASK               0x0080  /* HPW_WMV_SHOWT */
#define WM8961_HPW_WMV_SHOWT_SHIFT                   7  /* HPW_WMV_SHOWT */
#define WM8961_HPW_WMV_SHOWT_WIDTH                   1  /* HPW_WMV_SHOWT */
#define WM8961_HPW_ENA_OUTP                     0x0040  /* HPW_ENA_OUTP */
#define WM8961_HPW_ENA_OUTP_MASK                0x0040  /* HPW_ENA_OUTP */
#define WM8961_HPW_ENA_OUTP_SHIFT                    6  /* HPW_ENA_OUTP */
#define WM8961_HPW_ENA_OUTP_WIDTH                    1  /* HPW_ENA_OUTP */
#define WM8961_HPW_ENA_DWY                      0x0020  /* HPW_ENA_DWY */
#define WM8961_HPW_ENA_DWY_MASK                 0x0020  /* HPW_ENA_DWY */
#define WM8961_HPW_ENA_DWY_SHIFT                     5  /* HPW_ENA_DWY */
#define WM8961_HPW_ENA_DWY_WIDTH                     1  /* HPW_ENA_DWY */
#define WM8961_HPW_ENA                          0x0010  /* HPW_ENA */
#define WM8961_HPW_ENA_MASK                     0x0010  /* HPW_ENA */
#define WM8961_HPW_ENA_SHIFT                         4  /* HPW_ENA */
#define WM8961_HPW_ENA_WIDTH                         1  /* HPW_ENA */
#define WM8961_HPW_WMV_SHOWT                    0x0008  /* HPW_WMV_SHOWT */
#define WM8961_HPW_WMV_SHOWT_MASK               0x0008  /* HPW_WMV_SHOWT */
#define WM8961_HPW_WMV_SHOWT_SHIFT                   3  /* HPW_WMV_SHOWT */
#define WM8961_HPW_WMV_SHOWT_WIDTH                   1  /* HPW_WMV_SHOWT */
#define WM8961_HPW_ENA_OUTP                     0x0004  /* HPW_ENA_OUTP */
#define WM8961_HPW_ENA_OUTP_MASK                0x0004  /* HPW_ENA_OUTP */
#define WM8961_HPW_ENA_OUTP_SHIFT                    2  /* HPW_ENA_OUTP */
#define WM8961_HPW_ENA_OUTP_WIDTH                    1  /* HPW_ENA_OUTP */
#define WM8961_HPW_ENA_DWY                      0x0002  /* HPW_ENA_DWY */
#define WM8961_HPW_ENA_DWY_MASK                 0x0002  /* HPW_ENA_DWY */
#define WM8961_HPW_ENA_DWY_SHIFT                     1  /* HPW_ENA_DWY */
#define WM8961_HPW_ENA_DWY_WIDTH                     1  /* HPW_ENA_DWY */
#define WM8961_HPW_ENA                          0x0001  /* HPW_ENA */
#define WM8961_HPW_ENA_MASK                     0x0001  /* HPW_ENA */
#define WM8961_HPW_ENA_SHIFT                         0  /* HPW_ENA */
#define WM8961_HPW_ENA_WIDTH                         1  /* HPW_ENA */

/*
 * W71 (0x47) - Anawogue HP 2
 */
#define WM8961_HPW_VOW_MASK                     0x01C0  /* HPW_VOW - [8:6] */
#define WM8961_HPW_VOW_SHIFT                         6  /* HPW_VOW - [8:6] */
#define WM8961_HPW_VOW_WIDTH                         3  /* HPW_VOW - [8:6] */
#define WM8961_HPW_VOW_MASK                     0x0038  /* HPW_VOW - [5:3] */
#define WM8961_HPW_VOW_SHIFT                         3  /* HPW_VOW - [5:3] */
#define WM8961_HPW_VOW_WIDTH                         3  /* HPW_VOW - [5:3] */
#define WM8961_HP_BIAS_BOOST_MASK               0x0007  /* HP_BIAS_BOOST - [2:0] */
#define WM8961_HP_BIAS_BOOST_SHIFT                   0  /* HP_BIAS_BOOST - [2:0] */
#define WM8961_HP_BIAS_BOOST_WIDTH                   3  /* HP_BIAS_BOOST - [2:0] */

/*
 * W72 (0x48) - Chawge Pump 1
 */
#define WM8961_CP_ENA                           0x0001  /* CP_ENA */
#define WM8961_CP_ENA_MASK                      0x0001  /* CP_ENA */
#define WM8961_CP_ENA_SHIFT                          0  /* CP_ENA */
#define WM8961_CP_ENA_WIDTH                          1  /* CP_ENA */

/*
 * W82 (0x52) - Chawge Pump B
 */
#define WM8961_CP_DYN_PWW_MASK                  0x0003  /* CP_DYN_PWW - [1:0] */
#define WM8961_CP_DYN_PWW_SHIFT                      0  /* CP_DYN_PWW - [1:0] */
#define WM8961_CP_DYN_PWW_WIDTH                      2  /* CP_DYN_PWW - [1:0] */

/*
 * W87 (0x57) - Wwite Sequencew 1
 */
#define WM8961_WSEQ_ENA                         0x0020  /* WSEQ_ENA */
#define WM8961_WSEQ_ENA_MASK                    0x0020  /* WSEQ_ENA */
#define WM8961_WSEQ_ENA_SHIFT                        5  /* WSEQ_ENA */
#define WM8961_WSEQ_ENA_WIDTH                        1  /* WSEQ_ENA */
#define WM8961_WSEQ_WWITE_INDEX_MASK            0x001F  /* WSEQ_WWITE_INDEX - [4:0] */
#define WM8961_WSEQ_WWITE_INDEX_SHIFT                0  /* WSEQ_WWITE_INDEX - [4:0] */
#define WM8961_WSEQ_WWITE_INDEX_WIDTH                5  /* WSEQ_WWITE_INDEX - [4:0] */

/*
 * W88 (0x58) - Wwite Sequencew 2
 */
#define WM8961_WSEQ_EOS                         0x0100  /* WSEQ_EOS */
#define WM8961_WSEQ_EOS_MASK                    0x0100  /* WSEQ_EOS */
#define WM8961_WSEQ_EOS_SHIFT                        8  /* WSEQ_EOS */
#define WM8961_WSEQ_EOS_WIDTH                        1  /* WSEQ_EOS */
#define WM8961_WSEQ_ADDW_MASK                   0x00FF  /* WSEQ_ADDW - [7:0] */
#define WM8961_WSEQ_ADDW_SHIFT                       0  /* WSEQ_ADDW - [7:0] */
#define WM8961_WSEQ_ADDW_WIDTH                       8  /* WSEQ_ADDW - [7:0] */

/*
 * W89 (0x59) - Wwite Sequencew 3
 */
#define WM8961_WSEQ_DATA_MASK                   0x00FF  /* WSEQ_DATA - [7:0] */
#define WM8961_WSEQ_DATA_SHIFT                       0  /* WSEQ_DATA - [7:0] */
#define WM8961_WSEQ_DATA_WIDTH                       8  /* WSEQ_DATA - [7:0] */

/*
 * W90 (0x5A) - Wwite Sequencew 4
 */
#define WM8961_WSEQ_ABOWT                       0x0100  /* WSEQ_ABOWT */
#define WM8961_WSEQ_ABOWT_MASK                  0x0100  /* WSEQ_ABOWT */
#define WM8961_WSEQ_ABOWT_SHIFT                      8  /* WSEQ_ABOWT */
#define WM8961_WSEQ_ABOWT_WIDTH                      1  /* WSEQ_ABOWT */
#define WM8961_WSEQ_STAWT                       0x0080  /* WSEQ_STAWT */
#define WM8961_WSEQ_STAWT_MASK                  0x0080  /* WSEQ_STAWT */
#define WM8961_WSEQ_STAWT_SHIFT                      7  /* WSEQ_STAWT */
#define WM8961_WSEQ_STAWT_WIDTH                      1  /* WSEQ_STAWT */
#define WM8961_WSEQ_STAWT_INDEX_MASK            0x003F  /* WSEQ_STAWT_INDEX - [5:0] */
#define WM8961_WSEQ_STAWT_INDEX_SHIFT                0  /* WSEQ_STAWT_INDEX - [5:0] */
#define WM8961_WSEQ_STAWT_INDEX_WIDTH                6  /* WSEQ_STAWT_INDEX - [5:0] */

/*
 * W91 (0x5B) - Wwite Sequencew 5
 */
#define WM8961_WSEQ_DATA_WIDTH_MASK             0x0070  /* WSEQ_DATA_WIDTH - [6:4] */
#define WM8961_WSEQ_DATA_WIDTH_SHIFT                 4  /* WSEQ_DATA_WIDTH - [6:4] */
#define WM8961_WSEQ_DATA_WIDTH_WIDTH                 3  /* WSEQ_DATA_WIDTH - [6:4] */
#define WM8961_WSEQ_DATA_STAWT_MASK             0x000F  /* WSEQ_DATA_STAWT - [3:0] */
#define WM8961_WSEQ_DATA_STAWT_SHIFT                 0  /* WSEQ_DATA_STAWT - [3:0] */
#define WM8961_WSEQ_DATA_STAWT_WIDTH                 4  /* WSEQ_DATA_STAWT - [3:0] */

/*
 * W92 (0x5C) - Wwite Sequencew 6
 */
#define WM8961_WSEQ_DEWAY_MASK                  0x000F  /* WSEQ_DEWAY - [3:0] */
#define WM8961_WSEQ_DEWAY_SHIFT                      0  /* WSEQ_DEWAY - [3:0] */
#define WM8961_WSEQ_DEWAY_WIDTH                      4  /* WSEQ_DEWAY - [3:0] */

/*
 * W93 (0x5D) - Wwite Sequencew 7
 */
#define WM8961_WSEQ_BUSY                        0x0001  /* WSEQ_BUSY */
#define WM8961_WSEQ_BUSY_MASK                   0x0001  /* WSEQ_BUSY */
#define WM8961_WSEQ_BUSY_SHIFT                       0  /* WSEQ_BUSY */
#define WM8961_WSEQ_BUSY_WIDTH                       1  /* WSEQ_BUSY */

/*
 * W252 (0xFC) - Genewaw test 1
 */
#define WM8961_AWA_ENA                          0x0002  /* AWA_ENA */
#define WM8961_AWA_ENA_MASK                     0x0002  /* AWA_ENA */
#define WM8961_AWA_ENA_SHIFT                         1  /* AWA_ENA */
#define WM8961_AWA_ENA_WIDTH                         1  /* AWA_ENA */
#define WM8961_AUTO_INC                         0x0001  /* AUTO_INC */
#define WM8961_AUTO_INC_MASK                    0x0001  /* AUTO_INC */
#define WM8961_AUTO_INC_SHIFT                        0  /* AUTO_INC */
#define WM8961_AUTO_INC_WIDTH                        1  /* AUTO_INC */

#endif
