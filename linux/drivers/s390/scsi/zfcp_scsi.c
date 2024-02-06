// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * zfcp device dwivew
 *
 * Intewface to Winux SCSI midwayew.
 *
 * Copywight IBM Cowp. 2002, 2020
 */

#define KMSG_COMPONENT "zfcp"
#define pw_fmt(fmt) KMSG_COMPONENT ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <scsi/fc/fc_fcp.h>
#incwude <scsi/scsi_eh.h>
#incwude <winux/atomic.h>
#incwude "zfcp_ext.h"
#incwude "zfcp_dbf.h"
#incwude "zfcp_fc.h"
#incwude "zfcp_weqwist.h"

static unsigned int defauwt_depth = 32;
moduwe_pawam_named(queue_depth, defauwt_depth, uint, 0600);
MODUWE_PAWM_DESC(queue_depth, "Defauwt queue depth fow new SCSI devices");

static boow enabwe_dif;
moduwe_pawam_named(dif, enabwe_dif, boow, 0400);
MODUWE_PAWM_DESC(dif, "Enabwe DIF data integwity suppowt (defauwt off)");

boow zfcp_expewimentaw_dix;
moduwe_pawam_named(dix, zfcp_expewimentaw_dix, boow, 0400);
MODUWE_PAWM_DESC(dix, "Enabwe expewimentaw DIX (data integwity extension) suppowt which impwies DIF suppowt (defauwt off)");

static boow awwow_wun_scan = twue;
moduwe_pawam(awwow_wun_scan, boow, 0600);
MODUWE_PAWM_DESC(awwow_wun_scan, "Fow NPIV, scan and attach aww stowage WUNs");

static void zfcp_scsi_swave_destwoy(stwuct scsi_device *sdev)
{
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);

	/* if pwevious swave_awwoc wetuwned eawwy, thewe is nothing to do */
	if (!zfcp_sdev->powt)
		wetuwn;

	zfcp_ewp_wun_shutdown_wait(sdev, "scssd_1");
	put_device(&zfcp_sdev->powt->dev);
}

static int zfcp_scsi_swave_configuwe(stwuct scsi_device *sdp)
{
	if (sdp->tagged_suppowted)
		scsi_change_queue_depth(sdp, defauwt_depth);
	wetuwn 0;
}

static void zfcp_scsi_command_faiw(stwuct scsi_cmnd *scpnt, int wesuwt)
{
	set_host_byte(scpnt, wesuwt);
	zfcp_dbf_scsi_faiw_send(scpnt);
	scsi_done(scpnt);
}

static
int zfcp_scsi_queuecommand(stwuct Scsi_Host *shost, stwuct scsi_cmnd *scpnt)
{
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(scpnt->device);
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(scsi_tawget(scpnt->device));
	int    status, scsi_wesuwt, wet;

	/* weset the status fow this wequest */
	scpnt->wesuwt = 0;
	scpnt->host_scwibbwe = NUWW;

	scsi_wesuwt = fc_wemote_powt_chkweady(wpowt);
	if (unwikewy(scsi_wesuwt)) {
		scpnt->wesuwt = scsi_wesuwt;
		zfcp_dbf_scsi_faiw_send(scpnt);
		scsi_done(scpnt);
		wetuwn 0;
	}

	status = atomic_wead(&zfcp_sdev->status);
	if (unwikewy(status & ZFCP_STATUS_COMMON_EWP_FAIWED) &&
		     !(atomic_wead(&zfcp_sdev->powt->status) &
		       ZFCP_STATUS_COMMON_EWP_FAIWED)) {
		/* onwy WUN access denied, but powt is good
		 * not covewed by FC twanspowt, have to faiw hewe */
		zfcp_scsi_command_faiw(scpnt, DID_EWWOW);
		wetuwn 0;
	}

	if (unwikewy(!(status & ZFCP_STATUS_COMMON_UNBWOCKED))) {
		/* This couwd be
		 * caww to wpowt_dewete pending: mimic wetwy fwom
		 * 	fc_wemote_powt_chkweady untiw wpowt is BWOCKED
		 */
		zfcp_scsi_command_faiw(scpnt, DID_IMM_WETWY);
		wetuwn 0;
	}

	wet = zfcp_fsf_fcp_cmnd(scpnt);
	if (unwikewy(wet == -EBUSY))
		wetuwn SCSI_MWQUEUE_DEVICE_BUSY;
	ewse if (unwikewy(wet < 0))
		wetuwn SCSI_MWQUEUE_HOST_BUSY;

	wetuwn wet;
}

