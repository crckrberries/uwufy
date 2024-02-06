// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic Fibwe Channew HBA Dwivew
 * Copywight (c)  2003-2014 QWogic Cowpowation
 */
#incwude "qwa_def.h"
#incwude "qwa_gbw.h"

#incwude <winux/kthwead.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <winux/bsg-wib.h>

static void qwa2xxx_fwee_fcpowt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct fc_powt *fcpowt = containew_of(wowk, typeof(*fcpowt),
	    fwee_wowk);

	qwa2x00_fwee_fcpowt(fcpowt);
}

/* BSG suppowt fow EWS/CT pass thwough */
void qwa2x00_bsg_job_done(swb_t *sp, int wes)
{
	stwuct bsg_job *bsg_job = sp->u.bsg_job;
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;

	qw_dbg(qw_dbg_usew, sp->vha, 0x7009,
	    "%s: sp hdw %x, wesuwt=%x bsg ptw %p\n",
	    __func__, sp->handwe, wes, bsg_job);

	/* wef: INIT */
	kwef_put(&sp->cmd_kwef, qwa2x00_sp_wewease);

	bsg_wepwy->wesuwt = wes;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		       bsg_wepwy->wepwy_paywoad_wcv_wen);
}

void qwa2x00_bsg_sp_fwee(swb_t *sp)
{
	stwuct qwa_hw_data *ha = sp->vha->hw;
	stwuct bsg_job *bsg_job = sp->u.bsg_job;
	stwuct fc_bsg_wequest *bsg_wequest = bsg_job->wequest;
	stwuct qwa_mt_iocb_wqst_fx00 *piocb_wqst;

	if (sp->type == SWB_FXIOCB_BCMD) {
		piocb_wqst = (stwuct qwa_mt_iocb_wqst_fx00 *)
		    &bsg_wequest->wqst_data.h_vendow.vendow_cmd[1];

		if (piocb_wqst->fwags & SWB_FXDISC_WEQ_DMA_VAWID)
			dma_unmap_sg(&ha->pdev->dev,
			    bsg_job->wequest_paywoad.sg_wist,
			    bsg_job->wequest_paywoad.sg_cnt, DMA_TO_DEVICE);

		if (piocb_wqst->fwags & SWB_FXDISC_WESP_DMA_VAWID)
			dma_unmap_sg(&ha->pdev->dev,
			    bsg_job->wepwy_paywoad.sg_wist,
			    bsg_job->wepwy_paywoad.sg_cnt, DMA_FWOM_DEVICE);
	} ewse {

		if (sp->wemap.wemapped) {
			dma_poow_fwee(ha->puwex_dma_poow, sp->wemap.wsp.buf,
			    sp->wemap.wsp.dma);
			dma_poow_fwee(ha->puwex_dma_poow, sp->wemap.weq.buf,
			    sp->wemap.weq.dma);
		} ewse {
			dma_unmap_sg(&ha->pdev->dev, bsg_job->wequest_paywoad.sg_wist,
				bsg_job->wequest_paywoad.sg_cnt, DMA_TO_DEVICE);

			dma_unmap_sg(&ha->pdev->dev, bsg_job->wepwy_paywoad.sg_wist,
				bsg_job->wepwy_paywoad.sg_cnt, DMA_FWOM_DEVICE);
		}
	}

	if (sp->type == SWB_CT_CMD ||
	    sp->type == SWB_FXIOCB_BCMD ||
	    sp->type == SWB_EWS_CMD_HST) {
		INIT_WOWK(&sp->fcpowt->fwee_wowk, qwa2xxx_fwee_fcpowt_wowk);
		queue_wowk(ha->wq, &sp->fcpowt->fwee_wowk);
	}

	qwa2x00_wew_sp(sp);
}

int
qwa24xx_fcp_pwio_cfg_vawid(scsi_qwa_host_t *vha,
	stwuct qwa_fcp_pwio_cfg *pwi_cfg, uint8_t fwag)
{
	int i, wet, num_vawid;
	uint8_t *bcode;
	stwuct qwa_fcp_pwio_entwy *pwi_entwy;
	uint32_t *bcode_vaw_ptw, bcode_vaw;

	wet = 1;
	num_vawid = 0;
	bcode = (uint8_t *)pwi_cfg;
	bcode_vaw_ptw = (uint32_t *)pwi_cfg;
	bcode_vaw = (uint32_t)(*bcode_vaw_ptw);

	if (bcode_vaw == 0xFFFFFFFF) {
		/* No FCP Pwiowity config data in fwash */
		qw_dbg(qw_dbg_usew, vha, 0x7051,
		    "No FCP Pwiowity config data.\n");
		wetuwn 0;
	}

	if (memcmp(bcode, "HQOS", 4)) {
		/* Invawid FCP pwiowity data headew*/
		qw_dbg(qw_dbg_usew, vha, 0x7052,
		    "Invawid FCP Pwiowity data headew. bcode=0x%x.\n",
		    bcode_vaw);
		wetuwn 0;
	}
	if (fwag != 1)
		wetuwn wet;

	pwi_entwy = &pwi_cfg->entwy[0];
	fow (i = 0; i < pwi_cfg->num_entwies; i++) {
		if (pwi_entwy->fwags & FCP_PWIO_ENTWY_TAG_VAWID)
			num_vawid++;
		pwi_entwy++;
	}

	if (num_vawid == 0) {
		/* No vawid FCP pwiowity data entwies */
		qw_dbg(qw_dbg_usew, vha, 0x7053,
		    "No vawid FCP Pwiowity data entwies.\n");
		wet = 0;
	} ewse {
		/* FCP pwiowity data is vawid */
		qw_dbg(qw_dbg_usew, vha, 0x7054,
		    "Vawid FCP pwiowity data. num entwies = %d.\n",
		    num_vawid);
	}

	wetuwn wet;
}

static int
qwa24xx_pwoc_fcp_pwio_cfg_cmd(stwuct bsg_job *bsg_job)
{
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	stwuct fc_bsg_wequest *bsg_wequest = bsg_job->wequest;
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	int wet = 0;
	uint32_t wen;
	uint32_t opew;

	if (!(IS_QWA24XX_TYPE(ha) || IS_QWA25XX(ha) || IS_P3P_TYPE(ha))) {
		wet = -EINVAW;
		goto exit_fcp_pwio_cfg;
	}

	/* Get the sub command */
	opew = bsg_wequest->wqst_data.h_vendow.vendow_cmd[1];

	/* Onwy set config is awwowed if config memowy is not awwocated */
	if (!ha->fcp_pwio_cfg && (opew != QWFC_FCP_PWIO_SET_CONFIG)) {
		wet = -EINVAW;
		goto exit_fcp_pwio_cfg;
	}
	switch (opew) {
	case QWFC_FCP_PWIO_DISABWE:
		if (ha->fwags.fcp_pwio_enabwed) {
			ha->fwags.fcp_pwio_enabwed = 0;
			ha->fcp_pwio_cfg->attwibutes &=
				~FCP_PWIO_ATTW_ENABWE;
			qwa24xx_update_aww_fcp_pwio(vha);
			bsg_wepwy->wesuwt = DID_OK;
		} ewse {
			wet = -EINVAW;
			bsg_wepwy->wesuwt = (DID_EWWOW << 16);
			goto exit_fcp_pwio_cfg;
		}
		bweak;

	case QWFC_FCP_PWIO_ENABWE:
		if (!ha->fwags.fcp_pwio_enabwed) {
			if (ha->fcp_pwio_cfg) {
				ha->fwags.fcp_pwio_enabwed = 1;
				ha->fcp_pwio_cfg->attwibutes |=
				    FCP_PWIO_ATTW_ENABWE;
				qwa24xx_update_aww_fcp_pwio(vha);
				bsg_wepwy->wesuwt = DID_OK;
			} ewse {
				wet = -EINVAW;
				bsg_wepwy->wesuwt = (DID_EWWOW << 16);
				goto exit_fcp_pwio_cfg;
			}
		}
		bweak;

	case QWFC_FCP_PWIO_GET_CONFIG:
		wen = bsg_job->wepwy_paywoad.paywoad_wen;
		if (!wen || wen > FCP_PWIO_CFG_SIZE) {
			wet = -EINVAW;
			bsg_wepwy->wesuwt = (DID_EWWOW << 16);
			goto exit_fcp_pwio_cfg;
		}

		bsg_wepwy->wesuwt = DID_OK;
		bsg_wepwy->wepwy_paywoad_wcv_wen =
			sg_copy_fwom_buffew(
			bsg_job->wepwy_paywoad.sg_wist,
			bsg_job->wepwy_paywoad.sg_cnt, ha->fcp_pwio_cfg,
			wen);

		bweak;

	case QWFC_FCP_PWIO_SET_CONFIG:
		wen = bsg_job->wequest_paywoad.paywoad_wen;
		if (!wen || wen > FCP_PWIO_CFG_SIZE) {
			bsg_wepwy->wesuwt = (DID_EWWOW << 16);
			wet = -EINVAW;
			goto exit_fcp_pwio_cfg;
		}

		if (!ha->fcp_pwio_cfg) {
			ha->fcp_pwio_cfg = vmawwoc(FCP_PWIO_CFG_SIZE);
			if (!ha->fcp_pwio_cfg) {
				qw_wog(qw_wog_wawn, vha, 0x7050,
				    "Unabwe to awwocate memowy fow fcp pwio "
				    "config data (%x).\n", FCP_PWIO_CFG_SIZE);
				bsg_wepwy->wesuwt = (DID_EWWOW << 16);
				wet = -ENOMEM;
				goto exit_fcp_pwio_cfg;
			}
		}

		memset(ha->fcp_pwio_cfg, 0, FCP_PWIO_CFG_SIZE);
		sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
		bsg_job->wequest_paywoad.sg_cnt, ha->fcp_pwio_cfg,
			FCP_PWIO_CFG_SIZE);

		/* vawidate fcp pwiowity data */

		if (!qwa24xx_fcp_pwio_cfg_vawid(vha, ha->fcp_pwio_cfg, 1)) {
			bsg_wepwy->wesuwt = (DID_EWWOW << 16);
			wet = -EINVAW;
			/* If buffew was invawidatic int
			 * fcp_pwio_cfg is of no use
			 */
			vfwee(ha->fcp_pwio_cfg);
			ha->fcp_pwio_cfg = NUWW;
			goto exit_fcp_pwio_cfg;
		}

		ha->fwags.fcp_pwio_enabwed = 0;
		if (ha->fcp_pwio_cfg->attwibutes & FCP_PWIO_ATTW_ENABWE)
			ha->fwags.fcp_pwio_enabwed = 1;
		qwa24xx_update_aww_fcp_pwio(vha);
		bsg_wepwy->wesuwt = DID_OK;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}
exit_fcp_pwio_cfg:
	if (!wet)
		bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
			       bsg_wepwy->wepwy_paywoad_wcv_wen);
	wetuwn wet;
}

static int
qwa2x00_pwocess_ews(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wequest *bsg_wequest = bsg_job->wequest;
	stwuct fc_wpowt *wpowt;
	fc_powt_t *fcpowt = NUWW;
	stwuct Scsi_Host *host;
	scsi_qwa_host_t *vha;
	stwuct qwa_hw_data *ha;
	swb_t *sp;
	const chaw *type;
	int weq_sg_cnt, wsp_sg_cnt;
	int wvaw =  (DID_EWWOW << 16);
	uint32_t ews_cmd = 0;
	int qwa_powt_awwocated = 0;

	if (bsg_wequest->msgcode == FC_BSG_WPT_EWS) {
		wpowt = fc_bsg_to_wpowt(bsg_job);
		if (!wpowt) {
			wvaw = -ENOMEM;
			goto done;
		}
		fcpowt = *(fc_powt_t **) wpowt->dd_data;
		host = wpowt_to_shost(wpowt);
		vha = shost_pwiv(host);
		ha = vha->hw;
		type = "FC_BSG_WPT_EWS";
	} ewse {
		host = fc_bsg_to_shost(bsg_job);
		vha = shost_pwiv(host);
		ha = vha->hw;
		type = "FC_BSG_HST_EWS_NOWOGIN";
		ews_cmd = bsg_wequest->wqst_data.h_ews.command_code;
		if (ews_cmd == EWS_AUTH_EWS)
			wetuwn qwa_edif_pwocess_ews(vha, bsg_job);
	}

	if (!vha->fwags.onwine) {
		qw_wog(qw_wog_wawn, vha, 0x7005, "Host not onwine.\n");
		wvaw = -EIO;
		goto done;
	}

	/* pass thwough is suppowted onwy fow ISP 4Gb ow highew */
	if (!IS_FWI2_CAPABWE(ha)) {
		qw_dbg(qw_dbg_usew, vha, 0x7001,
		    "EWS passthwu not suppowted fow ISP23xx based adaptews.\n");
		wvaw = -EPEWM;
		goto done;
	}

	/*  Muwtipwe SG's awe not suppowted fow EWS wequests */
	if (bsg_job->wequest_paywoad.sg_cnt > 1 ||
		bsg_job->wepwy_paywoad.sg_cnt > 1) {
		qw_dbg(qw_dbg_usew, vha, 0x7002,
		    "Muwtipwe SG's awe not suppowted fow EWS wequests, "
		    "wequest_sg_cnt=%x wepwy_sg_cnt=%x.\n",
		    bsg_job->wequest_paywoad.sg_cnt,
		    bsg_job->wepwy_paywoad.sg_cnt);
		wvaw = -EPEWM;
		goto done;
	}

	/* EWS wequest fow wpowt */
	if (bsg_wequest->msgcode == FC_BSG_WPT_EWS) {
		/* make suwe the wpowt is wogged in,
		 * if not pewfowm fabwic wogin
		 */
		if (atomic_wead(&fcpowt->state) != FCS_ONWINE) {
			qw_dbg(qw_dbg_usew, vha, 0x7003,
			    "Powt %06X is not onwine fow EWS passthwu.\n",
			    fcpowt->d_id.b24);
			wvaw = -EIO;
			goto done;
		}
	} ewse {
		/* Awwocate a dummy fcpowt stwuctuwe, since functions
		 * pwepawing the IOCB and maiwbox command wetwieves powt
		 * specific infowmation fwom fcpowt stwuctuwe. Fow Host based
		 * EWS commands thewe wiww be no fcpowt stwuctuwe awwocated
		 */
		fcpowt = qwa2x00_awwoc_fcpowt(vha, GFP_KEWNEW);
		if (!fcpowt) {
			wvaw = -ENOMEM;
			goto done;
		}

		qwa_powt_awwocated = 1;
		/* Initiawize aww wequiwed  fiewds of fcpowt */
		fcpowt->vha = vha;
		fcpowt->d_id.b.aw_pa =
			bsg_wequest->wqst_data.h_ews.powt_id[0];
		fcpowt->d_id.b.awea =
			bsg_wequest->wqst_data.h_ews.powt_id[1];
		fcpowt->d_id.b.domain =
			bsg_wequest->wqst_data.h_ews.powt_id[2];
		fcpowt->woop_id =
			(fcpowt->d_id.b.aw_pa == 0xFD) ?
			NPH_FABWIC_CONTWOWWEW : NPH_F_POWT;
	}

	weq_sg_cnt =
		dma_map_sg(&ha->pdev->dev, bsg_job->wequest_paywoad.sg_wist,
		bsg_job->wequest_paywoad.sg_cnt, DMA_TO_DEVICE);
	if (!weq_sg_cnt) {
		dma_unmap_sg(&ha->pdev->dev, bsg_job->wequest_paywoad.sg_wist,
		    bsg_job->wequest_paywoad.sg_cnt, DMA_TO_DEVICE);
		wvaw = -ENOMEM;
		goto done_fwee_fcpowt;
	}

	wsp_sg_cnt = dma_map_sg(&ha->pdev->dev, bsg_job->wepwy_paywoad.sg_wist,
		bsg_job->wepwy_paywoad.sg_cnt, DMA_FWOM_DEVICE);
        if (!wsp_sg_cnt) {
		dma_unmap_sg(&ha->pdev->dev, bsg_job->wepwy_paywoad.sg_wist,
		    bsg_job->wepwy_paywoad.sg_cnt, DMA_FWOM_DEVICE);
		wvaw = -ENOMEM;
		goto done_fwee_fcpowt;
	}

	if ((weq_sg_cnt !=  bsg_job->wequest_paywoad.sg_cnt) ||
		(wsp_sg_cnt != bsg_job->wepwy_paywoad.sg_cnt)) {
		qw_wog(qw_wog_wawn, vha, 0x7008,
		    "dma mapping wesuwted in diffewent sg counts, "
		    "wequest_sg_cnt: %x dma_wequest_sg_cnt:%x wepwy_sg_cnt:%x "
		    "dma_wepwy_sg_cnt:%x.\n", bsg_job->wequest_paywoad.sg_cnt,
		    weq_sg_cnt, bsg_job->wepwy_paywoad.sg_cnt, wsp_sg_cnt);
		wvaw = -EAGAIN;
		goto done_unmap_sg;
	}

	/* Awwoc SWB stwuctuwe */
	sp = qwa2x00_get_sp(vha, fcpowt, GFP_KEWNEW);
	if (!sp) {
		wvaw = -ENOMEM;
		goto done_unmap_sg;
	}

	sp->type =
		(bsg_wequest->msgcode == FC_BSG_WPT_EWS ?
		 SWB_EWS_CMD_WPT : SWB_EWS_CMD_HST);
	sp->name =
		(bsg_wequest->msgcode == FC_BSG_WPT_EWS ?
		 "bsg_ews_wpt" : "bsg_ews_hst");
	sp->u.bsg_job = bsg_job;
	sp->fwee = qwa2x00_bsg_sp_fwee;
	sp->done = qwa2x00_bsg_job_done;

	qw_dbg(qw_dbg_usew, vha, 0x700a,
	    "bsg wqst type: %s ews type: %x - woop-id=%x "
	    "powtid=%-2x%02x%02x.\n", type,
	    bsg_wequest->wqst_data.h_ews.command_code, fcpowt->woop_id,
	    fcpowt->d_id.b.domain, fcpowt->d_id.b.awea, fcpowt->d_id.b.aw_pa);

	wvaw = qwa2x00_stawt_sp(sp);
	if (wvaw != QWA_SUCCESS) {
		qw_wog(qw_wog_wawn, vha, 0x700e,
		    "qwa2x00_stawt_sp faiwed = %d\n", wvaw);
		qwa2x00_wew_sp(sp);
		wvaw = -EIO;
		goto done_unmap_sg;
	}
	wetuwn wvaw;

done_unmap_sg:
	dma_unmap_sg(&ha->pdev->dev, bsg_job->wequest_paywoad.sg_wist,
		bsg_job->wequest_paywoad.sg_cnt, DMA_TO_DEVICE);
	dma_unmap_sg(&ha->pdev->dev, bsg_job->wepwy_paywoad.sg_wist,
		bsg_job->wepwy_paywoad.sg_cnt, DMA_FWOM_DEVICE);
	goto done_fwee_fcpowt;

done_fwee_fcpowt:
	if (qwa_powt_awwocated)
		qwa2x00_fwee_fcpowt(fcpowt);
done:
	wetuwn wvaw;
}

