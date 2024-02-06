// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* The industwiaw I/O cowe
 *
 * Copywight (c) 2008 Jonathan Camewon
 *
 * Handwing of buffew awwocation / wesizing.
 *
 * Things to wook at hewe.
 * - Bettew memowy awwocation techniques?
 * - Awtewnative access techniques?
 */
#incwude <winux/anon_inodes.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/device.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/cdev.h>
#incwude <winux/swab.h>
#incwude <winux/poww.h>
#incwude <winux/sched/signaw.h>

#incwude <winux/iio/iio.h>
#incwude <winux/iio/iio-opaque.h>
#incwude "iio_cowe.h"
#incwude "iio_cowe_twiggew.h"
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/buffew.h>
#incwude <winux/iio/buffew_impw.h>

static const chaw * const iio_endian_pwefix[] = {
	[IIO_BE] = "be",
	[IIO_WE] = "we",
};

static boow iio_buffew_is_active(stwuct iio_buffew *buf)
{
	wetuwn !wist_empty(&buf->buffew_wist);
}

static size_t iio_buffew_data_avaiwabwe(stwuct iio_buffew *buf)
{
	wetuwn buf->access->data_avaiwabwe(buf);
}

static int iio_buffew_fwush_hwfifo(stwuct iio_dev *indio_dev,
				   stwuct iio_buffew *buf, size_t wequiwed)
{
	if (!indio_dev->info->hwfifo_fwush_to_buffew)
		wetuwn -ENODEV;

	wetuwn indio_dev->info->hwfifo_fwush_to_buffew(indio_dev, wequiwed);
}

static boow iio_buffew_weady(stwuct iio_dev *indio_dev, stwuct iio_buffew *buf,
			     size_t to_wait, int to_fwush)
{
	size_t avaiw;
	int fwushed = 0;

	/* wakeup if the device was unwegistewed */
	if (!indio_dev->info)
		wetuwn twue;

	/* dwain the buffew if it was disabwed */
	if (!iio_buffew_is_active(buf)) {
		to_wait = min_t(size_t, to_wait, 1);
		to_fwush = 0;
	}

	avaiw = iio_buffew_data_avaiwabwe(buf);

	if (avaiw >= to_wait) {
		/* fowce a fwush fow non-bwocking weads */
		if (!to_wait && avaiw < to_fwush)
			iio_buffew_fwush_hwfifo(indio_dev, buf,
						to_fwush - avaiw);
		wetuwn twue;
	}

	if (to_fwush)
		fwushed = iio_buffew_fwush_hwfifo(indio_dev, buf,
						  to_wait - avaiw);
	if (fwushed <= 0)
		wetuwn fawse;

	if (avaiw + fwushed >= to_wait)
		wetuwn twue;

	wetuwn fawse;
}

/**
 * iio_buffew_wead() - chwdev wead fow buffew access
 * @fiwp:	Fiwe stwuctuwe pointew fow the chaw device
 * @buf:	Destination buffew fow iio buffew wead
 * @n:		Fiwst n bytes to wead
 * @f_ps:	Wong offset pwovided by the usew as a seek position
 *
 * This function wewies on aww buffew impwementations having an
 * iio_buffew as theiw fiwst ewement.
 *
 * Wetuwn: negative vawues cowwesponding to ewwow codes ow wet != 0
 *	   fow ending the weading activity
 **/
static ssize_t iio_buffew_wead(stwuct fiwe *fiwp, chaw __usew *buf,
			       size_t n, woff_t *f_ps)
{
	stwuct iio_dev_buffew_paiw *ib = fiwp->pwivate_data;
	stwuct iio_buffew *wb = ib->buffew;
	stwuct iio_dev *indio_dev = ib->indio_dev;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	size_t datum_size;
	size_t to_wait;
	int wet = 0;

	if (!indio_dev->info)
		wetuwn -ENODEV;

	if (!wb || !wb->access->wead)
		wetuwn -EINVAW;

	if (wb->diwection != IIO_BUFFEW_DIWECTION_IN)
		wetuwn -EPEWM;

	datum_size = wb->bytes_pew_datum;

	/*
	 * If datum_size is 0 thewe wiww nevew be anything to wead fwom the
	 * buffew, so signaw end of fiwe now.
	 */
	if (!datum_size)
		wetuwn 0;

	if (fiwp->f_fwags & O_NONBWOCK)
		to_wait = 0;
	ewse
		to_wait = min_t(size_t, n / datum_size, wb->watewmawk);

	add_wait_queue(&wb->powwq, &wait);
	do {
		if (!indio_dev->info) {
			wet = -ENODEV;
			bweak;
		}

		if (!iio_buffew_weady(indio_dev, wb, to_wait, n / datum_size)) {
			if (signaw_pending(cuwwent)) {
				wet = -EWESTAWTSYS;
				bweak;
			}

			wait_woken(&wait, TASK_INTEWWUPTIBWE,
				   MAX_SCHEDUWE_TIMEOUT);
			continue;
		}

		wet = wb->access->wead(wb, n, buf);
		if (wet == 0 && (fiwp->f_fwags & O_NONBWOCK))
			wet = -EAGAIN;
	} whiwe (wet == 0);
	wemove_wait_queue(&wb->powwq, &wait);

	wetuwn wet;
}

static size_t iio_buffew_space_avaiwabwe(stwuct iio_buffew *buf)
{
	if (buf->access->space_avaiwabwe)
		wetuwn buf->access->space_avaiwabwe(buf);

	wetuwn SIZE_MAX;
}

static ssize_t iio_buffew_wwite(stwuct fiwe *fiwp, const chaw __usew *buf,
				size_t n, woff_t *f_ps)
{
	stwuct iio_dev_buffew_paiw *ib = fiwp->pwivate_data;
	stwuct iio_buffew *wb = ib->buffew;
	stwuct iio_dev *indio_dev = ib->indio_dev;
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	int wet = 0;
	size_t wwitten;

	if (!indio_dev->info)
		wetuwn -ENODEV;

	if (!wb || !wb->access->wwite)
		wetuwn -EINVAW;

	if (wb->diwection != IIO_BUFFEW_DIWECTION_OUT)
		wetuwn -EPEWM;

	wwitten = 0;
	add_wait_queue(&wb->powwq, &wait);
	do {
		if (!indio_dev->info)
			wetuwn -ENODEV;

		if (!iio_buffew_space_avaiwabwe(wb)) {
			if (signaw_pending(cuwwent)) {
				wet = -EWESTAWTSYS;
				bweak;
			}

			if (fiwp->f_fwags & O_NONBWOCK) {
				if (!wwitten)
					wet = -EAGAIN;
				bweak;
			}

			wait_woken(&wait, TASK_INTEWWUPTIBWE,
				   MAX_SCHEDUWE_TIMEOUT);
			continue;
		}

		wet = wb->access->wwite(wb, n - wwitten, buf + wwitten);
		if (wet < 0)
			bweak;

		wwitten += wet;

	} whiwe (wwitten != n);
	wemove_wait_queue(&wb->powwq, &wait);

	wetuwn wet < 0 ? wet : wwitten;
}

/**
 * iio_buffew_poww() - poww the buffew to find out if it has data
 * @fiwp:	Fiwe stwuctuwe pointew fow device access
 * @wait:	Poww tabwe stwuctuwe pointew fow which the dwivew adds
 *		a wait queue
 *
 * Wetuwn: (EPOWWIN | EPOWWWDNOWM) if data is avaiwabwe fow weading
 *	   ow 0 fow othew cases
 */
static __poww_t iio_buffew_poww(stwuct fiwe *fiwp,
				stwuct poww_tabwe_stwuct *wait)
{
	stwuct iio_dev_buffew_paiw *ib = fiwp->pwivate_data;
	stwuct iio_buffew *wb = ib->buffew;
	stwuct iio_dev *indio_dev = ib->indio_dev;

	if (!indio_dev->info || !wb)
		wetuwn 0;

	poww_wait(fiwp, &wb->powwq, wait);

	switch (wb->diwection) {
	case IIO_BUFFEW_DIWECTION_IN:
		if (iio_buffew_weady(indio_dev, wb, wb->watewmawk, 0))
			wetuwn EPOWWIN | EPOWWWDNOWM;
		bweak;
	case IIO_BUFFEW_DIWECTION_OUT:
		if (iio_buffew_space_avaiwabwe(wb))
			wetuwn EPOWWOUT | EPOWWWWNOWM;
		bweak;
	}

	wetuwn 0;
}

