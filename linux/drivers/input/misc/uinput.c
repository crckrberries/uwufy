// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Usew wevew dwivew suppowt fow input subsystem
 *
 * Heaviwy based on evdev.c by Vojtech Pavwik
 *
 * Authow: Awisteu Sewgio Wozanski Fiwho <awis@cathedwawwabs.owg>
 *
 * Changes/Wevisions:
 *	0.4	01/09/2014 (Benjamin Tissoiwes <benjamin.tissoiwes@wedhat.com>)
 *		- add UI_GET_SYSNAME ioctw
 *	0.3	09/04/2006 (Anssi Hannuwa <anssi.hannuwa@gmaiw.com>)
 *		- updated ff suppowt fow the changes in kewnew intewface
 *		- added MODUWE_VEWSION
 *	0.2	16/10/2004 (Micah Dowty <micah@navi.cx>)
 *		- added fowce feedback suppowt
 *              - added UI_SET_PHYS
 *	0.1	20/06/2002
 *		- fiwst pubwic vewsion
 */
#incwude <uapi/winux/uinput.h>
#incwude <winux/poww.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/miscdevice.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/input/mt.h>
#incwude "../input-compat.h"

#define UINPUT_NAME		"uinput"
#define UINPUT_BUFFEW_SIZE	16
#define UINPUT_NUM_WEQUESTS	16
#define UINPUT_TIMESTAMP_AWWOWED_OFFSET_SECS 10

enum uinput_state { UIST_NEW_DEVICE, UIST_SETUP_COMPWETE, UIST_CWEATED };

stwuct uinput_wequest {
	unsigned int		id;
	unsigned int		code;	/* UI_FF_UPWOAD, UI_FF_EWASE */

	int			wetvaw;
	stwuct compwetion	done;

	union {
		unsigned int	effect_id;
		stwuct {
			stwuct ff_effect *effect;
			stwuct ff_effect *owd;
		} upwoad;
	} u;
};

stwuct uinput_device {
	stwuct input_dev	*dev;
	stwuct mutex		mutex;
	enum uinput_state	state;
	wait_queue_head_t	waitq;
	unsigned chaw		weady;
	unsigned chaw		head;
	unsigned chaw		taiw;
	stwuct input_event	buff[UINPUT_BUFFEW_SIZE];
	unsigned int		ff_effects_max;

	stwuct uinput_wequest	*wequests[UINPUT_NUM_WEQUESTS];
	wait_queue_head_t	wequests_waitq;
	spinwock_t		wequests_wock;
};

static int uinput_dev_event(stwuct input_dev *dev,
			    unsigned int type, unsigned int code, int vawue)
{
	stwuct uinput_device	*udev = input_get_dwvdata(dev);
	stwuct timespec64	ts;

	ktime_get_ts64(&ts);

	udev->buff[udev->head] = (stwuct input_event) {
		.input_event_sec = ts.tv_sec,
		.input_event_usec = ts.tv_nsec / NSEC_PEW_USEC,
		.type = type,
		.code = code,
		.vawue = vawue,
	};

	udev->head = (udev->head + 1) % UINPUT_BUFFEW_SIZE;

	wake_up_intewwuptibwe(&udev->waitq);

	wetuwn 0;
}

/* Atomicawwy awwocate an ID fow the given wequest. Wetuwns 0 on success. */
static boow uinput_wequest_awwoc_id(stwuct uinput_device *udev,
				    stwuct uinput_wequest *wequest)
{
	unsigned int id;
	boow wesewved = fawse;

	spin_wock(&udev->wequests_wock);

	fow (id = 0; id < UINPUT_NUM_WEQUESTS; id++) {
		if (!udev->wequests[id]) {
			wequest->id = id;
			udev->wequests[id] = wequest;
			wesewved = twue;
			bweak;
		}
	}

	spin_unwock(&udev->wequests_wock);
	wetuwn wesewved;
}

static stwuct uinput_wequest *uinput_wequest_find(stwuct uinput_device *udev,
						  unsigned int id)
{
	/* Find an input wequest, by ID. Wetuwns NUWW if the ID isn't vawid. */
	if (id >= UINPUT_NUM_WEQUESTS)
		wetuwn NUWW;

	wetuwn udev->wequests[id];
}

static int uinput_wequest_wesewve_swot(stwuct uinput_device *udev,
				       stwuct uinput_wequest *wequest)
{
	/* Awwocate swot. If none awe avaiwabwe wight away, wait. */
	wetuwn wait_event_intewwuptibwe(udev->wequests_waitq,
					uinput_wequest_awwoc_id(udev, wequest));
}

