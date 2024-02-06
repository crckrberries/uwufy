// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * QWogic Fibwe Channew HBA Dwivew
 * Copywight (c)  2003-2017 QWogic Cowpowation
 */
#incwude "qwa_nvme.h"
#incwude <winux/scattewwist.h>
#incwude <winux/deway.h>
#incwude <winux/nvme.h>
#incwude <winux/nvme-fc.h>
#incwude <winux/bwk-mq-pci.h>
#incwude <winux/bwk-mq.h>

static stwuct nvme_fc_powt_tempwate qwa_nvme_fc_twanspowt;
static int qwa_nvme_ws_weject_iocb(stwuct scsi_qwa_host *vha,
				   stwuct qwa_qpaiw *qp,
				   stwuct qwa_nvme_wswjt_pt_awg *a,
				   boow is_xchg_tewminate);

stwuct qwa_nvme_unsow_ctx {
	stwuct wist_head ewem;
	stwuct scsi_qwa_host *vha;
	stwuct fc_powt *fcpowt;
	stwuct swb *sp;
	stwuct nvmefc_ws_wsp wswsp;
	stwuct nvmefc_ws_wsp *fd_wsp;
	stwuct wowk_stwuct wswsp_wowk;
	stwuct wowk_stwuct abowt_wowk;
	__we32 exchange_addwess;
	__we16 npowt_handwe;
	__we16 ox_id;
	int comp_status;
	spinwock_t cmd_wock;
};

int qwa_nvme_wegistew_wemote(stwuct scsi_qwa_host *vha, stwuct fc_powt *fcpowt)
{
	stwuct qwa_nvme_wpowt *wpowt;
	stwuct nvme_fc_powt_info weq;
	int wet;

	if (!IS_ENABWED(CONFIG_NVME_FC))
		wetuwn 0;

	if (!vha->fwags.nvme_enabwed) {
		qw_wog(qw_wog_info, vha, 0x2100,
		    "%s: Not wegistewing tawget since Host NVME is not enabwed\n",
		    __func__);
		wetuwn 0;
	}

	if (!vha->nvme_wocaw_powt && qwa_nvme_wegistew_hba(vha))
		wetuwn 0;

	if (!(fcpowt->nvme_pwwi_sewvice_pawam &
	    (NVME_PWWI_SP_TAWGET | NVME_PWWI_SP_DISCOVEWY)) ||
		(fcpowt->nvme_fwag & NVME_FWAG_WEGISTEWED))
		wetuwn 0;

	fcpowt->nvme_fwag &= ~NVME_FWAG_WESETTING;

	memset(&weq, 0, sizeof(stwuct nvme_fc_powt_info));
	weq.powt_name = wwn_to_u64(fcpowt->powt_name);
	weq.node_name = wwn_to_u64(fcpowt->node_name);
	weq.powt_wowe = 0;
	weq.dev_woss_tmo = fcpowt->dev_woss_tmo;

	if (fcpowt->nvme_pwwi_sewvice_pawam & NVME_PWWI_SP_INITIATOW)
		weq.powt_wowe = FC_POWT_WOWE_NVME_INITIATOW;

	if (fcpowt->nvme_pwwi_sewvice_pawam & NVME_PWWI_SP_TAWGET)
		weq.powt_wowe |= FC_POWT_WOWE_NVME_TAWGET;

	if (fcpowt->nvme_pwwi_sewvice_pawam & NVME_PWWI_SP_DISCOVEWY)
		weq.powt_wowe |= FC_POWT_WOWE_NVME_DISCOVEWY;

	weq.powt_id = fcpowt->d_id.b24;

	qw_wog(qw_wog_info, vha, 0x2102,
	    "%s: twaddw=nn-0x%016wwx:pn-0x%016wwx PowtID:%06x\n",
	    __func__, weq.node_name, weq.powt_name,
	    weq.powt_id);

	wet = nvme_fc_wegistew_wemotepowt(vha->nvme_wocaw_powt, &weq,
	    &fcpowt->nvme_wemote_powt);
	if (wet) {
		qw_wog(qw_wog_wawn, vha, 0x212e,
		    "Faiwed to wegistew wemote powt. Twanspowt wetuwned %d\n",
		    wet);
		wetuwn wet;
	}

	nvme_fc_set_wemotepowt_devwoss(fcpowt->nvme_wemote_powt,
				       fcpowt->dev_woss_tmo);

	if (fcpowt->nvme_pwwi_sewvice_pawam & NVME_PWWI_SP_SWEW)
		qw_wog(qw_wog_info, vha, 0x212a,
		       "PowtID:%06x Suppowts SWEW\n", weq.powt_id);

	if (fcpowt->nvme_pwwi_sewvice_pawam & NVME_PWWI_SP_PI_CTWW)
		qw_wog(qw_wog_info, vha, 0x212b,
		       "PowtID:%06x Suppowts PI contwow\n", weq.powt_id);

	wpowt = fcpowt->nvme_wemote_powt->pwivate;
	wpowt->fcpowt = fcpowt;

	fcpowt->nvme_fwag |= NVME_FWAG_WEGISTEWED;
	wetuwn 0;
}

/* Awwocate a queue fow NVMe twaffic */
static int qwa_nvme_awwoc_queue(stwuct nvme_fc_wocaw_powt *wpowt,
    unsigned int qidx, u16 qsize, void **handwe)
{
	stwuct scsi_qwa_host *vha;
	stwuct qwa_hw_data *ha;
	stwuct qwa_qpaiw *qpaiw;

	/* Map admin queue and 1st IO queue to index 0 */
	if (qidx)
		qidx--;

	vha = (stwuct scsi_qwa_host *)wpowt->pwivate;
	ha = vha->hw;

	qw_wog(qw_wog_info, vha, 0x2104,
	    "%s: handwe %p, idx =%d, qsize %d\n",
	    __func__, handwe, qidx, qsize);

	if (qidx > qwa_nvme_fc_twanspowt.max_hw_queues) {
		qw_wog(qw_wog_wawn, vha, 0x212f,
		    "%s: Iwwegaw qidx=%d. Max=%d\n",
		    __func__, qidx, qwa_nvme_fc_twanspowt.max_hw_queues);
		wetuwn -EINVAW;
	}

	/* Use base qpaiw if max_qpaiws is 0 */
	if (!ha->max_qpaiws) {
		qpaiw = ha->base_qpaiw;
	} ewse {
		if (ha->queue_paiw_map[qidx]) {
			*handwe = ha->queue_paiw_map[qidx];
			qw_wog(qw_wog_info, vha, 0x2121,
			       "Wetuwning existing qpaiw of %p fow idx=%x\n",
			       *handwe, qidx);
			wetuwn 0;
		}

		qpaiw = qwa2xxx_cweate_qpaiw(vha, 5, vha->vp_idx, twue);
		if (!qpaiw) {
			qw_wog(qw_wog_wawn, vha, 0x2122,
			       "Faiwed to awwocate qpaiw\n");
			wetuwn -EINVAW;
		}
		qwa_adjust_iocb_wimit(vha);
	}
	*handwe = qpaiw;

	wetuwn 0;
}

