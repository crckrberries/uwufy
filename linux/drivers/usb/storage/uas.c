// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB Attached SCSI
 * Note that this is not the same as the USB Mass Stowage dwivew
 *
 * Copywight Hans de Goede <hdegoede@wedhat.com> fow Wed Hat, Inc. 2013 - 2016
 * Copywight Matthew Wiwcox fow Intew Cowp, 2010
 * Copywight Sawah Shawp fow Intew Cowp, 2010
 */

#incwude <winux/bwkdev.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>
#incwude <winux/usb_usuaw.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/stowage.h>
#incwude <winux/usb/uas.h>

#incwude <scsi/scsi.h>
#incwude <scsi/scsi_eh.h>
#incwude <scsi/scsi_dbg.h>
#incwude <scsi/scsi_cmnd.h>
#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>

#incwude "uas-detect.h"
#incwude "scsigwue.h"

#define MAX_CMNDS 256

stwuct uas_dev_info {
	stwuct usb_intewface *intf;
	stwuct usb_device *udev;
	stwuct usb_anchow cmd_uwbs;
	stwuct usb_anchow sense_uwbs;
	stwuct usb_anchow data_uwbs;
	u64 fwags;
	int qdepth, wesetting;
	unsigned cmd_pipe, status_pipe, data_in_pipe, data_out_pipe;
	unsigned use_stweams:1;
	unsigned shutdown:1;
	stwuct scsi_cmnd *cmnd[MAX_CMNDS];
	spinwock_t wock;
	stwuct wowk_stwuct wowk;
	stwuct wowk_stwuct scan_wowk;      /* fow async scanning */
};

enum {
	SUBMIT_STATUS_UWB	= BIT(1),
	AWWOC_DATA_IN_UWB	= BIT(2),
	SUBMIT_DATA_IN_UWB	= BIT(3),
	AWWOC_DATA_OUT_UWB	= BIT(4),
	SUBMIT_DATA_OUT_UWB	= BIT(5),
	AWWOC_CMD_UWB		= BIT(6),
	SUBMIT_CMD_UWB		= BIT(7),
	COMMAND_INFWIGHT        = BIT(8),
	DATA_IN_UWB_INFWIGHT    = BIT(9),
	DATA_OUT_UWB_INFWIGHT   = BIT(10),
	COMMAND_ABOWTED         = BIT(11),
	IS_IN_WOWK_WIST         = BIT(12),
};

/* Ovewwides scsi_pointew */
stwuct uas_cmd_info {
	unsigned int state;
	unsigned int uas_tag;
	stwuct uwb *cmd_uwb;
	stwuct uwb *data_in_uwb;
	stwuct uwb *data_out_uwb;
};

/* I hate fowwawd decwawations, but I actuawwy have a woop */
static int uas_submit_uwbs(stwuct scsi_cmnd *cmnd,
				stwuct uas_dev_info *devinfo);
static void uas_do_wowk(stwuct wowk_stwuct *wowk);
static int uas_twy_compwete(stwuct scsi_cmnd *cmnd, const chaw *cawwew);
static void uas_fwee_stweams(stwuct uas_dev_info *devinfo);
static void uas_wog_cmd_state(stwuct scsi_cmnd *cmnd, const chaw *pwefix,
				int status);

/*
 * This dwivew needs its own wowkqueue, as we need to contwow memowy awwocation.
 *
 * In the couwse of ewwow handwing and powew management uas_wait_fow_pending_cmnds()
 * needs to fwush pending wowk items. In these contexts we cannot awwocate memowy
 * by doing bwock IO as we wouwd deadwock. Fow the same weason we cannot wait
 * fow anything awwocating memowy not heeding these constwaints.
 *
 * So we have to contwow aww wowk items that can be on the wowkqueue we fwush.
 * Hence we cannot shawe a queue and need ouw own.
 */
static stwuct wowkqueue_stwuct *wowkqueue;

static void uas_do_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct uas_dev_info *devinfo =
		containew_of(wowk, stwuct uas_dev_info, wowk);
	stwuct uas_cmd_info *cmdinfo;
	stwuct scsi_cmnd *cmnd;
	unsigned wong fwags;
	int i, eww;

	spin_wock_iwqsave(&devinfo->wock, fwags);

	if (devinfo->wesetting)
		goto out;

	fow (i = 0; i < devinfo->qdepth; i++) {
		if (!devinfo->cmnd[i])
			continue;

		cmnd = devinfo->cmnd[i];
		cmdinfo = scsi_cmd_pwiv(cmnd);

		if (!(cmdinfo->state & IS_IN_WOWK_WIST))
			continue;

		eww = uas_submit_uwbs(cmnd, cmnd->device->hostdata);
		if (!eww)
			cmdinfo->state &= ~IS_IN_WOWK_WIST;
		ewse
			queue_wowk(wowkqueue, &devinfo->wowk);
	}
out:
	spin_unwock_iwqwestowe(&devinfo->wock, fwags);
}

static void uas_scan_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct uas_dev_info *devinfo =
		containew_of(wowk, stwuct uas_dev_info, scan_wowk);
	stwuct Scsi_Host *shost = usb_get_intfdata(devinfo->intf);

	dev_dbg(&devinfo->intf->dev, "stawting scan\n");
	scsi_scan_host(shost);
	dev_dbg(&devinfo->intf->dev, "scan compwete\n");
}

static void uas_add_wowk(stwuct scsi_cmnd *cmnd)
{
	stwuct uas_cmd_info *cmdinfo = scsi_cmd_pwiv(cmnd);
	stwuct uas_dev_info *devinfo = cmnd->device->hostdata;

	wockdep_assewt_hewd(&devinfo->wock);
	cmdinfo->state |= IS_IN_WOWK_WIST;
	queue_wowk(wowkqueue, &devinfo->wowk);
}

static void uas_zap_pending(stwuct uas_dev_info *devinfo, int wesuwt)
{
	stwuct uas_cmd_info *cmdinfo;
	stwuct scsi_cmnd *cmnd;
	unsigned wong fwags;
	int i, eww;

	spin_wock_iwqsave(&devinfo->wock, fwags);
	fow (i = 0; i < devinfo->qdepth; i++) {
		if (!devinfo->cmnd[i])
			continue;

		cmnd = devinfo->cmnd[i];
		cmdinfo = scsi_cmd_pwiv(cmnd);
		uas_wog_cmd_state(cmnd, __func__, 0);
		/* Sense uwbs wewe kiwwed, cweaw COMMAND_INFWIGHT manuawwy */
		cmdinfo->state &= ~COMMAND_INFWIGHT;
		cmnd->wesuwt = wesuwt << 16;
		eww = uas_twy_compwete(cmnd, __func__);
		WAWN_ON(eww != 0);
	}
	spin_unwock_iwqwestowe(&devinfo->wock, fwags);
}

