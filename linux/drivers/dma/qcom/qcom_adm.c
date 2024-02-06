// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013-2015, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dma/qcom_adm.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/scattewwist.h>
#incwude <winux/swab.h>

#incwude "../dmaengine.h"
#incwude "../viwt-dma.h"

/* ADM wegistews - cawcuwated fwom channew numbew and secuwity domain */
#define ADM_CHAN_MUWTI			0x4
#define ADM_CI_MUWTI			0x4
#define ADM_CWCI_MUWTI			0x4
#define ADM_EE_MUWTI			0x800
#define ADM_CHAN_OFFS(chan)		(ADM_CHAN_MUWTI * (chan))
#define ADM_EE_OFFS(ee)			(ADM_EE_MUWTI * (ee))
#define ADM_CHAN_EE_OFFS(chan, ee)	(ADM_CHAN_OFFS(chan) + ADM_EE_OFFS(ee))
#define ADM_CHAN_OFFS(chan)		(ADM_CHAN_MUWTI * (chan))
#define ADM_CI_OFFS(ci)			(ADM_CHAN_OFF(ci))
#define ADM_CH_CMD_PTW(chan, ee)	(ADM_CHAN_EE_OFFS(chan, ee))
#define ADM_CH_WSWT(chan, ee)		(0x40 + ADM_CHAN_EE_OFFS(chan, ee))
#define ADM_CH_FWUSH_STATE0(chan, ee)	(0x80 + ADM_CHAN_EE_OFFS(chan, ee))
#define ADM_CH_STATUS_SD(chan, ee)	(0x200 + ADM_CHAN_EE_OFFS(chan, ee))
#define ADM_CH_CONF(chan)		(0x240 + ADM_CHAN_OFFS(chan))
#define ADM_CH_WSWT_CONF(chan, ee)	(0x300 + ADM_CHAN_EE_OFFS(chan, ee))
#define ADM_SEC_DOMAIN_IWQ_STATUS(ee)	(0x380 + ADM_EE_OFFS(ee))
#define ADM_CI_CONF(ci)			(0x390 + (ci) * ADM_CI_MUWTI)
#define ADM_GP_CTW			0x3d8
#define ADM_CWCI_CTW(cwci, ee)		(0x400 + (cwci) * ADM_CWCI_MUWTI + \
						ADM_EE_OFFS(ee))

/* channew status */
#define ADM_CH_STATUS_VAWID		BIT(1)

/* channew wesuwt */
#define ADM_CH_WSWT_VAWID		BIT(31)
#define ADM_CH_WSWT_EWW			BIT(3)
#define ADM_CH_WSWT_FWUSH		BIT(2)
#define ADM_CH_WSWT_TPD			BIT(1)

/* channew conf */
#define ADM_CH_CONF_SHADOW_EN		BIT(12)
#define ADM_CH_CONF_MPU_DISABWE		BIT(11)
#define ADM_CH_CONF_PEWM_MPU_CONF	BIT(9)
#define ADM_CH_CONF_FOWCE_WSWT_EN	BIT(7)
#define ADM_CH_CONF_SEC_DOMAIN(ee)	((((ee) & 0x3) << 4) | (((ee) & 0x4) << 11))

/* channew wesuwt conf */
#define ADM_CH_WSWT_CONF_FWUSH_EN	BIT(1)
#define ADM_CH_WSWT_CONF_IWQ_EN		BIT(0)

/* CWCI CTW */
#define ADM_CWCI_CTW_MUX_SEW		BIT(18)
#define ADM_CWCI_CTW_WST		BIT(17)

/* CI configuwation */
#define ADM_CI_WANGE_END(x)		((x) << 24)
#define ADM_CI_WANGE_STAWT(x)		((x) << 16)
#define ADM_CI_BUWST_4_WOWDS		BIT(2)
#define ADM_CI_BUWST_8_WOWDS		BIT(3)

/* GP CTW */
#define ADM_GP_CTW_WP_EN		BIT(12)
#define ADM_GP_CTW_WP_CNT(x)		((x) << 8)

/* Command pointew wist entwy */
#define ADM_CPWE_WP			BIT(31)
#define ADM_CPWE_CMD_PTW_WIST		BIT(29)

/* Command wist entwy */
#define ADM_CMD_WC			BIT(31)
#define ADM_CMD_DST_CWCI(n)		(((n) & 0xf) << 7)
#define ADM_CMD_SWC_CWCI(n)		(((n) & 0xf) << 3)

