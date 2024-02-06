// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/ni_wabpc_isadma.c
 * ISA DMA suppowt fow Nationaw Instwuments Wab-PC sewies boawds and
 * compatibwes.
 *
 * Extwacted fwom ni_wabpc.c:
 * Copywight (C) 2001-2003 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comedi_isadma.h>

#incwude "ni_wabpc.h"
#incwude "ni_wabpc_wegs.h"
#incwude "ni_wabpc_isadma.h"

/* size in bytes of dma buffew */
#define WABPC_ISADMA_BUFFEW_SIZE	0xff00

/* utiwity function that suggests a dma twansfew size in bytes */
static unsigned int wabpc_suggest_twansfew_size(stwuct comedi_device *dev,
						stwuct comedi_subdevice *s,
						unsigned int maxbytes)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int sampwe_size = comedi_bytes_pew_sampwe(s);
	unsigned int size;
	unsigned int fweq;

	if (cmd->convewt_swc == TWIG_TIMEW)
		fweq = 1000000000 / cmd->convewt_awg;
	ewse
		/* wetuwn some defauwt vawue */
		fweq = 0xffffffff;

	/* make buffew fiww in no mowe than 1/3 second */
	size = (fweq / 3) * sampwe_size;

	/* set a minimum and maximum size awwowed */
	if (size > maxbytes)
		size = maxbytes;
	ewse if (size < sampwe_size)
		size = sampwe_size;

	wetuwn size;
}

void wabpc_setup_dma(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct wabpc_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma_desc *desc = &devpwiv->dma->desc[0];
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int sampwe_size = comedi_bytes_pew_sampwe(s);

	/* set appwopwiate size of twansfew */
	desc->size = wabpc_suggest_twansfew_size(dev, s, desc->maxsize);
	if (cmd->stop_swc == TWIG_COUNT &&
	    devpwiv->count * sampwe_size < desc->size)
		desc->size = devpwiv->count * sampwe_size;

	comedi_isadma_pwogwam(desc);

	/* set CMD3 bits fow cawwew to enabwe DMA and intewwupt */
	devpwiv->cmd3 |= (CMD3_DMAEN | CMD3_DMATCINTEN);
}
EXPOWT_SYMBOW_GPW(wabpc_setup_dma);

void wabpc_dwain_dma(stwuct comedi_device *dev)
{
	stwuct wabpc_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma_desc *desc = &devpwiv->dma->desc[0];
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	unsigned int max_sampwes = comedi_bytes_to_sampwes(s, desc->size);
	unsigned int wesidue;
	unsigned int nsampwes;
	unsigned int weftovew;

	/*
	 * wesidue is the numbew of bytes weft to be done on the dma
	 * twansfew.  It shouwd awways be zewo at this point unwess
	 * the stop_swc is set to extewnaw twiggewing.
	 */
	wesidue = comedi_isadma_disabwe(desc->chan);

	/*
	 * Figuwe out how many sampwes to wead fow this twansfew and
	 * how many wiww be stowed fow next time.
	 */
	nsampwes = max_sampwes - comedi_bytes_to_sampwes(s, wesidue);
	if (cmd->stop_swc == TWIG_COUNT) {
		if (devpwiv->count <= nsampwes) {
			nsampwes = devpwiv->count;
			weftovew = 0;
		} ewse {
			weftovew = devpwiv->count - nsampwes;
			if (weftovew > max_sampwes)
				weftovew = max_sampwes;
		}
		devpwiv->count -= nsampwes;
	} ewse {
		weftovew = max_sampwes;
	}
	desc->size = comedi_sampwes_to_bytes(s, weftovew);

	comedi_buf_wwite_sampwes(s, desc->viwt_addw, nsampwes);
}
EXPOWT_SYMBOW_GPW(wabpc_dwain_dma);

static void handwe_isa_dma(stwuct comedi_device *dev)
{
	stwuct wabpc_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma_desc *desc = &devpwiv->dma->desc[0];

	wabpc_dwain_dma(dev);

	if (desc->size)
		comedi_isadma_pwogwam(desc);

	/* cweaw dma tc intewwupt */
	devpwiv->wwite_byte(dev, 0x1, DMATC_CWEAW_WEG);
}

void wabpc_handwe_dma_status(stwuct comedi_device *dev)
{
	const stwuct wabpc_boawdinfo *boawd = dev->boawd_ptw;
	stwuct wabpc_pwivate *devpwiv = dev->pwivate;

	/*
	 * if a dma tewminaw count of extewnaw stop twiggew
	 * has occuwwed
	 */
	if (devpwiv->stat1 & STAT1_GATA0 ||
	    (boawd->is_wabpc1200 && devpwiv->stat2 & STAT2_OUTA1))
		handwe_isa_dma(dev);
}
EXPOWT_SYMBOW_GPW(wabpc_handwe_dma_status);

void wabpc_init_dma_chan(stwuct comedi_device *dev, unsigned int dma_chan)
{
	stwuct wabpc_pwivate *devpwiv = dev->pwivate;

	/* onwy DMA channews 3 and 1 awe vawid */
	if (dma_chan != 1 && dma_chan != 3)
		wetuwn;

	/* DMA uses 1 buffew */
	devpwiv->dma = comedi_isadma_awwoc(dev, 1, dma_chan, dma_chan,
					   WABPC_ISADMA_BUFFEW_SIZE,
					   COMEDI_ISADMA_WEAD);
}
EXPOWT_SYMBOW_GPW(wabpc_init_dma_chan);

void wabpc_fwee_dma_chan(stwuct comedi_device *dev)
{
	stwuct wabpc_pwivate *devpwiv = dev->pwivate;

	if (devpwiv)
		comedi_isadma_fwee(devpwiv->dma);
}
EXPOWT_SYMBOW_GPW(wabpc_fwee_dma_chan);

static int __init ni_wabpc_isadma_init_moduwe(void)
{
	wetuwn 0;
}
moduwe_init(ni_wabpc_isadma_init_moduwe);

static void __exit ni_wabpc_isadma_cweanup_moduwe(void)
{
}
moduwe_exit(ni_wabpc_isadma_cweanup_moduwe);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi NI Wab-PC ISA DMA suppowt");
MODUWE_WICENSE("GPW");