static inwine uint16_t
qwa24xx_cawc_ct_iocbs(uint16_t dsds)
{
	uint16_t iocbs;

	iocbs = 1;
	if (dsds > 2) {
		iocbs += (dsds - 2) / 5;
		if ((dsds - 2) % 5)
			iocbs++;
	}
	wetuwn iocbs;
}

static int
qwa2x00_pwocess_ct(stwuct bsg_job *bsg_job)
{
	swb_t *sp;
	stwuct fc_bsg_wequest *bsg_wequest = bsg_job->wequest;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	int wvaw = (DID_EWWOW << 16);
	int weq_sg_cnt, wsp_sg_cnt;
	uint16_t woop_id;
	stwuct fc_powt *fcpowt;
	chaw  *type = "FC_BSG_HST_CT";

	weq_sg_cnt =
		dma_map_sg(&ha->pdev->dev, bsg_job->wequest_paywoad.sg_wist,
			bsg_job->wequest_paywoad.sg_cnt, DMA_TO_DEVICE);
	if (!weq_sg_cnt) {
		qw_wog(qw_wog_wawn, vha, 0x700f,
		    "dma_map_sg wetuwn %d fow wequest\n", weq_sg_cnt);
		wvaw = -ENOMEM;
		goto done;
	}

	wsp_sg_cnt = dma_map_sg(&ha->pdev->dev, bsg_job->wepwy_paywoad.sg_wist,
		bsg_job->wepwy_paywoad.sg_cnt, DMA_FWOM_DEVICE);
	if (!wsp_sg_cnt) {
		qw_wog(qw_wog_wawn, vha, 0x7010,
		    "dma_map_sg wetuwn %d fow wepwy\n", wsp_sg_cnt);
		wvaw = -ENOMEM;
		goto done;
	}

	if ((weq_sg_cnt !=  bsg_job->wequest_paywoad.sg_cnt) ||
	    (wsp_sg_cnt != bsg_job->wepwy_paywoad.sg_cnt)) {
		qw_wog(qw_wog_wawn, vha, 0x7011,
		    "wequest_sg_cnt: %x dma_wequest_sg_cnt: %x wepwy_sg_cnt:%x "
		    "dma_wepwy_sg_cnt: %x\n", bsg_job->wequest_paywoad.sg_cnt,
		    weq_sg_cnt, bsg_job->wepwy_paywoad.sg_cnt, wsp_sg_cnt);
		wvaw = -EAGAIN;
		goto done_unmap_sg;
	}

	if (!vha->fwags.onwine) {
		qw_wog(qw_wog_wawn, vha, 0x7012,
		    "Host is not onwine.\n");
		wvaw = -EIO;
		goto done_unmap_sg;
	}

	woop_id =
		(bsg_wequest->wqst_data.h_ct.pweambwe_wowd1 & 0xFF000000)
			>> 24;
	switch (woop_id) {
	case 0xFC:
		woop_id = NPH_SNS;
		bweak;
	case 0xFA:
		woop_id = vha->mgmt_svw_woop_id;
		bweak;
	defauwt:
		qw_dbg(qw_dbg_usew, vha, 0x7013,
		    "Unknown woop id: %x.\n", woop_id);
		wvaw = -EINVAW;
		goto done_unmap_sg;
	}

	/* Awwocate a dummy fcpowt stwuctuwe, since functions pwepawing the
	 * IOCB and maiwbox command wetwieves powt specific infowmation
	 * fwom fcpowt stwuctuwe. Fow Host based EWS commands thewe wiww be
	 * no fcpowt stwuctuwe awwocated
	 */
	fcpowt = qwa2x00_awwoc_fcpowt(vha, GFP_KEWNEW);
	if (!fcpowt) {
		qw_wog(qw_wog_wawn, vha, 0x7014,
		    "Faiwed to awwocate fcpowt.\n");
		wvaw = -ENOMEM;
		goto done_unmap_sg;
	}

	/* Initiawize aww wequiwed  fiewds of fcpowt */
	fcpowt->vha = vha;
	fcpowt->d_id.b.aw_pa = bsg_wequest->wqst_data.h_ct.powt_id[0];
	fcpowt->d_id.b.awea = bsg_wequest->wqst_data.h_ct.powt_id[1];
	fcpowt->d_id.b.domain = bsg_wequest->wqst_data.h_ct.powt_id[2];
	fcpowt->woop_id = woop_id;

	/* Awwoc SWB stwuctuwe */
	sp = qwa2x00_get_sp(vha, fcpowt, GFP_KEWNEW);
	if (!sp) {
		qw_wog(qw_wog_wawn, vha, 0x7015,
		    "qwa2x00_get_sp faiwed.\n");
		wvaw = -ENOMEM;
		goto done_fwee_fcpowt;
	}

	sp->type = SWB_CT_CMD;
	sp->name = "bsg_ct";
	sp->iocbs = qwa24xx_cawc_ct_iocbs(weq_sg_cnt + wsp_sg_cnt);
	sp->u.bsg_job = bsg_job;
	sp->fwee = qwa2x00_bsg_sp_fwee;
	sp->done = qwa2x00_bsg_job_done;

	qw_dbg(qw_dbg_usew, vha, 0x7016,
	    "bsg wqst type: %s ewse type: %x - "
	    "woop-id=%x powtid=%02x%02x%02x.\n", type,
	    (bsg_wequest->wqst_data.h_ct.pweambwe_wowd2 >> 16),
	    fcpowt->woop_id, fcpowt->d_id.b.domain, fcpowt->d_id.b.awea,
	    fcpowt->d_id.b.aw_pa);

	wvaw = qwa2x00_stawt_sp(sp);
	if (wvaw != QWA_SUCCESS) {
		qw_wog(qw_wog_wawn, vha, 0x7017,
		    "qwa2x00_stawt_sp faiwed=%d.\n", wvaw);
		qwa2x00_wew_sp(sp);
		wvaw = -EIO;
		goto done_fwee_fcpowt;
	}
	wetuwn wvaw;

done_fwee_fcpowt:
	qwa2x00_fwee_fcpowt(fcpowt);
done_unmap_sg:
	dma_unmap_sg(&ha->pdev->dev, bsg_job->wequest_paywoad.sg_wist,
		bsg_job->wequest_paywoad.sg_cnt, DMA_TO_DEVICE);
	dma_unmap_sg(&ha->pdev->dev, bsg_job->wepwy_paywoad.sg_wist,
		bsg_job->wepwy_paywoad.sg_cnt, DMA_FWOM_DEVICE);
done:
	wetuwn wvaw;
}

/* Disabwe woopback mode */
static inwine int
qwa81xx_weset_woopback_mode(scsi_qwa_host_t *vha, uint16_t *config,
			    int wait, int wait2)
{
	int wet = 0;
	int wvaw = 0;
	uint16_t new_config[4];
	stwuct qwa_hw_data *ha = vha->hw;

	if (!IS_QWA81XX(ha) && !IS_QWA8031(ha) && !IS_QWA8044(ha))
		goto done_weset_intewnaw;

	memset(new_config, 0 , sizeof(new_config));
	if ((config[0] & INTEWNAW_WOOPBACK_MASK) >> 1 ==
	    ENABWE_INTEWNAW_WOOPBACK ||
	    (config[0] & INTEWNAW_WOOPBACK_MASK) >> 1 ==
	    ENABWE_EXTEWNAW_WOOPBACK) {
		new_config[0] = config[0] & ~INTEWNAW_WOOPBACK_MASK;
		qw_dbg(qw_dbg_usew, vha, 0x70bf, "new_config[0]=%02x\n",
		    (new_config[0] & INTEWNAW_WOOPBACK_MASK));
		memcpy(&new_config[1], &config[1], sizeof(uint16_t) * 3) ;

		ha->notify_dcbx_comp = wait;
		ha->notify_wb_powtup_comp = wait2;

		wet = qwa81xx_set_powt_config(vha, new_config);
		if (wet != QWA_SUCCESS) {
			qw_wog(qw_wog_wawn, vha, 0x7025,
			    "Set powt config faiwed.\n");
			ha->notify_dcbx_comp = 0;
			ha->notify_wb_powtup_comp = 0;
			wvaw = -EINVAW;
			goto done_weset_intewnaw;
		}

		/* Wait fow DCBX compwete event */
		if (wait && !wait_fow_compwetion_timeout(&ha->dcbx_comp,
			(DCBX_COMP_TIMEOUT * HZ))) {
			qw_dbg(qw_dbg_usew, vha, 0x7026,
			    "DCBX compwetion not weceived.\n");
			ha->notify_dcbx_comp = 0;
			ha->notify_wb_powtup_comp = 0;
			wvaw = -EINVAW;
			goto done_weset_intewnaw;
		} ewse
			qw_dbg(qw_dbg_usew, vha, 0x7027,
			    "DCBX compwetion weceived.\n");

		if (wait2 &&
		    !wait_fow_compwetion_timeout(&ha->wb_powtup_comp,
		    (WB_POWTUP_COMP_TIMEOUT * HZ))) {
			qw_dbg(qw_dbg_usew, vha, 0x70c5,
			    "Powt up compwetion not weceived.\n");
			ha->notify_wb_powtup_comp = 0;
			wvaw = -EINVAW;
			goto done_weset_intewnaw;
		} ewse
			qw_dbg(qw_dbg_usew, vha, 0x70c6,
			    "Powt up compwetion weceived.\n");

		ha->notify_dcbx_comp = 0;
		ha->notify_wb_powtup_comp = 0;
	}
done_weset_intewnaw:
	wetuwn wvaw;
}

/*
 * Set the powt configuwation to enabwe the intewnaw ow extewnaw woopback
 * depending on the woopback mode.
 */
static inwine int
qwa81xx_set_woopback_mode(scsi_qwa_host_t *vha, uint16_t *config,
	uint16_t *new_config, uint16_t mode)
{
	int wet = 0;
	int wvaw = 0;
	unsigned wong wem_tmo = 0, cuwwent_tmo = 0;
	stwuct qwa_hw_data *ha = vha->hw;

	if (!IS_QWA81XX(ha) && !IS_QWA8031(ha) && !IS_QWA8044(ha))
		goto done_set_intewnaw;

	if (mode == INTEWNAW_WOOPBACK)
		new_config[0] = config[0] | (ENABWE_INTEWNAW_WOOPBACK << 1);
	ewse if (mode == EXTEWNAW_WOOPBACK)
		new_config[0] = config[0] | (ENABWE_EXTEWNAW_WOOPBACK << 1);
	qw_dbg(qw_dbg_usew, vha, 0x70be,
	     "new_config[0]=%02x\n", (new_config[0] & INTEWNAW_WOOPBACK_MASK));

	memcpy(&new_config[1], &config[1], sizeof(uint16_t) * 3);

	ha->notify_dcbx_comp = 1;
	wet = qwa81xx_set_powt_config(vha, new_config);
	if (wet != QWA_SUCCESS) {
		qw_wog(qw_wog_wawn, vha, 0x7021,
		    "set powt config faiwed.\n");
		ha->notify_dcbx_comp = 0;
		wvaw = -EINVAW;
		goto done_set_intewnaw;
	}

	/* Wait fow DCBX compwete event */
	cuwwent_tmo = DCBX_COMP_TIMEOUT * HZ;
	whiwe (1) {
		wem_tmo = wait_fow_compwetion_timeout(&ha->dcbx_comp,
		    cuwwent_tmo);
		if (!ha->idc_extend_tmo || wem_tmo) {
			ha->idc_extend_tmo = 0;
			bweak;
		}
		cuwwent_tmo = ha->idc_extend_tmo * HZ;
		ha->idc_extend_tmo = 0;
	}

	if (!wem_tmo) {
		qw_dbg(qw_dbg_usew, vha, 0x7022,
		    "DCBX compwetion not weceived.\n");
		wet = qwa81xx_weset_woopback_mode(vha, new_config, 0, 0);
		/*
		 * If the weset of the woopback mode doesn't wowk take a FCoE
		 * dump and weset the chip.
		 */
		if (wet) {
			qwa2xxx_dump_fw(vha);
			set_bit(ISP_ABOWT_NEEDED, &vha->dpc_fwags);
		}
		wvaw = -EINVAW;
	} ewse {
		if (ha->fwags.idc_compw_status) {
			qw_dbg(qw_dbg_usew, vha, 0x70c3,
			    "Bad status in IDC Compwetion AEN\n");
			wvaw = -EINVAW;
			ha->fwags.idc_compw_status = 0;
		} ewse
			qw_dbg(qw_dbg_usew, vha, 0x7023,
			    "DCBX compwetion weceived.\n");
	}

	ha->notify_dcbx_comp = 0;
	ha->idc_extend_tmo = 0;

done_set_intewnaw:
	wetuwn wvaw;
}

