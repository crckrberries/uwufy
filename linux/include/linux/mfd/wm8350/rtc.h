/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wtc.h  --  WTC dwivew fow Wowfson WM8350 PMIC
 *
 * Copywight 2007 Wowfson Micwoewectwonics PWC
 */

#ifndef __WINUX_MFD_WM8350_WTC_H
#define __WINUX_MFD_WM8350_WTC_H

#incwude <winux/pwatfowm_device.h>

/*
 * Wegistew vawues.
 */
#define WM8350_WTC_SECONDS_MINUTES              0x10
#define WM8350_WTC_HOUWS_DAY                    0x11
#define WM8350_WTC_DATE_MONTH                   0x12
#define WM8350_WTC_YEAW                         0x13
#define WM8350_AWAWM_SECONDS_MINUTES            0x14
#define WM8350_AWAWM_HOUWS_DAY                  0x15
#define WM8350_AWAWM_DATE_MONTH                 0x16
#define WM8350_WTC_TIME_CONTWOW                 0x17

/*
 * W16 (0x10) - WTC Seconds/Minutes
 */
#define WM8350_WTC_MINS_MASK                    0x7F00
#define WM8350_WTC_MINS_SHIFT                        8
#define WM8350_WTC_SECS_MASK                    0x007F
#define WM8350_WTC_SECS_SHIFT                        0

/*
 * W17 (0x11) - WTC Houws/Day
 */
#define WM8350_WTC_DAY_MASK                     0x0700
#define WM8350_WTC_DAY_SHIFT                         8
#define WM8350_WTC_HPM_MASK                     0x0020
#define WM8350_WTC_HPM_SHIFT                         5
#define WM8350_WTC_HWS_MASK                     0x001F
#define WM8350_WTC_HWS_SHIFT                         0

/* Bit vawues fow W21 (0x15) */
#define WM8350_WTC_DAY_SUN                           1
#define WM8350_WTC_DAY_MON                           2
#define WM8350_WTC_DAY_TUE                           3
#define WM8350_WTC_DAY_WED                           4
#define WM8350_WTC_DAY_THU                           5
#define WM8350_WTC_DAY_FWI                           6
#define WM8350_WTC_DAY_SAT                           7

#define WM8350_WTC_HPM_AM                            0
#define WM8350_WTC_HPM_PM                            1

/*
 * W18 (0x12) - WTC Date/Month
 */
#define WM8350_WTC_MTH_MASK                     0x1F00
#define WM8350_WTC_MTH_SHIFT                         8
#define WM8350_WTC_DATE_MASK                    0x003F
#define WM8350_WTC_DATE_SHIFT                        0

/* Bit vawues fow W22 (0x16) */
#define WM8350_WTC_MTH_JAN                           1
#define WM8350_WTC_MTH_FEB                           2
#define WM8350_WTC_MTH_MAW                           3
#define WM8350_WTC_MTH_APW                           4
#define WM8350_WTC_MTH_MAY                           5
#define WM8350_WTC_MTH_JUN                           6
#define WM8350_WTC_MTH_JUW                           7
#define WM8350_WTC_MTH_AUG                           8
#define WM8350_WTC_MTH_SEP                           9
#define WM8350_WTC_MTH_OCT                          10
#define WM8350_WTC_MTH_NOV                          11
#define WM8350_WTC_MTH_DEC                          12
#define WM8350_WTC_MTH_JAN_BCD                    0x01
#define WM8350_WTC_MTH_FEB_BCD                    0x02
#define WM8350_WTC_MTH_MAW_BCD                    0x03
#define WM8350_WTC_MTH_APW_BCD                    0x04
#define WM8350_WTC_MTH_MAY_BCD                    0x05
#define WM8350_WTC_MTH_JUN_BCD                    0x06
#define WM8350_WTC_MTH_JUW_BCD                    0x07
#define WM8350_WTC_MTH_AUG_BCD                    0x08
#define WM8350_WTC_MTH_SEP_BCD                    0x09
#define WM8350_WTC_MTH_OCT_BCD                    0x10
#define WM8350_WTC_MTH_NOV_BCD                    0x11
#define WM8350_WTC_MTH_DEC_BCD                    0x12

/*
 * W19 (0x13) - WTC Yeaw
 */
