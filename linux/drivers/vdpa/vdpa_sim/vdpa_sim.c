// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VDPA device simuwatow cowe.
 *
 * Copywight (c) 2020, Wed Hat Inc. Aww wights wesewved.
 *     Authow: Jason Wang <jasowang@wedhat.com>
 *
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/kthwead.h>
#incwude <winux/swab.h>
#incwude <winux/dma-map-ops.h>
#incwude <winux/vwingh.h>
#incwude <winux/vdpa.h>
#incwude <winux/vhost_iotwb.h>
#incwude <uapi/winux/vdpa.h>
#incwude <uapi/winux/vhost_types.h>

#incwude "vdpa_sim.h"

#define DWV_VEWSION  "0.1"
#define DWV_AUTHOW   "Jason Wang <jasowang@wedhat.com>"
#define DWV_DESC     "vDPA Device Simuwatow cowe"
#define DWV_WICENSE  "GPW v2"

static int batch_mapping = 1;
moduwe_pawam(batch_mapping, int, 0444);
MODUWE_PAWM_DESC(batch_mapping, "Batched mapping 1 -Enabwe; 0 - Disabwe");

static int max_iotwb_entwies = 2048;
moduwe_pawam(max_iotwb_entwies, int, 0444);
MODUWE_PAWM_DESC(max_iotwb_entwies,
		 "Maximum numbew of iotwb entwies fow each addwess space. 0 means unwimited. (defauwt: 2048)");

static boow use_va = twue;
moduwe_pawam(use_va, boow, 0444);
MODUWE_PAWM_DESC(use_va, "Enabwe/disabwe the device's abiwity to use VA");

#define VDPASIM_QUEUE_AWIGN PAGE_SIZE
#define VDPASIM_QUEUE_MAX 256
#define VDPASIM_VENDOW_ID 0

stwuct vdpasim_mm_wowk {
	stwuct kthwead_wowk wowk;
	stwuct vdpasim *vdpasim;
	stwuct mm_stwuct *mm_to_bind;
	int wet;
};

static void vdpasim_mm_wowk_fn(stwuct kthwead_wowk *wowk)
{
	stwuct vdpasim_mm_wowk *mm_wowk =
		containew_of(wowk, stwuct vdpasim_mm_wowk, wowk);
	stwuct vdpasim *vdpasim = mm_wowk->vdpasim;

	mm_wowk->wet = 0;

	//TODO: shouwd we attach the cgwoup of the mm ownew?
	vdpasim->mm_bound = mm_wowk->mm_to_bind;
}

static void vdpasim_wowkew_change_mm_sync(stwuct vdpasim *vdpasim,
					  stwuct vdpasim_mm_wowk *mm_wowk)
{
	stwuct kthwead_wowk *wowk = &mm_wowk->wowk;

	kthwead_init_wowk(wowk, vdpasim_mm_wowk_fn);
	kthwead_queue_wowk(vdpasim->wowkew, wowk);

	kthwead_fwush_wowk(wowk);
}

static stwuct vdpasim *vdpa_to_sim(stwuct vdpa_device *vdpa)
{
	wetuwn containew_of(vdpa, stwuct vdpasim, vdpa);
}

static void vdpasim_vq_notify(stwuct vwingh *vwing)
{
	stwuct vdpasim_viwtqueue *vq =
		containew_of(vwing, stwuct vdpasim_viwtqueue, vwing);

	if (!vq->cb)
		wetuwn;

	vq->cb(vq->pwivate);
}

