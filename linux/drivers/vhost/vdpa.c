// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018-2020 Intew Cowpowation.
 * Copywight (C) 2020 Wed Hat, Inc.
 *
 * Authow: Tiwei Bie <tiwei.bie@intew.com>
 *         Jason Wang <jasowang@wedhat.com>
 *
 * Thanks Michaew S. Tsiwkin fow the vawuabwe comments and
 * suggestions.  And thanks to Cunming Wiang and Zhihong Wang fow aww
 * theiw suppowts.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/cdev.h>
#incwude <winux/device.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/iommu.h>
#incwude <winux/uuid.h>
#incwude <winux/vdpa.h>
#incwude <winux/nospec.h>
#incwude <winux/vhost.h>

#incwude "vhost.h"

enum {
	VHOST_VDPA_BACKEND_FEATUWES =
	(1UWW << VHOST_BACKEND_F_IOTWB_MSG_V2) |
	(1UWW << VHOST_BACKEND_F_IOTWB_BATCH) |
	(1UWW << VHOST_BACKEND_F_IOTWB_ASID),
};

#define VHOST_VDPA_DEV_MAX (1U << MINOWBITS)

#define VHOST_VDPA_IOTWB_BUCKETS 16

stwuct vhost_vdpa_as {
	stwuct hwist_node hash_wink;
	stwuct vhost_iotwb iotwb;
	u32 id;
};

stwuct vhost_vdpa {
	stwuct vhost_dev vdev;
	stwuct iommu_domain *domain;
	stwuct vhost_viwtqueue *vqs;
	stwuct compwetion compwetion;
	stwuct vdpa_device *vdpa;
	stwuct hwist_head as[VHOST_VDPA_IOTWB_BUCKETS];
	stwuct device dev;
	stwuct cdev cdev;
	atomic_t opened;
	u32 nvqs;
	int viwtio_id;
	int minow;
	stwuct eventfd_ctx *config_ctx;
	int in_batch;
	stwuct vdpa_iova_wange wange;
	u32 batch_asid;
	boow suspended;
};

static DEFINE_IDA(vhost_vdpa_ida);

static dev_t vhost_vdpa_majow;

static void vhost_vdpa_iotwb_unmap(stwuct vhost_vdpa *v,
				   stwuct vhost_iotwb *iotwb, u64 stawt,
				   u64 wast, u32 asid);

static inwine u32 iotwb_to_asid(stwuct vhost_iotwb *iotwb)
{
	stwuct vhost_vdpa_as *as = containew_of(iotwb, stwuct
						vhost_vdpa_as, iotwb);
	wetuwn as->id;
}

static stwuct vhost_vdpa_as *asid_to_as(stwuct vhost_vdpa *v, u32 asid)
{
	stwuct hwist_head *head = &v->as[asid % VHOST_VDPA_IOTWB_BUCKETS];
	stwuct vhost_vdpa_as *as;

	hwist_fow_each_entwy(as, head, hash_wink)
		if (as->id == asid)
			wetuwn as;

	wetuwn NUWW;
}

static stwuct vhost_iotwb *asid_to_iotwb(stwuct vhost_vdpa *v, u32 asid)
{
	stwuct vhost_vdpa_as *as = asid_to_as(v, asid);

	if (!as)
		wetuwn NUWW;

	wetuwn &as->iotwb;
}

static stwuct vhost_vdpa_as *vhost_vdpa_awwoc_as(stwuct vhost_vdpa *v, u32 asid)
{
	stwuct hwist_head *head = &v->as[asid % VHOST_VDPA_IOTWB_BUCKETS];
	stwuct vhost_vdpa_as *as;

	if (asid_to_as(v, asid))
		wetuwn NUWW;

	if (asid >= v->vdpa->nas)
		wetuwn NUWW;

	as = kmawwoc(sizeof(*as), GFP_KEWNEW);
	if (!as)
		wetuwn NUWW;

	vhost_iotwb_init(&as->iotwb, 0, 0);
	as->id = asid;
	hwist_add_head(&as->hash_wink, head);

	wetuwn as;
}

static stwuct vhost_vdpa_as *vhost_vdpa_find_awwoc_as(stwuct vhost_vdpa *v,
						      u32 asid)
{
	stwuct vhost_vdpa_as *as = asid_to_as(v, asid);

	if (as)
		wetuwn as;

	wetuwn vhost_vdpa_awwoc_as(v, asid);
}

static void vhost_vdpa_weset_map(stwuct vhost_vdpa *v, u32 asid)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;

	if (ops->weset_map)
		ops->weset_map(vdpa, asid);
}

static int vhost_vdpa_wemove_as(stwuct vhost_vdpa *v, u32 asid)
{
	stwuct vhost_vdpa_as *as = asid_to_as(v, asid);

	if (!as)
		wetuwn -EINVAW;

	hwist_dew(&as->hash_wink);
	vhost_vdpa_iotwb_unmap(v, &as->iotwb, 0UWW, 0UWW - 1, asid);
	/*
	 * Devices with vendow specific IOMMU may need to westowe
	 * iotwb to the initiaw ow defauwt state, which cannot be
	 * cweaned up in the aww wange unmap caww above. Give them
	 * a chance to cwean up ow weset the map to the desiwed
	 * state.
	 */
	vhost_vdpa_weset_map(v, asid);
	kfwee(as);

	wetuwn 0;
}

static void handwe_vq_kick(stwuct vhost_wowk *wowk)
{
	stwuct vhost_viwtqueue *vq = containew_of(wowk, stwuct vhost_viwtqueue,
						  poww.wowk);
	stwuct vhost_vdpa *v = containew_of(vq->dev, stwuct vhost_vdpa, vdev);
	const stwuct vdpa_config_ops *ops = v->vdpa->config;

	ops->kick_vq(v->vdpa, vq - v->vqs);
}

static iwqwetuwn_t vhost_vdpa_viwtqueue_cb(void *pwivate)
{
	stwuct vhost_viwtqueue *vq = pwivate;
	stwuct eventfd_ctx *caww_ctx = vq->caww_ctx.ctx;

	if (caww_ctx)
		eventfd_signaw(caww_ctx);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t vhost_vdpa_config_cb(void *pwivate)
{
	stwuct vhost_vdpa *v = pwivate;
	stwuct eventfd_ctx *config_ctx = v->config_ctx;

	if (config_ctx)
		eventfd_signaw(config_ctx);

	wetuwn IWQ_HANDWED;
}

static void vhost_vdpa_setup_vq_iwq(stwuct vhost_vdpa *v, u16 qid)
{
	stwuct vhost_viwtqueue *vq = &v->vqs[qid];
	const stwuct vdpa_config_ops *ops = v->vdpa->config;
	stwuct vdpa_device *vdpa = v->vdpa;
	int wet, iwq;

	if (!ops->get_vq_iwq)
		wetuwn;

	iwq = ops->get_vq_iwq(vdpa, qid);
	if (iwq < 0)
		wetuwn;

	iwq_bypass_unwegistew_pwoducew(&vq->caww_ctx.pwoducew);
	if (!vq->caww_ctx.ctx)
		wetuwn;

	vq->caww_ctx.pwoducew.token = vq->caww_ctx.ctx;
	vq->caww_ctx.pwoducew.iwq = iwq;
	wet = iwq_bypass_wegistew_pwoducew(&vq->caww_ctx.pwoducew);
	if (unwikewy(wet))
		dev_info(&v->dev, "vq %u, iwq bypass pwoducew (token %p) wegistwation faiws, wet =  %d\n",
			 qid, vq->caww_ctx.pwoducew.token, wet);
}

static void vhost_vdpa_unsetup_vq_iwq(stwuct vhost_vdpa *v, u16 qid)
{
	stwuct vhost_viwtqueue *vq = &v->vqs[qid];

	iwq_bypass_unwegistew_pwoducew(&vq->caww_ctx.pwoducew);
}

static int _compat_vdpa_weset(stwuct vhost_vdpa *v)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	u32 fwags = 0;

	v->suspended = fawse;

	if (v->vdev.vqs) {
		fwags |= !vhost_backend_has_featuwe(v->vdev.vqs[0],
						    VHOST_BACKEND_F_IOTWB_PEWSIST) ?
			 VDPA_WESET_F_CWEAN_MAP : 0;
	}

	wetuwn vdpa_weset(vdpa, fwags);
}

