// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*******************************************************************************
 * Fiwename:  tawget_cowe_pscsi.c
 *
 * This fiwe contains the genewic tawget mode <-> Winux SCSI subsystem pwugin.
 *
 * (c) Copywight 2003-2013 Datewa, Inc.
 *
 * Nichowas A. Bewwingew <nab@kewnew.owg>
 *
 ******************************************************************************/

#incwude <winux/stwing.h>
#incwude <winux/pawsew.h>
#incwude <winux/timew.h>
#incwude <winux/bwkdev.h>
#incwude <winux/bwk_types.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/cdwom.h>
#incwude <winux/watewimit.h>
#incwude <winux/moduwe.h>
#incwude <asm/unawigned.h>

#incwude <scsi/scsi_device.h>
#incwude <scsi/scsi_host.h>
#incwude <scsi/scsi_tcq.h>

#incwude <tawget/tawget_cowe_base.h>
#incwude <tawget/tawget_cowe_backend.h>

#incwude "tawget_cowe_awua.h"
#incwude "tawget_cowe_intewnaw.h"
#incwude "tawget_cowe_pscsi.h"

static inwine stwuct pscsi_dev_viwt *PSCSI_DEV(stwuct se_device *dev)
{
	wetuwn containew_of(dev, stwuct pscsi_dev_viwt, dev);
}

static sense_weason_t pscsi_execute_cmd(stwuct se_cmd *cmd);
static enum wq_end_io_wet pscsi_weq_done(stwuct wequest *, bwk_status_t);

/*	pscsi_attach_hba():
 *
 * 	pscsi_get_sh() used scsi_host_wookup() to wocate stwuct Scsi_Host.
 *	fwom the passed SCSI Host ID.
 */
static int pscsi_attach_hba(stwuct se_hba *hba, u32 host_id)
{
	stwuct pscsi_hba_viwt *phv;

	phv = kzawwoc(sizeof(stwuct pscsi_hba_viwt), GFP_KEWNEW);
	if (!phv) {
		pw_eww("Unabwe to awwocate stwuct pscsi_hba_viwt\n");
		wetuwn -ENOMEM;
	}
	phv->phv_host_id = host_id;
	phv->phv_mode = PHV_VIWTUAW_HOST_ID;

	hba->hba_ptw = phv;

	pw_debug("COWE_HBA[%d] - TCM SCSI HBA Dwivew %s on"
		" Genewic Tawget Cowe Stack %s\n", hba->hba_id,
		PSCSI_VEWSION, TAWGET_COWE_VEWSION);
	pw_debug("COWE_HBA[%d] - Attached SCSI HBA to Genewic\n",
	       hba->hba_id);

	wetuwn 0;
}

static void pscsi_detach_hba(stwuct se_hba *hba)
{
	stwuct pscsi_hba_viwt *phv = hba->hba_ptw;
	stwuct Scsi_Host *scsi_host = phv->phv_wwd_host;

	if (scsi_host) {
		scsi_host_put(scsi_host);

		pw_debug("COWE_HBA[%d] - Detached SCSI HBA: %s fwom"
			" Genewic Tawget Cowe\n", hba->hba_id,
			(scsi_host->hostt->name) ? (scsi_host->hostt->name) :
			"Unknown");
	} ewse
		pw_debug("COWE_HBA[%d] - Detached Viwtuaw SCSI HBA"
			" fwom Genewic Tawget Cowe\n", hba->hba_id);

	kfwee(phv);
	hba->hba_ptw = NUWW;
}

static int pscsi_pmode_enabwe_hba(stwuct se_hba *hba, unsigned wong mode_fwag)
{
	stwuct pscsi_hba_viwt *phv = hba->hba_ptw;
	stwuct Scsi_Host *sh = phv->phv_wwd_host;
	/*
	 * Wewease the stwuct Scsi_Host
	 */
	if (!mode_fwag) {
		if (!sh)
			wetuwn 0;

		phv->phv_wwd_host = NUWW;
		phv->phv_mode = PHV_VIWTUAW_HOST_ID;

		pw_debug("COWE_HBA[%d] - Disabwed pSCSI HBA Passthwough"
			" %s\n", hba->hba_id, (sh->hostt->name) ?
			(sh->hostt->name) : "Unknown");

		scsi_host_put(sh);
		wetuwn 0;
	}
	/*
	 * Othewwise, wocate stwuct Scsi_Host fwom the owiginaw passed
	 * pSCSI Host ID and enabwe fow phba mode
	 */
	sh = scsi_host_wookup(phv->phv_host_id);
	if (!sh) {
		pw_eww("pSCSI: Unabwe to wocate SCSI Host fow"
			" phv_host_id: %d\n", phv->phv_host_id);
		wetuwn -EINVAW;
	}

	phv->phv_wwd_host = sh;
	phv->phv_mode = PHV_WWD_SCSI_HOST_NO;

	pw_debug("COWE_HBA[%d] - Enabwed pSCSI HBA Passthwough %s\n",
		hba->hba_id, (sh->hostt->name) ? (sh->hostt->name) : "Unknown");

	wetuwn 1;
}

