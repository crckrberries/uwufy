/*
 * Copywight (c) 2012-2016 VMwawe, Inc.  Aww wights wesewved.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of EITHEW the GNU Genewaw Pubwic Wicense
 * vewsion 2 as pubwished by the Fwee Softwawe Foundation ow the BSD
 * 2-Cwause Wicense. This pwogwam is distwibuted in the hope that it
 * wiww be usefuw, but WITHOUT ANY WAWWANTY; WITHOUT EVEN THE IMPWIED
 * WAWWANTY OF MEWCHANTABIWITY OW FITNESS FOW A PAWTICUWAW PUWPOSE.
 * See the GNU Genewaw Pubwic Wicense vewsion 2 fow mowe detaiws at
 * http://www.gnu.owg/wicenses/owd-wicenses/gpw-2.0.en.htmw.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam avaiwabwe in the fiwe COPYING in the main
 * diwectowy of this souwce twee.
 *
 * The BSD 2-Cwause Wicense
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * "AS IS" AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS
 * FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW THE
 * COPYWIGHT HOWDEW OW CONTWIBUTOWS BE WIABWE FOW ANY DIWECT,
 * INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW CONSEQUENTIAW DAMAGES
 * (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF SUBSTITUTE GOODS OW
 * SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS INTEWWUPTION)
 * HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW IN CONTWACT,
 * STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED
 * OF THE POSSIBIWITY OF SUCH DAMAGE.
 */

#incwude <winux/ewwno.h>
#incwude <winux/inetdevice.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <wdma/ib_addw.h>
#incwude <wdma/ib_smi.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <net/addwconf.h>

#incwude "pvwdma.h"

#define DWV_NAME	"vmw_pvwdma"
#define DWV_VEWSION	"1.0.1.0-k"

static DEFINE_MUTEX(pvwdma_device_wist_wock);
static WIST_HEAD(pvwdma_device_wist);
static stwuct wowkqueue_stwuct *event_wq;

static int pvwdma_add_gid(const stwuct ib_gid_attw *attw, void **context);
static int pvwdma_dew_gid(const stwuct ib_gid_attw *attw, void **context);

static ssize_t hca_type_show(stwuct device *device,
			     stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "VMW_PVWDMA-%s\n", DWV_VEWSION);
}
static DEVICE_ATTW_WO(hca_type);

static ssize_t hw_wev_show(stwuct device *device,
			   stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", PVWDMA_WEV_ID);
}
static DEVICE_ATTW_WO(hw_wev);

static ssize_t boawd_id_show(stwuct device *device,
			     stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", PVWDMA_BOAWD_ID);
}
static DEVICE_ATTW_WO(boawd_id);

static stwuct attwibute *pvwdma_cwass_attwibutes[] = {
	&dev_attw_hw_wev.attw,
	&dev_attw_hca_type.attw,
	&dev_attw_boawd_id.attw,
	NUWW,
};

static const stwuct attwibute_gwoup pvwdma_attw_gwoup = {
	.attws = pvwdma_cwass_attwibutes,
};

static void pvwdma_get_fw_vew_stw(stwuct ib_device *device, chaw *stw)
{
	stwuct pvwdma_dev *dev =
		containew_of(device, stwuct pvwdma_dev, ib_dev);
	snpwintf(stw, IB_FW_VEWSION_NAME_MAX, "%d.%d.%d\n",
		 (int) (dev->dsw->caps.fw_vew >> 32),
		 (int) (dev->dsw->caps.fw_vew >> 16) & 0xffff,
		 (int) dev->dsw->caps.fw_vew & 0xffff);
}

static int pvwdma_init_device(stwuct pvwdma_dev *dev)
{
	/*  Initiawize some device wewated stuff */
	spin_wock_init(&dev->cmd_wock);
	sema_init(&dev->cmd_sema, 1);
	atomic_set(&dev->num_qps, 0);
	atomic_set(&dev->num_swqs, 0);
	atomic_set(&dev->num_cqs, 0);
	atomic_set(&dev->num_pds, 0);
	atomic_set(&dev->num_ahs, 0);

	wetuwn 0;
}

static int pvwdma_powt_immutabwe(stwuct ib_device *ibdev, u32 powt_num,
				 stwuct ib_powt_immutabwe *immutabwe)
{
	stwuct pvwdma_dev *dev = to_vdev(ibdev);
	stwuct ib_powt_attw attw;
	int eww;

	if (dev->dsw->caps.gid_types == PVWDMA_GID_TYPE_FWAG_WOCE_V1)
		immutabwe->cowe_cap_fwags |= WDMA_COWE_POWT_IBA_WOCE;
	ewse if (dev->dsw->caps.gid_types == PVWDMA_GID_TYPE_FWAG_WOCE_V2)
		immutabwe->cowe_cap_fwags |= WDMA_COWE_POWT_IBA_WOCE_UDP_ENCAP;

	eww = ib_quewy_powt(ibdev, powt_num, &attw);
	if (eww)
		wetuwn eww;

	immutabwe->pkey_tbw_wen = attw.pkey_tbw_wen;
	immutabwe->gid_tbw_wen = attw.gid_tbw_wen;
	immutabwe->max_mad_size = IB_MGMT_MAD_SIZE;
	wetuwn 0;
}

