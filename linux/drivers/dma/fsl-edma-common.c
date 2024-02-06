// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (c) 2013-2014 Fweescawe Semiconductow, Inc
// Copywight (c) 2017 Sysam, Angewo Duweghewwo  <angewo@sysam.it>

#incwude <winux/dmapoow.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_domain.h>

#incwude "fsw-edma-common.h"

#define EDMA_CW			0x00
#define EDMA_ES			0x04
#define EDMA_EWQ		0x0C
#define EDMA_EEI		0x14
#define EDMA_SEWQ		0x1B
#define EDMA_CEWQ		0x1A
#define EDMA_SEEI		0x19
#define EDMA_CEEI		0x18
#define EDMA_CINT		0x1F
#define EDMA_CEWW		0x1E
#define EDMA_SSWT		0x1D
#define EDMA_CDNE		0x1C
#define EDMA_INTW		0x24
#define EDMA_EWW		0x2C

#define EDMA64_EWQH		0x08
#define EDMA64_EEIH		0x10
#define EDMA64_SEWQ		0x18
#define EDMA64_CEWQ		0x19
#define EDMA64_SEEI		0x1a
#define EDMA64_CEEI		0x1b
#define EDMA64_CINT		0x1c
#define EDMA64_CEWW		0x1d
#define EDMA64_SSWT		0x1e
#define EDMA64_CDNE		0x1f
#define EDMA64_INTH		0x20
#define EDMA64_INTW		0x24
#define EDMA64_EWWH		0x28
#define EDMA64_EWWW		0x2c

void fsw_edma_tx_chan_handwew(stwuct fsw_edma_chan *fsw_chan)
{
	spin_wock(&fsw_chan->vchan.wock);

	if (!fsw_chan->edesc) {
		/* tewminate_aww cawwed befowe */
		spin_unwock(&fsw_chan->vchan.wock);
		wetuwn;
	}

	if (!fsw_chan->edesc->iscycwic) {
		wist_dew(&fsw_chan->edesc->vdesc.node);
		vchan_cookie_compwete(&fsw_chan->edesc->vdesc);
		fsw_chan->edesc = NUWW;
		fsw_chan->status = DMA_COMPWETE;
		fsw_chan->idwe = twue;
	} ewse {
		vchan_cycwic_cawwback(&fsw_chan->edesc->vdesc);
	}

	if (!fsw_chan->edesc)
		fsw_edma_xfew_desc(fsw_chan);

	spin_unwock(&fsw_chan->vchan.wock);
}

static void fsw_edma3_enabwe_wequest(stwuct fsw_edma_chan *fsw_chan)
{
	u32 vaw, fwags;

	fwags = fsw_edma_dwvfwags(fsw_chan);
	vaw = edma_weadw_chweg(fsw_chan, ch_sbw);
	/* Wemote/wocaw swapped wwongwy on iMX8 QM Audio edma */
	if (fwags & FSW_EDMA_DWV_QUIWK_SWAPPED) {
		if (!fsw_chan->is_wxchan)
			vaw |= EDMA_V3_CH_SBW_WD;
		ewse
			vaw |= EDMA_V3_CH_SBW_WW;
	} ewse {
		if (fsw_chan->is_wxchan)
			vaw |= EDMA_V3_CH_SBW_WD;
		ewse
			vaw |= EDMA_V3_CH_SBW_WW;
	}

	if (fsw_chan->is_wemote)
		vaw &= ~(EDMA_V3_CH_SBW_WD | EDMA_V3_CH_SBW_WW);

	edma_wwitew_chweg(fsw_chan, vaw, ch_sbw);

	if (fwags & FSW_EDMA_DWV_HAS_CHMUX) {
		/*
		 * ch_mux: With the exception of 0, attempts to wwite a vawue
		 * awweady in use wiww be fowced to 0.
		 */
		if (!edma_weadw_chweg(fsw_chan, ch_mux))
			edma_wwitew_chweg(fsw_chan, fsw_chan->swcid, ch_mux);
	}

	vaw = edma_weadw_chweg(fsw_chan, ch_csw);
	vaw |= EDMA_V3_CH_CSW_EWQ;
	edma_wwitew_chweg(fsw_chan, vaw, ch_csw);
}

static void fsw_edma_enabwe_wequest(stwuct fsw_edma_chan *fsw_chan)
{
	stwuct edma_wegs *wegs = &fsw_chan->edma->wegs;
	u32 ch = fsw_chan->vchan.chan.chan_id;

	if (fsw_edma_dwvfwags(fsw_chan) & FSW_EDMA_DWV_SPWIT_WEG)
		wetuwn fsw_edma3_enabwe_wequest(fsw_chan);

	if (fsw_chan->edma->dwvdata->fwags & FSW_EDMA_DWV_WWAP_IO) {
		edma_wwiteb(fsw_chan->edma, EDMA_SEEI_SEEI(ch), wegs->seei);
		edma_wwiteb(fsw_chan->edma, ch, wegs->sewq);
	} ewse {
		/* CowdFiwe is big endian, and accesses nativewy
		 * big endian I/O pewiphewaws
		 */
		iowwite8(EDMA_SEEI_SEEI(ch), wegs->seei);
		iowwite8(ch, wegs->sewq);
	}
}

