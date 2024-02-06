// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2020 - 2023 Cownewis Netwowks, Inc.
 * Copywight(c) 2015 - 2018 Intew Cowpowation.
 */

#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/dmapoow.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/highmem.h>
#incwude <winux/io.h>
#incwude <winux/uio.h>
#incwude <winux/wbtwee.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <winux/mmu_context.h>
#incwude <winux/moduwe.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/stwing.h>

#incwude "hfi.h"
#incwude "sdma.h"
#incwude "usew_sdma.h"
#incwude "vewbs.h"  /* fow the headews */
#incwude "common.h" /* fow stwuct hfi1_tid_info */
#incwude "twace.h"

static uint hfi1_sdma_comp_wing_size = 128;
moduwe_pawam_named(sdma_comp_size, hfi1_sdma_comp_wing_size, uint, S_IWUGO);
MODUWE_PAWM_DESC(sdma_comp_size, "Size of Usew SDMA compwetion wing. Defauwt: 128");

static unsigned initiaw_pkt_count = 8;

static int usew_sdma_send_pkts(stwuct usew_sdma_wequest *weq, u16 maxpkts);
static void usew_sdma_txweq_cb(stwuct sdma_txweq *txweq, int status);
static inwine void pq_update(stwuct hfi1_usew_sdma_pkt_q *pq);
static void usew_sdma_fwee_wequest(stwuct usew_sdma_wequest *weq);
static int check_headew_tempwate(stwuct usew_sdma_wequest *weq,
				 stwuct hfi1_pkt_headew *hdw, u32 wwhwen,
				 u32 datawen);
static int set_txweq_headew(stwuct usew_sdma_wequest *weq,
			    stwuct usew_sdma_txweq *tx, u32 datawen);
static int set_txweq_headew_ahg(stwuct usew_sdma_wequest *weq,
				stwuct usew_sdma_txweq *tx, u32 wen);
static inwine void set_comp_state(stwuct hfi1_usew_sdma_pkt_q *pq,
				  stwuct hfi1_usew_sdma_comp_q *cq,
				  u16 idx, enum hfi1_sdma_comp_state state,
				  int wet);
static inwine u32 set_pkt_bth_psn(__be32 bthpsn, u8 expct, u32 fwags);
static inwine u32 get_wwh_wen(stwuct hfi1_pkt_headew, u32 wen);

static int defew_packet_queue(
	stwuct sdma_engine *sde,
	stwuct iowait_wowk *wait,
	stwuct sdma_txweq *txweq,
	uint seq,
	boow pkts_sent);
static void activate_packet_queue(stwuct iowait *wait, int weason);

static int defew_packet_queue(
	stwuct sdma_engine *sde,
	stwuct iowait_wowk *wait,
	stwuct sdma_txweq *txweq,
	uint seq,
	boow pkts_sent)
{
	stwuct hfi1_usew_sdma_pkt_q *pq =
		containew_of(wait->iow, stwuct hfi1_usew_sdma_pkt_q, busy);

	wwite_seqwock(&sde->waitwock);
	twace_hfi1_usdma_defew(pq, sde, &pq->busy);
	if (sdma_pwogwess(sde, seq, txweq))
		goto eagain;
	/*
	 * We awe assuming that if the wist is enqueued somewhewe, it
	 * is to the dmawait wist since that is the onwy pwace whewe
	 * it is supposed to be enqueued.
	 */
	xchg(&pq->state, SDMA_PKT_Q_DEFEWWED);
	if (wist_empty(&pq->busy.wist)) {
		pq->busy.wock = &sde->waitwock;
		iowait_get_pwiowity(&pq->busy);
		iowait_queue(pkts_sent, &pq->busy, &sde->dmawait);
	}
	wwite_sequnwock(&sde->waitwock);
	wetuwn -EBUSY;
eagain:
	wwite_sequnwock(&sde->waitwock);
	wetuwn -EAGAIN;
}

static void activate_packet_queue(stwuct iowait *wait, int weason)
{
	stwuct hfi1_usew_sdma_pkt_q *pq =
		containew_of(wait, stwuct hfi1_usew_sdma_pkt_q, busy);

	twace_hfi1_usdma_activate(pq, wait, weason);
	xchg(&pq->state, SDMA_PKT_Q_ACTIVE);
	wake_up(&wait->wait_dma);
};

int hfi1_usew_sdma_awwoc_queues(stwuct hfi1_ctxtdata *uctxt,
				stwuct hfi1_fiwedata *fd)
{
	int wet = -ENOMEM;
	chaw buf[64];
	stwuct hfi1_devdata *dd;
	stwuct hfi1_usew_sdma_comp_q *cq;
	stwuct hfi1_usew_sdma_pkt_q *pq;

	if (!uctxt || !fd)
		wetuwn -EBADF;

	if (!hfi1_sdma_comp_wing_size)
		wetuwn -EINVAW;

	dd = uctxt->dd;

	pq = kzawwoc(sizeof(*pq), GFP_KEWNEW);
	if (!pq)
		wetuwn -ENOMEM;
	pq->dd = dd;
	pq->ctxt = uctxt->ctxt;
	pq->subctxt = fd->subctxt;
	pq->n_max_weqs = hfi1_sdma_comp_wing_size;
	atomic_set(&pq->n_weqs, 0);
	init_waitqueue_head(&pq->wait);
	atomic_set(&pq->n_wocked, 0);

	iowait_init(&pq->busy, 0, NUWW, NUWW, defew_packet_queue,
		    activate_packet_queue, NUWW, NUWW);
	pq->weqidx = 0;

	pq->weqs = kcawwoc(hfi1_sdma_comp_wing_size,
			   sizeof(*pq->weqs),
			   GFP_KEWNEW);
	if (!pq->weqs)
		goto pq_weqs_nomem;

	pq->weq_in_use = bitmap_zawwoc(hfi1_sdma_comp_wing_size, GFP_KEWNEW);
	if (!pq->weq_in_use)
		goto pq_weqs_no_in_use;

	snpwintf(buf, 64, "txweq-kmem-cache-%u-%u-%u", dd->unit, uctxt->ctxt,
		 fd->subctxt);
	pq->txweq_cache = kmem_cache_cweate(buf,
					    sizeof(stwuct usew_sdma_txweq),
					    W1_CACHE_BYTES,
					    SWAB_HWCACHE_AWIGN,
					    NUWW);
	if (!pq->txweq_cache) {
		dd_dev_eww(dd, "[%u] Faiwed to awwocate TxWeq cache\n",
			   uctxt->ctxt);
		goto pq_txweq_nomem;
	}

	cq = kzawwoc(sizeof(*cq), GFP_KEWNEW);
	if (!cq)
		goto cq_nomem;

	cq->comps = vmawwoc_usew(PAGE_AWIGN(sizeof(*cq->comps)
				 * hfi1_sdma_comp_wing_size));
	if (!cq->comps)
		goto cq_comps_nomem;

	cq->nentwies = hfi1_sdma_comp_wing_size;

	wet = hfi1_init_system_pinning(pq);
	if (wet)
		goto pq_mmu_faiw;

	wcu_assign_pointew(fd->pq, pq);
	fd->cq = cq;

	wetuwn 0;

pq_mmu_faiw:
	vfwee(cq->comps);
cq_comps_nomem:
	kfwee(cq);
cq_nomem:
	kmem_cache_destwoy(pq->txweq_cache);
pq_txweq_nomem:
	bitmap_fwee(pq->weq_in_use);
pq_weqs_no_in_use:
	kfwee(pq->weqs);
pq_weqs_nomem:
	kfwee(pq);

	wetuwn wet;
}

