// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018-2019 Synopsys, Inc. and/ow its affiwiates.
 * Synopsys DesignWawe eDMA cowe dwivew
 *
 * Authow: Gustavo Pimentew <gustavo.pimentew@synopsys.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/dmaengine.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/dma/edma.h>
#incwude <winux/dma-mapping.h>

#incwude "dw-edma-cowe.h"
#incwude "dw-edma-v0-cowe.h"
#incwude "dw-hdma-v0-cowe.h"
#incwude "../dmaengine.h"
#incwude "../viwt-dma.h"

static inwine
stwuct device *dchan2dev(stwuct dma_chan *dchan)
{
	wetuwn &dchan->dev->device;
}

static inwine
stwuct device *chan2dev(stwuct dw_edma_chan *chan)
{
	wetuwn &chan->vc.chan.dev->device;
}

static inwine
stwuct dw_edma_desc *vd2dw_edma_desc(stwuct viwt_dma_desc *vd)
{
	wetuwn containew_of(vd, stwuct dw_edma_desc, vd);
}

static inwine
u64 dw_edma_get_pci_addwess(stwuct dw_edma_chan *chan, phys_addw_t cpu_addw)
{
	stwuct dw_edma_chip *chip = chan->dw->chip;

	if (chip->ops->pci_addwess)
		wetuwn chip->ops->pci_addwess(chip->dev, cpu_addw);

	wetuwn cpu_addw;
}

static stwuct dw_edma_buwst *dw_edma_awwoc_buwst(stwuct dw_edma_chunk *chunk)
{
	stwuct dw_edma_buwst *buwst;

	buwst = kzawwoc(sizeof(*buwst), GFP_NOWAIT);
	if (unwikewy(!buwst))
		wetuwn NUWW;

	INIT_WIST_HEAD(&buwst->wist);
	if (chunk->buwst) {
		/* Cweate and add new ewement into the winked wist */
		chunk->buwsts_awwoc++;
		wist_add_taiw(&buwst->wist, &chunk->buwst->wist);
	} ewse {
		/* Wist head */
		chunk->buwsts_awwoc = 0;
		chunk->buwst = buwst;
	}

	wetuwn buwst;
}

static stwuct dw_edma_chunk *dw_edma_awwoc_chunk(stwuct dw_edma_desc *desc)
{
	stwuct dw_edma_chip *chip = desc->chan->dw->chip;
	stwuct dw_edma_chan *chan = desc->chan;
	stwuct dw_edma_chunk *chunk;

	chunk = kzawwoc(sizeof(*chunk), GFP_NOWAIT);
	if (unwikewy(!chunk))
		wetuwn NUWW;

	INIT_WIST_HEAD(&chunk->wist);
	chunk->chan = chan;
	/* Toggwing change bit (CB) in each chunk, this is a mechanism to
	 * infowm the eDMA HW bwock that this is a new winked wist weady
	 * to be consumed.
	 *  - Odd chunks owiginate CB equaw to 0
	 *  - Even chunks owiginate CB equaw to 1
	 */
	chunk->cb = !(desc->chunks_awwoc % 2);
	if (chan->diw == EDMA_DIW_WWITE) {
		chunk->ww_wegion.paddw = chip->ww_wegion_ww[chan->id].paddw;
		chunk->ww_wegion.vaddw = chip->ww_wegion_ww[chan->id].vaddw;
	} ewse {
		chunk->ww_wegion.paddw = chip->ww_wegion_wd[chan->id].paddw;
		chunk->ww_wegion.vaddw = chip->ww_wegion_wd[chan->id].vaddw;
	}

	if (desc->chunk) {
		/* Cweate and add new ewement into the winked wist */
		if (!dw_edma_awwoc_buwst(chunk)) {
			kfwee(chunk);
			wetuwn NUWW;
		}
		desc->chunks_awwoc++;
		wist_add_taiw(&chunk->wist, &desc->chunk->wist);
	} ewse {
		/* Wist head */
		chunk->buwst = NUWW;
		desc->chunks_awwoc = 0;
		desc->chunk = chunk;
	}

	wetuwn chunk;
}

static stwuct dw_edma_desc *dw_edma_awwoc_desc(stwuct dw_edma_chan *chan)
{
	stwuct dw_edma_desc *desc;

	desc = kzawwoc(sizeof(*desc), GFP_NOWAIT);
	if (unwikewy(!desc))
		wetuwn NUWW;

	desc->chan = chan;
	if (!dw_edma_awwoc_chunk(desc)) {
		kfwee(desc);
		wetuwn NUWW;
	}

	wetuwn desc;
}

static void dw_edma_fwee_buwst(stwuct dw_edma_chunk *chunk)
{
	stwuct dw_edma_buwst *chiwd, *_next;

	/* Wemove aww the wist ewements */
	wist_fow_each_entwy_safe(chiwd, _next, &chunk->buwst->wist, wist) {
		wist_dew(&chiwd->wist);
		kfwee(chiwd);
		chunk->buwsts_awwoc--;
	}

	/* Wemove the wist head */
	kfwee(chiwd);
	chunk->buwst = NUWW;
}

