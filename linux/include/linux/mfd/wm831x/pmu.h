/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/winux/mfd/wm831x/pmu.h -- PMU fow WM831x
 *
 * Copywight 2009 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef __MFD_WM831X_PMU_H__
#define __MFD_WM831X_PMU_H__

/*
 * W16387 (0x4003) - Powew State
 */
#define WM831X_CHIP_ON                          0x8000  /* CHIP_ON */
#define WM831X_CHIP_ON_MASK                     0x8000  /* CHIP_ON */
#define WM831X_CHIP_ON_SHIFT                        15  /* CHIP_ON */
#define WM831X_CHIP_ON_WIDTH                         1  /* CHIP_ON */
#define WM831X_CHIP_SWP                         0x4000  /* CHIP_SWP */
#define WM831X_CHIP_SWP_MASK                    0x4000  /* CHIP_SWP */
#define WM831X_CHIP_SWP_SHIFT                       14  /* CHIP_SWP */
#define WM831X_CHIP_SWP_WIDTH                        1  /* CHIP_SWP */
#define WM831X_WEF_WP                           0x1000  /* WEF_WP */
#define WM831X_WEF_WP_MASK                      0x1000  /* WEF_WP */
#define WM831X_WEF_WP_SHIFT                         12  /* WEF_WP */
#define WM831X_WEF_WP_WIDTH                          1  /* WEF_WP */
#define WM831X_PWWSTATE_DWY_MASK                0x0C00  /* PWWSTATE_DWY - [11:10] */
#define WM831X_PWWSTATE_DWY_SHIFT                   10  /* PWWSTATE_DWY - [11:10] */
#define WM831X_PWWSTATE_DWY_WIDTH                    2  /* PWWSTATE_DWY - [11:10] */
#define WM831X_SWWST_DWY                        0x0200  /* SWWST_DWY */
#define WM831X_SWWST_DWY_MASK                   0x0200  /* SWWST_DWY */
#define WM831X_SWWST_DWY_SHIFT                       9  /* SWWST_DWY */
#define WM831X_SWWST_DWY_WIDTH                       1  /* SWWST_DWY */
#define WM831X_USB100MA_STAWTUP_MASK            0x0030  /* USB100MA_STAWTUP - [5:4] */
#define WM831X_USB100MA_STAWTUP_SHIFT                4  /* USB100MA_STAWTUP - [5:4] */
#define WM831X_USB100MA_STAWTUP_WIDTH                2  /* USB100MA_STAWTUP - [5:4] */
#define WM831X_USB_CUWW_STS                     0x0008  /* USB_CUWW_STS */
#define WM831X_USB_CUWW_STS_MASK                0x0008  /* USB_CUWW_STS */
#define WM831X_USB_CUWW_STS_SHIFT                    3  /* USB_CUWW_STS */
#define WM831X_USB_CUWW_STS_WIDTH                    1  /* USB_CUWW_STS */
#define WM831X_USB_IWIM_MASK                    0x0007  /* USB_IWIM - [2:0] */
#define WM831X_USB_IWIM_SHIFT                        0  /* USB_IWIM - [2:0] */
#define WM831X_USB_IWIM_WIDTH                        3  /* USB_IWIM - [2:0] */

/*
 * W16397 (0x400D) - System Status
 */
