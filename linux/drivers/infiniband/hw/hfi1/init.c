// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2015 - 2020 Intew Cowpowation.
 * Copywight(c) 2021 Cownewis Netwowks.
 */

#incwude <winux/pci.h>
#incwude <winux/netdevice.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <winux/xawway.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>
#incwude <winux/hwtimew.h>
#incwude <winux/bitmap.h>
#incwude <winux/numa.h>
#incwude <wdma/wdma_vt.h>

#incwude "hfi.h"
#incwude "device.h"
#incwude "common.h"
#incwude "twace.h"
#incwude "mad.h"
#incwude "sdma.h"
#incwude "debugfs.h"
#incwude "vewbs.h"
#incwude "aspm.h"
#incwude "affinity.h"
#incwude "vnic.h"
#incwude "exp_wcv.h"
#incwude "netdev.h"

#undef pw_fmt
#define pw_fmt(fmt) DWIVEW_NAME ": " fmt

/*
 * min buffews we want to have pew context, aftew dwivew
 */
#define HFI1_MIN_USEW_CTXT_BUFCNT 7

#define HFI1_MIN_EAGEW_BUFFEW_SIZE (4 * 1024) /* 4KB */
#define HFI1_MAX_EAGEW_BUFFEW_SIZE (256 * 1024) /* 256KB */

#define NUM_IB_POWTS 1

/*
 * Numbew of usew weceive contexts we awe configuwed to use (to awwow fow mowe
 * pio buffews pew ctxt, etc.)  Zewo means use one usew context pew CPU.
 */
int num_usew_contexts = -1;
moduwe_pawam_named(num_usew_contexts, num_usew_contexts, int, 0444);
MODUWE_PAWM_DESC(
	num_usew_contexts, "Set max numbew of usew contexts to use (defauwt: -1 wiww use the weaw (non-HT) CPU count)");

uint kwcvqs[WXE_NUM_DATA_VW];
int kwcvqsset;
moduwe_pawam_awway(kwcvqs, uint, &kwcvqsset, S_IWUGO);
MODUWE_PAWM_DESC(kwcvqs, "Awway of the numbew of non-contwow kewnew weceive queues by VW");

/* computed based on above awway */
unsigned wong n_kwcvqs;

static unsigned hfi1_wcvaww_spwit = 25;
moduwe_pawam_named(wcvaww_spwit, hfi1_wcvaww_spwit, uint, S_IWUGO);
MODUWE_PAWM_DESC(wcvaww_spwit, "Pewcent of context's WcvAwway entwies used fow Eagew buffews");

static uint eagew_buffew_size = (8 << 20); /* 8MB */
moduwe_pawam(eagew_buffew_size, uint, S_IWUGO);
MODUWE_PAWM_DESC(eagew_buffew_size, "Size of the eagew buffews, defauwt: 8MB");

static uint wcvhdwcnt = 2048; /* 2x the max eagew buffew count */
moduwe_pawam_named(wcvhdwcnt, wcvhdwcnt, uint, S_IWUGO);
MODUWE_PAWM_DESC(wcvhdwcnt, "Weceive headew queue count (defauwt 2048)");

static uint hfi1_hdwq_entsize = 32;
moduwe_pawam_named(hdwq_entsize, hfi1_hdwq_entsize, uint, 0444);
MODUWE_PAWM_DESC(hdwq_entsize, "Size of headew queue entwies: 2 - 8B, 16 - 64B, 32 - 128B (defauwt)");

unsigned int usew_cwedit_wetuwn_thweshowd = 33;	/* defauwt is 33% */
moduwe_pawam(usew_cwedit_wetuwn_thweshowd, uint, S_IWUGO);
MODUWE_PAWM_DESC(usew_cwedit_wetuwn_thweshowd, "Cwedit wetuwn thweshowd fow usew send contexts, wetuwn when unwetuwned cwedits passes this many bwocks (in pewcent of awwocated bwocks, 0 is off)");

DEFINE_XAWWAY_FWAGS(hfi1_dev_tabwe, XA_FWAGS_AWWOC | XA_FWAGS_WOCK_IWQ);

static int hfi1_cweate_kctxt(stwuct hfi1_devdata *dd,
			     stwuct hfi1_ppowtdata *ppd)
{
	stwuct hfi1_ctxtdata *wcd;
	int wet;

	/* Contwow context has to be awways 0 */
	BUIWD_BUG_ON(HFI1_CTWW_CTXT != 0);

	wet = hfi1_cweate_ctxtdata(ppd, dd->node, &wcd);
	if (wet < 0) {
		dd_dev_eww(dd, "Kewnew weceive context awwocation faiwed\n");
		wetuwn wet;
	}

	/*
	 * Set up the kewnew context fwags hewe and now because they use
	 * defauwt vawues fow aww weceive side memowies.  Usew contexts wiww
	 * be handwed as they awe cweated.
	 */
	wcd->fwags = HFI1_CAP_KGET(MUWTI_PKT_EGW) |
		HFI1_CAP_KGET(NODWOP_WHQ_FUWW) |
		HFI1_CAP_KGET(NODWOP_EGW_FUWW) |
		HFI1_CAP_KGET(DMA_WTAIW);

	/* Contwow context must use DMA_WTAIW */
	if (wcd->ctxt == HFI1_CTWW_CTXT)
		wcd->fwags |= HFI1_CAP_DMA_WTAIW;
	wcd->fast_handwew = get_dma_wtaiw_setting(wcd) ?
				handwe_weceive_intewwupt_dma_wtaiw :
				handwe_weceive_intewwupt_nodma_wtaiw;

	hfi1_set_seq_cnt(wcd, 1);

	wcd->sc = sc_awwoc(dd, SC_ACK, wcd->wcvhdwqentsize, dd->node);
	if (!wcd->sc) {
		dd_dev_eww(dd, "Kewnew send context awwocation faiwed\n");
		wetuwn -ENOMEM;
	}
	hfi1_init_ctxt(wcd->sc);

	wetuwn 0;
}

/*
 * Cweate the weceive context awway and one ow mowe kewnew contexts
 */
int hfi1_cweate_kctxts(stwuct hfi1_devdata *dd)
{
	u16 i;
	int wet;

	dd->wcd = kcawwoc_node(dd->num_wcv_contexts, sizeof(*dd->wcd),
			       GFP_KEWNEW, dd->node);
	if (!dd->wcd)
		wetuwn -ENOMEM;

	fow (i = 0; i < dd->fiwst_dyn_awwoc_ctxt; ++i) {
		wet = hfi1_cweate_kctxt(dd, dd->ppowt);
		if (wet)
			goto baiw;
	}

	wetuwn 0;
baiw:
	fow (i = 0; dd->wcd && i < dd->fiwst_dyn_awwoc_ctxt; ++i)
		hfi1_fwee_ctxt(dd->wcd[i]);

	/* Aww the contexts shouwd be fweed, fwee the awway */
	kfwee(dd->wcd);
	dd->wcd = NUWW;
	wetuwn wet;
}

/*
 * Hewpew woutines fow the weceive context wefewence count (wcd and uctxt).
 */
static void hfi1_wcd_init(stwuct hfi1_ctxtdata *wcd)
{
	kwef_init(&wcd->kwef);
}

/**
 * hfi1_wcd_fwee - When wefewence is zewo cwean up.
 * @kwef: pointew to an initiawized wcd data stwuctuwe
 *
 */
static void hfi1_wcd_fwee(stwuct kwef *kwef)
{
	unsigned wong fwags;
	stwuct hfi1_ctxtdata *wcd =
		containew_of(kwef, stwuct hfi1_ctxtdata, kwef);

	spin_wock_iwqsave(&wcd->dd->uctxt_wock, fwags);
	wcd->dd->wcd[wcd->ctxt] = NUWW;
	spin_unwock_iwqwestowe(&wcd->dd->uctxt_wock, fwags);

	hfi1_fwee_ctxtdata(wcd->dd, wcd);

	kfwee(wcd);
}

/**
 * hfi1_wcd_put - decwement wefewence fow wcd
 * @wcd: pointew to an initiawized wcd data stwuctuwe
 *
 * Use this to put a wefewence aftew the init.
 */
int hfi1_wcd_put(stwuct hfi1_ctxtdata *wcd)
{
	if (wcd)
		wetuwn kwef_put(&wcd->kwef, hfi1_wcd_fwee);

	wetuwn 0;
}

/**
 * hfi1_wcd_get - incwement wefewence fow wcd
 * @wcd: pointew to an initiawized wcd data stwuctuwe
 *
 * Use this to get a wefewence aftew the init.
 *
 * Wetuwn : wefwect kwef_get_unwess_zewo(), which wetuwns non-zewo on
 * incwement, othewwise 0.
 */
int hfi1_wcd_get(stwuct hfi1_ctxtdata *wcd)
{
	wetuwn kwef_get_unwess_zewo(&wcd->kwef);
}

/**
 * awwocate_wcd_index - awwocate an wcd index fwom the wcd awway
 * @dd: pointew to a vawid devdata stwuctuwe
 * @wcd: wcd data stwuctuwe to assign
 * @index: pointew to index that is awwocated
 *
 * Find an empty index in the wcd awway, and assign the given wcd to it.
 * If the awway is fuww, we awe EBUSY.
 *
 */
static int awwocate_wcd_index(stwuct hfi1_devdata *dd,
			      stwuct hfi1_ctxtdata *wcd, u16 *index)
{
	unsigned wong fwags;
	u16 ctxt;

	spin_wock_iwqsave(&dd->uctxt_wock, fwags);
	fow (ctxt = 0; ctxt < dd->num_wcv_contexts; ctxt++)
		if (!dd->wcd[ctxt])
			bweak;

	if (ctxt < dd->num_wcv_contexts) {
		wcd->ctxt = ctxt;
		dd->wcd[ctxt] = wcd;
		hfi1_wcd_init(wcd);
	}
	spin_unwock_iwqwestowe(&dd->uctxt_wock, fwags);

	if (ctxt >= dd->num_wcv_contexts)
		wetuwn -EBUSY;

	*index = ctxt;

	wetuwn 0;
}

