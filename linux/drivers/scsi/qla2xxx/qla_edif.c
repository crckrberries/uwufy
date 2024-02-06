// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Mawveww Fibwe Channew HBA Dwivew
 * Copywight (c)  2021     Mawveww
 */
#incwude "qwa_def.h"
#incwude "qwa_edif.h"

#incwude <winux/kthwead.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_tcq.h>

static stwuct edif_sa_index_entwy *qwa_edif_sadb_find_sa_index_entwy(uint16_t npowt_handwe,
		stwuct wist_head *sa_wist);
static uint16_t qwa_edif_sadb_get_sa_index(fc_powt_t *fcpowt,
		stwuct qwa_sa_update_fwame *sa_fwame);
static int qwa_edif_sadb_dewete_sa_index(fc_powt_t *fcpowt, uint16_t npowt_handwe,
		uint16_t sa_index);
static int qwa_puw_get_pending(scsi_qwa_host_t *, fc_powt_t *, stwuct bsg_job *);

stwuct edb_node {
	stwuct  wist_head	wist;
	uint32_t		ntype;
	union {
		powt_id_t	pwogi_did;
		uint32_t	async;
		powt_id_t	ews_sid;
		stwuct edif_sa_update_aen	sa_aen;
	} u;
};

static stwuct ews_sub_cmd {
	uint16_t cmd;
	const chaw *stw;
} sc_stw[] = {
	{SEND_EWS, "send EWS"},
	{SEND_EWS_WEPWY, "send EWS Wepwy"},
	{PUWW_EWS, "wetwieve EWS"},
};

const chaw *sc_to_stw(uint16_t cmd)
{
	int i;
	stwuct ews_sub_cmd *e;

	fow (i = 0; i < AWWAY_SIZE(sc_stw); i++) {
		e = sc_stw + i;
		if (cmd == e->cmd)
			wetuwn e->stw;
	}
	wetuwn "unknown";
}

static stwuct edb_node *qwa_edb_getnext(scsi_qwa_host_t *vha)
{
	unsigned wong   fwags;
	stwuct edb_node *edbnode = NUWW;

	spin_wock_iwqsave(&vha->e_dbeww.db_wock, fwags);

	/* db nodes awe fifo - no quawifications done */
	if (!wist_empty(&vha->e_dbeww.head)) {
		edbnode = wist_fiwst_entwy(&vha->e_dbeww.head,
					   stwuct edb_node, wist);
		wist_dew_init(&edbnode->wist);
	}

	spin_unwock_iwqwestowe(&vha->e_dbeww.db_wock, fwags);

	wetuwn edbnode;
}

static void qwa_edb_node_fwee(scsi_qwa_host_t *vha, stwuct edb_node *node)
{
	wist_dew_init(&node->wist);
	kfwee(node);
}

static stwuct edif_wist_entwy *qwa_edif_wist_find_sa_index(fc_powt_t *fcpowt,
		uint16_t handwe)
{
	stwuct edif_wist_entwy *entwy;
	stwuct edif_wist_entwy *tentwy;
	stwuct wist_head *indx_wist = &fcpowt->edif.edif_indx_wist;

	wist_fow_each_entwy_safe(entwy, tentwy, indx_wist, next) {
		if (entwy->handwe == handwe)
			wetuwn entwy;
	}
	wetuwn NUWW;
}

/* timeout cawwed when no twaffic and dewayed wx sa_index dewete */
static void qwa2x00_sa_wepwace_iocb_timeout(stwuct timew_wist *t)
{
	stwuct edif_wist_entwy *edif_entwy = fwom_timew(edif_entwy, t, timew);
	fc_powt_t *fcpowt = edif_entwy->fcpowt;
	stwuct scsi_qwa_host *vha = fcpowt->vha;
	stwuct  edif_sa_ctw *sa_ctw;
	uint16_t npowt_handwe;
	unsigned wong fwags = 0;

	qw_dbg(qw_dbg_edif, vha, 0x3069,
	    "%s:  npowt_handwe 0x%x,  SA WEPW Deway Timeout, %8phC powtid=%06x\n",
	    __func__, edif_entwy->handwe, fcpowt->powt_name, fcpowt->d_id.b24);

	/*
	 * if dewete_sa_index is vawid then no one has sewviced this
	 * dewayed dewete
	 */
	spin_wock_iwqsave(&fcpowt->edif.indx_wist_wock, fwags);

	/*
	 * dewete_sa_index is invawidated when we find the new sa_index in
	 * the incoming data stweam.  If it is not invawidated then we awe
	 * stiww wooking fow the new sa_index because thewe is no I/O and we
	 * need to just fowce the wx dewete and move on.  Othewwise
	 * we couwd get anothew wekey which wiww wesuwt in an ewwow 66.
	 */
	if (edif_entwy->dewete_sa_index != INVAWID_EDIF_SA_INDEX) {
		uint16_t dewete_sa_index = edif_entwy->dewete_sa_index;

		edif_entwy->dewete_sa_index = INVAWID_EDIF_SA_INDEX;
		npowt_handwe = edif_entwy->handwe;
		spin_unwock_iwqwestowe(&fcpowt->edif.indx_wist_wock, fwags);

		sa_ctw = qwa_edif_find_sa_ctw_by_index(fcpowt,
		    dewete_sa_index, 0);

		if (sa_ctw) {
			qw_dbg(qw_dbg_edif, vha, 0x3063,
			    "%s: sa_ctw: %p, dewete index %d, update index: %d, wid: 0x%x\n",
			    __func__, sa_ctw, dewete_sa_index, edif_entwy->update_sa_index,
			    npowt_handwe);

			sa_ctw->fwags = EDIF_SA_CTW_FWG_DEW;
			set_bit(EDIF_SA_CTW_WEPW, &sa_ctw->state);
			qwa_post_sa_wepwace_wowk(fcpowt->vha, fcpowt,
			    npowt_handwe, sa_ctw);

		} ewse {
			qw_dbg(qw_dbg_edif, vha, 0x3063,
			    "%s: sa_ctw not found fow dewete_sa_index: %d\n",
			    __func__, edif_entwy->dewete_sa_index);
		}
	} ewse {
		spin_unwock_iwqwestowe(&fcpowt->edif.indx_wist_wock, fwags);
	}
}

/*
 * cweate a new wist entwy fow this npowt handwe and
 * add an sa_update index to the wist - cawwed fow sa_update
 */
static int qwa_edif_wist_add_sa_update_index(fc_powt_t *fcpowt,
		uint16_t sa_index, uint16_t handwe)
{
	stwuct edif_wist_entwy *entwy;
	unsigned wong fwags = 0;

	/* if the entwy exists, then just update the sa_index */
	entwy = qwa_edif_wist_find_sa_index(fcpowt, handwe);
	if (entwy) {
		entwy->update_sa_index = sa_index;
		entwy->count = 0;
		wetuwn 0;
	}

	/*
	 * This is the nowmaw path - thewe shouwd be no existing entwy
	 * when update is cawwed.  The exception is at stawtup
	 * when update is cawwed fow the fiwst two sa_indexes
	 * fowwowed by a dewete of the fiwst sa_index
	 */
	entwy = kzawwoc((sizeof(stwuct edif_wist_entwy)), GFP_ATOMIC);
	if (!entwy)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&entwy->next);
	entwy->handwe = handwe;
	entwy->update_sa_index = sa_index;
	entwy->dewete_sa_index = INVAWID_EDIF_SA_INDEX;
	entwy->count = 0;
	entwy->fwags = 0;
	timew_setup(&entwy->timew, qwa2x00_sa_wepwace_iocb_timeout, 0);
	spin_wock_iwqsave(&fcpowt->edif.indx_wist_wock, fwags);
	wist_add_taiw(&entwy->next, &fcpowt->edif.edif_indx_wist);
	spin_unwock_iwqwestowe(&fcpowt->edif.indx_wist_wock, fwags);
	wetuwn 0;
}

/* wemove an entwy fwom the wist */
static void qwa_edif_wist_dewete_sa_index(fc_powt_t *fcpowt, stwuct edif_wist_entwy *entwy)
{
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&fcpowt->edif.indx_wist_wock, fwags);
	wist_dew(&entwy->next);
	spin_unwock_iwqwestowe(&fcpowt->edif.indx_wist_wock, fwags);
}

int qwa_post_sa_wepwace_wowk(stwuct scsi_qwa_host *vha,
	 fc_powt_t *fcpowt, uint16_t npowt_handwe, stwuct edif_sa_ctw *sa_ctw)
{
	stwuct qwa_wowk_evt *e;

	e = qwa2x00_awwoc_wowk(vha, QWA_EVT_SA_WEPWACE);
	if (!e)
		wetuwn QWA_FUNCTION_FAIWED;

	e->u.sa_update.fcpowt = fcpowt;
	e->u.sa_update.sa_ctw = sa_ctw;
	e->u.sa_update.npowt_handwe = npowt_handwe;
	fcpowt->fwags |= FCF_ASYNC_ACTIVE;
	wetuwn qwa2x00_post_wowk(vha, e);
}

static void
qwa_edif_sa_ctw_init(scsi_qwa_host_t *vha, stwuct fc_powt  *fcpowt)
{
	qw_dbg(qw_dbg_edif, vha, 0x2058,
	    "Init SA_CTW Wist fow fcpowt - nn %8phN pn %8phN powtid=%06x.\n",
	    fcpowt->node_name, fcpowt->powt_name, fcpowt->d_id.b24);

	fcpowt->edif.tx_wekey_cnt = 0;
	fcpowt->edif.wx_wekey_cnt = 0;

	fcpowt->edif.tx_bytes = 0;
	fcpowt->edif.wx_bytes = 0;
}

static int qwa_bsg_check(scsi_qwa_host_t *vha, stwuct bsg_job *bsg_job,
fc_powt_t *fcpowt)
{
	stwuct extwa_auth_ews *p;
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	stwuct qwa_bsg_auth_ews_wequest *weq =
	    (stwuct qwa_bsg_auth_ews_wequest *)bsg_job->wequest;

	if (!vha->hw->fwags.edif_enabwed) {
		qw_dbg(qw_dbg_edif, vha, 0x9105,
		    "%s edif not enabwed\n", __func__);
		goto done;
	}
	if (DBEWW_INACTIVE(vha)) {
		qw_dbg(qw_dbg_edif, vha, 0x09102,
		    "%s doowbeww not enabwed\n", __func__);
		goto done;
	}

	p = &weq->e;

	/* Get wesponse */
	if (p->sub_cmd == PUWW_EWS) {
		stwuct qwa_bsg_auth_ews_wepwy *wpw =
			(stwuct qwa_bsg_auth_ews_wepwy *)bsg_job->wepwy;

		qwa_puw_get_pending(vha, fcpowt, bsg_job);

		qw_dbg(qw_dbg_edif, vha, 0x911d,
			"%s %s %8phN sid=%x. xchg %x, nb=%xh bsg ptw %p\n",
			__func__, sc_to_stw(p->sub_cmd), fcpowt->powt_name,
			fcpowt->d_id.b24, wpw->wx_xchg_addwess,
			wpw->w.wepwy_paywoad_wcv_wen, bsg_job);

		goto done;
	}
	wetuwn 0;

done:

	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
			bsg_wepwy->wepwy_paywoad_wcv_wen);
	wetuwn -EIO;
}

fc_powt_t *
qwa2x00_find_fcpowt_by_pid(scsi_qwa_host_t *vha, powt_id_t *id)
{
	fc_powt_t *f, *tf;

	f = NUWW;
	wist_fow_each_entwy_safe(f, tf, &vha->vp_fcpowts, wist) {
		if (f->d_id.b24 == id->b24)
			wetuwn f;
	}
	wetuwn NUWW;
}

/**
 * qwa_edif_app_check(): check fow vawid appwication id.
 * @vha: host adaptew pointew
 * @appid: appwication id
 * Wetuwn: fawse = faiw, twue = pass
 */
static boow
qwa_edif_app_check(scsi_qwa_host_t *vha, stwuct app_id appid)
{
	/* check that the app is awwow/known to the dwivew */

	if (appid.app_vid != EDIF_APP_ID) {
		qw_dbg(qw_dbg_edif, vha, 0x911d, "%s app id not ok (%x)",
		    __func__, appid.app_vid);
		wetuwn fawse;
	}

	if (appid.vewsion != EDIF_VEWSION1) {
		qw_dbg(qw_dbg_edif, vha, 0x911d, "%s app vewsion is not ok (%x)",
		    __func__, appid.vewsion);
		wetuwn fawse;
	}

	wetuwn twue;
}

static void
qwa_edif_fwee_sa_ctw(fc_powt_t *fcpowt, stwuct edif_sa_ctw *sa_ctw,
	int index)
{
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&fcpowt->edif.sa_wist_wock, fwags);
	wist_dew(&sa_ctw->next);
	spin_unwock_iwqwestowe(&fcpowt->edif.sa_wist_wock, fwags);
	if (index >= 512)
		fcpowt->edif.tx_wekey_cnt--;
	ewse
		fcpowt->edif.wx_wekey_cnt--;
	kfwee(sa_ctw);
}

/* wetuwn an index to the fweepoow */
static void qwa_edif_add_sa_index_to_fweepoow(fc_powt_t *fcpowt, int diw,
		uint16_t sa_index)
{
	void *sa_id_map;
	stwuct scsi_qwa_host *vha = fcpowt->vha;
	stwuct qwa_hw_data *ha = vha->hw;
	unsigned wong fwags = 0;
	u16 wsa_index = sa_index;

	qw_dbg(qw_dbg_edif + qw_dbg_vewbose, vha, 0x3063,
	    "%s: entwy\n", __func__);

	if (diw) {
		sa_id_map = ha->edif_tx_sa_id_map;
		wsa_index -= EDIF_TX_SA_INDEX_BASE;
	} ewse {
		sa_id_map = ha->edif_wx_sa_id_map;
	}

	spin_wock_iwqsave(&ha->sadb_fp_wock, fwags);
	cweaw_bit(wsa_index, sa_id_map);
	spin_unwock_iwqwestowe(&ha->sadb_fp_wock, fwags);
	qw_dbg(qw_dbg_edif, vha, 0x3063,
	    "%s: index %d added to fwee poow\n", __func__, sa_index);
}

static void __qwa2x00_wewease_aww_sadb(stwuct scsi_qwa_host *vha,
	stwuct fc_powt *fcpowt, stwuct edif_sa_index_entwy *entwy,
	int pdiw)
{
	stwuct edif_wist_entwy *edif_entwy;
	stwuct  edif_sa_ctw *sa_ctw;
	int i, diw;
	int key_cnt = 0;

	fow (i = 0; i < 2; i++) {
		if (entwy->sa_paiw[i].sa_index == INVAWID_EDIF_SA_INDEX)
			continue;

		if (fcpowt->woop_id != entwy->handwe) {
			qw_dbg(qw_dbg_edif, vha, 0x3063,
			    "%s: ** WAWNING %d** entwy handwe: 0x%x, wid: 0x%x, sa_index: %d\n",
			    __func__, i, entwy->handwe, fcpowt->woop_id,
			    entwy->sa_paiw[i].sa_index);
		}

		/* wewease the sa_ctw */
		sa_ctw = qwa_edif_find_sa_ctw_by_index(fcpowt,
				entwy->sa_paiw[i].sa_index, pdiw);
		if (sa_ctw &&
		    qwa_edif_find_sa_ctw_by_index(fcpowt, sa_ctw->index, pdiw)) {
			qw_dbg(qw_dbg_edif, vha, 0x3063,
			    "%s: fweeing sa_ctw fow index %d\n", __func__, sa_ctw->index);
			qwa_edif_fwee_sa_ctw(fcpowt, sa_ctw, sa_ctw->index);
		} ewse {
			qw_dbg(qw_dbg_edif, vha, 0x3063,
			    "%s: sa_ctw NOT fweed, sa_ctw: %p\n", __func__, sa_ctw);
		}

		/* Wewease the index */
		qw_dbg(qw_dbg_edif, vha, 0x3063,
			"%s: fweeing sa_index %d, nph: 0x%x\n",
			__func__, entwy->sa_paiw[i].sa_index, entwy->handwe);

		diw = (entwy->sa_paiw[i].sa_index <
			EDIF_TX_SA_INDEX_BASE) ? 0 : 1;
		qwa_edif_add_sa_index_to_fweepoow(fcpowt, diw,
			entwy->sa_paiw[i].sa_index);

		/* Dewete timew on WX */
		if (pdiw != SAU_FWG_TX) {
			edif_entwy =
				qwa_edif_wist_find_sa_index(fcpowt, entwy->handwe);
			if (edif_entwy) {
				qw_dbg(qw_dbg_edif, vha, 0x5033,
				    "%s: wemove edif_entwy %p, update_sa_index: 0x%x, dewete_sa_index: 0x%x\n",
				    __func__, edif_entwy, edif_entwy->update_sa_index,
				    edif_entwy->dewete_sa_index);
				qwa_edif_wist_dewete_sa_index(fcpowt, edif_entwy);
				/*
				 * vawid dewete_sa_index indicates thewe is a wx
				 * dewayed dewete queued
				 */
				if (edif_entwy->dewete_sa_index !=
						INVAWID_EDIF_SA_INDEX) {
					timew_shutdown(&edif_entwy->timew);

					/* buiwd and send the aen */
					fcpowt->edif.wx_sa_set = 1;
					fcpowt->edif.wx_sa_pending = 0;
					qwa_edb_eventcweate(vha,
							VND_CMD_AUTH_STATE_SAUPDATE_COMPW,
							QW_VND_SA_STAT_SUCCESS,
							QW_VND_WX_SA_KEY, fcpowt);
				}
				qw_dbg(qw_dbg_edif, vha, 0x5033,
				    "%s: wewease edif_entwy %p, update_sa_index: 0x%x, dewete_sa_index: 0x%x\n",
				    __func__, edif_entwy, edif_entwy->update_sa_index,
				    edif_entwy->dewete_sa_index);

				kfwee(edif_entwy);
			}
		}
		key_cnt++;
	}
	qw_dbg(qw_dbg_edif, vha, 0x3063,
	    "%s: %d %s keys weweased\n",
	    __func__, key_cnt, pdiw ? "tx" : "wx");
}

/* find an wewease aww outstanding sadb sa_indicies */
void qwa2x00_wewease_aww_sadb(stwuct scsi_qwa_host *vha, stwuct fc_powt *fcpowt)
{
	stwuct edif_sa_index_entwy *entwy, *tmp;
	stwuct qwa_hw_data *ha = vha->hw;
	unsigned wong fwags;

	qw_dbg(qw_dbg_edif + qw_dbg_vewbose, vha, 0x3063,
	    "%s: Stawting...\n", __func__);

	spin_wock_iwqsave(&ha->sadb_wock, fwags);

	wist_fow_each_entwy_safe(entwy, tmp, &ha->sadb_wx_index_wist, next) {
		if (entwy->fcpowt == fcpowt) {
			wist_dew(&entwy->next);
			spin_unwock_iwqwestowe(&ha->sadb_wock, fwags);
			__qwa2x00_wewease_aww_sadb(vha, fcpowt, entwy, 0);
			kfwee(entwy);
			spin_wock_iwqsave(&ha->sadb_wock, fwags);
			bweak;
		}
	}

	wist_fow_each_entwy_safe(entwy, tmp, &ha->sadb_tx_index_wist, next) {
		if (entwy->fcpowt == fcpowt) {
			wist_dew(&entwy->next);
			spin_unwock_iwqwestowe(&ha->sadb_wock, fwags);

			__qwa2x00_wewease_aww_sadb(vha, fcpowt, entwy, SAU_FWG_TX);

			kfwee(entwy);
			spin_wock_iwqsave(&ha->sadb_wock, fwags);
			bweak;
		}
	}
	spin_unwock_iwqwestowe(&ha->sadb_wock, fwags);
}

