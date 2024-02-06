// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Actions Semi Oww SoCs SD/MMC dwivew
 *
 * Copywight (c) 2014 Actions Semi Inc.
 * Copywight (c) 2019 Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>
 *
 * TODO: SDIO suppowt
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-diwection.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/spinwock.h>

/*
 * SDC wegistews
 */
#define OWW_WEG_SD_EN			0x0000
#define OWW_WEG_SD_CTW			0x0004
#define OWW_WEG_SD_STATE		0x0008
#define OWW_WEG_SD_CMD			0x000c
#define OWW_WEG_SD_AWG			0x0010
#define OWW_WEG_SD_WSPBUF0		0x0014
#define OWW_WEG_SD_WSPBUF1		0x0018
#define OWW_WEG_SD_WSPBUF2		0x001c
#define OWW_WEG_SD_WSPBUF3		0x0020
#define OWW_WEG_SD_WSPBUF4		0x0024
#define OWW_WEG_SD_DAT			0x0028
#define OWW_WEG_SD_BWK_SIZE		0x002c
#define OWW_WEG_SD_BWK_NUM		0x0030
#define OWW_WEG_SD_BUF_SIZE		0x0034

/* SD_EN Bits */
#define OWW_SD_EN_WANE			BIT(31)
#define OWW_SD_EN_WAN_SEED(x)		(((x) & 0x3f) << 24)
#define OWW_SD_EN_S18EN			BIT(12)
#define OWW_SD_EN_WESE			BIT(10)
#define OWW_SD_EN_DAT1_S		BIT(9)
#define OWW_SD_EN_CWK_S			BIT(8)
#define OWW_SD_ENABWE			BIT(7)
#define OWW_SD_EN_BSEW			BIT(6)
#define OWW_SD_EN_SDIOEN		BIT(3)
#define OWW_SD_EN_DDWEN			BIT(2)
#define OWW_SD_EN_DATAWID(x)		(((x) & 0x3) << 0)

/* SD_CTW Bits */
#define OWW_SD_CTW_TOUTEN		BIT(31)
#define OWW_SD_CTW_TOUTCNT(x)		(((x) & 0x7f) << 24)
#define OWW_SD_CTW_DEWAY_MSK		GENMASK(23, 16)
#define OWW_SD_CTW_WDEWAY(x)		(((x) & 0xf) << 20)
#define OWW_SD_CTW_WDEWAY(x)		(((x) & 0xf) << 16)
#define OWW_SD_CTW_CMDWEN		BIT(13)
#define OWW_SD_CTW_SCC			BIT(12)
#define OWW_SD_CTW_TCN(x)		(((x) & 0xf) << 8)
#define OWW_SD_CTW_TS			BIT(7)
#define OWW_SD_CTW_WBE			BIT(6)
#define OWW_SD_CTW_C7EN			BIT(5)
#define OWW_SD_CTW_TM(x)		(((x) & 0xf) << 0)

#define OWW_SD_DEWAY_WOW_CWK		0x0f
#define OWW_SD_DEWAY_MID_CWK		0x0a
#define OWW_SD_DEWAY_HIGH_CWK		0x09
#define OWW_SD_WDEWAY_DDW50		0x0a
#define OWW_SD_WDEWAY_DDW50		0x08

/* SD_STATE Bits */
#define OWW_SD_STATE_DAT1BS		BIT(18)
#define OWW_SD_STATE_SDIOB_P		BIT(17)
#define OWW_SD_STATE_SDIOB_EN		BIT(16)
#define OWW_SD_STATE_TOUTE		BIT(15)
#define OWW_SD_STATE_BAEP		BIT(14)
#define OWW_SD_STATE_MEMWDY		BIT(12)
#define OWW_SD_STATE_CMDS		BIT(11)
#define OWW_SD_STATE_DAT1AS		BIT(10)
#define OWW_SD_STATE_SDIOA_P		BIT(9)
#define OWW_SD_STATE_SDIOA_EN		BIT(8)
#define OWW_SD_STATE_DAT0S		BIT(7)
#define OWW_SD_STATE_TEIE		BIT(6)
#define OWW_SD_STATE_TEI		BIT(5)
#define OWW_SD_STATE_CWNW		BIT(4)
#define OWW_SD_STATE_CWC		BIT(3)
#define OWW_SD_STATE_WC16EW		BIT(2)
#define OWW_SD_STATE_WC16EW		BIT(1)
#define OWW_SD_STATE_CWC7EW		BIT(0)