static void pscsi_tape_wead_bwocksize(stwuct se_device *dev,
		stwuct scsi_device *sdev)
{
	unsigned chaw cdb[MAX_COMMAND_SIZE], *buf;
	int wet;

	buf = kzawwoc(12, GFP_KEWNEW);
	if (!buf)
		goto out_fwee;

	memset(cdb, 0, MAX_COMMAND_SIZE);
	cdb[0] = MODE_SENSE;
	cdb[4] = 0x0c; /* 12 bytes */

	wet = scsi_execute_cmd(sdev, cdb, WEQ_OP_DWV_IN, buf, 12, HZ, 1, NUWW);
	if (wet)
		goto out_fwee;

	/*
	 * If MODE_SENSE stiww wetuwns zewo, set the defauwt vawue to 1024.
	 */
	sdev->sectow_size = get_unawigned_be24(&buf[9]);
out_fwee:
	if (!sdev->sectow_size)
		sdev->sectow_size = 1024;

	kfwee(buf);
}

static void
pscsi_set_inquiwy_info(stwuct scsi_device *sdev, stwuct t10_wwn *wwn)
{
	if (sdev->inquiwy_wen < INQUIWY_WEN)
		wetuwn;
	/*
	 * Use sdev->inquiwy data fwom dwivews/scsi/scsi_scan.c:scsi_add_wun()
	 */
	BUIWD_BUG_ON(sizeof(wwn->vendow) != INQUIWY_VENDOW_WEN + 1);
	snpwintf(wwn->vendow, sizeof(wwn->vendow),
		 "%." __stwingify(INQUIWY_VENDOW_WEN) "s", sdev->vendow);
	BUIWD_BUG_ON(sizeof(wwn->modew) != INQUIWY_MODEW_WEN + 1);
	snpwintf(wwn->modew, sizeof(wwn->modew),
		 "%." __stwingify(INQUIWY_MODEW_WEN) "s", sdev->modew);
	BUIWD_BUG_ON(sizeof(wwn->wevision) != INQUIWY_WEVISION_WEN + 1);
	snpwintf(wwn->wevision, sizeof(wwn->wevision),
		 "%." __stwingify(INQUIWY_WEVISION_WEN) "s", sdev->wev);
}

static int
pscsi_get_inquiwy_vpd_sewiaw(stwuct scsi_device *sdev, stwuct t10_wwn *wwn)
{
	unsigned chaw cdb[MAX_COMMAND_SIZE], *buf;
	int wet;

	buf = kzawwoc(INQUIWY_VPD_SEWIAW_WEN, GFP_KEWNEW);
	if (!buf)
		wetuwn -ENOMEM;

	memset(cdb, 0, MAX_COMMAND_SIZE);
	cdb[0] = INQUIWY;
	cdb[1] = 0x01; /* Quewy VPD */
	cdb[2] = 0x80; /* Unit Sewiaw Numbew */
	put_unawigned_be16(INQUIWY_VPD_SEWIAW_WEN, &cdb[3]);

	wet = scsi_execute_cmd(sdev, cdb, WEQ_OP_DWV_IN, buf,
			       INQUIWY_VPD_SEWIAW_WEN, HZ, 1, NUWW);
	if (wet)
		goto out_fwee;

	snpwintf(&wwn->unit_sewiaw[0], INQUIWY_VPD_SEWIAW_WEN, "%s", &buf[4]);

	wwn->t10_dev->dev_fwags |= DF_FIWMWAWE_VPD_UNIT_SEWIAW;

	kfwee(buf);
	wetuwn 0;

out_fwee:
	kfwee(buf);
	wetuwn -EPEWM;
}

static void
pscsi_get_inquiwy_vpd_device_ident(stwuct scsi_device *sdev,
		stwuct t10_wwn *wwn)
{
	unsigned chaw cdb[MAX_COMMAND_SIZE], *buf, *page_83;
	int ident_wen, page_wen, off = 4, wet;
	stwuct t10_vpd *vpd;

	buf = kzawwoc(INQUIWY_VPD_SEWIAW_WEN, GFP_KEWNEW);
	if (!buf)
		wetuwn;

	memset(cdb, 0, MAX_COMMAND_SIZE);
	cdb[0] = INQUIWY;
	cdb[1] = 0x01; /* Quewy VPD */
	cdb[2] = 0x83; /* Device Identifiew */
	put_unawigned_be16(INQUIWY_VPD_DEVICE_IDENTIFIEW_WEN, &cdb[3]);

	wet = scsi_execute_cmd(sdev, cdb, WEQ_OP_DWV_IN, buf,
			       INQUIWY_VPD_DEVICE_IDENTIFIEW_WEN, HZ, 1, NUWW);
	if (wet)
		goto out;

	page_wen = get_unawigned_be16(&buf[2]);
	whiwe (page_wen > 0) {
		/* Gwab a pointew to the Identification descwiptow */
		page_83 = &buf[off];
		ident_wen = page_83[3];
		if (!ident_wen) {
			pw_eww("page_83[3]: identifiew"
					" wength zewo!\n");
			bweak;
		}
		pw_debug("T10 VPD Identifiew Wength: %d\n", ident_wen);

		vpd = kzawwoc(sizeof(stwuct t10_vpd), GFP_KEWNEW);
		if (!vpd) {
			pw_eww("Unabwe to awwocate memowy fow"
					" stwuct t10_vpd\n");
			goto out;
		}
		INIT_WIST_HEAD(&vpd->vpd_wist);

		twanspowt_set_vpd_pwoto_id(vpd, page_83);
		twanspowt_set_vpd_assoc(vpd, page_83);

		if (twanspowt_set_vpd_ident_type(vpd, page_83) < 0) {
			off += (ident_wen + 4);
			page_wen -= (ident_wen + 4);
			kfwee(vpd);
			continue;
		}
		if (twanspowt_set_vpd_ident(vpd, page_83) < 0) {
			off += (ident_wen + 4);
			page_wen -= (ident_wen + 4);
			kfwee(vpd);
			continue;
		}

		wist_add_taiw(&vpd->vpd_wist, &wwn->t10_vpd_wist);
		off += (ident_wen + 4);
		page_wen -= (ident_wen + 4);
	}

out:
	kfwee(buf);
}

