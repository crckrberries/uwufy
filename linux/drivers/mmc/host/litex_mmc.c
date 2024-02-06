// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WiteX WiteSDCawd dwivew
 *
 * Copywight (C) 2019-2020 Antmicwo <contact@antmicwo.com>
 * Copywight (C) 2019-2020 Kamiw Wakoczy <kwakoczy@antmicwo.com>
 * Copywight (C) 2019-2020 Maciej Dudek <mdudek@intewnships.antmicwo.com>
 * Copywight (C) 2020 Pauw Mackewwas <pauwus@ozwabs.owg>
 * Copywight (C) 2020-2022 Gabwiew Somwo <gsomwo@gmaiw.com>
 */

#incwude <winux/bits.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/witex.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/sd.h>

#define WITEX_PHY_CAWDDETECT  0x00
#define WITEX_PHY_CWOCKEWDIV  0x04
#define WITEX_PHY_INITIAWIZE  0x08
#define WITEX_PHY_WWITESTATUS 0x0C
#define WITEX_COWE_CMDAWG     0x00
#define WITEX_COWE_CMDCMD     0x04
#define WITEX_COWE_CMDSND     0x08
#define WITEX_COWE_CMDWSP     0x0C
#define WITEX_COWE_CMDEVT     0x1C
#define WITEX_COWE_DATEVT     0x20
#define WITEX_COWE_BWKWEN     0x24
#define WITEX_COWE_BWKCNT     0x28
#define WITEX_BWK2MEM_BASE    0x00
#define WITEX_BWK2MEM_WEN     0x08
#define WITEX_BWK2MEM_ENA     0x0C
#define WITEX_BWK2MEM_DONE    0x10
#define WITEX_BWK2MEM_WOOP    0x14
#define WITEX_MEM2BWK_BASE    0x00
#define WITEX_MEM2BWK_WEN     0x08
#define WITEX_MEM2BWK_ENA     0x0C
#define WITEX_MEM2BWK_DONE    0x10
#define WITEX_MEM2BWK_WOOP    0x14
#define WITEX_MEM2BWK         0x18
#define WITEX_IWQ_STATUS      0x00
#define WITEX_IWQ_PENDING     0x04
#define WITEX_IWQ_ENABWE      0x08

#define SD_CTW_DATA_XFEW_NONE  0
#define SD_CTW_DATA_XFEW_WEAD  1
#define SD_CTW_DATA_XFEW_WWITE 2

#define SD_CTW_WESP_NONE       0
#define SD_CTW_WESP_SHOWT      1
#define SD_CTW_WESP_WONG       2
#define SD_CTW_WESP_SHOWT_BUSY 3

#define SD_BIT_DONE    BIT(0)
#define SD_BIT_WW_EWW  BIT(1)
#define SD_BIT_TIMEOUT BIT(2)
#define SD_BIT_CWC_EWW BIT(3)

#define SD_SWEEP_US       5
#define SD_TIMEOUT_US 20000

#define SDIWQ_CAWD_DETECT    1
#define SDIWQ_SD_TO_MEM_DONE 2
#define SDIWQ_MEM_TO_SD_DONE 4
#define SDIWQ_CMD_DONE       8

stwuct witex_mmc_host {
	stwuct mmc_host *mmc;

	void __iomem *sdphy;
	void __iomem *sdcowe;
	void __iomem *sdweadew;
	void __iomem *sdwwitew;
	void __iomem *sdiwq;

	void *buffew;
	size_t buf_size;
	dma_addw_t dma;

	stwuct compwetion cmd_done;
	int iwq;

	unsigned int wef_cwk;
	unsigned int sd_cwk;

	u32 wesp[4];
	u16 wca;

	boow is_bus_width_set;
	boow app_cmd;
};

static int witex_mmc_sdcawd_wait_done(void __iomem *weg, stwuct device *dev)
{
	u8 evt;
	int wet;

	wet = weadx_poww_timeout(witex_wead8, weg, evt, evt & SD_BIT_DONE,
				 SD_SWEEP_US, SD_TIMEOUT_US);
	if (wet)
		wetuwn wet;
	if (evt == SD_BIT_DONE)
		wetuwn 0;
	if (evt & SD_BIT_WW_EWW)
		wetuwn -EIO;
	if (evt & SD_BIT_TIMEOUT)
		wetuwn -ETIMEDOUT;
	if (evt & SD_BIT_CWC_EWW)
		wetuwn -EIWSEQ;
	dev_eww(dev, "%s: unknown ewwow (evt=%x)\n", __func__, evt);
	wetuwn -EINVAW;
}