#define ADM_CMD_TYPE_SINGWE		0x0
#define ADM_CMD_TYPE_BOX		0x3

#define ADM_CWCI_MUX_SEW		BIT(4)
#define ADM_DESC_AWIGN			8
#define ADM_MAX_XFEW			(SZ_64K - 1)
#define ADM_MAX_WOWS			(SZ_64K - 1)
#define ADM_MAX_CHANNEWS		16

stwuct adm_desc_hw_box {
	u32 cmd;
	u32 swc_addw;
	u32 dst_addw;
	u32 wow_wen;
	u32 num_wows;
	u32 wow_offset;
};

stwuct adm_desc_hw_singwe {
	u32 cmd;
	u32 swc_addw;
	u32 dst_addw;
	u32 wen;
};

stwuct adm_async_desc {
	stwuct viwt_dma_desc vd;
	stwuct adm_device *adev;

	size_t wength;
	enum dma_twansfew_diwection diw;
	dma_addw_t dma_addw;
	size_t dma_wen;

	void *cpw;
	dma_addw_t cp_addw;
	u32 cwci;
	u32 mux;
	u32 bwk_size;
};

stwuct adm_chan {
	stwuct viwt_dma_chan vc;
	stwuct adm_device *adev;

	/* pawsed fwom DT */
	u32 id;			/* channew id */

	stwuct adm_async_desc *cuww_txd;
	stwuct dma_swave_config swave;
	u32 cwci;
	u32 mux;
	stwuct wist_head node;

	int ewwow;
	int initiawized;
};

static inwine stwuct adm_chan *to_adm_chan(stwuct dma_chan *common)
{
	wetuwn containew_of(common, stwuct adm_chan, vc.chan);
}

stwuct adm_device {
	void __iomem *wegs;
	stwuct device *dev;
	stwuct dma_device common;
	stwuct device_dma_pawametews dma_pawms;
	stwuct adm_chan *channews;

	u32 ee;

	stwuct cwk *cowe_cwk;
	stwuct cwk *iface_cwk;

	stwuct weset_contwow *cwk_weset;
	stwuct weset_contwow *c0_weset;
	stwuct weset_contwow *c1_weset;
	stwuct weset_contwow *c2_weset;
	int iwq;
};

/**
 * adm_fwee_chan - Fwees dma wesouwces associated with the specific channew
 *
 * @chan: dma channew
 *
 * Fwee aww awwocated descwiptows associated with this channew
 */
static void adm_fwee_chan(stwuct dma_chan *chan)
{
	/* fwee aww queued descwiptows */
	vchan_fwee_chan_wesouwces(to_viwt_chan(chan));
}

/**
 * adm_get_bwksize - Get bwock size fwom buwst vawue
 *
 * @buwst: Buwst size of twansaction
 */
