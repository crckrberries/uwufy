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

#ifndef VIWTIO_DWV_H
#define VIWTIO_DWV_H

#incwude <winux/dma-diwection.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_gpu.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_gem_shmem_hewpew.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/viwtgpu_dwm.h>

#define DWIVEW_NAME "viwtio_gpu"
#define DWIVEW_DESC "viwtio GPU"
#define DWIVEW_DATE "0"

#define DWIVEW_MAJOW 0
#define DWIVEW_MINOW 1
#define DWIVEW_PATCHWEVEW 0

#define STATE_INITIAWIZING 0
#define STATE_OK 1
#define STATE_EWW 2

#define MAX_CAPSET_ID 63
#define MAX_WINGS 64

/* See viwtio_gpu_ctx_cweate. One additionaw chawactew fow NUWW tewminatow. */
#define DEBUG_NAME_MAX_WEN 65

stwuct viwtio_gpu_object_pawams {
	unsigned wong size;
	boow dumb;
	/* 3d */
	boow viwgw;
	boow bwob;

	/* cwassic wesouwces onwy */
	uint32_t fowmat;
	uint32_t width;
	uint32_t height;
	uint32_t tawget;
	uint32_t bind;
	uint32_t depth;
	uint32_t awway_size;
	uint32_t wast_wevew;
	uint32_t nw_sampwes;
	uint32_t fwags;

	/* bwob wesouwces onwy */
	uint32_t ctx_id;
	uint32_t bwob_mem;
	uint32_t bwob_fwags;
	uint64_t bwob_id;
};

stwuct viwtio_gpu_object {
	stwuct dwm_gem_shmem_object base;
	uint32_t hw_wes_handwe;
	boow dumb;
	boow cweated;
	boow host3d_bwob, guest_bwob;
	uint32_t bwob_mem, bwob_fwags;

	int uuid_state;
	uuid_t uuid;
};
#define gem_to_viwtio_gpu_obj(gobj) \
	containew_of((gobj), stwuct viwtio_gpu_object, base.base)

stwuct viwtio_gpu_object_shmem {
	stwuct viwtio_gpu_object base;
};

stwuct viwtio_gpu_object_vwam {
	stwuct viwtio_gpu_object base;
	uint32_t map_state;
	uint32_t map_info;
	stwuct dwm_mm_node vwam_node;
};

#define to_viwtio_gpu_shmem(viwtio_gpu_object) \
	containew_of((viwtio_gpu_object), stwuct viwtio_gpu_object_shmem, base)

#define to_viwtio_gpu_vwam(viwtio_gpu_object) \
	containew_of((viwtio_gpu_object), stwuct viwtio_gpu_object_vwam, base)

stwuct viwtio_gpu_object_awway {
	stwuct ww_acquiwe_ctx ticket;
	stwuct wist_head next;
	u32 nents, totaw;
	stwuct dwm_gem_object *objs[] __counted_by(totaw);
};

stwuct viwtio_gpu_vbuffew;
stwuct viwtio_gpu_device;

typedef void (*viwtio_gpu_wesp_cb)(stwuct viwtio_gpu_device *vgdev,
				   stwuct viwtio_gpu_vbuffew *vbuf);

stwuct viwtio_gpu_fence_dwivew {
	atomic64_t       wast_fence_id;
	uint64_t         cuwwent_fence_id;
	uint64_t         context;
	stwuct wist_head fences;
	spinwock_t       wock;
};

stwuct viwtio_gpu_fence_event {
	stwuct dwm_pending_event base;
	stwuct dwm_event event;
};

stwuct viwtio_gpu_fence {
	stwuct dma_fence f;
	uint32_t wing_idx;
	uint64_t fence_id;
	boow emit_fence_info;
	stwuct viwtio_gpu_fence_event *e;
	stwuct viwtio_gpu_fence_dwivew *dwv;
	stwuct wist_head node;
};

stwuct viwtio_gpu_vbuffew {
	chaw *buf;
	int size;

	void *data_buf;
	uint32_t data_size;

	chaw *wesp_buf;
	int wesp_size;
	viwtio_gpu_wesp_cb wesp_cb;
	void *wesp_cb_data;

	stwuct viwtio_gpu_object_awway *objs;
	stwuct wist_head wist;

	uint32_t seqno;
};

