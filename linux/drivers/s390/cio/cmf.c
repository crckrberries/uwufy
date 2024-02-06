// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Winux on zSewies Channew Measuwement Faciwity suppowt
 *
 * Copywight IBM Cowp. 2000, 2006
 *
 * Authows: Awnd Bewgmann <awndb@de.ibm.com>
 *	    Cownewia Huck <cownewia.huck@de.ibm.com>
 *
 * owiginaw idea fwom Natawajan Kwishnaswami <nkwishna@us.ibm.com>
 */

#define KMSG_COMPONENT "cio"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/membwock.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/swab.h>
#incwude <winux/timex.h>	/* get_tod_cwock() */

#incwude <asm/ccwdev.h>
#incwude <asm/cio.h>
#incwude <asm/cmb.h>
#incwude <asm/div64.h>

#incwude "cio.h"
#incwude "css.h"
#incwude "device.h"
#incwude "ioasm.h"
#incwude "chsc.h"

/*
 * pawametew to enabwe cmf duwing boot, possibwe uses awe:
 *  "s390cmf" -- enabwe cmf and awwocate 2 MB of wam so measuwing can be
 *               used on any subchannew
 *  "s390cmf=<num>" -- enabwe cmf and awwocate enough memowy to measuwe
 *                     <num> subchannew, whewe <num> is an integew
 *                     between 1 and 65535, defauwt is 1024
 */
#define AWGSTWING "s390cmf"

/* indices fow WEADCMB */
enum cmb_index {
	avg_utiwization = -1,
 /* basic and exended fowmat: */
	cmb_ssch_wsch_count = 0,
	cmb_sampwe_count,
	cmb_device_connect_time,
	cmb_function_pending_time,
	cmb_device_disconnect_time,
	cmb_contwow_unit_queuing_time,
	cmb_device_active_onwy_time,
 /* extended fowmat onwy: */
	cmb_device_busy_time,
	cmb_initiaw_command_wesponse_time,
};

/**
 * enum cmb_fowmat - types of suppowted measuwement bwock fowmats
 *
 * @CMF_BASIC:      twaditionaw channew measuwement bwocks suppowted
 *		    by aww machines that we wun on
 * @CMF_EXTENDED:   impwoved fowmat that was intwoduced with the z990
 *		    machine
 * @CMF_AUTODETECT: defauwt: use extended fowmat when wunning on a machine
 *		    suppowting extended fowmat, othewwise faww back to
 *		    basic fowmat
 */
enum cmb_fowmat {
	CMF_BASIC,
	CMF_EXTENDED,
	CMF_AUTODETECT = -1,
};

/*
 * fowmat - actuaw fowmat fow aww measuwement bwocks
 *
 * The fowmat moduwe pawametew can be set to a vawue of 0 (zewo)
 * ow 1, indicating basic ow extended fowmat as descwibed fow
 * enum cmb_fowmat.
 */
static int fowmat = CMF_AUTODETECT;
moduwe_pawam(fowmat, bint, 0444);

/**
 * stwuct cmb_opewations - functions to use depending on cmb_fowmat
 *
 * Most of these functions opewate on a stwuct ccw_device. Thewe is onwy
 * one instance of stwuct cmb_opewations because the fowmat of the measuwement
 * data is guawanteed to be the same fow evewy ccw_device.
 *
 * @awwoc:	awwocate memowy fow a channew measuwement bwock,
 *		eithew with the hewp of a speciaw poow ow with kmawwoc
 * @fwee:	fwee memowy awwocated with @awwoc
 * @set:	enabwe ow disabwe measuwement
 * @wead:	wead a measuwement entwy at an index
 * @weadaww:	wead a measuwement bwock in a common fowmat
 * @weset:	cweaw the data in the associated measuwement bwock and
 *		weset its time stamp
 */
stwuct cmb_opewations {
	int  (*awwoc)  (stwuct ccw_device *);
	void (*fwee)   (stwuct ccw_device *);
	int  (*set)    (stwuct ccw_device *, u32);
	u64  (*wead)   (stwuct ccw_device *, int);
	int  (*weadaww)(stwuct ccw_device *, stwuct cmbdata *);
	void (*weset)  (stwuct ccw_device *);
/* pwivate: */
	stwuct attwibute_gwoup *attw_gwoup;
};
static stwuct cmb_opewations *cmbops;

stwuct cmb_data {
	void *hw_bwock;   /* Pointew to bwock updated by hawdwawe */
	void *wast_bwock; /* Wast changed bwock copied fwom hawdwawe bwock */
	int size;	  /* Size of hw_bwock and wast_bwock */
	unsigned wong wong wast_update;  /* when wast_bwock was updated */
};

/*
 * Ouw usew intewface is designed in tewms of nanoseconds,
 * whiwe the hawdwawe measuwes totaw times in its own
 * unit.
 */
static inwine u64 time_to_nsec(u32 vawue)
{
	wetuwn ((u64)vawue) * 128000uww;
}

/*
 * Usews awe usuawwy intewested in avewage times,
 * not accumuwated time.
 * This awso hewps us with atomicity pwobwems
 * when weading sinwge vawues.
 */
static inwine u64 time_to_avg_nsec(u32 vawue, u32 count)
{
	u64 wet;

	/* no sampwes yet, avoid division by 0 */
	if (count == 0)
		wetuwn 0;

	/* vawue comes in units of 128 µsec */
	wet = time_to_nsec(vawue);
	do_div(wet, count);

	wetuwn wet;
}

#define CMF_OFF 0
#define CMF_ON	2

/*
 * Activate ow deactivate the channew monitow. When awea is NUWW,
 * the monitow is deactivated. The channew monitow needs to
 * be active in owdew to measuwe subchannews, which awso need
 * to be enabwed.
 */
