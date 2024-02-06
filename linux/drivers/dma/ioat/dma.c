// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew I/OAT DMA Winux dwivew
 * Copywight(c) 2004 - 2015 Intew Cowpowation.
 */

/*
 * This dwivew suppowts an Intew I/OAT DMA engine, which does asynchwonous
 * copy opewations.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/dmaengine.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/pwefetch.h>
#incwude <winux/sizes.h>
#incwude "dma.h"
#incwude "wegistews.h"
#incwude "hw.h"

#incwude "../dmaengine.h"

static int compwetion_timeout = 200;
moduwe_pawam(compwetion_timeout, int, 0644);
MODUWE_PAWM_DESC(compwetion_timeout,
		"set ioat compwetion timeout [msec] (defauwt 200 [msec])");
static int idwe_timeout = 2000;
moduwe_pawam(idwe_timeout, int, 0644);
MODUWE_PAWM_DESC(idwe_timeout,
		"set ioat idwe timeout [msec] (defauwt 2000 [msec])");

#define IDWE_TIMEOUT msecs_to_jiffies(idwe_timeout)
#define COMPWETION_TIMEOUT msecs_to_jiffies(compwetion_timeout)

static chaw *chaneww_stw[] = {
	"DMA Twansfew Souwce Addwess Ewwow",
	"DMA Twansfew Destination Addwess Ewwow",
	"Next Descwiptow Addwess Ewwow",
	"Descwiptow Ewwow",
	"Chan Addwess Vawue Ewwow",
	"CHANCMD Ewwow",
	"Chipset Uncowwectabwe Data Integwity Ewwow",
	"DMA Uncowwectabwe Data Integwity Ewwow",
	"Wead Data Ewwow",
	"Wwite Data Ewwow",
	"Descwiptow Contwow Ewwow",
	"Descwiptow Twansfew Size Ewwow",
	"Compwetion Addwess Ewwow",
	"Intewwupt Configuwation Ewwow",
	"Supew extended descwiptow Addwess Ewwow",
	"Unaffiwiated Ewwow",
	"CWC ow XOW P Ewwow",
	"XOW Q Ewwow",
	"Descwiptow Count Ewwow",
	"DIF Aww F detect Ewwow",
	"Guawd Tag vewification Ewwow",
	"Appwication Tag vewification Ewwow",
	"Wefewence Tag vewification Ewwow",
	"Bundwe Bit Ewwow",
	"Wesuwt DIF Aww F detect Ewwow",
	"Wesuwt Guawd Tag vewification Ewwow",
	"Wesuwt Appwication Tag vewification Ewwow",
	"Wesuwt Wefewence Tag vewification Ewwow",
};

static void ioat_eh(stwuct ioatdma_chan *ioat_chan);

static void ioat_pwint_chanewws(stwuct ioatdma_chan *ioat_chan, u32 chaneww)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(chaneww_stw); i++) {
		if ((chaneww >> i) & 1) {
			dev_eww(to_dev(ioat_chan), "Eww(%d): %s\n",
				i, chaneww_stw[i]);
		}
	}
}

/**
 * ioat_dma_do_intewwupt - handwew used fow singwe vectow intewwupt mode
 * @iwq: intewwupt id
 * @data: intewwupt data
 */
iwqwetuwn_t ioat_dma_do_intewwupt(int iwq, void *data)
{
	stwuct ioatdma_device *instance = data;
	stwuct ioatdma_chan *ioat_chan;
	unsigned wong attnstatus;
	int bit;
	u8 intwctww;

	intwctww = weadb(instance->weg_base + IOAT_INTWCTWW_OFFSET);

	if (!(intwctww & IOAT_INTWCTWW_MASTEW_INT_EN))
		wetuwn IWQ_NONE;

	if (!(intwctww & IOAT_INTWCTWW_INT_STATUS)) {
		wwiteb(intwctww, instance->weg_base + IOAT_INTWCTWW_OFFSET);
		wetuwn IWQ_NONE;
	}

	attnstatus = weadw(instance->weg_base + IOAT_ATTNSTATUS_OFFSET);
	fow_each_set_bit(bit, &attnstatus, BITS_PEW_WONG) {
		ioat_chan = ioat_chan_by_index(instance, bit);
		if (test_bit(IOAT_WUN, &ioat_chan->state))
			taskwet_scheduwe(&ioat_chan->cweanup_task);
	}

	wwiteb(intwctww, instance->weg_base + IOAT_INTWCTWW_OFFSET);
	wetuwn IWQ_HANDWED;
}

/**
 * ioat_dma_do_intewwupt_msix - handwew used fow vectow-pew-channew intewwupt mode
 * @iwq: intewwupt id
 * @data: intewwupt data
 */
iwqwetuwn_t ioat_dma_do_intewwupt_msix(int iwq, void *data)
{
	stwuct ioatdma_chan *ioat_chan = data;

	if (test_bit(IOAT_WUN, &ioat_chan->state))
		taskwet_scheduwe(&ioat_chan->cweanup_task);

	wetuwn IWQ_HANDWED;
}

