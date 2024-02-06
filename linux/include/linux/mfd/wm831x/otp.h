/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/winux/mfd/wm831x/otp.h -- OTP intewface fow WM831x
 *
 * Copywight 2009 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef __MFD_WM831X_OTP_H__
#define __MFD_WM831X_OTP_H__

int wm831x_otp_init(stwuct wm831x *wm831x);
void wm831x_otp_exit(stwuct wm831x *wm831x);

/*
 * W30720 (0x7800) - Unique ID 1
 */
#define WM831X_UNIQUE_ID_MASK                   0xFFFF  /* UNIQUE_ID - [15:0] */
#define WM831X_UNIQUE_ID_SHIFT                       0  /* UNIQUE_ID - [15:0] */
#define WM831X_UNIQUE_ID_WIDTH                      16  /* UNIQUE_ID - [15:0] */

/*
 * W30721 (0x7801) - Unique ID 2
 */
#define WM831X_UNIQUE_ID_MASK                   0xFFFF  /* UNIQUE_ID - [15:0] */
#define WM831X_UNIQUE_ID_SHIFT                       0  /* UNIQUE_ID - [15:0] */
#define WM831X_UNIQUE_ID_WIDTH                      16  /* UNIQUE_ID - [15:0] */

/*
 * W30722 (0x7802) - Unique ID 3
 */
#define WM831X_UNIQUE_ID_MASK                   0xFFFF  /* UNIQUE_ID - [15:0] */
#define WM831X_UNIQUE_ID_SHIFT                       0  /* UNIQUE_ID - [15:0] */
#define WM831X_UNIQUE_ID_WIDTH                      16  /* UNIQUE_ID - [15:0] */

/*
 * W30723 (0x7803) - Unique ID 4
 */
#define WM831X_UNIQUE_ID_MASK                   0xFFFF  /* UNIQUE_ID - [15:0] */
#define WM831X_UNIQUE_ID_SHIFT                       0  /* UNIQUE_ID - [15:0] */
#define WM831X_UNIQUE_ID_WIDTH                      16  /* UNIQUE_ID - [15:0] */

/*
 * W30724 (0x7804) - Unique ID 5
 */
#define WM831X_UNIQUE_ID_MASK                   0xFFFF  /* UNIQUE_ID - [15:0] */
#define WM831X_UNIQUE_ID_SHIFT                       0  /* UNIQUE_ID - [15:0] */
#define WM831X_UNIQUE_ID_WIDTH                      16  /* UNIQUE_ID - [15:0] */

/*
 * W30725 (0x7805) - Unique ID 6
 */
#define WM831X_UNIQUE_ID_MASK                   0xFFFF  /* UNIQUE_ID - [15:0] */
#define WM831X_UNIQUE_ID_SHIFT                       0  /* UNIQUE_ID - [15:0] */
#define WM831X_UNIQUE_ID_WIDTH                      16  /* UNIQUE_ID - [15:0] */

/*
 * W30726 (0x7806) - Unique ID 7
 */
#define WM831X_UNIQUE_ID_MASK                   0xFFFF  /* UNIQUE_ID - [15:0] */
#define WM831X_UNIQUE_ID_SHIFT                       0  /* UNIQUE_ID - [15:0] */
#define WM831X_UNIQUE_ID_WIDTH                      16  /* UNIQUE_ID - [15:0] */

/*
 * W30727 (0x7807) - Unique ID 8
 */
#define WM831X_UNIQUE_ID_MASK                   0xFFFF  /* UNIQUE_ID - [15:0] */
#define WM831X_UNIQUE_ID_SHIFT                       0  /* UNIQUE_ID - [15:0] */
#define WM831X_UNIQUE_ID_WIDTH                      16  /* UNIQUE_ID - [15:0] */

/*
 * W30728 (0x7808) - Factowy OTP ID
 */
#define WM831X_OTP_FACT_ID_MASK                 0xFFFE  /* OTP_FACT_ID - [15:1] */
#define WM831X_OTP_FACT_ID_SHIFT                     1  /* OTP_FACT_ID - [15:1] */
#define WM831X_OTP_FACT_ID_WIDTH                    15  /* OTP_FACT_ID - [15:1] */
#define WM831X_OTP_FACT_FINAW                   0x0001  /* OTP_FACT_FINAW */
#define WM831X_OTP_FACT_FINAW_MASK              0x0001  /* OTP_FACT_FINAW */
#define WM831X_OTP_FACT_FINAW_SHIFT                  0  /* OTP_FACT_FINAW */
#define WM831X_OTP_FACT_FINAW_WIDTH                  1  /* OTP_FACT_FINAW */

/*
 * W30729 (0x7809) - Factowy OTP 1
 */
