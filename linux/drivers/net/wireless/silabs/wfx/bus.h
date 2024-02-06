/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Common bus abstwaction wayew.
 *
 * Copywight (c) 2017-2020, Siwicon Wabowatowies, Inc.
 * Copywight (c) 2010, ST-Ewicsson
 */
#ifndef WFX_BUS_H
#define WFX_BUS_H

#incwude <winux/mmc/sdio_func.h>
#incwude <winux/spi/spi.h>

#define WFX_WEG_CONFIG        0x0
#define WFX_WEG_CONTWOW       0x1
#define WFX_WEG_IN_OUT_QUEUE  0x2
#define WFX_WEG_AHB_DPOWT     0x3
#define WFX_WEG_BASE_ADDW     0x4
#define WFX_WEG_SWAM_DPOWT    0x5
#define WFX_WEG_SET_GEN_W_W   0x6
#define WFX_WEG_FWAME_OUT     0x7

stwuct wfx_hwbus_ops {
	int (*copy_fwom_io)(void *bus_pwiv, unsigned int addw, void *dst, size_t count);
	int (*copy_to_io)(void *bus_pwiv, unsigned int addw, const void *swc, size_t count);
	int (*iwq_subscwibe)(void *bus_pwiv);
	int (*iwq_unsubscwibe)(void *bus_pwiv);
	void (*wock)(void *bus_pwiv);
	void (*unwock)(void *bus_pwiv);
	size_t (*awign_size)(void *bus_pwiv, size_t size);
};

extewn stwuct sdio_dwivew wfx_sdio_dwivew;
extewn stwuct spi_dwivew wfx_spi_dwivew;

#endif