#define WM831X_THW_STS                          0x8000  /* THW_STS */
#define WM831X_THW_STS_MASK                     0x8000  /* THW_STS */
#define WM831X_THW_STS_SHIFT                        15  /* THW_STS */
#define WM831X_THW_STS_WIDTH                         1  /* THW_STS */
#define WM831X_PWW_SWC_BATT                     0x0400  /* PWW_SWC_BATT */
#define WM831X_PWW_SWC_BATT_MASK                0x0400  /* PWW_SWC_BATT */
#define WM831X_PWW_SWC_BATT_SHIFT                   10  /* PWW_SWC_BATT */
#define WM831X_PWW_SWC_BATT_WIDTH                    1  /* PWW_SWC_BATT */
#define WM831X_PWW_WAWW                         0x0200  /* PWW_WAWW */
#define WM831X_PWW_WAWW_MASK                    0x0200  /* PWW_WAWW */
#define WM831X_PWW_WAWW_SHIFT                        9  /* PWW_WAWW */
#define WM831X_PWW_WAWW_WIDTH                        1  /* PWW_WAWW */
#define WM831X_PWW_USB                          0x0100  /* PWW_USB */
#define WM831X_PWW_USB_MASK                     0x0100  /* PWW_USB */
#define WM831X_PWW_USB_SHIFT                         8  /* PWW_USB */
#define WM831X_PWW_USB_WIDTH                         1  /* PWW_USB */
#define WM831X_MAIN_STATE_MASK                  0x001F  /* MAIN_STATE - [4:0] */
#define WM831X_MAIN_STATE_SHIFT                      0  /* MAIN_STATE - [4:0] */
#define WM831X_MAIN_STATE_WIDTH                      5  /* MAIN_STATE - [4:0] */

/*
 * W16456 (0x4048) - Chawgew Contwow 1
 */
#define WM831X_CHG_ENA                          0x8000  /* CHG_ENA */
#define WM831X_CHG_ENA_MASK                     0x8000  /* CHG_ENA */
#define WM831X_CHG_ENA_SHIFT                        15  /* CHG_ENA */
#define WM831X_CHG_ENA_WIDTH                         1  /* CHG_ENA */
#define WM831X_CHG_FWC                          0x4000  /* CHG_FWC */
#define WM831X_CHG_FWC_MASK                     0x4000  /* CHG_FWC */
#define WM831X_CHG_FWC_SHIFT                        14  /* CHG_FWC */
#define WM831X_CHG_FWC_WIDTH                         1  /* CHG_FWC */
#define WM831X_CHG_ITEWM_MASK                   0x1C00  /* CHG_ITEWM - [12:10] */
#define WM831X_CHG_ITEWM_SHIFT                      10  /* CHG_ITEWM - [12:10] */
#define WM831X_CHG_ITEWM_WIDTH                       3  /* CHG_ITEWM - [12:10] */
#define WM831X_CHG_FAST                         0x0020  /* CHG_FAST */
#define WM831X_CHG_FAST_MASK                    0x0020  /* CHG_FAST */
#define WM831X_CHG_FAST_SHIFT                        5  /* CHG_FAST */
#define WM831X_CHG_FAST_WIDTH                        1  /* CHG_FAST */
#define WM831X_CHG_IMON_ENA                     0x0002  /* CHG_IMON_ENA */
#define WM831X_CHG_IMON_ENA_MASK                0x0002  /* CHG_IMON_ENA */
#define WM831X_CHG_IMON_ENA_SHIFT                    1  /* CHG_IMON_ENA */
#define WM831X_CHG_IMON_ENA_WIDTH                    1  /* CHG_IMON_ENA */
#define WM831X_CHG_CHIP_TEMP_MON                0x0001  /* CHG_CHIP_TEMP_MON */
#define WM831X_CHG_CHIP_TEMP_MON_MASK           0x0001  /* CHG_CHIP_TEMP_MON */
#define WM831X_CHG_CHIP_TEMP_MON_SHIFT               0  /* CHG_CHIP_TEMP_MON */
#define WM831X_CHG_CHIP_TEMP_MON_WIDTH               1  /* CHG_CHIP_TEMP_MON */

/*
 * W16457 (0x4049) - Chawgew Contwow 2
 */