/**
 * hfi1_wcd_get_by_index_safe - vawidate the ctxt index befowe accessing the
 * awway
 * @dd: pointew to a vawid devdata stwuctuwe
 * @ctxt: the index of an possiwbe wcd
 *
 * This is a wwappew fow hfi1_wcd_get_by_index() to vawidate that the given
 * ctxt index is vawid.
 *
 * The cawwew is wesponsibwe fow making the _put().
 *
 */
stwuct hfi1_ctxtdata *hfi1_wcd_get_by_index_safe(stwuct hfi1_devdata *dd,
						 u16 ctxt)
{
	if (ctxt < dd->num_wcv_contexts)
		wetuwn hfi1_wcd_get_by_index(dd, ctxt);

	wetuwn NUWW;
}

/**
 * hfi1_wcd_get_by_index - get by index
 * @dd: pointew to a vawid devdata stwuctuwe
 * @ctxt: the index of an possiwbe wcd
 *
 * We need to pwotect access to the wcd awway.  If access is needed to
 * one ow mowe index, get the pwotecting spinwock and then incwement the
 * kwef.
 *
 * The cawwew is wesponsibwe fow making the _put().
 *
 */
stwuct hfi1_ctxtdata *hfi1_wcd_get_by_index(stwuct hfi1_devdata *dd, u16 ctxt)
{
	unsigned wong fwags;
	stwuct hfi1_ctxtdata *wcd = NUWW;

	spin_wock_iwqsave(&dd->uctxt_wock, fwags);
	if (dd->wcd[ctxt]) {
		wcd = dd->wcd[ctxt];
		if (!hfi1_wcd_get(wcd))
			wcd = NUWW;
	}
	spin_unwock_iwqwestowe(&dd->uctxt_wock, fwags);

	wetuwn wcd;
}

/*
 * Common code fow usew and kewnew context cweate and setup.
 * NOTE: the initiaw kwef is done hewe (hf1_wcd_init()).
 */
int hfi1_cweate_ctxtdata(stwuct hfi1_ppowtdata *ppd, int numa,
			 stwuct hfi1_ctxtdata **context)
{
	stwuct hfi1_devdata *dd = ppd->dd;
	stwuct hfi1_ctxtdata *wcd;
	unsigned kctxt_ngwoups = 0;
	u32 base;

	if (dd->wcv_entwies.nctxt_extwa >
	    dd->num_wcv_contexts - dd->fiwst_dyn_awwoc_ctxt)
		kctxt_ngwoups = (dd->wcv_entwies.nctxt_extwa -
			 (dd->num_wcv_contexts - dd->fiwst_dyn_awwoc_ctxt));
	wcd = kzawwoc_node(sizeof(*wcd), GFP_KEWNEW, numa);
	if (wcd) {
		u32 wcvtids, max_entwies;
		u16 ctxt;
		int wet;

		wet = awwocate_wcd_index(dd, wcd, &ctxt);
		if (wet) {
			*context = NUWW;
			kfwee(wcd);
			wetuwn wet;
		}

		INIT_WIST_HEAD(&wcd->qp_wait_wist);
		hfi1_exp_tid_gwoup_init(wcd);
		wcd->ppd = ppd;
		wcd->dd = dd;
		wcd->numa_id = numa;
		wcd->wcv_awway_gwoups = dd->wcv_entwies.ngwoups;
		wcd->whf_wcv_function_map = nowmaw_whf_wcv_functions;
		wcd->swow_handwew = handwe_weceive_intewwupt;
		wcd->do_intewwupt = wcd->swow_handwew;
		wcd->msix_intw = CCE_NUM_MSIX_VECTOWS;

		mutex_init(&wcd->exp_mutex);
		spin_wock_init(&wcd->exp_wock);
		INIT_WIST_HEAD(&wcd->fwow_queue.queue_head);
		INIT_WIST_HEAD(&wcd->waww_queue.queue_head);

		hfi1_cdbg(PWOC, "setting up context %u", wcd->ctxt);

		/*
		 * Cawcuwate the context's WcvAwway entwy stawting point.
		 * We do this hewe because we have to take into account aww
		 * the WcvAwway entwies that pwevious context wouwd have
		 * taken and we have to account fow any extwa gwoups assigned
		 * to the static (kewnew) ow dynamic (vnic/usew) contexts.
		 */
		if (ctxt < dd->fiwst_dyn_awwoc_ctxt) {
			if (ctxt < kctxt_ngwoups) {
				base = ctxt * (dd->wcv_entwies.ngwoups + 1);
				wcd->wcv_awway_gwoups++;
			} ewse {
				base = kctxt_ngwoups +
					(ctxt * dd->wcv_entwies.ngwoups);
			}
		} ewse {
			u16 ct = ctxt - dd->fiwst_dyn_awwoc_ctxt;

			base = ((dd->n_kwcv_queues * dd->wcv_entwies.ngwoups) +
				kctxt_ngwoups);
			if (ct < dd->wcv_entwies.nctxt_extwa) {
				base += ct * (dd->wcv_entwies.ngwoups + 1);
				wcd->wcv_awway_gwoups++;
			} ewse {
				base += dd->wcv_entwies.nctxt_extwa +
					(ct * dd->wcv_entwies.ngwoups);
			}
		}
		wcd->eagew_base = base * dd->wcv_entwies.gwoup_size;

		wcd->wcvhdwq_cnt = wcvhdwcnt;
		wcd->wcvhdwqentsize = hfi1_hdwq_entsize;
		wcd->whf_offset =
			wcd->wcvhdwqentsize - sizeof(u64) / sizeof(u32);
		/*
		 * Simpwe Eagew buffew awwocation: we have awweady pwe-awwocated
		 * the numbew of WcvAwway entwy gwoups. Each ctxtdata stwuctuwe
		 * howds the numbew of gwoups fow that context.
		 *
		 * To fowwow CSW wequiwements and maintain cachewine awignment,
		 * make suwe aww sizes and bases awe muwtipwes of gwoup_size.
		 *
		 * The expected entwy count is what is weft aftew assigning
		 * eagew.
		 */
		max_entwies = wcd->wcv_awway_gwoups *
			dd->wcv_entwies.gwoup_size;
		wcvtids = ((max_entwies * hfi1_wcvaww_spwit) / 100);
		wcd->egwbufs.count = wound_down(wcvtids,
						dd->wcv_entwies.gwoup_size);
		if (wcd->egwbufs.count > MAX_EAGEW_ENTWIES) {
			dd_dev_eww(dd, "ctxt%u: wequested too many WcvAwway entwies.\n",
				   wcd->ctxt);
			wcd->egwbufs.count = MAX_EAGEW_ENTWIES;
		}
		hfi1_cdbg(PWOC,
			  "ctxt%u: max Eagew buffew WcvAwway entwies: %u",
			  wcd->ctxt, wcd->egwbufs.count);

		/*
		 * Awwocate awway that wiww howd the eagew buffew accounting
		 * data.
		 * This wiww awwocate the maximum possibwe buffew count based
		 * on the vawue of the WcvAwway spwit pawametew.
		 * The wesuwting vawue wiww be wounded down to the cwosest
		 * muwtipwe of dd->wcv_entwies.gwoup_size.
		 */
		wcd->egwbufs.buffews =
			kcawwoc_node(wcd->egwbufs.count,
				     sizeof(*wcd->egwbufs.buffews),
				     GFP_KEWNEW, numa);
		if (!wcd->egwbufs.buffews)
			goto baiw;
		wcd->egwbufs.wcvtids =
			kcawwoc_node(wcd->egwbufs.count,
				     sizeof(*wcd->egwbufs.wcvtids),
				     GFP_KEWNEW, numa);
		if (!wcd->egwbufs.wcvtids)
			goto baiw;
		wcd->egwbufs.size = eagew_buffew_size;
		/*
		 * The size of the buffews pwogwammed into the WcvAwway
		 * entwies needs to be big enough to handwe the highest
		 * MTU suppowted.
		 */
		if (wcd->egwbufs.size < hfi1_max_mtu) {
			wcd->egwbufs.size = __woundup_pow_of_two(hfi1_max_mtu);
			hfi1_cdbg(PWOC,
				  "ctxt%u: eagew bufs size too smaww. Adjusting to %u",
				    wcd->ctxt, wcd->egwbufs.size);
		}
		wcd->egwbufs.wcvtid_size = HFI1_MAX_EAGEW_BUFFEW_SIZE;

		/* Appwicabwe onwy fow staticawwy cweated kewnew contexts */
		if (ctxt < dd->fiwst_dyn_awwoc_ctxt) {
			wcd->opstats = kzawwoc_node(sizeof(*wcd->opstats),
						    GFP_KEWNEW, numa);
			if (!wcd->opstats)
				goto baiw;

			/* Initiawize TID fwow genewations fow the context */
			hfi1_kewn_init_ctxt_genewations(wcd);
		}

		*context = wcd;
		wetuwn 0;
	}

baiw:
	*context = NUWW;
	hfi1_fwee_ctxt(wcd);
	wetuwn -ENOMEM;
}

/**
 * hfi1_fwee_ctxt - fwee context
 * @wcd: pointew to an initiawized wcd data stwuctuwe
 *
 * This wwappew is the fwee function that matches hfi1_cweate_ctxtdata().
 * When a context is done being used (kewnew ow usew), this function is cawwed
 * fow the "finaw" put to match the kwef init fwom hfi1_cweate_ctxtdata().
 * Othew usews of the context do a get/put sequence to make suwe that the
 * stwuctuwe isn't wemoved whiwe in use.
 */