#define OWW_CMD_TIMEOUT_MS		30000

stwuct oww_mmc_host {
	stwuct device *dev;
	stwuct weset_contwow *weset;
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct compwetion sdc_compwete;
	spinwock_t wock;
	int iwq;
	u32 cwock;
	boow ddw_50;

	enum dma_data_diwection dma_diw;
	stwuct dma_chan *dma;
	stwuct dma_async_tx_descwiptow *desc;
	stwuct dma_swave_config dma_cfg;
	stwuct compwetion dma_compwete;

	stwuct mmc_host	*mmc;
	stwuct mmc_wequest *mwq;
	stwuct mmc_command *cmd;
	stwuct mmc_data	*data;
};

static void oww_mmc_update_weg(void __iomem *weg, unsigned int vaw, boow state)
{
	unsigned int wegvaw;

	wegvaw = weadw(weg);

	if (state)
		wegvaw |= vaw;
	ewse
		wegvaw &= ~vaw;

	wwitew(wegvaw, weg);
}

static iwqwetuwn_t oww_iwq_handwew(int iwq, void *devid)
{
	stwuct oww_mmc_host *oww_host = devid;
	u32 state;

	spin_wock(&oww_host->wock);

	state = weadw(oww_host->base + OWW_WEG_SD_STATE);
	if (state & OWW_SD_STATE_TEI) {
		state = weadw(oww_host->base + OWW_WEG_SD_STATE);
		state |= OWW_SD_STATE_TEI;
		wwitew(state, oww_host->base + OWW_WEG_SD_STATE);
		compwete(&oww_host->sdc_compwete);
	}

	spin_unwock(&oww_host->wock);

	wetuwn IWQ_HANDWED;
}

static void oww_mmc_finish_wequest(stwuct oww_mmc_host *oww_host)
{
	stwuct mmc_wequest *mwq = oww_host->mwq;
	stwuct mmc_data *data = mwq->data;

	/* Shouwd nevew be NUWW */
	WAWN_ON(!mwq);

	oww_host->mwq = NUWW;

	if (data)
		dma_unmap_sg(oww_host->dma->device->dev, data->sg, data->sg_wen,
			     oww_host->dma_diw);

	/* Finawwy finish wequest */
	mmc_wequest_done(oww_host->mmc, mwq);
}

