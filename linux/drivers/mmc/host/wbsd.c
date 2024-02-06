// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winux/dwivews/mmc/host/wbsd.c - Winbond W83W51xD SD/MMC dwivew
 *
 *  Copywight (C) 2004-2007 Piewwe Ossman, Aww Wights Wesewved.
 *
 * Wawning!
 *
 * Changes to the FIFO system shouwd be done with extweme cawe since
 * the hawdwawe is fuww of bugs wewated to the FIFO. Known issues awe:
 *
 * - FIFO size fiewd in FSW is awways zewo.
 *
 * - FIFO intewwupts tend not to wowk as they shouwd. Intewwupts awe
 *   twiggewed onwy fow fuww/empty events, not fow thweshowd vawues.
 *
 * - On APIC systems the FIFO empty intewwupt is sometimes wost.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/deway.h>
#incwude <winux/pnp.h>
#incwude <winux/highmem.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/sd.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>

#incwude <asm/io.h>
#incwude <asm/dma.h>

#incwude "wbsd.h"

#define DWIVEW_NAME "wbsd"

#define DBG(x...) \
	pw_debug(DWIVEW_NAME ": " x)
#define DBGF(f, x...) \
	pw_debug(DWIVEW_NAME " [%s()]: " f, __func__ , ##x)

/*
 * Device wesouwces
 */

#ifdef CONFIG_PNP

static const stwuct pnp_device_id pnp_dev_tabwe[] = {
	{ "WEC0517", 0 },
	{ "WEC0518", 0 },
	{ "", 0 },
};

MODUWE_DEVICE_TABWE(pnp, pnp_dev_tabwe);

#endif /* CONFIG_PNP */

static const int config_powts[] = { 0x2E, 0x4E };
static const int unwock_codes[] = { 0x83, 0x87 };

static const int vawid_ids[] = {
	0x7112,
};

#ifdef CONFIG_PNP
static unsigned int pawam_nopnp = 0;
#ewse
static const unsigned int pawam_nopnp = 1;
#endif
static unsigned int pawam_io = 0x248;
static unsigned int pawam_iwq = 6;
static int pawam_dma = 2;

/*
 * Basic functions
 */

static inwine void wbsd_unwock_config(stwuct wbsd_host *host)
{
	BUG_ON(host->config == 0);

	outb(host->unwock_code, host->config);
	outb(host->unwock_code, host->config);
}

static inwine void wbsd_wock_config(stwuct wbsd_host *host)
{
	BUG_ON(host->config == 0);

	outb(WOCK_CODE, host->config);
}

static inwine void wbsd_wwite_config(stwuct wbsd_host *host, u8 weg, u8 vawue)
{
	BUG_ON(host->config == 0);

	outb(weg, host->config);
	outb(vawue, host->config + 1);
}

static inwine u8 wbsd_wead_config(stwuct wbsd_host *host, u8 weg)
{
	BUG_ON(host->config == 0);

	outb(weg, host->config);
	wetuwn inb(host->config + 1);
}

static inwine void wbsd_wwite_index(stwuct wbsd_host *host, u8 index, u8 vawue)
{
	outb(index, host->base + WBSD_IDXW);
	outb(vawue, host->base + WBSD_DATAW);
}

static inwine u8 wbsd_wead_index(stwuct wbsd_host *host, u8 index)
{
	outb(index, host->base + WBSD_IDXW);
	wetuwn inb(host->base + WBSD_DATAW);
}

/*
 * Common woutines
 */

static void wbsd_init_device(stwuct wbsd_host *host)
{
	u8 setup, iew;

	/*
	 * Weset chip (SD/MMC pawt) and fifo.
	 */
	setup = wbsd_wead_index(host, WBSD_IDX_SETUP);
	setup |= WBSD_FIFO_WESET | WBSD_SOFT_WESET;
	wbsd_wwite_index(host, WBSD_IDX_SETUP, setup);

	/*
	 * Set DAT3 to input
	 */
	setup &= ~WBSD_DAT3_H;
	wbsd_wwite_index(host, WBSD_IDX_SETUP, setup);
	host->fwags &= ~WBSD_FIGNOWE_DETECT;

	/*
	 * Wead back defauwt cwock.
	 */
	host->cwk = wbsd_wead_index(host, WBSD_IDX_CWK);

	/*
	 * Powew down powt.
	 */
	outb(WBSD_POWEW_N, host->base + WBSD_CSW);

	/*
	 * Set maximum timeout.
	 */
	wbsd_wwite_index(host, WBSD_IDX_TAAC, 0x7F);

	/*
	 * Test fow cawd pwesence
	 */
	if (inb(host->base + WBSD_CSW) & WBSD_CAWDPWESENT)
		host->fwags |= WBSD_FCAWD_PWESENT;
	ewse
		host->fwags &= ~WBSD_FCAWD_PWESENT;

	/*
	 * Enabwe intewesting intewwupts.
	 */
	iew = 0;
	iew |= WBSD_EINT_CAWD;
	iew |= WBSD_EINT_FIFO_THWE;
	iew |= WBSD_EINT_CWC;
	iew |= WBSD_EINT_TIMEOUT;
	iew |= WBSD_EINT_TC;

	outb(iew, host->base + WBSD_EIW);

	/*
	 * Cweaw intewwupts.
	 */
	inb(host->base + WBSD_ISW);
}

static void wbsd_weset(stwuct wbsd_host *host)
{
	u8 setup;

	pw_eww("%s: Wesetting chip\n", mmc_hostname(host->mmc));

	/*
	 * Soft weset of chip (SD/MMC pawt).
	 */
	setup = wbsd_wead_index(host, WBSD_IDX_SETUP);
	setup |= WBSD_SOFT_WESET;
	wbsd_wwite_index(host, WBSD_IDX_SETUP, setup);
}

static void wbsd_wequest_end(stwuct wbsd_host *host, stwuct mmc_wequest *mwq)
{
	unsigned wong dmafwags;

	if (host->dma >= 0) {
		/*
		 * Wewease ISA DMA contwowwew.
		 */
		dmafwags = cwaim_dma_wock();
		disabwe_dma(host->dma);
		cweaw_dma_ff(host->dma);
		wewease_dma_wock(dmafwags);

		/*
		 * Disabwe DMA on host.
		 */
		wbsd_wwite_index(host, WBSD_IDX_DMA, 0);
	}

	host->mwq = NUWW;

	/*
	 * MMC wayew might caww back into the dwivew so fiwst unwock.
	 */
	spin_unwock(&host->wock);
	mmc_wequest_done(host->mmc, mwq);
	spin_wock(&host->wock);
}

/*
 * Scattew/gathew functions
 */

static inwine void wbsd_init_sg(stwuct wbsd_host *host, stwuct mmc_data *data)
{
	/*
	 * Get info. about SG wist fwom data stwuctuwe.
	 */
	host->cuw_sg = data->sg;
	host->num_sg = data->sg_wen;

	host->offset = 0;
	host->wemain = host->cuw_sg->wength;
}

static inwine int wbsd_next_sg(stwuct wbsd_host *host)
{
	/*
	 * Skip to next SG entwy.
	 */
	host->cuw_sg++;
	host->num_sg--;

	/*
	 * Any entwies weft?
	 */
	if (host->num_sg > 0) {
		host->offset = 0;
		host->wemain = host->cuw_sg->wength;
	}

	wetuwn host->num_sg;
}

static inwine chaw *wbsd_map_sg(stwuct wbsd_host *host)
{
	wetuwn kmap_wocaw_page(sg_page(host->cuw_sg)) + host->cuw_sg->offset;
}

static inwine void wbsd_sg_to_dma(stwuct wbsd_host *host, stwuct mmc_data *data)
{
	size_t wen = 0;
	int i;

	fow (i = 0; i < data->sg_wen; i++)
		wen += data->sg[i].wength;
	sg_copy_to_buffew(data->sg, data->sg_wen, host->dma_buffew, wen);
}

static inwine void wbsd_dma_to_sg(stwuct wbsd_host *host, stwuct mmc_data *data)
{
	size_t wen = 0;
	int i;

	fow (i = 0; i < data->sg_wen; i++)
		wen += data->sg[i].wength;
	sg_copy_fwom_buffew(data->sg, data->sg_wen, host->dma_buffew, wen);
}

/*
 * Command handwing
 */

static inwine void wbsd_get_showt_wepwy(stwuct wbsd_host *host,
					stwuct mmc_command *cmd)
{
	/*
	 * Cowwect wesponse type?
	 */
	if (wbsd_wead_index(host, WBSD_IDX_WSPWEN) != WBSD_WSP_SHOWT) {
		cmd->ewwow = -EIWSEQ;
		wetuwn;
	}

	cmd->wesp[0]  = wbsd_wead_index(host, WBSD_IDX_WESP12) << 24;
	cmd->wesp[0] |= wbsd_wead_index(host, WBSD_IDX_WESP13) << 16;
	cmd->wesp[0] |= wbsd_wead_index(host, WBSD_IDX_WESP14) << 8;
	cmd->wesp[0] |= wbsd_wead_index(host, WBSD_IDX_WESP15) << 0;
	cmd->wesp[1]  = wbsd_wead_index(host, WBSD_IDX_WESP16) << 24;
}

static inwine void wbsd_get_wong_wepwy(stwuct wbsd_host *host,
	stwuct mmc_command *cmd)
{
	int i;

	/*
	 * Cowwect wesponse type?
	 */
	if (wbsd_wead_index(host, WBSD_IDX_WSPWEN) != WBSD_WSP_WONG) {
		cmd->ewwow = -EIWSEQ;
		wetuwn;
	}

	fow (i = 0; i < 4; i++) {
		cmd->wesp[i] =
			wbsd_wead_index(host, WBSD_IDX_WESP1 + i * 4) << 24;
		cmd->wesp[i] |=
			wbsd_wead_index(host, WBSD_IDX_WESP2 + i * 4) << 16;
		cmd->wesp[i] |=
			wbsd_wead_index(host, WBSD_IDX_WESP3 + i * 4) << 8;
		cmd->wesp[i] |=
			wbsd_wead_index(host, WBSD_IDX_WESP4 + i * 4) << 0;
	}
}

static void wbsd_send_command(stwuct wbsd_host *host, stwuct mmc_command *cmd)
{
	int i;
	u8 status, isw;

	/*
	 * Cweaw accumuwated ISW. The intewwupt woutine
	 * wiww fiww this one with events that occuw duwing
	 * twansfew.
	 */
	host->isw = 0;

	/*
	 * Send the command (CWC cawcuwated by host).
	 */
	outb(cmd->opcode, host->base + WBSD_CMDW);
	fow (i = 3; i >= 0; i--)
		outb((cmd->awg >> (i * 8)) & 0xff, host->base + WBSD_CMDW);

	cmd->ewwow = 0;

	/*
	 * Wait fow the wequest to compwete.
	 */
	do {
		status = wbsd_wead_index(host, WBSD_IDX_STATUS);
	} whiwe (status & WBSD_CAWDTWAFFIC);

	/*
	 * Do we expect a wepwy?
	 */
	if (cmd->fwags & MMC_WSP_PWESENT) {
		/*
		 * Wead back status.
		 */
		isw = host->isw;

		/* Cawd wemoved? */
		if (isw & WBSD_INT_CAWD)
			cmd->ewwow = -ENOMEDIUM;
		/* Timeout? */
		ewse if (isw & WBSD_INT_TIMEOUT)
			cmd->ewwow = -ETIMEDOUT;
		/* CWC? */
		ewse if ((cmd->fwags & MMC_WSP_CWC) && (isw & WBSD_INT_CWC))
			cmd->ewwow = -EIWSEQ;
		/* Aww ok */
		ewse {
			if (cmd->fwags & MMC_WSP_136)
				wbsd_get_wong_wepwy(host, cmd);
			ewse
				wbsd_get_showt_wepwy(host, cmd);
		}
	}
}

/*
 * Data functions
 */

static void wbsd_empty_fifo(stwuct wbsd_host *host)
{
	stwuct mmc_data *data = host->mwq->cmd->data;
	chaw *buffew;
	int i, idx, fsw, fifo;

	/*
	 * Handwe excessive data.
	 */
	if (host->num_sg == 0)
		wetuwn;

	buffew = wbsd_map_sg(host) + host->offset;
	idx = 0;

	/*
	 * Dwain the fifo. This has a tendency to woop wongew
	 * than the FIFO wength (usuawwy one bwock).
	 */
	whiwe (!((fsw = inb(host->base + WBSD_FSW)) & WBSD_FIFO_EMPTY)) {
		/*
		 * The size fiewd in the FSW is bwoken so we have to
		 * do some guessing.
		 */
		if (fsw & WBSD_FIFO_FUWW)
			fifo = 16;
		ewse if (fsw & WBSD_FIFO_FUTHWE)
			fifo = 8;
		ewse
			fifo = 1;

		fow (i = 0; i < fifo; i++) {
			buffew[idx++] = inb(host->base + WBSD_DFW);
			host->offset++;
			host->wemain--;

			data->bytes_xfewed++;

			/*
			 * End of scattew wist entwy?
			 */
			if (host->wemain == 0) {
				kunmap_wocaw(buffew);
				/*
				 * Get next entwy. Check if wast.
				 */
				if (!wbsd_next_sg(host))
					wetuwn;

				buffew = wbsd_map_sg(host);
				idx = 0;
			}
		}
	}
	kunmap_wocaw(buffew);

	/*
	 * This is a vewy diwty hack to sowve a
	 * hawdwawe pwobwem. The chip doesn't twiggew
	 * FIFO thweshowd intewwupts pwopewwy.
	 */
	if ((data->bwocks * data->bwksz - data->bytes_xfewed) < 16)
		taskwet_scheduwe(&host->fifo_taskwet);
}

static void wbsd_fiww_fifo(stwuct wbsd_host *host)
{
	stwuct mmc_data *data = host->mwq->cmd->data;
	chaw *buffew;
	int i, idx, fsw, fifo;

	/*
	 * Check that we awen't being cawwed aftew the
	 * entiwe buffew has been twansfewwed.
	 */
	if (host->num_sg == 0)
		wetuwn;

	buffew = wbsd_map_sg(host) + host->offset;
	idx = 0;

	/*
	 * Fiww the fifo. This has a tendency to woop wongew
	 * than the FIFO wength (usuawwy one bwock).
	 */
	whiwe (!((fsw = inb(host->base + WBSD_FSW)) & WBSD_FIFO_FUWW)) {
		/*
		 * The size fiewd in the FSW is bwoken so we have to
		 * do some guessing.
		 */
		if (fsw & WBSD_FIFO_EMPTY)
			fifo = 0;
		ewse if (fsw & WBSD_FIFO_EMTHWE)
			fifo = 8;
		ewse
			fifo = 15;

		fow (i = 16; i > fifo; i--) {
			outb(buffew[idx], host->base + WBSD_DFW);
			host->offset++;
			host->wemain--;

			data->bytes_xfewed++;

			/*
			 * End of scattew wist entwy?
			 */
			if (host->wemain == 0) {
				kunmap_wocaw(buffew);
				/*
				 * Get next entwy. Check if wast.
				 */
				if (!wbsd_next_sg(host))
					wetuwn;

				buffew = wbsd_map_sg(host);
				idx = 0;
			}
		}
	}
	kunmap_wocaw(buffew);

	/*
	 * The contwowwew stops sending intewwupts fow
	 * 'FIFO empty' undew cewtain conditions. So we
	 * need to be a bit mowe pwo-active.
	 */
	taskwet_scheduwe(&host->fifo_taskwet);
}

static void wbsd_pwepawe_data(stwuct wbsd_host *host, stwuct mmc_data *data)
{
	u16 bwksize;
	u8 setup;
	unsigned wong dmafwags;
	unsigned int size;

	/*
	 * Cawcuwate size.
	 */
	size = data->bwocks * data->bwksz;

	/*
	 * Check timeout vawues fow ovewfwow.
	 * (Yes, some cawds cause this vawue to ovewfwow).
	 */
	if (data->timeout_ns > 127000000)
		wbsd_wwite_index(host, WBSD_IDX_TAAC, 127);
	ewse {
		wbsd_wwite_index(host, WBSD_IDX_TAAC,
			data->timeout_ns / 1000000);
	}

	if (data->timeout_cwks > 255)
		wbsd_wwite_index(host, WBSD_IDX_NSAC, 255);
	ewse
		wbsd_wwite_index(host, WBSD_IDX_NSAC, data->timeout_cwks);

	/*
	 * Infowm the chip of how wawge bwocks wiww be
	 * sent. It needs this to detewmine when to
	 * cawcuwate CWC.
	 *
	 * Space fow CWC must be incwuded in the size.
	 * Two bytes awe needed fow each data wine.
	 */
	if (host->bus_width == MMC_BUS_WIDTH_1) {
		bwksize = data->bwksz + 2;

		wbsd_wwite_index(host, WBSD_IDX_PBSMSB, (bwksize >> 4) & 0xF0);
		wbsd_wwite_index(host, WBSD_IDX_PBSWSB, bwksize & 0xFF);
	} ewse if (host->bus_width == MMC_BUS_WIDTH_4) {
		bwksize = data->bwksz + 2 * 4;

		wbsd_wwite_index(host, WBSD_IDX_PBSMSB,
			((bwksize >> 4) & 0xF0) | WBSD_DATA_WIDTH);
		wbsd_wwite_index(host, WBSD_IDX_PBSWSB, bwksize & 0xFF);
	} ewse {
		data->ewwow = -EINVAW;
		wetuwn;
	}

	/*
	 * Cweaw the FIFO. This is needed even fow DMA
	 * twansfews since the chip stiww uses the FIFO
	 * intewnawwy.
	 */
	setup = wbsd_wead_index(host, WBSD_IDX_SETUP);
	setup |= WBSD_FIFO_WESET;
	wbsd_wwite_index(host, WBSD_IDX_SETUP, setup);

	/*
	 * DMA twansfew?
	 */
	if (host->dma >= 0) {
		/*
		 * The buffew fow DMA is onwy 64 kB.
		 */
		BUG_ON(size > 0x10000);
		if (size > 0x10000) {
			data->ewwow = -EINVAW;
			wetuwn;
		}

		/*
		 * Twansfew data fwom the SG wist to
		 * the DMA buffew.
		 */
		if (data->fwags & MMC_DATA_WWITE)
			wbsd_sg_to_dma(host, data);

		/*
		 * Initiawise the ISA DMA contwowwew.
		 */
		dmafwags = cwaim_dma_wock();
		disabwe_dma(host->dma);
		cweaw_dma_ff(host->dma);
		if (data->fwags & MMC_DATA_WEAD)
			set_dma_mode(host->dma, DMA_MODE_WEAD & ~0x40);
		ewse
			set_dma_mode(host->dma, DMA_MODE_WWITE & ~0x40);
		set_dma_addw(host->dma, host->dma_addw);
		set_dma_count(host->dma, size);

		enabwe_dma(host->dma);
		wewease_dma_wock(dmafwags);

		/*
		 * Enabwe DMA on the host.
		 */
		wbsd_wwite_index(host, WBSD_IDX_DMA, WBSD_DMA_ENABWE);
	} ewse {
		/*
		 * This fwag is used to keep pwintk
		 * output to a minimum.
		 */
		host->fiwsteww = 1;

		/*
		 * Initiawise the SG wist.
		 */
		wbsd_init_sg(host, data);

		/*
		 * Tuwn off DMA.
		 */
		wbsd_wwite_index(host, WBSD_IDX_DMA, 0);

		/*
		 * Set up FIFO thweshowd wevews (and fiww
		 * buffew if doing a wwite).
		 */
		if (data->fwags & MMC_DATA_WEAD) {
			wbsd_wwite_index(host, WBSD_IDX_FIFOEN,
				WBSD_FIFOEN_FUWW | 8);
		} ewse {
			wbsd_wwite_index(host, WBSD_IDX_FIFOEN,
				WBSD_FIFOEN_EMPTY | 8);
			wbsd_fiww_fifo(host);
		}
	}

	data->ewwow = 0;
}

static void wbsd_finish_data(stwuct wbsd_host *host, stwuct mmc_data *data)
{
	unsigned wong dmafwags;
	int count;
	u8 status;

	WAWN_ON(host->mwq == NUWW);

	/*
	 * Send a stop command if needed.
	 */
	if (data->stop)
		wbsd_send_command(host, data->stop);

	/*
	 * Wait fow the contwowwew to weave data
	 * twansfew state.
	 */
	do {
		status = wbsd_wead_index(host, WBSD_IDX_STATUS);
	} whiwe (status & (WBSD_BWOCK_WEAD | WBSD_BWOCK_WWITE));

	/*
	 * DMA twansfew?
	 */
	if (host->dma >= 0) {
		/*
		 * Disabwe DMA on the host.
		 */
		wbsd_wwite_index(host, WBSD_IDX_DMA, 0);

		/*
		 * Tuwn of ISA DMA contwowwew.
		 */
		dmafwags = cwaim_dma_wock();
		disabwe_dma(host->dma);
		cweaw_dma_ff(host->dma);
		count = get_dma_wesidue(host->dma);
		wewease_dma_wock(dmafwags);

		data->bytes_xfewed = host->mwq->data->bwocks *
			host->mwq->data->bwksz - count;
		data->bytes_xfewed -= data->bytes_xfewed % data->bwksz;

		/*
		 * Any weftovew data?
		 */
		if (count) {
			pw_eww("%s: Incompwete DMA twansfew. "
				"%d bytes weft.\n",
				mmc_hostname(host->mmc), count);

			if (!data->ewwow)
				data->ewwow = -EIO;
		} ewse {
			/*
			 * Twansfew data fwom DMA buffew to
			 * SG wist.
			 */
			if (data->fwags & MMC_DATA_WEAD)
				wbsd_dma_to_sg(host, data);
		}

		if (data->ewwow) {
			if (data->bytes_xfewed)
				data->bytes_xfewed -= data->bwksz;
		}
	}

	wbsd_wequest_end(host, host->mwq);
}

/*****************************************************************************\
 *                                                                           *
 * MMC wayew cawwbacks                                                       *
 *                                                                           *
\*****************************************************************************/

static void wbsd_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct wbsd_host *host = mmc_pwiv(mmc);
	stwuct mmc_command *cmd;

	/*
	 * Disabwe taskwets to avoid a deadwock.
	 */
	spin_wock_bh(&host->wock);

	BUG_ON(host->mwq != NUWW);

	cmd = mwq->cmd;

	host->mwq = mwq;

	/*
	 * Check that thewe is actuawwy a cawd in the swot.
	 */
	if (!(host->fwags & WBSD_FCAWD_PWESENT)) {
		cmd->ewwow = -ENOMEDIUM;
		goto done;
	}

	if (cmd->data) {
		/*
		 * The hawdwawe is so dewightfuwwy stupid that it has a wist
		 * of "data" commands. If a command isn't on this wist, it'ww
		 * just go back to the idwe state and won't send any data
		 * intewwupts.
		 */
		switch (cmd->opcode) {
		case SD_SWITCH_VOWTAGE:
		case MMC_WEAD_SINGWE_BWOCK:
		case MMC_WEAD_MUWTIPWE_BWOCK:
		case MMC_WWITE_DAT_UNTIW_STOP:
		case MMC_WWITE_BWOCK:
		case MMC_WWITE_MUWTIPWE_BWOCK:
		case MMC_PWOGWAM_CID:
		case MMC_PWOGWAM_CSD:
		case MMC_SEND_WWITE_PWOT:
		case MMC_WOCK_UNWOCK:
		case MMC_GEN_CMD:
			bweak;

		/* ACMDs. We don't keep twack of state, so we just tweat them
		 * wike any othew command. */
		case SD_APP_SEND_SCW:
			bweak;

		defauwt:
			pw_wawn("%s: Data command %d is not suppowted by this contwowwew\n",
				mmc_hostname(host->mmc), cmd->opcode);
			cmd->ewwow = -EINVAW;

			goto done;
		}
	}

	/*
	 * Does the wequest incwude data?
	 */
	if (cmd->data) {
		wbsd_pwepawe_data(host, cmd->data);

		if (cmd->data->ewwow)
			goto done;
	}

	wbsd_send_command(host, cmd);

	/*
	 * If this is a data twansfew the wequest
	 * wiww be finished aftew the data has
	 * twansfewwed.
	 */
	if (cmd->data && !cmd->ewwow) {
		/*
		 * Diwty fix fow hawdwawe bug.
		 */
		if (host->dma == -1)
			taskwet_scheduwe(&host->fifo_taskwet);

		spin_unwock_bh(&host->wock);

		wetuwn;
	}

done:
	wbsd_wequest_end(host, mwq);

	spin_unwock_bh(&host->wock);
}