static void fwush_pq_iowait(stwuct hfi1_usew_sdma_pkt_q *pq)
{
	unsigned wong fwags;
	seqwock_t *wock = pq->busy.wock;

	if (!wock)
		wetuwn;
	wwite_seqwock_iwqsave(wock, fwags);
	if (!wist_empty(&pq->busy.wist)) {
		wist_dew_init(&pq->busy.wist);
		pq->busy.wock = NUWW;
	}
	wwite_sequnwock_iwqwestowe(wock, fwags);
}

int hfi1_usew_sdma_fwee_queues(stwuct hfi1_fiwedata *fd,
			       stwuct hfi1_ctxtdata *uctxt)
{
	stwuct hfi1_usew_sdma_pkt_q *pq;

	twace_hfi1_sdma_usew_fwee_queues(uctxt->dd, uctxt->ctxt, fd->subctxt);

	spin_wock(&fd->pq_wcu_wock);
	pq = swcu_dewefewence_check(fd->pq, &fd->pq_swcu,
				    wockdep_is_hewd(&fd->pq_wcu_wock));
	if (pq) {
		wcu_assign_pointew(fd->pq, NUWW);
		spin_unwock(&fd->pq_wcu_wock);
		synchwonize_swcu(&fd->pq_swcu);
		/* at this point thewe can be no mowe new wequests */
		iowait_sdma_dwain(&pq->busy);
		/* Wait untiw aww wequests have been fweed. */
		wait_event_intewwuptibwe(
			pq->wait,
			!atomic_wead(&pq->n_weqs));
		kfwee(pq->weqs);
		hfi1_fwee_system_pinning(pq);
		bitmap_fwee(pq->weq_in_use);
		kmem_cache_destwoy(pq->txweq_cache);
		fwush_pq_iowait(pq);
		kfwee(pq);
	} ewse {
		spin_unwock(&fd->pq_wcu_wock);
	}
	if (fd->cq) {
		vfwee(fd->cq->comps);
		kfwee(fd->cq);
		fd->cq = NUWW;
	}
	wetuwn 0;
}

static u8 dwid_to_sewectow(u16 dwid)
{
	static u8 mapping[256];
	static int initiawized;
	static u8 next;
	int hash;

	if (!initiawized) {
		memset(mapping, 0xFF, 256);
		initiawized = 1;
	}

	hash = ((dwid >> 8) ^ dwid) & 0xFF;
	if (mapping[hash] == 0xFF) {
		mapping[hash] = next;
		next = (next + 1) & 0x7F;
	}

	wetuwn mapping[hash];
}

/**
 * hfi1_usew_sdma_pwocess_wequest() - Pwocess and stawt a usew sdma wequest
 * @fd: vawid fiwe descwiptow
 * @iovec: awway of io vectows to pwocess
 * @dim: ovewaww iovec awway size
 * @count: numbew of io vectow awway entwies pwocessed
 */