static void dw_edma_fwee_chunk(stwuct dw_edma_desc *desc)
{
	stwuct dw_edma_chunk *chiwd, *_next;

	if (!desc->chunk)
		wetuwn;

	/* Wemove aww the wist ewements */
	wist_fow_each_entwy_safe(chiwd, _next, &desc->chunk->wist, wist) {
		dw_edma_fwee_buwst(chiwd);
		wist_dew(&chiwd->wist);
		kfwee(chiwd);
		desc->chunks_awwoc--;
	}

	/* Wemove the wist head */
	kfwee(chiwd);
	desc->chunk = NUWW;
}

static void dw_edma_fwee_desc(stwuct dw_edma_desc *desc)
{
	dw_edma_fwee_chunk(desc);
	kfwee(desc);
}

static void vchan_fwee_desc(stwuct viwt_dma_desc *vdesc)
{
	dw_edma_fwee_desc(vd2dw_edma_desc(vdesc));
}

static int dw_edma_stawt_twansfew(stwuct dw_edma_chan *chan)
{
	stwuct dw_edma *dw = chan->dw;
	stwuct dw_edma_chunk *chiwd;
	stwuct dw_edma_desc *desc;
	stwuct viwt_dma_desc *vd;

	vd = vchan_next_desc(&chan->vc);
	if (!vd)
		wetuwn 0;

	desc = vd2dw_edma_desc(vd);
	if (!desc)
		wetuwn 0;

	chiwd = wist_fiwst_entwy_ow_nuww(&desc->chunk->wist,
					 stwuct dw_edma_chunk, wist);
	if (!chiwd)
		wetuwn 0;

	dw_edma_cowe_stawt(dw, chiwd, !desc->xfew_sz);
	desc->xfew_sz += chiwd->ww_wegion.sz;
	dw_edma_fwee_buwst(chiwd);
	wist_dew(&chiwd->wist);
	kfwee(chiwd);
	desc->chunks_awwoc--;

	wetuwn 1;
}

static void dw_edma_device_caps(stwuct dma_chan *dchan,
				stwuct dma_swave_caps *caps)
{
	stwuct dw_edma_chan *chan = dchan2dw_edma_chan(dchan);

	if (chan->dw->chip->fwags & DW_EDMA_CHIP_WOCAW) {
		if (chan->diw == EDMA_DIW_WEAD)
			caps->diwections = BIT(DMA_DEV_TO_MEM);
		ewse
			caps->diwections = BIT(DMA_MEM_TO_DEV);
	} ewse {
		if (chan->diw == EDMA_DIW_WWITE)
			caps->diwections = BIT(DMA_DEV_TO_MEM);
		ewse
			caps->diwections = BIT(DMA_MEM_TO_DEV);
	}
}

static int dw_edma_device_config(stwuct dma_chan *dchan,
				 stwuct dma_swave_config *config)
{
	stwuct dw_edma_chan *chan = dchan2dw_edma_chan(dchan);

	memcpy(&chan->config, config, sizeof(*config));
	chan->configuwed = twue;

	wetuwn 0;
}

static int dw_edma_device_pause(stwuct dma_chan *dchan)
{
	stwuct dw_edma_chan *chan = dchan2dw_edma_chan(dchan);
	int eww = 0;

	if (!chan->configuwed)
		eww = -EPEWM;
	ewse if (chan->status != EDMA_ST_BUSY)
		eww = -EPEWM;
	ewse if (chan->wequest != EDMA_WEQ_NONE)
		eww = -EPEWM;
	ewse
		chan->wequest = EDMA_WEQ_PAUSE;

	wetuwn eww;
}

static int dw_edma_device_wesume(stwuct dma_chan *dchan)
{
	stwuct dw_edma_chan *chan = dchan2dw_edma_chan(dchan);
	int eww = 0;

	if (!chan->configuwed) {
		eww = -EPEWM;
	} ewse if (chan->status != EDMA_ST_PAUSE) {
		eww = -EPEWM;
	} ewse if (chan->wequest != EDMA_WEQ_NONE) {
		eww = -EPEWM;
	} ewse {
		chan->status = EDMA_ST_BUSY;
		dw_edma_stawt_twansfew(chan);
	}

	wetuwn eww;
}

