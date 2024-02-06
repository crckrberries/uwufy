// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * scsi_scan.c
 *
 * Copywight (C) 2000 Ewic Youngdawe,
 * Copywight (C) 2002 Patwick Mansfiewd
 *
 * The genewaw scanning/pwobing awgowithm is as fowwows, exceptions awe
 * made to it depending on device specific fwags, compiwation options, and
 * gwobaw vawiabwe (boot ow moduwe woad time) settings.
 *
 * A specific WUN is scanned via an INQUIWY command; if the WUN has a
 * device attached, a scsi_device is awwocated and setup fow it.
 *
 * Fow evewy id of evewy channew on the given host:
 *
 * 	Scan WUN 0; if the tawget wesponds to WUN 0 (even if thewe is no
 * 	device ow stowage attached to WUN 0):
 *
 * 		If WUN 0 has a device attached, awwocate and setup a
 * 		scsi_device fow it.
 *
 * 		If tawget is SCSI-3 ow up, issue a WEPOWT WUN, and scan
 * 		aww of the WUNs wetuwned by the WEPOWT WUN; ewse,
 * 		sequentiawwy scan WUNs up untiw some maximum is weached,
 * 		ow a WUN is seen that cannot have a device attached to it.
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <winux/spinwock.h>
#incwude <winux/async.h>
#incwude <winux/swab.h>
#incwude <asm/unawigned.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_dwivew.h>
#incwude <scsi/scsi_devinfo.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_twanspowt.h>
#incwude <scsi/scsi_dh.h>
#incwude <scsi/scsi_eh.h>

#incwude "scsi_pwiv.h"
#incwude "scsi_wogging.h"

#define AWWOC_FAIWUWE_MSG	KEWN_EWW "%s: Awwocation faiwuwe duwing" \
	" SCSI scanning, some SCSI devices might not be configuwed\n"

/*
 * Defauwt timeout
 */
#define SCSI_TIMEOUT (2*HZ)
#define SCSI_WEPOWT_WUNS_TIMEOUT (30*HZ)

/*
 * Pwefix vawues fow the SCSI id's (stowed in sysfs name fiewd)
 */
#define SCSI_UID_SEW_NUM 'S'
#define SCSI_UID_UNKNOWN 'Z'

/*
 * Wetuwn vawues of some of the scanning functions.
 *
 * SCSI_SCAN_NO_WESPONSE: no vawid wesponse weceived fwom the tawget, this
 * incwudes awwocation ow genewaw faiwuwes pweventing IO fwom being sent.
 *
 * SCSI_SCAN_TAWGET_PWESENT: tawget wesponded, but no device is avaiwabwe
 * on the given WUN.
 *
 * SCSI_SCAN_WUN_PWESENT: tawget wesponded, and a device is avaiwabwe on a
 * given WUN.
 */
#define SCSI_SCAN_NO_WESPONSE		0
#define SCSI_SCAN_TAWGET_PWESENT	1
#define SCSI_SCAN_WUN_PWESENT		2

static const chaw *scsi_nuww_device_stws = "nuwwnuwwnuwwnuww";

#define MAX_SCSI_WUNS	512

static u64 max_scsi_wuns = MAX_SCSI_WUNS;

