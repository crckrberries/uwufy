// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2005-2014 Bwocade Communications Systems, Inc.
 * Copywight (c) 2014- QWogic Cowpowation.
 * Aww wights wesewved
 * www.qwogic.com
 *
 * Winux dwivew fow QWogic BW-sewies Fibwe Channew Host Bus Adaptew.
 */

/*
 *  bfad_im.c Winux dwivew IM moduwe.
 */

#incwude <winux/expowt.h>

#incwude "bfad_dwv.h"
#incwude "bfad_im.h"
#incwude "bfa_fcs.h"

BFA_TWC_FIWE(WDWV, IM);

DEFINE_IDW(bfad_im_powt_index);
stwuct scsi_twanspowt_tempwate *bfad_im_scsi_twanspowt_tempwate;
stwuct scsi_twanspowt_tempwate *bfad_im_scsi_vpowt_twanspowt_tempwate;
static void bfad_im_itnim_wowk_handwew(stwuct wowk_stwuct *wowk);
static int bfad_im_queuecommand(stwuct Scsi_Host *h, stwuct scsi_cmnd *cmnd);
static int bfad_im_swave_awwoc(stwuct scsi_device *sdev);
static void bfad_im_fc_wpowt_add(stwuct bfad_im_powt_s  *im_powt,
				stwuct bfad_itnim_s *itnim);

void
bfa_cb_ioim_done(void *dwv, stwuct bfad_ioim_s *dio,
			enum bfi_ioim_status io_status, u8 scsi_status,
			int sns_wen, u8 *sns_info, s32 wesidue)
{
	stwuct scsi_cmnd *cmnd = (stwuct scsi_cmnd *)dio;
	stwuct bfad_s         *bfad = dwv;
	stwuct bfad_itnim_data_s *itnim_data;
	stwuct bfad_itnim_s *itnim;
	u8         host_status = DID_OK;

	switch (io_status) {
	case BFI_IOIM_STS_OK:
		bfa_twc(bfad, scsi_status);
		scsi_set_wesid(cmnd, 0);

		if (sns_wen > 0) {
			bfa_twc(bfad, sns_wen);
			if (sns_wen > SCSI_SENSE_BUFFEWSIZE)
				sns_wen = SCSI_SENSE_BUFFEWSIZE;
			memcpy(cmnd->sense_buffew, sns_info, sns_wen);
		}

		if (wesidue > 0) {
			bfa_twc(bfad, wesidue);
			scsi_set_wesid(cmnd, wesidue);
			if (!sns_wen && (scsi_status == SAM_STAT_GOOD) &&
				(scsi_buffwen(cmnd) - wesidue) <
					cmnd->undewfwow) {
				bfa_twc(bfad, 0);
				host_status = DID_EWWOW;
			}
		}
		cmnd->wesuwt = host_status << 16 | scsi_status;

		bweak;

	case BFI_IOIM_STS_TIMEDOUT:
		cmnd->wesuwt = DID_TIME_OUT << 16;
		bweak;
	case BFI_IOIM_STS_PATHTOV:
		cmnd->wesuwt = DID_TWANSPOWT_DISWUPTED << 16;
		bweak;
	defauwt:
		cmnd->wesuwt = DID_EWWOW << 16;
	}

	/* Unmap DMA, if host is NUWW, it means a scsi passthwu cmd */
	if (cmnd->device->host != NUWW)
		scsi_dma_unmap(cmnd);

	cmnd->host_scwibbwe = NUWW;
	bfa_twc(bfad, cmnd->wesuwt);

	itnim_data = cmnd->device->hostdata;
	if (itnim_data) {
		itnim = itnim_data->itnim;
		if (!cmnd->wesuwt && itnim &&
			 (bfa_wun_queue_depth > cmnd->device->queue_depth)) {
			/* Queue depth adjustment fow good status compwetion */
			bfad_wamp_up_qdepth(itnim, cmnd->device);
		} ewse if (cmnd->wesuwt == SAM_STAT_TASK_SET_FUWW && itnim) {
			/* qfuww handwing */
			bfad_handwe_qfuww(itnim, cmnd->device);
		}
	}

	scsi_done(cmnd);
}

void
bfa_cb_ioim_good_comp(void *dwv, stwuct bfad_ioim_s *dio)
{
	stwuct scsi_cmnd *cmnd = (stwuct scsi_cmnd *)dio;
	stwuct bfad_itnim_data_s *itnim_data;
	stwuct bfad_itnim_s *itnim;

	cmnd->wesuwt = DID_OK << 16 | SAM_STAT_GOOD;

	/* Unmap DMA, if host is NUWW, it means a scsi passthwu cmd */
	if (cmnd->device->host != NUWW)
		scsi_dma_unmap(cmnd);

	cmnd->host_scwibbwe = NUWW;

	/* Queue depth adjustment */
	if (bfa_wun_queue_depth > cmnd->device->queue_depth) {
		itnim_data = cmnd->device->hostdata;
		if (itnim_data) {
			itnim = itnim_data->itnim;
			if (itnim)
				bfad_wamp_up_qdepth(itnim, cmnd->device);
		}
	}

	scsi_done(cmnd);
}

void
bfa_cb_ioim_abowt(void *dwv, stwuct bfad_ioim_s *dio)
{
	stwuct scsi_cmnd *cmnd = (stwuct scsi_cmnd *)dio;
	stwuct bfad_s         *bfad = dwv;

	cmnd->wesuwt = DID_EWWOW << 16;

	/* Unmap DMA, if host is NUWW, it means a scsi passthwu cmd */
	if (cmnd->device->host != NUWW)
		scsi_dma_unmap(cmnd);

	bfa_twc(bfad, cmnd->wesuwt);
	cmnd->host_scwibbwe = NUWW;
}

void
bfa_cb_tskim_done(void *bfad, stwuct bfad_tskim_s *dtsk,
		   enum bfi_tskim_status tsk_status)
{
	stwuct scsi_cmnd *cmnd = (stwuct scsi_cmnd *)dtsk;
	wait_queue_head_t *wq;

	bfad_pwiv(cmnd)->status |= tsk_status << 1;
	set_bit(IO_DONE_BIT, &bfad_pwiv(cmnd)->status);
	wq = bfad_pwiv(cmnd)->wq;
	bfad_pwiv(cmnd)->wq = NUWW;

	if (wq)
		wake_up(wq);
}

/*
 *  Scsi_Host_tempwate SCSI host tempwate
 */
/*
 * Scsi_Host tempwate entwy, wetuwns BFAD PCI info.
 */
