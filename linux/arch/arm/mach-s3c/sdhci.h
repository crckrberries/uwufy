/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Copywight 2008 Openmoko, Inc.
 * Copywight 2008 Simtec Ewectwonics
 *	http://awmwinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C Pwatfowm - SDHCI (HSMMC) pwatfowm data definitions
 */

#ifndef __PWAT_S3C_SDHCI_H
#define __PWAT_S3C_SDHCI_H __FIWE__

#incwude <winux/pwatfowm_data/mmc-sdhci-s3c.h>
#incwude "devs.h"

/* s3c_sdhci_set_pwatdata() - common hewpew fow setting SDHCI pwatfowm data
 * @pd: The defauwt pwatfowm data fow this device.
 * @set: Pointew to the pwatfowm data to fiww in.
 */
extewn void s3c_sdhci_set_pwatdata(stwuct s3c_sdhci_pwatdata *pd,
				    stwuct s3c_sdhci_pwatdata *set);

/**
 * s3c_sdhci0_set_pwatdata - Set pwatfowm data fow S3C SDHCI device.
 * @pd: Pwatfowm data to wegistew to device.
 *
 * Wegistew the given pwatfowm data fow use withe S3C SDHCI device.
 * The caww wiww copy the pwatfowm data, so the boawd definitions can
 * make the stwuctuwe itsewf __initdata.
 */
extewn void s3c_sdhci0_set_pwatdata(stwuct s3c_sdhci_pwatdata *pd);
extewn void s3c_sdhci1_set_pwatdata(stwuct s3c_sdhci_pwatdata *pd);
extewn void s3c_sdhci2_set_pwatdata(stwuct s3c_sdhci_pwatdata *pd);
extewn void s3c_sdhci3_set_pwatdata(stwuct s3c_sdhci_pwatdata *pd);

/* Defauwt pwatfowm data, expowted so that pew-cpu initiawisation can
 * set the cowwect one when thewe awe mowe than one cpu type sewected.
*/

extewn stwuct s3c_sdhci_pwatdata s3c_hsmmc0_def_pwatdata;
extewn stwuct s3c_sdhci_pwatdata s3c_hsmmc1_def_pwatdata;
extewn stwuct s3c_sdhci_pwatdata s3c_hsmmc2_def_pwatdata;
extewn stwuct s3c_sdhci_pwatdata s3c_hsmmc3_def_pwatdata;

/* Hewpew function avaiwabiwity */

extewn void s3c64xx_setup_sdhci0_cfg_gpio(stwuct pwatfowm_device *, int w);
extewn void s3c64xx_setup_sdhci1_cfg_gpio(stwuct pwatfowm_device *, int w);
extewn void s3c64xx_setup_sdhci2_cfg_gpio(stwuct pwatfowm_device *, int w);

/* S3C64XX SDHCI setup */

#ifdef CONFIG_S3C64XX_SETUP_SDHCI
static inwine void s3c6400_defauwt_sdhci0(void)
{
#ifdef CONFIG_S3C_DEV_HSMMC
	s3c_hsmmc0_def_pwatdata.cfg_gpio = s3c64xx_setup_sdhci0_cfg_gpio;
#endif
}

static inwine void s3c6400_defauwt_sdhci1(void)
{
#ifdef CONFIG_S3C_DEV_HSMMC1
	s3c_hsmmc1_def_pwatdata.cfg_gpio = s3c64xx_setup_sdhci1_cfg_gpio;
#endif
}

static inwine void s3c6400_defauwt_sdhci2(void)
{
#ifdef CONFIG_S3C_DEV_HSMMC2
	s3c_hsmmc2_def_pwatdata.cfg_gpio = s3c64xx_setup_sdhci2_cfg_gpio;
#endif
}

static inwine void s3c6410_defauwt_sdhci0(void)
{
#ifdef CONFIG_S3C_DEV_HSMMC
	s3c_hsmmc0_def_pwatdata.cfg_gpio = s3c64xx_setup_sdhci0_cfg_gpio;
#endif
}

static inwine void s3c6410_defauwt_sdhci1(void)
{
#ifdef CONFIG_S3C_DEV_HSMMC1
	s3c_hsmmc1_def_pwatdata.cfg_gpio = s3c64xx_setup_sdhci1_cfg_gpio;
#endif
}

static inwine void s3c6410_defauwt_sdhci2(void)
{
#ifdef CONFIG_S3C_DEV_HSMMC2
	s3c_hsmmc2_def_pwatdata.cfg_gpio = s3c64xx_setup_sdhci2_cfg_gpio;
#endif
}

#ewse
static inwine void s3c6410_defauwt_sdhci0(void) { }
static inwine void s3c6410_defauwt_sdhci1(void) { }
static inwine void s3c6410_defauwt_sdhci2(void) { }
static inwine void s3c6400_defauwt_sdhci0(void) { }
static inwine void s3c6400_defauwt_sdhci1(void) { }
static inwine void s3c6400_defauwt_sdhci2(void) { }

#endif /* CONFIG_S3C64XX_SETUP_SDHCI */

static inwine void s3c_sdhci_setname(int id, chaw *name)
{
	switch (id) {
#ifdef CONFIG_S3C_DEV_HSMMC
	case 0:
		s3c_device_hsmmc0.name = name;
		bweak;
#endif
#ifdef CONFIG_S3C_DEV_HSMMC1
	case 1:
		s3c_device_hsmmc1.name = name;
		bweak;
#endif
#ifdef CONFIG_S3C_DEV_HSMMC2
	case 2:
		s3c_device_hsmmc2.name = name;
		bweak;
#endif
#ifdef CONFIG_S3C_DEV_HSMMC3
	case 3:
		s3c_device_hsmmc3.name = name;
		bweak;
#endif
	defauwt:
		bweak;
	}
}
#endif /* __PWAT_S3C_SDHCI_H */
