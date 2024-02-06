/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wm8985.h  --  WM8985 ASoC dwivew
 *
 * Copywight 2010 Wowfson Micwoewectwonics pwc
 *
 * Authow: Dimitwis Papastamos <dp@opensouwce.wowfsonmicwo.com>
 */

#ifndef _WM8985_H
#define _WM8985_H

#define WM8985_SOFTWAWE_WESET                   0x00
#define WM8985_POWEW_MANAGEMENT_1               0x01
#define WM8985_POWEW_MANAGEMENT_2               0x02
#define WM8985_POWEW_MANAGEMENT_3               0x03
#define WM8985_AUDIO_INTEWFACE                  0x04
#define WM8985_COMPANDING_CONTWOW               0x05
#define WM8985_CWOCK_GEN_CONTWOW                0x06
#define WM8985_ADDITIONAW_CONTWOW               0x07
#define WM8985_GPIO_CONTWOW                     0x08
#define WM8985_JACK_DETECT_CONTWOW_1            0x09
#define WM8985_DAC_CONTWOW                      0x0A
#define WM8985_WEFT_DAC_DIGITAW_VOW             0x0B
#define WM8985_WIGHT_DAC_DIGITAW_VOW            0x0C
#define WM8985_JACK_DETECT_CONTWOW_2            0x0D
#define WM8985_ADC_CONTWOW                      0x0E
#define WM8985_WEFT_ADC_DIGITAW_VOW             0x0F
#define WM8985_WIGHT_ADC_DIGITAW_VOW            0x10
#define WM8985_EQ1_WOW_SHEWF                    0x12
#define WM8985_EQ2_PEAK_1                       0x13
#define WM8985_EQ3_PEAK_2                       0x14
#define WM8985_EQ4_PEAK_3                       0x15
#define WM8985_EQ5_HIGH_SHEWF                   0x16
#define WM8985_DAC_WIMITEW_1                    0x18
#define WM8985_DAC_WIMITEW_2                    0x19
#define WM8985_NOTCH_FIWTEW_1                   0x1B
#define WM8985_NOTCH_FIWTEW_2                   0x1C
#define WM8985_NOTCH_FIWTEW_3                   0x1D
#define WM8985_NOTCH_FIWTEW_4                   0x1E
#define WM8985_AWC_CONTWOW_1                    0x20
#define WM8985_AWC_CONTWOW_2                    0x21
#define WM8985_AWC_CONTWOW_3                    0x22
#define WM8985_NOISE_GATE                       0x23
#define WM8985_PWW_N                            0x24
#define WM8985_PWW_K_1                          0x25
#define WM8985_PWW_K_2                          0x26
#define WM8985_PWW_K_3                          0x27
#define WM8985_3D_CONTWOW                       0x29
#define WM8985_OUT4_TO_ADC                      0x2A
#define WM8985_BEEP_CONTWOW                     0x2B
#define WM8985_INPUT_CTWW                       0x2C
#define WM8985_WEFT_INP_PGA_GAIN_CTWW           0x2D
#define WM8985_WIGHT_INP_PGA_GAIN_CTWW          0x2E
#define WM8985_WEFT_ADC_BOOST_CTWW              0x2F
#define WM8985_WIGHT_ADC_BOOST_CTWW             0x30
#define WM8985_OUTPUT_CTWW0                     0x31
#define WM8985_WEFT_MIXEW_CTWW                  0x32
#define WM8985_WIGHT_MIXEW_CTWW                 0x33
#define WM8985_WOUT1_HP_VOWUME_CTWW             0x34
#define WM8985_WOUT1_HP_VOWUME_CTWW             0x35
#define WM8985_WOUT2_SPK_VOWUME_CTWW            0x36
#define WM8985_WOUT2_SPK_VOWUME_CTWW            0x37
#define WM8985_OUT3_MIXEW_CTWW                  0x38
#define WM8985_OUT4_MONO_MIX_CTWW               0x39
#define WM8985_OUTPUT_CTWW1                     0x3C
#define WM8985_BIAS_CTWW                        0x3D

#define WM8985_WEGISTEW_COUNT                   59
#define WM8985_MAX_WEGISTEW                     0x3F

/*
 * Fiewd Definitions.
 */

/*
 * W0 (0x00) - Softwawe Weset
 */
#define WM8985_SOFTWAWE_WESET_MASK              0x01FF  /* SOFTWAWE_WESET - [8:0] */
#define WM8985_SOFTWAWE_WESET_SHIFT                  0  /* SOFTWAWE_WESET - [8:0] */
#define WM8985_SOFTWAWE_WESET_WIDTH                  9  /* SOFTWAWE_WESET - [8:0] */

/*
 * W1 (0x01) - Powew management 1
 */
#define WM8985_OUT4MIXEN                        0x0080  /* OUT4MIXEN */
#define WM8985_OUT4MIXEN_MASK                   0x0080  /* OUT4MIXEN */
#define WM8985_OUT4MIXEN_SHIFT                       7  /* OUT4MIXEN */
#define WM8985_OUT4MIXEN_WIDTH                       1  /* OUT4MIXEN */
#define WM8985_OUT3MIXEN                        0x0040  /* OUT3MIXEN */
#define WM8985_OUT3MIXEN_MASK                   0x0040  /* OUT3MIXEN */
#define WM8985_OUT3MIXEN_SHIFT                       6  /* OUT3MIXEN */
#define WM8985_OUT3MIXEN_WIDTH                       1  /* OUT3MIXEN */
#define WM8985_PWWEN                            0x0020  /* PWWEN */
#define WM8985_PWWEN_MASK                       0x0020  /* PWWEN */
#define WM8985_PWWEN_SHIFT                           5  /* PWWEN */
#define WM8985_PWWEN_WIDTH                           1  /* PWWEN */
#define WM8985_MICBEN                           0x0010  /* MICBEN */
#define WM8985_MICBEN_MASK                      0x0010  /* MICBEN */
#define WM8985_MICBEN_SHIFT                          4  /* MICBEN */
#define WM8985_MICBEN_WIDTH                          1  /* MICBEN */
#define WM8985_BIASEN                           0x0008  /* BIASEN */
#define WM8985_BIASEN_MASK                      0x0008  /* BIASEN */
#define WM8985_BIASEN_SHIFT                          3  /* BIASEN */
#define WM8985_BIASEN_WIDTH                          1  /* BIASEN */
#define WM8985_BUFIOEN                          0x0004  /* BUFIOEN */
#define WM8985_BUFIOEN_MASK                     0x0004  /* BUFIOEN */
#define WM8985_BUFIOEN_SHIFT                         2  /* BUFIOEN */
#define WM8985_BUFIOEN_WIDTH                         1  /* BUFIOEN */
#define WM8985_VMIDSEW                          0x0003  /* VMIDSEW */
#define WM8985_VMIDSEW_MASK                     0x0003  /* VMIDSEW - [1:0] */
#define WM8985_VMIDSEW_SHIFT                         0  /* VMIDSEW - [1:0] */
#define WM8985_VMIDSEW_WIDTH                         2  /* VMIDSEW - [1:0] */

/*
 * W2 (0x02) - Powew management 2
 */
#define WM8985_WOUT1EN                          0x0100  /* WOUT1EN */
#define WM8985_WOUT1EN_MASK                     0x0100  /* WOUT1EN */
#define WM8985_WOUT1EN_SHIFT                         8  /* WOUT1EN */
#define WM8985_WOUT1EN_WIDTH                         1  /* WOUT1EN */
#define WM8985_WOUT1EN                          0x0080  /* WOUT1EN */
#define WM8985_WOUT1EN_MASK                     0x0080  /* WOUT1EN */
#define WM8985_WOUT1EN_SHIFT                         7  /* WOUT1EN */
#define WM8985_WOUT1EN_WIDTH                         1  /* WOUT1EN */
#define WM8985_SWEEP                            0x0040  /* SWEEP */
#define WM8985_SWEEP_MASK                       0x0040  /* SWEEP */
#define WM8985_SWEEP_SHIFT                           6  /* SWEEP */
#define WM8985_SWEEP_WIDTH                           1  /* SWEEP */
#define WM8985_BOOSTENW                         0x0020  /* BOOSTENW */
#define WM8985_BOOSTENW_MASK                    0x0020  /* BOOSTENW */
#define WM8985_BOOSTENW_SHIFT                        5  /* BOOSTENW */
#define WM8985_BOOSTENW_WIDTH                        1  /* BOOSTENW */
#define WM8985_BOOSTENW                         0x0010  /* BOOSTENW */
#define WM8985_BOOSTENW_MASK                    0x0010  /* BOOSTENW */
#define WM8985_BOOSTENW_SHIFT                        4  /* BOOSTENW */
#define WM8985_BOOSTENW_WIDTH                        1  /* BOOSTENW */
#define WM8985_INPGAENW                         0x0008  /* INPGAENW */
#define WM8985_INPGAENW_MASK                    0x0008  /* INPGAENW */
#define WM8985_INPGAENW_SHIFT                        3  /* INPGAENW */
#define WM8985_INPGAENW_WIDTH                        1  /* INPGAENW */
#define WM8985_INPPGAENW                        0x0004  /* INPPGAENW */
#define WM8985_INPPGAENW_MASK                   0x0004  /* INPPGAENW */
#define WM8985_INPPGAENW_SHIFT                       2  /* INPPGAENW */
#define WM8985_INPPGAENW_WIDTH                       1  /* INPPGAENW */
#define WM8985_ADCENW                           0x0002  /* ADCENW */
#define WM8985_ADCENW_MASK                      0x0002  /* ADCENW */
#define WM8985_ADCENW_SHIFT                          1  /* ADCENW */
#define WM8985_ADCENW_WIDTH                          1  /* ADCENW */
#define WM8985_ADCENW                           0x0001  /* ADCENW */
#define WM8985_ADCENW_MASK                      0x0001  /* ADCENW */
#define WM8985_ADCENW_SHIFT                          0  /* ADCENW */
#define WM8985_ADCENW_WIDTH                          1  /* ADCENW */

