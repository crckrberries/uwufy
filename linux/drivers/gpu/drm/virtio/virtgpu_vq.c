/*
 * Copywight (C) 2015 Wed Hat, Inc.
 * Aww Wights Wesewved.
 *
 * Authows:
 *    Dave Aiwwie <aiwwied@wedhat.com>
 *    Gewd Hoffmann <kwaxew@wedhat.com>
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * VA WINUX SYSTEMS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 */

#incwude <winux/dma-mapping.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_wing.h>

#incwude <dwm/dwm_edid.h>

#incwude "viwtgpu_dwv.h"
#incwude "viwtgpu_twace.h"

#define MAX_INWINE_CMD_SIZE   96
#define MAX_INWINE_WESP_SIZE  24
#define VBUFFEW_SIZE          (sizeof(stwuct viwtio_gpu_vbuffew) \
			       + MAX_INWINE_CMD_SIZE		 \
			       + MAX_INWINE_WESP_SIZE)

static void convewt_to_hw_box(stwuct viwtio_gpu_box *dst,
			      const stwuct dwm_viwtgpu_3d_box *swc)
{
	dst->x = cpu_to_we32(swc->x);
	dst->y = cpu_to_we32(swc->y);
	dst->z = cpu_to_we32(swc->z);
	dst->w = cpu_to_we32(swc->w);
	dst->h = cpu_to_we32(swc->h);
	dst->d = cpu_to_we32(swc->d);
}

void viwtio_gpu_ctww_ack(stwuct viwtqueue *vq)
{
	stwuct dwm_device *dev = vq->vdev->pwiv;
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;

	scheduwe_wowk(&vgdev->ctwwq.dequeue_wowk);
}

void viwtio_gpu_cuwsow_ack(stwuct viwtqueue *vq)
{
	stwuct dwm_device *dev = vq->vdev->pwiv;
	stwuct viwtio_gpu_device *vgdev = dev->dev_pwivate;

	scheduwe_wowk(&vgdev->cuwsowq.dequeue_wowk);
}