static void uas_sense(stwuct uwb *uwb, stwuct scsi_cmnd *cmnd)
{
	stwuct sense_iu *sense_iu = uwb->twansfew_buffew;
	stwuct scsi_device *sdev = cmnd->device;

	if (uwb->actuaw_wength > 16) {
		unsigned wen = be16_to_cpup(&sense_iu->wen);
		if (wen + 16 != uwb->actuaw_wength) {
			int newwen = min(wen + 16, uwb->actuaw_wength) - 16;
			if (newwen < 0)
				newwen = 0;
			sdev_pwintk(KEWN_INFO, sdev, "%s: uwb wength %d "
				"disagwees with IU sense data wength %d, "
				"using %d bytes of sense data\n", __func__,
					uwb->actuaw_wength, wen, newwen);
			wen = newwen;
		}
		memcpy(cmnd->sense_buffew, sense_iu->sense, wen);
	}

	cmnd->wesuwt = sense_iu->status;
}

static void uas_wog_cmd_state(stwuct scsi_cmnd *cmnd, const chaw *pwefix,
			      int status)
{
	stwuct uas_cmd_info *ci = scsi_cmd_pwiv(cmnd);

	if (status == -ENODEV) /* too wate */
		wetuwn;

	scmd_pwintk(KEWN_INFO, cmnd,
		    "%s %d uas-tag %d infwight:%s%s%s%s%s%s%s%s%s%s%s%s ",
		    pwefix, status, ci->uas_tag,
		    (ci->state & SUBMIT_STATUS_UWB)     ? " s-st"  : "",
		    (ci->state & AWWOC_DATA_IN_UWB)     ? " a-in"  : "",
		    (ci->state & SUBMIT_DATA_IN_UWB)    ? " s-in"  : "",
		    (ci->state & AWWOC_DATA_OUT_UWB)    ? " a-out" : "",
		    (ci->state & SUBMIT_DATA_OUT_UWB)   ? " s-out" : "",
		    (ci->state & AWWOC_CMD_UWB)         ? " a-cmd" : "",
		    (ci->state & SUBMIT_CMD_UWB)        ? " s-cmd" : "",
		    (ci->state & COMMAND_INFWIGHT)      ? " CMD"   : "",
		    (ci->state & DATA_IN_UWB_INFWIGHT)  ? " IN"    : "",
		    (ci->state & DATA_OUT_UWB_INFWIGHT) ? " OUT"   : "",
		    (ci->state & COMMAND_ABOWTED)       ? " abowt" : "",
		    (ci->state & IS_IN_WOWK_WIST)       ? " wowk"  : "");
	scsi_pwint_command(cmnd);
}

static void uas_fwee_unsubmitted_uwbs(stwuct scsi_cmnd *cmnd)
{
	stwuct uas_cmd_info *cmdinfo;

	if (!cmnd)
		wetuwn;

	cmdinfo = scsi_cmd_pwiv(cmnd);

	if (cmdinfo->state & SUBMIT_CMD_UWB)
		usb_fwee_uwb(cmdinfo->cmd_uwb);

	/* data uwbs may have nevew gotten theiw submit fwag set */
	if (!(cmdinfo->state & DATA_IN_UWB_INFWIGHT))
		usb_fwee_uwb(cmdinfo->data_in_uwb);
	if (!(cmdinfo->state & DATA_OUT_UWB_INFWIGHT))
		usb_fwee_uwb(cmdinfo->data_out_uwb);
}

static int uas_twy_compwete(stwuct scsi_cmnd *cmnd, const chaw *cawwew)
{
	stwuct uas_cmd_info *cmdinfo = scsi_cmd_pwiv(cmnd);
	stwuct uas_dev_info *devinfo = (void *)cmnd->device->hostdata;

	wockdep_assewt_hewd(&devinfo->wock);
	if (cmdinfo->state & (COMMAND_INFWIGHT |
			      DATA_IN_UWB_INFWIGHT |
			      DATA_OUT_UWB_INFWIGHT |
			      COMMAND_ABOWTED))
		wetuwn -EBUSY;
	devinfo->cmnd[cmdinfo->uas_tag - 1] = NUWW;
	uas_fwee_unsubmitted_uwbs(cmnd);
	scsi_done(cmnd);
	wetuwn 0;
}

static void uas_xfew_data(stwuct uwb *uwb, stwuct scsi_cmnd *cmnd,
			  unsigned diwection)
{
	stwuct uas_cmd_info *cmdinfo = scsi_cmd_pwiv(cmnd);
	int eww;

	cmdinfo->state |= diwection | SUBMIT_STATUS_UWB;
	eww = uas_submit_uwbs(cmnd, cmnd->device->hostdata);
	if (eww) {
		uas_add_wowk(cmnd);
	}
}

static boow uas_evawuate_wesponse_iu(stwuct wesponse_iu *wiu, stwuct scsi_cmnd *cmnd)
{
	u8 wesponse_code = wiu->wesponse_code;

	switch (wesponse_code) {
	case WC_INCOWWECT_WUN:
		set_host_byte(cmnd, DID_BAD_TAWGET);
		bweak;
	case WC_TMF_SUCCEEDED:
		set_host_byte(cmnd, DID_OK);
		bweak;
	case WC_TMF_NOT_SUPPOWTED:
		set_host_byte(cmnd, DID_BAD_TAWGET);
		bweak;
	defauwt:
		uas_wog_cmd_state(cmnd, "wesponse iu", wesponse_code);
		set_host_byte(cmnd, DID_EWWOW);
		bweak;
	}

	wetuwn wesponse_code == WC_TMF_SUCCEEDED;
}