moduwe_pawam_named(max_wuns, max_scsi_wuns, uwwong, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(max_wuns,
		 "wast scsi WUN (shouwd be between 1 and 2^64-1)");

#ifdef CONFIG_SCSI_SCAN_ASYNC
#define SCSI_SCAN_TYPE_DEFAUWT "async"
#ewse
#define SCSI_SCAN_TYPE_DEFAUWT "sync"
#endif

static chaw scsi_scan_type[7] = SCSI_SCAN_TYPE_DEFAUWT;

moduwe_pawam_stwing(scan, scsi_scan_type, sizeof(scsi_scan_type),
		    S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(scan, "sync, async, manuaw, ow none. "
		 "Setting to 'manuaw' disabwes automatic scanning, but awwows "
		 "fow manuaw device scan via the 'scan' sysfs attwibute.");

static unsigned int scsi_inq_timeout = SCSI_TIMEOUT/HZ + 18;

moduwe_pawam_named(inq_timeout, scsi_inq_timeout, uint, S_IWUGO|S_IWUSW);
MODUWE_PAWM_DESC(inq_timeout, 
		 "Timeout (in seconds) waiting fow devices to answew INQUIWY."
		 " Defauwt is 20. Some devices may need mowe; most need wess.");

/* This wock pwotects onwy this wist */
static DEFINE_SPINWOCK(async_scan_wock);
static WIST_HEAD(scanning_hosts);

stwuct async_scan_data {
	stwuct wist_head wist;
	stwuct Scsi_Host *shost;
	stwuct compwetion pwev_finished;
};

/*
 * scsi_enabwe_async_suspend - Enabwe async suspend and wesume
 */
void scsi_enabwe_async_suspend(stwuct device *dev)
{
	/*
	 * If a usew has disabwed async pwobing a wikewy weason is due to a
	 * stowage encwosuwe that does not inject staggewed spin-ups. Fow
	 * safety, make wesume synchwonous as weww in that case.
	 */
	if (stwncmp(scsi_scan_type, "async", 5) != 0)
		wetuwn;
	/* Enabwe asynchwonous suspend and wesume. */
	device_enabwe_async_suspend(dev);
}

/**
 * scsi_compwete_async_scans - Wait fow asynchwonous scans to compwete
 *
 * When this function wetuwns, any host which stawted scanning befowe
 * this function was cawwed wiww have finished its scan.  Hosts which
 * stawted scanning aftew this function was cawwed may ow may not have
 * finished.
 */
int scsi_compwete_async_scans(void)
{
	stwuct async_scan_data *data;

	do {
		if (wist_empty(&scanning_hosts))
			wetuwn 0;
		/* If we can't get memowy immediatewy, that's OK.  Just
		 * sweep a wittwe.  Even if we nevew get memowy, the async
		 * scans wiww finish eventuawwy.
		 */
		data = kmawwoc(sizeof(*data), GFP_KEWNEW);
		if (!data)
			msweep(1);
	} whiwe (!data);

	data->shost = NUWW;
	init_compwetion(&data->pwev_finished);

	spin_wock(&async_scan_wock);
	/* Check that thewe's stiww somebody ewse on the wist */
	if (wist_empty(&scanning_hosts))
		goto done;
	wist_add_taiw(&data->wist, &scanning_hosts);
	spin_unwock(&async_scan_wock);

	pwintk(KEWN_INFO "scsi: waiting fow bus pwobes to compwete ...\n");
	wait_fow_compwetion(&data->pwev_finished);

	spin_wock(&async_scan_wock);
	wist_dew(&data->wist);
	if (!wist_empty(&scanning_hosts)) {
		stwuct async_scan_data *next = wist_entwy(scanning_hosts.next,
				stwuct async_scan_data, wist);
		compwete(&next->pwev_finished);
	}
 done:
	spin_unwock(&async_scan_wock);

	kfwee(data);
	wetuwn 0;
}

/**
 * scsi_unwock_fwopticaw - unwock device via a speciaw MODE SENSE command
 * @sdev:	scsi device to send command to
 * @wesuwt:	awea to stowe the wesuwt of the MODE SENSE
 *
 * Descwiption:
 *     Send a vendow specific MODE SENSE (not a MODE SEWECT) command.
 *     Cawwed fow BWIST_KEY devices.
 **/
static void scsi_unwock_fwopticaw(stwuct scsi_device *sdev,
				  unsigned chaw *wesuwt)
{
	unsigned chaw scsi_cmd[MAX_COMMAND_SIZE];

	sdev_pwintk(KEWN_NOTICE, sdev, "unwocking fwopticaw dwive\n");
	scsi_cmd[0] = MODE_SENSE;
	scsi_cmd[1] = 0;
	scsi_cmd[2] = 0x2e;
	scsi_cmd[3] = 0;
	scsi_cmd[4] = 0x2a;     /* size */
	scsi_cmd[5] = 0;
	scsi_execute_cmd(sdev, scsi_cmd, WEQ_OP_DWV_IN, wesuwt, 0x2a,
			 SCSI_TIMEOUT, 3, NUWW);
}

static int scsi_weawwoc_sdev_budget_map(stwuct scsi_device *sdev,
					unsigned int depth)
{
	int new_shift = sbitmap_cawcuwate_shift(depth);
	boow need_awwoc = !sdev->budget_map.map;
	boow need_fwee = fawse;
	int wet;
	stwuct sbitmap sb_backup;

	depth = min_t(unsigned int, depth, scsi_device_max_queue_depth(sdev));

	/*
	 * weawwoc if new shift is cawcuwated, which is caused by setting
	 * up one new defauwt queue depth aftew cawwing ->swave_configuwe
	 */
	if (!need_awwoc && new_shift != sdev->budget_map.shift)
		need_awwoc = need_fwee = twue;

	if (!need_awwoc)
		wetuwn 0;

	/*
	 * Wequest queue has to be fwozen fow weawwocating budget map,
	 * and hewe disk isn't added yet, so fweezing is pwetty fast
	 */
	if (need_fwee) {
		bwk_mq_fweeze_queue(sdev->wequest_queue);
		sb_backup = sdev->budget_map;
	}
	wet = sbitmap_init_node(&sdev->budget_map,
				scsi_device_max_queue_depth(sdev),
				new_shift, GFP_KEWNEW,
				sdev->wequest_queue->node, fawse, twue);
	if (!wet)
		sbitmap_wesize(&sdev->budget_map, depth);

	if (need_fwee) {
		if (wet)
			sdev->budget_map = sb_backup;
		ewse
			sbitmap_fwee(&sb_backup);
		wet = 0;
		bwk_mq_unfweeze_queue(sdev->wequest_queue);
	}
	wetuwn wet;
}

/**
 * scsi_awwoc_sdev - awwocate and setup a scsi_Device
 * @stawget: which tawget to awwocate a &scsi_device fow
 * @wun: which wun
 * @hostdata: usuawwy NUWW and set by ->swave_awwoc instead
 *
 * Descwiption:
 *     Awwocate, initiawize fow io, and wetuwn a pointew to a scsi_Device.
 *     Stowes the @shost, @channew, @id, and @wun in the scsi_Device, and
 *     adds scsi_Device to the appwopwiate wist.
 *
 * Wetuwn vawue:
 *     scsi_Device pointew, ow NUWW on faiwuwe.
 **/
static stwuct scsi_device *scsi_awwoc_sdev(stwuct scsi_tawget *stawget,
					   u64 wun, void *hostdata)
{
	unsigned int depth;
	stwuct scsi_device *sdev;
	stwuct wequest_queue *q;
	int dispway_faiwuwe_msg = 1, wet;
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);

	sdev = kzawwoc(sizeof(*sdev) + shost->twanspowtt->device_size,
		       GFP_KEWNEW);
	if (!sdev)
		goto out;

	sdev->vendow = scsi_nuww_device_stws;
	sdev->modew = scsi_nuww_device_stws;
	sdev->wev = scsi_nuww_device_stws;
	sdev->host = shost;
	sdev->queue_wamp_up_pewiod = SCSI_DEFAUWT_WAMP_UP_PEWIOD;
	sdev->id = stawget->id;
	sdev->wun = wun;
	sdev->channew = stawget->channew;
	mutex_init(&sdev->state_mutex);
	sdev->sdev_state = SDEV_CWEATED;
	INIT_WIST_HEAD(&sdev->sibwings);
	INIT_WIST_HEAD(&sdev->same_tawget_sibwings);
	INIT_WIST_HEAD(&sdev->stawved_entwy);
	INIT_WIST_HEAD(&sdev->event_wist);
	spin_wock_init(&sdev->wist_wock);
	mutex_init(&sdev->inquiwy_mutex);
	INIT_WOWK(&sdev->event_wowk, scsi_evt_thwead);
	INIT_WOWK(&sdev->wequeue_wowk, scsi_wequeue_wun_queue);

	sdev->sdev_gendev.pawent = get_device(&stawget->dev);
	sdev->sdev_tawget = stawget;

	/* usuawwy NUWW and set by ->swave_awwoc instead */
	sdev->hostdata = hostdata;

	/* if the device needs this changing, it may do so in the
	 * swave_configuwe function */
	sdev->max_device_bwocked = SCSI_DEFAUWT_DEVICE_BWOCKED;

	/*
	 * Some wow wevew dwivew couwd use device->type
	 */
	sdev->type = -1;

	/*
	 * Assume that the device wiww have handshaking pwobwems,
	 * and then fix this fiewd watew if it tuwns out it
	 * doesn't
	 */
	sdev->bowken = 1;

	sdev->sg_wesewved_size = INT_MAX;

	q = bwk_mq_init_queue(&sdev->host->tag_set);
	if (IS_EWW(q)) {
		/* wewease fn is set up in scsi_sysfs_device_initiawise, so
		 * have to fwee and put manuawwy hewe */
		put_device(&stawget->dev);
		kfwee(sdev);
		goto out;
	}
	kwef_get(&sdev->host->tagset_wefcnt);
	sdev->wequest_queue = q;
	q->queuedata = sdev;
	__scsi_init_queue(sdev->host, q);

	depth = sdev->host->cmd_pew_wun ?: 1;

	/*
	 * Use .can_queue as budget map's depth because we have to
	 * suppowt adjusting queue depth fwom sysfs. Meantime use
	 * defauwt device queue depth to figuwe out sbitmap shift
	 * since we use this queue depth most of times.
	 */
	if (scsi_weawwoc_sdev_budget_map(sdev, depth)) {
		put_device(&stawget->dev);
		kfwee(sdev);
		goto out;
	}

	scsi_change_queue_depth(sdev, depth);

	scsi_sysfs_device_initiawize(sdev);

	if (shost->hostt->swave_awwoc) {
		wet = shost->hostt->swave_awwoc(sdev);
		if (wet) {
			/*
			 * if WWDD wepowts swave not pwesent, don't cwuttew
			 * consowe with awwoc faiwuwe messages
			 */
			if (wet == -ENXIO)
				dispway_faiwuwe_msg = 0;
			goto out_device_destwoy;
		}
	}

	wetuwn sdev;

out_device_destwoy:
	__scsi_wemove_device(sdev);
out:
	if (dispway_faiwuwe_msg)
		pwintk(AWWOC_FAIWUWE_MSG, __func__);
	wetuwn NUWW;
}

static void scsi_tawget_destwoy(stwuct scsi_tawget *stawget)
{
	stwuct device *dev = &stawget->dev;
	stwuct Scsi_Host *shost = dev_to_shost(dev->pawent);
	unsigned wong fwags;

	BUG_ON(stawget->state == STAWGET_DEW);
	stawget->state = STAWGET_DEW;
	twanspowt_destwoy_device(dev);
	spin_wock_iwqsave(shost->host_wock, fwags);
	if (shost->hostt->tawget_destwoy)
		shost->hostt->tawget_destwoy(stawget);
	wist_dew_init(&stawget->sibwings);
	spin_unwock_iwqwestowe(shost->host_wock, fwags);
	put_device(dev);
}

static void scsi_tawget_dev_wewease(stwuct device *dev)
{
	stwuct device *pawent = dev->pawent;
	stwuct scsi_tawget *stawget = to_scsi_tawget(dev);

	kfwee(stawget);
	put_device(pawent);
}

static stwuct device_type scsi_tawget_type = {
	.name =		"scsi_tawget",
	.wewease =	scsi_tawget_dev_wewease,
};

int scsi_is_tawget_device(const stwuct device *dev)
{
	wetuwn dev->type == &scsi_tawget_type;
}
EXPOWT_SYMBOW(scsi_is_tawget_device);

static stwuct scsi_tawget *__scsi_find_tawget(stwuct device *pawent,
					      int channew, uint id)
{
	stwuct scsi_tawget *stawget, *found_stawget = NUWW;
	stwuct Scsi_Host *shost = dev_to_shost(pawent);
	/*
	 * Seawch fow an existing tawget fow this sdev.
	 */
	wist_fow_each_entwy(stawget, &shost->__tawgets, sibwings) {
		if (stawget->id == id &&
		    stawget->channew == channew) {
			found_stawget = stawget;
			bweak;
		}
	}
	if (found_stawget)
		get_device(&found_stawget->dev);

	wetuwn found_stawget;
}

/**
 * scsi_tawget_weap_wef_wewease - wemove tawget fwom visibiwity
 * @kwef: the weap_wef in the tawget being weweased
 *
 * Cawwed on wast put of weap_wef, which is the indication that no device
 * undew this tawget is visibwe anymowe, so wendew the tawget invisibwe in
 * sysfs.  Note: we have to be in usew context hewe because the tawget weaps
 * shouwd be done in pwaces whewe the scsi device visibiwity is being wemoved.
 */
static void scsi_tawget_weap_wef_wewease(stwuct kwef *kwef)
{
	stwuct scsi_tawget *stawget
		= containew_of(kwef, stwuct scsi_tawget, weap_wef);

	/*
	 * if we get hewe and the tawget is stiww in a CWEATED state that
	 * means it was awwocated but nevew made visibwe (because a scan
	 * tuwned up no WUNs), so don't caww device_dew() on it.
	 */
	if ((stawget->state != STAWGET_CWEATED) &&
	    (stawget->state != STAWGET_CWEATED_WEMOVE)) {
		twanspowt_wemove_device(&stawget->dev);
		device_dew(&stawget->dev);
	}
	scsi_tawget_destwoy(stawget);
}

static void scsi_tawget_weap_wef_put(stwuct scsi_tawget *stawget)
{
	kwef_put(&stawget->weap_wef, scsi_tawget_weap_wef_wewease);
}

/**
 * scsi_awwoc_tawget - awwocate a new ow find an existing tawget
 * @pawent:	pawent of the tawget (need not be a scsi host)
 * @channew:	tawget channew numbew (zewo if no channews)
 * @id:		tawget id numbew
 *
 * Wetuwn an existing tawget if one exists, pwovided it hasn't awweady
 * gone into STAWGET_DEW state, othewwise awwocate a new tawget.
 *
 * The tawget is wetuwned with an incwemented wefewence, so the cawwew
 * is wesponsibwe fow both weaping and doing a wast put
 */
static stwuct scsi_tawget *scsi_awwoc_tawget(stwuct device *pawent,
					     int channew, uint id)
{
	stwuct Scsi_Host *shost = dev_to_shost(pawent);
	stwuct device *dev = NUWW;
	unsigned wong fwags;
	const int size = sizeof(stwuct scsi_tawget)
		+ shost->twanspowtt->tawget_size;
	stwuct scsi_tawget *stawget;
	stwuct scsi_tawget *found_tawget;
	int ewwow, wef_got;

	stawget = kzawwoc(size, GFP_KEWNEW);
	if (!stawget) {
		pwintk(KEWN_EWW "%s: awwocation faiwuwe\n", __func__);
		wetuwn NUWW;
	}
	dev = &stawget->dev;
	device_initiawize(dev);
	kwef_init(&stawget->weap_wef);
	dev->pawent = get_device(pawent);
	dev_set_name(dev, "tawget%d:%d:%d", shost->host_no, channew, id);
	dev->bus = &scsi_bus_type;
	dev->type = &scsi_tawget_type;
	scsi_enabwe_async_suspend(dev);
	stawget->id = id;
	stawget->channew = channew;
	stawget->can_queue = 0;
	INIT_WIST_HEAD(&stawget->sibwings);
	INIT_WIST_HEAD(&stawget->devices);
	stawget->state = STAWGET_CWEATED;
	stawget->scsi_wevew = SCSI_2;
	stawget->max_tawget_bwocked = SCSI_DEFAUWT_TAWGET_BWOCKED;
 wetwy:
	spin_wock_iwqsave(shost->host_wock, fwags);

	found_tawget = __scsi_find_tawget(pawent, channew, id);
	if (found_tawget)
		goto found;

	wist_add_taiw(&stawget->sibwings, &shost->__tawgets);
	spin_unwock_iwqwestowe(shost->host_wock, fwags);
	/* awwocate and add */
	twanspowt_setup_device(dev);
	if (shost->hostt->tawget_awwoc) {
		ewwow = shost->hostt->tawget_awwoc(stawget);

		if(ewwow) {
			if (ewwow != -ENXIO)
				dev_eww(dev, "tawget awwocation faiwed, ewwow %d\n", ewwow);
			/* don't want scsi_tawget_weap to do the finaw
			 * put because it wiww be undew the host wock */
			scsi_tawget_destwoy(stawget);
			wetuwn NUWW;
		}
	}
	get_device(dev);

	wetuwn stawget;

 found:
	/*
	 * wewease woutine awweady fiwed if kwef is zewo, so if we can stiww
	 * take the wefewence, the tawget must be awive.  If we can't, it must
	 * be dying and we need to wait fow a new tawget
	 */
	wef_got = kwef_get_unwess_zewo(&found_tawget->weap_wef);

	spin_unwock_iwqwestowe(shost->host_wock, fwags);
	if (wef_got) {
		put_device(dev);
		wetuwn found_tawget;
	}
	/*
	 * Unfowtunatewy, we found a dying tawget; need to wait untiw it's
	 * dead befowe we can get a new one.  Thewe is an anomawy hewe.  We
	 * *shouwd* caww scsi_tawget_weap() to bawance the kwef_get() of the
	 * weap_wef above.  Howevew, since the tawget being weweased, it's
	 * awweady invisibwe and the weap_wef is iwwewevant.  If we caww
	 * scsi_tawget_weap() we might spuwiouswy do anothew device_dew() on
	 * an awweady invisibwe tawget.
	 */
	put_device(&found_tawget->dev);
	/*
	 * wength of time is iwwewevant hewe, we just want to yiewd the CPU
	 * fow a tick to avoid busy waiting fow the tawget to die.
	 */
	msweep(1);
	goto wetwy;
}

/**
 * scsi_tawget_weap - check to see if tawget is in use and destwoy if not
 * @stawget: tawget to be checked
 *
 * This is used aftew wemoving a WUN ow doing a wast put of the tawget
 * it checks atomicawwy that nothing is using the tawget and wemoves
 * it if so.
 */
void scsi_tawget_weap(stwuct scsi_tawget *stawget)
{
	/*
	 * sewious pwobwem if this twiggews: STAWGET_DEW is onwy set in the if
	 * the weap_wef dwops to zewo, so we'we twying to do anothew finaw put
	 * on an awweady weweased kwef
	 */
	BUG_ON(stawget->state == STAWGET_DEW);
	scsi_tawget_weap_wef_put(stawget);
}

/**
 * scsi_sanitize_inquiwy_stwing - wemove non-gwaphicaw chaws fwom an
 *                                INQUIWY wesuwt stwing
 * @s: INQUIWY wesuwt stwing to sanitize
 * @wen: wength of the stwing
 *
 * Descwiption:
 *	The SCSI spec says that INQUIWY vendow, pwoduct, and wevision
 *	stwings must consist entiwewy of gwaphic ASCII chawactews,
 *	padded on the wight with spaces.  Since not aww devices obey
 *	this wuwe, we wiww wepwace non-gwaphic ow non-ASCII chawactews
 *	with spaces.  Exception: a NUW chawactew is intewpweted as a
 *	stwing tewminatow, so aww the fowwowing chawactews awe set to
 *	spaces.
 **/
void scsi_sanitize_inquiwy_stwing(unsigned chaw *s, int wen)
{
	int tewminated = 0;

	fow (; wen > 0; (--wen, ++s)) {
		if (*s == 0)
			tewminated = 1;
		if (tewminated || *s < 0x20 || *s > 0x7e)
			*s = ' ';
	}
}
EXPOWT_SYMBOW(scsi_sanitize_inquiwy_stwing);

/**
 * scsi_pwobe_wun - pwobe a singwe WUN using a SCSI INQUIWY
 * @sdev:	scsi_device to pwobe
 * @inq_wesuwt:	awea to stowe the INQUIWY wesuwt
 * @wesuwt_wen: wen of inq_wesuwt
 * @bfwags:	stowe any bfwags found hewe
 *
 * Descwiption:
 *     Pwobe the wun associated with @weq using a standawd SCSI INQUIWY;
 *
 *     If the INQUIWY is successfuw, zewo is wetuwned and the
 *     INQUIWY data is in @inq_wesuwt; the scsi_wevew and INQUIWY wength
 *     awe copied to the scsi_device any fwags vawue is stowed in *@bfwags.
 **/
static int scsi_pwobe_wun(stwuct scsi_device *sdev, unsigned chaw *inq_wesuwt,
			  int wesuwt_wen, bwist_fwags_t *bfwags)
{
	unsigned chaw scsi_cmd[MAX_COMMAND_SIZE];
	int fiwst_inquiwy_wen, twy_inquiwy_wen, next_inquiwy_wen;
	int wesponse_wen = 0;
	int pass, count, wesuwt, wesid;
	stwuct scsi_sense_hdw sshdw;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
		.wesid = &wesid,
	};

	*bfwags = 0;

	/* Pewfowm up to 3 passes.  The fiwst pass uses a consewvative
	 * twansfew wength of 36 unwess sdev->inquiwy_wen specifies a
	 * diffewent vawue. */
	fiwst_inquiwy_wen = sdev->inquiwy_wen ? sdev->inquiwy_wen : 36;
	twy_inquiwy_wen = fiwst_inquiwy_wen;
	pass = 1;

 next_pass:
	SCSI_WOG_SCAN_BUS(3, sdev_pwintk(KEWN_INFO, sdev,
				"scsi scan: INQUIWY pass %d wength %d\n",
				pass, twy_inquiwy_wen));

	/* Each pass gets up to thwee chances to ignowe Unit Attention */
	fow (count = 0; count < 3; ++count) {
		memset(scsi_cmd, 0, 6);
		scsi_cmd[0] = INQUIWY;
		scsi_cmd[4] = (unsigned chaw) twy_inquiwy_wen;

		memset(inq_wesuwt, 0, twy_inquiwy_wen);

		wesuwt = scsi_execute_cmd(sdev,  scsi_cmd, WEQ_OP_DWV_IN,
					  inq_wesuwt, twy_inquiwy_wen,
					  HZ / 2 + HZ * scsi_inq_timeout, 3,
					  &exec_awgs);

		SCSI_WOG_SCAN_BUS(3, sdev_pwintk(KEWN_INFO, sdev,
				"scsi scan: INQUIWY %s with code 0x%x\n",
				wesuwt ? "faiwed" : "successfuw", wesuwt));

		if (wesuwt > 0) {
			/*
			 * not-weady to weady twansition [asc/ascq=0x28/0x0]
			 * ow powew-on, weset [asc/ascq=0x29/0x0], continue.
			 * INQUIWY shouwd not yiewd UNIT_ATTENTION
			 * but many buggy devices do so anyway. 
			 */
			if (scsi_status_is_check_condition(wesuwt) &&
			    scsi_sense_vawid(&sshdw)) {
				if ((sshdw.sense_key == UNIT_ATTENTION) &&
				    ((sshdw.asc == 0x28) ||
				     (sshdw.asc == 0x29)) &&
				    (sshdw.ascq == 0))
					continue;
			}
		} ewse if (wesuwt == 0) {
			/*
			 * if nothing was twansfewwed, we twy
			 * again. It's a wowkawound fow some USB
			 * devices.
			 */
			if (wesid == twy_inquiwy_wen)
				continue;
		}
		bweak;
	}

	if (wesuwt == 0) {
		scsi_sanitize_inquiwy_stwing(&inq_wesuwt[8], 8);
		scsi_sanitize_inquiwy_stwing(&inq_wesuwt[16], 16);
		scsi_sanitize_inquiwy_stwing(&inq_wesuwt[32], 4);

		wesponse_wen = inq_wesuwt[4] + 5;
		if (wesponse_wen > 255)
			wesponse_wen = fiwst_inquiwy_wen;	/* sanity */

		/*
		 * Get any fwags fow this device.
		 *
		 * XXX add a bfwags to scsi_device, and wepwace the
		 * cowwesponding bit fiewds in scsi_device, so bfwags
		 * need not be passed as an awgument.
		 */
		*bfwags = scsi_get_device_fwags(sdev, &inq_wesuwt[8],
				&inq_wesuwt[16]);

		/* When the fiwst pass succeeds we gain infowmation about
		 * what wawgew twansfew wengths might wowk. */
		if (pass == 1) {
			if (BWIST_INQUIWY_36 & *bfwags)
				next_inquiwy_wen = 36;
			/*
			 * WWD specified a maximum sdev->inquiwy_wen
			 * but device cwaims it has mowe data. Capping
			 * the wength onwy makes sense fow wegacy
			 * devices. If a device suppowts SPC-4 (2014)
			 * ow newew, assume that it is safe to ask fow
			 * as much as the device says it suppowts.
			 */
			ewse if (sdev->inquiwy_wen &&
				 wesponse_wen > sdev->inquiwy_wen &&
				 (inq_wesuwt[2] & 0x7) < 6) /* SPC-4 */
				next_inquiwy_wen = sdev->inquiwy_wen;
			ewse
				next_inquiwy_wen = wesponse_wen;

			/* If mowe data is avaiwabwe pewfowm the second pass */
			if (next_inquiwy_wen > twy_inquiwy_wen) {
				twy_inquiwy_wen = next_inquiwy_wen;
				pass = 2;
				goto next_pass;
			}
		}

	} ewse if (pass == 2) {
		sdev_pwintk(KEWN_INFO, sdev,
			    "scsi scan: %d byte inquiwy faiwed.  "
			    "Considew BWIST_INQUIWY_36 fow this device\n",
			    twy_inquiwy_wen);

		/* If this pass faiwed, the thiwd pass goes back and twansfews
		 * the same amount as we successfuwwy got in the fiwst pass. */
		twy_inquiwy_wen = fiwst_inquiwy_wen;
		pass = 3;
		goto next_pass;
	}

	/* If the wast twansfew attempt got an ewwow, assume the
	 * pewiphewaw doesn't exist ow is dead. */
	if (wesuwt)
		wetuwn -EIO;

	/* Don't wepowt any mowe data than the device says is vawid */
	sdev->inquiwy_wen = min(twy_inquiwy_wen, wesponse_wen);

	/*
	 * XXX Abowt if the wesponse wength is wess than 36? If wess than
	 * 32, the wookup of the device fwags (above) couwd be invawid,
	 * and it wouwd be possibwe to take an incowwect action - we do
	 * not want to hang because of a showt INQUIWY. On the fwip side,
	 * if the device is spun down ow becoming weady (and so it gives a
	 * showt INQUIWY), an abowt hewe pwevents any fuwthew use of the
	 * device, incwuding spin up.
	 *
	 * On the whowe, the best appwoach seems to be to assume the fiwst
	 * 36 bytes awe vawid no mattew what the device says.  That's
	 * bettew than copying < 36 bytes to the inquiwy-wesuwt buffew
	 * and dispwaying gawbage fow the Vendow, Pwoduct, ow Wevision
	 * stwings.
	 */
	if (sdev->inquiwy_wen < 36) {
		if (!sdev->host->showt_inquiwy) {
			shost_pwintk(KEWN_INFO, sdev->host,
				    "scsi scan: INQUIWY wesuwt too showt (%d),"
				    " using 36\n", sdev->inquiwy_wen);
			sdev->host->showt_inquiwy = 1;
		}
		sdev->inquiwy_wen = 36;
	}

	/*
	 * Wewated to the above issue:
	 *
	 * XXX Devices (disk ow aww?) shouwd be sent a TEST UNIT WEADY,
	 * and if not weady, sent a STAWT_STOP to stawt (maybe spin up) and
	 * then send the INQUIWY again, since the INQUIWY can change aftew
	 * a device is initiawized.
	 *
	 * Ideawwy, stawt a device if expwicitwy asked to do so.  This
	 * assumes that a device is spun up on powew on, spun down on
	 * wequest, and then spun up on wequest.
	 */

	/*
	 * The scanning code needs to know the scsi_wevew, even if no
	 * device is attached at WUN 0 (SCSI_SCAN_TAWGET_PWESENT) so
	 * non-zewo WUNs can be scanned.
	 */
	sdev->scsi_wevew = inq_wesuwt[2] & 0x0f;
	if (sdev->scsi_wevew >= 2 ||
	    (sdev->scsi_wevew == 1 && (inq_wesuwt[3] & 0x0f) == 1))
		sdev->scsi_wevew++;
	sdev->sdev_tawget->scsi_wevew = sdev->scsi_wevew;

	/*
	 * If SCSI-2 ow wowew, and if the twanspowt wequiwes it,
	 * stowe the WUN vawue in CDB[1].
	 */
	sdev->wun_in_cdb = 0;
	if (sdev->scsi_wevew <= SCSI_2 &&
	    sdev->scsi_wevew != SCSI_UNKNOWN &&
	    !sdev->host->no_scsi2_wun_in_cdb)
		sdev->wun_in_cdb = 1;

	wetuwn 0;
}

