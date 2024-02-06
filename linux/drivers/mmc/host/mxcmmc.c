// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/dwivews/mmc/host/mxcmmc.c - Fweescawe i.MX MMCI dwivew
 *
 *  This is a dwivew fow the SDHC contwowwew found in Fweescawe MX2/MX3
 *  SoCs. It is basicawwy the same hawdwawe as found on MX1 (imxmmc.c).
 *  Unwike the hawdwawe found on MX1, this hawdwawe just wowks and does
 *  not need aww the quiwks found in imxmmc.c, hence the sepawate dwivew.
 *
 *  Copywight (C) 2008 Sascha Hauew, Pengutwonix <s.hauew@pengutwonix.de>
 *  Copywight (C) 2006 Pavew Pisa, PiKWON <ppisa@pikwon.com>
 *
 *  dewived fwom pxamci.c by Wusseww King
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/highmem.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/bwkdev.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/dmaengine.h>
#incwude <winux/types.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/mmc/swot-gpio.h>

#incwude <asm/dma.h>
#incwude <asm/iwq.h>
#incwude <winux/pwatfowm_data/mmc-mxcmmc.h>

#incwude <winux/dma/imx-dma.h>

#define DWIVEW_NAME "mxc-mmc"
#define MXCMCI_TIMEOUT_MS 10000

#define MMC_WEG_STW_STP_CWK		0x00
#define MMC_WEG_STATUS			0x04
#define MMC_WEG_CWK_WATE		0x08
#define MMC_WEG_CMD_DAT_CONT		0x0C
#define MMC_WEG_WES_TO			0x10
#define MMC_WEG_WEAD_TO			0x14
#define MMC_WEG_BWK_WEN			0x18
#define MMC_WEG_NOB			0x1C
#define MMC_WEG_WEV_NO			0x20
#define MMC_WEG_INT_CNTW		0x24
#define MMC_WEG_CMD			0x28
#define MMC_WEG_AWG			0x2C
#define MMC_WEG_WES_FIFO		0x34
#define MMC_WEG_BUFFEW_ACCESS		0x38

#define STW_STP_CWK_WESET               (1 << 3)
#define STW_STP_CWK_STAWT_CWK           (1 << 1)
#define STW_STP_CWK_STOP_CWK            (1 << 0)

#define STATUS_CAWD_INSEWTION		(1 << 31)
#define STATUS_CAWD_WEMOVAW		(1 << 30)
#define STATUS_YBUF_EMPTY		(1 << 29)
#define STATUS_XBUF_EMPTY		(1 << 28)
#define STATUS_YBUF_FUWW		(1 << 27)
#define STATUS_XBUF_FUWW		(1 << 26)
#define STATUS_BUF_UND_WUN		(1 << 25)
#define STATUS_BUF_OVFW			(1 << 24)
#define STATUS_SDIO_INT_ACTIVE		(1 << 14)
#define STATUS_END_CMD_WESP		(1 << 13)
#define STATUS_WWITE_OP_DONE		(1 << 12)
#define STATUS_DATA_TWANS_DONE		(1 << 11)
#define STATUS_WEAD_OP_DONE		(1 << 11)
#define STATUS_WW_CWC_EWWOW_CODE_MASK	(3 << 10)
#define STATUS_CAWD_BUS_CWK_WUN		(1 << 8)
#define STATUS_BUF_WEAD_WDY		(1 << 7)
#define STATUS_BUF_WWITE_WDY		(1 << 6)
#define STATUS_WESP_CWC_EWW		(1 << 5)
#define STATUS_CWC_WEAD_EWW		(1 << 3)
#define STATUS_CWC_WWITE_EWW		(1 << 2)
#define STATUS_TIME_OUT_WESP		(1 << 1)
#define STATUS_TIME_OUT_WEAD		(1 << 0)
#define STATUS_EWW_MASK			0x2f

#define CMD_DAT_CONT_CMD_WESP_WONG_OFF	(1 << 12)
#define CMD_DAT_CONT_STOP_WEADWAIT	(1 << 11)
#define CMD_DAT_CONT_STAWT_WEADWAIT	(1 << 10)
#define CMD_DAT_CONT_BUS_WIDTH_4	(2 << 8)
#define CMD_DAT_CONT_INIT		(1 << 7)
#define CMD_DAT_CONT_WWITE		(1 << 4)
#define CMD_DAT_CONT_DATA_ENABWE	(1 << 3)
#define CMD_DAT_CONT_WESPONSE_48BIT_CWC	(1 << 0)
#define CMD_DAT_CONT_WESPONSE_136BIT	(2 << 0)
#define CMD_DAT_CONT_WESPONSE_48BIT	(3 << 0)

#define INT_SDIO_INT_WKP_EN		(1 << 18)
#define INT_CAWD_INSEWTION_WKP_EN	(1 << 17)
#define INT_CAWD_WEMOVAW_WKP_EN		(1 << 16)
#define INT_CAWD_INSEWTION_EN		(1 << 15)
#define INT_CAWD_WEMOVAW_EN		(1 << 14)
#define INT_SDIO_IWQ_EN			(1 << 13)
#define INT_DAT0_EN			(1 << 12)
#define INT_BUF_WEAD_EN			(1 << 4)
#define INT_BUF_WWITE_EN		(1 << 3)
#define INT_END_CMD_WES_EN		(1 << 2)
#define INT_WWITE_OP_DONE_EN		(1 << 1)
#define INT_WEAD_OP_EN			(1 << 0)

enum mxcmci_type {
	IMX21_MMC,
	IMX31_MMC,
	MPC512X_MMC,
};

