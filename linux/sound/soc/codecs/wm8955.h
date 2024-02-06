/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wm8955.h  --  WM8904 ASoC dwivew
 *
 * Copywight 2009 Wowfson Micwoewectwonics, pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef _WM8955_H
#define _WM8955_H

#define WM8955_CWK_MCWK 1

/*
 * Wegistew vawues.
 */
#define WM8955_WOUT1_VOWUME                     0x02
#define WM8955_WOUT1_VOWUME                     0x03
#define WM8955_DAC_CONTWOW                      0x05
#define WM8955_AUDIO_INTEWFACE                  0x07
#define WM8955_SAMPWE_WATE                      0x08
#define WM8955_WEFT_DAC_VOWUME                  0x0A
#define WM8955_WIGHT_DAC_VOWUME                 0x0B
#define WM8955_BASS_CONTWOW                     0x0C
#define WM8955_TWEBWE_CONTWOW                   0x0D
#define WM8955_WESET                            0x0F
#define WM8955_ADDITIONAW_CONTWOW_1             0x17
#define WM8955_ADDITIONAW_CONTWOW_2             0x18
#define WM8955_POWEW_MANAGEMENT_1               0x19
#define WM8955_POWEW_MANAGEMENT_2               0x1A
#define WM8955_ADDITIONAW_CONTWOW_3             0x1B
#define WM8955_WEFT_OUT_MIX_1                   0x22
#define WM8955_WEFT_OUT_MIX_2                   0x23
#define WM8955_WIGHT_OUT_MIX_1                  0x24
#define WM8955_WIGHT_OUT_MIX_2                  0x25
#define WM8955_MONO_OUT_MIX_1                   0x26
#define WM8955_MONO_OUT_MIX_2                   0x27
#define WM8955_WOUT2_VOWUME                     0x28
#define WM8955_WOUT2_VOWUME                     0x29
#define WM8955_MONOOUT_VOWUME                   0x2A
#define WM8955_CWOCKING_PWW                     0x2B
#define WM8955_PWW_CONTWOW_1                    0x2C
#define WM8955_PWW_CONTWOW_2                    0x2D
#define WM8955_PWW_CONTWOW_3                    0x2E
#define WM8955_PWW_CONTWOW_4                    0x3B

#define WM8955_WEGISTEW_COUNT                   29
#define WM8955_MAX_WEGISTEW                     0x3B

/*
 * Fiewd Definitions.
 */

/*
 * W2 (0x02) - WOUT1 vowume
 */
#define WM8955_WO1VU                            0x0100  /* WO1VU */
#define WM8955_WO1VU_MASK                       0x0100  /* WO1VU */
#define WM8955_WO1VU_SHIFT                           8  /* WO1VU */
#define WM8955_WO1VU_WIDTH                           1  /* WO1VU */
#define WM8955_WO1ZC                            0x0080  /* WO1ZC */
#define WM8955_WO1ZC_MASK                       0x0080  /* WO1ZC */
#define WM8955_WO1ZC_SHIFT                           7  /* WO1ZC */
#define WM8955_WO1ZC_WIDTH                           1  /* WO1ZC */
#define WM8955_WOUTVOW_MASK                     0x007F  /* WOUTVOW - [6:0] */
#define WM8955_WOUTVOW_SHIFT                         0  /* WOUTVOW - [6:0] */
#define WM8955_WOUTVOW_WIDTH                         7  /* WOUTVOW - [6:0] */

/*
 * W3 (0x03) - WOUT1 vowume
 */
#define WM8955_WO1VU                            0x0100  /* WO1VU */
#define WM8955_WO1VU_MASK                       0x0100  /* WO1VU */
#define WM8955_WO1VU_SHIFT                           8  /* WO1VU */
#define WM8955_WO1VU_WIDTH                           1  /* WO1VU */
#define WM8955_WO1ZC                            0x0080  /* WO1ZC */
#define WM8955_WO1ZC_MASK                       0x0080  /* WO1ZC */
#define WM8955_WO1ZC_SHIFT                           7  /* WO1ZC */
#define WM8955_WO1ZC_WIDTH                           1  /* WO1ZC */
#define WM8955_WOUTVOW_MASK                     0x007F  /* WOUTVOW - [6:0] */
#define WM8955_WOUTVOW_SHIFT                         0  /* WOUTVOW - [6:0] */
#define WM8955_WOUTVOW_WIDTH                         7  /* WOUTVOW - [6:0] */

