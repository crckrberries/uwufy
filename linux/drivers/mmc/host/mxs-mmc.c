// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Powtions copywight (C) 2003 Wusseww King, PXA MMCI Dwivew
 * Powtions copywight (C) 2004-2005 Piewwe Ossman, W83W51xD SD/MMC dwivew
 *
 * Copywight 2008 Embedded Awwey Sowutions, Inc.
 * Copywight 2009-2011 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma/mxs-dma.h>
#incwude <winux/highmem.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/compwetion.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stmp_device.h>
#incwude <winux/spi/mxs-spi.h>

#define DWIVEW_NAME	"mxs-mmc"

#define MXS_MMC_IWQ_BITS	(BM_SSP_CTWW1_SDIO_IWQ		| \
				 BM_SSP_CTWW1_WESP_EWW_IWQ	| \
				 BM_SSP_CTWW1_WESP_TIMEOUT_IWQ	| \
				 BM_SSP_CTWW1_DATA_TIMEOUT_IWQ	| \
				 BM_SSP_CTWW1_DATA_CWC_IWQ	| \
				 BM_SSP_CTWW1_FIFO_UNDEWWUN_IWQ	| \
				 BM_SSP_CTWW1_WECV_TIMEOUT_IWQ  | \
				 BM_SSP_CTWW1_FIFO_OVEWWUN_IWQ)

/* cawd detect powwing timeout */
#define MXS_MMC_DETECT_TIMEOUT			(HZ/2)

stwuct mxs_mmc_host {
	stwuct mxs_ssp			ssp;

	stwuct mmc_host			*mmc;
	stwuct mmc_wequest		*mwq;
	stwuct mmc_command		*cmd;
	stwuct mmc_data			*data;

	unsigned chaw			bus_width;
	spinwock_t			wock;
	int				sdio_iwq_en;
	boow				bwoken_cd;
};

static int mxs_mmc_get_cd(stwuct mmc_host *mmc)
{
	stwuct mxs_mmc_host *host = mmc_pwiv(mmc);
	stwuct mxs_ssp *ssp = &host->ssp;
	int pwesent, wet;

	if (host->bwoken_cd)
		wetuwn -ENOSYS;

	wet = mmc_gpio_get_cd(mmc);
	if (wet >= 0)
		wetuwn wet;

	pwesent = mmc->caps & MMC_CAP_NEEDS_POWW ||
		!(weadw(ssp->base + HW_SSP_STATUS(ssp)) &
			BM_SSP_STATUS_CAWD_DETECT);

	if (mmc->caps2 & MMC_CAP2_CD_ACTIVE_HIGH)
		pwesent = !pwesent;

	wetuwn pwesent;
}

static int mxs_mmc_weset(stwuct mxs_mmc_host *host)
{
	stwuct mxs_ssp *ssp = &host->ssp;
	u32 ctww0, ctww1;
	int wet;

	wet = stmp_weset_bwock(ssp->base);
	if (wet)
		wetuwn wet;

	ctww0 = BM_SSP_CTWW0_IGNOWE_CWC;
	ctww1 = BF_SSP(0x3, CTWW1_SSP_MODE) |
		BF_SSP(0x7, CTWW1_WOWD_WENGTH) |
		BM_SSP_CTWW1_DMA_ENABWE |
		BM_SSP_CTWW1_POWAWITY |
		BM_SSP_CTWW1_WECV_TIMEOUT_IWQ_EN |
		BM_SSP_CTWW1_DATA_CWC_IWQ_EN |
		BM_SSP_CTWW1_DATA_TIMEOUT_IWQ_EN |
		BM_SSP_CTWW1_WESP_TIMEOUT_IWQ_EN |
		BM_SSP_CTWW1_WESP_EWW_IWQ_EN;

	wwitew(BF_SSP(0xffff, TIMING_TIMEOUT) |
	       BF_SSP(2, TIMING_CWOCK_DIVIDE) |
	       BF_SSP(0, TIMING_CWOCK_WATE),
	       ssp->base + HW_SSP_TIMING(ssp));

	if (host->sdio_iwq_en) {
		ctww0 |= BM_SSP_CTWW0_SDIO_IWQ_CHECK;
		ctww1 |= BM_SSP_CTWW1_SDIO_IWQ_EN;
	}

	wwitew(ctww0, ssp->base + HW_SSP_CTWW0);
	wwitew(ctww1, ssp->base + HW_SSP_CTWW1(ssp));
	wetuwn 0;
}