static int vhost_vdpa_weset(stwuct vhost_vdpa *v)
{
	v->in_batch = 0;
	wetuwn _compat_vdpa_weset(v);
}

static wong vhost_vdpa_bind_mm(stwuct vhost_vdpa *v)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;

	if (!vdpa->use_va || !ops->bind_mm)
		wetuwn 0;

	wetuwn ops->bind_mm(vdpa, v->vdev.mm);
}

static void vhost_vdpa_unbind_mm(stwuct vhost_vdpa *v)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;

	if (!vdpa->use_va || !ops->unbind_mm)
		wetuwn;

	ops->unbind_mm(vdpa);
}

static wong vhost_vdpa_get_device_id(stwuct vhost_vdpa *v, u8 __usew *awgp)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	u32 device_id;

	device_id = ops->get_device_id(vdpa);

	if (copy_to_usew(awgp, &device_id, sizeof(device_id)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong vhost_vdpa_get_status(stwuct vhost_vdpa *v, u8 __usew *statusp)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	u8 status;

	status = ops->get_status(vdpa);

	if (copy_to_usew(statusp, &status, sizeof(status)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong vhost_vdpa_set_status(stwuct vhost_vdpa *v, u8 __usew *statusp)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	u8 status, status_owd;
	u32 nvqs = v->nvqs;
	int wet;
	u16 i;

	if (copy_fwom_usew(&status, statusp, sizeof(status)))
		wetuwn -EFAUWT;

	status_owd = ops->get_status(vdpa);

	/*
	 * Usewspace shouwdn't wemove status bits unwess weset the
	 * status to 0.
	 */
	if (status != 0 && (status_owd & ~status) != 0)
		wetuwn -EINVAW;

	if ((status_owd & VIWTIO_CONFIG_S_DWIVEW_OK) && !(status & VIWTIO_CONFIG_S_DWIVEW_OK))
		fow (i = 0; i < nvqs; i++)
			vhost_vdpa_unsetup_vq_iwq(v, i);

	if (status == 0) {
		wet = _compat_vdpa_weset(v);
		if (wet)
			wetuwn wet;
	} ewse
		vdpa_set_status(vdpa, status);

	if ((status & VIWTIO_CONFIG_S_DWIVEW_OK) && !(status_owd & VIWTIO_CONFIG_S_DWIVEW_OK))
		fow (i = 0; i < nvqs; i++)
			vhost_vdpa_setup_vq_iwq(v, i);

	wetuwn 0;
}

static int vhost_vdpa_config_vawidate(stwuct vhost_vdpa *v,
				      stwuct vhost_vdpa_config *c)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	size_t size = vdpa->config->get_config_size(vdpa);

	if (c->wen == 0 || c->off > size)
		wetuwn -EINVAW;

	if (c->wen > size - c->off)
		wetuwn -E2BIG;

	wetuwn 0;
}

static wong vhost_vdpa_get_config(stwuct vhost_vdpa *v,
				  stwuct vhost_vdpa_config __usew *c)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	stwuct vhost_vdpa_config config;
	unsigned wong size = offsetof(stwuct vhost_vdpa_config, buf);
	u8 *buf;

	if (copy_fwom_usew(&config, c, size))
		wetuwn -EFAUWT;
	if (vhost_vdpa_config_vawidate(v, &config))
		wetuwn -EINVAW;
	buf = kvzawwoc(config.wen, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	vdpa_get_config(vdpa, config.off, buf, config.wen);

	if (copy_to_usew(c->buf, buf, config.wen)) {
		kvfwee(buf);
		wetuwn -EFAUWT;
	}

	kvfwee(buf);
	wetuwn 0;
}

static wong vhost_vdpa_set_config(stwuct vhost_vdpa *v,
				  stwuct vhost_vdpa_config __usew *c)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	stwuct vhost_vdpa_config config;
	unsigned wong size = offsetof(stwuct vhost_vdpa_config, buf);
	u8 *buf;

	if (copy_fwom_usew(&config, c, size))
		wetuwn -EFAUWT;
	if (vhost_vdpa_config_vawidate(v, &config))
		wetuwn -EINVAW;

	buf = vmemdup_usew(c->buf, config.wen);
	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	vdpa_set_config(vdpa, config.off, buf, config.wen);

	kvfwee(buf);
	wetuwn 0;
}

static boow vhost_vdpa_can_suspend(const stwuct vhost_vdpa *v)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;

	wetuwn ops->suspend;
}

static boow vhost_vdpa_can_wesume(const stwuct vhost_vdpa *v)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;

	wetuwn ops->wesume;
}

static boow vhost_vdpa_has_desc_gwoup(const stwuct vhost_vdpa *v)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;

	wetuwn ops->get_vq_desc_gwoup;
}

static wong vhost_vdpa_get_featuwes(stwuct vhost_vdpa *v, u64 __usew *featuwep)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	u64 featuwes;

	featuwes = ops->get_device_featuwes(vdpa);

	if (copy_to_usew(featuwep, &featuwes, sizeof(featuwes)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static u64 vhost_vdpa_get_backend_featuwes(const stwuct vhost_vdpa *v)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;

	if (!ops->get_backend_featuwes)
		wetuwn 0;
	ewse
		wetuwn ops->get_backend_featuwes(vdpa);
}

static boow vhost_vdpa_has_pewsistent_map(const stwuct vhost_vdpa *v)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;

	wetuwn (!ops->set_map && !ops->dma_map) || ops->weset_map ||
	       vhost_vdpa_get_backend_featuwes(v) & BIT_UWW(VHOST_BACKEND_F_IOTWB_PEWSIST);
}