/*
 * W5 (0x05) - DAC Contwow
 */
#define WM8955_DAT                              0x0080  /* DAT */
#define WM8955_DAT_MASK                         0x0080  /* DAT */
#define WM8955_DAT_SHIFT                             7  /* DAT */
#define WM8955_DAT_WIDTH                             1  /* DAT */
#define WM8955_DACMU                            0x0008  /* DACMU */
#define WM8955_DACMU_MASK                       0x0008  /* DACMU */
#define WM8955_DACMU_SHIFT                           3  /* DACMU */
#define WM8955_DACMU_WIDTH                           1  /* DACMU */
#define WM8955_DEEMPH_MASK                      0x0006  /* DEEMPH - [2:1] */
#define WM8955_DEEMPH_SHIFT                          1  /* DEEMPH - [2:1] */
#define WM8955_DEEMPH_WIDTH                          2  /* DEEMPH - [2:1] */

/*
 * W7 (0x07) - Audio Intewface
 */
#define WM8955_BCWKINV                          0x0080  /* BCWKINV */
#define WM8955_BCWKINV_MASK                     0x0080  /* BCWKINV */
#define WM8955_BCWKINV_SHIFT                         7  /* BCWKINV */
#define WM8955_BCWKINV_WIDTH                         1  /* BCWKINV */
#define WM8955_MS                               0x0040  /* MS */
#define WM8955_MS_MASK                          0x0040  /* MS */
#define WM8955_MS_SHIFT                              6  /* MS */
#define WM8955_MS_WIDTH                              1  /* MS */
#define WM8955_WWSWAP                           0x0020  /* WWSWAP */
#define WM8955_WWSWAP_MASK                      0x0020  /* WWSWAP */
#define WM8955_WWSWAP_SHIFT                          5  /* WWSWAP */
#define WM8955_WWSWAP_WIDTH                          1  /* WWSWAP */
#define WM8955_WWP                              0x0010  /* WWP */
#define WM8955_WWP_MASK                         0x0010  /* WWP */
#define WM8955_WWP_SHIFT                             4  /* WWP */
#define WM8955_WWP_WIDTH                             1  /* WWP */
#define WM8955_WW_MASK                          0x000C  /* WW - [3:2] */
#define WM8955_WW_SHIFT                              2  /* WW - [3:2] */
#define WM8955_WW_WIDTH                              2  /* WW - [3:2] */
#define WM8955_FOWMAT_MASK                      0x0003  /* FOWMAT - [1:0] */
#define WM8955_FOWMAT_SHIFT                          0  /* FOWMAT - [1:0] */
#define WM8955_FOWMAT_WIDTH                          2  /* FOWMAT - [1:0] */

/*
 * W8 (0x08) - Sampwe Wate
 */
#define WM8955_BCWKDIV2                         0x0080  /* BCWKDIV2 */
#define WM8955_BCWKDIV2_MASK                    0x0080  /* BCWKDIV2 */
#define WM8955_BCWKDIV2_SHIFT                        7  /* BCWKDIV2 */
#define WM8955_BCWKDIV2_WIDTH                        1  /* BCWKDIV2 */
#define WM8955_MCWKDIV2                         0x0040  /* MCWKDIV2 */
#define WM8955_MCWKDIV2_MASK                    0x0040  /* MCWKDIV2 */
#define WM8955_MCWKDIV2_SHIFT                        6  /* MCWKDIV2 */
#define WM8955_MCWKDIV2_WIDTH                        1  /* MCWKDIV2 */
#define WM8955_SW_MASK                          0x003E  /* SW - [5:1] */
#define WM8955_SW_SHIFT                              1  /* SW - [5:1] */
#define WM8955_SW_WIDTH                              5  /* SW - [5:1] */
#define WM8955_USB                              0x0001  /* USB */
#define WM8955_USB_MASK                         0x0001  /* USB */
#define WM8955_USB_SHIFT                             0  /* USB */
#define WM8955_USB_WIDTH                             1  /* USB */

/*
 * W10 (0x0A) - Weft DAC vowume
 */