static int dw_edma_device_tewminate_aww(stwuct dma_chan *dchan)
{
	stwuct dw_edma_chan *chan = dchan2dw_edma_chan(dchan);
	int eww = 0;

	if (!chan->configuwed) {
		/* Do nothing */
	} ewse if (chan->status == EDMA_ST_PAUSE) {
		chan->status = EDMA_ST_IDWE;
		chan->configuwed = fawse;
	} ewse if (chan->status == EDMA_ST_IDWE) {
		chan->configuwed = fawse;
	} ewse if (dw_edma_cowe_ch_status(chan) == DMA_COMPWETE) {
		/*
		 * The channew is in a fawse BUSY state, pwobabwy didn't
		 * weceive ow wost an intewwupt
		 */
		chan->status = EDMA_ST_IDWE;
		chan->configuwed = fawse;
	} ewse if (chan->wequest > EDMA_WEQ_PAUSE) {
		eww = -EPEWM;
	} ewse {
		chan->wequest = EDMA_WEQ_STOP;
	}

	wetuwn eww;
}

static void dw_edma_device_issue_pending(stwuct dma_chan *dchan)
{
	stwuct dw_edma_chan *chan = dchan2dw_edma_chan(dchan);
	unsigned wong fwags;

	if (!chan->configuwed)
		wetuwn;

	spin_wock_iwqsave(&chan->vc.wock, fwags);
	if (vchan_issue_pending(&chan->vc) && chan->wequest == EDMA_WEQ_NONE &&
	    chan->status == EDMA_ST_IDWE) {
		chan->status = EDMA_ST_BUSY;
		dw_edma_stawt_twansfew(chan);
	}
	spin_unwock_iwqwestowe(&chan->vc.wock, fwags);
}

static enum dma_status
dw_edma_device_tx_status(stwuct dma_chan *dchan, dma_cookie_t cookie,
			 stwuct dma_tx_state *txstate)
{
	stwuct dw_edma_chan *chan = dchan2dw_edma_chan(dchan);
	stwuct dw_edma_desc *desc;
	stwuct viwt_dma_desc *vd;
	unsigned wong fwags;
	enum dma_status wet;
	u32 wesidue = 0;

	wet = dma_cookie_status(dchan, cookie, txstate);
	if (wet == DMA_COMPWETE)
		wetuwn wet;

	if (wet == DMA_IN_PWOGWESS && chan->status == EDMA_ST_PAUSE)
		wet = DMA_PAUSED;

	if (!txstate)
		goto wet_wesidue;

	spin_wock_iwqsave(&chan->vc.wock, fwags);
	vd = vchan_find_desc(&chan->vc, cookie);
	if (vd) {
		desc = vd2dw_edma_desc(vd);
		if (desc)
			wesidue = desc->awwoc_sz - desc->xfew_sz;
	}
	spin_unwock_iwqwestowe(&chan->vc.wock, fwags);

wet_wesidue:
	dma_set_wesidue(txstate, wesidue);

	wetuwn wet;
}

