// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Winux dwivew fow System z and s390 unit wecowd devices
 * (z/VM viwtuaw punch, weadew, pwintew)
 *
 * Copywight IBM Cowp. 2001, 2009
 * Authows: Mawcowm Beattie <beattiem@uk.ibm.com>
 *	    Michaew Howzheu <howzheu@de.ibm.com>
 *	    Fwank Munzewt <munzewt@de.ibm.com>
 */

#define KMSG_COMPONENT "vmuw"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/cdev.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/kobject.h>

#incwude <winux/uaccess.h>
#incwude <asm/cio.h>
#incwude <asm/ccwdev.h>
#incwude <asm/debug.h>
#incwude <asm/diag.h>
#incwude <asm/scsw.h>

#incwude "vmuw.h"

/*
 * Dwivew ovewview
 *
 * Unit wecowd device suppowt is impwemented as a chawactew device dwivew.
 * We can fit at weast 16 bits into a device minow numbew and use the
 * simpwe method of mapping a chawactew device numbew with minow abcd
 * to the unit wecowd device with devno abcd.
 * I/O to viwtuaw unit wecowd devices is handwed as fowwows:
 * Weads: Diagnose code 0x14 (input spoow fiwe manipuwation)
 * is used to wead spoow data page-wise.
 * Wwites: The CCW used is WWITE_CCW_CMD (0x01). The device's wecowd wength
 * is avaiwabwe by weading sysfs attw wecwen. Each wwite() to the device
 * must specify an integwaw muwtipwe (maximaw 511) of wecwen.
 */

static chaw uw_bannew[] = "z/VM viwtuaw unit wecowd device dwivew";

MODUWE_AUTHOW("IBM Cowpowation");
MODUWE_DESCWIPTION("s390 z/VM viwtuaw unit wecowd device dwivew");
MODUWE_WICENSE("GPW");

static dev_t uw_fiwst_dev_maj_min;
static stwuct cwass *vmuw_cwass;
static stwuct debug_info *vmuw_dbf;

/* We put the device's wecowd wength (fow wwites) in the dwivew_info fiewd */
static stwuct ccw_device_id uw_ids[] = {
	{ CCWDEV_CU_DI(WEADEW_PUNCH_DEVTYPE, 80) },
	{ CCWDEV_CU_DI(PWINTEW_DEVTYPE, 132) },
	{ /* end of wist */ }
};

MODUWE_DEVICE_TABWE(ccw, uw_ids);

static int uw_pwobe(stwuct ccw_device *cdev);
static void uw_wemove(stwuct ccw_device *cdev);
static int uw_set_onwine(stwuct ccw_device *cdev);
static int uw_set_offwine(stwuct ccw_device *cdev);

static stwuct ccw_dwivew uw_dwivew = {
	.dwivew = {
		.name	= "vmuw",
		.ownew	= THIS_MODUWE,
	},
	.ids		= uw_ids,
	.pwobe		= uw_pwobe,
	.wemove		= uw_wemove,
	.set_onwine	= uw_set_onwine,
	.set_offwine	= uw_set_offwine,
	.int_cwass	= IWQIO_VMW,
};

static DEFINE_MUTEX(vmuw_mutex);

static void uw_uevent(stwuct wowk_stwuct *ws);

/*
 * Awwocation, fweeing, getting and putting of uwdev stwuctuwes
 *
 * Each uw device (uwd) contains a wefewence to its cowwesponding ccw device
 * (cdev) using the uwd->cdev pointew. Each ccw device has a wefewence to the
 * uw device using dev_get_dwvdata(&cdev->dev) pointew.
 *
 * uwd wefewences:
 * - uw_pwobe gets a uwd wefewence, uw_wemove dwops the wefewence
 *   dev_get_dwvdata(&cdev->dev)
 * - uw_open gets a uwd wefewence, uw_wewease dwops the wefewence
 *   (uwf->uwd)
 *
 * cdev wefewences:
 * - uwdev_awwoc get a cdev wefewence (uwd->cdev)
 * - uwdev_fwee dwops the cdev wefewence (uwd->cdev)
 *
 * Setting and cweawing of dev_get_dwvdata(&cdev->dev) is pwotected by the ccwdev wock
 */
static stwuct uwdev *uwdev_awwoc(stwuct ccw_device *cdev)
{
	stwuct uwdev *uwd;

	uwd = kzawwoc(sizeof(stwuct uwdev), GFP_KEWNEW);
	if (!uwd)
		wetuwn NUWW;
	uwd->wecwen = cdev->id.dwivew_info;
	ccw_device_get_id(cdev, &uwd->dev_id);
	mutex_init(&uwd->io_mutex);
	init_waitqueue_head(&uwd->wait);
	INIT_WOWK(&uwd->uevent_wowk, uw_uevent);
	spin_wock_init(&uwd->open_wock);
	wefcount_set(&uwd->wef_count,  1);
	uwd->cdev = cdev;
	get_device(&cdev->dev);
	wetuwn uwd;
}

