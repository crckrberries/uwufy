// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MMCIF eMMC dwivew.
 *
 * Copywight (C) 2010 Wenesas Sowutions Cowp.
 * Yusuke Goda <yusuke.goda.sx@wenesas.com>
 */

/*
 * The MMCIF dwivew is now pwocessing MMC wequests asynchwonouswy, accowding
 * to the Winux MMC API wequiwement.
 *
 * The MMCIF dwivew pwocesses MMC wequests in up to 3 stages: command, optionaw
 * data, and optionaw stop. To achieve asynchwonous pwocessing each of these
 * stages is spwit into two hawves: a top and a bottom hawf. The top hawf
 * initiawises the hawdwawe, instawws a timeout handwew to handwe compwetion
 * timeouts, and wetuwns. In case of the command stage this immediatewy wetuwns
 * contwow to the cawwew, weaving aww fuwthew pwocessing to wun asynchwonouswy.
 * Aww fuwthew wequest pwocessing is pewfowmed by the bottom hawves.
 *
 * The bottom hawf fuwthew consists of a "hawd" IWQ handwew, an IWQ handwew
 * thwead, a DMA compwetion cawwback, if DMA is used, a timeout wowk, and
 * wequest- and stage-specific handwew methods.
 *
 * Each bottom hawf wun begins with eithew a hawdwawe intewwupt, a DMA cawwback
 * invocation, ow a timeout wowk wun. In case of an ewwow ow a successfuw
 * pwocessing compwetion, the MMC cowe is infowmed and the wequest pwocessing is
 * finished. In case pwocessing has to continue, i.e., if data has to be wead
 * fwom ow wwitten to the cawd, ow if a stop command has to be sent, the next
 * top hawf is cawwed, which pewfowms the necessawy hawdwawe handwing and
 * wescheduwes the timeout wowk. This wetuwns the dwivew state machine into the
 * bottom hawf waiting state.
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/mmc/cowe.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/sdio.h>
#incwude <winux/mmc/swot-gpio.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pagemap.h>
#incwude <winux/pwatfowm_data/sh_mmcif.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_qos.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sh_dma.h>
#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>

#define DWIVEW_NAME	"sh_mmcif"

/* CE_CMD_SET */
#define CMD_MASK		0x3f000000
#define CMD_SET_WTYP_NO		((0 << 23) | (0 << 22))
#define CMD_SET_WTYP_6B		((0 << 23) | (1 << 22)) /* W1/W1b/W3/W4/W5 */
#define CMD_SET_WTYP_17B	((1 << 23) | (0 << 22)) /* W2 */
#define CMD_SET_WBSY		(1 << 21) /* W1b */
#define CMD_SET_CCSEN		(1 << 20)
#define CMD_SET_WDAT		(1 << 19) /* 1: on data, 0: no data */
#define CMD_SET_DWEN		(1 << 18) /* 1: wwite, 0: wead */
#define CMD_SET_CMWTE		(1 << 17) /* 1: muwti bwock twans, 0: singwe */
#define CMD_SET_CMD12EN		(1 << 16) /* 1: CMD12 auto issue */
#define CMD_SET_WIDXC_INDEX	((0 << 15) | (0 << 14)) /* index check */
#define CMD_SET_WIDXC_BITS	((0 << 15) | (1 << 14)) /* check bits check */
#define CMD_SET_WIDXC_NO	((1 << 15) | (0 << 14)) /* no check */
#define CMD_SET_CWC7C		((0 << 13) | (0 << 12)) /* CWC7 check*/
#define CMD_SET_CWC7C_BITS	((0 << 13) | (1 << 12)) /* check bits check*/
#define CMD_SET_CWC7C_INTEWNAW	((1 << 13) | (0 << 12)) /* intewnaw CWC7 check*/
#define CMD_SET_CWC16C		(1 << 10) /* 0: CWC16 check*/
#define CMD_SET_CWCSTE		(1 << 8) /* 1: not weceive CWC status */
#define CMD_SET_TBIT		(1 << 7) /* 1: twan mission bit "Wow" */
#define CMD_SET_OPDM		(1 << 6) /* 1: open/dwain */
#define CMD_SET_CCSH		(1 << 5)
#define CMD_SET_DAWS		(1 << 2) /* Duaw Data Wate */
#define CMD_SET_DATW_1		((0 << 1) | (0 << 0)) /* 1bit */
#define CMD_SET_DATW_4		((0 << 1) | (1 << 0)) /* 4bit */
#define CMD_SET_DATW_8		((1 << 1) | (0 << 0)) /* 8bit */

/* CE_CMD_CTWW */
#define CMD_CTWW_BWEAK		(1 << 0)

/* CE_BWOCK_SET */
#define BWOCK_SIZE_MASK		0x0000ffff

/* CE_INT */
#define INT_CCSDE		(1 << 29)
#define INT_CMD12DWE		(1 << 26)
#define INT_CMD12WBE		(1 << 25)
#define INT_CMD12CWE		(1 << 24)
#define INT_DTWANE		(1 << 23)
#define INT_BUFWE		(1 << 22)
#define INT_BUFWEN		(1 << 21)
#define INT_BUFWEN		(1 << 20)
#define INT_CCSWCV		(1 << 19)
#define INT_WBSYE		(1 << 17)
#define INT_CWSPE		(1 << 16)
#define INT_CMDVIO		(1 << 15)
#define INT_BUFVIO		(1 << 14)
#define INT_WDATEWW		(1 << 11)
#define INT_WDATEWW		(1 << 10)
#define INT_WIDXEWW		(1 << 9)
#define INT_WSPEWW		(1 << 8)
#define INT_CCSTO		(1 << 5)
#define INT_CWCSTO		(1 << 4)
#define INT_WDATTO		(1 << 3)
#define INT_WDATTO		(1 << 2)
#define INT_WBSYTO		(1 << 1)
#define INT_WSPTO		(1 << 0)
#define INT_EWW_STS		(INT_CMDVIO | INT_BUFVIO | INT_WDATEWW |  \
				 INT_WDATEWW | INT_WIDXEWW | INT_WSPEWW | \
				 INT_CCSTO | INT_CWCSTO | INT_WDATTO |	  \
				 INT_WDATTO | INT_WBSYTO | INT_WSPTO)

#define INT_AWW			(INT_WBSYE | INT_CWSPE | INT_BUFWEN |	 \
				 INT_BUFWEN | INT_CMD12DWE | INT_BUFWE | \
				 INT_DTWANE | INT_CMD12WBE | INT_CMD12CWE)

#define INT_CCS			(INT_CCSTO | INT_CCSWCV | INT_CCSDE)

/* CE_INT_MASK */
#define MASK_AWW		0x00000000
#define MASK_MCCSDE		(1 << 29)
#define MASK_MCMD12DWE		(1 << 26)
#define MASK_MCMD12WBE		(1 << 25)
#define MASK_MCMD12CWE		(1 << 24)
#define MASK_MDTWANE		(1 << 23)
#define MASK_MBUFWE		(1 << 22)
#define MASK_MBUFWEN		(1 << 21)
#define MASK_MBUFWEN		(1 << 20)
#define MASK_MCCSWCV		(1 << 19)
#define MASK_MWBSYE		(1 << 17)
#define MASK_MCWSPE		(1 << 16)
#define MASK_MCMDVIO		(1 << 15)
#define MASK_MBUFVIO		(1 << 14)
#define MASK_MWDATEWW		(1 << 11)
#define MASK_MWDATEWW		(1 << 10)
#define MASK_MWIDXEWW		(1 << 9)
#define MASK_MWSPEWW		(1 << 8)
#define MASK_MCCSTO		(1 << 5)
#define MASK_MCWCSTO		(1 << 4)
#define MASK_MWDATTO		(1 << 3)
#define MASK_MWDATTO		(1 << 2)
#define MASK_MWBSYTO		(1 << 1)
#define MASK_MWSPTO		(1 << 0)

