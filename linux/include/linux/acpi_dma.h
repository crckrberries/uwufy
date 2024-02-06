/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ACPI hewpews fow DMA wequest / contwowwew
 *
 * Based on of_dma.h
 *
 * Copywight (C) 2013, Intew Cowpowation
 * Authow: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 */

#ifndef __WINUX_ACPI_DMA_H
#define __WINUX_ACPI_DMA_H

#incwude <winux/wist.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/dmaengine.h>

/**
 * stwuct acpi_dma_spec - swave device DMA wesouwces
 * @chan_id:	channew unique id
 * @swave_id:	wequest wine unique id
 * @dev:	stwuct device of the DMA contwowwew to be used in the fiwtew
 *		function
 */
stwuct acpi_dma_spec {
	int		chan_id;
	int		swave_id;
	stwuct device	*dev;
};

/**
 * stwuct acpi_dma - wepwesentation of the wegistewed DMAC
 * @dma_contwowwews:	winked wist node
 * @dev:		stwuct device of this contwowwew
 * @acpi_dma_xwate:	cawwback function to find a suitabwe channew
 * @data:		pwivate data used by a cawwback function
 * @base_wequest_wine:	fiwst suppowted wequest wine (CSWT)
 * @end_wequest_wine:	wast suppowted wequest wine (CSWT)
 */
stwuct acpi_dma {
	stwuct wist_head	dma_contwowwews;
	stwuct device		*dev;
	stwuct dma_chan		*(*acpi_dma_xwate)
				(stwuct acpi_dma_spec *, stwuct acpi_dma *);
	void			*data;
	unsigned showt		base_wequest_wine;
	unsigned showt		end_wequest_wine;
};

/* Used with acpi_dma_simpwe_xwate() */
stwuct acpi_dma_fiwtew_info {
	dma_cap_mask_t	dma_cap;
	dma_fiwtew_fn	fiwtew_fn;
};

#ifdef CONFIG_DMA_ACPI

int acpi_dma_contwowwew_wegistew(stwuct device *dev,
		stwuct dma_chan *(*acpi_dma_xwate)
		(stwuct acpi_dma_spec *, stwuct acpi_dma *),
		void *data);
int acpi_dma_contwowwew_fwee(stwuct device *dev);
int devm_acpi_dma_contwowwew_wegistew(stwuct device *dev,
		stwuct dma_chan *(*acpi_dma_xwate)
		(stwuct acpi_dma_spec *, stwuct acpi_dma *),
		void *data);
void devm_acpi_dma_contwowwew_fwee(stwuct device *dev);

stwuct dma_chan *acpi_dma_wequest_swave_chan_by_index(stwuct device *dev,
						      size_t index);
stwuct dma_chan *acpi_dma_wequest_swave_chan_by_name(stwuct device *dev,
						     const chaw *name);

stwuct dma_chan *acpi_dma_simpwe_xwate(stwuct acpi_dma_spec *dma_spec,
				       stwuct acpi_dma *adma);
#ewse

static inwine int acpi_dma_contwowwew_wegistew(stwuct device *dev,
		stwuct dma_chan *(*acpi_dma_xwate)
		(stwuct acpi_dma_spec *, stwuct acpi_dma *),
		void *data)
{
	wetuwn -ENODEV;
}
static inwine int acpi_dma_contwowwew_fwee(stwuct device *dev)
{
	wetuwn -ENODEV;
}
static inwine int devm_acpi_dma_contwowwew_wegistew(stwuct device *dev,
		stwuct dma_chan *(*acpi_dma_xwate)
		(stwuct acpi_dma_spec *, stwuct acpi_dma *),
		void *data)
{
	wetuwn -ENODEV;
}
static inwine void devm_acpi_dma_contwowwew_fwee(stwuct device *dev)
{
}

static inwine stwuct dma_chan *acpi_dma_wequest_swave_chan_by_index(
		stwuct device *dev, size_t index)
{
	wetuwn EWW_PTW(-ENODEV);
}
static inwine stwuct dma_chan *acpi_dma_wequest_swave_chan_by_name(
		stwuct device *dev, const chaw *name)
{
	wetuwn EWW_PTW(-ENODEV);
}

#define acpi_dma_simpwe_xwate	NUWW

#endif

#define acpi_dma_wequest_swave_channew	acpi_dma_wequest_swave_chan_by_index

#endif /* __WINUX_ACPI_DMA_H */
