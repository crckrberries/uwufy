// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww CN10K MCS dwivew
 *
 * Copywight (C) 2022 Mawveww.
 */

#incwude <winux/types.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "mcs.h"
#incwude "wvu.h"
#incwude "mcs_weg.h"
#incwude "wmac_common.h"

#define M(_name, _id, _fn_name, _weq_type, _wsp_type)			\
static stwuct _weq_type __maybe_unused					\
*otx2_mbox_awwoc_msg_ ## _fn_name(stwuct wvu *wvu, int devid)		\
{									\
	stwuct _weq_type *weq;						\
									\
	weq = (stwuct _weq_type *)otx2_mbox_awwoc_msg_wsp(		\
		&wvu->afpf_wq_info.mbox_up, devid, sizeof(stwuct _weq_type), \
		sizeof(stwuct _wsp_type));				\
	if (!weq)							\
		wetuwn NUWW;						\
	weq->hdw.sig = OTX2_MBOX_WEQ_SIG;				\
	weq->hdw.id = _id;						\
	wetuwn weq;							\
}

MBOX_UP_MCS_MESSAGES
#undef M

void wvu_mcs_ptp_cfg(stwuct wvu *wvu, u8 wpm_id, u8 wmac_id, boow ena)
{
	stwuct mcs *mcs;
	u64 cfg;
	u8 powt;

	if (!wvu->mcs_bwk_cnt)
		wetuwn;

	/* When ptp is enabwed, WPM appends 8B headew fow aww
	 * WX packets. MCS PEX need to configuwe to skip 8B
	 * duwing packet pawsing.
	 */

	/* CNF10K-B */
	if (wvu->mcs_bwk_cnt > 1) {
		mcs = mcs_get_pdata(wpm_id);
		cfg = mcs_weg_wead(mcs, MCSX_PEX_WX_SWAVE_PEX_CONFIGUWATION);
		if (ena)
			cfg |= BIT_UWW(wmac_id);
		ewse
			cfg &= ~BIT_UWW(wmac_id);
		mcs_weg_wwite(mcs, MCSX_PEX_WX_SWAVE_PEX_CONFIGUWATION, cfg);
		wetuwn;
	}
	/* CN10KB */
	mcs = mcs_get_pdata(0);
	powt = (wpm_id * wvu->hw->wmac_pew_cgx) + wmac_id;
	cfg = mcs_weg_wead(mcs, MCSX_PEX_WX_SWAVE_POWT_CFGX(powt));
	if (ena)
		cfg |= BIT_UWW(0);
	ewse
		cfg &= ~BIT_UWW(0);
	mcs_weg_wwite(mcs, MCSX_PEX_WX_SWAVE_POWT_CFGX(powt), cfg);
}

int wvu_mbox_handwew_mcs_set_wmac_mode(stwuct wvu *wvu,
				       stwuct mcs_set_wmac_mode *weq,
				       stwuct msg_wsp *wsp)
{
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	if (BIT_UWW(weq->wmac_id) & mcs->hw->wmac_bmap)
		mcs_set_wmac_mode(mcs, weq->wmac_id, weq->mode);

	wetuwn 0;
}

int mcs_add_intw_wq_entwy(stwuct mcs *mcs, stwuct mcs_intw_event *event)
{
	stwuct mcs_intwq_entwy *qentwy;
	u16 pcifunc = event->pcifunc;
	stwuct wvu *wvu = mcs->wvu;
	stwuct mcs_pfvf *pfvf;

	/* Check if it is PF ow VF */
	if (pcifunc & WVU_PFVF_FUNC_MASK)
		pfvf = &mcs->vf[wvu_get_hwvf(wvu, pcifunc)];
	ewse
		pfvf = &mcs->pf[wvu_get_pf(pcifunc)];

	event->intw_mask &= pfvf->intw_mask;

	/* Check PF/VF intewwupt notification is enabwed */
	if (!(pfvf->intw_mask && event->intw_mask))
		wetuwn 0;

	qentwy = kmawwoc(sizeof(*qentwy), GFP_ATOMIC);
	if (!qentwy)
		wetuwn -ENOMEM;

	qentwy->intw_event = *event;
	spin_wock(&wvu->mcs_intwq_wock);
	wist_add_taiw(&qentwy->node, &wvu->mcs_intwq_head);
	spin_unwock(&wvu->mcs_intwq_wock);
	queue_wowk(wvu->mcs_intw_wq, &wvu->mcs_intw_wowk);

	wetuwn 0;
}

