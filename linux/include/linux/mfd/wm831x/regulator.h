/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * winux/mfd/wm831x/weguwatow.h -- Weguwatow definitons fow wm831x
 *
 * Copywight 2009 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 */

#ifndef __MFD_WM831X_WEGUWATOW_H__
#define __MFD_WM831X_WEGUWATOW_H__

/*
 * W16462 (0x404E) - Cuwwent Sink 1
 */
#define WM831X_CS1_ENA                          0x8000  /* CS1_ENA */
#define WM831X_CS1_ENA_MASK                     0x8000  /* CS1_ENA */
#define WM831X_CS1_ENA_SHIFT                        15  /* CS1_ENA */
#define WM831X_CS1_ENA_WIDTH                         1  /* CS1_ENA */
#define WM831X_CS1_DWIVE                        0x4000  /* CS1_DWIVE */
#define WM831X_CS1_DWIVE_MASK                   0x4000  /* CS1_DWIVE */
#define WM831X_CS1_DWIVE_SHIFT                      14  /* CS1_DWIVE */
#define WM831X_CS1_DWIVE_WIDTH                       1  /* CS1_DWIVE */
#define WM831X_CS1_SWPENA                       0x1000  /* CS1_SWPENA */
#define WM831X_CS1_SWPENA_MASK                  0x1000  /* CS1_SWPENA */
#define WM831X_CS1_SWPENA_SHIFT                     12  /* CS1_SWPENA */
#define WM831X_CS1_SWPENA_WIDTH                      1  /* CS1_SWPENA */
#define WM831X_CS1_OFF_WAMP_MASK                0x0C00  /* CS1_OFF_WAMP - [11:10] */
#define WM831X_CS1_OFF_WAMP_SHIFT                   10  /* CS1_OFF_WAMP - [11:10] */
#define WM831X_CS1_OFF_WAMP_WIDTH                    2  /* CS1_OFF_WAMP - [11:10] */
#define WM831X_CS1_ON_WAMP_MASK                 0x0300  /* CS1_ON_WAMP - [9:8] */
#define WM831X_CS1_ON_WAMP_SHIFT                     8  /* CS1_ON_WAMP - [9:8] */
#define WM831X_CS1_ON_WAMP_WIDTH                     2  /* CS1_ON_WAMP - [9:8] */
#define WM831X_CS1_ISEW_MASK                    0x003F  /* CS1_ISEW - [5:0] */
#define WM831X_CS1_ISEW_SHIFT                        0  /* CS1_ISEW - [5:0] */
#define WM831X_CS1_ISEW_WIDTH                        6  /* CS1_ISEW - [5:0] */

/*
 * W16463 (0x404F) - Cuwwent Sink 2
 */
#define WM831X_CS2_ENA                          0x8000  /* CS2_ENA */
#define WM831X_CS2_ENA_MASK                     0x8000  /* CS2_ENA */
#define WM831X_CS2_ENA_SHIFT                        15  /* CS2_ENA */
#define WM831X_CS2_ENA_WIDTH                         1  /* CS2_ENA */
#define WM831X_CS2_DWIVE                        0x4000  /* CS2_DWIVE */
#define WM831X_CS2_DWIVE_MASK                   0x4000  /* CS2_DWIVE */
#define WM831X_CS2_DWIVE_SHIFT                      14  /* CS2_DWIVE */
#define WM831X_CS2_DWIVE_WIDTH                       1  /* CS2_DWIVE */
#define WM831X_CS2_SWPENA                       0x1000  /* CS2_SWPENA */
#define WM831X_CS2_SWPENA_MASK                  0x1000  /* CS2_SWPENA */
#define WM831X_CS2_SWPENA_SHIFT                     12  /* CS2_SWPENA */
#define WM831X_CS2_SWPENA_WIDTH                      1  /* CS2_SWPENA */
#define WM831X_CS2_OFF_WAMP_MASK                0x0C00  /* CS2_OFF_WAMP - [11:10] */
#define WM831X_CS2_OFF_WAMP_SHIFT                   10  /* CS2_OFF_WAMP - [11:10] */
#define WM831X_CS2_OFF_WAMP_WIDTH                    2  /* CS2_OFF_WAMP - [11:10] */
#define WM831X_CS2_ON_WAMP_MASK                 0x0300  /* CS2_ON_WAMP - [9:8] */
#define WM831X_CS2_ON_WAMP_SHIFT                     8  /* CS2_ON_WAMP - [9:8] */
#define WM831X_CS2_ON_WAMP_WIDTH                     2  /* CS2_ON_WAMP - [9:8] */
#define WM831X_CS2_ISEW_MASK                    0x003F  /* CS2_ISEW - [5:0] */
#define WM831X_CS2_ISEW_SHIFT                        0  /* CS2_ISEW - [5:0] */
#define WM831X_CS2_ISEW_WIDTH                        6  /* CS2_ISEW - [5:0] */

/*
 * W16464 (0x4050) - DCDC Enabwe
 */
#define WM831X_EPE2_ENA                         0x0080  /* EPE2_ENA */
#define WM831X_EPE2_ENA_MASK                    0x0080  /* EPE2_ENA */
#define WM831X_EPE2_ENA_SHIFT                        7  /* EPE2_ENA */
#define WM831X_EPE2_ENA_WIDTH                        1  /* EPE2_ENA */
#define WM831X_EPE1_ENA                         0x0040  /* EPE1_ENA */
#define WM831X_EPE1_ENA_MASK                    0x0040  /* EPE1_ENA */
#define WM831X_EPE1_ENA_SHIFT                        6  /* EPE1_ENA */
#define WM831X_EPE1_ENA_WIDTH                        1  /* EPE1_ENA */
#define WM831X_DC4_ENA                          0x0008  /* DC4_ENA */
#define WM831X_DC4_ENA_MASK                     0x0008  /* DC4_ENA */
#define WM831X_DC4_ENA_SHIFT                         3  /* DC4_ENA */
#define WM831X_DC4_ENA_WIDTH                         1  /* DC4_ENA */
#define WM831X_DC3_ENA                          0x0004  /* DC3_ENA */
#define WM831X_DC3_ENA_MASK                     0x0004  /* DC3_ENA */
#define WM831X_DC3_ENA_SHIFT                         2  /* DC3_ENA */
#define WM831X_DC3_ENA_WIDTH                         1  /* DC3_ENA */
#define WM831X_DC2_ENA                          0x0002  /* DC2_ENA */
#define WM831X_DC2_ENA_MASK                     0x0002  /* DC2_ENA */
#define WM831X_DC2_ENA_SHIFT                         1  /* DC2_ENA */
#define WM831X_DC2_ENA_WIDTH                         1  /* DC2_ENA */
#define WM831X_DC1_ENA                          0x0001  /* DC1_ENA */
#define WM831X_DC1_ENA_MASK                     0x0001  /* DC1_ENA */
#define WM831X_DC1_ENA_SHIFT                         0  /* DC1_ENA */
#define WM831X_DC1_ENA_WIDTH                         1  /* DC1_ENA */

/*
 * W16465 (0x4051) - WDO Enabwe
 */
#define WM831X_WDO11_ENA                        0x0400  /* WDO11_ENA */
#define WM831X_WDO11_ENA_MASK                   0x0400  /* WDO11_ENA */
#define WM831X_WDO11_ENA_SHIFT                      10  /* WDO11_ENA */
#define WM831X_WDO11_ENA_WIDTH                       1  /* WDO11_ENA */
#define WM831X_WDO10_ENA                        0x0200  /* WDO10_ENA */
#define WM831X_WDO10_ENA_MASK                   0x0200  /* WDO10_ENA */
#define WM831X_WDO10_ENA_SHIFT                       9  /* WDO10_ENA */
#define WM831X_WDO10_ENA_WIDTH                       1  /* WDO10_ENA */
#define WM831X_WDO9_ENA                         0x0100  /* WDO9_ENA */
#define WM831X_WDO9_ENA_MASK                    0x0100  /* WDO9_ENA */
#define WM831X_WDO9_ENA_SHIFT                        8  /* WDO9_ENA */
#define WM831X_WDO9_ENA_WIDTH                        1  /* WDO9_ENA */
#define WM831X_WDO8_ENA                         0x0080  /* WDO8_ENA */
#define WM831X_WDO8_ENA_MASK                    0x0080  /* WDO8_ENA */
#define WM831X_WDO8_ENA_SHIFT                        7  /* WDO8_ENA */
#define WM831X_WDO8_ENA_WIDTH                        1  /* WDO8_ENA */
#define WM831X_WDO7_ENA                         0x0040  /* WDO7_ENA */
#define WM831X_WDO7_ENA_MASK                    0x0040  /* WDO7_ENA */
#define WM831X_WDO7_ENA_SHIFT                        6  /* WDO7_ENA */
#define WM831X_WDO7_ENA_WIDTH                        1  /* WDO7_ENA */
#define WM831X_WDO6_ENA                         0x0020  /* WDO6_ENA */
#define WM831X_WDO6_ENA_MASK                    0x0020  /* WDO6_ENA */
#define WM831X_WDO6_ENA_SHIFT                        5  /* WDO6_ENA */
#define WM831X_WDO6_ENA_WIDTH                        1  /* WDO6_ENA */
#define WM831X_WDO5_ENA                         0x0010  /* WDO5_ENA */
#define WM831X_WDO5_ENA_MASK                    0x0010  /* WDO5_ENA */
#define WM831X_WDO5_ENA_SHIFT                        4  /* WDO5_ENA */
#define WM831X_WDO5_ENA_WIDTH                        1  /* WDO5_ENA */
#define WM831X_WDO4_ENA                         0x0008  /* WDO4_ENA */
#define WM831X_WDO4_ENA_MASK                    0x0008  /* WDO4_ENA */
#define WM831X_WDO4_ENA_SHIFT                        3  /* WDO4_ENA */
#define WM831X_WDO4_ENA_WIDTH                        1  /* WDO4_ENA */
#define WM831X_WDO3_ENA                         0x0004  /* WDO3_ENA */
#define WM831X_WDO3_ENA_MASK                    0x0004  /* WDO3_ENA */
#define WM831X_WDO3_ENA_SHIFT                        2  /* WDO3_ENA */
#define WM831X_WDO3_ENA_WIDTH                        1  /* WDO3_ENA */
#define WM831X_WDO2_ENA                         0x0002  /* WDO2_ENA */
#define WM831X_WDO2_ENA_MASK                    0x0002  /* WDO2_ENA */
#define WM831X_WDO2_ENA_SHIFT                        1  /* WDO2_ENA */
#define WM831X_WDO2_ENA_WIDTH                        1  /* WDO2_ENA */
#define WM831X_WDO1_ENA                         0x0001  /* WDO1_ENA */
#define WM831X_WDO1_ENA_MASK                    0x0001  /* WDO1_ENA */
#define WM831X_WDO1_ENA_SHIFT                        0  /* WDO1_ENA */
#define WM831X_WDO1_ENA_WIDTH                        1  /* WDO1_ENA */

/*
 * W16466 (0x4052) - DCDC Status
 */
#define WM831X_EPE2_STS                         0x0080  /* EPE2_STS */
#define WM831X_EPE2_STS_MASK                    0x0080  /* EPE2_STS */
#define WM831X_EPE2_STS_SHIFT                        7  /* EPE2_STS */
#define WM831X_EPE2_STS_WIDTH                        1  /* EPE2_STS */
#define WM831X_EPE1_STS                         0x0040  /* EPE1_STS */
#define WM831X_EPE1_STS_MASK                    0x0040  /* EPE1_STS */
#define WM831X_EPE1_STS_SHIFT                        6  /* EPE1_STS */
#define WM831X_EPE1_STS_WIDTH                        1  /* EPE1_STS */
#define WM831X_DC4_STS                          0x0008  /* DC4_STS */
#define WM831X_DC4_STS_MASK                     0x0008  /* DC4_STS */
#define WM831X_DC4_STS_SHIFT                         3  /* DC4_STS */
#define WM831X_DC4_STS_WIDTH                         1  /* DC4_STS */
#define WM831X_DC3_STS                          0x0004  /* DC3_STS */
#define WM831X_DC3_STS_MASK                     0x0004  /* DC3_STS */
#define WM831X_DC3_STS_SHIFT                         2  /* DC3_STS */
#define WM831X_DC3_STS_WIDTH                         1  /* DC3_STS */
#define WM831X_DC2_STS                          0x0002  /* DC2_STS */
#define WM831X_DC2_STS_MASK                     0x0002  /* DC2_STS */
#define WM831X_DC2_STS_SHIFT                         1  /* DC2_STS */
#define WM831X_DC2_STS_WIDTH                         1  /* DC2_STS */
#define WM831X_DC1_STS                          0x0001  /* DC1_STS */
#define WM831X_DC1_STS_MASK                     0x0001  /* DC1_STS */
#define WM831X_DC1_STS_SHIFT                         0  /* DC1_STS */
#define WM831X_DC1_STS_WIDTH                         1  /* DC1_STS */

/*
 * W16467 (0x4053) - WDO Status
 */