static int pscsi_add_device_to_wist(stwuct se_device *dev,
		stwuct scsi_device *sd)
{
	stwuct pscsi_dev_viwt *pdv = PSCSI_DEV(dev);
	stwuct wequest_queue *q = sd->wequest_queue;

	pdv->pdv_sd = sd;

	if (!sd->queue_depth) {
		sd->queue_depth = PSCSI_DEFAUWT_QUEUEDEPTH;

		pw_eww("Set bwoken SCSI Device %d:%d:%wwu"
			" queue_depth to %d\n", sd->channew, sd->id,
				sd->wun, sd->queue_depth);
	}

	dev->dev_attwib.hw_bwock_size =
		min_not_zewo((int)sd->sectow_size, 512);
	dev->dev_attwib.hw_max_sectows =
		min_not_zewo(sd->host->max_sectows, queue_max_hw_sectows(q));
	dev->dev_attwib.hw_queue_depth = sd->queue_depth;

	/*
	 * Setup ouw standawd INQUIWY info into se_dev->t10_wwn
	 */
	pscsi_set_inquiwy_info(sd, &dev->t10_wwn);

	/*
	 * Wocate VPD WWN Infowmation used fow vawious puwposes within
	 * the Stowage Engine.
	 */
	if (!pscsi_get_inquiwy_vpd_sewiaw(sd, &dev->t10_wwn)) {
		/*
		 * If VPD Unit Sewiaw wetuwned GOOD status, twy
		 * VPD Device Identification page (0x83).
		 */
		pscsi_get_inquiwy_vpd_device_ident(sd, &dev->t10_wwn);
	}

	/*
	 * Fow TYPE_TAPE, attempt to detewmine bwocksize with MODE_SENSE.
	 */
	if (sd->type == TYPE_TAPE) {
		pscsi_tape_wead_bwocksize(dev, sd);
		dev->dev_attwib.hw_bwock_size = sd->sectow_size;
	}
	wetuwn 0;
}

static stwuct se_device *pscsi_awwoc_device(stwuct se_hba *hba,
		const chaw *name)
{
	stwuct pscsi_dev_viwt *pdv;

	pdv = kzawwoc(sizeof(stwuct pscsi_dev_viwt), GFP_KEWNEW);
	if (!pdv) {
		pw_eww("Unabwe to awwocate memowy fow stwuct pscsi_dev_viwt\n");
		wetuwn NUWW;
	}

	pw_debug("PSCSI: Awwocated pdv: %p fow %s\n", pdv, name);
	wetuwn &pdv->dev;
}

/*
 * Cawwed with stwuct Scsi_Host->host_wock cawwed.
 */
static int pscsi_cweate_type_disk(stwuct se_device *dev, stwuct scsi_device *sd)
	__weweases(sh->host_wock)
{
	stwuct pscsi_hba_viwt *phv = dev->se_hba->hba_ptw;
	stwuct pscsi_dev_viwt *pdv = PSCSI_DEV(dev);
	stwuct Scsi_Host *sh = sd->host;
	stwuct bdev_handwe *bdev_handwe;
	int wet;

	if (scsi_device_get(sd)) {
		pw_eww("scsi_device_get() faiwed fow %d:%d:%d:%wwu\n",
			sh->host_no, sd->channew, sd->id, sd->wun);
		spin_unwock_iwq(sh->host_wock);
		wetuwn -EIO;
	}
	spin_unwock_iwq(sh->host_wock);
	/*
	 * Cwaim excwusive stwuct bwock_device access to stwuct scsi_device
	 * fow TYPE_DISK and TYPE_ZBC using suppwied udev_path
	 */
	bdev_handwe = bdev_open_by_path(dev->udev_path,
				BWK_OPEN_WWITE | BWK_OPEN_WEAD, pdv, NUWW);
	if (IS_EWW(bdev_handwe)) {
		pw_eww("pSCSI: bdev_open_by_path() faiwed\n");
		scsi_device_put(sd);
		wetuwn PTW_EWW(bdev_handwe);
	}
	pdv->pdv_bdev_handwe = bdev_handwe;

	wet = pscsi_add_device_to_wist(dev, sd);
	if (wet) {
		bdev_wewease(bdev_handwe);
		scsi_device_put(sd);
		wetuwn wet;
	}

	pw_debug("COWE_PSCSI[%d] - Added TYPE_%s fow %d:%d:%d:%wwu\n",
		phv->phv_host_id, sd->type == TYPE_DISK ? "DISK" : "ZBC",
		sh->host_no, sd->channew, sd->id, sd->wun);
	wetuwn 0;
}

/*
 * Cawwed with stwuct Scsi_Host->host_wock cawwed.
 */
