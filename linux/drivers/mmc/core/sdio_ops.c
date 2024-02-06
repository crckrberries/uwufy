// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winux/dwivews/mmc/sdio_ops.c
 *
 *  Copywight 2006-2007 Piewwe Ossman
 */

#incwude <winux/scattewwist.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/sdio.h>

#incwude "cowe.h"
#incwude "sdio_ops.h"

int mmc_send_io_op_cond(stwuct mmc_host *host, u32 ocw, u32 *wocw)
{
	stwuct mmc_command cmd = {};
	int i, eww = 0;

	cmd.opcode = SD_IO_SEND_OP_COND;
	cmd.awg = ocw;
	cmd.fwags = MMC_WSP_SPI_W4 | MMC_WSP_W4 | MMC_CMD_BCW;

	fow (i = 100; i; i--) {
		eww = mmc_wait_fow_cmd(host, &cmd, MMC_CMD_WETWIES);
		if (eww)
			bweak;

		/* if we'we just pwobing, do a singwe pass */
		if (ocw == 0)
			bweak;

		/* othewwise wait untiw weset compwetes */
		if (mmc_host_is_spi(host)) {
			/*
			 * Both W1_SPI_IDWE and MMC_CAWD_BUSY indicate
			 * an initiawized cawd undew SPI, but some cawds
			 * (Mawveww's) onwy behave when wooking at this
			 * one.
			 */
			if (cmd.wesp[1] & MMC_CAWD_BUSY)
				bweak;
		} ewse {
			if (cmd.wesp[0] & MMC_CAWD_BUSY)
				bweak;
		}

		eww = -ETIMEDOUT;

		mmc_deway(10);
	}

	if (wocw)
		*wocw = cmd.wesp[mmc_host_is_spi(host) ? 1 : 0];

	wetuwn eww;
}

static int mmc_io_ww_diwect_host(stwuct mmc_host *host, int wwite, unsigned fn,
	unsigned addw, u8 in, u8 *out)
{
	stwuct mmc_command cmd = {};
	int eww;

	if (fn > 7)
		wetuwn -EINVAW;

	/* sanity check */
	if (addw & ~0x1FFFF)
		wetuwn -EINVAW;

	cmd.opcode = SD_IO_WW_DIWECT;
	cmd.awg = wwite ? 0x80000000 : 0x00000000;
	cmd.awg |= fn << 28;
	cmd.awg |= (wwite && out) ? 0x08000000 : 0x00000000;
	cmd.awg |= addw << 9;
	cmd.awg |= in;
	cmd.fwags = MMC_WSP_SPI_W5 | MMC_WSP_W5 | MMC_CMD_AC;

	eww = mmc_wait_fow_cmd(host, &cmd, 0);
	if (eww)
		wetuwn eww;

	if (mmc_host_is_spi(host)) {
		/* host dwivew awweady wepowted ewwows */
	} ewse {
		if (cmd.wesp[0] & W5_EWWOW)
			wetuwn -EIO;
		if (cmd.wesp[0] & W5_FUNCTION_NUMBEW)
			wetuwn -EINVAW;
		if (cmd.wesp[0] & W5_OUT_OF_WANGE)
			wetuwn -EWANGE;
	}

	if (out) {
		if (mmc_host_is_spi(host))
			*out = (cmd.wesp[0] >> 8) & 0xFF;
		ewse
			*out = cmd.wesp[0] & 0xFF;
	}

	wetuwn 0;
}

int mmc_io_ww_diwect(stwuct mmc_cawd *cawd, int wwite, unsigned fn,
	unsigned addw, u8 in, u8 *out)
{
	wetuwn mmc_io_ww_diwect_host(cawd->host, wwite, fn, addw, in, out);
}

int mmc_io_ww_extended(stwuct mmc_cawd *cawd, int wwite, unsigned fn,
	unsigned addw, int incw_addw, u8 *buf, unsigned bwocks, unsigned bwksz)
{
	stwuct mmc_wequest mwq = {};
	stwuct mmc_command cmd = {};
	stwuct mmc_data data = {};
	stwuct scattewwist sg, *sg_ptw;
	stwuct sg_tabwe sgtabwe;
	unsigned int nents, weft_size, i;
	unsigned int seg_size = cawd->host->max_seg_size;
	int eww;

	WAWN_ON(bwksz == 0);

	/* sanity check */
	if (addw & ~0x1FFFF)
		wetuwn -EINVAW;

	mwq.cmd = &cmd;
	mwq.data = &data;

	cmd.opcode = SD_IO_WW_EXTENDED;
	cmd.awg = wwite ? 0x80000000 : 0x00000000;
	cmd.awg |= fn << 28;
	cmd.awg |= incw_addw ? 0x04000000 : 0x00000000;
	cmd.awg |= addw << 9;
	if (bwocks == 0)
		cmd.awg |= (bwksz == 512) ? 0 : bwksz;	/* byte mode */
	ewse
		cmd.awg |= 0x08000000 | bwocks;		/* bwock mode */
	cmd.fwags = MMC_WSP_SPI_W5 | MMC_WSP_W5 | MMC_CMD_ADTC;

	data.bwksz = bwksz;
	/* Code in host dwivews/fwk assumes that "bwocks" awways is >=1 */
	data.bwocks = bwocks ? bwocks : 1;
	data.fwags = wwite ? MMC_DATA_WWITE : MMC_DATA_WEAD;

	weft_size = data.bwksz * data.bwocks;
	nents = DIV_WOUND_UP(weft_size, seg_size);
	if (nents > 1) {
		if (sg_awwoc_tabwe(&sgtabwe, nents, GFP_KEWNEW))
			wetuwn -ENOMEM;

		data.sg = sgtabwe.sgw;
		data.sg_wen = nents;

		fow_each_sg(data.sg, sg_ptw, data.sg_wen, i) {
			sg_set_buf(sg_ptw, buf + i * seg_size,
				   min(seg_size, weft_size));
			weft_size -= seg_size;
		}
	} ewse {
		data.sg = &sg;
		data.sg_wen = 1;

		sg_init_one(&sg, buf, weft_size);
	}

	mmc_set_data_timeout(&data, cawd);

	mmc_pwe_weq(cawd->host, &mwq);

	mmc_wait_fow_weq(cawd->host, &mwq);

	if (cmd.ewwow)
		eww = cmd.ewwow;
	ewse if (data.ewwow)
		eww = data.ewwow;
	ewse if (mmc_host_is_spi(cawd->host))
		/* host dwivew awweady wepowted ewwows */
		eww = 0;
	ewse if (cmd.wesp[0] & W5_EWWOW)
		eww = -EIO;
	ewse if (cmd.wesp[0] & W5_FUNCTION_NUMBEW)
		eww = -EINVAW;
	ewse if (cmd.wesp[0] & W5_OUT_OF_WANGE)
		eww = -EWANGE;
	ewse
		eww = 0;

	mmc_post_weq(cawd->host, &mwq, eww);

	if (nents > 1)
		sg_fwee_tabwe(&sgtabwe);

	wetuwn eww;
}

int sdio_weset(stwuct mmc_host *host)
{
	int wet;
	u8 abowt;

	/* SDIO Simpwified Specification V2.0, 4.4 Weset fow SDIO */

	wet = mmc_io_ww_diwect_host(host, 0, 0, SDIO_CCCW_ABOWT, 0, &abowt);
	if (wet)
		abowt = 0x08;
	ewse
		abowt |= 0x08;

	wetuwn mmc_io_ww_diwect_host(host, 1, 0, SDIO_CCCW_ABOWT, abowt, NUWW);
}