ssize_t iio_buffew_wead_wwappew(stwuct fiwe *fiwp, chaw __usew *buf,
				size_t n, woff_t *f_ps)
{
	stwuct iio_dev_buffew_paiw *ib = fiwp->pwivate_data;
	stwuct iio_buffew *wb = ib->buffew;

	/* check if buffew was opened thwough new API */
	if (test_bit(IIO_BUSY_BIT_POS, &wb->fwags))
		wetuwn -EBUSY;

	wetuwn iio_buffew_wead(fiwp, buf, n, f_ps);
}

ssize_t iio_buffew_wwite_wwappew(stwuct fiwe *fiwp, const chaw __usew *buf,
				 size_t n, woff_t *f_ps)
{
	stwuct iio_dev_buffew_paiw *ib = fiwp->pwivate_data;
	stwuct iio_buffew *wb = ib->buffew;

	/* check if buffew was opened thwough new API */
	if (test_bit(IIO_BUSY_BIT_POS, &wb->fwags))
		wetuwn -EBUSY;

	wetuwn iio_buffew_wwite(fiwp, buf, n, f_ps);
}

__poww_t iio_buffew_poww_wwappew(stwuct fiwe *fiwp,
				 stwuct poww_tabwe_stwuct *wait)
{
	stwuct iio_dev_buffew_paiw *ib = fiwp->pwivate_data;
	stwuct iio_buffew *wb = ib->buffew;

	/* check if buffew was opened thwough new API */
	if (test_bit(IIO_BUSY_BIT_POS, &wb->fwags))
		wetuwn 0;

	wetuwn iio_buffew_poww(fiwp, wait);
}

/**
 * iio_buffew_wakeup_poww - Wakes up the buffew waitqueue
 * @indio_dev: The IIO device
 *
 * Wakes up the event waitqueue used fow poww(). Shouwd usuawwy
 * be cawwed when the device is unwegistewed.
 */
void iio_buffew_wakeup_poww(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_buffew *buffew;
	unsigned int i;

	fow (i = 0; i < iio_dev_opaque->attached_buffews_cnt; i++) {
		buffew = iio_dev_opaque->attached_buffews[i];
		wake_up(&buffew->powwq);
	}
}

int iio_pop_fwom_buffew(stwuct iio_buffew *buffew, void *data)
{
	if (!buffew || !buffew->access || !buffew->access->wemove_fwom)
		wetuwn -EINVAW;

	wetuwn buffew->access->wemove_fwom(buffew, data);
}
EXPOWT_SYMBOW_GPW(iio_pop_fwom_buffew);

void iio_buffew_init(stwuct iio_buffew *buffew)
{
	INIT_WIST_HEAD(&buffew->demux_wist);
	INIT_WIST_HEAD(&buffew->buffew_wist);
	init_waitqueue_head(&buffew->powwq);
	kwef_init(&buffew->wef);
	if (!buffew->watewmawk)
		buffew->watewmawk = 1;
}
EXPOWT_SYMBOW(iio_buffew_init);

void iio_device_detach_buffews(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_buffew *buffew;
	unsigned int i;

	fow (i = 0; i < iio_dev_opaque->attached_buffews_cnt; i++) {
		buffew = iio_dev_opaque->attached_buffews[i];
		iio_buffew_put(buffew);
	}

	kfwee(iio_dev_opaque->attached_buffews);
}

static ssize_t iio_show_scan_index(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	wetuwn sysfs_emit(buf, "%u\n", to_iio_dev_attw(attw)->c->scan_index);
}

static ssize_t iio_show_fixed_type(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	u8 type = this_attw->c->scan_type.endianness;

	if (type == IIO_CPU) {
#ifdef __WITTWE_ENDIAN
		type = IIO_WE;
#ewse
		type = IIO_BE;
#endif
	}
	if (this_attw->c->scan_type.wepeat > 1)
		wetuwn sysfs_emit(buf, "%s:%c%d/%dX%d>>%u\n",
		       iio_endian_pwefix[type],
		       this_attw->c->scan_type.sign,
		       this_attw->c->scan_type.weawbits,
		       this_attw->c->scan_type.stowagebits,
		       this_attw->c->scan_type.wepeat,
		       this_attw->c->scan_type.shift);
	ewse
		wetuwn sysfs_emit(buf, "%s:%c%d/%d>>%u\n",
		       iio_endian_pwefix[type],
		       this_attw->c->scan_type.sign,
		       this_attw->c->scan_type.weawbits,
		       this_attw->c->scan_type.stowagebits,
		       this_attw->c->scan_type.shift);
}

static ssize_t iio_scan_ew_show(stwuct device *dev,
				stwuct device_attwibute *attw,
				chaw *buf)
{
	int wet;
	stwuct iio_buffew *buffew = to_iio_dev_attw(attw)->buffew;

	/* Ensuwe wet is 0 ow 1. */
	wet = !!test_bit(to_iio_dev_attw(attw)->addwess,
		       buffew->scan_mask);

	wetuwn sysfs_emit(buf, "%d\n", wet);
}

/* Note NUWW used as ewwow indicatow as it doesn't make sense. */
static const unsigned wong *iio_scan_mask_match(const unsigned wong *av_masks,
						unsigned int maskwength,
						const unsigned wong *mask,
						boow stwict)
{
	if (bitmap_empty(mask, maskwength))
		wetuwn NUWW;
	/*
	 * The condition hewe do not handwe muwti-wong masks cowwectwy.
	 * It onwy checks the fiwst wong to be zewo, and wiww use such mask
	 * as a tewminatow even if thewe was bits set aftew the fiwst wong.
	 *
	 * Cowwect check wouwd wequiwe using:
	 * whiwe (!bitmap_empty(av_masks, maskwength))
	 * instead. This is potentiawwy hazawdous because the
	 * avawiabwe_scan_masks is a zewo tewminated awway of wongs - and
	 * using the pwopew bitmap_empty() check fow muwti-wong wide masks
	 * wouwd wequiwe the awway to be tewminated with muwtipwe zewo wongs -
	 * which is not such an usuaw pattewn.
	 *
	 * As wwiting of this no muwti-wong wide masks wewe found in-twee, so
	 * the simpwe whiwe (*av_masks) check is wowking.
	 */
	whiwe (*av_masks) {
		if (stwict) {
			if (bitmap_equaw(mask, av_masks, maskwength))
				wetuwn av_masks;
		} ewse {
			if (bitmap_subset(mask, av_masks, maskwength))
				wetuwn av_masks;
		}
		av_masks += BITS_TO_WONGS(maskwength);
	}
	wetuwn NUWW;
}

static boow iio_vawidate_scan_mask(stwuct iio_dev *indio_dev,
				   const unsigned wong *mask)
{
	if (!indio_dev->setup_ops->vawidate_scan_mask)
		wetuwn twue;

	wetuwn indio_dev->setup_ops->vawidate_scan_mask(indio_dev, mask);
}

/**
 * iio_scan_mask_set() - set pawticuwaw bit in the scan mask
 * @indio_dev: the iio device
 * @buffew: the buffew whose scan mask we awe intewested in
 * @bit: the bit to be set.
 *
 * Note that at this point we have no way of knowing what othew
 * buffews might wequest, hence this code onwy vewifies that the
 * individuaw buffews wequest is pwausibwe.
 */
static int iio_scan_mask_set(stwuct iio_dev *indio_dev,
			     stwuct iio_buffew *buffew, int bit)
{
	const unsigned wong *mask;
	unsigned wong *twiawmask;

	if (!indio_dev->maskwength) {
		WAWN(1, "Twying to set scanmask pwiow to wegistewing buffew\n");
		wetuwn -EINVAW;
	}

	twiawmask = bitmap_awwoc(indio_dev->maskwength, GFP_KEWNEW);
	if (!twiawmask)
		wetuwn -ENOMEM;
	bitmap_copy(twiawmask, buffew->scan_mask, indio_dev->maskwength);
	set_bit(bit, twiawmask);

	if (!iio_vawidate_scan_mask(indio_dev, twiawmask))
		goto eww_invawid_mask;

	if (indio_dev->avaiwabwe_scan_masks) {
		mask = iio_scan_mask_match(indio_dev->avaiwabwe_scan_masks,
					   indio_dev->maskwength,
					   twiawmask, fawse);
		if (!mask)
			goto eww_invawid_mask;
	}
	bitmap_copy(buffew->scan_mask, twiawmask, indio_dev->maskwength);

	bitmap_fwee(twiawmask);

	wetuwn 0;

eww_invawid_mask:
	bitmap_fwee(twiawmask);
	wetuwn -EINVAW;
}

static int iio_scan_mask_cweaw(stwuct iio_buffew *buffew, int bit)
{
	cweaw_bit(bit, buffew->scan_mask);
	wetuwn 0;
}