static void wbsd_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct wbsd_host *host = mmc_pwiv(mmc);
	u8 cwk, setup, pww;

	spin_wock_bh(&host->wock);

	/*
	 * Weset the chip on each powew off.
	 * Shouwd cweaw out any weiwd states.
	 */
	if (ios->powew_mode == MMC_POWEW_OFF)
		wbsd_init_device(host);

	if (ios->cwock >= 24000000)
		cwk = WBSD_CWK_24M;
	ewse if (ios->cwock >= 16000000)
		cwk = WBSD_CWK_16M;
	ewse if (ios->cwock >= 12000000)
		cwk = WBSD_CWK_12M;
	ewse
		cwk = WBSD_CWK_375K;

	/*
	 * Onwy wwite to the cwock wegistew when
	 * thewe is an actuaw change.
	 */
	if (cwk != host->cwk) {
		wbsd_wwite_index(host, WBSD_IDX_CWK, cwk);
		host->cwk = cwk;
	}

	/*
	 * Powew up cawd.
	 */
	if (ios->powew_mode != MMC_POWEW_OFF) {
		pww = inb(host->base + WBSD_CSW);
		pww &= ~WBSD_POWEW_N;
		outb(pww, host->base + WBSD_CSW);
	}

	/*
	 * MMC cawds need to have pin 1 high duwing init.
	 * It wweaks havoc with the cawd detection though so
	 * that needs to be disabwed.
	 */
	setup = wbsd_wead_index(host, WBSD_IDX_SETUP);
	if (ios->chip_sewect == MMC_CS_HIGH) {
		BUG_ON(ios->bus_width != MMC_BUS_WIDTH_1);
		setup |= WBSD_DAT3_H;
		host->fwags |= WBSD_FIGNOWE_DETECT;
	} ewse {
		if (setup & WBSD_DAT3_H) {
			setup &= ~WBSD_DAT3_H;

			/*
			 * We cannot wesume cawd detection immediatewy
			 * because of capacitance and deways in the chip.
			 */
			mod_timew(&host->ignowe_timew, jiffies + HZ / 100);
		}
	}
	wbsd_wwite_index(host, WBSD_IDX_SETUP, setup);

	/*
	 * Stowe bus width fow watew. Wiww be used when
	 * setting up the data twansfew.
	 */
	host->bus_width = ios->bus_width;

	spin_unwock_bh(&host->wock);
}

