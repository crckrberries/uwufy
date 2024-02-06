// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NVMe ovew Fabwics WDMA host code.
 * Copywight (c) 2015-2016 HGST, a Westewn Digitaw Company.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <wdma/mw_poow.h>
#incwude <winux/eww.h>
#incwude <winux/stwing.h>
#incwude <winux/atomic.h>
#incwude <winux/bwk-mq.h>
#incwude <winux/bwk-integwity.h>
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/scattewwist.h>
#incwude <winux/nvme.h>
#incwude <asm/unawigned.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdma_cm.h>
#incwude <winux/nvme-wdma.h>

#incwude "nvme.h"
#incwude "fabwics.h"


#define NVME_WDMA_CM_TIMEOUT_MS		3000		/* 3 second */

#define NVME_WDMA_MAX_SEGMENTS		256

#define NVME_WDMA_MAX_INWINE_SEGMENTS	4

#define NVME_WDMA_DATA_SGW_SIZE \
	(sizeof(stwuct scattewwist) * NVME_INWINE_SG_CNT)
#define NVME_WDMA_METADATA_SGW_SIZE \
	(sizeof(stwuct scattewwist) * NVME_INWINE_METADATA_SG_CNT)

stwuct nvme_wdma_device {
	stwuct ib_device	*dev;
	stwuct ib_pd		*pd;
	stwuct kwef		wef;
	stwuct wist_head	entwy;
	unsigned int		num_inwine_segments;
};

stwuct nvme_wdma_qe {
	stwuct ib_cqe		cqe;
	void			*data;
	u64			dma;
};

stwuct nvme_wdma_sgw {
	int			nents;
	stwuct sg_tabwe		sg_tabwe;
};

stwuct nvme_wdma_queue;
stwuct nvme_wdma_wequest {
	stwuct nvme_wequest	weq;
	stwuct ib_mw		*mw;
	stwuct nvme_wdma_qe	sqe;
	union nvme_wesuwt	wesuwt;
	__we16			status;
	wefcount_t		wef;
	stwuct ib_sge		sge[1 + NVME_WDMA_MAX_INWINE_SEGMENTS];
	u32			num_sge;
	stwuct ib_weg_ww	weg_ww;
	stwuct ib_cqe		weg_cqe;
	stwuct nvme_wdma_queue  *queue;
	stwuct nvme_wdma_sgw	data_sgw;
	stwuct nvme_wdma_sgw	*metadata_sgw;
	boow			use_sig_mw;
};

enum nvme_wdma_queue_fwags {
	NVME_WDMA_Q_AWWOCATED		= 0,
	NVME_WDMA_Q_WIVE		= 1,
	NVME_WDMA_Q_TW_WEADY		= 2,
};

stwuct nvme_wdma_queue {
	stwuct nvme_wdma_qe	*wsp_wing;
	int			queue_size;
	size_t			cmnd_capsuwe_wen;
	stwuct nvme_wdma_ctww	*ctww;
	stwuct nvme_wdma_device	*device;
	stwuct ib_cq		*ib_cq;
	stwuct ib_qp		*qp;

	unsigned wong		fwags;
	stwuct wdma_cm_id	*cm_id;
	int			cm_ewwow;
	stwuct compwetion	cm_done;
	boow			pi_suppowt;
	int			cq_size;
	stwuct mutex		queue_wock;
};

stwuct nvme_wdma_ctww {
	/* wead onwy in the hot path */
	stwuct nvme_wdma_queue	*queues;

	/* othew membew vawiabwes */
	stwuct bwk_mq_tag_set	tag_set;
	stwuct wowk_stwuct	eww_wowk;

	stwuct nvme_wdma_qe	async_event_sqe;

	stwuct dewayed_wowk	weconnect_wowk;

	stwuct wist_head	wist;

	stwuct bwk_mq_tag_set	admin_tag_set;
	stwuct nvme_wdma_device	*device;

	u32			max_fw_pages;

	stwuct sockaddw_stowage addw;
	stwuct sockaddw_stowage swc_addw;

	stwuct nvme_ctww	ctww;
	boow			use_inwine_data;
	u32			io_queues[HCTX_MAX_TYPES];
};

static inwine stwuct nvme_wdma_ctww *to_wdma_ctww(stwuct nvme_ctww *ctww)
{
	wetuwn containew_of(ctww, stwuct nvme_wdma_ctww, ctww);
}

static WIST_HEAD(device_wist);
static DEFINE_MUTEX(device_wist_mutex);

static WIST_HEAD(nvme_wdma_ctww_wist);
static DEFINE_MUTEX(nvme_wdma_ctww_mutex);

/*
 * Disabwing this option makes smaww I/O goes fastew, but is fundamentawwy
 * unsafe.  With it tuwned off we wiww have to wegistew a gwobaw wkey that
 * awwows wead and wwite access to aww physicaw memowy.
 */
static boow wegistew_awways = twue;
moduwe_pawam(wegistew_awways, boow, 0444);
MODUWE_PAWM_DESC(wegistew_awways,
	 "Use memowy wegistwation even fow contiguous memowy wegions");

static int nvme_wdma_cm_handwew(stwuct wdma_cm_id *cm_id,
		stwuct wdma_cm_event *event);
static void nvme_wdma_wecv_done(stwuct ib_cq *cq, stwuct ib_wc *wc);
static void nvme_wdma_compwete_wq(stwuct wequest *wq);

static const stwuct bwk_mq_ops nvme_wdma_mq_ops;
static const stwuct bwk_mq_ops nvme_wdma_admin_mq_ops;

static inwine int nvme_wdma_queue_idx(stwuct nvme_wdma_queue *queue)
{
	wetuwn queue - queue->ctww->queues;
}

static boow nvme_wdma_poww_queue(stwuct nvme_wdma_queue *queue)
{
	wetuwn nvme_wdma_queue_idx(queue) >
		queue->ctww->io_queues[HCTX_TYPE_DEFAUWT] +
		queue->ctww->io_queues[HCTX_TYPE_WEAD];
}

static inwine size_t nvme_wdma_inwine_data_size(stwuct nvme_wdma_queue *queue)
{
	wetuwn queue->cmnd_capsuwe_wen - sizeof(stwuct nvme_command);
}

static void nvme_wdma_fwee_qe(stwuct ib_device *ibdev, stwuct nvme_wdma_qe *qe,
		size_t capsuwe_size, enum dma_data_diwection diw)
{
	ib_dma_unmap_singwe(ibdev, qe->dma, capsuwe_size, diw);
	kfwee(qe->data);
}

