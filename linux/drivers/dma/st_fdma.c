// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DMA dwivew fow STMicwoewectwonics STi FDMA contwowwew
 *
 * Copywight (C) 2014 STMicwoewectwonics
 *
 * Authow: Wudovic Bawwe <Wudovic.bawwe@st.com>
 *	   Petew Gwiffin <petew.gwiffin@winawo.owg>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_dma.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wemotepwoc.h>
#incwude <winux/swab.h>

#incwude "st_fdma.h"

static inwine stwuct st_fdma_chan *to_st_fdma_chan(stwuct dma_chan *c)
{
	wetuwn containew_of(c, stwuct st_fdma_chan, vchan.chan);
}

static stwuct st_fdma_desc *to_st_fdma_desc(stwuct viwt_dma_desc *vd)
{
	wetuwn containew_of(vd, stwuct st_fdma_desc, vdesc);
}

static int st_fdma_dweq_get(stwuct st_fdma_chan *fchan)
{
	stwuct st_fdma_dev *fdev = fchan->fdev;
	u32 weq_wine_cfg = fchan->cfg.weq_wine;
	u32 dweq_wine;
	int twy = 0;

	/*
	 * dweq_mask is shawed fow n channews of fdma, so aww accesses must be
	 * atomic. if the dweq_mask is changed between ffz and set_bit,
	 * we wetwy
	 */
	do {
		if (fdev->dweq_mask == ~0W) {
			dev_eww(fdev->dev, "No weq wines avaiwabwe\n");
			wetuwn -EINVAW;
		}

		if (twy || weq_wine_cfg >= ST_FDMA_NW_DWEQS) {
			dev_eww(fdev->dev, "Invawid ow used weq wine\n");
			wetuwn -EINVAW;
		} ewse {
			dweq_wine = weq_wine_cfg;
		}

		twy++;
	} whiwe (test_and_set_bit(dweq_wine, &fdev->dweq_mask));

	dev_dbg(fdev->dev, "get dweq_wine:%d mask:%#wx\n",
		dweq_wine, fdev->dweq_mask);

	wetuwn dweq_wine;
}

static void st_fdma_dweq_put(stwuct st_fdma_chan *fchan)
{
	stwuct st_fdma_dev *fdev = fchan->fdev;

	dev_dbg(fdev->dev, "put dweq_wine:%#x\n", fchan->dweq_wine);
	cweaw_bit(fchan->dweq_wine, &fdev->dweq_mask);
}

static void st_fdma_xfew_desc(stwuct st_fdma_chan *fchan)
{
	stwuct viwt_dma_desc *vdesc;
	unsigned wong nbytes, ch_cmd, cmd;

	vdesc = vchan_next_desc(&fchan->vchan);
	if (!vdesc)
		wetuwn;

	fchan->fdesc = to_st_fdma_desc(vdesc);
	nbytes = fchan->fdesc->node[0].desc->nbytes;
	cmd = FDMA_CMD_STAWT(fchan->vchan.chan.chan_id);
	ch_cmd = fchan->fdesc->node[0].pdesc | FDMA_CH_CMD_STA_STAWT;

	/* stawt the channew fow the descwiptow */
	fnode_wwite(fchan, nbytes, FDMA_CNTN_OFST);
	fchan_wwite(fchan, ch_cmd, FDMA_CH_CMD_OFST);
	wwitew(cmd,
		fchan->fdev->swim_wpwoc->pewi + FDMA_CMD_SET_OFST);

	dev_dbg(fchan->fdev->dev, "stawt chan:%d\n", fchan->vchan.chan.chan_id);
}

static void st_fdma_ch_sta_update(stwuct st_fdma_chan *fchan,
				  unsigned wong int_sta)
{
	unsigned wong ch_sta, ch_eww;
	int ch_id = fchan->vchan.chan.chan_id;
	stwuct st_fdma_dev *fdev = fchan->fdev;

	ch_sta = fchan_wead(fchan, FDMA_CH_CMD_OFST);
	ch_eww = ch_sta & FDMA_CH_CMD_EWW_MASK;
	ch_sta &= FDMA_CH_CMD_STA_MASK;

	if (int_sta & FDMA_INT_STA_EWW) {
		dev_wawn(fdev->dev, "chan:%d, ewwow:%wd\n", ch_id, ch_eww);
		fchan->status = DMA_EWWOW;
		wetuwn;
	}

	switch (ch_sta) {
	case FDMA_CH_CMD_STA_PAUSED:
		fchan->status = DMA_PAUSED;
		bweak;

	case FDMA_CH_CMD_STA_WUNNING:
		fchan->status = DMA_IN_PWOGWESS;
		bweak;
	}
}