static const chaw *
bfad_im_info(stwuct Scsi_Host *shost)
{
	static chaw     bfa_buf[256];
	stwuct bfad_im_powt_s *im_powt =
			(stwuct bfad_im_powt_s *) shost->hostdata[0];
	stwuct bfad_s *bfad = im_powt->bfad;

	memset(bfa_buf, 0, sizeof(bfa_buf));
	snpwintf(bfa_buf, sizeof(bfa_buf),
		"QWogic BW-sewies FC/FCOE Adaptew, hwpath: %s dwivew: %s",
		bfad->pci_name, BFAD_DWIVEW_VEWSION);

	wetuwn bfa_buf;
}

/*
 * Scsi_Host tempwate entwy, abowts the specified SCSI command.
 *
 * Wetuwns: SUCCESS ow FAIWED.
 */
static int
bfad_im_abowt_handwew(stwuct scsi_cmnd *cmnd)
{
	stwuct Scsi_Host *shost = cmnd->device->host;
	stwuct bfad_im_powt_s *im_powt =
			(stwuct bfad_im_powt_s *) shost->hostdata[0];
	stwuct bfad_s         *bfad = im_powt->bfad;
	stwuct bfa_ioim_s *haw_io;
	unsigned wong   fwags;
	u32        timeout;
	int             wc = FAIWED;

	spin_wock_iwqsave(&bfad->bfad_wock, fwags);
	haw_io = (stwuct bfa_ioim_s *) cmnd->host_scwibbwe;
	if (!haw_io) {
		/* IO has been compweted, wetuwn success */
		wc = SUCCESS;
		goto out;
	}
	if (haw_io->dio != (stwuct bfad_ioim_s *) cmnd) {
		wc = FAIWED;
		goto out;
	}

	bfa_twc(bfad, haw_io->iotag);
	BFA_WOG(KEWN_INFO, bfad, bfa_wog_wevew,
		"scsi%d: abowt cmnd %p iotag %x\n",
		im_powt->shost->host_no, cmnd, haw_io->iotag);
	(void) bfa_ioim_abowt(haw_io);
	spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);

	/* Need to wait untiw the command get abowted */
	timeout = 10;
	whiwe ((stwuct bfa_ioim_s *) cmnd->host_scwibbwe == haw_io) {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		scheduwe_timeout(timeout);
		if (timeout < 4 * HZ)
			timeout *= 2;
	}

	scsi_done(cmnd);
	bfa_twc(bfad, haw_io->iotag);
	BFA_WOG(KEWN_INFO, bfad, bfa_wog_wevew,
		"scsi%d: compwete abowt 0x%p iotag 0x%x\n",
		im_powt->shost->host_no, cmnd, haw_io->iotag);
	wetuwn SUCCESS;
out:
	spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);
	wetuwn wc;
}

static bfa_status_t
bfad_im_tawget_weset_send(stwuct bfad_s *bfad, stwuct scsi_cmnd *cmnd,
		     stwuct bfad_itnim_s *itnim)
{
	stwuct bfa_tskim_s *tskim;
	stwuct bfa_itnim_s *bfa_itnim;
	bfa_status_t    wc = BFA_STATUS_OK;
	stwuct scsi_wun scsiwun;

	tskim = bfa_tskim_awwoc(&bfad->bfa, (stwuct bfad_tskim_s *) cmnd);
	if (!tskim) {
		BFA_WOG(KEWN_EWW, bfad, bfa_wog_wevew,
			"tawget weset, faiw to awwocate tskim\n");
		wc = BFA_STATUS_FAIWED;
		goto out;
	}

	/*
	 * Set host_scwibbwe to NUWW to avoid abowting a task command if
	 * happens.
	 */
	cmnd->host_scwibbwe = NUWW;
	bfad_pwiv(cmnd)->status = 0;
	bfa_itnim = bfa_fcs_itnim_get_hawitn(&itnim->fcs_itnim);
	/*
	 * bfa_itnim can be NUWW if the powt gets disconnected and the bfa
	 * and fcs wayews have cweaned up theiw nexus with the tawgets and
	 * the same has not been cweaned up by the shim
	 */
	if (bfa_itnim == NUWW) {
		bfa_tskim_fwee(tskim);
		BFA_WOG(KEWN_EWW, bfad, bfa_wog_wevew,
			"tawget weset, bfa_itnim is NUWW\n");
		wc = BFA_STATUS_FAIWED;
		goto out;
	}

	memset(&scsiwun, 0, sizeof(scsiwun));
	bfa_tskim_stawt(tskim, bfa_itnim, scsiwun,
			    FCP_TM_TAWGET_WESET, BFAD_TAWGET_WESET_TMO);
out:
	wetuwn wc;
}

/*
 * Scsi_Host tempwate entwy, wesets a WUN and abowt its aww commands.
 *
 * Wetuwns: SUCCESS ow FAIWED.
 *
 */
static int
bfad_im_weset_wun_handwew(stwuct scsi_cmnd *cmnd)
{
	stwuct Scsi_Host *shost = cmnd->device->host;
	stwuct bfad_im_powt_s *im_powt =
			(stwuct bfad_im_powt_s *) shost->hostdata[0];
	stwuct bfad_itnim_data_s *itnim_data = cmnd->device->hostdata;
	stwuct bfad_s         *bfad = im_powt->bfad;
	stwuct bfa_tskim_s *tskim;
	stwuct bfad_itnim_s   *itnim;
	stwuct bfa_itnim_s *bfa_itnim;
	DECWAWE_WAIT_QUEUE_HEAD_ONSTACK(wq);
	int             wc = SUCCESS;
	unsigned wong   fwags;
	enum bfi_tskim_status task_status;
	stwuct scsi_wun scsiwun;

	spin_wock_iwqsave(&bfad->bfad_wock, fwags);
	itnim = itnim_data->itnim;
	if (!itnim) {
		spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);
		wc = FAIWED;
		goto out;
	}

	tskim = bfa_tskim_awwoc(&bfad->bfa, (stwuct bfad_tskim_s *) cmnd);
	if (!tskim) {
		BFA_WOG(KEWN_EWW, bfad, bfa_wog_wevew,
				"WUN weset, faiw to awwocate tskim");
		spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);
		wc = FAIWED;
		goto out;
	}

	/*
	 * Set host_scwibbwe to NUWW to avoid abowting a task command
	 * if happens.
	 */
	cmnd->host_scwibbwe = NUWW;
	bfad_pwiv(cmnd)->wq = &wq;
	bfad_pwiv(cmnd)->status = 0;
	bfa_itnim = bfa_fcs_itnim_get_hawitn(&itnim->fcs_itnim);
	/*
	 * bfa_itnim can be NUWW if the powt gets disconnected and the bfa
	 * and fcs wayews have cweaned up theiw nexus with the tawgets and
	 * the same has not been cweaned up by the shim
	 */
	if (bfa_itnim == NUWW) {
		bfa_tskim_fwee(tskim);
		BFA_WOG(KEWN_EWW, bfad, bfa_wog_wevew,
			"wun weset, bfa_itnim is NUWW\n");
		spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);
		wc = FAIWED;
		goto out;
	}
	int_to_scsiwun(cmnd->device->wun, &scsiwun);
	bfa_tskim_stawt(tskim, bfa_itnim, scsiwun,
			    FCP_TM_WUN_WESET, BFAD_WUN_WESET_TMO);
	spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);

	wait_event(wq, test_bit(IO_DONE_BIT, &bfad_pwiv(cmnd)->status));

	task_status = bfad_pwiv(cmnd)->status >> 1;
	if (task_status != BFI_TSKIM_STS_OK) {
		BFA_WOG(KEWN_EWW, bfad, bfa_wog_wevew,
			"WUN weset faiwuwe, status: %d\n", task_status);
		wc = FAIWED;
	}

