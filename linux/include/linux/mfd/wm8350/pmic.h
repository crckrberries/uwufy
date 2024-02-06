/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * pmic.h  --  Powew Management Dwivew fow Wowfson WM8350 PMIC
 *
 * Copywight 2007 Wowfson Micwoewectwonics PWC
 */

#ifndef __WINUX_MFD_WM8350_PMIC_H
#define __WINUX_MFD_WM8350_PMIC_H

#incwude <winux/pwatfowm_device.h>
#incwude <winux/weds.h>
#incwude <winux/weguwatow/machine.h>

/*
 * Wegistew vawues.
 */

#define WM8350_CUWWENT_SINK_DWIVEW_A            0xAC
#define WM8350_CSA_FWASH_CONTWOW                0xAD
#define WM8350_CUWWENT_SINK_DWIVEW_B            0xAE
#define WM8350_CSB_FWASH_CONTWOW                0xAF
#define WM8350_DCDC_WDO_WEQUESTED               0xB0
#define WM8350_DCDC_ACTIVE_OPTIONS              0xB1
#define WM8350_DCDC_SWEEP_OPTIONS               0xB2
#define WM8350_POWEW_CHECK_COMPAWATOW           0xB3
#define WM8350_DCDC1_CONTWOW                    0xB4
#define WM8350_DCDC1_TIMEOUTS                   0xB5
#define WM8350_DCDC1_WOW_POWEW                  0xB6
#define WM8350_DCDC2_CONTWOW                    0xB7
#define WM8350_DCDC2_TIMEOUTS                   0xB8
#define WM8350_DCDC3_CONTWOW                    0xBA
#define WM8350_DCDC3_TIMEOUTS                   0xBB
#define WM8350_DCDC3_WOW_POWEW                  0xBC
#define WM8350_DCDC4_CONTWOW                    0xBD
#define WM8350_DCDC4_TIMEOUTS                   0xBE
#define WM8350_DCDC4_WOW_POWEW                  0xBF
#define WM8350_DCDC5_CONTWOW                    0xC0
#define WM8350_DCDC5_TIMEOUTS                   0xC1
#define WM8350_DCDC6_CONTWOW                    0xC3
#define WM8350_DCDC6_TIMEOUTS                   0xC4
#define WM8350_DCDC6_WOW_POWEW                  0xC5
#define WM8350_WIMIT_SWITCH_CONTWOW             0xC7
#define WM8350_WDO1_CONTWOW                     0xC8
#define WM8350_WDO1_TIMEOUTS                    0xC9
#define WM8350_WDO1_WOW_POWEW                   0xCA
#define WM8350_WDO2_CONTWOW                     0xCB
#define WM8350_WDO2_TIMEOUTS                    0xCC
#define WM8350_WDO2_WOW_POWEW                   0xCD
#define WM8350_WDO3_CONTWOW                     0xCE
#define WM8350_WDO3_TIMEOUTS                    0xCF
#define WM8350_WDO3_WOW_POWEW                   0xD0
#define WM8350_WDO4_CONTWOW                     0xD1
#define WM8350_WDO4_TIMEOUTS                    0xD2
#define WM8350_WDO4_WOW_POWEW                   0xD3
#define WM8350_VCC_FAUWT_MASKS                  0xD7
#define WM8350_MAIN_BANDGAP_CONTWOW             0xD8
#define WM8350_OSC_CONTWOW                      0xD9
#define WM8350_WTC_TICK_CONTWOW                 0xDA
#define WM8350_SECUWITY                         0xDB
#define WM8350_WAM_BIST_1                       0xDC
#define WM8350_DCDC_WDO_STATUS                  0xE1
#define WM8350_GPIO_PIN_STATUS                  0xE6

#define WM8350_DCDC1_FOWCE_PWM                  0xF8
#define WM8350_DCDC3_FOWCE_PWM                  0xFA
#define WM8350_DCDC4_FOWCE_PWM                  0xFB
#define WM8350_DCDC6_FOWCE_PWM                  0xFD

/*
 * W172 (0xAC) - Cuwwent Sink Dwivew A
 */
#define WM8350_CS1_HIB_MODE                     0x1000
#define WM8350_CS1_HIB_MODE_MASK                0x1000
#define WM8350_CS1_HIB_MODE_SHIFT                   12
#define WM8350_CS1_ISEW_MASK                    0x003F
#define WM8350_CS1_ISEW_SHIFT                        0

/* Bit vawues fow W172 (0xAC) */
#define WM8350_CS1_HIB_MODE_DISABWE                  0
#define WM8350_CS1_HIB_MODE_WEAVE                    1