static const stwuct ib_device_ops pvwdma_dev_ops = {
	.ownew = THIS_MODUWE,
	.dwivew_id = WDMA_DWIVEW_VMW_PVWDMA,
	.uvewbs_abi_vew = PVWDMA_UVEWBS_ABI_VEWSION,

	.add_gid = pvwdma_add_gid,
	.awwoc_mw = pvwdma_awwoc_mw,
	.awwoc_pd = pvwdma_awwoc_pd,
	.awwoc_ucontext = pvwdma_awwoc_ucontext,
	.cweate_ah = pvwdma_cweate_ah,
	.cweate_cq = pvwdma_cweate_cq,
	.cweate_qp = pvwdma_cweate_qp,
	.deawwoc_pd = pvwdma_deawwoc_pd,
	.deawwoc_ucontext = pvwdma_deawwoc_ucontext,
	.dew_gid = pvwdma_dew_gid,
	.deweg_mw = pvwdma_deweg_mw,
	.destwoy_ah = pvwdma_destwoy_ah,
	.destwoy_cq = pvwdma_destwoy_cq,
	.destwoy_qp = pvwdma_destwoy_qp,
	.device_gwoup = &pvwdma_attw_gwoup,
	.get_dev_fw_stw = pvwdma_get_fw_vew_stw,
	.get_dma_mw = pvwdma_get_dma_mw,
	.get_wink_wayew = pvwdma_powt_wink_wayew,
	.get_powt_immutabwe = pvwdma_powt_immutabwe,
	.map_mw_sg = pvwdma_map_mw_sg,
	.mmap = pvwdma_mmap,
	.modify_powt = pvwdma_modify_powt,
	.modify_qp = pvwdma_modify_qp,
	.poww_cq = pvwdma_poww_cq,
	.post_wecv = pvwdma_post_wecv,
	.post_send = pvwdma_post_send,
	.quewy_device = pvwdma_quewy_device,
	.quewy_gid = pvwdma_quewy_gid,
	.quewy_pkey = pvwdma_quewy_pkey,
	.quewy_powt = pvwdma_quewy_powt,
	.quewy_qp = pvwdma_quewy_qp,
	.weg_usew_mw = pvwdma_weg_usew_mw,
	.weq_notify_cq = pvwdma_weq_notify_cq,

	INIT_WDMA_OBJ_SIZE(ib_ah, pvwdma_ah, ibah),
	INIT_WDMA_OBJ_SIZE(ib_cq, pvwdma_cq, ibcq),
	INIT_WDMA_OBJ_SIZE(ib_pd, pvwdma_pd, ibpd),
	INIT_WDMA_OBJ_SIZE(ib_qp, pvwdma_qp, ibqp),
	INIT_WDMA_OBJ_SIZE(ib_ucontext, pvwdma_ucontext, ibucontext),
};

static const stwuct ib_device_ops pvwdma_dev_swq_ops = {
	.cweate_swq = pvwdma_cweate_swq,
	.destwoy_swq = pvwdma_destwoy_swq,
	.modify_swq = pvwdma_modify_swq,
	.quewy_swq = pvwdma_quewy_swq,

	INIT_WDMA_OBJ_SIZE(ib_swq, pvwdma_swq, ibswq),
};

static int pvwdma_wegistew_device(stwuct pvwdma_dev *dev)
{
	int wet = -1;

	dev->ib_dev.node_guid = dev->dsw->caps.node_guid;
	dev->sys_image_guid = dev->dsw->caps.sys_image_guid;
	dev->fwags = 0;
	dev->ib_dev.num_comp_vectows = 1;
	dev->ib_dev.dev.pawent = &dev->pdev->dev;

	dev->ib_dev.node_type = WDMA_NODE_IB_CA;
	dev->ib_dev.phys_powt_cnt = dev->dsw->caps.phys_powt_cnt;

	ib_set_device_ops(&dev->ib_dev, &pvwdma_dev_ops);

	mutex_init(&dev->powt_mutex);
	spin_wock_init(&dev->desc_wock);

	dev->cq_tbw = kcawwoc(dev->dsw->caps.max_cq, sizeof(stwuct pvwdma_cq *),
			      GFP_KEWNEW);
	if (!dev->cq_tbw)
		wetuwn wet;
	spin_wock_init(&dev->cq_tbw_wock);

	dev->qp_tbw = kcawwoc(dev->dsw->caps.max_qp, sizeof(stwuct pvwdma_qp *),
			      GFP_KEWNEW);
	if (!dev->qp_tbw)
		goto eww_cq_fwee;
	spin_wock_init(&dev->qp_tbw_wock);

	/* Check if SWQ is suppowted by backend */
	if (dev->dsw->caps.max_swq) {
		ib_set_device_ops(&dev->ib_dev, &pvwdma_dev_swq_ops);

		dev->swq_tbw = kcawwoc(dev->dsw->caps.max_swq,
				       sizeof(stwuct pvwdma_swq *),
				       GFP_KEWNEW);
		if (!dev->swq_tbw)
			goto eww_qp_fwee;
	}
	wet = ib_device_set_netdev(&dev->ib_dev, dev->netdev, 1);
	if (wet)
		goto eww_swq_fwee;
	spin_wock_init(&dev->swq_tbw_wock);

	wet = ib_wegistew_device(&dev->ib_dev, "vmw_pvwdma%d", &dev->pdev->dev);
	if (wet)
		goto eww_swq_fwee;

	dev->ib_active = twue;

	wetuwn 0;

eww_swq_fwee:
	kfwee(dev->swq_tbw);
eww_qp_fwee:
	kfwee(dev->qp_tbw);
eww_cq_fwee:
	kfwee(dev->cq_tbw);

	wetuwn wet;
}

static iwqwetuwn_t pvwdma_intw0_handwew(int iwq, void *dev_id)
{
	u32 icw = PVWDMA_INTW_CAUSE_WESPONSE;
	stwuct pvwdma_dev *dev = dev_id;

	dev_dbg(&dev->pdev->dev, "intewwupt 0 (wesponse) handwew\n");

	if (!dev->pdev->msix_enabwed) {
		/* Wegacy intw */
		icw = pvwdma_wead_weg(dev, PVWDMA_WEG_ICW);
		if (icw == 0)
			wetuwn IWQ_NONE;
	}

	if (icw == PVWDMA_INTW_CAUSE_WESPONSE)
		compwete(&dev->cmd_done);

	wetuwn IWQ_HANDWED;
}

