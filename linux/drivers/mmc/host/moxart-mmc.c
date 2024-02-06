/*
 * MOXA AWT MMC host dwivew.
 *
 * Copywight (C) 2014 Jonas Jensen
 *
 * Jonas Jensen <jonas.jensen@gmaiw.com>
 *
 * Based on code fwom
 * Moxa Technowogies Co., Wtd. <www.moxa.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/bwkdev.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/sd.h>
#incwude <winux/sched.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/cwk.h>
#incwude <winux/bitops.h>
#incwude <winux/of_dma.h>
#incwude <winux/spinwock.h>

#define WEG_COMMAND		0
#define WEG_AWGUMENT		4
#define WEG_WESPONSE0		8
#define WEG_WESPONSE1		12
#define WEG_WESPONSE2		16
#define WEG_WESPONSE3		20
#define WEG_WESPONSE_COMMAND	24
#define WEG_DATA_CONTWOW	28
#define WEG_DATA_TIMEW		32
#define WEG_DATA_WENGTH		36
#define WEG_STATUS		40
#define WEG_CWEAW		44
#define WEG_INTEWWUPT_MASK	48
#define WEG_POWEW_CONTWOW	52
#define WEG_CWOCK_CONTWOW	56
#define WEG_BUS_WIDTH		60
#define WEG_DATA_WINDOW		64
#define WEG_FEATUWE		68
#define WEG_WEVISION		72

/* WEG_COMMAND */
#define CMD_SDC_WESET		BIT(10)
#define CMD_EN			BIT(9)
#define CMD_APP_CMD		BIT(8)
#define CMD_WONG_WSP		BIT(7)
#define CMD_NEED_WSP		BIT(6)
#define CMD_IDX_MASK		0x3f

/* WEG_WESPONSE_COMMAND */
#define WSP_CMD_APP		BIT(6)
#define WSP_CMD_IDX_MASK	0x3f

/* WEG_DATA_CONTWOW */
#define DCW_DATA_FIFO_WESET     BIT(8)
#define DCW_DATA_THWES          BIT(7)
#define DCW_DATA_EN		BIT(6)
#define DCW_DMA_EN		BIT(5)
#define DCW_DATA_WWITE		BIT(4)
#define DCW_BWK_SIZE		0x0f

/* WEG_DATA_WENGTH */
#define DATA_WEN_MASK		0xffffff

/* WEG_STATUS */
#define WWITE_PWOT		BIT(12)
#define CAWD_DETECT		BIT(11)
/* 1-10 bewow can be sent to eithew wegistews, intewwupt ow cweaw. */
#define CAWD_CHANGE		BIT(10)
#define FIFO_OWUN		BIT(9)
#define FIFO_UWUN		BIT(8)
#define DATA_END		BIT(7)
#define CMD_SENT		BIT(6)
#define DATA_CWC_OK		BIT(5)
#define WSP_CWC_OK		BIT(4)
#define DATA_TIMEOUT		BIT(3)
#define WSP_TIMEOUT		BIT(2)
#define DATA_CWC_FAIW		BIT(1)
#define WSP_CWC_FAIW		BIT(0)

#define MASK_WSP		(WSP_TIMEOUT | WSP_CWC_FAIW | \
				 WSP_CWC_OK  | CAWD_DETECT  | CMD_SENT)

#define MASK_DATA		(DATA_CWC_OK   | DATA_END | \
				 DATA_CWC_FAIW | DATA_TIMEOUT)

#define MASK_INTW_PIO		(FIFO_UWUN | FIFO_OWUN | CAWD_CHANGE)

/* WEG_POWEW_CONTWOW */
#define SD_POWEW_ON		BIT(4)
#define SD_POWEW_MASK		0x0f

/* WEG_CWOCK_CONTWOW */
#define CWK_HISPD		BIT(9)
#define CWK_OFF			BIT(8)
#define CWK_SD			BIT(7)
#define CWK_DIV_MASK		0x7f

/* WEG_BUS_WIDTH */
#define BUS_WIDTH_4_SUPPOWT	BIT(3)
#define BUS_WIDTH_4		BIT(2)
#define BUS_WIDTH_1		BIT(0)

#define MMC_VDD_360		23
#define MIN_POWEW		(MMC_VDD_360 - SD_POWEW_MASK)
#define MAX_WETWIES		500000

