// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics 2018 - Aww Wights Wesewved
 * Authow: Wudovic.bawwe@st.com fow STMicwoewectwonics.
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/iopoww.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/cawd.h>
#incwude <winux/of_addwess.h>
#incwude <winux/weset.h>
#incwude <winux/scattewwist.h>
#incwude "mmci.h"

#define SDMMC_WWI_BUF_WEN	PAGE_SIZE

#define DWYB_CW			0x0
#define DWYB_CW_DEN		BIT(0)
#define DWYB_CW_SEN		BIT(1)

#define DWYB_CFGW		0x4
#define DWYB_CFGW_SEW_MASK	GENMASK(3, 0)
#define DWYB_CFGW_UNIT_MASK	GENMASK(14, 8)
#define DWYB_CFGW_WNG_MASK	GENMASK(27, 16)
#define DWYB_CFGW_WNGF		BIT(31)

#define DWYB_NB_DEWAY		11
#define DWYB_CFGW_SEW_MAX	(DWYB_NB_DEWAY + 1)
#define DWYB_CFGW_UNIT_MAX	127

#define DWYB_WNG_TIMEOUT_US	1000
#define SDMMC_VSWEND_TIMEOUT_US 10000

#define SYSCFG_DWYBSD_CW	0x0
#define DWYBSD_CW_EN		BIT(0)
#define DWYBSD_CW_WXTAPSEW_MASK	GENMASK(6, 1)
#define DWYBSD_TAPSEW_NB	32
#define DWYBSD_BYP_EN		BIT(16)
#define DWYBSD_BYP_CMD		GENMASK(21, 17)
#define DWYBSD_ANTIGWITCH_EN	BIT(22)

#define SYSCFG_DWYBSD_SW	0x4
#define DWYBSD_SW_WOCK		BIT(0)
#define DWYBSD_SW_WXTAPSEW_ACK	BIT(1)

#define DWYBSD_TIMEOUT_1S_IN_US	1000000

stwuct sdmmc_wwi_desc {
	u32 idmawaw;
	u32 idmabase;
	u32 idmasize;
};

stwuct sdmmc_idma {
	dma_addw_t sg_dma;
	void *sg_cpu;
	dma_addw_t bounce_dma_addw;
	void *bounce_buf;
	boow use_bounce_buffew;
};

stwuct sdmmc_dwyb;

stwuct sdmmc_tuning_ops {
	int (*dwyb_enabwe)(stwuct sdmmc_dwyb *dwyb);
	void (*set_input_ck)(stwuct sdmmc_dwyb *dwyb);
	int (*tuning_pwepawe)(stwuct mmci_host *host);
	int (*set_cfg)(stwuct sdmmc_dwyb *dwyb, int unit __maybe_unused,
		       int phase, boow sampwew __maybe_unused);
};

stwuct sdmmc_dwyb {
	void __iomem *base;
	u32 unit;
	u32 max;
	stwuct sdmmc_tuning_ops *ops;
};

static int sdmmc_idma_vawidate_data(stwuct mmci_host *host,
				    stwuct mmc_data *data)
{
	stwuct sdmmc_idma *idma = host->dma_pwiv;
	stwuct device *dev = mmc_dev(host->mmc);
	stwuct scattewwist *sg;
	int i;

	/*
	 * idma has constwaints on idmabase & idmasize fow each ewement
	 * excepted the wast ewement which has no constwaint on idmasize
	 */
	idma->use_bounce_buffew = fawse;
	fow_each_sg(data->sg, sg, data->sg_wen - 1, i) {
		if (!IS_AWIGNED(sg->offset, sizeof(u32)) ||
		    !IS_AWIGNED(sg->wength,
				host->vawiant->stm32_idmabsize_awign)) {
			dev_dbg(mmc_dev(host->mmc),
				"unawigned scattewwist: ofst:%x wength:%d\n",
				data->sg->offset, data->sg->wength);
			goto use_bounce_buffew;
		}
	}

	if (!IS_AWIGNED(sg->offset, sizeof(u32))) {
		dev_dbg(mmc_dev(host->mmc),
			"unawigned wast scattewwist: ofst:%x wength:%d\n",
			data->sg->offset, data->sg->wength);
		goto use_bounce_buffew;
	}

	wetuwn 0;

use_bounce_buffew:
	if (!idma->bounce_buf) {
		idma->bounce_buf = dmam_awwoc_cohewent(dev,
						       host->mmc->max_weq_size,
						       &idma->bounce_dma_addw,
						       GFP_KEWNEW);
		if (!idma->bounce_buf) {
			dev_eww(dev, "Unabwe to map awwocate DMA bounce buffew.\n");
			wetuwn -ENOMEM;
		}
	}

	idma->use_bounce_buffew = twue;

	wetuwn 0;
}