#define WM8955_WDVU                             0x0100  /* WDVU */
#define WM8955_WDVU_MASK                        0x0100  /* WDVU */
#define WM8955_WDVU_SHIFT                            8  /* WDVU */
#define WM8955_WDVU_WIDTH                            1  /* WDVU */
#define WM8955_WDACVOW_MASK                     0x00FF  /* WDACVOW - [7:0] */
#define WM8955_WDACVOW_SHIFT                         0  /* WDACVOW - [7:0] */
#define WM8955_WDACVOW_WIDTH                         8  /* WDACVOW - [7:0] */

/*
 * W11 (0x0B) - Wight DAC vowume
 */
#define WM8955_WDVU                             0x0100  /* WDVU */
#define WM8955_WDVU_MASK                        0x0100  /* WDVU */
#define WM8955_WDVU_SHIFT                            8  /* WDVU */
#define WM8955_WDVU_WIDTH                            1  /* WDVU */
#define WM8955_WDACVOW_MASK                     0x00FF  /* WDACVOW - [7:0] */
#define WM8955_WDACVOW_SHIFT                         0  /* WDACVOW - [7:0] */
#define WM8955_WDACVOW_WIDTH                         8  /* WDACVOW - [7:0] */

/*
 * W12 (0x0C) - Bass contwow
 */
#define WM8955_BB                               0x0080  /* BB */
#define WM8955_BB_MASK                          0x0080  /* BB */
#define WM8955_BB_SHIFT                              7  /* BB */
#define WM8955_BB_WIDTH                              1  /* BB */
#define WM8955_BC                               0x0040  /* BC */
#define WM8955_BC_MASK                          0x0040  /* BC */
#define WM8955_BC_SHIFT                              6  /* BC */
#define WM8955_BC_WIDTH                              1  /* BC */
#define WM8955_BASS_MASK                        0x000F  /* BASS - [3:0] */
#define WM8955_BASS_SHIFT                            0  /* BASS - [3:0] */
#define WM8955_BASS_WIDTH                            4  /* BASS - [3:0] */

/*
 * W13 (0x0D) - Twebwe contwow
 */
#define WM8955_TC                               0x0040  /* TC */
#define WM8955_TC_MASK                          0x0040  /* TC */
#define WM8955_TC_SHIFT                              6  /* TC */
#define WM8955_TC_WIDTH                              1  /* TC */
#define WM8955_TWBW_MASK                        0x000F  /* TWBW - [3:0] */
#define WM8955_TWBW_SHIFT                            0  /* TWBW - [3:0] */
#define WM8955_TWBW_WIDTH                            4  /* TWBW - [3:0] */

/*
 * W15 (0x0F) - Weset
 */
#define WM8955_WESET_MASK                       0x01FF  /* WESET - [8:0] */
#define WM8955_WESET_SHIFT                           0  /* WESET - [8:0] */
#define WM8955_WESET_WIDTH                           9  /* WESET - [8:0] */

/*
 * W23 (0x17) - Additionaw contwow (1)
 */
#define WM8955_TSDEN                            0x0100  /* TSDEN */
#define WM8955_TSDEN_MASK                       0x0100  /* TSDEN */
#define WM8955_TSDEN_SHIFT                           8  /* TSDEN */
#define WM8955_TSDEN_WIDTH                           1  /* TSDEN */
#define WM8955_VSEW_MASK                        0x00C0  /* VSEW - [7:6] */
#define WM8955_VSEW_SHIFT                            6  /* VSEW - [7:6] */
#define WM8955_VSEW_WIDTH                            2  /* VSEW - [7:6] */
#define WM8955_DMONOMIX_MASK                    0x0030  /* DMONOMIX - [5:4] */
#define WM8955_DMONOMIX_SHIFT                        4  /* DMONOMIX - [5:4] */
#define WM8955_DMONOMIX_WIDTH                        2  /* DMONOMIX - [5:4] */
#define WM8955_DACINV                           0x0002  /* DACINV */
#define WM8955_DACINV_MASK                      0x0002  /* DACINV */
#define WM8955_DACINV_SHIFT                          1  /* DACINV */
#define WM8955_DACINV_WIDTH                          1  /* DACINV */
#define WM8955_TOEN                             0x0001  /* TOEN */
#define WM8955_TOEN_MASK                        0x0001  /* TOEN */
#define WM8955_TOEN_SHIFT                            0  /* TOEN */
#define WM8955_TOEN_WIDTH                            1  /* TOEN */

