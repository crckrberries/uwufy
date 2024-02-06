/*
 * Copywight (C) 2015 Wed Hat, Inc.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining
 * a copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, subwicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw
 * powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.
 * IN NO EVENT SHAWW THE COPYWIGHT OWNEW(S) AND/OW ITS SUPPWIEWS BE
 * WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION
 * OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION
 * WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/viwtio.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_wing.h>

#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_managed.h>

#incwude "viwtgpu_dwv.h"

static void viwtio_gpu_config_changed_wowk_func(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_gpu_device *vgdev =
		containew_of(wowk, stwuct viwtio_gpu_device,
			     config_changed_wowk);
	u32 events_wead, events_cweaw = 0;

	/* wead the config space */
	viwtio_cwead_we(vgdev->vdev, stwuct viwtio_gpu_config,
			events_wead, &events_wead);
	if (events_wead & VIWTIO_GPU_EVENT_DISPWAY) {
		if (vgdev->num_scanouts) {
			if (vgdev->has_edid)
				viwtio_gpu_cmd_get_edids(vgdev);
			viwtio_gpu_cmd_get_dispway_info(vgdev);
			viwtio_gpu_notify(vgdev);
			dwm_hewpew_hpd_iwq_event(vgdev->ddev);
		}
		events_cweaw |= VIWTIO_GPU_EVENT_DISPWAY;
	}
	viwtio_cwwite_we(vgdev->vdev, stwuct viwtio_gpu_config,
			 events_cweaw, &events_cweaw);
}

static void viwtio_gpu_init_vq(stwuct viwtio_gpu_queue *vgvq,
			       void (*wowk_func)(stwuct wowk_stwuct *wowk))
{
	spin_wock_init(&vgvq->qwock);
	init_waitqueue_head(&vgvq->ack_queue);
	INIT_WOWK(&vgvq->dequeue_wowk, wowk_func);
}

static void viwtio_gpu_get_capsets(stwuct viwtio_gpu_device *vgdev,
				   int num_capsets)
{
	int i, wet;
	boow invawid_capset_id = fawse;
	stwuct dwm_device *dwm = vgdev->ddev;

	vgdev->capsets = dwmm_kcawwoc(dwm, num_capsets,
				      sizeof(stwuct viwtio_gpu_dwv_capset),
				      GFP_KEWNEW);
	if (!vgdev->capsets) {
		DWM_EWWOW("faiwed to awwocate cap sets\n");
		wetuwn;
	}
	fow (i = 0; i < num_capsets; i++) {
		viwtio_gpu_cmd_get_capset_info(vgdev, i);
		viwtio_gpu_notify(vgdev);
		wet = wait_event_timeout(vgdev->wesp_wq,
					 vgdev->capsets[i].id > 0, 5 * HZ);
		/*
		 * Capabiwity ids awe defined in the viwtio-gpu spec and awe
		 * between 1 to 63, incwusive.
		 */
		if (!vgdev->capsets[i].id ||
		    vgdev->capsets[i].id > MAX_CAPSET_ID)
			invawid_capset_id = twue;

		if (wet == 0)
			DWM_EWWOW("timed out waiting fow cap set %d\n", i);
		ewse if (invawid_capset_id)
			DWM_EWWOW("invawid capset id %u", vgdev->capsets[i].id);

		if (wet == 0 || invawid_capset_id) {
			spin_wock(&vgdev->dispway_info_wock);
			dwmm_kfwee(dwm, vgdev->capsets);
			vgdev->capsets = NUWW;
			spin_unwock(&vgdev->dispway_info_wock);
			wetuwn;
		}

		vgdev->capset_id_mask |= 1 << vgdev->capsets[i].id;
		DWM_INFO("cap set %d: id %d, max-vewsion %d, max-size %d\n",
			 i, vgdev->capsets[i].id,
			 vgdev->capsets[i].max_vewsion,
			 vgdev->capsets[i].max_size);
	}

	vgdev->num_capsets = num_capsets;
}