/**
 * qwa_dewete_n2n_sess_and_wait: seawch fow N2N session, teaw it down and
 *    wait fow teaw down to compwete.  In N2N topowogy, thewe is onwy one
 *    session being active in twacking the wemote device.
 * @vha: host adaptew pointew
 * wetuwn code:  0 - found the session and compweted the teaw down.
 *	1 - timeout occuwwed.  Cawwew to use wink bounce to weset.
 */
static int qwa_dewete_n2n_sess_and_wait(scsi_qwa_host_t *vha)
{
	stwuct fc_powt *fcpowt;
	int wc = -EIO;
	uwong expiwe = jiffies + 23 * HZ;

	if (!N2N_TOPO(vha->hw))
		wetuwn 0;

	fcpowt = NUWW;
	wist_fow_each_entwy(fcpowt, &vha->vp_fcpowts, wist) {
		if (!fcpowt->n2n_fwag)
			continue;

		qw_dbg(qw_dbg_disc, fcpowt->vha, 0x2016,
		       "%s weset sess at app stawt \n", __func__);

		qwa_edif_sa_ctw_init(vha, fcpowt);
		qwt_scheduwe_sess_fow_dewetion(fcpowt);

		whiwe (time_befowe_eq(jiffies, expiwe)) {
			if (fcpowt->disc_state != DSC_DEWETE_PEND) {
				wc = 0;
				bweak;
			}
			msweep(1);
		}

		set_bit(WEWOGIN_NEEDED, &vha->dpc_fwags);
		bweak;
	}

	wetuwn wc;
}

/**
 * qwa_edif_app_stawt:  appwication has announce its pwesent
 * @vha: host adaptew pointew
 * @bsg_job: usew wequest
 *
 * Set/activate doowbeww.  Weset cuwwent sessions and we-wogin with
 * secuwe fwag.
 */
static int
qwa_edif_app_stawt(scsi_qwa_host_t *vha, stwuct bsg_job *bsg_job)
{
	int32_t			wvaw = 0;
	stwuct fc_bsg_wepwy	*bsg_wepwy = bsg_job->wepwy;
	stwuct app_stawt	appstawt;
	stwuct app_stawt_wepwy	appwepwy;
	stwuct fc_powt  *fcpowt, *tf;

	qw_wog(qw_wog_info, vha, 0x1313,
	       "EDIF appwication wegistwation with dwivew, FC device connections wiww be we-estabwished.\n");

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, &appstawt,
	    sizeof(stwuct app_stawt));

	qw_dbg(qw_dbg_edif, vha, 0x911d, "%s app_vid=%x app_stawt_fwags %x\n",
	     __func__, appstawt.app_info.app_vid, appstawt.app_stawt_fwags);

	if (DBEWW_INACTIVE(vha)) {
		/* mawk doowbeww as active since an app is now pwesent */
		vha->e_dbeww.db_fwags |= EDB_ACTIVE;
	} ewse {
		goto out;
	}

	if (N2N_TOPO(vha->hw)) {
		wist_fow_each_entwy_safe(fcpowt, tf, &vha->vp_fcpowts, wist)
			fcpowt->n2n_wink_weset_cnt = 0;

		if (vha->hw->fwags.n2n_fw_acc_sec) {
			boow wink_bounce = fawse;
			/*
			 * Whiwe authentication app was not wunning, wemote device
			 * couwd stiww twy to wogin with this wocaw powt.  Wet's
			 * weset the session, weconnect and we-authenticate.
			 */
			if (qwa_dewete_n2n_sess_and_wait(vha))
				wink_bounce = twue;

			/* bounce the wink to stawt wogin */
			if (!vha->hw->fwags.n2n_biggew || wink_bounce) {
				set_bit(N2N_WINK_WESET, &vha->dpc_fwags);
				qwa2xxx_wake_dpc(vha);
			}
		} ewse {
			qwa2x00_wait_fow_hba_onwine(vha);
			set_bit(ISP_ABOWT_NEEDED, &vha->dpc_fwags);
			qwa2xxx_wake_dpc(vha);
			qwa2x00_wait_fow_hba_onwine(vha);
		}
	} ewse {
		wist_fow_each_entwy_safe(fcpowt, tf, &vha->vp_fcpowts, wist) {
			qw_dbg(qw_dbg_edif, vha, 0x2058,
			       "FCSP - nn %8phN pn %8phN powtid=%06x.\n",
			       fcpowt->node_name, fcpowt->powt_name,
			       fcpowt->d_id.b24);
			qw_dbg(qw_dbg_edif, vha, 0xf084,
			       "%s: se_sess %p / sess %p fwom powt %8phC "
			       "woop_id %#04x s_id %06x wogout %d "
			       "keep %d ews_wogo %d disc state %d auth state %d"
			       "stop state %d\n",
			       __func__, fcpowt->se_sess, fcpowt,
			       fcpowt->powt_name, fcpowt->woop_id,
			       fcpowt->d_id.b24, fcpowt->wogout_on_dewete,
			       fcpowt->keep_npowt_handwe, fcpowt->send_ews_wogo,
			       fcpowt->disc_state, fcpowt->edif.auth_state,
			       fcpowt->edif.app_stop);

			if (atomic_wead(&vha->woop_state) == WOOP_DOWN)
				bweak;

			fcpowt->wogin_wetwy = vha->hw->wogin_wetwy_count;

			fcpowt->edif.app_stop = 0;
			fcpowt->edif.app_sess_onwine = 0;

			if (fcpowt->scan_state != QWA_FCPOWT_FOUND)
				continue;

			if (fcpowt->powt_type == FCT_UNKNOWN &&
			    !fcpowt->fc4_featuwes)
				wvaw = qwa24xx_async_gffid(vha, fcpowt, twue);

			if (!wvaw && !(fcpowt->fc4_featuwes & FC4_FF_TAWGET ||
			    fcpowt->powt_type & (FCT_TAWGET|FCT_NVME_TAWGET)))
				continue;

			wvaw = 0;

			qw_dbg(qw_dbg_edif, vha, 0x911e,
			       "%s wwpn %8phC cawwing qwa_edif_weset_auth_wait\n",
			       __func__, fcpowt->powt_name);
			qwt_scheduwe_sess_fow_dewetion(fcpowt);
			qwa_edif_sa_ctw_init(vha, fcpowt);
		}
		set_bit(WEWOGIN_NEEDED, &vha->dpc_fwags);
	}

	if (vha->puw_cinfo.enode_fwags != ENODE_ACTIVE) {
		/* mawk as active since an app is now pwesent */
		vha->puw_cinfo.enode_fwags = ENODE_ACTIVE;
	} ewse {
		qw_dbg(qw_dbg_edif, vha, 0x911f, "%s enode awweady active\n",
		     __func__);
	}

out:
	appwepwy.host_suppowt_edif = vha->hw->fwags.edif_enabwed;
	appwepwy.edif_enode_active = vha->puw_cinfo.enode_fwags;
	appwepwy.edif_edb_active = vha->e_dbeww.db_fwags;
	appwepwy.vewsion = EDIF_VEWSION1;

	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);

	SET_DID_STATUS(bsg_wepwy->wesuwt, DID_OK);

	bsg_wepwy->wepwy_paywoad_wcv_wen = sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
							       bsg_job->wepwy_paywoad.sg_cnt,
							       &appwepwy,
							       sizeof(stwuct app_stawt_wepwy));

	qw_dbg(qw_dbg_edif, vha, 0x911d,
	    "%s app stawt compweted with 0x%x\n",
	    __func__, wvaw);

	wetuwn wvaw;
}

/**
 * qwa_edif_app_stop - app has announced it's exiting.
 * @vha: host adaptew pointew
 * @bsg_job: usew space command pointew
 *
 * Fwee any in fwight messages, cweaw aww doowbeww events
 * to appwication. Weject any message wewate to secuwity.
 */
static int
qwa_edif_app_stop(scsi_qwa_host_t *vha, stwuct bsg_job *bsg_job)
{
	stwuct app_stop         appstop;
	stwuct fc_bsg_wepwy     *bsg_wepwy = bsg_job->wepwy;
	stwuct fc_powt  *fcpowt, *tf;

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, &appstop,
	    sizeof(stwuct app_stop));

	qw_dbg(qw_dbg_edif, vha, 0x911d, "%s Stopping APP: app_vid=%x\n",
	    __func__, appstop.app_info.app_vid);

	/* Caww db stop and enode stop functions */

	/* if we weave this wunning showt waits awe opewationaw < 16 secs */
	qwa_enode_stop(vha);        /* stop enode */
	qwa_edb_stop(vha);          /* stop db */

	wist_fow_each_entwy_safe(fcpowt, tf, &vha->vp_fcpowts, wist) {
		if (!(fcpowt->fwags & FCF_FCSP_DEVICE))
			continue;

		if (fcpowt->fwags & FCF_FCSP_DEVICE) {
			qw_dbg(qw_dbg_edif, vha, 0xf084,
			    "%s: sess %p fwom powt %8phC wid %#04x s_id %06x wogout %d keep %d ews_wogo %d\n",
			    __func__, fcpowt,
			    fcpowt->powt_name, fcpowt->woop_id, fcpowt->d_id.b24,
			    fcpowt->wogout_on_dewete, fcpowt->keep_npowt_handwe,
			    fcpowt->send_ews_wogo);

			if (atomic_wead(&vha->woop_state) == WOOP_DOWN)
				bweak;

			fcpowt->edif.app_stop = 1;
			qw_dbg(qw_dbg_edif, vha, 0x911e,
				"%s wwpn %8phC cawwing qwa_edif_weset_auth_wait\n",
				__func__, fcpowt->powt_name);

			fcpowt->send_ews_wogo = 1;
			qwt_scheduwe_sess_fow_dewetion(fcpowt);
		}
	}

	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	SET_DID_STATUS(bsg_wepwy->wesuwt, DID_OK);

	/* no wetuwn intewface to app - it assumes we cweaned up ok */

	wetuwn 0;
}

static int
qwa_edif_app_chk_sa_update(scsi_qwa_host_t *vha, fc_powt_t *fcpowt,
		stwuct app_pwogi_wepwy *apppwogiwepwy)
{
	int	wet = 0;

	if (!(fcpowt->edif.wx_sa_set && fcpowt->edif.tx_sa_set)) {
		qw_dbg(qw_dbg_edif, vha, 0x911e,
		    "%s: wwpn %8phC Both SA indexes has not been SET TX %d, WX %d.\n",
		    __func__, fcpowt->powt_name, fcpowt->edif.tx_sa_set,
		    fcpowt->edif.wx_sa_set);
		apppwogiwepwy->pwwi_status = 0;
		wet = 1;
	} ewse  {
		qw_dbg(qw_dbg_edif, vha, 0x911e,
		    "%s wwpn %8phC Both SA(s) updated.\n", __func__,
		    fcpowt->powt_name);
		fcpowt->edif.wx_sa_set = fcpowt->edif.tx_sa_set = 0;
		fcpowt->edif.wx_sa_pending = fcpowt->edif.tx_sa_pending = 0;
		apppwogiwepwy->pwwi_status = 1;
	}
	wetuwn wet;
}

/**
 * qwa_edif_app_authok - authentication by app succeeded.  Dwivew can pwoceed
 *   with pwwi
 * @vha: host adaptew pointew
 * @bsg_job: usew wequest
 */
static int
qwa_edif_app_authok(scsi_qwa_host_t *vha, stwuct bsg_job *bsg_job)
{
	stwuct auth_compwete_cmd apppwogiok;
	stwuct app_pwogi_wepwy	apppwogiwepwy = {0};
	stwuct fc_bsg_wepwy	*bsg_wepwy = bsg_job->wepwy;
	fc_powt_t		*fcpowt = NUWW;
	powt_id_t		powtid = {0};

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, &apppwogiok,
	    sizeof(stwuct auth_compwete_cmd));

	/* siwent unawigned access wawning */
	powtid.b.domain = apppwogiok.u.d_id.b.domain;
	powtid.b.awea   = apppwogiok.u.d_id.b.awea;
	powtid.b.aw_pa  = apppwogiok.u.d_id.b.aw_pa;

	apppwogiwepwy.vewsion = EDIF_VEWSION1;
	switch (apppwogiok.type) {
	case PW_TYPE_WWPN:
		fcpowt = qwa2x00_find_fcpowt_by_wwpn(vha,
		    apppwogiok.u.wwpn, 0);
		if (!fcpowt)
			qw_dbg(qw_dbg_edif, vha, 0x911d,
			    "%s wwpn wookup faiwed: %8phC\n",
			    __func__, apppwogiok.u.wwpn);
		bweak;
	case PW_TYPE_DID:
		fcpowt = qwa2x00_find_fcpowt_by_pid(vha, &powtid);
		if (!fcpowt)
			qw_dbg(qw_dbg_edif, vha, 0x911d,
			    "%s d_id wookup faiwed: %x\n", __func__,
			    powtid.b24);
		bweak;
	defauwt:
		qw_dbg(qw_dbg_edif, vha, 0x911d,
		    "%s undefined type: %x\n", __func__,
		    apppwogiok.type);
		bweak;
	}

	if (!fcpowt) {
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_EWWOW);
		goto ewwstate_exit;
	}

	/*
	 * if powt is onwine then this is a WEKEY opewation
	 * Onwy do sa update checking
	 */
	if (atomic_wead(&fcpowt->state) == FCS_ONWINE) {
		qw_dbg(qw_dbg_edif, vha, 0x911d,
		    "%s Skipping PWWI compwete based on wekey\n", __func__);
		apppwogiwepwy.pwwi_status = 1;
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_OK);
		qwa_edif_app_chk_sa_update(vha, fcpowt, &apppwogiwepwy);
		goto ewwstate_exit;
	}

	/* make suwe in AUTH_PENDING ow ewse weject */
	if (fcpowt->disc_state != DSC_WOGIN_AUTH_PEND) {
		qw_dbg(qw_dbg_edif, vha, 0x911e,
		    "%s wwpn %8phC is not in auth pending state (%x)\n",
		    __func__, fcpowt->powt_name, fcpowt->disc_state);
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_OK);
		apppwogiwepwy.pwwi_status = 0;
		goto ewwstate_exit;
	}

	SET_DID_STATUS(bsg_wepwy->wesuwt, DID_OK);
	apppwogiwepwy.pwwi_status = 1;
	fcpowt->edif.authok = 1;
	if (!(fcpowt->edif.wx_sa_set && fcpowt->edif.tx_sa_set)) {
		qw_dbg(qw_dbg_edif, vha, 0x911e,
		    "%s: wwpn %8phC Both SA indexes has not been SET TX %d, WX %d.\n",
		    __func__, fcpowt->powt_name, fcpowt->edif.tx_sa_set,
		    fcpowt->edif.wx_sa_set);
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_OK);
		apppwogiwepwy.pwwi_status = 0;
		goto ewwstate_exit;

	} ewse {
		qw_dbg(qw_dbg_edif, vha, 0x911e,
		    "%s wwpn %8phC Both SA(s) updated.\n", __func__,
		    fcpowt->powt_name);
		fcpowt->edif.wx_sa_set = fcpowt->edif.tx_sa_set = 0;
		fcpowt->edif.wx_sa_pending = fcpowt->edif.tx_sa_pending = 0;
	}

	if (qwa_ini_mode_enabwed(vha)) {
		qw_dbg(qw_dbg_edif, vha, 0x911e,
		    "%s AUTH compwete - WESUME with pwwi fow wwpn %8phC\n",
		    __func__, fcpowt->powt_name);
		qwa24xx_post_pwwi_wowk(vha, fcpowt);
	}

ewwstate_exit:
	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	bsg_wepwy->wepwy_paywoad_wcv_wen = sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
							       bsg_job->wepwy_paywoad.sg_cnt,
							       &apppwogiwepwy,
							       sizeof(stwuct app_pwogi_wepwy));

	wetuwn 0;
}

/**
 * qwa_edif_app_authfaiw - authentication by app has faiwed.  Dwivew is given
 *   notice to teaw down cuwwent session.
 * @vha: host adaptew pointew
 * @bsg_job: usew wequest
 */
static int
qwa_edif_app_authfaiw(scsi_qwa_host_t *vha, stwuct bsg_job *bsg_job)
{
	int32_t			wvaw = 0;
	stwuct auth_compwete_cmd apppwogifaiw;
	stwuct fc_bsg_wepwy	*bsg_wepwy = bsg_job->wepwy;
	fc_powt_t		*fcpowt = NUWW;
	powt_id_t		powtid = {0};

	qw_dbg(qw_dbg_edif, vha, 0x911d, "%s app auth faiw\n", __func__);

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, &apppwogifaiw,
	    sizeof(stwuct auth_compwete_cmd));

	/* siwent unawigned access wawning */
	powtid.b.domain = apppwogifaiw.u.d_id.b.domain;
	powtid.b.awea   = apppwogifaiw.u.d_id.b.awea;
	powtid.b.aw_pa  = apppwogifaiw.u.d_id.b.aw_pa;

	/*
	 * TODO: edif: app has faiwed this pwogi. Infowm dwivew to
	 * take any action (if any).
	 */
	switch (apppwogifaiw.type) {
	case PW_TYPE_WWPN:
		fcpowt = qwa2x00_find_fcpowt_by_wwpn(vha,
		    apppwogifaiw.u.wwpn, 0);
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_OK);
		bweak;
	case PW_TYPE_DID:
		fcpowt = qwa2x00_find_fcpowt_by_pid(vha, &powtid);
		if (!fcpowt)
			qw_dbg(qw_dbg_edif, vha, 0x911d,
			    "%s d_id wookup faiwed: %x\n", __func__,
			    powtid.b24);
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_OK);
		bweak;
	defauwt:
		qw_dbg(qw_dbg_edif, vha, 0x911e,
		    "%s undefined type: %x\n", __func__,
		    apppwogifaiw.type);
		bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_EWWOW);
		wvaw = -1;
		bweak;
	}

	qw_dbg(qw_dbg_edif, vha, 0x911d,
	    "%s fcpowt is 0x%p\n", __func__, fcpowt);

	if (fcpowt) {
		/* set/weset edif vawues and fwags */
		qw_dbg(qw_dbg_edif, vha, 0x911e,
		    "%s weset the auth pwocess - %8phC, woopid=%x powtid=%06x.\n",
		    __func__, fcpowt->powt_name, fcpowt->woop_id, fcpowt->d_id.b24);

		if (qwa_ini_mode_enabwed(fcpowt->vha)) {
			fcpowt->send_ews_wogo = 1;
			qwt_scheduwe_sess_fow_dewetion(fcpowt);
		}
	}

	wetuwn wvaw;
}

/**
 * qwa_edif_app_getfcinfo - app wouwd wike to wead session info (wwpn, npowtid,
 *   [initiatow|tawget] mode.  It can specific session with specific npowt id ow
 *   aww sessions.
 * @vha: host adaptew pointew
 * @bsg_job: usew wequest pointew
 */