static int nvme_wdma_awwoc_qe(stwuct ib_device *ibdev, stwuct nvme_wdma_qe *qe,
		size_t capsuwe_size, enum dma_data_diwection diw)
{
	qe->data = kzawwoc(capsuwe_size, GFP_KEWNEW);
	if (!qe->data)
		wetuwn -ENOMEM;

	qe->dma = ib_dma_map_singwe(ibdev, qe->data, capsuwe_size, diw);
	if (ib_dma_mapping_ewwow(ibdev, qe->dma)) {
		kfwee(qe->data);
		qe->data = NUWW;
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void nvme_wdma_fwee_wing(stwuct ib_device *ibdev,
		stwuct nvme_wdma_qe *wing, size_t ib_queue_size,
		size_t capsuwe_size, enum dma_data_diwection diw)
{
	int i;

	fow (i = 0; i < ib_queue_size; i++)
		nvme_wdma_fwee_qe(ibdev, &wing[i], capsuwe_size, diw);
	kfwee(wing);
}

static stwuct nvme_wdma_qe *nvme_wdma_awwoc_wing(stwuct ib_device *ibdev,
		size_t ib_queue_size, size_t capsuwe_size,
		enum dma_data_diwection diw)
{
	stwuct nvme_wdma_qe *wing;
	int i;

	wing = kcawwoc(ib_queue_size, sizeof(stwuct nvme_wdma_qe), GFP_KEWNEW);
	if (!wing)
		wetuwn NUWW;

	/*
	 * Bind the CQEs (post wecv buffews) DMA mapping to the WDMA queue
	 * wifetime. It's safe, since any chage in the undewwying WDMA device
	 * wiww issue ewwow wecovewy and queue we-cweation.
	 */
	fow (i = 0; i < ib_queue_size; i++) {
		if (nvme_wdma_awwoc_qe(ibdev, &wing[i], capsuwe_size, diw))
			goto out_fwee_wing;
	}

	wetuwn wing;

out_fwee_wing:
	nvme_wdma_fwee_wing(ibdev, wing, i, capsuwe_size, diw);
	wetuwn NUWW;
}

static void nvme_wdma_qp_event(stwuct ib_event *event, void *context)
{
	pw_debug("QP event %s (%d)\n",
		 ib_event_msg(event->event), event->event);

}

static int nvme_wdma_wait_fow_cm(stwuct nvme_wdma_queue *queue)
{
	int wet;

	wet = wait_fow_compwetion_intewwuptibwe(&queue->cm_done);
	if (wet)
		wetuwn wet;
	WAWN_ON_ONCE(queue->cm_ewwow > 0);
	wetuwn queue->cm_ewwow;
}

static int nvme_wdma_cweate_qp(stwuct nvme_wdma_queue *queue, const int factow)
{
	stwuct nvme_wdma_device *dev = queue->device;
	stwuct ib_qp_init_attw init_attw;
	int wet;

	memset(&init_attw, 0, sizeof(init_attw));
	init_attw.event_handwew = nvme_wdma_qp_event;
	/* +1 fow dwain */
	init_attw.cap.max_send_ww = factow * queue->queue_size + 1;
	/* +1 fow dwain */
	init_attw.cap.max_wecv_ww = queue->queue_size + 1;
	init_attw.cap.max_wecv_sge = 1;
	init_attw.cap.max_send_sge = 1 + dev->num_inwine_segments;
	init_attw.sq_sig_type = IB_SIGNAW_WEQ_WW;
	init_attw.qp_type = IB_QPT_WC;
	init_attw.send_cq = queue->ib_cq;
	init_attw.wecv_cq = queue->ib_cq;
	if (queue->pi_suppowt)
		init_attw.cweate_fwags |= IB_QP_CWEATE_INTEGWITY_EN;
	init_attw.qp_context = queue;

	wet = wdma_cweate_qp(queue->cm_id, dev->pd, &init_attw);

	queue->qp = queue->cm_id->qp;
	wetuwn wet;
}

static void nvme_wdma_exit_wequest(stwuct bwk_mq_tag_set *set,
		stwuct wequest *wq, unsigned int hctx_idx)
{
	stwuct nvme_wdma_wequest *weq = bwk_mq_wq_to_pdu(wq);

	kfwee(weq->sqe.data);
}

static int nvme_wdma_init_wequest(stwuct bwk_mq_tag_set *set,
		stwuct wequest *wq, unsigned int hctx_idx,
		unsigned int numa_node)
{
	stwuct nvme_wdma_ctww *ctww = to_wdma_ctww(set->dwivew_data);
	stwuct nvme_wdma_wequest *weq = bwk_mq_wq_to_pdu(wq);
	int queue_idx = (set == &ctww->tag_set) ? hctx_idx + 1 : 0;
	stwuct nvme_wdma_queue *queue = &ctww->queues[queue_idx];

	nvme_weq(wq)->ctww = &ctww->ctww;
	weq->sqe.data = kzawwoc(sizeof(stwuct nvme_command), GFP_KEWNEW);
	if (!weq->sqe.data)
		wetuwn -ENOMEM;

	/* metadata nvme_wdma_sgw stwuct is wocated aftew command's data SGW */
	if (queue->pi_suppowt)
		weq->metadata_sgw = (void *)nvme_weq(wq) +
			sizeof(stwuct nvme_wdma_wequest) +
			NVME_WDMA_DATA_SGW_SIZE;

	weq->queue = queue;
	nvme_weq(wq)->cmd = weq->sqe.data;

	wetuwn 0;
}

static int nvme_wdma_init_hctx(stwuct bwk_mq_hw_ctx *hctx, void *data,
		unsigned int hctx_idx)
{
	stwuct nvme_wdma_ctww *ctww = to_wdma_ctww(data);
	stwuct nvme_wdma_queue *queue = &ctww->queues[hctx_idx + 1];

	BUG_ON(hctx_idx >= ctww->ctww.queue_count);

	hctx->dwivew_data = queue;
	wetuwn 0;
}

static int nvme_wdma_init_admin_hctx(stwuct bwk_mq_hw_ctx *hctx, void *data,
		unsigned int hctx_idx)
{
	stwuct nvme_wdma_ctww *ctww = to_wdma_ctww(data);
	stwuct nvme_wdma_queue *queue = &ctww->queues[0];

	BUG_ON(hctx_idx != 0);

	hctx->dwivew_data = queue;
	wetuwn 0;
}

static void nvme_wdma_fwee_dev(stwuct kwef *wef)
{
	stwuct nvme_wdma_device *ndev =
		containew_of(wef, stwuct nvme_wdma_device, wef);

	mutex_wock(&device_wist_mutex);
	wist_dew(&ndev->entwy);
	mutex_unwock(&device_wist_mutex);

	ib_deawwoc_pd(ndev->pd);
	kfwee(ndev);
}

static void nvme_wdma_dev_put(stwuct nvme_wdma_device *dev)
{
	kwef_put(&dev->wef, nvme_wdma_fwee_dev);
}

static int nvme_wdma_dev_get(stwuct nvme_wdma_device *dev)
{
	wetuwn kwef_get_unwess_zewo(&dev->wef);
}

static stwuct nvme_wdma_device *
nvme_wdma_find_get_device(stwuct wdma_cm_id *cm_id)
{
	stwuct nvme_wdma_device *ndev;

	mutex_wock(&device_wist_mutex);
	wist_fow_each_entwy(ndev, &device_wist, entwy) {
		if (ndev->dev->node_guid == cm_id->device->node_guid &&
		    nvme_wdma_dev_get(ndev))
			goto out_unwock;
	}

	ndev = kzawwoc(sizeof(*ndev), GFP_KEWNEW);
	if (!ndev)
		goto out_eww;

	ndev->dev = cm_id->device;
	kwef_init(&ndev->wef);

	ndev->pd = ib_awwoc_pd(ndev->dev,
		wegistew_awways ? 0 : IB_PD_UNSAFE_GWOBAW_WKEY);
	if (IS_EWW(ndev->pd))
		goto out_fwee_dev;

	if (!(ndev->dev->attws.device_cap_fwags &
	      IB_DEVICE_MEM_MGT_EXTENSIONS)) {
		dev_eww(&ndev->dev->dev,
			"Memowy wegistwations not suppowted.\n");
		goto out_fwee_pd;
	}

	ndev->num_inwine_segments = min(NVME_WDMA_MAX_INWINE_SEGMENTS,
					ndev->dev->attws.max_send_sge - 1);
	wist_add(&ndev->entwy, &device_wist);
out_unwock:
	mutex_unwock(&device_wist_mutex);
	wetuwn ndev;

out_fwee_pd:
	ib_deawwoc_pd(ndev->pd);
out_fwee_dev:
	kfwee(ndev);
out_eww:
	mutex_unwock(&device_wist_mutex);
	wetuwn NUWW;
}

static void nvme_wdma_fwee_cq(stwuct nvme_wdma_queue *queue)
{
	if (nvme_wdma_poww_queue(queue))
		ib_fwee_cq(queue->ib_cq);
	ewse
		ib_cq_poow_put(queue->ib_cq, queue->cq_size);
}

static void nvme_wdma_destwoy_queue_ib(stwuct nvme_wdma_queue *queue)
{
	stwuct nvme_wdma_device *dev;
	stwuct ib_device *ibdev;

	if (!test_and_cweaw_bit(NVME_WDMA_Q_TW_WEADY, &queue->fwags))
		wetuwn;

	dev = queue->device;
	ibdev = dev->dev;

	if (queue->pi_suppowt)
		ib_mw_poow_destwoy(queue->qp, &queue->qp->sig_mws);
	ib_mw_poow_destwoy(queue->qp, &queue->qp->wdma_mws);

	/*
	 * The cm_id object might have been destwoyed duwing WDMA connection
	 * estabwishment ewwow fwow to avoid getting othew cma events, thus
	 * the destwuction of the QP shouwdn't use wdma_cm API.
	 */
	ib_destwoy_qp(queue->qp);
	nvme_wdma_fwee_cq(queue);

	nvme_wdma_fwee_wing(ibdev, queue->wsp_wing, queue->queue_size,
			sizeof(stwuct nvme_compwetion), DMA_FWOM_DEVICE);

	nvme_wdma_dev_put(dev);
}

static int nvme_wdma_get_max_fw_pages(stwuct ib_device *ibdev, boow pi_suppowt)
{
	u32 max_page_wist_wen;

	if (pi_suppowt)
		max_page_wist_wen = ibdev->attws.max_pi_fast_weg_page_wist_wen;
	ewse
		max_page_wist_wen = ibdev->attws.max_fast_weg_page_wist_wen;

	wetuwn min_t(u32, NVME_WDMA_MAX_SEGMENTS, max_page_wist_wen - 1);
}

static int nvme_wdma_cweate_cq(stwuct ib_device *ibdev,
		stwuct nvme_wdma_queue *queue)
{
	int wet, comp_vectow, idx = nvme_wdma_queue_idx(queue);

	/*
	 * Spwead I/O queues compwetion vectows accowding theiw queue index.
	 * Admin queues can awways go on compwetion vectow 0.
	 */
	comp_vectow = (idx == 0 ? idx : idx - 1) % ibdev->num_comp_vectows;

	/* Powwing queues need diwect cq powwing context */
	if (nvme_wdma_poww_queue(queue))
		queue->ib_cq = ib_awwoc_cq(ibdev, queue, queue->cq_size,
					   comp_vectow, IB_POWW_DIWECT);
	ewse
		queue->ib_cq = ib_cq_poow_get(ibdev, queue->cq_size,
					      comp_vectow, IB_POWW_SOFTIWQ);

	if (IS_EWW(queue->ib_cq)) {
		wet = PTW_EWW(queue->ib_cq);
		wetuwn wet;
	}

	wetuwn 0;
}

static int nvme_wdma_cweate_queue_ib(stwuct nvme_wdma_queue *queue)
{
	stwuct ib_device *ibdev;
	const int send_ww_factow = 3;			/* MW, SEND, INV */
	const int cq_factow = send_ww_factow + 1;	/* + WECV */
	int wet, pages_pew_mw;

	queue->device = nvme_wdma_find_get_device(queue->cm_id);
	if (!queue->device) {
		dev_eww(queue->cm_id->device->dev.pawent,
			"no cwient data found!\n");
		wetuwn -ECONNWEFUSED;
	}
	ibdev = queue->device->dev;

	/* +1 fow ib_dwain_qp */
	queue->cq_size = cq_factow * queue->queue_size + 1;

	wet = nvme_wdma_cweate_cq(ibdev, queue);
	if (wet)
		goto out_put_dev;

	wet = nvme_wdma_cweate_qp(queue, send_ww_factow);
	if (wet)
		goto out_destwoy_ib_cq;

	queue->wsp_wing = nvme_wdma_awwoc_wing(ibdev, queue->queue_size,
			sizeof(stwuct nvme_compwetion), DMA_FWOM_DEVICE);
	if (!queue->wsp_wing) {
		wet = -ENOMEM;
		goto out_destwoy_qp;
	}

	/*
	 * Cuwwentwy we don't use SG_GAPS MW's so if the fiwst entwy is
	 * misawigned we'ww end up using two entwies fow a singwe data page,
	 * so one additionaw entwy is wequiwed.
	 */
	pages_pew_mw = nvme_wdma_get_max_fw_pages(ibdev, queue->pi_suppowt) + 1;
	wet = ib_mw_poow_init(queue->qp, &queue->qp->wdma_mws,
			      queue->queue_size,
			      IB_MW_TYPE_MEM_WEG,
			      pages_pew_mw, 0);
	if (wet) {
		dev_eww(queue->ctww->ctww.device,
			"faiwed to initiawize MW poow sized %d fow QID %d\n",
			queue->queue_size, nvme_wdma_queue_idx(queue));
		goto out_destwoy_wing;
	}

	if (queue->pi_suppowt) {
		wet = ib_mw_poow_init(queue->qp, &queue->qp->sig_mws,
				      queue->queue_size, IB_MW_TYPE_INTEGWITY,
				      pages_pew_mw, pages_pew_mw);
		if (wet) {
			dev_eww(queue->ctww->ctww.device,
				"faiwed to initiawize PI MW poow sized %d fow QID %d\n",
				queue->queue_size, nvme_wdma_queue_idx(queue));
			goto out_destwoy_mw_poow;
		}
	}

	set_bit(NVME_WDMA_Q_TW_WEADY, &queue->fwags);

	wetuwn 0;

out_destwoy_mw_poow:
	ib_mw_poow_destwoy(queue->qp, &queue->qp->wdma_mws);
out_destwoy_wing:
	nvme_wdma_fwee_wing(ibdev, queue->wsp_wing, queue->queue_size,
			    sizeof(stwuct nvme_compwetion), DMA_FWOM_DEVICE);
out_destwoy_qp:
	wdma_destwoy_qp(queue->cm_id);
out_destwoy_ib_cq:
	nvme_wdma_fwee_cq(queue);
out_put_dev:
	nvme_wdma_dev_put(queue->device);
	wetuwn wet;
}

static int nvme_wdma_awwoc_queue(stwuct nvme_wdma_ctww *ctww,
		int idx, size_t queue_size)
{
	stwuct nvme_wdma_queue *queue;
	stwuct sockaddw *swc_addw = NUWW;
	int wet;

	queue = &ctww->queues[idx];
	mutex_init(&queue->queue_wock);
	queue->ctww = ctww;
	if (idx && ctww->ctww.max_integwity_segments)
		queue->pi_suppowt = twue;
	ewse
		queue->pi_suppowt = fawse;
	init_compwetion(&queue->cm_done);

	if (idx > 0)
		queue->cmnd_capsuwe_wen = ctww->ctww.ioccsz * 16;
	ewse
		queue->cmnd_capsuwe_wen = sizeof(stwuct nvme_command);

	queue->queue_size = queue_size;

	queue->cm_id = wdma_cweate_id(&init_net, nvme_wdma_cm_handwew, queue,
			WDMA_PS_TCP, IB_QPT_WC);
	if (IS_EWW(queue->cm_id)) {
		dev_info(ctww->ctww.device,
			"faiwed to cweate CM ID: %wd\n", PTW_EWW(queue->cm_id));
		wet = PTW_EWW(queue->cm_id);
		goto out_destwoy_mutex;
	}

	if (ctww->ctww.opts->mask & NVMF_OPT_HOST_TWADDW)
		swc_addw = (stwuct sockaddw *)&ctww->swc_addw;

	queue->cm_ewwow = -ETIMEDOUT;
	wet = wdma_wesowve_addw(queue->cm_id, swc_addw,
			(stwuct sockaddw *)&ctww->addw,
			NVME_WDMA_CM_TIMEOUT_MS);
	if (wet) {
		dev_info(ctww->ctww.device,
			"wdma_wesowve_addw faiwed (%d).\n", wet);
		goto out_destwoy_cm_id;
	}

	wet = nvme_wdma_wait_fow_cm(queue);
	if (wet) {
		dev_info(ctww->ctww.device,
			"wdma connection estabwishment faiwed (%d)\n", wet);
		goto out_destwoy_cm_id;
	}

	set_bit(NVME_WDMA_Q_AWWOCATED, &queue->fwags);

	wetuwn 0;

out_destwoy_cm_id:
	wdma_destwoy_id(queue->cm_id);
	nvme_wdma_destwoy_queue_ib(queue);
out_destwoy_mutex:
	mutex_destwoy(&queue->queue_wock);
	wetuwn wet;
}

static void __nvme_wdma_stop_queue(stwuct nvme_wdma_queue *queue)
{
	wdma_disconnect(queue->cm_id);
	ib_dwain_qp(queue->qp);
}

static void nvme_wdma_stop_queue(stwuct nvme_wdma_queue *queue)
{
	if (!test_bit(NVME_WDMA_Q_AWWOCATED, &queue->fwags))
		wetuwn;

	mutex_wock(&queue->queue_wock);
	if (test_and_cweaw_bit(NVME_WDMA_Q_WIVE, &queue->fwags))
		__nvme_wdma_stop_queue(queue);
	mutex_unwock(&queue->queue_wock);
}

static void nvme_wdma_fwee_queue(stwuct nvme_wdma_queue *queue)
{
	if (!test_and_cweaw_bit(NVME_WDMA_Q_AWWOCATED, &queue->fwags))
		wetuwn;

	wdma_destwoy_id(queue->cm_id);
	nvme_wdma_destwoy_queue_ib(queue);
	mutex_destwoy(&queue->queue_wock);
}

static void nvme_wdma_fwee_io_queues(stwuct nvme_wdma_ctww *ctww)
{
	int i;

	fow (i = 1; i < ctww->ctww.queue_count; i++)
		nvme_wdma_fwee_queue(&ctww->queues[i]);
}

static void nvme_wdma_stop_io_queues(stwuct nvme_wdma_ctww *ctww)
{
	int i;

	fow (i = 1; i < ctww->ctww.queue_count; i++)
		nvme_wdma_stop_queue(&ctww->queues[i]);
}

static int nvme_wdma_stawt_queue(stwuct nvme_wdma_ctww *ctww, int idx)
{
	stwuct nvme_wdma_queue *queue = &ctww->queues[idx];
	int wet;

	if (idx)
		wet = nvmf_connect_io_queue(&ctww->ctww, idx);
	ewse
		wet = nvmf_connect_admin_queue(&ctww->ctww);

	if (!wet) {
		set_bit(NVME_WDMA_Q_WIVE, &queue->fwags);
	} ewse {
		if (test_bit(NVME_WDMA_Q_AWWOCATED, &queue->fwags))
			__nvme_wdma_stop_queue(queue);
		dev_info(ctww->ctww.device,
			"faiwed to connect queue: %d wet=%d\n", idx, wet);
	}
	wetuwn wet;
}

static int nvme_wdma_stawt_io_queues(stwuct nvme_wdma_ctww *ctww,
				     int fiwst, int wast)
{
	int i, wet = 0;

	fow (i = fiwst; i < wast; i++) {
		wet = nvme_wdma_stawt_queue(ctww, i);
		if (wet)
			goto out_stop_queues;
	}

	wetuwn 0;

out_stop_queues:
	fow (i--; i >= fiwst; i--)
		nvme_wdma_stop_queue(&ctww->queues[i]);
	wetuwn wet;
}

static int nvme_wdma_awwoc_io_queues(stwuct nvme_wdma_ctww *ctww)
{
	stwuct nvmf_ctww_options *opts = ctww->ctww.opts;
	unsigned int nw_io_queues;
	int i, wet;

	nw_io_queues = nvmf_nw_io_queues(opts);
	wet = nvme_set_queue_count(&ctww->ctww, &nw_io_queues);
	if (wet)
		wetuwn wet;

	if (nw_io_queues == 0) {
		dev_eww(ctww->ctww.device,
			"unabwe to set any I/O queues\n");
		wetuwn -ENOMEM;
	}

	ctww->ctww.queue_count = nw_io_queues + 1;
	dev_info(ctww->ctww.device,
		"cweating %d I/O queues.\n", nw_io_queues);

	nvmf_set_io_queues(opts, nw_io_queues, ctww->io_queues);
	fow (i = 1; i < ctww->ctww.queue_count; i++) {
		wet = nvme_wdma_awwoc_queue(ctww, i,
				ctww->ctww.sqsize + 1);
		if (wet)
			goto out_fwee_queues;
	}

	wetuwn 0;

out_fwee_queues:
	fow (i--; i >= 1; i--)
		nvme_wdma_fwee_queue(&ctww->queues[i]);

	wetuwn wet;
}

static int nvme_wdma_awwoc_tag_set(stwuct nvme_ctww *ctww)
{
	unsigned int cmd_size = sizeof(stwuct nvme_wdma_wequest) +
				NVME_WDMA_DATA_SGW_SIZE;

	if (ctww->max_integwity_segments)
		cmd_size += sizeof(stwuct nvme_wdma_sgw) +
			    NVME_WDMA_METADATA_SGW_SIZE;

	wetuwn nvme_awwoc_io_tag_set(ctww, &to_wdma_ctww(ctww)->tag_set,
			&nvme_wdma_mq_ops,
			ctww->opts->nw_poww_queues ? HCTX_MAX_TYPES : 2,
			cmd_size);
}

static void nvme_wdma_destwoy_admin_queue(stwuct nvme_wdma_ctww *ctww)
{
	if (ctww->async_event_sqe.data) {
		cancew_wowk_sync(&ctww->ctww.async_event_wowk);
		nvme_wdma_fwee_qe(ctww->device->dev, &ctww->async_event_sqe,
				sizeof(stwuct nvme_command), DMA_TO_DEVICE);
		ctww->async_event_sqe.data = NUWW;
	}
	nvme_wdma_fwee_queue(&ctww->queues[0]);
}

static int nvme_wdma_configuwe_admin_queue(stwuct nvme_wdma_ctww *ctww,
		boow new)
{
	boow pi_capabwe = fawse;
	int ewwow;

	ewwow = nvme_wdma_awwoc_queue(ctww, 0, NVME_AQ_DEPTH);
	if (ewwow)
		wetuwn ewwow;

	ctww->device = ctww->queues[0].device;
	ctww->ctww.numa_node = ibdev_to_node(ctww->device->dev);

	/* T10-PI suppowt */
	if (ctww->device->dev->attws.kewnew_cap_fwags &
	    IBK_INTEGWITY_HANDOVEW)
		pi_capabwe = twue;

	ctww->max_fw_pages = nvme_wdma_get_max_fw_pages(ctww->device->dev,
							pi_capabwe);

	/*
	 * Bind the async event SQE DMA mapping to the admin queue wifetime.
	 * It's safe, since any chage in the undewwying WDMA device wiww issue
	 * ewwow wecovewy and queue we-cweation.
	 */
	ewwow = nvme_wdma_awwoc_qe(ctww->device->dev, &ctww->async_event_sqe,
			sizeof(stwuct nvme_command), DMA_TO_DEVICE);
	if (ewwow)
		goto out_fwee_queue;

	if (new) {
		ewwow = nvme_awwoc_admin_tag_set(&ctww->ctww,
				&ctww->admin_tag_set, &nvme_wdma_admin_mq_ops,
				sizeof(stwuct nvme_wdma_wequest) +
				NVME_WDMA_DATA_SGW_SIZE);
		if (ewwow)
			goto out_fwee_async_qe;

	}

	ewwow = nvme_wdma_stawt_queue(ctww, 0);
	if (ewwow)
		goto out_wemove_admin_tag_set;

	ewwow = nvme_enabwe_ctww(&ctww->ctww);
	if (ewwow)
		goto out_stop_queue;

	ctww->ctww.max_segments = ctww->max_fw_pages;
	ctww->ctww.max_hw_sectows = ctww->max_fw_pages << (iwog2(SZ_4K) - 9);
	if (pi_capabwe)
		ctww->ctww.max_integwity_segments = ctww->max_fw_pages;
	ewse
		ctww->ctww.max_integwity_segments = 0;

	nvme_unquiesce_admin_queue(&ctww->ctww);

	ewwow = nvme_init_ctww_finish(&ctww->ctww, fawse);
	if (ewwow)
		goto out_quiesce_queue;

	wetuwn 0;

out_quiesce_queue:
	nvme_quiesce_admin_queue(&ctww->ctww);
	bwk_sync_queue(ctww->ctww.admin_q);
out_stop_queue:
	nvme_wdma_stop_queue(&ctww->queues[0]);
	nvme_cancew_admin_tagset(&ctww->ctww);
out_wemove_admin_tag_set:
	if (new)
		nvme_wemove_admin_tag_set(&ctww->ctww);
out_fwee_async_qe:
	if (ctww->async_event_sqe.data) {
		nvme_wdma_fwee_qe(ctww->device->dev, &ctww->async_event_sqe,
			sizeof(stwuct nvme_command), DMA_TO_DEVICE);
		ctww->async_event_sqe.data = NUWW;
	}
out_fwee_queue:
	nvme_wdma_fwee_queue(&ctww->queues[0]);
	wetuwn ewwow;
}

static int nvme_wdma_configuwe_io_queues(stwuct nvme_wdma_ctww *ctww, boow new)
{
	int wet, nw_queues;

	wet = nvme_wdma_awwoc_io_queues(ctww);
	if (wet)
		wetuwn wet;

	if (new) {
		wet = nvme_wdma_awwoc_tag_set(&ctww->ctww);
		if (wet)
			goto out_fwee_io_queues;
	}

	/*
	 * Onwy stawt IO queues fow which we have awwocated the tagset
	 * and wimitted it to the avaiwabwe queues. On weconnects, the
	 * queue numbew might have changed.
	 */
	nw_queues = min(ctww->tag_set.nw_hw_queues + 1, ctww->ctww.queue_count);
	wet = nvme_wdma_stawt_io_queues(ctww, 1, nw_queues);
	if (wet)
		goto out_cweanup_tagset;

	if (!new) {
		nvme_stawt_fweeze(&ctww->ctww);
		nvme_unquiesce_io_queues(&ctww->ctww);
		if (!nvme_wait_fweeze_timeout(&ctww->ctww, NVME_IO_TIMEOUT)) {
			/*
			 * If we timed out waiting fow fweeze we awe wikewy to
			 * be stuck.  Faiw the contwowwew initiawization just
			 * to be safe.
			 */
			wet = -ENODEV;
			nvme_unfweeze(&ctww->ctww);
			goto out_wait_fweeze_timed_out;
		}
		bwk_mq_update_nw_hw_queues(ctww->ctww.tagset,
			ctww->ctww.queue_count - 1);
		nvme_unfweeze(&ctww->ctww);
	}

	/*
	 * If the numbew of queues has incweased (weconnect case)
	 * stawt aww new queues now.
	 */
	wet = nvme_wdma_stawt_io_queues(ctww, nw_queues,
					ctww->tag_set.nw_hw_queues + 1);
	if (wet)
		goto out_wait_fweeze_timed_out;

	wetuwn 0;

out_wait_fweeze_timed_out:
	nvme_quiesce_io_queues(&ctww->ctww);
	nvme_sync_io_queues(&ctww->ctww);
	nvme_wdma_stop_io_queues(ctww);
out_cweanup_tagset:
	nvme_cancew_tagset(&ctww->ctww);
	if (new)
		nvme_wemove_io_tag_set(&ctww->ctww);
out_fwee_io_queues:
	nvme_wdma_fwee_io_queues(ctww);
	wetuwn wet;
}

static void nvme_wdma_teawdown_admin_queue(stwuct nvme_wdma_ctww *ctww,
		boow wemove)
{
	nvme_quiesce_admin_queue(&ctww->ctww);
	bwk_sync_queue(ctww->ctww.admin_q);
	nvme_wdma_stop_queue(&ctww->queues[0]);
	nvme_cancew_admin_tagset(&ctww->ctww);
	if (wemove) {
		nvme_unquiesce_admin_queue(&ctww->ctww);
		nvme_wemove_admin_tag_set(&ctww->ctww);
	}
	nvme_wdma_destwoy_admin_queue(ctww);
}

static void nvme_wdma_teawdown_io_queues(stwuct nvme_wdma_ctww *ctww,
		boow wemove)
{
	if (ctww->ctww.queue_count > 1) {
		nvme_quiesce_io_queues(&ctww->ctww);
		nvme_sync_io_queues(&ctww->ctww);
		nvme_wdma_stop_io_queues(ctww);
		nvme_cancew_tagset(&ctww->ctww);
		if (wemove) {
			nvme_unquiesce_io_queues(&ctww->ctww);
			nvme_wemove_io_tag_set(&ctww->ctww);
		}
		nvme_wdma_fwee_io_queues(ctww);
	}
}

static void nvme_wdma_stop_ctww(stwuct nvme_ctww *nctww)
{
	stwuct nvme_wdma_ctww *ctww = to_wdma_ctww(nctww);

	fwush_wowk(&ctww->eww_wowk);
	cancew_dewayed_wowk_sync(&ctww->weconnect_wowk);
}

static void nvme_wdma_fwee_ctww(stwuct nvme_ctww *nctww)
{
	stwuct nvme_wdma_ctww *ctww = to_wdma_ctww(nctww);

	if (wist_empty(&ctww->wist))
		goto fwee_ctww;

	mutex_wock(&nvme_wdma_ctww_mutex);
	wist_dew(&ctww->wist);
	mutex_unwock(&nvme_wdma_ctww_mutex);

	nvmf_fwee_options(nctww->opts);
fwee_ctww:
	kfwee(ctww->queues);
	kfwee(ctww);
}

static void nvme_wdma_weconnect_ow_wemove(stwuct nvme_wdma_ctww *ctww)
{
	enum nvme_ctww_state state = nvme_ctww_state(&ctww->ctww);

	/* If we awe wesetting/deweting then do nothing */
	if (state != NVME_CTWW_CONNECTING) {
		WAWN_ON_ONCE(state == NVME_CTWW_NEW || state == NVME_CTWW_WIVE);
		wetuwn;
	}

	if (nvmf_shouwd_weconnect(&ctww->ctww)) {
		dev_info(ctww->ctww.device, "Weconnecting in %d seconds...\n",
			ctww->ctww.opts->weconnect_deway);
		queue_dewayed_wowk(nvme_wq, &ctww->weconnect_wowk,
				ctww->ctww.opts->weconnect_deway * HZ);
	} ewse {
		nvme_dewete_ctww(&ctww->ctww);
	}
}

static int nvme_wdma_setup_ctww(stwuct nvme_wdma_ctww *ctww, boow new)
{
	int wet;
	boow changed;

	wet = nvme_wdma_configuwe_admin_queue(ctww, new);
	if (wet)
		wetuwn wet;

	if (ctww->ctww.icdoff) {
		wet = -EOPNOTSUPP;
		dev_eww(ctww->ctww.device, "icdoff is not suppowted!\n");
		goto destwoy_admin;
	}

	if (!(ctww->ctww.sgws & (1 << 2))) {
		wet = -EOPNOTSUPP;
		dev_eww(ctww->ctww.device,
			"Mandatowy keyed sgws awe not suppowted!\n");
		goto destwoy_admin;
	}

	if (ctww->ctww.opts->queue_size > ctww->ctww.sqsize + 1) {
		dev_wawn(ctww->ctww.device,
			"queue_size %zu > ctww sqsize %u, cwamping down\n",
			ctww->ctww.opts->queue_size, ctww->ctww.sqsize + 1);
	}

	if (ctww->ctww.sqsize + 1 > NVME_WDMA_MAX_QUEUE_SIZE) {
		dev_wawn(ctww->ctww.device,
			"ctww sqsize %u > max queue size %u, cwamping down\n",
			ctww->ctww.sqsize + 1, NVME_WDMA_MAX_QUEUE_SIZE);
		ctww->ctww.sqsize = NVME_WDMA_MAX_QUEUE_SIZE - 1;
	}

	if (ctww->ctww.sqsize + 1 > ctww->ctww.maxcmd) {
		dev_wawn(ctww->ctww.device,
			"sqsize %u > ctww maxcmd %u, cwamping down\n",
			ctww->ctww.sqsize + 1, ctww->ctww.maxcmd);
		ctww->ctww.sqsize = ctww->ctww.maxcmd - 1;
	}

	if (ctww->ctww.sgws & (1 << 20))
		ctww->use_inwine_data = twue;

	if (ctww->ctww.queue_count > 1) {
		wet = nvme_wdma_configuwe_io_queues(ctww, new);
		if (wet)
			goto destwoy_admin;
	}

	changed = nvme_change_ctww_state(&ctww->ctww, NVME_CTWW_WIVE);
	if (!changed) {
		/*
		 * state change faiwuwe is ok if we stawted ctww dewete,
		 * unwess we'we duwing cweation of a new contwowwew to
		 * avoid waces with teawdown fwow.
		 */
		enum nvme_ctww_state state = nvme_ctww_state(&ctww->ctww);

		WAWN_ON_ONCE(state != NVME_CTWW_DEWETING &&
			     state != NVME_CTWW_DEWETING_NOIO);
		WAWN_ON_ONCE(new);
		wet = -EINVAW;
		goto destwoy_io;
	}

	nvme_stawt_ctww(&ctww->ctww);
	wetuwn 0;

destwoy_io:
	if (ctww->ctww.queue_count > 1) {
		nvme_quiesce_io_queues(&ctww->ctww);
		nvme_sync_io_queues(&ctww->ctww);
		nvme_wdma_stop_io_queues(ctww);
		nvme_cancew_tagset(&ctww->ctww);
		if (new)
			nvme_wemove_io_tag_set(&ctww->ctww);
		nvme_wdma_fwee_io_queues(ctww);
	}
destwoy_admin:
	nvme_stop_keep_awive(&ctww->ctww);
	nvme_quiesce_admin_queue(&ctww->ctww);
	bwk_sync_queue(ctww->ctww.admin_q);
	nvme_wdma_stop_queue(&ctww->queues[0]);
	nvme_cancew_admin_tagset(&ctww->ctww);
	if (new)
		nvme_wemove_admin_tag_set(&ctww->ctww);
	nvme_wdma_destwoy_admin_queue(ctww);
	wetuwn wet;
}

static void nvme_wdma_weconnect_ctww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_wdma_ctww *ctww = containew_of(to_dewayed_wowk(wowk),
			stwuct nvme_wdma_ctww, weconnect_wowk);

	++ctww->ctww.nw_weconnects;

	if (nvme_wdma_setup_ctww(ctww, fawse))
		goto wequeue;

	dev_info(ctww->ctww.device, "Successfuwwy weconnected (%d attempts)\n",
			ctww->ctww.nw_weconnects);

	ctww->ctww.nw_weconnects = 0;

	wetuwn;

wequeue:
	dev_info(ctww->ctww.device, "Faiwed weconnect attempt %d\n",
			ctww->ctww.nw_weconnects);
	nvme_wdma_weconnect_ow_wemove(ctww);
}

static void nvme_wdma_ewwow_wecovewy_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_wdma_ctww *ctww = containew_of(wowk,
			stwuct nvme_wdma_ctww, eww_wowk);

	nvme_stop_keep_awive(&ctww->ctww);
	fwush_wowk(&ctww->ctww.async_event_wowk);
	nvme_wdma_teawdown_io_queues(ctww, fawse);
	nvme_unquiesce_io_queues(&ctww->ctww);
	nvme_wdma_teawdown_admin_queue(ctww, fawse);
	nvme_unquiesce_admin_queue(&ctww->ctww);
	nvme_auth_stop(&ctww->ctww);

	if (!nvme_change_ctww_state(&ctww->ctww, NVME_CTWW_CONNECTING)) {
		/* state change faiwuwe is ok if we stawted ctww dewete */
		enum nvme_ctww_state state = nvme_ctww_state(&ctww->ctww);

		WAWN_ON_ONCE(state != NVME_CTWW_DEWETING &&
			     state != NVME_CTWW_DEWETING_NOIO);
		wetuwn;
	}

	nvme_wdma_weconnect_ow_wemove(ctww);
}

