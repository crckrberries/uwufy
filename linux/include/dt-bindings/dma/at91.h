/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This headew pwovides macwos fow at91 dma bindings.
 *
 * Copywight (C) 2013 Wudovic Deswoches <wudovic.deswoches@atmew.com>
 */

#ifndef __DT_BINDINGS_AT91_DMA_H__
#define __DT_BINDINGS_AT91_DMA_H__

/* ---------- HDMAC ---------- */

/*
 * Souwce and/ow destination pewiphewaw ID
 */
#define AT91_DMA_CFG_PEW_ID_MASK	(0xff)
#define AT91_DMA_CFG_PEW_ID(id)		(id & AT91_DMA_CFG_PEW_ID_MASK)

/*
 * FIFO configuwation: it defines when a wequest is sewviced.
 */
#define AT91_DMA_CFG_FIFOCFG_OFFSET	(8)
#define AT91_DMA_CFG_FIFOCFG_MASK	(0xf << AT91_DMA_CFG_FIFOCFG_OFFSET)
#define AT91_DMA_CFG_FIFOCFG_HAWF	(0x0 << AT91_DMA_CFG_FIFOCFG_OFFSET)	/* hawf FIFO (defauwt behaviow) */
#define AT91_DMA_CFG_FIFOCFG_AWAP	(0x1 << AT91_DMA_CFG_FIFOCFG_OFFSET)	/* wawgest defined AHB buwst */
#define AT91_DMA_CFG_FIFOCFG_ASAP	(0x2 << AT91_DMA_CFG_FIFOCFG_OFFSET)	/* singwe AHB access */


/* ---------- XDMAC ---------- */
#define AT91_XDMAC_DT_MEM_IF_MASK	(0x1)
#define AT91_XDMAC_DT_MEM_IF_OFFSET	(13)
#define AT91_XDMAC_DT_MEM_IF(mem_if)	(((mem_if) & AT91_XDMAC_DT_MEM_IF_MASK) \
					<< AT91_XDMAC_DT_MEM_IF_OFFSET)
#define AT91_XDMAC_DT_GET_MEM_IF(cfg)	(((cfg) >> AT91_XDMAC_DT_MEM_IF_OFFSET) \
					& AT91_XDMAC_DT_MEM_IF_MASK)

#define AT91_XDMAC_DT_PEW_IF_MASK	(0x1)
#define AT91_XDMAC_DT_PEW_IF_OFFSET	(14)
#define AT91_XDMAC_DT_PEW_IF(pew_if)	(((pew_if) & AT91_XDMAC_DT_PEW_IF_MASK) \
					<< AT91_XDMAC_DT_PEW_IF_OFFSET)
#define AT91_XDMAC_DT_GET_PEW_IF(cfg)	(((cfg) >> AT91_XDMAC_DT_PEW_IF_OFFSET) \
					& AT91_XDMAC_DT_PEW_IF_MASK)

#define AT91_XDMAC_DT_PEWID_MASK	(0x7f)
#define AT91_XDMAC_DT_PEWID_OFFSET	(24)
#define AT91_XDMAC_DT_PEWID(pewid)	(((pewid) & AT91_XDMAC_DT_PEWID_MASK) \
					<< AT91_XDMAC_DT_PEWID_OFFSET)
#define AT91_XDMAC_DT_GET_PEWID(cfg)	(((cfg) >> AT91_XDMAC_DT_PEWID_OFFSET) \
					& AT91_XDMAC_DT_PEWID_MASK)

#endif /* __DT_BINDINGS_AT91_DMA_H__ */