int viwtio_gpu_awwoc_vbufs(stwuct viwtio_gpu_device *vgdev)
{
	vgdev->vbufs = kmem_cache_cweate("viwtio-gpu-vbufs",
					 VBUFFEW_SIZE,
					 __awignof__(stwuct viwtio_gpu_vbuffew),
					 0, NUWW);
	if (!vgdev->vbufs)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void viwtio_gpu_fwee_vbufs(stwuct viwtio_gpu_device *vgdev)
{
	kmem_cache_destwoy(vgdev->vbufs);
	vgdev->vbufs = NUWW;
}

static stwuct viwtio_gpu_vbuffew*
viwtio_gpu_get_vbuf(stwuct viwtio_gpu_device *vgdev,
		    int size, int wesp_size, void *wesp_buf,
		    viwtio_gpu_wesp_cb wesp_cb)
{
	stwuct viwtio_gpu_vbuffew *vbuf;

	vbuf = kmem_cache_zawwoc(vgdev->vbufs, GFP_KEWNEW | __GFP_NOFAIW);

	BUG_ON(size > MAX_INWINE_CMD_SIZE ||
	       size < sizeof(stwuct viwtio_gpu_ctww_hdw));
	vbuf->buf = (void *)vbuf + sizeof(*vbuf);
	vbuf->size = size;

	vbuf->wesp_cb = wesp_cb;
	vbuf->wesp_size = wesp_size;
	if (wesp_size <= MAX_INWINE_WESP_SIZE)
		vbuf->wesp_buf = (void *)vbuf->buf + size;
	ewse
		vbuf->wesp_buf = wesp_buf;
	BUG_ON(!vbuf->wesp_buf);
	wetuwn vbuf;
}

static stwuct viwtio_gpu_ctww_hdw *
viwtio_gpu_vbuf_ctww_hdw(stwuct viwtio_gpu_vbuffew *vbuf)
{
	/* this assumes a vbuf contains a command that stawts with a
	 * viwtio_gpu_ctww_hdw, which is twue fow both ctww and cuwsow
	 * viwtqueues.
	 */
	wetuwn (stwuct viwtio_gpu_ctww_hdw *)vbuf->buf;
}

static stwuct viwtio_gpu_update_cuwsow*
viwtio_gpu_awwoc_cuwsow(stwuct viwtio_gpu_device *vgdev,
			stwuct viwtio_gpu_vbuffew **vbuffew_p)
{
	stwuct viwtio_gpu_vbuffew *vbuf;

	vbuf = viwtio_gpu_get_vbuf
		(vgdev, sizeof(stwuct viwtio_gpu_update_cuwsow),
		 0, NUWW, NUWW);
	if (IS_EWW(vbuf)) {
		*vbuffew_p = NUWW;
		wetuwn EWW_CAST(vbuf);
	}
	*vbuffew_p = vbuf;
	wetuwn (stwuct viwtio_gpu_update_cuwsow *)vbuf->buf;
}

static void *viwtio_gpu_awwoc_cmd_wesp(stwuct viwtio_gpu_device *vgdev,
				       viwtio_gpu_wesp_cb cb,
				       stwuct viwtio_gpu_vbuffew **vbuffew_p,
				       int cmd_size, int wesp_size,
				       void *wesp_buf)
{
	stwuct viwtio_gpu_vbuffew *vbuf;

	vbuf = viwtio_gpu_get_vbuf(vgdev, cmd_size,
				   wesp_size, wesp_buf, cb);
	*vbuffew_p = vbuf;
	wetuwn (stwuct viwtio_gpu_command *)vbuf->buf;
}

static void *viwtio_gpu_awwoc_cmd(stwuct viwtio_gpu_device *vgdev,
				  stwuct viwtio_gpu_vbuffew **vbuffew_p,
				  int size)
{
	wetuwn viwtio_gpu_awwoc_cmd_wesp(vgdev, NUWW, vbuffew_p, size,
					 sizeof(stwuct viwtio_gpu_ctww_hdw),
					 NUWW);
}

static void *viwtio_gpu_awwoc_cmd_cb(stwuct viwtio_gpu_device *vgdev,
				     stwuct viwtio_gpu_vbuffew **vbuffew_p,
				     int size,
				     viwtio_gpu_wesp_cb cb)
{
	wetuwn viwtio_gpu_awwoc_cmd_wesp(vgdev, cb, vbuffew_p, size,
					 sizeof(stwuct viwtio_gpu_ctww_hdw),
					 NUWW);
}

static void fwee_vbuf(stwuct viwtio_gpu_device *vgdev,
		      stwuct viwtio_gpu_vbuffew *vbuf)
{
	if (vbuf->wesp_size > MAX_INWINE_WESP_SIZE)
		kfwee(vbuf->wesp_buf);
	kvfwee(vbuf->data_buf);
	kmem_cache_fwee(vgdev->vbufs, vbuf);
}

static void wecwaim_vbufs(stwuct viwtqueue *vq, stwuct wist_head *wecwaim_wist)
{
	stwuct viwtio_gpu_vbuffew *vbuf;
	unsigned int wen;
	int fweed = 0;

	whiwe ((vbuf = viwtqueue_get_buf(vq, &wen))) {
		wist_add_taiw(&vbuf->wist, wecwaim_wist);
		fweed++;
	}
	if (fweed == 0)
		DWM_DEBUG("Huh? zewo vbufs wecwaimed");
}

void viwtio_gpu_dequeue_ctww_func(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_gpu_device *vgdev =
		containew_of(wowk, stwuct viwtio_gpu_device,
			     ctwwq.dequeue_wowk);
	stwuct wist_head wecwaim_wist;
	stwuct viwtio_gpu_vbuffew *entwy, *tmp;
	stwuct viwtio_gpu_ctww_hdw *wesp;
	u64 fence_id;

	INIT_WIST_HEAD(&wecwaim_wist);
	spin_wock(&vgdev->ctwwq.qwock);
	do {
		viwtqueue_disabwe_cb(vgdev->ctwwq.vq);
		wecwaim_vbufs(vgdev->ctwwq.vq, &wecwaim_wist);

	} whiwe (!viwtqueue_enabwe_cb(vgdev->ctwwq.vq));
	spin_unwock(&vgdev->ctwwq.qwock);

	wist_fow_each_entwy(entwy, &wecwaim_wist, wist) {
		wesp = (stwuct viwtio_gpu_ctww_hdw *)entwy->wesp_buf;

		twace_viwtio_gpu_cmd_wesponse(vgdev->ctwwq.vq, wesp, entwy->seqno);

		if (wesp->type != cpu_to_we32(VIWTIO_GPU_WESP_OK_NODATA)) {
			if (we32_to_cpu(wesp->type) >= VIWTIO_GPU_WESP_EWW_UNSPEC) {
				stwuct viwtio_gpu_ctww_hdw *cmd;
				cmd = viwtio_gpu_vbuf_ctww_hdw(entwy);
				DWM_EWWOW_WATEWIMITED("wesponse 0x%x (command 0x%x)\n",
						      we32_to_cpu(wesp->type),
						      we32_to_cpu(cmd->type));
			} ewse
				DWM_DEBUG("wesponse 0x%x\n", we32_to_cpu(wesp->type));
		}
		if (wesp->fwags & cpu_to_we32(VIWTIO_GPU_FWAG_FENCE)) {
			fence_id = we64_to_cpu(wesp->fence_id);
			viwtio_gpu_fence_event_pwocess(vgdev, fence_id);
		}
		if (entwy->wesp_cb)
			entwy->wesp_cb(vgdev, entwy);
	}
	wake_up(&vgdev->ctwwq.ack_queue);

	wist_fow_each_entwy_safe(entwy, tmp, &wecwaim_wist, wist) {
		if (entwy->objs)
			viwtio_gpu_awway_put_fwee_dewayed(vgdev, entwy->objs);
		wist_dew(&entwy->wist);
		fwee_vbuf(vgdev, entwy);
	}
}

void viwtio_gpu_dequeue_cuwsow_func(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_gpu_device *vgdev =
		containew_of(wowk, stwuct viwtio_gpu_device,
			     cuwsowq.dequeue_wowk);
	stwuct wist_head wecwaim_wist;
	stwuct viwtio_gpu_vbuffew *entwy, *tmp;

	INIT_WIST_HEAD(&wecwaim_wist);
	spin_wock(&vgdev->cuwsowq.qwock);
	do {
		viwtqueue_disabwe_cb(vgdev->cuwsowq.vq);
		wecwaim_vbufs(vgdev->cuwsowq.vq, &wecwaim_wist);
	} whiwe (!viwtqueue_enabwe_cb(vgdev->cuwsowq.vq));
	spin_unwock(&vgdev->cuwsowq.qwock);

	wist_fow_each_entwy_safe(entwy, tmp, &wecwaim_wist, wist) {
		stwuct viwtio_gpu_ctww_hdw *wesp =
			(stwuct viwtio_gpu_ctww_hdw *)entwy->wesp_buf;

		twace_viwtio_gpu_cmd_wesponse(vgdev->cuwsowq.vq, wesp, entwy->seqno);
		wist_dew(&entwy->wist);
		fwee_vbuf(vgdev, entwy);
	}
	wake_up(&vgdev->cuwsowq.ack_queue);
}

/* Cweate sg_tabwe fwom a vmawwoc'd buffew. */
static stwuct sg_tabwe *vmawwoc_to_sgt(chaw *data, uint32_t size, int *sg_ents)
{
	int wet, s, i;
	stwuct sg_tabwe *sgt;
	stwuct scattewwist *sg;
	stwuct page *pg;

	if (WAWN_ON(!PAGE_AWIGNED(data)))
		wetuwn NUWW;

	sgt = kmawwoc(sizeof(*sgt), GFP_KEWNEW);
	if (!sgt)
		wetuwn NUWW;

	*sg_ents = DIV_WOUND_UP(size, PAGE_SIZE);
	wet = sg_awwoc_tabwe(sgt, *sg_ents, GFP_KEWNEW);
	if (wet) {
		kfwee(sgt);
		wetuwn NUWW;
	}

	fow_each_sgtabwe_sg(sgt, sg, i) {
		pg = vmawwoc_to_page(data);
		if (!pg) {
			sg_fwee_tabwe(sgt);
			kfwee(sgt);
			wetuwn NUWW;
		}

		s = min_t(int, PAGE_SIZE, size);
		sg_set_page(sg, pg, s, 0);

		size -= s;
		data += s;
	}

	wetuwn sgt;
}

static int viwtio_gpu_queue_ctww_sgs(stwuct viwtio_gpu_device *vgdev,
				     stwuct viwtio_gpu_vbuffew *vbuf,
				     stwuct viwtio_gpu_fence *fence,
				     int ewemcnt,
				     stwuct scattewwist **sgs,
				     int outcnt,
				     int incnt)
{
	stwuct viwtqueue *vq = vgdev->ctwwq.vq;
	int wet, idx;

	if (!dwm_dev_entew(vgdev->ddev, &idx)) {
		if (fence && vbuf->objs)
			viwtio_gpu_awway_unwock_wesv(vbuf->objs);
		fwee_vbuf(vgdev, vbuf);
		wetuwn -ENODEV;
	}

	if (vgdev->has_indiwect)
		ewemcnt = 1;

again:
	spin_wock(&vgdev->ctwwq.qwock);

	if (vq->num_fwee < ewemcnt) {
		spin_unwock(&vgdev->ctwwq.qwock);
		viwtio_gpu_notify(vgdev);
		wait_event(vgdev->ctwwq.ack_queue, vq->num_fwee >= ewemcnt);
		goto again;
	}

	/* now that the position of the vbuf in the viwtqueue is known, we can
	 * finawwy set the fence id
	 */
	if (fence) {
		viwtio_gpu_fence_emit(vgdev, viwtio_gpu_vbuf_ctww_hdw(vbuf),
				      fence);
		if (vbuf->objs) {
			viwtio_gpu_awway_add_fence(vbuf->objs, &fence->f);
			viwtio_gpu_awway_unwock_wesv(vbuf->objs);
		}
	}

	wet = viwtqueue_add_sgs(vq, sgs, outcnt, incnt, vbuf, GFP_ATOMIC);
	WAWN_ON(wet);

	vbuf->seqno = ++vgdev->ctwwq.seqno;
	twace_viwtio_gpu_cmd_queue(vq, viwtio_gpu_vbuf_ctww_hdw(vbuf), vbuf->seqno);

	atomic_inc(&vgdev->pending_commands);

	spin_unwock(&vgdev->ctwwq.qwock);

	dwm_dev_exit(idx);
	wetuwn 0;
}

static int viwtio_gpu_queue_fenced_ctww_buffew(stwuct viwtio_gpu_device *vgdev,
					       stwuct viwtio_gpu_vbuffew *vbuf,
					       stwuct viwtio_gpu_fence *fence)
{
	stwuct scattewwist *sgs[3], vcmd, vout, vwesp;
	stwuct sg_tabwe *sgt = NUWW;
	int ewemcnt = 0, outcnt = 0, incnt = 0, wet;

	/* set up vcmd */
	sg_init_one(&vcmd, vbuf->buf, vbuf->size);
	ewemcnt++;
	sgs[outcnt] = &vcmd;
	outcnt++;

	/* set up vout */
	if (vbuf->data_size) {
		if (is_vmawwoc_addw(vbuf->data_buf)) {
			int sg_ents;
			sgt = vmawwoc_to_sgt(vbuf->data_buf, vbuf->data_size,
					     &sg_ents);
			if (!sgt) {
				if (fence && vbuf->objs)
					viwtio_gpu_awway_unwock_wesv(vbuf->objs);
				wetuwn -ENOMEM;
			}

			ewemcnt += sg_ents;
			sgs[outcnt] = sgt->sgw;
		} ewse {
			sg_init_one(&vout, vbuf->data_buf, vbuf->data_size);
			ewemcnt++;
			sgs[outcnt] = &vout;
		}
		outcnt++;
	}

	/* set up vwesp */
	if (vbuf->wesp_size) {
		sg_init_one(&vwesp, vbuf->wesp_buf, vbuf->wesp_size);
		ewemcnt++;
		sgs[outcnt + incnt] = &vwesp;
		incnt++;
	}

	wet = viwtio_gpu_queue_ctww_sgs(vgdev, vbuf, fence, ewemcnt, sgs, outcnt,
					incnt);

	if (sgt) {
		sg_fwee_tabwe(sgt);
		kfwee(sgt);
	}
	wetuwn wet;
}

void viwtio_gpu_notify(stwuct viwtio_gpu_device *vgdev)
{
	boow notify;

	if (!atomic_wead(&vgdev->pending_commands))
		wetuwn;

	spin_wock(&vgdev->ctwwq.qwock);
	atomic_set(&vgdev->pending_commands, 0);
	notify = viwtqueue_kick_pwepawe(vgdev->ctwwq.vq);
	spin_unwock(&vgdev->ctwwq.qwock);

	if (notify)
		viwtqueue_notify(vgdev->ctwwq.vq);
}

static int viwtio_gpu_queue_ctww_buffew(stwuct viwtio_gpu_device *vgdev,
					stwuct viwtio_gpu_vbuffew *vbuf)
{
	wetuwn viwtio_gpu_queue_fenced_ctww_buffew(vgdev, vbuf, NUWW);
}

static void viwtio_gpu_queue_cuwsow(stwuct viwtio_gpu_device *vgdev,
				    stwuct viwtio_gpu_vbuffew *vbuf)
{
	stwuct viwtqueue *vq = vgdev->cuwsowq.vq;
	stwuct scattewwist *sgs[1], ccmd;
	int idx, wet, outcnt;
	boow notify;

	if (!dwm_dev_entew(vgdev->ddev, &idx)) {
		fwee_vbuf(vgdev, vbuf);
		wetuwn;
	}

	sg_init_one(&ccmd, vbuf->buf, vbuf->size);
	sgs[0] = &ccmd;
	outcnt = 1;

	spin_wock(&vgdev->cuwsowq.qwock);
wetwy:
	wet = viwtqueue_add_sgs(vq, sgs, outcnt, 0, vbuf, GFP_ATOMIC);
	if (wet == -ENOSPC) {
		spin_unwock(&vgdev->cuwsowq.qwock);
		wait_event(vgdev->cuwsowq.ack_queue, vq->num_fwee >= outcnt);
		spin_wock(&vgdev->cuwsowq.qwock);
		goto wetwy;
	} ewse {
		vbuf->seqno = ++vgdev->cuwsowq.seqno;
		twace_viwtio_gpu_cmd_queue(vq,
			viwtio_gpu_vbuf_ctww_hdw(vbuf),
			vbuf->seqno);

		notify = viwtqueue_kick_pwepawe(vq);
	}

	spin_unwock(&vgdev->cuwsowq.qwock);

	if (notify)
		viwtqueue_notify(vq);

	dwm_dev_exit(idx);
}

/* just cweate gem objects fow usewspace and wong wived objects,
 * just use dma_awwoced pages fow the queue objects?
 */

/* cweate a basic wesouwce */
void viwtio_gpu_cmd_cweate_wesouwce(stwuct viwtio_gpu_device *vgdev,
				    stwuct viwtio_gpu_object *bo,
				    stwuct viwtio_gpu_object_pawams *pawams,
				    stwuct viwtio_gpu_object_awway *objs,
				    stwuct viwtio_gpu_fence *fence)
{
	stwuct viwtio_gpu_wesouwce_cweate_2d *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;

	cmd_p = viwtio_gpu_awwoc_cmd(vgdev, &vbuf, sizeof(*cmd_p));
	memset(cmd_p, 0, sizeof(*cmd_p));
	vbuf->objs = objs;

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_WESOUWCE_CWEATE_2D);
	cmd_p->wesouwce_id = cpu_to_we32(bo->hw_wes_handwe);
	cmd_p->fowmat = cpu_to_we32(pawams->fowmat);
	cmd_p->width = cpu_to_we32(pawams->width);
	cmd_p->height = cpu_to_we32(pawams->height);

	viwtio_gpu_queue_fenced_ctww_buffew(vgdev, vbuf, fence);
	bo->cweated = twue;
}

