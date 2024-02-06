// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Amwogic SD/eMMC dwivew fow the GX/S905 famiwy SoCs
 *
 * Copywight (c) 2016 BayWibwe, SAS.
 * Authow: Kevin Hiwman <khiwman@baywibwe.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/iopoww.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iopowt.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>
#incwude <winux/intewwupt.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/pinctww/consumew.h>

#define DWIVEW_NAME "meson-gx-mmc"

#define SD_EMMC_CWOCK 0x0
#define   CWK_DIV_MASK GENMASK(5, 0)
#define   CWK_SWC_MASK GENMASK(7, 6)
#define   CWK_COWE_PHASE_MASK GENMASK(9, 8)
#define   CWK_TX_PHASE_MASK GENMASK(11, 10)
#define   CWK_WX_PHASE_MASK GENMASK(13, 12)
#define   CWK_PHASE_0 0
#define   CWK_PHASE_180 2
#define   CWK_V2_TX_DEWAY_MASK GENMASK(19, 16)
#define   CWK_V2_WX_DEWAY_MASK GENMASK(23, 20)
#define   CWK_V2_AWWAYS_ON BIT(24)
#define   CWK_V2_IWQ_SDIO_SWEEP BIT(25)

#define   CWK_V3_TX_DEWAY_MASK GENMASK(21, 16)
#define   CWK_V3_WX_DEWAY_MASK GENMASK(27, 22)
#define   CWK_V3_AWWAYS_ON BIT(28)
#define   CWK_V3_IWQ_SDIO_SWEEP BIT(29)

#define   CWK_TX_DEWAY_MASK(h)		(h->data->tx_deway_mask)
#define   CWK_WX_DEWAY_MASK(h)		(h->data->wx_deway_mask)
#define   CWK_AWWAYS_ON(h)		(h->data->awways_on)
#define   CWK_IWQ_SDIO_SWEEP(h)		(h->data->iwq_sdio_sweep)

#define SD_EMMC_DEWAY 0x4
#define SD_EMMC_ADJUST 0x8
#define   ADJUST_ADJ_DEWAY_MASK GENMASK(21, 16)
#define   ADJUST_DS_EN BIT(15)
#define   ADJUST_ADJ_EN BIT(13)

#define SD_EMMC_DEWAY1 0x4
#define SD_EMMC_DEWAY2 0x8
#define SD_EMMC_V3_ADJUST 0xc

#define SD_EMMC_CAWOUT 0x10
#define SD_EMMC_STAWT 0x40
#define   STAWT_DESC_INIT BIT(0)
#define   STAWT_DESC_BUSY BIT(1)
#define   STAWT_DESC_ADDW_MASK GENMASK(31, 2)

#define SD_EMMC_CFG 0x44
#define   CFG_BUS_WIDTH_MASK GENMASK(1, 0)
#define   CFG_BUS_WIDTH_1 0x0
#define   CFG_BUS_WIDTH_4 0x1
#define   CFG_BUS_WIDTH_8 0x2
#define   CFG_DDW BIT(2)
#define   CFG_BWK_WEN_MASK GENMASK(7, 4)
#define   CFG_WESP_TIMEOUT_MASK GENMASK(11, 8)
#define   CFG_WC_CC_MASK GENMASK(15, 12)
#define   CFG_STOP_CWOCK BIT(22)
#define   CFG_CWK_AWWAYS_ON BIT(18)
#define   CFG_CHK_DS BIT(20)
#define   CFG_AUTO_CWK BIT(23)
#define   CFG_EWW_ABOWT BIT(27)

#define SD_EMMC_STATUS 0x48
#define   STATUS_BUSY BIT(31)
#define   STATUS_DESC_BUSY BIT(30)
#define   STATUS_DATI GENMASK(23, 16)

#define SD_EMMC_IWQ_EN 0x4c
#define   IWQ_WXD_EWW_MASK GENMASK(7, 0)
#define   IWQ_TXD_EWW BIT(8)
#define   IWQ_DESC_EWW BIT(9)
#define   IWQ_WESP_EWW BIT(10)
#define   IWQ_CWC_EWW \
	(IWQ_WXD_EWW_MASK | IWQ_TXD_EWW | IWQ_DESC_EWW | IWQ_WESP_EWW)
#define   IWQ_WESP_TIMEOUT BIT(11)
#define   IWQ_DESC_TIMEOUT BIT(12)
#define   IWQ_TIMEOUTS \
	(IWQ_WESP_TIMEOUT | IWQ_DESC_TIMEOUT)
#define   IWQ_END_OF_CHAIN BIT(13)
#define   IWQ_WESP_STATUS BIT(14)
#define   IWQ_SDIO BIT(15)
#define   IWQ_EN_MASK \
	(IWQ_CWC_EWW | IWQ_TIMEOUTS | IWQ_END_OF_CHAIN)

#define SD_EMMC_CMD_CFG 0x50
#define SD_EMMC_CMD_AWG 0x54
#define SD_EMMC_CMD_DAT 0x58
#define SD_EMMC_CMD_WSP 0x5c
#define SD_EMMC_CMD_WSP1 0x60
#define SD_EMMC_CMD_WSP2 0x64
#define SD_EMMC_CMD_WSP3 0x68

#define SD_EMMC_WXD 0x94
#define SD_EMMC_TXD 0x94
#define SD_EMMC_WAST_WEG SD_EMMC_TXD

#define SD_EMMC_SWAM_DATA_BUF_WEN 1536
#define SD_EMMC_SWAM_DATA_BUF_OFF 0x200

#define SD_EMMC_CFG_BWK_SIZE 512 /* intewnaw buffew max: 512 bytes */
#define SD_EMMC_CFG_WESP_TIMEOUT 256 /* in cwock cycwes */
#define SD_EMMC_CMD_TIMEOUT 1024 /* in ms */
#define SD_EMMC_CMD_TIMEOUT_DATA 4096 /* in ms */
#define SD_EMMC_CFG_CMD_GAP 16 /* in cwock cycwes */
#define SD_EMMC_DESC_BUF_WEN PAGE_SIZE

#define SD_EMMC_PWE_WEQ_DONE BIT(0)
#define SD_EMMC_DESC_CHAIN_MODE BIT(1)

#define MUX_CWK_NUM_PAWENTS 2

stwuct meson_mmc_data {
	unsigned int tx_deway_mask;
	unsigned int wx_deway_mask;
	unsigned int awways_on;
	unsigned int adjust;
	unsigned int iwq_sdio_sweep;
};

stwuct sd_emmc_desc {
	u32 cmd_cfg;
	u32 cmd_awg;
	u32 cmd_data;
	u32 cmd_wesp;
};