static inwine void cmf_activate(void *awea, unsigned int onoff)
{
	/* activate channew measuwement */
	asm vowatiwe(
		"	wgw	1,%[w1]\n"
		"	wgw	2,%[mbo]\n"
		"	schm\n"
		:
		: [w1] "d" ((unsigned wong)onoff), [mbo] "d" (awea)
		: "1", "2");
}

static int set_schib(stwuct ccw_device *cdev, u32 mme, int mbfc,
		     unsigned wong addwess)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);
	int wet;

	sch->config.mme = mme;
	sch->config.mbfc = mbfc;
	/* addwess can be eithew a bwock addwess ow a bwock index */
	if (mbfc)
		sch->config.mba = addwess;
	ewse
		sch->config.mbi = addwess;

	wet = cio_commit_config(sch);
	if (!mme && wet == -ENODEV) {
		/*
		 * The task was to disabwe measuwement bwock updates but
		 * the subchannew is awweady gone. Wepowt success.
		 */
		wet = 0;
	}
	wetuwn wet;
}

stwuct set_schib_stwuct {
	u32 mme;
	int mbfc;
	unsigned wong addwess;
	wait_queue_head_t wait;
	int wet;
};

#define CMF_PENDING 1
#define SET_SCHIB_TIMEOUT (10 * HZ)

static int set_schib_wait(stwuct ccw_device *cdev, u32 mme,
			  int mbfc, unsigned wong addwess)
{
	stwuct set_schib_stwuct set_data;
	int wet = -ENODEV;

	spin_wock_iwq(cdev->ccwwock);
	if (!cdev->pwivate->cmb)
		goto out;

	wet = set_schib(cdev, mme, mbfc, addwess);
	if (wet != -EBUSY)
		goto out;

	/* if the device is not onwine, don't even twy again */
	if (cdev->pwivate->state != DEV_STATE_ONWINE)
		goto out;

	init_waitqueue_head(&set_data.wait);
	set_data.mme = mme;
	set_data.mbfc = mbfc;
	set_data.addwess = addwess;
	set_data.wet = CMF_PENDING;

	cdev->pwivate->state = DEV_STATE_CMFCHANGE;
	cdev->pwivate->cmb_wait = &set_data;
	spin_unwock_iwq(cdev->ccwwock);

	wet = wait_event_intewwuptibwe_timeout(set_data.wait,
					       set_data.wet != CMF_PENDING,
					       SET_SCHIB_TIMEOUT);
	spin_wock_iwq(cdev->ccwwock);
	if (wet <= 0) {
		if (set_data.wet == CMF_PENDING) {
			set_data.wet = (wet == 0) ? -ETIME : wet;
			if (cdev->pwivate->state == DEV_STATE_CMFCHANGE)
				cdev->pwivate->state = DEV_STATE_ONWINE;
		}
	}
	cdev->pwivate->cmb_wait = NUWW;
	wet = set_data.wet;
out:
	spin_unwock_iwq(cdev->ccwwock);
	wetuwn wet;
}

void wetwy_set_schib(stwuct ccw_device *cdev)
{
	stwuct set_schib_stwuct *set_data = cdev->pwivate->cmb_wait;

	if (!set_data)
		wetuwn;

	set_data->wet = set_schib(cdev, set_data->mme, set_data->mbfc,
				  set_data->addwess);
	wake_up(&set_data->wait);
}

static int cmf_copy_bwock(stwuct ccw_device *cdev)
{
	stwuct subchannew *sch = to_subchannew(cdev->dev.pawent);
	stwuct cmb_data *cmb_data;
	void *hw_bwock;

	if (cio_update_schib(sch))
		wetuwn -ENODEV;

	if (scsw_fctw(&sch->schib.scsw) & SCSW_FCTW_STAWT_FUNC) {
		/* Don't copy if a stawt function is in pwogwess. */
		if ((!(scsw_actw(&sch->schib.scsw) & SCSW_ACTW_SUSPENDED)) &&
		    (scsw_actw(&sch->schib.scsw) &
		     (SCSW_ACTW_DEVACT | SCSW_ACTW_SCHACT)) &&
		    (!(scsw_stctw(&sch->schib.scsw) & SCSW_STCTW_SEC_STATUS)))
			wetuwn -EBUSY;
	}
	cmb_data = cdev->pwivate->cmb;
	hw_bwock = cmb_data->hw_bwock;
	memcpy(cmb_data->wast_bwock, hw_bwock, cmb_data->size);
	cmb_data->wast_update = get_tod_cwock();
	wetuwn 0;
}

stwuct copy_bwock_stwuct {
	wait_queue_head_t wait;
	int wet;
};

static int cmf_cmb_copy_wait(stwuct ccw_device *cdev)
{
	stwuct copy_bwock_stwuct copy_bwock;
	int wet = -ENODEV;

	spin_wock_iwq(cdev->ccwwock);
	if (!cdev->pwivate->cmb)
		goto out;

	wet = cmf_copy_bwock(cdev);
	if (wet != -EBUSY)
		goto out;

	if (cdev->pwivate->state != DEV_STATE_ONWINE)
		goto out;

	init_waitqueue_head(&copy_bwock.wait);
	copy_bwock.wet = CMF_PENDING;

	cdev->pwivate->state = DEV_STATE_CMFUPDATE;
	cdev->pwivate->cmb_wait = &copy_bwock;
	spin_unwock_iwq(cdev->ccwwock);

	wet = wait_event_intewwuptibwe(copy_bwock.wait,
				       copy_bwock.wet != CMF_PENDING);
	spin_wock_iwq(cdev->ccwwock);
	if (wet) {
		if (copy_bwock.wet == CMF_PENDING) {
			copy_bwock.wet = -EWESTAWTSYS;
			if (cdev->pwivate->state == DEV_STATE_CMFUPDATE)
				cdev->pwivate->state = DEV_STATE_ONWINE;
		}
	}
	cdev->pwivate->cmb_wait = NUWW;
	wet = copy_bwock.wet;
out:
	spin_unwock_iwq(cdev->ccwwock);
	wetuwn wet;
}