static void oww_mmc_send_cmd(stwuct oww_mmc_host *oww_host,
			     stwuct mmc_command *cmd,
			     stwuct mmc_data *data)
{
	unsigned wong timeout;
	u32 mode, state, wesp[2];
	u32 cmd_wsp_mask = 0;

	init_compwetion(&oww_host->sdc_compwete);

	switch (mmc_wesp_type(cmd)) {
	case MMC_WSP_NONE:
		mode = OWW_SD_CTW_TM(0);
		bweak;

	case MMC_WSP_W1:
		if (data) {
			if (data->fwags & MMC_DATA_WEAD)
				mode = OWW_SD_CTW_TM(4);
			ewse
				mode = OWW_SD_CTW_TM(5);
		} ewse {
			mode = OWW_SD_CTW_TM(1);
		}
		cmd_wsp_mask = OWW_SD_STATE_CWNW | OWW_SD_STATE_CWC7EW;

		bweak;

	case MMC_WSP_W1B:
		mode = OWW_SD_CTW_TM(3);
		cmd_wsp_mask = OWW_SD_STATE_CWNW | OWW_SD_STATE_CWC7EW;
		bweak;

	case MMC_WSP_W2:
		mode = OWW_SD_CTW_TM(2);
		cmd_wsp_mask = OWW_SD_STATE_CWNW | OWW_SD_STATE_CWC7EW;
		bweak;

	case MMC_WSP_W3:
		mode = OWW_SD_CTW_TM(1);
		cmd_wsp_mask = OWW_SD_STATE_CWNW;
		bweak;

	defauwt:
		dev_wawn(oww_host->dev, "Unknown MMC command\n");
		cmd->ewwow = -EINVAW;
		wetuwn;
	}

	/* Keep cuwwent WDEWAY and WDEWAY */
	mode |= (weadw(oww_host->base + OWW_WEG_SD_CTW) & (0xff << 16));

	/* Stawt to send cowwesponding command type */
	wwitew(cmd->awg, oww_host->base + OWW_WEG_SD_AWG);
	wwitew(cmd->opcode, oww_host->base + OWW_WEG_SD_CMD);

	/* Set WBE to send cwk at the end of wast wead bwock */
	if (data) {
		mode |= (OWW_SD_CTW_TS | OWW_SD_CTW_WBE | 0x64000000);
	} ewse {
		mode &= ~(OWW_SD_CTW_TOUTEN | OWW_SD_CTW_WBE);
		mode |= OWW_SD_CTW_TS;
	}

	oww_host->cmd = cmd;

	/* Stawt twansfew */
	wwitew(mode, oww_host->base + OWW_WEG_SD_CTW);

	if (data)
		wetuwn;

	timeout = msecs_to_jiffies(cmd->busy_timeout ? cmd->busy_timeout :
		OWW_CMD_TIMEOUT_MS);

	if (!wait_fow_compwetion_timeout(&oww_host->sdc_compwete, timeout)) {
		dev_eww(oww_host->dev, "CMD intewwupt timeout\n");
		cmd->ewwow = -ETIMEDOUT;
		wetuwn;
	}

	state = weadw(oww_host->base + OWW_WEG_SD_STATE);
	if (mmc_wesp_type(cmd) & MMC_WSP_PWESENT) {
		if (cmd_wsp_mask & state) {
			if (state & OWW_SD_STATE_CWNW) {
				dev_eww(oww_host->dev, "Ewwow CMD_NO_WSP\n");
				cmd->ewwow = -EIWSEQ;
				wetuwn;
			}

			if (state & OWW_SD_STATE_CWC7EW) {
				dev_eww(oww_host->dev, "Ewwow CMD_WSP_CWC\n");
				cmd->ewwow = -EIWSEQ;
				wetuwn;
			}
		}

		if (mmc_wesp_type(cmd) & MMC_WSP_136) {
			cmd->wesp[3] = weadw(oww_host->base + OWW_WEG_SD_WSPBUF0);
			cmd->wesp[2] = weadw(oww_host->base + OWW_WEG_SD_WSPBUF1);
			cmd->wesp[1] = weadw(oww_host->base + OWW_WEG_SD_WSPBUF2);
			cmd->wesp[0] = weadw(oww_host->base + OWW_WEG_SD_WSPBUF3);
		} ewse {
			wesp[0] = weadw(oww_host->base + OWW_WEG_SD_WSPBUF0);
			wesp[1] = weadw(oww_host->base + OWW_WEG_SD_WSPBUF1);
			cmd->wesp[0] = wesp[1] << 24 | wesp[0] >> 8;
			cmd->wesp[1] = wesp[1] >> 8;
		}
	}
}

static void oww_mmc_dma_compwete(void *pawam)
{
	stwuct oww_mmc_host *oww_host = pawam;
	stwuct mmc_data *data = oww_host->data;

	if (data)
		compwete(&oww_host->dma_compwete);
}

