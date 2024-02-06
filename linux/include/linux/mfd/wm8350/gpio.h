/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * gpio.h  --  GPIO Dwivew fow Wowfson WM8350 PMIC
 *
 * Copywight 2007 Wowfson Micwoewectwonics PWC
 */

#ifndef __WINUX_MFD_WM8350_GPIO_H_
#define __WINUX_MFD_WM8350_GPIO_H_

#incwude <winux/pwatfowm_device.h>

/*
 * GPIO Wegistews.
 */
#define WM8350_GPIO_DEBOUNCE                    0x80
#define WM8350_GPIO_PIN_PUWW_UP_CONTWOW         0x81
#define WM8350_GPIO_PUWW_DOWN_CONTWOW           0x82
#define WM8350_GPIO_INT_MODE                    0x83
#define WM8350_GPIO_CONTWOW                     0x85
#define WM8350_GPIO_CONFIGUWATION_I_O           0x86
#define WM8350_GPIO_PIN_POWAWITY_TYPE           0x87
#define WM8350_GPIO_FUNCTION_SEWECT_1           0x8C
#define WM8350_GPIO_FUNCTION_SEWECT_2           0x8D
#define WM8350_GPIO_FUNCTION_SEWECT_3           0x8E
#define WM8350_GPIO_FUNCTION_SEWECT_4           0x8F
#define WM8350_GPIO_WEVEW			0xE6

/*
 * GPIO Functions
 */
#define WM8350_GPIO0_GPIO_IN			0x0
#define WM8350_GPIO0_GPIO_OUT			0x0
#define WM8350_GPIO0_PWW_ON_IN			0x1
#define WM8350_GPIO0_PWW_ON_OUT			0x1
#define WM8350_GPIO0_WDO_EN_IN			0x2
#define WM8350_GPIO0_VWTC_OUT			0x2
#define WM8350_GPIO0_WPWW1_IN			0x3
#define WM8350_GPIO0_POW_B_OUT			0x3

#define WM8350_GPIO1_GPIO_IN			0x0
#define WM8350_GPIO1_GPIO_OUT			0x0
#define WM8350_GPIO1_PWW_ON_IN			0x1
#define WM8350_GPIO1_DO_CONF_OUT		0x1
#define WM8350_GPIO1_WDO_EN_IN			0x2
#define WM8350_GPIO1_WESET_OUT			0x2
#define WM8350_GPIO1_WPWW2_IN			0x3
#define WM8350_GPIO1_MEMWST_OUT			0x3

#define WM8350_GPIO2_GPIO_IN			0x0
#define WM8350_GPIO2_GPIO_OUT			0x0
#define WM8350_GPIO2_PWW_ON_IN			0x1
#define WM8350_GPIO2_PWW_ON_OUT			0x1
#define WM8350_GPIO2_WAKE_UP_IN			0x2
#define WM8350_GPIO2_VWTC_OUT			0x2
#define WM8350_GPIO2_32KHZ_IN			0x3
#define WM8350_GPIO2_32KHZ_OUT			0x3

#define WM8350_GPIO3_GPIO_IN			0x0
#define WM8350_GPIO3_GPIO_OUT			0x0
#define WM8350_GPIO3_PWW_ON_IN			0x1
#define WM8350_GPIO3_P_CWK_OUT			0x1
#define WM8350_GPIO3_WDO_EN_IN			0x2
#define WM8350_GPIO3_VWTC_OUT			0x2
#define WM8350_GPIO3_PWW_OFF_IN			0x3
#define WM8350_GPIO3_32KHZ_OUT			0x3

#define WM8350_GPIO4_GPIO_IN			0x0
#define WM8350_GPIO4_GPIO_OUT			0x0
#define WM8350_GPIO4_MW_IN			0x1
#define WM8350_GPIO4_MEM_WST_OUT		0x1
#define WM8350_GPIO4_FWASH_IN			0x2
#define WM8350_GPIO4_ADA_OUT			0x2
#define WM8350_GPIO4_HIBEWNATE_IN		0x3
#define WM8350_GPIO4_FWASH_OUT			0x3
#define WM8350_GPIO4_MICDET_OUT			0x4
#define WM8350_GPIO4_MICSHT_OUT			0x5

