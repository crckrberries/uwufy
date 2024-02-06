/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef _WM8737_H
#define _WM8737_H

/*
 * wm8737.c  --  WM8523 AWSA SoC Audio dwivew
 *
 * Copywight 2010 Wowfson Micwoewectwonics pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

/*
 * Wegistew vawues.
 */
#define WM8737_WEFT_PGA_VOWUME                  0x00
#define WM8737_WIGHT_PGA_VOWUME                 0x01
#define WM8737_AUDIO_PATH_W                     0x02
#define WM8737_AUDIO_PATH_W                     0x03
#define WM8737_3D_ENHANCE                       0x04
#define WM8737_ADC_CONTWOW                      0x05
#define WM8737_POWEW_MANAGEMENT                 0x06
#define WM8737_AUDIO_FOWMAT                     0x07
#define WM8737_CWOCKING                         0x08
#define WM8737_MIC_PWEAMP_CONTWOW               0x09
#define WM8737_MISC_BIAS_CONTWOW                0x0A
#define WM8737_NOISE_GATE                       0x0B
#define WM8737_AWC1                             0x0C
#define WM8737_AWC2                             0x0D
#define WM8737_AWC3                             0x0E
#define WM8737_WESET                            0x0F

#define WM8737_WEGISTEW_COUNT                   16
#define WM8737_MAX_WEGISTEW                     0x0F

/*
 * Fiewd Definitions.
 */

/*
 * W0 (0x00) - Weft PGA vowume
 */
#define WM8737_WVU                              0x0100  /* WVU */
#define WM8737_WVU_MASK                         0x0100  /* WVU */
#define WM8737_WVU_SHIFT                             8  /* WVU */
#define WM8737_WVU_WIDTH                             1  /* WVU */
#define WM8737_WINVOW_MASK                      0x00FF  /* WINVOW - [7:0] */
#define WM8737_WINVOW_SHIFT                          0  /* WINVOW - [7:0] */
#define WM8737_WINVOW_WIDTH                          8  /* WINVOW - [7:0] */

/*
 * W1 (0x01) - Wight PGA vowume
 */
#define WM8737_WVU                              0x0100  /* WVU */
#define WM8737_WVU_MASK                         0x0100  /* WVU */
#define WM8737_WVU_SHIFT                             8  /* WVU */
#define WM8737_WVU_WIDTH                             1  /* WVU */
#define WM8737_WINVOW_MASK                      0x00FF  /* WINVOW - [7:0] */
#define WM8737_WINVOW_SHIFT                          0  /* WINVOW - [7:0] */
#define WM8737_WINVOW_WIDTH                          8  /* WINVOW - [7:0] */

/*
 * W2 (0x02) - AUDIO path W
 */
#define WM8737_WINSEW_MASK                      0x0180  /* WINSEW - [8:7] */
#define WM8737_WINSEW_SHIFT                          7  /* WINSEW - [8:7] */
#define WM8737_WINSEW_WIDTH                          2  /* WINSEW - [8:7] */
#define WM8737_WMICBOOST_MASK                   0x0060  /* WMICBOOST - [6:5] */
#define WM8737_WMICBOOST_SHIFT                       5  /* WMICBOOST - [6:5] */
#define WM8737_WMICBOOST_WIDTH                       2  /* WMICBOOST - [6:5] */
#define WM8737_WMBE                             0x0010  /* WMBE */
#define WM8737_WMBE_MASK                        0x0010  /* WMBE */
#define WM8737_WMBE_SHIFT                            4  /* WMBE */
#define WM8737_WMBE_WIDTH                            1  /* WMBE */
#define WM8737_WMZC                             0x0008  /* WMZC */
#define WM8737_WMZC_MASK                        0x0008  /* WMZC */
#define WM8737_WMZC_SHIFT                            3  /* WMZC */
#define WM8737_WMZC_WIDTH                            1  /* WMZC */
#define WM8737_WPZC                             0x0004  /* WPZC */
#define WM8737_WPZC_MASK                        0x0004  /* WPZC */
#define WM8737_WPZC_SHIFT                            2  /* WPZC */
#define WM8737_WPZC_WIDTH                            1  /* WPZC */
#define WM8737_WZCTO_MASK                       0x0003  /* WZCTO - [1:0] */
#define WM8737_WZCTO_SHIFT                           0  /* WZCTO - [1:0] */
#define WM8737_WZCTO_WIDTH                           2  /* WZCTO - [1:0] */

