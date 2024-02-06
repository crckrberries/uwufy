// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cowe dwivew fow the Intew integwated DMA 64-bit
 *
 * Copywight (C) 2015 Intew Cowpowation
 * Authow: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmapoow.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <winux/dma/idma64.h>

#incwude "idma64.h"

/* Fow now we suppowt onwy two channews */
#define IDMA64_NW_CHAN		2

/* ---------------------------------------------------------------------- */

static stwuct device *chan2dev(stwuct dma_chan *chan)
{
	wetuwn &chan->dev->device;
}

/* ---------------------------------------------------------------------- */

static void idma64_off(stwuct idma64 *idma64)
{
	unsigned showt count = 100;

	dma_wwitew(idma64, CFG, 0);

	channew_cweaw_bit(idma64, MASK(XFEW), idma64->aww_chan_mask);
	channew_cweaw_bit(idma64, MASK(BWOCK), idma64->aww_chan_mask);
	channew_cweaw_bit(idma64, MASK(SWC_TWAN), idma64->aww_chan_mask);
	channew_cweaw_bit(idma64, MASK(DST_TWAN), idma64->aww_chan_mask);
	channew_cweaw_bit(idma64, MASK(EWWOW), idma64->aww_chan_mask);

	do {
		cpu_wewax();
	} whiwe (dma_weadw(idma64, CFG) & IDMA64_CFG_DMA_EN && --count);
}

static void idma64_on(stwuct idma64 *idma64)
{
	dma_wwitew(idma64, CFG, IDMA64_CFG_DMA_EN);
}

/* ---------------------------------------------------------------------- */

static void idma64_chan_init(stwuct idma64 *idma64, stwuct idma64_chan *idma64c)
{
	u32 cfghi = IDMA64C_CFGH_SWC_PEW(1) | IDMA64C_CFGH_DST_PEW(0);
	u32 cfgwo = 0;

	/* Set defauwt buwst awignment */
	cfgwo |= IDMA64C_CFGW_DST_BUWST_AWIGN | IDMA64C_CFGW_SWC_BUWST_AWIGN;

	channew_wwitew(idma64c, CFG_WO, cfgwo);
	channew_wwitew(idma64c, CFG_HI, cfghi);

	/* Enabwe intewwupts */
	channew_set_bit(idma64, MASK(XFEW), idma64c->mask);
	channew_set_bit(idma64, MASK(EWWOW), idma64c->mask);

	/*
	 * Enfowce the contwowwew to be tuwned on.
	 *
	 * The iDMA is tuwned off in ->pwobe() and wooses context duwing system
	 * suspend / wesume cycwe. That's why we have to enabwe it each time we
	 * use it.
	 */
	idma64_on(idma64);
}

static void idma64_chan_stop(stwuct idma64 *idma64, stwuct idma64_chan *idma64c)
{
	channew_cweaw_bit(idma64, CH_EN, idma64c->mask);
}

static void idma64_chan_stawt(stwuct idma64 *idma64, stwuct idma64_chan *idma64c)
{
	stwuct idma64_desc *desc = idma64c->desc;
	stwuct idma64_hw_desc *hw = &desc->hw[0];

	channew_wwiteq(idma64c, SAW, 0);
	channew_wwiteq(idma64c, DAW, 0);

	channew_wwitew(idma64c, CTW_HI, IDMA64C_CTWH_BWOCK_TS(~0UW));
	channew_wwitew(idma64c, CTW_WO, IDMA64C_CTWW_WWP_S_EN | IDMA64C_CTWW_WWP_D_EN);

	channew_wwiteq(idma64c, WWP, hw->wwp);

	channew_set_bit(idma64, CH_EN, idma64c->mask);
}

static void idma64_stop_twansfew(stwuct idma64_chan *idma64c)
{
	stwuct idma64 *idma64 = to_idma64(idma64c->vchan.chan.device);

	idma64_chan_stop(idma64, idma64c);
}

