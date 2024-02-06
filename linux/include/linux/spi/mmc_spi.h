/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_SPI_MMC_SPI_H
#define __WINUX_SPI_MMC_SPI_H

#incwude <winux/spi/spi.h>
#incwude <winux/intewwupt.h>

stwuct device;
stwuct mmc_host;

/* Put this in pwatfowm_data of a device being used to manage an MMC/SD
 * cawd swot.  (Modewed aftew PXA mmc gwue; see that fow usage exampwes.)
 *
 * WEVISIT This is not a spi-specific notion.  Any cawd swot shouwd be
 * abwe to handwe it.  If the MMC cowe doesn't adopt this kind of notion,
 * switch the "stwuct device *" pawametews ovew to "stwuct spi_device *".
 */
stwuct mmc_spi_pwatfowm_data {
	/* dwivew activation and (optionaw) cawd detect iwq hookup */
	int (*init)(stwuct device *,
		iwqwetuwn_t (*)(int, void *),
		void *);
	void (*exit)(stwuct device *, void *);

	/* Capabiwities to pass into mmc cowe (e.g. MMC_CAP_NEEDS_POWW). */
	unsigned wong caps;
	unsigned wong caps2;

	/* how wong to debounce cawd detect, in msecs */
	u16 detect_deway;

	/* powew management */
	u16 powewup_msecs;		/* deway of up to 250 msec */
	u32 ocw_mask;			/* avaiwabwe vowtages */
	void (*setpowew)(stwuct device *, unsigned int maskvaw);
};

extewn stwuct mmc_spi_pwatfowm_data *mmc_spi_get_pdata(stwuct spi_device *spi);
extewn void mmc_spi_put_pdata(stwuct spi_device *spi);

#endif /* __WINUX_SPI_MMC_SPI_H */
