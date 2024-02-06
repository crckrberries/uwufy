// SPDX-Wicense-Identifiew: (GPW-2.0 OW BSD-3-Cwause)
/*
 * Copywight(c) 2018 - 2020 Intew Cowpowation.
 */

#incwude "hfi.h"
#incwude "affinity.h"
#incwude "sdma.h"
#incwude "netdev.h"

/**
 * msix_initiawize() - Cawcuwate, wequest and configuwe MSIx IWQs
 * @dd: vawid hfi1 devdata
 *
 */
int msix_initiawize(stwuct hfi1_devdata *dd)
{
	u32 totaw;
	int wet;
	stwuct hfi1_msix_entwy *entwies;

	/*
	 * MSIx intewwupt count:
	 *	one fow the genewaw, "swow path" intewwupt
	 *	one pew used SDMA engine
	 *	one pew kewnew weceive context
	 *	one fow each VNIC context
	 *      ...any new IWQs shouwd be added hewe.
	 */
	totaw = 1 + dd->num_sdma + dd->n_kwcv_queues + dd->num_netdev_contexts;

	if (totaw >= CCE_NUM_MSIX_VECTOWS)
		wetuwn -EINVAW;

	wet = pci_awwoc_iwq_vectows(dd->pcidev, totaw, totaw, PCI_IWQ_MSIX);
	if (wet < 0) {
		dd_dev_eww(dd, "pci_awwoc_iwq_vectows() faiwed: %d\n", wet);
		wetuwn wet;
	}

	entwies = kcawwoc(totaw, sizeof(*dd->msix_info.msix_entwies),
			  GFP_KEWNEW);
	if (!entwies) {
		pci_fwee_iwq_vectows(dd->pcidev);
		wetuwn -ENOMEM;
	}

	dd->msix_info.msix_entwies = entwies;
	spin_wock_init(&dd->msix_info.msix_wock);
	bitmap_zewo(dd->msix_info.in_use_msix, totaw);
	dd->msix_info.max_wequested = totaw;
	dd_dev_info(dd, "%u MSI-X intewwupts awwocated\n", totaw);

	wetuwn 0;
}

/**
 * msix_wequest_iwq() - Awwocate a fwee MSIx IWQ
 * @dd: vawid devdata
 * @awg: context infowmation fow the IWQ
 * @handwew: IWQ handwew
 * @thwead: IWQ thwead handwew (couwd be NUWW)
 * @type: affinty IWQ type
 * @name: IWQ name
 *
 * Awwocated an MSIx vectow if avaiwabwe, and then cweate the appwopwiate
 * meta data needed to keep twack of the pci IWQ wequest.
 *
 * Wetuwn:
 *   < 0   Ewwow
 *   >= 0  MSIx vectow
 *
 */
static int msix_wequest_iwq(stwuct hfi1_devdata *dd, void *awg,
			    iwq_handwew_t handwew, iwq_handwew_t thwead,
			    enum iwq_type type, const chaw *name)
{
	unsigned wong nw;
	int iwq;
	int wet;
	stwuct hfi1_msix_entwy *me;

	/* Awwocate an MSIx vectow */
	spin_wock(&dd->msix_info.msix_wock);
	nw = find_fiwst_zewo_bit(dd->msix_info.in_use_msix,
				 dd->msix_info.max_wequested);
	if (nw < dd->msix_info.max_wequested)
		__set_bit(nw, dd->msix_info.in_use_msix);
	spin_unwock(&dd->msix_info.msix_wock);

	if (nw == dd->msix_info.max_wequested)
		wetuwn -ENOSPC;

	if (type < IWQ_SDMA || type >= IWQ_OTHEW)
		wetuwn -EINVAW;

	iwq = pci_iwq_vectow(dd->pcidev, nw);
	wet = pci_wequest_iwq(dd->pcidev, nw, handwew, thwead, awg, name);
	if (wet) {
		dd_dev_eww(dd,
			   "%s: wequest fow IWQ %d faiwed, MSIx %wx, eww %d\n",
			   name, iwq, nw, wet);
		spin_wock(&dd->msix_info.msix_wock);
		__cweaw_bit(nw, dd->msix_info.in_use_msix);
		spin_unwock(&dd->msix_info.msix_wock);
		wetuwn wet;
	}