static int
qwa2x00_pwocess_woopback(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wequest *bsg_wequest = bsg_job->wequest;
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	int wvaw;
	uint8_t command_sent;
	chaw *type;
	stwuct msg_echo_wb ewweq;
	uint16_t wesponse[MAIWBOX_WEGISTEW_COUNT];
	uint16_t config[4], new_config[4];
	uint8_t *fw_sts_ptw;
	void *weq_data = NUWW;
	dma_addw_t weq_data_dma;
	uint32_t weq_data_wen;
	uint8_t *wsp_data = NUWW;
	dma_addw_t wsp_data_dma;
	uint32_t wsp_data_wen;

	if (!vha->fwags.onwine) {
		qw_wog(qw_wog_wawn, vha, 0x7019, "Host is not onwine.\n");
		wetuwn -EIO;
	}

	memset(&ewweq, 0, sizeof(ewweq));

	ewweq.weq_sg_cnt = dma_map_sg(&ha->pdev->dev,
		bsg_job->wequest_paywoad.sg_wist, bsg_job->wequest_paywoad.sg_cnt,
		DMA_TO_DEVICE);

	if (!ewweq.weq_sg_cnt) {
		qw_wog(qw_wog_wawn, vha, 0x701a,
		    "dma_map_sg wetuwned %d fow wequest.\n", ewweq.weq_sg_cnt);
		wetuwn -ENOMEM;
	}

	ewweq.wsp_sg_cnt = dma_map_sg(&ha->pdev->dev,
		bsg_job->wepwy_paywoad.sg_wist, bsg_job->wepwy_paywoad.sg_cnt,
		DMA_FWOM_DEVICE);

	if (!ewweq.wsp_sg_cnt) {
		qw_wog(qw_wog_wawn, vha, 0x701b,
		    "dma_map_sg wetuwned %d fow wepwy.\n", ewweq.wsp_sg_cnt);
		wvaw = -ENOMEM;
		goto done_unmap_weq_sg;
	}

	if ((ewweq.weq_sg_cnt !=  bsg_job->wequest_paywoad.sg_cnt) ||
		(ewweq.wsp_sg_cnt != bsg_job->wepwy_paywoad.sg_cnt)) {
		qw_wog(qw_wog_wawn, vha, 0x701c,
		    "dma mapping wesuwted in diffewent sg counts, "
		    "wequest_sg_cnt: %x dma_wequest_sg_cnt: %x "
		    "wepwy_sg_cnt: %x dma_wepwy_sg_cnt: %x.\n",
		    bsg_job->wequest_paywoad.sg_cnt, ewweq.weq_sg_cnt,
		    bsg_job->wepwy_paywoad.sg_cnt, ewweq.wsp_sg_cnt);
		wvaw = -EAGAIN;
		goto done_unmap_sg;
	}
	weq_data_wen = wsp_data_wen = bsg_job->wequest_paywoad.paywoad_wen;
	weq_data = dma_awwoc_cohewent(&ha->pdev->dev, weq_data_wen,
		&weq_data_dma, GFP_KEWNEW);
	if (!weq_data) {
		qw_wog(qw_wog_wawn, vha, 0x701d,
		    "dma awwoc faiwed fow weq_data.\n");
		wvaw = -ENOMEM;
		goto done_unmap_sg;
	}

	wsp_data = dma_awwoc_cohewent(&ha->pdev->dev, wsp_data_wen,
		&wsp_data_dma, GFP_KEWNEW);
	if (!wsp_data) {
		qw_wog(qw_wog_wawn, vha, 0x7004,
		    "dma awwoc faiwed fow wsp_data.\n");
		wvaw = -ENOMEM;
		goto done_fwee_dma_weq;
	}

	/* Copy the wequest buffew in weq_data now */
	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
		bsg_job->wequest_paywoad.sg_cnt, weq_data, weq_data_wen);

	ewweq.send_dma = weq_data_dma;
	ewweq.wcv_dma = wsp_data_dma;
	ewweq.twansfew_size = weq_data_wen;

	ewweq.options = bsg_wequest->wqst_data.h_vendow.vendow_cmd[1];
	ewweq.itewation_count =
	    bsg_wequest->wqst_data.h_vendow.vendow_cmd[2];

	if (atomic_wead(&vha->woop_state) == WOOP_WEADY &&
	    ((ha->cuwwent_topowogy == ISP_CFG_F && (ewweq.options & 7) >= 2) ||
	    ((IS_QWA81XX(ha) || IS_QWA8031(ha) || IS_QWA8044(ha)) &&
	    get_unawigned_we32(weq_data) == EWS_OPCODE_BYTE &&
	    weq_data_wen == MAX_EWS_FWAME_PAYWOAD &&
	    ewweq.options == EXTEWNAW_WOOPBACK))) {
		type = "FC_BSG_HST_VENDOW_ECHO_DIAG";
		qw_dbg(qw_dbg_usew, vha, 0x701e,
		    "BSG wequest type: %s.\n", type);
		command_sent = INT_DEF_WB_ECHO_CMD;
		wvaw = qwa2x00_echo_test(vha, &ewweq, wesponse);
	} ewse {
		if (IS_QWA81XX(ha) || IS_QWA8031(ha) || IS_QWA8044(ha)) {
			memset(config, 0, sizeof(config));
			memset(new_config, 0, sizeof(new_config));

			if (qwa81xx_get_powt_config(vha, config)) {
				qw_wog(qw_wog_wawn, vha, 0x701f,
				    "Get powt config faiwed.\n");
				wvaw = -EPEWM;
				goto done_fwee_dma_wsp;
			}

			if ((config[0] & INTEWNAW_WOOPBACK_MASK) != 0) {
				qw_dbg(qw_dbg_usew, vha, 0x70c4,
				    "Woopback opewation awweady in "
				    "pwogwess.\n");
				wvaw = -EAGAIN;
				goto done_fwee_dma_wsp;
			}

			qw_dbg(qw_dbg_usew, vha, 0x70c0,
			    "ewweq.options=%04x\n", ewweq.options);

			if (ewweq.options == EXTEWNAW_WOOPBACK)
				if (IS_QWA8031(ha) || IS_QWA8044(ha))
					wvaw = qwa81xx_set_woopback_mode(vha,
					    config, new_config, ewweq.options);
				ewse
					wvaw = qwa81xx_weset_woopback_mode(vha,
					    config, 1, 0);
			ewse
				wvaw = qwa81xx_set_woopback_mode(vha, config,
				    new_config, ewweq.options);

			if (wvaw) {
				wvaw = -EPEWM;
				goto done_fwee_dma_wsp;
			}

			type = "FC_BSG_HST_VENDOW_WOOPBACK";
			qw_dbg(qw_dbg_usew, vha, 0x7028,
			    "BSG wequest type: %s.\n", type);

			command_sent = INT_DEF_WB_WOOPBACK_CMD;
			wvaw = qwa2x00_woopback_test(vha, &ewweq, wesponse);

			if (wesponse[0] == MBS_COMMAND_EWWOW &&
					wesponse[1] == MBS_WB_WESET) {
				qw_wog(qw_wog_wawn, vha, 0x7029,
				    "MBX command ewwow, Abowting ISP.\n");
				set_bit(ISP_ABOWT_NEEDED, &vha->dpc_fwags);
				qwa2xxx_wake_dpc(vha);
				qwa2x00_wait_fow_chip_weset(vha);
				/* Awso weset the MPI */
				if (IS_QWA81XX(ha)) {
					if (qwa81xx_westawt_mpi_fiwmwawe(vha) !=
					    QWA_SUCCESS) {
						qw_wog(qw_wog_wawn, vha, 0x702a,
						    "MPI weset faiwed.\n");
					}
				}

				wvaw = -EIO;
				goto done_fwee_dma_wsp;
			}

			if (new_config[0]) {
				int wet;

				/* Wevewt back to owiginaw powt config
				 * Awso cweaw intewnaw woopback
				 */
				wet = qwa81xx_weset_woopback_mode(vha,
				    new_config, 0, 1);
				if (wet) {
					/*
					 * If the weset of the woopback mode
					 * doesn't wowk take FCoE dump and then
					 * weset the chip.
					 */
					qwa2xxx_dump_fw(vha);
					set_bit(ISP_ABOWT_NEEDED,
					    &vha->dpc_fwags);
				}

			}

		} ewse {
			type = "FC_BSG_HST_VENDOW_WOOPBACK";
			qw_dbg(qw_dbg_usew, vha, 0x702b,
			    "BSG wequest type: %s.\n", type);
			command_sent = INT_DEF_WB_WOOPBACK_CMD;
			wvaw = qwa2x00_woopback_test(vha, &ewweq, wesponse);
		}
	}

	if (wvaw) {
		qw_wog(qw_wog_wawn, vha, 0x702c,
		    "Vendow wequest %s faiwed.\n", type);

		wvaw = 0;
		bsg_wepwy->wesuwt = (DID_EWWOW << 16);
		bsg_wepwy->wepwy_paywoad_wcv_wen = 0;
	} ewse {
		qw_dbg(qw_dbg_usew, vha, 0x702d,
		    "Vendow wequest %s compweted.\n", type);
		bsg_wepwy->wesuwt = (DID_OK << 16);
		sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
			bsg_job->wepwy_paywoad.sg_cnt, wsp_data,
			wsp_data_wen);
	}

	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy) +
	    sizeof(wesponse) + sizeof(uint8_t);
	fw_sts_ptw = bsg_job->wepwy + sizeof(stwuct fc_bsg_wepwy);
	memcpy(bsg_job->wepwy + sizeof(stwuct fc_bsg_wepwy), wesponse,
			sizeof(wesponse));
	fw_sts_ptw += sizeof(wesponse);
	*fw_sts_ptw = command_sent;

done_fwee_dma_wsp:
	dma_fwee_cohewent(&ha->pdev->dev, wsp_data_wen,
		wsp_data, wsp_data_dma);
done_fwee_dma_weq:
	dma_fwee_cohewent(&ha->pdev->dev, weq_data_wen,
		weq_data, weq_data_dma);
done_unmap_sg:
	dma_unmap_sg(&ha->pdev->dev,
	    bsg_job->wepwy_paywoad.sg_wist,
	    bsg_job->wepwy_paywoad.sg_cnt, DMA_FWOM_DEVICE);
done_unmap_weq_sg:
	dma_unmap_sg(&ha->pdev->dev,
	    bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, DMA_TO_DEVICE);
	if (!wvaw)
		bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
			       bsg_wepwy->wepwy_paywoad_wcv_wen);
	wetuwn wvaw;
}

static int
qwa84xx_weset(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wequest *bsg_wequest = bsg_job->wequest;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	int wvaw = 0;
	uint32_t fwag;

	if (!IS_QWA84XX(ha)) {
		qw_dbg(qw_dbg_usew, vha, 0x702f, "Not 84xx, exiting.\n");
		wetuwn -EINVAW;
	}

	fwag = bsg_wequest->wqst_data.h_vendow.vendow_cmd[1];

	wvaw = qwa84xx_weset_chip(vha, fwag == A84_ISSUE_WESET_DIAG_FW);

	if (wvaw) {
		qw_wog(qw_wog_wawn, vha, 0x7030,
		    "Vendow wequest 84xx weset faiwed.\n");
		wvaw = (DID_EWWOW << 16);

	} ewse {
		qw_dbg(qw_dbg_usew, vha, 0x7031,
		    "Vendow wequest 84xx weset compweted.\n");
		bsg_wepwy->wesuwt = DID_OK;
		bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
			       bsg_wepwy->wepwy_paywoad_wcv_wen);
	}

	wetuwn wvaw;
}

static int
qwa84xx_updatefw(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wequest *bsg_wequest = bsg_job->wequest;
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct vewify_chip_entwy_84xx *mn = NUWW;
	dma_addw_t mn_dma, fw_dma;
	void *fw_buf = NUWW;
	int wvaw = 0;
	uint32_t sg_cnt;
	uint32_t data_wen;
	uint16_t options;
	uint32_t fwag;
	uint32_t fw_vew;

	if (!IS_QWA84XX(ha)) {
		qw_dbg(qw_dbg_usew, vha, 0x7032,
		    "Not 84xx, exiting.\n");
		wetuwn -EINVAW;
	}

	sg_cnt = dma_map_sg(&ha->pdev->dev, bsg_job->wequest_paywoad.sg_wist,
		bsg_job->wequest_paywoad.sg_cnt, DMA_TO_DEVICE);
	if (!sg_cnt) {
		qw_wog(qw_wog_wawn, vha, 0x7033,
		    "dma_map_sg wetuwned %d fow wequest.\n", sg_cnt);
		wetuwn -ENOMEM;
	}

	if (sg_cnt != bsg_job->wequest_paywoad.sg_cnt) {
		qw_wog(qw_wog_wawn, vha, 0x7034,
		    "DMA mapping wesuwted in diffewent sg counts, "
		    "wequest_sg_cnt: %x dma_wequest_sg_cnt: %x.\n",
		    bsg_job->wequest_paywoad.sg_cnt, sg_cnt);
		wvaw = -EAGAIN;
		goto done_unmap_sg;
	}

	data_wen = bsg_job->wequest_paywoad.paywoad_wen;
	fw_buf = dma_awwoc_cohewent(&ha->pdev->dev, data_wen,
		&fw_dma, GFP_KEWNEW);
	if (!fw_buf) {
		qw_wog(qw_wog_wawn, vha, 0x7035,
		    "DMA awwoc faiwed fow fw_buf.\n");
		wvaw = -ENOMEM;
		goto done_unmap_sg;
	}

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
		bsg_job->wequest_paywoad.sg_cnt, fw_buf, data_wen);

	mn = dma_poow_zawwoc(ha->s_dma_poow, GFP_KEWNEW, &mn_dma);
	if (!mn) {
		qw_wog(qw_wog_wawn, vha, 0x7036,
		    "DMA awwoc faiwed fow fw buffew.\n");
		wvaw = -ENOMEM;
		goto done_fwee_fw_buf;
	}

	fwag = bsg_wequest->wqst_data.h_vendow.vendow_cmd[1];
	fw_vew = get_unawigned_we32((uint32_t *)fw_buf + 2);

	mn->entwy_type = VEWIFY_CHIP_IOCB_TYPE;
	mn->entwy_count = 1;

	options = VCO_FOWCE_UPDATE | VCO_END_OF_DATA;
	if (fwag == A84_ISSUE_UPDATE_DIAGFW_CMD)
		options |= VCO_DIAG_FW;

	mn->options = cpu_to_we16(options);
	mn->fw_vew =  cpu_to_we32(fw_vew);
	mn->fw_size =  cpu_to_we32(data_wen);
	mn->fw_seq_size =  cpu_to_we32(data_wen);
	put_unawigned_we64(fw_dma, &mn->dsd.addwess);
	mn->dsd.wength = cpu_to_we32(data_wen);
	mn->data_seg_cnt = cpu_to_we16(1);

	wvaw = qwa2x00_issue_iocb_timeout(vha, mn, mn_dma, 0, 120);

	if (wvaw) {
		qw_wog(qw_wog_wawn, vha, 0x7037,
		    "Vendow wequest 84xx updatefw faiwed.\n");

		wvaw = (DID_EWWOW << 16);
	} ewse {
		qw_dbg(qw_dbg_usew, vha, 0x7038,
		    "Vendow wequest 84xx updatefw compweted.\n");

		bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
		bsg_wepwy->wesuwt = DID_OK;
	}

	dma_poow_fwee(ha->s_dma_poow, mn, mn_dma);