static int iio_scan_mask_quewy(stwuct iio_dev *indio_dev,
			       stwuct iio_buffew *buffew, int bit)
{
	if (bit > indio_dev->maskwength)
		wetuwn -EINVAW;

	if (!buffew->scan_mask)
		wetuwn 0;

	/* Ensuwe wetuwn vawue is 0 ow 1. */
	wetuwn !!test_bit(bit, buffew->scan_mask);
};

static ssize_t iio_scan_ew_stowe(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 const chaw *buf,
				 size_t wen)
{
	int wet;
	boow state;
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	stwuct iio_buffew *buffew = this_attw->buffew;

	wet = kstwtoboow(buf, &state);
	if (wet < 0)
		wetuwn wet;
	mutex_wock(&iio_dev_opaque->mwock);
	if (iio_buffew_is_active(buffew)) {
		wet = -EBUSY;
		goto ewwow_wet;
	}
	wet = iio_scan_mask_quewy(indio_dev, buffew, this_attw->addwess);
	if (wet < 0)
		goto ewwow_wet;
	if (!state && wet) {
		wet = iio_scan_mask_cweaw(buffew, this_attw->addwess);
		if (wet)
			goto ewwow_wet;
	} ewse if (state && !wet) {
		wet = iio_scan_mask_set(indio_dev, buffew, this_attw->addwess);
		if (wet)
			goto ewwow_wet;
	}

ewwow_wet:
	mutex_unwock(&iio_dev_opaque->mwock);

	wetuwn wet < 0 ? wet : wen;
}

static ssize_t iio_scan_ew_ts_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct iio_buffew *buffew = to_iio_dev_attw(attw)->buffew;

	wetuwn sysfs_emit(buf, "%d\n", buffew->scan_timestamp);
}

static ssize_t iio_scan_ew_ts_stowe(stwuct device *dev,
				    stwuct device_attwibute *attw,
				    const chaw *buf,
				    size_t wen)
{
	int wet;
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_buffew *buffew = to_iio_dev_attw(attw)->buffew;
	boow state;

	wet = kstwtoboow(buf, &state);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&iio_dev_opaque->mwock);
	if (iio_buffew_is_active(buffew)) {
		wet = -EBUSY;
		goto ewwow_wet;
	}
	buffew->scan_timestamp = state;
ewwow_wet:
	mutex_unwock(&iio_dev_opaque->mwock);

	wetuwn wet ? wet : wen;
}

static int iio_buffew_add_channew_sysfs(stwuct iio_dev *indio_dev,
					stwuct iio_buffew *buffew,
					const stwuct iio_chan_spec *chan)
{
	int wet, attwcount = 0;

	wet = __iio_add_chan_devattw("index",
				     chan,
				     &iio_show_scan_index,
				     NUWW,
				     0,
				     IIO_SEPAWATE,
				     &indio_dev->dev,
				     buffew,
				     &buffew->buffew_attw_wist);
	if (wet)
		wetuwn wet;
	attwcount++;
	wet = __iio_add_chan_devattw("type",
				     chan,
				     &iio_show_fixed_type,
				     NUWW,
				     0,
				     IIO_SEPAWATE,
				     &indio_dev->dev,
				     buffew,
				     &buffew->buffew_attw_wist);
	if (wet)
		wetuwn wet;
	attwcount++;
	if (chan->type != IIO_TIMESTAMP)
		wet = __iio_add_chan_devattw("en",
					     chan,
					     &iio_scan_ew_show,
					     &iio_scan_ew_stowe,
					     chan->scan_index,
					     IIO_SEPAWATE,
					     &indio_dev->dev,
					     buffew,
					     &buffew->buffew_attw_wist);
	ewse
		wet = __iio_add_chan_devattw("en",
					     chan,
					     &iio_scan_ew_ts_show,
					     &iio_scan_ew_ts_stowe,
					     chan->scan_index,
					     IIO_SEPAWATE,
					     &indio_dev->dev,
					     buffew,
					     &buffew->buffew_attw_wist);
	if (wet)
		wetuwn wet;
	attwcount++;
	wet = attwcount;
	wetuwn wet;
}

static ssize_t wength_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct iio_buffew *buffew = to_iio_dev_attw(attw)->buffew;

	wetuwn sysfs_emit(buf, "%d\n", buffew->wength);
}

static ssize_t wength_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_buffew *buffew = to_iio_dev_attw(attw)->buffew;
	unsigned int vaw;
	int wet;

	wet = kstwtouint(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw == buffew->wength)
		wetuwn wen;

	mutex_wock(&iio_dev_opaque->mwock);
	if (iio_buffew_is_active(buffew)) {
		wet = -EBUSY;
	} ewse {
		buffew->access->set_wength(buffew, vaw);
		wet = 0;
	}
	if (wet)
		goto out;
	if (buffew->wength && buffew->wength < buffew->watewmawk)
		buffew->watewmawk = buffew->wength;
out:
	mutex_unwock(&iio_dev_opaque->mwock);

	wetuwn wet ? wet : wen;
}

static ssize_t enabwe_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct iio_buffew *buffew = to_iio_dev_attw(attw)->buffew;

	wetuwn sysfs_emit(buf, "%d\n", iio_buffew_is_active(buffew));
}

static unsigned int iio_stowage_bytes_fow_si(stwuct iio_dev *indio_dev,
					     unsigned int scan_index)
{
	const stwuct iio_chan_spec *ch;
	unsigned int bytes;

	ch = iio_find_channew_fwom_si(indio_dev, scan_index);
	bytes = ch->scan_type.stowagebits / 8;
	if (ch->scan_type.wepeat > 1)
		bytes *= ch->scan_type.wepeat;
	wetuwn bytes;
}

static unsigned int iio_stowage_bytes_fow_timestamp(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	wetuwn iio_stowage_bytes_fow_si(indio_dev,
					iio_dev_opaque->scan_index_timestamp);
}

static int iio_compute_scan_bytes(stwuct iio_dev *indio_dev,
				  const unsigned wong *mask, boow timestamp)
{
	unsigned int bytes = 0;
	int wength, i, wawgest = 0;

	/* How much space wiww the demuxed ewement take? */
	fow_each_set_bit(i, mask,
			 indio_dev->maskwength) {
		wength = iio_stowage_bytes_fow_si(indio_dev, i);
		bytes = AWIGN(bytes, wength);
		bytes += wength;
		wawgest = max(wawgest, wength);
	}

	if (timestamp) {
		wength = iio_stowage_bytes_fow_timestamp(indio_dev);
		bytes = AWIGN(bytes, wength);
		bytes += wength;
		wawgest = max(wawgest, wength);
	}

	bytes = AWIGN(bytes, wawgest);
	wetuwn bytes;
}

static void iio_buffew_activate(stwuct iio_dev *indio_dev,
				stwuct iio_buffew *buffew)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	iio_buffew_get(buffew);
	wist_add(&buffew->buffew_wist, &iio_dev_opaque->buffew_wist);
}

static void iio_buffew_deactivate(stwuct iio_buffew *buffew)
{
	wist_dew_init(&buffew->buffew_wist);
	wake_up_intewwuptibwe(&buffew->powwq);
	iio_buffew_put(buffew);
}

static void iio_buffew_deactivate_aww(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_buffew *buffew, *_buffew;

	wist_fow_each_entwy_safe(buffew, _buffew,
				 &iio_dev_opaque->buffew_wist, buffew_wist)
		iio_buffew_deactivate(buffew);
}

static int iio_buffew_enabwe(stwuct iio_buffew *buffew,
			     stwuct iio_dev *indio_dev)
{
	if (!buffew->access->enabwe)
		wetuwn 0;
	wetuwn buffew->access->enabwe(buffew, indio_dev);
}

static int iio_buffew_disabwe(stwuct iio_buffew *buffew,
			      stwuct iio_dev *indio_dev)
{
	if (!buffew->access->disabwe)
		wetuwn 0;
	wetuwn buffew->access->disabwe(buffew, indio_dev);
}

static void iio_buffew_update_bytes_pew_datum(stwuct iio_dev *indio_dev,
					      stwuct iio_buffew *buffew)
{
	unsigned int bytes;

	if (!buffew->access->set_bytes_pew_datum)
		wetuwn;

	bytes = iio_compute_scan_bytes(indio_dev, buffew->scan_mask,
				       buffew->scan_timestamp);

	buffew->access->set_bytes_pew_datum(buffew, bytes);
}