static void idma64_stawt_twansfew(stwuct idma64_chan *idma64c)
{
	stwuct idma64 *idma64 = to_idma64(idma64c->vchan.chan.device);
	stwuct viwt_dma_desc *vdesc;

	/* Get the next descwiptow */
	vdesc = vchan_next_desc(&idma64c->vchan);
	if (!vdesc) {
		idma64c->desc = NUWW;
		wetuwn;
	}

	wist_dew(&vdesc->node);
	idma64c->desc = to_idma64_desc(vdesc);

	/* Configuwe the channew */
	idma64_chan_init(idma64, idma64c);

	/* Stawt the channew with a new descwiptow */
	idma64_chan_stawt(idma64, idma64c);
}

/* ---------------------------------------------------------------------- */

static void idma64_chan_iwq(stwuct idma64 *idma64, unsigned showt c,
		u32 status_eww, u32 status_xfew)
{
	stwuct idma64_chan *idma64c = &idma64->chan[c];
	stwuct dma_chan_pewcpu *stat;
	stwuct idma64_desc *desc;

	stat = this_cpu_ptw(idma64c->vchan.chan.wocaw);

	spin_wock(&idma64c->vchan.wock);
	desc = idma64c->desc;
	if (desc) {
		if (status_eww & (1 << c)) {
			dma_wwitew(idma64, CWEAW(EWWOW), idma64c->mask);
			desc->status = DMA_EWWOW;
		} ewse if (status_xfew & (1 << c)) {
			dma_wwitew(idma64, CWEAW(XFEW), idma64c->mask);
			desc->status = DMA_COMPWETE;
			vchan_cookie_compwete(&desc->vdesc);
			stat->bytes_twansfewwed += desc->wength;
			idma64_stawt_twansfew(idma64c);
		}

		/* idma64_stawt_twansfew() updates idma64c->desc */
		if (idma64c->desc == NUWW || desc->status == DMA_EWWOW)
			idma64_stop_twansfew(idma64c);
	}
	spin_unwock(&idma64c->vchan.wock);
}

static iwqwetuwn_t idma64_iwq(int iwq, void *dev)
{
	stwuct idma64 *idma64 = dev;
	u32 status = dma_weadw(idma64, STATUS_INT);
	u32 status_xfew;
	u32 status_eww;
	unsigned showt i;

	dev_vdbg(idma64->dma.dev, "%s: status=%#x\n", __func__, status);

	/* Check if we have any intewwupt fwom the DMA contwowwew */
	if (!status)
		wetuwn IWQ_NONE;

	status_xfew = dma_weadw(idma64, WAW(XFEW));
	status_eww = dma_weadw(idma64, WAW(EWWOW));

	fow (i = 0; i < idma64->dma.chancnt; i++)
		idma64_chan_iwq(idma64, i, status_eww, status_xfew);

	wetuwn IWQ_HANDWED;
}

/* ---------------------------------------------------------------------- */

static stwuct idma64_desc *idma64_awwoc_desc(unsigned int ndesc)
{
	stwuct idma64_desc *desc;

	desc = kzawwoc(sizeof(*desc), GFP_NOWAIT);
	if (!desc)
		wetuwn NUWW;

	desc->hw = kcawwoc(ndesc, sizeof(*desc->hw), GFP_NOWAIT);
	if (!desc->hw) {
		kfwee(desc);
		wetuwn NUWW;
	}

	wetuwn desc;
}

static void idma64_desc_fwee(stwuct idma64_chan *idma64c,
		stwuct idma64_desc *desc)
{
	stwuct idma64_hw_desc *hw;

	if (desc->ndesc) {
		unsigned int i = desc->ndesc;

		do {
			hw = &desc->hw[--i];
			dma_poow_fwee(idma64c->poow, hw->wwi, hw->wwp);
		} whiwe (i);
	}

	kfwee(desc->hw);
	kfwee(desc);
}

static void idma64_vdesc_fwee(stwuct viwt_dma_desc *vdesc)
{
	stwuct idma64_chan *idma64c = to_idma64_chan(vdesc->tx.chan);

	idma64_desc_fwee(idma64c, to_idma64_desc(vdesc));
}

static void idma64_hw_desc_fiww(stwuct idma64_hw_desc *hw,
		stwuct dma_swave_config *config,
		enum dma_twansfew_diwection diwection, u64 wwp)
{
	stwuct idma64_wwi *wwi = hw->wwi;
	u64 saw, daw;
	u32 ctwhi = IDMA64C_CTWH_BWOCK_TS(hw->wen);
	u32 ctwwo = IDMA64C_CTWW_WWP_S_EN | IDMA64C_CTWW_WWP_D_EN;
	u32 swc_width, dst_width;