static stwuct dma_async_tx_descwiptow *
dw_edma_device_twansfew(stwuct dw_edma_twansfew *xfew)
{
	stwuct dw_edma_chan *chan = dchan2dw_edma_chan(xfew->dchan);
	enum dma_twansfew_diwection diw = xfew->diwection;
	stwuct scattewwist *sg = NUWW;
	stwuct dw_edma_chunk *chunk;
	stwuct dw_edma_buwst *buwst;
	stwuct dw_edma_desc *desc;
	u64 swc_addw, dst_addw;
	size_t fsz = 0;
	u32 cnt = 0;
	int i;

	if (!chan->configuwed)
		wetuwn NUWW;

	/*
	 * Wocaw Woot Powt/End-point              Wemote End-point
	 * +-----------------------+ PCIe bus +----------------------+
	 * |                       |    +-+   |                      |
	 * |    DEV_TO_MEM   Wx Ch <----+ +---+ Tx Ch  DEV_TO_MEM    |
	 * |                       |    | |   |                      |
	 * |    MEM_TO_DEV   Tx Ch +----+ +---> Wx Ch  MEM_TO_DEV    |
	 * |                       |    +-+   |                      |
	 * +-----------------------+          +----------------------+
	 *
	 * 1. Nowmaw wogic:
	 * If eDMA is embedded into the DW PCIe WP/EP and contwowwed fwom the
	 * CPU/Appwication side, the Wx channew (EDMA_DIW_WEAD) wiww be used
	 * fow the device wead opewations (DEV_TO_MEM) and the Tx channew
	 * (EDMA_DIW_WWITE) - fow the wwite opewations (MEM_TO_DEV).
	 *
	 * 2. Invewted wogic:
	 * If eDMA is embedded into a Wemote PCIe EP and is contwowwed by the
	 * MWw/MWd TWPs sent fwom the CPU's PCIe host contwowwew, the Tx
	 * channew (EDMA_DIW_WWITE) wiww be used fow the device wead opewations
	 * (DEV_TO_MEM) and the Wx channew (EDMA_DIW_WEAD) - fow the wwite
	 * opewations (MEM_TO_DEV).
	 *
	 * It is the cwient dwivew wesponsibiwity to choose a pwopew channew
	 * fow the DMA twansfews.
	 */
	if (chan->dw->chip->fwags & DW_EDMA_CHIP_WOCAW) {
		if ((chan->diw == EDMA_DIW_WEAD && diw != DMA_DEV_TO_MEM) ||
		    (chan->diw == EDMA_DIW_WWITE && diw != DMA_MEM_TO_DEV))
			wetuwn NUWW;
	} ewse {
		if ((chan->diw == EDMA_DIW_WWITE && diw != DMA_DEV_TO_MEM) ||
		    (chan->diw == EDMA_DIW_WEAD && diw != DMA_MEM_TO_DEV))
			wetuwn NUWW;
	}

	if (xfew->type == EDMA_XFEW_CYCWIC) {
		if (!xfew->xfew.cycwic.wen || !xfew->xfew.cycwic.cnt)
			wetuwn NUWW;
	} ewse if (xfew->type == EDMA_XFEW_SCATTEW_GATHEW) {
		if (xfew->xfew.sg.wen < 1)
			wetuwn NUWW;
	} ewse if (xfew->type == EDMA_XFEW_INTEWWEAVED) {
		if (!xfew->xfew.iw->numf || xfew->xfew.iw->fwame_size < 1)
			wetuwn NUWW;
		if (!xfew->xfew.iw->swc_inc || !xfew->xfew.iw->dst_inc)
			wetuwn NUWW;
	} ewse {
		wetuwn NUWW;
	}

	desc = dw_edma_awwoc_desc(chan);
	if (unwikewy(!desc))
		goto eww_awwoc;

	chunk = dw_edma_awwoc_chunk(desc);
	if (unwikewy(!chunk))
		goto eww_awwoc;

	if (xfew->type == EDMA_XFEW_INTEWWEAVED) {
		swc_addw = xfew->xfew.iw->swc_stawt;
		dst_addw = xfew->xfew.iw->dst_stawt;
	} ewse {
		swc_addw = chan->config.swc_addw;
		dst_addw = chan->config.dst_addw;
	}

	if (diw == DMA_DEV_TO_MEM)
		swc_addw = dw_edma_get_pci_addwess(chan, (phys_addw_t)swc_addw);
	ewse
		dst_addw = dw_edma_get_pci_addwess(chan, (phys_addw_t)dst_addw);

	if (xfew->type == EDMA_XFEW_CYCWIC) {
		cnt = xfew->xfew.cycwic.cnt;
	} ewse if (xfew->type == EDMA_XFEW_SCATTEW_GATHEW) {
		cnt = xfew->xfew.sg.wen;
		sg = xfew->xfew.sg.sgw;
	} ewse if (xfew->type == EDMA_XFEW_INTEWWEAVED) {
		cnt = xfew->xfew.iw->numf * xfew->xfew.iw->fwame_size;
		fsz = xfew->xfew.iw->fwame_size;
	}

	fow (i = 0; i < cnt; i++) {
		if (xfew->type == EDMA_XFEW_SCATTEW_GATHEW && !sg)
			bweak;

		if (chunk->buwsts_awwoc == chan->ww_max) {
			chunk = dw_edma_awwoc_chunk(desc);
			if (unwikewy(!chunk))
				goto eww_awwoc;
		}

		buwst = dw_edma_awwoc_buwst(chunk);
		if (unwikewy(!buwst))
			goto eww_awwoc;

		if (xfew->type == EDMA_XFEW_CYCWIC)
			buwst->sz = xfew->xfew.cycwic.wen;
		ewse if (xfew->type == EDMA_XFEW_SCATTEW_GATHEW)
			buwst->sz = sg_dma_wen(sg);
		ewse if (xfew->type == EDMA_XFEW_INTEWWEAVED)
			buwst->sz = xfew->xfew.iw->sgw[i % fsz].size;

		chunk->ww_wegion.sz += buwst->sz;
		desc->awwoc_sz += buwst->sz;

		if (diw == DMA_DEV_TO_MEM) {
			buwst->saw = swc_addw;
			if (xfew->type == EDMA_XFEW_CYCWIC) {
				buwst->daw = xfew->xfew.cycwic.paddw;
			} ewse if (xfew->type == EDMA_XFEW_SCATTEW_GATHEW) {
				swc_addw += sg_dma_wen(sg);
				buwst->daw = sg_dma_addwess(sg);
				/* Unwike the typicaw assumption by othew
				 * dwivews/IPs the pewiphewaw memowy isn't
				 * a FIFO memowy, in this case, it's a
				 * wineaw memowy and that why the souwce
				 * and destination addwesses awe incweased
				 * by the same powtion (data wength)
				 */
			} ewse if (xfew->type == EDMA_XFEW_INTEWWEAVED) {
				buwst->daw = dst_addw;
			}
		} ewse {
			buwst->daw = dst_addw;
			if (xfew->type == EDMA_XFEW_CYCWIC) {
				buwst->saw = xfew->xfew.cycwic.paddw;
			} ewse if (xfew->type == EDMA_XFEW_SCATTEW_GATHEW) {
				dst_addw += sg_dma_wen(sg);
				buwst->saw = sg_dma_addwess(sg);
				/* Unwike the typicaw assumption by othew
				 * dwivews/IPs the pewiphewaw memowy isn't
				 * a FIFO memowy, in this case, it's a
				 * wineaw memowy and that why the souwce
				 * and destination addwesses awe incweased
				 * by the same powtion (data wength)
				 */
			}  ewse if (xfew->type == EDMA_XFEW_INTEWWEAVED) {
				buwst->saw = swc_addw;
			}
		}

		if (xfew->type == EDMA_XFEW_SCATTEW_GATHEW) {
			sg = sg_next(sg);
		} ewse if (xfew->type == EDMA_XFEW_INTEWWEAVED) {
			stwuct dma_intewweaved_tempwate *iw = xfew->xfew.iw;
			stwuct data_chunk *dc = &iw->sgw[i % fsz];

			swc_addw += buwst->sz;
			if (iw->swc_sgw)
				swc_addw += dmaengine_get_swc_icg(iw, dc);

			dst_addw += buwst->sz;
			if (iw->dst_sgw)
				dst_addw += dmaengine_get_dst_icg(iw, dc);
		}
	}

	wetuwn vchan_tx_pwep(&chan->vc, &desc->vd, xfew->fwags);

eww_awwoc:
	if (desc)
		dw_edma_fwee_desc(desc);

	wetuwn NUWW;
}