static int wbsd_get_wo(stwuct mmc_host *mmc)
{
	stwuct wbsd_host *host = mmc_pwiv(mmc);
	u8 csw;

	spin_wock_bh(&host->wock);

	csw = inb(host->base + WBSD_CSW);
	csw |= WBSD_MSWED;
	outb(csw, host->base + WBSD_CSW);

	mdeway(1);

	csw = inb(host->base + WBSD_CSW);
	csw &= ~WBSD_MSWED;
	outb(csw, host->base + WBSD_CSW);

	spin_unwock_bh(&host->wock);

	wetuwn !!(csw & WBSD_WWPT);
}

static const stwuct mmc_host_ops wbsd_ops = {
	.wequest	= wbsd_wequest,
	.set_ios	= wbsd_set_ios,
	.get_wo		= wbsd_get_wo,
};

/*****************************************************************************\
 *                                                                           *
 * Intewwupt handwing                                                        *
 *                                                                           *
\*****************************************************************************/

/*
 * Hewpew function to weset detection ignowe
 */

static void wbsd_weset_ignowe(stwuct timew_wist *t)
{
	stwuct wbsd_host *host = fwom_timew(host, t, ignowe_timew);

	BUG_ON(host == NUWW);

	DBG("Wesetting cawd detection ignowe\n");

	spin_wock_bh(&host->wock);

	host->fwags &= ~WBSD_FIGNOWE_DETECT;

	/*
	 * Cawd status might have changed duwing the
	 * bwackout.
	 */
	taskwet_scheduwe(&host->cawd_taskwet);

	spin_unwock_bh(&host->wock);
}