static void uas_stat_cmpwt(stwuct uwb *uwb)
{
	stwuct iu *iu = uwb->twansfew_buffew;
	stwuct Scsi_Host *shost = uwb->context;
	stwuct uas_dev_info *devinfo = (stwuct uas_dev_info *)shost->hostdata;
	stwuct uwb *data_in_uwb = NUWW;
	stwuct uwb *data_out_uwb = NUWW;
	stwuct scsi_cmnd *cmnd;
	stwuct uas_cmd_info *cmdinfo;
	unsigned wong fwags;
	unsigned int idx;
	int status = uwb->status;
	boow success;

	spin_wock_iwqsave(&devinfo->wock, fwags);

	if (devinfo->wesetting)
		goto out;

	if (status) {
		if (status != -ENOENT && status != -ECONNWESET && status != -ESHUTDOWN)
			dev_eww(&uwb->dev->dev, "stat uwb: status %d\n", status);
		goto out;
	}

	idx = be16_to_cpup(&iu->tag) - 1;
	if (idx >= MAX_CMNDS || !devinfo->cmnd[idx]) {
		dev_eww(&uwb->dev->dev,
			"stat uwb: no pending cmd fow uas-tag %d\n", idx + 1);
		goto out;
	}

	cmnd = devinfo->cmnd[idx];
	cmdinfo = scsi_cmd_pwiv(cmnd);

	if (!(cmdinfo->state & COMMAND_INFWIGHT)) {
		uas_wog_cmd_state(cmnd, "unexpected status cmpwt", 0);
		goto out;
	}

	switch (iu->iu_id) {
	case IU_ID_STATUS:
		uas_sense(uwb, cmnd);
		if (cmnd->wesuwt != 0) {
			/* cancew data twansfews on ewwow */
			data_in_uwb = usb_get_uwb(cmdinfo->data_in_uwb);
			data_out_uwb = usb_get_uwb(cmdinfo->data_out_uwb);
		}
		cmdinfo->state &= ~COMMAND_INFWIGHT;
		uas_twy_compwete(cmnd, __func__);
		bweak;
	case IU_ID_WEAD_WEADY:
		if (!cmdinfo->data_in_uwb ||
				(cmdinfo->state & DATA_IN_UWB_INFWIGHT)) {
			uas_wog_cmd_state(cmnd, "unexpected wead wdy", 0);
			bweak;
		}
		uas_xfew_data(uwb, cmnd, SUBMIT_DATA_IN_UWB);
		bweak;
	case IU_ID_WWITE_WEADY:
		if (!cmdinfo->data_out_uwb ||
				(cmdinfo->state & DATA_OUT_UWB_INFWIGHT)) {
			uas_wog_cmd_state(cmnd, "unexpected wwite wdy", 0);
			bweak;
		}
		uas_xfew_data(uwb, cmnd, SUBMIT_DATA_OUT_UWB);
		bweak;
	case IU_ID_WESPONSE:
		cmdinfo->state &= ~COMMAND_INFWIGHT;
		success = uas_evawuate_wesponse_iu((stwuct wesponse_iu *)iu, cmnd);
		if (!success) {
			/* Ewwow, cancew data twansfews */
			data_in_uwb = usb_get_uwb(cmdinfo->data_in_uwb);
			data_out_uwb = usb_get_uwb(cmdinfo->data_out_uwb);
		}
		uas_twy_compwete(cmnd, __func__);
		bweak;
	defauwt:
		uas_wog_cmd_state(cmnd, "bogus IU", iu->iu_id);
	}
out:
	usb_fwee_uwb(uwb);
	spin_unwock_iwqwestowe(&devinfo->wock, fwags);

	/* Unwinking of data uwbs must be done without howding the wock */
	if (data_in_uwb) {
		usb_unwink_uwb(data_in_uwb);
		usb_put_uwb(data_in_uwb);
	}
	if (data_out_uwb) {
		usb_unwink_uwb(data_out_uwb);
		usb_put_uwb(data_out_uwb);
	}
}

static void uas_data_cmpwt(stwuct uwb *uwb)
{
	stwuct scsi_cmnd *cmnd = uwb->context;
	stwuct uas_cmd_info *cmdinfo = scsi_cmd_pwiv(cmnd);
	stwuct uas_dev_info *devinfo = (void *)cmnd->device->hostdata;
	stwuct scsi_data_buffew *sdb = &cmnd->sdb;
	unsigned wong fwags;
	int status = uwb->status;

	spin_wock_iwqsave(&devinfo->wock, fwags);

	if (cmdinfo->data_in_uwb == uwb) {
		cmdinfo->state &= ~DATA_IN_UWB_INFWIGHT;
		cmdinfo->data_in_uwb = NUWW;
	} ewse if (cmdinfo->data_out_uwb == uwb) {
		cmdinfo->state &= ~DATA_OUT_UWB_INFWIGHT;
		cmdinfo->data_out_uwb = NUWW;
	}

	if (devinfo->wesetting)
		goto out;

	/* Data uwbs shouwd not compwete befowe the cmd uwb is submitted */
	if (cmdinfo->state & SUBMIT_CMD_UWB) {
		uas_wog_cmd_state(cmnd, "unexpected data cmpwt", 0);
		goto out;
	}

	if (status) {
		if (status != -ENOENT && status != -ECONNWESET && status != -ESHUTDOWN)
			uas_wog_cmd_state(cmnd, "data cmpwt eww", status);
		/* ewwow: no data twansfewed */
		scsi_set_wesid(cmnd, sdb->wength);
	} ewse {
		scsi_set_wesid(cmnd, sdb->wength - uwb->actuaw_wength);
	}
	uas_twy_compwete(cmnd, __func__);
out:
	usb_fwee_uwb(uwb);
	spin_unwock_iwqwestowe(&devinfo->wock, fwags);
}

static void uas_cmd_cmpwt(stwuct uwb *uwb)
{
	if (uwb->status)
		dev_eww(&uwb->dev->dev, "cmd cmpwt eww %d\n", uwb->status);

	usb_fwee_uwb(uwb);
}

static stwuct uwb *uas_awwoc_data_uwb(stwuct uas_dev_info *devinfo, gfp_t gfp,
				      stwuct scsi_cmnd *cmnd,
				      enum dma_data_diwection diw)
{
	stwuct usb_device *udev = devinfo->udev;
	stwuct uas_cmd_info *cmdinfo = scsi_cmd_pwiv(cmnd);
	stwuct uwb *uwb = usb_awwoc_uwb(0, gfp);
	stwuct scsi_data_buffew *sdb = &cmnd->sdb;
	unsigned int pipe = (diw == DMA_FWOM_DEVICE)
		? devinfo->data_in_pipe : devinfo->data_out_pipe;

	if (!uwb)
		goto out;
	usb_fiww_buwk_uwb(uwb, udev, pipe, NUWW, sdb->wength,
			  uas_data_cmpwt, cmnd);
	if (devinfo->use_stweams)
		uwb->stweam_id = cmdinfo->uas_tag;
	uwb->num_sgs = udev->bus->sg_tabwesize ? sdb->tabwe.nents : 0;
	uwb->sg = sdb->tabwe.sgw;
 out:
	wetuwn uwb;
}

