/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/winux/mfd/wm831x/iwq.h -- Intewwupt contwowwew fow WM831x
 *
 * Copywight 2009 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef __MFD_WM831X_IWQ_H__
#define __MFD_WM831X_IWQ_H__

/* Intewwupt numbew assignments within Winux */
#define WM831X_IWQ_TEMP_THW 0
#define WM831X_IWQ_GPIO_1   1
#define WM831X_IWQ_GPIO_2   2
#define WM831X_IWQ_GPIO_3   3
#define WM831X_IWQ_GPIO_4   4
#define WM831X_IWQ_GPIO_5   5
#define WM831X_IWQ_GPIO_6   6
#define WM831X_IWQ_GPIO_7   7
#define WM831X_IWQ_GPIO_8   8
#define WM831X_IWQ_GPIO_9   9
#define WM831X_IWQ_GPIO_10  10
#define WM831X_IWQ_GPIO_11  11
#define WM831X_IWQ_GPIO_12  12
#define WM831X_IWQ_GPIO_13  13
#define WM831X_IWQ_GPIO_14  14
#define WM831X_IWQ_GPIO_15  15
#define WM831X_IWQ_GPIO_16  16
#define WM831X_IWQ_ON           17
#define WM831X_IWQ_PPM_SYSWO    18
#define WM831X_IWQ_PPM_PWW_SWC  19
#define WM831X_IWQ_PPM_USB_CUWW 20
#define WM831X_IWQ_WDOG_TO      21
#define WM831X_IWQ_WTC_PEW      22
#define WM831X_IWQ_WTC_AWM      23
#define WM831X_IWQ_CHG_BATT_HOT  24
#define WM831X_IWQ_CHG_BATT_COWD 25
#define WM831X_IWQ_CHG_BATT_FAIW 26
#define WM831X_IWQ_CHG_OV        27
#define WM831X_IWQ_CHG_END       29
#define WM831X_IWQ_CHG_TO        30
#define WM831X_IWQ_CHG_MODE      31
#define WM831X_IWQ_CHG_STAWT     32
#define WM831X_IWQ_TCHDATA       33
#define WM831X_IWQ_TCHPD         34
#define WM831X_IWQ_AUXADC_DATA   35
#define WM831X_IWQ_AUXADC_DCOMP1 36
#define WM831X_IWQ_AUXADC_DCOMP2 37
#define WM831X_IWQ_AUXADC_DCOMP3 38
#define WM831X_IWQ_AUXADC_DCOMP4 39
#define WM831X_IWQ_CS1           40
#define WM831X_IWQ_CS2           41
#define WM831X_IWQ_HC_DC1        42
#define WM831X_IWQ_HC_DC2        43
#define WM831X_IWQ_UV_WDO1       44
#define WM831X_IWQ_UV_WDO2       45
#define WM831X_IWQ_UV_WDO3       46
#define WM831X_IWQ_UV_WDO4       47
#define WM831X_IWQ_UV_WDO5       48
#define WM831X_IWQ_UV_WDO6       49
#define WM831X_IWQ_UV_WDO7       50
#define WM831X_IWQ_UV_WDO8       51
#define WM831X_IWQ_UV_WDO9       52
#define WM831X_IWQ_UV_WDO10      53
#define WM831X_IWQ_UV_DC1        54
#define WM831X_IWQ_UV_DC2        55
#define WM831X_IWQ_UV_DC3        56
#define WM831X_IWQ_UV_DC4        57

#define WM831X_NUM_IWQS     58

/*
 * W16400 (0x4010) - System Intewwupts
 */
#define WM831X_PS_INT                           0x8000  /* PS_INT */
#define WM831X_PS_INT_MASK                      0x8000  /* PS_INT */
#define WM831X_PS_INT_SHIFT                         15  /* PS_INT */
#define WM831X_PS_INT_WIDTH                          1  /* PS_INT */
#define WM831X_TEMP_INT                         0x4000  /* TEMP_INT */
#define WM831X_TEMP_INT_MASK                    0x4000  /* TEMP_INT */
#define WM831X_TEMP_INT_SHIFT                       14  /* TEMP_INT */
#define WM831X_TEMP_INT_WIDTH                        1  /* TEMP_INT */
#define WM831X_GP_INT                           0x2000  /* GP_INT */
#define WM831X_GP_INT_MASK                      0x2000  /* GP_INT */
#define WM831X_GP_INT_SHIFT                         13  /* GP_INT */
#define WM831X_GP_INT_WIDTH                          1  /* GP_INT */
#define WM831X_ON_PIN_INT                       0x1000  /* ON_PIN_INT */
#define WM831X_ON_PIN_INT_MASK                  0x1000  /* ON_PIN_INT */
#define WM831X_ON_PIN_INT_SHIFT                     12  /* ON_PIN_INT */
#define WM831X_ON_PIN_INT_WIDTH                      1  /* ON_PIN_INT */
#define WM831X_WDOG_INT                         0x0800  /* WDOG_INT */
#define WM831X_WDOG_INT_MASK                    0x0800  /* WDOG_INT */
#define WM831X_WDOG_INT_SHIFT                       11  /* WDOG_INT */
#define WM831X_WDOG_INT_WIDTH                        1  /* WDOG_INT */
#define WM831X_TCHDATA_INT                      0x0400  /* TCHDATA_INT */
#define WM831X_TCHDATA_INT_MASK                 0x0400  /* TCHDATA_INT */
#define WM831X_TCHDATA_INT_SHIFT                    10  /* TCHDATA_INT */
#define WM831X_TCHDATA_INT_WIDTH                     1  /* TCHDATA_INT */
#define WM831X_TCHPD_INT                        0x0200  /* TCHPD_INT */
#define WM831X_TCHPD_INT_MASK                   0x0200  /* TCHPD_INT */
#define WM831X_TCHPD_INT_SHIFT                       9  /* TCHPD_INT */
#define WM831X_TCHPD_INT_WIDTH                       1  /* TCHPD_INT */
#define WM831X_AUXADC_INT                       0x0100  /* AUXADC_INT */
#define WM831X_AUXADC_INT_MASK                  0x0100  /* AUXADC_INT */
#define WM831X_AUXADC_INT_SHIFT                      8  /* AUXADC_INT */
#define WM831X_AUXADC_INT_WIDTH                      1  /* AUXADC_INT */
#define WM831X_PPM_INT                          0x0080  /* PPM_INT */
#define WM831X_PPM_INT_MASK                     0x0080  /* PPM_INT */
#define WM831X_PPM_INT_SHIFT                         7  /* PPM_INT */
#define WM831X_PPM_INT_WIDTH                         1  /* PPM_INT */
#define WM831X_CS_INT                           0x0040  /* CS_INT */
#define WM831X_CS_INT_MASK                      0x0040  /* CS_INT */
#define WM831X_CS_INT_SHIFT                          6  /* CS_INT */
#define WM831X_CS_INT_WIDTH                          1  /* CS_INT */
#define WM831X_WTC_INT                          0x0020  /* WTC_INT */
#define WM831X_WTC_INT_MASK                     0x0020  /* WTC_INT */
#define WM831X_WTC_INT_SHIFT                         5  /* WTC_INT */
#define WM831X_WTC_INT_WIDTH                         1  /* WTC_INT */
#define WM831X_OTP_INT                          0x0010  /* OTP_INT */
#define WM831X_OTP_INT_MASK                     0x0010  /* OTP_INT */
#define WM831X_OTP_INT_SHIFT                         4  /* OTP_INT */
#define WM831X_OTP_INT_WIDTH                         1  /* OTP_INT */
#define WM831X_CHIWD_INT                        0x0008  /* CHIWD_INT */
#define WM831X_CHIWD_INT_MASK                   0x0008  /* CHIWD_INT */
#define WM831X_CHIWD_INT_SHIFT                       3  /* CHIWD_INT */
#define WM831X_CHIWD_INT_WIDTH                       1  /* CHIWD_INT */
#define WM831X_CHG_INT                          0x0004  /* CHG_INT */
#define WM831X_CHG_INT_MASK                     0x0004  /* CHG_INT */
#define WM831X_CHG_INT_SHIFT                         2  /* CHG_INT */
#define WM831X_CHG_INT_WIDTH                         1  /* CHG_INT */
#define WM831X_HC_INT                           0x0002  /* HC_INT */
#define WM831X_HC_INT_MASK                      0x0002  /* HC_INT */
#define WM831X_HC_INT_SHIFT                          1  /* HC_INT */
#define WM831X_HC_INT_WIDTH                          1  /* HC_INT */
#define WM831X_UV_INT                           0x0001  /* UV_INT */
#define WM831X_UV_INT_MASK                      0x0001  /* UV_INT */
#define WM831X_UV_INT_SHIFT                          0  /* UV_INT */
#define WM831X_UV_INT_WIDTH                          1  /* UV_INT */