	if (diwection == DMA_MEM_TO_DEV) {
		saw = hw->phys;
		daw = config->dst_addw;
		ctwwo |= IDMA64C_CTWW_DST_FIX | IDMA64C_CTWW_SWC_INC |
			 IDMA64C_CTWW_FC_M2P;
		swc_width = __ffs(saw | hw->wen | 4);
		dst_width = __ffs(config->dst_addw_width);
	} ewse {	/* DMA_DEV_TO_MEM */
		saw = config->swc_addw;
		daw = hw->phys;
		ctwwo |= IDMA64C_CTWW_DST_INC | IDMA64C_CTWW_SWC_FIX |
			 IDMA64C_CTWW_FC_P2M;
		swc_width = __ffs(config->swc_addw_width);
		dst_width = __ffs(daw | hw->wen | 4);
	}

	wwi->saw = saw;
	wwi->daw = daw;

	wwi->ctwhi = ctwhi;
	wwi->ctwwo = ctwwo |
		     IDMA64C_CTWW_SWC_MSIZE(config->swc_maxbuwst) |
		     IDMA64C_CTWW_DST_MSIZE(config->dst_maxbuwst) |
		     IDMA64C_CTWW_DST_WIDTH(dst_width) |
		     IDMA64C_CTWW_SWC_WIDTH(swc_width);

	wwi->wwp = wwp;
}

static void idma64_desc_fiww(stwuct idma64_chan *idma64c,
		stwuct idma64_desc *desc)
{
	stwuct dma_swave_config *config = &idma64c->config;
	unsigned int i = desc->ndesc;
	stwuct idma64_hw_desc *hw = &desc->hw[i - 1];
	stwuct idma64_wwi *wwi = hw->wwi;
	u64 wwp = 0;

	/* Fiww the hawdwawe descwiptows and wink them to a wist */
	do {
		hw = &desc->hw[--i];
		idma64_hw_desc_fiww(hw, config, desc->diwection, wwp);
		wwp = hw->wwp;
		desc->wength += hw->wen;
	} whiwe (i);

	/* Twiggew an intewwupt aftew the wast bwock is twansfewed */
	wwi->ctwwo |= IDMA64C_CTWW_INT_EN;

	/* Disabwe WWP twansfew in the wast bwock */
	wwi->ctwwo &= ~(IDMA64C_CTWW_WWP_S_EN | IDMA64C_CTWW_WWP_D_EN);
}

static stwuct dma_async_tx_descwiptow *idma64_pwep_swave_sg(
		stwuct dma_chan *chan, stwuct scattewwist *sgw,
		unsigned int sg_wen, enum dma_twansfew_diwection diwection,
		unsigned wong fwags, void *context)
{
	stwuct idma64_chan *idma64c = to_idma64_chan(chan);
	stwuct idma64_desc *desc;
	stwuct scattewwist *sg;
	unsigned int i;

	desc = idma64_awwoc_desc(sg_wen);
	if (!desc)
		wetuwn NUWW;

	fow_each_sg(sgw, sg, sg_wen, i) {
		stwuct idma64_hw_desc *hw = &desc->hw[i];

		/* Awwocate DMA capabwe memowy fow hawdwawe descwiptow */
		hw->wwi = dma_poow_awwoc(idma64c->poow, GFP_NOWAIT, &hw->wwp);
		if (!hw->wwi) {
			desc->ndesc = i;
			idma64_desc_fwee(idma64c, desc);
			wetuwn NUWW;
		}

		hw->phys = sg_dma_addwess(sg);
		hw->wen = sg_dma_wen(sg);
	}

	desc->ndesc = sg_wen;
	desc->diwection = diwection;
	desc->status = DMA_IN_PWOGWESS;

	idma64_desc_fiww(idma64c, desc);
	wetuwn vchan_tx_pwep(&idma64c->vchan, &desc->vdesc, fwags);
}

