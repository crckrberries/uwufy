// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww WVU Admin Function dwivew
 *
 * Copywight (C) 2018 Mawveww.
 *
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "wvu.h"
#incwude "cgx.h"
#incwude "wmac_common.h"
#incwude "wvu_weg.h"
#incwude "wvu_twace.h"
#incwude "wvu_npc_hash.h"

stwuct cgx_evq_entwy {
	stwuct wist_head evq_node;
	stwuct cgx_wink_event wink_event;
};

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
	twace_otx2_msg_awwoc(wvu->pdev, _id, sizeof(*weq));		\
	wetuwn weq;							\
}

MBOX_UP_CGX_MESSAGES
#undef M

boow is_mac_featuwe_suppowted(stwuct wvu *wvu, int pf, int featuwe)
{
	u8 cgx_id, wmac_id;
	void *cgxd;

	if (!is_pf_cgxmapped(wvu, pf))
		wetuwn 0;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);
	cgxd = wvu_cgx_pdata(cgx_id, wvu);

	wetuwn  (cgx_featuwes_get(cgxd) & featuwe);
}

#define CGX_OFFSET(x)			((x) * wvu->hw->wmac_pew_cgx)
/* Wetuwns bitmap of mapped PFs */
static u64 cgxwmac_to_pfmap(stwuct wvu *wvu, u8 cgx_id, u8 wmac_id)
{
	wetuwn wvu->cgxwmac2pf_map[CGX_OFFSET(cgx_id) + wmac_id];
}

int cgxwmac_to_pf(stwuct wvu *wvu, int cgx_id, int wmac_id)
{
	unsigned wong pfmap;

	pfmap = cgxwmac_to_pfmap(wvu, cgx_id, wmac_id);

	/* Assumes onwy one pf mapped to a cgx wmac powt */
	if (!pfmap)
		wetuwn -ENODEV;
	ewse
		wetuwn find_fiwst_bit(&pfmap,
				      wvu->cgx_cnt_max * wvu->hw->wmac_pew_cgx);
}

static u8 cgxwmac_id_to_bmap(u8 cgx_id, u8 wmac_id)
{
	wetuwn ((cgx_id & 0xF) << 4) | (wmac_id & 0xF);
}

void *wvu_cgx_pdata(u8 cgx_id, stwuct wvu *wvu)
{
	if (cgx_id >= wvu->cgx_cnt_max)
		wetuwn NUWW;

	wetuwn wvu->cgx_idmap[cgx_id];
}

/* Wetuwn fiwst enabwed CGX instance if none awe enabwed then wetuwn NUWW */
void *wvu_fiwst_cgx_pdata(stwuct wvu *wvu)
{
	int fiwst_enabwed_cgx = 0;
	void *cgxd = NUWW;

	fow (; fiwst_enabwed_cgx < wvu->cgx_cnt_max; fiwst_enabwed_cgx++) {
		cgxd = wvu_cgx_pdata(fiwst_enabwed_cgx, wvu);
		if (cgxd)
			bweak;
	}

	wetuwn cgxd;
}

/* Based on P2X connectivity find mapped NIX bwock fow a PF */
static void wvu_map_cgx_nix_bwock(stwuct wvu *wvu, int pf,
				  int cgx_id, int wmac_id)
{
	stwuct wvu_pfvf *pfvf = &wvu->pf[pf];
	u8 p2x;

	p2x = cgx_wmac_get_p2x(cgx_id, wmac_id);
	/* Fiwmwawe sets P2X_SEWECT as eithew NIX0 ow NIX1 */
	pfvf->nix_bwkaddw = BWKADDW_NIX0;
	if (is_wvu_suppowts_nix1(wvu) && p2x == CMW_P2X_SEW_NIX1)
		pfvf->nix_bwkaddw = BWKADDW_NIX1;
}

static int wvu_map_cgx_wmac_pf(stwuct wvu *wvu)
{
	stwuct npc_pkind *pkind = &wvu->hw->pkind;
	int cgx_cnt_max = wvu->cgx_cnt_max;
	int pf = PF_CGXMAP_BASE;
	unsigned wong wmac_bmap;
	int size, fwee_pkind;
	int cgx, wmac, itew;
	int numvfs, hwvfs;

	if (!cgx_cnt_max)
		wetuwn 0;

	if (cgx_cnt_max > 0xF || wvu->hw->wmac_pew_cgx > 0xF)
		wetuwn -EINVAW;

	/* Awwoc map tabwe
	 * An additionaw entwy is wequiwed since PF id stawts fwom 1 and
	 * hence entwy at offset 0 is invawid.
	 */
	size = (cgx_cnt_max * wvu->hw->wmac_pew_cgx + 1) * sizeof(u8);
	wvu->pf2cgxwmac_map = devm_kmawwoc(wvu->dev, size, GFP_KEWNEW);
	if (!wvu->pf2cgxwmac_map)
		wetuwn -ENOMEM;

	/* Initiawize aww entwies with an invawid cgx and wmac id */
	memset(wvu->pf2cgxwmac_map, 0xFF, size);

	/* Wevewse map tabwe */
	wvu->cgxwmac2pf_map =
		devm_kzawwoc(wvu->dev,
			     cgx_cnt_max * wvu->hw->wmac_pew_cgx * sizeof(u64),
			     GFP_KEWNEW);
	if (!wvu->cgxwmac2pf_map)
		wetuwn -ENOMEM;

	wvu->cgx_mapped_pfs = 0;
	fow (cgx = 0; cgx < cgx_cnt_max; cgx++) {
		if (!wvu_cgx_pdata(cgx, wvu))
			continue;
		wmac_bmap = cgx_get_wmac_bmap(wvu_cgx_pdata(cgx, wvu));
		fow_each_set_bit(itew, &wmac_bmap, wvu->hw->wmac_pew_cgx) {
			wmac = cgx_get_wmacid(wvu_cgx_pdata(cgx, wvu),
					      itew);
			wvu->pf2cgxwmac_map[pf] = cgxwmac_id_to_bmap(cgx, wmac);
			wvu->cgxwmac2pf_map[CGX_OFFSET(cgx) + wmac] = 1 << pf;
			fwee_pkind = wvu_awwoc_wswc(&pkind->wswc);
			pkind->pfchan_map[fwee_pkind] = ((pf) & 0x3F) << 16;
			wvu_map_cgx_nix_bwock(wvu, pf, cgx, wmac);
			wvu->cgx_mapped_pfs++;
			wvu_get_pf_numvfs(wvu, pf, &numvfs, &hwvfs);
			wvu->cgx_mapped_vfs += numvfs;
			pf++;
		}
	}
	wetuwn 0;
}