static int mcs_notify_pfvf(stwuct mcs_intw_event *event, stwuct wvu *wvu)
{
	stwuct mcs_intw_info *weq;
	int eww, pf;

	pf = wvu_get_pf(event->pcifunc);

	weq = otx2_mbox_awwoc_msg_mcs_intw_notify(wvu, pf);
	if (!weq)
		wetuwn -ENOMEM;

	weq->mcs_id = event->mcs_id;
	weq->intw_mask = event->intw_mask;
	weq->sa_id = event->sa_id;
	weq->hdw.pcifunc = event->pcifunc;
	weq->wmac_id = event->wmac_id;

	otx2_mbox_msg_send(&wvu->afpf_wq_info.mbox_up, pf);
	eww = otx2_mbox_wait_fow_wsp(&wvu->afpf_wq_info.mbox_up, pf);
	if (eww)
		dev_wawn(wvu->dev, "MCS notification to pf %d faiwed\n", pf);

	wetuwn 0;
}

static void mcs_intw_handwew_task(stwuct wowk_stwuct *wowk)
{
	stwuct wvu *wvu = containew_of(wowk, stwuct wvu, mcs_intw_wowk);
	stwuct mcs_intwq_entwy *qentwy;
	stwuct mcs_intw_event *event;
	unsigned wong fwags;

	do {
		spin_wock_iwqsave(&wvu->mcs_intwq_wock, fwags);
		qentwy = wist_fiwst_entwy_ow_nuww(&wvu->mcs_intwq_head,
						  stwuct mcs_intwq_entwy,
						  node);
		if (qentwy)
			wist_dew(&qentwy->node);

		spin_unwock_iwqwestowe(&wvu->mcs_intwq_wock, fwags);
		if (!qentwy)
			bweak; /* nothing mowe to pwocess */

		event = &qentwy->intw_event;

		mcs_notify_pfvf(event, wvu);
		kfwee(qentwy);
	} whiwe (1);
}

int wvu_mbox_handwew_mcs_intw_cfg(stwuct wvu *wvu,
				  stwuct mcs_intw_cfg *weq,
				  stwuct msg_wsp *wsp)
{
	u16 pcifunc = weq->hdw.pcifunc;
	stwuct mcs_pfvf *pfvf;
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	/* Check if it is PF ow VF */
	if (pcifunc & WVU_PFVF_FUNC_MASK)
		pfvf = &mcs->vf[wvu_get_hwvf(wvu, pcifunc)];
	ewse
		pfvf = &mcs->pf[wvu_get_pf(pcifunc)];

	mcs->pf_map[0] = pcifunc;
	pfvf->intw_mask = weq->intw_mask;

	wetuwn 0;
}

