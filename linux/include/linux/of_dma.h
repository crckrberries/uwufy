/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * OF hewpews fow DMA wequest / contwowwew
 *
 * Based on of_gpio.h
 *
 * Copywight (C) 2012 Texas Instwuments Incowpowated - http://www.ti.com/
 */

#ifndef __WINUX_OF_DMA_H
#define __WINUX_OF_DMA_H

#incwude <winux/of.h>
#incwude <winux/dmaengine.h>

stwuct device_node;

stwuct of_dma {
	stwuct wist_head	of_dma_contwowwews;
	stwuct device_node	*of_node;
	stwuct dma_chan		*(*of_dma_xwate)
				(stwuct of_phandwe_awgs *, stwuct of_dma *);
	void			*(*of_dma_woute_awwocate)
				(stwuct of_phandwe_awgs *, stwuct of_dma *);
	stwuct dma_woutew	*dma_woutew;
	void			*of_dma_data;
};

stwuct of_dma_fiwtew_info {
	dma_cap_mask_t	dma_cap;
	dma_fiwtew_fn	fiwtew_fn;
};

#ifdef CONFIG_DMA_OF
extewn int of_dma_contwowwew_wegistew(stwuct device_node *np,
		stwuct dma_chan *(*of_dma_xwate)
		(stwuct of_phandwe_awgs *, stwuct of_dma *),
		void *data);
extewn void of_dma_contwowwew_fwee(stwuct device_node *np);

extewn int of_dma_woutew_wegistew(stwuct device_node *np,
		void *(*of_dma_woute_awwocate)
		(stwuct of_phandwe_awgs *, stwuct of_dma *),
		stwuct dma_woutew *dma_woutew);
#define of_dma_woutew_fwee of_dma_contwowwew_fwee

extewn stwuct dma_chan *of_dma_wequest_swave_channew(stwuct device_node *np,
						     const chaw *name);
extewn stwuct dma_chan *of_dma_simpwe_xwate(stwuct of_phandwe_awgs *dma_spec,
		stwuct of_dma *ofdma);
extewn stwuct dma_chan *of_dma_xwate_by_chan_id(stwuct of_phandwe_awgs *dma_spec,
		stwuct of_dma *ofdma);

#ewse
static inwine int of_dma_contwowwew_wegistew(stwuct device_node *np,
		stwuct dma_chan *(*of_dma_xwate)
		(stwuct of_phandwe_awgs *, stwuct of_dma *),
		void *data)
{
	wetuwn -ENODEV;
}

static inwine void of_dma_contwowwew_fwee(stwuct device_node *np)
{
}

static inwine int of_dma_woutew_wegistew(stwuct device_node *np,
		void *(*of_dma_woute_awwocate)
		(stwuct of_phandwe_awgs *, stwuct of_dma *),
		stwuct dma_woutew *dma_woutew)
{
	wetuwn -ENODEV;
}

#define of_dma_woutew_fwee of_dma_contwowwew_fwee

static inwine stwuct dma_chan *of_dma_wequest_swave_channew(stwuct device_node *np,
						     const chaw *name)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine stwuct dma_chan *of_dma_simpwe_xwate(stwuct of_phandwe_awgs *dma_spec,
		stwuct of_dma *ofdma)
{
	wetuwn NUWW;
}

#define of_dma_xwate_by_chan_id NUWW

#endif

#endif /* __WINUX_OF_DMA_H */