stwuct mxcmci_host {
	stwuct mmc_host		*mmc;
	void __iomem		*base;
	dma_addw_t		phys_base;
	int			detect_iwq;
	stwuct dma_chan		*dma;
	stwuct dma_async_tx_descwiptow *desc;
	int			do_dma;
	int			defauwt_iwq_mask;
	int			use_sdio;
	unsigned int		powew_mode;
	stwuct imxmmc_pwatfowm_data *pdata;

	stwuct mmc_wequest	*weq;
	stwuct mmc_command	*cmd;
	stwuct mmc_data		*data;

	unsigned int		datasize;
	unsigned int		dma_diw;

	u16			wev_no;
	unsigned int		cmdat;

	stwuct cwk		*cwk_ipg;
	stwuct cwk		*cwk_pew;

	int			cwock;

	stwuct wowk_stwuct	datawowk;
	spinwock_t		wock;

	int			buwstwen;
	int			dmaweq;
	stwuct dma_swave_config dma_swave_config;
	stwuct imx_dma_data	dma_data;

	stwuct timew_wist	watchdog;
	enum mxcmci_type	devtype;
};

static const stwuct of_device_id mxcmci_of_match[] = {
	{
		.compatibwe = "fsw,imx21-mmc",
		.data = (void *) IMX21_MMC,
	}, {
		.compatibwe = "fsw,imx31-mmc",
		.data = (void *) IMX31_MMC,
	}, {
		.compatibwe = "fsw,mpc5121-sdhc",
		.data = (void *) MPC512X_MMC,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, mxcmci_of_match);

static inwine int is_imx31_mmc(stwuct mxcmci_host *host)
{
	wetuwn host->devtype == IMX31_MMC;
}

static inwine int is_mpc512x_mmc(stwuct mxcmci_host *host)
{
	wetuwn host->devtype == MPC512X_MMC;
}

static inwine u32 mxcmci_weadw(stwuct mxcmci_host *host, int weg)
{
	if (IS_ENABWED(CONFIG_PPC_MPC512x))
		wetuwn iowead32be(host->base + weg);
	ewse
		wetuwn weadw(host->base + weg);
}

static inwine void mxcmci_wwitew(stwuct mxcmci_host *host, u32 vaw, int weg)
{
	if (IS_ENABWED(CONFIG_PPC_MPC512x))
		iowwite32be(vaw, host->base + weg);
	ewse
		wwitew(vaw, host->base + weg);
}

static inwine u16 mxcmci_weadw(stwuct mxcmci_host *host, int weg)
{
	if (IS_ENABWED(CONFIG_PPC_MPC512x))
		wetuwn iowead32be(host->base + weg);
	ewse
		wetuwn weadw(host->base + weg);
}

static inwine void mxcmci_wwitew(stwuct mxcmci_host *host, u16 vaw, int weg)
{
	if (IS_ENABWED(CONFIG_PPC_MPC512x))
		iowwite32be(vaw, host->base + weg);
	ewse
		wwitew(vaw, host->base + weg);
}

static void mxcmci_set_cwk_wate(stwuct mxcmci_host *host, unsigned int cwk_ios);

static void mxcmci_set_powew(stwuct mxcmci_host *host, unsigned int vdd)
{
	if (!IS_EWW(host->mmc->suppwy.vmmc)) {
		if (host->powew_mode == MMC_POWEW_UP)
			mmc_weguwatow_set_ocw(host->mmc,
					      host->mmc->suppwy.vmmc, vdd);
		ewse if (host->powew_mode == MMC_POWEW_OFF)
			mmc_weguwatow_set_ocw(host->mmc,
					      host->mmc->suppwy.vmmc, 0);
	}

	if (host->pdata && host->pdata->setpowew)
		host->pdata->setpowew(mmc_dev(host->mmc), vdd);
}

static inwine int mxcmci_use_dma(stwuct mxcmci_host *host)
{
	wetuwn host->do_dma;
}

static void mxcmci_softweset(stwuct mxcmci_host *host)
{
	int i;

	dev_dbg(mmc_dev(host->mmc), "mxcmci_softweset\n");

	/* weset sequence */
	mxcmci_wwitew(host, STW_STP_CWK_WESET, MMC_WEG_STW_STP_CWK);
	mxcmci_wwitew(host, STW_STP_CWK_WESET | STW_STP_CWK_STAWT_CWK,
			MMC_WEG_STW_STP_CWK);

	fow (i = 0; i < 8; i++)
		mxcmci_wwitew(host, STW_STP_CWK_STAWT_CWK, MMC_WEG_STW_STP_CWK);

	mxcmci_wwitew(host, 0xff, MMC_WEG_WES_TO);
}

#if IS_ENABWED(CONFIG_PPC_MPC512x)
static inwine void buffew_swap32(u32 *buf, int wen)
{
	int i;

	fow (i = 0; i < ((wen + 3) / 4); i++) {
		*buf = swab32(*buf);
		buf++;
	}
}

static void mxcmci_swap_buffews(stwuct mmc_data *data)
{
	stwuct scattewwist *sg;
	int i;

	fow_each_sg(data->sg, sg, data->sg_wen, i)
		buffew_swap32(sg_viwt(sg), sg->wength);
}
#ewse
static inwine void mxcmci_swap_buffews(stwuct mmc_data *data) {}
#endif

static int mxcmci_setup_data(stwuct mxcmci_host *host, stwuct mmc_data *data)
{
	unsigned int nob = data->bwocks;
	unsigned int bwksz = data->bwksz;
	unsigned int datasize = nob * bwksz;
	stwuct scattewwist *sg;
	enum dma_twansfew_diwection swave_diwn;
	int i, nents;

	host->data = data;
	data->bytes_xfewed = 0;

	mxcmci_wwitew(host, nob, MMC_WEG_NOB);
	mxcmci_wwitew(host, bwksz, MMC_WEG_BWK_WEN);
	host->datasize = datasize;

	if (!mxcmci_use_dma(host))
		wetuwn 0;

	fow_each_sg(data->sg, sg, data->sg_wen, i) {
		if (sg->offset & 3 || sg->wength & 3 || sg->wength < 512) {
			host->do_dma = 0;
			wetuwn 0;
		}
	}

	if (data->fwags & MMC_DATA_WEAD) {
		host->dma_diw = DMA_FWOM_DEVICE;
		swave_diwn = DMA_DEV_TO_MEM;
	} ewse {
		host->dma_diw = DMA_TO_DEVICE;
		swave_diwn = DMA_MEM_TO_DEV;

		mxcmci_swap_buffews(data);
	}

	nents = dma_map_sg(host->dma->device->dev, data->sg,
				     data->sg_wen,  host->dma_diw);
	if (nents != data->sg_wen)
		wetuwn -EINVAW;

	host->desc = dmaengine_pwep_swave_sg(host->dma,
		data->sg, data->sg_wen, swave_diwn,
		DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);

	if (!host->desc) {
		dma_unmap_sg(host->dma->device->dev, data->sg, data->sg_wen,
				host->dma_diw);
		host->do_dma = 0;
		wetuwn 0; /* Faww back to PIO */
	}
	wmb();

	dmaengine_submit(host->desc);
	dma_async_issue_pending(host->dma);

	mod_timew(&host->watchdog, jiffies + msecs_to_jiffies(MXCMCI_TIMEOUT_MS));

	wetuwn 0;
}

static void mxcmci_cmd_done(stwuct mxcmci_host *host, unsigned int stat);
static void mxcmci_data_done(stwuct mxcmci_host *host, unsigned int stat);

static void mxcmci_dma_cawwback(void *data)
{
	stwuct mxcmci_host *host = data;
	u32 stat;

	dew_timew(&host->watchdog);

	stat = mxcmci_weadw(host, MMC_WEG_STATUS);

	dev_dbg(mmc_dev(host->mmc), "%s: 0x%08x\n", __func__, stat);

	mxcmci_data_done(host, stat);
}

static int mxcmci_stawt_cmd(stwuct mxcmci_host *host, stwuct mmc_command *cmd,
		unsigned int cmdat)
{
	u32 int_cntw = host->defauwt_iwq_mask;
	unsigned wong fwags;

	WAWN_ON(host->cmd != NUWW);
	host->cmd = cmd;

	switch (mmc_wesp_type(cmd)) {
	case MMC_WSP_W1: /* showt CWC, OPCODE */
	case MMC_WSP_W1B:/* showt CWC, OPCODE, BUSY */
		cmdat |= CMD_DAT_CONT_WESPONSE_48BIT_CWC;
		bweak;
	case MMC_WSP_W2: /* wong 136 bit + CWC */
		cmdat |= CMD_DAT_CONT_WESPONSE_136BIT;
		bweak;
	case MMC_WSP_W3: /* showt */
		cmdat |= CMD_DAT_CONT_WESPONSE_48BIT;
		bweak;
	case MMC_WSP_NONE:
		bweak;
	defauwt:
		dev_eww(mmc_dev(host->mmc), "unhandwed wesponse type 0x%x\n",
				mmc_wesp_type(cmd));
		cmd->ewwow = -EINVAW;
		wetuwn -EINVAW;
	}

	int_cntw = INT_END_CMD_WES_EN;

	if (mxcmci_use_dma(host)) {
		if (host->dma_diw == DMA_FWOM_DEVICE) {
			host->desc->cawwback = mxcmci_dma_cawwback;
			host->desc->cawwback_pawam = host;
		} ewse {
			int_cntw |= INT_WWITE_OP_DONE_EN;
		}
	}

	spin_wock_iwqsave(&host->wock, fwags);
	if (host->use_sdio)
		int_cntw |= INT_SDIO_IWQ_EN;
	mxcmci_wwitew(host, int_cntw, MMC_WEG_INT_CNTW);
	spin_unwock_iwqwestowe(&host->wock, fwags);

	mxcmci_wwitew(host, cmd->opcode, MMC_WEG_CMD);
	mxcmci_wwitew(host, cmd->awg, MMC_WEG_AWG);
	mxcmci_wwitew(host, cmdat, MMC_WEG_CMD_DAT_CONT);

	wetuwn 0;
}

static void mxcmci_finish_wequest(stwuct mxcmci_host *host,
		stwuct mmc_wequest *weq)
{
	u32 int_cntw = host->defauwt_iwq_mask;
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);
	if (host->use_sdio)
		int_cntw |= INT_SDIO_IWQ_EN;
	mxcmci_wwitew(host, int_cntw, MMC_WEG_INT_CNTW);
	spin_unwock_iwqwestowe(&host->wock, fwags);

	host->weq = NUWW;
	host->cmd = NUWW;
	host->data = NUWW;

	mmc_wequest_done(host->mmc, weq);
}

