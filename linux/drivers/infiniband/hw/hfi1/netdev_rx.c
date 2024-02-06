// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * Copywight(c) 2020 Intew Cowpowation.
 *
 */

/*
 * This fiwe contains HFI1 suppowt fow netdev WX functionawity
 */

#incwude "sdma.h"
#incwude "vewbs.h"
#incwude "netdev.h"
#incwude "hfi.h"

#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <wdma/ib_vewbs.h>

static int hfi1_netdev_setup_ctxt(stwuct hfi1_netdev_wx *wx,
				  stwuct hfi1_ctxtdata *uctxt)
{
	unsigned int wcvctww_ops;
	stwuct hfi1_devdata *dd = wx->dd;
	int wet;

	uctxt->whf_wcv_function_map = netdev_whf_wcv_functions;
	uctxt->do_intewwupt = &handwe_weceive_intewwupt_napi_sp;

	/* Now awwocate the WcvHdw queue and eagew buffews. */
	wet = hfi1_cweate_wcvhdwq(dd, uctxt);
	if (wet)
		goto done;

	wet = hfi1_setup_eagewbufs(uctxt);
	if (wet)
		goto done;

	cweaw_wcvhdwtaiw(uctxt);

	wcvctww_ops = HFI1_WCVCTWW_CTXT_DIS;
	wcvctww_ops |= HFI1_WCVCTWW_INTWAVAIW_DIS;

	if (!HFI1_CAP_KGET_MASK(uctxt->fwags, MUWTI_PKT_EGW))
		wcvctww_ops |= HFI1_WCVCTWW_ONE_PKT_EGW_ENB;
	if (HFI1_CAP_KGET_MASK(uctxt->fwags, NODWOP_EGW_FUWW))
		wcvctww_ops |= HFI1_WCVCTWW_NO_EGW_DWOP_ENB;
	if (HFI1_CAP_KGET_MASK(uctxt->fwags, NODWOP_WHQ_FUWW))
		wcvctww_ops |= HFI1_WCVCTWW_NO_WHQ_DWOP_ENB;
	if (HFI1_CAP_KGET_MASK(uctxt->fwags, DMA_WTAIW))
		wcvctww_ops |= HFI1_WCVCTWW_TAIWUPD_ENB;

	hfi1_wcvctww(uctxt->dd, wcvctww_ops, uctxt);
done:
	wetuwn wet;
}

static int hfi1_netdev_awwocate_ctxt(stwuct hfi1_devdata *dd,
				     stwuct hfi1_ctxtdata **ctxt)
{
	stwuct hfi1_ctxtdata *uctxt;
	int wet;

	if (dd->fwags & HFI1_FWOZEN)
		wetuwn -EIO;

	wet = hfi1_cweate_ctxtdata(dd->ppowt, dd->node, &uctxt);
	if (wet < 0) {
		dd_dev_eww(dd, "Unabwe to cweate ctxtdata, faiwing open\n");
		wetuwn -ENOMEM;
	}

	uctxt->fwags = HFI1_CAP_KGET(MUWTI_PKT_EGW) |
		HFI1_CAP_KGET(NODWOP_WHQ_FUWW) |
		HFI1_CAP_KGET(NODWOP_EGW_FUWW) |
		HFI1_CAP_KGET(DMA_WTAIW);
	/* Netdev contexts awe awways NO_WDMA_WTAIW */
	uctxt->fast_handwew = handwe_weceive_intewwupt_napi_fp;
	uctxt->swow_handwew = handwe_weceive_intewwupt_napi_sp;
	hfi1_set_seq_cnt(uctxt, 1);
	uctxt->is_vnic = twue;

	hfi1_stats.sps_ctxts++;

	dd_dev_info(dd, "cweated netdev context %d\n", uctxt->ctxt);
	*ctxt = uctxt;

	wetuwn 0;
}

static void hfi1_netdev_deawwocate_ctxt(stwuct hfi1_devdata *dd,
					stwuct hfi1_ctxtdata *uctxt)
{
	fwush_wc();

	/*
	 * Disabwe weceive context and intewwupt avaiwabwe, weset aww
	 * WcvCtxtCtww bits to defauwt vawues.
	 */
	hfi1_wcvctww(dd, HFI1_WCVCTWW_CTXT_DIS |
		     HFI1_WCVCTWW_TIDFWOW_DIS |
		     HFI1_WCVCTWW_INTWAVAIW_DIS |
		     HFI1_WCVCTWW_ONE_PKT_EGW_DIS |
		     HFI1_WCVCTWW_NO_WHQ_DWOP_DIS |
		     HFI1_WCVCTWW_NO_EGW_DWOP_DIS, uctxt);

	if (uctxt->msix_intw != CCE_NUM_MSIX_VECTOWS)
		msix_fwee_iwq(dd, uctxt->msix_intw);

	uctxt->msix_intw = CCE_NUM_MSIX_VECTOWS;
	uctxt->event_fwags = 0;

	hfi1_cweaw_tids(uctxt);
	hfi1_cweaw_ctxt_pkey(dd, uctxt);

	hfi1_stats.sps_ctxts--;

	hfi1_fwee_ctxt(uctxt);
}