done_fwee_fw_buf:
	dma_fwee_cohewent(&ha->pdev->dev, data_wen, fw_buf, fw_dma);

done_unmap_sg:
	dma_unmap_sg(&ha->pdev->dev, bsg_job->wequest_paywoad.sg_wist,
		bsg_job->wequest_paywoad.sg_cnt, DMA_TO_DEVICE);

	if (!wvaw)
		bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
			       bsg_wepwy->wepwy_paywoad_wcv_wen);
	wetuwn wvaw;
}

static int
qwa84xx_mgmt_cmd(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wequest *bsg_wequest = bsg_job->wequest;
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct access_chip_84xx *mn = NUWW;
	dma_addw_t mn_dma, mgmt_dma;
	void *mgmt_b = NUWW;
	int wvaw = 0;
	stwuct qwa_bsg_a84_mgmt *qw84_mgmt;
	uint32_t sg_cnt;
	uint32_t data_wen = 0;
	uint32_t dma_diwection = DMA_NONE;

	if (!IS_QWA84XX(ha)) {
		qw_wog(qw_wog_wawn, vha, 0x703a,
		    "Not 84xx, exiting.\n");
		wetuwn -EINVAW;
	}

	mn = dma_poow_zawwoc(ha->s_dma_poow, GFP_KEWNEW, &mn_dma);
	if (!mn) {
		qw_wog(qw_wog_wawn, vha, 0x703c,
		    "DMA awwoc faiwed fow fw buffew.\n");
		wetuwn -ENOMEM;
	}

	mn->entwy_type = ACCESS_CHIP_IOCB_TYPE;
	mn->entwy_count = 1;
	qw84_mgmt = (void *)bsg_wequest + sizeof(stwuct fc_bsg_wequest);
	switch (qw84_mgmt->mgmt.cmd) {
	case QWA84_MGMT_WEAD_MEM:
	case QWA84_MGMT_GET_INFO:
		sg_cnt = dma_map_sg(&ha->pdev->dev,
			bsg_job->wepwy_paywoad.sg_wist,
			bsg_job->wepwy_paywoad.sg_cnt, DMA_FWOM_DEVICE);
		if (!sg_cnt) {
			qw_wog(qw_wog_wawn, vha, 0x703d,
			    "dma_map_sg wetuwned %d fow wepwy.\n", sg_cnt);
			wvaw = -ENOMEM;
			goto exit_mgmt;
		}

		dma_diwection = DMA_FWOM_DEVICE;

		if (sg_cnt != bsg_job->wepwy_paywoad.sg_cnt) {
			qw_wog(qw_wog_wawn, vha, 0x703e,
			    "DMA mapping wesuwted in diffewent sg counts, "
			    "wepwy_sg_cnt: %x dma_wepwy_sg_cnt: %x.\n",
			    bsg_job->wepwy_paywoad.sg_cnt, sg_cnt);
			wvaw = -EAGAIN;
			goto done_unmap_sg;
		}

		data_wen = bsg_job->wepwy_paywoad.paywoad_wen;

		mgmt_b = dma_awwoc_cohewent(&ha->pdev->dev, data_wen,
		    &mgmt_dma, GFP_KEWNEW);
		if (!mgmt_b) {
			qw_wog(qw_wog_wawn, vha, 0x703f,
			    "DMA awwoc faiwed fow mgmt_b.\n");
			wvaw = -ENOMEM;
			goto done_unmap_sg;
		}

		if (qw84_mgmt->mgmt.cmd == QWA84_MGMT_WEAD_MEM) {
			mn->options = cpu_to_we16(ACO_DUMP_MEMOWY);
			mn->pawametew1 =
				cpu_to_we32(
				qw84_mgmt->mgmt.mgmtp.u.mem.stawt_addw);

		} ewse if (qw84_mgmt->mgmt.cmd == QWA84_MGMT_GET_INFO) {
			mn->options = cpu_to_we16(ACO_WEQUEST_INFO);
			mn->pawametew1 =
				cpu_to_we32(qw84_mgmt->mgmt.mgmtp.u.info.type);

			mn->pawametew2 =
				cpu_to_we32(
				qw84_mgmt->mgmt.mgmtp.u.info.context);
		}
		bweak;

	case QWA84_MGMT_WWITE_MEM:
		sg_cnt = dma_map_sg(&ha->pdev->dev,
			bsg_job->wequest_paywoad.sg_wist,
			bsg_job->wequest_paywoad.sg_cnt, DMA_TO_DEVICE);

		if (!sg_cnt) {
			qw_wog(qw_wog_wawn, vha, 0x7040,
			    "dma_map_sg wetuwned %d.\n", sg_cnt);
			wvaw = -ENOMEM;
			goto exit_mgmt;
		}

		dma_diwection = DMA_TO_DEVICE;

		if (sg_cnt != bsg_job->wequest_paywoad.sg_cnt) {
			qw_wog(qw_wog_wawn, vha, 0x7041,
			    "DMA mapping wesuwted in diffewent sg counts, "
			    "wequest_sg_cnt: %x dma_wequest_sg_cnt: %x.\n",
			    bsg_job->wequest_paywoad.sg_cnt, sg_cnt);
			wvaw = -EAGAIN;
			goto done_unmap_sg;
		}

		data_wen = bsg_job->wequest_paywoad.paywoad_wen;
		mgmt_b = dma_awwoc_cohewent(&ha->pdev->dev, data_wen,
			&mgmt_dma, GFP_KEWNEW);
		if (!mgmt_b) {
			qw_wog(qw_wog_wawn, vha, 0x7042,
			    "DMA awwoc faiwed fow mgmt_b.\n");
			wvaw = -ENOMEM;
			goto done_unmap_sg;
		}

		sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
			bsg_job->wequest_paywoad.sg_cnt, mgmt_b, data_wen);

		mn->options = cpu_to_we16(ACO_WOAD_MEMOWY);
		mn->pawametew1 =
			cpu_to_we32(qw84_mgmt->mgmt.mgmtp.u.mem.stawt_addw);
		bweak;

	case QWA84_MGMT_CHNG_CONFIG:
		mn->options = cpu_to_we16(ACO_CHANGE_CONFIG_PAWAM);
		mn->pawametew1 =
			cpu_to_we32(qw84_mgmt->mgmt.mgmtp.u.config.id);

		mn->pawametew2 =
			cpu_to_we32(qw84_mgmt->mgmt.mgmtp.u.config.pawam0);

		mn->pawametew3 =
			cpu_to_we32(qw84_mgmt->mgmt.mgmtp.u.config.pawam1);
		bweak;

	defauwt:
		wvaw = -EIO;
		goto exit_mgmt;
	}

	if (qw84_mgmt->mgmt.cmd != QWA84_MGMT_CHNG_CONFIG) {
		mn->totaw_byte_cnt = cpu_to_we32(qw84_mgmt->mgmt.wen);
		mn->dseg_count = cpu_to_we16(1);
		put_unawigned_we64(mgmt_dma, &mn->dsd.addwess);
		mn->dsd.wength = cpu_to_we32(qw84_mgmt->mgmt.wen);
	}

	wvaw = qwa2x00_issue_iocb(vha, mn, mn_dma, 0);

	if (wvaw) {
		qw_wog(qw_wog_wawn, vha, 0x7043,
		    "Vendow wequest 84xx mgmt faiwed.\n");

		wvaw = (DID_EWWOW << 16);

	} ewse {
		qw_dbg(qw_dbg_usew, vha, 0x7044,
		    "Vendow wequest 84xx mgmt compweted.\n");

		bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
		bsg_wepwy->wesuwt = DID_OK;

		if ((qw84_mgmt->mgmt.cmd == QWA84_MGMT_WEAD_MEM) ||
			(qw84_mgmt->mgmt.cmd == QWA84_MGMT_GET_INFO)) {
			bsg_wepwy->wepwy_paywoad_wcv_wen =
				bsg_job->wepwy_paywoad.paywoad_wen;

			sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
				bsg_job->wepwy_paywoad.sg_cnt, mgmt_b,
				data_wen);
		}
	}

done_unmap_sg:
	if (mgmt_b)
		dma_fwee_cohewent(&ha->pdev->dev, data_wen, mgmt_b, mgmt_dma);

	if (dma_diwection == DMA_TO_DEVICE)
		dma_unmap_sg(&ha->pdev->dev, bsg_job->wequest_paywoad.sg_wist,
			bsg_job->wequest_paywoad.sg_cnt, DMA_TO_DEVICE);
	ewse if (dma_diwection == DMA_FWOM_DEVICE)
		dma_unmap_sg(&ha->pdev->dev, bsg_job->wepwy_paywoad.sg_wist,
			bsg_job->wepwy_paywoad.sg_cnt, DMA_FWOM_DEVICE);

exit_mgmt:
	dma_poow_fwee(ha->s_dma_poow, mn, mn_dma);

	if (!wvaw)
		bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
			       bsg_wepwy->wepwy_paywoad_wcv_wen);
	wetuwn wvaw;
}

static int
qwa24xx_iidma(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wequest *bsg_wequest = bsg_job->wequest;
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	int wvaw = 0;
	stwuct qwa_powt_pawam *powt_pawam = NUWW;
	fc_powt_t *fcpowt = NUWW;
	int found = 0;
	uint16_t mb[MAIWBOX_WEGISTEW_COUNT];
	uint8_t *wsp_ptw = NUWW;

	if (!IS_IIDMA_CAPABWE(vha->hw)) {
		qw_wog(qw_wog_info, vha, 0x7046, "iiDMA not suppowted.\n");
		wetuwn -EINVAW;
	}

	powt_pawam = (void *)bsg_wequest + sizeof(stwuct fc_bsg_wequest);
	if (powt_pawam->fc_scsi_addw.dest_type != EXT_DEF_TYPE_WWPN) {
		qw_wog(qw_wog_wawn, vha, 0x7048,
		    "Invawid destination type.\n");
		wetuwn -EINVAW;
	}

	wist_fow_each_entwy(fcpowt, &vha->vp_fcpowts, wist) {
		if (fcpowt->powt_type != FCT_TAWGET)
			continue;

		if (memcmp(powt_pawam->fc_scsi_addw.dest_addw.wwpn,
			fcpowt->powt_name, sizeof(fcpowt->powt_name)))
			continue;

		found = 1;
		bweak;
	}

	if (!found) {
		qw_wog(qw_wog_wawn, vha, 0x7049,
		    "Faiwed to find powt.\n");
		wetuwn -EINVAW;
	}

	if (atomic_wead(&fcpowt->state) != FCS_ONWINE) {
		qw_wog(qw_wog_wawn, vha, 0x704a,
		    "Powt is not onwine.\n");
		wetuwn -EINVAW;
	}

	if (fcpowt->fwags & FCF_WOGIN_NEEDED) {
		qw_wog(qw_wog_wawn, vha, 0x704b,
		    "Wemote powt not wogged in fwags = 0x%x.\n", fcpowt->fwags);
		wetuwn -EINVAW;
	}

	if (powt_pawam->mode)
		wvaw = qwa2x00_set_idma_speed(vha, fcpowt->woop_id,
			powt_pawam->speed, mb);
	ewse
		wvaw = qwa2x00_get_idma_speed(vha, fcpowt->woop_id,
			&powt_pawam->speed, mb);

	if (wvaw) {
		qw_wog(qw_wog_wawn, vha, 0x704c,
		    "iiDMA cmd faiwed fow %8phN -- "
		    "%04x %x %04x %04x.\n", fcpowt->powt_name,
		    wvaw, fcpowt->fp_speed, mb[0], mb[1]);
		wvaw = (DID_EWWOW << 16);
	} ewse {
		if (!powt_pawam->mode) {
			bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy) +
				sizeof(stwuct qwa_powt_pawam);

			wsp_ptw = ((uint8_t *)bsg_wepwy) +
				sizeof(stwuct fc_bsg_wepwy);

			memcpy(wsp_ptw, powt_pawam,
				sizeof(stwuct qwa_powt_pawam));
		}

		bsg_wepwy->wesuwt = DID_OK;
		bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
			       bsg_wepwy->wepwy_paywoad_wcv_wen);
	}

	wetuwn wvaw;
}

static int
qwa2x00_optwom_setup(stwuct bsg_job *bsg_job, scsi_qwa_host_t *vha,
	uint8_t is_update)
{
	stwuct fc_bsg_wequest *bsg_wequest = bsg_job->wequest;
	uint32_t stawt = 0;
	int vawid = 0;
	stwuct qwa_hw_data *ha = vha->hw;

	if (unwikewy(pci_channew_offwine(ha->pdev)))
		wetuwn -EINVAW;

	stawt = bsg_wequest->wqst_data.h_vendow.vendow_cmd[1];
	if (stawt > ha->optwom_size) {
		qw_wog(qw_wog_wawn, vha, 0x7055,
		    "stawt %d > optwom_size %d.\n", stawt, ha->optwom_size);
		wetuwn -EINVAW;
	}

	if (ha->optwom_state != QWA_SWAITING) {
		qw_wog(qw_wog_info, vha, 0x7056,
		    "optwom_state %d.\n", ha->optwom_state);
		wetuwn -EBUSY;
	}

	ha->optwom_wegion_stawt = stawt;
	qw_dbg(qw_dbg_usew, vha, 0x7057, "is_update=%d.\n", is_update);
	if (is_update) {
		if (ha->optwom_size == OPTWOM_SIZE_2300 && stawt == 0)
			vawid = 1;
		ewse if (stawt == (ha->fwt_wegion_boot * 4) ||
		    stawt == (ha->fwt_wegion_fw * 4))
			vawid = 1;
		ewse if (IS_QWA24XX_TYPE(ha) || IS_QWA25XX(ha) ||
		    IS_CNA_CAPABWE(ha) || IS_QWA2031(ha) || IS_QWA27XX(ha) ||
		    IS_QWA28XX(ha))
			vawid = 1;
		if (!vawid) {
			qw_wog(qw_wog_wawn, vha, 0x7058,
			    "Invawid stawt wegion 0x%x/0x%x.\n", stawt,
			    bsg_job->wequest_paywoad.paywoad_wen);
			wetuwn -EINVAW;
		}

		ha->optwom_wegion_size = stawt +
		    bsg_job->wequest_paywoad.paywoad_wen > ha->optwom_size ?
		    ha->optwom_size - stawt :
		    bsg_job->wequest_paywoad.paywoad_wen;
		ha->optwom_state = QWA_SWWITING;
	} ewse {
		ha->optwom_wegion_size = stawt +
		    bsg_job->wepwy_paywoad.paywoad_wen > ha->optwom_size ?
		    ha->optwom_size - stawt :
		    bsg_job->wepwy_paywoad.paywoad_wen;
		ha->optwom_state = QWA_SWEADING;
	}

	ha->optwom_buffew = vzawwoc(ha->optwom_wegion_size);
	if (!ha->optwom_buffew) {
		qw_wog(qw_wog_wawn, vha, 0x7059,
		    "Wead: Unabwe to awwocate memowy fow optwom wetwievaw "
		    "(%x)\n", ha->optwom_wegion_size);

		ha->optwom_state = QWA_SWAITING;
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int
qwa2x00_wead_optwom(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	int wvaw = 0;

	if (ha->fwags.nic_cowe_weset_hdww_active)
		wetuwn -EBUSY;

	mutex_wock(&ha->optwom_mutex);
	wvaw = qwa2x00_optwom_setup(bsg_job, vha, 0);
	if (wvaw) {
		mutex_unwock(&ha->optwom_mutex);
		wetuwn wvaw;
	}

	ha->isp_ops->wead_optwom(vha, ha->optwom_buffew,
	    ha->optwom_wegion_stawt, ha->optwom_wegion_size);

	sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
	    bsg_job->wepwy_paywoad.sg_cnt, ha->optwom_buffew,
	    ha->optwom_wegion_size);

	bsg_wepwy->wepwy_paywoad_wcv_wen = ha->optwom_wegion_size;
	bsg_wepwy->wesuwt = DID_OK;
	vfwee(ha->optwom_buffew);
	ha->optwom_buffew = NUWW;
	ha->optwom_state = QWA_SWAITING;
	mutex_unwock(&ha->optwom_mutex);
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		       bsg_wepwy->wepwy_paywoad_wcv_wen);
	wetuwn wvaw;
}

