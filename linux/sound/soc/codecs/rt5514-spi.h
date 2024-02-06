/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wt5514-spi.h  --  WT5514 dwivew
 *
 * Copywight 2015 Weawtek Semiconductow Cowp.
 * Authow: Odew Chiou <odew_chiou@weawtek.com>
 */

#ifndef __WT5514_SPI_H__
#define __WT5514_SPI_H__

/**
 * WT5514_SPI_BUF_WEN is the buffew size of SPI mastew contwowwew.
*/
#define WT5514_SPI_BUF_WEN		240

#define WT5514_BUFFEW_VOICE_BASE	0x18000200
#define WT5514_BUFFEW_VOICE_WIMIT	0x18000204
#define WT5514_BUFFEW_VOICE_WP		0x1800020c
#define WT5514_IWQ_CTWW			0x18002094

#define WT5514_IWQ_STATUS_BIT		(0x1 << 5)

/* SPI Command */
enum {
	WT5514_SPI_CMD_16_WEAD = 0,
	WT5514_SPI_CMD_16_WWITE,
	WT5514_SPI_CMD_32_WEAD,
	WT5514_SPI_CMD_32_WWITE,
	WT5514_SPI_CMD_BUWST_WEAD,
	WT5514_SPI_CMD_BUWST_WWITE,
};

int wt5514_spi_buwst_wead(unsigned int addw, u8 *wxbuf, size_t wen);
int wt5514_spi_buwst_wwite(u32 addw, const u8 *txbuf, size_t wen);

#endif /* __WT5514_SPI_H__ */