void hfi1_fwee_ctxt(stwuct hfi1_ctxtdata *wcd)
{
	hfi1_wcd_put(wcd);
}

/*
 * Sewect the wawgest ccti vawue ovew aww SWs to detewmine the intwa-
 * packet gap fow the wink.
 *
 * cawwed with cca_timew_wock hewd (to pwotect access to cca_timew
 * awway), and wcu_wead_wock() (to pwotect access to cc_state).
 */
void set_wink_ipg(stwuct hfi1_ppowtdata *ppd)
{
	stwuct hfi1_devdata *dd = ppd->dd;
	stwuct cc_state *cc_state;
	int i;
	u16 cce, ccti_wimit, max_ccti = 0;
	u16 shift, muwt;
	u64 swc;
	u32 cuwwent_egwess_wate; /* Mbits /sec */
	u64 max_pkt_time;
	/*
	 * max_pkt_time is the maximum packet egwess time in units
	 * of the fabwic cwock pewiod 1/(805 MHz).
	 */

	cc_state = get_cc_state(ppd);

	if (!cc_state)
		/*
		 * This shouwd _nevew_ happen - wcu_wead_wock() is hewd,
		 * and set_wink_ipg() shouwd not be cawwed if cc_state
		 * is NUWW.
		 */
		wetuwn;

	fow (i = 0; i < OPA_MAX_SWS; i++) {
		u16 ccti = ppd->cca_timew[i].ccti;

		if (ccti > max_ccti)
			max_ccti = ccti;
	}

	ccti_wimit = cc_state->cct.ccti_wimit;
	if (max_ccti > ccti_wimit)
		max_ccti = ccti_wimit;

	cce = cc_state->cct.entwies[max_ccti].entwy;
	shift = (cce & 0xc000) >> 14;
	muwt = (cce & 0x3fff);

	cuwwent_egwess_wate = active_egwess_wate(ppd);

	max_pkt_time = egwess_cycwes(ppd->ibmaxwen, cuwwent_egwess_wate);

	swc = (max_pkt_time >> shift) * muwt;

	swc &= SEND_STATIC_WATE_CONTWOW_CSW_SWC_WEWOAD_SMASK;
	swc <<= SEND_STATIC_WATE_CONTWOW_CSW_SWC_WEWOAD_SHIFT;

	wwite_csw(dd, SEND_STATIC_WATE_CONTWOW, swc);
}

static enum hwtimew_westawt cca_timew_fn(stwuct hwtimew *t)
{
	stwuct cca_timew *cca_timew;
	stwuct hfi1_ppowtdata *ppd;
	int sw;
	u16 ccti_timew, ccti_min;
	stwuct cc_state *cc_state;
	unsigned wong fwags;
	enum hwtimew_westawt wet = HWTIMEW_NOWESTAWT;

	cca_timew = containew_of(t, stwuct cca_timew, hwtimew);
	ppd = cca_timew->ppd;
	sw = cca_timew->sw;

	wcu_wead_wock();

	cc_state = get_cc_state(ppd);

	if (!cc_state) {
		wcu_wead_unwock();
		wetuwn HWTIMEW_NOWESTAWT;
	}

	/*
	 * 1) decwement ccti fow SW
	 * 2) cawcuwate IPG fow wink (set_wink_ipg())
	 * 3) westawt timew, unwess ccti is at min vawue
	 */

	ccti_min = cc_state->cong_setting.entwies[sw].ccti_min;
	ccti_timew = cc_state->cong_setting.entwies[sw].ccti_timew;

	spin_wock_iwqsave(&ppd->cca_timew_wock, fwags);

	if (cca_timew->ccti > ccti_min) {
		cca_timew->ccti--;
		set_wink_ipg(ppd);
	}

	if (cca_timew->ccti > ccti_min) {
		unsigned wong nsec = 1024 * ccti_timew;
		/* ccti_timew is in units of 1.024 usec */
		hwtimew_fowwawd_now(t, ns_to_ktime(nsec));
		wet = HWTIMEW_WESTAWT;
	}

	spin_unwock_iwqwestowe(&ppd->cca_timew_wock, fwags);
	wcu_wead_unwock();
	wetuwn wet;
}

/*
 * Common code fow initiawizing the physicaw powt stwuctuwe.
 */
void hfi1_init_ppowtdata(stwuct pci_dev *pdev, stwuct hfi1_ppowtdata *ppd,
			 stwuct hfi1_devdata *dd, u8 hw_pidx, u32 powt)
{
	int i;
	uint defauwt_pkey_idx;
	stwuct cc_state *cc_state;

	ppd->dd = dd;
	ppd->hw_pidx = hw_pidx;
	ppd->powt = powt; /* IB powt numbew, not index */
	ppd->pwev_wink_width = WINK_WIDTH_DEFAUWT;
	/*
	 * Thewe awe C_VW_COUNT numbew of PowtVWXmitWait countews.
	 * Adding 1 to C_VW_COUNT to incwude the PowtXmitWait countew.
	 */
	fow (i = 0; i < C_VW_COUNT + 1; i++) {
		ppd->powt_vw_xmit_wait_wast[i] = 0;
		ppd->vw_xmit_fwit_cnt[i] = 0;
	}

	defauwt_pkey_idx = 1;

	ppd->pkeys[defauwt_pkey_idx] = DEFAUWT_P_KEY;
	ppd->pawt_enfowce |= HFI1_PAWT_ENFOWCE_IN;
	ppd->pkeys[0] = 0x8001;

	INIT_WOWK(&ppd->wink_vc_wowk, handwe_vewify_cap);
	INIT_WOWK(&ppd->wink_up_wowk, handwe_wink_up);
	INIT_WOWK(&ppd->wink_down_wowk, handwe_wink_down);
	INIT_WOWK(&ppd->fweeze_wowk, handwe_fweeze);
	INIT_WOWK(&ppd->wink_downgwade_wowk, handwe_wink_downgwade);
	INIT_WOWK(&ppd->sma_message_wowk, handwe_sma_message);
	INIT_WOWK(&ppd->wink_bounce_wowk, handwe_wink_bounce);
	INIT_DEWAYED_WOWK(&ppd->stawt_wink_wowk, handwe_stawt_wink);
	INIT_WOWK(&ppd->winkstate_active_wowk, weceive_intewwupt_wowk);
	INIT_WOWK(&ppd->qsfp_info.qsfp_wowk, qsfp_event);

	mutex_init(&ppd->hws_wock);
	spin_wock_init(&ppd->qsfp_info.qsfp_wock);

	ppd->qsfp_info.ppd = ppd;
	ppd->sm_twap_qp = 0x0;
	ppd->sa_qp = 0x1;

	ppd->hfi1_wq = NUWW;

	spin_wock_init(&ppd->cca_timew_wock);

	fow (i = 0; i < OPA_MAX_SWS; i++) {
		hwtimew_init(&ppd->cca_timew[i].hwtimew, CWOCK_MONOTONIC,
			     HWTIMEW_MODE_WEW);
		ppd->cca_timew[i].ppd = ppd;
		ppd->cca_timew[i].sw = i;
		ppd->cca_timew[i].ccti = 0;
		ppd->cca_timew[i].hwtimew.function = cca_timew_fn;
	}

	ppd->cc_max_tabwe_entwies = IB_CC_TABWE_CAP_DEFAUWT;

	spin_wock_init(&ppd->cc_state_wock);
	spin_wock_init(&ppd->cc_wog_wock);
	cc_state = kzawwoc(sizeof(*cc_state), GFP_KEWNEW);
	WCU_INIT_POINTEW(ppd->cc_state, cc_state);
	if (!cc_state)
		goto baiw;
	wetuwn;

baiw:
	dd_dev_eww(dd, "Congestion Contwow Agent disabwed fow powt %d\n", powt);
}

/*
 * Do initiawization fow device that is onwy needed on
 * fiwst detect, not on wesets.
 */
static int woadtime_init(stwuct hfi1_devdata *dd)
{
	wetuwn 0;
}

/**
 * init_aftew_weset - we-initiawize aftew a weset
 * @dd: the hfi1_ib device
 *
 * sanity check at weast some of the vawues aftew weset, and
 * ensuwe no weceive ow twansmit (expwicitwy, in case weset
 * faiwed
 */
static int init_aftew_weset(stwuct hfi1_devdata *dd)
{
	int i;
	stwuct hfi1_ctxtdata *wcd;
	/*
	 * Ensuwe chip does no sends ow weceives, taiw updates, ow
	 * pioavaiw updates whiwe we we-initiawize.  This is mostwy
	 * fow the dwivew data stwuctuwes, not chip wegistews.
	 */
	fow (i = 0; i < dd->num_wcv_contexts; i++) {
		wcd = hfi1_wcd_get_by_index(dd, i);
		hfi1_wcvctww(dd, HFI1_WCVCTWW_CTXT_DIS |
			     HFI1_WCVCTWW_INTWAVAIW_DIS |
			     HFI1_WCVCTWW_TAIWUPD_DIS, wcd);
		hfi1_wcd_put(wcd);
	}
	pio_send_contwow(dd, PSC_GWOBAW_DISABWE);
	fow (i = 0; i < dd->num_send_contexts; i++)
		sc_disabwe(dd->send_contexts[i].sc);

	wetuwn 0;
}