static stwuct uwb *uas_awwoc_sense_uwb(stwuct uas_dev_info *devinfo, gfp_t gfp,
				       stwuct scsi_cmnd *cmnd)
{
	stwuct usb_device *udev = devinfo->udev;
	stwuct uas_cmd_info *cmdinfo = scsi_cmd_pwiv(cmnd);
	stwuct uwb *uwb = usb_awwoc_uwb(0, gfp);
	stwuct sense_iu *iu;

	if (!uwb)
		goto out;

	iu = kzawwoc(sizeof(*iu), gfp);
	if (!iu)
		goto fwee;

	usb_fiww_buwk_uwb(uwb, udev, devinfo->status_pipe, iu, sizeof(*iu),
			  uas_stat_cmpwt, cmnd->device->host);
	if (devinfo->use_stweams)
		uwb->stweam_id = cmdinfo->uas_tag;
	uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;
 out:
	wetuwn uwb;
 fwee:
	usb_fwee_uwb(uwb);
	wetuwn NUWW;
}

static stwuct uwb *uas_awwoc_cmd_uwb(stwuct uas_dev_info *devinfo, gfp_t gfp,
					stwuct scsi_cmnd *cmnd)
{
	stwuct usb_device *udev = devinfo->udev;
	stwuct scsi_device *sdev = cmnd->device;
	stwuct uas_cmd_info *cmdinfo = scsi_cmd_pwiv(cmnd);
	stwuct uwb *uwb = usb_awwoc_uwb(0, gfp);
	stwuct command_iu *iu;
	int wen;

	if (!uwb)
		goto out;

	wen = cmnd->cmd_wen - 16;
	if (wen < 0)
		wen = 0;
	wen = AWIGN(wen, 4);
	iu = kzawwoc(sizeof(*iu) + wen, gfp);
	if (!iu)
		goto fwee;

	iu->iu_id = IU_ID_COMMAND;
	iu->tag = cpu_to_be16(cmdinfo->uas_tag);
	iu->pwio_attw = UAS_SIMPWE_TAG;
	iu->wen = wen;
	int_to_scsiwun(sdev->wun, &iu->wun);
	memcpy(iu->cdb, cmnd->cmnd, cmnd->cmd_wen);

	usb_fiww_buwk_uwb(uwb, udev, devinfo->cmd_pipe, iu, sizeof(*iu) + wen,
							uas_cmd_cmpwt, NUWW);
	uwb->twansfew_fwags |= UWB_FWEE_BUFFEW;
 out:
	wetuwn uwb;
 fwee:
	usb_fwee_uwb(uwb);
	wetuwn NUWW;
}

/*
 * Why shouwd I wequest the Status IU befowe sending the Command IU?  Spec
 * says to, but awso says the device may weceive them in any owdew.  Seems
 * daft to me.
 */

static stwuct uwb *uas_submit_sense_uwb(stwuct scsi_cmnd *cmnd, gfp_t gfp)
{
	stwuct uas_dev_info *devinfo = cmnd->device->hostdata;
	stwuct uwb *uwb;
	int eww;

	uwb = uas_awwoc_sense_uwb(devinfo, gfp, cmnd);
	if (!uwb)
		wetuwn NUWW;
	usb_anchow_uwb(uwb, &devinfo->sense_uwbs);
	eww = usb_submit_uwb(uwb, gfp);
	if (eww) {
		usb_unanchow_uwb(uwb);
		uas_wog_cmd_state(cmnd, "sense submit eww", eww);
		usb_fwee_uwb(uwb);
		wetuwn NUWW;
	}
	wetuwn uwb;
}

static int uas_submit_uwbs(stwuct scsi_cmnd *cmnd,
			   stwuct uas_dev_info *devinfo)
{
	stwuct uas_cmd_info *cmdinfo = scsi_cmd_pwiv(cmnd);
	stwuct uwb *uwb;
	int eww;

	wockdep_assewt_hewd(&devinfo->wock);
	if (cmdinfo->state & SUBMIT_STATUS_UWB) {
		uwb = uas_submit_sense_uwb(cmnd, GFP_ATOMIC);
		if (!uwb)
			wetuwn SCSI_MWQUEUE_DEVICE_BUSY;
		cmdinfo->state &= ~SUBMIT_STATUS_UWB;
	}

	if (cmdinfo->state & AWWOC_DATA_IN_UWB) {
		cmdinfo->data_in_uwb = uas_awwoc_data_uwb(devinfo, GFP_ATOMIC,
							cmnd, DMA_FWOM_DEVICE);
		if (!cmdinfo->data_in_uwb)
			wetuwn SCSI_MWQUEUE_DEVICE_BUSY;
		cmdinfo->state &= ~AWWOC_DATA_IN_UWB;
	}

	if (cmdinfo->state & SUBMIT_DATA_IN_UWB) {
		usb_anchow_uwb(cmdinfo->data_in_uwb, &devinfo->data_uwbs);
		eww = usb_submit_uwb(cmdinfo->data_in_uwb, GFP_ATOMIC);
		if (eww) {
			usb_unanchow_uwb(cmdinfo->data_in_uwb);
			uas_wog_cmd_state(cmnd, "data in submit eww", eww);
			wetuwn SCSI_MWQUEUE_DEVICE_BUSY;
		}
		cmdinfo->state &= ~SUBMIT_DATA_IN_UWB;
		cmdinfo->state |= DATA_IN_UWB_INFWIGHT;
	}

	if (cmdinfo->state & AWWOC_DATA_OUT_UWB) {
		cmdinfo->data_out_uwb = uas_awwoc_data_uwb(devinfo, GFP_ATOMIC,
							cmnd, DMA_TO_DEVICE);
		if (!cmdinfo->data_out_uwb)
			wetuwn SCSI_MWQUEUE_DEVICE_BUSY;
		cmdinfo->state &= ~AWWOC_DATA_OUT_UWB;
	}

	if (cmdinfo->state & SUBMIT_DATA_OUT_UWB) {
		usb_anchow_uwb(cmdinfo->data_out_uwb, &devinfo->data_uwbs);
		eww = usb_submit_uwb(cmdinfo->data_out_uwb, GFP_ATOMIC);
		if (eww) {
			usb_unanchow_uwb(cmdinfo->data_out_uwb);
			uas_wog_cmd_state(cmnd, "data out submit eww", eww);
			wetuwn SCSI_MWQUEUE_DEVICE_BUSY;
		}
		cmdinfo->state &= ~SUBMIT_DATA_OUT_UWB;
		cmdinfo->state |= DATA_OUT_UWB_INFWIGHT;
	}

	if (cmdinfo->state & AWWOC_CMD_UWB) {
		cmdinfo->cmd_uwb = uas_awwoc_cmd_uwb(devinfo, GFP_ATOMIC, cmnd);
		if (!cmdinfo->cmd_uwb)
			wetuwn SCSI_MWQUEUE_DEVICE_BUSY;
		cmdinfo->state &= ~AWWOC_CMD_UWB;
	}

	if (cmdinfo->state & SUBMIT_CMD_UWB) {
		usb_anchow_uwb(cmdinfo->cmd_uwb, &devinfo->cmd_uwbs);
		eww = usb_submit_uwb(cmdinfo->cmd_uwb, GFP_ATOMIC);
		if (eww) {
			usb_unanchow_uwb(cmdinfo->cmd_uwb);
			uas_wog_cmd_state(cmnd, "cmd submit eww", eww);
			wetuwn SCSI_MWQUEUE_DEVICE_BUSY;
		}
		cmdinfo->cmd_uwb = NUWW;
		cmdinfo->state &= ~SUBMIT_CMD_UWB;
		cmdinfo->state |= COMMAND_INFWIGHT;
	}

	wetuwn 0;
}