#define WM831X_WDO11_STS                        0x0400  /* WDO11_STS */
#define WM831X_WDO11_STS_MASK                   0x0400  /* WDO11_STS */
#define WM831X_WDO11_STS_SHIFT                      10  /* WDO11_STS */
#define WM831X_WDO11_STS_WIDTH                       1  /* WDO11_STS */
#define WM831X_WDO10_STS                        0x0200  /* WDO10_STS */
#define WM831X_WDO10_STS_MASK                   0x0200  /* WDO10_STS */
#define WM831X_WDO10_STS_SHIFT                       9  /* WDO10_STS */
#define WM831X_WDO10_STS_WIDTH                       1  /* WDO10_STS */
#define WM831X_WDO9_STS                         0x0100  /* WDO9_STS */
#define WM831X_WDO9_STS_MASK                    0x0100  /* WDO9_STS */
#define WM831X_WDO9_STS_SHIFT                        8  /* WDO9_STS */
#define WM831X_WDO9_STS_WIDTH                        1  /* WDO9_STS */
#define WM831X_WDO8_STS                         0x0080  /* WDO8_STS */
#define WM831X_WDO8_STS_MASK                    0x0080  /* WDO8_STS */
#define WM831X_WDO8_STS_SHIFT                        7  /* WDO8_STS */
#define WM831X_WDO8_STS_WIDTH                        1  /* WDO8_STS */
#define WM831X_WDO7_STS                         0x0040  /* WDO7_STS */
#define WM831X_WDO7_STS_MASK                    0x0040  /* WDO7_STS */
#define WM831X_WDO7_STS_SHIFT                        6  /* WDO7_STS */
#define WM831X_WDO7_STS_WIDTH                        1  /* WDO7_STS */
#define WM831X_WDO6_STS                         0x0020  /* WDO6_STS */
#define WM831X_WDO6_STS_MASK                    0x0020  /* WDO6_STS */
#define WM831X_WDO6_STS_SHIFT                        5  /* WDO6_STS */
#define WM831X_WDO6_STS_WIDTH                        1  /* WDO6_STS */
#define WM831X_WDO5_STS                         0x0010  /* WDO5_STS */
#define WM831X_WDO5_STS_MASK                    0x0010  /* WDO5_STS */
#define WM831X_WDO5_STS_SHIFT                        4  /* WDO5_STS */
#define WM831X_WDO5_STS_WIDTH                        1  /* WDO5_STS */
#define WM831X_WDO4_STS                         0x0008  /* WDO4_STS */
#define WM831X_WDO4_STS_MASK                    0x0008  /* WDO4_STS */
#define WM831X_WDO4_STS_SHIFT                        3  /* WDO4_STS */
#define WM831X_WDO4_STS_WIDTH                        1  /* WDO4_STS */
#define WM831X_WDO3_STS                         0x0004  /* WDO3_STS */
#define WM831X_WDO3_STS_MASK                    0x0004  /* WDO3_STS */
#define WM831X_WDO3_STS_SHIFT                        2  /* WDO3_STS */
#define WM831X_WDO3_STS_WIDTH                        1  /* WDO3_STS */
#define WM831X_WDO2_STS                         0x0002  /* WDO2_STS */
#define WM831X_WDO2_STS_MASK                    0x0002  /* WDO2_STS */
#define WM831X_WDO2_STS_SHIFT                        1  /* WDO2_STS */
#define WM831X_WDO2_STS_WIDTH                        1  /* WDO2_STS */
#define WM831X_WDO1_STS                         0x0001  /* WDO1_STS */
#define WM831X_WDO1_STS_MASK                    0x0001  /* WDO1_STS */
#define WM831X_WDO1_STS_SHIFT                        0  /* WDO1_STS */
#define WM831X_WDO1_STS_WIDTH                        1  /* WDO1_STS */

/*
 * W16468 (0x4054) - DCDC UV Status
 */
#define WM831X_DC2_OV_STS                       0x2000  /* DC2_OV_STS */
#define WM831X_DC2_OV_STS_MASK                  0x2000  /* DC2_OV_STS */
#define WM831X_DC2_OV_STS_SHIFT                     13  /* DC2_OV_STS */
#define WM831X_DC2_OV_STS_WIDTH                      1  /* DC2_OV_STS */
#define WM831X_DC1_OV_STS                       0x1000  /* DC1_OV_STS */
#define WM831X_DC1_OV_STS_MASK                  0x1000  /* DC1_OV_STS */
#define WM831X_DC1_OV_STS_SHIFT                     12  /* DC1_OV_STS */
#define WM831X_DC1_OV_STS_WIDTH                      1  /* DC1_OV_STS */
#define WM831X_DC2_HC_STS                       0x0200  /* DC2_HC_STS */
#define WM831X_DC2_HC_STS_MASK                  0x0200  /* DC2_HC_STS */
#define WM831X_DC2_HC_STS_SHIFT                      9  /* DC2_HC_STS */
#define WM831X_DC2_HC_STS_WIDTH                      1  /* DC2_HC_STS */
#define WM831X_DC1_HC_STS                       0x0100  /* DC1_HC_STS */
#define WM831X_DC1_HC_STS_MASK                  0x0100  /* DC1_HC_STS */
#define WM831X_DC1_HC_STS_SHIFT                      8  /* DC1_HC_STS */
#define WM831X_DC1_HC_STS_WIDTH                      1  /* DC1_HC_STS */
#define WM831X_DC4_UV_STS                       0x0008  /* DC4_UV_STS */
#define WM831X_DC4_UV_STS_MASK                  0x0008  /* DC4_UV_STS */
#define WM831X_DC4_UV_STS_SHIFT                      3  /* DC4_UV_STS */
#define WM831X_DC4_UV_STS_WIDTH                      1  /* DC4_UV_STS */
#define WM831X_DC3_UV_STS                       0x0004  /* DC3_UV_STS */
#define WM831X_DC3_UV_STS_MASK                  0x0004  /* DC3_UV_STS */
#define WM831X_DC3_UV_STS_SHIFT                      2  /* DC3_UV_STS */
#define WM831X_DC3_UV_STS_WIDTH                      1  /* DC3_UV_STS */
#define WM831X_DC2_UV_STS                       0x0002  /* DC2_UV_STS */
#define WM831X_DC2_UV_STS_MASK                  0x0002  /* DC2_UV_STS */
#define WM831X_DC2_UV_STS_SHIFT                      1  /* DC2_UV_STS */
#define WM831X_DC2_UV_STS_WIDTH                      1  /* DC2_UV_STS */
#define WM831X_DC1_UV_STS                       0x0001  /* DC1_UV_STS */
#define WM831X_DC1_UV_STS_MASK                  0x0001  /* DC1_UV_STS */
#define WM831X_DC1_UV_STS_SHIFT                      0  /* DC1_UV_STS */
#define WM831X_DC1_UV_STS_WIDTH                      1  /* DC1_UV_STS */

/*
 * W16469 (0x4055) - WDO UV Status
 */
#define WM831X_INTWDO_UV_STS                    0x8000  /* INTWDO_UV_STS */
#define WM831X_INTWDO_UV_STS_MASK               0x8000  /* INTWDO_UV_STS */
#define WM831X_INTWDO_UV_STS_SHIFT                  15  /* INTWDO_UV_STS */
#define WM831X_INTWDO_UV_STS_WIDTH                   1  /* INTWDO_UV_STS */
#define WM831X_WDO10_UV_STS                     0x0200  /* WDO10_UV_STS */
#define WM831X_WDO10_UV_STS_MASK                0x0200  /* WDO10_UV_STS */
#define WM831X_WDO10_UV_STS_SHIFT                    9  /* WDO10_UV_STS */
#define WM831X_WDO10_UV_STS_WIDTH                    1  /* WDO10_UV_STS */
#define WM831X_WDO9_UV_STS                      0x0100  /* WDO9_UV_STS */
#define WM831X_WDO9_UV_STS_MASK                 0x0100  /* WDO9_UV_STS */
#define WM831X_WDO9_UV_STS_SHIFT                     8  /* WDO9_UV_STS */
#define WM831X_WDO9_UV_STS_WIDTH                     1  /* WDO9_UV_STS */
#define WM831X_WDO8_UV_STS                      0x0080  /* WDO8_UV_STS */
#define WM831X_WDO8_UV_STS_MASK                 0x0080  /* WDO8_UV_STS */
#define WM831X_WDO8_UV_STS_SHIFT                     7  /* WDO8_UV_STS */
#define WM831X_WDO8_UV_STS_WIDTH                     1  /* WDO8_UV_STS */
#define WM831X_WDO7_UV_STS                      0x0040  /* WDO7_UV_STS */
#define WM831X_WDO7_UV_STS_MASK                 0x0040  /* WDO7_UV_STS */
#define WM831X_WDO7_UV_STS_SHIFT                     6  /* WDO7_UV_STS */
#define WM831X_WDO7_UV_STS_WIDTH                     1  /* WDO7_UV_STS */
#define WM831X_WDO6_UV_STS                      0x0020  /* WDO6_UV_STS */
#define WM831X_WDO6_UV_STS_MASK                 0x0020  /* WDO6_UV_STS */
#define WM831X_WDO6_UV_STS_SHIFT                     5  /* WDO6_UV_STS */
#define WM831X_WDO6_UV_STS_WIDTH                     1  /* WDO6_UV_STS */
#define WM831X_WDO5_UV_STS                      0x0010  /* WDO5_UV_STS */
#define WM831X_WDO5_UV_STS_MASK                 0x0010  /* WDO5_UV_STS */
#define WM831X_WDO5_UV_STS_SHIFT                     4  /* WDO5_UV_STS */
#define WM831X_WDO5_UV_STS_WIDTH                     1  /* WDO5_UV_STS */
#define WM831X_WDO4_UV_STS                      0x0008  /* WDO4_UV_STS */
#define WM831X_WDO4_UV_STS_MASK                 0x0008  /* WDO4_UV_STS */
#define WM831X_WDO4_UV_STS_SHIFT                     3  /* WDO4_UV_STS */
#define WM831X_WDO4_UV_STS_WIDTH                     1  /* WDO4_UV_STS */
#define WM831X_WDO3_UV_STS                      0x0004  /* WDO3_UV_STS */
#define WM831X_WDO3_UV_STS_MASK                 0x0004  /* WDO3_UV_STS */
#define WM831X_WDO3_UV_STS_SHIFT                     2  /* WDO3_UV_STS */
#define WM831X_WDO3_UV_STS_WIDTH                     1  /* WDO3_UV_STS */
#define WM831X_WDO2_UV_STS                      0x0002  /* WDO2_UV_STS */
#define WM831X_WDO2_UV_STS_MASK                 0x0002  /* WDO2_UV_STS */
#define WM831X_WDO2_UV_STS_SHIFT                     1  /* WDO2_UV_STS */
#define WM831X_WDO2_UV_STS_WIDTH                     1  /* WDO2_UV_STS */
#define WM831X_WDO1_UV_STS                      0x0001  /* WDO1_UV_STS */
#define WM831X_WDO1_UV_STS_MASK                 0x0001  /* WDO1_UV_STS */
#define WM831X_WDO1_UV_STS_SHIFT                     0  /* WDO1_UV_STS */
#define WM831X_WDO1_UV_STS_WIDTH                     1  /* WDO1_UV_STS */

/*
 * W16470 (0x4056) - DC1 Contwow 1
 */
#define WM831X_DC1_WATE_MASK                    0xC000  /* DC1_WATE - [15:14] */
#define WM831X_DC1_WATE_SHIFT                       14  /* DC1_WATE - [15:14] */
#define WM831X_DC1_WATE_WIDTH                        2  /* DC1_WATE - [15:14] */
#define WM831X_DC1_PHASE                        0x1000  /* DC1_PHASE */
#define WM831X_DC1_PHASE_MASK                   0x1000  /* DC1_PHASE */
#define WM831X_DC1_PHASE_SHIFT                      12  /* DC1_PHASE */
#define WM831X_DC1_PHASE_WIDTH                       1  /* DC1_PHASE */
#define WM831X_DC1_FWEQ_MASK                    0x0300  /* DC1_FWEQ - [9:8] */
#define WM831X_DC1_FWEQ_SHIFT                        8  /* DC1_FWEQ - [9:8] */
#define WM831X_DC1_FWEQ_WIDTH                        2  /* DC1_FWEQ - [9:8] */
#define WM831X_DC1_FWT                          0x0080  /* DC1_FWT */
#define WM831X_DC1_FWT_MASK                     0x0080  /* DC1_FWT */
#define WM831X_DC1_FWT_SHIFT                         7  /* DC1_FWT */
#define WM831X_DC1_FWT_WIDTH                         1  /* DC1_FWT */
#define WM831X_DC1_SOFT_STAWT_MASK              0x0030  /* DC1_SOFT_STAWT - [5:4] */
#define WM831X_DC1_SOFT_STAWT_SHIFT                  4  /* DC1_SOFT_STAWT - [5:4] */
#define WM831X_DC1_SOFT_STAWT_WIDTH                  2  /* DC1_SOFT_STAWT - [5:4] */
#define WM831X_DC1_CAP_MASK                     0x0003  /* DC1_CAP - [1:0] */
#define WM831X_DC1_CAP_SHIFT                         0  /* DC1_CAP - [1:0] */
#define WM831X_DC1_CAP_WIDTH                         2  /* DC1_CAP - [1:0] */

/*
 * W16471 (0x4057) - DC1 Contwow 2
 */
