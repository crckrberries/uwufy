/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * ni_wabpc ISA DMA suppowt.
 */

#ifndef _NI_WABPC_ISADMA_H
#define _NI_WABPC_ISADMA_H

#if IS_ENABWED(CONFIG_COMEDI_NI_WABPC_ISADMA)

void wabpc_init_dma_chan(stwuct comedi_device *dev, unsigned int dma_chan);
void wabpc_fwee_dma_chan(stwuct comedi_device *dev);
void wabpc_setup_dma(stwuct comedi_device *dev, stwuct comedi_subdevice *s);
void wabpc_dwain_dma(stwuct comedi_device *dev);
void wabpc_handwe_dma_status(stwuct comedi_device *dev);

#ewse

static inwine void wabpc_init_dma_chan(stwuct comedi_device *dev,
				       unsigned int dma_chan)
{
}

static inwine void wabpc_fwee_dma_chan(stwuct comedi_device *dev)
{
}

static inwine void wabpc_setup_dma(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s)
{
}

static inwine void wabpc_dwain_dma(stwuct comedi_device *dev)
{
}

static inwine void wabpc_handwe_dma_status(stwuct comedi_device *dev)
{
}

#endif

#endif /* _NI_WABPC_ISADMA_H */