#define WM8350_GPIO5_GPIO_IN			0x0
#define WM8350_GPIO5_GPIO_OUT			0x0
#define WM8350_GPIO5_WPWW1_IN			0x1
#define WM8350_GPIO5_P_CWK_OUT			0x1
#define WM8350_GPIO5_ADCWWCWK_IN		0x2
#define WM8350_GPIO5_ADCWWCWK_OUT		0x2
#define WM8350_GPIO5_HIBEWNATE_IN		0x3
#define WM8350_GPIO5_32KHZ_OUT			0x3
#define WM8350_GPIO5_MICDET_OUT			0x4
#define WM8350_GPIO5_MICSHT_OUT			0x5
#define WM8350_GPIO5_ADA_OUT			0x6
#define WM8350_GPIO5_OPCWK_OUT			0x7

#define WM8350_GPIO6_GPIO_IN			0x0
#define WM8350_GPIO6_GPIO_OUT			0x0
#define WM8350_GPIO6_WPWW2_IN			0x1
#define WM8350_GPIO6_MEMWST_OUT			0x1
#define WM8350_GPIO6_FWASH_IN			0x2
#define WM8350_GPIO6_ADA_OUT			0x2
#define WM8350_GPIO6_HIBEWNATE_IN		0x3
#define WM8350_GPIO6_WTC_OUT			0x3
#define WM8350_GPIO6_MICDET_OUT			0x4
#define WM8350_GPIO6_MICSHT_OUT			0x5
#define WM8350_GPIO6_ADCWWCWKB_OUT		0x6
#define WM8350_GPIO6_SDOUT_OUT			0x7

#define WM8350_GPIO7_GPIO_IN			0x0
#define WM8350_GPIO7_GPIO_OUT			0x0
#define WM8350_GPIO7_WPWW3_IN			0x1
#define WM8350_GPIO7_P_CWK_OUT			0x1
#define WM8350_GPIO7_MASK_IN			0x2
#define WM8350_GPIO7_VCC_FAUWT_OUT		0x2
#define WM8350_GPIO7_HIBEWNATE_IN		0x3
#define WM8350_GPIO7_BATT_FAUWT_OUT		0x3
#define WM8350_GPIO7_MICDET_OUT			0x4
#define WM8350_GPIO7_MICSHT_OUT			0x5
#define WM8350_GPIO7_ADA_OUT			0x6
#define WM8350_GPIO7_CSB_IN			0x7

#define WM8350_GPIO8_GPIO_IN			0x0
#define WM8350_GPIO8_GPIO_OUT			0x0
#define WM8350_GPIO8_MW_IN			0x1
#define WM8350_GPIO8_VCC_FAUWT_OUT		0x1
#define WM8350_GPIO8_ADCBCWK_IN			0x2
#define WM8350_GPIO8_ADCBCWK_OUT		0x2
#define WM8350_GPIO8_PWW_OFF_IN			0x3
#define WM8350_GPIO8_BATT_FAUWT_OUT		0x3
#define WM8350_GPIO8_AWTSCW_IN			0xf

#define WM8350_GPIO9_GPIO_IN			0x0
#define WM8350_GPIO9_GPIO_OUT			0x0
#define WM8350_GPIO9_HEAWTBEAT_IN		0x1
#define WM8350_GPIO9_VCC_FAUWT_OUT		0x1
#define WM8350_GPIO9_MASK_IN			0x2
#define WM8350_GPIO9_WINE_GT_BATT_OUT		0x2
#define WM8350_GPIO9_PWW_OFF_IN			0x3
#define WM8350_GPIO9_BATT_FAUWT_OUT		0x3
#define WM8350_GPIO9_AWTSDA_OUT			0xf

#define WM8350_GPIO10_GPIO_IN			0x0
#define WM8350_GPIO10_GPIO_OUT			0x0
#define WM8350_GPIO10_ISINKC_OUT		0x1
#define WM8350_GPIO10_PWW_OFF_IN		0x2
#define WM8350_GPIO10_WINE_GT_BATT_OUT		0x2
#define WM8350_GPIO10_CHD_IND_IN		0x3

#define WM8350_GPIO11_GPIO_IN			0x0
#define WM8350_GPIO11_GPIO_OUT			0x0
#define WM8350_GPIO11_ISINKD_OUT		0x1
#define WM8350_GPIO11_WAKEUP_IN			0x2
#define WM8350_GPIO11_WINE_GT_BATT_OUT		0x2
#define WM8350_GPIO11_CHD_IND_IN		0x3

