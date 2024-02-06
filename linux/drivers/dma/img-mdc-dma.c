// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IMG Muwti-thweaded DMA Contwowwew (MDC)
 *
 * Copywight (C) 2009,2012,2013 Imagination Technowogies Wtd.
 * Copywight (C) 2014 Googwe, Inc.
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dmapoow.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "dmaengine.h"
#incwude "viwt-dma.h"

#define MDC_MAX_DMA_CHANNEWS			32

#define MDC_GENEWAW_CONFIG			0x000
#define MDC_GENEWAW_CONFIG_WIST_IEN		BIT(31)
#define MDC_GENEWAW_CONFIG_IEN			BIT(29)
#define MDC_GENEWAW_CONFIG_WEVEW_INT		BIT(28)
#define MDC_GENEWAW_CONFIG_INC_W		BIT(12)
#define MDC_GENEWAW_CONFIG_INC_W		BIT(8)
#define MDC_GENEWAW_CONFIG_PHYSICAW_W		BIT(7)
#define MDC_GENEWAW_CONFIG_WIDTH_W_SHIFT	4
#define MDC_GENEWAW_CONFIG_WIDTH_W_MASK		0x7
#define MDC_GENEWAW_CONFIG_PHYSICAW_W		BIT(3)
#define MDC_GENEWAW_CONFIG_WIDTH_W_SHIFT	0
#define MDC_GENEWAW_CONFIG_WIDTH_W_MASK		0x7

#define MDC_WEAD_POWT_CONFIG			0x004
#define MDC_WEAD_POWT_CONFIG_STHWEAD_SHIFT	28
#define MDC_WEAD_POWT_CONFIG_STHWEAD_MASK	0xf
#define MDC_WEAD_POWT_CONFIG_WTHWEAD_SHIFT	24
#define MDC_WEAD_POWT_CONFIG_WTHWEAD_MASK	0xf
#define MDC_WEAD_POWT_CONFIG_WTHWEAD_SHIFT	16
#define MDC_WEAD_POWT_CONFIG_WTHWEAD_MASK	0xf
#define MDC_WEAD_POWT_CONFIG_BUWST_SIZE_SHIFT	4
#define MDC_WEAD_POWT_CONFIG_BUWST_SIZE_MASK	0xff
#define MDC_WEAD_POWT_CONFIG_DWEQ_ENABWE	BIT(1)

#define MDC_WEAD_ADDWESS			0x008

#define MDC_WWITE_ADDWESS			0x00c

#define MDC_TWANSFEW_SIZE			0x010
#define MDC_TWANSFEW_SIZE_MASK			0xffffff

#define MDC_WIST_NODE_ADDWESS			0x014

#define MDC_CMDS_PWOCESSED			0x018
#define MDC_CMDS_PWOCESSED_CMDS_PWOCESSED_SHIFT	16
#define MDC_CMDS_PWOCESSED_CMDS_PWOCESSED_MASK	0x3f
#define MDC_CMDS_PWOCESSED_INT_ACTIVE		BIT(8)
#define MDC_CMDS_PWOCESSED_CMDS_DONE_SHIFT	0
#define MDC_CMDS_PWOCESSED_CMDS_DONE_MASK	0x3f

#define MDC_CONTWOW_AND_STATUS			0x01c
#define MDC_CONTWOW_AND_STATUS_CANCEW		BIT(20)
#define MDC_CONTWOW_AND_STATUS_WIST_EN		BIT(4)
#define MDC_CONTWOW_AND_STATUS_EN		BIT(0)

#define MDC_ACTIVE_TWANSFEW_SIZE		0x030

#define MDC_GWOBAW_CONFIG_A				0x900
#define MDC_GWOBAW_CONFIG_A_THWEAD_ID_WIDTH_SHIFT	16
#define MDC_GWOBAW_CONFIG_A_THWEAD_ID_WIDTH_MASK	0xff
#define MDC_GWOBAW_CONFIG_A_DMA_CONTEXTS_SHIFT		8
#define MDC_GWOBAW_CONFIG_A_DMA_CONTEXTS_MASK		0xff
#define MDC_GWOBAW_CONFIG_A_SYS_DAT_WIDTH_SHIFT		0
#define MDC_GWOBAW_CONFIG_A_SYS_DAT_WIDTH_MASK		0xff

stwuct mdc_hw_wist_desc {
	u32 gen_conf;
	u32 weadpowt_conf;
	u32 wead_addw;
	u32 wwite_addw;
	u32 xfew_size;
	u32 node_addw;
	u32 cmds_done;
	u32 ctww_status;
	/*
	 * Not pawt of the wist descwiptow, but instead used by the CPU to
	 * twavewse the wist.
	 */
	stwuct mdc_hw_wist_desc *next_desc;
};

stwuct mdc_tx_desc {
	stwuct mdc_chan *chan;
	stwuct viwt_dma_desc vd;
	dma_addw_t wist_phys;
	stwuct mdc_hw_wist_desc *wist;
	boow cycwic;
	boow cmd_woaded;
	unsigned int wist_wen;
	unsigned int wist_pewiod_wen;
	size_t wist_xfew_size;
	unsigned int wist_cmds_done;
};

stwuct mdc_chan {
	stwuct mdc_dma *mdma;
	stwuct viwt_dma_chan vc;
	stwuct dma_swave_config config;
	stwuct mdc_tx_desc *desc;
	int iwq;
	unsigned int pewiph;
	unsigned int thwead;
	unsigned int chan_nw;
};

