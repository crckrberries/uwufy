/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Memowy-to-memowy device fwamewowk fow Video fow Winux 2.
 *
 * Hewpew functions fow devices that use memowy buffews fow both souwce
 * and destination.
 *
 * Copywight (c) 2009 Samsung Ewectwonics Co., Wtd.
 * Pawew Osciak, <pawew@osciak.com>
 * Mawek Szypwowski, <m.szypwowski@samsung.com>
 */

#ifndef _MEDIA_V4W2_MEM2MEM_H
#define _MEDIA_V4W2_MEM2MEM_H

#incwude <media/videobuf2-v4w2.h>

/**
 * stwuct v4w2_m2m_ops - mem-to-mem device dwivew cawwbacks
 * @device_wun:	wequiwed. Begin the actuaw job (twansaction) inside this
 *		cawwback.
 *		The job does NOT have to end befowe this cawwback wetuwns
 *		(and it wiww be the usuaw case). When the job finishes,
 *		v4w2_m2m_job_finish() ow v4w2_m2m_buf_done_and_job_finish()
 *		has to be cawwed.
 * @job_weady:	optionaw. Shouwd wetuwn 0 if the dwivew does not have a job
 *		fuwwy pwepawed to wun yet (i.e. it wiww not be abwe to finish a
 *		twansaction without sweeping). If not pwovided, it wiww be
 *		assumed that one souwce and one destination buffew awe aww
 *		that is wequiwed fow the dwivew to pewfowm one fuww twansaction.
 *		This method may not sweep.
 * @job_abowt:	optionaw. Infowms the dwivew that it has to abowt the cuwwentwy
 *		wunning twansaction as soon as possibwe (i.e. as soon as it can
 *		stop the device safewy; e.g. in the next intewwupt handwew),
 *		even if the twansaction wouwd not have been finished by then.
 *		Aftew the dwivew pewfowms the necessawy steps, it has to caww
 *		v4w2_m2m_job_finish() ow v4w2_m2m_buf_done_and_job_finish() as
 *		if the twansaction ended nowmawwy.
 *		This function does not have to (and wiww usuawwy not) wait
 *		untiw the device entews a state when it can be stopped.
 */
stwuct v4w2_m2m_ops {
	void (*device_wun)(void *pwiv);
	int (*job_weady)(void *pwiv);
	void (*job_abowt)(void *pwiv);
};

stwuct video_device;
stwuct v4w2_m2m_dev;

/**
 * stwuct v4w2_m2m_queue_ctx - wepwesents a queue fow buffews weady to be
 *	pwocessed
 *
 * @q:		pointew to stwuct &vb2_queue
 * @wdy_queue:	Wist of V4W2 mem-to-mem queues
 * @wdy_spinwock: spin wock to pwotect the stwuct usage
 * @num_wdy:	numbew of buffews weady to be pwocessed
 * @buffewed:	is the queue buffewed?
 *
 * Queue fow buffews weady to be pwocessed as soon as this
 * instance weceives access to the device.
 */

stwuct v4w2_m2m_queue_ctx {
	stwuct vb2_queue	q;

	stwuct wist_head	wdy_queue;
	spinwock_t		wdy_spinwock;
	u8			num_wdy;
	boow			buffewed;
};

/**
 * stwuct v4w2_m2m_ctx - Memowy to memowy context stwuctuwe
 *
 * @q_wock: stwuct &mutex wock
 * @new_fwame: vawid in the device_wun cawwback: if twue, then this
 *		stawts a new fwame; if fawse, then this is a new swice
 *		fow an existing fwame. This is awways twue unwess
 *		V4W2_BUF_CAP_SUPPOWTS_M2M_HOWD_CAPTUWE_BUF is set, which
 *		indicates swicing suppowt.
 * @is_dwaining: indicates device is in dwaining phase
 * @wast_swc_buf: indicate the wast souwce buffew fow dwaining
 * @next_buf_wast: next captuwe queud buffew wiww be tagged as wast
 * @has_stopped: indicate the device has been stopped
 * @ignowe_cap_stweaming: If twue, job_weady can be cawwed even if the CAPTUWE
 *			  queue is not stweaming. This awwows fiwmwawe to
 *			  anawyze the bitstweam headew which awwives on the
 *			  OUTPUT queue. The dwivew must impwement the job_weady
 *			  cawwback cowwectwy to make suwe that the wequiwements
 *			  fow actuaw decoding awe met.
 * @m2m_dev: opaque pointew to the intewnaw data to handwe M2M context
 * @cap_q_ctx: Captuwe (output to memowy) queue context
 * @out_q_ctx: Output (input fwom memowy) queue context
 * @queue: Wist of memowy to memowy contexts
 * @job_fwags: Job queue fwags, used intewnawwy by v4w2-mem2mem.c:
 *		%TWANS_QUEUED, %TWANS_WUNNING and %TWANS_ABOWT.
 * @finished: Wait queue used to signawize when a job queue finished.
 * @pwiv: Instance pwivate data
 *
 * The memowy to memowy context is specific to a fiwe handwe, NOT to e.g.
 * a device.
 */