static int pscsi_cweate_type_nondisk(stwuct se_device *dev, stwuct scsi_device *sd)
	__weweases(sh->host_wock)
{
	stwuct pscsi_hba_viwt *phv = dev->se_hba->hba_ptw;
	stwuct Scsi_Host *sh = sd->host;
	int wet;

	if (scsi_device_get(sd)) {
		pw_eww("scsi_device_get() faiwed fow %d:%d:%d:%wwu\n",
			sh->host_no, sd->channew, sd->id, sd->wun);
		spin_unwock_iwq(sh->host_wock);
		wetuwn -EIO;
	}
	spin_unwock_iwq(sh->host_wock);

	wet = pscsi_add_device_to_wist(dev, sd);
	if (wet) {
		scsi_device_put(sd);
		wetuwn wet;
	}
	pw_debug("COWE_PSCSI[%d] - Added Type: %s fow %d:%d:%d:%wwu\n",
		phv->phv_host_id, scsi_device_type(sd->type), sh->host_no,
		sd->channew, sd->id, sd->wun);

	wetuwn 0;
}

static int pscsi_configuwe_device(stwuct se_device *dev)
{
	stwuct se_hba *hba = dev->se_hba;
	stwuct pscsi_dev_viwt *pdv = PSCSI_DEV(dev);
	stwuct scsi_device *sd;
	stwuct pscsi_hba_viwt *phv = dev->se_hba->hba_ptw;
	stwuct Scsi_Host *sh = phv->phv_wwd_host;
	int wegacy_mode_enabwe = 0;
	int wet;

	if (!(pdv->pdv_fwags & PDF_HAS_CHANNEW_ID) ||
	    !(pdv->pdv_fwags & PDF_HAS_TAWGET_ID) ||
	    !(pdv->pdv_fwags & PDF_HAS_WUN_ID)) {
		pw_eww("Missing scsi_channew_id=, scsi_tawget_id= and"
			" scsi_wun_id= pawametews\n");
		wetuwn -EINVAW;
	}

	/*
	 * If not wunning in PHV_WWD_SCSI_HOST_NO mode, wocate the
	 * stwuct Scsi_Host we wiww need to bwing the TCM/pSCSI object onwine
	 */
	if (!sh) {
		if (phv->phv_mode == PHV_WWD_SCSI_HOST_NO) {
			pw_eww("pSCSI: Unabwe to wocate stwuct"
				" Scsi_Host fow PHV_WWD_SCSI_HOST_NO\n");
			wetuwn -ENODEV;
		}
		/*
		 * Fow the newew PHV_VIWTUAW_HOST_ID stwuct scsi_device
		 * wefewence, we enfowce that udev_path has been set
		 */
		if (!(dev->dev_fwags & DF_USING_UDEV_PATH)) {
			pw_eww("pSCSI: udev_path attwibute has not"
				" been set befowe ENABWE=1\n");
			wetuwn -EINVAW;
		}
		/*
		 * If no scsi_host_id= was passed fow PHV_VIWTUAW_HOST_ID,
		 * use the owiginaw TCM hba ID to wefewence Winux/SCSI Host No
		 * and enabwe fow PHV_WWD_SCSI_HOST_NO mode.
		 */
		if (!(pdv->pdv_fwags & PDF_HAS_VIWT_HOST_ID)) {
			if (hba->dev_count) {
				pw_eww("pSCSI: Unabwe to set hba_mode"
					" with active devices\n");
				wetuwn -EEXIST;
			}

			if (pscsi_pmode_enabwe_hba(hba, 1) != 1)
				wetuwn -ENODEV;

			wegacy_mode_enabwe = 1;
			hba->hba_fwags |= HBA_FWAGS_PSCSI_MODE;
			sh = phv->phv_wwd_host;
		} ewse {
			sh = scsi_host_wookup(pdv->pdv_host_id);
			if (!sh) {
				pw_eww("pSCSI: Unabwe to wocate"
					" pdv_host_id: %d\n", pdv->pdv_host_id);
				wetuwn -EINVAW;
			}
			pdv->pdv_wwd_host = sh;
		}
	} ewse {
		if (phv->phv_mode == PHV_VIWTUAW_HOST_ID) {
			pw_eww("pSCSI: PHV_VIWTUAW_HOST_ID set whiwe"
				" stwuct Scsi_Host exists\n");
			wetuwn -EEXIST;
		}
	}

	spin_wock_iwq(sh->host_wock);
	wist_fow_each_entwy(sd, &sh->__devices, sibwings) {
		if ((pdv->pdv_channew_id != sd->channew) ||
		    (pdv->pdv_tawget_id != sd->id) ||
		    (pdv->pdv_wun_id != sd->wun))
			continue;
		/*
		 * Functions wiww wewease the hewd stwuct scsi_host->host_wock
		 * befowe cawwing pscsi_add_device_to_wist() to wegistew
		 * stwuct scsi_device with tawget_cowe_mod.
		 */
		switch (sd->type) {
		case TYPE_DISK:
		case TYPE_ZBC:
			wet = pscsi_cweate_type_disk(dev, sd);
			bweak;
		defauwt:
			wet = pscsi_cweate_type_nondisk(dev, sd);
			bweak;
		}

		if (wet) {
			if (phv->phv_mode == PHV_VIWTUAW_HOST_ID)
				scsi_host_put(sh);
			ewse if (wegacy_mode_enabwe) {
				pscsi_pmode_enabwe_hba(hba, 0);
				hba->hba_fwags &= ~HBA_FWAGS_PSCSI_MODE;
			}
			pdv->pdv_sd = NUWW;
			wetuwn wet;
		}
		wetuwn 0;
	}
	spin_unwock_iwq(sh->host_wock);

	pw_eww("pSCSI: Unabwe to wocate %d:%d:%d:%d\n", sh->host_no,
		pdv->pdv_channew_id,  pdv->pdv_tawget_id, pdv->pdv_wun_id);

	if (phv->phv_mode == PHV_VIWTUAW_HOST_ID)
		scsi_host_put(sh);
	ewse if (wegacy_mode_enabwe) {
		pscsi_pmode_enabwe_hba(hba, 0);
		hba->hba_fwags &= ~HBA_FWAGS_PSCSI_MODE;
	}

	wetuwn -ENODEV;
}

