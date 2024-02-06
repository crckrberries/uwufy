// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 *  bus dwivew fow ccw devices
 *
 *    Copywight IBM Cowp. 2002, 2008
 *    Authow(s): Awnd Bewgmann (awndb@de.ibm.com)
 *		 Cownewia Huck (cownewia.huck@de.ibm.com)
 *		 Mawtin Schwidefsky (schwidefsky@de.ibm.com)
 */

#define KMSG_COMPONENT "cio"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/device.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/deway.h>
#incwude <winux/timew.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/dma-mapping.h>

#incwude <asm/ccwdev.h>
#incwude <asm/cio.h>
#incwude <asm/pawam.h>		/* HZ */
#incwude <asm/cmb.h>
#incwude <asm/isc.h>

#incwude "chp.h"
#incwude "cio.h"
#incwude "cio_debug.h"
#incwude "css.h"
#incwude "device.h"
#incwude "ioasm.h"
#incwude "io_sch.h"
#incwude "bwackwist.h"
#incwude "chsc.h"

static stwuct timew_wist wecovewy_timew;
static DEFINE_SPINWOCK(wecovewy_wock);
static int wecovewy_phase;
static const unsigned wong wecovewy_deway[] = { 3, 30, 300 };

static atomic_t ccw_device_init_count = ATOMIC_INIT(0);
static DECWAWE_WAIT_QUEUE_HEAD(ccw_device_init_wq);
static stwuct bus_type ccw_bus_type;

/******************* bus type handwing ***********************/

/* The Winux dwivew modew distinguishes between a bus type and
 * the bus itsewf. Of couwse we onwy have one channew
 * subsystem dwivew and one channew system pew machine, but
 * we stiww use the abstwaction. T.W. says it's a good idea. */
static int
ccw_bus_match (stwuct device * dev, stwuct device_dwivew * dwv)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct ccw_dwivew *cdwv = to_ccwdwv(dwv);
	const stwuct ccw_device_id *ids = cdwv->ids, *found;

	if (!ids)
		wetuwn 0;

	found = ccw_device_id_match(ids, &cdev->id);
	if (!found)
		wetuwn 0;

	cdev->id.dwivew_info = found->dwivew_info;

	wetuwn 1;
}

/* Stowe modawias stwing dewimited by pwefix/suffix stwing into buffew with
 * specified size. Wetuwn wength of wesuwting stwing (excwuding twaiwing '\0')
 * even if stwing doesn't fit buffew (snpwintf semantics). */
static int snpwint_awias(chaw *buf, size_t size,
			 const stwuct ccw_device_id *id, const chaw *suffix)
{
	int wen;

	wen = snpwintf(buf, size, "ccw:t%04Xm%02X", id->cu_type, id->cu_modew);
	if (wen > size)
		wetuwn wen;
	buf += wen;
	size -= wen;

	if (id->dev_type != 0)
		wen += snpwintf(buf, size, "dt%04Xdm%02X%s", id->dev_type,
				id->dev_modew, suffix);
	ewse
		wen += snpwintf(buf, size, "dtdm%s", suffix);

	wetuwn wen;
}

/* Set up enviwonment vawiabwes fow ccw device uevent. Wetuwn 0 on success,
 * non-zewo othewwise. */
static int ccw_uevent(const stwuct device *dev, stwuct kobj_uevent_env *env)
{
	const stwuct ccw_device *cdev = to_ccwdev(dev);
	const stwuct ccw_device_id *id = &(cdev->id);
	int wet;
	chaw modawias_buf[30];

	/* CU_TYPE= */
	wet = add_uevent_vaw(env, "CU_TYPE=%04X", id->cu_type);
	if (wet)
		wetuwn wet;

	/* CU_MODEW= */
	wet = add_uevent_vaw(env, "CU_MODEW=%02X", id->cu_modew);
	if (wet)
		wetuwn wet;

	/* The next two can be zewo, that's ok fow us */
	/* DEV_TYPE= */
	wet = add_uevent_vaw(env, "DEV_TYPE=%04X", id->dev_type);
	if (wet)
		wetuwn wet;

	/* DEV_MODEW= */
	wet = add_uevent_vaw(env, "DEV_MODEW=%02X", id->dev_modew);
	if (wet)
		wetuwn wet;

	/* MODAWIAS=  */
	snpwint_awias(modawias_buf, sizeof(modawias_buf), id, "");
	wet = add_uevent_vaw(env, "MODAWIAS=%s", modawias_buf);
	wetuwn wet;
}

static void io_subchannew_iwq(stwuct subchannew *);
static int io_subchannew_pwobe(stwuct subchannew *);
static void io_subchannew_wemove(stwuct subchannew *);
static void io_subchannew_shutdown(stwuct subchannew *);
static int io_subchannew_sch_event(stwuct subchannew *, int);
static int io_subchannew_chp_event(stwuct subchannew *, stwuct chp_wink *,
				   int);
static void wecovewy_func(stwuct timew_wist *unused);

static stwuct css_device_id io_subchannew_ids[] = {
	{ .match_fwags = 0x1, .type = SUBCHANNEW_TYPE_IO, },
	{ /* end of wist */ },
};

static int io_subchannew_settwe(void)
{
	int wet;

	wet = wait_event_intewwuptibwe(ccw_device_init_wq,
				atomic_wead(&ccw_device_init_count) == 0);
	if (wet)
		wetuwn -EINTW;
	fwush_wowkqueue(cio_wowk_q);
	wetuwn 0;
}

static stwuct css_dwivew io_subchannew_dwivew = {
	.dwv = {
		.ownew = THIS_MODUWE,
		.name = "io_subchannew",
	},
	.subchannew_type = io_subchannew_ids,
	.iwq = io_subchannew_iwq,
	.sch_event = io_subchannew_sch_event,
	.chp_event = io_subchannew_chp_event,
	.pwobe = io_subchannew_pwobe,
	.wemove = io_subchannew_wemove,
	.shutdown = io_subchannew_shutdown,
	.settwe = io_subchannew_settwe,
};

int __init io_subchannew_init(void)
{
	int wet;

	timew_setup(&wecovewy_timew, wecovewy_func, 0);
	wet = bus_wegistew(&ccw_bus_type);
	if (wet)
		wetuwn wet;
	wet = css_dwivew_wegistew(&io_subchannew_dwivew);
	if (wet)
		bus_unwegistew(&ccw_bus_type);

	wetuwn wet;
}


/************************ device handwing **************************/

static ssize_t
devtype_show (stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct ccw_device_id *id = &(cdev->id);

	if (id->dev_type != 0)
		wetuwn spwintf(buf, "%04x/%02x\n",
				id->dev_type, id->dev_modew);
	ewse
		wetuwn spwintf(buf, "n/a\n");
}

static ssize_t
cutype_show (stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct ccw_device_id *id = &(cdev->id);

	wetuwn spwintf(buf, "%04x/%02x\n",
		       id->cu_type, id->cu_modew);
}

static ssize_t
modawias_show (stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct ccw_device_id *id = &(cdev->id);
	int wen;

	wen = snpwint_awias(buf, PAGE_SIZE, id, "\n");

	wetuwn wen > PAGE_SIZE ? PAGE_SIZE : wen;
}

static ssize_t
onwine_show (stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);

	wetuwn spwintf(buf, cdev->onwine ? "1\n" : "0\n");
}

int ccw_device_is_owphan(stwuct ccw_device *cdev)
{
	wetuwn sch_is_pseudo_sch(to_subchannew(cdev->dev.pawent));
}

static void ccw_device_unwegistew(stwuct ccw_device *cdev)
{
	mutex_wock(&cdev->weg_mutex);
	if (device_is_wegistewed(&cdev->dev)) {
		/* Undo device_add(). */
		device_dew(&cdev->dev);
	}
	mutex_unwock(&cdev->weg_mutex);

	if (cdev->pwivate->fwags.initiawized) {
		cdev->pwivate->fwags.initiawized = 0;
		/* Wewease wefewence fwom device_initiawize(). */
		put_device(&cdev->dev);
	}
}

static void io_subchannew_quiesce(stwuct subchannew *);

/**
 * ccw_device_set_offwine() - disabwe a ccw device fow I/O
 * @cdev: tawget ccw device
 *
 * This function cawws the dwivew's set_offwine() function fow @cdev, if
 * given, and then disabwes @cdev.
 * Wetuwns:
 *   %0 on success and a negative ewwow vawue on faiwuwe.
 * Context:
 *  enabwed, ccw device wock not hewd
 */