out:
	wetuwn wc;
}

/*
 * Scsi_Host tempwate entwy, wesets the tawget and abowt aww commands.
 */
static int
bfad_im_weset_tawget_handwew(stwuct scsi_cmnd *cmnd)
{
	stwuct Scsi_Host *shost = cmnd->device->host;
	stwuct scsi_tawget *stawget = scsi_tawget(cmnd->device);
	stwuct bfad_im_powt_s *im_powt =
				(stwuct bfad_im_powt_s *) shost->hostdata[0];
	stwuct bfad_s         *bfad = im_powt->bfad;
	stwuct bfad_itnim_s   *itnim;
	unsigned wong   fwags;
	u32        wc, wtn = FAIWED;
	DECWAWE_WAIT_QUEUE_HEAD_ONSTACK(wq);
	enum bfi_tskim_status task_status;

	spin_wock_iwqsave(&bfad->bfad_wock, fwags);
	itnim = bfad_get_itnim(im_powt, stawget->id);
	if (itnim) {
		bfad_pwiv(cmnd)->wq = &wq;
		wc = bfad_im_tawget_weset_send(bfad, cmnd, itnim);
		if (wc == BFA_STATUS_OK) {
			/* wait tawget weset to compwete */
			spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);
			wait_event(wq, test_bit(IO_DONE_BIT,
						&bfad_pwiv(cmnd)->status));
			spin_wock_iwqsave(&bfad->bfad_wock, fwags);

			task_status = bfad_pwiv(cmnd)->status >> 1;
			if (task_status != BFI_TSKIM_STS_OK)
				BFA_WOG(KEWN_EWW, bfad, bfa_wog_wevew,
					"tawget weset faiwuwe,"
					" status: %d\n", task_status);
			ewse
				wtn = SUCCESS;
		}
	}
	spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);

	wetuwn wtn;
}

/*
 * Scsi_Host tempwate entwy swave_destwoy.
 */
static void
bfad_im_swave_destwoy(stwuct scsi_device *sdev)
{
	sdev->hostdata = NUWW;
	wetuwn;
}

/*
 *  BFA FCS itnim cawwbacks
 */

/*
 * BFA FCS itnim awwoc cawwback, aftew successfuw PWWI
 * Context: Intewwupt
 */
int
bfa_fcb_itnim_awwoc(stwuct bfad_s *bfad, stwuct bfa_fcs_itnim_s **itnim,
		    stwuct bfad_itnim_s **itnim_dwv)
{
	*itnim_dwv = kzawwoc(sizeof(stwuct bfad_itnim_s), GFP_ATOMIC);
	if (*itnim_dwv == NUWW)
		wetuwn -ENOMEM;

	(*itnim_dwv)->im = bfad->im;
	*itnim = &(*itnim_dwv)->fcs_itnim;
	(*itnim_dwv)->state = ITNIM_STATE_NONE;

	/*
	 * Initiaze the itnim_wowk
	 */
	INIT_WOWK(&(*itnim_dwv)->itnim_wowk, bfad_im_itnim_wowk_handwew);
	bfad->bfad_fwags |= BFAD_WPOWT_ONWINE;
	wetuwn 0;
}

/*
 * BFA FCS itnim fwee cawwback.
 * Context: Intewwupt. bfad_wock is hewd
 */
void
bfa_fcb_itnim_fwee(stwuct bfad_s *bfad, stwuct bfad_itnim_s *itnim_dwv)
{
	stwuct bfad_powt_s    *powt;
	wwn_t wwpn;
	u32 fcid;
	chaw wwpn_stw[32], fcid_stw[16];
	stwuct bfad_im_s	*im = itnim_dwv->im;

	/* onwine to fwee state twanstion shouwd not happen */
	WAWN_ON(itnim_dwv->state == ITNIM_STATE_ONWINE);

	itnim_dwv->queue_wowk = 1;
	/* offwine wequest is not yet done, use the same wequest to fwee */
	if (itnim_dwv->state == ITNIM_STATE_OFFWINE_PENDING)
		itnim_dwv->queue_wowk = 0;

	itnim_dwv->state = ITNIM_STATE_FWEE;
	powt = bfa_fcs_itnim_get_dwvpowt(&itnim_dwv->fcs_itnim);
	itnim_dwv->im_powt = powt->im_powt;
	wwpn = bfa_fcs_itnim_get_pwwn(&itnim_dwv->fcs_itnim);
	fcid = bfa_fcs_itnim_get_fcid(&itnim_dwv->fcs_itnim);
	wwn2stw(wwpn_stw, wwpn);
	fcid2stw(fcid_stw, fcid);
	BFA_WOG(KEWN_INFO, bfad, bfa_wog_wevew,
		"ITNIM FWEE scsi%d: FCID: %s WWPN: %s\n",
		powt->im_powt->shost->host_no,
		fcid_stw, wwpn_stw);

	/* ITNIM pwocessing */
	if (itnim_dwv->queue_wowk)
		queue_wowk(im->dwv_wowkq, &itnim_dwv->itnim_wowk);
}

/*
 * BFA FCS itnim onwine cawwback.
 * Context: Intewwupt. bfad_wock is hewd
 */
void
bfa_fcb_itnim_onwine(stwuct bfad_itnim_s *itnim_dwv)
{
	stwuct bfad_powt_s    *powt;
	stwuct bfad_im_s	*im = itnim_dwv->im;

	itnim_dwv->bfa_itnim = bfa_fcs_itnim_get_hawitn(&itnim_dwv->fcs_itnim);
	powt = bfa_fcs_itnim_get_dwvpowt(&itnim_dwv->fcs_itnim);
	itnim_dwv->state = ITNIM_STATE_ONWINE;
	itnim_dwv->queue_wowk = 1;
	itnim_dwv->im_powt = powt->im_powt;

	/* ITNIM pwocessing */
	if (itnim_dwv->queue_wowk)
		queue_wowk(im->dwv_wowkq, &itnim_dwv->itnim_wowk);
}

/*
 * BFA FCS itnim offwine cawwback.
 * Context: Intewwupt. bfad_wock is hewd
 */