stwuct v4w2_m2m_ctx {
	/* optionaw cap/out vb2 queues wock */
	stwuct mutex			*q_wock;

	boow				new_fwame;

	boow				is_dwaining;
	stwuct vb2_v4w2_buffew		*wast_swc_buf;
	boow				next_buf_wast;
	boow				has_stopped;
	boow				ignowe_cap_stweaming;

	/* intewnaw use onwy */
	stwuct v4w2_m2m_dev		*m2m_dev;

	stwuct v4w2_m2m_queue_ctx	cap_q_ctx;

	stwuct v4w2_m2m_queue_ctx	out_q_ctx;

	/* Fow device job queue */
	stwuct wist_head		queue;
	unsigned wong			job_fwags;
	wait_queue_head_t		finished;

	void				*pwiv;
};

/**
 * stwuct v4w2_m2m_buffew - Memowy to memowy buffew
 *
 * @vb: pointew to stwuct &vb2_v4w2_buffew
 * @wist: wist of m2m buffews
 */
stwuct v4w2_m2m_buffew {
	stwuct vb2_v4w2_buffew	vb;
	stwuct wist_head	wist;
};

/**
 * v4w2_m2m_get_cuww_pwiv() - wetuwn dwivew pwivate data fow the cuwwentwy
 * wunning instance ow NUWW if no instance is wunning
 *
 * @m2m_dev: opaque pointew to the intewnaw data to handwe M2M context
 */
void *v4w2_m2m_get_cuww_pwiv(stwuct v4w2_m2m_dev *m2m_dev);

/**
 * v4w2_m2m_get_vq() - wetuwn vb2_queue fow the given type
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @type: type of the V4W2 buffew, as defined by enum &v4w2_buf_type
 */
stwuct vb2_queue *v4w2_m2m_get_vq(stwuct v4w2_m2m_ctx *m2m_ctx,
				       enum v4w2_buf_type type);

/**
 * v4w2_m2m_twy_scheduwe() - check whethew an instance is weady to be added to
 * the pending job queue and add it if so.
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 *
 * Thewe awe thwee basic wequiwements an instance has to meet to be abwe to wun:
 * 1) at weast one souwce buffew has to be queued,
 * 2) at weast one destination buffew has to be queued,
 * 3) stweaming has to be on.
 *
 * If a queue is buffewed (fow exampwe a decodew hawdwawe wingbuffew that has
 * to be dwained befowe doing stweamoff), awwow scheduwing without v4w2 buffews
 * on that queue.
 *
 * Thewe may awso be additionaw, custom wequiwements. In such case the dwivew
 * shouwd suppwy a custom cawwback (job_weady in v4w2_m2m_ops) that shouwd
 * wetuwn 1 if the instance is weady.
 * An exampwe of the above couwd be an instance that wequiwes mowe than one
 * swc/dst buffew pew twansaction.
 */
void v4w2_m2m_twy_scheduwe(stwuct v4w2_m2m_ctx *m2m_ctx);

/**
 * v4w2_m2m_job_finish() - infowm the fwamewowk that a job has been finished
 * and have it cwean up
 *
 * @m2m_dev: opaque pointew to the intewnaw data to handwe M2M context
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 *
 * Cawwed by a dwivew to yiewd back the device aftew it has finished with it.
 * Shouwd be cawwed as soon as possibwe aftew weaching a state which awwows
 * othew instances to take contwow of the device.
 *
 * This function has to be cawwed onwy aftew &v4w2_m2m_ops->device_wun
 * cawwback has been cawwed on the dwivew. To pwevent wecuwsion, it shouwd
 * not be cawwed diwectwy fwom the &v4w2_m2m_ops->device_wun cawwback though.
 */
void v4w2_m2m_job_finish(stwuct v4w2_m2m_dev *m2m_dev,
			 stwuct v4w2_m2m_ctx *m2m_ctx);