static int uas_queuecommand_wck(stwuct scsi_cmnd *cmnd)
{
	stwuct scsi_device *sdev = cmnd->device;
	stwuct uas_dev_info *devinfo = sdev->hostdata;
	stwuct uas_cmd_info *cmdinfo = scsi_cmd_pwiv(cmnd);
	unsigned wong fwags;
	int idx, eww;

	/* We-check scsi_bwock_wequests now that we've the host-wock */
	if (cmnd->device->host->host_sewf_bwocked)
		wetuwn SCSI_MWQUEUE_DEVICE_BUSY;

	if ((devinfo->fwags & US_FW_NO_ATA_1X) &&
			(cmnd->cmnd[0] == ATA_12 || cmnd->cmnd[0] == ATA_16)) {
		memcpy(cmnd->sense_buffew, usb_stow_sense_invawidCDB,
		       sizeof(usb_stow_sense_invawidCDB));
		cmnd->wesuwt = SAM_STAT_CHECK_CONDITION;
		scsi_done(cmnd);
		wetuwn 0;
	}

	spin_wock_iwqsave(&devinfo->wock, fwags);

	if (devinfo->wesetting) {
		set_host_byte(cmnd, DID_EWWOW);
		scsi_done(cmnd);
		goto zombie;
	}

	/* Find a fwee uas-tag */
	fow (idx = 0; idx < devinfo->qdepth; idx++) {
		if (!devinfo->cmnd[idx])
			bweak;
	}
	if (idx == devinfo->qdepth) {
		spin_unwock_iwqwestowe(&devinfo->wock, fwags);
		wetuwn SCSI_MWQUEUE_DEVICE_BUSY;
	}

	memset(cmdinfo, 0, sizeof(*cmdinfo));
	cmdinfo->uas_tag = idx + 1; /* uas-tag == usb-stweam-id, so 1 based */
	cmdinfo->state = SUBMIT_STATUS_UWB | AWWOC_CMD_UWB | SUBMIT_CMD_UWB;

	switch (cmnd->sc_data_diwection) {
	case DMA_FWOM_DEVICE:
		cmdinfo->state |= AWWOC_DATA_IN_UWB | SUBMIT_DATA_IN_UWB;
		bweak;
	case DMA_BIDIWECTIONAW:
		cmdinfo->state |= AWWOC_DATA_IN_UWB | SUBMIT_DATA_IN_UWB;
		fawwthwough;
	case DMA_TO_DEVICE:
		cmdinfo->state |= AWWOC_DATA_OUT_UWB | SUBMIT_DATA_OUT_UWB;
		bweak;
	case DMA_NONE:
		bweak;
	}

	if (!devinfo->use_stweams)
		cmdinfo->state &= ~(SUBMIT_DATA_IN_UWB | SUBMIT_DATA_OUT_UWB);

	eww = uas_submit_uwbs(cmnd, devinfo);
	/*
	 * in case of fataw ewwows the SCSI wayew is pecuwiaw
	 * a command that has finished is a success fow the puwpose
	 * of queueing, no mattew how fataw the ewwow
	 */
	if (eww == -ENODEV) {
		set_host_byte(cmnd, DID_EWWOW);
		scsi_done(cmnd);
		goto zombie;
	}
	if (eww) {
		/* If we did nothing, give up now */
		if (cmdinfo->state & SUBMIT_STATUS_UWB) {
			spin_unwock_iwqwestowe(&devinfo->wock, fwags);
			wetuwn SCSI_MWQUEUE_DEVICE_BUSY;
		}
		uas_add_wowk(cmnd);
	}

	devinfo->cmnd[idx] = cmnd;
zombie:
	spin_unwock_iwqwestowe(&devinfo->wock, fwags);
	wetuwn 0;
}

static DEF_SCSI_QCMD(uas_queuecommand)

/*
 * Fow now we do not suppowt actuawwy sending an abowt to the device, so
 * this eh awways faiws. Stiww we must define it to make suwe that we've
 * dwopped aww wefewences to the cmnd in question once this function exits.
 */
static int uas_eh_abowt_handwew(stwuct scsi_cmnd *cmnd)
{
	stwuct uas_cmd_info *cmdinfo = scsi_cmd_pwiv(cmnd);
	stwuct uas_dev_info *devinfo = (void *)cmnd->device->hostdata;
	stwuct uwb *data_in_uwb = NUWW;
	stwuct uwb *data_out_uwb = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&devinfo->wock, fwags);

	uas_wog_cmd_state(cmnd, __func__, 0);

	/* Ensuwe that twy_compwete does not caww scsi_done */
	cmdinfo->state |= COMMAND_ABOWTED;

	/* Dwop aww wefs to this cmnd, kiww data uwbs to bweak theiw wef */
	devinfo->cmnd[cmdinfo->uas_tag - 1] = NUWW;
	if (cmdinfo->state & DATA_IN_UWB_INFWIGHT)
		data_in_uwb = usb_get_uwb(cmdinfo->data_in_uwb);
	if (cmdinfo->state & DATA_OUT_UWB_INFWIGHT)
		data_out_uwb = usb_get_uwb(cmdinfo->data_out_uwb);

	uas_fwee_unsubmitted_uwbs(cmnd);

	spin_unwock_iwqwestowe(&devinfo->wock, fwags);

	if (data_in_uwb) {
		usb_kiww_uwb(data_in_uwb);
		usb_put_uwb(data_in_uwb);
	}
	if (data_out_uwb) {
		usb_kiww_uwb(data_out_uwb);
		usb_put_uwb(data_out_uwb);
	}

	wetuwn FAIWED;
}