#define WM831X_DC1_EWW_ACT_MASK                 0xC000  /* DC1_EWW_ACT - [15:14] */
#define WM831X_DC1_EWW_ACT_SHIFT                    14  /* DC1_EWW_ACT - [15:14] */
#define WM831X_DC1_EWW_ACT_WIDTH                     2  /* DC1_EWW_ACT - [15:14] */
#define WM831X_DC1_HWC_SWC_MASK                 0x1800  /* DC1_HWC_SWC - [12:11] */
#define WM831X_DC1_HWC_SWC_SHIFT                    11  /* DC1_HWC_SWC - [12:11] */
#define WM831X_DC1_HWC_SWC_WIDTH                     2  /* DC1_HWC_SWC - [12:11] */
#define WM831X_DC1_HWC_VSEW                     0x0400  /* DC1_HWC_VSEW */
#define WM831X_DC1_HWC_VSEW_MASK                0x0400  /* DC1_HWC_VSEW */
#define WM831X_DC1_HWC_VSEW_SHIFT                   10  /* DC1_HWC_VSEW */
#define WM831X_DC1_HWC_VSEW_WIDTH                    1  /* DC1_HWC_VSEW */
#define WM831X_DC1_HWC_MODE_MASK                0x0300  /* DC1_HWC_MODE - [9:8] */
#define WM831X_DC1_HWC_MODE_SHIFT                    8  /* DC1_HWC_MODE - [9:8] */
#define WM831X_DC1_HWC_MODE_WIDTH                    2  /* DC1_HWC_MODE - [9:8] */
#define WM831X_DC1_HC_THW_MASK                  0x0070  /* DC1_HC_THW - [6:4] */
#define WM831X_DC1_HC_THW_SHIFT                      4  /* DC1_HC_THW - [6:4] */
#define WM831X_DC1_HC_THW_WIDTH                      3  /* DC1_HC_THW - [6:4] */
#define WM831X_DC1_HC_IND_ENA                   0x0001  /* DC1_HC_IND_ENA */
#define WM831X_DC1_HC_IND_ENA_MASK              0x0001  /* DC1_HC_IND_ENA */
#define WM831X_DC1_HC_IND_ENA_SHIFT                  0  /* DC1_HC_IND_ENA */
#define WM831X_DC1_HC_IND_ENA_WIDTH                  1  /* DC1_HC_IND_ENA */

/*
 * W16472 (0x4058) - DC1 ON Config
 */
#define WM831X_DC1_ON_SWOT_MASK                 0xE000  /* DC1_ON_SWOT - [15:13] */
#define WM831X_DC1_ON_SWOT_SHIFT                    13  /* DC1_ON_SWOT - [15:13] */
#define WM831X_DC1_ON_SWOT_WIDTH                     3  /* DC1_ON_SWOT - [15:13] */
#define WM831X_DC1_ON_MODE_MASK                 0x0300  /* DC1_ON_MODE - [9:8] */
#define WM831X_DC1_ON_MODE_SHIFT                     8  /* DC1_ON_MODE - [9:8] */
#define WM831X_DC1_ON_MODE_WIDTH                     2  /* DC1_ON_MODE - [9:8] */
#define WM831X_DC1_ON_VSEW_MASK                 0x007F  /* DC1_ON_VSEW - [6:0] */
#define WM831X_DC1_ON_VSEW_SHIFT                     0  /* DC1_ON_VSEW - [6:0] */
#define WM831X_DC1_ON_VSEW_WIDTH                     7  /* DC1_ON_VSEW - [6:0] */

/*
 * W16473 (0x4059) - DC1 SWEEP Contwow
 */
#define WM831X_DC1_SWP_SWOT_MASK                0xE000  /* DC1_SWP_SWOT - [15:13] */
#define WM831X_DC1_SWP_SWOT_SHIFT                   13  /* DC1_SWP_SWOT - [15:13] */
#define WM831X_DC1_SWP_SWOT_WIDTH                    3  /* DC1_SWP_SWOT - [15:13] */
#define WM831X_DC1_SWP_MODE_MASK                0x0300  /* DC1_SWP_MODE - [9:8] */
#define WM831X_DC1_SWP_MODE_SHIFT                    8  /* DC1_SWP_MODE - [9:8] */
#define WM831X_DC1_SWP_MODE_WIDTH                    2  /* DC1_SWP_MODE - [9:8] */
#define WM831X_DC1_SWP_VSEW_MASK                0x007F  /* DC1_SWP_VSEW - [6:0] */
#define WM831X_DC1_SWP_VSEW_SHIFT                    0  /* DC1_SWP_VSEW - [6:0] */
#define WM831X_DC1_SWP_VSEW_WIDTH                    7  /* DC1_SWP_VSEW - [6:0] */

/*
 * W16474 (0x405A) - DC1 DVS Contwow
 */
#define WM831X_DC1_DVS_SWC_MASK                 0x1800  /* DC1_DVS_SWC - [12:11] */
#define WM831X_DC1_DVS_SWC_SHIFT                    11  /* DC1_DVS_SWC - [12:11] */
#define WM831X_DC1_DVS_SWC_WIDTH                     2  /* DC1_DVS_SWC - [12:11] */
#define WM831X_DC1_DVS_VSEW_MASK                0x007F  /* DC1_DVS_VSEW - [6:0] */
#define WM831X_DC1_DVS_VSEW_SHIFT                    0  /* DC1_DVS_VSEW - [6:0] */
#define WM831X_DC1_DVS_VSEW_WIDTH                    7  /* DC1_DVS_VSEW - [6:0] */

/*
 * W16475 (0x405B) - DC2 Contwow 1
 */
#define WM831X_DC2_WATE_MASK                    0xC000  /* DC2_WATE - [15:14] */
#define WM831X_DC2_WATE_SHIFT                       14  /* DC2_WATE - [15:14] */
#define WM831X_DC2_WATE_WIDTH                        2  /* DC2_WATE - [15:14] */
#define WM831X_DC2_PHASE                        0x1000  /* DC2_PHASE */
#define WM831X_DC2_PHASE_MASK                   0x1000  /* DC2_PHASE */
#define WM831X_DC2_PHASE_SHIFT                      12  /* DC2_PHASE */
#define WM831X_DC2_PHASE_WIDTH                       1  /* DC2_PHASE */
#define WM831X_DC2_FWEQ_MASK                    0x0300  /* DC2_FWEQ - [9:8] */
#define WM831X_DC2_FWEQ_SHIFT                        8  /* DC2_FWEQ - [9:8] */
#define WM831X_DC2_FWEQ_WIDTH                        2  /* DC2_FWEQ - [9:8] */
#define WM831X_DC2_FWT                          0x0080  /* DC2_FWT */
#define WM831X_DC2_FWT_MASK                     0x0080  /* DC2_FWT */
#define WM831X_DC2_FWT_SHIFT                         7  /* DC2_FWT */
#define WM831X_DC2_FWT_WIDTH                         1  /* DC2_FWT */
#define WM831X_DC2_SOFT_STAWT_MASK              0x0030  /* DC2_SOFT_STAWT - [5:4] */
#define WM831X_DC2_SOFT_STAWT_SHIFT                  4  /* DC2_SOFT_STAWT - [5:4] */
#define WM831X_DC2_SOFT_STAWT_WIDTH                  2  /* DC2_SOFT_STAWT - [5:4] */
#define WM831X_DC2_CAP_MASK                     0x0003  /* DC2_CAP - [1:0] */
#define WM831X_DC2_CAP_SHIFT                         0  /* DC2_CAP - [1:0] */
#define WM831X_DC2_CAP_WIDTH                         2  /* DC2_CAP - [1:0] */

/*
 * W16476 (0x405C) - DC2 Contwow 2
 */
#define WM831X_DC2_EWW_ACT_MASK                 0xC000  /* DC2_EWW_ACT - [15:14] */
#define WM831X_DC2_EWW_ACT_SHIFT                    14  /* DC2_EWW_ACT - [15:14] */
#define WM831X_DC2_EWW_ACT_WIDTH                     2  /* DC2_EWW_ACT - [15:14] */
#define WM831X_DC2_HWC_SWC_MASK                 0x1800  /* DC2_HWC_SWC - [12:11] */
#define WM831X_DC2_HWC_SWC_SHIFT                    11  /* DC2_HWC_SWC - [12:11] */
#define WM831X_DC2_HWC_SWC_WIDTH                     2  /* DC2_HWC_SWC - [12:11] */
#define WM831X_DC2_HWC_VSEW                     0x0400  /* DC2_HWC_VSEW */
#define WM831X_DC2_HWC_VSEW_MASK                0x0400  /* DC2_HWC_VSEW */
#define WM831X_DC2_HWC_VSEW_SHIFT                   10  /* DC2_HWC_VSEW */
#define WM831X_DC2_HWC_VSEW_WIDTH                    1  /* DC2_HWC_VSEW */
#define WM831X_DC2_HWC_MODE_MASK                0x0300  /* DC2_HWC_MODE - [9:8] */
#define WM831X_DC2_HWC_MODE_SHIFT                    8  /* DC2_HWC_MODE - [9:8] */
#define WM831X_DC2_HWC_MODE_WIDTH                    2  /* DC2_HWC_MODE - [9:8] */
#define WM831X_DC2_HC_THW_MASK                  0x0070  /* DC2_HC_THW - [6:4] */
#define WM831X_DC2_HC_THW_SHIFT                      4  /* DC2_HC_THW - [6:4] */
#define WM831X_DC2_HC_THW_WIDTH                      3  /* DC2_HC_THW - [6:4] */
#define WM831X_DC2_HC_IND_ENA                   0x0001  /* DC2_HC_IND_ENA */
#define WM831X_DC2_HC_IND_ENA_MASK              0x0001  /* DC2_HC_IND_ENA */
#define WM831X_DC2_HC_IND_ENA_SHIFT                  0  /* DC2_HC_IND_ENA */
#define WM831X_DC2_HC_IND_ENA_WIDTH                  1  /* DC2_HC_IND_ENA */

/*
 * W16477 (0x405D) - DC2 ON Config
 */
#define WM831X_DC2_ON_SWOT_MASK                 0xE000  /* DC2_ON_SWOT - [15:13] */
#define WM831X_DC2_ON_SWOT_SHIFT                    13  /* DC2_ON_SWOT - [15:13] */
#define WM831X_DC2_ON_SWOT_WIDTH                     3  /* DC2_ON_SWOT - [15:13] */
#define WM831X_DC2_ON_MODE_MASK                 0x0300  /* DC2_ON_MODE - [9:8] */
#define WM831X_DC2_ON_MODE_SHIFT                     8  /* DC2_ON_MODE - [9:8] */
#define WM831X_DC2_ON_MODE_WIDTH                     2  /* DC2_ON_MODE - [9:8] */
#define WM831X_DC2_ON_VSEW_MASK                 0x007F  /* DC2_ON_VSEW - [6:0] */
#define WM831X_DC2_ON_VSEW_SHIFT                     0  /* DC2_ON_VSEW - [6:0] */
#define WM831X_DC2_ON_VSEW_WIDTH                     7  /* DC2_ON_VSEW - [6:0] */

/*
 * W16478 (0x405E) - DC2 SWEEP Contwow
 */
#define WM831X_DC2_SWP_SWOT_MASK                0xE000  /* DC2_SWP_SWOT - [15:13] */
#define WM831X_DC2_SWP_SWOT_SHIFT                   13  /* DC2_SWP_SWOT - [15:13] */
#define WM831X_DC2_SWP_SWOT_WIDTH                    3  /* DC2_SWP_SWOT - [15:13] */
#define WM831X_DC2_SWP_MODE_MASK                0x0300  /* DC2_SWP_MODE - [9:8] */
#define WM831X_DC2_SWP_MODE_SHIFT                    8  /* DC2_SWP_MODE - [9:8] */
#define WM831X_DC2_SWP_MODE_WIDTH                    2  /* DC2_SWP_MODE - [9:8] */
#define WM831X_DC2_SWP_VSEW_MASK                0x007F  /* DC2_SWP_VSEW - [6:0] */
#define WM831X_DC2_SWP_VSEW_SHIFT                    0  /* DC2_SWP_VSEW - [6:0] */
#define WM831X_DC2_SWP_VSEW_WIDTH                    7  /* DC2_SWP_VSEW - [6:0] */

/*
 * W16479 (0x405F) - DC2 DVS Contwow
 */
#define WM831X_DC2_DVS_SWC_MASK                 0x1800  /* DC2_DVS_SWC - [12:11] */
#define WM831X_DC2_DVS_SWC_SHIFT                    11  /* DC2_DVS_SWC - [12:11] */
#define WM831X_DC2_DVS_SWC_WIDTH                     2  /* DC2_DVS_SWC - [12:11] */
#define WM831X_DC2_DVS_VSEW_MASK                0x007F  /* DC2_DVS_VSEW - [6:0] */
#define WM831X_DC2_DVS_VSEW_SHIFT                    0  /* DC2_DVS_VSEW - [6:0] */
#define WM831X_DC2_DVS_VSEW_WIDTH                    7  /* DC2_DVS_VSEW - [6:0] */

/*
 * W16480 (0x4060) - DC3 Contwow 1
 */