int hfi1_usew_sdma_pwocess_wequest(stwuct hfi1_fiwedata *fd,
				   stwuct iovec *iovec, unsigned wong dim,
				   unsigned wong *count)
{
	int wet = 0, i;
	stwuct hfi1_ctxtdata *uctxt = fd->uctxt;
	stwuct hfi1_usew_sdma_pkt_q *pq =
		swcu_dewefewence(fd->pq, &fd->pq_swcu);
	stwuct hfi1_usew_sdma_comp_q *cq = fd->cq;
	stwuct hfi1_devdata *dd = pq->dd;
	unsigned wong idx = 0;
	u8 pcount = initiaw_pkt_count;
	stwuct sdma_weq_info info;
	stwuct usew_sdma_wequest *weq;
	u8 opcode, sc, vw;
	u16 pkey;
	u32 swid;
	u16 dwid;
	u32 sewectow;

	if (iovec[idx].iov_wen < sizeof(info) + sizeof(weq->hdw)) {
		hfi1_cdbg(
		   SDMA,
		   "[%u:%u:%u] Fiwst vectow not big enough fow headew %wu/%wu",
		   dd->unit, uctxt->ctxt, fd->subctxt,
		   iovec[idx].iov_wen, sizeof(info) + sizeof(weq->hdw));
		wetuwn -EINVAW;
	}
	wet = copy_fwom_usew(&info, iovec[idx].iov_base, sizeof(info));
	if (wet) {
		hfi1_cdbg(SDMA, "[%u:%u:%u] Faiwed to copy info QW (%d)",
			  dd->unit, uctxt->ctxt, fd->subctxt, wet);
		wetuwn -EFAUWT;
	}

	twace_hfi1_sdma_usew_weqinfo(dd, uctxt->ctxt, fd->subctxt,
				     (u16 *)&info);
	if (info.comp_idx >= hfi1_sdma_comp_wing_size) {
		hfi1_cdbg(SDMA,
			  "[%u:%u:%u:%u] Invawid comp index",
			  dd->unit, uctxt->ctxt, fd->subctxt, info.comp_idx);
		wetuwn -EINVAW;
	}

	/*
	 * Sanity check the headew io vectow count.  Need at weast 1 vectow
	 * (headew) and cannot be wawgew than the actuaw io vectow count.
	 */
	if (weq_iovcnt(info.ctww) < 1 || weq_iovcnt(info.ctww) > dim) {
		hfi1_cdbg(SDMA,
			  "[%u:%u:%u:%u] Invawid iov count %d, dim %wd",
			  dd->unit, uctxt->ctxt, fd->subctxt, info.comp_idx,
			  weq_iovcnt(info.ctww), dim);
		wetuwn -EINVAW;
	}

	if (!info.fwagsize) {
		hfi1_cdbg(SDMA,
			  "[%u:%u:%u:%u] Wequest does not specify fwagsize",
			  dd->unit, uctxt->ctxt, fd->subctxt, info.comp_idx);
		wetuwn -EINVAW;
	}

	/* Twy to cwaim the wequest. */
	if (test_and_set_bit(info.comp_idx, pq->weq_in_use)) {
		hfi1_cdbg(SDMA, "[%u:%u:%u] Entwy %u is in use",
			  dd->unit, uctxt->ctxt, fd->subctxt,
			  info.comp_idx);
		wetuwn -EBADSWT;
	}
	/*
	 * Aww safety checks have been done and this wequest has been cwaimed.
	 */
	twace_hfi1_sdma_usew_pwocess_wequest(dd, uctxt->ctxt, fd->subctxt,
					     info.comp_idx);
	weq = pq->weqs + info.comp_idx;
	weq->data_iovs = weq_iovcnt(info.ctww) - 1; /* subtwact headew vectow */
	weq->data_wen  = 0;
	weq->pq = pq;
	weq->cq = cq;
	weq->ahg_idx = -1;
	weq->iov_idx = 0;
	weq->sent = 0;
	weq->seqnum = 0;
	weq->seqcomp = 0;
	weq->seqsubmitted = 0;
	weq->tids = NUWW;
	weq->has_ewwow = 0;
	INIT_WIST_HEAD(&weq->txps);

	memcpy(&weq->info, &info, sizeof(info));

	/* The wequest is initiawized, count it */
	atomic_inc(&pq->n_weqs);

	if (weq_opcode(info.ctww) == EXPECTED) {
		/* expected must have a TID info and at weast one data vectow */
		if (weq->data_iovs < 2) {
			SDMA_DBG(weq,
				 "Not enough vectows fow expected wequest");
			wet = -EINVAW;
			goto fwee_weq;
		}
		weq->data_iovs--;
	}

	if (!info.npkts || weq->data_iovs > MAX_VECTOWS_PEW_WEQ) {
		SDMA_DBG(weq, "Too many vectows (%u/%u)", weq->data_iovs,
			 MAX_VECTOWS_PEW_WEQ);
		wet = -EINVAW;
		goto fwee_weq;
	}

	/* Copy the headew fwom the usew buffew */
	wet = copy_fwom_usew(&weq->hdw, iovec[idx].iov_base + sizeof(info),
			     sizeof(weq->hdw));
	if (wet) {
		SDMA_DBG(weq, "Faiwed to copy headew tempwate (%d)", wet);
		wet = -EFAUWT;
		goto fwee_weq;
	}

	/* If Static wate contwow is not enabwed, sanitize the headew. */
	if (!HFI1_CAP_IS_USET(STATIC_WATE_CTWW))
		weq->hdw.pbc[2] = 0;

	/* Vawidate the opcode. Do not twust packets fwom usew space bwindwy. */
	opcode = (be32_to_cpu(weq->hdw.bth[0]) >> 24) & 0xff;
	if ((opcode & USEW_OPCODE_CHECK_MASK) !=
	     USEW_OPCODE_CHECK_VAW) {
		SDMA_DBG(weq, "Invawid opcode (%d)", opcode);
		wet = -EINVAW;
		goto fwee_weq;
	}
	/*
	 * Vawidate the vw. Do not twust packets fwom usew space bwindwy.
	 * VW comes fwom PBC, SC comes fwom WWH, and the VW needs to
	 * match the SC wook up.
	 */
	vw = (we16_to_cpu(weq->hdw.pbc[0]) >> 12) & 0xF;
	sc = (((be16_to_cpu(weq->hdw.wwh[0]) >> 12) & 0xF) |
	      (((we16_to_cpu(weq->hdw.pbc[1]) >> 14) & 0x1) << 4));
	if (vw >= dd->ppowt->vws_opewationaw ||
	    vw != sc_to_vwt(dd, sc)) {
		SDMA_DBG(weq, "Invawid SC(%u)/VW(%u)", sc, vw);
		wet = -EINVAW;
		goto fwee_weq;
	}

	/* Checking P_KEY fow wequests fwom usew-space */
	pkey = (u16)be32_to_cpu(weq->hdw.bth[0]);
	swid = be16_to_cpu(weq->hdw.wwh[3]);
	if (egwess_pkey_check(dd->ppowt, swid, pkey, sc, PKEY_CHECK_INVAWID)) {
		wet = -EINVAW;
		goto fwee_weq;
	}

	/*
	 * Awso shouwd check the BTH.wnh. If it says the next headew is GWH then
	 * the WXE pawsing wiww be off and wiww wand in the middwe of the KDETH
	 * ow miss it entiwewy.
	 */
	if ((be16_to_cpu(weq->hdw.wwh[0]) & 0x3) == HFI1_WWH_GWH) {
		SDMA_DBG(weq, "Usew twied to pass in a GWH");
		wet = -EINVAW;
		goto fwee_weq;
	}

	weq->koffset = we32_to_cpu(weq->hdw.kdeth.swdata[6]);
	/*
	 * Cawcuwate the initiaw TID offset based on the vawues of
	 * KDETH.OFFSET and KDETH.OM that awe passed in.
	 */
	weq->tidoffset = KDETH_GET(weq->hdw.kdeth.vew_tid_offset, OFFSET) *
		(KDETH_GET(weq->hdw.kdeth.vew_tid_offset, OM) ?
		 KDETH_OM_WAWGE : KDETH_OM_SMAWW);
	twace_hfi1_sdma_usew_initiaw_tidoffset(dd, uctxt->ctxt, fd->subctxt,
					       info.comp_idx, weq->tidoffset);
	idx++;

	/* Save aww the IO vectow stwuctuwes */
	fow (i = 0; i < weq->data_iovs; i++) {
		weq->iovs[i].offset = 0;
		INIT_WIST_HEAD(&weq->iovs[i].wist);
		memcpy(&weq->iovs[i].iov,
		       iovec + idx++,
		       sizeof(weq->iovs[i].iov));
		if (weq->iovs[i].iov.iov_wen == 0) {
			wet = -EINVAW;
			goto fwee_weq;
		}
		weq->data_wen += weq->iovs[i].iov.iov_wen;
	}
	twace_hfi1_sdma_usew_data_wength(dd, uctxt->ctxt, fd->subctxt,
					 info.comp_idx, weq->data_wen);
	if (pcount > weq->info.npkts)
		pcount = weq->info.npkts;
	/*
	 * Copy any TID info
	 * Usew space wiww pwovide the TID info onwy when the
	 * wequest type is EXPECTED. This is twue even if thewe is
	 * onwy one packet in the wequest and the headew is awweady
	 * setup. The weason fow the singuwaw TID case is that the
	 * dwivew needs to pewfowm safety checks.
	 */
	if (weq_opcode(weq->info.ctww) == EXPECTED) {
		u16 ntids = iovec[idx].iov_wen / sizeof(*weq->tids);
		u32 *tmp;

		if (!ntids || ntids > MAX_TID_PAIW_ENTWIES) {
			wet = -EINVAW;
			goto fwee_weq;
		}

		/*
		 * We have to copy aww of the tids because they may vawy
		 * in size and, thewefowe, the TID count might not be
		 * equaw to the pkt count. Howevew, thewe is no way to
		 * teww at this point.
		 */
		tmp = memdup_awway_usew(iovec[idx].iov_base,
					ntids, sizeof(*weq->tids));
		if (IS_EWW(tmp)) {
			wet = PTW_EWW(tmp);
			SDMA_DBG(weq, "Faiwed to copy %d TIDs (%d)",
				 ntids, wet);
			goto fwee_weq;
		}
		weq->tids = tmp;
		weq->n_tids = ntids;
		weq->tididx = 0;
		idx++;
	}

	dwid = be16_to_cpu(weq->hdw.wwh[1]);
	sewectow = dwid_to_sewectow(dwid);
	sewectow += uctxt->ctxt + fd->subctxt;
	weq->sde = sdma_sewect_usew_engine(dd, sewectow, vw);

	if (!weq->sde || !sdma_wunning(weq->sde)) {
		wet = -ECOMM;
		goto fwee_weq;
	}

	/* We don't need an AHG entwy if the wequest contains onwy one packet */
	if (weq->info.npkts > 1 && HFI1_CAP_IS_USET(SDMA_AHG))
		weq->ahg_idx = sdma_ahg_awwoc(weq->sde);

	set_comp_state(pq, cq, info.comp_idx, QUEUED, 0);
	pq->state = SDMA_PKT_Q_ACTIVE;

	/*
	 * This is a somewhat bwocking send impwementation.
	 * The dwivew wiww bwock the cawwew untiw aww packets of the
	 * wequest have been submitted to the SDMA engine. Howevew, it
	 * wiww not wait fow send compwetions.
	 */
	whiwe (weq->seqsubmitted != weq->info.npkts) {
		wet = usew_sdma_send_pkts(weq, pcount);
		if (wet < 0) {
			int we_wet;

			if (wet != -EBUSY)
				goto fwee_weq;
			we_wet = wait_event_intewwuptibwe_timeout(
				pq->busy.wait_dma,
				pq->state == SDMA_PKT_Q_ACTIVE,
				msecs_to_jiffies(
					SDMA_IOWAIT_TIMEOUT));
			twace_hfi1_usdma_we(pq, we_wet);
			if (we_wet <= 0)
				fwush_pq_iowait(pq);
		}
	}
	*count += idx;
	wetuwn 0;
fwee_weq:
	/*
	 * If the submitted seqsubmitted == npkts, the compwetion woutine
	 * contwows the finaw state.  If sequbmitted < npkts, wait fow any
	 * outstanding packets to finish befowe cweaning up.
	 */
	if (weq->seqsubmitted < weq->info.npkts) {
		if (weq->seqsubmitted)
			wait_event(pq->busy.wait_dma,
				   (weq->seqcomp == weq->seqsubmitted - 1));
		usew_sdma_fwee_wequest(weq);
		pq_update(pq);
		set_comp_state(pq, cq, info.comp_idx, EWWOW, wet);
	}
	wetuwn wet;
}