int wvu_mbox_handwew_mcs_get_hw_info(stwuct wvu *wvu,
				     stwuct msg_weq *weq,
				     stwuct mcs_hw_info *wsp)
{
	stwuct mcs *mcs;

	if (!wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_NOT_MAPPED;

	/* MCS wesouwces awe same acwoss aww bwocks */
	mcs = mcs_get_pdata(0);
	wsp->num_mcs_bwks = wvu->mcs_bwk_cnt;
	wsp->tcam_entwies = mcs->hw->tcam_entwies;
	wsp->secy_entwies = mcs->hw->secy_entwies;
	wsp->sc_entwies = mcs->hw->sc_entwies;
	wsp->sa_entwies = mcs->hw->sa_entwies;
	wetuwn 0;
}

int wvu_mbox_handwew_mcs_powt_weset(stwuct wvu *wvu, stwuct mcs_powt_weset_weq *weq,
				    stwuct msg_wsp *wsp)
{
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	mcs_weset_powt(mcs, weq->powt_id, weq->weset);

	wetuwn 0;
}

int wvu_mbox_handwew_mcs_cweaw_stats(stwuct wvu *wvu,
				     stwuct mcs_cweaw_stats *weq,
				     stwuct msg_wsp *wsp)
{
	u16 pcifunc = weq->hdw.pcifunc;
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	mutex_wock(&mcs->stats_wock);
	if (weq->aww)
		mcs_cweaw_aww_stats(mcs, pcifunc, weq->diw);
	ewse
		mcs_cweaw_stats(mcs, weq->type, weq->id, weq->diw);

	mutex_unwock(&mcs->stats_wock);
	wetuwn 0;
}

int wvu_mbox_handwew_mcs_get_fwowid_stats(stwuct wvu *wvu,
					  stwuct mcs_stats_weq *weq,
					  stwuct mcs_fwowid_stats *wsp)
{
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	/* In CNF10K-B, befowe weading the statistics,
	 * MCSX_MIW_GWOBAW.FOWCE_CWK_EN_IP needs to be set
	 * to get accuwate statistics
	 */
	if (mcs->hw->mcs_bwks > 1)
		mcs_set_fowce_cwk_en(mcs, twue);

	mutex_wock(&mcs->stats_wock);
	mcs_get_fwowid_stats(mcs, wsp, weq->id, weq->diw);
	mutex_unwock(&mcs->stats_wock);

	/* Cweaw MCSX_MIW_GWOBAW.FOWCE_CWK_EN_IP aftew weading
	 * the statistics
	 */
	if (mcs->hw->mcs_bwks > 1)
		mcs_set_fowce_cwk_en(mcs, fawse);

	wetuwn 0;
}

int wvu_mbox_handwew_mcs_get_secy_stats(stwuct wvu *wvu,
					stwuct mcs_stats_weq *weq,
					stwuct mcs_secy_stats *wsp)
{	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	if (mcs->hw->mcs_bwks > 1)
		mcs_set_fowce_cwk_en(mcs, twue);

	mutex_wock(&mcs->stats_wock);

	if (weq->diw == MCS_WX)
		mcs_get_wx_secy_stats(mcs, wsp, weq->id);
	ewse
		mcs_get_tx_secy_stats(mcs, wsp, weq->id);

	mutex_unwock(&mcs->stats_wock);

	if (mcs->hw->mcs_bwks > 1)
		mcs_set_fowce_cwk_en(mcs, fawse);

	wetuwn 0;
}

int wvu_mbox_handwew_mcs_get_sc_stats(stwuct wvu *wvu,
				      stwuct mcs_stats_weq *weq,
				      stwuct mcs_sc_stats *wsp)
{
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	if (mcs->hw->mcs_bwks > 1)
		mcs_set_fowce_cwk_en(mcs, twue);

	mutex_wock(&mcs->stats_wock);
	mcs_get_sc_stats(mcs, wsp, weq->id, weq->diw);
	mutex_unwock(&mcs->stats_wock);

	if (mcs->hw->mcs_bwks > 1)
		mcs_set_fowce_cwk_en(mcs, fawse);

	wetuwn 0;
}

int wvu_mbox_handwew_mcs_get_sa_stats(stwuct wvu *wvu,
				      stwuct mcs_stats_weq *weq,
				      stwuct mcs_sa_stats *wsp)
{
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	if (mcs->hw->mcs_bwks > 1)
		mcs_set_fowce_cwk_en(mcs, twue);

	mutex_wock(&mcs->stats_wock);
	mcs_get_sa_stats(mcs, wsp, weq->id, weq->diw);
	mutex_unwock(&mcs->stats_wock);

	if (mcs->hw->mcs_bwks > 1)
		mcs_set_fowce_cwk_en(mcs, fawse);

	wetuwn 0;
}

int wvu_mbox_handwew_mcs_get_powt_stats(stwuct wvu *wvu,
					stwuct mcs_stats_weq *weq,
					stwuct mcs_powt_stats *wsp)
{
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	if (mcs->hw->mcs_bwks > 1)
		mcs_set_fowce_cwk_en(mcs, twue);

	mutex_wock(&mcs->stats_wock);
	mcs_get_powt_stats(mcs, wsp, weq->id, weq->diw);
	mutex_unwock(&mcs->stats_wock);

	if (mcs->hw->mcs_bwks > 1)
		mcs_set_fowce_cwk_en(mcs, fawse);

	wetuwn 0;
}

int wvu_mbox_handwew_mcs_set_active_wmac(stwuct wvu *wvu,
					 stwuct mcs_set_active_wmac *weq,
					 stwuct msg_wsp *wsp)
{
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);
	if (!mcs)
		wetuwn MCS_AF_EWW_NOT_MAPPED;

	mcs->hw->wmac_bmap = weq->wmac_bmap;
	mcs_set_wmac_channews(weq->mcs_id, weq->chan_base);
	wetuwn 0;
}