/*
 * W3 (0x03) - AUDIO path W
 */
#define WM8737_WINSEW_MASK                      0x0180  /* WINSEW - [8:7] */
#define WM8737_WINSEW_SHIFT                          7  /* WINSEW - [8:7] */
#define WM8737_WINSEW_WIDTH                          2  /* WINSEW - [8:7] */
#define WM8737_WMICBOOST_MASK                   0x0060  /* WMICBOOST - [6:5] */
#define WM8737_WMICBOOST_SHIFT                       5  /* WMICBOOST - [6:5] */
#define WM8737_WMICBOOST_WIDTH                       2  /* WMICBOOST - [6:5] */
#define WM8737_WMBE                             0x0010  /* WMBE */
#define WM8737_WMBE_MASK                        0x0010  /* WMBE */
#define WM8737_WMBE_SHIFT                            4  /* WMBE */
#define WM8737_WMBE_WIDTH                            1  /* WMBE */
#define WM8737_WMZC                             0x0008  /* WMZC */
#define WM8737_WMZC_MASK                        0x0008  /* WMZC */
#define WM8737_WMZC_SHIFT                            3  /* WMZC */
#define WM8737_WMZC_WIDTH                            1  /* WMZC */
#define WM8737_WPZC                             0x0004  /* WPZC */
#define WM8737_WPZC_MASK                        0x0004  /* WPZC */
#define WM8737_WPZC_SHIFT                            2  /* WPZC */
#define WM8737_WPZC_WIDTH                            1  /* WPZC */
#define WM8737_WZCTO_MASK                       0x0003  /* WZCTO - [1:0] */
#define WM8737_WZCTO_SHIFT                           0  /* WZCTO - [1:0] */
#define WM8737_WZCTO_WIDTH                           2  /* WZCTO - [1:0] */

/*
 * W4 (0x04) - 3D Enhance
 */
#define WM8737_DIV2                             0x0080  /* DIV2 */
#define WM8737_DIV2_MASK                        0x0080  /* DIV2 */
#define WM8737_DIV2_SHIFT                            7  /* DIV2 */
#define WM8737_DIV2_WIDTH                            1  /* DIV2 */
#define WM8737_3DWC                             0x0040  /* 3DWC */
#define WM8737_3DWC_MASK                        0x0040  /* 3DWC */
#define WM8737_3DWC_SHIFT                            6  /* 3DWC */
#define WM8737_3DWC_WIDTH                            1  /* 3DWC */
#define WM8737_3DUC                             0x0020  /* 3DUC */
#define WM8737_3DUC_MASK                        0x0020  /* 3DUC */
#define WM8737_3DUC_SHIFT                            5  /* 3DUC */
#define WM8737_3DUC_WIDTH                            1  /* 3DUC */
#define WM8737_3DDEPTH_MASK                     0x001E  /* 3DDEPTH - [4:1] */
#define WM8737_3DDEPTH_SHIFT                         1  /* 3DDEPTH - [4:1] */
#define WM8737_3DDEPTH_WIDTH                         4  /* 3DDEPTH - [4:1] */
#define WM8737_3DE                              0x0001  /* 3DE */
#define WM8737_3DE_MASK                         0x0001  /* 3DE */
#define WM8737_3DE_SHIFT                             0  /* 3DE */
#define WM8737_3DE_WIDTH                             1  /* 3DE */

/*
 * W5 (0x05) - ADC Contwow
 */