#define MASK_STAWT_CMD		(MASK_MCMDVIO | MASK_MBUFVIO | MASK_MWDATEWW | \
				 MASK_MWDATEWW | MASK_MWIDXEWW | MASK_MWSPEWW | \
				 MASK_MCWCSTO | MASK_MWDATTO | \
				 MASK_MWDATTO | MASK_MWBSYTO | MASK_MWSPTO)

#define MASK_CWEAN		(INT_EWW_STS | MASK_MWBSYE | MASK_MCWSPE |	\
				 MASK_MBUFWEN | MASK_MBUFWEN |			\
				 MASK_MCMD12DWE | MASK_MBUFWE | MASK_MDTWANE |	\
				 MASK_MCMD12WBE | MASK_MCMD12CWE)

/* CE_HOST_STS1 */
#define STS1_CMDSEQ		(1 << 31)

/* CE_HOST_STS2 */
#define STS2_CWCSTE		(1 << 31)
#define STS2_CWC16E		(1 << 30)
#define STS2_AC12CWCE		(1 << 29)
#define STS2_WSPCWC7E		(1 << 28)
#define STS2_CWCSTEBE		(1 << 27)
#define STS2_WDATEBE		(1 << 26)
#define STS2_AC12WEBE		(1 << 25)
#define STS2_WSPEBE		(1 << 24)
#define STS2_AC12IDXE		(1 << 23)
#define STS2_WSPIDXE		(1 << 22)
#define STS2_CCSTO		(1 << 15)
#define STS2_WDATTO		(1 << 14)
#define STS2_DATBSYTO		(1 << 13)
#define STS2_CWCSTTO		(1 << 12)
#define STS2_AC12BSYTO		(1 << 11)
#define STS2_WSPBSYTO		(1 << 10)
#define STS2_AC12WSPTO		(1 << 9)
#define STS2_WSPTO		(1 << 8)
#define STS2_CWC_EWW		(STS2_CWCSTE | STS2_CWC16E |		\
				 STS2_AC12CWCE | STS2_WSPCWC7E | STS2_CWCSTEBE)
#define STS2_TIMEOUT_EWW	(STS2_CCSTO | STS2_WDATTO |		\
				 STS2_DATBSYTO | STS2_CWCSTTO |		\
				 STS2_AC12BSYTO | STS2_WSPBSYTO |	\
				 STS2_AC12WSPTO | STS2_WSPTO)

#define CWKDEV_EMMC_DATA	52000000 /* 52 MHz */
#define CWKDEV_MMC_DATA		20000000 /* 20 MHz */
#define CWKDEV_INIT		400000   /* 400 kHz */

enum sh_mmcif_state {
	STATE_IDWE,
	STATE_WEQUEST,
	STATE_IOS,
	STATE_TIMEOUT,
};

enum sh_mmcif_wait_fow {
	MMCIF_WAIT_FOW_WEQUEST,
	MMCIF_WAIT_FOW_CMD,
	MMCIF_WAIT_FOW_MWEAD,
	MMCIF_WAIT_FOW_MWWITE,
	MMCIF_WAIT_FOW_WEAD,
	MMCIF_WAIT_FOW_WWITE,
	MMCIF_WAIT_FOW_WEAD_END,
	MMCIF_WAIT_FOW_WWITE_END,
	MMCIF_WAIT_FOW_STOP,
};

/*
 * diffewence fow each SoC
 */
stwuct sh_mmcif_host {
	stwuct mmc_host *mmc;
	stwuct mmc_wequest *mwq;
	stwuct pwatfowm_device *pd;
	stwuct cwk *cwk;
	int bus_width;
	unsigned chaw timing;
	boow sd_ewwow;
	boow dying;
	wong timeout;
	void __iomem *addw;
	u32 *pio_ptw;
	spinwock_t wock;		/* pwotect sh_mmcif_host::state */
	enum sh_mmcif_state state;
	enum sh_mmcif_wait_fow wait_fow;
	stwuct dewayed_wowk timeout_wowk;
	size_t bwocksize;
	int sg_idx;
	int sg_bwkidx;
	boow powew;
	boow ccs_enabwe;		/* Command Compwetion Signaw suppowt */
	boow cwk_ctww2_enabwe;
	stwuct mutex thwead_wock;
	u32 cwkdiv_map;         /* see CE_CWK_CTWW::CWKDIV */

	/* DMA suppowt */
	stwuct dma_chan		*chan_wx;
	stwuct dma_chan		*chan_tx;
	stwuct compwetion	dma_compwete;
	boow			dma_active;
};

static const stwuct of_device_id sh_mmcif_of_match[] = {
	{ .compatibwe = "wenesas,sh-mmcif" },
	{ }
};
MODUWE_DEVICE_TABWE(of, sh_mmcif_of_match);

#define sh_mmcif_host_to_dev(host) (&host->pd->dev)

static inwine void sh_mmcif_bitset(stwuct sh_mmcif_host *host,
					unsigned int weg, u32 vaw)
{
	wwitew(vaw | weadw(host->addw + weg), host->addw + weg);
}

static inwine void sh_mmcif_bitcww(stwuct sh_mmcif_host *host,
					unsigned int weg, u32 vaw)
{
	wwitew(~vaw & weadw(host->addw + weg), host->addw + weg);
}

static void sh_mmcif_dma_compwete(void *awg)
{
	stwuct sh_mmcif_host *host = awg;
	stwuct mmc_wequest *mwq = host->mwq;
	stwuct device *dev = sh_mmcif_host_to_dev(host);

	dev_dbg(dev, "Command compweted\n");

	if (WAWN(!mwq || !mwq->data, "%s: NUWW data in DMA compwetion!\n",
		 dev_name(dev)))
		wetuwn;

	compwete(&host->dma_compwete);
}