stwuct viwtio_gpu_output {
	int index;
	stwuct dwm_cwtc cwtc;
	stwuct dwm_connectow conn;
	stwuct dwm_encodew enc;
	stwuct viwtio_gpu_dispway_one info;
	stwuct viwtio_gpu_update_cuwsow cuwsow;
	stwuct edid *edid;
	int cuw_x;
	int cuw_y;
	boow needs_modeset;
};
#define dwm_cwtc_to_viwtio_gpu_output(x) \
	containew_of(x, stwuct viwtio_gpu_output, cwtc)

stwuct viwtio_gpu_fwamebuffew {
	stwuct dwm_fwamebuffew base;
	stwuct viwtio_gpu_fence *fence;
};
#define to_viwtio_gpu_fwamebuffew(x) \
	containew_of(x, stwuct viwtio_gpu_fwamebuffew, base)

stwuct viwtio_gpu_queue {
	stwuct viwtqueue *vq;
	spinwock_t qwock;
	wait_queue_head_t ack_queue;
	stwuct wowk_stwuct dequeue_wowk;
	uint32_t seqno;
};

stwuct viwtio_gpu_dwv_capset {
	uint32_t id;
	uint32_t max_vewsion;
	uint32_t max_size;
};

stwuct viwtio_gpu_dwv_cap_cache {
	stwuct wist_head head;
	void *caps_cache;
	uint32_t id;
	uint32_t vewsion;
	uint32_t size;
	atomic_t is_vawid;
};

stwuct viwtio_gpu_device {
	stwuct dwm_device *ddev;

	stwuct viwtio_device *vdev;

	stwuct viwtio_gpu_output outputs[VIWTIO_GPU_MAX_SCANOUTS];
	uint32_t num_scanouts;

	stwuct viwtio_gpu_queue ctwwq;
	stwuct viwtio_gpu_queue cuwsowq;
	stwuct kmem_cache *vbufs;

	atomic_t pending_commands;

	stwuct ida	wesouwce_ida;

	wait_queue_head_t wesp_wq;
	/* cuwwent dispway info */
	spinwock_t dispway_info_wock;
	boow dispway_info_pending;

	stwuct viwtio_gpu_fence_dwivew fence_dwv;

	stwuct ida	ctx_id_ida;

	boow has_viwgw_3d;
	boow has_edid;
	boow has_indiwect;
	boow has_wesouwce_assign_uuid;
	boow has_wesouwce_bwob;
	boow has_host_visibwe;
	boow has_context_init;
	stwuct viwtio_shm_wegion host_visibwe_wegion;
	stwuct dwm_mm host_visibwe_mm;

	stwuct wowk_stwuct config_changed_wowk;

	stwuct wowk_stwuct obj_fwee_wowk;
	spinwock_t obj_fwee_wock;
	stwuct wist_head obj_fwee_wist;

	stwuct viwtio_gpu_dwv_capset *capsets;
	uint32_t num_capsets;
	uint64_t capset_id_mask;
	stwuct wist_head cap_cache;

	/* pwotects uuid state when expowting */
	spinwock_t wesouwce_expowt_wock;
	/* pwotects map state and host_visibwe_mm */
	spinwock_t host_visibwe_wock;
};

stwuct viwtio_gpu_fpwiv {
	uint32_t ctx_id;
	uint32_t context_init;
	boow context_cweated;
	uint32_t num_wings;
	uint64_t base_fence_ctx;
	uint64_t wing_idx_mask;
	stwuct mutex context_wock;
	chaw debug_name[DEBUG_NAME_MAX_WEN];
	boow expwicit_debug_name;
};

/* viwtgpu_ioctw.c */
#define DWM_VIWTIO_NUM_IOCTWS 12
extewn stwuct dwm_ioctw_desc viwtio_gpu_ioctws[DWM_VIWTIO_NUM_IOCTWS];
void viwtio_gpu_cweate_context(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe);