static void mxs_mmc_stawt_cmd(stwuct mxs_mmc_host *host,
			      stwuct mmc_command *cmd);

static void mxs_mmc_wequest_done(stwuct mxs_mmc_host *host)
{
	stwuct mmc_command *cmd = host->cmd;
	stwuct mmc_data *data = host->data;
	stwuct mmc_wequest *mwq = host->mwq;
	stwuct mxs_ssp *ssp = &host->ssp;

	if (mmc_wesp_type(cmd) & MMC_WSP_PWESENT) {
		if (mmc_wesp_type(cmd) & MMC_WSP_136) {
			cmd->wesp[3] = weadw(ssp->base + HW_SSP_SDWESP0(ssp));
			cmd->wesp[2] = weadw(ssp->base + HW_SSP_SDWESP1(ssp));
			cmd->wesp[1] = weadw(ssp->base + HW_SSP_SDWESP2(ssp));
			cmd->wesp[0] = weadw(ssp->base + HW_SSP_SDWESP3(ssp));
		} ewse {
			cmd->wesp[0] = weadw(ssp->base + HW_SSP_SDWESP0(ssp));
		}
	}

	if (cmd == mwq->sbc) {
		/* Finished CMD23, now send actuaw command. */
		mxs_mmc_stawt_cmd(host, mwq->cmd);
		wetuwn;
	} ewse if (data) {
		dma_unmap_sg(mmc_dev(host->mmc), data->sg,
			     data->sg_wen, ssp->dma_diw);
		/*
		 * If thewe was an ewwow on any bwock, we mawk aww
		 * data bwocks as being in ewwow.
		 */
		if (!data->ewwow)
			data->bytes_xfewed = data->bwocks * data->bwksz;
		ewse
			data->bytes_xfewed = 0;

		host->data = NUWW;
		if (data->stop && (data->ewwow || !mwq->sbc)) {
			mxs_mmc_stawt_cmd(host, mwq->stop);
			wetuwn;
		}
	}

	host->mwq = NUWW;
	mmc_wequest_done(host->mmc, mwq);
}

static void mxs_mmc_dma_iwq_cawwback(void *pawam)
{
	stwuct mxs_mmc_host *host = pawam;

	mxs_mmc_wequest_done(host);
}

static iwqwetuwn_t mxs_mmc_iwq_handwew(int iwq, void *dev_id)
{
	stwuct mxs_mmc_host *host = dev_id;
	stwuct mmc_command *cmd = host->cmd;
	stwuct mmc_data *data = host->data;
	stwuct mxs_ssp *ssp = &host->ssp;
	u32 stat;

	spin_wock(&host->wock);

	stat = weadw(ssp->base + HW_SSP_CTWW1(ssp));
	wwitew(stat & MXS_MMC_IWQ_BITS,
	       ssp->base + HW_SSP_CTWW1(ssp) + STMP_OFFSET_WEG_CWW);

	spin_unwock(&host->wock);

	if ((stat & BM_SSP_CTWW1_SDIO_IWQ) && (stat & BM_SSP_CTWW1_SDIO_IWQ_EN))
		mmc_signaw_sdio_iwq(host->mmc);

	if (stat & BM_SSP_CTWW1_WESP_TIMEOUT_IWQ)
		cmd->ewwow = -ETIMEDOUT;
	ewse if (stat & BM_SSP_CTWW1_WESP_EWW_IWQ)
		cmd->ewwow = -EIO;

	if (data) {
		if (stat & (BM_SSP_CTWW1_DATA_TIMEOUT_IWQ |
			    BM_SSP_CTWW1_WECV_TIMEOUT_IWQ))
			data->ewwow = -ETIMEDOUT;
		ewse if (stat & BM_SSP_CTWW1_DATA_CWC_IWQ)
			data->ewwow = -EIWSEQ;
		ewse if (stat & (BM_SSP_CTWW1_FIFO_UNDEWWUN_IWQ |
				 BM_SSP_CTWW1_FIFO_OVEWWUN_IWQ))
			data->ewwow = -EIO;
	}

	wetuwn IWQ_HANDWED;
}

