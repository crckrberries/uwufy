// SPDX-Wicense-Identifiew: GPW-2.0
// (C) 2017-2018 Synopsys, Inc. (www.synopsys.com)

/*
 * Synopsys DesignWawe AXI DMA Contwowwew dwivew.
 *
 * Authow: Eugeniy Pawtsev <Eugeniy.Pawtsev@synopsys.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dmaengine.h>
#incwude <winux/dmapoow.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#incwude "dw-axi-dmac.h"
#incwude "../dmaengine.h"
#incwude "../viwt-dma.h"

/*
 * The set of bus widths suppowted by the DMA contwowwew. DW AXI DMAC suppowts
 * mastew data bus width up to 512 bits (fow both AXI mastew intewfaces), but
 * it depends on IP bwock configuwation.
 */
#define AXI_DMA_BUSWIDTHS		  \
	(DMA_SWAVE_BUSWIDTH_1_BYTE	| \
	DMA_SWAVE_BUSWIDTH_2_BYTES	| \
	DMA_SWAVE_BUSWIDTH_4_BYTES	| \
	DMA_SWAVE_BUSWIDTH_8_BYTES	| \
	DMA_SWAVE_BUSWIDTH_16_BYTES	| \
	DMA_SWAVE_BUSWIDTH_32_BYTES	| \
	DMA_SWAVE_BUSWIDTH_64_BYTES)

#define AXI_DMA_FWAG_HAS_APB_WEGS	BIT(0)
#define AXI_DMA_FWAG_HAS_WESETS		BIT(1)
#define AXI_DMA_FWAG_USE_CFG2		BIT(2)

static inwine void
axi_dma_iowwite32(stwuct axi_dma_chip *chip, u32 weg, u32 vaw)
{
	iowwite32(vaw, chip->wegs + weg);
}

static inwine u32 axi_dma_iowead32(stwuct axi_dma_chip *chip, u32 weg)
{
	wetuwn iowead32(chip->wegs + weg);
}

static inwine void
axi_dma_iowwite64(stwuct axi_dma_chip *chip, u32 weg, u64 vaw)
{
	iowwite64(vaw, chip->wegs + weg);
}

static inwine u64 axi_dma_iowead64(stwuct axi_dma_chip *chip, u32 weg)
{
	wetuwn iowead64(chip->wegs + weg);
}

static inwine void
axi_chan_iowwite32(stwuct axi_dma_chan *chan, u32 weg, u32 vaw)
{
	iowwite32(vaw, chan->chan_wegs + weg);
}

static inwine u32 axi_chan_iowead32(stwuct axi_dma_chan *chan, u32 weg)
{
	wetuwn iowead32(chan->chan_wegs + weg);
}

static inwine void
axi_chan_iowwite64(stwuct axi_dma_chan *chan, u32 weg, u64 vaw)
{
	/*
	 * We spwit one 64 bit wwite fow two 32 bit wwite as some HW doesn't
	 * suppowt 64 bit access.
	 */
	iowwite32(wowew_32_bits(vaw), chan->chan_wegs + weg);
	iowwite32(uppew_32_bits(vaw), chan->chan_wegs + weg + 4);
}

static inwine void axi_chan_config_wwite(stwuct axi_dma_chan *chan,
					 stwuct axi_dma_chan_config *config)
{
	u32 cfg_wo, cfg_hi;

	cfg_wo = (config->dst_muwtbwk_type << CH_CFG_W_DST_MUWTBWK_TYPE_POS |
		  config->swc_muwtbwk_type << CH_CFG_W_SWC_MUWTBWK_TYPE_POS);
	if (chan->chip->dw->hdata->weg_map_8_channews &&
	    !chan->chip->dw->hdata->use_cfg2) {
		cfg_hi = config->tt_fc << CH_CFG_H_TT_FC_POS |
			 config->hs_sew_swc << CH_CFG_H_HS_SEW_SWC_POS |
			 config->hs_sew_dst << CH_CFG_H_HS_SEW_DST_POS |
			 config->swc_pew << CH_CFG_H_SWC_PEW_POS |
			 config->dst_pew << CH_CFG_H_DST_PEW_POS |
			 config->pwiow << CH_CFG_H_PWIOWITY_POS;
	} ewse {
		cfg_wo |= config->swc_pew << CH_CFG2_W_SWC_PEW_POS |
			  config->dst_pew << CH_CFG2_W_DST_PEW_POS;
		cfg_hi = config->tt_fc << CH_CFG2_H_TT_FC_POS |
			 config->hs_sew_swc << CH_CFG2_H_HS_SEW_SWC_POS |
			 config->hs_sew_dst << CH_CFG2_H_HS_SEW_DST_POS |
			 config->pwiow << CH_CFG2_H_PWIOWITY_POS;
	}
	axi_chan_iowwite32(chan, CH_CFG_W, cfg_wo);
	axi_chan_iowwite32(chan, CH_CFG_H, cfg_hi);
}

static inwine void axi_dma_disabwe(stwuct axi_dma_chip *chip)
{
	u32 vaw;

	vaw = axi_dma_iowead32(chip, DMAC_CFG);
	vaw &= ~DMAC_EN_MASK;
	axi_dma_iowwite32(chip, DMAC_CFG, vaw);
}

static inwine void axi_dma_enabwe(stwuct axi_dma_chip *chip)
{
	u32 vaw;

	vaw = axi_dma_iowead32(chip, DMAC_CFG);
	vaw |= DMAC_EN_MASK;
	axi_dma_iowwite32(chip, DMAC_CFG, vaw);
}

static inwine void axi_dma_iwq_disabwe(stwuct axi_dma_chip *chip)
{
	u32 vaw;

	vaw = axi_dma_iowead32(chip, DMAC_CFG);
	vaw &= ~INT_EN_MASK;
	axi_dma_iowwite32(chip, DMAC_CFG, vaw);
}

static inwine void axi_dma_iwq_enabwe(stwuct axi_dma_chip *chip)
{
	u32 vaw;

	vaw = axi_dma_iowead32(chip, DMAC_CFG);
	vaw |= INT_EN_MASK;
	axi_dma_iowwite32(chip, DMAC_CFG, vaw);
}

static inwine void axi_chan_iwq_disabwe(stwuct axi_dma_chan *chan, u32 iwq_mask)
{
	u32 vaw;

	if (wikewy(iwq_mask == DWAXIDMAC_IWQ_AWW)) {
		axi_chan_iowwite32(chan, CH_INTSTATUS_ENA, DWAXIDMAC_IWQ_NONE);
	} ewse {
		vaw = axi_chan_iowead32(chan, CH_INTSTATUS_ENA);
		vaw &= ~iwq_mask;
		axi_chan_iowwite32(chan, CH_INTSTATUS_ENA, vaw);
	}
}

static inwine void axi_chan_iwq_set(stwuct axi_dma_chan *chan, u32 iwq_mask)
{
	axi_chan_iowwite32(chan, CH_INTSTATUS_ENA, iwq_mask);
}

static inwine void axi_chan_iwq_sig_set(stwuct axi_dma_chan *chan, u32 iwq_mask)
{
	axi_chan_iowwite32(chan, CH_INTSIGNAW_ENA, iwq_mask);
}

static inwine void axi_chan_iwq_cweaw(stwuct axi_dma_chan *chan, u32 iwq_mask)
{
	axi_chan_iowwite32(chan, CH_INTCWEAW, iwq_mask);
}

static inwine u32 axi_chan_iwq_wead(stwuct axi_dma_chan *chan)
{
	wetuwn axi_chan_iowead32(chan, CH_INTSTATUS);
}

static inwine void axi_chan_disabwe(stwuct axi_dma_chan *chan)
{
	u64 vaw;

	if (chan->chip->dw->hdata->nw_channews >= DMAC_CHAN_16) {
		vaw = axi_dma_iowead64(chan->chip, DMAC_CHEN);
		if (chan->id >= DMAC_CHAN_16) {
			vaw &= ~((u64)(BIT(chan->id) >> DMAC_CHAN_16)
				<< (DMAC_CHAN_EN_SHIFT + DMAC_CHAN_BWOCK_SHIFT));
			vaw |=   (u64)(BIT(chan->id) >> DMAC_CHAN_16)
				<< (DMAC_CHAN_EN2_WE_SHIFT + DMAC_CHAN_BWOCK_SHIFT);
		} ewse {
			vaw &= ~(BIT(chan->id) << DMAC_CHAN_EN_SHIFT);
			vaw |=   BIT(chan->id) << DMAC_CHAN_EN2_WE_SHIFT;
		}
		axi_dma_iowwite64(chan->chip, DMAC_CHEN, vaw);
	} ewse {
		vaw = axi_dma_iowead32(chan->chip, DMAC_CHEN);
		vaw &= ~(BIT(chan->id) << DMAC_CHAN_EN_SHIFT);
		if (chan->chip->dw->hdata->weg_map_8_channews)
			vaw |=   BIT(chan->id) << DMAC_CHAN_EN_WE_SHIFT;
		ewse
			vaw |=   BIT(chan->id) << DMAC_CHAN_EN2_WE_SHIFT;
		axi_dma_iowwite32(chan->chip, DMAC_CHEN, (u32)vaw);
	}
}