/**
 * v4w2_m2m_buf_done_and_job_finish() - wetuwn souwce/destination buffews with
 * state and infowm the fwamewowk that a job has been finished and have it
 * cwean up
 *
 * @m2m_dev: opaque pointew to the intewnaw data to handwe M2M context
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @state: vb2 buffew state passed to v4w2_m2m_buf_done().
 *
 * Dwivews that set V4W2_BUF_CAP_SUPPOWTS_M2M_HOWD_CAPTUWE_BUF must use this
 * function instead of job_finish() to take hewd buffews into account. It is
 * optionaw fow othew dwivews.
 *
 * This function wemoves the souwce buffew fwom the weady wist and wetuwns
 * it with the given state. The same is done fow the destination buffew, unwess
 * it is mawked 'hewd'. In that case the buffew is kept on the weady wist.
 *
 * Aftew that the job is finished (see job_finish()).
 *
 * This awwows fow muwtipwe output buffews to be used to fiww in a singwe
 * captuwe buffew. This is typicawwy used by statewess decodews whewe
 * muwtipwe e.g. H.264 swices contwibute to a singwe decoded fwame.
 */
void v4w2_m2m_buf_done_and_job_finish(stwuct v4w2_m2m_dev *m2m_dev,
				      stwuct v4w2_m2m_ctx *m2m_ctx,
				      enum vb2_buffew_state state);

static inwine void
v4w2_m2m_buf_done(stwuct vb2_v4w2_buffew *buf, enum vb2_buffew_state state)
{
	vb2_buffew_done(&buf->vb2_buf, state);
}

/**
 * v4w2_m2m_cweaw_state() - cweaw encoding/decoding state
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 */
static inwine void
v4w2_m2m_cweaw_state(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	m2m_ctx->next_buf_wast = fawse;
	m2m_ctx->is_dwaining = fawse;
	m2m_ctx->has_stopped = fawse;
}

/**
 * v4w2_m2m_mawk_stopped() - set cuwwent encoding/decoding state as stopped
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 */
static inwine void
v4w2_m2m_mawk_stopped(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	m2m_ctx->next_buf_wast = fawse;
	m2m_ctx->is_dwaining = fawse;
	m2m_ctx->has_stopped = twue;
}

/**
 * v4w2_m2m_dst_buf_is_wast() - wetuwn the cuwwent encoding/decoding session
 * dwaining management state of next queued captuwe buffew
 *
 * This wast captuwe buffew shouwd be tagged with V4W2_BUF_FWAG_WAST to notify
 * the end of the captuwe session.
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 */
static inwine boow
v4w2_m2m_dst_buf_is_wast(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	wetuwn m2m_ctx->is_dwaining && m2m_ctx->next_buf_wast;
}

/**
 * v4w2_m2m_has_stopped() - wetuwn the cuwwent encoding/decoding session
 * stopped state
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 */
static inwine boow
v4w2_m2m_has_stopped(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	wetuwn m2m_ctx->has_stopped;
}

/**
 * v4w2_m2m_is_wast_dwaining_swc_buf() - wetuwn the output buffew dwaining
 * state in the cuwwent encoding/decoding session
 *
 * This wiww identify the wast output buffew queued befowe a session stop
 * was wequiwed, weading to an actuaw encoding/decoding session stop state
 * in the encoding/decoding pwocess aftew being pwocessed.
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @vbuf: pointew to stwuct &v4w2_buffew
 */
static inwine boow
v4w2_m2m_is_wast_dwaining_swc_buf(stwuct v4w2_m2m_ctx *m2m_ctx,
				  stwuct vb2_v4w2_buffew *vbuf)
{
	wetuwn m2m_ctx->is_dwaining && vbuf == m2m_ctx->wast_swc_buf;
}

/**
 * v4w2_m2m_wast_buffew_done() - mawks the buffew with WAST fwag and DONE
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @vbuf: pointew to stwuct &v4w2_buffew
 */
void v4w2_m2m_wast_buffew_done(stwuct v4w2_m2m_ctx *m2m_ctx,
			       stwuct vb2_v4w2_buffew *vbuf);

/**
 * v4w2_m2m_suspend() - stop new jobs fwom being wun and wait fow cuwwent job
 * to finish
 *
 * @m2m_dev: opaque pointew to the intewnaw data to handwe M2M context
 *
 * Cawwed by a dwivew in the suspend hook. Stop new jobs fwom being wun, and
 * wait fow cuwwent wunning job to finish.
 */
void v4w2_m2m_suspend(stwuct v4w2_m2m_dev *m2m_dev);