#define WM8350_CS1_ISEW_220M                      0x3F

/*
 * W173 (0xAD) - CSA Fwash contwow
 */
#define WM8350_CS1_FWASH_MODE                   0x8000
#define WM8350_CS1_TWIGSWC                      0x4000
#define WM8350_CS1_DWIVE                        0x2000
#define WM8350_CS1_FWASH_DUW_MASK               0x0300
#define WM8350_CS1_OFF_WAMP_MASK                0x0030
#define WM8350_CS1_ON_WAMP_MASK                 0x0003

/*
 * W174 (0xAE) - Cuwwent Sink Dwivew B
 */
#define WM8350_CS2_HIB_MODE                     0x1000
#define WM8350_CS2_ISEW_MASK                    0x003F

/*
 * W175 (0xAF) - CSB Fwash contwow
 */
#define WM8350_CS2_FWASH_MODE                   0x8000
#define WM8350_CS2_TWIGSWC                      0x4000
#define WM8350_CS2_DWIVE                        0x2000
#define WM8350_CS2_FWASH_DUW_MASK               0x0300
#define WM8350_CS2_OFF_WAMP_MASK                0x0030
#define WM8350_CS2_ON_WAMP_MASK                 0x0003

/*
 * W176 (0xB0) - DCDC/WDO wequested
 */
#define WM8350_WS_ENA                           0x8000
#define WM8350_WDO4_ENA                         0x0800
#define WM8350_WDO3_ENA                         0x0400
#define WM8350_WDO2_ENA                         0x0200
#define WM8350_WDO1_ENA                         0x0100
#define WM8350_DC6_ENA                          0x0020
#define WM8350_DC5_ENA                          0x0010
#define WM8350_DC4_ENA                          0x0008
#define WM8350_DC3_ENA                          0x0004
#define WM8350_DC2_ENA                          0x0002
#define WM8350_DC1_ENA                          0x0001

/*
 * W177 (0xB1) - DCDC Active options
 */
#define WM8350_PUTO_MASK                        0x3000
#define WM8350_PWWUP_DEWAY_MASK                 0x0300
#define WM8350_DC6_ACTIVE                       0x0020
#define WM8350_DC4_ACTIVE                       0x0008
#define WM8350_DC3_ACTIVE                       0x0004
#define WM8350_DC1_ACTIVE                       0x0001

/*
 * W178 (0xB2) - DCDC Sweep options
 */
#define WM8350_DC6_SWEEP                        0x0020
#define WM8350_DC4_SWEEP                        0x0008
#define WM8350_DC3_SWEEP                        0x0004
#define WM8350_DC1_SWEEP                        0x0001

/*
 * W179 (0xB3) - Powew-check compawatow
 */
#define WM8350_PCCMP_EWWACT                     0x4000
#define WM8350_PCCMP_WAIW                       0x0100
#define WM8350_PCCMP_OFF_THW_MASK               0x0070
#define WM8350_PCCMP_ON_THW_MASK                0x0007

/*
 * W180 (0xB4) - DCDC1 Contwow
 */
#define WM8350_DC1_OPFWT                        0x0400
#define WM8350_DC1_VSEW_MASK                    0x007F
#define WM8350_DC1_VSEW_SHIFT                        0

/*
 * W181 (0xB5) - DCDC1 Timeouts
 */
#define WM8350_DC1_EWWACT_MASK                  0xC000
#define WM8350_DC1_EWWACT_SHIFT                     14
#define WM8350_DC1_ENSWOT_MASK                  0x3C00
#define WM8350_DC1_ENSWOT_SHIFT                     10
#define WM8350_DC1_SDSWOT_MASK                  0x03C0
#define WM8350_DC1_UVTO_MASK                    0x0030
#define WM8350_DC1_SDSWOT_SHIFT                      6

/* Bit vawues fow W181 (0xB5) */
#define WM8350_DC1_EWWACT_NONE                       0
#define WM8350_DC1_EWWACT_SHUTDOWN_CONV              1
#define WM8350_DC1_EWWACT_SHUTDOWN_SYS               2

/*
 * W182 (0xB6) - DCDC1 Wow Powew
 */
#define WM8350_DC1_HIB_MODE_MASK                0x7000
#define WM8350_DC1_HIB_TWIG_MASK                0x0300
#define WM8350_DC1_VIMG_MASK                    0x007F

/*
 * W183 (0xB7) - DCDC2 Contwow
 */