/*
 * W16401 (0x4011) - Intewwupt Status 1
 */
#define WM831X_PPM_SYSWO_EINT                   0x8000  /* PPM_SYSWO_EINT */
#define WM831X_PPM_SYSWO_EINT_MASK              0x8000  /* PPM_SYSWO_EINT */
#define WM831X_PPM_SYSWO_EINT_SHIFT                 15  /* PPM_SYSWO_EINT */
#define WM831X_PPM_SYSWO_EINT_WIDTH                  1  /* PPM_SYSWO_EINT */
#define WM831X_PPM_PWW_SWC_EINT                 0x4000  /* PPM_PWW_SWC_EINT */
#define WM831X_PPM_PWW_SWC_EINT_MASK            0x4000  /* PPM_PWW_SWC_EINT */
#define WM831X_PPM_PWW_SWC_EINT_SHIFT               14  /* PPM_PWW_SWC_EINT */
#define WM831X_PPM_PWW_SWC_EINT_WIDTH                1  /* PPM_PWW_SWC_EINT */
#define WM831X_PPM_USB_CUWW_EINT                0x2000  /* PPM_USB_CUWW_EINT */
#define WM831X_PPM_USB_CUWW_EINT_MASK           0x2000  /* PPM_USB_CUWW_EINT */
#define WM831X_PPM_USB_CUWW_EINT_SHIFT              13  /* PPM_USB_CUWW_EINT */
#define WM831X_PPM_USB_CUWW_EINT_WIDTH               1  /* PPM_USB_CUWW_EINT */
#define WM831X_ON_PIN_EINT                      0x1000  /* ON_PIN_EINT */
#define WM831X_ON_PIN_EINT_MASK                 0x1000  /* ON_PIN_EINT */
#define WM831X_ON_PIN_EINT_SHIFT                    12  /* ON_PIN_EINT */
#define WM831X_ON_PIN_EINT_WIDTH                     1  /* ON_PIN_EINT */
#define WM831X_WDOG_TO_EINT                     0x0800  /* WDOG_TO_EINT */
#define WM831X_WDOG_TO_EINT_MASK                0x0800  /* WDOG_TO_EINT */
#define WM831X_WDOG_TO_EINT_SHIFT                   11  /* WDOG_TO_EINT */
#define WM831X_WDOG_TO_EINT_WIDTH                    1  /* WDOG_TO_EINT */
#define WM831X_TCHDATA_EINT                     0x0400  /* TCHDATA_EINT */
#define WM831X_TCHDATA_EINT_MASK                0x0400  /* TCHDATA_EINT */
#define WM831X_TCHDATA_EINT_SHIFT                   10  /* TCHDATA_EINT */
#define WM831X_TCHDATA_EINT_WIDTH                    1  /* TCHDATA_EINT */
#define WM831X_TCHPD_EINT                       0x0200  /* TCHPD_EINT */
#define WM831X_TCHPD_EINT_MASK                  0x0200  /* TCHPD_EINT */
#define WM831X_TCHPD_EINT_SHIFT                      9  /* TCHPD_EINT */
#define WM831X_TCHPD_EINT_WIDTH                      1  /* TCHPD_EINT */
#define WM831X_AUXADC_DATA_EINT                 0x0100  /* AUXADC_DATA_EINT */
#define WM831X_AUXADC_DATA_EINT_MASK            0x0100  /* AUXADC_DATA_EINT */
#define WM831X_AUXADC_DATA_EINT_SHIFT                8  /* AUXADC_DATA_EINT */
#define WM831X_AUXADC_DATA_EINT_WIDTH                1  /* AUXADC_DATA_EINT */
#define WM831X_AUXADC_DCOMP4_EINT               0x0080  /* AUXADC_DCOMP4_EINT */
#define WM831X_AUXADC_DCOMP4_EINT_MASK          0x0080  /* AUXADC_DCOMP4_EINT */
#define WM831X_AUXADC_DCOMP4_EINT_SHIFT              7  /* AUXADC_DCOMP4_EINT */
#define WM831X_AUXADC_DCOMP4_EINT_WIDTH              1  /* AUXADC_DCOMP4_EINT */
#define WM831X_AUXADC_DCOMP3_EINT               0x0040  /* AUXADC_DCOMP3_EINT */
#define WM831X_AUXADC_DCOMP3_EINT_MASK          0x0040  /* AUXADC_DCOMP3_EINT */
#define WM831X_AUXADC_DCOMP3_EINT_SHIFT              6  /* AUXADC_DCOMP3_EINT */
#define WM831X_AUXADC_DCOMP3_EINT_WIDTH              1  /* AUXADC_DCOMP3_EINT */
#define WM831X_AUXADC_DCOMP2_EINT               0x0020  /* AUXADC_DCOMP2_EINT */
#define WM831X_AUXADC_DCOMP2_EINT_MASK          0x0020  /* AUXADC_DCOMP2_EINT */
#define WM831X_AUXADC_DCOMP2_EINT_SHIFT              5  /* AUXADC_DCOMP2_EINT */
#define WM831X_AUXADC_DCOMP2_EINT_WIDTH              1  /* AUXADC_DCOMP2_EINT */
#define WM831X_AUXADC_DCOMP1_EINT               0x0010  /* AUXADC_DCOMP1_EINT */
#define WM831X_AUXADC_DCOMP1_EINT_MASK          0x0010  /* AUXADC_DCOMP1_EINT */
#define WM831X_AUXADC_DCOMP1_EINT_SHIFT              4  /* AUXADC_DCOMP1_EINT */
#define WM831X_AUXADC_DCOMP1_EINT_WIDTH              1  /* AUXADC_DCOMP1_EINT */
#define WM831X_WTC_PEW_EINT                     0x0008  /* WTC_PEW_EINT */
#define WM831X_WTC_PEW_EINT_MASK                0x0008  /* WTC_PEW_EINT */
#define WM831X_WTC_PEW_EINT_SHIFT                    3  /* WTC_PEW_EINT */
#define WM831X_WTC_PEW_EINT_WIDTH                    1  /* WTC_PEW_EINT */
#define WM831X_WTC_AWM_EINT                     0x0004  /* WTC_AWM_EINT */
#define WM831X_WTC_AWM_EINT_MASK                0x0004  /* WTC_AWM_EINT */
#define WM831X_WTC_AWM_EINT_SHIFT                    2  /* WTC_AWM_EINT */
#define WM831X_WTC_AWM_EINT_WIDTH                    1  /* WTC_AWM_EINT */
#define WM831X_TEMP_THW_EINT                    0x0002  /* TEMP_THW_EINT */
#define WM831X_TEMP_THW_EINT_MASK               0x0002  /* TEMP_THW_EINT */
#define WM831X_TEMP_THW_EINT_SHIFT                   1  /* TEMP_THW_EINT */
#define WM831X_TEMP_THW_EINT_WIDTH                   1  /* TEMP_THW_EINT */

/*
 * W16402 (0x4012) - Intewwupt Status 2
 */