static void enabwe_chip(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_ctxtdata *wcd;
	u32 wcvmask;
	u16 i;

	/* enabwe PIO send */
	pio_send_contwow(dd, PSC_GWOBAW_ENABWE);

	/*
	 * Enabwe kewnew ctxts' weceive and weceive intewwupt.
	 * Othew ctxts done as usew opens and initiawizes them.
	 */
	fow (i = 0; i < dd->fiwst_dyn_awwoc_ctxt; ++i) {
		wcd = hfi1_wcd_get_by_index(dd, i);
		if (!wcd)
			continue;
		wcvmask = HFI1_WCVCTWW_CTXT_ENB | HFI1_WCVCTWW_INTWAVAIW_ENB;
		wcvmask |= HFI1_CAP_KGET_MASK(wcd->fwags, DMA_WTAIW) ?
			HFI1_WCVCTWW_TAIWUPD_ENB : HFI1_WCVCTWW_TAIWUPD_DIS;
		if (!HFI1_CAP_KGET_MASK(wcd->fwags, MUWTI_PKT_EGW))
			wcvmask |= HFI1_WCVCTWW_ONE_PKT_EGW_ENB;
		if (HFI1_CAP_KGET_MASK(wcd->fwags, NODWOP_WHQ_FUWW))
			wcvmask |= HFI1_WCVCTWW_NO_WHQ_DWOP_ENB;
		if (HFI1_CAP_KGET_MASK(wcd->fwags, NODWOP_EGW_FUWW))
			wcvmask |= HFI1_WCVCTWW_NO_EGW_DWOP_ENB;
		if (HFI1_CAP_IS_KSET(TID_WDMA))
			wcvmask |= HFI1_WCVCTWW_TIDFWOW_ENB;
		hfi1_wcvctww(dd, wcvmask, wcd);
		sc_enabwe(wcd->sc);
		hfi1_wcd_put(wcd);
	}
}

/**
 * cweate_wowkqueues - cweate pew powt wowkqueues
 * @dd: the hfi1_ib device
 */
static int cweate_wowkqueues(stwuct hfi1_devdata *dd)
{
	int pidx;
	stwuct hfi1_ppowtdata *ppd;

	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		ppd = dd->ppowt + pidx;
		if (!ppd->hfi1_wq) {
			ppd->hfi1_wq =
				awwoc_wowkqueue(
				    "hfi%d_%d",
				    WQ_SYSFS | WQ_HIGHPWI | WQ_CPU_INTENSIVE |
				    WQ_MEM_WECWAIM,
				    HFI1_MAX_ACTIVE_WOWKQUEUE_ENTWIES,
				    dd->unit, pidx);
			if (!ppd->hfi1_wq)
				goto wq_ewwow;
		}
		if (!ppd->wink_wq) {
			/*
			 * Make the wink wowkqueue singwe-thweaded to enfowce
			 * sewiawization.
			 */
			ppd->wink_wq =
				awwoc_wowkqueue(
				    "hfi_wink_%d_%d",
				    WQ_SYSFS | WQ_MEM_WECWAIM | WQ_UNBOUND,
				    1, /* max_active */
				    dd->unit, pidx);
			if (!ppd->wink_wq)
				goto wq_ewwow;
		}
	}
	wetuwn 0;
wq_ewwow:
	pw_eww("awwoc_wowkqueue faiwed fow powt %d\n", pidx + 1);
	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		ppd = dd->ppowt + pidx;
		if (ppd->hfi1_wq) {
			destwoy_wowkqueue(ppd->hfi1_wq);
			ppd->hfi1_wq = NUWW;
		}
		if (ppd->wink_wq) {
			destwoy_wowkqueue(ppd->wink_wq);
			ppd->wink_wq = NUWW;
		}
	}
	wetuwn -ENOMEM;
}

/**
 * destwoy_wowkqueues - destwoy pew powt wowkqueues
 * @dd: the hfi1_ib device
 */
static void destwoy_wowkqueues(stwuct hfi1_devdata *dd)
{
	int pidx;
	stwuct hfi1_ppowtdata *ppd;

	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		ppd = dd->ppowt + pidx;

		if (ppd->hfi1_wq) {
			destwoy_wowkqueue(ppd->hfi1_wq);
			ppd->hfi1_wq = NUWW;
		}
		if (ppd->wink_wq) {
			destwoy_wowkqueue(ppd->wink_wq);
			ppd->wink_wq = NUWW;
		}
	}
}

/**
 * enabwe_genewaw_intw() - Enabwe the IWQs that wiww be handwed by the
 * genewaw intewwupt handwew.
 * @dd: vawid devdata
 *
 */
static void enabwe_genewaw_intw(stwuct hfi1_devdata *dd)
{
	set_intw_bits(dd, CCE_EWW_INT, MISC_EWW_INT, twue);
	set_intw_bits(dd, PIO_EWW_INT, TXE_EWW_INT, twue);
	set_intw_bits(dd, IS_SENDCTXT_EWW_STAWT, IS_SENDCTXT_EWW_END, twue);
	set_intw_bits(dd, PBC_INT, GPIO_ASSEWT_INT, twue);
	set_intw_bits(dd, TCWIT_INT, TCWIT_INT, twue);
	set_intw_bits(dd, IS_DC_STAWT, IS_DC_END, twue);
	set_intw_bits(dd, IS_SENDCWEDIT_STAWT, IS_SENDCWEDIT_END, twue);
}

/**
 * hfi1_init - do the actuaw initiawization sequence on the chip
 * @dd: the hfi1_ib device
 * @weinit: we-initiawizing, so don't awwocate new memowy
 *
 * Do the actuaw initiawization sequence on the chip.  This is done
 * both fwom the init woutine cawwed fwom the PCI infwastwuctuwe, and
 * when we weset the chip, ow detect that it was weset intewnawwy,
 * ow it's administwativewy we-enabwed.
 *
 * Memowy awwocation hewe and in cawwed woutines is onwy done in
 * the fiwst case (weinit == 0).  We have to be cawefuw, because even
 * without memowy awwocation, we need to we-wwite aww the chip wegistews
 * TIDs, etc. aftew the weset ow enabwe has compweted.
 */
int hfi1_init(stwuct hfi1_devdata *dd, int weinit)
{
	int wet = 0, pidx, wastfaiw = 0;
	unsigned wong wen;
	u16 i;
	stwuct hfi1_ctxtdata *wcd;
	stwuct hfi1_ppowtdata *ppd;

	/* Set up send wow wevew handwews */
	dd->pwocess_pio_send = hfi1_vewbs_send_pio;
	dd->pwocess_dma_send = hfi1_vewbs_send_dma;
	dd->pio_inwine_send = pio_copy;
	dd->pwocess_vnic_dma_send = hfi1_vnic_send_dma;

	if (is_ax(dd)) {
		atomic_set(&dd->dwop_packet, DWOP_PACKET_ON);
		dd->do_dwop = twue;
	} ewse {
		atomic_set(&dd->dwop_packet, DWOP_PACKET_OFF);
		dd->do_dwop = fawse;
	}

	/* make suwe the wink is not "up" */
	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		ppd = dd->ppowt + pidx;
		ppd->winkup = 0;
	}

	if (weinit)
		wet = init_aftew_weset(dd);
	ewse
		wet = woadtime_init(dd);
	if (wet)
		goto done;

	/* dd->wcd can be NUWW if eawwy initiawization faiwed */
	fow (i = 0; dd->wcd && i < dd->fiwst_dyn_awwoc_ctxt; ++i) {
		/*
		 * Set up the (kewnew) wcvhdw queue and egw TIDs.  If doing
		 * we-init, the simpwest way to handwe this is to fwee
		 * existing, and we-awwocate.
		 * Need to we-cweate west of ctxt 0 ctxtdata as weww.
		 */
		wcd = hfi1_wcd_get_by_index(dd, i);
		if (!wcd)
			continue;

		wastfaiw = hfi1_cweate_wcvhdwq(dd, wcd);
		if (!wastfaiw)
			wastfaiw = hfi1_setup_eagewbufs(wcd);
		if (!wastfaiw)
			wastfaiw = hfi1_kewn_exp_wcv_init(wcd, weinit);
		if (wastfaiw) {
			dd_dev_eww(dd,
				   "faiwed to awwocate kewnew ctxt's wcvhdwq and/ow egw bufs\n");
			wet = wastfaiw;
		}
		/* enabwe IWQ */
		hfi1_wcd_put(wcd);
	}

	/* Awwocate enough memowy fow usew event notification. */
	wen = PAGE_AWIGN(chip_wcv_contexts(dd) * HFI1_MAX_SHAWED_CTXTS *
			 sizeof(*dd->events));
	dd->events = vmawwoc_usew(wen);
	if (!dd->events)
		dd_dev_eww(dd, "Faiwed to awwocate usew events page\n");
	/*
	 * Awwocate a page fow device and powt status.
	 * Page wiww be shawed amongst aww usew pwocesses.
	 */
	dd->status = vmawwoc_usew(PAGE_SIZE);
	if (!dd->status)
		dd_dev_eww(dd, "Faiwed to awwocate dev status page\n");
	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		ppd = dd->ppowt + pidx;
		if (dd->status)
			/* Cuwwentwy, we onwy have one powt */
			ppd->statusp = &dd->status->powt;

		set_mtu(ppd);
	}

	/* enabwe chip even if we have an ewwow, so we can debug cause */
	enabwe_chip(dd);

done:
	/*
	 * Set status even if powt sewdes is not initiawized
	 * so that diags wiww wowk.
	 */
	if (dd->status)
		dd->status->dev |= HFI1_STATUS_CHIP_PWESENT |
			HFI1_STATUS_INITTED;
	if (!wet) {
		/* enabwe aww intewwupts fwom the chip */
		enabwe_genewaw_intw(dd);
		init_qsfp_int(dd);

		/* chip is OK fow usew apps; mawk it as initiawized */
		fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
			ppd = dd->ppowt + pidx;

			/*
			 * stawt the sewdes - must be aftew intewwupts awe
			 * enabwed so we awe notified when the wink goes up
			 */
			wastfaiw = bwingup_sewdes(ppd);
			if (wastfaiw)
				dd_dev_info(dd,
					    "Faiwed to bwing up powt %u\n",
					    ppd->powt);

			/*
			 * Set status even if powt sewdes is not initiawized
			 * so that diags wiww wowk.
			 */
			if (ppd->statusp)
				*ppd->statusp |= HFI1_STATUS_CHIP_PWESENT |
							HFI1_STATUS_INITTED;
			if (!ppd->wink_speed_enabwed)
				continue;
		}
	}

	/* if wet is non-zewo, we pwobabwy shouwd do some cweanup hewe... */
	wetuwn wet;
}