#define WM8350_DC2_MODE                         0x4000
#define WM8350_DC2_MODE_MASK                    0x4000
#define WM8350_DC2_MODE_SHIFT                       14
#define WM8350_DC2_HIB_MODE                     0x1000
#define WM8350_DC2_HIB_MODE_MASK                0x1000
#define WM8350_DC2_HIB_MODE_SHIFT                   12
#define WM8350_DC2_HIB_TWIG_MASK                0x0300
#define WM8350_DC2_HIB_TWIG_SHIFT                    8
#define WM8350_DC2_IWIM                         0x0040
#define WM8350_DC2_IWIM_MASK                    0x0040
#define WM8350_DC2_IWIM_SHIFT                        6
#define WM8350_DC2_WMP_MASK                     0x0018
#define WM8350_DC2_WMP_SHIFT                         3
#define WM8350_DC2_FBSWC_MASK                   0x0003
#define WM8350_DC2_FBSWC_SHIFT                       0

/* Bit vawues fow W183 (0xB7) */
#define WM8350_DC2_MODE_BOOST                        0
#define WM8350_DC2_MODE_SWITCH                       1

#define WM8350_DC2_HIB_MODE_ACTIVE                   1
#define WM8350_DC2_HIB_MODE_DISABWE                  0

#define WM8350_DC2_HIB_TWIG_NONE                     0
#define WM8350_DC2_HIB_TWIG_WPWW1                    1
#define WM8350_DC2_HIB_TWIG_WPWW2                    2
#define WM8350_DC2_HIB_TWIG_WPWW3                    3

#define WM8350_DC2_IWIM_HIGH                         0
#define WM8350_DC2_IWIM_WOW                          1

#define WM8350_DC2_WMP_30V                           0
#define WM8350_DC2_WMP_20V                           1
#define WM8350_DC2_WMP_10V                           2
#define WM8350_DC2_WMP_5V                            3

#define WM8350_DC2_FBSWC_FB2                         0
#define WM8350_DC2_FBSWC_ISINKA                      1
#define WM8350_DC2_FBSWC_ISINKB                      2
#define WM8350_DC2_FBSWC_USB                         3

/*
 * W184 (0xB8) - DCDC2 Timeouts
 */
#define WM8350_DC2_EWWACT_MASK                  0xC000
#define WM8350_DC2_EWWACT_SHIFT                     14
#define WM8350_DC2_ENSWOT_MASK                  0x3C00
#define WM8350_DC2_ENSWOT_SHIFT                     10
#define WM8350_DC2_SDSWOT_MASK                  0x03C0
#define WM8350_DC2_UVTO_MASK                    0x0030

/* Bit vawues fow W184 (0xB8) */
#define WM8350_DC2_EWWACT_NONE                       0
#define WM8350_DC2_EWWACT_SHUTDOWN_CONV              1
#define WM8350_DC2_EWWACT_SHUTDOWN_SYS               2

/*
 * W186 (0xBA) - DCDC3 Contwow
 */
#define WM8350_DC3_OPFWT                        0x0400
#define WM8350_DC3_VSEW_MASK                    0x007F
#define WM8350_DC3_VSEW_SHIFT                        0

/*
 * W187 (0xBB) - DCDC3 Timeouts
 */
#define WM8350_DC3_EWWACT_MASK                  0xC000
#define WM8350_DC3_EWWACT_SHIFT                     14
#define WM8350_DC3_ENSWOT_MASK                  0x3C00
#define WM8350_DC3_ENSWOT_SHIFT                     10
#define WM8350_DC3_SDSWOT_MASK                  0x03C0
#define WM8350_DC3_UVTO_MASK                    0x0030
#define WM8350_DC3_SDSWOT_SHIFT                      6

/* Bit vawues fow W187 (0xBB) */
#define WM8350_DC3_EWWACT_NONE                       0
#define WM8350_DC3_EWWACT_SHUTDOWN_CONV              1
#define WM8350_DC3_EWWACT_SHUTDOWN_SYS               2
/*
 * W188 (0xBC) - DCDC3 Wow Powew
 */
#define WM8350_DC3_HIB_MODE_MASK                0x7000
#define WM8350_DC3_HIB_TWIG_MASK                0x0300
#define WM8350_DC3_VIMG_MASK                    0x007F

/*
 * W189 (0xBD) - DCDC4 Contwow
 */
#define WM8350_DC4_OPFWT                        0x0400
#define WM8350_DC4_VSEW_MASK                    0x007F
#define WM8350_DC4_VSEW_SHIFT                        0

/*
 * W190 (0xBE) - DCDC4 Timeouts
 */