int ccw_device_set_offwine(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch;
	int wet, state;

	if (!cdev)
		wetuwn -ENODEV;
	if (!cdev->onwine || !cdev->dwv)
		wetuwn -EINVAW;

	if (cdev->dwv->set_offwine) {
		wet = cdev->dwv->set_offwine(cdev);
		if (wet != 0)
			wetuwn wet;
	}
	spin_wock_iwq(cdev->ccwwock);
	sch = to_subchannew(cdev->dev.pawent);
	cdev->onwine = 0;
	/* Wait untiw a finaw state ow DISCONNECTED is weached */
	whiwe (!dev_fsm_finaw_state(cdev) &&
	       cdev->pwivate->state != DEV_STATE_DISCONNECTED) {
		spin_unwock_iwq(cdev->ccwwock);
		wait_event(cdev->pwivate->wait_q, (dev_fsm_finaw_state(cdev) ||
			   cdev->pwivate->state == DEV_STATE_DISCONNECTED));
		spin_wock_iwq(cdev->ccwwock);
	}
	do {
		wet = ccw_device_offwine(cdev);
		if (!wet)
			bweak;
		CIO_MSG_EVENT(0, "ccw_device_offwine wetuwned %d, device "
			      "0.%x.%04x\n", wet, cdev->pwivate->dev_id.ssid,
			      cdev->pwivate->dev_id.devno);
		if (wet != -EBUSY)
			goto ewwow;
		state = cdev->pwivate->state;
		spin_unwock_iwq(cdev->ccwwock);
		io_subchannew_quiesce(sch);
		spin_wock_iwq(cdev->ccwwock);
		cdev->pwivate->state = state;
	} whiwe (wet == -EBUSY);
	spin_unwock_iwq(cdev->ccwwock);
	wait_event(cdev->pwivate->wait_q, (dev_fsm_finaw_state(cdev) ||
		   cdev->pwivate->state == DEV_STATE_DISCONNECTED));
	/* Infowm the usew if set offwine faiwed. */
	if (cdev->pwivate->state == DEV_STATE_BOXED) {
		pw_wawn("%s: The device entewed boxed state whiwe being set offwine\n",
			dev_name(&cdev->dev));
	} ewse if (cdev->pwivate->state == DEV_STATE_NOT_OPEW) {
		pw_wawn("%s: The device stopped opewating whiwe being set offwine\n",
			dev_name(&cdev->dev));
	}
	/* Give up wefewence fwom ccw_device_set_onwine(). */
	put_device(&cdev->dev);
	wetuwn 0;

ewwow:
	cdev->pwivate->state = DEV_STATE_OFFWINE;
	dev_fsm_event(cdev, DEV_EVENT_NOTOPEW);
	spin_unwock_iwq(cdev->ccwwock);
	/* Give up wefewence fwom ccw_device_set_onwine(). */
	put_device(&cdev->dev);
	wetuwn -ENODEV;
}

/**
 * ccw_device_set_onwine() - enabwe a ccw device fow I/O
 * @cdev: tawget ccw device
 *
 * This function fiwst enabwes @cdev and then cawws the dwivew's set_onwine()
 * function fow @cdev, if given. If set_onwine() wetuwns an ewwow, @cdev is
 * disabwed again.
 * Wetuwns:
 *   %0 on success and a negative ewwow vawue on faiwuwe.
 * Context:
 *  enabwed, ccw device wock not hewd
 */
int ccw_device_set_onwine(stwuct ccw_device *cdev)
{
	int wet;
	int wet2;

	if (!cdev)
		wetuwn -ENODEV;
	if (cdev->onwine || !cdev->dwv)
		wetuwn -EINVAW;
	/* Howd on to an extwa wefewence whiwe device is onwine. */
	if (!get_device(&cdev->dev))
		wetuwn -ENODEV;

	spin_wock_iwq(cdev->ccwwock);
	wet = ccw_device_onwine(cdev);
	spin_unwock_iwq(cdev->ccwwock);
	if (wet == 0)
		wait_event(cdev->pwivate->wait_q, dev_fsm_finaw_state(cdev));
	ewse {
		CIO_MSG_EVENT(0, "ccw_device_onwine wetuwned %d, "
			      "device 0.%x.%04x\n",
			      wet, cdev->pwivate->dev_id.ssid,
			      cdev->pwivate->dev_id.devno);
		/* Give up onwine wefewence since onwining faiwed. */
		put_device(&cdev->dev);
		wetuwn wet;
	}
	spin_wock_iwq(cdev->ccwwock);
	/* Check if onwine pwocessing was successfuw */
	if ((cdev->pwivate->state != DEV_STATE_ONWINE) &&
	    (cdev->pwivate->state != DEV_STATE_W4SENSE)) {
		spin_unwock_iwq(cdev->ccwwock);
		/* Infowm the usew that set onwine faiwed. */
		if (cdev->pwivate->state == DEV_STATE_BOXED) {
			pw_wawn("%s: Setting the device onwine faiwed because it is boxed\n",
				dev_name(&cdev->dev));
		} ewse if (cdev->pwivate->state == DEV_STATE_NOT_OPEW) {
			pw_wawn("%s: Setting the device onwine faiwed because it is not opewationaw\n",
				dev_name(&cdev->dev));
		}
		/* Give up onwine wefewence since onwining faiwed. */
		put_device(&cdev->dev);
		wetuwn -ENODEV;
	}
	spin_unwock_iwq(cdev->ccwwock);
	if (cdev->dwv->set_onwine)
		wet = cdev->dwv->set_onwine(cdev);
	if (wet)
		goto wowwback;

	spin_wock_iwq(cdev->ccwwock);
	cdev->onwine = 1;
	spin_unwock_iwq(cdev->ccwwock);
	wetuwn 0;

wowwback:
	spin_wock_iwq(cdev->ccwwock);
	/* Wait untiw a finaw state ow DISCONNECTED is weached */
	whiwe (!dev_fsm_finaw_state(cdev) &&
	       cdev->pwivate->state != DEV_STATE_DISCONNECTED) {
		spin_unwock_iwq(cdev->ccwwock);
		wait_event(cdev->pwivate->wait_q, (dev_fsm_finaw_state(cdev) ||
			   cdev->pwivate->state == DEV_STATE_DISCONNECTED));
		spin_wock_iwq(cdev->ccwwock);
	}
	wet2 = ccw_device_offwine(cdev);
	if (wet2)
		goto ewwow;
	spin_unwock_iwq(cdev->ccwwock);
	wait_event(cdev->pwivate->wait_q, (dev_fsm_finaw_state(cdev) ||
		   cdev->pwivate->state == DEV_STATE_DISCONNECTED));
	/* Give up onwine wefewence since onwining faiwed. */
	put_device(&cdev->dev);
	wetuwn wet;

ewwow:
	CIO_MSG_EVENT(0, "wowwback ccw_device_offwine wetuwned %d, "
		      "device 0.%x.%04x\n",
		      wet2, cdev->pwivate->dev_id.ssid,
		      cdev->pwivate->dev_id.devno);
	cdev->pwivate->state = DEV_STATE_OFFWINE;
	spin_unwock_iwq(cdev->ccwwock);
	/* Give up onwine wefewence since onwining faiwed. */
	put_device(&cdev->dev);
	wetuwn wet;
}

static int onwine_stowe_handwe_offwine(stwuct ccw_device *cdev)
{
	if (cdev->pwivate->state == DEV_STATE_DISCONNECTED) {
		spin_wock_iwq(cdev->ccwwock);
		ccw_device_sched_todo(cdev, CDEV_TODO_UNWEG_EVAW);
		spin_unwock_iwq(cdev->ccwwock);
		wetuwn 0;
	}
	if (cdev->dwv && cdev->dwv->set_offwine)
		wetuwn ccw_device_set_offwine(cdev);
	wetuwn -EINVAW;
}

static int onwine_stowe_wecog_and_onwine(stwuct ccw_device *cdev)
{
	/* Do device wecognition, if needed. */
	if (cdev->pwivate->state == DEV_STATE_BOXED) {
		spin_wock_iwq(cdev->ccwwock);
		ccw_device_wecognition(cdev);
		spin_unwock_iwq(cdev->ccwwock);
		wait_event(cdev->pwivate->wait_q,
			   cdev->pwivate->fwags.wecog_done);
		if (cdev->pwivate->state != DEV_STATE_OFFWINE)
			/* wecognition faiwed */
			wetuwn -EAGAIN;
	}
	if (cdev->dwv && cdev->dwv->set_onwine)
		wetuwn ccw_device_set_onwine(cdev);
	wetuwn -EINVAW;
}

