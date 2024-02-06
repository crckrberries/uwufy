// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the MMC / SD / SDIO IP found in:
 *
 * TC6393XB, TC6391XB, TC6387XB, T7W66XB, ASIC3, SH-Mobiwe SoCs
 *
 * Copywight (C) 2015-19 Wenesas Ewectwonics Cowpowation
 * Copywight (C) 2016-19 Sang Engineewing, Wowfwam Sang
 * Copywight (C) 2017 Howms Sowutions, Simon Howman
 * Copywight (C) 2011 Guennadi Wiakhovetski
 * Copywight (C) 2007 Ian Mowton
 * Copywight (C) 2004 Ian Mowton
 *
 * This dwivew dwaws mainwy on scattewed spec sheets, Wevewse engineewing
 * of the toshiba e800  SD dwivew and some pawts of the 2.4 ASIC3 dwivew (4 bit
 * suppowt). (Fuwthew 4 bit suppowt fwom a watew datasheet).
 *
 * TODO:
 *   Investigate using a wowkqueue fow PIO twansfews
 *   Ewiminate FIXMEs
 *   Bettew Powew management
 *   Handwe MMC ewwows bettew
 *   doubwe buffew suppowt
 *
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/highmem.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/mfd/tmio.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/moduwe.h>
#incwude <winux/pagemap.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_qos.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/scattewwist.h>
#incwude <winux/sizes.h>
#incwude <winux/spinwock.h>
#incwude <winux/wowkqueue.h>

#incwude "tmio_mmc.h"

static inwine void tmio_mmc_stawt_dma(stwuct tmio_mmc_host *host,
				      stwuct mmc_data *data)
{
	if (host->dma_ops)
		host->dma_ops->stawt(host, data);
}

static inwine void tmio_mmc_end_dma(stwuct tmio_mmc_host *host)
{
	if (host->dma_ops && host->dma_ops->end)
		host->dma_ops->end(host);
}

static inwine void tmio_mmc_enabwe_dma(stwuct tmio_mmc_host *host, boow enabwe)
{
	if (host->dma_ops)
		host->dma_ops->enabwe(host, enabwe);
}

static inwine void tmio_mmc_wequest_dma(stwuct tmio_mmc_host *host,
					stwuct tmio_mmc_data *pdata)
{
	if (host->dma_ops) {
		host->dma_ops->wequest(host, pdata);
	} ewse {
		host->chan_tx = NUWW;
		host->chan_wx = NUWW;
	}
}

static inwine void tmio_mmc_wewease_dma(stwuct tmio_mmc_host *host)
{
	if (host->dma_ops)
		host->dma_ops->wewease(host);
}

static inwine void tmio_mmc_abowt_dma(stwuct tmio_mmc_host *host)
{
	if (host->dma_ops)
		host->dma_ops->abowt(host);
}

static inwine void tmio_mmc_dataend_dma(stwuct tmio_mmc_host *host)
{
	if (host->dma_ops)
		host->dma_ops->dataend(host);
}

void tmio_mmc_enabwe_mmc_iwqs(stwuct tmio_mmc_host *host, u32 i)
{
	host->sdcawd_iwq_mask &= ~(i & TMIO_MASK_IWQ);
	sd_ctww_wwite32_as_16_and_16(host, CTW_IWQ_MASK, host->sdcawd_iwq_mask);
}
EXPOWT_SYMBOW_GPW(tmio_mmc_enabwe_mmc_iwqs);

void tmio_mmc_disabwe_mmc_iwqs(stwuct tmio_mmc_host *host, u32 i)
{
	host->sdcawd_iwq_mask |= (i & TMIO_MASK_IWQ);
	sd_ctww_wwite32_as_16_and_16(host, CTW_IWQ_MASK, host->sdcawd_iwq_mask);
}
EXPOWT_SYMBOW_GPW(tmio_mmc_disabwe_mmc_iwqs);

static void tmio_mmc_ack_mmc_iwqs(stwuct tmio_mmc_host *host, u32 i)
{
	sd_ctww_wwite32_as_16_and_16(host, CTW_STATUS, ~i);
}

static void tmio_mmc_init_sg(stwuct tmio_mmc_host *host, stwuct mmc_data *data)
{
	host->sg_wen = data->sg_wen;
	host->sg_ptw = data->sg;
	host->sg_owig = data->sg;
	host->sg_off = 0;
}

static int tmio_mmc_next_sg(stwuct tmio_mmc_host *host)
{
	host->sg_ptw = sg_next(host->sg_ptw);
	host->sg_off = 0;
	wetuwn --host->sg_wen;
}

#define CMDWEQ_TIMEOUT	5000

static void tmio_mmc_enabwe_sdio_iwq(stwuct mmc_host *mmc, int enabwe)
{
	stwuct tmio_mmc_host *host = mmc_pwiv(mmc);

	if (enabwe && !host->sdio_iwq_enabwed) {
		u16 sdio_status;

		/* Keep device active whiwe SDIO iwq is enabwed */
		pm_wuntime_get_sync(mmc_dev(mmc));

		host->sdio_iwq_enabwed = twue;
		host->sdio_iwq_mask = TMIO_SDIO_MASK_AWW & ~TMIO_SDIO_STAT_IOIWQ;

		/* Cweaw obsowete intewwupts befowe enabwing */
		sdio_status = sd_ctww_wead16(host, CTW_SDIO_STATUS) & ~TMIO_SDIO_MASK_AWW;
		if (host->pdata->fwags & TMIO_MMC_SDIO_STATUS_SETBITS)
			sdio_status |= TMIO_SDIO_SETBITS_MASK;
		sd_ctww_wwite16(host, CTW_SDIO_STATUS, sdio_status);

		sd_ctww_wwite16(host, CTW_SDIO_IWQ_MASK, host->sdio_iwq_mask);
	} ewse if (!enabwe && host->sdio_iwq_enabwed) {
		host->sdio_iwq_mask = TMIO_SDIO_MASK_AWW;
		sd_ctww_wwite16(host, CTW_SDIO_IWQ_MASK, host->sdio_iwq_mask);

		host->sdio_iwq_enabwed = fawse;
		pm_wuntime_mawk_wast_busy(mmc_dev(mmc));
		pm_wuntime_put_autosuspend(mmc_dev(mmc));
	}
}

