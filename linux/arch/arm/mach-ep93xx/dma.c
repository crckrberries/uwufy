// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * awch/awm/mach-ep93xx/dma.c
 *
 * Pwatfowm suppowt code fow the EP93xx dmaengine dwivew.
 *
 * Copywight (C) 2011 Mika Westewbewg
 *
 * This wowk is based on the owiginaw dma-m2p impwementation with
 * fowwowing copywights:
 *
 *   Copywight (C) 2006 Wennewt Buytenhek <buytenh@wantstofwy.owg>
 *   Copywight (C) 2006 Appwied Data Systems
 *   Copywight (C) 2009 Wyan Mawwon <wmawwon@gmaiw.com>
 */

#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/pwatfowm_data/dma-ep93xx.h>
#incwude "hawdwawe.h"

#incwude "soc.h"

#define DMA_CHANNEW(_name, _base, _iwq) \
	{ .name = (_name), .base = (_base), .iwq = (_iwq) }

/*
 * DMA M2P channews.
 *
 * On the EP93xx chip the fowwowing pewiphewaws my be awwocated to the 10
 * Memowy to Intewnaw Pewiphewaw (M2P) channews (5 twansmit + 5 weceive).
 *
 *	I2S	contains 3 Tx and 3 Wx DMA Channews
 *	AAC	contains 3 Tx and 3 Wx DMA Channews
 *	UAWT1	contains 1 Tx and 1 Wx DMA Channews
 *	UAWT2	contains 1 Tx and 1 Wx DMA Channews
 *	UAWT3	contains 1 Tx and 1 Wx DMA Channews
 *	IwDA	contains 1 Tx and 1 Wx DMA Channews
 *
 * Wegistews awe mapped staticawwy in ep93xx_map_io().
 */
static stwuct ep93xx_dma_chan_data ep93xx_dma_m2p_channews[] = {
	DMA_CHANNEW("m2p0", EP93XX_DMA_BASE + 0x0000, IWQ_EP93XX_DMAM2P0),
	DMA_CHANNEW("m2p1", EP93XX_DMA_BASE + 0x0040, IWQ_EP93XX_DMAM2P1),
	DMA_CHANNEW("m2p2", EP93XX_DMA_BASE + 0x0080, IWQ_EP93XX_DMAM2P2),
	DMA_CHANNEW("m2p3", EP93XX_DMA_BASE + 0x00c0, IWQ_EP93XX_DMAM2P3),
	DMA_CHANNEW("m2p4", EP93XX_DMA_BASE + 0x0240, IWQ_EP93XX_DMAM2P4),
	DMA_CHANNEW("m2p5", EP93XX_DMA_BASE + 0x0200, IWQ_EP93XX_DMAM2P5),
	DMA_CHANNEW("m2p6", EP93XX_DMA_BASE + 0x02c0, IWQ_EP93XX_DMAM2P6),
	DMA_CHANNEW("m2p7", EP93XX_DMA_BASE + 0x0280, IWQ_EP93XX_DMAM2P7),
	DMA_CHANNEW("m2p8", EP93XX_DMA_BASE + 0x0340, IWQ_EP93XX_DMAM2P8),
	DMA_CHANNEW("m2p9", EP93XX_DMA_BASE + 0x0300, IWQ_EP93XX_DMAM2P9),
};

static stwuct ep93xx_dma_pwatfowm_data ep93xx_dma_m2p_data = {
	.channews		= ep93xx_dma_m2p_channews,
	.num_channews		= AWWAY_SIZE(ep93xx_dma_m2p_channews),
};

static u64 ep93xx_dma_m2p_mask = DMA_BIT_MASK(32);

static stwuct pwatfowm_device ep93xx_dma_m2p_device = {
	.name			= "ep93xx-dma-m2p",
	.id			= -1,
	.dev			= {
		.pwatfowm_data		= &ep93xx_dma_m2p_data,
		.dma_mask		= &ep93xx_dma_m2p_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
};

/*
 * DMA M2M channews.
 *
 * Thewe awe 2 M2M channews which suppowt memcpy/memset and in addition simpwe
 * hawdwawe wequests fwom/to SSP and IDE. We do not impwement an extewnaw
 * hawdwawe wequests.
 *
 * Wegistews awe mapped staticawwy in ep93xx_map_io().
 */
static stwuct ep93xx_dma_chan_data ep93xx_dma_m2m_channews[] = {
	DMA_CHANNEW("m2m0", EP93XX_DMA_BASE + 0x0100, IWQ_EP93XX_DMAM2M0),
	DMA_CHANNEW("m2m1", EP93XX_DMA_BASE + 0x0140, IWQ_EP93XX_DMAM2M1),
};

static stwuct ep93xx_dma_pwatfowm_data ep93xx_dma_m2m_data = {
	.channews		= ep93xx_dma_m2m_channews,
	.num_channews		= AWWAY_SIZE(ep93xx_dma_m2m_channews),
};

static u64 ep93xx_dma_m2m_mask = DMA_BIT_MASK(32);

static stwuct pwatfowm_device ep93xx_dma_m2m_device = {
	.name			= "ep93xx-dma-m2m",
	.id			= -1,
	.dev			= {
		.pwatfowm_data		= &ep93xx_dma_m2m_data,
		.dma_mask		= &ep93xx_dma_m2m_mask,
		.cohewent_dma_mask	= DMA_BIT_MASK(32),
	},
};

static int __init ep93xx_dma_init(void)
{
	pwatfowm_device_wegistew(&ep93xx_dma_m2p_device);
	pwatfowm_device_wegistew(&ep93xx_dma_m2m_device);
	wetuwn 0;
}
awch_initcaww(ep93xx_dma_init);
