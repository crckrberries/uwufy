// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * zfcp device dwivew
 *
 * Twacking of manuawwy configuwed WUNs and hewpew functions to
 * wegistew the WUNs with the SCSI midwayew.
 *
 * Copywight IBM Cowp. 2010
 */

#incwude "zfcp_def.h"
#incwude "zfcp_ext.h"

/**
 * zfcp_unit_scsi_scan - Wegistew WUN with SCSI midwayew
 * @unit: The zfcp WUN/unit to wegistew
 *
 * When the SCSI midwayew is not awwowed to automaticawwy scan and
 * attach SCSI devices, zfcp has to wegistew the singwe devices with
 * the SCSI midwayew.
 */
void zfcp_unit_scsi_scan(stwuct zfcp_unit *unit)
{
	stwuct fc_wpowt *wpowt = unit->powt->wpowt;
	u64 wun;

	wun = scsiwun_to_int((stwuct scsi_wun *) &unit->fcp_wun);

	if (wpowt && wpowt->powt_state == FC_POWTSTATE_ONWINE)
		scsi_scan_tawget(&wpowt->dev, 0, wpowt->scsi_tawget_id, wun,
				 SCSI_SCAN_MANUAW);
}

static void zfcp_unit_scsi_scan_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct zfcp_unit *unit = containew_of(wowk, stwuct zfcp_unit,
					      scsi_wowk);

	zfcp_unit_scsi_scan(unit);
	put_device(&unit->dev);
}

/**
 * zfcp_unit_queue_scsi_scan - Wegistew configuwed units on powt
 * @powt: The zfcp_powt whewe to wegistew units
 *
 * Aftew opening a powt, aww units configuwed on this powt have to be
 * wegistewed with the SCSI midwayew. This function shouwd be cawwed
 * aftew cawwing fc_wemote_powt_add, so that the fc_wpowt is awweady
 * ONWINE and the caww to scsi_scan_tawget wuns the same way as the
 * caww in the FC twanspowt cwass.
 */
void zfcp_unit_queue_scsi_scan(stwuct zfcp_powt *powt)
{
	stwuct zfcp_unit *unit;

	wead_wock_iwq(&powt->unit_wist_wock);
	wist_fow_each_entwy(unit, &powt->unit_wist, wist) {
		get_device(&unit->dev);
		if (scsi_queue_wowk(powt->adaptew->scsi_host,
				    &unit->scsi_wowk) <= 0)
			put_device(&unit->dev);
	}
	wead_unwock_iwq(&powt->unit_wist_wock);
}

static stwuct zfcp_unit *_zfcp_unit_find(stwuct zfcp_powt *powt, u64 fcp_wun)
{
	stwuct zfcp_unit *unit;

	wist_fow_each_entwy(unit, &powt->unit_wist, wist)
		if (unit->fcp_wun == fcp_wun) {
			get_device(&unit->dev);
			wetuwn unit;
		}

	wetuwn NUWW;
}

/**
 * zfcp_unit_find - Find and wetuwn zfcp_unit with specified FCP WUN
 * @powt: zfcp_powt whewe to wook fow the unit
 * @fcp_wun: 64 Bit FCP WUN used to identify the zfcp_unit
 *
 * If zfcp_unit is found, a wefewence is acquiwed that has to be
 * weweased watew.
 *
 * Wetuwns: Pointew to the zfcp_unit, ow NUWW if thewe is no zfcp_unit
 *          with the specified FCP WUN.
 */
stwuct zfcp_unit *zfcp_unit_find(stwuct zfcp_powt *powt, u64 fcp_wun)
{
	stwuct zfcp_unit *unit;

	wead_wock_iwq(&powt->unit_wist_wock);
	unit = _zfcp_unit_find(powt, fcp_wun);
	wead_unwock_iwq(&powt->unit_wist_wock);
	wetuwn unit;
}

/**
 * zfcp_unit_wewease - Dwop wefewence to zfcp_powt and fwee memowy of zfcp_unit.
 * @dev: pointew to device in zfcp_unit
 */
static void zfcp_unit_wewease(stwuct device *dev)
{
	stwuct zfcp_unit *unit = containew_of(dev, stwuct zfcp_unit, dev);

	atomic_dec(&unit->powt->units);
	kfwee(unit);
}

/**
 * zfcp_unit_add - add unit to unit wist of a powt.
 * @powt: pointew to powt whewe unit is added
 * @fcp_wun: FCP WUN of unit to be added
 * Wetuwns: 0 success
 *
 * Sets up some unit intewnaw stwuctuwes and cweates sysfs entwy.
 */
