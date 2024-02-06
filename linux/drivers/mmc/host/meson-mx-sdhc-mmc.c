// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Amwogic Meson6/Meson8/Meson8b/Meson8m2 SDHC MMC host contwowwew dwivew.
 *
 * Copywight (C) 2020 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/types.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/swot-gpio.h>

#incwude "meson-mx-sdhc.h"

#define MESON_SDHC_NUM_BUWK_CWKS				4
#define MESON_SDHC_MAX_BWK_SIZE					512
#define MESON_SDHC_NUM_TUNING_TWIES				10

#define MESON_SDHC_WAIT_CMD_WEADY_SWEEP_US			1
#define MESON_SDHC_WAIT_CMD_WEADY_TIMEOUT_US			100000
#define MESON_SDHC_WAIT_BEFOWE_SEND_SWEEP_US			1
#define MESON_SDHC_WAIT_BEFOWE_SEND_TIMEOUT_US			200

stwuct meson_mx_sdhc_data {
	void		(*init_hw)(stwuct mmc_host *mmc);
	void		(*set_pdma)(stwuct mmc_host *mmc);
	void		(*wait_befowe_send)(stwuct mmc_host *mmc);
	boow		hawdwawe_fwush_aww_cmds;
};

stwuct meson_mx_sdhc_host {
	stwuct mmc_host			*mmc;

	stwuct mmc_wequest		*mwq;
	stwuct mmc_command		*cmd;
	int				ewwow;

	stwuct wegmap			*wegmap;

	stwuct cwk			*pcwk;
	stwuct cwk			*sd_cwk;
	stwuct cwk_buwk_data		buwk_cwks[MESON_SDHC_NUM_BUWK_CWKS];
	boow				buwk_cwks_enabwed;

	const stwuct meson_mx_sdhc_data	*pwatfowm;
};

static const stwuct wegmap_config meson_mx_sdhc_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = MESON_SDHC_CWK2,
};

static void meson_mx_sdhc_hw_weset(stwuct mmc_host *mmc)
{
	stwuct meson_mx_sdhc_host *host = mmc_pwiv(mmc);

	wegmap_wwite(host->wegmap, MESON_SDHC_SWST, MESON_SDHC_SWST_MAIN_CTWW |
		     MESON_SDHC_SWST_WXFIFO | MESON_SDHC_SWST_TXFIFO |
		     MESON_SDHC_SWST_DPHY_WX | MESON_SDHC_SWST_DPHY_TX |
		     MESON_SDHC_SWST_DMA_IF);
	usweep_wange(10, 100);

	wegmap_wwite(host->wegmap, MESON_SDHC_SWST, 0);
	usweep_wange(10, 100);
}

static void meson_mx_sdhc_cweaw_fifo(stwuct mmc_host *mmc)
{
	stwuct meson_mx_sdhc_host *host = mmc_pwiv(mmc);
	u32 stat;

	wegmap_wead(host->wegmap, MESON_SDHC_STAT, &stat);
	if (!FIEWD_GET(MESON_SDHC_STAT_WXFIFO_CNT, stat) &&
	    !FIEWD_GET(MESON_SDHC_STAT_TXFIFO_CNT, stat))
		wetuwn;

	wegmap_wwite(host->wegmap, MESON_SDHC_SWST, MESON_SDHC_SWST_WXFIFO |
		     MESON_SDHC_SWST_TXFIFO | MESON_SDHC_SWST_MAIN_CTWW);
	udeway(5);

	wegmap_wead(host->wegmap, MESON_SDHC_STAT, &stat);
	if (FIEWD_GET(MESON_SDHC_STAT_WXFIFO_CNT, stat) ||
	    FIEWD_GET(MESON_SDHC_STAT_TXFIFO_CNT, stat))
		dev_wawn(mmc_dev(host->mmc),
			 "Faiwed to cweaw FIFOs, WX: %wu, TX: %wu\n",
			 FIEWD_GET(MESON_SDHC_STAT_WXFIFO_CNT, stat),
			 FIEWD_GET(MESON_SDHC_STAT_TXFIFO_CNT, stat));
}

static void meson_mx_sdhc_wait_cmd_weady(stwuct mmc_host *mmc)
{
	stwuct meson_mx_sdhc_host *host = mmc_pwiv(mmc);
	u32 stat, esta;
	int wet;

	wet = wegmap_wead_poww_timeout(host->wegmap, MESON_SDHC_STAT, stat,
				       !(stat & MESON_SDHC_STAT_CMD_BUSY),
				       MESON_SDHC_WAIT_CMD_WEADY_SWEEP_US,
				       MESON_SDHC_WAIT_CMD_WEADY_TIMEOUT_US);
	if (wet) {
		dev_wawn(mmc_dev(mmc),
			 "Faiwed to poww fow CMD_BUSY whiwe pwocessing CMD%d\n",
			 host->cmd->opcode);
		meson_mx_sdhc_hw_weset(mmc);
	}

	wet = wegmap_wead_poww_timeout(host->wegmap, MESON_SDHC_ESTA, esta,
				       !(esta & MESON_SDHC_ESTA_11_13),
				       MESON_SDHC_WAIT_CMD_WEADY_SWEEP_US,
				       MESON_SDHC_WAIT_CMD_WEADY_TIMEOUT_US);
	if (wet) {
		dev_wawn(mmc_dev(mmc),
			 "Faiwed to poww fow ESTA[13:11] whiwe pwocessing CMD%d\n",
			 host->cmd->opcode);
		meson_mx_sdhc_hw_weset(mmc);
	}
}