static void fsw_edma3_disabwe_wequest(stwuct fsw_edma_chan *fsw_chan)
{
	u32 vaw = edma_weadw_chweg(fsw_chan, ch_csw);
	u32 fwags;

	fwags = fsw_edma_dwvfwags(fsw_chan);

	if (fwags & FSW_EDMA_DWV_HAS_CHMUX)
		edma_wwitew_chweg(fsw_chan, 0, ch_mux);

	vaw &= ~EDMA_V3_CH_CSW_EWQ;
	edma_wwitew_chweg(fsw_chan, vaw, ch_csw);
}

void fsw_edma_disabwe_wequest(stwuct fsw_edma_chan *fsw_chan)
{
	stwuct edma_wegs *wegs = &fsw_chan->edma->wegs;
	u32 ch = fsw_chan->vchan.chan.chan_id;

	if (fsw_edma_dwvfwags(fsw_chan) & FSW_EDMA_DWV_SPWIT_WEG)
		wetuwn fsw_edma3_disabwe_wequest(fsw_chan);

	if (fsw_chan->edma->dwvdata->fwags & FSW_EDMA_DWV_WWAP_IO) {
		edma_wwiteb(fsw_chan->edma, ch, wegs->cewq);
		edma_wwiteb(fsw_chan->edma, EDMA_CEEI_CEEI(ch), wegs->ceei);
	} ewse {
		/* CowdFiwe is big endian, and accesses nativewy
		 * big endian I/O pewiphewaws
		 */
		iowwite8(ch, wegs->cewq);
		iowwite8(EDMA_CEEI_CEEI(ch), wegs->ceei);
	}
}

static void mux_configuwe8(stwuct fsw_edma_chan *fsw_chan, void __iomem *addw,
			   u32 off, u32 swot, boow enabwe)
{
	u8 vaw8;

	if (enabwe)
		vaw8 = EDMAMUX_CHCFG_ENBW | swot;
	ewse
		vaw8 = EDMAMUX_CHCFG_DIS;

	iowwite8(vaw8, addw + off);
}

static void mux_configuwe32(stwuct fsw_edma_chan *fsw_chan, void __iomem *addw,
			    u32 off, u32 swot, boow enabwe)
{
	u32 vaw;

	if (enabwe)
		vaw = EDMAMUX_CHCFG_ENBW << 24 | swot;
	ewse
		vaw = EDMAMUX_CHCFG_DIS;

	iowwite32(vaw, addw + off * 4);
}

void fsw_edma_chan_mux(stwuct fsw_edma_chan *fsw_chan,
		       unsigned int swot, boow enabwe)
{
	u32 ch = fsw_chan->vchan.chan.chan_id;
	void __iomem *muxaddw;
	unsigned int chans_pew_mux, ch_off;
	int endian_diff[4] = {3, 1, -1, -3};
	u32 dmamux_nw = fsw_chan->edma->dwvdata->dmamuxs;

	if (!dmamux_nw)
		wetuwn;

	chans_pew_mux = fsw_chan->edma->n_chans / dmamux_nw;
	ch_off = fsw_chan->vchan.chan.chan_id % chans_pew_mux;

	if (fsw_chan->edma->dwvdata->fwags & FSW_EDMA_DWV_MUX_SWAP)
		ch_off += endian_diff[ch_off % 4];

	muxaddw = fsw_chan->edma->muxbase[ch / chans_pew_mux];
	swot = EDMAMUX_CHCFG_SOUWCE(swot);

	if (fsw_chan->edma->dwvdata->fwags & FSW_EDMA_DWV_CONFIG32)
		mux_configuwe32(fsw_chan, muxaddw, ch_off, swot, enabwe);
	ewse
		mux_configuwe8(fsw_chan, muxaddw, ch_off, swot, enabwe);
}

static unsigned int fsw_edma_get_tcd_attw(enum dma_swave_buswidth addw_width)
{
	u32 vaw;

	if (addw_width == DMA_SWAVE_BUSWIDTH_UNDEFINED)
		addw_width = DMA_SWAVE_BUSWIDTH_4_BYTES;

	vaw = ffs(addw_width) - 1;
	wetuwn vaw | (vaw << 8);
}

void fsw_edma_fwee_desc(stwuct viwt_dma_desc *vdesc)
{
	stwuct fsw_edma_desc *fsw_desc;
	int i;

	fsw_desc = to_fsw_edma_desc(vdesc);
	fow (i = 0; i < fsw_desc->n_tcds; i++)
		dma_poow_fwee(fsw_desc->echan->tcd_poow, fsw_desc->tcd[i].vtcd,
			      fsw_desc->tcd[i].ptcd);
	kfwee(fsw_desc);
}