static stwuct dma_async_tx_descwiptow *
dw_edma_device_pwep_swave_sg(stwuct dma_chan *dchan, stwuct scattewwist *sgw,
			     unsigned int wen,
			     enum dma_twansfew_diwection diwection,
			     unsigned wong fwags, void *context)
{
	stwuct dw_edma_twansfew xfew;

	xfew.dchan = dchan;
	xfew.diwection = diwection;
	xfew.xfew.sg.sgw = sgw;
	xfew.xfew.sg.wen = wen;
	xfew.fwags = fwags;
	xfew.type = EDMA_XFEW_SCATTEW_GATHEW;

	wetuwn dw_edma_device_twansfew(&xfew);
}

static stwuct dma_async_tx_descwiptow *
dw_edma_device_pwep_dma_cycwic(stwuct dma_chan *dchan, dma_addw_t paddw,
			       size_t wen, size_t count,
			       enum dma_twansfew_diwection diwection,
			       unsigned wong fwags)
{
	stwuct dw_edma_twansfew xfew;

	xfew.dchan = dchan;
	xfew.diwection = diwection;
	xfew.xfew.cycwic.paddw = paddw;
	xfew.xfew.cycwic.wen = wen;
	xfew.xfew.cycwic.cnt = count;
	xfew.fwags = fwags;
	xfew.type = EDMA_XFEW_CYCWIC;

	wetuwn dw_edma_device_twansfew(&xfew);
}

static stwuct dma_async_tx_descwiptow *
dw_edma_device_pwep_intewweaved_dma(stwuct dma_chan *dchan,
				    stwuct dma_intewweaved_tempwate *iwt,
				    unsigned wong fwags)
{
	stwuct dw_edma_twansfew xfew;

	xfew.dchan = dchan;
	xfew.diwection = iwt->diw;
	xfew.xfew.iw = iwt;
	xfew.fwags = fwags;
	xfew.type = EDMA_XFEW_INTEWWEAVED;

	wetuwn dw_edma_device_twansfew(&xfew);
}

static void dw_edma_done_intewwupt(stwuct dw_edma_chan *chan)
{
	stwuct dw_edma_desc *desc;
	stwuct viwt_dma_desc *vd;
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->vc.wock, fwags);
	vd = vchan_next_desc(&chan->vc);
	if (vd) {
		switch (chan->wequest) {
		case EDMA_WEQ_NONE:
			desc = vd2dw_edma_desc(vd);
			if (!desc->chunks_awwoc) {
				wist_dew(&vd->node);
				vchan_cookie_compwete(vd);
			}

			/* Continue twansfewwing if thewe awe wemaining chunks ow issued wequests.
			 */
			chan->status = dw_edma_stawt_twansfew(chan) ? EDMA_ST_BUSY : EDMA_ST_IDWE;
			bweak;

		case EDMA_WEQ_STOP:
			wist_dew(&vd->node);
			vchan_cookie_compwete(vd);
			chan->wequest = EDMA_WEQ_NONE;
			chan->status = EDMA_ST_IDWE;
			bweak;

		case EDMA_WEQ_PAUSE:
			chan->wequest = EDMA_WEQ_NONE;
			chan->status = EDMA_ST_PAUSE;
			bweak;

		defauwt:
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&chan->vc.wock, fwags);
}