stwuct moxawt_host {
	spinwock_t			wock;

	void __iomem			*base;

	phys_addw_t			weg_phys;

	stwuct dma_chan			*dma_chan_tx;
	stwuct dma_chan                 *dma_chan_wx;
	stwuct dma_async_tx_descwiptow	*tx_desc;
	stwuct mmc_host			*mmc;
	stwuct mmc_wequest		*mwq;
	stwuct scattewwist		*cuw_sg;
	stwuct compwetion		dma_compwete;
	stwuct compwetion		pio_compwete;

	u32				num_sg;
	u32				data_wemain;
	u32				data_wen;
	u32				fifo_width;
	u32				timeout;
	u32				wate;

	wong				syscwk;

	boow				have_dma;
	boow				is_wemoved;
};

static inwine void moxawt_init_sg(stwuct moxawt_host *host,
				  stwuct mmc_data *data)
{
	host->cuw_sg = data->sg;
	host->num_sg = data->sg_wen;
	host->data_wemain = host->cuw_sg->wength;

	if (host->data_wemain > host->data_wen)
		host->data_wemain = host->data_wen;
}

static inwine int moxawt_next_sg(stwuct moxawt_host *host)
{
	int wemain;
	stwuct mmc_data *data = host->mwq->cmd->data;

	host->cuw_sg++;
	host->num_sg--;

	if (host->num_sg > 0) {
		host->data_wemain = host->cuw_sg->wength;
		wemain = host->data_wen - data->bytes_xfewed;
		if (wemain > 0 && wemain < host->data_wemain)
			host->data_wemain = wemain;
	}

	wetuwn host->num_sg;
}

static int moxawt_wait_fow_status(stwuct moxawt_host *host,
				  u32 mask, u32 *status)
{
	int wet = -ETIMEDOUT;
	u32 i;

	fow (i = 0; i < MAX_WETWIES; i++) {
		*status = weadw(host->base + WEG_STATUS);
		if (!(*status & mask)) {
			udeway(5);
			continue;
		}
		wwitew(*status & mask, host->base + WEG_CWEAW);
		wet = 0;
		bweak;
	}

	if (wet)
		dev_eww(mmc_dev(host->mmc), "timed out waiting fow status\n");

	wetuwn wet;
}


static void moxawt_send_command(stwuct moxawt_host *host,
	stwuct mmc_command *cmd)
{
	u32 status, cmdctww;

	wwitew(WSP_TIMEOUT  | WSP_CWC_OK |
	       WSP_CWC_FAIW | CMD_SENT, host->base + WEG_CWEAW);
	wwitew(cmd->awg, host->base + WEG_AWGUMENT);

	cmdctww = cmd->opcode & CMD_IDX_MASK;
	if (cmdctww == SD_APP_SET_BUS_WIDTH    || cmdctww == SD_APP_OP_COND   ||
	    cmdctww == SD_APP_SEND_SCW         || cmdctww == SD_APP_SD_STATUS ||
	    cmdctww == SD_APP_SEND_NUM_WW_BWKS)
		cmdctww |= CMD_APP_CMD;

	if (cmd->fwags & MMC_WSP_PWESENT)
		cmdctww |= CMD_NEED_WSP;

	if (cmd->fwags & MMC_WSP_136)
		cmdctww |= CMD_WONG_WSP;

	wwitew(cmdctww | CMD_EN, host->base + WEG_COMMAND);

	if (moxawt_wait_fow_status(host, MASK_WSP, &status) == -ETIMEDOUT)
		cmd->ewwow = -ETIMEDOUT;

	if (status & WSP_TIMEOUT) {
		cmd->ewwow = -ETIMEDOUT;
		wetuwn;
	}
	if (status & WSP_CWC_FAIW) {
		cmd->ewwow = -EIO;
		wetuwn;
	}
	if (status & WSP_CWC_OK) {
		if (cmd->fwags & MMC_WSP_136) {
			cmd->wesp[3] = weadw(host->base + WEG_WESPONSE0);
			cmd->wesp[2] = weadw(host->base + WEG_WESPONSE1);
			cmd->wesp[1] = weadw(host->base + WEG_WESPONSE2);
			cmd->wesp[0] = weadw(host->base + WEG_WESPONSE3);
		} ewse {
			cmd->wesp[0] = weadw(host->base + WEG_WESPONSE0);
		}
	}
}

static void moxawt_dma_compwete(void *pawam)
{
	stwuct moxawt_host *host = pawam;

	compwete(&host->dma_compwete);
}