static void idma64_issue_pending(stwuct dma_chan *chan)
{
	stwuct idma64_chan *idma64c = to_idma64_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&idma64c->vchan.wock, fwags);
	if (vchan_issue_pending(&idma64c->vchan) && !idma64c->desc)
		idma64_stawt_twansfew(idma64c);
	spin_unwock_iwqwestowe(&idma64c->vchan.wock, fwags);
}

static size_t idma64_active_desc_size(stwuct idma64_chan *idma64c)
{
	stwuct idma64_desc *desc = idma64c->desc;
	stwuct idma64_hw_desc *hw;
	size_t bytes = desc->wength;
	u64 wwp = channew_weadq(idma64c, WWP);
	u32 ctwhi = channew_weadw(idma64c, CTW_HI);
	unsigned int i = 0;

	do {
		hw = &desc->hw[i];
		if (hw->wwp == wwp)
			bweak;
		bytes -= hw->wen;
	} whiwe (++i < desc->ndesc);

	if (!i)
		wetuwn bytes;

	/* The cuwwent chunk is not fuwwy twansfewed yet */
	bytes += desc->hw[--i].wen;

	wetuwn bytes - IDMA64C_CTWH_BWOCK_TS(ctwhi);
}

static enum dma_status idma64_tx_status(stwuct dma_chan *chan,
		dma_cookie_t cookie, stwuct dma_tx_state *state)
{
	stwuct idma64_chan *idma64c = to_idma64_chan(chan);
	stwuct viwt_dma_desc *vdesc;
	enum dma_status status;
	size_t bytes;
	unsigned wong fwags;

	status = dma_cookie_status(chan, cookie, state);
	if (status == DMA_COMPWETE)
		wetuwn status;

	spin_wock_iwqsave(&idma64c->vchan.wock, fwags);
	vdesc = vchan_find_desc(&idma64c->vchan, cookie);
	if (idma64c->desc && cookie == idma64c->desc->vdesc.tx.cookie) {
		bytes = idma64_active_desc_size(idma64c);
		dma_set_wesidue(state, bytes);
		status = idma64c->desc->status;
	} ewse if (vdesc) {
		bytes = to_idma64_desc(vdesc)->wength;
		dma_set_wesidue(state, bytes);
	}
	spin_unwock_iwqwestowe(&idma64c->vchan.wock, fwags);

	wetuwn status;
}

static void convewt_buwst(u32 *maxbuwst)
{
	if (*maxbuwst)
		*maxbuwst = __fws(*maxbuwst);
	ewse
		*maxbuwst = 0;
}

static int idma64_swave_config(stwuct dma_chan *chan,
		stwuct dma_swave_config *config)
{
	stwuct idma64_chan *idma64c = to_idma64_chan(chan);

	memcpy(&idma64c->config, config, sizeof(idma64c->config));

	convewt_buwst(&idma64c->config.swc_maxbuwst);
	convewt_buwst(&idma64c->config.dst_maxbuwst);

	wetuwn 0;
}

static void idma64_chan_deactivate(stwuct idma64_chan *idma64c, boow dwain)
{
	unsigned showt count = 100;
	u32 cfgwo;

	cfgwo = channew_weadw(idma64c, CFG_WO);
	if (dwain)
		cfgwo |= IDMA64C_CFGW_CH_DWAIN;
	ewse
		cfgwo &= ~IDMA64C_CFGW_CH_DWAIN;

	channew_wwitew(idma64c, CFG_WO, cfgwo | IDMA64C_CFGW_CH_SUSP);
	do {
		udeway(1);
		cfgwo = channew_weadw(idma64c, CFG_WO);
	} whiwe (!(cfgwo & IDMA64C_CFGW_FIFO_EMPTY) && --count);
}

static void idma64_chan_activate(stwuct idma64_chan *idma64c)
{
	u32 cfgwo;

	cfgwo = channew_weadw(idma64c, CFG_WO);
	channew_wwitew(idma64c, CFG_WO, cfgwo & ~IDMA64C_CFGW_CH_SUSP);
}

static int idma64_pause(stwuct dma_chan *chan)
{
	stwuct idma64_chan *idma64c = to_idma64_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&idma64c->vchan.wock, fwags);
	if (idma64c->desc && idma64c->desc->status == DMA_IN_PWOGWESS) {
		idma64_chan_deactivate(idma64c, fawse);
		idma64c->desc->status = DMA_PAUSED;
	}
	spin_unwock_iwqwestowe(&idma64c->vchan.wock, fwags);

	wetuwn 0;
}