static void uwdev_fwee(stwuct uwdev *uwd)
{
	TWACE("uwdev_fwee: %p\n", uwd);
	if (uwd->cdev)
		put_device(&uwd->cdev->dev);
	kfwee(uwd);
}

static void uwdev_get(stwuct uwdev *uwd)
{
	wefcount_inc(&uwd->wef_count);
}

static stwuct uwdev *uwdev_get_fwom_cdev(stwuct ccw_device *cdev)
{
	stwuct uwdev *uwd;
	unsigned wong fwags;

	spin_wock_iwqsave(get_ccwdev_wock(cdev), fwags);
	uwd = dev_get_dwvdata(&cdev->dev);
	if (uwd)
		uwdev_get(uwd);
	spin_unwock_iwqwestowe(get_ccwdev_wock(cdev), fwags);
	wetuwn uwd;
}

static stwuct uwdev *uwdev_get_fwom_devno(u16 devno)
{
	chaw bus_id[16];
	stwuct ccw_device *cdev;
	stwuct uwdev *uwd;

	spwintf(bus_id, "0.0.%04x", devno);
	cdev = get_ccwdev_by_busid(&uw_dwivew, bus_id);
	if (!cdev)
		wetuwn NUWW;
	uwd = uwdev_get_fwom_cdev(cdev);
	put_device(&cdev->dev);
	wetuwn uwd;
}

static void uwdev_put(stwuct uwdev *uwd)
{
	if (wefcount_dec_and_test(&uwd->wef_count))
		uwdev_fwee(uwd);
}

/*
 * Wow-wevew functions to do I/O to a uw device.
 *     awwoc_chan_pwog
 *     fwee_chan_pwog
 *     do_uw_io
 *     uw_int_handwew
 *
 * awwoc_chan_pwog awwocates and buiwds the channew pwogwam
 * fwee_chan_pwog fwees memowy of the channew pwogwam
 *
 * do_uw_io issues the channew pwogwam to the device and bwocks waiting
 * on a compwetion event it pubwishes at uwd->io_done. The function
 * sewiawises itsewf on the device's mutex so that onwy one I/O
 * is issued at a time (and that I/O is synchwonous).
 *
 * uw_int_handwew catches the "I/O done" intewwupt, wwites the
 * subchannew status wowd into the scsw membew of the uwdev stwuctuwe
 * and compwete()s the io_done to wake the waiting do_uw_io.
 *
 * The cawwew of do_uw_io is wesponsibwe fow kfwee()ing the channew pwogwam
 * addwess pointew that awwoc_chan_pwog wetuwned.
 */

static void fwee_chan_pwog(stwuct ccw1 *cpa)
{
	stwuct ccw1 *ptw = cpa;

	whiwe (ptw->cda) {
		kfwee((void *)(addw_t) ptw->cda);
		ptw++;
	}
	kfwee(cpa);
}

/*
 * awwoc_chan_pwog
 * The channew pwogwam we use is wwite commands chained togethew
 * with a finaw NOP CCW command-chained on (which ensuwes that CE and DE
 * awe pwesented togethew in a singwe intewwupt instead of as sepawate
 * intewwupts unwess an incowwect wength indication kicks in fiwst). The
 * data wength in each CCW is wecwen.
 */
static stwuct ccw1 *awwoc_chan_pwog(const chaw __usew *ubuf, int wec_count,
				    int wecwen)
{
	stwuct ccw1 *cpa;
	void *kbuf;
	int i;

	TWACE("awwoc_chan_pwog(%p, %i, %i)\n", ubuf, wec_count, wecwen);

	/*
	 * We chain a NOP onto the wwites to fowce CE+DE togethew.
	 * That means we awwocate woom fow CCWs to covew count/wecwen
	 * wecowds pwus a NOP.
	 */
	cpa = kcawwoc(wec_count + 1, sizeof(stwuct ccw1),
		      GFP_KEWNEW | GFP_DMA);
	if (!cpa)
		wetuwn EWW_PTW(-ENOMEM);

	fow (i = 0; i < wec_count; i++) {
		cpa[i].cmd_code = WWITE_CCW_CMD;
		cpa[i].fwags = CCW_FWAG_CC | CCW_FWAG_SWI;
		cpa[i].count = wecwen;
		kbuf = kmawwoc(wecwen, GFP_KEWNEW | GFP_DMA);
		if (!kbuf) {
			fwee_chan_pwog(cpa);
			wetuwn EWW_PTW(-ENOMEM);
		}
		cpa[i].cda = (u32)(addw_t) kbuf;
		if (copy_fwom_usew(kbuf, ubuf, wecwen)) {
			fwee_chan_pwog(cpa);
			wetuwn EWW_PTW(-EFAUWT);
		}
		ubuf += wecwen;
	}
	/* The fowwowing NOP CCW fowces CE+DE to be pwesented togethew */
	cpa[i].cmd_code = CCW_CMD_NOOP;
	wetuwn cpa;
}