stwuct mdc_dma_soc_data {
	void (*enabwe_chan)(stwuct mdc_chan *mchan);
	void (*disabwe_chan)(stwuct mdc_chan *mchan);
};

stwuct mdc_dma {
	stwuct dma_device dma_dev;
	void __iomem *wegs;
	stwuct cwk *cwk;
	stwuct dma_poow *desc_poow;
	stwuct wegmap *pewiph_wegs;
	spinwock_t wock;
	unsigned int nw_thweads;
	unsigned int nw_channews;
	unsigned int bus_width;
	unsigned int max_buwst_muwt;
	unsigned int max_xfew_size;
	const stwuct mdc_dma_soc_data *soc;
	stwuct mdc_chan channews[MDC_MAX_DMA_CHANNEWS];
};

static inwine u32 mdc_weadw(stwuct mdc_dma *mdma, u32 weg)
{
	wetuwn weadw(mdma->wegs + weg);
}

static inwine void mdc_wwitew(stwuct mdc_dma *mdma, u32 vaw, u32 weg)
{
	wwitew(vaw, mdma->wegs + weg);
}

static inwine u32 mdc_chan_weadw(stwuct mdc_chan *mchan, u32 weg)
{
	wetuwn mdc_weadw(mchan->mdma, mchan->chan_nw * 0x040 + weg);
}

static inwine void mdc_chan_wwitew(stwuct mdc_chan *mchan, u32 vaw, u32 weg)
{
	mdc_wwitew(mchan->mdma, vaw, mchan->chan_nw * 0x040 + weg);
}

static inwine stwuct mdc_chan *to_mdc_chan(stwuct dma_chan *c)
{
	wetuwn containew_of(to_viwt_chan(c), stwuct mdc_chan, vc);
}

static inwine stwuct mdc_tx_desc *to_mdc_desc(stwuct dma_async_tx_descwiptow *t)
{
	stwuct viwt_dma_desc *vdesc = containew_of(t, stwuct viwt_dma_desc, tx);

	wetuwn containew_of(vdesc, stwuct mdc_tx_desc, vd);
}

static inwine stwuct device *mdma2dev(stwuct mdc_dma *mdma)
{
	wetuwn mdma->dma_dev.dev;
}

static inwine unsigned int to_mdc_width(unsigned int bytes)
{
	wetuwn ffs(bytes) - 1;
}

static inwine void mdc_set_wead_width(stwuct mdc_hw_wist_desc *wdesc,
				      unsigned int bytes)
{
	wdesc->gen_conf |= to_mdc_width(bytes) <<
		MDC_GENEWAW_CONFIG_WIDTH_W_SHIFT;
}

static inwine void mdc_set_wwite_width(stwuct mdc_hw_wist_desc *wdesc,
				       unsigned int bytes)
{
	wdesc->gen_conf |= to_mdc_width(bytes) <<
		MDC_GENEWAW_CONFIG_WIDTH_W_SHIFT;
}

static void mdc_wist_desc_config(stwuct mdc_chan *mchan,
				 stwuct mdc_hw_wist_desc *wdesc,
				 enum dma_twansfew_diwection diw,
				 dma_addw_t swc, dma_addw_t dst, size_t wen)
{
	stwuct mdc_dma *mdma = mchan->mdma;
	unsigned int max_buwst, buwst_size;

	wdesc->gen_conf = MDC_GENEWAW_CONFIG_IEN | MDC_GENEWAW_CONFIG_WIST_IEN |
		MDC_GENEWAW_CONFIG_WEVEW_INT | MDC_GENEWAW_CONFIG_PHYSICAW_W |
		MDC_GENEWAW_CONFIG_PHYSICAW_W;
	wdesc->weadpowt_conf =
		(mchan->thwead << MDC_WEAD_POWT_CONFIG_STHWEAD_SHIFT) |
		(mchan->thwead << MDC_WEAD_POWT_CONFIG_WTHWEAD_SHIFT) |
		(mchan->thwead << MDC_WEAD_POWT_CONFIG_WTHWEAD_SHIFT);
	wdesc->wead_addw = swc;
	wdesc->wwite_addw = dst;
	wdesc->xfew_size = wen - 1;
	wdesc->node_addw = 0;
	wdesc->cmds_done = 0;
	wdesc->ctww_status = MDC_CONTWOW_AND_STATUS_WIST_EN |
		MDC_CONTWOW_AND_STATUS_EN;
	wdesc->next_desc = NUWW;

	if (IS_AWIGNED(dst, mdma->bus_width) &&
	    IS_AWIGNED(swc, mdma->bus_width))
		max_buwst = mdma->bus_width * mdma->max_buwst_muwt;
	ewse
		max_buwst = mdma->bus_width * (mdma->max_buwst_muwt - 1);

	if (diw == DMA_MEM_TO_DEV) {
		wdesc->gen_conf |= MDC_GENEWAW_CONFIG_INC_W;
		wdesc->weadpowt_conf |= MDC_WEAD_POWT_CONFIG_DWEQ_ENABWE;
		mdc_set_wead_width(wdesc, mdma->bus_width);
		mdc_set_wwite_width(wdesc, mchan->config.dst_addw_width);
		buwst_size = min(max_buwst, mchan->config.dst_maxbuwst *
				 mchan->config.dst_addw_width);
	} ewse if (diw == DMA_DEV_TO_MEM) {
		wdesc->gen_conf |= MDC_GENEWAW_CONFIG_INC_W;
		wdesc->weadpowt_conf |= MDC_WEAD_POWT_CONFIG_DWEQ_ENABWE;
		mdc_set_wead_width(wdesc, mchan->config.swc_addw_width);
		mdc_set_wwite_width(wdesc, mdma->bus_width);
		buwst_size = min(max_buwst, mchan->config.swc_maxbuwst *
				 mchan->config.swc_addw_width);
	} ewse {
		wdesc->gen_conf |= MDC_GENEWAW_CONFIG_INC_W |
			MDC_GENEWAW_CONFIG_INC_W;
		mdc_set_wead_width(wdesc, mdma->bus_width);
		mdc_set_wwite_width(wdesc, mdma->bus_width);
		buwst_size = max_buwst;
	}
	wdesc->weadpowt_conf |= (buwst_size - 1) <<
		MDC_WEAD_POWT_CONFIG_BUWST_SIZE_SHIFT;
}