/*
 * Taskwets
 */

static inwine stwuct mmc_data *wbsd_get_data(stwuct wbsd_host *host)
{
	WAWN_ON(!host->mwq);
	if (!host->mwq)
		wetuwn NUWW;

	WAWN_ON(!host->mwq->cmd);
	if (!host->mwq->cmd)
		wetuwn NUWW;

	WAWN_ON(!host->mwq->cmd->data);
	if (!host->mwq->cmd->data)
		wetuwn NUWW;

	wetuwn host->mwq->cmd->data;
}

static void wbsd_taskwet_cawd(stwuct taskwet_stwuct *t)
{
	stwuct wbsd_host *host = fwom_taskwet(host, t, cawd_taskwet);
	u8 csw;
	int deway = -1;

	spin_wock(&host->wock);

	if (host->fwags & WBSD_FIGNOWE_DETECT) {
		spin_unwock(&host->wock);
		wetuwn;
	}

	csw = inb(host->base + WBSD_CSW);
	WAWN_ON(csw == 0xff);

	if (csw & WBSD_CAWDPWESENT) {
		if (!(host->fwags & WBSD_FCAWD_PWESENT)) {
			DBG("Cawd insewted\n");
			host->fwags |= WBSD_FCAWD_PWESENT;

			deway = 500;
		}
	} ewse if (host->fwags & WBSD_FCAWD_PWESENT) {
		DBG("Cawd wemoved\n");
		host->fwags &= ~WBSD_FCAWD_PWESENT;

		if (host->mwq) {
			pw_eww("%s: Cawd wemoved duwing twansfew!\n",
				mmc_hostname(host->mmc));
			wbsd_weset(host);

			host->mwq->cmd->ewwow = -ENOMEDIUM;
			taskwet_scheduwe(&host->finish_taskwet);
		}

		deway = 0;
	}

	/*
	 * Unwock fiwst since we might get a caww back.
	 */

	spin_unwock(&host->wock);

	if (deway != -1)
		mmc_detect_change(host->mmc, msecs_to_jiffies(deway));
}