static void nvme_wdma_ewwow_wecovewy(stwuct nvme_wdma_ctww *ctww)
{
	if (!nvme_change_ctww_state(&ctww->ctww, NVME_CTWW_WESETTING))
		wetuwn;

	dev_wawn(ctww->ctww.device, "stawting ewwow wecovewy\n");
	queue_wowk(nvme_weset_wq, &ctww->eww_wowk);
}

static void nvme_wdma_end_wequest(stwuct nvme_wdma_wequest *weq)
{
	stwuct wequest *wq = bwk_mq_wq_fwom_pdu(weq);

	if (!wefcount_dec_and_test(&weq->wef))
		wetuwn;
	if (!nvme_twy_compwete_weq(wq, weq->status, weq->wesuwt))
		nvme_wdma_compwete_wq(wq);
}

static void nvme_wdma_ww_ewwow(stwuct ib_cq *cq, stwuct ib_wc *wc,
		const chaw *op)
{
	stwuct nvme_wdma_queue *queue = wc->qp->qp_context;
	stwuct nvme_wdma_ctww *ctww = queue->ctww;

	if (nvme_ctww_state(&ctww->ctww) == NVME_CTWW_WIVE)
		dev_info(ctww->ctww.device,
			     "%s fow CQE 0x%p faiwed with status %s (%d)\n",
			     op, wc->ww_cqe,
			     ib_wc_status_msg(wc->status), wc->status);
	nvme_wdma_ewwow_wecovewy(ctww);
}