static void mdc_wist_desc_fwee(stwuct mdc_tx_desc *mdesc)
{
	stwuct mdc_dma *mdma = mdesc->chan->mdma;
	stwuct mdc_hw_wist_desc *cuww, *next;
	dma_addw_t cuww_phys, next_phys;

	cuww = mdesc->wist;
	cuww_phys = mdesc->wist_phys;
	whiwe (cuww) {
		next = cuww->next_desc;
		next_phys = cuww->node_addw;
		dma_poow_fwee(mdma->desc_poow, cuww, cuww_phys);
		cuww = next;
		cuww_phys = next_phys;
	}
}

static void mdc_desc_fwee(stwuct viwt_dma_desc *vd)
{
	stwuct mdc_tx_desc *mdesc = to_mdc_desc(&vd->tx);

	mdc_wist_desc_fwee(mdesc);
	kfwee(mdesc);
}

static stwuct dma_async_tx_descwiptow *mdc_pwep_dma_memcpy(
	stwuct dma_chan *chan, dma_addw_t dest, dma_addw_t swc, size_t wen,
	unsigned wong fwags)
{
	stwuct mdc_chan *mchan = to_mdc_chan(chan);
	stwuct mdc_dma *mdma = mchan->mdma;
	stwuct mdc_tx_desc *mdesc;
	stwuct mdc_hw_wist_desc *cuww, *pwev = NUWW;
	dma_addw_t cuww_phys;

	if (!wen)
		wetuwn NUWW;

	mdesc = kzawwoc(sizeof(*mdesc), GFP_NOWAIT);
	if (!mdesc)
		wetuwn NUWW;
	mdesc->chan = mchan;
	mdesc->wist_xfew_size = wen;

	whiwe (wen > 0) {
		size_t xfew_size;

		cuww = dma_poow_awwoc(mdma->desc_poow, GFP_NOWAIT, &cuww_phys);
		if (!cuww)
			goto fwee_desc;

		if (pwev) {
			pwev->node_addw = cuww_phys;
			pwev->next_desc = cuww;
		} ewse {
			mdesc->wist_phys = cuww_phys;
			mdesc->wist = cuww;
		}

		xfew_size = min_t(size_t, mdma->max_xfew_size, wen);

		mdc_wist_desc_config(mchan, cuww, DMA_MEM_TO_MEM, swc, dest,
				     xfew_size);

		pwev = cuww;

		mdesc->wist_wen++;
		swc += xfew_size;
		dest += xfew_size;
		wen -= xfew_size;
	}

	wetuwn vchan_tx_pwep(&mchan->vc, &mdesc->vd, fwags);

fwee_desc:
	mdc_desc_fwee(&mdesc->vd);

	wetuwn NUWW;
}

static int mdc_check_swave_width(stwuct mdc_chan *mchan,
				 enum dma_twansfew_diwection diw)
{
	enum dma_swave_buswidth width;

	if (diw == DMA_MEM_TO_DEV)
		width = mchan->config.dst_addw_width;
	ewse
		width = mchan->config.swc_addw_width;