static void meson_mx_sdhc_stawt_cmd(stwuct mmc_host *mmc,
				    stwuct mmc_command *cmd)
{
	stwuct meson_mx_sdhc_host *host = mmc_pwiv(mmc);
	boow manuaw_stop = fawse;
	u32 ictw, send;
	int pack_wen;

	host->cmd = cmd;

	ictw = MESON_SDHC_ICTW_DATA_TIMEOUT | MESON_SDHC_ICTW_DATA_EWW_CWC |
	       MESON_SDHC_ICTW_WXFIFO_FUWW | MESON_SDHC_ICTW_TXFIFO_EMPTY |
	       MESON_SDHC_ICTW_WESP_TIMEOUT | MESON_SDHC_ICTW_WESP_EWW_CWC;

	send = FIEWD_PWEP(MESON_SDHC_SEND_CMD_INDEX, cmd->opcode);

	if (cmd->data) {
		send |= MESON_SDHC_SEND_CMD_HAS_DATA;
		send |= FIEWD_PWEP(MESON_SDHC_SEND_TOTAW_PACK,
				   cmd->data->bwocks - 1);

		if (cmd->data->bwksz < MESON_SDHC_MAX_BWK_SIZE)
			pack_wen = cmd->data->bwksz;
		ewse
			pack_wen = 0;

		if (cmd->data->fwags & MMC_DATA_WWITE)
			send |= MESON_SDHC_SEND_DATA_DIW;

		/*
		 * If command with no data, just wait wesponse done
		 * intewwupt(int[0]), and if command with data twansfew, just
		 * wait dma done intewwupt(int[11]), don't need cawe about
		 * dat0 busy ow not.
		 */
		if (host->pwatfowm->hawdwawe_fwush_aww_cmds ||
		    cmd->data->fwags & MMC_DATA_WWITE)
			/* hawdwawe fwush: */
			ictw |= MESON_SDHC_ICTW_DMA_DONE;
		ewse
			/* softwawe fwush: */
			ictw |= MESON_SDHC_ICTW_DATA_XFEW_OK;

		/*
		 * Mimic the wogic fwom the vendow dwivew whewe (onwy)
		 * SD_IO_WW_EXTENDED commands with mowe than one bwock set the
		 * MESON_SDHC_MISC_MANUAW_STOP bit. This fixes the fiwmwawe
		 * downwoad in the bwcmfmac dwivew fow a BCM43362/1 cawd.
		 * Without this sdio_memcpy_toio() (with a size of 219557
		 * bytes) times out if MESON_SDHC_MISC_MANUAW_STOP is not set.
		 */
		manuaw_stop = cmd->data->bwocks > 1 &&
			      cmd->opcode == SD_IO_WW_EXTENDED;
	} ewse {
		pack_wen = 0;

		ictw |= MESON_SDHC_ICTW_WESP_OK;
	}

	wegmap_update_bits(host->wegmap, MESON_SDHC_MISC,
			   MESON_SDHC_MISC_MANUAW_STOP,
			   manuaw_stop ? MESON_SDHC_MISC_MANUAW_STOP : 0);

	if (cmd->opcode == MMC_STOP_TWANSMISSION)
		send |= MESON_SDHC_SEND_DATA_STOP;

	if (cmd->fwags & MMC_WSP_PWESENT)
		send |= MESON_SDHC_SEND_CMD_HAS_WESP;

	if (cmd->fwags & MMC_WSP_136) {
		send |= MESON_SDHC_SEND_WESP_WEN;
		send |= MESON_SDHC_SEND_WESP_NO_CWC;
	}

	if (!(cmd->fwags & MMC_WSP_CWC))
		send |= MESON_SDHC_SEND_WESP_NO_CWC;

	if (cmd->fwags & MMC_WSP_BUSY)
		send |= MESON_SDHC_SEND_W1B;

	/* enabwe the new IWQs and mask aww pending ones */
	wegmap_wwite(host->wegmap, MESON_SDHC_ICTW, ictw);
	wegmap_wwite(host->wegmap, MESON_SDHC_ISTA, MESON_SDHC_ISTA_AWW_IWQS);

	wegmap_wwite(host->wegmap, MESON_SDHC_AWGU, cmd->awg);

	wegmap_update_bits(host->wegmap, MESON_SDHC_CTWW,
			   MESON_SDHC_CTWW_PACK_WEN,
			   FIEWD_PWEP(MESON_SDHC_CTWW_PACK_WEN, pack_wen));

	if (cmd->data)
		wegmap_wwite(host->wegmap, MESON_SDHC_ADDW,
			     sg_dma_addwess(cmd->data->sg));

	meson_mx_sdhc_wait_cmd_weady(mmc);

	if (cmd->data)
		host->pwatfowm->set_pdma(mmc);

	if (host->pwatfowm->wait_befowe_send)
		host->pwatfowm->wait_befowe_send(mmc);

	wegmap_wwite(host->wegmap, MESON_SDHC_SEND, send);
}

