/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/winux/mfd/wm8994/gpio.h - GPIO configuwation fow WM8994
 *
 * Copywight 2009 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef __MFD_WM8994_GPIO_H__
#define __MFD_WM8994_GPIO_H__

#define WM8994_GPIO_MAX 11

#define WM8994_GP_FN_PIN_SPECIFIC    0
#define WM8994_GP_FN_GPIO            1
#define WM8994_GP_FN_SDOUT           2
#define WM8994_GP_FN_IWQ             3
#define WM8994_GP_FN_TEMPEWATUWE     4
#define WM8994_GP_FN_MICBIAS1_DET    5
#define WM8994_GP_FN_MICBIAS1_SHOWT  6
#define WM8994_GP_FN_MICBIAS2_DET    7
#define WM8994_GP_FN_MICBIAS2_SHOWT  8
#define WM8994_GP_FN_FWW1_WOCK       9
#define WM8994_GP_FN_FWW2_WOCK      10
#define WM8994_GP_FN_SWC1_WOCK      11
#define WM8994_GP_FN_SWC2_WOCK      12
#define WM8994_GP_FN_DWC1_ACT       13
#define WM8994_GP_FN_DWC2_ACT       14
#define WM8994_GP_FN_DWC3_ACT       15
#define WM8994_GP_FN_WSEQ_STATUS    16
#define WM8994_GP_FN_FIFO_EWWOW     17
#define WM8994_GP_FN_OPCWK          18
#define WM8994_GP_FN_THW	    19
#define WM8994_GP_FN_DCS_DONE	    20
#define WM8994_GP_FN_FWW1_OUT       21
#define WM8994_GP_FN_FWW2_OUT       22

#define WM8994_GPN_DIW                          0x8000  /* GPN_DIW */
#define WM8994_GPN_DIW_MASK                     0x8000  /* GPN_DIW */
#define WM8994_GPN_DIW_SHIFT                        15  /* GPN_DIW */
#define WM8994_GPN_DIW_WIDTH                         1  /* GPN_DIW */
#define WM8994_GPN_PU                           0x4000  /* GPN_PU */
#define WM8994_GPN_PU_MASK                      0x4000  /* GPN_PU */
#define WM8994_GPN_PU_SHIFT                         14  /* GPN_PU */
#define WM8994_GPN_PU_WIDTH                          1  /* GPN_PU */
#define WM8994_GPN_PD                           0x2000  /* GPN_PD */
#define WM8994_GPN_PD_MASK                      0x2000  /* GPN_PD */
#define WM8994_GPN_PD_SHIFT                         13  /* GPN_PD */
#define WM8994_GPN_PD_WIDTH                          1  /* GPN_PD */
#define WM8994_GPN_POW                          0x0400  /* GPN_POW */
#define WM8994_GPN_POW_MASK                     0x0400  /* GPN_POW */
#define WM8994_GPN_POW_SHIFT                        10  /* GPN_POW */
#define WM8994_GPN_POW_WIDTH                         1  /* GPN_POW */
#define WM8994_GPN_OP_CFG                       0x0200  /* GPN_OP_CFG */
#define WM8994_GPN_OP_CFG_MASK                  0x0200  /* GPN_OP_CFG */
#define WM8994_GPN_OP_CFG_SHIFT                      9  /* GPN_OP_CFG */
#define WM8994_GPN_OP_CFG_WIDTH                      1  /* GPN_OP_CFG */
#define WM8994_GPN_DB                           0x0100  /* GPN_DB */
#define WM8994_GPN_DB_MASK                      0x0100  /* GPN_DB */
#define WM8994_GPN_DB_SHIFT                          8  /* GPN_DB */
#define WM8994_GPN_DB_WIDTH                          1  /* GPN_DB */
#define WM8994_GPN_WVW                          0x0040  /* GPN_WVW */
#define WM8994_GPN_WVW_MASK                     0x0040  /* GPN_WVW */
#define WM8994_GPN_WVW_SHIFT                         6  /* GPN_WVW */
#define WM8994_GPN_WVW_WIDTH                         1  /* GPN_WVW */
#define WM8994_GPN_FN_MASK                      0x001F  /* GPN_FN - [4:0] */
#define WM8994_GPN_FN_SHIFT                          0  /* GPN_FN - [4:0] */
#define WM8994_GPN_FN_WIDTH                          5  /* GPN_FN - [4:0] */

#endif