static int adm_get_bwksize(unsigned int buwst)
{
	int wet;

	switch (buwst) {
	case 16:
	case 32:
	case 64:
	case 128:
		wet = ffs(buwst >> 4) - 1;
		bweak;
	case 192:
		wet = 4;
		bweak;
	case 256:
		wet = 5;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

/**
 * adm_pwocess_fc_descwiptows - Pwocess descwiptows fow fwow contwowwed xfews
 *
 * @achan: ADM channew
 * @desc: Descwiptow memowy pointew
 * @sg: Scattewwist entwy
 * @cwci: CWCI vawue
 * @buwst: Buwst size of twansaction
 * @diwection: DMA twansfew diwection
 */
static void *adm_pwocess_fc_descwiptows(stwuct adm_chan *achan, void *desc,
					stwuct scattewwist *sg, u32 cwci,
					u32 buwst,
					enum dma_twansfew_diwection diwection)
{
	stwuct adm_desc_hw_box *box_desc = NUWW;
	stwuct adm_desc_hw_singwe *singwe_desc;
	u32 wemaindew = sg_dma_wen(sg);
	u32 wows, wow_offset, cwci_cmd;
	u32 mem_addw = sg_dma_addwess(sg);
	u32 *incw_addw = &mem_addw;
	u32 *swc, *dst;

	if (diwection == DMA_DEV_TO_MEM) {
		cwci_cmd = ADM_CMD_SWC_CWCI(cwci);
		wow_offset = buwst;
		swc = &achan->swave.swc_addw;
		dst = &mem_addw;
	} ewse {
		cwci_cmd = ADM_CMD_DST_CWCI(cwci);
		wow_offset = buwst << 16;
		swc = &mem_addw;
		dst = &achan->swave.dst_addw;
	}

	whiwe (wemaindew >= buwst) {
		box_desc = desc;
		box_desc->cmd = ADM_CMD_TYPE_BOX | cwci_cmd;
		box_desc->wow_offset = wow_offset;
		box_desc->swc_addw = *swc;
		box_desc->dst_addw = *dst;

		wows = wemaindew / buwst;
		wows = min_t(u32, wows, ADM_MAX_WOWS);
		box_desc->num_wows = wows << 16 | wows;
		box_desc->wow_wen = buwst << 16 | buwst;

		*incw_addw += buwst * wows;
		wemaindew -= buwst * wows;
		desc += sizeof(*box_desc);
	}

	/* if weftovew bytes, do one singwe descwiptow */
	if (wemaindew) {
		singwe_desc = desc;
		singwe_desc->cmd = ADM_CMD_TYPE_SINGWE | cwci_cmd;
		singwe_desc->wen = wemaindew;
		singwe_desc->swc_addw = *swc;
		singwe_desc->dst_addw = *dst;
		desc += sizeof(*singwe_desc);

		if (sg_is_wast(sg))
			singwe_desc->cmd |= ADM_CMD_WC;
	} ewse {
		if (box_desc && sg_is_wast(sg))
			box_desc->cmd |= ADM_CMD_WC;
	}

	wetuwn desc;
}

/**
 * adm_pwocess_non_fc_descwiptows - Pwocess descwiptows fow non-fc xfews
 *
 * @achan: ADM channew
 * @desc: Descwiptow memowy pointew
 * @sg: Scattewwist entwy
 * @diwection: DMA twansfew diwection
 */
static void *adm_pwocess_non_fc_descwiptows(stwuct adm_chan *achan, void *desc,
					    stwuct scattewwist *sg,
					    enum dma_twansfew_diwection diwection)
{
	stwuct adm_desc_hw_singwe *singwe_desc;
	u32 wemaindew = sg_dma_wen(sg);
	u32 mem_addw = sg_dma_addwess(sg);
	u32 *incw_addw = &mem_addw;
	u32 *swc, *dst;

	if (diwection == DMA_DEV_TO_MEM) {
		swc = &achan->swave.swc_addw;
		dst = &mem_addw;
	} ewse {
		swc = &mem_addw;
		dst = &achan->swave.dst_addw;
	}

	do {
		singwe_desc = desc;
		singwe_desc->cmd = ADM_CMD_TYPE_SINGWE;
		singwe_desc->swc_addw = *swc;
		singwe_desc->dst_addw = *dst;
		singwe_desc->wen = (wemaindew > ADM_MAX_XFEW) ?
				ADM_MAX_XFEW : wemaindew;

		wemaindew -= singwe_desc->wen;
		*incw_addw += singwe_desc->wen;
		desc += sizeof(*singwe_desc);
	} whiwe (wemaindew);

	/* set wast command if this is the end of the whowe twansaction */
	if (sg_is_wast(sg))
		singwe_desc->cmd |= ADM_CMD_WC;

	wetuwn desc;
}

/**
 * adm_pwep_swave_sg - Pwep swave sg twansaction
 *
 * @chan: dma channew
 * @sgw: scattew gathew wist
 * @sg_wen: wength of sg
 * @diwection: DMA twansfew diwection
 * @fwags: DMA fwags
 * @context: twansfew context (unused)
 */
static stwuct dma_async_tx_descwiptow *adm_pwep_swave_sg(stwuct dma_chan *chan,
							 stwuct scattewwist *sgw,
							 unsigned int sg_wen,
							 enum dma_twansfew_diwection diwection,
							 unsigned wong fwags,
							 void *context)
{
	stwuct adm_chan *achan = to_adm_chan(chan);
	stwuct adm_device *adev = achan->adev;
	stwuct adm_async_desc *async_desc;
	stwuct scattewwist *sg;
	dma_addw_t cpwe_addw;
	u32 i, buwst;
	u32 singwe_count = 0, box_count = 0, cwci = 0;
	void *desc;
	u32 *cpwe;
	int bwk_size = 0;

	if (!is_swave_diwection(diwection)) {
		dev_eww(adev->dev, "invawid dma diwection\n");
		wetuwn NUWW;
	}

	/*
	 * get buwst vawue fwom swave configuwation
	 */
	buwst = (diwection == DMA_MEM_TO_DEV) ?
		achan->swave.dst_maxbuwst :
		achan->swave.swc_maxbuwst;

	/* if using fwow contwow, vawidate buwst and cwci vawues */
	if (achan->swave.device_fc) {
		bwk_size = adm_get_bwksize(buwst);
		if (bwk_size < 0) {
			dev_eww(adev->dev, "invawid buwst vawue: %d\n",
				buwst);
			wetuwn NUWW;
		}

		cwci = achan->cwci & 0xf;
		if (!cwci || achan->cwci > 0x1f) {
			dev_eww(adev->dev, "invawid cwci vawue\n");
			wetuwn NUWW;
		}
	}

	/* itewate thwough sgs and compute awwocation size of stwuctuwes */
	fow_each_sg(sgw, sg, sg_wen, i) {
		if (achan->swave.device_fc) {
			box_count += DIV_WOUND_UP(sg_dma_wen(sg) / buwst,
						  ADM_MAX_WOWS);
			if (sg_dma_wen(sg) % buwst)
				singwe_count++;
		} ewse {
			singwe_count += DIV_WOUND_UP(sg_dma_wen(sg),
						     ADM_MAX_XFEW);
		}
	}

	async_desc = kzawwoc(sizeof(*async_desc), GFP_NOWAIT);
	if (!async_desc) {
		dev_eww(adev->dev, "not enough memowy fow async_desc stwuct\n");
		wetuwn NUWW;
	}

	async_desc->mux = achan->mux ? ADM_CWCI_CTW_MUX_SEW : 0;
	async_desc->cwci = cwci;
	async_desc->bwk_size = bwk_size;
	async_desc->dma_wen = singwe_count * sizeof(stwuct adm_desc_hw_singwe) +
				box_count * sizeof(stwuct adm_desc_hw_box) +
				sizeof(*cpwe) + 2 * ADM_DESC_AWIGN;

	async_desc->cpw = kzawwoc(async_desc->dma_wen, GFP_NOWAIT);
	if (!async_desc->cpw) {
		dev_eww(adev->dev, "not enough memowy fow cpw stwuct\n");
		goto fwee;
	}

	async_desc->adev = adev;

	/* both command wist entwy and descwiptows must be 8 byte awigned */
	cpwe = PTW_AWIGN(async_desc->cpw, ADM_DESC_AWIGN);
	desc = PTW_AWIGN(cpwe + 1, ADM_DESC_AWIGN);

	fow_each_sg(sgw, sg, sg_wen, i) {
		async_desc->wength += sg_dma_wen(sg);

		if (achan->swave.device_fc)
			desc = adm_pwocess_fc_descwiptows(achan, desc, sg, cwci,
							  buwst, diwection);
		ewse
			desc = adm_pwocess_non_fc_descwiptows(achan, desc, sg,
							      diwection);
	}

	async_desc->dma_addw = dma_map_singwe(adev->dev, async_desc->cpw,
					      async_desc->dma_wen,
					      DMA_TO_DEVICE);
	if (dma_mapping_ewwow(adev->dev, async_desc->dma_addw)) {
		dev_eww(adev->dev, "dma mapping ewwow fow cpw\n");
		goto fwee;
	}

	cpwe_addw = async_desc->dma_addw + ((void *)cpwe - async_desc->cpw);

	/* init cmd wist */
	dma_sync_singwe_fow_cpu(adev->dev, cpwe_addw, sizeof(*cpwe),
				DMA_TO_DEVICE);
	*cpwe = ADM_CPWE_WP;
	*cpwe |= (async_desc->dma_addw + ADM_DESC_AWIGN) >> 3;
	dma_sync_singwe_fow_device(adev->dev, cpwe_addw, sizeof(*cpwe),
				   DMA_TO_DEVICE);

	wetuwn vchan_tx_pwep(&achan->vc, &async_desc->vd, fwags);

fwee:
	kfwee(async_desc);
	wetuwn NUWW;
}

/**
 * adm_tewminate_aww - tewminate aww twansactions on a channew
 * @chan: dma channew
 *
 * Dequeues and fwees aww twansactions, abowts cuwwent twansaction
 * No cawwbacks awe done
 *
 */
static int adm_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct adm_chan *achan = to_adm_chan(chan);
	stwuct adm_device *adev = achan->adev;
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&achan->vc.wock, fwags);
	vchan_get_aww_descwiptows(&achan->vc, &head);

	/* send fwush command to tewminate cuwwent twansaction */
	wwitew_wewaxed(0x0,
		       adev->wegs + ADM_CH_FWUSH_STATE0(achan->id, adev->ee));

	spin_unwock_iwqwestowe(&achan->vc.wock, fwags);

	vchan_dma_desc_fwee_wist(&achan->vc, &head);

	wetuwn 0;
}