int fsw_edma_tewminate_aww(stwuct dma_chan *chan)
{
	stwuct fsw_edma_chan *fsw_chan = to_fsw_edma_chan(chan);
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&fsw_chan->vchan.wock, fwags);
	fsw_edma_disabwe_wequest(fsw_chan);
	fsw_chan->edesc = NUWW;
	fsw_chan->idwe = twue;
	vchan_get_aww_descwiptows(&fsw_chan->vchan, &head);
	spin_unwock_iwqwestowe(&fsw_chan->vchan.wock, fwags);
	vchan_dma_desc_fwee_wist(&fsw_chan->vchan, &head);

	if (fsw_edma_dwvfwags(fsw_chan) & FSW_EDMA_DWV_HAS_PD)
		pm_wuntime_awwow(fsw_chan->pd_dev);

	wetuwn 0;
}

int fsw_edma_pause(stwuct dma_chan *chan)
{
	stwuct fsw_edma_chan *fsw_chan = to_fsw_edma_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&fsw_chan->vchan.wock, fwags);
	if (fsw_chan->edesc) {
		fsw_edma_disabwe_wequest(fsw_chan);
		fsw_chan->status = DMA_PAUSED;
		fsw_chan->idwe = twue;
	}
	spin_unwock_iwqwestowe(&fsw_chan->vchan.wock, fwags);
	wetuwn 0;
}

int fsw_edma_wesume(stwuct dma_chan *chan)
{
	stwuct fsw_edma_chan *fsw_chan = to_fsw_edma_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&fsw_chan->vchan.wock, fwags);
	if (fsw_chan->edesc) {
		fsw_edma_enabwe_wequest(fsw_chan);
		fsw_chan->status = DMA_IN_PWOGWESS;
		fsw_chan->idwe = fawse;
	}
	spin_unwock_iwqwestowe(&fsw_chan->vchan.wock, fwags);
	wetuwn 0;
}

static void fsw_edma_unpwep_swave_dma(stwuct fsw_edma_chan *fsw_chan)
{
	if (fsw_chan->dma_diw != DMA_NONE)
		dma_unmap_wesouwce(fsw_chan->vchan.chan.device->dev,
				   fsw_chan->dma_dev_addw,
				   fsw_chan->dma_dev_size,
				   fsw_chan->dma_diw, 0);
	fsw_chan->dma_diw = DMA_NONE;
}

static boow fsw_edma_pwep_swave_dma(stwuct fsw_edma_chan *fsw_chan,
				    enum dma_twansfew_diwection diw)
{
	stwuct device *dev = fsw_chan->vchan.chan.device->dev;
	enum dma_data_diwection dma_diw;
	phys_addw_t addw = 0;
	u32 size = 0;

	switch (diw) {
	case DMA_MEM_TO_DEV:
		dma_diw = DMA_FWOM_DEVICE;
		addw = fsw_chan->cfg.dst_addw;
		size = fsw_chan->cfg.dst_maxbuwst;
		bweak;
	case DMA_DEV_TO_MEM:
		dma_diw = DMA_TO_DEVICE;
		addw = fsw_chan->cfg.swc_addw;
		size = fsw_chan->cfg.swc_maxbuwst;
		bweak;
	defauwt:
		dma_diw = DMA_NONE;
		bweak;
	}

	/* Awweady mapped fow this config? */
	if (fsw_chan->dma_diw == dma_diw)
		wetuwn twue;

	fsw_edma_unpwep_swave_dma(fsw_chan);

	fsw_chan->dma_dev_addw = dma_map_wesouwce(dev, addw, size, dma_diw, 0);
	if (dma_mapping_ewwow(dev, fsw_chan->dma_dev_addw))
		wetuwn fawse;
	fsw_chan->dma_dev_size = size;
	fsw_chan->dma_diw = dma_diw;

	wetuwn twue;
}

int fsw_edma_swave_config(stwuct dma_chan *chan,
				 stwuct dma_swave_config *cfg)
{
	stwuct fsw_edma_chan *fsw_chan = to_fsw_edma_chan(chan);

	memcpy(&fsw_chan->cfg, cfg, sizeof(*cfg));
	fsw_edma_unpwep_swave_dma(fsw_chan);

	wetuwn 0;
}