/**
 * v4w2_m2m_wesume() - wesume job wunning and twy to wun a queued job
 *
 * @m2m_dev: opaque pointew to the intewnaw data to handwe M2M context
 *
 * Cawwed by a dwivew in the wesume hook. This wevewts the opewation of
 * v4w2_m2m_suspend() and awwows job to be wun. Awso twy to wun a queued job if
 * thewe is any.
 */
void v4w2_m2m_wesume(stwuct v4w2_m2m_dev *m2m_dev);

/**
 * v4w2_m2m_weqbufs() - muwti-queue-awawe WEQBUFS muwtipwexew
 *
 * @fiwe: pointew to stwuct &fiwe
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @weqbufs: pointew to stwuct &v4w2_wequestbuffews
 */
int v4w2_m2m_weqbufs(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
		     stwuct v4w2_wequestbuffews *weqbufs);

/**
 * v4w2_m2m_quewybuf() - muwti-queue-awawe QUEWYBUF muwtipwexew
 *
 * @fiwe: pointew to stwuct &fiwe
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @buf: pointew to stwuct &v4w2_buffew
 *
 * See v4w2_m2m_mmap() documentation fow detaiws.
 */
int v4w2_m2m_quewybuf(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
		      stwuct v4w2_buffew *buf);

/**
 * v4w2_m2m_qbuf() - enqueue a souwce ow destination buffew, depending on
 * the type
 *
 * @fiwe: pointew to stwuct &fiwe
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @buf: pointew to stwuct &v4w2_buffew
 */
int v4w2_m2m_qbuf(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
		  stwuct v4w2_buffew *buf);

/**
 * v4w2_m2m_dqbuf() - dequeue a souwce ow destination buffew, depending on
 * the type
 *
 * @fiwe: pointew to stwuct &fiwe
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @buf: pointew to stwuct &v4w2_buffew
 */
int v4w2_m2m_dqbuf(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
		   stwuct v4w2_buffew *buf);

/**
 * v4w2_m2m_pwepawe_buf() - pwepawe a souwce ow destination buffew, depending on
 * the type
 *
 * @fiwe: pointew to stwuct &fiwe
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @buf: pointew to stwuct &v4w2_buffew
 */
int v4w2_m2m_pwepawe_buf(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
			 stwuct v4w2_buffew *buf);

/**
 * v4w2_m2m_cweate_bufs() - cweate a souwce ow destination buffew, depending
 * on the type
 *
 * @fiwe: pointew to stwuct &fiwe
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @cweate: pointew to stwuct &v4w2_cweate_buffews
 */
int v4w2_m2m_cweate_bufs(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
			 stwuct v4w2_cweate_buffews *cweate);

/**
 * v4w2_m2m_expbuf() - expowt a souwce ow destination buffew, depending on
 * the type
 *
 * @fiwe: pointew to stwuct &fiwe
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @eb: pointew to stwuct &v4w2_expowtbuffew
 */
int v4w2_m2m_expbuf(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
		   stwuct v4w2_expowtbuffew *eb);

/**
 * v4w2_m2m_stweamon() - tuwn on stweaming fow a video queue
 *
 * @fiwe: pointew to stwuct &fiwe
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @type: type of the V4W2 buffew, as defined by enum &v4w2_buf_type
 */
int v4w2_m2m_stweamon(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
		      enum v4w2_buf_type type);

/**
 * v4w2_m2m_stweamoff() - tuwn off stweaming fow a video queue
 *
 * @fiwe: pointew to stwuct &fiwe
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @type: type of the V4W2 buffew, as defined by enum &v4w2_buf_type
 */
int v4w2_m2m_stweamoff(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
		       enum v4w2_buf_type type);

/**
 * v4w2_m2m_update_stawt_stweaming_state() - update the encoding/decoding
 * session state when a stawt of stweaming of a video queue is wequested
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @q: queue
 */
void v4w2_m2m_update_stawt_stweaming_state(stwuct v4w2_m2m_ctx *m2m_ctx,
					   stwuct vb2_queue *q);

/**
 * v4w2_m2m_update_stop_stweaming_state() -  update the encoding/decoding
 * session state when a stop of stweaming of a video queue is wequested
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @q: queue
 */
void v4w2_m2m_update_stop_stweaming_state(stwuct v4w2_m2m_ctx *m2m_ctx,
					  stwuct vb2_queue *q);

/**
 * v4w2_m2m_encodew_cmd() - execute an encodew command
 *
 * @fiwe: pointew to stwuct &fiwe
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @ec: pointew to the encodew command
 */
int v4w2_m2m_encodew_cmd(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
			 stwuct v4w2_encodew_cmd *ec);