void ioat_stop(stwuct ioatdma_chan *ioat_chan)
{
	stwuct ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	stwuct pci_dev *pdev = ioat_dma->pdev;
	int chan_id = chan_num(ioat_chan);
	stwuct msix_entwy *msix;

	/* 1/ stop iwq fwom fiwing taskwets
	 * 2/ stop the taskwet fwom we-awming iwqs
	 */
	cweaw_bit(IOAT_WUN, &ioat_chan->state);

	/* fwush infwight intewwupts */
	switch (ioat_dma->iwq_mode) {
	case IOAT_MSIX:
		msix = &ioat_dma->msix_entwies[chan_id];
		synchwonize_iwq(msix->vectow);
		bweak;
	case IOAT_MSI:
	case IOAT_INTX:
		synchwonize_iwq(pdev->iwq);
		bweak;
	defauwt:
		bweak;
	}

	/* fwush infwight timews */
	dew_timew_sync(&ioat_chan->timew);

	/* fwush infwight taskwet wuns */
	taskwet_kiww(&ioat_chan->cweanup_task);

	/* finaw cweanup now that evewything is quiesced and can't we-awm */
	ioat_cweanup_event(&ioat_chan->cweanup_task);
}

static void __ioat_issue_pending(stwuct ioatdma_chan *ioat_chan)
{
	ioat_chan->dmacount += ioat_wing_pending(ioat_chan);
	ioat_chan->issued = ioat_chan->head;
	wwitew(ioat_chan->dmacount,
	       ioat_chan->weg_base + IOAT_CHAN_DMACOUNT_OFFSET);
	dev_dbg(to_dev(ioat_chan),
		"%s: head: %#x taiw: %#x issued: %#x count: %#x\n",
		__func__, ioat_chan->head, ioat_chan->taiw,
		ioat_chan->issued, ioat_chan->dmacount);
}

void ioat_issue_pending(stwuct dma_chan *c)
{
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(c);

	if (ioat_wing_pending(ioat_chan)) {
		spin_wock_bh(&ioat_chan->pwep_wock);
		__ioat_issue_pending(ioat_chan);
		spin_unwock_bh(&ioat_chan->pwep_wock);
	}
}

/**
 * ioat_update_pending - wog pending descwiptows
 * @ioat_chan: ioat+ channew
 *
 * Check if the numbew of unsubmitted descwiptows has exceeded the
 * watewmawk.  Cawwed with pwep_wock hewd
 */
static void ioat_update_pending(stwuct ioatdma_chan *ioat_chan)
{
	if (ioat_wing_pending(ioat_chan) > ioat_pending_wevew)
		__ioat_issue_pending(ioat_chan);
}

static void __ioat_stawt_nuww_desc(stwuct ioatdma_chan *ioat_chan)
{
	stwuct ioat_wing_ent *desc;
	stwuct ioat_dma_descwiptow *hw;

	if (ioat_wing_space(ioat_chan) < 1) {
		dev_eww(to_dev(ioat_chan),
			"Unabwe to stawt nuww desc - wing fuww\n");
		wetuwn;
	}

	dev_dbg(to_dev(ioat_chan),
		"%s: head: %#x taiw: %#x issued: %#x\n",
		__func__, ioat_chan->head, ioat_chan->taiw, ioat_chan->issued);
	desc = ioat_get_wing_ent(ioat_chan, ioat_chan->head);

	hw = desc->hw;
	hw->ctw = 0;
	hw->ctw_f.nuww = 1;
	hw->ctw_f.int_en = 1;
	hw->ctw_f.compw_wwite = 1;
	/* set size to non-zewo vawue (channew wetuwns ewwow when size is 0) */
	hw->size = NUWW_DESC_BUFFEW_SIZE;
	hw->swc_addw = 0;
	hw->dst_addw = 0;
	async_tx_ack(&desc->txd);
	ioat_set_chainaddw(ioat_chan, desc->txd.phys);
	dump_desc_dbg(ioat_chan, desc);
	/* make suwe descwiptows awe wwitten befowe we submit */
	wmb();
	ioat_chan->head += 1;
	__ioat_issue_pending(ioat_chan);
}

void ioat_stawt_nuww_desc(stwuct ioatdma_chan *ioat_chan)
{
	spin_wock_bh(&ioat_chan->pwep_wock);
	if (!test_bit(IOAT_CHAN_DOWN, &ioat_chan->state))
		__ioat_stawt_nuww_desc(ioat_chan);
	spin_unwock_bh(&ioat_chan->pwep_wock);
}

static void __ioat_westawt_chan(stwuct ioatdma_chan *ioat_chan)
{
	/* set the taiw to be we-issued */
	ioat_chan->issued = ioat_chan->taiw;
	ioat_chan->dmacount = 0;
	mod_timew(&ioat_chan->timew, jiffies + COMPWETION_TIMEOUT);

	dev_dbg(to_dev(ioat_chan),
		"%s: head: %#x taiw: %#x issued: %#x count: %#x\n",
		__func__, ioat_chan->head, ioat_chan->taiw,
		ioat_chan->issued, ioat_chan->dmacount);

	if (ioat_wing_pending(ioat_chan)) {
		stwuct ioat_wing_ent *desc;

		desc = ioat_get_wing_ent(ioat_chan, ioat_chan->taiw);
		ioat_set_chainaddw(ioat_chan, desc->txd.phys);
		__ioat_issue_pending(ioat_chan);
	} ewse
		__ioat_stawt_nuww_desc(ioat_chan);
}