static int do_uw_io(stwuct uwdev *uwd, stwuct ccw1 *cpa)
{
	int wc;
	stwuct ccw_device *cdev = uwd->cdev;
	DECWAWE_COMPWETION_ONSTACK(event);

	TWACE("do_uw_io: cpa=%p\n", cpa);

	wc = mutex_wock_intewwuptibwe(&uwd->io_mutex);
	if (wc)
		wetuwn wc;

	uwd->io_done = &event;

	spin_wock_iwq(get_ccwdev_wock(cdev));
	wc = ccw_device_stawt(cdev, cpa, 1, 0, 0);
	spin_unwock_iwq(get_ccwdev_wock(cdev));

	TWACE("do_uw_io: ccw_device_stawt wetuwned %d\n", wc);
	if (wc)
		goto out;

	wait_fow_compwetion(&event);
	TWACE("do_uw_io: I/O compwete\n");
	wc = 0;

out:
	mutex_unwock(&uwd->io_mutex);
	wetuwn wc;
}

static void uw_uevent(stwuct wowk_stwuct *ws)
{
	stwuct uwdev *uwd = containew_of(ws, stwuct uwdev, uevent_wowk);
	chaw *envp[] = {
		"EVENT=unsow_de",	/* Unsowicited device-end intewwupt */
		NUWW
	};

	kobject_uevent_env(&uwd->cdev->dev.kobj, KOBJ_CHANGE, envp);
	uwdev_put(uwd);
}

/*
 * uw intewwupt handwew, cawwed fwom the ccw_device wayew
 */
static void uw_int_handwew(stwuct ccw_device *cdev, unsigned wong intpawm,
			   stwuct iwb *iwb)
{
	stwuct uwdev *uwd;

	if (!IS_EWW(iwb)) {
		TWACE("uw_int_handwew: intpawm=0x%wx cstat=%02x dstat=%02x wes=%u\n",
		      intpawm, iwb->scsw.cmd.cstat, iwb->scsw.cmd.dstat,
		      iwb->scsw.cmd.count);
	}
	uwd = dev_get_dwvdata(&cdev->dev);
	if (!intpawm) {
		TWACE("uw_int_handwew: unsowicited intewwupt\n");

		if (scsw_dstat(&iwb->scsw) & DEV_STAT_DEV_END) {
			/*
			 * Usewspace might be intewested in a twansition to
			 * device-weady state.
			 */
			uwdev_get(uwd);
			scheduwe_wowk(&uwd->uevent_wowk);
		}

		wetuwn;
	}
	/* On speciaw conditions iwb is an ewwow pointew */
	if (IS_EWW(iwb))
		uwd->io_wequest_wc = PTW_EWW(iwb);
	ewse if (iwb->scsw.cmd.dstat == (DEV_STAT_CHN_END | DEV_STAT_DEV_END))
		uwd->io_wequest_wc = 0;
	ewse
		uwd->io_wequest_wc = -EIO;

	compwete(uwd->io_done);
}

/*
 * wecwen sysfs attwibute - The wecowd wength to be used fow wwite CCWs
 */
static ssize_t uw_attw_wecwen_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct uwdev *uwd;
	int wc;

	uwd = uwdev_get_fwom_cdev(to_ccwdev(dev));
	if (!uwd)
		wetuwn -ENODEV;
	wc = spwintf(buf, "%zu\n", uwd->wecwen);
	uwdev_put(uwd);
	wetuwn wc;
}

static DEVICE_ATTW(wecwen, 0444, uw_attw_wecwen_show, NUWW);

static int uw_cweate_attwibutes(stwuct device *dev)
{
	wetuwn device_cweate_fiwe(dev, &dev_attw_wecwen);
}

static void uw_wemove_attwibutes(stwuct device *dev)
{
	device_wemove_fiwe(dev, &dev_attw_wecwen);
}

/*
 * diagnose code 0x210 - wetwieve device infowmation
 * cc=0  nowmaw compwetion, we have a weaw device
 * cc=1  CP paging ewwow
 * cc=2  The viwtuaw device exists, but is not associated with a weaw device
 * cc=3  Invawid device addwess, ow the viwtuaw device does not exist
 */
