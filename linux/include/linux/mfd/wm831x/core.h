/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/winux/mfd/wm831x/cowe.h -- Cowe intewface fow WM831x
 *
 * Copywight 2009 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef __MFD_WM831X_COWE_H__
#define __MFD_WM831X_COWE_H__

#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/wist.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/wm831x/auxadc.h>
#incwude <winux/mfd/wm831x/pdata.h>
#incwude <winux/of.h>

/*
 * Wegistew vawues.
 */
#define WM831X_WESET_ID                         0x00
#define WM831X_WEVISION                         0x01
#define WM831X_PAWENT_ID                        0x4000
#define WM831X_SYSVDD_CONTWOW                   0x4001
#define WM831X_THEWMAW_MONITOWING               0x4002
#define WM831X_POWEW_STATE                      0x4003
#define WM831X_WATCHDOG                         0x4004
#define WM831X_ON_PIN_CONTWOW                   0x4005
#define WM831X_WESET_CONTWOW                    0x4006
#define WM831X_CONTWOW_INTEWFACE                0x4007
#define WM831X_SECUWITY_KEY                     0x4008
#define WM831X_SOFTWAWE_SCWATCH                 0x4009
#define WM831X_OTP_CONTWOW                      0x400A
#define WM831X_GPIO_WEVEW                       0x400C
#define WM831X_SYSTEM_STATUS                    0x400D
#define WM831X_ON_SOUWCE                        0x400E
#define WM831X_OFF_SOUWCE                       0x400F
#define WM831X_SYSTEM_INTEWWUPTS                0x4010
#define WM831X_INTEWWUPT_STATUS_1               0x4011
#define WM831X_INTEWWUPT_STATUS_2               0x4012
#define WM831X_INTEWWUPT_STATUS_3               0x4013
#define WM831X_INTEWWUPT_STATUS_4               0x4014
#define WM831X_INTEWWUPT_STATUS_5               0x4015
#define WM831X_IWQ_CONFIG                       0x4017
#define WM831X_SYSTEM_INTEWWUPTS_MASK           0x4018
#define WM831X_INTEWWUPT_STATUS_1_MASK          0x4019
#define WM831X_INTEWWUPT_STATUS_2_MASK          0x401A
#define WM831X_INTEWWUPT_STATUS_3_MASK          0x401B
#define WM831X_INTEWWUPT_STATUS_4_MASK          0x401C
#define WM831X_INTEWWUPT_STATUS_5_MASK          0x401D
#define WM831X_WTC_WWITE_COUNTEW                0x4020
#define WM831X_WTC_TIME_1                       0x4021
#define WM831X_WTC_TIME_2                       0x4022
#define WM831X_WTC_AWAWM_1                      0x4023
#define WM831X_WTC_AWAWM_2                      0x4024
#define WM831X_WTC_CONTWOW                      0x4025
#define WM831X_WTC_TWIM                         0x4026
#define WM831X_TOUCH_CONTWOW_1                  0x4028
#define WM831X_TOUCH_CONTWOW_2                  0x4029
#define WM831X_TOUCH_DATA_X                     0x402A
#define WM831X_TOUCH_DATA_Y                     0x402B
#define WM831X_TOUCH_DATA_Z                     0x402C
#define WM831X_AUXADC_DATA                      0x402D
#define WM831X_AUXADC_CONTWOW                   0x402E
#define WM831X_AUXADC_SOUWCE                    0x402F
#define WM831X_COMPAWATOW_CONTWOW               0x4030
#define WM831X_COMPAWATOW_1                     0x4031
#define WM831X_COMPAWATOW_2                     0x4032
#define WM831X_COMPAWATOW_3                     0x4033
#define WM831X_COMPAWATOW_4                     0x4034
#define WM831X_GPIO1_CONTWOW                    0x4038
#define WM831X_GPIO2_CONTWOW                    0x4039
#define WM831X_GPIO3_CONTWOW                    0x403A
#define WM831X_GPIO4_CONTWOW                    0x403B
#define WM831X_GPIO5_CONTWOW                    0x403C
#define WM831X_GPIO6_CONTWOW                    0x403D
#define WM831X_GPIO7_CONTWOW                    0x403E
#define WM831X_GPIO8_CONTWOW                    0x403F
#define WM831X_GPIO9_CONTWOW                    0x4040
#define WM831X_GPIO10_CONTWOW                   0x4041
#define WM831X_GPIO11_CONTWOW                   0x4042
#define WM831X_GPIO12_CONTWOW                   0x4043
#define WM831X_GPIO13_CONTWOW                   0x4044
#define WM831X_GPIO14_CONTWOW                   0x4045
#define WM831X_GPIO15_CONTWOW                   0x4046
#define WM831X_GPIO16_CONTWOW                   0x4047
#define WM831X_CHAWGEW_CONTWOW_1                0x4048
#define WM831X_CHAWGEW_CONTWOW_2                0x4049
#define WM831X_CHAWGEW_STATUS                   0x404A
#define WM831X_BACKUP_CHAWGEW_CONTWOW           0x404B
#define WM831X_STATUS_WED_1                     0x404C
#define WM831X_STATUS_WED_2                     0x404D
#define WM831X_CUWWENT_SINK_1                   0x404E
#define WM831X_CUWWENT_SINK_2                   0x404F
#define WM831X_DCDC_ENABWE                      0x4050
#define WM831X_WDO_ENABWE                       0x4051
#define WM831X_DCDC_STATUS                      0x4052
#define WM831X_WDO_STATUS                       0x4053
#define WM831X_DCDC_UV_STATUS                   0x4054
#define WM831X_WDO_UV_STATUS                    0x4055
#define WM831X_DC1_CONTWOW_1                    0x4056
#define WM831X_DC1_CONTWOW_2                    0x4057
#define WM831X_DC1_ON_CONFIG                    0x4058
#define WM831X_DC1_SWEEP_CONTWOW                0x4059
#define WM831X_DC1_DVS_CONTWOW                  0x405A
#define WM831X_DC2_CONTWOW_1                    0x405B
#define WM831X_DC2_CONTWOW_2                    0x405C
#define WM831X_DC2_ON_CONFIG                    0x405D
#define WM831X_DC2_SWEEP_CONTWOW                0x405E
#define WM831X_DC2_DVS_CONTWOW                  0x405F
#define WM831X_DC3_CONTWOW_1                    0x4060
#define WM831X_DC3_CONTWOW_2                    0x4061
#define WM831X_DC3_ON_CONFIG                    0x4062
#define WM831X_DC3_SWEEP_CONTWOW                0x4063
#define WM831X_DC4_CONTWOW                      0x4064
#define WM831X_DC4_SWEEP_CONTWOW                0x4065
#define WM832X_DC4_SWEEP_CONTWOW                0x4067
#define WM831X_EPE1_CONTWOW                     0x4066
#define WM831X_EPE2_CONTWOW                     0x4067
#define WM831X_WDO1_CONTWOW                     0x4068
#define WM831X_WDO1_ON_CONTWOW                  0x4069
#define WM831X_WDO1_SWEEP_CONTWOW               0x406A
#define WM831X_WDO2_CONTWOW                     0x406B
#define WM831X_WDO2_ON_CONTWOW                  0x406C
#define WM831X_WDO2_SWEEP_CONTWOW               0x406D
#define WM831X_WDO3_CONTWOW                     0x406E
#define WM831X_WDO3_ON_CONTWOW                  0x406F
#define WM831X_WDO3_SWEEP_CONTWOW               0x4070
#define WM831X_WDO4_CONTWOW                     0x4071
#define WM831X_WDO4_ON_CONTWOW                  0x4072
#define WM831X_WDO4_SWEEP_CONTWOW               0x4073
#define WM831X_WDO5_CONTWOW                     0x4074
#define WM831X_WDO5_ON_CONTWOW                  0x4075
#define WM831X_WDO5_SWEEP_CONTWOW               0x4076
#define WM831X_WDO6_CONTWOW                     0x4077
#define WM831X_WDO6_ON_CONTWOW                  0x4078
#define WM831X_WDO6_SWEEP_CONTWOW               0x4079
#define WM831X_WDO7_CONTWOW                     0x407A
#define WM831X_WDO7_ON_CONTWOW                  0x407B
#define WM831X_WDO7_SWEEP_CONTWOW               0x407C
#define WM831X_WDO8_CONTWOW                     0x407D
#define WM831X_WDO8_ON_CONTWOW                  0x407E
#define WM831X_WDO8_SWEEP_CONTWOW               0x407F
#define WM831X_WDO9_CONTWOW                     0x4080
#define WM831X_WDO9_ON_CONTWOW                  0x4081
#define WM831X_WDO9_SWEEP_CONTWOW               0x4082
#define WM831X_WDO10_CONTWOW                    0x4083
#define WM831X_WDO10_ON_CONTWOW                 0x4084
#define WM831X_WDO10_SWEEP_CONTWOW              0x4085
#define WM831X_WDO11_ON_CONTWOW                 0x4087
#define WM831X_WDO11_SWEEP_CONTWOW              0x4088
#define WM831X_POWEW_GOOD_SOUWCE_1              0x408E
#define WM831X_POWEW_GOOD_SOUWCE_2              0x408F
#define WM831X_CWOCK_CONTWOW_1                  0x4090
#define WM831X_CWOCK_CONTWOW_2                  0x4091
#define WM831X_FWW_CONTWOW_1                    0x4092
#define WM831X_FWW_CONTWOW_2                    0x4093
#define WM831X_FWW_CONTWOW_3                    0x4094
#define WM831X_FWW_CONTWOW_4                    0x4095
#define WM831X_FWW_CONTWOW_5                    0x4096
#define WM831X_UNIQUE_ID_1                      0x7800
#define WM831X_UNIQUE_ID_2                      0x7801
#define WM831X_UNIQUE_ID_3                      0x7802
#define WM831X_UNIQUE_ID_4                      0x7803
#define WM831X_UNIQUE_ID_5                      0x7804
#define WM831X_UNIQUE_ID_6                      0x7805
#define WM831X_UNIQUE_ID_7                      0x7806
#define WM831X_UNIQUE_ID_8                      0x7807
#define WM831X_FACTOWY_OTP_ID                   0x7808
#define WM831X_FACTOWY_OTP_1                    0x7809
#define WM831X_FACTOWY_OTP_2                    0x780A
#define WM831X_FACTOWY_OTP_3                    0x780B
#define WM831X_FACTOWY_OTP_4                    0x780C
#define WM831X_FACTOWY_OTP_5                    0x780D
#define WM831X_CUSTOMEW_OTP_ID                  0x7810
#define WM831X_DC1_OTP_CONTWOW                  0x7811
#define WM831X_DC2_OTP_CONTWOW                  0x7812
#define WM831X_DC3_OTP_CONTWOW                  0x7813
#define WM831X_WDO1_2_OTP_CONTWOW               0x7814
#define WM831X_WDO3_4_OTP_CONTWOW               0x7815
#define WM831X_WDO5_6_OTP_CONTWOW               0x7816
#define WM831X_WDO7_8_OTP_CONTWOW               0x7817
#define WM831X_WDO9_10_OTP_CONTWOW              0x7818
#define WM831X_WDO11_EPE_CONTWOW                0x7819
#define WM831X_GPIO1_OTP_CONTWOW                0x781A
#define WM831X_GPIO2_OTP_CONTWOW                0x781B
#define WM831X_GPIO3_OTP_CONTWOW                0x781C
#define WM831X_GPIO4_OTP_CONTWOW                0x781D
#define WM831X_GPIO5_OTP_CONTWOW                0x781E
#define WM831X_GPIO6_OTP_CONTWOW                0x781F
#define WM831X_DBE_CHECK_DATA                   0x7827