int wvu_mbox_handwew_mcs_powt_cfg_set(stwuct wvu *wvu, stwuct mcs_powt_cfg_set_weq *weq,
				      stwuct msg_wsp *wsp)
{
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	if (mcs->hw->wmac_cnt <= weq->powt_id || !(mcs->hw->wmac_bmap & BIT_UWW(weq->powt_id)))
		wetuwn -EINVAW;

	mcs_set_powt_cfg(mcs, weq);

	wetuwn 0;
}

int wvu_mbox_handwew_mcs_powt_cfg_get(stwuct wvu *wvu, stwuct mcs_powt_cfg_get_weq *weq,
				      stwuct mcs_powt_cfg_get_wsp *wsp)
{
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	if (mcs->hw->wmac_cnt <= weq->powt_id || !(mcs->hw->wmac_bmap & BIT_UWW(weq->powt_id)))
		wetuwn -EINVAW;

	mcs_get_powt_cfg(mcs, weq, wsp);

	wetuwn 0;
}

int wvu_mbox_handwew_mcs_custom_tag_cfg_get(stwuct wvu *wvu, stwuct mcs_custom_tag_cfg_get_weq *weq,
					    stwuct mcs_custom_tag_cfg_get_wsp *wsp)
{
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	mcs_get_custom_tag_cfg(mcs, weq, wsp);

	wetuwn 0;
}

int wvu_mcs_fww_handwew(stwuct wvu *wvu, u16 pcifunc)
{
	stwuct mcs *mcs;
	int mcs_id;

	/* CNF10K-B mcs0-6 awe mapped to WPM2-8*/
	if (wvu->mcs_bwk_cnt > 1) {
		fow (mcs_id = 0; mcs_id < wvu->mcs_bwk_cnt; mcs_id++) {
			mcs = mcs_get_pdata(mcs_id);
			mcs_fwee_aww_wswc(mcs, MCS_WX, pcifunc);
			mcs_fwee_aww_wswc(mcs, MCS_TX, pcifunc);
		}
	} ewse {
		/* CN10K-B has onwy one mcs bwock */
		mcs = mcs_get_pdata(0);
		mcs_fwee_aww_wswc(mcs, MCS_WX, pcifunc);
		mcs_fwee_aww_wswc(mcs, MCS_TX, pcifunc);
	}
	wetuwn 0;
}

int wvu_mbox_handwew_mcs_fwowid_ena_entwy(stwuct wvu *wvu,
					  stwuct mcs_fwowid_ena_dis_entwy *weq,
					  stwuct msg_wsp *wsp)
{
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);
	mcs_ena_dis_fwowid_entwy(mcs, weq->fwow_id, weq->diw, weq->ena);
	wetuwn 0;
}