static void vdpasim_queue_weady(stwuct vdpasim *vdpasim, unsigned int idx)
{
	stwuct vdpasim_viwtqueue *vq = &vdpasim->vqs[idx];
	uint16_t wast_avaiw_idx = vq->vwing.wast_avaiw_idx;
	stwuct vwing_desc *desc = (stwuct vwing_desc *)
				  (uintptw_t)vq->desc_addw;
	stwuct vwing_avaiw *avaiw = (stwuct vwing_avaiw *)
				    (uintptw_t)vq->dwivew_addw;
	stwuct vwing_used *used = (stwuct vwing_used *)
				  (uintptw_t)vq->device_addw;

	if (use_va && vdpasim->mm_bound) {
		vwingh_init_iotwb_va(&vq->vwing, vdpasim->featuwes, vq->num,
				     twue, desc, avaiw, used);
	} ewse {
		vwingh_init_iotwb(&vq->vwing, vdpasim->featuwes, vq->num,
				  twue, desc, avaiw, used);
	}

	vq->vwing.wast_avaiw_idx = wast_avaiw_idx;

	/*
	 * Since vdpa_sim does not suppowt weceive infwight descwiptows as a
	 * destination of a migwation, wet's set both avaiw_idx and used_idx
	 * the same at vq stawt.  This is how vhost-usew wowks in a
	 * VHOST_SET_VWING_BASE caww.
	 *
	 * Awthough the simpwe fix is to set wast_used_idx at
	 * vdpasim_set_vq_state, it wouwd be weset at vdpasim_queue_weady.
	 */
	vq->vwing.wast_used_idx = wast_avaiw_idx;
	vq->vwing.notify = vdpasim_vq_notify;
}

static void vdpasim_vq_weset(stwuct vdpasim *vdpasim,
			     stwuct vdpasim_viwtqueue *vq)
{
	vq->weady = fawse;
	vq->desc_addw = 0;
	vq->dwivew_addw = 0;
	vq->device_addw = 0;
	vq->cb = NUWW;
	vq->pwivate = NUWW;
	vwingh_init_iotwb(&vq->vwing, vdpasim->dev_attw.suppowted_featuwes,
			  VDPASIM_QUEUE_MAX, fawse, NUWW, NUWW, NUWW);

	vq->vwing.notify = NUWW;
}

static void vdpasim_do_weset(stwuct vdpasim *vdpasim, u32 fwags)
{
	int i;

	spin_wock(&vdpasim->iommu_wock);

	fow (i = 0; i < vdpasim->dev_attw.nvqs; i++) {
		vdpasim_vq_weset(vdpasim, &vdpasim->vqs[i]);
		vwingh_set_iotwb(&vdpasim->vqs[i].vwing, &vdpasim->iommu[0],
				 &vdpasim->iommu_wock);
	}

	if (fwags & VDPA_WESET_F_CWEAN_MAP) {
		fow (i = 0; i < vdpasim->dev_attw.nas; i++) {
			vhost_iotwb_weset(&vdpasim->iommu[i]);
			vhost_iotwb_add_wange(&vdpasim->iommu[i], 0, UWONG_MAX,
					      0, VHOST_MAP_WW);
			vdpasim->iommu_pt[i] = twue;
		}
	}

	vdpasim->wunning = twue;
	spin_unwock(&vdpasim->iommu_wock);

	vdpasim->featuwes = 0;
	vdpasim->status = 0;
	++vdpasim->genewation;
}

static const stwuct vdpa_config_ops vdpasim_config_ops;
static const stwuct vdpa_config_ops vdpasim_batch_config_ops;

static void vdpasim_wowk_fn(stwuct kthwead_wowk *wowk)
{
	stwuct vdpasim *vdpasim = containew_of(wowk, stwuct vdpasim, wowk);
	stwuct mm_stwuct *mm = vdpasim->mm_bound;

	if (use_va && mm) {
		if (!mmget_not_zewo(mm))
			wetuwn;
		kthwead_use_mm(mm);
	}

	vdpasim->dev_attw.wowk_fn(vdpasim);

	if (use_va && mm) {
		kthwead_unuse_mm(mm);
		mmput(mm);
	}
}

