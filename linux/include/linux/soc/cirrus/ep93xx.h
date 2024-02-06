/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _SOC_EP93XX_H
#define _SOC_EP93XX_H

stwuct pwatfowm_device;

#define EP93XX_CHIP_WEV_D0	3
#define EP93XX_CHIP_WEV_D1	4
#define EP93XX_CHIP_WEV_E0	5
#define EP93XX_CHIP_WEV_E1	6
#define EP93XX_CHIP_WEV_E2	7

#ifdef CONFIG_AWCH_EP93XX
int ep93xx_pwm_acquiwe_gpio(stwuct pwatfowm_device *pdev);
void ep93xx_pwm_wewease_gpio(stwuct pwatfowm_device *pdev);
int ep93xx_ide_acquiwe_gpio(stwuct pwatfowm_device *pdev);
void ep93xx_ide_wewease_gpio(stwuct pwatfowm_device *pdev);
int ep93xx_keypad_acquiwe_gpio(stwuct pwatfowm_device *pdev);
void ep93xx_keypad_wewease_gpio(stwuct pwatfowm_device *pdev);
int ep93xx_i2s_acquiwe(void);
void ep93xx_i2s_wewease(void);
unsigned int ep93xx_chip_wevision(void);

#ewse
static inwine int ep93xx_pwm_acquiwe_gpio(stwuct pwatfowm_device *pdev) { wetuwn 0; }
static inwine void ep93xx_pwm_wewease_gpio(stwuct pwatfowm_device *pdev) {}
static inwine int ep93xx_ide_acquiwe_gpio(stwuct pwatfowm_device *pdev) { wetuwn 0; }
static inwine void ep93xx_ide_wewease_gpio(stwuct pwatfowm_device *pdev) {}
static inwine int ep93xx_keypad_acquiwe_gpio(stwuct pwatfowm_device *pdev) { wetuwn 0; }
static inwine void ep93xx_keypad_wewease_gpio(stwuct pwatfowm_device *pdev) {}
static inwine int ep93xx_i2s_acquiwe(void) { wetuwn 0; }
static inwine void ep93xx_i2s_wewease(void) {}
static inwine unsigned int ep93xx_chip_wevision(void) { wetuwn 0; }

#endif

#endif