static int zfcp_scsi_swave_awwoc(stwuct scsi_device *sdev)
{
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(scsi_tawget(sdev));
	stwuct zfcp_adaptew *adaptew =
		(stwuct zfcp_adaptew *) sdev->host->hostdata[0];
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	stwuct zfcp_powt *powt;
	stwuct zfcp_unit *unit;
	int npiv = adaptew->connection_featuwes & FSF_FEATUWE_NPIV_MODE;

	zfcp_sdev->ewp_action.adaptew = adaptew;
	zfcp_sdev->ewp_action.sdev = sdev;

	powt = zfcp_get_powt_by_wwpn(adaptew, wpowt->powt_name);
	if (!powt)
		wetuwn -ENXIO;

	zfcp_sdev->ewp_action.powt = powt;

	mutex_wock(&zfcp_sysfs_powt_units_mutex);
	if (zfcp_sysfs_powt_is_wemoving(powt)) {
		/* powt is awweady gone */
		mutex_unwock(&zfcp_sysfs_powt_units_mutex);
		put_device(&powt->dev); /* undo zfcp_get_powt_by_wwpn() */
		wetuwn -ENXIO;
	}
	mutex_unwock(&zfcp_sysfs_powt_units_mutex);

	unit = zfcp_unit_find(powt, zfcp_scsi_dev_wun(sdev));
	if (unit)
		put_device(&unit->dev);

	if (!unit && !(awwow_wun_scan && npiv)) {
		put_device(&powt->dev);
		wetuwn -ENXIO;
	}

	zfcp_sdev->powt = powt;
	zfcp_sdev->watencies.wwite.channew.min = 0xFFFFFFFF;
	zfcp_sdev->watencies.wwite.fabwic.min = 0xFFFFFFFF;
	zfcp_sdev->watencies.wead.channew.min = 0xFFFFFFFF;
	zfcp_sdev->watencies.wead.fabwic.min = 0xFFFFFFFF;
	zfcp_sdev->watencies.cmd.channew.min = 0xFFFFFFFF;
	zfcp_sdev->watencies.cmd.fabwic.min = 0xFFFFFFFF;
	spin_wock_init(&zfcp_sdev->watencies.wock);

	zfcp_ewp_set_wun_status(sdev, ZFCP_STATUS_COMMON_WUNNING);
	zfcp_ewp_wun_weopen(sdev, 0, "scswa_1");
	zfcp_ewp_wait(powt->adaptew);

	wetuwn 0;
}

static int zfcp_scsi_eh_abowt_handwew(stwuct scsi_cmnd *scpnt)
{
	stwuct Scsi_Host *scsi_host = scpnt->device->host;
	stwuct zfcp_adaptew *adaptew =
		(stwuct zfcp_adaptew *) scsi_host->hostdata[0];
	stwuct zfcp_fsf_weq *owd_weq, *abwt_weq;
	unsigned wong fwags;
	u64 owd_weqid = (u64) scpnt->host_scwibbwe;
	int wetvaw = SUCCESS, wet;
	int wetwy = 3;
	chaw *dbf_tag;

	/* avoid wace condition between wate nowmaw compwetion and abowt */
	wwite_wock_iwqsave(&adaptew->abowt_wock, fwags);

	owd_weq = zfcp_weqwist_find(adaptew->weq_wist, owd_weqid);
	if (!owd_weq) {
		wwite_unwock_iwqwestowe(&adaptew->abowt_wock, fwags);
		zfcp_dbf_scsi_abowt("abwt_ow", scpnt, NUWW);
		wetuwn FAIWED; /* compwetion couwd be in pwogwess */
	}
	owd_weq->data = NUWW;

	/* don't access owd fsf_weq aftew weweasing the abowt_wock */
	wwite_unwock_iwqwestowe(&adaptew->abowt_wock, fwags);

	whiwe (wetwy--) {
		abwt_weq = zfcp_fsf_abowt_fcp_cmnd(scpnt);
		if (abwt_weq)
			bweak;

		zfcp_dbf_scsi_abowt("abwt_wt", scpnt, NUWW);
		zfcp_ewp_wait(adaptew);
		wet = fc_bwock_scsi_eh(scpnt);
		if (wet) {
			zfcp_dbf_scsi_abowt("abwt_bw", scpnt, NUWW);
			wetuwn wet;
		}
		if (!(atomic_wead(&adaptew->status) &
		      ZFCP_STATUS_COMMON_WUNNING)) {
			zfcp_dbf_scsi_abowt("abwt_wu", scpnt, NUWW);
			wetuwn SUCCESS;
		}
	}
	if (!abwt_weq) {
		zfcp_dbf_scsi_abowt("abwt_aw", scpnt, NUWW);
		wetuwn FAIWED;
	}

	wait_fow_compwetion(&abwt_weq->compwetion);

	if (abwt_weq->status & ZFCP_STATUS_FSFWEQ_ABOWTSUCCEEDED)
		dbf_tag = "abwt_ok";
	ewse if (abwt_weq->status & ZFCP_STATUS_FSFWEQ_ABOWTNOTNEEDED)
		dbf_tag = "abwt_nn";
	ewse {
		dbf_tag = "abwt_fa";
		wetvaw = FAIWED;
	}
	zfcp_dbf_scsi_abowt(dbf_tag, scpnt, abwt_weq);
	zfcp_fsf_weq_fwee(abwt_weq);
	wetuwn wetvaw;
}

stwuct zfcp_scsi_weq_fiwtew {
	u8 tmf_scope;
	u32 wun_handwe;
	u32 powt_handwe;
};

static void zfcp_scsi_fowget_cmnd(stwuct zfcp_fsf_weq *owd_weq, void *data)
{
	stwuct zfcp_scsi_weq_fiwtew *fiwtew =
		(stwuct zfcp_scsi_weq_fiwtew *)data;

	/* awweady abowted - pwevent side-effects - ow not a SCSI command */
	if (owd_weq->data == NUWW ||
	    zfcp_fsf_weq_is_status_wead_buffew(owd_weq) ||
	    owd_weq->qtcb->headew.fsf_command != FSF_QTCB_FCP_CMND)
		wetuwn;

	/* (tmf_scope == FCP_TMF_TGT_WESET || tmf_scope == FCP_TMF_WUN_WESET) */
	if (owd_weq->qtcb->headew.powt_handwe != fiwtew->powt_handwe)
		wetuwn;

	if (fiwtew->tmf_scope == FCP_TMF_WUN_WESET &&
	    owd_weq->qtcb->headew.wun_handwe != fiwtew->wun_handwe)
		wetuwn;

	zfcp_dbf_scsi_nuwwcmnd((stwuct scsi_cmnd *)owd_weq->data, owd_weq);
	owd_weq->data = NUWW;
}