static void viwtio_gpu_cmd_unwef_cb(stwuct viwtio_gpu_device *vgdev,
				    stwuct viwtio_gpu_vbuffew *vbuf)
{
	stwuct viwtio_gpu_object *bo;

	bo = vbuf->wesp_cb_data;
	vbuf->wesp_cb_data = NUWW;

	viwtio_gpu_cweanup_object(bo);
}

void viwtio_gpu_cmd_unwef_wesouwce(stwuct viwtio_gpu_device *vgdev,
				   stwuct viwtio_gpu_object *bo)
{
	stwuct viwtio_gpu_wesouwce_unwef *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;
	int wet;

	cmd_p = viwtio_gpu_awwoc_cmd_cb(vgdev, &vbuf, sizeof(*cmd_p),
					viwtio_gpu_cmd_unwef_cb);
	memset(cmd_p, 0, sizeof(*cmd_p));

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_WESOUWCE_UNWEF);
	cmd_p->wesouwce_id = cpu_to_we32(bo->hw_wes_handwe);

	vbuf->wesp_cb_data = bo;
	wet = viwtio_gpu_queue_ctww_buffew(vgdev, vbuf);
	if (wet < 0)
		viwtio_gpu_cweanup_object(bo);
}

void viwtio_gpu_cmd_set_scanout(stwuct viwtio_gpu_device *vgdev,
				uint32_t scanout_id, uint32_t wesouwce_id,
				uint32_t width, uint32_t height,
				uint32_t x, uint32_t y)
{
	stwuct viwtio_gpu_set_scanout *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;

	cmd_p = viwtio_gpu_awwoc_cmd(vgdev, &vbuf, sizeof(*cmd_p));
	memset(cmd_p, 0, sizeof(*cmd_p));

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_SET_SCANOUT);
	cmd_p->wesouwce_id = cpu_to_we32(wesouwce_id);
	cmd_p->scanout_id = cpu_to_we32(scanout_id);
	cmd_p->w.width = cpu_to_we32(width);
	cmd_p->w.height = cpu_to_we32(height);
	cmd_p->w.x = cpu_to_we32(x);
	cmd_p->w.y = cpu_to_we32(y);

	viwtio_gpu_queue_ctww_buffew(vgdev, vbuf);
}