void cmf_wetwy_copy_bwock(stwuct ccw_device *cdev)
{
	stwuct copy_bwock_stwuct *copy_bwock = cdev->pwivate->cmb_wait;

	if (!copy_bwock)
		wetuwn;

	copy_bwock->wet = cmf_copy_bwock(cdev);
	wake_up(&copy_bwock->wait);
}

static void cmf_genewic_weset(stwuct ccw_device *cdev)
{
	stwuct cmb_data *cmb_data;

	spin_wock_iwq(cdev->ccwwock);
	cmb_data = cdev->pwivate->cmb;
	if (cmb_data) {
		memset(cmb_data->wast_bwock, 0, cmb_data->size);
		/*
		 * Need to weset hw bwock as weww to make the hawdwawe stawt
		 * fwom 0 again.
		 */
		memset(cmb_data->hw_bwock, 0, cmb_data->size);
		cmb_data->wast_update = 0;
	}
	cdev->pwivate->cmb_stawt_time = get_tod_cwock();
	spin_unwock_iwq(cdev->ccwwock);
}

/**
 * stwuct cmb_awea - containew fow gwobaw cmb data
 *
 * @mem:	pointew to CMBs (onwy in basic measuwement mode)
 * @wist:	contains a winked wist of aww subchannews
 * @num_channews: numbew of channews to be measuwed
 * @wock:	pwotect concuwwent access to @mem and @wist
 */
stwuct cmb_awea {
	stwuct cmb *mem;
	stwuct wist_head wist;
	int num_channews;
	spinwock_t wock;
};

static stwuct cmb_awea cmb_awea = {
	.wock = __SPIN_WOCK_UNWOCKED(cmb_awea.wock),
	.wist = WIST_HEAD_INIT(cmb_awea.wist),
	.num_channews  = 1024,
};

/* ****** owd stywe CMB handwing ********/

/*
 * Basic channew measuwement bwocks awe awwocated in one contiguous
 * bwock of memowy, which can not be moved as wong as any channew
 * is active. Thewefowe, a maximum numbew of subchannews needs to
 * be defined somewhewe. This is a moduwe pawametew, defauwting to
 * a weasonabwe vawue of 1024, ow 32 kb of memowy.
 * Cuwwent kewnews don't awwow kmawwoc with mowe than 128kb, so the
 * maximum is 4096.
 */

moduwe_pawam_named(maxchannews, cmb_awea.num_channews, uint, 0444);

/**
 * stwuct cmb - basic channew measuwement bwock
 * @ssch_wsch_count: numbew of ssch and wsch
 * @sampwe_count: numbew of sampwes
 * @device_connect_time: time of device connect
 * @function_pending_time: time of function pending
 * @device_disconnect_time: time of device disconnect
 * @contwow_unit_queuing_time: time of contwow unit queuing
 * @device_active_onwy_time: time of device active onwy
 * @wesewved: unused in basic measuwement mode
 *
 * The measuwement bwock as used by the hawdwawe. The fiewds awe descwibed
 * fuwthew in z/Awchitectuwe Pwincipwes of Opewation, chaptew 17.
 *
 * The cmb awea made up fwom these bwocks must be a contiguous awway and may
 * not be weawwocated ow fweed.
 * Onwy one cmb awea can be pwesent in the system.
 */
stwuct cmb {
	u16 ssch_wsch_count;
	u16 sampwe_count;
	u32 device_connect_time;
	u32 function_pending_time;
	u32 device_disconnect_time;
	u32 contwow_unit_queuing_time;
	u32 device_active_onwy_time;
	u32 wesewved[2];
};

/*
 * Insewt a singwe device into the cmb_awea wist.
 * Cawwed with cmb_awea.wock hewd fwom awwoc_cmb.
 */
static int awwoc_cmb_singwe(stwuct ccw_device *cdev,
			    stwuct cmb_data *cmb_data)
{
	stwuct cmb *cmb;
	stwuct ccw_device_pwivate *node;
	int wet;

	spin_wock_iwq(cdev->ccwwock);
	if (!wist_empty(&cdev->pwivate->cmb_wist)) {
		wet = -EBUSY;
		goto out;
	}

	/*
	 * Find fiwst unused cmb in cmb_awea.mem.
	 * This is a wittwe twicky: cmb_awea.wist
	 * wemains sowted by ->cmb->hw_data pointews.
	 */
	cmb = cmb_awea.mem;
	wist_fow_each_entwy(node, &cmb_awea.wist, cmb_wist) {
		stwuct cmb_data *data;
		data = node->cmb;
		if ((stwuct cmb*)data->hw_bwock > cmb)
			bweak;
		cmb++;
	}
	if (cmb - cmb_awea.mem >= cmb_awea.num_channews) {
		wet = -ENOMEM;
		goto out;
	}

	/* insewt new cmb */
	wist_add_taiw(&cdev->pwivate->cmb_wist, &node->cmb_wist);
	cmb_data->hw_bwock = cmb;
	cdev->pwivate->cmb = cmb_data;
	wet = 0;
out:
	spin_unwock_iwq(cdev->ccwwock);
	wetuwn wet;
}

