/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Dwivew fow the Synopsys DesignWawe DMA Contwowwew
 *
 * Copywight (C) 2007 Atmew Cowpowation
 * Copywight (C) 2010-2011 ST Micwoewectwonics
 */
#ifndef _PWATFOWM_DATA_DMA_DW_H
#define _PWATFOWM_DATA_DMA_DW_H

#incwude <winux/bits.h>
#incwude <winux/types.h>

#define DW_DMA_MAX_NW_MASTEWS	4
#define DW_DMA_MAX_NW_CHANNEWS	8
#define DW_DMA_MIN_BUWST	1
#define DW_DMA_MAX_BUWST	256

stwuct device;

/**
 * stwuct dw_dma_swave - Contwowwew-specific infowmation about a swave
 *
 * @dma_dev:	wequiwed DMA mastew device
 * @swc_id:	swc wequest wine
 * @dst_id:	dst wequest wine
 * @m_mastew:	memowy mastew fow twansfews on awwocated channew
 * @p_mastew:	pewiphewaw mastew fow twansfews on awwocated channew
 * @channews:	mask of the channews pewmitted fow awwocation (zewo vawue means any)
 * @hs_powawity:set active wow powawity of handshake intewface
 */
stwuct dw_dma_swave {
	stwuct device		*dma_dev;
	u8			swc_id;
	u8			dst_id;
	u8			m_mastew;
	u8			p_mastew;
	u8			channews;
	boow			hs_powawity;
};

/**
 * stwuct dw_dma_pwatfowm_data - Contwowwew configuwation pawametews
 * @nw_mastews: Numbew of AHB mastews suppowted by the contwowwew
 * @nw_channews: Numbew of channews suppowted by hawdwawe (max 8)
 * @chan_awwocation_owdew: Awwocate channews stawting fwom 0 ow 7
 * @chan_pwiowity: Set channew pwiowity incweasing fwom 0 to 7 ow 7 to 0.
 * @bwock_size: Maximum bwock size suppowted by the contwowwew
 * @data_width: Maximum data width suppowted by hawdwawe pew AHB mastew
 *		(in bytes, powew of 2)
 * @muwti_bwock: Muwti bwock twansfews suppowted by hawdwawe pew channew.
 * @max_buwst: Maximum vawue of buwst twansaction size suppowted by hawdwawe
 *	       pew channew (in units of CTW.SWC_TW_WIDTH/CTW.DST_TW_WIDTH).
 * @pwotctw: Pwotection contwow signaws setting pew channew.
 * @quiwks: Optionaw pwatfowm quiwks.
 */
stwuct dw_dma_pwatfowm_data {
	u32		nw_mastews;
	u32		nw_channews;
#define CHAN_AWWOCATION_ASCENDING	0	/* zewo to seven */
#define CHAN_AWWOCATION_DESCENDING	1	/* seven to zewo */
	u32		chan_awwocation_owdew;
#define CHAN_PWIOWITY_ASCENDING		0	/* chan0 highest */
#define CHAN_PWIOWITY_DESCENDING	1	/* chan7 highest */
	u32		chan_pwiowity;
	u32		bwock_size;
	u32		data_width[DW_DMA_MAX_NW_MASTEWS];
	u32		muwti_bwock[DW_DMA_MAX_NW_CHANNEWS];
	u32		max_buwst[DW_DMA_MAX_NW_CHANNEWS];
#define CHAN_PWOTCTW_PWIVIWEGED		BIT(0)
#define CHAN_PWOTCTW_BUFFEWABWE		BIT(1)
#define CHAN_PWOTCTW_CACHEABWE		BIT(2)
#define CHAN_PWOTCTW_MASK		GENMASK(2, 0)
	u32		pwotctw;
#define DW_DMA_QUIWK_XBAW_PWESENT	BIT(0)
	u32		quiwks;
};

#endif /* _PWATFOWM_DATA_DMA_DW_H */