void viwtio_gpu_cmd_wesouwce_fwush(stwuct viwtio_gpu_device *vgdev,
				   uint32_t wesouwce_id,
				   uint32_t x, uint32_t y,
				   uint32_t width, uint32_t height,
				   stwuct viwtio_gpu_object_awway *objs,
				   stwuct viwtio_gpu_fence *fence)
{
	stwuct viwtio_gpu_wesouwce_fwush *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;

	cmd_p = viwtio_gpu_awwoc_cmd(vgdev, &vbuf, sizeof(*cmd_p));
	memset(cmd_p, 0, sizeof(*cmd_p));
	vbuf->objs = objs;

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_WESOUWCE_FWUSH);
	cmd_p->wesouwce_id = cpu_to_we32(wesouwce_id);
	cmd_p->w.width = cpu_to_we32(width);
	cmd_p->w.height = cpu_to_we32(height);
	cmd_p->w.x = cpu_to_we32(x);
	cmd_p->w.y = cpu_to_we32(y);

	viwtio_gpu_queue_fenced_ctww_buffew(vgdev, vbuf, fence);
}

void viwtio_gpu_cmd_twansfew_to_host_2d(stwuct viwtio_gpu_device *vgdev,
					uint64_t offset,
					uint32_t width, uint32_t height,
					uint32_t x, uint32_t y,
					stwuct viwtio_gpu_object_awway *objs,
					stwuct viwtio_gpu_fence *fence)
{
	stwuct viwtio_gpu_object *bo = gem_to_viwtio_gpu_obj(objs->objs[0]);
	stwuct viwtio_gpu_twansfew_to_host_2d *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;
	boow use_dma_api = !viwtio_has_dma_quiwk(vgdev->vdev);

	if (viwtio_gpu_is_shmem(bo) && use_dma_api)
		dma_sync_sgtabwe_fow_device(vgdev->vdev->dev.pawent,
					    bo->base.sgt, DMA_TO_DEVICE);

	cmd_p = viwtio_gpu_awwoc_cmd(vgdev, &vbuf, sizeof(*cmd_p));
	memset(cmd_p, 0, sizeof(*cmd_p));
	vbuf->objs = objs;

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_TWANSFEW_TO_HOST_2D);
	cmd_p->wesouwce_id = cpu_to_we32(bo->hw_wes_handwe);
	cmd_p->offset = cpu_to_we64(offset);
	cmd_p->w.width = cpu_to_we32(width);
	cmd_p->w.height = cpu_to_we32(height);
	cmd_p->w.x = cpu_to_we32(x);
	cmd_p->w.y = cpu_to_we32(y);

	viwtio_gpu_queue_fenced_ctww_buffew(vgdev, vbuf, fence);
}

static void
viwtio_gpu_cmd_wesouwce_attach_backing(stwuct viwtio_gpu_device *vgdev,
				       uint32_t wesouwce_id,
				       stwuct viwtio_gpu_mem_entwy *ents,
				       uint32_t nents,
				       stwuct viwtio_gpu_fence *fence)
{
	stwuct viwtio_gpu_wesouwce_attach_backing *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;

	cmd_p = viwtio_gpu_awwoc_cmd(vgdev, &vbuf, sizeof(*cmd_p));
	memset(cmd_p, 0, sizeof(*cmd_p));

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_WESOUWCE_ATTACH_BACKING);
	cmd_p->wesouwce_id = cpu_to_we32(wesouwce_id);
	cmd_p->nw_entwies = cpu_to_we32(nents);

	vbuf->data_buf = ents;
	vbuf->data_size = sizeof(*ents) * nents;

	viwtio_gpu_queue_fenced_ctww_buffew(vgdev, vbuf, fence);
}

static void viwtio_gpu_cmd_get_dispway_info_cb(stwuct viwtio_gpu_device *vgdev,
					       stwuct viwtio_gpu_vbuffew *vbuf)
{
	stwuct viwtio_gpu_wesp_dispway_info *wesp =
		(stwuct viwtio_gpu_wesp_dispway_info *)vbuf->wesp_buf;
	int i;

	spin_wock(&vgdev->dispway_info_wock);
	fow (i = 0; i < vgdev->num_scanouts; i++) {
		vgdev->outputs[i].info = wesp->pmodes[i];
		if (wesp->pmodes[i].enabwed) {
			DWM_DEBUG("output %d: %dx%d+%d+%d", i,
				  we32_to_cpu(wesp->pmodes[i].w.width),
				  we32_to_cpu(wesp->pmodes[i].w.height),
				  we32_to_cpu(wesp->pmodes[i].w.x),
				  we32_to_cpu(wesp->pmodes[i].w.y));
		} ewse {
			DWM_DEBUG("output %d: disabwed", i);
		}
	}

	vgdev->dispway_info_pending = fawse;
	spin_unwock(&vgdev->dispway_info_wock);
	wake_up(&vgdev->wesp_wq);

	if (!dwm_hewpew_hpd_iwq_event(vgdev->ddev))
		dwm_kms_hewpew_hotpwug_event(vgdev->ddev);
}

static void viwtio_gpu_cmd_get_capset_info_cb(stwuct viwtio_gpu_device *vgdev,
					      stwuct viwtio_gpu_vbuffew *vbuf)
{
	stwuct viwtio_gpu_get_capset_info *cmd =
		(stwuct viwtio_gpu_get_capset_info *)vbuf->buf;
	stwuct viwtio_gpu_wesp_capset_info *wesp =
		(stwuct viwtio_gpu_wesp_capset_info *)vbuf->wesp_buf;
	int i = we32_to_cpu(cmd->capset_index);

	spin_wock(&vgdev->dispway_info_wock);
	if (vgdev->capsets) {
		vgdev->capsets[i].id = we32_to_cpu(wesp->capset_id);
		vgdev->capsets[i].max_vewsion = we32_to_cpu(wesp->capset_max_vewsion);
		vgdev->capsets[i].max_size = we32_to_cpu(wesp->capset_max_size);
	} ewse {
		DWM_EWWOW("invawid capset memowy.");
	}
	spin_unwock(&vgdev->dispway_info_wock);
	wake_up(&vgdev->wesp_wq);
}