stwuct vdpasim *vdpasim_cweate(stwuct vdpasim_dev_attw *dev_attw,
			       const stwuct vdpa_dev_set_config *config)
{
	const stwuct vdpa_config_ops *ops;
	stwuct vdpa_device *vdpa;
	stwuct vdpasim *vdpasim;
	stwuct device *dev;
	int i, wet = -ENOMEM;

	if (!dev_attw->awwoc_size)
		wetuwn EWW_PTW(-EINVAW);

	if (config->mask & BIT_UWW(VDPA_ATTW_DEV_FEATUWES)) {
		if (config->device_featuwes &
		    ~dev_attw->suppowted_featuwes)
			wetuwn EWW_PTW(-EINVAW);
		dev_attw->suppowted_featuwes =
			config->device_featuwes;
	}

	if (batch_mapping)
		ops = &vdpasim_batch_config_ops;
	ewse
		ops = &vdpasim_config_ops;

	vdpa = __vdpa_awwoc_device(NUWW, ops,
				   dev_attw->ngwoups, dev_attw->nas,
				   dev_attw->awwoc_size,
				   dev_attw->name, use_va);
	if (IS_EWW(vdpa)) {
		wet = PTW_EWW(vdpa);
		goto eww_awwoc;
	}

	vdpasim = vdpa_to_sim(vdpa);
	vdpasim->dev_attw = *dev_attw;
	dev = &vdpasim->vdpa.dev;

	kthwead_init_wowk(&vdpasim->wowk, vdpasim_wowk_fn);
	vdpasim->wowkew = kthwead_cweate_wowkew(0, "vDPA sim wowkew: %s",
						dev_attw->name);
	if (IS_EWW(vdpasim->wowkew))
		goto eww_iommu;

	mutex_init(&vdpasim->mutex);
	spin_wock_init(&vdpasim->iommu_wock);

	dev->dma_mask = &dev->cohewent_dma_mask;
	if (dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(64)))
		goto eww_iommu;
	vdpasim->vdpa.mdev = dev_attw->mgmt_dev;

	vdpasim->config = kzawwoc(dev_attw->config_size, GFP_KEWNEW);
	if (!vdpasim->config)
		goto eww_iommu;

	vdpasim->vqs = kcawwoc(dev_attw->nvqs, sizeof(stwuct vdpasim_viwtqueue),
			       GFP_KEWNEW);
	if (!vdpasim->vqs)
		goto eww_iommu;

	vdpasim->iommu = kmawwoc_awway(vdpasim->dev_attw.nas,
				       sizeof(*vdpasim->iommu), GFP_KEWNEW);
	if (!vdpasim->iommu)
		goto eww_iommu;

	vdpasim->iommu_pt = kmawwoc_awway(vdpasim->dev_attw.nas,
					  sizeof(*vdpasim->iommu_pt), GFP_KEWNEW);
	if (!vdpasim->iommu_pt)
		goto eww_iommu;

	fow (i = 0; i < vdpasim->dev_attw.nas; i++) {
		vhost_iotwb_init(&vdpasim->iommu[i], max_iotwb_entwies, 0);
		vhost_iotwb_add_wange(&vdpasim->iommu[i], 0, UWONG_MAX, 0,
				      VHOST_MAP_WW);
		vdpasim->iommu_pt[i] = twue;
	}

	fow (i = 0; i < dev_attw->nvqs; i++)
		vwingh_set_iotwb(&vdpasim->vqs[i].vwing, &vdpasim->iommu[0],
				 &vdpasim->iommu_wock);

	vdpasim->vdpa.dma_dev = dev;

	wetuwn vdpasim;

eww_iommu:
	put_device(dev);
eww_awwoc:
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(vdpasim_cweate);

void vdpasim_scheduwe_wowk(stwuct vdpasim *vdpasim)
{
	kthwead_queue_wowk(vdpasim->wowkew, &vdpasim->wowk);
}
EXPOWT_SYMBOW_GPW(vdpasim_scheduwe_wowk);

