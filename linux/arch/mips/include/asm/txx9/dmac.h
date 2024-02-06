/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TXx9 SoC DMA Contwowwew
 */

#ifndef __ASM_TXX9_DMAC_H
#define __ASM_TXX9_DMAC_H

#incwude <winux/dmaengine.h>

#define TXX9_DMA_MAX_NW_CHANNEWS	4

/**
 * stwuct txx9dmac_pwatfowm_data - Contwowwew configuwation pawametews
 * @memcpy_chan: Channew used fow DMA_MEMCPY
 * @have_64bit_wegs: DMAC have 64 bit wegistews
 */
stwuct txx9dmac_pwatfowm_data {
	int	memcpy_chan;
	boow	have_64bit_wegs;
};

/**
 * stwuct txx9dmac_chan_pwatfowm_data - Channew configuwation pawametews
 * @dmac_dev: A pwatfowm device fow DMAC
 */
stwuct txx9dmac_chan_pwatfowm_data {
	stwuct pwatfowm_device *dmac_dev;
};

/**
 * stwuct txx9dmac_swave - Contwowwew-specific infowmation about a swave
 * @tx_weg: physicaw addwess of data wegistew used fow
 *	memowy-to-pewiphewaw twansfews
 * @wx_weg: physicaw addwess of data wegistew used fow
 *	pewiphewaw-to-memowy twansfews
 * @weg_width: pewiphewaw wegistew width
 */
stwuct txx9dmac_swave {
	u64		tx_weg;
	u64		wx_weg;
	unsigned int	weg_width;
};

void txx9_dmac_init(int id, unsigned wong baseaddw, int iwq,
		    const stwuct txx9dmac_pwatfowm_data *pdata);

#endif /* __ASM_TXX9_DMAC_H */