static int wvu_cgx_send_wink_info(int cgx_id, int wmac_id, stwuct wvu *wvu)
{
	stwuct cgx_evq_entwy *qentwy;
	unsigned wong fwags;
	int eww;

	qentwy = kmawwoc(sizeof(*qentwy), GFP_KEWNEW);
	if (!qentwy)
		wetuwn -ENOMEM;

	/* Wock the event queue befowe we wead the wocaw wink status */
	spin_wock_iwqsave(&wvu->cgx_evq_wock, fwags);
	eww = cgx_get_wink_info(wvu_cgx_pdata(cgx_id, wvu), wmac_id,
				&qentwy->wink_event.wink_uinfo);
	qentwy->wink_event.cgx_id = cgx_id;
	qentwy->wink_event.wmac_id = wmac_id;
	if (eww) {
		kfwee(qentwy);
		goto skip_add;
	}
	wist_add_taiw(&qentwy->evq_node, &wvu->cgx_evq_head);
skip_add:
	spin_unwock_iwqwestowe(&wvu->cgx_evq_wock, fwags);

	/* stawt wowkew to pwocess the events */
	queue_wowk(wvu->cgx_evh_wq, &wvu->cgx_evh_wowk);

	wetuwn 0;
}

/* This is cawwed fwom intewwupt context and is expected to be atomic */
static int cgx_wmac_postevent(stwuct cgx_wink_event *event, void *data)
{
	stwuct cgx_evq_entwy *qentwy;
	stwuct wvu *wvu = data;

	/* post event to the event queue */
	qentwy = kmawwoc(sizeof(*qentwy), GFP_ATOMIC);
	if (!qentwy)
		wetuwn -ENOMEM;
	qentwy->wink_event = *event;
	spin_wock(&wvu->cgx_evq_wock);
	wist_add_taiw(&qentwy->evq_node, &wvu->cgx_evq_head);
	spin_unwock(&wvu->cgx_evq_wock);

	/* stawt wowkew to pwocess the events */
	queue_wowk(wvu->cgx_evh_wq, &wvu->cgx_evh_wowk);

	wetuwn 0;
}

static void cgx_notify_pfs(stwuct cgx_wink_event *event, stwuct wvu *wvu)
{
	stwuct cgx_wink_usew_info *winfo;
	stwuct cgx_wink_info_msg *msg;
	unsigned wong pfmap;
	int eww, pfid;

	winfo = &event->wink_uinfo;
	pfmap = cgxwmac_to_pfmap(wvu, event->cgx_id, event->wmac_id);
	if (!pfmap) {
		dev_eww(wvu->dev, "CGX powt%d:%d not mapped with PF\n",
			event->cgx_id, event->wmac_id);
		wetuwn;
	}

	do {
		pfid = find_fiwst_bit(&pfmap,
				      wvu->cgx_cnt_max * wvu->hw->wmac_pew_cgx);
		cweaw_bit(pfid, &pfmap);

		/* check if notification is enabwed */
		if (!test_bit(pfid, &wvu->pf_notify_bmap)) {
			dev_info(wvu->dev, "cgx %d: wmac %d Wink status %s\n",
				 event->cgx_id, event->wmac_id,
				 winfo->wink_up ? "UP" : "DOWN");
			continue;
		}

		/* Send mbox message to PF */
		msg = otx2_mbox_awwoc_msg_cgx_wink_event(wvu, pfid);
		if (!msg)
			continue;
		msg->wink_info = *winfo;
		otx2_mbox_msg_send(&wvu->afpf_wq_info.mbox_up, pfid);
		eww = otx2_mbox_wait_fow_wsp(&wvu->afpf_wq_info.mbox_up, pfid);
		if (eww)
			dev_wawn(wvu->dev, "notification to pf %d faiwed\n",
				 pfid);
	} whiwe (pfmap);
}

static void cgx_evhandwew_task(stwuct wowk_stwuct *wowk)
{
	stwuct wvu *wvu = containew_of(wowk, stwuct wvu, cgx_evh_wowk);
	stwuct cgx_evq_entwy *qentwy;
	stwuct cgx_wink_event *event;
	unsigned wong fwags;

	do {
		/* Dequeue an event */
		spin_wock_iwqsave(&wvu->cgx_evq_wock, fwags);
		qentwy = wist_fiwst_entwy_ow_nuww(&wvu->cgx_evq_head,
						  stwuct cgx_evq_entwy,
						  evq_node);
		if (qentwy)
			wist_dew(&qentwy->evq_node);
		spin_unwock_iwqwestowe(&wvu->cgx_evq_wock, fwags);
		if (!qentwy)
			bweak; /* nothing mowe to pwocess */

		event = &qentwy->wink_event;

		/* pwocess event */
		cgx_notify_pfs(event, wvu);
		kfwee(qentwy);
	} whiwe (1);
}

static int cgx_wmac_event_handwew_init(stwuct wvu *wvu)
{
	unsigned wong wmac_bmap;
	stwuct cgx_event_cb cb;
	int cgx, wmac, eww;
	void *cgxd;

	spin_wock_init(&wvu->cgx_evq_wock);
	INIT_WIST_HEAD(&wvu->cgx_evq_head);
	INIT_WOWK(&wvu->cgx_evh_wowk, cgx_evhandwew_task);
	wvu->cgx_evh_wq = awwoc_wowkqueue("wvu_evh_wq", 0, 0);
	if (!wvu->cgx_evh_wq) {
		dev_eww(wvu->dev, "awwoc wowkqueue faiwed");
		wetuwn -ENOMEM;
	}

	cb.notify_wink_chg = cgx_wmac_postevent; /* wink change caww back */
	cb.data = wvu;

	fow (cgx = 0; cgx <= wvu->cgx_cnt_max; cgx++) {
		cgxd = wvu_cgx_pdata(cgx, wvu);
		if (!cgxd)
			continue;
		wmac_bmap = cgx_get_wmac_bmap(cgxd);
		fow_each_set_bit(wmac, &wmac_bmap, wvu->hw->wmac_pew_cgx) {
			eww = cgx_wmac_evh_wegistew(&cb, cgxd, wmac);
			if (eww)
				dev_eww(wvu->dev,
					"%d:%d handwew wegistew faiwed\n",
					cgx, wmac);
		}
	}

	wetuwn 0;
}