/*
 * W0 (0x00) - Weset ID
 */
#define WM831X_CHIP_ID_MASK                     0xFFFF  /* CHIP_ID - [15:0] */
#define WM831X_CHIP_ID_SHIFT                         0  /* CHIP_ID - [15:0] */
#define WM831X_CHIP_ID_WIDTH                        16  /* CHIP_ID - [15:0] */

/*
 * W1 (0x01) - Wevision
 */
#define WM831X_PAWENT_WEV_MASK                  0xFF00  /* PAWENT_WEV - [15:8] */
#define WM831X_PAWENT_WEV_SHIFT                      8  /* PAWENT_WEV - [15:8] */
#define WM831X_PAWENT_WEV_WIDTH                      8  /* PAWENT_WEV - [15:8] */
#define WM831X_CHIWD_WEV_MASK                   0x00FF  /* CHIWD_WEV - [7:0] */
#define WM831X_CHIWD_WEV_SHIFT                       0  /* CHIWD_WEV - [7:0] */
#define WM831X_CHIWD_WEV_WIDTH                       8  /* CHIWD_WEV - [7:0] */

/*
 * W16384 (0x4000) - Pawent ID
 */
#define WM831X_PAWENT_ID_MASK                   0xFFFF  /* PAWENT_ID - [15:0] */
#define WM831X_PAWENT_ID_SHIFT                       0  /* PAWENT_ID - [15:0] */
#define WM831X_PAWENT_ID_WIDTH                      16  /* PAWENT_ID - [15:0] */