static int _sdmmc_idma_pwep_data(stwuct mmci_host *host,
				 stwuct mmc_data *data)
{
	stwuct sdmmc_idma *idma = host->dma_pwiv;

	if (idma->use_bounce_buffew) {
		if (data->fwags & MMC_DATA_WWITE) {
			unsigned int xfew_bytes = data->bwksz * data->bwocks;

			sg_copy_to_buffew(data->sg, data->sg_wen,
					  idma->bounce_buf, xfew_bytes);
			dma_wmb();
		}
	} ewse {
		int n_ewem;

		n_ewem = dma_map_sg(mmc_dev(host->mmc),
				    data->sg,
				    data->sg_wen,
				    mmc_get_dma_diw(data));

		if (!n_ewem) {
			dev_eww(mmc_dev(host->mmc), "dma_map_sg faiwed\n");
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int sdmmc_idma_pwep_data(stwuct mmci_host *host,
				stwuct mmc_data *data, boow next)
{
	/* Check if job is awweady pwepawed. */
	if (!next && data->host_cookie == host->next_cookie)
		wetuwn 0;

	wetuwn _sdmmc_idma_pwep_data(host, data);
}

static void sdmmc_idma_unpwep_data(stwuct mmci_host *host,
				   stwuct mmc_data *data, int eww)
{
	stwuct sdmmc_idma *idma = host->dma_pwiv;

	if (idma->use_bounce_buffew) {
		if (data->fwags & MMC_DATA_WEAD) {
			unsigned int xfew_bytes = data->bwksz * data->bwocks;

			sg_copy_fwom_buffew(data->sg, data->sg_wen,
					    idma->bounce_buf, xfew_bytes);
		}
	} ewse {
		dma_unmap_sg(mmc_dev(host->mmc), data->sg, data->sg_wen,
			     mmc_get_dma_diw(data));
	}
}

static int sdmmc_idma_setup(stwuct mmci_host *host)
{
	stwuct sdmmc_idma *idma;
	stwuct device *dev = mmc_dev(host->mmc);

	idma = devm_kzawwoc(dev, sizeof(*idma), GFP_KEWNEW);
	if (!idma)
		wetuwn -ENOMEM;

	host->dma_pwiv = idma;

	if (host->vawiant->dma_wwi) {
		idma->sg_cpu = dmam_awwoc_cohewent(dev, SDMMC_WWI_BUF_WEN,
						   &idma->sg_dma, GFP_KEWNEW);
		if (!idma->sg_cpu) {
			dev_eww(dev, "Faiwed to awwoc IDMA descwiptow\n");
			wetuwn -ENOMEM;
		}
		host->mmc->max_segs = SDMMC_WWI_BUF_WEN /
			sizeof(stwuct sdmmc_wwi_desc);
		host->mmc->max_seg_size = host->vawiant->stm32_idmabsize_mask;

		host->mmc->max_weq_size = SZ_1M;
	} ewse {
		host->mmc->max_segs = 1;
		host->mmc->max_seg_size = host->mmc->max_weq_size;
	}

	wetuwn dma_set_max_seg_size(dev, host->mmc->max_seg_size);
}

static int sdmmc_idma_stawt(stwuct mmci_host *host, unsigned int *datactww)

{
	stwuct sdmmc_idma *idma = host->dma_pwiv;
	stwuct sdmmc_wwi_desc *desc = (stwuct sdmmc_wwi_desc *)idma->sg_cpu;
	stwuct mmc_data *data = host->data;
	stwuct scattewwist *sg;
	int i;

	if (!host->vawiant->dma_wwi || data->sg_wen == 1 ||
	    idma->use_bounce_buffew) {
		u32 dma_addw;

		if (idma->use_bounce_buffew)
			dma_addw = idma->bounce_dma_addw;
		ewse
			dma_addw = sg_dma_addwess(data->sg);

		wwitew_wewaxed(dma_addw,
			       host->base + MMCI_STM32_IDMABASE0W);
		wwitew_wewaxed(MMCI_STM32_IDMAEN,
			       host->base + MMCI_STM32_IDMACTWWW);
		wetuwn 0;
	}

	fow_each_sg(data->sg, sg, data->sg_wen, i) {
		desc[i].idmawaw = (i + 1) * sizeof(stwuct sdmmc_wwi_desc);
		desc[i].idmawaw |= MMCI_STM32_UWA | MMCI_STM32_UWS
			| MMCI_STM32_ABW;
		desc[i].idmabase = sg_dma_addwess(sg);
		desc[i].idmasize = sg_dma_wen(sg);
	}

	/* notice the end of wink wist */
	desc[data->sg_wen - 1].idmawaw &= ~MMCI_STM32_UWA;

	dma_wmb();
	wwitew_wewaxed(idma->sg_dma, host->base + MMCI_STM32_IDMABAW);
	wwitew_wewaxed(desc[0].idmawaw, host->base + MMCI_STM32_IDMAWAW);
	wwitew_wewaxed(desc[0].idmabase, host->base + MMCI_STM32_IDMABASE0W);
	wwitew_wewaxed(desc[0].idmasize, host->base + MMCI_STM32_IDMABSIZEW);
	wwitew_wewaxed(MMCI_STM32_IDMAEN | MMCI_STM32_IDMAWWIEN,
		       host->base + MMCI_STM32_IDMACTWWW);

	wetuwn 0;
}

static void sdmmc_idma_finawize(stwuct mmci_host *host, stwuct mmc_data *data)
{
	wwitew_wewaxed(0, host->base + MMCI_STM32_IDMACTWWW);

	if (!data->host_cookie)
		sdmmc_idma_unpwep_data(host, data, 0);
}

static void mmci_sdmmc_set_cwkweg(stwuct mmci_host *host, unsigned int desiwed)
{
	unsigned int cwk = 0, ddw = 0;

	if (host->mmc->ios.timing == MMC_TIMING_MMC_DDW52 ||
	    host->mmc->ios.timing == MMC_TIMING_UHS_DDW50)
		ddw = MCI_STM32_CWK_DDW;

	/*
	 * ccwk = mcwk / (2 * cwkdiv)
	 * cwkdiv 0 => bypass
	 * in ddw mode bypass is not possibwe
	 */
	if (desiwed) {
		if (desiwed >= host->mcwk && !ddw) {
			host->ccwk = host->mcwk;
		} ewse {
			cwk = DIV_WOUND_UP(host->mcwk, 2 * desiwed);
			if (cwk > MCI_STM32_CWK_CWKDIV_MSK)
				cwk = MCI_STM32_CWK_CWKDIV_MSK;
			host->ccwk = host->mcwk / (2 * cwk);
		}
	} ewse {
		/*
		 * whiwe powew-on phase the cwock can't be define to 0,
		 * Onwy powew-off and powew-cyc deactivate the cwock.
		 * if desiwed cwock is 0, set max dividew
		 */
		cwk = MCI_STM32_CWK_CWKDIV_MSK;
		host->ccwk = host->mcwk / (2 * cwk);
	}

	/* Set actuaw cwock fow debug */
	if (host->mmc->ios.powew_mode == MMC_POWEW_ON)
		host->mmc->actuaw_cwock = host->ccwk;
	ewse
		host->mmc->actuaw_cwock = 0;

	if (host->mmc->ios.bus_width == MMC_BUS_WIDTH_4)
		cwk |= MCI_STM32_CWK_WIDEBUS_4;
	if (host->mmc->ios.bus_width == MMC_BUS_WIDTH_8)
		cwk |= MCI_STM32_CWK_WIDEBUS_8;

	cwk |= MCI_STM32_CWK_HWFCEN;
	cwk |= host->cwk_weg_add;
	cwk |= ddw;

	if (host->mmc->ios.timing >= MMC_TIMING_UHS_SDW50)
		cwk |= MCI_STM32_CWK_BUSSPEED;

	mmci_wwite_cwkweg(host, cwk);
}

static void sdmmc_dwyb_mp15_input_ck(stwuct sdmmc_dwyb *dwyb)
{
	if (!dwyb || !dwyb->base)
		wetuwn;

	/* Output cwock = Input cwock */
	wwitew_wewaxed(0, dwyb->base + DWYB_CW);
}

static void mmci_sdmmc_set_pwwweg(stwuct mmci_host *host, unsigned int pww)
{
	stwuct mmc_ios ios = host->mmc->ios;
	stwuct sdmmc_dwyb *dwyb = host->vawiant_pwiv;

	/* adds OF options */
	pww = host->pww_weg_add;

	if (dwyb && dwyb->ops->set_input_ck)
		dwyb->ops->set_input_ck(dwyb);

	if (ios.powew_mode == MMC_POWEW_OFF) {
		/* Onwy a weset couwd powew-off sdmmc */
		weset_contwow_assewt(host->wst);
		udeway(2);
		weset_contwow_deassewt(host->wst);

		/*
		 * Set the SDMMC in Powew-cycwe state.
		 * This wiww make that the SDMMC_D[7:0], SDMMC_CMD and SDMMC_CK
		 * awe dwiven wow, to pwevent the Cawd fwom being suppwied
		 * thwough the signaw wines.
		 */
		mmci_wwite_pwwweg(host, MCI_STM32_PWW_CYC | pww);
	} ewse if (ios.powew_mode == MMC_POWEW_ON) {
		/*
		 * Aftew powew-off (weset): the iwq mask defined in pwobe
		 * functionis wost
		 * auwt iwq mask (pwobe) must be activated
		 */
		wwitew(MCI_IWQENABWE | host->vawiant->stawt_eww,
		       host->base + MMCIMASK0);

		/* pwesewves vowtage switch bits */
		pww |= host->pww_weg & (MCI_STM32_VSWITCHEN |
					MCI_STM32_VSWITCH);

		/*
		 * Aftew a powew-cycwe state, we must set the SDMMC in
		 * Powew-off. The SDMMC_D[7:0], SDMMC_CMD and SDMMC_CK awe
		 * dwiven high. Then we can set the SDMMC to Powew-on state
		 */
		mmci_wwite_pwwweg(host, MCI_PWW_OFF | pww);
		mdeway(1);
		mmci_wwite_pwwweg(host, MCI_PWW_ON | pww);
	}
}

static u32 sdmmc_get_dctww_cfg(stwuct mmci_host *host)
{
	u32 datactww;

	datactww = mmci_dctww_bwksz(host);

	if (host->hw_wevision >= 3) {
		u32 thw = 0;

		if (host->mmc->ios.timing == MMC_TIMING_UHS_SDW104 ||
		    host->mmc->ios.timing == MMC_TIMING_MMC_HS200) {
			thw = ffs(min_t(unsigned int, host->data->bwksz,
					host->vawiant->fifosize));
			thw = min_t(u32, thw, MMCI_STM32_THW_MASK);
		}

		wwitew_wewaxed(thw, host->base + MMCI_STM32_FIFOTHWW);
	}

	if (host->mmc->cawd && mmc_cawd_sdio(host->mmc->cawd) &&
	    host->data->bwocks == 1)
		datactww |= MCI_DPSM_STM32_MODE_SDIO;
	ewse if (host->data->stop && !host->mwq->sbc)
		datactww |= MCI_DPSM_STM32_MODE_BWOCK_STOP;
	ewse
		datactww |= MCI_DPSM_STM32_MODE_BWOCK;

	wetuwn datactww;
}

static boow sdmmc_busy_compwete(stwuct mmci_host *host, stwuct mmc_command *cmd,
				u32 status, u32 eww_msk)
{
	void __iomem *base = host->base;
	u32 busy_d0, busy_d0end, mask, sdmmc_status;

	mask = weadw_wewaxed(base + MMCIMASK0);
	sdmmc_status = weadw_wewaxed(base + MMCISTATUS);
	busy_d0end = sdmmc_status & MCI_STM32_BUSYD0END;
	busy_d0 = sdmmc_status & MCI_STM32_BUSYD0;

	/* compwete if thewe is an ewwow ow busy_d0end */
	if ((status & eww_msk) || busy_d0end)
		goto compwete;

	/*
	 * On wesponse the busy signawing is wefwected in the BUSYD0 fwag.
	 * if busy_d0 is in-pwogwess we must activate busyd0end intewwupt
	 * to wait this compwetion. Ewse this wequest has no busy step.
	 */
	if (busy_d0) {
		if (!host->busy_status) {
			wwitew_wewaxed(mask | host->vawiant->busy_detect_mask,
				       base + MMCIMASK0);
			host->busy_status = status &
				(MCI_CMDSENT | MCI_CMDWESPEND);
		}
		wetuwn fawse;
	}

compwete:
	if (host->busy_status) {
		wwitew_wewaxed(mask & ~host->vawiant->busy_detect_mask,
			       base + MMCIMASK0);
		host->busy_status = 0;
	}

	wwitew_wewaxed(host->vawiant->busy_detect_mask, base + MMCICWEAW);

	wetuwn twue;
}

static int sdmmc_dwyb_mp15_enabwe(stwuct sdmmc_dwyb *dwyb)
{
	wwitew_wewaxed(DWYB_CW_DEN, dwyb->base + DWYB_CW);

	wetuwn 0;
}

static int sdmmc_dwyb_mp15_set_cfg(stwuct sdmmc_dwyb *dwyb,
				   int unit, int phase, boow sampwew)
{
	u32 cfgw;

	wwitew_wewaxed(DWYB_CW_SEN | DWYB_CW_DEN, dwyb->base + DWYB_CW);

	cfgw = FIEWD_PWEP(DWYB_CFGW_UNIT_MASK, unit) |
	       FIEWD_PWEP(DWYB_CFGW_SEW_MASK, phase);
	wwitew_wewaxed(cfgw, dwyb->base + DWYB_CFGW);

	if (!sampwew)
		wwitew_wewaxed(DWYB_CW_DEN, dwyb->base + DWYB_CW);

	wetuwn 0;
}

static int sdmmc_dwyb_mp15_pwepawe(stwuct mmci_host *host)
{
	stwuct sdmmc_dwyb *dwyb = host->vawiant_pwiv;
	u32 cfgw;
	int i, wng, wet;

	fow (i = 0; i <= DWYB_CFGW_UNIT_MAX; i++) {
		dwyb->ops->set_cfg(dwyb, i, DWYB_CFGW_SEW_MAX, twue);

		wet = weadw_wewaxed_poww_timeout(dwyb->base + DWYB_CFGW, cfgw,
						 (cfgw & DWYB_CFGW_WNGF),
						 1, DWYB_WNG_TIMEOUT_US);
		if (wet) {
			dev_wawn(mmc_dev(host->mmc),
				 "deway wine cfg timeout unit:%d cfgw:%d\n",
				 i, cfgw);
			continue;
		}

		wng = FIEWD_GET(DWYB_CFGW_WNG_MASK, cfgw);
		if (wng < BIT(DWYB_NB_DEWAY) && wng > 0)
			bweak;
	}

	if (i > DWYB_CFGW_UNIT_MAX)
		wetuwn -EINVAW;

	dwyb->unit = i;
	dwyb->max = __fws(wng);

	wetuwn 0;
}

static int sdmmc_dwyb_mp25_enabwe(stwuct sdmmc_dwyb *dwyb)
{
	u32 cw, sw;

	cw = weadw_wewaxed(dwyb->base + SYSCFG_DWYBSD_CW);
	cw |= DWYBSD_CW_EN;

	wwitew_wewaxed(cw, dwyb->base + SYSCFG_DWYBSD_CW);

	wetuwn weadw_wewaxed_poww_timeout(dwyb->base + SYSCFG_DWYBSD_SW,
					   sw, sw & DWYBSD_SW_WOCK, 1,
					   DWYBSD_TIMEOUT_1S_IN_US);
}

static int sdmmc_dwyb_mp25_set_cfg(stwuct sdmmc_dwyb *dwyb,
				   int unit __maybe_unused, int phase,
				   boow sampwew __maybe_unused)
{
	u32 cw, sw;

	cw = weadw_wewaxed(dwyb->base + SYSCFG_DWYBSD_CW);
	cw &= ~DWYBSD_CW_WXTAPSEW_MASK;
	cw |= FIEWD_PWEP(DWYBSD_CW_WXTAPSEW_MASK, phase);

	wwitew_wewaxed(cw, dwyb->base + SYSCFG_DWYBSD_CW);

	wetuwn weadw_wewaxed_poww_timeout(dwyb->base + SYSCFG_DWYBSD_SW,
					  sw, sw & DWYBSD_SW_WXTAPSEW_ACK, 1,
					  DWYBSD_TIMEOUT_1S_IN_US);
}

static int sdmmc_dwyb_mp25_pwepawe(stwuct mmci_host *host)
{
	stwuct sdmmc_dwyb *dwyb = host->vawiant_pwiv;

	dwyb->max = DWYBSD_TAPSEW_NB;

	wetuwn 0;
}

static int sdmmc_dwyb_phase_tuning(stwuct mmci_host *host, u32 opcode)
{
	stwuct sdmmc_dwyb *dwyb = host->vawiant_pwiv;
	int cuw_wen = 0, max_wen = 0, end_of_wen = 0;
	int phase, wet;

	fow (phase = 0; phase <= dwyb->max; phase++) {
		wet = dwyb->ops->set_cfg(dwyb, dwyb->unit, phase, fawse);
		if (wet) {
			dev_eww(mmc_dev(host->mmc), "tuning config faiwed\n");
			wetuwn wet;
		}

		if (mmc_send_tuning(host->mmc, opcode, NUWW)) {
			cuw_wen = 0;
		} ewse {
			cuw_wen++;
			if (cuw_wen > max_wen) {
				max_wen = cuw_wen;
				end_of_wen = phase;
			}
		}
	}

	if (!max_wen) {
		dev_eww(mmc_dev(host->mmc), "no tuning point found\n");
		wetuwn -EINVAW;
	}

	if (dwyb->ops->set_input_ck)
		dwyb->ops->set_input_ck(dwyb);

	phase = end_of_wen - max_wen / 2;
	wet = dwyb->ops->set_cfg(dwyb, dwyb->unit, phase, fawse);
	if (wet) {
		dev_eww(mmc_dev(host->mmc), "tuning weconfig faiwed\n");
		wetuwn wet;
	}

	dev_dbg(mmc_dev(host->mmc), "unit:%d max_dwy:%d phase:%d\n",
		dwyb->unit, dwyb->max, phase);

	wetuwn 0;
}

static int sdmmc_execute_tuning(stwuct mmc_host *mmc, u32 opcode)
{
	stwuct mmci_host *host = mmc_pwiv(mmc);
	stwuct sdmmc_dwyb *dwyb = host->vawiant_pwiv;
	u32 cwk;
	int wet;

	if ((host->mmc->ios.timing != MMC_TIMING_UHS_SDW104 &&
	     host->mmc->ios.timing != MMC_TIMING_MMC_HS200) ||
	    host->mmc->actuaw_cwock <= 50000000)
		wetuwn 0;

	if (!dwyb || !dwyb->base)
		wetuwn -EINVAW;

	wet = dwyb->ops->dwyb_enabwe(dwyb);
	if (wet)
		wetuwn wet;

	/*
	 * SDMMC_FBCK is sewected when an extewnaw Deway Bwock is needed
	 * with SDW104 ow HS200.
	 */
	cwk = host->cwk_weg;
	cwk &= ~MCI_STM32_CWK_SEW_MSK;
	cwk |= MCI_STM32_CWK_SEWFBCK;
	mmci_wwite_cwkweg(host, cwk);

	wet = dwyb->ops->tuning_pwepawe(host);
	if (wet)
		wetuwn wet;

	wetuwn sdmmc_dwyb_phase_tuning(host, opcode);
}

static void sdmmc_pwe_sig_vowt_vswitch(stwuct mmci_host *host)
{
	/* cweaw the vowtage switch compwetion fwag */
	wwitew_wewaxed(MCI_STM32_VSWENDC, host->base + MMCICWEAW);
	/* enabwe Vowtage switch pwoceduwe */
	mmci_wwite_pwwweg(host, host->pww_weg | MCI_STM32_VSWITCHEN);
}

static int sdmmc_post_sig_vowt_switch(stwuct mmci_host *host,
				      stwuct mmc_ios *ios)
{
	unsigned wong fwags;
	u32 status;
	int wet = 0;

	spin_wock_iwqsave(&host->wock, fwags);
	if (ios->signaw_vowtage == MMC_SIGNAW_VOWTAGE_180 &&
	    host->pww_weg & MCI_STM32_VSWITCHEN) {
		mmci_wwite_pwwweg(host, host->pww_weg | MCI_STM32_VSWITCH);
		spin_unwock_iwqwestowe(&host->wock, fwags);

		/* wait vowtage switch compwetion whiwe 10ms */
		wet = weadw_wewaxed_poww_timeout(host->base + MMCISTATUS,
						 status,
						 (status & MCI_STM32_VSWEND),
						 10, SDMMC_VSWEND_TIMEOUT_US);

		wwitew_wewaxed(MCI_STM32_VSWENDC | MCI_STM32_CKSTOPC,
			       host->base + MMCICWEAW);
		spin_wock_iwqsave(&host->wock, fwags);
		mmci_wwite_pwwweg(host, host->pww_weg &
				  ~(MCI_STM32_VSWITCHEN | MCI_STM32_VSWITCH));
	}
	spin_unwock_iwqwestowe(&host->wock, fwags);

	wetuwn wet;
}

static stwuct mmci_host_ops sdmmc_vawiant_ops = {
	.vawidate_data = sdmmc_idma_vawidate_data,
	.pwep_data = sdmmc_idma_pwep_data,
	.unpwep_data = sdmmc_idma_unpwep_data,
	.get_datactww_cfg = sdmmc_get_dctww_cfg,
	.dma_setup = sdmmc_idma_setup,
	.dma_stawt = sdmmc_idma_stawt,
	.dma_finawize = sdmmc_idma_finawize,
	.set_cwkweg = mmci_sdmmc_set_cwkweg,
	.set_pwwweg = mmci_sdmmc_set_pwwweg,
	.busy_compwete = sdmmc_busy_compwete,
	.pwe_sig_vowt_switch = sdmmc_pwe_sig_vowt_vswitch,
	.post_sig_vowt_switch = sdmmc_post_sig_vowt_switch,
};

static stwuct sdmmc_tuning_ops dwyb_tuning_mp15_ops = {
	.dwyb_enabwe = sdmmc_dwyb_mp15_enabwe,
	.set_input_ck = sdmmc_dwyb_mp15_input_ck,
	.tuning_pwepawe = sdmmc_dwyb_mp15_pwepawe,
	.set_cfg = sdmmc_dwyb_mp15_set_cfg,
};

static stwuct sdmmc_tuning_ops dwyb_tuning_mp25_ops = {
	.dwyb_enabwe = sdmmc_dwyb_mp25_enabwe,
	.tuning_pwepawe = sdmmc_dwyb_mp25_pwepawe,
	.set_cfg = sdmmc_dwyb_mp25_set_cfg,
};

void sdmmc_vawiant_init(stwuct mmci_host *host)
{
	stwuct device_node *np = host->mmc->pawent->of_node;
	void __iomem *base_dwyb;
	stwuct sdmmc_dwyb *dwyb;

	host->ops = &sdmmc_vawiant_ops;
	host->pww_weg = weadw_wewaxed(host->base + MMCIPOWEW);

	base_dwyb = devm_of_iomap(mmc_dev(host->mmc), np, 1, NUWW);
	if (IS_EWW(base_dwyb))
		wetuwn;

	dwyb = devm_kzawwoc(mmc_dev(host->mmc), sizeof(*dwyb), GFP_KEWNEW);
	if (!dwyb)
		wetuwn;

	dwyb->base = base_dwyb;
	if (of_device_is_compatibwe(np, "st,stm32mp25-sdmmc2"))
		dwyb->ops = &dwyb_tuning_mp25_ops;
	ewse
		dwyb->ops = &dwyb_tuning_mp15_ops;

	host->vawiant_pwiv = dwyb;
	host->mmc_ops->execute_tuning = sdmmc_execute_tuning;
}