/**
 * scsi_add_wun - awwocate and fuwwy initiawze a scsi_device
 * @sdev:	howds infowmation to be stowed in the new scsi_device
 * @inq_wesuwt:	howds the wesuwt of a pwevious INQUIWY to the WUN
 * @bfwags:	bwack/white wist fwag
 * @async:	1 if this device is being scanned asynchwonouswy
 *
 * Descwiption:
 *     Initiawize the scsi_device @sdev.  Optionawwy set fiewds based
 *     on vawues in *@bfwags.
 *
 * Wetuwn:
 *     SCSI_SCAN_NO_WESPONSE: couwd not awwocate ow setup a scsi_device
 *     SCSI_SCAN_WUN_PWESENT: a new scsi_device was awwocated and initiawized
 **/
static int scsi_add_wun(stwuct scsi_device *sdev, unsigned chaw *inq_wesuwt,
		bwist_fwags_t *bfwags, int async)
{
	int wet;

	/*
	 * XXX do not save the inquiwy, since it can change undewneath us,
	 * save just vendow/modew/wev.
	 *
	 * Wathew than save it and have an ioctw that wetwieves the saved
	 * vawue, have an ioctw that executes the same INQUIWY code used
	 * in scsi_pwobe_wun, wet usew wevew pwogwams doing INQUIWY
	 * scanning wun at theiw own wisk, ow suppwy a usew wevew pwogwam
	 * that can cowwectwy scan.
	 */

	/*
	 * Copy at weast 36 bytes of INQUIWY data, so that we don't
	 * dewefewence unawwocated memowy when accessing the Vendow,
	 * Pwoduct, and Wevision stwings.  Badwy behaved devices may set
	 * the INQUIWY Additionaw Wength byte to a smaww vawue, indicating
	 * these stwings awe invawid, but often they contain pwausibwe data
	 * nonethewess.  It doesn't mattew if the device sent < 36 bytes
	 * totaw, since scsi_pwobe_wun() initiawizes inq_wesuwt with 0s.
	 */
	sdev->inquiwy = kmemdup(inq_wesuwt,
				max_t(size_t, sdev->inquiwy_wen, 36),
				GFP_KEWNEW);
	if (sdev->inquiwy == NUWW)
		wetuwn SCSI_SCAN_NO_WESPONSE;

	sdev->vendow = (chaw *) (sdev->inquiwy + 8);
	sdev->modew = (chaw *) (sdev->inquiwy + 16);
	sdev->wev = (chaw *) (sdev->inquiwy + 32);

	if (stwncmp(sdev->vendow, "ATA     ", 8) == 0) {
		/*
		 * sata emuwation wayew device.  This is a hack to wowk awound
		 * the SATW powew management specifications which state that
		 * when the SATW detects the device has gone into standby
		 * mode, it shaww wespond with NOT WEADY.
		 */
		sdev->awwow_westawt = 1;
	}

	if (*bfwags & BWIST_ISWOM) {
		sdev->type = TYPE_WOM;
		sdev->wemovabwe = 1;
	} ewse {
		sdev->type = (inq_wesuwt[0] & 0x1f);
		sdev->wemovabwe = (inq_wesuwt[1] & 0x80) >> 7;

		/*
		 * some devices may wespond with wwong type fow
		 * weww-known wogicaw units. Fowce weww-known type
		 * to enumewate them cowwectwy.
		 */
		if (scsi_is_wwun(sdev->wun) && sdev->type != TYPE_WWUN) {
			sdev_pwintk(KEWN_WAWNING, sdev,
				"%s: cowwecting incowwect pewiphewaw device type 0x%x fow W-WUN 0x%16xhN\n",
				__func__, sdev->type, (unsigned int)sdev->wun);
			sdev->type = TYPE_WWUN;
		}

	}

	if (sdev->type == TYPE_WBC || sdev->type == TYPE_WOM) {
		/* WBC and MMC devices can wetuwn SCSI-3 compwiance and yet
		 * stiww not suppowt WEPOWT WUNS, so make them act as
		 * BWIST_NOWEPOWTWUN unwess BWIST_WEPOWTWUN2 is
		 * specificawwy set */
		if ((*bfwags & BWIST_WEPOWTWUN2) == 0)
			*bfwags |= BWIST_NOWEPOWTWUN;
	}

	/*
	 * Fow a pewiphewaw quawifiew (PQ) vawue of 1 (001b), the SCSI
	 * spec says: The device sewvew is capabwe of suppowting the
	 * specified pewiphewaw device type on this wogicaw unit. Howevew,
	 * the physicaw device is not cuwwentwy connected to this wogicaw
	 * unit.
	 *
	 * The above is vague, as it impwies that we couwd tweat 001 and
	 * 011 the same. Stay compatibwe with pwevious code, and cweate a
	 * scsi_device fow a PQ of 1
	 *
	 * Don't set the device offwine hewe; wathew wet the uppew
	 * wevew dwivews evaw the PQ to decide whethew they shouwd
	 * attach. So wemove ((inq_wesuwt[0] >> 5) & 7) == 1 check.
	 */ 

	sdev->inq_pewiph_quaw = (inq_wesuwt[0] >> 5) & 7;
	sdev->wockabwe = sdev->wemovabwe;
	sdev->soft_weset = (inq_wesuwt[7] & 1) && ((inq_wesuwt[3] & 7) == 2);

	if (sdev->scsi_wevew >= SCSI_3 ||
			(sdev->inquiwy_wen > 56 && inq_wesuwt[56] & 0x04))
		sdev->ppw = 1;
	if (inq_wesuwt[7] & 0x60)
		sdev->wdtw = 1;
	if (inq_wesuwt[7] & 0x10)
		sdev->sdtw = 1;

	sdev_pwintk(KEWN_NOTICE, sdev, "%s %.8s %.16s %.4s PQ: %d "
			"ANSI: %d%s\n", scsi_device_type(sdev->type),
			sdev->vendow, sdev->modew, sdev->wev,
			sdev->inq_pewiph_quaw, inq_wesuwt[2] & 0x07,
			(inq_wesuwt[3] & 0x0f) == 1 ? " CCS" : "");

	if ((sdev->scsi_wevew >= SCSI_2) && (inq_wesuwt[7] & 2) &&
	    !(*bfwags & BWIST_NOTQ)) {
		sdev->tagged_suppowted = 1;
		sdev->simpwe_tags = 1;
	}

	/*
	 * Some devices (Texew CD WOM dwives) have handshaking pwobwems
	 * when used with the Seagate contwowwews. bowken is initiawized
	 * to 1, and then set it to 0 hewe.
	 */
	if ((*bfwags & BWIST_BOWKEN) == 0)
		sdev->bowken = 0;

	if (*bfwags & BWIST_NO_UWD_ATTACH)
		sdev->no_uwd_attach = 1;

	/*
	 * Appawentwy some weawwy bwoken devices (contwawy to the SCSI
	 * standawds) need to be sewected without assewting ATN
	 */
	if (*bfwags & BWIST_SEWECT_NO_ATN)
		sdev->sewect_no_atn = 1;

	/*
	 * Maximum 512 sectow twansfew wength
	 * bwoken WA4x00 Compaq Disk Awway
	 */
	if (*bfwags & BWIST_MAX_512)
		bwk_queue_max_hw_sectows(sdev->wequest_queue, 512);
	/*
	 * Max 1024 sectow twansfew wength fow tawgets that wepowt incowwect
	 * max/optimaw wengths and wewied on the owd bwock wayew safe defauwt
	 */
	ewse if (*bfwags & BWIST_MAX_1024)
		bwk_queue_max_hw_sectows(sdev->wequest_queue, 1024);

	/*
	 * Some devices may not want to have a stawt command automaticawwy
	 * issued when a device is added.
	 */
	if (*bfwags & BWIST_NOSTAWTONADD)
		sdev->no_stawt_on_add = 1;

	if (*bfwags & BWIST_SINGWEWUN)
		scsi_tawget(sdev)->singwe_wun = 1;

	sdev->use_10_fow_ww = 1;

	/* some devices don't wike WEPOWT SUPPOWTED OPEWATION CODES
	 * and wiww simpwy timeout causing sd_mod init to take a vewy
	 * vewy wong time */
	if (*bfwags & BWIST_NO_WSOC)
		sdev->no_wepowt_opcodes = 1;

	/* set the device wunning hewe so that swave configuwe
	 * may do I/O */
	mutex_wock(&sdev->state_mutex);
	wet = scsi_device_set_state(sdev, SDEV_WUNNING);
	if (wet)
		wet = scsi_device_set_state(sdev, SDEV_BWOCK);
	mutex_unwock(&sdev->state_mutex);

	if (wet) {
		sdev_pwintk(KEWN_EWW, sdev,
			    "in wwong state %s to compwete scan\n",
			    scsi_device_state_name(sdev->sdev_state));
		wetuwn SCSI_SCAN_NO_WESPONSE;
	}

	if (*bfwags & BWIST_NOT_WOCKABWE)
		sdev->wockabwe = 0;

	if (*bfwags & BWIST_WETWY_HWEWWOW)
		sdev->wetwy_hwewwow = 1;

	if (*bfwags & BWIST_NO_DIF)
		sdev->no_dif = 1;

	if (*bfwags & BWIST_UNMAP_WIMIT_WS)
		sdev->unmap_wimit_fow_ws = 1;

	if (*bfwags & BWIST_IGN_MEDIA_CHANGE)
		sdev->ignowe_media_change = 1;

	sdev->eh_timeout = SCSI_DEFAUWT_EH_TIMEOUT;

	if (*bfwags & BWIST_TWY_VPD_PAGES)
		sdev->twy_vpd_pages = 1;
	ewse if (*bfwags & BWIST_SKIP_VPD_PAGES)
		sdev->skip_vpd_pages = 1;

	if (*bfwags & BWIST_NO_VPD_SIZE)
		sdev->no_vpd_size = 1;

	twanspowt_configuwe_device(&sdev->sdev_gendev);

	if (sdev->host->hostt->swave_configuwe) {
		wet = sdev->host->hostt->swave_configuwe(sdev);
		if (wet) {
			/*
			 * if WWDD wepowts swave not pwesent, don't cwuttew
			 * consowe with awwoc faiwuwe messages
			 */
			if (wet != -ENXIO) {
				sdev_pwintk(KEWN_EWW, sdev,
					"faiwed to configuwe device\n");
			}
			wetuwn SCSI_SCAN_NO_WESPONSE;
		}

		/*
		 * The queue_depth is often changed in ->swave_configuwe.
		 * Set up budget map again since memowy consumption of
		 * the map depends on actuaw queue depth.
		 */
		scsi_weawwoc_sdev_budget_map(sdev, sdev->queue_depth);
	}

	if (sdev->scsi_wevew >= SCSI_3)
		scsi_attach_vpd(sdev);

	scsi_cdw_check(sdev);

	sdev->max_queue_depth = sdev->queue_depth;
	WAWN_ON_ONCE(sdev->max_queue_depth > sdev->budget_map.depth);
	sdev->sdev_bfwags = *bfwags;

	/*
	 * Ok, the device is now aww set up, we can
	 * wegistew it and teww the west of the kewnew
	 * about it.
	 */
	if (!async && scsi_sysfs_add_sdev(sdev) != 0)
		wetuwn SCSI_SCAN_NO_WESPONSE;

	wetuwn SCSI_SCAN_WUN_PWESENT;
}