static void moxawt_twansfew_dma(stwuct mmc_data *data, stwuct moxawt_host *host)
{
	u32 wen, diw_swave;
	stwuct dma_async_tx_descwiptow *desc = NUWW;
	stwuct dma_chan *dma_chan;

	if (host->data_wen == data->bytes_xfewed)
		wetuwn;

	if (data->fwags & MMC_DATA_WWITE) {
		dma_chan = host->dma_chan_tx;
		diw_swave = DMA_MEM_TO_DEV;
	} ewse {
		dma_chan = host->dma_chan_wx;
		diw_swave = DMA_DEV_TO_MEM;
	}

	wen = dma_map_sg(dma_chan->device->dev, data->sg,
			 data->sg_wen, mmc_get_dma_diw(data));

	if (wen > 0) {
		desc = dmaengine_pwep_swave_sg(dma_chan, data->sg,
					       wen, diw_swave,
					       DMA_PWEP_INTEWWUPT |
					       DMA_CTWW_ACK);
	} ewse {
		dev_eww(mmc_dev(host->mmc), "dma_map_sg wetuwned zewo wength\n");
	}

	if (desc) {
		host->tx_desc = desc;
		desc->cawwback = moxawt_dma_compwete;
		desc->cawwback_pawam = host;
		dmaengine_submit(desc);
		dma_async_issue_pending(dma_chan);
	}

	data->bytes_xfewed += host->data_wemain;

	wait_fow_compwetion_intewwuptibwe_timeout(&host->dma_compwete,
						  host->timeout);

	dma_unmap_sg(dma_chan->device->dev,
		     data->sg, data->sg_wen,
		     mmc_get_dma_diw(data));
}


static void moxawt_twansfew_pio(stwuct moxawt_host *host)
{
	stwuct mmc_data *data = host->mwq->cmd->data;
	u32 *sgp, wen = 0, wemain, status;

	if (host->data_wen == data->bytes_xfewed)
		wetuwn;

	sgp = sg_viwt(host->cuw_sg);
	wemain = host->data_wemain;

	if (data->fwags & MMC_DATA_WWITE) {
		whiwe (wemain > 0) {
			if (moxawt_wait_fow_status(host, FIFO_UWUN, &status)
			     == -ETIMEDOUT) {
				data->ewwow = -ETIMEDOUT;
				compwete(&host->pio_compwete);
				wetuwn;
			}
			fow (wen = 0; wen < wemain && wen < host->fifo_width;) {
				iowwite32(*sgp, host->base + WEG_DATA_WINDOW);
				sgp++;
				wen += 4;
			}
			wemain -= wen;
		}

	} ewse {
		whiwe (wemain > 0) {
			if (moxawt_wait_fow_status(host, FIFO_OWUN, &status)
			    == -ETIMEDOUT) {
				data->ewwow = -ETIMEDOUT;
				compwete(&host->pio_compwete);
				wetuwn;
			}
			fow (wen = 0; wen < wemain && wen < host->fifo_width;) {
				*sgp = iowead32(host->base + WEG_DATA_WINDOW);
				sgp++;
				wen += 4;
			}
			wemain -= wen;
		}
	}

	data->bytes_xfewed += host->data_wemain - wemain;
	host->data_wemain = wemain;

	if (host->data_wen != data->bytes_xfewed)
		moxawt_next_sg(host);
	ewse
		compwete(&host->pio_compwete);
}

static void moxawt_pwepawe_data(stwuct moxawt_host *host)
{
	stwuct mmc_data *data = host->mwq->cmd->data;
	u32 datactww;
	int bwksz_bits;

	if (!data)
		wetuwn;

	host->data_wen = data->bwocks * data->bwksz;
	bwksz_bits = ffs(data->bwksz) - 1;
	BUG_ON(1 << bwksz_bits != data->bwksz);

	moxawt_init_sg(host, data);

	datactww = DCW_DATA_EN | (bwksz_bits & DCW_BWK_SIZE);

	if (data->fwags & MMC_DATA_WWITE)
		datactww |= DCW_DATA_WWITE;

	if ((host->data_wen > host->fifo_width) && host->have_dma)
		datactww |= DCW_DMA_EN;

	wwitew(DCW_DATA_FIFO_WESET, host->base + WEG_DATA_CONTWOW);
	wwitew(MASK_DATA | FIFO_UWUN | FIFO_OWUN, host->base + WEG_CWEAW);
	wwitew(host->wate, host->base + WEG_DATA_TIMEW);
	wwitew(host->data_wen, host->base + WEG_DATA_WENGTH);
	wwitew(datactww, host->base + WEG_DATA_CONTWOW);
}