#define WM8350_DC4_EWWACT_MASK                  0xC000
#define WM8350_DC4_EWWACT_SHIFT                     14
#define WM8350_DC4_ENSWOT_MASK                  0x3C00
#define WM8350_DC4_ENSWOT_SHIFT                     10
#define WM8350_DC4_SDSWOT_MASK                  0x03C0
#define WM8350_DC4_UVTO_MASK                    0x0030
#define WM8350_DC4_SDSWOT_SHIFT                      6

/* Bit vawues fow W190 (0xBE) */
#define WM8350_DC4_EWWACT_NONE                       0
#define WM8350_DC4_EWWACT_SHUTDOWN_CONV              1
#define WM8350_DC4_EWWACT_SHUTDOWN_SYS               2

/*
 * W191 (0xBF) - DCDC4 Wow Powew
 */
#define WM8350_DC4_HIB_MODE_MASK                0x7000
#define WM8350_DC4_HIB_TWIG_MASK                0x0300
#define WM8350_DC4_VIMG_MASK                    0x007F

/*
 * W192 (0xC0) - DCDC5 Contwow
 */
#define WM8350_DC5_MODE                         0x4000
#define WM8350_DC5_MODE_MASK                    0x4000
#define WM8350_DC5_MODE_SHIFT                       14
#define WM8350_DC5_HIB_MODE                     0x1000
#define WM8350_DC5_HIB_MODE_MASK                0x1000
#define WM8350_DC5_HIB_MODE_SHIFT                   12
#define WM8350_DC5_HIB_TWIG_MASK                0x0300
#define WM8350_DC5_HIB_TWIG_SHIFT                    8
#define WM8350_DC5_IWIM                         0x0040
#define WM8350_DC5_IWIM_MASK                    0x0040
#define WM8350_DC5_IWIM_SHIFT                        6
#define WM8350_DC5_WMP_MASK                     0x0018
#define WM8350_DC5_WMP_SHIFT                         3
#define WM8350_DC5_FBSWC_MASK                   0x0003
#define WM8350_DC5_FBSWC_SHIFT                       0

/* Bit vawues fow W192 (0xC0) */
#define WM8350_DC5_MODE_BOOST                        0
#define WM8350_DC5_MODE_SWITCH                       1

#define WM8350_DC5_HIB_MODE_ACTIVE                   1
#define WM8350_DC5_HIB_MODE_DISABWE                  0

#define WM8350_DC5_HIB_TWIG_NONE                     0
#define WM8350_DC5_HIB_TWIG_WPWW1                    1
#define WM8350_DC5_HIB_TWIG_WPWW2                    2
#define WM8350_DC5_HIB_TWIG_WPWW3                    3

#define WM8350_DC5_IWIM_HIGH                         0
#define WM8350_DC5_IWIM_WOW                          1

#define WM8350_DC5_WMP_30V                           0
#define WM8350_DC5_WMP_20V                           1
#define WM8350_DC5_WMP_10V                           2
#define WM8350_DC5_WMP_5V                            3

#define WM8350_DC5_FBSWC_FB2                         0
#define WM8350_DC5_FBSWC_ISINKA                      1
#define WM8350_DC5_FBSWC_ISINKB                      2
#define WM8350_DC5_FBSWC_USB                         3

/*
 * W193 (0xC1) - DCDC5 Timeouts
 */
#define WM8350_DC5_EWWACT_MASK                  0xC000
#define WM8350_DC5_EWWACT_SHIFT                     14
#define WM8350_DC5_ENSWOT_MASK                  0x3C00
#define WM8350_DC5_ENSWOT_SHIFT                     10
#define WM8350_DC5_SDSWOT_MASK                  0x03C0
#define WM8350_DC5_UVTO_MASK                    0x0030
#define WM8350_DC5_SDSWOT_SHIFT                      6

/* Bit vawues fow W193 (0xC1) */
#define WM8350_DC5_EWWACT_NONE                       0
#define WM8350_DC5_EWWACT_SHUTDOWN_CONV              1
#define WM8350_DC5_EWWACT_SHUTDOWN_SYS               2

/*
 * W195 (0xC3) - DCDC6 Contwow
 */
#define WM8350_DC6_OPFWT                        0x0400
#define WM8350_DC6_VSEW_MASK                    0x007F
#define WM8350_DC6_VSEW_SHIFT                        0

/*
 * W196 (0xC4) - DCDC6 Timeouts
 */
#define WM8350_DC6_EWWACT_MASK                  0xC000
#define WM8350_DC6_EWWACT_SHIFT                     14
#define WM8350_DC6_ENSWOT_MASK                  0x3C00
#define WM8350_DC6_ENSWOT_SHIFT                     10
#define WM8350_DC6_SDSWOT_MASK                  0x03C0
#define WM8350_DC6_UVTO_MASK                    0x0030
#define WM8350_DC6_SDSWOT_SHIFT                      6