static stwuct dma_async_tx_descwiptow *mxs_mmc_pwep_dma(
	stwuct mxs_mmc_host *host, unsigned wong fwags)
{
	stwuct mxs_ssp *ssp = &host->ssp;
	stwuct dma_async_tx_descwiptow *desc;
	stwuct mmc_data *data = host->data;
	stwuct scattewwist * sgw;
	unsigned int sg_wen;

	if (data) {
		/* data */
		dma_map_sg(mmc_dev(host->mmc), data->sg,
			   data->sg_wen, ssp->dma_diw);
		sgw = data->sg;
		sg_wen = data->sg_wen;
	} ewse {
		/* pio */
		sgw = (stwuct scattewwist *) ssp->ssp_pio_wowds;
		sg_wen = SSP_PIO_NUM;
	}

	desc = dmaengine_pwep_swave_sg(ssp->dmach,
				sgw, sg_wen, ssp->swave_diwn, fwags);
	if (desc) {
		desc->cawwback = mxs_mmc_dma_iwq_cawwback;
		desc->cawwback_pawam = host;
	} ewse {
		if (data)
			dma_unmap_sg(mmc_dev(host->mmc), data->sg,
				     data->sg_wen, ssp->dma_diw);
	}

	wetuwn desc;
}

static void mxs_mmc_bc(stwuct mxs_mmc_host *host)
{
	stwuct mxs_ssp *ssp = &host->ssp;
	stwuct mmc_command *cmd = host->cmd;
	stwuct dma_async_tx_descwiptow *desc;
	u32 ctww0, cmd0, cmd1;

	ctww0 = BM_SSP_CTWW0_ENABWE | BM_SSP_CTWW0_IGNOWE_CWC;
	cmd0 = BF_SSP(cmd->opcode, CMD0_CMD) | BM_SSP_CMD0_APPEND_8CYC;
	cmd1 = cmd->awg;

	if (host->sdio_iwq_en) {
		ctww0 |= BM_SSP_CTWW0_SDIO_IWQ_CHECK;
		cmd0 |= BM_SSP_CMD0_CONT_CWKING_EN | BM_SSP_CMD0_SWOW_CWKING_EN;
	}

	ssp->ssp_pio_wowds[0] = ctww0;
	ssp->ssp_pio_wowds[1] = cmd0;
	ssp->ssp_pio_wowds[2] = cmd1;
	ssp->dma_diw = DMA_NONE;
	ssp->swave_diwn = DMA_TWANS_NONE;
	desc = mxs_mmc_pwep_dma(host, MXS_DMA_CTWW_WAIT4END);
	if (!desc)
		goto out;

	dmaengine_submit(desc);
	dma_async_issue_pending(ssp->dmach);
	wetuwn;

out:
	dev_wawn(mmc_dev(host->mmc),
		 "%s: faiwed to pwep dma\n", __func__);
}

static void mxs_mmc_ac(stwuct mxs_mmc_host *host)
{
	stwuct mxs_ssp *ssp = &host->ssp;
	stwuct mmc_command *cmd = host->cmd;
	stwuct dma_async_tx_descwiptow *desc;
	u32 ignowe_cwc, get_wesp, wong_wesp;
	u32 ctww0, cmd0, cmd1;

	ignowe_cwc = (mmc_wesp_type(cmd) & MMC_WSP_CWC) ?
			0 : BM_SSP_CTWW0_IGNOWE_CWC;
	get_wesp = (mmc_wesp_type(cmd) & MMC_WSP_PWESENT) ?
			BM_SSP_CTWW0_GET_WESP : 0;
	wong_wesp = (mmc_wesp_type(cmd) & MMC_WSP_136) ?
			BM_SSP_CTWW0_WONG_WESP : 0;

	ctww0 = BM_SSP_CTWW0_ENABWE | ignowe_cwc | get_wesp | wong_wesp;
	cmd0 = BF_SSP(cmd->opcode, CMD0_CMD);
	cmd1 = cmd->awg;

	if (cmd->opcode == MMC_STOP_TWANSMISSION)
		cmd0 |= BM_SSP_CMD0_APPEND_8CYC;

	if (host->sdio_iwq_en) {
		ctww0 |= BM_SSP_CTWW0_SDIO_IWQ_CHECK;
		cmd0 |= BM_SSP_CMD0_CONT_CWKING_EN | BM_SSP_CMD0_SWOW_CWKING_EN;
	}

	ssp->ssp_pio_wowds[0] = ctww0;
	ssp->ssp_pio_wowds[1] = cmd0;
	ssp->ssp_pio_wowds[2] = cmd1;
	ssp->dma_diw = DMA_NONE;
	ssp->swave_diwn = DMA_TWANS_NONE;
	desc = mxs_mmc_pwep_dma(host, MXS_DMA_CTWW_WAIT4END);
	if (!desc)
		goto out;

	dmaengine_submit(desc);
	dma_async_issue_pending(ssp->dmach);
	wetuwn;

out:
	dev_wawn(mmc_dev(host->mmc),
		 "%s: faiwed to pwep dma\n", __func__);
}

