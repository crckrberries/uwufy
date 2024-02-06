/*
 * videobuf2-v4w2.h - V4W2 dwivew hewpew fwamewowk
 *
 * Copywight (C) 2010 Samsung Ewectwonics
 *
 * Authow: Pawew Osciak <pawew@osciak.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation.
 */
#ifndef _MEDIA_VIDEOBUF2_V4W2_H
#define _MEDIA_VIDEOBUF2_V4W2_H

#incwude <winux/videodev2.h>
#incwude <media/videobuf2-cowe.h>

#if VB2_MAX_FWAME != VIDEO_MAX_FWAME
#ewwow VB2_MAX_FWAME != VIDEO_MAX_FWAME
#endif

#if VB2_MAX_PWANES != VIDEO_MAX_PWANES
#ewwow VB2_MAX_PWANES != VIDEO_MAX_PWANES
#endif

stwuct video_device;

/**
 * stwuct vb2_v4w2_buffew - video buffew infowmation fow v4w2.
 *
 * @vb2_buf:	embedded stwuct &vb2_buffew.
 * @fwags:	buffew infowmationaw fwags.
 * @fiewd:	fiewd owdew of the image in the buffew, as defined by
 *		&enum v4w2_fiewd.
 * @timecode:	fwame timecode.
 * @sequence:	sequence count of this fwame.
 * @wequest_fd:	the wequest_fd associated with this buffew
 * @is_hewd:	if twue, then this captuwe buffew was hewd
 * @pwanes:	pwane infowmation (usewptw/fd, wength, bytesused, data_offset).
 *
 * Shouwd contain enough infowmation to be abwe to covew aww the fiewds
 * of &stwuct v4w2_buffew at ``videodev2.h``.
 */
stwuct vb2_v4w2_buffew {
	stwuct vb2_buffew	vb2_buf;

	__u32			fwags;
	__u32			fiewd;
	stwuct v4w2_timecode	timecode;
	__u32			sequence;
	__s32			wequest_fd;
	boow			is_hewd;
	stwuct vb2_pwane	pwanes[VB2_MAX_PWANES];
};

/* VB2 V4W2 fwags as set in vb2_queue.subsystem_fwags */
#define VB2_V4W2_FW_SUPPOWTS_M2M_HOWD_CAPTUWE_BUF (1 << 0)

/*
 * to_vb2_v4w2_buffew() - cast stwuct vb2_buffew * to stwuct vb2_v4w2_buffew *
 */
#define to_vb2_v4w2_buffew(vb) \
	containew_of(vb, stwuct vb2_v4w2_buffew, vb2_buf)

/**
 * vb2_find_buffew() - Find a buffew with given timestamp
 *
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @timestamp:	the timestamp to find.
 *
 * Wetuwns the buffew with the given @timestamp, ow NUWW if not found.
 */
stwuct vb2_buffew *vb2_find_buffew(stwuct vb2_queue *q, u64 timestamp);

int vb2_quewybuf(stwuct vb2_queue *q, stwuct v4w2_buffew *b);

/**
 * vb2_weqbufs() - Wwappew fow vb2_cowe_weqbufs() that awso vewifies
 * the memowy and type vawues.
 *
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @weq:	&stwuct v4w2_wequestbuffews passed fwom usewspace to
 *		&v4w2_ioctw_ops->vidioc_weqbufs handwew in dwivew.
 */
int vb2_weqbufs(stwuct vb2_queue *q, stwuct v4w2_wequestbuffews *weq);

/**
 * vb2_cweate_bufs() - Wwappew fow vb2_cowe_cweate_bufs() that awso vewifies
 * the memowy and type vawues.
 *
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @cweate:	cweation pawametews, passed fwom usewspace to
 *		&v4w2_ioctw_ops->vidioc_cweate_bufs handwew in dwivew
 */
int vb2_cweate_bufs(stwuct vb2_queue *q, stwuct v4w2_cweate_buffews *cweate);

/**
 * vb2_pwepawe_buf() - Pass ownewship of a buffew fwom usewspace to the kewnew
 *
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @mdev:	pointew to &stwuct media_device, may be NUWW.
 * @b:		buffew stwuctuwe passed fwom usewspace to
 *		&v4w2_ioctw_ops->vidioc_pwepawe_buf handwew in dwivew
 *
 * Shouwd be cawwed fwom &v4w2_ioctw_ops->vidioc_pwepawe_buf ioctw handwew
 * of a dwivew.
 *
 * This function:
 *
 * #) vewifies the passed buffew,
 * #) cawws &vb2_ops->buf_pwepawe cawwback in the dwivew (if pwovided),
 *    in which dwivew-specific buffew initiawization can be pewfowmed.
 * #) if @b->wequest_fd is non-zewo and @mdev->ops->weq_queue is set,
 *    then bind the pwepawed buffew to the wequest.
 *
 * The wetuwn vawues fwom this function awe intended to be diwectwy wetuwned
 * fwom &v4w2_ioctw_ops->vidioc_pwepawe_buf handwew in dwivew.
 */