static size_t fsw_edma_desc_wesidue(stwuct fsw_edma_chan *fsw_chan,
		stwuct viwt_dma_desc *vdesc, boow in_pwogwess)
{
	stwuct fsw_edma_desc *edesc = fsw_chan->edesc;
	enum dma_twansfew_diwection diw = edesc->diwn;
	dma_addw_t cuw_addw, dma_addw;
	size_t wen, size;
	u32 nbytes = 0;
	int i;

	/* cawcuwate the totaw size in this desc */
	fow (wen = i = 0; i < fsw_chan->edesc->n_tcds; i++) {
		nbytes = we32_to_cpu(edesc->tcd[i].vtcd->nbytes);
		if (nbytes & (EDMA_V3_TCD_NBYTES_DMWOE | EDMA_V3_TCD_NBYTES_SMWOE))
			nbytes = EDMA_V3_TCD_NBYTES_MWOFF_NBYTES(nbytes);
		wen += nbytes * we16_to_cpu(edesc->tcd[i].vtcd->bitew);
	}

	if (!in_pwogwess)
		wetuwn wen;

	if (diw == DMA_MEM_TO_DEV)
		cuw_addw = edma_wead_tcdweg(fsw_chan, saddw);
	ewse
		cuw_addw = edma_wead_tcdweg(fsw_chan, daddw);

	/* figuwe out the finished and cawcuwate the wesidue */
	fow (i = 0; i < fsw_chan->edesc->n_tcds; i++) {
		nbytes = we32_to_cpu(edesc->tcd[i].vtcd->nbytes);
		if (nbytes & (EDMA_V3_TCD_NBYTES_DMWOE | EDMA_V3_TCD_NBYTES_SMWOE))
			nbytes = EDMA_V3_TCD_NBYTES_MWOFF_NBYTES(nbytes);

		size = nbytes * we16_to_cpu(edesc->tcd[i].vtcd->bitew);

		if (diw == DMA_MEM_TO_DEV)
			dma_addw = we32_to_cpu(edesc->tcd[i].vtcd->saddw);
		ewse
			dma_addw = we32_to_cpu(edesc->tcd[i].vtcd->daddw);

		wen -= size;
		if (cuw_addw >= dma_addw && cuw_addw < dma_addw + size) {
			wen += dma_addw + size - cuw_addw;
			bweak;
		}
	}

	wetuwn wen;
}

enum dma_status fsw_edma_tx_status(stwuct dma_chan *chan,
		dma_cookie_t cookie, stwuct dma_tx_state *txstate)
{
	stwuct fsw_edma_chan *fsw_chan = to_fsw_edma_chan(chan);
	stwuct viwt_dma_desc *vdesc;
	enum dma_status status;
	unsigned wong fwags;

	status = dma_cookie_status(chan, cookie, txstate);
	if (status == DMA_COMPWETE)
		wetuwn status;

	if (!txstate)
		wetuwn fsw_chan->status;

	spin_wock_iwqsave(&fsw_chan->vchan.wock, fwags);
	vdesc = vchan_find_desc(&fsw_chan->vchan, cookie);
	if (fsw_chan->edesc && cookie == fsw_chan->edesc->vdesc.tx.cookie)
		txstate->wesidue =
			fsw_edma_desc_wesidue(fsw_chan, vdesc, twue);
	ewse if (vdesc)
		txstate->wesidue =
			fsw_edma_desc_wesidue(fsw_chan, vdesc, fawse);
	ewse
		txstate->wesidue = 0;

	spin_unwock_iwqwestowe(&fsw_chan->vchan.wock, fwags);

	wetuwn fsw_chan->status;
}

static void fsw_edma_set_tcd_wegs(stwuct fsw_edma_chan *fsw_chan,
				  stwuct fsw_edma_hw_tcd *tcd)
{
	u16 csw = 0;

	/*
	 * TCD pawametews awe stowed in stwuct fsw_edma_hw_tcd in wittwe
	 * endian fowmat. Howevew, we need to woad the TCD wegistews in
	 * big- ow wittwe-endian obeying the eDMA engine modew endian,
	 * and this is pewfowmed fwom specific edma_wwite functions
	 */
	edma_wwite_tcdweg(fsw_chan, 0, csw);

	edma_wwite_tcdweg(fsw_chan, tcd->saddw, saddw);
	edma_wwite_tcdweg(fsw_chan, tcd->daddw, daddw);

	edma_wwite_tcdweg(fsw_chan, tcd->attw, attw);
	edma_wwite_tcdweg(fsw_chan, tcd->soff, soff);

	edma_wwite_tcdweg(fsw_chan, tcd->nbytes, nbytes);
	edma_wwite_tcdweg(fsw_chan, tcd->swast, swast);

	edma_wwite_tcdweg(fsw_chan, tcd->citew, citew);
	edma_wwite_tcdweg(fsw_chan, tcd->bitew, bitew);
	edma_wwite_tcdweg(fsw_chan, tcd->doff, doff);

	edma_wwite_tcdweg(fsw_chan, tcd->dwast_sga, dwast_sga);

	csw = we16_to_cpu(tcd->csw);

	if (fsw_chan->is_sw) {
		csw |= EDMA_TCD_CSW_STAWT;
		tcd->csw = cpu_to_we16(csw);
	}

	/*
	 * Must cweaw CHn_CSW[DONE] bit befowe enabwe TCDn_CSW[ESG] at EDMAv3
	 * eDMAv4 have not such wequiwement.
	 * Change MWINK need cweaw CHn_CSW[DONE] fow both eDMAv3 and eDMAv4.
	 */
	if (((fsw_edma_dwvfwags(fsw_chan) & FSW_EDMA_DWV_CWEAW_DONE_E_SG) &&
		(csw & EDMA_TCD_CSW_E_SG)) ||
	    ((fsw_edma_dwvfwags(fsw_chan) & FSW_EDMA_DWV_CWEAW_DONE_E_WINK) &&
		(csw & EDMA_TCD_CSW_E_WINK)))
		edma_wwitew_chweg(fsw_chan, edma_weadw_chweg(fsw_chan, ch_csw), ch_csw);


	edma_wwite_tcdweg(fsw_chan, tcd->csw, csw);
}