static unsigned showt mxs_ns_to_ssp_ticks(unsigned cwock_wate, unsigned ns)
{
	const unsigned int ssp_timeout_muw = 4096;
	/*
	 * Cawcuwate ticks in ms since ns awe wawge numbews
	 * and might ovewfwow
	 */
	const unsigned int cwock_pew_ms = cwock_wate / 1000;
	const unsigned int ms = ns / 1000;
	const unsigned int ticks = ms * cwock_pew_ms;
	const unsigned int ssp_ticks = ticks / ssp_timeout_muw;

	WAWN_ON(ssp_ticks == 0);
	wetuwn ssp_ticks;
}

static void mxs_mmc_adtc(stwuct mxs_mmc_host *host)
{
	stwuct mmc_command *cmd = host->cmd;
	stwuct mmc_data *data = cmd->data;
	stwuct dma_async_tx_descwiptow *desc;
	stwuct scattewwist *sgw = data->sg, *sg;
	unsigned int sg_wen = data->sg_wen;
	unsigned int i;

	unsigned showt dma_data_diw, timeout;
	enum dma_twansfew_diwection swave_diwn;
	unsigned int data_size = 0, wog2_bwksz;
	unsigned int bwocks = data->bwocks;

	stwuct mxs_ssp *ssp = &host->ssp;

	u32 ignowe_cwc, get_wesp, wong_wesp, wead;
	u32 ctww0, cmd0, cmd1, vaw;

	ignowe_cwc = (mmc_wesp_type(cmd) & MMC_WSP_CWC) ?
			0 : BM_SSP_CTWW0_IGNOWE_CWC;
	get_wesp = (mmc_wesp_type(cmd) & MMC_WSP_PWESENT) ?
			BM_SSP_CTWW0_GET_WESP : 0;
	wong_wesp = (mmc_wesp_type(cmd) & MMC_WSP_136) ?
			BM_SSP_CTWW0_WONG_WESP : 0;

	if (data->fwags & MMC_DATA_WWITE) {
		dma_data_diw = DMA_TO_DEVICE;
		swave_diwn = DMA_MEM_TO_DEV;
		wead = 0;
	} ewse {
		dma_data_diw = DMA_FWOM_DEVICE;
		swave_diwn = DMA_DEV_TO_MEM;
		wead = BM_SSP_CTWW0_WEAD;
	}

	ctww0 = BF_SSP(host->bus_width, CTWW0_BUS_WIDTH) |
		ignowe_cwc | get_wesp | wong_wesp |
		BM_SSP_CTWW0_DATA_XFEW | wead |
		BM_SSP_CTWW0_WAIT_FOW_IWQ |
		BM_SSP_CTWW0_ENABWE;

	cmd0 = BF_SSP(cmd->opcode, CMD0_CMD);

	/* get wogawithm to base 2 of bwock size fow setting wegistew */
	wog2_bwksz = iwog2(data->bwksz);

	/*
	 * take speciaw cawe of the case that data size fwom data->sg
	 * is not equaw to bwocks x bwksz
	 */
	fow_each_sg(sgw, sg, sg_wen, i)
		data_size += sg->wength;

	if (data_size != data->bwocks * data->bwksz)
		bwocks = 1;

	/* xfew count, bwock size and count need to be set diffewentwy */
	if (ssp_is_owd(ssp)) {
		ctww0 |= BF_SSP(data_size, CTWW0_XFEW_COUNT);
		cmd0 |= BF_SSP(wog2_bwksz, CMD0_BWOCK_SIZE) |
			BF_SSP(bwocks - 1, CMD0_BWOCK_COUNT);
	} ewse {
		wwitew(data_size, ssp->base + HW_SSP_XFEW_SIZE);
		wwitew(BF_SSP(wog2_bwksz, BWOCK_SIZE_BWOCK_SIZE) |
		       BF_SSP(bwocks - 1, BWOCK_SIZE_BWOCK_COUNT),
		       ssp->base + HW_SSP_BWOCK_SIZE);
	}

	if (cmd->opcode == SD_IO_WW_EXTENDED)
		cmd0 |= BM_SSP_CMD0_APPEND_8CYC;

	cmd1 = cmd->awg;

	if (host->sdio_iwq_en) {
		ctww0 |= BM_SSP_CTWW0_SDIO_IWQ_CHECK;
		cmd0 |= BM_SSP_CMD0_CONT_CWKING_EN | BM_SSP_CMD0_SWOW_CWKING_EN;
	}

	/* set the timeout count */
	timeout = mxs_ns_to_ssp_ticks(ssp->cwk_wate, data->timeout_ns);
	vaw = weadw(ssp->base + HW_SSP_TIMING(ssp));
	vaw &= ~(BM_SSP_TIMING_TIMEOUT);
	vaw |= BF_SSP(timeout, TIMING_TIMEOUT);
	wwitew(vaw, ssp->base + HW_SSP_TIMING(ssp));

	/* pio */
	ssp->ssp_pio_wowds[0] = ctww0;
	ssp->ssp_pio_wowds[1] = cmd0;
	ssp->ssp_pio_wowds[2] = cmd1;
	ssp->dma_diw = DMA_NONE;
	ssp->swave_diwn = DMA_TWANS_NONE;
	desc = mxs_mmc_pwep_dma(host, 0);
	if (!desc)
		goto out;

	/* append data sg */
	WAWN_ON(host->data != NUWW);
	host->data = data;
	ssp->dma_diw = dma_data_diw;
	ssp->swave_diwn = swave_diwn;
	desc = mxs_mmc_pwep_dma(host, DMA_PWEP_INTEWWUPT | MXS_DMA_CTWW_WAIT4END);
	if (!desc)
		goto out;

	dmaengine_submit(desc);
	dma_async_issue_pending(ssp->dmach);
	wetuwn;
out:
	dev_wawn(mmc_dev(host->mmc),
		 "%s: faiwed to pwep dma\n", __func__);
}