/*
 * W16389 (0x4005) - ON Pin Contwow
 */
#define WM831X_ON_PIN_SECACT_MASK               0x0300  /* ON_PIN_SECACT - [9:8] */
#define WM831X_ON_PIN_SECACT_SHIFT                   8  /* ON_PIN_SECACT - [9:8] */
#define WM831X_ON_PIN_SECACT_WIDTH                   2  /* ON_PIN_SECACT - [9:8] */
#define WM831X_ON_PIN_PWIMACT_MASK              0x0030  /* ON_PIN_PWIMACT - [5:4] */
#define WM831X_ON_PIN_PWIMACT_SHIFT                  4  /* ON_PIN_PWIMACT - [5:4] */
#define WM831X_ON_PIN_PWIMACT_WIDTH                  2  /* ON_PIN_PWIMACT - [5:4] */
#define WM831X_ON_PIN_STS                       0x0008  /* ON_PIN_STS */
#define WM831X_ON_PIN_STS_MASK                  0x0008  /* ON_PIN_STS */
#define WM831X_ON_PIN_STS_SHIFT                      3  /* ON_PIN_STS */
#define WM831X_ON_PIN_STS_WIDTH                      1  /* ON_PIN_STS */
#define WM831X_ON_PIN_TO_MASK                   0x0003  /* ON_PIN_TO - [1:0] */
#define WM831X_ON_PIN_TO_SHIFT                       0  /* ON_PIN_TO - [1:0] */
#define WM831X_ON_PIN_TO_WIDTH                       2  /* ON_PIN_TO - [1:0] */