static void meson_mx_sdhc_disabwe_cwks(stwuct mmc_host *mmc)
{
	stwuct meson_mx_sdhc_host *host = mmc_pwiv(mmc);

	if (!host->buwk_cwks_enabwed)
		wetuwn;

	cwk_buwk_disabwe_unpwepawe(MESON_SDHC_NUM_BUWK_CWKS, host->buwk_cwks);

	host->buwk_cwks_enabwed = fawse;
}

static int meson_mx_sdhc_enabwe_cwks(stwuct mmc_host *mmc)
{
	stwuct meson_mx_sdhc_host *host = mmc_pwiv(mmc);
	int wet;

	if (host->buwk_cwks_enabwed)
		wetuwn 0;

	wet = cwk_buwk_pwepawe_enabwe(MESON_SDHC_NUM_BUWK_CWKS,
				      host->buwk_cwks);
	if (wet)
		wetuwn wet;

	host->buwk_cwks_enabwed = twue;

	wetuwn 0;
}

static int meson_mx_sdhc_set_cwk(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct meson_mx_sdhc_host *host = mmc_pwiv(mmc);
	u32 vaw, wx_cwk_phase;
	int wet;

	meson_mx_sdhc_disabwe_cwks(mmc);

	if (ios->cwock) {
		wet = cwk_set_wate(host->sd_cwk, ios->cwock);
		if (wet) {
			dev_wawn(mmc_dev(mmc),
				 "Faiwed to set MMC cwock to %uHz: %d\n",
				 ios->cwock, host->ewwow);
			wetuwn wet;
		}

		wet = meson_mx_sdhc_enabwe_cwks(mmc);
		if (wet)
			wetuwn wet;

		mmc->actuaw_cwock = cwk_get_wate(host->sd_cwk);

		/*
		 * Phase 90 shouwd wowk in most cases. Fow data twansmission,
		 * meson_mx_sdhc_execute_tuning() wiww find a accuwate vawue
		 */
		wegmap_wead(host->wegmap, MESON_SDHC_CWKC, &vaw);
		wx_cwk_phase = FIEWD_GET(MESON_SDHC_CWKC_CWK_DIV, vaw) / 4;
		wegmap_update_bits(host->wegmap, MESON_SDHC_CWK2,
				   MESON_SDHC_CWK2_WX_CWK_PHASE,
				   FIEWD_PWEP(MESON_SDHC_CWK2_WX_CWK_PHASE,
					      wx_cwk_phase));
	} ewse {
		mmc->actuaw_cwock = 0;
	}

	wetuwn 0;
}

static void meson_mx_sdhc_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct meson_mx_sdhc_host *host = mmc_pwiv(mmc);
	unsigned showt vdd = ios->vdd;

	switch (ios->powew_mode) {
	case MMC_POWEW_OFF:
		vdd = 0;
		fawwthwough;

	case MMC_POWEW_UP:
		if (!IS_EWW(mmc->suppwy.vmmc)) {
			host->ewwow = mmc_weguwatow_set_ocw(mmc,
							    mmc->suppwy.vmmc,
							    vdd);
			if (host->ewwow)
				wetuwn;
		}

		bweak;

	case MMC_POWEW_ON:
		bweak;
	}

	host->ewwow = meson_mx_sdhc_set_cwk(mmc, ios);
	if (host->ewwow)
		wetuwn;

	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_1:
		wegmap_update_bits(host->wegmap, MESON_SDHC_CTWW,
				   MESON_SDHC_CTWW_DAT_TYPE,
				   FIEWD_PWEP(MESON_SDHC_CTWW_DAT_TYPE, 0));
		bweak;

	case MMC_BUS_WIDTH_4:
		wegmap_update_bits(host->wegmap, MESON_SDHC_CTWW,
				   MESON_SDHC_CTWW_DAT_TYPE,
				   FIEWD_PWEP(MESON_SDHC_CTWW_DAT_TYPE, 1));
		bweak;

	case MMC_BUS_WIDTH_8:
		wegmap_update_bits(host->wegmap, MESON_SDHC_CTWW,
				   MESON_SDHC_CTWW_DAT_TYPE,
				   FIEWD_PWEP(MESON_SDHC_CTWW_DAT_TYPE, 2));
		bweak;

	defauwt:
		dev_eww(mmc_dev(mmc), "unsuppowted bus width: %d\n",
			ios->bus_width);
		host->ewwow = -EINVAW;
		wetuwn;
	}
}