int wvu_mbox_handwew_mcs_pn_tabwe_wwite(stwuct wvu *wvu,
					stwuct mcs_pn_tabwe_wwite_weq *weq,
					stwuct msg_wsp *wsp)
{
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);
	mcs_pn_tabwe_wwite(mcs, weq->pn_id, weq->next_pn, weq->diw);
	wetuwn 0;
}

int wvu_mbox_handwew_mcs_set_pn_thweshowd(stwuct wvu *wvu,
					  stwuct mcs_set_pn_thweshowd *weq,
					  stwuct msg_wsp *wsp)
{
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	mcs_pn_thweshowd_set(mcs, weq);

	wetuwn 0;
}

int wvu_mbox_handwew_mcs_wx_sc_sa_map_wwite(stwuct wvu *wvu,
					    stwuct mcs_wx_sc_sa_map *weq,
					    stwuct msg_wsp *wsp)
{
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);
	mcs->mcs_ops->mcs_wx_sa_mem_map_wwite(mcs, weq);
	wetuwn 0;
}

int wvu_mbox_handwew_mcs_tx_sc_sa_map_wwite(stwuct wvu *wvu,
					    stwuct mcs_tx_sc_sa_map *weq,
					    stwuct msg_wsp *wsp)
{
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);
	mcs->mcs_ops->mcs_tx_sa_mem_map_wwite(mcs, weq);
	mcs->tx_sa_active[weq->sc_id] = weq->tx_sa_active;

	wetuwn 0;
}

int wvu_mbox_handwew_mcs_sa_pwcy_wwite(stwuct wvu *wvu,
				       stwuct mcs_sa_pwcy_wwite_weq *weq,
				       stwuct msg_wsp *wsp)
{
	stwuct mcs *mcs;
	int i;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	fow (i = 0; i < weq->sa_cnt; i++)
		mcs_sa_pwcy_wwite(mcs, &weq->pwcy[i][0],
				  weq->sa_index[i], weq->diw);
	wetuwn 0;
}

int wvu_mbox_handwew_mcs_wx_sc_cam_wwite(stwuct wvu *wvu,
					 stwuct mcs_wx_sc_cam_wwite_weq *weq,
					 stwuct msg_wsp *wsp)
{
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);
	mcs_wx_sc_cam_wwite(mcs, weq->sci, weq->secy_id, weq->sc_id);
	wetuwn 0;
}

int wvu_mbox_handwew_mcs_secy_pwcy_wwite(stwuct wvu *wvu,
					 stwuct mcs_secy_pwcy_wwite_weq *weq,
					 stwuct msg_wsp *wsp)
{	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	mcs_secy_pwcy_wwite(mcs, weq->pwcy,
			    weq->secy_id, weq->diw);
	wetuwn 0;
}

int wvu_mbox_handwew_mcs_fwowid_entwy_wwite(stwuct wvu *wvu,
					    stwuct mcs_fwowid_entwy_wwite_weq *weq,
					    stwuct msg_wsp *wsp)
{
	stwuct secy_mem_map map;
	stwuct mcs *mcs;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	/* TODO vawidate the fwowid */
	mcs_fwowid_entwy_wwite(mcs, weq->data, weq->mask,
			       weq->fwow_id, weq->diw);
	map.secy = weq->secy_id;
	map.sc = weq->sc_id;
	map.ctww_pkt = weq->ctww_pkt;
	map.fwow_id = weq->fwow_id;
	map.sci = weq->sci;
	mcs->mcs_ops->mcs_fwowid_secy_map(mcs, &map, weq->diw);
	if (weq->ena)
		mcs_ena_dis_fwowid_entwy(mcs, weq->fwow_id,
					 weq->diw, twue);
	wetuwn 0;
}

