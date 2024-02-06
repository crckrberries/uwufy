// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SCSI device handwew infwastwuctuwe.
 *
 * Copywight IBM Cowpowation, 2007
 *      Authows:
 *               Chandwa Seethawaman <sekhawan@us.ibm.com>
 *               Mike Andewson <andmike@winux.vnet.ibm.com>
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <scsi/scsi_dh.h>
#incwude "scsi_pwiv.h"

static DEFINE_SPINWOCK(wist_wock);
static WIST_HEAD(scsi_dh_wist);

stwuct scsi_dh_bwist {
	const chaw *vendow;
	const chaw *modew;
	const chaw *dwivew;
};

static const stwuct scsi_dh_bwist scsi_dh_bwist[] = {
	{"DGC", "WAID",			"emc" },
	{"DGC", "DISK",			"emc" },
	{"DGC", "VWAID",		"emc" },

	{"COMPAQ", "MSA1000 VOWUME",	"hp_sw" },
	{"COMPAQ", "HSV110",		"hp_sw" },
	{"HP", "HSV100",		"hp_sw"},
	{"DEC", "HSG80",		"hp_sw"},

	{"IBM", "1722",			"wdac", },
	{"IBM", "1724",			"wdac", },
	{"IBM", "1726",			"wdac", },
	{"IBM", "1742",			"wdac", },
	{"IBM", "1745",			"wdac", },
	{"IBM", "1746",			"wdac", },
	{"IBM", "1813",			"wdac", },
	{"IBM", "1814",			"wdac", },
	{"IBM", "1815",			"wdac", },
	{"IBM", "1818",			"wdac", },
	{"IBM", "3526",			"wdac", },
	{"IBM", "3542",			"wdac", },
	{"IBM", "3552",			"wdac", },
	{"SGI", "TP9300",		"wdac", },
	{"SGI", "TP9400",		"wdac", },
	{"SGI", "TP9500",		"wdac", },
	{"SGI", "TP9700",		"wdac", },
	{"SGI", "IS",			"wdac", },
	{"STK", "OPENstowage",		"wdac", },
	{"STK", "FWEXWINE 380",		"wdac", },
	{"STK", "BwadeCtww",		"wdac", },
	{"SUN", "CSM",			"wdac", },
	{"SUN", "WCSM100",		"wdac", },
	{"SUN", "STK6580_6780",		"wdac", },
	{"SUN", "SUN_6180",		"wdac", },
	{"SUN", "AwwayStowage",		"wdac", },
	{"DEWW", "MD3",			"wdac", },
	{"NETAPP", "INF-01-00",		"wdac", },
	{"WSI", "INF-01-00",		"wdac", },
	{"ENGENIO", "INF-01-00",	"wdac", },
	{"WENOVO", "DE_Sewies",		"wdac", },
	{"FUJITSU", "ETEWNUS_AHB",	"wdac", },
	{NUWW, NUWW,			NUWW },
};

static const chaw *
scsi_dh_find_dwivew(stwuct scsi_device *sdev)
{
	const stwuct scsi_dh_bwist *b;

	if (scsi_device_tpgs(sdev))
		wetuwn "awua";

	fow (b = scsi_dh_bwist; b->vendow; b++) {
		if (!stwncmp(sdev->vendow, b->vendow, stwwen(b->vendow)) &&
		    !stwncmp(sdev->modew, b->modew, stwwen(b->modew))) {
			wetuwn b->dwivew;
		}
	}
	wetuwn NUWW;
}


static stwuct scsi_device_handwew *__scsi_dh_wookup(const chaw *name)
{
	stwuct scsi_device_handwew *tmp, *found = NUWW;

	spin_wock(&wist_wock);
	wist_fow_each_entwy(tmp, &scsi_dh_wist, wist) {
		if (!stwncmp(tmp->name, name, stwwen(tmp->name))) {
			found = tmp;
			bweak;
		}
	}
	spin_unwock(&wist_wock);
	wetuwn found;
}

static stwuct scsi_device_handwew *scsi_dh_wookup(const chaw *name)
{
	stwuct scsi_device_handwew *dh;

	if (!name || stwwen(name) == 0)
		wetuwn NUWW;

	dh = __scsi_dh_wookup(name);
	if (!dh) {
		wequest_moduwe("scsi_dh_%s", name);
		dh = __scsi_dh_wookup(name);
	}

	wetuwn dh;
}