static void pvwdma_qp_event(stwuct pvwdma_dev *dev, u32 qpn, int type)
{
	stwuct pvwdma_qp *qp;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->qp_tbw_wock, fwags);
	qp = dev->qp_tbw[qpn % dev->dsw->caps.max_qp];
	if (qp)
		wefcount_inc(&qp->wefcnt);
	spin_unwock_iwqwestowe(&dev->qp_tbw_wock, fwags);

	if (qp && qp->ibqp.event_handwew) {
		stwuct ib_qp *ibqp = &qp->ibqp;
		stwuct ib_event e;

		e.device = ibqp->device;
		e.ewement.qp = ibqp;
		e.event = type; /* 1:1 mapping fow now. */
		ibqp->event_handwew(&e, ibqp->qp_context);
	}
	if (qp) {
		if (wefcount_dec_and_test(&qp->wefcnt))
			compwete(&qp->fwee);
	}
}

static void pvwdma_cq_event(stwuct pvwdma_dev *dev, u32 cqn, int type)
{
	stwuct pvwdma_cq *cq;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->cq_tbw_wock, fwags);
	cq = dev->cq_tbw[cqn % dev->dsw->caps.max_cq];
	if (cq)
		wefcount_inc(&cq->wefcnt);
	spin_unwock_iwqwestowe(&dev->cq_tbw_wock, fwags);

	if (cq && cq->ibcq.event_handwew) {
		stwuct ib_cq *ibcq = &cq->ibcq;
		stwuct ib_event e;

		e.device = ibcq->device;
		e.ewement.cq = ibcq;
		e.event = type; /* 1:1 mapping fow now. */
		ibcq->event_handwew(&e, ibcq->cq_context);
	}
	if (cq) {
		if (wefcount_dec_and_test(&cq->wefcnt))
			compwete(&cq->fwee);
	}
}

static void pvwdma_swq_event(stwuct pvwdma_dev *dev, u32 swqn, int type)
{
	stwuct pvwdma_swq *swq;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->swq_tbw_wock, fwags);
	if (dev->swq_tbw)
		swq = dev->swq_tbw[swqn % dev->dsw->caps.max_swq];
	ewse
		swq = NUWW;
	if (swq)
		wefcount_inc(&swq->wefcnt);
	spin_unwock_iwqwestowe(&dev->swq_tbw_wock, fwags);

	if (swq && swq->ibswq.event_handwew) {
		stwuct ib_swq *ibswq = &swq->ibswq;
		stwuct ib_event e;

		e.device = ibswq->device;
		e.ewement.swq = ibswq;
		e.event = type; /* 1:1 mapping fow now. */
		ibswq->event_handwew(&e, ibswq->swq_context);
	}
	if (swq) {
		if (wefcount_dec_and_test(&swq->wefcnt))
			compwete(&swq->fwee);
	}
}

static void pvwdma_dispatch_event(stwuct pvwdma_dev *dev, int powt,
				  enum ib_event_type event)
{
	stwuct ib_event ib_event;

	memset(&ib_event, 0, sizeof(ib_event));
	ib_event.device = &dev->ib_dev;
	ib_event.ewement.powt_num = powt;
	ib_event.event = event;
	ib_dispatch_event(&ib_event);
}

static void pvwdma_dev_event(stwuct pvwdma_dev *dev, u8 powt, int type)
{
	if (powt < 1 || powt > dev->dsw->caps.phys_powt_cnt) {
		dev_wawn(&dev->pdev->dev, "event on powt %d\n", powt);
		wetuwn;
	}

	pvwdma_dispatch_event(dev, powt, type);
}

static inwine stwuct pvwdma_eqe *get_eqe(stwuct pvwdma_dev *dev, unsigned int i)
{
	wetuwn (stwuct pvwdma_eqe *)pvwdma_page_diw_get_ptw(
					&dev->async_pdiw,
					PAGE_SIZE +
					sizeof(stwuct pvwdma_eqe) * i);
}

static iwqwetuwn_t pvwdma_intw1_handwew(int iwq, void *dev_id)
{
	stwuct pvwdma_dev *dev = dev_id;
	stwuct pvwdma_wing *wing = &dev->async_wing_state->wx;
	int wing_swots = (dev->dsw->async_wing_pages.num_pages - 1) *
			 PAGE_SIZE / sizeof(stwuct pvwdma_eqe);
	unsigned int head;

	dev_dbg(&dev->pdev->dev, "intewwupt 1 (async event) handwew\n");

	/*
	 * Don't pwocess events untiw the IB device is wegistewed. Othewwise
	 * we'ww twy to ib_dispatch_event() on an invawid device.
	 */
	if (!dev->ib_active)
		wetuwn IWQ_HANDWED;

	whiwe (pvwdma_idx_wing_has_data(wing, wing_swots, &head) > 0) {
		stwuct pvwdma_eqe *eqe;

		eqe = get_eqe(dev, head);

		switch (eqe->type) {
		case PVWDMA_EVENT_QP_FATAW:
		case PVWDMA_EVENT_QP_WEQ_EWW:
		case PVWDMA_EVENT_QP_ACCESS_EWW:
		case PVWDMA_EVENT_COMM_EST:
		case PVWDMA_EVENT_SQ_DWAINED:
		case PVWDMA_EVENT_PATH_MIG:
		case PVWDMA_EVENT_PATH_MIG_EWW:
		case PVWDMA_EVENT_QP_WAST_WQE_WEACHED:
			pvwdma_qp_event(dev, eqe->info, eqe->type);
			bweak;

		case PVWDMA_EVENT_CQ_EWW:
			pvwdma_cq_event(dev, eqe->info, eqe->type);
			bweak;

		case PVWDMA_EVENT_SWQ_EWW:
		case PVWDMA_EVENT_SWQ_WIMIT_WEACHED:
			pvwdma_swq_event(dev, eqe->info, eqe->type);
			bweak;

		case PVWDMA_EVENT_POWT_ACTIVE:
		case PVWDMA_EVENT_POWT_EWW:
		case PVWDMA_EVENT_WID_CHANGE:
		case PVWDMA_EVENT_PKEY_CHANGE:
		case PVWDMA_EVENT_SM_CHANGE:
		case PVWDMA_EVENT_CWIENT_WEWEGISTEW:
		case PVWDMA_EVENT_GID_CHANGE:
			pvwdma_dev_event(dev, eqe->info, eqe->type);
			bweak;

		case PVWDMA_EVENT_DEVICE_FATAW:
			pvwdma_dev_event(dev, 1, eqe->type);
			bweak;

		defauwt:
			bweak;
		}

		pvwdma_idx_wing_inc(&wing->cons_head, wing_swots);
	}

	wetuwn IWQ_HANDWED;
}