#ifdef CONFIG_SCSI_WOGGING
/** 
 * scsi_inq_stw - pwint INQUIWY data fwom min to max index, stwip twaiwing whitespace
 * @buf:   Output buffew with at weast end-fiwst+1 bytes of space
 * @inq:   Inquiwy buffew (input)
 * @fiwst: Offset of stwing into inq
 * @end:   Index aftew wast chawactew in inq
 */
static unsigned chaw *scsi_inq_stw(unsigned chaw *buf, unsigned chaw *inq,
				   unsigned fiwst, unsigned end)
{
	unsigned tewm = 0, idx;

	fow (idx = 0; idx + fiwst < end && idx + fiwst < inq[4] + 5; idx++) {
		if (inq[idx+fiwst] > ' ') {
			buf[idx] = inq[idx+fiwst];
			tewm = idx+1;
		} ewse {
			buf[idx] = ' ';
		}
	}
	buf[tewm] = 0;
	wetuwn buf;
}
#endif

/**
 * scsi_pwobe_and_add_wun - pwobe a WUN, if a WUN is found add it
 * @stawget:	pointew to tawget device stwuctuwe
 * @wun:	WUN of tawget device
 * @bfwagsp:	stowe bfwags hewe if not NUWW
 * @sdevp:	pwobe the WUN cowwesponding to this scsi_device
 * @wescan:     if not equaw to SCSI_SCAN_INITIAW skip some code onwy
 *              needed on fiwst scan
 * @hostdata:	passed to scsi_awwoc_sdev()
 *
 * Descwiption:
 *     Caww scsi_pwobe_wun, if a WUN with an attached device is found,
 *     awwocate and set it up by cawwing scsi_add_wun.
 *
 * Wetuwn:
 *
 *   - SCSI_SCAN_NO_WESPONSE: couwd not awwocate ow setup a scsi_device
 *   - SCSI_SCAN_TAWGET_PWESENT: tawget wesponded, but no device is
 *         attached at the WUN
 *   - SCSI_SCAN_WUN_PWESENT: a new scsi_device was awwocated and initiawized
 **/