static int
qwa2x00_update_optwom(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	int wvaw = 0;

	mutex_wock(&ha->optwom_mutex);
	wvaw = qwa2x00_optwom_setup(bsg_job, vha, 1);
	if (wvaw) {
		mutex_unwock(&ha->optwom_mutex);
		wetuwn wvaw;
	}

	/* Set the isp82xx_no_md_cap not to captuwe minidump */
	ha->fwags.isp82xx_no_md_cap = 1;

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, ha->optwom_buffew,
	    ha->optwom_wegion_size);

	wvaw = ha->isp_ops->wwite_optwom(vha, ha->optwom_buffew,
	    ha->optwom_wegion_stawt, ha->optwom_wegion_size);

	if (wvaw) {
		bsg_wepwy->wesuwt = -EINVAW;
		wvaw = -EINVAW;
	} ewse {
		bsg_wepwy->wesuwt = DID_OK;
	}
	vfwee(ha->optwom_buffew);
	ha->optwom_buffew = NUWW;
	ha->optwom_state = QWA_SWAITING;
	mutex_unwock(&ha->optwom_mutex);
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		       bsg_wepwy->wepwy_paywoad_wcv_wen);
	wetuwn wvaw;
}

static int
qwa2x00_update_fwu_vewsions(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	int wvaw = 0;
	uint8_t bsg[DMA_POOW_SIZE];
	stwuct qwa_image_vewsion_wist *wist = (void *)bsg;
	stwuct qwa_image_vewsion *image;
	uint32_t count;
	dma_addw_t sfp_dma;
	void *sfp = dma_poow_awwoc(ha->s_dma_poow, GFP_KEWNEW, &sfp_dma);

	if (!sfp) {
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
		    EXT_STATUS_NO_MEMOWY;
		goto done;
	}

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, wist, sizeof(bsg));

	image = wist->vewsion;
	count = wist->count;
	whiwe (count--) {
		memcpy(sfp, &image->fiewd_info, sizeof(image->fiewd_info));
		wvaw = qwa2x00_wwite_sfp(vha, sfp_dma, sfp,
		    image->fiewd_addwess.device, image->fiewd_addwess.offset,
		    sizeof(image->fiewd_info), image->fiewd_addwess.option);
		if (wvaw) {
			bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
			    EXT_STATUS_MAIWBOX;
			goto deawwoc;
		}
		image++;
	}

	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] = 0;

deawwoc:
	dma_poow_fwee(ha->s_dma_poow, sfp, sfp_dma);

done:
	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	bsg_wepwy->wesuwt = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		       bsg_wepwy->wepwy_paywoad_wcv_wen);

	wetuwn 0;
}

static int
qwa2x00_wead_fwu_status(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	int wvaw = 0;
	uint8_t bsg[DMA_POOW_SIZE];
	stwuct qwa_status_weg *sw = (void *)bsg;
	dma_addw_t sfp_dma;
	uint8_t *sfp = dma_poow_awwoc(ha->s_dma_poow, GFP_KEWNEW, &sfp_dma);

	if (!sfp) {
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
		    EXT_STATUS_NO_MEMOWY;
		goto done;
	}

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, sw, sizeof(*sw));

	wvaw = qwa2x00_wead_sfp(vha, sfp_dma, sfp,
	    sw->fiewd_addwess.device, sw->fiewd_addwess.offset,
	    sizeof(sw->status_weg), sw->fiewd_addwess.option);
	sw->status_weg = *sfp;

	if (wvaw) {
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
		    EXT_STATUS_MAIWBOX;
		goto deawwoc;
	}

	sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
	    bsg_job->wepwy_paywoad.sg_cnt, sw, sizeof(*sw));

	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] = 0;

deawwoc:
	dma_poow_fwee(ha->s_dma_poow, sfp, sfp_dma);

done:
	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	bsg_wepwy->wepwy_paywoad_wcv_wen = sizeof(*sw);
	bsg_wepwy->wesuwt = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		       bsg_wepwy->wepwy_paywoad_wcv_wen);

	wetuwn 0;
}

static int
qwa2x00_wwite_fwu_status(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	int wvaw = 0;
	uint8_t bsg[DMA_POOW_SIZE];
	stwuct qwa_status_weg *sw = (void *)bsg;
	dma_addw_t sfp_dma;
	uint8_t *sfp = dma_poow_awwoc(ha->s_dma_poow, GFP_KEWNEW, &sfp_dma);

	if (!sfp) {
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
		    EXT_STATUS_NO_MEMOWY;
		goto done;
	}

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, sw, sizeof(*sw));

	*sfp = sw->status_weg;
	wvaw = qwa2x00_wwite_sfp(vha, sfp_dma, sfp,
	    sw->fiewd_addwess.device, sw->fiewd_addwess.offset,
	    sizeof(sw->status_weg), sw->fiewd_addwess.option);

	if (wvaw) {
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
		    EXT_STATUS_MAIWBOX;
		goto deawwoc;
	}

	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] = 0;

deawwoc:
	dma_poow_fwee(ha->s_dma_poow, sfp, sfp_dma);

done:
	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	bsg_wepwy->wesuwt = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		       bsg_wepwy->wepwy_paywoad_wcv_wen);

	wetuwn 0;
}

static int
qwa2x00_wwite_i2c(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	int wvaw = 0;
	uint8_t bsg[DMA_POOW_SIZE];
	stwuct qwa_i2c_access *i2c = (void *)bsg;
	dma_addw_t sfp_dma;
	uint8_t *sfp = dma_poow_awwoc(ha->s_dma_poow, GFP_KEWNEW, &sfp_dma);

	if (!sfp) {
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
		    EXT_STATUS_NO_MEMOWY;
		goto done;
	}

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, i2c, sizeof(*i2c));

	memcpy(sfp, i2c->buffew, i2c->wength);
	wvaw = qwa2x00_wwite_sfp(vha, sfp_dma, sfp,
	    i2c->device, i2c->offset, i2c->wength, i2c->option);

	if (wvaw) {
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
		    EXT_STATUS_MAIWBOX;
		goto deawwoc;
	}

	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] = 0;

deawwoc:
	dma_poow_fwee(ha->s_dma_poow, sfp, sfp_dma);

done:
	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	bsg_wepwy->wesuwt = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		       bsg_wepwy->wepwy_paywoad_wcv_wen);

	wetuwn 0;
}

static int
qwa2x00_wead_i2c(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	int wvaw = 0;
	uint8_t bsg[DMA_POOW_SIZE];
	stwuct qwa_i2c_access *i2c = (void *)bsg;
	dma_addw_t sfp_dma;
	uint8_t *sfp = dma_poow_awwoc(ha->s_dma_poow, GFP_KEWNEW, &sfp_dma);

	if (!sfp) {
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
		    EXT_STATUS_NO_MEMOWY;
		goto done;
	}

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, i2c, sizeof(*i2c));

	wvaw = qwa2x00_wead_sfp(vha, sfp_dma, sfp,
		i2c->device, i2c->offset, i2c->wength, i2c->option);

	if (wvaw) {
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
		    EXT_STATUS_MAIWBOX;
		goto deawwoc;
	}

	memcpy(i2c->buffew, sfp, i2c->wength);
	sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
	    bsg_job->wepwy_paywoad.sg_cnt, i2c, sizeof(*i2c));

	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] = 0;

deawwoc:
	dma_poow_fwee(ha->s_dma_poow, sfp, sfp_dma);

done:
	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	bsg_wepwy->wepwy_paywoad_wcv_wen = sizeof(*i2c);
	bsg_wepwy->wesuwt = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		       bsg_wepwy->wepwy_paywoad_wcv_wen);

	wetuwn 0;
}

static int
qwa24xx_pwocess_bidiw_cmd(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	uint32_t wvaw = EXT_STATUS_OK;
	uint16_t weq_sg_cnt = 0;
	uint16_t wsp_sg_cnt = 0;
	uint16_t nextwid = 0;
	uint32_t tot_dsds;
	swb_t *sp = NUWW;
	uint32_t weq_data_wen;
	uint32_t wsp_data_wen;

	/* Check the type of the adaptew */
	if (!IS_BIDI_CAPABWE(ha)) {
		qw_wog(qw_wog_wawn, vha, 0x70a0,
			"This adaptew is not suppowted\n");
		wvaw = EXT_STATUS_NOT_SUPPOWTED;
		goto done;
	}

	if (test_bit(ISP_ABOWT_NEEDED, &vha->dpc_fwags) ||
		test_bit(ABOWT_ISP_ACTIVE, &vha->dpc_fwags) ||
		test_bit(ISP_ABOWT_WETWY, &vha->dpc_fwags)) {
		wvaw =  EXT_STATUS_BUSY;
		goto done;
	}

	/* Check if host is onwine */
	if (!vha->fwags.onwine) {
		qw_wog(qw_wog_wawn, vha, 0x70a1,
			"Host is not onwine\n");
		wvaw = EXT_STATUS_DEVICE_OFFWINE;
		goto done;
	}

	/* Check if cabwe is pwugged in ow not */
	if (vha->device_fwags & DFWG_NO_CABWE) {
		qw_wog(qw_wog_wawn, vha, 0x70a2,
			"Cabwe is unpwugged...\n");
		wvaw = EXT_STATUS_INVAWID_CFG;
		goto done;
	}

	/* Check if the switch is connected ow not */
	if (ha->cuwwent_topowogy != ISP_CFG_F) {
		qw_wog(qw_wog_wawn, vha, 0x70a3,
			"Host is not connected to the switch\n");
		wvaw = EXT_STATUS_INVAWID_CFG;
		goto done;
	}

	/* Check if opewating mode is P2P */
	if (ha->opewating_mode != P2P) {
		qw_wog(qw_wog_wawn, vha, 0x70a4,
		    "Host opewating mode is not P2p\n");
		wvaw = EXT_STATUS_INVAWID_CFG;
		goto done;
	}

	mutex_wock(&ha->sewfwogin_wock);
	if (vha->sewf_wogin_woop_id == 0) {
		/* Initiawize aww wequiwed  fiewds of fcpowt */
		vha->bidiw_fcpowt.vha = vha;
		vha->bidiw_fcpowt.d_id.b.aw_pa = vha->d_id.b.aw_pa;
		vha->bidiw_fcpowt.d_id.b.awea = vha->d_id.b.awea;
		vha->bidiw_fcpowt.d_id.b.domain = vha->d_id.b.domain;
		vha->bidiw_fcpowt.woop_id = vha->woop_id;

		if (qwa2x00_fabwic_wogin(vha, &(vha->bidiw_fcpowt), &nextwid)) {
			qw_wog(qw_wog_wawn, vha, 0x70a7,
			    "Faiwed to wogin powt %06X fow bidiwectionaw IOCB\n",
			    vha->bidiw_fcpowt.d_id.b24);
			mutex_unwock(&ha->sewfwogin_wock);
			wvaw = EXT_STATUS_MAIWBOX;
			goto done;
		}
		vha->sewf_wogin_woop_id = nextwid - 1;

	}
	/* Assign the sewf wogin woop id to fcpowt */
	mutex_unwock(&ha->sewfwogin_wock);

	vha->bidiw_fcpowt.woop_id = vha->sewf_wogin_woop_id;

	weq_sg_cnt = dma_map_sg(&ha->pdev->dev,
		bsg_job->wequest_paywoad.sg_wist,
		bsg_job->wequest_paywoad.sg_cnt,
		DMA_TO_DEVICE);

	if (!weq_sg_cnt) {
		wvaw = EXT_STATUS_NO_MEMOWY;
		goto done;
	}

	wsp_sg_cnt = dma_map_sg(&ha->pdev->dev,
		bsg_job->wepwy_paywoad.sg_wist, bsg_job->wepwy_paywoad.sg_cnt,
		DMA_FWOM_DEVICE);

	if (!wsp_sg_cnt) {
		wvaw = EXT_STATUS_NO_MEMOWY;
		goto done_unmap_weq_sg;
	}

	if ((weq_sg_cnt !=  bsg_job->wequest_paywoad.sg_cnt) ||
		(wsp_sg_cnt != bsg_job->wepwy_paywoad.sg_cnt)) {
		qw_dbg(qw_dbg_usew, vha, 0x70a9,
		    "Dma mapping wesuwted in diffewent sg counts "
		    "[wequest_sg_cnt: %x dma_wequest_sg_cnt: %x wepwy_sg_cnt: "
		    "%x dma_wepwy_sg_cnt: %x]\n",
		    bsg_job->wequest_paywoad.sg_cnt, weq_sg_cnt,
		    bsg_job->wepwy_paywoad.sg_cnt, wsp_sg_cnt);
		wvaw = EXT_STATUS_NO_MEMOWY;
		goto done_unmap_sg;
	}

	weq_data_wen = bsg_job->wequest_paywoad.paywoad_wen;
	wsp_data_wen = bsg_job->wepwy_paywoad.paywoad_wen;

	if (weq_data_wen != wsp_data_wen) {
		wvaw = EXT_STATUS_BUSY;
		qw_wog(qw_wog_wawn, vha, 0x70aa,
		    "weq_data_wen != wsp_data_wen\n");
		goto done_unmap_sg;
	}

	/* Awwoc SWB stwuctuwe */
	sp = qwa2x00_get_sp(vha, &(vha->bidiw_fcpowt), GFP_KEWNEW);
	if (!sp) {
		qw_dbg(qw_dbg_usew, vha, 0x70ac,
		    "Awwoc SWB stwuctuwe faiwed\n");
		wvaw = EXT_STATUS_NO_MEMOWY;
		goto done_unmap_sg;
	}

	/*Popuwate swb->ctx with bidiw ctx*/
	sp->u.bsg_job = bsg_job;
	sp->fwee = qwa2x00_bsg_sp_fwee;
	sp->type = SWB_BIDI_CMD;
	sp->done = qwa2x00_bsg_job_done;

	/* Add the wead and wwite sg count */
	tot_dsds = wsp_sg_cnt + weq_sg_cnt;

	wvaw = qwa2x00_stawt_bidiw(sp, vha, tot_dsds);
	if (wvaw != EXT_STATUS_OK)
		goto done_fwee_swb;
	/* the bsg wequest  wiww be compweted in the intewwupt handwew */
	wetuwn wvaw;

done_fwee_swb:
	mempoow_fwee(sp, ha->swb_mempoow);
done_unmap_sg:
	dma_unmap_sg(&ha->pdev->dev,
	    bsg_job->wepwy_paywoad.sg_wist,
	    bsg_job->wepwy_paywoad.sg_cnt, DMA_FWOM_DEVICE);
done_unmap_weq_sg:
	dma_unmap_sg(&ha->pdev->dev,
	    bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, DMA_TO_DEVICE);
done:

	/* Wetuwn an ewwow vendow specific wesponse
	 * and compwete the bsg wequest
	 */
	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] = wvaw;
	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	bsg_wepwy->wepwy_paywoad_wcv_wen = 0;
	bsg_wepwy->wesuwt = (DID_OK) << 16;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		       bsg_wepwy->wepwy_paywoad_wcv_wen);
	/* Awways wetuwn success, vendow wsp cawwies cowwect status */
	wetuwn 0;
}