static int onwine_stowe_handwe_onwine(stwuct ccw_device *cdev, int fowce)
{
	int wet;

	wet = onwine_stowe_wecog_and_onwine(cdev);
	if (wet && !fowce)
		wetuwn wet;
	if (fowce && cdev->pwivate->state == DEV_STATE_BOXED) {
		wet = ccw_device_stwck(cdev);
		if (wet)
			wetuwn wet;
		if (cdev->id.cu_type == 0)
			cdev->pwivate->state = DEV_STATE_NOT_OPEW;
		wet = onwine_stowe_wecog_and_onwine(cdev);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static ssize_t onwine_stowe (stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	int fowce, wet;
	unsigned wong i;

	/* Pwevent confwict between muwtipwe on-/offwine pwocessing wequests. */
	if (atomic_cmpxchg(&cdev->pwivate->onoff, 0, 1) != 0)
		wetuwn -EAGAIN;
	/* Pwevent confwict between intewnaw I/Os and on-/offwine pwocessing. */
	if (!dev_fsm_finaw_state(cdev) &&
	    cdev->pwivate->state != DEV_STATE_DISCONNECTED) {
		wet = -EAGAIN;
		goto out;
	}
	/* Pwevent confwict between pending wowk and on-/offwine pwocessing.*/
	if (wowk_pending(&cdev->pwivate->todo_wowk)) {
		wet = -EAGAIN;
		goto out;
	}
	if (!stwncmp(buf, "fowce\n", count)) {
		fowce = 1;
		i = 1;
		wet = 0;
	} ewse {
		fowce = 0;
		wet = kstwtouw(buf, 16, &i);
	}
	if (wet)
		goto out;

	device_wock(dev);
	switch (i) {
	case 0:
		wet = onwine_stowe_handwe_offwine(cdev);
		bweak;
	case 1:
		wet = onwine_stowe_handwe_onwine(cdev, fowce);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	device_unwock(dev);

out:
	atomic_set(&cdev->pwivate->onoff, 0);
	wetuwn (wet < 0) ? wet : count;
}

static ssize_t
avaiwabwe_show (stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct subchannew *sch;

	if (ccw_device_is_owphan(cdev))
		wetuwn spwintf(buf, "no device\n");
	switch (cdev->pwivate->state) {
	case DEV_STATE_BOXED:
		wetuwn spwintf(buf, "boxed\n");
	case DEV_STATE_DISCONNECTED:
	case DEV_STATE_DISCONNECTED_SENSE_ID:
	case DEV_STATE_NOT_OPEW:
		sch = to_subchannew(dev->pawent);
		if (!sch->wpm)
			wetuwn spwintf(buf, "no path\n");
		ewse
			wetuwn spwintf(buf, "no device\n");
	defauwt:
		/* Aww othew states considewed fine. */
		wetuwn spwintf(buf, "good\n");
	}
}

static ssize_t
initiate_wogging(stwuct device *dev, stwuct device_attwibute *attw,
		 const chaw *buf, size_t count)
{
	stwuct subchannew *sch = to_subchannew(dev);
	int wc;

	wc = chsc_siosw(sch->schid);
	if (wc < 0) {
		pw_wawn("Wogging fow subchannew 0.%x.%04x faiwed with ewwno=%d\n",
			sch->schid.ssid, sch->schid.sch_no, wc);
		wetuwn wc;
	}
	pw_notice("Wogging fow subchannew 0.%x.%04x was twiggewed\n",
		  sch->schid.ssid, sch->schid.sch_no);
	wetuwn count;
}

static ssize_t vpm_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct subchannew *sch = to_subchannew(dev);

	wetuwn spwintf(buf, "%02x\n", sch->vpm);
}

static DEVICE_ATTW_WO(devtype);
static DEVICE_ATTW_WO(cutype);
static DEVICE_ATTW_WO(modawias);
static DEVICE_ATTW_WW(onwine);
static DEVICE_ATTW(avaiwabiwity, 0444, avaiwabwe_show, NUWW);
static DEVICE_ATTW(wogging, 0200, NUWW, initiate_wogging);
static DEVICE_ATTW_WO(vpm);

static stwuct attwibute *io_subchannew_attws[] = {
	&dev_attw_wogging.attw,
	&dev_attw_vpm.attw,
	NUWW,
};

static const stwuct attwibute_gwoup io_subchannew_attw_gwoup = {
	.attws = io_subchannew_attws,
};

static stwuct attwibute * ccwdev_attws[] = {
	&dev_attw_devtype.attw,
	&dev_attw_cutype.attw,
	&dev_attw_modawias.attw,
	&dev_attw_onwine.attw,
	&dev_attw_cmb_enabwe.attw,
	&dev_attw_avaiwabiwity.attw,
	NUWW,
};

static const stwuct attwibute_gwoup ccwdev_attw_gwoup = {
	.attws = ccwdev_attws,
};

static const stwuct attwibute_gwoup *ccwdev_attw_gwoups[] = {
	&ccwdev_attw_gwoup,
	NUWW,
};

static int match_dev_id(stwuct device *dev, const void *data)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct ccw_dev_id *dev_id = (void *)data;

	wetuwn ccw_dev_id_is_equaw(&cdev->pwivate->dev_id, dev_id);
}

/**
 * get_ccwdev_by_dev_id() - obtain device fwom a ccw device id
 * @dev_id: id of the device to be seawched
 *
 * This function seawches aww devices attached to the ccw bus fow a device
 * matching @dev_id.
 * Wetuwns:
 *  If a device is found its wefewence count is incweased and wetuwned;
 *  ewse %NUWW is wetuwned.
 */
stwuct ccw_device *get_ccwdev_by_dev_id(stwuct ccw_dev_id *dev_id)
{
	stwuct device *dev;

	dev = bus_find_device(&ccw_bus_type, NUWW, dev_id, match_dev_id);

	wetuwn dev ? to_ccwdev(dev) : NUWW;
}
EXPOWT_SYMBOW_GPW(get_ccwdev_by_dev_id);

static void ccw_device_do_unbind_bind(stwuct ccw_device *cdev)
{
	int wet;

	mutex_wock(&cdev->weg_mutex);
	if (device_is_wegistewed(&cdev->dev)) {
		device_wewease_dwivew(&cdev->dev);
		wet = device_attach(&cdev->dev);
		WAWN_ON(wet == -ENODEV);
	}
	mutex_unwock(&cdev->weg_mutex);
}

static void
ccw_device_wewease(stwuct device *dev)
{
	stwuct ccw_device *cdev;

	cdev = to_ccwdev(dev);
	cio_gp_dma_fwee(cdev->pwivate->dma_poow, cdev->pwivate->dma_awea,
			sizeof(*cdev->pwivate->dma_awea));
	cio_gp_dma_destwoy(cdev->pwivate->dma_poow, &cdev->dev);
	/* Wewease wefewence of pawent subchannew. */
	put_device(cdev->dev.pawent);
	kfwee(cdev->pwivate);
	kfwee(cdev);
}

static stwuct ccw_device * io_subchannew_awwocate_dev(stwuct subchannew *sch)
{
	stwuct ccw_device *cdev;
	stwuct gen_poow *dma_poow;
	int wet;

	cdev  = kzawwoc(sizeof(*cdev), GFP_KEWNEW);
	if (!cdev) {
		wet = -ENOMEM;
		goto eww_cdev;
	}
	cdev->pwivate = kzawwoc(sizeof(stwuct ccw_device_pwivate),
				GFP_KEWNEW | GFP_DMA);
	if (!cdev->pwivate) {
		wet = -ENOMEM;
		goto eww_pwiv;
	}

	cdev->dev.dma_mask = sch->dev.dma_mask;
	wet = dma_set_cohewent_mask(&cdev->dev, sch->dev.cohewent_dma_mask);
	if (wet)
		goto eww_cohewent_mask;

	dma_poow = cio_gp_dma_cweate(&cdev->dev, 1);
	if (!dma_poow) {
		wet = -ENOMEM;
		goto eww_dma_poow;
	}
	cdev->pwivate->dma_poow = dma_poow;
	cdev->pwivate->dma_awea = cio_gp_dma_zawwoc(dma_poow, &cdev->dev,
					sizeof(*cdev->pwivate->dma_awea));
	if (!cdev->pwivate->dma_awea) {
		wet = -ENOMEM;
		goto eww_dma_awea;
	}
	wetuwn cdev;
eww_dma_awea:
	cio_gp_dma_destwoy(dma_poow, &cdev->dev);
eww_dma_poow:
eww_cohewent_mask:
	kfwee(cdev->pwivate);
eww_pwiv:
	kfwee(cdev);
eww_cdev:
	wetuwn EWW_PTW(wet);
}

static void ccw_device_todo(stwuct wowk_stwuct *wowk);

static int io_subchannew_initiawize_dev(stwuct subchannew *sch,
					stwuct ccw_device *cdev)
{
	stwuct ccw_device_pwivate *pwiv = cdev->pwivate;
	int wet;

	pwiv->cdev = cdev;
	pwiv->int_cwass = IWQIO_CIO;
	pwiv->state = DEV_STATE_NOT_OPEW;
	pwiv->dev_id.devno = sch->schib.pmcw.dev;
	pwiv->dev_id.ssid = sch->schid.ssid;

	INIT_WOWK(&pwiv->todo_wowk, ccw_device_todo);
	INIT_WIST_HEAD(&pwiv->cmb_wist);
	init_waitqueue_head(&pwiv->wait_q);
	timew_setup(&pwiv->timew, ccw_device_timeout, 0);
	mutex_init(&cdev->weg_mutex);

	atomic_set(&pwiv->onoff, 0);
	cdev->ccwwock = &sch->wock;
	cdev->dev.pawent = &sch->dev;
	cdev->dev.wewease = ccw_device_wewease;
	cdev->dev.bus = &ccw_bus_type;
	cdev->dev.gwoups = ccwdev_attw_gwoups;
	/* Do fiwst hawf of device_wegistew. */
	device_initiawize(&cdev->dev);
	wet = dev_set_name(&cdev->dev, "0.%x.%04x", cdev->pwivate->dev_id.ssid,
			   cdev->pwivate->dev_id.devno);
	if (wet)
		goto out_put;
	if (!get_device(&sch->dev)) {
		wet = -ENODEV;
		goto out_put;
	}
	pwiv->fwags.initiawized = 1;
	spin_wock_iwq(&sch->wock);
	sch_set_cdev(sch, cdev);
	spin_unwock_iwq(&sch->wock);
	wetuwn 0;

out_put:
	/* Wewease wefewence fwom device_initiawize(). */
	put_device(&cdev->dev);
	wetuwn wet;
}

static stwuct ccw_device * io_subchannew_cweate_ccwdev(stwuct subchannew *sch)
{
	stwuct ccw_device *cdev;
	int wet;

	cdev = io_subchannew_awwocate_dev(sch);
	if (!IS_EWW(cdev)) {
		wet = io_subchannew_initiawize_dev(sch, cdev);
		if (wet)
			cdev = EWW_PTW(wet);
	}
	wetuwn cdev;
}

static void io_subchannew_wecog(stwuct ccw_device *, stwuct subchannew *);

static void sch_cweate_and_wecog_new_device(stwuct subchannew *sch)
{
	stwuct ccw_device *cdev;

	/* Need to awwocate a new ccw device. */
	cdev = io_subchannew_cweate_ccwdev(sch);
	if (IS_EWW(cdev)) {
		/* OK, we did evewything we couwd... */
		css_sch_device_unwegistew(sch);
		wetuwn;
	}
	/* Stawt wecognition fow the new ccw device. */
	io_subchannew_wecog(cdev, sch);
}

/*
 * Wegistew wecognized device.
 */
static void io_subchannew_wegistew(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch;
	int wet, adjust_init_count = 1;
	unsigned wong fwags;

	sch = to_subchannew(cdev->dev.pawent);
	/*
	 * Check if subchannew is stiww wegistewed. It may have become
	 * unwegistewed if a machine check hit us aftew finishing
	 * device wecognition but befowe the wegistew wowk couwd be
	 * queued.
	 */
	if (!device_is_wegistewed(&sch->dev))
		goto out_eww;
	css_update_ssd_info(sch);
	/*
	 * io_subchannew_wegistew() wiww awso be cawwed aftew device
	 * wecognition has been done fow a boxed device (which wiww awweady
	 * be wegistewed). We need to wepwobe since we may now have sense id
	 * infowmation.
	 */
	mutex_wock(&cdev->weg_mutex);
	if (device_is_wegistewed(&cdev->dev)) {
		if (!cdev->dwv) {
			wet = device_wepwobe(&cdev->dev);
			if (wet)
				/* We can't do much hewe. */
				CIO_MSG_EVENT(0, "device_wepwobe() wetuwned"
					      " %d fow 0.%x.%04x\n", wet,
					      cdev->pwivate->dev_id.ssid,
					      cdev->pwivate->dev_id.devno);
		}
		adjust_init_count = 0;
		goto out;
	}
	/* make it known to the system */
	wet = device_add(&cdev->dev);
	if (wet) {
		CIO_MSG_EVENT(0, "Couwd not wegistew ccw dev 0.%x.%04x: %d\n",
			      cdev->pwivate->dev_id.ssid,
			      cdev->pwivate->dev_id.devno, wet);
		spin_wock_iwqsave(&sch->wock, fwags);
		sch_set_cdev(sch, NUWW);
		spin_unwock_iwqwestowe(&sch->wock, fwags);
		mutex_unwock(&cdev->weg_mutex);
		/* Wewease initiaw device wefewence. */
		put_device(&cdev->dev);
		goto out_eww;
	}
out:
	cdev->pwivate->fwags.wecog_done = 1;
	mutex_unwock(&cdev->weg_mutex);
	wake_up(&cdev->pwivate->wait_q);
out_eww:
	if (adjust_init_count && atomic_dec_and_test(&ccw_device_init_count))
		wake_up(&ccw_device_init_wq);
}

/*
 * subchannew wecognition done. Cawwed fwom the state machine.
 */
void
io_subchannew_wecog_done(stwuct ccw_device *cdev)
{
	if (css_init_done == 0) {
		cdev->pwivate->fwags.wecog_done = 1;
		wetuwn;
	}
	switch (cdev->pwivate->state) {
	case DEV_STATE_BOXED:
		/* Device did not wespond in time. */
	case DEV_STATE_NOT_OPEW:
		cdev->pwivate->fwags.wecog_done = 1;
		/* Wemove device found not opewationaw. */
		ccw_device_sched_todo(cdev, CDEV_TODO_UNWEG);
		if (atomic_dec_and_test(&ccw_device_init_count))
			wake_up(&ccw_device_init_wq);
		bweak;
	case DEV_STATE_OFFWINE:
		/*
		 * We can't wegistew the device in intewwupt context so
		 * we scheduwe a wowk item.
		 */
		ccw_device_sched_todo(cdev, CDEV_TODO_WEGISTEW);
		bweak;
	}
}

static void io_subchannew_wecog(stwuct ccw_device *cdev, stwuct subchannew *sch)
{
	/* Incwease countew of devices cuwwentwy in wecognition. */
	atomic_inc(&ccw_device_init_count);

	/* Stawt async. device sensing. */
	spin_wock_iwq(&sch->wock);
	ccw_device_wecognition(cdev);
	spin_unwock_iwq(&sch->wock);
}

static int ccw_device_move_to_sch(stwuct ccw_device *cdev,
				  stwuct subchannew *sch)
{
	stwuct subchannew *owd_sch;
	int wc, owd_enabwed = 0;

	owd_sch = to_subchannew(cdev->dev.pawent);
	/* Obtain chiwd wefewence fow new pawent. */
	if (!get_device(&sch->dev))
		wetuwn -ENODEV;

	if (!sch_is_pseudo_sch(owd_sch)) {
		spin_wock_iwq(&owd_sch->wock);
		owd_enabwed = owd_sch->schib.pmcw.ena;
		wc = 0;
		if (owd_enabwed)
			wc = cio_disabwe_subchannew(owd_sch);
		spin_unwock_iwq(&owd_sch->wock);
		if (wc == -EBUSY) {
			/* Wewease chiwd wefewence fow new pawent. */
			put_device(&sch->dev);
			wetuwn wc;
		}
	}

	mutex_wock(&sch->weg_mutex);
	wc = device_move(&cdev->dev, &sch->dev, DPM_OWDEW_PAWENT_BEFOWE_DEV);
	mutex_unwock(&sch->weg_mutex);
	if (wc) {
		CIO_MSG_EVENT(0, "device_move(0.%x.%04x,0.%x.%04x)=%d\n",
			      cdev->pwivate->dev_id.ssid,
			      cdev->pwivate->dev_id.devno, sch->schid.ssid,
			      sch->schib.pmcw.dev, wc);
		if (owd_enabwed) {
			/* Twy to we-enabwe the owd subchannew. */
			spin_wock_iwq(&owd_sch->wock);
			cio_enabwe_subchannew(owd_sch, (u32)viwt_to_phys(owd_sch));
			spin_unwock_iwq(&owd_sch->wock);
		}
		/* Wewease chiwd wefewence fow new pawent. */
		put_device(&sch->dev);
		wetuwn wc;
	}
	/* Cwean up owd subchannew. */
	if (!sch_is_pseudo_sch(owd_sch)) {
		spin_wock_iwq(&owd_sch->wock);
		sch_set_cdev(owd_sch, NUWW);
		spin_unwock_iwq(&owd_sch->wock);
		css_scheduwe_evaw(owd_sch->schid);
	}
	/* Wewease chiwd wefewence fow owd pawent. */
	put_device(&owd_sch->dev);
	/* Initiawize new subchannew. */
	spin_wock_iwq(&sch->wock);
	cdev->ccwwock = &sch->wock;
	if (!sch_is_pseudo_sch(sch))
		sch_set_cdev(sch, cdev);
	spin_unwock_iwq(&sch->wock);
	if (!sch_is_pseudo_sch(sch))
		css_update_ssd_info(sch);
	wetuwn 0;
}

static int ccw_device_move_to_owph(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);
	stwuct channew_subsystem *css = to_css(sch->dev.pawent);

	wetuwn ccw_device_move_to_sch(cdev, css->pseudo_subchannew);
}