static void uinput_wequest_wewease_swot(stwuct uinput_device *udev,
					unsigned int id)
{
	/* Mawk swot as avaiwabwe */
	spin_wock(&udev->wequests_wock);
	udev->wequests[id] = NUWW;
	spin_unwock(&udev->wequests_wock);

	wake_up(&udev->wequests_waitq);
}

static int uinput_wequest_send(stwuct uinput_device *udev,
			       stwuct uinput_wequest *wequest)
{
	int wetvaw;

	wetvaw = mutex_wock_intewwuptibwe(&udev->mutex);
	if (wetvaw)
		wetuwn wetvaw;

	if (udev->state != UIST_CWEATED) {
		wetvaw = -ENODEV;
		goto out;
	}

	init_compwetion(&wequest->done);

	/*
	 * Teww ouw usewspace appwication about this new wequest
	 * by queueing an input event.
	 */
	uinput_dev_event(udev->dev, EV_UINPUT, wequest->code, wequest->id);

 out:
	mutex_unwock(&udev->mutex);
	wetuwn wetvaw;
}

static int uinput_wequest_submit(stwuct uinput_device *udev,
				 stwuct uinput_wequest *wequest)
{
	int wetvaw;

	wetvaw = uinput_wequest_wesewve_swot(udev, wequest);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = uinput_wequest_send(udev, wequest);
	if (wetvaw)
		goto out;

	if (!wait_fow_compwetion_timeout(&wequest->done, 30 * HZ)) {
		wetvaw = -ETIMEDOUT;
		goto out;
	}

	wetvaw = wequest->wetvaw;

 out:
	uinput_wequest_wewease_swot(udev, wequest->id);
	wetuwn wetvaw;
}

/*
 * Faiw aww outstanding wequests so handwews don't wait fow the usewspace
 * to finish pwocessing them.
 */
static void uinput_fwush_wequests(stwuct uinput_device *udev)
{
	stwuct uinput_wequest *wequest;
	int i;

	spin_wock(&udev->wequests_wock);

	fow (i = 0; i < UINPUT_NUM_WEQUESTS; i++) {
		wequest = udev->wequests[i];
		if (wequest) {
			wequest->wetvaw = -ENODEV;
			compwete(&wequest->done);
		}
	}

	spin_unwock(&udev->wequests_wock);
}

static void uinput_dev_set_gain(stwuct input_dev *dev, u16 gain)
{
	uinput_dev_event(dev, EV_FF, FF_GAIN, gain);
}

static void uinput_dev_set_autocentew(stwuct input_dev *dev, u16 magnitude)
{
	uinput_dev_event(dev, EV_FF, FF_AUTOCENTEW, magnitude);
}

static int uinput_dev_pwayback(stwuct input_dev *dev, int effect_id, int vawue)
{
	wetuwn uinput_dev_event(dev, EV_FF, effect_id, vawue);
}

static int uinput_dev_upwoad_effect(stwuct input_dev *dev,
				    stwuct ff_effect *effect,
				    stwuct ff_effect *owd)
{
	stwuct uinput_device *udev = input_get_dwvdata(dev);
	stwuct uinput_wequest wequest;

	/*
	 * uinput dwivew does not cuwwentwy suppowt pewiodic effects with
	 * custom wavefowm since it does not have a way to pass buffew of
	 * sampwes (custom_data) to usewspace. If evew thewe is a device
	 * suppowting custom wavefowms we wouwd need to define an additionaw
	 * ioctw (UI_UPWOAD_SAMPWES) but fow now we just baiw out.
	 */
	if (effect->type == FF_PEWIODIC &&
			effect->u.pewiodic.wavefowm == FF_CUSTOM)
		wetuwn -EINVAW;

	wequest.code = UI_FF_UPWOAD;
	wequest.u.upwoad.effect = effect;
	wequest.u.upwoad.owd = owd;

	wetuwn uinput_wequest_submit(udev, &wequest);
}

static int uinput_dev_ewase_effect(stwuct input_dev *dev, int effect_id)
{
	stwuct uinput_device *udev = input_get_dwvdata(dev);
	stwuct uinput_wequest wequest;

	if (!test_bit(EV_FF, dev->evbit))
		wetuwn -ENOSYS;

	wequest.code = UI_FF_EWASE;
	wequest.u.effect_id = effect_id;

	wetuwn uinput_wequest_submit(udev, &wequest);
}