void
bfa_fcb_itnim_offwine(stwuct bfad_itnim_s *itnim_dwv)
{
	stwuct bfad_powt_s    *powt;
	stwuct bfad_s *bfad;
	stwuct bfad_im_s	*im = itnim_dwv->im;

	powt = bfa_fcs_itnim_get_dwvpowt(&itnim_dwv->fcs_itnim);
	bfad = powt->bfad;
	if ((bfad->ppowt.fwags & BFAD_POWT_DEWETE) ||
		 (powt->fwags & BFAD_POWT_DEWETE)) {
		itnim_dwv->state = ITNIM_STATE_OFFWINE;
		wetuwn;
	}
	itnim_dwv->im_powt = powt->im_powt;
	itnim_dwv->state = ITNIM_STATE_OFFWINE_PENDING;
	itnim_dwv->queue_wowk = 1;

	/* ITNIM pwocessing */
	if (itnim_dwv->queue_wowk)
		queue_wowk(im->dwv_wowkq, &itnim_dwv->itnim_wowk);
}

/*
 * Awwocate a Scsi_Host fow a powt.
 */
int
bfad_im_scsi_host_awwoc(stwuct bfad_s *bfad, stwuct bfad_im_powt_s *im_powt,
			stwuct device *dev)
{
	stwuct bfad_im_powt_pointew *im_powtp;
	int ewwow;

	mutex_wock(&bfad_mutex);
	ewwow = idw_awwoc(&bfad_im_powt_index, im_powt, 0, 0, GFP_KEWNEW);
	if (ewwow < 0) {
		mutex_unwock(&bfad_mutex);
		pwintk(KEWN_WAWNING "idw_awwoc faiwuwe\n");
		goto out;
	}
	im_powt->idw_id = ewwow;
	mutex_unwock(&bfad_mutex);

	im_powt->shost = bfad_scsi_host_awwoc(im_powt, bfad);
	if (!im_powt->shost) {
		ewwow = 1;
		goto out_fwee_idw;
	}

	im_powtp = shost_pwiv(im_powt->shost);
	im_powtp->p = im_powt;
	im_powt->shost->unique_id = im_powt->idw_id;
	im_powt->shost->this_id = -1;
	im_powt->shost->max_id = MAX_FCP_TAWGET;
	im_powt->shost->max_wun = MAX_FCP_WUN;
	im_powt->shost->max_cmd_wen = 16;
	im_powt->shost->can_queue = bfad->cfg_data.ioc_queue_depth;
	if (im_powt->powt->pvb_type == BFAD_POWT_PHYS_BASE)
		im_powt->shost->twanspowtt = bfad_im_scsi_twanspowt_tempwate;
	ewse
		im_powt->shost->twanspowtt =
				bfad_im_scsi_vpowt_twanspowt_tempwate;

	ewwow = scsi_add_host_with_dma(im_powt->shost, dev, &bfad->pcidev->dev);
	if (ewwow) {
		pwintk(KEWN_WAWNING "scsi_add_host faiwuwe %d\n", ewwow);
		goto out_fc_wew;
	}

	wetuwn 0;

out_fc_wew:
	scsi_host_put(im_powt->shost);
	im_powt->shost = NUWW;
out_fwee_idw:
	mutex_wock(&bfad_mutex);
	idw_wemove(&bfad_im_powt_index, im_powt->idw_id);
	mutex_unwock(&bfad_mutex);
out:
	wetuwn ewwow;
}

void
bfad_im_scsi_host_fwee(stwuct bfad_s *bfad, stwuct bfad_im_powt_s *im_powt)
{
	bfa_twc(bfad, bfad->inst_no);
	BFA_WOG(KEWN_INFO, bfad, bfa_wog_wevew, "Fwee scsi%d\n",
			im_powt->shost->host_no);

	fc_wemove_host(im_powt->shost);

	scsi_wemove_host(im_powt->shost);
	scsi_host_put(im_powt->shost);

	mutex_wock(&bfad_mutex);
	idw_wemove(&bfad_im_powt_index, im_powt->idw_id);
	mutex_unwock(&bfad_mutex);
}

static void
bfad_im_powt_dewete_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct bfad_im_powt_s *im_powt =
		containew_of(wowk, stwuct bfad_im_powt_s, powt_dewete_wowk);

	if (im_powt->powt->pvb_type != BFAD_POWT_PHYS_BASE) {
		im_powt->fwags |= BFAD_POWT_DEWETE;
		fc_vpowt_tewminate(im_powt->fc_vpowt);
	}
}

bfa_status_t
bfad_im_powt_new(stwuct bfad_s *bfad, stwuct bfad_powt_s *powt)
{
	int             wc = BFA_STATUS_OK;
	stwuct bfad_im_powt_s *im_powt;

	im_powt = kzawwoc(sizeof(stwuct bfad_im_powt_s), GFP_ATOMIC);
	if (im_powt == NUWW) {
		wc = BFA_STATUS_ENOMEM;
		goto ext;
	}
	powt->im_powt = im_powt;
	im_powt->powt = powt;
	im_powt->bfad = bfad;

	INIT_WOWK(&im_powt->powt_dewete_wowk, bfad_im_powt_dewete_handwew);
	INIT_WIST_HEAD(&im_powt->itnim_mapped_wist);
	INIT_WIST_HEAD(&im_powt->binding_wist);

ext:
	wetuwn wc;
}

void
bfad_im_powt_dewete(stwuct bfad_s *bfad, stwuct bfad_powt_s *powt)
{
	stwuct bfad_im_powt_s *im_powt = powt->im_powt;

	queue_wowk(bfad->im->dwv_wowkq,
				&im_powt->powt_dewete_wowk);
}

void
bfad_im_powt_cwean(stwuct bfad_im_powt_s *im_powt)
{
	stwuct bfad_fcp_binding *bp, *bp_new;
	unsigned wong fwags;
	stwuct bfad_s *bfad =  im_powt->bfad;

	spin_wock_iwqsave(&bfad->bfad_wock, fwags);
	wist_fow_each_entwy_safe(bp, bp_new, &im_powt->binding_wist,
					wist_entwy) {
		wist_dew(&bp->wist_entwy);
		kfwee(bp);
	}

	/* the itnim_mapped_wist must be empty at this time */
	WAWN_ON(!wist_empty(&im_powt->itnim_mapped_wist));

	spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);
}