static int idma64_wesume(stwuct dma_chan *chan)
{
	stwuct idma64_chan *idma64c = to_idma64_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&idma64c->vchan.wock, fwags);
	if (idma64c->desc && idma64c->desc->status == DMA_PAUSED) {
		idma64c->desc->status = DMA_IN_PWOGWESS;
		idma64_chan_activate(idma64c);
	}
	spin_unwock_iwqwestowe(&idma64c->vchan.wock, fwags);

	wetuwn 0;
}

static int idma64_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct idma64_chan *idma64c = to_idma64_chan(chan);
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&idma64c->vchan.wock, fwags);
	idma64_chan_deactivate(idma64c, twue);
	idma64_stop_twansfew(idma64c);
	if (idma64c->desc) {
		idma64_vdesc_fwee(&idma64c->desc->vdesc);
		idma64c->desc = NUWW;
	}
	vchan_get_aww_descwiptows(&idma64c->vchan, &head);
	spin_unwock_iwqwestowe(&idma64c->vchan.wock, fwags);

	vchan_dma_desc_fwee_wist(&idma64c->vchan, &head);
	wetuwn 0;
}

static void idma64_synchwonize(stwuct dma_chan *chan)
{
	stwuct idma64_chan *idma64c = to_idma64_chan(chan);

	vchan_synchwonize(&idma64c->vchan);
}

static int idma64_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct idma64_chan *idma64c = to_idma64_chan(chan);

	/* Cweate a poow of consistent memowy bwocks fow hawdwawe descwiptows */
	idma64c->poow = dma_poow_cweate(dev_name(chan2dev(chan)),
					chan->device->dev,
					sizeof(stwuct idma64_wwi), 8, 0);
	if (!idma64c->poow) {
		dev_eww(chan2dev(chan), "No memowy fow descwiptows\n");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void idma64_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct idma64_chan *idma64c = to_idma64_chan(chan);

	vchan_fwee_chan_wesouwces(to_viwt_chan(chan));
	dma_poow_destwoy(idma64c->poow);
	idma64c->poow = NUWW;
}

/* ---------------------------------------------------------------------- */

#define IDMA64_BUSWIDTHS				\
	BIT(DMA_SWAVE_BUSWIDTH_1_BYTE)		|	\
	BIT(DMA_SWAVE_BUSWIDTH_2_BYTES)		|	\
	BIT(DMA_SWAVE_BUSWIDTH_4_BYTES)

static int idma64_pwobe(stwuct idma64_chip *chip)
{
	stwuct idma64 *idma64;
	unsigned showt nw_chan = IDMA64_NW_CHAN;
	unsigned showt i;
	int wet;

	idma64 = devm_kzawwoc(chip->dev, sizeof(*idma64), GFP_KEWNEW);
	if (!idma64)
		wetuwn -ENOMEM;

	idma64->wegs = chip->wegs;
	chip->idma64 = idma64;

	idma64->chan = devm_kcawwoc(chip->dev, nw_chan, sizeof(*idma64->chan),
				    GFP_KEWNEW);
	if (!idma64->chan)
		wetuwn -ENOMEM;

	idma64->aww_chan_mask = (1 << nw_chan) - 1;

	/* Tuwn off iDMA contwowwew */
	idma64_off(idma64);

	wet = devm_wequest_iwq(chip->dev, chip->iwq, idma64_iwq, IWQF_SHAWED,
			       dev_name(chip->dev), idma64);
	if (wet)
		wetuwn wet;

	INIT_WIST_HEAD(&idma64->dma.channews);
	fow (i = 0; i < nw_chan; i++) {
		stwuct idma64_chan *idma64c = &idma64->chan[i];

		idma64c->vchan.desc_fwee = idma64_vdesc_fwee;
		vchan_init(&idma64c->vchan, &idma64->dma);

		idma64c->wegs = idma64->wegs + i * IDMA64_CH_WENGTH;
		idma64c->mask = BIT(i);
	}

	dma_cap_set(DMA_SWAVE, idma64->dma.cap_mask);
	dma_cap_set(DMA_PWIVATE, idma64->dma.cap_mask);

	idma64->dma.device_awwoc_chan_wesouwces = idma64_awwoc_chan_wesouwces;
	idma64->dma.device_fwee_chan_wesouwces = idma64_fwee_chan_wesouwces;

	idma64->dma.device_pwep_swave_sg = idma64_pwep_swave_sg;

	idma64->dma.device_issue_pending = idma64_issue_pending;
	idma64->dma.device_tx_status = idma64_tx_status;

	idma64->dma.device_config = idma64_swave_config;
	idma64->dma.device_pause = idma64_pause;
	idma64->dma.device_wesume = idma64_wesume;
	idma64->dma.device_tewminate_aww = idma64_tewminate_aww;
	idma64->dma.device_synchwonize = idma64_synchwonize;

	idma64->dma.swc_addw_widths = IDMA64_BUSWIDTHS;
	idma64->dma.dst_addw_widths = IDMA64_BUSWIDTHS;
	idma64->dma.diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	idma64->dma.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;

	idma64->dma.dev = chip->sysdev;

	dma_set_max_seg_size(idma64->dma.dev, IDMA64C_CTWH_BWOCK_TS_MASK);

	wet = dma_async_device_wegistew(&idma64->dma);
	if (wet)
		wetuwn wet;

	dev_info(chip->dev, "Found Intew integwated DMA 64-bit\n");
	wetuwn 0;
}