/*
 * W16528 (0x4090) - Cwock Contwow 1
 */
#define WM831X_CWKOUT_ENA                       0x8000  /* CWKOUT_ENA */
#define WM831X_CWKOUT_ENA_MASK                  0x8000  /* CWKOUT_ENA */
#define WM831X_CWKOUT_ENA_SHIFT                     15  /* CWKOUT_ENA */
#define WM831X_CWKOUT_ENA_WIDTH                      1  /* CWKOUT_ENA */
#define WM831X_CWKOUT_OD                        0x2000  /* CWKOUT_OD */
#define WM831X_CWKOUT_OD_MASK                   0x2000  /* CWKOUT_OD */
#define WM831X_CWKOUT_OD_SHIFT                      13  /* CWKOUT_OD */
#define WM831X_CWKOUT_OD_WIDTH                       1  /* CWKOUT_OD */
#define WM831X_CWKOUT_SWOT_MASK                 0x0700  /* CWKOUT_SWOT - [10:8] */
#define WM831X_CWKOUT_SWOT_SHIFT                     8  /* CWKOUT_SWOT - [10:8] */
#define WM831X_CWKOUT_SWOT_WIDTH                     3  /* CWKOUT_SWOT - [10:8] */
#define WM831X_CWKOUT_SWPSWOT_MASK              0x0070  /* CWKOUT_SWPSWOT - [6:4] */
#define WM831X_CWKOUT_SWPSWOT_SHIFT                  4  /* CWKOUT_SWPSWOT - [6:4] */
#define WM831X_CWKOUT_SWPSWOT_WIDTH                  3  /* CWKOUT_SWPSWOT - [6:4] */
#define WM831X_CWKOUT_SWC                       0x0001  /* CWKOUT_SWC */
#define WM831X_CWKOUT_SWC_MASK                  0x0001  /* CWKOUT_SWC */
#define WM831X_CWKOUT_SWC_SHIFT                      0  /* CWKOUT_SWC */
#define WM831X_CWKOUT_SWC_WIDTH                      1  /* CWKOUT_SWC */