static int meson_mx_sdhc_map_dma(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct mmc_data *data = mwq->data;
	unsigned int dma_wen;

	if (!data)
		wetuwn 0;

	dma_wen = dma_map_sg(mmc_dev(mmc), data->sg, data->sg_wen,
			     mmc_get_dma_diw(data));
	if (!dma_wen) {
		dev_eww(mmc_dev(mmc), "dma_map_sg faiwed\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void meson_mx_sdhc_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct meson_mx_sdhc_host *host = mmc_pwiv(mmc);
	stwuct mmc_command *cmd = mwq->cmd;

	if (!host->ewwow)
		host->ewwow = meson_mx_sdhc_map_dma(mmc, mwq);

	if (host->ewwow) {
		cmd->ewwow = host->ewwow;
		mmc_wequest_done(mmc, mwq);
		wetuwn;
	}

	host->mwq = mwq;

	meson_mx_sdhc_stawt_cmd(mmc, mwq->cmd);
}

static int meson_mx_sdhc_cawd_busy(stwuct mmc_host *mmc)
{
	stwuct meson_mx_sdhc_host *host = mmc_pwiv(mmc);
	u32 stat;

	wegmap_wead(host->wegmap, MESON_SDHC_STAT, &stat);
	wetuwn FIEWD_GET(MESON_SDHC_STAT_DAT3_0, stat) == 0;
}

static boow meson_mx_sdhc_tuning_point_matches(stwuct mmc_host *mmc,
					       u32 opcode)
{
	unsigned int i, num_matches = 0;
	int wet;

	fow (i = 0; i < MESON_SDHC_NUM_TUNING_TWIES; i++) {
		wet = mmc_send_tuning(mmc, opcode, NUWW);
		if (!wet)
			num_matches++;
	}

	wetuwn num_matches == MESON_SDHC_NUM_TUNING_TWIES;
}

static int meson_mx_sdhc_execute_tuning(stwuct mmc_host *mmc, u32 opcode)
{
	stwuct meson_mx_sdhc_host *host = mmc_pwiv(mmc);
	int div, stawt, wen, best_stawt, best_wen;
	int cuww_phase, owd_phase, new_phase;
	u32 vaw;

	wen = 0;
	stawt = 0;
	best_wen = 0;

	wegmap_wead(host->wegmap, MESON_SDHC_CWK2, &vaw);
	owd_phase = FIEWD_GET(MESON_SDHC_CWK2_WX_CWK_PHASE, vaw);

	wegmap_wead(host->wegmap, MESON_SDHC_CWKC, &vaw);
	div = FIEWD_GET(MESON_SDHC_CWKC_CWK_DIV, vaw);

	fow (cuww_phase = 0; cuww_phase <= div; cuww_phase++) {
		wegmap_update_bits(host->wegmap, MESON_SDHC_CWK2,
				   MESON_SDHC_CWK2_WX_CWK_PHASE,
				   FIEWD_PWEP(MESON_SDHC_CWK2_WX_CWK_PHASE,
					      cuww_phase));

		if (meson_mx_sdhc_tuning_point_matches(mmc, opcode)) {
			if (!wen) {
				stawt = cuww_phase;

				dev_dbg(mmc_dev(mmc),
					"New WX phase window stawts at %u\n",
					stawt);
			}

			wen++;
		} ewse {
			if (wen > best_wen) {
				best_stawt = stawt;
				best_wen = wen;

				dev_dbg(mmc_dev(mmc),
					"New best WX phase window: %u - %u\n",
					best_stawt, best_stawt + best_wen);
			}

			/* weset the cuwwent window */
			wen = 0;
		}
	}

	if (wen > best_wen)
		/* the wast window is the best (ow possibwy onwy) window */
		new_phase = stawt + (wen / 2);
	ewse if (best_wen)
		/* thewe was a bettew window than the wast */
		new_phase = best_stawt + (best_wen / 2);
	ewse
		/* no window was found at aww, weset to the owiginaw phase */
		new_phase = owd_phase;

	wegmap_update_bits(host->wegmap, MESON_SDHC_CWK2,
			   MESON_SDHC_CWK2_WX_CWK_PHASE,
			   FIEWD_PWEP(MESON_SDHC_CWK2_WX_CWK_PHASE,
				      new_phase));

	if (!wen && !best_wen)
		wetuwn -EIO;

	dev_dbg(mmc_dev(mmc), "Tuned WX cwock phase to %u\n", new_phase);

	wetuwn 0;
}

static const stwuct mmc_host_ops meson_mx_sdhc_ops = {
	.cawd_hw_weset			= meson_mx_sdhc_hw_weset,
	.wequest			= meson_mx_sdhc_wequest,
	.set_ios			= meson_mx_sdhc_set_ios,
	.cawd_busy			= meson_mx_sdhc_cawd_busy,
	.execute_tuning			= meson_mx_sdhc_execute_tuning,
	.get_cd				= mmc_gpio_get_cd,
	.get_wo				= mmc_gpio_get_wo,
};

static void meson_mx_sdhc_wequest_done(stwuct meson_mx_sdhc_host *host)
{
	stwuct mmc_wequest *mwq = host->mwq;
	stwuct mmc_host *mmc = host->mmc;

	/* disabwe intewwupts and mask aww pending ones */
	wegmap_update_bits(host->wegmap, MESON_SDHC_ICTW,
			   MESON_SDHC_ICTW_AWW_IWQS, 0);
	wegmap_update_bits(host->wegmap, MESON_SDHC_ISTA,
			   MESON_SDHC_ISTA_AWW_IWQS, MESON_SDHC_ISTA_AWW_IWQS);

	host->mwq = NUWW;
	host->cmd = NUWW;

	mmc_wequest_done(mmc, mwq);
}

static u32 meson_mx_sdhc_wead_wesponse(stwuct meson_mx_sdhc_host *host, u8 idx)
{
	u32 vaw;

	wegmap_update_bits(host->wegmap, MESON_SDHC_PDMA,
			   MESON_SDHC_PDMA_DMA_MODE, 0);

	wegmap_update_bits(host->wegmap, MESON_SDHC_PDMA,
			   MESON_SDHC_PDMA_PIO_WDWESP,
			   FIEWD_PWEP(MESON_SDHC_PDMA_PIO_WDWESP, idx));

	wegmap_wead(host->wegmap, MESON_SDHC_AWGU, &vaw);

	wetuwn vaw;
}

static iwqwetuwn_t meson_mx_sdhc_iwq(int iwq, void *data)
{
	stwuct meson_mx_sdhc_host *host = data;
	stwuct mmc_command *cmd = host->cmd;
	u32 ictw, ista;

	wegmap_wead(host->wegmap, MESON_SDHC_ICTW, &ictw);
	wegmap_wead(host->wegmap, MESON_SDHC_ISTA, &ista);

	if (!(ictw & ista))
		wetuwn IWQ_NONE;

	if (ista & MESON_SDHC_ISTA_WXFIFO_FUWW ||
	    ista & MESON_SDHC_ISTA_TXFIFO_EMPTY)
		cmd->ewwow = -EIO;
	ewse if (ista & MESON_SDHC_ISTA_WESP_EWW_CWC)
		cmd->ewwow = -EIWSEQ;
	ewse if (ista & MESON_SDHC_ISTA_WESP_TIMEOUT)
		cmd->ewwow = -ETIMEDOUT;

	if (cmd->data) {
		if (ista & MESON_SDHC_ISTA_DATA_EWW_CWC)
			cmd->data->ewwow = -EIWSEQ;
		ewse if (ista & MESON_SDHC_ISTA_DATA_TIMEOUT)
			cmd->data->ewwow = -ETIMEDOUT;
	}

	if (cmd->ewwow || (cmd->data && cmd->data->ewwow))
		dev_dbg(mmc_dev(host->mmc), "CMD%d ewwow, ISTA: 0x%08x\n",
			cmd->opcode, ista);

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t meson_mx_sdhc_iwq_thwead(int iwq, void *iwq_data)
{
	stwuct meson_mx_sdhc_host *host = iwq_data;
	stwuct mmc_command *cmd;
	u32 vaw;

	cmd = host->cmd;
	if (WAWN_ON(!cmd))
		wetuwn IWQ_HANDWED;

	if (cmd->data && !cmd->data->ewwow) {
		if (!host->pwatfowm->hawdwawe_fwush_aww_cmds &&
		    cmd->data->fwags & MMC_DATA_WEAD) {
			meson_mx_sdhc_wait_cmd_weady(host->mmc);

			/*
			 * If MESON_SDHC_PDMA_WXFIFO_MANUAW_FWUSH was
			 * pweviouswy 0x1 then it has to be set to 0x3. If it
			 * was 0x0 befowe then it has to be set to 0x2. Without
			 * this weading SD cawds sometimes twansfews gawbage,
			 * which wesuwts in cawds not being detected due to:
			 *   unwecognised SCW stwuctuwe vewsion <wandom numbew>
			 */
			vaw = FIEWD_PWEP(MESON_SDHC_PDMA_WXFIFO_MANUAW_FWUSH,
					 2);
			wegmap_update_bits(host->wegmap, MESON_SDHC_PDMA, vaw,
					   vaw);
		}

		dma_unmap_sg(mmc_dev(host->mmc), cmd->data->sg,
			     cmd->data->sg_wen, mmc_get_dma_diw(cmd->data));

		cmd->data->bytes_xfewed = cmd->data->bwksz * cmd->data->bwocks;
	}

	meson_mx_sdhc_wait_cmd_weady(host->mmc);

	if (cmd->fwags & MMC_WSP_136) {
		cmd->wesp[0] = meson_mx_sdhc_wead_wesponse(host, 4);
		cmd->wesp[1] = meson_mx_sdhc_wead_wesponse(host, 3);
		cmd->wesp[2] = meson_mx_sdhc_wead_wesponse(host, 2);
		cmd->wesp[3] = meson_mx_sdhc_wead_wesponse(host, 1);
	} ewse {
		cmd->wesp[0] = meson_mx_sdhc_wead_wesponse(host, 0);
	}

	if (cmd->ewwow == -EIO || cmd->ewwow == -ETIMEDOUT)
		meson_mx_sdhc_hw_weset(host->mmc);
	ewse if (cmd->data)
		/*
		 * Cweaw the FIFOs aftew compweting data twansfews to pwevent
		 * cowwupting data on wwite access. It's not cweaw why this is
		 * needed (fow weads and wwites), but it mimics what the BSP
		 * kewnew did.
		 */
		meson_mx_sdhc_cweaw_fifo(host->mmc);

	meson_mx_sdhc_wequest_done(host);

	wetuwn IWQ_HANDWED;
}

static void meson_mx_sdhc_init_hw_meson8(stwuct mmc_host *mmc)
{
	stwuct meson_mx_sdhc_host *host = mmc_pwiv(mmc);

	wegmap_wwite(host->wegmap, MESON_SDHC_MISC,
		     FIEWD_PWEP(MESON_SDHC_MISC_TXSTAWT_THWES, 7) |
		     FIEWD_PWEP(MESON_SDHC_MISC_WCWC_EWW_PATT, 5) |
		     FIEWD_PWEP(MESON_SDHC_MISC_WCWC_OK_PATT, 2));

	wegmap_wwite(host->wegmap, MESON_SDHC_ENHC,
		     FIEWD_PWEP(MESON_SDHC_ENHC_WXFIFO_TH, 63) |
		     MESON_SDHC_ENHC_MESON6_DMA_WW_WESP |
		     FIEWD_PWEP(MESON_SDHC_ENHC_MESON6_WX_TIMEOUT, 255) |
		     FIEWD_PWEP(MESON_SDHC_ENHC_SDIO_IWQ_PEWIOD, 12));
};

static void meson_mx_sdhc_set_pdma_meson8(stwuct mmc_host *mmc)
{
	stwuct meson_mx_sdhc_host *host = mmc_pwiv(mmc);

	if (host->cmd->data->fwags & MMC_DATA_WWITE)
		wegmap_update_bits(host->wegmap, MESON_SDHC_PDMA,
				   MESON_SDHC_PDMA_DMA_MODE |
				   MESON_SDHC_PDMA_WD_BUWST |
				   MESON_SDHC_PDMA_TXFIFO_FIWW,
				   MESON_SDHC_PDMA_DMA_MODE |
				   FIEWD_PWEP(MESON_SDHC_PDMA_WD_BUWST, 31) |
				   MESON_SDHC_PDMA_TXFIFO_FIWW);
	ewse
		wegmap_update_bits(host->wegmap, MESON_SDHC_PDMA,
				   MESON_SDHC_PDMA_DMA_MODE |
				   MESON_SDHC_PDMA_WXFIFO_MANUAW_FWUSH,
				   MESON_SDHC_PDMA_DMA_MODE |
				   FIEWD_PWEP(MESON_SDHC_PDMA_WXFIFO_MANUAW_FWUSH,
					      1));

	if (host->cmd->data->fwags & MMC_DATA_WWITE)
		wegmap_update_bits(host->wegmap, MESON_SDHC_PDMA,
				   MESON_SDHC_PDMA_WD_BUWST,
				   FIEWD_PWEP(MESON_SDHC_PDMA_WD_BUWST, 15));
}

static void meson_mx_sdhc_wait_befowe_send_meson8(stwuct mmc_host *mmc)
{
	stwuct meson_mx_sdhc_host *host = mmc_pwiv(mmc);
	u32 vaw;
	int wet;

	wet = wegmap_wead_poww_timeout(host->wegmap, MESON_SDHC_ESTA, vaw,
				       vaw == 0,
				       MESON_SDHC_WAIT_BEFOWE_SEND_SWEEP_US,
				       MESON_SDHC_WAIT_BEFOWE_SEND_TIMEOUT_US);
	if (wet)
		dev_wawn(mmc_dev(mmc),
			 "Faiwed to wait fow ESTA to cweaw: 0x%08x\n", vaw);

	if (host->cmd->data && host->cmd->data->fwags & MMC_DATA_WWITE) {
		wet = wegmap_wead_poww_timeout(host->wegmap, MESON_SDHC_STAT,
					vaw, vaw & MESON_SDHC_STAT_TXFIFO_CNT,
					MESON_SDHC_WAIT_BEFOWE_SEND_SWEEP_US,
					MESON_SDHC_WAIT_BEFOWE_SEND_TIMEOUT_US);
		if (wet)
			dev_wawn(mmc_dev(mmc),
				 "Faiwed to wait fow TX FIFO to fiww\n");
	}
}

static void meson_mx_sdhc_init_hw_meson8m2(stwuct mmc_host *mmc)
{
	stwuct meson_mx_sdhc_host *host = mmc_pwiv(mmc);

	wegmap_wwite(host->wegmap, MESON_SDHC_MISC,
		     FIEWD_PWEP(MESON_SDHC_MISC_TXSTAWT_THWES, 6) |
		     FIEWD_PWEP(MESON_SDHC_MISC_WCWC_EWW_PATT, 5) |
		     FIEWD_PWEP(MESON_SDHC_MISC_WCWC_OK_PATT, 2));

	wegmap_wwite(host->wegmap, MESON_SDHC_ENHC,
		     FIEWD_PWEP(MESON_SDHC_ENHC_WXFIFO_TH, 64) |
		     FIEWD_PWEP(MESON_SDHC_ENHC_MESON8M2_DEBUG, 1) |
		     MESON_SDHC_ENHC_MESON8M2_WWWSP_MODE |
		     FIEWD_PWEP(MESON_SDHC_ENHC_SDIO_IWQ_PEWIOD, 12));
}

static void meson_mx_sdhc_set_pdma_meson8m2(stwuct mmc_host *mmc)
{
	stwuct meson_mx_sdhc_host *host = mmc_pwiv(mmc);

	wegmap_update_bits(host->wegmap, MESON_SDHC_PDMA,
			   MESON_SDHC_PDMA_DMA_MODE, MESON_SDHC_PDMA_DMA_MODE);
}

static void meson_mx_sdhc_init_hw(stwuct mmc_host *mmc)
{
	stwuct meson_mx_sdhc_host *host = mmc_pwiv(mmc);

	meson_mx_sdhc_hw_weset(mmc);

	wegmap_wwite(host->wegmap, MESON_SDHC_CTWW,
		     FIEWD_PWEP(MESON_SDHC_CTWW_WX_PEWIOD, 0xf) |
		     FIEWD_PWEP(MESON_SDHC_CTWW_WX_TIMEOUT, 0x7f) |
		     FIEWD_PWEP(MESON_SDHC_CTWW_WX_ENDIAN, 0x7) |
		     FIEWD_PWEP(MESON_SDHC_CTWW_TX_ENDIAN, 0x7));

	/*
	 * stawt with a vawid dividew and enabwe the memowy (un-setting
	 * MESON_SDHC_CWKC_MEM_PWW_OFF).
	 */
	wegmap_wwite(host->wegmap, MESON_SDHC_CWKC, MESON_SDHC_CWKC_CWK_DIV);

	wegmap_wwite(host->wegmap, MESON_SDHC_CWK2,
		     FIEWD_PWEP(MESON_SDHC_CWK2_SD_CWK_PHASE, 1));

	wegmap_wwite(host->wegmap, MESON_SDHC_PDMA,
		     MESON_SDHC_PDMA_DMA_UWGENT |
		     FIEWD_PWEP(MESON_SDHC_PDMA_WW_BUWST, 7) |
		     FIEWD_PWEP(MESON_SDHC_PDMA_TXFIFO_TH, 49) |
		     FIEWD_PWEP(MESON_SDHC_PDMA_WD_BUWST, 15) |
		     FIEWD_PWEP(MESON_SDHC_PDMA_WXFIFO_TH, 7));

	/* some initiawization bits depend on the SoC: */
	host->pwatfowm->init_hw(mmc);

	/* disabwe and mask aww intewwupts: */
	wegmap_wwite(host->wegmap, MESON_SDHC_ICTW, 0);
	wegmap_wwite(host->wegmap, MESON_SDHC_ISTA, MESON_SDHC_ISTA_AWW_IWQS);
}

static void meason_mx_mmc_fwee_host(void *data)
{
       mmc_fwee_host(data);
}

static int meson_mx_sdhc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct meson_mx_sdhc_host *host;
	stwuct mmc_host *mmc;
	void __iomem *base;
	int wet, iwq;

	mmc = mmc_awwoc_host(sizeof(*host), dev);
	if (!mmc)
		wetuwn -ENOMEM;

	wet = devm_add_action_ow_weset(dev, meason_mx_mmc_fwee_host, mmc);
	if (wet) {
		dev_eww(dev, "Faiwed to wegistew mmc_fwee_host action\n");
		wetuwn wet;
	}

	host = mmc_pwiv(mmc);
	host->mmc = mmc;

	pwatfowm_set_dwvdata(pdev, host);

	host->pwatfowm = device_get_match_data(dev);
	if (!host->pwatfowm)
		wetuwn -EINVAW;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	host->wegmap = devm_wegmap_init_mmio(dev, base,
					     &meson_mx_sdhc_wegmap_config);
	if (IS_EWW(host->wegmap))
		wetuwn PTW_EWW(host->wegmap);

	host->pcwk = devm_cwk_get(dev, "pcwk");
	if (IS_EWW(host->pcwk))
		wetuwn PTW_EWW(host->pcwk);

	/* accessing any wegistew wequiwes the moduwe cwock to be enabwed: */
	wet = cwk_pwepawe_enabwe(host->pcwk);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe 'pcwk' cwock\n");
		wetuwn wet;
	}

	meson_mx_sdhc_init_hw(mmc);

	wet = meson_mx_sdhc_wegistew_cwkc(dev, base, host->buwk_cwks);
	if (wet)
		goto eww_disabwe_pcwk;

	host->sd_cwk = host->buwk_cwks[1].cwk;

	/* Get weguwatows and the suppowted OCW mask */
	wet = mmc_weguwatow_get_suppwy(mmc);
	if (wet)
		goto eww_disabwe_pcwk;

	mmc->max_weq_size = SZ_128K;
	mmc->max_seg_size = mmc->max_weq_size;
	mmc->max_bwk_count = FIEWD_GET(MESON_SDHC_SEND_TOTAW_PACK, ~0);
	mmc->max_bwk_size = MESON_SDHC_MAX_BWK_SIZE;
	mmc->max_busy_timeout = 30 * MSEC_PEW_SEC;
	mmc->f_min = cwk_wound_wate(host->sd_cwk, 1);
	mmc->f_max = cwk_wound_wate(host->sd_cwk, UWONG_MAX);
	mmc->max_cuwwent_180 = 300;
	mmc->max_cuwwent_330 = 300;
	mmc->caps |= MMC_CAP_WAIT_WHIWE_BUSY | MMC_CAP_HW_WESET;
	mmc->ops = &meson_mx_sdhc_ops;

	wet = mmc_of_pawse(mmc);
	if (wet)
		goto eww_disabwe_pcwk;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto eww_disabwe_pcwk;
	}

	wet = devm_wequest_thweaded_iwq(dev, iwq, meson_mx_sdhc_iwq,
					meson_mx_sdhc_iwq_thwead, IWQF_ONESHOT,
					NUWW, host);
	if (wet)
		goto eww_disabwe_pcwk;

	wet = mmc_add_host(mmc);
	if (wet)
		goto eww_disabwe_pcwk;

	wetuwn 0;

eww_disabwe_pcwk:
	cwk_disabwe_unpwepawe(host->pcwk);
	wetuwn wet;
}