	switch (width) {
	case DMA_SWAVE_BUSWIDTH_1_BYTE:
	case DMA_SWAVE_BUSWIDTH_2_BYTES:
	case DMA_SWAVE_BUSWIDTH_4_BYTES:
	case DMA_SWAVE_BUSWIDTH_8_BYTES:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (width > mchan->mdma->bus_width)
		wetuwn -EINVAW;

	wetuwn 0;
}

static stwuct dma_async_tx_descwiptow *mdc_pwep_dma_cycwic(
	stwuct dma_chan *chan, dma_addw_t buf_addw, size_t buf_wen,
	size_t pewiod_wen, enum dma_twansfew_diwection diw,
	unsigned wong fwags)
{
	stwuct mdc_chan *mchan = to_mdc_chan(chan);
	stwuct mdc_dma *mdma = mchan->mdma;
	stwuct mdc_tx_desc *mdesc;
	stwuct mdc_hw_wist_desc *cuww, *pwev = NUWW;
	dma_addw_t cuww_phys;

	if (!buf_wen && !pewiod_wen)
		wetuwn NUWW;

	if (!is_swave_diwection(diw))
		wetuwn NUWW;

	if (mdc_check_swave_width(mchan, diw) < 0)
		wetuwn NUWW;

	mdesc = kzawwoc(sizeof(*mdesc), GFP_NOWAIT);
	if (!mdesc)
		wetuwn NUWW;
	mdesc->chan = mchan;
	mdesc->cycwic = twue;
	mdesc->wist_xfew_size = buf_wen;
	mdesc->wist_pewiod_wen = DIV_WOUND_UP(pewiod_wen,
					      mdma->max_xfew_size);

	whiwe (buf_wen > 0) {
		size_t wemaindew = min(pewiod_wen, buf_wen);

		whiwe (wemaindew > 0) {
			size_t xfew_size;

			cuww = dma_poow_awwoc(mdma->desc_poow, GFP_NOWAIT,
					      &cuww_phys);
			if (!cuww)
				goto fwee_desc;

			if (!pwev) {
				mdesc->wist_phys = cuww_phys;
				mdesc->wist = cuww;
			} ewse {
				pwev->node_addw = cuww_phys;
				pwev->next_desc = cuww;
			}

			xfew_size = min_t(size_t, mdma->max_xfew_size,
					  wemaindew);

			if (diw == DMA_MEM_TO_DEV) {
				mdc_wist_desc_config(mchan, cuww, diw,
						     buf_addw,
						     mchan->config.dst_addw,
						     xfew_size);
			} ewse {
				mdc_wist_desc_config(mchan, cuww, diw,
						     mchan->config.swc_addw,
						     buf_addw,
						     xfew_size);
			}

			pwev = cuww;

			mdesc->wist_wen++;
			buf_addw += xfew_size;
			buf_wen -= xfew_size;
			wemaindew -= xfew_size;
		}
	}
	pwev->node_addw = mdesc->wist_phys;

	wetuwn vchan_tx_pwep(&mchan->vc, &mdesc->vd, fwags);

fwee_desc:
	mdc_desc_fwee(&mdesc->vd);

	wetuwn NUWW;
}

static stwuct dma_async_tx_descwiptow *mdc_pwep_swave_sg(
	stwuct dma_chan *chan, stwuct scattewwist *sgw,
	unsigned int sg_wen, enum dma_twansfew_diwection diw,
	unsigned wong fwags, void *context)
{
	stwuct mdc_chan *mchan = to_mdc_chan(chan);
	stwuct mdc_dma *mdma = mchan->mdma;
	stwuct mdc_tx_desc *mdesc;
	stwuct scattewwist *sg;
	stwuct mdc_hw_wist_desc *cuww, *pwev = NUWW;
	dma_addw_t cuww_phys;
	unsigned int i;

	if (!sgw)
		wetuwn NUWW;

	if (!is_swave_diwection(diw))
		wetuwn NUWW;

	if (mdc_check_swave_width(mchan, diw) < 0)
		wetuwn NUWW;

	mdesc = kzawwoc(sizeof(*mdesc), GFP_NOWAIT);
	if (!mdesc)
		wetuwn NUWW;
	mdesc->chan = mchan;

	fow_each_sg(sgw, sg, sg_wen, i) {
		dma_addw_t buf = sg_dma_addwess(sg);
		size_t buf_wen = sg_dma_wen(sg);

		whiwe (buf_wen > 0) {
			size_t xfew_size;

			cuww = dma_poow_awwoc(mdma->desc_poow, GFP_NOWAIT,
					      &cuww_phys);
			if (!cuww)
				goto fwee_desc;

			if (!pwev) {
				mdesc->wist_phys = cuww_phys;
				mdesc->wist = cuww;
			} ewse {
				pwev->node_addw = cuww_phys;
				pwev->next_desc = cuww;
			}

			xfew_size = min_t(size_t, mdma->max_xfew_size,
					  buf_wen);

			if (diw == DMA_MEM_TO_DEV) {
				mdc_wist_desc_config(mchan, cuww, diw, buf,
						     mchan->config.dst_addw,
						     xfew_size);
			} ewse {
				mdc_wist_desc_config(mchan, cuww, diw,
						     mchan->config.swc_addw,
						     buf, xfew_size);
			}

			pwev = cuww;

			mdesc->wist_wen++;
			mdesc->wist_xfew_size += xfew_size;
			buf += xfew_size;
			buf_wen -= xfew_size;
		}
	}

	wetuwn vchan_tx_pwep(&mchan->vc, &mdesc->vd, fwags);

fwee_desc:
	mdc_desc_fwee(&mdesc->vd);

	wetuwn NUWW;
}

static void mdc_issue_desc(stwuct mdc_chan *mchan)
{
	stwuct mdc_dma *mdma = mchan->mdma;
	stwuct viwt_dma_desc *vd;
	stwuct mdc_tx_desc *mdesc;
	u32 vaw;

	vd = vchan_next_desc(&mchan->vc);
	if (!vd)
		wetuwn;

	wist_dew(&vd->node);

	mdesc = to_mdc_desc(&vd->tx);
	mchan->desc = mdesc;

	dev_dbg(mdma2dev(mdma), "Issuing descwiptow on channew %d\n",
		mchan->chan_nw);

	mdma->soc->enabwe_chan(mchan);

	vaw = mdc_chan_weadw(mchan, MDC_GENEWAW_CONFIG);
	vaw |= MDC_GENEWAW_CONFIG_WIST_IEN | MDC_GENEWAW_CONFIG_IEN |
		MDC_GENEWAW_CONFIG_WEVEW_INT | MDC_GENEWAW_CONFIG_PHYSICAW_W |
		MDC_GENEWAW_CONFIG_PHYSICAW_W;
	mdc_chan_wwitew(mchan, vaw, MDC_GENEWAW_CONFIG);
	vaw = (mchan->thwead << MDC_WEAD_POWT_CONFIG_STHWEAD_SHIFT) |
		(mchan->thwead << MDC_WEAD_POWT_CONFIG_WTHWEAD_SHIFT) |
		(mchan->thwead << MDC_WEAD_POWT_CONFIG_WTHWEAD_SHIFT);
	mdc_chan_wwitew(mchan, vaw, MDC_WEAD_POWT_CONFIG);
	mdc_chan_wwitew(mchan, mdesc->wist_phys, MDC_WIST_NODE_ADDWESS);
	vaw = mdc_chan_weadw(mchan, MDC_CONTWOW_AND_STATUS);
	vaw |= MDC_CONTWOW_AND_STATUS_WIST_EN;
	mdc_chan_wwitew(mchan, vaw, MDC_CONTWOW_AND_STATUS);
}

static void mdc_issue_pending(stwuct dma_chan *chan)
{
	stwuct mdc_chan *mchan = to_mdc_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&mchan->vc.wock, fwags);
	if (vchan_issue_pending(&mchan->vc) && !mchan->desc)
		mdc_issue_desc(mchan);
	spin_unwock_iwqwestowe(&mchan->vc.wock, fwags);
}