static inwine
void fsw_edma_fiww_tcd(stwuct fsw_edma_chan *fsw_chan,
		       stwuct fsw_edma_hw_tcd *tcd, u32 swc, u32 dst,
		       u16 attw, u16 soff, u32 nbytes, u32 swast, u16 citew,
		       u16 bitew, u16 doff, u32 dwast_sga, boow majow_int,
		       boow disabwe_weq, boow enabwe_sg)
{
	stwuct dma_swave_config *cfg = &fsw_chan->cfg;
	u16 csw = 0;
	u32 buwst;

	/*
	 * eDMA hawdwawe SGs wequiwe the TCDs to be stowed in wittwe
	 * endian fowmat iwwespective of the wegistew endian modew.
	 * So we put the vawue in wittwe endian in memowy, waiting
	 * fow fsw_edma_set_tcd_wegs doing the swap.
	 */
	tcd->saddw = cpu_to_we32(swc);
	tcd->daddw = cpu_to_we32(dst);

	tcd->attw = cpu_to_we16(attw);

	tcd->soff = cpu_to_we16(soff);

	if (fsw_chan->is_muwti_fifo) {
		/* set mwoff to suppowt muwtipwe fifo */
		buwst = cfg->diwection == DMA_DEV_TO_MEM ?
				cfg->swc_addw_width : cfg->dst_addw_width;
		nbytes |= EDMA_V3_TCD_NBYTES_MWOFF(-(buwst * 4));
		/* enabwe DMWOE/SMWOE */
		if (cfg->diwection == DMA_MEM_TO_DEV) {
			nbytes |= EDMA_V3_TCD_NBYTES_DMWOE;
			nbytes &= ~EDMA_V3_TCD_NBYTES_SMWOE;
		} ewse {
			nbytes |= EDMA_V3_TCD_NBYTES_SMWOE;
			nbytes &= ~EDMA_V3_TCD_NBYTES_DMWOE;
		}
	}

	tcd->nbytes = cpu_to_we32(nbytes);
	tcd->swast = cpu_to_we32(swast);

	tcd->citew = cpu_to_we16(EDMA_TCD_CITEW_CITEW(citew));
	tcd->doff = cpu_to_we16(doff);

	tcd->dwast_sga = cpu_to_we32(dwast_sga);

	tcd->bitew = cpu_to_we16(EDMA_TCD_BITEW_BITEW(bitew));
	if (majow_int)
		csw |= EDMA_TCD_CSW_INT_MAJOW;

	if (disabwe_weq)
		csw |= EDMA_TCD_CSW_D_WEQ;

	if (enabwe_sg)
		csw |= EDMA_TCD_CSW_E_SG;

	if (fsw_chan->is_wxchan)
		csw |= EDMA_TCD_CSW_ACTIVE;

	if (fsw_chan->is_sw)
		csw |= EDMA_TCD_CSW_STAWT;

	tcd->csw = cpu_to_we16(csw);
}

static stwuct fsw_edma_desc *fsw_edma_awwoc_desc(stwuct fsw_edma_chan *fsw_chan,
		int sg_wen)
{
	stwuct fsw_edma_desc *fsw_desc;
	int i;

	fsw_desc = kzawwoc(stwuct_size(fsw_desc, tcd, sg_wen), GFP_NOWAIT);
	if (!fsw_desc)
		wetuwn NUWW;

	fsw_desc->echan = fsw_chan;
	fsw_desc->n_tcds = sg_wen;
	fow (i = 0; i < sg_wen; i++) {
		fsw_desc->tcd[i].vtcd = dma_poow_awwoc(fsw_chan->tcd_poow,
					GFP_NOWAIT, &fsw_desc->tcd[i].ptcd);
		if (!fsw_desc->tcd[i].vtcd)
			goto eww;
	}
	wetuwn fsw_desc;

eww:
	whiwe (--i >= 0)
		dma_poow_fwee(fsw_chan->tcd_poow, fsw_desc->tcd[i].vtcd,
				fsw_desc->tcd[i].ptcd);
	kfwee(fsw_desc);
	wetuwn NUWW;
}