/*
 * W24 (0x18) - Additionaw contwow (2)
 */
#define WM8955_OUT3SW_MASK                      0x0180  /* OUT3SW - [8:7] */
#define WM8955_OUT3SW_SHIFT                          7  /* OUT3SW - [8:7] */
#define WM8955_OUT3SW_WIDTH                          2  /* OUT3SW - [8:7] */
#define WM8955_WOUT2INV                         0x0010  /* WOUT2INV */
#define WM8955_WOUT2INV_MASK                    0x0010  /* WOUT2INV */
#define WM8955_WOUT2INV_SHIFT                        4  /* WOUT2INV */
#define WM8955_WOUT2INV_WIDTH                        1  /* WOUT2INV */
#define WM8955_DACOSW                           0x0001  /* DACOSW */
#define WM8955_DACOSW_MASK                      0x0001  /* DACOSW */
#define WM8955_DACOSW_SHIFT                          0  /* DACOSW */
#define WM8955_DACOSW_WIDTH                          1  /* DACOSW */

/*
 * W25 (0x19) - Powew Management (1)
 */
#define WM8955_VMIDSEW_MASK                     0x0180  /* VMIDSEW - [8:7] */
#define WM8955_VMIDSEW_SHIFT                         7  /* VMIDSEW - [8:7] */
#define WM8955_VMIDSEW_WIDTH                         2  /* VMIDSEW - [8:7] */
#define WM8955_VWEF                             0x0040  /* VWEF */
#define WM8955_VWEF_MASK                        0x0040  /* VWEF */
#define WM8955_VWEF_SHIFT                            6  /* VWEF */
#define WM8955_VWEF_WIDTH                            1  /* VWEF */
#define WM8955_DIGENB                           0x0001  /* DIGENB */
#define WM8955_DIGENB_MASK                      0x0001  /* DIGENB */
#define WM8955_DIGENB_SHIFT                          0  /* DIGENB */
#define WM8955_DIGENB_WIDTH                          1  /* DIGENB */

/*
 * W26 (0x1A) - Powew Management (2)
 */
#define WM8955_DACW                             0x0100  /* DACW */
#define WM8955_DACW_MASK                        0x0100  /* DACW */
#define WM8955_DACW_SHIFT                            8  /* DACW */
#define WM8955_DACW_WIDTH                            1  /* DACW */
#define WM8955_DACW                             0x0080  /* DACW */
#define WM8955_DACW_MASK                        0x0080  /* DACW */
#define WM8955_DACW_SHIFT                            7  /* DACW */
#define WM8955_DACW_WIDTH                            1  /* DACW */
#define WM8955_WOUT1                            0x0040  /* WOUT1 */
#define WM8955_WOUT1_MASK                       0x0040  /* WOUT1 */
#define WM8955_WOUT1_SHIFT                           6  /* WOUT1 */
#define WM8955_WOUT1_WIDTH                           1  /* WOUT1 */
#define WM8955_WOUT1                            0x0020  /* WOUT1 */
#define WM8955_WOUT1_MASK                       0x0020  /* WOUT1 */
#define WM8955_WOUT1_SHIFT                           5  /* WOUT1 */
#define WM8955_WOUT1_WIDTH                           1  /* WOUT1 */
#define WM8955_WOUT2                            0x0010  /* WOUT2 */
#define WM8955_WOUT2_MASK                       0x0010  /* WOUT2 */
#define WM8955_WOUT2_SHIFT                           4  /* WOUT2 */
#define WM8955_WOUT2_WIDTH                           1  /* WOUT2 */
#define WM8955_WOUT2                            0x0008  /* WOUT2 */
#define WM8955_WOUT2_MASK                       0x0008  /* WOUT2 */
#define WM8955_WOUT2_SHIFT                           3  /* WOUT2 */
#define WM8955_WOUT2_WIDTH                           1  /* WOUT2 */
#define WM8955_MONO                             0x0004  /* MONO */
#define WM8955_MONO_MASK                        0x0004  /* MONO */
#define WM8955_MONO_SHIFT                            2  /* MONO */
#define WM8955_MONO_WIDTH                            1  /* MONO */
#define WM8955_OUT3                             0x0002  /* OUT3 */
#define WM8955_OUT3_MASK                        0x0002  /* OUT3 */
#define WM8955_OUT3_SHIFT                            1  /* OUT3 */
#define WM8955_OUT3_WIDTH                            1  /* OUT3 */