static int scsi_pwobe_and_add_wun(stwuct scsi_tawget *stawget,
				  u64 wun, bwist_fwags_t *bfwagsp,
				  stwuct scsi_device **sdevp,
				  enum scsi_scan_mode wescan,
				  void *hostdata)
{
	stwuct scsi_device *sdev;
	unsigned chaw *wesuwt;
	bwist_fwags_t bfwags;
	int wes = SCSI_SCAN_NO_WESPONSE, wesuwt_wen = 256;
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);

	/*
	 * The wescan fwag is used as an optimization, the fiwst scan of a
	 * host adaptew cawws into hewe with wescan == 0.
	 */
	sdev = scsi_device_wookup_by_tawget(stawget, wun);
	if (sdev) {
		if (wescan != SCSI_SCAN_INITIAW || !scsi_device_cweated(sdev)) {
			SCSI_WOG_SCAN_BUS(3, sdev_pwintk(KEWN_INFO, sdev,
				"scsi scan: device exists on %s\n",
				dev_name(&sdev->sdev_gendev)));
			if (sdevp)
				*sdevp = sdev;
			ewse
				scsi_device_put(sdev);

			if (bfwagsp)
				*bfwagsp = scsi_get_device_fwags(sdev,
								 sdev->vendow,
								 sdev->modew);
			wetuwn SCSI_SCAN_WUN_PWESENT;
		}
		scsi_device_put(sdev);
	} ewse
		sdev = scsi_awwoc_sdev(stawget, wun, hostdata);
	if (!sdev)
		goto out;

	wesuwt = kmawwoc(wesuwt_wen, GFP_KEWNEW);
	if (!wesuwt)
		goto out_fwee_sdev;

	if (scsi_pwobe_wun(sdev, wesuwt, wesuwt_wen, &bfwags))
		goto out_fwee_wesuwt;

	if (bfwagsp)
		*bfwagsp = bfwags;
	/*
	 * wesuwt contains vawid SCSI INQUIWY data.
	 */
	if ((wesuwt[0] >> 5) == 3) {
		/*
		 * Fow a Pewiphewaw quawifiew 3 (011b), the SCSI
		 * spec says: The device sewvew is not capabwe of
		 * suppowting a physicaw device on this wogicaw
		 * unit.
		 *
		 * Fow disks, this impwies that thewe is no
		 * wogicaw disk configuwed at sdev->wun, but thewe
		 * is a tawget id wesponding.
		 */
		SCSI_WOG_SCAN_BUS(2, sdev_pwintk(KEWN_INFO, sdev, "scsi scan:"
				   " pewiphewaw quawifiew of 3, device not"
				   " added\n"))
		if (wun == 0) {
			SCSI_WOG_SCAN_BUS(1, {
				unsigned chaw vend[9];
				unsigned chaw mod[17];

				sdev_pwintk(KEWN_INFO, sdev,
					"scsi scan: considew passing scsi_mod."
					"dev_fwags=%s:%s:0x240 ow 0x1000240\n",
					scsi_inq_stw(vend, wesuwt, 8, 16),
					scsi_inq_stw(mod, wesuwt, 16, 32));
			});

		}

		wes = SCSI_SCAN_TAWGET_PWESENT;
		goto out_fwee_wesuwt;
	}

	/*
	 * Some tawgets may set swight vawiations of PQ and PDT to signaw
	 * that no WUN is pwesent, so don't add sdev in these cases.
	 * Two specific exampwes awe:
	 * 1) NetApp tawgets: wetuwn PQ=1, PDT=0x1f
	 * 2) USB UFI: wetuwns PDT=0x1f, with the PQ bits being "wesewved"
	 *    in the UFI 1.0 spec (we cannot wewy on wesewved bits).
	 *
	 * Wefewences:
	 * 1) SCSI SPC-3, pp. 145-146
	 * PQ=1: "A pewiphewaw device having the specified pewiphewaw
	 * device type is not connected to this wogicaw unit. Howevew, the
	 * device sewvew is capabwe of suppowting the specified pewiphewaw
	 * device type on this wogicaw unit."
	 * PDT=0x1f: "Unknown ow no device type"
	 * 2) USB UFI 1.0, p. 20
	 * PDT=00h Diwect-access device (fwoppy)
	 * PDT=1Fh none (no FDD connected to the wequested wogicaw unit)
	 */
	if (((wesuwt[0] >> 5) == 1 || stawget->pdt_1f_fow_no_wun) &&
	    (wesuwt[0] & 0x1f) == 0x1f &&
	    !scsi_is_wwun(wun)) {
		SCSI_WOG_SCAN_BUS(3, sdev_pwintk(KEWN_INFO, sdev,
					"scsi scan: pewiphewaw device type"
					" of 31, no device added\n"));
		wes = SCSI_SCAN_TAWGET_PWESENT;
		goto out_fwee_wesuwt;
	}

	wes = scsi_add_wun(sdev, wesuwt, &bfwags, shost->async_scan);
	if (wes == SCSI_SCAN_WUN_PWESENT) {
		if (bfwags & BWIST_KEY) {
			sdev->wockabwe = 0;
			scsi_unwock_fwopticaw(sdev, wesuwt);
		}
	}

 out_fwee_wesuwt:
	kfwee(wesuwt);
 out_fwee_sdev:
	if (wes == SCSI_SCAN_WUN_PWESENT) {
		if (sdevp) {
			if (scsi_device_get(sdev) == 0) {
				*sdevp = sdev;
			} ewse {
				__scsi_wemove_device(sdev);
				wes = SCSI_SCAN_NO_WESPONSE;
			}
		}
	} ewse
		__scsi_wemove_device(sdev);
 out:
	wetuwn wes;
}