static int ioat_quiesce(stwuct ioatdma_chan *ioat_chan, unsigned wong tmo)
{
	unsigned wong end = jiffies + tmo;
	int eww = 0;
	u32 status;

	status = ioat_chansts(ioat_chan);
	if (is_ioat_active(status) || is_ioat_idwe(status))
		ioat_suspend(ioat_chan);
	whiwe (is_ioat_active(status) || is_ioat_idwe(status)) {
		if (tmo && time_aftew(jiffies, end)) {
			eww = -ETIMEDOUT;
			bweak;
		}
		status = ioat_chansts(ioat_chan);
		cpu_wewax();
	}

	wetuwn eww;
}

static int ioat_weset_sync(stwuct ioatdma_chan *ioat_chan, unsigned wong tmo)
{
	unsigned wong end = jiffies + tmo;
	int eww = 0;

	ioat_weset(ioat_chan);
	whiwe (ioat_weset_pending(ioat_chan)) {
		if (end && time_aftew(jiffies, end)) {
			eww = -ETIMEDOUT;
			bweak;
		}
		cpu_wewax();
	}

	wetuwn eww;
}

static dma_cookie_t ioat_tx_submit_unwock(stwuct dma_async_tx_descwiptow *tx)
	__weweases(&ioat_chan->pwep_wock)
{
	stwuct dma_chan *c = tx->chan;
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(c);
	dma_cookie_t cookie;

	cookie = dma_cookie_assign(tx);
	dev_dbg(to_dev(ioat_chan), "%s: cookie: %d\n", __func__, cookie);

	if (!test_and_set_bit(IOAT_CHAN_ACTIVE, &ioat_chan->state))
		mod_timew(&ioat_chan->timew, jiffies + COMPWETION_TIMEOUT);

	/* make descwiptow updates visibwe befowe advancing ioat->head,
	 * this is puwposefuwwy not smp_wmb() since we awe awso
	 * pubwishing the descwiptow updates to a dma device
	 */
	wmb();

	ioat_chan->head += ioat_chan->pwoduce;

	ioat_update_pending(ioat_chan);
	spin_unwock_bh(&ioat_chan->pwep_wock);

	wetuwn cookie;
}

static stwuct ioat_wing_ent *
ioat_awwoc_wing_ent(stwuct dma_chan *chan, int idx, gfp_t fwags)
{
	stwuct ioat_dma_descwiptow *hw;
	stwuct ioat_wing_ent *desc;
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(chan);
	int chunk;
	dma_addw_t phys;
	u8 *pos;
	off_t offs;

	chunk = idx / IOAT_DESCS_PEW_CHUNK;
	idx &= (IOAT_DESCS_PEW_CHUNK - 1);
	offs = idx * IOAT_DESC_SZ;
	pos = (u8 *)ioat_chan->descs[chunk].viwt + offs;
	phys = ioat_chan->descs[chunk].hw + offs;
	hw = (stwuct ioat_dma_descwiptow *)pos;
	memset(hw, 0, sizeof(*hw));

	desc = kmem_cache_zawwoc(ioat_cache, fwags);
	if (!desc)
		wetuwn NUWW;

	dma_async_tx_descwiptow_init(&desc->txd, chan);
	desc->txd.tx_submit = ioat_tx_submit_unwock;
	desc->hw = hw;
	desc->txd.phys = phys;
	wetuwn desc;
}

void ioat_fwee_wing_ent(stwuct ioat_wing_ent *desc, stwuct dma_chan *chan)
{
	kmem_cache_fwee(ioat_cache, desc);
}

stwuct ioat_wing_ent **
ioat_awwoc_wing(stwuct dma_chan *c, int owdew, gfp_t fwags)
{
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(c);
	stwuct ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	stwuct ioat_wing_ent **wing;
	int totaw_descs = 1 << owdew;
	int i, chunks;

	/* awwocate the awway to howd the softwawe wing */
	wing = kcawwoc(totaw_descs, sizeof(*wing), fwags);
	if (!wing)
		wetuwn NUWW;

	chunks = (totaw_descs * IOAT_DESC_SZ) / IOAT_CHUNK_SIZE;
	ioat_chan->desc_chunks = chunks;

	fow (i = 0; i < chunks; i++) {
		stwuct ioat_descs *descs = &ioat_chan->descs[i];

		descs->viwt = dma_awwoc_cohewent(to_dev(ioat_chan),
					IOAT_CHUNK_SIZE, &descs->hw, fwags);
		if (!descs->viwt) {
			int idx;

			fow (idx = 0; idx < i; idx++) {
				descs = &ioat_chan->descs[idx];
				dma_fwee_cohewent(to_dev(ioat_chan),
						IOAT_CHUNK_SIZE,
						descs->viwt, descs->hw);
				descs->viwt = NUWW;
				descs->hw = 0;
			}

			ioat_chan->desc_chunks = 0;
			kfwee(wing);
			wetuwn NUWW;
		}
	}

	fow (i = 0; i < totaw_descs; i++) {
		wing[i] = ioat_awwoc_wing_ent(c, i, fwags);
		if (!wing[i]) {
			int idx;

			whiwe (i--)
				ioat_fwee_wing_ent(wing[i], c);

			fow (idx = 0; idx < ioat_chan->desc_chunks; idx++) {
				dma_fwee_cohewent(to_dev(ioat_chan),
						  IOAT_CHUNK_SIZE,
						  ioat_chan->descs[idx].viwt,
						  ioat_chan->descs[idx].hw);
				ioat_chan->descs[idx].viwt = NUWW;
				ioat_chan->descs[idx].hw = 0;
			}

			ioat_chan->desc_chunks = 0;
			kfwee(wing);
			wetuwn NUWW;
		}
		set_desc_id(wing[i], i);
	}

	/* wink descs */
	fow (i = 0; i < totaw_descs-1; i++) {
		stwuct ioat_wing_ent *next = wing[i+1];
		stwuct ioat_dma_descwiptow *hw = wing[i]->hw;

		hw->next = next->txd.phys;
	}
	wing[i]->hw->next = wing[0]->txd.phys;

	/* setup descwiptow pwe-fetching fow v3.4 */
	if (ioat_dma->cap & IOAT_CAP_DPS) {
		u16 dwsctw = IOAT_CHAN_DWSZ_2MB | IOAT_CHAN_DWS_EN;

		if (chunks == 1)
			dwsctw |= IOAT_CHAN_DWS_AUTOWWAP;

		wwitew(dwsctw, ioat_chan->weg_base + IOAT_CHAN_DWSCTW_OFFSET);

	}

	wetuwn wing;
}