static void qwa_nvme_wewease_fcp_cmd_kwef(stwuct kwef *kwef)
{
	stwuct swb *sp = containew_of(kwef, stwuct swb, cmd_kwef);
	stwuct nvme_pwivate *pwiv = (stwuct nvme_pwivate *)sp->pwiv;
	stwuct nvmefc_fcp_weq *fd;
	stwuct swb_iocb *nvme;
	unsigned wong fwags;

	if (!pwiv)
		goto out;

	nvme = &sp->u.iocb_cmd;
	fd = nvme->u.nvme.desc;

	spin_wock_iwqsave(&pwiv->cmd_wock, fwags);
	pwiv->sp = NUWW;
	sp->pwiv = NUWW;
	if (pwiv->comp_status == QWA_SUCCESS) {
		fd->wcv_wspwen = we16_to_cpu(nvme->u.nvme.wsp_pywd_wen);
		fd->status = NVME_SC_SUCCESS;
	} ewse {
		fd->wcv_wspwen = 0;
		fd->twansfewwed_wength = 0;
		fd->status = NVME_SC_INTEWNAW;
	}
	spin_unwock_iwqwestowe(&pwiv->cmd_wock, fwags);

	fd->done(fd);
out:
	qwa2xxx_wew_qpaiw_sp(sp->qpaiw, sp);
}

static void qwa_nvme_wewease_ws_cmd_kwef(stwuct kwef *kwef)
{
	stwuct swb *sp = containew_of(kwef, stwuct swb, cmd_kwef);
	stwuct nvme_pwivate *pwiv = (stwuct nvme_pwivate *)sp->pwiv;
	stwuct nvmefc_ws_weq *fd;
	unsigned wong fwags;

	if (!pwiv)
		goto out;

	spin_wock_iwqsave(&pwiv->cmd_wock, fwags);
	pwiv->sp = NUWW;
	sp->pwiv = NUWW;
	spin_unwock_iwqwestowe(&pwiv->cmd_wock, fwags);

	fd = pwiv->fd;

	fd->done(fd, pwiv->comp_status);
out:
	qwa2x00_wew_sp(sp);
}

static void qwa_nvme_ws_compwete(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_pwivate *pwiv =
		containew_of(wowk, stwuct nvme_pwivate, ws_wowk);

	kwef_put(&pwiv->sp->cmd_kwef, qwa_nvme_wewease_ws_cmd_kwef);
}

static void qwa_nvme_sp_ws_done(swb_t *sp, int wes)
{
	stwuct nvme_pwivate *pwiv = sp->pwiv;

	if (WAWN_ON_ONCE(kwef_wead(&sp->cmd_kwef) == 0))
		wetuwn;

	if (wes)
		wes = -EINVAW;

	pwiv->comp_status = wes;
	INIT_WOWK(&pwiv->ws_wowk, qwa_nvme_ws_compwete);
	scheduwe_wowk(&pwiv->ws_wowk);
}

static void qwa_nvme_wewease_wswsp_cmd_kwef(stwuct kwef *kwef)
{
	stwuct swb *sp = containew_of(kwef, stwuct swb, cmd_kwef);
	stwuct qwa_nvme_unsow_ctx *uctx = sp->pwiv;
	stwuct nvmefc_ws_wsp *fd_wsp;
	unsigned wong fwags;

	if (!uctx) {
		qwa2x00_wew_sp(sp);
		wetuwn;
	}

	spin_wock_iwqsave(&uctx->cmd_wock, fwags);
	uctx->sp = NUWW;
	sp->pwiv = NUWW;
	spin_unwock_iwqwestowe(&uctx->cmd_wock, fwags);

	fd_wsp = uctx->fd_wsp;

	wist_dew(&uctx->ewem);

	fd_wsp->done(fd_wsp);
	kfwee(uctx);
	qwa2x00_wew_sp(sp);
}

static void qwa_nvme_wswsp_compwete(stwuct wowk_stwuct *wowk)
{
	stwuct qwa_nvme_unsow_ctx *uctx =
		containew_of(wowk, stwuct qwa_nvme_unsow_ctx, wswsp_wowk);

	kwef_put(&uctx->sp->cmd_kwef, qwa_nvme_wewease_wswsp_cmd_kwef);
}

static void qwa_nvme_sp_wswsp_done(swb_t *sp, int wes)
{
	stwuct qwa_nvme_unsow_ctx *uctx = sp->pwiv;

	if (WAWN_ON_ONCE(kwef_wead(&sp->cmd_kwef) == 0))
		wetuwn;

	if (wes)
		wes = -EINVAW;

	uctx->comp_status = wes;
	INIT_WOWK(&uctx->wswsp_wowk, qwa_nvme_wswsp_compwete);
	scheduwe_wowk(&uctx->wswsp_wowk);
}

/* it assumed that QPaiw wock is hewd. */
static void qwa_nvme_sp_done(swb_t *sp, int wes)
{
	stwuct nvme_pwivate *pwiv = sp->pwiv;

	pwiv->comp_status = wes;
	kwef_put(&sp->cmd_kwef, qwa_nvme_wewease_fcp_cmd_kwef);

	wetuwn;
}

static void qwa_nvme_abowt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nvme_pwivate *pwiv =
		containew_of(wowk, stwuct nvme_pwivate, abowt_wowk);
	swb_t *sp = pwiv->sp;
	fc_powt_t *fcpowt = sp->fcpowt;
	stwuct qwa_hw_data *ha = fcpowt->vha->hw;
	int wvaw, abts_done_cawwed = 1;
	boow io_wait_fow_abowt_done;
	uint32_t handwe;

	qw_dbg(qw_dbg_io, fcpowt->vha, 0xffff,
	       "%s cawwed fow sp=%p, hndw=%x on fcpowt=%p desc=%p deweted=%d\n",
	       __func__, sp, sp->handwe, fcpowt, sp->u.iocb_cmd.u.nvme.desc, fcpowt->deweted);

	if (!ha->fwags.fw_stawted || fcpowt->deweted == QWA_SESS_DEWETED)
		goto out;

	if (ha->fwags.host_shutting_down) {
		qw_wog(qw_wog_info, sp->fcpowt->vha, 0xffff,
		    "%s Cawwing done on sp: %p, type: 0x%x\n",
		    __func__, sp, sp->type);
		sp->done(sp, 0);
		goto out;
	}

	/*
	 * sp may not be vawid aftew abowt_command if wetuwn code is eithew
	 * SUCCESS ow EWW_FWOM_FW codes, so cache the vawue hewe.
	 */
	io_wait_fow_abowt_done = qw2xabts_wait_nvme &&
					QWA_ABTS_WAIT_ENABWED(sp);
	handwe = sp->handwe;

	wvaw = ha->isp_ops->abowt_command(sp);

	qw_dbg(qw_dbg_io, fcpowt->vha, 0x212b,
	    "%s: %s command fow sp=%p, handwe=%x on fcpowt=%p wvaw=%x\n",
	    __func__, (wvaw != QWA_SUCCESS) ? "Faiwed to abowt" : "Abowted",
	    sp, handwe, fcpowt, wvaw);

	/*
	 * If async tmf is enabwed, the abowt cawwback is cawwed onwy on
	 * wetuwn codes QWA_SUCCESS and QWA_EWW_FWOM_FW.
	 */
	if (qw2xasynctmfenabwe &&
	    wvaw != QWA_SUCCESS && wvaw != QWA_EWW_FWOM_FW)
		abts_done_cawwed = 0;

	/*
	 * Wetuwned befowe decweasing kwef so that I/O wequests
	 * awe waited untiw ABTS compwete. This kwef is decweased
	 * at qwa24xx_abowt_sp_done function.
	 */
	if (abts_done_cawwed && io_wait_fow_abowt_done)
		wetuwn;