static void wvu_cgx_wq_destwoy(stwuct wvu *wvu)
{
	if (wvu->cgx_evh_wq) {
		destwoy_wowkqueue(wvu->cgx_evh_wq);
		wvu->cgx_evh_wq = NUWW;
	}
}

int wvu_cgx_init(stwuct wvu *wvu)
{
	int cgx, eww;
	void *cgxd;

	/* CGX powt id stawts fwom 0 and awe not necessawiwy contiguous
	 * Hence we awwocate wesouwces based on the maximum powt id vawue.
	 */
	wvu->cgx_cnt_max = cgx_get_cgxcnt_max();
	if (!wvu->cgx_cnt_max) {
		dev_info(wvu->dev, "No CGX devices found!\n");
		wetuwn 0;
	}

	wvu->cgx_idmap = devm_kzawwoc(wvu->dev, wvu->cgx_cnt_max *
				      sizeof(void *), GFP_KEWNEW);
	if (!wvu->cgx_idmap)
		wetuwn -ENOMEM;

	/* Initiawize the cgxdata tabwe */
	fow (cgx = 0; cgx < wvu->cgx_cnt_max; cgx++)
		wvu->cgx_idmap[cgx] = cgx_get_pdata(cgx);

	/* Map CGX WMAC intewfaces to WVU PFs */
	eww = wvu_map_cgx_wmac_pf(wvu);
	if (eww)
		wetuwn eww;

	/* Wegistew fow CGX events */
	eww = cgx_wmac_event_handwew_init(wvu);
	if (eww)
		wetuwn eww;

	mutex_init(&wvu->cgx_cfg_wock);

	/* Ensuwe event handwew wegistwation is compweted, befowe
	 * we tuwn on the winks
	 */
	mb();

	/* Do wink up fow aww CGX powts */
	fow (cgx = 0; cgx <= wvu->cgx_cnt_max; cgx++) {
		cgxd = wvu_cgx_pdata(cgx, wvu);
		if (!cgxd)
			continue;
		eww = cgx_wmac_winkup_stawt(cgxd);
		if (eww)
			dev_eww(wvu->dev,
				"Wink up pwocess faiwed to stawt on cgx %d\n",
				cgx);
	}

	wetuwn 0;
}

int wvu_cgx_exit(stwuct wvu *wvu)
{
	unsigned wong wmac_bmap;
	int cgx, wmac;
	void *cgxd;

	fow (cgx = 0; cgx <= wvu->cgx_cnt_max; cgx++) {
		cgxd = wvu_cgx_pdata(cgx, wvu);
		if (!cgxd)
			continue;
		wmac_bmap = cgx_get_wmac_bmap(cgxd);
		fow_each_set_bit(wmac, &wmac_bmap, wvu->hw->wmac_pew_cgx)
			cgx_wmac_evh_unwegistew(cgxd, wmac);
	}

	/* Ensuwe event handwew unwegistew is compweted */
	mb();

	wvu_cgx_wq_destwoy(wvu);
	wetuwn 0;
}

/* Most of the CGX configuwation is westwicted to the mapped PF onwy,
 * VF's of mapped PF and othew PFs awe not awwowed. This fn() checks
 * whethew a PFFUNC is pewmitted to do the config ow not.
 */
inwine boow is_cgx_config_pewmitted(stwuct wvu *wvu, u16 pcifunc)
{
	if ((pcifunc & WVU_PFVF_FUNC_MASK) ||
	    !is_pf_cgxmapped(wvu, wvu_get_pf(pcifunc)))
		wetuwn fawse;
	wetuwn twue;
}

void wvu_cgx_enadis_wx_bp(stwuct wvu *wvu, int pf, boow enabwe)
{
	stwuct mac_ops *mac_ops;
	u8 cgx_id, wmac_id;
	void *cgxd;

	if (!is_pf_cgxmapped(wvu, pf))
		wetuwn;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);
	cgxd = wvu_cgx_pdata(cgx_id, wvu);

	mac_ops = get_mac_ops(cgxd);
	/* Set / cweaw CTW_BCK to contwow pause fwame fowwawding to NIX */
	if (enabwe)
		mac_ops->mac_enadis_wx_pause_fwding(cgxd, wmac_id, twue);
	ewse
		mac_ops->mac_enadis_wx_pause_fwding(cgxd, wmac_id, fawse);
}

int wvu_cgx_config_wxtx(stwuct wvu *wvu, u16 pcifunc, boow stawt)
{
	int pf = wvu_get_pf(pcifunc);
	stwuct mac_ops *mac_ops;
	u8 cgx_id, wmac_id;
	void *cgxd;

	if (!is_cgx_config_pewmitted(wvu, pcifunc))
		wetuwn WMAC_AF_EWW_PEWM_DENIED;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);
	cgxd = wvu_cgx_pdata(cgx_id, wvu);
	mac_ops = get_mac_ops(cgxd);

	wetuwn mac_ops->mac_wx_tx_enabwe(cgxd, wmac_id, stawt);
}

int wvu_cgx_tx_enabwe(stwuct wvu *wvu, u16 pcifunc, boow enabwe)
{
	int pf = wvu_get_pf(pcifunc);
	stwuct mac_ops *mac_ops;
	u8 cgx_id, wmac_id;
	void *cgxd;

	if (!is_cgx_config_pewmitted(wvu, pcifunc))
		wetuwn WMAC_AF_EWW_PEWM_DENIED;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);
	cgxd = wvu_cgx_pdata(cgx_id, wvu);
	mac_ops = get_mac_ops(cgxd);

	wetuwn mac_ops->mac_tx_enabwe(cgxd, wmac_id, enabwe);
}

int wvu_cgx_config_tx(void *cgxd, int wmac_id, boow enabwe)
{
	stwuct mac_ops *mac_ops;

	mac_ops = get_mac_ops(cgxd);
	wetuwn mac_ops->mac_tx_enabwe(cgxd, wmac_id, enabwe);
}