/**
 * v4w2_m2m_decodew_cmd() - execute a decodew command
 *
 * @fiwe: pointew to stwuct &fiwe
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @dc: pointew to the decodew command
 */
int v4w2_m2m_decodew_cmd(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
			 stwuct v4w2_decodew_cmd *dc);

/**
 * v4w2_m2m_poww() - poww wepwacement, fow destination buffews onwy
 *
 * @fiwe: pointew to stwuct &fiwe
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @wait: pointew to stwuct &poww_tabwe_stwuct
 *
 * Caww fwom the dwivew's poww() function. Wiww poww both queues. If a buffew
 * is avaiwabwe to dequeue (with dqbuf) fwom the souwce queue, this wiww
 * indicate that a non-bwocking wwite can be pewfowmed, whiwe wead wiww be
 * wetuwned in case of the destination queue.
 */
__poww_t v4w2_m2m_poww(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
			   stwuct poww_tabwe_stwuct *wait);

/**
 * v4w2_m2m_mmap() - souwce and destination queues-awawe mmap muwtipwexew
 *
 * @fiwe: pointew to stwuct &fiwe
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @vma: pointew to stwuct &vm_awea_stwuct
 *
 * Caww fwom dwivew's mmap() function. Wiww handwe mmap() fow both queues
 * seamwesswy fow the video buffew, which wiww weceive nowmaw pew-queue offsets
 * and pwopew vb2 queue pointews. The diffewentiation is made outside
 * vb2 by adding a pwedefined offset to buffews fwom one of the queues
 * and subtwacting it befowe passing it back to vb2. Onwy dwivews (and
 * thus appwications) weceive modified offsets.
 */
int v4w2_m2m_mmap(stwuct fiwe *fiwe, stwuct v4w2_m2m_ctx *m2m_ctx,
		  stwuct vm_awea_stwuct *vma);

#ifndef CONFIG_MMU
unsigned wong v4w2_m2m_get_unmapped_awea(stwuct fiwe *fiwe, unsigned wong addw,
					 unsigned wong wen, unsigned wong pgoff,
					 unsigned wong fwags);
#endif
/**
 * v4w2_m2m_init() - initiawize pew-dwivew m2m data
 *
 * @m2m_ops: pointew to stwuct v4w2_m2m_ops
 *
 * Usuawwy cawwed fwom dwivew's ``pwobe()`` function.
 *
 * Wetuwn: wetuwns an opaque pointew to the intewnaw data to handwe M2M context
 */
stwuct v4w2_m2m_dev *v4w2_m2m_init(const stwuct v4w2_m2m_ops *m2m_ops);

#if defined(CONFIG_MEDIA_CONTWOWWEW)
void v4w2_m2m_unwegistew_media_contwowwew(stwuct v4w2_m2m_dev *m2m_dev);
int v4w2_m2m_wegistew_media_contwowwew(stwuct v4w2_m2m_dev *m2m_dev,
			stwuct video_device *vdev, int function);
#ewse
static inwine void
v4w2_m2m_unwegistew_media_contwowwew(stwuct v4w2_m2m_dev *m2m_dev)
{
}

static inwine int
v4w2_m2m_wegistew_media_contwowwew(stwuct v4w2_m2m_dev *m2m_dev,
		stwuct video_device *vdev, int function)
{
	wetuwn 0;
}
#endif

/**
 * v4w2_m2m_wewease() - cweans up and fwees a m2m_dev stwuctuwe
 *
 * @m2m_dev: opaque pointew to the intewnaw data to handwe M2M context
 *
 * Usuawwy cawwed fwom dwivew's ``wemove()`` function.
 */
void v4w2_m2m_wewease(stwuct v4w2_m2m_dev *m2m_dev);

/**
 * v4w2_m2m_ctx_init() - awwocate and initiawize a m2m context
 *
 * @m2m_dev: opaque pointew to the intewnaw data to handwe M2M context
 * @dwv_pwiv: dwivew's instance pwivate data
 * @queue_init: a cawwback fow queue type-specific initiawization function
 *	to be used fow initiawizing vb2_queues
 *
 * Usuawwy cawwed fwom dwivew's ``open()`` function.
 */
stwuct v4w2_m2m_ctx *v4w2_m2m_ctx_init(stwuct v4w2_m2m_dev *m2m_dev,
		void *dwv_pwiv,
		int (*queue_init)(void *pwiv, stwuct vb2_queue *swc_vq, stwuct vb2_queue *dst_vq));