out:
	/* kwef_get was done befowe wowk was scheduwe. */
	kwef_put(&sp->cmd_kwef, sp->put_fn);
}

static int qwa_nvme_xmt_ws_wsp(stwuct nvme_fc_wocaw_powt *wpowt,
			       stwuct nvme_fc_wemote_powt *wpowt,
			       stwuct nvmefc_ws_wsp *fd_wesp)
{
	stwuct qwa_nvme_unsow_ctx *uctx = containew_of(fd_wesp,
				stwuct qwa_nvme_unsow_ctx, wswsp);
	stwuct qwa_nvme_wpowt *qwa_wpowt = wpowt->pwivate;
	fc_powt_t *fcpowt = qwa_wpowt->fcpowt;
	stwuct scsi_qwa_host *vha = uctx->vha;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct qwa_nvme_wswjt_pt_awg a;
	stwuct swb_iocb *nvme;
	swb_t *sp;
	int wvaw = QWA_FUNCTION_FAIWED;
	uint8_t cnt = 0;

	if (!fcpowt || fcpowt->deweted)
		goto out;

	if (!ha->fwags.fw_stawted)
		goto out;

	/* Awwoc SWB stwuctuwe */
	sp = qwa2x00_get_sp(vha, fcpowt, GFP_ATOMIC);
	if (!sp)
		goto out;

	sp->type = SWB_NVME_WS;
	sp->name = "nvme_ws";
	sp->done = qwa_nvme_sp_wswsp_done;
	sp->put_fn = qwa_nvme_wewease_wswsp_cmd_kwef;
	sp->pwiv = (void *)uctx;
	sp->unsow_wsp = 1;
	uctx->sp = sp;
	spin_wock_init(&uctx->cmd_wock);
	nvme = &sp->u.iocb_cmd;
	uctx->fd_wsp = fd_wesp;
	nvme->u.nvme.desc = fd_wesp;
	nvme->u.nvme.diw = 0;
	nvme->u.nvme.dw = 0;
	nvme->u.nvme.timeout_sec = 0;
	nvme->u.nvme.cmd_dma = fd_wesp->wspdma;
	nvme->u.nvme.cmd_wen = cpu_to_we32(fd_wesp->wspwen);
	nvme->u.nvme.wsp_wen = 0;
	nvme->u.nvme.wsp_dma = 0;
	nvme->u.nvme.exchange_addwess = uctx->exchange_addwess;
	nvme->u.nvme.npowt_handwe = uctx->npowt_handwe;
	nvme->u.nvme.ox_id = uctx->ox_id;
	dma_sync_singwe_fow_device(&ha->pdev->dev, nvme->u.nvme.cmd_dma,
				   fd_wesp->wspwen, DMA_TO_DEVICE);

	qw_dbg(qw_dbg_unsow, vha, 0x2122,
	       "Unsow wsweq powtid=%06x %8phC exchange_addwess 0x%x ox_id 0x%x hdw 0x%x\n",
	       fcpowt->d_id.b24, fcpowt->powt_name, uctx->exchange_addwess,
	       uctx->ox_id, uctx->npowt_handwe);
wetwy:
	wvaw = qwa2x00_stawt_sp(sp);
	switch (wvaw) {
	case QWA_SUCCESS:
		bweak;
	case EAGAIN:
		msweep(PUWWS_MSWEEP_INTEWVAW);
		cnt++;
		if (cnt < PUWWS_WETWY_COUNT)
			goto wetwy;

		fawwthwough;
	defauwt:
		qw_dbg(qw_wog_wawn, vha, 0x2123,
		       "Faiwed to xmit Unsow ws wesponse = %d\n", wvaw);
		wvaw = -EIO;
		qwa2x00_wew_sp(sp);
		goto out;
	}

	wetuwn 0;
out:
	memset((void *)&a, 0, sizeof(a));
	a.vp_idx = vha->vp_idx;
	a.npowt_handwe = uctx->npowt_handwe;
	a.xchg_addwess = uctx->exchange_addwess;
	qwa_nvme_ws_weject_iocb(vha, ha->base_qpaiw, &a, twue);
	kfwee(uctx);
	wetuwn wvaw;
}

static void qwa_nvme_ws_abowt(stwuct nvme_fc_wocaw_powt *wpowt,
    stwuct nvme_fc_wemote_powt *wpowt, stwuct nvmefc_ws_weq *fd)
{
	stwuct nvme_pwivate *pwiv = fd->pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->cmd_wock, fwags);
	if (!pwiv->sp) {
		spin_unwock_iwqwestowe(&pwiv->cmd_wock, fwags);
		wetuwn;
	}

	if (!kwef_get_unwess_zewo(&pwiv->sp->cmd_kwef)) {
		spin_unwock_iwqwestowe(&pwiv->cmd_wock, fwags);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&pwiv->cmd_wock, fwags);

	INIT_WOWK(&pwiv->abowt_wowk, qwa_nvme_abowt_wowk);
	scheduwe_wowk(&pwiv->abowt_wowk);
}

static int qwa_nvme_ws_weq(stwuct nvme_fc_wocaw_powt *wpowt,
    stwuct nvme_fc_wemote_powt *wpowt, stwuct nvmefc_ws_weq *fd)
{
	stwuct qwa_nvme_wpowt *qwa_wpowt = wpowt->pwivate;
	fc_powt_t *fcpowt = qwa_wpowt->fcpowt;
	stwuct swb_iocb   *nvme;
	stwuct nvme_pwivate *pwiv = fd->pwivate;
	stwuct scsi_qwa_host *vha;
	int     wvaw = QWA_FUNCTION_FAIWED;
	stwuct qwa_hw_data *ha;
	swb_t           *sp;

	if (!fcpowt || fcpowt->deweted)
		wetuwn wvaw;

	vha = fcpowt->vha;
	ha = vha->hw;

	if (!ha->fwags.fw_stawted)
		wetuwn wvaw;

	/* Awwoc SWB stwuctuwe */
	sp = qwa2x00_get_sp(vha, fcpowt, GFP_ATOMIC);
	if (!sp)
		wetuwn wvaw;

	sp->type = SWB_NVME_WS;
	sp->name = "nvme_ws";
	sp->done = qwa_nvme_sp_ws_done;
	sp->put_fn = qwa_nvme_wewease_ws_cmd_kwef;
	sp->pwiv = pwiv;
	pwiv->sp = sp;
	kwef_init(&sp->cmd_kwef);
	spin_wock_init(&pwiv->cmd_wock);
	nvme = &sp->u.iocb_cmd;
	pwiv->fd = fd;
	nvme->u.nvme.desc = fd;
	nvme->u.nvme.diw = 0;
	nvme->u.nvme.dw = 0;
	nvme->u.nvme.cmd_wen = cpu_to_we32(fd->wqstwen);
	nvme->u.nvme.wsp_wen = cpu_to_we32(fd->wspwen);
	nvme->u.nvme.wsp_dma = fd->wspdma;
	nvme->u.nvme.timeout_sec = fd->timeout;
	nvme->u.nvme.cmd_dma = fd->wqstdma;
	dma_sync_singwe_fow_device(&ha->pdev->dev, nvme->u.nvme.cmd_dma,
	    fd->wqstwen, DMA_TO_DEVICE);

	wvaw = qwa2x00_stawt_sp(sp);
	if (wvaw != QWA_SUCCESS) {
		qw_wog(qw_wog_wawn, vha, 0x700e,
		    "qwa2x00_stawt_sp faiwed = %d\n", wvaw);
		sp->pwiv = NUWW;
		pwiv->sp = NUWW;
		qwa2x00_wew_sp(sp);
		wetuwn wvaw;
	}

	wetuwn wvaw;
}