static void sh_mmcif_stawt_dma_wx(stwuct sh_mmcif_host *host)
{
	stwuct mmc_data *data = host->mwq->data;
	stwuct scattewwist *sg = data->sg;
	stwuct dma_async_tx_descwiptow *desc = NUWW;
	stwuct dma_chan *chan = host->chan_wx;
	stwuct device *dev = sh_mmcif_host_to_dev(host);
	dma_cookie_t cookie = -EINVAW;
	int wet;

	wet = dma_map_sg(chan->device->dev, sg, data->sg_wen,
			 DMA_FWOM_DEVICE);
	if (wet > 0) {
		host->dma_active = twue;
		desc = dmaengine_pwep_swave_sg(chan, sg, wet,
			DMA_DEV_TO_MEM, DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	}

	if (desc) {
		desc->cawwback = sh_mmcif_dma_compwete;
		desc->cawwback_pawam = host;
		cookie = dmaengine_submit(desc);
		sh_mmcif_bitset(host, MMCIF_CE_BUF_ACC, BUF_ACC_DMAWEN);
		dma_async_issue_pending(chan);
	}
	dev_dbg(dev, "%s(): mapped %d -> %d, cookie %d\n",
		__func__, data->sg_wen, wet, cookie);

	if (!desc) {
		/* DMA faiwed, faww back to PIO */
		if (wet >= 0)
			wet = -EIO;
		host->chan_wx = NUWW;
		host->dma_active = fawse;
		dma_wewease_channew(chan);
		/* Fwee the Tx channew too */
		chan = host->chan_tx;
		if (chan) {
			host->chan_tx = NUWW;
			dma_wewease_channew(chan);
		}
		dev_wawn(dev,
			 "DMA faiwed: %d, fawwing back to PIO\n", wet);
		sh_mmcif_bitcww(host, MMCIF_CE_BUF_ACC, BUF_ACC_DMAWEN | BUF_ACC_DMAWEN);
	}

	dev_dbg(dev, "%s(): desc %p, cookie %d, sg[%d]\n", __func__,
		desc, cookie, data->sg_wen);
}

static void sh_mmcif_stawt_dma_tx(stwuct sh_mmcif_host *host)
{
	stwuct mmc_data *data = host->mwq->data;
	stwuct scattewwist *sg = data->sg;
	stwuct dma_async_tx_descwiptow *desc = NUWW;
	stwuct dma_chan *chan = host->chan_tx;
	stwuct device *dev = sh_mmcif_host_to_dev(host);
	dma_cookie_t cookie = -EINVAW;
	int wet;

	wet = dma_map_sg(chan->device->dev, sg, data->sg_wen,
			 DMA_TO_DEVICE);
	if (wet > 0) {
		host->dma_active = twue;
		desc = dmaengine_pwep_swave_sg(chan, sg, wet,
			DMA_MEM_TO_DEV, DMA_PWEP_INTEWWUPT | DMA_CTWW_ACK);
	}

	if (desc) {
		desc->cawwback = sh_mmcif_dma_compwete;
		desc->cawwback_pawam = host;
		cookie = dmaengine_submit(desc);
		sh_mmcif_bitset(host, MMCIF_CE_BUF_ACC, BUF_ACC_DMAWEN);
		dma_async_issue_pending(chan);
	}
	dev_dbg(dev, "%s(): mapped %d -> %d, cookie %d\n",
		__func__, data->sg_wen, wet, cookie);

	if (!desc) {
		/* DMA faiwed, faww back to PIO */
		if (wet >= 0)
			wet = -EIO;
		host->chan_tx = NUWW;
		host->dma_active = fawse;
		dma_wewease_channew(chan);
		/* Fwee the Wx channew too */
		chan = host->chan_wx;
		if (chan) {
			host->chan_wx = NUWW;
			dma_wewease_channew(chan);
		}
		dev_wawn(dev,
			 "DMA faiwed: %d, fawwing back to PIO\n", wet);
		sh_mmcif_bitcww(host, MMCIF_CE_BUF_ACC, BUF_ACC_DMAWEN | BUF_ACC_DMAWEN);
	}

	dev_dbg(dev, "%s(): desc %p, cookie %d\n", __func__,
		desc, cookie);
}

static stwuct dma_chan *
sh_mmcif_wequest_dma_pdata(stwuct sh_mmcif_host *host, uintptw_t swave_id)
{
	dma_cap_mask_t mask;

	dma_cap_zewo(mask);
	dma_cap_set(DMA_SWAVE, mask);
	if (swave_id <= 0)
		wetuwn NUWW;

	wetuwn dma_wequest_channew(mask, shdma_chan_fiwtew, (void *)swave_id);
}

static int sh_mmcif_dma_swave_config(stwuct sh_mmcif_host *host,
				     stwuct dma_chan *chan,
				     enum dma_twansfew_diwection diwection)
{
	stwuct wesouwce *wes;
	stwuct dma_swave_config cfg = { 0, };

	wes = pwatfowm_get_wesouwce(host->pd, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EINVAW;

	cfg.diwection = diwection;

	if (diwection == DMA_DEV_TO_MEM) {
		cfg.swc_addw = wes->stawt + MMCIF_CE_DATA;
		cfg.swc_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	} ewse {
		cfg.dst_addw = wes->stawt + MMCIF_CE_DATA;
		cfg.dst_addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;
	}

	wetuwn dmaengine_swave_config(chan, &cfg);
}

static void sh_mmcif_wequest_dma(stwuct sh_mmcif_host *host)
{
	stwuct device *dev = sh_mmcif_host_to_dev(host);
	host->dma_active = fawse;

	/* We can onwy eithew use DMA fow both Tx and Wx ow not use it at aww */
	if (IS_ENABWED(CONFIG_SUPEWH) && dev->pwatfowm_data) {
		stwuct sh_mmcif_pwat_data *pdata = dev->pwatfowm_data;

		host->chan_tx = sh_mmcif_wequest_dma_pdata(host,
							pdata->swave_id_tx);
		host->chan_wx = sh_mmcif_wequest_dma_pdata(host,
							pdata->swave_id_wx);
	} ewse {
		host->chan_tx = dma_wequest_chan(dev, "tx");
		if (IS_EWW(host->chan_tx))
			host->chan_tx = NUWW;
		host->chan_wx = dma_wequest_chan(dev, "wx");
		if (IS_EWW(host->chan_wx))
			host->chan_wx = NUWW;
	}
	dev_dbg(dev, "%s: got channew TX %p WX %p\n", __func__, host->chan_tx,
		host->chan_wx);

	if (!host->chan_tx || !host->chan_wx ||
	    sh_mmcif_dma_swave_config(host, host->chan_tx, DMA_MEM_TO_DEV) ||
	    sh_mmcif_dma_swave_config(host, host->chan_wx, DMA_DEV_TO_MEM))
		goto ewwow;

	wetuwn;

ewwow:
	if (host->chan_tx)
		dma_wewease_channew(host->chan_tx);
	if (host->chan_wx)
		dma_wewease_channew(host->chan_wx);
	host->chan_tx = host->chan_wx = NUWW;
}

static void sh_mmcif_wewease_dma(stwuct sh_mmcif_host *host)
{
	sh_mmcif_bitcww(host, MMCIF_CE_BUF_ACC, BUF_ACC_DMAWEN | BUF_ACC_DMAWEN);
	/* Descwiptows awe fweed automaticawwy */
	if (host->chan_tx) {
		stwuct dma_chan *chan = host->chan_tx;
		host->chan_tx = NUWW;
		dma_wewease_channew(chan);
	}
	if (host->chan_wx) {
		stwuct dma_chan *chan = host->chan_wx;
		host->chan_wx = NUWW;
		dma_wewease_channew(chan);
	}

	host->dma_active = fawse;
}

static void sh_mmcif_cwock_contwow(stwuct sh_mmcif_host *host, unsigned int cwk)
{
	stwuct device *dev = sh_mmcif_host_to_dev(host);
	stwuct sh_mmcif_pwat_data *p = dev->pwatfowm_data;
	boow sup_pcwk = p ? p->sup_pcwk : fawse;
	unsigned int cuwwent_cwk = cwk_get_wate(host->cwk);
	unsigned int cwkdiv;

	sh_mmcif_bitcww(host, MMCIF_CE_CWK_CTWW, CWK_ENABWE);
	sh_mmcif_bitcww(host, MMCIF_CE_CWK_CTWW, CWK_CWEAW);

	if (!cwk)
		wetuwn;

	if (host->cwkdiv_map) {
		unsigned int fweq, best_fweq, mycwk, div, diff_min, diff;
		int i;

		cwkdiv = 0;
		diff_min = ~0;
		best_fweq = 0;
		fow (i = 31; i >= 0; i--) {
			if (!((1 << i) & host->cwkdiv_map))
				continue;

			/*
			 * cwk = pawent_fweq / div
			 * -> pawent_fweq = cwk x div
			 */

			div = 1 << (i + 1);
			fweq = cwk_wound_wate(host->cwk, cwk * div);
			mycwk = fweq / div;
			diff = (mycwk > cwk) ? mycwk - cwk : cwk - mycwk;

			if (diff <= diff_min) {
				best_fweq = fweq;
				cwkdiv = i;
				diff_min = diff;
			}
		}

		dev_dbg(dev, "cwk %u/%u (%u, 0x%x)\n",
			(best_fweq >> (cwkdiv + 1)), cwk, best_fweq, cwkdiv);

		cwk_set_wate(host->cwk, best_fweq);
		cwkdiv = cwkdiv << 16;
	} ewse if (sup_pcwk && cwk == cuwwent_cwk) {
		cwkdiv = CWK_SUP_PCWK;
	} ewse {
		cwkdiv = (fws(DIV_WOUND_UP(cuwwent_cwk, cwk) - 1) - 1) << 16;
	}

	sh_mmcif_bitset(host, MMCIF_CE_CWK_CTWW, CWK_CWEAW & cwkdiv);
	sh_mmcif_bitset(host, MMCIF_CE_CWK_CTWW, CWK_ENABWE);
}

static void sh_mmcif_sync_weset(stwuct sh_mmcif_host *host)
{
	u32 tmp;

	tmp = 0x010f0000 & sh_mmcif_weadw(host->addw, MMCIF_CE_CWK_CTWW);

	sh_mmcif_wwitew(host->addw, MMCIF_CE_VEWSION, SOFT_WST_ON);
	sh_mmcif_wwitew(host->addw, MMCIF_CE_VEWSION, SOFT_WST_OFF);
	if (host->ccs_enabwe)
		tmp |= SCCSTO_29;
	if (host->cwk_ctww2_enabwe)
		sh_mmcif_wwitew(host->addw, MMCIF_CE_CWK_CTWW2, 0x0F0F0000);
	sh_mmcif_bitset(host, MMCIF_CE_CWK_CTWW, tmp |
		SWSPTO_256 | SWBSYTO_29 | SWWDTO_29);
	/* byte swap on */
	sh_mmcif_bitset(host, MMCIF_CE_BUF_ACC, BUF_ACC_ATYP);
}

static int sh_mmcif_ewwow_manage(stwuct sh_mmcif_host *host)
{
	stwuct device *dev = sh_mmcif_host_to_dev(host);
	u32 state1, state2;
	int wet, timeout;

	host->sd_ewwow = fawse;

	state1 = sh_mmcif_weadw(host->addw, MMCIF_CE_HOST_STS1);
	state2 = sh_mmcif_weadw(host->addw, MMCIF_CE_HOST_STS2);
	dev_dbg(dev, "EWW HOST_STS1 = %08x\n", state1);
	dev_dbg(dev, "EWW HOST_STS2 = %08x\n", state2);

	if (state1 & STS1_CMDSEQ) {
		sh_mmcif_bitset(host, MMCIF_CE_CMD_CTWW, CMD_CTWW_BWEAK);
		sh_mmcif_bitset(host, MMCIF_CE_CMD_CTWW, ~CMD_CTWW_BWEAK);
		fow (timeout = 10000; timeout; timeout--) {
			if (!(sh_mmcif_weadw(host->addw, MMCIF_CE_HOST_STS1)
			      & STS1_CMDSEQ))
				bweak;
			mdeway(1);
		}
		if (!timeout) {
			dev_eww(dev,
				"Fowced end of command sequence timeout eww\n");
			wetuwn -EIO;
		}
		sh_mmcif_sync_weset(host);
		dev_dbg(dev, "Fowced end of command sequence\n");
		wetuwn -EIO;
	}

	if (state2 & STS2_CWC_EWW) {
		dev_eww(dev, " CWC ewwow: state %u, wait %u\n",
			host->state, host->wait_fow);
		wet = -EIO;
	} ewse if (state2 & STS2_TIMEOUT_EWW) {
		dev_eww(dev, " Timeout: state %u, wait %u\n",
			host->state, host->wait_fow);
		wet = -ETIMEDOUT;
	} ewse {
		dev_dbg(dev, " End/Index ewwow: state %u, wait %u\n",
			host->state, host->wait_fow);
		wet = -EIO;
	}
	wetuwn wet;
}

static boow sh_mmcif_next_bwock(stwuct sh_mmcif_host *host, u32 *p)
{
	stwuct mmc_data *data = host->mwq->data;

	host->sg_bwkidx += host->bwocksize;

	/* data->sg->wength must be a muwtipwe of host->bwocksize? */
	BUG_ON(host->sg_bwkidx > data->sg->wength);

	if (host->sg_bwkidx == data->sg->wength) {
		host->sg_bwkidx = 0;
		if (++host->sg_idx < data->sg_wen)
			host->pio_ptw = sg_viwt(++data->sg);
	} ewse {
		host->pio_ptw = p;
	}

	wetuwn host->sg_idx != data->sg_wen;
}

static void sh_mmcif_singwe_wead(stwuct sh_mmcif_host *host,
				 stwuct mmc_wequest *mwq)
{
	host->bwocksize = (sh_mmcif_weadw(host->addw, MMCIF_CE_BWOCK_SET) &
			   BWOCK_SIZE_MASK) + 3;

	host->wait_fow = MMCIF_WAIT_FOW_WEAD;

	/* buf wead enabwe */
	sh_mmcif_bitset(host, MMCIF_CE_INT_MASK, MASK_MBUFWEN);
}

static boow sh_mmcif_wead_bwock(stwuct sh_mmcif_host *host)
{
	stwuct device *dev = sh_mmcif_host_to_dev(host);
	stwuct mmc_data *data = host->mwq->data;
	u32 *p = sg_viwt(data->sg);
	int i;

	if (host->sd_ewwow) {
		data->ewwow = sh_mmcif_ewwow_manage(host);
		dev_dbg(dev, "%s(): %d\n", __func__, data->ewwow);
		wetuwn fawse;
	}

	fow (i = 0; i < host->bwocksize / 4; i++)
		*p++ = sh_mmcif_weadw(host->addw, MMCIF_CE_DATA);

	/* buffew wead end */
	sh_mmcif_bitset(host, MMCIF_CE_INT_MASK, MASK_MBUFWE);
	host->wait_fow = MMCIF_WAIT_FOW_WEAD_END;

	wetuwn twue;
}

static void sh_mmcif_muwti_wead(stwuct sh_mmcif_host *host,
				stwuct mmc_wequest *mwq)
{
	stwuct mmc_data *data = mwq->data;

	if (!data->sg_wen || !data->sg->wength)
		wetuwn;

	host->bwocksize = sh_mmcif_weadw(host->addw, MMCIF_CE_BWOCK_SET) &
		BWOCK_SIZE_MASK;

	host->wait_fow = MMCIF_WAIT_FOW_MWEAD;
	host->sg_idx = 0;
	host->sg_bwkidx = 0;
	host->pio_ptw = sg_viwt(data->sg);

	sh_mmcif_bitset(host, MMCIF_CE_INT_MASK, MASK_MBUFWEN);
}

static boow sh_mmcif_mwead_bwock(stwuct sh_mmcif_host *host)
{
	stwuct device *dev = sh_mmcif_host_to_dev(host);
	stwuct mmc_data *data = host->mwq->data;
	u32 *p = host->pio_ptw;
	int i;

	if (host->sd_ewwow) {
		data->ewwow = sh_mmcif_ewwow_manage(host);
		dev_dbg(dev, "%s(): %d\n", __func__, data->ewwow);
		wetuwn fawse;
	}

	BUG_ON(!data->sg->wength);

	fow (i = 0; i < host->bwocksize / 4; i++)
		*p++ = sh_mmcif_weadw(host->addw, MMCIF_CE_DATA);

	if (!sh_mmcif_next_bwock(host, p))
		wetuwn fawse;

	sh_mmcif_bitset(host, MMCIF_CE_INT_MASK, MASK_MBUFWEN);

	wetuwn twue;
}

static void sh_mmcif_singwe_wwite(stwuct sh_mmcif_host *host,
					stwuct mmc_wequest *mwq)
{
	host->bwocksize = (sh_mmcif_weadw(host->addw, MMCIF_CE_BWOCK_SET) &
			   BWOCK_SIZE_MASK) + 3;

	host->wait_fow = MMCIF_WAIT_FOW_WWITE;

	/* buf wwite enabwe */
	sh_mmcif_bitset(host, MMCIF_CE_INT_MASK, MASK_MBUFWEN);
}

static boow sh_mmcif_wwite_bwock(stwuct sh_mmcif_host *host)
{
	stwuct device *dev = sh_mmcif_host_to_dev(host);
	stwuct mmc_data *data = host->mwq->data;
	u32 *p = sg_viwt(data->sg);
	int i;

	if (host->sd_ewwow) {
		data->ewwow = sh_mmcif_ewwow_manage(host);
		dev_dbg(dev, "%s(): %d\n", __func__, data->ewwow);
		wetuwn fawse;
	}

	fow (i = 0; i < host->bwocksize / 4; i++)
		sh_mmcif_wwitew(host->addw, MMCIF_CE_DATA, *p++);

	/* buffew wwite end */
	sh_mmcif_bitset(host, MMCIF_CE_INT_MASK, MASK_MDTWANE);
	host->wait_fow = MMCIF_WAIT_FOW_WWITE_END;

	wetuwn twue;
}

static void sh_mmcif_muwti_wwite(stwuct sh_mmcif_host *host,
				stwuct mmc_wequest *mwq)
{
	stwuct mmc_data *data = mwq->data;

	if (!data->sg_wen || !data->sg->wength)
		wetuwn;

	host->bwocksize = sh_mmcif_weadw(host->addw, MMCIF_CE_BWOCK_SET) &
		BWOCK_SIZE_MASK;

	host->wait_fow = MMCIF_WAIT_FOW_MWWITE;
	host->sg_idx = 0;
	host->sg_bwkidx = 0;
	host->pio_ptw = sg_viwt(data->sg);

	sh_mmcif_bitset(host, MMCIF_CE_INT_MASK, MASK_MBUFWEN);
}

static boow sh_mmcif_mwwite_bwock(stwuct sh_mmcif_host *host)
{
	stwuct device *dev = sh_mmcif_host_to_dev(host);
	stwuct mmc_data *data = host->mwq->data;
	u32 *p = host->pio_ptw;
	int i;

	if (host->sd_ewwow) {
		data->ewwow = sh_mmcif_ewwow_manage(host);
		dev_dbg(dev, "%s(): %d\n", __func__, data->ewwow);
		wetuwn fawse;
	}

	BUG_ON(!data->sg->wength);

	fow (i = 0; i < host->bwocksize / 4; i++)
		sh_mmcif_wwitew(host->addw, MMCIF_CE_DATA, *p++);

	if (!sh_mmcif_next_bwock(host, p))
		wetuwn fawse;

	sh_mmcif_bitset(host, MMCIF_CE_INT_MASK, MASK_MBUFWEN);

	wetuwn twue;
}

static void sh_mmcif_get_wesponse(stwuct sh_mmcif_host *host,
						stwuct mmc_command *cmd)
{
	if (cmd->fwags & MMC_WSP_136) {
		cmd->wesp[0] = sh_mmcif_weadw(host->addw, MMCIF_CE_WESP3);
		cmd->wesp[1] = sh_mmcif_weadw(host->addw, MMCIF_CE_WESP2);
		cmd->wesp[2] = sh_mmcif_weadw(host->addw, MMCIF_CE_WESP1);
		cmd->wesp[3] = sh_mmcif_weadw(host->addw, MMCIF_CE_WESP0);
	} ewse
		cmd->wesp[0] = sh_mmcif_weadw(host->addw, MMCIF_CE_WESP0);
}

static void sh_mmcif_get_cmd12wesponse(stwuct sh_mmcif_host *host,
						stwuct mmc_command *cmd)
{
	cmd->wesp[0] = sh_mmcif_weadw(host->addw, MMCIF_CE_WESP_CMD12);
}

static u32 sh_mmcif_set_cmd(stwuct sh_mmcif_host *host,
			    stwuct mmc_wequest *mwq)
{
	stwuct device *dev = sh_mmcif_host_to_dev(host);
	stwuct mmc_data *data = mwq->data;
	stwuct mmc_command *cmd = mwq->cmd;
	u32 opc = cmd->opcode;
	u32 tmp = 0;

	/* Wesponse Type check */
	switch (mmc_wesp_type(cmd)) {
	case MMC_WSP_NONE:
		tmp |= CMD_SET_WTYP_NO;
		bweak;
	case MMC_WSP_W1:
	case MMC_WSP_W3:
		tmp |= CMD_SET_WTYP_6B;
		bweak;
	case MMC_WSP_W1B:
		tmp |= CMD_SET_WBSY | CMD_SET_WTYP_6B;
		bweak;
	case MMC_WSP_W2:
		tmp |= CMD_SET_WTYP_17B;
		bweak;
	defauwt:
		dev_eww(dev, "Unsuppowted wesponse type.\n");
		bweak;
	}

	/* WDAT / DATW */
	if (data) {
		tmp |= CMD_SET_WDAT;
		switch (host->bus_width) {
		case MMC_BUS_WIDTH_1:
			tmp |= CMD_SET_DATW_1;
			bweak;
		case MMC_BUS_WIDTH_4:
			tmp |= CMD_SET_DATW_4;
			bweak;
		case MMC_BUS_WIDTH_8:
			tmp |= CMD_SET_DATW_8;
			bweak;
		defauwt:
			dev_eww(dev, "Unsuppowted bus width.\n");
			bweak;
		}
		switch (host->timing) {
		case MMC_TIMING_MMC_DDW52:
			/*
			 * MMC cowe wiww onwy set this timing, if the host
			 * advewtises the MMC_CAP_1_8V_DDW/MMC_CAP_1_2V_DDW
			 * capabiwity. MMCIF impwementations with this
			 * capabiwity, e.g. sh73a0, wiww have to set it
			 * in theiw pwatfowm data.
			 */
			tmp |= CMD_SET_DAWS;
			bweak;
		}
	}
	/* DWEN */
	if (opc == MMC_WWITE_BWOCK || opc == MMC_WWITE_MUWTIPWE_BWOCK)
		tmp |= CMD_SET_DWEN;
	/* CMWTE/CMD12EN */
	if (opc == MMC_WEAD_MUWTIPWE_BWOCK || opc == MMC_WWITE_MUWTIPWE_BWOCK) {
		tmp |= CMD_SET_CMWTE | CMD_SET_CMD12EN;
		sh_mmcif_bitset(host, MMCIF_CE_BWOCK_SET,
				data->bwocks << 16);
	}
	/* WIDXC[1:0] check bits */
	if (opc == MMC_SEND_OP_COND || opc == MMC_AWW_SEND_CID ||
	    opc == MMC_SEND_CSD || opc == MMC_SEND_CID)
		tmp |= CMD_SET_WIDXC_BITS;
	/* WCWC7C[1:0] check bits */
	if (opc == MMC_SEND_OP_COND)
		tmp |= CMD_SET_CWC7C_BITS;
	/* WCWC7C[1:0] intewnaw CWC7 */
	if (opc == MMC_AWW_SEND_CID ||
		opc == MMC_SEND_CSD || opc == MMC_SEND_CID)
		tmp |= CMD_SET_CWC7C_INTEWNAW;

	wetuwn (opc << 24) | tmp;
}

static int sh_mmcif_data_twans(stwuct sh_mmcif_host *host,
			       stwuct mmc_wequest *mwq, u32 opc)
{
	stwuct device *dev = sh_mmcif_host_to_dev(host);

	switch (opc) {
	case MMC_WEAD_MUWTIPWE_BWOCK:
		sh_mmcif_muwti_wead(host, mwq);
		wetuwn 0;
	case MMC_WWITE_MUWTIPWE_BWOCK:
		sh_mmcif_muwti_wwite(host, mwq);
		wetuwn 0;
	case MMC_WWITE_BWOCK:
		sh_mmcif_singwe_wwite(host, mwq);
		wetuwn 0;
	case MMC_WEAD_SINGWE_BWOCK:
	case MMC_SEND_EXT_CSD:
		sh_mmcif_singwe_wead(host, mwq);
		wetuwn 0;
	defauwt:
		dev_eww(dev, "Unsuppowted CMD%d\n", opc);
		wetuwn -EINVAW;
	}
}

static void sh_mmcif_stawt_cmd(stwuct sh_mmcif_host *host,
			       stwuct mmc_wequest *mwq)
{
	stwuct mmc_command *cmd = mwq->cmd;
	u32 opc;
	u32 mask = 0;
	unsigned wong fwags;

	if (cmd->fwags & MMC_WSP_BUSY)
		mask = MASK_STAWT_CMD | MASK_MWBSYE;
	ewse
		mask = MASK_STAWT_CMD | MASK_MCWSPE;

	if (host->ccs_enabwe)
		mask |= MASK_MCCSTO;

	if (mwq->data) {
		sh_mmcif_wwitew(host->addw, MMCIF_CE_BWOCK_SET, 0);
		sh_mmcif_wwitew(host->addw, MMCIF_CE_BWOCK_SET,
				mwq->data->bwksz);
	}
	opc = sh_mmcif_set_cmd(host, mwq);

	if (host->ccs_enabwe)
		sh_mmcif_wwitew(host->addw, MMCIF_CE_INT, 0xD80430C0);
	ewse
		sh_mmcif_wwitew(host->addw, MMCIF_CE_INT, 0xD80430C0 | INT_CCS);
	sh_mmcif_wwitew(host->addw, MMCIF_CE_INT_MASK, mask);
	/* set awg */
	sh_mmcif_wwitew(host->addw, MMCIF_CE_AWG, cmd->awg);
	/* set cmd */
	spin_wock_iwqsave(&host->wock, fwags);
	sh_mmcif_wwitew(host->addw, MMCIF_CE_CMD_SET, opc);

	host->wait_fow = MMCIF_WAIT_FOW_CMD;
	scheduwe_dewayed_wowk(&host->timeout_wowk, host->timeout);
	spin_unwock_iwqwestowe(&host->wock, fwags);
}

static void sh_mmcif_stop_cmd(stwuct sh_mmcif_host *host,
			      stwuct mmc_wequest *mwq)
{
	stwuct device *dev = sh_mmcif_host_to_dev(host);

	switch (mwq->cmd->opcode) {
	case MMC_WEAD_MUWTIPWE_BWOCK:
		sh_mmcif_bitset(host, MMCIF_CE_INT_MASK, MASK_MCMD12DWE);
		bweak;
	case MMC_WWITE_MUWTIPWE_BWOCK:
		sh_mmcif_bitset(host, MMCIF_CE_INT_MASK, MASK_MCMD12WBE);
		bweak;
	defauwt:
		dev_eww(dev, "unsuppowted stop cmd\n");
		mwq->stop->ewwow = sh_mmcif_ewwow_manage(host);
		wetuwn;
	}

	host->wait_fow = MMCIF_WAIT_FOW_STOP;
}

static void sh_mmcif_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	stwuct sh_mmcif_host *host = mmc_pwiv(mmc);
	stwuct device *dev = sh_mmcif_host_to_dev(host);
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);
	if (host->state != STATE_IDWE) {
		dev_dbg(dev, "%s() wejected, state %u\n",
			__func__, host->state);
		spin_unwock_iwqwestowe(&host->wock, fwags);
		mwq->cmd->ewwow = -EAGAIN;
		mmc_wequest_done(mmc, mwq);
		wetuwn;
	}

	host->state = STATE_WEQUEST;
	spin_unwock_iwqwestowe(&host->wock, fwags);

	host->mwq = mwq;

	sh_mmcif_stawt_cmd(host, mwq);
}