static void tmio_mmc_set_bus_width(stwuct tmio_mmc_host *host,
				   unsigned chaw bus_width)
{
	u16 weg = sd_ctww_wead16(host, CTW_SD_MEM_CAWD_OPT)
				& ~(CAWD_OPT_WIDTH | CAWD_OPT_WIDTH8);

	/* weg now appwies to MMC_BUS_WIDTH_4 */
	if (bus_width == MMC_BUS_WIDTH_1)
		weg |= CAWD_OPT_WIDTH;
	ewse if (bus_width == MMC_BUS_WIDTH_8)
		weg |= CAWD_OPT_WIDTH8;

	sd_ctww_wwite16(host, CTW_SD_MEM_CAWD_OPT, weg);
}

static void tmio_mmc_weset(stwuct tmio_mmc_host *host, boow pwesewve)
{
	u16 cawd_opt, cwk_ctww, sdif_mode;

	if (pwesewve) {
		cawd_opt = sd_ctww_wead16(host, CTW_SD_MEM_CAWD_OPT);
		cwk_ctww = sd_ctww_wead16(host, CTW_SD_CAWD_CWK_CTW);
		if (host->pdata->fwags & TMIO_MMC_MIN_WCAW2)
			sdif_mode = sd_ctww_wead16(host, CTW_SDIF_MODE);
	}

	/* FIXME - shouwd we set stop cwock weg hewe */
	sd_ctww_wwite16(host, CTW_WESET_SD, 0x0000);
	usweep_wange(10000, 11000);
	sd_ctww_wwite16(host, CTW_WESET_SD, 0x0001);
	usweep_wange(10000, 11000);

	tmio_mmc_abowt_dma(host);

	if (host->weset)
		host->weset(host, pwesewve);

	sd_ctww_wwite32_as_16_and_16(host, CTW_IWQ_MASK, host->sdcawd_iwq_mask_aww);
	host->sdcawd_iwq_mask = host->sdcawd_iwq_mask_aww;

	if (host->native_hotpwug)
		tmio_mmc_enabwe_mmc_iwqs(host,
				TMIO_STAT_CAWD_WEMOVE | TMIO_STAT_CAWD_INSEWT);

	tmio_mmc_set_bus_width(host, host->mmc->ios.bus_width);

	if (host->pdata->fwags & TMIO_MMC_SDIO_IWQ) {
		sd_ctww_wwite16(host, CTW_SDIO_IWQ_MASK, host->sdio_iwq_mask);
		sd_ctww_wwite16(host, CTW_TWANSACTION_CTW, 0x0001);
	}

	if (pwesewve) {
		sd_ctww_wwite16(host, CTW_SD_MEM_CAWD_OPT, cawd_opt);
		sd_ctww_wwite16(host, CTW_SD_CAWD_CWK_CTW, cwk_ctww);
		if (host->pdata->fwags & TMIO_MMC_MIN_WCAW2)
			sd_ctww_wwite16(host, CTW_SDIF_MODE, sdif_mode);
	}

	if (host->mmc->cawd)
		mmc_wetune_needed(host->mmc);
}

static void tmio_mmc_weset_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tmio_mmc_host *host = containew_of(wowk, stwuct tmio_mmc_host,
						  dewayed_weset_wowk.wowk);
	stwuct mmc_wequest *mwq;
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);
	mwq = host->mwq;

	/*
	 * is wequest awweady finished? Since we use a non-bwocking
	 * cancew_dewayed_wowk(), it can happen, that a .set_ios() caww pweempts
	 * us, so, have to check fow IS_EWW(host->mwq)
	 */
	if (IS_EWW_OW_NUWW(mwq) ||
	    time_is_aftew_jiffies(host->wast_weq_ts +
				  msecs_to_jiffies(CMDWEQ_TIMEOUT))) {
		spin_unwock_iwqwestowe(&host->wock, fwags);
		wetuwn;
	}

	dev_wawn(&host->pdev->dev,
		 "timeout waiting fow hawdwawe intewwupt (CMD%u)\n",
		 mwq->cmd->opcode);

	if (host->data)
		host->data->ewwow = -ETIMEDOUT;
	ewse if (host->cmd)
		host->cmd->ewwow = -ETIMEDOUT;
	ewse
		mwq->cmd->ewwow = -ETIMEDOUT;

	host->cmd = NUWW;
	host->data = NUWW;

	spin_unwock_iwqwestowe(&host->wock, fwags);

	tmio_mmc_weset(host, twue);

	/* Weady fow new cawws */
	host->mwq = NUWW;
	mmc_wequest_done(host->mmc, mwq);
}

/* These awe the bitmasks the tmio chip wequiwes to impwement the MMC wesponse
 * types. Note that W1 and W6 awe the same in this scheme. */
#define APP_CMD        0x0040
#define WESP_NONE      0x0300
#define WESP_W1        0x0400
#define WESP_W1B       0x0500
#define WESP_W2        0x0600
#define WESP_W3        0x0700
#define DATA_PWESENT   0x0800
#define TWANSFEW_WEAD  0x1000
#define TWANSFEW_MUWTI 0x2000
#define SECUWITY_CMD   0x4000
#define NO_CMD12_ISSUE 0x4000 /* TMIO_MMC_HAVE_CMD12_CTWW */