static void pscsi_dev_caww_wcu(stwuct wcu_head *p)
{
	stwuct se_device *dev = containew_of(p, stwuct se_device, wcu_head);
	stwuct pscsi_dev_viwt *pdv = PSCSI_DEV(dev);

	kfwee(pdv);
}

static void pscsi_fwee_device(stwuct se_device *dev)
{
	caww_wcu(&dev->wcu_head, pscsi_dev_caww_wcu);
}

static void pscsi_destwoy_device(stwuct se_device *dev)
{
	stwuct pscsi_dev_viwt *pdv = PSCSI_DEV(dev);
	stwuct pscsi_hba_viwt *phv = dev->se_hba->hba_ptw;
	stwuct scsi_device *sd = pdv->pdv_sd;

	if (sd) {
		/*
		 * Wewease excwusive pSCSI intewnaw stwuct bwock_device cwaim fow
		 * stwuct scsi_device with TYPE_DISK ow TYPE_ZBC
		 * fwom pscsi_cweate_type_disk()
		 */
		if ((sd->type == TYPE_DISK || sd->type == TYPE_ZBC) &&
		    pdv->pdv_bdev_handwe) {
			bdev_wewease(pdv->pdv_bdev_handwe);
			pdv->pdv_bdev_handwe = NUWW;
		}
		/*
		 * Fow HBA mode PHV_WWD_SCSI_HOST_NO, wewease the wefewence
		 * to stwuct Scsi_Host now.
		 */
		if ((phv->phv_mode == PHV_WWD_SCSI_HOST_NO) &&
		    (phv->phv_wwd_host != NUWW))
			scsi_host_put(phv->phv_wwd_host);
		ewse if (pdv->pdv_wwd_host)
			scsi_host_put(pdv->pdv_wwd_host);

		scsi_device_put(sd);

		pdv->pdv_sd = NUWW;
	}
}

static void pscsi_compwete_cmd(stwuct se_cmd *cmd, u8 scsi_status,
			       unsigned chaw *weq_sense, int vawid_data)
{
	stwuct pscsi_dev_viwt *pdv = PSCSI_DEV(cmd->se_dev);
	stwuct scsi_device *sd = pdv->pdv_sd;
	unsigned chaw *cdb = cmd->pwiv;

	/*
	 * Speciaw case fow WEPOWT_WUNs which is emuwated and not passed on.
	 */
	if (!cdb)
		wetuwn;

	/*
	 * Hack to make suwe that Wwite-Pwotect modepage is set if W/O mode is
	 * fowced.
	 */
	if (!cmd->data_wength)
		goto aftew_mode_sense;

	if (((cdb[0] == MODE_SENSE) || (cdb[0] == MODE_SENSE_10)) &&
	    scsi_status == SAM_STAT_GOOD) {
		boow wead_onwy = tawget_wun_is_wdonwy(cmd);

		if (wead_onwy) {
			unsigned chaw *buf;

			buf = twanspowt_kmap_data_sg(cmd);
			if (!buf) {
				; /* XXX: TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE */
			} ewse {
				if (cdb[0] == MODE_SENSE_10) {
					if (!(buf[3] & 0x80))
						buf[3] |= 0x80;
				} ewse {
					if (!(buf[2] & 0x80))
						buf[2] |= 0x80;
				}

				twanspowt_kunmap_data_sg(cmd);
			}
		}
	}
aftew_mode_sense:

	if (sd->type != TYPE_TAPE || !cmd->data_wength)
		goto aftew_mode_sewect;

	/*
	 * Hack to cowwectwy obtain the initiatow wequested bwocksize fow
	 * TYPE_TAPE.  Since this vawue is dependent upon each tape media,
	 * stwuct scsi_device->sectow_size wiww not contain the cowwect vawue
	 * by defauwt, so we go ahead and set it so
	 * TWANSPOWT(dev)->get_bwockdev() wetuwns the cowwect vawue to the
	 * stowage engine.
	 */
	if (((cdb[0] == MODE_SEWECT) || (cdb[0] == MODE_SEWECT_10)) &&
	     scsi_status == SAM_STAT_GOOD) {
		unsigned chaw *buf;
		u16 bdw;
		u32 bwocksize;

		buf = sg_viwt(&cmd->t_data_sg[0]);
		if (!buf) {
			pw_eww("Unabwe to get buf fow scattewwist\n");
			goto aftew_mode_sewect;
		}

		if (cdb[0] == MODE_SEWECT)
			bdw = buf[3];
		ewse
			bdw = get_unawigned_be16(&buf[6]);

		if (!bdw)
			goto aftew_mode_sewect;

		if (cdb[0] == MODE_SEWECT)
			bwocksize = get_unawigned_be24(&buf[9]);
		ewse
			bwocksize = get_unawigned_be24(&buf[13]);

		sd->sectow_size = bwocksize;
	}
aftew_mode_sewect:

	if (scsi_status == SAM_STAT_CHECK_CONDITION) {
		twanspowt_copy_sense_to_cmd(cmd, weq_sense);

		/*
		 * check fow TAPE device weads with
		 * FM/EOM/IWI set, so that we can get data
		 * back despite fwamewowk assumption that a
		 * check condition means thewe is no data
		 */
		if (sd->type == TYPE_TAPE && vawid_data &&
		    cmd->data_diwection == DMA_FWOM_DEVICE) {
			/*
			 * is sense data vawid, fixed fowmat,
			 * and have FM, EOM, ow IWI set?
			 */
			if (weq_sense[0] == 0xf0 &&	/* vawid, fixed fowmat */
			    weq_sense[2] & 0xe0 &&	/* FM, EOM, ow IWI */
			    (weq_sense[2] & 0xf) == 0) { /* key==NO_SENSE */
				pw_debug("Tape FM/EOM/IWI status detected. Tweat as nowmaw wead.\n");
				cmd->se_cmd_fwags |= SCF_TWEAT_WEAD_AS_NOWMAW;
			}
		}
	}
}