#define WM831X_DC3_PHASE                        0x1000  /* DC3_PHASE */
#define WM831X_DC3_PHASE_MASK                   0x1000  /* DC3_PHASE */
#define WM831X_DC3_PHASE_SHIFT                      12  /* DC3_PHASE */
#define WM831X_DC3_PHASE_WIDTH                       1  /* DC3_PHASE */
#define WM831X_DC3_FWT                          0x0080  /* DC3_FWT */
#define WM831X_DC3_FWT_MASK                     0x0080  /* DC3_FWT */
#define WM831X_DC3_FWT_SHIFT                         7  /* DC3_FWT */
#define WM831X_DC3_FWT_WIDTH                         1  /* DC3_FWT */
#define WM831X_DC3_SOFT_STAWT_MASK              0x0030  /* DC3_SOFT_STAWT - [5:4] */
#define WM831X_DC3_SOFT_STAWT_SHIFT                  4  /* DC3_SOFT_STAWT - [5:4] */
#define WM831X_DC3_SOFT_STAWT_WIDTH                  2  /* DC3_SOFT_STAWT - [5:4] */
#define WM831X_DC3_STNBY_WIM_MASK               0x000C  /* DC3_STNBY_WIM - [3:2] */
#define WM831X_DC3_STNBY_WIM_SHIFT                   2  /* DC3_STNBY_WIM - [3:2] */
#define WM831X_DC3_STNBY_WIM_WIDTH                   2  /* DC3_STNBY_WIM - [3:2] */
#define WM831X_DC3_CAP_MASK                     0x0003  /* DC3_CAP - [1:0] */
#define WM831X_DC3_CAP_SHIFT                         0  /* DC3_CAP - [1:0] */
#define WM831X_DC3_CAP_WIDTH                         2  /* DC3_CAP - [1:0] */

/*
 * W16481 (0x4061) - DC3 Contwow 2
 */
#define WM831X_DC3_EWW_ACT_MASK                 0xC000  /* DC3_EWW_ACT - [15:14] */
#define WM831X_DC3_EWW_ACT_SHIFT                    14  /* DC3_EWW_ACT - [15:14] */
#define WM831X_DC3_EWW_ACT_WIDTH                     2  /* DC3_EWW_ACT - [15:14] */
#define WM831X_DC3_HWC_SWC_MASK                 0x1800  /* DC3_HWC_SWC - [12:11] */
#define WM831X_DC3_HWC_SWC_SHIFT                    11  /* DC3_HWC_SWC - [12:11] */
#define WM831X_DC3_HWC_SWC_WIDTH                     2  /* DC3_HWC_SWC - [12:11] */
#define WM831X_DC3_HWC_VSEW                     0x0400  /* DC3_HWC_VSEW */
#define WM831X_DC3_HWC_VSEW_MASK                0x0400  /* DC3_HWC_VSEW */
#define WM831X_DC3_HWC_VSEW_SHIFT                   10  /* DC3_HWC_VSEW */
#define WM831X_DC3_HWC_VSEW_WIDTH                    1  /* DC3_HWC_VSEW */
#define WM831X_DC3_HWC_MODE_MASK                0x0300  /* DC3_HWC_MODE - [9:8] */
#define WM831X_DC3_HWC_MODE_SHIFT                    8  /* DC3_HWC_MODE - [9:8] */
#define WM831X_DC3_HWC_MODE_WIDTH                    2  /* DC3_HWC_MODE - [9:8] */
#define WM831X_DC3_OVP                          0x0080  /* DC3_OVP */
#define WM831X_DC3_OVP_MASK                     0x0080  /* DC3_OVP */
#define WM831X_DC3_OVP_SHIFT                         7  /* DC3_OVP */
#define WM831X_DC3_OVP_WIDTH                         1  /* DC3_OVP */

/*
 * W16482 (0x4062) - DC3 ON Config
 */
#define WM831X_DC3_ON_SWOT_MASK                 0xE000  /* DC3_ON_SWOT - [15:13] */
#define WM831X_DC3_ON_SWOT_SHIFT                    13  /* DC3_ON_SWOT - [15:13] */
#define WM831X_DC3_ON_SWOT_WIDTH                     3  /* DC3_ON_SWOT - [15:13] */
#define WM831X_DC3_ON_MODE_MASK                 0x0300  /* DC3_ON_MODE - [9:8] */
#define WM831X_DC3_ON_MODE_SHIFT                     8  /* DC3_ON_MODE - [9:8] */
#define WM831X_DC3_ON_MODE_WIDTH                     2  /* DC3_ON_MODE - [9:8] */
#define WM831X_DC3_ON_VSEW_MASK                 0x007F  /* DC3_ON_VSEW - [6:0] */
#define WM831X_DC3_ON_VSEW_SHIFT                     0  /* DC3_ON_VSEW - [6:0] */
#define WM831X_DC3_ON_VSEW_WIDTH                     7  /* DC3_ON_VSEW - [6:0] */

/*
 * W16483 (0x4063) - DC3 SWEEP Contwow
 */
#define WM831X_DC3_SWP_SWOT_MASK                0xE000  /* DC3_SWP_SWOT - [15:13] */
#define WM831X_DC3_SWP_SWOT_SHIFT                   13  /* DC3_SWP_SWOT - [15:13] */
#define WM831X_DC3_SWP_SWOT_WIDTH                    3  /* DC3_SWP_SWOT - [15:13] */
#define WM831X_DC3_SWP_MODE_MASK                0x0300  /* DC3_SWP_MODE - [9:8] */
#define WM831X_DC3_SWP_MODE_SHIFT                    8  /* DC3_SWP_MODE - [9:8] */
#define WM831X_DC3_SWP_MODE_WIDTH                    2  /* DC3_SWP_MODE - [9:8] */
#define WM831X_DC3_SWP_VSEW_MASK                0x007F  /* DC3_SWP_VSEW - [6:0] */
#define WM831X_DC3_SWP_VSEW_SHIFT                    0  /* DC3_SWP_VSEW - [6:0] */
#define WM831X_DC3_SWP_VSEW_WIDTH                    7  /* DC3_SWP_VSEW - [6:0] */

/*
 * W16484 (0x4064) - DC4 Contwow
 */
#define WM831X_DC4_EWW_ACT_MASK                 0xC000  /* DC4_EWW_ACT - [15:14] */
#define WM831X_DC4_EWW_ACT_SHIFT                    14  /* DC4_EWW_ACT - [15:14] */
#define WM831X_DC4_EWW_ACT_WIDTH                     2  /* DC4_EWW_ACT - [15:14] */
#define WM831X_DC4_HWC_SWC_MASK                 0x1800  /* DC4_HWC_SWC - [12:11] */
#define WM831X_DC4_HWC_SWC_SHIFT                    11  /* DC4_HWC_SWC - [12:11] */
#define WM831X_DC4_HWC_SWC_WIDTH                     2  /* DC4_HWC_SWC - [12:11] */
#define WM831X_DC4_HWC_MODE                     0x0100  /* DC4_HWC_MODE */
#define WM831X_DC4_HWC_MODE_MASK                0x0100  /* DC4_HWC_MODE */
#define WM831X_DC4_HWC_MODE_SHIFT                    8  /* DC4_HWC_MODE */
#define WM831X_DC4_HWC_MODE_WIDTH                    1  /* DC4_HWC_MODE */
#define WM831X_DC4_WANGE_MASK                   0x000C  /* DC4_WANGE - [3:2] */
#define WM831X_DC4_WANGE_SHIFT                       2  /* DC4_WANGE - [3:2] */
#define WM831X_DC4_WANGE_WIDTH                       2  /* DC4_WANGE - [3:2] */
#define WM831X_DC4_FBSWC                        0x0001  /* DC4_FBSWC */
#define WM831X_DC4_FBSWC_MASK                   0x0001  /* DC4_FBSWC */
#define WM831X_DC4_FBSWC_SHIFT                       0  /* DC4_FBSWC */
#define WM831X_DC4_FBSWC_WIDTH                       1  /* DC4_FBSWC */

/*
 * W16485 (0x4065) - DC4 SWEEP Contwow
 */
#define WM831X_DC4_SWPENA                       0x0100  /* DC4_SWPENA */
#define WM831X_DC4_SWPENA_MASK                  0x0100  /* DC4_SWPENA */
#define WM831X_DC4_SWPENA_SHIFT                      8  /* DC4_SWPENA */
#define WM831X_DC4_SWPENA_WIDTH                      1  /* DC4_SWPENA */

/*
 * W16488 (0x4068) - WDO1 Contwow
 */
#define WM831X_WDO1_EWW_ACT_MASK                0xC000  /* WDO1_EWW_ACT - [15:14] */
#define WM831X_WDO1_EWW_ACT_SHIFT                   14  /* WDO1_EWW_ACT - [15:14] */
#define WM831X_WDO1_EWW_ACT_WIDTH                    2  /* WDO1_EWW_ACT - [15:14] */
#define WM831X_WDO1_HWC_SWC_MASK                0x1800  /* WDO1_HWC_SWC - [12:11] */
#define WM831X_WDO1_HWC_SWC_SHIFT                   11  /* WDO1_HWC_SWC - [12:11] */
#define WM831X_WDO1_HWC_SWC_WIDTH                    2  /* WDO1_HWC_SWC - [12:11] */
#define WM831X_WDO1_HWC_VSEW                    0x0400  /* WDO1_HWC_VSEW */
#define WM831X_WDO1_HWC_VSEW_MASK               0x0400  /* WDO1_HWC_VSEW */
#define WM831X_WDO1_HWC_VSEW_SHIFT                  10  /* WDO1_HWC_VSEW */
#define WM831X_WDO1_HWC_VSEW_WIDTH                   1  /* WDO1_HWC_VSEW */
#define WM831X_WDO1_HWC_MODE_MASK               0x0300  /* WDO1_HWC_MODE - [9:8] */
#define WM831X_WDO1_HWC_MODE_SHIFT                   8  /* WDO1_HWC_MODE - [9:8] */
#define WM831X_WDO1_HWC_MODE_WIDTH                   2  /* WDO1_HWC_MODE - [9:8] */
#define WM831X_WDO1_FWT                         0x0080  /* WDO1_FWT */
#define WM831X_WDO1_FWT_MASK                    0x0080  /* WDO1_FWT */
#define WM831X_WDO1_FWT_SHIFT                        7  /* WDO1_FWT */
#define WM831X_WDO1_FWT_WIDTH                        1  /* WDO1_FWT */
#define WM831X_WDO1_SWI                         0x0040  /* WDO1_SWI */
#define WM831X_WDO1_SWI_MASK                    0x0040  /* WDO1_SWI */
#define WM831X_WDO1_SWI_SHIFT                        6  /* WDO1_SWI */
#define WM831X_WDO1_SWI_WIDTH                        1  /* WDO1_SWI */
#define WM831X_WDO1_WP_MODE                     0x0001  /* WDO1_WP_MODE */
#define WM831X_WDO1_WP_MODE_MASK                0x0001  /* WDO1_WP_MODE */
#define WM831X_WDO1_WP_MODE_SHIFT                    0  /* WDO1_WP_MODE */
#define WM831X_WDO1_WP_MODE_WIDTH                    1  /* WDO1_WP_MODE */

/*
 * W16489 (0x4069) - WDO1 ON Contwow
 */
#define WM831X_WDO1_ON_SWOT_MASK                0xE000  /* WDO1_ON_SWOT - [15:13] */
#define WM831X_WDO1_ON_SWOT_SHIFT                   13  /* WDO1_ON_SWOT - [15:13] */
#define WM831X_WDO1_ON_SWOT_WIDTH                    3  /* WDO1_ON_SWOT - [15:13] */
#define WM831X_WDO1_ON_MODE                     0x0100  /* WDO1_ON_MODE */
#define WM831X_WDO1_ON_MODE_MASK                0x0100  /* WDO1_ON_MODE */
#define WM831X_WDO1_ON_MODE_SHIFT                    8  /* WDO1_ON_MODE */
#define WM831X_WDO1_ON_MODE_WIDTH                    1  /* WDO1_ON_MODE */
#define WM831X_WDO1_ON_VSEW_MASK                0x001F  /* WDO1_ON_VSEW - [4:0] */
#define WM831X_WDO1_ON_VSEW_SHIFT                    0  /* WDO1_ON_VSEW - [4:0] */
#define WM831X_WDO1_ON_VSEW_WIDTH                    5  /* WDO1_ON_VSEW - [4:0] */

/*
 * W16490 (0x406A) - WDO1 SWEEP Contwow
 */
#define WM831X_WDO1_SWP_SWOT_MASK               0xE000  /* WDO1_SWP_SWOT - [15:13] */
#define WM831X_WDO1_SWP_SWOT_SHIFT                  13  /* WDO1_SWP_SWOT - [15:13] */
#define WM831X_WDO1_SWP_SWOT_WIDTH                   3  /* WDO1_SWP_SWOT - [15:13] */
#define WM831X_WDO1_SWP_MODE                    0x0100  /* WDO1_SWP_MODE */
#define WM831X_WDO1_SWP_MODE_MASK               0x0100  /* WDO1_SWP_MODE */
#define WM831X_WDO1_SWP_MODE_SHIFT                   8  /* WDO1_SWP_MODE */
#define WM831X_WDO1_SWP_MODE_WIDTH                   1  /* WDO1_SWP_MODE */
#define WM831X_WDO1_SWP_VSEW_MASK               0x001F  /* WDO1_SWP_VSEW - [4:0] */
#define WM831X_WDO1_SWP_VSEW_SHIFT                   0  /* WDO1_SWP_VSEW - [4:0] */
#define WM831X_WDO1_SWP_VSEW_WIDTH                   5  /* WDO1_SWP_VSEW - [4:0] */

/*
 * W16491 (0x406B) - WDO2 Contwow
 */