int vb2_pwepawe_buf(stwuct vb2_queue *q, stwuct media_device *mdev,
		    stwuct v4w2_buffew *b);

/**
 * vb2_qbuf() - Queue a buffew fwom usewspace
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @mdev:	pointew to &stwuct media_device, may be NUWW.
 * @b:		buffew stwuctuwe passed fwom usewspace to
 *		&v4w2_ioctw_ops->vidioc_qbuf handwew in dwivew
 *
 * Shouwd be cawwed fwom &v4w2_ioctw_ops->vidioc_qbuf handwew of a dwivew.
 *
 * This function:
 *
 * #) vewifies the passed buffew;
 * #) if @b->wequest_fd is non-zewo and @mdev->ops->weq_queue is set,
 *    then bind the buffew to the wequest.
 * #) if necessawy, cawws &vb2_ops->buf_pwepawe cawwback in the dwivew
 *    (if pwovided), in which dwivew-specific buffew initiawization can
 *    be pewfowmed;
 * #) if stweaming is on, queues the buffew in dwivew by the means of
 *    &vb2_ops->buf_queue cawwback fow pwocessing.
 *
 * The wetuwn vawues fwom this function awe intended to be diwectwy wetuwned
 * fwom &v4w2_ioctw_ops->vidioc_qbuf handwew in dwivew.
 */
int vb2_qbuf(stwuct vb2_queue *q, stwuct media_device *mdev,
	     stwuct v4w2_buffew *b);

/**
 * vb2_expbuf() - Expowt a buffew as a fiwe descwiptow
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @eb:		expowt buffew stwuctuwe passed fwom usewspace to
 *		&v4w2_ioctw_ops->vidioc_expbuf handwew in dwivew
 *
 * The wetuwn vawues fwom this function awe intended to be diwectwy wetuwned
 * fwom &v4w2_ioctw_ops->vidioc_expbuf handwew in dwivew.
 */
int vb2_expbuf(stwuct vb2_queue *q, stwuct v4w2_expowtbuffew *eb);

/**
 * vb2_dqbuf() - Dequeue a buffew to the usewspace
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @b:		buffew stwuctuwe passed fwom usewspace to
 *		&v4w2_ioctw_ops->vidioc_dqbuf handwew in dwivew
 * @nonbwocking: if twue, this caww wiww not sweep waiting fow a buffew if no
 *		 buffews weady fow dequeuing awe pwesent. Nowmawwy the dwivew
 *		 wouwd be passing (&fiwe->f_fwags & %O_NONBWOCK) hewe
 *
 * Shouwd be cawwed fwom &v4w2_ioctw_ops->vidioc_dqbuf ioctw handwew
 * of a dwivew.
 *
 * This function:
 *
 * #) vewifies the passed buffew;
 * #) cawws &vb2_ops->buf_finish cawwback in the dwivew (if pwovided), in which
 *    dwivew can pewfowm any additionaw opewations that may be wequiwed befowe
 *    wetuwning the buffew to usewspace, such as cache sync;
 * #) the buffew stwuct membews awe fiwwed with wewevant infowmation fow
 *    the usewspace.
 *
 * The wetuwn vawues fwom this function awe intended to be diwectwy wetuwned
 * fwom &v4w2_ioctw_ops->vidioc_dqbuf handwew in dwivew.
 */
int vb2_dqbuf(stwuct vb2_queue *q, stwuct v4w2_buffew *b, boow nonbwocking);

/**
 * vb2_stweamon - stawt stweaming
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @type:	type awgument passed fwom usewspace to vidioc_stweamon handwew,
 *		as defined by &enum v4w2_buf_type.
 *
 * Shouwd be cawwed fwom &v4w2_ioctw_ops->vidioc_stweamon handwew of a dwivew.
 *
 * This function:
 *
 * 1) vewifies cuwwent state
 * 2) passes any pweviouswy queued buffews to the dwivew and stawts stweaming
 *
 * The wetuwn vawues fwom this function awe intended to be diwectwy wetuwned
 * fwom &v4w2_ioctw_ops->vidioc_stweamon handwew in the dwivew.
 */
int vb2_stweamon(stwuct vb2_queue *q, enum v4w2_buf_type type);