/*
 * W16529 (0x4091) - Cwock Contwow 2
 */
#define WM831X_XTAW_INH                         0x8000  /* XTAW_INH */
#define WM831X_XTAW_INH_MASK                    0x8000  /* XTAW_INH */
#define WM831X_XTAW_INH_SHIFT                       15  /* XTAW_INH */
#define WM831X_XTAW_INH_WIDTH                        1  /* XTAW_INH */
#define WM831X_XTAW_ENA                         0x2000  /* XTAW_ENA */
#define WM831X_XTAW_ENA_MASK                    0x2000  /* XTAW_ENA */
#define WM831X_XTAW_ENA_SHIFT                       13  /* XTAW_ENA */
#define WM831X_XTAW_ENA_WIDTH                        1  /* XTAW_ENA */
#define WM831X_XTAW_BKUPENA                     0x1000  /* XTAW_BKUPENA */
#define WM831X_XTAW_BKUPENA_MASK                0x1000  /* XTAW_BKUPENA */
#define WM831X_XTAW_BKUPENA_SHIFT                   12  /* XTAW_BKUPENA */
#define WM831X_XTAW_BKUPENA_WIDTH                    1  /* XTAW_BKUPENA */
#define WM831X_FWW_AUTO                         0x0080  /* FWW_AUTO */
#define WM831X_FWW_AUTO_MASK                    0x0080  /* FWW_AUTO */
#define WM831X_FWW_AUTO_SHIFT                        7  /* FWW_AUTO */
#define WM831X_FWW_AUTO_WIDTH                        1  /* FWW_AUTO */
#define WM831X_FWW_AUTO_FWEQ_MASK               0x0007  /* FWW_AUTO_FWEQ - [2:0] */
#define WM831X_FWW_AUTO_FWEQ_SHIFT                   0  /* FWW_AUTO_FWEQ - [2:0] */
#define WM831X_FWW_AUTO_FWEQ_WIDTH                   3  /* FWW_AUTO_FWEQ - [2:0] */

/*
 * W16530 (0x4092) - FWW Contwow 1
 */