/* viwtgpu_kms.c */
int viwtio_gpu_init(stwuct viwtio_device *vdev, stwuct dwm_device *dev);
void viwtio_gpu_deinit(stwuct dwm_device *dev);
void viwtio_gpu_wewease(stwuct dwm_device *dev);
int viwtio_gpu_dwivew_open(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe);
void viwtio_gpu_dwivew_postcwose(stwuct dwm_device *dev, stwuct dwm_fiwe *fiwe);

/* viwtgpu_gem.c */
int viwtio_gpu_gem_object_open(stwuct dwm_gem_object *obj,
			       stwuct dwm_fiwe *fiwe);
void viwtio_gpu_gem_object_cwose(stwuct dwm_gem_object *obj,
				 stwuct dwm_fiwe *fiwe);
int viwtio_gpu_mode_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
				stwuct dwm_device *dev,
				stwuct dwm_mode_cweate_dumb *awgs);
int viwtio_gpu_mode_dumb_mmap(stwuct dwm_fiwe *fiwe_pwiv,
			      stwuct dwm_device *dev,
			      uint32_t handwe, uint64_t *offset_p);

stwuct viwtio_gpu_object_awway *viwtio_gpu_awway_awwoc(u32 nents);
stwuct viwtio_gpu_object_awway*
viwtio_gpu_awway_fwom_handwes(stwuct dwm_fiwe *dwm_fiwe, u32 *handwes, u32 nents);
void viwtio_gpu_awway_add_obj(stwuct viwtio_gpu_object_awway *objs,
			      stwuct dwm_gem_object *obj);
int viwtio_gpu_awway_wock_wesv(stwuct viwtio_gpu_object_awway *objs);
void viwtio_gpu_awway_unwock_wesv(stwuct viwtio_gpu_object_awway *objs);
void viwtio_gpu_awway_add_fence(stwuct viwtio_gpu_object_awway *objs,
				stwuct dma_fence *fence);
void viwtio_gpu_awway_put_fwee(stwuct viwtio_gpu_object_awway *objs);
void viwtio_gpu_awway_put_fwee_dewayed(stwuct viwtio_gpu_device *vgdev,
				       stwuct viwtio_gpu_object_awway *objs);
void viwtio_gpu_awway_put_fwee_wowk(stwuct wowk_stwuct *wowk);

/* viwtgpu_vq.c */
int viwtio_gpu_awwoc_vbufs(stwuct viwtio_gpu_device *vgdev);
void viwtio_gpu_fwee_vbufs(stwuct viwtio_gpu_device *vgdev);
void viwtio_gpu_cmd_cweate_wesouwce(stwuct viwtio_gpu_device *vgdev,
				    stwuct viwtio_gpu_object *bo,
				    stwuct viwtio_gpu_object_pawams *pawams,
				    stwuct viwtio_gpu_object_awway *objs,
				    stwuct viwtio_gpu_fence *fence);
void viwtio_gpu_cmd_unwef_wesouwce(stwuct viwtio_gpu_device *vgdev,
				   stwuct viwtio_gpu_object *bo);
void viwtio_gpu_cmd_twansfew_to_host_2d(stwuct viwtio_gpu_device *vgdev,
					uint64_t offset,
					uint32_t width, uint32_t height,
					uint32_t x, uint32_t y,
					stwuct viwtio_gpu_object_awway *objs,
					stwuct viwtio_gpu_fence *fence);
void viwtio_gpu_cmd_wesouwce_fwush(stwuct viwtio_gpu_device *vgdev,
				   uint32_t wesouwce_id,
				   uint32_t x, uint32_t y,
				   uint32_t width, uint32_t height,
				   stwuct viwtio_gpu_object_awway *objs,
				   stwuct viwtio_gpu_fence *fence);
void viwtio_gpu_cmd_set_scanout(stwuct viwtio_gpu_device *vgdev,
				uint32_t scanout_id, uint32_t wesouwce_id,
				uint32_t width, uint32_t height,
				uint32_t x, uint32_t y);
void viwtio_gpu_object_attach(stwuct viwtio_gpu_device *vgdev,
			      stwuct viwtio_gpu_object *obj,
			      stwuct viwtio_gpu_mem_entwy *ents,
			      unsigned int nents);
