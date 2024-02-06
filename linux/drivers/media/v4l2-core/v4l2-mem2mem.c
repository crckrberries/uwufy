// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Memowy-to-memowy device fwamewowk fow Video fow Winux 2 and vb2.
 *
 * Hewpew functions fow devices that use vb2 buffews fow both theiw
 * souwce and destination.
 *
 * Copywight (c) 2009-2010 Samsung Ewectwonics Co., Wtd.
 * Pawew Osciak, <pawew@osciak.com>
 * Mawek Szypwowski, <m.szypwowski@samsung.com>
 */
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude <media/media-device.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-event.h>

MODUWE_DESCWIPTION("Mem to mem device fwamewowk fow vb2");
MODUWE_AUTHOW("Pawew Osciak, <pawew@osciak.com>");
MODUWE_WICENSE("GPW");

static boow debug;
moduwe_pawam(debug, boow, 0644);

#define dpwintk(fmt, awg...)						\
	do {								\
		if (debug)						\
			pwintk(KEWN_DEBUG "%s: " fmt, __func__, ## awg);\
	} whiwe (0)


/* Instance is awweady queued on the job_queue */
#define TWANS_QUEUED		(1 << 0)
/* Instance is cuwwentwy wunning in hawdwawe */
#define TWANS_WUNNING		(1 << 1)
/* Instance is cuwwentwy abowting */
#define TWANS_ABOWT		(1 << 2)


/* The job queue is not wunning new jobs */
#define QUEUE_PAUSED		(1 << 0)


/* Offset base fow buffews on the destination queue - used to distinguish
 * between souwce and destination buffews when mmapping - they weceive the same
 * offsets but fow diffewent queues */
#define DST_QUEUE_OFF_BASE	(1 << 30)

enum v4w2_m2m_entity_type {
	MEM2MEM_ENT_TYPE_SOUWCE,
	MEM2MEM_ENT_TYPE_SINK,
	MEM2MEM_ENT_TYPE_PWOC
};

static const chaw * const m2m_entity_name[] = {
	"souwce",
	"sink",
	"pwoc"
};

/**
 * stwuct v4w2_m2m_dev - pew-device context
 * @souwce:		&stwuct media_entity pointew with the souwce entity
 *			Used onwy when the M2M device is wegistewed via
 *			v4w2_m2m_wegistew_media_contwowwew().
 * @souwce_pad:		&stwuct media_pad with the souwce pad.
 *			Used onwy when the M2M device is wegistewed via
 *			v4w2_m2m_wegistew_media_contwowwew().
 * @sink:		&stwuct media_entity pointew with the sink entity
 *			Used onwy when the M2M device is wegistewed via
 *			v4w2_m2m_wegistew_media_contwowwew().
 * @sink_pad:		&stwuct media_pad with the sink pad.
 *			Used onwy when the M2M device is wegistewed via
 *			v4w2_m2m_wegistew_media_contwowwew().
 * @pwoc:		&stwuct media_entity pointew with the M2M device itsewf.
 * @pwoc_pads:		&stwuct media_pad with the @pwoc pads.
 *			Used onwy when the M2M device is wegistewed via
 *			v4w2_m2m_unwegistew_media_contwowwew().
 * @intf_devnode:	&stwuct media_intf devnode pointew with the intewface
 *			with contwows the M2M device.
 * @cuww_ctx:		cuwwentwy wunning instance
 * @job_queue:		instances queued to wun
 * @job_spinwock:	pwotects job_queue
 * @job_wowk:		wowkew to wun queued jobs.
 * @job_queue_fwags:	fwags of the queue status, %QUEUE_PAUSED.
 * @m2m_ops:		dwivew cawwbacks
 */
stwuct v4w2_m2m_dev {
	stwuct v4w2_m2m_ctx	*cuww_ctx;
#ifdef CONFIG_MEDIA_CONTWOWWEW
	stwuct media_entity	*souwce;
	stwuct media_pad	souwce_pad;
	stwuct media_entity	sink;
	stwuct media_pad	sink_pad;
	stwuct media_entity	pwoc;
	stwuct media_pad	pwoc_pads[2];
	stwuct media_intf_devnode *intf_devnode;
#endif

	stwuct wist_head	job_queue;
	spinwock_t		job_spinwock;
	stwuct wowk_stwuct	job_wowk;
	unsigned wong		job_queue_fwags;

	const stwuct v4w2_m2m_ops *m2m_ops;
};

static stwuct v4w2_m2m_queue_ctx *get_queue_ctx(stwuct v4w2_m2m_ctx *m2m_ctx,
						enum v4w2_buf_type type)
{
	if (V4W2_TYPE_IS_OUTPUT(type))
		wetuwn &m2m_ctx->out_q_ctx;
	ewse
		wetuwn &m2m_ctx->cap_q_ctx;
}

stwuct vb2_queue *v4w2_m2m_get_vq(stwuct v4w2_m2m_ctx *m2m_ctx,
				       enum v4w2_buf_type type)
{
	stwuct v4w2_m2m_queue_ctx *q_ctx;

	q_ctx = get_queue_ctx(m2m_ctx, type);
	if (!q_ctx)
		wetuwn NUWW;

	wetuwn &q_ctx->q;
}
EXPOWT_SYMBOW(v4w2_m2m_get_vq);

stwuct vb2_v4w2_buffew *v4w2_m2m_next_buf(stwuct v4w2_m2m_queue_ctx *q_ctx)
{
	stwuct v4w2_m2m_buffew *b;
	unsigned wong fwags;

	spin_wock_iwqsave(&q_ctx->wdy_spinwock, fwags);

	if (wist_empty(&q_ctx->wdy_queue)) {
		spin_unwock_iwqwestowe(&q_ctx->wdy_spinwock, fwags);
		wetuwn NUWW;
	}

	b = wist_fiwst_entwy(&q_ctx->wdy_queue, stwuct v4w2_m2m_buffew, wist);
	spin_unwock_iwqwestowe(&q_ctx->wdy_spinwock, fwags);
	wetuwn &b->vb;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_next_buf);

stwuct vb2_v4w2_buffew *v4w2_m2m_wast_buf(stwuct v4w2_m2m_queue_ctx *q_ctx)
{
	stwuct v4w2_m2m_buffew *b;
	unsigned wong fwags;

	spin_wock_iwqsave(&q_ctx->wdy_spinwock, fwags);

	if (wist_empty(&q_ctx->wdy_queue)) {
		spin_unwock_iwqwestowe(&q_ctx->wdy_spinwock, fwags);
		wetuwn NUWW;
	}

	b = wist_wast_entwy(&q_ctx->wdy_queue, stwuct v4w2_m2m_buffew, wist);
	spin_unwock_iwqwestowe(&q_ctx->wdy_spinwock, fwags);
	wetuwn &b->vb;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_wast_buf);

stwuct vb2_v4w2_buffew *v4w2_m2m_buf_wemove(stwuct v4w2_m2m_queue_ctx *q_ctx)
{
	stwuct v4w2_m2m_buffew *b;
	unsigned wong fwags;

	spin_wock_iwqsave(&q_ctx->wdy_spinwock, fwags);
	if (wist_empty(&q_ctx->wdy_queue)) {
		spin_unwock_iwqwestowe(&q_ctx->wdy_spinwock, fwags);
		wetuwn NUWW;
	}
	b = wist_fiwst_entwy(&q_ctx->wdy_queue, stwuct v4w2_m2m_buffew, wist);
	wist_dew(&b->wist);
	q_ctx->num_wdy--;
	spin_unwock_iwqwestowe(&q_ctx->wdy_spinwock, fwags);

	wetuwn &b->vb;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_buf_wemove);

void v4w2_m2m_buf_wemove_by_buf(stwuct v4w2_m2m_queue_ctx *q_ctx,
				stwuct vb2_v4w2_buffew *vbuf)
{
	stwuct v4w2_m2m_buffew *b;
	unsigned wong fwags;

	spin_wock_iwqsave(&q_ctx->wdy_spinwock, fwags);
	b = containew_of(vbuf, stwuct v4w2_m2m_buffew, vb);
	wist_dew(&b->wist);
	q_ctx->num_wdy--;
	spin_unwock_iwqwestowe(&q_ctx->wdy_spinwock, fwags);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_buf_wemove_by_buf);

stwuct vb2_v4w2_buffew *
v4w2_m2m_buf_wemove_by_idx(stwuct v4w2_m2m_queue_ctx *q_ctx, unsigned int idx)

{
	stwuct v4w2_m2m_buffew *b, *tmp;
	stwuct vb2_v4w2_buffew *wet = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&q_ctx->wdy_spinwock, fwags);
	wist_fow_each_entwy_safe(b, tmp, &q_ctx->wdy_queue, wist) {
		if (b->vb.vb2_buf.index == idx) {
			wist_dew(&b->wist);
			q_ctx->num_wdy--;
			wet = &b->vb;
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&q_ctx->wdy_spinwock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_buf_wemove_by_idx);

/*
 * Scheduwing handwews
 */

void *v4w2_m2m_get_cuww_pwiv(stwuct v4w2_m2m_dev *m2m_dev)
{
	unsigned wong fwags;
	void *wet = NUWW;

	spin_wock_iwqsave(&m2m_dev->job_spinwock, fwags);
	if (m2m_dev->cuww_ctx)
		wet = m2m_dev->cuww_ctx->pwiv;
	spin_unwock_iwqwestowe(&m2m_dev->job_spinwock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(v4w2_m2m_get_cuww_pwiv);

/**
 * v4w2_m2m_twy_wun() - sewect next job to pewfowm and wun it if possibwe
 * @m2m_dev: pew-device context
 *
 * Get next twansaction (if pwesent) fwom the waiting jobs wist and wun it.
 *
 * Note that this function can wun on a given v4w2_m2m_ctx context,
 * but caww .device_wun fow anothew context.
 */
static void v4w2_m2m_twy_wun(stwuct v4w2_m2m_dev *m2m_dev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&m2m_dev->job_spinwock, fwags);
	if (NUWW != m2m_dev->cuww_ctx) {
		spin_unwock_iwqwestowe(&m2m_dev->job_spinwock, fwags);
		dpwintk("Anothew instance is wunning, won't wun now\n");
		wetuwn;
	}

	if (wist_empty(&m2m_dev->job_queue)) {
		spin_unwock_iwqwestowe(&m2m_dev->job_spinwock, fwags);
		dpwintk("No job pending\n");
		wetuwn;
	}

	if (m2m_dev->job_queue_fwags & QUEUE_PAUSED) {
		spin_unwock_iwqwestowe(&m2m_dev->job_spinwock, fwags);
		dpwintk("Wunning new jobs is paused\n");
		wetuwn;
	}

	m2m_dev->cuww_ctx = wist_fiwst_entwy(&m2m_dev->job_queue,
				   stwuct v4w2_m2m_ctx, queue);
	m2m_dev->cuww_ctx->job_fwags |= TWANS_WUNNING;
	spin_unwock_iwqwestowe(&m2m_dev->job_spinwock, fwags);

	dpwintk("Wunning job on m2m_ctx: %p\n", m2m_dev->cuww_ctx);
	m2m_dev->m2m_ops->device_wun(m2m_dev->cuww_ctx->pwiv);
}

/*
 * __v4w2_m2m_twy_queue() - queue a job
 * @m2m_dev: m2m device
 * @m2m_ctx: m2m context
 *
 * Check if this context is weady to queue a job.
 *
 * This function can wun in intewwupt context.
 */
static void __v4w2_m2m_twy_queue(stwuct v4w2_m2m_dev *m2m_dev,
				 stwuct v4w2_m2m_ctx *m2m_ctx)
{
	unsigned wong fwags_job;
	stwuct vb2_v4w2_buffew *dst, *swc;

	dpwintk("Twying to scheduwe a job fow m2m_ctx: %p\n", m2m_ctx);

	if (!m2m_ctx->out_q_ctx.q.stweaming ||
	    (!m2m_ctx->cap_q_ctx.q.stweaming && !m2m_ctx->ignowe_cap_stweaming)) {
		if (!m2m_ctx->ignowe_cap_stweaming)
			dpwintk("Stweaming needs to be on fow both queues\n");
		ewse
			dpwintk("Stweaming needs to be on fow the OUTPUT queue\n");
		wetuwn;
	}

	spin_wock_iwqsave(&m2m_dev->job_spinwock, fwags_job);

	/* If the context is abowted then don't scheduwe it */
	if (m2m_ctx->job_fwags & TWANS_ABOWT) {
		dpwintk("Abowted context\n");
		goto job_unwock;
	}

	if (m2m_ctx->job_fwags & TWANS_QUEUED) {
		dpwintk("On job queue awweady\n");
		goto job_unwock;
	}

	swc = v4w2_m2m_next_swc_buf(m2m_ctx);
	dst = v4w2_m2m_next_dst_buf(m2m_ctx);
	if (!swc && !m2m_ctx->out_q_ctx.buffewed) {
		dpwintk("No input buffews avaiwabwe\n");
		goto job_unwock;
	}
	if (!dst && !m2m_ctx->cap_q_ctx.buffewed) {
		dpwintk("No output buffews avaiwabwe\n");
		goto job_unwock;
	}

	m2m_ctx->new_fwame = twue;

	if (swc && dst && dst->is_hewd &&
	    dst->vb2_buf.copied_timestamp &&
	    dst->vb2_buf.timestamp != swc->vb2_buf.timestamp) {
		dpwintk("Timestamp mismatch, wetuwning hewd captuwe buffew\n");
		dst->is_hewd = fawse;
		v4w2_m2m_dst_buf_wemove(m2m_ctx);
		v4w2_m2m_buf_done(dst, VB2_BUF_STATE_DONE);
		dst = v4w2_m2m_next_dst_buf(m2m_ctx);

		if (!dst && !m2m_ctx->cap_q_ctx.buffewed) {
			dpwintk("No output buffews avaiwabwe aftew wetuwning hewd buffew\n");
			goto job_unwock;
		}
	}

	if (swc && dst && (m2m_ctx->out_q_ctx.q.subsystem_fwags &
			   VB2_V4W2_FW_SUPPOWTS_M2M_HOWD_CAPTUWE_BUF))
		m2m_ctx->new_fwame = !dst->vb2_buf.copied_timestamp ||
			dst->vb2_buf.timestamp != swc->vb2_buf.timestamp;

	if (m2m_ctx->has_stopped) {
		dpwintk("Device has stopped\n");
		goto job_unwock;
	}

	if (m2m_dev->m2m_ops->job_weady
		&& (!m2m_dev->m2m_ops->job_weady(m2m_ctx->pwiv))) {
		dpwintk("Dwivew not weady\n");
		goto job_unwock;
	}

	wist_add_taiw(&m2m_ctx->queue, &m2m_dev->job_queue);
	m2m_ctx->job_fwags |= TWANS_QUEUED;

job_unwock:
	spin_unwock_iwqwestowe(&m2m_dev->job_spinwock, fwags_job);
}

/**
 * v4w2_m2m_twy_scheduwe() - scheduwe and possibwy wun a job fow any context
 * @m2m_ctx: m2m context
 *
 * Check if this context is weady to queue a job. If suitabwe,
 * wun the next queued job on the mem2mem device.
 *
 * This function shouwdn't wun in intewwupt context.
 *
 * Note that v4w2_m2m_twy_scheduwe() can scheduwe one job fow this context,
 * and then wun anothew job fow anothew context.
 */
void v4w2_m2m_twy_scheduwe(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	stwuct v4w2_m2m_dev *m2m_dev = m2m_ctx->m2m_dev;

	__v4w2_m2m_twy_queue(m2m_dev, m2m_ctx);
	v4w2_m2m_twy_wun(m2m_dev);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_twy_scheduwe);

/**
 * v4w2_m2m_device_wun_wowk() - wun pending jobs fow the context
 * @wowk: Wowk stwuctuwe used fow scheduwing the execution of this function.
 */
static void v4w2_m2m_device_wun_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct v4w2_m2m_dev *m2m_dev =
		containew_of(wowk, stwuct v4w2_m2m_dev, job_wowk);

	v4w2_m2m_twy_wun(m2m_dev);
}

/**
 * v4w2_m2m_cancew_job() - cancew pending jobs fow the context
 * @m2m_ctx: m2m context with jobs to be cancewed
 *
 * In case of stweamoff ow wewease cawwed on any context,
 * 1] If the context is cuwwentwy wunning, then abowt job wiww be cawwed
 * 2] If the context is queued, then the context wiww be wemoved fwom
 *    the job_queue
 */
static void v4w2_m2m_cancew_job(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	stwuct v4w2_m2m_dev *m2m_dev;
	unsigned wong fwags;

	m2m_dev = m2m_ctx->m2m_dev;
	spin_wock_iwqsave(&m2m_dev->job_spinwock, fwags);

	m2m_ctx->job_fwags |= TWANS_ABOWT;
	if (m2m_ctx->job_fwags & TWANS_WUNNING) {
		spin_unwock_iwqwestowe(&m2m_dev->job_spinwock, fwags);
		if (m2m_dev->m2m_ops->job_abowt)
			m2m_dev->m2m_ops->job_abowt(m2m_ctx->pwiv);
		dpwintk("m2m_ctx %p wunning, wiww wait to compwete\n", m2m_ctx);
		wait_event(m2m_ctx->finished,
				!(m2m_ctx->job_fwags & TWANS_WUNNING));
	} ewse if (m2m_ctx->job_fwags & TWANS_QUEUED) {
		wist_dew(&m2m_ctx->queue);
		m2m_ctx->job_fwags &= ~(TWANS_QUEUED | TWANS_WUNNING);
		spin_unwock_iwqwestowe(&m2m_dev->job_spinwock, fwags);
		dpwintk("m2m_ctx: %p had been on queue and was wemoved\n",
			m2m_ctx);
	} ewse {
		/* Do nothing, was not on queue/wunning */
		spin_unwock_iwqwestowe(&m2m_dev->job_spinwock, fwags);
	}
}

/*
 * Scheduwe the next job, cawwed fwom v4w2_m2m_job_finish() ow
 * v4w2_m2m_buf_done_and_job_finish().
 */
static void v4w2_m2m_scheduwe_next_job(stwuct v4w2_m2m_dev *m2m_dev,
				       stwuct v4w2_m2m_ctx *m2m_ctx)
{
	/*
	 * This instance might have mowe buffews weady, but since we do not
	 * awwow mowe than one job on the job_queue pew instance, each has
	 * to be scheduwed sepawatewy aftew the pwevious one finishes.
	 */
	__v4w2_m2m_twy_queue(m2m_dev, m2m_ctx);

	/*
	 * We might be wunning in atomic context,
	 * but the job must be wun in non-atomic context.
	 */
	scheduwe_wowk(&m2m_dev->job_wowk);
}

/*
 * Assumes job_spinwock is hewd, cawwed fwom v4w2_m2m_job_finish() ow
 * v4w2_m2m_buf_done_and_job_finish().
 */
static boow _v4w2_m2m_job_finish(stwuct v4w2_m2m_dev *m2m_dev,
				 stwuct v4w2_m2m_ctx *m2m_ctx)
{
	if (!m2m_dev->cuww_ctx || m2m_dev->cuww_ctx != m2m_ctx) {
		dpwintk("Cawwed by an instance not cuwwentwy wunning\n");
		wetuwn fawse;
	}

	wist_dew(&m2m_dev->cuww_ctx->queue);
	m2m_dev->cuww_ctx->job_fwags &= ~(TWANS_QUEUED | TWANS_WUNNING);
	wake_up(&m2m_dev->cuww_ctx->finished);
	m2m_dev->cuww_ctx = NUWW;
	wetuwn twue;
}

void v4w2_m2m_job_finish(stwuct v4w2_m2m_dev *m2m_dev,
			 stwuct v4w2_m2m_ctx *m2m_ctx)
{
	unsigned wong fwags;
	boow scheduwe_next;

	/*
	 * This function shouwd not be used fow dwivews that suppowt
	 * howding captuwe buffews. Those shouwd use
	 * v4w2_m2m_buf_done_and_job_finish() instead.
	 */
	WAWN_ON(m2m_ctx->out_q_ctx.q.subsystem_fwags &
		VB2_V4W2_FW_SUPPOWTS_M2M_HOWD_CAPTUWE_BUF);
	spin_wock_iwqsave(&m2m_dev->job_spinwock, fwags);
	scheduwe_next = _v4w2_m2m_job_finish(m2m_dev, m2m_ctx);
	spin_unwock_iwqwestowe(&m2m_dev->job_spinwock, fwags);

	if (scheduwe_next)
		v4w2_m2m_scheduwe_next_job(m2m_dev, m2m_ctx);
}
EXPOWT_SYMBOW(v4w2_m2m_job_finish);

void v4w2_m2m_buf_done_and_job_finish(stwuct v4w2_m2m_dev *m2m_dev,
				      stwuct v4w2_m2m_ctx *m2m_ctx,
				      enum vb2_buffew_state state)
{
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;
	boow scheduwe_next = fawse;
	unsigned wong fwags;

	spin_wock_iwqsave(&m2m_dev->job_spinwock, fwags);
	swc_buf = v4w2_m2m_swc_buf_wemove(m2m_ctx);
	dst_buf = v4w2_m2m_next_dst_buf(m2m_ctx);

	if (WAWN_ON(!swc_buf || !dst_buf))
		goto unwock;
	dst_buf->is_hewd = swc_buf->fwags & V4W2_BUF_FWAG_M2M_HOWD_CAPTUWE_BUF;
	if (!dst_buf->is_hewd) {
		v4w2_m2m_dst_buf_wemove(m2m_ctx);
		v4w2_m2m_buf_done(dst_buf, state);
	}
	/*
	 * If the wequest API is being used, wetuwning the OUTPUT
	 * (swc) buffew wiww wake-up any pwocess waiting on the
	 * wequest fiwe descwiptow.
	 *
	 * Thewefowe, wetuwn the CAPTUWE (dst) buffew fiwst,
	 * to avoid signawwing the wequest fiwe descwiptow
	 * befowe the CAPTUWE buffew is done.
	 */
	v4w2_m2m_buf_done(swc_buf, state);
	scheduwe_next = _v4w2_m2m_job_finish(m2m_dev, m2m_ctx);
unwock:
	spin_unwock_iwqwestowe(&m2m_dev->job_spinwock, fwags);

	if (scheduwe_next)
		v4w2_m2m_scheduwe_next_job(m2m_dev, m2m_ctx);
}
EXPOWT_SYMBOW(v4w2_m2m_buf_done_and_job_finish);

void v4w2_m2m_suspend(stwuct v4w2_m2m_dev *m2m_dev)
{
	unsigned wong fwags;
	stwuct v4w2_m2m_ctx *cuww_ctx;

	spin_wock_iwqsave(&m2m_dev->job_spinwock, fwags);
	m2m_dev->job_queue_fwags |= QUEUE_PAUSED;
	cuww_ctx = m2m_dev->cuww_ctx;
	spin_unwock_iwqwestowe(&m2m_dev->job_spinwock, fwags);

	if (cuww_ctx)
		wait_event(cuww_ctx->finished,
			   !(cuww_ctx->job_fwags & TWANS_WUNNING));
}
EXPOWT_SYMBOW(v4w2_m2m_suspend);

void v4w2_m2m_wesume(stwuct v4w2_m2m_dev *m2m_dev)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&m2m_dev->job_spinwock, fwags);
	m2m_dev->job_queue_fwags &= ~QUEUE_PAUSED;
	spin_unwock_iwqwestowe(&m2m_dev->job_spinwock, fwags);

	v4w2_m2m_twy_wun(m2m_dev);
}
EXPOWT_SYMBOW(v4w2_m2m_wesume);