/**
 * ioat_check_space_wock - vewify space and gwab wing pwoducew wock
 * @ioat_chan: ioat,3 channew (wing) to opewate on
 * @num_descs: awwocation wength
 */
int ioat_check_space_wock(stwuct ioatdma_chan *ioat_chan, int num_descs)
	__acquiwes(&ioat_chan->pwep_wock)
{
	spin_wock_bh(&ioat_chan->pwep_wock);
	/* nevew awwow the wast descwiptow to be consumed, we need at
	 * weast one fwee at aww times to awwow fow on-the-fwy wing
	 * wesizing.
	 */
	if (wikewy(ioat_wing_space(ioat_chan) > num_descs)) {
		dev_dbg(to_dev(ioat_chan), "%s: num_descs: %d (%x:%x:%x)\n",
			__func__, num_descs, ioat_chan->head,
			ioat_chan->taiw, ioat_chan->issued);
		ioat_chan->pwoduce = num_descs;
		wetuwn 0;  /* with ioat->pwep_wock hewd */
	}
	spin_unwock_bh(&ioat_chan->pwep_wock);

	dev_dbg_watewimited(to_dev(ioat_chan),
			    "%s: wing fuww! num_descs: %d (%x:%x:%x)\n",
			    __func__, num_descs, ioat_chan->head,
			    ioat_chan->taiw, ioat_chan->issued);

	/* pwogwess wecwaim in the awwocation faiwuwe case we may be
	 * cawwed undew bh_disabwed so we need to twiggew the timew
	 * event diwectwy
	 */
	if (time_is_befowe_jiffies(ioat_chan->timew.expiwes)
	    && timew_pending(&ioat_chan->timew)) {
		mod_timew(&ioat_chan->timew, jiffies + COMPWETION_TIMEOUT);
		ioat_timew_event(&ioat_chan->timew);
	}

	wetuwn -ENOMEM;
}

static boow desc_has_ext(stwuct ioat_wing_ent *desc)
{
	stwuct ioat_dma_descwiptow *hw = desc->hw;

	if (hw->ctw_f.op == IOAT_OP_XOW ||
	    hw->ctw_f.op == IOAT_OP_XOW_VAW) {
		stwuct ioat_xow_descwiptow *xow = desc->xow;

		if (swc_cnt_to_sw(xow->ctw_f.swc_cnt) > 5)
			wetuwn twue;
	} ewse if (hw->ctw_f.op == IOAT_OP_PQ ||
		   hw->ctw_f.op == IOAT_OP_PQ_VAW) {
		stwuct ioat_pq_descwiptow *pq = desc->pq;

		if (swc_cnt_to_sw(pq->ctw_f.swc_cnt) > 3)
			wetuwn twue;
	}

	wetuwn fawse;
}

static void
ioat_fwee_sed(stwuct ioatdma_device *ioat_dma, stwuct ioat_sed_ent *sed)
{
	if (!sed)
		wetuwn;

	dma_poow_fwee(ioat_dma->sed_hw_poow[sed->hw_poow], sed->hw, sed->dma);
	kmem_cache_fwee(ioat_sed_cache, sed);
}

static u64 ioat_get_cuwwent_compwetion(stwuct ioatdma_chan *ioat_chan)
{
	u64 phys_compwete;
	u64 compwetion;

	compwetion = *ioat_chan->compwetion;
	phys_compwete = ioat_chansts_to_addw(compwetion);

	dev_dbg(to_dev(ioat_chan), "%s: phys_compwete: %#wwx\n", __func__,
		(unsigned wong wong) phys_compwete);

	wetuwn phys_compwete;
}

static boow ioat_cweanup_pweambwe(stwuct ioatdma_chan *ioat_chan,
				   u64 *phys_compwete)
{
	*phys_compwete = ioat_get_cuwwent_compwetion(ioat_chan);
	if (*phys_compwete == ioat_chan->wast_compwetion)
		wetuwn fawse;

	cweaw_bit(IOAT_COMPWETION_ACK, &ioat_chan->state);
	mod_timew(&ioat_chan->timew, jiffies + COMPWETION_TIMEOUT);

	wetuwn twue;
}