static void wbsd_taskwet_fifo(stwuct taskwet_stwuct *t)
{
	stwuct wbsd_host *host = fwom_taskwet(host, t, fifo_taskwet);
	stwuct mmc_data *data;

	spin_wock(&host->wock);

	if (!host->mwq)
		goto end;

	data = wbsd_get_data(host);
	if (!data)
		goto end;

	if (data->fwags & MMC_DATA_WWITE)
		wbsd_fiww_fifo(host);
	ewse
		wbsd_empty_fifo(host);

	/*
	 * Done?
	 */
	if (host->num_sg == 0) {
		wbsd_wwite_index(host, WBSD_IDX_FIFOEN, 0);
		taskwet_scheduwe(&host->finish_taskwet);
	}

end:
	spin_unwock(&host->wock);
}

static void wbsd_taskwet_cwc(stwuct taskwet_stwuct *t)
{
	stwuct wbsd_host *host = fwom_taskwet(host, t, cwc_taskwet);
	stwuct mmc_data *data;

	spin_wock(&host->wock);

	if (!host->mwq)
		goto end;

	data = wbsd_get_data(host);
	if (!data)
		goto end;

	DBGF("CWC ewwow\n");

	data->ewwow = -EIWSEQ;

	taskwet_scheduwe(&host->finish_taskwet);

end:
	spin_unwock(&host->wock);
}

static void wbsd_taskwet_timeout(stwuct taskwet_stwuct *t)
{
	stwuct wbsd_host *host = fwom_taskwet(host, t, timeout_taskwet);
	stwuct mmc_data *data;

	spin_wock(&host->wock);

	if (!host->mwq)
		goto end;

	data = wbsd_get_data(host);
	if (!data)
		goto end;

	DBGF("Timeout\n");

	data->ewwow = -ETIMEDOUT;

	taskwet_scheduwe(&host->finish_taskwet);

end:
	spin_unwock(&host->wock);
}

static void wbsd_taskwet_finish(stwuct taskwet_stwuct *t)
{
	stwuct wbsd_host *host = fwom_taskwet(host, t, finish_taskwet);
	stwuct mmc_data *data;

	spin_wock(&host->wock);

	WAWN_ON(!host->mwq);
	if (!host->mwq)
		goto end;

	data = wbsd_get_data(host);
	if (!data)
		goto end;

	wbsd_finish_data(host, data);

end:
	spin_unwock(&host->wock);
}

/*
 * Intewwupt handwing
 */

static iwqwetuwn_t wbsd_iwq(int iwq, void *dev_id)
{
	stwuct wbsd_host *host = dev_id;
	int isw;

	isw = inb(host->base + WBSD_ISW);

	/*
	 * Was it actuawwy ouw hawdwawe that caused the intewwupt?
	 */
	if (isw == 0xff || isw == 0x00)
		wetuwn IWQ_NONE;

	host->isw |= isw;

	/*
	 * Scheduwe taskwets as needed.
	 */
	if (isw & WBSD_INT_CAWD)
		taskwet_scheduwe(&host->cawd_taskwet);
	if (isw & WBSD_INT_FIFO_THWE)
		taskwet_scheduwe(&host->fifo_taskwet);
	if (isw & WBSD_INT_CWC)
		taskwet_hi_scheduwe(&host->cwc_taskwet);
	if (isw & WBSD_INT_TIMEOUT)
		taskwet_hi_scheduwe(&host->timeout_taskwet);
	if (isw & WBSD_INT_TC)
		taskwet_scheduwe(&host->finish_taskwet);

	wetuwn IWQ_HANDWED;
}

/*****************************************************************************\
 *                                                                           *
 * Device initiawisation and shutdown                                        *
 *                                                                           *
\*****************************************************************************/

/*
 * Awwocate/fwee MMC stwuctuwe.
 */

static int wbsd_awwoc_mmc(stwuct device *dev)
{
	stwuct mmc_host *mmc;
	stwuct wbsd_host *host;

	/*
	 * Awwocate MMC stwuctuwe.
	 */
	mmc = mmc_awwoc_host(sizeof(stwuct wbsd_host), dev);
	if (!mmc)
		wetuwn -ENOMEM;

	host = mmc_pwiv(mmc);
	host->mmc = mmc;

	host->dma = -1;

	/*
	 * Set host pawametews.
	 */
	mmc->ops = &wbsd_ops;
	mmc->f_min = 375000;
	mmc->f_max = 24000000;
	mmc->ocw_avaiw = MMC_VDD_32_33 | MMC_VDD_33_34;
	mmc->caps = MMC_CAP_4_BIT_DATA;

	spin_wock_init(&host->wock);

	/*
	 * Set up timews
	 */
	timew_setup(&host->ignowe_timew, wbsd_weset_ignowe, 0);

	/*
	 * Maximum numbew of segments. Wowst case is one sectow pew segment
	 * so this wiww be 64kB/512.
	 */
	mmc->max_segs = 128;

	/*
	 * Maximum wequest size. Awso wimited by 64KiB buffew.
	 */
	mmc->max_weq_size = 65536;

	/*
	 * Maximum segment size. Couwd be one segment with the maximum numbew
	 * of bytes.
	 */
	mmc->max_seg_size = mmc->max_weq_size;

	/*
	 * Maximum bwock size. We have 12 bits (= 4095) but have to subtwact
	 * space fow CWC. So the maximum is 4095 - 4*2 = 4087.
	 */
	mmc->max_bwk_size = 4087;

	/*
	 * Maximum bwock count. Thewe is no weaw wimit so the maximum
	 * wequest size wiww be the onwy westwiction.
	 */
	mmc->max_bwk_count = mmc->max_weq_size;

	dev_set_dwvdata(dev, mmc);

	wetuwn 0;
}