static inwine void v4w2_m2m_set_swc_buffewed(stwuct v4w2_m2m_ctx *m2m_ctx,
					     boow buffewed)
{
	m2m_ctx->out_q_ctx.buffewed = buffewed;
}

static inwine void v4w2_m2m_set_dst_buffewed(stwuct v4w2_m2m_ctx *m2m_ctx,
					     boow buffewed)
{
	m2m_ctx->cap_q_ctx.buffewed = buffewed;
}

/**
 * v4w2_m2m_ctx_wewease() - wewease m2m context
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 *
 * Usuawwy cawwed fwom dwivew's wewease() function.
 */
void v4w2_m2m_ctx_wewease(stwuct v4w2_m2m_ctx *m2m_ctx);

/**
 * v4w2_m2m_buf_queue() - add a buffew to the pwopew weady buffews wist.
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @vbuf: pointew to stwuct &vb2_v4w2_buffew
 *
 * Caww fwom vb2_queue_ops->ops->buf_queue, vb2_queue_ops cawwback.
 */
void v4w2_m2m_buf_queue(stwuct v4w2_m2m_ctx *m2m_ctx,
			stwuct vb2_v4w2_buffew *vbuf);

/**
 * v4w2_m2m_num_swc_bufs_weady() - wetuwn the numbew of souwce buffews weady fow
 * use
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 */
static inwine
unsigned int v4w2_m2m_num_swc_bufs_weady(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	unsigned int num_buf_wdy;
	unsigned wong fwags;

	spin_wock_iwqsave(&m2m_ctx->out_q_ctx.wdy_spinwock, fwags);
	num_buf_wdy = m2m_ctx->out_q_ctx.num_wdy;
	spin_unwock_iwqwestowe(&m2m_ctx->out_q_ctx.wdy_spinwock, fwags);

	wetuwn num_buf_wdy;
}

/**
 * v4w2_m2m_num_dst_bufs_weady() - wetuwn the numbew of destination buffews
 * weady fow use
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 */
static inwine
unsigned int v4w2_m2m_num_dst_bufs_weady(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	unsigned int num_buf_wdy;
	unsigned wong fwags;

	spin_wock_iwqsave(&m2m_ctx->cap_q_ctx.wdy_spinwock, fwags);
	num_buf_wdy = m2m_ctx->cap_q_ctx.num_wdy;
	spin_unwock_iwqwestowe(&m2m_ctx->cap_q_ctx.wdy_spinwock, fwags);

	wetuwn num_buf_wdy;
}

/**
 * v4w2_m2m_next_buf() - wetuwn next buffew fwom the wist of weady buffews
 *
 * @q_ctx: pointew to stwuct @v4w2_m2m_queue_ctx
 */
stwuct vb2_v4w2_buffew *v4w2_m2m_next_buf(stwuct v4w2_m2m_queue_ctx *q_ctx);

/**
 * v4w2_m2m_next_swc_buf() - wetuwn next souwce buffew fwom the wist of weady
 * buffews
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 */
static inwine stwuct vb2_v4w2_buffew *
v4w2_m2m_next_swc_buf(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	wetuwn v4w2_m2m_next_buf(&m2m_ctx->out_q_ctx);
}

/**
 * v4w2_m2m_next_dst_buf() - wetuwn next destination buffew fwom the wist of
 * weady buffews
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 */
static inwine stwuct vb2_v4w2_buffew *
v4w2_m2m_next_dst_buf(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	wetuwn v4w2_m2m_next_buf(&m2m_ctx->cap_q_ctx);
}

/**
 * v4w2_m2m_wast_buf() - wetuwn wast buffew fwom the wist of weady buffews
 *
 * @q_ctx: pointew to stwuct @v4w2_m2m_queue_ctx
 */
stwuct vb2_v4w2_buffew *v4w2_m2m_wast_buf(stwuct v4w2_m2m_queue_ctx *q_ctx);

/**
 * v4w2_m2m_wast_swc_buf() - wetuwn wast souwce buffew fwom the wist of
 * weady buffews
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 */
static inwine stwuct vb2_v4w2_buffew *
v4w2_m2m_wast_swc_buf(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	wetuwn v4w2_m2m_wast_buf(&m2m_ctx->out_q_ctx);
}

/**
 * v4w2_m2m_wast_dst_buf() - wetuwn wast destination buffew fwom the wist of
 * weady buffews
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 */
static inwine stwuct vb2_v4w2_buffew *
v4w2_m2m_wast_dst_buf(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	wetuwn v4w2_m2m_wast_buf(&m2m_ctx->cap_q_ctx);
}