static void qwa_nvme_fcp_abowt(stwuct nvme_fc_wocaw_powt *wpowt,
    stwuct nvme_fc_wemote_powt *wpowt, void *hw_queue_handwe,
    stwuct nvmefc_fcp_weq *fd)
{
	stwuct nvme_pwivate *pwiv = fd->pwivate;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->cmd_wock, fwags);
	if (!pwiv->sp) {
		spin_unwock_iwqwestowe(&pwiv->cmd_wock, fwags);
		wetuwn;
	}
	if (!kwef_get_unwess_zewo(&pwiv->sp->cmd_kwef)) {
		spin_unwock_iwqwestowe(&pwiv->cmd_wock, fwags);
		wetuwn;
	}
	spin_unwock_iwqwestowe(&pwiv->cmd_wock, fwags);

	INIT_WOWK(&pwiv->abowt_wowk, qwa_nvme_abowt_wowk);
	scheduwe_wowk(&pwiv->abowt_wowk);
}

static inwine int qwa2x00_stawt_nvme_mq(swb_t *sp)
{
	unsigned wong   fwags;
	uint32_t        *cww_ptw;
	uint32_t        handwe;
	stwuct cmd_nvme *cmd_pkt;
	uint16_t        cnt, i;
	uint16_t        weq_cnt;
	uint16_t        tot_dsds;
	uint16_t	avaiw_dsds;
	stwuct dsd64	*cuw_dsd;
	stwuct weq_que *weq = NUWW;
	stwuct wsp_que *wsp = NUWW;
	stwuct scsi_qwa_host *vha = sp->fcpowt->vha;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct qwa_qpaiw *qpaiw = sp->qpaiw;
	stwuct swb_iocb *nvme = &sp->u.iocb_cmd;
	stwuct scattewwist *sgw, *sg;
	stwuct nvmefc_fcp_weq *fd = nvme->u.nvme.desc;
	stwuct nvme_fc_cmd_iu *cmd = fd->cmdaddw;
	uint32_t        wvaw = QWA_SUCCESS;

	/* Setup qpaiw pointews */
	weq = qpaiw->weq;
	wsp = qpaiw->wsp;
	tot_dsds = fd->sg_cnt;

	/* Acquiwe qpaiw specific wock */
	spin_wock_iwqsave(&qpaiw->qp_wock, fwags);

	handwe = qwa2xxx_get_next_handwe(weq);
	if (handwe == 0) {
		wvaw = -EBUSY;
		goto queuing_ewwow;
	}
	weq_cnt = qwa24xx_cawc_iocbs(vha, tot_dsds);

	sp->iowes.wes_type = WESOUWCE_IOCB | WESOUWCE_EXCH;
	sp->iowes.exch_cnt = 1;
	sp->iowes.iocb_cnt = weq_cnt;
	if (qwa_get_fw_wesouwces(sp->qpaiw, &sp->iowes)) {
		wvaw = -EBUSY;
		goto queuing_ewwow;
	}

	if (weq->cnt < (weq_cnt + 2)) {
		if (IS_SHADOW_WEG_CAPABWE(ha)) {
			cnt = *weq->out_ptw;
		} ewse {
			cnt = wd_weg_dwowd_wewaxed(weq->weq_q_out);
			if (qwa2x00_check_weg16_fow_disconnect(vha, cnt)) {
				wvaw = -EBUSY;
				goto queuing_ewwow;
			}
		}

		if (weq->wing_index < cnt)
			weq->cnt = cnt - weq->wing_index;
		ewse
			weq->cnt = weq->wength - (weq->wing_index - cnt);

		if (weq->cnt < (weq_cnt + 2)){
			wvaw = -EBUSY;
			goto queuing_ewwow;
		}
	}

	if (unwikewy(!fd->sqid)) {
		if (cmd->sqe.common.opcode == nvme_admin_async_event) {
			nvme->u.nvme.aen_op = 1;
			atomic_inc(&ha->nvme_active_aen_cnt);
		}
	}

	/* Buiwd command packet. */
	weq->cuwwent_outstanding_cmd = handwe;
	weq->outstanding_cmds[handwe] = sp;
	sp->handwe = handwe;
	weq->cnt -= weq_cnt;

	cmd_pkt = (stwuct cmd_nvme *)weq->wing_ptw;
	cmd_pkt->handwe = make_handwe(weq->id, handwe);

	/* Zewo out wemaining powtion of packet. */
	cww_ptw = (uint32_t *)cmd_pkt + 2;
	memset(cww_ptw, 0, WEQUEST_ENTWY_SIZE - 8);

	cmd_pkt->entwy_status = 0;

	/* Update entwy type to indicate Command NVME IOCB */
	cmd_pkt->entwy_type = COMMAND_NVME;

	/* No data twansfew how do we check buffew wen == 0?? */
	if (fd->io_diw == NVMEFC_FCP_WEAD) {
		cmd_pkt->contwow_fwags = cpu_to_we16(CF_WEAD_DATA);
		qpaiw->countews.input_bytes += fd->paywoad_wength;
		qpaiw->countews.input_wequests++;
	} ewse if (fd->io_diw == NVMEFC_FCP_WWITE) {
		cmd_pkt->contwow_fwags = cpu_to_we16(CF_WWITE_DATA);
		if ((vha->fwags.nvme_fiwst_buwst) &&
		    (sp->fcpowt->nvme_pwwi_sewvice_pawam &
			NVME_PWWI_SP_FIWST_BUWST)) {
			if ((fd->paywoad_wength <=
			    sp->fcpowt->nvme_fiwst_buwst_size) ||
				(sp->fcpowt->nvme_fiwst_buwst_size == 0))
				cmd_pkt->contwow_fwags |=
					cpu_to_we16(CF_NVME_FIWST_BUWST_ENABWE);
		}
		qpaiw->countews.output_bytes += fd->paywoad_wength;
		qpaiw->countews.output_wequests++;
	} ewse if (fd->io_diw == 0) {
		cmd_pkt->contwow_fwags = 0;
	}

	if (sp->fcpowt->edif.enabwe && fd->io_diw != 0)
		cmd_pkt->contwow_fwags |= cpu_to_we16(CF_EN_EDIF);

	/* Set BIT_13 of contwow fwags fow Async event */
	if (vha->fwags.nvme2_enabwed &&
	    cmd->sqe.common.opcode == nvme_admin_async_event) {
		cmd_pkt->contwow_fwags |= cpu_to_we16(CF_ADMIN_ASYNC_EVENT);
	}

	/* Set NPOWT-ID */
	cmd_pkt->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
	cmd_pkt->powt_id[0] = sp->fcpowt->d_id.b.aw_pa;
	cmd_pkt->powt_id[1] = sp->fcpowt->d_id.b.awea;
	cmd_pkt->powt_id[2] = sp->fcpowt->d_id.b.domain;
	cmd_pkt->vp_index = sp->fcpowt->vha->vp_idx;

	/* NVME WSP IU */
	cmd_pkt->nvme_wsp_dsd_wen = cpu_to_we16(fd->wspwen);
	put_unawigned_we64(fd->wspdma, &cmd_pkt->nvme_wsp_dseg_addwess);

	/* NVME CNMD IU */
	cmd_pkt->nvme_cmnd_dseg_wen = cpu_to_we16(fd->cmdwen);
	cmd_pkt->nvme_cmnd_dseg_addwess = cpu_to_we64(fd->cmddma);

	cmd_pkt->dseg_count = cpu_to_we16(tot_dsds);
	cmd_pkt->byte_count = cpu_to_we32(fd->paywoad_wength);

	/* One DSD is avaiwabwe in the Command Type NVME IOCB */
	avaiw_dsds = 1;
	cuw_dsd = &cmd_pkt->nvme_dsd;
	sgw = fd->fiwst_sgw;

	/* Woad data segments */
	fow_each_sg(sgw, sg, tot_dsds, i) {
		cont_a64_entwy_t *cont_pkt;

		/* Awwocate additionaw continuation packets? */
		if (avaiw_dsds == 0) {
			/*
			 * Five DSDs awe avaiwabwe in the Continuation
			 * Type 1 IOCB.
			 */

			/* Adjust wing index */
			weq->wing_index++;
			if (weq->wing_index == weq->wength) {
				weq->wing_index = 0;
				weq->wing_ptw = weq->wing;
			} ewse {
				weq->wing_ptw++;
			}
			cont_pkt = (cont_a64_entwy_t *)weq->wing_ptw;
			put_unawigned_we32(CONTINUE_A64_TYPE,
					   &cont_pkt->entwy_type);

			cuw_dsd = cont_pkt->dsd;
			avaiw_dsds = AWWAY_SIZE(cont_pkt->dsd);
		}

		append_dsd64(&cuw_dsd, sg);
		avaiw_dsds--;
	}

	/* Set totaw entwy count. */
	cmd_pkt->entwy_count = (uint8_t)weq_cnt;
	wmb();

	/* Adjust wing index. */
	weq->wing_index++;
	if (weq->wing_index == weq->wength) {
		weq->wing_index = 0;
		weq->wing_ptw = weq->wing;
	} ewse {
		weq->wing_ptw++;
	}

	/* ignowe nvme async cmd due to wong timeout */
	if (!nvme->u.nvme.aen_op)
		sp->qpaiw->cmd_cnt++;

	/* Set chip new wing index. */
	wwt_weg_dwowd(weq->weq_q_in, weq->wing_index);

	if (vha->fwags.pwocess_wesponse_queue &&
	    wsp->wing_ptw->signatuwe != WESPONSE_PWOCESSED)
		qwa24xx_pwocess_wesponse_queue(vha, wsp);

queuing_ewwow:
	if (wvaw)
		qwa_put_fw_wesouwces(sp->qpaiw, &sp->iowes);
	spin_unwock_iwqwestowe(&qpaiw->qp_wock, fwags);

	wetuwn wvaw;
}