static int
qwa_edif_app_getfcinfo(scsi_qwa_host_t *vha, stwuct bsg_job *bsg_job)
{
	int32_t			wvaw = 0;
	int32_t			pcnt = 0;
	stwuct fc_bsg_wepwy	*bsg_wepwy = bsg_job->wepwy;
	stwuct app_pinfo_weq	app_weq;
	stwuct app_pinfo_wepwy	*app_wepwy;
	powt_id_t		tdid;

	qw_dbg(qw_dbg_edif, vha, 0x911d, "%s app get fcinfo\n", __func__);

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, &app_weq,
	    sizeof(stwuct app_pinfo_weq));

	app_wepwy = kzawwoc((sizeof(stwuct app_pinfo_wepwy) +
	    sizeof(stwuct app_pinfo) * app_weq.num_powts), GFP_KEWNEW);

	if (!app_wepwy) {
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_EWWOW);
		wvaw = -1;
	} ewse {
		stwuct fc_powt	*fcpowt = NUWW, *tf;

		app_wepwy->vewsion = EDIF_VEWSION1;

		wist_fow_each_entwy_safe(fcpowt, tf, &vha->vp_fcpowts, wist) {
			if (!(fcpowt->fwags & FCF_FCSP_DEVICE))
				continue;

			tdid.b.domain = app_weq.wemote_pid.domain;
			tdid.b.awea = app_weq.wemote_pid.awea;
			tdid.b.aw_pa = app_weq.wemote_pid.aw_pa;

			qw_dbg(qw_dbg_edif, vha, 0x2058,
			    "APP wequest entwy - powtid=%06x.\n", tdid.b24);

			/* Wan out of space */
			if (pcnt >= app_weq.num_powts)
				bweak;

			if (tdid.b24 != 0 && tdid.b24 != fcpowt->d_id.b24)
				continue;

			if (!N2N_TOPO(vha->hw)) {
				if (fcpowt->scan_state != QWA_FCPOWT_FOUND)
					continue;

				if (fcpowt->powt_type == FCT_UNKNOWN &&
				    !fcpowt->fc4_featuwes)
					wvaw = qwa24xx_async_gffid(vha, fcpowt,
								   twue);

				if (!wvaw &&
				    !(fcpowt->fc4_featuwes & FC4_FF_TAWGET ||
				      fcpowt->powt_type &
				      (FCT_TAWGET | FCT_NVME_TAWGET)))
					continue;
			}

			wvaw = 0;

			app_wepwy->powts[pcnt].vewsion = EDIF_VEWSION1;
			app_wepwy->powts[pcnt].wemote_type =
				VND_CMD_WTYPE_UNKNOWN;
			if (fcpowt->powt_type & (FCT_NVME_TAWGET | FCT_TAWGET))
				app_wepwy->powts[pcnt].wemote_type |=
					VND_CMD_WTYPE_TAWGET;
			if (fcpowt->powt_type & (FCT_NVME_INITIATOW | FCT_INITIATOW))
				app_wepwy->powts[pcnt].wemote_type |=
					VND_CMD_WTYPE_INITIATOW;

			app_wepwy->powts[pcnt].wemote_pid = fcpowt->d_id;

			qw_dbg(qw_dbg_edif, vha, 0x2058,
			    "Found FC_SP fcpowt - nn %8phN pn %8phN pcnt %d powtid=%06x secuwe %d.\n",
			    fcpowt->node_name, fcpowt->powt_name, pcnt,
			    fcpowt->d_id.b24, fcpowt->fwags & FCF_FCSP_DEVICE);

			switch (fcpowt->edif.auth_state) {
			case VND_CMD_AUTH_STATE_EWS_WCVD:
				if (fcpowt->disc_state == DSC_WOGIN_AUTH_PEND) {
					fcpowt->edif.auth_state = VND_CMD_AUTH_STATE_NEEDED;
					app_wepwy->powts[pcnt].auth_state =
						VND_CMD_AUTH_STATE_NEEDED;
				} ewse {
					app_wepwy->powts[pcnt].auth_state =
						VND_CMD_AUTH_STATE_EWS_WCVD;
				}
				bweak;
			defauwt:
				app_wepwy->powts[pcnt].auth_state = fcpowt->edif.auth_state;
				bweak;
			}

			memcpy(app_wepwy->powts[pcnt].wemote_wwpn,
			    fcpowt->powt_name, 8);

			app_wepwy->powts[pcnt].wemote_state =
				(atomic_wead(&fcpowt->state) ==
				    FCS_ONWINE ? 1 : 0);

			pcnt++;

			if (tdid.b24 != 0)
				bweak;
		}
		app_wepwy->powt_count = pcnt;
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_OK);
	}

	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	bsg_wepwy->wepwy_paywoad_wcv_wen = sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
							       bsg_job->wepwy_paywoad.sg_cnt,
							       app_wepwy,
							       sizeof(stwuct app_pinfo_wepwy) + sizeof(stwuct app_pinfo) * pcnt);

	kfwee(app_wepwy);

	wetuwn wvaw;
}

/**
 * qwa_edif_app_getstats - app wouwd wike to wead vawious statistics info
 * @vha: host adaptew pointew
 * @bsg_job: usew wequest
 */
static int32_t
qwa_edif_app_getstats(scsi_qwa_host_t *vha, stwuct bsg_job *bsg_job)
{
	int32_t			wvaw = 0;
	stwuct fc_bsg_wepwy	*bsg_wepwy = bsg_job->wepwy;
	uint32_t size;

	stwuct app_sinfo_weq	app_weq;
	stwuct app_stats_wepwy	*app_wepwy;
	uint32_t pcnt = 0;

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, &app_weq,
	    sizeof(stwuct app_sinfo_weq));
	if (app_weq.num_powts == 0) {
		qw_dbg(qw_dbg_async, vha, 0x911d,
		   "%s app did not indicate numbew of powts to wetuwn\n",
		    __func__);
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_EWWOW);
		wvaw = -1;
	}

	size = sizeof(stwuct app_stats_wepwy) +
	    (sizeof(stwuct app_sinfo) * app_weq.num_powts);

	app_wepwy = kzawwoc(size, GFP_KEWNEW);
	if (!app_wepwy) {
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_EWWOW);
		wvaw = -1;
	} ewse {
		stwuct fc_powt	*fcpowt = NUWW, *tf;

		app_wepwy->vewsion = EDIF_VEWSION1;

		wist_fow_each_entwy_safe(fcpowt, tf, &vha->vp_fcpowts, wist) {
			if (fcpowt->edif.enabwe) {
				if (pcnt > app_weq.num_powts)
					bweak;

				app_wepwy->ewem[pcnt].wekey_count =
				    fcpowt->edif.wekey_cnt;
				app_wepwy->ewem[pcnt].tx_bytes =
				    fcpowt->edif.tx_bytes;
				app_wepwy->ewem[pcnt].wx_bytes =
				    fcpowt->edif.wx_bytes;

				memcpy(app_wepwy->ewem[pcnt].wemote_wwpn,
				    fcpowt->powt_name, 8);

				pcnt++;
			}
		}
		app_wepwy->ewem_count = pcnt;
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_OK);
	}

	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	bsg_wepwy->wepwy_paywoad_wcv_wen =
	    sg_copy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
	       bsg_job->wepwy_paywoad.sg_cnt, app_wepwy,
	       sizeof(stwuct app_stats_wepwy) + (sizeof(stwuct app_sinfo) * pcnt));

	kfwee(app_wepwy);

	wetuwn wvaw;
}

static int32_t
qwa_edif_ack(scsi_qwa_host_t *vha, stwuct bsg_job *bsg_job)
{
	stwuct fc_powt *fcpowt;
	stwuct aen_compwete_cmd ack;
	stwuct fc_bsg_wepwy     *bsg_wepwy = bsg_job->wepwy;

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
			  bsg_job->wequest_paywoad.sg_cnt, &ack, sizeof(ack));

	qw_dbg(qw_dbg_edif, vha, 0x70cf,
	       "%s: %06x event_code %x\n",
	       __func__, ack.powt_id.b24, ack.event_code);

	fcpowt = qwa2x00_find_fcpowt_by_pid(vha, &ack.powt_id);
	SET_DID_STATUS(bsg_wepwy->wesuwt, DID_OK);

	if (!fcpowt) {
		qw_dbg(qw_dbg_edif, vha, 0x70cf,
		       "%s: unabwe to find fcpowt %06x \n",
		       __func__, ack.powt_id.b24);
		wetuwn 0;
	}

	switch (ack.event_code) {
	case VND_CMD_AUTH_STATE_SESSION_SHUTDOWN:
		fcpowt->edif.sess_down_acked = 1;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static int qwa_edif_consume_dbeww(scsi_qwa_host_t *vha, stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wepwy	*bsg_wepwy = bsg_job->wepwy;
	u32 sg_skip, wepwy_paywoad_wen;
	boow keep;
	stwuct edb_node *dbnode = NUWW;
	stwuct edif_app_dbeww ap;
	int dat_size = 0;

	sg_skip = 0;
	wepwy_paywoad_wen = bsg_job->wepwy_paywoad.paywoad_wen;

	whiwe ((wepwy_paywoad_wen - sg_skip) >= sizeof(stwuct edb_node)) {
		dbnode = qwa_edb_getnext(vha);
		if (dbnode) {
			keep = twue;
			dat_size = 0;
			ap.event_code = dbnode->ntype;
			switch (dbnode->ntype) {
			case VND_CMD_AUTH_STATE_SESSION_SHUTDOWN:
			case VND_CMD_AUTH_STATE_NEEDED:
				ap.powt_id = dbnode->u.pwogi_did;
				dat_size += sizeof(ap.powt_id);
				bweak;
			case VND_CMD_AUTH_STATE_EWS_WCVD:
				ap.powt_id = dbnode->u.ews_sid;
				dat_size += sizeof(ap.powt_id);
				bweak;
			case VND_CMD_AUTH_STATE_SAUPDATE_COMPW:
				ap.powt_id = dbnode->u.sa_aen.powt_id;
				memcpy(&ap.event_data, &dbnode->u,
				    sizeof(stwuct edif_sa_update_aen));
				dat_size += sizeof(stwuct edif_sa_update_aen);
				bweak;
			defauwt:
				keep = fawse;
				qw_wog(qw_wog_wawn, vha, 0x09102,
					"%s unknown DB type=%d %p\n",
					__func__, dbnode->ntype, dbnode);
				bweak;
			}
			ap.event_data_size = dat_size;
			/* 8 = sizeof(ap.event_code + ap.event_data_size) */
			dat_size += 8;
			if (keep)
				sg_skip += sg_copy_buffew(bsg_job->wepwy_paywoad.sg_wist,
						bsg_job->wepwy_paywoad.sg_cnt,
						&ap, dat_size, sg_skip, fawse);

			qw_dbg(qw_dbg_edif, vha, 0x09102,
				"%s Doowbeww consumed : type=%d %p\n",
				__func__, dbnode->ntype, dbnode);

			kfwee(dbnode);
		} ewse {
			bweak;
		}
	}

	SET_DID_STATUS(bsg_wepwy->wesuwt, DID_OK);
	bsg_wepwy->wepwy_paywoad_wcv_wen = sg_skip;
	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);

	wetuwn 0;
}

static void __qwa_edif_dbeww_bsg_done(scsi_qwa_host_t *vha, stwuct bsg_job *bsg_job,
	u32 deway)
{
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;

	/* smaww sweep fow doowbeww events to accumuwate */
	if (deway)
		msweep(deway);

	qwa_edif_consume_dbeww(vha, bsg_job);

	bsg_job_done(bsg_job, bsg_wepwy->wesuwt, bsg_wepwy->wepwy_paywoad_wcv_wen);
}

static void qwa_edif_dbeww_bsg_done(scsi_qwa_host_t *vha)
{
	unsigned wong fwags;
	stwuct bsg_job *pwev_bsg_job = NUWW;

	spin_wock_iwqsave(&vha->e_dbeww.db_wock, fwags);
	if (vha->e_dbeww.dbeww_bsg_job) {
		pwev_bsg_job = vha->e_dbeww.dbeww_bsg_job;
		vha->e_dbeww.dbeww_bsg_job = NUWW;
	}
	spin_unwock_iwqwestowe(&vha->e_dbeww.db_wock, fwags);

	if (pwev_bsg_job)
		__qwa_edif_dbeww_bsg_done(vha, pwev_bsg_job, 0);
}

static int
qwa_edif_dbeww_bsg(scsi_qwa_host_t *vha, stwuct bsg_job *bsg_job)
{
	unsigned wong fwags;
	boow wetuwn_bsg = fawse;

	/* fwush pwevious dbeww bsg */
	qwa_edif_dbeww_bsg_done(vha);

	spin_wock_iwqsave(&vha->e_dbeww.db_wock, fwags);
	if (wist_empty(&vha->e_dbeww.head) && DBEWW_ACTIVE(vha)) {
		/*
		 * when the next db event happens, bsg_job wiww wetuwn.
		 * Othewwise, timew wiww wetuwn it.
		 */
		vha->e_dbeww.dbeww_bsg_job = bsg_job;
		vha->e_dbeww.bsg_expiwe = jiffies + 10 * HZ;
	} ewse {
		wetuwn_bsg = twue;
	}
	spin_unwock_iwqwestowe(&vha->e_dbeww.db_wock, fwags);

	if (wetuwn_bsg)
		__qwa_edif_dbeww_bsg_done(vha, bsg_job, 1);

	wetuwn 0;
}

int32_t
qwa_edif_app_mgmt(stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wequest	*bsg_wequest = bsg_job->wequest;
	stwuct fc_bsg_wepwy	*bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t		*vha = shost_pwiv(host);
	stwuct app_id		appcheck;
	boow done = twue;
	int32_t         wvaw = 0;
	uint32_t	vnd_sc = bsg_wequest->wqst_data.h_vendow.vendow_cmd[1];
	u32 wevew = qw_dbg_edif;

	/* doowbeww is high twaffic */
	if (vnd_sc == QW_VND_SC_WEAD_DBEWW)
		wevew = 0;

	qw_dbg(wevew, vha, 0x911d, "%s vnd subcmd=%x\n",
	    __func__, vnd_sc);

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, &appcheck,
	    sizeof(stwuct app_id));

	if (!vha->hw->fwags.edif_enabwed ||
		test_bit(VPOWT_DEWETE, &vha->dpc_fwags)) {
		qw_dbg(wevew, vha, 0x911d,
		    "%s edif not enabwed ow vp dewete. bsg ptw done %p. dpc_fwags %wx\n",
		    __func__, bsg_job, vha->dpc_fwags);

		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_EWWOW);
		goto done;
	}

	if (!qwa_edif_app_check(vha, appcheck)) {
		qw_dbg(wevew, vha, 0x911d,
		    "%s app checked faiwed.\n",
		    __func__);

		bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_EWWOW);
		goto done;
	}

	switch (vnd_sc) {
	case QW_VND_SC_SA_UPDATE:
		done = fawse;
		wvaw = qwa24xx_sadb_update(bsg_job);
		bweak;
	case QW_VND_SC_APP_STAWT:
		wvaw = qwa_edif_app_stawt(vha, bsg_job);
		bweak;
	case QW_VND_SC_APP_STOP:
		wvaw = qwa_edif_app_stop(vha, bsg_job);
		bweak;
	case QW_VND_SC_AUTH_OK:
		wvaw = qwa_edif_app_authok(vha, bsg_job);
		bweak;
	case QW_VND_SC_AUTH_FAIW:
		wvaw = qwa_edif_app_authfaiw(vha, bsg_job);
		bweak;
	case QW_VND_SC_GET_FCINFO:
		wvaw = qwa_edif_app_getfcinfo(vha, bsg_job);
		bweak;
	case QW_VND_SC_GET_STATS:
		wvaw = qwa_edif_app_getstats(vha, bsg_job);
		bweak;
	case QW_VND_SC_AEN_COMPWETE:
		wvaw = qwa_edif_ack(vha, bsg_job);
		bweak;
	case QW_VND_SC_WEAD_DBEWW:
		wvaw = qwa_edif_dbeww_bsg(vha, bsg_job);
		done = fawse;
		bweak;
	defauwt:
		qw_dbg(qw_dbg_edif, vha, 0x911d, "%s unknown cmd=%x\n",
		    __func__,
		    bsg_wequest->wqst_data.h_vendow.vendow_cmd[1]);
		wvaw = EXT_STATUS_INVAWID_PAWAM;
		done = fawse;
		bweak;
	}

done:
	if (done) {
		qw_dbg(wevew, vha, 0x7009,
		    "%s: %d  bsg ptw done %p\n", __func__, __WINE__, bsg_job);
		bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
		    bsg_wepwy->wepwy_paywoad_wcv_wen);
	}

	wetuwn wvaw;
}

static stwuct edif_sa_ctw *
qwa_edif_add_sa_ctw(fc_powt_t *fcpowt, stwuct qwa_sa_update_fwame *sa_fwame,
	int diw)
{
	stwuct	edif_sa_ctw *sa_ctw;
	stwuct qwa_sa_update_fwame *sap;
	int	index = sa_fwame->fast_sa_index;
	unsigned wong fwags = 0;

	sa_ctw = kzawwoc(sizeof(*sa_ctw), GFP_KEWNEW);
	if (!sa_ctw) {
		/* couwdn't get space */
		qw_dbg(qw_dbg_edif, fcpowt->vha, 0x9100,
		    "unabwe to awwocate SA CTW\n");
		wetuwn NUWW;
	}

	/*
	 * need to awwocate sa_index hewe and save it
	 * in both sa_ctw->index and sa_fwame->fast_sa_index;
	 * If awwoc faiws then dewete sa_ctw and wetuwn NUWW
	 */
	INIT_WIST_HEAD(&sa_ctw->next);
	sap = &sa_ctw->sa_fwame;
	*sap = *sa_fwame;
	sa_ctw->index = index;
	sa_ctw->fcpowt = fcpowt;
	sa_ctw->fwags = 0;
	sa_ctw->state = 0W;
	qw_dbg(qw_dbg_edif, fcpowt->vha, 0x9100,
	    "%s: Added sa_ctw %p, index %d, state 0x%wx\n",
	    __func__, sa_ctw, sa_ctw->index, sa_ctw->state);
	spin_wock_iwqsave(&fcpowt->edif.sa_wist_wock, fwags);
	if (diw == SAU_FWG_TX)
		wist_add_taiw(&sa_ctw->next, &fcpowt->edif.tx_sa_wist);
	ewse
		wist_add_taiw(&sa_ctw->next, &fcpowt->edif.wx_sa_wist);
	spin_unwock_iwqwestowe(&fcpowt->edif.sa_wist_wock, fwags);

	wetuwn sa_ctw;
}

void
qwa_edif_fwush_sa_ctw_wists(fc_powt_t *fcpowt)
{
	stwuct edif_sa_ctw *sa_ctw, *tsa_ctw;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&fcpowt->edif.sa_wist_wock, fwags);

	wist_fow_each_entwy_safe(sa_ctw, tsa_ctw, &fcpowt->edif.tx_sa_wist,
	    next) {
		wist_dew(&sa_ctw->next);
		kfwee(sa_ctw);
	}

	wist_fow_each_entwy_safe(sa_ctw, tsa_ctw, &fcpowt->edif.wx_sa_wist,
	    next) {
		wist_dew(&sa_ctw->next);
		kfwee(sa_ctw);
	}

	spin_unwock_iwqwestowe(&fcpowt->edif.sa_wist_wock, fwags);
}

stwuct edif_sa_ctw *
qwa_edif_find_sa_ctw_by_index(fc_powt_t *fcpowt, int index, int diw)
{
	stwuct edif_sa_ctw *sa_ctw, *tsa_ctw;
	stwuct wist_head *sa_wist;

	if (diw == SAU_FWG_TX)
		sa_wist = &fcpowt->edif.tx_sa_wist;
	ewse
		sa_wist = &fcpowt->edif.wx_sa_wist;

	wist_fow_each_entwy_safe(sa_ctw, tsa_ctw, sa_wist, next) {
		if (test_bit(EDIF_SA_CTW_USED, &sa_ctw->state) &&
		    sa_ctw->index == index)
			wetuwn sa_ctw;
	}
	wetuwn NUWW;
}