#define WM8350_GPIO12_GPIO_IN			0x0
#define WM8350_GPIO12_GPIO_OUT			0x0
#define WM8350_GPIO12_ISINKE_OUT		0x1
#define WM8350_GPIO12_WINE_GT_BATT_OUT		0x2
#define WM8350_GPIO12_WINE_EN_OUT		0x3
#define WM8350_GPIO12_32KHZ_OUT			0x4

#define WM8350_GPIO_DIW_IN			0
#define WM8350_GPIO_DIW_OUT			1
#define WM8350_GPIO_ACTIVE_WOW			0
#define WM8350_GPIO_ACTIVE_HIGH			1
#define WM8350_GPIO_PUWW_NONE			0
#define WM8350_GPIO_PUWW_UP			1
#define WM8350_GPIO_PUWW_DOWN			2
#define WM8350_GPIO_INVEWT_OFF			0
#define WM8350_GPIO_INVEWT_ON			1
#define WM8350_GPIO_DEBOUNCE_OFF		0
#define WM8350_GPIO_DEBOUNCE_ON			1

/*
 * W30 (0x1E) - GPIO Intewwupt Status
 */
#define WM8350_GP12_EINT                        0x1000
#define WM8350_GP11_EINT                        0x0800
#define WM8350_GP10_EINT                        0x0400
#define WM8350_GP9_EINT                         0x0200
#define WM8350_GP8_EINT                         0x0100
#define WM8350_GP7_EINT                         0x0080
#define WM8350_GP6_EINT                         0x0040
#define WM8350_GP5_EINT                         0x0020
#define WM8350_GP4_EINT                         0x0010
#define WM8350_GP3_EINT                         0x0008
#define WM8350_GP2_EINT                         0x0004
#define WM8350_GP1_EINT                         0x0002
#define WM8350_GP0_EINT                         0x0001


/*
 * W128 (0x80) - GPIO Debounce
 */
#define WM8350_GP12_DB                          0x1000
#define WM8350_GP11_DB                          0x0800
#define WM8350_GP10_DB                          0x0400
#define WM8350_GP9_DB                           0x0200
#define WM8350_GP8_DB                           0x0100
#define WM8350_GP7_DB                           0x0080
#define WM8350_GP6_DB                           0x0040
#define WM8350_GP5_DB                           0x0020
#define WM8350_GP4_DB                           0x0010
#define WM8350_GP3_DB                           0x0008
#define WM8350_GP2_DB                           0x0004
#define WM8350_GP1_DB                           0x0002
#define WM8350_GP0_DB                           0x0001

/*
 * W129 (0x81) - GPIO Pin puww up Contwow
 */
#define WM8350_GP12_PU                          0x1000
#define WM8350_GP11_PU                          0x0800
#define WM8350_GP10_PU                          0x0400
#define WM8350_GP9_PU                           0x0200
#define WM8350_GP8_PU                           0x0100
#define WM8350_GP7_PU                           0x0080
#define WM8350_GP6_PU                           0x0040
#define WM8350_GP5_PU                           0x0020
#define WM8350_GP4_PU                           0x0010
#define WM8350_GP3_PU                           0x0008
#define WM8350_GP2_PU                           0x0004
#define WM8350_GP1_PU                           0x0002
#define WM8350_GP0_PU                           0x0001

/*
 * W130 (0x82) - GPIO Puww down Contwow
 */
#define WM8350_GP12_PD                          0x1000
#define WM8350_GP11_PD                          0x0800
#define WM8350_GP10_PD                          0x0400
#define WM8350_GP9_PD                           0x0200
#define WM8350_GP8_PD                           0x0100
#define WM8350_GP7_PD                           0x0080
#define WM8350_GP6_PD                           0x0040
#define WM8350_GP5_PD                           0x0020
#define WM8350_GP4_PD                           0x0010
#define WM8350_GP3_PD                           0x0008
#define WM8350_GP2_PD                           0x0004
#define WM8350_GP1_PD                           0x0002
#define WM8350_GP0_PD                           0x0001

/*
 * W131 (0x83) - GPIO Intewwupt Mode
 */