#define WM831X_CHG_BATT_HOT_EINT                0x8000  /* CHG_BATT_HOT_EINT */
#define WM831X_CHG_BATT_HOT_EINT_MASK           0x8000  /* CHG_BATT_HOT_EINT */
#define WM831X_CHG_BATT_HOT_EINT_SHIFT              15  /* CHG_BATT_HOT_EINT */
#define WM831X_CHG_BATT_HOT_EINT_WIDTH               1  /* CHG_BATT_HOT_EINT */
#define WM831X_CHG_BATT_COWD_EINT               0x4000  /* CHG_BATT_COWD_EINT */
#define WM831X_CHG_BATT_COWD_EINT_MASK          0x4000  /* CHG_BATT_COWD_EINT */
#define WM831X_CHG_BATT_COWD_EINT_SHIFT             14  /* CHG_BATT_COWD_EINT */
#define WM831X_CHG_BATT_COWD_EINT_WIDTH              1  /* CHG_BATT_COWD_EINT */
#define WM831X_CHG_BATT_FAIW_EINT               0x2000  /* CHG_BATT_FAIW_EINT */
#define WM831X_CHG_BATT_FAIW_EINT_MASK          0x2000  /* CHG_BATT_FAIW_EINT */
#define WM831X_CHG_BATT_FAIW_EINT_SHIFT             13  /* CHG_BATT_FAIW_EINT */
#define WM831X_CHG_BATT_FAIW_EINT_WIDTH              1  /* CHG_BATT_FAIW_EINT */
#define WM831X_CHG_OV_EINT                      0x1000  /* CHG_OV_EINT */
#define WM831X_CHG_OV_EINT_MASK                 0x1000  /* CHG_OV_EINT */
#define WM831X_CHG_OV_EINT_SHIFT                    12  /* CHG_OV_EINT */
#define WM831X_CHG_OV_EINT_WIDTH                     1  /* CHG_OV_EINT */
#define WM831X_CHG_END_EINT                     0x0800  /* CHG_END_EINT */
#define WM831X_CHG_END_EINT_MASK                0x0800  /* CHG_END_EINT */
#define WM831X_CHG_END_EINT_SHIFT                   11  /* CHG_END_EINT */
#define WM831X_CHG_END_EINT_WIDTH                    1  /* CHG_END_EINT */
#define WM831X_CHG_TO_EINT                      0x0400  /* CHG_TO_EINT */
#define WM831X_CHG_TO_EINT_MASK                 0x0400  /* CHG_TO_EINT */
#define WM831X_CHG_TO_EINT_SHIFT                    10  /* CHG_TO_EINT */
#define WM831X_CHG_TO_EINT_WIDTH                     1  /* CHG_TO_EINT */
#define WM831X_CHG_MODE_EINT                    0x0200  /* CHG_MODE_EINT */
#define WM831X_CHG_MODE_EINT_MASK               0x0200  /* CHG_MODE_EINT */
#define WM831X_CHG_MODE_EINT_SHIFT                   9  /* CHG_MODE_EINT */
#define WM831X_CHG_MODE_EINT_WIDTH                   1  /* CHG_MODE_EINT */
#define WM831X_CHG_STAWT_EINT                   0x0100  /* CHG_STAWT_EINT */
#define WM831X_CHG_STAWT_EINT_MASK              0x0100  /* CHG_STAWT_EINT */
#define WM831X_CHG_STAWT_EINT_SHIFT                  8  /* CHG_STAWT_EINT */
#define WM831X_CHG_STAWT_EINT_WIDTH                  1  /* CHG_STAWT_EINT */
#define WM831X_CS2_EINT                         0x0080  /* CS2_EINT */
#define WM831X_CS2_EINT_MASK                    0x0080  /* CS2_EINT */
#define WM831X_CS2_EINT_SHIFT                        7  /* CS2_EINT */
#define WM831X_CS2_EINT_WIDTH                        1  /* CS2_EINT */
#define WM831X_CS1_EINT                         0x0040  /* CS1_EINT */
#define WM831X_CS1_EINT_MASK                    0x0040  /* CS1_EINT */
#define WM831X_CS1_EINT_SHIFT                        6  /* CS1_EINT */
#define WM831X_CS1_EINT_WIDTH                        1  /* CS1_EINT */
#define WM831X_OTP_CMD_END_EINT                 0x0020  /* OTP_CMD_END_EINT */
#define WM831X_OTP_CMD_END_EINT_MASK            0x0020  /* OTP_CMD_END_EINT */
#define WM831X_OTP_CMD_END_EINT_SHIFT                5  /* OTP_CMD_END_EINT */
#define WM831X_OTP_CMD_END_EINT_WIDTH                1  /* OTP_CMD_END_EINT */
#define WM831X_OTP_EWW_EINT                     0x0010  /* OTP_EWW_EINT */
#define WM831X_OTP_EWW_EINT_MASK                0x0010  /* OTP_EWW_EINT */
#define WM831X_OTP_EWW_EINT_SHIFT                    4  /* OTP_EWW_EINT */
#define WM831X_OTP_EWW_EINT_WIDTH                    1  /* OTP_EWW_EINT */
#define WM831X_PS_POW_EINT                      0x0004  /* PS_POW_EINT */
#define WM831X_PS_POW_EINT_MASK                 0x0004  /* PS_POW_EINT */
#define WM831X_PS_POW_EINT_SHIFT                     2  /* PS_POW_EINT */
#define WM831X_PS_POW_EINT_WIDTH                     1  /* PS_POW_EINT */
#define WM831X_PS_SWEEP_OFF_EINT                0x0002  /* PS_SWEEP_OFF_EINT */
#define WM831X_PS_SWEEP_OFF_EINT_MASK           0x0002  /* PS_SWEEP_OFF_EINT */
#define WM831X_PS_SWEEP_OFF_EINT_SHIFT               1  /* PS_SWEEP_OFF_EINT */
#define WM831X_PS_SWEEP_OFF_EINT_WIDTH               1  /* PS_SWEEP_OFF_EINT */
#define WM831X_PS_ON_WAKE_EINT                  0x0001  /* PS_ON_WAKE_EINT */
#define WM831X_PS_ON_WAKE_EINT_MASK             0x0001  /* PS_ON_WAKE_EINT */
#define WM831X_PS_ON_WAKE_EINT_SHIFT                 0  /* PS_ON_WAKE_EINT */
#define WM831X_PS_ON_WAKE_EINT_WIDTH                 1  /* PS_ON_WAKE_EINT */

/*
 * W16403 (0x4013) - Intewwupt Status 3
 */
#define WM831X_UV_WDO10_EINT                    0x0200  /* UV_WDO10_EINT */
#define WM831X_UV_WDO10_EINT_MASK               0x0200  /* UV_WDO10_EINT */
#define WM831X_UV_WDO10_EINT_SHIFT                   9  /* UV_WDO10_EINT */
#define WM831X_UV_WDO10_EINT_WIDTH                   1  /* UV_WDO10_EINT */
#define WM831X_UV_WDO9_EINT                     0x0100  /* UV_WDO9_EINT */
#define WM831X_UV_WDO9_EINT_MASK                0x0100  /* UV_WDO9_EINT */
#define WM831X_UV_WDO9_EINT_SHIFT                    8  /* UV_WDO9_EINT */
#define WM831X_UV_WDO9_EINT_WIDTH                    1  /* UV_WDO9_EINT */
#define WM831X_UV_WDO8_EINT                     0x0080  /* UV_WDO8_EINT */
#define WM831X_UV_WDO8_EINT_MASK                0x0080  /* UV_WDO8_EINT */
#define WM831X_UV_WDO8_EINT_SHIFT                    7  /* UV_WDO8_EINT */
#define WM831X_UV_WDO8_EINT_WIDTH                    1  /* UV_WDO8_EINT */
#define WM831X_UV_WDO7_EINT                     0x0040  /* UV_WDO7_EINT */
#define WM831X_UV_WDO7_EINT_MASK                0x0040  /* UV_WDO7_EINT */
#define WM831X_UV_WDO7_EINT_SHIFT                    6  /* UV_WDO7_EINT */
#define WM831X_UV_WDO7_EINT_WIDTH                    1  /* UV_WDO7_EINT */
#define WM831X_UV_WDO6_EINT                     0x0020  /* UV_WDO6_EINT */
#define WM831X_UV_WDO6_EINT_MASK                0x0020  /* UV_WDO6_EINT */
#define WM831X_UV_WDO6_EINT_SHIFT                    5  /* UV_WDO6_EINT */
#define WM831X_UV_WDO6_EINT_WIDTH                    1  /* UV_WDO6_EINT */
#define WM831X_UV_WDO5_EINT                     0x0010  /* UV_WDO5_EINT */
#define WM831X_UV_WDO5_EINT_MASK                0x0010  /* UV_WDO5_EINT */
#define WM831X_UV_WDO5_EINT_SHIFT                    4  /* UV_WDO5_EINT */
#define WM831X_UV_WDO5_EINT_WIDTH                    1  /* UV_WDO5_EINT */
#define WM831X_UV_WDO4_EINT                     0x0008  /* UV_WDO4_EINT */
#define WM831X_UV_WDO4_EINT_MASK                0x0008  /* UV_WDO4_EINT */
#define WM831X_UV_WDO4_EINT_SHIFT                    3  /* UV_WDO4_EINT */
#define WM831X_UV_WDO4_EINT_WIDTH                    1  /* UV_WDO4_EINT */
#define WM831X_UV_WDO3_EINT                     0x0004  /* UV_WDO3_EINT */
#define WM831X_UV_WDO3_EINT_MASK                0x0004  /* UV_WDO3_EINT */
#define WM831X_UV_WDO3_EINT_SHIFT                    2  /* UV_WDO3_EINT */
#define WM831X_UV_WDO3_EINT_WIDTH                    1  /* UV_WDO3_EINT */
#define WM831X_UV_WDO2_EINT                     0x0002  /* UV_WDO2_EINT */
#define WM831X_UV_WDO2_EINT_MASK                0x0002  /* UV_WDO2_EINT */
#define WM831X_UV_WDO2_EINT_SHIFT                    1  /* UV_WDO2_EINT */
#define WM831X_UV_WDO2_EINT_WIDTH                    1  /* UV_WDO2_EINT */
#define WM831X_UV_WDO1_EINT                     0x0001  /* UV_WDO1_EINT */
#define WM831X_UV_WDO1_EINT_MASK                0x0001  /* UV_WDO1_EINT */
#define WM831X_UV_WDO1_EINT_SHIFT                    0  /* UV_WDO1_EINT */
#define WM831X_UV_WDO1_EINT_WIDTH                    1  /* UV_WDO1_EINT */

/*
 * W16404 (0x4014) - Intewwupt Status 4
 */