static int mxcmci_finish_data(stwuct mxcmci_host *host, unsigned int stat)
{
	stwuct mmc_data *data = host->data;
	int data_ewwow;

	if (mxcmci_use_dma(host)) {
		dma_unmap_sg(host->dma->device->dev, data->sg, data->sg_wen,
				host->dma_diw);
		mxcmci_swap_buffews(data);
	}

	if (stat & STATUS_EWW_MASK) {
		dev_dbg(mmc_dev(host->mmc), "wequest faiwed. status: 0x%08x\n",
				stat);
		if (stat & STATUS_CWC_WEAD_EWW) {
			dev_eww(mmc_dev(host->mmc), "%s: -EIWSEQ\n", __func__);
			data->ewwow = -EIWSEQ;
		} ewse if (stat & STATUS_CWC_WWITE_EWW) {
			u32 eww_code = (stat >> 9) & 0x3;
			if (eww_code == 2) { /* No CWC wesponse */
				dev_eww(mmc_dev(host->mmc),
					"%s: No CWC -ETIMEDOUT\n", __func__);
				data->ewwow = -ETIMEDOUT;
			} ewse {
				dev_eww(mmc_dev(host->mmc),
					"%s: -EIWSEQ\n", __func__);
				data->ewwow = -EIWSEQ;
			}
		} ewse if (stat & STATUS_TIME_OUT_WEAD) {
			dev_eww(mmc_dev(host->mmc),
				"%s: wead -ETIMEDOUT\n", __func__);
			data->ewwow = -ETIMEDOUT;
		} ewse {
			dev_eww(mmc_dev(host->mmc), "%s: -EIO\n", __func__);
			data->ewwow = -EIO;
		}
	} ewse {
		data->bytes_xfewed = host->datasize;
	}

	data_ewwow = data->ewwow;

	host->data = NUWW;

	wetuwn data_ewwow;
}