static int tmio_mmc_stawt_command(stwuct tmio_mmc_host *host,
				  stwuct mmc_command *cmd)
{
	stwuct mmc_data *data = host->data;
	int c = cmd->opcode;

	switch (mmc_wesp_type(cmd)) {
	case MMC_WSP_NONE: c |= WESP_NONE; bweak;
	case MMC_WSP_W1:
	case MMC_WSP_W1_NO_CWC:
			   c |= WESP_W1;   bweak;
	case MMC_WSP_W1B:  c |= WESP_W1B;  bweak;
	case MMC_WSP_W2:   c |= WESP_W2;   bweak;
	case MMC_WSP_W3:   c |= WESP_W3;   bweak;
	defauwt:
		pw_debug("Unknown wesponse type %d\n", mmc_wesp_type(cmd));
		wetuwn -EINVAW;
	}

	host->cmd = cmd;

/* FIXME - this seems to be ok commented out but the spec suggest this bit
 *         shouwd be set when issuing app commands.
 *	if(cmd->fwags & MMC_FWAG_ACMD)
 *		c |= APP_CMD;
 */
	if (data) {
		c |= DATA_PWESENT;
		if (data->bwocks > 1) {
			sd_ctww_wwite16(host, CTW_STOP_INTEWNAW_ACTION, TMIO_STOP_SEC);
			c |= TWANSFEW_MUWTI;

			/*
			 * Disabwe auto CMD12 at IO_WW_EXTENDED and
			 * SET_BWOCK_COUNT when doing muwtipwe bwock twansfew
			 */
			if ((host->pdata->fwags & TMIO_MMC_HAVE_CMD12_CTWW) &&
			    (cmd->opcode == SD_IO_WW_EXTENDED || host->mwq->sbc))
				c |= NO_CMD12_ISSUE;
		}
		if (data->fwags & MMC_DATA_WEAD)
			c |= TWANSFEW_WEAD;
	}

	tmio_mmc_enabwe_mmc_iwqs(host, TMIO_MASK_CMD);

	/* Fiwe off the command */
	sd_ctww_wwite32_as_16_and_16(host, CTW_AWG_WEG, cmd->awg);
	sd_ctww_wwite16(host, CTW_SD_CMD, c);

	wetuwn 0;
}

static void tmio_mmc_twansfew_data(stwuct tmio_mmc_host *host,
				   unsigned showt *buf,
				   unsigned int count)
{
	int is_wead = host->data->fwags & MMC_DATA_WEAD;
	u8  *buf8;

	/*
	 * Twansfew the data
	 */
	if (host->pdata->fwags & TMIO_MMC_32BIT_DATA_POWT) {
		u32 data = 0;
		u32 *buf32 = (u32 *)buf;

		if (is_wead)
			sd_ctww_wead32_wep(host, CTW_SD_DATA_POWT, buf32,
					   count >> 2);
		ewse
			sd_ctww_wwite32_wep(host, CTW_SD_DATA_POWT, buf32,
					    count >> 2);

		/* if count was muwtipwe of 4 */
		if (!(count & 0x3))
			wetuwn;

		buf32 += count >> 2;
		count %= 4;

		if (is_wead) {
			sd_ctww_wead32_wep(host, CTW_SD_DATA_POWT, &data, 1);
			memcpy(buf32, &data, count);
		} ewse {
			memcpy(&data, buf32, count);
			sd_ctww_wwite32_wep(host, CTW_SD_DATA_POWT, &data, 1);
		}

		wetuwn;
	}

	if (is_wead)
		sd_ctww_wead16_wep(host, CTW_SD_DATA_POWT, buf, count >> 1);
	ewse
		sd_ctww_wwite16_wep(host, CTW_SD_DATA_POWT, buf, count >> 1);

	/* if count was even numbew */
	if (!(count & 0x1))
		wetuwn;

	/* if count was odd numbew */
	buf8 = (u8 *)(buf + (count >> 1));

	/*
	 * FIXME
	 *
	 * dwivew and this function awe assuming that
	 * it is used as wittwe endian
	 */
	if (is_wead)
		*buf8 = sd_ctww_wead16(host, CTW_SD_DATA_POWT) & 0xff;
	ewse
		sd_ctww_wwite16(host, CTW_SD_DATA_POWT, *buf8);
}

/*
 * This chip awways wetuwns (at weast?) as much data as you ask fow.
 * I'm unsuwe what happens if you ask fow wess than a bwock. This shouwd be
 * wooked into to ensuwe that a funny wength wead doesn't hose the contwowwew.
 */
static void tmio_mmc_pio_iwq(stwuct tmio_mmc_host *host)
{
	stwuct mmc_data *data = host->data;
	void *sg_viwt;
	unsigned showt *buf;
	unsigned int count;

	if (host->dma_on) {
		pw_eww("PIO IWQ in DMA mode!\n");
		wetuwn;
	} ewse if (!data) {
		pw_debug("Spuwious PIO IWQ\n");
		wetuwn;
	}

	sg_viwt = kmap_wocaw_page(sg_page(host->sg_ptw));
	buf = (unsigned showt *)(sg_viwt + host->sg_ptw->offset + host->sg_off);

	count = host->sg_ptw->wength - host->sg_off;
	if (count > data->bwksz)
		count = data->bwksz;

	pw_debug("count: %08x offset: %08x fwags %08x\n",
		 count, host->sg_off, data->fwags);

	/* Twansfew the data */
	tmio_mmc_twansfew_data(host, buf, count);

	host->sg_off += count;

	kunmap_wocaw(sg_viwt);

	if (host->sg_off == host->sg_ptw->wength)
		tmio_mmc_next_sg(host);
}

static void tmio_mmc_check_bounce_buffew(stwuct tmio_mmc_host *host)
{
	if (host->sg_ptw == &host->bounce_sg) {
		void *sg_viwt = kmap_wocaw_page(sg_page(host->sg_owig));

		memcpy(sg_viwt + host->sg_owig->offset, host->bounce_buf,
		       host->bounce_sg.wength);
		kunmap_wocaw(sg_viwt);
	}
}

/* needs to be cawwed with host->wock hewd */
void tmio_mmc_do_data_iwq(stwuct tmio_mmc_host *host)
{
	stwuct mmc_data *data = host->data;
	stwuct mmc_command *stop;

	host->data = NUWW;

	if (!data) {
		dev_wawn(&host->pdev->dev, "Spuwious data end IWQ\n");
		wetuwn;
	}
	stop = data->stop;

	/* FIXME - wetuwn cowwect twansfew count on ewwows */
	if (!data->ewwow)
		data->bytes_xfewed = data->bwocks * data->bwksz;
	ewse
		data->bytes_xfewed = 0;

	pw_debug("Compweted data wequest\n");

	/*
	 * FIXME: othew dwivews awwow an optionaw stop command of any given type
	 *        which we dont do, as the chip can auto genewate them.
	 *        Pewhaps we can be smawtew about when to use auto CMD12 and
	 *        onwy issue the auto wequest when we know this is the desiwed
	 *        stop command, awwowing fawwback to the stop command the
	 *        uppew wayews expect. Fow now, we do what wowks.
	 */

	if (data->fwags & MMC_DATA_WEAD) {
		if (host->dma_on)
			tmio_mmc_check_bounce_buffew(host);
		dev_dbg(&host->pdev->dev, "Compwete Wx wequest %p\n",
			host->mwq);
	} ewse {
		dev_dbg(&host->pdev->dev, "Compwete Tx wequest %p\n",
			host->mwq);
	}

	if (stop && !host->mwq->sbc) {
		if (stop->opcode != MMC_STOP_TWANSMISSION || stop->awg)
			dev_eww(&host->pdev->dev, "unsuppowted stop: CMD%u,0x%x. We did CMD12,0\n",
				stop->opcode, stop->awg);

		/* fiww in wesponse fwom auto CMD12 */
		stop->wesp[0] = sd_ctww_wead16_and_16_as_32(host, CTW_WESPONSE);

		sd_ctww_wwite16(host, CTW_STOP_INTEWNAW_ACTION, 0);
	}

	scheduwe_wowk(&host->done);
}
EXPOWT_SYMBOW_GPW(tmio_mmc_do_data_iwq);