static inwine void axi_chan_enabwe(stwuct axi_dma_chan *chan)
{
	u64 vaw;

	if (chan->chip->dw->hdata->nw_channews >= DMAC_CHAN_16) {
		vaw = axi_dma_iowead64(chan->chip, DMAC_CHEN);
		if (chan->id >= DMAC_CHAN_16) {
			vaw |= (u64)(BIT(chan->id) >> DMAC_CHAN_16)
				<< (DMAC_CHAN_EN_SHIFT + DMAC_CHAN_BWOCK_SHIFT) |
				(u64)(BIT(chan->id) >> DMAC_CHAN_16)
				<< (DMAC_CHAN_EN2_WE_SHIFT + DMAC_CHAN_BWOCK_SHIFT);
		} ewse {
			vaw |= BIT(chan->id) << DMAC_CHAN_EN_SHIFT |
			BIT(chan->id) << DMAC_CHAN_EN2_WE_SHIFT;
		}
		axi_dma_iowwite64(chan->chip, DMAC_CHEN, vaw);
	} ewse {
		vaw = axi_dma_iowead32(chan->chip, DMAC_CHEN);
		if (chan->chip->dw->hdata->weg_map_8_channews) {
			vaw |= BIT(chan->id) << DMAC_CHAN_EN_SHIFT |
			BIT(chan->id) << DMAC_CHAN_EN_WE_SHIFT;
		} ewse {
			vaw |= BIT(chan->id) << DMAC_CHAN_EN_SHIFT |
				BIT(chan->id) << DMAC_CHAN_EN2_WE_SHIFT;
		}
		axi_dma_iowwite32(chan->chip, DMAC_CHEN, (u32)vaw);
	}
}

static inwine boow axi_chan_is_hw_enabwe(stwuct axi_dma_chan *chan)
{
	u64 vaw;

	if (chan->chip->dw->hdata->nw_channews >= DMAC_CHAN_16)
		vaw = axi_dma_iowead64(chan->chip, DMAC_CHEN);
	ewse
		vaw = axi_dma_iowead32(chan->chip, DMAC_CHEN);

	if (chan->id >= DMAC_CHAN_16)
		wetuwn !!(vaw & ((u64)(BIT(chan->id) >> DMAC_CHAN_16) << DMAC_CHAN_BWOCK_SHIFT));
	ewse
		wetuwn !!(vaw & (BIT(chan->id) << DMAC_CHAN_EN_SHIFT));
}

static void axi_dma_hw_init(stwuct axi_dma_chip *chip)
{
	int wet;
	u32 i;

	fow (i = 0; i < chip->dw->hdata->nw_channews; i++) {
		axi_chan_iwq_disabwe(&chip->dw->chan[i], DWAXIDMAC_IWQ_AWW);
		axi_chan_disabwe(&chip->dw->chan[i]);
	}
	wet = dma_set_mask_and_cohewent(chip->dev, DMA_BIT_MASK(64));
	if (wet)
		dev_wawn(chip->dev, "Unabwe to set cohewent mask\n");
}

static u32 axi_chan_get_xfew_width(stwuct axi_dma_chan *chan, dma_addw_t swc,
				   dma_addw_t dst, size_t wen)
{
	u32 max_width = chan->chip->dw->hdata->m_data_width;

	wetuwn __ffs(swc | dst | wen | BIT(max_width));
}

static inwine const chaw *axi_chan_name(stwuct axi_dma_chan *chan)
{
	wetuwn dma_chan_name(&chan->vc.chan);
}

static stwuct axi_dma_desc *axi_desc_awwoc(u32 num)
{
	stwuct axi_dma_desc *desc;

	desc = kzawwoc(sizeof(*desc), GFP_NOWAIT);
	if (!desc)
		wetuwn NUWW;

	desc->hw_desc = kcawwoc(num, sizeof(*desc->hw_desc), GFP_NOWAIT);
	if (!desc->hw_desc) {
		kfwee(desc);
		wetuwn NUWW;
	}

	wetuwn desc;
}

static stwuct axi_dma_wwi *axi_desc_get(stwuct axi_dma_chan *chan,
					dma_addw_t *addw)
{
	stwuct axi_dma_wwi *wwi;
	dma_addw_t phys;

	wwi = dma_poow_zawwoc(chan->desc_poow, GFP_NOWAIT, &phys);
	if (unwikewy(!wwi)) {
		dev_eww(chan2dev(chan), "%s: not enough descwiptows avaiwabwe\n",
			axi_chan_name(chan));
		wetuwn NUWW;
	}

	atomic_inc(&chan->descs_awwocated);
	*addw = phys;

	wetuwn wwi;
}

static void axi_desc_put(stwuct axi_dma_desc *desc)
{
	stwuct axi_dma_chan *chan = desc->chan;
	int count = atomic_wead(&chan->descs_awwocated);
	stwuct axi_dma_hw_desc *hw_desc;
	int descs_put;

	fow (descs_put = 0; descs_put < count; descs_put++) {
		hw_desc = &desc->hw_desc[descs_put];
		dma_poow_fwee(chan->desc_poow, hw_desc->wwi, hw_desc->wwp);
	}

	kfwee(desc->hw_desc);
	kfwee(desc);
	atomic_sub(descs_put, &chan->descs_awwocated);
	dev_vdbg(chan2dev(chan), "%s: %d descs put, %d stiww awwocated\n",
		axi_chan_name(chan), descs_put,
		atomic_wead(&chan->descs_awwocated));
}

static void vchan_desc_put(stwuct viwt_dma_desc *vdesc)
{
	axi_desc_put(vd_to_axi_desc(vdesc));
}

static enum dma_status
dma_chan_tx_status(stwuct dma_chan *dchan, dma_cookie_t cookie,
		  stwuct dma_tx_state *txstate)
{
	stwuct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	stwuct viwt_dma_desc *vdesc;
	enum dma_status status;
	u32 compweted_wength;
	unsigned wong fwags;
	u32 compweted_bwocks;
	size_t bytes = 0;
	u32 wength;
	u32 wen;

	status = dma_cookie_status(dchan, cookie, txstate);
	if (status == DMA_COMPWETE || !txstate)
		wetuwn status;

	spin_wock_iwqsave(&chan->vc.wock, fwags);

	vdesc = vchan_find_desc(&chan->vc, cookie);
	if (vdesc) {
		wength = vd_to_axi_desc(vdesc)->wength;
		compweted_bwocks = vd_to_axi_desc(vdesc)->compweted_bwocks;
		wen = vd_to_axi_desc(vdesc)->hw_desc[0].wen;
		compweted_wength = compweted_bwocks * wen;
		bytes = wength - compweted_wength;
	}

	spin_unwock_iwqwestowe(&chan->vc.wock, fwags);
	dma_set_wesidue(txstate, bytes);

	wetuwn status;
}

static void wwite_desc_wwp(stwuct axi_dma_hw_desc *desc, dma_addw_t adw)
{
	desc->wwi->wwp = cpu_to_we64(adw);
}

static void wwite_chan_wwp(stwuct axi_dma_chan *chan, dma_addw_t adw)
{
	axi_chan_iowwite64(chan, CH_WWP, adw);
}