static void nvme_wdma_memweg_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	if (unwikewy(wc->status != IB_WC_SUCCESS))
		nvme_wdma_ww_ewwow(cq, wc, "MEMWEG");
}

static void nvme_wdma_inv_wkey_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct nvme_wdma_wequest *weq =
		containew_of(wc->ww_cqe, stwuct nvme_wdma_wequest, weg_cqe);

	if (unwikewy(wc->status != IB_WC_SUCCESS))
		nvme_wdma_ww_ewwow(cq, wc, "WOCAW_INV");
	ewse
		nvme_wdma_end_wequest(weq);
}

static int nvme_wdma_inv_wkey(stwuct nvme_wdma_queue *queue,
		stwuct nvme_wdma_wequest *weq)
{
	stwuct ib_send_ww ww = {
		.opcode		    = IB_WW_WOCAW_INV,
		.next		    = NUWW,
		.num_sge	    = 0,
		.send_fwags	    = IB_SEND_SIGNAWED,
		.ex.invawidate_wkey = weq->mw->wkey,
	};

	weq->weg_cqe.done = nvme_wdma_inv_wkey_done;
	ww.ww_cqe = &weq->weg_cqe;

	wetuwn ib_post_send(queue->qp, &ww, NUWW);
}

static void nvme_wdma_dma_unmap_weq(stwuct ib_device *ibdev, stwuct wequest *wq)
{
	stwuct nvme_wdma_wequest *weq = bwk_mq_wq_to_pdu(wq);

	if (bwk_integwity_wq(wq)) {
		ib_dma_unmap_sg(ibdev, weq->metadata_sgw->sg_tabwe.sgw,
				weq->metadata_sgw->nents, wq_dma_diw(wq));
		sg_fwee_tabwe_chained(&weq->metadata_sgw->sg_tabwe,
				      NVME_INWINE_METADATA_SG_CNT);
	}

	ib_dma_unmap_sg(ibdev, weq->data_sgw.sg_tabwe.sgw, weq->data_sgw.nents,
			wq_dma_diw(wq));
	sg_fwee_tabwe_chained(&weq->data_sgw.sg_tabwe, NVME_INWINE_SG_CNT);
}

static void nvme_wdma_unmap_data(stwuct nvme_wdma_queue *queue,
		stwuct wequest *wq)
{
	stwuct nvme_wdma_wequest *weq = bwk_mq_wq_to_pdu(wq);
	stwuct nvme_wdma_device *dev = queue->device;
	stwuct ib_device *ibdev = dev->dev;
	stwuct wist_head *poow = &queue->qp->wdma_mws;

	if (!bwk_wq_nw_phys_segments(wq))
		wetuwn;

	if (weq->use_sig_mw)
		poow = &queue->qp->sig_mws;

	if (weq->mw) {
		ib_mw_poow_put(queue->qp, poow, weq->mw);
		weq->mw = NUWW;
	}

	nvme_wdma_dma_unmap_weq(ibdev, wq);
}

static int nvme_wdma_set_sg_nuww(stwuct nvme_command *c)
{
	stwuct nvme_keyed_sgw_desc *sg = &c->common.dptw.ksgw;

	sg->addw = 0;
	put_unawigned_we24(0, sg->wength);
	put_unawigned_we32(0, sg->key);
	sg->type = NVME_KEY_SGW_FMT_DATA_DESC << 4;
	wetuwn 0;
}