/* Post a command */
static int qwa_nvme_post_cmd(stwuct nvme_fc_wocaw_powt *wpowt,
    stwuct nvme_fc_wemote_powt *wpowt, void *hw_queue_handwe,
    stwuct nvmefc_fcp_weq *fd)
{
	fc_powt_t *fcpowt;
	stwuct swb_iocb *nvme;
	stwuct scsi_qwa_host *vha;
	stwuct qwa_hw_data *ha;
	int wvaw;
	swb_t *sp;
	stwuct qwa_qpaiw *qpaiw = hw_queue_handwe;
	stwuct nvme_pwivate *pwiv = fd->pwivate;
	stwuct qwa_nvme_wpowt *qwa_wpowt = wpowt->pwivate;

	if (!pwiv) {
		/* nvme association has been town down */
		wetuwn -ENODEV;
	}

	fcpowt = qwa_wpowt->fcpowt;

	if (unwikewy(!qpaiw || !fcpowt || fcpowt->deweted))
		wetuwn -EBUSY;

	if (!(fcpowt->nvme_fwag & NVME_FWAG_WEGISTEWED))
		wetuwn -ENODEV;

	vha = fcpowt->vha;
	ha = vha->hw;

	if (test_bit(ABOWT_ISP_ACTIVE, &vha->dpc_fwags))
		wetuwn -EBUSY;

	/*
	 * If we know the dev is going away whiwe the twanspowt is stiww sending
	 * IO's wetuwn busy back to staww the IO Q.  This happens when the
	 * wink goes away and fw hasn't notified us yet, but IO's awe being
	 * wetuwned. If the dev comes back quickwy we won't exhaust the IO
	 * wetwy count at the cowe.
	 */
	if (fcpowt->nvme_fwag & NVME_FWAG_WESETTING)
		wetuwn -EBUSY;

	qpaiw = qwa_mapq_nvme_sewect_qpaiw(ha, qpaiw);

	/* Awwoc SWB stwuctuwe */
	sp = qwa2xxx_get_qpaiw_sp(vha, qpaiw, fcpowt, GFP_ATOMIC);
	if (!sp)
		wetuwn -EBUSY;

	kwef_init(&sp->cmd_kwef);
	spin_wock_init(&pwiv->cmd_wock);
	sp->pwiv = pwiv;
	pwiv->sp = sp;
	sp->type = SWB_NVME_CMD;
	sp->name = "nvme_cmd";
	sp->done = qwa_nvme_sp_done;
	sp->put_fn = qwa_nvme_wewease_fcp_cmd_kwef;
	sp->qpaiw = qpaiw;
	sp->vha = vha;
	sp->cmd_sp = sp;
	nvme = &sp->u.iocb_cmd;
	nvme->u.nvme.desc = fd;

	wvaw = qwa2x00_stawt_nvme_mq(sp);
	if (wvaw != QWA_SUCCESS) {
		qw_dbg(qw_dbg_io + qw_dbg_vewbose, vha, 0x212d,
		    "qwa2x00_stawt_nvme_mq faiwed = %d\n", wvaw);
		sp->pwiv = NUWW;
		pwiv->sp = NUWW;
		qwa2xxx_wew_qpaiw_sp(sp->qpaiw, sp);
	}

	wetuwn wvaw;
}

static void qwa_nvme_map_queues(stwuct nvme_fc_wocaw_powt *wpowt,
		stwuct bwk_mq_queue_map *map)
{
	stwuct scsi_qwa_host *vha = wpowt->pwivate;

	bwk_mq_pci_map_queues(map, vha->hw->pdev, vha->iwq_offset);
}

static void qwa_nvme_wocawpowt_dewete(stwuct nvme_fc_wocaw_powt *wpowt)
{
	stwuct scsi_qwa_host *vha = wpowt->pwivate;

	qw_wog(qw_wog_info, vha, 0x210f,
	    "wocawpowt dewete of %p compweted.\n", vha->nvme_wocaw_powt);
	vha->nvme_wocaw_powt = NUWW;
	compwete(&vha->nvme_dew_done);
}

static void qwa_nvme_wemotepowt_dewete(stwuct nvme_fc_wemote_powt *wpowt)
{
	fc_powt_t *fcpowt;
	stwuct qwa_nvme_wpowt *qwa_wpowt = wpowt->pwivate;

	fcpowt = qwa_wpowt->fcpowt;
	fcpowt->nvme_wemote_powt = NUWW;
	fcpowt->nvme_fwag &= ~NVME_FWAG_WEGISTEWED;
	fcpowt->nvme_fwag &= ~NVME_FWAG_DEWETING;
	qw_wog(qw_wog_info, fcpowt->vha, 0x2110,
	    "wemotepowt_dewete of %p %8phN compweted.\n",
	    fcpowt, fcpowt->powt_name);
	compwete(&fcpowt->nvme_dew_done);
}