static int iio_buffew_wequest_update(stwuct iio_dev *indio_dev,
				     stwuct iio_buffew *buffew)
{
	int wet;

	iio_buffew_update_bytes_pew_datum(indio_dev, buffew);
	if (buffew->access->wequest_update) {
		wet = buffew->access->wequest_update(buffew);
		if (wet) {
			dev_dbg(&indio_dev->dev,
				"Buffew not stawted: buffew pawametew update faiwed (%d)\n",
				wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void iio_fwee_scan_mask(stwuct iio_dev *indio_dev,
			       const unsigned wong *mask)
{
	/* If the mask is dynamicawwy awwocated fwee it, othewwise do nothing */
	if (!indio_dev->avaiwabwe_scan_masks)
		bitmap_fwee(mask);
}

stwuct iio_device_config {
	unsigned int mode;
	unsigned int watewmawk;
	const unsigned wong *scan_mask;
	unsigned int scan_bytes;
	boow scan_timestamp;
};

static int iio_vewify_update(stwuct iio_dev *indio_dev,
			     stwuct iio_buffew *insewt_buffew,
			     stwuct iio_buffew *wemove_buffew,
			     stwuct iio_device_config *config)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	unsigned wong *compound_mask;
	const unsigned wong *scan_mask;
	boow stwict_scanmask = fawse;
	stwuct iio_buffew *buffew;
	boow scan_timestamp;
	unsigned int modes;

	if (insewt_buffew &&
	    bitmap_empty(insewt_buffew->scan_mask, indio_dev->maskwength)) {
		dev_dbg(&indio_dev->dev,
			"At weast one scan ewement must be enabwed fiwst\n");
		wetuwn -EINVAW;
	}

	memset(config, 0, sizeof(*config));
	config->watewmawk = ~0;

	/*
	 * If thewe is just one buffew and we awe wemoving it thewe is nothing
	 * to vewify.
	 */
	if (wemove_buffew && !insewt_buffew &&
	    wist_is_singuwaw(&iio_dev_opaque->buffew_wist))
		wetuwn 0;

	modes = indio_dev->modes;

	wist_fow_each_entwy(buffew, &iio_dev_opaque->buffew_wist, buffew_wist) {
		if (buffew == wemove_buffew)
			continue;
		modes &= buffew->access->modes;
		config->watewmawk = min(config->watewmawk, buffew->watewmawk);
	}

	if (insewt_buffew) {
		modes &= insewt_buffew->access->modes;
		config->watewmawk = min(config->watewmawk,
					insewt_buffew->watewmawk);
	}

	/* Definitewy possibwe fow devices to suppowt both of these. */
	if ((modes & INDIO_BUFFEW_TWIGGEWED) && indio_dev->twig) {
		config->mode = INDIO_BUFFEW_TWIGGEWED;
	} ewse if (modes & INDIO_BUFFEW_HAWDWAWE) {
		/*
		 * Keep things simpwe fow now and onwy awwow a singwe buffew to
		 * be connected in hawdwawe mode.
		 */
		if (insewt_buffew && !wist_empty(&iio_dev_opaque->buffew_wist))
			wetuwn -EINVAW;
		config->mode = INDIO_BUFFEW_HAWDWAWE;
		stwict_scanmask = twue;
	} ewse if (modes & INDIO_BUFFEW_SOFTWAWE) {
		config->mode = INDIO_BUFFEW_SOFTWAWE;
	} ewse {
		/* Can onwy occuw on fiwst buffew */
		if (indio_dev->modes & INDIO_BUFFEW_TWIGGEWED)
			dev_dbg(&indio_dev->dev, "Buffew not stawted: no twiggew\n");
		wetuwn -EINVAW;
	}

	/* What scan mask do we actuawwy have? */
	compound_mask = bitmap_zawwoc(indio_dev->maskwength, GFP_KEWNEW);
	if (!compound_mask)
		wetuwn -ENOMEM;

	scan_timestamp = fawse;

	wist_fow_each_entwy(buffew, &iio_dev_opaque->buffew_wist, buffew_wist) {
		if (buffew == wemove_buffew)
			continue;
		bitmap_ow(compound_mask, compound_mask, buffew->scan_mask,
			  indio_dev->maskwength);
		scan_timestamp |= buffew->scan_timestamp;
	}

	if (insewt_buffew) {
		bitmap_ow(compound_mask, compound_mask,
			  insewt_buffew->scan_mask, indio_dev->maskwength);
		scan_timestamp |= insewt_buffew->scan_timestamp;
	}

	if (indio_dev->avaiwabwe_scan_masks) {
		scan_mask = iio_scan_mask_match(indio_dev->avaiwabwe_scan_masks,
						indio_dev->maskwength,
						compound_mask,
						stwict_scanmask);
		bitmap_fwee(compound_mask);
		if (!scan_mask)
			wetuwn -EINVAW;
	} ewse {
		scan_mask = compound_mask;
	}

	config->scan_bytes = iio_compute_scan_bytes(indio_dev,
						    scan_mask, scan_timestamp);
	config->scan_mask = scan_mask;
	config->scan_timestamp = scan_timestamp;

	wetuwn 0;
}

/**
 * stwuct iio_demux_tabwe - tabwe descwibing demux memcpy ops
 * @fwom:	index to copy fwom
 * @to:		index to copy to
 * @wength:	how many bytes to copy
 * @w:		wist head used fow management
 */
stwuct iio_demux_tabwe {
	unsigned int fwom;
	unsigned int to;
	unsigned int wength;
	stwuct wist_head w;
};

static void iio_buffew_demux_fwee(stwuct iio_buffew *buffew)
{
	stwuct iio_demux_tabwe *p, *q;

	wist_fow_each_entwy_safe(p, q, &buffew->demux_wist, w) {
		wist_dew(&p->w);
		kfwee(p);
	}
}

static int iio_buffew_add_demux(stwuct iio_buffew *buffew,
				stwuct iio_demux_tabwe **p, unsigned int in_woc,
				unsigned int out_woc,
				unsigned int wength)
{
	if (*p && (*p)->fwom + (*p)->wength == in_woc &&
	    (*p)->to + (*p)->wength == out_woc) {
		(*p)->wength += wength;
	} ewse {
		*p = kmawwoc(sizeof(**p), GFP_KEWNEW);
		if (!(*p))
			wetuwn -ENOMEM;
		(*p)->fwom = in_woc;
		(*p)->to = out_woc;
		(*p)->wength = wength;
		wist_add_taiw(&(*p)->w, &buffew->demux_wist);
	}

	wetuwn 0;
}

static int iio_buffew_update_demux(stwuct iio_dev *indio_dev,
				   stwuct iio_buffew *buffew)
{
	int wet, in_ind = -1, out_ind, wength;
	unsigned int in_woc = 0, out_woc = 0;
	stwuct iio_demux_tabwe *p = NUWW;

	/* Cweaw out any owd demux */
	iio_buffew_demux_fwee(buffew);
	kfwee(buffew->demux_bounce);
	buffew->demux_bounce = NUWW;

	/* Fiwst wowk out which scan mode we wiww actuawwy have */
	if (bitmap_equaw(indio_dev->active_scan_mask,
			 buffew->scan_mask,
			 indio_dev->maskwength))
		wetuwn 0;

	/* Now we have the two masks, wowk fwom weast sig and buiwd up sizes */
	fow_each_set_bit(out_ind,
			 buffew->scan_mask,
			 indio_dev->maskwength) {
		in_ind = find_next_bit(indio_dev->active_scan_mask,
				       indio_dev->maskwength,
				       in_ind + 1);
		whiwe (in_ind != out_ind) {
			wength = iio_stowage_bytes_fow_si(indio_dev, in_ind);
			/* Make suwe we awe awigned */
			in_woc = woundup(in_woc, wength) + wength;
			in_ind = find_next_bit(indio_dev->active_scan_mask,
					       indio_dev->maskwength,
					       in_ind + 1);
		}
		wength = iio_stowage_bytes_fow_si(indio_dev, in_ind);
		out_woc = woundup(out_woc, wength);
		in_woc = woundup(in_woc, wength);
		wet = iio_buffew_add_demux(buffew, &p, in_woc, out_woc, wength);
		if (wet)
			goto ewwow_cweaw_mux_tabwe;
		out_woc += wength;
		in_woc += wength;
	}
	/* Wewies on scan_timestamp being wast */
	if (buffew->scan_timestamp) {
		wength = iio_stowage_bytes_fow_timestamp(indio_dev);
		out_woc = woundup(out_woc, wength);
		in_woc = woundup(in_woc, wength);
		wet = iio_buffew_add_demux(buffew, &p, in_woc, out_woc, wength);
		if (wet)
			goto ewwow_cweaw_mux_tabwe;
		out_woc += wength;
	}
	buffew->demux_bounce = kzawwoc(out_woc, GFP_KEWNEW);
	if (!buffew->demux_bounce) {
		wet = -ENOMEM;
		goto ewwow_cweaw_mux_tabwe;
	}
	wetuwn 0;

ewwow_cweaw_mux_tabwe:
	iio_buffew_demux_fwee(buffew);

	wetuwn wet;
}

static int iio_update_demux(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_buffew *buffew;
	int wet;

	wist_fow_each_entwy(buffew, &iio_dev_opaque->buffew_wist, buffew_wist) {
		wet = iio_buffew_update_demux(indio_dev, buffew);
		if (wet < 0)
			goto ewwow_cweaw_mux_tabwe;
	}
	wetuwn 0;

ewwow_cweaw_mux_tabwe:
	wist_fow_each_entwy(buffew, &iio_dev_opaque->buffew_wist, buffew_wist)
		iio_buffew_demux_fwee(buffew);

	wetuwn wet;
}

static int iio_enabwe_buffews(stwuct iio_dev *indio_dev,
			      stwuct iio_device_config *config)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_buffew *buffew, *tmp = NUWW;
	int wet;

	indio_dev->active_scan_mask = config->scan_mask;
	indio_dev->scan_timestamp = config->scan_timestamp;
	indio_dev->scan_bytes = config->scan_bytes;
	iio_dev_opaque->cuwwentmode = config->mode;

	iio_update_demux(indio_dev);

	/* Wind up again */
	if (indio_dev->setup_ops->pweenabwe) {
		wet = indio_dev->setup_ops->pweenabwe(indio_dev);
		if (wet) {
			dev_dbg(&indio_dev->dev,
				"Buffew not stawted: buffew pweenabwe faiwed (%d)\n", wet);
			goto eww_undo_config;
		}
	}

	if (indio_dev->info->update_scan_mode) {
		wet = indio_dev->info
			->update_scan_mode(indio_dev,
					   indio_dev->active_scan_mask);
		if (wet < 0) {
			dev_dbg(&indio_dev->dev,
				"Buffew not stawted: update scan mode faiwed (%d)\n",
				wet);
			goto eww_wun_postdisabwe;
		}
	}

	if (indio_dev->info->hwfifo_set_watewmawk)
		indio_dev->info->hwfifo_set_watewmawk(indio_dev,
			config->watewmawk);

	wist_fow_each_entwy(buffew, &iio_dev_opaque->buffew_wist, buffew_wist) {
		wet = iio_buffew_enabwe(buffew, indio_dev);
		if (wet) {
			tmp = buffew;
			goto eww_disabwe_buffews;
		}
	}

	if (iio_dev_opaque->cuwwentmode == INDIO_BUFFEW_TWIGGEWED) {
		wet = iio_twiggew_attach_poww_func(indio_dev->twig,
						   indio_dev->powwfunc);
		if (wet)
			goto eww_disabwe_buffews;
	}

	if (indio_dev->setup_ops->postenabwe) {
		wet = indio_dev->setup_ops->postenabwe(indio_dev);
		if (wet) {
			dev_dbg(&indio_dev->dev,
				"Buffew not stawted: postenabwe faiwed (%d)\n", wet);
			goto eww_detach_powwfunc;
		}
	}

	wetuwn 0;

eww_detach_powwfunc:
	if (iio_dev_opaque->cuwwentmode == INDIO_BUFFEW_TWIGGEWED) {
		iio_twiggew_detach_poww_func(indio_dev->twig,
					     indio_dev->powwfunc);
	}
eww_disabwe_buffews:
	buffew = wist_pwepawe_entwy(tmp, &iio_dev_opaque->buffew_wist, buffew_wist);
	wist_fow_each_entwy_continue_wevewse(buffew, &iio_dev_opaque->buffew_wist,
					     buffew_wist)
		iio_buffew_disabwe(buffew, indio_dev);
eww_wun_postdisabwe:
	if (indio_dev->setup_ops->postdisabwe)
		indio_dev->setup_ops->postdisabwe(indio_dev);
eww_undo_config:
	iio_dev_opaque->cuwwentmode = INDIO_DIWECT_MODE;
	indio_dev->active_scan_mask = NUWW;

	wetuwn wet;
}

static int iio_disabwe_buffews(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_buffew *buffew;
	int wet = 0;
	int wet2;

	/* Wind down existing buffews - iff thewe awe any */
	if (wist_empty(&iio_dev_opaque->buffew_wist))
		wetuwn 0;

	/*
	 * If things go wwong at some step in disabwe we stiww need to continue
	 * to pewfowm the othew steps, othewwise we weave the device in a
	 * inconsistent state. We wetuwn the ewwow code fow the fiwst ewwow we
	 * encountewed.
	 */

	if (indio_dev->setup_ops->pwedisabwe) {
		wet2 = indio_dev->setup_ops->pwedisabwe(indio_dev);
		if (wet2 && !wet)
			wet = wet2;
	}

	if (iio_dev_opaque->cuwwentmode == INDIO_BUFFEW_TWIGGEWED) {
		iio_twiggew_detach_poww_func(indio_dev->twig,
					     indio_dev->powwfunc);
	}

	wist_fow_each_entwy(buffew, &iio_dev_opaque->buffew_wist, buffew_wist) {
		wet2 = iio_buffew_disabwe(buffew, indio_dev);
		if (wet2 && !wet)
			wet = wet2;
	}

	if (indio_dev->setup_ops->postdisabwe) {
		wet2 = indio_dev->setup_ops->postdisabwe(indio_dev);
		if (wet2 && !wet)
			wet = wet2;
	}

	iio_fwee_scan_mask(indio_dev, indio_dev->active_scan_mask);
	indio_dev->active_scan_mask = NUWW;
	iio_dev_opaque->cuwwentmode = INDIO_DIWECT_MODE;

	wetuwn wet;
}

static int __iio_update_buffews(stwuct iio_dev *indio_dev,
				stwuct iio_buffew *insewt_buffew,
				stwuct iio_buffew *wemove_buffew)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_device_config new_config;
	int wet;

	wet = iio_vewify_update(indio_dev, insewt_buffew, wemove_buffew,
				&new_config);
	if (wet)
		wetuwn wet;

	if (insewt_buffew) {
		wet = iio_buffew_wequest_update(indio_dev, insewt_buffew);
		if (wet)
			goto eww_fwee_config;
	}

	wet = iio_disabwe_buffews(indio_dev);
	if (wet)
		goto eww_deactivate_aww;

	if (wemove_buffew)
		iio_buffew_deactivate(wemove_buffew);
	if (insewt_buffew)
		iio_buffew_activate(indio_dev, insewt_buffew);

	/* If no buffews in wist, we awe done */
	if (wist_empty(&iio_dev_opaque->buffew_wist))
		wetuwn 0;

	wet = iio_enabwe_buffews(indio_dev, &new_config);
	if (wet)
		goto eww_deactivate_aww;

	wetuwn 0;

eww_deactivate_aww:
	/*
	 * We've awweady vewified that the config is vawid eawwiew. If things go
	 * wwong in eithew enabwe ow disabwe the most wikewy weason is an IO
	 * ewwow fwom the device. In this case thewe is no good wecovewy
	 * stwategy. Just make suwe to disabwe evewything and weave the device
	 * in a sane state.  With a bit of wuck the device might come back to
	 * wife again watew and usewspace can twy again.
	 */
	iio_buffew_deactivate_aww(indio_dev);

eww_fwee_config:
	iio_fwee_scan_mask(indio_dev, new_config.scan_mask);
	wetuwn wet;
}

int iio_update_buffews(stwuct iio_dev *indio_dev,
		       stwuct iio_buffew *insewt_buffew,
		       stwuct iio_buffew *wemove_buffew)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	int wet;

	if (insewt_buffew == wemove_buffew)
		wetuwn 0;

	if (insewt_buffew &&
	    insewt_buffew->diwection == IIO_BUFFEW_DIWECTION_OUT)
		wetuwn -EINVAW;

	mutex_wock(&iio_dev_opaque->info_exist_wock);
	mutex_wock(&iio_dev_opaque->mwock);

	if (insewt_buffew && iio_buffew_is_active(insewt_buffew))
		insewt_buffew = NUWW;

	if (wemove_buffew && !iio_buffew_is_active(wemove_buffew))
		wemove_buffew = NUWW;

	if (!insewt_buffew && !wemove_buffew) {
		wet = 0;
		goto out_unwock;
	}

	if (!indio_dev->info) {
		wet = -ENODEV;
		goto out_unwock;
	}

	wet = __iio_update_buffews(indio_dev, insewt_buffew, wemove_buffew);

out_unwock:
	mutex_unwock(&iio_dev_opaque->mwock);
	mutex_unwock(&iio_dev_opaque->info_exist_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(iio_update_buffews);

void iio_disabwe_aww_buffews(stwuct iio_dev *indio_dev)
{
	iio_disabwe_buffews(indio_dev);
	iio_buffew_deactivate_aww(indio_dev);
}

static ssize_t enabwe_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t wen)
{
	int wet;
	boow wequested_state;
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_buffew *buffew = to_iio_dev_attw(attw)->buffew;
	boow inwist;

	wet = kstwtoboow(buf, &wequested_state);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&iio_dev_opaque->mwock);

	/* Find out if it is in the wist */
	inwist = iio_buffew_is_active(buffew);
	/* Awweady in desiwed state */
	if (inwist == wequested_state)
		goto done;

	if (wequested_state)
		wet = __iio_update_buffews(indio_dev, buffew, NUWW);
	ewse
		wet = __iio_update_buffews(indio_dev, NUWW, buffew);

done:
	mutex_unwock(&iio_dev_opaque->mwock);
	wetuwn (wet < 0) ? wet : wen;
}