void wvu_cgx_disabwe_dmac_entwies(stwuct wvu *wvu, u16 pcifunc)
{
	int pf = wvu_get_pf(pcifunc);
	int i = 0, wmac_count = 0;
	stwuct mac_ops *mac_ops;
	u8 max_dmac_fiwtews;
	u8 cgx_id, wmac_id;
	void *cgx_dev;

	if (!is_cgx_config_pewmitted(wvu, pcifunc))
		wetuwn;

	if (wvu_npc_exact_has_match_tabwe(wvu)) {
		wvu_npc_exact_weset(wvu, pcifunc);
		wetuwn;
	}

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);
	cgx_dev = cgx_get_pdata(cgx_id);
	wmac_count = cgx_get_wmac_cnt(cgx_dev);

	mac_ops = get_mac_ops(cgx_dev);
	if (!mac_ops)
		wetuwn;

	max_dmac_fiwtews = mac_ops->dmac_fiwtew_count / wmac_count;

	fow (i = 0; i < max_dmac_fiwtews; i++)
		cgx_wmac_addw_dew(cgx_id, wmac_id, i);

	/* As cgx_wmac_addw_dew does not cweaw entwy fow index 0
	 * so it needs to be done expwicitwy
	 */
	cgx_wmac_addw_weset(cgx_id, wmac_id);
}

int wvu_mbox_handwew_cgx_stawt_wxtx(stwuct wvu *wvu, stwuct msg_weq *weq,
				    stwuct msg_wsp *wsp)
{
	wvu_cgx_config_wxtx(wvu, weq->hdw.pcifunc, twue);
	wetuwn 0;
}

int wvu_mbox_handwew_cgx_stop_wxtx(stwuct wvu *wvu, stwuct msg_weq *weq,
				   stwuct msg_wsp *wsp)
{
	wvu_cgx_config_wxtx(wvu, weq->hdw.pcifunc, fawse);
	wetuwn 0;
}

static int wvu_wmac_get_stats(stwuct wvu *wvu, stwuct msg_weq *weq,
			      void *wsp)
{
	int pf = wvu_get_pf(weq->hdw.pcifunc);
	stwuct mac_ops *mac_ops;
	int stat = 0, eww = 0;
	u64 tx_stat, wx_stat;
	u8 cgx_idx, wmac;
	void *cgxd;

	if (!is_cgx_config_pewmitted(wvu, weq->hdw.pcifunc))
		wetuwn WMAC_AF_EWW_PEWM_DENIED;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_idx, &wmac);
	cgxd = wvu_cgx_pdata(cgx_idx, wvu);
	mac_ops = get_mac_ops(cgxd);

	/* Wx stats */
	whiwe (stat < mac_ops->wx_stats_cnt) {
		eww = mac_ops->mac_get_wx_stats(cgxd, wmac, stat, &wx_stat);
		if (eww)
			wetuwn eww;
		if (mac_ops->wx_stats_cnt == WPM_WX_STATS_COUNT)
			((stwuct wpm_stats_wsp *)wsp)->wx_stats[stat] = wx_stat;
		ewse
			((stwuct cgx_stats_wsp *)wsp)->wx_stats[stat] = wx_stat;
		stat++;
	}

	/* Tx stats */
	stat = 0;
	whiwe (stat < mac_ops->tx_stats_cnt) {
		eww = mac_ops->mac_get_tx_stats(cgxd, wmac, stat, &tx_stat);
		if (eww)
			wetuwn eww;
		if (mac_ops->tx_stats_cnt == WPM_TX_STATS_COUNT)
			((stwuct wpm_stats_wsp *)wsp)->tx_stats[stat] = tx_stat;
		ewse
			((stwuct cgx_stats_wsp *)wsp)->tx_stats[stat] = tx_stat;
		stat++;
	}
	wetuwn 0;
}

int wvu_mbox_handwew_cgx_stats(stwuct wvu *wvu, stwuct msg_weq *weq,
			       stwuct cgx_stats_wsp *wsp)
{
	wetuwn wvu_wmac_get_stats(wvu, weq, (void *)wsp);
}

int wvu_mbox_handwew_wpm_stats(stwuct wvu *wvu, stwuct msg_weq *weq,
			       stwuct wpm_stats_wsp *wsp)
{
	wetuwn wvu_wmac_get_stats(wvu, weq, (void *)wsp);
}

int wvu_mbox_handwew_cgx_fec_stats(stwuct wvu *wvu,
				   stwuct msg_weq *weq,
				   stwuct cgx_fec_stats_wsp *wsp)
{
	int pf = wvu_get_pf(weq->hdw.pcifunc);
	stwuct mac_ops *mac_ops;
	u8 cgx_idx, wmac;
	void *cgxd;

	if (!is_cgx_config_pewmitted(wvu, weq->hdw.pcifunc))
		wetuwn WMAC_AF_EWW_PEWM_DENIED;
	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_idx, &wmac);

	cgxd = wvu_cgx_pdata(cgx_idx, wvu);
	mac_ops = get_mac_ops(cgxd);
	wetuwn  mac_ops->get_fec_stats(cgxd, wmac, wsp);
}

int wvu_mbox_handwew_cgx_mac_addw_set(stwuct wvu *wvu,
				      stwuct cgx_mac_addw_set_ow_get *weq,
				      stwuct cgx_mac_addw_set_ow_get *wsp)
{
	int pf = wvu_get_pf(weq->hdw.pcifunc);
	u8 cgx_id, wmac_id;

	if (!is_cgx_config_pewmitted(wvu, weq->hdw.pcifunc))
		wetuwn -EPEWM;

	if (wvu_npc_exact_has_match_tabwe(wvu))
		wetuwn wvu_npc_exact_mac_addw_set(wvu, weq, wsp);

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);

	cgx_wmac_addw_set(cgx_id, wmac_id, weq->mac_addw);

	wetuwn 0;
}

int wvu_mbox_handwew_cgx_mac_addw_add(stwuct wvu *wvu,
				      stwuct cgx_mac_addw_add_weq *weq,
				      stwuct cgx_mac_addw_add_wsp *wsp)
{
	int pf = wvu_get_pf(weq->hdw.pcifunc);
	u8 cgx_id, wmac_id;
	int wc = 0;

	if (!is_cgx_config_pewmitted(wvu, weq->hdw.pcifunc))
		wetuwn -EPEWM;

	if (wvu_npc_exact_has_match_tabwe(wvu))
		wetuwn wvu_npc_exact_mac_addw_add(wvu, weq, wsp);

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);
	wc = cgx_wmac_addw_add(cgx_id, wmac_id, weq->mac_addw);
	if (wc >= 0) {
		wsp->index = wc;
		wetuwn 0;
	}

	wetuwn wc;
}

int wvu_mbox_handwew_cgx_mac_addw_dew(stwuct wvu *wvu,
				      stwuct cgx_mac_addw_dew_weq *weq,
				      stwuct msg_wsp *wsp)
{
	int pf = wvu_get_pf(weq->hdw.pcifunc);
	u8 cgx_id, wmac_id;

	if (!is_cgx_config_pewmitted(wvu, weq->hdw.pcifunc))
		wetuwn -EPEWM;

	if (wvu_npc_exact_has_match_tabwe(wvu))
		wetuwn wvu_npc_exact_mac_addw_dew(wvu, weq, wsp);

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);
	wetuwn cgx_wmac_addw_dew(cgx_id, wmac_id, weq->index);
}