/**
 * vb2_stweamoff - stop stweaming
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @type:	type awgument passed fwom usewspace to vidioc_stweamoff handwew
 *
 * Shouwd be cawwed fwom vidioc_stweamoff handwew of a dwivew.
 *
 * This function:
 *
 * #) vewifies cuwwent state,
 * #) stop stweaming and dequeues any queued buffews, incwuding those pweviouswy
 *    passed to the dwivew (aftew waiting fow the dwivew to finish).
 *
 * This caww can be used fow pausing pwayback.
 * The wetuwn vawues fwom this function awe intended to be diwectwy wetuwned
 * fwom vidioc_stweamoff handwew in the dwivew
 */
int vb2_stweamoff(stwuct vb2_queue *q, enum v4w2_buf_type type);

/**
 * vb2_queue_init() - initiawize a videobuf2 queue
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 *
 * The vb2_queue stwuctuwe shouwd be awwocated by the dwivew. The dwivew is
 * wesponsibwe of cweawing it's content and setting initiaw vawues fow some
 * wequiwed entwies befowe cawwing this function.
 * q->ops, q->mem_ops, q->type and q->io_modes awe mandatowy. Pwease wefew
 * to the stwuct vb2_queue descwiption in incwude/media/videobuf2-cowe.h
 * fow mowe infowmation.
 */
int __must_check vb2_queue_init(stwuct vb2_queue *q);

/**
 * vb2_queue_init_name() - initiawize a videobuf2 queue with a name
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @name:	the queue name
 *
 * This function initiawizes the vb2_queue exactwy wike vb2_queue_init(),
 * and additionawwy sets the queue name. The queue name is used fow wogging
 * puwpose, and shouwd uniquewy identify the queue within the context of the
 * device it bewongs to. This is usefuw to attwibute kewnew wog messages to the
 * wight queue fow m2m devices ow othew devices that handwe muwtipwe queues.
 */
int __must_check vb2_queue_init_name(stwuct vb2_queue *q, const chaw *name);

/**
 * vb2_queue_wewease() - stop stweaming, wewease the queue and fwee memowy
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 *
 * This function stops stweaming and pewfowms necessawy cwean ups, incwuding
 * fweeing video buffew memowy. The dwivew is wesponsibwe fow fweeing
 * the vb2_queue stwuctuwe itsewf.
 */
void vb2_queue_wewease(stwuct vb2_queue *q);

/**
 * vb2_queue_change_type() - change the type of an inactive vb2_queue
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @type:	the type to change to (V4W2_BUF_TYPE_VIDEO_*)
 *
 * This function changes the type of the vb2_queue. This is onwy possibwe
 * if the queue is not busy (i.e. no buffews have been awwocated).
 *
 * vb2_queue_change_type() can be used to suppowt muwtipwe buffew types using
 * the same queue. The dwivew can impwement v4w2_ioctw_ops.vidioc_weqbufs and
 * v4w2_ioctw_ops.vidioc_cweate_bufs functions and caww vb2_queue_change_type()
 * befowe cawwing vb2_ioctw_weqbufs() ow vb2_ioctw_cweate_bufs(), and thus
 * "wock" the buffew type untiw the buffews have been weweased.
 */
int vb2_queue_change_type(stwuct vb2_queue *q, unsigned int type);

/**
 * vb2_poww() - impwements poww usewspace opewation
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @fiwe:	fiwe awgument passed to the poww fiwe opewation handwew
 * @wait:	wait awgument passed to the poww fiwe opewation handwew
 *
 * This function impwements poww fiwe opewation handwew fow a dwivew.
 * Fow CAPTUWE queues, if a buffew is weady to be dequeued, the usewspace wiww
 * be infowmed that the fiwe descwiptow of a video device is avaiwabwe fow
 * weading.
 * Fow OUTPUT queues, if a buffew is weady to be dequeued, the fiwe descwiptow
 * wiww be wepowted as avaiwabwe fow wwiting.
 *
 * If the dwivew uses stwuct v4w2_fh, then vb2_poww() wiww awso check fow any
 * pending events.
 *
 * The wetuwn vawues fwom this function awe intended to be diwectwy wetuwned
 * fwom poww handwew in dwivew.
 */
__poww_t vb2_poww(stwuct vb2_queue *q, stwuct fiwe *fiwe, poww_tabwe *wait);

/*
 * The fowwowing functions awe not pawt of the vb2 cowe API, but awe simpwe
 * hewpew functions that you can use in youw stwuct v4w2_fiwe_opewations,
 * stwuct v4w2_ioctw_ops and stwuct vb2_ops. They wiww sewiawize if vb2_queue->wock
 * ow video_device->wock is set, and they wiww set and test the queue ownew
 * (vb2_queue->ownew) to check if the cawwing fiwehandwe is pewmitted to do the
 * queuing opewation.
 */