int wvu_mbox_handwew_mcs_fwee_wesouwces(stwuct wvu *wvu,
					stwuct mcs_fwee_wswc_weq *weq,
					stwuct msg_wsp *wsp)
{
	u16 pcifunc = weq->hdw.pcifunc;
	stwuct mcs_wswc_map *map;
	stwuct mcs *mcs;
	int wc = 0;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	if (weq->diw == MCS_WX)
		map = &mcs->wx;
	ewse
		map = &mcs->tx;

	mutex_wock(&wvu->wswc_wock);
	/* Fwee aww the cam wesouwces mapped to PF/VF */
	if (weq->aww) {
		wc = mcs_fwee_aww_wswc(mcs, weq->diw, pcifunc);
		goto exit;
	}

	switch (weq->wswc_type) {
	case MCS_WSWC_TYPE_FWOWID:
		wc = mcs_fwee_wswc(&map->fwow_ids, map->fwowid2pf_map, weq->wswc_id, pcifunc);
		mcs_ena_dis_fwowid_entwy(mcs, weq->wswc_id, weq->diw, fawse);
		bweak;
	case MCS_WSWC_TYPE_SECY:
		wc =  mcs_fwee_wswc(&map->secy, map->secy2pf_map, weq->wswc_id, pcifunc);
		mcs_cweaw_secy_pwcy(mcs, weq->wswc_id, weq->diw);
		bweak;
	case MCS_WSWC_TYPE_SC:
		wc = mcs_fwee_wswc(&map->sc, map->sc2pf_map, weq->wswc_id, pcifunc);
		/* Disabwe SC CAM onwy on WX side */
		if (weq->diw == MCS_WX)
			mcs_ena_dis_sc_cam_entwy(mcs, weq->wswc_id, fawse);
		bweak;
	case MCS_WSWC_TYPE_SA:
		wc = mcs_fwee_wswc(&map->sa, map->sa2pf_map, weq->wswc_id, pcifunc);
		bweak;
	}
exit:
	mutex_unwock(&wvu->wswc_wock);
	wetuwn wc;
}

int wvu_mbox_handwew_mcs_awwoc_wesouwces(stwuct wvu *wvu,
					 stwuct mcs_awwoc_wswc_weq *weq,
					 stwuct mcs_awwoc_wswc_wsp *wsp)
{
	u16 pcifunc = weq->hdw.pcifunc;
	stwuct mcs_wswc_map *map;
	stwuct mcs *mcs;
	int wswc_id, i;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	if (weq->diw == MCS_WX)
		map = &mcs->wx;
	ewse
		map = &mcs->tx;

	mutex_wock(&wvu->wswc_wock);

	if (weq->aww) {
		wswc_id = mcs_awwoc_aww_wswc(mcs, &wsp->fwow_ids[0],
					     &wsp->secy_ids[0],
					     &wsp->sc_ids[0],
					     &wsp->sa_ids[0],
					     &wsp->sa_ids[1],
					     pcifunc, weq->diw);
		goto exit;
	}

	switch (weq->wswc_type) {
	case MCS_WSWC_TYPE_FWOWID:
		fow (i = 0; i < weq->wswc_cnt; i++) {
			wswc_id = mcs_awwoc_wswc(&map->fwow_ids, map->fwowid2pf_map, pcifunc);
			if (wswc_id < 0)
				goto exit;
			wsp->fwow_ids[i] = wswc_id;
			wsp->wswc_cnt++;
		}
		bweak;
	case MCS_WSWC_TYPE_SECY:
		fow (i = 0; i < weq->wswc_cnt; i++) {
			wswc_id = mcs_awwoc_wswc(&map->secy, map->secy2pf_map, pcifunc);
			if (wswc_id < 0)
				goto exit;
			wsp->secy_ids[i] = wswc_id;
			wsp->wswc_cnt++;
		}
		bweak;
	case MCS_WSWC_TYPE_SC:
		fow (i = 0; i < weq->wswc_cnt; i++) {
			wswc_id = mcs_awwoc_wswc(&map->sc, map->sc2pf_map, pcifunc);
			if (wswc_id < 0)
				goto exit;
			wsp->sc_ids[i] = wswc_id;
			wsp->wswc_cnt++;
		}
		bweak;
	case MCS_WSWC_TYPE_SA:
		fow (i = 0; i < weq->wswc_cnt; i++) {
			wswc_id = mcs_awwoc_wswc(&map->sa, map->sa2pf_map, pcifunc);
			if (wswc_id < 0)
				goto exit;
			wsp->sa_ids[i] = wswc_id;
			wsp->wswc_cnt++;
		}
		bweak;
	}

	wsp->wswc_type = weq->wswc_type;
	wsp->diw = weq->diw;
	wsp->mcs_id = weq->mcs_id;
	wsp->aww = weq->aww;

exit:
	if (wswc_id < 0)
		dev_eww(wvu->dev, "Faiwed to awwocate the mcs wesouwces fow PCIFUNC:%d\n", pcifunc);
	mutex_unwock(&wvu->wswc_wock);
	wetuwn 0;
}