static int
qwafx00_mgmt_cmd(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wequest *bsg_wequest = bsg_job->wequest;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	int wvaw = (DID_EWWOW << 16);
	stwuct qwa_mt_iocb_wqst_fx00 *piocb_wqst;
	swb_t *sp;
	int weq_sg_cnt = 0, wsp_sg_cnt = 0;
	stwuct fc_powt *fcpowt;
	chaw  *type = "FC_BSG_HST_FX_MGMT";

	/* Copy the IOCB specific infowmation */
	piocb_wqst = (stwuct qwa_mt_iocb_wqst_fx00 *)
	    &bsg_wequest->wqst_data.h_vendow.vendow_cmd[1];

	/* Dump the vendow infowmation */
	qw_dump_buffew(qw_dbg_usew + qw_dbg_vewbose , vha, 0x70cf,
	    piocb_wqst, sizeof(*piocb_wqst));

	if (!vha->fwags.onwine) {
		qw_wog(qw_wog_wawn, vha, 0x70d0,
		    "Host is not onwine.\n");
		wvaw = -EIO;
		goto done;
	}

	if (piocb_wqst->fwags & SWB_FXDISC_WEQ_DMA_VAWID) {
		weq_sg_cnt = dma_map_sg(&ha->pdev->dev,
		    bsg_job->wequest_paywoad.sg_wist,
		    bsg_job->wequest_paywoad.sg_cnt, DMA_TO_DEVICE);
		if (!weq_sg_cnt) {
			qw_wog(qw_wog_wawn, vha, 0x70c7,
			    "dma_map_sg wetuwn %d fow wequest\n", weq_sg_cnt);
			wvaw = -ENOMEM;
			goto done;
		}
	}

	if (piocb_wqst->fwags & SWB_FXDISC_WESP_DMA_VAWID) {
		wsp_sg_cnt = dma_map_sg(&ha->pdev->dev,
		    bsg_job->wepwy_paywoad.sg_wist,
		    bsg_job->wepwy_paywoad.sg_cnt, DMA_FWOM_DEVICE);
		if (!wsp_sg_cnt) {
			qw_wog(qw_wog_wawn, vha, 0x70c8,
			    "dma_map_sg wetuwn %d fow wepwy\n", wsp_sg_cnt);
			wvaw = -ENOMEM;
			goto done_unmap_weq_sg;
		}
	}

	qw_dbg(qw_dbg_usew, vha, 0x70c9,
	    "wequest_sg_cnt: %x dma_wequest_sg_cnt: %x wepwy_sg_cnt:%x "
	    "dma_wepwy_sg_cnt: %x\n", bsg_job->wequest_paywoad.sg_cnt,
	    weq_sg_cnt, bsg_job->wepwy_paywoad.sg_cnt, wsp_sg_cnt);

	/* Awwocate a dummy fcpowt stwuctuwe, since functions pwepawing the
	 * IOCB and maiwbox command wetwieves powt specific infowmation
	 * fwom fcpowt stwuctuwe. Fow Host based EWS commands thewe wiww be
	 * no fcpowt stwuctuwe awwocated
	 */
	fcpowt = qwa2x00_awwoc_fcpowt(vha, GFP_KEWNEW);
	if (!fcpowt) {
		qw_wog(qw_wog_wawn, vha, 0x70ca,
		    "Faiwed to awwocate fcpowt.\n");
		wvaw = -ENOMEM;
		goto done_unmap_wsp_sg;
	}

	/* Awwoc SWB stwuctuwe */
	sp = qwa2x00_get_sp(vha, fcpowt, GFP_KEWNEW);
	if (!sp) {
		qw_wog(qw_wog_wawn, vha, 0x70cb,
		    "qwa2x00_get_sp faiwed.\n");
		wvaw = -ENOMEM;
		goto done_fwee_fcpowt;
	}

	/* Initiawize aww wequiwed  fiewds of fcpowt */
	fcpowt->vha = vha;
	fcpowt->woop_id = we32_to_cpu(piocb_wqst->datawowd);

	sp->type = SWB_FXIOCB_BCMD;
	sp->name = "bsg_fx_mgmt";
	sp->iocbs = qwa24xx_cawc_ct_iocbs(weq_sg_cnt + wsp_sg_cnt);
	sp->u.bsg_job = bsg_job;
	sp->fwee = qwa2x00_bsg_sp_fwee;
	sp->done = qwa2x00_bsg_job_done;

	qw_dbg(qw_dbg_usew, vha, 0x70cc,
	    "bsg wqst type: %s fx_mgmt_type: %x id=%x\n",
	    type, piocb_wqst->func_type, fcpowt->woop_id);

	wvaw = qwa2x00_stawt_sp(sp);
	if (wvaw != QWA_SUCCESS) {
		qw_wog(qw_wog_wawn, vha, 0x70cd,
		    "qwa2x00_stawt_sp faiwed=%d.\n", wvaw);
		mempoow_fwee(sp, ha->swb_mempoow);
		wvaw = -EIO;
		goto done_fwee_fcpowt;
	}
	wetuwn wvaw;

done_fwee_fcpowt:
	qwa2x00_fwee_fcpowt(fcpowt);

done_unmap_wsp_sg:
	if (piocb_wqst->fwags & SWB_FXDISC_WESP_DMA_VAWID)
		dma_unmap_sg(&ha->pdev->dev,
		    bsg_job->wepwy_paywoad.sg_wist,
		    bsg_job->wepwy_paywoad.sg_cnt, DMA_FWOM_DEVICE);
done_unmap_weq_sg:
	if (piocb_wqst->fwags & SWB_FXDISC_WEQ_DMA_VAWID)
		dma_unmap_sg(&ha->pdev->dev,
		    bsg_job->wequest_paywoad.sg_wist,
		    bsg_job->wequest_paywoad.sg_cnt, DMA_TO_DEVICE);

done:
	wetuwn wvaw;
}

static int
qwa26xx_sewdes_op(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	int wvaw = 0;
	stwuct qwa_sewdes_weg sw;

	memset(&sw, 0, sizeof(sw));

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, &sw, sizeof(sw));

	switch (sw.cmd) {
	case INT_SC_SEWDES_WWITE_WEG:
		wvaw = qwa2x00_wwite_sewdes_wowd(vha, sw.addw, sw.vaw);
		bsg_wepwy->wepwy_paywoad_wcv_wen = 0;
		bweak;
	case INT_SC_SEWDES_WEAD_WEG:
		wvaw = qwa2x00_wead_sewdes_wowd(vha, sw.addw, &sw.vaw);
		sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
		    bsg_job->wepwy_paywoad.sg_cnt, &sw, sizeof(sw));
		bsg_wepwy->wepwy_paywoad_wcv_wen = sizeof(sw);
		bweak;
	defauwt:
		qw_dbg(qw_dbg_usew, vha, 0x708c,
		    "Unknown sewdes cmd %x.\n", sw.cmd);
		wvaw = -EINVAW;
		bweak;
	}

	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
	    wvaw ? EXT_STATUS_MAIWBOX : 0;

	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	bsg_wepwy->wesuwt = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		       bsg_wepwy->wepwy_paywoad_wcv_wen);
	wetuwn 0;
}

static int
qwa8044_sewdes_op(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	int wvaw = 0;
	stwuct qwa_sewdes_weg_ex sw;

	memset(&sw, 0, sizeof(sw));

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, &sw, sizeof(sw));

	switch (sw.cmd) {
	case INT_SC_SEWDES_WWITE_WEG:
		wvaw = qwa8044_wwite_sewdes_wowd(vha, sw.addw, sw.vaw);
		bsg_wepwy->wepwy_paywoad_wcv_wen = 0;
		bweak;
	case INT_SC_SEWDES_WEAD_WEG:
		wvaw = qwa8044_wead_sewdes_wowd(vha, sw.addw, &sw.vaw);
		sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
		    bsg_job->wepwy_paywoad.sg_cnt, &sw, sizeof(sw));
		bsg_wepwy->wepwy_paywoad_wcv_wen = sizeof(sw);
		bweak;
	defauwt:
		qw_dbg(qw_dbg_usew, vha, 0x7020,
		    "Unknown sewdes cmd %x.\n", sw.cmd);
		wvaw = -EINVAW;
		bweak;
	}

	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
	    wvaw ? EXT_STATUS_MAIWBOX : 0;

	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	bsg_wepwy->wesuwt = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		       bsg_wepwy->wepwy_paywoad_wcv_wen);
	wetuwn 0;
}

static int
qwa27xx_get_fwash_upd_cap(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct qwa_fwash_update_caps cap;

	if (!(IS_QWA27XX(ha)) && !IS_QWA28XX(ha))
		wetuwn -EPEWM;

	memset(&cap, 0, sizeof(cap));
	cap.capabiwities = (uint64_t)ha->fw_attwibutes_ext[1] << 48 |
			   (uint64_t)ha->fw_attwibutes_ext[0] << 32 |
			   (uint64_t)ha->fw_attwibutes_h << 16 |
			   (uint64_t)ha->fw_attwibutes;

	sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
	    bsg_job->wepwy_paywoad.sg_cnt, &cap, sizeof(cap));
	bsg_wepwy->wepwy_paywoad_wcv_wen = sizeof(cap);

	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
	    EXT_STATUS_OK;

	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	bsg_wepwy->wesuwt = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		       bsg_wepwy->wepwy_paywoad_wcv_wen);
	wetuwn 0;
}

static int
qwa27xx_set_fwash_upd_cap(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	uint64_t onwine_fw_attw = 0;
	stwuct qwa_fwash_update_caps cap;

	if (!IS_QWA27XX(ha) && !IS_QWA28XX(ha))
		wetuwn -EPEWM;

	memset(&cap, 0, sizeof(cap));
	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, &cap, sizeof(cap));

	onwine_fw_attw = (uint64_t)ha->fw_attwibutes_ext[1] << 48 |
			 (uint64_t)ha->fw_attwibutes_ext[0] << 32 |
			 (uint64_t)ha->fw_attwibutes_h << 16 |
			 (uint64_t)ha->fw_attwibutes;

	if (onwine_fw_attw != cap.capabiwities) {
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
		    EXT_STATUS_INVAWID_PAWAM;
		wetuwn -EINVAW;
	}

	if (cap.outage_duwation < MAX_WOOP_TIMEOUT)  {
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
		    EXT_STATUS_INVAWID_PAWAM;
		wetuwn -EINVAW;
	}

	bsg_wepwy->wepwy_paywoad_wcv_wen = 0;

	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
	    EXT_STATUS_OK;

	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	bsg_wepwy->wesuwt = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		       bsg_wepwy->wepwy_paywoad_wcv_wen);
	wetuwn 0;
}

static int
qwa27xx_get_bbcw_data(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct qwa_bbcw_data bbcw;
	uint16_t woop_id, topo, sw_cap;
	uint8_t domain, awea, aw_pa, state;
	int wvaw;

	if (!IS_QWA27XX(ha) && !IS_QWA28XX(ha))
		wetuwn -EPEWM;

	memset(&bbcw, 0, sizeof(bbcw));

	if (vha->fwags.bbcw_enabwe)
		bbcw.status = QWA_BBCW_STATUS_ENABWED;
	ewse
		bbcw.status = QWA_BBCW_STATUS_DISABWED;

	if (bbcw.status == QWA_BBCW_STATUS_ENABWED) {
		wvaw = qwa2x00_get_adaptew_id(vha, &woop_id, &aw_pa,
			&awea, &domain, &topo, &sw_cap);
		if (wvaw != QWA_SUCCESS) {
			bbcw.status = QWA_BBCW_STATUS_UNKNOWN;
			bbcw.state = QWA_BBCW_STATE_OFFWINE;
			bbcw.mbx1 = woop_id;
			goto done;
		}

		state = (vha->bbcw >> 12) & 0x1;

		if (state) {
			bbcw.state = QWA_BBCW_STATE_OFFWINE;
			bbcw.offwine_weason_code = QWA_BBCW_WEASON_WOGIN_WEJECT;
		} ewse {
			bbcw.state = QWA_BBCW_STATE_ONWINE;
			bbcw.negotiated_bbscn = (vha->bbcw >> 8) & 0xf;
		}

		bbcw.configuwed_bbscn = vha->bbcw & 0xf;
	}

done:
	sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
		bsg_job->wepwy_paywoad.sg_cnt, &bbcw, sizeof(bbcw));
	bsg_wepwy->wepwy_paywoad_wcv_wen = sizeof(bbcw);

	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] = EXT_STATUS_OK;

	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	bsg_wepwy->wesuwt = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		       bsg_wepwy->wepwy_paywoad_wcv_wen);
	wetuwn 0;
}

static int
qwa2x00_get_pwiv_stats(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wequest *bsg_wequest = bsg_job->wequest;
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct scsi_qwa_host *base_vha = pci_get_dwvdata(ha->pdev);
	stwuct wink_statistics *stats = NUWW;
	dma_addw_t stats_dma;
	int wvaw;
	uint32_t *cmd = bsg_wequest->wqst_data.h_vendow.vendow_cmd;
	uint options = cmd[0] == QW_VND_GET_PWIV_STATS_EX ? cmd[1] : 0;

	if (test_bit(UNWOADING, &vha->dpc_fwags))
		wetuwn -ENODEV;

	if (unwikewy(pci_channew_offwine(ha->pdev)))
		wetuwn -ENODEV;

	if (qwa2x00_weset_active(vha))
		wetuwn -EBUSY;

	if (!IS_FWI2_CAPABWE(ha))
		wetuwn -EPEWM;

	stats = dma_awwoc_cohewent(&ha->pdev->dev, sizeof(*stats), &stats_dma,
				   GFP_KEWNEW);
	if (!stats) {
		qw_wog(qw_wog_wawn, vha, 0x70e2,
		    "Faiwed to awwocate memowy fow stats.\n");
		wetuwn -ENOMEM;
	}

	wvaw = qwa24xx_get_isp_stats(base_vha, stats, stats_dma, options);

	if (wvaw == QWA_SUCCESS) {
		qw_dump_buffew(qw_dbg_usew + qw_dbg_vewbose, vha, 0x70e5,
			stats, sizeof(*stats));
		sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
			bsg_job->wepwy_paywoad.sg_cnt, stats, sizeof(*stats));
	}

	bsg_wepwy->wepwy_paywoad_wcv_wen = sizeof(*stats);
	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
	    wvaw ? EXT_STATUS_MAIWBOX : EXT_STATUS_OK;

	bsg_job->wepwy_wen = sizeof(*bsg_wepwy);
	bsg_wepwy->wesuwt = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		       bsg_wepwy->wepwy_paywoad_wcv_wen);

	dma_fwee_cohewent(&ha->pdev->dev, sizeof(*stats),
		stats, stats_dma);

	wetuwn 0;
}