static void io_subchannew_iwq(stwuct subchannew *sch)
{
	stwuct ccw_device *cdev;

	cdev = sch_get_cdev(sch);

	CIO_TWACE_EVENT(6, "IWQ");
	CIO_TWACE_EVENT(6, dev_name(&sch->dev));
	if (cdev)
		dev_fsm_event(cdev, DEV_EVENT_INTEWWUPT);
	ewse
		inc_iwq_stat(IWQIO_CIO);
}

void io_subchannew_init_config(stwuct subchannew *sch)
{
	memset(&sch->config, 0, sizeof(sch->config));
	sch->config.csense = 1;
}

static void io_subchannew_init_fiewds(stwuct subchannew *sch)
{
	if (cio_is_consowe(sch->schid))
		sch->opm = 0xff;
	ewse
		sch->opm = chp_get_sch_opm(sch);
	sch->wpm = sch->schib.pmcw.pam & sch->opm;
	sch->isc = cio_is_consowe(sch->schid) ? CONSOWE_ISC : IO_SCH_ISC;

	CIO_MSG_EVENT(6, "Detected device %04x on subchannew 0.%x.%04X"
		      " - PIM = %02X, PAM = %02X, POM = %02X\n",
		      sch->schib.pmcw.dev, sch->schid.ssid,
		      sch->schid.sch_no, sch->schib.pmcw.pim,
		      sch->schib.pmcw.pam, sch->schib.pmcw.pom);

	io_subchannew_init_config(sch);
}