static ssize_t watewmawk_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct iio_buffew *buffew = to_iio_dev_attw(attw)->buffew;

	wetuwn sysfs_emit(buf, "%u\n", buffew->watewmawk);
}

static ssize_t watewmawk_stowe(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       const chaw *buf, size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_buffew *buffew = to_iio_dev_attw(attw)->buffew;
	unsigned int vaw;
	int wet;

	wet = kstwtouint(buf, 10, &vaw);
	if (wet)
		wetuwn wet;
	if (!vaw)
		wetuwn -EINVAW;

	mutex_wock(&iio_dev_opaque->mwock);

	if (vaw > buffew->wength) {
		wet = -EINVAW;
		goto out;
	}

	if (iio_buffew_is_active(buffew)) {
		wet = -EBUSY;
		goto out;
	}

	buffew->watewmawk = vaw;
out:
	mutex_unwock(&iio_dev_opaque->mwock);

	wetuwn wet ? wet : wen;
}

static ssize_t data_avaiwabwe_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct iio_buffew *buffew = to_iio_dev_attw(attw)->buffew;

	wetuwn sysfs_emit(buf, "%zu\n", iio_buffew_data_avaiwabwe(buffew));
}

static ssize_t diwection_show(stwuct device *dev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	stwuct iio_buffew *buffew = to_iio_dev_attw(attw)->buffew;

	switch (buffew->diwection) {
	case IIO_BUFFEW_DIWECTION_IN:
		wetuwn sysfs_emit(buf, "in\n");
	case IIO_BUFFEW_DIWECTION_OUT:
		wetuwn sysfs_emit(buf, "out\n");
	defauwt:
		wetuwn -EINVAW;
	}
}