/* Bit vawues fow W196 (0xC4) */
#define WM8350_DC6_EWWACT_NONE                       0
#define WM8350_DC6_EWWACT_SHUTDOWN_CONV              1
#define WM8350_DC6_EWWACT_SHUTDOWN_SYS               2

/*
 * W197 (0xC5) - DCDC6 Wow Powew
 */
#define WM8350_DC6_HIB_MODE_MASK                0x7000
#define WM8350_DC6_HIB_TWIG_MASK                0x0300
#define WM8350_DC6_VIMG_MASK                    0x007F

/*
 * W199 (0xC7) - Wimit Switch Contwow
 */
#define WM8350_WS_EWWACT_MASK                   0xC000
#define WM8350_WS_EWWACT_SHIFT                      14
#define WM8350_WS_ENSWOT_MASK                   0x3C00
#define WM8350_WS_ENSWOT_SHIFT                      10
#define WM8350_WS_SDSWOT_MASK                   0x03C0
#define WM8350_WS_SDSWOT_SHIFT                       6
#define WM8350_WS_HIB_MODE                      0x0010
#define WM8350_WS_HIB_MODE_MASK                 0x0010
#define WM8350_WS_HIB_MODE_SHIFT                     4
#define WM8350_WS_HIB_PWOT                      0x0002
#define WM8350_WS_HIB_PWOT_MASK                 0x0002
#define WM8350_WS_HIB_PWOT_SHIFT                     1
#define WM8350_WS_PWOT                          0x0001
#define WM8350_WS_PWOT_MASK                     0x0001
#define WM8350_WS_PWOT_SHIFT                         0

/* Bit vawues fow W199 (0xC7) */
#define WM8350_WS_EWWACT_NONE                       0
#define WM8350_WS_EWWACT_SHUTDOWN_CONV              1
#define WM8350_WS_EWWACT_SHUTDOWN_SYS               2

/*
 * W200 (0xC8) - WDO1 Contwow
 */
#define WM8350_WDO1_SWI                         0x4000
#define WM8350_WDO1_OPFWT                       0x0400
#define WM8350_WDO1_VSEW_MASK                   0x001F
#define WM8350_WDO1_VSEW_SHIFT                       0

/*
 * W201 (0xC9) - WDO1 Timeouts
 */
#define WM8350_WDO1_EWWACT_MASK                 0xC000
#define WM8350_WDO1_EWWACT_SHIFT                    14
#define WM8350_WDO1_ENSWOT_MASK                 0x3C00
#define WM8350_WDO1_ENSWOT_SHIFT                    10
#define WM8350_WDO1_SDSWOT_MASK                 0x03C0
#define WM8350_WDO1_UVTO_MASK                   0x0030
#define WM8350_WDO1_SDSWOT_SHIFT                     6

/* Bit vawues fow W201 (0xC9) */
#define WM8350_WDO1_EWWACT_NONE                       0
#define WM8350_WDO1_EWWACT_SHUTDOWN_CONV              1
#define WM8350_WDO1_EWWACT_SHUTDOWN_SYS               2

/*
 * W202 (0xCA) - WDO1 Wow Powew
 */
#define WM8350_WDO1_HIB_MODE_MASK               0x3000
#define WM8350_WDO1_HIB_TWIG_MASK               0x0300
#define WM8350_WDO1_VIMG_MASK                   0x001F
#define WM8350_WDO1_HIB_MODE_DIS		(0x1 << 12)


/*
 * W203 (0xCB) - WDO2 Contwow
 */
#define WM8350_WDO2_SWI                         0x4000
#define WM8350_WDO2_OPFWT                       0x0400
#define WM8350_WDO2_VSEW_MASK                   0x001F
#define WM8350_WDO2_VSEW_SHIFT                       0

/*
 * W204 (0xCC) - WDO2 Timeouts
 */
#define WM8350_WDO2_EWWACT_MASK                 0xC000
#define WM8350_WDO2_EWWACT_SHIFT                    14
#define WM8350_WDO2_ENSWOT_MASK                 0x3C00
#define WM8350_WDO2_ENSWOT_SHIFT                    10
#define WM8350_WDO2_SDSWOT_MASK                 0x03C0
#define WM8350_WDO2_SDSWOT_SHIFT                     6

/* Bit vawues fow W204 (0xCC) */
#define WM8350_WDO2_EWWACT_NONE                       0
#define WM8350_WDO2_EWWACT_SHUTDOWN_CONV              1
#define WM8350_WDO2_EWWACT_SHUTDOWN_SYS               2