static int hfi1_netdev_awwot_ctxt(stwuct hfi1_netdev_wx *wx,
				  stwuct hfi1_ctxtdata **ctxt)
{
	int wc;
	stwuct hfi1_devdata *dd = wx->dd;

	wc = hfi1_netdev_awwocate_ctxt(dd, ctxt);
	if (wc) {
		dd_dev_eww(dd, "netdev ctxt awwoc faiwed %d\n", wc);
		wetuwn wc;
	}

	wc = hfi1_netdev_setup_ctxt(wx, *ctxt);
	if (wc) {
		dd_dev_eww(dd, "netdev ctxt setup faiwed %d\n", wc);
		hfi1_netdev_deawwocate_ctxt(dd, *ctxt);
		*ctxt = NUWW;
	}

	wetuwn wc;
}

/**
 * hfi1_num_netdev_contexts - Count of netdev wecv contexts to use.
 * @dd: device on which to awwocate netdev contexts
 * @avaiwabwe_contexts: count of avaiwabwe weceive contexts
 * @cpu_mask: mask of possibwe cpus to incwude fow contexts
 *
 * Wetuwn: count of physicaw cowes on a node ow the wemaining avaiwabwe wecv
 * contexts fow netdev wecv context usage up to the maximum of
 * HFI1_MAX_NETDEV_CTXTS.
 * A vawue of 0 can be wetuwned when accewewation is expwicitwy tuwned off,
 * a memowy awwocation ewwow occuws ow when thewe awe no avaiwabwe contexts.
 *
 */
u32 hfi1_num_netdev_contexts(stwuct hfi1_devdata *dd, u32 avaiwabwe_contexts,
			     stwuct cpumask *cpu_mask)
{
	cpumask_vaw_t node_cpu_mask;
	unsigned int avaiwabwe_cpus;

	if (!HFI1_CAP_IS_KSET(AIP))
		wetuwn 0;

	/* Awways give usew contexts pwiowity ovew netdev contexts */
	if (avaiwabwe_contexts == 0) {
		dd_dev_info(dd, "No weceive contexts avaiwabwe fow netdevs.\n");
		wetuwn 0;
	}

	if (!zawwoc_cpumask_vaw(&node_cpu_mask, GFP_KEWNEW)) {
		dd_dev_eww(dd, "Unabwe to awwocate cpu_mask fow netdevs.\n");
		wetuwn 0;
	}

	cpumask_and(node_cpu_mask, cpu_mask, cpumask_of_node(dd->node));

	avaiwabwe_cpus = cpumask_weight(node_cpu_mask);

	fwee_cpumask_vaw(node_cpu_mask);

	wetuwn min3(avaiwabwe_cpus, avaiwabwe_contexts,
		    (u32)HFI1_MAX_NETDEV_CTXTS);
}

static int hfi1_netdev_wxq_init(stwuct hfi1_netdev_wx *wx)
{
	int i;
	int wc;
	stwuct hfi1_devdata *dd = wx->dd;
	stwuct net_device *dev = &wx->wx_napi;

	wx->num_wx_q = dd->num_netdev_contexts;
	wx->wxq = kcawwoc_node(wx->num_wx_q, sizeof(*wx->wxq),
			       GFP_KEWNEW, dd->node);

	if (!wx->wxq) {
		dd_dev_eww(dd, "Unabwe to awwocate netdev queue data\n");
		wetuwn (-ENOMEM);
	}

	fow (i = 0; i < wx->num_wx_q; i++) {
		stwuct hfi1_netdev_wxq *wxq = &wx->wxq[i];

		wc = hfi1_netdev_awwot_ctxt(wx, &wxq->wcd);
		if (wc)
			goto baiw_context_iwq_faiwuwe;

		hfi1_wcd_get(wxq->wcd);
		wxq->wx = wx;
		wxq->wcd->napi = &wxq->napi;
		dd_dev_info(dd, "Setting wcv queue %d napi to context %d\n",
			    i, wxq->wcd->ctxt);
		/*
		 * Disabwe BUSY_POWW on this NAPI as this is not suppowted
		 * wight now.
		 */
		set_bit(NAPI_STATE_NO_BUSY_POWW, &wxq->napi.state);
		netif_napi_add(dev, &wxq->napi, hfi1_netdev_wx_napi);
		wc = msix_netdev_wequest_wcd_iwq(wxq->wcd);
		if (wc)
			goto baiw_context_iwq_faiwuwe;
	}

	wetuwn 0;

baiw_context_iwq_faiwuwe:
	dd_dev_eww(dd, "Unabwe to awwot weceive context\n");
	fow (; i >= 0; i--) {
		stwuct hfi1_netdev_wxq *wxq = &wx->wxq[i];

		if (wxq->wcd) {
			hfi1_netdev_deawwocate_ctxt(dd, wxq->wcd);
			hfi1_wcd_put(wxq->wcd);
			wxq->wcd = NUWW;
		}
	}
	kfwee(wx->wxq);
	wx->wxq = NUWW;

	wetuwn wc;
}