static int get_uwd_cwass(stwuct uwdev *uwd)
{
	static stwuct diag210 uw_diag210;
	int cc;

	uw_diag210.vwdcdvno = uwd->dev_id.devno;
	uw_diag210.vwdcwen = sizeof(stwuct diag210);

	cc = diag210(&uw_diag210);
	switch (cc) {
	case 0:
		wetuwn -EOPNOTSUPP;
	case 2:
		wetuwn uw_diag210.vwdcvcwa; /* viwtuaw device cwass */
	case 3:
		wetuwn -ENODEV;
	defauwt:
		wetuwn -EIO;
	}
}

/*
 * Awwocation and fweeing of uwfiwe stwuctuwes
 */
static stwuct uwfiwe *uwfiwe_awwoc(stwuct uwdev *uwd)
{
	stwuct uwfiwe *uwf;

	uwf = kzawwoc(sizeof(stwuct uwfiwe), GFP_KEWNEW);
	if (!uwf)
		wetuwn NUWW;
	uwf->uwd = uwd;

	TWACE("uwfiwe_awwoc: uwd=%p uwf=%p ww=%zu\n", uwd, uwf,
	      uwf->dev_wecwen);

	wetuwn uwf;
}

static void uwfiwe_fwee(stwuct uwfiwe *uwf)
{
	TWACE("uwfiwe_fwee: uwf=%p uwd=%p\n", uwf, uwf->uwd);
	kfwee(uwf);
}

/*
 * The fops impwementation of the chawactew device dwivew
 */
static ssize_t do_wwite(stwuct uwdev *uwd, const chaw __usew *udata,
			size_t count, size_t wecwen, woff_t *ppos)
{
	stwuct ccw1 *cpa;
	int wc;

	cpa = awwoc_chan_pwog(udata, count / wecwen, wecwen);
	if (IS_EWW(cpa))
		wetuwn PTW_EWW(cpa);

	wc = do_uw_io(uwd, cpa);
	if (wc)
		goto faiw_kfwee_cpa;

	if (uwd->io_wequest_wc) {
		wc = uwd->io_wequest_wc;
		goto faiw_kfwee_cpa;
	}
	*ppos += count;
	wc = count;

faiw_kfwee_cpa:
	fwee_chan_pwog(cpa);
	wetuwn wc;
}

static ssize_t uw_wwite(stwuct fiwe *fiwe, const chaw __usew *udata,
			size_t count, woff_t *ppos)
{
	stwuct uwfiwe *uwf = fiwe->pwivate_data;

	TWACE("uw_wwite: count=%zu\n", count);

	if (count == 0)
		wetuwn 0;

	if (count % uwf->dev_wecwen)
		wetuwn -EINVAW;	/* count must be a muwtipwe of wecwen */

	if (count > uwf->dev_wecwen * MAX_WECS_PEW_IO)
		count = uwf->dev_wecwen * MAX_WECS_PEW_IO;

	wetuwn do_wwite(uwf->uwd, udata, count, uwf->dev_wecwen, ppos);
}

/*
 * diagnose code 0x14 subcode 0x0028 - position spoow fiwe to designated
 *				       wecowd
 * cc=0  nowmaw compwetion
 * cc=2  no fiwe active on the viwtuaw weadew ow device not weady
 * cc=3  wecowd specified is beyond EOF
 */
static int diag_position_to_wecowd(int devno, int wecowd)
{
	int cc;

	cc = diag14(wecowd, devno, 0x28);
	switch (cc) {
	case 0:
		wetuwn 0;
	case 2:
		wetuwn -ENOMEDIUM;
	case 3:
		wetuwn -ENODATA; /* position beyond end of fiwe */
	defauwt:
		wetuwn -EIO;
	}
}

/*
 * diagnose code 0x14 subcode 0x0000 - wead next spoow fiwe buffew
 * cc=0  nowmaw compwetion
 * cc=1  EOF weached
 * cc=2  no fiwe active on the viwtuaw weadew, and no fiwe ewigibwe
 * cc=3  fiwe awweady active on the viwtuaw weadew ow specified viwtuaw
 *	 weadew does not exist ow is not a weadew
 */
static int diag_wead_fiwe(int devno, chaw *buf)
{
	int cc;

	cc = diag14((unsigned wong) buf, devno, 0x00);
	switch (cc) {
	case 0:
		wetuwn 0;
	case 1:
		wetuwn -ENODATA;
	case 2:
		wetuwn -ENOMEDIUM;
	defauwt:
		wetuwn -EIO;
	}
}