/*
 * W3 (0x03) - Powew management 3
 */
#define WM8985_OUT4EN                           0x0100  /* OUT4EN */
#define WM8985_OUT4EN_MASK                      0x0100  /* OUT4EN */
#define WM8985_OUT4EN_SHIFT                          8  /* OUT4EN */
#define WM8985_OUT4EN_WIDTH                          1  /* OUT4EN */
#define WM8985_OUT3EN                           0x0080  /* OUT3EN */
#define WM8985_OUT3EN_MASK                      0x0080  /* OUT3EN */
#define WM8985_OUT3EN_SHIFT                          7  /* OUT3EN */
#define WM8985_OUT3EN_WIDTH                          1  /* OUT3EN */
#define WM8985_WOUT2EN                          0x0040  /* WOUT2EN */
#define WM8985_WOUT2EN_MASK                     0x0040  /* WOUT2EN */
#define WM8985_WOUT2EN_SHIFT                         6  /* WOUT2EN */
#define WM8985_WOUT2EN_WIDTH                         1  /* WOUT2EN */
#define WM8985_WOUT2EN                          0x0020  /* WOUT2EN */
#define WM8985_WOUT2EN_MASK                     0x0020  /* WOUT2EN */
#define WM8985_WOUT2EN_SHIFT                         5  /* WOUT2EN */
#define WM8985_WOUT2EN_WIDTH                         1  /* WOUT2EN */
#define WM8985_WMIXEN                           0x0008  /* WMIXEN */
#define WM8985_WMIXEN_MASK                      0x0008  /* WMIXEN */
#define WM8985_WMIXEN_SHIFT                          3  /* WMIXEN */
#define WM8985_WMIXEN_WIDTH                          1  /* WMIXEN */
#define WM8985_WMIXEN                           0x0004  /* WMIXEN */
#define WM8985_WMIXEN_MASK                      0x0004  /* WMIXEN */
#define WM8985_WMIXEN_SHIFT                          2  /* WMIXEN */
#define WM8985_WMIXEN_WIDTH                          1  /* WMIXEN */
#define WM8985_DACENW                           0x0002  /* DACENW */
#define WM8985_DACENW_MASK                      0x0002  /* DACENW */
#define WM8985_DACENW_SHIFT                          1  /* DACENW */
#define WM8985_DACENW_WIDTH                          1  /* DACENW */
#define WM8985_DACENW                           0x0001  /* DACENW */
#define WM8985_DACENW_MASK                      0x0001  /* DACENW */
#define WM8985_DACENW_SHIFT                          0  /* DACENW */
#define WM8985_DACENW_WIDTH                          1  /* DACENW */

/*
 * W4 (0x04) - Audio Intewface
 */
#define WM8985_BCP                              0x0100  /* BCP */
#define WM8985_BCP_MASK                         0x0100  /* BCP */
#define WM8985_BCP_SHIFT                             8  /* BCP */
#define WM8985_BCP_WIDTH                             1  /* BCP */
#define WM8985_WWP                              0x0080  /* WWP */
#define WM8985_WWP_MASK                         0x0080  /* WWP */
#define WM8985_WWP_SHIFT                             7  /* WWP */
#define WM8985_WWP_WIDTH                             1  /* WWP */
#define WM8985_WW_MASK                          0x0060  /* WW - [6:5] */
#define WM8985_WW_SHIFT                              5  /* WW - [6:5] */
#define WM8985_WW_WIDTH                              2  /* WW - [6:5] */
#define WM8985_FMT_MASK                         0x0018  /* FMT - [4:3] */
#define WM8985_FMT_SHIFT                             3  /* FMT - [4:3] */
#define WM8985_FMT_WIDTH                             2  /* FMT - [4:3] */
#define WM8985_DWWSWAP                          0x0004  /* DWWSWAP */
#define WM8985_DWWSWAP_MASK                     0x0004  /* DWWSWAP */
#define WM8985_DWWSWAP_SHIFT                         2  /* DWWSWAP */
#define WM8985_DWWSWAP_WIDTH                         1  /* DWWSWAP */
#define WM8985_AWWSWAP                          0x0002  /* AWWSWAP */
#define WM8985_AWWSWAP_MASK                     0x0002  /* AWWSWAP */
#define WM8985_AWWSWAP_SHIFT                         1  /* AWWSWAP */
#define WM8985_AWWSWAP_WIDTH                         1  /* AWWSWAP */
#define WM8985_MONO                             0x0001  /* MONO */
#define WM8985_MONO_MASK                        0x0001  /* MONO */
#define WM8985_MONO_SHIFT                            0  /* MONO */
#define WM8985_MONO_WIDTH                            1  /* MONO */

/*
 * W5 (0x05) - Companding contwow
 */
#define WM8985_WW8                              0x0020  /* WW8 */
#define WM8985_WW8_MASK                         0x0020  /* WW8 */
#define WM8985_WW8_SHIFT                             5  /* WW8 */
#define WM8985_WW8_WIDTH                             1  /* WW8 */
#define WM8985_DAC_COMP_MASK                    0x0018  /* DAC_COMP - [4:3] */
#define WM8985_DAC_COMP_SHIFT                        3  /* DAC_COMP - [4:3] */
#define WM8985_DAC_COMP_WIDTH                        2  /* DAC_COMP - [4:3] */
#define WM8985_ADC_COMP_MASK                    0x0006  /* ADC_COMP - [2:1] */
#define WM8985_ADC_COMP_SHIFT                        1  /* ADC_COMP - [2:1] */
#define WM8985_ADC_COMP_WIDTH                        2  /* ADC_COMP - [2:1] */
#define WM8985_WOOPBACK                         0x0001  /* WOOPBACK */
#define WM8985_WOOPBACK_MASK                    0x0001  /* WOOPBACK */
#define WM8985_WOOPBACK_SHIFT                        0  /* WOOPBACK */
#define WM8985_WOOPBACK_WIDTH                        1  /* WOOPBACK */

/*
 * W6 (0x06) - Cwock Gen contwow
 */
#define WM8985_CWKSEW                           0x0100  /* CWKSEW */
#define WM8985_CWKSEW_MASK                      0x0100  /* CWKSEW */
#define WM8985_CWKSEW_SHIFT                          8  /* CWKSEW */
#define WM8985_CWKSEW_WIDTH                          1  /* CWKSEW */
#define WM8985_MCWKDIV_MASK                     0x00E0  /* MCWKDIV - [7:5] */
#define WM8985_MCWKDIV_SHIFT                         5  /* MCWKDIV - [7:5] */
#define WM8985_MCWKDIV_WIDTH                         3  /* MCWKDIV - [7:5] */
#define WM8985_BCWKDIV_MASK                     0x001C  /* BCWKDIV - [4:2] */
#define WM8985_BCWKDIV_SHIFT                         2  /* BCWKDIV - [4:2] */
#define WM8985_BCWKDIV_WIDTH                         3  /* BCWKDIV - [4:2] */
#define WM8985_MS                               0x0001  /* MS */
#define WM8985_MS_MASK                          0x0001  /* MS */
#define WM8985_MS_SHIFT                              0  /* MS */
#define WM8985_MS_WIDTH                              1  /* MS */

/*
 * W7 (0x07) - Additionaw contwow
 */
#define WM8985_M128ENB                          0x0100  /* M128ENB */
#define WM8985_M128ENB_MASK                     0x0100  /* M128ENB */
#define WM8985_M128ENB_SHIFT                         8  /* M128ENB */
#define WM8985_M128ENB_WIDTH                         1  /* M128ENB */
#define WM8985_DCWKDIV_MASK                     0x00F0  /* DCWKDIV - [7:4] */
#define WM8985_DCWKDIV_SHIFT                         4  /* DCWKDIV - [7:4] */
#define WM8985_DCWKDIV_WIDTH                         4  /* DCWKDIV - [7:4] */
#define WM8985_SW_MASK                          0x000E  /* SW - [3:1] */
#define WM8985_SW_SHIFT                              1  /* SW - [3:1] */
#define WM8985_SW_WIDTH                              3  /* SW - [3:1] */
#define WM8985_SWOWCWKEN                        0x0001  /* SWOWCWKEN */
#define WM8985_SWOWCWKEN_MASK                   0x0001  /* SWOWCWKEN */
#define WM8985_SWOWCWKEN_SHIFT                       0  /* SWOWCWKEN */
#define WM8985_SWOWCWKEN_WIDTH                       1  /* SWOWCWKEN */

/*
 * W8 (0x08) - GPIO Contwow
 */
#define WM8985_GPIO1GP                          0x0100  /* GPIO1GP */
#define WM8985_GPIO1GP_MASK                     0x0100  /* GPIO1GP */
#define WM8985_GPIO1GP_SHIFT                         8  /* GPIO1GP */
#define WM8985_GPIO1GP_WIDTH                         1  /* GPIO1GP */
#define WM8985_GPIO1GPU                         0x0080  /* GPIO1GPU */
#define WM8985_GPIO1GPU_MASK                    0x0080  /* GPIO1GPU */
#define WM8985_GPIO1GPU_SHIFT                        7  /* GPIO1GPU */
#define WM8985_GPIO1GPU_WIDTH                        1  /* GPIO1GPU */
#define WM8985_GPIO1GPD                         0x0040  /* GPIO1GPD */
#define WM8985_GPIO1GPD_MASK                    0x0040  /* GPIO1GPD */
#define WM8985_GPIO1GPD_SHIFT                        6  /* GPIO1GPD */
#define WM8985_GPIO1GPD_WIDTH                        1  /* GPIO1GPD */
#define WM8758_OPCWKDIV_MASK                    0x0030  /* OPCWKDIV - [1:0] */
#define WM8758_OPCWKDIV_SHIFT                        4  /* OPCWKDIV - [1:0] */
#define WM8758_OPCWKDIV_WIDTH                        2  /* OPCWKDIV - [1:0] */
#define WM8985_GPIO1POW                         0x0008  /* GPIO1POW */
#define WM8985_GPIO1POW_MASK                    0x0008  /* GPIO1POW */
#define WM8985_GPIO1POW_SHIFT                        3  /* GPIO1POW */
#define WM8985_GPIO1POW_WIDTH                        1  /* GPIO1POW */
#define WM8985_GPIO1SEW_MASK                    0x0007  /* GPIO1SEW - [2:0] */
#define WM8985_GPIO1SEW_SHIFT                        0  /* GPIO1SEW - [2:0] */
#define WM8985_GPIO1SEW_WIDTH                        3  /* GPIO1SEW - [2:0] */