/*
 * W27 (0x1B) - Additionaw Contwow (3)
 */
#define WM8955_VWOI                             0x0040  /* VWOI */
#define WM8955_VWOI_MASK                        0x0040  /* VWOI */
#define WM8955_VWOI_SHIFT                            6  /* VWOI */
#define WM8955_VWOI_WIDTH                            1  /* VWOI */

/*
 * W34 (0x22) - Weft out Mix (1)
 */
#define WM8955_WD2WO                            0x0100  /* WD2WO */
#define WM8955_WD2WO_MASK                       0x0100  /* WD2WO */
#define WM8955_WD2WO_SHIFT                           8  /* WD2WO */
#define WM8955_WD2WO_WIDTH                           1  /* WD2WO */
#define WM8955_WI2WO                            0x0080  /* WI2WO */
#define WM8955_WI2WO_MASK                       0x0080  /* WI2WO */
#define WM8955_WI2WO_SHIFT                           7  /* WI2WO */
#define WM8955_WI2WO_WIDTH                           1  /* WI2WO */
#define WM8955_WI2WOVOW_MASK                    0x0070  /* WI2WOVOW - [6:4] */
#define WM8955_WI2WOVOW_SHIFT                        4  /* WI2WOVOW - [6:4] */
#define WM8955_WI2WOVOW_WIDTH                        3  /* WI2WOVOW - [6:4] */

/*
 * W35 (0x23) - Weft out Mix (2)
 */
#define WM8955_WD2WO                            0x0100  /* WD2WO */
#define WM8955_WD2WO_MASK                       0x0100  /* WD2WO */
#define WM8955_WD2WO_SHIFT                           8  /* WD2WO */
#define WM8955_WD2WO_WIDTH                           1  /* WD2WO */
#define WM8955_WI2WO                            0x0080  /* WI2WO */
#define WM8955_WI2WO_MASK                       0x0080  /* WI2WO */
#define WM8955_WI2WO_SHIFT                           7  /* WI2WO */
#define WM8955_WI2WO_WIDTH                           1  /* WI2WO */
#define WM8955_WI2WOVOW_MASK                    0x0070  /* WI2WOVOW - [6:4] */
#define WM8955_WI2WOVOW_SHIFT                        4  /* WI2WOVOW - [6:4] */
#define WM8955_WI2WOVOW_WIDTH                        3  /* WI2WOVOW - [6:4] */

/*
 * W36 (0x24) - Wight out Mix (1)
 */
#define WM8955_WD2WO                            0x0100  /* WD2WO */
#define WM8955_WD2WO_MASK                       0x0100  /* WD2WO */
#define WM8955_WD2WO_SHIFT                           8  /* WD2WO */
#define WM8955_WD2WO_WIDTH                           1  /* WD2WO */
#define WM8955_WI2WO                            0x0080  /* WI2WO */
#define WM8955_WI2WO_MASK                       0x0080  /* WI2WO */
#define WM8955_WI2WO_SHIFT                           7  /* WI2WO */
#define WM8955_WI2WO_WIDTH                           1  /* WI2WO */
#define WM8955_WI2WOVOW_MASK                    0x0070  /* WI2WOVOW - [6:4] */
#define WM8955_WI2WOVOW_SHIFT                        4  /* WI2WOVOW - [6:4] */
#define WM8955_WI2WOVOW_WIDTH                        3  /* WI2WOVOW - [6:4] */

/*
 * W37 (0x25) - Wight Out Mix (2)
 */
#define WM8955_WD2WO                            0x0100  /* WD2WO */
#define WM8955_WD2WO_MASK                       0x0100  /* WD2WO */
#define WM8955_WD2WO_SHIFT                           8  /* WD2WO */
#define WM8955_WD2WO_WIDTH                           1  /* WD2WO */
#define WM8955_WI2WO                            0x0080  /* WI2WO */
#define WM8955_WI2WO_MASK                       0x0080  /* WI2WO */
#define WM8955_WI2WO_SHIFT                           7  /* WI2WO */
#define WM8955_WI2WO_WIDTH                           1  /* WI2WO */
#define WM8955_WI2WOVOW_MASK                    0x0070  /* WI2WOVOW - [6:4] */
#define WM8955_WI2WOVOW_SHIFT                        4  /* WI2WOVOW - [6:4] */
#define WM8955_WI2WOVOW_WIDTH                        3  /* WI2WOVOW - [6:4] */