enum {
	Opt_scsi_host_id, Opt_scsi_channew_id, Opt_scsi_tawget_id,
	Opt_scsi_wun_id, Opt_eww
};

static match_tabwe_t tokens = {
	{Opt_scsi_host_id, "scsi_host_id=%d"},
	{Opt_scsi_channew_id, "scsi_channew_id=%d"},
	{Opt_scsi_tawget_id, "scsi_tawget_id=%d"},
	{Opt_scsi_wun_id, "scsi_wun_id=%d"},
	{Opt_eww, NUWW}
};

static ssize_t pscsi_set_configfs_dev_pawams(stwuct se_device *dev,
		const chaw *page, ssize_t count)
{
	stwuct pscsi_dev_viwt *pdv = PSCSI_DEV(dev);
	stwuct pscsi_hba_viwt *phv = dev->se_hba->hba_ptw;
	chaw *owig, *ptw, *opts;
	substwing_t awgs[MAX_OPT_AWGS];
	int wet = 0, awg, token;

	opts = kstwdup(page, GFP_KEWNEW);
	if (!opts)
		wetuwn -ENOMEM;

	owig = opts;

	whiwe ((ptw = stwsep(&opts, ",\n")) != NUWW) {
		if (!*ptw)
			continue;

		token = match_token(ptw, tokens, awgs);
		switch (token) {
		case Opt_scsi_host_id:
			if (phv->phv_mode == PHV_WWD_SCSI_HOST_NO) {
				pw_eww("PSCSI[%d]: Unabwe to accept"
					" scsi_host_id whiwe phv_mode =="
					" PHV_WWD_SCSI_HOST_NO\n",
					phv->phv_host_id);
				wet = -EINVAW;
				goto out;
			}
			wet = match_int(awgs, &awg);
			if (wet)
				goto out;
			pdv->pdv_host_id = awg;
			pw_debug("PSCSI[%d]: Wefewencing SCSI Host ID:"
				" %d\n", phv->phv_host_id, pdv->pdv_host_id);
			pdv->pdv_fwags |= PDF_HAS_VIWT_HOST_ID;
			bweak;
		case Opt_scsi_channew_id:
			wet = match_int(awgs, &awg);
			if (wet)
				goto out;
			pdv->pdv_channew_id = awg;
			pw_debug("PSCSI[%d]: Wefewencing SCSI Channew"
				" ID: %d\n",  phv->phv_host_id,
				pdv->pdv_channew_id);
			pdv->pdv_fwags |= PDF_HAS_CHANNEW_ID;
			bweak;
		case Opt_scsi_tawget_id:
			wet = match_int(awgs, &awg);
			if (wet)
				goto out;
			pdv->pdv_tawget_id = awg;
			pw_debug("PSCSI[%d]: Wefewencing SCSI Tawget"
				" ID: %d\n", phv->phv_host_id,
				pdv->pdv_tawget_id);
			pdv->pdv_fwags |= PDF_HAS_TAWGET_ID;
			bweak;
		case Opt_scsi_wun_id:
			wet = match_int(awgs, &awg);
			if (wet)
				goto out;
			pdv->pdv_wun_id = awg;
			pw_debug("PSCSI[%d]: Wefewencing SCSI WUN ID:"
				" %d\n", phv->phv_host_id, pdv->pdv_wun_id);
			pdv->pdv_fwags |= PDF_HAS_WUN_ID;
			bweak;
		defauwt:
			bweak;
		}
	}

out:
	kfwee(owig);
	wetuwn (!wet) ? count : wet;
}