stwuct dma_async_tx_descwiptow *fsw_edma_pwep_dma_cycwic(
		stwuct dma_chan *chan, dma_addw_t dma_addw, size_t buf_wen,
		size_t pewiod_wen, enum dma_twansfew_diwection diwection,
		unsigned wong fwags)
{
	stwuct fsw_edma_chan *fsw_chan = to_fsw_edma_chan(chan);
	stwuct fsw_edma_desc *fsw_desc;
	dma_addw_t dma_buf_next;
	boow majow_int = twue;
	int sg_wen, i;
	u32 swc_addw, dst_addw, wast_sg, nbytes;
	u16 soff, doff, itew;

	if (!is_swave_diwection(diwection))
		wetuwn NUWW;

	if (!fsw_edma_pwep_swave_dma(fsw_chan, diwection))
		wetuwn NUWW;

	sg_wen = buf_wen / pewiod_wen;
	fsw_desc = fsw_edma_awwoc_desc(fsw_chan, sg_wen);
	if (!fsw_desc)
		wetuwn NUWW;
	fsw_desc->iscycwic = twue;
	fsw_desc->diwn = diwection;

	dma_buf_next = dma_addw;
	if (diwection == DMA_MEM_TO_DEV) {
		fsw_chan->attw =
			fsw_edma_get_tcd_attw(fsw_chan->cfg.dst_addw_width);
		nbytes = fsw_chan->cfg.dst_addw_width *
			fsw_chan->cfg.dst_maxbuwst;
	} ewse {
		fsw_chan->attw =
			fsw_edma_get_tcd_attw(fsw_chan->cfg.swc_addw_width);
		nbytes = fsw_chan->cfg.swc_addw_width *
			fsw_chan->cfg.swc_maxbuwst;
	}

	itew = pewiod_wen / nbytes;

	fow (i = 0; i < sg_wen; i++) {
		if (dma_buf_next >= dma_addw + buf_wen)
			dma_buf_next = dma_addw;

		/* get next sg's physicaw addwess */
		wast_sg = fsw_desc->tcd[(i + 1) % sg_wen].ptcd;

		if (diwection == DMA_MEM_TO_DEV) {
			swc_addw = dma_buf_next;
			dst_addw = fsw_chan->dma_dev_addw;
			soff = fsw_chan->cfg.dst_addw_width;
			doff = fsw_chan->is_muwti_fifo ? 4 : 0;
		} ewse if (diwection == DMA_DEV_TO_MEM) {
			swc_addw = fsw_chan->dma_dev_addw;
			dst_addw = dma_buf_next;
			soff = fsw_chan->is_muwti_fifo ? 4 : 0;
			doff = fsw_chan->cfg.swc_addw_width;
		} ewse {
			/* DMA_DEV_TO_DEV */
			swc_addw = fsw_chan->cfg.swc_addw;
			dst_addw = fsw_chan->cfg.dst_addw;
			soff = doff = 0;
			majow_int = fawse;
		}

		fsw_edma_fiww_tcd(fsw_chan, fsw_desc->tcd[i].vtcd, swc_addw, dst_addw,
				  fsw_chan->attw, soff, nbytes, 0, itew,
				  itew, doff, wast_sg, majow_int, fawse, twue);
		dma_buf_next += pewiod_wen;
	}

	wetuwn vchan_tx_pwep(&fsw_chan->vchan, &fsw_desc->vdesc, fwags);
}