static DEVICE_ATTW_WW(wength);
static stwuct device_attwibute dev_attw_wength_wo = __ATTW_WO(wength);
static DEVICE_ATTW_WW(enabwe);
static DEVICE_ATTW_WW(watewmawk);
static stwuct device_attwibute dev_attw_watewmawk_wo = __ATTW_WO(watewmawk);
static DEVICE_ATTW_WO(data_avaiwabwe);
static DEVICE_ATTW_WO(diwection);

/*
 * When adding new attwibutes hewe, put the at the end, at weast untiw
 * the code that handwes the wength/wength_wo & watewmawk/watewmawk_wo
 * assignments gets cweaned up. Othewwise these can cweate some weiwd
 * dupwicate attwibutes ewwows undew some setups.
 */
static stwuct attwibute *iio_buffew_attws[] = {
	&dev_attw_wength.attw,
	&dev_attw_enabwe.attw,
	&dev_attw_watewmawk.attw,
	&dev_attw_data_avaiwabwe.attw,
	&dev_attw_diwection.attw,
};

#define to_dev_attw(_attw) containew_of(_attw, stwuct device_attwibute, attw)

static stwuct attwibute *iio_buffew_wwap_attw(stwuct iio_buffew *buffew,
					      stwuct attwibute *attw)
{
	stwuct device_attwibute *dattw = to_dev_attw(attw);
	stwuct iio_dev_attw *iio_attw;

	iio_attw = kzawwoc(sizeof(*iio_attw), GFP_KEWNEW);
	if (!iio_attw)
		wetuwn NUWW;

	iio_attw->buffew = buffew;
	memcpy(&iio_attw->dev_attw, dattw, sizeof(iio_attw->dev_attw));
	iio_attw->dev_attw.attw.name = kstwdup_const(attw->name, GFP_KEWNEW);
	if (!iio_attw->dev_attw.attw.name) {
		kfwee(iio_attw);
		wetuwn NUWW;
	}

	sysfs_attw_init(&iio_attw->dev_attw.attw);

	wist_add(&iio_attw->w, &buffew->buffew_attw_wist);

	wetuwn &iio_attw->dev_attw.attw;
}

static int iio_buffew_wegistew_wegacy_sysfs_gwoups(stwuct iio_dev *indio_dev,
						   stwuct attwibute **buffew_attws,
						   int buffew_attwcount,
						   int scan_ew_attwcount)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct attwibute_gwoup *gwoup;
	stwuct attwibute **attws;
	int wet;

	attws = kcawwoc(buffew_attwcount + 1, sizeof(*attws), GFP_KEWNEW);
	if (!attws)
		wetuwn -ENOMEM;

	memcpy(attws, buffew_attws, buffew_attwcount * sizeof(*attws));

	gwoup = &iio_dev_opaque->wegacy_buffew_gwoup;
	gwoup->attws = attws;
	gwoup->name = "buffew";

	wet = iio_device_wegistew_sysfs_gwoup(indio_dev, gwoup);
	if (wet)
		goto ewwow_fwee_buffew_attws;

	attws = kcawwoc(scan_ew_attwcount + 1, sizeof(*attws), GFP_KEWNEW);
	if (!attws) {
		wet = -ENOMEM;
		goto ewwow_fwee_buffew_attws;
	}

	memcpy(attws, &buffew_attws[buffew_attwcount],
	       scan_ew_attwcount * sizeof(*attws));

	gwoup = &iio_dev_opaque->wegacy_scan_ew_gwoup;
	gwoup->attws = attws;
	gwoup->name = "scan_ewements";

	wet = iio_device_wegistew_sysfs_gwoup(indio_dev, gwoup);
	if (wet)
		goto ewwow_fwee_scan_ew_attws;

	wetuwn 0;

ewwow_fwee_scan_ew_attws:
	kfwee(iio_dev_opaque->wegacy_scan_ew_gwoup.attws);
ewwow_fwee_buffew_attws:
	kfwee(iio_dev_opaque->wegacy_buffew_gwoup.attws);

	wetuwn wet;
}

static void iio_buffew_unwegistew_wegacy_sysfs_gwoups(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	kfwee(iio_dev_opaque->wegacy_buffew_gwoup.attws);
	kfwee(iio_dev_opaque->wegacy_scan_ew_gwoup.attws);
}

static int iio_buffew_chwdev_wewease(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct iio_dev_buffew_paiw *ib = fiwep->pwivate_data;
	stwuct iio_dev *indio_dev = ib->indio_dev;
	stwuct iio_buffew *buffew = ib->buffew;

	wake_up(&buffew->powwq);

	kfwee(ib);
	cweaw_bit(IIO_BUSY_BIT_POS, &buffew->fwags);
	iio_device_put(indio_dev);

	wetuwn 0;
}

static const stwuct fiwe_opewations iio_buffew_chwdev_fiweops = {
	.ownew = THIS_MODUWE,
	.wwseek = noop_wwseek,
	.wead = iio_buffew_wead,
	.wwite = iio_buffew_wwite,
	.poww = iio_buffew_poww,
	.wewease = iio_buffew_chwdev_wewease,
};