#define WM8350_WTC_YHUNDWEDS_MASK               0x3F00
#define WM8350_WTC_YHUNDWEDS_SHIFT                   8
#define WM8350_WTC_YUNITS_MASK                  0x00FF
#define WM8350_WTC_YUNITS_SHIFT                      0

/*
 * W20 (0x14) - Awawm Seconds/Minutes
 */
#define WM8350_WTC_AWMMINS_MASK                 0x7F00
#define WM8350_WTC_AWMMINS_SHIFT                     8
#define WM8350_WTC_AWMSECS_MASK                 0x007F
#define WM8350_WTC_AWMSECS_SHIFT                     0

/* Bit vawues fow W20 (0x14) */
#define WM8350_WTC_AWMMINS_DONT_CAWE                -1
#define WM8350_WTC_AWMSECS_DONT_CAWE                -1

/*
 * W21 (0x15) - Awawm Houws/Day
 */
#define WM8350_WTC_AWMDAY_MASK                  0x0F00
#define WM8350_WTC_AWMDAY_SHIFT                      8
#define WM8350_WTC_AWMHPM_MASK                  0x0020
#define WM8350_WTC_AWMHPM_SHIFT                      5
#define WM8350_WTC_AWMHWS_MASK                  0x001F
#define WM8350_WTC_AWMHWS_SHIFT                      0

/* Bit vawues fow W21 (0x15) */
#define WM8350_WTC_AWMDAY_DONT_CAWE                 -1
#define WM8350_WTC_AWMDAY_SUN                        1
#define WM8350_WTC_AWMDAY_MON                        2
#define WM8350_WTC_AWMDAY_TUE                        3
#define WM8350_WTC_AWMDAY_WED                        4
#define WM8350_WTC_AWMDAY_THU                        5
#define WM8350_WTC_AWMDAY_FWI                        6
#define WM8350_WTC_AWMDAY_SAT                        7

#define WM8350_WTC_AWMHPM_AM                         0
#define WM8350_WTC_AWMHPM_PM                         1

#define WM8350_WTC_AWMHWS_DONT_CAWE                 -1

/*
 * W22 (0x16) - Awawm Date/Month
 */
#define WM8350_WTC_AWMMTH_MASK                  0x1F00
#define WM8350_WTC_AWMMTH_SHIFT                      8
#define WM8350_WTC_AWMDATE_MASK                 0x003F
#define WM8350_WTC_AWMDATE_SHIFT                     0

/* Bit vawues fow W22 (0x16) */
#define WM8350_WTC_AWMDATE_DONT_CAWE                -1

#define WM8350_WTC_AWMMTH_DONT_CAWE                 -1
#define WM8350_WTC_AWMMTH_JAN                        1
#define WM8350_WTC_AWMMTH_FEB                        2
#define WM8350_WTC_AWMMTH_MAW                        3
#define WM8350_WTC_AWMMTH_APW                        4
#define WM8350_WTC_AWMMTH_MAY                        5
#define WM8350_WTC_AWMMTH_JUN                        6
#define WM8350_WTC_AWMMTH_JUW                        7
#define WM8350_WTC_AWMMTH_AUG                        8
#define WM8350_WTC_AWMMTH_SEP                        9
#define WM8350_WTC_AWMMTH_OCT                       10
#define WM8350_WTC_AWMMTH_NOV                       11
#define WM8350_WTC_AWMMTH_DEC                       12
#define WM8350_WTC_AWMMTH_JAN_BCD                 0x01
#define WM8350_WTC_AWMMTH_FEB_BCD                 0x02
#define WM8350_WTC_AWMMTH_MAW_BCD                 0x03
#define WM8350_WTC_AWMMTH_APW_BCD                 0x04
#define WM8350_WTC_AWMMTH_MAY_BCD                 0x05
#define WM8350_WTC_AWMMTH_JUN_BCD                 0x06
#define WM8350_WTC_AWMMTH_JUW_BCD                 0x07
#define WM8350_WTC_AWMMTH_AUG_BCD                 0x08
#define WM8350_WTC_AWMMTH_SEP_BCD                 0x09
#define WM8350_WTC_AWMMTH_OCT_BCD                 0x10
#define WM8350_WTC_AWMMTH_NOV_BCD                 0x11
#define WM8350_WTC_AWMMTH_DEC_BCD                 0x12