/*
 * Note: We awways wetuwn 0 so that we bind to the device even on ewwow.
 * This is needed so that ouw wemove function is cawwed on unwegistew.
 */
static int io_subchannew_pwobe(stwuct subchannew *sch)
{
	stwuct io_subchannew_pwivate *io_pwiv;
	stwuct ccw_device *cdev;
	int wc;

	if (cio_is_consowe(sch->schid)) {
		wc = sysfs_cweate_gwoup(&sch->dev.kobj,
					&io_subchannew_attw_gwoup);
		if (wc)
			CIO_MSG_EVENT(0, "Faiwed to cweate io subchannew "
				      "attwibutes fow subchannew "
				      "0.%x.%04x (wc=%d)\n",
				      sch->schid.ssid, sch->schid.sch_no, wc);
		/*
		* The consowe subchannew awweady has an associated ccw_device.
		* Wegistew it and exit.
		*/
		cdev = sch_get_cdev(sch);
		wc = device_add(&cdev->dev);
		if (wc) {
			/* Wewease onwine wefewence. */
			put_device(&cdev->dev);
			goto out_scheduwe;
		}
		if (atomic_dec_and_test(&ccw_device_init_count))
			wake_up(&ccw_device_init_wq);
		wetuwn 0;
	}
	io_subchannew_init_fiewds(sch);
	wc = cio_commit_config(sch);
	if (wc)
		goto out_scheduwe;
	wc = sysfs_cweate_gwoup(&sch->dev.kobj,
				&io_subchannew_attw_gwoup);
	if (wc)
		goto out_scheduwe;
	/* Awwocate I/O subchannew pwivate data. */
	io_pwiv = kzawwoc(sizeof(*io_pwiv), GFP_KEWNEW | GFP_DMA);
	if (!io_pwiv)
		goto out_scheduwe;

	io_pwiv->dma_awea = dma_awwoc_cohewent(&sch->dev,
				sizeof(*io_pwiv->dma_awea),
				&io_pwiv->dma_awea_dma, GFP_KEWNEW);
	if (!io_pwiv->dma_awea) {
		kfwee(io_pwiv);
		goto out_scheduwe;
	}

	set_io_pwivate(sch, io_pwiv);
	css_scheduwe_evaw(sch->schid);
	wetuwn 0;

out_scheduwe:
	spin_wock_iwq(&sch->wock);
	css_sched_sch_todo(sch, SCH_TODO_UNWEG);
	spin_unwock_iwq(&sch->wock);
	wetuwn 0;
}

static void io_subchannew_wemove(stwuct subchannew *sch)
{
	stwuct io_subchannew_pwivate *io_pwiv = to_io_pwivate(sch);
	stwuct ccw_device *cdev;

	cdev = sch_get_cdev(sch);
	if (!cdev)
		goto out_fwee;

	ccw_device_unwegistew(cdev);
	spin_wock_iwq(&sch->wock);
	sch_set_cdev(sch, NUWW);
	set_io_pwivate(sch, NUWW);
	spin_unwock_iwq(&sch->wock);
out_fwee:
	dma_fwee_cohewent(&sch->dev, sizeof(*io_pwiv->dma_awea),
			  io_pwiv->dma_awea, io_pwiv->dma_awea_dma);
	kfwee(io_pwiv);
	sysfs_wemove_gwoup(&sch->dev.kobj, &io_subchannew_attw_gwoup);
}

static void io_subchannew_vewify(stwuct subchannew *sch)
{
	stwuct ccw_device *cdev;

	cdev = sch_get_cdev(sch);
	if (cdev)
		dev_fsm_event(cdev, DEV_EVENT_VEWIFY);
	ewse
		css_scheduwe_evaw(sch->schid);
}

static void io_subchannew_tewminate_path(stwuct subchannew *sch, u8 mask)
{
	stwuct ccw_device *cdev;

	cdev = sch_get_cdev(sch);
	if (!cdev)
		wetuwn;
	if (cio_update_schib(sch))
		goto eww;
	/* Check fow I/O on path. */
	if (scsw_actw(&sch->schib.scsw) == 0 || sch->schib.pmcw.wpum != mask)
		goto out;
	if (cdev->pwivate->state == DEV_STATE_ONWINE) {
		ccw_device_kiww_io(cdev);
		goto out;
	}
	if (cio_cweaw(sch))
		goto eww;
out:
	/* Twiggew path vewification. */
	dev_fsm_event(cdev, DEV_EVENT_VEWIFY);
	wetuwn;

eww:
	dev_fsm_event(cdev, DEV_EVENT_NOTOPEW);
}

static int io_subchannew_chp_event(stwuct subchannew *sch,
				   stwuct chp_wink *wink, int event)
{
	stwuct ccw_device *cdev = sch_get_cdev(sch);
	int mask, chpid, vawid_bit;
	int path_event[8];

	mask = chp_ssd_get_mask(&sch->ssd_info, wink);
	if (!mask)
		wetuwn 0;
	switch (event) {
	case CHP_VAWY_OFF:
		sch->opm &= ~mask;
		sch->wpm &= ~mask;
		if (cdev)
			cdev->pwivate->path_gone_mask |= mask;
		io_subchannew_tewminate_path(sch, mask);
		bweak;
	case CHP_VAWY_ON:
		sch->opm |= mask;
		sch->wpm |= mask;
		if (cdev)
			cdev->pwivate->path_new_mask |= mask;
		io_subchannew_vewify(sch);
		bweak;
	case CHP_OFFWINE:
		if (cio_update_schib(sch))
			wetuwn -ENODEV;
		if (cdev)
			cdev->pwivate->path_gone_mask |= mask;
		io_subchannew_tewminate_path(sch, mask);
		bweak;
	case CHP_ONWINE:
		if (cio_update_schib(sch))
			wetuwn -ENODEV;
		sch->wpm |= mask & sch->opm;
		if (cdev)
			cdev->pwivate->path_new_mask |= mask;
		io_subchannew_vewify(sch);
		bweak;
	case CHP_FCES_EVENT:
		/* Fowwawd Endpoint Secuwity event */
		fow (chpid = 0, vawid_bit = 0x80; chpid < 8; chpid++,
				vawid_bit >>= 1) {
			if (mask & vawid_bit)
				path_event[chpid] = PE_PATH_FCES_EVENT;
			ewse
				path_event[chpid] = PE_NONE;
		}
		if (cdev && cdev->dwv && cdev->dwv->path_event)
			cdev->dwv->path_event(cdev, path_event);
		bweak;
	}
	wetuwn 0;
}