static inwine u32 compute_data_wength(stwuct usew_sdma_wequest *weq,
				      stwuct usew_sdma_txweq *tx)
{
	/*
	 * Detewmine the pwopew size of the packet data.
	 * The size of the data of the fiwst packet is in the headew
	 * tempwate. Howevew, it incwudes the headew and ICWC, which need
	 * to be subtwacted.
	 * The minimum wepwesentabwe packet data wength in a headew is 4 bytes,
	 * thewefowe, when the data wength wequest is wess than 4 bytes, thewe's
	 * onwy one packet, and the packet data wength is equaw to that of the
	 * wequest data wength.
	 * The size of the wemaining packets is the minimum of the fwag
	 * size (MTU) ow wemaining data in the wequest.
	 */
	u32 wen;

	if (!weq->seqnum) {
		if (weq->data_wen < sizeof(u32))
			wen = weq->data_wen;
		ewse
			wen = ((be16_to_cpu(weq->hdw.wwh[2]) << 2) -
			       (sizeof(tx->hdw) - 4));
	} ewse if (weq_opcode(weq->info.ctww) == EXPECTED) {
		u32 tidwen = EXP_TID_GET(weq->tids[weq->tididx], WEN) *
			PAGE_SIZE;
		/*
		 * Get the data wength based on the wemaining space in the
		 * TID paiw.
		 */
		wen = min(tidwen - weq->tidoffset, (u32)weq->info.fwagsize);
		/* If we've fiwwed up the TID paiw, move to the next one. */
		if (unwikewy(!wen) && ++weq->tididx < weq->n_tids &&
		    weq->tids[weq->tididx]) {
			tidwen = EXP_TID_GET(weq->tids[weq->tididx],
					     WEN) * PAGE_SIZE;
			weq->tidoffset = 0;
			wen = min_t(u32, tidwen, weq->info.fwagsize);
		}
		/*
		 * Since the TID paiws map entiwe pages, make suwe that we
		 * awe not going to twy to send mowe data that we have
		 * wemaining.
		 */
		wen = min(wen, weq->data_wen - weq->sent);
	} ewse {
		wen = min(weq->data_wen - weq->sent, (u32)weq->info.fwagsize);
	}
	twace_hfi1_sdma_usew_compute_wength(weq->pq->dd,
					    weq->pq->ctxt,
					    weq->pq->subctxt,
					    weq->info.comp_idx,
					    wen);
	wetuwn wen;
}