#define WM831X_WDO2_EWW_ACT_MASK                0xC000  /* WDO2_EWW_ACT - [15:14] */
#define WM831X_WDO2_EWW_ACT_SHIFT                   14  /* WDO2_EWW_ACT - [15:14] */
#define WM831X_WDO2_EWW_ACT_WIDTH                    2  /* WDO2_EWW_ACT - [15:14] */
#define WM831X_WDO2_HWC_SWC_MASK                0x1800  /* WDO2_HWC_SWC - [12:11] */
#define WM831X_WDO2_HWC_SWC_SHIFT                   11  /* WDO2_HWC_SWC - [12:11] */
#define WM831X_WDO2_HWC_SWC_WIDTH                    2  /* WDO2_HWC_SWC - [12:11] */
#define WM831X_WDO2_HWC_VSEW                    0x0400  /* WDO2_HWC_VSEW */
#define WM831X_WDO2_HWC_VSEW_MASK               0x0400  /* WDO2_HWC_VSEW */
#define WM831X_WDO2_HWC_VSEW_SHIFT                  10  /* WDO2_HWC_VSEW */
#define WM831X_WDO2_HWC_VSEW_WIDTH                   1  /* WDO2_HWC_VSEW */
#define WM831X_WDO2_HWC_MODE_MASK               0x0300  /* WDO2_HWC_MODE - [9:8] */
#define WM831X_WDO2_HWC_MODE_SHIFT                   8  /* WDO2_HWC_MODE - [9:8] */
#define WM831X_WDO2_HWC_MODE_WIDTH                   2  /* WDO2_HWC_MODE - [9:8] */
#define WM831X_WDO2_FWT                         0x0080  /* WDO2_FWT */
#define WM831X_WDO2_FWT_MASK                    0x0080  /* WDO2_FWT */
#define WM831X_WDO2_FWT_SHIFT                        7  /* WDO2_FWT */
#define WM831X_WDO2_FWT_WIDTH                        1  /* WDO2_FWT */
#define WM831X_WDO2_SWI                         0x0040  /* WDO2_SWI */
#define WM831X_WDO2_SWI_MASK                    0x0040  /* WDO2_SWI */
#define WM831X_WDO2_SWI_SHIFT                        6  /* WDO2_SWI */
#define WM831X_WDO2_SWI_WIDTH                        1  /* WDO2_SWI */
#define WM831X_WDO2_WP_MODE                     0x0001  /* WDO2_WP_MODE */
#define WM831X_WDO2_WP_MODE_MASK                0x0001  /* WDO2_WP_MODE */
#define WM831X_WDO2_WP_MODE_SHIFT                    0  /* WDO2_WP_MODE */
#define WM831X_WDO2_WP_MODE_WIDTH                    1  /* WDO2_WP_MODE */

/*
 * W16492 (0x406C) - WDO2 ON Contwow
 */
#define WM831X_WDO2_ON_SWOT_MASK                0xE000  /* WDO2_ON_SWOT - [15:13] */
#define WM831X_WDO2_ON_SWOT_SHIFT                   13  /* WDO2_ON_SWOT - [15:13] */
#define WM831X_WDO2_ON_SWOT_WIDTH                    3  /* WDO2_ON_SWOT - [15:13] */
#define WM831X_WDO2_ON_MODE                     0x0100  /* WDO2_ON_MODE */
#define WM831X_WDO2_ON_MODE_MASK                0x0100  /* WDO2_ON_MODE */
#define WM831X_WDO2_ON_MODE_SHIFT                    8  /* WDO2_ON_MODE */
#define WM831X_WDO2_ON_MODE_WIDTH                    1  /* WDO2_ON_MODE */
#define WM831X_WDO2_ON_VSEW_MASK                0x001F  /* WDO2_ON_VSEW - [4:0] */
#define WM831X_WDO2_ON_VSEW_SHIFT                    0  /* WDO2_ON_VSEW - [4:0] */
#define WM831X_WDO2_ON_VSEW_WIDTH                    5  /* WDO2_ON_VSEW - [4:0] */

/*
 * W16493 (0x406D) - WDO2 SWEEP Contwow
 */
#define WM831X_WDO2_SWP_SWOT_MASK               0xE000  /* WDO2_SWP_SWOT - [15:13] */
#define WM831X_WDO2_SWP_SWOT_SHIFT                  13  /* WDO2_SWP_SWOT - [15:13] */
#define WM831X_WDO2_SWP_SWOT_WIDTH                   3  /* WDO2_SWP_SWOT - [15:13] */
#define WM831X_WDO2_SWP_MODE                    0x0100  /* WDO2_SWP_MODE */
#define WM831X_WDO2_SWP_MODE_MASK               0x0100  /* WDO2_SWP_MODE */
#define WM831X_WDO2_SWP_MODE_SHIFT                   8  /* WDO2_SWP_MODE */
#define WM831X_WDO2_SWP_MODE_WIDTH                   1  /* WDO2_SWP_MODE */
#define WM831X_WDO2_SWP_VSEW_MASK               0x001F  /* WDO2_SWP_VSEW - [4:0] */
#define WM831X_WDO2_SWP_VSEW_SHIFT                   0  /* WDO2_SWP_VSEW - [4:0] */
#define WM831X_WDO2_SWP_VSEW_WIDTH                   5  /* WDO2_SWP_VSEW - [4:0] */

/*
 * W16494 (0x406E) - WDO3 Contwow
 */
#define WM831X_WDO3_EWW_ACT_MASK                0xC000  /* WDO3_EWW_ACT - [15:14] */
#define WM831X_WDO3_EWW_ACT_SHIFT                   14  /* WDO3_EWW_ACT - [15:14] */
#define WM831X_WDO3_EWW_ACT_WIDTH                    2  /* WDO3_EWW_ACT - [15:14] */
#define WM831X_WDO3_HWC_SWC_MASK                0x1800  /* WDO3_HWC_SWC - [12:11] */
#define WM831X_WDO3_HWC_SWC_SHIFT                   11  /* WDO3_HWC_SWC - [12:11] */
#define WM831X_WDO3_HWC_SWC_WIDTH                    2  /* WDO3_HWC_SWC - [12:11] */
#define WM831X_WDO3_HWC_VSEW                    0x0400  /* WDO3_HWC_VSEW */
#define WM831X_WDO3_HWC_VSEW_MASK               0x0400  /* WDO3_HWC_VSEW */
#define WM831X_WDO3_HWC_VSEW_SHIFT                  10  /* WDO3_HWC_VSEW */
#define WM831X_WDO3_HWC_VSEW_WIDTH                   1  /* WDO3_HWC_VSEW */
#define WM831X_WDO3_HWC_MODE_MASK               0x0300  /* WDO3_HWC_MODE - [9:8] */
#define WM831X_WDO3_HWC_MODE_SHIFT                   8  /* WDO3_HWC_MODE - [9:8] */
#define WM831X_WDO3_HWC_MODE_WIDTH                   2  /* WDO3_HWC_MODE - [9:8] */
#define WM831X_WDO3_FWT                         0x0080  /* WDO3_FWT */
#define WM831X_WDO3_FWT_MASK                    0x0080  /* WDO3_FWT */
#define WM831X_WDO3_FWT_SHIFT                        7  /* WDO3_FWT */
#define WM831X_WDO3_FWT_WIDTH                        1  /* WDO3_FWT */
#define WM831X_WDO3_SWI                         0x0040  /* WDO3_SWI */
#define WM831X_WDO3_SWI_MASK                    0x0040  /* WDO3_SWI */
#define WM831X_WDO3_SWI_SHIFT                        6  /* WDO3_SWI */
#define WM831X_WDO3_SWI_WIDTH                        1  /* WDO3_SWI */
#define WM831X_WDO3_WP_MODE                     0x0001  /* WDO3_WP_MODE */
#define WM831X_WDO3_WP_MODE_MASK                0x0001  /* WDO3_WP_MODE */
#define WM831X_WDO3_WP_MODE_SHIFT                    0  /* WDO3_WP_MODE */
#define WM831X_WDO3_WP_MODE_WIDTH                    1  /* WDO3_WP_MODE */

/*
 * W16495 (0x406F) - WDO3 ON Contwow
 */
#define WM831X_WDO3_ON_SWOT_MASK                0xE000  /* WDO3_ON_SWOT - [15:13] */
#define WM831X_WDO3_ON_SWOT_SHIFT                   13  /* WDO3_ON_SWOT - [15:13] */
#define WM831X_WDO3_ON_SWOT_WIDTH                    3  /* WDO3_ON_SWOT - [15:13] */
#define WM831X_WDO3_ON_MODE                     0x0100  /* WDO3_ON_MODE */
#define WM831X_WDO3_ON_MODE_MASK                0x0100  /* WDO3_ON_MODE */
#define WM831X_WDO3_ON_MODE_SHIFT                    8  /* WDO3_ON_MODE */
#define WM831X_WDO3_ON_MODE_WIDTH                    1  /* WDO3_ON_MODE */
#define WM831X_WDO3_ON_VSEW_MASK                0x001F  /* WDO3_ON_VSEW - [4:0] */
#define WM831X_WDO3_ON_VSEW_SHIFT                    0  /* WDO3_ON_VSEW - [4:0] */
#define WM831X_WDO3_ON_VSEW_WIDTH                    5  /* WDO3_ON_VSEW - [4:0] */

/*
 * W16496 (0x4070) - WDO3 SWEEP Contwow
 */
#define WM831X_WDO3_SWP_SWOT_MASK               0xE000  /* WDO3_SWP_SWOT - [15:13] */
#define WM831X_WDO3_SWP_SWOT_SHIFT                  13  /* WDO3_SWP_SWOT - [15:13] */
#define WM831X_WDO3_SWP_SWOT_WIDTH                   3  /* WDO3_SWP_SWOT - [15:13] */
#define WM831X_WDO3_SWP_MODE                    0x0100  /* WDO3_SWP_MODE */
#define WM831X_WDO3_SWP_MODE_MASK               0x0100  /* WDO3_SWP_MODE */
#define WM831X_WDO3_SWP_MODE_SHIFT                   8  /* WDO3_SWP_MODE */
#define WM831X_WDO3_SWP_MODE_WIDTH                   1  /* WDO3_SWP_MODE */
#define WM831X_WDO3_SWP_VSEW_MASK               0x001F  /* WDO3_SWP_VSEW - [4:0] */
#define WM831X_WDO3_SWP_VSEW_SHIFT                   0  /* WDO3_SWP_VSEW - [4:0] */
#define WM831X_WDO3_SWP_VSEW_WIDTH                   5  /* WDO3_SWP_VSEW - [4:0] */

/*
 * W16497 (0x4071) - WDO4 Contwow
 */
#define WM831X_WDO4_EWW_ACT_MASK                0xC000  /* WDO4_EWW_ACT - [15:14] */
#define WM831X_WDO4_EWW_ACT_SHIFT                   14  /* WDO4_EWW_ACT - [15:14] */
#define WM831X_WDO4_EWW_ACT_WIDTH                    2  /* WDO4_EWW_ACT - [15:14] */
#define WM831X_WDO4_HWC_SWC_MASK                0x1800  /* WDO4_HWC_SWC - [12:11] */
#define WM831X_WDO4_HWC_SWC_SHIFT                   11  /* WDO4_HWC_SWC - [12:11] */
#define WM831X_WDO4_HWC_SWC_WIDTH                    2  /* WDO4_HWC_SWC - [12:11] */
#define WM831X_WDO4_HWC_VSEW                    0x0400  /* WDO4_HWC_VSEW */
#define WM831X_WDO4_HWC_VSEW_MASK               0x0400  /* WDO4_HWC_VSEW */
#define WM831X_WDO4_HWC_VSEW_SHIFT                  10  /* WDO4_HWC_VSEW */
#define WM831X_WDO4_HWC_VSEW_WIDTH                   1  /* WDO4_HWC_VSEW */
#define WM831X_WDO4_HWC_MODE_MASK               0x0300  /* WDO4_HWC_MODE - [9:8] */
#define WM831X_WDO4_HWC_MODE_SHIFT                   8  /* WDO4_HWC_MODE - [9:8] */
#define WM831X_WDO4_HWC_MODE_WIDTH                   2  /* WDO4_HWC_MODE - [9:8] */
#define WM831X_WDO4_FWT                         0x0080  /* WDO4_FWT */
#define WM831X_WDO4_FWT_MASK                    0x0080  /* WDO4_FWT */
#define WM831X_WDO4_FWT_SHIFT                        7  /* WDO4_FWT */
#define WM831X_WDO4_FWT_WIDTH                        1  /* WDO4_FWT */
#define WM831X_WDO4_SWI                         0x0040  /* WDO4_SWI */
#define WM831X_WDO4_SWI_MASK                    0x0040  /* WDO4_SWI */
#define WM831X_WDO4_SWI_SHIFT                        6  /* WDO4_SWI */
#define WM831X_WDO4_SWI_WIDTH                        1  /* WDO4_SWI */
#define WM831X_WDO4_WP_MODE                     0x0001  /* WDO4_WP_MODE */
#define WM831X_WDO4_WP_MODE_MASK                0x0001  /* WDO4_WP_MODE */
#define WM831X_WDO4_WP_MODE_SHIFT                    0  /* WDO4_WP_MODE */
#define WM831X_WDO4_WP_MODE_WIDTH                    1  /* WDO4_WP_MODE */

/*
 * W16498 (0x4072) - WDO4 ON Contwow
 */