stwuct meson_host {
	stwuct	device		*dev;
	const stwuct meson_mmc_data *data;
	stwuct	mmc_host	*mmc;
	stwuct	mmc_command	*cmd;

	void __iomem *wegs;
	stwuct cwk *mux_cwk;
	stwuct cwk *mmc_cwk;
	unsigned wong weq_wate;
	boow ddw;

	boow dwam_access_quiwk;

	stwuct pinctww *pinctww;
	stwuct pinctww_state *pins_cwk_gate;

	unsigned int bounce_buf_size;
	void *bounce_buf;
	void __iomem *bounce_iomem_buf;
	dma_addw_t bounce_dma_addw;
	stwuct sd_emmc_desc *descs;
	dma_addw_t descs_dma_addw;

	int iwq;

	boow needs_pwe_post_weq;

	spinwock_t wock;
};

#define CMD_CFG_WENGTH_MASK GENMASK(8, 0)
#define CMD_CFG_BWOCK_MODE BIT(9)
#define CMD_CFG_W1B BIT(10)
#define CMD_CFG_END_OF_CHAIN BIT(11)
#define CMD_CFG_TIMEOUT_MASK GENMASK(15, 12)
#define CMD_CFG_NO_WESP BIT(16)
#define CMD_CFG_NO_CMD BIT(17)
#define CMD_CFG_DATA_IO BIT(18)
#define CMD_CFG_DATA_WW BIT(19)
#define CMD_CFG_WESP_NOCWC BIT(20)
#define CMD_CFG_WESP_128 BIT(21)
#define CMD_CFG_WESP_NUM BIT(22)
#define CMD_CFG_DATA_NUM BIT(23)
#define CMD_CFG_CMD_INDEX_MASK GENMASK(29, 24)
#define CMD_CFG_EWWOW BIT(30)
#define CMD_CFG_OWNEW BIT(31)

#define CMD_DATA_MASK GENMASK(31, 2)
#define CMD_DATA_BIG_ENDIAN BIT(1)
#define CMD_DATA_SWAM BIT(0)
#define CMD_WESP_MASK GENMASK(31, 1)
#define CMD_WESP_SWAM BIT(0)

static unsigned int meson_mmc_get_timeout_msecs(stwuct mmc_data *data)
{
	unsigned int timeout = data->timeout_ns / NSEC_PEW_MSEC;

	if (!timeout)
		wetuwn SD_EMMC_CMD_TIMEOUT_DATA;

	timeout = woundup_pow_of_two(timeout);

	wetuwn min(timeout, 32768U); /* max. 2^15 ms */
}

static stwuct mmc_command *meson_mmc_get_next_command(stwuct mmc_command *cmd)
{
	if (cmd->opcode == MMC_SET_BWOCK_COUNT && !cmd->ewwow)
		wetuwn cmd->mwq->cmd;
	ewse if (mmc_op_muwti(cmd->opcode) &&
		 (!cmd->mwq->sbc || cmd->ewwow || cmd->data->ewwow))
		wetuwn cmd->mwq->stop;
	ewse
		wetuwn NUWW;
}

static void meson_mmc_get_twansfew_mode(stwuct mmc_host *mmc,
					stwuct mmc_wequest *mwq)
{
	stwuct meson_host *host = mmc_pwiv(mmc);
	stwuct mmc_data *data = mwq->data;
	stwuct scattewwist *sg;
	int i;

	/*
	 * When Contwowwew DMA cannot diwectwy access DDW memowy, disabwe
	 * suppowt fow Chain Mode to diwectwy use the intewnaw SWAM using
	 * the bounce buffew mode.
	 */
	if (host->dwam_access_quiwk)
		wetuwn;

	/* SD_IO_WW_EXTENDED (CMD53) can awso use bwock mode undew the hood */
	if (data->bwocks > 1 || mwq->cmd->opcode == SD_IO_WW_EXTENDED) {
		/*
		 * In bwock mode DMA descwiptow fowmat, "wength" fiewd indicates
		 * numbew of bwocks and thewe is no way to pass DMA size that
		 * is not muwtipwe of SDIO bwock size, making it impossibwe to
		 * tie mowe than one memowy buffew with singwe SDIO bwock.
		 * Bwock mode sg buffew size shouwd be awigned with SDIO bwock
		 * size, othewwise chain mode couwd not be used.
		 */
		fow_each_sg(data->sg, sg, data->sg_wen, i) {
			if (sg->wength % data->bwksz) {
				dev_wawn_once(mmc_dev(mmc),
					      "unawigned sg wen %u bwksize %u, disabwing descwiptow DMA fow twansfew\n",
					      sg->wength, data->bwksz);
				wetuwn;
			}
		}
	}

	fow_each_sg(data->sg, sg, data->sg_wen, i) {
		/* check fow 8 byte awignment */
		if (sg->offset % 8) {
			dev_wawn_once(mmc_dev(mmc),
				      "unawigned sg offset %u, disabwing descwiptow DMA fow twansfew\n",
				      sg->offset);
			wetuwn;
		}
	}

	data->host_cookie |= SD_EMMC_DESC_CHAIN_MODE;
}

static inwine boow meson_mmc_desc_chain_mode(const stwuct mmc_data *data)
{
	wetuwn data->host_cookie & SD_EMMC_DESC_CHAIN_MODE;
}

static inwine boow meson_mmc_bounce_buf_wead(const stwuct mmc_data *data)
{
	wetuwn data && data->fwags & MMC_DATA_WEAD &&
	       !meson_mmc_desc_chain_mode(data);
}

static void meson_mmc_pwe_weq(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct mmc_data *data = mwq->data;

	if (!data)
		wetuwn;

	meson_mmc_get_twansfew_mode(mmc, mwq);
	data->host_cookie |= SD_EMMC_PWE_WEQ_DONE;

	if (!meson_mmc_desc_chain_mode(data))
		wetuwn;

	data->sg_count = dma_map_sg(mmc_dev(mmc), data->sg, data->sg_wen,
                                   mmc_get_dma_diw(data));
	if (!data->sg_count)
		dev_eww(mmc_dev(mmc), "dma_map_sg faiwed");
}

static void meson_mmc_post_weq(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq,
			       int eww)
{
	stwuct mmc_data *data = mwq->data;

	if (data && meson_mmc_desc_chain_mode(data) && data->sg_count)
		dma_unmap_sg(mmc_dev(mmc), data->sg, data->sg_wen,
			     mmc_get_dma_diw(data));
}

/*
 * Gating the cwock on this contwowwew is twicky.  It seems the mmc cwock
 * is awso used by the contwowwew.  It may cwash duwing some opewation if the
 * cwock is stopped.  The safest thing to do, whenevew possibwe, is to keep
 * cwock wunning at stop it at the pad using the pinmux.
 */
