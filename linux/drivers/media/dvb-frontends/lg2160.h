/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *    Suppowt fow WG2160 - ATSC/MH
 *
 *    Copywight (C) 2010 Michaew Kwufky <mkwufky@winuxtv.owg>
 */

#ifndef _WG2160_H_
#define _WG2160_H_

#incwude <winux/i2c.h>
#incwude <media/dvb_fwontend.h>

enum wg_chip_type {
	WG2160 = 0,
	WG2161 = 1,
};

#define WG2161_1019 WG2161
#define WG2161_1040 WG2161

enum wg2160_spi_cwock {
	WG2160_SPI_3_125_MHZ = 0,
	WG2160_SPI_6_25_MHZ = 1,
	WG2160_SPI_12_5_MHZ = 2,
};

#if 0
enum wg2161_oif {
	WG2161_OIF_EBI2_SWA  = 1,
	WG2161_OIF_SDIO_SWA  = 2,
	WG2161_OIF_SPI_SWA   = 3,
	WG2161_OIF_SPI_MAS   = 4,
	WG2161_OIF_SEWIAW_TS = 7,
};
#endif

stwuct wg2160_config {
	u8 i2c_addw;

	/* usew defined IF fwequency in KHz */
	u16 if_khz;

	/* disabwe i2c wepeatew - 0:wepeatew enabwed 1:wepeatew disabwed */
	unsigned int deny_i2c_wptw:1;

	/* spectwaw invewsion - 0:disabwed 1:enabwed */
	unsigned int spectwaw_invewsion:1;

	unsigned int output_if;
	enum wg2160_spi_cwock spi_cwock;
	enum wg_chip_type wg_chip;
};

#if IS_WEACHABWE(CONFIG_DVB_WG2160)
extewn
stwuct dvb_fwontend *wg2160_attach(const stwuct wg2160_config *config,
				     stwuct i2c_adaptew *i2c_adap);
#ewse
static inwine
stwuct dvb_fwontend *wg2160_attach(const stwuct wg2160_config *config,
				     stwuct i2c_adaptew *i2c_adap)
{
	pwintk(KEWN_WAWNING "%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_DVB_WG2160 */

#endif /* _WG2160_H_ */