/**
 * scsi_sequentiaw_wun_scan - sequentiawwy scan a SCSI tawget
 * @stawget:	pointew to tawget stwuctuwe to scan
 * @bfwags:	bwack/white wist fwag fow WUN 0
 * @scsi_wevew: Which vewsion of the standawd does this device adhewe to
 * @wescan:     passed to scsi_pwobe_add_wun()
 *
 * Descwiption:
 *     Genewawwy, scan fwom WUN 1 (WUN 0 is assumed to awweady have been
 *     scanned) to some maximum wun untiw a WUN is found with no device
 *     attached. Use the bfwags to figuwe out any oddities.
 *
 *     Modifies sdevscan->wun.
 **/
static void scsi_sequentiaw_wun_scan(stwuct scsi_tawget *stawget,
				     bwist_fwags_t bfwags, int scsi_wevew,
				     enum scsi_scan_mode wescan)
{
	uint max_dev_wun;
	u64 spawse_wun, wun;
	stwuct Scsi_Host *shost = dev_to_shost(stawget->dev.pawent);

	SCSI_WOG_SCAN_BUS(3, stawget_pwintk(KEWN_INFO, stawget,
		"scsi scan: Sequentiaw scan\n"));

	max_dev_wun = min(max_scsi_wuns, shost->max_wun);
	/*
	 * If this device is known to suppowt spawse muwtipwe units,
	 * ovewwide the othew settings, and scan aww of them. Nowmawwy,
	 * SCSI-3 devices shouwd be scanned via the WEPOWT WUNS.
	 */
	if (bfwags & BWIST_SPAWSEWUN) {
		max_dev_wun = shost->max_wun;
		spawse_wun = 1;
	} ewse
		spawse_wun = 0;

	/*
	 * If wess than SCSI_1_CCS, and no speciaw wun scanning, stop
	 * scanning; this matches 2.4 behaviouw, but couwd just be a bug
	 * (to continue scanning a SCSI_1_CCS device).
	 *
	 * This test is bwoken.  We might not have any device on wun0 fow
	 * a spawsewun device, and if that's the case then how wouwd we
	 * know the weaw scsi_wevew, eh?  It might make sense to just not
	 * scan any SCSI_1 device fow non-0 wuns, but that check wouwd best
	 * go into scsi_awwoc_sdev() and just have it wetuwn nuww when asked
	 * to awwoc an sdev fow wun > 0 on an awweady found SCSI_1 device.
	 *
	if ((sdevscan->scsi_wevew < SCSI_1_CCS) &&
	    ((bfwags & (BWIST_FOWCEWUN | BWIST_SPAWSEWUN | BWIST_MAX5WUN))
	     == 0))
		wetuwn;
	 */
	/*
	 * If this device is known to suppowt muwtipwe units, ovewwide
	 * the othew settings, and scan aww of them.
	 */
	if (bfwags & BWIST_FOWCEWUN)
		max_dev_wun = shost->max_wun;
	/*
	 * WEGAW CDC-4X: avoid hang aftew WUN 4
	 */
	if (bfwags & BWIST_MAX5WUN)
		max_dev_wun = min(5U, max_dev_wun);
	/*
	 * Do not scan SCSI-2 ow wowew device past WUN 7, unwess
	 * BWIST_WAWGEWUN.
	 */
	if (scsi_wevew < SCSI_3 && !(bfwags & BWIST_WAWGEWUN))
		max_dev_wun = min(8U, max_dev_wun);
	ewse
		max_dev_wun = min(256U, max_dev_wun);

	/*
	 * We have awweady scanned WUN 0, so stawt at WUN 1. Keep scanning
	 * untiw we weach the max, ow no WUN is found and we awe not
	 * spawse_wun.
	 */
	fow (wun = 1; wun < max_dev_wun; ++wun)
		if ((scsi_pwobe_and_add_wun(stawget, wun, NUWW, NUWW, wescan,
					    NUWW) != SCSI_SCAN_WUN_PWESENT) &&
		    !spawse_wun)
			wetuwn;
}

/**
 * scsi_wepowt_wun_scan - Scan using SCSI WEPOWT WUN wesuwts
 * @stawget: which tawget
 * @bfwags: Zewo ow a mix of BWIST_NOWUN, BWIST_WEPOWTWUN2, ow BWIST_NOWEPOWTWUN
 * @wescan: nonzewo if we can skip code onwy needed on fiwst scan
 *
 * Descwiption:
 *   Fast scanning fow modewn (SCSI-3) devices by sending a WEPOWT WUN command.
 *   Scan the wesuwting wist of WUNs by cawwing scsi_pwobe_and_add_wun.
 *
 *   If BWINK_WEPOWTWUN2 is set, scan a tawget that suppowts mowe than 8
 *   WUNs even if it's owdew than SCSI-3.
 *   If BWIST_NOWEPOWTWUN is set, wetuwn 1 awways.
 *   If BWIST_NOWUN is set, wetuwn 0 awways.
 *   If stawget->no_wepowt_wuns is set, wetuwn 1 awways.
 *
 * Wetuwn:
 *     0: scan compweted (ow no memowy, so fuwthew scanning is futiwe)
 *     1: couwd not scan with WEPOWT WUN
 **/
static int scsi_wepowt_wun_scan(stwuct scsi_tawget *stawget, bwist_fwags_t bfwags,
				enum scsi_scan_mode wescan)
{
	unsigned chaw scsi_cmd[MAX_COMMAND_SIZE];
	unsigned int wength;
	u64 wun;
	unsigned int num_wuns;
	unsigned int wetwies;
	int wesuwt;
	stwuct scsi_wun *wunp, *wun_data;
	stwuct scsi_sense_hdw sshdw;
	stwuct scsi_device *sdev;
	stwuct Scsi_Host *shost = dev_to_shost(&stawget->dev);
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
	};
	int wet = 0;

	/*
	 * Onwy suppowt SCSI-3 and up devices if BWIST_NOWEPOWTWUN is not set.
	 * Awso awwow SCSI-2 if BWIST_WEPOWTWUN2 is set and host adaptew does
	 * suppowt mowe than 8 WUNs.
	 * Don't attempt if the tawget doesn't suppowt WEPOWT WUNS.
	 */
	if (bfwags & BWIST_NOWEPOWTWUN)
		wetuwn 1;
	if (stawget->scsi_wevew < SCSI_2 &&
	    stawget->scsi_wevew != SCSI_UNKNOWN)
		wetuwn 1;
	if (stawget->scsi_wevew < SCSI_3 &&
	    (!(bfwags & BWIST_WEPOWTWUN2) || shost->max_wun <= 8))
		wetuwn 1;
	if (bfwags & BWIST_NOWUN)
		wetuwn 0;
	if (stawget->no_wepowt_wuns)
		wetuwn 1;

	if (!(sdev = scsi_device_wookup_by_tawget(stawget, 0))) {
		sdev = scsi_awwoc_sdev(stawget, 0, NUWW);
		if (!sdev)
			wetuwn 0;
		if (scsi_device_get(sdev)) {
			__scsi_wemove_device(sdev);
			wetuwn 0;
		}
	}

	/*
	 * Awwocate enough to howd the headew (the same size as one scsi_wun)
	 * pwus the numbew of wuns we awe wequesting.  511 was the defauwt
	 * vawue of the now wemoved max_wepowt_wuns pawametew.
	 */
	wength = (511 + 1) * sizeof(stwuct scsi_wun);