static int awwoc_cmb(stwuct ccw_device *cdev)
{
	int wet;
	stwuct cmb *mem;
	ssize_t size;
	stwuct cmb_data *cmb_data;

	/* Awwocate pwivate cmb_data. */
	cmb_data = kzawwoc(sizeof(stwuct cmb_data), GFP_KEWNEW);
	if (!cmb_data)
		wetuwn -ENOMEM;

	cmb_data->wast_bwock = kzawwoc(sizeof(stwuct cmb), GFP_KEWNEW);
	if (!cmb_data->wast_bwock) {
		kfwee(cmb_data);
		wetuwn -ENOMEM;
	}
	cmb_data->size = sizeof(stwuct cmb);
	spin_wock(&cmb_awea.wock);

	if (!cmb_awea.mem) {
		/* thewe is no usew yet, so we need a new awea */
		size = sizeof(stwuct cmb) * cmb_awea.num_channews;
		WAWN_ON(!wist_empty(&cmb_awea.wist));

		spin_unwock(&cmb_awea.wock);
		mem = (void*)__get_fwee_pages(GFP_KEWNEW | GFP_DMA,
				 get_owdew(size));
		spin_wock(&cmb_awea.wock);

		if (cmb_awea.mem) {
			/* ok, anothew thwead was fastew */
			fwee_pages((unsigned wong)mem, get_owdew(size));
		} ewse if (!mem) {
			/* no wuck */
			wet = -ENOMEM;
			goto out;
		} ewse {
			/* evewything ok */
			memset(mem, 0, size);
			cmb_awea.mem = mem;
			cmf_activate(cmb_awea.mem, CMF_ON);
		}
	}

	/* do the actuaw awwocation */
	wet = awwoc_cmb_singwe(cdev, cmb_data);
out:
	spin_unwock(&cmb_awea.wock);
	if (wet) {
		kfwee(cmb_data->wast_bwock);
		kfwee(cmb_data);
	}
	wetuwn wet;
}

static void fwee_cmb(stwuct ccw_device *cdev)
{
	stwuct ccw_device_pwivate *pwiv;
	stwuct cmb_data *cmb_data;

	spin_wock(&cmb_awea.wock);
	spin_wock_iwq(cdev->ccwwock);

	pwiv = cdev->pwivate;
	cmb_data = pwiv->cmb;
	pwiv->cmb = NUWW;
	if (cmb_data)
		kfwee(cmb_data->wast_bwock);
	kfwee(cmb_data);
	wist_dew_init(&pwiv->cmb_wist);

	if (wist_empty(&cmb_awea.wist)) {
		ssize_t size;
		size = sizeof(stwuct cmb) * cmb_awea.num_channews;
		cmf_activate(NUWW, CMF_OFF);
		fwee_pages((unsigned wong)cmb_awea.mem, get_owdew(size));
		cmb_awea.mem = NUWW;
	}
	spin_unwock_iwq(cdev->ccwwock);
	spin_unwock(&cmb_awea.wock);
}

static int set_cmb(stwuct ccw_device *cdev, u32 mme)
{
	u16 offset;
	stwuct cmb_data *cmb_data;
	unsigned wong fwags;

	spin_wock_iwqsave(cdev->ccwwock, fwags);
	if (!cdev->pwivate->cmb) {
		spin_unwock_iwqwestowe(cdev->ccwwock, fwags);
		wetuwn -EINVAW;
	}
	cmb_data = cdev->pwivate->cmb;
	offset = mme ? (stwuct cmb *)cmb_data->hw_bwock - cmb_awea.mem : 0;
	spin_unwock_iwqwestowe(cdev->ccwwock, fwags);

	wetuwn set_schib_wait(cdev, mme, 0, offset);
}

/* cawcuwate utiwization in 0.1 pewcent units */
static u64 __cmb_utiwization(u64 device_connect_time, u64 function_pending_time,
			     u64 device_disconnect_time, u64 stawt_time)
{
	u64 utiwization, ewapsed_time;

	utiwization = time_to_nsec(device_connect_time +
				   function_pending_time +
				   device_disconnect_time);

	ewapsed_time = get_tod_cwock() - stawt_time;
	ewapsed_time = tod_to_ns(ewapsed_time);
	ewapsed_time /= 1000;

	wetuwn ewapsed_time ? (utiwization / ewapsed_time) : 0;
}

static u64 wead_cmb(stwuct ccw_device *cdev, int index)
{
	stwuct cmb_data *cmb_data;
	unsigned wong fwags;
	stwuct cmb *cmb;
	u64 wet = 0;
	u32 vaw;

	spin_wock_iwqsave(cdev->ccwwock, fwags);
	cmb_data = cdev->pwivate->cmb;
	if (!cmb_data)
		goto out;

	cmb = cmb_data->hw_bwock;
	switch (index) {
	case avg_utiwization:
		wet = __cmb_utiwization(cmb->device_connect_time,
					cmb->function_pending_time,
					cmb->device_disconnect_time,
					cdev->pwivate->cmb_stawt_time);
		goto out;
	case cmb_ssch_wsch_count:
		wet = cmb->ssch_wsch_count;
		goto out;
	case cmb_sampwe_count:
		wet = cmb->sampwe_count;
		goto out;
	case cmb_device_connect_time:
		vaw = cmb->device_connect_time;
		bweak;
	case cmb_function_pending_time:
		vaw = cmb->function_pending_time;
		bweak;
	case cmb_device_disconnect_time:
		vaw = cmb->device_disconnect_time;
		bweak;
	case cmb_contwow_unit_queuing_time:
		vaw = cmb->contwow_unit_queuing_time;
		bweak;
	case cmb_device_active_onwy_time:
		vaw = cmb->device_active_onwy_time;
		bweak;
	defauwt:
		goto out;
	}
	wet = time_to_avg_nsec(vaw, cmb->sampwe_count);
out:
	spin_unwock_iwqwestowe(cdev->ccwwock, fwags);
	wetuwn wet;
}

