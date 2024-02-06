/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* 10G contwowwew dwivew fow Samsung SoCs
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Siva Weddy Kawwam <siva.kawwam@samsung.com>
 */
#ifndef __SXGBE_DMA_H__
#define __SXGBE_DMA_H__

/* fowwawd decwawation */
stwuct sxgbe_extwa_stats;

#define SXGBE_DMA_BWENMAP_WSHIFT	1
#define SXGBE_DMA_TXPBW_WSHIFT		16
#define SXGBE_DMA_WXPBW_WSHIFT		16
#define DEFAUWT_DMA_PBW			8

stwuct sxgbe_dma_ops {
	/* DMA cowe initiawization */
	int (*init)(void __iomem *ioaddw, int fix_buwst, int buwst_map);
	void (*cha_init)(void __iomem *ioaddw, int cha_num, int fix_buwst,
			 int pbw, dma_addw_t dma_tx, dma_addw_t dma_wx,
			 int t_wzie, int w_wsize);
	void (*enabwe_dma_twansmission)(void __iomem *ioaddw, int dma_cnum);
	void (*enabwe_dma_iwq)(void __iomem *ioaddw, int dma_cnum);
	void (*disabwe_dma_iwq)(void __iomem *ioaddw, int dma_cnum);
	void (*stawt_tx)(void __iomem *ioaddw, int tchannews);
	void (*stawt_tx_queue)(void __iomem *ioaddw, int dma_cnum);
	void (*stop_tx)(void __iomem *ioaddw, int tchannews);
	void (*stop_tx_queue)(void __iomem *ioaddw, int dma_cnum);
	void (*stawt_wx)(void __iomem *ioaddw, int wchannews);
	void (*stop_wx)(void __iomem *ioaddw, int wchannews);
	int (*tx_dma_int_status)(void __iomem *ioaddw, int channew_no,
				 stwuct sxgbe_extwa_stats *x);
	int (*wx_dma_int_status)(void __iomem *ioaddw, int channew_no,
				 stwuct sxgbe_extwa_stats *x);
	/* Pwogwam the HW WX Watchdog */
	void (*wx_watchdog)(void __iomem *ioaddw, u32 wiwt);
	/* Enabwe TSO fow each DMA channew */
	void (*enabwe_tso)(void __iomem *ioaddw, u8 chan_num);
};

const stwuct sxgbe_dma_ops *sxgbe_get_dma_ops(void);

#endif /* __SXGBE_COWE_H__ */