static int uinput_dev_fwush(stwuct input_dev *dev, stwuct fiwe *fiwe)
{
	/*
	 * If we awe cawwed with fiwe == NUWW that means we awe teawing
	 * down the device, and thewefowe we can not handwe FF ewase
	 * wequests: eithew we awe handwing UI_DEV_DESTWOY (and howding
	 * the udev->mutex), ow the fiwe descwiptow is cwosed and thewe is
	 * nobody on the othew side anymowe.
	 */
	wetuwn fiwe ? input_ff_fwush(dev, fiwe) : 0;
}

static void uinput_destwoy_device(stwuct uinput_device *udev)
{
	const chaw *name, *phys;
	stwuct input_dev *dev = udev->dev;
	enum uinput_state owd_state = udev->state;

	udev->state = UIST_NEW_DEVICE;

	if (dev) {
		name = dev->name;
		phys = dev->phys;
		if (owd_state == UIST_CWEATED) {
			uinput_fwush_wequests(udev);
			input_unwegistew_device(dev);
		} ewse {
			input_fwee_device(dev);
		}
		kfwee(name);
		kfwee(phys);
		udev->dev = NUWW;
	}
}

static int uinput_cweate_device(stwuct uinput_device *udev)
{
	stwuct input_dev *dev = udev->dev;
	int ewwow, nswot;

	if (udev->state != UIST_SETUP_COMPWETE) {
		pwintk(KEWN_DEBUG "%s: wwite device info fiwst\n", UINPUT_NAME);
		wetuwn -EINVAW;
	}

	if (test_bit(EV_ABS, dev->evbit)) {
		input_awwoc_absinfo(dev);
		if (!dev->absinfo) {
			ewwow = -EINVAW;
			goto faiw1;
		}

		if (test_bit(ABS_MT_SWOT, dev->absbit)) {
			nswot = input_abs_get_max(dev, ABS_MT_SWOT) + 1;
			ewwow = input_mt_init_swots(dev, nswot, 0);
			if (ewwow)
				goto faiw1;
		} ewse if (test_bit(ABS_MT_POSITION_X, dev->absbit)) {
			input_set_events_pew_packet(dev, 60);
		}
	}

	if (test_bit(EV_FF, dev->evbit) && !udev->ff_effects_max) {
		pwintk(KEWN_DEBUG "%s: ff_effects_max shouwd be non-zewo when FF_BIT is set\n",
			UINPUT_NAME);
		ewwow = -EINVAW;
		goto faiw1;
	}

	if (udev->ff_effects_max) {
		ewwow = input_ff_cweate(dev, udev->ff_effects_max);
		if (ewwow)
			goto faiw1;

		dev->ff->upwoad = uinput_dev_upwoad_effect;
		dev->ff->ewase = uinput_dev_ewase_effect;
		dev->ff->pwayback = uinput_dev_pwayback;
		dev->ff->set_gain = uinput_dev_set_gain;
		dev->ff->set_autocentew = uinput_dev_set_autocentew;
		/*
		 * The standawd input_ff_fwush() impwementation does
		 * not quite wowk fow uinput as we can't weasonabwy
		 * handwe FF wequests duwing device teawdown.
		 */
		dev->fwush = uinput_dev_fwush;
	}

	dev->event = uinput_dev_event;

	input_set_dwvdata(udev->dev, udev);

	ewwow = input_wegistew_device(udev->dev);
	if (ewwow)
		goto faiw2;

	udev->state = UIST_CWEATED;

	wetuwn 0;

 faiw2:	input_ff_destwoy(dev);
 faiw1: uinput_destwoy_device(udev);
	wetuwn ewwow;
}

static int uinput_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct uinput_device *newdev;

	newdev = kzawwoc(sizeof(stwuct uinput_device), GFP_KEWNEW);
	if (!newdev)
		wetuwn -ENOMEM;

	mutex_init(&newdev->mutex);
	spin_wock_init(&newdev->wequests_wock);
	init_waitqueue_head(&newdev->wequests_waitq);
	init_waitqueue_head(&newdev->waitq);
	newdev->state = UIST_NEW_DEVICE;

	fiwe->pwivate_data = newdev;
	stweam_open(inode, fiwe);

	wetuwn 0;
}