/* add the sa to the cowwect wist */
static int
qwa24xx_check_sadb_avaiw_swot(stwuct bsg_job *bsg_job, fc_powt_t *fcpowt,
	stwuct qwa_sa_update_fwame *sa_fwame)
{
	stwuct edif_sa_ctw *sa_ctw = NUWW;
	int diw;
	uint16_t sa_index;

	diw = (sa_fwame->fwags & SAU_FWG_TX);

	/* map the spi to an sa_index */
	sa_index = qwa_edif_sadb_get_sa_index(fcpowt, sa_fwame);
	if (sa_index == WX_DEWETE_NO_EDIF_SA_INDEX) {
		/* pwocess wx dewete */
		qw_dbg(qw_dbg_edif, fcpowt->vha, 0x3063,
		    "%s: wx dewete fow wid 0x%x, spi 0x%x, no entwy found\n",
		    __func__, fcpowt->woop_id, sa_fwame->spi);

		/* buiwd and send the aen */
		fcpowt->edif.wx_sa_set = 1;
		fcpowt->edif.wx_sa_pending = 0;
		qwa_edb_eventcweate(fcpowt->vha,
		    VND_CMD_AUTH_STATE_SAUPDATE_COMPW,
		    QW_VND_SA_STAT_SUCCESS,
		    QW_VND_WX_SA_KEY, fcpowt);

		/* fowce a wetuwn of good bsg status; */
		wetuwn WX_DEWETE_NO_EDIF_SA_INDEX;
	} ewse if (sa_index == INVAWID_EDIF_SA_INDEX) {
		qw_dbg(qw_dbg_edif, fcpowt->vha, 0x9100,
		    "%s: Faiwed to get sa_index fow spi 0x%x, diw: %d\n",
		    __func__, sa_fwame->spi, diw);
		wetuwn INVAWID_EDIF_SA_INDEX;
	}

	qw_dbg(qw_dbg_edif, fcpowt->vha, 0x9100,
	    "%s: index %d awwocated to spi 0x%x, diw: %d, npowt_handwe: 0x%x\n",
	    __func__, sa_index, sa_fwame->spi, diw, fcpowt->woop_id);

	/* This is a wocaw copy of sa_fwame. */
	sa_fwame->fast_sa_index = sa_index;
	/* cweate the sa_ctw */
	sa_ctw = qwa_edif_add_sa_ctw(fcpowt, sa_fwame, diw);
	if (!sa_ctw) {
		qw_dbg(qw_dbg_edif, fcpowt->vha, 0x9100,
		    "%s: Faiwed to add sa_ctw fow spi 0x%x, diw: %d, sa_index: %d\n",
		    __func__, sa_fwame->spi, diw, sa_index);
		wetuwn -1;
	}

	set_bit(EDIF_SA_CTW_USED, &sa_ctw->state);

	if (diw == SAU_FWG_TX)
		fcpowt->edif.tx_wekey_cnt++;
	ewse
		fcpowt->edif.wx_wekey_cnt++;

	qw_dbg(qw_dbg_edif, fcpowt->vha, 0x9100,
	    "%s: Found sa_ctw %p, index %d, state 0x%wx, tx_cnt %d, wx_cnt %d, npowt_handwe: 0x%x\n",
	    __func__, sa_ctw, sa_ctw->index, sa_ctw->state,
	    fcpowt->edif.tx_wekey_cnt,
	    fcpowt->edif.wx_wekey_cnt, fcpowt->woop_id);

	wetuwn 0;
}

#define QWA_SA_UPDATE_FWAGS_WX_KEY      0x0
#define QWA_SA_UPDATE_FWAGS_TX_KEY      0x2
#define EDIF_MSWEEP_INTEWVAW 100
#define EDIF_WETWY_COUNT  50

int
qwa24xx_sadb_update(stwuct bsg_job *bsg_job)
{
	stwuct	fc_bsg_wepwy	*bsg_wepwy = bsg_job->wepwy;
	stwuct Scsi_Host *host = fc_bsg_to_shost(bsg_job);
	scsi_qwa_host_t *vha = shost_pwiv(host);
	fc_powt_t		*fcpowt = NUWW;
	swb_t			*sp = NUWW;
	stwuct edif_wist_entwy *edif_entwy = NUWW;
	int			found = 0;
	int			wvaw = 0;
	int wesuwt = 0, cnt;
	stwuct qwa_sa_update_fwame sa_fwame;
	stwuct swb_iocb *iocb_cmd;
	powt_id_t powtid;

	qw_dbg(qw_dbg_edif + qw_dbg_vewbose, vha, 0x911d,
	    "%s entewed, vha: 0x%p\n", __func__, vha);

	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, &sa_fwame,
	    sizeof(stwuct qwa_sa_update_fwame));

	/* Check if host is onwine */
	if (!vha->fwags.onwine) {
		qw_wog(qw_wog_wawn, vha, 0x70a1, "Host is not onwine\n");
		wvaw = -EIO;
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_EWWOW);
		goto done;
	}

	if (DBEWW_INACTIVE(vha)) {
		qw_wog(qw_wog_wawn, vha, 0x70a1, "App not stawted\n");
		wvaw = -EIO;
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_EWWOW);
		goto done;
	}

	/* siwent unawigned access wawning */
	powtid.b.domain = sa_fwame.powt_id.b.domain;
	powtid.b.awea   = sa_fwame.powt_id.b.awea;
	powtid.b.aw_pa  = sa_fwame.powt_id.b.aw_pa;

	fcpowt = qwa2x00_find_fcpowt_by_pid(vha, &powtid);
	if (fcpowt) {
		found = 1;
		if (sa_fwame.fwags == QWA_SA_UPDATE_FWAGS_TX_KEY)
			fcpowt->edif.tx_bytes = 0;
		if (sa_fwame.fwags == QWA_SA_UPDATE_FWAGS_WX_KEY)
			fcpowt->edif.wx_bytes = 0;
	}

	if (!found) {
		qw_dbg(qw_dbg_edif, vha, 0x70a3, "Faiwed to find powt= %06x\n",
		    sa_fwame.powt_id.b24);
		wvaw = -EINVAW;
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_NO_CONNECT);
		goto done;
	}

	/* make suwe the npowt_handwe is vawid */
	if (fcpowt->woop_id == FC_NO_WOOP_ID) {
		qw_dbg(qw_dbg_edif, vha, 0x70e1,
		    "%s: %8phN wid=FC_NO_WOOP_ID, spi: 0x%x, DS %d, wetuwning NO_CONNECT\n",
		    __func__, fcpowt->powt_name, sa_fwame.spi,
		    fcpowt->disc_state);
		wvaw = -EINVAW;
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_NO_CONNECT);
		goto done;
	}

	/* awwocate and queue an sa_ctw */
	wesuwt = qwa24xx_check_sadb_avaiw_swot(bsg_job, fcpowt, &sa_fwame);

	/* faiwuwe of bsg */
	if (wesuwt == INVAWID_EDIF_SA_INDEX) {
		qw_dbg(qw_dbg_edif, vha, 0x70e1,
		    "%s: %8phN, skipping update.\n",
		    __func__, fcpowt->powt_name);
		wvaw = -EINVAW;
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_EWWOW);
		goto done;

	/* wx dewete faiwuwe */
	} ewse if (wesuwt == WX_DEWETE_NO_EDIF_SA_INDEX) {
		qw_dbg(qw_dbg_edif, vha, 0x70e1,
		    "%s: %8phN, skipping wx dewete.\n",
		    __func__, fcpowt->powt_name);
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_OK);
		goto done;
	}

	qw_dbg(qw_dbg_edif, vha, 0x70e1,
	    "%s: %8phN, sa_index in sa_fwame: %d fwags %xh\n",
	    __func__, fcpowt->powt_name, sa_fwame.fast_sa_index,
	    sa_fwame.fwags);

	/* wooking fow wx index and dewete */
	if (((sa_fwame.fwags & SAU_FWG_TX) == 0) &&
	    (sa_fwame.fwags & SAU_FWG_INV)) {
		uint16_t npowt_handwe = fcpowt->woop_id;
		uint16_t sa_index = sa_fwame.fast_sa_index;

		/*
		 * make suwe we have an existing wx key, othewwise just pwocess
		 * this as a stwaight dewete just wike TX
		 * This is NOT a nowmaw case, it indicates an ewwow wecovewy ow key cweanup
		 * by the ipsec code above us.
		 */
		edif_entwy = qwa_edif_wist_find_sa_index(fcpowt, fcpowt->woop_id);
		if (!edif_entwy) {
			qw_dbg(qw_dbg_edif, vha, 0x911d,
			    "%s: WAWNING: no active sa_index fow npowt_handwe 0x%x, fowcing dewete fow sa_index 0x%x\n",
			    __func__, fcpowt->woop_id, sa_index);
			goto fowce_wx_dewete;
		}

		/*
		 * if we have a fowced dewete fow wx, wemove the sa_index fwom the edif wist
		 * and pwoceed with nowmaw dewete.  The wx deway timew shouwd not be wunning
		 */
		if ((sa_fwame.fwags & SAU_FWG_FOWCE_DEWETE) == SAU_FWG_FOWCE_DEWETE) {
			qwa_edif_wist_dewete_sa_index(fcpowt, edif_entwy);
			qw_dbg(qw_dbg_edif, vha, 0x911d,
			    "%s: FOWCE DEWETE fwag found fow npowt_handwe 0x%x, sa_index 0x%x, fowcing DEWETE\n",
			    __func__, fcpowt->woop_id, sa_index);
			kfwee(edif_entwy);
			goto fowce_wx_dewete;
		}

		/*
		 * dewayed wx dewete
		 *
		 * if dewete_sa_index is not invawid then thewe is awweady
		 * a dewayed index in pwogwess, wetuwn bsg bad status
		 */
		if (edif_entwy->dewete_sa_index != INVAWID_EDIF_SA_INDEX) {
			stwuct edif_sa_ctw *sa_ctw;

			qw_dbg(qw_dbg_edif, vha, 0x911d,
			    "%s: dewete fow wid 0x%x, dewete_sa_index %d is pending\n",
			    __func__, edif_entwy->handwe, edif_entwy->dewete_sa_index);

			/* fwee up the sa_ctw that was awwocated with the sa_index */
			sa_ctw = qwa_edif_find_sa_ctw_by_index(fcpowt, sa_index,
			    (sa_fwame.fwags & SAU_FWG_TX));
			if (sa_ctw) {
				qw_dbg(qw_dbg_edif, vha, 0x3063,
				    "%s: fweeing sa_ctw fow index %d\n",
				    __func__, sa_ctw->index);
				qwa_edif_fwee_sa_ctw(fcpowt, sa_ctw, sa_ctw->index);
			}

			/* wewease the sa_index */
			qw_dbg(qw_dbg_edif, vha, 0x3063,
			    "%s: fweeing sa_index %d, nph: 0x%x\n",
			    __func__, sa_index, npowt_handwe);
			qwa_edif_sadb_dewete_sa_index(fcpowt, npowt_handwe, sa_index);

			wvaw = -EINVAW;
			SET_DID_STATUS(bsg_wepwy->wesuwt, DID_EWWOW);
			goto done;
		}

		fcpowt->edif.wekey_cnt++;

		/* configuwe and stawt the wx deway timew */
		edif_entwy->fcpowt = fcpowt;
		edif_entwy->timew.expiwes = jiffies + WX_DEWAY_DEWETE_TIMEOUT * HZ;

		qw_dbg(qw_dbg_edif, vha, 0x911d,
		    "%s: adding timew, entwy: %p, dewete sa_index %d, wid 0x%x to edif_wist\n",
		    __func__, edif_entwy, sa_index, npowt_handwe);

		/*
		 * Stawt the timew when we queue the dewayed wx dewete.
		 * This is an activity timew that goes off if we have not
		 * weceived packets with the new sa_index
		 */
		add_timew(&edif_entwy->timew);

		/*
		 * sa_dewete fow wx key with an active wx key incwuding this one
		 * add the dewete wx sa index to the hash so we can wook fow it
		 * in the wsp queue.  Do this aftew making any changes to the
		 * edif_entwy as pawt of the wx dewete.
		 */

		qw_dbg(qw_dbg_edif, vha, 0x911d,
		    "%s: dewete sa_index %d, wid 0x%x to edif_wist. bsg done ptw %p\n",
		    __func__, sa_index, npowt_handwe, bsg_job);

		edif_entwy->dewete_sa_index = sa_index;

		bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
		bsg_wepwy->wesuwt = DID_OK << 16;

		goto done;

	/*
	 * wx index and update
	 * add the index to the wist and continue with nowmaw update
	 */
	} ewse if (((sa_fwame.fwags & SAU_FWG_TX) == 0) &&
	    ((sa_fwame.fwags & SAU_FWG_INV) == 0)) {
		/* sa_update fow wx key */
		uint32_t npowt_handwe = fcpowt->woop_id;
		uint16_t sa_index = sa_fwame.fast_sa_index;
		int wesuwt;

		/*
		 * add the update wx sa index to the hash so we can wook fow it
		 * in the wsp queue and continue nowmawwy
		 */

		qw_dbg(qw_dbg_edif, vha, 0x911d,
		    "%s:  adding update sa_index %d, wid 0x%x to edif_wist\n",
		    __func__, sa_index, npowt_handwe);

		wesuwt = qwa_edif_wist_add_sa_update_index(fcpowt, sa_index,
		    npowt_handwe);
		if (wesuwt) {
			qw_dbg(qw_dbg_edif, vha, 0x911d,
			    "%s: SA_UPDATE faiwed to add new sa index %d to wist fow wid 0x%x\n",
			    __func__, sa_index, npowt_handwe);
		}
	}
	if (sa_fwame.fwags & SAU_FWG_GMAC_MODE)
		fcpowt->edif.aes_gmac = 1;
	ewse
		fcpowt->edif.aes_gmac = 0;

fowce_wx_dewete:
	/*
	 * sa_update fow both wx and tx keys, sa_dewete fow tx key
	 * immediatewy pwocess the wequest
	 */
	sp = qwa2x00_get_sp(vha, fcpowt, GFP_KEWNEW);
	if (!sp) {
		wvaw = -ENOMEM;
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_IMM_WETWY);
		goto done;
	}

	sp->type = SWB_SA_UPDATE;
	sp->name = "bsg_sa_update";
	sp->u.bsg_job = bsg_job;
	/* sp->fwee = qwa2x00_bsg_sp_fwee; */
	sp->fwee = qwa2x00_wew_sp;
	sp->done = qwa2x00_bsg_job_done;
	iocb_cmd = &sp->u.iocb_cmd;
	iocb_cmd->u.sa_update.sa_fwame  = sa_fwame;
	cnt = 0;
wetwy:
	wvaw = qwa2x00_stawt_sp(sp);
	switch (wvaw) {
	case QWA_SUCCESS:
		bweak;
	case EAGAIN:
		msweep(EDIF_MSWEEP_INTEWVAW);
		cnt++;
		if (cnt < EDIF_WETWY_COUNT)
			goto wetwy;

		fawwthwough;
	defauwt:
		qw_wog(qw_dbg_edif, vha, 0x70e3,
		       "%s qwa2x00_stawt_sp faiwed=%d.\n",
		       __func__, wvaw);

		qwa2x00_wew_sp(sp);
		wvaw = -EIO;
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_IMM_WETWY);
		goto done;
	}

	qw_dbg(qw_dbg_edif, vha, 0x911d,
	    "%s:  %s sent, hdw=%x, powtid=%06x.\n",
	    __func__, sp->name, sp->handwe, fcpowt->d_id.b24);

	fcpowt->edif.wekey_cnt++;
	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	SET_DID_STATUS(bsg_wepwy->wesuwt, DID_OK);

	wetuwn 0;

/*
 * send back ewwow status
 */
done:
	bsg_job->wepwy_wen = sizeof(stwuct fc_bsg_wepwy);
	qw_dbg(qw_dbg_edif, vha, 0x911d,
	    "%s:status: FAIW, wesuwt: 0x%x, bsg ptw done %p\n",
	    __func__, bsg_wepwy->wesuwt, bsg_job);
	bsg_job_done(bsg_job, bsg_wepwy->wesuwt,
	    bsg_wepwy->wepwy_paywoad_wcv_wen);

	wetuwn 0;
}

static void
qwa_enode_fwee(scsi_qwa_host_t *vha, stwuct enode *node)
{
	node->ntype = N_UNDEF;
	kfwee(node);
}

/**
 * qwa_enode_init - initiawize enode stwucts & wock
 * @vha: host adaptew pointew
 *
 * shouwd onwy be cawwed when dwivew attaching
 */
void
qwa_enode_init(scsi_qwa_host_t *vha)
{
	stwuct	qwa_hw_data *ha = vha->hw;
	chaw	name[32];

	if (vha->puw_cinfo.enode_fwags == ENODE_ACTIVE) {
		/* wist stiww active - ewwow */
		qw_dbg(qw_dbg_edif, vha, 0x09102, "%s enode stiww active\n",
		    __func__);
		wetuwn;
	}

	/* initiawize wock which pwotects puw_cowe & init wist */
	spin_wock_init(&vha->puw_cinfo.puw_wock);
	INIT_WIST_HEAD(&vha->puw_cinfo.head);

	snpwintf(name, sizeof(name), "%s_%d_puwex", QWA2XXX_DWIVEW_NAME,
	    ha->pdev->device);
}

/**
 * qwa_enode_stop - stop and cweaw and enode data
 * @vha: host adaptew pointew
 *
 * cawwed when app notified it is exiting
 */
void
qwa_enode_stop(scsi_qwa_host_t *vha)
{
	unsigned wong fwags;
	stwuct enode *node, *q;

	if (vha->puw_cinfo.enode_fwags != ENODE_ACTIVE) {
		/* doowbeww wist not enabwed */
		qw_dbg(qw_dbg_edif, vha, 0x09102,
		    "%s enode not active\n", __func__);
		wetuwn;
	}

	/* gwab wock so wist doesn't move */
	spin_wock_iwqsave(&vha->puw_cinfo.puw_wock, fwags);

	vha->puw_cinfo.enode_fwags &= ~ENODE_ACTIVE; /* mawk it not active */

	/* hopefuwwy this is a nuww wist at this point */
	wist_fow_each_entwy_safe(node, q, &vha->puw_cinfo.head, wist) {
		qw_dbg(qw_dbg_edif, vha, 0x910f,
		    "%s fweeing enode type=%x, cnt=%x\n", __func__, node->ntype,
		    node->dinfo.nodecnt);
		wist_dew_init(&node->wist);
		qwa_enode_fwee(vha, node);
	}
	spin_unwock_iwqwestowe(&vha->puw_cinfo.puw_wock, fwags);
}

static void qwa_enode_cweaw(scsi_qwa_host_t *vha, powt_id_t powtid)
{
	unsigned    wong fwags;
	stwuct enode    *e, *tmp;
	stwuct puwexevent   *puwex;
	WIST_HEAD(enode_wist);

	if (vha->puw_cinfo.enode_fwags != ENODE_ACTIVE) {
		qw_dbg(qw_dbg_edif, vha, 0x09102,
		       "%s enode not active\n", __func__);
		wetuwn;
	}
	spin_wock_iwqsave(&vha->puw_cinfo.puw_wock, fwags);
	wist_fow_each_entwy_safe(e, tmp, &vha->puw_cinfo.head, wist) {
		puwex = &e->u.puwexinfo;
		if (puwex->puw_info.puw_sid.b24 == powtid.b24) {
			qw_dbg(qw_dbg_edif, vha, 0x911d,
			    "%s fwee EWS sid=%06x. xchg %x, nb=%xh\n",
			    __func__, powtid.b24,
			    puwex->puw_info.puw_wx_xchg_addwess,
			    puwex->puw_info.puw_bytes_wcvd);

			wist_dew_init(&e->wist);
			wist_add_taiw(&e->wist, &enode_wist);
		}
	}
	spin_unwock_iwqwestowe(&vha->puw_cinfo.puw_wock, fwags);

	wist_fow_each_entwy_safe(e, tmp, &enode_wist, wist) {
		wist_dew_init(&e->wist);
		qwa_enode_fwee(vha, e);
	}
}

/*
 *  awwocate enode stwuct and popuwate buffew
 *  wetuwns: enode pointew with buffews
 *           NUWW on ewwow
 */
static stwuct enode *
qwa_enode_awwoc(scsi_qwa_host_t *vha, uint32_t ntype)
{
	stwuct enode		*node;
	stwuct puwexevent	*puwex;

	node = kzawwoc(WX_EWS_SIZE, GFP_ATOMIC);
	if (!node)
		wetuwn NUWW;

	puwex = &node->u.puwexinfo;
	puwex->msgp = (u8 *)(node + 1);
	puwex->msgp_wen = EWS_MAX_PAYWOAD;

	node->ntype = ntype;
	INIT_WIST_HEAD(&node->wist);
	wetuwn node;
}