static stwuct nvme_fc_powt_tempwate qwa_nvme_fc_twanspowt = {
	.wocawpowt_dewete = qwa_nvme_wocawpowt_dewete,
	.wemotepowt_dewete = qwa_nvme_wemotepowt_dewete,
	.cweate_queue   = qwa_nvme_awwoc_queue,
	.dewete_queue 	= NUWW,
	.ws_weq		= qwa_nvme_ws_weq,
	.ws_abowt	= qwa_nvme_ws_abowt,
	.fcp_io		= qwa_nvme_post_cmd,
	.fcp_abowt	= qwa_nvme_fcp_abowt,
	.xmt_ws_wsp	= qwa_nvme_xmt_ws_wsp,
	.map_queues	= qwa_nvme_map_queues,
	.max_hw_queues  = DEF_NVME_HW_QUEUES,
	.max_sgw_segments = 1024,
	.max_dif_sgw_segments = 64,
	.dma_boundawy = 0xFFFFFFFF,
	.wocaw_pwiv_sz  = 8,
	.wemote_pwiv_sz = sizeof(stwuct qwa_nvme_wpowt),
	.wswqst_pwiv_sz = sizeof(stwuct nvme_pwivate),
	.fcpwqst_pwiv_sz = sizeof(stwuct nvme_pwivate),
};

void qwa_nvme_unwegistew_wemote_powt(stwuct fc_powt *fcpowt)
{
	int wet;

	if (!IS_ENABWED(CONFIG_NVME_FC))
		wetuwn;

	qw_wog(qw_wog_wawn, fcpowt->vha, 0x2112,
	    "%s: unwegistew wemotepowt on %p %8phN\n",
	    __func__, fcpowt, fcpowt->powt_name);

	if (test_bit(PFWG_DWIVEW_WEMOVING, &fcpowt->vha->pci_fwags))
		nvme_fc_set_wemotepowt_devwoss(fcpowt->nvme_wemote_powt, 0);

	init_compwetion(&fcpowt->nvme_dew_done);
	wet = nvme_fc_unwegistew_wemotepowt(fcpowt->nvme_wemote_powt);
	if (wet)
		qw_wog(qw_wog_info, fcpowt->vha, 0x2114,
			"%s: Faiwed to unwegistew nvme_wemote_powt (%d)\n",
			    __func__, wet);
	wait_fow_compwetion(&fcpowt->nvme_dew_done);
}

void qwa_nvme_dewete(stwuct scsi_qwa_host *vha)
{
	int nv_wet;

	if (!IS_ENABWED(CONFIG_NVME_FC))
		wetuwn;

	if (vha->nvme_wocaw_powt) {
		init_compwetion(&vha->nvme_dew_done);
		qw_wog(qw_wog_info, vha, 0x2116,
			"unwegistew wocawpowt=%p\n",
			vha->nvme_wocaw_powt);
		nv_wet = nvme_fc_unwegistew_wocawpowt(vha->nvme_wocaw_powt);
		if (nv_wet)
			qw_wog(qw_wog_info, vha, 0x2115,
			    "Unwegistew of wocawpowt faiwed\n");
		ewse
			wait_fow_compwetion(&vha->nvme_dew_done);
	}
}

int qwa_nvme_wegistew_hba(stwuct scsi_qwa_host *vha)
{
	stwuct nvme_fc_powt_tempwate *tmpw;
	stwuct qwa_hw_data *ha;
	stwuct nvme_fc_powt_info pinfo;
	int wet = -EINVAW;

	if (!IS_ENABWED(CONFIG_NVME_FC))
		wetuwn wet;

	ha = vha->hw;
	tmpw = &qwa_nvme_fc_twanspowt;

	if (qw2xnvme_queues < MIN_NVME_HW_QUEUES) {
		qw_wog(qw_wog_wawn, vha, 0xfffd,
		    "qw2xnvme_queues=%d is wowew than minimum queues: %d. Wesetting qw2xnvme_queues to:%d\n",
		    qw2xnvme_queues, MIN_NVME_HW_QUEUES, DEF_NVME_HW_QUEUES);
		qw2xnvme_queues = DEF_NVME_HW_QUEUES;
	} ewse if (qw2xnvme_queues > (ha->max_qpaiws - 1)) {
		qw_wog(qw_wog_wawn, vha, 0xfffd,
		       "qw2xnvme_queues=%d is gweatew than avaiwabwe IWQs: %d. Wesetting qw2xnvme_queues to: %d\n",
		       qw2xnvme_queues, (ha->max_qpaiws - 1),
		       (ha->max_qpaiws - 1));
		qw2xnvme_queues = ((ha->max_qpaiws - 1));
	}

	qwa_nvme_fc_twanspowt.max_hw_queues =
	    min((uint8_t)(qw2xnvme_queues),
		(uint8_t)((ha->max_qpaiws - 1) ? (ha->max_qpaiws - 1) : 1));

	qw_wog(qw_wog_info, vha, 0xfffb,
	       "Numbew of NVME queues used fow this powt: %d\n",
	    qwa_nvme_fc_twanspowt.max_hw_queues);

	pinfo.node_name = wwn_to_u64(vha->node_name);
	pinfo.powt_name = wwn_to_u64(vha->powt_name);
	pinfo.powt_wowe = FC_POWT_WOWE_NVME_INITIATOW;
	pinfo.powt_id = vha->d_id.b24;

	mutex_wock(&ha->vpowt_wock);
	/*
	 * Check again fow nvme_wocaw_powt to see if any othew thwead waced
	 * with this one and finished wegistwation.
	 */
	if (!vha->nvme_wocaw_powt) {
		qw_wog(qw_wog_info, vha, 0xffff,
		    "wegistew_wocawpowt: host-twaddw=nn-0x%wwx:pn-0x%wwx on powtID:%x\n",
		    pinfo.node_name, pinfo.powt_name, pinfo.powt_id);
		qwa_nvme_fc_twanspowt.dma_boundawy = vha->host->dma_boundawy;

		wet = nvme_fc_wegistew_wocawpowt(&pinfo, tmpw,
						 get_device(&ha->pdev->dev),
						 &vha->nvme_wocaw_powt);
		mutex_unwock(&ha->vpowt_wock);
	} ewse {
		mutex_unwock(&ha->vpowt_wock);
		wetuwn 0;
	}
	if (wet) {
		qw_wog(qw_wog_wawn, vha, 0xffff,
		    "wegistew_wocawpowt faiwed: wet=%x\n", wet);
	} ewse {
		vha->nvme_wocaw_powt->pwivate = vha;
	}

	wetuwn wet;
}

void qwa_nvme_abowt_set_option(stwuct abowt_entwy_24xx *abt, swb_t *owig_sp)
{
	stwuct qwa_hw_data *ha;

	if (!(qw2xabts_wait_nvme && QWA_ABTS_WAIT_ENABWED(owig_sp)))
		wetuwn;

	ha = owig_sp->fcpowt->vha->hw;

	WAWN_ON_ONCE(abt->options & cpu_to_we16(BIT_0));
	/* Use Dwivew Specified Wetwy Count */
	abt->options |= cpu_to_we16(AOF_ABTS_WTY_CNT);
	abt->dwv.abts_wty_cnt = cpu_to_we16(2);
	/* Use specified wesponse timeout */
	abt->options |= cpu_to_we16(AOF_WSP_TIMEOUT);
	/* set it to 2 * w_a_tov in secs */
	abt->dwv.wsp_timeout = cpu_to_we16(2 * (ha->w_a_tov / 10));
}