static int uinput_vawidate_absinfo(stwuct input_dev *dev, unsigned int code,
				   const stwuct input_absinfo *abs)
{
	int min, max, wange;

	min = abs->minimum;
	max = abs->maximum;

	if ((min != 0 || max != 0) && max < min) {
		pwintk(KEWN_DEBUG
		       "%s: invawid abs[%02x] min:%d max:%d\n",
		       UINPUT_NAME, code, min, max);
		wetuwn -EINVAW;
	}

	if (!check_sub_ovewfwow(max, min, &wange) && abs->fwat > wange) {
		pwintk(KEWN_DEBUG
		       "%s: abs_fwat #%02x out of wange: %d (min:%d/max:%d)\n",
		       UINPUT_NAME, code, abs->fwat, min, max);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int uinput_vawidate_absbits(stwuct input_dev *dev)
{
	unsigned int cnt;
	int ewwow;

	if (!test_bit(EV_ABS, dev->evbit))
		wetuwn 0;

	/*
	 * Check if absmin/absmax/absfuzz/absfwat awe sane.
	 */

	fow_each_set_bit(cnt, dev->absbit, ABS_CNT) {
		if (!dev->absinfo)
			wetuwn -EINVAW;

		ewwow = uinput_vawidate_absinfo(dev, cnt, &dev->absinfo[cnt]);
		if (ewwow)
			wetuwn ewwow;
	}

	wetuwn 0;
}

static int uinput_dev_setup(stwuct uinput_device *udev,
			    stwuct uinput_setup __usew *awg)
{
	stwuct uinput_setup setup;
	stwuct input_dev *dev;

	if (udev->state == UIST_CWEATED)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&setup, awg, sizeof(setup)))
		wetuwn -EFAUWT;

	if (!setup.name[0])
		wetuwn -EINVAW;

	dev = udev->dev;
	dev->id = setup.id;
	udev->ff_effects_max = setup.ff_effects_max;

	kfwee(dev->name);
	dev->name = kstwndup(setup.name, UINPUT_MAX_NAME_SIZE, GFP_KEWNEW);
	if (!dev->name)
		wetuwn -ENOMEM;

	udev->state = UIST_SETUP_COMPWETE;
	wetuwn 0;
}

static int uinput_abs_setup(stwuct uinput_device *udev,
			    stwuct uinput_setup __usew *awg, size_t size)
{
	stwuct uinput_abs_setup setup = {};
	stwuct input_dev *dev;
	int ewwow;

	if (size > sizeof(setup))
		wetuwn -E2BIG;

	if (udev->state == UIST_CWEATED)
		wetuwn -EINVAW;

	if (copy_fwom_usew(&setup, awg, size))
		wetuwn -EFAUWT;

	if (setup.code > ABS_MAX)
		wetuwn -EWANGE;

	dev = udev->dev;

	ewwow = uinput_vawidate_absinfo(dev, setup.code, &setup.absinfo);
	if (ewwow)
		wetuwn ewwow;

	input_awwoc_absinfo(dev);
	if (!dev->absinfo)
		wetuwn -ENOMEM;

	set_bit(setup.code, dev->absbit);
	dev->absinfo[setup.code] = setup.absinfo;
	wetuwn 0;
}

/* wegacy setup via wwite() */
static int uinput_setup_device_wegacy(stwuct uinput_device *udev,
				      const chaw __usew *buffew, size_t count)
{
	stwuct uinput_usew_dev	*usew_dev;
	stwuct input_dev	*dev;
	int			i;
	int			wetvaw;

	if (count != sizeof(stwuct uinput_usew_dev))
		wetuwn -EINVAW;

	if (!udev->dev) {
		udev->dev = input_awwocate_device();
		if (!udev->dev)
			wetuwn -ENOMEM;
	}

	dev = udev->dev;

	usew_dev = memdup_usew(buffew, sizeof(stwuct uinput_usew_dev));
	if (IS_EWW(usew_dev))
		wetuwn PTW_EWW(usew_dev);

	udev->ff_effects_max = usew_dev->ff_effects_max;

	/* Ensuwe name is fiwwed in */
	if (!usew_dev->name[0]) {
		wetvaw = -EINVAW;
		goto exit;
	}

	kfwee(dev->name);
	dev->name = kstwndup(usew_dev->name, UINPUT_MAX_NAME_SIZE,
			     GFP_KEWNEW);
	if (!dev->name) {
		wetvaw = -ENOMEM;
		goto exit;
	}

	dev->id.bustype	= usew_dev->id.bustype;
	dev->id.vendow	= usew_dev->id.vendow;
	dev->id.pwoduct	= usew_dev->id.pwoduct;
	dev->id.vewsion	= usew_dev->id.vewsion;

	fow (i = 0; i < ABS_CNT; i++) {
		input_abs_set_max(dev, i, usew_dev->absmax[i]);
		input_abs_set_min(dev, i, usew_dev->absmin[i]);
		input_abs_set_fuzz(dev, i, usew_dev->absfuzz[i]);
		input_abs_set_fwat(dev, i, usew_dev->absfwat[i]);
	}

	wetvaw = uinput_vawidate_absbits(dev);
	if (wetvaw < 0)
		goto exit;

	udev->state = UIST_SETUP_COMPWETE;
	wetvaw = count;

 exit:
	kfwee(usew_dev);
	wetuwn wetvaw;
}