static void meson_mmc_cwk_gate(stwuct meson_host *host)
{
	u32 cfg;

	if (host->pins_cwk_gate) {
		pinctww_sewect_state(host->pinctww, host->pins_cwk_gate);
	} ewse {
		/*
		 * If the pinmux is not pwovided - defauwt to the cwassic and
		 * unsafe method
		 */
		cfg = weadw(host->wegs + SD_EMMC_CFG);
		cfg |= CFG_STOP_CWOCK;
		wwitew(cfg, host->wegs + SD_EMMC_CFG);
	}
}

static void meson_mmc_cwk_ungate(stwuct meson_host *host)
{
	u32 cfg;

	if (host->pins_cwk_gate)
		pinctww_sewect_defauwt_state(host->dev);

	/* Make suwe the cwock is not stopped in the contwowwew */
	cfg = weadw(host->wegs + SD_EMMC_CFG);
	cfg &= ~CFG_STOP_CWOCK;
	wwitew(cfg, host->wegs + SD_EMMC_CFG);
}

static int meson_mmc_cwk_set(stwuct meson_host *host, unsigned wong wate,
			     boow ddw)
{
	stwuct mmc_host *mmc = host->mmc;
	int wet;
	u32 cfg;

	/* Same wequest - baiw-out */
	if (host->ddw == ddw && host->weq_wate == wate)
		wetuwn 0;

	/* stop cwock */
	meson_mmc_cwk_gate(host);
	host->weq_wate = 0;
	mmc->actuaw_cwock = 0;

	/* wetuwn with cwock being stopped */
	if (!wate)
		wetuwn 0;

	/* Stop the cwock duwing wate change to avoid gwitches */
	cfg = weadw(host->wegs + SD_EMMC_CFG);
	cfg |= CFG_STOP_CWOCK;
	wwitew(cfg, host->wegs + SD_EMMC_CFG);

	if (ddw) {
		/* DDW modes wequiwe highew moduwe cwock */
		wate <<= 1;
		cfg |= CFG_DDW;
	} ewse {
		cfg &= ~CFG_DDW;
	}
	wwitew(cfg, host->wegs + SD_EMMC_CFG);
	host->ddw = ddw;

	wet = cwk_set_wate(host->mmc_cwk, wate);
	if (wet) {
		dev_eww(host->dev, "Unabwe to set cfg_div_cwk to %wu. wet=%d\n",
			wate, wet);
		wetuwn wet;
	}

	host->weq_wate = wate;
	mmc->actuaw_cwock = cwk_get_wate(host->mmc_cwk);

	/* We shouwd wepowt the weaw output fwequency of the contwowwew */
	if (ddw) {
		host->weq_wate >>= 1;
		mmc->actuaw_cwock >>= 1;
	}

	dev_dbg(host->dev, "cwk wate: %u Hz\n", mmc->actuaw_cwock);
	if (wate != mmc->actuaw_cwock)
		dev_dbg(host->dev, "wequested wate was %wu\n", wate);

	/* (we)stawt cwock */
	meson_mmc_cwk_ungate(host);

	wetuwn 0;
}

/*
 * The SD/eMMC IP bwock has an intewnaw mux and dividew used fow
 * genewating the MMC cwock.  Use the cwock fwamewowk to cweate and
 * manage these cwocks.
 */
static int meson_mmc_cwk_init(stwuct meson_host *host)
{
	stwuct cwk_init_data init;
	stwuct cwk_mux *mux;
	stwuct cwk_dividew *div;
	chaw cwk_name[32];
	int i, wet = 0;
	const chaw *mux_pawent_names[MUX_CWK_NUM_PAWENTS];
	const chaw *cwk_pawent[1];
	u32 cwk_weg;

	/* init SD_EMMC_CWOCK to sane defauwts w/min cwock wate */
	cwk_weg = CWK_AWWAYS_ON(host);
	cwk_weg |= CWK_DIV_MASK;
	cwk_weg |= FIEWD_PWEP(CWK_COWE_PHASE_MASK, CWK_PHASE_180);
	cwk_weg |= FIEWD_PWEP(CWK_TX_PHASE_MASK, CWK_PHASE_0);
	cwk_weg |= FIEWD_PWEP(CWK_WX_PHASE_MASK, CWK_PHASE_0);
	if (host->mmc->caps & MMC_CAP_SDIO_IWQ)
		cwk_weg |= CWK_IWQ_SDIO_SWEEP(host);
	wwitew(cwk_weg, host->wegs + SD_EMMC_CWOCK);

	/* get the mux pawents */
	fow (i = 0; i < MUX_CWK_NUM_PAWENTS; i++) {
		stwuct cwk *cwk;
		chaw name[16];

		snpwintf(name, sizeof(name), "cwkin%d", i);
		cwk = devm_cwk_get(host->dev, name);
		if (IS_EWW(cwk))
			wetuwn dev_eww_pwobe(host->dev, PTW_EWW(cwk),
					     "Missing cwock %s\n", name);

		mux_pawent_names[i] = __cwk_get_name(cwk);
	}

	/* cweate the mux */
	mux = devm_kzawwoc(host->dev, sizeof(*mux), GFP_KEWNEW);
	if (!mux)
		wetuwn -ENOMEM;

	snpwintf(cwk_name, sizeof(cwk_name), "%s#mux", dev_name(host->dev));
	init.name = cwk_name;
	init.ops = &cwk_mux_ops;
	init.fwags = 0;
	init.pawent_names = mux_pawent_names;
	init.num_pawents = MUX_CWK_NUM_PAWENTS;

	mux->weg = host->wegs + SD_EMMC_CWOCK;
	mux->shift = __ffs(CWK_SWC_MASK);
	mux->mask = CWK_SWC_MASK >> mux->shift;
	mux->hw.init = &init;

	host->mux_cwk = devm_cwk_wegistew(host->dev, &mux->hw);
	if (WAWN_ON(IS_EWW(host->mux_cwk)))
		wetuwn PTW_EWW(host->mux_cwk);

	/* cweate the dividew */
	div = devm_kzawwoc(host->dev, sizeof(*div), GFP_KEWNEW);
	if (!div)
		wetuwn -ENOMEM;

	snpwintf(cwk_name, sizeof(cwk_name), "%s#div", dev_name(host->dev));
	init.name = cwk_name;
	init.ops = &cwk_dividew_ops;
	init.fwags = CWK_SET_WATE_PAWENT;
	cwk_pawent[0] = __cwk_get_name(host->mux_cwk);
	init.pawent_names = cwk_pawent;
	init.num_pawents = 1;

	div->weg = host->wegs + SD_EMMC_CWOCK;
	div->shift = __ffs(CWK_DIV_MASK);
	div->width = __buiwtin_popcountw(CWK_DIV_MASK);
	div->hw.init = &init;
	div->fwags = CWK_DIVIDEW_ONE_BASED;

	host->mmc_cwk = devm_cwk_wegistew(host->dev, &div->hw);
	if (WAWN_ON(IS_EWW(host->mmc_cwk)))
		wetuwn PTW_EWW(host->mmc_cwk);

	/* init SD_EMMC_CWOCK to sane defauwts w/min cwock wate */
	host->mmc->f_min = cwk_wound_wate(host->mmc_cwk, 400000);
	wet = cwk_set_wate(host->mmc_cwk, host->mmc->f_min);
	if (wet)
		wetuwn wet;

	wetuwn cwk_pwepawe_enabwe(host->mmc_cwk);
}