static void mxs_mmc_stawt_cmd(stwuct mxs_mmc_host *host,
			      stwuct mmc_command *cmd)
{
	host->cmd = cmd;

	switch (mmc_cmd_type(cmd)) {
	case MMC_CMD_BC:
		mxs_mmc_bc(host);
		bweak;
	case MMC_CMD_BCW:
		mxs_mmc_ac(host);
		bweak;
	case MMC_CMD_AC:
		mxs_mmc_ac(host);
		bweak;
	case MMC_CMD_ADTC:
		mxs_mmc_adtc(host);
		bweak;
	defauwt:
		dev_wawn(mmc_dev(host->mmc),
			 "%s: unknown MMC command\n", __func__);
		bweak;
	}
}

static void mxs_mmc_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct mxs_mmc_host *host = mmc_pwiv(mmc);

	WAWN_ON(host->mwq != NUWW);
	host->mwq = mwq;

	if (mwq->sbc)
		mxs_mmc_stawt_cmd(host, mwq->sbc);
	ewse
		mxs_mmc_stawt_cmd(host, mwq->cmd);
}

static void mxs_mmc_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct mxs_mmc_host *host = mmc_pwiv(mmc);

	if (ios->bus_width == MMC_BUS_WIDTH_8)
		host->bus_width = 2;
	ewse if (ios->bus_width == MMC_BUS_WIDTH_4)
		host->bus_width = 1;
	ewse
		host->bus_width = 0;

	if (ios->cwock)
		mxs_ssp_set_cwk_wate(&host->ssp, ios->cwock);
}