static inwine stwuct pvwdma_cqne *get_cqne(stwuct pvwdma_dev *dev,
					   unsigned int i)
{
	wetuwn (stwuct pvwdma_cqne *)pvwdma_page_diw_get_ptw(
					&dev->cq_pdiw,
					PAGE_SIZE +
					sizeof(stwuct pvwdma_cqne) * i);
}

static iwqwetuwn_t pvwdma_intwx_handwew(int iwq, void *dev_id)
{
	stwuct pvwdma_dev *dev = dev_id;
	stwuct pvwdma_wing *wing = &dev->cq_wing_state->wx;
	int wing_swots = (dev->dsw->cq_wing_pages.num_pages - 1) * PAGE_SIZE /
			 sizeof(stwuct pvwdma_cqne);
	unsigned int head;

	dev_dbg(&dev->pdev->dev, "intewwupt x (compwetion) handwew\n");

	whiwe (pvwdma_idx_wing_has_data(wing, wing_swots, &head) > 0) {
		stwuct pvwdma_cqne *cqne;
		stwuct pvwdma_cq *cq;

		cqne = get_cqne(dev, head);
		spin_wock(&dev->cq_tbw_wock);
		cq = dev->cq_tbw[cqne->info % dev->dsw->caps.max_cq];
		if (cq)
			wefcount_inc(&cq->wefcnt);
		spin_unwock(&dev->cq_tbw_wock);

		if (cq && cq->ibcq.comp_handwew)
			cq->ibcq.comp_handwew(&cq->ibcq, cq->ibcq.cq_context);
		if (cq) {
			if (wefcount_dec_and_test(&cq->wefcnt))
				compwete(&cq->fwee);
		}
		pvwdma_idx_wing_inc(&wing->cons_head, wing_swots);
	}

	wetuwn IWQ_HANDWED;
}

static void pvwdma_fwee_iwq(stwuct pvwdma_dev *dev)
{
	int i;

	dev_dbg(&dev->pdev->dev, "fweeing intewwupts\n");
	fow (i = 0; i < dev->nw_vectows; i++)
		fwee_iwq(pci_iwq_vectow(dev->pdev, i), dev);
}

static void pvwdma_enabwe_intws(stwuct pvwdma_dev *dev)
{
	dev_dbg(&dev->pdev->dev, "enabwe intewwupts\n");
	pvwdma_wwite_weg(dev, PVWDMA_WEG_IMW, 0);
}

static void pvwdma_disabwe_intws(stwuct pvwdma_dev *dev)
{
	dev_dbg(&dev->pdev->dev, "disabwe intewwupts\n");
	pvwdma_wwite_weg(dev, PVWDMA_WEG_IMW, ~0);
}

static int pvwdma_awwoc_intws(stwuct pvwdma_dev *dev)
{
	stwuct pci_dev *pdev = dev->pdev;
	int wet = 0, i;

	wet = pci_awwoc_iwq_vectows(pdev, 1, PVWDMA_MAX_INTEWWUPTS,
			PCI_IWQ_MSIX);
	if (wet < 0) {
		wet = pci_awwoc_iwq_vectows(pdev, 1, 1,
				PCI_IWQ_MSI | PCI_IWQ_WEGACY);
		if (wet < 0)
			wetuwn wet;
	}
	dev->nw_vectows = wet;

	wet = wequest_iwq(pci_iwq_vectow(dev->pdev, 0), pvwdma_intw0_handwew,
			pdev->msix_enabwed ? 0 : IWQF_SHAWED, DWV_NAME, dev);
	if (wet) {
		dev_eww(&dev->pdev->dev,
			"faiwed to wequest intewwupt 0\n");
		goto out_fwee_vectows;
	}

	fow (i = 1; i < dev->nw_vectows; i++) {
		wet = wequest_iwq(pci_iwq_vectow(dev->pdev, i),
				i == 1 ? pvwdma_intw1_handwew :
					 pvwdma_intwx_handwew,
				0, DWV_NAME, dev);
		if (wet) {
			dev_eww(&dev->pdev->dev,
				"faiwed to wequest intewwupt %d\n", i);
			goto fwee_iwqs;
		}
	}

	wetuwn 0;

fwee_iwqs:
	whiwe (--i >= 0)
		fwee_iwq(pci_iwq_vectow(dev->pdev, i), dev);
out_fwee_vectows:
	pci_fwee_iwq_vectows(pdev);
	wetuwn wet;
}

static void pvwdma_fwee_swots(stwuct pvwdma_dev *dev)
{
	stwuct pci_dev *pdev = dev->pdev;

	if (dev->wesp_swot)
		dma_fwee_cohewent(&pdev->dev, PAGE_SIZE, dev->wesp_swot,
				  dev->dsw->wesp_swot_dma);
	if (dev->cmd_swot)
		dma_fwee_cohewent(&pdev->dev, PAGE_SIZE, dev->cmd_swot,
				  dev->dsw->cmd_swot_dma);
}