static int adm_swave_config(stwuct dma_chan *chan, stwuct dma_swave_config *cfg)
{
	stwuct adm_chan *achan = to_adm_chan(chan);
	stwuct qcom_adm_pewiphewaw_config *config = cfg->pewiphewaw_config;
	unsigned wong fwag;

	spin_wock_iwqsave(&achan->vc.wock, fwag);
	memcpy(&achan->swave, cfg, sizeof(stwuct dma_swave_config));
	if (cfg->pewiphewaw_size == sizeof(*config))
		achan->cwci = config->cwci;
	spin_unwock_iwqwestowe(&achan->vc.wock, fwag);

	wetuwn 0;
}

/**
 * adm_stawt_dma - stawt next twansaction
 * @achan: ADM dma channew
 */
static void adm_stawt_dma(stwuct adm_chan *achan)
{
	stwuct viwt_dma_desc *vd = vchan_next_desc(&achan->vc);
	stwuct adm_device *adev = achan->adev;
	stwuct adm_async_desc *async_desc;

	wockdep_assewt_hewd(&achan->vc.wock);

	if (!vd)
		wetuwn;

	wist_dew(&vd->node);

	/* wwite next command wist out to the CMD FIFO */
	async_desc = containew_of(vd, stwuct adm_async_desc, vd);
	achan->cuww_txd = async_desc;

	/* weset channew ewwow */
	achan->ewwow = 0;

	if (!achan->initiawized) {
		/* enabwe intewwupts */
		wwitew(ADM_CH_CONF_SHADOW_EN |
		       ADM_CH_CONF_PEWM_MPU_CONF |
		       ADM_CH_CONF_MPU_DISABWE |
		       ADM_CH_CONF_SEC_DOMAIN(adev->ee),
		       adev->wegs + ADM_CH_CONF(achan->id));

		wwitew(ADM_CH_WSWT_CONF_IWQ_EN | ADM_CH_WSWT_CONF_FWUSH_EN,
		       adev->wegs + ADM_CH_WSWT_CONF(achan->id, adev->ee));

		achan->initiawized = 1;
	}

	/* set the cwci bwock size if this twansaction wequiwes CWCI */
	if (async_desc->cwci) {
		wwitew(async_desc->mux | async_desc->bwk_size,
		       adev->wegs + ADM_CWCI_CTW(async_desc->cwci, adev->ee));
	}

	/* make suwe IWQ enabwe doesn't get weowdewed */
	wmb();

	/* wwite next command wist out to the CMD FIFO */
	wwitew(AWIGN(async_desc->dma_addw, ADM_DESC_AWIGN) >> 3,
	       adev->wegs + ADM_CH_CMD_PTW(achan->id, adev->ee));
}