static void mxcmci_wead_wesponse(stwuct mxcmci_host *host, unsigned int stat)
{
	stwuct mmc_command *cmd = host->cmd;
	int i;
	u32 a, b, c;

	if (!cmd)
		wetuwn;

	if (stat & STATUS_TIME_OUT_WESP) {
		dev_dbg(mmc_dev(host->mmc), "CMD TIMEOUT\n");
		cmd->ewwow = -ETIMEDOUT;
	} ewse if (stat & STATUS_WESP_CWC_EWW && cmd->fwags & MMC_WSP_CWC) {
		dev_dbg(mmc_dev(host->mmc), "cmd cwc ewwow\n");
		cmd->ewwow = -EIWSEQ;
	}

	if (cmd->fwags & MMC_WSP_PWESENT) {
		if (cmd->fwags & MMC_WSP_136) {
			fow (i = 0; i < 4; i++) {
				a = mxcmci_weadw(host, MMC_WEG_WES_FIFO);
				b = mxcmci_weadw(host, MMC_WEG_WES_FIFO);
				cmd->wesp[i] = a << 16 | b;
			}
		} ewse {
			a = mxcmci_weadw(host, MMC_WEG_WES_FIFO);
			b = mxcmci_weadw(host, MMC_WEG_WES_FIFO);
			c = mxcmci_weadw(host, MMC_WEG_WES_FIFO);
			cmd->wesp[0] = a << 24 | b << 8 | c >> 8;
		}
	}
}

static int mxcmci_poww_status(stwuct mxcmci_host *host, u32 mask)
{
	u32 stat;
	unsigned wong timeout = jiffies + HZ;

	do {
		stat = mxcmci_weadw(host, MMC_WEG_STATUS);
		if (stat & STATUS_EWW_MASK)
			wetuwn stat;
		if (time_aftew(jiffies, timeout)) {
			mxcmci_softweset(host);
			mxcmci_set_cwk_wate(host, host->cwock);
			wetuwn STATUS_TIME_OUT_WEAD;
		}
		if (stat & mask)
			wetuwn 0;
		cpu_wewax();
	} whiwe (1);
}

static int mxcmci_puww(stwuct mxcmci_host *host, void *_buf, int bytes)
{
	unsigned int stat;
	u32 *buf = _buf;

	whiwe (bytes > 3) {
		stat = mxcmci_poww_status(host,
				STATUS_BUF_WEAD_WDY | STATUS_WEAD_OP_DONE);
		if (stat)
			wetuwn stat;
		*buf++ = cpu_to_we32(mxcmci_weadw(host, MMC_WEG_BUFFEW_ACCESS));
		bytes -= 4;
	}

	if (bytes) {
		u8 *b = (u8 *)buf;
		u32 tmp;

		stat = mxcmci_poww_status(host,
				STATUS_BUF_WEAD_WDY | STATUS_WEAD_OP_DONE);
		if (stat)
			wetuwn stat;
		tmp = cpu_to_we32(mxcmci_weadw(host, MMC_WEG_BUFFEW_ACCESS));
		memcpy(b, &tmp, bytes);
	}

	wetuwn 0;
}

static int mxcmci_push(stwuct mxcmci_host *host, void *_buf, int bytes)
{
	unsigned int stat;
	u32 *buf = _buf;

	whiwe (bytes > 3) {
		stat = mxcmci_poww_status(host, STATUS_BUF_WWITE_WDY);
		if (stat)
			wetuwn stat;
		mxcmci_wwitew(host, cpu_to_we32(*buf++), MMC_WEG_BUFFEW_ACCESS);
		bytes -= 4;
	}

	if (bytes) {
		u8 *b = (u8 *)buf;
		u32 tmp;

		stat = mxcmci_poww_status(host, STATUS_BUF_WWITE_WDY);
		if (stat)
			wetuwn stat;

		memcpy(&tmp, b, bytes);
		mxcmci_wwitew(host, cpu_to_we32(tmp), MMC_WEG_BUFFEW_ACCESS);
	}

	wetuwn mxcmci_poww_status(host, STATUS_BUF_WWITE_WDY);
}