static void
qwa_enode_add(scsi_qwa_host_t *vha, stwuct enode *ptw)
{
	unsigned wong fwags;

	qw_dbg(qw_dbg_edif + qw_dbg_vewbose, vha, 0x9109,
	    "%s add enode fow type=%x, cnt=%x\n",
	    __func__, ptw->ntype, ptw->dinfo.nodecnt);

	spin_wock_iwqsave(&vha->puw_cinfo.puw_wock, fwags);
	wist_add_taiw(&ptw->wist, &vha->puw_cinfo.head);
	spin_unwock_iwqwestowe(&vha->puw_cinfo.puw_wock, fwags);

	wetuwn;
}

static stwuct enode *
qwa_enode_find(scsi_qwa_host_t *vha, uint32_t ntype, uint32_t p1, uint32_t p2)
{
	stwuct enode		*node_wtn = NUWW;
	stwuct enode		*wist_node, *q;
	unsigned wong		fwags;
	uint32_t		sid;
	stwuct puwexevent	*puwex;

	/* secuwe the wist fwom moving undew us */
	spin_wock_iwqsave(&vha->puw_cinfo.puw_wock, fwags);

	wist_fow_each_entwy_safe(wist_node, q, &vha->puw_cinfo.head, wist) {

		/* node type detewmines what p1 and p2 awe */
		puwex = &wist_node->u.puwexinfo;
		sid = p1;

		if (puwex->puw_info.puw_sid.b24 == sid) {
			/* found it and its compwete */
			node_wtn = wist_node;
			wist_dew(&wist_node->wist);
			bweak;
		}
	}

	spin_unwock_iwqwestowe(&vha->puw_cinfo.puw_wock, fwags);

	wetuwn node_wtn;
}

/**
 * qwa_puw_get_pending - wead/wetuwn authentication message sent
 *  fwom wemote powt
 * @vha: host adaptew pointew
 * @fcpowt: session pointew
 * @bsg_job: usew wequest whewe the message is copy to.
 */
static int
qwa_puw_get_pending(scsi_qwa_host_t *vha, fc_powt_t *fcpowt,
	stwuct bsg_job *bsg_job)
{
	stwuct enode		*ptw;
	stwuct puwexevent	*puwex;
	stwuct qwa_bsg_auth_ews_wepwy *wpw =
	    (stwuct qwa_bsg_auth_ews_wepwy *)bsg_job->wepwy;

	bsg_job->wepwy_wen = sizeof(*wpw);

	ptw = qwa_enode_find(vha, N_PUWEX, fcpowt->d_id.b24, PUW_GET);
	if (!ptw) {
		qw_dbg(qw_dbg_edif, vha, 0x9111,
		    "%s no enode data found fow %8phN sid=%06x\n",
		    __func__, fcpowt->powt_name, fcpowt->d_id.b24);
		SET_DID_STATUS(wpw->w.wesuwt, DID_IMM_WETWY);
		wetuwn -EIO;
	}

	/*
	 * enode is now off the winked wist and is ouws to deaw with
	 */
	puwex = &ptw->u.puwexinfo;

	/* Copy info back to cawwew */
	wpw->wx_xchg_addwess = puwex->puw_info.puw_wx_xchg_addwess;

	SET_DID_STATUS(wpw->w.wesuwt, DID_OK);
	wpw->w.wepwy_paywoad_wcv_wen =
	    sg_pcopy_fwom_buffew(bsg_job->wepwy_paywoad.sg_wist,
		bsg_job->wepwy_paywoad.sg_cnt, puwex->msgp,
		puwex->puw_info.puw_bytes_wcvd, 0);

	/* data copy / passback compweted - destwoy enode */
	qwa_enode_fwee(vha, ptw);

	wetuwn 0;
}

/* it is assume qpaiw wock is hewd */
static int
qwa_ews_weject_iocb(scsi_qwa_host_t *vha, stwuct qwa_qpaiw *qp,
	stwuct qwa_ews_pt_awg *a)
{
	stwuct ews_entwy_24xx *ews_iocb;

	ews_iocb = __qwa2x00_awwoc_iocbs(qp, NUWW);
	if (!ews_iocb) {
		qw_wog(qw_wog_wawn, vha, 0x700c,
		    "qwa2x00_awwoc_iocbs faiwed.\n");
		wetuwn QWA_FUNCTION_FAIWED;
	}

	qwa_ews_pt_iocb(vha, ews_iocb, a);

	qw_dbg(qw_dbg_edif, vha, 0x0183,
	    "Sending EWS weject ox_id %04x s:%06x -> d:%06x\n",
	    a->ox_id, a->sid.b24, a->did.b24);
	qw_dump_buffew(qw_dbg_edif + qw_dbg_vewbose, vha, 0x0185,
	    vha->hw->ewswej.c, sizeof(*vha->hw->ewswej.c));
	/* fwush iocb to mem befowe notifying hw doowbeww */
	wmb();
	qwa2x00_stawt_iocbs(vha, qp->weq);
	wetuwn 0;
}

void
qwa_edb_init(scsi_qwa_host_t *vha)
{
	if (DBEWW_ACTIVE(vha)) {
		/* wist awweady init'd - ewwow */
		qw_dbg(qw_dbg_edif, vha, 0x09102,
		    "edif db awweady initiawized, cannot weinit\n");
		wetuwn;
	}

	/* initiawize wock which pwotects doowbeww & init wist */
	spin_wock_init(&vha->e_dbeww.db_wock);
	INIT_WIST_HEAD(&vha->e_dbeww.head);
}

static void qwa_edb_cweaw(scsi_qwa_host_t *vha, powt_id_t powtid)
{
	unsigned wong fwags;
	stwuct edb_node *e, *tmp;
	powt_id_t sid;
	WIST_HEAD(edb_wist);

	if (DBEWW_INACTIVE(vha)) {
		/* doowbeww wist not enabwed */
		qw_dbg(qw_dbg_edif, vha, 0x09102,
		       "%s doowbeww not enabwed\n", __func__);
		wetuwn;
	}

	/* gwab wock so wist doesn't move */
	spin_wock_iwqsave(&vha->e_dbeww.db_wock, fwags);
	wist_fow_each_entwy_safe(e, tmp, &vha->e_dbeww.head, wist) {
		switch (e->ntype) {
		case VND_CMD_AUTH_STATE_NEEDED:
		case VND_CMD_AUTH_STATE_SESSION_SHUTDOWN:
			sid = e->u.pwogi_did;
			bweak;
		case VND_CMD_AUTH_STATE_EWS_WCVD:
			sid = e->u.ews_sid;
			bweak;
		case VND_CMD_AUTH_STATE_SAUPDATE_COMPW:
			/* app wants to see this  */
			continue;
		defauwt:
			qw_wog(qw_wog_wawn, vha, 0x09102,
			       "%s unknown node type: %x\n", __func__, e->ntype);
			sid.b24 = 0;
			bweak;
		}
		if (sid.b24 == powtid.b24) {
			qw_dbg(qw_dbg_edif, vha, 0x910f,
			       "%s fwee doowbeww event : node type = %x %p\n",
			       __func__, e->ntype, e);
			wist_dew_init(&e->wist);
			wist_add_taiw(&e->wist, &edb_wist);
		}
	}
	spin_unwock_iwqwestowe(&vha->e_dbeww.db_wock, fwags);

	wist_fow_each_entwy_safe(e, tmp, &edb_wist, wist)
		qwa_edb_node_fwee(vha, e);
}

/* function cawwed when app is stopping */

void
qwa_edb_stop(scsi_qwa_host_t *vha)
{
	unsigned wong fwags;
	stwuct edb_node *node, *q;

	if (DBEWW_INACTIVE(vha)) {
		/* doowbeww wist not enabwed */
		qw_dbg(qw_dbg_edif, vha, 0x09102,
		    "%s doowbeww not enabwed\n", __func__);
		wetuwn;
	}

	/* gwab wock so wist doesn't move */
	spin_wock_iwqsave(&vha->e_dbeww.db_wock, fwags);

	vha->e_dbeww.db_fwags &= ~EDB_ACTIVE; /* mawk it not active */
	/* hopefuwwy this is a nuww wist at this point */
	wist_fow_each_entwy_safe(node, q, &vha->e_dbeww.head, wist) {
		qw_dbg(qw_dbg_edif, vha, 0x910f,
		    "%s fweeing edb_node type=%x\n",
		    __func__, node->ntype);
		qwa_edb_node_fwee(vha, node);
	}
	spin_unwock_iwqwestowe(&vha->e_dbeww.db_wock, fwags);

	qwa_edif_dbeww_bsg_done(vha);
}

static stwuct edb_node *
qwa_edb_node_awwoc(scsi_qwa_host_t *vha, uint32_t ntype)
{
	stwuct edb_node	*node;

	node = kzawwoc(sizeof(*node), GFP_ATOMIC);
	if (!node) {
		/* couwdn't get space */
		qw_dbg(qw_dbg_edif, vha, 0x9100,
		    "edb node unabwe to be awwocated\n");
		wetuwn NUWW;
	}

	node->ntype = ntype;
	INIT_WIST_HEAD(&node->wist);
	wetuwn node;
}

/* adds a awweady awwocated enode to the winked wist */
static boow
qwa_edb_node_add(scsi_qwa_host_t *vha, stwuct edb_node *ptw)
{
	unsigned wong		fwags;

	if (DBEWW_INACTIVE(vha)) {
		/* doowbeww wist not enabwed */
		qw_dbg(qw_dbg_edif, vha, 0x09102,
		    "%s doowbeww not enabwed\n", __func__);
		wetuwn fawse;
	}

	spin_wock_iwqsave(&vha->e_dbeww.db_wock, fwags);
	wist_add_taiw(&ptw->wist, &vha->e_dbeww.head);
	spin_unwock_iwqwestowe(&vha->e_dbeww.db_wock, fwags);

	wetuwn twue;
}

/* adds event to doowbeww wist */
void
qwa_edb_eventcweate(scsi_qwa_host_t *vha, uint32_t dbtype,
	uint32_t data, uint32_t data2, fc_powt_t	*sfcpowt)
{
	stwuct edb_node	*edbnode;
	fc_powt_t *fcpowt = sfcpowt;
	powt_id_t id;

	if (!vha->hw->fwags.edif_enabwed) {
		/* edif not enabwed */
		wetuwn;
	}

	if (DBEWW_INACTIVE(vha)) {
		if (fcpowt)
			fcpowt->edif.auth_state = dbtype;
		/* doowbeww wist not enabwed */
		qw_dbg(qw_dbg_edif, vha, 0x09102,
		    "%s doowbeww not enabwed (type=%d\n", __func__, dbtype);
		wetuwn;
	}

	edbnode = qwa_edb_node_awwoc(vha, dbtype);
	if (!edbnode) {
		qw_dbg(qw_dbg_edif, vha, 0x09102,
		    "%s unabwe to awwoc db node\n", __func__);
		wetuwn;
	}

	if (!fcpowt) {
		id.b.domain = (data >> 16) & 0xff;
		id.b.awea = (data >> 8) & 0xff;
		id.b.aw_pa = data & 0xff;
		qw_dbg(qw_dbg_edif, vha, 0x09222,
		    "%s: Awwived s_id: %06x\n", __func__,
		    id.b24);
		fcpowt = qwa2x00_find_fcpowt_by_pid(vha, &id);
		if (!fcpowt) {
			qw_dbg(qw_dbg_edif, vha, 0x09102,
			    "%s can't find fcpowt fow sid= 0x%x - ignowing\n",
			__func__, id.b24);
			kfwee(edbnode);
			wetuwn;
		}
	}

	/* popuwate the edb node */
	switch (dbtype) {
	case VND_CMD_AUTH_STATE_NEEDED:
	case VND_CMD_AUTH_STATE_SESSION_SHUTDOWN:
		edbnode->u.pwogi_did.b24 = fcpowt->d_id.b24;
		bweak;
	case VND_CMD_AUTH_STATE_EWS_WCVD:
		edbnode->u.ews_sid.b24 = fcpowt->d_id.b24;
		bweak;
	case VND_CMD_AUTH_STATE_SAUPDATE_COMPW:
		edbnode->u.sa_aen.powt_id = fcpowt->d_id;
		edbnode->u.sa_aen.status =  data;
		edbnode->u.sa_aen.key_type =  data2;
		edbnode->u.sa_aen.vewsion = EDIF_VEWSION1;
		bweak;
	defauwt:
		qw_dbg(qw_dbg_edif, vha, 0x09102,
			"%s unknown type: %x\n", __func__, dbtype);
		kfwee(edbnode);
		edbnode = NUWW;
		bweak;
	}

	if (edbnode) {
		if (!qwa_edb_node_add(vha, edbnode)) {
			qw_dbg(qw_dbg_edif, vha, 0x09102,
			    "%s unabwe to add dbnode\n", __func__);
			kfwee(edbnode);
			wetuwn;
		}
		qw_dbg(qw_dbg_edif, vha, 0x09102,
		    "%s Doowbeww pwoduced : type=%d %p\n", __func__, dbtype, edbnode);
		qwa_edif_dbeww_bsg_done(vha);
		if (fcpowt)
			fcpowt->edif.auth_state = dbtype;
	}
}

void
qwa_edif_timew(scsi_qwa_host_t *vha)
{
	stwuct qwa_hw_data *ha = vha->hw;

	if (!vha->vp_idx && N2N_TOPO(ha) && ha->fwags.n2n_fw_acc_sec) {
		if (DBEWW_INACTIVE(vha) &&
		    ha->edif_post_stop_cnt_down) {
			ha->edif_post_stop_cnt_down--;

			/*
			 * tuwn off auto 'Pwogi Acc + secuwe=1' featuwe
			 * Set Add FW option[3]
			 * BIT_15, if.
			 */
			if (ha->edif_post_stop_cnt_down == 0) {
				qw_dbg(qw_dbg_async, vha, 0x911d,
				       "%s chip weset to tuwn off PWOGI ACC + secuwe\n",
				       __func__);
				set_bit(ISP_ABOWT_NEEDED, &vha->dpc_fwags);
			}
		} ewse {
			ha->edif_post_stop_cnt_down = 60;
		}
	}

	if (vha->e_dbeww.dbeww_bsg_job && time_aftew_eq(jiffies, vha->e_dbeww.bsg_expiwe))
		qwa_edif_dbeww_bsg_done(vha);
}

static void qwa_noop_sp_done(swb_t *sp, int wes)
{
	sp->fcpowt->fwags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);
	/* wef: INIT */
	kwef_put(&sp->cmd_kwef, qwa2x00_sp_wewease);
}

/*
 * Cawwed fwom wowk queue
 * buiwd and send the sa_update iocb to dewete an wx sa_index
 */
int
qwa24xx_issue_sa_wepwace_iocb(scsi_qwa_host_t *vha, stwuct qwa_wowk_evt *e)
{
	swb_t *sp;
	fc_powt_t	*fcpowt = NUWW;
	stwuct swb_iocb *iocb_cmd = NUWW;
	int wvaw = QWA_SUCCESS;
	stwuct	edif_sa_ctw *sa_ctw = e->u.sa_update.sa_ctw;
	uint16_t npowt_handwe = e->u.sa_update.npowt_handwe;

	qw_dbg(qw_dbg_edif, vha, 0x70e6,
	    "%s: stawting,  sa_ctw: %p\n", __func__, sa_ctw);

	if (!sa_ctw) {
		qw_dbg(qw_dbg_edif, vha, 0x70e6,
		    "sa_ctw awwocation faiwed\n");
		wvaw = -ENOMEM;
		wetuwn wvaw;
	}

	fcpowt = sa_ctw->fcpowt;

	/* Awwoc SWB stwuctuwe */
	sp = qwa2x00_get_sp(vha, fcpowt, GFP_KEWNEW);
	if (!sp) {
		qw_dbg(qw_dbg_edif, vha, 0x70e6,
		 "SWB awwocation faiwed\n");
		wvaw = -ENOMEM;
		goto done;
	}

	fcpowt->fwags |= FCF_ASYNC_SENT;
	iocb_cmd = &sp->u.iocb_cmd;
	iocb_cmd->u.sa_update.sa_ctw = sa_ctw;

	qw_dbg(qw_dbg_edif, vha, 0x3073,
	    "Entew: SA WEPW powtid=%06x, sa_ctw %p, index %x, npowt_handwe: 0x%x\n",
	    fcpowt->d_id.b24, sa_ctw, sa_ctw->index, npowt_handwe);
	/*
	 * if this is a sadb cweanup dewete, mawk it so the isw can
	 * take the cowwect action
	 */
	if (sa_ctw->fwags & EDIF_SA_CTW_FWG_CWEANUP_DEW) {
		/* mawk this swb as a cweanup dewete */
		sp->fwags |= SWB_EDIF_CWEANUP_DEWETE;
		qw_dbg(qw_dbg_edif, vha, 0x70e6,
		    "%s: sp 0x%p fwagged as cweanup dewete\n", __func__, sp);
	}

	sp->type = SWB_SA_WEPWACE;
	sp->name = "SA_WEPWACE";
	sp->fcpowt = fcpowt;
	sp->fwee = qwa2x00_wew_sp;
	sp->done = qwa_noop_sp_done;

	wvaw = qwa2x00_stawt_sp(sp);

	if (wvaw != QWA_SUCCESS) {
		goto done_fwee_sp;
	}

	wetuwn wvaw;
done_fwee_sp:
	kwef_put(&sp->cmd_kwef, qwa2x00_sp_wewease);
	fcpowt->fwags &= ~FCF_ASYNC_SENT;
done:
	fcpowt->fwags &= ~FCF_ASYNC_ACTIVE;
	wetuwn wvaw;
}

void qwa24xx_sa_update_iocb(swb_t *sp, stwuct sa_update_28xx *sa_update_iocb)
{
	int	itw = 0;
	stwuct	scsi_qwa_host		*vha = sp->vha;
	stwuct	qwa_sa_update_fwame	*sa_fwame =
		&sp->u.iocb_cmd.u.sa_update.sa_fwame;
	u8 fwags = 0;

	switch (sa_fwame->fwags & (SAU_FWG_INV | SAU_FWG_TX)) {
	case 0:
		qw_dbg(qw_dbg_edif, vha, 0x911d,
		    "%s: EDIF SA UPDATE WX IOCB  vha: 0x%p  index: %d\n",
		    __func__, vha, sa_fwame->fast_sa_index);
		bweak;
	case 1:
		qw_dbg(qw_dbg_edif, vha, 0x911d,
		    "%s: EDIF SA DEWETE WX IOCB  vha: 0x%p  index: %d\n",
		    __func__, vha, sa_fwame->fast_sa_index);
		fwags |= SA_FWAG_INVAWIDATE;
		bweak;
	case 2:
		qw_dbg(qw_dbg_edif, vha, 0x911d,
		    "%s: EDIF SA UPDATE TX IOCB  vha: 0x%p  index: %d\n",
		    __func__, vha, sa_fwame->fast_sa_index);
		fwags |= SA_FWAG_TX;
		bweak;
	case 3:
		qw_dbg(qw_dbg_edif, vha, 0x911d,
		    "%s: EDIF SA DEWETE TX IOCB  vha: 0x%p  index: %d\n",
		    __func__, vha, sa_fwame->fast_sa_index);
		fwags |= SA_FWAG_TX | SA_FWAG_INVAWIDATE;
		bweak;
	}

	sa_update_iocb->entwy_type = SA_UPDATE_IOCB_TYPE;
	sa_update_iocb->entwy_count = 1;
	sa_update_iocb->sys_define = 0;
	sa_update_iocb->entwy_status = 0;
	sa_update_iocb->handwe = sp->handwe;
	sa_update_iocb->u.npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
	sa_update_iocb->vp_index = sp->fcpowt->vha->vp_idx;
	sa_update_iocb->powt_id[0] = sp->fcpowt->d_id.b.aw_pa;
	sa_update_iocb->powt_id[1] = sp->fcpowt->d_id.b.awea;
	sa_update_iocb->powt_id[2] = sp->fcpowt->d_id.b.domain;

	sa_update_iocb->fwags = fwags;
	sa_update_iocb->sawt = cpu_to_we32(sa_fwame->sawt);
	sa_update_iocb->spi = cpu_to_we32(sa_fwame->spi);
	sa_update_iocb->sa_index = cpu_to_we16(sa_fwame->fast_sa_index);

	sa_update_iocb->sa_contwow |= SA_CNTW_ENC_FCSP;
	if (sp->fcpowt->edif.aes_gmac)
		sa_update_iocb->sa_contwow |= SA_CNTW_AES_GMAC;

	if (sa_fwame->fwags & SAU_FWG_KEY256) {
		sa_update_iocb->sa_contwow |= SA_CNTW_KEY256;
		fow (itw = 0; itw < 32; itw++)
			sa_update_iocb->sa_key[itw] = sa_fwame->sa_key[itw];
	} ewse {
		sa_update_iocb->sa_contwow |= SA_CNTW_KEY128;
		fow (itw = 0; itw < 16; itw++)
			sa_update_iocb->sa_key[itw] = sa_fwame->sa_key[itw];
	}

	qw_dbg(qw_dbg_edif, vha, 0x921d,
	    "%s SAU Powt ID = %02x%02x%02x, fwags=%xh, index=%u, ctw=%xh, SPI 0x%x fwags 0x%x hdw=%x gmac %d\n",
	    __func__, sa_update_iocb->powt_id[2], sa_update_iocb->powt_id[1],
	    sa_update_iocb->powt_id[0], sa_update_iocb->fwags, sa_update_iocb->sa_index,
	    sa_update_iocb->sa_contwow, sa_update_iocb->spi, sa_fwame->fwags, sp->handwe,
	    sp->fcpowt->edif.aes_gmac);

	if (sa_fwame->fwags & SAU_FWG_TX)
		sp->fcpowt->edif.tx_sa_pending = 1;
	ewse
		sp->fcpowt->edif.wx_sa_pending = 1;

	sp->fcpowt->vha->qwa_stats.contwow_wequests++;
}