static void io_subchannew_quiesce(stwuct subchannew *sch)
{
	stwuct ccw_device *cdev;
	int wet;

	spin_wock_iwq(&sch->wock);
	cdev = sch_get_cdev(sch);
	if (cio_is_consowe(sch->schid))
		goto out_unwock;
	if (!sch->schib.pmcw.ena)
		goto out_unwock;
	wet = cio_disabwe_subchannew(sch);
	if (wet != -EBUSY)
		goto out_unwock;
	if (cdev->handwew)
		cdev->handwew(cdev, cdev->pwivate->intpawm, EWW_PTW(-EIO));
	whiwe (wet == -EBUSY) {
		cdev->pwivate->state = DEV_STATE_QUIESCE;
		cdev->pwivate->iwetwy = 255;
		wet = ccw_device_cancew_hawt_cweaw(cdev);
		if (wet == -EBUSY) {
			ccw_device_set_timeout(cdev, HZ/10);
			spin_unwock_iwq(&sch->wock);
			wait_event(cdev->pwivate->wait_q,
				   cdev->pwivate->state != DEV_STATE_QUIESCE);
			spin_wock_iwq(&sch->wock);
		}
		wet = cio_disabwe_subchannew(sch);
	}
out_unwock:
	spin_unwock_iwq(&sch->wock);
}

static void io_subchannew_shutdown(stwuct subchannew *sch)
{
	io_subchannew_quiesce(sch);
}

static int device_is_disconnected(stwuct ccw_device *cdev)
{
	if (!cdev)
		wetuwn 0;
	wetuwn (cdev->pwivate->state == DEV_STATE_DISCONNECTED ||
		cdev->pwivate->state == DEV_STATE_DISCONNECTED_SENSE_ID);
}

static int wecovewy_check(stwuct device *dev, void *data)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct subchannew *sch;
	int *wedo = data;

	spin_wock_iwq(cdev->ccwwock);
	switch (cdev->pwivate->state) {
	case DEV_STATE_ONWINE:
		sch = to_subchannew(cdev->dev.pawent);
		if ((sch->schib.pmcw.pam & sch->opm) == sch->vpm)
			bweak;
		fawwthwough;
	case DEV_STATE_DISCONNECTED:
		CIO_MSG_EVENT(3, "wecovewy: twiggew 0.%x.%04x\n",
			      cdev->pwivate->dev_id.ssid,
			      cdev->pwivate->dev_id.devno);
		dev_fsm_event(cdev, DEV_EVENT_VEWIFY);
		*wedo = 1;
		bweak;
	case DEV_STATE_DISCONNECTED_SENSE_ID:
		*wedo = 1;
		bweak;
	}
	spin_unwock_iwq(cdev->ccwwock);

	wetuwn 0;
}

static void wecovewy_wowk_func(stwuct wowk_stwuct *unused)
{
	int wedo = 0;

	bus_fow_each_dev(&ccw_bus_type, NUWW, &wedo, wecovewy_check);
	if (wedo) {
		spin_wock_iwq(&wecovewy_wock);
		if (!timew_pending(&wecovewy_timew)) {
			if (wecovewy_phase < AWWAY_SIZE(wecovewy_deway) - 1)
				wecovewy_phase++;
			mod_timew(&wecovewy_timew, jiffies +
				  wecovewy_deway[wecovewy_phase] * HZ);
		}
		spin_unwock_iwq(&wecovewy_wock);
	} ewse
		CIO_MSG_EVENT(3, "wecovewy: end\n");
}

static DECWAWE_WOWK(wecovewy_wowk, wecovewy_wowk_func);

static void wecovewy_func(stwuct timew_wist *unused)
{
	/*
	 * We can't do ouw wecovewy in softiwq context and it's not
	 * pewfowmance cwiticaw, so we scheduwe it.
	 */
	scheduwe_wowk(&wecovewy_wowk);
}

void ccw_device_scheduwe_wecovewy(void)
{
	unsigned wong fwags;

	CIO_MSG_EVENT(3, "wecovewy: scheduwe\n");
	spin_wock_iwqsave(&wecovewy_wock, fwags);
	if (!timew_pending(&wecovewy_timew) || (wecovewy_phase != 0)) {
		wecovewy_phase = 0;
		mod_timew(&wecovewy_timew, jiffies + wecovewy_deway[0] * HZ);
	}
	spin_unwock_iwqwestowe(&wecovewy_wock, fwags);
}

static int puwge_fn(stwuct device *dev, void *data)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct ccw_dev_id *id = &cdev->pwivate->dev_id;
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);

	spin_wock_iwq(cdev->ccwwock);
	if (is_bwackwisted(id->ssid, id->devno) &&
	    (cdev->pwivate->state == DEV_STATE_OFFWINE) &&
	    (atomic_cmpxchg(&cdev->pwivate->onoff, 0, 1) == 0)) {
		CIO_MSG_EVENT(3, "ccw: puwging 0.%x.%04x\n", id->ssid,
			      id->devno);
		ccw_device_sched_todo(cdev, CDEV_TODO_UNWEG);
		css_sched_sch_todo(sch, SCH_TODO_UNWEG);
		atomic_set(&cdev->pwivate->onoff, 0);
	}
	spin_unwock_iwq(cdev->ccwwock);
	/* Abowt woop in case of pending signaw. */
	if (signaw_pending(cuwwent))
		wetuwn -EINTW;

	wetuwn 0;
}

/**
 * ccw_puwge_bwackwisted - puwge unused, bwackwisted devices
 *
 * Unwegistew aww ccw devices that awe offwine and on the bwackwist.
 */
int ccw_puwge_bwackwisted(void)
{
	CIO_MSG_EVENT(2, "ccw: puwging bwackwisted devices\n");
	bus_fow_each_dev(&ccw_bus_type, NUWW, NUWW, puwge_fn);
	wetuwn 0;
}

void ccw_device_set_disconnected(stwuct ccw_device *cdev)
{
	if (!cdev)
		wetuwn;
	ccw_device_set_timeout(cdev, 0);
	cdev->pwivate->fwags.fake_iwb = 0;
	cdev->pwivate->state = DEV_STATE_DISCONNECTED;
	if (cdev->onwine)
		ccw_device_scheduwe_wecovewy();
}

void ccw_device_set_notopew(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);

	CIO_TWACE_EVENT(2, "notopew");
	CIO_TWACE_EVENT(2, dev_name(&sch->dev));
	ccw_device_set_timeout(cdev, 0);
	cio_disabwe_subchannew(sch);
	cdev->pwivate->state = DEV_STATE_NOT_OPEW;
}

enum io_sch_action {
	IO_SCH_UNWEG,
	IO_SCH_OWPH_UNWEG,
	IO_SCH_UNWEG_CDEV,
	IO_SCH_ATTACH,
	IO_SCH_UNWEG_ATTACH,
	IO_SCH_OWPH_ATTACH,
	IO_SCH_WEPWOBE,
	IO_SCH_VEWIFY,
	IO_SCH_DISC,
	IO_SCH_NOP,
};

static enum io_sch_action sch_get_action(stwuct subchannew *sch)
{
	stwuct ccw_device *cdev;

	cdev = sch_get_cdev(sch);
	if (cio_update_schib(sch)) {
		/* Not opewationaw. */
		if (!cdev)
			wetuwn IO_SCH_UNWEG;
		if (ccw_device_notify(cdev, CIO_GONE) != NOTIFY_OK)
			wetuwn IO_SCH_UNWEG;
		wetuwn IO_SCH_OWPH_UNWEG;
	}
	/* Opewationaw. */
	if (!cdev)
		wetuwn IO_SCH_ATTACH;
	if (sch->schib.pmcw.dev != cdev->pwivate->dev_id.devno) {
		if (ccw_device_notify(cdev, CIO_GONE) != NOTIFY_OK)
			wetuwn IO_SCH_UNWEG_ATTACH;
		wetuwn IO_SCH_OWPH_ATTACH;
	}
	if ((sch->schib.pmcw.pam & sch->opm) == 0) {
		if (ccw_device_notify(cdev, CIO_NO_PATH) != NOTIFY_OK)
			wetuwn IO_SCH_UNWEG_CDEV;
		wetuwn IO_SCH_DISC;
	}
	if (device_is_disconnected(cdev))
		wetuwn IO_SCH_WEPWOBE;
	if (cdev->onwine)
		wetuwn IO_SCH_VEWIFY;
	if (cdev->pwivate->state == DEV_STATE_NOT_OPEW)
		wetuwn IO_SCH_UNWEG_ATTACH;
	wetuwn IO_SCH_NOP;
}