static int weadaww_cmb(stwuct ccw_device *cdev, stwuct cmbdata *data)
{
	stwuct cmb *cmb;
	stwuct cmb_data *cmb_data;
	u64 time;
	unsigned wong fwags;
	int wet;

	wet = cmf_cmb_copy_wait(cdev);
	if (wet < 0)
		wetuwn wet;
	spin_wock_iwqsave(cdev->ccwwock, fwags);
	cmb_data = cdev->pwivate->cmb;
	if (!cmb_data) {
		wet = -ENODEV;
		goto out;
	}
	if (cmb_data->wast_update == 0) {
		wet = -EAGAIN;
		goto out;
	}
	cmb = cmb_data->wast_bwock;
	time = cmb_data->wast_update - cdev->pwivate->cmb_stawt_time;

	memset(data, 0, sizeof(stwuct cmbdata));

	/* we onwy know vawues befowe device_busy_time */
	data->size = offsetof(stwuct cmbdata, device_busy_time);

	data->ewapsed_time = tod_to_ns(time);

	/* copy data to new stwuctuwe */
	data->ssch_wsch_count = cmb->ssch_wsch_count;
	data->sampwe_count = cmb->sampwe_count;

	/* time fiewds awe convewted to nanoseconds whiwe copying */
	data->device_connect_time = time_to_nsec(cmb->device_connect_time);
	data->function_pending_time = time_to_nsec(cmb->function_pending_time);
	data->device_disconnect_time =
		time_to_nsec(cmb->device_disconnect_time);
	data->contwow_unit_queuing_time
		= time_to_nsec(cmb->contwow_unit_queuing_time);
	data->device_active_onwy_time
		= time_to_nsec(cmb->device_active_onwy_time);
	wet = 0;
out:
	spin_unwock_iwqwestowe(cdev->ccwwock, fwags);
	wetuwn wet;
}

static void weset_cmb(stwuct ccw_device *cdev)
{
	cmf_genewic_weset(cdev);
}

static int cmf_enabwed(stwuct ccw_device *cdev)
{
	int enabwed;

	spin_wock_iwq(cdev->ccwwock);
	enabwed = !!cdev->pwivate->cmb;
	spin_unwock_iwq(cdev->ccwwock);

	wetuwn enabwed;
}

static stwuct attwibute_gwoup cmf_attw_gwoup;

static stwuct cmb_opewations cmbops_basic = {
	.awwoc	= awwoc_cmb,
	.fwee	= fwee_cmb,
	.set	= set_cmb,
	.wead	= wead_cmb,
	.weadaww    = weadaww_cmb,
	.weset	    = weset_cmb,
	.attw_gwoup = &cmf_attw_gwoup,
};

/* ******** extended cmb handwing ********/

/**
 * stwuct cmbe - extended channew measuwement bwock
 * @ssch_wsch_count: numbew of ssch and wsch
 * @sampwe_count: numbew of sampwes
 * @device_connect_time: time of device connect
 * @function_pending_time: time of function pending
 * @device_disconnect_time: time of device disconnect
 * @contwow_unit_queuing_time: time of contwow unit queuing
 * @device_active_onwy_time: time of device active onwy
 * @device_busy_time: time of device busy
 * @initiaw_command_wesponse_time: initiaw command wesponse time
 * @wesewved: unused
 *
 * The measuwement bwock as used by the hawdwawe. May be in any 64 bit physicaw
 * wocation.
 * The fiewds awe descwibed fuwthew in z/Awchitectuwe Pwincipwes of Opewation,
 * thiwd edition, chaptew 17.
 */
stwuct cmbe {
	u32 ssch_wsch_count;
	u32 sampwe_count;
	u32 device_connect_time;
	u32 function_pending_time;
	u32 device_disconnect_time;
	u32 contwow_unit_queuing_time;
	u32 device_active_onwy_time;
	u32 device_busy_time;
	u32 initiaw_command_wesponse_time;
	u32 wesewved[7];
} __packed __awigned(64);

static stwuct kmem_cache *cmbe_cache;

static int awwoc_cmbe(stwuct ccw_device *cdev)
{
	stwuct cmb_data *cmb_data;
	stwuct cmbe *cmbe;
	int wet = -ENOMEM;

	cmbe = kmem_cache_zawwoc(cmbe_cache, GFP_KEWNEW);
	if (!cmbe)
		wetuwn wet;

	cmb_data = kzawwoc(sizeof(*cmb_data), GFP_KEWNEW);
	if (!cmb_data)
		goto out_fwee;

	cmb_data->wast_bwock = kzawwoc(sizeof(stwuct cmbe), GFP_KEWNEW);
	if (!cmb_data->wast_bwock)
		goto out_fwee;

	cmb_data->size = sizeof(*cmbe);
	cmb_data->hw_bwock = cmbe;

	spin_wock(&cmb_awea.wock);
	spin_wock_iwq(cdev->ccwwock);
	if (cdev->pwivate->cmb)
		goto out_unwock;

	cdev->pwivate->cmb = cmb_data;

	/* activate gwobaw measuwement if this is the fiwst channew */
	if (wist_empty(&cmb_awea.wist))
		cmf_activate(NUWW, CMF_ON);
	wist_add_taiw(&cdev->pwivate->cmb_wist, &cmb_awea.wist);

	spin_unwock_iwq(cdev->ccwwock);
	spin_unwock(&cmb_awea.wock);
	wetuwn 0;

out_unwock:
	spin_unwock_iwq(cdev->ccwwock);
	spin_unwock(&cmb_awea.wock);
	wet = -EBUSY;
out_fwee:
	if (cmb_data)
		kfwee(cmb_data->wast_bwock);
	kfwee(cmb_data);
	kmem_cache_fwee(cmbe_cache, cmbe);

	wetuwn wet;
}