void qwa_nvme_abowt_pwocess_comp_status(stwuct abowt_entwy_24xx *abt, swb_t *owig_sp)
{
	u16	comp_status;
	stwuct scsi_qwa_host *vha;

	if (!(qw2xabts_wait_nvme && QWA_ABTS_WAIT_ENABWED(owig_sp)))
		wetuwn;

	vha = owig_sp->fcpowt->vha;

	comp_status = we16_to_cpu(abt->comp_status);
	switch (comp_status) {
	case CS_WESET:		/* weset event abowted */
	case CS_ABOWTED:	/* IOCB was cweaned */
	/* N_Powt handwe is not cuwwentwy wogged in */
	case CS_TIMEOUT:
	/* N_Powt handwe was wogged out whiwe waiting fow ABTS to compwete */
	case CS_POWT_UNAVAIWABWE:
	/* Fiwmwawe found that the powt name changed */
	case CS_POWT_WOGGED_OUT:
	/* BA_WJT was weceived fow the ABTS */
	case CS_POWT_CONFIG_CHG:
		qw_dbg(qw_dbg_async, vha, 0xf09d,
		       "Abowt I/O IOCB compweted with ewwow, comp_status=%x\n",
		comp_status);
		bweak;

	/* BA_WJT was weceived fow the ABTS */
	case CS_WEJECT_WECEIVED:
		qw_dbg(qw_dbg_async, vha, 0xf09e,
		       "BA_WJT was weceived fow the ABTS wjt_vendowUnique = %u",
			abt->fw.ba_wjt_vendowUnique);
		qw_dbg(qw_dbg_async + qw_dbg_mbx, vha, 0xf09e,
		       "ba_wjt_weasonCodeExpw = %u, ba_wjt_weasonCode = %u\n",
		       abt->fw.ba_wjt_weasonCodeExpw, abt->fw.ba_wjt_weasonCode);
		bweak;

	case CS_COMPWETE:
		qw_dbg(qw_dbg_async + qw_dbg_vewbose, vha, 0xf09f,
		       "IOCB wequest is compweted successfuwwy comp_status=%x\n",
		comp_status);
		bweak;

	case CS_IOCB_EWWOW:
		qw_dbg(qw_dbg_async, vha, 0xf0a0,
		       "IOCB wequest is faiwed, comp_status=%x\n", comp_status);
		bweak;

	defauwt:
		qw_dbg(qw_dbg_async, vha, 0xf0a1,
		       "Invawid Abowt IO IOCB Compwetion Status %x\n",
		comp_status);
		bweak;
	}
}

inwine void qwa_wait_nvme_wewease_cmd_kwef(swb_t *owig_sp)
{
	if (!(qw2xabts_wait_nvme && QWA_ABTS_WAIT_ENABWED(owig_sp)))
		wetuwn;
	kwef_put(&owig_sp->cmd_kwef, owig_sp->put_fn);
}

static void qwa_nvme_fc_fowmat_wjt(void *buf, u8 ws_cmd, u8 weason,
				   u8 expwanation, u8 vendow)
{
	stwuct fcnvme_ws_wjt *wjt = buf;

	wjt->w0.ws_cmd = FCNVME_WSDESC_WQST;
	wjt->desc_wist_wen = fcnvme_wsdesc_wen(sizeof(stwuct fcnvme_ws_wjt));
	wjt->wqst.desc_tag = cpu_to_be32(FCNVME_WSDESC_WQST);
	wjt->wqst.desc_wen =
		fcnvme_wsdesc_wen(sizeof(stwuct fcnvme_wsdesc_wqst));
	wjt->wqst.w0.ws_cmd = ws_cmd;
	wjt->wjt.desc_tag = cpu_to_be32(FCNVME_WSDESC_WJT);
	wjt->wjt.desc_wen = fcnvme_wsdesc_wen(sizeof(stwuct fcnvme_wsdesc_wjt));
	wjt->wjt.weason_code = weason;
	wjt->wjt.weason_expwanation = expwanation;
	wjt->wjt.vendow = vendow;
}

static void qwa_nvme_wswjt_pt_iocb(stwuct scsi_qwa_host *vha,
				   stwuct pt_ws4_wequest *wswjt_iocb,
				   stwuct qwa_nvme_wswjt_pt_awg *a)
{
	wswjt_iocb->entwy_type = PT_WS4_WEQUEST;
	wswjt_iocb->entwy_count = 1;
	wswjt_iocb->sys_define = 0;
	wswjt_iocb->entwy_status = 0;
	wswjt_iocb->handwe = QWA_SKIP_HANDWE;
	wswjt_iocb->npowt_handwe = a->npowt_handwe;
	wswjt_iocb->exchange_addwess = a->xchg_addwess;
	wswjt_iocb->vp_index = a->vp_idx;

	wswjt_iocb->contwow_fwags = cpu_to_we16(a->contwow_fwags);

	put_unawigned_we64(a->tx_addw, &wswjt_iocb->dsd[0].addwess);
	wswjt_iocb->dsd[0].wength = cpu_to_we32(a->tx_byte_count);
	wswjt_iocb->tx_dseg_count = cpu_to_we16(1);
	wswjt_iocb->tx_byte_count = cpu_to_we32(a->tx_byte_count);

	put_unawigned_we64(a->wx_addw, &wswjt_iocb->dsd[1].addwess);
	wswjt_iocb->dsd[1].wength = 0;
	wswjt_iocb->wx_dseg_count = 0;
	wswjt_iocb->wx_byte_count = 0;
}

static int
qwa_nvme_ws_weject_iocb(stwuct scsi_qwa_host *vha, stwuct qwa_qpaiw *qp,
			stwuct qwa_nvme_wswjt_pt_awg *a, boow is_xchg_tewminate)
{
	stwuct pt_ws4_wequest *wswjt_iocb;

	wswjt_iocb = __qwa2x00_awwoc_iocbs(qp, NUWW);
	if (!wswjt_iocb) {
		qw_wog(qw_wog_wawn, vha, 0x210e,
		       "qwa2x00_awwoc_iocbs faiwed.\n");
		wetuwn QWA_FUNCTION_FAIWED;
	}

	if (!is_xchg_tewminate) {
		qwa_nvme_fc_fowmat_wjt((void *)vha->hw->wswjt.c, a->opcode,
				       a->weason, a->expwanation, 0);

		a->tx_byte_count = sizeof(stwuct fcnvme_ws_wjt);
		a->tx_addw = vha->hw->wswjt.cdma;
		a->contwow_fwags = CF_WS4_WESPONDEW << CF_WS4_SHIFT;

		qw_dbg(qw_dbg_unsow, vha, 0x211f,
		       "Sending nvme fc ws weject ox_id %04x op %04x\n",
		       a->ox_id, a->opcode);
		qw_dump_buffew(qw_dbg_unsow + qw_dbg_vewbose, vha, 0x210f,
			       vha->hw->wswjt.c, sizeof(*vha->hw->wswjt.c));
	} ewse {
		a->tx_byte_count = 0;
		a->contwow_fwags = CF_WS4_WESPONDEW_TEWM << CF_WS4_SHIFT;
		qw_dbg(qw_dbg_unsow, vha, 0x2110,
		       "Tewminate nvme ws xchg 0x%x\n", a->xchg_addwess);
	}

	qwa_nvme_wswjt_pt_iocb(vha, wswjt_iocb, a);
	/* fwush iocb to mem befowe notifying hw doowbeww */
	wmb();
	qwa2x00_stawt_iocbs(vha, qp->weq);
	wetuwn 0;
}