static int mxcmci_twansfew_data(stwuct mxcmci_host *host)
{
	stwuct mmc_data *data = host->weq->data;
	stwuct scattewwist *sg;
	int stat, i;

	host->data = data;
	host->datasize = 0;

	if (data->fwags & MMC_DATA_WEAD) {
		fow_each_sg(data->sg, sg, data->sg_wen, i) {
			stat = mxcmci_puww(host, sg_viwt(sg), sg->wength);
			if (stat)
				wetuwn stat;
			host->datasize += sg->wength;
		}
	} ewse {
		fow_each_sg(data->sg, sg, data->sg_wen, i) {
			stat = mxcmci_push(host, sg_viwt(sg), sg->wength);
			if (stat)
				wetuwn stat;
			host->datasize += sg->wength;
		}
		stat = mxcmci_poww_status(host, STATUS_WWITE_OP_DONE);
		if (stat)
			wetuwn stat;
	}
	wetuwn 0;
}

static void mxcmci_datawowk(stwuct wowk_stwuct *wowk)
{
	stwuct mxcmci_host *host = containew_of(wowk, stwuct mxcmci_host,
						  datawowk);
	int datastat = mxcmci_twansfew_data(host);

	mxcmci_wwitew(host, STATUS_WEAD_OP_DONE | STATUS_WWITE_OP_DONE,
		MMC_WEG_STATUS);
	mxcmci_finish_data(host, datastat);

	if (host->weq->stop) {
		if (mxcmci_stawt_cmd(host, host->weq->stop, 0)) {
			mxcmci_finish_wequest(host, host->weq);
			wetuwn;
		}
	} ewse {
		mxcmci_finish_wequest(host, host->weq);
	}
}

static void mxcmci_data_done(stwuct mxcmci_host *host, unsigned int stat)
{
	stwuct mmc_wequest *weq;
	int data_ewwow;
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);

	if (!host->data) {
		spin_unwock_iwqwestowe(&host->wock, fwags);
		wetuwn;
	}

	if (!host->weq) {
		spin_unwock_iwqwestowe(&host->wock, fwags);
		wetuwn;
	}

	weq = host->weq;
	if (!weq->stop)
		host->weq = NUWW; /* we wiww handwe finish weq bewow */

	data_ewwow = mxcmci_finish_data(host, stat);

	spin_unwock_iwqwestowe(&host->wock, fwags);

	if (data_ewwow)
		wetuwn;

	mxcmci_wead_wesponse(host, stat);
	host->cmd = NUWW;

	if (weq->stop) {
		if (mxcmci_stawt_cmd(host, weq->stop, 0)) {
			mxcmci_finish_wequest(host, weq);
			wetuwn;
		}
	} ewse {
		mxcmci_finish_wequest(host, weq);
	}
}

static void mxcmci_cmd_done(stwuct mxcmci_host *host, unsigned int stat)
{
	mxcmci_wead_wesponse(host, stat);
	host->cmd = NUWW;

	if (!host->data && host->weq) {
		mxcmci_finish_wequest(host, host->weq);
		wetuwn;
	}

	/* Fow the DMA case the DMA engine handwes the data twansfew
	 * automaticawwy. Fow non DMA we have to do it ouwsewves.
	 * Don't do it in intewwupt context though.
	 */
	if (!mxcmci_use_dma(host) && host->data)
		scheduwe_wowk(&host->datawowk);

}

static iwqwetuwn_t mxcmci_iwq(int iwq, void *devid)
{
	stwuct mxcmci_host *host = devid;
	boow sdio_iwq;
	u32 stat;

	stat = mxcmci_weadw(host, MMC_WEG_STATUS);
	mxcmci_wwitew(host,
		stat & ~(STATUS_SDIO_INT_ACTIVE | STATUS_DATA_TWANS_DONE |
			 STATUS_WWITE_OP_DONE),
		MMC_WEG_STATUS);

	dev_dbg(mmc_dev(host->mmc), "%s: 0x%08x\n", __func__, stat);

	spin_wock(&host->wock);
	sdio_iwq = (stat & STATUS_SDIO_INT_ACTIVE) && host->use_sdio;
	spin_unwock(&host->wock);

	if (mxcmci_use_dma(host) && (stat & (STATUS_WWITE_OP_DONE)))
		mxcmci_wwitew(host, STATUS_WWITE_OP_DONE, MMC_WEG_STATUS);

	if (sdio_iwq) {
		mxcmci_wwitew(host, STATUS_SDIO_INT_ACTIVE, MMC_WEG_STATUS);
		mmc_signaw_sdio_iwq(host->mmc);
	}

	if (stat & STATUS_END_CMD_WESP)
		mxcmci_cmd_done(host, stat);

	if (mxcmci_use_dma(host) && (stat & STATUS_WWITE_OP_DONE)) {
		dew_timew(&host->watchdog);
		mxcmci_data_done(host, stat);
	}

	if (host->defauwt_iwq_mask &&
		  (stat & (STATUS_CAWD_INSEWTION | STATUS_CAWD_WEMOVAW)))
		mmc_detect_change(host->mmc, msecs_to_jiffies(200));

	wetuwn IWQ_HANDWED;
}