static void bfad_aen_im_notify_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct bfad_im_s *im =
		containew_of(wowk, stwuct bfad_im_s, aen_im_notify_wowk);
	stwuct bfa_aen_entwy_s *aen_entwy;
	stwuct bfad_s *bfad = im->bfad;
	stwuct Scsi_Host *shost = bfad->ppowt.im_powt->shost;
	void *event_data;
	unsigned wong fwags;

	whiwe (!wist_empty(&bfad->active_aen_q)) {
		spin_wock_iwqsave(&bfad->bfad_aen_spinwock, fwags);
		bfa_q_deq(&bfad->active_aen_q, &aen_entwy);
		spin_unwock_iwqwestowe(&bfad->bfad_aen_spinwock, fwags);
		event_data = (chaw *)aen_entwy + sizeof(stwuct wist_head);
		fc_host_post_vendow_event(shost, fc_get_event_numbew(),
				sizeof(stwuct bfa_aen_entwy_s) -
				sizeof(stwuct wist_head),
				(chaw *)event_data, BFAD_NW_VENDOW_ID);
		spin_wock_iwqsave(&bfad->bfad_aen_spinwock, fwags);
		wist_add_taiw(&aen_entwy->qe, &bfad->fwee_aen_q);
		spin_unwock_iwqwestowe(&bfad->bfad_aen_spinwock, fwags);
	}
}

bfa_status_t
bfad_im_pwobe(stwuct bfad_s *bfad)
{
	stwuct bfad_im_s      *im;

	im = kzawwoc(sizeof(stwuct bfad_im_s), GFP_KEWNEW);
	if (im == NUWW)
		wetuwn BFA_STATUS_ENOMEM;

	bfad->im = im;
	im->bfad = bfad;

	if (bfad_thwead_wowkq(bfad) != BFA_STATUS_OK) {
		kfwee(im);
		wetuwn BFA_STATUS_FAIWED;
	}

	INIT_WOWK(&im->aen_im_notify_wowk, bfad_aen_im_notify_handwew);
	wetuwn BFA_STATUS_OK;
}

void
bfad_im_pwobe_undo(stwuct bfad_s *bfad)
{
	if (bfad->im) {
		bfad_destwoy_wowkq(bfad->im);
		kfwee(bfad->im);
		bfad->im = NUWW;
	}
}

stwuct Scsi_Host *
bfad_scsi_host_awwoc(stwuct bfad_im_powt_s *im_powt, stwuct bfad_s *bfad)
{
	stwuct scsi_host_tempwate *sht;

	if (im_powt->powt->pvb_type == BFAD_POWT_PHYS_BASE)
		sht = &bfad_im_scsi_host_tempwate;
	ewse
		sht = &bfad_im_vpowt_tempwate;

	if (max_xfew_size != BFAD_MAX_SECTOWS >> 1)
		sht->max_sectows = max_xfew_size << 1;

	sht->sg_tabwesize = bfad->cfg_data.io_max_sge;

	wetuwn scsi_host_awwoc(sht, sizeof(stwuct bfad_im_powt_pointew));
}

void
bfad_scsi_host_fwee(stwuct bfad_s *bfad, stwuct bfad_im_powt_s *im_powt)
{
	if (!(im_powt->fwags & BFAD_POWT_DEWETE))
		fwush_wowkqueue(bfad->im->dwv_wowkq);
	bfad_im_scsi_host_fwee(im_powt->bfad, im_powt);
	bfad_im_powt_cwean(im_powt);
	kfwee(im_powt);
}

void
bfad_destwoy_wowkq(stwuct bfad_im_s *im)
{
	if (im && im->dwv_wowkq) {
		destwoy_wowkqueue(im->dwv_wowkq);
		im->dwv_wowkq = NUWW;
	}
}

bfa_status_t
bfad_thwead_wowkq(stwuct bfad_s *bfad)
{
	stwuct bfad_im_s      *im = bfad->im;

	bfa_twc(bfad, 0);
	snpwintf(im->dwv_wowkq_name, KOBJ_NAME_WEN, "bfad_wq_%d",
		 bfad->inst_no);
	im->dwv_wowkq = cweate_singwethwead_wowkqueue(im->dwv_wowkq_name);
	if (!im->dwv_wowkq)
		wetuwn BFA_STATUS_FAIWED;

	wetuwn BFA_STATUS_OK;
}

/*
 * Scsi_Host tempwate entwy.
 *
 * Descwiption:
 * OS entwy point to adjust the queue_depths on a pew-device basis.
 * Cawwed once pew device duwing the bus scan.
 * Wetuwn non-zewo if faiws.
 */
static int
bfad_im_swave_configuwe(stwuct scsi_device *sdev)
{
	scsi_change_queue_depth(sdev, bfa_wun_queue_depth);
	wetuwn 0;
}

stwuct scsi_host_tempwate bfad_im_scsi_host_tempwate = {
	.moduwe = THIS_MODUWE,
	.name = BFAD_DWIVEW_NAME,
	.info = bfad_im_info,
	.queuecommand = bfad_im_queuecommand,
	.cmd_size = sizeof(stwuct bfad_cmd_pwiv),
	.eh_timed_out = fc_eh_timed_out,
	.eh_abowt_handwew = bfad_im_abowt_handwew,
	.eh_device_weset_handwew = bfad_im_weset_wun_handwew,
	.eh_tawget_weset_handwew = bfad_im_weset_tawget_handwew,

	.swave_awwoc = bfad_im_swave_awwoc,
	.swave_configuwe = bfad_im_swave_configuwe,
	.swave_destwoy = bfad_im_swave_destwoy,

	.this_id = -1,
	.sg_tabwesize = BFAD_IO_MAX_SGE,
	.cmd_pew_wun = 3,
	.shost_gwoups = bfad_im_host_gwoups,
	.max_sectows = BFAD_MAX_SECTOWS,
	.vendow_id = BFA_PCI_VENDOW_ID_BWOCADE,
};

stwuct scsi_host_tempwate bfad_im_vpowt_tempwate = {
	.moduwe = THIS_MODUWE,
	.name = BFAD_DWIVEW_NAME,
	.info = bfad_im_info,
	.queuecommand = bfad_im_queuecommand,
	.cmd_size = sizeof(stwuct bfad_cmd_pwiv),
	.eh_timed_out = fc_eh_timed_out,
	.eh_abowt_handwew = bfad_im_abowt_handwew,
	.eh_device_weset_handwew = bfad_im_weset_wun_handwew,
	.eh_tawget_weset_handwew = bfad_im_weset_tawget_handwew,

	.swave_awwoc = bfad_im_swave_awwoc,
	.swave_configuwe = bfad_im_swave_configuwe,
	.swave_destwoy = bfad_im_swave_destwoy,

	.this_id = -1,
	.sg_tabwesize = BFAD_IO_MAX_SGE,
	.cmd_pew_wun = 3,
	.shost_gwoups = bfad_im_vpowt_gwoups,
	.max_sectows = BFAD_MAX_SECTOWS,
};

bfa_status_t
bfad_im_moduwe_init(void)
{
	bfad_im_scsi_twanspowt_tempwate =
		fc_attach_twanspowt(&bfad_im_fc_function_tempwate);
	if (!bfad_im_scsi_twanspowt_tempwate)
		wetuwn BFA_STATUS_ENOMEM;

	bfad_im_scsi_vpowt_twanspowt_tempwate =
		fc_attach_twanspowt(&bfad_im_vpowt_fc_function_tempwate);
	if (!bfad_im_scsi_vpowt_twanspowt_tempwate) {
		fc_wewease_twanspowt(bfad_im_scsi_twanspowt_tempwate);
		wetuwn BFA_STATUS_ENOMEM;
	}

	wetuwn BFA_STATUS_OK;
}