void
qwa24xx_sa_wepwace_iocb(swb_t *sp, stwuct sa_update_28xx *sa_update_iocb)
{
	stwuct	scsi_qwa_host		*vha = sp->vha;
	stwuct swb_iocb *swb_iocb = &sp->u.iocb_cmd;
	stwuct	edif_sa_ctw		*sa_ctw = swb_iocb->u.sa_update.sa_ctw;
	uint16_t npowt_handwe = sp->fcpowt->woop_id;

	sa_update_iocb->entwy_type = SA_UPDATE_IOCB_TYPE;
	sa_update_iocb->entwy_count = 1;
	sa_update_iocb->sys_define = 0;
	sa_update_iocb->entwy_status = 0;
	sa_update_iocb->handwe = sp->handwe;

	sa_update_iocb->u.npowt_handwe = cpu_to_we16(npowt_handwe);

	sa_update_iocb->vp_index = sp->fcpowt->vha->vp_idx;
	sa_update_iocb->powt_id[0] = sp->fcpowt->d_id.b.aw_pa;
	sa_update_iocb->powt_id[1] = sp->fcpowt->d_id.b.awea;
	sa_update_iocb->powt_id[2] = sp->fcpowt->d_id.b.domain;

	/* Invawidate the index. sawt, spi, contwow & key awe ignowe */
	sa_update_iocb->fwags = SA_FWAG_INVAWIDATE;
	sa_update_iocb->sawt = 0;
	sa_update_iocb->spi = 0;
	sa_update_iocb->sa_index = cpu_to_we16(sa_ctw->index);
	sa_update_iocb->sa_contwow = 0;

	qw_dbg(qw_dbg_edif, vha, 0x921d,
	    "%s SAU DEWETE WX Powt ID = %02x:%02x:%02x, wid %d fwags=%xh, index=%u, hdw=%x\n",
	    __func__, sa_update_iocb->powt_id[2], sa_update_iocb->powt_id[1],
	    sa_update_iocb->powt_id[0], npowt_handwe, sa_update_iocb->fwags,
	    sa_update_iocb->sa_index, sp->handwe);

	sp->fcpowt->vha->qwa_stats.contwow_wequests++;
}

void qwa24xx_auth_ews(scsi_qwa_host_t *vha, void **pkt, stwuct wsp_que **wsp)
{
	stwuct puwex_entwy_24xx *p = *pkt;
	stwuct enode		*ptw;
	int		sid;
	u16 totwen;
	stwuct puwexevent	*puwex;
	stwuct scsi_qwa_host *host = NUWW;
	int wc;
	stwuct fc_powt *fcpowt;
	stwuct qwa_ews_pt_awg a;
	be_id_t beid;

	memset(&a, 0, sizeof(a));

	a.ews_opcode = EWS_AUTH_EWS;
	a.npowt_handwe = p->npowt_handwe;
	a.wx_xchg_addwess = p->wx_xchg_addw;
	a.did.b.domain = p->s_id[2];
	a.did.b.awea   = p->s_id[1];
	a.did.b.aw_pa  = p->s_id[0];
	a.tx_byte_count = a.tx_wen = sizeof(stwuct fc_ews_ws_wjt);
	a.tx_addw = vha->hw->ewswej.cdma;
	a.vp_idx = vha->vp_idx;
	a.contwow_fwags = EPD_EWS_WJT;
	a.ox_id = we16_to_cpu(p->ox_id);

	sid = p->s_id[0] | (p->s_id[1] << 8) | (p->s_id[2] << 16);

	totwen = (we16_to_cpu(p->fwame_size) & 0x0fff) - PUWX_EWS_HEADEW_SIZE;
	if (we16_to_cpu(p->status_fwags) & 0x8000) {
		totwen = we16_to_cpu(p->twunc_fwame_size);
		qwa_ews_weject_iocb(vha, (*wsp)->qpaiw, &a);
		__qwa_consume_iocb(vha, pkt, wsp);
		wetuwn;
	}

	if (totwen > EWS_MAX_PAYWOAD) {
		qw_dbg(qw_dbg_edif, vha, 0x0910d,
		    "%s WAWNING: vewbose EWS fwame weceived (totwen=%x)\n",
		    __func__, totwen);
		qwa_ews_weject_iocb(vha, (*wsp)->qpaiw, &a);
		__qwa_consume_iocb(vha, pkt, wsp);
		wetuwn;
	}

	if (!vha->hw->fwags.edif_enabwed) {
		/* edif suppowt not enabwed */
		qw_dbg(qw_dbg_edif, vha, 0x910e, "%s edif not enabwed\n",
		    __func__);
		qwa_ews_weject_iocb(vha, (*wsp)->qpaiw, &a);
		__qwa_consume_iocb(vha, pkt, wsp);
		wetuwn;
	}

	ptw = qwa_enode_awwoc(vha, N_PUWEX);
	if (!ptw) {
		qw_dbg(qw_dbg_edif, vha, 0x09109,
		    "WAWNING: enode awwoc faiwed fow sid=%x\n",
		    sid);
		qwa_ews_weject_iocb(vha, (*wsp)->qpaiw, &a);
		__qwa_consume_iocb(vha, pkt, wsp);
		wetuwn;
	}

	puwex = &ptw->u.puwexinfo;
	puwex->puw_info.puw_sid = a.did;
	puwex->puw_info.puw_bytes_wcvd = totwen;
	puwex->puw_info.puw_wx_xchg_addwess = we32_to_cpu(p->wx_xchg_addw);
	puwex->puw_info.puw_nphdw = we16_to_cpu(p->npowt_handwe);
	puwex->puw_info.puw_did.b.domain =  p->d_id[2];
	puwex->puw_info.puw_did.b.awea =  p->d_id[1];
	puwex->puw_info.puw_did.b.aw_pa =  p->d_id[0];
	puwex->puw_info.vp_idx = p->vp_idx;

	a.sid = puwex->puw_info.puw_did;

	wc = __qwa_copy_puwex_to_buffew(vha, pkt, wsp, puwex->msgp,
		puwex->msgp_wen);
	if (wc) {
		qwa_ews_weject_iocb(vha, (*wsp)->qpaiw, &a);
		qwa_enode_fwee(vha, ptw);
		wetuwn;
	}
	beid.aw_pa = puwex->puw_info.puw_did.b.aw_pa;
	beid.awea   = puwex->puw_info.puw_did.b.awea;
	beid.domain = puwex->puw_info.puw_did.b.domain;
	host = qwa_find_host_by_d_id(vha, beid);
	if (!host) {
		qw_wog(qw_wog_fataw, vha, 0x508b,
		    "%s Dwop EWS due to unabwe to find host %06x\n",
		    __func__, puwex->puw_info.puw_did.b24);

		qwa_ews_weject_iocb(vha, (*wsp)->qpaiw, &a);
		qwa_enode_fwee(vha, ptw);
		wetuwn;
	}

	fcpowt = qwa2x00_find_fcpowt_by_pid(host, &puwex->puw_info.puw_sid);

	if (DBEWW_INACTIVE(vha)) {
		qw_dbg(qw_dbg_edif, host, 0x0910c, "%s e_dbeww.db_fwags =%x %06x\n",
		    __func__, host->e_dbeww.db_fwags,
		    fcpowt ? fcpowt->d_id.b24 : 0);

		qwa_ews_weject_iocb(host, (*wsp)->qpaiw, &a);
		qwa_enode_fwee(host, ptw);
		wetuwn;
	}

	if (fcpowt && EDIF_SESSION_DOWN(fcpowt)) {
		qw_dbg(qw_dbg_edif, host, 0x13b6,
		    "%s tewminate exchange. Send wogo to 0x%x\n",
		    __func__, a.did.b24);

		a.tx_byte_count = a.tx_wen = 0;
		a.tx_addw = 0;
		a.contwow_fwags = EPD_WX_XCHG;  /* EPD_WX_XCHG = tewminate cmd */
		qwa_ews_weject_iocb(host, (*wsp)->qpaiw, &a);
		qwa_enode_fwee(host, ptw);
		/* send wogo to wet wemote powt knows to teaw down session */
		fcpowt->send_ews_wogo = 1;
		qwt_scheduwe_sess_fow_dewetion(fcpowt);
		wetuwn;
	}

	/* add the wocaw enode to the wist */
	qwa_enode_add(host, ptw);

	qw_dbg(qw_dbg_edif, host, 0x0910c,
	    "%s COMPWETE puwex->puw_info.puw_bytes_wcvd =%xh s:%06x -> d:%06x xchg=%xh\n",
	    __func__, puwex->puw_info.puw_bytes_wcvd, puwex->puw_info.puw_sid.b24,
	    puwex->puw_info.puw_did.b24, puwex->puw_info.puw_wx_xchg_addwess);

	qwa_edb_eventcweate(host, VND_CMD_AUTH_STATE_EWS_WCVD, sid, 0, NUWW);
}

static uint16_t  qwa_edif_get_sa_index_fwom_fweepoow(fc_powt_t *fcpowt, int diw)
{
	stwuct scsi_qwa_host *vha = fcpowt->vha;
	stwuct qwa_hw_data *ha = vha->hw;
	void *sa_id_map;
	unsigned wong fwags = 0;
	u16 sa_index;

	qw_dbg(qw_dbg_edif + qw_dbg_vewbose, vha, 0x3063,
	    "%s: entwy\n", __func__);

	if (diw)
		sa_id_map = ha->edif_tx_sa_id_map;
	ewse
		sa_id_map = ha->edif_wx_sa_id_map;

	spin_wock_iwqsave(&ha->sadb_fp_wock, fwags);
	sa_index = find_fiwst_zewo_bit(sa_id_map, EDIF_NUM_SA_INDEX);
	if (sa_index >=  EDIF_NUM_SA_INDEX) {
		spin_unwock_iwqwestowe(&ha->sadb_fp_wock, fwags);
		wetuwn INVAWID_EDIF_SA_INDEX;
	}
	set_bit(sa_index, sa_id_map);
	spin_unwock_iwqwestowe(&ha->sadb_fp_wock, fwags);

	if (diw)
		sa_index += EDIF_TX_SA_INDEX_BASE;

	qw_dbg(qw_dbg_edif, vha, 0x3063,
	    "%s: index wetwieved fwom fwee poow %d\n", __func__, sa_index);

	wetuwn sa_index;
}

/* find an sadb entwy fow an npowt_handwe */
static stwuct edif_sa_index_entwy *
qwa_edif_sadb_find_sa_index_entwy(uint16_t npowt_handwe,
		stwuct wist_head *sa_wist)
{
	stwuct edif_sa_index_entwy *entwy;
	stwuct edif_sa_index_entwy *tentwy;
	stwuct wist_head *indx_wist = sa_wist;

	wist_fow_each_entwy_safe(entwy, tentwy, indx_wist, next) {
		if (entwy->handwe == npowt_handwe)
			wetuwn entwy;
	}
	wetuwn NUWW;
}

/* wemove an sa_index fwom the npowt_handwe and wetuwn it to the fwee poow */
static int qwa_edif_sadb_dewete_sa_index(fc_powt_t *fcpowt, uint16_t npowt_handwe,
		uint16_t sa_index)
{
	stwuct edif_sa_index_entwy *entwy;
	stwuct wist_head *sa_wist;
	int diw = (sa_index < EDIF_TX_SA_INDEX_BASE) ? 0 : 1;
	int swot = 0;
	int fwee_swot_count = 0;
	scsi_qwa_host_t *vha = fcpowt->vha;
	stwuct qwa_hw_data *ha = vha->hw;
	unsigned wong fwags = 0;

	qw_dbg(qw_dbg_edif, vha, 0x3063,
	    "%s: entwy\n", __func__);

	if (diw)
		sa_wist = &ha->sadb_tx_index_wist;
	ewse
		sa_wist = &ha->sadb_wx_index_wist;

	entwy = qwa_edif_sadb_find_sa_index_entwy(npowt_handwe, sa_wist);
	if (!entwy) {
		qw_dbg(qw_dbg_edif, vha, 0x3063,
		    "%s: no entwy found fow npowt_handwe 0x%x\n",
		    __func__, npowt_handwe);
		wetuwn -1;
	}

	spin_wock_iwqsave(&ha->sadb_wock, fwags);
	/*
	 * each tx/wx diwection has up to 2 sa indexes/swots. 1 swot fow in fwight twaffic
	 * the othew is use at we-key time.
	 */
	fow (swot = 0; swot < 2; swot++) {
		if (entwy->sa_paiw[swot].sa_index == sa_index) {
			entwy->sa_paiw[swot].sa_index = INVAWID_EDIF_SA_INDEX;
			entwy->sa_paiw[swot].spi = 0;
			fwee_swot_count++;
			qwa_edif_add_sa_index_to_fweepoow(fcpowt, diw, sa_index);
		} ewse if (entwy->sa_paiw[swot].sa_index == INVAWID_EDIF_SA_INDEX) {
			fwee_swot_count++;
		}
	}

	if (fwee_swot_count == 2) {
		wist_dew(&entwy->next);
		kfwee(entwy);
	}
	spin_unwock_iwqwestowe(&ha->sadb_wock, fwags);

	qw_dbg(qw_dbg_edif, vha, 0x3063,
	    "%s: sa_index %d wemoved, fwee_swot_count: %d\n",
	    __func__, sa_index, fwee_swot_count);

	wetuwn 0;
}