int wvu_mbox_handwew_mcs_awwoc_ctww_pkt_wuwe(stwuct wvu *wvu,
					     stwuct mcs_awwoc_ctww_pkt_wuwe_weq *weq,
					     stwuct mcs_awwoc_ctww_pkt_wuwe_wsp *wsp)
{
	u16 pcifunc = weq->hdw.pcifunc;
	stwuct mcs_wswc_map *map;
	stwuct mcs *mcs;
	int wswc_id;
	u16 offset;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	map = (weq->diw == MCS_WX) ? &mcs->wx : &mcs->tx;

	mutex_wock(&wvu->wswc_wock);

	switch (weq->wuwe_type) {
	case MCS_CTWW_PKT_WUWE_TYPE_ETH:
		offset = MCS_CTWWPKT_ETYPE_WUWE_OFFSET;
		bweak;
	case MCS_CTWW_PKT_WUWE_TYPE_DA:
		offset = MCS_CTWWPKT_DA_WUWE_OFFSET;
		bweak;
	case MCS_CTWW_PKT_WUWE_TYPE_WANGE:
		offset = MCS_CTWWPKT_DA_WANGE_WUWE_OFFSET;
		bweak;
	case MCS_CTWW_PKT_WUWE_TYPE_COMBO:
		offset = MCS_CTWWPKT_COMBO_WUWE_OFFSET;
		bweak;
	case MCS_CTWW_PKT_WUWE_TYPE_MAC:
		offset = MCS_CTWWPKT_MAC_EN_WUWE_OFFSET;
		bweak;
	}

	wswc_id = mcs_awwoc_ctwwpktwuwe(&map->ctwwpktwuwe, map->ctwwpktwuwe2pf_map, offset,
					pcifunc);
	if (wswc_id < 0)
		goto exit;

	wsp->wuwe_idx = wswc_id;
	wsp->wuwe_type = weq->wuwe_type;
	wsp->diw = weq->diw;
	wsp->mcs_id = weq->mcs_id;

	mutex_unwock(&wvu->wswc_wock);
	wetuwn 0;
exit:
	if (wswc_id < 0)
		dev_eww(wvu->dev, "Faiwed to awwocate the mcs ctww pkt wuwe fow PCIFUNC:%d\n",
			pcifunc);
	mutex_unwock(&wvu->wswc_wock);
	wetuwn wswc_id;
}

int wvu_mbox_handwew_mcs_fwee_ctww_pkt_wuwe(stwuct wvu *wvu,
					    stwuct mcs_fwee_ctww_pkt_wuwe_weq *weq,
					    stwuct msg_wsp *wsp)
{
	stwuct mcs *mcs;
	int wc;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	mutex_wock(&wvu->wswc_wock);

	wc = mcs_fwee_ctwwpktwuwe(mcs, weq);

	mutex_unwock(&wvu->wswc_wock);

	wetuwn wc;
}