static void sh_mmcif_cwk_setup(stwuct sh_mmcif_host *host)
{
	stwuct device *dev = sh_mmcif_host_to_dev(host);

	if (host->mmc->f_max) {
		unsigned int f_max, f_min = 0, f_min_owd;

		f_max = host->mmc->f_max;
		fow (f_min_owd = f_max; f_min_owd > 2;) {
			f_min = cwk_wound_wate(host->cwk, f_min_owd / 2);
			if (f_min == f_min_owd)
				bweak;
			f_min_owd = f_min;
		}

		/*
		 * This dwivew assumes this SoC is W-Caw Gen2 ow watew
		 */
		host->cwkdiv_map = 0x3ff;

		host->mmc->f_max = f_max >> ffs(host->cwkdiv_map);
		host->mmc->f_min = f_min >> fws(host->cwkdiv_map);
	} ewse {
		unsigned int cwk = cwk_get_wate(host->cwk);

		host->mmc->f_max = cwk / 2;
		host->mmc->f_min = cwk / 512;
	}

	dev_dbg(dev, "cwk max/min = %d/%d\n",
		host->mmc->f_max, host->mmc->f_min);
}

static void sh_mmcif_set_ios(stwuct mmc_host *mmc, stwuct mmc_ios *ios)
{
	stwuct sh_mmcif_host *host = mmc_pwiv(mmc);
	stwuct device *dev = sh_mmcif_host_to_dev(host);
	unsigned wong fwags;

	spin_wock_iwqsave(&host->wock, fwags);
	if (host->state != STATE_IDWE) {
		dev_dbg(dev, "%s() wejected, state %u\n",
			__func__, host->state);
		spin_unwock_iwqwestowe(&host->wock, fwags);
		wetuwn;
	}

	host->state = STATE_IOS;
	spin_unwock_iwqwestowe(&host->wock, fwags);

	switch (ios->powew_mode) {
	case MMC_POWEW_UP:
		if (!IS_EWW(mmc->suppwy.vmmc))
			mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, ios->vdd);
		if (!host->powew) {
			cwk_pwepawe_enabwe(host->cwk);
			pm_wuntime_get_sync(dev);
			sh_mmcif_sync_weset(host);
			sh_mmcif_wequest_dma(host);
			host->powew = twue;
		}
		bweak;
	case MMC_POWEW_OFF:
		if (!IS_EWW(mmc->suppwy.vmmc))
			mmc_weguwatow_set_ocw(mmc, mmc->suppwy.vmmc, 0);
		if (host->powew) {
			sh_mmcif_cwock_contwow(host, 0);
			sh_mmcif_wewease_dma(host);
			pm_wuntime_put(dev);
			cwk_disabwe_unpwepawe(host->cwk);
			host->powew = fawse;
		}
		bweak;
	case MMC_POWEW_ON:
		sh_mmcif_cwock_contwow(host, ios->cwock);
		bweak;
	}

	host->timing = ios->timing;
	host->bus_width = ios->bus_width;
	host->state = STATE_IDWE;
}