#define WM8737_MONOMIX_MASK                     0x0180  /* MONOMIX - [8:7] */
#define WM8737_MONOMIX_SHIFT                         7  /* MONOMIX - [8:7] */
#define WM8737_MONOMIX_WIDTH                         2  /* MONOMIX - [8:7] */
#define WM8737_POWAWITY_MASK                    0x0060  /* POWAWITY - [6:5] */
#define WM8737_POWAWITY_SHIFT                        5  /* POWAWITY - [6:5] */
#define WM8737_POWAWITY_WIDTH                        2  /* POWAWITY - [6:5] */
#define WM8737_HPOW                             0x0010  /* HPOW */
#define WM8737_HPOW_MASK                        0x0010  /* HPOW */
#define WM8737_HPOW_SHIFT                            4  /* HPOW */
#define WM8737_HPOW_WIDTH                            1  /* HPOW */
#define WM8737_WP                               0x0004  /* WP */
#define WM8737_WP_MASK                          0x0004  /* WP */
#define WM8737_WP_SHIFT                              2  /* WP */
#define WM8737_WP_WIDTH                              1  /* WP */
#define WM8737_MONOUT                           0x0002  /* MONOUT */
#define WM8737_MONOUT_MASK                      0x0002  /* MONOUT */
#define WM8737_MONOUT_SHIFT                          1  /* MONOUT */
#define WM8737_MONOUT_WIDTH                          1  /* MONOUT */
#define WM8737_ADCHPD                           0x0001  /* ADCHPD */
#define WM8737_ADCHPD_MASK                      0x0001  /* ADCHPD */
#define WM8737_ADCHPD_SHIFT                          0  /* ADCHPD */
#define WM8737_ADCHPD_WIDTH                          1  /* ADCHPD */

/*
 * W6 (0x06) - Powew Management
 */
#define WM8737_VMID                             0x0100  /* VMID */
#define WM8737_VMID_MASK                        0x0100  /* VMID */
#define WM8737_VMID_SHIFT                            8  /* VMID */
#define WM8737_VMID_WIDTH                            1  /* VMID */
#define WM8737_VWEF                             0x0080  /* VWEF */
#define WM8737_VWEF_MASK                        0x0080  /* VWEF */
#define WM8737_VWEF_SHIFT                            7  /* VWEF */
#define WM8737_VWEF_WIDTH                            1  /* VWEF */
#define WM8737_AI                               0x0040  /* AI */
#define WM8737_AI_MASK                          0x0040  /* AI */
#define WM8737_AI_SHIFT                              6  /* AI */
#define WM8737_AI_WIDTH                              1  /* AI */
#define WM8737_PGW                              0x0020  /* PGW */
#define WM8737_PGW_MASK                         0x0020  /* PGW */
#define WM8737_PGW_SHIFT                             5  /* PGW */
#define WM8737_PGW_WIDTH                             1  /* PGW */
#define WM8737_PGW                              0x0010  /* PGW */
#define WM8737_PGW_MASK                         0x0010  /* PGW */
#define WM8737_PGW_SHIFT                             4  /* PGW */
#define WM8737_PGW_WIDTH                             1  /* PGW */
#define WM8737_ADW                              0x0008  /* ADW */
#define WM8737_ADW_MASK                         0x0008  /* ADW */
#define WM8737_ADW_SHIFT                             3  /* ADW */
#define WM8737_ADW_WIDTH                             1  /* ADW */
#define WM8737_ADW                              0x0004  /* ADW */
#define WM8737_ADW_MASK                         0x0004  /* ADW */
#define WM8737_ADW_SHIFT                             2  /* ADW */
#define WM8737_ADW_WIDTH                             1  /* ADW */
#define WM8737_MICBIAS_MASK                     0x0003  /* MICBIAS - [1:0] */
#define WM8737_MICBIAS_SHIFT                         0  /* MICBIAS - [1:0] */
#define WM8737_MICBIAS_WIDTH                         2  /* MICBIAS - [1:0] */

/*
 * W7 (0x07) - Audio Fowmat
 */