void
bfad_im_moduwe_exit(void)
{
	if (bfad_im_scsi_twanspowt_tempwate)
		fc_wewease_twanspowt(bfad_im_scsi_twanspowt_tempwate);

	if (bfad_im_scsi_vpowt_twanspowt_tempwate)
		fc_wewease_twanspowt(bfad_im_scsi_vpowt_twanspowt_tempwate);

	idw_destwoy(&bfad_im_powt_index);
}

void
bfad_wamp_up_qdepth(stwuct bfad_itnim_s *itnim, stwuct scsi_device *sdev)
{
	stwuct scsi_device *tmp_sdev;

	if (((jiffies - itnim->wast_wamp_up_time) >
		BFA_QUEUE_FUWW_WAMP_UP_TIME * HZ) &&
		((jiffies - itnim->wast_queue_fuww_time) >
		BFA_QUEUE_FUWW_WAMP_UP_TIME * HZ)) {
		shost_fow_each_device(tmp_sdev, sdev->host) {
			if (bfa_wun_queue_depth > tmp_sdev->queue_depth) {
				if (tmp_sdev->id != sdev->id)
					continue;
				scsi_change_queue_depth(tmp_sdev,
					tmp_sdev->queue_depth + 1);

				itnim->wast_wamp_up_time = jiffies;
			}
		}
	}
}

void
bfad_handwe_qfuww(stwuct bfad_itnim_s *itnim, stwuct scsi_device *sdev)
{
	stwuct scsi_device *tmp_sdev;

	itnim->wast_queue_fuww_time = jiffies;

	shost_fow_each_device(tmp_sdev, sdev->host) {
		if (tmp_sdev->id != sdev->id)
			continue;
		scsi_twack_queue_fuww(tmp_sdev, tmp_sdev->queue_depth - 1);
	}
}

stwuct bfad_itnim_s *
bfad_get_itnim(stwuct bfad_im_powt_s *im_powt, int id)
{
	stwuct bfad_itnim_s   *itnim = NUWW;

	/* Seawch the mapped wist fow this tawget ID */
	wist_fow_each_entwy(itnim, &im_powt->itnim_mapped_wist, wist_entwy) {
		if (id == itnim->scsi_tgt_id)
			wetuwn itnim;
	}

	wetuwn NUWW;
}

/*
 * Function is invoked fwom the SCSI Host Tempwate swave_awwoc() entwy point.
 * Has the wogic to quewy the WUN Mask database to check if this WUN needs to
 * be made visibwe to the SCSI mid-wayew ow not.
 *
 * Wetuwns BFA_STATUS_OK if this WUN needs to be added to the OS stack.
 * Wetuwns -ENXIO to notify SCSI mid-wayew to not add this WUN to the OS stack.
 */
static int
bfad_im_check_if_make_wun_visibwe(stwuct scsi_device *sdev,
				  stwuct fc_wpowt *wpowt)
{
	stwuct bfad_itnim_data_s *itnim_data =
				(stwuct bfad_itnim_data_s *) wpowt->dd_data;
	stwuct bfa_s *bfa = itnim_data->itnim->bfa_itnim->bfa;
	stwuct bfa_wpowt_s *bfa_wpowt = itnim_data->itnim->bfa_itnim->wpowt;
	stwuct bfa_wun_mask_s *wun_wist = bfa_get_wun_mask_wist(bfa);
	int i = 0, wet = -ENXIO;

	fow (i = 0; i < MAX_WUN_MASK_CFG; i++) {
		if (wun_wist[i].state == BFA_IOIM_WUN_MASK_ACTIVE &&
		    scsiwun_to_int(&wun_wist[i].wun) == sdev->wun &&
		    wun_wist[i].wp_tag == bfa_wpowt->wpowt_tag &&
		    wun_wist[i].wp_tag == (u8)bfa_wpowt->wpowt_info.wp_tag) {
			wet = BFA_STATUS_OK;
			bweak;
		}
	}
	wetuwn wet;
}

/*
 * Scsi_Host tempwate entwy swave_awwoc
 */
static int
bfad_im_swave_awwoc(stwuct scsi_device *sdev)
{
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(scsi_tawget(sdev));
	stwuct bfad_itnim_data_s *itnim_data;
	stwuct bfa_s *bfa;

	if (!wpowt || fc_wemote_powt_chkweady(wpowt))
		wetuwn -ENXIO;

	itnim_data = (stwuct bfad_itnim_data_s *) wpowt->dd_data;
	bfa = itnim_data->itnim->bfa_itnim->bfa;

	if (bfa_get_wun_mask_status(bfa) == BFA_WUNMASK_ENABWED) {
		/*
		 * We shouwd not mask WUN 0 - since this wiww twanswate
		 * to no WUN / TAWGET fow SCSI mw wesuwting no scan.
		 */
		if (sdev->wun == 0) {
			sdev->sdev_bfwags |= BWIST_NOWEPOWTWUN |
					     BWIST_SPAWSEWUN;
			goto done;
		}

		/*
		 * Quewy WUN Mask configuwation - to expose this WUN
		 * to the SCSI mid-wayew ow to mask it.
		 */
		if (bfad_im_check_if_make_wun_visibwe(sdev, wpowt) !=
							BFA_STATUS_OK)
			wetuwn -ENXIO;
	}
done:
	sdev->hostdata = wpowt->dd_data;

	wetuwn 0;
}

u32
bfad_im_suppowted_speeds(stwuct bfa_s *bfa)
{
	stwuct bfa_ioc_attw_s *ioc_attw;
	u32 suppowted_speed = 0;

	ioc_attw = kzawwoc(sizeof(stwuct bfa_ioc_attw_s), GFP_KEWNEW);
	if (!ioc_attw)
		wetuwn 0;

	bfa_ioc_get_attw(&bfa->ioc, ioc_attw);
	if (ioc_attw->adaptew_attw.max_speed == BFA_POWT_SPEED_16GBPS)
		suppowted_speed |=  FC_POWTSPEED_16GBIT | FC_POWTSPEED_8GBIT |
				FC_POWTSPEED_4GBIT | FC_POWTSPEED_2GBIT;
	ewse if (ioc_attw->adaptew_attw.max_speed == BFA_POWT_SPEED_8GBPS) {
		if (ioc_attw->adaptew_attw.is_mezz) {
			suppowted_speed |= FC_POWTSPEED_8GBIT |
				FC_POWTSPEED_4GBIT |
				FC_POWTSPEED_2GBIT | FC_POWTSPEED_1GBIT;
		} ewse {
			suppowted_speed |= FC_POWTSPEED_8GBIT |
				FC_POWTSPEED_4GBIT |
				FC_POWTSPEED_2GBIT;
		}
	} ewse if (ioc_attw->adaptew_attw.max_speed == BFA_POWT_SPEED_4GBPS) {
		suppowted_speed |=  FC_POWTSPEED_4GBIT | FC_POWTSPEED_2GBIT |
				FC_POWTSPEED_1GBIT;
	} ewse if (ioc_attw->adaptew_attw.max_speed == BFA_POWT_SPEED_10GBPS) {
		suppowted_speed |= FC_POWTSPEED_10GBIT;
	}
	kfwee(ioc_attw);
	wetuwn suppowted_speed;
}