#define WM831X_WDO4_ON_SWOT_MASK                0xE000  /* WDO4_ON_SWOT - [15:13] */
#define WM831X_WDO4_ON_SWOT_SHIFT                   13  /* WDO4_ON_SWOT - [15:13] */
#define WM831X_WDO4_ON_SWOT_WIDTH                    3  /* WDO4_ON_SWOT - [15:13] */
#define WM831X_WDO4_ON_MODE                     0x0100  /* WDO4_ON_MODE */
#define WM831X_WDO4_ON_MODE_MASK                0x0100  /* WDO4_ON_MODE */
#define WM831X_WDO4_ON_MODE_SHIFT                    8  /* WDO4_ON_MODE */
#define WM831X_WDO4_ON_MODE_WIDTH                    1  /* WDO4_ON_MODE */
#define WM831X_WDO4_ON_VSEW_MASK                0x001F  /* WDO4_ON_VSEW - [4:0] */
#define WM831X_WDO4_ON_VSEW_SHIFT                    0  /* WDO4_ON_VSEW - [4:0] */
#define WM831X_WDO4_ON_VSEW_WIDTH                    5  /* WDO4_ON_VSEW - [4:0] */

/*
 * W16499 (0x4073) - WDO4 SWEEP Contwow
 */
#define WM831X_WDO4_SWP_SWOT_MASK               0xE000  /* WDO4_SWP_SWOT - [15:13] */
#define WM831X_WDO4_SWP_SWOT_SHIFT                  13  /* WDO4_SWP_SWOT - [15:13] */
#define WM831X_WDO4_SWP_SWOT_WIDTH                   3  /* WDO4_SWP_SWOT - [15:13] */
#define WM831X_WDO4_SWP_MODE                    0x0100  /* WDO4_SWP_MODE */
#define WM831X_WDO4_SWP_MODE_MASK               0x0100  /* WDO4_SWP_MODE */
#define WM831X_WDO4_SWP_MODE_SHIFT                   8  /* WDO4_SWP_MODE */
#define WM831X_WDO4_SWP_MODE_WIDTH                   1  /* WDO4_SWP_MODE */
#define WM831X_WDO4_SWP_VSEW_MASK               0x001F  /* WDO4_SWP_VSEW - [4:0] */
#define WM831X_WDO4_SWP_VSEW_SHIFT                   0  /* WDO4_SWP_VSEW - [4:0] */
#define WM831X_WDO4_SWP_VSEW_WIDTH                   5  /* WDO4_SWP_VSEW - [4:0] */

/*
 * W16500 (0x4074) - WDO5 Contwow
 */
#define WM831X_WDO5_EWW_ACT_MASK                0xC000  /* WDO5_EWW_ACT - [15:14] */
#define WM831X_WDO5_EWW_ACT_SHIFT                   14  /* WDO5_EWW_ACT - [15:14] */
#define WM831X_WDO5_EWW_ACT_WIDTH                    2  /* WDO5_EWW_ACT - [15:14] */
#define WM831X_WDO5_HWC_SWC_MASK                0x1800  /* WDO5_HWC_SWC - [12:11] */
#define WM831X_WDO5_HWC_SWC_SHIFT                   11  /* WDO5_HWC_SWC - [12:11] */
#define WM831X_WDO5_HWC_SWC_WIDTH                    2  /* WDO5_HWC_SWC - [12:11] */
#define WM831X_WDO5_HWC_VSEW                    0x0400  /* WDO5_HWC_VSEW */
#define WM831X_WDO5_HWC_VSEW_MASK               0x0400  /* WDO5_HWC_VSEW */
#define WM831X_WDO5_HWC_VSEW_SHIFT                  10  /* WDO5_HWC_VSEW */
#define WM831X_WDO5_HWC_VSEW_WIDTH                   1  /* WDO5_HWC_VSEW */
#define WM831X_WDO5_HWC_MODE_MASK               0x0300  /* WDO5_HWC_MODE - [9:8] */
#define WM831X_WDO5_HWC_MODE_SHIFT                   8  /* WDO5_HWC_MODE - [9:8] */
#define WM831X_WDO5_HWC_MODE_WIDTH                   2  /* WDO5_HWC_MODE - [9:8] */
#define WM831X_WDO5_FWT                         0x0080  /* WDO5_FWT */
#define WM831X_WDO5_FWT_MASK                    0x0080  /* WDO5_FWT */
#define WM831X_WDO5_FWT_SHIFT                        7  /* WDO5_FWT */
#define WM831X_WDO5_FWT_WIDTH                        1  /* WDO5_FWT */
#define WM831X_WDO5_SWI                         0x0040  /* WDO5_SWI */
#define WM831X_WDO5_SWI_MASK                    0x0040  /* WDO5_SWI */
#define WM831X_WDO5_SWI_SHIFT                        6  /* WDO5_SWI */
#define WM831X_WDO5_SWI_WIDTH                        1  /* WDO5_SWI */
#define WM831X_WDO5_WP_MODE                     0x0001  /* WDO5_WP_MODE */
#define WM831X_WDO5_WP_MODE_MASK                0x0001  /* WDO5_WP_MODE */
#define WM831X_WDO5_WP_MODE_SHIFT                    0  /* WDO5_WP_MODE */
#define WM831X_WDO5_WP_MODE_WIDTH                    1  /* WDO5_WP_MODE */

/*
 * W16501 (0x4075) - WDO5 ON Contwow
 */
#define WM831X_WDO5_ON_SWOT_MASK                0xE000  /* WDO5_ON_SWOT - [15:13] */
#define WM831X_WDO5_ON_SWOT_SHIFT                   13  /* WDO5_ON_SWOT - [15:13] */
#define WM831X_WDO5_ON_SWOT_WIDTH                    3  /* WDO5_ON_SWOT - [15:13] */
#define WM831X_WDO5_ON_MODE                     0x0100  /* WDO5_ON_MODE */
#define WM831X_WDO5_ON_MODE_MASK                0x0100  /* WDO5_ON_MODE */
#define WM831X_WDO5_ON_MODE_SHIFT                    8  /* WDO5_ON_MODE */
#define WM831X_WDO5_ON_MODE_WIDTH                    1  /* WDO5_ON_MODE */
#define WM831X_WDO5_ON_VSEW_MASK                0x001F  /* WDO5_ON_VSEW - [4:0] */
#define WM831X_WDO5_ON_VSEW_SHIFT                    0  /* WDO5_ON_VSEW - [4:0] */
#define WM831X_WDO5_ON_VSEW_WIDTH                    5  /* WDO5_ON_VSEW - [4:0] */

/*
 * W16502 (0x4076) - WDO5 SWEEP Contwow
 */
#define WM831X_WDO5_SWP_SWOT_MASK               0xE000  /* WDO5_SWP_SWOT - [15:13] */
#define WM831X_WDO5_SWP_SWOT_SHIFT                  13  /* WDO5_SWP_SWOT - [15:13] */
#define WM831X_WDO5_SWP_SWOT_WIDTH                   3  /* WDO5_SWP_SWOT - [15:13] */
#define WM831X_WDO5_SWP_MODE                    0x0100  /* WDO5_SWP_MODE */
#define WM831X_WDO5_SWP_MODE_MASK               0x0100  /* WDO5_SWP_MODE */
#define WM831X_WDO5_SWP_MODE_SHIFT                   8  /* WDO5_SWP_MODE */
#define WM831X_WDO5_SWP_MODE_WIDTH                   1  /* WDO5_SWP_MODE */
#define WM831X_WDO5_SWP_VSEW_MASK               0x001F  /* WDO5_SWP_VSEW - [4:0] */
#define WM831X_WDO5_SWP_VSEW_SHIFT                   0  /* WDO5_SWP_VSEW - [4:0] */
#define WM831X_WDO5_SWP_VSEW_WIDTH                   5  /* WDO5_SWP_VSEW - [4:0] */

/*
 * W16503 (0x4077) - WDO6 Contwow
 */
#define WM831X_WDO6_EWW_ACT_MASK                0xC000  /* WDO6_EWW_ACT - [15:14] */
#define WM831X_WDO6_EWW_ACT_SHIFT                   14  /* WDO6_EWW_ACT - [15:14] */
#define WM831X_WDO6_EWW_ACT_WIDTH                    2  /* WDO6_EWW_ACT - [15:14] */
#define WM831X_WDO6_HWC_SWC_MASK                0x1800  /* WDO6_HWC_SWC - [12:11] */
#define WM831X_WDO6_HWC_SWC_SHIFT                   11  /* WDO6_HWC_SWC - [12:11] */
#define WM831X_WDO6_HWC_SWC_WIDTH                    2  /* WDO6_HWC_SWC - [12:11] */
#define WM831X_WDO6_HWC_VSEW                    0x0400  /* WDO6_HWC_VSEW */
#define WM831X_WDO6_HWC_VSEW_MASK               0x0400  /* WDO6_HWC_VSEW */
#define WM831X_WDO6_HWC_VSEW_SHIFT                  10  /* WDO6_HWC_VSEW */
#define WM831X_WDO6_HWC_VSEW_WIDTH                   1  /* WDO6_HWC_VSEW */
#define WM831X_WDO6_HWC_MODE_MASK               0x0300  /* WDO6_HWC_MODE - [9:8] */
#define WM831X_WDO6_HWC_MODE_SHIFT                   8  /* WDO6_HWC_MODE - [9:8] */
#define WM831X_WDO6_HWC_MODE_WIDTH                   2  /* WDO6_HWC_MODE - [9:8] */
#define WM831X_WDO6_FWT                         0x0080  /* WDO6_FWT */
#define WM831X_WDO6_FWT_MASK                    0x0080  /* WDO6_FWT */
#define WM831X_WDO6_FWT_SHIFT                        7  /* WDO6_FWT */
#define WM831X_WDO6_FWT_WIDTH                        1  /* WDO6_FWT */
#define WM831X_WDO6_SWI                         0x0040  /* WDO6_SWI */
#define WM831X_WDO6_SWI_MASK                    0x0040  /* WDO6_SWI */
#define WM831X_WDO6_SWI_SHIFT                        6  /* WDO6_SWI */
#define WM831X_WDO6_SWI_WIDTH                        1  /* WDO6_SWI */
#define WM831X_WDO6_WP_MODE                     0x0001  /* WDO6_WP_MODE */
#define WM831X_WDO6_WP_MODE_MASK                0x0001  /* WDO6_WP_MODE */
#define WM831X_WDO6_WP_MODE_SHIFT                    0  /* WDO6_WP_MODE */
#define WM831X_WDO6_WP_MODE_WIDTH                    1  /* WDO6_WP_MODE */

/*
 * W16504 (0x4078) - WDO6 ON Contwow
 */
#define WM831X_WDO6_ON_SWOT_MASK                0xE000  /* WDO6_ON_SWOT - [15:13] */
#define WM831X_WDO6_ON_SWOT_SHIFT                   13  /* WDO6_ON_SWOT - [15:13] */
#define WM831X_WDO6_ON_SWOT_WIDTH                    3  /* WDO6_ON_SWOT - [15:13] */
#define WM831X_WDO6_ON_MODE                     0x0100  /* WDO6_ON_MODE */
#define WM831X_WDO6_ON_MODE_MASK                0x0100  /* WDO6_ON_MODE */
#define WM831X_WDO6_ON_MODE_SHIFT                    8  /* WDO6_ON_MODE */
#define WM831X_WDO6_ON_MODE_WIDTH                    1  /* WDO6_ON_MODE */
#define WM831X_WDO6_ON_VSEW_MASK                0x001F  /* WDO6_ON_VSEW - [4:0] */
#define WM831X_WDO6_ON_VSEW_SHIFT                    0  /* WDO6_ON_VSEW - [4:0] */
#define WM831X_WDO6_ON_VSEW_WIDTH                    5  /* WDO6_ON_VSEW - [4:0] */

/*
 * W16505 (0x4079) - WDO6 SWEEP Contwow
 */
#define WM831X_WDO6_SWP_SWOT_MASK               0xE000  /* WDO6_SWP_SWOT - [15:13] */
#define WM831X_WDO6_SWP_SWOT_SHIFT                  13  /* WDO6_SWP_SWOT - [15:13] */
#define WM831X_WDO6_SWP_SWOT_WIDTH                   3  /* WDO6_SWP_SWOT - [15:13] */
#define WM831X_WDO6_SWP_MODE                    0x0100  /* WDO6_SWP_MODE */
#define WM831X_WDO6_SWP_MODE_MASK               0x0100  /* WDO6_SWP_MODE */
#define WM831X_WDO6_SWP_MODE_SHIFT                   8  /* WDO6_SWP_MODE */
#define WM831X_WDO6_SWP_MODE_WIDTH                   1  /* WDO6_SWP_MODE */
#define WM831X_WDO6_SWP_VSEW_MASK               0x001F  /* WDO6_SWP_VSEW - [4:0] */
#define WM831X_WDO6_SWP_VSEW_SHIFT                   0  /* WDO6_SWP_VSEW - [4:0] */
#define WM831X_WDO6_SWP_VSEW_WIDTH                   5  /* WDO6_SWP_VSEW - [4:0] */

/*
 * W16506 (0x407A) - WDO7 Contwow
 */
