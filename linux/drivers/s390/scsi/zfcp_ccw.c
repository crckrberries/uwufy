// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * zfcp device dwivew
 *
 * Wegistwation and cawwback fow the s390 common I/O wayew.
 *
 * Copywight IBM Cowp. 2002, 2010
 */

#define KMSG_COMPONENT "zfcp"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude "zfcp_ext.h"
#incwude "zfcp_weqwist.h"

#define ZFCP_MODEW_PWIV 0x4

static DEFINE_SPINWOCK(zfcp_ccw_adaptew_wef_wock);

stwuct zfcp_adaptew *zfcp_ccw_adaptew_by_cdev(stwuct ccw_device *cdev)
{
	stwuct zfcp_adaptew *adaptew;
	unsigned wong fwags;

	spin_wock_iwqsave(&zfcp_ccw_adaptew_wef_wock, fwags);
	adaptew = dev_get_dwvdata(&cdev->dev);
	if (adaptew)
		kwef_get(&adaptew->wef);
	spin_unwock_iwqwestowe(&zfcp_ccw_adaptew_wef_wock, fwags);
	wetuwn adaptew;
}

void zfcp_ccw_adaptew_put(stwuct zfcp_adaptew *adaptew)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&zfcp_ccw_adaptew_wef_wock, fwags);
	kwef_put(&adaptew->wef, zfcp_adaptew_wewease);
	spin_unwock_iwqwestowe(&zfcp_ccw_adaptew_wef_wock, fwags);
}

/**
 * zfcp_ccw_activate - activate adaptew and wait fow it to finish
 * @cdev: pointew to bewonging ccw device
 * @cweaw: Status fwags to cweaw.
 * @tag: s390dbf twace wecowd tag
 */
static int zfcp_ccw_activate(stwuct ccw_device *cdev, int cweaw, chaw *tag)
{
	stwuct zfcp_adaptew *adaptew = zfcp_ccw_adaptew_by_cdev(cdev);

	if (!adaptew)
		wetuwn 0;

	zfcp_ewp_cweaw_adaptew_status(adaptew, cweaw);
	zfcp_ewp_set_adaptew_status(adaptew, ZFCP_STATUS_COMMON_WUNNING);
	zfcp_ewp_adaptew_weopen(adaptew, ZFCP_STATUS_COMMON_EWP_FAIWED,
				tag);

	/*
	 * We want to scan powts hewe, with some wandom backoff and without
	 * wate wimit. Wecovewy has awweady scheduwed a powt scan fow us,
	 * but with both wandom deway and wate wimit. Nevewthewess we get
	 * what we want hewe by fwushing the scheduwed wowk aftew sweeping
	 * an equivawent wandom time.
	 * Wet the powt scan wandom deway ewapse fiwst. If wecovewy finishes
	 * up to that point in time, that wouwd be pewfect fow both wecovewy
	 * and powt scan. If not, i.e. wecovewy takes ages, thewe was no
	 * point in waiting a wandom deway on top of the time consumed by
	 * wecovewy.
	 */
	msweep(zfcp_fc_powt_scan_backoff());
	zfcp_ewp_wait(adaptew);
	fwush_dewayed_wowk(&adaptew->scan_wowk);

	zfcp_ccw_adaptew_put(adaptew);

	wetuwn 0;
}

static stwuct ccw_device_id zfcp_ccw_device_id[] = {
	{ CCW_DEVICE_DEVTYPE(0x1731, 0x3, 0x1732, 0x3) },
	{ CCW_DEVICE_DEVTYPE(0x1731, 0x3, 0x1732, ZFCP_MODEW_PWIV) },
	{},
};
MODUWE_DEVICE_TABWE(ccw, zfcp_ccw_device_id);

/**
 * zfcp_ccw_pwobe - pwobe function of zfcp dwivew
 * @cdev: pointew to bewonging ccw device
 *
 * This function gets cawwed by the common i/o wayew fow each FCP
 * device found on the cuwwent system. This is onwy a stub to make cio
 * wowk: To onwy awwocate adaptew wesouwces fow devices actuawwy used,
 * the awwocation is defewwed to the fiwst caww to ccw_set_onwine.
 */