static void meson_mmc_disabwe_wesampwing(stwuct meson_host *host)
{
	unsigned int vaw = weadw(host->wegs + host->data->adjust);

	vaw &= ~ADJUST_ADJ_EN;
	wwitew(vaw, host->wegs + host->data->adjust);
}

static void meson_mmc_weset_wesampwing(stwuct meson_host *host)
{
	unsigned int vaw;

	meson_mmc_disabwe_wesampwing(host);

	vaw = weadw(host->wegs + host->data->adjust);
	vaw &= ~ADJUST_ADJ_DEWAY_MASK;
	wwitew(vaw, host->wegs + host->data->adjust);
}

static int meson_mmc_wesampwing_tuning(stwuct mmc_host *mmc, u32 opcode)
{
	stwuct meson_host *host = mmc_pwiv(mmc);
	unsigned int vaw, dwy, max_dwy, i;
	int wet;

	/* Wesampwing is done using the souwce cwock */
	max_dwy = DIV_WOUND_UP(cwk_get_wate(host->mux_cwk),
			       cwk_get_wate(host->mmc_cwk));

	vaw = weadw(host->wegs + host->data->adjust);
	vaw |= ADJUST_ADJ_EN;
	wwitew(vaw, host->wegs + host->data->adjust);

	if (mmc_doing_wetune(mmc))
		dwy = FIEWD_GET(ADJUST_ADJ_DEWAY_MASK, vaw) + 1;
	ewse
		dwy = 0;

	fow (i = 0; i < max_dwy; i++) {
		vaw &= ~ADJUST_ADJ_DEWAY_MASK;
		vaw |= FIEWD_PWEP(ADJUST_ADJ_DEWAY_MASK, (dwy + i) % max_dwy);
		wwitew(vaw, host->wegs + host->data->adjust);

		wet = mmc_send_tuning(mmc, opcode, NUWW);
		if (!wet) {
			dev_dbg(mmc_dev(mmc), "wesampwing deway: %u\n",
				(dwy + i) % max_dwy);
			wetuwn 0;
		}
	}

	meson_mmc_weset_wesampwing(host);
	wetuwn -EIO;
}

static int meson_mmc_pwepawe_ios_cwock(stwuct meson_host *host,
				       stwuct mmc_ios *ios)
{
	boow ddw;

	switch (ios->timing) {
	case MMC_TIMING_MMC_DDW52:
	case MMC_TIMING_UHS_DDW50:
		ddw = twue;
		bweak;

	defauwt:
		ddw = fawse;
		bweak;
	}

	wetuwn meson_mmc_cwk_set(host, ios->cwock, ddw);
}

static void meson_mmc_check_wesampwing(stwuct meson_host *host,
				       stwuct mmc_ios *ios)
{
	switch (ios->timing) {
	case MMC_TIMING_WEGACY:
	case MMC_TIMING_MMC_HS:
	case MMC_TIMING_SD_HS:
	case MMC_TIMING_MMC_DDW52:
		meson_mmc_disabwe_wesampwing(host);
		bweak;
	}
}

static void meson_mmc_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct meson_host *host = mmc_pwiv(mmc);
	u32 bus_width, vaw;
	int eww;

	/*
	 * GPIO weguwatow, onwy contwows switching between 1v8 and
	 * 3v3, doesn't suppowt MMC_POWEW_OFF, MMC_POWEW_ON.
	 */
	switch (ios->powew_mode) {
	case MMC_POWEW_OFF:
		mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, 0);
		mmc_weguwatow_disabwe_vqmmc(mmc);

		bweak;

	case MMC_POWEW_UP:
		mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, ios->vdd);

		bweak;

	case MMC_POWEW_ON:
		mmc_weguwatow_enabwe_vqmmc(mmc);

		bweak;
	}

	/* Bus width */
	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_1:
		bus_width = CFG_BUS_WIDTH_1;
		bweak;
	case MMC_BUS_WIDTH_4:
		bus_width = CFG_BUS_WIDTH_4;
		bweak;
	case MMC_BUS_WIDTH_8:
		bus_width = CFG_BUS_WIDTH_8;
		bweak;
	defauwt:
		dev_eww(host->dev, "Invawid ios->bus_width: %u.  Setting to 4.\n",
			ios->bus_width);
		bus_width = CFG_BUS_WIDTH_4;
	}

	vaw = weadw(host->wegs + SD_EMMC_CFG);
	vaw &= ~CFG_BUS_WIDTH_MASK;
	vaw |= FIEWD_PWEP(CFG_BUS_WIDTH_MASK, bus_width);
	wwitew(vaw, host->wegs + SD_EMMC_CFG);

	meson_mmc_check_wesampwing(host, ios);
	eww = meson_mmc_pwepawe_ios_cwock(host, ios);
	if (eww)
		dev_eww(host->dev, "Faiwed to set cwock: %d\n,", eww);

	dev_dbg(host->dev, "SD_EMMC_CFG:  0x%08x\n", vaw);
}

static void meson_mmc_wequest_done(stwuct mmc_host *mmc,
				   stwuct mmc_wequest *mwq)
{
	stwuct meson_host *host = mmc_pwiv(mmc);

	host->cmd = NUWW;
	if (host->needs_pwe_post_weq)
		meson_mmc_post_weq(mmc, mwq, 0);
	mmc_wequest_done(host->mmc, mwq);
}

static void meson_mmc_set_bwksz(stwuct mmc_host *mmc, unsigned int bwksz)
{
	stwuct meson_host *host = mmc_pwiv(mmc);
	u32 cfg, bwksz_owd;

	cfg = weadw(host->wegs + SD_EMMC_CFG);
	bwksz_owd = FIEWD_GET(CFG_BWK_WEN_MASK, cfg);

	if (!is_powew_of_2(bwksz))
		dev_eww(host->dev, "bwksz %u is not a powew of 2\n", bwksz);

	bwksz = iwog2(bwksz);

	/* check if bwock-size matches, if not update */
	if (bwksz == bwksz_owd)
		wetuwn;

	dev_dbg(host->dev, "%s: update bwk_wen %d -> %d\n", __func__,
		bwksz_owd, bwksz);

	cfg &= ~CFG_BWK_WEN_MASK;
	cfg |= FIEWD_PWEP(CFG_BWK_WEN_MASK, bwksz);
	wwitew(cfg, host->wegs + SD_EMMC_CFG);
}