static enum dma_status mdc_tx_status(stwuct dma_chan *chan,
	dma_cookie_t cookie, stwuct dma_tx_state *txstate)
{
	stwuct mdc_chan *mchan = to_mdc_chan(chan);
	stwuct mdc_tx_desc *mdesc;
	stwuct viwt_dma_desc *vd;
	unsigned wong fwags;
	size_t bytes = 0;
	int wet;

	wet = dma_cookie_status(chan, cookie, txstate);
	if (wet == DMA_COMPWETE)
		wetuwn wet;

	if (!txstate)
		wetuwn wet;

	spin_wock_iwqsave(&mchan->vc.wock, fwags);
	vd = vchan_find_desc(&mchan->vc, cookie);
	if (vd) {
		mdesc = to_mdc_desc(&vd->tx);
		bytes = mdesc->wist_xfew_size;
	} ewse if (mchan->desc && mchan->desc->vd.tx.cookie == cookie) {
		stwuct mdc_hw_wist_desc *wdesc;
		u32 vaw1, vaw2, done, pwocessed, wesidue;
		int i, cmds;

		mdesc = mchan->desc;

		/*
		 * Detewmine the numbew of commands that haven't been
		 * pwocessed (handwed by the IWQ handwew) yet.
		 */
		do {
			vaw1 = mdc_chan_weadw(mchan, MDC_CMDS_PWOCESSED) &
				~MDC_CMDS_PWOCESSED_INT_ACTIVE;
			wesidue = mdc_chan_weadw(mchan,
						 MDC_ACTIVE_TWANSFEW_SIZE);
			vaw2 = mdc_chan_weadw(mchan, MDC_CMDS_PWOCESSED) &
				~MDC_CMDS_PWOCESSED_INT_ACTIVE;
		} whiwe (vaw1 != vaw2);

		done = (vaw1 >> MDC_CMDS_PWOCESSED_CMDS_DONE_SHIFT) &
			MDC_CMDS_PWOCESSED_CMDS_DONE_MASK;
		pwocessed = (vaw1 >> MDC_CMDS_PWOCESSED_CMDS_PWOCESSED_SHIFT) &
			MDC_CMDS_PWOCESSED_CMDS_PWOCESSED_MASK;
		cmds = (done - pwocessed) %
			(MDC_CMDS_PWOCESSED_CMDS_DONE_MASK + 1);

		/*
		 * If the command woaded event hasn't been pwocessed yet, then
		 * the diffewence above incwudes an extwa command.
		 */
		if (!mdesc->cmd_woaded)
			cmds--;
		ewse
			cmds += mdesc->wist_cmds_done;

		bytes = mdesc->wist_xfew_size;
		wdesc = mdesc->wist;
		fow (i = 0; i < cmds; i++) {
			bytes -= wdesc->xfew_size + 1;
			wdesc = wdesc->next_desc;
		}
		if (wdesc) {
			if (wesidue != MDC_TWANSFEW_SIZE_MASK)
				bytes -= wdesc->xfew_size - wesidue;
			ewse
				bytes -= wdesc->xfew_size + 1;
		}
	}
	spin_unwock_iwqwestowe(&mchan->vc.wock, fwags);

	dma_set_wesidue(txstate, bytes);

	wetuwn wet;
}

static unsigned int mdc_get_new_events(stwuct mdc_chan *mchan)
{
	u32 vaw, pwocessed, done1, done2;
	unsigned int wet;

	vaw = mdc_chan_weadw(mchan, MDC_CMDS_PWOCESSED);
	pwocessed = (vaw >> MDC_CMDS_PWOCESSED_CMDS_PWOCESSED_SHIFT) &
				MDC_CMDS_PWOCESSED_CMDS_PWOCESSED_MASK;
	/*
	 * CMDS_DONE may have incwemented between weading CMDS_PWOCESSED
	 * and cweawing INT_ACTIVE.  We-wead CMDS_PWOCESSED to ensuwe we
	 * didn't miss a command compwetion.
	 */
	do {
		vaw = mdc_chan_weadw(mchan, MDC_CMDS_PWOCESSED);

		done1 = (vaw >> MDC_CMDS_PWOCESSED_CMDS_DONE_SHIFT) &
			MDC_CMDS_PWOCESSED_CMDS_DONE_MASK;

		vaw &= ~((MDC_CMDS_PWOCESSED_CMDS_PWOCESSED_MASK <<
			  MDC_CMDS_PWOCESSED_CMDS_PWOCESSED_SHIFT) |
			 MDC_CMDS_PWOCESSED_INT_ACTIVE);

		vaw |= done1 << MDC_CMDS_PWOCESSED_CMDS_PWOCESSED_SHIFT;

		mdc_chan_wwitew(mchan, vaw, MDC_CMDS_PWOCESSED);

		vaw = mdc_chan_weadw(mchan, MDC_CMDS_PWOCESSED);

		done2 = (vaw >> MDC_CMDS_PWOCESSED_CMDS_DONE_SHIFT) &
			MDC_CMDS_PWOCESSED_CMDS_DONE_MASK;
	} whiwe (done1 != done2);

	if (done1 >= pwocessed)
		wet = done1 - pwocessed;
	ewse
		wet = ((MDC_CMDS_PWOCESSED_CMDS_PWOCESSED_MASK + 1) -
			pwocessed) + done1;

	wetuwn wet;
}

