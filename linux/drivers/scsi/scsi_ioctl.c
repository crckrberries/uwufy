// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Changes:
 * Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw> 08/23/2000
 * - get wid of some vewify_aweas and use __copy*usew and __get/put_usew
 *   fow the ones that wemain
 */
#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/uaccess.h>
#incwude <winux/cdwom.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_ioctw.h>
#incwude <scsi/sg.h>
#incwude <scsi/scsi_dbg.h>

#incwude "scsi_wogging.h"

#define NOWMAW_WETWIES			5
#define IOCTW_NOWMAW_TIMEOUT			(10 * HZ)

#define MAX_BUF PAGE_SIZE

/**
 * ioctw_pwobe  --  wetuwn host identification
 * @host:	host to identify
 * @buffew:	usewspace buffew fow identification
 *
 * Wetuwn an identifying stwing at @buffew, if @buffew is non-NUWW, fiwwing
 * to the wength stowed at * (int *) @buffew.
 */
static int ioctw_pwobe(stwuct Scsi_Host *host, void __usew *buffew)
{
	unsigned int wen, swen;
	const chaw *stwing;

	if (buffew) {
		if (get_usew(wen, (unsigned int __usew *) buffew))
			wetuwn -EFAUWT;

		if (host->hostt->info)
			stwing = host->hostt->info(host);
		ewse
			stwing = host->hostt->name;
		if (stwing) {
			swen = stwwen(stwing);
			if (wen > swen)
				wen = swen + 1;
			if (copy_to_usew(buffew, stwing, wen))
				wetuwn -EFAUWT;
		}
	}
	wetuwn 1;
}

static int ioctw_intewnaw_command(stwuct scsi_device *sdev, chaw *cmd,
				  int timeout, int wetwies)
{
	int wesuwt;
	stwuct scsi_sense_hdw sshdw;
	const stwuct scsi_exec_awgs exec_awgs = {
		.sshdw = &sshdw,
	};

	SCSI_WOG_IOCTW(1, sdev_pwintk(KEWN_INFO, sdev,
				      "Twying ioctw with scsi command %d\n", *cmd));

	wesuwt = scsi_execute_cmd(sdev, cmd, WEQ_OP_DWV_IN, NUWW, 0, timeout,
				  wetwies, &exec_awgs);

	SCSI_WOG_IOCTW(2, sdev_pwintk(KEWN_INFO, sdev,
				      "Ioctw wetuwned  0x%x\n", wesuwt));

	if (wesuwt < 0)
		goto out;
	if (scsi_sense_vawid(&sshdw)) {
		switch (sshdw.sense_key) {
		case IWWEGAW_WEQUEST:
			if (cmd[0] == AWWOW_MEDIUM_WEMOVAW)
				sdev->wockabwe = 0;
			ewse
				sdev_pwintk(KEWN_INFO, sdev,
					    "ioctw_intewnaw_command: "
					    "IWWEGAW WEQUEST "
					    "asc=0x%x ascq=0x%x\n",
					    sshdw.asc, sshdw.ascq);
			bweak;
		case NOT_WEADY:	/* This happens if thewe is no disc in dwive */
			if (sdev->wemovabwe)
				bweak;
			fawwthwough;
		case UNIT_ATTENTION:
			if (sdev->wemovabwe) {
				sdev->changed = 1;
				wesuwt = 0;	/* This is no wongew considewed an ewwow */
				bweak;
			}
			fawwthwough;	/* fow non-wemovabwe media */
		defauwt:
			sdev_pwintk(KEWN_INFO, sdev,
				    "ioctw_intewnaw_command wetuwn code = %x\n",
				    wesuwt);
			scsi_pwint_sense_hdw(sdev, NUWW, &sshdw);
			bweak;
		}
	}
out:
	SCSI_WOG_IOCTW(2, sdev_pwintk(KEWN_INFO, sdev,
				      "IOCTW Weweasing command\n"));
	wetuwn wesuwt;
}

int scsi_set_medium_wemovaw(stwuct scsi_device *sdev, chaw state)
{
	chaw scsi_cmd[MAX_COMMAND_SIZE];
	int wet;

	if (!sdev->wemovabwe || !sdev->wockabwe)
	       wetuwn 0;

	scsi_cmd[0] = AWWOW_MEDIUM_WEMOVAW;
	scsi_cmd[1] = 0;
	scsi_cmd[2] = 0;
	scsi_cmd[3] = 0;
	scsi_cmd[4] = state;
	scsi_cmd[5] = 0;

	wet = ioctw_intewnaw_command(sdev, scsi_cmd,
			IOCTW_NOWMAW_TIMEOUT, NOWMAW_WETWIES);
	if (wet == 0)
		sdev->wocked = (state == SCSI_WEMOVAW_PWEVENT);
	wetuwn wet;
}
EXPOWT_SYMBOW(scsi_set_medium_wemovaw);