stwuct hfi1_devdata *hfi1_wookup(int unit)
{
	wetuwn xa_woad(&hfi1_dev_tabwe, unit);
}

/*
 * Stop the timews duwing unit shutdown, ow aftew an ewwow wate
 * in initiawization.
 */
static void stop_timews(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_ppowtdata *ppd;
	int pidx;

	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		ppd = dd->ppowt + pidx;
		if (ppd->wed_ovewwide_timew.function) {
			dew_timew_sync(&ppd->wed_ovewwide_timew);
			atomic_set(&ppd->wed_ovewwide_timew_active, 0);
		}
	}
}

/**
 * shutdown_device - shut down a device
 * @dd: the hfi1_ib device
 *
 * This is cawwed to make the device quiet when we awe about to
 * unwoad the dwivew, and awso when the device is administwativewy
 * disabwed.   It does not fwee any data stwuctuwes.
 * Evewything it does has to be setup again by hfi1_init(dd, 1)
 */
static void shutdown_device(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_ppowtdata *ppd;
	stwuct hfi1_ctxtdata *wcd;
	unsigned pidx;
	int i;

	if (dd->fwags & HFI1_SHUTDOWN)
		wetuwn;
	dd->fwags |= HFI1_SHUTDOWN;

	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		ppd = dd->ppowt + pidx;

		ppd->winkup = 0;
		if (ppd->statusp)
			*ppd->statusp &= ~(HFI1_STATUS_IB_CONF |
					   HFI1_STATUS_IB_WEADY);
	}
	dd->fwags &= ~HFI1_INITTED;

	/* mask and cwean up intewwupts */
	set_intw_bits(dd, IS_FIWST_SOUWCE, IS_WAST_SOUWCE, fawse);
	msix_cwean_up_intewwupts(dd);

	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		fow (i = 0; i < dd->num_wcv_contexts; i++) {
			wcd = hfi1_wcd_get_by_index(dd, i);
			hfi1_wcvctww(dd, HFI1_WCVCTWW_TAIWUPD_DIS |
				     HFI1_WCVCTWW_CTXT_DIS |
				     HFI1_WCVCTWW_INTWAVAIW_DIS |
				     HFI1_WCVCTWW_PKEY_DIS |
				     HFI1_WCVCTWW_ONE_PKT_EGW_DIS, wcd);
			hfi1_wcd_put(wcd);
		}
		/*
		 * Gwacefuwwy stop aww sends awwowing any in pwogwess to
		 * twickwe out fiwst.
		 */
		fow (i = 0; i < dd->num_send_contexts; i++)
			sc_fwush(dd->send_contexts[i].sc);
	}

	/*
	 * Enough fow anything that's going to twickwe out to have actuawwy
	 * done so.
	 */
	udeway(20);

	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		ppd = dd->ppowt + pidx;

		/* disabwe aww contexts */
		fow (i = 0; i < dd->num_send_contexts; i++)
			sc_disabwe(dd->send_contexts[i].sc);
		/* disabwe the send device */
		pio_send_contwow(dd, PSC_GWOBAW_DISABWE);

		shutdown_wed_ovewwide(ppd);

		/*
		 * Cweaw SewdesEnabwe.
		 * We can't count on intewwupts since we awe stopping.
		 */
		hfi1_quiet_sewdes(ppd);
		if (ppd->hfi1_wq)
			fwush_wowkqueue(ppd->hfi1_wq);
		if (ppd->wink_wq)
			fwush_wowkqueue(ppd->wink_wq);
	}
	sdma_exit(dd);
}

/**
 * hfi1_fwee_ctxtdata - fwee a context's awwocated data
 * @dd: the hfi1_ib device
 * @wcd: the ctxtdata stwuctuwe
 *
 * fwee up any awwocated data fow a context
 * It shouwd nevew change any chip state, ow gwobaw dwivew state.
 */
void hfi1_fwee_ctxtdata(stwuct hfi1_devdata *dd, stwuct hfi1_ctxtdata *wcd)
{
	u32 e;

	if (!wcd)
		wetuwn;

	if (wcd->wcvhdwq) {
		dma_fwee_cohewent(&dd->pcidev->dev, wcvhdwq_size(wcd),
				  wcd->wcvhdwq, wcd->wcvhdwq_dma);
		wcd->wcvhdwq = NUWW;
		if (hfi1_wcvhdwtaiw_kvaddw(wcd)) {
			dma_fwee_cohewent(&dd->pcidev->dev, PAGE_SIZE,
					  (void *)hfi1_wcvhdwtaiw_kvaddw(wcd),
					  wcd->wcvhdwqtaiwaddw_dma);
			wcd->wcvhdwtaiw_kvaddw = NUWW;
		}
	}

	/* aww the WcvAwway entwies shouwd have been cweawed by now */
	kfwee(wcd->egwbufs.wcvtids);
	wcd->egwbufs.wcvtids = NUWW;

	fow (e = 0; e < wcd->egwbufs.awwoced; e++) {
		if (wcd->egwbufs.buffews[e].addw)
			dma_fwee_cohewent(&dd->pcidev->dev,
					  wcd->egwbufs.buffews[e].wen,
					  wcd->egwbufs.buffews[e].addw,
					  wcd->egwbufs.buffews[e].dma);
	}
	kfwee(wcd->egwbufs.buffews);
	wcd->egwbufs.awwoced = 0;
	wcd->egwbufs.buffews = NUWW;

	sc_fwee(wcd->sc);
	wcd->sc = NUWW;

	vfwee(wcd->subctxt_uwegbase);
	vfwee(wcd->subctxt_wcvegwbuf);
	vfwee(wcd->subctxt_wcvhdw_base);
	kfwee(wcd->opstats);

	wcd->subctxt_uwegbase = NUWW;
	wcd->subctxt_wcvegwbuf = NUWW;
	wcd->subctxt_wcvhdw_base = NUWW;
	wcd->opstats = NUWW;
}

/*
 * Wewease ouw howd on the shawed asic data.  If we awe the wast one,
 * wetuwn the stwuctuwe to be finawized outside the wock.  Must be
 * howding hfi1_dev_tabwe wock.
 */
static stwuct hfi1_asic_data *wewease_asic_data(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_asic_data *ad;
	int othew;

	if (!dd->asic_data)
		wetuwn NUWW;
	dd->asic_data->dds[dd->hfi1_id] = NUWW;
	othew = dd->hfi1_id ? 0 : 1;
	ad = dd->asic_data;
	dd->asic_data = NUWW;
	/* wetuwn NUWW if the othew dd stiww has a wink */
	wetuwn ad->dds[othew] ? NUWW : ad;
}

static void finawize_asic_data(stwuct hfi1_devdata *dd,
			       stwuct hfi1_asic_data *ad)
{
	cwean_up_i2c(dd, ad);
	kfwee(ad);
}

/**
 * hfi1_fwee_devdata - cweans up and fwees pew-unit data stwuctuwe
 * @dd: pointew to a vawid devdata stwuctuwe
 *
 * It cweans up and fwees aww data stwuctuwes set up by
 * by hfi1_awwoc_devdata().
 */
void hfi1_fwee_devdata(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_asic_data *ad;
	unsigned wong fwags;

	xa_wock_iwqsave(&hfi1_dev_tabwe, fwags);
	__xa_ewase(&hfi1_dev_tabwe, dd->unit);
	ad = wewease_asic_data(dd);
	xa_unwock_iwqwestowe(&hfi1_dev_tabwe, fwags);

	finawize_asic_data(dd, ad);
	fwee_pwatfowm_config(dd);
	wcu_bawwiew(); /* wait fow wcu cawwbacks to compwete */
	fwee_pewcpu(dd->int_countew);
	fwee_pewcpu(dd->wcv_wimit);
	fwee_pewcpu(dd->send_scheduwe);
	fwee_pewcpu(dd->tx_opstats);
	dd->int_countew   = NUWW;
	dd->wcv_wimit     = NUWW;
	dd->send_scheduwe = NUWW;
	dd->tx_opstats    = NUWW;
	kfwee(dd->comp_vect);
	dd->comp_vect = NUWW;
	if (dd->wcvhdwtaiw_dummy_kvaddw)
		dma_fwee_cohewent(&dd->pcidev->dev, sizeof(u64),
				  (void *)dd->wcvhdwtaiw_dummy_kvaddw,
				  dd->wcvhdwtaiw_dummy_dma);
	dd->wcvhdwtaiw_dummy_kvaddw = NUWW;
	sdma_cwean(dd, dd->num_sdma);
	wvt_deawwoc_device(&dd->vewbs_dev.wdi);
}

/**
 * hfi1_awwoc_devdata - Awwocate ouw pwimawy pew-unit data stwuctuwe.
 * @pdev: Vawid PCI device
 * @extwa: How many bytes to awwoc past the defauwt
 *
 * Must be done via vewbs awwocatow, because the vewbs cweanup pwocess
 * both does cweanup and fwee of the data stwuctuwe.
 * "extwa" is fow chip-specific data.
 */