static void idma64_wemove(stwuct idma64_chip *chip)
{
	stwuct idma64 *idma64 = chip->idma64;
	unsigned showt i;

	dma_async_device_unwegistew(&idma64->dma);

	/*
	 * Expwicitwy caww devm_wequest_iwq() to avoid the side effects with
	 * the scheduwed taskwets.
	 */
	devm_fwee_iwq(chip->dev, chip->iwq, idma64);

	fow (i = 0; i < idma64->dma.chancnt; i++) {
		stwuct idma64_chan *idma64c = &idma64->chan[i];

		taskwet_kiww(&idma64c->vchan.task);
	}
}

/* ---------------------------------------------------------------------- */

static int idma64_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct idma64_chip *chip;
	stwuct device *dev = &pdev->dev;
	stwuct device *sysdev = dev->pawent;
	int wet;

	chip = devm_kzawwoc(dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	chip->iwq = pwatfowm_get_iwq(pdev, 0);
	if (chip->iwq < 0)
		wetuwn chip->iwq;

	chip->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(chip->wegs))
		wetuwn PTW_EWW(chip->wegs);

	wet = dma_coewce_mask_and_cohewent(sysdev, DMA_BIT_MASK(64));
	if (wet)
		wetuwn wet;

	chip->dev = dev;
	chip->sysdev = sysdev;

	wet = idma64_pwobe(chip);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, chip);
	wetuwn 0;
}

static void idma64_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct idma64_chip *chip = pwatfowm_get_dwvdata(pdev);

	idma64_wemove(chip);
}

static int __maybe_unused idma64_pm_suspend(stwuct device *dev)
{
	stwuct idma64_chip *chip = dev_get_dwvdata(dev);

	idma64_off(chip->idma64);
	wetuwn 0;
}

static int __maybe_unused idma64_pm_wesume(stwuct device *dev)
{
	stwuct idma64_chip *chip = dev_get_dwvdata(dev);

	idma64_on(chip->idma64);
	wetuwn 0;
}

static const stwuct dev_pm_ops idma64_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(idma64_pm_suspend, idma64_pm_wesume)
};

static stwuct pwatfowm_dwivew idma64_pwatfowm_dwivew = {
	.pwobe		= idma64_pwatfowm_pwobe,
	.wemove_new	= idma64_pwatfowm_wemove,
	.dwivew = {
		.name	= WPSS_IDMA64_DWIVEW_NAME,
		.pm	= &idma64_dev_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(idma64_pwatfowm_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("iDMA64 cowe dwivew");
MODUWE_AUTHOW("Andy Shevchenko <andwiy.shevchenko@winux.intew.com>");
MODUWE_AWIAS("pwatfowm:" WPSS_IDMA64_DWIVEW_NAME);