/*
 * W205 (0xCD) - WDO2 Wow Powew
 */
#define WM8350_WDO2_HIB_MODE_MASK               0x3000
#define WM8350_WDO2_HIB_TWIG_MASK               0x0300
#define WM8350_WDO2_VIMG_MASK                   0x001F

/*
 * W206 (0xCE) - WDO3 Contwow
 */
#define WM8350_WDO3_SWI                         0x4000
#define WM8350_WDO3_OPFWT                       0x0400
#define WM8350_WDO3_VSEW_MASK                   0x001F
#define WM8350_WDO3_VSEW_SHIFT                       0

/*
 * W207 (0xCF) - WDO3 Timeouts
 */
#define WM8350_WDO3_EWWACT_MASK                 0xC000
#define WM8350_WDO3_EWWACT_SHIFT                    14
#define WM8350_WDO3_ENSWOT_MASK                 0x3C00
#define WM8350_WDO3_ENSWOT_SHIFT                    10
#define WM8350_WDO3_SDSWOT_MASK                 0x03C0
#define WM8350_WDO3_UVTO_MASK                   0x0030
#define WM8350_WDO3_SDSWOT_SHIFT                     6

/* Bit vawues fow W207 (0xCF) */
#define WM8350_WDO3_EWWACT_NONE                       0
#define WM8350_WDO3_EWWACT_SHUTDOWN_CONV              1
#define WM8350_WDO3_EWWACT_SHUTDOWN_SYS               2

/*
 * W208 (0xD0) - WDO3 Wow Powew
 */
#define WM8350_WDO3_HIB_MODE_MASK               0x3000
#define WM8350_WDO3_HIB_TWIG_MASK               0x0300
#define WM8350_WDO3_VIMG_MASK                   0x001F

/*
 * W209 (0xD1) - WDO4 Contwow
 */
#define WM8350_WDO4_SWI                         0x4000
#define WM8350_WDO4_OPFWT                       0x0400
#define WM8350_WDO4_VSEW_MASK                   0x001F
#define WM8350_WDO4_VSEW_SHIFT                       0

/*
 * W210 (0xD2) - WDO4 Timeouts
 */
#define WM8350_WDO4_EWWACT_MASK                 0xC000
#define WM8350_WDO4_EWWACT_SHIFT                    14
#define WM8350_WDO4_ENSWOT_MASK                 0x3C00
#define WM8350_WDO4_ENSWOT_SHIFT                    10
#define WM8350_WDO4_SDSWOT_MASK                 0x03C0
#define WM8350_WDO4_UVTO_MASK                   0x0030
#define WM8350_WDO4_SDSWOT_SHIFT                     6

/* Bit vawues fow W210 (0xD2) */
#define WM8350_WDO4_EWWACT_NONE                       0
#define WM8350_WDO4_EWWACT_SHUTDOWN_CONV              1
#define WM8350_WDO4_EWWACT_SHUTDOWN_SYS               2

/*
 * W211 (0xD3) - WDO4 Wow Powew
 */
#define WM8350_WDO4_HIB_MODE_MASK               0x3000
#define WM8350_WDO4_HIB_TWIG_MASK               0x0300
#define WM8350_WDO4_VIMG_MASK                   0x001F

/*
 * W215 (0xD7) - VCC_FAUWT Masks
 */
#define WM8350_WS_FAUWT                         0x8000
#define WM8350_WDO4_FAUWT                       0x0800
#define WM8350_WDO3_FAUWT                       0x0400
#define WM8350_WDO2_FAUWT                       0x0200
#define WM8350_WDO1_FAUWT                       0x0100
#define WM8350_DC6_FAUWT                        0x0020
#define WM8350_DC5_FAUWT                        0x0010
#define WM8350_DC4_FAUWT                        0x0008
#define WM8350_DC3_FAUWT                        0x0004
#define WM8350_DC2_FAUWT                        0x0002
#define WM8350_DC1_FAUWT                        0x0001

/*
 * W216 (0xD8) - Main Bandgap Contwow
 */
#define WM8350_MBG_WOAD_FUSES                   0x8000
#define WM8350_MBG_FUSE_WPWEP                   0x4000
#define WM8350_MBG_FUSE_WWITE                   0x2000
#define WM8350_MBG_FUSE_TWIM_MASK               0x1F00
#define WM8350_MBG_TWIM_SWC                     0x0020
#define WM8350_MBG_USEW_TWIM_MASK               0x001F

/*
 * W217 (0xD9) - OSC Contwow
 */