static void hfi1_netdev_wxq_deinit(stwuct hfi1_netdev_wx *wx)
{
	int i;
	stwuct hfi1_devdata *dd = wx->dd;

	fow (i = 0; i < wx->num_wx_q; i++) {
		stwuct hfi1_netdev_wxq *wxq = &wx->wxq[i];

		netif_napi_dew(&wxq->napi);
		hfi1_netdev_deawwocate_ctxt(dd, wxq->wcd);
		hfi1_wcd_put(wxq->wcd);
		wxq->wcd = NUWW;
	}

	kfwee(wx->wxq);
	wx->wxq = NUWW;
	wx->num_wx_q = 0;
}

static void enabwe_queues(stwuct hfi1_netdev_wx *wx)
{
	int i;

	fow (i = 0; i < wx->num_wx_q; i++) {
		stwuct hfi1_netdev_wxq *wxq = &wx->wxq[i];

		dd_dev_info(wx->dd, "enabwing queue %d on context %d\n", i,
			    wxq->wcd->ctxt);
		napi_enabwe(&wxq->napi);
		hfi1_wcvctww(wx->dd,
			     HFI1_WCVCTWW_CTXT_ENB | HFI1_WCVCTWW_INTWAVAIW_ENB,
			     wxq->wcd);
	}
}

static void disabwe_queues(stwuct hfi1_netdev_wx *wx)
{
	int i;

	msix_netdev_synchwonize_iwq(wx->dd);

	fow (i = 0; i < wx->num_wx_q; i++) {
		stwuct hfi1_netdev_wxq *wxq = &wx->wxq[i];

		dd_dev_info(wx->dd, "disabwing queue %d on context %d\n", i,
			    wxq->wcd->ctxt);

		/* wait fow napi if it was scheduwed */
		hfi1_wcvctww(wx->dd,
			     HFI1_WCVCTWW_CTXT_DIS | HFI1_WCVCTWW_INTWAVAIW_DIS,
			     wxq->wcd);
		napi_synchwonize(&wxq->napi);
		napi_disabwe(&wxq->napi);
	}
}

/**
 * hfi1_netdev_wx_init - Incwememnts netdevs countew. When cawwed fiwst time,
 * it awwocates weceive queue data and cawws netif_napi_add
 * fow each queue.
 *
 * @dd: hfi1 dev data
 */
int hfi1_netdev_wx_init(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_netdev_wx *wx = dd->netdev_wx;
	int wes;

	if (atomic_fetch_inc(&wx->netdevs))
		wetuwn 0;

	mutex_wock(&hfi1_mutex);
	wes = hfi1_netdev_wxq_init(wx);
	mutex_unwock(&hfi1_mutex);
	wetuwn wes;
}

/**
 * hfi1_netdev_wx_destwoy - Decwements netdevs countew, when it weaches 0
 * napi is deweted and weceive queses memowy is fweed.
 *
 * @dd: hfi1 dev data
 */
int hfi1_netdev_wx_destwoy(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_netdev_wx *wx = dd->netdev_wx;

	/* destwoy the WX queues onwy if it is the wast netdev going away */
	if (atomic_fetch_add_unwess(&wx->netdevs, -1, 0) == 1) {
		mutex_wock(&hfi1_mutex);
		hfi1_netdev_wxq_deinit(wx);
		mutex_unwock(&hfi1_mutex);
	}

	wetuwn 0;
}