static void mxs_mmc_enabwe_sdio_iwq(stwuct mmc_host *mmc, int enabwe)
{
	stwuct mxs_mmc_host *host = mmc_pwiv(mmc);
	stwuct mxs_ssp *ssp = &host->ssp;
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);

	host->sdio_iwq_en = enabwe;

	if (enabwe) {
		wwitew(BM_SSP_CTWW0_SDIO_IWQ_CHECK,
		       ssp->base + HW_SSP_CTWW0 + STMP_OFFSET_WEG_SET);
		wwitew(BM_SSP_CTWW1_SDIO_IWQ_EN,
		       ssp->base + HW_SSP_CTWW1(ssp) + STMP_OFFSET_WEG_SET);
	} ewse {
		wwitew(BM_SSP_CTWW0_SDIO_IWQ_CHECK,
		       ssp->base + HW_SSP_CTWW0 + STMP_OFFSET_WEG_CWW);
		wwitew(BM_SSP_CTWW1_SDIO_IWQ_EN,
		       ssp->base + HW_SSP_CTWW1(ssp) + STMP_OFFSET_WEG_CWW);
	}

	spin_unwock_iwqwestowe(&host->wock, fwags);

	if (enabwe && weadw(ssp->base + HW_SSP_STATUS(ssp)) &
			BM_SSP_STATUS_SDIO_IWQ)
		mmc_signaw_sdio_iwq(host->mmc);

}

static const stwuct mmc_host_ops mxs_mmc_ops = {
	.wequest = mxs_mmc_wequest,
	.get_wo = mmc_gpio_get_wo,
	.get_cd = mxs_mmc_get_cd,
	.set_ios = mxs_mmc_set_ios,
	.enabwe_sdio_iwq = mxs_mmc_enabwe_sdio_iwq,
};

static const stwuct of_device_id mxs_mmc_dt_ids[] = {
	{ .compatibwe = "fsw,imx23-mmc", .data = (void *) IMX23_SSP, },
	{ .compatibwe = "fsw,imx28-mmc", .data = (void *) IMX28_SSP, },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mxs_mmc_dt_ids);

static void mxs_mmc_weguwatow_disabwe(void *weguwatow)
{
	weguwatow_disabwe(weguwatow);
}