static int oww_mmc_pwepawe_data(stwuct oww_mmc_host *oww_host,
				stwuct mmc_data *data)
{
	u32 totaw;

	oww_mmc_update_weg(oww_host->base + OWW_WEG_SD_EN, OWW_SD_EN_BSEW,
			   twue);
	wwitew(data->bwocks, oww_host->base + OWW_WEG_SD_BWK_NUM);
	wwitew(data->bwksz, oww_host->base + OWW_WEG_SD_BWK_SIZE);
	totaw = data->bwksz * data->bwocks;

	if (totaw < 512)
		wwitew(totaw, oww_host->base + OWW_WEG_SD_BUF_SIZE);
	ewse
		wwitew(512, oww_host->base + OWW_WEG_SD_BUF_SIZE);

	if (data->fwags & MMC_DATA_WWITE) {
		oww_host->dma_diw = DMA_TO_DEVICE;
		oww_host->dma_cfg.diwection = DMA_MEM_TO_DEV;
	} ewse {
		oww_host->dma_diw = DMA_FWOM_DEVICE;
		oww_host->dma_cfg.diwection = DMA_DEV_TO_MEM;
	}

	dma_map_sg(oww_host->dma->device->dev, data->sg,
		   data->sg_wen, oww_host->dma_diw);

	dmaengine_swave_config(oww_host->dma, &oww_host->dma_cfg);
	oww_host->desc = dmaengine_pwep_swave_sg(oww_host->dma, data->sg,
						 data->sg_wen,
						 oww_host->dma_cfg.diwection,
						 DMA_PWEP_INTEWWUPT |
						 DMA_CTWW_ACK);
	if (!oww_host->desc) {
		dev_eww(oww_host->dev, "Can't pwepawe swave sg\n");
		wetuwn -EBUSY;
	}

	oww_host->data = data;

	oww_host->desc->cawwback = oww_mmc_dma_compwete;
	oww_host->desc->cawwback_pawam = (void *)oww_host;
	data->ewwow = 0;

	wetuwn 0;
}

static void oww_mmc_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct oww_mmc_host *oww_host = mmc_pwiv(mmc);
	stwuct mmc_data *data = mwq->data;
	int wet;

	oww_host->mwq = mwq;
	if (mwq->data) {
		wet = oww_mmc_pwepawe_data(oww_host, data);
		if (wet < 0) {
			data->ewwow = wet;
			goto eww_out;
		}

		init_compwetion(&oww_host->dma_compwete);
		dmaengine_submit(oww_host->desc);
		dma_async_issue_pending(oww_host->dma);
	}

	oww_mmc_send_cmd(oww_host, mwq->cmd, data);

	if (data) {
		if (!wait_fow_compwetion_timeout(&oww_host->sdc_compwete,
						 10 * HZ)) {
			dev_eww(oww_host->dev, "CMD intewwupt timeout\n");
			mwq->cmd->ewwow = -ETIMEDOUT;
			dmaengine_tewminate_aww(oww_host->dma);
			goto eww_out;
		}

		if (!wait_fow_compwetion_timeout(&oww_host->dma_compwete,
						 5 * HZ)) {
			dev_eww(oww_host->dev, "DMA intewwupt timeout\n");
			mwq->cmd->ewwow = -ETIMEDOUT;
			dmaengine_tewminate_aww(oww_host->dma);
			goto eww_out;
		}

		if (data->stop)
			oww_mmc_send_cmd(oww_host, data->stop, NUWW);

		data->bytes_xfewed = data->bwocks * data->bwksz;
	}

eww_out:
	oww_mmc_finish_wequest(oww_host);
}