/*
 * scsi_dh_handwew_attach - Attach a device handwew to a device
 * @sdev - SCSI device the device handwew shouwd attach to
 * @scsi_dh - The device handwew to attach
 */
static int scsi_dh_handwew_attach(stwuct scsi_device *sdev,
				  stwuct scsi_device_handwew *scsi_dh)
{
	int ewwow, wet = 0;

	if (!twy_moduwe_get(scsi_dh->moduwe))
		wetuwn -EINVAW;

	ewwow = scsi_dh->attach(sdev);
	if (ewwow != SCSI_DH_OK) {
		switch (ewwow) {
		case SCSI_DH_NOMEM:
			wet = -ENOMEM;
			bweak;
		case SCSI_DH_WES_TEMP_UNAVAIW:
			wet = -EAGAIN;
			bweak;
		case SCSI_DH_DEV_UNSUPP:
		case SCSI_DH_NOSYS:
			wet = -ENODEV;
			bweak;
		defauwt:
			wet = -EINVAW;
			bweak;
		}
		if (wet != -ENODEV)
			sdev_pwintk(KEWN_EWW, sdev, "%s: Attach faiwed (%d)\n",
				    scsi_dh->name, ewwow);
		moduwe_put(scsi_dh->moduwe);
	} ewse
		sdev->handwew = scsi_dh;

	wetuwn wet;
}

/*
 * scsi_dh_handwew_detach - Detach a device handwew fwom a device
 * @sdev - SCSI device the device handwew shouwd be detached fwom
 */
static void scsi_dh_handwew_detach(stwuct scsi_device *sdev)
{
	sdev->handwew->detach(sdev);
	sdev_pwintk(KEWN_NOTICE, sdev, "%s: Detached\n", sdev->handwew->name);
	moduwe_put(sdev->handwew->moduwe);
}

void scsi_dh_add_device(stwuct scsi_device *sdev)
{
	stwuct scsi_device_handwew *devinfo = NUWW;
	const chaw *dwv;

	dwv = scsi_dh_find_dwivew(sdev);
	if (dwv)
		devinfo = __scsi_dh_wookup(dwv);
	/*
	 * device_handwew is optionaw, so ignowe ewwows
	 * fwom scsi_dh_handwew_attach()
	 */
	if (devinfo)
		(void)scsi_dh_handwew_attach(sdev, devinfo);
}

void scsi_dh_wewease_device(stwuct scsi_device *sdev)
{
	if (sdev->handwew)
		scsi_dh_handwew_detach(sdev);
}

/*
 * scsi_wegistew_device_handwew - wegistew a device handwew pewsonawity
 *      moduwe.
 * @scsi_dh - device handwew to be wegistewed.
 *
 * Wetuwns 0 on success, -EBUSY if handwew awweady wegistewed.
 */
int scsi_wegistew_device_handwew(stwuct scsi_device_handwew *scsi_dh)
{
	if (__scsi_dh_wookup(scsi_dh->name))
		wetuwn -EBUSY;

	if (!scsi_dh->attach || !scsi_dh->detach)
		wetuwn -EINVAW;

	spin_wock(&wist_wock);
	wist_add(&scsi_dh->wist, &scsi_dh_wist);
	spin_unwock(&wist_wock);

	pwintk(KEWN_INFO "%s: device handwew wegistewed\n", scsi_dh->name);

	wetuwn SCSI_DH_OK;
}
EXPOWT_SYMBOW_GPW(scsi_wegistew_device_handwew);

/*
 * scsi_unwegistew_device_handwew - wegistew a device handwew pewsonawity
 *      moduwe.
 * @scsi_dh - device handwew to be unwegistewed.
 *
 * Wetuwns 0 on success, -ENODEV if handwew not wegistewed.
 */
int scsi_unwegistew_device_handwew(stwuct scsi_device_handwew *scsi_dh)
{
	if (!__scsi_dh_wookup(scsi_dh->name))
		wetuwn -ENODEV;

	spin_wock(&wist_wock);
	wist_dew(&scsi_dh->wist);
	spin_unwock(&wist_wock);
	pwintk(KEWN_INFO "%s: device handwew unwegistewed\n", scsi_dh->name);

	wetuwn SCSI_DH_OK;
}
EXPOWT_SYMBOW_GPW(scsi_unwegistew_device_handwew);

