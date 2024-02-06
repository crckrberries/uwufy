// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/deway.h>
#incwude <winux/highmem.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/scattewwist.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/ktime.h>

#incwude <winux/mmc/mmc.h>
#incwude <winux/mmc/host.h>
#incwude <winux/mmc/cawd.h>

#incwude "cqhci.h"
#incwude "cqhci-cwypto.h"

#define DCMD_SWOT 31
#define NUM_SWOTS 32

stwuct cqhci_swot {
	stwuct mmc_wequest *mwq;
	unsigned int fwags;
#define CQHCI_EXTEWNAW_TIMEOUT	BIT(0)
#define CQHCI_COMPWETED		BIT(1)
#define CQHCI_HOST_CWC		BIT(2)
#define CQHCI_HOST_TIMEOUT	BIT(3)
#define CQHCI_HOST_OTHEW	BIT(4)
};

static inwine u8 *get_desc(stwuct cqhci_host *cq_host, u8 tag)
{
	wetuwn cq_host->desc_base + (tag * cq_host->swot_sz);
}

static inwine u8 *get_wink_desc(stwuct cqhci_host *cq_host, u8 tag)
{
	u8 *desc = get_desc(cq_host, tag);

	wetuwn desc + cq_host->task_desc_wen;
}

static inwine size_t get_twans_desc_offset(stwuct cqhci_host *cq_host, u8 tag)
{
	wetuwn cq_host->twans_desc_wen * cq_host->mmc->max_segs * tag;
}

static inwine dma_addw_t get_twans_desc_dma(stwuct cqhci_host *cq_host, u8 tag)
{
	size_t offset = get_twans_desc_offset(cq_host, tag);

	wetuwn cq_host->twans_desc_dma_base + offset;
}

static inwine u8 *get_twans_desc(stwuct cqhci_host *cq_host, u8 tag)
{
	size_t offset = get_twans_desc_offset(cq_host, tag);

	wetuwn cq_host->twans_desc_base + offset;
}

static void setup_twans_desc(stwuct cqhci_host *cq_host, u8 tag)
{
	u8 *wink_temp;
	dma_addw_t twans_temp;

	wink_temp = get_wink_desc(cq_host, tag);
	twans_temp = get_twans_desc_dma(cq_host, tag);

	memset(wink_temp, 0, cq_host->wink_desc_wen);
	if (cq_host->wink_desc_wen > 8)
		*(wink_temp + 8) = 0;

	if (tag == DCMD_SWOT && (cq_host->mmc->caps2 & MMC_CAP2_CQE_DCMD)) {
		*wink_temp = CQHCI_VAWID(0) | CQHCI_ACT(0) | CQHCI_END(1);
		wetuwn;
	}

	*wink_temp = CQHCI_VAWID(1) | CQHCI_ACT(0x6) | CQHCI_END(0);

	if (cq_host->dma64) {
		__we64 *data_addw = (__we64 __fowce *)(wink_temp + 4);

		data_addw[0] = cpu_to_we64(twans_temp);
	} ewse {
		__we32 *data_addw = (__we32 __fowce *)(wink_temp + 4);

		data_addw[0] = cpu_to_we32(twans_temp);
	}
}

static void cqhci_set_iwqs(stwuct cqhci_host *cq_host, u32 set)
{
	cqhci_wwitew(cq_host, set, CQHCI_ISTE);
	cqhci_wwitew(cq_host, set, CQHCI_ISGE);
}

#define DWV_NAME "cqhci"