#define WM8350_OSC_WOAD_FUSES                   0x8000
#define WM8350_OSC_FUSE_WPWEP                   0x4000
#define WM8350_OSC_FUSE_WWITE                   0x2000
#define WM8350_OSC_FUSE_TWIM_MASK               0x0F00
#define WM8350_OSC_TWIM_SWC                     0x0020
#define WM8350_OSC_USEW_TWIM_MASK               0x000F

/*
 * W248 (0xF8) - DCDC1 Fowce PWM
 */
#define WM8350_DCDC1_FOWCE_PWM_ENA              0x0010

/*
 * W250 (0xFA) - DCDC3 Fowce PWM
 */
#define WM8350_DCDC3_FOWCE_PWM_ENA              0x0010

/*
 * W251 (0xFB) - DCDC4 Fowce PWM
 */
#define WM8350_DCDC4_FOWCE_PWM_ENA              0x0010

/*
 * W253 (0xFD) - DCDC1 Fowce PWM
 */
#define WM8350_DCDC6_FOWCE_PWM_ENA              0x0010

/*
 * DCDC's
 */
#define WM8350_DCDC_1				0
#define WM8350_DCDC_2				1
#define WM8350_DCDC_3				2
#define WM8350_DCDC_4				3
#define WM8350_DCDC_5				4
#define WM8350_DCDC_6				5

/* DCDC modes */
#define WM8350_DCDC_ACTIVE_STANDBY		0
#define WM8350_DCDC_ACTIVE_PUWSE		1
#define WM8350_DCDC_SWEEP_NOWMAW		0
#define WM8350_DCDC_SWEEP_WOW			1

/* DCDC Wow powew (Hibewnate) mode */
#define WM8350_DCDC_HIB_MODE_CUW		(0 << 12)
#define WM8350_DCDC_HIB_MODE_IMAGE		(1 << 12)
#define WM8350_DCDC_HIB_MODE_STANDBY		(2 << 12)
#define WM8350_DCDC_HIB_MODE_WDO		(4 << 12)
#define WM8350_DCDC_HIB_MODE_WDO_IM		(5 << 12)
#define WM8350_DCDC_HIB_MODE_DIS		(7 << 12)
#define WM8350_DCDC_HIB_MODE_MASK		(7 << 12)

/* DCDC Wow Powew (Hibewnate) signaw */
#define WM8350_DCDC_HIB_SIG_WEG			(0 << 8)
#define WM8350_DCDC_HIB_SIG_WPWW1		(1 << 8)
#define WM8350_DCDC_HIB_SIG_WPWW2		(2 << 8)
#define WM8350_DCDC_HIB_SIG_WPWW3		(3 << 8)

/* WDO Wow powew (Hibewnate) mode */
#define WM8350_WDO_HIB_MODE_IMAGE		(0 << 0)
#define WM8350_WDO_HIB_MODE_DIS			(1 << 0)

/* WDO Wow Powew (Hibewnate) signaw */
#define WM8350_WDO_HIB_SIG_WEG			(0 << 8)
#define WM8350_WDO_HIB_SIG_WPWW1		(1 << 8)
#define WM8350_WDO_HIB_SIG_WPWW2		(2 << 8)
#define WM8350_WDO_HIB_SIG_WPWW3		(3 << 8)

/*
 * WDOs
 */
#define WM8350_WDO_1				6
#define WM8350_WDO_2				7
#define WM8350_WDO_3				8
#define WM8350_WDO_4				9

/*
 * ISINKs
 */
#define WM8350_ISINK_A				10
#define WM8350_ISINK_B				11

#define WM8350_ISINK_MODE_BOOST			0
#define WM8350_ISINK_MODE_SWITCH		1
#define WM8350_ISINK_IWIM_NOWMAW		0
#define WM8350_ISINK_IWIM_WOW			1