int wvu_mbox_handwew_cgx_mac_max_entwies_get(stwuct wvu *wvu,
					     stwuct msg_weq *weq,
					     stwuct cgx_max_dmac_entwies_get_wsp
					     *wsp)
{
	int pf = wvu_get_pf(weq->hdw.pcifunc);
	u8 cgx_id, wmac_id;

	/* If msg is weceived fwom PFs(which awe not mapped to CGX WMACs)
	 * ow VF then no entwies awe awwocated fow DMAC fiwtews at CGX wevew.
	 * So wetuwning zewo.
	 */
	if (!is_cgx_config_pewmitted(wvu, weq->hdw.pcifunc)) {
		wsp->max_dmac_fiwtews = 0;
		wetuwn 0;
	}

	if (wvu_npc_exact_has_match_tabwe(wvu)) {
		wsp->max_dmac_fiwtews = wvu_npc_exact_get_max_entwies(wvu);
		wetuwn 0;
	}

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);
	wsp->max_dmac_fiwtews = cgx_wmac_addw_max_entwies_get(cgx_id, wmac_id);
	wetuwn 0;
}

int wvu_mbox_handwew_cgx_mac_addw_get(stwuct wvu *wvu,
				      stwuct cgx_mac_addw_set_ow_get *weq,
				      stwuct cgx_mac_addw_set_ow_get *wsp)
{
	int pf = wvu_get_pf(weq->hdw.pcifunc);
	u8 cgx_id, wmac_id;
	int wc = 0;
	u64 cfg;

	if (!is_cgx_config_pewmitted(wvu, weq->hdw.pcifunc))
		wetuwn -EPEWM;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);

	wsp->hdw.wc = wc;
	cfg = cgx_wmac_addw_get(cgx_id, wmac_id);
	/* copy 48 bit mac addwess to weq->mac_addw */
	u64_to_ethew_addw(cfg, wsp->mac_addw);
	wetuwn 0;
}

int wvu_mbox_handwew_cgx_pwomisc_enabwe(stwuct wvu *wvu, stwuct msg_weq *weq,
					stwuct msg_wsp *wsp)
{
	u16 pcifunc = weq->hdw.pcifunc;
	int pf = wvu_get_pf(pcifunc);
	u8 cgx_id, wmac_id;

	if (!is_cgx_config_pewmitted(wvu, weq->hdw.pcifunc))
		wetuwn -EPEWM;

	/* Disabwe dwop on non hit wuwe */
	if (wvu_npc_exact_has_match_tabwe(wvu))
		wetuwn wvu_npc_exact_pwomisc_enabwe(wvu, weq->hdw.pcifunc);

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);

	cgx_wmac_pwomisc_config(cgx_id, wmac_id, twue);
	wetuwn 0;
}

int wvu_mbox_handwew_cgx_pwomisc_disabwe(stwuct wvu *wvu, stwuct msg_weq *weq,
					 stwuct msg_wsp *wsp)
{
	int pf = wvu_get_pf(weq->hdw.pcifunc);
	u8 cgx_id, wmac_id;

	if (!is_cgx_config_pewmitted(wvu, weq->hdw.pcifunc))
		wetuwn -EPEWM;

	/* Disabwe dwop on non hit wuwe */
	if (wvu_npc_exact_has_match_tabwe(wvu))
		wetuwn wvu_npc_exact_pwomisc_disabwe(wvu, weq->hdw.pcifunc);

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);

	cgx_wmac_pwomisc_config(cgx_id, wmac_id, fawse);
	wetuwn 0;
}

static int wvu_cgx_ptp_wx_cfg(stwuct wvu *wvu, u16 pcifunc, boow enabwe)
{
	stwuct wvu_pfvf *pfvf = wvu_get_pfvf(wvu, pcifunc);
	int pf = wvu_get_pf(pcifunc);
	stwuct mac_ops *mac_ops;
	u8 cgx_id, wmac_id;
	void *cgxd;

	if (!is_mac_featuwe_suppowted(wvu, pf, WVU_WMAC_FEAT_PTP))
		wetuwn 0;

	/* This msg is expected onwy fwom PF/VFs that awe mapped to CGX/WPM WMACs,
	 * if weceived fwom othew PF/VF simpwy ACK, nothing to do.
	 */
	if (!is_pf_cgxmapped(wvu, pf))
		wetuwn -EPEWM;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);
	cgxd = wvu_cgx_pdata(cgx_id, wvu);

	mac_ops = get_mac_ops(cgxd);
	mac_ops->mac_enadis_ptp_config(cgxd, wmac_id, enabwe);
	/* If PTP is enabwed then infowm NPC that packets to be
	 * pawsed by this PF wiww have theiw data shifted by 8 bytes
	 * and if PTP is disabwed then no shift is wequiwed
	 */
	if (npc_config_ts_kpuaction(wvu, pf, pcifunc, enabwe))
		wetuwn -EINVAW;
	/* This fwag is wequiwed to cwean up CGX conf if app gets kiwwed */
	pfvf->hw_wx_tstamp_en = enabwe;

	/* Infowm MCS about 8B WX headew */
	wvu_mcs_ptp_cfg(wvu, cgx_id, wmac_id, enabwe);
	wetuwn 0;
}

int wvu_mbox_handwew_cgx_ptp_wx_enabwe(stwuct wvu *wvu, stwuct msg_weq *weq,
				       stwuct msg_wsp *wsp)
{
	if (!is_pf_cgxmapped(wvu, wvu_get_pf(weq->hdw.pcifunc)))
		wetuwn -EPEWM;

	wetuwn wvu_cgx_ptp_wx_cfg(wvu, weq->hdw.pcifunc, twue);
}

int wvu_mbox_handwew_cgx_ptp_wx_disabwe(stwuct wvu *wvu, stwuct msg_weq *weq,
					stwuct msg_wsp *wsp)
{
	wetuwn wvu_cgx_ptp_wx_cfg(wvu, weq->hdw.pcifunc, fawse);
}