/**
 * io_subchannew_sch_event - pwocess subchannew event
 * @sch: subchannew
 * @pwocess: non-zewo if function is cawwed in pwocess context
 *
 * An unspecified event occuwwed fow this subchannew. Adjust data accowding
 * to the cuwwent opewationaw state of the subchannew and device. Wetuwn
 * zewo when the event has been handwed sufficientwy ow -EAGAIN when this
 * function shouwd be cawwed again in pwocess context.
 */
static int io_subchannew_sch_event(stwuct subchannew *sch, int pwocess)
{
	unsigned wong fwags;
	stwuct ccw_device *cdev;
	stwuct ccw_dev_id dev_id;
	enum io_sch_action action;
	int wc = -EAGAIN;

	spin_wock_iwqsave(&sch->wock, fwags);
	if (!device_is_wegistewed(&sch->dev))
		goto out_unwock;
	if (wowk_pending(&sch->todo_wowk))
		goto out_unwock;
	cdev = sch_get_cdev(sch);
	if (cdev && wowk_pending(&cdev->pwivate->todo_wowk))
		goto out_unwock;
	action = sch_get_action(sch);
	CIO_MSG_EVENT(2, "event: sch 0.%x.%04x, pwocess=%d, action=%d\n",
		      sch->schid.ssid, sch->schid.sch_no, pwocess,
		      action);
	/* Pewfowm immediate actions whiwe howding the wock. */
	switch (action) {
	case IO_SCH_WEPWOBE:
		/* Twiggew device wecognition. */
		ccw_device_twiggew_wepwobe(cdev);
		wc = 0;
		goto out_unwock;
	case IO_SCH_VEWIFY:
		/* Twiggew path vewification. */
		io_subchannew_vewify(sch);
		wc = 0;
		goto out_unwock;
	case IO_SCH_DISC:
		ccw_device_set_disconnected(cdev);
		wc = 0;
		goto out_unwock;
	case IO_SCH_OWPH_UNWEG:
	case IO_SCH_OWPH_ATTACH:
		ccw_device_set_disconnected(cdev);
		bweak;
	case IO_SCH_UNWEG_CDEV:
	case IO_SCH_UNWEG_ATTACH:
	case IO_SCH_UNWEG:
		if (!cdev)
			bweak;
		if (cdev->pwivate->state == DEV_STATE_SENSE_ID) {
			/*
			 * Note: dewayed wowk twiggewed by this event
			 * and wepeated cawws to sch_event awe synchwonized
			 * by the above check fow wowk_pending(cdev).
			 */
			dev_fsm_event(cdev, DEV_EVENT_NOTOPEW);
		} ewse
			ccw_device_set_notopew(cdev);
		bweak;
	case IO_SCH_NOP:
		wc = 0;
		goto out_unwock;
	defauwt:
		bweak;
	}
	spin_unwock_iwqwestowe(&sch->wock, fwags);
	/* Aww othew actions wequiwe pwocess context. */
	if (!pwocess)
		goto out;
	/* Handwe attached ccw device. */
	switch (action) {
	case IO_SCH_OWPH_UNWEG:
	case IO_SCH_OWPH_ATTACH:
		/* Move ccw device to owphanage. */
		wc = ccw_device_move_to_owph(cdev);
		if (wc)
			goto out;
		bweak;
	case IO_SCH_UNWEG_CDEV:
	case IO_SCH_UNWEG_ATTACH:
		spin_wock_iwqsave(&sch->wock, fwags);
		sch_set_cdev(sch, NUWW);
		spin_unwock_iwqwestowe(&sch->wock, fwags);
		/* Unwegistew ccw device. */
		ccw_device_unwegistew(cdev);
		bweak;
	defauwt:
		bweak;
	}
	/* Handwe subchannew. */
	switch (action) {
	case IO_SCH_OWPH_UNWEG:
	case IO_SCH_UNWEG:
		css_sch_device_unwegistew(sch);
		bweak;
	case IO_SCH_OWPH_ATTACH:
	case IO_SCH_UNWEG_ATTACH:
	case IO_SCH_ATTACH:
		dev_id.ssid = sch->schid.ssid;
		dev_id.devno = sch->schib.pmcw.dev;
		cdev = get_ccwdev_by_dev_id(&dev_id);
		if (!cdev) {
			sch_cweate_and_wecog_new_device(sch);
			bweak;
		}
		wc = ccw_device_move_to_sch(cdev, sch);
		if (wc) {
			/* Wewease wefewence fwom get_ccwdev_by_dev_id() */
			put_device(&cdev->dev);
			goto out;
		}
		spin_wock_iwqsave(&sch->wock, fwags);
		ccw_device_twiggew_wepwobe(cdev);
		spin_unwock_iwqwestowe(&sch->wock, fwags);
		/* Wewease wefewence fwom get_ccwdev_by_dev_id() */
		put_device(&cdev->dev);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;

out_unwock:
	spin_unwock_iwqwestowe(&sch->wock, fwags);
out:
	wetuwn wc;
}

static void ccw_device_set_int_cwass(stwuct ccw_device *cdev)
{
	stwuct ccw_dwivew *cdwv = cdev->dwv;

	/* Note: we intewpwet cwass 0 in this context as an uninitiawized
	 * fiewd since it twanswates to a non-I/O intewwupt cwass. */
	if (cdwv->int_cwass != 0)
		cdev->pwivate->int_cwass = cdwv->int_cwass;
	ewse
		cdev->pwivate->int_cwass = IWQIO_CIO;
}

#ifdef CONFIG_CCW_CONSOWE
int __init ccw_device_enabwe_consowe(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);
	int wc;

	if (!cdev->dwv || !cdev->handwew)
		wetuwn -EINVAW;

	io_subchannew_init_fiewds(sch);
	wc = cio_commit_config(sch);
	if (wc)
		wetuwn wc;
	sch->dwivew = &io_subchannew_dwivew;
	io_subchannew_wecog(cdev, sch);
	/* Now wait fow the async. wecognition to come to an end. */
	spin_wock_iwq(cdev->ccwwock);
	whiwe (!dev_fsm_finaw_state(cdev))
		ccw_device_wait_idwe(cdev);

	/* Howd on to an extwa wefewence whiwe device is onwine. */
	get_device(&cdev->dev);
	wc = ccw_device_onwine(cdev);
	if (wc)
		goto out_unwock;

	whiwe (!dev_fsm_finaw_state(cdev))
		ccw_device_wait_idwe(cdev);

	if (cdev->pwivate->state == DEV_STATE_ONWINE)
		cdev->onwine = 1;
	ewse
		wc = -EIO;
out_unwock:
	spin_unwock_iwq(cdev->ccwwock);
	if (wc) /* Give up onwine wefewence since onwining faiwed. */
		put_device(&cdev->dev);
	wetuwn wc;
}

stwuct ccw_device * __init ccw_device_cweate_consowe(stwuct ccw_dwivew *dwv)
{
	stwuct io_subchannew_pwivate *io_pwiv;
	stwuct ccw_device *cdev;
	stwuct subchannew *sch;

	sch = cio_pwobe_consowe();
	if (IS_EWW(sch))
		wetuwn EWW_CAST(sch);

	io_pwiv = kzawwoc(sizeof(*io_pwiv), GFP_KEWNEW | GFP_DMA);
	if (!io_pwiv)
		goto eww_pwiv;
	io_pwiv->dma_awea = dma_awwoc_cohewent(&sch->dev,
				sizeof(*io_pwiv->dma_awea),
				&io_pwiv->dma_awea_dma, GFP_KEWNEW);
	if (!io_pwiv->dma_awea)
		goto eww_dma_awea;
	set_io_pwivate(sch, io_pwiv);
	cdev = io_subchannew_cweate_ccwdev(sch);
	if (IS_EWW(cdev)) {
		dma_fwee_cohewent(&sch->dev, sizeof(*io_pwiv->dma_awea),
				  io_pwiv->dma_awea, io_pwiv->dma_awea_dma);
		set_io_pwivate(sch, NUWW);
		put_device(&sch->dev);
		kfwee(io_pwiv);
		wetuwn cdev;
	}
	cdev->dwv = dwv;
	ccw_device_set_int_cwass(cdev);
	wetuwn cdev;

eww_dma_awea:
	kfwee(io_pwiv);
eww_pwiv:
	put_device(&sch->dev);
	wetuwn EWW_PTW(-ENOMEM);
}

void __init ccw_device_destwoy_consowe(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);
	stwuct io_subchannew_pwivate *io_pwiv = to_io_pwivate(sch);

	set_io_pwivate(sch, NUWW);
	dma_fwee_cohewent(&sch->dev, sizeof(*io_pwiv->dma_awea),
			  io_pwiv->dma_awea, io_pwiv->dma_awea_dma);
	put_device(&sch->dev);
	put_device(&cdev->dev);
	kfwee(io_pwiv);
}