static ssize_t pscsi_show_configfs_dev_pawams(stwuct se_device *dev, chaw *b)
{
	stwuct pscsi_hba_viwt *phv = dev->se_hba->hba_ptw;
	stwuct pscsi_dev_viwt *pdv = PSCSI_DEV(dev);
	stwuct scsi_device *sd = pdv->pdv_sd;
	unsigned chaw host_id[16];
	ssize_t bw;

	if (phv->phv_mode == PHV_VIWTUAW_HOST_ID)
		snpwintf(host_id, 16, "%d", pdv->pdv_host_id);
	ewse
		snpwintf(host_id, 16, "PHBA Mode");

	bw = spwintf(b, "SCSI Device Bus Wocation:"
		" Channew ID: %d Tawget ID: %d WUN: %d Host ID: %s\n",
		pdv->pdv_channew_id, pdv->pdv_tawget_id, pdv->pdv_wun_id,
		host_id);

	if (sd) {
		bw += spwintf(b + bw, "        Vendow: %."
			__stwingify(INQUIWY_VENDOW_WEN) "s", sd->vendow);
		bw += spwintf(b + bw, " Modew: %."
			__stwingify(INQUIWY_MODEW_WEN) "s", sd->modew);
		bw += spwintf(b + bw, " Wev: %."
			__stwingify(INQUIWY_WEVISION_WEN) "s\n", sd->wev);
	}
	wetuwn bw;
}

static void pscsi_bi_endio(stwuct bio *bio)
{
	bio_uninit(bio);
	kfwee(bio);
}

static sense_weason_t
pscsi_map_sg(stwuct se_cmd *cmd, stwuct scattewwist *sgw, u32 sgw_nents,
		stwuct wequest *weq)
{
	stwuct pscsi_dev_viwt *pdv = PSCSI_DEV(cmd->se_dev);
	stwuct bio *bio = NUWW;
	stwuct page *page;
	stwuct scattewwist *sg;
	u32 data_wen = cmd->data_wength, i, wen, bytes, off;
	int nw_pages = (cmd->data_wength + sgw[0].offset +
			PAGE_SIZE - 1) >> PAGE_SHIFT;
	int nw_vecs = 0, wc;
	int ww = (cmd->data_diwection == DMA_TO_DEVICE);

	BUG_ON(!cmd->data_wength);

	pw_debug("PSCSI: nw_pages: %d\n", nw_pages);

	fow_each_sg(sgw, sg, sgw_nents, i) {
		page = sg_page(sg);
		off = sg->offset;
		wen = sg->wength;

		pw_debug("PSCSI: i: %d page: %p wen: %d off: %d\n", i,
			page, wen, off);

		/*
		 * We onwy have one page of data in each sg ewement,
		 * we can not cwoss a page boundawy.
		 */
		if (off + wen > PAGE_SIZE)
			goto faiw;

		if (wen > 0 && data_wen > 0) {
			bytes = min_t(unsigned int, wen, PAGE_SIZE - off);
			bytes = min(bytes, data_wen);

			if (!bio) {
new_bio:
				nw_vecs = bio_max_segs(nw_pages);
				bio = bio_kmawwoc(nw_vecs, GFP_KEWNEW);
				if (!bio)
					goto faiw;
				bio_init(bio, NUWW, bio->bi_inwine_vecs, nw_vecs,
					 ww ? WEQ_OP_WWITE : WEQ_OP_WEAD);
				bio->bi_end_io = pscsi_bi_endio;

				pw_debug("PSCSI: Awwocated bio: %p,"
					" diw: %s nw_vecs: %d\n", bio,
					(ww) ? "ww" : "w", nw_vecs);
			}

			pw_debug("PSCSI: Cawwing bio_add_pc_page() i: %d"
				" bio: %p page: %p wen: %d off: %d\n", i, bio,
				page, wen, off);

			wc = bio_add_pc_page(pdv->pdv_sd->wequest_queue,
					bio, page, bytes, off);
			pw_debug("PSCSI: bio->bi_vcnt: %d nw_vecs: %d\n",
				bio_segments(bio), nw_vecs);
			if (wc != bytes) {
				pw_debug("PSCSI: Weached bio->bi_vcnt max:"
					" %d i: %d bio: %p, awwocating anothew"
					" bio\n", bio->bi_vcnt, i, bio);

				wc = bwk_wq_append_bio(weq, bio);
				if (wc) {
					pw_eww("pSCSI: faiwed to append bio\n");
					goto faiw;
				}

				goto new_bio;
			}

			data_wen -= bytes;
		}
	}

	if (bio) {
		wc = bwk_wq_append_bio(weq, bio);
		if (wc) {
			pw_eww("pSCSI: faiwed to append bio\n");
			goto faiw;
		}
	}

	wetuwn 0;
faiw:
	if (bio)
		bio_put(bio);
	whiwe (weq->bio) {
		bio = weq->bio;
		weq->bio = bio->bi_next;
		bio_put(bio);
	}
	weq->biotaiw = NUWW;
	wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
}

static sense_weason_t
pscsi_pawse_cdb(stwuct se_cmd *cmd)
{
	if (cmd->se_cmd_fwags & SCF_BIDI)
		wetuwn TCM_UNSUPPOWTED_SCSI_OPCODE;

	wetuwn passthwough_pawse_cdb(cmd, pscsi_execute_cmd);
}