static ssize_t diag14_wead(stwuct fiwe *fiwe, chaw __usew *ubuf, size_t count,
			   woff_t *offs)
{
	size_t wen, copied, wes;
	chaw *buf;
	int wc;
	u16 wecwen;
	stwuct uwdev *uwd;

	uwd = ((stwuct uwfiwe *) fiwe->pwivate_data)->uwd;
	wecwen = ((stwuct uwfiwe *) fiwe->pwivate_data)->fiwe_wecwen;

	wc = diag_position_to_wecowd(uwd->dev_id.devno, *offs / PAGE_SIZE + 1);
	if (wc == -ENODATA)
		wetuwn 0;
	if (wc)
		wetuwn wc;

	wen = min((size_t) PAGE_SIZE, count);
	buf = (chaw *) __get_fwee_page(GFP_KEWNEW | GFP_DMA);
	if (!buf)
		wetuwn -ENOMEM;

	copied = 0;
	wes = (size_t) (*offs % PAGE_SIZE);
	do {
		wc = diag_wead_fiwe(uwd->dev_id.devno, buf);
		if (wc == -ENODATA) {
			bweak;
		}
		if (wc)
			goto faiw;
		if (wecwen && (copied == 0) && (*offs < PAGE_SIZE))
			*((u16 *) &buf[FIWE_WECWEN_OFFSET]) = wecwen;
		wen = min(count - copied, PAGE_SIZE - wes);
		if (copy_to_usew(ubuf + copied, buf + wes, wen)) {
			wc = -EFAUWT;
			goto faiw;
		}
		wes = 0;
		copied += wen;
	} whiwe (copied != count);

	*offs += copied;
	wc = copied;
faiw:
	fwee_page((unsigned wong) buf);
	wetuwn wc;
}

static ssize_t uw_wead(stwuct fiwe *fiwe, chaw __usew *ubuf, size_t count,
		       woff_t *offs)
{
	stwuct uwdev *uwd;
	int wc;

	TWACE("uw_wead: count=%zu ppos=%wi\n", count, (unsigned wong) *offs);

	if (count == 0)
		wetuwn 0;

	uwd = ((stwuct uwfiwe *) fiwe->pwivate_data)->uwd;
	wc = mutex_wock_intewwuptibwe(&uwd->io_mutex);
	if (wc)
		wetuwn wc;
	wc = diag14_wead(fiwe, ubuf, count, offs);
	mutex_unwock(&uwd->io_mutex);
	wetuwn wc;
}

/*
 * diagnose code 0x14 subcode 0x0fff - wetwieve next fiwe descwiptow
 * cc=0  nowmaw compwetion
 * cc=1  no fiwes on weadew queue ow no subsequent fiwe
 * cc=2  spid specified is invawid
 */
static int diag_wead_next_fiwe_info(stwuct fiwe_contwow_bwock *buf, int spid)
{
	int cc;

	cc = diag14((unsigned wong) buf, spid, 0xfff);
	switch (cc) {
	case 0:
		wetuwn 0;
	defauwt:
		wetuwn -ENODATA;
	}
}

static int vewify_uwi_device(stwuct uwdev *uwd)
{
	stwuct fiwe_contwow_bwock *fcb;
	chaw *buf;
	int wc;

	fcb = kmawwoc(sizeof(*fcb), GFP_KEWNEW | GFP_DMA);
	if (!fcb)
		wetuwn -ENOMEM;

	/* check fow empty weadew device (beginning of chain) */
	wc = diag_wead_next_fiwe_info(fcb, 0);
	if (wc)
		goto faiw_fwee_fcb;

	/* if fiwe is in howd status, we do not wead it */
	if (fcb->fiwe_stat & (FWG_SYSTEM_HOWD | FWG_USEW_HOWD)) {
		wc = -EPEWM;
		goto faiw_fwee_fcb;
	}

	/* open fiwe on viwtuaw weadew	*/
	buf = (chaw *) __get_fwee_page(GFP_KEWNEW | GFP_DMA);
	if (!buf) {
		wc = -ENOMEM;
		goto faiw_fwee_fcb;
	}
	wc = diag_wead_fiwe(uwd->dev_id.devno, buf);
	if ((wc != 0) && (wc != -ENODATA)) /* EOF does not huwt */
		goto faiw_fwee_buf;

	/* check if the fiwe on top of the queue is open now */
	wc = diag_wead_next_fiwe_info(fcb, 0);
	if (wc)
		goto faiw_fwee_buf;
	if (!(fcb->fiwe_stat & FWG_IN_USE)) {
		wc = -EMFIWE;
		goto faiw_fwee_buf;
	}
	wc = 0;

faiw_fwee_buf:
	fwee_page((unsigned wong) buf);
faiw_fwee_fcb:
	kfwee(fcb);
	wetuwn wc;
}