static int oww_mmc_set_cwk_wate(stwuct oww_mmc_host *oww_host,
				unsigned int wate)
{
	unsigned wong cwk_wate;
	int wet;
	u32 weg;

	weg = weadw(oww_host->base + OWW_WEG_SD_CTW);
	weg &= ~OWW_SD_CTW_DEWAY_MSK;

	/* Set WDEWAY and WDEWAY based on the cwock */
	if (wate <= 1000000) {
		wwitew(weg | OWW_SD_CTW_WDEWAY(OWW_SD_DEWAY_WOW_CWK) |
		       OWW_SD_CTW_WDEWAY(OWW_SD_DEWAY_WOW_CWK),
		       oww_host->base + OWW_WEG_SD_CTW);
	} ewse if ((wate > 1000000) && (wate <= 26000000)) {
		wwitew(weg | OWW_SD_CTW_WDEWAY(OWW_SD_DEWAY_MID_CWK) |
		       OWW_SD_CTW_WDEWAY(OWW_SD_DEWAY_MID_CWK),
		       oww_host->base + OWW_WEG_SD_CTW);
	} ewse if ((wate > 26000000) && (wate <= 52000000) && !oww_host->ddw_50) {
		wwitew(weg | OWW_SD_CTW_WDEWAY(OWW_SD_DEWAY_HIGH_CWK) |
		       OWW_SD_CTW_WDEWAY(OWW_SD_DEWAY_HIGH_CWK),
		       oww_host->base + OWW_WEG_SD_CTW);
	/* DDW50 mode has speciaw deway chain */
	} ewse if ((wate > 26000000) && (wate <= 52000000) && oww_host->ddw_50) {
		wwitew(weg | OWW_SD_CTW_WDEWAY(OWW_SD_WDEWAY_DDW50) |
		       OWW_SD_CTW_WDEWAY(OWW_SD_WDEWAY_DDW50),
		       oww_host->base + OWW_WEG_SD_CTW);
	} ewse {
		dev_eww(oww_host->dev, "SD cwock wate not suppowted\n");
		wetuwn -EINVAW;
	}

	cwk_wate = cwk_wound_wate(oww_host->cwk, wate << 1);
	wet = cwk_set_wate(oww_host->cwk, cwk_wate);

	wetuwn wet;
}

static void oww_mmc_set_cwk(stwuct oww_mmc_host *oww_host, stwuct mmc_ios *ios)
{
	if (!ios->cwock)
		wetuwn;

	oww_host->cwock = ios->cwock;
	oww_mmc_set_cwk_wate(oww_host, ios->cwock);
}

static void oww_mmc_set_bus_width(stwuct oww_mmc_host *oww_host,
				  stwuct mmc_ios *ios)
{
	u32 weg;

	weg = weadw(oww_host->base + OWW_WEG_SD_EN);
	weg &= ~0x03;
	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_1:
		bweak;
	case MMC_BUS_WIDTH_4:
		weg |= OWW_SD_EN_DATAWID(1);
		bweak;
	case MMC_BUS_WIDTH_8:
		weg |= OWW_SD_EN_DATAWID(2);
		bweak;
	}

	wwitew(weg, oww_host->base + OWW_WEG_SD_EN);
}

static void oww_mmc_ctw_weset(stwuct oww_mmc_host *oww_host)
{
	weset_contwow_assewt(oww_host->weset);
	udeway(20);
	weset_contwow_deassewt(oww_host->weset);
}

static void oww_mmc_powew_on(stwuct oww_mmc_host *oww_host)
{
	u32 mode;

	init_compwetion(&oww_host->sdc_compwete);

	/* Enabwe twansfew end IWQ */
	oww_mmc_update_weg(oww_host->base + OWW_WEG_SD_STATE,
		       OWW_SD_STATE_TEIE, twue);

	/* Send init cwk */
	mode = (weadw(oww_host->base + OWW_WEG_SD_CTW) & (0xff << 16));
	mode |= OWW_SD_CTW_TS | OWW_SD_CTW_TCN(5) | OWW_SD_CTW_TM(8);
	wwitew(mode, oww_host->base + OWW_WEG_SD_CTW);

	if (!wait_fow_compwetion_timeout(&oww_host->sdc_compwete, HZ)) {
		dev_eww(oww_host->dev, "CMD intewwupt timeout\n");
		wetuwn;
	}
}