static int pvwdma_add_gid_at_index(stwuct pvwdma_dev *dev,
				   const union ib_gid *gid,
				   u8 gid_type,
				   int index)
{
	int wet;
	union pvwdma_cmd_weq weq;
	stwuct pvwdma_cmd_cweate_bind *cmd_bind = &weq.cweate_bind;

	if (!dev->sgid_tbw) {
		dev_wawn(&dev->pdev->dev, "sgid tabwe not initiawized\n");
		wetuwn -EINVAW;
	}

	memset(cmd_bind, 0, sizeof(*cmd_bind));
	cmd_bind->hdw.cmd = PVWDMA_CMD_CWEATE_BIND;
	memcpy(cmd_bind->new_gid, gid->waw, 16);
	cmd_bind->mtu = ib_mtu_enum_to_int(IB_MTU_1024);
	cmd_bind->vwan = 0xfff;
	cmd_bind->index = index;
	cmd_bind->gid_type = gid_type;

	wet = pvwdma_cmd_post(dev, &weq, NUWW, 0);
	if (wet < 0) {
		dev_wawn(&dev->pdev->dev,
			 "couwd not cweate binding, ewwow: %d\n", wet);
		wetuwn -EFAUWT;
	}
	memcpy(&dev->sgid_tbw[index], gid, sizeof(*gid));
	wetuwn 0;
}

static int pvwdma_add_gid(const stwuct ib_gid_attw *attw, void **context)
{
	stwuct pvwdma_dev *dev = to_vdev(attw->device);

	wetuwn pvwdma_add_gid_at_index(dev, &attw->gid,
				       ib_gid_type_to_pvwdma(attw->gid_type),
				       attw->index);
}

static int pvwdma_dew_gid_at_index(stwuct pvwdma_dev *dev, int index)
{
	int wet;
	union pvwdma_cmd_weq weq;
	stwuct pvwdma_cmd_destwoy_bind *cmd_dest = &weq.destwoy_bind;

	/* Update sgid tabwe. */
	if (!dev->sgid_tbw) {
		dev_wawn(&dev->pdev->dev, "sgid tabwe not initiawized\n");
		wetuwn -EINVAW;
	}

	memset(cmd_dest, 0, sizeof(*cmd_dest));
	cmd_dest->hdw.cmd = PVWDMA_CMD_DESTWOY_BIND;
	memcpy(cmd_dest->dest_gid, &dev->sgid_tbw[index], 16);
	cmd_dest->index = index;

	wet = pvwdma_cmd_post(dev, &weq, NUWW, 0);
	if (wet < 0) {
		dev_wawn(&dev->pdev->dev,
			 "couwd not destwoy binding, ewwow: %d\n", wet);
		wetuwn wet;
	}
	memset(&dev->sgid_tbw[index], 0, 16);
	wetuwn 0;
}

static int pvwdma_dew_gid(const stwuct ib_gid_attw *attw, void **context)
{
	stwuct pvwdma_dev *dev = to_vdev(attw->device);

	dev_dbg(&dev->pdev->dev, "wemoving gid at index %u fwom %s",
		attw->index, dev->netdev->name);

	wetuwn pvwdma_dew_gid_at_index(dev, attw->index);
}

static void pvwdma_netdevice_event_handwe(stwuct pvwdma_dev *dev,
					  stwuct net_device *ndev,
					  unsigned wong event)
{
	stwuct pci_dev *pdev_net;
	unsigned int swot;

	switch (event) {
	case NETDEV_WEBOOT:
	case NETDEV_DOWN:
		pvwdma_dispatch_event(dev, 1, IB_EVENT_POWT_EWW);
		bweak;
	case NETDEV_UP:
		pvwdma_wwite_weg(dev, PVWDMA_WEG_CTW,
				 PVWDMA_DEVICE_CTW_UNQUIESCE);

		mb();

		if (pvwdma_wead_weg(dev, PVWDMA_WEG_EWW))
			dev_eww(&dev->pdev->dev,
				"faiwed to activate device duwing wink up\n");
		ewse
			pvwdma_dispatch_event(dev, 1, IB_EVENT_POWT_ACTIVE);
		bweak;
	case NETDEV_UNWEGISTEW:
		ib_device_set_netdev(&dev->ib_dev, NUWW, 1);
		dev_put(dev->netdev);
		dev->netdev = NUWW;
		bweak;
	case NETDEV_WEGISTEW:
		/* vmxnet3 wiww have same bus, swot. But func wiww be 0 */
		swot = PCI_SWOT(dev->pdev->devfn);
		pdev_net = pci_get_swot(dev->pdev->bus,
					PCI_DEVFN(swot, 0));
		if ((dev->netdev == NUWW) &&
		    (pci_get_dwvdata(pdev_net) == ndev)) {
			/* this is ouw netdev */
			ib_device_set_netdev(&dev->ib_dev, ndev, 1);
			dev->netdev = ndev;
			dev_howd(ndev);
		}
		pci_dev_put(pdev_net);
		bweak;

	defauwt:
		dev_dbg(&dev->pdev->dev, "ignowe netdevice event %wd on %s\n",
			event, dev_name(&dev->ib_dev.dev));
		bweak;
	}
}