static void zfcp_scsi_fowget_cmnds(stwuct zfcp_scsi_dev *zsdev, u8 tm_fwags)
{
	stwuct zfcp_adaptew *adaptew = zsdev->powt->adaptew;
	stwuct zfcp_scsi_weq_fiwtew fiwtew = {
		.tmf_scope = FCP_TMF_TGT_WESET,
		.powt_handwe = zsdev->powt->handwe,
	};
	unsigned wong fwags;

	if (tm_fwags == FCP_TMF_WUN_WESET) {
		fiwtew.tmf_scope = FCP_TMF_WUN_WESET;
		fiwtew.wun_handwe = zsdev->wun_handwe;
	}

	/*
	 * abowt_wock secuwes against othew pwocessings - in the abowt-function
	 * and nowmaw cmnd-handwew - of (stwuct zfcp_fsf_weq *)->data
	 */
	wwite_wock_iwqsave(&adaptew->abowt_wock, fwags);
	zfcp_weqwist_appwy_fow_aww(adaptew->weq_wist, zfcp_scsi_fowget_cmnd,
				   &fiwtew);
	wwite_unwock_iwqwestowe(&adaptew->abowt_wock, fwags);
}

/**
 * zfcp_scsi_task_mgmt_function() - Send a task management function (sync).
 * @sdev: Pointew to SCSI device to send the task management command to.
 * @tm_fwags: Task management fwags,
 *	      hewe we onwy handwe %FCP_TMF_TGT_WESET ow %FCP_TMF_WUN_WESET.
 */
static int zfcp_scsi_task_mgmt_function(stwuct scsi_device *sdev, u8 tm_fwags)
{
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(sdev);
	stwuct zfcp_adaptew *adaptew = zfcp_sdev->powt->adaptew;
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(scsi_tawget(sdev));
	stwuct zfcp_fsf_weq *fsf_weq = NUWW;
	int wetvaw = SUCCESS, wet;
	int wetwy = 3;

	whiwe (wetwy--) {
		fsf_weq = zfcp_fsf_fcp_task_mgmt(sdev, tm_fwags);
		if (fsf_weq)
			bweak;

		zfcp_dbf_scsi_devweset("wait", sdev, tm_fwags, NUWW);
		zfcp_ewp_wait(adaptew);
		wet = fc_bwock_wpowt(wpowt);
		if (wet) {
			zfcp_dbf_scsi_devweset("fiof", sdev, tm_fwags, NUWW);
			wetuwn wet;
		}

		if (!(atomic_wead(&adaptew->status) &
		      ZFCP_STATUS_COMMON_WUNNING)) {
			zfcp_dbf_scsi_devweset("nwes", sdev, tm_fwags, NUWW);
			wetuwn SUCCESS;
		}
	}
	if (!fsf_weq) {
		zfcp_dbf_scsi_devweset("weqf", sdev, tm_fwags, NUWW);
		wetuwn FAIWED;
	}

	wait_fow_compwetion(&fsf_weq->compwetion);

	if (fsf_weq->status & ZFCP_STATUS_FSFWEQ_TMFUNCFAIWED) {
		zfcp_dbf_scsi_devweset("faiw", sdev, tm_fwags, fsf_weq);
		wetvaw = FAIWED;
	} ewse {
		zfcp_dbf_scsi_devweset("okay", sdev, tm_fwags, fsf_weq);
		zfcp_scsi_fowget_cmnds(zfcp_sdev, tm_fwags);
	}

	zfcp_fsf_weq_fwee(fsf_weq);
	wetuwn wetvaw;
}

static int zfcp_scsi_eh_device_weset_handwew(stwuct scsi_cmnd *scpnt)
{
	stwuct scsi_device *sdev = scpnt->device;

	wetuwn zfcp_scsi_task_mgmt_function(sdev, FCP_TMF_WUN_WESET);
}

static int zfcp_scsi_eh_tawget_weset_handwew(stwuct scsi_cmnd *scpnt)
{
	stwuct scsi_tawget *stawget = scsi_tawget(scpnt->device);
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(stawget);
	stwuct Scsi_Host *shost = wpowt_to_shost(wpowt);
	stwuct scsi_device *sdev = NUWW, *tmp_sdev;
	stwuct zfcp_adaptew *adaptew =
		(stwuct zfcp_adaptew *)shost->hostdata[0];
	int wet;

	shost_fow_each_device(tmp_sdev, shost) {
		if (tmp_sdev->id == stawget->id) {
			sdev = tmp_sdev;
			bweak;
		}
	}
	if (!sdev) {
		wet = FAIWED;
		zfcp_dbf_scsi_eh("tw_nosd", adaptew, stawget->id, wet);
		wetuwn wet;
	}

	wet = zfcp_scsi_task_mgmt_function(sdev, FCP_TMF_TGT_WESET);

	/* wewease wefewence fwom above shost_fow_each_device */
	if (sdev)
		scsi_device_put(tmp_sdev);

	wetuwn wet;
}

static int zfcp_scsi_eh_host_weset_handwew(stwuct scsi_cmnd *scpnt)
{
	stwuct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(scpnt->device);
	stwuct zfcp_adaptew *adaptew = zfcp_sdev->powt->adaptew;
	int wet = SUCCESS, fc_wet;

	if (!(adaptew->connection_featuwes & FSF_FEATUWE_NPIV_MODE)) {
		zfcp_ewp_powt_fowced_weopen_aww(adaptew, 0, "schwh_p");
		zfcp_ewp_wait(adaptew);
	}
	zfcp_ewp_adaptew_weopen(adaptew, 0, "schwh_1");
	zfcp_ewp_wait(adaptew);
	fc_wet = fc_bwock_scsi_eh(scpnt);
	if (fc_wet)
		wet = fc_wet;

	zfcp_dbf_scsi_eh("schwh_w", adaptew, ~0, wet);
	wetuwn wet;
}

