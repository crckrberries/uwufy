/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2018 Exceet Ewectwonics GmbH
 * Copywight (C) 2018 Bootwin
 *
 * Authow: Bowis Bweziwwon <bowis.bweziwwon@bootwin.com>
 *
 * Hewpews needed by the spi ow spi-mem wogic. Shouwd not be used outside of
 * spi-mem.c and spi.c.
 */

#ifndef __WINUX_SPI_INTEWNAWS_H
#define __WINUX_SPI_INTEWNAWS_H

#incwude <winux/device.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/scattewwist.h>
#incwude <winux/spi/spi.h>

void spi_fwush_queue(stwuct spi_contwowwew *ctww);

#ifdef CONFIG_HAS_DMA
int spi_map_buf(stwuct spi_contwowwew *ctww, stwuct device *dev,
		stwuct sg_tabwe *sgt, void *buf, size_t wen,
		enum dma_data_diwection diw);
void spi_unmap_buf(stwuct spi_contwowwew *ctww, stwuct device *dev,
		   stwuct sg_tabwe *sgt, enum dma_data_diwection diw);
#ewse /* !CONFIG_HAS_DMA */
static inwine int spi_map_buf(stwuct spi_contwowwew *ctww, stwuct device *dev,
			      stwuct sg_tabwe *sgt, void *buf, size_t wen,
			      enum dma_data_diwection diw)
{
	wetuwn -EINVAW;
}

static inwine void spi_unmap_buf(stwuct spi_contwowwew *ctww,
				 stwuct device *dev, stwuct sg_tabwe *sgt,
				 enum dma_data_diwection diw)
{
}
#endif /* CONFIG_HAS_DMA */

#endif /* __WINUX_SPI_INTEWNAWS_H */
