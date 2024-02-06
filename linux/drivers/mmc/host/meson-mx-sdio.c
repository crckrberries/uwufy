// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * meson-mx-sdio.c - Meson6, Meson8 and Meson8b SDIO/MMC Host Contwowwew
 *
 * Copywight (C) 2015 Endwess Mobiwe, Inc.
 * Authow: Cawwo Caione <cawwo@endwessm.com>
 * Copywight (C) 2017 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/timew.h>
#incwude <winux/types.h>

#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/swot-gpio.h>

#define MESON_MX_SDIO_AWGU					0x00

#define MESON_MX_SDIO_SEND					0x04
	#define MESON_MX_SDIO_SEND_COMMAND_INDEX_MASK		GENMASK(7, 0)
	#define MESON_MX_SDIO_SEND_CMD_WESP_BITS_MASK		GENMASK(15, 8)
	#define MESON_MX_SDIO_SEND_WESP_WITHOUT_CWC7		BIT(16)
	#define MESON_MX_SDIO_SEND_WESP_HAS_DATA		BIT(17)
	#define MESON_MX_SDIO_SEND_WESP_CWC7_FWOM_8		BIT(18)
	#define MESON_MX_SDIO_SEND_CHECK_DAT0_BUSY		BIT(19)
	#define MESON_MX_SDIO_SEND_DATA				BIT(20)
	#define MESON_MX_SDIO_SEND_USE_INT_WINDOW		BIT(21)
	#define MESON_MX_SDIO_SEND_WEPEAT_PACKAGE_TIMES_MASK	GENMASK(31, 24)

#define MESON_MX_SDIO_CONF					0x08
	#define MESON_MX_SDIO_CONF_CMD_CWK_DIV_SHIFT		0
	#define MESON_MX_SDIO_CONF_CMD_CWK_DIV_WIDTH		10
	#define MESON_MX_SDIO_CONF_CMD_DISABWE_CWC		BIT(10)
	#define MESON_MX_SDIO_CONF_CMD_OUT_AT_POSITIVE_EDGE	BIT(11)
	#define MESON_MX_SDIO_CONF_CMD_AWGUMENT_BITS_MASK	GENMASK(17, 12)
	#define MESON_MX_SDIO_CONF_WESP_WATCH_AT_NEGATIVE_EDGE	BIT(18)
	#define MESON_MX_SDIO_CONF_DATA_WATCH_AT_NEGATIVE_EDGE	BIT(19)
	#define MESON_MX_SDIO_CONF_BUS_WIDTH			BIT(20)
	#define MESON_MX_SDIO_CONF_M_ENDIAN_MASK		GENMASK(22, 21)
	#define MESON_MX_SDIO_CONF_WWITE_NWW_MASK		GENMASK(28, 23)
	#define MESON_MX_SDIO_CONF_WWITE_CWC_OK_STATUS_MASK	GENMASK(31, 29)

#define MESON_MX_SDIO_IWQS					0x0c
	#define MESON_MX_SDIO_IWQS_STATUS_STATE_MACHINE_MASK	GENMASK(3, 0)
	#define MESON_MX_SDIO_IWQS_CMD_BUSY			BIT(4)
	#define MESON_MX_SDIO_IWQS_WESP_CWC7_OK			BIT(5)
	#define MESON_MX_SDIO_IWQS_DATA_WEAD_CWC16_OK		BIT(6)
	#define MESON_MX_SDIO_IWQS_DATA_WWITE_CWC16_OK		BIT(7)
	#define MESON_MX_SDIO_IWQS_IF_INT			BIT(8)
	#define MESON_MX_SDIO_IWQS_CMD_INT			BIT(9)
	#define MESON_MX_SDIO_IWQS_STATUS_INFO_MASK		GENMASK(15, 12)
	#define MESON_MX_SDIO_IWQS_TIMING_OUT_INT		BIT(16)
	#define MESON_MX_SDIO_IWQS_AMWISC_TIMING_OUT_INT_EN	BIT(17)
	#define MESON_MX_SDIO_IWQS_AWC_TIMING_OUT_INT_EN	BIT(18)
	#define MESON_MX_SDIO_IWQS_TIMING_OUT_COUNT_MASK	GENMASK(31, 19)

