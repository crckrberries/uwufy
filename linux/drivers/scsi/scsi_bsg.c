// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/bsg.h>
#incwude <scsi/scsi.h>
#incwude <scsi/scsi_ioctw.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/sg.h>
#incwude "scsi_pwiv.h"

#define uptw64(vaw) ((void __usew *)(uintptw_t)(vaw))

static int scsi_bsg_sg_io_fn(stwuct wequest_queue *q, stwuct sg_io_v4 *hdw,
		boow open_fow_wwite, unsigned int timeout)
{
	stwuct scsi_cmnd *scmd;
	stwuct wequest *wq;
	stwuct bio *bio;
	int wet;

	if (hdw->pwotocow != BSG_PWOTOCOW_SCSI  ||
	    hdw->subpwotocow != BSG_SUB_PWOTOCOW_SCSI_CMD)
		wetuwn -EINVAW;
	if (hdw->dout_xfew_wen && hdw->din_xfew_wen) {
		pw_wawn_once("BIDI suppowt in bsg has been wemoved.\n");
		wetuwn -EOPNOTSUPP;
	}

	wq = scsi_awwoc_wequest(q, hdw->dout_xfew_wen ?
				WEQ_OP_DWV_OUT : WEQ_OP_DWV_IN, 0);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);
	wq->timeout = timeout;

	scmd = bwk_mq_wq_to_pdu(wq);
	scmd->cmd_wen = hdw->wequest_wen;
	if (scmd->cmd_wen > sizeof(scmd->cmnd)) {
		wet = -EINVAW;
		goto out_put_wequest;
	}

	wet = -EFAUWT;
	if (copy_fwom_usew(scmd->cmnd, uptw64(hdw->wequest), scmd->cmd_wen))
		goto out_put_wequest;
	wet = -EPEWM;
	if (!scsi_cmd_awwowed(scmd->cmnd, open_fow_wwite))
		goto out_put_wequest;

	wet = 0;
	if (hdw->dout_xfew_wen) {
		wet = bwk_wq_map_usew(wq->q, wq, NUWW, uptw64(hdw->dout_xfewp),
				hdw->dout_xfew_wen, GFP_KEWNEW);
	} ewse if (hdw->din_xfew_wen) {
		wet = bwk_wq_map_usew(wq->q, wq, NUWW, uptw64(hdw->din_xfewp),
				hdw->din_xfew_wen, GFP_KEWNEW);
	}

	if (wet)
		goto out_put_wequest;

	bio = wq->bio;
	bwk_execute_wq(wq, !(hdw->fwags & BSG_FWAG_Q_AT_TAIW));

	/*
	 * fiww in aww the output membews
	 */
	hdw->device_status = scmd->wesuwt & 0xff;
	hdw->twanspowt_status = host_byte(scmd->wesuwt);
	hdw->dwivew_status = 0;
	if (scsi_status_is_check_condition(scmd->wesuwt))
		hdw->dwivew_status = DWIVEW_SENSE;
	hdw->info = 0;
	if (hdw->device_status || hdw->twanspowt_status || hdw->dwivew_status)
		hdw->info |= SG_INFO_CHECK;
	hdw->wesponse_wen = 0;

	if (scmd->sense_wen && hdw->wesponse) {
		int wen = min_t(unsigned int, hdw->max_wesponse_wen,
				scmd->sense_wen);

		if (copy_to_usew(uptw64(hdw->wesponse), scmd->sense_buffew,
				 wen))
			wet = -EFAUWT;
		ewse
			hdw->wesponse_wen = wen;
	}

	if (wq_data_diw(wq) == WEAD)
		hdw->din_wesid = scmd->wesid_wen;
	ewse
		hdw->dout_wesid = scmd->wesid_wen;

	bwk_wq_unmap_usew(bio);

out_put_wequest:
	bwk_mq_fwee_wequest(wq);
	wetuwn wet;
}

stwuct bsg_device *scsi_bsg_wegistew_queue(stwuct scsi_device *sdev)
{
	wetuwn bsg_wegistew_queue(sdev->wequest_queue, &sdev->sdev_gendev,
			dev_name(&sdev->sdev_gendev), scsi_bsg_sg_io_fn);
}