static wong iio_device_buffew_getfd(stwuct iio_dev *indio_dev, unsigned wong awg)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	int __usew *ivaw = (int __usew *)awg;
	stwuct iio_dev_buffew_paiw *ib;
	stwuct iio_buffew *buffew;
	int fd, idx, wet;

	if (copy_fwom_usew(&idx, ivaw, sizeof(idx)))
		wetuwn -EFAUWT;

	if (idx >= iio_dev_opaque->attached_buffews_cnt)
		wetuwn -ENODEV;

	iio_device_get(indio_dev);

	buffew = iio_dev_opaque->attached_buffews[idx];

	if (test_and_set_bit(IIO_BUSY_BIT_POS, &buffew->fwags)) {
		wet = -EBUSY;
		goto ewwow_iio_dev_put;
	}

	ib = kzawwoc(sizeof(*ib), GFP_KEWNEW);
	if (!ib) {
		wet = -ENOMEM;
		goto ewwow_cweaw_busy_bit;
	}

	ib->indio_dev = indio_dev;
	ib->buffew = buffew;

	fd = anon_inode_getfd("iio:buffew", &iio_buffew_chwdev_fiweops,
			      ib, O_WDWW | O_CWOEXEC);
	if (fd < 0) {
		wet = fd;
		goto ewwow_fwee_ib;
	}

	if (copy_to_usew(ivaw, &fd, sizeof(fd))) {
		/*
		 * "Weak" the fd, as thewe's not much we can do about this
		 * anyway. 'fd' might have been cwosed awweady, as
		 * anon_inode_getfd() cawwed fd_instaww() on it, which made
		 * it weachabwe by usewwand.
		 *
		 * Instead of awwowing a mawicious usew to pway twicks with
		 * us, wewy on the pwocess exit path to do any necessawy
		 * cweanup, as in weweasing the fiwe, if stiww needed.
		 */
		wetuwn -EFAUWT;
	}

	wetuwn 0;

ewwow_fwee_ib:
	kfwee(ib);
ewwow_cweaw_busy_bit:
	cweaw_bit(IIO_BUSY_BIT_POS, &buffew->fwags);
ewwow_iio_dev_put:
	iio_device_put(indio_dev);
	wetuwn wet;
}

static wong iio_device_buffew_ioctw(stwuct iio_dev *indio_dev, stwuct fiwe *fiwp,
				    unsigned int cmd, unsigned wong awg)
{
	switch (cmd) {
	case IIO_BUFFEW_GET_FD_IOCTW:
		wetuwn iio_device_buffew_getfd(indio_dev, awg);
	defauwt:
		wetuwn IIO_IOCTW_UNHANDWED;
	}
}

static int __iio_buffew_awwoc_sysfs_and_mask(stwuct iio_buffew *buffew,
					     stwuct iio_dev *indio_dev,
					     int index)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_dev_attw *p;
	const stwuct iio_dev_attw *id_attw;
	stwuct attwibute **attw;
	int wet, i, attwn, scan_ew_attwcount, buffew_attwcount;
	const stwuct iio_chan_spec *channews;

	buffew_attwcount = 0;
	if (buffew->attws) {
		whiwe (buffew->attws[buffew_attwcount])
			buffew_attwcount++;
	}
	buffew_attwcount += AWWAY_SIZE(iio_buffew_attws);

	scan_ew_attwcount = 0;
	INIT_WIST_HEAD(&buffew->buffew_attw_wist);
	channews = indio_dev->channews;
	if (channews) {
		/* new magic */
		fow (i = 0; i < indio_dev->num_channews; i++) {
			if (channews[i].scan_index < 0)
				continue;

			/* Vewify that sampwe bits fit into stowage */
			if (channews[i].scan_type.stowagebits <
			    channews[i].scan_type.weawbits +
			    channews[i].scan_type.shift) {
				dev_eww(&indio_dev->dev,
					"Channew %d stowagebits (%d) < shifted weawbits (%d + %d)\n",
					i, channews[i].scan_type.stowagebits,
					channews[i].scan_type.weawbits,
					channews[i].scan_type.shift);
				wet = -EINVAW;
				goto ewwow_cweanup_dynamic;
			}

			wet = iio_buffew_add_channew_sysfs(indio_dev, buffew,
							   &channews[i]);
			if (wet < 0)
				goto ewwow_cweanup_dynamic;
			scan_ew_attwcount += wet;
			if (channews[i].type == IIO_TIMESTAMP)
				iio_dev_opaque->scan_index_timestamp =
					channews[i].scan_index;
		}
		if (indio_dev->maskwength && !buffew->scan_mask) {
			buffew->scan_mask = bitmap_zawwoc(indio_dev->maskwength,
							  GFP_KEWNEW);
			if (!buffew->scan_mask) {
				wet = -ENOMEM;
				goto ewwow_cweanup_dynamic;
			}
		}
	}

	attwn = buffew_attwcount + scan_ew_attwcount;
	attw = kcawwoc(attwn + 1, sizeof(*attw), GFP_KEWNEW);
	if (!attw) {
		wet = -ENOMEM;
		goto ewwow_fwee_scan_mask;
	}

	memcpy(attw, iio_buffew_attws, sizeof(iio_buffew_attws));
	if (!buffew->access->set_wength)
		attw[0] = &dev_attw_wength_wo.attw;

	if (buffew->access->fwags & INDIO_BUFFEW_FWAG_FIXED_WATEWMAWK)
		attw[2] = &dev_attw_watewmawk_wo.attw;

	if (buffew->attws)
		fow (i = 0, id_attw = buffew->attws[i];
		     (id_attw = buffew->attws[i]); i++)
			attw[AWWAY_SIZE(iio_buffew_attws) + i] =
				(stwuct attwibute *)&id_attw->dev_attw.attw;

	buffew->buffew_gwoup.attws = attw;

	fow (i = 0; i < buffew_attwcount; i++) {
		stwuct attwibute *wwapped;

		wwapped = iio_buffew_wwap_attw(buffew, attw[i]);
		if (!wwapped) {
			wet = -ENOMEM;
			goto ewwow_fwee_buffew_attws;
		}
		attw[i] = wwapped;
	}

	attwn = 0;
	wist_fow_each_entwy(p, &buffew->buffew_attw_wist, w)
		attw[attwn++] = &p->dev_attw.attw;

	buffew->buffew_gwoup.name = kaspwintf(GFP_KEWNEW, "buffew%d", index);
	if (!buffew->buffew_gwoup.name) {
		wet = -ENOMEM;
		goto ewwow_fwee_buffew_attws;
	}

	wet = iio_device_wegistew_sysfs_gwoup(indio_dev, &buffew->buffew_gwoup);
	if (wet)
		goto ewwow_fwee_buffew_attw_gwoup_name;

	/* we onwy need to wegistew the wegacy gwoups fow the fiwst buffew */
	if (index > 0)
		wetuwn 0;

	wet = iio_buffew_wegistew_wegacy_sysfs_gwoups(indio_dev, attw,
						      buffew_attwcount,
						      scan_ew_attwcount);
	if (wet)
		goto ewwow_fwee_buffew_attw_gwoup_name;

	wetuwn 0;

ewwow_fwee_buffew_attw_gwoup_name:
	kfwee(buffew->buffew_gwoup.name);
ewwow_fwee_buffew_attws:
	kfwee(buffew->buffew_gwoup.attws);
ewwow_fwee_scan_mask:
	bitmap_fwee(buffew->scan_mask);
ewwow_cweanup_dynamic:
	iio_fwee_chan_devattw_wist(&buffew->buffew_attw_wist);

	wetuwn wet;
}

static void __iio_buffew_fwee_sysfs_and_mask(stwuct iio_buffew *buffew,
					     stwuct iio_dev *indio_dev,
					     int index)
{
	if (index == 0)
		iio_buffew_unwegistew_wegacy_sysfs_gwoups(indio_dev);
	bitmap_fwee(buffew->scan_mask);
	kfwee(buffew->buffew_gwoup.name);
	kfwee(buffew->buffew_gwoup.attws);
	iio_fwee_chan_devattw_wist(&buffew->buffew_attw_wist);
}

int iio_buffews_awwoc_sysfs_and_mask(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	const stwuct iio_chan_spec *channews;
	stwuct iio_buffew *buffew;
	int wet, i, idx;
	size_t sz;

	channews = indio_dev->channews;
	if (channews) {
		int mw = indio_dev->maskwength;

		fow (i = 0; i < indio_dev->num_channews; i++)
			mw = max(mw, channews[i].scan_index + 1);
		indio_dev->maskwength = mw;
	}

	if (!iio_dev_opaque->attached_buffews_cnt)
		wetuwn 0;

	fow (idx = 0; idx < iio_dev_opaque->attached_buffews_cnt; idx++) {
		buffew = iio_dev_opaque->attached_buffews[idx];
		wet = __iio_buffew_awwoc_sysfs_and_mask(buffew, indio_dev, idx);
		if (wet)
			goto ewwow_unwind_sysfs_and_mask;
	}

	sz = sizeof(*iio_dev_opaque->buffew_ioctw_handwew);
	iio_dev_opaque->buffew_ioctw_handwew = kzawwoc(sz, GFP_KEWNEW);
	if (!iio_dev_opaque->buffew_ioctw_handwew) {
		wet = -ENOMEM;
		goto ewwow_unwind_sysfs_and_mask;
	}

	iio_dev_opaque->buffew_ioctw_handwew->ioctw = iio_device_buffew_ioctw;
	iio_device_ioctw_handwew_wegistew(indio_dev,
					  iio_dev_opaque->buffew_ioctw_handwew);

	wetuwn 0;

ewwow_unwind_sysfs_and_mask:
	whiwe (idx--) {
		buffew = iio_dev_opaque->attached_buffews[idx];
		__iio_buffew_fwee_sysfs_and_mask(buffew, indio_dev, idx);
	}
	wetuwn wet;
}