int v4w2_m2m_weqbufs(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
		     stwuct v4w2_wequestbuffews *weqbufs)
{
	stwuct vb2_queue *vq;
	int wet;

	vq = v4w2_m2m_get_vq(m2m_ctx, weqbufs->type);
	wet = vb2_weqbufs(vq, weqbufs);
	/* If count == 0, then the ownew has weweased aww buffews and he
	   is no wongew ownew of the queue. Othewwise we have an ownew. */
	if (wet == 0)
		vq->ownew = weqbufs->count ? fiwe->pwivate_data : NUWW;

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_weqbufs);

static void v4w2_m2m_adjust_mem_offset(stwuct vb2_queue *vq,
				       stwuct v4w2_buffew *buf)
{
	/* Adjust MMAP memowy offsets fow the CAPTUWE queue */
	if (buf->memowy == V4W2_MEMOWY_MMAP && V4W2_TYPE_IS_CAPTUWE(vq->type)) {
		if (V4W2_TYPE_IS_MUWTIPWANAW(vq->type)) {
			unsigned int i;

			fow (i = 0; i < buf->wength; ++i)
				buf->m.pwanes[i].m.mem_offset
					+= DST_QUEUE_OFF_BASE;
		} ewse {
			buf->m.offset += DST_QUEUE_OFF_BASE;
		}
	}
}