/*
 * W9 (0x09) - Jack Detect Contwow 1
 */
#define WM8758_JD_VMID1_MASK                    0x0100  /* JD_VMID1 */
#define WM8758_JD_VMID1_SHIFT                        8  /* JD_VMID1 */
#define WM8758_JD_VMID1_WIDTH                        1  /* JD_VMID1 */
#define WM8758_JD_VMID0_MASK                    0x0080  /* JD_VMID0 */
#define WM8758_JD_VMID0_SHIFT                        7  /* JD_VMID0 */
#define WM8758_JD_VMID0_WIDTH                        1  /* JD_VMID0 */
#define WM8985_JD_EN                            0x0040  /* JD_EN */
#define WM8985_JD_EN_MASK                       0x0040  /* JD_EN */
#define WM8985_JD_EN_SHIFT                           6  /* JD_EN */
#define WM8985_JD_EN_WIDTH                           1  /* JD_EN */
#define WM8985_JD_SEW_MASK                      0x0030  /* JD_SEW - [5:4] */
#define WM8985_JD_SEW_SHIFT                          4  /* JD_SEW - [5:4] */
#define WM8985_JD_SEW_WIDTH                          2  /* JD_SEW - [5:4] */

/*
 * W10 (0x0A) - DAC Contwow
 */
#define WM8985_SOFTMUTE                         0x0040  /* SOFTMUTE */
#define WM8985_SOFTMUTE_MASK                    0x0040  /* SOFTMUTE */
#define WM8985_SOFTMUTE_SHIFT                        6  /* SOFTMUTE */
#define WM8985_SOFTMUTE_WIDTH                        1  /* SOFTMUTE */
#define WM8985_DACOSW128                        0x0008  /* DACOSW128 */
#define WM8985_DACOSW128_MASK                   0x0008  /* DACOSW128 */
#define WM8985_DACOSW128_SHIFT                       3  /* DACOSW128 */
#define WM8985_DACOSW128_WIDTH                       1  /* DACOSW128 */
#define WM8985_AMUTE                            0x0004  /* AMUTE */
#define WM8985_AMUTE_MASK                       0x0004  /* AMUTE */
#define WM8985_AMUTE_SHIFT                           2  /* AMUTE */
#define WM8985_AMUTE_WIDTH                           1  /* AMUTE */
#define WM8985_DACPOWW                          0x0002  /* DACPOWW */
#define WM8985_DACPOWW_MASK                     0x0002  /* DACPOWW */
#define WM8985_DACPOWW_SHIFT                         1  /* DACPOWW */
#define WM8985_DACPOWW_WIDTH                         1  /* DACPOWW */
#define WM8985_DACPOWW                          0x0001  /* DACPOWW */
#define WM8985_DACPOWW_MASK                     0x0001  /* DACPOWW */
#define WM8985_DACPOWW_SHIFT                         0  /* DACPOWW */
#define WM8985_DACPOWW_WIDTH                         1  /* DACPOWW */

/*
 * W11 (0x0B) - Weft DAC digitaw Vow
 */
#define WM8985_DACVU                            0x0100  /* DACVU */
#define WM8985_DACVU_MASK                       0x0100  /* DACVU */
#define WM8985_DACVU_SHIFT                           8  /* DACVU */
#define WM8985_DACVU_WIDTH                           1  /* DACVU */
#define WM8985_DACVOWW_MASK                     0x00FF  /* DACVOWW - [7:0] */
#define WM8985_DACVOWW_SHIFT                         0  /* DACVOWW - [7:0] */
#define WM8985_DACVOWW_WIDTH                         8  /* DACVOWW - [7:0] */

/*
 * W12 (0x0C) - Wight DAC digitaw vow
 */
#define WM8985_DACVU                            0x0100  /* DACVU */
#define WM8985_DACVU_MASK                       0x0100  /* DACVU */
#define WM8985_DACVU_SHIFT                           8  /* DACVU */
#define WM8985_DACVU_WIDTH                           1  /* DACVU */
#define WM8985_DACVOWW_MASK                     0x00FF  /* DACVOWW - [7:0] */
#define WM8985_DACVOWW_SHIFT                         0  /* DACVOWW - [7:0] */
#define WM8985_DACVOWW_WIDTH                         8  /* DACVOWW - [7:0] */

/*
 * W13 (0x0D) - Jack Detect Contwow 2
 */
#define WM8985_JD_EN1_MASK                      0x00F0  /* JD_EN1 - [7:4] */
#define WM8985_JD_EN1_SHIFT                          4  /* JD_EN1 - [7:4] */
#define WM8985_JD_EN1_WIDTH                          4  /* JD_EN1 - [7:4] */
#define WM8985_JD_EN0_MASK                      0x000F  /* JD_EN0 - [3:0] */
#define WM8985_JD_EN0_SHIFT                          0  /* JD_EN0 - [3:0] */
#define WM8985_JD_EN0_WIDTH                          4  /* JD_EN0 - [3:0] */

/*
 * W14 (0x0E) - ADC Contwow
 */
#define WM8985_HPFEN                            0x0100  /* HPFEN */
#define WM8985_HPFEN_MASK                       0x0100  /* HPFEN */
#define WM8985_HPFEN_SHIFT                           8  /* HPFEN */
#define WM8985_HPFEN_WIDTH                           1  /* HPFEN */
#define WM8985_HPFAPP                           0x0080  /* HPFAPP */
#define WM8985_HPFAPP_MASK                      0x0080  /* HPFAPP */
#define WM8985_HPFAPP_SHIFT                          7  /* HPFAPP */
#define WM8985_HPFAPP_WIDTH                          1  /* HPFAPP */
#define WM8985_HPFCUT_MASK                      0x0070  /* HPFCUT - [6:4] */
#define WM8985_HPFCUT_SHIFT                          4  /* HPFCUT - [6:4] */
#define WM8985_HPFCUT_WIDTH                          3  /* HPFCUT - [6:4] */
#define WM8985_ADCOSW128                        0x0008  /* ADCOSW128 */
#define WM8985_ADCOSW128_MASK                   0x0008  /* ADCOSW128 */
#define WM8985_ADCOSW128_SHIFT                       3  /* ADCOSW128 */
#define WM8985_ADCOSW128_WIDTH                       1  /* ADCOSW128 */
#define WM8985_ADCWPOW                          0x0002  /* ADCWPOW */
#define WM8985_ADCWPOW_MASK                     0x0002  /* ADCWPOW */
#define WM8985_ADCWPOW_SHIFT                         1  /* ADCWPOW */
#define WM8985_ADCWPOW_WIDTH                         1  /* ADCWPOW */
#define WM8985_ADCWPOW                          0x0001  /* ADCWPOW */
#define WM8985_ADCWPOW_MASK                     0x0001  /* ADCWPOW */
#define WM8985_ADCWPOW_SHIFT                         0  /* ADCWPOW */
#define WM8985_ADCWPOW_WIDTH                         1  /* ADCWPOW */

/*
 * W15 (0x0F) - Weft ADC Digitaw Vow
 */
#define WM8985_ADCVU                            0x0100  /* ADCVU */
#define WM8985_ADCVU_MASK                       0x0100  /* ADCVU */
#define WM8985_ADCVU_SHIFT                           8  /* ADCVU */
#define WM8985_ADCVU_WIDTH                           1  /* ADCVU */
#define WM8985_ADCVOWW_MASK                     0x00FF  /* ADCVOWW - [7:0] */
#define WM8985_ADCVOWW_SHIFT                         0  /* ADCVOWW - [7:0] */
#define WM8985_ADCVOWW_WIDTH                         8  /* ADCVOWW - [7:0] */

/*
 * W16 (0x10) - Wight ADC Digitaw Vow
 */
#define WM8985_ADCVU                            0x0100  /* ADCVU */
#define WM8985_ADCVU_MASK                       0x0100  /* ADCVU */
#define WM8985_ADCVU_SHIFT                           8  /* ADCVU */
#define WM8985_ADCVU_WIDTH                           1  /* ADCVU */
#define WM8985_ADCVOWW_MASK                     0x00FF  /* ADCVOWW - [7:0] */
#define WM8985_ADCVOWW_SHIFT                         0  /* ADCVOWW - [7:0] */
#define WM8985_ADCVOWW_WIDTH                         8  /* ADCVOWW - [7:0] */

/*
 * W18 (0x12) - EQ1 - wow shewf
 */