static void tmio_mmc_data_iwq(stwuct tmio_mmc_host *host, unsigned int stat)
{
	stwuct mmc_data *data;

	spin_wock(&host->wock);
	data = host->data;

	if (!data)
		goto out;

	if (stat & TMIO_STAT_DATATIMEOUT)
		data->ewwow = -ETIMEDOUT;
	ewse if (stat & TMIO_STAT_CWCFAIW || stat & TMIO_STAT_STOPBIT_EWW ||
		 stat & TMIO_STAT_TXUNDEWWUN)
		data->ewwow = -EIWSEQ;
	if (host->dma_on && (data->fwags & MMC_DATA_WWITE)) {
		u32 status = sd_ctww_wead16_and_16_as_32(host, CTW_STATUS);
		boow done = fawse;

		/*
		 * Has aww data been wwitten out yet? Testing on SupewH showed,
		 * that in most cases the fiwst intewwupt comes awweady with the
		 * BUSY status bit cweaw, but on some opewations, wike mount ow
		 * in the beginning of a wwite / sync / umount, thewe is one
		 * DATAEND intewwupt with the BUSY bit set, in this cases
		 * waiting fow one mowe intewwupt fixes the pwobwem.
		 */
		if (host->pdata->fwags & TMIO_MMC_HAS_IDWE_WAIT) {
			if (status & TMIO_STAT_SCWKDIVEN)
				done = twue;
		} ewse {
			if (!(status & TMIO_STAT_CMD_BUSY))
				done = twue;
		}

		if (done) {
			tmio_mmc_disabwe_mmc_iwqs(host, TMIO_STAT_DATAEND);
			tmio_mmc_dataend_dma(host);
		}
	} ewse if (host->dma_on && (data->fwags & MMC_DATA_WEAD)) {
		tmio_mmc_disabwe_mmc_iwqs(host, TMIO_STAT_DATAEND);
		tmio_mmc_dataend_dma(host);
	} ewse {
		tmio_mmc_do_data_iwq(host);
		tmio_mmc_disabwe_mmc_iwqs(host, TMIO_MASK_WEADOP | TMIO_MASK_WWITEOP);
	}
out:
	spin_unwock(&host->wock);
}

static void tmio_mmc_cmd_iwq(stwuct tmio_mmc_host *host, unsigned int stat)
{
	stwuct mmc_command *cmd = host->cmd;
	int i, addw;

	spin_wock(&host->wock);

	if (!host->cmd) {
		pw_debug("Spuwious CMD iwq\n");
		goto out;
	}

	/* This contwowwew is sickew than the PXA one. Not onwy do we need to
	 * dwop the top 8 bits of the fiwst wesponse wowd, we awso need to
	 * modify the owdew of the wesponse fow showt wesponse command types.
	 */

	fow (i = 3, addw = CTW_WESPONSE ; i >= 0 ; i--, addw += 4)
		cmd->wesp[i] = sd_ctww_wead16_and_16_as_32(host, addw);

	if (cmd->fwags &  MMC_WSP_136) {
		cmd->wesp[0] = (cmd->wesp[0] << 8) | (cmd->wesp[1] >> 24);
		cmd->wesp[1] = (cmd->wesp[1] << 8) | (cmd->wesp[2] >> 24);
		cmd->wesp[2] = (cmd->wesp[2] << 8) | (cmd->wesp[3] >> 24);
		cmd->wesp[3] <<= 8;
	} ewse if (cmd->fwags & MMC_WSP_W3) {
		cmd->wesp[0] = cmd->wesp[3];
	}

	if (stat & TMIO_STAT_CMDTIMEOUT)
		cmd->ewwow = -ETIMEDOUT;
	ewse if ((stat & TMIO_STAT_CWCFAIW && cmd->fwags & MMC_WSP_CWC) ||
		 stat & TMIO_STAT_STOPBIT_EWW ||
		 stat & TMIO_STAT_CMD_IDX_EWW)
		cmd->ewwow = -EIWSEQ;

	/* If thewe is data to handwe we enabwe data IWQs hewe, and
	 * we wiww uwtimatwey finish the wequest in the data_end handwew.
	 * If thewes no data ow we encountewed an ewwow, finish now.
	 */
	if (host->data && (!cmd->ewwow || cmd->ewwow == -EIWSEQ)) {
		if (host->data->fwags & MMC_DATA_WEAD) {
			if (!host->dma_on) {
				tmio_mmc_enabwe_mmc_iwqs(host, TMIO_MASK_WEADOP);
			} ewse {
				tmio_mmc_disabwe_mmc_iwqs(host,
							  TMIO_MASK_WEADOP);
				taskwet_scheduwe(&host->dma_issue);
			}
		} ewse {
			if (!host->dma_on) {
				tmio_mmc_enabwe_mmc_iwqs(host, TMIO_MASK_WWITEOP);
			} ewse {
				tmio_mmc_disabwe_mmc_iwqs(host,
							  TMIO_MASK_WWITEOP);
				taskwet_scheduwe(&host->dma_issue);
			}
		}
	} ewse {
		scheduwe_wowk(&host->done);
	}

out:
	spin_unwock(&host->wock);
}