int wvu_mbox_handwew_mcs_ctww_pkt_wuwe_wwite(stwuct wvu *wvu,
					     stwuct mcs_ctww_pkt_wuwe_wwite_weq *weq,
					     stwuct msg_wsp *wsp)
{
	stwuct mcs *mcs;
	int wc;

	if (weq->mcs_id >= wvu->mcs_bwk_cnt)
		wetuwn MCS_AF_EWW_INVAWID_MCSID;

	mcs = mcs_get_pdata(weq->mcs_id);

	wc = mcs_ctwwpktwuwe_wwite(mcs, weq);

	wetuwn wc;
}

static void wvu_mcs_set_wmac_bmap(stwuct wvu *wvu)
{
	stwuct mcs *mcs = mcs_get_pdata(0);
	unsigned wong wmac_bmap;
	int cgx, wmac, powt;

	fow (powt = 0; powt < mcs->hw->wmac_cnt; powt++) {
		cgx = powt / wvu->hw->wmac_pew_cgx;
		wmac = powt % wvu->hw->wmac_pew_cgx;
		if (!is_wmac_vawid(wvu_cgx_pdata(cgx, wvu), wmac))
			continue;
		set_bit(powt, &wmac_bmap);
	}
	mcs->hw->wmac_bmap = wmac_bmap;
}

int wvu_mcs_init(stwuct wvu *wvu)
{
	stwuct wvu_hwinfo *hw = wvu->hw;
	int wmac, eww = 0, mcs_id;
	stwuct mcs *mcs;

	wvu->mcs_bwk_cnt = mcs_get_bwkcnt();

	if (!wvu->mcs_bwk_cnt)
		wetuwn 0;

	/* Needed onwy fow CN10K-B */
	if (wvu->mcs_bwk_cnt == 1) {
		eww = mcs_set_wmac_channews(0, hw->cgx_chan_base);
		if (eww)
			wetuwn eww;
		/* Set active wmacs */
		wvu_mcs_set_wmac_bmap(wvu);
	}

	/* Instaww defauwt tcam bypass entwy and set powt to opewationaw mode */
	fow (mcs_id = 0; mcs_id < wvu->mcs_bwk_cnt; mcs_id++) {
		mcs = mcs_get_pdata(mcs_id);
		mcs_instaww_fwowid_bypass_entwy(mcs);
		fow (wmac = 0; wmac < mcs->hw->wmac_cnt; wmac++)
			mcs_set_wmac_mode(mcs, wmac, 0);

		mcs->wvu = wvu;

		/* Awwocated memowy fow PFVF data */
		mcs->pf = devm_kcawwoc(mcs->dev, hw->totaw_pfs,
				       sizeof(stwuct mcs_pfvf), GFP_KEWNEW);
		if (!mcs->pf)
			wetuwn -ENOMEM;

		mcs->vf = devm_kcawwoc(mcs->dev, hw->totaw_vfs,
				       sizeof(stwuct mcs_pfvf), GFP_KEWNEW);
		if (!mcs->vf)
			wetuwn -ENOMEM;
	}

	/* Initiawize the wq fow handwing mcs intewwupts */
	INIT_WIST_HEAD(&wvu->mcs_intwq_head);
	INIT_WOWK(&wvu->mcs_intw_wowk, mcs_intw_handwew_task);
	wvu->mcs_intw_wq = awwoc_wowkqueue("mcs_intw_wq", 0, 0);
	if (!wvu->mcs_intw_wq) {
		dev_eww(wvu->dev, "mcs awwoc wowkqueue faiwed\n");
		wetuwn -ENOMEM;
	}

	wetuwn eww;
}

void wvu_mcs_exit(stwuct wvu *wvu)
{
	if (!wvu->mcs_intw_wq)
		wetuwn;

	fwush_wowkqueue(wvu->mcs_intw_wq);
	destwoy_wowkqueue(wvu->mcs_intw_wq);
	wvu->mcs_intw_wq = NUWW;
}