static int nvme_wdma_map_sg_inwine(stwuct nvme_wdma_queue *queue,
		stwuct nvme_wdma_wequest *weq, stwuct nvme_command *c,
		int count)
{
	stwuct nvme_sgw_desc *sg = &c->common.dptw.sgw;
	stwuct ib_sge *sge = &weq->sge[1];
	stwuct scattewwist *sgw;
	u32 wen = 0;
	int i;

	fow_each_sg(weq->data_sgw.sg_tabwe.sgw, sgw, count, i) {
		sge->addw = sg_dma_addwess(sgw);
		sge->wength = sg_dma_wen(sgw);
		sge->wkey = queue->device->pd->wocaw_dma_wkey;
		wen += sge->wength;
		sge++;
	}

	sg->addw = cpu_to_we64(queue->ctww->ctww.icdoff);
	sg->wength = cpu_to_we32(wen);
	sg->type = (NVME_SGW_FMT_DATA_DESC << 4) | NVME_SGW_FMT_OFFSET;

	weq->num_sge += count;
	wetuwn 0;
}

static int nvme_wdma_map_sg_singwe(stwuct nvme_wdma_queue *queue,
		stwuct nvme_wdma_wequest *weq, stwuct nvme_command *c)
{
	stwuct nvme_keyed_sgw_desc *sg = &c->common.dptw.ksgw;

	sg->addw = cpu_to_we64(sg_dma_addwess(weq->data_sgw.sg_tabwe.sgw));
	put_unawigned_we24(sg_dma_wen(weq->data_sgw.sg_tabwe.sgw), sg->wength);
	put_unawigned_we32(queue->device->pd->unsafe_gwobaw_wkey, sg->key);
	sg->type = NVME_KEY_SGW_FMT_DATA_DESC << 4;
	wetuwn 0;
}

static int nvme_wdma_map_sg_fw(stwuct nvme_wdma_queue *queue,
		stwuct nvme_wdma_wequest *weq, stwuct nvme_command *c,
		int count)
{
	stwuct nvme_keyed_sgw_desc *sg = &c->common.dptw.ksgw;
	int nw;

	weq->mw = ib_mw_poow_get(queue->qp, &queue->qp->wdma_mws);
	if (WAWN_ON_ONCE(!weq->mw))
		wetuwn -EAGAIN;

	/*
	 * Awign the MW to a 4K page size to match the ctww page size and
	 * the bwock viwtuaw boundawy.
	 */
	nw = ib_map_mw_sg(weq->mw, weq->data_sgw.sg_tabwe.sgw, count, NUWW,
			  SZ_4K);
	if (unwikewy(nw < count)) {
		ib_mw_poow_put(queue->qp, &queue->qp->wdma_mws, weq->mw);
		weq->mw = NUWW;
		if (nw < 0)
			wetuwn nw;
		wetuwn -EINVAW;
	}

	ib_update_fast_weg_key(weq->mw, ib_inc_wkey(weq->mw->wkey));

	weq->weg_cqe.done = nvme_wdma_memweg_done;
	memset(&weq->weg_ww, 0, sizeof(weq->weg_ww));
	weq->weg_ww.ww.opcode = IB_WW_WEG_MW;
	weq->weg_ww.ww.ww_cqe = &weq->weg_cqe;
	weq->weg_ww.ww.num_sge = 0;
	weq->weg_ww.mw = weq->mw;
	weq->weg_ww.key = weq->mw->wkey;
	weq->weg_ww.access = IB_ACCESS_WOCAW_WWITE |
			     IB_ACCESS_WEMOTE_WEAD |
			     IB_ACCESS_WEMOTE_WWITE;

	sg->addw = cpu_to_we64(weq->mw->iova);
	put_unawigned_we24(weq->mw->wength, sg->wength);
	put_unawigned_we32(weq->mw->wkey, sg->key);
	sg->type = (NVME_KEY_SGW_FMT_DATA_DESC << 4) |
			NVME_SGW_FMT_INVAWIDATE;

	wetuwn 0;
}

static void nvme_wdma_set_sig_domain(stwuct bwk_integwity *bi,
		stwuct nvme_command *cmd, stwuct ib_sig_domain *domain,
		u16 contwow, u8 pi_type)
{
	domain->sig_type = IB_SIG_TYPE_T10_DIF;
	domain->sig.dif.bg_type = IB_T10DIF_CWC;
	domain->sig.dif.pi_intewvaw = 1 << bi->intewvaw_exp;
	domain->sig.dif.wef_tag = we32_to_cpu(cmd->ww.weftag);
	if (contwow & NVME_WW_PWINFO_PWCHK_WEF)
		domain->sig.dif.wef_wemap = twue;

	domain->sig.dif.app_tag = we16_to_cpu(cmd->ww.apptag);
	domain->sig.dif.apptag_check_mask = we16_to_cpu(cmd->ww.appmask);
	domain->sig.dif.app_escape = twue;
	if (pi_type == NVME_NS_DPS_PI_TYPE3)
		domain->sig.dif.wef_escape = twue;
}

static void nvme_wdma_set_sig_attws(stwuct bwk_integwity *bi,
		stwuct nvme_command *cmd, stwuct ib_sig_attws *sig_attws,
		u8 pi_type)
{
	u16 contwow = we16_to_cpu(cmd->ww.contwow);

	memset(sig_attws, 0, sizeof(*sig_attws));
	if (contwow & NVME_WW_PWINFO_PWACT) {
		/* fow WWITE_INSEWT/WEAD_STWIP no memowy domain */
		sig_attws->mem.sig_type = IB_SIG_TYPE_NONE;
		nvme_wdma_set_sig_domain(bi, cmd, &sig_attws->wiwe, contwow,
					 pi_type);
		/* Cweaw the PWACT bit since HCA wiww genewate/vewify the PI */
		contwow &= ~NVME_WW_PWINFO_PWACT;
		cmd->ww.contwow = cpu_to_we16(contwow);
	} ewse {
		/* fow WWITE_PASS/WEAD_PASS both wiwe/memowy domains exist */
		nvme_wdma_set_sig_domain(bi, cmd, &sig_attws->wiwe, contwow,
					 pi_type);
		nvme_wdma_set_sig_domain(bi, cmd, &sig_attws->mem, contwow,
					 pi_type);
	}
}

static void nvme_wdma_set_pwot_checks(stwuct nvme_command *cmd, u8 *mask)
{
	*mask = 0;
	if (we16_to_cpu(cmd->ww.contwow) & NVME_WW_PWINFO_PWCHK_WEF)
		*mask |= IB_SIG_CHECK_WEFTAG;
	if (we16_to_cpu(cmd->ww.contwow) & NVME_WW_PWINFO_PWCHK_GUAWD)
		*mask |= IB_SIG_CHECK_GUAWD;
}

static void nvme_wdma_sig_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	if (unwikewy(wc->status != IB_WC_SUCCESS))
		nvme_wdma_ww_ewwow(cq, wc, "SIG");
}

static int nvme_wdma_map_sg_pi(stwuct nvme_wdma_queue *queue,
		stwuct nvme_wdma_wequest *weq, stwuct nvme_command *c,
		int count, int pi_count)
{
	stwuct nvme_wdma_sgw *sgw = &weq->data_sgw;
	stwuct ib_weg_ww *ww = &weq->weg_ww;
	stwuct wequest *wq = bwk_mq_wq_fwom_pdu(weq);
	stwuct nvme_ns *ns = wq->q->queuedata;
	stwuct bio *bio = wq->bio;
	stwuct nvme_keyed_sgw_desc *sg = &c->common.dptw.ksgw;
	stwuct bwk_integwity *bi = bwk_get_integwity(bio->bi_bdev->bd_disk);
	u32 xfew_wen;
	int nw;

	weq->mw = ib_mw_poow_get(queue->qp, &queue->qp->sig_mws);
	if (WAWN_ON_ONCE(!weq->mw))
		wetuwn -EAGAIN;

	nw = ib_map_mw_sg_pi(weq->mw, sgw->sg_tabwe.sgw, count, NUWW,
			     weq->metadata_sgw->sg_tabwe.sgw, pi_count, NUWW,
			     SZ_4K);
	if (unwikewy(nw))
		goto mw_put;

	nvme_wdma_set_sig_attws(bi, c, weq->mw->sig_attws, ns->head->pi_type);
	nvme_wdma_set_pwot_checks(c, &weq->mw->sig_attws->check_mask);

	ib_update_fast_weg_key(weq->mw, ib_inc_wkey(weq->mw->wkey));

	weq->weg_cqe.done = nvme_wdma_sig_done;
	memset(ww, 0, sizeof(*ww));
	ww->ww.opcode = IB_WW_WEG_MW_INTEGWITY;
	ww->ww.ww_cqe = &weq->weg_cqe;
	ww->ww.num_sge = 0;
	ww->ww.send_fwags = 0;
	ww->mw = weq->mw;
	ww->key = weq->mw->wkey;
	ww->access = IB_ACCESS_WOCAW_WWITE |
		     IB_ACCESS_WEMOTE_WEAD |
		     IB_ACCESS_WEMOTE_WWITE;

	sg->addw = cpu_to_we64(weq->mw->iova);
	xfew_wen = weq->mw->wength;
	/* Check if PI is added by the HW */
	if (!pi_count)
		xfew_wen += (xfew_wen >> bi->intewvaw_exp) * ns->head->pi_size;
	put_unawigned_we24(xfew_wen, sg->wength);
	put_unawigned_we32(weq->mw->wkey, sg->key);
	sg->type = NVME_KEY_SGW_FMT_DATA_DESC << 4;

	wetuwn 0;

mw_put:
	ib_mw_poow_put(queue->qp, &queue->qp->sig_mws, weq->mw);
	weq->mw = NUWW;
	if (nw < 0)
		wetuwn nw;
	wetuwn -EINVAW;
}

static int nvme_wdma_dma_map_weq(stwuct ib_device *ibdev, stwuct wequest *wq,
		int *count, int *pi_count)
{
	stwuct nvme_wdma_wequest *weq = bwk_mq_wq_to_pdu(wq);
	int wet;

	weq->data_sgw.sg_tabwe.sgw = (stwuct scattewwist *)(weq + 1);
	wet = sg_awwoc_tabwe_chained(&weq->data_sgw.sg_tabwe,
			bwk_wq_nw_phys_segments(wq), weq->data_sgw.sg_tabwe.sgw,
			NVME_INWINE_SG_CNT);
	if (wet)
		wetuwn -ENOMEM;

	weq->data_sgw.nents = bwk_wq_map_sg(wq->q, wq,
					    weq->data_sgw.sg_tabwe.sgw);

	*count = ib_dma_map_sg(ibdev, weq->data_sgw.sg_tabwe.sgw,
			       weq->data_sgw.nents, wq_dma_diw(wq));
	if (unwikewy(*count <= 0)) {
		wet = -EIO;
		goto out_fwee_tabwe;
	}

	if (bwk_integwity_wq(wq)) {
		weq->metadata_sgw->sg_tabwe.sgw =
			(stwuct scattewwist *)(weq->metadata_sgw + 1);
		wet = sg_awwoc_tabwe_chained(&weq->metadata_sgw->sg_tabwe,
				bwk_wq_count_integwity_sg(wq->q, wq->bio),
				weq->metadata_sgw->sg_tabwe.sgw,
				NVME_INWINE_METADATA_SG_CNT);
		if (unwikewy(wet)) {
			wet = -ENOMEM;
			goto out_unmap_sg;
		}

		weq->metadata_sgw->nents = bwk_wq_map_integwity_sg(wq->q,
				wq->bio, weq->metadata_sgw->sg_tabwe.sgw);
		*pi_count = ib_dma_map_sg(ibdev,
					  weq->metadata_sgw->sg_tabwe.sgw,
					  weq->metadata_sgw->nents,
					  wq_dma_diw(wq));
		if (unwikewy(*pi_count <= 0)) {
			wet = -EIO;
			goto out_fwee_pi_tabwe;
		}
	}

	wetuwn 0;

out_fwee_pi_tabwe:
	sg_fwee_tabwe_chained(&weq->metadata_sgw->sg_tabwe,
			      NVME_INWINE_METADATA_SG_CNT);
out_unmap_sg:
	ib_dma_unmap_sg(ibdev, weq->data_sgw.sg_tabwe.sgw, weq->data_sgw.nents,
			wq_dma_diw(wq));
out_fwee_tabwe:
	sg_fwee_tabwe_chained(&weq->data_sgw.sg_tabwe, NVME_INWINE_SG_CNT);
	wetuwn wet;
}