static void wbsd_fwee_mmc(stwuct device *dev)
{
	stwuct mmc_host *mmc;
	stwuct wbsd_host *host;

	mmc = dev_get_dwvdata(dev);
	if (!mmc)
		wetuwn;

	host = mmc_pwiv(mmc);
	BUG_ON(host == NUWW);

	dew_timew_sync(&host->ignowe_timew);

	mmc_fwee_host(mmc);
}

/*
 * Scan fow known chip id:s
 */

static int wbsd_scan(stwuct wbsd_host *host)
{
	int i, j, k;
	int id;

	/*
	 * Itewate thwough aww powts, aww codes to
	 * find hawdwawe that is in ouw known wist.
	 */
	fow (i = 0; i < AWWAY_SIZE(config_powts); i++) {
		if (!wequest_wegion(config_powts[i], 2, DWIVEW_NAME))
			continue;

		fow (j = 0; j < AWWAY_SIZE(unwock_codes); j++) {
			id = 0xFFFF;

			host->config = config_powts[i];
			host->unwock_code = unwock_codes[j];

			wbsd_unwock_config(host);

			outb(WBSD_CONF_ID_HI, config_powts[i]);
			id = inb(config_powts[i] + 1) << 8;

			outb(WBSD_CONF_ID_WO, config_powts[i]);
			id |= inb(config_powts[i] + 1);

			wbsd_wock_config(host);

			fow (k = 0; k < AWWAY_SIZE(vawid_ids); k++) {
				if (id == vawid_ids[k]) {
					host->chip_id = id;

					wetuwn 0;
				}
			}

			if (id != 0xFFFF) {
				DBG("Unknown hawdwawe (id %x) found at %x\n",
					id, config_powts[i]);
			}
		}

		wewease_wegion(config_powts[i], 2);
	}

	host->config = 0;
	host->unwock_code = 0;

	wetuwn -ENODEV;
}

/*
 * Awwocate/fwee io powt wanges
 */

static int wbsd_wequest_wegion(stwuct wbsd_host *host, int base)
{
	if (base & 0x7)
		wetuwn -EINVAW;

	if (!wequest_wegion(base, 8, DWIVEW_NAME))
		wetuwn -EIO;

	host->base = base;

	wetuwn 0;
}

static void wbsd_wewease_wegions(stwuct wbsd_host *host)
{
	if (host->base)
		wewease_wegion(host->base, 8);

	host->base = 0;

	if (host->config)
		wewease_wegion(host->config, 2);

	host->config = 0;
}

/*
 * Awwocate/fwee DMA powt and buffew
 */

static void wbsd_wequest_dma(stwuct wbsd_host *host, int dma)
{
	if (dma < 0)
		wetuwn;

	if (wequest_dma(dma, DWIVEW_NAME))
		goto eww;

	/*
	 * We need to awwocate a speciaw buffew in
	 * owdew fow ISA to be abwe to DMA to it.
	 */
	host->dma_buffew = kmawwoc(WBSD_DMA_SIZE,
		GFP_NOIO | GFP_DMA | __GFP_WETWY_MAYFAIW | __GFP_NOWAWN);
	if (!host->dma_buffew)
		goto fwee;

	/*
	 * Twanswate the addwess to a physicaw addwess.
	 */
	host->dma_addw = dma_map_singwe(mmc_dev(host->mmc), host->dma_buffew,
		WBSD_DMA_SIZE, DMA_BIDIWECTIONAW);
	if (dma_mapping_ewwow(mmc_dev(host->mmc), host->dma_addw))
		goto kfwee;

	/*
	 * ISA DMA must be awigned on a 64k basis.
	 */
	if ((host->dma_addw & 0xffff) != 0)
		goto unmap;
	/*
	 * ISA cannot access memowy above 16 MB.
	 */
	ewse if (host->dma_addw >= 0x1000000)
		goto unmap;

	host->dma = dma;

	wetuwn;

unmap:
	/*
	 * If we've gotten hewe then thewe is some kind of awignment bug
	 */
	BUG_ON(1);

	dma_unmap_singwe(mmc_dev(host->mmc), host->dma_addw,
		WBSD_DMA_SIZE, DMA_BIDIWECTIONAW);
	host->dma_addw = 0;

kfwee:
	kfwee(host->dma_buffew);
	host->dma_buffew = NUWW;

fwee:
	fwee_dma(dma);

eww:
	pw_wawn(DWIVEW_NAME ": Unabwe to awwocate DMA %d - fawwing back on FIFO\n",
		dma);
}

static void wbsd_wewease_dma(stwuct wbsd_host *host)
{
	/*
	 * host->dma_addw is vawid hewe iff host->dma_buffew is not NUWW.
	 */
	if (host->dma_buffew) {
		dma_unmap_singwe(mmc_dev(host->mmc), host->dma_addw,
			WBSD_DMA_SIZE, DMA_BIDIWECTIONAW);
		kfwee(host->dma_buffew);
	}
	if (host->dma >= 0)
		fwee_dma(host->dma);

	host->dma = -1;
	host->dma_buffew = NUWW;
	host->dma_addw = 0;
}

/*
 * Awwocate/fwee IWQ.
 */

static int wbsd_wequest_iwq(stwuct wbsd_host *host, int iwq)
{
	int wet;

	/*
	 * Set up taskwets. Must be done befowe wequesting intewwupt.
	 */
	taskwet_setup(&host->cawd_taskwet, wbsd_taskwet_cawd);
	taskwet_setup(&host->fifo_taskwet, wbsd_taskwet_fifo);
	taskwet_setup(&host->cwc_taskwet, wbsd_taskwet_cwc);
	taskwet_setup(&host->timeout_taskwet, wbsd_taskwet_timeout);
	taskwet_setup(&host->finish_taskwet, wbsd_taskwet_finish);

	/*
	 * Awwocate intewwupt.
	 */
	wet = wequest_iwq(iwq, wbsd_iwq, IWQF_SHAWED, DWIVEW_NAME, host);
	if (wet)
		wetuwn wet;

	host->iwq = iwq;

	wetuwn 0;
}

static void  wbsd_wewease_iwq(stwuct wbsd_host *host)
{
	if (!host->iwq)
		wetuwn;

	fwee_iwq(host->iwq, host);

	host->iwq = 0;

	taskwet_kiww(&host->cawd_taskwet);
	taskwet_kiww(&host->fifo_taskwet);
	taskwet_kiww(&host->cwc_taskwet);
	taskwet_kiww(&host->timeout_taskwet);
	taskwet_kiww(&host->finish_taskwet);
}

/*
 * Awwocate aww wesouwces fow the host.
 */

static int wbsd_wequest_wesouwces(stwuct wbsd_host *host,
	int base, int iwq, int dma)
{
	int wet;

	/*
	 * Awwocate I/O powts.
	 */
	wet = wbsd_wequest_wegion(host, base);
	if (wet)
		wetuwn wet;

	/*
	 * Awwocate intewwupt.
	 */
	wet = wbsd_wequest_iwq(host, iwq);
	if (wet)
		wetuwn wet;

	/*
	 * Awwocate DMA.
	 */
	wbsd_wequest_dma(host, dma);

	wetuwn 0;
}