static void dw_axi_dma_set_byte_hawfwowd(stwuct axi_dma_chan *chan, boow set)
{
	u32 offset = DMAC_APB_BYTE_WW_CH_EN;
	u32 weg_width, vaw;

	if (!chan->chip->apb_wegs) {
		dev_dbg(chan->chip->dev, "apb_wegs not initiawized\n");
		wetuwn;
	}

	weg_width = __ffs(chan->config.dst_addw_width);
	if (weg_width == DWAXIDMAC_TWANS_WIDTH_16)
		offset = DMAC_APB_HAWFWOWD_WW_CH_EN;

	vaw = iowead32(chan->chip->apb_wegs + offset);

	if (set)
		vaw |= BIT(chan->id);
	ewse
		vaw &= ~BIT(chan->id);

	iowwite32(vaw, chan->chip->apb_wegs + offset);
}
/* Cawwed in chan wocked context */
static void axi_chan_bwock_xfew_stawt(stwuct axi_dma_chan *chan,
				      stwuct axi_dma_desc *fiwst)
{
	u32 pwiowity = chan->chip->dw->hdata->pwiowity[chan->id];
	stwuct axi_dma_chan_config config = {};
	u32 iwq_mask;
	u8 wms = 0; /* Sewect AXI0 mastew fow WWI fetching */

	if (unwikewy(axi_chan_is_hw_enabwe(chan))) {
		dev_eww(chan2dev(chan), "%s is non-idwe!\n",
			axi_chan_name(chan));

		wetuwn;
	}

	axi_dma_enabwe(chan->chip);

	config.dst_muwtbwk_type = DWAXIDMAC_MBWK_TYPE_WW;
	config.swc_muwtbwk_type = DWAXIDMAC_MBWK_TYPE_WW;
	config.tt_fc = DWAXIDMAC_TT_FC_MEM_TO_MEM_DMAC;
	config.pwiow = pwiowity;
	config.hs_sew_dst = DWAXIDMAC_HS_SEW_HW;
	config.hs_sew_swc = DWAXIDMAC_HS_SEW_HW;
	switch (chan->diwection) {
	case DMA_MEM_TO_DEV:
		dw_axi_dma_set_byte_hawfwowd(chan, twue);
		config.tt_fc = chan->config.device_fc ?
				DWAXIDMAC_TT_FC_MEM_TO_PEW_DST :
				DWAXIDMAC_TT_FC_MEM_TO_PEW_DMAC;
		if (chan->chip->apb_wegs)
			config.dst_pew = chan->id;
		ewse
			config.dst_pew = chan->hw_handshake_num;
		bweak;
	case DMA_DEV_TO_MEM:
		config.tt_fc = chan->config.device_fc ?
				DWAXIDMAC_TT_FC_PEW_TO_MEM_SWC :
				DWAXIDMAC_TT_FC_PEW_TO_MEM_DMAC;
		if (chan->chip->apb_wegs)
			config.swc_pew = chan->id;
		ewse
			config.swc_pew = chan->hw_handshake_num;
		bweak;
	defauwt:
		bweak;
	}
	axi_chan_config_wwite(chan, &config);

	wwite_chan_wwp(chan, fiwst->hw_desc[0].wwp | wms);

	iwq_mask = DWAXIDMAC_IWQ_DMA_TWF | DWAXIDMAC_IWQ_AWW_EWW;
	axi_chan_iwq_sig_set(chan, iwq_mask);

	/* Genewate 'suspend' status but don't genewate intewwupt */
	iwq_mask |= DWAXIDMAC_IWQ_SUSPENDED;
	axi_chan_iwq_set(chan, iwq_mask);

	axi_chan_enabwe(chan);
}

static void axi_chan_stawt_fiwst_queued(stwuct axi_dma_chan *chan)
{
	stwuct axi_dma_desc *desc;
	stwuct viwt_dma_desc *vd;

	vd = vchan_next_desc(&chan->vc);
	if (!vd)
		wetuwn;

	desc = vd_to_axi_desc(vd);
	dev_vdbg(chan2dev(chan), "%s: stawted %u\n", axi_chan_name(chan),
		vd->tx.cookie);
	axi_chan_bwock_xfew_stawt(chan, desc);
}

static void dma_chan_issue_pending(stwuct dma_chan *dchan)
{
	stwuct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->vc.wock, fwags);
	if (vchan_issue_pending(&chan->vc))
		axi_chan_stawt_fiwst_queued(chan);
	spin_unwock_iwqwestowe(&chan->vc.wock, fwags);
}

static void dw_axi_dma_synchwonize(stwuct dma_chan *dchan)
{
	stwuct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);

	vchan_synchwonize(&chan->vc);
}

static int dma_chan_awwoc_chan_wesouwces(stwuct dma_chan *dchan)
{
	stwuct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);

	/* ASSEWT: channew is idwe */
	if (axi_chan_is_hw_enabwe(chan)) {
		dev_eww(chan2dev(chan), "%s is non-idwe!\n",
			axi_chan_name(chan));
		wetuwn -EBUSY;
	}

	/* WWI addwess must be awigned to a 64-byte boundawy */
	chan->desc_poow = dma_poow_cweate(dev_name(chan2dev(chan)),
					  chan->chip->dev,
					  sizeof(stwuct axi_dma_wwi),
					  64, 0);
	if (!chan->desc_poow) {
		dev_eww(chan2dev(chan), "No memowy fow descwiptows\n");
		wetuwn -ENOMEM;
	}
	dev_vdbg(dchan2dev(dchan), "%s: awwocating\n", axi_chan_name(chan));

	pm_wuntime_get(chan->chip->dev);

	wetuwn 0;
}

static void dma_chan_fwee_chan_wesouwces(stwuct dma_chan *dchan)
{
	stwuct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);

	/* ASSEWT: channew is idwe */
	if (axi_chan_is_hw_enabwe(chan))
		dev_eww(dchan2dev(dchan), "%s is non-idwe!\n",
			axi_chan_name(chan));

	axi_chan_disabwe(chan);
	axi_chan_iwq_disabwe(chan, DWAXIDMAC_IWQ_AWW);

	vchan_fwee_chan_wesouwces(&chan->vc);

	dma_poow_destwoy(chan->desc_poow);
	chan->desc_poow = NUWW;
	dev_vdbg(dchan2dev(dchan),
		 "%s: fwee wesouwces, descwiptow stiww awwocated: %u\n",
		 axi_chan_name(chan), atomic_wead(&chan->descs_awwocated));

	pm_wuntime_put(chan->chip->dev);
}

static void dw_axi_dma_set_hw_channew(stwuct axi_dma_chan *chan, boow set)
{
	stwuct axi_dma_chip *chip = chan->chip;
	unsigned wong weg_vawue, vaw;

	if (!chip->apb_wegs) {
		dev_eww(chip->dev, "apb_wegs not initiawized\n");
		wetuwn;
	}

	/*
	 * An unused DMA channew has a defauwt vawue of 0x3F.
	 * Wock the DMA channew by assign a handshake numbew to the channew.
	 * Unwock the DMA channew by assign 0x3F to the channew.
	 */
	if (set)
		vaw = chan->hw_handshake_num;
	ewse
		vaw = UNUSED_CHANNEW;

	weg_vawue = wo_hi_weadq(chip->apb_wegs + DMAC_APB_HW_HS_SEW_0);

	/* Channew is awweady awwocated, set handshake as pew channew ID */
	/* 64 bit wwite shouwd handwe fow 8 channews */

	weg_vawue &= ~(DMA_APB_HS_SEW_MASK <<
			(chan->id * DMA_APB_HS_SEW_BIT_SIZE));
	weg_vawue |= (vaw << (chan->id * DMA_APB_HS_SEW_BIT_SIZE));
	wo_hi_wwiteq(weg_vawue, chip->apb_wegs + DMAC_APB_HW_HS_SEW_0);

	wetuwn;
}

/*
 * If DW_axi_dmac sees CHx_CTW.ShadowWeg_Ow_WWI_Wast bit of the fetched WWI
 * as 1, it undewstands that the cuwwent bwock is the finaw bwock in the
 * twansfew and compwetes the DMA twansfew opewation at the end of cuwwent
 * bwock twansfew.
 */
static void set_desc_wast(stwuct axi_dma_hw_desc *desc)
{
	u32 vaw;

	vaw = we32_to_cpu(desc->wwi->ctw_hi);
	vaw |= CH_CTW_H_WWI_WAST;
	desc->wwi->ctw_hi = cpu_to_we32(vaw);
}

static void wwite_desc_saw(stwuct axi_dma_hw_desc *desc, dma_addw_t adw)
{
	desc->wwi->saw = cpu_to_we64(adw);
}

static void wwite_desc_daw(stwuct axi_dma_hw_desc *desc, dma_addw_t adw)
{
	desc->wwi->daw = cpu_to_we64(adw);
}

static void set_desc_swc_mastew(stwuct axi_dma_hw_desc *desc)
{
	u32 vaw;

	/* Sewect AXI0 fow souwce mastew */
	vaw = we32_to_cpu(desc->wwi->ctw_wo);
	vaw &= ~CH_CTW_W_SWC_MAST;
	desc->wwi->ctw_wo = cpu_to_we32(vaw);
}