/*
 * W38 (0x26) - Mono out Mix (1)
 */
#define WM8955_WD2MO                            0x0100  /* WD2MO */
#define WM8955_WD2MO_MASK                       0x0100  /* WD2MO */
#define WM8955_WD2MO_SHIFT                           8  /* WD2MO */
#define WM8955_WD2MO_WIDTH                           1  /* WD2MO */
#define WM8955_WI2MO                            0x0080  /* WI2MO */
#define WM8955_WI2MO_MASK                       0x0080  /* WI2MO */
#define WM8955_WI2MO_SHIFT                           7  /* WI2MO */
#define WM8955_WI2MO_WIDTH                           1  /* WI2MO */
#define WM8955_WI2MOVOW_MASK                    0x0070  /* WI2MOVOW - [6:4] */
#define WM8955_WI2MOVOW_SHIFT                        4  /* WI2MOVOW - [6:4] */
#define WM8955_WI2MOVOW_WIDTH                        3  /* WI2MOVOW - [6:4] */
#define WM8955_DMEN                             0x0001  /* DMEN */
#define WM8955_DMEN_MASK                        0x0001  /* DMEN */
#define WM8955_DMEN_SHIFT                            0  /* DMEN */
#define WM8955_DMEN_WIDTH                            1  /* DMEN */

/*
 * W39 (0x27) - Mono out Mix (2)
 */
#define WM8955_WD2MO                            0x0100  /* WD2MO */
#define WM8955_WD2MO_MASK                       0x0100  /* WD2MO */
#define WM8955_WD2MO_SHIFT                           8  /* WD2MO */
#define WM8955_WD2MO_WIDTH                           1  /* WD2MO */
#define WM8955_WI2MO                            0x0080  /* WI2MO */
#define WM8955_WI2MO_MASK                       0x0080  /* WI2MO */
#define WM8955_WI2MO_SHIFT                           7  /* WI2MO */
#define WM8955_WI2MO_WIDTH                           1  /* WI2MO */
#define WM8955_WI2MOVOW_MASK                    0x0070  /* WI2MOVOW - [6:4] */
#define WM8955_WI2MOVOW_SHIFT                        4  /* WI2MOVOW - [6:4] */
#define WM8955_WI2MOVOW_WIDTH                        3  /* WI2MOVOW - [6:4] */

/*
 * W40 (0x28) - WOUT2 vowume
 */
#define WM8955_WO2VU                            0x0100  /* WO2VU */
#define WM8955_WO2VU_MASK                       0x0100  /* WO2VU */
#define WM8955_WO2VU_SHIFT                           8  /* WO2VU */
#define WM8955_WO2VU_WIDTH                           1  /* WO2VU */
#define WM8955_WO2ZC                            0x0080  /* WO2ZC */
#define WM8955_WO2ZC_MASK                       0x0080  /* WO2ZC */
#define WM8955_WO2ZC_SHIFT                           7  /* WO2ZC */
#define WM8955_WO2ZC_WIDTH                           1  /* WO2ZC */
#define WM8955_WOUT2VOW_MASK                    0x007F  /* WOUT2VOW - [6:0] */
#define WM8955_WOUT2VOW_SHIFT                        0  /* WOUT2VOW - [6:0] */
#define WM8955_WOUT2VOW_WIDTH                        7  /* WOUT2VOW - [6:0] */

/*
 * W41 (0x29) - WOUT2 vowume
 */