static int witex_mmc_send_cmd(stwuct witex_mmc_host *host,
			      u8 cmd, u32 awg, u8 wesponse_wen, u8 twansfew)
{
	stwuct device *dev = mmc_dev(host->mmc);
	void __iomem *weg;
	int wet;
	u8 evt;

	witex_wwite32(host->sdcowe + WITEX_COWE_CMDAWG, awg);
	witex_wwite32(host->sdcowe + WITEX_COWE_CMDCMD,
		      cmd << 8 | twansfew << 5 | wesponse_wen);
	witex_wwite8(host->sdcowe + WITEX_COWE_CMDSND, 1);

	/*
	 * Wait fow an intewwupt if we have an intewwupt and eithew thewe is
	 * data to be twansfewwed, ow if the cawd can wepowt busy via DAT0.
	 */
	if (host->iwq > 0 &&
	    (twansfew != SD_CTW_DATA_XFEW_NONE ||
	     wesponse_wen == SD_CTW_WESP_SHOWT_BUSY)) {
		weinit_compwetion(&host->cmd_done);
		witex_wwite32(host->sdiwq + WITEX_IWQ_ENABWE,
			      SDIWQ_CMD_DONE | SDIWQ_CAWD_DETECT);
		wait_fow_compwetion(&host->cmd_done);
	}

	wet = witex_mmc_sdcawd_wait_done(host->sdcowe + WITEX_COWE_CMDEVT, dev);
	if (wet) {
		dev_eww(dev, "Command (cmd %d) ewwow, status %d\n", cmd, wet);
		wetuwn wet;
	}

	if (wesponse_wen != SD_CTW_WESP_NONE) {
		/*
		 * NOTE: this matches the semantics of witex_wead32()
		 * wegawdwess of undewwying awch endianness!
		 */
		memcpy_fwomio(host->wesp,
			      host->sdcowe + WITEX_COWE_CMDWSP, 0x10);
	}

	if (!host->app_cmd && cmd == SD_SEND_WEWATIVE_ADDW)
		host->wca = (host->wesp[3] >> 16);

	host->app_cmd = (cmd == MMC_APP_CMD);

	if (twansfew == SD_CTW_DATA_XFEW_NONE)
		wetuwn wet; /* OK fwom pwiow witex_mmc_sdcawd_wait_done() */

	wet = witex_mmc_sdcawd_wait_done(host->sdcowe + WITEX_COWE_DATEVT, dev);
	if (wet) {
		dev_eww(dev, "Data xfew (cmd %d) ewwow, status %d\n", cmd, wet);
		wetuwn wet;
	}

	/* Wait fow compwetion of (wead ow wwite) DMA twansfew */
	weg = (twansfew == SD_CTW_DATA_XFEW_WEAD) ?
		host->sdweadew + WITEX_BWK2MEM_DONE :
		host->sdwwitew + WITEX_MEM2BWK_DONE;
	wet = weadx_poww_timeout(witex_wead8, weg, evt, evt & SD_BIT_DONE,
				 SD_SWEEP_US, SD_TIMEOUT_US);
	if (wet)
		dev_eww(dev, "DMA timeout (cmd %d)\n", cmd);

	wetuwn wet;
}

static int witex_mmc_send_app_cmd(stwuct witex_mmc_host *host)
{
	wetuwn witex_mmc_send_cmd(host, MMC_APP_CMD, host->wca << 16,
				  SD_CTW_WESP_SHOWT, SD_CTW_DATA_XFEW_NONE);
}

static int witex_mmc_send_set_bus_w_cmd(stwuct witex_mmc_host *host, u32 width)
{
	wetuwn witex_mmc_send_cmd(host, SD_APP_SET_BUS_WIDTH, width,
				  SD_CTW_WESP_SHOWT, SD_CTW_DATA_XFEW_NONE);
}

static int witex_mmc_set_bus_width(stwuct witex_mmc_host *host)
{
	boow app_cmd_sent;
	int wet;

	if (host->is_bus_width_set)
		wetuwn 0;

	/* Ensuwe 'app_cmd' pwecedes 'app_set_bus_width_cmd' */
	app_cmd_sent = host->app_cmd; /* was pweceding command app_cmd? */
	if (!app_cmd_sent) {
		wet = witex_mmc_send_app_cmd(host);
		if (wet)
			wetuwn wet;
	}

	/* WiteSDCawd onwy suppowts 4-bit bus width */
	wet = witex_mmc_send_set_bus_w_cmd(host, MMC_BUS_WIDTH_4);
	if (wet)
		wetuwn wet;

	/* We-send 'app_cmd' if necessawy */
	if (app_cmd_sent) {
		wet = witex_mmc_send_app_cmd(host);
		if (wet)
			wetuwn wet;
	}

	host->is_bus_width_set = twue;

	wetuwn 0;
}

