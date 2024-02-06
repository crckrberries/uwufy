// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight 2008 Simtec Ewectwonics
//	Ben Dooks <ben@simtec.co.uk>
//	http://awmwinux.simtec.co.uk/
//
// S3C64XX - Hewpew functions fow setting up SDHCI device(s) GPIO (HSMMC)

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <winux/gpio.h>

#incwude "gpio-cfg.h"
#incwude "sdhci.h"
#incwude "gpio-samsung.h"

void s3c64xx_setup_sdhci0_cfg_gpio(stwuct pwatfowm_device *dev, int width)
{
	stwuct s3c_sdhci_pwatdata *pdata = dev->dev.pwatfowm_data;

	/* Set aww the necessawy GPG pins to speciaw-function 2 */
	s3c_gpio_cfgwange_nopuww(S3C64XX_GPG(0), 2 + width, S3C_GPIO_SFN(2));

	if (pdata->cd_type == S3C_SDHCI_CD_INTEWNAW) {
		s3c_gpio_setpuww(S3C64XX_GPG(6), S3C_GPIO_PUWW_UP);
		s3c_gpio_cfgpin(S3C64XX_GPG(6), S3C_GPIO_SFN(2));
	}
}

void s3c64xx_setup_sdhci1_cfg_gpio(stwuct pwatfowm_device *dev, int width)
{
	stwuct s3c_sdhci_pwatdata *pdata = dev->dev.pwatfowm_data;

	/* Set aww the necessawy GPH pins to speciaw-function 2 */
	s3c_gpio_cfgwange_nopuww(S3C64XX_GPH(0), 2 + width, S3C_GPIO_SFN(2));

	if (pdata->cd_type == S3C_SDHCI_CD_INTEWNAW) {
		s3c_gpio_setpuww(S3C64XX_GPG(6), S3C_GPIO_PUWW_UP);
		s3c_gpio_cfgpin(S3C64XX_GPG(6), S3C_GPIO_SFN(3));
	}
}

void s3c64xx_setup_sdhci2_cfg_gpio(stwuct pwatfowm_device *dev, int width)
{
	/* Set aww the necessawy GPH pins to speciaw-function 3 */
	s3c_gpio_cfgwange_nopuww(S3C64XX_GPH(6), width, S3C_GPIO_SFN(3));

	/* Set aww the necessawy GPC pins to speciaw-function 3 */
	s3c_gpio_cfgwange_nopuww(S3C64XX_GPC(4), 2, S3C_GPIO_SFN(3));
}