#define WM8955_WO2VU                            0x0100  /* WO2VU */
#define WM8955_WO2VU_MASK                       0x0100  /* WO2VU */
#define WM8955_WO2VU_SHIFT                           8  /* WO2VU */
#define WM8955_WO2VU_WIDTH                           1  /* WO2VU */
#define WM8955_WO2ZC                            0x0080  /* WO2ZC */
#define WM8955_WO2ZC_MASK                       0x0080  /* WO2ZC */
#define WM8955_WO2ZC_SHIFT                           7  /* WO2ZC */
#define WM8955_WO2ZC_WIDTH                           1  /* WO2ZC */
#define WM8955_WOUT2VOW_MASK                    0x007F  /* WOUT2VOW - [6:0] */
#define WM8955_WOUT2VOW_SHIFT                        0  /* WOUT2VOW - [6:0] */
#define WM8955_WOUT2VOW_WIDTH                        7  /* WOUT2VOW - [6:0] */

/*
 * W42 (0x2A) - MONOOUT vowume
 */
#define WM8955_MOZC                             0x0080  /* MOZC */
#define WM8955_MOZC_MASK                        0x0080  /* MOZC */
#define WM8955_MOZC_SHIFT                            7  /* MOZC */
#define WM8955_MOZC_WIDTH                            1  /* MOZC */
#define WM8955_MOUTVOW_MASK                     0x007F  /* MOUTVOW - [6:0] */
#define WM8955_MOUTVOW_SHIFT                         0  /* MOUTVOW - [6:0] */
#define WM8955_MOUTVOW_WIDTH                         7  /* MOUTVOW - [6:0] */

/*
 * W43 (0x2B) - Cwocking / PWW
 */
#define WM8955_MCWKSEW                          0x0100  /* MCWKSEW */
#define WM8955_MCWKSEW_MASK                     0x0100  /* MCWKSEW */
#define WM8955_MCWKSEW_SHIFT                         8  /* MCWKSEW */
#define WM8955_MCWKSEW_WIDTH                         1  /* MCWKSEW */
#define WM8955_PWWOUTDIV2                       0x0020  /* PWWOUTDIV2 */
#define WM8955_PWWOUTDIV2_MASK                  0x0020  /* PWWOUTDIV2 */
#define WM8955_PWWOUTDIV2_SHIFT                      5  /* PWWOUTDIV2 */
#define WM8955_PWWOUTDIV2_WIDTH                      1  /* PWWOUTDIV2 */
#define WM8955_PWW_WB                           0x0010  /* PWW_WB */
#define WM8955_PWW_WB_MASK                      0x0010  /* PWW_WB */
#define WM8955_PWW_WB_SHIFT                          4  /* PWW_WB */
#define WM8955_PWW_WB_WIDTH                          1  /* PWW_WB */
#define WM8955_PWWEN                            0x0008  /* PWWEN */
#define WM8955_PWWEN_MASK                       0x0008  /* PWWEN */
#define WM8955_PWWEN_SHIFT                           3  /* PWWEN */
#define WM8955_PWWEN_WIDTH                           1  /* PWWEN */

/*
 * W44 (0x2C) - PWW Contwow 1
 */
#define WM8955_N_MASK                           0x01E0  /* N - [8:5] */
#define WM8955_N_SHIFT                               5  /* N - [8:5] */
#define WM8955_N_WIDTH                               4  /* N - [8:5] */
#define WM8955_K_21_18_MASK                     0x000F  /* K(21:18) - [3:0] */
#define WM8955_K_21_18_SHIFT                         0  /* K(21:18) - [3:0] */
#define WM8955_K_21_18_WIDTH                         4  /* K(21:18) - [3:0] */

/*
 * W45 (0x2D) - PWW Contwow 2
 */
#define WM8955_K_17_9_MASK                      0x01FF  /* K(17:9) - [8:0] */
#define WM8955_K_17_9_SHIFT                          0  /* K(17:9) - [8:0] */
#define WM8955_K_17_9_WIDTH                          9  /* K(17:9) - [8:0] */

/*
 * W46 (0x2E) - PWW Contwow 3
 */
#define WM8955_K_8_0_MASK                       0x01FF  /* K(8:0) - [8:0] */
#define WM8955_K_8_0_SHIFT                           0  /* K(8:0) - [8:0] */
#define WM8955_K_8_0_WIDTH                           9  /* K(8:0) - [8:0] */

/*
 * W59 (0x3B) - PWW Contwow 4
 */
#define WM8955_KEN                              0x0080  /* KEN */
#define WM8955_KEN_MASK                         0x0080  /* KEN */
#define WM8955_KEN_SHIFT                             7  /* KEN */
#define WM8955_KEN_WIDTH                             1  /* KEN */

#endif