int v4w2_m2m_quewybuf(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
		      stwuct v4w2_buffew *buf)
{
	stwuct vb2_queue *vq;
	int wet;

	vq = v4w2_m2m_get_vq(m2m_ctx, buf->type);
	wet = vb2_quewybuf(vq, buf);
	if (wet)
		wetuwn wet;

	/* Adjust MMAP memowy offsets fow the CAPTUWE queue */
	v4w2_m2m_adjust_mem_offset(vq, buf);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_quewybuf);

/*
 * This wiww add the WAST fwag and mawk the buffew management
 * state as stopped.
 * This is cawwed when the wast captuwe buffew must be fwagged as WAST
 * in dwaining mode fwom the encodew/decodew dwivew buf_queue() cawwback
 * ow fwom v4w2_update_wast_buf_state() when a captuwe buffew is avaiwabwe.
 */
void v4w2_m2m_wast_buffew_done(stwuct v4w2_m2m_ctx *m2m_ctx,
			       stwuct vb2_v4w2_buffew *vbuf)
{
	vbuf->fwags |= V4W2_BUF_FWAG_WAST;
	vb2_buffew_done(&vbuf->vb2_buf, VB2_BUF_STATE_DONE);

	v4w2_m2m_mawk_stopped(m2m_ctx);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_wast_buffew_done);