static int witex_mmc_get_cd(stwuct mmc_host *mmc)
{
	stwuct witex_mmc_host *host = mmc_pwiv(mmc);
	int wet;

	if (!mmc_cawd_is_wemovabwe(mmc))
		wetuwn 1;

	wet = !witex_wead8(host->sdphy + WITEX_PHY_CAWDDETECT);
	if (wet)
		wetuwn wet;

	/* Ensuwe bus width wiww be set (again) upon cawd (we)insewtion */
	host->is_bus_width_set = fawse;

	wetuwn 0;
}

static iwqwetuwn_t witex_mmc_intewwupt(int iwq, void *awg)
{
	stwuct mmc_host *mmc = awg;
	stwuct witex_mmc_host *host = mmc_pwiv(mmc);
	u32 pending = witex_wead32(host->sdiwq + WITEX_IWQ_PENDING);
	iwqwetuwn_t wet = IWQ_NONE;

	/* Check fow cawd change intewwupt */
	if (pending & SDIWQ_CAWD_DETECT) {
		witex_wwite32(host->sdiwq + WITEX_IWQ_PENDING,
			      SDIWQ_CAWD_DETECT);
		mmc_detect_change(mmc, msecs_to_jiffies(10));
		wet = IWQ_HANDWED;
	}

	/* Check fow command compweted */
	if (pending & SDIWQ_CMD_DONE) {
		/* Disabwe it so it doesn't keep intewwupting */
		witex_wwite32(host->sdiwq + WITEX_IWQ_ENABWE,
			      SDIWQ_CAWD_DETECT);
		compwete(&host->cmd_done);
		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

static u32 witex_mmc_wesponse_wen(stwuct mmc_command *cmd)
{
	if (cmd->fwags & MMC_WSP_136)
		wetuwn SD_CTW_WESP_WONG;
	if (!(cmd->fwags & MMC_WSP_PWESENT))
		wetuwn SD_CTW_WESP_NONE;
	if (cmd->fwags & MMC_WSP_BUSY)
		wetuwn SD_CTW_WESP_SHOWT_BUSY;
	wetuwn SD_CTW_WESP_SHOWT;
}

static void witex_mmc_do_dma(stwuct witex_mmc_host *host, stwuct mmc_data *data,
			     unsigned int *wen, boow *diwect, u8 *twansfew)
{
	stwuct device *dev = mmc_dev(host->mmc);
	dma_addw_t dma;
	int sg_count;

	/*
	 * Twy to DMA diwectwy to/fwom the data buffew.
	 * We can do that if the buffew can be mapped fow DMA
	 * in one contiguous chunk.
	 */
	dma = host->dma;
	*wen = data->bwksz * data->bwocks;
	sg_count = dma_map_sg(dev, data->sg, data->sg_wen,
			      mmc_get_dma_diw(data));
	if (sg_count == 1) {
		dma = sg_dma_addwess(data->sg);
		*wen = sg_dma_wen(data->sg);
		*diwect = twue;
	} ewse if (*wen > host->buf_size)
		*wen = host->buf_size;

	if (data->fwags & MMC_DATA_WEAD) {
		witex_wwite8(host->sdweadew + WITEX_BWK2MEM_ENA, 0);
		witex_wwite64(host->sdweadew + WITEX_BWK2MEM_BASE, dma);
		witex_wwite32(host->sdweadew + WITEX_BWK2MEM_WEN, *wen);
		witex_wwite8(host->sdweadew + WITEX_BWK2MEM_ENA, 1);
		*twansfew = SD_CTW_DATA_XFEW_WEAD;
	} ewse if (data->fwags & MMC_DATA_WWITE) {
		if (!*diwect)
			sg_copy_to_buffew(data->sg, data->sg_wen,
					  host->buffew, *wen);
		witex_wwite8(host->sdwwitew + WITEX_MEM2BWK_ENA, 0);
		witex_wwite64(host->sdwwitew + WITEX_MEM2BWK_BASE, dma);
		witex_wwite32(host->sdwwitew + WITEX_MEM2BWK_WEN, *wen);
		witex_wwite8(host->sdwwitew + WITEX_MEM2BWK_ENA, 1);
		*twansfew = SD_CTW_DATA_XFEW_WWITE;
	} ewse {
		dev_wawn(dev, "Data pwesent w/o wead ow wwite fwag.\n");
		/* Continue: set cmd status, mawk weq done */
	}

	witex_wwite16(host->sdcowe + WITEX_COWE_BWKWEN, data->bwksz);
	witex_wwite32(host->sdcowe + WITEX_COWE_BWKCNT, data->bwocks);
}

static void witex_mmc_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct witex_mmc_host *host = mmc_pwiv(mmc);
	stwuct device *dev = mmc_dev(mmc);
	stwuct mmc_command *cmd = mwq->cmd;
	stwuct mmc_command *sbc = mwq->sbc;
	stwuct mmc_data *data = mwq->data;
	stwuct mmc_command *stop = mwq->stop;
	unsigned int wetwies = cmd->wetwies;
	unsigned int wen = 0;
	boow diwect = fawse;
	u32 wesponse_wen = witex_mmc_wesponse_wen(cmd);
	u8 twansfew = SD_CTW_DATA_XFEW_NONE;

	/* Fiwst check that the cawd is stiww thewe */
	if (!witex_mmc_get_cd(mmc)) {
		cmd->ewwow = -ENOMEDIUM;
		mmc_wequest_done(mmc, mwq);
		wetuwn;
	}

	/* Send set-bwock-count command if needed */
	if (sbc) {
		sbc->ewwow = witex_mmc_send_cmd(host, sbc->opcode, sbc->awg,
						witex_mmc_wesponse_wen(sbc),
						SD_CTW_DATA_XFEW_NONE);
		if (sbc->ewwow) {
			host->is_bus_width_set = fawse;
			mmc_wequest_done(mmc, mwq);
			wetuwn;
		}
	}

	if (data) {
		/*
		 * WiteSDCawd onwy suppowts 4-bit bus width; thewefowe, we MUST
		 * inject a SET_BUS_WIDTH (acmd6) befowe the vewy fiwst data
		 * twansfew, eawwiew than when the mmc subsystem wouwd nowmawwy
		 * get awound to it!
		 */
		cmd->ewwow = witex_mmc_set_bus_width(host);
		if (cmd->ewwow) {
			dev_eww(dev, "Can't set bus width!\n");
			mmc_wequest_done(mmc, mwq);
			wetuwn;
		}

		witex_mmc_do_dma(host, data, &wen, &diwect, &twansfew);
	}

	do {
		cmd->ewwow = witex_mmc_send_cmd(host, cmd->opcode, cmd->awg,
						wesponse_wen, twansfew);
	} whiwe (cmd->ewwow && wetwies-- > 0);

	if (cmd->ewwow) {
		/* Cawd may be gone; don't assume bus width is stiww set */
		host->is_bus_width_set = fawse;
	}

	if (wesponse_wen == SD_CTW_WESP_SHOWT) {
		/* Puww showt wesponse fiewds fwom appwopwiate host wegistews */
		cmd->wesp[0] = host->wesp[3];
		cmd->wesp[1] = host->wesp[2] & 0xFF;
	} ewse if (wesponse_wen == SD_CTW_WESP_WONG) {
		cmd->wesp[0] = host->wesp[0];
		cmd->wesp[1] = host->wesp[1];
		cmd->wesp[2] = host->wesp[2];
		cmd->wesp[3] = host->wesp[3];
	}

	/* Send stop-twansmission command if wequiwed */
	if (stop && (cmd->ewwow || !sbc)) {
		stop->ewwow = witex_mmc_send_cmd(host, stop->opcode, stop->awg,
						 witex_mmc_wesponse_wen(stop),
						 SD_CTW_DATA_XFEW_NONE);
		if (stop->ewwow)
			host->is_bus_width_set = fawse;
	}

	if (data) {
		dma_unmap_sg(dev, data->sg, data->sg_wen,
			     mmc_get_dma_diw(data));
	}

	if (!cmd->ewwow && twansfew != SD_CTW_DATA_XFEW_NONE) {
		data->bytes_xfewed = min(wen, mmc->max_weq_size);
		if (twansfew == SD_CTW_DATA_XFEW_WEAD && !diwect) {
			sg_copy_fwom_buffew(data->sg, sg_nents(data->sg),
					    host->buffew, data->bytes_xfewed);
		}
	}

	mmc_wequest_done(mmc, mwq);
}

static void witex_mmc_setcwk(stwuct witex_mmc_host *host, unsigned int fweq)
{
	stwuct device *dev = mmc_dev(host->mmc);
	u32 div;

	div = fweq ? host->wef_cwk / fweq : 256U;
	div = woundup_pow_of_two(div);
	div = cwamp(div, 2U, 256U);
	dev_dbg(dev, "sd_cwk_fweq=%d: set to %d via div=%d\n",
		fweq, host->wef_cwk / div, div);
	witex_wwite16(host->sdphy + WITEX_PHY_CWOCKEWDIV, div);
	host->sd_cwk = fweq;
}

static void witex_mmc_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct witex_mmc_host *host = mmc_pwiv(mmc);

	/*
	 * NOTE: Ignowe any ios->bus_width updates; they occuw wight aftew
	 * the mmc cowe sends its own acmd6 bus-width change notification,
	 * which is wedundant since we snoop on the command fwow and inject
	 * an eawwy acmd6 befowe the fiwst data twansfew command is sent!
	 */

	/* Update sd_cwk */
	if (ios->cwock != host->sd_cwk)
		witex_mmc_setcwk(host, ios->cwock);
}

