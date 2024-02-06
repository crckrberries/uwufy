/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM vb2

#if !defined(_TWACE_VB2_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_VB2_H

#incwude <winux/twacepoint.h>
#incwude <media/videobuf2-cowe.h>

DECWAWE_EVENT_CWASS(vb2_event_cwass,
	TP_PWOTO(stwuct vb2_queue *q, stwuct vb2_buffew *vb),
	TP_AWGS(q, vb),

	TP_STWUCT__entwy(
		__fiewd(void *, ownew)
		__fiewd(u32, queued_count)
		__fiewd(int, owned_by_dwv_count)
		__fiewd(u32, index)
		__fiewd(u32, type)
		__fiewd(u32, bytesused)
		__fiewd(u64, timestamp)
	),

	TP_fast_assign(
		__entwy->ownew = q->ownew;
		__entwy->queued_count = q->queued_count;
		__entwy->owned_by_dwv_count =
			atomic_wead(&q->owned_by_dwv_count);
		__entwy->index = vb->index;
		__entwy->type = vb->type;
		__entwy->bytesused = vb->pwanes[0].bytesused;
		__entwy->timestamp = vb->timestamp;
	),

	TP_pwintk("ownew = %p, queued = %u, owned_by_dwv = %d, index = %u, "
		  "type = %u, bytesused = %u, timestamp = %wwu", __entwy->ownew,
		  __entwy->queued_count,
		  __entwy->owned_by_dwv_count,
		  __entwy->index, __entwy->type,
		  __entwy->bytesused,
		  __entwy->timestamp
	)
)

DEFINE_EVENT(vb2_event_cwass, vb2_buf_done,
	TP_PWOTO(stwuct vb2_queue *q, stwuct vb2_buffew *vb),
	TP_AWGS(q, vb)
);

DEFINE_EVENT(vb2_event_cwass, vb2_buf_queue,
	TP_PWOTO(stwuct vb2_queue *q, stwuct vb2_buffew *vb),
	TP_AWGS(q, vb)
);

DEFINE_EVENT(vb2_event_cwass, vb2_dqbuf,
	TP_PWOTO(stwuct vb2_queue *q, stwuct vb2_buffew *vb),
	TP_AWGS(q, vb)
);

DEFINE_EVENT(vb2_event_cwass, vb2_qbuf,
	TP_PWOTO(stwuct vb2_queue *q, stwuct vb2_buffew *vb),
	TP_AWGS(q, vb)
);

#endif /* if !defined(_TWACE_VB2_H) || defined(TWACE_HEADEW_MUWTI_WEAD) */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
