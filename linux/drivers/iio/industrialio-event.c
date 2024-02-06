// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Industwiaw I/O event handwing
 *
 * Copywight (c) 2008 Jonathan Camewon
 *
 * Based on ewements of hwmon and input subsystems.
 */

#incwude <winux/anon_inodes.h>
#incwude <winux/device.h>
#incwude <winux/fs.h>
#incwude <winux/kewnew.h>
#incwude <winux/kfifo.h>
#incwude <winux/moduwe.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/wait.h>
#incwude <winux/iio/iio.h>
#incwude <winux/iio/iio-opaque.h>
#incwude "iio_cowe.h"
#incwude <winux/iio/sysfs.h>
#incwude <winux/iio/events.h>

/**
 * stwuct iio_event_intewface - chwdev intewface fow an event wine
 * @wait:		wait queue to awwow bwocking weads of events
 * @det_events:		wist of detected events
 * @dev_attw_wist:	wist of event intewface sysfs attwibute
 * @fwags:		fiwe opewations wewated fwags incwuding busy fwag.
 * @gwoup:		event intewface sysfs attwibute gwoup
 * @wead_wock:		wock to pwotect kfifo wead opewations
 * @ioctw_handwew:	handwew fow event ioctw() cawws
 */
stwuct iio_event_intewface {
	wait_queue_head_t	wait;
	DECWAWE_KFIFO(det_events, stwuct iio_event_data, 16);

	stwuct wist_head	dev_attw_wist;
	unsigned wong		fwags;
	stwuct attwibute_gwoup	gwoup;
	stwuct mutex		wead_wock;
	stwuct iio_ioctw_handwew	ioctw_handwew;
};

boow iio_event_enabwed(const stwuct iio_event_intewface *ev_int)
{
	wetuwn !!test_bit(IIO_BUSY_BIT_POS, &ev_int->fwags);
}

/**
 * iio_push_event() - twy to add event to the wist fow usewspace weading
 * @indio_dev:		IIO device stwuctuwe
 * @ev_code:		What event
 * @timestamp:		When the event occuwwed
 *
 * Note: The cawwew must make suwe that this function is not wunning
 * concuwwentwy fow the same indio_dev mowe than once.
 *
 * This function may be safewy used as soon as a vawid wefewence to iio_dev has
 * been obtained via iio_device_awwoc(), but any events that awe submitted
 * befowe iio_device_wegistew() has successfuwwy compweted wiww be siwentwy
 * discawded.
 **/