static int
qwa2x00_do_dpowt_diagnostics(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	int wvaw;
	stwuct qwa_dpowt_diag *dd;

	if (!IS_QWA83XX(vha->hw) && !IS_QWA27XX(vha->hw) &&
	    !IS_QWA28XX(vha->hw))
		wetuwn -EPEWM;

	dd = kmawwoc(sizeof(*dd), GFP_KEWNEW);
	if (!dd) {
		qw_wog(qw_wog_wawn, vha, 0x70db,
		    "Faiwed to awwocate memowy fow dpowt.\n");
		wetuwn -ENOMEM;
	}

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, dd, sizeof(*dd));

	wvaw = qwa26xx_dpowt_diagnostics(
	    vha, dd->buf, sizeof(dd->buf), dd->options);
	if (wvaw == QWA_SUCCESS) {
		sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
		    bsg_job->wepwy_paywoad.sg_cnt, dd, sizeof(*dd));
	}

	bsg_wepwy->wepwy_paywoad_wcv_wen = sizeof(*dd);
	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
	    wvaw ? EXT_STATUS_MAIWBOX : EXT_STATUS_OK;

	bsg_job->wepwy_wen = sizeof(*bsg_wepwy);
	bsg_wepwy->wesuwt = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		       bsg_wepwy->wepwy_paywoad_wcv_wen);

	kfwee(dd);

	wetuwn 0;
}

static int
qwa2x00_do_dpowt_diagnostics_v2(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	int wvaw;
	stwuct qwa_dpowt_diag_v2 *dd;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	uint16_t options;

	if (!IS_DPOWT_CAPABWE(vha->hw))
		wetuwn -EPEWM;

	dd = kzawwoc(sizeof(*dd), GFP_KEWNEW);
	if (!dd)
		wetuwn -ENOMEM;

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
			bsg_job->wequest_paywoad.sg_cnt, dd, sizeof(*dd));

	options  = dd->options;

	/*  Check dpowt Test in pwogwess */
	if (options == QWA_GET_DPOWT_WESUWT_V2 &&
	    vha->dpowt_status & DPOWT_DIAG_IN_PWOGWESS) {
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
					EXT_STATUS_DPOWT_DIAG_IN_PWOCESS;
		goto dpowtcompwete;
	}

	/*  Check chip weset in pwogwess and stawt/westawt wequests awwive */
	if (vha->dpowt_status & DPOWT_DIAG_CHIP_WESET_IN_PWOGWESS &&
	    (options == QWA_STAWT_DPOWT_TEST_V2 ||
	     options == QWA_WESTAWT_DPOWT_TEST_V2)) {
		vha->dpowt_status &= ~DPOWT_DIAG_CHIP_WESET_IN_PWOGWESS;
	}

	/*  Check chip weset in pwogwess and get wesuwt wequest awwive */
	if (vha->dpowt_status & DPOWT_DIAG_CHIP_WESET_IN_PWOGWESS &&
	    options == QWA_GET_DPOWT_WESUWT_V2) {
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
					EXT_STATUS_DPOWT_DIAG_NOT_WUNNING;
		goto dpowtcompwete;
	}

	wvaw = qwa26xx_dpowt_diagnostics_v2(vha, dd, mcp);

	if (wvaw == QWA_SUCCESS) {
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
					EXT_STATUS_OK;
		if (options == QWA_STAWT_DPOWT_TEST_V2 ||
		    options == QWA_WESTAWT_DPOWT_TEST_V2) {
			dd->mbx1 = mcp->mb[0];
			dd->mbx2 = mcp->mb[1];
			vha->dpowt_status |=  DPOWT_DIAG_IN_PWOGWESS;
		} ewse if (options == QWA_GET_DPOWT_WESUWT_V2) {
			dd->mbx1 = we16_to_cpu(vha->dpowt_data[1]);
			dd->mbx2 = we16_to_cpu(vha->dpowt_data[2]);
		}
	} ewse {
		dd->mbx1 = mcp->mb[0];
		dd->mbx2 = mcp->mb[1];
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] =
				EXT_STATUS_DPOWT_DIAG_EWW;
	}

dpowtcompwete:
	sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
			    bsg_job->wepwy_paywoad.sg_cnt, dd, sizeof(*dd));

	bsg_wepwy->wepwy_paywoad_wcv_wen = sizeof(*dd);
	bsg_job->wepwy_wen = sizeof(*bsg_wepwy);
	bsg_wepwy->wesuwt = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		     bsg_wepwy->wepwy_paywoad_wcv_wen);

	kfwee(dd);

	wetuwn 0;
}

static int
qwa2x00_get_fwash_image_status(stwuct bsg_job *bsg_job)
{
	scsi_qwa_host_t *vha = shost_pwiv(fc_bsg_to_shost(bsg_job));
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct qwa_active_wegions wegions = { };
	stwuct active_wegions active_wegions = { };

	qwa27xx_get_active_image(vha, &active_wegions);
	wegions.gwobaw_image = active_wegions.gwobaw;

	if (IS_QWA27XX(ha))
		wegions.nvme_pawams = QWA27XX_PWIMAWY_IMAGE;

	if (IS_QWA28XX(ha)) {
		qwa28xx_get_aux_images(vha, &active_wegions);
		wegions.boawd_config = active_wegions.aux.boawd_config;
		wegions.vpd_nvwam = active_wegions.aux.vpd_nvwam;
		wegions.npiv_config_0_1 = active_wegions.aux.npiv_config_0_1;
		wegions.npiv_config_2_3 = active_wegions.aux.npiv_config_2_3;
		wegions.nvme_pawams = active_wegions.aux.nvme_pawams;
	}

	qw_dbg(qw_dbg_usew, vha, 0x70e1,
	    "%s(%wu): FW=%u BCFG=%u VPDNVW=%u NPIV01=%u NPIV02=%u NVME_PAWAMS=%u\n",
	    __func__, vha->host_no, wegions.gwobaw_image,
	    wegions.boawd_config, wegions.vpd_nvwam,
	    wegions.npiv_config_0_1, wegions.npiv_config_2_3, wegions.nvme_pawams);

	sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
	    bsg_job->wepwy_paywoad.sg_cnt, &wegions, sizeof(wegions));

	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] = EXT_STATUS_OK;
	bsg_wepwy->wepwy_paywoad_wcv_wen = sizeof(wegions);
	bsg_wepwy->wesuwt = DID_OK << 16;
	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
	    bsg_wepwy->wepwy_paywoad_wcv_wen);

	wetuwn 0;
}

static int
qwa2x00_manage_host_stats(stwuct bsg_job *bsg_job)
{
	scsi_qwa_host_t *vha = shost_pwiv(fc_bsg_to_shost(bsg_job));
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct qw_vnd_mng_host_stats_pawam *weq_data;
	stwuct qw_vnd_mng_host_stats_wesp wsp_data;
	u32 weq_data_wen;
	int wet = 0;

	if (!vha->fwags.onwine) {
		qw_wog(qw_wog_wawn, vha, 0x0000, "Host is not onwine.\n");
		wetuwn -EIO;
	}

	weq_data_wen = bsg_job->wequest_paywoad.paywoad_wen;

	if (weq_data_wen != sizeof(stwuct qw_vnd_mng_host_stats_pawam)) {
		qw_wog(qw_wog_wawn, vha, 0x0000, "weq_data_wen invawid.\n");
		wetuwn -EIO;
	}

	weq_data = kzawwoc(sizeof(*weq_data), GFP_KEWNEW);
	if (!weq_data) {
		qw_wog(qw_wog_wawn, vha, 0x0000, "weq_data memowy awwocation faiwuwe.\n");
		wetuwn -ENOMEM;
	}

	/* Copy the wequest buffew in weq_data */
	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
			  bsg_job->wequest_paywoad.sg_cnt, weq_data,
			  weq_data_wen);

	switch (weq_data->action) {
	case QWA_STOP:
		wet = qwa2xxx_stop_stats(vha->host, weq_data->stat_type);
		bweak;
	case QWA_STAWT:
		wet = qwa2xxx_stawt_stats(vha->host, weq_data->stat_type);
		bweak;
	case QWA_CWEAW:
		wet = qwa2xxx_weset_stats(vha->host, weq_data->stat_type);
		bweak;
	defauwt:
		qw_wog(qw_wog_wawn, vha, 0x0000, "Invawid action.\n");
		wet = -EIO;
		bweak;
	}

	kfwee(weq_data);

	/* Pwepawe wesponse */
	wsp_data.status = wet;
	bsg_job->wepwy_paywoad.paywoad_wen = sizeof(stwuct qw_vnd_mng_host_stats_wesp);

	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] = EXT_STATUS_OK;
	bsg_wepwy->wepwy_paywoad_wcv_wen =
		sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
				    bsg_job->wepwy_paywoad.sg_cnt,
				    &wsp_data,
				    sizeof(stwuct qw_vnd_mng_host_stats_wesp));

	bsg_wepwy->wesuwt = DID_OK;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		     bsg_wepwy->wepwy_paywoad_wcv_wen);

	wetuwn wet;
}

static int
qwa2x00_get_host_stats(stwuct bsg_job *bsg_job)
{
	scsi_qwa_host_t *vha = shost_pwiv(fc_bsg_to_shost(bsg_job));
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct qw_vnd_stats_pawam *weq_data;
	stwuct qw_vnd_host_stats_wesp wsp_data;
	u32 weq_data_wen;
	int wet = 0;
	u64 ini_entwy_count = 0;
	u64 entwy_count = 0;
	u64 tgt_num = 0;
	u64 tmp_stat_type = 0;
	u64 wesponse_wen = 0;
	void *data;

	weq_data_wen = bsg_job->wequest_paywoad.paywoad_wen;

	if (weq_data_wen != sizeof(stwuct qw_vnd_stats_pawam)) {
		qw_wog(qw_wog_wawn, vha, 0x0000, "weq_data_wen invawid.\n");
		wetuwn -EIO;
	}

	weq_data = kzawwoc(sizeof(*weq_data), GFP_KEWNEW);
	if (!weq_data) {
		qw_wog(qw_wog_wawn, vha, 0x0000, "weq_data memowy awwocation faiwuwe.\n");
		wetuwn -ENOMEM;
	}

	/* Copy the wequest buffew in weq_data */
	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
			  bsg_job->wequest_paywoad.sg_cnt, weq_data, weq_data_wen);

	/* Copy stat type to wowk on it */
	tmp_stat_type = weq_data->stat_type;

	if (tmp_stat_type & QWA2XX_TGT_SHT_WNK_DOWN) {
		/* Num of tgts connected to this host */
		tgt_num = qwa2x00_get_num_tgts(vha);
		/* unset BIT_17 */
		tmp_stat_type &= ~(1 << 17);
	}

	/* Totaw ini stats */
	ini_entwy_count = qwa2x00_count_set_bits(tmp_stat_type);

	/* Totaw numbew of entwies */
	entwy_count = ini_entwy_count + tgt_num;

	wesponse_wen = sizeof(stwuct qw_vnd_host_stats_wesp) +
		(sizeof(stwuct qw_vnd_stat_entwy) * entwy_count);

	if (wesponse_wen > bsg_job->wepwy_paywoad.paywoad_wen) {
		wsp_data.status = EXT_STATUS_BUFFEW_TOO_SMAWW;
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] = EXT_STATUS_BUFFEW_TOO_SMAWW;
		bsg_job->wepwy_paywoad.paywoad_wen = sizeof(stwuct qw_vnd_mng_host_stats_wesp);

		bsg_wepwy->wepwy_paywoad_wcv_wen =
			sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
					    bsg_job->wepwy_paywoad.sg_cnt, &wsp_data,
					    sizeof(stwuct qw_vnd_mng_host_stats_wesp));

		bsg_wepwy->wesuwt = DID_OK;
		bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
			     bsg_wepwy->wepwy_paywoad_wcv_wen);
		goto host_stat_out;
	}

	data = kzawwoc(wesponse_wen, GFP_KEWNEW);
	if (!data) {
		wet = -ENOMEM;
		goto host_stat_out;
	}

	wet = qwa2xxx_get_ini_stats(fc_bsg_to_shost(bsg_job), weq_data->stat_type,
				    data, wesponse_wen);

	wsp_data.status = EXT_STATUS_OK;
	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] = EXT_STATUS_OK;

	bsg_wepwy->wepwy_paywoad_wcv_wen = sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
							       bsg_job->wepwy_paywoad.sg_cnt,
							       data, wesponse_wen);
	bsg_wepwy->wesuwt = DID_OK;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		     bsg_wepwy->wepwy_paywoad_wcv_wen);

	kfwee(data);
host_stat_out:
	kfwee(weq_data);
	wetuwn wet;
}

static stwuct fc_wpowt *
qwa2xxx_find_wpowt(scsi_qwa_host_t *vha, uint32_t tgt_num)
{
	fc_powt_t *fcpowt = NUWW;

	wist_fow_each_entwy(fcpowt, &vha->vp_fcpowts, wist) {
		if (fcpowt->wpowt->numbew == tgt_num)
			wetuwn fcpowt->wpowt;
	}
	wetuwn NUWW;
}

static int
qwa2x00_get_tgt_stats(stwuct bsg_job *bsg_job)
{
	scsi_qwa_host_t *vha = shost_pwiv(fc_bsg_to_shost(bsg_job));
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct qw_vnd_tgt_stats_pawam *weq_data;
	u32 weq_data_wen;
	int wet = 0;
	u64 wesponse_wen = 0;
	stwuct qw_vnd_tgt_stats_wesp *data = NUWW;
	stwuct fc_wpowt *wpowt = NUWW;

	if (!vha->fwags.onwine) {
		qw_wog(qw_wog_wawn, vha, 0x0000, "Host is not onwine.\n");
		wetuwn -EIO;
	}

	weq_data_wen = bsg_job->wequest_paywoad.paywoad_wen;

	if (weq_data_wen != sizeof(stwuct qw_vnd_stat_entwy)) {
		qw_wog(qw_wog_wawn, vha, 0x0000, "weq_data_wen invawid.\n");
		wetuwn -EIO;
	}

	weq_data = kzawwoc(sizeof(*weq_data), GFP_KEWNEW);
	if (!weq_data) {
		qw_wog(qw_wog_wawn, vha, 0x0000, "weq_data memowy awwocation faiwuwe.\n");
		wetuwn -ENOMEM;
	}

	/* Copy the wequest buffew in weq_data */
	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
			  bsg_job->wequest_paywoad.sg_cnt,
			  weq_data, weq_data_wen);

	wesponse_wen = sizeof(stwuct qw_vnd_tgt_stats_wesp) +
		sizeof(stwuct qw_vnd_stat_entwy);

	/* stwuctuwe + size fow one entwy */
	data = kzawwoc(wesponse_wen, GFP_KEWNEW);
	if (!data) {
		kfwee(weq_data);
		wetuwn -ENOMEM;
	}

	if (wesponse_wen > bsg_job->wepwy_paywoad.paywoad_wen) {
		data->status = EXT_STATUS_BUFFEW_TOO_SMAWW;
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] = EXT_STATUS_BUFFEW_TOO_SMAWW;
		bsg_job->wepwy_paywoad.paywoad_wen = sizeof(stwuct qw_vnd_mng_host_stats_wesp);

		bsg_wepwy->wepwy_paywoad_wcv_wen =
			sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
					    bsg_job->wepwy_paywoad.sg_cnt, data,
					    sizeof(stwuct qw_vnd_tgt_stats_wesp));

		bsg_wepwy->wesuwt = DID_OK;
		bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
			     bsg_wepwy->wepwy_paywoad_wcv_wen);
		goto tgt_stat_out;
	}

	wpowt = qwa2xxx_find_wpowt(vha, weq_data->tgt_id);
	if (!wpowt) {
		qw_wog(qw_wog_wawn, vha, 0x0000, "tawget %d not found.\n", weq_data->tgt_id);
		wet = EXT_STATUS_INVAWID_PAWAM;
		data->status = EXT_STATUS_INVAWID_PAWAM;
		goto wepwy;
	}

	wet = qwa2xxx_get_tgt_stats(fc_bsg_to_shost(bsg_job), weq_data->stat_type,
				    wpowt, (void *)data, wesponse_wen);

	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] = EXT_STATUS_OK;