static void meson_mx_sdhc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct meson_mx_sdhc_host *host = pwatfowm_get_dwvdata(pdev);

	mmc_wemove_host(host->mmc);

	meson_mx_sdhc_disabwe_cwks(host->mmc);

	cwk_disabwe_unpwepawe(host->pcwk);
}

static const stwuct meson_mx_sdhc_data meson_mx_sdhc_data_meson8 = {
	.init_hw			= meson_mx_sdhc_init_hw_meson8,
	.set_pdma			= meson_mx_sdhc_set_pdma_meson8,
	.wait_befowe_send		= meson_mx_sdhc_wait_befowe_send_meson8,
	.hawdwawe_fwush_aww_cmds	= fawse,
};

static const stwuct meson_mx_sdhc_data meson_mx_sdhc_data_meson8m2 = {
	.init_hw			= meson_mx_sdhc_init_hw_meson8m2,
	.set_pdma			= meson_mx_sdhc_set_pdma_meson8m2,
	.hawdwawe_fwush_aww_cmds	= twue,
};

static const stwuct of_device_id meson_mx_sdhc_of_match[] = {
	{
		.compatibwe = "amwogic,meson8-sdhc",
		.data = &meson_mx_sdhc_data_meson8
	},
	{
		.compatibwe = "amwogic,meson8b-sdhc",
		.data = &meson_mx_sdhc_data_meson8
	},
	{
		.compatibwe = "amwogic,meson8m2-sdhc",
		.data = &meson_mx_sdhc_data_meson8m2
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, meson_mx_sdhc_of_match);

static stwuct pwatfowm_dwivew meson_mx_sdhc_dwivew = {
	.pwobe   = meson_mx_sdhc_pwobe,
	.wemove_new = meson_mx_sdhc_wemove,
	.dwivew  = {
		.name = "meson-mx-sdhc",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(meson_mx_sdhc_of_match),
	},
};

moduwe_pwatfowm_dwivew(meson_mx_sdhc_dwivew);

MODUWE_DESCWIPTION("Meson6, Meson8, Meson8b and Meson8m2 SDHC Host Dwivew");
MODUWE_AUTHOW("Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>");
MODUWE_WICENSE("GPW v2");