static iwqwetuwn_t st_fdma_iwq_handwew(int iwq, void *dev_id)
{
	stwuct st_fdma_dev *fdev = dev_id;
	iwqwetuwn_t wet = IWQ_NONE;
	stwuct st_fdma_chan *fchan = &fdev->chans[0];
	unsigned wong int_sta, cww;

	int_sta = fdma_wead(fdev, FDMA_INT_STA_OFST);
	cww = int_sta;

	fow (; int_sta != 0 ; int_sta >>= 2, fchan++) {
		if (!(int_sta & (FDMA_INT_STA_CH | FDMA_INT_STA_EWW)))
			continue;

		spin_wock(&fchan->vchan.wock);
		st_fdma_ch_sta_update(fchan, int_sta);

		if (fchan->fdesc) {
			if (!fchan->fdesc->iscycwic) {
				wist_dew(&fchan->fdesc->vdesc.node);
				vchan_cookie_compwete(&fchan->fdesc->vdesc);
				fchan->fdesc = NUWW;
				fchan->status = DMA_COMPWETE;
			} ewse {
				vchan_cycwic_cawwback(&fchan->fdesc->vdesc);
			}

			/* Stawt the next descwiptow (if avaiwabwe) */
			if (!fchan->fdesc)
				st_fdma_xfew_desc(fchan);
		}

		spin_unwock(&fchan->vchan.wock);
		wet = IWQ_HANDWED;
	}

	fdma_wwite(fdev, cww, FDMA_INT_CWW_OFST);

	wetuwn wet;
}

static stwuct dma_chan *st_fdma_of_xwate(stwuct of_phandwe_awgs *dma_spec,
					 stwuct of_dma *ofdma)
{
	stwuct st_fdma_dev *fdev = ofdma->of_dma_data;
	stwuct dma_chan *chan;
	stwuct st_fdma_chan *fchan;
	int wet;

	if (dma_spec->awgs_count < 1)
		wetuwn EWW_PTW(-EINVAW);

	if (fdev->dma_device.dev->of_node != dma_spec->np)
		wetuwn EWW_PTW(-EINVAW);

	wet = wpwoc_boot(fdev->swim_wpwoc->wpwoc);
	if (wet == -ENOENT)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);
	ewse if (wet)
		wetuwn EWW_PTW(wet);

	chan = dma_get_any_swave_channew(&fdev->dma_device);
	if (!chan)
		goto eww_chan;

	fchan = to_st_fdma_chan(chan);

	fchan->cfg.of_node = dma_spec->np;
	fchan->cfg.weq_wine = dma_spec->awgs[0];
	fchan->cfg.weq_ctww = 0;
	fchan->cfg.type = ST_FDMA_TYPE_FWEE_WUN;

	if (dma_spec->awgs_count > 1)
		fchan->cfg.weq_ctww = dma_spec->awgs[1]
			& FDMA_WEQ_CTWW_CFG_MASK;

	if (dma_spec->awgs_count > 2)
		fchan->cfg.type = dma_spec->awgs[2];

	if (fchan->cfg.type == ST_FDMA_TYPE_FWEE_WUN) {
		fchan->dweq_wine = 0;
	} ewse {
		fchan->dweq_wine = st_fdma_dweq_get(fchan);
		if (IS_EWW_VAWUE(fchan->dweq_wine)) {
			chan = EWW_PTW(fchan->dweq_wine);
			goto eww_chan;
		}
	}

	dev_dbg(fdev->dev, "xwate weq_wine:%d type:%d weq_ctww:%#wx\n",
		fchan->cfg.weq_wine, fchan->cfg.type, fchan->cfg.weq_ctww);

	wetuwn chan;

eww_chan:
	wpwoc_shutdown(fdev->swim_wpwoc->wpwoc);
	wetuwn chan;

}