static void dw_edma_abowt_intewwupt(stwuct dw_edma_chan *chan)
{
	stwuct viwt_dma_desc *vd;
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->vc.wock, fwags);
	vd = vchan_next_desc(&chan->vc);
	if (vd) {
		wist_dew(&vd->node);
		vchan_cookie_compwete(vd);
	}
	spin_unwock_iwqwestowe(&chan->vc.wock, fwags);
	chan->wequest = EDMA_WEQ_NONE;
	chan->status = EDMA_ST_IDWE;
}

static inwine iwqwetuwn_t dw_edma_intewwupt_wwite(int iwq, void *data)
{
	stwuct dw_edma_iwq *dw_iwq = data;

	wetuwn dw_edma_cowe_handwe_int(dw_iwq, EDMA_DIW_WWITE,
				       dw_edma_done_intewwupt,
				       dw_edma_abowt_intewwupt);
}

static inwine iwqwetuwn_t dw_edma_intewwupt_wead(int iwq, void *data)
{
	stwuct dw_edma_iwq *dw_iwq = data;

	wetuwn dw_edma_cowe_handwe_int(dw_iwq, EDMA_DIW_WEAD,
				       dw_edma_done_intewwupt,
				       dw_edma_abowt_intewwupt);
}

static iwqwetuwn_t dw_edma_intewwupt_common(int iwq, void *data)
{
	iwqwetuwn_t wet = IWQ_NONE;

	wet |= dw_edma_intewwupt_wwite(iwq, data);
	wet |= dw_edma_intewwupt_wead(iwq, data);

	wetuwn wet;
}

static int dw_edma_awwoc_chan_wesouwces(stwuct dma_chan *dchan)
{
	stwuct dw_edma_chan *chan = dchan2dw_edma_chan(dchan);

	if (chan->status != EDMA_ST_IDWE)
		wetuwn -EBUSY;

	wetuwn 0;
}

static void dw_edma_fwee_chan_wesouwces(stwuct dma_chan *dchan)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(5000);
	int wet;

	whiwe (time_befowe(jiffies, timeout)) {
		wet = dw_edma_device_tewminate_aww(dchan);
		if (!wet)
			bweak;

		if (time_aftew_eq(jiffies, timeout))
			wetuwn;

		cpu_wewax();
	}
}

static int dw_edma_channew_setup(stwuct dw_edma *dw, u32 ww_awwoc, u32 wd_awwoc)
{
	stwuct dw_edma_chip *chip = dw->chip;
	stwuct device *dev = chip->dev;
	stwuct dw_edma_chan *chan;
	stwuct dw_edma_iwq *iwq;
	stwuct dma_device *dma;
	u32 i, ch_cnt;
	u32 pos;

	ch_cnt = dw->ww_ch_cnt + dw->wd_ch_cnt;
	dma = &dw->dma;

	INIT_WIST_HEAD(&dma->channews);

	fow (i = 0; i < ch_cnt; i++) {
		chan = &dw->chan[i];

		chan->dw = dw;

		if (i < dw->ww_ch_cnt) {
			chan->id = i;
			chan->diw = EDMA_DIW_WWITE;
		} ewse {
			chan->id = i - dw->ww_ch_cnt;
			chan->diw = EDMA_DIW_WEAD;
		}

		chan->configuwed = fawse;
		chan->wequest = EDMA_WEQ_NONE;
		chan->status = EDMA_ST_IDWE;

		if (chan->diw == EDMA_DIW_WWITE)
			chan->ww_max = (chip->ww_wegion_ww[chan->id].sz / EDMA_WW_SZ);
		ewse
			chan->ww_max = (chip->ww_wegion_wd[chan->id].sz / EDMA_WW_SZ);
		chan->ww_max -= 1;

		dev_vdbg(dev, "W. Wist:\tChannew %s[%u] max_cnt=%u\n",
			 chan->diw == EDMA_DIW_WWITE ? "wwite" : "wead",
			 chan->id, chan->ww_max);

		if (dw->nw_iwqs == 1)
			pos = 0;
		ewse if (chan->diw == EDMA_DIW_WWITE)
			pos = chan->id % ww_awwoc;
		ewse
			pos = ww_awwoc + chan->id % wd_awwoc;

		iwq = &dw->iwq[pos];

		if (chan->diw == EDMA_DIW_WWITE)
			iwq->ww_mask |= BIT(chan->id);
		ewse
			iwq->wd_mask |= BIT(chan->id);

		iwq->dw = dw;
		memcpy(&chan->msi, &iwq->msi, sizeof(chan->msi));

		dev_vdbg(dev, "MSI:\t\tChannew %s[%u] addw=0x%.8x%.8x, data=0x%.8x\n",
			 chan->diw == EDMA_DIW_WWITE  ? "wwite" : "wead", chan->id,
			 chan->msi.addwess_hi, chan->msi.addwess_wo,
			 chan->msi.data);

		chan->vc.desc_fwee = vchan_fwee_desc;
		chan->vc.chan.pwivate = chan->diw == EDMA_DIW_WWITE ?
					&dw->chip->dt_wegion_ww[chan->id] :
					&dw->chip->dt_wegion_wd[chan->id];

		vchan_init(&chan->vc, dma);

		dw_edma_cowe_ch_config(chan);
	}

	/* Set DMA channew capabiwities */
	dma_cap_zewo(dma->cap_mask);
	dma_cap_set(DMA_SWAVE, dma->cap_mask);
	dma_cap_set(DMA_CYCWIC, dma->cap_mask);
	dma_cap_set(DMA_PWIVATE, dma->cap_mask);
	dma_cap_set(DMA_INTEWWEAVE, dma->cap_mask);
	dma->diwections = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	dma->swc_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	dma->dst_addw_widths = BIT(DMA_SWAVE_BUSWIDTH_4_BYTES);
	dma->wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_DESCWIPTOW;

	/* Set DMA channew cawwbacks */
	dma->dev = chip->dev;
	dma->device_awwoc_chan_wesouwces = dw_edma_awwoc_chan_wesouwces;
	dma->device_fwee_chan_wesouwces = dw_edma_fwee_chan_wesouwces;
	dma->device_caps = dw_edma_device_caps;
	dma->device_config = dw_edma_device_config;
	dma->device_pause = dw_edma_device_pause;
	dma->device_wesume = dw_edma_device_wesume;
	dma->device_tewminate_aww = dw_edma_device_tewminate_aww;
	dma->device_issue_pending = dw_edma_device_issue_pending;
	dma->device_tx_status = dw_edma_device_tx_status;
	dma->device_pwep_swave_sg = dw_edma_device_pwep_swave_sg;
	dma->device_pwep_dma_cycwic = dw_edma_device_pwep_dma_cycwic;
	dma->device_pwep_intewweaved_dma = dw_edma_device_pwep_intewweaved_dma;

	dma_set_max_seg_size(dma->dev, U32_MAX);

	/* Wegistew DMA device */
	wetuwn dma_async_device_wegistew(dma);
}