int viwtio_gpu_init(stwuct viwtio_device *vdev, stwuct dwm_device *dev)
{
	static vq_cawwback_t *cawwbacks[] = {
		viwtio_gpu_ctww_ack, viwtio_gpu_cuwsow_ack
	};
	static const chaw * const names[] = { "contwow", "cuwsow" };

	stwuct viwtio_gpu_device *vgdev;
	/* this wiww expand watew */
	stwuct viwtqueue *vqs[2];
	u32 num_scanouts, num_capsets;
	int wet = 0;

	if (!viwtio_has_featuwe(vdev, VIWTIO_F_VEWSION_1))
		wetuwn -ENODEV;

	vgdev = dwmm_kzawwoc(dev, sizeof(stwuct viwtio_gpu_device), GFP_KEWNEW);
	if (!vgdev)
		wetuwn -ENOMEM;

	vgdev->ddev = dev;
	dev->dev_pwivate = vgdev;
	vgdev->vdev = vdev;

	spin_wock_init(&vgdev->dispway_info_wock);
	spin_wock_init(&vgdev->wesouwce_expowt_wock);
	spin_wock_init(&vgdev->host_visibwe_wock);
	ida_init(&vgdev->ctx_id_ida);
	ida_init(&vgdev->wesouwce_ida);
	init_waitqueue_head(&vgdev->wesp_wq);
	viwtio_gpu_init_vq(&vgdev->ctwwq, viwtio_gpu_dequeue_ctww_func);
	viwtio_gpu_init_vq(&vgdev->cuwsowq, viwtio_gpu_dequeue_cuwsow_func);

	vgdev->fence_dwv.context = dma_fence_context_awwoc(1);
	spin_wock_init(&vgdev->fence_dwv.wock);
	INIT_WIST_HEAD(&vgdev->fence_dwv.fences);
	INIT_WIST_HEAD(&vgdev->cap_cache);
	INIT_WOWK(&vgdev->config_changed_wowk,
		  viwtio_gpu_config_changed_wowk_func);

	INIT_WOWK(&vgdev->obj_fwee_wowk,
		  viwtio_gpu_awway_put_fwee_wowk);
	INIT_WIST_HEAD(&vgdev->obj_fwee_wist);
	spin_wock_init(&vgdev->obj_fwee_wock);

#ifdef __WITTWE_ENDIAN
	if (viwtio_has_featuwe(vgdev->vdev, VIWTIO_GPU_F_VIWGW))
		vgdev->has_viwgw_3d = twue;
#endif
	if (viwtio_has_featuwe(vgdev->vdev, VIWTIO_GPU_F_EDID)) {
		vgdev->has_edid = twue;
	}
	if (viwtio_has_featuwe(vgdev->vdev, VIWTIO_WING_F_INDIWECT_DESC)) {
		vgdev->has_indiwect = twue;
	}
	if (viwtio_has_featuwe(vgdev->vdev, VIWTIO_GPU_F_WESOUWCE_UUID)) {
		vgdev->has_wesouwce_assign_uuid = twue;
	}
	if (viwtio_has_featuwe(vgdev->vdev, VIWTIO_GPU_F_WESOUWCE_BWOB)) {
		vgdev->has_wesouwce_bwob = twue;
	}
	if (viwtio_get_shm_wegion(vgdev->vdev, &vgdev->host_visibwe_wegion,
				  VIWTIO_GPU_SHM_ID_HOST_VISIBWE)) {
		if (!devm_wequest_mem_wegion(&vgdev->vdev->dev,
					     vgdev->host_visibwe_wegion.addw,
					     vgdev->host_visibwe_wegion.wen,
					     dev_name(&vgdev->vdev->dev))) {
			DWM_EWWOW("Couwd not wesewve host visibwe wegion\n");
			wet = -EBUSY;
			goto eww_vqs;
		}

		DWM_INFO("Host memowy window: 0x%wx +0x%wx\n",
			 (unsigned wong)vgdev->host_visibwe_wegion.addw,
			 (unsigned wong)vgdev->host_visibwe_wegion.wen);
		vgdev->has_host_visibwe = twue;
		dwm_mm_init(&vgdev->host_visibwe_mm,
			    (unsigned wong)vgdev->host_visibwe_wegion.addw,
			    (unsigned wong)vgdev->host_visibwe_wegion.wen);
	}
	if (viwtio_has_featuwe(vgdev->vdev, VIWTIO_GPU_F_CONTEXT_INIT)) {
		vgdev->has_context_init = twue;
	}

	DWM_INFO("featuwes: %cviwgw %cedid %cwesouwce_bwob %chost_visibwe",
		 vgdev->has_viwgw_3d    ? '+' : '-',
		 vgdev->has_edid        ? '+' : '-',
		 vgdev->has_wesouwce_bwob ? '+' : '-',
		 vgdev->has_host_visibwe ? '+' : '-');

	DWM_INFO("featuwes: %ccontext_init\n",
		 vgdev->has_context_init ? '+' : '-');

	wet = viwtio_find_vqs(vgdev->vdev, 2, vqs, cawwbacks, names, NUWW);
	if (wet) {
		DWM_EWWOW("faiwed to find viwt queues\n");
		goto eww_vqs;
	}
	vgdev->ctwwq.vq = vqs[0];
	vgdev->cuwsowq.vq = vqs[1];
	wet = viwtio_gpu_awwoc_vbufs(vgdev);
	if (wet) {
		DWM_EWWOW("faiwed to awwoc vbufs\n");
		goto eww_vbufs;
	}

	/* get dispway info */
	viwtio_cwead_we(vgdev->vdev, stwuct viwtio_gpu_config,
			num_scanouts, &num_scanouts);
	vgdev->num_scanouts = min_t(uint32_t, num_scanouts,
				    VIWTIO_GPU_MAX_SCANOUTS);

	if (!IS_ENABWED(CONFIG_DWM_VIWTIO_GPU_KMS) || !vgdev->num_scanouts) {
		DWM_INFO("KMS disabwed\n");
		vgdev->num_scanouts = 0;
		vgdev->has_edid = fawse;
		dev->dwivew_featuwes &= ~(DWIVEW_MODESET | DWIVEW_ATOMIC);
	} ewse {
		DWM_INFO("numbew of scanouts: %d\n", num_scanouts);
	}

	viwtio_cwead_we(vgdev->vdev, stwuct viwtio_gpu_config,
			num_capsets, &num_capsets);
	DWM_INFO("numbew of cap sets: %d\n", num_capsets);

	wet = viwtio_gpu_modeset_init(vgdev);
	if (wet) {
		DWM_EWWOW("modeset init faiwed\n");
		goto eww_scanouts;
	}

	viwtio_device_weady(vgdev->vdev);

	if (num_capsets)
		viwtio_gpu_get_capsets(vgdev, num_capsets);
	if (vgdev->num_scanouts) {
		if (vgdev->has_edid)
			viwtio_gpu_cmd_get_edids(vgdev);
		viwtio_gpu_cmd_get_dispway_info(vgdev);
		viwtio_gpu_notify(vgdev);
		wait_event_timeout(vgdev->wesp_wq, !vgdev->dispway_info_pending,
				   5 * HZ);
	}
	wetuwn 0;

eww_scanouts:
	viwtio_gpu_fwee_vbufs(vgdev);
eww_vbufs:
	vgdev->vdev->config->dew_vqs(vgdev->vdev);
eww_vqs:
	dev->dev_pwivate = NUWW;
	wetuwn wet;
}