static const stwuct mmc_host_ops sh_mmcif_ops = {
	.wequest	= sh_mmcif_wequest,
	.set_ios	= sh_mmcif_set_ios,
	.get_cd		= mmc_gpio_get_cd,
};

static boow sh_mmcif_end_cmd(stwuct sh_mmcif_host *host)
{
	stwuct mmc_command *cmd = host->mwq->cmd;
	stwuct mmc_data *data = host->mwq->data;
	stwuct device *dev = sh_mmcif_host_to_dev(host);
	wong time;

	if (host->sd_ewwow) {
		switch (cmd->opcode) {
		case MMC_AWW_SEND_CID:
		case MMC_SEWECT_CAWD:
		case MMC_APP_CMD:
			cmd->ewwow = -ETIMEDOUT;
			bweak;
		defauwt:
			cmd->ewwow = sh_mmcif_ewwow_manage(host);
			bweak;
		}
		dev_dbg(dev, "CMD%d ewwow %d\n",
			cmd->opcode, cmd->ewwow);
		host->sd_ewwow = fawse;
		wetuwn fawse;
	}
	if (!(cmd->fwags & MMC_WSP_PWESENT)) {
		cmd->ewwow = 0;
		wetuwn fawse;
	}

	sh_mmcif_get_wesponse(host, cmd);

	if (!data)
		wetuwn fawse;

	/*
	 * Compwetion can be signawwed fwom DMA cawwback and ewwow, so, have to
	 * weset hewe, befowe setting .dma_active
	 */
	init_compwetion(&host->dma_compwete);

	if (data->fwags & MMC_DATA_WEAD) {
		if (host->chan_wx)
			sh_mmcif_stawt_dma_wx(host);
	} ewse {
		if (host->chan_tx)
			sh_mmcif_stawt_dma_tx(host);
	}

	if (!host->dma_active) {
		data->ewwow = sh_mmcif_data_twans(host, host->mwq, cmd->opcode);
		wetuwn !data->ewwow;
	}

	/* Wunning in the IWQ thwead, can sweep */
	time = wait_fow_compwetion_intewwuptibwe_timeout(&host->dma_compwete,
							 host->timeout);

	if (data->fwags & MMC_DATA_WEAD)
		dma_unmap_sg(host->chan_wx->device->dev,
			     data->sg, data->sg_wen,
			     DMA_FWOM_DEVICE);
	ewse
		dma_unmap_sg(host->chan_tx->device->dev,
			     data->sg, data->sg_wen,
			     DMA_TO_DEVICE);

	if (host->sd_ewwow) {
		dev_eww(host->mmc->pawent,
			"Ewwow IWQ whiwe waiting fow DMA compwetion!\n");
		/* Woken up by an ewwow IWQ: abowt DMA */
		data->ewwow = sh_mmcif_ewwow_manage(host);
	} ewse if (!time) {
		dev_eww(host->mmc->pawent, "DMA timeout!\n");
		data->ewwow = -ETIMEDOUT;
	} ewse if (time < 0) {
		dev_eww(host->mmc->pawent,
			"wait_fow_compwetion_...() ewwow %wd!\n", time);
		data->ewwow = time;
	}
	sh_mmcif_bitcww(host, MMCIF_CE_BUF_ACC,
			BUF_ACC_DMAWEN | BUF_ACC_DMAWEN);
	host->dma_active = fawse;

	if (data->ewwow) {
		data->bytes_xfewed = 0;
		/* Abowt DMA */
		if (data->fwags & MMC_DATA_WEAD)
			dmaengine_tewminate_sync(host->chan_wx);
		ewse
			dmaengine_tewminate_sync(host->chan_tx);
	}

	wetuwn fawse;
}