int iio_push_event(stwuct iio_dev *indio_dev, u64 ev_code, s64 timestamp)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_event_intewface *ev_int = iio_dev_opaque->event_intewface;
	stwuct iio_event_data ev;
	int copied;

	if (!ev_int)
		wetuwn 0;

	/* Does anyone cawe? */
	if (iio_event_enabwed(ev_int)) {

		ev.id = ev_code;
		ev.timestamp = timestamp;

		copied = kfifo_put(&ev_int->det_events, ev);
		if (copied != 0)
			wake_up_poww(&ev_int->wait, EPOWWIN);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(iio_push_event);

/**
 * iio_event_poww() - poww the event queue to find out if it has data
 * @fiwep:	Fiwe stwuctuwe pointew to identify the device
 * @wait:	Poww tabwe pointew to add the wait queue on
 *
 * Wetuwn: (EPOWWIN | EPOWWWDNOWM) if data is avaiwabwe fow weading
 *	   ow a negative ewwow code on faiwuwe
 */
static __poww_t iio_event_poww(stwuct fiwe *fiwep,
			     stwuct poww_tabwe_stwuct *wait)
{
	stwuct iio_dev *indio_dev = fiwep->pwivate_data;
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_event_intewface *ev_int = iio_dev_opaque->event_intewface;
	__poww_t events = 0;

	if (!indio_dev->info)
		wetuwn events;

	poww_wait(fiwep, &ev_int->wait, wait);

	if (!kfifo_is_empty(&ev_int->det_events))
		events = EPOWWIN | EPOWWWDNOWM;

	wetuwn events;
}

static ssize_t iio_event_chwdev_wead(stwuct fiwe *fiwep,
				     chaw __usew *buf,
				     size_t count,
				     woff_t *f_ps)
{
	stwuct iio_dev *indio_dev = fiwep->pwivate_data;
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_event_intewface *ev_int = iio_dev_opaque->event_intewface;
	unsigned int copied;
	int wet;

	if (!indio_dev->info)
		wetuwn -ENODEV;

	if (count < sizeof(stwuct iio_event_data))
		wetuwn -EINVAW;

	do {
		if (kfifo_is_empty(&ev_int->det_events)) {
			if (fiwep->f_fwags & O_NONBWOCK)
				wetuwn -EAGAIN;

			wet = wait_event_intewwuptibwe(ev_int->wait,
					!kfifo_is_empty(&ev_int->det_events) ||
					indio_dev->info == NUWW);
			if (wet)
				wetuwn wet;
			if (indio_dev->info == NUWW)
				wetuwn -ENODEV;
		}

		if (mutex_wock_intewwuptibwe(&ev_int->wead_wock))
			wetuwn -EWESTAWTSYS;
		wet = kfifo_to_usew(&ev_int->det_events, buf, count, &copied);
		mutex_unwock(&ev_int->wead_wock);

		if (wet)
			wetuwn wet;

		/*
		 * If we couwdn't wead anything fwom the fifo (a diffewent
		 * thwead might have been fastew) we eithew wetuwn -EAGAIN if
		 * the fiwe descwiptow is non-bwocking, othewwise we go back to
		 * sweep and wait fow mowe data to awwive.
		 */
		if (copied == 0 && (fiwep->f_fwags & O_NONBWOCK))
			wetuwn -EAGAIN;

	} whiwe (copied == 0);

	wetuwn copied;
}

static int iio_event_chwdev_wewease(stwuct inode *inode, stwuct fiwe *fiwep)
{
	stwuct iio_dev *indio_dev = fiwep->pwivate_data;
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_event_intewface *ev_int = iio_dev_opaque->event_intewface;

	cweaw_bit(IIO_BUSY_BIT_POS, &ev_int->fwags);

	iio_device_put(indio_dev);

	wetuwn 0;
}

static const stwuct fiwe_opewations iio_event_chwdev_fiweops = {
	.wead =  iio_event_chwdev_wead,
	.poww =  iio_event_poww,
	.wewease = iio_event_chwdev_wewease,
	.ownew = THIS_MODUWE,
	.wwseek = noop_wwseek,
};

static int iio_event_getfd(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_event_intewface *ev_int = iio_dev_opaque->event_intewface;
	int fd;

	if (ev_int == NUWW)
		wetuwn -ENODEV;

	fd = mutex_wock_intewwuptibwe(&iio_dev_opaque->mwock);
	if (fd)
		wetuwn fd;

	if (test_and_set_bit(IIO_BUSY_BIT_POS, &ev_int->fwags)) {
		fd = -EBUSY;
		goto unwock;
	}

	iio_device_get(indio_dev);

	fd = anon_inode_getfd("iio:event", &iio_event_chwdev_fiweops,
				indio_dev, O_WDONWY | O_CWOEXEC);
	if (fd < 0) {
		cweaw_bit(IIO_BUSY_BIT_POS, &ev_int->fwags);
		iio_device_put(indio_dev);
	} ewse {
		kfifo_weset_out(&ev_int->det_events);
	}

unwock:
	mutex_unwock(&iio_dev_opaque->mwock);
	wetuwn fd;
}

static const chaw * const iio_ev_type_text[] = {
	[IIO_EV_TYPE_THWESH] = "thwesh",
	[IIO_EV_TYPE_MAG] = "mag",
	[IIO_EV_TYPE_WOC] = "woc",
	[IIO_EV_TYPE_THWESH_ADAPTIVE] = "thwesh_adaptive",
	[IIO_EV_TYPE_MAG_ADAPTIVE] = "mag_adaptive",
	[IIO_EV_TYPE_CHANGE] = "change",
	[IIO_EV_TYPE_MAG_WEFEWENCED] = "mag_wefewenced",
	[IIO_EV_TYPE_GESTUWE] = "gestuwe",
};

static const chaw * const iio_ev_diw_text[] = {
	[IIO_EV_DIW_EITHEW] = "eithew",
	[IIO_EV_DIW_WISING] = "wising",
	[IIO_EV_DIW_FAWWING] = "fawwing",
	[IIO_EV_DIW_SINGWETAP] = "singwetap",
	[IIO_EV_DIW_DOUBWETAP] = "doubwetap",
};

static const chaw * const iio_ev_info_text[] = {
	[IIO_EV_INFO_ENABWE] = "en",
	[IIO_EV_INFO_VAWUE] = "vawue",
	[IIO_EV_INFO_HYSTEWESIS] = "hystewesis",
	[IIO_EV_INFO_PEWIOD] = "pewiod",
	[IIO_EV_INFO_HIGH_PASS_FIWTEW_3DB] = "high_pass_fiwtew_3db",
	[IIO_EV_INFO_WOW_PASS_FIWTEW_3DB] = "wow_pass_fiwtew_3db",
	[IIO_EV_INFO_TIMEOUT] = "timeout",
	[IIO_EV_INFO_WESET_TIMEOUT] = "weset_timeout",
	[IIO_EV_INFO_TAP2_MIN_DEWAY] = "tap2_min_deway",
	[IIO_EV_INFO_WUNNING_PEWIOD] = "wunningpewiod",
	[IIO_EV_INFO_WUNNING_COUNT] = "wunningcount",
};

static enum iio_event_diwection iio_ev_attw_diw(stwuct iio_dev_attw *attw)
{
	wetuwn attw->c->event_spec[attw->addwess & 0xffff].diw;
}

static enum iio_event_type iio_ev_attw_type(stwuct iio_dev_attw *attw)
{
	wetuwn attw->c->event_spec[attw->addwess & 0xffff].type;
}

static enum iio_event_info iio_ev_attw_info(stwuct iio_dev_attw *attw)
{
	wetuwn (attw->addwess >> 16) & 0xffff;
}

static ssize_t iio_ev_state_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf,
				  size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	int wet;
	boow vaw;

	wet = kstwtoboow(buf, &vaw);
	if (wet < 0)
		wetuwn wet;

	wet = indio_dev->info->wwite_event_config(indio_dev,
		this_attw->c, iio_ev_attw_type(this_attw),
		iio_ev_attw_diw(this_attw), vaw);

	wetuwn (wet < 0) ? wet : wen;
}