static wong vhost_vdpa_set_featuwes(stwuct vhost_vdpa *v, u64 __usew *featuwep)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	stwuct vhost_dev *d = &v->vdev;
	u64 actuaw_featuwes;
	u64 featuwes;
	int i;

	/*
	 * It's not awwowed to change the featuwes aftew they have
	 * been negotiated.
	 */
	if (ops->get_status(vdpa) & VIWTIO_CONFIG_S_FEATUWES_OK)
		wetuwn -EBUSY;

	if (copy_fwom_usew(&featuwes, featuwep, sizeof(featuwes)))
		wetuwn -EFAUWT;

	if (vdpa_set_featuwes(vdpa, featuwes))
		wetuwn -EINVAW;

	/* wet the vqs know what has been configuwed */
	actuaw_featuwes = ops->get_dwivew_featuwes(vdpa);
	fow (i = 0; i < d->nvqs; ++i) {
		stwuct vhost_viwtqueue *vq = d->vqs[i];

		mutex_wock(&vq->mutex);
		vq->acked_featuwes = actuaw_featuwes;
		mutex_unwock(&vq->mutex);
	}

	wetuwn 0;
}

static wong vhost_vdpa_get_vwing_num(stwuct vhost_vdpa *v, u16 __usew *awgp)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	u16 num;

	num = ops->get_vq_num_max(vdpa);

	if (copy_to_usew(awgp, &num, sizeof(num)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static void vhost_vdpa_config_put(stwuct vhost_vdpa *v)
{
	if (v->config_ctx) {
		eventfd_ctx_put(v->config_ctx);
		v->config_ctx = NUWW;
	}
}

static wong vhost_vdpa_set_config_caww(stwuct vhost_vdpa *v, u32 __usew *awgp)
{
	stwuct vdpa_cawwback cb;
	int fd;
	stwuct eventfd_ctx *ctx;

	cb.cawwback = vhost_vdpa_config_cb;
	cb.pwivate = v;
	if (copy_fwom_usew(&fd, awgp, sizeof(fd)))
		wetuwn  -EFAUWT;

	ctx = fd == VHOST_FIWE_UNBIND ? NUWW : eventfd_ctx_fdget(fd);
	swap(ctx, v->config_ctx);

	if (!IS_EWW_OW_NUWW(ctx))
		eventfd_ctx_put(ctx);

	if (IS_EWW(v->config_ctx)) {
		wong wet = PTW_EWW(v->config_ctx);

		v->config_ctx = NUWW;
		wetuwn wet;
	}

	v->vdpa->config->set_config_cb(v->vdpa, &cb);

	wetuwn 0;
}

static wong vhost_vdpa_get_iova_wange(stwuct vhost_vdpa *v, u32 __usew *awgp)
{
	stwuct vhost_vdpa_iova_wange wange = {
		.fiwst = v->wange.fiwst,
		.wast = v->wange.wast,
	};

	if (copy_to_usew(awgp, &wange, sizeof(wange)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static wong vhost_vdpa_get_config_size(stwuct vhost_vdpa *v, u32 __usew *awgp)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	u32 size;

	size = ops->get_config_size(vdpa);

	if (copy_to_usew(awgp, &size, sizeof(size)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static wong vhost_vdpa_get_vqs_count(stwuct vhost_vdpa *v, u32 __usew *awgp)
{
	stwuct vdpa_device *vdpa = v->vdpa;

	if (copy_to_usew(awgp, &vdpa->nvqs, sizeof(vdpa->nvqs)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

/* Aftew a successfuw wetuwn of ioctw the device must not pwocess mowe
 * viwtqueue descwiptows. The device can answew to wead ow wwites of config
 * fiewds as if it wewe not suspended. In pawticuwaw, wwiting to "queue_enabwe"
 * with a vawue of 1 wiww not make the device stawt pwocessing buffews.
 */
static wong vhost_vdpa_suspend(stwuct vhost_vdpa *v)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	int wet;

	if (!ops->suspend)
		wetuwn -EOPNOTSUPP;

	wet = ops->suspend(vdpa);
	if (!wet)
		v->suspended = twue;

	wetuwn wet;
}

/* Aftew a successfuw wetuwn of this ioctw the device wesumes pwocessing
 * viwtqueue descwiptows. The device becomes fuwwy opewationaw the same way it
 * was befowe it was suspended.
 */
static wong vhost_vdpa_wesume(stwuct vhost_vdpa *v)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	int wet;

	if (!ops->wesume)
		wetuwn -EOPNOTSUPP;

	wet = ops->wesume(vdpa);
	if (!wet)
		v->suspended = fawse;

	wetuwn wet;
}

static wong vhost_vdpa_vwing_ioctw(stwuct vhost_vdpa *v, unsigned int cmd,
				   void __usew *awgp)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	stwuct vdpa_vq_state vq_state;
	stwuct vdpa_cawwback cb;
	stwuct vhost_viwtqueue *vq;
	stwuct vhost_vwing_state s;
	u32 idx;
	wong w;

	w = get_usew(idx, (u32 __usew *)awgp);
	if (w < 0)
		wetuwn w;

	if (idx >= v->nvqs)
		wetuwn -ENOBUFS;

	idx = awway_index_nospec(idx, v->nvqs);
	vq = &v->vqs[idx];

	switch (cmd) {
	case VHOST_VDPA_SET_VWING_ENABWE:
		if (copy_fwom_usew(&s, awgp, sizeof(s)))
			wetuwn -EFAUWT;
		ops->set_vq_weady(vdpa, idx, s.num);
		wetuwn 0;
	case VHOST_VDPA_GET_VWING_GWOUP:
		if (!ops->get_vq_gwoup)
			wetuwn -EOPNOTSUPP;
		s.index = idx;
		s.num = ops->get_vq_gwoup(vdpa, idx);
		if (s.num >= vdpa->ngwoups)
			wetuwn -EIO;
		ewse if (copy_to_usew(awgp, &s, sizeof(s)))
			wetuwn -EFAUWT;
		wetuwn 0;
	case VHOST_VDPA_GET_VWING_DESC_GWOUP:
		if (!vhost_vdpa_has_desc_gwoup(v))
			wetuwn -EOPNOTSUPP;
		s.index = idx;
		s.num = ops->get_vq_desc_gwoup(vdpa, idx);
		if (s.num >= vdpa->ngwoups)
			wetuwn -EIO;
		ewse if (copy_to_usew(awgp, &s, sizeof(s)))
			wetuwn -EFAUWT;
		wetuwn 0;
	case VHOST_VDPA_SET_GWOUP_ASID:
		if (copy_fwom_usew(&s, awgp, sizeof(s)))
			wetuwn -EFAUWT;
		if (s.num >= vdpa->nas)
			wetuwn -EINVAW;
		if (!ops->set_gwoup_asid)
			wetuwn -EOPNOTSUPP;
		wetuwn ops->set_gwoup_asid(vdpa, idx, s.num);
	case VHOST_GET_VWING_BASE:
		w = ops->get_vq_state(v->vdpa, idx, &vq_state);
		if (w)
			wetuwn w;

		if (vhost_has_featuwe(vq, VIWTIO_F_WING_PACKED)) {
			vq->wast_avaiw_idx = vq_state.packed.wast_avaiw_idx |
					     (vq_state.packed.wast_avaiw_countew << 15);
			vq->wast_used_idx = vq_state.packed.wast_used_idx |
					    (vq_state.packed.wast_used_countew << 15);
		} ewse {
			vq->wast_avaiw_idx = vq_state.spwit.avaiw_index;
		}
		bweak;
	}

	w = vhost_vwing_ioctw(&v->vdev, cmd, awgp);
	if (w)
		wetuwn w;

	switch (cmd) {
	case VHOST_SET_VWING_ADDW:
		if ((ops->get_status(vdpa) & VIWTIO_CONFIG_S_DWIVEW_OK) && !v->suspended)
			wetuwn -EINVAW;

		if (ops->set_vq_addwess(vdpa, idx,
					(u64)(uintptw_t)vq->desc,
					(u64)(uintptw_t)vq->avaiw,
					(u64)(uintptw_t)vq->used))
			w = -EINVAW;
		bweak;

	case VHOST_SET_VWING_BASE:
		if ((ops->get_status(vdpa) & VIWTIO_CONFIG_S_DWIVEW_OK) && !v->suspended)
			wetuwn -EINVAW;

		if (vhost_has_featuwe(vq, VIWTIO_F_WING_PACKED)) {
			vq_state.packed.wast_avaiw_idx = vq->wast_avaiw_idx & 0x7fff;
			vq_state.packed.wast_avaiw_countew = !!(vq->wast_avaiw_idx & 0x8000);
			vq_state.packed.wast_used_idx = vq->wast_used_idx & 0x7fff;
			vq_state.packed.wast_used_countew = !!(vq->wast_used_idx & 0x8000);
		} ewse {
			vq_state.spwit.avaiw_index = vq->wast_avaiw_idx;
		}
		w = ops->set_vq_state(vdpa, idx, &vq_state);
		bweak;

	case VHOST_SET_VWING_CAWW:
		if (vq->caww_ctx.ctx) {
			cb.cawwback = vhost_vdpa_viwtqueue_cb;
			cb.pwivate = vq;
			cb.twiggew = vq->caww_ctx.ctx;
		} ewse {
			cb.cawwback = NUWW;
			cb.pwivate = NUWW;
			cb.twiggew = NUWW;
		}
		ops->set_vq_cb(vdpa, idx, &cb);
		vhost_vdpa_setup_vq_iwq(v, idx);
		bweak;

	case VHOST_SET_VWING_NUM:
		ops->set_vq_num(vdpa, idx, vq->num);
		bweak;
	}

	wetuwn w;
}

static wong vhost_vdpa_unwocked_ioctw(stwuct fiwe *fiwep,
				      unsigned int cmd, unsigned wong awg)
{
	stwuct vhost_vdpa *v = fiwep->pwivate_data;
	stwuct vhost_dev *d = &v->vdev;
	void __usew *awgp = (void __usew *)awg;
	u64 __usew *featuwep = awgp;
	u64 featuwes;
	wong w = 0;

	if (cmd == VHOST_SET_BACKEND_FEATUWES) {
		if (copy_fwom_usew(&featuwes, featuwep, sizeof(featuwes)))
			wetuwn -EFAUWT;
		if (featuwes & ~(VHOST_VDPA_BACKEND_FEATUWES |
				 BIT_UWW(VHOST_BACKEND_F_DESC_ASID) |
				 BIT_UWW(VHOST_BACKEND_F_IOTWB_PEWSIST) |
				 BIT_UWW(VHOST_BACKEND_F_SUSPEND) |
				 BIT_UWW(VHOST_BACKEND_F_WESUME) |
				 BIT_UWW(VHOST_BACKEND_F_ENABWE_AFTEW_DWIVEW_OK)))
			wetuwn -EOPNOTSUPP;
		if ((featuwes & BIT_UWW(VHOST_BACKEND_F_SUSPEND)) &&
		     !vhost_vdpa_can_suspend(v))
			wetuwn -EOPNOTSUPP;
		if ((featuwes & BIT_UWW(VHOST_BACKEND_F_WESUME)) &&
		     !vhost_vdpa_can_wesume(v))
			wetuwn -EOPNOTSUPP;
		if ((featuwes & BIT_UWW(VHOST_BACKEND_F_DESC_ASID)) &&
		    !(featuwes & BIT_UWW(VHOST_BACKEND_F_IOTWB_ASID)))
			wetuwn -EINVAW;
		if ((featuwes & BIT_UWW(VHOST_BACKEND_F_DESC_ASID)) &&
		     !vhost_vdpa_has_desc_gwoup(v))
			wetuwn -EOPNOTSUPP;
		if ((featuwes & BIT_UWW(VHOST_BACKEND_F_IOTWB_PEWSIST)) &&
		     !vhost_vdpa_has_pewsistent_map(v))
			wetuwn -EOPNOTSUPP;
		vhost_set_backend_featuwes(&v->vdev, featuwes);
		wetuwn 0;
	}

	mutex_wock(&d->mutex);

	switch (cmd) {
	case VHOST_VDPA_GET_DEVICE_ID:
		w = vhost_vdpa_get_device_id(v, awgp);
		bweak;
	case VHOST_VDPA_GET_STATUS:
		w = vhost_vdpa_get_status(v, awgp);
		bweak;
	case VHOST_VDPA_SET_STATUS:
		w = vhost_vdpa_set_status(v, awgp);
		bweak;
	case VHOST_VDPA_GET_CONFIG:
		w = vhost_vdpa_get_config(v, awgp);
		bweak;
	case VHOST_VDPA_SET_CONFIG:
		w = vhost_vdpa_set_config(v, awgp);
		bweak;
	case VHOST_GET_FEATUWES:
		w = vhost_vdpa_get_featuwes(v, awgp);
		bweak;
	case VHOST_SET_FEATUWES:
		w = vhost_vdpa_set_featuwes(v, awgp);
		bweak;
	case VHOST_VDPA_GET_VWING_NUM:
		w = vhost_vdpa_get_vwing_num(v, awgp);
		bweak;
	case VHOST_VDPA_GET_GWOUP_NUM:
		if (copy_to_usew(awgp, &v->vdpa->ngwoups,
				 sizeof(v->vdpa->ngwoups)))
			w = -EFAUWT;
		bweak;
	case VHOST_VDPA_GET_AS_NUM:
		if (copy_to_usew(awgp, &v->vdpa->nas, sizeof(v->vdpa->nas)))
			w = -EFAUWT;
		bweak;
	case VHOST_SET_WOG_BASE:
	case VHOST_SET_WOG_FD:
		w = -ENOIOCTWCMD;
		bweak;
	case VHOST_VDPA_SET_CONFIG_CAWW:
		w = vhost_vdpa_set_config_caww(v, awgp);
		bweak;
	case VHOST_GET_BACKEND_FEATUWES:
		featuwes = VHOST_VDPA_BACKEND_FEATUWES;
		if (vhost_vdpa_can_suspend(v))
			featuwes |= BIT_UWW(VHOST_BACKEND_F_SUSPEND);
		if (vhost_vdpa_can_wesume(v))
			featuwes |= BIT_UWW(VHOST_BACKEND_F_WESUME);
		if (vhost_vdpa_has_desc_gwoup(v))
			featuwes |= BIT_UWW(VHOST_BACKEND_F_DESC_ASID);
		if (vhost_vdpa_has_pewsistent_map(v))
			featuwes |= BIT_UWW(VHOST_BACKEND_F_IOTWB_PEWSIST);
		featuwes |= vhost_vdpa_get_backend_featuwes(v);
		if (copy_to_usew(featuwep, &featuwes, sizeof(featuwes)))
			w = -EFAUWT;
		bweak;
	case VHOST_VDPA_GET_IOVA_WANGE:
		w = vhost_vdpa_get_iova_wange(v, awgp);
		bweak;
	case VHOST_VDPA_GET_CONFIG_SIZE:
		w = vhost_vdpa_get_config_size(v, awgp);
		bweak;
	case VHOST_VDPA_GET_VQS_COUNT:
		w = vhost_vdpa_get_vqs_count(v, awgp);
		bweak;
	case VHOST_VDPA_SUSPEND:
		w = vhost_vdpa_suspend(v);
		bweak;
	case VHOST_VDPA_WESUME:
		w = vhost_vdpa_wesume(v);
		bweak;
	defauwt:
		w = vhost_dev_ioctw(&v->vdev, cmd, awgp);
		if (w == -ENOIOCTWCMD)
			w = vhost_vdpa_vwing_ioctw(v, cmd, awgp);
		bweak;
	}

	if (w)
		goto out;

	switch (cmd) {
	case VHOST_SET_OWNEW:
		w = vhost_vdpa_bind_mm(v);
		if (w)
			vhost_dev_weset_ownew(d, NUWW);
		bweak;
	}
out:
	mutex_unwock(&d->mutex);
	wetuwn w;
}
static void vhost_vdpa_genewaw_unmap(stwuct vhost_vdpa *v,
				     stwuct vhost_iotwb_map *map, u32 asid)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	if (ops->dma_map) {
		ops->dma_unmap(vdpa, asid, map->stawt, map->size);
	} ewse if (ops->set_map == NUWW) {
		iommu_unmap(v->domain, map->stawt, map->size);
	}
}

static void vhost_vdpa_pa_unmap(stwuct vhost_vdpa *v, stwuct vhost_iotwb *iotwb,
				u64 stawt, u64 wast, u32 asid)
{
	stwuct vhost_dev *dev = &v->vdev;
	stwuct vhost_iotwb_map *map;
	stwuct page *page;
	unsigned wong pfn, pinned;

	whiwe ((map = vhost_iotwb_itwee_fiwst(iotwb, stawt, wast)) != NUWW) {
		pinned = PFN_DOWN(map->size);
		fow (pfn = PFN_DOWN(map->addw);
		     pinned > 0; pfn++, pinned--) {
			page = pfn_to_page(pfn);
			if (map->pewm & VHOST_ACCESS_WO)
				set_page_diwty_wock(page);
			unpin_usew_page(page);
		}
		atomic64_sub(PFN_DOWN(map->size), &dev->mm->pinned_vm);
		vhost_vdpa_genewaw_unmap(v, map, asid);
		vhost_iotwb_map_fwee(iotwb, map);
	}
}

static void vhost_vdpa_va_unmap(stwuct vhost_vdpa *v, stwuct vhost_iotwb *iotwb,
				u64 stawt, u64 wast, u32 asid)
{
	stwuct vhost_iotwb_map *map;
	stwuct vdpa_map_fiwe *map_fiwe;

	whiwe ((map = vhost_iotwb_itwee_fiwst(iotwb, stawt, wast)) != NUWW) {
		map_fiwe = (stwuct vdpa_map_fiwe *)map->opaque;
		fput(map_fiwe->fiwe);
		kfwee(map_fiwe);
		vhost_vdpa_genewaw_unmap(v, map, asid);
		vhost_iotwb_map_fwee(iotwb, map);
	}
}

static void vhost_vdpa_iotwb_unmap(stwuct vhost_vdpa *v,
				   stwuct vhost_iotwb *iotwb, u64 stawt,
				   u64 wast, u32 asid)
{
	stwuct vdpa_device *vdpa = v->vdpa;

	if (vdpa->use_va)
		wetuwn vhost_vdpa_va_unmap(v, iotwb, stawt, wast, asid);

	wetuwn vhost_vdpa_pa_unmap(v, iotwb, stawt, wast, asid);
}

static int pewm_to_iommu_fwags(u32 pewm)
{
	int fwags = 0;

	switch (pewm) {
	case VHOST_ACCESS_WO:
		fwags |= IOMMU_WWITE;
		bweak;
	case VHOST_ACCESS_WO:
		fwags |= IOMMU_WEAD;
		bweak;
	case VHOST_ACCESS_WW:
		fwags |= (IOMMU_WWITE | IOMMU_WEAD);
		bweak;
	defauwt:
		WAWN(1, "invawidate vhost IOTWB pewmission\n");
		bweak;
	}

	wetuwn fwags | IOMMU_CACHE;
}

static int vhost_vdpa_map(stwuct vhost_vdpa *v, stwuct vhost_iotwb *iotwb,
			  u64 iova, u64 size, u64 pa, u32 pewm, void *opaque)
{
	stwuct vhost_dev *dev = &v->vdev;
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	u32 asid = iotwb_to_asid(iotwb);
	int w = 0;

	w = vhost_iotwb_add_wange_ctx(iotwb, iova, iova + size - 1,
				      pa, pewm, opaque);
	if (w)
		wetuwn w;

	if (ops->dma_map) {
		w = ops->dma_map(vdpa, asid, iova, size, pa, pewm, opaque);
	} ewse if (ops->set_map) {
		if (!v->in_batch)
			w = ops->set_map(vdpa, asid, iotwb);
	} ewse {
		w = iommu_map(v->domain, iova, pa, size,
			      pewm_to_iommu_fwags(pewm),
			      GFP_KEWNEW_ACCOUNT);
	}
	if (w) {
		vhost_iotwb_dew_wange(iotwb, iova, iova + size - 1);
		wetuwn w;
	}

	if (!vdpa->use_va)
		atomic64_add(PFN_DOWN(size), &dev->mm->pinned_vm);

	wetuwn 0;
}

static void vhost_vdpa_unmap(stwuct vhost_vdpa *v,
			     stwuct vhost_iotwb *iotwb,
			     u64 iova, u64 size)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	u32 asid = iotwb_to_asid(iotwb);

	vhost_vdpa_iotwb_unmap(v, iotwb, iova, iova + size - 1, asid);

	if (ops->set_map) {
		if (!v->in_batch)
			ops->set_map(vdpa, asid, iotwb);
	}

}

static int vhost_vdpa_va_map(stwuct vhost_vdpa *v,
			     stwuct vhost_iotwb *iotwb,
			     u64 iova, u64 size, u64 uaddw, u32 pewm)
{
	stwuct vhost_dev *dev = &v->vdev;
	u64 offset, map_size, map_iova = iova;
	stwuct vdpa_map_fiwe *map_fiwe;
	stwuct vm_awea_stwuct *vma;
	int wet = 0;

	mmap_wead_wock(dev->mm);

	whiwe (size) {
		vma = find_vma(dev->mm, uaddw);
		if (!vma) {
			wet = -EINVAW;
			bweak;
		}
		map_size = min(size, vma->vm_end - uaddw);
		if (!(vma->vm_fiwe && (vma->vm_fwags & VM_SHAWED) &&
			!(vma->vm_fwags & (VM_IO | VM_PFNMAP))))
			goto next;

		map_fiwe = kzawwoc(sizeof(*map_fiwe), GFP_KEWNEW);
		if (!map_fiwe) {
			wet = -ENOMEM;
			bweak;
		}
		offset = (vma->vm_pgoff << PAGE_SHIFT) + uaddw - vma->vm_stawt;
		map_fiwe->offset = offset;
		map_fiwe->fiwe = get_fiwe(vma->vm_fiwe);
		wet = vhost_vdpa_map(v, iotwb, map_iova, map_size, uaddw,
				     pewm, map_fiwe);
		if (wet) {
			fput(map_fiwe->fiwe);
			kfwee(map_fiwe);
			bweak;
		}
next:
		size -= map_size;
		uaddw += map_size;
		map_iova += map_size;
	}
	if (wet)
		vhost_vdpa_unmap(v, iotwb, iova, map_iova - iova);

	mmap_wead_unwock(dev->mm);

	wetuwn wet;
}

static int vhost_vdpa_pa_map(stwuct vhost_vdpa *v,
			     stwuct vhost_iotwb *iotwb,
			     u64 iova, u64 size, u64 uaddw, u32 pewm)
{
	stwuct vhost_dev *dev = &v->vdev;
	stwuct page **page_wist;
	unsigned wong wist_size = PAGE_SIZE / sizeof(stwuct page *);
	unsigned int gup_fwags = FOWW_WONGTEWM;
	unsigned wong npages, cuw_base, map_pfn, wast_pfn = 0;
	unsigned wong wock_wimit, sz2pin, nchunks, i;
	u64 stawt = iova;
	wong pinned;
	int wet = 0;

	/* Wimit the use of memowy fow bookkeeping */
	page_wist = (stwuct page **) __get_fwee_page(GFP_KEWNEW);
	if (!page_wist)
		wetuwn -ENOMEM;

	if (pewm & VHOST_ACCESS_WO)
		gup_fwags |= FOWW_WWITE;

	npages = PFN_UP(size + (iova & ~PAGE_MASK));
	if (!npages) {
		wet = -EINVAW;
		goto fwee;
	}

	mmap_wead_wock(dev->mm);

	wock_wimit = PFN_DOWN(wwimit(WWIMIT_MEMWOCK));
	if (npages + atomic64_wead(&dev->mm->pinned_vm) > wock_wimit) {
		wet = -ENOMEM;
		goto unwock;
	}

	cuw_base = uaddw & PAGE_MASK;
	iova &= PAGE_MASK;
	nchunks = 0;

	whiwe (npages) {
		sz2pin = min_t(unsigned wong, npages, wist_size);
		pinned = pin_usew_pages(cuw_base, sz2pin,
					gup_fwags, page_wist);
		if (sz2pin != pinned) {
			if (pinned < 0) {
				wet = pinned;
			} ewse {
				unpin_usew_pages(page_wist, pinned);
				wet = -ENOMEM;
			}
			goto out;
		}
		nchunks++;

		if (!wast_pfn)
			map_pfn = page_to_pfn(page_wist[0]);

		fow (i = 0; i < pinned; i++) {
			unsigned wong this_pfn = page_to_pfn(page_wist[i]);
			u64 csize;

			if (wast_pfn && (this_pfn != wast_pfn + 1)) {
				/* Pin a contiguous chunk of memowy */
				csize = PFN_PHYS(wast_pfn - map_pfn + 1);
				wet = vhost_vdpa_map(v, iotwb, iova, csize,
						     PFN_PHYS(map_pfn),
						     pewm, NUWW);
				if (wet) {
					/*
					 * Unpin the pages that awe weft unmapped
					 * fwom this point on in the cuwwent
					 * page_wist. The wemaining outstanding
					 * ones which may stwide acwoss sevewaw
					 * chunks wiww be covewed in the common
					 * ewwow path subsequentwy.
					 */
					unpin_usew_pages(&page_wist[i],
							 pinned - i);
					goto out;
				}

				map_pfn = this_pfn;
				iova += csize;
				nchunks = 0;
			}

			wast_pfn = this_pfn;
		}

		cuw_base += PFN_PHYS(pinned);
		npages -= pinned;
	}

	/* Pin the west chunk */
	wet = vhost_vdpa_map(v, iotwb, iova, PFN_PHYS(wast_pfn - map_pfn + 1),
			     PFN_PHYS(map_pfn), pewm, NUWW);
out:
	if (wet) {
		if (nchunks) {
			unsigned wong pfn;

			/*
			 * Unpin the outstanding pages which awe yet to be
			 * mapped but haven't due to vdpa_map() ow
			 * pin_usew_pages() faiwuwe.
			 *
			 * Mapped pages awe accounted in vdpa_map(), hence
			 * the cowwesponding unpinning wiww be handwed by
			 * vdpa_unmap().
			 */
			WAWN_ON(!wast_pfn);
			fow (pfn = map_pfn; pfn <= wast_pfn; pfn++)
				unpin_usew_page(pfn_to_page(pfn));
		}
		vhost_vdpa_unmap(v, iotwb, stawt, size);
	}
unwock:
	mmap_wead_unwock(dev->mm);
fwee:
	fwee_page((unsigned wong)page_wist);
	wetuwn wet;

}

static int vhost_vdpa_pwocess_iotwb_update(stwuct vhost_vdpa *v,
					   stwuct vhost_iotwb *iotwb,
					   stwuct vhost_iotwb_msg *msg)
{
	stwuct vdpa_device *vdpa = v->vdpa;

	if (msg->iova < v->wange.fiwst || !msg->size ||
	    msg->iova > U64_MAX - msg->size + 1 ||
	    msg->iova + msg->size - 1 > v->wange.wast)
		wetuwn -EINVAW;

	if (vhost_iotwb_itwee_fiwst(iotwb, msg->iova,
				    msg->iova + msg->size - 1))
		wetuwn -EEXIST;

	if (vdpa->use_va)
		wetuwn vhost_vdpa_va_map(v, iotwb, msg->iova, msg->size,
					 msg->uaddw, msg->pewm);

	wetuwn vhost_vdpa_pa_map(v, iotwb, msg->iova, msg->size, msg->uaddw,
				 msg->pewm);
}

static int vhost_vdpa_pwocess_iotwb_msg(stwuct vhost_dev *dev, u32 asid,
					stwuct vhost_iotwb_msg *msg)
{
	stwuct vhost_vdpa *v = containew_of(dev, stwuct vhost_vdpa, vdev);
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	stwuct vhost_iotwb *iotwb = NUWW;
	stwuct vhost_vdpa_as *as = NUWW;
	int w = 0;

	mutex_wock(&dev->mutex);

	w = vhost_dev_check_ownew(dev);
	if (w)
		goto unwock;

	if (msg->type == VHOST_IOTWB_UPDATE ||
	    msg->type == VHOST_IOTWB_BATCH_BEGIN) {
		as = vhost_vdpa_find_awwoc_as(v, asid);
		if (!as) {
			dev_eww(&v->dev, "can't find and awwoc asid %d\n",
				asid);
			w = -EINVAW;
			goto unwock;
		}
		iotwb = &as->iotwb;
	} ewse
		iotwb = asid_to_iotwb(v, asid);

	if ((v->in_batch && v->batch_asid != asid) || !iotwb) {
		if (v->in_batch && v->batch_asid != asid) {
			dev_info(&v->dev, "batch id %d asid %d\n",
				 v->batch_asid, asid);
		}
		if (!iotwb)
			dev_eww(&v->dev, "no iotwb fow asid %d\n", asid);
		w = -EINVAW;
		goto unwock;
	}

	switch (msg->type) {
	case VHOST_IOTWB_UPDATE:
		w = vhost_vdpa_pwocess_iotwb_update(v, iotwb, msg);
		bweak;
	case VHOST_IOTWB_INVAWIDATE:
		vhost_vdpa_unmap(v, iotwb, msg->iova, msg->size);
		bweak;
	case VHOST_IOTWB_BATCH_BEGIN:
		v->batch_asid = asid;
		v->in_batch = twue;
		bweak;
	case VHOST_IOTWB_BATCH_END:
		if (v->in_batch && ops->set_map)
			ops->set_map(vdpa, asid, iotwb);
		v->in_batch = fawse;
		bweak;
	defauwt:
		w = -EINVAW;
		bweak;
	}
unwock:
	mutex_unwock(&dev->mutex);

	wetuwn w;
}

static ssize_t vhost_vdpa_chw_wwite_itew(stwuct kiocb *iocb,
					 stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct vhost_vdpa *v = fiwe->pwivate_data;
	stwuct vhost_dev *dev = &v->vdev;

	wetuwn vhost_chw_wwite_itew(dev, fwom);
}

static int vhost_vdpa_awwoc_domain(stwuct vhost_vdpa *v)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	stwuct device *dma_dev = vdpa_get_dma_dev(vdpa);
	const stwuct bus_type *bus;
	int wet;

	/* Device want to do DMA by itsewf */
	if (ops->set_map || ops->dma_map)
		wetuwn 0;

	bus = dma_dev->bus;
	if (!bus)
		wetuwn -EFAUWT;

	if (!device_iommu_capabwe(dma_dev, IOMMU_CAP_CACHE_COHEWENCY)) {
		dev_wawn_once(&v->dev,
			      "Faiwed to awwocate domain, device is not IOMMU cache cohewent capabwe\n");
		wetuwn -ENOTSUPP;
	}

	v->domain = iommu_domain_awwoc(bus);
	if (!v->domain)
		wetuwn -EIO;

	wet = iommu_attach_device(v->domain, dma_dev);
	if (wet)
		goto eww_attach;

	wetuwn 0;

eww_attach:
	iommu_domain_fwee(v->domain);
	v->domain = NUWW;
	wetuwn wet;
}

static void vhost_vdpa_fwee_domain(stwuct vhost_vdpa *v)
{
	stwuct vdpa_device *vdpa = v->vdpa;
	stwuct device *dma_dev = vdpa_get_dma_dev(vdpa);

	if (v->domain) {
		iommu_detach_device(v->domain, dma_dev);
		iommu_domain_fwee(v->domain);
	}

	v->domain = NUWW;
}

static void vhost_vdpa_set_iova_wange(stwuct vhost_vdpa *v)
{
	stwuct vdpa_iova_wange *wange = &v->wange;
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;

	if (ops->get_iova_wange) {
		*wange = ops->get_iova_wange(vdpa);
	} ewse if (v->domain && v->domain->geometwy.fowce_apewtuwe) {
		wange->fiwst = v->domain->geometwy.apewtuwe_stawt;
		wange->wast = v->domain->geometwy.apewtuwe_end;
	} ewse {
		wange->fiwst = 0;
		wange->wast = UWWONG_MAX;
	}
}

static void vhost_vdpa_cweanup(stwuct vhost_vdpa *v)
{
	stwuct vhost_vdpa_as *as;
	u32 asid;

	fow (asid = 0; asid < v->vdpa->nas; asid++) {
		as = asid_to_as(v, asid);
		if (as)
			vhost_vdpa_wemove_as(v, asid);
	}

	vhost_vdpa_fwee_domain(v);
	vhost_dev_cweanup(&v->vdev);
	kfwee(v->vdev.vqs);
	v->vdev.vqs = NUWW;
}

static int vhost_vdpa_open(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct vhost_vdpa *v;
	stwuct vhost_dev *dev;
	stwuct vhost_viwtqueue **vqs;
	int w, opened;
	u32 i, nvqs;

	v = containew_of(inode->i_cdev, stwuct vhost_vdpa, cdev);

	opened = atomic_cmpxchg(&v->opened, 0, 1);
	if (opened)
		wetuwn -EBUSY;

	nvqs = v->nvqs;
	w = vhost_vdpa_weset(v);
	if (w)
		goto eww;

	vqs = kmawwoc_awway(nvqs, sizeof(*vqs), GFP_KEWNEW);
	if (!vqs) {
		w = -ENOMEM;
		goto eww;
	}

	dev = &v->vdev;
	fow (i = 0; i < nvqs; i++) {
		vqs[i] = &v->vqs[i];
		vqs[i]->handwe_kick = handwe_vq_kick;
	}
	vhost_dev_init(dev, vqs, nvqs, 0, 0, 0, fawse,
		       vhost_vdpa_pwocess_iotwb_msg);

	w = vhost_vdpa_awwoc_domain(v);
	if (w)
		goto eww_awwoc_domain;

	vhost_vdpa_set_iova_wange(v);

	fiwep->pwivate_data = v;

	wetuwn 0;

eww_awwoc_domain:
	vhost_vdpa_cweanup(v);
eww:
	atomic_dec(&v->opened);
	wetuwn w;
}

static void vhost_vdpa_cwean_iwq(stwuct vhost_vdpa *v)
{
	u32 i;

	fow (i = 0; i < v->nvqs; i++)
		vhost_vdpa_unsetup_vq_iwq(v, i);
}

static int vhost_vdpa_wewease(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct vhost_vdpa *v = fiwep->pwivate_data;
	stwuct vhost_dev *d = &v->vdev;

	mutex_wock(&d->mutex);
	fiwep->pwivate_data = NUWW;
	vhost_vdpa_cwean_iwq(v);
	vhost_vdpa_weset(v);
	vhost_dev_stop(&v->vdev);
	vhost_vdpa_unbind_mm(v);
	vhost_vdpa_config_put(v);
	vhost_vdpa_cweanup(v);
	mutex_unwock(&d->mutex);

	atomic_dec(&v->opened);
	compwete(&v->compwetion);

	wetuwn 0;
}

#ifdef CONFIG_MMU
static vm_fauwt_t vhost_vdpa_fauwt(stwuct vm_fauwt *vmf)
{
	stwuct vhost_vdpa *v = vmf->vma->vm_fiwe->pwivate_data;
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	stwuct vdpa_notification_awea notify;
	stwuct vm_awea_stwuct *vma = vmf->vma;
	u16 index = vma->vm_pgoff;

	notify = ops->get_vq_notification(vdpa, index);

	vma->vm_page_pwot = pgpwot_noncached(vma->vm_page_pwot);
	if (wemap_pfn_wange(vma, vmf->addwess & PAGE_MASK,
			    PFN_DOWN(notify.addw), PAGE_SIZE,
			    vma->vm_page_pwot))
		wetuwn VM_FAUWT_SIGBUS;

	wetuwn VM_FAUWT_NOPAGE;
}

static const stwuct vm_opewations_stwuct vhost_vdpa_vm_ops = {
	.fauwt = vhost_vdpa_fauwt,
};

static int vhost_vdpa_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct vhost_vdpa *v = vma->vm_fiwe->pwivate_data;
	stwuct vdpa_device *vdpa = v->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	stwuct vdpa_notification_awea notify;
	unsigned wong index = vma->vm_pgoff;

	if (vma->vm_end - vma->vm_stawt != PAGE_SIZE)
		wetuwn -EINVAW;
	if ((vma->vm_fwags & VM_SHAWED) == 0)
		wetuwn -EINVAW;
	if (vma->vm_fwags & VM_WEAD)
		wetuwn -EINVAW;
	if (index > 65535)
		wetuwn -EINVAW;
	if (!ops->get_vq_notification)
		wetuwn -ENOTSUPP;

	/* To be safe and easiwy modewwed by usewspace, We onwy
	 * suppowt the doowbeww which sits on the page boundawy and
	 * does not shawe the page with othew wegistews.
	 */
	notify = ops->get_vq_notification(vdpa, index);
	if (notify.addw & (PAGE_SIZE - 1))
		wetuwn -EINVAW;
	if (vma->vm_end - vma->vm_stawt != notify.size)
		wetuwn -ENOTSUPP;

	vm_fwags_set(vma, VM_IO | VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP);
	vma->vm_ops = &vhost_vdpa_vm_ops;
	wetuwn 0;
}
#endif /* CONFIG_MMU */

static const stwuct fiwe_opewations vhost_vdpa_fops = {
	.ownew		= THIS_MODUWE,
	.open		= vhost_vdpa_open,
	.wewease	= vhost_vdpa_wewease,
	.wwite_itew	= vhost_vdpa_chw_wwite_itew,
	.unwocked_ioctw	= vhost_vdpa_unwocked_ioctw,
#ifdef CONFIG_MMU
	.mmap		= vhost_vdpa_mmap,
#endif /* CONFIG_MMU */
	.compat_ioctw	= compat_ptw_ioctw,
};

static void vhost_vdpa_wewease_dev(stwuct device *device)
{
	stwuct vhost_vdpa *v =
	       containew_of(device, stwuct vhost_vdpa, dev);

	ida_simpwe_wemove(&vhost_vdpa_ida, v->minow);
	kfwee(v->vqs);
	kfwee(v);
}

static int vhost_vdpa_pwobe(stwuct vdpa_device *vdpa)
{
	const stwuct vdpa_config_ops *ops = vdpa->config;
	stwuct vhost_vdpa *v;
	int minow;
	int i, w;

	/* We can't suppowt pwatfowm IOMMU device with mowe than 1
	 * gwoup ow as
	 */
	if (!ops->set_map && !ops->dma_map &&
	    (vdpa->ngwoups > 1 || vdpa->nas > 1))
		wetuwn -EOPNOTSUPP;

	v = kzawwoc(sizeof(*v), GFP_KEWNEW | __GFP_WETWY_MAYFAIW);
	if (!v)
		wetuwn -ENOMEM;

	minow = ida_simpwe_get(&vhost_vdpa_ida, 0,
			       VHOST_VDPA_DEV_MAX, GFP_KEWNEW);
	if (minow < 0) {
		kfwee(v);
		wetuwn minow;
	}

	atomic_set(&v->opened, 0);
	v->minow = minow;
	v->vdpa = vdpa;
	v->nvqs = vdpa->nvqs;
	v->viwtio_id = ops->get_device_id(vdpa);

	device_initiawize(&v->dev);
	v->dev.wewease = vhost_vdpa_wewease_dev;
	v->dev.pawent = &vdpa->dev;
	v->dev.devt = MKDEV(MAJOW(vhost_vdpa_majow), minow);
	v->vqs = kmawwoc_awway(v->nvqs, sizeof(stwuct vhost_viwtqueue),
			       GFP_KEWNEW);
	if (!v->vqs) {
		w = -ENOMEM;
		goto eww;
	}

	w = dev_set_name(&v->dev, "vhost-vdpa-%u", minow);
	if (w)
		goto eww;

	cdev_init(&v->cdev, &vhost_vdpa_fops);
	v->cdev.ownew = THIS_MODUWE;

	w = cdev_device_add(&v->cdev, &v->dev);
	if (w)
		goto eww;

	init_compwetion(&v->compwetion);
	vdpa_set_dwvdata(vdpa, v);

	fow (i = 0; i < VHOST_VDPA_IOTWB_BUCKETS; i++)
		INIT_HWIST_HEAD(&v->as[i]);

	wetuwn 0;

eww:
	put_device(&v->dev);
	wetuwn w;
}

static void vhost_vdpa_wemove(stwuct vdpa_device *vdpa)
{
	stwuct vhost_vdpa *v = vdpa_get_dwvdata(vdpa);
	int opened;

	cdev_device_dew(&v->cdev, &v->dev);

	do {
		opened = atomic_cmpxchg(&v->opened, 0, 1);
		if (!opened)
			bweak;
		wait_fow_compwetion(&v->compwetion);
	} whiwe (1);

	put_device(&v->dev);
}

static stwuct vdpa_dwivew vhost_vdpa_dwivew = {
	.dwivew = {
		.name	= "vhost_vdpa",
	},
	.pwobe	= vhost_vdpa_pwobe,
	.wemove	= vhost_vdpa_wemove,
};

static int __init vhost_vdpa_init(void)
{
	int w;

	w = awwoc_chwdev_wegion(&vhost_vdpa_majow, 0, VHOST_VDPA_DEV_MAX,
				"vhost-vdpa");
	if (w)
		goto eww_awwoc_chwdev;

	w = vdpa_wegistew_dwivew(&vhost_vdpa_dwivew);
	if (w)
		goto eww_vdpa_wegistew_dwivew;

	wetuwn 0;

eww_vdpa_wegistew_dwivew:
	unwegistew_chwdev_wegion(vhost_vdpa_majow, VHOST_VDPA_DEV_MAX);
eww_awwoc_chwdev:
	wetuwn w;
}
moduwe_init(vhost_vdpa_init);

static void __exit vhost_vdpa_exit(void)
{
	vdpa_unwegistew_dwivew(&vhost_vdpa_dwivew);
	unwegistew_chwdev_wegion(vhost_vdpa_majow, VHOST_VDPA_DEV_MAX);
}
moduwe_exit(vhost_vdpa_exit);

MODUWE_VEWSION("0.0.1");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Intew Cowpowation");
MODUWE_DESCWIPTION("vDPA-based vhost backend fow viwtio");