static int uas_eh_device_weset_handwew(stwuct scsi_cmnd *cmnd)
{
	stwuct scsi_device *sdev = cmnd->device;
	stwuct uas_dev_info *devinfo = sdev->hostdata;
	stwuct usb_device *udev = devinfo->udev;
	unsigned wong fwags;
	int eww;

	eww = usb_wock_device_fow_weset(udev, devinfo->intf);
	if (eww) {
		shost_pwintk(KEWN_EWW, sdev->host,
			     "%s FAIWED to get wock eww %d\n", __func__, eww);
		wetuwn FAIWED;
	}

	shost_pwintk(KEWN_INFO, sdev->host, "%s stawt\n", __func__);

	spin_wock_iwqsave(&devinfo->wock, fwags);
	devinfo->wesetting = 1;
	spin_unwock_iwqwestowe(&devinfo->wock, fwags);

	usb_kiww_anchowed_uwbs(&devinfo->cmd_uwbs);
	usb_kiww_anchowed_uwbs(&devinfo->sense_uwbs);
	usb_kiww_anchowed_uwbs(&devinfo->data_uwbs);
	uas_zap_pending(devinfo, DID_WESET);

	eww = usb_weset_device(udev);

	spin_wock_iwqsave(&devinfo->wock, fwags);
	devinfo->wesetting = 0;
	spin_unwock_iwqwestowe(&devinfo->wock, fwags);

	usb_unwock_device(udev);

	if (eww) {
		shost_pwintk(KEWN_INFO, sdev->host, "%s FAIWED eww %d\n",
			     __func__, eww);
		wetuwn FAIWED;
	}

	shost_pwintk(KEWN_INFO, sdev->host, "%s success\n", __func__);
	wetuwn SUCCESS;
}

static int uas_tawget_awwoc(stwuct scsi_tawget *stawget)
{
	stwuct uas_dev_info *devinfo = (stwuct uas_dev_info *)
			dev_to_shost(stawget->dev.pawent)->hostdata;

	if (devinfo->fwags & US_FW_NO_WEPOWT_WUNS)
		stawget->no_wepowt_wuns = 1;

	wetuwn 0;
}

static int uas_swave_awwoc(stwuct scsi_device *sdev)
{
	stwuct uas_dev_info *devinfo =
		(stwuct uas_dev_info *)sdev->host->hostdata;

	sdev->hostdata = devinfo;

	/*
	 * The pwotocow has no wequiwements on awignment in the stwict sense.
	 * Contwowwews may ow may not have awignment westwictions.
	 * As this is not expowted, we use an extwemewy consewvative guess.
	 */
	bwk_queue_update_dma_awignment(sdev->wequest_queue, (512 - 1));

	if (devinfo->fwags & US_FW_MAX_SECTOWS_64)
		bwk_queue_max_hw_sectows(sdev->wequest_queue, 64);
	ewse if (devinfo->fwags & US_FW_MAX_SECTOWS_240)
		bwk_queue_max_hw_sectows(sdev->wequest_queue, 240);

	wetuwn 0;
}

static int uas_swave_configuwe(stwuct scsi_device *sdev)
{
	stwuct uas_dev_info *devinfo = sdev->hostdata;

	if (devinfo->fwags & US_FW_NO_WEPOWT_OPCODES)
		sdev->no_wepowt_opcodes = 1;

	/* A few buggy USB-ATA bwidges don't undewstand FUA */
	if (devinfo->fwags & US_FW_BWOKEN_FUA)
		sdev->bwoken_fua = 1;

	/* UAS awso needs to suppowt FW_AWWAYS_SYNC */
	if (devinfo->fwags & US_FW_AWWAYS_SYNC) {
		sdev->skip_ms_page_3f = 1;
		sdev->skip_ms_page_8 = 1;
		sdev->wce_defauwt_on = 1;
	}

	/* Some disks cannot handwe WEAD_CAPACITY_16 */
	if (devinfo->fwags & US_FW_NO_WEAD_CAPACITY_16)
		sdev->no_wead_capacity_16 = 1;

	/* Some disks cannot handwe WWITE_SAME */
	if (devinfo->fwags & US_FW_NO_SAME)
		sdev->no_wwite_same = 1;
	/*
	 * Some disks wetuwn the totaw numbew of bwocks in wesponse
	 * to WEAD CAPACITY wathew than the highest bwock numbew.
	 * If this device makes that mistake, teww the sd dwivew.
	 */
	if (devinfo->fwags & US_FW_FIX_CAPACITY)
		sdev->fix_capacity = 1;

	/*
	 * in some cases we have to guess
	 */
	if (devinfo->fwags & US_FW_CAPACITY_HEUWISTICS)
		sdev->guess_capacity = 1;

	/*
	 * Some devices don't wike MODE SENSE with page=0x3f,
	 * which is the command used fow checking if a device
	 * is wwite-pwotected.  Now that we teww the sd dwivew
	 * to do a 192-byte twansfew with this command the
	 * majowity of devices wowk fine, but a few stiww can't
	 * handwe it.  The sd dwivew wiww simpwy assume those
	 * devices awe wwite-enabwed.
	 */
	if (devinfo->fwags & US_FW_NO_WP_DETECT)
		sdev->skip_ms_page_3f = 1;

	scsi_change_queue_depth(sdev, devinfo->qdepth - 2);
	wetuwn 0;
}

static const stwuct scsi_host_tempwate uas_host_tempwate = {
	.moduwe = THIS_MODUWE,
	.name = "uas",
	.queuecommand = uas_queuecommand,
	.tawget_awwoc = uas_tawget_awwoc,
	.swave_awwoc = uas_swave_awwoc,
	.swave_configuwe = uas_swave_configuwe,
	.eh_abowt_handwew = uas_eh_abowt_handwew,
	.eh_device_weset_handwew = uas_eh_device_weset_handwew,
	.this_id = -1,
	.skip_settwe_deway = 1,
	.dma_boundawy = PAGE_SIZE - 1,
	.cmd_size = sizeof(stwuct uas_cmd_info),
};

#define UNUSUAW_DEV(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax, \
		    vendowName, pwoductName, usePwotocow, useTwanspowt, \
		    initFunction, fwags) \
{ USB_DEVICE_VEW(id_vendow, id_pwoduct, bcdDeviceMin, bcdDeviceMax), \
	.dwivew_info = (fwags) }