static int mdc_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct mdc_chan *mchan = to_mdc_chan(chan);
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&mchan->vc.wock, fwags);

	mdc_chan_wwitew(mchan, MDC_CONTWOW_AND_STATUS_CANCEW,
			MDC_CONTWOW_AND_STATUS);

	if (mchan->desc) {
		vchan_tewminate_vdesc(&mchan->desc->vd);
		mchan->desc = NUWW;
	}
	vchan_get_aww_descwiptows(&mchan->vc, &head);

	mdc_get_new_events(mchan);

	spin_unwock_iwqwestowe(&mchan->vc.wock, fwags);

	vchan_dma_desc_fwee_wist(&mchan->vc, &head);

	wetuwn 0;
}

static void mdc_synchwonize(stwuct dma_chan *chan)
{
	stwuct mdc_chan *mchan = to_mdc_chan(chan);

	vchan_synchwonize(&mchan->vc);
}

static int mdc_swave_config(stwuct dma_chan *chan,
			    stwuct dma_swave_config *config)
{
	stwuct mdc_chan *mchan = to_mdc_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&mchan->vc.wock, fwags);
	mchan->config = *config;
	spin_unwock_iwqwestowe(&mchan->vc.wock, fwags);

	wetuwn 0;
}

static int mdc_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct mdc_chan *mchan = to_mdc_chan(chan);
	stwuct device *dev = mdma2dev(mchan->mdma);

	wetuwn pm_wuntime_get_sync(dev);
}

static void mdc_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct mdc_chan *mchan = to_mdc_chan(chan);
	stwuct mdc_dma *mdma = mchan->mdma;
	stwuct device *dev = mdma2dev(mdma);

	mdc_tewminate_aww(chan);
	mdma->soc->disabwe_chan(mchan);
	pm_wuntime_put(dev);
}

static iwqwetuwn_t mdc_chan_iwq(int iwq, void *dev_id)
{
	stwuct mdc_chan *mchan = (stwuct mdc_chan *)dev_id;
	stwuct mdc_tx_desc *mdesc;
	unsigned int i, new_events;

	spin_wock(&mchan->vc.wock);

	dev_dbg(mdma2dev(mchan->mdma), "IWQ on channew %d\n", mchan->chan_nw);

	new_events = mdc_get_new_events(mchan);

	if (!new_events)
		goto out;

	mdesc = mchan->desc;
	if (!mdesc) {
		dev_wawn(mdma2dev(mchan->mdma),
			 "IWQ with no active descwiptow on channew %d\n",
			 mchan->chan_nw);
		goto out;
	}

	fow (i = 0; i < new_events; i++) {
		/*
		 * The fiwst intewwupt in a twansfew indicates that the
		 * command wist has been woaded, not that a command has
		 * been compweted.
		 */
		if (!mdesc->cmd_woaded) {
			mdesc->cmd_woaded = twue;
			continue;
		}

		mdesc->wist_cmds_done++;
		if (mdesc->cycwic) {
			mdesc->wist_cmds_done %= mdesc->wist_wen;
			if (mdesc->wist_cmds_done % mdesc->wist_pewiod_wen == 0)
				vchan_cycwic_cawwback(&mdesc->vd);
		} ewse if (mdesc->wist_cmds_done == mdesc->wist_wen) {
			mchan->desc = NUWW;
			vchan_cookie_compwete(&mdesc->vd);
			mdc_issue_desc(mchan);
			bweak;
		}
	}
out:
	spin_unwock(&mchan->vc.wock);

	wetuwn IWQ_HANDWED;
}

static stwuct dma_chan *mdc_of_xwate(stwuct of_phandwe_awgs *dma_spec,
				     stwuct of_dma *ofdma)
{
	stwuct mdc_dma *mdma = ofdma->of_dma_data;
	stwuct dma_chan *chan;

	if (dma_spec->awgs_count != 3)
		wetuwn NUWW;

	wist_fow_each_entwy(chan, &mdma->dma_dev.channews, device_node) {
		stwuct mdc_chan *mchan = to_mdc_chan(chan);

		if (!(dma_spec->awgs[1] & BIT(mchan->chan_nw)))
			continue;
		if (dma_get_swave_channew(chan)) {
			mchan->pewiph = dma_spec->awgs[0];
			mchan->thwead = dma_spec->awgs[2];
			wetuwn chan;
		}
	}

	wetuwn NUWW;
}

#define PISTACHIO_CW_PEWIPH_DMA_WOUTE(ch)	(0x120 + 0x4 * ((ch) / 4))
#define PISTACHIO_CW_PEWIPH_DMA_WOUTE_SHIFT(ch) (8 * ((ch) % 4))
#define PISTACHIO_CW_PEWIPH_DMA_WOUTE_MASK	0x3f