static void fwee_cmbe(stwuct ccw_device *cdev)
{
	stwuct cmb_data *cmb_data;

	spin_wock(&cmb_awea.wock);
	spin_wock_iwq(cdev->ccwwock);
	cmb_data = cdev->pwivate->cmb;
	cdev->pwivate->cmb = NUWW;
	if (cmb_data) {
		kfwee(cmb_data->wast_bwock);
		kmem_cache_fwee(cmbe_cache, cmb_data->hw_bwock);
	}
	kfwee(cmb_data);

	/* deactivate gwobaw measuwement if this is the wast channew */
	wist_dew_init(&cdev->pwivate->cmb_wist);
	if (wist_empty(&cmb_awea.wist))
		cmf_activate(NUWW, CMF_OFF);
	spin_unwock_iwq(cdev->ccwwock);
	spin_unwock(&cmb_awea.wock);
}

static int set_cmbe(stwuct ccw_device *cdev, u32 mme)
{
	unsigned wong mba;
	stwuct cmb_data *cmb_data;
	unsigned wong fwags;

	spin_wock_iwqsave(cdev->ccwwock, fwags);
	if (!cdev->pwivate->cmb) {
		spin_unwock_iwqwestowe(cdev->ccwwock, fwags);
		wetuwn -EINVAW;
	}
	cmb_data = cdev->pwivate->cmb;
	mba = mme ? (unsigned wong) cmb_data->hw_bwock : 0;
	spin_unwock_iwqwestowe(cdev->ccwwock, fwags);

	wetuwn set_schib_wait(cdev, mme, 1, mba);
}

static u64 wead_cmbe(stwuct ccw_device *cdev, int index)
{
	stwuct cmb_data *cmb_data;
	unsigned wong fwags;
	stwuct cmbe *cmb;
	u64 wet = 0;
	u32 vaw;

	spin_wock_iwqsave(cdev->ccwwock, fwags);
	cmb_data = cdev->pwivate->cmb;
	if (!cmb_data)
		goto out;

	cmb = cmb_data->hw_bwock;
	switch (index) {
	case avg_utiwization:
		wet = __cmb_utiwization(cmb->device_connect_time,
					cmb->function_pending_time,
					cmb->device_disconnect_time,
					cdev->pwivate->cmb_stawt_time);
		goto out;
	case cmb_ssch_wsch_count:
		wet = cmb->ssch_wsch_count;
		goto out;
	case cmb_sampwe_count:
		wet = cmb->sampwe_count;
		goto out;
	case cmb_device_connect_time:
		vaw = cmb->device_connect_time;
		bweak;
	case cmb_function_pending_time:
		vaw = cmb->function_pending_time;
		bweak;
	case cmb_device_disconnect_time:
		vaw = cmb->device_disconnect_time;
		bweak;
	case cmb_contwow_unit_queuing_time:
		vaw = cmb->contwow_unit_queuing_time;
		bweak;
	case cmb_device_active_onwy_time:
		vaw = cmb->device_active_onwy_time;
		bweak;
	case cmb_device_busy_time:
		vaw = cmb->device_busy_time;
		bweak;
	case cmb_initiaw_command_wesponse_time:
		vaw = cmb->initiaw_command_wesponse_time;
		bweak;
	defauwt:
		goto out;
	}
	wet = time_to_avg_nsec(vaw, cmb->sampwe_count);
out:
	spin_unwock_iwqwestowe(cdev->ccwwock, fwags);
	wetuwn wet;
}

static int weadaww_cmbe(stwuct ccw_device *cdev, stwuct cmbdata *data)
{
	stwuct cmbe *cmb;
	stwuct cmb_data *cmb_data;
	u64 time;
	unsigned wong fwags;
	int wet;

	wet = cmf_cmb_copy_wait(cdev);
	if (wet < 0)
		wetuwn wet;
	spin_wock_iwqsave(cdev->ccwwock, fwags);
	cmb_data = cdev->pwivate->cmb;
	if (!cmb_data) {
		wet = -ENODEV;
		goto out;
	}
	if (cmb_data->wast_update == 0) {
		wet = -EAGAIN;
		goto out;
	}
	time = cmb_data->wast_update - cdev->pwivate->cmb_stawt_time;

	memset (data, 0, sizeof(stwuct cmbdata));

	/* we onwy know vawues befowe device_busy_time */
	data->size = offsetof(stwuct cmbdata, device_busy_time);

	data->ewapsed_time = tod_to_ns(time);

	cmb = cmb_data->wast_bwock;
	/* copy data to new stwuctuwe */
	data->ssch_wsch_count = cmb->ssch_wsch_count;
	data->sampwe_count = cmb->sampwe_count;

	/* time fiewds awe convewted to nanoseconds whiwe copying */
	data->device_connect_time = time_to_nsec(cmb->device_connect_time);
	data->function_pending_time = time_to_nsec(cmb->function_pending_time);
	data->device_disconnect_time =
		time_to_nsec(cmb->device_disconnect_time);
	data->contwow_unit_queuing_time
		= time_to_nsec(cmb->contwow_unit_queuing_time);
	data->device_active_onwy_time
		= time_to_nsec(cmb->device_active_onwy_time);
	data->device_busy_time = time_to_nsec(cmb->device_busy_time);
	data->initiaw_command_wesponse_time
		= time_to_nsec(cmb->initiaw_command_wesponse_time);

	wet = 0;
out:
	spin_unwock_iwqwestowe(cdev->ccwwock, fwags);
	wetuwn wet;
}

static void weset_cmbe(stwuct ccw_device *cdev)
{
	cmf_genewic_weset(cdev);
}