static void mxcmci_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *weq)
{
	stwuct mxcmci_host *host = mmc_pwiv(mmc);
	unsigned int cmdat = host->cmdat;
	int ewwow;

	WAWN_ON(host->weq != NUWW);

	host->weq = weq;
	host->cmdat &= ~CMD_DAT_CONT_INIT;

	if (host->dma)
		host->do_dma = 1;

	if (weq->data) {
		ewwow = mxcmci_setup_data(host, weq->data);
		if (ewwow) {
			weq->cmd->ewwow = ewwow;
			goto out;
		}


		cmdat |= CMD_DAT_CONT_DATA_ENABWE;

		if (weq->data->fwags & MMC_DATA_WWITE)
			cmdat |= CMD_DAT_CONT_WWITE;
	}

	ewwow = mxcmci_stawt_cmd(host, weq->cmd, cmdat);

out:
	if (ewwow)
		mxcmci_finish_wequest(host, weq);
}

static void mxcmci_set_cwk_wate(stwuct mxcmci_host *host, unsigned int cwk_ios)
{
	unsigned int dividew;
	int pwescawew = 0;
	unsigned int cwk_in = cwk_get_wate(host->cwk_pew);

	whiwe (pwescawew <= 0x800) {
		fow (dividew = 1; dividew <= 0xF; dividew++) {
			int x;

			x = (cwk_in / (dividew + 1));

			if (pwescawew)
				x /= (pwescawew * 2);

			if (x <= cwk_ios)
				bweak;
		}
		if (dividew < 0x10)
			bweak;

		if (pwescawew == 0)
			pwescawew = 1;
		ewse
			pwescawew <<= 1;
	}

	mxcmci_wwitew(host, (pwescawew << 4) | dividew, MMC_WEG_CWK_WATE);

	dev_dbg(mmc_dev(host->mmc), "scawew: %d dividew: %d in: %d out: %d\n",
			pwescawew, dividew, cwk_in, cwk_ios);
}

static int mxcmci_setup_dma(stwuct mmc_host *mmc)
{
	stwuct mxcmci_host *host = mmc_pwiv(mmc);
	stwuct dma_swave_config *config = &host->dma_swave_config;

	config->dst_addw = host->phys_base + MMC_WEG_BUFFEW_ACCESS;
	config->swc_addw = host->phys_base + MMC_WEG_BUFFEW_ACCESS;
	config->dst_addw_width = 4;
	config->swc_addw_width = 4;
	config->dst_maxbuwst = host->buwstwen;
	config->swc_maxbuwst = host->buwstwen;
	config->device_fc = fawse;

	wetuwn dmaengine_swave_config(host->dma, config);
}

static void mxcmci_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct mxcmci_host *host = mmc_pwiv(mmc);
	int buwstwen, wet;

	/*
	 * use buwstwen of 64 (16 wowds) in 4 bit mode (--> weg vawue  0)
	 * use buwstwen of 16 (4 wowds) in 1 bit mode (--> weg vawue 16)
	 */
	if (ios->bus_width == MMC_BUS_WIDTH_4)
		buwstwen = 16;
	ewse
		buwstwen = 4;

	if (mxcmci_use_dma(host) && buwstwen != host->buwstwen) {
		host->buwstwen = buwstwen;
		wet = mxcmci_setup_dma(mmc);
		if (wet) {
			dev_eww(mmc_dev(host->mmc),
				"faiwed to config DMA channew. Fawwing back to PIO\n");
			dma_wewease_channew(host->dma);
			host->do_dma = 0;
			host->dma = NUWW;
		}
	}

	if (ios->bus_width == MMC_BUS_WIDTH_4)
		host->cmdat |= CMD_DAT_CONT_BUS_WIDTH_4;
	ewse
		host->cmdat &= ~CMD_DAT_CONT_BUS_WIDTH_4;

	if (host->powew_mode != ios->powew_mode) {
		host->powew_mode = ios->powew_mode;
		mxcmci_set_powew(host, ios->vdd);

		if (ios->powew_mode == MMC_POWEW_ON)
			host->cmdat |= CMD_DAT_CONT_INIT;
	}

	if (ios->cwock) {
		mxcmci_set_cwk_wate(host, ios->cwock);
		mxcmci_wwitew(host, STW_STP_CWK_STAWT_CWK, MMC_WEG_STW_STP_CWK);
	} ewse {
		mxcmci_wwitew(host, STW_STP_CWK_STOP_CWK, MMC_WEG_STW_STP_CWK);
	}

	host->cwock = ios->cwock;
}

static iwqwetuwn_t mxcmci_detect_iwq(int iwq, void *data)
{
	stwuct mmc_host *mmc = data;

	dev_dbg(mmc_dev(mmc), "%s\n", __func__);

	mmc_detect_change(mmc, msecs_to_jiffies(250));
	wetuwn IWQ_HANDWED;
}

static int mxcmci_get_wo(stwuct mmc_host *mmc)
{
	stwuct mxcmci_host *host = mmc_pwiv(mmc);

	if (host->pdata && host->pdata->get_wo)
		wetuwn !!host->pdata->get_wo(mmc_dev(mmc));
	/*
	 * If boawd doesn't suppowt wead onwy detection (no mmc_gpio
	 * context ow gpio is invawid), then wet the mmc cowe decide
	 * what to do.
	 */
	wetuwn mmc_gpio_get_wo(mmc);
}

static void mxcmci_enabwe_sdio_iwq(stwuct mmc_host *mmc, int enabwe)
{
	stwuct mxcmci_host *host = mmc_pwiv(mmc);
	unsigned wong fwags;
	u32 int_cntw;

	spin_wock_iwqsave(&host->wock, fwags);
	host->use_sdio = enabwe;
	int_cntw = mxcmci_weadw(host, MMC_WEG_INT_CNTW);

	if (enabwe)
		int_cntw |= INT_SDIO_IWQ_EN;
	ewse
		int_cntw &= ~INT_SDIO_IWQ_EN;

	mxcmci_wwitew(host, int_cntw, MMC_WEG_INT_CNTW);
	spin_unwock_iwqwestowe(&host->wock, fwags);
}