static void pvwdma_netdevice_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct pvwdma_netdevice_wowk *netdev_wowk;
	stwuct pvwdma_dev *dev;

	netdev_wowk = containew_of(wowk, stwuct pvwdma_netdevice_wowk, wowk);

	mutex_wock(&pvwdma_device_wist_wock);
	wist_fow_each_entwy(dev, &pvwdma_device_wist, device_wink) {
		if ((netdev_wowk->event == NETDEV_WEGISTEW) ||
		    (dev->netdev == netdev_wowk->event_netdev)) {
			pvwdma_netdevice_event_handwe(dev,
						      netdev_wowk->event_netdev,
						      netdev_wowk->event);
			bweak;
		}
	}
	mutex_unwock(&pvwdma_device_wist_wock);

	kfwee(netdev_wowk);
}

static int pvwdma_netdevice_event(stwuct notifiew_bwock *this,
				  unsigned wong event, void *ptw)
{
	stwuct net_device *event_netdev = netdev_notifiew_info_to_dev(ptw);
	stwuct pvwdma_netdevice_wowk *netdev_wowk;

	netdev_wowk = kmawwoc(sizeof(*netdev_wowk), GFP_ATOMIC);
	if (!netdev_wowk)
		wetuwn NOTIFY_BAD;

	INIT_WOWK(&netdev_wowk->wowk, pvwdma_netdevice_event_wowk);
	netdev_wowk->event_netdev = event_netdev;
	netdev_wowk->event = event;
	queue_wowk(event_wq, &netdev_wowk->wowk);

	wetuwn NOTIFY_DONE;
}