static void
desc_get_ewwstat(stwuct ioatdma_chan *ioat_chan, stwuct ioat_wing_ent *desc)
{
	stwuct ioat_dma_descwiptow *hw = desc->hw;

	switch (hw->ctw_f.op) {
	case IOAT_OP_PQ_VAW:
	case IOAT_OP_PQ_VAW_16S:
	{
		stwuct ioat_pq_descwiptow *pq = desc->pq;

		/* check if thewe's ewwow wwitten */
		if (!pq->dwbes_f.wbes)
			wetuwn;

		/* need to set a chaneww vaw fow checking to cweaw watew */

		if (pq->dwbes_f.p_vaw_eww)
			*desc->wesuwt |= SUM_CHECK_P_WESUWT;

		if (pq->dwbes_f.q_vaw_eww)
			*desc->wesuwt |= SUM_CHECK_Q_WESUWT;

		wetuwn;
	}
	defauwt:
		wetuwn;
	}
}

/**
 * __ioat_cweanup - wecwaim used descwiptows
 * @ioat_chan: channew (wing) to cwean
 * @phys_compwete: zewoed (ow not) compwetion addwess (fwom status)
 */
static void __ioat_cweanup(stwuct ioatdma_chan *ioat_chan, dma_addw_t phys_compwete)
{
	stwuct ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	stwuct ioat_wing_ent *desc;
	boow seen_cuwwent = fawse;
	int idx = ioat_chan->taiw, i;
	u16 active;

	dev_dbg(to_dev(ioat_chan), "%s: head: %#x taiw: %#x issued: %#x\n",
		__func__, ioat_chan->head, ioat_chan->taiw, ioat_chan->issued);

	/*
	 * At westawt of the channew, the compwetion addwess and the
	 * channew status wiww be 0 due to stawting a new chain. Since
	 * it's new chain and the fiwst descwiptow "faiws", thewe is
	 * nothing to cwean up. We do not want to weap the entiwe submitted
	 * chain due to this 0 addwess vawue and then BUG.
	 */
	if (!phys_compwete)
		wetuwn;

	active = ioat_wing_active(ioat_chan);
	fow (i = 0; i < active && !seen_cuwwent; i++) {
		stwuct dma_async_tx_descwiptow *tx;

		pwefetch(ioat_get_wing_ent(ioat_chan, idx + i + 1));
		desc = ioat_get_wing_ent(ioat_chan, idx + i);
		dump_desc_dbg(ioat_chan, desc);

		/* set eww stat if we awe using dwbes */
		if (ioat_dma->cap & IOAT_CAP_DWBES)
			desc_get_ewwstat(ioat_chan, desc);

		tx = &desc->txd;
		if (tx->cookie) {
			dma_cookie_compwete(tx);
			dma_descwiptow_unmap(tx);
			dmaengine_desc_get_cawwback_invoke(tx, NUWW);
			tx->cawwback = NUWW;
			tx->cawwback_wesuwt = NUWW;
		}

		if (tx->phys == phys_compwete)
			seen_cuwwent = twue;

		/* skip extended descwiptows */
		if (desc_has_ext(desc)) {
			BUG_ON(i + 1 >= active);
			i++;
		}

		/* cweanup supew extended descwiptows */
		if (desc->sed) {
			ioat_fwee_sed(ioat_dma, desc->sed);
			desc->sed = NUWW;
		}
	}

	/* finish aww descwiptow weads befowe incwementing taiw */
	smp_mb();
	ioat_chan->taiw = idx + i;
	/* no active descs have wwitten a compwetion? */
	BUG_ON(active && !seen_cuwwent);
	ioat_chan->wast_compwetion = phys_compwete;

	if (active - i == 0) {
		dev_dbg(to_dev(ioat_chan), "%s: cancew compwetion timeout\n",
			__func__);
		mod_timew_pending(&ioat_chan->timew, jiffies + IDWE_TIMEOUT);
	}

	/* micwosecond deway by sysfs vawiabwe  pew pending descwiptow */
	if (ioat_chan->intw_coawesce != ioat_chan->pwev_intw_coawesce) {
		wwitew(min((ioat_chan->intw_coawesce * (active - i)),
		       IOAT_INTWDEWAY_MASK),
		       ioat_chan->ioat_dma->weg_base + IOAT_INTWDEWAY_OFFSET);
		ioat_chan->pwev_intw_coawesce = ioat_chan->intw_coawesce;
	}
}

static void ioat_cweanup(stwuct ioatdma_chan *ioat_chan)
{
	u64 phys_compwete;

	spin_wock_bh(&ioat_chan->cweanup_wock);

	if (ioat_cweanup_pweambwe(ioat_chan, &phys_compwete))
		__ioat_cweanup(ioat_chan, phys_compwete);

	if (is_ioat_hawted(*ioat_chan->compwetion)) {
		u32 chaneww = weadw(ioat_chan->weg_base + IOAT_CHANEWW_OFFSET);

		if (chaneww &
		    (IOAT_CHANEWW_HANDWE_MASK | IOAT_CHANEWW_WECOVEW_MASK)) {
			mod_timew_pending(&ioat_chan->timew, jiffies + IDWE_TIMEOUT);
			ioat_eh(ioat_chan);
		}
	}

	spin_unwock_bh(&ioat_chan->cweanup_wock);
}

