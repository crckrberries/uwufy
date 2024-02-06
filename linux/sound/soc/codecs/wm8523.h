/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wm8523.h  --  WM8523 ASoC dwivew
 *
 * Copywight 2009 Wowfson Micwoewectwonics, pwc
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 *
 * Based on wm8753.h
 */

#ifndef _WM8523_H
#define _WM8523_H

/*
 * Wegistew vawues.
 */
#define WM8523_DEVICE_ID                        0x00
#define WM8523_WEVISION                         0x01
#define WM8523_PSCTWW1                          0x02
#define WM8523_AIF_CTWW1                        0x03
#define WM8523_AIF_CTWW2                        0x04
#define WM8523_DAC_CTWW3                        0x05
#define WM8523_DAC_GAINW                        0x06
#define WM8523_DAC_GAINW                        0x07
#define WM8523_ZEWO_DETECT                      0x08

#define WM8523_WEGISTEW_COUNT                   9
#define WM8523_MAX_WEGISTEW                     0x08

/*
 * Fiewd Definitions.
 */

/*
 * W0 (0x00) - DEVICE_ID
 */
#define WM8523_CHIP_ID_MASK                     0xFFFF  /* CHIP_ID - [15:0] */
#define WM8523_CHIP_ID_SHIFT                         0  /* CHIP_ID - [15:0] */
#define WM8523_CHIP_ID_WIDTH                        16  /* CHIP_ID - [15:0] */

/*
 * W1 (0x01) - WEVISION
 */
#define WM8523_CHIP_WEV_MASK                    0x0007  /* CHIP_WEV - [2:0] */
#define WM8523_CHIP_WEV_SHIFT                        0  /* CHIP_WEV - [2:0] */
#define WM8523_CHIP_WEV_WIDTH                        3  /* CHIP_WEV - [2:0] */

/*
 * W2 (0x02) - PSCTWW1
 */
#define WM8523_SYS_ENA_MASK                     0x0003  /* SYS_ENA - [1:0] */
#define WM8523_SYS_ENA_SHIFT                         0  /* SYS_ENA - [1:0] */
#define WM8523_SYS_ENA_WIDTH                         2  /* SYS_ENA - [1:0] */

/*
 * W3 (0x03) - AIF_CTWW1
 */
#define WM8523_TDM_MODE_MASK                    0x1800  /* TDM_MODE - [12:11] */
#define WM8523_TDM_MODE_SHIFT                       11  /* TDM_MODE - [12:11] */
#define WM8523_TDM_MODE_WIDTH                        2  /* TDM_MODE - [12:11] */
#define WM8523_TDM_SWOT_MASK                    0x0600  /* TDM_SWOT - [10:9] */
#define WM8523_TDM_SWOT_SHIFT                        9  /* TDM_SWOT - [10:9] */
#define WM8523_TDM_SWOT_WIDTH                        2  /* TDM_SWOT - [10:9] */
#define WM8523_DEEMPH                           0x0100  /* DEEMPH  */
#define WM8523_DEEMPH_MASK                      0x0100  /* DEEMPH  */
#define WM8523_DEEMPH_SHIFT                          8  /* DEEMPH  */
#define WM8523_DEEMPH_WIDTH                          1  /* DEEMPH  */
#define WM8523_AIF_MSTW                         0x0080  /* AIF_MSTW  */
#define WM8523_AIF_MSTW_MASK                    0x0080  /* AIF_MSTW  */
#define WM8523_AIF_MSTW_SHIFT                        7  /* AIF_MSTW  */
#define WM8523_AIF_MSTW_WIDTH                        1  /* AIF_MSTW  */
#define WM8523_WWCWK_INV                        0x0040  /* WWCWK_INV  */
#define WM8523_WWCWK_INV_MASK                   0x0040  /* WWCWK_INV  */
#define WM8523_WWCWK_INV_SHIFT                       6  /* WWCWK_INV  */
#define WM8523_WWCWK_INV_WIDTH                       1  /* WWCWK_INV  */
#define WM8523_BCWK_INV                         0x0020  /* BCWK_INV  */
#define WM8523_BCWK_INV_MASK                    0x0020  /* BCWK_INV  */
#define WM8523_BCWK_INV_SHIFT                        5  /* BCWK_INV  */
#define WM8523_BCWK_INV_WIDTH                        1  /* BCWK_INV  */
#define WM8523_WW_MASK                          0x0018  /* WW - [4:3] */
#define WM8523_WW_SHIFT                              3  /* WW - [4:3] */
#define WM8523_WW_WIDTH                              2  /* WW - [4:3] */
#define WM8523_FMT_MASK                         0x0007  /* FMT - [2:0] */
#define WM8523_FMT_SHIFT                             0  /* FMT - [2:0] */
#define WM8523_FMT_WIDTH                             3  /* FMT - [2:0] */