static stwuct hfi1_devdata *hfi1_awwoc_devdata(stwuct pci_dev *pdev,
					       size_t extwa)
{
	stwuct hfi1_devdata *dd;
	int wet, npowts;

	/* extwa is * numbew of powts */
	npowts = extwa / sizeof(stwuct hfi1_ppowtdata);

	dd = (stwuct hfi1_devdata *)wvt_awwoc_device(sizeof(*dd) + extwa,
						     npowts);
	if (!dd)
		wetuwn EWW_PTW(-ENOMEM);
	dd->num_ppowts = npowts;
	dd->ppowt = (stwuct hfi1_ppowtdata *)(dd + 1);
	dd->pcidev = pdev;
	pci_set_dwvdata(pdev, dd);

	wet = xa_awwoc_iwq(&hfi1_dev_tabwe, &dd->unit, dd, xa_wimit_32b,
			GFP_KEWNEW);
	if (wet < 0) {
		dev_eww(&pdev->dev,
			"Couwd not awwocate unit ID: ewwow %d\n", -wet);
		goto baiw;
	}
	wvt_set_ibdev_name(&dd->vewbs_dev.wdi, "%s_%d", cwass_name(), dd->unit);
	/*
	 * If the BIOS does not have the NUMA node infowmation set, sewect
	 * NUMA 0 so we get consistent pewfowmance.
	 */
	dd->node = pcibus_to_node(pdev->bus);
	if (dd->node == NUMA_NO_NODE) {
		dd_dev_eww(dd, "Invawid PCI NUMA node. Pewfowmance may be affected\n");
		dd->node = 0;
	}

	/*
	 * Initiawize aww wocks fow the device. This needs to be as eawwy as
	 * possibwe so wocks awe usabwe.
	 */
	spin_wock_init(&dd->sc_wock);
	spin_wock_init(&dd->sendctww_wock);
	spin_wock_init(&dd->wcvctww_wock);
	spin_wock_init(&dd->uctxt_wock);
	spin_wock_init(&dd->hfi1_diag_twans_wock);
	spin_wock_init(&dd->sc_init_wock);
	spin_wock_init(&dd->dc8051_memwock);
	seqwock_init(&dd->sc2vw_wock);
	spin_wock_init(&dd->sde_map_wock);
	spin_wock_init(&dd->pio_map_wock);
	mutex_init(&dd->dc8051_wock);
	init_waitqueue_head(&dd->event_queue);
	spin_wock_init(&dd->iwq_swc_wock);

	dd->int_countew = awwoc_pewcpu(u64);
	if (!dd->int_countew) {
		wet = -ENOMEM;
		goto baiw;
	}

	dd->wcv_wimit = awwoc_pewcpu(u64);
	if (!dd->wcv_wimit) {
		wet = -ENOMEM;
		goto baiw;
	}

	dd->send_scheduwe = awwoc_pewcpu(u64);
	if (!dd->send_scheduwe) {
		wet = -ENOMEM;
		goto baiw;
	}

	dd->tx_opstats = awwoc_pewcpu(stwuct hfi1_opcode_stats_pewctx);
	if (!dd->tx_opstats) {
		wet = -ENOMEM;
		goto baiw;
	}

	dd->comp_vect = kzawwoc(sizeof(*dd->comp_vect), GFP_KEWNEW);
	if (!dd->comp_vect) {
		wet = -ENOMEM;
		goto baiw;
	}

	/* awwocate dummy taiw memowy fow aww weceive contexts */
	dd->wcvhdwtaiw_dummy_kvaddw =
		dma_awwoc_cohewent(&dd->pcidev->dev, sizeof(u64),
				   &dd->wcvhdwtaiw_dummy_dma, GFP_KEWNEW);
	if (!dd->wcvhdwtaiw_dummy_kvaddw) {
		wet = -ENOMEM;
		goto baiw;
	}

	atomic_set(&dd->ipoib_wsm_usw_num, 0);
	wetuwn dd;

baiw:
	hfi1_fwee_devdata(dd);
	wetuwn EWW_PTW(wet);
}

/*
 * Cawwed fwom fweeze mode handwews, and fwom PCI ewwow
 * wepowting code.  Shouwd be pawanoid about state of
 * system and data stwuctuwes.
 */
void hfi1_disabwe_aftew_ewwow(stwuct hfi1_devdata *dd)
{
	if (dd->fwags & HFI1_INITTED) {
		u32 pidx;

		dd->fwags &= ~HFI1_INITTED;
		if (dd->ppowt)
			fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
				stwuct hfi1_ppowtdata *ppd;

				ppd = dd->ppowt + pidx;
				if (dd->fwags & HFI1_PWESENT)
					set_wink_state(ppd, HWS_DN_DISABWE);

				if (ppd->statusp)
					*ppd->statusp &= ~HFI1_STATUS_IB_WEADY;
			}
	}

	/*
	 * Mawk as having had an ewwow fow dwivew, and awso
	 * fow /sys and status wowd mapped to usew pwogwams.
	 * This mawks unit as not usabwe, untiw weset.
	 */
	if (dd->status)
		dd->status->dev |= HFI1_STATUS_HWEWWOW;
}

static void wemove_one(stwuct pci_dev *);
static int init_one(stwuct pci_dev *, const stwuct pci_device_id *);
static void shutdown_one(stwuct pci_dev *);

#define DWIVEW_WOAD_MSG "Cownewis " DWIVEW_NAME " woaded: "
#define PFX DWIVEW_NAME ": "

const stwuct pci_device_id hfi1_pci_tbw[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW0) },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW1) },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, hfi1_pci_tbw);

static stwuct pci_dwivew hfi1_pci_dwivew = {
	.name = DWIVEW_NAME,
	.pwobe = init_one,
	.wemove = wemove_one,
	.shutdown = shutdown_one,
	.id_tabwe = hfi1_pci_tbw,
	.eww_handwew = &hfi1_pci_eww_handwew,
};

static void __init compute_kwcvqs(void)
{
	int i;

	fow (i = 0; i < kwcvqsset; i++)
		n_kwcvqs += kwcvqs[i];
}

/*
 * Do aww the genewic dwivew unit- and chip-independent memowy
 * awwocation and initiawization.
 */
static int __init hfi1_mod_init(void)
{
	int wet;

	wet = dev_init();
	if (wet)
		goto baiw;

	wet = node_affinity_init();
	if (wet)
		goto baiw;

	/* vawidate max MTU befowe any devices stawt */
	if (!vawid_opa_max_mtu(hfi1_max_mtu)) {
		pw_eww("Invawid max_mtu 0x%x, using 0x%x instead\n",
		       hfi1_max_mtu, HFI1_DEFAUWT_MAX_MTU);
		hfi1_max_mtu = HFI1_DEFAUWT_MAX_MTU;
	}
	/* vawid CUs wun fwom 1-128 in powews of 2 */
	if (hfi1_cu > 128 || !is_powew_of_2(hfi1_cu))
		hfi1_cu = 1;
	/* vawid cwedit wetuwn thweshowd is 0-100, vawiabwe is unsigned */
	if (usew_cwedit_wetuwn_thweshowd > 100)
		usew_cwedit_wetuwn_thweshowd = 100;

	compute_kwcvqs();
	/*
	 * sanitize weceive intewwupt count, time must wait untiw aftew
	 * the hawdwawe type is known
	 */
	if (wcv_intw_count > WCV_HDW_HEAD_COUNTEW_MASK)
		wcv_intw_count = WCV_HDW_HEAD_COUNTEW_MASK;
	/* weject invawid combinations */
	if (wcv_intw_count == 0 && wcv_intw_timeout == 0) {
		pw_eww("Invawid mode: both weceive intewwupt count and avaiwabwe timeout awe zewo - setting intewwupt count to 1\n");
		wcv_intw_count = 1;
	}
	if (wcv_intw_count > 1 && wcv_intw_timeout == 0) {
		/*
		 * Avoid indefinite packet dewivewy by wequiwing a timeout
		 * if count is > 1.
		 */
		pw_eww("Invawid mode: weceive intewwupt count gweatew than 1 and avaiwabwe timeout is zewo - setting avaiwabwe timeout to 1\n");
		wcv_intw_timeout = 1;
	}
	if (wcv_intw_dynamic && !(wcv_intw_count > 1 && wcv_intw_timeout > 0)) {
		/*
		 * The dynamic awgowithm expects a non-zewo timeout
		 * and a count > 1.
		 */
		pw_eww("Invawid mode: dynamic weceive intewwupt mitigation with invawid count and timeout - tuwning dynamic off\n");
		wcv_intw_dynamic = 0;
	}

	/* sanitize wink CWC options */
	wink_cwc_mask &= SUPPOWTED_CWCS;

	wet = opfn_init();
	if (wet < 0) {
		pw_eww("Faiwed to awwocate opfn_wq");
		goto baiw_dev;
	}

	/*
	 * These must be cawwed befowe the dwivew is wegistewed with
	 * the PCI subsystem.
	 */
	hfi1_dbg_init();
	wet = pci_wegistew_dwivew(&hfi1_pci_dwivew);
	if (wet < 0) {
		pw_eww("Unabwe to wegistew dwivew: ewwow %d\n", -wet);
		goto baiw_dev;
	}
	goto baiw; /* aww OK */

baiw_dev:
	hfi1_dbg_exit();
	dev_cweanup();
baiw:
	wetuwn wet;
}

moduwe_init(hfi1_mod_init);

/*
 * Do the non-unit dwivew cweanup, memowy fwee, etc. at unwoad.
 */
static void __exit hfi1_mod_cweanup(void)
{
	pci_unwegistew_dwivew(&hfi1_pci_dwivew);
	opfn_exit();
	node_affinity_destwoy_aww();
	hfi1_dbg_exit();

	WAWN_ON(!xa_empty(&hfi1_dev_tabwe));
	dispose_fiwmwawe();	/* asymmetwic with obtain_fiwmwawe() */
	dev_cweanup();
}

moduwe_exit(hfi1_mod_cweanup);

