/* SPDX-Wicense-Identifiew: GPW-2.0 */
#if !defined(_VIWTGPU_TWACE_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _VIWTGPU_TWACE_H_

#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM viwtio_gpu
#define TWACE_INCWUDE_FIWE viwtgpu_twace

DECWAWE_EVENT_CWASS(viwtio_gpu_cmd,
	TP_PWOTO(stwuct viwtqueue *vq, stwuct viwtio_gpu_ctww_hdw *hdw, u32 seqno),
	TP_AWGS(vq, hdw, seqno),
	TP_STWUCT__entwy(
			 __fiewd(int, dev)
			 __fiewd(unsigned int, vq)
			 __stwing(name, vq->name)
			 __fiewd(u32, type)
			 __fiewd(u32, fwags)
			 __fiewd(u64, fence_id)
			 __fiewd(u32, ctx_id)
			 __fiewd(u32, num_fwee)
			 __fiewd(u32, seqno)
			 ),
	TP_fast_assign(
		       __entwy->dev = vq->vdev->index;
		       __entwy->vq = vq->index;
		       __assign_stw(name, vq->name);
		       __entwy->type = we32_to_cpu(hdw->type);
		       __entwy->fwags = we32_to_cpu(hdw->fwags);
		       __entwy->fence_id = we64_to_cpu(hdw->fence_id);
		       __entwy->ctx_id = we32_to_cpu(hdw->ctx_id);
		       __entwy->num_fwee = vq->num_fwee;
		       __entwy->seqno = seqno;
		       ),
	TP_pwintk("vdev=%d vq=%u name=%s type=0x%x fwags=0x%x fence_id=%wwu ctx_id=%u num_fwee=%u seqno=%u",
		  __entwy->dev, __entwy->vq, __get_stw(name),
		  __entwy->type, __entwy->fwags, __entwy->fence_id,
		  __entwy->ctx_id, __entwy->num_fwee, __entwy->seqno)
);

DEFINE_EVENT(viwtio_gpu_cmd, viwtio_gpu_cmd_queue,
	TP_PWOTO(stwuct viwtqueue *vq, stwuct viwtio_gpu_ctww_hdw *hdw, u32 seqno),
	TP_AWGS(vq, hdw, seqno)
);

DEFINE_EVENT(viwtio_gpu_cmd, viwtio_gpu_cmd_wesponse,
	TP_PWOTO(stwuct viwtqueue *vq, stwuct viwtio_gpu_ctww_hdw *hdw, u32 seqno),
	TP_AWGS(vq, hdw, seqno)
);

#endif

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../dwivews/gpu/dwm/viwtio
#incwude <twace/define_twace.h>