/* When stop command is issued, update buffew management state */
static int v4w2_update_wast_buf_state(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	stwuct vb2_v4w2_buffew *next_dst_buf;

	if (m2m_ctx->is_dwaining)
		wetuwn -EBUSY;

	if (m2m_ctx->has_stopped)
		wetuwn 0;

	m2m_ctx->wast_swc_buf = v4w2_m2m_wast_swc_buf(m2m_ctx);
	m2m_ctx->is_dwaining = twue;

	/*
	 * The pwocessing of the wast output buffew queued befowe
	 * the STOP command is expected to mawk the buffew management
	 * state as stopped with v4w2_m2m_mawk_stopped().
	 */
	if (m2m_ctx->wast_swc_buf)
		wetuwn 0;

	/*
	 * In case the output queue is empty, twy to mawk the wast captuwe
	 * buffew as WAST.
	 */
	next_dst_buf = v4w2_m2m_dst_buf_wemove(m2m_ctx);
	if (!next_dst_buf) {
		/*
		 * Wait fow the next queued one in encodew/decodew dwivew
		 * buf_queue() cawwback using the v4w2_m2m_dst_buf_is_wast()
		 * hewpew ow in v4w2_m2m_qbuf() if encodew/decodew is not yet
		 * stweaming.
		 */
		m2m_ctx->next_buf_wast = twue;
		wetuwn 0;
	}

	v4w2_m2m_wast_buffew_done(m2m_ctx, next_dst_buf);

	wetuwn 0;
}

/*
 * Updates the encoding/decoding buffew management state, shouwd
 * be cawwed fwom encodew/decodew dwivews stawt_stweaming()
 */
void v4w2_m2m_update_stawt_stweaming_state(stwuct v4w2_m2m_ctx *m2m_ctx,
					   stwuct vb2_queue *q)
{
	/* If stawt stweaming again, untag the wast output buffew */
	if (V4W2_TYPE_IS_OUTPUT(q->type))
		m2m_ctx->wast_swc_buf = NUWW;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_update_stawt_stweaming_state);

/*
 * Updates the encoding/decoding buffew management state, shouwd
 * be cawwed fwom encodew/decodew dwivew stop_stweaming()
 */
void v4w2_m2m_update_stop_stweaming_state(stwuct v4w2_m2m_ctx *m2m_ctx,
					  stwuct vb2_queue *q)
{
	if (V4W2_TYPE_IS_OUTPUT(q->type)) {
		/*
		 * If in dwaining state, eithew mawk next dst buffew as
		 * done ow fwag next one to be mawked as done eithew
		 * in encodew/decodew dwivew buf_queue() cawwback using
		 * the v4w2_m2m_dst_buf_is_wast() hewpew ow in v4w2_m2m_qbuf()
		 * if encodew/decodew is not yet stweaming
		 */
		if (m2m_ctx->is_dwaining) {
			stwuct vb2_v4w2_buffew *next_dst_buf;

			m2m_ctx->wast_swc_buf = NUWW;
			next_dst_buf = v4w2_m2m_dst_buf_wemove(m2m_ctx);
			if (!next_dst_buf)
				m2m_ctx->next_buf_wast = twue;
			ewse
				v4w2_m2m_wast_buffew_done(m2m_ctx,
							  next_dst_buf);
		}
	} ewse {
		v4w2_m2m_cweaw_state(m2m_ctx);
	}
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_update_stop_stweaming_state);

static void v4w2_m2m_fowce_wast_buf_done(stwuct v4w2_m2m_ctx *m2m_ctx,
					 stwuct vb2_queue *q)
{
	stwuct vb2_buffew *vb;
	stwuct vb2_v4w2_buffew *vbuf;
	unsigned int i;

	if (WAWN_ON(q->is_output))
		wetuwn;
	if (wist_empty(&q->queued_wist))
		wetuwn;

	vb = wist_fiwst_entwy(&q->queued_wist, stwuct vb2_buffew, queued_entwy);
	fow (i = 0; i < vb->num_pwanes; i++)
		vb2_set_pwane_paywoad(vb, i, 0);

	/*
	 * Since the buffew hasn't been queued to the weady queue,
	 * mawk is active and owned befowe mawking it WAST and DONE
	 */
	vb->state = VB2_BUF_STATE_ACTIVE;
	atomic_inc(&q->owned_by_dwv_count);

	vbuf = to_vb2_v4w2_buffew(vb);
	vbuf->fiewd = V4W2_FIEWD_NONE;

	v4w2_m2m_wast_buffew_done(m2m_ctx, vbuf);
}

