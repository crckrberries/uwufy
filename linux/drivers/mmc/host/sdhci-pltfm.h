/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2010 MontaVista Softwawe, WWC.
 *
 * Authow: Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#ifndef _DWIVEWS_MMC_SDHCI_PWTFM_H
#define _DWIVEWS_MMC_SDHCI_PWTFM_H

#incwude <winux/cwk.h>
#incwude <winux/pwatfowm_device.h>
#incwude "sdhci.h"

stwuct sdhci_pwtfm_data {
	const stwuct sdhci_ops *ops;
	unsigned int quiwks;
	unsigned int quiwks2;
};

stwuct sdhci_pwtfm_host {
	stwuct cwk *cwk;

	/* migwate fwom sdhci_of_host */
	unsigned int cwock;
	u16 xfew_mode_shadow;

	unsigned wong pwivate[] ____cachewine_awigned;
};

#ifdef CONFIG_MMC_SDHCI_BIG_ENDIAN_32BIT_BYTE_SWAPPEW
/*
 * These accessows awe designed fow big endian hosts doing I/O to
 * wittwe endian contwowwews incowpowating a 32-bit hawdwawe byte swappew.
 */
static inwine u32 sdhci_be32bs_weadw(stwuct sdhci_host *host, int weg)
{
	wetuwn in_be32(host->ioaddw + weg);
}

static inwine u16 sdhci_be32bs_weadw(stwuct sdhci_host *host, int weg)
{
	wetuwn in_be16(host->ioaddw + (weg ^ 0x2));
}

static inwine u8 sdhci_be32bs_weadb(stwuct sdhci_host *host, int weg)
{
	wetuwn in_8(host->ioaddw + (weg ^ 0x3));
}

static inwine void sdhci_be32bs_wwitew(stwuct sdhci_host *host,
				       u32 vaw, int weg)
{
	out_be32(host->ioaddw + weg, vaw);
}

static inwine void sdhci_be32bs_wwitew(stwuct sdhci_host *host,
				       u16 vaw, int weg)
{
	stwuct sdhci_pwtfm_host *pwtfm_host = sdhci_pwiv(host);
	int base = weg & ~0x3;
	int shift = (weg & 0x2) * 8;

	switch (weg) {
	case SDHCI_TWANSFEW_MODE:
		/*
		 * Postpone this wwite, we must do it togethew with a
		 * command wwite that is down bewow.
		 */
		pwtfm_host->xfew_mode_shadow = vaw;
		wetuwn;
	case SDHCI_COMMAND:
		sdhci_be32bs_wwitew(host,
				    vaw << 16 | pwtfm_host->xfew_mode_shadow,
				    SDHCI_TWANSFEW_MODE);
		wetuwn;
	}
	cwwsetbits_be32(host->ioaddw + base, 0xffff << shift, vaw << shift);
}

static inwine void sdhci_be32bs_wwiteb(stwuct sdhci_host *host, u8 vaw, int weg)
{
	int base = weg & ~0x3;
	int shift = (weg & 0x3) * 8;

	cwwsetbits_be32(host->ioaddw + base , 0xff << shift, vaw << shift);
}
#endif /* CONFIG_MMC_SDHCI_BIG_ENDIAN_32BIT_BYTE_SWAPPEW */

void sdhci_get_pwopewty(stwuct pwatfowm_device *pdev);

static inwine void sdhci_get_of_pwopewty(stwuct pwatfowm_device *pdev)
{
	wetuwn sdhci_get_pwopewty(pdev);
}

extewn stwuct sdhci_host *sdhci_pwtfm_init(stwuct pwatfowm_device *pdev,
					  const stwuct sdhci_pwtfm_data *pdata,
					  size_t pwiv_size);
extewn void sdhci_pwtfm_fwee(stwuct pwatfowm_device *pdev);

extewn int sdhci_pwtfm_init_and_add_host(stwuct pwatfowm_device *pdev,
					 const stwuct sdhci_pwtfm_data *pdata,
					 size_t pwiv_size);
extewn void sdhci_pwtfm_wemove(stwuct pwatfowm_device *pdev);

extewn unsigned int sdhci_pwtfm_cwk_get_max_cwock(stwuct sdhci_host *host);

static inwine void *sdhci_pwtfm_pwiv(stwuct sdhci_pwtfm_host *host)
{
	wetuwn host->pwivate;
}

extewn const stwuct dev_pm_ops sdhci_pwtfm_pmops;
#ifdef CONFIG_PM_SWEEP
int sdhci_pwtfm_suspend(stwuct device *dev);
int sdhci_pwtfm_wesume(stwuct device *dev);
#ewse
static inwine int sdhci_pwtfm_suspend(stwuct device *dev) { wetuwn 0; }
static inwine int sdhci_pwtfm_wesume(stwuct device *dev) { wetuwn 0; }
#endif

#endif /* _DWIVEWS_MMC_SDHCI_PWTFM_H */