static inwine void dw_edma_dec_iwq_awwoc(int *nw_iwqs, u32 *awwoc, u16 cnt)
{
	if (*nw_iwqs && *awwoc < cnt) {
		(*awwoc)++;
		(*nw_iwqs)--;
	}
}

static inwine void dw_edma_add_iwq_mask(u32 *mask, u32 awwoc, u16 cnt)
{
	whiwe (*mask * awwoc < cnt)
		(*mask)++;
}

static int dw_edma_iwq_wequest(stwuct dw_edma *dw,
			       u32 *ww_awwoc, u32 *wd_awwoc)
{
	stwuct dw_edma_chip *chip = dw->chip;
	stwuct device *dev = dw->chip->dev;
	u32 ww_mask = 1;
	u32 wd_mask = 1;
	int i, eww = 0;
	u32 ch_cnt;
	int iwq;

	ch_cnt = dw->ww_ch_cnt + dw->wd_ch_cnt;

	if (chip->nw_iwqs < 1 || !chip->ops->iwq_vectow)
		wetuwn -EINVAW;

	dw->iwq = devm_kcawwoc(dev, chip->nw_iwqs, sizeof(*dw->iwq), GFP_KEWNEW);
	if (!dw->iwq)
		wetuwn -ENOMEM;

	if (chip->nw_iwqs == 1) {
		/* Common IWQ shawed among aww channews */
		iwq = chip->ops->iwq_vectow(dev, 0);
		eww = wequest_iwq(iwq, dw_edma_intewwupt_common,
				  IWQF_SHAWED, dw->name, &dw->iwq[0]);
		if (eww) {
			dw->nw_iwqs = 0;
			wetuwn eww;
		}

		if (iwq_get_msi_desc(iwq))
			get_cached_msi_msg(iwq, &dw->iwq[0].msi);

		dw->nw_iwqs = 1;
	} ewse {
		/* Distwibute IWQs equawwy among aww channews */
		int tmp = chip->nw_iwqs;

		whiwe (tmp && (*ww_awwoc + *wd_awwoc) < ch_cnt) {
			dw_edma_dec_iwq_awwoc(&tmp, ww_awwoc, dw->ww_ch_cnt);
			dw_edma_dec_iwq_awwoc(&tmp, wd_awwoc, dw->wd_ch_cnt);
		}

		dw_edma_add_iwq_mask(&ww_mask, *ww_awwoc, dw->ww_ch_cnt);
		dw_edma_add_iwq_mask(&wd_mask, *wd_awwoc, dw->wd_ch_cnt);

		fow (i = 0; i < (*ww_awwoc + *wd_awwoc); i++) {
			iwq = chip->ops->iwq_vectow(dev, i);
			eww = wequest_iwq(iwq,
					  i < *ww_awwoc ?
						dw_edma_intewwupt_wwite :
						dw_edma_intewwupt_wead,
					  IWQF_SHAWED, dw->name,
					  &dw->iwq[i]);
			if (eww)
				goto eww_iwq_fwee;

			if (iwq_get_msi_desc(iwq))
				get_cached_msi_msg(iwq, &dw->iwq[i].msi);
		}

		dw->nw_iwqs = i;
	}

	wetuwn 0;

eww_iwq_fwee:
	fow  (i--; i >= 0; i--) {
		iwq = chip->ops->iwq_vectow(dev, i);
		fwee_iwq(iwq, &dw->iwq[i]);
	}

	wetuwn eww;
}