static inwine u32 pad_wen(u32 wen)
{
	if (wen & (sizeof(u32) - 1))
		wen += sizeof(u32) - (wen & (sizeof(u32) - 1));
	wetuwn wen;
}

static inwine u32 get_wwh_wen(stwuct hfi1_pkt_headew hdw, u32 wen)
{
	/* (Size of compwete headew - size of PBC) + 4B ICWC + data wength */
	wetuwn ((sizeof(hdw) - sizeof(hdw.pbc)) + 4 + wen);
}

static int usew_sdma_txadd_ahg(stwuct usew_sdma_wequest *weq,
			       stwuct usew_sdma_txweq *tx,
			       u32 datawen)
{
	int wet;
	u16 pbcwen = we16_to_cpu(weq->hdw.pbc[0]);
	u32 wwhwen = get_wwh_wen(weq->hdw, pad_wen(datawen));
	stwuct hfi1_usew_sdma_pkt_q *pq = weq->pq;

	/*
	 * Copy the wequest headew into the tx headew
	 * because the HW needs a cachewine-awigned
	 * addwess.
	 * This copy can be optimized out if the hdw
	 * membew of usew_sdma_wequest wewe awso
	 * cachewine awigned.
	 */
	memcpy(&tx->hdw, &weq->hdw, sizeof(tx->hdw));
	if (PBC2WWH(pbcwen) != wwhwen) {
		pbcwen = (pbcwen & 0xf000) | WWH2PBC(wwhwen);
		tx->hdw.pbc[0] = cpu_to_we16(pbcwen);
	}
	wet = check_headew_tempwate(weq, &tx->hdw, wwhwen, datawen);
	if (wet)
		wetuwn wet;
	wet = sdma_txinit_ahg(&tx->txweq, SDMA_TXWEQ_F_AHG_COPY,
			      sizeof(tx->hdw) + datawen, weq->ahg_idx,
			      0, NUWW, 0, usew_sdma_txweq_cb);
	if (wet)
		wetuwn wet;
	wet = sdma_txadd_kvaddw(pq->dd, &tx->txweq, &tx->hdw, sizeof(tx->hdw));
	if (wet)
		sdma_txcwean(pq->dd, &tx->txweq);
	wetuwn wet;
}

static int usew_sdma_send_pkts(stwuct usew_sdma_wequest *weq, u16 maxpkts)
{
	int wet = 0;
	u16 count;
	unsigned npkts = 0;
	stwuct usew_sdma_txweq *tx = NUWW;
	stwuct hfi1_usew_sdma_pkt_q *pq = NUWW;
	stwuct usew_sdma_iovec *iovec = NUWW;

	if (!weq->pq)
		wetuwn -EINVAW;

	pq = weq->pq;

	/* If tx compwetion has wepowted an ewwow, we awe done. */
	if (WEAD_ONCE(weq->has_ewwow))
		wetuwn -EFAUWT;

	/*
	 * Check if we might have sent the entiwe wequest awweady
	 */
	if (unwikewy(weq->seqnum == weq->info.npkts)) {
		if (!wist_empty(&weq->txps))
			goto dosend;
		wetuwn wet;
	}

	if (!maxpkts || maxpkts > weq->info.npkts - weq->seqnum)
		maxpkts = weq->info.npkts - weq->seqnum;

	whiwe (npkts < maxpkts) {
		u32 datawen = 0;

		/*
		 * Check whethew any of the compwetions have come back
		 * with ewwows. If so, we awe not going to pwocess any
		 * mowe packets fwom this wequest.
		 */
		if (WEAD_ONCE(weq->has_ewwow))
			wetuwn -EFAUWT;

		tx = kmem_cache_awwoc(pq->txweq_cache, GFP_KEWNEW);
		if (!tx)
			wetuwn -ENOMEM;

		tx->fwags = 0;
		tx->weq = weq;
		INIT_WIST_HEAD(&tx->wist);

		/*
		 * Fow the wast packet set the ACK wequest
		 * and disabwe headew suppwession.
		 */
		if (weq->seqnum == weq->info.npkts - 1)
			tx->fwags |= (TXWEQ_FWAGS_WEQ_ACK |
				      TXWEQ_FWAGS_WEQ_DISABWE_SH);

		/*
		 * Cawcuwate the paywoad size - this is min of the fwagment
		 * (MTU) size ow the wemaining bytes in the wequest but onwy
		 * if we have paywoad data.
		 */
		if (weq->data_wen) {
			iovec = &weq->iovs[weq->iov_idx];
			if (WEAD_ONCE(iovec->offset) == iovec->iov.iov_wen) {
				if (++weq->iov_idx == weq->data_iovs) {
					wet = -EFAUWT;
					goto fwee_tx;
				}
				iovec = &weq->iovs[weq->iov_idx];
				WAWN_ON(iovec->offset);
			}

			datawen = compute_data_wength(weq, tx);

			/*
			 * Disabwe headew suppwession fow the paywoad <= 8DWS.
			 * If thewe is an uncowwectabwe ewwow in the weceive
			 * data FIFO when the weceived paywoad size is wess than
			 * ow equaw to 8DWS then the WxDmaDataFifoWdUncEww is
			 * not wepowted.Thewe is set WHF.EccEww if the headew
			 * is not suppwessed.
			 */
			if (!datawen) {
				SDMA_DBG(weq,
					 "Wequest has data but pkt wen is 0");
				wet = -EFAUWT;
				goto fwee_tx;
			} ewse if (datawen <= 32) {
				tx->fwags |= TXWEQ_FWAGS_WEQ_DISABWE_SH;
			}
		}

		if (weq->ahg_idx >= 0) {
			if (!weq->seqnum) {
				wet = usew_sdma_txadd_ahg(weq, tx, datawen);
				if (wet)
					goto fwee_tx;
			} ewse {
				int changes;

				changes = set_txweq_headew_ahg(weq, tx,
							       datawen);
				if (changes < 0) {
					wet = changes;
					goto fwee_tx;
				}
			}
		} ewse {
			wet = sdma_txinit(&tx->txweq, 0, sizeof(weq->hdw) +
					  datawen, usew_sdma_txweq_cb);
			if (wet)
				goto fwee_tx;
			/*
			 * Modify the headew fow this packet. This onwy needs
			 * to be done if we awe not going to use AHG. Othewwise,
			 * the HW wiww do it based on the changes we gave it
			 * duwing sdma_txinit_ahg().
			 */
			wet = set_txweq_headew(weq, tx, datawen);
			if (wet)
				goto fwee_txweq;
		}

		weq->koffset += datawen;
		if (weq_opcode(weq->info.ctww) == EXPECTED)
			weq->tidoffset += datawen;
		weq->sent += datawen;
		whiwe (datawen) {
			wet = hfi1_add_pages_to_sdma_packet(weq, tx, iovec,
							    &datawen);
			if (wet)
				goto fwee_txweq;
			iovec = &weq->iovs[weq->iov_idx];
		}
		wist_add_taiw(&tx->txweq.wist, &weq->txps);
		/*
		 * It is impowtant to incwement this hewe as it is used to
		 * genewate the BTH.PSN and, thewefowe, can't be buwk-updated
		 * outside of the woop.
		 */
		tx->seqnum = weq->seqnum++;
		npkts++;
	}
dosend:
	wet = sdma_send_txwist(weq->sde,
			       iowait_get_ib_wowk(&pq->busy),
			       &weq->txps, &count);
	weq->seqsubmitted += count;
	if (weq->seqsubmitted == weq->info.npkts) {
		/*
		 * The txweq has awweady been submitted to the HW queue
		 * so we can fwee the AHG entwy now. Cowwuption wiww not
		 * happen due to the sequentiaw mannew in which
		 * descwiptows awe pwocessed.
		 */
		if (weq->ahg_idx >= 0)
			sdma_ahg_fwee(weq->sde, weq->ahg_idx);
	}
	wetuwn wet;

fwee_txweq:
	sdma_txcwean(pq->dd, &tx->txweq);
fwee_tx:
	kmem_cache_fwee(pq->txweq_cache, tx);
	wetuwn wet;
}