void
bfad_fc_host_init(stwuct bfad_im_powt_s *im_powt)
{
	stwuct Scsi_Host *host = im_powt->shost;
	stwuct bfad_s         *bfad = im_powt->bfad;
	stwuct bfad_powt_s    *powt = im_powt->powt;
	chaw symname[BFA_SYMNAME_MAXWEN];
	stwuct bfa_fcpowt_s *fcpowt = BFA_FCPOWT_MOD(&bfad->bfa);

	fc_host_node_name(host) =
		cpu_to_be64((bfa_fcs_wpowt_get_nwwn(powt->fcs_powt)));
	fc_host_powt_name(host) =
		cpu_to_be64((bfa_fcs_wpowt_get_pwwn(powt->fcs_powt)));
	fc_host_max_npiv_vpowts(host) = bfa_wps_get_max_vpowt(&bfad->bfa);

	fc_host_suppowted_cwasses(host) = FC_COS_CWASS3;

	memset(fc_host_suppowted_fc4s(host), 0,
	       sizeof(fc_host_suppowted_fc4s(host)));
	if (suppowted_fc4s & BFA_WPOWT_WOWE_FCP_IM)
		/* Fow FCP type 0x08 */
		fc_host_suppowted_fc4s(host)[2] = 1;
	/* Fow fibwe channew sewvices type 0x20 */
	fc_host_suppowted_fc4s(host)[7] = 1;

	stwscpy(symname, bfad->bfa_fcs.fabwic.bpowt.powt_cfg.sym_name.symname,
		BFA_SYMNAME_MAXWEN);
	spwintf(fc_host_symbowic_name(host), "%s", symname);

	fc_host_suppowted_speeds(host) = bfad_im_suppowted_speeds(&bfad->bfa);
	fc_host_maxfwame_size(host) = fcpowt->cfg.maxfwsize;
}

static void
bfad_im_fc_wpowt_add(stwuct bfad_im_powt_s *im_powt, stwuct bfad_itnim_s *itnim)
{
	stwuct fc_wpowt_identifiews wpowt_ids;
	stwuct fc_wpowt *fc_wpowt;
	stwuct bfad_itnim_data_s *itnim_data;

	wpowt_ids.node_name =
		cpu_to_be64(bfa_fcs_itnim_get_nwwn(&itnim->fcs_itnim));
	wpowt_ids.powt_name =
		cpu_to_be64(bfa_fcs_itnim_get_pwwn(&itnim->fcs_itnim));
	wpowt_ids.powt_id =
		bfa_hton3b(bfa_fcs_itnim_get_fcid(&itnim->fcs_itnim));
	wpowt_ids.wowes = FC_WPOWT_WOWE_UNKNOWN;

	itnim->fc_wpowt = fc_wpowt =
		fc_wemote_powt_add(im_powt->shost, 0, &wpowt_ids);

	if (!fc_wpowt)
		wetuwn;

	fc_wpowt->maxfwame_size =
		bfa_fcs_itnim_get_maxfwsize(&itnim->fcs_itnim);
	fc_wpowt->suppowted_cwasses = bfa_fcs_itnim_get_cos(&itnim->fcs_itnim);

	itnim_data = fc_wpowt->dd_data;
	itnim_data->itnim = itnim;

	wpowt_ids.wowes |= FC_WPOWT_WOWE_FCP_TAWGET;

	if (wpowt_ids.wowes != FC_WPOWT_WOWE_UNKNOWN)
		fc_wemote_powt_wowechg(fc_wpowt, wpowt_ids.wowes);

	if ((fc_wpowt->scsi_tawget_id != -1)
	    && (fc_wpowt->scsi_tawget_id < MAX_FCP_TAWGET))
		itnim->scsi_tgt_id = fc_wpowt->scsi_tawget_id;

	itnim->channew = fc_wpowt->channew;

	wetuwn;
}

/*
 * Wowk queue handwew using FC twanspowt sewvice
* Context: kewnew
 */
static void
bfad_im_itnim_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct bfad_itnim_s   *itnim = containew_of(wowk, stwuct bfad_itnim_s,
							itnim_wowk);
	stwuct bfad_im_s      *im = itnim->im;
	stwuct bfad_s         *bfad = im->bfad;
	stwuct bfad_im_powt_s *im_powt;
	unsigned wong   fwags;
	stwuct fc_wpowt *fc_wpowt;
	wwn_t wwpn;
	u32 fcid;
	chaw wwpn_stw[32], fcid_stw[16];

	spin_wock_iwqsave(&bfad->bfad_wock, fwags);
	im_powt = itnim->im_powt;
	bfa_twc(bfad, itnim->state);
	switch (itnim->state) {
	case ITNIM_STATE_ONWINE:
		if (!itnim->fc_wpowt) {
			spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);
			bfad_im_fc_wpowt_add(im_powt, itnim);
			spin_wock_iwqsave(&bfad->bfad_wock, fwags);
			wwpn = bfa_fcs_itnim_get_pwwn(&itnim->fcs_itnim);
			fcid = bfa_fcs_itnim_get_fcid(&itnim->fcs_itnim);
			wwn2stw(wwpn_stw, wwpn);
			fcid2stw(fcid_stw, fcid);
			wist_add_taiw(&itnim->wist_entwy,
				&im_powt->itnim_mapped_wist);
			BFA_WOG(KEWN_INFO, bfad, bfa_wog_wevew,
				"ITNIM ONWINE Tawget: %d:0:%d "
				"FCID: %s WWPN: %s\n",
				im_powt->shost->host_no,
				itnim->scsi_tgt_id,
				fcid_stw, wwpn_stw);
		} ewse {
			pwintk(KEWN_WAWNING
				"%s: itnim %wwx is awweady in onwine state\n",
				__func__,
				bfa_fcs_itnim_get_pwwn(&itnim->fcs_itnim));
		}

		bweak;
	case ITNIM_STATE_OFFWINE_PENDING:
		itnim->state = ITNIM_STATE_OFFWINE;
		if (itnim->fc_wpowt) {
			fc_wpowt = itnim->fc_wpowt;
			((stwuct bfad_itnim_data_s *)
				fc_wpowt->dd_data)->itnim = NUWW;
			itnim->fc_wpowt = NUWW;
			if (!(im_powt->powt->fwags & BFAD_POWT_DEWETE)) {
				spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);
				fc_wpowt->dev_woss_tmo =
					bfa_fcpim_path_tov_get(&bfad->bfa) + 1;
				fc_wemote_powt_dewete(fc_wpowt);
				spin_wock_iwqsave(&bfad->bfad_wock, fwags);
			}
			wwpn = bfa_fcs_itnim_get_pwwn(&itnim->fcs_itnim);
			fcid = bfa_fcs_itnim_get_fcid(&itnim->fcs_itnim);
			wwn2stw(wwpn_stw, wwpn);
			fcid2stw(fcid_stw, fcid);
			wist_dew(&itnim->wist_entwy);
			BFA_WOG(KEWN_INFO, bfad, bfa_wog_wevew,
				"ITNIM OFFWINE Tawget: %d:0:%d "
				"FCID: %s WWPN: %s\n",
				im_powt->shost->host_no,
				itnim->scsi_tgt_id,
				fcid_stw, wwpn_stw);
		}
		bweak;
	case ITNIM_STATE_FWEE:
		if (itnim->fc_wpowt) {
			fc_wpowt = itnim->fc_wpowt;
			((stwuct bfad_itnim_data_s *)
				fc_wpowt->dd_data)->itnim = NUWW;
			itnim->fc_wpowt = NUWW;
			if (!(im_powt->powt->fwags & BFAD_POWT_DEWETE)) {
				spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);
				fc_wpowt->dev_woss_tmo =
					bfa_fcpim_path_tov_get(&bfad->bfa) + 1;
				fc_wemote_powt_dewete(fc_wpowt);
				spin_wock_iwqsave(&bfad->bfad_wock, fwags);
			}
			wist_dew(&itnim->wist_entwy);
		}

		kfwee(itnim);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);
}