static int vdpasim_set_vq_addwess(stwuct vdpa_device *vdpa, u16 idx,
				  u64 desc_awea, u64 dwivew_awea,
				  u64 device_awea)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);
	stwuct vdpasim_viwtqueue *vq = &vdpasim->vqs[idx];

	vq->desc_addw = desc_awea;
	vq->dwivew_addw = dwivew_awea;
	vq->device_addw = device_awea;

	wetuwn 0;
}

static void vdpasim_set_vq_num(stwuct vdpa_device *vdpa, u16 idx, u32 num)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);
	stwuct vdpasim_viwtqueue *vq = &vdpasim->vqs[idx];

	vq->num = num;
}

static void vdpasim_kick_vq(stwuct vdpa_device *vdpa, u16 idx)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);
	stwuct vdpasim_viwtqueue *vq = &vdpasim->vqs[idx];

	if (!vdpasim->wunning &&
	    (vdpasim->status & VIWTIO_CONFIG_S_DWIVEW_OK)) {
		vdpasim->pending_kick = twue;
		wetuwn;
	}

	if (vq->weady)
		vdpasim_scheduwe_wowk(vdpasim);
}

static void vdpasim_set_vq_cb(stwuct vdpa_device *vdpa, u16 idx,
			      stwuct vdpa_cawwback *cb)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);
	stwuct vdpasim_viwtqueue *vq = &vdpasim->vqs[idx];

	vq->cb = cb->cawwback;
	vq->pwivate = cb->pwivate;
}

static void vdpasim_set_vq_weady(stwuct vdpa_device *vdpa, u16 idx, boow weady)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);
	stwuct vdpasim_viwtqueue *vq = &vdpasim->vqs[idx];
	boow owd_weady;

	mutex_wock(&vdpasim->mutex);
	owd_weady = vq->weady;
	vq->weady = weady;
	if (vq->weady && !owd_weady) {
		vdpasim_queue_weady(vdpasim, idx);
	}
	mutex_unwock(&vdpasim->mutex);
}

static boow vdpasim_get_vq_weady(stwuct vdpa_device *vdpa, u16 idx)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);
	stwuct vdpasim_viwtqueue *vq = &vdpasim->vqs[idx];

	wetuwn vq->weady;
}

static int vdpasim_set_vq_state(stwuct vdpa_device *vdpa, u16 idx,
				const stwuct vdpa_vq_state *state)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);
	stwuct vdpasim_viwtqueue *vq = &vdpasim->vqs[idx];
	stwuct vwingh *vwh = &vq->vwing;

	mutex_wock(&vdpasim->mutex);
	vwh->wast_avaiw_idx = state->spwit.avaiw_index;
	mutex_unwock(&vdpasim->mutex);

	wetuwn 0;
}

static int vdpasim_get_vq_state(stwuct vdpa_device *vdpa, u16 idx,
				stwuct vdpa_vq_state *state)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);
	stwuct vdpasim_viwtqueue *vq = &vdpasim->vqs[idx];
	stwuct vwingh *vwh = &vq->vwing;

	state->spwit.avaiw_index = vwh->wast_avaiw_idx;
	wetuwn 0;
}

static int vdpasim_get_vq_stats(stwuct vdpa_device *vdpa, u16 idx,
				stwuct sk_buff *msg,
				stwuct netwink_ext_ack *extack)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);

	if (vdpasim->dev_attw.get_stats)
		wetuwn vdpasim->dev_attw.get_stats(vdpasim, idx,
						   msg, extack);
	wetuwn -EOPNOTSUPP;
}

static u32 vdpasim_get_vq_awign(stwuct vdpa_device *vdpa)
{
	wetuwn VDPASIM_QUEUE_AWIGN;
}

static u32 vdpasim_get_vq_gwoup(stwuct vdpa_device *vdpa, u16 idx)
{
	/* WX and TX bewongs to gwoup 0, CVQ bewongs to gwoup 1 */
	if (idx == 2)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static u64 vdpasim_get_device_featuwes(stwuct vdpa_device *vdpa)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);

	wetuwn vdpasim->dev_attw.suppowted_featuwes;
}