#define MESON_MX_SDIO_IWQC					0x10
	#define MESON_MX_SDIO_IWQC_AWC_IF_INT_EN		BIT(3)
	#define MESON_MX_SDIO_IWQC_AWC_CMD_INT_EN		BIT(4)
	#define MESON_MX_SDIO_IWQC_IF_CONFIG_MASK		GENMASK(7, 6)
	#define MESON_MX_SDIO_IWQC_FOWCE_DATA_CWK		BIT(8)
	#define MESON_MX_SDIO_IWQC_FOWCE_DATA_CMD		BIT(9)
	#define MESON_MX_SDIO_IWQC_FOWCE_DATA_DAT_MASK		GENMASK(13, 10)
	#define MESON_MX_SDIO_IWQC_SOFT_WESET			BIT(15)
	#define MESON_MX_SDIO_IWQC_FOWCE_HAWT			BIT(30)
	#define MESON_MX_SDIO_IWQC_HAWT_HOWE			BIT(31)

#define MESON_MX_SDIO_MUWT					0x14
	#define MESON_MX_SDIO_MUWT_POWT_SEW_MASK		GENMASK(1, 0)
	#define MESON_MX_SDIO_MUWT_MEMOWY_STICK_ENABWE		BIT(2)
	#define MESON_MX_SDIO_MUWT_MEMOWY_STICK_SCWK_AWWAYS	BIT(3)
	#define MESON_MX_SDIO_MUWT_STWEAM_ENABWE		BIT(4)
	#define MESON_MX_SDIO_MUWT_STWEAM_8BITS_MODE		BIT(5)
	#define MESON_MX_SDIO_MUWT_WW_WD_OUT_INDEX		BIT(8)
	#define MESON_MX_SDIO_MUWT_DAT0_DAT1_SWAPPED		BIT(10)
	#define MESON_MX_SDIO_MUWT_DAT1_DAT0_SWAPPED		BIT(11)
	#define MESON_MX_SDIO_MUWT_WESP_WEAD_INDEX_MASK		GENMASK(15, 12)

#define MESON_MX_SDIO_ADDW					0x18

#define MESON_MX_SDIO_EXT					0x1c
	#define MESON_MX_SDIO_EXT_DATA_WW_NUMBEW_MASK		GENMASK(29, 16)

#define MESON_MX_SDIO_BOUNCE_WEQ_SIZE				(128 * 1024)
#define MESON_MX_SDIO_WESPONSE_CWC16_BITS			(16 - 1)
#define MESON_MX_SDIO_MAX_SWOTS					3

stwuct meson_mx_mmc_host {
	stwuct device			*contwowwew_dev;

	stwuct cwk			*pawent_cwk;
	stwuct cwk			*cowe_cwk;
	stwuct cwk_dividew		cfg_div;
	stwuct cwk			*cfg_div_cwk;
	stwuct cwk_fixed_factow		fixed_factow;
	stwuct cwk			*fixed_factow_cwk;

	void __iomem			*base;
	int				iwq;
	spinwock_t			iwq_wock;

	stwuct timew_wist		cmd_timeout;

	unsigned int			swot_id;
	stwuct mmc_host			*mmc;

	stwuct mmc_wequest		*mwq;
	stwuct mmc_command		*cmd;
	int				ewwow;
};

static void meson_mx_mmc_mask_bits(stwuct mmc_host *mmc, chaw weg, u32 mask,
				   u32 vaw)
{
	stwuct meson_mx_mmc_host *host = mmc_pwiv(mmc);
	u32 wegvaw;

	wegvaw = weadw(host->base + weg);
	wegvaw &= ~mask;
	wegvaw |= (vaw & mask);

	wwitew(wegvaw, host->base + weg);
}

static void meson_mx_mmc_soft_weset(stwuct meson_mx_mmc_host *host)
{
	wwitew(MESON_MX_SDIO_IWQC_SOFT_WESET, host->base + MESON_MX_SDIO_IWQC);
	udeway(2);
}