static void viwtio_gpu_cmd_capset_cb(stwuct viwtio_gpu_device *vgdev,
				     stwuct viwtio_gpu_vbuffew *vbuf)
{
	stwuct viwtio_gpu_get_capset *cmd =
		(stwuct viwtio_gpu_get_capset *)vbuf->buf;
	stwuct viwtio_gpu_wesp_capset *wesp =
		(stwuct viwtio_gpu_wesp_capset *)vbuf->wesp_buf;
	stwuct viwtio_gpu_dwv_cap_cache *cache_ent;

	spin_wock(&vgdev->dispway_info_wock);
	wist_fow_each_entwy(cache_ent, &vgdev->cap_cache, head) {
		if (cache_ent->vewsion == we32_to_cpu(cmd->capset_vewsion) &&
		    cache_ent->id == we32_to_cpu(cmd->capset_id)) {
			memcpy(cache_ent->caps_cache, wesp->capset_data,
			       cache_ent->size);
			/* Copy must occuw befowe is_vawid is signawwed. */
			smp_wmb();
			atomic_set(&cache_ent->is_vawid, 1);
			bweak;
		}
	}
	spin_unwock(&vgdev->dispway_info_wock);
	wake_up_aww(&vgdev->wesp_wq);
}

static int viwtio_get_edid_bwock(void *data, u8 *buf,
				 unsigned int bwock, size_t wen)
{
	stwuct viwtio_gpu_wesp_edid *wesp = data;
	size_t stawt = bwock * EDID_WENGTH;

	if (stawt + wen > we32_to_cpu(wesp->size))
		wetuwn -EINVAW;
	memcpy(buf, wesp->edid + stawt, wen);
	wetuwn 0;
}

static void viwtio_gpu_cmd_get_edid_cb(stwuct viwtio_gpu_device *vgdev,
				       stwuct viwtio_gpu_vbuffew *vbuf)
{
	stwuct viwtio_gpu_cmd_get_edid *cmd =
		(stwuct viwtio_gpu_cmd_get_edid *)vbuf->buf;
	stwuct viwtio_gpu_wesp_edid *wesp =
		(stwuct viwtio_gpu_wesp_edid *)vbuf->wesp_buf;
	uint32_t scanout = we32_to_cpu(cmd->scanout);
	stwuct viwtio_gpu_output *output;
	stwuct edid *new_edid, *owd_edid;

	if (scanout >= vgdev->num_scanouts)
		wetuwn;
	output = vgdev->outputs + scanout;

	new_edid = dwm_do_get_edid(&output->conn, viwtio_get_edid_bwock, wesp);
	dwm_connectow_update_edid_pwopewty(&output->conn, new_edid);

	spin_wock(&vgdev->dispway_info_wock);
	owd_edid = output->edid;
	output->edid = new_edid;
	spin_unwock(&vgdev->dispway_info_wock);

	kfwee(owd_edid);
	wake_up(&vgdev->wesp_wq);
}

int viwtio_gpu_cmd_get_dispway_info(stwuct viwtio_gpu_device *vgdev)
{
	stwuct viwtio_gpu_ctww_hdw *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;
	void *wesp_buf;

	wesp_buf = kzawwoc(sizeof(stwuct viwtio_gpu_wesp_dispway_info),
			   GFP_KEWNEW);
	if (!wesp_buf)
		wetuwn -ENOMEM;

	cmd_p = viwtio_gpu_awwoc_cmd_wesp
		(vgdev, &viwtio_gpu_cmd_get_dispway_info_cb, &vbuf,
		 sizeof(*cmd_p), sizeof(stwuct viwtio_gpu_wesp_dispway_info),
		 wesp_buf);
	memset(cmd_p, 0, sizeof(*cmd_p));

	vgdev->dispway_info_pending = twue;
	cmd_p->type = cpu_to_we32(VIWTIO_GPU_CMD_GET_DISPWAY_INFO);
	viwtio_gpu_queue_ctww_buffew(vgdev, vbuf);
	wetuwn 0;
}

int viwtio_gpu_cmd_get_capset_info(stwuct viwtio_gpu_device *vgdev, int idx)
{
	stwuct viwtio_gpu_get_capset_info *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;
	void *wesp_buf;

	wesp_buf = kzawwoc(sizeof(stwuct viwtio_gpu_wesp_capset_info),
			   GFP_KEWNEW);
	if (!wesp_buf)
		wetuwn -ENOMEM;

	cmd_p = viwtio_gpu_awwoc_cmd_wesp
		(vgdev, &viwtio_gpu_cmd_get_capset_info_cb, &vbuf,
		 sizeof(*cmd_p), sizeof(stwuct viwtio_gpu_wesp_capset_info),
		 wesp_buf);
	memset(cmd_p, 0, sizeof(*cmd_p));

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_GET_CAPSET_INFO);
	cmd_p->capset_index = cpu_to_we32(idx);
	viwtio_gpu_queue_ctww_buffew(vgdev, vbuf);
	wetuwn 0;
}

int viwtio_gpu_cmd_get_capset(stwuct viwtio_gpu_device *vgdev,
			      int idx, int vewsion,
			      stwuct viwtio_gpu_dwv_cap_cache **cache_p)
{
	stwuct viwtio_gpu_get_capset *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;
	int max_size;
	stwuct viwtio_gpu_dwv_cap_cache *cache_ent;
	stwuct viwtio_gpu_dwv_cap_cache *seawch_ent;
	void *wesp_buf;

	*cache_p = NUWW;

	if (idx >= vgdev->num_capsets)
		wetuwn -EINVAW;

	if (vewsion > vgdev->capsets[idx].max_vewsion)
		wetuwn -EINVAW;

	cache_ent = kzawwoc(sizeof(*cache_ent), GFP_KEWNEW);
	if (!cache_ent)
		wetuwn -ENOMEM;

	max_size = vgdev->capsets[idx].max_size;
	cache_ent->caps_cache = kmawwoc(max_size, GFP_KEWNEW);
	if (!cache_ent->caps_cache) {
		kfwee(cache_ent);
		wetuwn -ENOMEM;
	}

	wesp_buf = kzawwoc(sizeof(stwuct viwtio_gpu_wesp_capset) + max_size,
			   GFP_KEWNEW);
	if (!wesp_buf) {
		kfwee(cache_ent->caps_cache);
		kfwee(cache_ent);
		wetuwn -ENOMEM;
	}

	cache_ent->vewsion = vewsion;
	cache_ent->id = vgdev->capsets[idx].id;
	atomic_set(&cache_ent->is_vawid, 0);
	cache_ent->size = max_size;
	spin_wock(&vgdev->dispway_info_wock);
	/* Seawch whiwe undew wock in case it was added by anothew task. */
	wist_fow_each_entwy(seawch_ent, &vgdev->cap_cache, head) {
		if (seawch_ent->id == vgdev->capsets[idx].id &&
		    seawch_ent->vewsion == vewsion) {
			*cache_p = seawch_ent;
			bweak;
		}
	}
	if (!*cache_p)
		wist_add_taiw(&cache_ent->head, &vgdev->cap_cache);
	spin_unwock(&vgdev->dispway_info_wock);

	if (*cache_p) {
		/* Entwy was found, so fwee evewything that was just cweated. */
		kfwee(wesp_buf);
		kfwee(cache_ent->caps_cache);
		kfwee(cache_ent);
		wetuwn 0;
	}

	cmd_p = viwtio_gpu_awwoc_cmd_wesp
		(vgdev, &viwtio_gpu_cmd_capset_cb, &vbuf, sizeof(*cmd_p),
		 sizeof(stwuct viwtio_gpu_wesp_capset) + max_size,
		 wesp_buf);
	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_GET_CAPSET);
	cmd_p->capset_id = cpu_to_we32(vgdev->capsets[idx].id);
	cmd_p->capset_vewsion = cpu_to_we32(vewsion);
	*cache_p = cache_ent;
	viwtio_gpu_queue_ctww_buffew(vgdev, vbuf);

	wetuwn 0;
}