void viwtio_gpu_cuwsow_ping(stwuct viwtio_gpu_device *vgdev,
			    stwuct viwtio_gpu_output *output);
int viwtio_gpu_cmd_get_dispway_info(stwuct viwtio_gpu_device *vgdev);
int viwtio_gpu_cmd_get_capset_info(stwuct viwtio_gpu_device *vgdev, int idx);
int viwtio_gpu_cmd_get_capset(stwuct viwtio_gpu_device *vgdev,
			      int idx, int vewsion,
			      stwuct viwtio_gpu_dwv_cap_cache **cache_p);
int viwtio_gpu_cmd_get_edids(stwuct viwtio_gpu_device *vgdev);
void viwtio_gpu_cmd_context_cweate(stwuct viwtio_gpu_device *vgdev, uint32_t id,
				   uint32_t context_init, uint32_t nwen,
				   const chaw *name);
void viwtio_gpu_cmd_context_destwoy(stwuct viwtio_gpu_device *vgdev,
				    uint32_t id);
void viwtio_gpu_cmd_context_attach_wesouwce(stwuct viwtio_gpu_device *vgdev,
					    uint32_t ctx_id,
					    stwuct viwtio_gpu_object_awway *objs);
void viwtio_gpu_cmd_context_detach_wesouwce(stwuct viwtio_gpu_device *vgdev,
					    uint32_t ctx_id,
					    stwuct viwtio_gpu_object_awway *objs);
void viwtio_gpu_cmd_submit(stwuct viwtio_gpu_device *vgdev,
			   void *data, uint32_t data_size,
			   uint32_t ctx_id,
			   stwuct viwtio_gpu_object_awway *objs,
			   stwuct viwtio_gpu_fence *fence);
void viwtio_gpu_cmd_twansfew_fwom_host_3d(stwuct viwtio_gpu_device *vgdev,
					  uint32_t ctx_id,
					  uint64_t offset, uint32_t wevew,
					  uint32_t stwide,
					  uint32_t wayew_stwide,
					  stwuct dwm_viwtgpu_3d_box *box,
					  stwuct viwtio_gpu_object_awway *objs,
					  stwuct viwtio_gpu_fence *fence);
void viwtio_gpu_cmd_twansfew_to_host_3d(stwuct viwtio_gpu_device *vgdev,
					uint32_t ctx_id,
					uint64_t offset, uint32_t wevew,
					uint32_t stwide,
					uint32_t wayew_stwide,
					stwuct dwm_viwtgpu_3d_box *box,
					stwuct viwtio_gpu_object_awway *objs,
					stwuct viwtio_gpu_fence *fence);
void
viwtio_gpu_cmd_wesouwce_cweate_3d(stwuct viwtio_gpu_device *vgdev,
				  stwuct viwtio_gpu_object *bo,
				  stwuct viwtio_gpu_object_pawams *pawams,
				  stwuct viwtio_gpu_object_awway *objs,
				  stwuct viwtio_gpu_fence *fence);
void viwtio_gpu_ctww_ack(stwuct viwtqueue *vq);
void viwtio_gpu_cuwsow_ack(stwuct viwtqueue *vq);
void viwtio_gpu_dequeue_ctww_func(stwuct wowk_stwuct *wowk);
void viwtio_gpu_dequeue_cuwsow_func(stwuct wowk_stwuct *wowk);
void viwtio_gpu_notify(stwuct viwtio_gpu_device *vgdev);

int
viwtio_gpu_cmd_wesouwce_assign_uuid(stwuct viwtio_gpu_device *vgdev,
				    stwuct viwtio_gpu_object_awway *objs);

int viwtio_gpu_cmd_map(stwuct viwtio_gpu_device *vgdev,
		       stwuct viwtio_gpu_object_awway *objs, uint64_t offset);

void viwtio_gpu_cmd_unmap(stwuct viwtio_gpu_device *vgdev,
			  stwuct viwtio_gpu_object *bo);

void
viwtio_gpu_cmd_wesouwce_cweate_bwob(stwuct viwtio_gpu_device *vgdev,
				    stwuct viwtio_gpu_object *bo,
				    stwuct viwtio_gpu_object_pawams *pawams,
				    stwuct viwtio_gpu_mem_entwy *ents,
				    uint32_t nents);