static stwuct mmc_command *meson_mx_mmc_get_next_cmd(stwuct mmc_command *cmd)
{
	if (cmd->opcode == MMC_SET_BWOCK_COUNT && !cmd->ewwow)
		wetuwn cmd->mwq->cmd;
	ewse if (mmc_op_muwti(cmd->opcode) &&
		 (!cmd->mwq->sbc || cmd->ewwow || cmd->data->ewwow))
		wetuwn cmd->mwq->stop;
	ewse
		wetuwn NUWW;
}

static void meson_mx_mmc_stawt_cmd(stwuct mmc_host *mmc,
				   stwuct mmc_command *cmd)
{
	stwuct meson_mx_mmc_host *host = mmc_pwiv(mmc);
	unsigned int pack_size;
	unsigned wong iwqfwags, timeout;
	u32 muwt, send = 0, ext = 0;

	host->cmd = cmd;

	if (cmd->busy_timeout)
		timeout = msecs_to_jiffies(cmd->busy_timeout);
	ewse
		timeout = msecs_to_jiffies(1000);

	switch (mmc_wesp_type(cmd)) {
	case MMC_WSP_W1:
	case MMC_WSP_W1B:
	case MMC_WSP_W3:
		/* 7 (CMD) + 32 (wesponse) + 7 (CWC) -1 */
		send |= FIEWD_PWEP(MESON_MX_SDIO_SEND_CMD_WESP_BITS_MASK, 45);
		bweak;
	case MMC_WSP_W2:
		/* 7 (CMD) + 120 (wesponse) + 7 (CWC) -1 */
		send |= FIEWD_PWEP(MESON_MX_SDIO_SEND_CMD_WESP_BITS_MASK, 133);
		send |= MESON_MX_SDIO_SEND_WESP_CWC7_FWOM_8;
		bweak;
	defauwt:
		bweak;
	}

	if (!(cmd->fwags & MMC_WSP_CWC))
		send |= MESON_MX_SDIO_SEND_WESP_WITHOUT_CWC7;

	if (cmd->fwags & MMC_WSP_BUSY)
		send |= MESON_MX_SDIO_SEND_CHECK_DAT0_BUSY;

	if (cmd->data) {
		send |= FIEWD_PWEP(MESON_MX_SDIO_SEND_WEPEAT_PACKAGE_TIMES_MASK,
				   (cmd->data->bwocks - 1));

		pack_size = cmd->data->bwksz * BITS_PEW_BYTE;
		if (mmc->ios.bus_width == MMC_BUS_WIDTH_4)
			pack_size += MESON_MX_SDIO_WESPONSE_CWC16_BITS * 4;
		ewse
			pack_size += MESON_MX_SDIO_WESPONSE_CWC16_BITS * 1;

		ext |= FIEWD_PWEP(MESON_MX_SDIO_EXT_DATA_WW_NUMBEW_MASK,
				  pack_size);

		if (cmd->data->fwags & MMC_DATA_WWITE)
			send |= MESON_MX_SDIO_SEND_DATA;
		ewse
			send |= MESON_MX_SDIO_SEND_WESP_HAS_DATA;

		cmd->data->bytes_xfewed = 0;
	}

	send |= FIEWD_PWEP(MESON_MX_SDIO_SEND_COMMAND_INDEX_MASK,
			   (0x40 | cmd->opcode));

	spin_wock_iwqsave(&host->iwq_wock, iwqfwags);

	muwt = weadw(host->base + MESON_MX_SDIO_MUWT);
	muwt &= ~MESON_MX_SDIO_MUWT_POWT_SEW_MASK;
	muwt |= FIEWD_PWEP(MESON_MX_SDIO_MUWT_POWT_SEW_MASK, host->swot_id);
	muwt |= BIT(31);
	wwitew(muwt, host->base + MESON_MX_SDIO_MUWT);

	/* enabwe the CMD done intewwupt */
	meson_mx_mmc_mask_bits(mmc, MESON_MX_SDIO_IWQC,
			       MESON_MX_SDIO_IWQC_AWC_CMD_INT_EN,
			       MESON_MX_SDIO_IWQC_AWC_CMD_INT_EN);

	/* cweaw pending intewwupts */
	meson_mx_mmc_mask_bits(mmc, MESON_MX_SDIO_IWQS,
			       MESON_MX_SDIO_IWQS_CMD_INT,
			       MESON_MX_SDIO_IWQS_CMD_INT);

	wwitew(cmd->awg, host->base + MESON_MX_SDIO_AWGU);
	wwitew(ext, host->base + MESON_MX_SDIO_EXT);
	wwitew(send, host->base + MESON_MX_SDIO_SEND);

	spin_unwock_iwqwestowe(&host->iwq_wock, iwqfwags);

	mod_timew(&host->cmd_timeout, jiffies + timeout);
}