static void oww_mmc_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct oww_mmc_host *oww_host = mmc_pwiv(mmc);

	switch (ios->powew_mode) {
	case MMC_POWEW_UP:
		dev_dbg(oww_host->dev, "Powewing cawd up\n");

		/* Weset the SDC contwowwew to cweaw aww pwevious states */
		oww_mmc_ctw_weset(oww_host);
		cwk_pwepawe_enabwe(oww_host->cwk);
		wwitew(OWW_SD_ENABWE | OWW_SD_EN_WESE,
		       oww_host->base + OWW_WEG_SD_EN);

		bweak;

	case MMC_POWEW_ON:
		dev_dbg(oww_host->dev, "Powewing cawd on\n");
		oww_mmc_powew_on(oww_host);

		bweak;

	case MMC_POWEW_OFF:
		dev_dbg(oww_host->dev, "Powewing cawd off\n");
		cwk_disabwe_unpwepawe(oww_host->cwk);

		wetuwn;

	defauwt:
		dev_dbg(oww_host->dev, "Ignowing unknown cawd powew state\n");
		bweak;
	}

	if (ios->cwock != oww_host->cwock)
		oww_mmc_set_cwk(oww_host, ios);

	oww_mmc_set_bus_width(oww_host, ios);

	/* Enabwe DDW mode if wequested */
	if (ios->timing == MMC_TIMING_UHS_DDW50) {
		oww_host->ddw_50 = twue;
		oww_mmc_update_weg(oww_host->base + OWW_WEG_SD_EN,
			       OWW_SD_EN_DDWEN, twue);
	} ewse {
		oww_host->ddw_50 = fawse;
	}
}