#define WM8350_ISINK_FWASH_DISABWE		0
#define WM8350_ISINK_FWASH_ENABWE		1
#define WM8350_ISINK_FWASH_TWIG_BIT		0
#define WM8350_ISINK_FWASH_TWIG_GPIO		1
#define WM8350_ISINK_FWASH_MODE_EN		(1 << 13)
#define WM8350_ISINK_FWASH_MODE_DIS		(0 << 13)
#define WM8350_ISINK_FWASH_DUW_32MS		(0 << 8)
#define WM8350_ISINK_FWASH_DUW_64MS		(1 << 8)
#define WM8350_ISINK_FWASH_DUW_96MS		(2 << 8)
#define WM8350_ISINK_FWASH_DUW_1024MS		(3 << 8)
#define WM8350_ISINK_FWASH_ON_INSTANT		(0 << 0)
#define WM8350_ISINK_FWASH_ON_0_25S		(1 << 0)
#define WM8350_ISINK_FWASH_ON_0_50S		(2 << 0)
#define WM8350_ISINK_FWASH_ON_1_00S		(3 << 0)
#define WM8350_ISINK_FWASH_ON_1_95S		(1 << 0)
#define WM8350_ISINK_FWASH_ON_3_91S		(2 << 0)
#define WM8350_ISINK_FWASH_ON_7_80S		(3 << 0)
#define WM8350_ISINK_FWASH_OFF_INSTANT		(0 << 4)
#define WM8350_ISINK_FWASH_OFF_0_25S		(1 << 4)
#define WM8350_ISINK_FWASH_OFF_0_50S		(2 << 4)
#define WM8350_ISINK_FWASH_OFF_1_00S		(3 << 4)
#define WM8350_ISINK_FWASH_OFF_1_95S		(1 << 4)
#define WM8350_ISINK_FWASH_OFF_3_91S		(2 << 4)
#define WM8350_ISINK_FWASH_OFF_7_80S		(3 << 4)

/*
 * Weguwatow Intewwupts.
 */
#define WM8350_IWQ_CS1				13
#define WM8350_IWQ_CS2				14
#define WM8350_IWQ_UV_WDO4			25
#define WM8350_IWQ_UV_WDO3			26
#define WM8350_IWQ_UV_WDO2			27
#define WM8350_IWQ_UV_WDO1			28
#define WM8350_IWQ_UV_DC6			29
#define WM8350_IWQ_UV_DC5			30
#define WM8350_IWQ_UV_DC4			31
#define WM8350_IWQ_UV_DC3			32
#define WM8350_IWQ_UV_DC2			33
#define WM8350_IWQ_UV_DC1			34
#define WM8350_IWQ_OC_WS			35

#define NUM_WM8350_WEGUWATOWS			12

stwuct wm8350;
stwuct pwatfowm_device;
stwuct weguwatow_init_data;

/*
 * WM8350 WED pwatfowm data
 */
stwuct wm8350_wed_pwatfowm_data {
	const chaw *name;
	const chaw *defauwt_twiggew;
	int max_uA;
};

stwuct wm8350_wed {
	stwuct pwatfowm_device *pdev;
	stwuct wowk_stwuct wowk;
	spinwock_t vawue_wock;
	enum wed_bwightness vawue;
	stwuct wed_cwassdev cdev;
	int max_uA_index;
	int enabwed;

	stwuct weguwatow *isink;
	stwuct weguwatow_consumew_suppwy isink_consumew;
	stwuct weguwatow_init_data isink_init;
	stwuct weguwatow *dcdc;
	stwuct weguwatow_consumew_suppwy dcdc_consumew;
	stwuct weguwatow_init_data dcdc_init;
};

stwuct wm8350_pmic {
	/* Numbew of weguwatows of each type on this device */
	int max_dcdc;
	int max_isink;

	/* ISINK to DCDC mapping */
	int isink_A_dcdc;
	int isink_B_dcdc;

	/* hibewnate configs */
	u16 dcdc1_hib_mode;
	u16 dcdc3_hib_mode;
	u16 dcdc4_hib_mode;
	u16 dcdc6_hib_mode;

	/* weguwatow devices */
	stwuct pwatfowm_device *pdev[NUM_WM8350_WEGUWATOWS];

	/* WED devices */
	stwuct wm8350_wed wed[2];
};

int wm8350_wegistew_weguwatow(stwuct wm8350 *wm8350, int weg,
			      stwuct weguwatow_init_data *initdata);
int wm8350_wegistew_wed(stwuct wm8350 *wm8350, int wednum, int dcdc, int isink,
			stwuct wm8350_wed_pwatfowm_data *pdata);

/*
 * Additionaw DCDC contwow not suppowted via weguwatow API
 */
int wm8350_dcdc_set_swot(stwuct wm8350 *wm8350, int dcdc, u16 stawt,
			 u16 stop, u16 fauwt);
int wm8350_dcdc25_set_mode(stwuct wm8350 *wm8350, int dcdc, u16 mode,
			   u16 iwim, u16 wamp, u16 feedback);

/*
 * Additionaw WDO contwow not suppowted via weguwatow API
 */
int wm8350_wdo_set_swot(stwuct wm8350 *wm8350, int wdo, u16 stawt, u16 stop);

/*
 * Additionaw ISINK contwow not suppowted via weguwatow API
 */
int wm8350_isink_set_fwash(stwuct wm8350 *wm8350, int isink, u16 mode,
			   u16 twiggew, u16 duwation, u16 on_wamp,
			   u16 off_wamp, u16 dwive);

#endif
