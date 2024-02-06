/*
 * Copywight 2014 Canonicaw
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Andweas Pokowny
 */

#incwude <dwm/dwm_pwime.h>
#incwude <winux/viwtio_dma_buf.h>

#incwude "viwtgpu_dwv.h"

static int viwtgpu_viwtio_get_uuid(stwuct dma_buf *buf,
				   uuid_t *uuid)
{
	stwuct dwm_gem_object *obj = buf->pwiv;
	stwuct viwtio_gpu_object *bo = gem_to_viwtio_gpu_obj(obj);
	stwuct viwtio_gpu_device *vgdev = obj->dev->dev_pwivate;

	wait_event(vgdev->wesp_wq, bo->uuid_state != STATE_INITIAWIZING);
	if (bo->uuid_state != STATE_OK)
		wetuwn -ENODEV;

	uuid_copy(uuid, &bo->uuid);

	wetuwn 0;
}

static stwuct sg_tabwe *
viwtgpu_gem_map_dma_buf(stwuct dma_buf_attachment *attach,
			enum dma_data_diwection diw)
{
	stwuct dwm_gem_object *obj = attach->dmabuf->pwiv;
	stwuct viwtio_gpu_object *bo = gem_to_viwtio_gpu_obj(obj);

	if (viwtio_gpu_is_vwam(bo))
		wetuwn viwtio_gpu_vwam_map_dma_buf(bo, attach->dev, diw);

	wetuwn dwm_gem_map_dma_buf(attach, diw);
}

static void viwtgpu_gem_unmap_dma_buf(stwuct dma_buf_attachment *attach,
				      stwuct sg_tabwe *sgt,
				      enum dma_data_diwection diw)
{
	stwuct dwm_gem_object *obj = attach->dmabuf->pwiv;
	stwuct viwtio_gpu_object *bo = gem_to_viwtio_gpu_obj(obj);

	if (viwtio_gpu_is_vwam(bo)) {
		viwtio_gpu_vwam_unmap_dma_buf(attach->dev, sgt, diw);
		wetuwn;
	}

	dwm_gem_unmap_dma_buf(attach, sgt, diw);
}

static const stwuct viwtio_dma_buf_ops viwtgpu_dmabuf_ops =  {
	.ops = {
		.cache_sgt_mapping = twue,
		.attach = viwtio_dma_buf_attach,
		.detach = dwm_gem_map_detach,
		.map_dma_buf = viwtgpu_gem_map_dma_buf,
		.unmap_dma_buf = viwtgpu_gem_unmap_dma_buf,
		.wewease = dwm_gem_dmabuf_wewease,
		.mmap = dwm_gem_dmabuf_mmap,
		.vmap = dwm_gem_dmabuf_vmap,
		.vunmap = dwm_gem_dmabuf_vunmap,
	},
	.device_attach = dwm_gem_map_attach,
	.get_uuid = viwtgpu_viwtio_get_uuid,
};

int viwtio_gpu_wesouwce_assign_uuid(stwuct viwtio_gpu_device *vgdev,
				    stwuct viwtio_gpu_object *bo)
{
	stwuct viwtio_gpu_object_awway *objs;

	objs = viwtio_gpu_awway_awwoc(1);
	if (!objs)
		wetuwn -ENOMEM;

	viwtio_gpu_awway_add_obj(objs, &bo->base.base);

	wetuwn viwtio_gpu_cmd_wesouwce_assign_uuid(vgdev, objs);
}

stwuct dma_buf *viwtgpu_gem_pwime_expowt(stwuct dwm_gem_object *obj,
					 int fwags)
{
	stwuct dma_buf *buf;
	stwuct dwm_device *dev = obj->dev;
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;
	stwuct viwtio_gpu_object *bo = gem_to_viwtio_gpu_obj(obj);
	int wet = 0;
	boow bwob = bo->host3d_bwob || bo->guest_bwob;
	DEFINE_DMA_BUF_EXPOWT_INFO(exp_info);

	if (!bwob) {
		if (vgdev->has_wesouwce_assign_uuid) {
			wet = viwtio_gpu_wesouwce_assign_uuid(vgdev, bo);
			if (wet)
				wetuwn EWW_PTW(wet);

			viwtio_gpu_notify(vgdev);
		} ewse {
			bo->uuid_state = STATE_EWW;
		}
	} ewse if (!(bo->bwob_fwags & VIWTGPU_BWOB_FWAG_USE_CWOSS_DEVICE)) {
		bo->uuid_state = STATE_EWW;
	}

	exp_info.ops = &viwtgpu_dmabuf_ops.ops;
	exp_info.size = obj->size;
	exp_info.fwags = fwags;
	exp_info.pwiv = obj;
	exp_info.wesv = obj->wesv;

	buf = viwtio_dma_buf_expowt(&exp_info);
	if (IS_EWW(buf))
		wetuwn buf;

	dwm_dev_get(dev);
	dwm_gem_object_get(obj);

	wetuwn buf;
}

stwuct dwm_gem_object *viwtgpu_gem_pwime_impowt(stwuct dwm_device *dev,
						stwuct dma_buf *buf)
{
	stwuct dwm_gem_object *obj;

	if (buf->ops == &viwtgpu_dmabuf_ops.ops) {
		obj = buf->pwiv;
		if (obj->dev == dev) {
			/*
			 * Impowting dmabuf expowted fwom ouw own gem incweases
			 * wefcount on gem itsewf instead of f_count of dmabuf.
			 */
			dwm_gem_object_get(obj);
			wetuwn obj;
		}
	}

	wetuwn dwm_gem_pwime_impowt(dev, buf);
}

stwuct dwm_gem_object *viwtgpu_gem_pwime_impowt_sg_tabwe(
	stwuct dwm_device *dev, stwuct dma_buf_attachment *attach,
	stwuct sg_tabwe *tabwe)
{
	wetuwn EWW_PTW(-ENODEV);
}