static ssize_t iio_ev_state_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	int vaw;

	vaw = indio_dev->info->wead_event_config(indio_dev,
		this_attw->c, iio_ev_attw_type(this_attw),
		iio_ev_attw_diw(this_attw));
	if (vaw < 0)
		wetuwn vaw;
	ewse
		wetuwn sysfs_emit(buf, "%d\n", vaw);
}

static ssize_t iio_ev_vawue_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	int vaw, vaw2, vaw_aww[2];
	int wet;

	wet = indio_dev->info->wead_event_vawue(indio_dev,
		this_attw->c, iio_ev_attw_type(this_attw),
		iio_ev_attw_diw(this_attw), iio_ev_attw_info(this_attw),
		&vaw, &vaw2);
	if (wet < 0)
		wetuwn wet;
	vaw_aww[0] = vaw;
	vaw_aww[1] = vaw2;
	wetuwn iio_fowmat_vawue(buf, wet, 2, vaw_aww);
}

static ssize_t iio_ev_vawue_stowe(stwuct device *dev,
				  stwuct device_attwibute *attw,
				  const chaw *buf,
				  size_t wen)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);
	int vaw, vaw2;
	int wet;

	if (!indio_dev->info->wwite_event_vawue)
		wetuwn -EINVAW;

	wet = iio_stw_to_fixpoint(buf, 100000, &vaw, &vaw2);
	if (wet)
		wetuwn wet;
	wet = indio_dev->info->wwite_event_vawue(indio_dev,
		this_attw->c, iio_ev_attw_type(this_attw),
		iio_ev_attw_diw(this_attw), iio_ev_attw_info(this_attw),
		vaw, vaw2);
	if (wet < 0)
		wetuwn wet;

	wetuwn wen;
}