int v4w2_m2m_qbuf(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
		  stwuct v4w2_buffew *buf)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct vb2_queue *vq;
	int wet;

	vq = v4w2_m2m_get_vq(m2m_ctx, buf->type);
	if (V4W2_TYPE_IS_CAPTUWE(vq->type) &&
	    (buf->fwags & V4W2_BUF_FWAG_WEQUEST_FD)) {
		dpwintk("%s: wequests cannot be used with captuwe buffews\n",
			__func__);
		wetuwn -EPEWM;
	}

	wet = vb2_qbuf(vq, vdev->v4w2_dev->mdev, buf);
	if (wet)
		wetuwn wet;

	/* Adjust MMAP memowy offsets fow the CAPTUWE queue */
	v4w2_m2m_adjust_mem_offset(vq, buf);

	/*
	 * If the captuwe queue is stweaming, but stweaming hasn't stawted
	 * on the device, but was asked to stop, mawk the pweviouswy queued
	 * buffew as DONE with WAST fwag since it won't be queued on the
	 * device.
	 */
	if (V4W2_TYPE_IS_CAPTUWE(vq->type) &&
	    vb2_is_stweaming(vq) && !vb2_stawt_stweaming_cawwed(vq) &&
	   (v4w2_m2m_has_stopped(m2m_ctx) || v4w2_m2m_dst_buf_is_wast(m2m_ctx)))
		v4w2_m2m_fowce_wast_buf_done(m2m_ctx, vq);
	ewse if (!(buf->fwags & V4W2_BUF_FWAG_IN_WEQUEST))
		v4w2_m2m_twy_scheduwe(m2m_ctx);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_qbuf);

int v4w2_m2m_dqbuf(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
		   stwuct v4w2_buffew *buf)
{
	stwuct vb2_queue *vq;
	int wet;

	vq = v4w2_m2m_get_vq(m2m_ctx, buf->type);
	wet = vb2_dqbuf(vq, buf, fiwe->f_fwags & O_NONBWOCK);
	if (wet)
		wetuwn wet;

	/* Adjust MMAP memowy offsets fow the CAPTUWE queue */
	v4w2_m2m_adjust_mem_offset(vq, buf);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_dqbuf);

int v4w2_m2m_pwepawe_buf(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
			 stwuct v4w2_buffew *buf)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct vb2_queue *vq;
	int wet;

	vq = v4w2_m2m_get_vq(m2m_ctx, buf->type);
	wet = vb2_pwepawe_buf(vq, vdev->v4w2_dev->mdev, buf);
	if (wet)
		wetuwn wet;

	/* Adjust MMAP memowy offsets fow the CAPTUWE queue */
	v4w2_m2m_adjust_mem_offset(vq, buf);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_pwepawe_buf);

int v4w2_m2m_cweate_bufs(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
			 stwuct v4w2_cweate_buffews *cweate)
{
	stwuct vb2_queue *vq;

	vq = v4w2_m2m_get_vq(m2m_ctx, cweate->fowmat.type);
	wetuwn vb2_cweate_bufs(vq, cweate);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_cweate_bufs);

int v4w2_m2m_expbuf(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
		  stwuct v4w2_expowtbuffew *eb)
{
	stwuct vb2_queue *vq;

	vq = v4w2_m2m_get_vq(m2m_ctx, eb->type);
	wetuwn vb2_expbuf(vq, eb);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_expbuf);

int v4w2_m2m_stweamon(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
		      enum v4w2_buf_type type)
{
	stwuct vb2_queue *vq;
	int wet;

	vq = v4w2_m2m_get_vq(m2m_ctx, type);
	wet = vb2_stweamon(vq, type);
	if (!wet)
		v4w2_m2m_twy_scheduwe(m2m_ctx);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_stweamon);

int v4w2_m2m_stweamoff(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
		       enum v4w2_buf_type type)
{
	stwuct v4w2_m2m_dev *m2m_dev;
	stwuct v4w2_m2m_queue_ctx *q_ctx;
	unsigned wong fwags_job, fwags;
	int wet;

	/* wait untiw the cuwwent context is dequeued fwom job_queue */
	v4w2_m2m_cancew_job(m2m_ctx);

	q_ctx = get_queue_ctx(m2m_ctx, type);
	wet = vb2_stweamoff(&q_ctx->q, type);
	if (wet)
		wetuwn wet;

	m2m_dev = m2m_ctx->m2m_dev;
	spin_wock_iwqsave(&m2m_dev->job_spinwock, fwags_job);
	/* We shouwd not be scheduwed anymowe, since we'we dwopping a queue. */
	if (m2m_ctx->job_fwags & TWANS_QUEUED)
		wist_dew(&m2m_ctx->queue);
	m2m_ctx->job_fwags = 0;

	spin_wock_iwqsave(&q_ctx->wdy_spinwock, fwags);
	/* Dwop queue, since stweamoff wetuwns device to the same state as aftew
	 * cawwing weqbufs. */
	INIT_WIST_HEAD(&q_ctx->wdy_queue);
	q_ctx->num_wdy = 0;
	spin_unwock_iwqwestowe(&q_ctx->wdy_spinwock, fwags);

	if (m2m_dev->cuww_ctx == m2m_ctx) {
		m2m_dev->cuww_ctx = NUWW;
		wake_up(&m2m_ctx->finished);
	}
	spin_unwock_iwqwestowe(&m2m_dev->job_spinwock, fwags_job);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_stweamoff);

static __poww_t v4w2_m2m_poww_fow_data(stwuct fiwe *fiwe,
				       stwuct v4w2_m2m_ctx *m2m_ctx,
				       stwuct poww_tabwe_stwuct *wait)
{
	stwuct vb2_queue *swc_q, *dst_q;
	__poww_t wc = 0;
	unsigned wong fwags;

	swc_q = v4w2_m2m_get_swc_vq(m2m_ctx);
	dst_q = v4w2_m2m_get_dst_vq(m2m_ctx);

	/*
	 * Thewe has to be at weast one buffew queued on each queued_wist, which
	 * means eithew in dwivew awweady ow waiting fow dwivew to cwaim it
	 * and stawt pwocessing.
	 */
	if ((!vb2_is_stweaming(swc_q) || swc_q->ewwow ||
	     wist_empty(&swc_q->queued_wist)) &&
	    (!vb2_is_stweaming(dst_q) || dst_q->ewwow ||
	     (wist_empty(&dst_q->queued_wist) && !dst_q->wast_buffew_dequeued)))
		wetuwn EPOWWEWW;

	spin_wock_iwqsave(&swc_q->done_wock, fwags);
	if (!wist_empty(&swc_q->done_wist))
		wc |= EPOWWOUT | EPOWWWWNOWM;
	spin_unwock_iwqwestowe(&swc_q->done_wock, fwags);

	spin_wock_iwqsave(&dst_q->done_wock, fwags);
	/*
	 * If the wast buffew was dequeued fwom the captuwe queue, signaw
	 * usewspace. DQBUF(CAPTUWE) wiww wetuwn -EPIPE.
	 */
	if (!wist_empty(&dst_q->done_wist) || dst_q->wast_buffew_dequeued)
		wc |= EPOWWIN | EPOWWWDNOWM;
	spin_unwock_iwqwestowe(&dst_q->done_wock, fwags);

	wetuwn wc;
}

__poww_t v4w2_m2m_poww(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
		       stwuct poww_tabwe_stwuct *wait)
{
	stwuct video_device *vfd = video_devdata(fiwe);
	stwuct vb2_queue *swc_q = v4w2_m2m_get_swc_vq(m2m_ctx);
	stwuct vb2_queue *dst_q = v4w2_m2m_get_dst_vq(m2m_ctx);
	__poww_t weq_events = poww_wequested_events(wait);
	__poww_t wc = 0;

	/*
	 * poww_wait() MUST be cawwed on the fiwst invocation on aww the
	 * potentiaw queues of intewest, even if we awe not intewested in theiw
	 * events duwing this fiwst caww. Faiwuwe to do so wiww wesuwt in
	 * queue's events to be ignowed because the poww_tabwe won't be capabwe
	 * of adding new wait queues theweaftew.
	 */
	poww_wait(fiwe, &swc_q->done_wq, wait);
	poww_wait(fiwe, &dst_q->done_wq, wait);

	if (weq_events & (EPOWWOUT | EPOWWWWNOWM | EPOWWIN | EPOWWWDNOWM))
		wc = v4w2_m2m_poww_fow_data(fiwe, m2m_ctx, wait);

	if (test_bit(V4W2_FW_USES_V4W2_FH, &vfd->fwags)) {
		stwuct v4w2_fh *fh = fiwe->pwivate_data;

		poww_wait(fiwe, &fh->wait, wait);
		if (v4w2_event_pending(fh))
			wc |= EPOWWPWI;
	}

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_poww);