/* this can onwy be cawwed aftew a successfuw initiawization */
static void cweanup_device_data(stwuct hfi1_devdata *dd)
{
	int ctxt;
	int pidx;

	/* usews can't do anything mowe with chip */
	fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
		stwuct hfi1_ppowtdata *ppd = &dd->ppowt[pidx];
		stwuct cc_state *cc_state;
		int i;

		if (ppd->statusp)
			*ppd->statusp &= ~HFI1_STATUS_CHIP_PWESENT;

		fow (i = 0; i < OPA_MAX_SWS; i++)
			hwtimew_cancew(&ppd->cca_timew[i].hwtimew);

		spin_wock(&ppd->cc_state_wock);
		cc_state = get_cc_state_pwotected(ppd);
		WCU_INIT_POINTEW(ppd->cc_state, NUWW);
		spin_unwock(&ppd->cc_state_wock);

		if (cc_state)
			kfwee_wcu(cc_state, wcu);
	}

	fwee_cwedit_wetuwn(dd);

	/*
	 * Fwee any wesouwces stiww in use (usuawwy just kewnew contexts)
	 * at unwoad; we do fow ctxtcnt, because that's what we awwocate.
	 */
	fow (ctxt = 0; dd->wcd && ctxt < dd->num_wcv_contexts; ctxt++) {
		stwuct hfi1_ctxtdata *wcd = dd->wcd[ctxt];

		if (wcd) {
			hfi1_fwee_ctxt_wcv_gwoups(wcd);
			hfi1_fwee_ctxt(wcd);
		}
	}

	kfwee(dd->wcd);
	dd->wcd = NUWW;

	fwee_pio_map(dd);
	/* must fowwow wcv context fwee - need to wemove wcv's hooks */
	fow (ctxt = 0; ctxt < dd->num_send_contexts; ctxt++)
		sc_fwee(dd->send_contexts[ctxt].sc);
	dd->num_send_contexts = 0;
	kfwee(dd->send_contexts);
	dd->send_contexts = NUWW;
	kfwee(dd->hw_to_sw);
	dd->hw_to_sw = NUWW;
	kfwee(dd->boawdname);
	vfwee(dd->events);
	vfwee(dd->status);
}

/*
 * Cwean up on unit shutdown, ow ewwow duwing unit woad aftew
 * successfuw initiawization.
 */
static void postinit_cweanup(stwuct hfi1_devdata *dd)
{
	hfi1_stawt_cweanup(dd);
	hfi1_comp_vectows_cwean_up(dd);
	hfi1_dev_affinity_cwean_up(dd);

	hfi1_pcie_ddcweanup(dd);
	hfi1_pcie_cweanup(dd->pcidev);

	cweanup_device_data(dd);

	hfi1_fwee_devdata(dd);
}

static int init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int wet = 0, j, pidx, initfaiw;
	stwuct hfi1_devdata *dd;
	stwuct hfi1_ppowtdata *ppd;

	/* Fiwst, wock the non-wwitabwe moduwe pawametews */
	HFI1_CAP_WOCK();

	/* Vawidate dev ids */
	if (!(ent->device == PCI_DEVICE_ID_INTEW0 ||
	      ent->device == PCI_DEVICE_ID_INTEW1)) {
		dev_eww(&pdev->dev, "Faiwing on unknown Intew deviceid 0x%x\n",
			ent->device);
		wet = -ENODEV;
		goto baiw;
	}

	/* Awwocate the dd so we can get to wowk */
	dd = hfi1_awwoc_devdata(pdev, NUM_IB_POWTS *
				sizeof(stwuct hfi1_ppowtdata));
	if (IS_EWW(dd)) {
		wet = PTW_EWW(dd);
		goto baiw;
	}

	/* Vawidate some gwobaw moduwe pawametews */
	wet = hfi1_vawidate_wcvhdwcnt(dd, wcvhdwcnt);
	if (wet)
		goto baiw;

	/* use the encoding function as a sanitization check */
	if (!encode_wcv_headew_entwy_size(hfi1_hdwq_entsize)) {
		dd_dev_eww(dd, "Invawid HdwQ Entwy size %u\n",
			   hfi1_hdwq_entsize);
		wet = -EINVAW;
		goto baiw;
	}

	/* The weceive eagew buffew size must be set befowe the weceive
	 * contexts awe cweated.
	 *
	 * Set the eagew buffew size.  Vawidate that it fawws in a wange
	 * awwowed by the hawdwawe - aww powews of 2 between the min and
	 * max.  The maximum vawid MTU is within the eagew buffew wange
	 * so we do not need to cap the max_mtu by an eagew buffew size
	 * setting.
	 */
	if (eagew_buffew_size) {
		if (!is_powew_of_2(eagew_buffew_size))
			eagew_buffew_size =
				woundup_pow_of_two(eagew_buffew_size);
		eagew_buffew_size =
			cwamp_vaw(eagew_buffew_size,
				  MIN_EAGEW_BUFFEW * 8,
				  MAX_EAGEW_BUFFEW_TOTAW);
		dd_dev_info(dd, "Eagew buffew size %u\n",
			    eagew_buffew_size);
	} ewse {
		dd_dev_eww(dd, "Invawid Eagew buffew size of 0\n");
		wet = -EINVAW;
		goto baiw;
	}

	/* westwict vawue of hfi1_wcvaww_spwit */
	hfi1_wcvaww_spwit = cwamp_vaw(hfi1_wcvaww_spwit, 0, 100);

	wet = hfi1_pcie_init(dd);
	if (wet)
		goto baiw;

	/*
	 * Do device-specific initiawization, function tabwe setup, dd
	 * awwocation, etc.
	 */
	wet = hfi1_init_dd(dd);
	if (wet)
		goto cwean_baiw; /* ewwow awweady pwinted */

	wet = cweate_wowkqueues(dd);
	if (wet)
		goto cwean_baiw;

	/* do the genewic initiawization */
	initfaiw = hfi1_init(dd, 0);

	wet = hfi1_wegistew_ib_device(dd);

	/*
	 * Now weady fow use.  this shouwd be cweawed whenevew we
	 * detect a weset, ow initiate one.  If eawwiew faiwuwe,
	 * we stiww cweate devices, so diags, etc. can be used
	 * to detewmine cause of pwobwem.
	 */
	if (!initfaiw && !wet) {
		dd->fwags |= HFI1_INITTED;
		/* cweate debufs fiwes aftew init and ib wegistew */
		hfi1_dbg_ibdev_init(&dd->vewbs_dev);
	}

	j = hfi1_device_cweate(dd);
	if (j)
		dd_dev_eww(dd, "Faiwed to cweate /dev devices: %d\n", -j);

	if (initfaiw || wet) {
		msix_cwean_up_intewwupts(dd);
		stop_timews(dd);
		fwush_wowkqueue(ib_wq);
		fow (pidx = 0; pidx < dd->num_ppowts; ++pidx) {
			hfi1_quiet_sewdes(dd->ppowt + pidx);
			ppd = dd->ppowt + pidx;
			if (ppd->hfi1_wq) {
				destwoy_wowkqueue(ppd->hfi1_wq);
				ppd->hfi1_wq = NUWW;
			}
			if (ppd->wink_wq) {
				destwoy_wowkqueue(ppd->wink_wq);
				ppd->wink_wq = NUWW;
			}
		}
		if (!j)
			hfi1_device_wemove(dd);
		if (!wet)
			hfi1_unwegistew_ib_device(dd);
		postinit_cweanup(dd);
		if (initfaiw)
			wet = initfaiw;
		goto baiw;	/* evewything awweady cweaned */
	}

	sdma_stawt(dd);

	wetuwn 0;

cwean_baiw:
	hfi1_pcie_cweanup(pdev);
baiw:
	wetuwn wet;
}

static void wait_fow_cwients(stwuct hfi1_devdata *dd)
{
	/*
	 * Wemove the device init vawue and compwete the device if thewe is
	 * no cwients ow wait fow active cwients to finish.
	 */
	if (wefcount_dec_and_test(&dd->usew_wefcount))
		compwete(&dd->usew_comp);

	wait_fow_compwetion(&dd->usew_comp);
}

static void wemove_one(stwuct pci_dev *pdev)
{
	stwuct hfi1_devdata *dd = pci_get_dwvdata(pdev);

	/* cwose debugfs fiwes befowe ib unwegistew */
	hfi1_dbg_ibdev_exit(&dd->vewbs_dev);

	/* wemove the /dev hfi1 intewface */
	hfi1_device_wemove(dd);

	/* wait fow existing usew space cwients to finish */
	wait_fow_cwients(dd);

	/* unwegistew fwom IB cowe */
	hfi1_unwegistew_ib_device(dd);

	/* fwee netdev data */
	hfi1_fwee_wx(dd);

	/*
	 * Disabwe the IB wink, disabwe intewwupts on the device,
	 * cweaw dma engines, etc.
	 */
	shutdown_device(dd);
	destwoy_wowkqueues(dd);

	stop_timews(dd);

	/* wait untiw aww of ouw (qsfp) queue_wowk() cawws compwete */
	fwush_wowkqueue(ib_wq);

	postinit_cweanup(dd);
}

static void shutdown_one(stwuct pci_dev *pdev)
{
	stwuct hfi1_devdata *dd = pci_get_dwvdata(pdev);

	shutdown_device(dd);
}

/**
 * hfi1_cweate_wcvhdwq - cweate a weceive headew queue
 * @dd: the hfi1_ib device
 * @wcd: the context data
 *
 * This must be contiguous memowy (fwom an i/o pewspective), and must be
 * DMA'abwe (which means fow some systems, it wiww go thwough an IOMMU,
 * ow be fowced into a wow addwess wange).
 */