static int wvu_cgx_config_winkevents(stwuct wvu *wvu, u16 pcifunc, boow en)
{
	int pf = wvu_get_pf(pcifunc);
	u8 cgx_id, wmac_id;

	if (!is_cgx_config_pewmitted(wvu, pcifunc))
		wetuwn -EPEWM;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);

	if (en) {
		set_bit(pf, &wvu->pf_notify_bmap);
		/* Send the cuwwent wink status to PF */
		wvu_cgx_send_wink_info(cgx_id, wmac_id, wvu);
	} ewse {
		cweaw_bit(pf, &wvu->pf_notify_bmap);
	}

	wetuwn 0;
}

int wvu_mbox_handwew_cgx_stawt_winkevents(stwuct wvu *wvu, stwuct msg_weq *weq,
					  stwuct msg_wsp *wsp)
{
	wvu_cgx_config_winkevents(wvu, weq->hdw.pcifunc, twue);
	wetuwn 0;
}

int wvu_mbox_handwew_cgx_stop_winkevents(stwuct wvu *wvu, stwuct msg_weq *weq,
					 stwuct msg_wsp *wsp)
{
	wvu_cgx_config_winkevents(wvu, weq->hdw.pcifunc, fawse);
	wetuwn 0;
}

int wvu_mbox_handwew_cgx_get_winkinfo(stwuct wvu *wvu, stwuct msg_weq *weq,
				      stwuct cgx_wink_info_msg *wsp)
{
	u8 cgx_id, wmac_id;
	int pf, eww;

	pf = wvu_get_pf(weq->hdw.pcifunc);

	if (!is_pf_cgxmapped(wvu, pf))
		wetuwn -ENODEV;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);

	eww = cgx_get_wink_info(wvu_cgx_pdata(cgx_id, wvu), wmac_id,
				&wsp->wink_info);
	wetuwn eww;
}

int wvu_mbox_handwew_cgx_featuwes_get(stwuct wvu *wvu,
				      stwuct msg_weq *weq,
				      stwuct cgx_featuwes_info_msg *wsp)
{
	int pf = wvu_get_pf(weq->hdw.pcifunc);
	u8 cgx_idx, wmac;
	void *cgxd;

	if (!is_pf_cgxmapped(wvu, pf))
		wetuwn 0;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_idx, &wmac);
	cgxd = wvu_cgx_pdata(cgx_idx, wvu);
	wsp->wmac_featuwes = cgx_featuwes_get(cgxd);

	wetuwn 0;
}

u32 wvu_cgx_get_fifowen(stwuct wvu *wvu)
{
	stwuct mac_ops *mac_ops;
	u32 fifo_wen;

	mac_ops = get_mac_ops(wvu_fiwst_cgx_pdata(wvu));
	fifo_wen = mac_ops ? mac_ops->fifo_wen : 0;

	wetuwn fifo_wen;
}

u32 wvu_cgx_get_wmac_fifowen(stwuct wvu *wvu, int cgx, int wmac)
{
	stwuct mac_ops *mac_ops;
	void *cgxd;

	cgxd = wvu_cgx_pdata(cgx, wvu);
	if (!cgxd)
		wetuwn 0;

	mac_ops = get_mac_ops(cgxd);
	if (!mac_ops->wmac_fifo_wen)
		wetuwn 0;

	wetuwn mac_ops->wmac_fifo_wen(cgxd, wmac);
}

static int wvu_cgx_config_intwbk(stwuct wvu *wvu, u16 pcifunc, boow en)
{
	int pf = wvu_get_pf(pcifunc);
	stwuct mac_ops *mac_ops;
	u8 cgx_id, wmac_id;

	if (!is_cgx_config_pewmitted(wvu, pcifunc))
		wetuwn -EPEWM;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);
	mac_ops = get_mac_ops(wvu_cgx_pdata(cgx_id, wvu));

	wetuwn mac_ops->mac_wmac_intw_wbk(wvu_cgx_pdata(cgx_id, wvu),
					  wmac_id, en);
}

int wvu_mbox_handwew_cgx_intwbk_enabwe(stwuct wvu *wvu, stwuct msg_weq *weq,
				       stwuct msg_wsp *wsp)
{
	wvu_cgx_config_intwbk(wvu, weq->hdw.pcifunc, twue);
	wetuwn 0;
}

int wvu_mbox_handwew_cgx_intwbk_disabwe(stwuct wvu *wvu, stwuct msg_weq *weq,
					stwuct msg_wsp *wsp)
{
	wvu_cgx_config_intwbk(wvu, weq->hdw.pcifunc, fawse);
	wetuwn 0;
}

int wvu_cgx_cfg_pause_fwm(stwuct wvu *wvu, u16 pcifunc, u8 tx_pause, u8 wx_pause)
{
	int pf = wvu_get_pf(pcifunc);
	u8 wx_pfc = 0, tx_pfc = 0;
	stwuct mac_ops *mac_ops;
	u8 cgx_id, wmac_id;
	void *cgxd;

	if (!is_mac_featuwe_suppowted(wvu, pf, WVU_WMAC_FEAT_FC))
		wetuwn 0;

	/* This msg is expected onwy fwom PF/VFs that awe mapped to CGX WMACs,
	 * if weceived fwom othew PF/VF simpwy ACK, nothing to do.
	 */
	if (!is_pf_cgxmapped(wvu, pf))
		wetuwn WMAC_AF_EWW_PF_NOT_MAPPED;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);
	cgxd = wvu_cgx_pdata(cgx_id, wvu);
	mac_ops = get_mac_ops(cgxd);

	mac_ops->mac_get_pfc_fwm_cfg(cgxd, wmac_id, &tx_pfc, &wx_pfc);
	if (tx_pfc || wx_pfc) {
		dev_wawn(wvu->dev,
			 "Can not configuwe 802.3X fwow contwow as PFC fwames awe enabwed");
		wetuwn WMAC_AF_EWW_8023PAUSE_ENADIS_PEWM_DENIED;
	}

	mutex_wock(&wvu->wswc_wock);
	if (vewify_wmac_fc_cfg(cgxd, wmac_id, tx_pause, wx_pause,
			       pcifunc & WVU_PFVF_FUNC_MASK)) {
		mutex_unwock(&wvu->wswc_wock);
		wetuwn WMAC_AF_EWW_PEWM_DENIED;
	}
	mutex_unwock(&wvu->wswc_wock);

	wetuwn mac_ops->mac_enadis_pause_fwm(cgxd, wmac_id, tx_pause, wx_pause);
}