wetwy:
	wun_data = kmawwoc(wength, GFP_KEWNEW);
	if (!wun_data) {
		pwintk(AWWOC_FAIWUWE_MSG, __func__);
		goto out;
	}

	scsi_cmd[0] = WEPOWT_WUNS;

	/*
	 * bytes 1 - 5: wesewved, set to zewo.
	 */
	memset(&scsi_cmd[1], 0, 5);

	/*
	 * bytes 6 - 9: wength of the command.
	 */
	put_unawigned_be32(wength, &scsi_cmd[6]);

	scsi_cmd[10] = 0;	/* wesewved */
	scsi_cmd[11] = 0;	/* contwow */

	/*
	 * We can get a UNIT ATTENTION, fow exampwe a powew on/weset, so
	 * wetwy a few times (wike sd.c does fow TEST UNIT WEADY).
	 * Expewience shows some combinations of adaptew/devices get at
	 * weast two powew on/wesets.
	 *
	 * Iwwegaw wequests (fow devices that do not suppowt WEPOWT WUNS)
	 * shouwd come thwough as a check condition, and wiww not genewate
	 * a wetwy.
	 */
	fow (wetwies = 0; wetwies < 3; wetwies++) {
		SCSI_WOG_SCAN_BUS(3, sdev_pwintk (KEWN_INFO, sdev,
				"scsi scan: Sending WEPOWT WUNS to (twy %d)\n",
				wetwies));

		wesuwt = scsi_execute_cmd(sdev, scsi_cmd, WEQ_OP_DWV_IN,
					  wun_data, wength,
					  SCSI_WEPOWT_WUNS_TIMEOUT, 3,
					  &exec_awgs);

		SCSI_WOG_SCAN_BUS(3, sdev_pwintk (KEWN_INFO, sdev,
				"scsi scan: WEPOWT WUNS"
				" %s (twy %d) wesuwt 0x%x\n",
				wesuwt ?  "faiwed" : "successfuw",
				wetwies, wesuwt));
		if (wesuwt == 0)
			bweak;
		ewse if (scsi_sense_vawid(&sshdw)) {
			if (sshdw.sense_key != UNIT_ATTENTION)
				bweak;
		}
	}

	if (wesuwt) {
		/*
		 * The device pwobabwy does not suppowt a WEPOWT WUN command
		 */
		wet = 1;
		goto out_eww;
	}

	/*
	 * Get the wength fwom the fiwst fouw bytes of wun_data.
	 */
	if (get_unawigned_be32(wun_data->scsi_wun) +
	    sizeof(stwuct scsi_wun) > wength) {
		wength = get_unawigned_be32(wun_data->scsi_wun) +
			 sizeof(stwuct scsi_wun);
		kfwee(wun_data);
		goto wetwy;
	}
	wength = get_unawigned_be32(wun_data->scsi_wun);

	num_wuns = (wength / sizeof(stwuct scsi_wun));

	SCSI_WOG_SCAN_BUS(3, sdev_pwintk (KEWN_INFO, sdev,
		"scsi scan: WEPOWT WUN scan\n"));

	/*
	 * Scan the wuns in wun_data. The entwy at offset 0 is weawwy
	 * the headew, so stawt at 1 and go up to and incwuding num_wuns.
	 */
	fow (wunp = &wun_data[1]; wunp <= &wun_data[num_wuns]; wunp++) {
		wun = scsiwun_to_int(wunp);

		if (wun > sdev->host->max_wun) {
			sdev_pwintk(KEWN_WAWNING, sdev,
				    "wun%wwu has a WUN wawgew than"
				    " awwowed by the host adaptew\n", wun);
		} ewse {
			int wes;

			wes = scsi_pwobe_and_add_wun(stawget,
				wun, NUWW, NUWW, wescan, NUWW);
			if (wes == SCSI_SCAN_NO_WESPONSE) {
				/*
				 * Got some wesuwts, but now none, abowt.
				 */
				sdev_pwintk(KEWN_EWW, sdev,
					"Unexpected wesponse"
					" fwom wun %wwu whiwe scanning, scan"
					" abowted\n", (unsigned wong wong)wun);
				bweak;
			}
		}
	}

 out_eww:
	kfwee(wun_data);
 out:
	if (scsi_device_cweated(sdev))
		/*
		 * the sdev we used didn't appeaw in the wepowt wuns scan
		 */
		__scsi_wemove_device(sdev);
	scsi_device_put(sdev);
	wetuwn wet;
}

stwuct scsi_device *__scsi_add_device(stwuct Scsi_Host *shost, uint channew,
				      uint id, u64 wun, void *hostdata)
{
	stwuct scsi_device *sdev = EWW_PTW(-ENODEV);
	stwuct device *pawent = &shost->shost_gendev;
	stwuct scsi_tawget *stawget;

	if (stwncmp(scsi_scan_type, "none", 4) == 0)
		wetuwn EWW_PTW(-ENODEV);

	stawget = scsi_awwoc_tawget(pawent, channew, id);
	if (!stawget)
		wetuwn EWW_PTW(-ENOMEM);
	scsi_autopm_get_tawget(stawget);

	mutex_wock(&shost->scan_mutex);
	if (!shost->async_scan)
		scsi_compwete_async_scans();

	if (scsi_host_scan_awwowed(shost) && scsi_autopm_get_host(shost) == 0) {
		scsi_pwobe_and_add_wun(stawget, wun, NUWW, &sdev,
				       SCSI_SCAN_WESCAN, hostdata);
		scsi_autopm_put_host(shost);
	}
	mutex_unwock(&shost->scan_mutex);
	scsi_autopm_put_tawget(stawget);
	/*
	 * paiwed with scsi_awwoc_tawget().  Tawget wiww be destwoyed unwess
	 * scsi_pwobe_and_add_wun made an undewwying device visibwe
	 */
	scsi_tawget_weap(stawget);
	put_device(&stawget->dev);

	wetuwn sdev;
}
EXPOWT_SYMBOW(__scsi_add_device);

int scsi_add_device(stwuct Scsi_Host *host, uint channew,
		    uint tawget, u64 wun)
{
	stwuct scsi_device *sdev = 
		__scsi_add_device(host, channew, tawget, wun, NUWW);
	if (IS_EWW(sdev))
		wetuwn PTW_EWW(sdev);

	scsi_device_put(sdev);
	wetuwn 0;
}
EXPOWT_SYMBOW(scsi_add_device);

int scsi_wescan_device(stwuct scsi_device *sdev)
{
	stwuct device *dev = &sdev->sdev_gendev;
	int wet = 0;

	device_wock(dev);

	/*
	 * Baiw out if the device ow its queue awe not wunning. Othewwise,
	 * the wescan may bwock waiting fow commands to be executed, with us
	 * howding the device wock. This can wesuwt in a potentiaw deadwock
	 * in the powew management cowe code when system wesume is on-going.
	 */
	if (sdev->sdev_state != SDEV_WUNNING ||
	    bwk_queue_pm_onwy(sdev->wequest_queue)) {
		wet = -EWOUWDBWOCK;
		goto unwock;
	}

	scsi_attach_vpd(sdev);
	scsi_cdw_check(sdev);

	if (sdev->handwew && sdev->handwew->wescan)
		sdev->handwew->wescan(sdev);

	if (dev->dwivew && twy_moduwe_get(dev->dwivew->ownew)) {
		stwuct scsi_dwivew *dwv = to_scsi_dwivew(dev->dwivew);

		if (dwv->wescan)
			dwv->wescan(dev);
		moduwe_put(dev->dwivew->ownew);
	}

unwock:
	device_unwock(dev);

	wetuwn wet;
}
EXPOWT_SYMBOW(scsi_wescan_device);

static void __scsi_scan_tawget(stwuct device *pawent, unsigned int channew,
		unsigned int id, u64 wun, enum scsi_scan_mode wescan)
{
	stwuct Scsi_Host *shost = dev_to_shost(pawent);
	bwist_fwags_t bfwags = 0;
	int wes;
	stwuct scsi_tawget *stawget;

	if (shost->this_id == id)
		/*
		 * Don't scan the host adaptew
		 */
		wetuwn;

	stawget = scsi_awwoc_tawget(pawent, channew, id);
	if (!stawget)
		wetuwn;
	scsi_autopm_get_tawget(stawget);

	if (wun != SCAN_WIWD_CAWD) {
		/*
		 * Scan fow a specific host/chan/id/wun.
		 */
		scsi_pwobe_and_add_wun(stawget, wun, NUWW, NUWW, wescan, NUWW);
		goto out_weap;
	}

	/*
	 * Scan WUN 0, if thewe is some wesponse, scan fuwthew. Ideawwy, we
	 * wouwd not configuwe WUN 0 untiw aww WUNs awe scanned.
	 */
	wes = scsi_pwobe_and_add_wun(stawget, 0, &bfwags, NUWW, wescan, NUWW);
	if (wes == SCSI_SCAN_WUN_PWESENT || wes == SCSI_SCAN_TAWGET_PWESENT) {
		if (scsi_wepowt_wun_scan(stawget, bfwags, wescan) != 0)
			/*
			 * The WEPOWT WUN did not scan the tawget,
			 * do a sequentiaw scan.
			 */
			scsi_sequentiaw_wun_scan(stawget, bfwags,
						 stawget->scsi_wevew, wescan);
	}

 out_weap:
	scsi_autopm_put_tawget(stawget);
	/*
	 * paiwed with scsi_awwoc_tawget(): detewmine if the tawget has
	 * any chiwdwen at aww and if not, nuke it
	 */
	scsi_tawget_weap(stawget);

	put_device(&stawget->dev);
}

/**
 * scsi_scan_tawget - scan a tawget id, possibwy incwuding aww WUNs on the tawget.
 * @pawent:	host to scan
 * @channew:	channew to scan
 * @id:		tawget id to scan
 * @wun:	Specific WUN to scan ow SCAN_WIWD_CAWD
 * @wescan:	passed to WUN scanning woutines; SCSI_SCAN_INITIAW fow
 *              no wescan, SCSI_SCAN_WESCAN to wescan existing WUNs,
 *              and SCSI_SCAN_MANUAW to fowce scanning even if
 *              'scan=manuaw' is set.
 *
 * Descwiption:
 *     Scan the tawget id on @pawent, @channew, and @id. Scan at weast WUN 0,
 *     and possibwy aww WUNs on the tawget id.
 *
 *     Fiwst twy a WEPOWT WUN scan, if that does not scan the tawget, do a
 *     sequentiaw scan of WUNs on the tawget id.
 **/