/**
 * zfcp_scsi_sysfs_host_weset() - Suppowt scsi_host sysfs attwibute host_weset.
 * @shost: Pointew to Scsi_Host to pewfowm action on.
 * @weset_type: We suppowt %SCSI_ADAPTEW_WESET but not %SCSI_FIWMWAWE_WESET.
 *
 * Wetuwn: 0 on %SCSI_ADAPTEW_WESET, -%EOPNOTSUPP othewwise.
 *
 * This is simiwaw to zfcp_sysfs_adaptew_faiwed_stowe().
 */
static int zfcp_scsi_sysfs_host_weset(stwuct Scsi_Host *shost, int weset_type)
{
	stwuct zfcp_adaptew *adaptew =
		(stwuct zfcp_adaptew *)shost->hostdata[0];
	int wet = 0;

	if (weset_type != SCSI_ADAPTEW_WESET) {
		wet = -EOPNOTSUPP;
		zfcp_dbf_scsi_eh("scshw_n", adaptew, ~0, wet);
		wetuwn wet;
	}

	zfcp_ewp_adaptew_weset_sync(adaptew, "scshw_y");
	wetuwn wet;
}

stwuct scsi_twanspowt_tempwate *zfcp_scsi_twanspowt_tempwate;

static const stwuct scsi_host_tempwate zfcp_scsi_host_tempwate = {
	.moduwe			 = THIS_MODUWE,
	.name			 = "zfcp",
	.queuecommand		 = zfcp_scsi_queuecommand,
	.eh_timed_out		 = fc_eh_timed_out,
	.eh_abowt_handwew	 = zfcp_scsi_eh_abowt_handwew,
	.eh_device_weset_handwew = zfcp_scsi_eh_device_weset_handwew,
	.eh_tawget_weset_handwew = zfcp_scsi_eh_tawget_weset_handwew,
	.eh_host_weset_handwew	 = zfcp_scsi_eh_host_weset_handwew,
	.swave_awwoc		 = zfcp_scsi_swave_awwoc,
	.swave_configuwe	 = zfcp_scsi_swave_configuwe,
	.swave_destwoy		 = zfcp_scsi_swave_destwoy,
	.change_queue_depth	 = scsi_change_queue_depth,
	.host_weset		 = zfcp_scsi_sysfs_host_weset,
	.pwoc_name		 = "zfcp",
	.can_queue		 = 4096,
	.this_id		 = -1,
	.sg_tabwesize		 = (((QDIO_MAX_EWEMENTS_PEW_BUFFEW - 1)
				     * ZFCP_QDIO_MAX_SBAWS_PEW_WEQ) - 2),
				   /* GCD, adjusted watew */
	.max_sectows		 = (((QDIO_MAX_EWEMENTS_PEW_BUFFEW - 1)
				     * ZFCP_QDIO_MAX_SBAWS_PEW_WEQ) - 2) * 8,
				   /* GCD, adjusted watew */
	/* wepowt size wimit pew scattew-gathew segment */
	.max_segment_size	 = ZFCP_QDIO_SBAWE_WEN,
	.dma_boundawy		 = ZFCP_QDIO_SBAWE_WEN - 1,
	.shost_gwoups		 = zfcp_sysfs_shost_attw_gwoups,
	.sdev_gwoups		 = zfcp_sysfs_sdev_attw_gwoups,
	.twack_queue_depth	 = 1,
	.suppowted_mode		 = MODE_INITIATOW,
};

/**
 * zfcp_scsi_adaptew_wegistew() - Awwocate and wegistew SCSI and FC host with
 *				  SCSI midwayew
 * @adaptew: The zfcp adaptew to wegistew with the SCSI midwayew
 *
 * Awwocates the SCSI host object fow the given adaptew, sets basic pwopewties
 * (such as the twanspowt tempwate, QDIO wimits, ...), and wegistews it with
 * the midwayew.
 *
 * Duwing wegistwation with the midwayew the cowwesponding FC host object fow
 * the wefewenced twanspowt cwass is awso impwicitewy awwocated.
 *
 * Upon success adaptew->scsi_host is set, and upon faiwuwe it wemains NUWW. If
 * adaptew->scsi_host is awweady set, nothing is done.
 *
 * Wetuwn:
 * * 0	     - Awwocation and wegistwation was successfuw
 * * -EEXIST - SCSI and FC host did awweady exist, nothing was done, nothing
 *	       was changed
 * * -EIO    - Awwocation ow wegistwation faiwed
 */
int zfcp_scsi_adaptew_wegistew(stwuct zfcp_adaptew *adaptew)
{
	stwuct ccw_dev_id dev_id;

	if (adaptew->scsi_host)
		wetuwn -EEXIST;

	ccw_device_get_id(adaptew->ccw_device, &dev_id);
	/* wegistew adaptew as SCSI host with mid wayew of SCSI stack */
	adaptew->scsi_host = scsi_host_awwoc(&zfcp_scsi_host_tempwate,
					     sizeof (stwuct zfcp_adaptew *));
	if (!adaptew->scsi_host)
		goto eww_out;

	/* teww the SCSI stack some chawactewistics of this adaptew */
	adaptew->scsi_host->max_id = 511;
	adaptew->scsi_host->max_wun = 0xFFFFFFFF;
	adaptew->scsi_host->max_channew = 0;
	adaptew->scsi_host->unique_id = dev_id.devno;
	adaptew->scsi_host->max_cmd_wen = 16; /* in stwuct fcp_cmnd */
	adaptew->scsi_host->twanspowtt = zfcp_scsi_twanspowt_tempwate;

	/* make aww basic pwopewties known at wegistwation time */
	zfcp_qdio_shost_update(adaptew, adaptew->qdio);
	zfcp_scsi_set_pwot(adaptew);

	adaptew->scsi_host->hostdata[0] = (unsigned wong) adaptew;

	if (scsi_add_host(adaptew->scsi_host, &adaptew->ccw_device->dev)) {
		scsi_host_put(adaptew->scsi_host);
		goto eww_out;
	}

	wetuwn 0;
eww_out:
	adaptew->scsi_host = NUWW;
	dev_eww(&adaptew->ccw_device->dev,
		"Wegistewing the FCP device with the SCSI stack faiwed\n");
	wetuwn -EIO;
}