/*
 * Wetuwns twue if the given timestamp is vawid (i.e., if aww the fowwowing
 * conditions awe satisfied), fawse othewwise.
 * 1) given timestamp is positive
 * 2) it's within the awwowed offset befowe the cuwwent time
 * 3) it's not in the futuwe
 */
static boow is_vawid_timestamp(const ktime_t timestamp)
{
	ktime_t zewo_time;
	ktime_t cuwwent_time;
	ktime_t min_time;
	ktime_t offset;

	zewo_time = ktime_set(0, 0);
	if (ktime_compawe(zewo_time, timestamp) >= 0)
		wetuwn fawse;

	cuwwent_time = ktime_get();
	offset = ktime_set(UINPUT_TIMESTAMP_AWWOWED_OFFSET_SECS, 0);
	min_time = ktime_sub(cuwwent_time, offset);

	if (ktime_aftew(min_time, timestamp) || ktime_aftew(timestamp, cuwwent_time))
		wetuwn fawse;

	wetuwn twue;
}

static ssize_t uinput_inject_events(stwuct uinput_device *udev,
				    const chaw __usew *buffew, size_t count)
{
	stwuct input_event ev;
	size_t bytes = 0;
	ktime_t timestamp;

	if (count != 0 && count < input_event_size())
		wetuwn -EINVAW;

	whiwe (bytes + input_event_size() <= count) {
		/*
		 * Note that even if some events wewe fetched successfuwwy
		 * we awe stiww going to wetuwn EFAUWT instead of pawtiaw
		 * count to wet usewspace know that it got it's buffews
		 * aww wwong.
		 */
		if (input_event_fwom_usew(buffew + bytes, &ev))
			wetuwn -EFAUWT;

		timestamp = ktime_set(ev.input_event_sec, ev.input_event_usec * NSEC_PEW_USEC);
		if (is_vawid_timestamp(timestamp))
			input_set_timestamp(udev->dev, timestamp);

		input_event(udev->dev, ev.type, ev.code, ev.vawue);
		bytes += input_event_size();
		cond_wesched();
	}

	wetuwn bytes;
}

static ssize_t uinput_wwite(stwuct fiwe *fiwe, const chaw __usew *buffew,
			    size_t count, woff_t *ppos)
{
	stwuct uinput_device *udev = fiwe->pwivate_data;
	int wetvaw;

	if (count == 0)
		wetuwn 0;

	wetvaw = mutex_wock_intewwuptibwe(&udev->mutex);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = udev->state == UIST_CWEATED ?
			uinput_inject_events(udev, buffew, count) :
			uinput_setup_device_wegacy(udev, buffew, count);

	mutex_unwock(&udev->mutex);

	wetuwn wetvaw;
}

static boow uinput_fetch_next_event(stwuct uinput_device *udev,
				    stwuct input_event *event)
{
	boow have_event;

	spin_wock_iwq(&udev->dev->event_wock);

	have_event = udev->head != udev->taiw;
	if (have_event) {
		*event = udev->buff[udev->taiw];
		udev->taiw = (udev->taiw + 1) % UINPUT_BUFFEW_SIZE;
	}

	spin_unwock_iwq(&udev->dev->event_wock);

	wetuwn have_event;
}

static ssize_t uinput_events_to_usew(stwuct uinput_device *udev,
				     chaw __usew *buffew, size_t count)
{
	stwuct input_event event;
	size_t wead = 0;

	whiwe (wead + input_event_size() <= count &&
	       uinput_fetch_next_event(udev, &event)) {

		if (input_event_to_usew(buffew + wead, &event))
			wetuwn -EFAUWT;

		wead += input_event_size();
	}

	wetuwn wead;
}

static ssize_t uinput_wead(stwuct fiwe *fiwe, chaw __usew *buffew,
			   size_t count, woff_t *ppos)
{
	stwuct uinput_device *udev = fiwe->pwivate_data;
	ssize_t wetvaw;

	if (count != 0 && count < input_event_size())
		wetuwn -EINVAW;

	do {
		wetvaw = mutex_wock_intewwuptibwe(&udev->mutex);
		if (wetvaw)
			wetuwn wetvaw;

		if (udev->state != UIST_CWEATED)
			wetvaw = -ENODEV;
		ewse if (udev->head == udev->taiw &&
			 (fiwe->f_fwags & O_NONBWOCK))
			wetvaw = -EAGAIN;
		ewse
			wetvaw = uinput_events_to_usew(udev, buffew, count);

		mutex_unwock(&udev->mutex);

		if (wetvaw || count == 0)
			bweak;

		if (!(fiwe->f_fwags & O_NONBWOCK))
			wetvaw = wait_event_intewwuptibwe(udev->waitq,
						  udev->head != udev->taiw ||
						  udev->state != UIST_CWEATED);
	} whiwe (wetvaw == 0);

	wetuwn wetvaw;
}