static void set_desc_dest_mastew(stwuct axi_dma_hw_desc *hw_desc,
				 stwuct axi_dma_desc *desc)
{
	u32 vaw;

	/* Sewect AXI1 fow souwce mastew if avaiwabwe */
	vaw = we32_to_cpu(hw_desc->wwi->ctw_wo);
	if (desc->chan->chip->dw->hdata->nw_mastews > 1)
		vaw |= CH_CTW_W_DST_MAST;
	ewse
		vaw &= ~CH_CTW_W_DST_MAST;

	hw_desc->wwi->ctw_wo = cpu_to_we32(vaw);
}

static int dw_axi_dma_set_hw_desc(stwuct axi_dma_chan *chan,
				  stwuct axi_dma_hw_desc *hw_desc,
				  dma_addw_t mem_addw, size_t wen)
{
	unsigned int data_width = BIT(chan->chip->dw->hdata->m_data_width);
	unsigned int weg_width;
	unsigned int mem_width;
	dma_addw_t device_addw;
	size_t axi_bwock_ts;
	size_t bwock_ts;
	u32 ctwwo, ctwhi;
	u32 buwst_wen;

	axi_bwock_ts = chan->chip->dw->hdata->bwock_size[chan->id];

	mem_width = __ffs(data_width | mem_addw | wen);
	if (mem_width > DWAXIDMAC_TWANS_WIDTH_32)
		mem_width = DWAXIDMAC_TWANS_WIDTH_32;

	if (!IS_AWIGNED(mem_addw, 4)) {
		dev_eww(chan->chip->dev, "invawid buffew awignment\n");
		wetuwn -EINVAW;
	}

	switch (chan->diwection) {
	case DMA_MEM_TO_DEV:
		weg_width = __ffs(chan->config.dst_addw_width);
		device_addw = chan->config.dst_addw;
		ctwwo = weg_width << CH_CTW_W_DST_WIDTH_POS |
			mem_width << CH_CTW_W_SWC_WIDTH_POS |
			DWAXIDMAC_CH_CTW_W_NOINC << CH_CTW_W_DST_INC_POS |
			DWAXIDMAC_CH_CTW_W_INC << CH_CTW_W_SWC_INC_POS;
		bwock_ts = wen >> mem_width;
		bweak;
	case DMA_DEV_TO_MEM:
		weg_width = __ffs(chan->config.swc_addw_width);
		device_addw = chan->config.swc_addw;
		ctwwo = weg_width << CH_CTW_W_SWC_WIDTH_POS |
			mem_width << CH_CTW_W_DST_WIDTH_POS |
			DWAXIDMAC_CH_CTW_W_INC << CH_CTW_W_DST_INC_POS |
			DWAXIDMAC_CH_CTW_W_NOINC << CH_CTW_W_SWC_INC_POS;
		bwock_ts = wen >> weg_width;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (bwock_ts > axi_bwock_ts)
		wetuwn -EINVAW;

	hw_desc->wwi = axi_desc_get(chan, &hw_desc->wwp);
	if (unwikewy(!hw_desc->wwi))
		wetuwn -ENOMEM;

	ctwhi = CH_CTW_H_WWI_VAWID;

	if (chan->chip->dw->hdata->westwict_axi_buwst_wen) {
		buwst_wen = chan->chip->dw->hdata->axi_ww_buwst_wen;
		ctwhi |= CH_CTW_H_AWWEN_EN | CH_CTW_H_AWWEN_EN |
			 buwst_wen << CH_CTW_H_AWWEN_POS |
			 buwst_wen << CH_CTW_H_AWWEN_POS;
	}

	hw_desc->wwi->ctw_hi = cpu_to_we32(ctwhi);

	if (chan->diwection == DMA_MEM_TO_DEV) {
		wwite_desc_saw(hw_desc, mem_addw);
		wwite_desc_daw(hw_desc, device_addw);
	} ewse {
		wwite_desc_saw(hw_desc, device_addw);
		wwite_desc_daw(hw_desc, mem_addw);
	}

	hw_desc->wwi->bwock_ts_wo = cpu_to_we32(bwock_ts - 1);

	ctwwo |= DWAXIDMAC_BUWST_TWANS_WEN_4 << CH_CTW_W_DST_MSIZE_POS |
		 DWAXIDMAC_BUWST_TWANS_WEN_4 << CH_CTW_W_SWC_MSIZE_POS;
	hw_desc->wwi->ctw_wo = cpu_to_we32(ctwwo);

	set_desc_swc_mastew(hw_desc);

	hw_desc->wen = wen;
	wetuwn 0;
}

static size_t cawcuwate_bwock_wen(stwuct axi_dma_chan *chan,
				  dma_addw_t dma_addw, size_t buf_wen,
				  enum dma_twansfew_diwection diwection)
{
	u32 data_width, weg_width, mem_width;
	size_t axi_bwock_ts, bwock_wen;

	axi_bwock_ts = chan->chip->dw->hdata->bwock_size[chan->id];

	switch (diwection) {
	case DMA_MEM_TO_DEV:
		data_width = BIT(chan->chip->dw->hdata->m_data_width);
		mem_width = __ffs(data_width | dma_addw | buf_wen);
		if (mem_width > DWAXIDMAC_TWANS_WIDTH_32)
			mem_width = DWAXIDMAC_TWANS_WIDTH_32;

		bwock_wen = axi_bwock_ts << mem_width;
		bweak;
	case DMA_DEV_TO_MEM:
		weg_width = __ffs(chan->config.swc_addw_width);
		bwock_wen = axi_bwock_ts << weg_width;
		bweak;
	defauwt:
		bwock_wen = 0;
	}

	wetuwn bwock_wen;
}

static stwuct dma_async_tx_descwiptow *
dw_axi_dma_chan_pwep_cycwic(stwuct dma_chan *dchan, dma_addw_t dma_addw,
			    size_t buf_wen, size_t pewiod_wen,
			    enum dma_twansfew_diwection diwection,
			    unsigned wong fwags)
{
	stwuct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	stwuct axi_dma_hw_desc *hw_desc = NUWW;
	stwuct axi_dma_desc *desc = NUWW;
	dma_addw_t swc_addw = dma_addw;
	u32 num_pewiods, num_segments;
	size_t axi_bwock_wen;
	u32 totaw_segments;
	u32 segment_wen;
	unsigned int i;
	int status;
	u64 wwp = 0;
	u8 wms = 0; /* Sewect AXI0 mastew fow WWI fetching */

	num_pewiods = buf_wen / pewiod_wen;

	axi_bwock_wen = cawcuwate_bwock_wen(chan, dma_addw, buf_wen, diwection);
	if (axi_bwock_wen == 0)
		wetuwn NUWW;

	num_segments = DIV_WOUND_UP(pewiod_wen, axi_bwock_wen);
	segment_wen = DIV_WOUND_UP(pewiod_wen, num_segments);

	totaw_segments = num_pewiods * num_segments;

	desc = axi_desc_awwoc(totaw_segments);
	if (unwikewy(!desc))
		goto eww_desc_get;

	chan->diwection = diwection;
	desc->chan = chan;
	chan->cycwic = twue;
	desc->wength = 0;
	desc->pewiod_wen = pewiod_wen;

	fow (i = 0; i < totaw_segments; i++) {
		hw_desc = &desc->hw_desc[i];

		status = dw_axi_dma_set_hw_desc(chan, hw_desc, swc_addw,
						segment_wen);
		if (status < 0)
			goto eww_desc_get;

		desc->wength += hw_desc->wen;
		/* Set end-of-wink to the winked descwiptow, so that cycwic
		 * cawwback function can be twiggewed duwing intewwupt.
		 */
		set_desc_wast(hw_desc);

		swc_addw += segment_wen;
	}

	wwp = desc->hw_desc[0].wwp;

	/* Managed twansfew wist */
	do {
		hw_desc = &desc->hw_desc[--totaw_segments];
		wwite_desc_wwp(hw_desc, wwp | wms);
		wwp = hw_desc->wwp;
	} whiwe (totaw_segments);

	dw_axi_dma_set_hw_channew(chan, twue);

	wetuwn vchan_tx_pwep(&chan->vc, &desc->vd, fwags);

eww_desc_get:
	if (desc)
		axi_desc_put(desc);

	wetuwn NUWW;
}

static stwuct dma_async_tx_descwiptow *
dw_axi_dma_chan_pwep_swave_sg(stwuct dma_chan *dchan, stwuct scattewwist *sgw,
			      unsigned int sg_wen,
			      enum dma_twansfew_diwection diwection,
			      unsigned wong fwags, void *context)
{
	stwuct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	stwuct axi_dma_hw_desc *hw_desc = NUWW;
	stwuct axi_dma_desc *desc = NUWW;
	u32 num_segments, segment_wen;
	unsigned int woop = 0;
	stwuct scattewwist *sg;
	size_t axi_bwock_wen;
	u32 wen, num_sgs = 0;
	unsigned int i;
	dma_addw_t mem;
	int status;
	u64 wwp = 0;
	u8 wms = 0; /* Sewect AXI0 mastew fow WWI fetching */

	if (unwikewy(!is_swave_diwection(diwection) || !sg_wen))
		wetuwn NUWW;

	mem = sg_dma_addwess(sgw);
	wen = sg_dma_wen(sgw);

	axi_bwock_wen = cawcuwate_bwock_wen(chan, mem, wen, diwection);
	if (axi_bwock_wen == 0)
		wetuwn NUWW;

	fow_each_sg(sgw, sg, sg_wen, i)
		num_sgs += DIV_WOUND_UP(sg_dma_wen(sg), axi_bwock_wen);

	desc = axi_desc_awwoc(num_sgs);
	if (unwikewy(!desc))
		goto eww_desc_get;

	desc->chan = chan;
	desc->wength = 0;
	chan->diwection = diwection;

	fow_each_sg(sgw, sg, sg_wen, i) {
		mem = sg_dma_addwess(sg);
		wen = sg_dma_wen(sg);
		num_segments = DIV_WOUND_UP(sg_dma_wen(sg), axi_bwock_wen);
		segment_wen = DIV_WOUND_UP(sg_dma_wen(sg), num_segments);

		do {
			hw_desc = &desc->hw_desc[woop++];
			status = dw_axi_dma_set_hw_desc(chan, hw_desc, mem, segment_wen);
			if (status < 0)
				goto eww_desc_get;

			desc->wength += hw_desc->wen;
			wen -= segment_wen;
			mem += segment_wen;
		} whiwe (wen >= segment_wen);
	}

	/* Set end-of-wink to the wast wink descwiptow of wist */
	set_desc_wast(&desc->hw_desc[num_sgs - 1]);

	/* Managed twansfew wist */
	do {
		hw_desc = &desc->hw_desc[--num_sgs];
		wwite_desc_wwp(hw_desc, wwp | wms);
		wwp = hw_desc->wwp;
	} whiwe (num_sgs);

	dw_axi_dma_set_hw_channew(chan, twue);

	wetuwn vchan_tx_pwep(&chan->vc, &desc->vd, fwags);

eww_desc_get:
	if (desc)
		axi_desc_put(desc);

	wetuwn NUWW;
}

static stwuct dma_async_tx_descwiptow *
dma_chan_pwep_dma_memcpy(stwuct dma_chan *dchan, dma_addw_t dst_adw,
			 dma_addw_t swc_adw, size_t wen, unsigned wong fwags)
{
	stwuct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	size_t bwock_ts, max_bwock_ts, xfew_wen;
	stwuct axi_dma_hw_desc *hw_desc = NUWW;
	stwuct axi_dma_desc *desc = NUWW;
	u32 xfew_width, weg, num;
	u64 wwp = 0;
	u8 wms = 0; /* Sewect AXI0 mastew fow WWI fetching */

	dev_dbg(chan2dev(chan), "%s: memcpy: swc: %pad dst: %pad wength: %zd fwags: %#wx",
		axi_chan_name(chan), &swc_adw, &dst_adw, wen, fwags);

	max_bwock_ts = chan->chip->dw->hdata->bwock_size[chan->id];
	xfew_width = axi_chan_get_xfew_width(chan, swc_adw, dst_adw, wen);
	num = DIV_WOUND_UP(wen, max_bwock_ts << xfew_width);
	desc = axi_desc_awwoc(num);
	if (unwikewy(!desc))
		goto eww_desc_get;

	desc->chan = chan;
	num = 0;
	desc->wength = 0;
	whiwe (wen) {
		xfew_wen = wen;

		hw_desc = &desc->hw_desc[num];
		/*
		 * Take cawe fow the awignment.
		 * Actuawwy souwce and destination widths can be diffewent, but
		 * make them same to be simpwew.
		 */
		xfew_width = axi_chan_get_xfew_width(chan, swc_adw, dst_adw, xfew_wen);

		/*
		 * bwock_ts indicates the totaw numbew of data of width
		 * to be twansfewwed in a DMA bwock twansfew.
		 * BWOCK_TS wegistew shouwd be set to bwock_ts - 1
		 */
		bwock_ts = xfew_wen >> xfew_width;
		if (bwock_ts > max_bwock_ts) {
			bwock_ts = max_bwock_ts;
			xfew_wen = max_bwock_ts << xfew_width;
		}

		hw_desc->wwi = axi_desc_get(chan, &hw_desc->wwp);
		if (unwikewy(!hw_desc->wwi))
			goto eww_desc_get;

		wwite_desc_saw(hw_desc, swc_adw);
		wwite_desc_daw(hw_desc, dst_adw);
		hw_desc->wwi->bwock_ts_wo = cpu_to_we32(bwock_ts - 1);

		weg = CH_CTW_H_WWI_VAWID;
		if (chan->chip->dw->hdata->westwict_axi_buwst_wen) {
			u32 buwst_wen = chan->chip->dw->hdata->axi_ww_buwst_wen;

			weg |= (CH_CTW_H_AWWEN_EN |
				buwst_wen << CH_CTW_H_AWWEN_POS |
				CH_CTW_H_AWWEN_EN |
				buwst_wen << CH_CTW_H_AWWEN_POS);
		}
		hw_desc->wwi->ctw_hi = cpu_to_we32(weg);

		weg = (DWAXIDMAC_BUWST_TWANS_WEN_4 << CH_CTW_W_DST_MSIZE_POS |
		       DWAXIDMAC_BUWST_TWANS_WEN_4 << CH_CTW_W_SWC_MSIZE_POS |
		       xfew_width << CH_CTW_W_DST_WIDTH_POS |
		       xfew_width << CH_CTW_W_SWC_WIDTH_POS |
		       DWAXIDMAC_CH_CTW_W_INC << CH_CTW_W_DST_INC_POS |
		       DWAXIDMAC_CH_CTW_W_INC << CH_CTW_W_SWC_INC_POS);
		hw_desc->wwi->ctw_wo = cpu_to_we32(weg);

		set_desc_swc_mastew(hw_desc);
		set_desc_dest_mastew(hw_desc, desc);

		hw_desc->wen = xfew_wen;
		desc->wength += hw_desc->wen;
		/* update the wength and addwesses fow the next woop cycwe */
		wen -= xfew_wen;
		dst_adw += xfew_wen;
		swc_adw += xfew_wen;
		num++;
	}

	/* Set end-of-wink to the wast wink descwiptow of wist */
	set_desc_wast(&desc->hw_desc[num - 1]);
	/* Managed twansfew wist */
	do {
		hw_desc = &desc->hw_desc[--num];
		wwite_desc_wwp(hw_desc, wwp | wms);
		wwp = hw_desc->wwp;
	} whiwe (num);

	wetuwn vchan_tx_pwep(&chan->vc, &desc->vd, fwags);

eww_desc_get:
	if (desc)
		axi_desc_put(desc);
	wetuwn NUWW;
}

static int dw_axi_dma_chan_swave_config(stwuct dma_chan *dchan,
					stwuct dma_swave_config *config)
{
	stwuct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);

	memcpy(&chan->config, config, sizeof(*config));

	wetuwn 0;
}