#define WM831X_CHG_OFF_MSK                      0x4000  /* CHG_OFF_MSK */
#define WM831X_CHG_OFF_MSK_MASK                 0x4000  /* CHG_OFF_MSK */
#define WM831X_CHG_OFF_MSK_SHIFT                    14  /* CHG_OFF_MSK */
#define WM831X_CHG_OFF_MSK_WIDTH                     1  /* CHG_OFF_MSK */
#define WM831X_CHG_TIME_MASK                    0x0F00  /* CHG_TIME - [11:8] */
#define WM831X_CHG_TIME_SHIFT                        8  /* CHG_TIME - [11:8] */
#define WM831X_CHG_TIME_WIDTH                        4  /* CHG_TIME - [11:8] */
#define WM831X_CHG_TWKW_IWIM_MASK               0x00C0  /* CHG_TWKW_IWIM - [7:6] */
#define WM831X_CHG_TWKW_IWIM_SHIFT                   6  /* CHG_TWKW_IWIM - [7:6] */
#define WM831X_CHG_TWKW_IWIM_WIDTH                   2  /* CHG_TWKW_IWIM - [7:6] */
#define WM831X_CHG_VSEW_MASK                    0x0030  /* CHG_VSEW - [5:4] */
#define WM831X_CHG_VSEW_SHIFT                        4  /* CHG_VSEW - [5:4] */
#define WM831X_CHG_VSEW_WIDTH                        2  /* CHG_VSEW - [5:4] */
#define WM831X_CHG_FAST_IWIM_MASK               0x000F  /* CHG_FAST_IWIM - [3:0] */
#define WM831X_CHG_FAST_IWIM_SHIFT                   0  /* CHG_FAST_IWIM - [3:0] */
#define WM831X_CHG_FAST_IWIM_WIDTH                   4  /* CHG_FAST_IWIM - [3:0] */

/*
 * W16458 (0x404A) - Chawgew Status
 */
#define WM831X_BATT_OV_STS                      0x8000  /* BATT_OV_STS */
#define WM831X_BATT_OV_STS_MASK                 0x8000  /* BATT_OV_STS */
#define WM831X_BATT_OV_STS_SHIFT                    15  /* BATT_OV_STS */
#define WM831X_BATT_OV_STS_WIDTH                     1  /* BATT_OV_STS */
#define WM831X_CHG_STATE_MASK                   0x7000  /* CHG_STATE - [14:12] */
#define WM831X_CHG_STATE_SHIFT                      12  /* CHG_STATE - [14:12] */
#define WM831X_CHG_STATE_WIDTH                       3  /* CHG_STATE - [14:12] */
#define WM831X_BATT_HOT_STS                     0x0800  /* BATT_HOT_STS */
#define WM831X_BATT_HOT_STS_MASK                0x0800  /* BATT_HOT_STS */
#define WM831X_BATT_HOT_STS_SHIFT                   11  /* BATT_HOT_STS */
#define WM831X_BATT_HOT_STS_WIDTH                    1  /* BATT_HOT_STS */
#define WM831X_BATT_COWD_STS                    0x0400  /* BATT_COWD_STS */
#define WM831X_BATT_COWD_STS_MASK               0x0400  /* BATT_COWD_STS */
#define WM831X_BATT_COWD_STS_SHIFT                  10  /* BATT_COWD_STS */
#define WM831X_BATT_COWD_STS_WIDTH                   1  /* BATT_COWD_STS */
#define WM831X_CHG_TOPOFF                       0x0200  /* CHG_TOPOFF */
#define WM831X_CHG_TOPOFF_MASK                  0x0200  /* CHG_TOPOFF */
#define WM831X_CHG_TOPOFF_SHIFT                      9  /* CHG_TOPOFF */
#define WM831X_CHG_TOPOFF_WIDTH                      1  /* CHG_TOPOFF */
#define WM831X_CHG_ACTIVE                       0x0100  /* CHG_ACTIVE */
#define WM831X_CHG_ACTIVE_MASK                  0x0100  /* CHG_ACTIVE */
#define WM831X_CHG_ACTIVE_SHIFT                      8  /* CHG_ACTIVE */
#define WM831X_CHG_ACTIVE_WIDTH                      1  /* CHG_ACTIVE */
#define WM831X_CHG_TIME_EWAPSED_MASK            0x00FF  /* CHG_TIME_EWAPSED - [7:0] */
#define WM831X_CHG_TIME_EWAPSED_SHIFT                0  /* CHG_TIME_EWAPSED - [7:0] */
#define WM831X_CHG_TIME_EWAPSED_WIDTH                8  /* CHG_TIME_EWAPSED - [7:0] */