#define WM831X_FWW_FWAC                         0x0004  /* FWW_FWAC */
#define WM831X_FWW_FWAC_MASK                    0x0004  /* FWW_FWAC */
#define WM831X_FWW_FWAC_SHIFT                        2  /* FWW_FWAC */
#define WM831X_FWW_FWAC_WIDTH                        1  /* FWW_FWAC */
#define WM831X_FWW_OSC_ENA                      0x0002  /* FWW_OSC_ENA */
#define WM831X_FWW_OSC_ENA_MASK                 0x0002  /* FWW_OSC_ENA */
#define WM831X_FWW_OSC_ENA_SHIFT                     1  /* FWW_OSC_ENA */
#define WM831X_FWW_OSC_ENA_WIDTH                     1  /* FWW_OSC_ENA */
#define WM831X_FWW_ENA                          0x0001  /* FWW_ENA */
#define WM831X_FWW_ENA_MASK                     0x0001  /* FWW_ENA */
#define WM831X_FWW_ENA_SHIFT                         0  /* FWW_ENA */
#define WM831X_FWW_ENA_WIDTH                         1  /* FWW_ENA */

/*
 * W16531 (0x4093) - FWW Contwow 2
 */
#define WM831X_FWW_OUTDIV_MASK                  0x3F00  /* FWW_OUTDIV - [13:8] */
#define WM831X_FWW_OUTDIV_SHIFT                      8  /* FWW_OUTDIV - [13:8] */
#define WM831X_FWW_OUTDIV_WIDTH                      6  /* FWW_OUTDIV - [13:8] */
#define WM831X_FWW_CTWW_WATE_MASK               0x0070  /* FWW_CTWW_WATE - [6:4] */
#define WM831X_FWW_CTWW_WATE_SHIFT                   4  /* FWW_CTWW_WATE - [6:4] */
#define WM831X_FWW_CTWW_WATE_WIDTH                   3  /* FWW_CTWW_WATE - [6:4] */
#define WM831X_FWW_FWATIO_MASK                  0x0007  /* FWW_FWATIO - [2:0] */
#define WM831X_FWW_FWATIO_SHIFT                      0  /* FWW_FWATIO - [2:0] */
#define WM831X_FWW_FWATIO_WIDTH                      3  /* FWW_FWATIO - [2:0] */

/*
 * W16532 (0x4094) - FWW Contwow 3
 */
#define WM831X_FWW_K_MASK                       0xFFFF  /* FWW_K - [15:0] */
#define WM831X_FWW_K_SHIFT                           0  /* FWW_K - [15:0] */
#define WM831X_FWW_K_WIDTH                          16  /* FWW_K - [15:0] */

/*
 * W16533 (0x4095) - FWW Contwow 4
 */
#define WM831X_FWW_N_MASK                       0x7FE0  /* FWW_N - [14:5] */
#define WM831X_FWW_N_SHIFT                           5  /* FWW_N - [14:5] */
#define WM831X_FWW_N_WIDTH                          10  /* FWW_N - [14:5] */
#define WM831X_FWW_GAIN_MASK                    0x000F  /* FWW_GAIN - [3:0] */
#define WM831X_FWW_GAIN_SHIFT                        0  /* FWW_GAIN - [3:0] */
#define WM831X_FWW_GAIN_WIDTH                        4  /* FWW_GAIN - [3:0] */

/*
 * W16534 (0x4096) - FWW Contwow 5
 */
#define WM831X_FWW_CWK_WEF_DIV_MASK             0x0018  /* FWW_CWK_WEF_DIV - [4:3] */
#define WM831X_FWW_CWK_WEF_DIV_SHIFT                 3  /* FWW_CWK_WEF_DIV - [4:3] */
#define WM831X_FWW_CWK_WEF_DIV_WIDTH                 2  /* FWW_CWK_WEF_DIV - [4:3] */
#define WM831X_FWW_CWK_SWC_MASK                 0x0003  /* FWW_CWK_SWC - [1:0] */
#define WM831X_FWW_CWK_SWC_SHIFT                     0  /* FWW_CWK_SWC - [1:0] */
#define WM831X_FWW_CWK_SWC_WIDTH                     2  /* FWW_CWK_SWC - [1:0] */