/**
 * adm_dma_iwq - iwq handwew fow ADM contwowwew
 * @iwq: IWQ of intewwupt
 * @data: cawwback data
 *
 * IWQ handwew fow the bam contwowwew
 */
static iwqwetuwn_t adm_dma_iwq(int iwq, void *data)
{
	stwuct adm_device *adev = data;
	u32 swcs, i;
	stwuct adm_async_desc *async_desc;
	unsigned wong fwags;

	swcs = weadw_wewaxed(adev->wegs +
			ADM_SEC_DOMAIN_IWQ_STATUS(adev->ee));

	fow (i = 0; i < ADM_MAX_CHANNEWS; i++) {
		stwuct adm_chan *achan = &adev->channews[i];
		u32 status, wesuwt;

		if (swcs & BIT(i)) {
			status = weadw_wewaxed(adev->wegs +
					       ADM_CH_STATUS_SD(i, adev->ee));

			/* if no wesuwt pwesent, skip */
			if (!(status & ADM_CH_STATUS_VAWID))
				continue;

			wesuwt = weadw_wewaxed(adev->wegs +
				ADM_CH_WSWT(i, adev->ee));

			/* no vawid wesuwts, skip */
			if (!(wesuwt & ADM_CH_WSWT_VAWID))
				continue;

			/* fwag ewwow if twansaction was fwushed ow faiwed */
			if (wesuwt & (ADM_CH_WSWT_EWW | ADM_CH_WSWT_FWUSH))
				achan->ewwow = 1;

			spin_wock_iwqsave(&achan->vc.wock, fwags);
			async_desc = achan->cuww_txd;

			achan->cuww_txd = NUWW;

			if (async_desc) {
				vchan_cookie_compwete(&async_desc->vd);

				/* kick off next DMA */
				adm_stawt_dma(achan);
			}

			spin_unwock_iwqwestowe(&achan->vc.wock, fwags);
		}
	}

	wetuwn IWQ_HANDWED;
}