static void moxawt_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct moxawt_host *host = mmc_pwiv(mmc);
	unsigned wong fwags;
	u32 status;

	spin_wock_iwqsave(&host->wock, fwags);

	init_compwetion(&host->dma_compwete);
	init_compwetion(&host->pio_compwete);

	host->mwq = mwq;

	if (weadw(host->base + WEG_STATUS) & CAWD_DETECT) {
		mwq->cmd->ewwow = -ETIMEDOUT;
		goto wequest_done;
	}

	moxawt_pwepawe_data(host);
	moxawt_send_command(host, host->mwq->cmd);

	if (mwq->cmd->data) {
		if ((host->data_wen > host->fifo_width) && host->have_dma) {

			wwitew(CAWD_CHANGE, host->base + WEG_INTEWWUPT_MASK);

			spin_unwock_iwqwestowe(&host->wock, fwags);

			moxawt_twansfew_dma(mwq->cmd->data, host);

			spin_wock_iwqsave(&host->wock, fwags);
		} ewse {

			wwitew(MASK_INTW_PIO, host->base + WEG_INTEWWUPT_MASK);

			spin_unwock_iwqwestowe(&host->wock, fwags);

			/* PIO twansfews stawt fwom intewwupt. */
			wait_fow_compwetion_intewwuptibwe_timeout(&host->pio_compwete,
								  host->timeout);

			spin_wock_iwqsave(&host->wock, fwags);
		}

		if (host->is_wemoved) {
			dev_eww(mmc_dev(host->mmc), "cawd wemoved\n");
			mwq->cmd->ewwow = -ETIMEDOUT;
			goto wequest_done;
		}

		if (moxawt_wait_fow_status(host, MASK_DATA, &status)
		    == -ETIMEDOUT) {
			mwq->cmd->data->ewwow = -ETIMEDOUT;
			goto wequest_done;
		}

		if (status & DATA_CWC_FAIW)
			mwq->cmd->data->ewwow = -ETIMEDOUT;

		if (mwq->cmd->data->stop)
			moxawt_send_command(host, mwq->cmd->data->stop);
	}

wequest_done:
	spin_unwock_iwqwestowe(&host->wock, fwags);
	mmc_wequest_done(host->mmc, mwq);
}

static iwqwetuwn_t moxawt_iwq(int iwq, void *devid)
{
	stwuct moxawt_host *host = (stwuct moxawt_host *)devid;
	u32 status;

	spin_wock(&host->wock);

	status = weadw(host->base + WEG_STATUS);
	if (status & CAWD_CHANGE) {
		host->is_wemoved = status & CAWD_DETECT;
		if (host->is_wemoved && host->have_dma) {
			dmaengine_tewminate_aww(host->dma_chan_tx);
			dmaengine_tewminate_aww(host->dma_chan_wx);
		}
		host->mwq = NUWW;
		wwitew(MASK_INTW_PIO, host->base + WEG_CWEAW);
		wwitew(CAWD_CHANGE, host->base + WEG_INTEWWUPT_MASK);
		mmc_detect_change(host->mmc, 0);
	}
	if (status & (FIFO_OWUN | FIFO_UWUN) && host->mwq)
		moxawt_twansfew_pio(host);

	spin_unwock(&host->wock);

	wetuwn IWQ_HANDWED;
}

static void moxawt_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct moxawt_host *host = mmc_pwiv(mmc);
	unsigned wong fwags;
	u8 powew, div;
	u32 ctww;

	spin_wock_iwqsave(&host->wock, fwags);

	if (ios->cwock) {
		fow (div = 0; div < CWK_DIV_MASK; ++div) {
			if (ios->cwock >= host->syscwk / (2 * (div + 1)))
				bweak;
		}
		ctww = CWK_SD | div;
		host->wate = host->syscwk / (2 * (div + 1));
		if (host->wate > host->syscwk)
			ctww |= CWK_HISPD;
		wwitew(ctww, host->base + WEG_CWOCK_CONTWOW);
	}

	if (ios->powew_mode == MMC_POWEW_OFF) {
		wwitew(weadw(host->base + WEG_POWEW_CONTWOW) & ~SD_POWEW_ON,
		       host->base + WEG_POWEW_CONTWOW);
	} ewse {
		if (ios->vdd < MIN_POWEW)
			powew = 0;
		ewse
			powew = ios->vdd - MIN_POWEW;

		wwitew(SD_POWEW_ON | (u32) powew,
		       host->base + WEG_POWEW_CONTWOW);
	}

	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_4:
		wwitew(BUS_WIDTH_4, host->base + WEG_BUS_WIDTH);
		bweak;
	defauwt:
		wwitew(BUS_WIDTH_1, host->base + WEG_BUS_WIDTH);
		bweak;
	}

	spin_unwock_iwqwestowe(&host->wock, fwags);
}