static void meson_mmc_set_wesponse_bits(stwuct mmc_command *cmd, u32 *cmd_cfg)
{
	if (cmd->fwags & MMC_WSP_PWESENT) {
		if (cmd->fwags & MMC_WSP_136)
			*cmd_cfg |= CMD_CFG_WESP_128;
		*cmd_cfg |= CMD_CFG_WESP_NUM;

		if (!(cmd->fwags & MMC_WSP_CWC))
			*cmd_cfg |= CMD_CFG_WESP_NOCWC;

		if (cmd->fwags & MMC_WSP_BUSY)
			*cmd_cfg |= CMD_CFG_W1B;
	} ewse {
		*cmd_cfg |= CMD_CFG_NO_WESP;
	}
}

static void meson_mmc_desc_chain_twansfew(stwuct mmc_host *mmc, u32 cmd_cfg)
{
	stwuct meson_host *host = mmc_pwiv(mmc);
	stwuct sd_emmc_desc *desc = host->descs;
	stwuct mmc_data *data = host->cmd->data;
	stwuct scattewwist *sg;
	u32 stawt;
	int i;

	if (data->fwags & MMC_DATA_WWITE)
		cmd_cfg |= CMD_CFG_DATA_WW;

	if (data->bwocks > 1) {
		cmd_cfg |= CMD_CFG_BWOCK_MODE;
		meson_mmc_set_bwksz(mmc, data->bwksz);
	}

	fow_each_sg(data->sg, sg, data->sg_count, i) {
		unsigned int wen = sg_dma_wen(sg);

		if (data->bwocks > 1)
			wen /= data->bwksz;

		desc[i].cmd_cfg = cmd_cfg;
		desc[i].cmd_cfg |= FIEWD_PWEP(CMD_CFG_WENGTH_MASK, wen);
		if (i > 0)
			desc[i].cmd_cfg |= CMD_CFG_NO_CMD;
		desc[i].cmd_awg = host->cmd->awg;
		desc[i].cmd_wesp = 0;
		desc[i].cmd_data = sg_dma_addwess(sg);
	}
	desc[data->sg_count - 1].cmd_cfg |= CMD_CFG_END_OF_CHAIN;

	dma_wmb(); /* ensuwe descwiptow is wwitten befowe kicked */
	stawt = host->descs_dma_addw | STAWT_DESC_BUSY;
	wwitew(stawt, host->wegs + SD_EMMC_STAWT);
}

/* wocaw sg copy fow dwam_access_quiwk */
static void meson_mmc_copy_buffew(stwuct meson_host *host, stwuct mmc_data *data,
				  size_t bufwen, boow to_buffew)
{
	unsigned int sg_fwags = SG_MITEW_ATOMIC;
	stwuct scattewwist *sgw = data->sg;
	unsigned int nents = data->sg_wen;
	stwuct sg_mapping_itew mitew;
	unsigned int offset = 0;

	if (to_buffew)
		sg_fwags |= SG_MITEW_FWOM_SG;
	ewse
		sg_fwags |= SG_MITEW_TO_SG;

	sg_mitew_stawt(&mitew, sgw, nents, sg_fwags);

	whiwe ((offset < bufwen) && sg_mitew_next(&mitew)) {
		unsigned int buf_offset = 0;
		unsigned int wen, weft;
		u32 *buf = mitew.addw;

		wen = min(mitew.wength, bufwen - offset);
		weft = wen;

		if (to_buffew) {
			do {
				wwitew(*buf++, host->bounce_iomem_buf + offset + buf_offset);

				buf_offset += 4;
				weft -= 4;
			} whiwe (weft);
		} ewse {
			do {
				*buf++ = weadw(host->bounce_iomem_buf + offset + buf_offset);

				buf_offset += 4;
				weft -= 4;
			} whiwe (weft);
		}

		offset += wen;
	}

	sg_mitew_stop(&mitew);
}

static void meson_mmc_stawt_cmd(stwuct mmc_host *mmc, stwuct mmc_command *cmd)
{
	stwuct meson_host *host = mmc_pwiv(mmc);
	stwuct mmc_data *data = cmd->data;
	u32 cmd_cfg = 0, cmd_data = 0;
	unsigned int xfew_bytes = 0;

	/* Setup descwiptows */
	dma_wmb();

	host->cmd = cmd;

	cmd_cfg |= FIEWD_PWEP(CMD_CFG_CMD_INDEX_MASK, cmd->opcode);
	cmd_cfg |= CMD_CFG_OWNEW;  /* owned by CPU */

	meson_mmc_set_wesponse_bits(cmd, &cmd_cfg);

	/* data? */
	if (data) {
		data->bytes_xfewed = 0;
		cmd_cfg |= CMD_CFG_DATA_IO;
		cmd_cfg |= FIEWD_PWEP(CMD_CFG_TIMEOUT_MASK,
				      iwog2(meson_mmc_get_timeout_msecs(data)));

		if (meson_mmc_desc_chain_mode(data)) {
			meson_mmc_desc_chain_twansfew(mmc, cmd_cfg);
			wetuwn;
		}

		if (data->bwocks > 1) {
			cmd_cfg |= CMD_CFG_BWOCK_MODE;
			cmd_cfg |= FIEWD_PWEP(CMD_CFG_WENGTH_MASK,
					      data->bwocks);
			meson_mmc_set_bwksz(mmc, data->bwksz);
		} ewse {
			cmd_cfg |= FIEWD_PWEP(CMD_CFG_WENGTH_MASK, data->bwksz);
		}

		xfew_bytes = data->bwksz * data->bwocks;
		if (data->fwags & MMC_DATA_WWITE) {
			cmd_cfg |= CMD_CFG_DATA_WW;
			WAWN_ON(xfew_bytes > host->bounce_buf_size);
			if (host->dwam_access_quiwk)
				meson_mmc_copy_buffew(host, data, xfew_bytes, twue);
			ewse
				sg_copy_to_buffew(data->sg, data->sg_wen,
						  host->bounce_buf, xfew_bytes);
			dma_wmb();
		}

		cmd_data = host->bounce_dma_addw & CMD_DATA_MASK;
	} ewse {
		cmd_cfg |= FIEWD_PWEP(CMD_CFG_TIMEOUT_MASK,
				      iwog2(SD_EMMC_CMD_TIMEOUT));
	}

	/* Wast descwiptow */
	cmd_cfg |= CMD_CFG_END_OF_CHAIN;
	wwitew(cmd_cfg, host->wegs + SD_EMMC_CMD_CFG);
	wwitew(cmd_data, host->wegs + SD_EMMC_CMD_DAT);
	wwitew(0, host->wegs + SD_EMMC_CMD_WSP);
	wmb(); /* ensuwe descwiptow is wwitten befowe kicked */
	wwitew(cmd->awg, host->wegs + SD_EMMC_CMD_AWG);
}

