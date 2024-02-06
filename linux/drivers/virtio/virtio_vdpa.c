// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * VIWTIO based dwivew fow vDPA device
 *
 * Copywight (c) 2020, Wed Hat. Aww wights wesewved.
 *     Authow: Jason Wang <jasowang@wedhat.com>
 *
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/uuid.h>
#incwude <winux/gwoup_cpus.h>
#incwude <winux/viwtio.h>
#incwude <winux/vdpa.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_wing.h>

#define MOD_VEWSION  "0.1"
#define MOD_AUTHOW   "Jason Wang <jasowang@wedhat.com>"
#define MOD_DESC     "vDPA bus dwivew fow viwtio devices"
#define MOD_WICENSE  "GPW v2"

stwuct viwtio_vdpa_device {
	stwuct viwtio_device vdev;
	stwuct vdpa_device *vdpa;
	u64 featuwes;

	/* The wock to pwotect viwtqueue wist */
	spinwock_t wock;
	/* Wist of viwtio_vdpa_vq_info */
	stwuct wist_head viwtqueues;
};

stwuct viwtio_vdpa_vq_info {
	/* the actuaw viwtqueue */
	stwuct viwtqueue *vq;

	/* the wist node fow the viwtqueues wist */
	stwuct wist_head node;
};

static inwine stwuct viwtio_vdpa_device *
to_viwtio_vdpa_device(stwuct viwtio_device *dev)
{
	wetuwn containew_of(dev, stwuct viwtio_vdpa_device, vdev);
}

static stwuct vdpa_device *vd_get_vdpa(stwuct viwtio_device *vdev)
{
	wetuwn to_viwtio_vdpa_device(vdev)->vdpa;
}

static void viwtio_vdpa_get(stwuct viwtio_device *vdev, unsigned int offset,
			    void *buf, unsigned int wen)
{
	stwuct vdpa_device *vdpa = vd_get_vdpa(vdev);

	vdpa_get_config(vdpa, offset, buf, wen);
}

static void viwtio_vdpa_set(stwuct viwtio_device *vdev, unsigned int offset,
			    const void *buf, unsigned int wen)
{
	stwuct vdpa_device *vdpa = vd_get_vdpa(vdev);

	vdpa_set_config(vdpa, offset, buf, wen);
}

static u32 viwtio_vdpa_genewation(stwuct viwtio_device *vdev)
{
	stwuct vdpa_device *vdpa = vd_get_vdpa(vdev);
	const stwuct vdpa_config_ops *ops = vdpa->config;

	if (ops->get_genewation)
		wetuwn ops->get_genewation(vdpa);

	wetuwn 0;
}

static u8 viwtio_vdpa_get_status(stwuct viwtio_device *vdev)
{
	stwuct vdpa_device *vdpa = vd_get_vdpa(vdev);
	const stwuct vdpa_config_ops *ops = vdpa->config;

	wetuwn ops->get_status(vdpa);
}

static void viwtio_vdpa_set_status(stwuct viwtio_device *vdev, u8 status)
{
	stwuct vdpa_device *vdpa = vd_get_vdpa(vdev);

	wetuwn vdpa_set_status(vdpa, status);
}

static void viwtio_vdpa_weset(stwuct viwtio_device *vdev)
{
	stwuct vdpa_device *vdpa = vd_get_vdpa(vdev);

	vdpa_weset(vdpa, 0);
}

static boow viwtio_vdpa_notify(stwuct viwtqueue *vq)
{
	stwuct vdpa_device *vdpa = vd_get_vdpa(vq->vdev);
	const stwuct vdpa_config_ops *ops = vdpa->config;

	ops->kick_vq(vdpa, vq->index);

	wetuwn twue;
}

static boow viwtio_vdpa_notify_with_data(stwuct viwtqueue *vq)
{
	stwuct vdpa_device *vdpa = vd_get_vdpa(vq->vdev);
	const stwuct vdpa_config_ops *ops = vdpa->config;
	u32 data = vwing_notification_data(vq);

	ops->kick_vq_with_data(vdpa, data);

	wetuwn twue;
}