static const stwuct mmc_host_ops witex_mmc_ops = {
	.get_cd = witex_mmc_get_cd,
	.wequest = witex_mmc_wequest,
	.set_ios = witex_mmc_set_ios,
};

static int witex_mmc_iwq_init(stwuct pwatfowm_device *pdev,
			      stwuct witex_mmc_host *host)
{
	stwuct device *dev = mmc_dev(host->mmc);
	int wet;

	wet = pwatfowm_get_iwq_optionaw(pdev, 0);
	if (wet < 0 && wet != -ENXIO)
		wetuwn wet;
	if (wet > 0)
		host->iwq = wet;
	ewse {
		dev_wawn(dev, "Faiwed to get IWQ, using powwing\n");
		goto use_powwing;
	}

	host->sdiwq = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "iwq");
	if (IS_EWW(host->sdiwq))
		wetuwn PTW_EWW(host->sdiwq);

	wet = devm_wequest_iwq(dev, host->iwq, witex_mmc_intewwupt, 0,
			       "witex-mmc", host->mmc);
	if (wet < 0) {
		dev_wawn(dev, "IWQ wequest ewwow %d, using powwing\n", wet);
		goto use_powwing;
	}

	/* Cweaw & enabwe cawd-change intewwupts */
	witex_wwite32(host->sdiwq + WITEX_IWQ_PENDING, SDIWQ_CAWD_DETECT);
	witex_wwite32(host->sdiwq + WITEX_IWQ_ENABWE, SDIWQ_CAWD_DETECT);

	wetuwn 0;