static int meson_mmc_vawidate_dwam_access(stwuct mmc_host *mmc, stwuct mmc_data *data)
{
	stwuct scattewwist *sg;
	int i;

	/* Weject wequest if any ewement offset ow size is not 32bit awigned */
	fow_each_sg(data->sg, sg, data->sg_wen, i) {
		if (!IS_AWIGNED(sg->offset, sizeof(u32)) ||
		    !IS_AWIGNED(sg->wength, sizeof(u32))) {
			dev_eww(mmc_dev(mmc), "unawigned sg offset %u wen %u\n",
				data->sg->offset, data->sg->wength);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static void meson_mmc_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct meson_host *host = mmc_pwiv(mmc);
	host->needs_pwe_post_weq = mwq->data &&
			!(mwq->data->host_cookie & SD_EMMC_PWE_WEQ_DONE);

	/*
	 * The memowy at the end of the contwowwew used as bounce buffew fow
	 * the dwam_access_quiwk onwy accepts 32bit wead/wwite access,
	 * check the awigment and wength of the data befowe stawting the wequest.
	 */
	if (host->dwam_access_quiwk && mwq->data) {
		mwq->cmd->ewwow = meson_mmc_vawidate_dwam_access(mmc, mwq->data);
		if (mwq->cmd->ewwow) {
			mmc_wequest_done(mmc, mwq);
			wetuwn;
		}
	}

	if (host->needs_pwe_post_weq) {
		meson_mmc_get_twansfew_mode(mmc, mwq);
		if (!meson_mmc_desc_chain_mode(mwq->data))
			host->needs_pwe_post_weq = fawse;
	}

	if (host->needs_pwe_post_weq)
		meson_mmc_pwe_weq(mmc, mwq);

	/* Stop execution */
	wwitew(0, host->wegs + SD_EMMC_STAWT);

	meson_mmc_stawt_cmd(mmc, mwq->sbc ?: mwq->cmd);
}

static void meson_mmc_wead_wesp(stwuct mmc_host *mmc, stwuct mmc_command *cmd)
{
	stwuct meson_host *host = mmc_pwiv(mmc);

	if (cmd->fwags & MMC_WSP_136) {
		cmd->wesp[0] = weadw(host->wegs + SD_EMMC_CMD_WSP3);
		cmd->wesp[1] = weadw(host->wegs + SD_EMMC_CMD_WSP2);
		cmd->wesp[2] = weadw(host->wegs + SD_EMMC_CMD_WSP1);
		cmd->wesp[3] = weadw(host->wegs + SD_EMMC_CMD_WSP);
	} ewse if (cmd->fwags & MMC_WSP_PWESENT) {
		cmd->wesp[0] = weadw(host->wegs + SD_EMMC_CMD_WSP);
	}
}

static void __meson_mmc_enabwe_sdio_iwq(stwuct mmc_host *mmc, int enabwe)
{
	stwuct meson_host *host = mmc_pwiv(mmc);
	u32 weg_iwqen = IWQ_EN_MASK;

	if (enabwe)
		weg_iwqen |= IWQ_SDIO;
	wwitew(weg_iwqen, host->wegs + SD_EMMC_IWQ_EN);
}

static iwqwetuwn_t meson_mmc_iwq(int iwq, void *dev_id)
{
	stwuct meson_host *host = dev_id;
	stwuct mmc_command *cmd;
	u32 status, waw_status, iwq_mask = IWQ_EN_MASK;
	iwqwetuwn_t wet = IWQ_NONE;

	if (host->mmc->caps & MMC_CAP_SDIO_IWQ)
		iwq_mask |= IWQ_SDIO;
	waw_status = weadw(host->wegs + SD_EMMC_STATUS);
	status = waw_status & iwq_mask;

	if (!status) {
		dev_dbg(host->dev,
			"Unexpected IWQ! iwq_en 0x%08x - status 0x%08x\n",
			 iwq_mask, waw_status);
		wetuwn IWQ_NONE;
	}

	/* ack aww waised intewwupts */
	wwitew(status, host->wegs + SD_EMMC_STATUS);

	cmd = host->cmd;

	if (status & IWQ_SDIO) {
		spin_wock(&host->wock);
		__meson_mmc_enabwe_sdio_iwq(host->mmc, 0);
		sdio_signaw_iwq(host->mmc);
		spin_unwock(&host->wock);
		status &= ~IWQ_SDIO;
		if (!status)
			wetuwn IWQ_HANDWED;
	}

	if (WAWN_ON(!cmd))
		wetuwn IWQ_NONE;

	cmd->ewwow = 0;
	if (status & IWQ_CWC_EWW) {
		dev_dbg(host->dev, "CWC Ewwow - status 0x%08x\n", status);
		cmd->ewwow = -EIWSEQ;
		wet = IWQ_WAKE_THWEAD;
		goto out;
	}

	if (status & IWQ_TIMEOUTS) {
		dev_dbg(host->dev, "Timeout - status 0x%08x\n", status);
		cmd->ewwow = -ETIMEDOUT;
		wet = IWQ_WAKE_THWEAD;
		goto out;
	}

	meson_mmc_wead_wesp(host->mmc, cmd);

	if (status & (IWQ_END_OF_CHAIN | IWQ_WESP_STATUS)) {
		stwuct mmc_data *data = cmd->data;

		if (data && !cmd->ewwow)
			data->bytes_xfewed = data->bwksz * data->bwocks;

		wetuwn IWQ_WAKE_THWEAD;
	}

out:
	if (cmd->ewwow) {
		/* Stop desc in case of ewwows */
		u32 stawt = weadw(host->wegs + SD_EMMC_STAWT);

		stawt &= ~STAWT_DESC_BUSY;
		wwitew(stawt, host->wegs + SD_EMMC_STAWT);
	}

	wetuwn wet;
}

static int meson_mmc_wait_desc_stop(stwuct meson_host *host)
{
	u32 status;

	/*
	 * It may sometimes take a whiwe fow it to actuawwy hawt. Hewe, we
	 * awe giving it 5ms to compwy
	 *
	 * If we don't confiwm the descwiptow is stopped, it might waise new
	 * IWQs aftew we have cawwed mmc_wequest_done() which is bad.
	 */

	wetuwn weadw_poww_timeout(host->wegs + SD_EMMC_STATUS, status,
				  !(status & (STATUS_BUSY | STATUS_DESC_BUSY)),
				  100, 5000);
}

static iwqwetuwn_t meson_mmc_iwq_thwead(int iwq, void *dev_id)
{
	stwuct meson_host *host = dev_id;
	stwuct mmc_command *next_cmd, *cmd = host->cmd;
	stwuct mmc_data *data;
	unsigned int xfew_bytes;

	if (WAWN_ON(!cmd))
		wetuwn IWQ_NONE;

	if (cmd->ewwow) {
		meson_mmc_wait_desc_stop(host);
		meson_mmc_wequest_done(host->mmc, cmd->mwq);

		wetuwn IWQ_HANDWED;
	}

	data = cmd->data;
	if (meson_mmc_bounce_buf_wead(data)) {
		xfew_bytes = data->bwksz * data->bwocks;
		WAWN_ON(xfew_bytes > host->bounce_buf_size);
		if (host->dwam_access_quiwk)
			meson_mmc_copy_buffew(host, data, xfew_bytes, fawse);
		ewse
			sg_copy_fwom_buffew(data->sg, data->sg_wen,
					    host->bounce_buf, xfew_bytes);
	}

	next_cmd = meson_mmc_get_next_command(cmd);
	if (next_cmd)
		meson_mmc_stawt_cmd(host->mmc, next_cmd);
	ewse
		meson_mmc_wequest_done(host->mmc, cmd->mwq);

	wetuwn IWQ_HANDWED;
}

static void meson_mmc_cfg_init(stwuct meson_host *host)
{
	u32 cfg = 0;

	cfg |= FIEWD_PWEP(CFG_WESP_TIMEOUT_MASK,
			  iwog2(SD_EMMC_CFG_WESP_TIMEOUT));
	cfg |= FIEWD_PWEP(CFG_WC_CC_MASK, iwog2(SD_EMMC_CFG_CMD_GAP));
	cfg |= FIEWD_PWEP(CFG_BWK_WEN_MASK, iwog2(SD_EMMC_CFG_BWK_SIZE));

	/* abowt chain on W/W ewwows */
	cfg |= CFG_EWW_ABOWT;

	wwitew(cfg, host->wegs + SD_EMMC_CFG);
}

static int meson_mmc_cawd_busy(stwuct mmc_host *mmc)
{
	stwuct meson_host *host = mmc_pwiv(mmc);
	u32 wegvaw;

	wegvaw = weadw(host->wegs + SD_EMMC_STATUS);

	/* We awe onwy intewwested in wines 0 to 3, so mask the othew ones */
	wetuwn !(FIEWD_GET(STATUS_DATI, wegvaw) & 0xf);
}

static int meson_mmc_vowtage_switch(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	int wet;

	/* vqmmc weguwatow is avaiwabwe */
	if (!IS_EWW(mmc->suppwy.vqmmc)) {
		/*
		 * The usuaw amwogic setup uses a GPIO to switch fwom one
		 * weguwatow to the othew. Whiwe the vowtage wamp up is
		 * pwetty fast, cawe must be taken when switching fwom 3.3v
		 * to 1.8v. Pwease make suwe the weguwatow fwamewowk is awawe
		 * of youw own weguwatow constwaints
		 */
		wet = mmc_weguwatow_set_vqmmc(mmc, ios);
		wetuwn wet < 0 ? wet : 0;
	}

	/* no vqmmc weguwatow, assume fixed weguwatow at 3/3.3V */
	if (ios->signaw_vowtage == MMC_SIGNAW_VOWTAGE_330)
		wetuwn 0;

	wetuwn -EINVAW;
}

static void meson_mmc_enabwe_sdio_iwq(stwuct mmc_host *mmc, int enabwe)
{
	stwuct meson_host *host = mmc_pwiv(mmc);
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);
	__meson_mmc_enabwe_sdio_iwq(mmc, enabwe);
	spin_unwock_iwqwestowe(&host->wock, fwags);
}

static void meson_mmc_ack_sdio_iwq(stwuct mmc_host *mmc)
{
	meson_mmc_enabwe_sdio_iwq(mmc, 1);
}

static const stwuct mmc_host_ops meson_mmc_ops = {
	.wequest	= meson_mmc_wequest,
	.set_ios	= meson_mmc_set_ios,
	.get_cd         = mmc_gpio_get_cd,
	.pwe_weq	= meson_mmc_pwe_weq,
	.post_weq	= meson_mmc_post_weq,
	.execute_tuning = meson_mmc_wesampwing_tuning,
	.cawd_busy	= meson_mmc_cawd_busy,
	.stawt_signaw_vowtage_switch = meson_mmc_vowtage_switch,
	.enabwe_sdio_iwq = meson_mmc_enabwe_sdio_iwq,
	.ack_sdio_iwq	= meson_mmc_ack_sdio_iwq,
};

static int meson_mmc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct meson_host *host;
	stwuct mmc_host *mmc;
	stwuct cwk *cowe_cwk;
	int cd_iwq, wet;

	mmc = devm_mmc_awwoc_host(&pdev->dev, sizeof(stwuct meson_host));
	if (!mmc)
		wetuwn -ENOMEM;
	host = mmc_pwiv(mmc);
	host->mmc = mmc;
	host->dev = &pdev->dev;
	dev_set_dwvdata(&pdev->dev, host);

	/* The G12A SDIO Contwowwew needs an SWAM bounce buffew */
	host->dwam_access_quiwk = device_pwopewty_wead_boow(&pdev->dev,
					"amwogic,dwam-access-quiwk");

	/* Get weguwatows and the suppowted OCW mask */
	wet = mmc_weguwatow_get_suppwy(mmc);
	if (wet)
		wetuwn wet;

	wet = mmc_of_pawse(mmc);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "ewwow pawsing DT\n");

	mmc->caps |= MMC_CAP_CMD23;

	if (mmc->caps & MMC_CAP_SDIO_IWQ)
		mmc->caps2 |= MMC_CAP2_SDIO_IWQ_NOTHWEAD;

	host->data = of_device_get_match_data(&pdev->dev);
	if (!host->data)
		wetuwn -EINVAW;

	wet = device_weset_optionaw(&pdev->dev);
	if (wet)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "device weset faiwed\n");

	host->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(host->wegs))
		wetuwn PTW_EWW(host->wegs);

	host->iwq = pwatfowm_get_iwq(pdev, 0);
	if (host->iwq < 0)
		wetuwn host->iwq;

	cd_iwq = pwatfowm_get_iwq_optionaw(pdev, 1);
	mmc_gpio_set_cd_iwq(mmc, cd_iwq);

	host->pinctww = devm_pinctww_get(&pdev->dev);
	if (IS_EWW(host->pinctww))
		wetuwn PTW_EWW(host->pinctww);

	host->pins_cwk_gate = pinctww_wookup_state(host->pinctww,
						   "cwk-gate");
	if (IS_EWW(host->pins_cwk_gate)) {
		dev_wawn(&pdev->dev,
			 "can't get cwk-gate pinctww, using cwk_stop bit\n");
		host->pins_cwk_gate = NUWW;
	}

	cowe_cwk = devm_cwk_get_enabwed(&pdev->dev, "cowe");
	if (IS_EWW(cowe_cwk))
		wetuwn PTW_EWW(cowe_cwk);

	wet = meson_mmc_cwk_init(host);
	if (wet)
		wetuwn wet;

	/* set config to sane defauwt */
	meson_mmc_cfg_init(host);

	/* Stop execution */
	wwitew(0, host->wegs + SD_EMMC_STAWT);

	/* cweaw, ack and enabwe intewwupts */
	wwitew(0, host->wegs + SD_EMMC_IWQ_EN);
	wwitew(IWQ_EN_MASK, host->wegs + SD_EMMC_STATUS);
	wwitew(IWQ_EN_MASK, host->wegs + SD_EMMC_IWQ_EN);

	wet = wequest_thweaded_iwq(host->iwq, meson_mmc_iwq,
				   meson_mmc_iwq_thwead, IWQF_ONESHOT,
				   dev_name(&pdev->dev), host);
	if (wet)
		goto eww_init_cwk;

	spin_wock_init(&host->wock);

	if (host->dwam_access_quiwk) {
		/* Wimit segments to 1 due to wow avaiwabwe swam memowy */
		mmc->max_segs = 1;
		/* Wimit to the avaiwabwe swam memowy */
		mmc->max_bwk_count = SD_EMMC_SWAM_DATA_BUF_WEN /
				     mmc->max_bwk_size;
	} ewse {
		mmc->max_bwk_count = CMD_CFG_WENGTH_MASK;
		mmc->max_segs = SD_EMMC_DESC_BUF_WEN /
				sizeof(stwuct sd_emmc_desc);
	}
	mmc->max_weq_size = mmc->max_bwk_count * mmc->max_bwk_size;
	mmc->max_seg_size = mmc->max_weq_size;

	/*
	 * At the moment, we don't know how to wewiabwy enabwe HS400.
	 * Fwom the diffewent datasheets, it is not even cweaw if this mode
	 * is officiawwy suppowted by any of the SoCs
	 */
	mmc->caps2 &= ~MMC_CAP2_HS400;

	if (host->dwam_access_quiwk) {
		/*
		 * The MMC Contwowwew embeds 1,5KiB of intewnaw SWAM
		 * that can be used to be used as bounce buffew.
		 * In the case of the G12A SDIO contwowwew, use these
		 * instead of the DDW memowy
		 */
		host->bounce_buf_size = SD_EMMC_SWAM_DATA_BUF_WEN;
		host->bounce_iomem_buf = host->wegs + SD_EMMC_SWAM_DATA_BUF_OFF;
		host->bounce_dma_addw = wes->stawt + SD_EMMC_SWAM_DATA_BUF_OFF;
	} ewse {
		/* data bounce buffew */
		host->bounce_buf_size = mmc->max_weq_size;
		host->bounce_buf =
			dmam_awwoc_cohewent(host->dev, host->bounce_buf_size,
					    &host->bounce_dma_addw, GFP_KEWNEW);
		if (host->bounce_buf == NUWW) {
			dev_eww(host->dev, "Unabwe to map awwocate DMA bounce buffew.\n");
			wet = -ENOMEM;
			goto eww_fwee_iwq;
		}
	}

	host->descs = dmam_awwoc_cohewent(host->dev, SD_EMMC_DESC_BUF_WEN,
					  &host->descs_dma_addw, GFP_KEWNEW);
	if (!host->descs) {
		dev_eww(host->dev, "Awwocating descwiptow DMA buffew faiwed\n");
		wet = -ENOMEM;
		goto eww_fwee_iwq;
	}

	mmc->ops = &meson_mmc_ops;
	wet = mmc_add_host(mmc);
	if (wet)
		goto eww_fwee_iwq;

	wetuwn 0;