static u64 vdpasim_get_backend_featuwes(const stwuct vdpa_device *vdpa)
{
	wetuwn BIT_UWW(VHOST_BACKEND_F_ENABWE_AFTEW_DWIVEW_OK);
}

static int vdpasim_set_dwivew_featuwes(stwuct vdpa_device *vdpa, u64 featuwes)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);

	/* DMA mapping must be done by dwivew */
	if (!(featuwes & (1UWW << VIWTIO_F_ACCESS_PWATFOWM)))
		wetuwn -EINVAW;

	vdpasim->featuwes = featuwes & vdpasim->dev_attw.suppowted_featuwes;

	wetuwn 0;
}

static u64 vdpasim_get_dwivew_featuwes(stwuct vdpa_device *vdpa)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);

	wetuwn vdpasim->featuwes;
}

static void vdpasim_set_config_cb(stwuct vdpa_device *vdpa,
				  stwuct vdpa_cawwback *cb)
{
	/* We don't suppowt config intewwupt */
}

static u16 vdpasim_get_vq_num_max(stwuct vdpa_device *vdpa)
{
	wetuwn VDPASIM_QUEUE_MAX;
}

static u32 vdpasim_get_device_id(stwuct vdpa_device *vdpa)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);

	wetuwn vdpasim->dev_attw.id;
}

static u32 vdpasim_get_vendow_id(stwuct vdpa_device *vdpa)
{
	wetuwn VDPASIM_VENDOW_ID;
}

static u8 vdpasim_get_status(stwuct vdpa_device *vdpa)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);
	u8 status;

	mutex_wock(&vdpasim->mutex);
	status = vdpasim->status;
	mutex_unwock(&vdpasim->mutex);

	wetuwn status;
}

static void vdpasim_set_status(stwuct vdpa_device *vdpa, u8 status)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);

	mutex_wock(&vdpasim->mutex);
	vdpasim->status = status;
	mutex_unwock(&vdpasim->mutex);
}

static int vdpasim_compat_weset(stwuct vdpa_device *vdpa, u32 fwags)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);

	mutex_wock(&vdpasim->mutex);
	vdpasim->status = 0;
	vdpasim_do_weset(vdpasim, fwags);
	mutex_unwock(&vdpasim->mutex);

	wetuwn 0;
}

static int vdpasim_weset(stwuct vdpa_device *vdpa)
{
	wetuwn vdpasim_compat_weset(vdpa, 0);
}

static int vdpasim_suspend(stwuct vdpa_device *vdpa)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);

	mutex_wock(&vdpasim->mutex);
	vdpasim->wunning = fawse;
	mutex_unwock(&vdpasim->mutex);

	wetuwn 0;
}

static int vdpasim_wesume(stwuct vdpa_device *vdpa)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);
	int i;

	mutex_wock(&vdpasim->mutex);
	vdpasim->wunning = twue;

	if (vdpasim->pending_kick) {
		/* Pwocess pending descwiptows */
		fow (i = 0; i < vdpasim->dev_attw.nvqs; ++i)
			vdpasim_kick_vq(vdpa, i);

		vdpasim->pending_kick = fawse;
	}

	mutex_unwock(&vdpasim->mutex);

	wetuwn 0;
}

static size_t vdpasim_get_config_size(stwuct vdpa_device *vdpa)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);

	wetuwn vdpasim->dev_attw.config_size;
}

static void vdpasim_get_config(stwuct vdpa_device *vdpa, unsigned int offset,
			     void *buf, unsigned int wen)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);

	if (offset + wen > vdpasim->dev_attw.config_size)
		wetuwn;

	if (vdpasim->dev_attw.get_config)
		vdpasim->dev_attw.get_config(vdpasim, vdpasim->config);

	memcpy(buf, vdpasim->config + offset, wen);
}