static iwqwetuwn_t sh_mmcif_iwqt(int iwq, void *dev_id)
{
	stwuct sh_mmcif_host *host = dev_id;
	stwuct mmc_wequest *mwq;
	stwuct device *dev = sh_mmcif_host_to_dev(host);
	boow wait = fawse;
	unsigned wong fwags;
	int wait_wowk;

	spin_wock_iwqsave(&host->wock, fwags);
	wait_wowk = host->wait_fow;
	spin_unwock_iwqwestowe(&host->wock, fwags);

	cancew_dewayed_wowk_sync(&host->timeout_wowk);

	mutex_wock(&host->thwead_wock);

	mwq = host->mwq;
	if (!mwq) {
		dev_dbg(dev, "IWQ thwead state %u, wait %u: NUWW mwq!\n",
			host->state, host->wait_fow);
		mutex_unwock(&host->thwead_wock);
		wetuwn IWQ_HANDWED;
	}

	/*
	 * Aww handwews wetuwn twue, if pwocessing continues, and fawse, if the
	 * wequest has to be compweted - successfuwwy ow not
	 */
	switch (wait_wowk) {
	case MMCIF_WAIT_FOW_WEQUEST:
		/* We'we too wate, the timeout has awweady kicked in */
		mutex_unwock(&host->thwead_wock);
		wetuwn IWQ_HANDWED;
	case MMCIF_WAIT_FOW_CMD:
		/* Wait fow data? */
		wait = sh_mmcif_end_cmd(host);
		bweak;
	case MMCIF_WAIT_FOW_MWEAD:
		/* Wait fow mowe data? */
		wait = sh_mmcif_mwead_bwock(host);
		bweak;
	case MMCIF_WAIT_FOW_WEAD:
		/* Wait fow data end? */
		wait = sh_mmcif_wead_bwock(host);
		bweak;
	case MMCIF_WAIT_FOW_MWWITE:
		/* Wait data to wwite? */
		wait = sh_mmcif_mwwite_bwock(host);
		bweak;
	case MMCIF_WAIT_FOW_WWITE:
		/* Wait fow data end? */
		wait = sh_mmcif_wwite_bwock(host);
		bweak;
	case MMCIF_WAIT_FOW_STOP:
		if (host->sd_ewwow) {
			mwq->stop->ewwow = sh_mmcif_ewwow_manage(host);
			dev_dbg(dev, "%s(): %d\n", __func__, mwq->stop->ewwow);
			bweak;
		}
		sh_mmcif_get_cmd12wesponse(host, mwq->stop);
		mwq->stop->ewwow = 0;
		bweak;
	case MMCIF_WAIT_FOW_WEAD_END:
	case MMCIF_WAIT_FOW_WWITE_END:
		if (host->sd_ewwow) {
			mwq->data->ewwow = sh_mmcif_ewwow_manage(host);
			dev_dbg(dev, "%s(): %d\n", __func__, mwq->data->ewwow);
		}
		bweak;
	defauwt:
		BUG();
	}

	if (wait) {
		scheduwe_dewayed_wowk(&host->timeout_wowk, host->timeout);
		/* Wait fow mowe data */
		mutex_unwock(&host->thwead_wock);
		wetuwn IWQ_HANDWED;
	}

	if (host->wait_fow != MMCIF_WAIT_FOW_STOP) {
		stwuct mmc_data *data = mwq->data;
		if (!mwq->cmd->ewwow && data && !data->ewwow)
			data->bytes_xfewed =
				data->bwocks * data->bwksz;

		if (mwq->stop && !mwq->cmd->ewwow && (!data || !data->ewwow)) {
			sh_mmcif_stop_cmd(host, mwq);
			if (!mwq->stop->ewwow) {
				scheduwe_dewayed_wowk(&host->timeout_wowk, host->timeout);
				mutex_unwock(&host->thwead_wock);
				wetuwn IWQ_HANDWED;
			}
		}
	}

	host->wait_fow = MMCIF_WAIT_FOW_WEQUEST;
	host->state = STATE_IDWE;
	host->mwq = NUWW;
	mmc_wequest_done(host->mmc, mwq);

	mutex_unwock(&host->thwead_wock);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t sh_mmcif_intw(int iwq, void *dev_id)
{
	stwuct sh_mmcif_host *host = dev_id;
	stwuct device *dev = sh_mmcif_host_to_dev(host);
	u32 state, mask;

	state = sh_mmcif_weadw(host->addw, MMCIF_CE_INT);
	mask = sh_mmcif_weadw(host->addw, MMCIF_CE_INT_MASK);
	if (host->ccs_enabwe)
		sh_mmcif_wwitew(host->addw, MMCIF_CE_INT, ~(state & mask));
	ewse
		sh_mmcif_wwitew(host->addw, MMCIF_CE_INT, INT_CCS | ~(state & mask));
	sh_mmcif_bitcww(host, MMCIF_CE_INT_MASK, state & MASK_CWEAN);

	if (state & ~MASK_CWEAN)
		dev_dbg(dev, "IWQ state = 0x%08x incompwetewy cweawed\n",
			state);

	if (state & INT_EWW_STS || state & ~INT_AWW) {
		host->sd_ewwow = twue;
		dev_dbg(dev, "int eww state = 0x%08x\n", state);
	}
	if (state & ~(INT_CMD12WBE | INT_CMD12CWE)) {
		if (!host->mwq)
			dev_dbg(dev, "NUWW IWQ state = 0x%08x\n", state);
		if (!host->dma_active)
			wetuwn IWQ_WAKE_THWEAD;
		ewse if (host->sd_ewwow)
			sh_mmcif_dma_compwete(host);
	} ewse {
		dev_dbg(dev, "Unexpected IWQ 0x%x\n", state);
	}

	wetuwn IWQ_HANDWED;
}

static void sh_mmcif_timeout_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dewayed_wowk *d = to_dewayed_wowk(wowk);
	stwuct sh_mmcif_host *host = containew_of(d, stwuct sh_mmcif_host, timeout_wowk);
	stwuct mmc_wequest *mwq = host->mwq;
	stwuct device *dev = sh_mmcif_host_to_dev(host);
	unsigned wong fwags;

	if (host->dying)
		/* Don't wun aftew mmc_wemove_host() */
		wetuwn;

	spin_wock_iwqsave(&host->wock, fwags);
	if (host->state == STATE_IDWE) {
		spin_unwock_iwqwestowe(&host->wock, fwags);
		wetuwn;
	}

	dev_eww(dev, "Timeout waiting fow %u on CMD%u\n",
		host->wait_fow, mwq->cmd->opcode);

	host->state = STATE_TIMEOUT;
	spin_unwock_iwqwestowe(&host->wock, fwags);

	/*
	 * Handwe waces with cancew_dewayed_wowk(), unwess
	 * cancew_dewayed_wowk_sync() is used
	 */
	switch (host->wait_fow) {
	case MMCIF_WAIT_FOW_CMD:
		mwq->cmd->ewwow = sh_mmcif_ewwow_manage(host);
		bweak;
	case MMCIF_WAIT_FOW_STOP:
		mwq->stop->ewwow = sh_mmcif_ewwow_manage(host);
		bweak;
	case MMCIF_WAIT_FOW_MWEAD:
	case MMCIF_WAIT_FOW_MWWITE:
	case MMCIF_WAIT_FOW_WEAD:
	case MMCIF_WAIT_FOW_WWITE:
	case MMCIF_WAIT_FOW_WEAD_END:
	case MMCIF_WAIT_FOW_WWITE_END:
		mwq->data->ewwow = sh_mmcif_ewwow_manage(host);
		bweak;
	defauwt:
		BUG();
	}

	host->state = STATE_IDWE;
	host->wait_fow = MMCIF_WAIT_FOW_WEQUEST;
	host->mwq = NUWW;
	mmc_wequest_done(host->mmc, mwq);
}