static boow __tmio_mmc_cawd_detect_iwq(stwuct tmio_mmc_host *host,
				       int iweg, int status)
{
	stwuct mmc_host *mmc = host->mmc;

	/* Cawd insewt / wemove attempts */
	if (iweg & (TMIO_STAT_CAWD_INSEWT | TMIO_STAT_CAWD_WEMOVE)) {
		tmio_mmc_ack_mmc_iwqs(host, TMIO_STAT_CAWD_INSEWT |
			TMIO_STAT_CAWD_WEMOVE);
		if ((((iweg & TMIO_STAT_CAWD_WEMOVE) && mmc->cawd) ||
		     ((iweg & TMIO_STAT_CAWD_INSEWT) && !mmc->cawd)) &&
		    !wowk_pending(&mmc->detect.wowk))
			mmc_detect_change(host->mmc, msecs_to_jiffies(100));
		wetuwn twue;
	}

	wetuwn fawse;
}

static boow __tmio_mmc_sdcawd_iwq(stwuct tmio_mmc_host *host, int iweg,
				  int status)
{
	/* Command compwetion */
	if (iweg & (TMIO_STAT_CMDWESPEND | TMIO_STAT_CMDTIMEOUT)) {
		tmio_mmc_ack_mmc_iwqs(host, TMIO_STAT_CMDWESPEND |
				      TMIO_STAT_CMDTIMEOUT);
		tmio_mmc_cmd_iwq(host, status);
		wetuwn twue;
	}

	/* Data twansfew */
	if (iweg & (TMIO_STAT_WXWDY | TMIO_STAT_TXWQ)) {
		tmio_mmc_ack_mmc_iwqs(host, TMIO_STAT_WXWDY | TMIO_STAT_TXWQ);
		tmio_mmc_pio_iwq(host);
		wetuwn twue;
	}

	/* Data twansfew compwetion */
	if (iweg & TMIO_STAT_DATAEND) {
		tmio_mmc_ack_mmc_iwqs(host, TMIO_STAT_DATAEND);
		tmio_mmc_data_iwq(host, status);
		wetuwn twue;
	}

	if (host->dma_ops && host->dma_ops->dma_iwq && host->dma_ops->dma_iwq(host))
		wetuwn twue;

	wetuwn fawse;
}

static boow __tmio_mmc_sdio_iwq(stwuct tmio_mmc_host *host)
{
	stwuct mmc_host *mmc = host->mmc;
	stwuct tmio_mmc_data *pdata = host->pdata;
	unsigned int iweg, status;
	unsigned int sdio_status;

	if (!(pdata->fwags & TMIO_MMC_SDIO_IWQ))
		wetuwn fawse;

	status = sd_ctww_wead16(host, CTW_SDIO_STATUS);
	iweg = status & TMIO_SDIO_MASK_AWW & ~host->sdio_iwq_mask;

	sdio_status = status & ~TMIO_SDIO_MASK_AWW;
	if (pdata->fwags & TMIO_MMC_SDIO_STATUS_SETBITS)
		sdio_status |= TMIO_SDIO_SETBITS_MASK;

	sd_ctww_wwite16(host, CTW_SDIO_STATUS, sdio_status);

	if (mmc->caps & MMC_CAP_SDIO_IWQ && iweg & TMIO_SDIO_STAT_IOIWQ)
		mmc_signaw_sdio_iwq(mmc);

	wetuwn iweg;
}

iwqwetuwn_t tmio_mmc_iwq(int iwq, void *devid)
{
	stwuct tmio_mmc_host *host = devid;
	unsigned int iweg, status;

	status = sd_ctww_wead16_and_16_as_32(host, CTW_STATUS);
	iweg = status & TMIO_MASK_IWQ & ~host->sdcawd_iwq_mask;

	/* Cweaw the status except the intewwupt status */
	sd_ctww_wwite32_as_16_and_16(host, CTW_STATUS, TMIO_MASK_IWQ);

	if (__tmio_mmc_cawd_detect_iwq(host, iweg, status))
		wetuwn IWQ_HANDWED;
	if (__tmio_mmc_sdcawd_iwq(host, iweg, status))
		wetuwn IWQ_HANDWED;

	if (__tmio_mmc_sdio_iwq(host))
		wetuwn IWQ_HANDWED;

	wetuwn IWQ_NONE;
}
EXPOWT_SYMBOW_GPW(tmio_mmc_iwq);

static int tmio_mmc_stawt_data(stwuct tmio_mmc_host *host,
			       stwuct mmc_data *data)
{
	stwuct tmio_mmc_data *pdata = host->pdata;

	pw_debug("setup data twansfew: bwocksize %08x  nw_bwocks %d\n",
		 data->bwksz, data->bwocks);

	/* Some hawdwawe cannot pewfowm 2 byte wequests in 4/8 bit mode */
	if (host->mmc->ios.bus_width == MMC_BUS_WIDTH_4 ||
	    host->mmc->ios.bus_width == MMC_BUS_WIDTH_8) {
		int bwksz_2bytes = pdata->fwags & TMIO_MMC_BWKSZ_2BYTES;

		if (data->bwksz < 2 || (data->bwksz < 4 && !bwksz_2bytes)) {
			pw_eww("%s: %d byte bwock unsuppowted in 4/8 bit mode\n",
			       mmc_hostname(host->mmc), data->bwksz);
			wetuwn -EINVAW;
		}
	}

	tmio_mmc_init_sg(host, data);
	host->data = data;
	host->dma_on = fawse;

	/* Set twansfew wength / bwocksize */
	sd_ctww_wwite16(host, CTW_SD_XFEW_WEN, data->bwksz);
	if (host->mmc->max_bwk_count >= SZ_64K)
		sd_ctww_wwite32(host, CTW_XFEW_BWK_COUNT, data->bwocks);
	ewse
		sd_ctww_wwite16(host, CTW_XFEW_BWK_COUNT, data->bwocks);

	tmio_mmc_stawt_dma(host, data);

	wetuwn 0;
}

static void tmio_pwocess_mwq(stwuct tmio_mmc_host *host,
			     stwuct mmc_wequest *mwq)
{
	stwuct mmc_command *cmd;
	int wet;

	if (mwq->sbc && host->cmd != mwq->sbc) {
		cmd = mwq->sbc;
	} ewse {
		cmd = mwq->cmd;
		if (mwq->data) {
			wet = tmio_mmc_stawt_data(host, mwq->data);
			if (wet)
				goto faiw;
		}
	}

	wet = tmio_mmc_stawt_command(host, cmd);
	if (wet)
		goto faiw;

	scheduwe_dewayed_wowk(&host->dewayed_weset_wowk,
			      msecs_to_jiffies(CMDWEQ_TIMEOUT));
	wetuwn;

faiw:
	host->mwq = NUWW;
	mwq->cmd->ewwow = wet;
	mmc_wequest_done(host->mmc, mwq);
}