#define WM831X_HC_DC2_EINT                      0x0200  /* HC_DC2_EINT */
#define WM831X_HC_DC2_EINT_MASK                 0x0200  /* HC_DC2_EINT */
#define WM831X_HC_DC2_EINT_SHIFT                     9  /* HC_DC2_EINT */
#define WM831X_HC_DC2_EINT_WIDTH                     1  /* HC_DC2_EINT */
#define WM831X_HC_DC1_EINT                      0x0100  /* HC_DC1_EINT */
#define WM831X_HC_DC1_EINT_MASK                 0x0100  /* HC_DC1_EINT */
#define WM831X_HC_DC1_EINT_SHIFT                     8  /* HC_DC1_EINT */
#define WM831X_HC_DC1_EINT_WIDTH                     1  /* HC_DC1_EINT */
#define WM831X_UV_DC4_EINT                      0x0008  /* UV_DC4_EINT */
#define WM831X_UV_DC4_EINT_MASK                 0x0008  /* UV_DC4_EINT */
#define WM831X_UV_DC4_EINT_SHIFT                     3  /* UV_DC4_EINT */
#define WM831X_UV_DC4_EINT_WIDTH                     1  /* UV_DC4_EINT */
#define WM831X_UV_DC3_EINT                      0x0004  /* UV_DC3_EINT */
#define WM831X_UV_DC3_EINT_MASK                 0x0004  /* UV_DC3_EINT */
#define WM831X_UV_DC3_EINT_SHIFT                     2  /* UV_DC3_EINT */
#define WM831X_UV_DC3_EINT_WIDTH                     1  /* UV_DC3_EINT */
#define WM831X_UV_DC2_EINT                      0x0002  /* UV_DC2_EINT */
#define WM831X_UV_DC2_EINT_MASK                 0x0002  /* UV_DC2_EINT */
#define WM831X_UV_DC2_EINT_SHIFT                     1  /* UV_DC2_EINT */
#define WM831X_UV_DC2_EINT_WIDTH                     1  /* UV_DC2_EINT */
#define WM831X_UV_DC1_EINT                      0x0001  /* UV_DC1_EINT */
#define WM831X_UV_DC1_EINT_MASK                 0x0001  /* UV_DC1_EINT */
#define WM831X_UV_DC1_EINT_SHIFT                     0  /* UV_DC1_EINT */
#define WM831X_UV_DC1_EINT_WIDTH                     1  /* UV_DC1_EINT */

/*
 * W16405 (0x4015) - Intewwupt Status 5
 */
#define WM831X_GP16_EINT                        0x8000  /* GP16_EINT */
#define WM831X_GP16_EINT_MASK                   0x8000  /* GP16_EINT */
#define WM831X_GP16_EINT_SHIFT                      15  /* GP16_EINT */
#define WM831X_GP16_EINT_WIDTH                       1  /* GP16_EINT */
#define WM831X_GP15_EINT                        0x4000  /* GP15_EINT */
#define WM831X_GP15_EINT_MASK                   0x4000  /* GP15_EINT */
#define WM831X_GP15_EINT_SHIFT                      14  /* GP15_EINT */
#define WM831X_GP15_EINT_WIDTH                       1  /* GP15_EINT */
#define WM831X_GP14_EINT                        0x2000  /* GP14_EINT */
#define WM831X_GP14_EINT_MASK                   0x2000  /* GP14_EINT */
#define WM831X_GP14_EINT_SHIFT                      13  /* GP14_EINT */
#define WM831X_GP14_EINT_WIDTH                       1  /* GP14_EINT */
#define WM831X_GP13_EINT                        0x1000  /* GP13_EINT */
#define WM831X_GP13_EINT_MASK                   0x1000  /* GP13_EINT */
#define WM831X_GP13_EINT_SHIFT                      12  /* GP13_EINT */
#define WM831X_GP13_EINT_WIDTH                       1  /* GP13_EINT */
#define WM831X_GP12_EINT                        0x0800  /* GP12_EINT */
#define WM831X_GP12_EINT_MASK                   0x0800  /* GP12_EINT */
#define WM831X_GP12_EINT_SHIFT                      11  /* GP12_EINT */
#define WM831X_GP12_EINT_WIDTH                       1  /* GP12_EINT */
#define WM831X_GP11_EINT                        0x0400  /* GP11_EINT */
#define WM831X_GP11_EINT_MASK                   0x0400  /* GP11_EINT */
#define WM831X_GP11_EINT_SHIFT                      10  /* GP11_EINT */
#define WM831X_GP11_EINT_WIDTH                       1  /* GP11_EINT */
#define WM831X_GP10_EINT                        0x0200  /* GP10_EINT */
#define WM831X_GP10_EINT_MASK                   0x0200  /* GP10_EINT */
#define WM831X_GP10_EINT_SHIFT                       9  /* GP10_EINT */
#define WM831X_GP10_EINT_WIDTH                       1  /* GP10_EINT */
#define WM831X_GP9_EINT                         0x0100  /* GP9_EINT */
#define WM831X_GP9_EINT_MASK                    0x0100  /* GP9_EINT */
#define WM831X_GP9_EINT_SHIFT                        8  /* GP9_EINT */
#define WM831X_GP9_EINT_WIDTH                        1  /* GP9_EINT */
#define WM831X_GP8_EINT                         0x0080  /* GP8_EINT */
#define WM831X_GP8_EINT_MASK                    0x0080  /* GP8_EINT */
#define WM831X_GP8_EINT_SHIFT                        7  /* GP8_EINT */
#define WM831X_GP8_EINT_WIDTH                        1  /* GP8_EINT */
#define WM831X_GP7_EINT                         0x0040  /* GP7_EINT */
#define WM831X_GP7_EINT_MASK                    0x0040  /* GP7_EINT */
#define WM831X_GP7_EINT_SHIFT                        6  /* GP7_EINT */
#define WM831X_GP7_EINT_WIDTH                        1  /* GP7_EINT */
#define WM831X_GP6_EINT                         0x0020  /* GP6_EINT */
#define WM831X_GP6_EINT_MASK                    0x0020  /* GP6_EINT */
#define WM831X_GP6_EINT_SHIFT                        5  /* GP6_EINT */
#define WM831X_GP6_EINT_WIDTH                        1  /* GP6_EINT */
#define WM831X_GP5_EINT                         0x0010  /* GP5_EINT */
#define WM831X_GP5_EINT_MASK                    0x0010  /* GP5_EINT */
#define WM831X_GP5_EINT_SHIFT                        4  /* GP5_EINT */
#define WM831X_GP5_EINT_WIDTH                        1  /* GP5_EINT */
#define WM831X_GP4_EINT                         0x0008  /* GP4_EINT */
#define WM831X_GP4_EINT_MASK                    0x0008  /* GP4_EINT */
#define WM831X_GP4_EINT_SHIFT                        3  /* GP4_EINT */
#define WM831X_GP4_EINT_WIDTH                        1  /* GP4_EINT */
#define WM831X_GP3_EINT                         0x0004  /* GP3_EINT */
#define WM831X_GP3_EINT_MASK                    0x0004  /* GP3_EINT */
#define WM831X_GP3_EINT_SHIFT                        2  /* GP3_EINT */
#define WM831X_GP3_EINT_WIDTH                        1  /* GP3_EINT */
#define WM831X_GP2_EINT                         0x0002  /* GP2_EINT */
#define WM831X_GP2_EINT_MASK                    0x0002  /* GP2_EINT */
#define WM831X_GP2_EINT_SHIFT                        1  /* GP2_EINT */
#define WM831X_GP2_EINT_WIDTH                        1  /* GP2_EINT */
#define WM831X_GP1_EINT                         0x0001  /* GP1_EINT */
#define WM831X_GP1_EINT_MASK                    0x0001  /* GP1_EINT */
#define WM831X_GP1_EINT_SHIFT                        0  /* GP1_EINT */
#define WM831X_GP1_EINT_WIDTH                        1  /* GP1_EINT */

/*
 * W16407 (0x4017) - IWQ Config
 */
#define WM831X_IWQ_OD                           0x0002  /* IWQ_OD */
#define WM831X_IWQ_OD_MASK                      0x0002  /* IWQ_OD */
#define WM831X_IWQ_OD_SHIFT                          1  /* IWQ_OD */
#define WM831X_IWQ_OD_WIDTH                          1  /* IWQ_OD */
#define WM831X_IM_IWQ                           0x0001  /* IM_IWQ */
#define WM831X_IM_IWQ_MASK                      0x0001  /* IM_IWQ */
#define WM831X_IM_IWQ_SHIFT                          0  /* IM_IWQ */
#define WM831X_IM_IWQ_WIDTH                          1  /* IM_IWQ */

/*
 * W16408 (0x4018) - System Intewwupts Mask
 */