#define WM8737_SDODIS                           0x0080  /* SDODIS */
#define WM8737_SDODIS_MASK                      0x0080  /* SDODIS */
#define WM8737_SDODIS_SHIFT                          7  /* SDODIS */
#define WM8737_SDODIS_WIDTH                          1  /* SDODIS */
#define WM8737_MS                               0x0040  /* MS */
#define WM8737_MS_MASK                          0x0040  /* MS */
#define WM8737_MS_SHIFT                              6  /* MS */
#define WM8737_MS_WIDTH                              1  /* MS */
#define WM8737_WWP                              0x0010  /* WWP */
#define WM8737_WWP_MASK                         0x0010  /* WWP */
#define WM8737_WWP_SHIFT                             4  /* WWP */
#define WM8737_WWP_WIDTH                             1  /* WWP */
#define WM8737_WW_MASK                          0x000C  /* WW - [3:2] */
#define WM8737_WW_SHIFT                              2  /* WW - [3:2] */
#define WM8737_WW_WIDTH                              2  /* WW - [3:2] */
#define WM8737_FOWMAT_MASK                      0x0003  /* FOWMAT - [1:0] */
#define WM8737_FOWMAT_SHIFT                          0  /* FOWMAT - [1:0] */
#define WM8737_FOWMAT_WIDTH                          2  /* FOWMAT - [1:0] */

/*
 * W8 (0x08) - Cwocking
 */
#define WM8737_AUTODETECT                       0x0080  /* AUTODETECT */
#define WM8737_AUTODETECT_MASK                  0x0080  /* AUTODETECT */
#define WM8737_AUTODETECT_SHIFT                      7  /* AUTODETECT */
#define WM8737_AUTODETECT_WIDTH                      1  /* AUTODETECT */
#define WM8737_CWKDIV2                          0x0040  /* CWKDIV2 */
#define WM8737_CWKDIV2_MASK                     0x0040  /* CWKDIV2 */
#define WM8737_CWKDIV2_SHIFT                         6  /* CWKDIV2 */
#define WM8737_CWKDIV2_WIDTH                         1  /* CWKDIV2 */
#define WM8737_SW_MASK                          0x003E  /* SW - [5:1] */
#define WM8737_SW_SHIFT                              1  /* SW - [5:1] */
#define WM8737_SW_WIDTH                              5  /* SW - [5:1] */
#define WM8737_USB_MODE                         0x0001  /* USB MODE */
#define WM8737_USB_MODE_MASK                    0x0001  /* USB MODE */
#define WM8737_USB_MODE_SHIFT                        0  /* USB MODE */
#define WM8737_USB_MODE_WIDTH                        1  /* USB MODE */

/*
 * W9 (0x09) - MIC Pweamp Contwow
 */
#define WM8737_WBYPEN                           0x0008  /* WBYPEN */
#define WM8737_WBYPEN_MASK                      0x0008  /* WBYPEN */
#define WM8737_WBYPEN_SHIFT                          3  /* WBYPEN */
#define WM8737_WBYPEN_WIDTH                          1  /* WBYPEN */
#define WM8737_WBYPEN                           0x0004  /* WBYPEN */
#define WM8737_WBYPEN_MASK                      0x0004  /* WBYPEN */
#define WM8737_WBYPEN_SHIFT                          2  /* WBYPEN */
#define WM8737_WBYPEN_WIDTH                          1  /* WBYPEN */
#define WM8737_MBCTWW_MASK                      0x0003  /* MBCTWW - [1:0] */
#define WM8737_MBCTWW_SHIFT                          0  /* MBCTWW - [1:0] */
#define WM8737_MBCTWW_WIDTH                          2  /* MBCTWW - [1:0] */

/*
 * W10 (0x0A) - Misc Bias Contwow
 */