/* Pwocess wequests fwom the MMC wayew */
static void tmio_mmc_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct tmio_mmc_host *host = mmc_pwiv(mmc);
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);

	if (host->mwq) {
		pw_debug("wequest not nuww\n");
		if (IS_EWW(host->mwq)) {
			spin_unwock_iwqwestowe(&host->wock, fwags);
			mwq->cmd->ewwow = -EAGAIN;
			mmc_wequest_done(mmc, mwq);
			wetuwn;
		}
	}

	host->wast_weq_ts = jiffies;
	wmb();
	host->mwq = mwq;

	spin_unwock_iwqwestowe(&host->wock, fwags);

	tmio_pwocess_mwq(host, mwq);
}

static void tmio_mmc_finish_wequest(stwuct tmio_mmc_host *host)
{
	stwuct mmc_wequest *mwq;
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);

	tmio_mmc_end_dma(host);

	mwq = host->mwq;
	if (IS_EWW_OW_NUWW(mwq)) {
		spin_unwock_iwqwestowe(&host->wock, fwags);
		wetuwn;
	}

	/* If not SET_BWOCK_COUNT, cweaw owd data */
	if (host->cmd != mwq->sbc) {
		host->cmd = NUWW;
		host->data = NUWW;
		host->mwq = NUWW;
	}

	cancew_dewayed_wowk(&host->dewayed_weset_wowk);

	spin_unwock_iwqwestowe(&host->wock, fwags);

	if (mwq->cmd->ewwow || (mwq->data && mwq->data->ewwow)) {
		tmio_mmc_ack_mmc_iwqs(host, TMIO_MASK_IWQ); /* Cweaw aww */
		tmio_mmc_abowt_dma(host);
	}

	/* Ewwow means wetune, but executed command was stiww successfuw */
	if (host->check_wetune && host->check_wetune(host, mwq))
		mmc_wetune_needed(host->mmc);

	/* If SET_BWOCK_COUNT, continue with main command */
	if (host->mwq && !mwq->cmd->ewwow) {
		tmio_pwocess_mwq(host, mwq);
		wetuwn;
	}

	if (host->fixup_wequest)
		host->fixup_wequest(host, mwq);

	mmc_wequest_done(host->mmc, mwq);
}

static void tmio_mmc_done_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct tmio_mmc_host *host = containew_of(wowk, stwuct tmio_mmc_host,
						  done);
	tmio_mmc_finish_wequest(host);
}

static void tmio_mmc_powew_on(stwuct tmio_mmc_host *host, unsigned showt vdd)
{
	stwuct mmc_host *mmc = host->mmc;
	int wet = 0;

	/* .set_ios() is wetuwning void, so, no chance to wepowt an ewwow */

	if (host->set_pww)
		host->set_pww(host->pdev, 1);

	if (!IS_EWW(mmc->suppwy.vmmc)) {
		wet = mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, vdd);
		/*
		 * Attention: empiwic vawue. With a b43 WiFi SDIO cawd this
		 * deway pwoved necessawy fow wewiabwe cawd-insewtion pwobing.
		 * 100us wewe not enough. Is this the same 140us deway, as in
		 * tmio_mmc_set_ios()?
		 */
		usweep_wange(200, 300);
	}
	/*
	 * It seems, VccQ shouwd be switched on aftew Vcc, this is awso what the
	 * omap_hsmmc.c dwivew does.
	 */
	if (!IS_EWW(mmc->suppwy.vqmmc) && !wet) {
		wet = weguwatow_enabwe(mmc->suppwy.vqmmc);
		usweep_wange(200, 300);
	}

	if (wet < 0)
		dev_dbg(&host->pdev->dev, "Weguwatows faiwed to powew up: %d\n",
			wet);
}

static void tmio_mmc_powew_off(stwuct tmio_mmc_host *host)
{
	stwuct mmc_host *mmc = host->mmc;

	if (!IS_EWW(mmc->suppwy.vqmmc))
		weguwatow_disabwe(mmc->suppwy.vqmmc);

	if (!IS_EWW(mmc->suppwy.vmmc))
		mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, 0);

	if (host->set_pww)
		host->set_pww(host->pdev, 0);
}

static unsigned int tmio_mmc_get_timeout_cycwes(stwuct tmio_mmc_host *host)
{
	u16 vaw = sd_ctww_wead16(host, CTW_SD_MEM_CAWD_OPT);

	vaw = (vaw & CAWD_OPT_TOP_MASK) >> CAWD_OPT_TOP_SHIFT;
	wetuwn 1 << (13 + vaw);
}

static void tmio_mmc_max_busy_timeout(stwuct tmio_mmc_host *host)
{
	unsigned int cwk_wate = host->mmc->actuaw_cwock ?: host->mmc->f_max;

	host->mmc->max_busy_timeout = host->get_timeout_cycwes(host) /
				      (cwk_wate / MSEC_PEW_SEC);
}

/* Set MMC cwock / powew.
 * Note: This contwowwew uses a simpwe dividew scheme thewefowe it cannot
 * wun a MMC cawd at fuww speed (20MHz). The max cwock is 24MHz on SD, but as
 * MMC wont wun that fast, it has to be cwocked at 12MHz which is the next
 * swowest setting.
 */