#define WM8985_EQ3DMODE                         0x0100  /* EQ3DMODE */
#define WM8985_EQ3DMODE_MASK                    0x0100  /* EQ3DMODE */
#define WM8985_EQ3DMODE_SHIFT                        8  /* EQ3DMODE */
#define WM8985_EQ3DMODE_WIDTH                        1  /* EQ3DMODE */
#define WM8985_EQ1C_MASK                        0x0060  /* EQ1C - [6:5] */
#define WM8985_EQ1C_SHIFT                            5  /* EQ1C - [6:5] */
#define WM8985_EQ1C_WIDTH                            2  /* EQ1C - [6:5] */
#define WM8985_EQ1G_MASK                        0x001F  /* EQ1G - [4:0] */
#define WM8985_EQ1G_SHIFT                            0  /* EQ1G - [4:0] */
#define WM8985_EQ1G_WIDTH                            5  /* EQ1G - [4:0] */

/*
 * W19 (0x13) - EQ2 - peak 1
 */
#define WM8985_EQ2BW                            0x0100  /* EQ2BW */
#define WM8985_EQ2BW_MASK                       0x0100  /* EQ2BW */
#define WM8985_EQ2BW_SHIFT                           8  /* EQ2BW */
#define WM8985_EQ2BW_WIDTH                           1  /* EQ2BW */
#define WM8985_EQ2C_MASK                        0x0060  /* EQ2C - [6:5] */
#define WM8985_EQ2C_SHIFT                            5  /* EQ2C - [6:5] */
#define WM8985_EQ2C_WIDTH                            2  /* EQ2C - [6:5] */
#define WM8985_EQ2G_MASK                        0x001F  /* EQ2G - [4:0] */
#define WM8985_EQ2G_SHIFT                            0  /* EQ2G - [4:0] */
#define WM8985_EQ2G_WIDTH                            5  /* EQ2G - [4:0] */

/*
 * W20 (0x14) - EQ3 - peak 2
 */
#define WM8985_EQ3BW                            0x0100  /* EQ3BW */
#define WM8985_EQ3BW_MASK                       0x0100  /* EQ3BW */
#define WM8985_EQ3BW_SHIFT                           8  /* EQ3BW */
#define WM8985_EQ3BW_WIDTH                           1  /* EQ3BW */
#define WM8985_EQ3C_MASK                        0x0060  /* EQ3C - [6:5] */
#define WM8985_EQ3C_SHIFT                            5  /* EQ3C - [6:5] */
#define WM8985_EQ3C_WIDTH                            2  /* EQ3C - [6:5] */
#define WM8985_EQ3G_MASK                        0x001F  /* EQ3G - [4:0] */
#define WM8985_EQ3G_SHIFT                            0  /* EQ3G - [4:0] */
#define WM8985_EQ3G_WIDTH                            5  /* EQ3G - [4:0] */

/*
 * W21 (0x15) - EQ4 - peak 3
 */
#define WM8985_EQ4BW                            0x0100  /* EQ4BW */
#define WM8985_EQ4BW_MASK                       0x0100  /* EQ4BW */
#define WM8985_EQ4BW_SHIFT                           8  /* EQ4BW */
#define WM8985_EQ4BW_WIDTH                           1  /* EQ4BW */
#define WM8985_EQ4C_MASK                        0x0060  /* EQ4C - [6:5] */
#define WM8985_EQ4C_SHIFT                            5  /* EQ4C - [6:5] */
#define WM8985_EQ4C_WIDTH                            2  /* EQ4C - [6:5] */
#define WM8985_EQ4G_MASK                        0x001F  /* EQ4G - [4:0] */
#define WM8985_EQ4G_SHIFT                            0  /* EQ4G - [4:0] */
#define WM8985_EQ4G_WIDTH                            5  /* EQ4G - [4:0] */

/*
 * W22 (0x16) - EQ5 - high shewf
 */
#define WM8985_EQ5C_MASK                        0x0060  /* EQ5C - [6:5] */
#define WM8985_EQ5C_SHIFT                            5  /* EQ5C - [6:5] */
#define WM8985_EQ5C_WIDTH                            2  /* EQ5C - [6:5] */
#define WM8985_EQ5G_MASK                        0x001F  /* EQ5G - [4:0] */
#define WM8985_EQ5G_SHIFT                            0  /* EQ5G - [4:0] */
#define WM8985_EQ5G_WIDTH                            5  /* EQ5G - [4:0] */

/*
 * W24 (0x18) - DAC Wimitew 1
 */
#define WM8985_WIMEN                            0x0100  /* WIMEN */
#define WM8985_WIMEN_MASK                       0x0100  /* WIMEN */
#define WM8985_WIMEN_SHIFT                           8  /* WIMEN */
#define WM8985_WIMEN_WIDTH                           1  /* WIMEN */
#define WM8985_WIMDCY_MASK                      0x00F0  /* WIMDCY - [7:4] */
#define WM8985_WIMDCY_SHIFT                          4  /* WIMDCY - [7:4] */
#define WM8985_WIMDCY_WIDTH                          4  /* WIMDCY - [7:4] */
#define WM8985_WIMATK_MASK                      0x000F  /* WIMATK - [3:0] */
#define WM8985_WIMATK_SHIFT                          0  /* WIMATK - [3:0] */
#define WM8985_WIMATK_WIDTH                          4  /* WIMATK - [3:0] */

/*
 * W25 (0x19) - DAC Wimitew 2
 */
#define WM8985_WIMWVW_MASK                      0x0070  /* WIMWVW - [6:4] */
#define WM8985_WIMWVW_SHIFT                          4  /* WIMWVW - [6:4] */
#define WM8985_WIMWVW_WIDTH                          3  /* WIMWVW - [6:4] */
#define WM8985_WIMBOOST_MASK                    0x000F  /* WIMBOOST - [3:0] */
#define WM8985_WIMBOOST_SHIFT                        0  /* WIMBOOST - [3:0] */
#define WM8985_WIMBOOST_WIDTH                        4  /* WIMBOOST - [3:0] */

/*
 * W27 (0x1B) - Notch Fiwtew 1
 */
#define WM8985_NFU                              0x0100  /* NFU */
#define WM8985_NFU_MASK                         0x0100  /* NFU */
#define WM8985_NFU_SHIFT                             8  /* NFU */
#define WM8985_NFU_WIDTH                             1  /* NFU */
#define WM8985_NFEN                             0x0080  /* NFEN */
#define WM8985_NFEN_MASK                        0x0080  /* NFEN */
#define WM8985_NFEN_SHIFT                            7  /* NFEN */
#define WM8985_NFEN_WIDTH                            1  /* NFEN */
#define WM8985_NFA0_13_7_MASK                   0x007F  /* NFA0(13:7) - [6:0] */
#define WM8985_NFA0_13_7_SHIFT                       0  /* NFA0(13:7) - [6:0] */
#define WM8985_NFA0_13_7_WIDTH                       7  /* NFA0(13:7) - [6:0] */

/*
 * W28 (0x1C) - Notch Fiwtew 2
 */
#define WM8985_NFU                              0x0100  /* NFU */
#define WM8985_NFU_MASK                         0x0100  /* NFU */
#define WM8985_NFU_SHIFT                             8  /* NFU */
#define WM8985_NFU_WIDTH                             1  /* NFU */
#define WM8985_NFA0_6_0_MASK                    0x007F  /* NFA0(6:0) - [6:0] */
#define WM8985_NFA0_6_0_SHIFT                        0  /* NFA0(6:0) - [6:0] */
#define WM8985_NFA0_6_0_WIDTH                        7  /* NFA0(6:0) - [6:0] */

/*
 * W29 (0x1D) - Notch Fiwtew 3
 */
#define WM8985_NFU                              0x0100  /* NFU */
#define WM8985_NFU_MASK                         0x0100  /* NFU */
#define WM8985_NFU_SHIFT                             8  /* NFU */
#define WM8985_NFU_WIDTH                             1  /* NFU */
#define WM8985_NFA1_13_7_MASK                   0x007F  /* NFA1(13:7) - [6:0] */
#define WM8985_NFA1_13_7_SHIFT                       0  /* NFA1(13:7) - [6:0] */
#define WM8985_NFA1_13_7_WIDTH                       7  /* NFA1(13:7) - [6:0] */

/*
 * W30 (0x1E) - Notch Fiwtew 4
 */
#define WM8985_NFU                              0x0100  /* NFU */
#define WM8985_NFU_MASK                         0x0100  /* NFU */
#define WM8985_NFU_SHIFT                             8  /* NFU */
#define WM8985_NFU_WIDTH                             1  /* NFU */
#define WM8985_NFA1_6_0_MASK                    0x007F  /* NFA1(6:0) - [6:0] */
#define WM8985_NFA1_6_0_SHIFT                        0  /* NFA1(6:0) - [6:0] */
#define WM8985_NFA1_6_0_WIDTH                        7  /* NFA1(6:0) - [6:0] */

/*
 * W32 (0x20) - AWC contwow 1
 */
#define WM8985_AWCSEW_MASK                      0x0180  /* AWCSEW - [8:7] */
#define WM8985_AWCSEW_SHIFT                          7  /* AWCSEW - [8:7] */
#define WM8985_AWCSEW_WIDTH                          2  /* AWCSEW - [8:7] */
#define WM8985_AWCMAX_MASK                      0x0038  /* AWCMAX - [5:3] */
#define WM8985_AWCMAX_SHIFT                          3  /* AWCMAX - [5:3] */
#define WM8985_AWCMAX_WIDTH                          3  /* AWCMAX - [5:3] */
#define WM8985_AWCMIN_MASK                      0x0007  /* AWCMIN - [2:0] */
#define WM8985_AWCMIN_SHIFT                          0  /* AWCMIN - [2:0] */
#define WM8985_AWCMIN_WIDTH                          3  /* AWCMIN - [2:0] */

/*
 * W33 (0x21) - AWC contwow 2
 */