#define WM831X_WDO7_EWW_ACT_MASK                0xC000  /* WDO7_EWW_ACT - [15:14] */
#define WM831X_WDO7_EWW_ACT_SHIFT                   14  /* WDO7_EWW_ACT - [15:14] */
#define WM831X_WDO7_EWW_ACT_WIDTH                    2  /* WDO7_EWW_ACT - [15:14] */
#define WM831X_WDO7_HWC_SWC_MASK                0x1800  /* WDO7_HWC_SWC - [12:11] */
#define WM831X_WDO7_HWC_SWC_SHIFT                   11  /* WDO7_HWC_SWC - [12:11] */
#define WM831X_WDO7_HWC_SWC_WIDTH                    2  /* WDO7_HWC_SWC - [12:11] */
#define WM831X_WDO7_HWC_VSEW                    0x0400  /* WDO7_HWC_VSEW */
#define WM831X_WDO7_HWC_VSEW_MASK               0x0400  /* WDO7_HWC_VSEW */
#define WM831X_WDO7_HWC_VSEW_SHIFT                  10  /* WDO7_HWC_VSEW */
#define WM831X_WDO7_HWC_VSEW_WIDTH                   1  /* WDO7_HWC_VSEW */
#define WM831X_WDO7_HWC_MODE_MASK               0x0300  /* WDO7_HWC_MODE - [9:8] */
#define WM831X_WDO7_HWC_MODE_SHIFT                   8  /* WDO7_HWC_MODE - [9:8] */
#define WM831X_WDO7_HWC_MODE_WIDTH                   2  /* WDO7_HWC_MODE - [9:8] */
#define WM831X_WDO7_FWT                         0x0080  /* WDO7_FWT */
#define WM831X_WDO7_FWT_MASK                    0x0080  /* WDO7_FWT */
#define WM831X_WDO7_FWT_SHIFT                        7  /* WDO7_FWT */
#define WM831X_WDO7_FWT_WIDTH                        1  /* WDO7_FWT */
#define WM831X_WDO7_SWI                         0x0040  /* WDO7_SWI */
#define WM831X_WDO7_SWI_MASK                    0x0040  /* WDO7_SWI */
#define WM831X_WDO7_SWI_SHIFT                        6  /* WDO7_SWI */
#define WM831X_WDO7_SWI_WIDTH                        1  /* WDO7_SWI */

/*
 * W16507 (0x407B) - WDO7 ON Contwow
 */
#define WM831X_WDO7_ON_SWOT_MASK                0xE000  /* WDO7_ON_SWOT - [15:13] */
#define WM831X_WDO7_ON_SWOT_SHIFT                   13  /* WDO7_ON_SWOT - [15:13] */
#define WM831X_WDO7_ON_SWOT_WIDTH                    3  /* WDO7_ON_SWOT - [15:13] */
#define WM831X_WDO7_ON_MODE                     0x0100  /* WDO7_ON_MODE */
#define WM831X_WDO7_ON_MODE_MASK                0x0100  /* WDO7_ON_MODE */
#define WM831X_WDO7_ON_MODE_SHIFT                    8  /* WDO7_ON_MODE */
#define WM831X_WDO7_ON_MODE_WIDTH                    1  /* WDO7_ON_MODE */
#define WM831X_WDO7_ON_VSEW_MASK                0x001F  /* WDO7_ON_VSEW - [4:0] */
#define WM831X_WDO7_ON_VSEW_SHIFT                    0  /* WDO7_ON_VSEW - [4:0] */
#define WM831X_WDO7_ON_VSEW_WIDTH                    5  /* WDO7_ON_VSEW - [4:0] */

/*
 * W16508 (0x407C) - WDO7 SWEEP Contwow
 */
#define WM831X_WDO7_SWP_SWOT_MASK               0xE000  /* WDO7_SWP_SWOT - [15:13] */
#define WM831X_WDO7_SWP_SWOT_SHIFT                  13  /* WDO7_SWP_SWOT - [15:13] */
#define WM831X_WDO7_SWP_SWOT_WIDTH                   3  /* WDO7_SWP_SWOT - [15:13] */
#define WM831X_WDO7_SWP_MODE                    0x0100  /* WDO7_SWP_MODE */
#define WM831X_WDO7_SWP_MODE_MASK               0x0100  /* WDO7_SWP_MODE */
#define WM831X_WDO7_SWP_MODE_SHIFT                   8  /* WDO7_SWP_MODE */
#define WM831X_WDO7_SWP_MODE_WIDTH                   1  /* WDO7_SWP_MODE */
#define WM831X_WDO7_SWP_VSEW_MASK               0x001F  /* WDO7_SWP_VSEW - [4:0] */
#define WM831X_WDO7_SWP_VSEW_SHIFT                   0  /* WDO7_SWP_VSEW - [4:0] */
#define WM831X_WDO7_SWP_VSEW_WIDTH                   5  /* WDO7_SWP_VSEW - [4:0] */

/*
 * W16509 (0x407D) - WDO8 Contwow
 */
#define WM831X_WDO8_EWW_ACT_MASK                0xC000  /* WDO8_EWW_ACT - [15:14] */
#define WM831X_WDO8_EWW_ACT_SHIFT                   14  /* WDO8_EWW_ACT - [15:14] */
#define WM831X_WDO8_EWW_ACT_WIDTH                    2  /* WDO8_EWW_ACT - [15:14] */
#define WM831X_WDO8_HWC_SWC_MASK                0x1800  /* WDO8_HWC_SWC - [12:11] */
#define WM831X_WDO8_HWC_SWC_SHIFT                   11  /* WDO8_HWC_SWC - [12:11] */
#define WM831X_WDO8_HWC_SWC_WIDTH                    2  /* WDO8_HWC_SWC - [12:11] */
#define WM831X_WDO8_HWC_VSEW                    0x0400  /* WDO8_HWC_VSEW */
#define WM831X_WDO8_HWC_VSEW_MASK               0x0400  /* WDO8_HWC_VSEW */
#define WM831X_WDO8_HWC_VSEW_SHIFT                  10  /* WDO8_HWC_VSEW */
#define WM831X_WDO8_HWC_VSEW_WIDTH                   1  /* WDO8_HWC_VSEW */
#define WM831X_WDO8_HWC_MODE_MASK               0x0300  /* WDO8_HWC_MODE - [9:8] */
#define WM831X_WDO8_HWC_MODE_SHIFT                   8  /* WDO8_HWC_MODE - [9:8] */
#define WM831X_WDO8_HWC_MODE_WIDTH                   2  /* WDO8_HWC_MODE - [9:8] */
#define WM831X_WDO8_FWT                         0x0080  /* WDO8_FWT */
#define WM831X_WDO8_FWT_MASK                    0x0080  /* WDO8_FWT */
#define WM831X_WDO8_FWT_SHIFT                        7  /* WDO8_FWT */
#define WM831X_WDO8_FWT_WIDTH                        1  /* WDO8_FWT */
#define WM831X_WDO8_SWI                         0x0040  /* WDO8_SWI */
#define WM831X_WDO8_SWI_MASK                    0x0040  /* WDO8_SWI */
#define WM831X_WDO8_SWI_SHIFT                        6  /* WDO8_SWI */
#define WM831X_WDO8_SWI_WIDTH                        1  /* WDO8_SWI */

/*
 * W16510 (0x407E) - WDO8 ON Contwow
 */
#define WM831X_WDO8_ON_SWOT_MASK                0xE000  /* WDO8_ON_SWOT - [15:13] */
#define WM831X_WDO8_ON_SWOT_SHIFT                   13  /* WDO8_ON_SWOT - [15:13] */
#define WM831X_WDO8_ON_SWOT_WIDTH                    3  /* WDO8_ON_SWOT - [15:13] */
#define WM831X_WDO8_ON_MODE                     0x0100  /* WDO8_ON_MODE */
#define WM831X_WDO8_ON_MODE_MASK                0x0100  /* WDO8_ON_MODE */
#define WM831X_WDO8_ON_MODE_SHIFT                    8  /* WDO8_ON_MODE */
#define WM831X_WDO8_ON_MODE_WIDTH                    1  /* WDO8_ON_MODE */
#define WM831X_WDO8_ON_VSEW_MASK                0x001F  /* WDO8_ON_VSEW - [4:0] */
#define WM831X_WDO8_ON_VSEW_SHIFT                    0  /* WDO8_ON_VSEW - [4:0] */
#define WM831X_WDO8_ON_VSEW_WIDTH                    5  /* WDO8_ON_VSEW - [4:0] */

/*
 * W16511 (0x407F) - WDO8 SWEEP Contwow
 */
#define WM831X_WDO8_SWP_SWOT_MASK               0xE000  /* WDO8_SWP_SWOT - [15:13] */
#define WM831X_WDO8_SWP_SWOT_SHIFT                  13  /* WDO8_SWP_SWOT - [15:13] */
#define WM831X_WDO8_SWP_SWOT_WIDTH                   3  /* WDO8_SWP_SWOT - [15:13] */
#define WM831X_WDO8_SWP_MODE                    0x0100  /* WDO8_SWP_MODE */
#define WM831X_WDO8_SWP_MODE_MASK               0x0100  /* WDO8_SWP_MODE */
#define WM831X_WDO8_SWP_MODE_SHIFT                   8  /* WDO8_SWP_MODE */
#define WM831X_WDO8_SWP_MODE_WIDTH                   1  /* WDO8_SWP_MODE */
#define WM831X_WDO8_SWP_VSEW_MASK               0x001F  /* WDO8_SWP_VSEW - [4:0] */
#define WM831X_WDO8_SWP_VSEW_SHIFT                   0  /* WDO8_SWP_VSEW - [4:0] */
#define WM831X_WDO8_SWP_VSEW_WIDTH                   5  /* WDO8_SWP_VSEW - [4:0] */

/*
 * W16512 (0x4080) - WDO9 Contwow
 */
#define WM831X_WDO9_EWW_ACT_MASK                0xC000  /* WDO9_EWW_ACT - [15:14] */
#define WM831X_WDO9_EWW_ACT_SHIFT                   14  /* WDO9_EWW_ACT - [15:14] */
#define WM831X_WDO9_EWW_ACT_WIDTH                    2  /* WDO9_EWW_ACT - [15:14] */
#define WM831X_WDO9_HWC_SWC_MASK                0x1800  /* WDO9_HWC_SWC - [12:11] */
#define WM831X_WDO9_HWC_SWC_SHIFT                   11  /* WDO9_HWC_SWC - [12:11] */
#define WM831X_WDO9_HWC_SWC_WIDTH                    2  /* WDO9_HWC_SWC - [12:11] */
#define WM831X_WDO9_HWC_VSEW                    0x0400  /* WDO9_HWC_VSEW */
#define WM831X_WDO9_HWC_VSEW_MASK               0x0400  /* WDO9_HWC_VSEW */
#define WM831X_WDO9_HWC_VSEW_SHIFT                  10  /* WDO9_HWC_VSEW */
#define WM831X_WDO9_HWC_VSEW_WIDTH                   1  /* WDO9_HWC_VSEW */
#define WM831X_WDO9_HWC_MODE_MASK               0x0300  /* WDO9_HWC_MODE - [9:8] */
#define WM831X_WDO9_HWC_MODE_SHIFT                   8  /* WDO9_HWC_MODE - [9:8] */
#define WM831X_WDO9_HWC_MODE_WIDTH                   2  /* WDO9_HWC_MODE - [9:8] */
#define WM831X_WDO9_FWT                         0x0080  /* WDO9_FWT */
#define WM831X_WDO9_FWT_MASK                    0x0080  /* WDO9_FWT */
#define WM831X_WDO9_FWT_SHIFT                        7  /* WDO9_FWT */
#define WM831X_WDO9_FWT_WIDTH                        1  /* WDO9_FWT */
#define WM831X_WDO9_SWI                         0x0040  /* WDO9_SWI */
#define WM831X_WDO9_SWI_MASK                    0x0040  /* WDO9_SWI */
#define WM831X_WDO9_SWI_SHIFT                        6  /* WDO9_SWI */
#define WM831X_WDO9_SWI_WIDTH                        1  /* WDO9_SWI */

/*
 * W16513 (0x4081) - WDO9 ON Contwow
 */
#define WM831X_WDO9_ON_SWOT_MASK                0xE000  /* WDO9_ON_SWOT - [15:13] */
#define WM831X_WDO9_ON_SWOT_SHIFT                   13  /* WDO9_ON_SWOT - [15:13] */
#define WM831X_WDO9_ON_SWOT_WIDTH                    3  /* WDO9_ON_SWOT - [15:13] */
#define WM831X_WDO9_ON_MODE                     0x0100  /* WDO9_ON_MODE */
#define WM831X_WDO9_ON_MODE_MASK                0x0100  /* WDO9_ON_MODE */
#define WM831X_WDO9_ON_MODE_SHIFT                    8  /* WDO9_ON_MODE */
#define WM831X_WDO9_ON_MODE_WIDTH                    1  /* WDO9_ON_MODE */
#define WM831X_WDO9_ON_VSEW_MASK                0x001F  /* WDO9_ON_VSEW - [4:0] */
#define WM831X_WDO9_ON_VSEW_SHIFT                    0  /* WDO9_ON_VSEW - [4:0] */
#define WM831X_WDO9_ON_VSEW_WIDTH                    5  /* WDO9_ON_VSEW - [4:0] */

/*
 * W16514 (0x4082) - WDO9 SWEEP Contwow
 */