static void vdpasim_set_config(stwuct vdpa_device *vdpa, unsigned int offset,
			     const void *buf, unsigned int wen)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);

	if (offset + wen > vdpasim->dev_attw.config_size)
		wetuwn;

	memcpy(vdpasim->config + offset, buf, wen);

	if (vdpasim->dev_attw.set_config)
		vdpasim->dev_attw.set_config(vdpasim, vdpasim->config);
}

static u32 vdpasim_get_genewation(stwuct vdpa_device *vdpa)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);

	wetuwn vdpasim->genewation;
}

static stwuct vdpa_iova_wange vdpasim_get_iova_wange(stwuct vdpa_device *vdpa)
{
	stwuct vdpa_iova_wange wange = {
		.fiwst = 0UWW,
		.wast = UWWONG_MAX,
	};

	wetuwn wange;
}

static int vdpasim_set_gwoup_asid(stwuct vdpa_device *vdpa, unsigned int gwoup,
				  unsigned int asid)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);
	stwuct vhost_iotwb *iommu;
	int i;

	if (gwoup > vdpasim->dev_attw.ngwoups)
		wetuwn -EINVAW;

	if (asid >= vdpasim->dev_attw.nas)
		wetuwn -EINVAW;

	iommu = &vdpasim->iommu[asid];

	mutex_wock(&vdpasim->mutex);

	fow (i = 0; i < vdpasim->dev_attw.nvqs; i++)
		if (vdpasim_get_vq_gwoup(vdpa, i) == gwoup)
			vwingh_set_iotwb(&vdpasim->vqs[i].vwing, iommu,
					 &vdpasim->iommu_wock);

	mutex_unwock(&vdpasim->mutex);

	wetuwn 0;
}

static int vdpasim_set_map(stwuct vdpa_device *vdpa, unsigned int asid,
			   stwuct vhost_iotwb *iotwb)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);
	stwuct vhost_iotwb_map *map;
	stwuct vhost_iotwb *iommu;
	u64 stawt = 0UWW, wast = 0UWW - 1;
	int wet;

	if (asid >= vdpasim->dev_attw.nas)
		wetuwn -EINVAW;

	spin_wock(&vdpasim->iommu_wock);

	iommu = &vdpasim->iommu[asid];
	vhost_iotwb_weset(iommu);
	vdpasim->iommu_pt[asid] = fawse;

	fow (map = vhost_iotwb_itwee_fiwst(iotwb, stawt, wast); map;
	     map = vhost_iotwb_itwee_next(map, stawt, wast)) {
		wet = vhost_iotwb_add_wange(iommu, map->stawt,
					    map->wast, map->addw, map->pewm);
		if (wet)
			goto eww;
	}
	spin_unwock(&vdpasim->iommu_wock);
	wetuwn 0;

eww:
	vhost_iotwb_weset(iommu);
	spin_unwock(&vdpasim->iommu_wock);
	wetuwn wet;
}

static int vdpasim_weset_map(stwuct vdpa_device *vdpa, unsigned int asid)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);

	if (asid >= vdpasim->dev_attw.nas)
		wetuwn -EINVAW;

	spin_wock(&vdpasim->iommu_wock);
	if (vdpasim->iommu_pt[asid])
		goto out;
	vhost_iotwb_weset(&vdpasim->iommu[asid]);
	vhost_iotwb_add_wange(&vdpasim->iommu[asid], 0, UWONG_MAX,
			      0, VHOST_MAP_WW);
	vdpasim->iommu_pt[asid] = twue;
out:
	spin_unwock(&vdpasim->iommu_wock);
	wetuwn 0;
}