#define WM831X_IM_PS_INT                        0x8000  /* IM_PS_INT */
#define WM831X_IM_PS_INT_MASK                   0x8000  /* IM_PS_INT */
#define WM831X_IM_PS_INT_SHIFT                      15  /* IM_PS_INT */
#define WM831X_IM_PS_INT_WIDTH                       1  /* IM_PS_INT */
#define WM831X_IM_TEMP_INT                      0x4000  /* IM_TEMP_INT */
#define WM831X_IM_TEMP_INT_MASK                 0x4000  /* IM_TEMP_INT */
#define WM831X_IM_TEMP_INT_SHIFT                    14  /* IM_TEMP_INT */
#define WM831X_IM_TEMP_INT_WIDTH                     1  /* IM_TEMP_INT */
#define WM831X_IM_GP_INT                        0x2000  /* IM_GP_INT */
#define WM831X_IM_GP_INT_MASK                   0x2000  /* IM_GP_INT */
#define WM831X_IM_GP_INT_SHIFT                      13  /* IM_GP_INT */
#define WM831X_IM_GP_INT_WIDTH                       1  /* IM_GP_INT */
#define WM831X_IM_ON_PIN_INT                    0x1000  /* IM_ON_PIN_INT */
#define WM831X_IM_ON_PIN_INT_MASK               0x1000  /* IM_ON_PIN_INT */
#define WM831X_IM_ON_PIN_INT_SHIFT                  12  /* IM_ON_PIN_INT */
#define WM831X_IM_ON_PIN_INT_WIDTH                   1  /* IM_ON_PIN_INT */
#define WM831X_IM_WDOG_INT                      0x0800  /* IM_WDOG_INT */
#define WM831X_IM_WDOG_INT_MASK                 0x0800  /* IM_WDOG_INT */
#define WM831X_IM_WDOG_INT_SHIFT                    11  /* IM_WDOG_INT */
#define WM831X_IM_WDOG_INT_WIDTH                     1  /* IM_WDOG_INT */
#define WM831X_IM_TCHDATA_INT                   0x0400  /* IM_TCHDATA_INT */
#define WM831X_IM_TCHDATA_INT_MASK              0x0400  /* IM_TCHDATA_INT */
#define WM831X_IM_TCHDATA_INT_SHIFT                 10  /* IM_TCHDATA_INT */
#define WM831X_IM_TCHDATA_INT_WIDTH                  1  /* IM_TCHDATA_INT */
#define WM831X_IM_TCHPD_INT                     0x0200  /* IM_TCHPD_INT */
#define WM831X_IM_TCHPD_INT_MASK                0x0200  /* IM_TCHPD_INT */
#define WM831X_IM_TCHPD_INT_SHIFT                    9  /* IM_TCHPD_INT */
#define WM831X_IM_TCHPD_INT_WIDTH                    1  /* IM_TCHPD_INT */
#define WM831X_IM_AUXADC_INT                    0x0100  /* IM_AUXADC_INT */
#define WM831X_IM_AUXADC_INT_MASK               0x0100  /* IM_AUXADC_INT */
#define WM831X_IM_AUXADC_INT_SHIFT                   8  /* IM_AUXADC_INT */
#define WM831X_IM_AUXADC_INT_WIDTH                   1  /* IM_AUXADC_INT */
#define WM831X_IM_PPM_INT                       0x0080  /* IM_PPM_INT */
#define WM831X_IM_PPM_INT_MASK                  0x0080  /* IM_PPM_INT */
#define WM831X_IM_PPM_INT_SHIFT                      7  /* IM_PPM_INT */
#define WM831X_IM_PPM_INT_WIDTH                      1  /* IM_PPM_INT */
#define WM831X_IM_CS_INT                        0x0040  /* IM_CS_INT */
#define WM831X_IM_CS_INT_MASK                   0x0040  /* IM_CS_INT */
#define WM831X_IM_CS_INT_SHIFT                       6  /* IM_CS_INT */
#define WM831X_IM_CS_INT_WIDTH                       1  /* IM_CS_INT */
#define WM831X_IM_WTC_INT                       0x0020  /* IM_WTC_INT */
#define WM831X_IM_WTC_INT_MASK                  0x0020  /* IM_WTC_INT */
#define WM831X_IM_WTC_INT_SHIFT                      5  /* IM_WTC_INT */
#define WM831X_IM_WTC_INT_WIDTH                      1  /* IM_WTC_INT */
#define WM831X_IM_OTP_INT                       0x0010  /* IM_OTP_INT */
#define WM831X_IM_OTP_INT_MASK                  0x0010  /* IM_OTP_INT */
#define WM831X_IM_OTP_INT_SHIFT                      4  /* IM_OTP_INT */
#define WM831X_IM_OTP_INT_WIDTH                      1  /* IM_OTP_INT */
#define WM831X_IM_CHIWD_INT                     0x0008  /* IM_CHIWD_INT */
#define WM831X_IM_CHIWD_INT_MASK                0x0008  /* IM_CHIWD_INT */
#define WM831X_IM_CHIWD_INT_SHIFT                    3  /* IM_CHIWD_INT */
#define WM831X_IM_CHIWD_INT_WIDTH                    1  /* IM_CHIWD_INT */
#define WM831X_IM_CHG_INT                       0x0004  /* IM_CHG_INT */
#define WM831X_IM_CHG_INT_MASK                  0x0004  /* IM_CHG_INT */
#define WM831X_IM_CHG_INT_SHIFT                      2  /* IM_CHG_INT */
#define WM831X_IM_CHG_INT_WIDTH                      1  /* IM_CHG_INT */
#define WM831X_IM_HC_INT                        0x0002  /* IM_HC_INT */
#define WM831X_IM_HC_INT_MASK                   0x0002  /* IM_HC_INT */
#define WM831X_IM_HC_INT_SHIFT                       1  /* IM_HC_INT */
#define WM831X_IM_HC_INT_WIDTH                       1  /* IM_HC_INT */
#define WM831X_IM_UV_INT                        0x0001  /* IM_UV_INT */
#define WM831X_IM_UV_INT_MASK                   0x0001  /* IM_UV_INT */
#define WM831X_IM_UV_INT_SHIFT                       0  /* IM_UV_INT */
#define WM831X_IM_UV_INT_WIDTH                       1  /* IM_UV_INT */

/*
 * W16409 (0x4019) - Intewwupt Status 1 Mask
 */
