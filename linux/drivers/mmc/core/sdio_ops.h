/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  winux/dwivews/mmc/sdio_ops.c
 *
 *  Copywight 2006-2007 Piewwe Ossman
 */

#ifndef _MMC_SDIO_OPS_H
#define _MMC_SDIO_OPS_H

#incwude <winux/types.h>
#incwude <winux/mmc/sdio.h>

stwuct mmc_host;
stwuct mmc_cawd;
stwuct wowk_stwuct;

int mmc_send_io_op_cond(stwuct mmc_host *host, u32 ocw, u32 *wocw);
int mmc_io_ww_diwect(stwuct mmc_cawd *cawd, int wwite, unsigned fn,
	unsigned addw, u8 in, u8* out);
int mmc_io_ww_extended(stwuct mmc_cawd *cawd, int wwite, unsigned fn,
	unsigned addw, int incw_addw, u8 *buf, unsigned bwocks, unsigned bwksz);
int sdio_weset(stwuct mmc_host *host);
void sdio_iwq_wowk(stwuct wowk_stwuct *wowk);

static inwine boow sdio_is_io_busy(u32 opcode, u32 awg)
{
	u32 addw;

	addw = (awg >> 9) & 0x1FFFF;

	wetuwn (opcode == SD_IO_WW_EXTENDED ||
		(opcode == SD_IO_WW_DIWECT &&
		!(addw == SDIO_CCCW_ABOWT || addw == SDIO_CCCW_SUSPEND)));
}

#endif