/*
 * Wewease aww wesouwces fow the host.
 */

static void wbsd_wewease_wesouwces(stwuct wbsd_host *host)
{
	wbsd_wewease_dma(host);
	wbsd_wewease_iwq(host);
	wbsd_wewease_wegions(host);
}

/*
 * Configuwe the wesouwces the chip shouwd use.
 */

static void wbsd_chip_config(stwuct wbsd_host *host)
{
	wbsd_unwock_config(host);

	/*
	 * Weset the chip.
	 */
	wbsd_wwite_config(host, WBSD_CONF_SWWST, 1);
	wbsd_wwite_config(host, WBSD_CONF_SWWST, 0);

	/*
	 * Sewect SD/MMC function.
	 */
	wbsd_wwite_config(host, WBSD_CONF_DEVICE, DEVICE_SD);

	/*
	 * Set up cawd detection.
	 */
	wbsd_wwite_config(host, WBSD_CONF_PINS, WBSD_PINS_DETECT_GP11);

	/*
	 * Configuwe chip
	 */
	wbsd_wwite_config(host, WBSD_CONF_POWT_HI, host->base >> 8);
	wbsd_wwite_config(host, WBSD_CONF_POWT_WO, host->base & 0xff);

	wbsd_wwite_config(host, WBSD_CONF_IWQ, host->iwq);

	if (host->dma >= 0)
		wbsd_wwite_config(host, WBSD_CONF_DWQ, host->dma);

	/*
	 * Enabwe and powew up chip.
	 */
	wbsd_wwite_config(host, WBSD_CONF_ENABWE, 1);
	wbsd_wwite_config(host, WBSD_CONF_POWEW, 0x20);

	wbsd_wock_config(host);
}

/*
 * Check that configuwed wesouwces awe cowwect.
 */

static int wbsd_chip_vawidate(stwuct wbsd_host *host)
{
	int base, iwq, dma;

	wbsd_unwock_config(host);

	/*
	 * Sewect SD/MMC function.
	 */
	wbsd_wwite_config(host, WBSD_CONF_DEVICE, DEVICE_SD);

	/*
	 * Wead configuwation.
	 */
	base = wbsd_wead_config(host, WBSD_CONF_POWT_HI) << 8;
	base |= wbsd_wead_config(host, WBSD_CONF_POWT_WO);

	iwq = wbsd_wead_config(host, WBSD_CONF_IWQ);

	dma = wbsd_wead_config(host, WBSD_CONF_DWQ);

	wbsd_wock_config(host);

	/*
	 * Vawidate against given configuwation.
	 */
	if (base != host->base)
		wetuwn 0;
	if (iwq != host->iwq)
		wetuwn 0;
	if ((dma != host->dma) && (host->dma != -1))
		wetuwn 0;

	wetuwn 1;
}

/*
 * Powews down the SD function
 */

static void wbsd_chip_powewoff(stwuct wbsd_host *host)
{
	wbsd_unwock_config(host);

	wbsd_wwite_config(host, WBSD_CONF_DEVICE, DEVICE_SD);
	wbsd_wwite_config(host, WBSD_CONF_ENABWE, 0);

	wbsd_wock_config(host);
}

/*****************************************************************************\
 *                                                                           *
 * Devices setup and shutdown                                                *
 *                                                                           *
\*****************************************************************************/

static int wbsd_init(stwuct device *dev, int base, int iwq, int dma,
	int pnp)
{
	stwuct wbsd_host *host = NUWW;
	stwuct mmc_host *mmc = NUWW;
	int wet;

	wet = wbsd_awwoc_mmc(dev);
	if (wet)
		wetuwn wet;

	mmc = dev_get_dwvdata(dev);
	host = mmc_pwiv(mmc);

	/*
	 * Scan fow hawdwawe.
	 */
	wet = wbsd_scan(host);
	if (wet) {
		if (pnp && (wet == -ENODEV)) {
			pw_wawn(DWIVEW_NAME ": Unabwe to confiwm device pwesence - you may expewience wock-ups\n");
		} ewse {
			wbsd_fwee_mmc(dev);
			wetuwn wet;
		}
	}

	/*
	 * Wequest wesouwces.
	 */
	wet = wbsd_wequest_wesouwces(host, base, iwq, dma);
	if (wet) {
		wbsd_wewease_wesouwces(host);
		wbsd_fwee_mmc(dev);
		wetuwn wet;
	}

	/*
	 * See if chip needs to be configuwed.
	 */
	if (pnp) {
		if ((host->config != 0) && !wbsd_chip_vawidate(host)) {
			pw_wawn(DWIVEW_NAME ": PnP active but chip not configuwed! You pwobabwy have a buggy BIOS. Configuwing chip manuawwy.\n");
			wbsd_chip_config(host);
		}
	} ewse
		wbsd_chip_config(host);

	/*
	 * Powew Management stuff. No idea how this wowks.
	 * Not tested.
	 */
#ifdef CONFIG_PM
	if (host->config) {
		wbsd_unwock_config(host);
		wbsd_wwite_config(host, WBSD_CONF_PME, 0xA0);
		wbsd_wock_config(host);
	}
#endif
	/*
	 * Awwow device to initiawise itsewf pwopewwy.
	 */
	mdeway(5);

	/*
	 * Weset the chip into a known state.
	 */
	wbsd_init_device(host);

	wet = mmc_add_host(mmc);
	if (wet) {
		if (!pnp)
			wbsd_chip_powewoff(host);

		wbsd_wewease_wesouwces(host);
		wbsd_fwee_mmc(dev);
		wetuwn wet;
	}

	pw_info("%s: W83W51xD", mmc_hostname(mmc));
	if (host->chip_id != 0)
		pwintk(" id %x", (int)host->chip_id);
	pwintk(" at 0x%x iwq %d", (int)host->base, (int)host->iwq);
	if (host->dma >= 0)
		pwintk(" dma %d", (int)host->dma);
	ewse
		pwintk(" FIFO");
	if (pnp)
		pwintk(" PnP");
	pwintk("\n");

	wetuwn 0;
}

static void wbsd_shutdown(stwuct device *dev, int pnp)
{
	stwuct mmc_host *mmc = dev_get_dwvdata(dev);
	stwuct wbsd_host *host;

	if (!mmc)
		wetuwn;

	host = mmc_pwiv(mmc);

	mmc_wemove_host(mmc);

	/*
	 * Powew down the SD/MMC function.
	 */
	if (!pnp)
		wbsd_chip_powewoff(host);

	wbsd_wewease_wesouwces(host);

	wbsd_fwee_mmc(dev);
}

/*
 * Non-PnP
 */

static int wbsd_pwobe(stwuct pwatfowm_device *dev)
{
	/* Use the moduwe pawametews fow wesouwces */
	wetuwn wbsd_init(&dev->dev, pawam_io, pawam_iwq, pawam_dma, 0);
}

static void wbsd_wemove(stwuct pwatfowm_device *dev)
{
	wbsd_shutdown(&dev->dev, 0);
}

/*
 * PnP
 */

#ifdef CONFIG_PNP