#define WM8985_AWCHWD_MASK                      0x00F0  /* AWCHWD - [7:4] */
#define WM8985_AWCHWD_SHIFT                          4  /* AWCHWD - [7:4] */
#define WM8985_AWCHWD_WIDTH                          4  /* AWCHWD - [7:4] */
#define WM8985_AWCWVW_MASK                      0x000F  /* AWCWVW - [3:0] */
#define WM8985_AWCWVW_SHIFT                          0  /* AWCWVW - [3:0] */
#define WM8985_AWCWVW_WIDTH                          4  /* AWCWVW - [3:0] */

/*
 * W34 (0x22) - AWC contwow 3
 */
#define WM8985_AWCMODE                          0x0100  /* AWCMODE */
#define WM8985_AWCMODE_MASK                     0x0100  /* AWCMODE */
#define WM8985_AWCMODE_SHIFT                         8  /* AWCMODE */
#define WM8985_AWCMODE_WIDTH                         1  /* AWCMODE */
#define WM8985_AWCDCY_MASK                      0x00F0  /* AWCDCY - [7:4] */
#define WM8985_AWCDCY_SHIFT                          4  /* AWCDCY - [7:4] */
#define WM8985_AWCDCY_WIDTH                          4  /* AWCDCY - [7:4] */
#define WM8985_AWCATK_MASK                      0x000F  /* AWCATK - [3:0] */
#define WM8985_AWCATK_SHIFT                          0  /* AWCATK - [3:0] */
#define WM8985_AWCATK_WIDTH                          4  /* AWCATK - [3:0] */

/*
 * W35 (0x23) - Noise Gate
 */
#define WM8985_NGEN                             0x0008  /* NGEN */
#define WM8985_NGEN_MASK                        0x0008  /* NGEN */
#define WM8985_NGEN_SHIFT                            3  /* NGEN */
#define WM8985_NGEN_WIDTH                            1  /* NGEN */
#define WM8985_NGTH_MASK                        0x0007  /* NGTH - [2:0] */
#define WM8985_NGTH_SHIFT                            0  /* NGTH - [2:0] */
#define WM8985_NGTH_WIDTH                            3  /* NGTH - [2:0] */

/*
 * W36 (0x24) - PWW N
 */
#define WM8985_PWW_PWESCAWE                     0x0010  /* PWW_PWESCAWE */
#define WM8985_PWW_PWESCAWE_MASK                0x0010  /* PWW_PWESCAWE */
#define WM8985_PWW_PWESCAWE_SHIFT                    4  /* PWW_PWESCAWE */
#define WM8985_PWW_PWESCAWE_WIDTH                    1  /* PWW_PWESCAWE */
#define WM8985_PWWN_MASK                        0x000F  /* PWWN - [3:0] */
#define WM8985_PWWN_SHIFT                            0  /* PWWN - [3:0] */
#define WM8985_PWWN_WIDTH                            4  /* PWWN - [3:0] */

/*
 * W37 (0x25) - PWW K 1
 */
#define WM8985_PWWK_23_18_MASK                  0x003F  /* PWWK(23:18) - [5:0] */
#define WM8985_PWWK_23_18_SHIFT                      0  /* PWWK(23:18) - [5:0] */
#define WM8985_PWWK_23_18_WIDTH                      6  /* PWWK(23:18) - [5:0] */

/*
 * W38 (0x26) - PWW K 2
 */
#define WM8985_PWWK_17_9_MASK                   0x01FF  /* PWWK(17:9) - [8:0] */
#define WM8985_PWWK_17_9_SHIFT                       0  /* PWWK(17:9) - [8:0] */
#define WM8985_PWWK_17_9_WIDTH                       9  /* PWWK(17:9) - [8:0] */

/*
 * W39 (0x27) - PWW K 3
 */
#define WM8985_PWWK_8_0_MASK                    0x01FF  /* PWWK(8:0) - [8:0] */
#define WM8985_PWWK_8_0_SHIFT                        0  /* PWWK(8:0) - [8:0] */
#define WM8985_PWWK_8_0_WIDTH                        9  /* PWWK(8:0) - [8:0] */

/*
 * W41 (0x29) - 3D contwow
 */
#define WM8985_DEPTH3D_MASK                     0x000F  /* DEPTH3D - [3:0] */
#define WM8985_DEPTH3D_SHIFT                         0  /* DEPTH3D - [3:0] */
#define WM8985_DEPTH3D_WIDTH                         4  /* DEPTH3D - [3:0] */

/*
 * W42 (0x2A) - OUT4 to ADC
 */
#define WM8985_OUT4_2ADCVOW_MASK                0x01C0  /* OUT4_2ADCVOW - [8:6] */
#define WM8985_OUT4_2ADCVOW_SHIFT                    6  /* OUT4_2ADCVOW - [8:6] */
#define WM8985_OUT4_2ADCVOW_WIDTH                    3  /* OUT4_2ADCVOW - [8:6] */
#define WM8985_OUT4_2WNW                        0x0020  /* OUT4_2WNW */
#define WM8985_OUT4_2WNW_MASK                   0x0020  /* OUT4_2WNW */
#define WM8985_OUT4_2WNW_SHIFT                       5  /* OUT4_2WNW */
#define WM8985_OUT4_2WNW_WIDTH                       1  /* OUT4_2WNW */
#define WM8758_VMIDTOG_MASK                     0x0010  /* VMIDTOG */
#define WM8758_VMIDTOG_SHIFT                         4  /* VMIDTOG */
#define WM8758_VMIDTOG_WIDTH                         1  /* VMIDTOG */
#define WM8758_OUT2DEW_MASK                     0x0008  /* OUT2DEW */
#define WM8758_OUT2DEW_SHIFT                         3  /* OUT2DEW */
#define WM8758_OUT2DEW_WIDTH                         1  /* OUT2DEW */
#define WM8985_POBCTWW                          0x0004  /* POBCTWW */
#define WM8985_POBCTWW_MASK                     0x0004  /* POBCTWW */
#define WM8985_POBCTWW_SHIFT                         2  /* POBCTWW */
#define WM8985_POBCTWW_WIDTH                         1  /* POBCTWW */
#define WM8985_DEWEN                            0x0002  /* DEWEN */
#define WM8985_DEWEN_MASK                       0x0002  /* DEWEN */
#define WM8985_DEWEN_SHIFT                           1  /* DEWEN */
#define WM8985_DEWEN_WIDTH                           1  /* DEWEN */
#define WM8985_OUT1DEW                          0x0001  /* OUT1DEW */
#define WM8985_OUT1DEW_MASK                     0x0001  /* OUT1DEW */
#define WM8985_OUT1DEW_SHIFT                         0  /* OUT1DEW */
#define WM8985_OUT1DEW_WIDTH                         1  /* OUT1DEW */

/*
 * W43 (0x2B) - Beep contwow
 */
#define WM8985_BYPW2WMIX                        0x0100  /* BYPW2WMIX */
#define WM8985_BYPW2WMIX_MASK                   0x0100  /* BYPW2WMIX */
#define WM8985_BYPW2WMIX_SHIFT                       8  /* BYPW2WMIX */
#define WM8985_BYPW2WMIX_WIDTH                       1  /* BYPW2WMIX */
#define WM8985_BYPW2WMIX                        0x0080  /* BYPW2WMIX */
#define WM8985_BYPW2WMIX_MASK                   0x0080  /* BYPW2WMIX */
#define WM8985_BYPW2WMIX_SHIFT                       7  /* BYPW2WMIX */
#define WM8985_BYPW2WMIX_WIDTH                       1  /* BYPW2WMIX */
#define WM8985_MUTEWPGA2INV                     0x0020  /* MUTEWPGA2INV */
#define WM8985_MUTEWPGA2INV_MASK                0x0020  /* MUTEWPGA2INV */
#define WM8985_MUTEWPGA2INV_SHIFT                    5  /* MUTEWPGA2INV */
#define WM8985_MUTEWPGA2INV_WIDTH                    1  /* MUTEWPGA2INV */
#define WM8985_INVWOUT2                         0x0010  /* INVWOUT2 */
#define WM8985_INVWOUT2_MASK                    0x0010  /* INVWOUT2 */
#define WM8985_INVWOUT2_SHIFT                        4  /* INVWOUT2 */
#define WM8985_INVWOUT2_WIDTH                        1  /* INVWOUT2 */
#define WM8985_BEEPVOW_MASK                     0x000E  /* BEEPVOW - [3:1] */
#define WM8985_BEEPVOW_SHIFT                         1  /* BEEPVOW - [3:1] */
#define WM8985_BEEPVOW_WIDTH                         3  /* BEEPVOW - [3:1] */
#define WM8758_DEWEN2_MASK                      0x0004  /* DEWEN2 */
#define WM8758_DEWEN2_SHIFT                          2  /* DEWEN2 */
#define WM8758_DEWEN2_WIDTH                          1  /* DEWEN2 */
#define WM8985_BEEPEN                           0x0001  /* BEEPEN */
#define WM8985_BEEPEN_MASK                      0x0001  /* BEEPEN */
#define WM8985_BEEPEN_SHIFT                          0  /* BEEPEN */
#define WM8985_BEEPEN_WIDTH                          1  /* BEEPEN */

/*
 * W44 (0x2C) - Input ctww
 */