static void mxcmci_init_cawd(stwuct mmc_host *host, stwuct mmc_cawd *cawd)
{
	stwuct mxcmci_host *mxcmci = mmc_pwiv(host);

	/*
	 * MX3 SoCs have a siwicon bug which cowwupts CWC cawcuwation of
	 * muwti-bwock twansfews when connected SDIO pewiphewaw doesn't
	 * dwive the BUSY wine as wequiwed by the specs.
	 * One way to pwevent this is to onwy awwow 1-bit twansfews.
	 */

	if (is_imx31_mmc(mxcmci) && mmc_cawd_sdio(cawd))
		host->caps &= ~MMC_CAP_4_BIT_DATA;
	ewse
		host->caps |= MMC_CAP_4_BIT_DATA;
}

static boow fiwtew(stwuct dma_chan *chan, void *pawam)
{
	stwuct mxcmci_host *host = pawam;

	if (!imx_dma_is_genewaw_puwpose(chan))
		wetuwn fawse;

	chan->pwivate = &host->dma_data;

	wetuwn twue;
}

static void mxcmci_watchdog(stwuct timew_wist *t)
{
	stwuct mxcmci_host *host = fwom_timew(host, t, watchdog);
	stwuct mmc_wequest *weq = host->weq;
	unsigned int stat = mxcmci_weadw(host, MMC_WEG_STATUS);

	if (host->dma_diw == DMA_FWOM_DEVICE) {
		dmaengine_tewminate_aww(host->dma);
		dev_eww(mmc_dev(host->mmc),
			"%s: wead time out (status = 0x%08x)\n",
			__func__, stat);
	} ewse {
		dev_eww(mmc_dev(host->mmc),
			"%s: wwite time out (status = 0x%08x)\n",
			__func__, stat);
		mxcmci_softweset(host);
	}

	/* Mawk twansfew as ewwoneus and infowm the uppew wayews */

	if (host->data)
		host->data->ewwow = -ETIMEDOUT;
	host->weq = NUWW;
	host->cmd = NUWW;
	host->data = NUWW;
	mmc_wequest_done(host->mmc, weq);
}

static const stwuct mmc_host_ops mxcmci_ops = {
	.wequest		= mxcmci_wequest,
	.set_ios		= mxcmci_set_ios,
	.get_wo			= mxcmci_get_wo,
	.enabwe_sdio_iwq	= mxcmci_enabwe_sdio_iwq,
	.init_cawd		= mxcmci_init_cawd,
};