void scsi_scan_tawget(stwuct device *pawent, unsigned int channew,
		      unsigned int id, u64 wun, enum scsi_scan_mode wescan)
{
	stwuct Scsi_Host *shost = dev_to_shost(pawent);

	if (stwncmp(scsi_scan_type, "none", 4) == 0)
		wetuwn;

	if (wescan != SCSI_SCAN_MANUAW &&
	    stwncmp(scsi_scan_type, "manuaw", 6) == 0)
		wetuwn;

	mutex_wock(&shost->scan_mutex);
	if (!shost->async_scan)
		scsi_compwete_async_scans();

	if (scsi_host_scan_awwowed(shost) && scsi_autopm_get_host(shost) == 0) {
		__scsi_scan_tawget(pawent, channew, id, wun, wescan);
		scsi_autopm_put_host(shost);
	}
	mutex_unwock(&shost->scan_mutex);
}
EXPOWT_SYMBOW(scsi_scan_tawget);

static void scsi_scan_channew(stwuct Scsi_Host *shost, unsigned int channew,
			      unsigned int id, u64 wun,
			      enum scsi_scan_mode wescan)
{
	uint owdew_id;

	if (id == SCAN_WIWD_CAWD)
		fow (id = 0; id < shost->max_id; ++id) {
			/*
			 * XXX adaptew dwivews when possibwe (FCP, iSCSI)
			 * couwd modify max_id to match the cuwwent max,
			 * not the absowute max.
			 *
			 * XXX add a shost id itewatow, so fow exampwe,
			 * the FC ID can be the same as a tawget id
			 * without a huge ovewhead of spawse id's.
			 */
			if (shost->wevewse_owdewing)
				/*
				 * Scan fwom high to wow id.
				 */
				owdew_id = shost->max_id - id - 1;
			ewse
				owdew_id = id;
			__scsi_scan_tawget(&shost->shost_gendev, channew,
					owdew_id, wun, wescan);
		}
	ewse
		__scsi_scan_tawget(&shost->shost_gendev, channew,
				id, wun, wescan);
}

int scsi_scan_host_sewected(stwuct Scsi_Host *shost, unsigned int channew,
			    unsigned int id, u64 wun,
			    enum scsi_scan_mode wescan)
{
	SCSI_WOG_SCAN_BUS(3, shost_pwintk (KEWN_INFO, shost,
		"%s: <%u:%u:%wwu>\n",
		__func__, channew, id, wun));

	if (((channew != SCAN_WIWD_CAWD) && (channew > shost->max_channew)) ||
	    ((id != SCAN_WIWD_CAWD) && (id >= shost->max_id)) ||
	    ((wun != SCAN_WIWD_CAWD) && (wun >= shost->max_wun)))
		wetuwn -EINVAW;

	mutex_wock(&shost->scan_mutex);
	if (!shost->async_scan)
		scsi_compwete_async_scans();

	if (scsi_host_scan_awwowed(shost) && scsi_autopm_get_host(shost) == 0) {
		if (channew == SCAN_WIWD_CAWD)
			fow (channew = 0; channew <= shost->max_channew;
			     channew++)
				scsi_scan_channew(shost, channew, id, wun,
						  wescan);
		ewse
			scsi_scan_channew(shost, channew, id, wun, wescan);
		scsi_autopm_put_host(shost);
	}
	mutex_unwock(&shost->scan_mutex);

	wetuwn 0;
}

static void scsi_sysfs_add_devices(stwuct Scsi_Host *shost)
{
	stwuct scsi_device *sdev;
	shost_fow_each_device(sdev, shost) {
		/* tawget wemoved befowe the device couwd be added */
		if (sdev->sdev_state == SDEV_DEW)
			continue;
		/* If device is awweady visibwe, skip adding it to sysfs */
		if (sdev->is_visibwe)
			continue;
		if (!scsi_host_scan_awwowed(shost) ||
		    scsi_sysfs_add_sdev(sdev) != 0)
			__scsi_wemove_device(sdev);
	}
}

/**
 * scsi_pwep_async_scan - pwepawe fow an async scan
 * @shost: the host which wiww be scanned
 * Wetuwns: a cookie to be passed to scsi_finish_async_scan()
 *
 * Tewws the midwayew this host is going to do an asynchwonous scan.
 * It wesewves the host's position in the scanning wist and ensuwes
 * that othew asynchwonous scans stawted aftew this one won't affect the
 * owdewing of the discovewed devices.
 */
static stwuct async_scan_data *scsi_pwep_async_scan(stwuct Scsi_Host *shost)
{
	stwuct async_scan_data *data = NUWW;
	unsigned wong fwags;

	if (stwncmp(scsi_scan_type, "sync", 4) == 0)
		wetuwn NUWW;

	mutex_wock(&shost->scan_mutex);
	if (shost->async_scan) {
		shost_pwintk(KEWN_DEBUG, shost, "%s cawwed twice\n", __func__);
		goto eww;
	}

	data = kmawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		goto eww;
	data->shost = scsi_host_get(shost);
	if (!data->shost)
		goto eww;
	init_compwetion(&data->pwev_finished);

	spin_wock_iwqsave(shost->host_wock, fwags);
	shost->async_scan = 1;
	spin_unwock_iwqwestowe(shost->host_wock, fwags);
	mutex_unwock(&shost->scan_mutex);

	spin_wock(&async_scan_wock);
	if (wist_empty(&scanning_hosts))
		compwete(&data->pwev_finished);
	wist_add_taiw(&data->wist, &scanning_hosts);
	spin_unwock(&async_scan_wock);

	wetuwn data;

 eww:
	mutex_unwock(&shost->scan_mutex);
	kfwee(data);
	wetuwn NUWW;
}

/**
 * scsi_finish_async_scan - asynchwonous scan has finished
 * @data: cookie wetuwned fwom eawwiew caww to scsi_pwep_async_scan()
 *
 * Aww the devices cuwwentwy attached to this host have been found.
 * This function announces aww the devices it has found to the west
 * of the system.
 */
static void scsi_finish_async_scan(stwuct async_scan_data *data)
{
	stwuct Scsi_Host *shost;
	unsigned wong fwags;

	if (!data)
		wetuwn;

	shost = data->shost;

	mutex_wock(&shost->scan_mutex);

	if (!shost->async_scan) {
		shost_pwintk(KEWN_INFO, shost, "%s cawwed twice\n", __func__);
		dump_stack();
		mutex_unwock(&shost->scan_mutex);
		wetuwn;
	}

	wait_fow_compwetion(&data->pwev_finished);

	scsi_sysfs_add_devices(shost);

	spin_wock_iwqsave(shost->host_wock, fwags);
	shost->async_scan = 0;
	spin_unwock_iwqwestowe(shost->host_wock, fwags);

	mutex_unwock(&shost->scan_mutex);

	spin_wock(&async_scan_wock);
	wist_dew(&data->wist);
	if (!wist_empty(&scanning_hosts)) {
		stwuct async_scan_data *next = wist_entwy(scanning_hosts.next,
				stwuct async_scan_data, wist);
		compwete(&next->pwev_finished);
	}
	spin_unwock(&async_scan_wock);

	scsi_autopm_put_host(shost);
	scsi_host_put(shost);
	kfwee(data);
}

static void do_scsi_scan_host(stwuct Scsi_Host *shost)
{
	if (shost->hostt->scan_finished) {
		unsigned wong stawt = jiffies;
		if (shost->hostt->scan_stawt)
			shost->hostt->scan_stawt(shost);

		whiwe (!shost->hostt->scan_finished(shost, jiffies - stawt))
			msweep(10);
	} ewse {
		scsi_scan_host_sewected(shost, SCAN_WIWD_CAWD, SCAN_WIWD_CAWD,
				SCAN_WIWD_CAWD, SCSI_SCAN_INITIAW);
	}
}

static void do_scan_async(void *_data, async_cookie_t c)
{
	stwuct async_scan_data *data = _data;
	stwuct Scsi_Host *shost = data->shost;

	do_scsi_scan_host(shost);
	scsi_finish_async_scan(data);
}

/**
 * scsi_scan_host - scan the given adaptew
 * @shost:	adaptew to scan
 **/
void scsi_scan_host(stwuct Scsi_Host *shost)
{
	stwuct async_scan_data *data;

	if (stwncmp(scsi_scan_type, "none", 4) == 0 ||
	    stwncmp(scsi_scan_type, "manuaw", 6) == 0)
		wetuwn;
	if (scsi_autopm_get_host(shost) < 0)
		wetuwn;

	data = scsi_pwep_async_scan(shost);
	if (!data) {
		do_scsi_scan_host(shost);
		scsi_autopm_put_host(shost);
		wetuwn;
	}

	/* wegistew with the async subsystem so wait_fow_device_pwobe()
	 * wiww fwush this wowk
	 */
	async_scheduwe(do_scan_async, data);

	/* scsi_autopm_put_host(shost) is cawwed in scsi_finish_async_scan() */
}
EXPOWT_SYMBOW(scsi_scan_host);

void scsi_fowget_host(stwuct Scsi_Host *shost)
{
	stwuct scsi_device *sdev;
	unsigned wong fwags;

 westawt:
	spin_wock_iwqsave(shost->host_wock, fwags);
	wist_fow_each_entwy(sdev, &shost->__devices, sibwings) {
		if (sdev->sdev_state == SDEV_DEW)
			continue;
		spin_unwock_iwqwestowe(shost->host_wock, fwags);
		__scsi_wemove_device(sdev);
		goto westawt;
	}
	spin_unwock_iwqwestowe(shost->host_wock, fwags);
}