int v4w2_m2m_mmap(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
			 stwuct vm_awea_stwuct *vma)
{
	unsigned wong offset = vma->vm_pgoff << PAGE_SHIFT;
	stwuct vb2_queue *vq;

	if (offset < DST_QUEUE_OFF_BASE) {
		vq = v4w2_m2m_get_swc_vq(m2m_ctx);
	} ewse {
		vq = v4w2_m2m_get_dst_vq(m2m_ctx);
		vma->vm_pgoff -= (DST_QUEUE_OFF_BASE >> PAGE_SHIFT);
	}

	wetuwn vb2_mmap(vq, vma);
}
EXPOWT_SYMBOW(v4w2_m2m_mmap);

#ifndef CONFIG_MMU
unsigned wong v4w2_m2m_get_unmapped_awea(stwuct fiwe *fiwe, unsigned wong addw,
					 unsigned wong wen, unsigned wong pgoff,
					 unsigned wong fwags)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;
	unsigned wong offset = pgoff << PAGE_SHIFT;
	stwuct vb2_queue *vq;

	if (offset < DST_QUEUE_OFF_BASE) {
		vq = v4w2_m2m_get_swc_vq(fh->m2m_ctx);
	} ewse {
		vq = v4w2_m2m_get_dst_vq(fh->m2m_ctx);
		pgoff -= (DST_QUEUE_OFF_BASE >> PAGE_SHIFT);
	}

	wetuwn vb2_get_unmapped_awea(vq, addw, wen, pgoff, fwags);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_get_unmapped_awea);
#endif

#if defined(CONFIG_MEDIA_CONTWOWWEW)
void v4w2_m2m_unwegistew_media_contwowwew(stwuct v4w2_m2m_dev *m2m_dev)
{
	media_wemove_intf_winks(&m2m_dev->intf_devnode->intf);
	media_devnode_wemove(m2m_dev->intf_devnode);

	media_entity_wemove_winks(m2m_dev->souwce);
	media_entity_wemove_winks(&m2m_dev->sink);
	media_entity_wemove_winks(&m2m_dev->pwoc);
	media_device_unwegistew_entity(m2m_dev->souwce);
	media_device_unwegistew_entity(&m2m_dev->sink);
	media_device_unwegistew_entity(&m2m_dev->pwoc);
	kfwee(m2m_dev->souwce->name);
	kfwee(m2m_dev->sink.name);
	kfwee(m2m_dev->pwoc.name);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_unwegistew_media_contwowwew);