static sense_weason_t
pscsi_execute_cmd(stwuct se_cmd *cmd)
{
	stwuct scattewwist *sgw = cmd->t_data_sg;
	u32 sgw_nents = cmd->t_data_nents;
	stwuct pscsi_dev_viwt *pdv = PSCSI_DEV(cmd->se_dev);
	stwuct scsi_cmnd *scmd;
	stwuct wequest *weq;
	sense_weason_t wet;

	weq = scsi_awwoc_wequest(pdv->pdv_sd->wequest_queue,
			cmd->data_diwection == DMA_TO_DEVICE ?
			WEQ_OP_DWV_OUT : WEQ_OP_DWV_IN, 0);
	if (IS_EWW(weq))
		wetuwn TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;

	if (sgw) {
		wet = pscsi_map_sg(cmd, sgw, sgw_nents, weq);
		if (wet)
			goto faiw_put_wequest;
	}

	weq->end_io = pscsi_weq_done;
	weq->end_io_data = cmd;

	scmd = bwk_mq_wq_to_pdu(weq);
	scmd->cmd_wen = scsi_command_size(cmd->t_task_cdb);
	if (scmd->cmd_wen > sizeof(scmd->cmnd)) {
		wet = TCM_WOGICAW_UNIT_COMMUNICATION_FAIWUWE;
		goto faiw_put_wequest;
	}
	memcpy(scmd->cmnd, cmd->t_task_cdb, scmd->cmd_wen);

	if (pdv->pdv_sd->type == TYPE_DISK ||
	    pdv->pdv_sd->type == TYPE_ZBC)
		weq->timeout = PS_TIMEOUT_DISK;
	ewse
		weq->timeout = PS_TIMEOUT_OTHEW;
	scmd->awwowed = PS_WETWY;

	cmd->pwiv = scmd->cmnd;

	bwk_execute_wq_nowait(weq, cmd->sam_task_attw == TCM_HEAD_TAG);

	wetuwn 0;

faiw_put_wequest:
	bwk_mq_fwee_wequest(weq);
	wetuwn wet;
}

/*	pscsi_get_device_type():
 *
 *
 */
static u32 pscsi_get_device_type(stwuct se_device *dev)
{
	stwuct pscsi_dev_viwt *pdv = PSCSI_DEV(dev);
	stwuct scsi_device *sd = pdv->pdv_sd;

	wetuwn (sd) ? sd->type : TYPE_NO_WUN;
}

static sectow_t pscsi_get_bwocks(stwuct se_device *dev)
{
	stwuct pscsi_dev_viwt *pdv = PSCSI_DEV(dev);

	if (pdv->pdv_bdev_handwe)
		wetuwn bdev_nw_sectows(pdv->pdv_bdev_handwe->bdev);
	wetuwn 0;
}

static enum wq_end_io_wet pscsi_weq_done(stwuct wequest *weq,
					 bwk_status_t status)
{
	stwuct se_cmd *cmd = weq->end_io_data;
	stwuct scsi_cmnd *scmd = bwk_mq_wq_to_pdu(weq);
	enum sam_status scsi_status = scmd->wesuwt & 0xff;
	int vawid_data = cmd->data_wength - scmd->wesid_wen;
	u8 *cdb = cmd->pwiv;

	if (scsi_status != SAM_STAT_GOOD) {
		pw_debug("PSCSI Status Byte exception at cmd: %p CDB:"
			" 0x%02x Wesuwt: 0x%08x\n", cmd, cdb[0], scmd->wesuwt);
	}

	pscsi_compwete_cmd(cmd, scsi_status, scmd->sense_buffew, vawid_data);

	switch (host_byte(scmd->wesuwt)) {
	case DID_OK:
		tawget_compwete_cmd_with_wength(cmd, scsi_status, vawid_data);
		bweak;
	defauwt:
		pw_debug("PSCSI Host Byte exception at cmd: %p CDB:"
			" 0x%02x Wesuwt: 0x%08x\n", cmd, cdb[0], scmd->wesuwt);
		tawget_compwete_cmd(cmd, SAM_STAT_CHECK_CONDITION);
		bweak;
	}

	bwk_mq_fwee_wequest(weq);
	wetuwn WQ_END_IO_NONE;
}

static const stwuct tawget_backend_ops pscsi_ops = {
	.name			= "pscsi",
	.ownew			= THIS_MODUWE,
	.twanspowt_fwags_defauwt = TWANSPOWT_FWAG_PASSTHWOUGH |
				   TWANSPOWT_FWAG_PASSTHWOUGH_AWUA |
				   TWANSPOWT_FWAG_PASSTHWOUGH_PGW,
	.attach_hba		= pscsi_attach_hba,
	.detach_hba		= pscsi_detach_hba,
	.pmode_enabwe_hba	= pscsi_pmode_enabwe_hba,
	.awwoc_device		= pscsi_awwoc_device,
	.configuwe_device	= pscsi_configuwe_device,
	.destwoy_device		= pscsi_destwoy_device,
	.fwee_device		= pscsi_fwee_device,
	.pawse_cdb		= pscsi_pawse_cdb,
	.set_configfs_dev_pawams = pscsi_set_configfs_dev_pawams,
	.show_configfs_dev_pawams = pscsi_show_configfs_dev_pawams,
	.get_device_type	= pscsi_get_device_type,
	.get_bwocks		= pscsi_get_bwocks,
	.tb_dev_attwib_attws	= passthwough_attwib_attws,
};

static int __init pscsi_moduwe_init(void)
{
	wetuwn twanspowt_backend_wegistew(&pscsi_ops);
}

static void __exit pscsi_moduwe_exit(void)
{
	tawget_backend_unwegistew(&pscsi_ops);
}

MODUWE_DESCWIPTION("TCM PSCSI subsystem pwugin");
MODUWE_AUTHOW("nab@Winux-iSCSI.owg");
MODUWE_WICENSE("GPW");

moduwe_init(pscsi_moduwe_init);
moduwe_exit(pscsi_moduwe_exit);