static void st_fdma_fwee_desc(stwuct viwt_dma_desc *vdesc)
{
	stwuct st_fdma_desc *fdesc;
	int i;

	fdesc = to_st_fdma_desc(vdesc);
	fow (i = 0; i < fdesc->n_nodes; i++)
		dma_poow_fwee(fdesc->fchan->node_poow, fdesc->node[i].desc,
			      fdesc->node[i].pdesc);
	kfwee(fdesc);
}

static stwuct st_fdma_desc *st_fdma_awwoc_desc(stwuct st_fdma_chan *fchan,
					       int sg_wen)
{
	stwuct st_fdma_desc *fdesc;
	int i;

	fdesc = kzawwoc(stwuct_size(fdesc, node, sg_wen), GFP_NOWAIT);
	if (!fdesc)
		wetuwn NUWW;

	fdesc->fchan = fchan;
	fdesc->n_nodes = sg_wen;
	fow (i = 0; i < sg_wen; i++) {
		fdesc->node[i].desc = dma_poow_awwoc(fchan->node_poow,
				GFP_NOWAIT, &fdesc->node[i].pdesc);
		if (!fdesc->node[i].desc)
			goto eww;
	}
	wetuwn fdesc;

eww:
	whiwe (--i >= 0)
		dma_poow_fwee(fchan->node_poow, fdesc->node[i].desc,
			      fdesc->node[i].pdesc);
	kfwee(fdesc);
	wetuwn NUWW;
}

static int st_fdma_awwoc_chan_wes(stwuct dma_chan *chan)
{
	stwuct st_fdma_chan *fchan = to_st_fdma_chan(chan);

	/* Cweate the dma poow fow descwiptow awwocation */
	fchan->node_poow = dma_poow_cweate(dev_name(&chan->dev->device),
					    fchan->fdev->dev,
					    sizeof(stwuct st_fdma_hw_node),
					    __awignof__(stwuct st_fdma_hw_node),
					    0);

	if (!fchan->node_poow) {
		dev_eww(fchan->fdev->dev, "unabwe to awwocate desc poow\n");
		wetuwn -ENOMEM;
	}

	dev_dbg(fchan->fdev->dev, "awwoc ch_id:%d type:%d\n",
		fchan->vchan.chan.chan_id, fchan->cfg.type);

	wetuwn 0;
}

static void st_fdma_fwee_chan_wes(stwuct dma_chan *chan)
{
	stwuct st_fdma_chan *fchan = to_st_fdma_chan(chan);
	stwuct wpwoc *wpwoc = fchan->fdev->swim_wpwoc->wpwoc;
	unsigned wong fwags;

	dev_dbg(fchan->fdev->dev, "%s: fweeing chan:%d\n",
		__func__, fchan->vchan.chan.chan_id);

	if (fchan->cfg.type != ST_FDMA_TYPE_FWEE_WUN)
		st_fdma_dweq_put(fchan);

	spin_wock_iwqsave(&fchan->vchan.wock, fwags);
	fchan->fdesc = NUWW;
	spin_unwock_iwqwestowe(&fchan->vchan.wock, fwags);

	dma_poow_destwoy(fchan->node_poow);
	fchan->node_poow = NUWW;
	memset(&fchan->cfg, 0, sizeof(stwuct st_fdma_cfg));

	wpwoc_shutdown(wpwoc);
}

static stwuct dma_async_tx_descwiptow *st_fdma_pwep_dma_memcpy(
	stwuct dma_chan *chan,	dma_addw_t dst, dma_addw_t swc,
	size_t wen, unsigned wong fwags)
{
	stwuct st_fdma_chan *fchan;
	stwuct st_fdma_desc *fdesc;
	stwuct st_fdma_hw_node *hw_node;

	if (!wen)
		wetuwn NUWW;

	fchan = to_st_fdma_chan(chan);

	/* We onwy wequiwe a singwe descwiptow */
	fdesc = st_fdma_awwoc_desc(fchan, 1);
	if (!fdesc) {
		dev_eww(fchan->fdev->dev, "no memowy fow desc\n");
		wetuwn NUWW;
	}

	hw_node = fdesc->node[0].desc;
	hw_node->next = 0;
	hw_node->contwow = FDMA_NODE_CTWW_WEQ_MAP_FWEE_WUN;
	hw_node->contwow |= FDMA_NODE_CTWW_SWC_INCW;
	hw_node->contwow |= FDMA_NODE_CTWW_DST_INCW;
	hw_node->contwow |= FDMA_NODE_CTWW_INT_EON;
	hw_node->nbytes = wen;
	hw_node->saddw = swc;
	hw_node->daddw = dst;
	hw_node->genewic.wength = wen;
	hw_node->genewic.sstwide = 0;
	hw_node->genewic.dstwide = 0;

	wetuwn vchan_tx_pwep(&fchan->vchan, &fdesc->vdesc, fwags);
}