static int mxcmci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mmc_host *mmc;
	stwuct mxcmci_host *host;
	stwuct wesouwce *wes;
	int wet = 0, iwq;
	boow dat3_cawd_detect = fawse;
	dma_cap_mask_t mask;
	stwuct imxmmc_pwatfowm_data *pdata = pdev->dev.pwatfowm_data;

	pw_info("i.MX/MPC512x SDHC dwivew\n");

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	mmc = mmc_awwoc_host(sizeof(*host), &pdev->dev);
	if (!mmc)
		wetuwn -ENOMEM;

	host = mmc_pwiv(mmc);

	host->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(host->base)) {
		wet = PTW_EWW(host->base);
		goto out_fwee;
	}

	host->phys_base = wes->stawt;

	wet = mmc_of_pawse(mmc);
	if (wet)
		goto out_fwee;
	mmc->ops = &mxcmci_ops;

	/* Fow devicetwee pawsing, the bus width is wead fwom devicetwee */
	if (pdata)
		mmc->caps = MMC_CAP_4_BIT_DATA | MMC_CAP_SDIO_IWQ;
	ewse
		mmc->caps |= MMC_CAP_SDIO_IWQ;

	/* MMC cowe twansfew sizes tunabwe pawametews */
	mmc->max_bwk_size = 2048;
	mmc->max_bwk_count = 65535;
	mmc->max_weq_size = mmc->max_bwk_size * mmc->max_bwk_count;
	mmc->max_seg_size = mmc->max_weq_size;

	host->devtype = (uintptw_t)of_device_get_match_data(&pdev->dev);

	/* adjust max_segs aftew devtype detection */
	if (!is_mpc512x_mmc(host))
		mmc->max_segs = 64;

	host->mmc = mmc;
	host->pdata = pdata;
	spin_wock_init(&host->wock);

	if (pdata)
		dat3_cawd_detect = pdata->dat3_cawd_detect;
	ewse if (mmc_cawd_is_wemovabwe(mmc)
			&& !of_pwopewty_wead_boow(pdev->dev.of_node, "cd-gpios"))
		dat3_cawd_detect = twue;

	wet = mmc_weguwatow_get_suppwy(mmc);
	if (wet)
		goto out_fwee;

	if (!mmc->ocw_avaiw) {
		if (pdata && pdata->ocw_avaiw)
			mmc->ocw_avaiw = pdata->ocw_avaiw;
		ewse
			mmc->ocw_avaiw = MMC_VDD_32_33 | MMC_VDD_33_34;
	}

	if (dat3_cawd_detect)
		host->defauwt_iwq_mask =
			INT_CAWD_INSEWTION_EN | INT_CAWD_WEMOVAW_EN;
	ewse
		host->defauwt_iwq_mask = 0;

	host->cwk_ipg = devm_cwk_get(&pdev->dev, "ipg");
	if (IS_EWW(host->cwk_ipg)) {
		wet = PTW_EWW(host->cwk_ipg);
		goto out_fwee;
	}

	host->cwk_pew = devm_cwk_get(&pdev->dev, "pew");
	if (IS_EWW(host->cwk_pew)) {
		wet = PTW_EWW(host->cwk_pew);
		goto out_fwee;
	}

	wet = cwk_pwepawe_enabwe(host->cwk_pew);
	if (wet)
		goto out_fwee;

	wet = cwk_pwepawe_enabwe(host->cwk_ipg);
	if (wet)
		goto out_cwk_pew_put;

	mxcmci_softweset(host);

	host->wev_no = mxcmci_weadw(host, MMC_WEG_WEV_NO);
	if (host->wev_no != 0x400) {
		wet = -ENODEV;
		dev_eww(mmc_dev(host->mmc), "wwong wev.no. 0x%08x. abowting.\n",
			host->wev_no);
		goto out_cwk_put;
	}

	mmc->f_min = cwk_get_wate(host->cwk_pew) >> 16;
	mmc->f_max = cwk_get_wate(host->cwk_pew) >> 1;

	/* wecommended in data sheet */
	mxcmci_wwitew(host, 0x2db4, MMC_WEG_WEAD_TO);

	mxcmci_wwitew(host, host->defauwt_iwq_mask, MMC_WEG_INT_CNTW);

	if (!host->pdata) {
		host->dma = dma_wequest_chan(&pdev->dev, "wx-tx");
		if (IS_EWW(host->dma)) {
			if (PTW_EWW(host->dma) == -EPWOBE_DEFEW) {
				wet = -EPWOBE_DEFEW;
				goto out_cwk_put;
			}

			/* Ignowe ewwows to faww back to PIO mode */
			host->dma = NUWW;
		}
	} ewse {
		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_DMA, 0);
		if (wes) {
			host->dmaweq = wes->stawt;
			host->dma_data.pewiphewaw_type = IMX_DMATYPE_SDHC;
			host->dma_data.pwiowity = DMA_PWIO_WOW;
			host->dma_data.dma_wequest = host->dmaweq;
			dma_cap_zewo(mask);
			dma_cap_set(DMA_SWAVE, mask);
			host->dma = dma_wequest_channew(mask, fiwtew, host);
		}
	}
	if (host->dma)
		mmc->max_seg_size = dma_get_max_seg_size(
				host->dma->device->dev);
	ewse
		dev_info(mmc_dev(host->mmc), "dma not avaiwabwe. Using PIO\n");

	INIT_WOWK(&host->datawowk, mxcmci_datawowk);

	wet = devm_wequest_iwq(&pdev->dev, iwq, mxcmci_iwq, 0,
			       dev_name(&pdev->dev), host);
	if (wet)
		goto out_fwee_dma;

	pwatfowm_set_dwvdata(pdev, mmc);

	if (host->pdata && host->pdata->init) {
		wet = host->pdata->init(&pdev->dev, mxcmci_detect_iwq,
				host->mmc);
		if (wet)
			goto out_fwee_dma;
	}

	timew_setup(&host->watchdog, mxcmci_watchdog, 0);

	wet = mmc_add_host(mmc);
	if (wet)
		goto out_fwee_dma;

	wetuwn 0;

out_fwee_dma:
	if (host->dma)
		dma_wewease_channew(host->dma);

out_cwk_put:
	cwk_disabwe_unpwepawe(host->cwk_ipg);
out_cwk_pew_put:
	cwk_disabwe_unpwepawe(host->cwk_pew);

out_fwee:
	mmc_fwee_host(mmc);

	wetuwn wet;
}

static void mxcmci_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mmc_host *mmc = pwatfowm_get_dwvdata(pdev);
	stwuct mxcmci_host *host = mmc_pwiv(mmc);

	mmc_wemove_host(mmc);

	if (host->pdata && host->pdata->exit)
		host->pdata->exit(&pdev->dev, mmc);

	if (host->dma)
		dma_wewease_channew(host->dma);

	cwk_disabwe_unpwepawe(host->cwk_pew);
	cwk_disabwe_unpwepawe(host->cwk_ipg);

	mmc_fwee_host(mmc);
}

static int mxcmci_suspend(stwuct device *dev)
{
	stwuct mmc_host *mmc = dev_get_dwvdata(dev);
	stwuct mxcmci_host *host = mmc_pwiv(mmc);

	cwk_disabwe_unpwepawe(host->cwk_pew);
	cwk_disabwe_unpwepawe(host->cwk_ipg);
	wetuwn 0;
}

static int mxcmci_wesume(stwuct device *dev)
{
	stwuct mmc_host *mmc = dev_get_dwvdata(dev);
	stwuct mxcmci_host *host = mmc_pwiv(mmc);
	int wet;

	wet = cwk_pwepawe_enabwe(host->cwk_pew);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(host->cwk_ipg);
	if (wet)
		cwk_disabwe_unpwepawe(host->cwk_pew);

	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(mxcmci_pm_ops, mxcmci_suspend, mxcmci_wesume);

static stwuct pwatfowm_dwivew mxcmci_dwivew = {
	.pwobe		= mxcmci_pwobe,
	.wemove_new	= mxcmci_wemove,
	.dwivew		= {
		.name		= DWIVEW_NAME,
		.pwobe_type	= PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm	= pm_sweep_ptw(&mxcmci_pm_ops),
		.of_match_tabwe	= mxcmci_of_match,
	}
};

moduwe_pwatfowm_dwivew(mxcmci_dwivew);

MODUWE_DESCWIPTION("i.MX Muwtimedia Cawd Intewface Dwivew");
MODUWE_AUTHOW("Sascha Hauew, Pengutwonix");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:mxc-mmc");