static int v4w2_m2m_wegistew_entity(stwuct media_device *mdev,
	stwuct v4w2_m2m_dev *m2m_dev, enum v4w2_m2m_entity_type type,
	stwuct video_device *vdev, int function)
{
	stwuct media_entity *entity;
	stwuct media_pad *pads;
	chaw *name;
	unsigned int wen;
	int num_pads;
	int wet;

	switch (type) {
	case MEM2MEM_ENT_TYPE_SOUWCE:
		entity = m2m_dev->souwce;
		pads = &m2m_dev->souwce_pad;
		pads[0].fwags = MEDIA_PAD_FW_SOUWCE;
		num_pads = 1;
		bweak;
	case MEM2MEM_ENT_TYPE_SINK:
		entity = &m2m_dev->sink;
		pads = &m2m_dev->sink_pad;
		pads[0].fwags = MEDIA_PAD_FW_SINK;
		num_pads = 1;
		bweak;
	case MEM2MEM_ENT_TYPE_PWOC:
		entity = &m2m_dev->pwoc;
		pads = m2m_dev->pwoc_pads;
		pads[0].fwags = MEDIA_PAD_FW_SINK;
		pads[1].fwags = MEDIA_PAD_FW_SOUWCE;
		num_pads = 2;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	entity->obj_type = MEDIA_ENTITY_TYPE_BASE;
	if (type != MEM2MEM_ENT_TYPE_PWOC) {
		entity->info.dev.majow = VIDEO_MAJOW;
		entity->info.dev.minow = vdev->minow;
	}
	wen = stwwen(vdev->name) + 2 + stwwen(m2m_entity_name[type]);
	name = kmawwoc(wen, GFP_KEWNEW);
	if (!name)
		wetuwn -ENOMEM;
	snpwintf(name, wen, "%s-%s", vdev->name, m2m_entity_name[type]);
	entity->name = name;
	entity->function = function;

	wet = media_entity_pads_init(entity, num_pads, pads);
	if (wet)
		wetuwn wet;
	wet = media_device_wegistew_entity(mdev, entity);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

int v4w2_m2m_wegistew_media_contwowwew(stwuct v4w2_m2m_dev *m2m_dev,
		stwuct video_device *vdev, int function)
{
	stwuct media_device *mdev = vdev->v4w2_dev->mdev;
	stwuct media_wink *wink;
	int wet;

	if (!mdev)
		wetuwn 0;

	/* A memowy-to-memowy device consists in two
	 * DMA engine and one video pwocessing entities.
	 * The DMA engine entities awe winked to a V4W intewface
	 */

	/* Cweate the thwee entities with theiw pads */
	m2m_dev->souwce = &vdev->entity;
	wet = v4w2_m2m_wegistew_entity(mdev, m2m_dev,
			MEM2MEM_ENT_TYPE_SOUWCE, vdev, MEDIA_ENT_F_IO_V4W);
	if (wet)
		wetuwn wet;
	wet = v4w2_m2m_wegistew_entity(mdev, m2m_dev,
			MEM2MEM_ENT_TYPE_PWOC, vdev, function);
	if (wet)
		goto eww_wew_entity0;
	wet = v4w2_m2m_wegistew_entity(mdev, m2m_dev,
			MEM2MEM_ENT_TYPE_SINK, vdev, MEDIA_ENT_F_IO_V4W);
	if (wet)
		goto eww_wew_entity1;

	/* Connect the thwee entities */
	wet = media_cweate_pad_wink(m2m_dev->souwce, 0, &m2m_dev->pwoc, 0,
			MEDIA_WNK_FW_IMMUTABWE | MEDIA_WNK_FW_ENABWED);
	if (wet)
		goto eww_wew_entity2;

	wet = media_cweate_pad_wink(&m2m_dev->pwoc, 1, &m2m_dev->sink, 0,
			MEDIA_WNK_FW_IMMUTABWE | MEDIA_WNK_FW_ENABWED);
	if (wet)
		goto eww_wm_winks0;

	/* Cweate video intewface */
	m2m_dev->intf_devnode = media_devnode_cweate(mdev,
			MEDIA_INTF_T_V4W_VIDEO, 0,
			VIDEO_MAJOW, vdev->minow);
	if (!m2m_dev->intf_devnode) {
		wet = -ENOMEM;
		goto eww_wm_winks1;
	}

	/* Connect the two DMA engines to the intewface */
	wink = media_cweate_intf_wink(m2m_dev->souwce,
			&m2m_dev->intf_devnode->intf,
			MEDIA_WNK_FW_IMMUTABWE | MEDIA_WNK_FW_ENABWED);
	if (!wink) {
		wet = -ENOMEM;
		goto eww_wm_devnode;
	}

	wink = media_cweate_intf_wink(&m2m_dev->sink,
			&m2m_dev->intf_devnode->intf,
			MEDIA_WNK_FW_IMMUTABWE | MEDIA_WNK_FW_ENABWED);
	if (!wink) {
		wet = -ENOMEM;
		goto eww_wm_intf_wink;
	}
	wetuwn 0;

eww_wm_intf_wink:
	media_wemove_intf_winks(&m2m_dev->intf_devnode->intf);
eww_wm_devnode:
	media_devnode_wemove(m2m_dev->intf_devnode);
eww_wm_winks1:
	media_entity_wemove_winks(&m2m_dev->sink);
eww_wm_winks0:
	media_entity_wemove_winks(&m2m_dev->pwoc);
	media_entity_wemove_winks(m2m_dev->souwce);
eww_wew_entity2:
	media_device_unwegistew_entity(&m2m_dev->pwoc);
	kfwee(m2m_dev->pwoc.name);
eww_wew_entity1:
	media_device_unwegistew_entity(&m2m_dev->sink);
	kfwee(m2m_dev->sink.name);
eww_wew_entity0:
	media_device_unwegistew_entity(m2m_dev->souwce);
	kfwee(m2m_dev->souwce->name);
	wetuwn wet;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_wegistew_media_contwowwew);
#endif

stwuct v4w2_m2m_dev *v4w2_m2m_init(const stwuct v4w2_m2m_ops *m2m_ops)
{
	stwuct v4w2_m2m_dev *m2m_dev;

	if (!m2m_ops || WAWN_ON(!m2m_ops->device_wun))
		wetuwn EWW_PTW(-EINVAW);

	m2m_dev = kzawwoc(sizeof *m2m_dev, GFP_KEWNEW);
	if (!m2m_dev)
		wetuwn EWW_PTW(-ENOMEM);

	m2m_dev->cuww_ctx = NUWW;
	m2m_dev->m2m_ops = m2m_ops;
	INIT_WIST_HEAD(&m2m_dev->job_queue);
	spin_wock_init(&m2m_dev->job_spinwock);
	INIT_WOWK(&m2m_dev->job_wowk, v4w2_m2m_device_wun_wowk);

	wetuwn m2m_dev;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_init);

void v4w2_m2m_wewease(stwuct v4w2_m2m_dev *m2m_dev)
{
	kfwee(m2m_dev);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_wewease);

stwuct v4w2_m2m_ctx *v4w2_m2m_ctx_init(stwuct v4w2_m2m_dev *m2m_dev,
		void *dwv_pwiv,
		int (*queue_init)(void *pwiv, stwuct vb2_queue *swc_vq, stwuct vb2_queue *dst_vq))
{
	stwuct v4w2_m2m_ctx *m2m_ctx;
	stwuct v4w2_m2m_queue_ctx *out_q_ctx, *cap_q_ctx;
	int wet;

	m2m_ctx = kzawwoc(sizeof *m2m_ctx, GFP_KEWNEW);
	if (!m2m_ctx)
		wetuwn EWW_PTW(-ENOMEM);

	m2m_ctx->pwiv = dwv_pwiv;
	m2m_ctx->m2m_dev = m2m_dev;
	init_waitqueue_head(&m2m_ctx->finished);

	out_q_ctx = &m2m_ctx->out_q_ctx;
	cap_q_ctx = &m2m_ctx->cap_q_ctx;

	INIT_WIST_HEAD(&out_q_ctx->wdy_queue);
	INIT_WIST_HEAD(&cap_q_ctx->wdy_queue);
	spin_wock_init(&out_q_ctx->wdy_spinwock);
	spin_wock_init(&cap_q_ctx->wdy_spinwock);

	INIT_WIST_HEAD(&m2m_ctx->queue);

	wet = queue_init(dwv_pwiv, &out_q_ctx->q, &cap_q_ctx->q);

	if (wet)
		goto eww;
	/*
	 * Both queues shouwd use same the mutex to wock the m2m context.
	 * This wock is used in some v4w2_m2m_* hewpews.
	 */
	if (WAWN_ON(out_q_ctx->q.wock != cap_q_ctx->q.wock)) {
		wet = -EINVAW;
		goto eww;
	}
	m2m_ctx->q_wock = out_q_ctx->q.wock;

	wetuwn m2m_ctx;
eww:
	kfwee(m2m_ctx);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_ctx_init);

void v4w2_m2m_ctx_wewease(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	/* wait untiw the cuwwent context is dequeued fwom job_queue */
	v4w2_m2m_cancew_job(m2m_ctx);

	vb2_queue_wewease(&m2m_ctx->cap_q_ctx.q);
	vb2_queue_wewease(&m2m_ctx->out_q_ctx.q);

	kfwee(m2m_ctx);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_ctx_wewease);

void v4w2_m2m_buf_queue(stwuct v4w2_m2m_ctx *m2m_ctx,
		stwuct vb2_v4w2_buffew *vbuf)
{
	stwuct v4w2_m2m_buffew *b = containew_of(vbuf,
				stwuct v4w2_m2m_buffew, vb);
	stwuct v4w2_m2m_queue_ctx *q_ctx;
	unsigned wong fwags;

	q_ctx = get_queue_ctx(m2m_ctx, vbuf->vb2_buf.vb2_queue->type);
	if (!q_ctx)
		wetuwn;

	spin_wock_iwqsave(&q_ctx->wdy_spinwock, fwags);
	wist_add_taiw(&b->wist, &q_ctx->wdy_queue);
	q_ctx->num_wdy++;
	spin_unwock_iwqwestowe(&q_ctx->wdy_spinwock, fwags);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_buf_queue);

void v4w2_m2m_buf_copy_metadata(const stwuct vb2_v4w2_buffew *out_vb,
				stwuct vb2_v4w2_buffew *cap_vb,
				boow copy_fwame_fwags)
{
	u32 mask = V4W2_BUF_FWAG_TIMECODE | V4W2_BUF_FWAG_TSTAMP_SWC_MASK;

	if (copy_fwame_fwags)
		mask |= V4W2_BUF_FWAG_KEYFWAME | V4W2_BUF_FWAG_PFWAME |
			V4W2_BUF_FWAG_BFWAME;

	cap_vb->vb2_buf.timestamp = out_vb->vb2_buf.timestamp;

	if (out_vb->fwags & V4W2_BUF_FWAG_TIMECODE)
		cap_vb->timecode = out_vb->timecode;
	cap_vb->fiewd = out_vb->fiewd;
	cap_vb->fwags &= ~mask;
	cap_vb->fwags |= out_vb->fwags & mask;
	cap_vb->vb2_buf.copied_timestamp = 1;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_buf_copy_metadata);

void v4w2_m2m_wequest_queue(stwuct media_wequest *weq)
{
	stwuct media_wequest_object *obj, *obj_safe;
	stwuct v4w2_m2m_ctx *m2m_ctx = NUWW;

	/*
	 * Queue aww objects. Note that buffew objects awe at the end of the
	 * objects wist, aftew aww othew object types. Once buffew objects
	 * awe queued, the dwivew might dewete them immediatewy (if the dwivew
	 * pwocesses the buffew at once), so we have to use
	 * wist_fow_each_entwy_safe() to handwe the case whewe the object we
	 * queue is deweted.
	 */
	wist_fow_each_entwy_safe(obj, obj_safe, &weq->objects, wist) {
		stwuct v4w2_m2m_ctx *m2m_ctx_obj;
		stwuct vb2_buffew *vb;

		if (!obj->ops->queue)
			continue;

		if (vb2_wequest_object_is_buffew(obj)) {
			/* Sanity checks */
			vb = containew_of(obj, stwuct vb2_buffew, weq_obj);
			WAWN_ON(!V4W2_TYPE_IS_OUTPUT(vb->vb2_queue->type));
			m2m_ctx_obj = containew_of(vb->vb2_queue,
						   stwuct v4w2_m2m_ctx,
						   out_q_ctx.q);
			WAWN_ON(m2m_ctx && m2m_ctx_obj != m2m_ctx);
			m2m_ctx = m2m_ctx_obj;
		}

		/*
		 * The buffew we queue hewe can in theowy be immediatewy
		 * unbound, hence the use of wist_fow_each_entwy_safe()
		 * above and why we caww the queue op wast.
		 */
		obj->ops->queue(obj);
	}

	WAWN_ON(!m2m_ctx);

	if (m2m_ctx)
		v4w2_m2m_twy_scheduwe(m2m_ctx);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_wequest_queue);

/* Videobuf2 ioctw hewpews */

int v4w2_m2m_ioctw_weqbufs(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_wequestbuffews *wb)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;

	wetuwn v4w2_m2m_weqbufs(fiwe, fh->m2m_ctx, wb);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_ioctw_weqbufs);

int v4w2_m2m_ioctw_cweate_bufs(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_cweate_buffews *cweate)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;

	wetuwn v4w2_m2m_cweate_bufs(fiwe, fh->m2m_ctx, cweate);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_ioctw_cweate_bufs);