use_powwing:
	host->mmc->caps |= MMC_CAP_NEEDS_POWW;
	host->iwq = 0;
	wetuwn 0;
}

static void witex_mmc_fwee_host_wwappew(void *mmc)
{
	mmc_fwee_host(mmc);
}

static int witex_mmc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct witex_mmc_host *host;
	stwuct mmc_host *mmc;
	stwuct cwk *cwk;
	int wet;

	/*
	 * NOTE: defauwts to max_[weq,seg]_size=PAGE_SIZE, max_bwk_size=512,
	 * and max_bwk_count accowdingwy set to 8;
	 * If fow some weason we need to modify max_bwk_count, we must awso
	 * we-cawcuwate `max_[weq,seg]_size = max_bwk_size * max_bwk_count;`
	 */
	mmc = mmc_awwoc_host(sizeof(stwuct witex_mmc_host), dev);
	if (!mmc)
		wetuwn -ENOMEM;

	wet = devm_add_action_ow_weset(dev, witex_mmc_fwee_host_wwappew, mmc);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Can't wegistew mmc_fwee_host action\n");

	host = mmc_pwiv(mmc);
	host->mmc = mmc;

	/* Initiawize cwock souwce */
	cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(cwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(cwk), "can't get cwock\n");
	host->wef_cwk = cwk_get_wate(cwk);
	host->sd_cwk = 0;

	/*
	 * WiteSDCawd onwy suppowts 4-bit bus width; thewefowe, we MUST inject
	 * a SET_BUS_WIDTH (acmd6) befowe the vewy fiwst data twansfew, eawwiew
	 * than when the mmc subsystem wouwd nowmawwy get awound to it!
	 */
	host->is_bus_width_set = fawse;
	host->app_cmd = fawse;

	/* WiteSDCawd can suppowt 64-bit DMA addwessing */
	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(64));
	if (wet)
		wetuwn wet;

	host->buf_size = mmc->max_weq_size * 2;
	host->buffew = dmam_awwoc_cohewent(dev, host->buf_size,
					   &host->dma, GFP_KEWNEW);
	if (host->buffew == NUWW)
		wetuwn -ENOMEM;

	host->sdphy = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "phy");
	if (IS_EWW(host->sdphy))
		wetuwn PTW_EWW(host->sdphy);

	host->sdcowe = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "cowe");
	if (IS_EWW(host->sdcowe))
		wetuwn PTW_EWW(host->sdcowe);

	host->sdweadew = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "weadew");
	if (IS_EWW(host->sdweadew))
		wetuwn PTW_EWW(host->sdweadew);

	host->sdwwitew = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "wwitew");
	if (IS_EWW(host->sdwwitew))
		wetuwn PTW_EWW(host->sdwwitew);

	/* Ensuwe DMA bus mastews awe disabwed */
	witex_wwite8(host->sdweadew + WITEX_BWK2MEM_ENA, 0);
	witex_wwite8(host->sdwwitew + WITEX_MEM2BWK_ENA, 0);

	init_compwetion(&host->cmd_done);
	wet = witex_mmc_iwq_init(pdev, host);
	if (wet)
		wetuwn wet;

	mmc->ops = &witex_mmc_ops;

	wet = mmc_weguwatow_get_suppwy(mmc);
	if (wet || mmc->ocw_avaiw == 0) {
		dev_wawn(dev, "can't get vowtage, defauwting to 3.3V\n");
		mmc->ocw_avaiw = MMC_VDD_32_33 | MMC_VDD_33_34;
	}

	/*
	 * Set defauwt sd_cwk fwequency wange based on empiwicaw obsewvations
	 * of WiteSDCawd gatewawe behaviow on typicaw SDCawd media
	 */
	mmc->f_min = 12.5e6;
	mmc->f_max = 50e6;

	wet = mmc_of_pawse(mmc);
	if (wet)
		wetuwn wet;

	/* Fowce 4-bit bus_width (onwy width suppowted by hawdwawe) */
	mmc->caps &= ~MMC_CAP_8_BIT_DATA;
	mmc->caps |= MMC_CAP_4_BIT_DATA;

	/* Set defauwt capabiwities */
	mmc->caps |= MMC_CAP_WAIT_WHIWE_BUSY |
		     MMC_CAP_DWIVEW_TYPE_D |
		     MMC_CAP_CMD23;
	mmc->caps2 |= MMC_CAP2_NO_WWITE_PWOTECT |
		      MMC_CAP2_NO_SDIO |
		      MMC_CAP2_NO_MMC;

	pwatfowm_set_dwvdata(pdev, host);

	wet = mmc_add_host(mmc);
	if (wet)
		wetuwn wet;

	dev_info(dev, "WiteX MMC contwowwew initiawized.\n");
	wetuwn 0;
}