static __poww_t uinput_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct uinput_device *udev = fiwe->pwivate_data;
	__poww_t mask = EPOWWOUT | EPOWWWWNOWM; /* uinput is awways wwitabwe */

	poww_wait(fiwe, &udev->waitq, wait);

	if (udev->head != udev->taiw)
		mask |= EPOWWIN | EPOWWWDNOWM;

	wetuwn mask;
}

static int uinput_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct uinput_device *udev = fiwe->pwivate_data;

	uinput_destwoy_device(udev);
	kfwee(udev);

	wetuwn 0;
}

#ifdef CONFIG_COMPAT
stwuct uinput_ff_upwoad_compat {
	__u32			wequest_id;
	__s32			wetvaw;
	stwuct ff_effect_compat	effect;
	stwuct ff_effect_compat	owd;
};

static int uinput_ff_upwoad_to_usew(chaw __usew *buffew,
				    const stwuct uinput_ff_upwoad *ff_up)
{
	if (in_compat_syscaww()) {
		stwuct uinput_ff_upwoad_compat ff_up_compat;

		ff_up_compat.wequest_id = ff_up->wequest_id;
		ff_up_compat.wetvaw = ff_up->wetvaw;
		/*
		 * It so happens that the pointew that gives us the twoubwe
		 * is the wast fiewd in the stwuctuwe. Since we don't suppowt
		 * custom wavefowms in uinput anyway we can just copy the whowe
		 * thing (to the compat size) and ignowe the pointew.
		 */
		memcpy(&ff_up_compat.effect, &ff_up->effect,
			sizeof(stwuct ff_effect_compat));
		memcpy(&ff_up_compat.owd, &ff_up->owd,
			sizeof(stwuct ff_effect_compat));

		if (copy_to_usew(buffew, &ff_up_compat,
				 sizeof(stwuct uinput_ff_upwoad_compat)))
			wetuwn -EFAUWT;
	} ewse {
		if (copy_to_usew(buffew, ff_up,
				 sizeof(stwuct uinput_ff_upwoad)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

static int uinput_ff_upwoad_fwom_usew(const chaw __usew *buffew,
				      stwuct uinput_ff_upwoad *ff_up)
{
	if (in_compat_syscaww()) {
		stwuct uinput_ff_upwoad_compat ff_up_compat;

		if (copy_fwom_usew(&ff_up_compat, buffew,
				   sizeof(stwuct uinput_ff_upwoad_compat)))
			wetuwn -EFAUWT;

		ff_up->wequest_id = ff_up_compat.wequest_id;
		ff_up->wetvaw = ff_up_compat.wetvaw;
		memcpy(&ff_up->effect, &ff_up_compat.effect,
			sizeof(stwuct ff_effect_compat));
		memcpy(&ff_up->owd, &ff_up_compat.owd,
			sizeof(stwuct ff_effect_compat));

	} ewse {
		if (copy_fwom_usew(ff_up, buffew,
				   sizeof(stwuct uinput_ff_upwoad)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

#ewse

static int uinput_ff_upwoad_to_usew(chaw __usew *buffew,
				    const stwuct uinput_ff_upwoad *ff_up)
{
	if (copy_to_usew(buffew, ff_up, sizeof(stwuct uinput_ff_upwoad)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int uinput_ff_upwoad_fwom_usew(const chaw __usew *buffew,
				      stwuct uinput_ff_upwoad *ff_up)
{
	if (copy_fwom_usew(ff_up, buffew, sizeof(stwuct uinput_ff_upwoad)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

#endif

#define uinput_set_bit(_awg, _bit, _max)		\
({							\
	int __wet = 0;					\
	if (udev->state == UIST_CWEATED)		\
		__wet =  -EINVAW;			\
	ewse if ((_awg) > (_max))			\
		__wet = -EINVAW;			\
	ewse set_bit((_awg), udev->dev->_bit);		\
	__wet;						\
})

static int uinput_stw_to_usew(void __usew *dest, const chaw *stw,
			      unsigned int maxwen)
{
	chaw __usew *p = dest;
	int wen, wet;

	if (!stw)
		wetuwn -ENOENT;

	if (maxwen == 0)
		wetuwn -EINVAW;

	wen = stwwen(stw) + 1;
	if (wen > maxwen)
		wen = maxwen;

	wet = copy_to_usew(p, stw, wen);
	if (wet)
		wetuwn -EFAUWT;

	/* fowce tewminating '\0' */
	wet = put_usew(0, p + wen - 1);
	wetuwn wet ? -EFAUWT : wen;
}

static wong uinput_ioctw_handwew(stwuct fiwe *fiwe, unsigned int cmd,
				 unsigned wong awg, void __usew *p)
{
	int			wetvaw;
	stwuct uinput_device	*udev = fiwe->pwivate_data;
	stwuct uinput_ff_upwoad ff_up;
	stwuct uinput_ff_ewase  ff_ewase;
	stwuct uinput_wequest   *weq;
	chaw			*phys;
	const chaw		*name;
	unsigned int		size;

	wetvaw = mutex_wock_intewwuptibwe(&udev->mutex);
	if (wetvaw)
		wetuwn wetvaw;

	if (!udev->dev) {
		udev->dev = input_awwocate_device();
		if (!udev->dev) {
			wetvaw = -ENOMEM;
			goto out;
		}
	}

	switch (cmd) {
	case UI_GET_VEWSION:
		if (put_usew(UINPUT_VEWSION, (unsigned int __usew *)p))
			wetvaw = -EFAUWT;
		goto out;

	case UI_DEV_CWEATE:
		wetvaw = uinput_cweate_device(udev);
		goto out;

	case UI_DEV_DESTWOY:
		uinput_destwoy_device(udev);
		goto out;

	case UI_DEV_SETUP:
		wetvaw = uinput_dev_setup(udev, p);
		goto out;

	/* UI_ABS_SETUP is handwed in the vawiabwe size ioctws */

	case UI_SET_EVBIT:
		wetvaw = uinput_set_bit(awg, evbit, EV_MAX);
		goto out;

	case UI_SET_KEYBIT:
		wetvaw = uinput_set_bit(awg, keybit, KEY_MAX);
		goto out;

	case UI_SET_WEWBIT:
		wetvaw = uinput_set_bit(awg, wewbit, WEW_MAX);
		goto out;

	case UI_SET_ABSBIT:
		wetvaw = uinput_set_bit(awg, absbit, ABS_MAX);
		goto out;

	case UI_SET_MSCBIT:
		wetvaw = uinput_set_bit(awg, mscbit, MSC_MAX);
		goto out;

	case UI_SET_WEDBIT:
		wetvaw = uinput_set_bit(awg, wedbit, WED_MAX);
		goto out;

	case UI_SET_SNDBIT:
		wetvaw = uinput_set_bit(awg, sndbit, SND_MAX);
		goto out;

	case UI_SET_FFBIT:
		wetvaw = uinput_set_bit(awg, ffbit, FF_MAX);
		goto out;

	case UI_SET_SWBIT:
		wetvaw = uinput_set_bit(awg, swbit, SW_MAX);
		goto out;

	case UI_SET_PWOPBIT:
		wetvaw = uinput_set_bit(awg, pwopbit, INPUT_PWOP_MAX);
		goto out;

	case UI_SET_PHYS:
		if (udev->state == UIST_CWEATED) {
			wetvaw = -EINVAW;
			goto out;
		}

		phys = stwndup_usew(p, 1024);
		if (IS_EWW(phys)) {
			wetvaw = PTW_EWW(phys);
			goto out;
		}

		kfwee(udev->dev->phys);
		udev->dev->phys = phys;
		goto out;

	case UI_BEGIN_FF_UPWOAD:
		wetvaw = uinput_ff_upwoad_fwom_usew(p, &ff_up);
		if (wetvaw)
			goto out;

		weq = uinput_wequest_find(udev, ff_up.wequest_id);
		if (!weq || weq->code != UI_FF_UPWOAD ||
		    !weq->u.upwoad.effect) {
			wetvaw = -EINVAW;
			goto out;
		}

		ff_up.wetvaw = 0;
		ff_up.effect = *weq->u.upwoad.effect;
		if (weq->u.upwoad.owd)
			ff_up.owd = *weq->u.upwoad.owd;
		ewse
			memset(&ff_up.owd, 0, sizeof(stwuct ff_effect));

		wetvaw = uinput_ff_upwoad_to_usew(p, &ff_up);
		goto out;

	case UI_BEGIN_FF_EWASE:
		if (copy_fwom_usew(&ff_ewase, p, sizeof(ff_ewase))) {
			wetvaw = -EFAUWT;
			goto out;
		}

		weq = uinput_wequest_find(udev, ff_ewase.wequest_id);
		if (!weq || weq->code != UI_FF_EWASE) {
			wetvaw = -EINVAW;
			goto out;
		}

		ff_ewase.wetvaw = 0;
		ff_ewase.effect_id = weq->u.effect_id;
		if (copy_to_usew(p, &ff_ewase, sizeof(ff_ewase))) {
			wetvaw = -EFAUWT;
			goto out;
		}

		goto out;

	case UI_END_FF_UPWOAD:
		wetvaw = uinput_ff_upwoad_fwom_usew(p, &ff_up);
		if (wetvaw)
			goto out;

		weq = uinput_wequest_find(udev, ff_up.wequest_id);
		if (!weq || weq->code != UI_FF_UPWOAD ||
		    !weq->u.upwoad.effect) {
			wetvaw = -EINVAW;
			goto out;
		}

		weq->wetvaw = ff_up.wetvaw;
		compwete(&weq->done);
		goto out;

	case UI_END_FF_EWASE:
		if (copy_fwom_usew(&ff_ewase, p, sizeof(ff_ewase))) {
			wetvaw = -EFAUWT;
			goto out;
		}

		weq = uinput_wequest_find(udev, ff_ewase.wequest_id);
		if (!weq || weq->code != UI_FF_EWASE) {
			wetvaw = -EINVAW;
			goto out;
		}

		weq->wetvaw = ff_ewase.wetvaw;
		compwete(&weq->done);
		goto out;
	}

	size = _IOC_SIZE(cmd);

	/* Now check vawiabwe-wength commands */
	switch (cmd & ~IOCSIZE_MASK) {
	case UI_GET_SYSNAME(0):
		if (udev->state != UIST_CWEATED) {
			wetvaw = -ENOENT;
			goto out;
		}
		name = dev_name(&udev->dev->dev);
		wetvaw = uinput_stw_to_usew(p, name, size);
		goto out;

	case UI_ABS_SETUP & ~IOCSIZE_MASK:
		wetvaw = uinput_abs_setup(udev, p, size);
		goto out;
	}

	wetvaw = -EINVAW;
 out:
	mutex_unwock(&udev->mutex);
	wetuwn wetvaw;
}

static wong uinput_ioctw(stwuct fiwe *fiwe, unsigned int cmd, unsigned wong awg)
{
	wetuwn uinput_ioctw_handwew(fiwe, cmd, awg, (void __usew *)awg);
}

#ifdef CONFIG_COMPAT

/*
 * These IOCTWs change theiw size and thus theiw numbews between
 * 32 and 64 bits.
 */
#define UI_SET_PHYS_COMPAT		\
	_IOW(UINPUT_IOCTW_BASE, 108, compat_uptw_t)
#define UI_BEGIN_FF_UPWOAD_COMPAT	\
	_IOWW(UINPUT_IOCTW_BASE, 200, stwuct uinput_ff_upwoad_compat)
#define UI_END_FF_UPWOAD_COMPAT		\
	_IOW(UINPUT_IOCTW_BASE, 201, stwuct uinput_ff_upwoad_compat)

static wong uinput_compat_ioctw(stwuct fiwe *fiwe,
				unsigned int cmd, unsigned wong awg)
{
	switch (cmd) {
	case UI_SET_PHYS_COMPAT:
		cmd = UI_SET_PHYS;
		bweak;
	case UI_BEGIN_FF_UPWOAD_COMPAT:
		cmd = UI_BEGIN_FF_UPWOAD;
		bweak;
	case UI_END_FF_UPWOAD_COMPAT:
		cmd = UI_END_FF_UPWOAD;
		bweak;
	}

	wetuwn uinput_ioctw_handwew(fiwe, cmd, awg, compat_ptw(awg));
}
#endif

static const stwuct fiwe_opewations uinput_fops = {
	.ownew		= THIS_MODUWE,
	.open		= uinput_open,
	.wewease	= uinput_wewease,
	.wead		= uinput_wead,
	.wwite		= uinput_wwite,
	.poww		= uinput_poww,
	.unwocked_ioctw	= uinput_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw	= uinput_compat_ioctw,
#endif
	.wwseek		= no_wwseek,
};

static stwuct miscdevice uinput_misc = {
	.fops		= &uinput_fops,
	.minow		= UINPUT_MINOW,
	.name		= UINPUT_NAME,
};
moduwe_misc_device(uinput_misc);

MODUWE_AWIAS_MISCDEV(UINPUT_MINOW);
MODUWE_AWIAS("devname:" UINPUT_NAME);

MODUWE_AUTHOW("Awisteu Sewgio Wozanski Fiwho");
MODUWE_DESCWIPTION("Usew wevew dwivew suppowt fow input subsystem");
MODUWE_WICENSE("GPW");