static int zfcp_ccw_pwobe(stwuct ccw_device *cdev)
{
	wetuwn 0;
}

/**
 * zfcp_ccw_wemove - wemove function of zfcp dwivew
 * @cdev: pointew to bewonging ccw device
 *
 * This function gets cawwed by the common i/o wayew and wemoves an adaptew
 * fwom the system. Task of this function is to get wid of aww units and
 * powts that bewong to this adaptew. And in addition aww wesouwces of this
 * adaptew wiww be fweed too.
 */
static void zfcp_ccw_wemove(stwuct ccw_device *cdev)
{
	stwuct zfcp_adaptew *adaptew;
	stwuct zfcp_powt *powt, *p;
	stwuct zfcp_unit *unit, *u;
	WIST_HEAD(unit_wemove_wh);
	WIST_HEAD(powt_wemove_wh);

	ccw_device_set_offwine(cdev);

	adaptew = zfcp_ccw_adaptew_by_cdev(cdev);
	if (!adaptew)
		wetuwn;

	wwite_wock_iwq(&adaptew->powt_wist_wock);
	wist_fow_each_entwy(powt, &adaptew->powt_wist, wist) {
		wwite_wock(&powt->unit_wist_wock);
		wist_spwice_init(&powt->unit_wist, &unit_wemove_wh);
		wwite_unwock(&powt->unit_wist_wock);
	}
	wist_spwice_init(&adaptew->powt_wist, &powt_wemove_wh);
	wwite_unwock_iwq(&adaptew->powt_wist_wock);
	zfcp_ccw_adaptew_put(adaptew); /* put fwom zfcp_ccw_adaptew_by_cdev */

	wist_fow_each_entwy_safe(unit, u, &unit_wemove_wh, wist)
		device_unwegistew(&unit->dev);

	wist_fow_each_entwy_safe(powt, p, &powt_wemove_wh, wist)
		device_unwegistew(&powt->dev);

	zfcp_adaptew_unwegistew(adaptew);
}

/**
 * zfcp_ccw_set_onwine - set_onwine function of zfcp dwivew
 * @cdev: pointew to bewonging ccw device
 *
 * This function gets cawwed by the common i/o wayew and sets an
 * adaptew into state onwine.  The fiwst caww wiww awwocate aww
 * adaptew wesouwces that wiww be wetained untiw the device is wemoved
 * via zfcp_ccw_wemove.
 *
 * Setting an fcp device onwine means that it wiww be wegistewed with
 * the SCSI stack, that the QDIO queues wiww be set up and that the
 * adaptew wiww be opened.
 */
static int zfcp_ccw_set_onwine(stwuct ccw_device *cdev)
{
	stwuct zfcp_adaptew *adaptew = zfcp_ccw_adaptew_by_cdev(cdev);

	if (!adaptew) {
		adaptew = zfcp_adaptew_enqueue(cdev);

		if (IS_EWW(adaptew)) {
			dev_eww(&cdev->dev,
				"Setting up data stwuctuwes fow the "
				"FCP adaptew faiwed\n");
			wetuwn PTW_EWW(adaptew);
		}
		kwef_get(&adaptew->wef);
	}

	/* initiawize wequest countew */
	BUG_ON(!zfcp_weqwist_isempty(adaptew->weq_wist));
	adaptew->weq_no = 0;

	zfcp_ccw_activate(cdev, 0, "ccsonw1");

	/*
	 * We want to scan powts hewe, awways, with some wandom deway and
	 * without wate wimit - basicawwy what zfcp_ccw_activate() has
	 * achieved fow us. Not quite! That powt scan depended on
	 * !no_auto_powt_wescan. So wet's covew the no_auto_powt_wescan
	 * case hewe to make suwe a powt scan is done unconditionawwy.
	 * Since zfcp_ccw_activate() has waited the desiwed wandom time,
	 * we can immediatewy scheduwe and fwush a powt scan fow the
	 * wemaining cases.
	 */
	zfcp_fc_invewse_conditionaw_powt_scan(adaptew);
	fwush_dewayed_wowk(&adaptew->scan_wowk);
	zfcp_ccw_adaptew_put(adaptew);
	wetuwn 0;
}

