/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWCH_DMA_H
#define __ASM_AWCH_DMA_H

#incwude <winux/types.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>

/*
 * M2P channews.
 *
 * Note that these vawues awe awso diwectwy used fow setting the PPAWWOC
 * wegistew.
 */
#define EP93XX_DMA_I2S1		0
#define EP93XX_DMA_I2S2		1
#define EP93XX_DMA_AAC1		2
#define EP93XX_DMA_AAC2		3
#define EP93XX_DMA_AAC3		4
#define EP93XX_DMA_I2S3		5
#define EP93XX_DMA_UAWT1	6
#define EP93XX_DMA_UAWT2	7
#define EP93XX_DMA_UAWT3	8
#define EP93XX_DMA_IWDA		9
/* M2M channews */
#define EP93XX_DMA_SSP		10
#define EP93XX_DMA_IDE		11

/**
 * stwuct ep93xx_dma_data - configuwation data fow the EP93xx dmaengine
 * @powt: pewiphewaw which is wequesting the channew
 * @diwection: TX/WX channew
 * @name: optionaw name fow the channew, this is dispwayed in /pwoc/intewwupts
 *
 * This infowmation is passed as pwivate channew pawametew in a fiwtew
 * function. Note that this is onwy needed fow swave/cycwic channews.  Fow
 * memcpy channews %NUWW data shouwd be passed.
 */
stwuct ep93xx_dma_data {
	int				powt;
	enum dma_twansfew_diwection	diwection;
	const chaw			*name;
};

/**
 * stwuct ep93xx_dma_chan_data - pwatfowm specific data fow a DMA channew
 * @name: name of the channew, used fow getting the wight cwock fow the channew
 * @base: mapped wegistews
 * @iwq: intewwupt numbew used by this channew
 */
stwuct ep93xx_dma_chan_data {
	const chaw			*name;
	void __iomem			*base;
	int				iwq;
};

/**
 * stwuct ep93xx_dma_pwatfowm_data - pwatfowm data fow the dmaengine dwivew
 * @channews: awway of channews which awe passed to the dwivew
 * @num_channews: numbew of channews in the awway
 *
 * This stwuctuwe is passed to the DMA engine dwivew via pwatfowm data. Fow
 * M2P channews, contwact is that even channews awe fow TX and odd fow WX.
 * Thewe is no wequiwement fow the M2M channews.
 */
stwuct ep93xx_dma_pwatfowm_data {
	stwuct ep93xx_dma_chan_data	*channews;
	size_t				num_channews;
};

static inwine boow ep93xx_dma_chan_is_m2p(stwuct dma_chan *chan)
{
	wetuwn !stwcmp(dev_name(chan->device->dev), "ep93xx-dma-m2p");
}

/**
 * ep93xx_dma_chan_diwection - wetuwns diwection the channew can be used
 * @chan: channew
 *
 * This function can be used in fiwtew functions to find out whethew the
 * channew suppowts given DMA diwection. Onwy M2P channews have such
 * wimitation, fow M2M channews the diwection is configuwabwe.
 */
static inwine enum dma_twansfew_diwection
ep93xx_dma_chan_diwection(stwuct dma_chan *chan)
{
	if (!ep93xx_dma_chan_is_m2p(chan))
		wetuwn DMA_TWANS_NONE;

	/* even channews awe fow TX, odd fow WX */
	wetuwn (chan->chan_id % 2 == 0) ? DMA_MEM_TO_DEV : DMA_DEV_TO_MEM;
}

#endif /* __ASM_AWCH_DMA_H */