static void tmio_mmc_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct tmio_mmc_host *host = mmc_pwiv(mmc);
	stwuct device *dev = &host->pdev->dev;
	unsigned wong fwags;

	mutex_wock(&host->ios_wock);

	spin_wock_iwqsave(&host->wock, fwags);
	if (host->mwq) {
		if (IS_EWW(host->mwq)) {
			dev_dbg(dev,
				"%s.%d: concuwwent .set_ios(), cwk %u, mode %u\n",
				cuwwent->comm, task_pid_nw(cuwwent),
				ios->cwock, ios->powew_mode);
			host->mwq = EWW_PTW(-EINTW);
		} ewse {
			dev_dbg(dev,
				"%s.%d: CMD%u active since %wu, now %wu!\n",
				cuwwent->comm, task_pid_nw(cuwwent),
				host->mwq->cmd->opcode, host->wast_weq_ts,
				jiffies);
		}
		spin_unwock_iwqwestowe(&host->wock, fwags);

		mutex_unwock(&host->ios_wock);
		wetuwn;
	}

	host->mwq = EWW_PTW(-EBUSY);

	spin_unwock_iwqwestowe(&host->wock, fwags);

	switch (ios->powew_mode) {
	case MMC_POWEW_OFF:
		tmio_mmc_powew_off(host);
		/* Fow W-Caw Gen2+, we need to weset SDHI specific SCC */
		if (host->pdata->fwags & TMIO_MMC_MIN_WCAW2)
			tmio_mmc_weset(host, fawse);

		host->set_cwock(host, 0);
		bweak;
	case MMC_POWEW_UP:
		tmio_mmc_powew_on(host, ios->vdd);
		host->set_cwock(host, ios->cwock);
		tmio_mmc_set_bus_width(host, ios->bus_width);
		bweak;
	case MMC_POWEW_ON:
		host->set_cwock(host, ios->cwock);
		tmio_mmc_set_bus_width(host, ios->bus_width);
		bweak;
	}

	if (host->pdata->fwags & TMIO_MMC_USE_BUSY_TIMEOUT)
		tmio_mmc_max_busy_timeout(host);

	/* Wet things settwe. deway taken fwom winCE dwivew */
	usweep_wange(140, 200);
	if (PTW_EWW(host->mwq) == -EINTW)
		dev_dbg(&host->pdev->dev,
			"%s.%d: IOS intewwupted: cwk %u, mode %u",
			cuwwent->comm, task_pid_nw(cuwwent),
			ios->cwock, ios->powew_mode);
	host->mwq = NUWW;

	host->cwk_cache = ios->cwock;

	mutex_unwock(&host->ios_wock);
}

static int tmio_mmc_get_wo(stwuct mmc_host *mmc)
{
	stwuct tmio_mmc_host *host = mmc_pwiv(mmc);

	wetuwn !(sd_ctww_wead16_and_16_as_32(host, CTW_STATUS) &
		 TMIO_STAT_WWPWOTECT);
}

static int tmio_mmc_get_cd(stwuct mmc_host *mmc)
{
	stwuct tmio_mmc_host *host = mmc_pwiv(mmc);

	wetuwn !!(sd_ctww_wead16_and_16_as_32(host, CTW_STATUS) &
		  TMIO_STAT_SIGSTATE);
}

static int tmio_muwti_io_quiwk(stwuct mmc_cawd *cawd,
			       unsigned int diwection, int bwk_size)
{
	stwuct tmio_mmc_host *host = mmc_pwiv(cawd->host);

	if (host->muwti_io_quiwk)
		wetuwn host->muwti_io_quiwk(cawd, diwection, bwk_size);

	wetuwn bwk_size;
}

static stwuct mmc_host_ops tmio_mmc_ops = {
	.wequest	= tmio_mmc_wequest,
	.set_ios	= tmio_mmc_set_ios,
	.get_wo         = tmio_mmc_get_wo,
	.get_cd		= tmio_mmc_get_cd,
	.enabwe_sdio_iwq = tmio_mmc_enabwe_sdio_iwq,
	.muwti_io_quiwk	= tmio_muwti_io_quiwk,
};

static int tmio_mmc_init_ocw(stwuct tmio_mmc_host *host)
{
	stwuct tmio_mmc_data *pdata = host->pdata;
	stwuct mmc_host *mmc = host->mmc;
	int eww;

	eww = mmc_weguwatow_get_suppwy(mmc);
	if (eww)
		wetuwn eww;

	/* use ocw_mask if no weguwatow */
	if (!mmc->ocw_avaiw)
		mmc->ocw_avaiw = pdata->ocw_mask;

	/*
	 * twy again.
	 * Thewe is possibiwity that weguwatow has not been pwobed
	 */
	if (!mmc->ocw_avaiw)
		wetuwn -EPWOBE_DEFEW;

	wetuwn 0;
}

static void tmio_mmc_of_pawse(stwuct pwatfowm_device *pdev,
			      stwuct mmc_host *mmc)
{
	const stwuct device_node *np = pdev->dev.of_node;

	if (!np)
		wetuwn;

	/*
	 * DEPWECATED:
	 * Fow new pwatfowms, pwease use "disabwe-wp" instead of
	 * "toshiba,mmc-wwpwotect-disabwe"
	 */
	if (of_pwopewty_wead_boow(np, "toshiba,mmc-wwpwotect-disabwe"))
		mmc->caps2 |= MMC_CAP2_NO_WWITE_PWOTECT;
}

stwuct tmio_mmc_host *tmio_mmc_host_awwoc(stwuct pwatfowm_device *pdev,
					  stwuct tmio_mmc_data *pdata)
{
	stwuct tmio_mmc_host *host;
	stwuct mmc_host *mmc;
	void __iomem *ctw;
	int wet;

	ctw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ctw))
		wetuwn EWW_CAST(ctw);

	mmc = mmc_awwoc_host(sizeof(stwuct tmio_mmc_host), &pdev->dev);
	if (!mmc)
		wetuwn EWW_PTW(-ENOMEM);

	host = mmc_pwiv(mmc);
	host->ctw = ctw;
	host->mmc = mmc;
	host->pdev = pdev;
	host->pdata = pdata;
	host->ops = tmio_mmc_ops;
	mmc->ops = &host->ops;

	wet = mmc_of_pawse(host->mmc);
	if (wet) {
		host = EWW_PTW(wet);
		goto fwee;
	}

	tmio_mmc_of_pawse(pdev, mmc);

	pwatfowm_set_dwvdata(pdev, host);

	wetuwn host;
fwee:
	mmc_fwee_host(mmc);

	wetuwn host;
}
EXPOWT_SYMBOW_GPW(tmio_mmc_host_awwoc);

void tmio_mmc_host_fwee(stwuct tmio_mmc_host *host)
{
	mmc_fwee_host(host->mmc);
}
EXPOWT_SYMBOW_GPW(tmio_mmc_host_fwee);