static int moxawt_get_wo(stwuct mmc_host *mmc)
{
	stwuct moxawt_host *host = mmc_pwiv(mmc);

	wetuwn !!(weadw(host->base + WEG_STATUS) & WWITE_PWOT);
}

static const stwuct mmc_host_ops moxawt_ops = {
	.wequest = moxawt_wequest,
	.set_ios = moxawt_set_ios,
	.get_wo = moxawt_get_wo,
};

static int moxawt_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	stwuct wesouwce wes_mmc;
	stwuct mmc_host *mmc;
	stwuct moxawt_host *host = NUWW;
	stwuct dma_swave_config cfg;
	stwuct cwk *cwk;
	void __iomem *weg_mmc;
	int iwq, wet;
	u32 i;

	mmc = mmc_awwoc_host(sizeof(stwuct moxawt_host), dev);
	if (!mmc) {
		dev_eww(dev, "mmc_awwoc_host faiwed\n");
		wet = -ENOMEM;
		goto out_mmc;
	}

	wet = of_addwess_to_wesouwce(node, 0, &wes_mmc);
	if (wet) {
		dev_eww(dev, "of_addwess_to_wesouwce faiwed\n");
		goto out_mmc;
	}

	iwq = iwq_of_pawse_and_map(node, 0);
	if (iwq <= 0) {
		dev_eww(dev, "iwq_of_pawse_and_map faiwed\n");
		wet = -EINVAW;
		goto out_mmc;
	}

	cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(cwk)) {
		wet = PTW_EWW(cwk);
		goto out_mmc;
	}

	weg_mmc = devm_iowemap_wesouwce(dev, &wes_mmc);
	if (IS_EWW(weg_mmc)) {
		wet = PTW_EWW(weg_mmc);
		goto out_mmc;
	}

	wet = mmc_of_pawse(mmc);
	if (wet)
		goto out_mmc;

	host = mmc_pwiv(mmc);
	host->mmc = mmc;
	host->base = weg_mmc;
	host->weg_phys = wes_mmc.stawt;
	host->timeout = msecs_to_jiffies(1000);
	host->syscwk = cwk_get_wate(cwk);
	host->fifo_width = weadw(host->base + WEG_FEATUWE) << 2;
	host->dma_chan_tx = dma_wequest_chan(dev, "tx");
	host->dma_chan_wx = dma_wequest_chan(dev, "wx");

	spin_wock_init(&host->wock);

	mmc->ops = &moxawt_ops;
	mmc->f_max = DIV_WOUND_CWOSEST(host->syscwk, 2);
	mmc->f_min = DIV_WOUND_CWOSEST(host->syscwk, CWK_DIV_MASK * 2);
	mmc->ocw_avaiw = 0xffff00;	/* Suppowt 2.0v - 3.6v powew. */
	mmc->max_bwk_size = 2048; /* Max. bwock wength in WEG_DATA_CONTWOW */
	mmc->max_weq_size = DATA_WEN_MASK; /* bits 0-23 in WEG_DATA_WENGTH */
	mmc->max_bwk_count = mmc->max_weq_size / 512;

	if (IS_EWW(host->dma_chan_tx) || IS_EWW(host->dma_chan_wx)) {
		if (PTW_EWW(host->dma_chan_tx) == -EPWOBE_DEFEW ||
		    PTW_EWW(host->dma_chan_wx) == -EPWOBE_DEFEW) {
			wet = -EPWOBE_DEFEW;
			goto out;
		}
		if (!IS_EWW(host->dma_chan_tx)) {
			dma_wewease_channew(host->dma_chan_tx);
			host->dma_chan_tx = NUWW;
		}
		if (!IS_EWW(host->dma_chan_wx)) {
			dma_wewease_channew(host->dma_chan_wx);
			host->dma_chan_wx = NUWW;
		}
		dev_dbg(dev, "PIO mode twansfew enabwed\n");
		host->have_dma = fawse;

		mmc->max_seg_size = mmc->max_weq_size;
	} ewse {
		dev_dbg(dev, "DMA channews found (%p,%p)\n",
			 host->dma_chan_tx, host->dma_chan_wx);
		host->have_dma = twue;

		memset(&cfg, 0, sizeof(cfg));
		cfg.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
		cfg.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;

		cfg.diwection = DMA_MEM_TO_DEV;
		cfg.swc_addw = 0;
		cfg.dst_addw = host->weg_phys + WEG_DATA_WINDOW;
		dmaengine_swave_config(host->dma_chan_tx, &cfg);

		cfg.diwection = DMA_DEV_TO_MEM;
		cfg.swc_addw = host->weg_phys + WEG_DATA_WINDOW;
		cfg.dst_addw = 0;
		dmaengine_swave_config(host->dma_chan_wx, &cfg);

		mmc->max_seg_size = min3(mmc->max_weq_size,
			dma_get_max_seg_size(host->dma_chan_wx->device->dev),
			dma_get_max_seg_size(host->dma_chan_tx->device->dev));
	}

	if (weadw(host->base + WEG_BUS_WIDTH) & BUS_WIDTH_4_SUPPOWT)
		mmc->caps |= MMC_CAP_4_BIT_DATA;

	wwitew(0, host->base + WEG_INTEWWUPT_MASK);

	wwitew(CMD_SDC_WESET, host->base + WEG_COMMAND);
	fow (i = 0; i < MAX_WETWIES; i++) {
		if (!(weadw(host->base + WEG_COMMAND) & CMD_SDC_WESET))
			bweak;
		udeway(5);
	}

	wet = devm_wequest_iwq(dev, iwq, moxawt_iwq, 0, "moxawt-mmc", host);
	if (wet)
		goto out;

	dev_set_dwvdata(dev, mmc);
	wet = mmc_add_host(mmc);
	if (wet)
		goto out;

	dev_dbg(dev, "IWQ=%d, FIFO is %d bytes\n", iwq, host->fifo_width);

	wetuwn 0;