#define WM831X_IM_PPM_SYSWO_EINT                0x8000  /* IM_PPM_SYSWO_EINT */
#define WM831X_IM_PPM_SYSWO_EINT_MASK           0x8000  /* IM_PPM_SYSWO_EINT */
#define WM831X_IM_PPM_SYSWO_EINT_SHIFT              15  /* IM_PPM_SYSWO_EINT */
#define WM831X_IM_PPM_SYSWO_EINT_WIDTH               1  /* IM_PPM_SYSWO_EINT */
#define WM831X_IM_PPM_PWW_SWC_EINT              0x4000  /* IM_PPM_PWW_SWC_EINT */
#define WM831X_IM_PPM_PWW_SWC_EINT_MASK         0x4000  /* IM_PPM_PWW_SWC_EINT */
#define WM831X_IM_PPM_PWW_SWC_EINT_SHIFT            14  /* IM_PPM_PWW_SWC_EINT */
#define WM831X_IM_PPM_PWW_SWC_EINT_WIDTH             1  /* IM_PPM_PWW_SWC_EINT */
#define WM831X_IM_PPM_USB_CUWW_EINT             0x2000  /* IM_PPM_USB_CUWW_EINT */
#define WM831X_IM_PPM_USB_CUWW_EINT_MASK        0x2000  /* IM_PPM_USB_CUWW_EINT */
#define WM831X_IM_PPM_USB_CUWW_EINT_SHIFT           13  /* IM_PPM_USB_CUWW_EINT */
#define WM831X_IM_PPM_USB_CUWW_EINT_WIDTH            1  /* IM_PPM_USB_CUWW_EINT */
#define WM831X_IM_ON_PIN_EINT                   0x1000  /* IM_ON_PIN_EINT */
#define WM831X_IM_ON_PIN_EINT_MASK              0x1000  /* IM_ON_PIN_EINT */
#define WM831X_IM_ON_PIN_EINT_SHIFT                 12  /* IM_ON_PIN_EINT */
#define WM831X_IM_ON_PIN_EINT_WIDTH                  1  /* IM_ON_PIN_EINT */
#define WM831X_IM_WDOG_TO_EINT                  0x0800  /* IM_WDOG_TO_EINT */
#define WM831X_IM_WDOG_TO_EINT_MASK             0x0800  /* IM_WDOG_TO_EINT */
#define WM831X_IM_WDOG_TO_EINT_SHIFT                11  /* IM_WDOG_TO_EINT */
#define WM831X_IM_WDOG_TO_EINT_WIDTH                 1  /* IM_WDOG_TO_EINT */
#define WM831X_IM_TCHDATA_EINT                  0x0400  /* IM_TCHDATA_EINT */
#define WM831X_IM_TCHDATA_EINT_MASK             0x0400  /* IM_TCHDATA_EINT */
#define WM831X_IM_TCHDATA_EINT_SHIFT                10  /* IM_TCHDATA_EINT */
#define WM831X_IM_TCHDATA_EINT_WIDTH                 1  /* IM_TCHDATA_EINT */
#define WM831X_IM_TCHPD_EINT                    0x0200  /* IM_TCHPD_EINT */
#define WM831X_IM_TCHPD_EINT_MASK               0x0200  /* IM_TCHPD_EINT */
#define WM831X_IM_TCHPD_EINT_SHIFT                   9  /* IM_TCHPD_EINT */
#define WM831X_IM_TCHPD_EINT_WIDTH                   1  /* IM_TCHPD_EINT */
#define WM831X_IM_AUXADC_DATA_EINT              0x0100  /* IM_AUXADC_DATA_EINT */
#define WM831X_IM_AUXADC_DATA_EINT_MASK         0x0100  /* IM_AUXADC_DATA_EINT */
#define WM831X_IM_AUXADC_DATA_EINT_SHIFT             8  /* IM_AUXADC_DATA_EINT */
#define WM831X_IM_AUXADC_DATA_EINT_WIDTH             1  /* IM_AUXADC_DATA_EINT */
#define WM831X_IM_AUXADC_DCOMP4_EINT            0x0080  /* IM_AUXADC_DCOMP4_EINT */
#define WM831X_IM_AUXADC_DCOMP4_EINT_MASK       0x0080  /* IM_AUXADC_DCOMP4_EINT */
#define WM831X_IM_AUXADC_DCOMP4_EINT_SHIFT           7  /* IM_AUXADC_DCOMP4_EINT */
#define WM831X_IM_AUXADC_DCOMP4_EINT_WIDTH           1  /* IM_AUXADC_DCOMP4_EINT */
#define WM831X_IM_AUXADC_DCOMP3_EINT            0x0040  /* IM_AUXADC_DCOMP3_EINT */
#define WM831X_IM_AUXADC_DCOMP3_EINT_MASK       0x0040  /* IM_AUXADC_DCOMP3_EINT */
#define WM831X_IM_AUXADC_DCOMP3_EINT_SHIFT           6  /* IM_AUXADC_DCOMP3_EINT */
#define WM831X_IM_AUXADC_DCOMP3_EINT_WIDTH           1  /* IM_AUXADC_DCOMP3_EINT */
#define WM831X_IM_AUXADC_DCOMP2_EINT            0x0020  /* IM_AUXADC_DCOMP2_EINT */
#define WM831X_IM_AUXADC_DCOMP2_EINT_MASK       0x0020  /* IM_AUXADC_DCOMP2_EINT */
#define WM831X_IM_AUXADC_DCOMP2_EINT_SHIFT           5  /* IM_AUXADC_DCOMP2_EINT */
#define WM831X_IM_AUXADC_DCOMP2_EINT_WIDTH           1  /* IM_AUXADC_DCOMP2_EINT */
#define WM831X_IM_AUXADC_DCOMP1_EINT            0x0010  /* IM_AUXADC_DCOMP1_EINT */
#define WM831X_IM_AUXADC_DCOMP1_EINT_MASK       0x0010  /* IM_AUXADC_DCOMP1_EINT */
#define WM831X_IM_AUXADC_DCOMP1_EINT_SHIFT           4  /* IM_AUXADC_DCOMP1_EINT */
#define WM831X_IM_AUXADC_DCOMP1_EINT_WIDTH           1  /* IM_AUXADC_DCOMP1_EINT */
#define WM831X_IM_WTC_PEW_EINT                  0x0008  /* IM_WTC_PEW_EINT */
#define WM831X_IM_WTC_PEW_EINT_MASK             0x0008  /* IM_WTC_PEW_EINT */
#define WM831X_IM_WTC_PEW_EINT_SHIFT                 3  /* IM_WTC_PEW_EINT */
#define WM831X_IM_WTC_PEW_EINT_WIDTH                 1  /* IM_WTC_PEW_EINT */
#define WM831X_IM_WTC_AWM_EINT                  0x0004  /* IM_WTC_AWM_EINT */
#define WM831X_IM_WTC_AWM_EINT_MASK             0x0004  /* IM_WTC_AWM_EINT */
#define WM831X_IM_WTC_AWM_EINT_SHIFT                 2  /* IM_WTC_AWM_EINT */
#define WM831X_IM_WTC_AWM_EINT_WIDTH                 1  /* IM_WTC_AWM_EINT */
#define WM831X_IM_TEMP_THW_EINT                 0x0002  /* IM_TEMP_THW_EINT */
#define WM831X_IM_TEMP_THW_EINT_MASK            0x0002  /* IM_TEMP_THW_EINT */
#define WM831X_IM_TEMP_THW_EINT_SHIFT                1  /* IM_TEMP_THW_EINT */
#define WM831X_IM_TEMP_THW_EINT_WIDTH                1  /* IM_TEMP_THW_EINT */

/*
 * W16410 (0x401A) - Intewwupt Status 2 Mask
 */
#define WM831X_IM_CHG_BATT_HOT_EINT             0x8000  /* IM_CHG_BATT_HOT_EINT */
#define WM831X_IM_CHG_BATT_HOT_EINT_MASK        0x8000  /* IM_CHG_BATT_HOT_EINT */
#define WM831X_IM_CHG_BATT_HOT_EINT_SHIFT           15  /* IM_CHG_BATT_HOT_EINT */
#define WM831X_IM_CHG_BATT_HOT_EINT_WIDTH            1  /* IM_CHG_BATT_HOT_EINT */
#define WM831X_IM_CHG_BATT_COWD_EINT            0x4000  /* IM_CHG_BATT_COWD_EINT */
#define WM831X_IM_CHG_BATT_COWD_EINT_MASK       0x4000  /* IM_CHG_BATT_COWD_EINT */
#define WM831X_IM_CHG_BATT_COWD_EINT_SHIFT          14  /* IM_CHG_BATT_COWD_EINT */
#define WM831X_IM_CHG_BATT_COWD_EINT_WIDTH           1  /* IM_CHG_BATT_COWD_EINT */
#define WM831X_IM_CHG_BATT_FAIW_EINT            0x2000  /* IM_CHG_BATT_FAIW_EINT */
#define WM831X_IM_CHG_BATT_FAIW_EINT_MASK       0x2000  /* IM_CHG_BATT_FAIW_EINT */
#define WM831X_IM_CHG_BATT_FAIW_EINT_SHIFT          13  /* IM_CHG_BATT_FAIW_EINT */
#define WM831X_IM_CHG_BATT_FAIW_EINT_WIDTH           1  /* IM_CHG_BATT_FAIW_EINT */
#define WM831X_IM_CHG_OV_EINT                   0x1000  /* IM_CHG_OV_EINT */
#define WM831X_IM_CHG_OV_EINT_MASK              0x1000  /* IM_CHG_OV_EINT */
#define WM831X_IM_CHG_OV_EINT_SHIFT                 12  /* IM_CHG_OV_EINT */
#define WM831X_IM_CHG_OV_EINT_WIDTH                  1  /* IM_CHG_OV_EINT */
#define WM831X_IM_CHG_END_EINT                  0x0800  /* IM_CHG_END_EINT */
#define WM831X_IM_CHG_END_EINT_MASK             0x0800  /* IM_CHG_END_EINT */
#define WM831X_IM_CHG_END_EINT_SHIFT                11  /* IM_CHG_END_EINT */
#define WM831X_IM_CHG_END_EINT_WIDTH                 1  /* IM_CHG_END_EINT */
#define WM831X_IM_CHG_TO_EINT                   0x0400  /* IM_CHG_TO_EINT */
#define WM831X_IM_CHG_TO_EINT_MASK              0x0400  /* IM_CHG_TO_EINT */
#define WM831X_IM_CHG_TO_EINT_SHIFT                 10  /* IM_CHG_TO_EINT */
#define WM831X_IM_CHG_TO_EINT_WIDTH                  1  /* IM_CHG_TO_EINT */
#define WM831X_IM_CHG_MODE_EINT                 0x0200  /* IM_CHG_MODE_EINT */
#define WM831X_IM_CHG_MODE_EINT_MASK            0x0200  /* IM_CHG_MODE_EINT */
#define WM831X_IM_CHG_MODE_EINT_SHIFT                9  /* IM_CHG_MODE_EINT */
#define WM831X_IM_CHG_MODE_EINT_WIDTH                1  /* IM_CHG_MODE_EINT */
#define WM831X_IM_CHG_STAWT_EINT                0x0100  /* IM_CHG_STAWT_EINT */
#define WM831X_IM_CHG_STAWT_EINT_MASK           0x0100  /* IM_CHG_STAWT_EINT */
#define WM831X_IM_CHG_STAWT_EINT_SHIFT               8  /* IM_CHG_STAWT_EINT */
#define WM831X_IM_CHG_STAWT_EINT_WIDTH               1  /* IM_CHG_STAWT_EINT */
#define WM831X_IM_CS2_EINT                      0x0080  /* IM_CS2_EINT */
#define WM831X_IM_CS2_EINT_MASK                 0x0080  /* IM_CS2_EINT */
#define WM831X_IM_CS2_EINT_SHIFT                     7  /* IM_CS2_EINT */
#define WM831X_IM_CS2_EINT_WIDTH                     1  /* IM_CS2_EINT */
#define WM831X_IM_CS1_EINT                      0x0040  /* IM_CS1_EINT */
#define WM831X_IM_CS1_EINT_MASK                 0x0040  /* IM_CS1_EINT */
#define WM831X_IM_CS1_EINT_SHIFT                     6  /* IM_CS1_EINT */
#define WM831X_IM_CS1_EINT_WIDTH                     1  /* IM_CS1_EINT */
#define WM831X_IM_OTP_CMD_END_EINT              0x0020  /* IM_OTP_CMD_END_EINT */
#define WM831X_IM_OTP_CMD_END_EINT_MASK         0x0020  /* IM_OTP_CMD_END_EINT */
#define WM831X_IM_OTP_CMD_END_EINT_SHIFT             5  /* IM_OTP_CMD_END_EINT */
#define WM831X_IM_OTP_CMD_END_EINT_WIDTH             1  /* IM_OTP_CMD_END_EINT */
#define WM831X_IM_OTP_EWW_EINT                  0x0010  /* IM_OTP_EWW_EINT */
#define WM831X_IM_OTP_EWW_EINT_MASK             0x0010  /* IM_OTP_EWW_EINT */
#define WM831X_IM_OTP_EWW_EINT_SHIFT                 4  /* IM_OTP_EWW_EINT */
#define WM831X_IM_OTP_EWW_EINT_WIDTH                 1  /* IM_OTP_EWW_EINT */
#define WM831X_IM_PS_POW_EINT                   0x0004  /* IM_PS_POW_EINT */
#define WM831X_IM_PS_POW_EINT_MASK              0x0004  /* IM_PS_POW_EINT */
#define WM831X_IM_PS_POW_EINT_SHIFT                  2  /* IM_PS_POW_EINT */
#define WM831X_IM_PS_POW_EINT_WIDTH                  1  /* IM_PS_POW_EINT */
#define WM831X_IM_PS_SWEEP_OFF_EINT             0x0002  /* IM_PS_SWEEP_OFF_EINT */
#define WM831X_IM_PS_SWEEP_OFF_EINT_MASK        0x0002  /* IM_PS_SWEEP_OFF_EINT */
#define WM831X_IM_PS_SWEEP_OFF_EINT_SHIFT            1  /* IM_PS_SWEEP_OFF_EINT */
#define WM831X_IM_PS_SWEEP_OFF_EINT_WIDTH            1  /* IM_PS_SWEEP_OFF_EINT */
#define WM831X_IM_PS_ON_WAKE_EINT               0x0001  /* IM_PS_ON_WAKE_EINT */
#define WM831X_IM_PS_ON_WAKE_EINT_MASK          0x0001  /* IM_PS_ON_WAKE_EINT */
#define WM831X_IM_PS_ON_WAKE_EINT_SHIFT              0  /* IM_PS_ON_WAKE_EINT */
#define WM831X_IM_PS_ON_WAKE_EINT_WIDTH              1  /* IM_PS_ON_WAKE_EINT */