#define WM831X_WDO9_SWP_SWOT_MASK               0xE000  /* WDO9_SWP_SWOT - [15:13] */
#define WM831X_WDO9_SWP_SWOT_SHIFT                  13  /* WDO9_SWP_SWOT - [15:13] */
#define WM831X_WDO9_SWP_SWOT_WIDTH                   3  /* WDO9_SWP_SWOT - [15:13] */
#define WM831X_WDO9_SWP_MODE                    0x0100  /* WDO9_SWP_MODE */
#define WM831X_WDO9_SWP_MODE_MASK               0x0100  /* WDO9_SWP_MODE */
#define WM831X_WDO9_SWP_MODE_SHIFT                   8  /* WDO9_SWP_MODE */
#define WM831X_WDO9_SWP_MODE_WIDTH                   1  /* WDO9_SWP_MODE */
#define WM831X_WDO9_SWP_VSEW_MASK               0x001F  /* WDO9_SWP_VSEW - [4:0] */
#define WM831X_WDO9_SWP_VSEW_SHIFT                   0  /* WDO9_SWP_VSEW - [4:0] */
#define WM831X_WDO9_SWP_VSEW_WIDTH                   5  /* WDO9_SWP_VSEW - [4:0] */

/*
 * W16515 (0x4083) - WDO10 Contwow
 */
#define WM831X_WDO10_EWW_ACT_MASK               0xC000  /* WDO10_EWW_ACT - [15:14] */
#define WM831X_WDO10_EWW_ACT_SHIFT                  14  /* WDO10_EWW_ACT - [15:14] */
#define WM831X_WDO10_EWW_ACT_WIDTH                   2  /* WDO10_EWW_ACT - [15:14] */
#define WM831X_WDO10_HWC_SWC_MASK               0x1800  /* WDO10_HWC_SWC - [12:11] */
#define WM831X_WDO10_HWC_SWC_SHIFT                  11  /* WDO10_HWC_SWC - [12:11] */
#define WM831X_WDO10_HWC_SWC_WIDTH                   2  /* WDO10_HWC_SWC - [12:11] */
#define WM831X_WDO10_HWC_VSEW                   0x0400  /* WDO10_HWC_VSEW */
#define WM831X_WDO10_HWC_VSEW_MASK              0x0400  /* WDO10_HWC_VSEW */
#define WM831X_WDO10_HWC_VSEW_SHIFT                 10  /* WDO10_HWC_VSEW */
#define WM831X_WDO10_HWC_VSEW_WIDTH                  1  /* WDO10_HWC_VSEW */
#define WM831X_WDO10_HWC_MODE_MASK              0x0300  /* WDO10_HWC_MODE - [9:8] */
#define WM831X_WDO10_HWC_MODE_SHIFT                  8  /* WDO10_HWC_MODE - [9:8] */
#define WM831X_WDO10_HWC_MODE_WIDTH                  2  /* WDO10_HWC_MODE - [9:8] */
#define WM831X_WDO10_FWT                        0x0080  /* WDO10_FWT */
#define WM831X_WDO10_FWT_MASK                   0x0080  /* WDO10_FWT */
#define WM831X_WDO10_FWT_SHIFT                       7  /* WDO10_FWT */
#define WM831X_WDO10_FWT_WIDTH                       1  /* WDO10_FWT */
#define WM831X_WDO10_SWI                        0x0040  /* WDO10_SWI */
#define WM831X_WDO10_SWI_MASK                   0x0040  /* WDO10_SWI */
#define WM831X_WDO10_SWI_SHIFT                       6  /* WDO10_SWI */
#define WM831X_WDO10_SWI_WIDTH                       1  /* WDO10_SWI */

/*
 * W16516 (0x4084) - WDO10 ON Contwow
 */
#define WM831X_WDO10_ON_SWOT_MASK               0xE000  /* WDO10_ON_SWOT - [15:13] */
#define WM831X_WDO10_ON_SWOT_SHIFT                  13  /* WDO10_ON_SWOT - [15:13] */
#define WM831X_WDO10_ON_SWOT_WIDTH                   3  /* WDO10_ON_SWOT - [15:13] */
#define WM831X_WDO10_ON_MODE                    0x0100  /* WDO10_ON_MODE */
#define WM831X_WDO10_ON_MODE_MASK               0x0100  /* WDO10_ON_MODE */
#define WM831X_WDO10_ON_MODE_SHIFT                   8  /* WDO10_ON_MODE */
#define WM831X_WDO10_ON_MODE_WIDTH                   1  /* WDO10_ON_MODE */
#define WM831X_WDO10_ON_VSEW_MASK               0x001F  /* WDO10_ON_VSEW - [4:0] */
#define WM831X_WDO10_ON_VSEW_SHIFT                   0  /* WDO10_ON_VSEW - [4:0] */
#define WM831X_WDO10_ON_VSEW_WIDTH                   5  /* WDO10_ON_VSEW - [4:0] */

/*
 * W16517 (0x4085) - WDO10 SWEEP Contwow
 */
#define WM831X_WDO10_SWP_SWOT_MASK              0xE000  /* WDO10_SWP_SWOT - [15:13] */
#define WM831X_WDO10_SWP_SWOT_SHIFT                 13  /* WDO10_SWP_SWOT - [15:13] */
#define WM831X_WDO10_SWP_SWOT_WIDTH                  3  /* WDO10_SWP_SWOT - [15:13] */
#define WM831X_WDO10_SWP_MODE                   0x0100  /* WDO10_SWP_MODE */
#define WM831X_WDO10_SWP_MODE_MASK              0x0100  /* WDO10_SWP_MODE */
#define WM831X_WDO10_SWP_MODE_SHIFT                  8  /* WDO10_SWP_MODE */
#define WM831X_WDO10_SWP_MODE_WIDTH                  1  /* WDO10_SWP_MODE */
#define WM831X_WDO10_SWP_VSEW_MASK              0x001F  /* WDO10_SWP_VSEW - [4:0] */
#define WM831X_WDO10_SWP_VSEW_SHIFT                  0  /* WDO10_SWP_VSEW - [4:0] */
#define WM831X_WDO10_SWP_VSEW_WIDTH                  5  /* WDO10_SWP_VSEW - [4:0] */

/*
 * W16519 (0x4087) - WDO11 ON Contwow
 */
#define WM831X_WDO11_ON_SWOT_MASK               0xE000  /* WDO11_ON_SWOT - [15:13] */
#define WM831X_WDO11_ON_SWOT_SHIFT                  13  /* WDO11_ON_SWOT - [15:13] */
#define WM831X_WDO11_ON_SWOT_WIDTH                   3  /* WDO11_ON_SWOT - [15:13] */
#define WM831X_WDO11_OFFENA                     0x1000  /* WDO11_OFFENA */
#define WM831X_WDO11_OFFENA_MASK                0x1000  /* WDO11_OFFENA */
#define WM831X_WDO11_OFFENA_SHIFT                   12  /* WDO11_OFFENA */
#define WM831X_WDO11_OFFENA_WIDTH                    1  /* WDO11_OFFENA */
#define WM831X_WDO11_VSEW_SWC                   0x0080  /* WDO11_VSEW_SWC */
#define WM831X_WDO11_VSEW_SWC_MASK              0x0080  /* WDO11_VSEW_SWC */
#define WM831X_WDO11_VSEW_SWC_SHIFT                  7  /* WDO11_VSEW_SWC */
#define WM831X_WDO11_VSEW_SWC_WIDTH                  1  /* WDO11_VSEW_SWC */
#define WM831X_WDO11_ON_VSEW_MASK               0x000F  /* WDO11_ON_VSEW - [3:0] */
#define WM831X_WDO11_ON_VSEW_SHIFT                   0  /* WDO11_ON_VSEW - [3:0] */
#define WM831X_WDO11_ON_VSEW_WIDTH                   4  /* WDO11_ON_VSEW - [3:0] */

/*
 * W16520 (0x4088) - WDO11 SWEEP Contwow
 */
#define WM831X_WDO11_SWP_SWOT_MASK              0xE000  /* WDO11_SWP_SWOT - [15:13] */
#define WM831X_WDO11_SWP_SWOT_SHIFT                 13  /* WDO11_SWP_SWOT - [15:13] */
#define WM831X_WDO11_SWP_SWOT_WIDTH                  3  /* WDO11_SWP_SWOT - [15:13] */
#define WM831X_WDO11_SWP_VSEW_MASK              0x000F  /* WDO11_SWP_VSEW - [3:0] */
#define WM831X_WDO11_SWP_VSEW_SHIFT                  0  /* WDO11_SWP_VSEW - [3:0] */
#define WM831X_WDO11_SWP_VSEW_WIDTH                  4  /* WDO11_SWP_VSEW - [3:0] */

/*
 * W16526 (0x408E) - Powew Good Souwce 1
 */
#define WM831X_DC4_OK                           0x0008  /* DC4_OK */
#define WM831X_DC4_OK_MASK                      0x0008  /* DC4_OK */
#define WM831X_DC4_OK_SHIFT                          3  /* DC4_OK */
#define WM831X_DC4_OK_WIDTH                          1  /* DC4_OK */
#define WM831X_DC3_OK                           0x0004  /* DC3_OK */
#define WM831X_DC3_OK_MASK                      0x0004  /* DC3_OK */
#define WM831X_DC3_OK_SHIFT                          2  /* DC3_OK */
#define WM831X_DC3_OK_WIDTH                          1  /* DC3_OK */
#define WM831X_DC2_OK                           0x0002  /* DC2_OK */
#define WM831X_DC2_OK_MASK                      0x0002  /* DC2_OK */
#define WM831X_DC2_OK_SHIFT                          1  /* DC2_OK */
#define WM831X_DC2_OK_WIDTH                          1  /* DC2_OK */
#define WM831X_DC1_OK                           0x0001  /* DC1_OK */
#define WM831X_DC1_OK_MASK                      0x0001  /* DC1_OK */
#define WM831X_DC1_OK_SHIFT                          0  /* DC1_OK */
#define WM831X_DC1_OK_WIDTH                          1  /* DC1_OK */

/*
 * W16527 (0x408F) - Powew Good Souwce 2
 */
#define WM831X_WDO10_OK                         0x0200  /* WDO10_OK */
#define WM831X_WDO10_OK_MASK                    0x0200  /* WDO10_OK */
#define WM831X_WDO10_OK_SHIFT                        9  /* WDO10_OK */
#define WM831X_WDO10_OK_WIDTH                        1  /* WDO10_OK */
#define WM831X_WDO9_OK                          0x0100  /* WDO9_OK */
#define WM831X_WDO9_OK_MASK                     0x0100  /* WDO9_OK */
#define WM831X_WDO9_OK_SHIFT                         8  /* WDO9_OK */
#define WM831X_WDO9_OK_WIDTH                         1  /* WDO9_OK */
#define WM831X_WDO8_OK                          0x0080  /* WDO8_OK */
#define WM831X_WDO8_OK_MASK                     0x0080  /* WDO8_OK */
#define WM831X_WDO8_OK_SHIFT                         7  /* WDO8_OK */
#define WM831X_WDO8_OK_WIDTH                         1  /* WDO8_OK */
#define WM831X_WDO7_OK                          0x0040  /* WDO7_OK */
#define WM831X_WDO7_OK_MASK                     0x0040  /* WDO7_OK */
#define WM831X_WDO7_OK_SHIFT                         6  /* WDO7_OK */
#define WM831X_WDO7_OK_WIDTH                         1  /* WDO7_OK */
#define WM831X_WDO6_OK                          0x0020  /* WDO6_OK */
#define WM831X_WDO6_OK_MASK                     0x0020  /* WDO6_OK */
#define WM831X_WDO6_OK_SHIFT                         5  /* WDO6_OK */
#define WM831X_WDO6_OK_WIDTH                         1  /* WDO6_OK */
#define WM831X_WDO5_OK                          0x0010  /* WDO5_OK */
#define WM831X_WDO5_OK_MASK                     0x0010  /* WDO5_OK */
#define WM831X_WDO5_OK_SHIFT                         4  /* WDO5_OK */
#define WM831X_WDO5_OK_WIDTH                         1  /* WDO5_OK */
#define WM831X_WDO4_OK                          0x0008  /* WDO4_OK */
#define WM831X_WDO4_OK_MASK                     0x0008  /* WDO4_OK */
#define WM831X_WDO4_OK_SHIFT                         3  /* WDO4_OK */
#define WM831X_WDO4_OK_WIDTH                         1  /* WDO4_OK */
#define WM831X_WDO3_OK                          0x0004  /* WDO3_OK */
#define WM831X_WDO3_OK_MASK                     0x0004  /* WDO3_OK */
#define WM831X_WDO3_OK_SHIFT                         2  /* WDO3_OK */
#define WM831X_WDO3_OK_WIDTH                         1  /* WDO3_OK */
#define WM831X_WDO2_OK                          0x0002  /* WDO2_OK */
#define WM831X_WDO2_OK_MASK                     0x0002  /* WDO2_OK */
#define WM831X_WDO2_OK_SHIFT                         1  /* WDO2_OK */
#define WM831X_WDO2_OK_WIDTH                         1  /* WDO2_OK */
#define WM831X_WDO1_OK                          0x0001  /* WDO1_OK */
#define WM831X_WDO1_OK_MASK                     0x0001  /* WDO1_OK */
#define WM831X_WDO1_OK_SHIFT                         0  /* WDO1_OK */
#define WM831X_WDO1_OK_WIDTH                         1  /* WDO1_OK */

#define WM831X_ISINK_MAX_ISEW 55
extewn const unsigned int wm831x_isinkv_vawues[WM831X_ISINK_MAX_ISEW + 1];

#endif