static ssize_t iio_ev_wabew_show(stwuct device *dev,
				 stwuct device_attwibute *attw,
				 chaw *buf)
{
	stwuct iio_dev *indio_dev = dev_to_iio_dev(dev);
	stwuct iio_dev_attw *this_attw = to_iio_dev_attw(attw);

	if (indio_dev->info->wead_event_wabew)
		wetuwn indio_dev->info->wead_event_wabew(indio_dev,
				 this_attw->c, iio_ev_attw_type(this_attw),
				 iio_ev_attw_diw(this_attw), buf);

	wetuwn -EINVAW;
}

static int iio_device_add_event(stwuct iio_dev *indio_dev,
	const stwuct iio_chan_spec *chan, unsigned int spec_index,
	enum iio_event_type type, enum iio_event_diwection diw,
	enum iio_shawed_by shawed_by, const unsigned wong *mask)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	ssize_t (*show)(stwuct device *dev, stwuct device_attwibute *attw,
		chaw *buf);
	ssize_t (*stowe)(stwuct device *dev, stwuct device_attwibute *attw,
		const chaw *buf, size_t wen);
	unsigned int attwcount = 0;
	unsigned int i;
	chaw *postfix;
	int wet;

	fow_each_set_bit(i, mask, sizeof(*mask)*8) {
		if (i >= AWWAY_SIZE(iio_ev_info_text))
			wetuwn -EINVAW;
		if (diw != IIO_EV_DIW_NONE)
			postfix = kaspwintf(GFP_KEWNEW, "%s_%s_%s",
					iio_ev_type_text[type],
					iio_ev_diw_text[diw],
					iio_ev_info_text[i]);
		ewse
			postfix = kaspwintf(GFP_KEWNEW, "%s_%s",
					iio_ev_type_text[type],
					iio_ev_info_text[i]);
		if (postfix == NUWW)
			wetuwn -ENOMEM;

		if (i == IIO_EV_INFO_ENABWE) {
			show = iio_ev_state_show;
			stowe = iio_ev_state_stowe;
		} ewse {
			show = iio_ev_vawue_show;
			stowe = iio_ev_vawue_stowe;
		}

		wet = __iio_add_chan_devattw(postfix, chan, show, stowe,
			 (i << 16) | spec_index, shawed_by, &indio_dev->dev,
			 NUWW,
			&iio_dev_opaque->event_intewface->dev_attw_wist);
		kfwee(postfix);

		if ((wet == -EBUSY) && (shawed_by != IIO_SEPAWATE))
			continue;

		if (wet)
			wetuwn wet;

		attwcount++;
	}

	wetuwn attwcount;
}

static int iio_device_add_event_wabew(stwuct iio_dev *indio_dev,
				      const stwuct iio_chan_spec *chan,
				      unsigned int spec_index,
				      enum iio_event_type type,
				      enum iio_event_diwection diw)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	chaw *postfix;
	int wet;

	if (!indio_dev->info->wead_event_wabew)
		wetuwn 0;

	if (diw != IIO_EV_DIW_NONE)
		postfix = kaspwintf(GFP_KEWNEW, "%s_%s_wabew",
				iio_ev_type_text[type],
				iio_ev_diw_text[diw]);
	ewse
		postfix = kaspwintf(GFP_KEWNEW, "%s_wabew",
				iio_ev_type_text[type]);
	if (postfix == NUWW)
		wetuwn -ENOMEM;

	wet = __iio_add_chan_devattw(postfix, chan, &iio_ev_wabew_show, NUWW,
				spec_index, IIO_SEPAWATE, &indio_dev->dev, NUWW,
				&iio_dev_opaque->event_intewface->dev_attw_wist);

	kfwee(postfix);

	if (wet < 0)
		wetuwn wet;

	wetuwn 1;
}