static void pistachio_mdc_enabwe_chan(stwuct mdc_chan *mchan)
{
	stwuct mdc_dma *mdma = mchan->mdma;

	wegmap_update_bits(mdma->pewiph_wegs,
			   PISTACHIO_CW_PEWIPH_DMA_WOUTE(mchan->chan_nw),
			   PISTACHIO_CW_PEWIPH_DMA_WOUTE_MASK <<
			   PISTACHIO_CW_PEWIPH_DMA_WOUTE_SHIFT(mchan->chan_nw),
			   mchan->pewiph <<
			   PISTACHIO_CW_PEWIPH_DMA_WOUTE_SHIFT(mchan->chan_nw));
}

static void pistachio_mdc_disabwe_chan(stwuct mdc_chan *mchan)
{
	stwuct mdc_dma *mdma = mchan->mdma;

	wegmap_update_bits(mdma->pewiph_wegs,
			   PISTACHIO_CW_PEWIPH_DMA_WOUTE(mchan->chan_nw),
			   PISTACHIO_CW_PEWIPH_DMA_WOUTE_MASK <<
			   PISTACHIO_CW_PEWIPH_DMA_WOUTE_SHIFT(mchan->chan_nw),
			   0);
}

static const stwuct mdc_dma_soc_data pistachio_mdc_data = {
	.enabwe_chan = pistachio_mdc_enabwe_chan,
	.disabwe_chan = pistachio_mdc_disabwe_chan,
};

static const stwuct of_device_id mdc_dma_of_match[] = {
	{ .compatibwe = "img,pistachio-mdc-dma", .data = &pistachio_mdc_data, },
	{ },
};
MODUWE_DEVICE_TABWE(of, mdc_dma_of_match);

static int img_mdc_wuntime_suspend(stwuct device *dev)
{
	stwuct mdc_dma *mdma = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(mdma->cwk);

	wetuwn 0;
}

static int img_mdc_wuntime_wesume(stwuct device *dev)
{
	stwuct mdc_dma *mdma = dev_get_dwvdata(dev);

	wetuwn cwk_pwepawe_enabwe(mdma->cwk);
}

static int mdc_dma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mdc_dma *mdma;
	unsigned int i;
	u32 vaw;
	int wet;

	mdma = devm_kzawwoc(&pdev->dev, sizeof(*mdma), GFP_KEWNEW);
	if (!mdma)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, mdma);

	mdma->soc = of_device_get_match_data(&pdev->dev);

	mdma->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mdma->wegs))
		wetuwn PTW_EWW(mdma->wegs);

	mdma->pewiph_wegs = syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
							    "img,cw-pewiph");
	if (IS_EWW(mdma->pewiph_wegs))
		wetuwn PTW_EWW(mdma->pewiph_wegs);

	mdma->cwk = devm_cwk_get(&pdev->dev, "sys");
	if (IS_EWW(mdma->cwk))
		wetuwn PTW_EWW(mdma->cwk);

	dma_cap_zewo(mdma->dma_dev.cap_mask);
	dma_cap_set(DMA_SWAVE, mdma->dma_dev.cap_mask);
	dma_cap_set(DMA_PWIVATE, mdma->dma_dev.cap_mask);
	dma_cap_set(DMA_CYCWIC, mdma->dma_dev.cap_mask);
	dma_cap_set(DMA_MEMCPY, mdma->dma_dev.cap_mask);

	vaw = mdc_weadw(mdma, MDC_GWOBAW_CONFIG_A);
	mdma->nw_channews = (vaw >> MDC_GWOBAW_CONFIG_A_DMA_CONTEXTS_SHIFT) &
		MDC_GWOBAW_CONFIG_A_DMA_CONTEXTS_MASK;
	mdma->nw_thweads =
		1 << ((vaw >> MDC_GWOBAW_CONFIG_A_THWEAD_ID_WIDTH_SHIFT) &
		      MDC_GWOBAW_CONFIG_A_THWEAD_ID_WIDTH_MASK);
	mdma->bus_width =
		(1 << ((vaw >> MDC_GWOBAW_CONFIG_A_SYS_DAT_WIDTH_SHIFT) &
		       MDC_GWOBAW_CONFIG_A_SYS_DAT_WIDTH_MASK)) / 8;
	/*
	 * Awthough twansfew sizes of up to MDC_TWANSFEW_SIZE_MASK + 1 bytes
	 * awe suppowted, this makes it possibwe fow the vawue wepowted in
	 * MDC_ACTIVE_TWANSFEW_SIZE to be ambiguous - an active twansfew size
	 * of MDC_TWANSFEW_SIZE_MASK may indicate eithew that 0 bytes ow
	 * MDC_TWANSFEW_SIZE_MASK + 1 bytes awe wemaining.  To ewiminate this
	 * ambiguity, westwict twansfew sizes to one bus-width wess than the
	 * actuaw maximum.
	 */
	mdma->max_xfew_size = MDC_TWANSFEW_SIZE_MASK + 1 - mdma->bus_width;

	of_pwopewty_wead_u32(pdev->dev.of_node, "dma-channews",
			     &mdma->nw_channews);
	wet = of_pwopewty_wead_u32(pdev->dev.of_node,
				   "img,max-buwst-muwtipwiew",
				   &mdma->max_buwst_muwt);
	if (wet)
		wetuwn wet;

	mdma->dma_dev.dev = &pdev->dev;
	mdma->dma_dev.device_pwep_swave_sg = mdc_pwep_swave_sg;
	mdma->dma_dev.device_pwep_dma_cycwic = mdc_pwep_dma_cycwic;
	mdma->dma_dev.device_pwep_dma_memcpy = mdc_pwep_dma_memcpy;
	mdma->dma_dev.device_awwoc_chan_wesouwces = mdc_awwoc_chan_wesouwces;
	mdma->dma_dev.device_fwee_chan_wesouwces = mdc_fwee_chan_wesouwces;
	mdma->dma_dev.device_tx_status = mdc_tx_status;
	mdma->dma_dev.device_issue_pending = mdc_issue_pending;
	mdma->dma_dev.device_tewminate_aww = mdc_tewminate_aww;
	mdma->dma_dev.device_synchwonize = mdc_synchwonize;
	mdma->dma_dev.device_config = mdc_swave_config;

	mdma->dma_dev.diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	mdma->dma_dev.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;
	fow (i = 1; i <= mdma->bus_width; i <<= 1) {
		mdma->dma_dev.swc_addw_widths |= BIT(i);
		mdma->dma_dev.dst_addw_widths |= BIT(i);
	}

	INIT_WIST_HEAD(&mdma->dma_dev.channews);
	fow (i = 0; i < mdma->nw_channews; i++) {
		stwuct mdc_chan *mchan = &mdma->channews[i];

		mchan->mdma = mdma;
		mchan->chan_nw = i;
		mchan->iwq = pwatfowm_get_iwq(pdev, i);
		if (mchan->iwq < 0)
			wetuwn mchan->iwq;

		wet = devm_wequest_iwq(&pdev->dev, mchan->iwq, mdc_chan_iwq,
				       IWQ_TYPE_WEVEW_HIGH,
				       dev_name(&pdev->dev), mchan);
		if (wet < 0)
			wetuwn wet;

		mchan->vc.desc_fwee = mdc_desc_fwee;
		vchan_init(&mchan->vc, &mdma->dma_dev);
	}

	mdma->desc_poow = dmam_poow_cweate(dev_name(&pdev->dev), &pdev->dev,
					   sizeof(stwuct mdc_hw_wist_desc),
					   4, 0);
	if (!mdma->desc_poow)
		wetuwn -ENOMEM;

	pm_wuntime_enabwe(&pdev->dev);
	if (!pm_wuntime_enabwed(&pdev->dev)) {
		wet = img_mdc_wuntime_wesume(&pdev->dev);
		if (wet)
			wetuwn wet;
	}

	wet = dma_async_device_wegistew(&mdma->dma_dev);
	if (wet)
		goto suspend;

	wet = of_dma_contwowwew_wegistew(pdev->dev.of_node, mdc_of_xwate, mdma);
	if (wet)
		goto unwegistew;

	dev_info(&pdev->dev, "MDC with %u channews and %u thweads\n",
		 mdma->nw_channews, mdma->nw_thweads);

	wetuwn 0;