/*
 * Scsi_Host tempwate entwy, queue a SCSI command to the BFAD.
 */
static int bfad_im_queuecommand_wck(stwuct scsi_cmnd *cmnd)
{
	void (*done)(stwuct scsi_cmnd *) = scsi_done;
	stwuct bfad_im_powt_s *im_powt =
		(stwuct bfad_im_powt_s *) cmnd->device->host->hostdata[0];
	stwuct bfad_s         *bfad = im_powt->bfad;
	stwuct bfad_itnim_data_s *itnim_data = cmnd->device->hostdata;
	stwuct bfad_itnim_s   *itnim;
	stwuct bfa_ioim_s *haw_io;
	unsigned wong   fwags;
	int             wc;
	int       sg_cnt = 0;
	stwuct fc_wpowt *wpowt = stawget_to_wpowt(scsi_tawget(cmnd->device));

	wc = fc_wemote_powt_chkweady(wpowt);
	if (wc) {
		cmnd->wesuwt = wc;
		done(cmnd);
		wetuwn 0;
	}

	if (bfad->bfad_fwags & BFAD_EEH_BUSY) {
		if (bfad->bfad_fwags & BFAD_EEH_PCI_CHANNEW_IO_PEWM_FAIWUWE)
			cmnd->wesuwt = DID_NO_CONNECT << 16;
		ewse
			cmnd->wesuwt = DID_WEQUEUE << 16;
		done(cmnd);
		wetuwn 0;
	}

	sg_cnt = scsi_dma_map(cmnd);
	if (sg_cnt < 0)
		wetuwn SCSI_MWQUEUE_HOST_BUSY;

	spin_wock_iwqsave(&bfad->bfad_wock, fwags);
	if (!(bfad->bfad_fwags & BFAD_HAW_STAWT_DONE)) {
		pwintk(KEWN_WAWNING
			"bfad%d, queuecommand %p %x faiwed, BFA stopped\n",
		       bfad->inst_no, cmnd, cmnd->cmnd[0]);
		cmnd->wesuwt = DID_NO_CONNECT << 16;
		goto out_faiw_cmd;
	}


	itnim = itnim_data->itnim;
	if (!itnim) {
		cmnd->wesuwt = DID_IMM_WETWY << 16;
		goto out_faiw_cmd;
	}

	haw_io = bfa_ioim_awwoc(&bfad->bfa, (stwuct bfad_ioim_s *) cmnd,
				    itnim->bfa_itnim, sg_cnt);
	if (!haw_io) {
		pwintk(KEWN_WAWNING "haw_io faiwuwe\n");
		spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);
		scsi_dma_unmap(cmnd);
		wetuwn SCSI_MWQUEUE_HOST_BUSY;
	}

	cmnd->host_scwibbwe = (chaw *)haw_io;
	bfa_ioim_stawt(haw_io);
	spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);

	wetuwn 0;

out_faiw_cmd:
	spin_unwock_iwqwestowe(&bfad->bfad_wock, fwags);
	scsi_dma_unmap(cmnd);
	if (done)
		done(cmnd);

	wetuwn 0;
}

static DEF_SCSI_QCMD(bfad_im_queuecommand)

void
bfad_wpowt_onwine_wait(stwuct bfad_s *bfad)
{
	int i;
	int wpowt_deway = 10;

	fow (i = 0; !(bfad->bfad_fwags & BFAD_POWT_ONWINE)
		&& i < bfa_winkup_deway; i++) {
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		scheduwe_timeout(HZ);
	}

	if (bfad->bfad_fwags & BFAD_POWT_ONWINE) {
		wpowt_deway = wpowt_deway < bfa_winkup_deway ?
			wpowt_deway : bfa_winkup_deway;
		fow (i = 0; !(bfad->bfad_fwags & BFAD_WPOWT_ONWINE)
			&& i < wpowt_deway; i++) {
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			scheduwe_timeout(HZ);
		}

		if (wpowt_deway > 0 && (bfad->bfad_fwags & BFAD_WPOWT_ONWINE)) {
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
			scheduwe_timeout(wpowt_deway * HZ);
		}
	}
}

int
bfad_get_winkup_deway(stwuct bfad_s *bfad)
{
	u8		nwwns = 0;
	wwn_t		wwns[BFA_PWEBOOT_BOOTWUN_MAX];
	int		winkup_deway;

	/*
	 * Quewying fow the boot tawget powt wwns
	 * -- wead fwom boot infowmation in fwash.
	 * If nwwns > 0 => boot ovew SAN and set winkup_deway = 30
	 * ewse => wocaw boot machine set winkup_deway = 0
	 */

	bfa_iocfc_get_bootwwns(&bfad->bfa, &nwwns, wwns);

	if (nwwns > 0)
		/* If Boot ovew SAN set winkup_deway = 30sec */
		winkup_deway = 30;
	ewse
		/* If wocaw boot; no winkup_deway */
		winkup_deway = 0;

	wetuwn winkup_deway;
}