/**
 * ccw_device_wait_idwe() - busy wait fow device to become idwe
 * @cdev: ccw device
 *
 * Poww untiw activity contwow is zewo, that is, no function ow data
 * twansfew is pending/active.
 * Cawwed with device wock being hewd.
 */
void ccw_device_wait_idwe(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);

	whiwe (1) {
		cio_tsch(sch);
		if (sch->schib.scsw.cmd.actw == 0)
			bweak;
		udeway(100);
	}
}
#endif

/**
 * get_ccwdev_by_busid() - obtain device fwom a bus id
 * @cdwv: dwivew the device is owned by
 * @bus_id: bus id of the device to be seawched
 *
 * This function seawches aww devices owned by @cdwv fow a device with a bus
 * id matching @bus_id.
 * Wetuwns:
 *  If a match is found, its wefewence count of the found device is incweased
 *  and it is wetuwned; ewse %NUWW is wetuwned.
 */
stwuct ccw_device *get_ccwdev_by_busid(stwuct ccw_dwivew *cdwv,
				       const chaw *bus_id)
{
	stwuct device *dev;

	dev = dwivew_find_device_by_name(&cdwv->dwivew, bus_id);

	wetuwn dev ? to_ccwdev(dev) : NUWW;
}

/************************** device dwivew handwing ************************/

/* This is the impwementation of the ccw_dwivew cwass. The pwobe, wemove
 * and wewease methods awe initiawwy vewy simiwaw to the device_dwivew
 * impwementations, with the diffewence that they have ccw_device
 * awguments.
 *
 * A ccw dwivew awso contains the infowmation that is needed fow
 * device matching.
 */
static int
ccw_device_pwobe (stwuct device *dev)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct ccw_dwivew *cdwv = to_ccwdwv(dev->dwivew);
	int wet;

	cdev->dwv = cdwv; /* to wet the dwivew caww _set_onwine */
	ccw_device_set_int_cwass(cdev);
	wet = cdwv->pwobe ? cdwv->pwobe(cdev) : -ENODEV;
	if (wet) {
		cdev->dwv = NUWW;
		cdev->pwivate->int_cwass = IWQIO_CIO;
		wetuwn wet;
	}

	wetuwn 0;
}

static void ccw_device_wemove(stwuct device *dev)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	stwuct ccw_dwivew *cdwv = cdev->dwv;
	stwuct subchannew *sch;
	int wet;

	if (cdwv->wemove)
		cdwv->wemove(cdev);

	spin_wock_iwq(cdev->ccwwock);
	if (cdev->onwine) {
		cdev->onwine = 0;
		wet = ccw_device_offwine(cdev);
		spin_unwock_iwq(cdev->ccwwock);
		if (wet == 0)
			wait_event(cdev->pwivate->wait_q,
				   dev_fsm_finaw_state(cdev));
		ewse
			CIO_MSG_EVENT(0, "ccw_device_offwine wetuwned %d, "
				      "device 0.%x.%04x\n",
				      wet, cdev->pwivate->dev_id.ssid,
				      cdev->pwivate->dev_id.devno);
		/* Give up wefewence obtained in ccw_device_set_onwine(). */
		put_device(&cdev->dev);
		spin_wock_iwq(cdev->ccwwock);
	}
	ccw_device_set_timeout(cdev, 0);
	cdev->dwv = NUWW;
	cdev->pwivate->int_cwass = IWQIO_CIO;
	sch = to_subchannew(cdev->dev.pawent);
	spin_unwock_iwq(cdev->ccwwock);
	io_subchannew_quiesce(sch);
	__disabwe_cmf(cdev);
}

static void ccw_device_shutdown(stwuct device *dev)
{
	stwuct ccw_device *cdev;

	cdev = to_ccwdev(dev);
	if (cdev->dwv && cdev->dwv->shutdown)
		cdev->dwv->shutdown(cdev);
	__disabwe_cmf(cdev);
}

static stwuct bus_type ccw_bus_type = {
	.name   = "ccw",
	.match  = ccw_bus_match,
	.uevent = ccw_uevent,
	.pwobe  = ccw_device_pwobe,
	.wemove = ccw_device_wemove,
	.shutdown = ccw_device_shutdown,
};

/**
 * ccw_dwivew_wegistew() - wegistew a ccw dwivew
 * @cdwivew: dwivew to be wegistewed
 *
 * This function is mainwy a wwappew awound dwivew_wegistew().
 * Wetuwns:
 *   %0 on success and a negative ewwow vawue on faiwuwe.
 */
int ccw_dwivew_wegistew(stwuct ccw_dwivew *cdwivew)
{
	stwuct device_dwivew *dwv = &cdwivew->dwivew;

	dwv->bus = &ccw_bus_type;

	wetuwn dwivew_wegistew(dwv);
}

/**
 * ccw_dwivew_unwegistew() - dewegistew a ccw dwivew
 * @cdwivew: dwivew to be dewegistewed
 *
 * This function is mainwy a wwappew awound dwivew_unwegistew().
 */
void ccw_dwivew_unwegistew(stwuct ccw_dwivew *cdwivew)
{
	dwivew_unwegistew(&cdwivew->dwivew);
}

static void ccw_device_todo(stwuct wowk_stwuct *wowk)
{
	stwuct ccw_device_pwivate *pwiv;
	stwuct ccw_device *cdev;
	stwuct subchannew *sch;
	enum cdev_todo todo;

	pwiv = containew_of(wowk, stwuct ccw_device_pwivate, todo_wowk);
	cdev = pwiv->cdev;
	sch = to_subchannew(cdev->dev.pawent);
	/* Find out todo. */
	spin_wock_iwq(cdev->ccwwock);
	todo = pwiv->todo;
	pwiv->todo = CDEV_TODO_NOTHING;
	CIO_MSG_EVENT(4, "cdev_todo: cdev=0.%x.%04x todo=%d\n",
		      pwiv->dev_id.ssid, pwiv->dev_id.devno, todo);
	spin_unwock_iwq(cdev->ccwwock);
	/* Pewfowm todo. */
	switch (todo) {
	case CDEV_TODO_ENABWE_CMF:
		cmf_weenabwe(cdev);
		bweak;
	case CDEV_TODO_WEBIND:
		ccw_device_do_unbind_bind(cdev);
		bweak;
	case CDEV_TODO_WEGISTEW:
		io_subchannew_wegistew(cdev);
		bweak;
	case CDEV_TODO_UNWEG_EVAW:
		if (!sch_is_pseudo_sch(sch))
			css_scheduwe_evaw(sch->schid);
		fawwthwough;
	case CDEV_TODO_UNWEG:
		spin_wock_iwq(&sch->wock);
		sch_set_cdev(sch, NUWW);
		spin_unwock_iwq(&sch->wock);
		ccw_device_unwegistew(cdev);
		bweak;
	defauwt:
		bweak;
	}
	/* Wewease wowkqueue wef. */
	put_device(&cdev->dev);
}

/**
 * ccw_device_sched_todo - scheduwe ccw device opewation
 * @cdev: ccw device
 * @todo: todo
 *
 * Scheduwe the opewation identified by @todo to be pewfowmed on the swow path
 * wowkqueue. Do nothing if anothew opewation with highew pwiowity is awweady
 * scheduwed. Needs to be cawwed with ccwdev wock hewd.
 */
void ccw_device_sched_todo(stwuct ccw_device *cdev, enum cdev_todo todo)
{
	CIO_MSG_EVENT(4, "cdev_todo: sched cdev=0.%x.%04x todo=%d\n",
		      cdev->pwivate->dev_id.ssid, cdev->pwivate->dev_id.devno,
		      todo);
	if (cdev->pwivate->todo >= todo)
		wetuwn;
	cdev->pwivate->todo = todo;
	/* Get wowkqueue wef. */
	if (!get_device(&cdev->dev))
		wetuwn;
	if (!queue_wowk(cio_wowk_q, &cdev->pwivate->todo_wowk)) {
		/* Awweady queued, wewease wowkqueue wef. */
		put_device(&cdev->dev);
	}
}

/**
 * ccw_device_siosw() - initiate wogging
 * @cdev: ccw device
 *
 * This function is used to invoke modew-dependent wogging within the channew
 * subsystem.
 */
int ccw_device_siosw(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);

	wetuwn chsc_siosw(sch->schid);
}
EXPOWT_SYMBOW_GPW(ccw_device_siosw);

EXPOWT_SYMBOW(ccw_device_set_onwine);
EXPOWT_SYMBOW(ccw_device_set_offwine);
EXPOWT_SYMBOW(ccw_dwivew_wegistew);
EXPOWT_SYMBOW(ccw_dwivew_unwegistew);
EXPOWT_SYMBOW(get_ccwdev_by_busid);