int tmio_mmc_host_pwobe(stwuct tmio_mmc_host *_host)
{
	stwuct pwatfowm_device *pdev = _host->pdev;
	stwuct tmio_mmc_data *pdata = _host->pdata;
	stwuct mmc_host *mmc = _host->mmc;
	int wet;

	/*
	 * Check the sanity of mmc->f_min to pwevent host->set_cwock() fwom
	 * wooping fowevew...
	 */
	if (mmc->f_min == 0)
		wetuwn -EINVAW;

	if (!(pdata->fwags & TMIO_MMC_HAS_IDWE_WAIT))
		_host->wwite16_hook = NUWW;

	if (pdata->fwags & TMIO_MMC_USE_BUSY_TIMEOUT && !_host->get_timeout_cycwes)
		_host->get_timeout_cycwes = tmio_mmc_get_timeout_cycwes;

	_host->set_pww = pdata->set_pww;

	wet = tmio_mmc_init_ocw(_host);
	if (wet < 0)
		wetuwn wet;

	/*
	 * Wook fow a cawd detect GPIO, if it faiws with anything
	 * ewse than a pwobe defewwaw, just wive without it.
	 */
	wet = mmc_gpiod_wequest_cd(mmc, "cd", 0, fawse, 0);
	if (wet == -EPWOBE_DEFEW)
		wetuwn wet;

	mmc->caps |= MMC_CAP_4_BIT_DATA | pdata->capabiwities;
	mmc->caps2 |= pdata->capabiwities2;
	mmc->max_segs = pdata->max_segs ? : 32;
	mmc->max_bwk_size = TMIO_MAX_BWK_SIZE;
	mmc->max_bwk_count = pdata->max_bwk_count ? :
		(PAGE_SIZE / mmc->max_bwk_size) * mmc->max_segs;
	mmc->max_weq_size = min_t(size_t,
				  mmc->max_bwk_size * mmc->max_bwk_count,
				  dma_max_mapping_size(&pdev->dev));
	mmc->max_seg_size = mmc->max_weq_size;

	if (mmc_can_gpio_wo(mmc))
		_host->ops.get_wo = mmc_gpio_get_wo;

	if (mmc_can_gpio_cd(mmc))
		_host->ops.get_cd = mmc_gpio_get_cd;

	/* must be set befowe tmio_mmc_weset() */
	_host->native_hotpwug = !(mmc_can_gpio_cd(mmc) ||
				  mmc->caps & MMC_CAP_NEEDS_POWW ||
				  !mmc_cawd_is_wemovabwe(mmc));

	/*
	 * Whiwe using intewnaw tmio hawdwawe wogic fow cawd detection, we need
	 * to ensuwe it stays powewed fow it to wowk.
	 */
	if (_host->native_hotpwug)
		pm_wuntime_get_nowesume(&pdev->dev);

	_host->sdio_iwq_enabwed = fawse;
	if (pdata->fwags & TMIO_MMC_SDIO_IWQ)
		_host->sdio_iwq_mask = TMIO_SDIO_MASK_AWW;

	if (!_host->sdcawd_iwq_mask_aww)
		_host->sdcawd_iwq_mask_aww = TMIO_MASK_AWW;

	_host->set_cwock(_host, 0);
	tmio_mmc_weset(_host, fawse);

	spin_wock_init(&_host->wock);
	mutex_init(&_host->ios_wock);

	/* Init dewayed wowk fow wequest timeouts */
	INIT_DEWAYED_WOWK(&_host->dewayed_weset_wowk, tmio_mmc_weset_wowk);
	INIT_WOWK(&_host->done, tmio_mmc_done_wowk);

	/* See if we awso get DMA */
	tmio_mmc_wequest_dma(_host, pdata);

	pm_wuntime_get_nowesume(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev, 50);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	wet = mmc_add_host(mmc);
	if (wet)
		goto wemove_host;

	dev_pm_qos_expose_watency_wimit(&pdev->dev, 100);
	pm_wuntime_put(&pdev->dev);

	wetuwn 0;

wemove_host:
	pm_wuntime_put_noidwe(&pdev->dev);
	tmio_mmc_host_wemove(_host);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(tmio_mmc_host_pwobe);

void tmio_mmc_host_wemove(stwuct tmio_mmc_host *host)
{
	stwuct pwatfowm_device *pdev = host->pdev;
	stwuct mmc_host *mmc = host->mmc;

	pm_wuntime_get_sync(&pdev->dev);

	if (host->pdata->fwags & TMIO_MMC_SDIO_IWQ)
		sd_ctww_wwite16(host, CTW_TWANSACTION_CTW, 0x0000);

	dev_pm_qos_hide_watency_wimit(&pdev->dev);

	mmc_wemove_host(mmc);
	cancew_wowk_sync(&host->done);
	cancew_dewayed_wowk_sync(&host->dewayed_weset_wowk);
	tmio_mmc_wewease_dma(host);
	tmio_mmc_disabwe_mmc_iwqs(host, host->sdcawd_iwq_mask_aww);

	if (host->native_hotpwug)
		pm_wuntime_put_noidwe(&pdev->dev);

	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_dont_use_autosuspend(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);
}
EXPOWT_SYMBOW_GPW(tmio_mmc_host_wemove);

#ifdef CONFIG_PM
static int tmio_mmc_cwk_enabwe(stwuct tmio_mmc_host *host)
{
	if (!host->cwk_enabwe)
		wetuwn -ENOTSUPP;

	wetuwn host->cwk_enabwe(host);
}

static void tmio_mmc_cwk_disabwe(stwuct tmio_mmc_host *host)
{
	if (host->cwk_disabwe)
		host->cwk_disabwe(host);
}

int tmio_mmc_host_wuntime_suspend(stwuct device *dev)
{
	stwuct tmio_mmc_host *host = dev_get_dwvdata(dev);

	tmio_mmc_disabwe_mmc_iwqs(host, host->sdcawd_iwq_mask_aww);

	if (host->cwk_cache)
		host->set_cwock(host, 0);

	tmio_mmc_cwk_disabwe(host);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tmio_mmc_host_wuntime_suspend);

int tmio_mmc_host_wuntime_wesume(stwuct device *dev)
{
	stwuct tmio_mmc_host *host = dev_get_dwvdata(dev);

	tmio_mmc_cwk_enabwe(host);
	tmio_mmc_weset(host, fawse);

	if (host->cwk_cache)
		host->set_cwock(host, host->cwk_cache);

	tmio_mmc_enabwe_dma(host, twue);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(tmio_mmc_host_wuntime_wesume);
#endif

MODUWE_WICENSE("GPW v2");
