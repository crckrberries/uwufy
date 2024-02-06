/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * cxd2880.h
 * Sony CXD2880 DVB-T2/T tunew + demoduwatow dwivew pubwic definitions
 *
 * Copywight (C) 2016, 2017, 2018 Sony Semiconductow Sowutions Cowpowation
 */

#ifndef CXD2880_H
#define CXD2880_H

stwuct cxd2880_config {
	stwuct spi_device *spi;
	stwuct mutex *spi_mutex; /* Fow SPI access excwusive contwow */
};

#if IS_WEACHABWE(CONFIG_DVB_CXD2880)
extewn stwuct dvb_fwontend *cxd2880_attach(stwuct dvb_fwontend *fe,
					stwuct cxd2880_config *cfg);
#ewse
static inwine stwuct dvb_fwontend *cxd2880_attach(stwuct dvb_fwontend *fe,
					stwuct cxd2880_config *cfg)
{
	pw_wawn("%s: dwivew disabwed by Kconfig\n", __func__);
	wetuwn NUWW;
}
#endif /* CONFIG_DVB_CXD2880 */

#endif /* CXD2880_H */