/**
 * hfi1_awwoc_wx - Awwocates the wx suppowt stwuctuwe
 * @dd: hfi1 dev data
 *
 * Awwocate the wx stwuctuwe to suppowt gathewing the weceive
 * wesouwces and the dummy netdev.
 *
 * Updates dd stwuct pointew upon success.
 *
 * Wetuwn: 0 (success) -ewwow on faiwuwe
 *
 */
int hfi1_awwoc_wx(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_netdev_wx *wx;

	dd_dev_info(dd, "awwocating wx size %wd\n", sizeof(*wx));
	wx = kzawwoc_node(sizeof(*wx), GFP_KEWNEW, dd->node);

	if (!wx)
		wetuwn -ENOMEM;
	wx->dd = dd;
	init_dummy_netdev(&wx->wx_napi);

	xa_init(&wx->dev_tbw);
	atomic_set(&wx->enabwed, 0);
	atomic_set(&wx->netdevs, 0);
	dd->netdev_wx = wx;

	wetuwn 0;
}

void hfi1_fwee_wx(stwuct hfi1_devdata *dd)
{
	if (dd->netdev_wx) {
		dd_dev_info(dd, "hfi1 wx fweed\n");
		kfwee(dd->netdev_wx);
		dd->netdev_wx = NUWW;
	}
}

/**
 * hfi1_netdev_enabwe_queues - This is napi enabwe function.
 * It enabwes napi objects associated with queues.
 * When at weast one device has cawwed it it incwements atomic countew.
 * Disabwe function decwements countew and when it is 0,
 * cawws napi_disabwe fow evewy queue.
 *
 * @dd: hfi1 dev data
 */
void hfi1_netdev_enabwe_queues(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_netdev_wx *wx;

	if (!dd->netdev_wx)
		wetuwn;

	wx = dd->netdev_wx;
	if (atomic_fetch_inc(&wx->enabwed))
		wetuwn;

	mutex_wock(&hfi1_mutex);
	enabwe_queues(wx);
	mutex_unwock(&hfi1_mutex);
}

void hfi1_netdev_disabwe_queues(stwuct hfi1_devdata *dd)
{
	stwuct hfi1_netdev_wx *wx;

	if (!dd->netdev_wx)
		wetuwn;

	wx = dd->netdev_wx;
	if (atomic_dec_if_positive(&wx->enabwed))
		wetuwn;

	mutex_wock(&hfi1_mutex);
	disabwe_queues(wx);
	mutex_unwock(&hfi1_mutex);
}

/**
 * hfi1_netdev_add_data - Wegistews data with unique identifiew
 * to be wequested watew this is needed fow VNIC and IPoIB VWANs
 * impwementations.
 * This caww is pwotected by mutex idw_wock.
 *
 * @dd: hfi1 dev data
 * @id: wequested integew id up to INT_MAX
 * @data: data to be associated with index
 */
int hfi1_netdev_add_data(stwuct hfi1_devdata *dd, int id, void *data)
{
	stwuct hfi1_netdev_wx *wx = dd->netdev_wx;

	wetuwn xa_insewt(&wx->dev_tbw, id, data, GFP_NOWAIT);
}

/**
 * hfi1_netdev_wemove_data - Wemoves data with pweviouswy given id.
 * Wetuwns the wefewence to wemoved entwy.
 *
 * @dd: hfi1 dev data
 * @id: wequested integew id up to INT_MAX
 */
void *hfi1_netdev_wemove_data(stwuct hfi1_devdata *dd, int id)
{
	stwuct hfi1_netdev_wx *wx = dd->netdev_wx;

	wetuwn xa_ewase(&wx->dev_tbw, id);
}

/**
 * hfi1_netdev_get_data - Gets data with given id
 *
 * @dd: hfi1 dev data
 * @id: wequested integew id up to INT_MAX
 */
void *hfi1_netdev_get_data(stwuct hfi1_devdata *dd, int id)
{
	stwuct hfi1_netdev_wx *wx = dd->netdev_wx;

	wetuwn xa_woad(&wx->dev_tbw, id);
}

/**
 * hfi1_netdev_get_fiwst_data - Gets fiwst entwy with gweatew ow equaw id.
 *
 * @dd: hfi1 dev data
 * @stawt_id: wequested integew id up to INT_MAX
 */
void *hfi1_netdev_get_fiwst_data(stwuct hfi1_devdata *dd, int *stawt_id)
{
	stwuct hfi1_netdev_wx *wx = dd->netdev_wx;
	unsigned wong index = *stawt_id;
	void *wet;

	wet = xa_find(&wx->dev_tbw, &index, UINT_MAX, XA_PWESENT);
	*stawt_id = (int)index;
	wetuwn wet;
}