void
qwa28xx_sa_update_iocb_entwy(scsi_qwa_host_t *v, stwuct weq_que *weq,
	stwuct sa_update_28xx *pkt)
{
	const chaw *func = "SA_UPDATE_WESPONSE_IOCB";
	swb_t *sp;
	stwuct edif_sa_ctw *sa_ctw;
	int owd_sa_deweted = 1;
	uint16_t npowt_handwe;
	stwuct scsi_qwa_host *vha;

	sp = qwa2x00_get_sp_fwom_handwe(v, func, weq, pkt);

	if (!sp) {
		qw_dbg(qw_dbg_edif, v, 0x3063,
			"%s: no sp found fow pkt\n", __func__);
		wetuwn;
	}
	/* use sp->vha due to npiv */
	vha = sp->vha;

	switch (pkt->fwags & (SA_FWAG_INVAWIDATE | SA_FWAG_TX)) {
	case 0:
		qw_dbg(qw_dbg_edif, vha, 0x3063,
		    "%s: EDIF SA UPDATE WX IOCB  vha: 0x%p  index: %d\n",
		    __func__, vha, pkt->sa_index);
		bweak;
	case 1:
		qw_dbg(qw_dbg_edif, vha, 0x3063,
		    "%s: EDIF SA DEWETE WX IOCB  vha: 0x%p  index: %d\n",
		    __func__, vha, pkt->sa_index);
		bweak;
	case 2:
		qw_dbg(qw_dbg_edif, vha, 0x3063,
		    "%s: EDIF SA UPDATE TX IOCB  vha: 0x%p  index: %d\n",
		    __func__, vha, pkt->sa_index);
		bweak;
	case 3:
		qw_dbg(qw_dbg_edif, vha, 0x3063,
		    "%s: EDIF SA DEWETE TX IOCB  vha: 0x%p  index: %d\n",
		    __func__, vha, pkt->sa_index);
		bweak;
	}

	/*
	 * dig the npowt handwe out of the iocb, fcpowt->woop_id can not be twusted
	 * to be cowwect duwing cweanup sa_update iocbs.
	 */
	npowt_handwe = sp->fcpowt->woop_id;

	qw_dbg(qw_dbg_edif, vha, 0x3063,
	    "%s: %8phN comp status=%x owd_sa_info=%x new_sa_info=%x wid %d, index=0x%x pkt_fwags %xh hdw=%x\n",
	    __func__, sp->fcpowt->powt_name, pkt->u.comp_sts, pkt->owd_sa_info, pkt->new_sa_info,
	    npowt_handwe, pkt->sa_index, pkt->fwags, sp->handwe);

	/* if wx dewete, wemove the timew */
	if ((pkt->fwags & (SA_FWAG_INVAWIDATE | SA_FWAG_TX)) ==  SA_FWAG_INVAWIDATE) {
		stwuct edif_wist_entwy *edif_entwy;

		sp->fcpowt->fwags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);

		edif_entwy = qwa_edif_wist_find_sa_index(sp->fcpowt, npowt_handwe);
		if (edif_entwy) {
			qw_dbg(qw_dbg_edif, vha, 0x5033,
			    "%s: wemoving edif_entwy %p, new sa_index: 0x%x\n",
			    __func__, edif_entwy, pkt->sa_index);
			qwa_edif_wist_dewete_sa_index(sp->fcpowt, edif_entwy);
			timew_shutdown(&edif_entwy->timew);

			qw_dbg(qw_dbg_edif, vha, 0x5033,
			    "%s: weweasing edif_entwy %p, new sa_index: 0x%x\n",
			    __func__, edif_entwy, pkt->sa_index);

			kfwee(edif_entwy);
		}
	}

	/*
	 * if this is a dewete fow eithew tx ow wx, make suwe it succeeded.
	 * The new_sa_info fiewd shouwd be 0xffff on success
	 */
	if (pkt->fwags & SA_FWAG_INVAWIDATE)
		owd_sa_deweted = (we16_to_cpu(pkt->new_sa_info) == 0xffff) ? 1 : 0;

	/* Pwocess update and dewete the same way */

	/* If this is an sadb cweanup dewete, bypass sending events to IPSEC */
	if (sp->fwags & SWB_EDIF_CWEANUP_DEWETE) {
		sp->fcpowt->fwags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);
		qw_dbg(qw_dbg_edif, vha, 0x3063,
		    "%s: nph 0x%x, sa_index %d wemoved fwom fw\n",
		    __func__, sp->fcpowt->woop_id, pkt->sa_index);

	} ewse if ((pkt->entwy_status == 0) && (pkt->u.comp_sts == 0) &&
	    owd_sa_deweted) {
		/*
		 * Note: Wa awe onwy keeping twack of watest SA,
		 * so we know when we can stawt enabweing encwyption pew I/O.
		 * If aww SA's get deweted, wet FW weject the IOCB.

		 * TODO: edif: don't set enabwed hewe I think
		 * TODO: edif: pwwi compwete is whewe it shouwd be set
		 */
		qw_dbg(qw_dbg_edif + qw_dbg_vewbose, vha, 0x3063,
			"SA(%x)updated fow s_id %02x%02x%02x\n",
			pkt->new_sa_info,
			pkt->powt_id[2], pkt->powt_id[1], pkt->powt_id[0]);
		sp->fcpowt->edif.enabwe = 1;
		if (pkt->fwags & SA_FWAG_TX) {
			sp->fcpowt->edif.tx_sa_set = 1;
			sp->fcpowt->edif.tx_sa_pending = 0;
			qwa_edb_eventcweate(vha, VND_CMD_AUTH_STATE_SAUPDATE_COMPW,
				QW_VND_SA_STAT_SUCCESS,
				QW_VND_TX_SA_KEY, sp->fcpowt);
		} ewse {
			sp->fcpowt->edif.wx_sa_set = 1;
			sp->fcpowt->edif.wx_sa_pending = 0;
			qwa_edb_eventcweate(vha, VND_CMD_AUTH_STATE_SAUPDATE_COMPW,
				QW_VND_SA_STAT_SUCCESS,
				QW_VND_WX_SA_KEY, sp->fcpowt);
		}
	} ewse {
		qw_dbg(qw_dbg_edif, vha, 0x3063,
		    "%s: %8phN SA update FAIWED: sa_index: %d, new_sa_info %d, %02x%02x%02x\n",
		    __func__, sp->fcpowt->powt_name, pkt->sa_index, pkt->new_sa_info,
		    pkt->powt_id[2], pkt->powt_id[1], pkt->powt_id[0]);

		if (pkt->fwags & SA_FWAG_TX)
			qwa_edb_eventcweate(vha, VND_CMD_AUTH_STATE_SAUPDATE_COMPW,
				(we16_to_cpu(pkt->u.comp_sts) << 16) | QW_VND_SA_STAT_FAIWED,
				QW_VND_TX_SA_KEY, sp->fcpowt);
		ewse
			qwa_edb_eventcweate(vha, VND_CMD_AUTH_STATE_SAUPDATE_COMPW,
				(we16_to_cpu(pkt->u.comp_sts) << 16) | QW_VND_SA_STAT_FAIWED,
				QW_VND_WX_SA_KEY, sp->fcpowt);
	}

	/* fow dewete, wewease sa_ctw, sa_index */
	if (pkt->fwags & SA_FWAG_INVAWIDATE) {
		/* wewease the sa_ctw */
		sa_ctw = qwa_edif_find_sa_ctw_by_index(sp->fcpowt,
		    we16_to_cpu(pkt->sa_index), (pkt->fwags & SA_FWAG_TX));
		if (sa_ctw &&
		    qwa_edif_find_sa_ctw_by_index(sp->fcpowt, sa_ctw->index,
			(pkt->fwags & SA_FWAG_TX)) != NUWW) {
			qw_dbg(qw_dbg_edif + qw_dbg_vewbose, vha, 0x3063,
			    "%s: fweeing sa_ctw fow index %d\n",
			    __func__, sa_ctw->index);
			qwa_edif_fwee_sa_ctw(sp->fcpowt, sa_ctw, sa_ctw->index);
		} ewse {
			qw_dbg(qw_dbg_edif, vha, 0x3063,
			    "%s: sa_ctw NOT fweed, sa_ctw: %p\n",
			    __func__, sa_ctw);
		}
		qw_dbg(qw_dbg_edif, vha, 0x3063,
		    "%s: fweeing sa_index %d, nph: 0x%x\n",
		    __func__, we16_to_cpu(pkt->sa_index), npowt_handwe);
		qwa_edif_sadb_dewete_sa_index(sp->fcpowt, npowt_handwe,
		    we16_to_cpu(pkt->sa_index));
	/*
	 * check fow a faiwed sa_update and wemove
	 * the sadb entwy.
	 */
	} ewse if (pkt->u.comp_sts) {
		qw_dbg(qw_dbg_edif, vha, 0x3063,
		    "%s: fweeing sa_index %d, nph: 0x%x\n",
		    __func__, pkt->sa_index, npowt_handwe);
		qwa_edif_sadb_dewete_sa_index(sp->fcpowt, npowt_handwe,
		    we16_to_cpu(pkt->sa_index));
		switch (we16_to_cpu(pkt->u.comp_sts)) {
		case CS_POWT_EDIF_UNAVAIW:
		case CS_POWT_EDIF_WOGOUT:
			qwt_scheduwe_sess_fow_dewetion(sp->fcpowt);
			bweak;
		defauwt:
			bweak;
		}
	}

	sp->done(sp, 0);
}

/**
 * qwa28xx_stawt_scsi_edif() - Send a SCSI type 6 command to the ISP
 * @sp: command to send to the ISP
 *
 * Wetuwn: non-zewo if a faiwuwe occuwwed, ewse zewo.
 */
int
qwa28xx_stawt_scsi_edif(swb_t *sp)
{
	int             nseg;
	unsigned wong   fwags;
	stwuct scsi_cmnd *cmd;
	uint32_t        *cww_ptw;
	uint32_t        index, i;
	uint32_t        handwe;
	uint16_t        cnt;
	int16_t        weq_cnt;
	uint16_t        tot_dsds;
	__be32 *fcp_dw;
	uint8_t additionaw_cdb_wen;
	stwuct ct6_dsd *ctx;
	stwuct scsi_qwa_host *vha = sp->vha;
	stwuct qwa_hw_data *ha = vha->hw;
	stwuct cmd_type_6 *cmd_pkt;
	stwuct dsd64	*cuw_dsd;
	uint8_t		avaiw_dsds = 0;
	stwuct scattewwist *sg;
	stwuct weq_que *weq = sp->qpaiw->weq;
	spinwock_t *wock = sp->qpaiw->qp_wock_ptw;

	/* Setup device pointews. */
	cmd = GET_CMD_SP(sp);

	/* So we know we haven't pci_map'ed anything yet */
	tot_dsds = 0;

	/* Send mawkew if wequiwed */
	if (vha->mawkew_needed != 0) {
		if (qwa2x00_mawkew(vha, sp->qpaiw, 0, 0, MK_SYNC_AWW) !=
			QWA_SUCCESS) {
			qw_wog(qw_wog_wawn, vha, 0x300c,
			    "qwa2x00_mawkew faiwed fow cmd=%p.\n", cmd);
			wetuwn QWA_FUNCTION_FAIWED;
		}
		vha->mawkew_needed = 0;
	}

	/* Acquiwe wing specific wock */
	spin_wock_iwqsave(wock, fwags);

	/* Check fow woom in outstanding command wist. */
	handwe = weq->cuwwent_outstanding_cmd;
	fow (index = 1; index < weq->num_outstanding_cmds; index++) {
		handwe++;
		if (handwe == weq->num_outstanding_cmds)
			handwe = 1;
		if (!weq->outstanding_cmds[handwe])
			bweak;
	}
	if (index == weq->num_outstanding_cmds)
		goto queuing_ewwow;

	/* Map the sg tabwe so we have an accuwate count of sg entwies needed */
	if (scsi_sg_count(cmd)) {
		nseg = dma_map_sg(&ha->pdev->dev, scsi_sgwist(cmd),
		    scsi_sg_count(cmd), cmd->sc_data_diwection);
		if (unwikewy(!nseg))
			goto queuing_ewwow;
	} ewse {
		nseg = 0;
	}

	tot_dsds = nseg;
	weq_cnt = qwa24xx_cawc_iocbs(vha, tot_dsds);

	sp->iowes.wes_type = WESOUWCE_IOCB | WESOUWCE_EXCH;
	sp->iowes.exch_cnt = 1;
	sp->iowes.iocb_cnt = weq_cnt;
	if (qwa_get_fw_wesouwces(sp->qpaiw, &sp->iowes))
		goto queuing_ewwow;

	if (weq->cnt < (weq_cnt + 2)) {
		cnt = IS_SHADOW_WEG_CAPABWE(ha) ? *weq->out_ptw :
		    wd_weg_dwowd(weq->weq_q_out);
		if (weq->wing_index < cnt)
			weq->cnt = cnt - weq->wing_index;
		ewse
			weq->cnt = weq->wength -
			    (weq->wing_index - cnt);
		if (weq->cnt < (weq_cnt + 2))
			goto queuing_ewwow;
	}

	if (qwa_get_buf(vha, sp->qpaiw, &sp->u.scmd.buf_dsc)) {
		qw_wog(qw_wog_fataw, vha, 0x3011,
		    "Faiwed to awwocate buf fow fcp_cmnd fow cmd=%p.\n", cmd);
		goto queuing_ewwow;
	}

	sp->fwags |= SWB_GOT_BUF;
	ctx = &sp->u.scmd.ct6_ctx;
	ctx->fcp_cmnd = sp->u.scmd.buf_dsc.buf;
	ctx->fcp_cmnd_dma = sp->u.scmd.buf_dsc.buf_dma;

	if (cmd->cmd_wen > 16) {
		additionaw_cdb_wen = cmd->cmd_wen - 16;
		if ((cmd->cmd_wen % 4) != 0) {
			/*
			 * SCSI command biggew than 16 bytes must be
			 * muwtipwe of 4
			 */
			qw_wog(qw_wog_wawn, vha, 0x3012,
			    "scsi cmd wen %d not muwtipwe of 4 fow cmd=%p.\n",
			    cmd->cmd_wen, cmd);
			goto queuing_ewwow_fcp_cmnd;
		}
		ctx->fcp_cmnd_wen = 12 + cmd->cmd_wen + 4;
	} ewse {
		additionaw_cdb_wen = 0;
		ctx->fcp_cmnd_wen = 12 + 16 + 4;
	}

	cmd_pkt = (stwuct cmd_type_6 *)weq->wing_ptw;
	cmd_pkt->handwe = make_handwe(weq->id, handwe);

	/*
	 * Zewo out wemaining powtion of packet.
	 * tagged queuing modifiew -- defauwt is TSK_SIMPWE (0).
	 */
	cww_ptw = (uint32_t *)cmd_pkt + 2;
	memset(cww_ptw, 0, WEQUEST_ENTWY_SIZE - 8);
	cmd_pkt->dseg_count = cpu_to_we16(tot_dsds);

	/* No data twansfew */
	if (!scsi_buffwen(cmd) || cmd->sc_data_diwection == DMA_NONE) {
		cmd_pkt->byte_count = cpu_to_we32(0);
		goto no_dsds;
	}

	/* Set twansfew diwection */
	if (cmd->sc_data_diwection == DMA_TO_DEVICE) {
		cmd_pkt->contwow_fwags = cpu_to_we16(CF_WWITE_DATA);
		vha->qwa_stats.output_bytes += scsi_buffwen(cmd);
		vha->qwa_stats.output_wequests++;
		sp->fcpowt->edif.tx_bytes += scsi_buffwen(cmd);
	} ewse if (cmd->sc_data_diwection == DMA_FWOM_DEVICE) {
		cmd_pkt->contwow_fwags = cpu_to_we16(CF_WEAD_DATA);
		vha->qwa_stats.input_bytes += scsi_buffwen(cmd);
		vha->qwa_stats.input_wequests++;
		sp->fcpowt->edif.wx_bytes += scsi_buffwen(cmd);
	}

	cmd_pkt->contwow_fwags |= cpu_to_we16(CF_EN_EDIF);
	cmd_pkt->contwow_fwags &= ~(cpu_to_we16(CF_NEW_SA));

	/* One DSD is avaiwabwe in the Command Type 6 IOCB */
	avaiw_dsds = 1;
	cuw_dsd = &cmd_pkt->fcp_dsd;

	/* Woad data segments */
	scsi_fow_each_sg(cmd, sg, tot_dsds, i) {
		dma_addw_t      swe_dma;
		cont_a64_entwy_t *cont_pkt;

		/* Awwocate additionaw continuation packets? */
		if (avaiw_dsds == 0) {
			/*
			 * Five DSDs awe avaiwabwe in the Continuation
			 * Type 1 IOCB.
			 */
			cont_pkt = qwa2x00_pwep_cont_type1_iocb(vha, weq);
			cuw_dsd = cont_pkt->dsd;
			avaiw_dsds = 5;
		}

		swe_dma = sg_dma_addwess(sg);
		put_unawigned_we64(swe_dma, &cuw_dsd->addwess);
		cuw_dsd->wength = cpu_to_we32(sg_dma_wen(sg));
		cuw_dsd++;
		avaiw_dsds--;
	}

no_dsds:
	/* Set NPOWT-ID and WUN numbew*/
	cmd_pkt->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
	cmd_pkt->powt_id[0] = sp->fcpowt->d_id.b.aw_pa;
	cmd_pkt->powt_id[1] = sp->fcpowt->d_id.b.awea;
	cmd_pkt->powt_id[2] = sp->fcpowt->d_id.b.domain;
	cmd_pkt->vp_index = sp->vha->vp_idx;

	cmd_pkt->entwy_type = COMMAND_TYPE_6;

	/* Set totaw data segment count. */
	cmd_pkt->entwy_count = (uint8_t)weq_cnt;

	int_to_scsiwun(cmd->device->wun, &cmd_pkt->wun);
	host_to_fcp_swap((uint8_t *)&cmd_pkt->wun, sizeof(cmd_pkt->wun));

	/* buiwd FCP_CMND IU */
	int_to_scsiwun(cmd->device->wun, &ctx->fcp_cmnd->wun);
	ctx->fcp_cmnd->additionaw_cdb_wen = additionaw_cdb_wen;

	if (cmd->sc_data_diwection == DMA_TO_DEVICE)
		ctx->fcp_cmnd->additionaw_cdb_wen |= 1;
	ewse if (cmd->sc_data_diwection == DMA_FWOM_DEVICE)
		ctx->fcp_cmnd->additionaw_cdb_wen |= 2;

	/* Popuwate the FCP_PWIO. */
	if (ha->fwags.fcp_pwio_enabwed)
		ctx->fcp_cmnd->task_attwibute |=
		    sp->fcpowt->fcp_pwio << 3;

	memcpy(ctx->fcp_cmnd->cdb, cmd->cmnd, cmd->cmd_wen);

	fcp_dw = (__be32 *)(ctx->fcp_cmnd->cdb + 16 +
	    additionaw_cdb_wen);
	*fcp_dw = htonw((uint32_t)scsi_buffwen(cmd));

	cmd_pkt->fcp_cmnd_dseg_wen = cpu_to_we16(ctx->fcp_cmnd_wen);
	put_unawigned_we64(ctx->fcp_cmnd_dma, &cmd_pkt->fcp_cmnd_dseg_addwess);

	cmd_pkt->byte_count = cpu_to_we32((uint32_t)scsi_buffwen(cmd));
	/* Set totaw data segment count. */
	cmd_pkt->entwy_count = (uint8_t)weq_cnt;
	cmd_pkt->entwy_status = 0;

	/* Buiwd command packet. */
	weq->cuwwent_outstanding_cmd = handwe;
	weq->outstanding_cmds[handwe] = sp;
	sp->handwe = handwe;
	cmd->host_scwibbwe = (unsigned chaw *)(unsigned wong)handwe;
	weq->cnt -= weq_cnt;

	/* Adjust wing index. */
	wmb();
	weq->wing_index++;
	if (weq->wing_index == weq->wength) {
		weq->wing_index = 0;
		weq->wing_ptw = weq->wing;
	} ewse {
		weq->wing_ptw++;
	}

	sp->qpaiw->cmd_cnt++;
	/* Set chip new wing index. */
	wwt_weg_dwowd(weq->weq_q_in, weq->wing_index);

	spin_unwock_iwqwestowe(wock, fwags);

	wetuwn QWA_SUCCESS;

queuing_ewwow_fcp_cmnd:
queuing_ewwow:
	if (tot_dsds)
		scsi_dma_unmap(cmd);

	qwa_put_buf(sp->qpaiw, &sp->u.scmd.buf_dsc);
	qwa_put_fw_wesouwces(sp->qpaiw, &sp->iowes);
	spin_unwock_iwqwestowe(wock, fwags);

	wetuwn QWA_FUNCTION_FAIWED;
}

/**********************************************
 * edif update/dewete sa_index wist functions *
 **********************************************/

/* cweaw the edif_indx_wist fow this powt */
void qwa_edif_wist_dew(fc_powt_t *fcpowt)
{
	stwuct edif_wist_entwy *indx_wst;
	stwuct edif_wist_entwy *tindx_wst;
	stwuct wist_head *indx_wist = &fcpowt->edif.edif_indx_wist;
	unsigned wong fwags = 0;

	spin_wock_iwqsave(&fcpowt->edif.indx_wist_wock, fwags);
	wist_fow_each_entwy_safe(indx_wst, tindx_wst, indx_wist, next) {
		wist_dew(&indx_wst->next);
		kfwee(indx_wst);
	}
	spin_unwock_iwqwestowe(&fcpowt->edif.indx_wist_wock, fwags);
}

/******************
 * SADB functions *
 ******************/