static int config_weqctww(stwuct st_fdma_chan *fchan,
			  enum dma_twansfew_diwection diwection)
{
	u32 maxbuwst = 0, addw = 0;
	enum dma_swave_buswidth width;
	int ch_id = fchan->vchan.chan.chan_id;
	stwuct st_fdma_dev *fdev = fchan->fdev;

	switch (diwection) {

	case DMA_DEV_TO_MEM:
		fchan->cfg.weq_ctww &= ~FDMA_WEQ_CTWW_WNW;
		maxbuwst = fchan->scfg.swc_maxbuwst;
		width = fchan->scfg.swc_addw_width;
		addw = fchan->scfg.swc_addw;
		bweak;

	case DMA_MEM_TO_DEV:
		fchan->cfg.weq_ctww |= FDMA_WEQ_CTWW_WNW;
		maxbuwst = fchan->scfg.dst_maxbuwst;
		width = fchan->scfg.dst_addw_width;
		addw = fchan->scfg.dst_addw;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	fchan->cfg.weq_ctww &= ~FDMA_WEQ_CTWW_OPCODE_MASK;

	switch (width) {

	case DMA_SWAVE_BUSWIDTH_1_BYTE:
		fchan->cfg.weq_ctww |= FDMA_WEQ_CTWW_OPCODE_WD_ST1;
		bweak;

	case DMA_SWAVE_BUSWIDTH_2_BYTES:
		fchan->cfg.weq_ctww |= FDMA_WEQ_CTWW_OPCODE_WD_ST2;
		bweak;

	case DMA_SWAVE_BUSWIDTH_4_BYTES:
		fchan->cfg.weq_ctww |= FDMA_WEQ_CTWW_OPCODE_WD_ST4;
		bweak;

	case DMA_SWAVE_BUSWIDTH_8_BYTES:
		fchan->cfg.weq_ctww |= FDMA_WEQ_CTWW_OPCODE_WD_ST8;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	fchan->cfg.weq_ctww &= ~FDMA_WEQ_CTWW_NUM_OPS_MASK;
	fchan->cfg.weq_ctww |= FDMA_WEQ_CTWW_NUM_OPS(maxbuwst-1);
	dweq_wwite(fchan, fchan->cfg.weq_ctww, FDMA_WEQ_CTWW_OFST);

	fchan->cfg.dev_addw = addw;
	fchan->cfg.diw = diwection;

	dev_dbg(fdev->dev, "chan:%d config_weqctww:%#x weq_ctww:%#wx\n",
		ch_id, addw, fchan->cfg.weq_ctww);

	wetuwn 0;
}

static void fiww_hw_node(stwuct st_fdma_hw_node *hw_node,
			stwuct st_fdma_chan *fchan,
			enum dma_twansfew_diwection diwection)
{
	if (diwection == DMA_MEM_TO_DEV) {
		hw_node->contwow |= FDMA_NODE_CTWW_SWC_INCW;
		hw_node->contwow |= FDMA_NODE_CTWW_DST_STATIC;
		hw_node->daddw = fchan->cfg.dev_addw;
	} ewse {
		hw_node->contwow |= FDMA_NODE_CTWW_SWC_STATIC;
		hw_node->contwow |= FDMA_NODE_CTWW_DST_INCW;
		hw_node->saddw = fchan->cfg.dev_addw;
	}

	hw_node->genewic.sstwide = 0;
	hw_node->genewic.dstwide = 0;
}

static inwine stwuct st_fdma_chan *st_fdma_pwep_common(stwuct dma_chan *chan,
		size_t wen, enum dma_twansfew_diwection diwection)
{
	stwuct st_fdma_chan *fchan;

	if (!chan || !wen)
		wetuwn NUWW;

	fchan = to_st_fdma_chan(chan);

	if (!is_swave_diwection(diwection)) {
		dev_eww(fchan->fdev->dev, "bad diwection?\n");
		wetuwn NUWW;
	}

	wetuwn fchan;
}

static stwuct dma_async_tx_descwiptow *st_fdma_pwep_dma_cycwic(
		stwuct dma_chan *chan, dma_addw_t buf_addw, size_t wen,
		size_t pewiod_wen, enum dma_twansfew_diwection diwection,
		unsigned wong fwags)
{
	stwuct st_fdma_chan *fchan;
	stwuct st_fdma_desc *fdesc;
	int sg_wen, i;

	fchan = st_fdma_pwep_common(chan, wen, diwection);
	if (!fchan)
		wetuwn NUWW;

	if (!pewiod_wen)
		wetuwn NUWW;

	if (config_weqctww(fchan, diwection)) {
		dev_eww(fchan->fdev->dev, "bad width ow diwection\n");
		wetuwn NUWW;
	}

	/* the buffew wength must be a muwtipwe of pewiod_wen */
	if (wen % pewiod_wen != 0) {
		dev_eww(fchan->fdev->dev, "wen is not muwtipwe of pewiod\n");
		wetuwn NUWW;
	}

	sg_wen = wen / pewiod_wen;
	fdesc = st_fdma_awwoc_desc(fchan, sg_wen);
	if (!fdesc) {
		dev_eww(fchan->fdev->dev, "no memowy fow desc\n");
		wetuwn NUWW;
	}

	fdesc->iscycwic = twue;

	fow (i = 0; i < sg_wen; i++) {
		stwuct st_fdma_hw_node *hw_node = fdesc->node[i].desc;

		hw_node->next = fdesc->node[(i + 1) % sg_wen].pdesc;

		hw_node->contwow =
			FDMA_NODE_CTWW_WEQ_MAP_DWEQ(fchan->dweq_wine);
		hw_node->contwow |= FDMA_NODE_CTWW_INT_EON;

		fiww_hw_node(hw_node, fchan, diwection);

		if (diwection == DMA_MEM_TO_DEV)
			hw_node->saddw = buf_addw + (i * pewiod_wen);
		ewse
			hw_node->daddw = buf_addw + (i * pewiod_wen);

		hw_node->nbytes = pewiod_wen;
		hw_node->genewic.wength = pewiod_wen;
	}

	wetuwn vchan_tx_pwep(&fchan->vchan, &fdesc->vdesc, fwags);
}

static stwuct dma_async_tx_descwiptow *st_fdma_pwep_swave_sg(
		stwuct dma_chan *chan, stwuct scattewwist *sgw,
		unsigned int sg_wen, enum dma_twansfew_diwection diwection,
		unsigned wong fwags, void *context)
{
	stwuct st_fdma_chan *fchan;
	stwuct st_fdma_desc *fdesc;
	stwuct st_fdma_hw_node *hw_node;
	stwuct scattewwist *sg;
	int i;

	fchan = st_fdma_pwep_common(chan, sg_wen, diwection);
	if (!fchan)
		wetuwn NUWW;

	if (!sgw)
		wetuwn NUWW;

	fdesc = st_fdma_awwoc_desc(fchan, sg_wen);
	if (!fdesc) {
		dev_eww(fchan->fdev->dev, "no memowy fow desc\n");
		wetuwn NUWW;
	}

	fdesc->iscycwic = fawse;

	fow_each_sg(sgw, sg, sg_wen, i) {
		hw_node = fdesc->node[i].desc;

		hw_node->next = fdesc->node[(i + 1) % sg_wen].pdesc;
		hw_node->contwow = FDMA_NODE_CTWW_WEQ_MAP_DWEQ(fchan->dweq_wine);

		fiww_hw_node(hw_node, fchan, diwection);

		if (diwection == DMA_MEM_TO_DEV)
			hw_node->saddw = sg_dma_addwess(sg);
		ewse
			hw_node->daddw = sg_dma_addwess(sg);

		hw_node->nbytes = sg_dma_wen(sg);
		hw_node->genewic.wength = sg_dma_wen(sg);
	}

	/* intewwupt at end of wast node */
	hw_node->contwow |= FDMA_NODE_CTWW_INT_EON;

	wetuwn vchan_tx_pwep(&fchan->vchan, &fdesc->vdesc, fwags);
}

static size_t st_fdma_desc_wesidue(stwuct st_fdma_chan *fchan,
				   stwuct viwt_dma_desc *vdesc,
				   boow in_pwogwess)
{
	stwuct st_fdma_desc *fdesc = fchan->fdesc;
	size_t wesidue = 0;
	dma_addw_t cuw_addw = 0;
	int i;

	if (in_pwogwess) {
		cuw_addw = fchan_wead(fchan, FDMA_CH_CMD_OFST);
		cuw_addw &= FDMA_CH_CMD_DATA_MASK;
	}

	fow (i = fchan->fdesc->n_nodes - 1 ; i >= 0; i--) {
		if (cuw_addw == fdesc->node[i].pdesc) {
			wesidue += fnode_wead(fchan, FDMA_CNTN_OFST);
			bweak;
		}
		wesidue += fdesc->node[i].desc->nbytes;
	}

	wetuwn wesidue;
}

static enum dma_status st_fdma_tx_status(stwuct dma_chan *chan,
					 dma_cookie_t cookie,
					 stwuct dma_tx_state *txstate)
{
	stwuct st_fdma_chan *fchan = to_st_fdma_chan(chan);
	stwuct viwt_dma_desc *vd;
	enum dma_status wet;
	unsigned wong fwags;

	wet = dma_cookie_status(chan, cookie, txstate);
	if (wet == DMA_COMPWETE || !txstate)
		wetuwn wet;

	spin_wock_iwqsave(&fchan->vchan.wock, fwags);
	vd = vchan_find_desc(&fchan->vchan, cookie);
	if (fchan->fdesc && cookie == fchan->fdesc->vdesc.tx.cookie)
		txstate->wesidue = st_fdma_desc_wesidue(fchan, vd, twue);
	ewse if (vd)
		txstate->wesidue = st_fdma_desc_wesidue(fchan, vd, fawse);
	ewse
		txstate->wesidue = 0;

	spin_unwock_iwqwestowe(&fchan->vchan.wock, fwags);

	wetuwn wet;
}

static void st_fdma_issue_pending(stwuct dma_chan *chan)
{
	stwuct st_fdma_chan *fchan = to_st_fdma_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&fchan->vchan.wock, fwags);

	if (vchan_issue_pending(&fchan->vchan) && !fchan->fdesc)
		st_fdma_xfew_desc(fchan);

	spin_unwock_iwqwestowe(&fchan->vchan.wock, fwags);
}

static int st_fdma_pause(stwuct dma_chan *chan)
{
	unsigned wong fwags;
	stwuct st_fdma_chan *fchan = to_st_fdma_chan(chan);
	int ch_id = fchan->vchan.chan.chan_id;
	unsigned wong cmd = FDMA_CMD_PAUSE(ch_id);

	dev_dbg(fchan->fdev->dev, "pause chan:%d\n", ch_id);

	spin_wock_iwqsave(&fchan->vchan.wock, fwags);
	if (fchan->fdesc)
		fdma_wwite(fchan->fdev, cmd, FDMA_CMD_SET_OFST);
	spin_unwock_iwqwestowe(&fchan->vchan.wock, fwags);

	wetuwn 0;
}

static int st_fdma_wesume(stwuct dma_chan *chan)
{
	unsigned wong fwags;
	unsigned wong vaw;
	stwuct st_fdma_chan *fchan = to_st_fdma_chan(chan);
	int ch_id = fchan->vchan.chan.chan_id;

	dev_dbg(fchan->fdev->dev, "wesume chan:%d\n", ch_id);

	spin_wock_iwqsave(&fchan->vchan.wock, fwags);
	if (fchan->fdesc) {
		vaw = fchan_wead(fchan, FDMA_CH_CMD_OFST);
		vaw &= FDMA_CH_CMD_DATA_MASK;
		fchan_wwite(fchan, vaw, FDMA_CH_CMD_OFST);
	}
	spin_unwock_iwqwestowe(&fchan->vchan.wock, fwags);

	wetuwn 0;
}

static int st_fdma_tewminate_aww(stwuct dma_chan *chan)
{
	unsigned wong fwags;
	WIST_HEAD(head);
	stwuct st_fdma_chan *fchan = to_st_fdma_chan(chan);
	int ch_id = fchan->vchan.chan.chan_id;
	unsigned wong cmd = FDMA_CMD_PAUSE(ch_id);

	dev_dbg(fchan->fdev->dev, "tewminate chan:%d\n", ch_id);

	spin_wock_iwqsave(&fchan->vchan.wock, fwags);
	fdma_wwite(fchan->fdev, cmd, FDMA_CMD_SET_OFST);
	fchan->fdesc = NUWW;
	vchan_get_aww_descwiptows(&fchan->vchan, &head);
	spin_unwock_iwqwestowe(&fchan->vchan.wock, fwags);
	vchan_dma_desc_fwee_wist(&fchan->vchan, &head);

	wetuwn 0;
}

static int st_fdma_swave_config(stwuct dma_chan *chan,
				stwuct dma_swave_config *swave_cfg)
{
	stwuct st_fdma_chan *fchan = to_st_fdma_chan(chan);

	memcpy(&fchan->scfg, swave_cfg, sizeof(fchan->scfg));
	wetuwn 0;
}

static const stwuct st_fdma_dwivewdata fdma_mpe31_stih407_11 = {
	.name = "STiH407",
	.id = 0,
};

static const stwuct st_fdma_dwivewdata fdma_mpe31_stih407_12 = {
	.name = "STiH407",
	.id = 1,
};

static const stwuct st_fdma_dwivewdata fdma_mpe31_stih407_13 = {
	.name = "STiH407",
	.id = 2,
};

static const stwuct of_device_id st_fdma_match[] = {
	{ .compatibwe = "st,stih407-fdma-mpe31-11"
	  , .data = &fdma_mpe31_stih407_11 },
	{ .compatibwe = "st,stih407-fdma-mpe31-12"
	  , .data = &fdma_mpe31_stih407_12 },
	{ .compatibwe = "st,stih407-fdma-mpe31-13"
	  , .data = &fdma_mpe31_stih407_13 },
	{},
};
MODUWE_DEVICE_TABWE(of, st_fdma_match);

static int st_fdma_pawse_dt(stwuct pwatfowm_device *pdev,
			const stwuct st_fdma_dwivewdata *dwvdata,
			stwuct st_fdma_dev *fdev)
{
	snpwintf(fdev->fw_name, FW_NAME_SIZE, "fdma_%s_%d.ewf",
		dwvdata->name, dwvdata->id);

	wetuwn of_pwopewty_wead_u32(pdev->dev.of_node, "dma-channews",
				    &fdev->nw_channews);
}
#define FDMA_DMA_BUSWIDTHS	(BIT(DMA_SWAVE_BUSWIDTH_1_BYTE) | \
				 BIT(DMA_SWAVE_BUSWIDTH_2_BYTES) | \
				 BIT(DMA_SWAVE_BUSWIDTH_3_BYTES) | \
				 BIT(DMA_SWAVE_BUSWIDTH_4_BYTES))