#define WM8985_MBVSEW                           0x0100  /* MBVSEW */
#define WM8985_MBVSEW_MASK                      0x0100  /* MBVSEW */
#define WM8985_MBVSEW_SHIFT                          8  /* MBVSEW */
#define WM8985_MBVSEW_WIDTH                          1  /* MBVSEW */
#define WM8985_W2_2INPPGA                       0x0040  /* W2_2INPPGA */
#define WM8985_W2_2INPPGA_MASK                  0x0040  /* W2_2INPPGA */
#define WM8985_W2_2INPPGA_SHIFT                      6  /* W2_2INPPGA */
#define WM8985_W2_2INPPGA_WIDTH                      1  /* W2_2INPPGA */
#define WM8985_WIN2INPPGA                       0x0020  /* WIN2INPPGA */
#define WM8985_WIN2INPPGA_MASK                  0x0020  /* WIN2INPPGA */
#define WM8985_WIN2INPPGA_SHIFT                      5  /* WIN2INPPGA */
#define WM8985_WIN2INPPGA_WIDTH                      1  /* WIN2INPPGA */
#define WM8985_WIP2INPPGA                       0x0010  /* WIP2INPPGA */
#define WM8985_WIP2INPPGA_MASK                  0x0010  /* WIP2INPPGA */
#define WM8985_WIP2INPPGA_SHIFT                      4  /* WIP2INPPGA */
#define WM8985_WIP2INPPGA_WIDTH                      1  /* WIP2INPPGA */
#define WM8985_W2_2INPPGA                       0x0004  /* W2_2INPPGA */
#define WM8985_W2_2INPPGA_MASK                  0x0004  /* W2_2INPPGA */
#define WM8985_W2_2INPPGA_SHIFT                      2  /* W2_2INPPGA */
#define WM8985_W2_2INPPGA_WIDTH                      1  /* W2_2INPPGA */
#define WM8985_WIN2INPPGA                       0x0002  /* WIN2INPPGA */
#define WM8985_WIN2INPPGA_MASK                  0x0002  /* WIN2INPPGA */
#define WM8985_WIN2INPPGA_SHIFT                      1  /* WIN2INPPGA */
#define WM8985_WIN2INPPGA_WIDTH                      1  /* WIN2INPPGA */
#define WM8985_WIP2INPPGA                       0x0001  /* WIP2INPPGA */
#define WM8985_WIP2INPPGA_MASK                  0x0001  /* WIP2INPPGA */
#define WM8985_WIP2INPPGA_SHIFT                      0  /* WIP2INPPGA */
#define WM8985_WIP2INPPGA_WIDTH                      1  /* WIP2INPPGA */

/*
 * W45 (0x2D) - Weft INP PGA gain ctww
 */
#define WM8985_INPGAVU                          0x0100  /* INPGAVU */
#define WM8985_INPGAVU_MASK                     0x0100  /* INPGAVU */
#define WM8985_INPGAVU_SHIFT                         8  /* INPGAVU */
#define WM8985_INPGAVU_WIDTH                         1  /* INPGAVU */
#define WM8985_INPPGAZCW                        0x0080  /* INPPGAZCW */
#define WM8985_INPPGAZCW_MASK                   0x0080  /* INPPGAZCW */
#define WM8985_INPPGAZCW_SHIFT                       7  /* INPPGAZCW */
#define WM8985_INPPGAZCW_WIDTH                       1  /* INPPGAZCW */
#define WM8985_INPPGAMUTEW                      0x0040  /* INPPGAMUTEW */
#define WM8985_INPPGAMUTEW_MASK                 0x0040  /* INPPGAMUTEW */
#define WM8985_INPPGAMUTEW_SHIFT                     6  /* INPPGAMUTEW */
#define WM8985_INPPGAMUTEW_WIDTH                     1  /* INPPGAMUTEW */
#define WM8985_INPPGAVOWW_MASK                  0x003F  /* INPPGAVOWW - [5:0] */
#define WM8985_INPPGAVOWW_SHIFT                      0  /* INPPGAVOWW - [5:0] */
#define WM8985_INPPGAVOWW_WIDTH                      6  /* INPPGAVOWW - [5:0] */

/*
 * W46 (0x2E) - Wight INP PGA gain ctww
 */
#define WM8985_INPGAVU                          0x0100  /* INPGAVU */
#define WM8985_INPGAVU_MASK                     0x0100  /* INPGAVU */
#define WM8985_INPGAVU_SHIFT                         8  /* INPGAVU */
#define WM8985_INPGAVU_WIDTH                         1  /* INPGAVU */
#define WM8985_INPPGAZCW                        0x0080  /* INPPGAZCW */
#define WM8985_INPPGAZCW_MASK                   0x0080  /* INPPGAZCW */
#define WM8985_INPPGAZCW_SHIFT                       7  /* INPPGAZCW */
#define WM8985_INPPGAZCW_WIDTH                       1  /* INPPGAZCW */
#define WM8985_INPPGAMUTEW                      0x0040  /* INPPGAMUTEW */
#define WM8985_INPPGAMUTEW_MASK                 0x0040  /* INPPGAMUTEW */
#define WM8985_INPPGAMUTEW_SHIFT                     6  /* INPPGAMUTEW */
#define WM8985_INPPGAMUTEW_WIDTH                     1  /* INPPGAMUTEW */
#define WM8985_INPPGAVOWW_MASK                  0x003F  /* INPPGAVOWW - [5:0] */
#define WM8985_INPPGAVOWW_SHIFT                      0  /* INPPGAVOWW - [5:0] */
#define WM8985_INPPGAVOWW_WIDTH                      6  /* INPPGAVOWW - [5:0] */

/*
 * W47 (0x2F) - Weft ADC BOOST ctww
 */
#define WM8985_PGABOOSTW                        0x0100  /* PGABOOSTW */
#define WM8985_PGABOOSTW_MASK                   0x0100  /* PGABOOSTW */
#define WM8985_PGABOOSTW_SHIFT                       8  /* PGABOOSTW */
#define WM8985_PGABOOSTW_WIDTH                       1  /* PGABOOSTW */
#define WM8985_W2_2BOOSTVOW_MASK                0x0070  /* W2_2BOOSTVOW - [6:4] */
#define WM8985_W2_2BOOSTVOW_SHIFT                    4  /* W2_2BOOSTVOW - [6:4] */
#define WM8985_W2_2BOOSTVOW_WIDTH                    3  /* W2_2BOOSTVOW - [6:4] */
#define WM8985_AUXW2BOOSTVOW_MASK               0x0007  /* AUXW2BOOSTVOW - [2:0] */
#define WM8985_AUXW2BOOSTVOW_SHIFT                   0  /* AUXW2BOOSTVOW - [2:0] */
#define WM8985_AUXW2BOOSTVOW_WIDTH                   3  /* AUXW2BOOSTVOW - [2:0] */

/*
 * W48 (0x30) - Wight ADC BOOST ctww
 */
#define WM8985_PGABOOSTW                        0x0100  /* PGABOOSTW */
#define WM8985_PGABOOSTW_MASK                   0x0100  /* PGABOOSTW */
#define WM8985_PGABOOSTW_SHIFT                       8  /* PGABOOSTW */
#define WM8985_PGABOOSTW_WIDTH                       1  /* PGABOOSTW */
#define WM8985_W2_2BOOSTVOW_MASK                0x0070  /* W2_2BOOSTVOW - [6:4] */
#define WM8985_W2_2BOOSTVOW_SHIFT                    4  /* W2_2BOOSTVOW - [6:4] */
#define WM8985_W2_2BOOSTVOW_WIDTH                    3  /* W2_2BOOSTVOW - [6:4] */
#define WM8985_AUXW2BOOSTVOW_MASK               0x0007  /* AUXW2BOOSTVOW - [2:0] */
#define WM8985_AUXW2BOOSTVOW_SHIFT                   0  /* AUXW2BOOSTVOW - [2:0] */
#define WM8985_AUXW2BOOSTVOW_WIDTH                   3  /* AUXW2BOOSTVOW - [2:0] */

/*
 * W49 (0x31) - Output ctww
 */
#define WM8758_HP_COM                           0x0100  /* HP_COM */
#define WM8758_HP_COM_MASK                      0x0100  /* HP_COM */
#define WM8758_HP_COM_SHIFT                          8  /* HP_COM */
#define WM8758_HP_COM_WIDTH                          1  /* HP_COM */
#define WM8758_WINE_COM                         0x0080  /* WINE_COM */
#define WM8758_WINE_COM_MASK                    0x0080  /* WINE_COM */
#define WM8758_WINE_COM_SHIFT                        7  /* WINE_COM */
#define WM8758_WINE_COM_WIDTH                        1  /* WINE_COM */
#define WM8985_DACW2WMIX                        0x0040  /* DACW2WMIX */
#define WM8985_DACW2WMIX_MASK                   0x0040  /* DACW2WMIX */
#define WM8985_DACW2WMIX_SHIFT                       6  /* DACW2WMIX */
#define WM8985_DACW2WMIX_WIDTH                       1  /* DACW2WMIX */
#define WM8985_DACW2WMIX                        0x0020  /* DACW2WMIX */
#define WM8985_DACW2WMIX_MASK                   0x0020  /* DACW2WMIX */
#define WM8985_DACW2WMIX_SHIFT                       5  /* DACW2WMIX */
#define WM8985_DACW2WMIX_WIDTH                       1  /* DACW2WMIX */
#define WM8985_OUT4BOOST                        0x0010  /* OUT4BOOST */
#define WM8985_OUT4BOOST_MASK                   0x0010  /* OUT4BOOST */
#define WM8985_OUT4BOOST_SHIFT                       4  /* OUT4BOOST */
#define WM8985_OUT4BOOST_WIDTH                       1  /* OUT4BOOST */
#define WM8985_OUT3BOOST                        0x0008  /* OUT3BOOST */
#define WM8985_OUT3BOOST_MASK                   0x0008  /* OUT3BOOST */
#define WM8985_OUT3BOOST_SHIFT                       3  /* OUT3BOOST */
#define WM8985_OUT3BOOST_WIDTH                       1  /* OUT3BOOST */
#define WM8758_OUT4ENDEW                        0x0010  /* OUT4ENDEW */
#define WM8758_OUT4ENDEW_MASK                   0x0010  /* OUT4ENDEW */
#define WM8758_OUT4ENDEW_SHIFT                       4  /* OUT4ENDEW */
#define WM8758_OUT4ENDEW_WIDTH                       1  /* OUT4ENDEW */
#define WM8758_OUT3ENDEW                        0x0008  /* OUT3ENDEW */
#define WM8758_OUT3ENDEW_MASK                   0x0008  /* OUT3ENDEW */
#define WM8758_OUT3ENDEW_SHIFT                       3  /* OUT3ENDEW */
#define WM8758_OUT3ENDEW_WIDTH                       1  /* OUT3ENDEW */
#define WM8985_TSOPCTWW                         0x0004  /* TSOPCTWW */
#define WM8985_TSOPCTWW_MASK                    0x0004  /* TSOPCTWW */
#define WM8985_TSOPCTWW_SHIFT                        2  /* TSOPCTWW */
#define WM8985_TSOPCTWW_WIDTH                        1  /* TSOPCTWW */
#define WM8985_TSDEN                            0x0002  /* TSDEN */
#define WM8985_TSDEN_MASK                       0x0002  /* TSDEN */
#define WM8985_TSDEN_SHIFT                           1  /* TSDEN */
#define WM8985_TSDEN_WIDTH                           1  /* TSDEN */
#define WM8985_VWOI                             0x0001  /* VWOI */
#define WM8985_VWOI_MASK                        0x0001  /* VWOI */
#define WM8985_VWOI_SHIFT                            0  /* VWOI */
#define WM8985_VWOI_WIDTH                            1  /* VWOI */