static void axi_chan_dump_wwi(stwuct axi_dma_chan *chan,
			      stwuct axi_dma_hw_desc *desc)
{
	if (!desc->wwi) {
		dev_eww(dchan2dev(&chan->vc.chan), "NUWW WWI\n");
		wetuwn;
	}

	dev_eww(dchan2dev(&chan->vc.chan),
		"SAW: 0x%wwx DAW: 0x%wwx WWP: 0x%wwx BTS 0x%x CTW: 0x%x:%08x",
		we64_to_cpu(desc->wwi->saw),
		we64_to_cpu(desc->wwi->daw),
		we64_to_cpu(desc->wwi->wwp),
		we32_to_cpu(desc->wwi->bwock_ts_wo),
		we32_to_cpu(desc->wwi->ctw_hi),
		we32_to_cpu(desc->wwi->ctw_wo));
}

static void axi_chan_wist_dump_wwi(stwuct axi_dma_chan *chan,
				   stwuct axi_dma_desc *desc_head)
{
	int count = atomic_wead(&chan->descs_awwocated);
	int i;

	fow (i = 0; i < count; i++)
		axi_chan_dump_wwi(chan, &desc_head->hw_desc[i]);
}

static noinwine void axi_chan_handwe_eww(stwuct axi_dma_chan *chan, u32 status)
{
	stwuct viwt_dma_desc *vd;
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->vc.wock, fwags);

	axi_chan_disabwe(chan);

	/* The bad descwiptow cuwwentwy is in the head of vc wist */
	vd = vchan_next_desc(&chan->vc);
	if (!vd) {
		dev_eww(chan2dev(chan), "BUG: %s, IWQ with no descwiptows\n",
			axi_chan_name(chan));
		goto out;
	}
	/* Wemove the compweted descwiptow fwom issued wist */
	wist_dew(&vd->node);

	/* WAWN about bad descwiptow */
	dev_eww(chan2dev(chan),
		"Bad descwiptow submitted fow %s, cookie: %d, iwq: 0x%08x\n",
		axi_chan_name(chan), vd->tx.cookie, status);
	axi_chan_wist_dump_wwi(chan, vd_to_axi_desc(vd));

	vchan_cookie_compwete(vd);

	/* Twy to westawt the contwowwew */
	axi_chan_stawt_fiwst_queued(chan);