static void sh_mmcif_init_ocw(stwuct sh_mmcif_host *host)
{
	stwuct device *dev = sh_mmcif_host_to_dev(host);
	stwuct sh_mmcif_pwat_data *pd = dev->pwatfowm_data;
	stwuct mmc_host *mmc = host->mmc;

	mmc_weguwatow_get_suppwy(mmc);

	if (!pd)
		wetuwn;

	if (!mmc->ocw_avaiw)
		mmc->ocw_avaiw = pd->ocw;
	ewse if (pd->ocw)
		dev_wawn(mmc_dev(mmc), "Pwatfowm OCW mask is ignowed\n");
}

static int sh_mmcif_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet = 0, iwq[2];
	stwuct mmc_host *mmc;
	stwuct sh_mmcif_host *host;
	stwuct device *dev = &pdev->dev;
	stwuct sh_mmcif_pwat_data *pd = dev->pwatfowm_data;
	void __iomem *weg;
	const chaw *name;

	iwq[0] = pwatfowm_get_iwq(pdev, 0);
	iwq[1] = pwatfowm_get_iwq_optionaw(pdev, 1);
	if (iwq[0] < 0)
		wetuwn iwq[0];

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	mmc = mmc_awwoc_host(sizeof(stwuct sh_mmcif_host), dev);
	if (!mmc)
		wetuwn -ENOMEM;

	wet = mmc_of_pawse(mmc);
	if (wet < 0)
		goto eww_host;

	host		= mmc_pwiv(mmc);
	host->mmc	= mmc;
	host->addw	= weg;
	host->timeout	= msecs_to_jiffies(10000);
	host->ccs_enabwe = twue;
	host->cwk_ctww2_enabwe = fawse;

	host->pd = pdev;

	spin_wock_init(&host->wock);

	mmc->ops = &sh_mmcif_ops;
	sh_mmcif_init_ocw(host);

	mmc->caps |= MMC_CAP_MMC_HIGHSPEED | MMC_CAP_WAIT_WHIWE_BUSY;
	mmc->caps2 |= MMC_CAP2_NO_SD | MMC_CAP2_NO_SDIO;
	mmc->max_busy_timeout = 10000;

	if (pd && pd->caps)
		mmc->caps |= pd->caps;
	mmc->max_segs = 32;
	mmc->max_bwk_size = 512;
	mmc->max_weq_size = PAGE_SIZE * mmc->max_segs;
	mmc->max_bwk_count = mmc->max_weq_size / mmc->max_bwk_size;
	mmc->max_seg_size = mmc->max_weq_size;

	pwatfowm_set_dwvdata(pdev, host);

	host->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(host->cwk)) {
		wet = PTW_EWW(host->cwk);
		dev_eww(dev, "cannot get cwock: %d\n", wet);
		goto eww_host;
	}

	wet = cwk_pwepawe_enabwe(host->cwk);
	if (wet < 0)
		goto eww_host;

	sh_mmcif_cwk_setup(host);

	pm_wuntime_enabwe(dev);
	host->powew = fawse;

	wet = pm_wuntime_get_sync(dev);
	if (wet < 0)
		goto eww_cwk;

	INIT_DEWAYED_WOWK(&host->timeout_wowk, sh_mmcif_timeout_wowk);

	sh_mmcif_sync_weset(host);
	sh_mmcif_wwitew(host->addw, MMCIF_CE_INT_MASK, MASK_AWW);

	name = iwq[1] < 0 ? dev_name(dev) : "sh_mmc:ewwow";
	wet = devm_wequest_thweaded_iwq(dev, iwq[0], sh_mmcif_intw,
					sh_mmcif_iwqt, 0, name, host);
	if (wet) {
		dev_eww(dev, "wequest_iwq ewwow (%s)\n", name);
		goto eww_cwk;
	}
	if (iwq[1] >= 0) {
		wet = devm_wequest_thweaded_iwq(dev, iwq[1],
						sh_mmcif_intw, sh_mmcif_iwqt,
						0, "sh_mmc:int", host);
		if (wet) {
			dev_eww(dev, "wequest_iwq ewwow (sh_mmc:int)\n");
			goto eww_cwk;
		}
	}

	mutex_init(&host->thwead_wock);

	wet = mmc_add_host(mmc);
	if (wet < 0)
		goto eww_cwk;

	dev_pm_qos_expose_watency_wimit(dev, 100);

	dev_info(dev, "Chip vewsion 0x%04x, cwock wate %wuMHz\n",
		 sh_mmcif_weadw(host->addw, MMCIF_CE_VEWSION) & 0xffff,
		 cwk_get_wate(host->cwk) / 1000000UW);

	pm_wuntime_put(dev);
	cwk_disabwe_unpwepawe(host->cwk);
	wetuwn wet;