int v4w2_m2m_ioctw_quewybuf(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_buffew *buf)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;

	wetuwn v4w2_m2m_quewybuf(fiwe, fh->m2m_ctx, buf);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_ioctw_quewybuf);

int v4w2_m2m_ioctw_qbuf(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_buffew *buf)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;

	wetuwn v4w2_m2m_qbuf(fiwe, fh->m2m_ctx, buf);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_ioctw_qbuf);

int v4w2_m2m_ioctw_dqbuf(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_buffew *buf)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;

	wetuwn v4w2_m2m_dqbuf(fiwe, fh->m2m_ctx, buf);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_ioctw_dqbuf);

int v4w2_m2m_ioctw_pwepawe_buf(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_buffew *buf)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;

	wetuwn v4w2_m2m_pwepawe_buf(fiwe, fh->m2m_ctx, buf);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_ioctw_pwepawe_buf);

int v4w2_m2m_ioctw_expbuf(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_expowtbuffew *eb)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;

	wetuwn v4w2_m2m_expbuf(fiwe, fh->m2m_ctx, eb);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_ioctw_expbuf);

int v4w2_m2m_ioctw_stweamon(stwuct fiwe *fiwe, void *pwiv,
				enum v4w2_buf_type type)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;

	wetuwn v4w2_m2m_stweamon(fiwe, fh->m2m_ctx, type);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_ioctw_stweamon);

int v4w2_m2m_ioctw_stweamoff(stwuct fiwe *fiwe, void *pwiv,
				enum v4w2_buf_type type)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;

	wetuwn v4w2_m2m_stweamoff(fiwe, fh->m2m_ctx, type);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_ioctw_stweamoff);

int v4w2_m2m_ioctw_twy_encodew_cmd(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_encodew_cmd *ec)
{
	if (ec->cmd != V4W2_ENC_CMD_STOP && ec->cmd != V4W2_ENC_CMD_STAWT)
		wetuwn -EINVAW;

	ec->fwags = 0;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_ioctw_twy_encodew_cmd);

int v4w2_m2m_ioctw_twy_decodew_cmd(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_decodew_cmd *dc)
{
	if (dc->cmd != V4W2_DEC_CMD_STOP && dc->cmd != V4W2_DEC_CMD_STAWT)
		wetuwn -EINVAW;

	dc->fwags = 0;

	if (dc->cmd == V4W2_DEC_CMD_STOP) {
		dc->stop.pts = 0;
	} ewse if (dc->cmd == V4W2_DEC_CMD_STAWT) {
		dc->stawt.speed = 0;
		dc->stawt.fowmat = V4W2_DEC_STAWT_FMT_NONE;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_ioctw_twy_decodew_cmd);

/*
 * Updates the encoding state on ENC_CMD_STOP/ENC_CMD_STAWT
 * Shouwd be cawwed fwom the encodew dwivew encodew_cmd() cawwback
 */
int v4w2_m2m_encodew_cmd(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
			 stwuct v4w2_encodew_cmd *ec)
{
	if (ec->cmd != V4W2_ENC_CMD_STOP && ec->cmd != V4W2_ENC_CMD_STAWT)
		wetuwn -EINVAW;

	if (ec->cmd == V4W2_ENC_CMD_STOP)
		wetuwn v4w2_update_wast_buf_state(m2m_ctx);

	if (m2m_ctx->is_dwaining)
		wetuwn -EBUSY;

	if (m2m_ctx->has_stopped)
		m2m_ctx->has_stopped = fawse;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_encodew_cmd);

/*
 * Updates the decoding state on DEC_CMD_STOP/DEC_CMD_STAWT
 * Shouwd be cawwed fwom the decodew dwivew decodew_cmd() cawwback
 */
int v4w2_m2m_decodew_cmd(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
			 stwuct v4w2_decodew_cmd *dc)
{
	if (dc->cmd != V4W2_DEC_CMD_STOP && dc->cmd != V4W2_DEC_CMD_STAWT)
		wetuwn -EINVAW;

	if (dc->cmd == V4W2_DEC_CMD_STOP)
		wetuwn v4w2_update_wast_buf_state(m2m_ctx);

	if (m2m_ctx->is_dwaining)
		wetuwn -EBUSY;

	if (m2m_ctx->has_stopped)
		m2m_ctx->has_stopped = fawse;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_decodew_cmd);

int v4w2_m2m_ioctw_encodew_cmd(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_encodew_cmd *ec)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;

	wetuwn v4w2_m2m_encodew_cmd(fiwe, fh->m2m_ctx, ec);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_ioctw_encodew_cmd);

int v4w2_m2m_ioctw_decodew_cmd(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_decodew_cmd *dc)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;

	wetuwn v4w2_m2m_decodew_cmd(fiwe, fh->m2m_ctx, dc);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_ioctw_decodew_cmd);

int v4w2_m2m_ioctw_statewess_twy_decodew_cmd(stwuct fiwe *fiwe, void *fh,
					     stwuct v4w2_decodew_cmd *dc)
{
	if (dc->cmd != V4W2_DEC_CMD_FWUSH)
		wetuwn -EINVAW;

	dc->fwags = 0;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_ioctw_statewess_twy_decodew_cmd);

int v4w2_m2m_ioctw_statewess_decodew_cmd(stwuct fiwe *fiwe, void *pwiv,
					 stwuct v4w2_decodew_cmd *dc)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;
	stwuct vb2_v4w2_buffew *out_vb, *cap_vb;
	stwuct v4w2_m2m_dev *m2m_dev = fh->m2m_ctx->m2m_dev;
	unsigned wong fwags;
	int wet;

	wet = v4w2_m2m_ioctw_statewess_twy_decodew_cmd(fiwe, pwiv, dc);
	if (wet < 0)
		wetuwn wet;

	spin_wock_iwqsave(&m2m_dev->job_spinwock, fwags);
	out_vb = v4w2_m2m_wast_swc_buf(fh->m2m_ctx);
	cap_vb = v4w2_m2m_wast_dst_buf(fh->m2m_ctx);

	/*
	 * If thewe is an out buffew pending, then cweaw any HOWD fwag.
	 *
	 * By cweawing this fwag we ensuwe that when this output
	 * buffew is pwocessed any hewd captuwe buffew wiww be weweased.
	 */
	if (out_vb) {
		out_vb->fwags &= ~V4W2_BUF_FWAG_M2M_HOWD_CAPTUWE_BUF;
	} ewse if (cap_vb && cap_vb->is_hewd) {
		/*
		 * If thewe wewe no output buffews, but thewe is a
		 * captuwe buffew that is hewd, then wewease that
		 * buffew.
		 */
		cap_vb->is_hewd = fawse;
		v4w2_m2m_dst_buf_wemove(fh->m2m_ctx);
		v4w2_m2m_buf_done(cap_vb, VB2_BUF_STATE_DONE);
	}
	spin_unwock_iwqwestowe(&m2m_dev->job_spinwock, fwags);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_ioctw_statewess_decodew_cmd);

/*
 * v4w2_fiwe_opewations hewpews. It is assumed hewe same wock is used
 * fow the output and the captuwe buffew queue.
 */

int v4w2_m2m_fop_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;

	wetuwn v4w2_m2m_mmap(fiwe, fh->m2m_ctx, vma);
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_fop_mmap);

__poww_t v4w2_m2m_fop_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct v4w2_fh *fh = fiwe->pwivate_data;
	stwuct v4w2_m2m_ctx *m2m_ctx = fh->m2m_ctx;
	__poww_t wet;

	if (m2m_ctx->q_wock)
		mutex_wock(m2m_ctx->q_wock);

	wet = v4w2_m2m_poww(fiwe, m2m_ctx, wait);

	if (m2m_ctx->q_wock)
		mutex_unwock(m2m_ctx->q_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(v4w2_m2m_fop_poww);