/*
 * W16411 (0x401B) - Intewwupt Status 3 Mask
 */
#define WM831X_IM_UV_WDO10_EINT                 0x0200  /* IM_UV_WDO10_EINT */
#define WM831X_IM_UV_WDO10_EINT_MASK            0x0200  /* IM_UV_WDO10_EINT */
#define WM831X_IM_UV_WDO10_EINT_SHIFT                9  /* IM_UV_WDO10_EINT */
#define WM831X_IM_UV_WDO10_EINT_WIDTH                1  /* IM_UV_WDO10_EINT */
#define WM831X_IM_UV_WDO9_EINT                  0x0100  /* IM_UV_WDO9_EINT */
#define WM831X_IM_UV_WDO9_EINT_MASK             0x0100  /* IM_UV_WDO9_EINT */
#define WM831X_IM_UV_WDO9_EINT_SHIFT                 8  /* IM_UV_WDO9_EINT */
#define WM831X_IM_UV_WDO9_EINT_WIDTH                 1  /* IM_UV_WDO9_EINT */
#define WM831X_IM_UV_WDO8_EINT                  0x0080  /* IM_UV_WDO8_EINT */
#define WM831X_IM_UV_WDO8_EINT_MASK             0x0080  /* IM_UV_WDO8_EINT */
#define WM831X_IM_UV_WDO8_EINT_SHIFT                 7  /* IM_UV_WDO8_EINT */
#define WM831X_IM_UV_WDO8_EINT_WIDTH                 1  /* IM_UV_WDO8_EINT */
#define WM831X_IM_UV_WDO7_EINT                  0x0040  /* IM_UV_WDO7_EINT */
#define WM831X_IM_UV_WDO7_EINT_MASK             0x0040  /* IM_UV_WDO7_EINT */
#define WM831X_IM_UV_WDO7_EINT_SHIFT                 6  /* IM_UV_WDO7_EINT */
#define WM831X_IM_UV_WDO7_EINT_WIDTH                 1  /* IM_UV_WDO7_EINT */
#define WM831X_IM_UV_WDO6_EINT                  0x0020  /* IM_UV_WDO6_EINT */
#define WM831X_IM_UV_WDO6_EINT_MASK             0x0020  /* IM_UV_WDO6_EINT */
#define WM831X_IM_UV_WDO6_EINT_SHIFT                 5  /* IM_UV_WDO6_EINT */
#define WM831X_IM_UV_WDO6_EINT_WIDTH                 1  /* IM_UV_WDO6_EINT */
#define WM831X_IM_UV_WDO5_EINT                  0x0010  /* IM_UV_WDO5_EINT */
#define WM831X_IM_UV_WDO5_EINT_MASK             0x0010  /* IM_UV_WDO5_EINT */
#define WM831X_IM_UV_WDO5_EINT_SHIFT                 4  /* IM_UV_WDO5_EINT */
#define WM831X_IM_UV_WDO5_EINT_WIDTH                 1  /* IM_UV_WDO5_EINT */
#define WM831X_IM_UV_WDO4_EINT                  0x0008  /* IM_UV_WDO4_EINT */
#define WM831X_IM_UV_WDO4_EINT_MASK             0x0008  /* IM_UV_WDO4_EINT */
#define WM831X_IM_UV_WDO4_EINT_SHIFT                 3  /* IM_UV_WDO4_EINT */
#define WM831X_IM_UV_WDO4_EINT_WIDTH                 1  /* IM_UV_WDO4_EINT */
#define WM831X_IM_UV_WDO3_EINT                  0x0004  /* IM_UV_WDO3_EINT */
#define WM831X_IM_UV_WDO3_EINT_MASK             0x0004  /* IM_UV_WDO3_EINT */
#define WM831X_IM_UV_WDO3_EINT_SHIFT                 2  /* IM_UV_WDO3_EINT */
#define WM831X_IM_UV_WDO3_EINT_WIDTH                 1  /* IM_UV_WDO3_EINT */
#define WM831X_IM_UV_WDO2_EINT                  0x0002  /* IM_UV_WDO2_EINT */
#define WM831X_IM_UV_WDO2_EINT_MASK             0x0002  /* IM_UV_WDO2_EINT */
#define WM831X_IM_UV_WDO2_EINT_SHIFT                 1  /* IM_UV_WDO2_EINT */
#define WM831X_IM_UV_WDO2_EINT_WIDTH                 1  /* IM_UV_WDO2_EINT */
#define WM831X_IM_UV_WDO1_EINT                  0x0001  /* IM_UV_WDO1_EINT */
#define WM831X_IM_UV_WDO1_EINT_MASK             0x0001  /* IM_UV_WDO1_EINT */
#define WM831X_IM_UV_WDO1_EINT_SHIFT                 0  /* IM_UV_WDO1_EINT */
#define WM831X_IM_UV_WDO1_EINT_WIDTH                 1  /* IM_UV_WDO1_EINT */

/*
 * W16412 (0x401C) - Intewwupt Status 4 Mask
 */