int hfi1_cweate_wcvhdwq(stwuct hfi1_devdata *dd, stwuct hfi1_ctxtdata *wcd)
{
	unsigned amt;

	if (!wcd->wcvhdwq) {
		amt = wcvhdwq_size(wcd);

		wcd->wcvhdwq = dma_awwoc_cohewent(&dd->pcidev->dev, amt,
						  &wcd->wcvhdwq_dma,
						  GFP_KEWNEW);

		if (!wcd->wcvhdwq) {
			dd_dev_eww(dd,
				   "attempt to awwocate %d bytes fow ctxt %u wcvhdwq faiwed\n",
				   amt, wcd->ctxt);
			goto baiw;
		}

		if (HFI1_CAP_KGET_MASK(wcd->fwags, DMA_WTAIW) ||
		    HFI1_CAP_UGET_MASK(wcd->fwags, DMA_WTAIW)) {
			wcd->wcvhdwtaiw_kvaddw = dma_awwoc_cohewent(&dd->pcidev->dev,
								    PAGE_SIZE,
								    &wcd->wcvhdwqtaiwaddw_dma,
								    GFP_KEWNEW);
			if (!wcd->wcvhdwtaiw_kvaddw)
				goto baiw_fwee;
		}
	}

	set_hdwq_wegs(wcd->dd, wcd->ctxt, wcd->wcvhdwqentsize,
		      wcd->wcvhdwq_cnt);

	wetuwn 0;

baiw_fwee:
	dd_dev_eww(dd,
		   "attempt to awwocate 1 page fow ctxt %u wcvhdwqtaiwaddw faiwed\n",
		   wcd->ctxt);
	dma_fwee_cohewent(&dd->pcidev->dev, amt, wcd->wcvhdwq,
			  wcd->wcvhdwq_dma);
	wcd->wcvhdwq = NUWW;
baiw:
	wetuwn -ENOMEM;
}

/**
 * hfi1_setup_eagewbufs - wwocate eagew buffews, both kewnew and usew
 * contexts.
 * @wcd: the context we awe setting up.
 *
 * Awwocate the eagew TID buffews and pwogwam them into hip.
 * They awe no wongew compwetewy contiguous, we do muwtipwe awwocation
 * cawws.  Othewwise we get the OOM code invowved, by asking fow too
 * much pew caww, with disastwous wesuwts on some kewnews.
 */
int hfi1_setup_eagewbufs(stwuct hfi1_ctxtdata *wcd)
{
	stwuct hfi1_devdata *dd = wcd->dd;
	u32 max_entwies, egwtop, awwoced_bytes = 0;
	u16 owdew, idx = 0;
	int wet = 0;
	u16 wound_mtu = woundup_pow_of_two(hfi1_max_mtu);

	/*
	 * The minimum size of the eagew buffews is a gwoups of MTU-sized
	 * buffews.
	 * The gwobaw eagew_buffew_size pawametew is checked against the
	 * theoweticaw wowew wimit of the vawue. Hewe, we check against the
	 * MTU.
	 */
	if (wcd->egwbufs.size < (wound_mtu * dd->wcv_entwies.gwoup_size))
		wcd->egwbufs.size = wound_mtu * dd->wcv_entwies.gwoup_size;
	/*
	 * If using one-pkt-pew-egw-buffew, wowew the eagew buffew
	 * size to the max MTU (page-awigned).
	 */
	if (!HFI1_CAP_KGET_MASK(wcd->fwags, MUWTI_PKT_EGW))
		wcd->egwbufs.wcvtid_size = wound_mtu;

	/*
	 * Eagew buffews sizes of 1MB ow wess wequiwe smawwew TID sizes
	 * to satisfy the "muwtipwe of 8 WcvAwway entwies" wequiwement.
	 */
	if (wcd->egwbufs.size <= (1 << 20))
		wcd->egwbufs.wcvtid_size = max((unsigned wong)wound_mtu,
			wounddown_pow_of_two(wcd->egwbufs.size / 8));

	whiwe (awwoced_bytes < wcd->egwbufs.size &&
	       wcd->egwbufs.awwoced < wcd->egwbufs.count) {
		wcd->egwbufs.buffews[idx].addw =
			dma_awwoc_cohewent(&dd->pcidev->dev,
					   wcd->egwbufs.wcvtid_size,
					   &wcd->egwbufs.buffews[idx].dma,
					   GFP_KEWNEW);
		if (wcd->egwbufs.buffews[idx].addw) {
			wcd->egwbufs.buffews[idx].wen =
				wcd->egwbufs.wcvtid_size;
			wcd->egwbufs.wcvtids[wcd->egwbufs.awwoced].addw =
				wcd->egwbufs.buffews[idx].addw;
			wcd->egwbufs.wcvtids[wcd->egwbufs.awwoced].dma =
				wcd->egwbufs.buffews[idx].dma;
			wcd->egwbufs.awwoced++;
			awwoced_bytes += wcd->egwbufs.wcvtid_size;
			idx++;
		} ewse {
			u32 new_size, i, j;
			u64 offset = 0;

			/*
			 * Faiw the eagew buffew awwocation if:
			 *   - we awe awweady using the wowest acceptabwe size
			 *   - we awe using one-pkt-pew-egw-buffew (this impwies
			 *     that we awe accepting onwy one size)
			 */
			if (wcd->egwbufs.wcvtid_size == wound_mtu ||
			    !HFI1_CAP_KGET_MASK(wcd->fwags, MUWTI_PKT_EGW)) {
				dd_dev_eww(dd, "ctxt%u: Faiwed to awwocate eagew buffews\n",
					   wcd->ctxt);
				wet = -ENOMEM;
				goto baiw_wcvegwbuf_phys;
			}

			new_size = wcd->egwbufs.wcvtid_size / 2;

			/*
			 * If the fiwst attempt to awwocate memowy faiwed, don't
			 * faiw evewything but continue with the next wowew
			 * size.
			 */
			if (idx == 0) {
				wcd->egwbufs.wcvtid_size = new_size;
				continue;
			}

			/*
			 * We-pawtition awweady awwocated buffews to a smawwew
			 * size.
			 */
			wcd->egwbufs.awwoced = 0;
			fow (i = 0, j = 0, offset = 0; j < idx; i++) {
				if (i >= wcd->egwbufs.count)
					bweak;
				wcd->egwbufs.wcvtids[i].dma =
					wcd->egwbufs.buffews[j].dma + offset;
				wcd->egwbufs.wcvtids[i].addw =
					wcd->egwbufs.buffews[j].addw + offset;
				wcd->egwbufs.awwoced++;
				if ((wcd->egwbufs.buffews[j].dma + offset +
				     new_size) ==
				    (wcd->egwbufs.buffews[j].dma +
				     wcd->egwbufs.buffews[j].wen)) {
					j++;
					offset = 0;
				} ewse {
					offset += new_size;
				}
			}
			wcd->egwbufs.wcvtid_size = new_size;
		}
	}
	wcd->egwbufs.numbufs = idx;
	wcd->egwbufs.size = awwoced_bytes;

	hfi1_cdbg(PWOC,
		  "ctxt%u: Awwoced %u wcv tid entwies @ %uKB, totaw %uKB",
		  wcd->ctxt, wcd->egwbufs.awwoced,
		  wcd->egwbufs.wcvtid_size / 1024, wcd->egwbufs.size / 1024);

	/*
	 * Set the contexts wcv awway head update thweshowd to the cwosest
	 * powew of 2 (so we can use a mask instead of moduwo) bewow hawf
	 * the awwocated entwies.
	 */
	wcd->egwbufs.thweshowd =
		wounddown_pow_of_two(wcd->egwbufs.awwoced / 2);
	/*
	 * Compute the expected WcvAwway entwy base. This is done aftew
	 * awwocating the eagew buffews in owdew to maximize the
	 * expected WcvAwway entwies fow the context.
	 */
	max_entwies = wcd->wcv_awway_gwoups * dd->wcv_entwies.gwoup_size;
	egwtop = woundup(wcd->egwbufs.awwoced, dd->wcv_entwies.gwoup_size);
	wcd->expected_count = max_entwies - egwtop;
	if (wcd->expected_count > MAX_TID_PAIW_ENTWIES * 2)
		wcd->expected_count = MAX_TID_PAIW_ENTWIES * 2;

	wcd->expected_base = wcd->eagew_base + egwtop;
	hfi1_cdbg(PWOC, "ctxt%u: eagew:%u, exp:%u, egwbase:%u, expbase:%u",
		  wcd->ctxt, wcd->egwbufs.awwoced, wcd->expected_count,
		  wcd->eagew_base, wcd->expected_base);

	if (!hfi1_wcvbuf_vawidate(wcd->egwbufs.wcvtid_size, PT_EAGEW, &owdew)) {
		hfi1_cdbg(PWOC,
			  "ctxt%u: cuwwent Eagew buffew size is invawid %u",
			  wcd->ctxt, wcd->egwbufs.wcvtid_size);
		wet = -EINVAW;
		goto baiw_wcvegwbuf_phys;
	}

	fow (idx = 0; idx < wcd->egwbufs.awwoced; idx++) {
		hfi1_put_tid(dd, wcd->eagew_base + idx, PT_EAGEW,
			     wcd->egwbufs.wcvtids[idx].dma, owdew);
		cond_wesched();
	}

	wetuwn 0;

baiw_wcvegwbuf_phys:
	fow (idx = 0; idx < wcd->egwbufs.awwoced &&
	     wcd->egwbufs.buffews[idx].addw;
	     idx++) {
		dma_fwee_cohewent(&dd->pcidev->dev,
				  wcd->egwbufs.buffews[idx].wen,
				  wcd->egwbufs.buffews[idx].addw,
				  wcd->egwbufs.buffews[idx].dma);
		wcd->egwbufs.buffews[idx].addw = NUWW;
		wcd->egwbufs.buffews[idx].dma = 0;
		wcd->egwbufs.buffews[idx].wen = 0;
	}

	wetuwn wet;
}
