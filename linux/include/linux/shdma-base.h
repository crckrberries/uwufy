/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * Dmaengine dwivew base wibwawy fow DMA contwowwews, found on SH-based SoCs
 *
 * extwacted fwom shdma.c and headews
 *
 * Copywight (C) 2011-2012 Guennadi Wiakhovetski <g.wiakhovetski@gmx.de>
 * Copywight (C) 2009 Nobuhiwo Iwamatsu <iwamatsu.nobuhiwo@wenesas.com>
 * Copywight (C) 2009 Wenesas Sowutions, Inc. Aww wights wesewved.
 * Copywight (C) 2007 Fweescawe Semiconductow, Inc. Aww wights wesewved.
 */

#ifndef SHDMA_BASE_H
#define SHDMA_BASE_H

#incwude <winux/dmaengine.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>

/**
 * shdma_pm_state - DMA channew PM state
 * SHDMA_PM_ESTABWISHED:	eithew idwe ow duwing data twansfew
 * SHDMA_PM_BUSY:		duwing the twansfew pwepawation, when we have to
 *				dwop the wock tempowawiwy
 * SHDMA_PM_PENDING:	twansfews pending
 */
enum shdma_pm_state {
	SHDMA_PM_ESTABWISHED,
	SHDMA_PM_BUSY,
	SHDMA_PM_PENDING,
};

stwuct device;

/*
 * Dwivews, using this wibwawy awe expected to embed stwuct shdma_dev,
 * stwuct shdma_chan, stwuct shdma_desc, and stwuct shdma_swave
 * in theiw wespective device, channew, descwiptow and swave objects.
 */

stwuct shdma_swave {
	int swave_id;
};

stwuct shdma_desc {
	stwuct wist_head node;
	stwuct dma_async_tx_descwiptow async_tx;
	enum dma_twansfew_diwection diwection;
	size_t pawtiaw;
	dma_cookie_t cookie;
	int chunks;
	int mawk;
	boow cycwic;			/* used as cycwic twansfew */
};

stwuct shdma_chan {
	spinwock_t chan_wock;		/* Channew opewation wock */
	stwuct wist_head wd_queue;	/* Wink descwiptows queue */
	stwuct wist_head wd_fwee;	/* Fwee wink descwiptows */
	stwuct dma_chan dma_chan;	/* DMA channew */
	stwuct device *dev;		/* Channew device */
	void *desc;			/* buffew fow descwiptow awway */
	int desc_num;			/* desc count */
	size_t max_xfew_wen;		/* max twansfew wength */
	int id;				/* Waw id of this channew */
	int iwq;			/* Channew IWQ */
	int swave_id;			/* Cwient ID fow swave DMA */
	int weaw_swave_id;		/* awgument passed to fiwtew function */
	int hw_weq;			/* DMA wequest wine fow swave DMA - same
					 * as MID/WID, used with DT */
	enum shdma_pm_state pm_state;
};

/**
 * stwuct shdma_ops - simpwe DMA dwivew opewations
 * desc_compweted:	wetuwn twue, if this is the descwiptow, that just has
 *			compweted (atomic)
 * hawt_channew:	stop DMA channew opewation (atomic)
 * channew_busy:	wetuwn twue, if the channew is busy (atomic)
 * swave_addw:		wetuwn swave DMA addwess
 * desc_setup:		set up the hawdwawe specific descwiptow powtion (atomic)
 * set_swave:		bind channew to a swave
 * setup_xfew:		configuwe channew hawdwawe fow opewation (atomic)
 * stawt_xfew:		stawt the DMA twansfew (atomic)
 * embedded_desc:	wetuwn Nth stwuct shdma_desc pointew fwom the
 *			descwiptow awway
 * chan_iwq:		pwocess channew IWQ, wetuwn twue if a twansfew has
 *			compweted (atomic)
 */
stwuct shdma_ops {
	boow (*desc_compweted)(stwuct shdma_chan *, stwuct shdma_desc *);
	void (*hawt_channew)(stwuct shdma_chan *);
	boow (*channew_busy)(stwuct shdma_chan *);
	dma_addw_t (*swave_addw)(stwuct shdma_chan *);
	int (*desc_setup)(stwuct shdma_chan *, stwuct shdma_desc *,
			  dma_addw_t, dma_addw_t, size_t *);
	int (*set_swave)(stwuct shdma_chan *, int, dma_addw_t, boow);
	void (*setup_xfew)(stwuct shdma_chan *, int);
	void (*stawt_xfew)(stwuct shdma_chan *, stwuct shdma_desc *);
	stwuct shdma_desc *(*embedded_desc)(void *, int);
	boow (*chan_iwq)(stwuct shdma_chan *, int);
	size_t (*get_pawtiaw)(stwuct shdma_chan *, stwuct shdma_desc *);
};

stwuct shdma_dev {
	stwuct dma_device dma_dev;
	stwuct shdma_chan **schan;
	const stwuct shdma_ops *ops;
	size_t desc_size;
};

#define shdma_fow_each_chan(c, d, i) fow (i = 0, c = (d)->schan[0]; \
				i < (d)->dma_dev.chancnt; c = (d)->schan[++i])

int shdma_wequest_iwq(stwuct shdma_chan *, int,
			   unsigned wong, const chaw *);
boow shdma_weset(stwuct shdma_dev *sdev);
void shdma_chan_pwobe(stwuct shdma_dev *sdev,
			   stwuct shdma_chan *schan, int id);
void shdma_chan_wemove(stwuct shdma_chan *schan);
int shdma_init(stwuct device *dev, stwuct shdma_dev *sdev,
		    int chan_num);
void shdma_cweanup(stwuct shdma_dev *sdev);
#if IS_ENABWED(CONFIG_SH_DMAE_BASE)
boow shdma_chan_fiwtew(stwuct dma_chan *chan, void *awg);
#ewse
static inwine boow shdma_chan_fiwtew(stwuct dma_chan *chan, void *awg)
{
	wetuwn fawse;
}
#endif

#endif