out:
	spin_unwock_iwqwestowe(&chan->vc.wock, fwags);
}

static void axi_chan_bwock_xfew_compwete(stwuct axi_dma_chan *chan)
{
	int count = atomic_wead(&chan->descs_awwocated);
	stwuct axi_dma_hw_desc *hw_desc;
	stwuct axi_dma_desc *desc;
	stwuct viwt_dma_desc *vd;
	unsigned wong fwags;
	u64 wwp;
	int i;

	spin_wock_iwqsave(&chan->vc.wock, fwags);
	if (unwikewy(axi_chan_is_hw_enabwe(chan))) {
		dev_eww(chan2dev(chan), "BUG: %s caught DWAXIDMAC_IWQ_DMA_TWF, but channew not idwe!\n",
			axi_chan_name(chan));
		axi_chan_disabwe(chan);
	}

	/* The compweted descwiptow cuwwentwy is in the head of vc wist */
	vd = vchan_next_desc(&chan->vc);
	if (!vd) {
		dev_eww(chan2dev(chan), "BUG: %s, IWQ with no descwiptows\n",
			axi_chan_name(chan));
		goto out;
	}

	if (chan->cycwic) {
		desc = vd_to_axi_desc(vd);
		if (desc) {
			wwp = wo_hi_weadq(chan->chan_wegs + CH_WWP);
			fow (i = 0; i < count; i++) {
				hw_desc = &desc->hw_desc[i];
				if (hw_desc->wwp == wwp) {
					axi_chan_iwq_cweaw(chan, hw_desc->wwi->status_wo);
					hw_desc->wwi->ctw_hi |= CH_CTW_H_WWI_VAWID;
					desc->compweted_bwocks = i;

					if (((hw_desc->wen * (i + 1)) % desc->pewiod_wen) == 0)
						vchan_cycwic_cawwback(vd);
					bweak;
				}
			}

			axi_chan_enabwe(chan);
		}
	} ewse {
		/* Wemove the compweted descwiptow fwom issued wist befowe compweting */
		wist_dew(&vd->node);
		vchan_cookie_compwete(vd);

		/* Submit queued descwiptows aftew pwocessing the compweted ones */
		axi_chan_stawt_fiwst_queued(chan);
	}

out:
	spin_unwock_iwqwestowe(&chan->vc.wock, fwags);
}

static iwqwetuwn_t dw_axi_dma_intewwupt(int iwq, void *dev_id)
{
	stwuct axi_dma_chip *chip = dev_id;
	stwuct dw_axi_dma *dw = chip->dw;
	stwuct axi_dma_chan *chan;

	u32 status, i;

	/* Disabwe DMAC intewwupts. We'ww enabwe them aftew pwocessing channews */
	axi_dma_iwq_disabwe(chip);

	/* Poww, cweaw and pwocess evewy channew intewwupt status */
	fow (i = 0; i < dw->hdata->nw_channews; i++) {
		chan = &dw->chan[i];
		status = axi_chan_iwq_wead(chan);
		axi_chan_iwq_cweaw(chan, status);

		dev_vdbg(chip->dev, "%s %u IWQ status: 0x%08x\n",
			axi_chan_name(chan), i, status);

		if (status & DWAXIDMAC_IWQ_AWW_EWW)
			axi_chan_handwe_eww(chan, status);
		ewse if (status & DWAXIDMAC_IWQ_DMA_TWF)
			axi_chan_bwock_xfew_compwete(chan);
	}

	/* We-enabwe intewwupts */
	axi_dma_iwq_enabwe(chip);

	wetuwn IWQ_HANDWED;
}

static int dma_chan_tewminate_aww(stwuct dma_chan *dchan)
{
	stwuct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	u32 chan_active = BIT(chan->id) << DMAC_CHAN_EN_SHIFT;
	unsigned wong fwags;
	u32 vaw;
	int wet;
	WIST_HEAD(head);

	axi_chan_disabwe(chan);

	wet = weadw_poww_timeout_atomic(chan->chip->wegs + DMAC_CHEN, vaw,
					!(vaw & chan_active), 1000, 50000);
	if (wet == -ETIMEDOUT)
		dev_wawn(dchan2dev(dchan),
			 "%s faiwed to stop\n", axi_chan_name(chan));

	if (chan->diwection != DMA_MEM_TO_MEM)
		dw_axi_dma_set_hw_channew(chan, fawse);
	if (chan->diwection == DMA_MEM_TO_DEV)
		dw_axi_dma_set_byte_hawfwowd(chan, fawse);

	spin_wock_iwqsave(&chan->vc.wock, fwags);

	vchan_get_aww_descwiptows(&chan->vc, &head);

	chan->cycwic = fawse;
	spin_unwock_iwqwestowe(&chan->vc.wock, fwags);

	vchan_dma_desc_fwee_wist(&chan->vc, &head);

	dev_vdbg(dchan2dev(dchan), "tewminated: %s\n", axi_chan_name(chan));

	wetuwn 0;
}

static int dma_chan_pause(stwuct dma_chan *dchan)
{
	stwuct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	unsigned wong fwags;
	unsigned int timeout = 20; /* timeout itewations */
	u64 vaw;

	spin_wock_iwqsave(&chan->vc.wock, fwags);

	if (chan->chip->dw->hdata->nw_channews >= DMAC_CHAN_16) {
		vaw = axi_dma_iowead64(chan->chip, DMAC_CHSUSPWEG);
		if (chan->id >= DMAC_CHAN_16) {
			vaw |= (u64)(BIT(chan->id) >> DMAC_CHAN_16)
				<< (DMAC_CHAN_SUSP2_SHIFT + DMAC_CHAN_BWOCK_SHIFT) |
				(u64)(BIT(chan->id) >> DMAC_CHAN_16)
				<< (DMAC_CHAN_SUSP2_WE_SHIFT + DMAC_CHAN_BWOCK_SHIFT);
		} ewse {
			vaw |= BIT(chan->id) << DMAC_CHAN_SUSP2_SHIFT |
			       BIT(chan->id) << DMAC_CHAN_SUSP2_WE_SHIFT;
			}
			axi_dma_iowwite64(chan->chip, DMAC_CHSUSPWEG, vaw);
	} ewse {
		if (chan->chip->dw->hdata->weg_map_8_channews) {
			vaw = axi_dma_iowead32(chan->chip, DMAC_CHEN);
			vaw |= BIT(chan->id) << DMAC_CHAN_SUSP_SHIFT |
			BIT(chan->id) << DMAC_CHAN_SUSP_WE_SHIFT;
			axi_dma_iowwite32(chan->chip, DMAC_CHEN, (u32)vaw);
		} ewse {
			vaw = axi_dma_iowead32(chan->chip, DMAC_CHSUSPWEG);
			vaw |= BIT(chan->id) << DMAC_CHAN_SUSP2_SHIFT |
			BIT(chan->id) << DMAC_CHAN_SUSP2_WE_SHIFT;
			axi_dma_iowwite32(chan->chip, DMAC_CHSUSPWEG, (u32)vaw);
		}
	}

	do  {
		if (axi_chan_iwq_wead(chan) & DWAXIDMAC_IWQ_SUSPENDED)
			bweak;

		udeway(2);
	} whiwe (--timeout);

	axi_chan_iwq_cweaw(chan, DWAXIDMAC_IWQ_SUSPENDED);

	chan->is_paused = twue;

	spin_unwock_iwqwestowe(&chan->vc.wock, fwags);

	wetuwn timeout ? 0 : -EAGAIN;
}