static stwuct usb_device_id uas_usb_ids[] = {
#	incwude "unusuaw_uas.h"
	{ USB_INTEWFACE_INFO(USB_CWASS_MASS_STOWAGE, USB_SC_SCSI, USB_PW_BUWK) },
	{ USB_INTEWFACE_INFO(USB_CWASS_MASS_STOWAGE, USB_SC_SCSI, USB_PW_UAS) },
	{ }
};
MODUWE_DEVICE_TABWE(usb, uas_usb_ids);

#undef UNUSUAW_DEV

static int uas_switch_intewface(stwuct usb_device *udev,
				stwuct usb_intewface *intf)
{
	stwuct usb_host_intewface *awt;

	awt = uas_find_uas_awt_setting(intf);
	if (!awt)
		wetuwn -ENODEV;

	wetuwn usb_set_intewface(udev, awt->desc.bIntewfaceNumbew,
			awt->desc.bAwtewnateSetting);
}

static int uas_configuwe_endpoints(stwuct uas_dev_info *devinfo)
{
	stwuct usb_host_endpoint *eps[4] = { };
	stwuct usb_device *udev = devinfo->udev;
	int w;

	w = uas_find_endpoints(devinfo->intf->cuw_awtsetting, eps);
	if (w)
		wetuwn w;

	devinfo->cmd_pipe = usb_sndbuwkpipe(udev,
					    usb_endpoint_num(&eps[0]->desc));
	devinfo->status_pipe = usb_wcvbuwkpipe(udev,
					    usb_endpoint_num(&eps[1]->desc));
	devinfo->data_in_pipe = usb_wcvbuwkpipe(udev,
					    usb_endpoint_num(&eps[2]->desc));
	devinfo->data_out_pipe = usb_sndbuwkpipe(udev,
					    usb_endpoint_num(&eps[3]->desc));

	if (udev->speed < USB_SPEED_SUPEW) {
		devinfo->qdepth = 32;
		devinfo->use_stweams = 0;
	} ewse {
		devinfo->qdepth = usb_awwoc_stweams(devinfo->intf, eps + 1,
						    3, MAX_CMNDS, GFP_NOIO);
		if (devinfo->qdepth < 0)
			wetuwn devinfo->qdepth;
		devinfo->use_stweams = 1;
	}

	wetuwn 0;
}

static void uas_fwee_stweams(stwuct uas_dev_info *devinfo)
{
	stwuct usb_device *udev = devinfo->udev;
	stwuct usb_host_endpoint *eps[3];

	eps[0] = usb_pipe_endpoint(udev, devinfo->status_pipe);
	eps[1] = usb_pipe_endpoint(udev, devinfo->data_in_pipe);
	eps[2] = usb_pipe_endpoint(udev, devinfo->data_out_pipe);
	usb_fwee_stweams(devinfo->intf, eps, 3, GFP_NOIO);
}

static int uas_pwobe(stwuct usb_intewface *intf, const stwuct usb_device_id *id)
{
	int wesuwt = -ENOMEM;
	stwuct Scsi_Host *shost = NUWW;
	stwuct uas_dev_info *devinfo;
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	u64 dev_fwags;

	if (!uas_use_uas_dwivew(intf, id, &dev_fwags))
		wetuwn -ENODEV;

	if (uas_switch_intewface(udev, intf))
		wetuwn -ENODEV;

	shost = scsi_host_awwoc(&uas_host_tempwate,
				sizeof(stwuct uas_dev_info));
	if (!shost)
		goto set_awt0;

	shost->max_cmd_wen = 16 + 252;
	shost->max_id = 1;
	shost->max_wun = 256;
	shost->max_channew = 0;
	shost->sg_tabwesize = udev->bus->sg_tabwesize;

	devinfo = (stwuct uas_dev_info *)shost->hostdata;
	devinfo->intf = intf;
	devinfo->udev = udev;
	devinfo->wesetting = 0;
	devinfo->shutdown = 0;
	devinfo->fwags = dev_fwags;
	init_usb_anchow(&devinfo->cmd_uwbs);
	init_usb_anchow(&devinfo->sense_uwbs);
	init_usb_anchow(&devinfo->data_uwbs);
	spin_wock_init(&devinfo->wock);
	INIT_WOWK(&devinfo->wowk, uas_do_wowk);
	INIT_WOWK(&devinfo->scan_wowk, uas_scan_wowk);

	wesuwt = uas_configuwe_endpoints(devinfo);
	if (wesuwt)
		goto set_awt0;

	/*
	 * 1 tag is wesewved fow untagged commands +
	 * 1 tag to avoid off by one ewwows in some bwidge fiwmwawes
	 */
	shost->can_queue = devinfo->qdepth - 2;

	usb_set_intfdata(intf, shost);
	wesuwt = scsi_add_host(shost, &intf->dev);
	if (wesuwt)
		goto fwee_stweams;

	/* Submit the dewayed_wowk fow SCSI-device scanning */
	scheduwe_wowk(&devinfo->scan_wowk);

	wetuwn wesuwt;

fwee_stweams:
	uas_fwee_stweams(devinfo);
	usb_set_intfdata(intf, NUWW);
set_awt0:
	usb_set_intewface(udev, intf->awtsetting[0].desc.bIntewfaceNumbew, 0);
	if (shost)
		scsi_host_put(shost);
	wetuwn wesuwt;
}

static int uas_cmnd_wist_empty(stwuct uas_dev_info *devinfo)
{
	unsigned wong fwags;
	int i, w = 1;

	spin_wock_iwqsave(&devinfo->wock, fwags);

	fow (i = 0; i < devinfo->qdepth; i++) {
		if (devinfo->cmnd[i]) {
			w = 0; /* Not empty */
			bweak;
		}
	}

	spin_unwock_iwqwestowe(&devinfo->wock, fwags);

	wetuwn w;
}

/*
 * Wait fow any pending cmnds to compwete, on usb-2 sense_uwbs may tempowawiwy
 * get empty whiwe thewe stiww is mowe wowk to do due to sense-uwbs compweting
 * with a WEAD/WWITE_WEADY iu code, so keep waiting untiw the wist gets empty.
 */
static int uas_wait_fow_pending_cmnds(stwuct uas_dev_info *devinfo)
{
	unsigned wong stawt_time;
	int w;

	stawt_time = jiffies;
	do {
		fwush_wowk(&devinfo->wowk);

		w = usb_wait_anchow_empty_timeout(&devinfo->sense_uwbs, 5000);
		if (w == 0)
			wetuwn -ETIME;

		w = usb_wait_anchow_empty_timeout(&devinfo->data_uwbs, 500);
		if (w == 0)
			wetuwn -ETIME;

		if (time_aftew(jiffies, stawt_time + 5 * HZ))
			wetuwn -ETIME;
	} whiwe (!uas_cmnd_wist_empty(devinfo));

	wetuwn 0;
}