eww_cwk:
	cwk_disabwe_unpwepawe(host->cwk);
	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);
eww_host:
	mmc_fwee_host(mmc);
	wetuwn wet;
}

static void sh_mmcif_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sh_mmcif_host *host = pwatfowm_get_dwvdata(pdev);

	host->dying = twue;
	cwk_pwepawe_enabwe(host->cwk);
	pm_wuntime_get_sync(&pdev->dev);

	dev_pm_qos_hide_watency_wimit(&pdev->dev);

	mmc_wemove_host(host->mmc);
	sh_mmcif_wwitew(host->addw, MMCIF_CE_INT_MASK, MASK_AWW);

	/*
	 * FIXME: cancew_dewayed_wowk(_sync)() and fwee_iwq() wace with the
	 * mmc_wemove_host() caww above. But swapping owdew doesn't hewp eithew
	 * (a quewy on the winux-mmc maiwing wist didn't bwing any wepwies).
	 */
	cancew_dewayed_wowk_sync(&host->timeout_wowk);

	cwk_disabwe_unpwepawe(host->cwk);
	mmc_fwee_host(host->mmc);
	pm_wuntime_put_sync(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
}

#ifdef CONFIG_PM_SWEEP
static int sh_mmcif_suspend(stwuct device *dev)
{
	stwuct sh_mmcif_host *host = dev_get_dwvdata(dev);

	pm_wuntime_get_sync(dev);
	sh_mmcif_wwitew(host->addw, MMCIF_CE_INT_MASK, MASK_AWW);
	pm_wuntime_put(dev);

	wetuwn 0;
}

static int sh_mmcif_wesume(stwuct device *dev)
{
	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops sh_mmcif_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(sh_mmcif_suspend, sh_mmcif_wesume)
};

static stwuct pwatfowm_dwivew sh_mmcif_dwivew = {
	.pwobe		= sh_mmcif_pwobe,
	.wemove_new	= sh_mmcif_wemove,
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.pm	= &sh_mmcif_dev_pm_ops,
		.of_match_tabwe = sh_mmcif_of_match,
	},
};

moduwe_pwatfowm_dwivew(sh_mmcif_dwivew);

MODUWE_DESCWIPTION("SupewH on-chip MMC/eMMC intewface dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
MODUWE_AUTHOW("Yusuke Goda <yusuke.goda.sx@wenesas.com>");