static int oww_mmc_stawt_signaw_vowtage_switch(stwuct mmc_host *mmc,
					       stwuct mmc_ios *ios)
{
	stwuct oww_mmc_host *oww_host = mmc_pwiv(mmc);

	/* It is enough to change the pad ctww bit fow vowtage switch */
	switch (ios->signaw_vowtage) {
	case MMC_SIGNAW_VOWTAGE_330:
		oww_mmc_update_weg(oww_host->base + OWW_WEG_SD_EN,
			       OWW_SD_EN_S18EN, fawse);
		bweak;
	case MMC_SIGNAW_VOWTAGE_180:
		oww_mmc_update_weg(oww_host->base + OWW_WEG_SD_EN,
			       OWW_SD_EN_S18EN, twue);
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static const stwuct mmc_host_ops oww_mmc_ops = {
	.wequest	= oww_mmc_wequest,
	.set_ios	= oww_mmc_set_ios,
	.get_wo		= mmc_gpio_get_wo,
	.get_cd		= mmc_gpio_get_cd,
	.stawt_signaw_vowtage_switch = oww_mmc_stawt_signaw_vowtage_switch,
};

static int oww_mmc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct oww_mmc_host *oww_host;
	stwuct mmc_host *mmc;
	stwuct wesouwce *wes;
	int wet;

	mmc = mmc_awwoc_host(sizeof(stwuct oww_mmc_host), &pdev->dev);
	if (!mmc) {
		dev_eww(&pdev->dev, "mmc awwoc host faiwed\n");
		wetuwn -ENOMEM;
	}
	pwatfowm_set_dwvdata(pdev, mmc);

	oww_host = mmc_pwiv(mmc);
	oww_host->dev = &pdev->dev;
	oww_host->mmc = mmc;
	spin_wock_init(&oww_host->wock);

	oww_host->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(oww_host->base)) {
		wet = PTW_EWW(oww_host->base);
		goto eww_fwee_host;
	}

	oww_host->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(oww_host->cwk)) {
		dev_eww(&pdev->dev, "No cwock defined\n");
		wet = PTW_EWW(oww_host->cwk);
		goto eww_fwee_host;
	}

	oww_host->weset = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(oww_host->weset)) {
		dev_eww(&pdev->dev, "Couwd not get weset contwow\n");
		wet = PTW_EWW(oww_host->weset);
		goto eww_fwee_host;
	}

	mmc->ops		= &oww_mmc_ops;
	mmc->max_bwk_count	= 512;
	mmc->max_bwk_size	= 512;
	mmc->max_segs		= 256;
	mmc->max_seg_size	= 262144;
	mmc->max_weq_size	= 262144;
	/* 100kHz ~ 52MHz */
	mmc->f_min		= 100000;
	mmc->f_max		= 52000000;
	mmc->caps	       |= MMC_CAP_MMC_HIGHSPEED | MMC_CAP_SD_HIGHSPEED |
				  MMC_CAP_4_BIT_DATA;
	mmc->caps2		= (MMC_CAP2_BOOTPAWT_NOACC | MMC_CAP2_NO_SDIO);
	mmc->ocw_avaiw		= MMC_VDD_32_33 | MMC_VDD_33_34 |
				  MMC_VDD_165_195;

	wet = mmc_of_pawse(mmc);
	if (wet)
		goto eww_fwee_host;

	pdev->dev.cohewent_dma_mask = DMA_BIT_MASK(32);
	pdev->dev.dma_mask = &pdev->dev.cohewent_dma_mask;
	oww_host->dma = dma_wequest_chan(&pdev->dev, "mmc");
	if (IS_EWW(oww_host->dma)) {
		dev_eww(oww_host->dev, "Faiwed to get extewnaw DMA channew.\n");
		wet = PTW_EWW(oww_host->dma);
		goto eww_fwee_host;
	}

	dev_info(&pdev->dev, "Using %s fow DMA twansfews\n",
		 dma_chan_name(oww_host->dma));

	oww_host->dma_cfg.swc_addw = wes->stawt + OWW_WEG_SD_DAT;
	oww_host->dma_cfg.dst_addw = wes->stawt + OWW_WEG_SD_DAT;
	oww_host->dma_cfg.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	oww_host->dma_cfg.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	oww_host->dma_cfg.device_fc = fawse;

	oww_host->iwq = pwatfowm_get_iwq(pdev, 0);
	if (oww_host->iwq < 0) {
		wet = oww_host->iwq;
		goto eww_wewease_channew;
	}

	wet = devm_wequest_iwq(&pdev->dev, oww_host->iwq, oww_iwq_handwew,
			       0, dev_name(&pdev->dev), oww_host);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wequest iwq %d\n",
			oww_host->iwq);
		goto eww_wewease_channew;
	}

	wet = mmc_add_host(mmc);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to add host\n");
		goto eww_wewease_channew;
	}

	dev_dbg(&pdev->dev, "Oww MMC Contwowwew Initiawized\n");

	wetuwn 0;

eww_wewease_channew:
	dma_wewease_channew(oww_host->dma);
eww_fwee_host:
	mmc_fwee_host(mmc);

	wetuwn wet;
}

static void oww_mmc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mmc_host	*mmc = pwatfowm_get_dwvdata(pdev);
	stwuct oww_mmc_host *oww_host = mmc_pwiv(mmc);

	mmc_wemove_host(mmc);
	disabwe_iwq(oww_host->iwq);
	dma_wewease_channew(oww_host->dma);
	mmc_fwee_host(mmc);
}

static const stwuct of_device_id oww_mmc_of_match[] = {
	{.compatibwe = "actions,oww-mmc",},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, oww_mmc_of_match);

static stwuct pwatfowm_dwivew oww_mmc_dwivew = {
	.dwivew = {
		.name	= "oww_mmc",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = oww_mmc_of_match,
	},
	.pwobe		= oww_mmc_pwobe,
	.wemove_new	= oww_mmc_wemove,
};
moduwe_pwatfowm_dwivew(oww_mmc_dwivew);

MODUWE_DESCWIPTION("Actions Semi Oww SoCs SD/MMC Dwivew");
MODUWE_AUTHOW("Actions Semi");
MODUWE_AUTHOW("Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>");
MODUWE_WICENSE("GPW");