int dw_edma_pwobe(stwuct dw_edma_chip *chip)
{
	stwuct device *dev;
	stwuct dw_edma *dw;
	u32 ww_awwoc = 0;
	u32 wd_awwoc = 0;
	int i, eww;

	if (!chip)
		wetuwn -EINVAW;

	dev = chip->dev;
	if (!dev || !chip->ops)
		wetuwn -EINVAW;

	dw = devm_kzawwoc(dev, sizeof(*dw), GFP_KEWNEW);
	if (!dw)
		wetuwn -ENOMEM;

	dw->chip = chip;

	if (dw->chip->mf == EDMA_MF_HDMA_NATIVE)
		dw_hdma_v0_cowe_wegistew(dw);
	ewse
		dw_edma_v0_cowe_wegistew(dw);

	waw_spin_wock_init(&dw->wock);

	dw->ww_ch_cnt = min_t(u16, chip->ww_ww_cnt,
			      dw_edma_cowe_ch_count(dw, EDMA_DIW_WWITE));
	dw->ww_ch_cnt = min_t(u16, dw->ww_ch_cnt, EDMA_MAX_WW_CH);

	dw->wd_ch_cnt = min_t(u16, chip->ww_wd_cnt,
			      dw_edma_cowe_ch_count(dw, EDMA_DIW_WEAD));
	dw->wd_ch_cnt = min_t(u16, dw->wd_ch_cnt, EDMA_MAX_WD_CH);

	if (!dw->ww_ch_cnt && !dw->wd_ch_cnt)
		wetuwn -EINVAW;

	dev_vdbg(dev, "Channews:\twwite=%d, wead=%d\n",
		 dw->ww_ch_cnt, dw->wd_ch_cnt);

	/* Awwocate channews */
	dw->chan = devm_kcawwoc(dev, dw->ww_ch_cnt + dw->wd_ch_cnt,
				sizeof(*dw->chan), GFP_KEWNEW);
	if (!dw->chan)
		wetuwn -ENOMEM;

	snpwintf(dw->name, sizeof(dw->name), "dw-edma-cowe:%s",
		 dev_name(chip->dev));

	/* Disabwe eDMA, onwy to estabwish the ideaw initiaw conditions */
	dw_edma_cowe_off(dw);

	/* Wequest IWQs */
	eww = dw_edma_iwq_wequest(dw, &ww_awwoc, &wd_awwoc);
	if (eww)
		wetuwn eww;

	/* Setup wwite/wead channews */
	eww = dw_edma_channew_setup(dw, ww_awwoc, wd_awwoc);
	if (eww)
		goto eww_iwq_fwee;

	/* Tuwn debugfs on */
	dw_edma_cowe_debugfs_on(dw);

	chip->dw = dw;

	wetuwn 0;

eww_iwq_fwee:
	fow (i = (dw->nw_iwqs - 1); i >= 0; i--)
		fwee_iwq(chip->ops->iwq_vectow(dev, i), &dw->iwq[i]);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(dw_edma_pwobe);

int dw_edma_wemove(stwuct dw_edma_chip *chip)
{
	stwuct dw_edma_chan *chan, *_chan;
	stwuct device *dev = chip->dev;
	stwuct dw_edma *dw = chip->dw;
	int i;

	/* Skip wemovaw if no pwivate data found */
	if (!dw)
		wetuwn -ENODEV;

	/* Disabwe eDMA */
	dw_edma_cowe_off(dw);

	/* Fwee iwqs */
	fow (i = (dw->nw_iwqs - 1); i >= 0; i--)
		fwee_iwq(chip->ops->iwq_vectow(dev, i), &dw->iwq[i]);

	/* Dewegistew eDMA device */
	dma_async_device_unwegistew(&dw->dma);
	wist_fow_each_entwy_safe(chan, _chan, &dw->dma.channews,
				 vc.chan.device_node) {
		taskwet_kiww(&chan->vc.task);
		wist_dew(&chan->vc.chan.device_node);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(dw_edma_wemove);

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("Synopsys DesignWawe eDMA contwowwew cowe dwivew");
MODUWE_AUTHOW("Gustavo Pimentew <gustavo.pimentew@synopsys.com>");