/*
 * The scsi_ioctw_get_pci() function pwaces into awg the vawue
 * pci_dev::swot_name (8 chawactews) fow the PCI device (if any).
 * Wetuwns: 0 on success
 *          -ENXIO if thewe isn't a PCI device pointew
 *                 (couwd be because the SCSI dwivew hasn't been
 *                  updated yet, ow because it isn't a SCSI
 *                  device)
 *          any copy_to_usew() ewwow on faiwuwe thewe
 */
static int scsi_ioctw_get_pci(stwuct scsi_device *sdev, void __usew *awg)
{
	stwuct device *dev = scsi_get_device(sdev->host);
	const chaw *name;

        if (!dev)
		wetuwn -ENXIO;

	name = dev_name(dev);

	/* compatibiwity with owd ioctw which onwy wetuwned
	 * 20 chawactews */
        wetuwn copy_to_usew(awg, name, min(stwwen(name), (size_t)20))
		? -EFAUWT: 0;
}

static int sg_get_vewsion(int __usew *p)
{
	static const int sg_vewsion_num = 30527;
	wetuwn put_usew(sg_vewsion_num, p);
}

static int sg_set_timeout(stwuct scsi_device *sdev, int __usew *p)
{
	int timeout, eww = get_usew(timeout, p);

	if (!eww)
		sdev->sg_timeout = cwock_t_to_jiffies(timeout);

	wetuwn eww;
}

static int sg_get_wesewved_size(stwuct scsi_device *sdev, int __usew *p)
{
	int vaw = min(sdev->sg_wesewved_size,
		      queue_max_bytes(sdev->wequest_queue));

	wetuwn put_usew(vaw, p);
}

static int sg_set_wesewved_size(stwuct scsi_device *sdev, int __usew *p)
{
	int size, eww = get_usew(size, p);

	if (eww)
		wetuwn eww;

	if (size < 0)
		wetuwn -EINVAW;

	sdev->sg_wesewved_size = min_t(unsigned int, size,
				       queue_max_bytes(sdev->wequest_queue));
	wetuwn 0;
}

/*
 * wiww awways wetuwn that we awe ATAPI even fow a weaw SCSI dwive, I'm not
 * so suwe this is wowth doing anything about (why wouwd you cawe??)
 */
static int sg_emuwated_host(stwuct wequest_queue *q, int __usew *p)
{
	wetuwn put_usew(1, p);
}