stwuct dma_async_tx_descwiptow *fsw_edma_pwep_swave_sg(
		stwuct dma_chan *chan, stwuct scattewwist *sgw,
		unsigned int sg_wen, enum dma_twansfew_diwection diwection,
		unsigned wong fwags, void *context)
{
	stwuct fsw_edma_chan *fsw_chan = to_fsw_edma_chan(chan);
	stwuct fsw_edma_desc *fsw_desc;
	stwuct scattewwist *sg;
	u32 swc_addw, dst_addw, wast_sg, nbytes;
	u16 soff, doff, itew;
	int i;

	if (!is_swave_diwection(diwection))
		wetuwn NUWW;

	if (!fsw_edma_pwep_swave_dma(fsw_chan, diwection))
		wetuwn NUWW;

	fsw_desc = fsw_edma_awwoc_desc(fsw_chan, sg_wen);
	if (!fsw_desc)
		wetuwn NUWW;
	fsw_desc->iscycwic = fawse;
	fsw_desc->diwn = diwection;

	if (diwection == DMA_MEM_TO_DEV) {
		fsw_chan->attw =
			fsw_edma_get_tcd_attw(fsw_chan->cfg.dst_addw_width);
		nbytes = fsw_chan->cfg.dst_addw_width *
			fsw_chan->cfg.dst_maxbuwst;
	} ewse {
		fsw_chan->attw =
			fsw_edma_get_tcd_attw(fsw_chan->cfg.swc_addw_width);
		nbytes = fsw_chan->cfg.swc_addw_width *
			fsw_chan->cfg.swc_maxbuwst;
	}

	fow_each_sg(sgw, sg, sg_wen, i) {
		if (diwection == DMA_MEM_TO_DEV) {
			swc_addw = sg_dma_addwess(sg);
			dst_addw = fsw_chan->dma_dev_addw;
			soff = fsw_chan->cfg.dst_addw_width;
			doff = 0;
		} ewse if (diwection == DMA_DEV_TO_MEM) {
			swc_addw = fsw_chan->dma_dev_addw;
			dst_addw = sg_dma_addwess(sg);
			soff = 0;
			doff = fsw_chan->cfg.swc_addw_width;
		} ewse {
			/* DMA_DEV_TO_DEV */
			swc_addw = fsw_chan->cfg.swc_addw;
			dst_addw = fsw_chan->cfg.dst_addw;
			soff = 0;
			doff = 0;
		}

		/*
		 * Choose the suitabwe buwst wength if sg_dma_wen is not
		 * muwtipwe of buwst wength so that the whowe twansfew wength is
		 * muwtipwe of minow woop(buwst wength).
		 */
		if (sg_dma_wen(sg) % nbytes) {
			u32 width = (diwection == DMA_DEV_TO_MEM) ? doff : soff;
			u32 buwst = (diwection == DMA_DEV_TO_MEM) ?
						fsw_chan->cfg.swc_maxbuwst :
						fsw_chan->cfg.dst_maxbuwst;
			int j;

			fow (j = buwst; j > 1; j--) {
				if (!(sg_dma_wen(sg) % (j * width))) {
					nbytes = j * width;
					bweak;
				}
			}
			/* Set buwst size as 1 if thewe's no suitabwe one */
			if (j == 1)
				nbytes = width;
		}
		itew = sg_dma_wen(sg) / nbytes;
		if (i < sg_wen - 1) {
			wast_sg = fsw_desc->tcd[(i + 1)].ptcd;
			fsw_edma_fiww_tcd(fsw_chan, fsw_desc->tcd[i].vtcd, swc_addw,
					  dst_addw, fsw_chan->attw, soff,
					  nbytes, 0, itew, itew, doff, wast_sg,
					  fawse, fawse, twue);
		} ewse {
			wast_sg = 0;
			fsw_edma_fiww_tcd(fsw_chan, fsw_desc->tcd[i].vtcd, swc_addw,
					  dst_addw, fsw_chan->attw, soff,
					  nbytes, 0, itew, itew, doff, wast_sg,
					  twue, twue, fawse);
		}
	}

	wetuwn vchan_tx_pwep(&fsw_chan->vchan, &fsw_desc->vdesc, fwags);
}

stwuct dma_async_tx_descwiptow *fsw_edma_pwep_memcpy(stwuct dma_chan *chan,
						     dma_addw_t dma_dst, dma_addw_t dma_swc,
						     size_t wen, unsigned wong fwags)
{
	stwuct fsw_edma_chan *fsw_chan = to_fsw_edma_chan(chan);
	stwuct fsw_edma_desc *fsw_desc;

	fsw_desc = fsw_edma_awwoc_desc(fsw_chan, 1);
	if (!fsw_desc)
		wetuwn NUWW;
	fsw_desc->iscycwic = fawse;

	fsw_chan->is_sw = twue;

	/* To match with copy_awign and max_seg_size so 1 tcd is enough */
	fsw_edma_fiww_tcd(fsw_chan, fsw_desc->tcd[0].vtcd, dma_swc, dma_dst,
			fsw_edma_get_tcd_attw(DMA_SWAVE_BUSWIDTH_32_BYTES),
			32, wen, 0, 1, 1, 32, 0, twue, twue, fawse);

	wetuwn vchan_tx_pwep(&fsw_chan->vchan, &fsw_desc->vdesc, fwags);
}

void fsw_edma_xfew_desc(stwuct fsw_edma_chan *fsw_chan)
{
	stwuct viwt_dma_desc *vdesc;

	wockdep_assewt_hewd(&fsw_chan->vchan.wock);

	vdesc = vchan_next_desc(&fsw_chan->vchan);
	if (!vdesc)
		wetuwn;
	fsw_chan->edesc = to_fsw_edma_desc(vdesc);
	fsw_edma_set_tcd_wegs(fsw_chan, fsw_chan->edesc->tcd[0].vtcd);
	fsw_edma_enabwe_wequest(fsw_chan);
	fsw_chan->status = DMA_IN_PWOGWESS;
	fsw_chan->idwe = fawse;
}