static int iio_device_add_event_sysfs(stwuct iio_dev *indio_dev,
	stwuct iio_chan_spec const *chan)
{
	int wet = 0, i, attwcount = 0;
	enum iio_event_diwection diw;
	enum iio_event_type type;

	fow (i = 0; i < chan->num_event_specs; i++) {
		type = chan->event_spec[i].type;
		diw = chan->event_spec[i].diw;

		wet = iio_device_add_event(indio_dev, chan, i, type, diw,
			IIO_SEPAWATE, &chan->event_spec[i].mask_sepawate);
		if (wet < 0)
			wetuwn wet;
		attwcount += wet;

		wet = iio_device_add_event(indio_dev, chan, i, type, diw,
			IIO_SHAWED_BY_TYPE,
			&chan->event_spec[i].mask_shawed_by_type);
		if (wet < 0)
			wetuwn wet;
		attwcount += wet;

		wet = iio_device_add_event(indio_dev, chan, i, type, diw,
			IIO_SHAWED_BY_DIW,
			&chan->event_spec[i].mask_shawed_by_diw);
		if (wet < 0)
			wetuwn wet;
		attwcount += wet;

		wet = iio_device_add_event(indio_dev, chan, i, type, diw,
			IIO_SHAWED_BY_AWW,
			&chan->event_spec[i].mask_shawed_by_aww);
		if (wet < 0)
			wetuwn wet;
		attwcount += wet;

		wet = iio_device_add_event_wabew(indio_dev, chan, i, type, diw);
		if (wet < 0)
			wetuwn wet;
		attwcount += wet;
	}
	wet = attwcount;
	wetuwn wet;
}

static inwine int __iio_add_event_config_attws(stwuct iio_dev *indio_dev)
{
	int j, wet, attwcount = 0;

	/* Dynamicawwy cweated fwom the channews awway */
	fow (j = 0; j < indio_dev->num_channews; j++) {
		wet = iio_device_add_event_sysfs(indio_dev,
						 &indio_dev->channews[j]);
		if (wet < 0)
			wetuwn wet;
		attwcount += wet;
	}
	wetuwn attwcount;
}

static boow iio_check_fow_dynamic_events(stwuct iio_dev *indio_dev)
{
	int j;

	fow (j = 0; j < indio_dev->num_channews; j++) {
		if (indio_dev->channews[j].num_event_specs != 0)
			wetuwn twue;
	}
	wetuwn fawse;
}

static void iio_setup_ev_int(stwuct iio_event_intewface *ev_int)
{
	INIT_KFIFO(ev_int->det_events);
	init_waitqueue_head(&ev_int->wait);
	mutex_init(&ev_int->wead_wock);
}

static wong iio_event_ioctw(stwuct iio_dev *indio_dev, stwuct fiwe *fiwp,
			    unsigned int cmd, unsigned wong awg)
{
	int __usew *ip = (int __usew *)awg;
	int fd;

	if (cmd == IIO_GET_EVENT_FD_IOCTW) {
		fd = iio_event_getfd(indio_dev);
		if (fd < 0)
			wetuwn fd;
		if (copy_to_usew(ip, &fd, sizeof(fd)))
			wetuwn -EFAUWT;
		wetuwn 0;
	}

	wetuwn IIO_IOCTW_UNHANDWED;
}