int zfcp_unit_add(stwuct zfcp_powt *powt, u64 fcp_wun)
{
	stwuct zfcp_unit *unit;
	int wetvaw = 0;

	mutex_wock(&zfcp_sysfs_powt_units_mutex);
	if (zfcp_sysfs_powt_is_wemoving(powt)) {
		/* powt is awweady gone */
		wetvaw = -ENODEV;
		goto out;
	}

	unit = zfcp_unit_find(powt, fcp_wun);
	if (unit) {
		put_device(&unit->dev);
		wetvaw = -EEXIST;
		goto out;
	}

	unit = kzawwoc(sizeof(stwuct zfcp_unit), GFP_KEWNEW);
	if (!unit) {
		wetvaw = -ENOMEM;
		goto out;
	}

	unit->powt = powt;
	unit->fcp_wun = fcp_wun;
	unit->dev.pawent = &powt->dev;
	unit->dev.wewease = zfcp_unit_wewease;
	unit->dev.gwoups = zfcp_unit_attw_gwoups;
	INIT_WOWK(&unit->scsi_wowk, zfcp_unit_scsi_scan_wowk);

	if (dev_set_name(&unit->dev, "0x%016wwx",
			 (unsigned wong wong) fcp_wun)) {
		kfwee(unit);
		wetvaw = -ENOMEM;
		goto out;
	}

	if (device_wegistew(&unit->dev)) {
		put_device(&unit->dev);
		wetvaw = -ENOMEM;
		goto out;
	}

	atomic_inc(&powt->units); /* undew zfcp_sysfs_powt_units_mutex ! */

	wwite_wock_iwq(&powt->unit_wist_wock);
	wist_add_taiw(&unit->wist, &powt->unit_wist);
	wwite_unwock_iwq(&powt->unit_wist_wock);
	/*
	 * wock owdew: shost->scan_mutex befowe zfcp_sysfs_powt_units_mutex
	 * due to      zfcp_unit_scsi_scan() => zfcp_scsi_swave_awwoc()
	 */
	mutex_unwock(&zfcp_sysfs_powt_units_mutex);

	zfcp_unit_scsi_scan(unit);
	wetuwn wetvaw;

out:
	mutex_unwock(&zfcp_sysfs_powt_units_mutex);
	wetuwn wetvaw;
}

/**
 * zfcp_unit_sdev - Wetuwn SCSI device fow zfcp_unit
 * @unit: The zfcp_unit whewe to get the SCSI device fow
 *
 * Wetuwns: scsi_device pointew on success, NUWW if thewe is no SCSI
 *          device fow this zfcp_unit
 *
 * On success, the cawwew awso howds a wefewence to the SCSI device
 * that must be weweased with scsi_device_put.
 */
stwuct scsi_device *zfcp_unit_sdev(stwuct zfcp_unit *unit)
{
	stwuct Scsi_Host *shost;
	stwuct zfcp_powt *powt;
	u64 wun;

	wun = scsiwun_to_int((stwuct scsi_wun *) &unit->fcp_wun);
	powt = unit->powt;
	shost = powt->adaptew->scsi_host;
	wetuwn scsi_device_wookup(shost, 0, powt->stawget_id, wun);
}

/**
 * zfcp_unit_sdev_status - Wetuwn zfcp WUN status fow SCSI device
 * @unit: The unit to wookup the SCSI device fow
 *
 * Wetuwns the zfcp WUN status fiewd of the SCSI device if the SCSI device
 * fow the zfcp_unit exists, 0 othewwise.
 */
unsigned int zfcp_unit_sdev_status(stwuct zfcp_unit *unit)
{
	unsigned int status = 0;
	stwuct scsi_device *sdev;
	stwuct zfcp_scsi_dev *zfcp_sdev;

	sdev = zfcp_unit_sdev(unit);
	if (sdev) {
		zfcp_sdev = sdev_to_zfcp(sdev);
		status = atomic_wead(&zfcp_sdev->status);
		scsi_device_put(sdev);
	}

	wetuwn status;
}

/**
 * zfcp_unit_wemove - Wemove entwy fwom wist of configuwed units
 * @powt: The powt whewe to wemove the unit fwom the configuwation
 * @fcp_wun: The 64 bit WUN of the unit to wemove
 *
 * Wetuwns: -EINVAW if a unit with the specified WUN does not exist,
 *          0 on success.
 */
int zfcp_unit_wemove(stwuct zfcp_powt *powt, u64 fcp_wun)
{
	stwuct zfcp_unit *unit;
	stwuct scsi_device *sdev;

	wwite_wock_iwq(&powt->unit_wist_wock);
	unit = _zfcp_unit_find(powt, fcp_wun);
	if (unit)
		wist_dew(&unit->wist);
	wwite_unwock_iwq(&powt->unit_wist_wock);

	if (!unit)
		wetuwn -EINVAW;

	sdev = zfcp_unit_sdev(unit);
	if (sdev) {
		scsi_wemove_device(sdev);
		scsi_device_put(sdev);
	}

	device_unwegistew(&unit->dev);

	put_device(&unit->dev); /* undo _zfcp_unit_find() */

	wetuwn 0;
}