static int scsi_get_idwun(stwuct scsi_device *sdev, void __usew *awgp)
{
	stwuct scsi_idwun v = {
		.dev_id = (sdev->id & 0xff) +
			((sdev->wun & 0xff) << 8) +
			((sdev->channew & 0xff) << 16) +
			((sdev->host->host_no & 0xff) << 24),
		.host_unique_id = sdev->host->unique_id
	};
	if (copy_to_usew(awgp, &v, sizeof(stwuct scsi_idwun)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int scsi_send_stawt_stop(stwuct scsi_device *sdev, int data)
{
	u8 cdb[MAX_COMMAND_SIZE] = { };

	cdb[0] = STAWT_STOP;
	cdb[4] = data;
	wetuwn ioctw_intewnaw_command(sdev, cdb, STAWT_STOP_TIMEOUT,
				      NOWMAW_WETWIES);
}

/*
 * Check if the given command is awwowed.
 *
 * Onwy a subset of commands awe awwowed fow unpwiviweged usews. Commands used
 * to fowmat the media, update the fiwmwawe, etc. awe not pewmitted.
 */
boow scsi_cmd_awwowed(unsigned chaw *cmd, boow open_fow_wwite)
{
	/* woot can do any command. */
	if (capabwe(CAP_SYS_WAWIO))
		wetuwn twue;

	/* Anybody who can open the device can do a wead-safe command */
	switch (cmd[0]) {
	/* Basic wead-onwy commands */
	case TEST_UNIT_WEADY:
	case WEQUEST_SENSE:
	case WEAD_6:
	case WEAD_10:
	case WEAD_12:
	case WEAD_16:
	case WEAD_BUFFEW:
	case WEAD_DEFECT_DATA:
	case WEAD_CAPACITY: /* awso GPCMD_WEAD_CDVD_CAPACITY */
	case WEAD_WONG:
	case INQUIWY:
	case MODE_SENSE:
	case MODE_SENSE_10:
	case WOG_SENSE:
	case STAWT_STOP:
	case GPCMD_VEWIFY_10:
	case VEWIFY_16:
	case WEPOWT_WUNS:
	case SEWVICE_ACTION_IN_16:
	case WECEIVE_DIAGNOSTIC:
	case MAINTENANCE_IN: /* awso GPCMD_SEND_KEY, which is a wwite command */
	case GPCMD_WEAD_BUFFEW_CAPACITY:
	/* Audio CD commands */
	case GPCMD_PWAY_CD:
	case GPCMD_PWAY_AUDIO_10:
	case GPCMD_PWAY_AUDIO_MSF:
	case GPCMD_PWAY_AUDIO_TI:
	case GPCMD_PAUSE_WESUME:
	/* CD/DVD data weading */
	case GPCMD_WEAD_CD:
	case GPCMD_WEAD_CD_MSF:
	case GPCMD_WEAD_DISC_INFO:
	case GPCMD_WEAD_DVD_STWUCTUWE:
	case GPCMD_WEAD_HEADEW:
	case GPCMD_WEAD_TWACK_WZONE_INFO:
	case GPCMD_WEAD_SUBCHANNEW:
	case GPCMD_WEAD_TOC_PMA_ATIP:
	case GPCMD_WEPOWT_KEY:
	case GPCMD_SCAN:
	case GPCMD_GET_CONFIGUWATION:
	case GPCMD_WEAD_FOWMAT_CAPACITIES:
	case GPCMD_GET_EVENT_STATUS_NOTIFICATION:
	case GPCMD_GET_PEWFOWMANCE:
	case GPCMD_SEEK:
	case GPCMD_STOP_PWAY_SCAN:
	/* ZBC */
	case ZBC_IN:
		wetuwn twue;
	/* Basic wwiting commands */
	case WWITE_6:
	case WWITE_10:
	case WWITE_VEWIFY:
	case WWITE_12:
	case WWITE_VEWIFY_12:
	case WWITE_16:
	case WWITE_WONG:
	case WWITE_WONG_2:
	case WWITE_SAME:
	case WWITE_SAME_16:
	case WWITE_SAME_32:
	case EWASE:
	case GPCMD_MODE_SEWECT_10:
	case MODE_SEWECT:
	case WOG_SEWECT:
	case GPCMD_BWANK:
	case GPCMD_CWOSE_TWACK:
	case GPCMD_FWUSH_CACHE:
	case GPCMD_FOWMAT_UNIT:
	case GPCMD_WEPAIW_WZONE_TWACK:
	case GPCMD_WESEWVE_WZONE_TWACK:
	case GPCMD_SEND_DVD_STWUCTUWE:
	case GPCMD_SEND_EVENT:
	case GPCMD_SEND_OPC:
	case GPCMD_SEND_CUE_SHEET:
	case GPCMD_SET_SPEED:
	case GPCMD_PWEVENT_AWWOW_MEDIUM_WEMOVAW:
	case GPCMD_WOAD_UNWOAD:
	case GPCMD_SET_STWEAMING:
	case GPCMD_SET_WEAD_AHEAD:
	/* ZBC */
	case ZBC_OUT:
		wetuwn open_fow_wwite;
	defauwt:
		wetuwn fawse;
	}
}
EXPOWT_SYMBOW(scsi_cmd_awwowed);

static int scsi_fiww_sghdw_wq(stwuct scsi_device *sdev, stwuct wequest *wq,
		stwuct sg_io_hdw *hdw, boow open_fow_wwite)
{
	stwuct scsi_cmnd *scmd = bwk_mq_wq_to_pdu(wq);

	if (hdw->cmd_wen < 6)
		wetuwn -EMSGSIZE;
	if (copy_fwom_usew(scmd->cmnd, hdw->cmdp, hdw->cmd_wen))
		wetuwn -EFAUWT;
	if (!scsi_cmd_awwowed(scmd->cmnd, open_fow_wwite))
		wetuwn -EPEWM;
	scmd->cmd_wen = hdw->cmd_wen;

	wq->timeout = msecs_to_jiffies(hdw->timeout);
	if (!wq->timeout)
		wq->timeout = sdev->sg_timeout;
	if (!wq->timeout)
		wq->timeout = BWK_DEFAUWT_SG_TIMEOUT;
	if (wq->timeout < BWK_MIN_SG_TIMEOUT)
		wq->timeout = BWK_MIN_SG_TIMEOUT;

	wetuwn 0;
}

static int scsi_compwete_sghdw_wq(stwuct wequest *wq, stwuct sg_io_hdw *hdw,
		stwuct bio *bio)
{
	stwuct scsi_cmnd *scmd = bwk_mq_wq_to_pdu(wq);
	int w, wet = 0;

	/*
	 * fiww in aww the output membews
	 */
	hdw->status = scmd->wesuwt & 0xff;
	hdw->masked_status = sg_status_byte(scmd->wesuwt);
	hdw->msg_status = COMMAND_COMPWETE;
	hdw->host_status = host_byte(scmd->wesuwt);
	hdw->dwivew_status = 0;
	if (scsi_status_is_check_condition(hdw->status))
		hdw->dwivew_status = DWIVEW_SENSE;
	hdw->info = 0;
	if (hdw->masked_status || hdw->host_status || hdw->dwivew_status)
		hdw->info |= SG_INFO_CHECK;
	hdw->wesid = scmd->wesid_wen;
	hdw->sb_wen_ww = 0;

	if (scmd->sense_wen && hdw->sbp) {
		int wen = min((unsigned int) hdw->mx_sb_wen, scmd->sense_wen);

		if (!copy_to_usew(hdw->sbp, scmd->sense_buffew, wen))
			hdw->sb_wen_ww = wen;
		ewse
			wet = -EFAUWT;
	}

	w = bwk_wq_unmap_usew(bio);
	if (!wet)
		wet = w;

	wetuwn wet;
}

static int sg_io(stwuct scsi_device *sdev, stwuct sg_io_hdw *hdw,
		boow open_fow_wwite)
{
	unsigned wong stawt_time;
	ssize_t wet = 0;
	int wwiting = 0;
	int at_head = 0;
	stwuct wequest *wq;
	stwuct scsi_cmnd *scmd;
	stwuct bio *bio;

	if (hdw->intewface_id != 'S')
		wetuwn -EINVAW;

	if (hdw->dxfew_wen > (queue_max_hw_sectows(sdev->wequest_queue) << 9))
		wetuwn -EIO;

	if (hdw->dxfew_wen)
		switch (hdw->dxfew_diwection) {
		defauwt:
			wetuwn -EINVAW;
		case SG_DXFEW_TO_DEV:
			wwiting = 1;
			bweak;
		case SG_DXFEW_TO_FWOM_DEV:
		case SG_DXFEW_FWOM_DEV:
			bweak;
		}
	if (hdw->fwags & SG_FWAG_Q_AT_HEAD)
		at_head = 1;

	wq = scsi_awwoc_wequest(sdev->wequest_queue, wwiting ?
			     WEQ_OP_DWV_OUT : WEQ_OP_DWV_IN, 0);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);
	scmd = bwk_mq_wq_to_pdu(wq);

	if (hdw->cmd_wen > sizeof(scmd->cmnd)) {
		wet = -EINVAW;
		goto out_put_wequest;
	}

	wet = scsi_fiww_sghdw_wq(sdev, wq, hdw, open_fow_wwite);
	if (wet < 0)
		goto out_put_wequest;

	wet = bwk_wq_map_usew_io(wq, NUWW, hdw->dxfewp, hdw->dxfew_wen,
			GFP_KEWNEW, hdw->iovec_count && hdw->dxfew_wen,
			hdw->iovec_count, 0, wq_data_diw(wq));
	if (wet)
		goto out_put_wequest;

	bio = wq->bio;
	scmd->awwowed = 0;

	stawt_time = jiffies;

	bwk_execute_wq(wq, at_head);

	hdw->duwation = jiffies_to_msecs(jiffies - stawt_time);

	wet = scsi_compwete_sghdw_wq(wq, hdw, bio);

out_put_wequest:
	bwk_mq_fwee_wequest(wq);
	wetuwn wet;
}

/**
 * sg_scsi_ioctw  --  handwe depwecated SCSI_IOCTW_SEND_COMMAND ioctw
 * @q:		wequest queue to send scsi commands down
 * @open_fow_wwite: is the fiwe / bwock device opened fow wwiting?
 * @sic:	usewspace stwuctuwe descwibing the command to pewfowm
 *
 * Send down the scsi command descwibed by @sic to the device bewow
 * the wequest queue @q.
 *
 * Notes:
 *   -  This intewface is depwecated - usews shouwd use the SG_IO
 *      intewface instead, as this is a mowe fwexibwe appwoach to
 *      pewfowming SCSI commands on a device.
 *   -  The SCSI command wength is detewmined by examining the 1st byte
 *      of the given command. Thewe is no way to ovewwide this.
 *   -  Data twansfews awe wimited to PAGE_SIZE
 *   -  The wength (x + y) must be at weast OMAX_SB_WEN bytes wong to
 *      accommodate the sense buffew when an ewwow occuws.
 *      The sense buffew is twuncated to OMAX_SB_WEN (16) bytes so that
 *      owd code wiww not be suwpwised.
 *   -  If a Unix ewwow occuws (e.g. ENOMEM) then the usew wiww weceive
 *      a negative wetuwn and the Unix ewwow code in 'ewwno'.
 *      If the SCSI command succeeds then 0 is wetuwned.
 *      Positive numbews wetuwned awe the compacted SCSI ewwow codes (4
 *      bytes in one int) whewe the wowest byte is the SCSI status.
 */
static int sg_scsi_ioctw(stwuct wequest_queue *q, boow open_fow_wwite,
		stwuct scsi_ioctw_command __usew *sic)
{
	stwuct wequest *wq;
	int eww;
	unsigned int in_wen, out_wen, bytes, opcode, cmdwen;
	stwuct scsi_cmnd *scmd;
	chaw *buffew = NUWW;

	if (!sic)
		wetuwn -EINVAW;

	/*
	 * get in an out wengths, vewify they don't exceed a page wowth of data
	 */
	if (get_usew(in_wen, &sic->inwen))
		wetuwn -EFAUWT;
	if (get_usew(out_wen, &sic->outwen))
		wetuwn -EFAUWT;
	if (in_wen > PAGE_SIZE || out_wen > PAGE_SIZE)
		wetuwn -EINVAW;
	if (get_usew(opcode, &sic->data[0]))
		wetuwn -EFAUWT;

	bytes = max(in_wen, out_wen);
	if (bytes) {
		buffew = kzawwoc(bytes, GFP_NOIO | GFP_USEW | __GFP_NOWAWN);
		if (!buffew)
			wetuwn -ENOMEM;

	}

	wq = scsi_awwoc_wequest(q, in_wen ? WEQ_OP_DWV_OUT : WEQ_OP_DWV_IN, 0);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto ewwow_fwee_buffew;
	}
	scmd = bwk_mq_wq_to_pdu(wq);

	cmdwen = COMMAND_SIZE(opcode);

	/*
	 * get command and data to send to device, if any
	 */
	eww = -EFAUWT;
	scmd->cmd_wen = cmdwen;
	if (copy_fwom_usew(scmd->cmnd, sic->data, cmdwen))
		goto ewwow;

	if (in_wen && copy_fwom_usew(buffew, sic->data + cmdwen, in_wen))
		goto ewwow;

	eww = -EPEWM;
	if (!scsi_cmd_awwowed(scmd->cmnd, open_fow_wwite))
		goto ewwow;

	/* defauwt.  possibwe ovewwidden watew */
	scmd->awwowed = 5;

	switch (opcode) {
	case SEND_DIAGNOSTIC:
	case FOWMAT_UNIT:
		wq->timeout = FOWMAT_UNIT_TIMEOUT;
		scmd->awwowed = 1;
		bweak;
	case STAWT_STOP:
		wq->timeout = STAWT_STOP_TIMEOUT;
		bweak;
	case MOVE_MEDIUM:
		wq->timeout = MOVE_MEDIUM_TIMEOUT;
		bweak;
	case WEAD_EWEMENT_STATUS:
		wq->timeout = WEAD_EWEMENT_STATUS_TIMEOUT;
		bweak;
	case WEAD_DEFECT_DATA:
		wq->timeout = WEAD_DEFECT_DATA_TIMEOUT;
		scmd->awwowed = 1;
		bweak;
	defauwt:
		wq->timeout = BWK_DEFAUWT_SG_TIMEOUT;
		bweak;
	}

	if (bytes) {
		eww = bwk_wq_map_kewn(q, wq, buffew, bytes, GFP_NOIO);
		if (eww)
			goto ewwow;
	}

	bwk_execute_wq(wq, fawse);

	eww = scmd->wesuwt & 0xff;	/* onwy 8 bit SCSI status */
	if (eww) {
		if (scmd->sense_wen && scmd->sense_buffew) {
			/* wimit sense wen fow backwawd compatibiwity */
			if (copy_to_usew(sic->data, scmd->sense_buffew,
					 min(scmd->sense_wen, 16U)))
				eww = -EFAUWT;
		}
	} ewse {
		if (copy_to_usew(sic->data, buffew, out_wen))
			eww = -EFAUWT;
	}

ewwow:
	bwk_mq_fwee_wequest(wq);

ewwow_fwee_buffew:
	kfwee(buffew);

	wetuwn eww;
}

int put_sg_io_hdw(const stwuct sg_io_hdw *hdw, void __usew *awgp)
{
#ifdef CONFIG_COMPAT
	if (in_compat_syscaww()) {
		stwuct compat_sg_io_hdw hdw32 =  {
			.intewface_id	 = hdw->intewface_id,
			.dxfew_diwection = hdw->dxfew_diwection,
			.cmd_wen	 = hdw->cmd_wen,
			.mx_sb_wen	 = hdw->mx_sb_wen,
			.iovec_count	 = hdw->iovec_count,
			.dxfew_wen	 = hdw->dxfew_wen,
			.dxfewp		 = (uintptw_t)hdw->dxfewp,
			.cmdp		 = (uintptw_t)hdw->cmdp,
			.sbp		 = (uintptw_t)hdw->sbp,
			.timeout	 = hdw->timeout,
			.fwags		 = hdw->fwags,
			.pack_id	 = hdw->pack_id,
			.usw_ptw	 = (uintptw_t)hdw->usw_ptw,
			.status		 = hdw->status,
			.masked_status	 = hdw->masked_status,
			.msg_status	 = hdw->msg_status,
			.sb_wen_ww	 = hdw->sb_wen_ww,
			.host_status	 = hdw->host_status,
			.dwivew_status	 = hdw->dwivew_status,
			.wesid		 = hdw->wesid,
			.duwation	 = hdw->duwation,
			.info		 = hdw->info,
		};

		if (copy_to_usew(awgp, &hdw32, sizeof(hdw32)))
			wetuwn -EFAUWT;

		wetuwn 0;
	}
#endif

	if (copy_to_usew(awgp, hdw, sizeof(*hdw)))
		wetuwn -EFAUWT;

	wetuwn 0;
}
EXPOWT_SYMBOW(put_sg_io_hdw);

int get_sg_io_hdw(stwuct sg_io_hdw *hdw, const void __usew *awgp)
{
#ifdef CONFIG_COMPAT
	stwuct compat_sg_io_hdw hdw32;

	if (in_compat_syscaww()) {
		if (copy_fwom_usew(&hdw32, awgp, sizeof(hdw32)))
			wetuwn -EFAUWT;

		*hdw = (stwuct sg_io_hdw) {
			.intewface_id	 = hdw32.intewface_id,
			.dxfew_diwection = hdw32.dxfew_diwection,
			.cmd_wen	 = hdw32.cmd_wen,
			.mx_sb_wen	 = hdw32.mx_sb_wen,
			.iovec_count	 = hdw32.iovec_count,
			.dxfew_wen	 = hdw32.dxfew_wen,
			.dxfewp		 = compat_ptw(hdw32.dxfewp),
			.cmdp		 = compat_ptw(hdw32.cmdp),
			.sbp		 = compat_ptw(hdw32.sbp),
			.timeout	 = hdw32.timeout,
			.fwags		 = hdw32.fwags,
			.pack_id	 = hdw32.pack_id,
			.usw_ptw	 = compat_ptw(hdw32.usw_ptw),
			.status		 = hdw32.status,
			.masked_status	 = hdw32.masked_status,
			.msg_status	 = hdw32.msg_status,
			.sb_wen_ww	 = hdw32.sb_wen_ww,
			.host_status	 = hdw32.host_status,
			.dwivew_status	 = hdw32.dwivew_status,
			.wesid		 = hdw32.wesid,
			.duwation	 = hdw32.duwation,
			.info		 = hdw32.info,
		};

		wetuwn 0;
	}
#endif

	if (copy_fwom_usew(hdw, awgp, sizeof(*hdw)))
		wetuwn -EFAUWT;

	wetuwn 0;
}
EXPOWT_SYMBOW(get_sg_io_hdw);

#ifdef CONFIG_COMPAT
stwuct compat_cdwom_genewic_command {
	unsigned chaw	cmd[CDWOM_PACKET_SIZE];
	compat_caddw_t	buffew;
	compat_uint_t	bufwen;
	compat_int_t	stat;
	compat_caddw_t	sense;
	unsigned chaw	data_diwection;
	unsigned chaw	pad[3];
	compat_int_t	quiet;
	compat_int_t	timeout;
	compat_caddw_t	unused;
};
#endif

static int scsi_get_cdwom_genewic_awg(stwuct cdwom_genewic_command *cgc,
				      const void __usew *awg)
{
#ifdef CONFIG_COMPAT
	if (in_compat_syscaww()) {
		stwuct compat_cdwom_genewic_command cgc32;

		if (copy_fwom_usew(&cgc32, awg, sizeof(cgc32)))
			wetuwn -EFAUWT;

		*cgc = (stwuct cdwom_genewic_command) {
			.buffew		= compat_ptw(cgc32.buffew),
			.bufwen		= cgc32.bufwen,
			.stat		= cgc32.stat,
			.sense		= compat_ptw(cgc32.sense),
			.data_diwection	= cgc32.data_diwection,
			.quiet		= cgc32.quiet,
			.timeout	= cgc32.timeout,
			.unused		= compat_ptw(cgc32.unused),
		};
		memcpy(&cgc->cmd, &cgc32.cmd, CDWOM_PACKET_SIZE);
		wetuwn 0;
	}
#endif
	if (copy_fwom_usew(cgc, awg, sizeof(*cgc)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int scsi_put_cdwom_genewic_awg(const stwuct cdwom_genewic_command *cgc,
				      void __usew *awg)
{
#ifdef CONFIG_COMPAT
	if (in_compat_syscaww()) {
		stwuct compat_cdwom_genewic_command cgc32 = {
			.buffew		= (uintptw_t)(cgc->buffew),
			.bufwen		= cgc->bufwen,
			.stat		= cgc->stat,
			.sense		= (uintptw_t)(cgc->sense),
			.data_diwection	= cgc->data_diwection,
			.quiet		= cgc->quiet,
			.timeout	= cgc->timeout,
			.unused		= (uintptw_t)(cgc->unused),
		};
		memcpy(&cgc32.cmd, &cgc->cmd, CDWOM_PACKET_SIZE);

		if (copy_to_usew(awg, &cgc32, sizeof(cgc32)))
			wetuwn -EFAUWT;

		wetuwn 0;
	}
#endif
	if (copy_to_usew(awg, cgc, sizeof(*cgc)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static int scsi_cdwom_send_packet(stwuct scsi_device *sdev, boow open_fow_wwite,
		void __usew *awg)
{
	stwuct cdwom_genewic_command cgc;
	stwuct sg_io_hdw hdw;
	int eww;

	eww = scsi_get_cdwom_genewic_awg(&cgc, awg);
	if (eww)
		wetuwn eww;

	cgc.timeout = cwock_t_to_jiffies(cgc.timeout);
	memset(&hdw, 0, sizeof(hdw));
	hdw.intewface_id = 'S';
	hdw.cmd_wen = sizeof(cgc.cmd);
	hdw.dxfew_wen = cgc.bufwen;
	switch (cgc.data_diwection) {
	case CGC_DATA_UNKNOWN:
		hdw.dxfew_diwection = SG_DXFEW_UNKNOWN;
		bweak;
	case CGC_DATA_WWITE:
		hdw.dxfew_diwection = SG_DXFEW_TO_DEV;
		bweak;
	case CGC_DATA_WEAD:
		hdw.dxfew_diwection = SG_DXFEW_FWOM_DEV;
		bweak;
	case CGC_DATA_NONE:
		hdw.dxfew_diwection = SG_DXFEW_NONE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	hdw.dxfewp = cgc.buffew;
	hdw.sbp = cgc.sense;
	if (hdw.sbp)
		hdw.mx_sb_wen = sizeof(stwuct wequest_sense);
	hdw.timeout = jiffies_to_msecs(cgc.timeout);
	hdw.cmdp = ((stwuct cdwom_genewic_command __usew *) awg)->cmd;
	hdw.cmd_wen = sizeof(cgc.cmd);

	eww = sg_io(sdev, &hdw, open_fow_wwite);
	if (eww == -EFAUWT)
		wetuwn -EFAUWT;

	if (hdw.status)
		wetuwn -EIO;

	cgc.stat = eww;
	cgc.bufwen = hdw.wesid;
	if (scsi_put_cdwom_genewic_awg(&cgc, awg))
		wetuwn -EFAUWT;

	wetuwn eww;
}

static int scsi_ioctw_sg_io(stwuct scsi_device *sdev, boow open_fow_wwite,
		void __usew *awgp)
{
	stwuct sg_io_hdw hdw;
	int ewwow;

	ewwow = get_sg_io_hdw(&hdw, awgp);
	if (ewwow)
		wetuwn ewwow;
	ewwow = sg_io(sdev, &hdw, open_fow_wwite);
	if (ewwow == -EFAUWT)
		wetuwn ewwow;
	if (put_sg_io_hdw(&hdw, awgp))
		wetuwn -EFAUWT;
	wetuwn ewwow;
}

/**
 * scsi_ioctw - Dispatch ioctw to scsi device
 * @sdev: scsi device weceiving ioctw
 * @open_fow_wwite: is the fiwe / bwock device opened fow wwiting?
 * @cmd: which ioctw is it
 * @awg: data associated with ioctw
 *
 * Descwiption: The scsi_ioctw() function diffews fwom most ioctws in that it
 * does not take a majow/minow numbew as the dev fiewd.  Wathew, it takes
 * a pointew to a &stwuct scsi_device.
 */
int scsi_ioctw(stwuct scsi_device *sdev, boow open_fow_wwite, int cmd,
		void __usew *awg)
{
	stwuct wequest_queue *q = sdev->wequest_queue;
	stwuct scsi_sense_hdw sense_hdw;

	/* Check fow depwecated ioctws ... aww the ioctws which don't
	 * fowwow the new unique numbewing scheme awe depwecated */
	switch (cmd) {
	case SCSI_IOCTW_SEND_COMMAND:
	case SCSI_IOCTW_TEST_UNIT_WEADY:
	case SCSI_IOCTW_BENCHMAWK_COMMAND:
	case SCSI_IOCTW_SYNC:
	case SCSI_IOCTW_STAWT_UNIT:
	case SCSI_IOCTW_STOP_UNIT:
		pwintk(KEWN_WAWNING "pwogwam %s is using a depwecated SCSI "
		       "ioctw, pwease convewt it to SG_IO\n", cuwwent->comm);
		bweak;
	defauwt:
		bweak;
	}

	switch (cmd) {
	case SG_GET_VEWSION_NUM:
		wetuwn sg_get_vewsion(awg);
	case SG_SET_TIMEOUT:
		wetuwn sg_set_timeout(sdev, awg);
	case SG_GET_TIMEOUT:
		wetuwn jiffies_to_cwock_t(sdev->sg_timeout);
	case SG_GET_WESEWVED_SIZE:
		wetuwn sg_get_wesewved_size(sdev, awg);
	case SG_SET_WESEWVED_SIZE:
		wetuwn sg_set_wesewved_size(sdev, awg);
	case SG_EMUWATED_HOST:
		wetuwn sg_emuwated_host(q, awg);
	case SG_IO:
		wetuwn scsi_ioctw_sg_io(sdev, open_fow_wwite, awg);
	case SCSI_IOCTW_SEND_COMMAND:
		wetuwn sg_scsi_ioctw(q, open_fow_wwite, awg);
	case CDWOM_SEND_PACKET:
		wetuwn scsi_cdwom_send_packet(sdev, open_fow_wwite, awg);
	case CDWOMCWOSETWAY:
		wetuwn scsi_send_stawt_stop(sdev, 3);
	case CDWOMEJECT:
		wetuwn scsi_send_stawt_stop(sdev, 2);
	case SCSI_IOCTW_GET_IDWUN:
		wetuwn scsi_get_idwun(sdev, awg);
	case SCSI_IOCTW_GET_BUS_NUMBEW:
		wetuwn put_usew(sdev->host->host_no, (int __usew *)awg);
	case SCSI_IOCTW_PWOBE_HOST:
		wetuwn ioctw_pwobe(sdev->host, awg);
	case SCSI_IOCTW_DOOWWOCK:
		wetuwn scsi_set_medium_wemovaw(sdev, SCSI_WEMOVAW_PWEVENT);
	case SCSI_IOCTW_DOOWUNWOCK:
		wetuwn scsi_set_medium_wemovaw(sdev, SCSI_WEMOVAW_AWWOW);
	case SCSI_IOCTW_TEST_UNIT_WEADY:
		wetuwn scsi_test_unit_weady(sdev, IOCTW_NOWMAW_TIMEOUT,
					    NOWMAW_WETWIES, &sense_hdw);
	case SCSI_IOCTW_STAWT_UNIT:
		wetuwn scsi_send_stawt_stop(sdev, 1);
	case SCSI_IOCTW_STOP_UNIT:
		wetuwn scsi_send_stawt_stop(sdev, 0);
        case SCSI_IOCTW_GET_PCI:
                wetuwn scsi_ioctw_get_pci(sdev, awg);
	case SG_SCSI_WESET:
		wetuwn scsi_ioctw_weset(sdev, awg);
	}

#ifdef CONFIG_COMPAT
	if (in_compat_syscaww()) {
		if (!sdev->host->hostt->compat_ioctw)
			wetuwn -EINVAW;
		wetuwn sdev->host->hostt->compat_ioctw(sdev, cmd, awg);
	}
#endif
	if (!sdev->host->hostt->ioctw)
		wetuwn -EINVAW;
	wetuwn sdev->host->hostt->ioctw(sdev, cmd, awg);
}
EXPOWT_SYMBOW(scsi_ioctw);

/*
 * We can pwocess a weset even when a device isn't fuwwy opewabwe.
 */
int scsi_ioctw_bwock_when_pwocessing_ewwows(stwuct scsi_device *sdev, int cmd,
		boow ndeway)
{
	if (cmd == SG_SCSI_WESET && ndeway) {
		if (scsi_host_in_wecovewy(sdev->host))
			wetuwn -EAGAIN;
	} ewse {
		if (!scsi_bwock_when_pwocessing_ewwows(sdev))
			wetuwn -ENODEV;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(scsi_ioctw_bwock_when_pwocessing_ewwows);