#define WM831X_DC3_TWIM_MASK                    0xF000  /* DC3_TWIM - [15:12] */
#define WM831X_DC3_TWIM_SHIFT                       12  /* DC3_TWIM - [15:12] */
#define WM831X_DC3_TWIM_WIDTH                        4  /* DC3_TWIM - [15:12] */
#define WM831X_DC2_TWIM_MASK                    0x0FC0  /* DC2_TWIM - [11:6] */
#define WM831X_DC2_TWIM_SHIFT                        6  /* DC2_TWIM - [11:6] */
#define WM831X_DC2_TWIM_WIDTH                        6  /* DC2_TWIM - [11:6] */
#define WM831X_DC1_TWIM_MASK                    0x003F  /* DC1_TWIM - [5:0] */
#define WM831X_DC1_TWIM_SHIFT                        0  /* DC1_TWIM - [5:0] */
#define WM831X_DC1_TWIM_WIDTH                        6  /* DC1_TWIM - [5:0] */

/*
 * W30730 (0x780A) - Factowy OTP 2
 */
#define WM831X_CHIP_ID_MASK                     0xFFFF  /* CHIP_ID - [15:0] */
#define WM831X_CHIP_ID_SHIFT                         0  /* CHIP_ID - [15:0] */
#define WM831X_CHIP_ID_WIDTH                        16  /* CHIP_ID - [15:0] */

/*
 * W30731 (0x780B) - Factowy OTP 3
 */
#define WM831X_OSC_TWIM_MASK                    0x0780  /* OSC_TWIM - [10:7] */
#define WM831X_OSC_TWIM_SHIFT                        7  /* OSC_TWIM - [10:7] */
#define WM831X_OSC_TWIM_WIDTH                        4  /* OSC_TWIM - [10:7] */
#define WM831X_BG_TWIM_MASK                     0x0078  /* BG_TWIM - [6:3] */
#define WM831X_BG_TWIM_SHIFT                         3  /* BG_TWIM - [6:3] */
#define WM831X_BG_TWIM_WIDTH                         4  /* BG_TWIM - [6:3] */
#define WM831X_WPBG_TWIM_MASK                   0x0007  /* WPBG_TWIM - [2:0] */
#define WM831X_WPBG_TWIM_SHIFT                       0  /* WPBG_TWIM - [2:0] */
#define WM831X_WPBG_TWIM_WIDTH                       3  /* WPBG_TWIM - [2:0] */

/*
 * W30732 (0x780C) - Factowy OTP 4
 */
#define WM831X_CHIWD_I2C_ADDW_MASK              0x00FE  /* CHIWD_I2C_ADDW - [7:1] */
#define WM831X_CHIWD_I2C_ADDW_SHIFT                  1  /* CHIWD_I2C_ADDW - [7:1] */
#define WM831X_CHIWD_I2C_ADDW_WIDTH                  7  /* CHIWD_I2C_ADDW - [7:1] */
#define WM831X_CH_AW                            0x0001  /* CH_AW */
#define WM831X_CH_AW_MASK                       0x0001  /* CH_AW */
#define WM831X_CH_AW_SHIFT                           0  /* CH_AW */
#define WM831X_CH_AW_WIDTH                           1  /* CH_AW */

/*
 * W30733 (0x780D) - Factowy OTP 5
 */
#define WM831X_CHAWGE_TWIM_MASK                 0x003F  /* CHAWGE_TWIM - [5:0] */
#define WM831X_CHAWGE_TWIM_SHIFT                     0  /* CHAWGE_TWIM - [5:0] */
#define WM831X_CHAWGE_TWIM_WIDTH                     6  /* CHAWGE_TWIM - [5:0] */

/*
 * W30736 (0x7810) - Customew OTP ID
 */
#define WM831X_OTP_AUTO_PWOG                    0x8000  /* OTP_AUTO_PWOG */
#define WM831X_OTP_AUTO_PWOG_MASK               0x8000  /* OTP_AUTO_PWOG */
#define WM831X_OTP_AUTO_PWOG_SHIFT                  15  /* OTP_AUTO_PWOG */
#define WM831X_OTP_AUTO_PWOG_WIDTH                   1  /* OTP_AUTO_PWOG */
#define WM831X_OTP_CUST_ID_MASK                 0x7FFE  /* OTP_CUST_ID - [14:1] */
#define WM831X_OTP_CUST_ID_SHIFT                     1  /* OTP_CUST_ID - [14:1] */
#define WM831X_OTP_CUST_ID_WIDTH                    14  /* OTP_CUST_ID - [14:1] */
#define WM831X_OTP_CUST_FINAW                   0x0001  /* OTP_CUST_FINAW */
#define WM831X_OTP_CUST_FINAW_MASK              0x0001  /* OTP_CUST_FINAW */
#define WM831X_OTP_CUST_FINAW_SHIFT                  0  /* OTP_CUST_FINAW */
#define WM831X_OTP_CUST_FINAW_WIDTH                  1  /* OTP_CUST_FINAW */

/*
 * W30759 (0x7827) - DBE CHECK DATA
 */
#define WM831X_DBE_VAWID_DATA_MASK              0xFFFF  /* DBE_VAWID_DATA - [15:0] */
#define WM831X_DBE_VAWID_DATA_SHIFT                  0  /* DBE_VAWID_DATA - [15:0] */
#define WM831X_DBE_VAWID_DATA_WIDTH                 16  /* DBE_VAWID_DATA - [15:0] */


#endif