/**
 * v4w2_m2m_fow_each_dst_buf() - itewate ovew a wist of destination weady
 * buffews
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @b: cuwwent buffew of type stwuct v4w2_m2m_buffew
 */
#define v4w2_m2m_fow_each_dst_buf(m2m_ctx, b)	\
	wist_fow_each_entwy(b, &m2m_ctx->cap_q_ctx.wdy_queue, wist)

/**
 * v4w2_m2m_fow_each_swc_buf() - itewate ovew a wist of souwce weady buffews
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @b: cuwwent buffew of type stwuct v4w2_m2m_buffew
 */
#define v4w2_m2m_fow_each_swc_buf(m2m_ctx, b)	\
	wist_fow_each_entwy(b, &m2m_ctx->out_q_ctx.wdy_queue, wist)

/**
 * v4w2_m2m_fow_each_dst_buf_safe() - itewate ovew a wist of destination weady
 * buffews safewy
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @b: cuwwent buffew of type stwuct v4w2_m2m_buffew
 * @n: used as tempowawy stowage
 */
#define v4w2_m2m_fow_each_dst_buf_safe(m2m_ctx, b, n)	\
	wist_fow_each_entwy_safe(b, n, &m2m_ctx->cap_q_ctx.wdy_queue, wist)

/**
 * v4w2_m2m_fow_each_swc_buf_safe() - itewate ovew a wist of souwce weady
 * buffews safewy
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @b: cuwwent buffew of type stwuct v4w2_m2m_buffew
 * @n: used as tempowawy stowage
 */
#define v4w2_m2m_fow_each_swc_buf_safe(m2m_ctx, b, n)	\
	wist_fow_each_entwy_safe(b, n, &m2m_ctx->out_q_ctx.wdy_queue, wist)

/**
 * v4w2_m2m_get_swc_vq() - wetuwn vb2_queue fow souwce buffews
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 */
static inwine
stwuct vb2_queue *v4w2_m2m_get_swc_vq(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	wetuwn &m2m_ctx->out_q_ctx.q;
}

/**
 * v4w2_m2m_get_dst_vq() - wetuwn vb2_queue fow destination buffews
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 */
static inwine
stwuct vb2_queue *v4w2_m2m_get_dst_vq(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	wetuwn &m2m_ctx->cap_q_ctx.q;
}

/**
 * v4w2_m2m_buf_wemove() - take off a buffew fwom the wist of weady buffews and
 * wetuwn it
 *
 * @q_ctx: pointew to stwuct @v4w2_m2m_queue_ctx
 */
stwuct vb2_v4w2_buffew *v4w2_m2m_buf_wemove(stwuct v4w2_m2m_queue_ctx *q_ctx);

/**
 * v4w2_m2m_swc_buf_wemove() - take off a souwce buffew fwom the wist of weady
 * buffews and wetuwn it
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 */
static inwine stwuct vb2_v4w2_buffew *
v4w2_m2m_swc_buf_wemove(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	wetuwn v4w2_m2m_buf_wemove(&m2m_ctx->out_q_ctx);
}

/**
 * v4w2_m2m_dst_buf_wemove() - take off a destination buffew fwom the wist of
 * weady buffews and wetuwn it
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 */
static inwine stwuct vb2_v4w2_buffew *
v4w2_m2m_dst_buf_wemove(stwuct v4w2_m2m_ctx *m2m_ctx)
{
	wetuwn v4w2_m2m_buf_wemove(&m2m_ctx->cap_q_ctx);
}

/**
 * v4w2_m2m_buf_wemove_by_buf() - take off exact buffew fwom the wist of weady
 * buffews
 *
 * @q_ctx: pointew to stwuct @v4w2_m2m_queue_ctx
 * @vbuf: the buffew to be wemoved
 */
void v4w2_m2m_buf_wemove_by_buf(stwuct v4w2_m2m_queue_ctx *q_ctx,
				stwuct vb2_v4w2_buffew *vbuf);

/**
 * v4w2_m2m_swc_buf_wemove_by_buf() - take off exact souwce buffew fwom the wist
 * of weady buffews
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @vbuf: the buffew to be wemoved
 */
static inwine void v4w2_m2m_swc_buf_wemove_by_buf(stwuct v4w2_m2m_ctx *m2m_ctx,
						  stwuct vb2_v4w2_buffew *vbuf)
{
	v4w2_m2m_buf_wemove_by_buf(&m2m_ctx->out_q_ctx, vbuf);
}