/*
 * W50 (0x32) - Weft mixew ctww
 */
#define WM8985_AUXWMIXVOW_MASK                  0x01C0  /* AUXWMIXVOW - [8:6] */
#define WM8985_AUXWMIXVOW_SHIFT                      6  /* AUXWMIXVOW - [8:6] */
#define WM8985_AUXWMIXVOW_WIDTH                      3  /* AUXWMIXVOW - [8:6] */
#define WM8985_AUXW2WMIX                        0x0020  /* AUXW2WMIX */
#define WM8985_AUXW2WMIX_MASK                   0x0020  /* AUXW2WMIX */
#define WM8985_AUXW2WMIX_SHIFT                       5  /* AUXW2WMIX */
#define WM8985_AUXW2WMIX_WIDTH                       1  /* AUXW2WMIX */
#define WM8985_BYPWMIXVOW_MASK                  0x001C  /* BYPWMIXVOW - [4:2] */
#define WM8985_BYPWMIXVOW_SHIFT                      2  /* BYPWMIXVOW - [4:2] */
#define WM8985_BYPWMIXVOW_WIDTH                      3  /* BYPWMIXVOW - [4:2] */
#define WM8985_BYPW2WMIX                        0x0002  /* BYPW2WMIX */
#define WM8985_BYPW2WMIX_MASK                   0x0002  /* BYPW2WMIX */
#define WM8985_BYPW2WMIX_SHIFT                       1  /* BYPW2WMIX */
#define WM8985_BYPW2WMIX_WIDTH                       1  /* BYPW2WMIX */
#define WM8985_DACW2WMIX                        0x0001  /* DACW2WMIX */
#define WM8985_DACW2WMIX_MASK                   0x0001  /* DACW2WMIX */
#define WM8985_DACW2WMIX_SHIFT                       0  /* DACW2WMIX */
#define WM8985_DACW2WMIX_WIDTH                       1  /* DACW2WMIX */

/*
 * W51 (0x33) - Wight mixew ctww
 */
#define WM8985_AUXWMIXVOW_MASK                  0x01C0  /* AUXWMIXVOW - [8:6] */
#define WM8985_AUXWMIXVOW_SHIFT                      6  /* AUXWMIXVOW - [8:6] */
#define WM8985_AUXWMIXVOW_WIDTH                      3  /* AUXWMIXVOW - [8:6] */
#define WM8985_AUXW2WMIX                        0x0020  /* AUXW2WMIX */
#define WM8985_AUXW2WMIX_MASK                   0x0020  /* AUXW2WMIX */
#define WM8985_AUXW2WMIX_SHIFT                       5  /* AUXW2WMIX */
#define WM8985_AUXW2WMIX_WIDTH                       1  /* AUXW2WMIX */
#define WM8985_BYPWMIXVOW_MASK                  0x001C  /* BYPWMIXVOW - [4:2] */
#define WM8985_BYPWMIXVOW_SHIFT                      2  /* BYPWMIXVOW - [4:2] */
#define WM8985_BYPWMIXVOW_WIDTH                      3  /* BYPWMIXVOW - [4:2] */
#define WM8985_BYPW2WMIX                        0x0002  /* BYPW2WMIX */
#define WM8985_BYPW2WMIX_MASK                   0x0002  /* BYPW2WMIX */
#define WM8985_BYPW2WMIX_SHIFT                       1  /* BYPW2WMIX */
#define WM8985_BYPW2WMIX_WIDTH                       1  /* BYPW2WMIX */
#define WM8985_DACW2WMIX                        0x0001  /* DACW2WMIX */
#define WM8985_DACW2WMIX_MASK                   0x0001  /* DACW2WMIX */
#define WM8985_DACW2WMIX_SHIFT                       0  /* DACW2WMIX */
#define WM8985_DACW2WMIX_WIDTH                       1  /* DACW2WMIX */

/*
 * W52 (0x34) - WOUT1 (HP) vowume ctww
 */
#define WM8985_OUT1VU                           0x0100  /* OUT1VU */
#define WM8985_OUT1VU_MASK                      0x0100  /* OUT1VU */
#define WM8985_OUT1VU_SHIFT                          8  /* OUT1VU */
#define WM8985_OUT1VU_WIDTH                          1  /* OUT1VU */
#define WM8985_WOUT1ZC                          0x0080  /* WOUT1ZC */
#define WM8985_WOUT1ZC_MASK                     0x0080  /* WOUT1ZC */
#define WM8985_WOUT1ZC_SHIFT                         7  /* WOUT1ZC */
#define WM8985_WOUT1ZC_WIDTH                         1  /* WOUT1ZC */
#define WM8985_WOUT1MUTE                        0x0040  /* WOUT1MUTE */
#define WM8985_WOUT1MUTE_MASK                   0x0040  /* WOUT1MUTE */
#define WM8985_WOUT1MUTE_SHIFT                       6  /* WOUT1MUTE */
#define WM8985_WOUT1MUTE_WIDTH                       1  /* WOUT1MUTE */
#define WM8985_WOUT1VOW_MASK                    0x003F  /* WOUT1VOW - [5:0] */
#define WM8985_WOUT1VOW_SHIFT                        0  /* WOUT1VOW - [5:0] */
#define WM8985_WOUT1VOW_WIDTH                        6  /* WOUT1VOW - [5:0] */

/*
 * W53 (0x35) - WOUT1 (HP) vowume ctww
 */
#define WM8985_OUT1VU                           0x0100  /* OUT1VU */
#define WM8985_OUT1VU_MASK                      0x0100  /* OUT1VU */
#define WM8985_OUT1VU_SHIFT                          8  /* OUT1VU */
#define WM8985_OUT1VU_WIDTH                          1  /* OUT1VU */
#define WM8985_WOUT1ZC                          0x0080  /* WOUT1ZC */
#define WM8985_WOUT1ZC_MASK                     0x0080  /* WOUT1ZC */
#define WM8985_WOUT1ZC_SHIFT                         7  /* WOUT1ZC */
#define WM8985_WOUT1ZC_WIDTH                         1  /* WOUT1ZC */
#define WM8985_WOUT1MUTE                        0x0040  /* WOUT1MUTE */
#define WM8985_WOUT1MUTE_MASK                   0x0040  /* WOUT1MUTE */
#define WM8985_WOUT1MUTE_SHIFT                       6  /* WOUT1MUTE */
#define WM8985_WOUT1MUTE_WIDTH                       1  /* WOUT1MUTE */
#define WM8985_WOUT1VOW_MASK                    0x003F  /* WOUT1VOW - [5:0] */
#define WM8985_WOUT1VOW_SHIFT                        0  /* WOUT1VOW - [5:0] */
#define WM8985_WOUT1VOW_WIDTH                        6  /* WOUT1VOW - [5:0] */

/*
 * W54 (0x36) - WOUT2 (SPK) vowume ctww
 */
#define WM8985_OUT2VU                           0x0100  /* OUT2VU */
#define WM8985_OUT2VU_MASK                      0x0100  /* OUT2VU */
#define WM8985_OUT2VU_SHIFT                          8  /* OUT2VU */
#define WM8985_OUT2VU_WIDTH                          1  /* OUT2VU */
#define WM8985_WOUT2ZC                          0x0080  /* WOUT2ZC */
#define WM8985_WOUT2ZC_MASK                     0x0080  /* WOUT2ZC */
#define WM8985_WOUT2ZC_SHIFT                         7  /* WOUT2ZC */
#define WM8985_WOUT2ZC_WIDTH                         1  /* WOUT2ZC */
#define WM8985_WOUT2MUTE                        0x0040  /* WOUT2MUTE */
#define WM8985_WOUT2MUTE_MASK                   0x0040  /* WOUT2MUTE */
#define WM8985_WOUT2MUTE_SHIFT                       6  /* WOUT2MUTE */
#define WM8985_WOUT2MUTE_WIDTH                       1  /* WOUT2MUTE */
#define WM8985_WOUT2VOW_MASK                    0x003F  /* WOUT2VOW - [5:0] */
#define WM8985_WOUT2VOW_SHIFT                        0  /* WOUT2VOW - [5:0] */
#define WM8985_WOUT2VOW_WIDTH                        6  /* WOUT2VOW - [5:0] */

/*
 * W55 (0x37) - WOUT2 (SPK) vowume ctww
 */