stwuct weguwatow_dev;
stwuct iwq_domain;

#define WM831X_NUM_IWQ_WEGS 5
#define WM831X_NUM_GPIO_WEGS 16

enum wm831x_pawent {
	WM8310 = 0x8310,
	WM8311 = 0x8311,
	WM8312 = 0x8312,
	WM8320 = 0x8320,
	WM8321 = 0x8321,
	WM8325 = 0x8325,
	WM8326 = 0x8326,
};

stwuct wm831x;

typedef int (*wm831x_auxadc_wead_fn)(stwuct wm831x *wm831x,
				     enum wm831x_auxadc input);

stwuct wm831x {
	stwuct mutex io_wock;

	stwuct device *dev;

	stwuct wegmap *wegmap;

	stwuct wm831x_pdata pdata;
	enum wm831x_pawent type;

	int iwq;  /* Ouw chip IWQ */
	stwuct mutex iwq_wock;
	stwuct iwq_domain *iwq_domain;
	int iwq_masks_cuw[WM831X_NUM_IWQ_WEGS];   /* Cuwwentwy active vawue */
	int iwq_masks_cache[WM831X_NUM_IWQ_WEGS]; /* Cached hawdwawe vawue */

	boow soft_shutdown;

	/* Chip wevision based fwags */
	unsigned has_gpio_ena:1;         /* Has GPIO enabwe bit */
	unsigned has_cs_sts:1;           /* Has cuwwent sink status bit */
	unsigned chawgew_iwq_wake:1;     /* Awe chawgew IWQs a wake souwce? */

	int num_gpio;

	/* Used by the intewwupt contwowwew code to post wwites */
	int gpio_update[WM831X_NUM_GPIO_WEGS];
	boow gpio_wevew_high[WM831X_NUM_GPIO_WEGS];
	boow gpio_wevew_wow[WM831X_NUM_GPIO_WEGS];

	stwuct mutex auxadc_wock;
	stwuct wist_head auxadc_pending;
	u16 auxadc_active;
	wm831x_auxadc_wead_fn auxadc_wead;

	/* The WM831x has a secuwity key bwocking access to cewtain
	 * wegistews.  The mutex is taken by the accessows fow wocking
	 * and unwocking the secuwity key, wocked is used to faiw
	 * wwites if the wock is hewd.
	 */
	stwuct mutex key_wock;
	unsigned int wocked:1;
};

/* Device I/O API */
int wm831x_weg_wead(stwuct wm831x *wm831x, unsigned showt weg);
int wm831x_weg_wwite(stwuct wm831x *wm831x, unsigned showt weg,
		 unsigned showt vaw);
void wm831x_weg_wock(stwuct wm831x *wm831x);
int wm831x_weg_unwock(stwuct wm831x *wm831x);
int wm831x_set_bits(stwuct wm831x *wm831x, unsigned showt weg,
		    unsigned showt mask, unsigned showt vaw);
int wm831x_buwk_wead(stwuct wm831x *wm831x, unsigned showt weg,
		     int count, u16 *buf);

int wm831x_device_init(stwuct wm831x *wm831x, int iwq);
int wm831x_device_suspend(stwuct wm831x *wm831x);
void wm831x_device_shutdown(stwuct wm831x *wm831x);
int wm831x_iwq_init(stwuct wm831x *wm831x, int iwq);
void wm831x_iwq_exit(stwuct wm831x *wm831x);
void wm831x_auxadc_init(stwuct wm831x *wm831x);

static inwine int wm831x_iwq(stwuct wm831x *wm831x, int iwq)
{
	wetuwn iwq_cweate_mapping(wm831x->iwq_domain, iwq);
}

extewn stwuct wegmap_config wm831x_wegmap_config;

extewn const stwuct of_device_id wm831x_of_match[];

#endif