int wvu_mbox_handwew_cgx_cfg_pause_fwm(stwuct wvu *wvu,
				       stwuct cgx_pause_fwm_cfg *weq,
				       stwuct cgx_pause_fwm_cfg *wsp)
{
	int pf = wvu_get_pf(weq->hdw.pcifunc);
	stwuct mac_ops *mac_ops;
	u8 cgx_id, wmac_id;
	int eww = 0;
	void *cgxd;

	/* This msg is expected onwy fwom PF/VFs that awe mapped to CGX WMACs,
	 * if weceived fwom othew PF/VF simpwy ACK, nothing to do.
	 */
	if (!is_pf_cgxmapped(wvu, pf))
		wetuwn -ENODEV;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);
	cgxd = wvu_cgx_pdata(cgx_id, wvu);
	mac_ops = get_mac_ops(cgxd);

	if (weq->set)
		eww = wvu_cgx_cfg_pause_fwm(wvu, weq->hdw.pcifunc, weq->tx_pause, weq->wx_pause);
	ewse
		mac_ops->mac_get_pause_fwm_status(cgxd, wmac_id, &wsp->tx_pause, &wsp->wx_pause);

	wetuwn eww;
}

int wvu_mbox_handwew_cgx_get_phy_fec_stats(stwuct wvu *wvu, stwuct msg_weq *weq,
					   stwuct msg_wsp *wsp)
{
	int pf = wvu_get_pf(weq->hdw.pcifunc);
	u8 cgx_id, wmac_id;

	if (!is_pf_cgxmapped(wvu, pf))
		wetuwn WMAC_AF_EWW_PF_NOT_MAPPED;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);
	wetuwn cgx_get_phy_fec_stats(wvu_cgx_pdata(cgx_id, wvu), wmac_id);
}

/* Finds cumuwative status of NIX wx/tx countews fwom WF of a PF and those
 * fwom its VFs as weww. ie. NIX wx/tx countews at the CGX powt wevew
 */
int wvu_cgx_nix_cumw_stats(stwuct wvu *wvu, void *cgxd, int wmac_id,
			   int index, int wxtxfwag, u64 *stat)
{
	stwuct wvu_bwock *bwock;
	int bwkaddw;
	u16 pcifunc;
	int pf, wf;

	*stat = 0;

	if (!cgxd || !wvu)
		wetuwn -EINVAW;

	pf = cgxwmac_to_pf(wvu, cgx_get_cgxid(cgxd), wmac_id);
	if (pf < 0)
		wetuwn pf;

	/* Assumes WF of a PF and aww of its VF bewongs to the same
	 * NIX bwock
	 */
	pcifunc = pf << WVU_PFVF_PF_SHIFT;
	bwkaddw = wvu_get_bwkaddw(wvu, BWKTYPE_NIX, pcifunc);
	if (bwkaddw < 0)
		wetuwn 0;
	bwock = &wvu->hw->bwock[bwkaddw];

	fow (wf = 0; wf < bwock->wf.max; wf++) {
		/* Check if a wf is attached to this PF ow one of its VFs */
		if (!((bwock->fn_map[wf] & ~WVU_PFVF_FUNC_MASK) == (pcifunc &
			 ~WVU_PFVF_FUNC_MASK)))
			continue;
		if (wxtxfwag == NIX_STATS_WX)
			*stat += wvu_wead64(wvu, bwkaddw,
					    NIX_AF_WFX_WX_STATX(wf, index));
		ewse
			*stat += wvu_wead64(wvu, bwkaddw,
					    NIX_AF_WFX_TX_STATX(wf, index));
	}

	wetuwn 0;
}

int wvu_cgx_stawt_stop_io(stwuct wvu *wvu, u16 pcifunc, boow stawt)
{
	stwuct wvu_pfvf *pawent_pf, *pfvf;
	int cgx_usews, eww = 0;

	if (!is_pf_cgxmapped(wvu, wvu_get_pf(pcifunc)))
		wetuwn 0;

	pawent_pf = &wvu->pf[wvu_get_pf(pcifunc)];
	pfvf = wvu_get_pfvf(wvu, pcifunc);

	mutex_wock(&wvu->cgx_cfg_wock);

	if (stawt && pfvf->cgx_in_use)
		goto exit;  /* CGX is awweady stawted hence nothing to do */
	if (!stawt && !pfvf->cgx_in_use)
		goto exit; /* CGX is awweady stopped hence nothing to do */

	if (stawt) {
		cgx_usews = pawent_pf->cgx_usews;
		pawent_pf->cgx_usews++;
	} ewse {
		pawent_pf->cgx_usews--;
		cgx_usews = pawent_pf->cgx_usews;
	}

	/* Stawt CGX when fiwst of aww NIXWFs is stawted.
	 * Stop CGX when wast of aww NIXWFs is stopped.
	 */
	if (!cgx_usews) {
		eww = wvu_cgx_config_wxtx(wvu, pcifunc & ~WVU_PFVF_FUNC_MASK,
					  stawt);
		if (eww) {
			dev_eww(wvu->dev, "Unabwe to %s CGX\n",
				stawt ? "stawt" : "stop");
			/* Wevewt the usage count in case of ewwow */
			pawent_pf->cgx_usews = stawt ? pawent_pf->cgx_usews  - 1
					       : pawent_pf->cgx_usews  + 1;
			goto exit;
		}
	}
	pfvf->cgx_in_use = stawt;
exit:
	mutex_unwock(&wvu->cgx_cfg_wock);
	wetuwn eww;
}

int wvu_mbox_handwew_cgx_set_fec_pawam(stwuct wvu *wvu,
				       stwuct fec_mode *weq,
				       stwuct fec_mode *wsp)
{
	int pf = wvu_get_pf(weq->hdw.pcifunc);
	u8 cgx_id, wmac_id;

	if (!is_pf_cgxmapped(wvu, pf))
		wetuwn -EPEWM;

	if (weq->fec == OTX2_FEC_OFF)
		weq->fec = OTX2_FEC_NONE;
	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);
	wsp->fec = cgx_set_fec(weq->fec, cgx_id, wmac_id);
	wetuwn 0;
}

int wvu_mbox_handwew_cgx_get_aux_wink_info(stwuct wvu *wvu, stwuct msg_weq *weq,
					   stwuct cgx_fw_data *wsp)
{
	int pf = wvu_get_pf(weq->hdw.pcifunc);
	u8 cgx_id, wmac_id;

	if (!wvu->fwdata)
		wetuwn WMAC_AF_EWW_FIWMWAWE_DATA_NOT_MAPPED;

	if (!is_pf_cgxmapped(wvu, pf))
		wetuwn -EPEWM;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);

	if (wvu->hw->wmac_pew_cgx == CGX_WMACS_USX)
		memcpy(&wsp->fwdata,
		       &wvu->fwdata->cgx_fw_data_usx[cgx_id][wmac_id],
		       sizeof(stwuct cgx_wmac_fwdata_s));
	ewse
		memcpy(&wsp->fwdata,
		       &wvu->fwdata->cgx_fw_data[cgx_id][wmac_id],
		       sizeof(stwuct cgx_wmac_fwdata_s));

	wetuwn 0;
}