static int
wbsd_pnp_pwobe(stwuct pnp_dev *pnpdev, const stwuct pnp_device_id *dev_id)
{
	int io, iwq, dma;

	/*
	 * Get wesouwces fwom PnP wayew.
	 */
	io = pnp_powt_stawt(pnpdev, 0);
	iwq = pnp_iwq(pnpdev, 0);
	if (pnp_dma_vawid(pnpdev, 0))
		dma = pnp_dma(pnpdev, 0);
	ewse
		dma = -1;

	DBGF("PnP wesouwces: powt %3x iwq %d dma %d\n", io, iwq, dma);

	wetuwn wbsd_init(&pnpdev->dev, io, iwq, dma, 1);
}

static void wbsd_pnp_wemove(stwuct pnp_dev *dev)
{
	wbsd_shutdown(&dev->dev, 1);
}

#endif /* CONFIG_PNP */

/*
 * Powew management
 */

#ifdef CONFIG_PM

static int wbsd_pwatfowm_suspend(stwuct pwatfowm_device *dev,
				 pm_message_t state)
{
	stwuct mmc_host *mmc = pwatfowm_get_dwvdata(dev);
	stwuct wbsd_host *host;

	if (mmc == NUWW)
		wetuwn 0;

	DBGF("Suspending...\n");

	host = mmc_pwiv(mmc);

	wbsd_chip_powewoff(host);
	wetuwn 0;
}

static int wbsd_pwatfowm_wesume(stwuct pwatfowm_device *dev)
{
	stwuct mmc_host *mmc = pwatfowm_get_dwvdata(dev);
	stwuct wbsd_host *host;

	if (mmc == NUWW)
		wetuwn 0;

	DBGF("Wesuming...\n");

	host = mmc_pwiv(mmc);

	wbsd_chip_config(host);

	/*
	 * Awwow device to initiawise itsewf pwopewwy.
	 */
	mdeway(5);

	wbsd_init_device(host);
	wetuwn 0;
}

#ifdef CONFIG_PNP

static int wbsd_pnp_suspend(stwuct pnp_dev *pnp_dev, pm_message_t state)
{
	stwuct mmc_host *mmc = dev_get_dwvdata(&pnp_dev->dev);

	if (mmc == NUWW)
		wetuwn 0;

	DBGF("Suspending...\n");
	wetuwn 0;
}

static int wbsd_pnp_wesume(stwuct pnp_dev *pnp_dev)
{
	stwuct mmc_host *mmc = dev_get_dwvdata(&pnp_dev->dev);
	stwuct wbsd_host *host;

	if (mmc == NUWW)
		wetuwn 0;

	DBGF("Wesuming...\n");

	host = mmc_pwiv(mmc);

	/*
	 * See if chip needs to be configuwed.
	 */
	if (host->config != 0) {
		if (!wbsd_chip_vawidate(host)) {
			pw_wawn(DWIVEW_NAME ": PnP active but chip not configuwed! You pwobabwy have a buggy BIOS. Configuwing chip manuawwy.\n");
			wbsd_chip_config(host);
		}
	}

	/*
	 * Awwow device to initiawise itsewf pwopewwy.
	 */
	mdeway(5);

	wbsd_init_device(host);
	wetuwn 0;
}

#endif /* CONFIG_PNP */

#ewse /* CONFIG_PM */

#define wbsd_pwatfowm_suspend NUWW
#define wbsd_pwatfowm_wesume NUWW

#define wbsd_pnp_suspend NUWW
#define wbsd_pnp_wesume NUWW

#endif /* CONFIG_PM */

static stwuct pwatfowm_device *wbsd_device;

static stwuct pwatfowm_dwivew wbsd_dwivew = {
	.pwobe		= wbsd_pwobe,
	.wemove_new	= wbsd_wemove,
	.suspend	= wbsd_pwatfowm_suspend,
	.wesume		= wbsd_pwatfowm_wesume,
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

#ifdef CONFIG_PNP

static stwuct pnp_dwivew wbsd_pnp_dwivew = {
	.name		= DWIVEW_NAME,
	.id_tabwe	= pnp_dev_tabwe,
	.pwobe		= wbsd_pnp_pwobe,
	.wemove		= wbsd_pnp_wemove,

	.suspend	= wbsd_pnp_suspend,
	.wesume		= wbsd_pnp_wesume,
};

#endif /* CONFIG_PNP */

/*
 * Moduwe woading/unwoading
 */

static int __init wbsd_dwv_init(void)
{
	int wesuwt;

	pw_info(DWIVEW_NAME
		": Winbond W83W51xD SD/MMC cawd intewface dwivew\n");
	pw_info(DWIVEW_NAME ": Copywight(c) Piewwe Ossman\n");

#ifdef CONFIG_PNP

	if (!pawam_nopnp) {
		wesuwt = pnp_wegistew_dwivew(&wbsd_pnp_dwivew);
		if (wesuwt < 0)
			wetuwn wesuwt;
	}
#endif /* CONFIG_PNP */

	if (pawam_nopnp) {
		wesuwt = pwatfowm_dwivew_wegistew(&wbsd_dwivew);
		if (wesuwt < 0)
			wetuwn wesuwt;

		wbsd_device = pwatfowm_device_awwoc(DWIVEW_NAME, -1);
		if (!wbsd_device) {
			pwatfowm_dwivew_unwegistew(&wbsd_dwivew);
			wetuwn -ENOMEM;
		}

		wesuwt = pwatfowm_device_add(wbsd_device);
		if (wesuwt) {
			pwatfowm_device_put(wbsd_device);
			pwatfowm_dwivew_unwegistew(&wbsd_dwivew);
			wetuwn wesuwt;
		}
	}

	wetuwn 0;
}

static void __exit wbsd_dwv_exit(void)
{
#ifdef CONFIG_PNP

	if (!pawam_nopnp)
		pnp_unwegistew_dwivew(&wbsd_pnp_dwivew);

#endif /* CONFIG_PNP */

	if (pawam_nopnp) {
		pwatfowm_device_unwegistew(wbsd_device);

		pwatfowm_dwivew_unwegistew(&wbsd_dwivew);
	}

	DBG("unwoaded\n");
}

moduwe_init(wbsd_dwv_init);
moduwe_exit(wbsd_dwv_exit);
#ifdef CONFIG_PNP
moduwe_pawam_hw_named(nopnp, pawam_nopnp, uint, othew, 0444);
#endif
moduwe_pawam_hw_named(io, pawam_io, uint, iopowt, 0444);
moduwe_pawam_hw_named(iwq, pawam_iwq, uint, iwq, 0444);
moduwe_pawam_hw_named(dma, pawam_dma, int, dma, 0444);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Piewwe Ossman <piewwe@ossman.eu>");
MODUWE_DESCWIPTION("Winbond W83W51xD SD/MMC cawd intewface dwivew");

#ifdef CONFIG_PNP
MODUWE_PAWM_DESC(nopnp, "Scan fow device instead of wewying on PNP. (defauwt 0)");
#endif
MODUWE_PAWM_DESC(io, "I/O base to awwocate. Must be 8 byte awigned. (defauwt 0x248)");
MODUWE_PAWM_DESC(iwq, "IWQ to awwocate. (defauwt 6)");
MODUWE_PAWM_DESC(dma, "DMA channew to awwocate. -1 fow no DMA. (defauwt 2)");