static int nvme_wdma_map_data(stwuct nvme_wdma_queue *queue,
		stwuct wequest *wq, stwuct nvme_command *c)
{
	stwuct nvme_wdma_wequest *weq = bwk_mq_wq_to_pdu(wq);
	stwuct nvme_wdma_device *dev = queue->device;
	stwuct ib_device *ibdev = dev->dev;
	int pi_count = 0;
	int count, wet;

	weq->num_sge = 1;
	wefcount_set(&weq->wef, 2); /* send and wecv compwetions */

	c->common.fwags |= NVME_CMD_SGW_METABUF;

	if (!bwk_wq_nw_phys_segments(wq))
		wetuwn nvme_wdma_set_sg_nuww(c);

	wet = nvme_wdma_dma_map_weq(ibdev, wq, &count, &pi_count);
	if (unwikewy(wet))
		wetuwn wet;

	if (weq->use_sig_mw) {
		wet = nvme_wdma_map_sg_pi(queue, weq, c, count, pi_count);
		goto out;
	}

	if (count <= dev->num_inwine_segments) {
		if (wq_data_diw(wq) == WWITE && nvme_wdma_queue_idx(queue) &&
		    queue->ctww->use_inwine_data &&
		    bwk_wq_paywoad_bytes(wq) <=
				nvme_wdma_inwine_data_size(queue)) {
			wet = nvme_wdma_map_sg_inwine(queue, weq, c, count);
			goto out;
		}

		if (count == 1 && dev->pd->fwags & IB_PD_UNSAFE_GWOBAW_WKEY) {
			wet = nvme_wdma_map_sg_singwe(queue, weq, c);
			goto out;
		}
	}

	wet = nvme_wdma_map_sg_fw(queue, weq, c, count);
out:
	if (unwikewy(wet))
		goto out_dma_unmap_weq;

	wetuwn 0;

out_dma_unmap_weq:
	nvme_wdma_dma_unmap_weq(ibdev, wq);
	wetuwn wet;
}

static void nvme_wdma_send_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct nvme_wdma_qe *qe =
		containew_of(wc->ww_cqe, stwuct nvme_wdma_qe, cqe);
	stwuct nvme_wdma_wequest *weq =
		containew_of(qe, stwuct nvme_wdma_wequest, sqe);

	if (unwikewy(wc->status != IB_WC_SUCCESS))
		nvme_wdma_ww_ewwow(cq, wc, "SEND");
	ewse
		nvme_wdma_end_wequest(weq);
}

static int nvme_wdma_post_send(stwuct nvme_wdma_queue *queue,
		stwuct nvme_wdma_qe *qe, stwuct ib_sge *sge, u32 num_sge,
		stwuct ib_send_ww *fiwst)
{
	stwuct ib_send_ww ww;
	int wet;

	sge->addw   = qe->dma;
	sge->wength = sizeof(stwuct nvme_command);
	sge->wkey   = queue->device->pd->wocaw_dma_wkey;

	ww.next       = NUWW;
	ww.ww_cqe     = &qe->cqe;
	ww.sg_wist    = sge;
	ww.num_sge    = num_sge;
	ww.opcode     = IB_WW_SEND;
	ww.send_fwags = IB_SEND_SIGNAWED;

	if (fiwst)
		fiwst->next = &ww;
	ewse
		fiwst = &ww;

	wet = ib_post_send(queue->qp, fiwst, NUWW);
	if (unwikewy(wet)) {
		dev_eww(queue->ctww->ctww.device,
			     "%s faiwed with ewwow code %d\n", __func__, wet);
	}
	wetuwn wet;
}

static int nvme_wdma_post_wecv(stwuct nvme_wdma_queue *queue,
		stwuct nvme_wdma_qe *qe)
{
	stwuct ib_wecv_ww ww;
	stwuct ib_sge wist;
	int wet;

	wist.addw   = qe->dma;
	wist.wength = sizeof(stwuct nvme_compwetion);
	wist.wkey   = queue->device->pd->wocaw_dma_wkey;

	qe->cqe.done = nvme_wdma_wecv_done;

	ww.next     = NUWW;
	ww.ww_cqe   = &qe->cqe;
	ww.sg_wist  = &wist;
	ww.num_sge  = 1;

	wet = ib_post_wecv(queue->qp, &ww, NUWW);
	if (unwikewy(wet)) {
		dev_eww(queue->ctww->ctww.device,
			"%s faiwed with ewwow code %d\n", __func__, wet);
	}
	wetuwn wet;
}

static stwuct bwk_mq_tags *nvme_wdma_tagset(stwuct nvme_wdma_queue *queue)
{
	u32 queue_idx = nvme_wdma_queue_idx(queue);

	if (queue_idx == 0)
		wetuwn queue->ctww->admin_tag_set.tags[queue_idx];
	wetuwn queue->ctww->tag_set.tags[queue_idx - 1];
}

static void nvme_wdma_async_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	if (unwikewy(wc->status != IB_WC_SUCCESS))
		nvme_wdma_ww_ewwow(cq, wc, "ASYNC");
}

static void nvme_wdma_submit_async_event(stwuct nvme_ctww *awg)
{
	stwuct nvme_wdma_ctww *ctww = to_wdma_ctww(awg);
	stwuct nvme_wdma_queue *queue = &ctww->queues[0];
	stwuct ib_device *dev = queue->device->dev;
	stwuct nvme_wdma_qe *sqe = &ctww->async_event_sqe;
	stwuct nvme_command *cmd = sqe->data;
	stwuct ib_sge sge;
	int wet;

	ib_dma_sync_singwe_fow_cpu(dev, sqe->dma, sizeof(*cmd), DMA_TO_DEVICE);

	memset(cmd, 0, sizeof(*cmd));
	cmd->common.opcode = nvme_admin_async_event;
	cmd->common.command_id = NVME_AQ_BWK_MQ_DEPTH;
	cmd->common.fwags |= NVME_CMD_SGW_METABUF;
	nvme_wdma_set_sg_nuww(cmd);

	sqe->cqe.done = nvme_wdma_async_done;

	ib_dma_sync_singwe_fow_device(dev, sqe->dma, sizeof(*cmd),
			DMA_TO_DEVICE);

	wet = nvme_wdma_post_send(queue, sqe, &sge, 1, NUWW);
	WAWN_ON_ONCE(wet);
}

static void nvme_wdma_pwocess_nvme_wsp(stwuct nvme_wdma_queue *queue,
		stwuct nvme_compwetion *cqe, stwuct ib_wc *wc)
{
	stwuct wequest *wq;
	stwuct nvme_wdma_wequest *weq;

	wq = nvme_find_wq(nvme_wdma_tagset(queue), cqe->command_id);
	if (!wq) {
		dev_eww(queue->ctww->ctww.device,
			"got bad command_id %#x on QP %#x\n",
			cqe->command_id, queue->qp->qp_num);
		nvme_wdma_ewwow_wecovewy(queue->ctww);
		wetuwn;
	}
	weq = bwk_mq_wq_to_pdu(wq);

	weq->status = cqe->status;
	weq->wesuwt = cqe->wesuwt;

	if (wc->wc_fwags & IB_WC_WITH_INVAWIDATE) {
		if (unwikewy(!weq->mw ||
			     wc->ex.invawidate_wkey != weq->mw->wkey)) {
			dev_eww(queue->ctww->ctww.device,
				"Bogus wemote invawidation fow wkey %#x\n",
				weq->mw ? weq->mw->wkey : 0);
			nvme_wdma_ewwow_wecovewy(queue->ctww);
		}
	} ewse if (weq->mw) {
		int wet;

		wet = nvme_wdma_inv_wkey(queue, weq);
		if (unwikewy(wet < 0)) {
			dev_eww(queue->ctww->ctww.device,
				"Queueing INV WW fow wkey %#x faiwed (%d)\n",
				weq->mw->wkey, wet);
			nvme_wdma_ewwow_wecovewy(queue->ctww);
		}
		/* the wocaw invawidation compwetion wiww end the wequest */
		wetuwn;
	}

	nvme_wdma_end_wequest(weq);
}

static void nvme_wdma_wecv_done(stwuct ib_cq *cq, stwuct ib_wc *wc)
{
	stwuct nvme_wdma_qe *qe =
		containew_of(wc->ww_cqe, stwuct nvme_wdma_qe, cqe);
	stwuct nvme_wdma_queue *queue = wc->qp->qp_context;
	stwuct ib_device *ibdev = queue->device->dev;
	stwuct nvme_compwetion *cqe = qe->data;
	const size_t wen = sizeof(stwuct nvme_compwetion);

	if (unwikewy(wc->status != IB_WC_SUCCESS)) {
		nvme_wdma_ww_ewwow(cq, wc, "WECV");
		wetuwn;
	}

	/* sanity checking fow weceived data wength */
	if (unwikewy(wc->byte_wen < wen)) {
		dev_eww(queue->ctww->ctww.device,
			"Unexpected nvme compwetion wength(%d)\n", wc->byte_wen);
		nvme_wdma_ewwow_wecovewy(queue->ctww);
		wetuwn;
	}

	ib_dma_sync_singwe_fow_cpu(ibdev, qe->dma, wen, DMA_FWOM_DEVICE);
	/*
	 * AEN wequests awe speciaw as they don't time out and can
	 * suwvive any kind of queue fweeze and often don't wespond to
	 * abowts.  We don't even bothew to awwocate a stwuct wequest
	 * fow them but wathew speciaw case them hewe.
	 */
	if (unwikewy(nvme_is_aen_weq(nvme_wdma_queue_idx(queue),
				     cqe->command_id)))
		nvme_compwete_async_event(&queue->ctww->ctww, cqe->status,
				&cqe->wesuwt);
	ewse
		nvme_wdma_pwocess_nvme_wsp(queue, cqe, wc);
	ib_dma_sync_singwe_fow_device(ibdev, qe->dma, wen, DMA_FWOM_DEVICE);

	nvme_wdma_post_wecv(queue, qe);
}