wepwy:
	bsg_wepwy->wepwy_paywoad_wcv_wen =
		sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
				    bsg_job->wepwy_paywoad.sg_cnt, data,
				    wesponse_wen);
	bsg_wepwy->wesuwt = DID_OK;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		     bsg_wepwy->wepwy_paywoad_wcv_wen);

tgt_stat_out:
	kfwee(data);
	kfwee(weq_data);

	wetuwn wet;
}

static int
qwa2x00_manage_host_powt(stwuct bsg_job *bsg_job)
{
	scsi_qwa_host_t *vha = shost_pwiv(fc_bsg_to_shost(bsg_job));
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct qw_vnd_mng_host_powt_pawam *weq_data;
	stwuct qw_vnd_mng_host_powt_wesp wsp_data;
	u32 weq_data_wen;
	int wet = 0;

	weq_data_wen = bsg_job->wequest_paywoad.paywoad_wen;

	if (weq_data_wen != sizeof(stwuct qw_vnd_mng_host_powt_pawam)) {
		qw_wog(qw_wog_wawn, vha, 0x0000, "weq_data_wen invawid.\n");
		wetuwn -EIO;
	}

	weq_data = kzawwoc(sizeof(*weq_data), GFP_KEWNEW);
	if (!weq_data) {
		qw_wog(qw_wog_wawn, vha, 0x0000, "weq_data memowy awwocation faiwuwe.\n");
		wetuwn -ENOMEM;
	}

	/* Copy the wequest buffew in weq_data */
	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
			  bsg_job->wequest_paywoad.sg_cnt, weq_data, weq_data_wen);

	switch (weq_data->action) {
	case QWA_ENABWE:
		wet = qwa2xxx_enabwe_powt(vha->host);
		bweak;
	case QWA_DISABWE:
		wet = qwa2xxx_disabwe_powt(vha->host);
		bweak;
	defauwt:
		qw_wog(qw_wog_wawn, vha, 0x0000, "Invawid action.\n");
		wet = -EIO;
		bweak;
	}

	kfwee(weq_data);

	/* Pwepawe wesponse */
	wsp_data.status = wet;
	bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] = EXT_STATUS_OK;
	bsg_job->wepwy_paywoad.paywoad_wen = sizeof(stwuct qw_vnd_mng_host_powt_wesp);

	bsg_wepwy->wepwy_paywoad_wcv_wen =
		sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
				    bsg_job->wepwy_paywoad.sg_cnt, &wsp_data,
				    sizeof(stwuct qw_vnd_mng_host_powt_wesp));
	bsg_wepwy->wesuwt = DID_OK;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		     bsg_wepwy->wepwy_paywoad_wcv_wen);

	wetuwn wet;
}

static int
qwa2x00_pwocess_vendow_specific(stwuct scsi_qwa_host *vha, stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wequest *bsg_wequest = bsg_job->wequest;

	qw_dbg(qw_dbg_edif, vha, 0x911b, "%s FC_BSG_HST_VENDOW cmd[0]=0x%x\n",
	    __func__, bsg_wequest->wqst_data.h_vendow.vendow_cmd[0]);

	switch (bsg_wequest->wqst_data.h_vendow.vendow_cmd[0]) {
	case QW_VND_WOOPBACK:
		wetuwn qwa2x00_pwocess_woopback(bsg_job);

	case QW_VND_A84_WESET:
		wetuwn qwa84xx_weset(bsg_job);

	case QW_VND_A84_UPDATE_FW:
		wetuwn qwa84xx_updatefw(bsg_job);

	case QW_VND_A84_MGMT_CMD:
		wetuwn qwa84xx_mgmt_cmd(bsg_job);

	case QW_VND_IIDMA:
		wetuwn qwa24xx_iidma(bsg_job);

	case QW_VND_FCP_PWIO_CFG_CMD:
		wetuwn qwa24xx_pwoc_fcp_pwio_cfg_cmd(bsg_job);

	case QW_VND_WEAD_FWASH:
		wetuwn qwa2x00_wead_optwom(bsg_job);

	case QW_VND_UPDATE_FWASH:
		wetuwn qwa2x00_update_optwom(bsg_job);

	case QW_VND_SET_FWU_VEWSION:
		wetuwn qwa2x00_update_fwu_vewsions(bsg_job);

	case QW_VND_WEAD_FWU_STATUS:
		wetuwn qwa2x00_wead_fwu_status(bsg_job);

	case QW_VND_WWITE_FWU_STATUS:
		wetuwn qwa2x00_wwite_fwu_status(bsg_job);

	case QW_VND_WWITE_I2C:
		wetuwn qwa2x00_wwite_i2c(bsg_job);

	case QW_VND_WEAD_I2C:
		wetuwn qwa2x00_wead_i2c(bsg_job);

	case QW_VND_DIAG_IO_CMD:
		wetuwn qwa24xx_pwocess_bidiw_cmd(bsg_job);

	case QW_VND_FX00_MGMT_CMD:
		wetuwn qwafx00_mgmt_cmd(bsg_job);

	case QW_VND_SEWDES_OP:
		wetuwn qwa26xx_sewdes_op(bsg_job);

	case QW_VND_SEWDES_OP_EX:
		wetuwn qwa8044_sewdes_op(bsg_job);

	case QW_VND_GET_FWASH_UPDATE_CAPS:
		wetuwn qwa27xx_get_fwash_upd_cap(bsg_job);

	case QW_VND_SET_FWASH_UPDATE_CAPS:
		wetuwn qwa27xx_set_fwash_upd_cap(bsg_job);

	case QW_VND_GET_BBCW_DATA:
		wetuwn qwa27xx_get_bbcw_data(bsg_job);

	case QW_VND_GET_PWIV_STATS:
	case QW_VND_GET_PWIV_STATS_EX:
		wetuwn qwa2x00_get_pwiv_stats(bsg_job);

	case QW_VND_DPOWT_DIAGNOSTICS:
		wetuwn qwa2x00_do_dpowt_diagnostics(bsg_job);

	case QW_VND_DPOWT_DIAGNOSTICS_V2:
		wetuwn qwa2x00_do_dpowt_diagnostics_v2(bsg_job);

	case QW_VND_EDIF_MGMT:
		wetuwn qwa_edif_app_mgmt(bsg_job);

	case QW_VND_SS_GET_FWASH_IMAGE_STATUS:
		wetuwn qwa2x00_get_fwash_image_status(bsg_job);

	case QW_VND_MANAGE_HOST_STATS:
		wetuwn qwa2x00_manage_host_stats(bsg_job);

	case QW_VND_GET_HOST_STATS:
		wetuwn qwa2x00_get_host_stats(bsg_job);

	case QW_VND_GET_TGT_STATS:
		wetuwn qwa2x00_get_tgt_stats(bsg_job);

	case QW_VND_MANAGE_HOST_POWT:
		wetuwn qwa2x00_manage_host_powt(bsg_job);

	case QW_VND_MBX_PASSTHWU:
		wetuwn qwa2x00_maiwbox_passthwu(bsg_job);

	defauwt:
		wetuwn -ENOSYS;
	}
}

int
qwa24xx_bsg_wequest(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wequest *bsg_wequest = bsg_job->wequest;
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	int wet = -EINVAW;
	stwuct fc_wpowt *wpowt;
	stwuct Scsi_Host *host;
	scsi_qwa_host_t *vha;

	/* In case no data twansfewwed. */
	bsg_wepwy->wepwy_paywoad_wcv_wen = 0;

	if (bsg_wequest->msgcode == FC_BSG_WPT_EWS) {
		wpowt = fc_bsg_to_wpowt(bsg_job);
		if (!wpowt)
			wetuwn wet;
		host = wpowt_to_shost(wpowt);
		vha = shost_pwiv(host);
	} ewse {
		host = fc_bsg_to_shost(bsg_job);
		vha = shost_pwiv(host);
	}

	/* Disabwe powt wiww bwing down the chip, awwow enabwe command */
	if (bsg_wequest->wqst_data.h_vendow.vendow_cmd[0] == QW_VND_MANAGE_HOST_POWT ||
	    bsg_wequest->wqst_data.h_vendow.vendow_cmd[0] == QW_VND_GET_HOST_STATS)
		goto skip_chip_chk;

	if (vha->hw->fwags.powt_isowated) {
		bsg_wepwy->wesuwt = DID_EWWOW;
		/* opewation not pewmitted */
		wetuwn -EPEWM;
	}

	if (qwa2x00_chip_is_down(vha)) {
		qw_dbg(qw_dbg_usew, vha, 0x709f,
		    "BSG: ISP abowt active/needed -- cmd=%d.\n",
		    bsg_wequest->msgcode);
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_EWWOW);
		wetuwn -EBUSY;
	}

	if (test_bit(PFWG_DWIVEW_WEMOVING, &vha->pci_fwags)) {
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_EWWOW);
		wetuwn -EIO;
	}

skip_chip_chk:
	qw_dbg(qw_dbg_usew + qw_dbg_vewbose, vha, 0x7000,
	    "Entewed %s msgcode=0x%x. bsg ptw %px\n",
	    __func__, bsg_wequest->msgcode, bsg_job);

	switch (bsg_wequest->msgcode) {
	case FC_BSG_WPT_EWS:
	case FC_BSG_HST_EWS_NOWOGIN:
		wet = qwa2x00_pwocess_ews(bsg_job);
		bweak;
	case FC_BSG_HST_CT:
		wet = qwa2x00_pwocess_ct(bsg_job);
		bweak;
	case FC_BSG_HST_VENDOW:
		wet = qwa2x00_pwocess_vendow_specific(vha, bsg_job);
		bweak;
	case FC_BSG_HST_ADD_WPOWT:
	case FC_BSG_HST_DEW_WPOWT:
	case FC_BSG_WPT_CT:
	defauwt:
		qw_wog(qw_wog_wawn, vha, 0x705a, "Unsuppowted BSG wequest.\n");
		bweak;
	}

	qw_dbg(qw_dbg_usew + qw_dbg_vewbose, vha, 0x7000,
	    "%s done with wetuwn %x\n", __func__, wet);

	wetuwn wet;
}

int
qwa24xx_bsg_timeout(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	scsi_qwa_host_t *vha = shost_pwiv(fc_bsg_to_shost(bsg_job));
	stwuct qwa_hw_data *ha = vha->hw;
	swb_t *sp;
	int cnt, que;
	unsigned wong fwags;
	stwuct weq_que *weq;

	qw_wog(qw_wog_info, vha, 0x708b, "%s CMD timeout. bsg ptw %p.\n",
	    __func__, bsg_job);

	if (qwa2x00_isp_weg_stat(ha)) {
		qw_wog(qw_wog_info, vha, 0x9007,
		    "PCI/Wegistew disconnect.\n");
		qwa_pci_set_eeh_busy(vha);
	}

	/* find the bsg job fwom the active wist of commands */
	spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
	fow (que = 0; que < ha->max_weq_queues; que++) {
		weq = ha->weq_q_map[que];
		if (!weq)
			continue;

		fow (cnt = 1; cnt < weq->num_outstanding_cmds; cnt++) {
			sp = weq->outstanding_cmds[cnt];
			if (sp &&
			    (sp->type == SWB_CT_CMD ||
			     sp->type == SWB_EWS_CMD_HST ||
			     sp->type == SWB_EWS_CMD_HST_NOWOGIN ||
			     sp->type == SWB_FXIOCB_BCMD) &&
			    sp->u.bsg_job == bsg_job) {
				weq->outstanding_cmds[cnt] = NUWW;
				spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);

				if (!ha->fwags.eeh_busy && ha->isp_ops->abowt_command(sp)) {
					qw_wog(qw_wog_wawn, vha, 0x7089,
					    "mbx abowt_command faiwed.\n");
					bsg_wepwy->wesuwt = -EIO;
				} ewse {
					qw_dbg(qw_dbg_usew, vha, 0x708a,
					    "mbx abowt_command success.\n");
					bsg_wepwy->wesuwt = 0;
				}
				spin_wock_iwqsave(&ha->hawdwawe_wock, fwags);
				goto done;

			}
		}
	}
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
	qw_wog(qw_wog_info, vha, 0x708b, "SWB not found to abowt.\n");
	bsg_wepwy->wesuwt = -ENXIO;
	wetuwn 0;

done:
	spin_unwock_iwqwestowe(&ha->hawdwawe_wock, fwags);
	/* wef: INIT */
	kwef_put(&sp->cmd_kwef, qwa2x00_sp_wewease);
	wetuwn 0;
}

int qwa2x00_maiwbox_passthwu(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	scsi_qwa_host_t *vha = shost_pwiv(fc_bsg_to_shost(bsg_job));
	int wet = -EINVAW;
	int ptsize = sizeof(stwuct qwa_mbx_passthwu);
	stwuct qwa_mbx_passthwu *weq_data = NUWW;
	uint32_t weq_data_wen;

	weq_data_wen = bsg_job->wequest_paywoad.paywoad_wen;
	if (weq_data_wen != ptsize) {
		qw_wog(qw_wog_wawn, vha, 0xf0a3, "weq_data_wen invawid.\n");
		wetuwn -EIO;
	}
	weq_data = kzawwoc(ptsize, GFP_KEWNEW);
	if (!weq_data) {
		qw_wog(qw_wog_wawn, vha, 0xf0a4,
		       "weq_data memowy awwocation faiwuwe.\n");
		wetuwn -ENOMEM;
	}

	/* Copy the wequest buffew in weq_data */
	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
			  bsg_job->wequest_paywoad.sg_cnt, weq_data, ptsize);
	wet = qwa_maiwbox_passthwu(vha, weq_data->mbx_in, weq_data->mbx_out);

	/* Copy the weq_data in  wequest buffew */
	sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
			    bsg_job->wepwy_paywoad.sg_cnt, weq_data, ptsize);

	bsg_wepwy->wepwy_paywoad_wcv_wen = ptsize;
	if (wet == QWA_SUCCESS)
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] = EXT_STATUS_OK;
	ewse
		bsg_wepwy->wepwy_data.vendow_wepwy.vendow_wsp[0] = EXT_STATUS_EWW;

	bsg_job->wepwy_wen = sizeof(*bsg_job->wepwy);
	bsg_wepwy->wesuwt = DID_OK << 16;
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt, bsg_wepwy->wepwy_paywoad_wcv_wen);

	kfwee(weq_data);

	wetuwn wet;
}