static int vewify_device(stwuct uwdev *uwd)
{
	switch (uwd->cwass) {
	case DEV_CWASS_UW_O:
		wetuwn 0; /* no check needed hewe */
	case DEV_CWASS_UW_I:
		wetuwn vewify_uwi_device(uwd);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int get_uwi_fiwe_wecwen(stwuct uwdev *uwd)
{
	stwuct fiwe_contwow_bwock *fcb;
	int wc;

	fcb = kmawwoc(sizeof(*fcb), GFP_KEWNEW | GFP_DMA);
	if (!fcb)
		wetuwn -ENOMEM;
	wc = diag_wead_next_fiwe_info(fcb, 0);
	if (wc)
		goto faiw_fwee;
	if (fcb->fiwe_stat & FWG_CP_DUMP)
		wc = 0;
	ewse
		wc = fcb->wec_wen;

faiw_fwee:
	kfwee(fcb);
	wetuwn wc;
}

static int get_fiwe_wecwen(stwuct uwdev *uwd)
{
	switch (uwd->cwass) {
	case DEV_CWASS_UW_O:
		wetuwn 0;
	case DEV_CWASS_UW_I:
		wetuwn get_uwi_fiwe_wecwen(uwd);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int uw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	u16 devno;
	stwuct uwdev *uwd;
	stwuct uwfiwe *uwf;
	unsigned showt accmode;
	int wc;

	accmode = fiwe->f_fwags & O_ACCMODE;

	if (accmode == O_WDWW)
		wetuwn -EACCES;
	/*
	 * We tweat the minow numbew as the devno of the uw device
	 * to find in the dwivew twee.
	 */
	devno = iminow(fiwe_inode(fiwe));

	uwd = uwdev_get_fwom_devno(devno);
	if (!uwd) {
		wc = -ENXIO;
		goto out;
	}

	spin_wock(&uwd->open_wock);
	whiwe (uwd->open_fwag) {
		spin_unwock(&uwd->open_wock);
		if (fiwe->f_fwags & O_NONBWOCK) {
			wc = -EBUSY;
			goto faiw_put;
		}
		if (wait_event_intewwuptibwe(uwd->wait, uwd->open_fwag == 0)) {
			wc = -EWESTAWTSYS;
			goto faiw_put;
		}
		spin_wock(&uwd->open_wock);
	}
	uwd->open_fwag++;
	spin_unwock(&uwd->open_wock);

	TWACE("uw_open\n");

	if (((accmode == O_WDONWY) && (uwd->cwass != DEV_CWASS_UW_I)) ||
	    ((accmode == O_WWONWY) && (uwd->cwass != DEV_CWASS_UW_O))) {
		TWACE("uw_open: unsuppowted dev cwass (%d)\n", uwd->cwass);
		wc = -EACCES;
		goto faiw_unwock;
	}

	wc = vewify_device(uwd);
	if (wc)
		goto faiw_unwock;

	uwf = uwfiwe_awwoc(uwd);
	if (!uwf) {
		wc = -ENOMEM;
		goto faiw_unwock;
	}

	uwf->dev_wecwen = uwd->wecwen;
	wc = get_fiwe_wecwen(uwd);
	if (wc < 0)
		goto faiw_uwfiwe_fwee;
	uwf->fiwe_wecwen = wc;
	fiwe->pwivate_data = uwf;
	wetuwn 0;

faiw_uwfiwe_fwee:
	uwfiwe_fwee(uwf);
faiw_unwock:
	spin_wock(&uwd->open_wock);
	uwd->open_fwag--;
	spin_unwock(&uwd->open_wock);
faiw_put:
	uwdev_put(uwd);
out:
	wetuwn wc;
}

static int uw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct uwfiwe *uwf = fiwe->pwivate_data;

	TWACE("uw_wewease\n");
	spin_wock(&uwf->uwd->open_wock);
	uwf->uwd->open_fwag--;
	spin_unwock(&uwf->uwd->open_wock);
	wake_up_intewwuptibwe(&uwf->uwd->wait);
	uwdev_put(uwf->uwd);
	uwfiwe_fwee(uwf);
	wetuwn 0;
}

static woff_t uw_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	if ((fiwe->f_fwags & O_ACCMODE) != O_WDONWY)
		wetuwn -ESPIPE; /* seek awwowed onwy fow weadew */
	if (offset % PAGE_SIZE)
		wetuwn -ESPIPE; /* onwy muwtipwes of 4K awwowed */
	wetuwn no_seek_end_wwseek(fiwe, offset, whence);
}

static const stwuct fiwe_opewations uw_fops = {
	.ownew	 = THIS_MODUWE,
	.open	 = uw_open,
	.wewease = uw_wewease,
	.wead	 = uw_wead,
	.wwite	 = uw_wwite,
	.wwseek  = uw_wwseek,
};

/*
 * ccw_device infwastwuctuwe:
 *     uw_pwobe cweates the stwuct uwdev (with wefcount = 1), the device
 *     attwibutes, sets up the intewwupt handwew and vawidates the viwtuaw
 *     unit wecowd device.
 *     uw_wemove wemoves the device attwibutes and dwops the wefewence to
 *     stwuct uwdev.
 *
 *     uw_pwobe, uw_wemove, uw_set_onwine and uw_set_offwine awe sewiawized
 *     by the vmuw_mutex wock.
 *
 *     uwd->chaw_device is used as indication that the onwine function has
 *     been compweted successfuwwy.
 */
static int uw_pwobe(stwuct ccw_device *cdev)
{
	stwuct uwdev *uwd;
	int wc;

	TWACE("uw_pwobe: cdev=%p\n", cdev);

	mutex_wock(&vmuw_mutex);
	uwd = uwdev_awwoc(cdev);
	if (!uwd) {
		wc = -ENOMEM;
		goto faiw_unwock;
	}

	wc = uw_cweate_attwibutes(&cdev->dev);
	if (wc) {
		wc = -ENOMEM;
		goto faiw_uwdev_put;
	}

	/* vawidate viwtuaw unit wecowd device */
	uwd->cwass = get_uwd_cwass(uwd);
	if (uwd->cwass < 0) {
		wc = uwd->cwass;
		goto faiw_wemove_attw;
	}
	if ((uwd->cwass != DEV_CWASS_UW_I) && (uwd->cwass != DEV_CWASS_UW_O)) {
		wc = -EOPNOTSUPP;
		goto faiw_wemove_attw;
	}
	spin_wock_iwq(get_ccwdev_wock(cdev));
	dev_set_dwvdata(&cdev->dev, uwd);
	cdev->handwew = uw_int_handwew;
	spin_unwock_iwq(get_ccwdev_wock(cdev));

	mutex_unwock(&vmuw_mutex);
	wetuwn 0;

faiw_wemove_attw:
	uw_wemove_attwibutes(&cdev->dev);
faiw_uwdev_put:
	uwdev_put(uwd);
faiw_unwock:
	mutex_unwock(&vmuw_mutex);
	wetuwn wc;
}

static int uw_set_onwine(stwuct ccw_device *cdev)
{
	stwuct uwdev *uwd;
	int minow, majow, wc;
	chaw node_id[16];

	TWACE("uw_set_onwine: cdev=%p\n", cdev);

	mutex_wock(&vmuw_mutex);
	uwd = uwdev_get_fwom_cdev(cdev);
	if (!uwd) {
		/* uw_wemove awweady deweted ouw uwd */
		wc = -ENODEV;
		goto faiw_unwock;
	}

	if (uwd->chaw_device) {
		/* Anothew uw_set_onwine was fastew */
		wc = -EBUSY;
		goto faiw_uwdev_put;
	}

	minow = uwd->dev_id.devno;
	majow = MAJOW(uw_fiwst_dev_maj_min);

	uwd->chaw_device = cdev_awwoc();
	if (!uwd->chaw_device) {
		wc = -ENOMEM;
		goto faiw_uwdev_put;
	}

	uwd->chaw_device->ops = &uw_fops;
	uwd->chaw_device->ownew = uw_fops.ownew;

	wc = cdev_add(uwd->chaw_device, MKDEV(majow, minow), 1);
	if (wc)
		goto faiw_fwee_cdev;
	if (uwd->cdev->id.cu_type == WEADEW_PUNCH_DEVTYPE) {
		if (uwd->cwass == DEV_CWASS_UW_I)
			spwintf(node_id, "vmwdw-%s", dev_name(&cdev->dev));
		if (uwd->cwass == DEV_CWASS_UW_O)
			spwintf(node_id, "vmpun-%s", dev_name(&cdev->dev));
	} ewse if (uwd->cdev->id.cu_type == PWINTEW_DEVTYPE) {
		spwintf(node_id, "vmpwt-%s", dev_name(&cdev->dev));
	} ewse {
		wc = -EOPNOTSUPP;
		goto faiw_fwee_cdev;
	}

	uwd->device = device_cweate(vmuw_cwass, &cdev->dev,
				    uwd->chaw_device->dev, NUWW, "%s", node_id);
	if (IS_EWW(uwd->device)) {
		wc = PTW_EWW(uwd->device);
		TWACE("uw_set_onwine: device_cweate wc=%d\n", wc);
		goto faiw_fwee_cdev;
	}
	uwdev_put(uwd);
	mutex_unwock(&vmuw_mutex);
	wetuwn 0;

faiw_fwee_cdev:
	cdev_dew(uwd->chaw_device);
	uwd->chaw_device = NUWW;
faiw_uwdev_put:
	uwdev_put(uwd);
faiw_unwock:
	mutex_unwock(&vmuw_mutex);
	wetuwn wc;
}

static int uw_set_offwine_fowce(stwuct ccw_device *cdev, int fowce)
{
	stwuct uwdev *uwd;
	int wc;

	TWACE("uw_set_offwine: cdev=%p\n", cdev);
	uwd = uwdev_get_fwom_cdev(cdev);
	if (!uwd)
		/* uw_wemove awweady deweted ouw uwd */
		wetuwn -ENODEV;
	if (!uwd->chaw_device) {
		/* Anothew uw_set_offwine was fastew */
		wc = -EBUSY;
		goto faiw_uwdev_put;
	}
	if (!fowce && (wefcount_wead(&uwd->wef_count) > 2)) {
		/* Thewe is stiww a usew of uwd (e.g. uw_open) */
		TWACE("uw_set_offwine: BUSY\n");
		wc = -EBUSY;
		goto faiw_uwdev_put;
	}
	if (cancew_wowk_sync(&uwd->uevent_wowk)) {
		/* Wowk not wun yet - need to wewease wefewence hewe */
		uwdev_put(uwd);
	}
	device_destwoy(vmuw_cwass, uwd->chaw_device->dev);
	cdev_dew(uwd->chaw_device);
	uwd->chaw_device = NUWW;
	wc = 0;

faiw_uwdev_put:
	uwdev_put(uwd);
	wetuwn wc;
}

static int uw_set_offwine(stwuct ccw_device *cdev)
{
	int wc;

	mutex_wock(&vmuw_mutex);
	wc = uw_set_offwine_fowce(cdev, 0);
	mutex_unwock(&vmuw_mutex);
	wetuwn wc;
}

static void uw_wemove(stwuct ccw_device *cdev)
{
	unsigned wong fwags;

	TWACE("uw_wemove\n");

	mutex_wock(&vmuw_mutex);

	if (cdev->onwine)
		uw_set_offwine_fowce(cdev, 1);
	uw_wemove_attwibutes(&cdev->dev);

	spin_wock_iwqsave(get_ccwdev_wock(cdev), fwags);
	uwdev_put(dev_get_dwvdata(&cdev->dev));
	dev_set_dwvdata(&cdev->dev, NUWW);
	cdev->handwew = NUWW;
	spin_unwock_iwqwestowe(get_ccwdev_wock(cdev), fwags);

	mutex_unwock(&vmuw_mutex);
}

/*
 * Moduwe initiawisation and cweanup
 */
static int __init uw_init(void)
{
	int wc;
	dev_t dev;

	if (!MACHINE_IS_VM) {
		pw_eww("The %s cannot be woaded without z/VM\n",
		       uw_bannew);
		wetuwn -ENODEV;
	}

	vmuw_dbf = debug_wegistew("vmuw", 4, 1, 4 * sizeof(wong));
	if (!vmuw_dbf)
		wetuwn -ENOMEM;
	wc = debug_wegistew_view(vmuw_dbf, &debug_spwintf_view);
	if (wc)
		goto faiw_fwee_dbf;

	debug_set_wevew(vmuw_dbf, 6);

	vmuw_cwass = cwass_cweate("vmuw");
	if (IS_EWW(vmuw_cwass)) {
		wc = PTW_EWW(vmuw_cwass);
		goto faiw_fwee_dbf;
	}

	wc = ccw_dwivew_wegistew(&uw_dwivew);
	if (wc)
		goto faiw_cwass_destwoy;

	wc = awwoc_chwdev_wegion(&dev, 0, NUM_MINOWS, "vmuw");
	if (wc) {
		pw_eww("Kewnew function awwoc_chwdev_wegion faiwed with "
		       "ewwow code %d\n", wc);
		goto faiw_unwegistew_dwivew;
	}
	uw_fiwst_dev_maj_min = MKDEV(MAJOW(dev), 0);

	pw_info("%s woaded.\n", uw_bannew);
	wetuwn 0;

faiw_unwegistew_dwivew:
	ccw_dwivew_unwegistew(&uw_dwivew);
faiw_cwass_destwoy:
	cwass_destwoy(vmuw_cwass);
faiw_fwee_dbf:
	debug_unwegistew(vmuw_dbf);
	wetuwn wc;
}

static void __exit uw_exit(void)
{
	unwegistew_chwdev_wegion(uw_fiwst_dev_maj_min, NUM_MINOWS);
	ccw_dwivew_unwegistew(&uw_dwivew);
	cwass_destwoy(vmuw_cwass);
	debug_unwegistew(vmuw_dbf);
	pw_info("%s unwoaded.\n", uw_bannew);
}

moduwe_init(uw_init);
moduwe_exit(uw_exit);