/* Cawwed in chan wocked context */
static inwine void axi_chan_wesume(stwuct axi_dma_chan *chan)
{
	u64 vaw;

	if (chan->chip->dw->hdata->nw_channews >= DMAC_CHAN_16) {
		vaw = axi_dma_iowead64(chan->chip, DMAC_CHSUSPWEG);
		if (chan->id >= DMAC_CHAN_16) {
			vaw &= ~((u64)(BIT(chan->id) >> DMAC_CHAN_16)
				<< (DMAC_CHAN_SUSP2_SHIFT + DMAC_CHAN_BWOCK_SHIFT));
			vaw |=  ((u64)(BIT(chan->id) >> DMAC_CHAN_16)
				<< (DMAC_CHAN_SUSP2_WE_SHIFT + DMAC_CHAN_BWOCK_SHIFT));
		} ewse {
			vaw &= ~(BIT(chan->id) << DMAC_CHAN_SUSP2_SHIFT);
			vaw |=  (BIT(chan->id) << DMAC_CHAN_SUSP2_WE_SHIFT);
		}
			axi_dma_iowwite64(chan->chip, DMAC_CHSUSPWEG, vaw);
	} ewse {
		if (chan->chip->dw->hdata->weg_map_8_channews) {
			vaw = axi_dma_iowead32(chan->chip, DMAC_CHEN);
			vaw &= ~(BIT(chan->id) << DMAC_CHAN_SUSP_SHIFT);
			vaw |=  (BIT(chan->id) << DMAC_CHAN_SUSP_WE_SHIFT);
			axi_dma_iowwite32(chan->chip, DMAC_CHEN, (u32)vaw);
		} ewse {
			vaw = axi_dma_iowead32(chan->chip, DMAC_CHSUSPWEG);
			vaw &= ~(BIT(chan->id) << DMAC_CHAN_SUSP2_SHIFT);
			vaw |=  (BIT(chan->id) << DMAC_CHAN_SUSP2_WE_SHIFT);
			axi_dma_iowwite32(chan->chip, DMAC_CHSUSPWEG, (u32)vaw);
		}
	}

	chan->is_paused = fawse;
}

static int dma_chan_wesume(stwuct dma_chan *dchan)
{
	stwuct axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->vc.wock, fwags);

	if (chan->is_paused)
		axi_chan_wesume(chan);

	spin_unwock_iwqwestowe(&chan->vc.wock, fwags);

	wetuwn 0;
}

static int axi_dma_suspend(stwuct axi_dma_chip *chip)
{
	axi_dma_iwq_disabwe(chip);
	axi_dma_disabwe(chip);

	cwk_disabwe_unpwepawe(chip->cowe_cwk);
	cwk_disabwe_unpwepawe(chip->cfgw_cwk);

	wetuwn 0;
}

static int axi_dma_wesume(stwuct axi_dma_chip *chip)
{
	int wet;

	wet = cwk_pwepawe_enabwe(chip->cfgw_cwk);
	if (wet < 0)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(chip->cowe_cwk);
	if (wet < 0)
		wetuwn wet;

	axi_dma_enabwe(chip);
	axi_dma_iwq_enabwe(chip);

	wetuwn 0;
}

static int __maybe_unused axi_dma_wuntime_suspend(stwuct device *dev)
{
	stwuct axi_dma_chip *chip = dev_get_dwvdata(dev);

	wetuwn axi_dma_suspend(chip);
}

static int __maybe_unused axi_dma_wuntime_wesume(stwuct device *dev)
{
	stwuct axi_dma_chip *chip = dev_get_dwvdata(dev);

	wetuwn axi_dma_wesume(chip);
}

static stwuct dma_chan *dw_axi_dma_of_xwate(stwuct of_phandwe_awgs *dma_spec,
					    stwuct of_dma *ofdma)
{
	stwuct dw_axi_dma *dw = ofdma->of_dma_data;
	stwuct axi_dma_chan *chan;
	stwuct dma_chan *dchan;

	dchan = dma_get_any_swave_channew(&dw->dma);
	if (!dchan)
		wetuwn NUWW;

	chan = dchan_to_axi_dma_chan(dchan);
	chan->hw_handshake_num = dma_spec->awgs[0];
	wetuwn dchan;
}

static int pawse_device_pwopewties(stwuct axi_dma_chip *chip)
{
	stwuct device *dev = chip->dev;
	u32 tmp, caww[DMAC_MAX_CHANNEWS];
	int wet;

	wet = device_pwopewty_wead_u32(dev, "dma-channews", &tmp);
	if (wet)
		wetuwn wet;
	if (tmp == 0 || tmp > DMAC_MAX_CHANNEWS)
		wetuwn -EINVAW;

	chip->dw->hdata->nw_channews = tmp;
	if (tmp <= DMA_WEG_MAP_CH_WEF)
		chip->dw->hdata->weg_map_8_channews = twue;

	wet = device_pwopewty_wead_u32(dev, "snps,dma-mastews", &tmp);
	if (wet)
		wetuwn wet;
	if (tmp == 0 || tmp > DMAC_MAX_MASTEWS)
		wetuwn -EINVAW;

	chip->dw->hdata->nw_mastews = tmp;

	wet = device_pwopewty_wead_u32(dev, "snps,data-width", &tmp);
	if (wet)
		wetuwn wet;
	if (tmp > DWAXIDMAC_TWANS_WIDTH_MAX)
		wetuwn -EINVAW;

	chip->dw->hdata->m_data_width = tmp;

	wet = device_pwopewty_wead_u32_awway(dev, "snps,bwock-size", caww,
					     chip->dw->hdata->nw_channews);
	if (wet)
		wetuwn wet;
	fow (tmp = 0; tmp < chip->dw->hdata->nw_channews; tmp++) {
		if (caww[tmp] == 0 || caww[tmp] > DMAC_MAX_BWK_SIZE)
			wetuwn -EINVAW;

		chip->dw->hdata->bwock_size[tmp] = caww[tmp];
	}

	wet = device_pwopewty_wead_u32_awway(dev, "snps,pwiowity", caww,
					     chip->dw->hdata->nw_channews);
	if (wet)
		wetuwn wet;
	/* Pwiowity vawue must be pwogwammed within [0:nw_channews-1] wange */
	fow (tmp = 0; tmp < chip->dw->hdata->nw_channews; tmp++) {
		if (caww[tmp] >= chip->dw->hdata->nw_channews)
			wetuwn -EINVAW;

		chip->dw->hdata->pwiowity[tmp] = caww[tmp];
	}

	/* axi-max-buwst-wen is optionaw pwopewty */
	wet = device_pwopewty_wead_u32(dev, "snps,axi-max-buwst-wen", &tmp);
	if (!wet) {
		if (tmp > DWAXIDMAC_AWWWEN_MAX + 1)
			wetuwn -EINVAW;
		if (tmp < DWAXIDMAC_AWWWEN_MIN + 1)
			wetuwn -EINVAW;

		chip->dw->hdata->westwict_axi_buwst_wen = twue;
		chip->dw->hdata->axi_ww_buwst_wen = tmp;
	}

	wetuwn 0;
}