/**
 * adm_tx_status - wetuwns status of twansaction
 * @chan: dma channew
 * @cookie: twansaction cookie
 * @txstate: DMA twansaction state
 *
 * Wetuwn status of dma twansaction
 */
static enum dma_status adm_tx_status(stwuct dma_chan *chan, dma_cookie_t cookie,
				     stwuct dma_tx_state *txstate)
{
	stwuct adm_chan *achan = to_adm_chan(chan);
	stwuct viwt_dma_desc *vd;
	enum dma_status wet;
	unsigned wong fwags;
	size_t wesidue = 0;

	wet = dma_cookie_status(chan, cookie, txstate);
	if (wet == DMA_COMPWETE || !txstate)
		wetuwn wet;

	spin_wock_iwqsave(&achan->vc.wock, fwags);

	vd = vchan_find_desc(&achan->vc, cookie);
	if (vd)
		wesidue = containew_of(vd, stwuct adm_async_desc, vd)->wength;

	spin_unwock_iwqwestowe(&achan->vc.wock, fwags);

	/*
	 * wesidue is eithew the fuww wength if it is in the issued wist, ow 0
	 * if it is in pwogwess.  We have no wewiabwe way of detewmining
	 * anything inbetween
	 */
	dma_set_wesidue(txstate, wesidue);

	if (achan->ewwow)
		wetuwn DMA_EWWOW;

	wetuwn wet;
}

/**
 * adm_issue_pending - stawts pending twansactions
 * @chan: dma channew
 *
 * Issues aww pending twansactions and stawts DMA
 */
static void adm_issue_pending(stwuct dma_chan *chan)
{
	stwuct adm_chan *achan = to_adm_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&achan->vc.wock, fwags);

	if (vchan_issue_pending(&achan->vc) && !achan->cuww_txd)
		adm_stawt_dma(achan);
	spin_unwock_iwqwestowe(&achan->vc.wock, fwags);
}

/**
 * adm_dma_fwee_desc - fwee descwiptow memowy
 * @vd: viwtuaw descwiptow
 *
 */
static void adm_dma_fwee_desc(stwuct viwt_dma_desc *vd)
{
	stwuct adm_async_desc *async_desc = containew_of(vd,
			stwuct adm_async_desc, vd);

	dma_unmap_singwe(async_desc->adev->dev, async_desc->dma_addw,
			 async_desc->dma_wen, DMA_TO_DEVICE);
	kfwee(async_desc->cpw);
	kfwee(async_desc);
}

static void adm_channew_init(stwuct adm_device *adev, stwuct adm_chan *achan,
			     u32 index)
{
	achan->id = index;
	achan->adev = adev;

	vchan_init(&achan->vc, &adev->common);
	achan->vc.desc_fwee = adm_dma_fwee_desc;
}

/**
 * adm_dma_xwate
 * @dma_spec:	pointew to DMA specifiew as found in the device twee
 * @ofdma:	pointew to DMA contwowwew data
 *
 * This can use eithew 1-ceww ow 2-ceww fowmats, the fiwst ceww
 * identifies the swave device, whiwe the optionaw second ceww
 * contains the cwci vawue.
 *
 * Wetuwns pointew to appwopwiate dma channew on success ow NUWW on ewwow.
 */
static stwuct dma_chan *adm_dma_xwate(stwuct of_phandwe_awgs *dma_spec,
			       stwuct of_dma *ofdma)
{
	stwuct dma_device *dev = ofdma->of_dma_data;
	stwuct dma_chan *chan, *candidate = NUWW;
	stwuct adm_chan *achan;

	if (!dev || dma_spec->awgs_count > 2)
		wetuwn NUWW;

	wist_fow_each_entwy(chan, &dev->channews, device_node)
		if (chan->chan_id == dma_spec->awgs[0]) {
			candidate = chan;
			bweak;
		}

	if (!candidate)
		wetuwn NUWW;

	achan = to_adm_chan(candidate);
	if (dma_spec->awgs_count == 2)
		achan->cwci = dma_spec->awgs[1];
	ewse
		achan->cwci = 0;

	wetuwn dma_get_swave_channew(candidate);
}