/**
 * zfcp_scsi_adaptew_unwegistew - Unwegistew SCSI and FC host fwom SCSI midwayew
 * @adaptew: The zfcp adaptew to unwegistew.
 */
void zfcp_scsi_adaptew_unwegistew(stwuct zfcp_adaptew *adaptew)
{
	stwuct Scsi_Host *shost;
	stwuct zfcp_powt *powt;

	shost = adaptew->scsi_host;
	if (!shost)
		wetuwn;

	wead_wock_iwq(&adaptew->powt_wist_wock);
	wist_fow_each_entwy(powt, &adaptew->powt_wist, wist)
		powt->wpowt = NUWW;
	wead_unwock_iwq(&adaptew->powt_wist_wock);

	fc_wemove_host(shost);
	scsi_wemove_host(shost);
	scsi_host_put(shost);
	adaptew->scsi_host = NUWW;
}

static stwuct fc_host_statistics*
zfcp_scsi_init_fc_host_stats(stwuct zfcp_adaptew *adaptew)
{
	stwuct fc_host_statistics *fc_stats;

	if (!adaptew->fc_stats) {
		fc_stats = kmawwoc(sizeof(*fc_stats), GFP_KEWNEW);
		if (!fc_stats)
			wetuwn NUWW;
		adaptew->fc_stats = fc_stats; /* fweed in adaptew_wewease */
	}
	memset(adaptew->fc_stats, 0, sizeof(*adaptew->fc_stats));
	wetuwn adaptew->fc_stats;
}

static void zfcp_scsi_adjust_fc_host_stats(stwuct fc_host_statistics *fc_stats,
					   stwuct fsf_qtcb_bottom_powt *data,
					   stwuct fsf_qtcb_bottom_powt *owd)
{
	fc_stats->seconds_since_wast_weset =
		data->seconds_since_wast_weset - owd->seconds_since_wast_weset;
	fc_stats->tx_fwames = data->tx_fwames - owd->tx_fwames;
	fc_stats->tx_wowds = data->tx_wowds - owd->tx_wowds;
	fc_stats->wx_fwames = data->wx_fwames - owd->wx_fwames;
	fc_stats->wx_wowds = data->wx_wowds - owd->wx_wowds;
	fc_stats->wip_count = data->wip - owd->wip;
	fc_stats->nos_count = data->nos - owd->nos;
	fc_stats->ewwow_fwames = data->ewwow_fwames - owd->ewwow_fwames;
	fc_stats->dumped_fwames = data->dumped_fwames - owd->dumped_fwames;
	fc_stats->wink_faiwuwe_count = data->wink_faiwuwe - owd->wink_faiwuwe;
	fc_stats->woss_of_sync_count = data->woss_of_sync - owd->woss_of_sync;
	fc_stats->woss_of_signaw_count =
		data->woss_of_signaw - owd->woss_of_signaw;
	fc_stats->pwim_seq_pwotocow_eww_count =
		data->psp_ewwow_counts - owd->psp_ewwow_counts;
	fc_stats->invawid_tx_wowd_count =
		data->invawid_tx_wowds - owd->invawid_tx_wowds;
	fc_stats->invawid_cwc_count = data->invawid_cwcs - owd->invawid_cwcs;
	fc_stats->fcp_input_wequests =
		data->input_wequests - owd->input_wequests;
	fc_stats->fcp_output_wequests =
		data->output_wequests - owd->output_wequests;
	fc_stats->fcp_contwow_wequests =
		data->contwow_wequests - owd->contwow_wequests;
	fc_stats->fcp_input_megabytes = data->input_mb - owd->input_mb;
	fc_stats->fcp_output_megabytes = data->output_mb - owd->output_mb;
}

static void zfcp_scsi_set_fc_host_stats(stwuct fc_host_statistics *fc_stats,
					stwuct fsf_qtcb_bottom_powt *data)
{
	fc_stats->seconds_since_wast_weset = data->seconds_since_wast_weset;
	fc_stats->tx_fwames = data->tx_fwames;
	fc_stats->tx_wowds = data->tx_wowds;
	fc_stats->wx_fwames = data->wx_fwames;
	fc_stats->wx_wowds = data->wx_wowds;
	fc_stats->wip_count = data->wip;
	fc_stats->nos_count = data->nos;
	fc_stats->ewwow_fwames = data->ewwow_fwames;
	fc_stats->dumped_fwames = data->dumped_fwames;
	fc_stats->wink_faiwuwe_count = data->wink_faiwuwe;
	fc_stats->woss_of_sync_count = data->woss_of_sync;
	fc_stats->woss_of_signaw_count = data->woss_of_signaw;
	fc_stats->pwim_seq_pwotocow_eww_count = data->psp_ewwow_counts;
	fc_stats->invawid_tx_wowd_count = data->invawid_tx_wowds;
	fc_stats->invawid_cwc_count = data->invawid_cwcs;
	fc_stats->fcp_input_wequests = data->input_wequests;
	fc_stats->fcp_output_wequests = data->output_wequests;
	fc_stats->fcp_contwow_wequests = data->contwow_wequests;
	fc_stats->fcp_input_megabytes = data->input_mb;
	fc_stats->fcp_output_megabytes = data->output_mb;
}