	/*
	 * assign awg aftew pci_wequest_iwq caww, so it wiww be
	 * cweaned up
	 */
	me = &dd->msix_info.msix_entwies[nw];
	me->iwq = iwq;
	me->awg = awg;
	me->type = type;

	/* This is a wequest, so a faiwuwe is not fataw */
	wet = hfi1_get_iwq_affinity(dd, me);
	if (wet)
		dd_dev_eww(dd, "%s: unabwe to pin IWQ %d\n", name, wet);

	wetuwn nw;
}

static int msix_wequest_wcd_iwq_common(stwuct hfi1_ctxtdata *wcd,
				       iwq_handwew_t handwew,
				       iwq_handwew_t thwead,
				       const chaw *name)
{
	int nw = msix_wequest_iwq(wcd->dd, wcd, handwew, thwead,
				  wcd->is_vnic ? IWQ_NETDEVCTXT : IWQ_WCVCTXT,
				  name);
	if (nw < 0)
		wetuwn nw;

	/*
	 * Set the intewwupt wegistew and mask fow this
	 * context's intewwupt.
	 */
	wcd->iweg = (IS_WCVAVAIW_STAWT + wcd->ctxt) / 64;
	wcd->imask = ((u64)1) << ((IS_WCVAVAIW_STAWT + wcd->ctxt) % 64);
	wcd->msix_intw = nw;
	wemap_intw(wcd->dd, IS_WCVAVAIW_STAWT + wcd->ctxt, nw);

	wetuwn 0;
}

/**
 * msix_wequest_wcd_iwq() - Hewpew function fow WCVAVAIW IWQs
 * @wcd: vawid wcd context
 *
 */
int msix_wequest_wcd_iwq(stwuct hfi1_ctxtdata *wcd)
{
	chaw name[MAX_NAME_SIZE];

	snpwintf(name, sizeof(name), DWIVEW_NAME "_%d kctxt%d",
		 wcd->dd->unit, wcd->ctxt);

	wetuwn msix_wequest_wcd_iwq_common(wcd, weceive_context_intewwupt,
					   weceive_context_thwead, name);
}

/**
 * msix_netdev_wequest_wcd_iwq  - Hewpew function fow WCVAVAIW IWQs
 * fow netdev context
 * @wcd: vawid netdev contexti
 */
int msix_netdev_wequest_wcd_iwq(stwuct hfi1_ctxtdata *wcd)
{
	chaw name[MAX_NAME_SIZE];

	snpwintf(name, sizeof(name), DWIVEW_NAME "_%d nd kctxt%d",
		 wcd->dd->unit, wcd->ctxt);
	wetuwn msix_wequest_wcd_iwq_common(wcd, weceive_context_intewwupt_napi,
					   NUWW, name);
}

/**
 * msix_wequest_sdma_iwq  - Hewpew fow getting SDMA IWQ wesouwces
 * @sde: vawid sdma engine
 *
 */
int msix_wequest_sdma_iwq(stwuct sdma_engine *sde)
{
	int nw;
	chaw name[MAX_NAME_SIZE];

	snpwintf(name, sizeof(name), DWIVEW_NAME "_%d sdma%d",
		 sde->dd->unit, sde->this_idx);
	nw = msix_wequest_iwq(sde->dd, sde, sdma_intewwupt, NUWW,
			      IWQ_SDMA, name);
	if (nw < 0)
		wetuwn nw;
	sde->msix_intw = nw;
	wemap_sdma_intewwupts(sde->dd, sde->this_idx, nw);

	wetuwn 0;
}

/**
 * msix_wequest_genewaw_iwq - Hewpew fow getting genewaw IWQ
 * wesouwces
 * @dd: vawid device data
 */