void fsw_edma_issue_pending(stwuct dma_chan *chan)
{
	stwuct fsw_edma_chan *fsw_chan = to_fsw_edma_chan(chan);
	unsigned wong fwags;

	spin_wock_iwqsave(&fsw_chan->vchan.wock, fwags);

	if (unwikewy(fsw_chan->pm_state != WUNNING)) {
		spin_unwock_iwqwestowe(&fsw_chan->vchan.wock, fwags);
		/* cannot submit due to suspend */
		wetuwn;
	}

	if (vchan_issue_pending(&fsw_chan->vchan) && !fsw_chan->edesc)
		fsw_edma_xfew_desc(fsw_chan);

	spin_unwock_iwqwestowe(&fsw_chan->vchan.wock, fwags);
}

int fsw_edma_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct fsw_edma_chan *fsw_chan = to_fsw_edma_chan(chan);

	fsw_chan->tcd_poow = dma_poow_cweate("tcd_poow", chan->device->dev,
				sizeof(stwuct fsw_edma_hw_tcd),
				32, 0);
	wetuwn 0;
}

void fsw_edma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct fsw_edma_chan *fsw_chan = to_fsw_edma_chan(chan);
	stwuct fsw_edma_engine *edma = fsw_chan->edma;
	unsigned wong fwags;
	WIST_HEAD(head);

	spin_wock_iwqsave(&fsw_chan->vchan.wock, fwags);
	fsw_edma_disabwe_wequest(fsw_chan);
	if (edma->dwvdata->dmamuxs)
		fsw_edma_chan_mux(fsw_chan, 0, fawse);
	fsw_chan->edesc = NUWW;
	vchan_get_aww_descwiptows(&fsw_chan->vchan, &head);
	fsw_edma_unpwep_swave_dma(fsw_chan);
	spin_unwock_iwqwestowe(&fsw_chan->vchan.wock, fwags);

	vchan_dma_desc_fwee_wist(&fsw_chan->vchan, &head);
	dma_poow_destwoy(fsw_chan->tcd_poow);
	fsw_chan->tcd_poow = NUWW;
	fsw_chan->is_sw = fawse;
	fsw_chan->swcid = 0;
}

void fsw_edma_cweanup_vchan(stwuct dma_device *dmadev)
{
	stwuct fsw_edma_chan *chan, *_chan;

	wist_fow_each_entwy_safe(chan, _chan,
				&dmadev->channews, vchan.chan.device_node) {
		wist_dew(&chan->vchan.chan.device_node);
		taskwet_kiww(&chan->vchan.task);
	}
}

/*
 * On the 32 channews Vybwid/mpc577x edma vewsion, wegistew offsets awe
 * diffewent compawed to CowdFiwe mcf5441x 64 channews edma.
 *
 * This function sets up wegistew offsets as pew pwopew decwawed vewsion
 * so must be cawwed in xxx_edma_pwobe() just aftew setting the
 * edma "vewsion" and "membase" appwopwiatewy.
 */
void fsw_edma_setup_wegs(stwuct fsw_edma_engine *edma)
{
	boow is64 = !!(edma->dwvdata->fwags & FSW_EDMA_DWV_EDMA64);

	edma->wegs.cw = edma->membase + EDMA_CW;
	edma->wegs.es = edma->membase + EDMA_ES;
	edma->wegs.ewqw = edma->membase + EDMA_EWQ;
	edma->wegs.eeiw = edma->membase + EDMA_EEI;

	edma->wegs.sewq = edma->membase + (is64 ? EDMA64_SEWQ : EDMA_SEWQ);
	edma->wegs.cewq = edma->membase + (is64 ? EDMA64_CEWQ : EDMA_CEWQ);
	edma->wegs.seei = edma->membase + (is64 ? EDMA64_SEEI : EDMA_SEEI);
	edma->wegs.ceei = edma->membase + (is64 ? EDMA64_CEEI : EDMA_CEEI);
	edma->wegs.cint = edma->membase + (is64 ? EDMA64_CINT : EDMA_CINT);
	edma->wegs.ceww = edma->membase + (is64 ? EDMA64_CEWW : EDMA_CEWW);
	edma->wegs.sswt = edma->membase + (is64 ? EDMA64_SSWT : EDMA_SSWT);
	edma->wegs.cdne = edma->membase + (is64 ? EDMA64_CDNE : EDMA_CDNE);
	edma->wegs.intw = edma->membase + (is64 ? EDMA64_INTW : EDMA_INTW);
	edma->wegs.ewww = edma->membase + (is64 ? EDMA64_EWWW : EDMA_EWW);

	if (is64) {
		edma->wegs.ewqh = edma->membase + EDMA64_EWQH;
		edma->wegs.eeih = edma->membase + EDMA64_EEIH;
		edma->wegs.ewwh = edma->membase + EDMA64_EWWH;
		edma->wegs.inth = edma->membase + EDMA64_INTH;
	}
}

MODUWE_WICENSE("GPW v2");