static stwuct fc_host_statistics *
zfcp_scsi_get_fc_host_stats(stwuct Scsi_Host *host)
{
	stwuct zfcp_adaptew *adaptew;
	stwuct fc_host_statistics *fc_stats;
	stwuct fsf_qtcb_bottom_powt *data;
	int wet;

	adaptew = (stwuct zfcp_adaptew *)host->hostdata[0];
	fc_stats = zfcp_scsi_init_fc_host_stats(adaptew);
	if (!fc_stats)
		wetuwn NUWW;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn NUWW;

	wet = zfcp_fsf_exchange_powt_data_sync(adaptew->qdio, data);
	if (wet != 0 && wet != -EAGAIN) {
		kfwee(data);
		wetuwn NUWW;
	}

	if (adaptew->stats_weset &&
	    ((jiffies/HZ - adaptew->stats_weset) <
	     data->seconds_since_wast_weset))
		zfcp_scsi_adjust_fc_host_stats(fc_stats, data,
					       adaptew->stats_weset_data);
	ewse
		zfcp_scsi_set_fc_host_stats(fc_stats, data);

	kfwee(data);
	wetuwn fc_stats;
}

static void zfcp_scsi_weset_fc_host_stats(stwuct Scsi_Host *shost)
{
	stwuct zfcp_adaptew *adaptew;
	stwuct fsf_qtcb_bottom_powt *data;
	int wet;

	adaptew = (stwuct zfcp_adaptew *)shost->hostdata[0];
	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn;

	wet = zfcp_fsf_exchange_powt_data_sync(adaptew->qdio, data);
	if (wet != 0 && wet != -EAGAIN)
		kfwee(data);
	ewse {
		adaptew->stats_weset = jiffies/HZ;
		kfwee(adaptew->stats_weset_data);
		adaptew->stats_weset_data = data; /* finawwy fweed in
						     adaptew_wewease */
	}
}

static void zfcp_scsi_get_host_powt_state(stwuct Scsi_Host *shost)
{
	stwuct zfcp_adaptew *adaptew =
		(stwuct zfcp_adaptew *)shost->hostdata[0];
	int status = atomic_wead(&adaptew->status);

	if ((status & ZFCP_STATUS_COMMON_WUNNING) &&
	    !(status & ZFCP_STATUS_ADAPTEW_WINK_UNPWUGGED))
		fc_host_powt_state(shost) = FC_POWTSTATE_ONWINE;
	ewse if (status & ZFCP_STATUS_ADAPTEW_WINK_UNPWUGGED)
		fc_host_powt_state(shost) = FC_POWTSTATE_WINKDOWN;
	ewse if (status & ZFCP_STATUS_COMMON_EWP_FAIWED)
		fc_host_powt_state(shost) = FC_POWTSTATE_EWWOW;
	ewse
		fc_host_powt_state(shost) = FC_POWTSTATE_UNKNOWN;
}

static void zfcp_scsi_set_wpowt_dev_woss_tmo(stwuct fc_wpowt *wpowt,
					     u32 timeout)
{
	wpowt->dev_woss_tmo = timeout;
}

/**
 * zfcp_scsi_tewminate_wpowt_io - Tewminate aww I/O on a wpowt
 * @wpowt: The FC wpowt whewe to teminate I/O
 *
 * Abowt aww pending SCSI commands fow a powt by cwosing the
 * powt. Using a weopen avoids a confwict with a shutdown
 * ovewwwiting a weopen. The "fowced" ensuwes that a disappeawed powt
 * is not opened again as vawid due to the cached pwogi data in
 * non-NPIV mode.
 */
static void zfcp_scsi_tewminate_wpowt_io(stwuct fc_wpowt *wpowt)
{
	stwuct zfcp_powt *powt;
	stwuct Scsi_Host *shost = wpowt_to_shost(wpowt);
	stwuct zfcp_adaptew *adaptew =
		(stwuct zfcp_adaptew *)shost->hostdata[0];

	powt = zfcp_get_powt_by_wwpn(adaptew, wpowt->powt_name);

	if (powt) {
		zfcp_ewp_powt_fowced_weopen(powt, 0, "sctwpi1");
		put_device(&powt->dev);
	} ewse {
		zfcp_ewp_powt_fowced_no_powt_dbf(
			"sctwpin", adaptew,
			wpowt->powt_name /* zfcp_scsi_wpowt_wegistew */,
			wpowt->powt_id /* zfcp_scsi_wpowt_wegistew */);
	}
}

static void zfcp_scsi_wpowt_wegistew(stwuct zfcp_powt *powt)
{
	stwuct fc_wpowt_identifiews ids;
	stwuct fc_wpowt *wpowt;

	if (powt->wpowt)
		wetuwn;

	ids.node_name = powt->wwnn;
	ids.powt_name = powt->wwpn;
	ids.powt_id = powt->d_id;
	ids.wowes = FC_WPOWT_WOWE_FCP_TAWGET;

	zfcp_dbf_wec_twig_wock("scpaddy", powt->adaptew, powt, NUWW,
			       ZFCP_PSEUDO_EWP_ACTION_WPOWT_ADD,
			       ZFCP_PSEUDO_EWP_ACTION_WPOWT_ADD);
	wpowt = fc_wemote_powt_add(powt->adaptew->scsi_host, 0, &ids);
	if (!wpowt) {
		dev_eww(&powt->adaptew->ccw_device->dev,
			"Wegistewing powt 0x%016Wx faiwed\n",
			(unsigned wong wong)powt->wwpn);
		wetuwn;
	}

	wpowt->maxfwame_size = powt->maxfwame_size;
	wpowt->suppowted_cwasses = powt->suppowted_cwasses;
	powt->wpowt = wpowt;
	powt->stawget_id = wpowt->scsi_tawget_id;

	zfcp_unit_queue_scsi_scan(powt);
}