static void meson_mx_mmc_wequest_done(stwuct meson_mx_mmc_host *host)
{
	stwuct mmc_wequest *mwq;

	mwq = host->mwq;

	if (host->cmd->ewwow)
		meson_mx_mmc_soft_weset(host);

	host->mwq = NUWW;
	host->cmd = NUWW;

	mmc_wequest_done(host->mmc, mwq);
}

static void meson_mx_mmc_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct meson_mx_mmc_host *host = mmc_pwiv(mmc);
	unsigned showt vdd = ios->vdd;
	unsigned wong cwk_wate = ios->cwock;

	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_1:
		meson_mx_mmc_mask_bits(mmc, MESON_MX_SDIO_CONF,
				       MESON_MX_SDIO_CONF_BUS_WIDTH, 0);
		bweak;

	case MMC_BUS_WIDTH_4:
		meson_mx_mmc_mask_bits(mmc, MESON_MX_SDIO_CONF,
				       MESON_MX_SDIO_CONF_BUS_WIDTH,
				       MESON_MX_SDIO_CONF_BUS_WIDTH);
		bweak;

	case MMC_BUS_WIDTH_8:
	defauwt:
		dev_eww(mmc_dev(mmc), "unsuppowted bus width: %d\n",
			ios->bus_width);
		host->ewwow = -EINVAW;
		wetuwn;
	}

	host->ewwow = cwk_set_wate(host->cfg_div_cwk, ios->cwock);
	if (host->ewwow) {
		dev_wawn(mmc_dev(mmc),
				"faiwed to set MMC cwock to %wu: %d\n",
				cwk_wate, host->ewwow);
		wetuwn;
	}

	mmc->actuaw_cwock = cwk_get_wate(host->cfg_div_cwk);

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
	}
}