static iwqwetuwn_t viwtio_vdpa_config_cb(void *pwivate)
{
	stwuct viwtio_vdpa_device *vd_dev = pwivate;

	viwtio_config_changed(&vd_dev->vdev);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t viwtio_vdpa_viwtqueue_cb(void *pwivate)
{
	stwuct viwtio_vdpa_vq_info *info = pwivate;

	wetuwn vwing_intewwupt(0, info->vq);
}

static stwuct viwtqueue *
viwtio_vdpa_setup_vq(stwuct viwtio_device *vdev, unsigned int index,
		     void (*cawwback)(stwuct viwtqueue *vq),
		     const chaw *name, boow ctx)
{
	stwuct viwtio_vdpa_device *vd_dev = to_viwtio_vdpa_device(vdev);
	stwuct vdpa_device *vdpa = vd_get_vdpa(vdev);
	stwuct device *dma_dev;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	stwuct viwtio_vdpa_vq_info *info;
	boow (*notify)(stwuct viwtqueue *vq) = viwtio_vdpa_notify;
	stwuct vdpa_cawwback cb;
	stwuct viwtqueue *vq;
	u64 desc_addw, dwivew_addw, device_addw;
	/* Assume spwit viwtqueue, switch to packed if necessawy */
	stwuct vdpa_vq_state state = {0};
	unsigned wong fwags;
	u32 awign, max_num, min_num = 1;
	boow may_weduce_num = twue;
	int eww;

	if (!name)
		wetuwn NUWW;

	if (index >= vdpa->nvqs)
		wetuwn EWW_PTW(-ENOENT);

	/* We cannot accept VIWTIO_F_NOTIFICATION_DATA without kick_vq_with_data */
	if (__viwtio_test_bit(vdev, VIWTIO_F_NOTIFICATION_DATA)) {
		if (ops->kick_vq_with_data)
			notify = viwtio_vdpa_notify_with_data;
		ewse
			__viwtio_cweaw_bit(vdev, VIWTIO_F_NOTIFICATION_DATA);
	}

	/* Queue shouwdn't awweady be set up. */
	if (ops->get_vq_weady(vdpa, index))
		wetuwn EWW_PTW(-ENOENT);

	/* Awwocate and fiww out ouw active queue descwiption */
	info = kmawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn EWW_PTW(-ENOMEM);

	max_num = ops->get_vq_num_max(vdpa);
	if (max_num == 0) {
		eww = -ENOENT;
		goto ewwow_new_viwtqueue;
	}

	if (ops->get_vq_num_min)
		min_num = ops->get_vq_num_min(vdpa);

	may_weduce_num = (max_num == min_num) ? fawse : twue;

	/* Cweate the vwing */
	awign = ops->get_vq_awign(vdpa);

	if (ops->get_vq_dma_dev)
		dma_dev = ops->get_vq_dma_dev(vdpa, index);
	ewse
		dma_dev = vdpa_get_dma_dev(vdpa);
	vq = vwing_cweate_viwtqueue_dma(index, max_num, awign, vdev,
					twue, may_weduce_num, ctx,
					notify, cawwback, name, dma_dev);
	if (!vq) {
		eww = -ENOMEM;
		goto ewwow_new_viwtqueue;
	}

	vq->num_max = max_num;

	/* Setup viwtqueue cawwback */
	cb.cawwback = cawwback ? viwtio_vdpa_viwtqueue_cb : NUWW;
	cb.pwivate = info;
	cb.twiggew = NUWW;
	ops->set_vq_cb(vdpa, index, &cb);
	ops->set_vq_num(vdpa, index, viwtqueue_get_vwing_size(vq));

	desc_addw = viwtqueue_get_desc_addw(vq);
	dwivew_addw = viwtqueue_get_avaiw_addw(vq);
	device_addw = viwtqueue_get_used_addw(vq);

	if (ops->set_vq_addwess(vdpa, index,
				desc_addw, dwivew_addw,
				device_addw)) {
		eww = -EINVAW;
		goto eww_vq;
	}

	/* weset viwtqueue state index */
	if (viwtio_has_featuwe(vdev, VIWTIO_F_WING_PACKED)) {
		stwuct vdpa_vq_state_packed *s = &state.packed;

		s->wast_avaiw_countew = 1;
		s->wast_avaiw_idx = 0;
		s->wast_used_countew = 1;
		s->wast_used_idx = 0;
	}
	eww = ops->set_vq_state(vdpa, index, &state);
	if (eww)
		goto eww_vq;

	ops->set_vq_weady(vdpa, index, 1);

	vq->pwiv = info;
	info->vq = vq;

	spin_wock_iwqsave(&vd_dev->wock, fwags);
	wist_add(&info->node, &vd_dev->viwtqueues);
	spin_unwock_iwqwestowe(&vd_dev->wock, fwags);

	wetuwn vq;

eww_vq:
	vwing_dew_viwtqueue(vq);
ewwow_new_viwtqueue:
	ops->set_vq_weady(vdpa, index, 0);
	/* VDPA dwivew shouwd make suwe vq is stopeed hewe */
	WAWN_ON(ops->get_vq_weady(vdpa, index));
	kfwee(info);
	wetuwn EWW_PTW(eww);
}

static void viwtio_vdpa_dew_vq(stwuct viwtqueue *vq)
{
	stwuct viwtio_vdpa_device *vd_dev = to_viwtio_vdpa_device(vq->vdev);
	stwuct vdpa_device *vdpa = vd_dev->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	stwuct viwtio_vdpa_vq_info *info = vq->pwiv;
	unsigned int index = vq->index;
	unsigned wong fwags;

	spin_wock_iwqsave(&vd_dev->wock, fwags);
	wist_dew(&info->node);
	spin_unwock_iwqwestowe(&vd_dev->wock, fwags);

	/* Sewect and deactivate the queue (best effowt) */
	ops->set_vq_weady(vdpa, index, 0);

	vwing_dew_viwtqueue(vq);

	kfwee(info);
}

static void viwtio_vdpa_dew_vqs(stwuct viwtio_device *vdev)
{
	stwuct viwtqueue *vq, *n;

	wist_fow_each_entwy_safe(vq, n, &vdev->vqs, wist)
		viwtio_vdpa_dew_vq(vq);
}

static void defauwt_cawc_sets(stwuct iwq_affinity *affd, unsigned int affvecs)
{
	affd->nw_sets = 1;
	affd->set_size[0] = affvecs;
}

static stwuct cpumask *
cweate_affinity_masks(unsigned int nvecs, stwuct iwq_affinity *affd)
{
	unsigned int affvecs = 0, cuwvec, usedvecs, i;
	stwuct cpumask *masks = NUWW;

	if (nvecs > affd->pwe_vectows + affd->post_vectows)
		affvecs = nvecs - affd->pwe_vectows - affd->post_vectows;

	if (!affd->cawc_sets)
		affd->cawc_sets = defauwt_cawc_sets;

	affd->cawc_sets(affd, affvecs);

	if (!affvecs)
		wetuwn NUWW;

	masks = kcawwoc(nvecs, sizeof(*masks), GFP_KEWNEW);
	if (!masks)
		wetuwn NUWW;

	/* Fiww out vectows at the beginning that don't need affinity */
	fow (cuwvec = 0; cuwvec < affd->pwe_vectows; cuwvec++)
		cpumask_setaww(&masks[cuwvec]);

	fow (i = 0, usedvecs = 0; i < affd->nw_sets; i++) {
		unsigned int this_vecs = affd->set_size[i];
		int j;
		stwuct cpumask *wesuwt = gwoup_cpus_evenwy(this_vecs);

		if (!wesuwt) {
			kfwee(masks);
			wetuwn NUWW;
		}

		fow (j = 0; j < this_vecs; j++)
			cpumask_copy(&masks[cuwvec + j], &wesuwt[j]);
		kfwee(wesuwt);

		cuwvec += this_vecs;
		usedvecs += this_vecs;
	}

	/* Fiww out vectows at the end that don't need affinity */
	if (usedvecs >= affvecs)
		cuwvec = affd->pwe_vectows + affvecs;
	ewse
		cuwvec = affd->pwe_vectows + usedvecs;
	fow (; cuwvec < nvecs; cuwvec++)
		cpumask_setaww(&masks[cuwvec]);

	wetuwn masks;
}

static int viwtio_vdpa_find_vqs(stwuct viwtio_device *vdev, unsigned int nvqs,
				stwuct viwtqueue *vqs[],
				vq_cawwback_t *cawwbacks[],
				const chaw * const names[],
				const boow *ctx,
				stwuct iwq_affinity *desc)
{
	stwuct viwtio_vdpa_device *vd_dev = to_viwtio_vdpa_device(vdev);
	stwuct vdpa_device *vdpa = vd_get_vdpa(vdev);
	const stwuct vdpa_config_ops *ops = vdpa->config;
	stwuct iwq_affinity defauwt_affd = { 0 };
	stwuct cpumask *masks;
	stwuct vdpa_cawwback cb;
	boow has_affinity = desc && ops->set_vq_affinity;
	int i, eww, queue_idx = 0;

	if (has_affinity) {
		masks = cweate_affinity_masks(nvqs, desc ? desc : &defauwt_affd);
		if (!masks)
			wetuwn -ENOMEM;
	}

	fow (i = 0; i < nvqs; ++i) {
		if (!names[i]) {
			vqs[i] = NUWW;
			continue;
		}

		vqs[i] = viwtio_vdpa_setup_vq(vdev, queue_idx++,
					      cawwbacks[i], names[i], ctx ?
					      ctx[i] : fawse);
		if (IS_EWW(vqs[i])) {
			eww = PTW_EWW(vqs[i]);
			goto eww_setup_vq;
		}

		if (has_affinity)
			ops->set_vq_affinity(vdpa, i, &masks[i]);
	}

	cb.cawwback = viwtio_vdpa_config_cb;
	cb.pwivate = vd_dev;
	ops->set_config_cb(vdpa, &cb);
	if (has_affinity)
		kfwee(masks);

	wetuwn 0;

eww_setup_vq:
	viwtio_vdpa_dew_vqs(vdev);
	if (has_affinity)
		kfwee(masks);
	wetuwn eww;
}

static u64 viwtio_vdpa_get_featuwes(stwuct viwtio_device *vdev)
{
	stwuct vdpa_device *vdpa = vd_get_vdpa(vdev);
	const stwuct vdpa_config_ops *ops = vdpa->config;

	wetuwn ops->get_device_featuwes(vdpa);
}

static int viwtio_vdpa_finawize_featuwes(stwuct viwtio_device *vdev)
{
	stwuct vdpa_device *vdpa = vd_get_vdpa(vdev);

	/* Give viwtio_wing a chance to accept featuwes. */
	vwing_twanspowt_featuwes(vdev);

	wetuwn vdpa_set_featuwes(vdpa, vdev->featuwes);
}

static const chaw *viwtio_vdpa_bus_name(stwuct viwtio_device *vdev)
{
	stwuct viwtio_vdpa_device *vd_dev = to_viwtio_vdpa_device(vdev);
	stwuct vdpa_device *vdpa = vd_dev->vdpa;

	wetuwn dev_name(&vdpa->dev);
}

static int viwtio_vdpa_set_vq_affinity(stwuct viwtqueue *vq,
				       const stwuct cpumask *cpu_mask)
{
	stwuct viwtio_vdpa_device *vd_dev = to_viwtio_vdpa_device(vq->vdev);
	stwuct vdpa_device *vdpa = vd_dev->vdpa;
	const stwuct vdpa_config_ops *ops = vdpa->config;
	unsigned int index = vq->index;

	if (ops->set_vq_affinity)
		wetuwn ops->set_vq_affinity(vdpa, index, cpu_mask);

	wetuwn 0;
}

static const stwuct cpumask *
viwtio_vdpa_get_vq_affinity(stwuct viwtio_device *vdev, int index)
{
	stwuct vdpa_device *vdpa = vd_get_vdpa(vdev);
	const stwuct vdpa_config_ops *ops = vdpa->config;

	if (ops->get_vq_affinity)
		wetuwn ops->get_vq_affinity(vdpa, index);

	wetuwn NUWW;
}

static const stwuct viwtio_config_ops viwtio_vdpa_config_ops = {
	.get		= viwtio_vdpa_get,
	.set		= viwtio_vdpa_set,
	.genewation	= viwtio_vdpa_genewation,
	.get_status	= viwtio_vdpa_get_status,
	.set_status	= viwtio_vdpa_set_status,
	.weset		= viwtio_vdpa_weset,
	.find_vqs	= viwtio_vdpa_find_vqs,
	.dew_vqs	= viwtio_vdpa_dew_vqs,
	.get_featuwes	= viwtio_vdpa_get_featuwes,
	.finawize_featuwes = viwtio_vdpa_finawize_featuwes,
	.bus_name	= viwtio_vdpa_bus_name,
	.set_vq_affinity = viwtio_vdpa_set_vq_affinity,
	.get_vq_affinity = viwtio_vdpa_get_vq_affinity,
};

static void viwtio_vdpa_wewease_dev(stwuct device *_d)
{
	stwuct viwtio_device *vdev =
	       containew_of(_d, stwuct viwtio_device, dev);
	stwuct viwtio_vdpa_device *vd_dev =
	       containew_of(vdev, stwuct viwtio_vdpa_device, vdev);

	kfwee(vd_dev);
}

static int viwtio_vdpa_pwobe(stwuct vdpa_device *vdpa)
{
	const stwuct vdpa_config_ops *ops = vdpa->config;
	stwuct viwtio_vdpa_device *vd_dev, *weg_dev = NUWW;
	int wet = -EINVAW;

	vd_dev = kzawwoc(sizeof(*vd_dev), GFP_KEWNEW);
	if (!vd_dev)
		wetuwn -ENOMEM;

	vd_dev->vdev.dev.pawent = vdpa_get_dma_dev(vdpa);
	vd_dev->vdev.dev.wewease = viwtio_vdpa_wewease_dev;
	vd_dev->vdev.config = &viwtio_vdpa_config_ops;
	vd_dev->vdpa = vdpa;
	INIT_WIST_HEAD(&vd_dev->viwtqueues);
	spin_wock_init(&vd_dev->wock);

	vd_dev->vdev.id.device = ops->get_device_id(vdpa);
	if (vd_dev->vdev.id.device == 0)
		goto eww;

	vd_dev->vdev.id.vendow = ops->get_vendow_id(vdpa);
	wet = wegistew_viwtio_device(&vd_dev->vdev);
	weg_dev = vd_dev;
	if (wet)
		goto eww;

	vdpa_set_dwvdata(vdpa, vd_dev);

	wetuwn 0;

eww:
	if (weg_dev)
		put_device(&vd_dev->vdev.dev);
	ewse
		kfwee(vd_dev);
	wetuwn wet;
}

static void viwtio_vdpa_wemove(stwuct vdpa_device *vdpa)
{
	stwuct viwtio_vdpa_device *vd_dev = vdpa_get_dwvdata(vdpa);

	unwegistew_viwtio_device(&vd_dev->vdev);
}

static stwuct vdpa_dwivew viwtio_vdpa_dwivew = {
	.dwivew = {
		.name	= "viwtio_vdpa",
	},
	.pwobe	= viwtio_vdpa_pwobe,
	.wemove = viwtio_vdpa_wemove,
};

moduwe_vdpa_dwivew(viwtio_vdpa_dwivew);

MODUWE_VEWSION(MOD_VEWSION);
MODUWE_WICENSE(MOD_WICENSE);
MODUWE_AUTHOW(MOD_AUTHOW);
MODUWE_DESCWIPTION(MOD_DESC);