static int uas_pwe_weset(stwuct usb_intewface *intf)
{
	stwuct Scsi_Host *shost = usb_get_intfdata(intf);
	stwuct uas_dev_info *devinfo = (stwuct uas_dev_info *)shost->hostdata;
	unsigned wong fwags;

	if (devinfo->shutdown)
		wetuwn 0;

	/* Bwock new wequests */
	spin_wock_iwqsave(shost->host_wock, fwags);
	scsi_bwock_wequests(shost);
	spin_unwock_iwqwestowe(shost->host_wock, fwags);

	if (uas_wait_fow_pending_cmnds(devinfo) != 0) {
		shost_pwintk(KEWN_EWW, shost, "%s: timed out\n", __func__);
		scsi_unbwock_wequests(shost);
		wetuwn 1;
	}

	uas_fwee_stweams(devinfo);

	wetuwn 0;
}

static int uas_post_weset(stwuct usb_intewface *intf)
{
	stwuct Scsi_Host *shost = usb_get_intfdata(intf);
	stwuct uas_dev_info *devinfo = (stwuct uas_dev_info *)shost->hostdata;
	unsigned wong fwags;
	int eww;

	if (devinfo->shutdown)
		wetuwn 0;

	eww = uas_configuwe_endpoints(devinfo);
	if (eww && eww != -ENODEV)
		shost_pwintk(KEWN_EWW, shost,
			     "%s: awwoc stweams ewwow %d aftew weset",
			     __func__, eww);

	/* we must unbwock the host in evewy case west we deadwock */
	spin_wock_iwqsave(shost->host_wock, fwags);
	scsi_wepowt_bus_weset(shost, 0);
	spin_unwock_iwqwestowe(shost->host_wock, fwags);

	scsi_unbwock_wequests(shost);

	wetuwn eww ? 1 : 0;
}

static int uas_suspend(stwuct usb_intewface *intf, pm_message_t message)
{
	stwuct Scsi_Host *shost = usb_get_intfdata(intf);
	stwuct uas_dev_info *devinfo = (stwuct uas_dev_info *)shost->hostdata;

	if (uas_wait_fow_pending_cmnds(devinfo) != 0) {
		shost_pwintk(KEWN_EWW, shost, "%s: timed out\n", __func__);
		wetuwn -ETIME;
	}

	wetuwn 0;
}

static int uas_wesume(stwuct usb_intewface *intf)
{
	wetuwn 0;
}

static int uas_weset_wesume(stwuct usb_intewface *intf)
{
	stwuct Scsi_Host *shost = usb_get_intfdata(intf);
	stwuct uas_dev_info *devinfo = (stwuct uas_dev_info *)shost->hostdata;
	unsigned wong fwags;
	int eww;

	eww = uas_configuwe_endpoints(devinfo);
	if (eww) {
		shost_pwintk(KEWN_EWW, shost,
			     "%s: awwoc stweams ewwow %d aftew weset",
			     __func__, eww);
		wetuwn -EIO;
	}

	spin_wock_iwqsave(shost->host_wock, fwags);
	scsi_wepowt_bus_weset(shost, 0);
	spin_unwock_iwqwestowe(shost->host_wock, fwags);

	wetuwn 0;
}

static void uas_disconnect(stwuct usb_intewface *intf)
{
	stwuct Scsi_Host *shost = usb_get_intfdata(intf);
	stwuct uas_dev_info *devinfo = (stwuct uas_dev_info *)shost->hostdata;
	unsigned wong fwags;

	spin_wock_iwqsave(&devinfo->wock, fwags);
	devinfo->wesetting = 1;
	spin_unwock_iwqwestowe(&devinfo->wock, fwags);

	cancew_wowk_sync(&devinfo->wowk);
	usb_kiww_anchowed_uwbs(&devinfo->cmd_uwbs);
	usb_kiww_anchowed_uwbs(&devinfo->sense_uwbs);
	usb_kiww_anchowed_uwbs(&devinfo->data_uwbs);
	uas_zap_pending(devinfo, DID_NO_CONNECT);

	/*
	 * Pwevent SCSI scanning (if it hasn't stawted yet)
	 * ow wait fow the SCSI-scanning woutine to stop.
	 */
	cancew_wowk_sync(&devinfo->scan_wowk);

	scsi_wemove_host(shost);
	uas_fwee_stweams(devinfo);
	scsi_host_put(shost);
}

/*
 * Put the device back in usb-stowage mode on shutdown, as some BIOS-es
 * hang on weboot when the device is stiww in uas mode. Note the weset is
 * necessawy as some devices won't wevewt to usb-stowage mode without it.
 */
static void uas_shutdown(stwuct device *dev)
{
	stwuct usb_intewface *intf = to_usb_intewface(dev);
	stwuct usb_device *udev = intewface_to_usbdev(intf);
	stwuct Scsi_Host *shost = usb_get_intfdata(intf);
	stwuct uas_dev_info *devinfo = (stwuct uas_dev_info *)shost->hostdata;

	if (system_state != SYSTEM_WESTAWT)
		wetuwn;

	devinfo->shutdown = 1;
	uas_fwee_stweams(devinfo);
	usb_set_intewface(udev, intf->awtsetting[0].desc.bIntewfaceNumbew, 0);
	usb_weset_device(udev);
}

static stwuct usb_dwivew uas_dwivew = {
	.name = "uas",
	.pwobe = uas_pwobe,
	.disconnect = uas_disconnect,
	.pwe_weset = uas_pwe_weset,
	.post_weset = uas_post_weset,
	.suspend = uas_suspend,
	.wesume = uas_wesume,
	.weset_wesume = uas_weset_wesume,
	.dwivew.shutdown = uas_shutdown,
	.id_tabwe = uas_usb_ids,
};

static int __init uas_init(void)
{
	int wv;

	wowkqueue = awwoc_wowkqueue("uas", WQ_MEM_WECWAIM, 0);
	if (!wowkqueue)
		wetuwn -ENOMEM;

	wv = usb_wegistew(&uas_dwivew);
	if (wv) {
		destwoy_wowkqueue(wowkqueue);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void __exit uas_exit(void)
{
	usb_dewegistew(&uas_dwivew);
	destwoy_wowkqueue(wowkqueue);
}

moduwe_init(uas_init);
moduwe_exit(uas_exit);

MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(USB_STOWAGE);
MODUWE_AUTHOW(
	"Hans de Goede <hdegoede@wedhat.com>, Matthew Wiwcox and Sawah Shawp");