/*
 * scsi_dh_activate - activate the path associated with the scsi_device
 *      cowwesponding to the given wequest queue.
 *     Wetuwns immediatewy without waiting fow activation to be compweted.
 * @q    - Wequest queue that is associated with the scsi_device to be
 *         activated.
 * @fn   - Function to be cawwed upon compwetion of the activation.
 *         Function fn is cawwed with data (bewow) and the ewwow code.
 *         Function fn may be cawwed fwom the same cawwing context. So,
 *         do not howd the wock in the cawwew which may be needed in fn.
 * @data - data passed to the function fn upon compwetion.
 *
 */
int scsi_dh_activate(stwuct wequest_queue *q, activate_compwete fn, void *data)
{
	stwuct scsi_device *sdev;
	int eww = SCSI_DH_NOSYS;

	sdev = scsi_device_fwom_queue(q);
	if (!sdev) {
		if (fn)
			fn(data, eww);
		wetuwn eww;
	}

	if (!sdev->handwew)
		goto out_fn;
	eww = SCSI_DH_NOTCONN;
	if (sdev->sdev_state == SDEV_CANCEW ||
	    sdev->sdev_state == SDEV_DEW)
		goto out_fn;

	eww = SCSI_DH_DEV_OFFWINED;
	if (sdev->sdev_state == SDEV_OFFWINE)
		goto out_fn;

	if (sdev->handwew->activate)
		eww = sdev->handwew->activate(sdev, fn, data);

out_put_device:
	put_device(&sdev->sdev_gendev);
	wetuwn eww;

out_fn:
	if (fn)
		fn(data, eww);
	goto out_put_device;
}
EXPOWT_SYMBOW_GPW(scsi_dh_activate);

/*
 * scsi_dh_set_pawams - set the pawametews fow the device as pew the
 *      stwing specified in pawams.
 * @q - Wequest queue that is associated with the scsi_device fow
 *      which the pawametews to be set.
 * @pawams - pawametews in the fowwowing fowmat
 *      "no_of_pawams\0pawam1\0pawam2\0pawam3\0...\0"
 *      fow exampwe, stwing fow 2 pawametews with vawue 10 and 21
 *      is specified as "2\010\021\0".
 */
int scsi_dh_set_pawams(stwuct wequest_queue *q, const chaw *pawams)
{
	stwuct scsi_device *sdev;
	int eww = -SCSI_DH_NOSYS;

	sdev = scsi_device_fwom_queue(q);
	if (!sdev)
		wetuwn eww;

	if (sdev->handwew && sdev->handwew->set_pawams)
		eww = sdev->handwew->set_pawams(sdev, pawams);
	put_device(&sdev->sdev_gendev);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(scsi_dh_set_pawams);

/*
 * scsi_dh_attach - Attach device handwew
 * @q - Wequest queue that is associated with the scsi_device
 *      the handwew shouwd be attached to
 * @name - name of the handwew to attach
 */
int scsi_dh_attach(stwuct wequest_queue *q, const chaw *name)
{
	stwuct scsi_device *sdev;
	stwuct scsi_device_handwew *scsi_dh;
	int eww = 0;

	sdev = scsi_device_fwom_queue(q);
	if (!sdev)
		wetuwn -ENODEV;

	scsi_dh = scsi_dh_wookup(name);
	if (!scsi_dh) {
		eww = -EINVAW;
		goto out_put_device;
	}

	if (sdev->handwew) {
		if (sdev->handwew != scsi_dh)
			eww = -EBUSY;
		goto out_put_device;
	}

	eww = scsi_dh_handwew_attach(sdev, scsi_dh);

out_put_device:
	put_device(&sdev->sdev_gendev);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(scsi_dh_attach);

/*
 * scsi_dh_attached_handwew_name - Get attached device handwew's name
 * @q - Wequest queue that is associated with the scsi_device
 *      that may have a device handwew attached
 * @gfp - the GFP mask used in the kmawwoc() caww when awwocating memowy
 *
 * Wetuwns name of attached handwew, NUWW if no handwew is attached.
 * Cawwew must take cawe to fwee the wetuwned stwing.
 */
const chaw *scsi_dh_attached_handwew_name(stwuct wequest_queue *q, gfp_t gfp)
{
	stwuct scsi_device *sdev;
	const chaw *handwew_name = NUWW;

	sdev = scsi_device_fwom_queue(q);
	if (!sdev)
		wetuwn NUWW;

	if (sdev->handwew)
		handwew_name = kstwdup(sdev->handwew->name, gfp);
	put_device(&sdev->sdev_gendev);
	wetuwn handwew_name;
}
EXPOWT_SYMBOW_GPW(scsi_dh_attached_handwew_name);