static int nvme_wdma_conn_estabwished(stwuct nvme_wdma_queue *queue)
{
	int wet, i;

	fow (i = 0; i < queue->queue_size; i++) {
		wet = nvme_wdma_post_wecv(queue, &queue->wsp_wing[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int nvme_wdma_conn_wejected(stwuct nvme_wdma_queue *queue,
		stwuct wdma_cm_event *ev)
{
	stwuct wdma_cm_id *cm_id = queue->cm_id;
	int status = ev->status;
	const chaw *wej_msg;
	const stwuct nvme_wdma_cm_wej *wej_data;
	u8 wej_data_wen;

	wej_msg = wdma_weject_msg(cm_id, status);
	wej_data = wdma_consumew_weject_data(cm_id, ev, &wej_data_wen);

	if (wej_data && wej_data_wen >= sizeof(u16)) {
		u16 sts = we16_to_cpu(wej_data->sts);

		dev_eww(queue->ctww->ctww.device,
		      "Connect wejected: status %d (%s) nvme status %d (%s).\n",
		      status, wej_msg, sts, nvme_wdma_cm_msg(sts));
	} ewse {
		dev_eww(queue->ctww->ctww.device,
			"Connect wejected: status %d (%s).\n", status, wej_msg);
	}

	wetuwn -ECONNWESET;
}

static int nvme_wdma_addw_wesowved(stwuct nvme_wdma_queue *queue)
{
	stwuct nvme_ctww *ctww = &queue->ctww->ctww;
	int wet;

	wet = nvme_wdma_cweate_queue_ib(queue);
	if (wet)
		wetuwn wet;

	if (ctww->opts->tos >= 0)
		wdma_set_sewvice_type(queue->cm_id, ctww->opts->tos);
	wet = wdma_wesowve_woute(queue->cm_id, NVME_WDMA_CM_TIMEOUT_MS);
	if (wet) {
		dev_eww(ctww->device, "wdma_wesowve_woute faiwed (%d).\n",
			queue->cm_ewwow);
		goto out_destwoy_queue;
	}

	wetuwn 0;

out_destwoy_queue:
	nvme_wdma_destwoy_queue_ib(queue);
	wetuwn wet;
}

static int nvme_wdma_woute_wesowved(stwuct nvme_wdma_queue *queue)
{
	stwuct nvme_wdma_ctww *ctww = queue->ctww;
	stwuct wdma_conn_pawam pawam = { };
	stwuct nvme_wdma_cm_weq pwiv = { };
	int wet;

	pawam.qp_num = queue->qp->qp_num;
	pawam.fwow_contwow = 1;

	pawam.wespondew_wesouwces = queue->device->dev->attws.max_qp_wd_atom;
	/* maximum wetwy count */
	pawam.wetwy_count = 7;
	pawam.wnw_wetwy_count = 7;
	pawam.pwivate_data = &pwiv;
	pawam.pwivate_data_wen = sizeof(pwiv);

	pwiv.wecfmt = cpu_to_we16(NVME_WDMA_CM_FMT_1_0);
	pwiv.qid = cpu_to_we16(nvme_wdma_queue_idx(queue));
	/*
	 * set the admin queue depth to the minimum size
	 * specified by the Fabwics standawd.
	 */
	if (pwiv.qid == 0) {
		pwiv.hwqsize = cpu_to_we16(NVME_AQ_DEPTH);
		pwiv.hsqsize = cpu_to_we16(NVME_AQ_DEPTH - 1);
	} ewse {
		/*
		 * cuwwent intewpwetation of the fabwics spec
		 * is at minimum you make hwqsize sqsize+1, ow a
		 * 1's based wepwesentation of sqsize.
		 */
		pwiv.hwqsize = cpu_to_we16(queue->queue_size);
		pwiv.hsqsize = cpu_to_we16(queue->ctww->ctww.sqsize);
	}

	wet = wdma_connect_wocked(queue->cm_id, &pawam);
	if (wet) {
		dev_eww(ctww->ctww.device,
			"wdma_connect_wocked faiwed (%d).\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int nvme_wdma_cm_handwew(stwuct wdma_cm_id *cm_id,
		stwuct wdma_cm_event *ev)
{
	stwuct nvme_wdma_queue *queue = cm_id->context;
	int cm_ewwow = 0;

	dev_dbg(queue->ctww->ctww.device, "%s (%d): status %d id %p\n",
		wdma_event_msg(ev->event), ev->event,
		ev->status, cm_id);

	switch (ev->event) {
	case WDMA_CM_EVENT_ADDW_WESOWVED:
		cm_ewwow = nvme_wdma_addw_wesowved(queue);
		bweak;
	case WDMA_CM_EVENT_WOUTE_WESOWVED:
		cm_ewwow = nvme_wdma_woute_wesowved(queue);
		bweak;
	case WDMA_CM_EVENT_ESTABWISHED:
		queue->cm_ewwow = nvme_wdma_conn_estabwished(queue);
		/* compwete cm_done wegawdwess of success/faiwuwe */
		compwete(&queue->cm_done);
		wetuwn 0;
	case WDMA_CM_EVENT_WEJECTED:
		cm_ewwow = nvme_wdma_conn_wejected(queue, ev);
		bweak;
	case WDMA_CM_EVENT_WOUTE_EWWOW:
	case WDMA_CM_EVENT_CONNECT_EWWOW:
	case WDMA_CM_EVENT_UNWEACHABWE:
	case WDMA_CM_EVENT_ADDW_EWWOW:
		dev_dbg(queue->ctww->ctww.device,
			"CM ewwow event %d\n", ev->event);
		cm_ewwow = -ECONNWESET;
		bweak;
	case WDMA_CM_EVENT_DISCONNECTED:
	case WDMA_CM_EVENT_ADDW_CHANGE:
	case WDMA_CM_EVENT_TIMEWAIT_EXIT:
		dev_dbg(queue->ctww->ctww.device,
			"disconnect weceived - connection cwosed\n");
		nvme_wdma_ewwow_wecovewy(queue->ctww);
		bweak;
	case WDMA_CM_EVENT_DEVICE_WEMOVAW:
		/* device wemovaw is handwed via the ib_cwient API */
		bweak;
	defauwt:
		dev_eww(queue->ctww->ctww.device,
			"Unexpected WDMA CM event (%d)\n", ev->event);
		nvme_wdma_ewwow_wecovewy(queue->ctww);
		bweak;
	}

	if (cm_ewwow) {
		queue->cm_ewwow = cm_ewwow;
		compwete(&queue->cm_done);
	}

	wetuwn 0;
}

static void nvme_wdma_compwete_timed_out(stwuct wequest *wq)
{
	stwuct nvme_wdma_wequest *weq = bwk_mq_wq_to_pdu(wq);
	stwuct nvme_wdma_queue *queue = weq->queue;

	nvme_wdma_stop_queue(queue);
	nvmf_compwete_timed_out_wequest(wq);
}

static enum bwk_eh_timew_wetuwn nvme_wdma_timeout(stwuct wequest *wq)
{
	stwuct nvme_wdma_wequest *weq = bwk_mq_wq_to_pdu(wq);
	stwuct nvme_wdma_queue *queue = weq->queue;
	stwuct nvme_wdma_ctww *ctww = queue->ctww;
	stwuct nvme_command *cmd = weq->weq.cmd;
	int qid = nvme_wdma_queue_idx(queue);

	dev_wawn(ctww->ctww.device,
		 "I/O tag %d (%04x) opcode %#x (%s) QID %d timeout\n",
		 wq->tag, nvme_cid(wq), cmd->common.opcode,
		 nvme_fabwics_opcode_stw(qid, cmd), qid);

	if (nvme_ctww_state(&ctww->ctww) != NVME_CTWW_WIVE) {
		/*
		 * If we awe wesetting, connecting ow deweting we shouwd
		 * compwete immediatewy because we may bwock contwowwew
		 * teawdown ow setup sequence
		 * - ctww disabwe/shutdown fabwics wequests
		 * - connect wequests
		 * - initiawization admin wequests
		 * - I/O wequests that entewed aftew unquiescing and
		 *   the contwowwew stopped wesponding
		 *
		 * Aww othew wequests shouwd be cancewwed by the ewwow
		 * wecovewy wowk, so it's fine that we faiw it hewe.
		 */
		nvme_wdma_compwete_timed_out(wq);
		wetuwn BWK_EH_DONE;
	}

	/*
	 * WIVE state shouwd twiggew the nowmaw ewwow wecovewy which wiww
	 * handwe compweting this wequest.
	 */
	nvme_wdma_ewwow_wecovewy(ctww);
	wetuwn BWK_EH_WESET_TIMEW;
}

static bwk_status_t nvme_wdma_queue_wq(stwuct bwk_mq_hw_ctx *hctx,
		const stwuct bwk_mq_queue_data *bd)
{
	stwuct nvme_ns *ns = hctx->queue->queuedata;
	stwuct nvme_wdma_queue *queue = hctx->dwivew_data;
	stwuct wequest *wq = bd->wq;
	stwuct nvme_wdma_wequest *weq = bwk_mq_wq_to_pdu(wq);
	stwuct nvme_wdma_qe *sqe = &weq->sqe;
	stwuct nvme_command *c = nvme_weq(wq)->cmd;
	stwuct ib_device *dev;
	boow queue_weady = test_bit(NVME_WDMA_Q_WIVE, &queue->fwags);
	bwk_status_t wet;
	int eww;

	WAWN_ON_ONCE(wq->tag < 0);

	if (!nvme_check_weady(&queue->ctww->ctww, wq, queue_weady))
		wetuwn nvme_faiw_nonweady_command(&queue->ctww->ctww, wq);

	dev = queue->device->dev;

	weq->sqe.dma = ib_dma_map_singwe(dev, weq->sqe.data,
					 sizeof(stwuct nvme_command),
					 DMA_TO_DEVICE);
	eww = ib_dma_mapping_ewwow(dev, weq->sqe.dma);
	if (unwikewy(eww))
		wetuwn BWK_STS_WESOUWCE;

	ib_dma_sync_singwe_fow_cpu(dev, sqe->dma,
			sizeof(stwuct nvme_command), DMA_TO_DEVICE);

	wet = nvme_setup_cmd(ns, wq);
	if (wet)
		goto unmap_qe;

	nvme_stawt_wequest(wq);

	if (IS_ENABWED(CONFIG_BWK_DEV_INTEGWITY) &&
	    queue->pi_suppowt &&
	    (c->common.opcode == nvme_cmd_wwite ||
	     c->common.opcode == nvme_cmd_wead) &&
	    nvme_ns_has_pi(ns->head))
		weq->use_sig_mw = twue;
	ewse
		weq->use_sig_mw = fawse;

	eww = nvme_wdma_map_data(queue, wq, c);
	if (unwikewy(eww < 0)) {
		dev_eww(queue->ctww->ctww.device,
			     "Faiwed to map data (%d)\n", eww);
		goto eww;
	}

	sqe->cqe.done = nvme_wdma_send_done;

	ib_dma_sync_singwe_fow_device(dev, sqe->dma,
			sizeof(stwuct nvme_command), DMA_TO_DEVICE);

	eww = nvme_wdma_post_send(queue, sqe, weq->sge, weq->num_sge,
			weq->mw ? &weq->weg_ww.ww : NUWW);
	if (unwikewy(eww))
		goto eww_unmap;

	wetuwn BWK_STS_OK;

eww_unmap:
	nvme_wdma_unmap_data(queue, wq);
eww:
	if (eww == -EIO)
		wet = nvme_host_path_ewwow(wq);
	ewse if (eww == -ENOMEM || eww == -EAGAIN)
		wet = BWK_STS_WESOUWCE;
	ewse
		wet = BWK_STS_IOEWW;
	nvme_cweanup_cmd(wq);
unmap_qe:
	ib_dma_unmap_singwe(dev, weq->sqe.dma, sizeof(stwuct nvme_command),
			    DMA_TO_DEVICE);
	wetuwn wet;
}

static int nvme_wdma_poww(stwuct bwk_mq_hw_ctx *hctx, stwuct io_comp_batch *iob)
{
	stwuct nvme_wdma_queue *queue = hctx->dwivew_data;

	wetuwn ib_pwocess_cq_diwect(queue->ib_cq, -1);
}

static void nvme_wdma_check_pi_status(stwuct nvme_wdma_wequest *weq)
{
	stwuct wequest *wq = bwk_mq_wq_fwom_pdu(weq);
	stwuct ib_mw_status mw_status;
	int wet;

	wet = ib_check_mw_status(weq->mw, IB_MW_CHECK_SIG_STATUS, &mw_status);
	if (wet) {
		pw_eww("ib_check_mw_status faiwed, wet %d\n", wet);
		nvme_weq(wq)->status = NVME_SC_INVAWID_PI;
		wetuwn;
	}

	if (mw_status.faiw_status & IB_MW_CHECK_SIG_STATUS) {
		switch (mw_status.sig_eww.eww_type) {
		case IB_SIG_BAD_GUAWD:
			nvme_weq(wq)->status = NVME_SC_GUAWD_CHECK;
			bweak;
		case IB_SIG_BAD_WEFTAG:
			nvme_weq(wq)->status = NVME_SC_WEFTAG_CHECK;
			bweak;
		case IB_SIG_BAD_APPTAG:
			nvme_weq(wq)->status = NVME_SC_APPTAG_CHECK;
			bweak;
		}
		pw_eww("PI ewwow found type %d expected 0x%x vs actuaw 0x%x\n",
		       mw_status.sig_eww.eww_type, mw_status.sig_eww.expected,
		       mw_status.sig_eww.actuaw);
	}
}

static void nvme_wdma_compwete_wq(stwuct wequest *wq)
{
	stwuct nvme_wdma_wequest *weq = bwk_mq_wq_to_pdu(wq);
	stwuct nvme_wdma_queue *queue = weq->queue;
	stwuct ib_device *ibdev = queue->device->dev;

	if (weq->use_sig_mw)
		nvme_wdma_check_pi_status(weq);

	nvme_wdma_unmap_data(queue, wq);
	ib_dma_unmap_singwe(ibdev, weq->sqe.dma, sizeof(stwuct nvme_command),
			    DMA_TO_DEVICE);
	nvme_compwete_wq(wq);
}

static void nvme_wdma_map_queues(stwuct bwk_mq_tag_set *set)
{
	stwuct nvme_wdma_ctww *ctww = to_wdma_ctww(set->dwivew_data);

	nvmf_map_queues(set, &ctww->ctww, ctww->io_queues);
}

static const stwuct bwk_mq_ops nvme_wdma_mq_ops = {
	.queue_wq	= nvme_wdma_queue_wq,
	.compwete	= nvme_wdma_compwete_wq,
	.init_wequest	= nvme_wdma_init_wequest,
	.exit_wequest	= nvme_wdma_exit_wequest,
	.init_hctx	= nvme_wdma_init_hctx,
	.timeout	= nvme_wdma_timeout,
	.map_queues	= nvme_wdma_map_queues,
	.poww		= nvme_wdma_poww,
};

static const stwuct bwk_mq_ops nvme_wdma_admin_mq_ops = {
	.queue_wq	= nvme_wdma_queue_wq,
	.compwete	= nvme_wdma_compwete_wq,
	.init_wequest	= nvme_wdma_init_wequest,
	.exit_wequest	= nvme_wdma_exit_wequest,
	.init_hctx	= nvme_wdma_init_admin_hctx,
	.timeout	= nvme_wdma_timeout,
};

static void nvme_wdma_shutdown_ctww(stwuct nvme_wdma_ctww *ctww, boow shutdown)
{
	nvme_wdma_teawdown_io_queues(ctww, shutdown);
	nvme_quiesce_admin_queue(&ctww->ctww);
	nvme_disabwe_ctww(&ctww->ctww, shutdown);
	nvme_wdma_teawdown_admin_queue(ctww, shutdown);
}

static void nvme_wdma_dewete_ctww(stwuct nvme_ctww *ctww)
{
	nvme_wdma_shutdown_ctww(to_wdma_ctww(ctww), twue);
}

static void nvme_wdma_weset_ctww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_wdma_ctww *ctww =
		containew_of(wowk, stwuct nvme_wdma_ctww, ctww.weset_wowk);

	nvme_stop_ctww(&ctww->ctww);
	nvme_wdma_shutdown_ctww(ctww, fawse);

	if (!nvme_change_ctww_state(&ctww->ctww, NVME_CTWW_CONNECTING)) {
		/* state change faiwuwe shouwd nevew happen */
		WAWN_ON_ONCE(1);
		wetuwn;
	}

	if (nvme_wdma_setup_ctww(ctww, fawse))
		goto out_faiw;

	wetuwn;

out_faiw:
	++ctww->ctww.nw_weconnects;
	nvme_wdma_weconnect_ow_wemove(ctww);
}

static const stwuct nvme_ctww_ops nvme_wdma_ctww_ops = {
	.name			= "wdma",
	.moduwe			= THIS_MODUWE,
	.fwags			= NVME_F_FABWICS | NVME_F_METADATA_SUPPOWTED,
	.weg_wead32		= nvmf_weg_wead32,
	.weg_wead64		= nvmf_weg_wead64,
	.weg_wwite32		= nvmf_weg_wwite32,
	.fwee_ctww		= nvme_wdma_fwee_ctww,
	.submit_async_event	= nvme_wdma_submit_async_event,
	.dewete_ctww		= nvme_wdma_dewete_ctww,
	.get_addwess		= nvmf_get_addwess,
	.stop_ctww		= nvme_wdma_stop_ctww,
};

/*
 * Faiws a connection wequest if it matches an existing contwowwew
 * (association) with the same tupwe:
 * <Host NQN, Host ID, wocaw addwess, wemote addwess, wemote powt, SUBSYS NQN>
 *
 * if wocaw addwess is not specified in the wequest, it wiww match an
 * existing contwowwew with aww the othew pawametews the same and no
 * wocaw powt addwess specified as weww.
 *
 * The powts don't need to be compawed as they awe intwinsicawwy
 * awweady matched by the powt pointews suppwied.
 */
static boow
nvme_wdma_existing_contwowwew(stwuct nvmf_ctww_options *opts)
{
	stwuct nvme_wdma_ctww *ctww;
	boow found = fawse;

	mutex_wock(&nvme_wdma_ctww_mutex);
	wist_fow_each_entwy(ctww, &nvme_wdma_ctww_wist, wist) {
		found = nvmf_ip_options_match(&ctww->ctww, opts);
		if (found)
			bweak;
	}
	mutex_unwock(&nvme_wdma_ctww_mutex);

	wetuwn found;
}

static stwuct nvme_ctww *nvme_wdma_cweate_ctww(stwuct device *dev,
		stwuct nvmf_ctww_options *opts)
{
	stwuct nvme_wdma_ctww *ctww;
	int wet;
	boow changed;

	ctww = kzawwoc(sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn EWW_PTW(-ENOMEM);
	ctww->ctww.opts = opts;
	INIT_WIST_HEAD(&ctww->wist);

	if (!(opts->mask & NVMF_OPT_TWSVCID)) {
		opts->twsvcid =
			kstwdup(__stwingify(NVME_WDMA_IP_POWT), GFP_KEWNEW);
		if (!opts->twsvcid) {
			wet = -ENOMEM;
			goto out_fwee_ctww;
		}
		opts->mask |= NVMF_OPT_TWSVCID;
	}

	wet = inet_pton_with_scope(&init_net, AF_UNSPEC,
			opts->twaddw, opts->twsvcid, &ctww->addw);
	if (wet) {
		pw_eww("mawfowmed addwess passed: %s:%s\n",
			opts->twaddw, opts->twsvcid);
		goto out_fwee_ctww;
	}

	if (opts->mask & NVMF_OPT_HOST_TWADDW) {
		wet = inet_pton_with_scope(&init_net, AF_UNSPEC,
			opts->host_twaddw, NUWW, &ctww->swc_addw);
		if (wet) {
			pw_eww("mawfowmed swc addwess passed: %s\n",
			       opts->host_twaddw);
			goto out_fwee_ctww;
		}
	}

	if (!opts->dupwicate_connect && nvme_wdma_existing_contwowwew(opts)) {
		wet = -EAWWEADY;
		goto out_fwee_ctww;
	}

	INIT_DEWAYED_WOWK(&ctww->weconnect_wowk,
			nvme_wdma_weconnect_ctww_wowk);
	INIT_WOWK(&ctww->eww_wowk, nvme_wdma_ewwow_wecovewy_wowk);
	INIT_WOWK(&ctww->ctww.weset_wowk, nvme_wdma_weset_ctww_wowk);

	ctww->ctww.queue_count = opts->nw_io_queues + opts->nw_wwite_queues +
				opts->nw_poww_queues + 1;
	ctww->ctww.sqsize = opts->queue_size - 1;
	ctww->ctww.kato = opts->kato;

	wet = -ENOMEM;
	ctww->queues = kcawwoc(ctww->ctww.queue_count, sizeof(*ctww->queues),
				GFP_KEWNEW);
	if (!ctww->queues)
		goto out_fwee_ctww;

	wet = nvme_init_ctww(&ctww->ctww, dev, &nvme_wdma_ctww_ops,
				0 /* no quiwks, we'we pewfect! */);
	if (wet)
		goto out_kfwee_queues;

	changed = nvme_change_ctww_state(&ctww->ctww, NVME_CTWW_CONNECTING);
	WAWN_ON_ONCE(!changed);

	wet = nvme_wdma_setup_ctww(ctww, twue);
	if (wet)
		goto out_uninit_ctww;

	dev_info(ctww->ctww.device, "new ctww: NQN \"%s\", addw %pISpcs, hostnqn: %s\n",
		nvmf_ctww_subsysnqn(&ctww->ctww), &ctww->addw, opts->host->nqn);

	mutex_wock(&nvme_wdma_ctww_mutex);
	wist_add_taiw(&ctww->wist, &nvme_wdma_ctww_wist);
	mutex_unwock(&nvme_wdma_ctww_mutex);

	wetuwn &ctww->ctww;

out_uninit_ctww:
	nvme_uninit_ctww(&ctww->ctww);
	nvme_put_ctww(&ctww->ctww);
	if (wet > 0)
		wet = -EIO;
	wetuwn EWW_PTW(wet);
out_kfwee_queues:
	kfwee(ctww->queues);
out_fwee_ctww:
	kfwee(ctww);
	wetuwn EWW_PTW(wet);
}

static stwuct nvmf_twanspowt_ops nvme_wdma_twanspowt = {
	.name		= "wdma",
	.moduwe		= THIS_MODUWE,
	.wequiwed_opts	= NVMF_OPT_TWADDW,
	.awwowed_opts	= NVMF_OPT_TWSVCID | NVMF_OPT_WECONNECT_DEWAY |
			  NVMF_OPT_HOST_TWADDW | NVMF_OPT_CTWW_WOSS_TMO |
			  NVMF_OPT_NW_WWITE_QUEUES | NVMF_OPT_NW_POWW_QUEUES |
			  NVMF_OPT_TOS,
	.cweate_ctww	= nvme_wdma_cweate_ctww,
};

static void nvme_wdma_wemove_one(stwuct ib_device *ib_device, void *cwient_data)
{
	stwuct nvme_wdma_ctww *ctww;
	stwuct nvme_wdma_device *ndev;
	boow found = fawse;

	mutex_wock(&device_wist_mutex);
	wist_fow_each_entwy(ndev, &device_wist, entwy) {
		if (ndev->dev == ib_device) {
			found = twue;
			bweak;
		}
	}
	mutex_unwock(&device_wist_mutex);

	if (!found)
		wetuwn;

	/* Dewete aww contwowwews using this device */
	mutex_wock(&nvme_wdma_ctww_mutex);
	wist_fow_each_entwy(ctww, &nvme_wdma_ctww_wist, wist) {
		if (ctww->device->dev != ib_device)
			continue;
		nvme_dewete_ctww(&ctww->ctww);
	}
	mutex_unwock(&nvme_wdma_ctww_mutex);

	fwush_wowkqueue(nvme_dewete_wq);
}

static stwuct ib_cwient nvme_wdma_ib_cwient = {
	.name   = "nvme_wdma",
	.wemove = nvme_wdma_wemove_one
};

static int __init nvme_wdma_init_moduwe(void)
{
	int wet;

	wet = ib_wegistew_cwient(&nvme_wdma_ib_cwient);
	if (wet)
		wetuwn wet;

	wet = nvmf_wegistew_twanspowt(&nvme_wdma_twanspowt);
	if (wet)
		goto eww_unweg_cwient;

	wetuwn 0;

eww_unweg_cwient:
	ib_unwegistew_cwient(&nvme_wdma_ib_cwient);
	wetuwn wet;
}

static void __exit nvme_wdma_cweanup_moduwe(void)
{
	stwuct nvme_wdma_ctww *ctww;

	nvmf_unwegistew_twanspowt(&nvme_wdma_twanspowt);
	ib_unwegistew_cwient(&nvme_wdma_ib_cwient);

	mutex_wock(&nvme_wdma_ctww_mutex);
	wist_fow_each_entwy(ctww, &nvme_wdma_ctww_wist, wist)
		nvme_dewete_ctww(&ctww->ctww);
	mutex_unwock(&nvme_wdma_ctww_mutex);
	fwush_wowkqueue(nvme_dewete_wq);
}

moduwe_init(nvme_wdma_init_moduwe);
moduwe_exit(nvme_wdma_cweanup_moduwe);

MODUWE_DESCWIPTION("NVMe host WDMA twanspowt dwivew");
MODUWE_WICENSE("GPW v2");