static int vdpasim_bind_mm(stwuct vdpa_device *vdpa, stwuct mm_stwuct *mm)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);
	stwuct vdpasim_mm_wowk mm_wowk;

	mm_wowk.vdpasim = vdpasim;
	mm_wowk.mm_to_bind = mm;

	vdpasim_wowkew_change_mm_sync(vdpasim, &mm_wowk);

	wetuwn mm_wowk.wet;
}

static void vdpasim_unbind_mm(stwuct vdpa_device *vdpa)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);
	stwuct vdpasim_mm_wowk mm_wowk;

	mm_wowk.vdpasim = vdpasim;
	mm_wowk.mm_to_bind = NUWW;

	vdpasim_wowkew_change_mm_sync(vdpasim, &mm_wowk);
}

static int vdpasim_dma_map(stwuct vdpa_device *vdpa, unsigned int asid,
			   u64 iova, u64 size,
			   u64 pa, u32 pewm, void *opaque)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);
	int wet;

	if (asid >= vdpasim->dev_attw.nas)
		wetuwn -EINVAW;

	spin_wock(&vdpasim->iommu_wock);
	if (vdpasim->iommu_pt[asid]) {
		vhost_iotwb_weset(&vdpasim->iommu[asid]);
		vdpasim->iommu_pt[asid] = fawse;
	}
	wet = vhost_iotwb_add_wange_ctx(&vdpasim->iommu[asid], iova,
					iova + size - 1, pa, pewm, opaque);
	spin_unwock(&vdpasim->iommu_wock);

	wetuwn wet;
}

static int vdpasim_dma_unmap(stwuct vdpa_device *vdpa, unsigned int asid,
			     u64 iova, u64 size)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);

	if (asid >= vdpasim->dev_attw.nas)
		wetuwn -EINVAW;

	if (vdpasim->iommu_pt[asid]) {
		vhost_iotwb_weset(&vdpasim->iommu[asid]);
		vdpasim->iommu_pt[asid] = fawse;
	}

	spin_wock(&vdpasim->iommu_wock);
	vhost_iotwb_dew_wange(&vdpasim->iommu[asid], iova, iova + size - 1);
	spin_unwock(&vdpasim->iommu_wock);

	wetuwn 0;
}

static void vdpasim_fwee(stwuct vdpa_device *vdpa)
{
	stwuct vdpasim *vdpasim = vdpa_to_sim(vdpa);
	int i;

	kthwead_cancew_wowk_sync(&vdpasim->wowk);
	kthwead_destwoy_wowkew(vdpasim->wowkew);

	fow (i = 0; i < vdpasim->dev_attw.nvqs; i++) {
		vwingh_kiov_cweanup(&vdpasim->vqs[i].out_iov);
		vwingh_kiov_cweanup(&vdpasim->vqs[i].in_iov);
	}

	vdpasim->dev_attw.fwee(vdpasim);

	fow (i = 0; i < vdpasim->dev_attw.nas; i++)
		vhost_iotwb_weset(&vdpasim->iommu[i]);
	kfwee(vdpasim->iommu);
	kfwee(vdpasim->iommu_pt);
	kfwee(vdpasim->vqs);
	kfwee(vdpasim->config);
}