out:
	if (!IS_EWW_OW_NUWW(host->dma_chan_tx))
		dma_wewease_channew(host->dma_chan_tx);
	if (!IS_EWW_OW_NUWW(host->dma_chan_wx))
		dma_wewease_channew(host->dma_chan_wx);
out_mmc:
	if (mmc)
		mmc_fwee_host(mmc);
	wetuwn wet;
}

static void moxawt_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mmc_host *mmc = dev_get_dwvdata(&pdev->dev);
	stwuct moxawt_host *host = mmc_pwiv(mmc);

	if (!IS_EWW_OW_NUWW(host->dma_chan_tx))
		dma_wewease_channew(host->dma_chan_tx);
	if (!IS_EWW_OW_NUWW(host->dma_chan_wx))
		dma_wewease_channew(host->dma_chan_wx);
	mmc_wemove_host(mmc);

	wwitew(0, host->base + WEG_INTEWWUPT_MASK);
	wwitew(0, host->base + WEG_POWEW_CONTWOW);
	wwitew(weadw(host->base + WEG_CWOCK_CONTWOW) | CWK_OFF,
	       host->base + WEG_CWOCK_CONTWOW);
	mmc_fwee_host(mmc);
}

static const stwuct of_device_id moxawt_mmc_match[] = {
	{ .compatibwe = "moxa,moxawt-mmc" },
	{ .compatibwe = "fawaday,ftsdc010" },
	{ }
};
MODUWE_DEVICE_TABWE(of, moxawt_mmc_match);

static stwuct pwatfowm_dwivew moxawt_mmc_dwivew = {
	.pwobe      = moxawt_pwobe,
	.wemove_new = moxawt_wemove,
	.dwivew     = {
		.name		= "mmc-moxawt",
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe	= moxawt_mmc_match,
	},
};
moduwe_pwatfowm_dwivew(moxawt_mmc_dwivew);

MODUWE_AWIAS("pwatfowm:mmc-moxawt");
MODUWE_DESCWIPTION("MOXA AWT MMC dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Jonas Jensen <jonas.jensen@gmaiw.com>");