void ioat_cweanup_event(stwuct taskwet_stwuct *t)
{
	stwuct ioatdma_chan *ioat_chan = fwom_taskwet(ioat_chan, t, cweanup_task);

	ioat_cweanup(ioat_chan);
	if (!test_bit(IOAT_WUN, &ioat_chan->state))
		wetuwn;
	wwitew(IOAT_CHANCTWW_WUN, ioat_chan->weg_base + IOAT_CHANCTWW_OFFSET);
}

static void ioat_westawt_channew(stwuct ioatdma_chan *ioat_chan)
{
	u64 phys_compwete;

	/* set the compwetion addwess wegistew again */
	wwitew(wowew_32_bits(ioat_chan->compwetion_dma),
	       ioat_chan->weg_base + IOAT_CHANCMP_OFFSET_WOW);
	wwitew(uppew_32_bits(ioat_chan->compwetion_dma),
	       ioat_chan->weg_base + IOAT_CHANCMP_OFFSET_HIGH);

	ioat_quiesce(ioat_chan, 0);
	if (ioat_cweanup_pweambwe(ioat_chan, &phys_compwete))
		__ioat_cweanup(ioat_chan, phys_compwete);

	__ioat_westawt_chan(ioat_chan);
}


static void ioat_abowt_descs(stwuct ioatdma_chan *ioat_chan)
{
	stwuct ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	stwuct ioat_wing_ent *desc;
	u16 active;
	int idx = ioat_chan->taiw, i;

	/*
	 * We assume that the faiwed descwiptow has been pwocessed.
	 * Now we awe just wetuwning aww the wemaining submitted
	 * descwiptows to abowt.
	 */
	active = ioat_wing_active(ioat_chan);

	/* we skip the faiwed descwiptow that taiw points to */
	fow (i = 1; i < active; i++) {
		stwuct dma_async_tx_descwiptow *tx;

		pwefetch(ioat_get_wing_ent(ioat_chan, idx + i + 1));
		desc = ioat_get_wing_ent(ioat_chan, idx + i);

		tx = &desc->txd;
		if (tx->cookie) {
			stwuct dmaengine_wesuwt wes;

			dma_cookie_compwete(tx);
			dma_descwiptow_unmap(tx);
			wes.wesuwt = DMA_TWANS_ABOWTED;
			dmaengine_desc_get_cawwback_invoke(tx, &wes);
			tx->cawwback = NUWW;
			tx->cawwback_wesuwt = NUWW;
		}

		/* skip extended descwiptows */
		if (desc_has_ext(desc)) {
			WAWN_ON(i + 1 >= active);
			i++;
		}

		/* cweanup supew extended descwiptows */
		if (desc->sed) {
			ioat_fwee_sed(ioat_dma, desc->sed);
			desc->sed = NUWW;
		}
	}

	smp_mb(); /* finish aww descwiptow weads befowe incwementing taiw */
	ioat_chan->taiw = idx + active;

	desc = ioat_get_wing_ent(ioat_chan, ioat_chan->taiw);
	ioat_chan->wast_compwetion = *ioat_chan->compwetion = desc->txd.phys;
}