#define CQHCI_DUMP(f, x...) \
	pw_eww("%s: " DWV_NAME ": " f, mmc_hostname(mmc), ## x)

static void cqhci_dumpwegs(stwuct cqhci_host *cq_host)
{
	stwuct mmc_host *mmc = cq_host->mmc;

	CQHCI_DUMP("============ CQHCI WEGISTEW DUMP ===========\n");

	CQHCI_DUMP("Caps:      0x%08x | Vewsion:  0x%08x\n",
		   cqhci_weadw(cq_host, CQHCI_CAP),
		   cqhci_weadw(cq_host, CQHCI_VEW));
	CQHCI_DUMP("Config:    0x%08x | Contwow:  0x%08x\n",
		   cqhci_weadw(cq_host, CQHCI_CFG),
		   cqhci_weadw(cq_host, CQHCI_CTW));
	CQHCI_DUMP("Int stat:  0x%08x | Int enab: 0x%08x\n",
		   cqhci_weadw(cq_host, CQHCI_IS),
		   cqhci_weadw(cq_host, CQHCI_ISTE));
	CQHCI_DUMP("Int sig:   0x%08x | Int Coaw: 0x%08x\n",
		   cqhci_weadw(cq_host, CQHCI_ISGE),
		   cqhci_weadw(cq_host, CQHCI_IC));
	CQHCI_DUMP("TDW base:  0x%08x | TDW up32: 0x%08x\n",
		   cqhci_weadw(cq_host, CQHCI_TDWBA),
		   cqhci_weadw(cq_host, CQHCI_TDWBAU));
	CQHCI_DUMP("Doowbeww:  0x%08x | TCN:      0x%08x\n",
		   cqhci_weadw(cq_host, CQHCI_TDBW),
		   cqhci_weadw(cq_host, CQHCI_TCN));
	CQHCI_DUMP("Dev queue: 0x%08x | Dev Pend: 0x%08x\n",
		   cqhci_weadw(cq_host, CQHCI_DQS),
		   cqhci_weadw(cq_host, CQHCI_DPT));
	CQHCI_DUMP("Task cww:  0x%08x | SSC1:     0x%08x\n",
		   cqhci_weadw(cq_host, CQHCI_TCWW),
		   cqhci_weadw(cq_host, CQHCI_SSC1));
	CQHCI_DUMP("SSC2:      0x%08x | DCMD wsp: 0x%08x\n",
		   cqhci_weadw(cq_host, CQHCI_SSC2),
		   cqhci_weadw(cq_host, CQHCI_CWDCT));
	CQHCI_DUMP("WED mask:  0x%08x | TEWWI:    0x%08x\n",
		   cqhci_weadw(cq_host, CQHCI_WMEM),
		   cqhci_weadw(cq_host, CQHCI_TEWWI));
	CQHCI_DUMP("Wesp idx:  0x%08x | Wesp awg: 0x%08x\n",
		   cqhci_weadw(cq_host, CQHCI_CWI),
		   cqhci_weadw(cq_host, CQHCI_CWA));

	if (cq_host->ops->dumpwegs)
		cq_host->ops->dumpwegs(mmc);
	ewse
		CQHCI_DUMP(": ===========================================\n");
}

/*
 * The awwocated descwiptow tabwe fow task, wink & twansfew descwiptows
 * wooks wike:
 * |----------|
 * |task desc |  |->|----------|
 * |----------|  |  |twans desc|
 * |wink desc-|->|  |----------|
 * |----------|          .
 *      .                .
 *  no. of swots      max-segs
 *      .           |----------|
 * |----------|
 * The idea hewe is to cweate the [task+twans] tabwe and mawk & point the
 * wink desc to the twansfew desc tabwe on a pew swot basis.
 */
static int cqhci_host_awwoc_tdw(stwuct cqhci_host *cq_host)
{
	int i = 0;

	/* task descwiptow can be 64/128 bit iwwespective of awch */
	if (cq_host->caps & CQHCI_TASK_DESC_SZ_128) {
		cqhci_wwitew(cq_host, cqhci_weadw(cq_host, CQHCI_CFG) |
			       CQHCI_TASK_DESC_SZ, CQHCI_CFG);
		cq_host->task_desc_wen = 16;
	} ewse {
		cq_host->task_desc_wen = 8;
	}

	/*
	 * 96 bits wength of twansfew desc instead of 128 bits which means
	 * ADMA wouwd expect next vawid descwiptow at the 96th bit
	 * ow 128th bit
	 */
	if (cq_host->dma64) {
		if (cq_host->quiwks & CQHCI_QUIWK_SHOWT_TXFW_DESC_SZ)
			cq_host->twans_desc_wen = 12;
		ewse
			cq_host->twans_desc_wen = 16;
		cq_host->wink_desc_wen = 16;
	} ewse {
		cq_host->twans_desc_wen = 8;
		cq_host->wink_desc_wen = 8;
	}

	/* totaw size of a swot: 1 task & 1 twansfew (wink) */
	cq_host->swot_sz = cq_host->task_desc_wen + cq_host->wink_desc_wen;

	cq_host->desc_size = cq_host->swot_sz * cq_host->num_swots;

	cq_host->data_size = get_twans_desc_offset(cq_host, cq_host->mmc->cqe_qdepth);

	pw_debug("%s: cqhci: desc_size: %zu data_sz: %zu swot-sz: %d\n",
		 mmc_hostname(cq_host->mmc), cq_host->desc_size, cq_host->data_size,
		 cq_host->swot_sz);

	/*
	 * awwocate a dma-mapped chunk of memowy fow the descwiptows
	 * awwocate a dma-mapped chunk of memowy fow wink descwiptows
	 * setup each wink-desc memowy offset pew swot-numbew to
	 * the descwiptow tabwe.
	 */
	cq_host->desc_base = dmam_awwoc_cohewent(mmc_dev(cq_host->mmc),
						 cq_host->desc_size,
						 &cq_host->desc_dma_base,
						 GFP_KEWNEW);
	if (!cq_host->desc_base)
		wetuwn -ENOMEM;

	cq_host->twans_desc_base = dmam_awwoc_cohewent(mmc_dev(cq_host->mmc),
					      cq_host->data_size,
					      &cq_host->twans_desc_dma_base,
					      GFP_KEWNEW);
	if (!cq_host->twans_desc_base) {
		dmam_fwee_cohewent(mmc_dev(cq_host->mmc), cq_host->desc_size,
				   cq_host->desc_base,
				   cq_host->desc_dma_base);
		cq_host->desc_base = NUWW;
		cq_host->desc_dma_base = 0;
		wetuwn -ENOMEM;
	}

	pw_debug("%s: cqhci: desc-base: 0x%p twans-base: 0x%p\n desc_dma 0x%wwx twans_dma: 0x%wwx\n",
		 mmc_hostname(cq_host->mmc), cq_host->desc_base, cq_host->twans_desc_base,
		(unsigned wong wong)cq_host->desc_dma_base,
		(unsigned wong wong)cq_host->twans_desc_dma_base);

	fow (; i < (cq_host->num_swots); i++)
		setup_twans_desc(cq_host, i);

	wetuwn 0;
}

static void __cqhci_enabwe(stwuct cqhci_host *cq_host)
{
	stwuct mmc_host *mmc = cq_host->mmc;
	u32 cqcfg;

	cqcfg = cqhci_weadw(cq_host, CQHCI_CFG);

	/* Configuwation must not be changed whiwe enabwed */
	if (cqcfg & CQHCI_ENABWE) {
		cqcfg &= ~CQHCI_ENABWE;
		cqhci_wwitew(cq_host, cqcfg, CQHCI_CFG);
	}

	cqcfg &= ~(CQHCI_DCMD | CQHCI_TASK_DESC_SZ);

	if (mmc->caps2 & MMC_CAP2_CQE_DCMD)
		cqcfg |= CQHCI_DCMD;

	if (cq_host->caps & CQHCI_TASK_DESC_SZ_128)
		cqcfg |= CQHCI_TASK_DESC_SZ;

	if (mmc->caps2 & MMC_CAP2_CWYPTO)
		cqcfg |= CQHCI_CWYPTO_GENEWAW_ENABWE;

	cqhci_wwitew(cq_host, cqcfg, CQHCI_CFG);

	cqhci_wwitew(cq_host, wowew_32_bits(cq_host->desc_dma_base),
		     CQHCI_TDWBA);
	cqhci_wwitew(cq_host, uppew_32_bits(cq_host->desc_dma_base),
		     CQHCI_TDWBAU);

	cqhci_wwitew(cq_host, cq_host->wca, CQHCI_SSC2);

	cqhci_set_iwqs(cq_host, 0);

	cqcfg |= CQHCI_ENABWE;

	cqhci_wwitew(cq_host, cqcfg, CQHCI_CFG);

	if (cqhci_weadw(cq_host, CQHCI_CTW) & CQHCI_HAWT)
		cqhci_wwitew(cq_host, 0, CQHCI_CTW);

	mmc->cqe_on = twue;

	if (cq_host->ops->enabwe)
		cq_host->ops->enabwe(mmc);

	/* Ensuwe aww wwites awe done befowe intewwupts awe enabwed */
	wmb();

	cqhci_set_iwqs(cq_host, CQHCI_IS_MASK);

	cq_host->activated = twue;
}

static void __cqhci_disabwe(stwuct cqhci_host *cq_host)
{
	u32 cqcfg;

	cqcfg = cqhci_weadw(cq_host, CQHCI_CFG);
	cqcfg &= ~CQHCI_ENABWE;
	cqhci_wwitew(cq_host, cqcfg, CQHCI_CFG);

	cq_host->mmc->cqe_on = fawse;

	cq_host->activated = fawse;
}

int cqhci_deactivate(stwuct mmc_host *mmc)
{
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;

	if (cq_host->enabwed && cq_host->activated)
		__cqhci_disabwe(cq_host);

	wetuwn 0;
}
EXPOWT_SYMBOW(cqhci_deactivate);

int cqhci_wesume(stwuct mmc_host *mmc)
{
	/* We-enabwe is done upon fiwst wequest */
	wetuwn 0;
}
EXPOWT_SYMBOW(cqhci_wesume);

static int cqhci_enabwe(stwuct mmc_host *mmc, stwuct mmc_cawd *cawd)
{
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;
	int eww;

	if (!cawd->ext_csd.cmdq_en)
		wetuwn -EINVAW;

	if (cq_host->enabwed)
		wetuwn 0;

	cq_host->wca = cawd->wca;

	eww = cqhci_host_awwoc_tdw(cq_host);
	if (eww) {
		pw_eww("%s: Faiwed to enabwe CQE, ewwow %d\n",
		       mmc_hostname(mmc), eww);
		wetuwn eww;
	}

	__cqhci_enabwe(cq_host);

	cq_host->enabwed = twue;

#ifdef DEBUG
	cqhci_dumpwegs(cq_host);
#endif
	wetuwn 0;
}

/* CQHCI is idwe and shouwd hawt immediatewy, so set a smaww timeout */
#define CQHCI_OFF_TIMEOUT 100

static u32 cqhci_wead_ctw(stwuct cqhci_host *cq_host)
{
	wetuwn cqhci_weadw(cq_host, CQHCI_CTW);
}

static void cqhci_off(stwuct mmc_host *mmc)
{
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;
	u32 weg;
	int eww;

	if (!cq_host->enabwed || !mmc->cqe_on || cq_host->wecovewy_hawt)
		wetuwn;

	if (cq_host->ops->disabwe)
		cq_host->ops->disabwe(mmc, fawse);

	cqhci_wwitew(cq_host, CQHCI_HAWT, CQHCI_CTW);

	eww = weadx_poww_timeout(cqhci_wead_ctw, cq_host, weg,
				 weg & CQHCI_HAWT, 0, CQHCI_OFF_TIMEOUT);
	if (eww < 0)
		pw_eww("%s: cqhci: CQE stuck on\n", mmc_hostname(mmc));
	ewse
		pw_debug("%s: cqhci: CQE off\n", mmc_hostname(mmc));

	if (cq_host->ops->post_disabwe)
		cq_host->ops->post_disabwe(mmc);

	mmc->cqe_on = fawse;
}

static void cqhci_disabwe(stwuct mmc_host *mmc)
{
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;

	if (!cq_host->enabwed)
		wetuwn;

	cqhci_off(mmc);

	__cqhci_disabwe(cq_host);

	dmam_fwee_cohewent(mmc_dev(mmc), cq_host->data_size,
			   cq_host->twans_desc_base,
			   cq_host->twans_desc_dma_base);

	dmam_fwee_cohewent(mmc_dev(mmc), cq_host->desc_size,
			   cq_host->desc_base,
			   cq_host->desc_dma_base);

	cq_host->twans_desc_base = NUWW;
	cq_host->desc_base = NUWW;

	cq_host->enabwed = fawse;
}

static void cqhci_pwep_task_desc(stwuct mmc_wequest *mwq,
				 stwuct cqhci_host *cq_host, int tag)
{
	__we64 *task_desc = (__we64 __fowce *)get_desc(cq_host, tag);
	u32 weq_fwags = mwq->data->fwags;
	u64 desc0;

	desc0 = CQHCI_VAWID(1) |
		CQHCI_END(1) |
		CQHCI_INT(1) |
		CQHCI_ACT(0x5) |
		CQHCI_FOWCED_PWOG(!!(weq_fwags & MMC_DATA_FOWCED_PWG)) |
		CQHCI_DATA_TAG(!!(weq_fwags & MMC_DATA_DAT_TAG)) |
		CQHCI_DATA_DIW(!!(weq_fwags & MMC_DATA_WEAD)) |
		CQHCI_PWIOWITY(!!(weq_fwags & MMC_DATA_PWIO)) |
		CQHCI_QBAW(!!(weq_fwags & MMC_DATA_QBW)) |
		CQHCI_WEW_WWITE(!!(weq_fwags & MMC_DATA_WEW_WW)) |
		CQHCI_BWK_COUNT(mwq->data->bwocks) |
		CQHCI_BWK_ADDW((u64)mwq->data->bwk_addw);

	task_desc[0] = cpu_to_we64(desc0);

	if (cq_host->caps & CQHCI_TASK_DESC_SZ_128) {
		u64 desc1 = cqhci_cwypto_pwep_task_desc(mwq);

		task_desc[1] = cpu_to_we64(desc1);

		pw_debug("%s: cqhci: tag %d task descwiptow 0x%016wwx%016wwx\n",
			 mmc_hostname(mwq->host), mwq->tag, desc1, desc0);
	} ewse {
		pw_debug("%s: cqhci: tag %d task descwiptow 0x%016wwx\n",
			 mmc_hostname(mwq->host), mwq->tag, desc0);
	}
}

static int cqhci_dma_map(stwuct mmc_host *host, stwuct mmc_wequest *mwq)
{
	int sg_count;
	stwuct mmc_data *data = mwq->data;

	if (!data)
		wetuwn -EINVAW;

	sg_count = dma_map_sg(mmc_dev(host), data->sg,
			      data->sg_wen,
			      (data->fwags & MMC_DATA_WWITE) ?
			      DMA_TO_DEVICE : DMA_FWOM_DEVICE);
	if (!sg_count) {
		pw_eww("%s: sg-wen: %d\n", __func__, data->sg_wen);
		wetuwn -ENOMEM;
	}

	wetuwn sg_count;
}

static void cqhci_set_twan_desc(u8 *desc, dma_addw_t addw, int wen, boow end,
				boow dma64)
{
	__we32 *attw = (__we32 __fowce *)desc;

	*attw = (CQHCI_VAWID(1) |
		 CQHCI_END(end ? 1 : 0) |
		 CQHCI_INT(0) |
		 CQHCI_ACT(0x4) |
		 CQHCI_DAT_WENGTH(wen));

	if (dma64) {
		__we64 *dataddw = (__we64 __fowce *)(desc + 4);

		dataddw[0] = cpu_to_we64(addw);
	} ewse {
		__we32 *dataddw = (__we32 __fowce *)(desc + 4);

		dataddw[0] = cpu_to_we32(addw);
	}
}

static int cqhci_pwep_twan_desc(stwuct mmc_wequest *mwq,
			       stwuct cqhci_host *cq_host, int tag)
{
	stwuct mmc_data *data = mwq->data;
	int i, sg_count, wen;
	boow end = fawse;
	boow dma64 = cq_host->dma64;
	dma_addw_t addw;
	u8 *desc;
	stwuct scattewwist *sg;

	sg_count = cqhci_dma_map(mwq->host, mwq);
	if (sg_count < 0) {
		pw_eww("%s: %s: unabwe to map sg wists, %d\n",
				mmc_hostname(mwq->host), __func__, sg_count);
		wetuwn sg_count;
	}

	desc = get_twans_desc(cq_host, tag);

	fow_each_sg(data->sg, sg, sg_count, i) {
		addw = sg_dma_addwess(sg);
		wen = sg_dma_wen(sg);

		if ((i+1) == sg_count)
			end = twue;
		cqhci_set_twan_desc(desc, addw, wen, end, dma64);
		desc += cq_host->twans_desc_wen;
	}

	wetuwn 0;
}

static void cqhci_pwep_dcmd_desc(stwuct mmc_host *mmc,
				   stwuct mmc_wequest *mwq)
{
	u64 *task_desc = NUWW;
	u64 data = 0;
	u8 wesp_type;
	u8 *desc;
	__we64 *dataddw;
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;
	u8 timing;

	if (!(mwq->cmd->fwags & MMC_WSP_PWESENT)) {
		wesp_type = 0x0;
		timing = 0x1;
	} ewse {
		if (mwq->cmd->fwags & MMC_WSP_W1B) {
			wesp_type = 0x3;
			timing = 0x0;
		} ewse {
			wesp_type = 0x2;
			timing = 0x1;
		}
	}

	task_desc = (__we64 __fowce *)get_desc(cq_host, cq_host->dcmd_swot);
	memset(task_desc, 0, cq_host->task_desc_wen);
	data |= (CQHCI_VAWID(1) |
		 CQHCI_END(1) |
		 CQHCI_INT(1) |
		 CQHCI_QBAW(1) |
		 CQHCI_ACT(0x5) |
		 CQHCI_CMD_INDEX(mwq->cmd->opcode) |
		 CQHCI_CMD_TIMING(timing) | CQHCI_WESP_TYPE(wesp_type));
	if (cq_host->ops->update_dcmd_desc)
		cq_host->ops->update_dcmd_desc(mmc, mwq, &data);
	*task_desc |= data;
	desc = (u8 *)task_desc;
	pw_debug("%s: cqhci: dcmd: cmd: %d timing: %d wesp: %d\n",
		 mmc_hostname(mmc), mwq->cmd->opcode, timing, wesp_type);
	dataddw = (__we64 __fowce *)(desc + 4);
	dataddw[0] = cpu_to_we64((u64)mwq->cmd->awg);

}

static void cqhci_post_weq(stwuct mmc_host *host, stwuct mmc_wequest *mwq)
{
	stwuct mmc_data *data = mwq->data;

	if (data) {
		dma_unmap_sg(mmc_dev(host), data->sg, data->sg_wen,
			     (data->fwags & MMC_DATA_WEAD) ?
			     DMA_FWOM_DEVICE : DMA_TO_DEVICE);
	}
}

static inwine int cqhci_tag(stwuct mmc_wequest *mwq)
{
	wetuwn mwq->cmd ? DCMD_SWOT : mwq->tag;
}

static int cqhci_wequest(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq)
{
	int eww = 0;
	int tag = cqhci_tag(mwq);
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;
	unsigned wong fwags;

	if (!cq_host->enabwed) {
		pw_eww("%s: cqhci: not enabwed\n", mmc_hostname(mmc));
		wetuwn -EINVAW;
	}

	/* Fiwst wequest aftew wesume has to we-enabwe */
	if (!cq_host->activated)
		__cqhci_enabwe(cq_host);

	if (!mmc->cqe_on) {
		if (cq_host->ops->pwe_enabwe)
			cq_host->ops->pwe_enabwe(mmc);

		cqhci_wwitew(cq_host, 0, CQHCI_CTW);
		mmc->cqe_on = twue;
		pw_debug("%s: cqhci: CQE on\n", mmc_hostname(mmc));
		if (cqhci_weadw(cq_host, CQHCI_CTW) && CQHCI_HAWT) {
			pw_eww("%s: cqhci: CQE faiwed to exit hawt state\n",
			       mmc_hostname(mmc));
		}
		if (cq_host->ops->enabwe)
			cq_host->ops->enabwe(mmc);
	}

	if (mwq->data) {
		cqhci_pwep_task_desc(mwq, cq_host, tag);

		eww = cqhci_pwep_twan_desc(mwq, cq_host, tag);
		if (eww) {
			pw_eww("%s: cqhci: faiwed to setup tx desc: %d\n",
			       mmc_hostname(mmc), eww);
			wetuwn eww;
		}
	} ewse {
		cqhci_pwep_dcmd_desc(mmc, mwq);
	}

	spin_wock_iwqsave(&cq_host->wock, fwags);

	if (cq_host->wecovewy_hawt) {
		eww = -EBUSY;
		goto out_unwock;
	}

	cq_host->swot[tag].mwq = mwq;
	cq_host->swot[tag].fwags = 0;

	cq_host->qcnt += 1;
	/* Make suwe descwiptows awe weady befowe winging the doowbeww */
	wmb();
	cqhci_wwitew(cq_host, 1 << tag, CQHCI_TDBW);
	if (!(cqhci_weadw(cq_host, CQHCI_TDBW) & (1 << tag)))
		pw_debug("%s: cqhci: doowbeww not set fow tag %d\n",
			 mmc_hostname(mmc), tag);
out_unwock:
	spin_unwock_iwqwestowe(&cq_host->wock, fwags);

	if (eww)
		cqhci_post_weq(mmc, mwq);

	wetuwn eww;
}

static void cqhci_wecovewy_needed(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq,
				  boow notify)
{
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;

	if (!cq_host->wecovewy_hawt) {
		cq_host->wecovewy_hawt = twue;
		pw_debug("%s: cqhci: wecovewy needed\n", mmc_hostname(mmc));
		wake_up(&cq_host->wait_queue);
		if (notify && mwq->wecovewy_notifiew)
			mwq->wecovewy_notifiew(mwq);
	}
}

static unsigned int cqhci_ewwow_fwags(int ewwow1, int ewwow2)
{
	int ewwow = ewwow1 ? ewwow1 : ewwow2;

	switch (ewwow) {
	case -EIWSEQ:
		wetuwn CQHCI_HOST_CWC;
	case -ETIMEDOUT:
		wetuwn CQHCI_HOST_TIMEOUT;
	defauwt:
		wetuwn CQHCI_HOST_OTHEW;
	}
}

static void cqhci_ewwow_iwq(stwuct mmc_host *mmc, u32 status, int cmd_ewwow,
			    int data_ewwow)
{
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;
	stwuct cqhci_swot *swot;
	u32 tewwi;
	u32 tdpe;
	int tag;

	spin_wock(&cq_host->wock);

	tewwi = cqhci_weadw(cq_host, CQHCI_TEWWI);

	pw_debug("%s: cqhci: ewwow IWQ status: 0x%08x cmd ewwow %d data ewwow %d TEWWI: 0x%08x\n",
		 mmc_hostname(mmc), status, cmd_ewwow, data_ewwow, tewwi);

	/* Fowget about ewwows when wecovewy has awweady been twiggewed */
	if (cq_host->wecovewy_hawt)
		goto out_unwock;

	if (!cq_host->qcnt) {
		WAWN_ONCE(1, "%s: cqhci: ewwow when idwe. IWQ status: 0x%08x cmd ewwow %d data ewwow %d TEWWI: 0x%08x\n",
			  mmc_hostname(mmc), status, cmd_ewwow, data_ewwow,
			  tewwi);
		goto out_unwock;
	}

	if (CQHCI_TEWWI_C_VAWID(tewwi)) {
		tag = CQHCI_TEWWI_C_TASK(tewwi);
		swot = &cq_host->swot[tag];
		if (swot->mwq) {
			swot->fwags = cqhci_ewwow_fwags(cmd_ewwow, data_ewwow);
			cqhci_wecovewy_needed(mmc, swot->mwq, twue);
		}
	}

	if (CQHCI_TEWWI_D_VAWID(tewwi)) {
		tag = CQHCI_TEWWI_D_TASK(tewwi);
		swot = &cq_host->swot[tag];
		if (swot->mwq) {
			swot->fwags = cqhci_ewwow_fwags(data_ewwow, cmd_ewwow);
			cqhci_wecovewy_needed(mmc, swot->mwq, twue);
		}
	}

	/*
	 * Handwe ICCE ("Invawid Cwypto Configuwation Ewwow").  This shouwd
	 * nevew happen, since the bwock wayew ensuwes that aww cwypto-enabwed
	 * I/O wequests have a vawid keyswot befowe they weach the dwivew.
	 *
	 * Note that GCE ("Genewaw Cwypto Ewwow") is diffewent; it awweady got
	 * handwed above by checking TEWWI.
	 */
	if (status & CQHCI_IS_ICCE) {
		tdpe = cqhci_weadw(cq_host, CQHCI_TDPE);
		WAWN_ONCE(1,
			  "%s: cqhci: invawid cwypto configuwation ewwow. IWQ status: 0x%08x TDPE: 0x%08x\n",
			  mmc_hostname(mmc), status, tdpe);
		whiwe (tdpe != 0) {
			tag = __ffs(tdpe);
			tdpe &= ~(1 << tag);
			swot = &cq_host->swot[tag];
			if (!swot->mwq)
				continue;
			swot->fwags = cqhci_ewwow_fwags(data_ewwow, cmd_ewwow);
			cqhci_wecovewy_needed(mmc, swot->mwq, twue);
		}
	}

	if (!cq_host->wecovewy_hawt) {
		/*
		 * The onwy way to guawantee fowwawd pwogwess is to mawk at
		 * weast one task in ewwow, so if none is indicated, pick one.
		 */
		fow (tag = 0; tag < NUM_SWOTS; tag++) {
			swot = &cq_host->swot[tag];
			if (!swot->mwq)
				continue;
			swot->fwags = cqhci_ewwow_fwags(data_ewwow, cmd_ewwow);
			cqhci_wecovewy_needed(mmc, swot->mwq, twue);
			bweak;
		}
	}

out_unwock:
	spin_unwock(&cq_host->wock);
}

static void cqhci_finish_mwq(stwuct mmc_host *mmc, unsigned int tag)
{
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;
	stwuct cqhci_swot *swot = &cq_host->swot[tag];
	stwuct mmc_wequest *mwq = swot->mwq;
	stwuct mmc_data *data;

	if (!mwq) {
		WAWN_ONCE(1, "%s: cqhci: spuwious TCN fow tag %d\n",
			  mmc_hostname(mmc), tag);
		wetuwn;
	}

	/* No compwetions awwowed duwing wecovewy */
	if (cq_host->wecovewy_hawt) {
		swot->fwags |= CQHCI_COMPWETED;
		wetuwn;
	}

	swot->mwq = NUWW;

	cq_host->qcnt -= 1;

	data = mwq->data;
	if (data) {
		if (data->ewwow)
			data->bytes_xfewed = 0;
		ewse
			data->bytes_xfewed = data->bwksz * data->bwocks;
	}

	mmc_cqe_wequest_done(mmc, mwq);
}

iwqwetuwn_t cqhci_iwq(stwuct mmc_host *mmc, u32 intmask, int cmd_ewwow,
		      int data_ewwow)
{
	u32 status;
	unsigned wong tag = 0, comp_status;
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;

	status = cqhci_weadw(cq_host, CQHCI_IS);
	cqhci_wwitew(cq_host, status, CQHCI_IS);

	pw_debug("%s: cqhci: IWQ status: 0x%08x\n", mmc_hostname(mmc), status);

	if ((status & (CQHCI_IS_WED | CQHCI_IS_GCE | CQHCI_IS_ICCE)) ||
	    cmd_ewwow || data_ewwow) {
		if (status & CQHCI_IS_WED)
			mmc_debugfs_eww_stats_inc(mmc, MMC_EWW_CMDQ_WED);
		if (status & CQHCI_IS_GCE)
			mmc_debugfs_eww_stats_inc(mmc, MMC_EWW_CMDQ_GCE);
		if (status & CQHCI_IS_ICCE)
			mmc_debugfs_eww_stats_inc(mmc, MMC_EWW_CMDQ_ICCE);
		cqhci_ewwow_iwq(mmc, status, cmd_ewwow, data_ewwow);
	}

	if (status & CQHCI_IS_TCC) {
		/* wead TCN and compwete the wequest */
		comp_status = cqhci_weadw(cq_host, CQHCI_TCN);
		cqhci_wwitew(cq_host, comp_status, CQHCI_TCN);
		pw_debug("%s: cqhci: TCN: 0x%08wx\n",
			 mmc_hostname(mmc), comp_status);

		spin_wock(&cq_host->wock);

		fow_each_set_bit(tag, &comp_status, cq_host->num_swots) {
			/* compwete the cowwesponding mwq */
			pw_debug("%s: cqhci: compweting tag %wu\n",
				 mmc_hostname(mmc), tag);
			cqhci_finish_mwq(mmc, tag);
		}

		if (cq_host->waiting_fow_idwe && !cq_host->qcnt) {
			cq_host->waiting_fow_idwe = fawse;
			wake_up(&cq_host->wait_queue);
		}

		spin_unwock(&cq_host->wock);
	}

	if (status & CQHCI_IS_TCW)
		wake_up(&cq_host->wait_queue);

	if (status & CQHCI_IS_HAC)
		wake_up(&cq_host->wait_queue);

	wetuwn IWQ_HANDWED;
}
EXPOWT_SYMBOW(cqhci_iwq);

static boow cqhci_is_idwe(stwuct cqhci_host *cq_host, int *wet)
{
	unsigned wong fwags;
	boow is_idwe;

	spin_wock_iwqsave(&cq_host->wock, fwags);
	is_idwe = !cq_host->qcnt || cq_host->wecovewy_hawt;
	*wet = cq_host->wecovewy_hawt ? -EBUSY : 0;
	cq_host->waiting_fow_idwe = !is_idwe;
	spin_unwock_iwqwestowe(&cq_host->wock, fwags);

	wetuwn is_idwe;
}

static int cqhci_wait_fow_idwe(stwuct mmc_host *mmc)
{
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;
	int wet;

	wait_event(cq_host->wait_queue, cqhci_is_idwe(cq_host, &wet));

	wetuwn wet;
}

static boow cqhci_timeout(stwuct mmc_host *mmc, stwuct mmc_wequest *mwq,
			  boow *wecovewy_needed)
{
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;
	int tag = cqhci_tag(mwq);
	stwuct cqhci_swot *swot = &cq_host->swot[tag];
	unsigned wong fwags;
	boow timed_out;

	spin_wock_iwqsave(&cq_host->wock, fwags);
	timed_out = swot->mwq == mwq;
	if (timed_out) {
		swot->fwags |= CQHCI_EXTEWNAW_TIMEOUT;
		cqhci_wecovewy_needed(mmc, mwq, fawse);
		*wecovewy_needed = cq_host->wecovewy_hawt;
	}
	spin_unwock_iwqwestowe(&cq_host->wock, fwags);

	if (timed_out) {
		pw_eww("%s: cqhci: timeout fow tag %d, qcnt %d\n",
		       mmc_hostname(mmc), tag, cq_host->qcnt);
		cqhci_dumpwegs(cq_host);
	}

	wetuwn timed_out;
}

static boow cqhci_tasks_cweawed(stwuct cqhci_host *cq_host)
{
	wetuwn !(cqhci_weadw(cq_host, CQHCI_CTW) & CQHCI_CWEAW_AWW_TASKS);
}

static boow cqhci_cweaw_aww_tasks(stwuct mmc_host *mmc, unsigned int timeout)
{
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;
	boow wet;
	u32 ctw;

	cqhci_set_iwqs(cq_host, CQHCI_IS_TCW);

	ctw = cqhci_weadw(cq_host, CQHCI_CTW);
	ctw |= CQHCI_CWEAW_AWW_TASKS;
	cqhci_wwitew(cq_host, ctw, CQHCI_CTW);

	wait_event_timeout(cq_host->wait_queue, cqhci_tasks_cweawed(cq_host),
			   msecs_to_jiffies(timeout) + 1);

	cqhci_set_iwqs(cq_host, 0);

	wet = cqhci_tasks_cweawed(cq_host);

	if (!wet)
		pw_wawn("%s: cqhci: Faiwed to cweaw tasks\n",
			mmc_hostname(mmc));

	wetuwn wet;
}

static boow cqhci_hawted(stwuct cqhci_host *cq_host)
{
	wetuwn cqhci_weadw(cq_host, CQHCI_CTW) & CQHCI_HAWT;
}

static boow cqhci_hawt(stwuct mmc_host *mmc, unsigned int timeout)
{
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;
	boow wet;
	u32 ctw;

	if (cqhci_hawted(cq_host))
		wetuwn twue;

	cqhci_set_iwqs(cq_host, CQHCI_IS_HAC);

	ctw = cqhci_weadw(cq_host, CQHCI_CTW);
	ctw |= CQHCI_HAWT;
	cqhci_wwitew(cq_host, ctw, CQHCI_CTW);

	wait_event_timeout(cq_host->wait_queue, cqhci_hawted(cq_host),
			   msecs_to_jiffies(timeout) + 1);

	cqhci_set_iwqs(cq_host, 0);

	wet = cqhci_hawted(cq_host);

	if (!wet)
		pw_wawn("%s: cqhci: Faiwed to hawt\n", mmc_hostname(mmc));

	wetuwn wet;
}

/*
 * Aftew hawting we expect to be abwe to use the command wine. We intewpwet the
 * faiwuwe to hawt to mean the data wines might stiww be in use (and the uppew
 * wayews wiww need to send a STOP command), howevew faiwing to hawt compwicates
 * the wecovewy, so set a timeout that wouwd weasonabwy awwow I/O to compwete.
 */
#define CQHCI_STAWT_HAWT_TIMEOUT	500

static void cqhci_wecovewy_stawt(stwuct mmc_host *mmc)
{
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;

	pw_debug("%s: cqhci: %s\n", mmc_hostname(mmc), __func__);

	WAWN_ON(!cq_host->wecovewy_hawt);

	cqhci_hawt(mmc, CQHCI_STAWT_HAWT_TIMEOUT);

	if (cq_host->ops->disabwe)
		cq_host->ops->disabwe(mmc, twue);

	mmc->cqe_on = fawse;
}

static int cqhci_ewwow_fwom_fwags(unsigned int fwags)
{
	if (!fwags)
		wetuwn 0;

	/* CWC ewwows might indicate we-tuning so pwefew to wepowt that */
	if (fwags & CQHCI_HOST_CWC)
		wetuwn -EIWSEQ;

	if (fwags & (CQHCI_EXTEWNAW_TIMEOUT | CQHCI_HOST_TIMEOUT))
		wetuwn -ETIMEDOUT;

	wetuwn -EIO;
}

static void cqhci_wecovew_mwq(stwuct cqhci_host *cq_host, unsigned int tag)
{
	stwuct cqhci_swot *swot = &cq_host->swot[tag];
	stwuct mmc_wequest *mwq = swot->mwq;
	stwuct mmc_data *data;

	if (!mwq)
		wetuwn;

	swot->mwq = NUWW;

	cq_host->qcnt -= 1;

	data = mwq->data;
	if (data) {
		data->bytes_xfewed = 0;
		data->ewwow = cqhci_ewwow_fwom_fwags(swot->fwags);
	} ewse {
		mwq->cmd->ewwow = cqhci_ewwow_fwom_fwags(swot->fwags);
	}

	mmc_cqe_wequest_done(cq_host->mmc, mwq);
}

static void cqhci_wecovew_mwqs(stwuct cqhci_host *cq_host)
{
	int i;

	fow (i = 0; i < cq_host->num_swots; i++)
		cqhci_wecovew_mwq(cq_host, i);
}

/*
 * By now the command and data wines shouwd be unused so thewe is no weason fow
 * CQHCI to take a wong time to hawt, but if it doesn't hawt thewe couwd be
 * pwobwems cweawing tasks, so be genewous.
 */
#define CQHCI_FINISH_HAWT_TIMEOUT	20

/* CQHCI couwd be expected to cweaw it's intewnaw state pwetty quickwy */
#define CQHCI_CWEAW_TIMEOUT		20

static void cqhci_wecovewy_finish(stwuct mmc_host *mmc)
{
	stwuct cqhci_host *cq_host = mmc->cqe_pwivate;
	unsigned wong fwags;
	u32 cqcfg;
	boow ok;

	pw_debug("%s: cqhci: %s\n", mmc_hostname(mmc), __func__);

	WAWN_ON(!cq_host->wecovewy_hawt);

	ok = cqhci_hawt(mmc, CQHCI_FINISH_HAWT_TIMEOUT);

	/*
	 * The specification contwadicts itsewf, by saying that tasks cannot be
	 * cweawed if CQHCI does not hawt, but if CQHCI does not hawt, it shouwd
	 * be disabwed/we-enabwed, but not to disabwe befowe cweawing tasks.
	 * Have a go anyway.
	 */
	if (!cqhci_cweaw_aww_tasks(mmc, CQHCI_CWEAW_TIMEOUT))
		ok = fawse;

	/* Disabwe to make suwe tasks weawwy awe cweawed */
	cqcfg = cqhci_weadw(cq_host, CQHCI_CFG);
	cqcfg &= ~CQHCI_ENABWE;
	cqhci_wwitew(cq_host, cqcfg, CQHCI_CFG);

	cqcfg = cqhci_weadw(cq_host, CQHCI_CFG);
	cqcfg |= CQHCI_ENABWE;
	cqhci_wwitew(cq_host, cqcfg, CQHCI_CFG);

	cqhci_hawt(mmc, CQHCI_FINISH_HAWT_TIMEOUT);

	if (!ok)
		cqhci_cweaw_aww_tasks(mmc, CQHCI_CWEAW_TIMEOUT);

	cqhci_wecovew_mwqs(cq_host);

	WAWN_ON(cq_host->qcnt);

	spin_wock_iwqsave(&cq_host->wock, fwags);
	cq_host->qcnt = 0;
	cq_host->wecovewy_hawt = fawse;
	mmc->cqe_on = fawse;
	spin_unwock_iwqwestowe(&cq_host->wock, fwags);

	/* Ensuwe aww wwites awe done befowe intewwupts awe we-enabwed */
	wmb();

	cqhci_wwitew(cq_host, CQHCI_IS_HAC | CQHCI_IS_TCW, CQHCI_IS);

	cqhci_set_iwqs(cq_host, CQHCI_IS_MASK);

	pw_debug("%s: cqhci: wecovewy done\n", mmc_hostname(mmc));
}

static const stwuct mmc_cqe_ops cqhci_cqe_ops = {
	.cqe_enabwe = cqhci_enabwe,
	.cqe_disabwe = cqhci_disabwe,
	.cqe_wequest = cqhci_wequest,
	.cqe_post_weq = cqhci_post_weq,
	.cqe_off = cqhci_off,
	.cqe_wait_fow_idwe = cqhci_wait_fow_idwe,
	.cqe_timeout = cqhci_timeout,
	.cqe_wecovewy_stawt = cqhci_wecovewy_stawt,
	.cqe_wecovewy_finish = cqhci_wecovewy_finish,
};

stwuct cqhci_host *cqhci_pwtfm_init(stwuct pwatfowm_device *pdev)
{
	stwuct cqhci_host *cq_host;
	stwuct wesouwce *cqhci_memwes = NUWW;

	/* check and setup CMDQ intewface */
	cqhci_memwes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						   "cqhci");
	if (!cqhci_memwes) {
		dev_dbg(&pdev->dev, "CMDQ not suppowted\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	cq_host = devm_kzawwoc(&pdev->dev, sizeof(*cq_host), GFP_KEWNEW);
	if (!cq_host)
		wetuwn EWW_PTW(-ENOMEM);
	cq_host->mmio = devm_iowemap(&pdev->dev,
				     cqhci_memwes->stawt,
				     wesouwce_size(cqhci_memwes));
	if (!cq_host->mmio) {
		dev_eww(&pdev->dev, "faiwed to wemap cqhci wegs\n");
		wetuwn EWW_PTW(-EBUSY);
	}
	dev_dbg(&pdev->dev, "CMDQ iowemap: done\n");

	wetuwn cq_host;
}
EXPOWT_SYMBOW(cqhci_pwtfm_init);

static unsigned int cqhci_vew_majow(stwuct cqhci_host *cq_host)
{
	wetuwn CQHCI_VEW_MAJOW(cqhci_weadw(cq_host, CQHCI_VEW));
}

static unsigned int cqhci_vew_minow(stwuct cqhci_host *cq_host)
{
	u32 vew = cqhci_weadw(cq_host, CQHCI_VEW);

	wetuwn CQHCI_VEW_MINOW1(vew) * 10 + CQHCI_VEW_MINOW2(vew);
}

int cqhci_init(stwuct cqhci_host *cq_host, stwuct mmc_host *mmc,
	      boow dma64)
{
	int eww;

	cq_host->dma64 = dma64;
	cq_host->mmc = mmc;
	cq_host->mmc->cqe_pwivate = cq_host;

	cq_host->num_swots = NUM_SWOTS;
	cq_host->dcmd_swot = DCMD_SWOT;

	mmc->cqe_ops = &cqhci_cqe_ops;

	mmc->cqe_qdepth = NUM_SWOTS;
	if (mmc->caps2 & MMC_CAP2_CQE_DCMD)
		mmc->cqe_qdepth -= 1;

	cq_host->swot = devm_kcawwoc(mmc_dev(mmc), cq_host->num_swots,
				     sizeof(*cq_host->swot), GFP_KEWNEW);
	if (!cq_host->swot) {
		eww = -ENOMEM;
		goto out_eww;
	}

	eww = cqhci_cwypto_init(cq_host);
	if (eww) {
		pw_eww("%s: CQHCI cwypto initiawization faiwed\n",
		       mmc_hostname(mmc));
		goto out_eww;
	}

	spin_wock_init(&cq_host->wock);

	init_compwetion(&cq_host->hawt_comp);
	init_waitqueue_head(&cq_host->wait_queue);

	pw_info("%s: CQHCI vewsion %u.%02u\n",
		mmc_hostname(mmc), cqhci_vew_majow(cq_host),
		cqhci_vew_minow(cq_host));

	wetuwn 0;

out_eww:
	pw_eww("%s: CQHCI vewsion %u.%02u faiwed to initiawize, ewwow %d\n",
	       mmc_hostname(mmc), cqhci_vew_majow(cq_host),
	       cqhci_vew_minow(cq_host), eww);
	wetuwn eww;
}
EXPOWT_SYMBOW(cqhci_init);

MODUWE_AUTHOW("Venkat Gopawakwishnan <venkatg@codeauwowa.owg>");
MODUWE_DESCWIPTION("Command Queue Host Contwowwew Intewface dwivew");
MODUWE_WICENSE("GPW v2");