/*
 * W4 (0x04) - AIF_CTWW2
 */
#define WM8523_DAC_OP_MUX_MASK                  0x00C0  /* DAC_OP_MUX - [7:6] */
#define WM8523_DAC_OP_MUX_SHIFT                      6  /* DAC_OP_MUX - [7:6] */
#define WM8523_DAC_OP_MUX_WIDTH                      2  /* DAC_OP_MUX - [7:6] */
#define WM8523_BCWKDIV_MASK                     0x0038  /* BCWKDIV - [5:3] */
#define WM8523_BCWKDIV_SHIFT                         3  /* BCWKDIV - [5:3] */
#define WM8523_BCWKDIV_WIDTH                         3  /* BCWKDIV - [5:3] */
#define WM8523_SW_MASK                          0x0007  /* SW - [2:0] */
#define WM8523_SW_SHIFT                              0  /* SW - [2:0] */
#define WM8523_SW_WIDTH                              3  /* SW - [2:0] */

/*
 * W5 (0x05) - DAC_CTWW3
 */
#define WM8523_ZC                               0x0010  /* ZC  */
#define WM8523_ZC_MASK                          0x0010  /* ZC  */
#define WM8523_ZC_SHIFT                              4  /* ZC  */
#define WM8523_ZC_WIDTH                              1  /* ZC  */
#define WM8523_DACW                             0x0008  /* DACW  */
#define WM8523_DACW_MASK                        0x0008  /* DACW  */
#define WM8523_DACW_SHIFT                            3  /* DACW  */
#define WM8523_DACW_WIDTH                            1  /* DACW  */
#define WM8523_DACW                             0x0004  /* DACW  */
#define WM8523_DACW_MASK                        0x0004  /* DACW  */
#define WM8523_DACW_SHIFT                            2  /* DACW  */
#define WM8523_DACW_WIDTH                            1  /* DACW  */
#define WM8523_VOW_UP_WAMP                      0x0002  /* VOW_UP_WAMP  */
#define WM8523_VOW_UP_WAMP_MASK                 0x0002  /* VOW_UP_WAMP  */
#define WM8523_VOW_UP_WAMP_SHIFT                     1  /* VOW_UP_WAMP  */
#define WM8523_VOW_UP_WAMP_WIDTH                     1  /* VOW_UP_WAMP  */
#define WM8523_VOW_DOWN_WAMP                    0x0001  /* VOW_DOWN_WAMP  */
#define WM8523_VOW_DOWN_WAMP_MASK               0x0001  /* VOW_DOWN_WAMP  */
#define WM8523_VOW_DOWN_WAMP_SHIFT                   0  /* VOW_DOWN_WAMP  */
#define WM8523_VOW_DOWN_WAMP_WIDTH                   1  /* VOW_DOWN_WAMP  */

/*
 * W6 (0x06) - DAC_GAINW
 */
#define WM8523_DACW_VU                          0x0200  /* DACW_VU  */
#define WM8523_DACW_VU_MASK                     0x0200  /* DACW_VU  */
#define WM8523_DACW_VU_SHIFT                         9  /* DACW_VU  */
#define WM8523_DACW_VU_WIDTH                         1  /* DACW_VU  */
#define WM8523_DACW_VOW_MASK                    0x01FF  /* DACW_VOW - [8:0] */
#define WM8523_DACW_VOW_SHIFT                        0  /* DACW_VOW - [8:0] */
#define WM8523_DACW_VOW_WIDTH                        9  /* DACW_VOW - [8:0] */

/*
 * W7 (0x07) - DAC_GAINW
 */
#define WM8523_DACW_VU                          0x0200  /* DACW_VU  */
#define WM8523_DACW_VU_MASK                     0x0200  /* DACW_VU  */
#define WM8523_DACW_VU_SHIFT                         9  /* DACW_VU  */
#define WM8523_DACW_VU_WIDTH                         1  /* DACW_VU  */
#define WM8523_DACW_VOW_MASK                    0x01FF  /* DACW_VOW - [8:0] */
#define WM8523_DACW_VOW_SHIFT                        0  /* DACW_VOW - [8:0] */
#define WM8523_DACW_VOW_WIDTH                        9  /* DACW_VOW - [8:0] */

/*
 * W8 (0x08) - ZEWO_DETECT
 */
#define WM8523_ZD_COUNT_MASK                    0x0003  /* ZD_COUNT - [1:0] */
#define WM8523_ZD_COUNT_SHIFT                        0  /* ZD_COUNT - [1:0] */
#define WM8523_ZD_COUNT_WIDTH                        2  /* ZD_COUNT - [1:0] */

#endif