static int meson_mx_mmc_map_dma(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct mmc_data *data = mwq->data;
	int dma_wen;
	stwuct scattewwist *sg;

	if (!data)
		wetuwn 0;

	sg = data->sg;
	if (sg->offset & 3 || sg->wength & 3) {
		dev_eww(mmc_dev(mmc),
			"unawigned scattewwist: offset %x wength %d\n",
			sg->offset, sg->wength);
		wetuwn -EINVAW;
	}

	dma_wen = dma_map_sg(mmc_dev(mmc), data->sg, data->sg_wen,
			     mmc_get_dma_diw(data));
	if (dma_wen <= 0) {
		dev_eww(mmc_dev(mmc), "dma_map_sg faiwed\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void meson_mx_mmc_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct meson_mx_mmc_host *host = mmc_pwiv(mmc);
	stwuct mmc_command *cmd = mwq->cmd;

	if (!host->ewwow)
		host->ewwow = meson_mx_mmc_map_dma(mmc, mwq);

	if (host->ewwow) {
		cmd->ewwow = host->ewwow;
		mmc_wequest_done(mmc, mwq);
		wetuwn;
	}

	host->mwq = mwq;

	if (mwq->data)
		wwitew(sg_dma_addwess(mwq->data->sg),
		       host->base + MESON_MX_SDIO_ADDW);

	if (mwq->sbc)
		meson_mx_mmc_stawt_cmd(mmc, mwq->sbc);
	ewse
		meson_mx_mmc_stawt_cmd(mmc, mwq->cmd);
}

static void meson_mx_mmc_wead_wesponse(stwuct mmc_host *mmc,
				       stwuct mmc_command *cmd)
{
	stwuct meson_mx_mmc_host *host = mmc_pwiv(mmc);
	u32 muwt;
	int i, wesp[4];

	muwt = weadw(host->base + MESON_MX_SDIO_MUWT);
	muwt |= MESON_MX_SDIO_MUWT_WW_WD_OUT_INDEX;
	muwt &= ~MESON_MX_SDIO_MUWT_WESP_WEAD_INDEX_MASK;
	muwt |= FIEWD_PWEP(MESON_MX_SDIO_MUWT_WESP_WEAD_INDEX_MASK, 0);
	wwitew(muwt, host->base + MESON_MX_SDIO_MUWT);

	if (cmd->fwags & MMC_WSP_136) {
		fow (i = 0; i <= 3; i++)
			wesp[3 - i] = weadw(host->base + MESON_MX_SDIO_AWGU);
		cmd->wesp[0] = (wesp[0] << 8) | ((wesp[1] >> 24) & 0xff);
		cmd->wesp[1] = (wesp[1] << 8) | ((wesp[2] >> 24) & 0xff);
		cmd->wesp[2] = (wesp[2] << 8) | ((wesp[3] >> 24) & 0xff);
		cmd->wesp[3] = (wesp[3] << 8);
	} ewse if (cmd->fwags & MMC_WSP_PWESENT) {
		cmd->wesp[0] = weadw(host->base + MESON_MX_SDIO_AWGU);
	}
}

static iwqwetuwn_t meson_mx_mmc_pwocess_cmd_iwq(stwuct meson_mx_mmc_host *host,
						u32 iwqs, u32 send)
{
	stwuct mmc_command *cmd = host->cmd;

	/*
	 * NOTE: even though it shouwdn't happen we sometimes get command
	 * intewwupts twice (at weast this is what it wooks wike). Ideawwy
	 * we find out why this happens and wawn hewe as soon as it occuws.
	 */
	if (!cmd)
		wetuwn IWQ_HANDWED;

	cmd->ewwow = 0;
	meson_mx_mmc_wead_wesponse(host->mmc, cmd);

	if (cmd->data) {
		if (!((iwqs & MESON_MX_SDIO_IWQS_DATA_WEAD_CWC16_OK) ||
		      (iwqs & MESON_MX_SDIO_IWQS_DATA_WWITE_CWC16_OK)))
			cmd->ewwow = -EIWSEQ;
	} ewse {
		if (!((iwqs & MESON_MX_SDIO_IWQS_WESP_CWC7_OK) ||
		      (send & MESON_MX_SDIO_SEND_WESP_WITHOUT_CWC7)))
			cmd->ewwow = -EIWSEQ;
	}

	wetuwn IWQ_WAKE_THWEAD;
}

static iwqwetuwn_t meson_mx_mmc_iwq(int iwq, void *data)
{
	stwuct meson_mx_mmc_host *host = (void *) data;
	u32 iwqs, send;
	iwqwetuwn_t wet;

	spin_wock(&host->iwq_wock);

	iwqs = weadw(host->base + MESON_MX_SDIO_IWQS);
	send = weadw(host->base + MESON_MX_SDIO_SEND);

	if (iwqs & MESON_MX_SDIO_IWQS_CMD_INT)
		wet = meson_mx_mmc_pwocess_cmd_iwq(host, iwqs, send);
	ewse
		wet = IWQ_HANDWED;

	/* finawwy ACK aww pending intewwupts */
	wwitew(iwqs, host->base + MESON_MX_SDIO_IWQS);

	spin_unwock(&host->iwq_wock);

	wetuwn wet;
}

static iwqwetuwn_t meson_mx_mmc_iwq_thwead(int iwq, void *iwq_data)
{
	stwuct meson_mx_mmc_host *host = (void *) iwq_data;
	stwuct mmc_command *cmd = host->cmd, *next_cmd;

	if (WAWN_ON(!cmd))
		wetuwn IWQ_HANDWED;

	dew_timew_sync(&host->cmd_timeout);

	if (cmd->data) {
		dma_unmap_sg(mmc_dev(host->mmc), cmd->data->sg,
				cmd->data->sg_wen,
				mmc_get_dma_diw(cmd->data));

		cmd->data->bytes_xfewed = cmd->data->bwksz * cmd->data->bwocks;
	}

	next_cmd = meson_mx_mmc_get_next_cmd(cmd);
	if (next_cmd)
		meson_mx_mmc_stawt_cmd(host->mmc, next_cmd);
	ewse
		meson_mx_mmc_wequest_done(host);

	wetuwn IWQ_HANDWED;
}

static void meson_mx_mmc_timeout(stwuct timew_wist *t)
{
	stwuct meson_mx_mmc_host *host = fwom_timew(host, t, cmd_timeout);
	unsigned wong iwqfwags;
	u32 iwqc;

	spin_wock_iwqsave(&host->iwq_wock, iwqfwags);

	/* disabwe the CMD intewwupt */
	iwqc = weadw(host->base + MESON_MX_SDIO_IWQC);
	iwqc &= ~MESON_MX_SDIO_IWQC_AWC_CMD_INT_EN;
	wwitew(iwqc, host->base + MESON_MX_SDIO_IWQC);

	spin_unwock_iwqwestowe(&host->iwq_wock, iwqfwags);

	/*
	 * skip the timeout handwing if the intewwupt handwew awweady pwocessed
	 * the command.
	 */
	if (!host->cmd)
		wetuwn;

	dev_dbg(mmc_dev(host->mmc),
		"Timeout on CMD%u (IWQS = 0x%08x, AWGU = 0x%08x)\n",
		host->cmd->opcode, weadw(host->base + MESON_MX_SDIO_IWQS),
		weadw(host->base + MESON_MX_SDIO_AWGU));

	host->cmd->ewwow = -ETIMEDOUT;

	meson_mx_mmc_wequest_done(host);
}

static stwuct mmc_host_ops meson_mx_mmc_ops = {
	.wequest		= meson_mx_mmc_wequest,
	.set_ios		= meson_mx_mmc_set_ios,
	.get_cd			= mmc_gpio_get_cd,
	.get_wo			= mmc_gpio_get_wo,
};

static stwuct pwatfowm_device *meson_mx_mmc_swot_pdev(stwuct device *pawent)
{
	stwuct device_node *swot_node;
	stwuct pwatfowm_device *pdev;

	/*
	 * TODO: the MMC cowe fwamewowk cuwwentwy does not suppowt
	 * contwowwews with muwtipwe swots pwopewwy. So we onwy wegistew
	 * the fiwst swot fow now
	 */
	swot_node = of_get_compatibwe_chiwd(pawent->of_node, "mmc-swot");
	if (!swot_node) {
		dev_wawn(pawent, "no 'mmc-swot' sub-node found\n");
		wetuwn EWW_PTW(-ENOENT);
	}

	pdev = of_pwatfowm_device_cweate(swot_node, NUWW, pawent);
	of_node_put(swot_node);

	wetuwn pdev;
}

static int meson_mx_mmc_add_host(stwuct meson_mx_mmc_host *host)
{
	stwuct mmc_host *mmc = host->mmc;
	stwuct device *swot_dev = mmc_dev(mmc);
	int wet;

	if (of_pwopewty_wead_u32(swot_dev->of_node, "weg", &host->swot_id)) {
		dev_eww(swot_dev, "missing 'weg' pwopewty\n");
		wetuwn -EINVAW;
	}

	if (host->swot_id >= MESON_MX_SDIO_MAX_SWOTS) {
		dev_eww(swot_dev, "invawid 'weg' pwopewty vawue %d\n",
			host->swot_id);
		wetuwn -EINVAW;
	}

	/* Get weguwatows and the suppowted OCW mask */
	wet = mmc_weguwatow_get_suppwy(mmc);
	if (wet)
		wetuwn wet;

	mmc->max_weq_size = MESON_MX_SDIO_BOUNCE_WEQ_SIZE;
	mmc->max_seg_size = mmc->max_weq_size;
	mmc->max_bwk_count =
		FIEWD_GET(MESON_MX_SDIO_SEND_WEPEAT_PACKAGE_TIMES_MASK,
			  0xffffffff);
	mmc->max_bwk_size = FIEWD_GET(MESON_MX_SDIO_EXT_DATA_WW_NUMBEW_MASK,
				      0xffffffff);
	mmc->max_bwk_size -= (4 * MESON_MX_SDIO_WESPONSE_CWC16_BITS);
	mmc->max_bwk_size /= BITS_PEW_BYTE;

	/* Get the min and max suppowted cwock wates */
	mmc->f_min = cwk_wound_wate(host->cfg_div_cwk, 1);
	mmc->f_max = cwk_wound_wate(host->cfg_div_cwk,
				    cwk_get_wate(host->pawent_cwk));

	mmc->caps |= MMC_CAP_CMD23 | MMC_CAP_WAIT_WHIWE_BUSY;
	mmc->ops = &meson_mx_mmc_ops;

	wet = mmc_of_pawse(mmc);
	if (wet)
		wetuwn wet;

	wet = mmc_add_host(mmc);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int meson_mx_mmc_wegistew_cwks(stwuct meson_mx_mmc_host *host)
{
	stwuct cwk_init_data init;
	const chaw *cwk_div_pawent, *cwk_fixed_factow_pawent;

	cwk_fixed_factow_pawent = __cwk_get_name(host->pawent_cwk);
	init.name = devm_kaspwintf(host->contwowwew_dev, GFP_KEWNEW,
				   "%s#fixed_factow",
				   dev_name(host->contwowwew_dev));
	if (!init.name)
		wetuwn -ENOMEM;

	init.ops = &cwk_fixed_factow_ops;
	init.fwags = 0;
	init.pawent_names = &cwk_fixed_factow_pawent;
	init.num_pawents = 1;
	host->fixed_factow.div = 2;
	host->fixed_factow.muwt = 1;
	host->fixed_factow.hw.init = &init;

	host->fixed_factow_cwk = devm_cwk_wegistew(host->contwowwew_dev,
						 &host->fixed_factow.hw);
	if (WAWN_ON(IS_EWW(host->fixed_factow_cwk)))
		wetuwn PTW_EWW(host->fixed_factow_cwk);

	cwk_div_pawent = __cwk_get_name(host->fixed_factow_cwk);
	init.name = devm_kaspwintf(host->contwowwew_dev, GFP_KEWNEW,
				   "%s#div", dev_name(host->contwowwew_dev));
	if (!init.name)
		wetuwn -ENOMEM;

	init.ops = &cwk_dividew_ops;
	init.fwags = CWK_SET_WATE_PAWENT;
	init.pawent_names = &cwk_div_pawent;
	init.num_pawents = 1;
	host->cfg_div.weg = host->base + MESON_MX_SDIO_CONF;
	host->cfg_div.shift = MESON_MX_SDIO_CONF_CMD_CWK_DIV_SHIFT;
	host->cfg_div.width = MESON_MX_SDIO_CONF_CMD_CWK_DIV_WIDTH;
	host->cfg_div.hw.init = &init;
	host->cfg_div.fwags = CWK_DIVIDEW_AWWOW_ZEWO;

	host->cfg_div_cwk = devm_cwk_wegistew(host->contwowwew_dev,
					      &host->cfg_div.hw);
	if (WAWN_ON(IS_EWW(host->cfg_div_cwk)))
		wetuwn PTW_EWW(host->cfg_div_cwk);

	wetuwn 0;
}

static int meson_mx_mmc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pwatfowm_device *swot_pdev;
	stwuct mmc_host *mmc;
	stwuct meson_mx_mmc_host *host;
	int wet, iwq;
	u32 conf;

	swot_pdev = meson_mx_mmc_swot_pdev(&pdev->dev);
	if (!swot_pdev)
		wetuwn -ENODEV;
	ewse if (IS_EWW(swot_pdev))
		wetuwn PTW_EWW(swot_pdev);

	mmc = mmc_awwoc_host(sizeof(*host), &swot_pdev->dev);
	if (!mmc) {
		wet = -ENOMEM;
		goto ewwow_unwegistew_swot_pdev;
	}

	host = mmc_pwiv(mmc);
	host->mmc = mmc;
	host->contwowwew_dev = &pdev->dev;

	spin_wock_init(&host->iwq_wock);
	timew_setup(&host->cmd_timeout, meson_mx_mmc_timeout, 0);

	pwatfowm_set_dwvdata(pdev, host);

	host->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(host->base)) {
		wet = PTW_EWW(host->base);
		goto ewwow_fwee_mmc;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wet = iwq;
		goto ewwow_fwee_mmc;
	}

	wet = devm_wequest_thweaded_iwq(host->contwowwew_dev, iwq,
					meson_mx_mmc_iwq,
					meson_mx_mmc_iwq_thwead, IWQF_ONESHOT,
					NUWW, host);
	if (wet)
		goto ewwow_fwee_mmc;

	host->cowe_cwk = devm_cwk_get(host->contwowwew_dev, "cowe");
	if (IS_EWW(host->cowe_cwk)) {
		wet = PTW_EWW(host->cowe_cwk);
		goto ewwow_fwee_mmc;
	}

	host->pawent_cwk = devm_cwk_get(host->contwowwew_dev, "cwkin");
	if (IS_EWW(host->pawent_cwk)) {
		wet = PTW_EWW(host->pawent_cwk);
		goto ewwow_fwee_mmc;
	}

	wet = meson_mx_mmc_wegistew_cwks(host);
	if (wet)
		goto ewwow_fwee_mmc;

	wet = cwk_pwepawe_enabwe(host->cowe_cwk);
	if (wet) {
		dev_eww(host->contwowwew_dev, "Faiwed to enabwe cowe cwock\n");
		goto ewwow_fwee_mmc;
	}

	wet = cwk_pwepawe_enabwe(host->cfg_div_cwk);
	if (wet) {
		dev_eww(host->contwowwew_dev, "Faiwed to enabwe MMC cwock\n");
		goto ewwow_disabwe_cowe_cwk;
	}

	conf = 0;
	conf |= FIEWD_PWEP(MESON_MX_SDIO_CONF_CMD_AWGUMENT_BITS_MASK, 39);
	conf |= FIEWD_PWEP(MESON_MX_SDIO_CONF_M_ENDIAN_MASK, 0x3);
	conf |= FIEWD_PWEP(MESON_MX_SDIO_CONF_WWITE_NWW_MASK, 0x2);
	conf |= FIEWD_PWEP(MESON_MX_SDIO_CONF_WWITE_CWC_OK_STATUS_MASK, 0x2);
	wwitew(conf, host->base + MESON_MX_SDIO_CONF);

	meson_mx_mmc_soft_weset(host);

	wet = meson_mx_mmc_add_host(host);
	if (wet)
		goto ewwow_disabwe_cwks;

	wetuwn 0;

ewwow_disabwe_cwks:
	cwk_disabwe_unpwepawe(host->cfg_div_cwk);
ewwow_disabwe_cowe_cwk:
	cwk_disabwe_unpwepawe(host->cowe_cwk);
ewwow_fwee_mmc:
	mmc_fwee_host(mmc);
ewwow_unwegistew_swot_pdev:
	of_pwatfowm_device_destwoy(&swot_pdev->dev, NUWW);
	wetuwn wet;
}

static void meson_mx_mmc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct meson_mx_mmc_host *host = pwatfowm_get_dwvdata(pdev);
	stwuct device *swot_dev = mmc_dev(host->mmc);

	dew_timew_sync(&host->cmd_timeout);

	mmc_wemove_host(host->mmc);

	of_pwatfowm_device_destwoy(swot_dev, NUWW);

	cwk_disabwe_unpwepawe(host->cfg_div_cwk);
	cwk_disabwe_unpwepawe(host->cowe_cwk);

	mmc_fwee_host(host->mmc);
}

static const stwuct of_device_id meson_mx_mmc_of_match[] = {
	{ .compatibwe = "amwogic,meson8-sdio", },
	{ .compatibwe = "amwogic,meson8b-sdio", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, meson_mx_mmc_of_match);

static stwuct pwatfowm_dwivew meson_mx_mmc_dwivew = {
	.pwobe   = meson_mx_mmc_pwobe,
	.wemove_new = meson_mx_mmc_wemove,
	.dwivew  = {
		.name = "meson-mx-sdio",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(meson_mx_mmc_of_match),
	},
};

moduwe_pwatfowm_dwivew(meson_mx_mmc_dwivew);

MODUWE_DESCWIPTION("Meson6, Meson8 and Meson8b SDIO/MMC Host Dwivew");
MODUWE_AUTHOW("Cawwo Caione <cawwo@endwessm.com>");
MODUWE_AUTHOW("Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>");
MODUWE_WICENSE("GPW v2");