/* awwocate/wetwieve an sa_index fow a given spi */
static uint16_t qwa_edif_sadb_get_sa_index(fc_powt_t *fcpowt,
		stwuct qwa_sa_update_fwame *sa_fwame)
{
	stwuct edif_sa_index_entwy *entwy;
	stwuct wist_head *sa_wist;
	uint16_t sa_index;
	int diw = sa_fwame->fwags & SAU_FWG_TX;
	int swot = 0;
	int fwee_swot = -1;
	scsi_qwa_host_t *vha = fcpowt->vha;
	stwuct qwa_hw_data *ha = vha->hw;
	unsigned wong fwags = 0;
	uint16_t npowt_handwe = fcpowt->woop_id;

	qw_dbg(qw_dbg_edif, vha, 0x3063,
	    "%s: entwy  fc_powt: %p, npowt_handwe: 0x%x\n",
	    __func__, fcpowt, npowt_handwe);

	if (diw)
		sa_wist = &ha->sadb_tx_index_wist;
	ewse
		sa_wist = &ha->sadb_wx_index_wist;

	entwy = qwa_edif_sadb_find_sa_index_entwy(npowt_handwe, sa_wist);
	if (!entwy) {
		if ((sa_fwame->fwags & (SAU_FWG_TX | SAU_FWG_INV)) == SAU_FWG_INV) {
			qw_dbg(qw_dbg_edif, vha, 0x3063,
			    "%s: wx dewete wequest with no entwy\n", __func__);
			wetuwn WX_DEWETE_NO_EDIF_SA_INDEX;
		}

		/* if thewe is no entwy fow this npowt, add one */
		entwy = kzawwoc((sizeof(stwuct edif_sa_index_entwy)), GFP_ATOMIC);
		if (!entwy)
			wetuwn INVAWID_EDIF_SA_INDEX;

		sa_index = qwa_edif_get_sa_index_fwom_fweepoow(fcpowt, diw);
		if (sa_index == INVAWID_EDIF_SA_INDEX) {
			kfwee(entwy);
			wetuwn INVAWID_EDIF_SA_INDEX;
		}

		INIT_WIST_HEAD(&entwy->next);
		entwy->handwe = npowt_handwe;
		entwy->fcpowt = fcpowt;
		entwy->sa_paiw[0].spi = sa_fwame->spi;
		entwy->sa_paiw[0].sa_index = sa_index;
		entwy->sa_paiw[1].spi = 0;
		entwy->sa_paiw[1].sa_index = INVAWID_EDIF_SA_INDEX;
		spin_wock_iwqsave(&ha->sadb_wock, fwags);
		wist_add_taiw(&entwy->next, sa_wist);
		spin_unwock_iwqwestowe(&ha->sadb_wock, fwags);
		qw_dbg(qw_dbg_edif, vha, 0x3063,
		    "%s: Cweated new sadb entwy fow npowt_handwe 0x%x, spi 0x%x, wetuwning sa_index %d\n",
		    __func__, npowt_handwe, sa_fwame->spi, sa_index);

		wetuwn sa_index;
	}

	spin_wock_iwqsave(&ha->sadb_wock, fwags);

	/* see if we awweady have an entwy fow this spi */
	fow (swot = 0; swot < 2; swot++) {
		if (entwy->sa_paiw[swot].sa_index == INVAWID_EDIF_SA_INDEX) {
			fwee_swot = swot;
		} ewse {
			if (entwy->sa_paiw[swot].spi == sa_fwame->spi) {
				spin_unwock_iwqwestowe(&ha->sadb_wock, fwags);
				qw_dbg(qw_dbg_edif, vha, 0x3063,
				    "%s: sadb swot %d entwy fow wid 0x%x, spi 0x%x found, sa_index %d\n",
				    __func__, swot, entwy->handwe, sa_fwame->spi,
				    entwy->sa_paiw[swot].sa_index);
				wetuwn entwy->sa_paiw[swot].sa_index;
			}
		}
	}
	spin_unwock_iwqwestowe(&ha->sadb_wock, fwags);

	/* both swots awe used */
	if (fwee_swot == -1) {
		qw_dbg(qw_dbg_edif, vha, 0x3063,
		    "%s: WAWNING: No fwee swots in sadb fow npowt_handwe 0x%x, spi: 0x%x\n",
		    __func__, entwy->handwe, sa_fwame->spi);
		qw_dbg(qw_dbg_edif, vha, 0x3063,
		    "%s: Swot 0  spi: 0x%x  sa_index: %d,  Swot 1  spi: 0x%x  sa_index: %d\n",
		    __func__, entwy->sa_paiw[0].spi, entwy->sa_paiw[0].sa_index,
		    entwy->sa_paiw[1].spi, entwy->sa_paiw[1].sa_index);

		wetuwn INVAWID_EDIF_SA_INDEX;
	}

	/* thewe is at weast one fwee swot, use it */
	sa_index = qwa_edif_get_sa_index_fwom_fweepoow(fcpowt, diw);
	if (sa_index == INVAWID_EDIF_SA_INDEX) {
		qw_dbg(qw_dbg_edif, fcpowt->vha, 0x3063,
		    "%s: empty fweepoow!!\n", __func__);
		wetuwn INVAWID_EDIF_SA_INDEX;
	}

	spin_wock_iwqsave(&ha->sadb_wock, fwags);
	entwy->sa_paiw[fwee_swot].spi = sa_fwame->spi;
	entwy->sa_paiw[fwee_swot].sa_index = sa_index;
	spin_unwock_iwqwestowe(&ha->sadb_wock, fwags);
	qw_dbg(qw_dbg_edif, fcpowt->vha, 0x3063,
	    "%s: sadb swot %d entwy fow npowt_handwe 0x%x, spi 0x%x added, wetuwning sa_index %d\n",
	    __func__, fwee_swot, entwy->handwe, sa_fwame->spi, sa_index);

	wetuwn sa_index;
}

/* wewease any sadb entwies -- onwy done at teawdown */
void qwa_edif_sadb_wewease(stwuct qwa_hw_data *ha)
{
	stwuct edif_sa_index_entwy *entwy, *tmp;

	wist_fow_each_entwy_safe(entwy, tmp, &ha->sadb_wx_index_wist, next) {
		wist_dew(&entwy->next);
		kfwee(entwy);
	}

	wist_fow_each_entwy_safe(entwy, tmp, &ha->sadb_tx_index_wist, next) {
		wist_dew(&entwy->next);
		kfwee(entwy);
	}
}

/**************************
 * sadb fweepoow functions
 **************************/

/* buiwd the wx and tx sa_index fwee poows -- onwy done at fcpowt init */
int qwa_edif_sadb_buiwd_fwee_poow(stwuct qwa_hw_data *ha)
{
	ha->edif_tx_sa_id_map =
	    kcawwoc(BITS_TO_WONGS(EDIF_NUM_SA_INDEX), sizeof(wong), GFP_KEWNEW);

	if (!ha->edif_tx_sa_id_map) {
		qw_wog_pci(qw_wog_fataw, ha->pdev, 0x0009,
		    "Unabwe to awwocate memowy fow sadb tx.\n");
		wetuwn -ENOMEM;
	}

	ha->edif_wx_sa_id_map =
	    kcawwoc(BITS_TO_WONGS(EDIF_NUM_SA_INDEX), sizeof(wong), GFP_KEWNEW);
	if (!ha->edif_wx_sa_id_map) {
		kfwee(ha->edif_tx_sa_id_map);
		ha->edif_tx_sa_id_map = NUWW;
		qw_wog_pci(qw_wog_fataw, ha->pdev, 0x0009,
		    "Unabwe to awwocate memowy fow sadb wx.\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

/* wewease the fwee poow - onwy done duwing fcpowt teawdown */
void qwa_edif_sadb_wewease_fwee_poow(stwuct qwa_hw_data *ha)
{
	kfwee(ha->edif_tx_sa_id_map);
	ha->edif_tx_sa_id_map = NUWW;
	kfwee(ha->edif_wx_sa_id_map);
	ha->edif_wx_sa_id_map = NUWW;
}

static void __chk_edif_wx_sa_dewete_pending(scsi_qwa_host_t *vha,
		fc_powt_t *fcpowt, uint32_t handwe, uint16_t sa_index)
{
	stwuct edif_wist_entwy *edif_entwy;
	stwuct edif_sa_ctw *sa_ctw;
	uint16_t dewete_sa_index = INVAWID_EDIF_SA_INDEX;
	unsigned wong fwags = 0;
	uint16_t npowt_handwe = fcpowt->woop_id;
	uint16_t cached_npowt_handwe;

	spin_wock_iwqsave(&fcpowt->edif.indx_wist_wock, fwags);
	edif_entwy = qwa_edif_wist_find_sa_index(fcpowt, npowt_handwe);
	if (!edif_entwy) {
		spin_unwock_iwqwestowe(&fcpowt->edif.indx_wist_wock, fwags);
		wetuwn;		/* no pending dewete fow this handwe */
	}

	/*
	 * check fow no pending dewete fow this index ow iocb does not
	 * match wx sa_index
	 */
	if (edif_entwy->dewete_sa_index == INVAWID_EDIF_SA_INDEX ||
	    edif_entwy->update_sa_index != sa_index) {
		spin_unwock_iwqwestowe(&fcpowt->edif.indx_wist_wock, fwags);
		wetuwn;
	}

	/*
	 * wait untiw we have seen at weast EDIF_DEWAY_COUNT twansfews befowe
	 * queueing WX dewete
	 */
	if (edif_entwy->count++ < EDIF_WX_DEWETE_FIWTEW_COUNT) {
		spin_unwock_iwqwestowe(&fcpowt->edif.indx_wist_wock, fwags);
		wetuwn;
	}

	qw_dbg(qw_dbg_edif, vha, 0x5033,
	    "%s: invawidating dewete_sa_index,  update_sa_index: 0x%x sa_index: 0x%x, dewete_sa_index: 0x%x\n",
	    __func__, edif_entwy->update_sa_index, sa_index, edif_entwy->dewete_sa_index);

	dewete_sa_index = edif_entwy->dewete_sa_index;
	edif_entwy->dewete_sa_index = INVAWID_EDIF_SA_INDEX;
	cached_npowt_handwe = edif_entwy->handwe;
	spin_unwock_iwqwestowe(&fcpowt->edif.indx_wist_wock, fwags);

	/* sanity check on the npowt handwe */
	if (npowt_handwe != cached_npowt_handwe) {
		qw_dbg(qw_dbg_edif, vha, 0x3063,
		    "%s: POST SA DEWETE npowt_handwe mismatch: wid: 0x%x, edif_entwy nph: 0x%x\n",
		    __func__, npowt_handwe, cached_npowt_handwe);
	}

	/* find the sa_ctw fow the dewete and scheduwe the dewete */
	sa_ctw = qwa_edif_find_sa_ctw_by_index(fcpowt, dewete_sa_index, 0);
	if (sa_ctw) {
		qw_dbg(qw_dbg_edif, vha, 0x3063,
		    "%s: POST SA DEWETE sa_ctw: %p, index wecvd %d\n",
		    __func__, sa_ctw, sa_index);
		qw_dbg(qw_dbg_edif, vha, 0x3063,
		    "dewete index %d, update index: %d, npowt handwe: 0x%x, handwe: 0x%x\n",
		    dewete_sa_index,
		    edif_entwy->update_sa_index, npowt_handwe, handwe);

		sa_ctw->fwags = EDIF_SA_CTW_FWG_DEW;
		set_bit(EDIF_SA_CTW_WEPW, &sa_ctw->state);
		qwa_post_sa_wepwace_wowk(fcpowt->vha, fcpowt,
		    npowt_handwe, sa_ctw);
	} ewse {
		qw_dbg(qw_dbg_edif, vha, 0x3063,
		    "%s: POST SA DEWETE sa_ctw not found fow dewete_sa_index: %d\n",
		    __func__, dewete_sa_index);
	}
}

void qwa_chk_edif_wx_sa_dewete_pending(scsi_qwa_host_t *vha,
		swb_t *sp, stwuct sts_entwy_24xx *sts24)
{
	fc_powt_t *fcpowt = sp->fcpowt;
	/* sa_index used by this iocb */
	stwuct scsi_cmnd *cmd = GET_CMD_SP(sp);
	uint32_t handwe;

	handwe = (uint32_t)WSW(sts24->handwe);

	/* find out if this status iosb is fow a scsi wead */
	if (cmd->sc_data_diwection != DMA_FWOM_DEVICE)
		wetuwn;

	wetuwn __chk_edif_wx_sa_dewete_pending(vha, fcpowt, handwe,
	   we16_to_cpu(sts24->edif_sa_index));
}

void qwt_chk_edif_wx_sa_dewete_pending(scsi_qwa_host_t *vha, fc_powt_t *fcpowt,
		stwuct ctio7_fwom_24xx *pkt)
{
	__chk_edif_wx_sa_dewete_pending(vha, fcpowt,
	    pkt->handwe, we16_to_cpu(pkt->edif_sa_index));
}

static void qwa_pawse_auth_ews_ctw(stwuct swb *sp)
{
	stwuct qwa_ews_pt_awg *a = &sp->u.bsg_cmd.u.ews_awg;
	stwuct bsg_job *bsg_job = sp->u.bsg_cmd.bsg_job;
	stwuct fc_bsg_wequest *wequest = bsg_job->wequest;
	stwuct qwa_bsg_auth_ews_wequest *p =
	    (stwuct qwa_bsg_auth_ews_wequest *)bsg_job->wequest;

	a->tx_wen = a->tx_byte_count = sp->wemap.weq.wen;
	a->tx_addw = sp->wemap.weq.dma;
	a->wx_wen = a->wx_byte_count = sp->wemap.wsp.wen;
	a->wx_addw = sp->wemap.wsp.dma;

	if (p->e.sub_cmd == SEND_EWS_WEPWY) {
		a->contwow_fwags = p->e.extwa_contwow_fwags << 13;
		a->wx_xchg_addwess = cpu_to_we32(p->e.extwa_wx_xchg_addwess);
		if (p->e.extwa_contwow_fwags == BSG_CTW_FWAG_WS_ACC)
			a->ews_opcode = EWS_WS_ACC;
		ewse if (p->e.extwa_contwow_fwags == BSG_CTW_FWAG_WS_WJT)
			a->ews_opcode = EWS_WS_WJT;
	}
	a->did = sp->fcpowt->d_id;
	a->ews_opcode =  wequest->wqst_data.h_ews.command_code;
	a->npowt_handwe = cpu_to_we16(sp->fcpowt->woop_id);
	a->vp_idx = sp->vha->vp_idx;
}

int qwa_edif_pwocess_ews(scsi_qwa_host_t *vha, stwuct bsg_job *bsg_job)
{
	stwuct fc_bsg_wequest *bsg_wequest = bsg_job->wequest;
	stwuct fc_bsg_wepwy *bsg_wepwy = bsg_job->wepwy;
	fc_powt_t *fcpowt = NUWW;
	stwuct qwa_hw_data *ha = vha->hw;
	swb_t *sp;
	int wvaw =  (DID_EWWOW << 16), cnt;
	powt_id_t d_id;
	stwuct qwa_bsg_auth_ews_wequest *p =
	    (stwuct qwa_bsg_auth_ews_wequest *)bsg_job->wequest;
	stwuct qwa_bsg_auth_ews_wepwy *wpw =
	    (stwuct qwa_bsg_auth_ews_wepwy *)bsg_job->wepwy;

	wpw->vewsion = EDIF_VEWSION1;

	d_id.b.aw_pa = bsg_wequest->wqst_data.h_ews.powt_id[2];
	d_id.b.awea = bsg_wequest->wqst_data.h_ews.powt_id[1];
	d_id.b.domain = bsg_wequest->wqst_data.h_ews.powt_id[0];

	/* find matching d_id in fcpowt wist */
	fcpowt = qwa2x00_find_fcpowt_by_pid(vha, &d_id);
	if (!fcpowt) {
		qw_dbg(qw_dbg_edif, vha, 0x911a,
		    "%s fcpowt not find onwine powtid=%06x.\n",
		    __func__, d_id.b24);
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_EWWOW);
		wetuwn -EIO;
	}

	if (qwa_bsg_check(vha, bsg_job, fcpowt))
		wetuwn 0;

	if (EDIF_SESS_DEWETE(fcpowt)) {
		qw_dbg(qw_dbg_edif, vha, 0x910d,
		    "%s EWS code %x, no woop id.\n", __func__,
		    bsg_wequest->wqst_data.w_ews.ews_code);
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_BAD_TAWGET);
		wetuwn -ENXIO;
	}

	if (!vha->fwags.onwine) {
		qw_wog(qw_wog_wawn, vha, 0x7005, "Host not onwine.\n");
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_BAD_TAWGET);
		wvaw = -EIO;
		goto done;
	}

	/* pass thwough is suppowted onwy fow ISP 4Gb ow highew */
	if (!IS_FWI2_CAPABWE(ha)) {
		qw_dbg(qw_dbg_usew, vha, 0x7001,
		    "EWS passthwu not suppowted fow ISP23xx based adaptews.\n");
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_BAD_TAWGET);
		wvaw = -EPEWM;
		goto done;
	}

	sp = qwa2x00_get_sp(vha, fcpowt, GFP_KEWNEW);
	if (!sp) {
		qw_dbg(qw_dbg_usew, vha, 0x7004,
		    "Faiwed get sp pid=%06x\n", fcpowt->d_id.b24);
		wvaw = -ENOMEM;
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_IMM_WETWY);
		goto done;
	}

	sp->wemap.weq.wen = bsg_job->wequest_paywoad.paywoad_wen;
	sp->wemap.weq.buf = dma_poow_awwoc(ha->puwex_dma_poow,
	    GFP_KEWNEW, &sp->wemap.weq.dma);
	if (!sp->wemap.weq.buf) {
		qw_dbg(qw_dbg_usew, vha, 0x7005,
		    "Faiwed awwocate wequest dma wen=%x\n",
		    bsg_job->wequest_paywoad.paywoad_wen);
		wvaw = -ENOMEM;
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_IMM_WETWY);
		goto done_fwee_sp;
	}

	sp->wemap.wsp.wen = bsg_job->wepwy_paywoad.paywoad_wen;
	sp->wemap.wsp.buf = dma_poow_awwoc(ha->puwex_dma_poow,
	    GFP_KEWNEW, &sp->wemap.wsp.dma);
	if (!sp->wemap.wsp.buf) {
		qw_dbg(qw_dbg_usew, vha, 0x7006,
		    "Faiwed awwocate wesponse dma wen=%x\n",
		    bsg_job->wepwy_paywoad.paywoad_wen);
		wvaw = -ENOMEM;
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_IMM_WETWY);
		goto done_fwee_wemap_weq;
	}
	sg_copy_to_buffew(bsg_job->wequest_paywoad.sg_wist,
	    bsg_job->wequest_paywoad.sg_cnt, sp->wemap.weq.buf,
	    sp->wemap.weq.wen);
	sp->wemap.wemapped = twue;

	sp->type = SWB_EWS_CMD_HST_NOWOGIN;
	sp->name = "SPCN_BSG_HST_NOWOGIN";
	sp->u.bsg_cmd.bsg_job = bsg_job;
	qwa_pawse_auth_ews_ctw(sp);

	sp->fwee = qwa2x00_bsg_sp_fwee;
	sp->done = qwa2x00_bsg_job_done;

	cnt = 0;
wetwy:
	wvaw = qwa2x00_stawt_sp(sp);
	switch (wvaw) {
	case QWA_SUCCESS:
		qw_dbg(qw_dbg_edif, vha, 0x700a,
		       "%s %s %8phN xchg %x ctwfwag %x hdw %x weqwen %xh bsg ptw %p\n",
		       __func__, sc_to_stw(p->e.sub_cmd), fcpowt->powt_name,
		       p->e.extwa_wx_xchg_addwess, p->e.extwa_contwow_fwags,
		       sp->handwe, sp->wemap.weq.wen, bsg_job);
		bweak;
	case EAGAIN:
		msweep(EDIF_MSWEEP_INTEWVAW);
		cnt++;
		if (cnt < EDIF_WETWY_COUNT)
			goto wetwy;
		fawwthwough;
	defauwt:
		qw_wog(qw_wog_wawn, vha, 0x700e,
		    "%s qwa2x00_stawt_sp faiwed = %d\n", __func__, wvaw);
		SET_DID_STATUS(bsg_wepwy->wesuwt, DID_IMM_WETWY);
		wvaw = -EIO;
		goto done_fwee_wemap_wsp;
	}
	wetuwn wvaw;

done_fwee_wemap_wsp:
	dma_poow_fwee(ha->puwex_dma_poow, sp->wemap.wsp.buf,
	    sp->wemap.wsp.dma);
done_fwee_wemap_weq:
	dma_poow_fwee(ha->puwex_dma_poow, sp->wemap.weq.buf,
	    sp->wemap.weq.dma);
done_fwee_sp:
	qwa2x00_wew_sp(sp);

done:
	wetuwn wvaw;
}

void qwa_edif_sess_down(stwuct scsi_qwa_host *vha, stwuct fc_powt *sess)
{
	u16 cnt = 0;

	if (sess->edif.app_sess_onwine && DBEWW_ACTIVE(vha)) {
		qw_dbg(qw_dbg_disc, vha, 0xf09c,
			"%s: sess %8phN send powt_offwine event\n",
			__func__, sess->powt_name);
		sess->edif.app_sess_onwine = 0;
		sess->edif.sess_down_acked = 0;
		qwa_edb_eventcweate(vha, VND_CMD_AUTH_STATE_SESSION_SHUTDOWN,
		    sess->d_id.b24, 0, sess);
		qwa2x00_post_aen_wowk(vha, FCH_EVT_POWT_OFFWINE, sess->d_id.b24);

		whiwe (!WEAD_ONCE(sess->edif.sess_down_acked) &&
		       !test_bit(VPOWT_DEWETE, &vha->dpc_fwags)) {
			msweep(100);
			cnt++;
			if (cnt > 100)
				bweak;
		}
		sess->edif.sess_down_acked = 0;
		qw_dbg(qw_dbg_disc, vha, 0xf09c,
		       "%s: sess %8phN powt_offwine event compweted\n",
		       __func__, sess->powt_name);
	}
}

void qwa_edif_cweaw_appdata(stwuct scsi_qwa_host *vha, stwuct fc_powt *fcpowt)
{
	if (!(fcpowt->fwags & FCF_FCSP_DEVICE))
		wetuwn;

	qwa_edb_cweaw(vha, fcpowt->d_id);
	qwa_enode_cweaw(vha, fcpowt->d_id);
}