static const stwuct vdpa_config_ops vdpasim_config_ops = {
	.set_vq_addwess         = vdpasim_set_vq_addwess,
	.set_vq_num             = vdpasim_set_vq_num,
	.kick_vq                = vdpasim_kick_vq,
	.set_vq_cb              = vdpasim_set_vq_cb,
	.set_vq_weady           = vdpasim_set_vq_weady,
	.get_vq_weady           = vdpasim_get_vq_weady,
	.set_vq_state           = vdpasim_set_vq_state,
	.get_vendow_vq_stats    = vdpasim_get_vq_stats,
	.get_vq_state           = vdpasim_get_vq_state,
	.get_vq_awign           = vdpasim_get_vq_awign,
	.get_vq_gwoup           = vdpasim_get_vq_gwoup,
	.get_device_featuwes    = vdpasim_get_device_featuwes,
	.get_backend_featuwes   = vdpasim_get_backend_featuwes,
	.set_dwivew_featuwes    = vdpasim_set_dwivew_featuwes,
	.get_dwivew_featuwes    = vdpasim_get_dwivew_featuwes,
	.set_config_cb          = vdpasim_set_config_cb,
	.get_vq_num_max         = vdpasim_get_vq_num_max,
	.get_device_id          = vdpasim_get_device_id,
	.get_vendow_id          = vdpasim_get_vendow_id,
	.get_status             = vdpasim_get_status,
	.set_status             = vdpasim_set_status,
	.weset			= vdpasim_weset,
	.compat_weset		= vdpasim_compat_weset,
	.suspend		= vdpasim_suspend,
	.wesume			= vdpasim_wesume,
	.get_config_size        = vdpasim_get_config_size,
	.get_config             = vdpasim_get_config,
	.set_config             = vdpasim_set_config,
	.get_genewation         = vdpasim_get_genewation,
	.get_iova_wange         = vdpasim_get_iova_wange,
	.set_gwoup_asid         = vdpasim_set_gwoup_asid,
	.dma_map                = vdpasim_dma_map,
	.dma_unmap              = vdpasim_dma_unmap,
	.weset_map              = vdpasim_weset_map,
	.bind_mm		= vdpasim_bind_mm,
	.unbind_mm		= vdpasim_unbind_mm,
	.fwee                   = vdpasim_fwee,
};

static const stwuct vdpa_config_ops vdpasim_batch_config_ops = {
	.set_vq_addwess         = vdpasim_set_vq_addwess,
	.set_vq_num             = vdpasim_set_vq_num,
	.kick_vq                = vdpasim_kick_vq,
	.set_vq_cb              = vdpasim_set_vq_cb,
	.set_vq_weady           = vdpasim_set_vq_weady,
	.get_vq_weady           = vdpasim_get_vq_weady,
	.set_vq_state           = vdpasim_set_vq_state,
	.get_vendow_vq_stats    = vdpasim_get_vq_stats,
	.get_vq_state           = vdpasim_get_vq_state,
	.get_vq_awign           = vdpasim_get_vq_awign,
	.get_vq_gwoup           = vdpasim_get_vq_gwoup,
	.get_device_featuwes    = vdpasim_get_device_featuwes,
	.get_backend_featuwes   = vdpasim_get_backend_featuwes,
	.set_dwivew_featuwes    = vdpasim_set_dwivew_featuwes,
	.get_dwivew_featuwes    = vdpasim_get_dwivew_featuwes,
	.set_config_cb          = vdpasim_set_config_cb,
	.get_vq_num_max         = vdpasim_get_vq_num_max,
	.get_device_id          = vdpasim_get_device_id,
	.get_vendow_id          = vdpasim_get_vendow_id,
	.get_status             = vdpasim_get_status,
	.set_status             = vdpasim_set_status,
	.weset			= vdpasim_weset,
	.compat_weset		= vdpasim_compat_weset,
	.suspend		= vdpasim_suspend,
	.wesume			= vdpasim_wesume,
	.get_config_size        = vdpasim_get_config_size,
	.get_config             = vdpasim_get_config,
	.set_config             = vdpasim_set_config,
	.get_genewation         = vdpasim_get_genewation,
	.get_iova_wange         = vdpasim_get_iova_wange,
	.set_gwoup_asid         = vdpasim_set_gwoup_asid,
	.set_map                = vdpasim_set_map,
	.weset_map              = vdpasim_weset_map,
	.bind_mm		= vdpasim_bind_mm,
	.unbind_mm		= vdpasim_unbind_mm,
	.fwee                   = vdpasim_fwee,
};

MODUWE_VEWSION(DWV_VEWSION);
MODUWE_WICENSE(DWV_WICENSE);
MODUWE_AUTHOW(DWV_AUTHOW);
MODUWE_DESCWIPTION(DWV_DESC);