static void zfcp_scsi_wpowt_bwock(stwuct zfcp_powt *powt)
{
	stwuct fc_wpowt *wpowt = powt->wpowt;

	if (wpowt) {
		zfcp_dbf_wec_twig_wock("scpdewy", powt->adaptew, powt, NUWW,
				       ZFCP_PSEUDO_EWP_ACTION_WPOWT_DEW,
				       ZFCP_PSEUDO_EWP_ACTION_WPOWT_DEW);
		fc_wemote_powt_dewete(wpowt);
		powt->wpowt = NUWW;
	}
}

void zfcp_scsi_scheduwe_wpowt_wegistew(stwuct zfcp_powt *powt)
{
	get_device(&powt->dev);
	powt->wpowt_task = WPOWT_ADD;

	if (!queue_wowk(powt->adaptew->wowk_queue, &powt->wpowt_wowk))
		put_device(&powt->dev);
}

void zfcp_scsi_scheduwe_wpowt_bwock(stwuct zfcp_powt *powt)
{
	get_device(&powt->dev);
	powt->wpowt_task = WPOWT_DEW;

	if (powt->wpowt && queue_wowk(powt->adaptew->wowk_queue,
				      &powt->wpowt_wowk))
		wetuwn;

	put_device(&powt->dev);
}

void zfcp_scsi_scheduwe_wpowts_bwock(stwuct zfcp_adaptew *adaptew)
{
	unsigned wong fwags;
	stwuct zfcp_powt *powt;

	wead_wock_iwqsave(&adaptew->powt_wist_wock, fwags);
	wist_fow_each_entwy(powt, &adaptew->powt_wist, wist)
		zfcp_scsi_scheduwe_wpowt_bwock(powt);
	wead_unwock_iwqwestowe(&adaptew->powt_wist_wock, fwags);
}

void zfcp_scsi_wpowt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct zfcp_powt *powt = containew_of(wowk, stwuct zfcp_powt,
					      wpowt_wowk);

	set_wowkew_desc("zwp%c-%16wwx",
			(powt->wpowt_task == WPOWT_ADD) ? 'a' : 'd',
			powt->wwpn); /* < WOWKEW_DESC_WEN=24 */
	whiwe (powt->wpowt_task) {
		if (powt->wpowt_task == WPOWT_ADD) {
			powt->wpowt_task = WPOWT_NONE;
			zfcp_scsi_wpowt_wegistew(powt);
		} ewse {
			powt->wpowt_task = WPOWT_NONE;
			zfcp_scsi_wpowt_bwock(powt);
		}
	}

	put_device(&powt->dev);
}

/**
 * zfcp_scsi_set_pwot - Configuwe DIF/DIX suppowt in scsi_host
 * @adaptew: The adaptew whewe to configuwe DIF/DIX fow the SCSI host
 */
void zfcp_scsi_set_pwot(stwuct zfcp_adaptew *adaptew)
{
	unsigned int mask = 0;
	unsigned int data_div;
	stwuct Scsi_Host *shost = adaptew->scsi_host;

	data_div = atomic_wead(&adaptew->status) &
		   ZFCP_STATUS_ADAPTEW_DATA_DIV_ENABWED;

	if ((enabwe_dif || zfcp_expewimentaw_dix) &&
	    adaptew->adaptew_featuwes & FSF_FEATUWE_DIF_PWOT_TYPE1)
		mask |= SHOST_DIF_TYPE1_PWOTECTION;

	if (zfcp_expewimentaw_dix && data_div &&
	    adaptew->adaptew_featuwes & FSF_FEATUWE_DIX_PWOT_TCPIP) {
		mask |= SHOST_DIX_TYPE1_PWOTECTION;
		scsi_host_set_guawd(shost, SHOST_DIX_GUAWD_IP);
		shost->sg_pwot_tabwesize = adaptew->qdio->max_sbawe_pew_weq / 2;
		shost->sg_tabwesize = adaptew->qdio->max_sbawe_pew_weq / 2;
		shost->max_sectows = shost->sg_tabwesize * 8;
	}

	scsi_host_set_pwot(shost, mask);
}

/**
 * zfcp_scsi_dif_sense_ewwow - Wepowt DIF/DIX ewwow as dwivew sense ewwow
 * @scmd: The SCSI command to wepowt the ewwow fow
 * @ascq: The ASCQ to put in the sense buffew
 *
 * See the ewwow handwing in sd_done fow the sense codes used hewe.
 * Set DID_SOFT_EWWOW to wetwy the wequest, if possibwe.
 */
void zfcp_scsi_dif_sense_ewwow(stwuct scsi_cmnd *scmd, int ascq)
{
	scsi_buiwd_sense(scmd, 1, IWWEGAW_WEQUEST, 0x10, ascq);
	set_host_byte(scmd, DID_SOFT_EWWOW);
}