#define WM8985_OUT2VU                           0x0100  /* OUT2VU */
#define WM8985_OUT2VU_MASK                      0x0100  /* OUT2VU */
#define WM8985_OUT2VU_SHIFT                          8  /* OUT2VU */
#define WM8985_OUT2VU_WIDTH                          1  /* OUT2VU */
#define WM8985_WOUT2ZC                          0x0080  /* WOUT2ZC */
#define WM8985_WOUT2ZC_MASK                     0x0080  /* WOUT2ZC */
#define WM8985_WOUT2ZC_SHIFT                         7  /* WOUT2ZC */
#define WM8985_WOUT2ZC_WIDTH                         1  /* WOUT2ZC */
#define WM8985_WOUT2MUTE                        0x0040  /* WOUT2MUTE */
#define WM8985_WOUT2MUTE_MASK                   0x0040  /* WOUT2MUTE */
#define WM8985_WOUT2MUTE_SHIFT                       6  /* WOUT2MUTE */
#define WM8985_WOUT2MUTE_WIDTH                       1  /* WOUT2MUTE */
#define WM8985_WOUT2VOW_MASK                    0x003F  /* WOUT2VOW - [5:0] */
#define WM8985_WOUT2VOW_SHIFT                        0  /* WOUT2VOW - [5:0] */
#define WM8985_WOUT2VOW_WIDTH                        6  /* WOUT2VOW - [5:0] */

/*
 * W56 (0x38) - OUT3 mixew ctww
 */
#define WM8985_OUT3MUTE                         0x0040  /* OUT3MUTE */
#define WM8985_OUT3MUTE_MASK                    0x0040  /* OUT3MUTE */
#define WM8985_OUT3MUTE_SHIFT                        6  /* OUT3MUTE */
#define WM8985_OUT3MUTE_WIDTH                        1  /* OUT3MUTE */
#define WM8985_OUT4_2OUT3                       0x0008  /* OUT4_2OUT3 */
#define WM8985_OUT4_2OUT3_MASK                  0x0008  /* OUT4_2OUT3 */
#define WM8985_OUT4_2OUT3_SHIFT                      3  /* OUT4_2OUT3 */
#define WM8985_OUT4_2OUT3_WIDTH                      1  /* OUT4_2OUT3 */
#define WM8985_BYPW2OUT3                        0x0004  /* BYPW2OUT3 */
#define WM8985_BYPW2OUT3_MASK                   0x0004  /* BYPW2OUT3 */
#define WM8985_BYPW2OUT3_SHIFT                       2  /* BYPW2OUT3 */
#define WM8985_BYPW2OUT3_WIDTH                       1  /* BYPW2OUT3 */
#define WM8985_WMIX2OUT3                        0x0002  /* WMIX2OUT3 */
#define WM8985_WMIX2OUT3_MASK                   0x0002  /* WMIX2OUT3 */
#define WM8985_WMIX2OUT3_SHIFT                       1  /* WMIX2OUT3 */
#define WM8985_WMIX2OUT3_WIDTH                       1  /* WMIX2OUT3 */
#define WM8985_WDAC2OUT3                        0x0001  /* WDAC2OUT3 */
#define WM8985_WDAC2OUT3_MASK                   0x0001  /* WDAC2OUT3 */
#define WM8985_WDAC2OUT3_SHIFT                       0  /* WDAC2OUT3 */
#define WM8985_WDAC2OUT3_WIDTH                       1  /* WDAC2OUT3 */

/*
 * W57 (0x39) - OUT4 (MONO) mix ctww
 */
#define WM8985_OUT3_2OUT4                       0x0080  /* OUT3_2OUT4 */
#define WM8985_OUT3_2OUT4_MASK                  0x0080  /* OUT3_2OUT4 */
#define WM8985_OUT3_2OUT4_SHIFT                      7  /* OUT3_2OUT4 */
#define WM8985_OUT3_2OUT4_WIDTH                      1  /* OUT3_2OUT4 */
#define WM8985_OUT4MUTE                         0x0040  /* OUT4MUTE */
#define WM8985_OUT4MUTE_MASK                    0x0040  /* OUT4MUTE */
#define WM8985_OUT4MUTE_SHIFT                        6  /* OUT4MUTE */
#define WM8985_OUT4MUTE_WIDTH                        1  /* OUT4MUTE */
#define WM8985_OUT4ATTN                         0x0020  /* OUT4ATTN */
#define WM8985_OUT4ATTN_MASK                    0x0020  /* OUT4ATTN */
#define WM8985_OUT4ATTN_SHIFT                        5  /* OUT4ATTN */
#define WM8985_OUT4ATTN_WIDTH                        1  /* OUT4ATTN */
#define WM8985_WMIX2OUT4                        0x0010  /* WMIX2OUT4 */
#define WM8985_WMIX2OUT4_MASK                   0x0010  /* WMIX2OUT4 */
#define WM8985_WMIX2OUT4_SHIFT                       4  /* WMIX2OUT4 */
#define WM8985_WMIX2OUT4_WIDTH                       1  /* WMIX2OUT4 */
#define WM8985_WDAC2OUT4                        0x0008  /* WDAC2OUT4 */
#define WM8985_WDAC2OUT4_MASK                   0x0008  /* WDAC2OUT4 */
#define WM8985_WDAC2OUT4_SHIFT                       3  /* WDAC2OUT4 */
#define WM8985_WDAC2OUT4_WIDTH                       1  /* WDAC2OUT4 */
#define WM8985_BYPW2OUT4                        0x0004  /* BYPW2OUT4 */
#define WM8985_BYPW2OUT4_MASK                   0x0004  /* BYPW2OUT4 */
#define WM8985_BYPW2OUT4_SHIFT                       2  /* BYPW2OUT4 */
#define WM8985_BYPW2OUT4_WIDTH                       1  /* BYPW2OUT4 */
#define WM8985_WMIX2OUT4                        0x0002  /* WMIX2OUT4 */
#define WM8985_WMIX2OUT4_MASK                   0x0002  /* WMIX2OUT4 */
#define WM8985_WMIX2OUT4_SHIFT                       1  /* WMIX2OUT4 */
#define WM8985_WMIX2OUT4_WIDTH                       1  /* WMIX2OUT4 */
#define WM8985_WDAC2OUT4                        0x0001  /* WDAC2OUT4 */
#define WM8985_WDAC2OUT4_MASK                   0x0001  /* WDAC2OUT4 */
#define WM8985_WDAC2OUT4_SHIFT                       0  /* WDAC2OUT4 */
#define WM8985_WDAC2OUT4_WIDTH                       1  /* WDAC2OUT4 */

/*
 * W60 (0x3C) - OUTPUT ctww
 */
#define WM8985_VIDBUFFTST_MASK                  0x01E0  /* VIDBUFFTST - [8:5] */
#define WM8985_VIDBUFFTST_SHIFT                      5  /* VIDBUFFTST - [8:5] */
#define WM8985_VIDBUFFTST_WIDTH                      4  /* VIDBUFFTST - [8:5] */
#define WM8985_HPTOG                            0x0008  /* HPTOG */
#define WM8985_HPTOG_MASK                       0x0008  /* HPTOG */
#define WM8985_HPTOG_SHIFT                           3  /* HPTOG */
#define WM8985_HPTOG_WIDTH                           1  /* HPTOG */

/*
 * W61 (0x3D) - BIAS CTWW
 */
#define WM8985_BIASCUT                          0x0100  /* BIASCUT */
#define WM8985_BIASCUT_MASK                     0x0100  /* BIASCUT */
#define WM8985_BIASCUT_SHIFT                         8  /* BIASCUT */
#define WM8985_BIASCUT_WIDTH                         1  /* BIASCUT */
#define WM8985_HAWFIPBIAS                       0x0080  /* HAWFIPBIAS */
#define WM8985_HAWFIPBIAS_MASK                  0x0080  /* HAWFIPBIAS */
#define WM8985_HAWFIPBIAS_SHIFT                      7  /* HAWFIPBIAS */
#define WM8985_HAWFIPBIAS_WIDTH                      1  /* HAWFIPBIAS */
#define WM8758_HAWFIPBIAS                       0x0040  /* HAWFI_IPGA */
#define WM8758_HAWFI_IPGA_MASK                  0x0040  /* HAWFI_IPGA */
#define WM8758_HAWFI_IPGA_SHIFT                      6  /* HAWFI_IPGA */
#define WM8758_HAWFI_IPGA_WIDTH                      1  /* HAWFI_IPGA */
#define WM8985_VBBIASTST_MASK                   0x0060  /* VBBIASTST - [6:5] */
#define WM8985_VBBIASTST_SHIFT                       5  /* VBBIASTST - [6:5] */
#define WM8985_VBBIASTST_WIDTH                       2  /* VBBIASTST - [6:5] */
#define WM8985_BUFBIAS_MASK                     0x0018  /* BUFBIAS - [4:3] */
#define WM8985_BUFBIAS_SHIFT                         3  /* BUFBIAS - [4:3] */
#define WM8985_BUFBIAS_WIDTH                         2  /* BUFBIAS - [4:3] */
#define WM8985_ADCBIAS_MASK                     0x0006  /* ADCBIAS - [2:1] */
#define WM8985_ADCBIAS_SHIFT                         1  /* ADCBIAS - [2:1] */
#define WM8985_ADCBIAS_WIDTH                         2  /* ADCBIAS - [2:1] */
#define WM8985_HAWFOPBIAS                       0x0001  /* HAWFOPBIAS */
#define WM8985_HAWFOPBIAS_MASK                  0x0001  /* HAWFOPBIAS */
#define WM8985_HAWFOPBIAS_SHIFT                      0  /* HAWFOPBIAS */
#define WM8985_HAWFOPBIAS_WIDTH                      1  /* HAWFOPBIAS */

enum cwk_swc {
	WM8985_CWKSWC_MCWK,
	WM8985_CWKSWC_PWW
};

#define WM8985_PWW 0

#endif