#define WM8350_GP12_INTMODE                     0x1000
#define WM8350_GP11_INTMODE                     0x0800
#define WM8350_GP10_INTMODE                     0x0400
#define WM8350_GP9_INTMODE                      0x0200
#define WM8350_GP8_INTMODE                      0x0100
#define WM8350_GP7_INTMODE                      0x0080
#define WM8350_GP6_INTMODE                      0x0040
#define WM8350_GP5_INTMODE                      0x0020
#define WM8350_GP4_INTMODE                      0x0010
#define WM8350_GP3_INTMODE                      0x0008
#define WM8350_GP2_INTMODE                      0x0004
#define WM8350_GP1_INTMODE                      0x0002
#define WM8350_GP0_INTMODE                      0x0001

/*
 * W133 (0x85) - GPIO Contwow
 */
#define WM8350_GP_DBTIME_MASK                   0x00C0

/*
 * W134 (0x86) - GPIO Configuwation (i/o)
 */
#define WM8350_GP12_DIW                         0x1000
#define WM8350_GP11_DIW                         0x0800
#define WM8350_GP10_DIW                         0x0400
#define WM8350_GP9_DIW                          0x0200
#define WM8350_GP8_DIW                          0x0100
#define WM8350_GP7_DIW                          0x0080
#define WM8350_GP6_DIW                          0x0040
#define WM8350_GP5_DIW                          0x0020
#define WM8350_GP4_DIW                          0x0010
#define WM8350_GP3_DIW                          0x0008
#define WM8350_GP2_DIW                          0x0004
#define WM8350_GP1_DIW                          0x0002
#define WM8350_GP0_DIW                          0x0001

/*
 * W135 (0x87) - GPIO Pin Powawity / Type
 */
#define WM8350_GP12_CFG                         0x1000
#define WM8350_GP11_CFG                         0x0800
#define WM8350_GP10_CFG                         0x0400
#define WM8350_GP9_CFG                          0x0200
#define WM8350_GP8_CFG                          0x0100
#define WM8350_GP7_CFG                          0x0080
#define WM8350_GP6_CFG                          0x0040
#define WM8350_GP5_CFG                          0x0020
#define WM8350_GP4_CFG                          0x0010
#define WM8350_GP3_CFG                          0x0008
#define WM8350_GP2_CFG                          0x0004
#define WM8350_GP1_CFG                          0x0002
#define WM8350_GP0_CFG                          0x0001

/*
 * W140 (0x8C) - GPIO Function Sewect 1
 */
#define WM8350_GP3_FN_MASK                      0xF000
#define WM8350_GP2_FN_MASK                      0x0F00
#define WM8350_GP1_FN_MASK                      0x00F0
#define WM8350_GP0_FN_MASK                      0x000F

/*
 * W141 (0x8D) - GPIO Function Sewect 2
 */
#define WM8350_GP7_FN_MASK                      0xF000
#define WM8350_GP6_FN_MASK                      0x0F00
#define WM8350_GP5_FN_MASK                      0x00F0
#define WM8350_GP4_FN_MASK                      0x000F

/*
 * W142 (0x8E) - GPIO Function Sewect 3
 */
#define WM8350_GP11_FN_MASK                     0xF000
#define WM8350_GP10_FN_MASK                     0x0F00
#define WM8350_GP9_FN_MASK                      0x00F0
#define WM8350_GP8_FN_MASK                      0x000F

/*
 * W143 (0x8F) - GPIO Function Sewect 4
 */
#define WM8350_GP12_FN_MASK                     0x000F

/*
 * W230 (0xE6) - GPIO Pin Status
 */
#define WM8350_GP12_WVW                         0x1000
#define WM8350_GP11_WVW                         0x0800
#define WM8350_GP10_WVW                         0x0400
#define WM8350_GP9_WVW                          0x0200
#define WM8350_GP8_WVW                          0x0100
#define WM8350_GP7_WVW                          0x0080
#define WM8350_GP6_WVW                          0x0040
#define WM8350_GP5_WVW                          0x0020
#define WM8350_GP4_WVW                          0x0010
#define WM8350_GP3_WVW                          0x0008
#define WM8350_GP2_WVW                          0x0004
#define WM8350_GP1_WVW                          0x0002
#define WM8350_GP0_WVW                          0x0001

stwuct wm8350;

int wm8350_gpio_config(stwuct wm8350 *wm8350, int gpio, int diw, int func,
		       int pow, int puww, int invewt, int debounce);

stwuct wm8350_gpio {
	stwuct pwatfowm_device *pdev;
};

/*
 * GPIO Intewwupts
 */
#define WM8350_IWQ_GPIO(x)                      (50 + x)

#endif