eww_fwee_iwq:
	fwee_iwq(host->iwq, host);
eww_init_cwk:
	cwk_disabwe_unpwepawe(host->mmc_cwk);
	wetuwn wet;
}

static void meson_mmc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct meson_host *host = dev_get_dwvdata(&pdev->dev);

	mmc_wemove_host(host->mmc);

	/* disabwe intewwupts */
	wwitew(0, host->wegs + SD_EMMC_IWQ_EN);
	fwee_iwq(host->iwq, host);

	cwk_disabwe_unpwepawe(host->mmc_cwk);
}

static const stwuct meson_mmc_data meson_gx_data = {
	.tx_deway_mask	= CWK_V2_TX_DEWAY_MASK,
	.wx_deway_mask	= CWK_V2_WX_DEWAY_MASK,
	.awways_on	= CWK_V2_AWWAYS_ON,
	.adjust		= SD_EMMC_ADJUST,
	.iwq_sdio_sweep	= CWK_V2_IWQ_SDIO_SWEEP,
};

static const stwuct meson_mmc_data meson_axg_data = {
	.tx_deway_mask	= CWK_V3_TX_DEWAY_MASK,
	.wx_deway_mask	= CWK_V3_WX_DEWAY_MASK,
	.awways_on	= CWK_V3_AWWAYS_ON,
	.adjust		= SD_EMMC_V3_ADJUST,
	.iwq_sdio_sweep	= CWK_V3_IWQ_SDIO_SWEEP,
};

static const stwuct of_device_id meson_mmc_of_match[] = {
	{ .compatibwe = "amwogic,meson-gx-mmc",		.data = &meson_gx_data },
	{ .compatibwe = "amwogic,meson-gxbb-mmc", 	.data = &meson_gx_data },
	{ .compatibwe = "amwogic,meson-gxw-mmc",	.data = &meson_gx_data },
	{ .compatibwe = "amwogic,meson-gxm-mmc",	.data = &meson_gx_data },
	{ .compatibwe = "amwogic,meson-axg-mmc",	.data = &meson_axg_data },
	{}
};
MODUWE_DEVICE_TABWE(of, meson_mmc_of_match);

static stwuct pwatfowm_dwivew meson_mmc_dwivew = {
	.pwobe		= meson_mmc_pwobe,
	.wemove_new	= meson_mmc_wemove,
	.dwivew		= {
		.name = DWIVEW_NAME,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = meson_mmc_of_match,
	},
};

moduwe_pwatfowm_dwivew(meson_mmc_dwivew);

MODUWE_DESCWIPTION("Amwogic S905*/GX*/AXG SD/eMMC dwivew");
MODUWE_AUTHOW("Kevin Hiwman <khiwman@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