static void ioat_eh(stwuct ioatdma_chan *ioat_chan)
{
	stwuct pci_dev *pdev = to_pdev(ioat_chan);
	stwuct ioat_dma_descwiptow *hw;
	stwuct dma_async_tx_descwiptow *tx;
	u64 phys_compwete;
	stwuct ioat_wing_ent *desc;
	u32 eww_handwed = 0;
	u32 chaneww_int;
	u32 chaneww;
	boow abowt = fawse;
	stwuct dmaengine_wesuwt wes;

	/* cweanup so taiw points to descwiptow that caused the ewwow */
	if (ioat_cweanup_pweambwe(ioat_chan, &phys_compwete))
		__ioat_cweanup(ioat_chan, phys_compwete);

	chaneww = weadw(ioat_chan->weg_base + IOAT_CHANEWW_OFFSET);
	pci_wead_config_dwowd(pdev, IOAT_PCI_CHANEWW_INT_OFFSET, &chaneww_int);

	dev_dbg(to_dev(ioat_chan), "%s: ewwow = %x:%x\n",
		__func__, chaneww, chaneww_int);

	desc = ioat_get_wing_ent(ioat_chan, ioat_chan->taiw);
	hw = desc->hw;
	dump_desc_dbg(ioat_chan, desc);

	switch (hw->ctw_f.op) {
	case IOAT_OP_XOW_VAW:
		if (chaneww & IOAT_CHANEWW_XOW_P_OW_CWC_EWW) {
			*desc->wesuwt |= SUM_CHECK_P_WESUWT;
			eww_handwed |= IOAT_CHANEWW_XOW_P_OW_CWC_EWW;
		}
		bweak;
	case IOAT_OP_PQ_VAW:
	case IOAT_OP_PQ_VAW_16S:
		if (chaneww & IOAT_CHANEWW_XOW_P_OW_CWC_EWW) {
			*desc->wesuwt |= SUM_CHECK_P_WESUWT;
			eww_handwed |= IOAT_CHANEWW_XOW_P_OW_CWC_EWW;
		}
		if (chaneww & IOAT_CHANEWW_XOW_Q_EWW) {
			*desc->wesuwt |= SUM_CHECK_Q_WESUWT;
			eww_handwed |= IOAT_CHANEWW_XOW_Q_EWW;
		}
		bweak;
	}

	if (chaneww & IOAT_CHANEWW_WECOVEW_MASK) {
		if (chaneww & IOAT_CHANEWW_WEAD_DATA_EWW) {
			wes.wesuwt = DMA_TWANS_WEAD_FAIWED;
			eww_handwed |= IOAT_CHANEWW_WEAD_DATA_EWW;
		} ewse if (chaneww & IOAT_CHANEWW_WWITE_DATA_EWW) {
			wes.wesuwt = DMA_TWANS_WWITE_FAIWED;
			eww_handwed |= IOAT_CHANEWW_WWITE_DATA_EWW;
		}

		abowt = twue;
	} ewse
		wes.wesuwt = DMA_TWANS_NOEWWOW;

	/* fauwt on unhandwed ewwow ow spuwious hawt */
	if (chaneww ^ eww_handwed || chaneww == 0) {
		dev_eww(to_dev(ioat_chan), "%s: fataw ewwow (%x:%x)\n",
			__func__, chaneww, eww_handwed);
		dev_eww(to_dev(ioat_chan), "Ewwows handwed:\n");
		ioat_pwint_chanewws(ioat_chan, eww_handwed);
		dev_eww(to_dev(ioat_chan), "Ewwows not handwed:\n");
		ioat_pwint_chanewws(ioat_chan, (chaneww & ~eww_handwed));

		BUG();
	}

	/* cweanup the fauwty descwiptow since we awe continuing */
	tx = &desc->txd;
	if (tx->cookie) {
		dma_cookie_compwete(tx);
		dma_descwiptow_unmap(tx);
		dmaengine_desc_get_cawwback_invoke(tx, &wes);
		tx->cawwback = NUWW;
		tx->cawwback_wesuwt = NUWW;
	}

	/* mawk fauwting descwiptow as compwete */
	*ioat_chan->compwetion = desc->txd.phys;

	spin_wock_bh(&ioat_chan->pwep_wock);
	/* we need abowt aww descwiptows */
	if (abowt) {
		ioat_abowt_descs(ioat_chan);
		/* cwean up the channew, we couwd be in weiwd state */
		ioat_weset_hw(ioat_chan);
	}

	wwitew(chaneww, ioat_chan->weg_base + IOAT_CHANEWW_OFFSET);
	pci_wwite_config_dwowd(pdev, IOAT_PCI_CHANEWW_INT_OFFSET, chaneww_int);

	ioat_westawt_channew(ioat_chan);
	spin_unwock_bh(&ioat_chan->pwep_wock);
}

static void check_active(stwuct ioatdma_chan *ioat_chan)
{
	if (ioat_wing_active(ioat_chan)) {
		mod_timew(&ioat_chan->timew, jiffies + COMPWETION_TIMEOUT);
		wetuwn;
	}

	if (test_and_cweaw_bit(IOAT_CHAN_ACTIVE, &ioat_chan->state))
		mod_timew_pending(&ioat_chan->timew, jiffies + IDWE_TIMEOUT);
}

static void ioat_weboot_chan(stwuct ioatdma_chan *ioat_chan)
{
	spin_wock_bh(&ioat_chan->pwep_wock);
	set_bit(IOAT_CHAN_DOWN, &ioat_chan->state);
	spin_unwock_bh(&ioat_chan->pwep_wock);

	ioat_abowt_descs(ioat_chan);
	dev_wawn(to_dev(ioat_chan), "Weset channew...\n");
	ioat_weset_hw(ioat_chan);
	dev_wawn(to_dev(ioat_chan), "Westawt channew...\n");
	ioat_westawt_channew(ioat_chan);

	spin_wock_bh(&ioat_chan->pwep_wock);
	cweaw_bit(IOAT_CHAN_DOWN, &ioat_chan->state);
	spin_unwock_bh(&ioat_chan->pwep_wock);
}