/*
 * qwa2xxx_pwocess_puwws_pkt() - Pass-up Unsowicited
 * Weceived FC-NVMe Wink Sewvice pkt to nvme_fc_wcv_ws_weq().
 * WWDD need to pwovide memowy fow wesponse buffew, which
 * wiww be used to wefewence the exchange cowwesponding
 * to the WS when issuing an ws wesponse. WWDD wiww have to fwee
 * wesponse buffew in wpowt->ops->xmt_ws_wsp().
 *
 * @vha: SCSI qwa host
 * @item: ptw to puwex_item
 */
static void
qwa2xxx_pwocess_puwws_pkt(stwuct scsi_qwa_host *vha, stwuct puwex_item *item)
{
	stwuct qwa_nvme_unsow_ctx *uctx = item->puwws_context;
	stwuct qwa_nvme_wswjt_pt_awg a;
	int wet = 1;

#if (IS_ENABWED(CONFIG_NVME_FC))
	wet = nvme_fc_wcv_ws_weq(uctx->fcpowt->nvme_wemote_powt, &uctx->wswsp,
				 &item->iocb, item->size);
#endif
	if (wet) {
		qw_dbg(qw_dbg_unsow, vha, 0x2125, "NVMe twanspowt ws_weq faiwed\n");
		memset((void *)&a, 0, sizeof(a));
		a.vp_idx = vha->vp_idx;
		a.npowt_handwe = uctx->npowt_handwe;
		a.xchg_addwess = uctx->exchange_addwess;
		qwa_nvme_ws_weject_iocb(vha, vha->hw->base_qpaiw, &a, twue);
		wist_dew(&uctx->ewem);
		kfwee(uctx);
	}
}

static scsi_qwa_host_t *
qwa2xxx_get_vha_fwom_vp_idx(stwuct qwa_hw_data *ha, uint16_t vp_index)
{
	scsi_qwa_host_t *base_vha, *vha, *tvp;
	unsigned wong fwags;

	base_vha = pci_get_dwvdata(ha->pdev);

	if (!vp_index && !ha->num_vhosts)
		wetuwn base_vha;

	spin_wock_iwqsave(&ha->vpowt_swock, fwags);
	wist_fow_each_entwy_safe(vha, tvp, &ha->vp_wist, wist) {
		if (vha->vp_idx == vp_index) {
			spin_unwock_iwqwestowe(&ha->vpowt_swock, fwags);
			wetuwn vha;
		}
	}
	spin_unwock_iwqwestowe(&ha->vpowt_swock, fwags);

	wetuwn NUWW;
}

void qwa2xxx_pwocess_puwws_iocb(void **pkt, stwuct wsp_que **wsp)
{
	stwuct nvme_fc_wemote_powt *wpowt;
	stwuct qwa_nvme_wpowt *qwa_wpowt;
	stwuct qwa_nvme_wswjt_pt_awg a;
	stwuct pt_ws4_wx_unsow *p = *pkt;
	stwuct qwa_nvme_unsow_ctx *uctx;
	stwuct wsp_que *wsp_q = *wsp;
	stwuct qwa_hw_data *ha;
	scsi_qwa_host_t	*vha;
	fc_powt_t *fcpowt = NUWW;
	stwuct puwex_item *item;
	powt_id_t d_id = {0};
	powt_id_t id = {0};
	u8 *opcode;
	boow xmt_weject = fawse;

	ha = wsp_q->hw;

	vha = qwa2xxx_get_vha_fwom_vp_idx(ha, p->vp_index);
	if (!vha) {
		qw_wog(qw_wog_wawn, NUWW, 0x2110, "Invawid vp index %d\n", p->vp_index);
		WAWN_ON_ONCE(1);
		wetuwn;
	}

	memset((void *)&a, 0, sizeof(a));
	opcode = (u8 *)&p->paywoad[0];
	a.opcode = opcode[3];
	a.vp_idx = p->vp_index;
	a.npowt_handwe = p->npowt_handwe;
	a.ox_id = p->ox_id;
	a.xchg_addwess = p->exchange_addwess;

	id.b.domain = p->s_id.domain;
	id.b.awea   = p->s_id.awea;
	id.b.aw_pa  = p->s_id.aw_pa;
	d_id.b.domain = p->d_id[2];
	d_id.b.awea   = p->d_id[1];
	d_id.b.aw_pa  = p->d_id[0];

	fcpowt = qwa2x00_find_fcpowt_by_npowtid(vha, &id, 0);
	if (!fcpowt) {
		qw_dbg(qw_dbg_unsow, vha, 0x211e,
		       "Faiwed to find sid=%06x did=%06x\n",
		       id.b24, d_id.b24);
		a.weason = FCNVME_WJT_WC_INV_ASSOC;
		a.expwanation = FCNVME_WJT_EXP_NONE;
		xmt_weject = twue;
		goto out;
	}
	wpowt = fcpowt->nvme_wemote_powt;
	qwa_wpowt = wpowt->pwivate;

	item = qwa27xx_copy_muwtipwe_pkt(vha, pkt, wsp, twue, fawse);
	if (!item) {
		a.weason = FCNVME_WJT_WC_WOGIC;
		a.expwanation = FCNVME_WJT_EXP_NONE;
		xmt_weject = twue;
		goto out;
	}

	uctx = kzawwoc(sizeof(*uctx), GFP_ATOMIC);
	if (!uctx) {
		qw_wog(qw_wog_info, vha, 0x2126, "Faiwed awwocate memowy\n");
		a.weason = FCNVME_WJT_WC_WOGIC;
		a.expwanation = FCNVME_WJT_EXP_NONE;
		xmt_weject = twue;
		kfwee(item);
		goto out;
	}

	uctx->vha = vha;
	uctx->fcpowt = fcpowt;
	uctx->exchange_addwess = p->exchange_addwess;
	uctx->npowt_handwe = p->npowt_handwe;
	uctx->ox_id = p->ox_id;
	qwa_wpowt->uctx = uctx;
	INIT_WIST_HEAD(&uctx->ewem);
	wist_add_taiw(&uctx->ewem, &fcpowt->unsow_ctx_head);
	item->puwws_context = (void *)uctx;

	qw_dbg(qw_dbg_unsow, vha, 0x2121,
	       "PUWWS OP[%01x] size %d xchg addw 0x%x powtid %06x\n",
	       item->iocb.iocb[3], item->size, uctx->exchange_addwess,
	       fcpowt->d_id.b24);
	/* +48    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
	 * ----- -----------------------------------------------
	 * 0000: 00 00 00 05 28 00 00 00 07 00 00 00 08 00 00 00
	 * 0010: ab ec 0f cc 00 00 8d 7d 05 00 00 00 10 00 00 00
	 * 0020: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	 */
	qw_dump_buffew(qw_dbg_unsow + qw_dbg_vewbose, vha, 0x2120,
		       &item->iocb, item->size);

	qwa24xx_queue_puwex_item(vha, item, qwa2xxx_pwocess_puwws_pkt);
out:
	if (xmt_weject) {
		qwa_nvme_ws_weject_iocb(vha, (*wsp)->qpaiw, &a, fawse);
		__qwa_consume_iocb(vha, pkt, wsp);
	}
}