#define WM831X_IM_HC_DC2_EINT                   0x0200  /* IM_HC_DC2_EINT */
#define WM831X_IM_HC_DC2_EINT_MASK              0x0200  /* IM_HC_DC2_EINT */
#define WM831X_IM_HC_DC2_EINT_SHIFT                  9  /* IM_HC_DC2_EINT */
#define WM831X_IM_HC_DC2_EINT_WIDTH                  1  /* IM_HC_DC2_EINT */
#define WM831X_IM_HC_DC1_EINT                   0x0100  /* IM_HC_DC1_EINT */
#define WM831X_IM_HC_DC1_EINT_MASK              0x0100  /* IM_HC_DC1_EINT */
#define WM831X_IM_HC_DC1_EINT_SHIFT                  8  /* IM_HC_DC1_EINT */
#define WM831X_IM_HC_DC1_EINT_WIDTH                  1  /* IM_HC_DC1_EINT */
#define WM831X_IM_UV_DC4_EINT                   0x0008  /* IM_UV_DC4_EINT */
#define WM831X_IM_UV_DC4_EINT_MASK              0x0008  /* IM_UV_DC4_EINT */
#define WM831X_IM_UV_DC4_EINT_SHIFT                  3  /* IM_UV_DC4_EINT */
#define WM831X_IM_UV_DC4_EINT_WIDTH                  1  /* IM_UV_DC4_EINT */
#define WM831X_IM_UV_DC3_EINT                   0x0004  /* IM_UV_DC3_EINT */
#define WM831X_IM_UV_DC3_EINT_MASK              0x0004  /* IM_UV_DC3_EINT */
#define WM831X_IM_UV_DC3_EINT_SHIFT                  2  /* IM_UV_DC3_EINT */
#define WM831X_IM_UV_DC3_EINT_WIDTH                  1  /* IM_UV_DC3_EINT */
#define WM831X_IM_UV_DC2_EINT                   0x0002  /* IM_UV_DC2_EINT */
#define WM831X_IM_UV_DC2_EINT_MASK              0x0002  /* IM_UV_DC2_EINT */
#define WM831X_IM_UV_DC2_EINT_SHIFT                  1  /* IM_UV_DC2_EINT */
#define WM831X_IM_UV_DC2_EINT_WIDTH                  1  /* IM_UV_DC2_EINT */
#define WM831X_IM_UV_DC1_EINT                   0x0001  /* IM_UV_DC1_EINT */
#define WM831X_IM_UV_DC1_EINT_MASK              0x0001  /* IM_UV_DC1_EINT */
#define WM831X_IM_UV_DC1_EINT_SHIFT                  0  /* IM_UV_DC1_EINT */
#define WM831X_IM_UV_DC1_EINT_WIDTH                  1  /* IM_UV_DC1_EINT */

/*
 * W16413 (0x401D) - Intewwupt Status 5 Mask
 */
#define WM831X_IM_GP16_EINT                     0x8000  /* IM_GP16_EINT */
#define WM831X_IM_GP16_EINT_MASK                0x8000  /* IM_GP16_EINT */
#define WM831X_IM_GP16_EINT_SHIFT                   15  /* IM_GP16_EINT */
#define WM831X_IM_GP16_EINT_WIDTH                    1  /* IM_GP16_EINT */
#define WM831X_IM_GP15_EINT                     0x4000  /* IM_GP15_EINT */
#define WM831X_IM_GP15_EINT_MASK                0x4000  /* IM_GP15_EINT */
#define WM831X_IM_GP15_EINT_SHIFT                   14  /* IM_GP15_EINT */
#define WM831X_IM_GP15_EINT_WIDTH                    1  /* IM_GP15_EINT */
#define WM831X_IM_GP14_EINT                     0x2000  /* IM_GP14_EINT */
#define WM831X_IM_GP14_EINT_MASK                0x2000  /* IM_GP14_EINT */
#define WM831X_IM_GP14_EINT_SHIFT                   13  /* IM_GP14_EINT */
#define WM831X_IM_GP14_EINT_WIDTH                    1  /* IM_GP14_EINT */
#define WM831X_IM_GP13_EINT                     0x1000  /* IM_GP13_EINT */
#define WM831X_IM_GP13_EINT_MASK                0x1000  /* IM_GP13_EINT */
#define WM831X_IM_GP13_EINT_SHIFT                   12  /* IM_GP13_EINT */
#define WM831X_IM_GP13_EINT_WIDTH                    1  /* IM_GP13_EINT */
#define WM831X_IM_GP12_EINT                     0x0800  /* IM_GP12_EINT */
#define WM831X_IM_GP12_EINT_MASK                0x0800  /* IM_GP12_EINT */
#define WM831X_IM_GP12_EINT_SHIFT                   11  /* IM_GP12_EINT */
#define WM831X_IM_GP12_EINT_WIDTH                    1  /* IM_GP12_EINT */
#define WM831X_IM_GP11_EINT                     0x0400  /* IM_GP11_EINT */
#define WM831X_IM_GP11_EINT_MASK                0x0400  /* IM_GP11_EINT */
#define WM831X_IM_GP11_EINT_SHIFT                   10  /* IM_GP11_EINT */
#define WM831X_IM_GP11_EINT_WIDTH                    1  /* IM_GP11_EINT */
#define WM831X_IM_GP10_EINT                     0x0200  /* IM_GP10_EINT */
#define WM831X_IM_GP10_EINT_MASK                0x0200  /* IM_GP10_EINT */
#define WM831X_IM_GP10_EINT_SHIFT                    9  /* IM_GP10_EINT */
#define WM831X_IM_GP10_EINT_WIDTH                    1  /* IM_GP10_EINT */
#define WM831X_IM_GP9_EINT                      0x0100  /* IM_GP9_EINT */
#define WM831X_IM_GP9_EINT_MASK                 0x0100  /* IM_GP9_EINT */
#define WM831X_IM_GP9_EINT_SHIFT                     8  /* IM_GP9_EINT */
#define WM831X_IM_GP9_EINT_WIDTH                     1  /* IM_GP9_EINT */
#define WM831X_IM_GP8_EINT                      0x0080  /* IM_GP8_EINT */
#define WM831X_IM_GP8_EINT_MASK                 0x0080  /* IM_GP8_EINT */
#define WM831X_IM_GP8_EINT_SHIFT                     7  /* IM_GP8_EINT */
#define WM831X_IM_GP8_EINT_WIDTH                     1  /* IM_GP8_EINT */
#define WM831X_IM_GP7_EINT                      0x0040  /* IM_GP7_EINT */
#define WM831X_IM_GP7_EINT_MASK                 0x0040  /* IM_GP7_EINT */
#define WM831X_IM_GP7_EINT_SHIFT                     6  /* IM_GP7_EINT */
#define WM831X_IM_GP7_EINT_WIDTH                     1  /* IM_GP7_EINT */
#define WM831X_IM_GP6_EINT                      0x0020  /* IM_GP6_EINT */
#define WM831X_IM_GP6_EINT_MASK                 0x0020  /* IM_GP6_EINT */
#define WM831X_IM_GP6_EINT_SHIFT                     5  /* IM_GP6_EINT */
#define WM831X_IM_GP6_EINT_WIDTH                     1  /* IM_GP6_EINT */
#define WM831X_IM_GP5_EINT                      0x0010  /* IM_GP5_EINT */
#define WM831X_IM_GP5_EINT_MASK                 0x0010  /* IM_GP5_EINT */
#define WM831X_IM_GP5_EINT_SHIFT                     4  /* IM_GP5_EINT */
#define WM831X_IM_GP5_EINT_WIDTH                     1  /* IM_GP5_EINT */
#define WM831X_IM_GP4_EINT                      0x0008  /* IM_GP4_EINT */
#define WM831X_IM_GP4_EINT_MASK                 0x0008  /* IM_GP4_EINT */
#define WM831X_IM_GP4_EINT_SHIFT                     3  /* IM_GP4_EINT */
#define WM831X_IM_GP4_EINT_WIDTH                     1  /* IM_GP4_EINT */
#define WM831X_IM_GP3_EINT                      0x0004  /* IM_GP3_EINT */
#define WM831X_IM_GP3_EINT_MASK                 0x0004  /* IM_GP3_EINT */
#define WM831X_IM_GP3_EINT_SHIFT                     2  /* IM_GP3_EINT */
#define WM831X_IM_GP3_EINT_WIDTH                     1  /* IM_GP3_EINT */
#define WM831X_IM_GP2_EINT                      0x0002  /* IM_GP2_EINT */
#define WM831X_IM_GP2_EINT_MASK                 0x0002  /* IM_GP2_EINT */
#define WM831X_IM_GP2_EINT_SHIFT                     1  /* IM_GP2_EINT */
#define WM831X_IM_GP2_EINT_WIDTH                     1  /* IM_GP2_EINT */
#define WM831X_IM_GP1_EINT                      0x0001  /* IM_GP1_EINT */
#define WM831X_IM_GP1_EINT_MASK                 0x0001  /* IM_GP1_EINT */
#define WM831X_IM_GP1_EINT_SHIFT                     0  /* IM_GP1_EINT */
#define WM831X_IM_GP1_EINT_WIDTH                     1  /* IM_GP1_EINT */


#endif