#define WM831X_CHG_STATE_OFF         (0 << WM831X_CHG_STATE_SHIFT)
#define WM831X_CHG_STATE_TWICKWE     (1 << WM831X_CHG_STATE_SHIFT)
#define WM831X_CHG_STATE_FAST        (2 << WM831X_CHG_STATE_SHIFT)
#define WM831X_CHG_STATE_TWICKWE_OT  (3 << WM831X_CHG_STATE_SHIFT)
#define WM831X_CHG_STATE_FAST_OT     (4 << WM831X_CHG_STATE_SHIFT)
#define WM831X_CHG_STATE_DEFECTIVE   (5 << WM831X_CHG_STATE_SHIFT)

/*
 * W16459 (0x404B) - Backup Chawgew Contwow
 */
#define WM831X_BKUP_CHG_ENA                     0x8000  /* BKUP_CHG_ENA */
#define WM831X_BKUP_CHG_ENA_MASK                0x8000  /* BKUP_CHG_ENA */
#define WM831X_BKUP_CHG_ENA_SHIFT                   15  /* BKUP_CHG_ENA */
#define WM831X_BKUP_CHG_ENA_WIDTH                    1  /* BKUP_CHG_ENA */
#define WM831X_BKUP_CHG_STS                     0x4000  /* BKUP_CHG_STS */
#define WM831X_BKUP_CHG_STS_MASK                0x4000  /* BKUP_CHG_STS */
#define WM831X_BKUP_CHG_STS_SHIFT                   14  /* BKUP_CHG_STS */
#define WM831X_BKUP_CHG_STS_WIDTH                    1  /* BKUP_CHG_STS */
#define WM831X_BKUP_CHG_MODE                    0x1000  /* BKUP_CHG_MODE */
#define WM831X_BKUP_CHG_MODE_MASK               0x1000  /* BKUP_CHG_MODE */
#define WM831X_BKUP_CHG_MODE_SHIFT                  12  /* BKUP_CHG_MODE */
#define WM831X_BKUP_CHG_MODE_WIDTH                   1  /* BKUP_CHG_MODE */
#define WM831X_BKUP_BATT_DET_ENA                0x0800  /* BKUP_BATT_DET_ENA */
#define WM831X_BKUP_BATT_DET_ENA_MASK           0x0800  /* BKUP_BATT_DET_ENA */
#define WM831X_BKUP_BATT_DET_ENA_SHIFT              11  /* BKUP_BATT_DET_ENA */
#define WM831X_BKUP_BATT_DET_ENA_WIDTH               1  /* BKUP_BATT_DET_ENA */
#define WM831X_BKUP_BATT_STS                    0x0400  /* BKUP_BATT_STS */
#define WM831X_BKUP_BATT_STS_MASK               0x0400  /* BKUP_BATT_STS */
#define WM831X_BKUP_BATT_STS_SHIFT                  10  /* BKUP_BATT_STS */
#define WM831X_BKUP_BATT_STS_WIDTH                   1  /* BKUP_BATT_STS */
#define WM831X_BKUP_CHG_VWIM                    0x0010  /* BKUP_CHG_VWIM */
#define WM831X_BKUP_CHG_VWIM_MASK               0x0010  /* BKUP_CHG_VWIM */
#define WM831X_BKUP_CHG_VWIM_SHIFT                   4  /* BKUP_CHG_VWIM */
#define WM831X_BKUP_CHG_VWIM_WIDTH                   1  /* BKUP_CHG_VWIM */
#define WM831X_BKUP_CHG_IWIM_MASK               0x0003  /* BKUP_CHG_IWIM - [1:0] */
#define WM831X_BKUP_CHG_IWIM_SHIFT                   0  /* BKUP_CHG_IWIM - [1:0] */
#define WM831X_BKUP_CHG_IWIM_WIDTH                   2  /* BKUP_CHG_IWIM - [1:0] */

#endif