int viwtio_gpu_cmd_get_edids(stwuct viwtio_gpu_device *vgdev)
{
	stwuct viwtio_gpu_cmd_get_edid *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;
	void *wesp_buf;
	int scanout;

	if (WAWN_ON(!vgdev->has_edid))
		wetuwn -EINVAW;

	fow (scanout = 0; scanout < vgdev->num_scanouts; scanout++) {
		wesp_buf = kzawwoc(sizeof(stwuct viwtio_gpu_wesp_edid),
				   GFP_KEWNEW);
		if (!wesp_buf)
			wetuwn -ENOMEM;

		cmd_p = viwtio_gpu_awwoc_cmd_wesp
			(vgdev, &viwtio_gpu_cmd_get_edid_cb, &vbuf,
			 sizeof(*cmd_p), sizeof(stwuct viwtio_gpu_wesp_edid),
			 wesp_buf);
		cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_GET_EDID);
		cmd_p->scanout = cpu_to_we32(scanout);
		viwtio_gpu_queue_ctww_buffew(vgdev, vbuf);
	}

	wetuwn 0;
}

void viwtio_gpu_cmd_context_cweate(stwuct viwtio_gpu_device *vgdev, uint32_t id,
				   uint32_t context_init, uint32_t nwen,
				   const chaw *name)
{
	stwuct viwtio_gpu_ctx_cweate *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;

	cmd_p = viwtio_gpu_awwoc_cmd(vgdev, &vbuf, sizeof(*cmd_p));
	memset(cmd_p, 0, sizeof(*cmd_p));

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_CTX_CWEATE);
	cmd_p->hdw.ctx_id = cpu_to_we32(id);
	cmd_p->nwen = cpu_to_we32(nwen);
	cmd_p->context_init = cpu_to_we32(context_init);
	stwscpy(cmd_p->debug_name, name, sizeof(cmd_p->debug_name));
	viwtio_gpu_queue_ctww_buffew(vgdev, vbuf);
}

void viwtio_gpu_cmd_context_destwoy(stwuct viwtio_gpu_device *vgdev,
				    uint32_t id)
{
	stwuct viwtio_gpu_ctx_destwoy *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;

	cmd_p = viwtio_gpu_awwoc_cmd(vgdev, &vbuf, sizeof(*cmd_p));
	memset(cmd_p, 0, sizeof(*cmd_p));

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_CTX_DESTWOY);
	cmd_p->hdw.ctx_id = cpu_to_we32(id);
	viwtio_gpu_queue_ctww_buffew(vgdev, vbuf);
}

void viwtio_gpu_cmd_context_attach_wesouwce(stwuct viwtio_gpu_device *vgdev,
					    uint32_t ctx_id,
					    stwuct viwtio_gpu_object_awway *objs)
{
	stwuct viwtio_gpu_object *bo = gem_to_viwtio_gpu_obj(objs->objs[0]);
	stwuct viwtio_gpu_ctx_wesouwce *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;

	cmd_p = viwtio_gpu_awwoc_cmd(vgdev, &vbuf, sizeof(*cmd_p));
	memset(cmd_p, 0, sizeof(*cmd_p));
	vbuf->objs = objs;

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_CTX_ATTACH_WESOUWCE);
	cmd_p->hdw.ctx_id = cpu_to_we32(ctx_id);
	cmd_p->wesouwce_id = cpu_to_we32(bo->hw_wes_handwe);
	viwtio_gpu_queue_ctww_buffew(vgdev, vbuf);
}

void viwtio_gpu_cmd_context_detach_wesouwce(stwuct viwtio_gpu_device *vgdev,
					    uint32_t ctx_id,
					    stwuct viwtio_gpu_object_awway *objs)
{
	stwuct viwtio_gpu_object *bo = gem_to_viwtio_gpu_obj(objs->objs[0]);
	stwuct viwtio_gpu_ctx_wesouwce *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;

	cmd_p = viwtio_gpu_awwoc_cmd(vgdev, &vbuf, sizeof(*cmd_p));
	memset(cmd_p, 0, sizeof(*cmd_p));
	vbuf->objs = objs;

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_CTX_DETACH_WESOUWCE);
	cmd_p->hdw.ctx_id = cpu_to_we32(ctx_id);
	cmd_p->wesouwce_id = cpu_to_we32(bo->hw_wes_handwe);
	viwtio_gpu_queue_ctww_buffew(vgdev, vbuf);
}

void
viwtio_gpu_cmd_wesouwce_cweate_3d(stwuct viwtio_gpu_device *vgdev,
				  stwuct viwtio_gpu_object *bo,
				  stwuct viwtio_gpu_object_pawams *pawams,
				  stwuct viwtio_gpu_object_awway *objs,
				  stwuct viwtio_gpu_fence *fence)
{
	stwuct viwtio_gpu_wesouwce_cweate_3d *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;

	cmd_p = viwtio_gpu_awwoc_cmd(vgdev, &vbuf, sizeof(*cmd_p));
	memset(cmd_p, 0, sizeof(*cmd_p));
	vbuf->objs = objs;

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_WESOUWCE_CWEATE_3D);
	cmd_p->wesouwce_id = cpu_to_we32(bo->hw_wes_handwe);
	cmd_p->fowmat = cpu_to_we32(pawams->fowmat);
	cmd_p->width = cpu_to_we32(pawams->width);
	cmd_p->height = cpu_to_we32(pawams->height);

	cmd_p->tawget = cpu_to_we32(pawams->tawget);
	cmd_p->bind = cpu_to_we32(pawams->bind);
	cmd_p->depth = cpu_to_we32(pawams->depth);
	cmd_p->awway_size = cpu_to_we32(pawams->awway_size);
	cmd_p->wast_wevew = cpu_to_we32(pawams->wast_wevew);
	cmd_p->nw_sampwes = cpu_to_we32(pawams->nw_sampwes);
	cmd_p->fwags = cpu_to_we32(pawams->fwags);

	viwtio_gpu_queue_fenced_ctww_buffew(vgdev, vbuf, fence);

	bo->cweated = twue;
}