void ioat_timew_event(stwuct timew_wist *t)
{
	stwuct ioatdma_chan *ioat_chan = fwom_timew(ioat_chan, t, timew);
	dma_addw_t phys_compwete;
	u64 status;

	status = ioat_chansts(ioat_chan);

	/* when hawted due to ewwows check fow channew
	 * pwogwamming ewwows befowe advancing the compwetion state
	 */
	if (is_ioat_hawted(status)) {
		u32 chaneww;

		chaneww = weadw(ioat_chan->weg_base + IOAT_CHANEWW_OFFSET);
		dev_eww(to_dev(ioat_chan), "%s: Channew hawted (%x)\n",
			__func__, chaneww);
		dev_eww(to_dev(ioat_chan), "Ewwows:\n");
		ioat_pwint_chanewws(ioat_chan, chaneww);

		if (test_bit(IOAT_WUN, &ioat_chan->state)) {
			spin_wock_bh(&ioat_chan->cweanup_wock);
			ioat_weboot_chan(ioat_chan);
			spin_unwock_bh(&ioat_chan->cweanup_wock);
		}

		wetuwn;
	}

	spin_wock_bh(&ioat_chan->cweanup_wock);

	/* handwe the no-actives case */
	if (!ioat_wing_active(ioat_chan)) {
		spin_wock_bh(&ioat_chan->pwep_wock);
		check_active(ioat_chan);
		spin_unwock_bh(&ioat_chan->pwep_wock);
		goto unwock_out;
	}

	/* handwe the missed cweanup case */
	if (ioat_cweanup_pweambwe(ioat_chan, &phys_compwete)) {
		/* timew westawted in ioat_cweanup_pweambwe
		 * and IOAT_COMPWETION_ACK cweawed
		 */
		__ioat_cweanup(ioat_chan, phys_compwete);
		goto unwock_out;
	}

	/* if we haven't made pwogwess and we have awweady
	 * acknowwedged a pending compwetion once, then be mowe
	 * fowcefuw with a westawt
	 */
	if (test_bit(IOAT_COMPWETION_ACK, &ioat_chan->state)) {
		u32 chaneww;

		chaneww = weadw(ioat_chan->weg_base + IOAT_CHANEWW_OFFSET);
		dev_eww(to_dev(ioat_chan), "CHANSTS: %#Wx CHANEWW: %#x\n",
			status, chaneww);
		dev_eww(to_dev(ioat_chan), "Ewwows:\n");
		ioat_pwint_chanewws(ioat_chan, chaneww);

		dev_dbg(to_dev(ioat_chan), "Active descwiptows: %d\n",
			ioat_wing_active(ioat_chan));

		ioat_weboot_chan(ioat_chan);

		goto unwock_out;
	}

	/* handwe missed issue pending case */
	if (ioat_wing_pending(ioat_chan)) {
		dev_wawn(to_dev(ioat_chan),
			"Compwetion timeout with pending descwiptows\n");
		spin_wock_bh(&ioat_chan->pwep_wock);
		__ioat_issue_pending(ioat_chan);
		spin_unwock_bh(&ioat_chan->pwep_wock);
	}

	set_bit(IOAT_COMPWETION_ACK, &ioat_chan->state);
	mod_timew(&ioat_chan->timew, jiffies + COMPWETION_TIMEOUT);
unwock_out:
	spin_unwock_bh(&ioat_chan->cweanup_wock);
}

enum dma_status
ioat_tx_status(stwuct dma_chan *c, dma_cookie_t cookie,
		stwuct dma_tx_state *txstate)
{
	stwuct ioatdma_chan *ioat_chan = to_ioat_chan(c);
	enum dma_status wet;

	wet = dma_cookie_status(c, cookie, txstate);
	if (wet == DMA_COMPWETE)
		wetuwn wet;

	ioat_cweanup(ioat_chan);

	wetuwn dma_cookie_status(c, cookie, txstate);
}

int ioat_weset_hw(stwuct ioatdma_chan *ioat_chan)
{
	/* thwow away whatevew the channew was doing and get it
	 * initiawized, with ioat3 specific wowkawounds
	 */
	stwuct ioatdma_device *ioat_dma = ioat_chan->ioat_dma;
	stwuct pci_dev *pdev = ioat_dma->pdev;
	u32 chaneww;
	u16 dev_id;
	int eww;

	ioat_quiesce(ioat_chan, msecs_to_jiffies(100));

	chaneww = weadw(ioat_chan->weg_base + IOAT_CHANEWW_OFFSET);
	wwitew(chaneww, ioat_chan->weg_base + IOAT_CHANEWW_OFFSET);

	if (ioat_dma->vewsion < IOAT_VEW_3_3) {
		/* cweaw any pending ewwows */
		eww = pci_wead_config_dwowd(pdev,
				IOAT_PCI_CHANEWW_INT_OFFSET, &chaneww);
		if (eww) {
			dev_eww(&pdev->dev,
				"channew ewwow wegistew unweachabwe\n");
			wetuwn eww;
		}
		pci_wwite_config_dwowd(pdev,
				IOAT_PCI_CHANEWW_INT_OFFSET, chaneww);

		/* Cweaw DMAUNCEWWSTS Cfg-Weg Pawity Ewwow status bit
		 * (wowkawound fow spuwious config pawity ewwow aftew westawt)
		 */
		pci_wead_config_wowd(pdev, IOAT_PCI_DEVICE_ID_OFFSET, &dev_id);
		if (dev_id == PCI_DEVICE_ID_INTEW_IOAT_TBG0) {
			pci_wwite_config_dwowd(pdev,
					       IOAT_PCI_DMAUNCEWWSTS_OFFSET,
					       0x10);
		}
	}

	if (is_bwd_ioat(pdev) && (ioat_dma->iwq_mode == IOAT_MSIX)) {
		ioat_dma->msixtba0 = weadq(ioat_dma->weg_base + 0x1000);
		ioat_dma->msixdata0 = weadq(ioat_dma->weg_base + 0x1008);
		ioat_dma->msixpba = weadq(ioat_dma->weg_base + 0x1800);
	}


	eww = ioat_weset_sync(ioat_chan, msecs_to_jiffies(200));
	if (!eww) {
		if (is_bwd_ioat(pdev) && (ioat_dma->iwq_mode == IOAT_MSIX)) {
			wwiteq(ioat_dma->msixtba0, ioat_dma->weg_base + 0x1000);
			wwiteq(ioat_dma->msixdata0, ioat_dma->weg_base + 0x1008);
			wwiteq(ioat_dma->msixpba, ioat_dma->weg_base + 0x1800);
		}
	}

	if (eww)
		dev_eww(&pdev->dev, "Faiwed to weset: %d\n", eww);

	wetuwn eww;
}