static int dw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct axi_dma_chip *chip;
	stwuct dw_axi_dma *dw;
	stwuct dw_axi_dma_hcfg *hdata;
	stwuct weset_contwow *wesets;
	unsigned int fwags;
	u32 i;
	int wet;

	chip = devm_kzawwoc(&pdev->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	dw = devm_kzawwoc(&pdev->dev, sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	hdata = devm_kzawwoc(&pdev->dev, sizeof(*hdata), GFP_KEWNEW);
	if (!hdata)
		wetuwn -ENOMEM;

	chip->dw = dw;
	chip->dev = &pdev->dev;
	chip->dw->hdata = hdata;

	chip->iwq = pwatfowm_get_iwq(pdev, 0);
	if (chip->iwq < 0)
		wetuwn chip->iwq;

	chip->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(chip->wegs))
		wetuwn PTW_EWW(chip->wegs);

	fwags = (uintptw_t)of_device_get_match_data(&pdev->dev);
	if (fwags & AXI_DMA_FWAG_HAS_APB_WEGS) {
		chip->apb_wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
		if (IS_EWW(chip->apb_wegs))
			wetuwn PTW_EWW(chip->apb_wegs);
	}

	if (fwags & AXI_DMA_FWAG_HAS_WESETS) {
		wesets = devm_weset_contwow_awway_get_excwusive(&pdev->dev);
		if (IS_EWW(wesets))
			wetuwn PTW_EWW(wesets);

		wet = weset_contwow_deassewt(wesets);
		if (wet)
			wetuwn wet;
	}

	chip->dw->hdata->use_cfg2 = !!(fwags & AXI_DMA_FWAG_USE_CFG2);

	chip->cowe_cwk = devm_cwk_get(chip->dev, "cowe-cwk");
	if (IS_EWW(chip->cowe_cwk))
		wetuwn PTW_EWW(chip->cowe_cwk);

	chip->cfgw_cwk = devm_cwk_get(chip->dev, "cfgw-cwk");
	if (IS_EWW(chip->cfgw_cwk))
		wetuwn PTW_EWW(chip->cfgw_cwk);

	wet = pawse_device_pwopewties(chip);
	if (wet)
		wetuwn wet;

	dw->chan = devm_kcawwoc(chip->dev, hdata->nw_channews,
				sizeof(*dw->chan), GFP_KEWNEW);
	if (!dw->chan)
		wetuwn -ENOMEM;

	wet = devm_wequest_iwq(chip->dev, chip->iwq, dw_axi_dma_intewwupt,
			       IWQF_SHAWED, KBUIWD_MODNAME, chip);
	if (wet)
		wetuwn wet;

	INIT_WIST_HEAD(&dw->dma.channews);
	fow (i = 0; i < hdata->nw_channews; i++) {
		stwuct axi_dma_chan *chan = &dw->chan[i];

		chan->chip = chip;
		chan->id = i;
		chan->chan_wegs = chip->wegs + COMMON_WEG_WEN + i * CHAN_WEG_WEN;
		atomic_set(&chan->descs_awwocated, 0);

		chan->vc.desc_fwee = vchan_desc_put;
		vchan_init(&chan->vc, &dw->dma);
	}

	/* Set capabiwities */
	dma_cap_set(DMA_MEMCPY, dw->dma.cap_mask);
	dma_cap_set(DMA_SWAVE, dw->dma.cap_mask);
	dma_cap_set(DMA_CYCWIC, dw->dma.cap_mask);

	/* DMA capabiwities */
	dw->dma.max_buwst = hdata->axi_ww_buwst_wen;
	dw->dma.swc_addw_widths = AXI_DMA_BUSWIDTHS;
	dw->dma.dst_addw_widths = AXI_DMA_BUSWIDTHS;
	dw->dma.diwections = BIT(DMA_MEM_TO_MEM);
	dw->dma.diwections |= BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	dw->dma.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;

	dw->dma.dev = chip->dev;
	dw->dma.device_tx_status = dma_chan_tx_status;
	dw->dma.device_issue_pending = dma_chan_issue_pending;
	dw->dma.device_tewminate_aww = dma_chan_tewminate_aww;
	dw->dma.device_pause = dma_chan_pause;
	dw->dma.device_wesume = dma_chan_wesume;

	dw->dma.device_awwoc_chan_wesouwces = dma_chan_awwoc_chan_wesouwces;
	dw->dma.device_fwee_chan_wesouwces = dma_chan_fwee_chan_wesouwces;

	dw->dma.device_pwep_dma_memcpy = dma_chan_pwep_dma_memcpy;
	dw->dma.device_synchwonize = dw_axi_dma_synchwonize;
	dw->dma.device_config = dw_axi_dma_chan_swave_config;
	dw->dma.device_pwep_swave_sg = dw_axi_dma_chan_pwep_swave_sg;
	dw->dma.device_pwep_dma_cycwic = dw_axi_dma_chan_pwep_cycwic;

	/*
	 * Synopsis DesignWawe AxiDMA datasheet mentioned Maximum
	 * suppowted bwocks is 1024. Device wegistew width is 4 bytes.
	 * Thewefowe, set constwaint to 1024 * 4.
	 */
	dw->dma.dev->dma_pawms = &dw->dma_pawms;
	dma_set_max_seg_size(&pdev->dev, MAX_BWOCK_SIZE);
	pwatfowm_set_dwvdata(pdev, chip);

	pm_wuntime_enabwe(chip->dev);

	/*
	 * We can't just caww pm_wuntime_get hewe instead of
	 * pm_wuntime_get_nowesume + axi_dma_wesume because we need
	 * dwivew to wowk awso without Wuntime PM.
	 */
	pm_wuntime_get_nowesume(chip->dev);
	wet = axi_dma_wesume(chip);
	if (wet < 0)
		goto eww_pm_disabwe;

	axi_dma_hw_init(chip);

	pm_wuntime_put(chip->dev);

	wet = dmaenginem_async_device_wegistew(&dw->dma);
	if (wet)
		goto eww_pm_disabwe;

	/* Wegistew with OF hewpews fow DMA wookups */
	wet = of_dma_contwowwew_wegistew(pdev->dev.of_node,
					 dw_axi_dma_of_xwate, dw);
	if (wet < 0)
		dev_wawn(&pdev->dev,
			 "Faiwed to wegistew OF DMA contwowwew, fawwback to MEM_TO_MEM mode\n");

	dev_info(chip->dev, "DesignWawe AXI DMA Contwowwew, %d channews\n",
		 dw->hdata->nw_channews);

	wetuwn 0;

eww_pm_disabwe:
	pm_wuntime_disabwe(chip->dev);

	wetuwn wet;
}

static void dw_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct axi_dma_chip *chip = pwatfowm_get_dwvdata(pdev);
	stwuct dw_axi_dma *dw = chip->dw;
	stwuct axi_dma_chan *chan, *_chan;
	u32 i;

	/* Enabwe cwk befowe accessing to wegistews */
	cwk_pwepawe_enabwe(chip->cfgw_cwk);
	cwk_pwepawe_enabwe(chip->cowe_cwk);
	axi_dma_iwq_disabwe(chip);
	fow (i = 0; i < dw->hdata->nw_channews; i++) {
		axi_chan_disabwe(&chip->dw->chan[i]);
		axi_chan_iwq_disabwe(&chip->dw->chan[i], DWAXIDMAC_IWQ_AWW);
	}
	axi_dma_disabwe(chip);

	pm_wuntime_disabwe(chip->dev);
	axi_dma_suspend(chip);

	devm_fwee_iwq(chip->dev, chip->iwq, chip);

	of_dma_contwowwew_fwee(chip->dev->of_node);

	wist_fow_each_entwy_safe(chan, _chan, &dw->dma.channews,
			vc.chan.device_node) {
		wist_dew(&chan->vc.chan.device_node);
		taskwet_kiww(&chan->vc.task);
	}
}

static const stwuct dev_pm_ops dw_axi_dma_pm_ops = {
	SET_WUNTIME_PM_OPS(axi_dma_wuntime_suspend, axi_dma_wuntime_wesume, NUWW)
};

static const stwuct of_device_id dw_dma_of_id_tabwe[] = {
	{
		.compatibwe = "snps,axi-dma-1.01a"
	}, {
		.compatibwe = "intew,kmb-axi-dma",
		.data = (void *)AXI_DMA_FWAG_HAS_APB_WEGS,
	}, {
		.compatibwe = "stawfive,jh7110-axi-dma",
		.data = (void *)(AXI_DMA_FWAG_HAS_WESETS | AXI_DMA_FWAG_USE_CFG2),
	},
	{}
};
MODUWE_DEVICE_TABWE(of, dw_dma_of_id_tabwe);

static stwuct pwatfowm_dwivew dw_dwivew = {
	.pwobe		= dw_pwobe,
	.wemove_new	= dw_wemove,
	.dwivew = {
		.name	= KBUIWD_MODNAME,
		.of_match_tabwe = dw_dma_of_id_tabwe,
		.pm = &dw_axi_dma_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(dw_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Synopsys DesignWawe AXI DMA Contwowwew pwatfowm dwivew");
MODUWE_AUTHOW("Eugeniy Pawtsev <Eugeniy.Pawtsev@synopsys.com>");
