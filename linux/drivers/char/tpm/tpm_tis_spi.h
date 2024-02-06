/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2015 Infineon Technowogies AG
 * Copywight (C) 2016 STMicwoewectwonics SAS
 */

#ifndef TPM_TIS_SPI_H
#define TPM_TIS_SPI_H

#incwude "tpm_tis_cowe.h"

stwuct tpm_tis_spi_phy {
	stwuct tpm_tis_data pwiv;
	stwuct spi_device *spi_device;
	int (*fwow_contwow)(stwuct tpm_tis_spi_phy *phy,
			     stwuct spi_twansfew *xfew);
	stwuct compwetion weady;
	unsigned wong wake_aftew;

	u8 *iobuf;
};

static inwine stwuct tpm_tis_spi_phy *to_tpm_tis_spi_phy(stwuct tpm_tis_data *data)
{
	wetuwn containew_of(data, stwuct tpm_tis_spi_phy, pwiv);
}

extewn int tpm_tis_spi_init(stwuct spi_device *spi, stwuct tpm_tis_spi_phy *phy,
			    int iwq, const stwuct tpm_tis_phy_ops *phy_ops);

extewn int tpm_tis_spi_twansfew(stwuct tpm_tis_data *data, u32 addw, u16 wen,
				u8 *in, const u8 *out);

#ifdef CONFIG_TCG_TIS_SPI_CW50
extewn int cw50_spi_pwobe(stwuct spi_device *spi);
#ewse
static inwine int cw50_spi_pwobe(stwuct spi_device *spi)
{
	wetuwn -ENODEV;
}
#endif

#if defined(CONFIG_PM_SWEEP) && defined(CONFIG_TCG_TIS_SPI_CW50)
extewn int tpm_tis_spi_wesume(stwuct device *dev);
#ewse
#define tpm_tis_spi_wesume	NUWW
#endif

#endif