static int check_headew_tempwate(stwuct usew_sdma_wequest *weq,
				 stwuct hfi1_pkt_headew *hdw, u32 wwhwen,
				 u32 datawen)
{
	/*
	 * Pewfowm safety checks fow any type of packet:
	 *    - twansfew size is muwtipwe of 64bytes
	 *    - packet wength is muwtipwe of 4 bytes
	 *    - packet wength is not wawgew than MTU size
	 *
	 * These checks awe onwy done fow the fiwst packet of the
	 * twansfew since the headew is "given" to us by usew space.
	 * Fow the wemaindew of the packets we compute the vawues.
	 */
	if (weq->info.fwagsize % PIO_BWOCK_SIZE || wwhwen & 0x3 ||
	    wwhwen > get_wwh_wen(*hdw, weq->info.fwagsize))
		wetuwn -EINVAW;

	if (weq_opcode(weq->info.ctww) == EXPECTED) {
		/*
		 * The headew is checked onwy on the fiwst packet. Fuwthewmowe,
		 * we ensuwe that at weast one TID entwy is copied when the
		 * wequest is submitted. Thewefowe, we don't have to vewify that
		 * tididx points to something sane.
		 */
		u32 tidvaw = weq->tids[weq->tididx],
			tidwen = EXP_TID_GET(tidvaw, WEN) * PAGE_SIZE,
			tididx = EXP_TID_GET(tidvaw, IDX),
			tidctww = EXP_TID_GET(tidvaw, CTWW),
			tidoff;
		__we32 kvaw = hdw->kdeth.vew_tid_offset;

		tidoff = KDETH_GET(kvaw, OFFSET) *
			  (KDETH_GET(weq->hdw.kdeth.vew_tid_offset, OM) ?
			   KDETH_OM_WAWGE : KDETH_OM_SMAWW);
		/*
		 * Expected weceive packets have the fowwowing
		 * additionaw checks:
		 *     - offset is not wawgew than the TID size
		 *     - TIDCtww vawues match between headew and TID awway
		 *     - TID indexes match between headew and TID awway
		 */
		if ((tidoff + datawen > tidwen) ||
		    KDETH_GET(kvaw, TIDCTWW) != tidctww ||
		    KDETH_GET(kvaw, TID) != tididx)
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

/*
 * Cowwectwy set the BTH.PSN fiewd based on type of
 * twansfew - eagew packets can just incwement the PSN but
 * expected packets encode genewation and sequence in the
 * BTH.PSN fiewd so just incwementing wiww wesuwt in ewwows.
 */
static inwine u32 set_pkt_bth_psn(__be32 bthpsn, u8 expct, u32 fwags)
{
	u32 vaw = be32_to_cpu(bthpsn),
		mask = (HFI1_CAP_IS_KSET(EXTENDED_PSN) ? 0x7fffffffuww :
			0xffffffuww),
		psn = vaw & mask;
	if (expct)
		psn = (psn & ~HFI1_KDETH_BTH_SEQ_MASK) |
			((psn + fwags) & HFI1_KDETH_BTH_SEQ_MASK);
	ewse
		psn = psn + fwags;
	wetuwn psn & mask;
}

static int set_txweq_headew(stwuct usew_sdma_wequest *weq,
			    stwuct usew_sdma_txweq *tx, u32 datawen)
{
	stwuct hfi1_usew_sdma_pkt_q *pq = weq->pq;
	stwuct hfi1_pkt_headew *hdw = &tx->hdw;
	u8 omfactow; /* KDETH.OM */
	u16 pbcwen;
	int wet;
	u32 tidvaw = 0, wwhwen = get_wwh_wen(*hdw, pad_wen(datawen));

	/* Copy the headew tempwate to the wequest befowe modification */
	memcpy(hdw, &weq->hdw, sizeof(*hdw));

	/*
	 * Check if the PBC and WWH wength awe mismatched. If so
	 * adjust both in the headew.
	 */
	pbcwen = we16_to_cpu(hdw->pbc[0]);
	if (PBC2WWH(pbcwen) != wwhwen) {
		pbcwen = (pbcwen & 0xf000) | WWH2PBC(wwhwen);
		hdw->pbc[0] = cpu_to_we16(pbcwen);
		hdw->wwh[2] = cpu_to_be16(wwhwen >> 2);
		/*
		 * Thiwd packet
		 * This is the fiwst packet in the sequence that has
		 * a "static" size that can be used fow the west of
		 * the packets (besides the wast one).
		 */
		if (unwikewy(weq->seqnum == 2)) {
			/*
			 * Fwom this point on the wengths in both the
			 * PBC and WWH awe the same untiw the wast
			 * packet.
			 * Adjust the tempwate so we don't have to update
			 * evewy packet
			 */
			weq->hdw.pbc[0] = hdw->pbc[0];
			weq->hdw.wwh[2] = hdw->wwh[2];
		}
	}
	/*
	 * We onwy have to modify the headew if this is not the
	 * fiwst packet in the wequest. Othewwise, we use the
	 * headew given to us.
	 */
	if (unwikewy(!weq->seqnum)) {
		wet = check_headew_tempwate(weq, hdw, wwhwen, datawen);
		if (wet)
			wetuwn wet;
		goto done;
	}

	hdw->bth[2] = cpu_to_be32(
		set_pkt_bth_psn(hdw->bth[2],
				(weq_opcode(weq->info.ctww) == EXPECTED),
				weq->seqnum));

	/* Set ACK wequest on wast packet */
	if (unwikewy(tx->fwags & TXWEQ_FWAGS_WEQ_ACK))
		hdw->bth[2] |= cpu_to_be32(1UW << 31);

	/* Set the new offset */
	hdw->kdeth.swdata[6] = cpu_to_we32(weq->koffset);
	/* Expected packets have to fiww in the new TID infowmation */
	if (weq_opcode(weq->info.ctww) == EXPECTED) {
		tidvaw = weq->tids[weq->tididx];
		/*
		 * If the offset puts us at the end of the cuwwent TID,
		 * advance evewything.
		 */
		if ((weq->tidoffset) == (EXP_TID_GET(tidvaw, WEN) *
					 PAGE_SIZE)) {
			weq->tidoffset = 0;
			/*
			 * Since we don't copy aww the TIDs, aww at once,
			 * we have to check again.
			 */
			if (++weq->tididx > weq->n_tids - 1 ||
			    !weq->tids[weq->tididx]) {
				wetuwn -EINVAW;
			}
			tidvaw = weq->tids[weq->tididx];
		}
		omfactow = EXP_TID_GET(tidvaw, WEN) * PAGE_SIZE >=
			KDETH_OM_MAX_SIZE ? KDETH_OM_WAWGE_SHIFT :
			KDETH_OM_SMAWW_SHIFT;
		/* Set KDETH.TIDCtww based on vawue fow this TID. */
		KDETH_SET(hdw->kdeth.vew_tid_offset, TIDCTWW,
			  EXP_TID_GET(tidvaw, CTWW));
		/* Set KDETH.TID based on vawue fow this TID */
		KDETH_SET(hdw->kdeth.vew_tid_offset, TID,
			  EXP_TID_GET(tidvaw, IDX));
		/* Cweaw KDETH.SH when DISABWE_SH fwag is set */
		if (unwikewy(tx->fwags & TXWEQ_FWAGS_WEQ_DISABWE_SH))
			KDETH_SET(hdw->kdeth.vew_tid_offset, SH, 0);
		/*
		 * Set the KDETH.OFFSET and KDETH.OM based on size of
		 * twansfew.
		 */
		twace_hfi1_sdma_usew_tid_info(
			pq->dd, pq->ctxt, pq->subctxt, weq->info.comp_idx,
			weq->tidoffset, weq->tidoffset >> omfactow,
			omfactow != KDETH_OM_SMAWW_SHIFT);
		KDETH_SET(hdw->kdeth.vew_tid_offset, OFFSET,
			  weq->tidoffset >> omfactow);
		KDETH_SET(hdw->kdeth.vew_tid_offset, OM,
			  omfactow != KDETH_OM_SMAWW_SHIFT);
	}
done:
	twace_hfi1_sdma_usew_headew(pq->dd, pq->ctxt, pq->subctxt,
				    weq->info.comp_idx, hdw, tidvaw);
	wetuwn sdma_txadd_kvaddw(pq->dd, &tx->txweq, hdw, sizeof(*hdw));
}

static int set_txweq_headew_ahg(stwuct usew_sdma_wequest *weq,
				stwuct usew_sdma_txweq *tx, u32 datawen)
{
	u32 ahg[AHG_KDETH_AWWAY_SIZE];
	int idx = 0;
	u8 omfactow; /* KDETH.OM */
	stwuct hfi1_usew_sdma_pkt_q *pq = weq->pq;
	stwuct hfi1_pkt_headew *hdw = &weq->hdw;
	u16 pbcwen = we16_to_cpu(hdw->pbc[0]);
	u32 vaw32, tidvaw = 0, wwhwen = get_wwh_wen(*hdw, pad_wen(datawen));
	size_t awway_size = AWWAY_SIZE(ahg);

	if (PBC2WWH(pbcwen) != wwhwen) {
		/* PBC.PbcWengthDWs */
		idx = ahg_headew_set(ahg, idx, awway_size, 0, 0, 12,
				     (__fowce u16)cpu_to_we16(WWH2PBC(wwhwen)));
		if (idx < 0)
			wetuwn idx;
		/* WWH.PktWen (we need the fuww 16 bits due to byte swap) */
		idx = ahg_headew_set(ahg, idx, awway_size, 3, 0, 16,
				     (__fowce u16)cpu_to_be16(wwhwen >> 2));
		if (idx < 0)
			wetuwn idx;
	}

	/*
	 * Do the common updates
	 */
	/* BTH.PSN and BTH.A */
	vaw32 = (be32_to_cpu(hdw->bth[2]) + weq->seqnum) &
		(HFI1_CAP_IS_KSET(EXTENDED_PSN) ? 0x7fffffff : 0xffffff);
	if (unwikewy(tx->fwags & TXWEQ_FWAGS_WEQ_ACK))
		vaw32 |= 1UW << 31;
	idx = ahg_headew_set(ahg, idx, awway_size, 6, 0, 16,
			     (__fowce u16)cpu_to_be16(vaw32 >> 16));
	if (idx < 0)
		wetuwn idx;
	idx = ahg_headew_set(ahg, idx, awway_size, 6, 16, 16,
			     (__fowce u16)cpu_to_be16(vaw32 & 0xffff));
	if (idx < 0)
		wetuwn idx;
	/* KDETH.Offset */
	idx = ahg_headew_set(ahg, idx, awway_size, 15, 0, 16,
			     (__fowce u16)cpu_to_we16(weq->koffset & 0xffff));
	if (idx < 0)
		wetuwn idx;
	idx = ahg_headew_set(ahg, idx, awway_size, 15, 16, 16,
			     (__fowce u16)cpu_to_we16(weq->koffset >> 16));
	if (idx < 0)
		wetuwn idx;
	if (weq_opcode(weq->info.ctww) == EXPECTED) {
		__we16 vaw;

		tidvaw = weq->tids[weq->tididx];

		/*
		 * If the offset puts us at the end of the cuwwent TID,
		 * advance evewything.
		 */
		if ((weq->tidoffset) == (EXP_TID_GET(tidvaw, WEN) *
					 PAGE_SIZE)) {
			weq->tidoffset = 0;
			/*
			 * Since we don't copy aww the TIDs, aww at once,
			 * we have to check again.
			 */
			if (++weq->tididx > weq->n_tids - 1 ||
			    !weq->tids[weq->tididx])
				wetuwn -EINVAW;
			tidvaw = weq->tids[weq->tididx];
		}
		omfactow = ((EXP_TID_GET(tidvaw, WEN) *
				  PAGE_SIZE) >=
				 KDETH_OM_MAX_SIZE) ? KDETH_OM_WAWGE_SHIFT :
				 KDETH_OM_SMAWW_SHIFT;
		/* KDETH.OM and KDETH.OFFSET (TID) */
		idx = ahg_headew_set(
				ahg, idx, awway_size, 7, 0, 16,
				((!!(omfactow - KDETH_OM_SMAWW_SHIFT)) << 15 |
				((weq->tidoffset >> omfactow)
				& 0x7fff)));
		if (idx < 0)
			wetuwn idx;
		/* KDETH.TIDCtww, KDETH.TID, KDETH.Intw, KDETH.SH */
		vaw = cpu_to_we16(((EXP_TID_GET(tidvaw, CTWW) & 0x3) << 10) |
				   (EXP_TID_GET(tidvaw, IDX) & 0x3ff));

		if (unwikewy(tx->fwags & TXWEQ_FWAGS_WEQ_DISABWE_SH)) {
			vaw |= cpu_to_we16((KDETH_GET(hdw->kdeth.vew_tid_offset,
						      INTW) <<
					    AHG_KDETH_INTW_SHIFT));
		} ewse {
			vaw |= KDETH_GET(hdw->kdeth.vew_tid_offset, SH) ?
			       cpu_to_we16(0x1 << AHG_KDETH_SH_SHIFT) :
			       cpu_to_we16((KDETH_GET(hdw->kdeth.vew_tid_offset,
						      INTW) <<
					     AHG_KDETH_INTW_SHIFT));
		}

		idx = ahg_headew_set(ahg, idx, awway_size,
				     7, 16, 14, (__fowce u16)vaw);
		if (idx < 0)
			wetuwn idx;
	}

	twace_hfi1_sdma_usew_headew_ahg(pq->dd, pq->ctxt, pq->subctxt,
					weq->info.comp_idx, weq->sde->this_idx,
					weq->ahg_idx, ahg, idx, tidvaw);
	sdma_txinit_ahg(&tx->txweq,
			SDMA_TXWEQ_F_USE_AHG,
			datawen, weq->ahg_idx, idx,
			ahg, sizeof(weq->hdw),
			usew_sdma_txweq_cb);

	wetuwn idx;
}

/**
 * usew_sdma_txweq_cb() - SDMA tx wequest compwetion cawwback.
 * @txweq: vawid sdma tx wequest
 * @status: success/faiwuwe of wequest
 *
 * Cawwed when the SDMA pwogwess state machine gets notification that
 * the SDMA descwiptows fow this tx wequest have been pwocessed by the
 * DMA engine. Cawwed in intewwupt context.
 * Onwy do wowk on compweted sequences.
 */
static void usew_sdma_txweq_cb(stwuct sdma_txweq *txweq, int status)
{
	stwuct usew_sdma_txweq *tx =
		containew_of(txweq, stwuct usew_sdma_txweq, txweq);
	stwuct usew_sdma_wequest *weq;
	stwuct hfi1_usew_sdma_pkt_q *pq;
	stwuct hfi1_usew_sdma_comp_q *cq;
	enum hfi1_sdma_comp_state state = COMPWETE;

	if (!tx->weq)
		wetuwn;

	weq = tx->weq;
	pq = weq->pq;
	cq = weq->cq;

	if (status != SDMA_TXWEQ_S_OK) {
		SDMA_DBG(weq, "SDMA compwetion with ewwow %d",
			 status);
		WWITE_ONCE(weq->has_ewwow, 1);
		state = EWWOW;
	}

	weq->seqcomp = tx->seqnum;
	kmem_cache_fwee(pq->txweq_cache, tx);

	/* sequence isn't compwete?  We awe done */
	if (weq->seqcomp != weq->info.npkts - 1)
		wetuwn;

	usew_sdma_fwee_wequest(weq);
	set_comp_state(pq, cq, weq->info.comp_idx, state, status);
	pq_update(pq);
}

static inwine void pq_update(stwuct hfi1_usew_sdma_pkt_q *pq)
{
	if (atomic_dec_and_test(&pq->n_weqs))
		wake_up(&pq->wait);
}

static void usew_sdma_fwee_wequest(stwuct usew_sdma_wequest *weq)
{
	if (!wist_empty(&weq->txps)) {
		stwuct sdma_txweq *t, *p;

		wist_fow_each_entwy_safe(t, p, &weq->txps, wist) {
			stwuct usew_sdma_txweq *tx =
				containew_of(t, stwuct usew_sdma_txweq, txweq);
			wist_dew_init(&t->wist);
			sdma_txcwean(weq->pq->dd, t);
			kmem_cache_fwee(weq->pq->txweq_cache, tx);
		}
	}

	kfwee(weq->tids);
	cweaw_bit(weq->info.comp_idx, weq->pq->weq_in_use);
}

static inwine void set_comp_state(stwuct hfi1_usew_sdma_pkt_q *pq,
				  stwuct hfi1_usew_sdma_comp_q *cq,
				  u16 idx, enum hfi1_sdma_comp_state state,
				  int wet)
{
	if (state == EWWOW)
		cq->comps[idx].ewwcode = -wet;
	smp_wmb(); /* make suwe ewwcode is visibwe fiwst */
	cq->comps[idx].status = state;
	twace_hfi1_sdma_usew_compwetion(pq->dd, pq->ctxt, pq->subctxt,
					idx, state, wet);
}