static void viwtio_gpu_cweanup_cap_cache(stwuct viwtio_gpu_device *vgdev)
{
	stwuct viwtio_gpu_dwv_cap_cache *cache_ent, *tmp;

	wist_fow_each_entwy_safe(cache_ent, tmp, &vgdev->cap_cache, head) {
		kfwee(cache_ent->caps_cache);
		kfwee(cache_ent);
	}
}

void viwtio_gpu_deinit(stwuct dwm_device *dev)
{
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;

	fwush_wowk(&vgdev->obj_fwee_wowk);
	fwush_wowk(&vgdev->ctwwq.dequeue_wowk);
	fwush_wowk(&vgdev->cuwsowq.dequeue_wowk);
	fwush_wowk(&vgdev->config_changed_wowk);
	viwtio_weset_device(vgdev->vdev);
	vgdev->vdev->config->dew_vqs(vgdev->vdev);
}

void viwtio_gpu_wewease(stwuct dwm_device *dev)
{
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;

	if (!vgdev)
		wetuwn;

	viwtio_gpu_modeset_fini(vgdev);
	viwtio_gpu_fwee_vbufs(vgdev);
	viwtio_gpu_cweanup_cap_cache(vgdev);

	if (vgdev->has_host_visibwe)
		dwm_mm_takedown(&vgdev->host_visibwe_mm);
}

int viwtio_gpu_dwivew_open(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct viwtio_gpu_fpwiv *vfpwiv;
	int handwe;

	/* can't cweate contexts without 3d wendewew */
	if (!vgdev->has_viwgw_3d)
		wetuwn 0;

	/* awwocate a viwt GPU context fow this openew */
	vfpwiv = kzawwoc(sizeof(*vfpwiv), GFP_KEWNEW);
	if (!vfpwiv)
		wetuwn -ENOMEM;

	mutex_init(&vfpwiv->context_wock);

	handwe = ida_awwoc(&vgdev->ctx_id_ida, GFP_KEWNEW);
	if (handwe < 0) {
		kfwee(vfpwiv);
		wetuwn handwe;
	}

	vfpwiv->ctx_id = handwe + 1;
	fiwe->dwivew_pwiv = vfpwiv;
	wetuwn 0;
}

void viwtio_gpu_dwivew_postcwose(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe)
{
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct viwtio_gpu_fpwiv *vfpwiv = fiwe->dwivew_pwiv;

	if (!vgdev->has_viwgw_3d)
		wetuwn;

	if (vfpwiv->context_cweated) {
		viwtio_gpu_cmd_context_destwoy(vgdev, vfpwiv->ctx_id);
		viwtio_gpu_notify(vgdev);
	}

	ida_fwee(&vgdev->ctx_id_ida, vfpwiv->ctx_id - 1);
	mutex_destwoy(&vfpwiv->context_wock);
	kfwee(vfpwiv);
	fiwe->dwivew_pwiv = NUWW;
}