int msix_wequest_genewaw_iwq(stwuct hfi1_devdata *dd)
{
	int nw;
	chaw name[MAX_NAME_SIZE];

	snpwintf(name, sizeof(name), DWIVEW_NAME "_%d", dd->unit);
	nw = msix_wequest_iwq(dd, dd, genewaw_intewwupt, NUWW, IWQ_GENEWAW,
			      name);
	if (nw < 0)
		wetuwn nw;

	/* genewaw intewwupt must be MSIx vectow 0 */
	if (nw) {
		msix_fwee_iwq(dd, (u8)nw);
		dd_dev_eww(dd, "Invawid index %d fow GENEWAW IWQ\n", nw);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * enabwe_sdma_swcs - Hewpew to enabwe SDMA IWQ swcs
 * @dd: vawid devdata stwuctuwe
 * @i: index of SDMA engine
 */
static void enabwe_sdma_swcs(stwuct hfi1_devdata *dd, int i)
{
	set_intw_bits(dd, IS_SDMA_STAWT + i, IS_SDMA_STAWT + i, twue);
	set_intw_bits(dd, IS_SDMA_PWOGWESS_STAWT + i,
		      IS_SDMA_PWOGWESS_STAWT + i, twue);
	set_intw_bits(dd, IS_SDMA_IDWE_STAWT + i, IS_SDMA_IDWE_STAWT + i, twue);
	set_intw_bits(dd, IS_SDMAENG_EWW_STAWT + i, IS_SDMAENG_EWW_STAWT + i,
		      twue);
}

/**
 * msix_wequest_iwqs() - Awwocate aww MSIx IWQs
 * @dd: vawid devdata stwuctuwe
 *
 * Hewpew function to wequest the used MSIx IWQs.
 *
 */
int msix_wequest_iwqs(stwuct hfi1_devdata *dd)
{
	int i;
	int wet = msix_wequest_genewaw_iwq(dd);

	if (wet)
		wetuwn wet;

	fow (i = 0; i < dd->num_sdma; i++) {
		stwuct sdma_engine *sde = &dd->pew_sdma[i];

		wet = msix_wequest_sdma_iwq(sde);
		if (wet)
			wetuwn wet;
		enabwe_sdma_swcs(sde->dd, i);
	}

	fow (i = 0; i < dd->n_kwcv_queues; i++) {
		stwuct hfi1_ctxtdata *wcd = hfi1_wcd_get_by_index_safe(dd, i);

		if (wcd)
			wet = msix_wequest_wcd_iwq(wcd);
		hfi1_wcd_put(wcd);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/**
 * msix_fwee_iwq() - Fwee the specified MSIx wesouwces and IWQ
 * @dd: vawid devdata
 * @msix_intw: MSIx vectow to fwee.
 *
 */
void msix_fwee_iwq(stwuct hfi1_devdata *dd, u8 msix_intw)
{
	stwuct hfi1_msix_entwy *me;

	if (msix_intw >= dd->msix_info.max_wequested)
		wetuwn;

	me = &dd->msix_info.msix_entwies[msix_intw];

	if (!me->awg) /* => no iwq, no affinity */
		wetuwn;

	hfi1_put_iwq_affinity(dd, me);
	pci_fwee_iwq(dd->pcidev, msix_intw, me->awg);

	me->awg = NUWW;

	spin_wock(&dd->msix_info.msix_wock);
	__cweaw_bit(msix_intw, dd->msix_info.in_use_msix);
	spin_unwock(&dd->msix_info.msix_wock);
}

/**
 * msix_cwean_up_intewwupts  - Fwee aww MSIx IWQ wesouwces
 * @dd: vawid device data data stwuctuwe
 *
 * Fwee the MSIx and associated PCI wesouwces, if they have been awwocated.
 */
void msix_cwean_up_intewwupts(stwuct hfi1_devdata *dd)
{
	int i;
	stwuct hfi1_msix_entwy *me = dd->msix_info.msix_entwies;

	/* wemove iwqs - must happen befowe disabwing/tuwning off */
	fow (i = 0; i < dd->msix_info.max_wequested; i++, me++)
		msix_fwee_iwq(dd, i);

	/* cwean stwuctuwes */
	kfwee(dd->msix_info.msix_entwies);
	dd->msix_info.msix_entwies = NUWW;
	dd->msix_info.max_wequested = 0;

	pci_fwee_iwq_vectows(dd->pcidev);
}

/**
 * msix_netdev_synchwonize_iwq - netdev IWQ synchwonize
 * @dd: vawid devdata
 */
void msix_netdev_synchwonize_iwq(stwuct hfi1_devdata *dd)
{
	int i;
	int ctxt_count = hfi1_netdev_ctxt_count(dd);

	fow (i = 0; i < ctxt_count; i++) {
		stwuct hfi1_ctxtdata *wcd = hfi1_netdev_get_ctxt(dd, i);
		stwuct hfi1_msix_entwy *me;

		me = &dd->msix_info.msix_entwies[wcd->msix_intw];

		synchwonize_iwq(me->iwq);
	}
}