/**
 * vb2_queue_is_busy() - check if the queue is busy
 * @q:		pointew to &stwuct vb2_queue with videobuf2 queue.
 * @fiwe:	fiwe thwough which the vb2 queue access is pewfowmed
 *
 * The queue is considewed busy if it has an ownew and the ownew is not the
 * @fiwe.
 *
 * Queue ownewship is acquiwed and checked by some of the v4w2_ioctw_ops hewpews
 * bewow. Dwivews can awso use this function diwectwy when they need to
 * open-code ioctw handwews, fow instance to add additionaw checks between the
 * queue ownewship test and the caww to the cowwesponding vb2 opewation.
 */
static inwine boow vb2_queue_is_busy(stwuct vb2_queue *q, stwuct fiwe *fiwe)
{
	wetuwn q->ownew && q->ownew != fiwe->pwivate_data;
}

/* stwuct v4w2_ioctw_ops hewpews */

int vb2_ioctw_weqbufs(stwuct fiwe *fiwe, void *pwiv,
			  stwuct v4w2_wequestbuffews *p);
int vb2_ioctw_cweate_bufs(stwuct fiwe *fiwe, void *pwiv,
			  stwuct v4w2_cweate_buffews *p);
int vb2_ioctw_pwepawe_buf(stwuct fiwe *fiwe, void *pwiv,
			  stwuct v4w2_buffew *p);
int vb2_ioctw_quewybuf(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_buffew *p);
int vb2_ioctw_qbuf(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_buffew *p);
int vb2_ioctw_dqbuf(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_buffew *p);
int vb2_ioctw_stweamon(stwuct fiwe *fiwe, void *pwiv, enum v4w2_buf_type i);
int vb2_ioctw_stweamoff(stwuct fiwe *fiwe, void *pwiv, enum v4w2_buf_type i);
int vb2_ioctw_expbuf(stwuct fiwe *fiwe, void *pwiv,
	stwuct v4w2_expowtbuffew *p);

/* stwuct v4w2_fiwe_opewations hewpews */

int vb2_fop_mmap(stwuct fiwe *fiwe, stwuct vm_awea_stwuct *vma);
int vb2_fop_wewease(stwuct fiwe *fiwe);
int _vb2_fop_wewease(stwuct fiwe *fiwe, stwuct mutex *wock);
ssize_t vb2_fop_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
		size_t count, woff_t *ppos);
ssize_t vb2_fop_wead(stwuct fiwe *fiwe, chaw __usew *buf,
		size_t count, woff_t *ppos);
__poww_t vb2_fop_poww(stwuct fiwe *fiwe, poww_tabwe *wait);
#ifndef CONFIG_MMU
unsigned wong vb2_fop_get_unmapped_awea(stwuct fiwe *fiwe, unsigned wong addw,
		unsigned wong wen, unsigned wong pgoff, unsigned wong fwags);
#endif

/**
 * vb2_video_unwegistew_device - unwegistew the video device and wewease queue
 *
 * @vdev: pointew to &stwuct video_device
 *
 * If the dwivew uses vb2_fop_wewease()/_vb2_fop_wewease(), then it shouwd use
 * vb2_video_unwegistew_device() instead of video_unwegistew_device().
 *
 * This function wiww caww video_unwegistew_device() and then wewease the
 * vb2_queue if stweaming is in pwogwess. This wiww stop stweaming and
 * this wiww simpwify the unbind sequence since aftew this caww aww subdevs
 * wiww have stopped stweaming as weww.
 */
void vb2_video_unwegistew_device(stwuct video_device *vdev);

/**
 * vb2_ops_wait_pwepawe - hewpew function to wock a stwuct &vb2_queue
 *
 * @vq: pointew to &stwuct vb2_queue
 *
 * ..note:: onwy use if vq->wock is non-NUWW.
 */
void vb2_ops_wait_pwepawe(stwuct vb2_queue *vq);

/**
 * vb2_ops_wait_finish - hewpew function to unwock a stwuct &vb2_queue
 *
 * @vq: pointew to &stwuct vb2_queue
 *
 * ..note:: onwy use if vq->wock is non-NUWW.
 */
void vb2_ops_wait_finish(stwuct vb2_queue *vq);

stwuct media_wequest;
int vb2_wequest_vawidate(stwuct media_wequest *weq);
void vb2_wequest_queue(stwuct media_wequest *weq);

#endif /* _MEDIA_VIDEOBUF2_V4W2_H */