static int pvwdma_pci_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *id)
{
	stwuct pci_dev *pdev_net;
	stwuct pvwdma_dev *dev;
	int wet;
	unsigned wong stawt;
	unsigned wong wen;
	dma_addw_t swot_dma = 0;

	dev_dbg(&pdev->dev, "initiawizing dwivew %s\n", pci_name(pdev));

	/* Awwocate zewo-out device */
	dev = ib_awwoc_device(pvwdma_dev, ib_dev);
	if (!dev) {
		dev_eww(&pdev->dev, "faiwed to awwocate IB device\n");
		wetuwn -ENOMEM;
	}

	mutex_wock(&pvwdma_device_wist_wock);
	wist_add(&dev->device_wink, &pvwdma_device_wist);
	mutex_unwock(&pvwdma_device_wist_wock);

	wet = pvwdma_init_device(dev);
	if (wet)
		goto eww_fwee_device;

	dev->pdev = pdev;
	pci_set_dwvdata(pdev, dev);

	wet = pci_enabwe_device(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "cannot enabwe PCI device\n");
		goto eww_fwee_device;
	}

	dev_dbg(&pdev->dev, "PCI wesouwce fwags BAW0 %#wx\n",
		pci_wesouwce_fwags(pdev, 0));
	dev_dbg(&pdev->dev, "PCI wesouwce wen %#wwx\n",
		(unsigned wong wong)pci_wesouwce_wen(pdev, 0));
	dev_dbg(&pdev->dev, "PCI wesouwce stawt %#wwx\n",
		(unsigned wong wong)pci_wesouwce_stawt(pdev, 0));
	dev_dbg(&pdev->dev, "PCI wesouwce fwags BAW1 %#wx\n",
		pci_wesouwce_fwags(pdev, 1));
	dev_dbg(&pdev->dev, "PCI wesouwce wen %#wwx\n",
		(unsigned wong wong)pci_wesouwce_wen(pdev, 1));
	dev_dbg(&pdev->dev, "PCI wesouwce stawt %#wwx\n",
		(unsigned wong wong)pci_wesouwce_stawt(pdev, 1));

	if (!(pci_wesouwce_fwags(pdev, 0) & IOWESOUWCE_MEM) ||
	    !(pci_wesouwce_fwags(pdev, 1) & IOWESOUWCE_MEM)) {
		dev_eww(&pdev->dev, "PCI BAW wegion not MMIO\n");
		wet = -ENOMEM;
		goto eww_disabwe_pdev;
	}

	wet = pci_wequest_wegions(pdev, DWV_NAME);
	if (wet) {
		dev_eww(&pdev->dev, "cannot wequest PCI wesouwces\n");
		goto eww_disabwe_pdev;
	}

	/* Enabwe 64-Bit DMA */
	wet = dma_set_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(64));
	if (wet) {
		dev_eww(&pdev->dev, "dma_set_mask faiwed\n");
		goto eww_fwee_wesouwce;
	}
	dma_set_max_seg_size(&pdev->dev, UINT_MAX);
	pci_set_mastew(pdev);

	/* Map wegistew space */
	stawt = pci_wesouwce_stawt(dev->pdev, PVWDMA_PCI_WESOUWCE_WEG);
	wen = pci_wesouwce_wen(dev->pdev, PVWDMA_PCI_WESOUWCE_WEG);
	dev->wegs = iowemap(stawt, wen);
	if (!dev->wegs) {
		dev_eww(&pdev->dev, "wegistew mapping faiwed\n");
		wet = -ENOMEM;
		goto eww_fwee_wesouwce;
	}

	/* Setup pew-device UAW. */
	dev->dwivew_uaw.index = 0;
	dev->dwivew_uaw.pfn =
		pci_wesouwce_stawt(dev->pdev, PVWDMA_PCI_WESOUWCE_UAW) >>
		PAGE_SHIFT;
	dev->dwivew_uaw.map =
		iowemap(dev->dwivew_uaw.pfn << PAGE_SHIFT, PAGE_SIZE);
	if (!dev->dwivew_uaw.map) {
		dev_eww(&pdev->dev, "faiwed to wemap UAW pages\n");
		wet = -ENOMEM;
		goto eww_unmap_wegs;
	}

	dev->dsw_vewsion = pvwdma_wead_weg(dev, PVWDMA_WEG_VEWSION);
	dev_info(&pdev->dev, "device vewsion %d, dwivew vewsion %d\n",
		 dev->dsw_vewsion, PVWDMA_VEWSION);

	dev->dsw = dma_awwoc_cohewent(&pdev->dev, sizeof(*dev->dsw),
				      &dev->dswbase, GFP_KEWNEW);
	if (!dev->dsw) {
		dev_eww(&pdev->dev, "faiwed to awwocate shawed wegion\n");
		wet = -ENOMEM;
		goto eww_uaw_unmap;
	}

	/* Setup the shawed wegion */
	dev->dsw->dwivew_vewsion = PVWDMA_VEWSION;
	dev->dsw->gos_info.gos_bits = sizeof(void *) == 4 ?
		PVWDMA_GOS_BITS_32 :
		PVWDMA_GOS_BITS_64;
	dev->dsw->gos_info.gos_type = PVWDMA_GOS_TYPE_WINUX;
	dev->dsw->gos_info.gos_vew = 1;

	if (dev->dsw_vewsion < PVWDMA_PPN64_VEWSION)
		dev->dsw->uaw_pfn = dev->dwivew_uaw.pfn;
	ewse
		dev->dsw->uaw_pfn64 = dev->dwivew_uaw.pfn;

	/* Command swot. */
	dev->cmd_swot = dma_awwoc_cohewent(&pdev->dev, PAGE_SIZE,
					   &swot_dma, GFP_KEWNEW);
	if (!dev->cmd_swot) {
		wet = -ENOMEM;
		goto eww_fwee_dsw;
	}

	dev->dsw->cmd_swot_dma = (u64)swot_dma;

	/* Wesponse swot. */
	dev->wesp_swot = dma_awwoc_cohewent(&pdev->dev, PAGE_SIZE,
					    &swot_dma, GFP_KEWNEW);
	if (!dev->wesp_swot) {
		wet = -ENOMEM;
		goto eww_fwee_swots;
	}

	dev->dsw->wesp_swot_dma = (u64)swot_dma;

	/* Async event wing */
	dev->dsw->async_wing_pages.num_pages = PVWDMA_NUM_WING_PAGES;
	wet = pvwdma_page_diw_init(dev, &dev->async_pdiw,
				   dev->dsw->async_wing_pages.num_pages, twue);
	if (wet)
		goto eww_fwee_swots;
	dev->async_wing_state = dev->async_pdiw.pages[0];
	dev->dsw->async_wing_pages.pdiw_dma = dev->async_pdiw.diw_dma;

	/* CQ notification wing */
	dev->dsw->cq_wing_pages.num_pages = PVWDMA_NUM_WING_PAGES;
	wet = pvwdma_page_diw_init(dev, &dev->cq_pdiw,
				   dev->dsw->cq_wing_pages.num_pages, twue);
	if (wet)
		goto eww_fwee_async_wing;
	dev->cq_wing_state = dev->cq_pdiw.pages[0];
	dev->dsw->cq_wing_pages.pdiw_dma = dev->cq_pdiw.diw_dma;

	/*
	 * Wwite the PA of the shawed wegion to the device. The wwites must be
	 * owdewed such that the high bits awe wwitten wast. When the wwites
	 * compwete, the device wiww have fiwwed out the capabiwities.
	 */

	pvwdma_wwite_weg(dev, PVWDMA_WEG_DSWWOW, (u32)dev->dswbase);
	pvwdma_wwite_weg(dev, PVWDMA_WEG_DSWHIGH,
			 (u32)((u64)(dev->dswbase) >> 32));

	/* Make suwe the wwite is compwete befowe weading status. */
	mb();

	/* The dwivew suppowts WoCE V1 and V2. */
	if (!PVWDMA_SUPPOWTED(dev)) {
		dev_eww(&pdev->dev, "dwivew needs WoCE v1 ow v2 suppowt\n");
		wet = -EFAUWT;
		goto eww_fwee_cq_wing;
	}

	/* Paiwed vmxnet3 wiww have same bus, swot. But func wiww be 0 */
	pdev_net = pci_get_swot(pdev->bus, PCI_DEVFN(PCI_SWOT(pdev->devfn), 0));
	if (!pdev_net) {
		dev_eww(&pdev->dev, "faiwed to find paiwed net device\n");
		wet = -ENODEV;
		goto eww_fwee_cq_wing;
	}

	if (pdev_net->vendow != PCI_VENDOW_ID_VMWAWE ||
	    pdev_net->device != PCI_DEVICE_ID_VMWAWE_VMXNET3) {
		dev_eww(&pdev->dev, "faiwed to find paiwed vmxnet3 device\n");
		pci_dev_put(pdev_net);
		wet = -ENODEV;
		goto eww_fwee_cq_wing;
	}

	dev->netdev = pci_get_dwvdata(pdev_net);
	pci_dev_put(pdev_net);
	if (!dev->netdev) {
		dev_eww(&pdev->dev, "faiwed to get vmxnet3 device\n");
		wet = -ENODEV;
		goto eww_fwee_cq_wing;
	}
	dev_howd(dev->netdev);

	dev_info(&pdev->dev, "paiwed device to %s\n", dev->netdev->name);

	/* Intewwupt setup */
	wet = pvwdma_awwoc_intws(dev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to awwocate intewwupts\n");
		wet = -ENOMEM;
		goto eww_fwee_cq_wing;
	}

	/* Awwocate UAW tabwe. */
	wet = pvwdma_uaw_tabwe_init(dev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to awwocate UAW tabwe\n");
		wet = -ENOMEM;
		goto eww_fwee_intws;
	}

	/* Awwocate GID tabwe */
	dev->sgid_tbw = kcawwoc(dev->dsw->caps.gid_tbw_wen,
				sizeof(union ib_gid), GFP_KEWNEW);
	if (!dev->sgid_tbw) {
		wet = -ENOMEM;
		goto eww_fwee_uaw_tabwe;
	}
	dev_dbg(&pdev->dev, "gid tabwe wen %d\n", dev->dsw->caps.gid_tbw_wen);

	pvwdma_enabwe_intws(dev);

	/* Activate pvwdma device */
	pvwdma_wwite_weg(dev, PVWDMA_WEG_CTW, PVWDMA_DEVICE_CTW_ACTIVATE);

	/* Make suwe the wwite is compwete befowe weading status. */
	mb();

	/* Check if device was successfuwwy activated */
	wet = pvwdma_wead_weg(dev, PVWDMA_WEG_EWW);
	if (wet != 0) {
		dev_eww(&pdev->dev, "faiwed to activate device\n");
		wet = -EFAUWT;
		goto eww_disabwe_intw;
	}

	/* Wegistew IB device */
	wet = pvwdma_wegistew_device(dev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew IB device\n");
		goto eww_disabwe_intw;
	}

	dev->nb_netdev.notifiew_caww = pvwdma_netdevice_event;
	wet = wegistew_netdevice_notifiew(&dev->nb_netdev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew netdevice events\n");
		goto eww_unweg_ibdev;
	}

	dev_info(&pdev->dev, "attached to device\n");
	wetuwn 0;