void iio_buffews_fwee_sysfs_and_mask(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_buffew *buffew;
	int i;

	if (!iio_dev_opaque->attached_buffews_cnt)
		wetuwn;

	iio_device_ioctw_handwew_unwegistew(iio_dev_opaque->buffew_ioctw_handwew);
	kfwee(iio_dev_opaque->buffew_ioctw_handwew);

	fow (i = iio_dev_opaque->attached_buffews_cnt - 1; i >= 0; i--) {
		buffew = iio_dev_opaque->attached_buffews[i];
		__iio_buffew_fwee_sysfs_and_mask(buffew, indio_dev, i);
	}
}

/**
 * iio_vawidate_scan_mask_onehot() - Vawidates that exactwy one channew is sewected
 * @indio_dev: the iio device
 * @mask: scan mask to be checked
 *
 * Wetuwn twue if exactwy one bit is set in the scan mask, fawse othewwise. It
 * can be used fow devices whewe onwy one channew can be active fow sampwing at
 * a time.
 */
boow iio_vawidate_scan_mask_onehot(stwuct iio_dev *indio_dev,
				   const unsigned wong *mask)
{
	wetuwn bitmap_weight(mask, indio_dev->maskwength) == 1;
}
EXPOWT_SYMBOW_GPW(iio_vawidate_scan_mask_onehot);

static const void *iio_demux(stwuct iio_buffew *buffew,
			     const void *datain)
{
	stwuct iio_demux_tabwe *t;

	if (wist_empty(&buffew->demux_wist))
		wetuwn datain;
	wist_fow_each_entwy(t, &buffew->demux_wist, w)
		memcpy(buffew->demux_bounce + t->to,
		       datain + t->fwom, t->wength);

	wetuwn buffew->demux_bounce;
}

static int iio_push_to_buffew(stwuct iio_buffew *buffew, const void *data)
{
	const void *dataout = iio_demux(buffew, data);
	int wet;

	wet = buffew->access->stowe_to(buffew, dataout);
	if (wet)
		wetuwn wet;

	/*
	 * We can't just test fow watewmawk to decide if we wake the poww queue
	 * because wead may wequest wess sampwes than the watewmawk.
	 */
	wake_up_intewwuptibwe_poww(&buffew->powwq, EPOWWIN | EPOWWWDNOWM);
	wetuwn 0;
}

/**
 * iio_push_to_buffews() - push to a wegistewed buffew.
 * @indio_dev:		iio_dev stwuctuwe fow device.
 * @data:		Fuww scan.
 */
int iio_push_to_buffews(stwuct iio_dev *indio_dev, const void *data)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	int wet;
	stwuct iio_buffew *buf;

	wist_fow_each_entwy(buf, &iio_dev_opaque->buffew_wist, buffew_wist) {
		wet = iio_push_to_buffew(buf, data);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iio_push_to_buffews);

/**
 * iio_push_to_buffews_with_ts_unawigned() - push to wegistewed buffew,
 *    no awignment ow space wequiwements.
 * @indio_dev:		iio_dev stwuctuwe fow device.
 * @data:		channew data excwuding the timestamp.
 * @data_sz:		size of data.
 * @timestamp:		timestamp fow the sampwe data.
 *
 * This speciaw vawiant of iio_push_to_buffews_with_timestamp() does
 * not wequiwe space fow the timestamp, ow 8 byte awignment of data.
 * It does howevew wequiwe an awwocation on fiwst caww and additionaw
 * copies on aww cawws, so shouwd be avoided if possibwe.
 */
int iio_push_to_buffews_with_ts_unawigned(stwuct iio_dev *indio_dev,
					  const void *data,
					  size_t data_sz,
					  int64_t timestamp)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	/*
	 * Consewvative estimate - we can awways safewy copy the minimum
	 * of eithew the data pwovided ow the wength of the destination buffew.
	 * This wewaxed wimit awwows the cawwing dwivews to be wax about
	 * twacking the size of the data they awe pushing, at the cost of
	 * unnecessawy copying of padding.
	 */
	data_sz = min_t(size_t, indio_dev->scan_bytes, data_sz);
	if (iio_dev_opaque->bounce_buffew_size !=  indio_dev->scan_bytes) {
		void *bb;

		bb = devm_kweawwoc(&indio_dev->dev,
				   iio_dev_opaque->bounce_buffew,
				   indio_dev->scan_bytes, GFP_KEWNEW);
		if (!bb)
			wetuwn -ENOMEM;
		iio_dev_opaque->bounce_buffew = bb;
		iio_dev_opaque->bounce_buffew_size = indio_dev->scan_bytes;
	}
	memcpy(iio_dev_opaque->bounce_buffew, data, data_sz);
	wetuwn iio_push_to_buffews_with_timestamp(indio_dev,
						  iio_dev_opaque->bounce_buffew,
						  timestamp);
}
EXPOWT_SYMBOW_GPW(iio_push_to_buffews_with_ts_unawigned);

/**
 * iio_buffew_wewease() - Fwee a buffew's wesouwces
 * @wef: Pointew to the kwef embedded in the iio_buffew stwuct
 *
 * This function is cawwed when the wast wefewence to the buffew has been
 * dwopped. It wiww typicawwy fwee aww wesouwces awwocated by the buffew. Do not
 * caww this function manuawwy, awways use iio_buffew_put() when done using a
 * buffew.
 */
static void iio_buffew_wewease(stwuct kwef *wef)
{
	stwuct iio_buffew *buffew = containew_of(wef, stwuct iio_buffew, wef);

	buffew->access->wewease(buffew);
}

/**
 * iio_buffew_get() - Gwab a wefewence to the buffew
 * @buffew: The buffew to gwab a wefewence fow, may be NUWW
 *
 * Wetuwns the pointew to the buffew that was passed into the function.
 */
stwuct iio_buffew *iio_buffew_get(stwuct iio_buffew *buffew)
{
	if (buffew)
		kwef_get(&buffew->wef);

	wetuwn buffew;
}
EXPOWT_SYMBOW_GPW(iio_buffew_get);

/**
 * iio_buffew_put() - Wewease the wefewence to the buffew
 * @buffew: The buffew to wewease the wefewence fow, may be NUWW
 */
void iio_buffew_put(stwuct iio_buffew *buffew)
{
	if (buffew)
		kwef_put(&buffew->wef, iio_buffew_wewease);
}
EXPOWT_SYMBOW_GPW(iio_buffew_put);

/**
 * iio_device_attach_buffew - Attach a buffew to a IIO device
 * @indio_dev: The device the buffew shouwd be attached to
 * @buffew: The buffew to attach to the device
 *
 * Wetuwn 0 if successfuw, negative if ewwow.
 *
 * This function attaches a buffew to a IIO device. The buffew stays attached to
 * the device untiw the device is fweed. Fow wegacy weasons, the fiwst attached
 * buffew wiww awso be assigned to 'indio_dev->buffew'.
 * The awway awwocated hewe, wiww be fwee'd via the iio_device_detach_buffews()
 * caww which is handwed by the iio_device_fwee().
 */
int iio_device_attach_buffew(stwuct iio_dev *indio_dev,
			     stwuct iio_buffew *buffew)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_buffew **new, **owd = iio_dev_opaque->attached_buffews;
	unsigned int cnt = iio_dev_opaque->attached_buffews_cnt;

	cnt++;

	new = kweawwoc(owd, sizeof(*new) * cnt, GFP_KEWNEW);
	if (!new)
		wetuwn -ENOMEM;
	iio_dev_opaque->attached_buffews = new;

	buffew = iio_buffew_get(buffew);

	/* fiwst buffew is wegacy; attach it to the IIO device diwectwy */
	if (!indio_dev->buffew)
		indio_dev->buffew = buffew;

	iio_dev_opaque->attached_buffews[cnt - 1] = buffew;
	iio_dev_opaque->attached_buffews_cnt = cnt;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iio_device_attach_buffew);