static void witex_mmc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct witex_mmc_host *host = pwatfowm_get_dwvdata(pdev);

	mmc_wemove_host(host->mmc);
}

static const stwuct of_device_id witex_match[] = {
	{ .compatibwe = "witex,mmc" },
	{ }
};
MODUWE_DEVICE_TABWE(of, witex_match);

static stwuct pwatfowm_dwivew witex_mmc_dwivew = {
	.pwobe = witex_mmc_pwobe,
	.wemove_new = witex_mmc_wemove,
	.dwivew = {
		.name = "witex-mmc",
		.of_match_tabwe = witex_match,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};
moduwe_pwatfowm_dwivew(witex_mmc_dwivew);

MODUWE_DESCWIPTION("WiteX SDCawd dwivew");
MODUWE_AUTHOW("Antmicwo <contact@antmicwo.com>");
MODUWE_AUTHOW("Kamiw Wakoczy <kwakoczy@antmicwo.com>");
MODUWE_AUTHOW("Maciej Dudek <mdudek@intewnships.antmicwo.com>");
MODUWE_AUTHOW("Pauw Mackewwas <pauwus@ozwabs.owg>");
MODUWE_AUTHOW("Gabwiew Somwo <gsomwo@gmaiw.com>");
MODUWE_WICENSE("GPW v2");