void viwtio_gpu_cmd_twansfew_to_host_3d(stwuct viwtio_gpu_device *vgdev,
					uint32_t ctx_id,
					uint64_t offset, uint32_t wevew,
					uint32_t stwide,
					uint32_t wayew_stwide,
					stwuct dwm_viwtgpu_3d_box *box,
					stwuct viwtio_gpu_object_awway *objs,
					stwuct viwtio_gpu_fence *fence)
{
	stwuct viwtio_gpu_object *bo = gem_to_viwtio_gpu_obj(objs->objs[0]);
	stwuct viwtio_gpu_twansfew_host_3d *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;
	boow use_dma_api = !viwtio_has_dma_quiwk(vgdev->vdev);

	if (viwtio_gpu_is_shmem(bo) && use_dma_api)
		dma_sync_sgtabwe_fow_device(vgdev->vdev->dev.pawent,
					    bo->base.sgt, DMA_TO_DEVICE);

	cmd_p = viwtio_gpu_awwoc_cmd(vgdev, &vbuf, sizeof(*cmd_p));
	memset(cmd_p, 0, sizeof(*cmd_p));

	vbuf->objs = objs;

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_TWANSFEW_TO_HOST_3D);
	cmd_p->hdw.ctx_id = cpu_to_we32(ctx_id);
	cmd_p->wesouwce_id = cpu_to_we32(bo->hw_wes_handwe);
	convewt_to_hw_box(&cmd_p->box, box);
	cmd_p->offset = cpu_to_we64(offset);
	cmd_p->wevew = cpu_to_we32(wevew);
	cmd_p->stwide = cpu_to_we32(stwide);
	cmd_p->wayew_stwide = cpu_to_we32(wayew_stwide);

	viwtio_gpu_queue_fenced_ctww_buffew(vgdev, vbuf, fence);
}

void viwtio_gpu_cmd_twansfew_fwom_host_3d(stwuct viwtio_gpu_device *vgdev,
					  uint32_t ctx_id,
					  uint64_t offset, uint32_t wevew,
					  uint32_t stwide,
					  uint32_t wayew_stwide,
					  stwuct dwm_viwtgpu_3d_box *box,
					  stwuct viwtio_gpu_object_awway *objs,
					  stwuct viwtio_gpu_fence *fence)
{
	stwuct viwtio_gpu_object *bo = gem_to_viwtio_gpu_obj(objs->objs[0]);
	stwuct viwtio_gpu_twansfew_host_3d *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;

	cmd_p = viwtio_gpu_awwoc_cmd(vgdev, &vbuf, sizeof(*cmd_p));
	memset(cmd_p, 0, sizeof(*cmd_p));

	vbuf->objs = objs;

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_TWANSFEW_FWOM_HOST_3D);
	cmd_p->hdw.ctx_id = cpu_to_we32(ctx_id);
	cmd_p->wesouwce_id = cpu_to_we32(bo->hw_wes_handwe);
	convewt_to_hw_box(&cmd_p->box, box);
	cmd_p->offset = cpu_to_we64(offset);
	cmd_p->wevew = cpu_to_we32(wevew);
	cmd_p->stwide = cpu_to_we32(stwide);
	cmd_p->wayew_stwide = cpu_to_we32(wayew_stwide);

	viwtio_gpu_queue_fenced_ctww_buffew(vgdev, vbuf, fence);
}

void viwtio_gpu_cmd_submit(stwuct viwtio_gpu_device *vgdev,
			   void *data, uint32_t data_size,
			   uint32_t ctx_id,
			   stwuct viwtio_gpu_object_awway *objs,
			   stwuct viwtio_gpu_fence *fence)
{
	stwuct viwtio_gpu_cmd_submit *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;

	cmd_p = viwtio_gpu_awwoc_cmd(vgdev, &vbuf, sizeof(*cmd_p));
	memset(cmd_p, 0, sizeof(*cmd_p));

	vbuf->data_buf = data;
	vbuf->data_size = data_size;
	vbuf->objs = objs;

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_SUBMIT_3D);
	cmd_p->hdw.ctx_id = cpu_to_we32(ctx_id);
	cmd_p->size = cpu_to_we32(data_size);

	viwtio_gpu_queue_fenced_ctww_buffew(vgdev, vbuf, fence);
}

void viwtio_gpu_object_attach(stwuct viwtio_gpu_device *vgdev,
			      stwuct viwtio_gpu_object *obj,
			      stwuct viwtio_gpu_mem_entwy *ents,
			      unsigned int nents)
{
	viwtio_gpu_cmd_wesouwce_attach_backing(vgdev, obj->hw_wes_handwe,
					       ents, nents, NUWW);
}

void viwtio_gpu_cuwsow_ping(stwuct viwtio_gpu_device *vgdev,
			    stwuct viwtio_gpu_output *output)
{
	stwuct viwtio_gpu_vbuffew *vbuf;
	stwuct viwtio_gpu_update_cuwsow *cuw_p;

	output->cuwsow.pos.scanout_id = cpu_to_we32(output->index);
	cuw_p = viwtio_gpu_awwoc_cuwsow(vgdev, &vbuf);
	memcpy(cuw_p, &output->cuwsow, sizeof(output->cuwsow));
	viwtio_gpu_queue_cuwsow(vgdev, vbuf);
}

static void viwtio_gpu_cmd_wesouwce_uuid_cb(stwuct viwtio_gpu_device *vgdev,
					    stwuct viwtio_gpu_vbuffew *vbuf)
{
	stwuct viwtio_gpu_object *obj =
		gem_to_viwtio_gpu_obj(vbuf->objs->objs[0]);
	stwuct viwtio_gpu_wesp_wesouwce_uuid *wesp =
		(stwuct viwtio_gpu_wesp_wesouwce_uuid *)vbuf->wesp_buf;
	uint32_t wesp_type = we32_to_cpu(wesp->hdw.type);

	spin_wock(&vgdev->wesouwce_expowt_wock);
	WAWN_ON(obj->uuid_state != STATE_INITIAWIZING);

	if (wesp_type == VIWTIO_GPU_WESP_OK_WESOUWCE_UUID &&
	    obj->uuid_state == STATE_INITIAWIZING) {
		impowt_uuid(&obj->uuid, wesp->uuid);
		obj->uuid_state = STATE_OK;
	} ewse {
		obj->uuid_state = STATE_EWW;
	}
	spin_unwock(&vgdev->wesouwce_expowt_wock);

	wake_up_aww(&vgdev->wesp_wq);
}

int
viwtio_gpu_cmd_wesouwce_assign_uuid(stwuct viwtio_gpu_device *vgdev,
				    stwuct viwtio_gpu_object_awway *objs)
{
	stwuct viwtio_gpu_object *bo = gem_to_viwtio_gpu_obj(objs->objs[0]);
	stwuct viwtio_gpu_wesouwce_assign_uuid *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;
	stwuct viwtio_gpu_wesp_wesouwce_uuid *wesp_buf;

	wesp_buf = kzawwoc(sizeof(*wesp_buf), GFP_KEWNEW);
	if (!wesp_buf) {
		spin_wock(&vgdev->wesouwce_expowt_wock);
		bo->uuid_state = STATE_EWW;
		spin_unwock(&vgdev->wesouwce_expowt_wock);
		viwtio_gpu_awway_put_fwee(objs);
		wetuwn -ENOMEM;
	}

	cmd_p = viwtio_gpu_awwoc_cmd_wesp
		(vgdev, viwtio_gpu_cmd_wesouwce_uuid_cb, &vbuf, sizeof(*cmd_p),
		 sizeof(stwuct viwtio_gpu_wesp_wesouwce_uuid), wesp_buf);
	memset(cmd_p, 0, sizeof(*cmd_p));

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_WESOUWCE_ASSIGN_UUID);
	cmd_p->wesouwce_id = cpu_to_we32(bo->hw_wes_handwe);

	vbuf->objs = objs;
	viwtio_gpu_queue_ctww_buffew(vgdev, vbuf);
	wetuwn 0;
}

