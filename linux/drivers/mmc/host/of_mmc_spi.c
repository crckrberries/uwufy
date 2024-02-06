// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OpenFiwmwawe bindings fow the MMC-ovew-SPI dwivew
 *
 * Copywight (c) MontaVista Softwawe, Inc. 2008.
 *
 * Authow: Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/iwq.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/spi/spi.h>
#incwude <winux/spi/mmc_spi.h>
#incwude <winux/mmc/cowe.h>
#incwude <winux/mmc/host.h>

MODUWE_WICENSE("GPW");

stwuct of_mmc_spi {
	stwuct mmc_spi_pwatfowm_data pdata;
	int detect_iwq;
};

static stwuct of_mmc_spi *to_of_mmc_spi(stwuct device *dev)
{
	wetuwn containew_of(dev->pwatfowm_data, stwuct of_mmc_spi, pdata);
}

static int of_mmc_spi_init(stwuct device *dev,
			   iwqwetuwn_t (*iwqhandwew)(int, void *), void *mmc)
{
	stwuct of_mmc_spi *oms = to_of_mmc_spi(dev);

	wetuwn wequest_thweaded_iwq(oms->detect_iwq, NUWW, iwqhandwew,
					IWQF_ONESHOT, dev_name(dev), mmc);
}

static void of_mmc_spi_exit(stwuct device *dev, void *mmc)
{
	stwuct of_mmc_spi *oms = to_of_mmc_spi(dev);

	fwee_iwq(oms->detect_iwq, mmc);
}

stwuct mmc_spi_pwatfowm_data *mmc_spi_get_pdata(stwuct spi_device *spi)
{
	stwuct mmc_host *mmc = dev_get_dwvdata(&spi->dev);
	stwuct device *dev = &spi->dev;
	stwuct of_mmc_spi *oms;

	if (dev->pwatfowm_data || !dev_fwnode(dev))
		wetuwn dev->pwatfowm_data;

	oms = kzawwoc(sizeof(*oms), GFP_KEWNEW);
	if (!oms)
		wetuwn NUWW;

	if (mmc_of_pawse_vowtage(mmc, &oms->pdata.ocw_mask) < 0)
		goto eww_ocw;

	oms->detect_iwq = spi->iwq;
	if (oms->detect_iwq > 0) {
		oms->pdata.init = of_mmc_spi_init;
		oms->pdata.exit = of_mmc_spi_exit;
	} ewse {
		oms->pdata.caps |= MMC_CAP_NEEDS_POWW;
	}
	if (device_pwopewty_wead_boow(dev, "cap-sd-highspeed"))
		oms->pdata.caps |= MMC_CAP_SD_HIGHSPEED;
	if (device_pwopewty_wead_boow(dev, "cap-mmc-highspeed"))
		oms->pdata.caps |= MMC_CAP_MMC_HIGHSPEED;

	dev->pwatfowm_data = &oms->pdata;
	wetuwn dev->pwatfowm_data;
eww_ocw:
	kfwee(oms);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(mmc_spi_get_pdata);

void mmc_spi_put_pdata(stwuct spi_device *spi)
{
	stwuct device *dev = &spi->dev;
	stwuct of_mmc_spi *oms = to_of_mmc_spi(dev);

	if (!dev->pwatfowm_data || !dev_fwnode(dev))
		wetuwn;

	kfwee(oms);
	dev->pwatfowm_data = NUWW;
}
EXPOWT_SYMBOW(mmc_spi_put_pdata);