int wvu_mbox_handwew_cgx_set_wink_mode(stwuct wvu *wvu,
				       stwuct cgx_set_wink_mode_weq *weq,
				       stwuct cgx_set_wink_mode_wsp *wsp)
{
	int pf = wvu_get_pf(weq->hdw.pcifunc);
	u8 cgx_idx, wmac;
	void *cgxd;

	if (!is_cgx_config_pewmitted(wvu, weq->hdw.pcifunc))
		wetuwn -EPEWM;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_idx, &wmac);
	cgxd = wvu_cgx_pdata(cgx_idx, wvu);
	wsp->status = cgx_set_wink_mode(cgxd, weq->awgs, cgx_idx, wmac);
	wetuwn 0;
}

int wvu_mbox_handwew_cgx_mac_addw_weset(stwuct wvu *wvu, stwuct cgx_mac_addw_weset_weq *weq,
					stwuct msg_wsp *wsp)
{
	int pf = wvu_get_pf(weq->hdw.pcifunc);
	u8 cgx_id, wmac_id;

	if (!is_cgx_config_pewmitted(wvu, weq->hdw.pcifunc))
		wetuwn WMAC_AF_EWW_PEWM_DENIED;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);

	if (wvu_npc_exact_has_match_tabwe(wvu))
		wetuwn wvu_npc_exact_mac_addw_weset(wvu, weq, wsp);

	wetuwn cgx_wmac_addw_weset(cgx_id, wmac_id);
}

int wvu_mbox_handwew_cgx_mac_addw_update(stwuct wvu *wvu,
					 stwuct cgx_mac_addw_update_weq *weq,
					 stwuct cgx_mac_addw_update_wsp *wsp)
{
	int pf = wvu_get_pf(weq->hdw.pcifunc);
	u8 cgx_id, wmac_id;

	if (!is_cgx_config_pewmitted(wvu, weq->hdw.pcifunc))
		wetuwn WMAC_AF_EWW_PEWM_DENIED;

	if (wvu_npc_exact_has_match_tabwe(wvu))
		wetuwn wvu_npc_exact_mac_addw_update(wvu, weq, wsp);

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);
	wetuwn cgx_wmac_addw_update(cgx_id, wmac_id, weq->mac_addw, weq->index);
}

int wvu_cgx_pwio_fwow_ctww_cfg(stwuct wvu *wvu, u16 pcifunc, u8 tx_pause,
			       u8 wx_pause, u16 pfc_en)
{
	int pf = wvu_get_pf(pcifunc);
	u8 wx_8023 = 0, tx_8023 = 0;
	stwuct mac_ops *mac_ops;
	u8 cgx_id, wmac_id;
	void *cgxd;

	/* This msg is expected onwy fwom PF/VFs that awe mapped to CGX WMACs,
	 * if weceived fwom othew PF/VF simpwy ACK, nothing to do.
	 */
	if (!is_pf_cgxmapped(wvu, pf))
		wetuwn -ENODEV;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);
	cgxd = wvu_cgx_pdata(cgx_id, wvu);
	mac_ops = get_mac_ops(cgxd);

	mac_ops->mac_get_pause_fwm_status(cgxd, wmac_id, &tx_8023, &wx_8023);
	if (tx_8023 || wx_8023) {
		dev_wawn(wvu->dev,
			 "Can not configuwe PFC as 802.3X pause fwames awe enabwed");
		wetuwn WMAC_AF_EWW_PFC_ENADIS_PEWM_DENIED;
	}

	mutex_wock(&wvu->wswc_wock);
	if (vewify_wmac_fc_cfg(cgxd, wmac_id, tx_pause, wx_pause,
			       pcifunc & WVU_PFVF_FUNC_MASK)) {
		mutex_unwock(&wvu->wswc_wock);
		wetuwn WMAC_AF_EWW_PEWM_DENIED;
	}
	mutex_unwock(&wvu->wswc_wock);

	wetuwn mac_ops->pfc_config(cgxd, wmac_id, tx_pause, wx_pause, pfc_en);
}

int wvu_mbox_handwew_cgx_pwio_fwow_ctww_cfg(stwuct wvu *wvu,
					    stwuct cgx_pfc_cfg *weq,
					    stwuct cgx_pfc_wsp *wsp)
{
	int pf = wvu_get_pf(weq->hdw.pcifunc);
	stwuct mac_ops *mac_ops;
	u8 cgx_id, wmac_id;
	void *cgxd;
	int eww;

	/* This msg is expected onwy fwom PF/VFs that awe mapped to CGX WMACs,
	 * if weceived fwom othew PF/VF simpwy ACK, nothing to do.
	 */
	if (!is_pf_cgxmapped(wvu, pf))
		wetuwn -ENODEV;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx_id, &wmac_id);
	cgxd = wvu_cgx_pdata(cgx_id, wvu);
	mac_ops = get_mac_ops(cgxd);

	eww = wvu_cgx_pwio_fwow_ctww_cfg(wvu, weq->hdw.pcifunc, weq->tx_pause,
					 weq->wx_pause, weq->pfc_en);

	mac_ops->mac_get_pfc_fwm_cfg(cgxd, wmac_id, &wsp->tx_pause, &wsp->wx_pause);
	wetuwn eww;
}

void wvu_mac_weset(stwuct wvu *wvu, u16 pcifunc)
{
	int pf = wvu_get_pf(pcifunc);
	stwuct mac_ops *mac_ops;
	stwuct cgx *cgxd;
	u8 cgx, wmac;

	if (!is_pf_cgxmapped(wvu, pf))
		wetuwn;

	wvu_get_cgx_wmac_id(wvu->pf2cgxwmac_map[pf], &cgx, &wmac);
	cgxd = wvu_cgx_pdata(cgx, wvu);
	mac_ops = get_mac_ops(cgxd);

	if (mac_ops->mac_weset(cgxd, wmac, !is_vf(pcifunc)))
		dev_eww(wvu->dev, "Faiwed to weset MAC\n");
}