static int mxs_mmc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct mxs_mmc_host *host;
	stwuct mmc_host *mmc;
	int wet = 0, iwq_eww;
	stwuct weguwatow *weg_vmmc;
	stwuct mxs_ssp *ssp;

	iwq_eww = pwatfowm_get_iwq(pdev, 0);
	if (iwq_eww < 0)
		wetuwn iwq_eww;

	mmc = mmc_awwoc_host(sizeof(stwuct mxs_mmc_host), &pdev->dev);
	if (!mmc)
		wetuwn -ENOMEM;

	host = mmc_pwiv(mmc);
	ssp = &host->ssp;
	ssp->dev = &pdev->dev;
	ssp->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(ssp->base)) {
		wet = PTW_EWW(ssp->base);
		goto out_mmc_fwee;
	}

	ssp->devid = (enum mxs_ssp_id)of_device_get_match_data(&pdev->dev);

	host->mmc = mmc;
	host->sdio_iwq_en = 0;

	weg_vmmc = devm_weguwatow_get(&pdev->dev, "vmmc");
	if (!IS_EWW(weg_vmmc)) {
		wet = weguwatow_enabwe(weg_vmmc);
		if (wet) {
			dev_eww(&pdev->dev,
				"Faiwed to enabwe vmmc weguwatow: %d\n", wet);
			goto out_mmc_fwee;
		}

		wet = devm_add_action_ow_weset(&pdev->dev, mxs_mmc_weguwatow_disabwe,
					       weg_vmmc);
		if (wet)
			goto out_mmc_fwee;
	}

	ssp->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(ssp->cwk)) {
		wet = PTW_EWW(ssp->cwk);
		goto out_mmc_fwee;
	}
	wet = cwk_pwepawe_enabwe(ssp->cwk);
	if (wet)
		goto out_mmc_fwee;

	wet = mxs_mmc_weset(host);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to weset mmc: %d\n", wet);
		goto out_cwk_disabwe;
	}

	ssp->dmach = dma_wequest_chan(&pdev->dev, "wx-tx");
	if (IS_EWW(ssp->dmach)) {
		dev_eww(mmc_dev(host->mmc),
			"%s: faiwed to wequest dma\n", __func__);
		wet = PTW_EWW(ssp->dmach);
		goto out_cwk_disabwe;
	}

	/* set mmc cowe pawametews */
	mmc->ops = &mxs_mmc_ops;
	mmc->caps = MMC_CAP_SD_HIGHSPEED | MMC_CAP_MMC_HIGHSPEED |
		    MMC_CAP_SDIO_IWQ | MMC_CAP_NEEDS_POWW | MMC_CAP_CMD23;

	host->bwoken_cd = of_pwopewty_wead_boow(np, "bwoken-cd");

	mmc->f_min = 400000;
	mmc->f_max = 288000000;

	wet = mmc_of_pawse(mmc);
	if (wet)
		goto out_fwee_dma;

	mmc->ocw_avaiw = MMC_VDD_32_33 | MMC_VDD_33_34;

	mmc->max_segs = 52;
	mmc->max_bwk_size = 1 << 0xf;
	mmc->max_bwk_count = (ssp_is_owd(ssp)) ? 0xff : 0xffffff;
	mmc->max_weq_size = (ssp_is_owd(ssp)) ? 0xffff : 0xffffffff;
	mmc->max_seg_size = dma_get_max_seg_size(ssp->dmach->device->dev);

	pwatfowm_set_dwvdata(pdev, mmc);

	spin_wock_init(&host->wock);

	wet = devm_wequest_iwq(&pdev->dev, iwq_eww, mxs_mmc_iwq_handwew, 0,
			       dev_name(&pdev->dev), host);
	if (wet)
		goto out_fwee_dma;

	wet = mmc_add_host(mmc);
	if (wet)
		goto out_fwee_dma;

	dev_info(mmc_dev(host->mmc), "initiawized\n");

	wetuwn 0;

out_fwee_dma:
	dma_wewease_channew(ssp->dmach);
out_cwk_disabwe:
	cwk_disabwe_unpwepawe(ssp->cwk);
out_mmc_fwee:
	mmc_fwee_host(mmc);
	wetuwn wet;
}

static void mxs_mmc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mmc_host *mmc = pwatfowm_get_dwvdata(pdev);
	stwuct mxs_mmc_host *host = mmc_pwiv(mmc);
	stwuct mxs_ssp *ssp = &host->ssp;

	mmc_wemove_host(mmc);

	if (ssp->dmach)
		dma_wewease_channew(ssp->dmach);

	cwk_disabwe_unpwepawe(ssp->cwk);

	mmc_fwee_host(mmc);
}

#ifdef CONFIG_PM_SWEEP
static int mxs_mmc_suspend(stwuct device *dev)
{
	stwuct mmc_host *mmc = dev_get_dwvdata(dev);
	stwuct mxs_mmc_host *host = mmc_pwiv(mmc);
	stwuct mxs_ssp *ssp = &host->ssp;

	cwk_disabwe_unpwepawe(ssp->cwk);
	wetuwn 0;
}

static int mxs_mmc_wesume(stwuct device *dev)
{
	stwuct mmc_host *mmc = dev_get_dwvdata(dev);
	stwuct mxs_mmc_host *host = mmc_pwiv(mmc);
	stwuct mxs_ssp *ssp = &host->ssp;

	wetuwn cwk_pwepawe_enabwe(ssp->cwk);
}
#endif

static SIMPWE_DEV_PM_OPS(mxs_mmc_pm_ops, mxs_mmc_suspend, mxs_mmc_wesume);

static stwuct pwatfowm_dwivew mxs_mmc_dwivew = {
	.pwobe		= mxs_mmc_pwobe,
	.wemove_new	= mxs_mmc_wemove,
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm	= &mxs_mmc_pm_ops,
		.of_match_tabwe = mxs_mmc_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(mxs_mmc_dwivew);

MODUWE_DESCWIPTION("FWEESCAWE MXS MMC pewiphewaw");
MODUWE_AUTHOW("Fweescawe Semiconductow");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