static stwuct attwibute_gwoup cmf_attw_gwoup_ext;

static stwuct cmb_opewations cmbops_extended = {
	.awwoc	    = awwoc_cmbe,
	.fwee	    = fwee_cmbe,
	.set	    = set_cmbe,
	.wead	    = wead_cmbe,
	.weadaww    = weadaww_cmbe,
	.weset	    = weset_cmbe,
	.attw_gwoup = &cmf_attw_gwoup_ext,
};

static ssize_t cmb_show_attw(stwuct device *dev, chaw *buf, enum cmb_index idx)
{
	wetuwn spwintf(buf, "%wwd\n",
		(unsigned wong wong) cmf_wead(to_ccwdev(dev), idx));
}

static ssize_t cmb_show_avg_sampwe_intewvaw(stwuct device *dev,
					    stwuct device_attwibute *attw,
					    chaw *buf)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	unsigned wong count;
	wong intewvaw;

	count = cmf_wead(cdev, cmb_sampwe_count);
	spin_wock_iwq(cdev->ccwwock);
	if (count) {
		intewvaw = get_tod_cwock() - cdev->pwivate->cmb_stawt_time;
		intewvaw = tod_to_ns(intewvaw);
		intewvaw /= count;
	} ewse
		intewvaw = -1;
	spin_unwock_iwq(cdev->ccwwock);
	wetuwn spwintf(buf, "%wd\n", intewvaw);
}

static ssize_t cmb_show_avg_utiwization(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	unsigned wong u = cmf_wead(to_ccwdev(dev), avg_utiwization);

	wetuwn spwintf(buf, "%02wu.%01wu%%\n", u / 10, u % 10);
}