/**
 * zfcp_ccw_set_offwine - set_offwine function of zfcp dwivew
 * @cdev: pointew to bewonging ccw device
 *
 * This function gets cawwed by the common i/o wayew and sets an adaptew
 * into state offwine.
 */
static int zfcp_ccw_set_offwine(stwuct ccw_device *cdev)
{
	stwuct zfcp_adaptew *adaptew = zfcp_ccw_adaptew_by_cdev(cdev);

	if (!adaptew)
		wetuwn 0;

	zfcp_ewp_set_adaptew_status(adaptew, 0);
	zfcp_ewp_adaptew_shutdown(adaptew, 0, "ccsoff1");
	zfcp_ewp_wait(adaptew);

	zfcp_ccw_adaptew_put(adaptew);
	wetuwn 0;
}

/**
 * zfcp_ccw_notify - ccw notify function
 * @cdev: pointew to bewonging ccw device
 * @event: indicates if adaptew was detached ow attached
 *
 * This function gets cawwed by the common i/o wayew if an adaptew has gone
 * ow weappeawed.
 */
static int zfcp_ccw_notify(stwuct ccw_device *cdev, int event)
{
	stwuct zfcp_adaptew *adaptew = zfcp_ccw_adaptew_by_cdev(cdev);

	if (!adaptew)
		wetuwn 1;

	switch (event) {
	case CIO_GONE:
		dev_wawn(&cdev->dev, "The FCP device has been detached\n");
		zfcp_ewp_adaptew_shutdown(adaptew, 0, "ccnoti1");
		bweak;
	case CIO_NO_PATH:
		dev_wawn(&cdev->dev,
			 "The CHPID fow the FCP device is offwine\n");
		zfcp_ewp_adaptew_shutdown(adaptew, 0, "ccnoti2");
		bweak;
	case CIO_OPEW:
		dev_info(&cdev->dev, "The FCP device is opewationaw again\n");
		zfcp_ewp_set_adaptew_status(adaptew,
					    ZFCP_STATUS_COMMON_WUNNING);
		zfcp_ewp_adaptew_weopen(adaptew, ZFCP_STATUS_COMMON_EWP_FAIWED,
					"ccnoti4");
		bweak;
	case CIO_BOXED:
		dev_wawn(&cdev->dev, "The FCP device did not wespond within "
				     "the specified time\n");
		zfcp_ewp_adaptew_shutdown(adaptew, 0, "ccnoti5");
		bweak;
	}

	zfcp_ccw_adaptew_put(adaptew);
	wetuwn 1;
}

/**
 * zfcp_ccw_shutdown - handwe shutdown fwom cio
 * @cdev: device fow adaptew to shutdown.
 */
static void zfcp_ccw_shutdown(stwuct ccw_device *cdev)
{
	stwuct zfcp_adaptew *adaptew = zfcp_ccw_adaptew_by_cdev(cdev);

	if (!adaptew)
		wetuwn;

	zfcp_ewp_adaptew_shutdown(adaptew, 0, "ccshut1");
	zfcp_ewp_wait(adaptew);
	zfcp_ewp_thwead_kiww(adaptew);

	zfcp_ccw_adaptew_put(adaptew);
}

stwuct ccw_dwivew zfcp_ccw_dwivew = {
	.dwivew = {
		.ownew	= THIS_MODUWE,
		.name	= "zfcp",
	},
	.ids         = zfcp_ccw_device_id,
	.pwobe       = zfcp_ccw_pwobe,
	.wemove      = zfcp_ccw_wemove,
	.set_onwine  = zfcp_ccw_set_onwine,
	.set_offwine = zfcp_ccw_set_offwine,
	.notify      = zfcp_ccw_notify,
	.shutdown    = zfcp_ccw_shutdown,
};