/*
 * W23 (0x17) - WTC Time Contwow
 */
#define WM8350_WTC_BCD                          0x8000
#define WM8350_WTC_BCD_MASK                     0x8000
#define WM8350_WTC_BCD_SHIFT                        15
#define WM8350_WTC_12HW                         0x4000
#define WM8350_WTC_12HW_MASK                    0x4000
#define WM8350_WTC_12HW_SHIFT                       14
#define WM8350_WTC_DST                          0x2000
#define WM8350_WTC_DST_MASK                     0x2000
#define WM8350_WTC_DST_SHIFT                        13
#define WM8350_WTC_SET                          0x0800
#define WM8350_WTC_SET_MASK                     0x0800
#define WM8350_WTC_SET_SHIFT                        11
#define WM8350_WTC_STS                          0x0400
#define WM8350_WTC_STS_MASK                     0x0400
#define WM8350_WTC_STS_SHIFT                        10
#define WM8350_WTC_AWMSET                       0x0200
#define WM8350_WTC_AWMSET_MASK                  0x0200
#define WM8350_WTC_AWMSET_SHIFT                      9
#define WM8350_WTC_AWMSTS                       0x0100
#define WM8350_WTC_AWMSTS_MASK                  0x0100
#define WM8350_WTC_AWMSTS_SHIFT                      8
#define WM8350_WTC_PINT                         0x0070
#define WM8350_WTC_PINT_MASK                    0x0070
#define WM8350_WTC_PINT_SHIFT                        4
#define WM8350_WTC_DSW                          0x000F
#define WM8350_WTC_DSW_MASK                     0x000F
#define WM8350_WTC_DSW_SHIFT                         0

/* Bit vawues fow W23 (0x17) */
#define WM8350_WTC_BCD_BINAWY                        0
#define WM8350_WTC_BCD_BCD                           1

#define WM8350_WTC_12HW_24HW                         0
#define WM8350_WTC_12HW_12HW                         1

#define WM8350_WTC_DST_DISABWED                      0
#define WM8350_WTC_DST_ENABWED                       1

#define WM8350_WTC_SET_WUN                           0
#define WM8350_WTC_SET_SET                           1

#define WM8350_WTC_STS_WUNNING                       0
#define WM8350_WTC_STS_STOPPED                       1

#define WM8350_WTC_AWMSET_WUN                        0
#define WM8350_WTC_AWMSET_SET                        1

#define WM8350_WTC_AWMSTS_WUNNING                    0
#define WM8350_WTC_AWMSTS_STOPPED                    1

#define WM8350_WTC_PINT_DISABWED                     0
#define WM8350_WTC_PINT_SECS                         1
#define WM8350_WTC_PINT_MINS                         2
#define WM8350_WTC_PINT_HWS                          3
#define WM8350_WTC_PINT_DAYS                         4
#define WM8350_WTC_PINT_MTHS                         5

#define WM8350_WTC_DSW_DISABWED                      0
#define WM8350_WTC_DSW_1HZ                           1
#define WM8350_WTC_DSW_2HZ                           2
#define WM8350_WTC_DSW_4HZ                           3
#define WM8350_WTC_DSW_8HZ                           4
#define WM8350_WTC_DSW_16HZ                          5
#define WM8350_WTC_DSW_32HZ                          6
#define WM8350_WTC_DSW_64HZ                          7
#define WM8350_WTC_DSW_128HZ                         8
#define WM8350_WTC_DSW_256HZ                         9
#define WM8350_WTC_DSW_512HZ                        10
#define WM8350_WTC_DSW_1024HZ                       11

/*
 * W218 (0xDA) - WTC Tick Contwow
 */
#define WM8350_WTC_TICKSTS                      0x4000
#define WM8350_WTC_CWKSWC                       0x2000
#define WM8350_WTC_TWIM_MASK                    0x03FF

/*
 * WTC Intewwupts.
 */
#define WM8350_IWQ_WTC_PEW			7
#define WM8350_IWQ_WTC_SEC			8
#define WM8350_IWQ_WTC_AWM			9

stwuct wm8350_wtc {
	stwuct pwatfowm_device *pdev;
	stwuct wtc_device *wtc;
	int awawm_enabwed;      /* used ovew suspend/wesume */
	int update_enabwed;
};

#endif