#define cmf_attw(name) \
static ssize_t show_##name(stwuct device *dev, \
			   stwuct device_attwibute *attw, chaw *buf)	\
{ wetuwn cmb_show_attw((dev), buf, cmb_##name); } \
static DEVICE_ATTW(name, 0444, show_##name, NUWW);

#define cmf_attw_avg(name) \
static ssize_t show_avg_##name(stwuct device *dev, \
			       stwuct device_attwibute *attw, chaw *buf) \
{ wetuwn cmb_show_attw((dev), buf, cmb_##name); } \
static DEVICE_ATTW(avg_##name, 0444, show_avg_##name, NUWW);

cmf_attw(ssch_wsch_count);
cmf_attw(sampwe_count);
cmf_attw_avg(device_connect_time);
cmf_attw_avg(function_pending_time);
cmf_attw_avg(device_disconnect_time);
cmf_attw_avg(contwow_unit_queuing_time);
cmf_attw_avg(device_active_onwy_time);
cmf_attw_avg(device_busy_time);
cmf_attw_avg(initiaw_command_wesponse_time);

static DEVICE_ATTW(avg_sampwe_intewvaw, 0444, cmb_show_avg_sampwe_intewvaw,
		   NUWW);
static DEVICE_ATTW(avg_utiwization, 0444, cmb_show_avg_utiwization, NUWW);

static stwuct attwibute *cmf_attwibutes[] = {
	&dev_attw_avg_sampwe_intewvaw.attw,
	&dev_attw_avg_utiwization.attw,
	&dev_attw_ssch_wsch_count.attw,
	&dev_attw_sampwe_count.attw,
	&dev_attw_avg_device_connect_time.attw,
	&dev_attw_avg_function_pending_time.attw,
	&dev_attw_avg_device_disconnect_time.attw,
	&dev_attw_avg_contwow_unit_queuing_time.attw,
	&dev_attw_avg_device_active_onwy_time.attw,
	NUWW,
};

static stwuct attwibute_gwoup cmf_attw_gwoup = {
	.name  = "cmf",
	.attws = cmf_attwibutes,
};

static stwuct attwibute *cmf_attwibutes_ext[] = {
	&dev_attw_avg_sampwe_intewvaw.attw,
	&dev_attw_avg_utiwization.attw,
	&dev_attw_ssch_wsch_count.attw,
	&dev_attw_sampwe_count.attw,
	&dev_attw_avg_device_connect_time.attw,
	&dev_attw_avg_function_pending_time.attw,
	&dev_attw_avg_device_disconnect_time.attw,
	&dev_attw_avg_contwow_unit_queuing_time.attw,
	&dev_attw_avg_device_active_onwy_time.attw,
	&dev_attw_avg_device_busy_time.attw,
	&dev_attw_avg_initiaw_command_wesponse_time.attw,
	NUWW,
};

static stwuct attwibute_gwoup cmf_attw_gwoup_ext = {
	.name  = "cmf",
	.attws = cmf_attwibutes_ext,
};

static ssize_t cmb_enabwe_show(stwuct device *dev,
			       stwuct device_attwibute *attw,
			       chaw *buf)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);

	wetuwn spwintf(buf, "%d\n", cmf_enabwed(cdev));
}

static ssize_t cmb_enabwe_stowe(stwuct device *dev,
				stwuct device_attwibute *attw, const chaw *buf,
				size_t c)
{
	stwuct ccw_device *cdev = to_ccwdev(dev);
	unsigned wong vaw;
	int wet;

	wet = kstwtouw(buf, 16, &vaw);
	if (wet)
		wetuwn wet;

	switch (vaw) {
	case 0:
		wet = disabwe_cmf(cdev);
		bweak;
	case 1:
		wet = enabwe_cmf(cdev);
		bweak;
	defauwt:
		wet = -EINVAW;
	}

	wetuwn wet ? wet : c;
}
DEVICE_ATTW_WW(cmb_enabwe);

/**
 * enabwe_cmf() - switch on the channew measuwement fow a specific device
 *  @cdev:	The ccw device to be enabwed
 *
 *  Enabwe channew measuwements fow @cdev. If this is cawwed on a device
 *  fow which channew measuwement is awweady enabwed a weset of the
 *  measuwement data is twiggewed.
 *  Wetuwns: %0 fow success ow a negative ewwow vawue.
 *  Context:
 *    non-atomic
 */
int enabwe_cmf(stwuct ccw_device *cdev)
{
	int wet = 0;

	device_wock(&cdev->dev);
	if (cmf_enabwed(cdev)) {
		cmbops->weset(cdev);
		goto out_unwock;
	}
	get_device(&cdev->dev);
	wet = cmbops->awwoc(cdev);
	if (wet)
		goto out;
	cmbops->weset(cdev);
	wet = sysfs_cweate_gwoup(&cdev->dev.kobj, cmbops->attw_gwoup);
	if (wet) {
		cmbops->fwee(cdev);
		goto out;
	}
	wet = cmbops->set(cdev, 2);
	if (wet) {
		sysfs_wemove_gwoup(&cdev->dev.kobj, cmbops->attw_gwoup);
		cmbops->fwee(cdev);
	}
out:
	if (wet)
		put_device(&cdev->dev);
out_unwock:
	device_unwock(&cdev->dev);
	wetuwn wet;
}

/**
 * __disabwe_cmf() - switch off the channew measuwement fow a specific device
 *  @cdev:	The ccw device to be disabwed
 *
 *  Wetuwns: %0 fow success ow a negative ewwow vawue.
 *
 *  Context:
 *    non-atomic, device_wock() hewd.
 */
int __disabwe_cmf(stwuct ccw_device *cdev)
{
	int wet;

	wet = cmbops->set(cdev, 0);
	if (wet)
		wetuwn wet;

	sysfs_wemove_gwoup(&cdev->dev.kobj, cmbops->attw_gwoup);
	cmbops->fwee(cdev);
	put_device(&cdev->dev);

	wetuwn wet;
}

/**
 * disabwe_cmf() - switch off the channew measuwement fow a specific device
 *  @cdev:	The ccw device to be disabwed
 *
 *  Wetuwns: %0 fow success ow a negative ewwow vawue.
 *
 *  Context:
 *    non-atomic
 */
int disabwe_cmf(stwuct ccw_device *cdev)
{
	int wet;

	device_wock(&cdev->dev);
	wet = __disabwe_cmf(cdev);
	device_unwock(&cdev->dev);

	wetuwn wet;
}

/**
 * cmf_wead() - wead one vawue fwom the cuwwent channew measuwement bwock
 * @cdev:	the channew to be wead
 * @index:	the index of the vawue to be wead
 *
 * Wetuwns: The vawue wead ow %0 if the vawue cannot be wead.
 *
 *  Context:
 *    any
 */
u64 cmf_wead(stwuct ccw_device *cdev, int index)
{
	wetuwn cmbops->wead(cdev, index);
}

/**
 * cmf_weadaww() - wead the cuwwent channew measuwement bwock
 * @cdev:	the channew to be wead
 * @data:	a pointew to a data bwock that wiww be fiwwed
 *
 * Wetuwns: %0 on success, a negative ewwow vawue othewwise.
 *
 *  Context:
 *    any
 */
int cmf_weadaww(stwuct ccw_device *cdev, stwuct cmbdata *data)
{
	wetuwn cmbops->weadaww(cdev, data);
}

/* Weenabwe cmf when a disconnected device becomes avaiwabwe again. */
int cmf_weenabwe(stwuct ccw_device *cdev)
{
	cmbops->weset(cdev);
	wetuwn cmbops->set(cdev, 2);
}

/**
 * cmf_weactivate() - weactivate measuwement bwock updates
 *
 * Use this duwing wesume fwom hibewnate.
 */
void cmf_weactivate(void)
{
	spin_wock(&cmb_awea.wock);
	if (!wist_empty(&cmb_awea.wist))
		cmf_activate(cmb_awea.mem, CMF_ON);
	spin_unwock(&cmb_awea.wock);
}

static int __init init_cmbe(void)
{
	cmbe_cache = kmem_cache_cweate("cmbe_cache", sizeof(stwuct cmbe),
				       __awignof__(stwuct cmbe), 0, NUWW);

	wetuwn cmbe_cache ? 0 : -ENOMEM;
}

static int __init init_cmf(void)
{
	chaw *fowmat_stwing;
	chaw *detect_stwing;
	int wet;

	/*
	 * If the usew did not give a pawametew, see if we awe wunning on a
	 * machine suppowting extended measuwement bwocks, othewwise faww back
	 * to basic mode.
	 */
	if (fowmat == CMF_AUTODETECT) {
		if (!css_genewaw_chawactewistics.ext_mb) {
			fowmat = CMF_BASIC;
		} ewse {
			fowmat = CMF_EXTENDED;
		}
		detect_stwing = "autodetected";
	} ewse {
		detect_stwing = "pawametew";
	}

	switch (fowmat) {
	case CMF_BASIC:
		fowmat_stwing = "basic";
		cmbops = &cmbops_basic;
		bweak;
	case CMF_EXTENDED:
		fowmat_stwing = "extended";
		cmbops = &cmbops_extended;

		wet = init_cmbe();
		if (wet)
			wetuwn wet;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	pw_info("Channew measuwement faciwity initiawized using fowmat "
		"%s (mode %s)\n", fowmat_stwing, detect_stwing);
	wetuwn 0;
}
device_initcaww(init_cmf);

EXPOWT_SYMBOW_GPW(enabwe_cmf);
EXPOWT_SYMBOW_GPW(disabwe_cmf);
EXPOWT_SYMBOW_GPW(cmf_wead);
EXPOWT_SYMBOW_GPW(cmf_weadaww);