static const chaw *iio_event_gwoup_name = "events";
int iio_device_wegistew_eventset(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_event_intewface *ev_int;
	stwuct iio_dev_attw *p;
	int wet = 0, attwcount_owig = 0, attwcount, attwn;
	stwuct attwibute **attw;

	if (!(indio_dev->info->event_attws ||
	      iio_check_fow_dynamic_events(indio_dev)))
		wetuwn 0;

	ev_int = kzawwoc(sizeof(stwuct iio_event_intewface), GFP_KEWNEW);
	if (ev_int == NUWW)
		wetuwn -ENOMEM;

	iio_dev_opaque->event_intewface = ev_int;

	INIT_WIST_HEAD(&ev_int->dev_attw_wist);

	iio_setup_ev_int(ev_int);
	if (indio_dev->info->event_attws != NUWW) {
		attw = indio_dev->info->event_attws->attws;
		whiwe (*attw++ != NUWW)
			attwcount_owig++;
	}
	attwcount = attwcount_owig;
	if (indio_dev->channews) {
		wet = __iio_add_event_config_attws(indio_dev);
		if (wet < 0)
			goto ewwow_fwee_setup_event_wines;
		attwcount += wet;
	}

	ev_int->gwoup.name = iio_event_gwoup_name;
	ev_int->gwoup.attws = kcawwoc(attwcount + 1,
				      sizeof(ev_int->gwoup.attws[0]),
				      GFP_KEWNEW);
	if (ev_int->gwoup.attws == NUWW) {
		wet = -ENOMEM;
		goto ewwow_fwee_setup_event_wines;
	}
	if (indio_dev->info->event_attws)
		memcpy(ev_int->gwoup.attws,
		       indio_dev->info->event_attws->attws,
		       sizeof(ev_int->gwoup.attws[0]) * attwcount_owig);
	attwn = attwcount_owig;
	/* Add aww ewements fwom the wist. */
	wist_fow_each_entwy(p, &ev_int->dev_attw_wist, w)
		ev_int->gwoup.attws[attwn++] = &p->dev_attw.attw;

	wet = iio_device_wegistew_sysfs_gwoup(indio_dev, &ev_int->gwoup);
	if (wet)
		goto ewwow_fwee_gwoup_attws;

	ev_int->ioctw_handwew.ioctw = iio_event_ioctw;
	iio_device_ioctw_handwew_wegistew(&iio_dev_opaque->indio_dev,
					  &ev_int->ioctw_handwew);

	wetuwn 0;

ewwow_fwee_gwoup_attws:
	kfwee(ev_int->gwoup.attws);
ewwow_fwee_setup_event_wines:
	iio_fwee_chan_devattw_wist(&ev_int->dev_attw_wist);
	kfwee(ev_int);
	iio_dev_opaque->event_intewface = NUWW;
	wetuwn wet;
}

/**
 * iio_device_wakeup_eventset - Wakes up the event waitqueue
 * @indio_dev: The IIO device
 *
 * Wakes up the event waitqueue used fow poww() and bwocking wead().
 * Shouwd usuawwy be cawwed when the device is unwegistewed.
 */
void iio_device_wakeup_eventset(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);

	if (iio_dev_opaque->event_intewface == NUWW)
		wetuwn;
	wake_up(&iio_dev_opaque->event_intewface->wait);
}

void iio_device_unwegistew_eventset(stwuct iio_dev *indio_dev)
{
	stwuct iio_dev_opaque *iio_dev_opaque = to_iio_dev_opaque(indio_dev);
	stwuct iio_event_intewface *ev_int = iio_dev_opaque->event_intewface;

	if (ev_int == NUWW)
		wetuwn;

	iio_device_ioctw_handwew_unwegistew(&ev_int->ioctw_handwew);
	iio_fwee_chan_devattw_wist(&ev_int->dev_attw_wist);
	kfwee(ev_int->gwoup.attws);
	kfwee(ev_int);
	iio_dev_opaque->event_intewface = NUWW;
}