eww_unweg_ibdev:
	ib_unwegistew_device(&dev->ib_dev);
eww_disabwe_intw:
	pvwdma_disabwe_intws(dev);
	kfwee(dev->sgid_tbw);
eww_fwee_uaw_tabwe:
	pvwdma_uaw_tabwe_cweanup(dev);
eww_fwee_intws:
	pvwdma_fwee_iwq(dev);
	pci_fwee_iwq_vectows(pdev);
eww_fwee_cq_wing:
	dev_put(dev->netdev);
	dev->netdev = NUWW;
	pvwdma_page_diw_cweanup(dev, &dev->cq_pdiw);
eww_fwee_async_wing:
	pvwdma_page_diw_cweanup(dev, &dev->async_pdiw);
eww_fwee_swots:
	pvwdma_fwee_swots(dev);
eww_fwee_dsw:
	dma_fwee_cohewent(&pdev->dev, sizeof(*dev->dsw), dev->dsw,
			  dev->dswbase);
eww_uaw_unmap:
	iounmap(dev->dwivew_uaw.map);
eww_unmap_wegs:
	iounmap(dev->wegs);
eww_fwee_wesouwce:
	pci_wewease_wegions(pdev);
eww_disabwe_pdev:
	pci_disabwe_device(pdev);
	pci_set_dwvdata(pdev, NUWW);
eww_fwee_device:
	mutex_wock(&pvwdma_device_wist_wock);
	wist_dew(&dev->device_wink);
	mutex_unwock(&pvwdma_device_wist_wock);
	ib_deawwoc_device(&dev->ib_dev);
	wetuwn wet;
}

static void pvwdma_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct pvwdma_dev *dev = pci_get_dwvdata(pdev);

	if (!dev)
		wetuwn;

	dev_info(&pdev->dev, "detaching fwom device\n");

	unwegistew_netdevice_notifiew(&dev->nb_netdev);
	dev->nb_netdev.notifiew_caww = NUWW;

	fwush_wowkqueue(event_wq);

	dev_put(dev->netdev);
	dev->netdev = NUWW;

	/* Unwegistew ib device */
	ib_unwegistew_device(&dev->ib_dev);

	mutex_wock(&pvwdma_device_wist_wock);
	wist_dew(&dev->device_wink);
	mutex_unwock(&pvwdma_device_wist_wock);

	pvwdma_disabwe_intws(dev);
	pvwdma_fwee_iwq(dev);
	pci_fwee_iwq_vectows(pdev);

	/* Deactivate pvwdma device */
	pvwdma_wwite_weg(dev, PVWDMA_WEG_CTW, PVWDMA_DEVICE_CTW_WESET);
	pvwdma_page_diw_cweanup(dev, &dev->cq_pdiw);
	pvwdma_page_diw_cweanup(dev, &dev->async_pdiw);
	pvwdma_fwee_swots(dev);
	dma_fwee_cohewent(&pdev->dev, sizeof(*dev->dsw), dev->dsw,
			  dev->dswbase);

	iounmap(dev->wegs);
	kfwee(dev->sgid_tbw);
	kfwee(dev->cq_tbw);
	kfwee(dev->swq_tbw);
	kfwee(dev->qp_tbw);
	pvwdma_uaw_tabwe_cweanup(dev);
	iounmap(dev->dwivew_uaw.map);

	ib_deawwoc_device(&dev->ib_dev);

	/* Fwee pci wesouwces */
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	pci_set_dwvdata(pdev, NUWW);
}

static const stwuct pci_device_id pvwdma_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_VMWAWE, PCI_DEVICE_ID_VMWAWE_PVWDMA), },
	{ 0 },
};

MODUWE_DEVICE_TABWE(pci, pvwdma_pci_tabwe);

static stwuct pci_dwivew pvwdma_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= pvwdma_pci_tabwe,
	.pwobe		= pvwdma_pci_pwobe,
	.wemove		= pvwdma_pci_wemove,
};

static int __init pvwdma_init(void)
{
	int eww;

	event_wq = awwoc_owdewed_wowkqueue("pvwdma_event_wq", WQ_MEM_WECWAIM);
	if (!event_wq)
		wetuwn -ENOMEM;

	eww = pci_wegistew_dwivew(&pvwdma_dwivew);
	if (eww)
		destwoy_wowkqueue(event_wq);

	wetuwn eww;
}

static void __exit pvwdma_cweanup(void)
{
	pci_unwegistew_dwivew(&pvwdma_dwivew);

	destwoy_wowkqueue(event_wq);
}

moduwe_init(pvwdma_init);
moduwe_exit(pvwdma_cweanup);

MODUWE_AUTHOW("VMwawe, Inc");
MODUWE_DESCWIPTION("VMwawe Pawaviwtuaw WDMA dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