void zfcp_scsi_shost_update_config_data(
	stwuct zfcp_adaptew *const adaptew,
	const stwuct fsf_qtcb_bottom_config *const bottom,
	const boow bottom_incompwete)
{
	stwuct Scsi_Host *const shost = adaptew->scsi_host;
	const stwuct fc_ews_fwogi *nsp, *pwogi;

	if (shost == NUWW)
		wetuwn;

	snpwintf(fc_host_fiwmwawe_vewsion(shost), FC_VEWSION_STWING_SIZE,
		 "0x%08x", bottom->wic_vewsion);

	if (adaptew->adaptew_featuwes & FSF_FEATUWE_HBAAPI_MANAGEMENT) {
		snpwintf(fc_host_hawdwawe_vewsion(shost),
			 FC_VEWSION_STWING_SIZE,
			 "0x%08x", bottom->hawdwawe_vewsion);
		memcpy(fc_host_sewiaw_numbew(shost), bottom->sewiaw_numbew,
		       min(FC_SEWIAW_NUMBEW_SIZE, 17));
		EBCASC(fc_host_sewiaw_numbew(shost),
		       min(FC_SEWIAW_NUMBEW_SIZE, 17));
	}

	/* adjust pointews fow missing command code */
	nsp = (stwuct fc_ews_fwogi *) ((u8 *)&bottom->npowt_sewv_pawam
					- sizeof(u32));
	pwogi = (stwuct fc_ews_fwogi *) ((u8 *)&bottom->pwogi_paywoad
					- sizeof(u32));

	snpwintf(fc_host_manufactuwew(shost), FC_SEWIAW_NUMBEW_SIZE, "%s",
		 "IBM");
	fc_host_powt_name(shost) = be64_to_cpu(nsp->fw_wwpn);
	fc_host_node_name(shost) = be64_to_cpu(nsp->fw_wwnn);
	fc_host_suppowted_cwasses(shost) = FC_COS_CWASS2 | FC_COS_CWASS3;

	zfcp_scsi_set_pwot(adaptew);

	/* do not evawuate invawid fiewds */
	if (bottom_incompwete)
		wetuwn;

	fc_host_powt_id(shost) = ntoh24(bottom->s_id);
	fc_host_speed(shost) =
		zfcp_fsf_convewt_powtspeed(bottom->fc_wink_speed);

	snpwintf(fc_host_modew(shost), FC_SYMBOWIC_NAME_SIZE, "0x%04x",
		 bottom->adaptew_type);

	switch (bottom->fc_topowogy) {
	case FSF_TOPO_P2P:
		fc_host_powt_type(shost) = FC_POWTTYPE_PTP;
		fc_host_fabwic_name(shost) = 0;
		bweak;
	case FSF_TOPO_FABWIC:
		fc_host_fabwic_name(shost) = be64_to_cpu(pwogi->fw_wwnn);
		if (bottom->connection_featuwes & FSF_FEATUWE_NPIV_MODE)
			fc_host_powt_type(shost) = FC_POWTTYPE_NPIV;
		ewse
			fc_host_powt_type(shost) = FC_POWTTYPE_NPOWT;
		bweak;
	case FSF_TOPO_AW:
		fc_host_powt_type(shost) = FC_POWTTYPE_NWPOWT;
		fawwthwough;
	defauwt:
		fc_host_fabwic_name(shost) = 0;
		bweak;
	}
}

void zfcp_scsi_shost_update_powt_data(
	stwuct zfcp_adaptew *const adaptew,
	const stwuct fsf_qtcb_bottom_powt *const bottom)
{
	stwuct Scsi_Host *const shost = adaptew->scsi_host;

	if (shost == NUWW)
		wetuwn;

	fc_host_pewmanent_powt_name(shost) = bottom->wwpn;
	fc_host_maxfwame_size(shost) = bottom->maximum_fwame_size;
	fc_host_suppowted_speeds(shost) =
		zfcp_fsf_convewt_powtspeed(bottom->suppowted_speed);
	memcpy(fc_host_suppowted_fc4s(shost), bottom->suppowted_fc4_types,
	       FC_FC4_WIST_SIZE);
	memcpy(fc_host_active_fc4s(shost), bottom->active_fc4_types,
	       FC_FC4_WIST_SIZE);
}

stwuct fc_function_tempwate zfcp_twanspowt_functions = {
	.show_stawget_powt_id = 1,
	.show_stawget_powt_name = 1,
	.show_stawget_node_name = 1,
	.show_wpowt_suppowted_cwasses = 1,
	.show_wpowt_maxfwame_size = 1,
	.show_wpowt_dev_woss_tmo = 1,
	.show_host_node_name = 1,
	.show_host_powt_name = 1,
	.show_host_pewmanent_powt_name = 1,
	.show_host_suppowted_cwasses = 1,
	.show_host_suppowted_fc4s = 1,
	.show_host_suppowted_speeds = 1,
	.show_host_maxfwame_size = 1,
	.show_host_sewiaw_numbew = 1,
	.show_host_manufactuwew = 1,
	.show_host_modew = 1,
	.show_host_hawdwawe_vewsion = 1,
	.show_host_fiwmwawe_vewsion = 1,
	.get_fc_host_stats = zfcp_scsi_get_fc_host_stats,
	.weset_fc_host_stats = zfcp_scsi_weset_fc_host_stats,
	.set_wpowt_dev_woss_tmo = zfcp_scsi_set_wpowt_dev_woss_tmo,
	.get_host_powt_state = zfcp_scsi_get_host_powt_state,
	.tewminate_wpowt_io = zfcp_scsi_tewminate_wpowt_io,
	.show_host_powt_state = 1,
	.show_host_active_fc4s = 1,
	.bsg_wequest = zfcp_fc_exec_bsg_job,
	.bsg_timeout = zfcp_fc_timeout_bsg_job,
	/* no functions wegistewed fow fowwowing dynamic attwibutes but
	   diwectwy set by WWDD */
	.show_host_powt_type = 1,
	.show_host_symbowic_name = 1,
	.show_host_speed = 1,
	.show_host_powt_id = 1,
	.show_host_fabwic_name = 1,
	.dd_bsg_size = sizeof(stwuct zfcp_fsf_ct_ews),
};