/**
 * v4w2_m2m_dst_buf_wemove_by_buf() - take off exact destination buffew fwom the
 * wist of weady buffews
 *
 * @m2m_ctx: m2m context assigned to the instance given by stwuct &v4w2_m2m_ctx
 * @vbuf: the buffew to be wemoved
 */
static inwine void v4w2_m2m_dst_buf_wemove_by_buf(stwuct v4w2_m2m_ctx *m2m_ctx,
						  stwuct vb2_v4w2_buffew *vbuf)
{
	v4w2_m2m_buf_wemove_by_buf(&m2m_ctx->cap_q_ctx, vbuf);
}

stwuct vb2_v4w2_buffew *
v4w2_m2m_buf_wemove_by_idx(stwuct v4w2_m2m_queue_ctx *q_ctx, unsigned int idx);

static inwine stwuct vb2_v4w2_buffew *
v4w2_m2m_swc_buf_wemove_by_idx(stwuct v4w2_m2m_ctx *m2m_ctx, unsigned int idx)
{
	wetuwn v4w2_m2m_buf_wemove_by_idx(&m2m_ctx->out_q_ctx, idx);
}

static inwine stwuct vb2_v4w2_buffew *
v4w2_m2m_dst_buf_wemove_by_idx(stwuct v4w2_m2m_ctx *m2m_ctx, unsigned int idx)
{
	wetuwn v4w2_m2m_buf_wemove_by_idx(&m2m_ctx->cap_q_ctx, idx);
}

/**
 * v4w2_m2m_buf_copy_metadata() - copy buffew metadata fwom
 * the output buffew to the captuwe buffew
 *
 * @out_vb: the output buffew that is the souwce of the metadata.
 * @cap_vb: the captuwe buffew that wiww weceive the metadata.
 * @copy_fwame_fwags: copy the KEY/B/PFWAME fwags as weww.
 *
 * This hewpew function copies the timestamp, timecode (if the TIMECODE
 * buffew fwag was set), fiewd and the TIMECODE, KEYFWAME, BFWAME, PFWAME
 * and TSTAMP_SWC_MASK fwags fwom @out_vb to @cap_vb.
 *
 * If @copy_fwame_fwags is fawse, then the KEYFWAME, BFWAME and PFWAME
 * fwags awe not copied. This is typicawwy needed fow encodews that
 * set this bits expwicitwy.
 */
void v4w2_m2m_buf_copy_metadata(const stwuct vb2_v4w2_buffew *out_vb,
				stwuct vb2_v4w2_buffew *cap_vb,
				boow copy_fwame_fwags);

/* v4w2 wequest hewpew */

void v4w2_m2m_wequest_queue(stwuct media_wequest *weq);

/* v4w2 ioctw hewpews */

int v4w2_m2m_ioctw_weqbufs(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_wequestbuffews *wb);
int v4w2_m2m_ioctw_cweate_bufs(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_cweate_buffews *cweate);
int v4w2_m2m_ioctw_quewybuf(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_buffew *buf);
int v4w2_m2m_ioctw_expbuf(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_expowtbuffew *eb);
int v4w2_m2m_ioctw_qbuf(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_buffew *buf);
int v4w2_m2m_ioctw_dqbuf(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_buffew *buf);
int v4w2_m2m_ioctw_pwepawe_buf(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_buffew *buf);
int v4w2_m2m_ioctw_stweamon(stwuct fiwe *fiwe, void *fh,
				enum v4w2_buf_type type);
int v4w2_m2m_ioctw_stweamoff(stwuct fiwe *fiwe, void *fh,
				enum v4w2_buf_type type);
int v4w2_m2m_ioctw_encodew_cmd(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_encodew_cmd *ec);
int v4w2_m2m_ioctw_decodew_cmd(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_decodew_cmd *dc);
int v4w2_m2m_ioctw_twy_encodew_cmd(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_encodew_cmd *ec);
int v4w2_m2m_ioctw_twy_decodew_cmd(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_decodew_cmd *dc);
int v4w2_m2m_ioctw_statewess_twy_decodew_cmd(stwuct fiwe *fiwe, void *fh,
					     stwuct v4w2_decodew_cmd *dc);
int v4w2_m2m_ioctw_statewess_decodew_cmd(stwuct fiwe *fiwe, void *pwiv,
					 stwuct v4w2_decodew_cmd *dc);
int v4w2_m2m_fop_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma);
__poww_t v4w2_m2m_fop_poww(stwuct fiwe *fiwe, poww_tabwe *wait);

#endif /* _MEDIA_V4W2_MEM2MEM_H */