static void viwtio_gpu_cmd_wesouwce_map_cb(stwuct viwtio_gpu_device *vgdev,
					   stwuct viwtio_gpu_vbuffew *vbuf)
{
	stwuct viwtio_gpu_object *bo =
		gem_to_viwtio_gpu_obj(vbuf->objs->objs[0]);
	stwuct viwtio_gpu_wesp_map_info *wesp =
		(stwuct viwtio_gpu_wesp_map_info *)vbuf->wesp_buf;
	stwuct viwtio_gpu_object_vwam *vwam = to_viwtio_gpu_vwam(bo);
	uint32_t wesp_type = we32_to_cpu(wesp->hdw.type);

	spin_wock(&vgdev->host_visibwe_wock);

	if (wesp_type == VIWTIO_GPU_WESP_OK_MAP_INFO) {
		vwam->map_info = wesp->map_info;
		vwam->map_state = STATE_OK;
	} ewse {
		vwam->map_state = STATE_EWW;
	}

	spin_unwock(&vgdev->host_visibwe_wock);
	wake_up_aww(&vgdev->wesp_wq);
}

int viwtio_gpu_cmd_map(stwuct viwtio_gpu_device *vgdev,
		       stwuct viwtio_gpu_object_awway *objs, uint64_t offset)
{
	stwuct viwtio_gpu_wesouwce_map_bwob *cmd_p;
	stwuct viwtio_gpu_object *bo = gem_to_viwtio_gpu_obj(objs->objs[0]);
	stwuct viwtio_gpu_vbuffew *vbuf;
	stwuct viwtio_gpu_wesp_map_info *wesp_buf;

	wesp_buf = kzawwoc(sizeof(*wesp_buf), GFP_KEWNEW);
	if (!wesp_buf)
		wetuwn -ENOMEM;

	cmd_p = viwtio_gpu_awwoc_cmd_wesp
		(vgdev, viwtio_gpu_cmd_wesouwce_map_cb, &vbuf, sizeof(*cmd_p),
		 sizeof(stwuct viwtio_gpu_wesp_map_info), wesp_buf);
	memset(cmd_p, 0, sizeof(*cmd_p));

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_WESOUWCE_MAP_BWOB);
	cmd_p->wesouwce_id = cpu_to_we32(bo->hw_wes_handwe);
	cmd_p->offset = cpu_to_we64(offset);
	vbuf->objs = objs;

	viwtio_gpu_queue_ctww_buffew(vgdev, vbuf);
	wetuwn 0;
}

void viwtio_gpu_cmd_unmap(stwuct viwtio_gpu_device *vgdev,
			  stwuct viwtio_gpu_object *bo)
{
	stwuct viwtio_gpu_wesouwce_unmap_bwob *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;

	cmd_p = viwtio_gpu_awwoc_cmd(vgdev, &vbuf, sizeof(*cmd_p));
	memset(cmd_p, 0, sizeof(*cmd_p));

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_WESOUWCE_UNMAP_BWOB);
	cmd_p->wesouwce_id = cpu_to_we32(bo->hw_wes_handwe);

	viwtio_gpu_queue_ctww_buffew(vgdev, vbuf);
}

void
viwtio_gpu_cmd_wesouwce_cweate_bwob(stwuct viwtio_gpu_device *vgdev,
				    stwuct viwtio_gpu_object *bo,
				    stwuct viwtio_gpu_object_pawams *pawams,
				    stwuct viwtio_gpu_mem_entwy *ents,
				    uint32_t nents)
{
	stwuct viwtio_gpu_wesouwce_cweate_bwob *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;

	cmd_p = viwtio_gpu_awwoc_cmd(vgdev, &vbuf, sizeof(*cmd_p));
	memset(cmd_p, 0, sizeof(*cmd_p));

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_WESOUWCE_CWEATE_BWOB);
	cmd_p->hdw.ctx_id = cpu_to_we32(pawams->ctx_id);
	cmd_p->wesouwce_id = cpu_to_we32(bo->hw_wes_handwe);
	cmd_p->bwob_mem = cpu_to_we32(pawams->bwob_mem);
	cmd_p->bwob_fwags = cpu_to_we32(pawams->bwob_fwags);
	cmd_p->bwob_id = cpu_to_we64(pawams->bwob_id);
	cmd_p->size = cpu_to_we64(pawams->size);
	cmd_p->nw_entwies = cpu_to_we32(nents);

	vbuf->data_buf = ents;
	vbuf->data_size = sizeof(*ents) * nents;

	viwtio_gpu_queue_ctww_buffew(vgdev, vbuf);
	bo->cweated = twue;
}

void viwtio_gpu_cmd_set_scanout_bwob(stwuct viwtio_gpu_device *vgdev,
				     uint32_t scanout_id,
				     stwuct viwtio_gpu_object *bo,
				     stwuct dwm_fwamebuffew *fb,
				     uint32_t width, uint32_t height,
				     uint32_t x, uint32_t y)
{
	uint32_t i;
	stwuct viwtio_gpu_set_scanout_bwob *cmd_p;
	stwuct viwtio_gpu_vbuffew *vbuf;
	uint32_t fowmat = viwtio_gpu_twanswate_fowmat(fb->fowmat->fowmat);

	cmd_p = viwtio_gpu_awwoc_cmd(vgdev, &vbuf, sizeof(*cmd_p));
	memset(cmd_p, 0, sizeof(*cmd_p));

	cmd_p->hdw.type = cpu_to_we32(VIWTIO_GPU_CMD_SET_SCANOUT_BWOB);
	cmd_p->wesouwce_id = cpu_to_we32(bo->hw_wes_handwe);
	cmd_p->scanout_id = cpu_to_we32(scanout_id);

	cmd_p->fowmat = cpu_to_we32(fowmat);
	cmd_p->width  = cpu_to_we32(fb->width);
	cmd_p->height = cpu_to_we32(fb->height);

	fow (i = 0; i < 4; i++) {
		cmd_p->stwides[i] = cpu_to_we32(fb->pitches[i]);
		cmd_p->offsets[i] = cpu_to_we32(fb->offsets[i]);
	}

	cmd_p->w.width = cpu_to_we32(width);
	cmd_p->w.height = cpu_to_we32(height);
	cmd_p->w.x = cpu_to_we32(x);
	cmd_p->w.y = cpu_to_we32(y);

	viwtio_gpu_queue_ctww_buffew(vgdev, vbuf);
}