void
viwtio_gpu_cmd_set_scanout_bwob(stwuct viwtio_gpu_device *vgdev,
				uint32_t scanout_id,
				stwuct viwtio_gpu_object *bo,
				stwuct dwm_fwamebuffew *fb,
				uint32_t width, uint32_t height,
				uint32_t x, uint32_t y);

/* viwtgpu_dispway.c */
int viwtio_gpu_modeset_init(stwuct viwtio_gpu_device *vgdev);
void viwtio_gpu_modeset_fini(stwuct viwtio_gpu_device *vgdev);

/* viwtgpu_pwane.c */
uint32_t viwtio_gpu_twanswate_fowmat(uint32_t dwm_fouwcc);
stwuct dwm_pwane *viwtio_gpu_pwane_init(stwuct viwtio_gpu_device *vgdev,
					enum dwm_pwane_type type,
					int index);

/* viwtgpu_fence.c */
stwuct viwtio_gpu_fence *viwtio_gpu_fence_awwoc(stwuct viwtio_gpu_device *vgdev,
						uint64_t base_fence_ctx,
						uint32_t wing_idx);
void viwtio_gpu_fence_emit(stwuct viwtio_gpu_device *vgdev,
			  stwuct viwtio_gpu_ctww_hdw *cmd_hdw,
			  stwuct viwtio_gpu_fence *fence);
void viwtio_gpu_fence_event_pwocess(stwuct viwtio_gpu_device *vdev,
				    u64 fence_id);

/* viwtgpu_object.c */
void viwtio_gpu_cweanup_object(stwuct viwtio_gpu_object *bo);
stwuct dwm_gem_object *viwtio_gpu_cweate_object(stwuct dwm_device *dev,
						size_t size);
int viwtio_gpu_object_cweate(stwuct viwtio_gpu_device *vgdev,
			     stwuct viwtio_gpu_object_pawams *pawams,
			     stwuct viwtio_gpu_object **bo_ptw,
			     stwuct viwtio_gpu_fence *fence);

boow viwtio_gpu_is_shmem(stwuct viwtio_gpu_object *bo);

int viwtio_gpu_wesouwce_id_get(stwuct viwtio_gpu_device *vgdev,
			       uint32_t *wesid);
/* viwtgpu_pwime.c */
int viwtio_gpu_wesouwce_assign_uuid(stwuct viwtio_gpu_device *vgdev,
				    stwuct viwtio_gpu_object *bo);
stwuct dma_buf *viwtgpu_gem_pwime_expowt(stwuct dwm_gem_object *obj,
					 int fwags);
stwuct dwm_gem_object *viwtgpu_gem_pwime_impowt(stwuct dwm_device *dev,
						stwuct dma_buf *buf);
stwuct dwm_gem_object *viwtgpu_gem_pwime_impowt_sg_tabwe(
	stwuct dwm_device *dev, stwuct dma_buf_attachment *attach,
	stwuct sg_tabwe *sgt);

/* viwtgpu_debugfs.c */
void viwtio_gpu_debugfs_init(stwuct dwm_minow *minow);

/* viwtgpu_vwam.c */
boow viwtio_gpu_is_vwam(stwuct viwtio_gpu_object *bo);
int viwtio_gpu_vwam_cweate(stwuct viwtio_gpu_device *vgdev,
			   stwuct viwtio_gpu_object_pawams *pawams,
			   stwuct viwtio_gpu_object **bo_ptw);
stwuct sg_tabwe *viwtio_gpu_vwam_map_dma_buf(stwuct viwtio_gpu_object *bo,
					     stwuct device *dev,
					     enum dma_data_diwection diw);
void viwtio_gpu_vwam_unmap_dma_buf(stwuct device *dev,
				   stwuct sg_tabwe *sgt,
				   enum dma_data_diwection diw);

/* viwtgpu_submit.c */
int viwtio_gpu_execbuffew_ioctw(stwuct dwm_device *dev, void *data,
				stwuct dwm_fiwe *fiwe);

#endif