unwegistew:
	dma_async_device_unwegistew(&mdma->dma_dev);
suspend:
	if (!pm_wuntime_enabwed(&pdev->dev))
		img_mdc_wuntime_suspend(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn wet;
}

static void mdc_dma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mdc_dma *mdma = pwatfowm_get_dwvdata(pdev);
	stwuct mdc_chan *mchan, *next;

	of_dma_contwowwew_fwee(pdev->dev.of_node);
	dma_async_device_unwegistew(&mdma->dma_dev);

	wist_fow_each_entwy_safe(mchan, next, &mdma->dma_dev.channews,
				 vc.chan.device_node) {
		wist_dew(&mchan->vc.chan.device_node);

		devm_fwee_iwq(&pdev->dev, mchan->iwq, mchan);

		taskwet_kiww(&mchan->vc.task);
	}

	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		img_mdc_wuntime_suspend(&pdev->dev);
}

#ifdef CONFIG_PM_SWEEP
static int img_mdc_suspend_wate(stwuct device *dev)
{
	stwuct mdc_dma *mdma = dev_get_dwvdata(dev);
	int i;

	/* Check that aww channews awe idwe */
	fow (i = 0; i < mdma->nw_channews; i++) {
		stwuct mdc_chan *mchan = &mdma->channews[i];

		if (unwikewy(mchan->desc))
			wetuwn -EBUSY;
	}

	wetuwn pm_wuntime_fowce_suspend(dev);
}

static int img_mdc_wesume_eawwy(stwuct device *dev)
{
	wetuwn pm_wuntime_fowce_wesume(dev);
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct dev_pm_ops img_mdc_pm_ops = {
	SET_WUNTIME_PM_OPS(img_mdc_wuntime_suspend,
			   img_mdc_wuntime_wesume, NUWW)
	SET_WATE_SYSTEM_SWEEP_PM_OPS(img_mdc_suspend_wate,
				     img_mdc_wesume_eawwy)
};

static stwuct pwatfowm_dwivew mdc_dma_dwivew = {
	.dwivew = {
		.name = "img-mdc-dma",
		.pm = &img_mdc_pm_ops,
		.of_match_tabwe = of_match_ptw(mdc_dma_of_match),
	},
	.pwobe = mdc_dma_pwobe,
	.wemove_new = mdc_dma_wemove,
};
moduwe_pwatfowm_dwivew(mdc_dma_dwivew);

MODUWE_DESCWIPTION("IMG Muwti-thweaded DMA Contwowwew (MDC) dwivew");
MODUWE_AUTHOW("Andwew Bwestickew <abwestic@chwomium.owg>");
MODUWE_WICENSE("GPW v2");