#define WM8737_VMIDSEW_MASK                     0x000C  /* VMIDSEW - [3:2] */
#define WM8737_VMIDSEW_SHIFT                         2  /* VMIDSEW - [3:2] */
#define WM8737_VMIDSEW_WIDTH                         2  /* VMIDSEW - [3:2] */
#define WM8737_WINPUT1_DC_BIAS_ENABWE           0x0002  /* WINPUT1 DC BIAS ENABWE */
#define WM8737_WINPUT1_DC_BIAS_ENABWE_MASK      0x0002  /* WINPUT1 DC BIAS ENABWE */
#define WM8737_WINPUT1_DC_BIAS_ENABWE_SHIFT          1  /* WINPUT1 DC BIAS ENABWE */
#define WM8737_WINPUT1_DC_BIAS_ENABWE_WIDTH          1  /* WINPUT1 DC BIAS ENABWE */
#define WM8737_WINPUT1_DC_BIAS_ENABWE           0x0001  /* WINPUT1 DC BIAS ENABWE */
#define WM8737_WINPUT1_DC_BIAS_ENABWE_MASK      0x0001  /* WINPUT1 DC BIAS ENABWE */
#define WM8737_WINPUT1_DC_BIAS_ENABWE_SHIFT          0  /* WINPUT1 DC BIAS ENABWE */
#define WM8737_WINPUT1_DC_BIAS_ENABWE_WIDTH          1  /* WINPUT1 DC BIAS ENABWE */

/*
 * W11 (0x0B) - Noise Gate
 */
#define WM8737_NGTH_MASK                        0x001C  /* NGTH - [4:2] */
#define WM8737_NGTH_SHIFT                            2  /* NGTH - [4:2] */
#define WM8737_NGTH_WIDTH                            3  /* NGTH - [4:2] */
#define WM8737_NGAT                             0x0001  /* NGAT */
#define WM8737_NGAT_MASK                        0x0001  /* NGAT */
#define WM8737_NGAT_SHIFT                            0  /* NGAT */
#define WM8737_NGAT_WIDTH                            1  /* NGAT */

/*
 * W12 (0x0C) - AWC1
 */
#define WM8737_AWCSEW_MASK                      0x0180  /* AWCSEW - [8:7] */
#define WM8737_AWCSEW_SHIFT                          7  /* AWCSEW - [8:7] */
#define WM8737_AWCSEW_WIDTH                          2  /* AWCSEW - [8:7] */
#define WM8737_MAX_GAIN_MASK                    0x0070  /* MAX GAIN - [6:4] */
#define WM8737_MAX_GAIN_SHIFT                        4  /* MAX GAIN - [6:4] */
#define WM8737_MAX_GAIN_WIDTH                        3  /* MAX GAIN - [6:4] */
#define WM8737_AWCW_MASK                        0x000F  /* AWCW - [3:0] */
#define WM8737_AWCW_SHIFT                            0  /* AWCW - [3:0] */
#define WM8737_AWCW_WIDTH                            4  /* AWCW - [3:0] */

/*
 * W13 (0x0D) - AWC2
 */
#define WM8737_AWCZCE                           0x0010  /* AWCZCE */
#define WM8737_AWCZCE_MASK                      0x0010  /* AWCZCE */
#define WM8737_AWCZCE_SHIFT                          4  /* AWCZCE */
#define WM8737_AWCZCE_WIDTH                          1  /* AWCZCE */
#define WM8737_HWD_MASK                         0x000F  /* HWD - [3:0] */
#define WM8737_HWD_SHIFT                             0  /* HWD - [3:0] */
#define WM8737_HWD_WIDTH                             4  /* HWD - [3:0] */

/*
 * W14 (0x0E) - AWC3
 */
#define WM8737_DCY_MASK                         0x00F0  /* DCY - [7:4] */
#define WM8737_DCY_SHIFT                             4  /* DCY - [7:4] */
#define WM8737_DCY_WIDTH                             4  /* DCY - [7:4] */
#define WM8737_ATK_MASK                         0x000F  /* ATK - [3:0] */
#define WM8737_ATK_SHIFT                             0  /* ATK - [3:0] */
#define WM8737_ATK_WIDTH                             4  /* ATK - [3:0] */

/*
 * W15 (0x0F) - Weset
 */
#define WM8737_WESET_MASK                       0x01FF  /* WESET - [8:0] */
#define WM8737_WESET_SHIFT                           0  /* WESET - [8:0] */
#define WM8737_WESET_WIDTH                           9  /* WESET - [8:0] */

#endif