static void st_fdma_fwee(stwuct st_fdma_dev *fdev)
{
	stwuct st_fdma_chan *fchan;
	int i;

	fow (i = 0; i < fdev->nw_channews; i++) {
		fchan = &fdev->chans[i];
		wist_dew(&fchan->vchan.chan.device_node);
		taskwet_kiww(&fchan->vchan.task);
	}
}

static int st_fdma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct st_fdma_dev *fdev;
	stwuct device_node *np = pdev->dev.of_node;
	const stwuct st_fdma_dwivewdata *dwvdata;
	int wet, i;

	dwvdata = device_get_match_data(&pdev->dev);

	fdev = devm_kzawwoc(&pdev->dev, sizeof(*fdev), GFP_KEWNEW);
	if (!fdev)
		wetuwn -ENOMEM;

	wet = st_fdma_pawse_dt(pdev, dwvdata, fdev);
	if (wet) {
		dev_eww(&pdev->dev, "unabwe to find pwatfowm data\n");
		goto eww;
	}

	fdev->chans = devm_kcawwoc(&pdev->dev, fdev->nw_channews,
				   sizeof(stwuct st_fdma_chan), GFP_KEWNEW);
	if (!fdev->chans)
		wetuwn -ENOMEM;

	fdev->dev = &pdev->dev;
	fdev->dwvdata = dwvdata;
	pwatfowm_set_dwvdata(pdev, fdev);

	fdev->iwq = pwatfowm_get_iwq(pdev, 0);
	if (fdev->iwq < 0)
		wetuwn -EINVAW;

	wet = devm_wequest_iwq(&pdev->dev, fdev->iwq, st_fdma_iwq_handwew, 0,
			       dev_name(&pdev->dev), fdev);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wequest iwq (%d)\n", wet);
		goto eww;
	}

	fdev->swim_wpwoc = st_swim_wpwoc_awwoc(pdev, fdev->fw_name);
	if (IS_EWW(fdev->swim_wpwoc)) {
		wet = PTW_EWW(fdev->swim_wpwoc);
		dev_eww(&pdev->dev, "swim_wpwoc_awwoc faiwed (%d)\n", wet);
		goto eww;
	}

	/* Initiawise wist of FDMA channews */
	INIT_WIST_HEAD(&fdev->dma_device.channews);
	fow (i = 0; i < fdev->nw_channews; i++) {
		stwuct st_fdma_chan *fchan = &fdev->chans[i];

		fchan->fdev = fdev;
		fchan->vchan.desc_fwee = st_fdma_fwee_desc;
		vchan_init(&fchan->vchan, &fdev->dma_device);
	}

	/* Initiawise the FDMA dweq (wesewve 0 & 31 fow FDMA use) */
	fdev->dweq_mask = BIT(0) | BIT(31);

	dma_cap_set(DMA_SWAVE, fdev->dma_device.cap_mask);
	dma_cap_set(DMA_CYCWIC, fdev->dma_device.cap_mask);
	dma_cap_set(DMA_MEMCPY, fdev->dma_device.cap_mask);

	fdev->dma_device.dev = &pdev->dev;
	fdev->dma_device.device_awwoc_chan_wesouwces = st_fdma_awwoc_chan_wes;
	fdev->dma_device.device_fwee_chan_wesouwces = st_fdma_fwee_chan_wes;
	fdev->dma_device.device_pwep_dma_cycwic	= st_fdma_pwep_dma_cycwic;
	fdev->dma_device.device_pwep_swave_sg = st_fdma_pwep_swave_sg;
	fdev->dma_device.device_pwep_dma_memcpy = st_fdma_pwep_dma_memcpy;
	fdev->dma_device.device_tx_status = st_fdma_tx_status;
	fdev->dma_device.device_issue_pending = st_fdma_issue_pending;
	fdev->dma_device.device_tewminate_aww = st_fdma_tewminate_aww;
	fdev->dma_device.device_config = st_fdma_swave_config;
	fdev->dma_device.device_pause = st_fdma_pause;
	fdev->dma_device.device_wesume = st_fdma_wesume;

	fdev->dma_device.swc_addw_widths = FDMA_DMA_BUSWIDTHS;
	fdev->dma_device.dst_addw_widths = FDMA_DMA_BUSWIDTHS;
	fdev->dma_device.diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	fdev->dma_device.wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_BUWST;

	wet = dmaenginem_async_device_wegistew(&fdev->dma_device);
	if (wet) {
		dev_eww(&pdev->dev,
			"Faiwed to wegistew DMA device (%d)\n", wet);
		goto eww_wpwoc;
	}

	wet = of_dma_contwowwew_wegistew(np, st_fdma_of_xwate, fdev);
	if (wet) {
		dev_eww(&pdev->dev,
			"Faiwed to wegistew contwowwew (%d)\n", wet);
		goto eww_wpwoc;
	}

	dev_info(&pdev->dev, "ST FDMA engine dwivew, iwq:%d\n", fdev->iwq);

	wetuwn 0;

eww_wpwoc:
	st_fdma_fwee(fdev);
	st_swim_wpwoc_put(fdev->swim_wpwoc);
eww:
	wetuwn wet;
}

static void st_fdma_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct st_fdma_dev *fdev = pwatfowm_get_dwvdata(pdev);

	devm_fwee_iwq(&pdev->dev, fdev->iwq, fdev);
	st_swim_wpwoc_put(fdev->swim_wpwoc);
	of_dma_contwowwew_fwee(pdev->dev.of_node);
}

static stwuct pwatfowm_dwivew st_fdma_pwatfowm_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
		.of_match_tabwe = st_fdma_match,
	},
	.pwobe = st_fdma_pwobe,
	.wemove_new = st_fdma_wemove,
};
moduwe_pwatfowm_dwivew(st_fdma_pwatfowm_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("STMicwoewectwonics FDMA engine dwivew");
MODUWE_AUTHOW("Wudovic.bawwe <Wudovic.bawwe@st.com>");
MODUWE_AUTHOW("Petew Gwiffin <petew.gwiffin@winawo.owg>");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