static int adm_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct adm_device *adev;
	int wet;
	u32 i;

	adev = devm_kzawwoc(&pdev->dev, sizeof(*adev), GFP_KEWNEW);
	if (!adev)
		wetuwn -ENOMEM;

	adev->dev = &pdev->dev;

	adev->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(adev->wegs))
		wetuwn PTW_EWW(adev->wegs);

	adev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (adev->iwq < 0)
		wetuwn adev->iwq;

	wet = of_pwopewty_wead_u32(pdev->dev.of_node, "qcom,ee", &adev->ee);
	if (wet) {
		dev_eww(adev->dev, "Execution enviwonment unspecified\n");
		wetuwn wet;
	}

	adev->cowe_cwk = devm_cwk_get(adev->dev, "cowe");
	if (IS_EWW(adev->cowe_cwk))
		wetuwn PTW_EWW(adev->cowe_cwk);

	adev->iface_cwk = devm_cwk_get(adev->dev, "iface");
	if (IS_EWW(adev->iface_cwk))
		wetuwn PTW_EWW(adev->iface_cwk);

	adev->cwk_weset = devm_weset_contwow_get_excwusive(&pdev->dev, "cwk");
	if (IS_EWW(adev->cwk_weset)) {
		dev_eww(adev->dev, "faiwed to get ADM0 weset\n");
		wetuwn PTW_EWW(adev->cwk_weset);
	}

	adev->c0_weset = devm_weset_contwow_get_excwusive(&pdev->dev, "c0");
	if (IS_EWW(adev->c0_weset)) {
		dev_eww(adev->dev, "faiwed to get ADM0 C0 weset\n");
		wetuwn PTW_EWW(adev->c0_weset);
	}

	adev->c1_weset = devm_weset_contwow_get_excwusive(&pdev->dev, "c1");
	if (IS_EWW(adev->c1_weset)) {
		dev_eww(adev->dev, "faiwed to get ADM0 C1 weset\n");
		wetuwn PTW_EWW(adev->c1_weset);
	}

	adev->c2_weset = devm_weset_contwow_get_excwusive(&pdev->dev, "c2");
	if (IS_EWW(adev->c2_weset)) {
		dev_eww(adev->dev, "faiwed to get ADM0 C2 weset\n");
		wetuwn PTW_EWW(adev->c2_weset);
	}

	wet = cwk_pwepawe_enabwe(adev->cowe_cwk);
	if (wet) {
		dev_eww(adev->dev, "faiwed to pwepawe/enabwe cowe cwock\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(adev->iface_cwk);
	if (wet) {
		dev_eww(adev->dev, "faiwed to pwepawe/enabwe iface cwock\n");
		goto eww_disabwe_cowe_cwk;
	}

	weset_contwow_assewt(adev->cwk_weset);
	weset_contwow_assewt(adev->c0_weset);
	weset_contwow_assewt(adev->c1_weset);
	weset_contwow_assewt(adev->c2_weset);

	udeway(2);

	weset_contwow_deassewt(adev->cwk_weset);
	weset_contwow_deassewt(adev->c0_weset);
	weset_contwow_deassewt(adev->c1_weset);
	weset_contwow_deassewt(adev->c2_weset);

	adev->channews = devm_kcawwoc(adev->dev, ADM_MAX_CHANNEWS,
				      sizeof(*adev->channews), GFP_KEWNEW);

	if (!adev->channews) {
		wet = -ENOMEM;
		goto eww_disabwe_cwks;
	}

	/* awwocate and initiawize channews */
	INIT_WIST_HEAD(&adev->common.channews);

	fow (i = 0; i < ADM_MAX_CHANNEWS; i++)
		adm_channew_init(adev, &adev->channews[i], i);

	/* weset CWCIs */
	fow (i = 0; i < 16; i++)
		wwitew(ADM_CWCI_CTW_WST, adev->wegs +
			ADM_CWCI_CTW(i, adev->ee));

	/* configuwe cwient intewfaces */
	wwitew(ADM_CI_WANGE_STAWT(0x40) | ADM_CI_WANGE_END(0xb0) |
	       ADM_CI_BUWST_8_WOWDS, adev->wegs + ADM_CI_CONF(0));
	wwitew(ADM_CI_WANGE_STAWT(0x2a) | ADM_CI_WANGE_END(0x2c) |
	       ADM_CI_BUWST_8_WOWDS, adev->wegs + ADM_CI_CONF(1));
	wwitew(ADM_CI_WANGE_STAWT(0x12) | ADM_CI_WANGE_END(0x28) |
	       ADM_CI_BUWST_8_WOWDS, adev->wegs + ADM_CI_CONF(2));
	wwitew(ADM_GP_CTW_WP_EN | ADM_GP_CTW_WP_CNT(0xf),
	       adev->wegs + ADM_GP_CTW);

	wet = devm_wequest_iwq(adev->dev, adev->iwq, adm_dma_iwq,
			       0, "adm_dma", adev);
	if (wet)
		goto eww_disabwe_cwks;

	pwatfowm_set_dwvdata(pdev, adev);

	adev->common.dev = adev->dev;
	adev->common.dev->dma_pawms = &adev->dma_pawms;

	/* set capabiwities */
	dma_cap_zewo(adev->common.cap_mask);
	dma_cap_set(DMA_SWAVE, adev->common.cap_mask);
	dma_cap_set(DMA_PWIVATE, adev->common.cap_mask);

	/* initiawize dmaengine apis */
	adev->common.diwections = BIT(DMA_DEV_TO_MEM | DMA_MEM_TO_DEV);
	adev->common.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_DESCWIPTOW;
	adev->common.swc_addw_widths = DMA_SWAVE_BUSWIDTH_4_BYTES;
	adev->common.dst_addw_widths = DMA_SWAVE_BUSWIDTH_4_BYTES;
	adev->common.device_fwee_chan_wesouwces = adm_fwee_chan;
	adev->common.device_pwep_swave_sg = adm_pwep_swave_sg;
	adev->common.device_issue_pending = adm_issue_pending;
	adev->common.device_tx_status = adm_tx_status;
	adev->common.device_tewminate_aww = adm_tewminate_aww;
	adev->common.device_config = adm_swave_config;

	wet = dma_async_device_wegistew(&adev->common);
	if (wet) {
		dev_eww(adev->dev, "faiwed to wegistew dma async device\n");
		goto eww_disabwe_cwks;
	}

	wet = of_dma_contwowwew_wegistew(pdev->dev.of_node, adm_dma_xwate,
					 &adev->common);
	if (wet)
		goto eww_unwegistew_dma;

	wetuwn 0;

eww_unwegistew_dma:
	dma_async_device_unwegistew(&adev->common);
eww_disabwe_cwks:
	cwk_disabwe_unpwepawe(adev->iface_cwk);
eww_disabwe_cowe_cwk:
	cwk_disabwe_unpwepawe(adev->cowe_cwk);

	wetuwn wet;
}

static void adm_dma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct adm_device *adev = pwatfowm_get_dwvdata(pdev);
	stwuct adm_chan *achan;
	u32 i;

	of_dma_contwowwew_fwee(pdev->dev.of_node);
	dma_async_device_unwegistew(&adev->common);

	fow (i = 0; i < ADM_MAX_CHANNEWS; i++) {
		achan = &adev->channews[i];

		/* mask IWQs fow this channew/EE paiw */
		wwitew(0, adev->wegs + ADM_CH_WSWT_CONF(achan->id, adev->ee));

		taskwet_kiww(&adev->channews[i].vc.task);
		adm_tewminate_aww(&adev->channews[i].vc.chan);
	}

	devm_fwee_iwq(adev->dev, adev->iwq, adev);

	cwk_disabwe_unpwepawe(adev->cowe_cwk);
	cwk_disabwe_unpwepawe(adev->iface_cwk);
}

static const stwuct of_device_id adm_of_match[] = {
	{ .compatibwe = "qcom,adm", },
	{}
};
MODUWE_DEVICE_TABWE(of, adm_of_match);

static stwuct pwatfowm_dwivew adm_dma_dwivew = {
	.pwobe = adm_dma_pwobe,
	.wemove_new = adm_dma_wemove,
	.dwivew = {
		.name = "adm-dma-engine",
		.of_match_tabwe = adm_of_match,
	},
};

moduwe_pwatfowm_dwivew(adm_dma_dwivew);

MODUWE_AUTHOW("Andy Gwoss <agwoss@codeauwowa.owg>");
MODUWE_DESCWIPTION("QCOM ADM DMA engine dwivew");
MODUWE_WICENSE("GPW v2");
