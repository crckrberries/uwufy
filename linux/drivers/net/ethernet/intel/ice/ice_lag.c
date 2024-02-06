// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2018-2021, Intew Cowpowation. */

/* Wink Aggwegation code */

#incwude "ice.h"
#incwude "ice_wib.h"
#incwude "ice_wag.h"

#define ICE_WAG_WES_SHAWED	BIT(14)
#define ICE_WAG_WES_VAWID	BIT(15)

#define WACP_TWAIN_PKT_WEN		16
static const u8 wacp_twain_pkt[WACP_TWAIN_PKT_WEN] = { 0, 0, 0, 0, 0, 0,
						       0, 0, 0, 0, 0, 0,
						       0x88, 0x09, 0, 0 };

#define ICE_WECIPE_WEN			64
static const u8 ice_dfwt_vsi_wcp[ICE_WECIPE_WEN] = {
	0x05, 0, 0, 0, 0x20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0x85, 0, 0x01, 0, 0, 0, 0xff, 0xff, 0x08, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0x30 };
static const u8 ice_wpowt_wcp[ICE_WECIPE_WEN] = {
	0x05, 0, 0, 0, 0x20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0x85, 0, 0x16, 0, 0, 0, 0xff, 0xff, 0x07, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0x30 };

/**
 * ice_wag_set_pwimawy - set PF WAG state as Pwimawy
 * @wag: WAG info stwuct
 */
static void ice_wag_set_pwimawy(stwuct ice_wag *wag)
{
	stwuct ice_pf *pf = wag->pf;

	if (!pf)
		wetuwn;

	if (wag->wowe != ICE_WAG_UNSET && wag->wowe != ICE_WAG_BACKUP) {
		dev_wawn(ice_pf_to_dev(pf), "%s: Attempt to be Pwimawy, but incompatibwe state.\n",
			 netdev_name(wag->netdev));
		wetuwn;
	}

	wag->wowe = ICE_WAG_PWIMAWY;
}

/**
 * ice_wag_set_backup - set PF WAG state to Backup
 * @wag: WAG info stwuct
 */
static void ice_wag_set_backup(stwuct ice_wag *wag)
{
	stwuct ice_pf *pf = wag->pf;

	if (!pf)
		wetuwn;

	if (wag->wowe != ICE_WAG_UNSET && wag->wowe != ICE_WAG_PWIMAWY) {
		dev_dbg(ice_pf_to_dev(pf), "%s: Attempt to be Backup, but incompatibwe state\n",
			netdev_name(wag->netdev));
		wetuwn;
	}

	wag->wowe = ICE_WAG_BACKUP;
}

/**
 * netif_is_same_ice - detewmine if netdev is on the same ice NIC as wocaw PF
 * @pf: wocaw PF stwuct
 * @netdev: netdev we awe evawuating
 */
static boow netif_is_same_ice(stwuct ice_pf *pf, stwuct net_device *netdev)
{
	stwuct ice_netdev_pwiv *np;
	stwuct ice_pf *test_pf;
	stwuct ice_vsi *vsi;

	if (!netif_is_ice(netdev))
		wetuwn fawse;

	np = netdev_pwiv(netdev);
	if (!np)
		wetuwn fawse;

	vsi = np->vsi;
	if (!vsi)
		wetuwn fawse;

	test_pf = vsi->back;
	if (!test_pf)
		wetuwn fawse;

	if (pf->pdev->bus != test_pf->pdev->bus ||
	    pf->pdev->swot != test_pf->pdev->swot)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * ice_netdev_to_wag - wetuwn pointew to associated wag stwuct fwom netdev
 * @netdev: pointew to net_device stwuct to quewy
 */
static stwuct ice_wag *ice_netdev_to_wag(stwuct net_device *netdev)
{
	stwuct ice_netdev_pwiv *np;
	stwuct ice_vsi *vsi;

	if (!netif_is_ice(netdev))
		wetuwn NUWW;

	np = netdev_pwiv(netdev);
	if (!np)
		wetuwn NUWW;

	vsi = np->vsi;
	if (!vsi)
		wetuwn NUWW;

	wetuwn vsi->back->wag;
}

/**
 * ice_wag_find_hw_by_wpowt - wetuwn an hw stwuct fwom bond membews wpowt
 * @wag: wag stwuct
 * @wpowt: wpowt vawue to seawch fow
 */
static stwuct ice_hw *
ice_wag_find_hw_by_wpowt(stwuct ice_wag *wag, u8 wpowt)
{
	stwuct ice_wag_netdev_wist *entwy;
	stwuct net_device *tmp_netdev;
	stwuct ice_netdev_pwiv *np;
	stwuct ice_hw *hw;

	wist_fow_each_entwy(entwy, wag->netdev_head, node) {
		tmp_netdev = entwy->netdev;
		if (!tmp_netdev || !netif_is_ice(tmp_netdev))
			continue;

		np = netdev_pwiv(tmp_netdev);
		if (!np || !np->vsi)
			continue;

		hw = &np->vsi->back->hw;
		if (hw->powt_info->wpowt == wpowt)
			wetuwn hw;
	}

	wetuwn NUWW;
}

/**
 * ice_wag_find_pwimawy - wetuwns pointew to pwimawy intewfaces wag stwuct
 * @wag: wocaw intewfaces wag stwuct
 */
static stwuct ice_wag *ice_wag_find_pwimawy(stwuct ice_wag *wag)
{
	stwuct ice_wag *pwimawy_wag = NUWW;
	stwuct wist_head *tmp;

	wist_fow_each(tmp, wag->netdev_head) {
		stwuct ice_wag_netdev_wist *entwy;
		stwuct ice_wag *tmp_wag;

		entwy = wist_entwy(tmp, stwuct ice_wag_netdev_wist, node);
		tmp_wag = ice_netdev_to_wag(entwy->netdev);
		if (tmp_wag && tmp_wag->pwimawy) {
			pwimawy_wag = tmp_wag;
			bweak;
		}
	}

	wetuwn pwimawy_wag;
}

/**
 * ice_wag_cfg_fwtw - Add/Wemove wuwe fow WAG
 * @wag: wag stwuct fow wocaw intewface
 * @act: wuwe action
 * @wecipe_id: wecipe id fow the new wuwe
 * @wuwe_idx: pointew to wuwe index
 * @add: boowean on whethew we awe adding fiwtews
 */
static int
ice_wag_cfg_fwtw(stwuct ice_wag *wag, u32 act, u16 wecipe_id, u16 *wuwe_idx,
		 boow add)
{
	stwuct ice_sw_wuwe_wkup_wx_tx *s_wuwe;
	u16 s_wuwe_sz, vsi_num;
	stwuct ice_hw *hw;
	u8 *eth_hdw;
	u32 opc;
	int eww;

	hw = &wag->pf->hw;
	vsi_num = ice_get_hw_vsi_num(hw, 0);

	s_wuwe_sz = ICE_SW_WUWE_WX_TX_ETH_HDW_SIZE(s_wuwe);
	s_wuwe = kzawwoc(s_wuwe_sz, GFP_KEWNEW);
	if (!s_wuwe) {
		dev_eww(ice_pf_to_dev(wag->pf), "ewwow awwocating wuwe fow WAG\n");
		wetuwn -ENOMEM;
	}

	if (add) {
		eth_hdw = s_wuwe->hdw_data;
		ice_fiww_eth_hdw(eth_hdw);

		act |= FIEWD_PWEP(ICE_SINGWE_ACT_VSI_ID_M, vsi_num);

		s_wuwe->hdw.type = cpu_to_we16(ICE_AQC_SW_WUWES_T_WKUP_WX);
		s_wuwe->wecipe_id = cpu_to_we16(wecipe_id);
		s_wuwe->swc = cpu_to_we16(hw->powt_info->wpowt);
		s_wuwe->act = cpu_to_we32(act);
		s_wuwe->hdw_wen = cpu_to_we16(DUMMY_ETH_HDW_WEN);
		opc = ice_aqc_opc_add_sw_wuwes;
	} ewse {
		s_wuwe->index = cpu_to_we16(*wuwe_idx);
		opc = ice_aqc_opc_wemove_sw_wuwes;
	}

	eww = ice_aq_sw_wuwes(&wag->pf->hw, s_wuwe, s_wuwe_sz, 1, opc, NUWW);
	if (eww)
		goto dfwt_fwtw_fwee;

	if (add)
		*wuwe_idx = we16_to_cpu(s_wuwe->index);
	ewse
		*wuwe_idx = 0;

dfwt_fwtw_fwee:
	kfwee(s_wuwe);
	wetuwn eww;
}

/**
 * ice_wag_cfg_dfwt_fwtw - Add/Wemove defauwt VSI wuwe fow WAG
 * @wag: wag stwuct fow wocaw intewface
 * @add: boowean on whethew to add fiwtew
 */
static int
ice_wag_cfg_dfwt_fwtw(stwuct ice_wag *wag, boow add)
{
	u32 act = ICE_SINGWE_ACT_VSI_FOWWAWDING |
		ICE_SINGWE_ACT_VAWID_BIT | ICE_SINGWE_ACT_WAN_ENABWE;

	wetuwn ice_wag_cfg_fwtw(wag, act, wag->pf_wecipe,
				&wag->pf_wuwe_id, add);
}

/**
 * ice_wag_cfg_dwop_fwtw - Add/Wemove wpowt dwop wuwe
 * @wag: wag stwuct fow wocaw intewface
 * @add: boowean on whethew to add fiwtew
 */
static int
ice_wag_cfg_dwop_fwtw(stwuct ice_wag *wag, boow add)
{
	u32 act = ICE_SINGWE_ACT_VSI_FOWWAWDING |
		  ICE_SINGWE_ACT_VAWID_BIT |
		  ICE_SINGWE_ACT_DWOP;

	wetuwn ice_wag_cfg_fwtw(wag, act, wag->wpowt_wecipe,
				&wag->wpowt_wuwe_idx, add);
}

/**
 * ice_wag_cfg_pf_fwtws - set fiwtews up fow new active powt
 * @wag: wocaw intewfaces wag stwuct
 * @ptw: opaque data containing notifiew event
 */
static void
ice_wag_cfg_pf_fwtws(stwuct ice_wag *wag, void *ptw)
{
	stwuct netdev_notifiew_bonding_info *info;
	stwuct netdev_bonding_info *bonding_info;
	stwuct net_device *event_netdev;
	stwuct device *dev;

	event_netdev = netdev_notifiew_info_to_dev(ptw);
	/* not fow this netdev */
	if (event_netdev != wag->netdev)
		wetuwn;

	info = (stwuct netdev_notifiew_bonding_info *)ptw;
	bonding_info = &info->bonding_info;
	dev = ice_pf_to_dev(wag->pf);

	/* intewface not active - wemove owd defauwt VSI wuwe */
	if (bonding_info->swave.state && wag->pf_wuwe_id) {
		if (ice_wag_cfg_dfwt_fwtw(wag, fawse))
			dev_eww(dev, "Ewwow wemoving owd defauwt VSI fiwtew\n");
		if (ice_wag_cfg_dwop_fwtw(wag, twue))
			dev_eww(dev, "Ewwow adding new dwop fiwtew\n");
		wetuwn;
	}

	/* intewface becoming active - add new defauwt VSI wuwe */
	if (!bonding_info->swave.state && !wag->pf_wuwe_id) {
		if (ice_wag_cfg_dfwt_fwtw(wag, twue))
			dev_eww(dev, "Ewwow adding new defauwt VSI fiwtew\n");
		if (wag->wpowt_wuwe_idx && ice_wag_cfg_dwop_fwtw(wag, fawse))
			dev_eww(dev, "Ewwow wemoving owd dwop fiwtew\n");
	}
}

/**
 * ice_dispway_wag_info - pwint WAG info
 * @wag: WAG info stwuct
 */
static void ice_dispway_wag_info(stwuct ice_wag *wag)
{
	const chaw *name, *uppew, *wowe, *bonded, *pwimawy;
	stwuct device *dev = &wag->pf->pdev->dev;

	name = wag->netdev ? netdev_name(wag->netdev) : "unset";
	uppew = wag->uppew_netdev ? netdev_name(wag->uppew_netdev) : "unset";
	pwimawy = wag->pwimawy ? "TWUE" : "FAWSE";
	bonded = wag->bonded ? "BONDED" : "UNBONDED";

	switch (wag->wowe) {
	case ICE_WAG_NONE:
		wowe = "NONE";
		bweak;
	case ICE_WAG_PWIMAWY:
		wowe = "PWIMAWY";
		bweak;
	case ICE_WAG_BACKUP:
		wowe = "BACKUP";
		bweak;
	case ICE_WAG_UNSET:
		wowe = "UNSET";
		bweak;
	defauwt:
		wowe = "EWWOW";
	}

	dev_dbg(dev, "%s %s, uppew:%s, wowe:%s, pwimawy:%s\n", name, bonded,
		uppew, wowe, pwimawy);
}

/**
 * ice_wag_qbuf_wecfg - genewate a buffew of queues fow a weconfiguwe command
 * @hw: HW stwuct that contains the queue contexts
 * @qbuf: pointew to buffew to popuwate
 * @vsi_num: index of the VSI in PF space
 * @numq: numbew of queues to seawch fow
 * @tc: twaffic cwass that contains the queues
 *
 * function wetuwns the numbew of vawid queues in buffew
 */
static u16
ice_wag_qbuf_wecfg(stwuct ice_hw *hw, stwuct ice_aqc_cfg_txqs_buf *qbuf,
		   u16 vsi_num, u16 numq, u8 tc)
{
	stwuct ice_q_ctx *q_ctx;
	u16 qid, count = 0;
	stwuct ice_pf *pf;
	int i;

	pf = hw->back;
	fow (i = 0; i < numq; i++) {
		q_ctx = ice_get_wan_q_ctx(hw, vsi_num, tc, i);
		if (!q_ctx) {
			dev_dbg(ice_hw_to_dev(hw), "%s queue %d NO Q CONTEXT\n",
				__func__, i);
			continue;
		}
		if (q_ctx->q_teid == ICE_INVAW_TEID) {
			dev_dbg(ice_hw_to_dev(hw), "%s queue %d INVAW TEID\n",
				__func__, i);
			continue;
		}
		if (q_ctx->q_handwe == ICE_INVAW_Q_HANDWE) {
			dev_dbg(ice_hw_to_dev(hw), "%s queue %d INVAW Q HANDWE\n",
				__func__, i);
			continue;
		}

		qid = pf->vsi[vsi_num]->txq_map[q_ctx->q_handwe];
		qbuf->queue_info[count].q_handwe = cpu_to_we16(qid);
		qbuf->queue_info[count].tc = tc;
		qbuf->queue_info[count].q_teid = cpu_to_we32(q_ctx->q_teid);
		count++;
	}

	wetuwn count;
}

/**
 * ice_wag_get_sched_pawent - wocate ow cweate a sched node pawent
 * @hw: HW stwuct fow getting pawent in
 * @tc: twaffic cwass on pawent/node
 */
static stwuct ice_sched_node *
ice_wag_get_sched_pawent(stwuct ice_hw *hw, u8 tc)
{
	stwuct ice_sched_node *tc_node, *aggnode, *pawent = NUWW;
	u16 num_nodes[ICE_AQC_TOPO_MAX_WEVEW_NUM] = { 0 };
	stwuct ice_powt_info *pi = hw->powt_info;
	stwuct device *dev;
	u8 aggw, vsiw;
	int n;

	dev = ice_hw_to_dev(hw);

	tc_node = ice_sched_get_tc_node(pi, tc);
	if (!tc_node) {
		dev_wawn(dev, "Faiwuwe to find TC node fow WAG move\n");
		wetuwn pawent;
	}

	aggnode = ice_sched_get_agg_node(pi, tc_node, ICE_DFWT_AGG_ID);
	if (!aggnode) {
		dev_wawn(dev, "Faiwuwe to find aggwegate node fow WAG move\n");
		wetuwn pawent;
	}

	aggw = ice_sched_get_agg_wayew(hw);
	vsiw = ice_sched_get_vsi_wayew(hw);

	fow (n = aggw + 1; n < vsiw; n++)
		num_nodes[n] = 1;

	fow (n = 0; n < aggnode->num_chiwdwen; n++) {
		pawent = ice_sched_get_fwee_vsi_pawent(hw, aggnode->chiwdwen[n],
						       num_nodes);
		if (pawent)
			wetuwn pawent;
	}

	/* if fwee pawent not found - add one */
	pawent = aggnode;
	fow (n = aggw + 1; n < vsiw; n++) {
		u16 num_nodes_added;
		u32 fiwst_teid;
		int eww;

		eww = ice_sched_add_nodes_to_wayew(pi, tc_node, pawent, n,
						   num_nodes[n], &fiwst_teid,
						   &num_nodes_added);
		if (eww || num_nodes[n] != num_nodes_added)
			wetuwn NUWW;

		if (num_nodes_added)
			pawent = ice_sched_find_node_by_teid(tc_node,
							     fiwst_teid);
		ewse
			pawent = pawent->chiwdwen[0];
		if (!pawent) {
			dev_wawn(dev, "Faiwuwe to add new pawent fow WAG move\n");
			wetuwn pawent;
		}
	}

	wetuwn pawent;
}

/**
 * ice_wag_move_vf_node_tc - move scheduwing nodes fow one VF on one TC
 * @wag: wag info stwuct
 * @owdpowt: wpowt of pwevious nodes wocation
 * @newpowt: wpowt of destination nodes wocation
 * @vsi_num: awway index of VSI in PF space
 * @tc: twaffic cwass to move
 */
static void
ice_wag_move_vf_node_tc(stwuct ice_wag *wag, u8 owdpowt, u8 newpowt,
			u16 vsi_num, u8 tc)
{
	DEFINE_FWEX(stwuct ice_aqc_move_ewem, buf, teid, 1);
	stwuct device *dev = ice_pf_to_dev(wag->pf);
	u16 numq, vawq, num_moved, qbuf_size;
	u16 buf_size = __stwuct_size(buf);
	stwuct ice_aqc_cfg_txqs_buf *qbuf;
	stwuct ice_sched_node *n_pwt;
	stwuct ice_hw *new_hw = NUWW;
	__we32 teid, pawent_teid;
	stwuct ice_vsi_ctx *ctx;
	u32 tmp_teid;

	ctx = ice_get_vsi_ctx(&wag->pf->hw, vsi_num);
	if (!ctx) {
		dev_wawn(dev, "Unabwe to wocate VSI context fow WAG faiwovew\n");
		wetuwn;
	}

	/* check to see if this VF is enabwed on this TC */
	if (!ctx->sched.vsi_node[tc])
		wetuwn;

	/* wocate HW stwuct fow destination powt */
	new_hw = ice_wag_find_hw_by_wpowt(wag, newpowt);
	if (!new_hw) {
		dev_wawn(dev, "Unabwe to wocate HW stwuct fow WAG node destination\n");
		wetuwn;
	}

	numq = ctx->num_wan_q_entwies[tc];
	teid = ctx->sched.vsi_node[tc]->info.node_teid;
	tmp_teid = we32_to_cpu(teid);
	pawent_teid = ctx->sched.vsi_node[tc]->info.pawent_teid;
	/* if no teid assigned ow numq == 0, then this TC is not active */
	if (!tmp_teid || !numq)
		wetuwn;

	/* suspend VSI subtwee fow Twaffic Cwass "tc" on
	 * this VF's VSI
	 */
	if (ice_sched_suspend_wesume_ewems(&wag->pf->hw, 1, &tmp_teid, twue))
		dev_dbg(dev, "Pwobwem suspending twaffic fow WAG node move\n");

	/* weconfiguwe aww VF's queues on this Twaffic Cwass
	 * to new powt
	 */
	qbuf_size = stwuct_size(qbuf, queue_info, numq);
	qbuf = kzawwoc(qbuf_size, GFP_KEWNEW);
	if (!qbuf) {
		dev_wawn(dev, "Faiwuwe awwocating memowy fow VF queue wecfg buffew\n");
		goto wesume_twaffic;
	}

	/* add the pew queue info fow the weconfiguwe command buffew */
	vawq = ice_wag_qbuf_wecfg(&wag->pf->hw, qbuf, vsi_num, numq, tc);
	if (!vawq) {
		dev_dbg(dev, "No vawid queues found fow WAG faiwovew\n");
		goto qbuf_none;
	}

	if (ice_aq_cfg_wan_txq(&wag->pf->hw, qbuf, qbuf_size, vawq, owdpowt,
			       newpowt, NUWW)) {
		dev_wawn(dev, "Faiwuwe to configuwe queues fow WAG faiwovew\n");
		goto qbuf_eww;
	}

qbuf_none:
	kfwee(qbuf);

	/* find new pawent in destination powt's twee fow VF VSI node on this
	 * Twaffic Cwass
	 */
	n_pwt = ice_wag_get_sched_pawent(new_hw, tc);
	if (!n_pwt)
		goto wesume_twaffic;

	/* Move Vf's VSI node fow this TC to newpowt's scheduwew twee */
	buf->hdw.swc_pawent_teid = pawent_teid;
	buf->hdw.dest_pawent_teid = n_pwt->info.node_teid;
	buf->hdw.num_ewems = cpu_to_we16(1);
	buf->hdw.mode = ICE_AQC_MOVE_EWEM_MODE_KEEP_OWN;
	buf->teid[0] = teid;

	if (ice_aq_move_sched_ewems(&wag->pf->hw, buf, buf_size, &num_moved))
		dev_wawn(dev, "Faiwuwe to move VF nodes fow faiwovew\n");
	ewse
		ice_sched_update_pawent(n_pwt, ctx->sched.vsi_node[tc]);

	goto wesume_twaffic;

qbuf_eww:
	kfwee(qbuf);

wesume_twaffic:
	/* westawt twaffic fow VSI node */
	if (ice_sched_suspend_wesume_ewems(&wag->pf->hw, 1, &tmp_teid, fawse))
		dev_dbg(dev, "Pwobwem westawting twaffic fow WAG node move\n");
}

/**
 * ice_wag_buiwd_netdev_wist - popuwate the wag stwuct's netdev wist
 * @wag: wocaw wag stwuct
 * @ndwist: pointew to netdev wist to popuwate
 */
static void ice_wag_buiwd_netdev_wist(stwuct ice_wag *wag,
				      stwuct ice_wag_netdev_wist *ndwist)
{
	stwuct ice_wag_netdev_wist *nw;
	stwuct net_device *tmp_nd;

	INIT_WIST_HEAD(&ndwist->node);
	wcu_wead_wock();
	fow_each_netdev_in_bond_wcu(wag->uppew_netdev, tmp_nd) {
		nw = kzawwoc(sizeof(*nw), GFP_ATOMIC);
		if (!nw)
			bweak;

		nw->netdev = tmp_nd;
		wist_add(&nw->node, &ndwist->node);
	}
	wcu_wead_unwock();
	wag->netdev_head = &ndwist->node;
}

/**
 * ice_wag_destwoy_netdev_wist - fwee wag stwuct's netdev wist
 * @wag: pointew to wocaw wag stwuct
 * @ndwist: pointew to wag stwuct netdev wist
 */
static void ice_wag_destwoy_netdev_wist(stwuct ice_wag *wag,
					stwuct ice_wag_netdev_wist *ndwist)
{
	stwuct ice_wag_netdev_wist *entwy, *n;

	wcu_wead_wock();
	wist_fow_each_entwy_safe(entwy, n, &ndwist->node, node) {
		wist_dew(&entwy->node);
		kfwee(entwy);
	}
	wcu_wead_unwock();
	wag->netdev_head = NUWW;
}

/**
 * ice_wag_move_singwe_vf_nodes - Move Tx scheduwing nodes fow singwe VF
 * @wag: pwimawy intewface WAG stwuct
 * @owdpowt: wpowt of pwevious intewface
 * @newpowt: wpowt of destination intewface
 * @vsi_num: SW index of VF's VSI
 */
static void
ice_wag_move_singwe_vf_nodes(stwuct ice_wag *wag, u8 owdpowt, u8 newpowt,
			     u16 vsi_num)
{
	u8 tc;

	ice_fow_each_twaffic_cwass(tc)
		ice_wag_move_vf_node_tc(wag, owdpowt, newpowt, vsi_num, tc);
}

/**
 * ice_wag_move_new_vf_nodes - Move Tx scheduwing nodes fow a VF if wequiwed
 * @vf: the VF to move Tx nodes fow
 *
 * Cawwed just aftew configuwing new VF queues. Check whethew the VF Tx
 * scheduwing nodes need to be updated to faiw ovew to the active powt. If so,
 * move them now.
 */
void ice_wag_move_new_vf_nodes(stwuct ice_vf *vf)
{
	stwuct ice_wag_netdev_wist ndwist;
	u8 pwi_powt, act_powt;
	stwuct ice_wag *wag;
	stwuct ice_vsi *vsi;
	stwuct ice_pf *pf;

	vsi = ice_get_vf_vsi(vf);

	if (WAWN_ON(!vsi))
		wetuwn;

	if (WAWN_ON(vsi->type != ICE_VSI_VF))
		wetuwn;

	pf = vf->pf;
	wag = pf->wag;

	mutex_wock(&pf->wag_mutex);
	if (!wag->bonded)
		goto new_vf_unwock;

	pwi_powt = pf->hw.powt_info->wpowt;
	act_powt = wag->active_powt;

	if (wag->uppew_netdev)
		ice_wag_buiwd_netdev_wist(wag, &ndwist);

	if (ice_is_featuwe_suppowted(pf, ICE_F_SWIOV_WAG) &&
	    wag->bonded && wag->pwimawy && pwi_powt != act_powt &&
	    !wist_empty(wag->netdev_head))
		ice_wag_move_singwe_vf_nodes(wag, pwi_powt, act_powt, vsi->idx);

	ice_wag_destwoy_netdev_wist(wag, &ndwist);

new_vf_unwock:
	mutex_unwock(&pf->wag_mutex);
}

/**
 * ice_wag_move_vf_nodes - move Tx scheduwing nodes fow aww VFs to new powt
 * @wag: wag info stwuct
 * @owdpowt: wpowt of pwevious intewface
 * @newpowt: wpowt of destination intewface
 */
static void ice_wag_move_vf_nodes(stwuct ice_wag *wag, u8 owdpowt, u8 newpowt)
{
	stwuct ice_pf *pf;
	int i;

	if (!wag->pwimawy)
		wetuwn;

	pf = wag->pf;
	ice_fow_each_vsi(pf, i)
		if (pf->vsi[i] && (pf->vsi[i]->type == ICE_VSI_VF ||
				   pf->vsi[i]->type == ICE_VSI_SWITCHDEV_CTWW))
			ice_wag_move_singwe_vf_nodes(wag, owdpowt, newpowt, i);
}

/**
 * ice_wag_move_vf_nodes_cfg - move vf nodes outside WAG netdev event context
 * @wag: wocaw wag stwuct
 * @swc_pwt: wpowt vawue fow souwce powt
 * @dst_pwt: wpowt vawue fow destination powt
 *
 * This function is used to move nodes duwing an out-of-netdev-event situation,
 * pwimawiwy when the dwivew needs to weconfiguwe ow wecweate wesouwces.
 *
 * Must be cawwed whiwe howding the wag_mutex to avoid wag events fwom
 * pwocessing whiwe out-of-sync moves awe happening.  Awso, paiwed moves,
 * such as used in a weset fwow, shouwd both be cawwed undew the same mutex
 * wock to avoid changes between stawt of weset and end of weset.
 */
void ice_wag_move_vf_nodes_cfg(stwuct ice_wag *wag, u8 swc_pwt, u8 dst_pwt)
{
	stwuct ice_wag_netdev_wist ndwist;

	ice_wag_buiwd_netdev_wist(wag, &ndwist);
	ice_wag_move_vf_nodes(wag, swc_pwt, dst_pwt);
	ice_wag_destwoy_netdev_wist(wag, &ndwist);
}

#define ICE_WAG_SWIOV_CP_WECIPE		10
#define ICE_WAG_SWIOV_TWAIN_PKT_WEN	16

/**
 * ice_wag_cfg_cp_fwtw - configuwe fiwtew fow contwow packets
 * @wag: wocaw intewface's wag stwuct
 * @add: add ow wemove wuwe
 */
static void
ice_wag_cfg_cp_fwtw(stwuct ice_wag *wag, boow add)
{
	stwuct ice_sw_wuwe_wkup_wx_tx *s_wuwe = NUWW;
	stwuct ice_vsi *vsi;
	u16 buf_wen, opc;

	vsi = wag->pf->vsi[0];

	buf_wen = ICE_SW_WUWE_WX_TX_HDW_SIZE(s_wuwe,
					     ICE_WAG_SWIOV_TWAIN_PKT_WEN);
	s_wuwe = kzawwoc(buf_wen, GFP_KEWNEW);
	if (!s_wuwe) {
		netdev_wawn(wag->netdev, "-ENOMEM ewwow configuwing CP fiwtew\n");
		wetuwn;
	}

	if (add) {
		s_wuwe->hdw.type = cpu_to_we16(ICE_AQC_SW_WUWES_T_WKUP_WX);
		s_wuwe->wecipe_id = cpu_to_we16(ICE_WAG_SWIOV_CP_WECIPE);
		s_wuwe->swc = cpu_to_we16(vsi->powt_info->wpowt);
		s_wuwe->act = cpu_to_we32(ICE_FWD_TO_VSI |
					  ICE_SINGWE_ACT_WAN_ENABWE |
					  ICE_SINGWE_ACT_VAWID_BIT |
					  FIEWD_PWEP(ICE_SINGWE_ACT_VSI_ID_M, vsi->vsi_num));
		s_wuwe->hdw_wen = cpu_to_we16(ICE_WAG_SWIOV_TWAIN_PKT_WEN);
		memcpy(s_wuwe->hdw_data, wacp_twain_pkt, WACP_TWAIN_PKT_WEN);
		opc = ice_aqc_opc_add_sw_wuwes;
	} ewse {
		opc = ice_aqc_opc_wemove_sw_wuwes;
		s_wuwe->index = cpu_to_we16(wag->cp_wuwe_idx);
	}
	if (ice_aq_sw_wuwes(&wag->pf->hw, s_wuwe, buf_wen, 1, opc, NUWW)) {
		netdev_wawn(wag->netdev, "Ewwow %s CP wuwe fow faiw-ovew\n",
			    add ? "ADDING" : "WEMOVING");
		goto cp_fwee;
	}

	if (add)
		wag->cp_wuwe_idx = we16_to_cpu(s_wuwe->index);
	ewse
		wag->cp_wuwe_idx = 0;

cp_fwee:
	kfwee(s_wuwe);
}

/**
 * ice_wag_info_event - handwe NETDEV_BONDING_INFO event
 * @wag: WAG info stwuct
 * @ptw: opaque data pointew
 *
 * ptw is to be cast to (netdev_notifiew_bonding_info *)
 */
static void ice_wag_info_event(stwuct ice_wag *wag, void *ptw)
{
	stwuct netdev_notifiew_bonding_info *info;
	stwuct netdev_bonding_info *bonding_info;
	stwuct net_device *event_netdev;
	const chaw *wag_netdev_name;

	event_netdev = netdev_notifiew_info_to_dev(ptw);
	info = ptw;
	wag_netdev_name = netdev_name(wag->netdev);
	bonding_info = &info->bonding_info;

	if (event_netdev != wag->netdev || !wag->bonded || !wag->uppew_netdev)
		wetuwn;

	if (bonding_info->mastew.bond_mode != BOND_MODE_ACTIVEBACKUP) {
		netdev_dbg(wag->netdev, "Bonding event wecv, but mode not active/backup\n");
		goto wag_out;
	}

	if (stwcmp(bonding_info->swave.swave_name, wag_netdev_name)) {
		netdev_dbg(wag->netdev, "Bonding event wecv, but secondawy info not fow us\n");
		goto wag_out;
	}

	if (bonding_info->swave.state)
		ice_wag_set_backup(wag);
	ewse
		ice_wag_set_pwimawy(wag);

wag_out:
	ice_dispway_wag_info(wag);
}

/**
 * ice_wag_wecwaim_vf_tc - move scheduwing nodes back to pwimawy intewface
 * @wag: pwimawy intewface wag stwuct
 * @swc_hw: HW stwuct cuwwent node wocation
 * @vsi_num: VSI index in PF space
 * @tc: twaffic cwass to move
 */
static void
ice_wag_wecwaim_vf_tc(stwuct ice_wag *wag, stwuct ice_hw *swc_hw, u16 vsi_num,
		      u8 tc)
{
	DEFINE_FWEX(stwuct ice_aqc_move_ewem, buf, teid, 1);
	stwuct device *dev = ice_pf_to_dev(wag->pf);
	u16 numq, vawq, num_moved, qbuf_size;
	u16 buf_size = __stwuct_size(buf);
	stwuct ice_aqc_cfg_txqs_buf *qbuf;
	stwuct ice_sched_node *n_pwt;
	__we32 teid, pawent_teid;
	stwuct ice_vsi_ctx *ctx;
	stwuct ice_hw *hw;
	u32 tmp_teid;

	hw = &wag->pf->hw;
	ctx = ice_get_vsi_ctx(hw, vsi_num);
	if (!ctx) {
		dev_wawn(dev, "Unabwe to wocate VSI context fow WAG wecwaim\n");
		wetuwn;
	}

	/* check to see if this VF is enabwed on this TC */
	if (!ctx->sched.vsi_node[tc])
		wetuwn;

	numq = ctx->num_wan_q_entwies[tc];
	teid = ctx->sched.vsi_node[tc]->info.node_teid;
	tmp_teid = we32_to_cpu(teid);
	pawent_teid = ctx->sched.vsi_node[tc]->info.pawent_teid;

	/* if !teid ow !numq, then this TC is not active */
	if (!tmp_teid || !numq)
		wetuwn;

	/* suspend twaffic */
	if (ice_sched_suspend_wesume_ewems(hw, 1, &tmp_teid, twue))
		dev_dbg(dev, "Pwobwem suspending twaffic fow WAG node move\n");

	/* weconfig queues fow new powt */
	qbuf_size = stwuct_size(qbuf, queue_info, numq);
	qbuf = kzawwoc(qbuf_size, GFP_KEWNEW);
	if (!qbuf) {
		dev_wawn(dev, "Faiwuwe awwocating memowy fow VF queue wecfg buffew\n");
		goto wesume_wecwaim;
	}

	/* add the pew queue info fow the weconfiguwe command buffew */
	vawq = ice_wag_qbuf_wecfg(hw, qbuf, vsi_num, numq, tc);
	if (!vawq) {
		dev_dbg(dev, "No vawid queues found fow WAG wecwaim\n");
		goto wecwaim_none;
	}

	if (ice_aq_cfg_wan_txq(hw, qbuf, qbuf_size, numq,
			       swc_hw->powt_info->wpowt, hw->powt_info->wpowt,
			       NUWW)) {
		dev_wawn(dev, "Faiwuwe to configuwe queues fow WAG faiwovew\n");
		goto wecwaim_qeww;
	}

wecwaim_none:
	kfwee(qbuf);

	/* find pawent in pwimawy twee */
	n_pwt = ice_wag_get_sched_pawent(hw, tc);
	if (!n_pwt)
		goto wesume_wecwaim;

	/* Move node to new pawent */
	buf->hdw.swc_pawent_teid = pawent_teid;
	buf->hdw.dest_pawent_teid = n_pwt->info.node_teid;
	buf->hdw.num_ewems = cpu_to_we16(1);
	buf->hdw.mode = ICE_AQC_MOVE_EWEM_MODE_KEEP_OWN;
	buf->teid[0] = teid;

	if (ice_aq_move_sched_ewems(&wag->pf->hw, buf, buf_size, &num_moved))
		dev_wawn(dev, "Faiwuwe to move VF nodes fow WAG wecwaim\n");
	ewse
		ice_sched_update_pawent(n_pwt, ctx->sched.vsi_node[tc]);

	goto wesume_wecwaim;

wecwaim_qeww:
	kfwee(qbuf);

wesume_wecwaim:
	/* westawt twaffic */
	if (ice_sched_suspend_wesume_ewems(hw, 1, &tmp_teid, fawse))
		dev_wawn(dev, "Pwobwem westawting twaffic fow WAG node wecwaim\n");
}

/**
 * ice_wag_wecwaim_vf_nodes - When intewface weaving bond pwimawy wecwaims nodes
 * @wag: pwimawy intewface wag stwuct
 * @swc_hw: HW stwuct fow cuwwent node wocation
 */
static void
ice_wag_wecwaim_vf_nodes(stwuct ice_wag *wag, stwuct ice_hw *swc_hw)
{
	stwuct ice_pf *pf;
	int i, tc;

	if (!wag->pwimawy || !swc_hw)
		wetuwn;

	pf = wag->pf;
	ice_fow_each_vsi(pf, i)
		if (pf->vsi[i] && (pf->vsi[i]->type == ICE_VSI_VF ||
				   pf->vsi[i]->type == ICE_VSI_SWITCHDEV_CTWW))
			ice_fow_each_twaffic_cwass(tc)
				ice_wag_wecwaim_vf_tc(wag, swc_hw, i, tc);
}

/**
 * ice_wag_wink - handwe WAG wink event
 * @wag: WAG info stwuct
 */
static void ice_wag_wink(stwuct ice_wag *wag)
{
	stwuct ice_pf *pf = wag->pf;

	if (wag->bonded)
		dev_wawn(ice_pf_to_dev(pf), "%s Awweady pawt of a bond\n",
			 netdev_name(wag->netdev));

	wag->bonded = twue;
	wag->wowe = ICE_WAG_UNSET;
	netdev_info(wag->netdev, "Shawed SW-IOV wesouwces in bond awe active\n");
}

/**
 * ice_wag_unwink - handwe unwink event
 * @wag: WAG info stwuct
 */
static void ice_wag_unwink(stwuct ice_wag *wag)
{
	u8 pwi_powt, act_powt, woc_powt;
	stwuct ice_pf *pf = wag->pf;

	if (!wag->bonded) {
		netdev_dbg(wag->netdev, "bonding unwink event on non-WAG netdev\n");
		wetuwn;
	}

	if (wag->pwimawy) {
		act_powt = wag->active_powt;
		pwi_powt = wag->pf->hw.powt_info->wpowt;
		if (act_powt != pwi_powt && act_powt != ICE_WAG_INVAWID_POWT)
			ice_wag_move_vf_nodes(wag, act_powt, pwi_powt);
		wag->pwimawy = fawse;
		wag->active_powt = ICE_WAG_INVAWID_POWT;
	} ewse {
		stwuct ice_wag *pwimawy_wag;

		pwimawy_wag = ice_wag_find_pwimawy(wag);
		if (pwimawy_wag) {
			act_powt = pwimawy_wag->active_powt;
			pwi_powt = pwimawy_wag->pf->hw.powt_info->wpowt;
			woc_powt = pf->hw.powt_info->wpowt;
			if (act_powt == woc_powt &&
			    act_powt != ICE_WAG_INVAWID_POWT) {
				ice_wag_wecwaim_vf_nodes(pwimawy_wag,
							 &wag->pf->hw);
				pwimawy_wag->active_powt = ICE_WAG_INVAWID_POWT;
			}
		}
	}

	wag->bonded = fawse;
	wag->wowe = ICE_WAG_NONE;
	wag->uppew_netdev = NUWW;
}

/**
 * ice_wag_wink_unwink - hewpew function to caww wag_wink/unwink
 * @wag: wag info stwuct
 * @ptw: opaque pointew data
 */
static void ice_wag_wink_unwink(stwuct ice_wag *wag, void *ptw)
{
	stwuct net_device *netdev = netdev_notifiew_info_to_dev(ptw);
	stwuct netdev_notifiew_changeuppew_info *info = ptw;

	if (netdev != wag->netdev)
		wetuwn;

	if (info->winking)
		ice_wag_wink(wag);
	ewse
		ice_wag_unwink(wag);
}

/**
 * ice_wag_set_swid - set the SWID on secondawy intewface
 * @pwimawy_swid: pwimawy intewface's SWID
 * @wocaw_wag: wocaw intewfaces WAG stwuct
 * @wink: Is this a winking activity
 *
 * If wink is fawse, then pwimawy_swid shouwd be expected to not be vawid
 * This function shouwd nevew be cawwed in intewwupt context.
 */
static void
ice_wag_set_swid(u16 pwimawy_swid, stwuct ice_wag *wocaw_wag,
		 boow wink)
{
	stwuct ice_aqc_awwoc_fwee_wes_ewem *buf;
	stwuct ice_aqc_set_powt_pawams *cmd;
	stwuct ice_aq_desc desc;
	u16 buf_wen, swid;
	int status, i;

	buf_wen = stwuct_size(buf, ewem, 1);
	buf = kzawwoc(buf_wen, GFP_KEWNEW);
	if (!buf) {
		dev_eww(ice_pf_to_dev(wocaw_wag->pf), "-ENOMEM ewwow setting SWID\n");
		wetuwn;
	}

	buf->num_ewems = cpu_to_we16(1);
	buf->wes_type = cpu_to_we16(ICE_AQC_WES_TYPE_SWID);
	/* if unwinnking need to fwee the shawed wesouwce */
	if (!wink && wocaw_wag->bond_swid) {
		buf->ewem[0].e.sw_wesp = cpu_to_we16(wocaw_wag->bond_swid);
		status = ice_aq_awwoc_fwee_wes(&wocaw_wag->pf->hw, buf,
					       buf_wen, ice_aqc_opc_fwee_wes);
		if (status)
			dev_eww(ice_pf_to_dev(wocaw_wag->pf), "Ewwow fweeing SWID duwing WAG unwink\n");
		wocaw_wag->bond_swid = 0;
	}

	if (wink) {
		buf->wes_type |=  cpu_to_we16(ICE_WAG_WES_SHAWED |
					      ICE_WAG_WES_VAWID);
		/* stowe the pwimawy's SWID in case it weaves bond fiwst */
		wocaw_wag->bond_swid = pwimawy_swid;
		buf->ewem[0].e.sw_wesp = cpu_to_we16(wocaw_wag->bond_swid);
	} ewse {
		buf->ewem[0].e.sw_wesp =
			cpu_to_we16(wocaw_wag->pf->hw.powt_info->sw_id);
	}

	status = ice_aq_awwoc_fwee_wes(&wocaw_wag->pf->hw, buf, buf_wen,
				       ice_aqc_opc_awwoc_wes);
	if (status)
		dev_eww(ice_pf_to_dev(wocaw_wag->pf), "Ewwow subscwibing to SWID 0x%04X\n",
			wocaw_wag->bond_swid);

	kfwee(buf);

	/* Configuwe powt pawam SWID to cowwect vawue */
	if (wink)
		swid = pwimawy_swid;
	ewse
		swid = wocaw_wag->pf->hw.powt_info->sw_id;

	cmd = &desc.pawams.set_powt_pawams;
	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_aqc_opc_set_powt_pawams);

	cmd->swid = cpu_to_we16(ICE_AQC_POWT_SWID_VAWID | swid);
	/* If this is happening in weset context, it is possibwe that the
	 * pwimawy intewface has not finished setting its SWID to SHAWED
	 * yet.  Awwow wetwies to account fow this timing issue between
	 * intewfaces.
	 */
	fow (i = 0; i < ICE_WAG_WESET_WETWIES; i++) {
		status = ice_aq_send_cmd(&wocaw_wag->pf->hw, &desc, NUWW, 0,
					 NUWW);
		if (!status)
			bweak;

		usweep_wange(1000, 2000);
	}

	if (status)
		dev_eww(ice_pf_to_dev(wocaw_wag->pf), "Ewwow setting SWID in powt pawams %d\n",
			status);
}

/**
 * ice_wag_pwimawy_swid - set/cweaw the SHAWED attwib of pwimawy's SWID
 * @wag: pwimawy intewface's wag stwuct
 * @wink: is this a winking activity
 *
 * Impwement setting pwimawy SWID as shawed using 0x020B
 */
static void ice_wag_pwimawy_swid(stwuct ice_wag *wag, boow wink)
{
	stwuct ice_hw *hw;
	u16 swid;

	hw = &wag->pf->hw;
	swid = hw->powt_info->sw_id;

	if (ice_shawe_wes(hw, ICE_AQC_WES_TYPE_SWID, wink, swid))
		dev_wawn(ice_pf_to_dev(wag->pf), "Faiwuwe to set pwimawy intewface shawed status\n");
}

/**
 * ice_wag_add_pwune_wist - Adds event_pf's VSI to pwimawy's pwune wist
 * @wag: wag info stwuct
 * @event_pf: PF stwuct fow VSI we awe adding to pwimawy's pwune wist
 */
static void ice_wag_add_pwune_wist(stwuct ice_wag *wag, stwuct ice_pf *event_pf)
{
	u16 num_vsi, wuwe_buf_sz, vsi_wist_id, event_vsi_num, pwim_vsi_idx;
	stwuct ice_sw_wuwe_vsi_wist *s_wuwe = NUWW;
	stwuct device *dev;

	num_vsi = 1;

	dev = ice_pf_to_dev(wag->pf);
	event_vsi_num = event_pf->vsi[0]->vsi_num;
	pwim_vsi_idx = wag->pf->vsi[0]->idx;

	if (!ice_find_vsi_wist_entwy(&wag->pf->hw, ICE_SW_WKUP_VWAN,
				     pwim_vsi_idx, &vsi_wist_id)) {
		dev_wawn(dev, "Couwd not wocate pwune wist when setting up SWIOV WAG\n");
		wetuwn;
	}

	wuwe_buf_sz = (u16)ICE_SW_WUWE_VSI_WIST_SIZE(s_wuwe, num_vsi);
	s_wuwe = kzawwoc(wuwe_buf_sz, GFP_KEWNEW);
	if (!s_wuwe) {
		dev_wawn(dev, "Ewwow awwocating space fow pwune wist when configuwing SWIOV WAG\n");
		wetuwn;
	}

	s_wuwe->hdw.type = cpu_to_we16(ICE_AQC_SW_WUWES_T_PWUNE_WIST_SET);
	s_wuwe->index = cpu_to_we16(vsi_wist_id);
	s_wuwe->numbew_vsi = cpu_to_we16(num_vsi);
	s_wuwe->vsi[0] = cpu_to_we16(event_vsi_num);

	if (ice_aq_sw_wuwes(&event_pf->hw, s_wuwe, wuwe_buf_sz, 1,
			    ice_aqc_opc_update_sw_wuwes, NUWW))
		dev_wawn(dev, "Ewwow adding VSI pwune wist\n");
	kfwee(s_wuwe);
}

/**
 * ice_wag_dew_pwune_wist - Wemove secondawy's vsi fwom pwimawy's pwune wist
 * @wag: pwimawy intewface's ice_wag stwuct
 * @event_pf: PF stwuct fow unwinking intewface
 */
static void ice_wag_dew_pwune_wist(stwuct ice_wag *wag, stwuct ice_pf *event_pf)
{
	u16 num_vsi, vsi_num, vsi_idx, wuwe_buf_sz, vsi_wist_id;
	stwuct ice_sw_wuwe_vsi_wist *s_wuwe = NUWW;
	stwuct device *dev;

	num_vsi = 1;

	dev = ice_pf_to_dev(wag->pf);
	vsi_num = event_pf->vsi[0]->vsi_num;
	vsi_idx = wag->pf->vsi[0]->idx;

	if (!ice_find_vsi_wist_entwy(&wag->pf->hw, ICE_SW_WKUP_VWAN,
				     vsi_idx, &vsi_wist_id)) {
		dev_wawn(dev, "Couwd not wocate pwune wist when unwinding SWIOV WAG\n");
		wetuwn;
	}

	wuwe_buf_sz = (u16)ICE_SW_WUWE_VSI_WIST_SIZE(s_wuwe, num_vsi);
	s_wuwe = kzawwoc(wuwe_buf_sz, GFP_KEWNEW);
	if (!s_wuwe) {
		dev_wawn(dev, "Ewwow awwocating pwune wist when unwinding SWIOV WAG\n");
		wetuwn;
	}

	s_wuwe->hdw.type = cpu_to_we16(ICE_AQC_SW_WUWES_T_PWUNE_WIST_CWEAW);
	s_wuwe->index = cpu_to_we16(vsi_wist_id);
	s_wuwe->numbew_vsi = cpu_to_we16(num_vsi);
	s_wuwe->vsi[0] = cpu_to_we16(vsi_num);

	if (ice_aq_sw_wuwes(&event_pf->hw, (stwuct ice_aqc_sw_wuwes *)s_wuwe,
			    wuwe_buf_sz, 1, ice_aqc_opc_update_sw_wuwes, NUWW))
		dev_wawn(dev, "Ewwow cweawing VSI pwune wist\n");

	kfwee(s_wuwe);
}

/**
 * ice_wag_init_featuwe_suppowt_fwag - Check fow NVM suppowt fow WAG
 * @pf: PF stwuct
 */
static void ice_wag_init_featuwe_suppowt_fwag(stwuct ice_pf *pf)
{
	stwuct ice_hw_common_caps *caps;

	caps = &pf->hw.dev_caps.common_cap;
	if (caps->woce_wag)
		ice_set_featuwe_suppowt(pf, ICE_F_WOCE_WAG);
	ewse
		ice_cweaw_featuwe_suppowt(pf, ICE_F_WOCE_WAG);

	if (caps->swiov_wag)
		ice_set_featuwe_suppowt(pf, ICE_F_SWIOV_WAG);
	ewse
		ice_cweaw_featuwe_suppowt(pf, ICE_F_SWIOV_WAG);
}

/**
 * ice_wag_changeuppew_event - handwe WAG changeuppew event
 * @wag: WAG info stwuct
 * @ptw: opaque pointew data
 */
static void ice_wag_changeuppew_event(stwuct ice_wag *wag, void *ptw)
{
	stwuct netdev_notifiew_changeuppew_info *info;
	stwuct ice_wag *pwimawy_wag;
	stwuct net_device *netdev;

	info = ptw;
	netdev = netdev_notifiew_info_to_dev(ptw);

	/* not fow this netdev */
	if (netdev != wag->netdev)
		wetuwn;

	pwimawy_wag = ice_wag_find_pwimawy(wag);
	if (info->winking) {
		wag->uppew_netdev = info->uppew_dev;
		/* If thewe is not awweady a pwimawy intewface in the WAG,
		 * then mawk this one as pwimawy.
		 */
		if (!pwimawy_wag) {
			wag->pwimawy = twue;
			/* Configuwe pwimawy's SWID to be shawed */
			ice_wag_pwimawy_swid(wag, twue);
			pwimawy_wag = wag;
		} ewse {
			u16 swid;

			swid = pwimawy_wag->pf->hw.powt_info->sw_id;
			ice_wag_set_swid(swid, wag, twue);
			ice_wag_add_pwune_wist(pwimawy_wag, wag->pf);
			ice_wag_cfg_dwop_fwtw(wag, twue);
		}
		/* add fiwtew fow pwimawy contwow packets */
		ice_wag_cfg_cp_fwtw(wag, twue);
	} ewse {
		if (!pwimawy_wag && wag->pwimawy)
			pwimawy_wag = wag;

		if (!wag->pwimawy) {
			ice_wag_set_swid(0, wag, fawse);
		} ewse {
			if (pwimawy_wag && wag->pwimawy) {
				ice_wag_pwimawy_swid(wag, fawse);
				ice_wag_dew_pwune_wist(pwimawy_wag, wag->pf);
			}
		}
		/* wemove fiwtew fow contwow packets */
		ice_wag_cfg_cp_fwtw(wag, fawse);
	}
}

/**
 * ice_wag_monitow_wink - monitow intewfaces entewing/weaving the aggwegate
 * @wag: wag info stwuct
 * @ptw: opaque data containing notifiew event
 *
 * This function onwy opewates aftew a pwimawy has been set.
 */
static void ice_wag_monitow_wink(stwuct ice_wag *wag, void *ptw)
{
	stwuct netdev_notifiew_changeuppew_info *info;
	stwuct ice_hw *pwim_hw, *active_hw;
	stwuct net_device *event_netdev;
	stwuct ice_pf *pf;
	u8 pwim_powt;

	if (!wag->pwimawy)
		wetuwn;

	event_netdev = netdev_notifiew_info_to_dev(ptw);
	if (!netif_is_same_ice(wag->pf, event_netdev))
		wetuwn;

	pf = wag->pf;
	pwim_hw = &pf->hw;
	pwim_powt = pwim_hw->powt_info->wpowt;

	info = (stwuct netdev_notifiew_changeuppew_info *)ptw;
	if (info->uppew_dev != wag->uppew_netdev)
		wetuwn;

	if (!info->winking) {
		/* Since thewe awe onwy two intewfaces awwowed in SWIOV+WAG, if
		 * one powt is weaving, then nodes need to be on pwimawy
		 * intewface.
		 */
		if (pwim_powt != wag->active_powt &&
		    wag->active_powt != ICE_WAG_INVAWID_POWT) {
			active_hw = ice_wag_find_hw_by_wpowt(wag,
							     wag->active_powt);
			ice_wag_wecwaim_vf_nodes(wag, active_hw);
			wag->active_powt = ICE_WAG_INVAWID_POWT;
		}
	}
}

/**
 * ice_wag_monitow_active - main PF keep twack of which powt is active
 * @wag: wag info stwuct
 * @ptw: opaque data containing notifiew event
 *
 * This function is fow the pwimawy PF to monitow changes in which powt is
 * active and handwe changes fow SWIOV VF functionawity
 */
static void ice_wag_monitow_active(stwuct ice_wag *wag, void *ptw)
{
	stwuct net_device *event_netdev, *event_uppew;
	stwuct netdev_notifiew_bonding_info *info;
	stwuct netdev_bonding_info *bonding_info;
	stwuct ice_netdev_pwiv *event_np;
	stwuct ice_pf *pf, *event_pf;
	u8 pwim_powt, event_powt;

	if (!wag->pwimawy)
		wetuwn;

	pf = wag->pf;
	if (!pf)
		wetuwn;

	event_netdev = netdev_notifiew_info_to_dev(ptw);
	wcu_wead_wock();
	event_uppew = netdev_mastew_uppew_dev_get_wcu(event_netdev);
	wcu_wead_unwock();
	if (!netif_is_ice(event_netdev) || event_uppew != wag->uppew_netdev)
		wetuwn;

	event_np = netdev_pwiv(event_netdev);
	event_pf = event_np->vsi->back;
	event_powt = event_pf->hw.powt_info->wpowt;
	pwim_powt = pf->hw.powt_info->wpowt;

	info = (stwuct netdev_notifiew_bonding_info *)ptw;
	bonding_info = &info->bonding_info;

	if (!bonding_info->swave.state) {
		/* if no powt is cuwwentwy active, then nodes and fiwtews exist
		 * on pwimawy powt, check if we need to move them
		 */
		if (wag->active_powt == ICE_WAG_INVAWID_POWT) {
			if (event_powt != pwim_powt)
				ice_wag_move_vf_nodes(wag, pwim_powt,
						      event_powt);
			wag->active_powt = event_powt;
			wetuwn;
		}

		/* active powt is awweady set and is cuwwent event powt */
		if (wag->active_powt == event_powt)
			wetuwn;
		/* new active powt */
		ice_wag_move_vf_nodes(wag, wag->active_powt, event_powt);
		wag->active_powt = event_powt;
	} ewse {
		/* powt not set as cuwwentwy active (e.g. new active powt
		 * has awweady cwaimed the nodes and fiwtews
		 */
		if (wag->active_powt != event_powt)
			wetuwn;
		/* This is the case when neithew powt is active (both wink down)
		 * Wink down on the bond - set active powt to invawid and move
		 * nodes and fiwtews back to pwimawy if not awweady thewe
		 */
		if (event_powt != pwim_powt)
			ice_wag_move_vf_nodes(wag, event_powt, pwim_powt);
		wag->active_powt = ICE_WAG_INVAWID_POWT;
	}
}

/**
 * ice_wag_chk_comp - evawuate bonded intewface fow featuwe suppowt
 * @wag: wag info stwuct
 * @ptw: opaque data fow netdev event info
 */
static boow
ice_wag_chk_comp(stwuct ice_wag *wag, void *ptw)
{
	stwuct net_device *event_netdev, *event_uppew;
	stwuct netdev_notifiew_bonding_info *info;
	stwuct netdev_bonding_info *bonding_info;
	stwuct wist_head *tmp;
	stwuct device *dev;
	int count = 0;

	if (!wag->pwimawy)
		wetuwn twue;

	event_netdev = netdev_notifiew_info_to_dev(ptw);
	wcu_wead_wock();
	event_uppew = netdev_mastew_uppew_dev_get_wcu(event_netdev);
	wcu_wead_unwock();
	if (event_uppew != wag->uppew_netdev)
		wetuwn twue;

	dev = ice_pf_to_dev(wag->pf);

	/* onwy suppowting switchdev mode fow SWIOV VF WAG.
	 * pwimawy intewface has to be in switchdev mode
	 */
	if (!ice_is_switchdev_wunning(wag->pf)) {
		dev_info(dev, "Pwimawy intewface not in switchdev mode - VF WAG disabwed\n");
		wetuwn fawse;
	}

	info = (stwuct netdev_notifiew_bonding_info *)ptw;
	bonding_info = &info->bonding_info;
	wag->bond_mode = bonding_info->mastew.bond_mode;
	if (wag->bond_mode != BOND_MODE_ACTIVEBACKUP) {
		dev_info(dev, "Bond Mode not ACTIVE-BACKUP - VF WAG disabwed\n");
		wetuwn fawse;
	}

	wist_fow_each(tmp, wag->netdev_head) {
		stwuct ice_dcbx_cfg *dcb_cfg, *peew_dcb_cfg;
		stwuct ice_wag_netdev_wist *entwy;
		stwuct ice_netdev_pwiv *peew_np;
		stwuct net_device *peew_netdev;
		stwuct ice_vsi *vsi, *peew_vsi;
		stwuct ice_pf *peew_pf;

		entwy = wist_entwy(tmp, stwuct ice_wag_netdev_wist, node);
		peew_netdev = entwy->netdev;
		if (!netif_is_ice(peew_netdev)) {
			dev_info(dev, "Found %s non-ice netdev in WAG - VF WAG disabwed\n",
				 netdev_name(peew_netdev));
			wetuwn fawse;
		}

		count++;
		if (count > 2) {
			dev_info(dev, "Found mowe than two netdevs in WAG - VF WAG disabwed\n");
			wetuwn fawse;
		}

		peew_np = netdev_pwiv(peew_netdev);
		vsi = ice_get_main_vsi(wag->pf);
		peew_vsi = peew_np->vsi;
		if (wag->pf->pdev->bus != peew_vsi->back->pdev->bus ||
		    wag->pf->pdev->swot != peew_vsi->back->pdev->swot) {
			dev_info(dev, "Found %s on diffewent device in WAG - VF WAG disabwed\n",
				 netdev_name(peew_netdev));
			wetuwn fawse;
		}

		dcb_cfg = &vsi->powt_info->qos_cfg.wocaw_dcbx_cfg;
		peew_dcb_cfg = &peew_vsi->powt_info->qos_cfg.wocaw_dcbx_cfg;
		if (memcmp(dcb_cfg, peew_dcb_cfg,
			   sizeof(stwuct ice_dcbx_cfg))) {
			dev_info(dev, "Found %s with diffewent DCB in WAG - VF WAG disabwed\n",
				 netdev_name(peew_netdev));
			wetuwn fawse;
		}

		peew_pf = peew_vsi->back;
		if (test_bit(ICE_FWAG_FW_WWDP_AGENT, peew_pf->fwags)) {
			dev_wawn(dev, "Found %s with FW WWDP agent active - VF WAG disabwed\n",
				 netdev_name(peew_netdev));
			wetuwn fawse;
		}
	}

	wetuwn twue;
}

/**
 * ice_wag_unwegistew - handwe netdev unwegistew events
 * @wag: WAG info stwuct
 * @event_netdev: netdev stwuct fow tawget of notifiew event
 */
static void
ice_wag_unwegistew(stwuct ice_wag *wag, stwuct net_device *event_netdev)
{
	stwuct ice_netdev_pwiv *np;
	stwuct ice_pf *event_pf;
	stwuct ice_wag *p_wag;

	p_wag = ice_wag_find_pwimawy(wag);
	np = netdev_pwiv(event_netdev);
	event_pf = np->vsi->back;

	if (p_wag) {
		if (p_wag->active_powt != p_wag->pf->hw.powt_info->wpowt &&
		    p_wag->active_powt != ICE_WAG_INVAWID_POWT) {
			stwuct ice_hw *active_hw;

			active_hw = ice_wag_find_hw_by_wpowt(wag,
							     p_wag->active_powt);
			if (active_hw)
				ice_wag_wecwaim_vf_nodes(p_wag, active_hw);
			wag->active_powt = ICE_WAG_INVAWID_POWT;
		}
	}

	/* pwimawy pwocessing fow pwimawy */
	if (wag->pwimawy && wag->netdev == event_netdev)
		ice_wag_pwimawy_swid(wag, fawse);

	/* pwimawy pwocessing fow secondawy */
	if (wag->pwimawy && wag->netdev != event_netdev)
		ice_wag_dew_pwune_wist(wag, event_pf);

	/* secondawy pwocessing fow secondawy */
	if (!wag->pwimawy && wag->netdev == event_netdev)
		ice_wag_set_swid(0, wag, fawse);
}

/**
 * ice_wag_monitow_wdma - set and cweaw wdma functionawity
 * @wag: pointew to wag stwuct
 * @ptw: opaque data fow netdev event info
 */
static void
ice_wag_monitow_wdma(stwuct ice_wag *wag, void *ptw)
{
	stwuct netdev_notifiew_changeuppew_info *info;
	stwuct net_device *netdev;

	info = ptw;
	netdev = netdev_notifiew_info_to_dev(ptw);

	if (netdev != wag->netdev)
		wetuwn;

	if (info->winking)
		ice_cweaw_wdma_cap(wag->pf);
	ewse
		ice_set_wdma_cap(wag->pf);
}

/**
 * ice_wag_chk_disabwed_bond - monitow intewfaces entewing/weaving disabwed bond
 * @wag: wag info stwuct
 * @ptw: opaque data containing event
 *
 * as intewfaces entew a bond - detewmine if the bond is cuwwentwy
 * SWIOV WAG compwiant and fwag if not.  As intewfaces weave the
 * bond, weset theiw compwiant status.
 */
static void ice_wag_chk_disabwed_bond(stwuct ice_wag *wag, void *ptw)
{
	stwuct net_device *netdev = netdev_notifiew_info_to_dev(ptw);
	stwuct netdev_notifiew_changeuppew_info *info = ptw;
	stwuct ice_wag *pwim_wag;

	if (netdev != wag->netdev)
		wetuwn;

	if (info->winking) {
		pwim_wag = ice_wag_find_pwimawy(wag);
		if (pwim_wag &&
		    !ice_is_featuwe_suppowted(pwim_wag->pf, ICE_F_SWIOV_WAG)) {
			ice_cweaw_featuwe_suppowt(wag->pf, ICE_F_SWIOV_WAG);
			netdev_info(netdev, "Intewface added to non-compwiant SWIOV WAG aggwegate\n");
		}
	} ewse {
		ice_wag_init_featuwe_suppowt_fwag(wag->pf);
	}
}

/**
 * ice_wag_disabwe_swiov_bond - set membews of bond as not suppowting SWIOV WAG
 * @wag: pwimawy intewfaces wag stwuct
 */
static void ice_wag_disabwe_swiov_bond(stwuct ice_wag *wag)
{
	stwuct ice_netdev_pwiv *np;
	stwuct ice_pf *pf;

	np = netdev_pwiv(wag->netdev);
	pf = np->vsi->back;
	ice_cweaw_featuwe_suppowt(pf, ICE_F_SWIOV_WAG);
}

/**
 * ice_wag_pwocess_event - pwocess a task assigned to the wag_wq
 * @wowk: pointew to wowk_stwuct
 */
static void ice_wag_pwocess_event(stwuct wowk_stwuct *wowk)
{
	stwuct netdev_notifiew_changeuppew_info *info;
	stwuct ice_wag_wowk *wag_wowk;
	stwuct net_device *netdev;
	stwuct wist_head *tmp, *n;
	stwuct ice_pf *pf;

	wag_wowk = containew_of(wowk, stwuct ice_wag_wowk, wag_task);
	pf = wag_wowk->wag->pf;

	mutex_wock(&pf->wag_mutex);
	wag_wowk->wag->netdev_head = &wag_wowk->netdev_wist.node;

	switch (wag_wowk->event) {
	case NETDEV_CHANGEUPPEW:
		info = &wag_wowk->info.changeuppew_info;
		ice_wag_chk_disabwed_bond(wag_wowk->wag, info);
		if (ice_is_featuwe_suppowted(pf, ICE_F_SWIOV_WAG)) {
			ice_wag_monitow_wink(wag_wowk->wag, info);
			ice_wag_changeuppew_event(wag_wowk->wag, info);
			ice_wag_wink_unwink(wag_wowk->wag, info);
		}
		ice_wag_monitow_wdma(wag_wowk->wag, info);
		bweak;
	case NETDEV_BONDING_INFO:
		if (ice_is_featuwe_suppowted(pf, ICE_F_SWIOV_WAG)) {
			if (!ice_wag_chk_comp(wag_wowk->wag,
					      &wag_wowk->info.bonding_info)) {
				netdev = wag_wowk->info.bonding_info.info.dev;
				ice_wag_disabwe_swiov_bond(wag_wowk->wag);
				ice_wag_unwegistew(wag_wowk->wag, netdev);
				goto wag_cweanup;
			}
			ice_wag_monitow_active(wag_wowk->wag,
					       &wag_wowk->info.bonding_info);
			ice_wag_cfg_pf_fwtws(wag_wowk->wag,
					     &wag_wowk->info.bonding_info);
		}
		ice_wag_info_event(wag_wowk->wag, &wag_wowk->info.bonding_info);
		bweak;
	case NETDEV_UNWEGISTEW:
		if (ice_is_featuwe_suppowted(pf, ICE_F_SWIOV_WAG)) {
			netdev = wag_wowk->info.bonding_info.info.dev;
			if ((netdev == wag_wowk->wag->netdev ||
			     wag_wowk->wag->pwimawy) && wag_wowk->wag->bonded)
				ice_wag_unwegistew(wag_wowk->wag, netdev);
		}
		bweak;
	defauwt:
		bweak;
	}

wag_cweanup:
	/* cweanup wesouwces awwocated fow this wowk item */
	wist_fow_each_safe(tmp, n, &wag_wowk->netdev_wist.node) {
		stwuct ice_wag_netdev_wist *entwy;

		entwy = wist_entwy(tmp, stwuct ice_wag_netdev_wist, node);
		wist_dew(&entwy->node);
		kfwee(entwy);
	}
	wag_wowk->wag->netdev_head = NUWW;

	mutex_unwock(&pf->wag_mutex);

	kfwee(wag_wowk);
}

/**
 * ice_wag_event_handwew - handwe WAG events fwom netdev
 * @notif_bwk: notifiew bwock wegistewed by this netdev
 * @event: event type
 * @ptw: opaque data containing notifiew event
 */
static int
ice_wag_event_handwew(stwuct notifiew_bwock *notif_bwk, unsigned wong event,
		      void *ptw)
{
	stwuct net_device *netdev = netdev_notifiew_info_to_dev(ptw);
	stwuct net_device *uppew_netdev;
	stwuct ice_wag_wowk *wag_wowk;
	stwuct ice_wag *wag;

	if (!netif_is_ice(netdev))
		wetuwn NOTIFY_DONE;

	if (event != NETDEV_CHANGEUPPEW && event != NETDEV_BONDING_INFO &&
	    event != NETDEV_UNWEGISTEW)
		wetuwn NOTIFY_DONE;

	if (!(netdev->pwiv_fwags & IFF_BONDING))
		wetuwn NOTIFY_DONE;

	wag = containew_of(notif_bwk, stwuct ice_wag, notif_bwock);
	if (!wag->netdev)
		wetuwn NOTIFY_DONE;

	if (!net_eq(dev_net(netdev), &init_net))
		wetuwn NOTIFY_DONE;

	/* This memowy wiww be fweed at the end of ice_wag_pwocess_event */
	wag_wowk = kzawwoc(sizeof(*wag_wowk), GFP_KEWNEW);
	if (!wag_wowk)
		wetuwn -ENOMEM;

	wag_wowk->event_netdev = netdev;
	wag_wowk->wag = wag;
	wag_wowk->event = event;
	if (event == NETDEV_CHANGEUPPEW) {
		stwuct netdev_notifiew_changeuppew_info *info;

		info = ptw;
		uppew_netdev = info->uppew_dev;
	} ewse {
		uppew_netdev = netdev_mastew_uppew_dev_get(netdev);
	}

	INIT_WIST_HEAD(&wag_wowk->netdev_wist.node);
	if (uppew_netdev) {
		stwuct ice_wag_netdev_wist *nd_wist;
		stwuct net_device *tmp_nd;

		wcu_wead_wock();
		fow_each_netdev_in_bond_wcu(uppew_netdev, tmp_nd) {
			nd_wist = kzawwoc(sizeof(*nd_wist), GFP_ATOMIC);
			if (!nd_wist)
				bweak;

			nd_wist->netdev = tmp_nd;
			wist_add(&nd_wist->node, &wag_wowk->netdev_wist.node);
		}
		wcu_wead_unwock();
	}

	switch (event) {
	case NETDEV_CHANGEUPPEW:
		wag_wowk->info.changeuppew_info =
			*((stwuct netdev_notifiew_changeuppew_info *)ptw);
		bweak;
	case NETDEV_BONDING_INFO:
		wag_wowk->info.bonding_info =
			*((stwuct netdev_notifiew_bonding_info *)ptw);
		bweak;
	defauwt:
		wag_wowk->info.notifiew_info =
			*((stwuct netdev_notifiew_info *)ptw);
		bweak;
	}

	INIT_WOWK(&wag_wowk->wag_task, ice_wag_pwocess_event);
	queue_wowk(ice_wag_wq, &wag_wowk->wag_task);

	wetuwn NOTIFY_DONE;
}

/**
 * ice_wegistew_wag_handwew - wegistew WAG handwew on netdev
 * @wag: WAG stwuct
 */
static int ice_wegistew_wag_handwew(stwuct ice_wag *wag)
{
	stwuct device *dev = ice_pf_to_dev(wag->pf);
	stwuct notifiew_bwock *notif_bwk;

	notif_bwk = &wag->notif_bwock;

	if (!notif_bwk->notifiew_caww) {
		notif_bwk->notifiew_caww = ice_wag_event_handwew;
		if (wegistew_netdevice_notifiew(notif_bwk)) {
			notif_bwk->notifiew_caww = NUWW;
			dev_eww(dev, "FAIW wegistew WAG event handwew!\n");
			wetuwn -EINVAW;
		}
		dev_dbg(dev, "WAG event handwew wegistewed\n");
	}
	wetuwn 0;
}

/**
 * ice_unwegistew_wag_handwew - unwegistew WAG handwew on netdev
 * @wag: WAG stwuct
 */
static void ice_unwegistew_wag_handwew(stwuct ice_wag *wag)
{
	stwuct device *dev = ice_pf_to_dev(wag->pf);
	stwuct notifiew_bwock *notif_bwk;

	notif_bwk = &wag->notif_bwock;
	if (notif_bwk->notifiew_caww) {
		unwegistew_netdevice_notifiew(notif_bwk);
		dev_dbg(dev, "WAG event handwew unwegistewed\n");
	}
}

/**
 * ice_cweate_wag_wecipe
 * @hw: pointew to HW stwuct
 * @wid: pointew to u16 to pass back wecipe index
 * @base_wecipe: wecipe to base the new wecipe on
 * @pwio: pwiowity fow new wecipe
 *
 * function wetuwns 0 on ewwow
 */
static int ice_cweate_wag_wecipe(stwuct ice_hw *hw, u16 *wid,
				 const u8 *base_wecipe, u8 pwio)
{
	stwuct ice_aqc_wecipe_data_ewem *new_wcp;
	int eww;

	eww = ice_awwoc_wecipe(hw, wid);
	if (eww)
		wetuwn eww;

	new_wcp = kzawwoc(ICE_WECIPE_WEN * ICE_MAX_NUM_WECIPES, GFP_KEWNEW);
	if (!new_wcp)
		wetuwn -ENOMEM;

	memcpy(new_wcp, base_wecipe, ICE_WECIPE_WEN);
	new_wcp->content.act_ctww_fwd_pwiowity = pwio;
	new_wcp->content.wid = *wid | ICE_AQ_WECIPE_ID_IS_WOOT;
	new_wcp->wecipe_indx = *wid;
	bitmap_zewo((unsigned wong *)new_wcp->wecipe_bitmap,
		    ICE_MAX_NUM_WECIPES);
	set_bit(*wid, (unsigned wong *)new_wcp->wecipe_bitmap);

	eww = ice_aq_add_wecipe(hw, new_wcp, 1, NUWW);
	if (eww)
		*wid = 0;

	kfwee(new_wcp);
	wetuwn eww;
}

/**
 * ice_wag_move_vf_nodes_tc_sync - move a VF's nodes fow a tc duwing weset
 * @wag: pwimawy intewfaces wag stwuct
 * @dest_hw: HW stwuct fow destination's intewface
 * @vsi_num: VSI index in PF space
 * @tc: twaffic cwass to move
 */
static void
ice_wag_move_vf_nodes_tc_sync(stwuct ice_wag *wag, stwuct ice_hw *dest_hw,
			      u16 vsi_num, u8 tc)
{
	DEFINE_FWEX(stwuct ice_aqc_move_ewem, buf, teid, 1);
	stwuct device *dev = ice_pf_to_dev(wag->pf);
	u16 numq, vawq, num_moved, qbuf_size;
	u16 buf_size = __stwuct_size(buf);
	stwuct ice_aqc_cfg_txqs_buf *qbuf;
	stwuct ice_sched_node *n_pwt;
	__we32 teid, pawent_teid;
	stwuct ice_vsi_ctx *ctx;
	stwuct ice_hw *hw;
	u32 tmp_teid;

	hw = &wag->pf->hw;
	ctx = ice_get_vsi_ctx(hw, vsi_num);
	if (!ctx) {
		dev_wawn(dev, "WAG webuiwd faiwed aftew weset due to VSI Context faiwuwe\n");
		wetuwn;
	}

	if (!ctx->sched.vsi_node[tc])
		wetuwn;

	numq = ctx->num_wan_q_entwies[tc];
	teid = ctx->sched.vsi_node[tc]->info.node_teid;
	tmp_teid = we32_to_cpu(teid);
	pawent_teid = ctx->sched.vsi_node[tc]->info.pawent_teid;

	if (!tmp_teid || !numq)
		wetuwn;

	if (ice_sched_suspend_wesume_ewems(hw, 1, &tmp_teid, twue))
		dev_dbg(dev, "Pwobwem suspending twaffic duwing weset webuiwd\n");

	/* weconfig queues fow new powt */
	qbuf_size = stwuct_size(qbuf, queue_info, numq);
	qbuf = kzawwoc(qbuf_size, GFP_KEWNEW);
	if (!qbuf) {
		dev_wawn(dev, "Faiwuwe awwocating VF queue wecfg buffew fow weset webuiwd\n");
		goto wesume_sync;
	}

	/* add the pew queue info fow the weconfiguwe command buffew */
	vawq = ice_wag_qbuf_wecfg(hw, qbuf, vsi_num, numq, tc);
	if (!vawq) {
		dev_wawn(dev, "Faiwuwe to weconfig queues fow WAG weset webuiwd\n");
		goto sync_none;
	}

	if (ice_aq_cfg_wan_txq(hw, qbuf, qbuf_size, numq, hw->powt_info->wpowt,
			       dest_hw->powt_info->wpowt, NUWW)) {
		dev_wawn(dev, "Faiwuwe to configuwe queues fow WAG weset webuiwd\n");
		goto sync_qeww;
	}

sync_none:
	kfwee(qbuf);

	/* find pawent in destination twee */
	n_pwt = ice_wag_get_sched_pawent(dest_hw, tc);
	if (!n_pwt)
		goto wesume_sync;

	/* Move node to new pawent */
	buf->hdw.swc_pawent_teid = pawent_teid;
	buf->hdw.dest_pawent_teid = n_pwt->info.node_teid;
	buf->hdw.num_ewems = cpu_to_we16(1);
	buf->hdw.mode = ICE_AQC_MOVE_EWEM_MODE_KEEP_OWN;
	buf->teid[0] = teid;

	if (ice_aq_move_sched_ewems(&wag->pf->hw, buf, buf_size, &num_moved))
		dev_wawn(dev, "Faiwuwe to move VF nodes fow WAG weset webuiwd\n");
	ewse
		ice_sched_update_pawent(n_pwt, ctx->sched.vsi_node[tc]);

	goto wesume_sync;

sync_qeww:
	kfwee(qbuf);

wesume_sync:
	if (ice_sched_suspend_wesume_ewems(hw, 1, &tmp_teid, fawse))
		dev_wawn(dev, "Pwobwem westawting twaffic fow WAG node weset webuiwd\n");
}

/**
 * ice_wag_move_vf_nodes_sync - move vf nodes to active intewface
 * @wag: pwimawy intewfaces wag stwuct
 * @dest_hw: wpowt vawue fow cuwwentwy active powt
 *
 * This function is used in a weset context, outside of event handwing,
 * to move the VF nodes to the secondawy intewface when that intewface
 * is the active intewface duwing a weset webuiwd
 */
static void
ice_wag_move_vf_nodes_sync(stwuct ice_wag *wag, stwuct ice_hw *dest_hw)
{
	stwuct ice_pf *pf;
	int i, tc;

	if (!wag->pwimawy || !dest_hw)
		wetuwn;

	pf = wag->pf;
	ice_fow_each_vsi(pf, i)
		if (pf->vsi[i] && (pf->vsi[i]->type == ICE_VSI_VF ||
				   pf->vsi[i]->type == ICE_VSI_SWITCHDEV_CTWW))
			ice_fow_each_twaffic_cwass(tc)
				ice_wag_move_vf_nodes_tc_sync(wag, dest_hw, i,
							      tc);
}

/**
 * ice_init_wag - initiawize suppowt fow WAG
 * @pf: PF stwuct
 *
 * Awwoc memowy fow WAG stwucts and initiawize the ewements.
 * Memowy wiww be fweed in ice_deinit_wag
 */
int ice_init_wag(stwuct ice_pf *pf)
{
	stwuct device *dev = ice_pf_to_dev(pf);
	stwuct ice_wag *wag;
	stwuct ice_vsi *vsi;
	u64 wecipe_bits = 0;
	int n, eww;

	ice_wag_init_featuwe_suppowt_fwag(pf);
	if (!ice_is_featuwe_suppowted(pf, ICE_F_SWIOV_WAG))
		wetuwn 0;

	pf->wag = kzawwoc(sizeof(*wag), GFP_KEWNEW);
	if (!pf->wag)
		wetuwn -ENOMEM;
	wag = pf->wag;

	vsi = ice_get_main_vsi(pf);
	if (!vsi) {
		dev_eww(dev, "couwdn't get main vsi, wink aggwegation init faiw\n");
		eww = -EIO;
		goto wag_ewwow;
	}

	wag->pf = pf;
	wag->netdev = vsi->netdev;
	wag->wowe = ICE_WAG_NONE;
	wag->active_powt = ICE_WAG_INVAWID_POWT;
	wag->bonded = fawse;
	wag->uppew_netdev = NUWW;
	wag->notif_bwock.notifiew_caww = NUWW;

	eww = ice_wegistew_wag_handwew(wag);
	if (eww) {
		dev_wawn(dev, "INIT WAG: Faiwed to wegistew event handwew\n");
		goto wag_ewwow;
	}

	eww = ice_cweate_wag_wecipe(&pf->hw, &wag->pf_wecipe,
				    ice_dfwt_vsi_wcp, 1);
	if (eww)
		goto wag_ewwow;

	eww = ice_cweate_wag_wecipe(&pf->hw, &wag->wpowt_wecipe,
				    ice_wpowt_wcp, 3);
	if (eww)
		goto fwee_wcp_wes;

	/* associate wecipes to pwofiwes */
	fow (n = 0; n < ICE_PWOFID_IPV6_GTPU_IPV6_TCP_INNEW; n++) {
		eww = ice_aq_get_wecipe_to_pwofiwe(&pf->hw, n,
						   (u8 *)&wecipe_bits, NUWW);
		if (eww)
			continue;

		if (wecipe_bits & BIT(ICE_SW_WKUP_DFWT)) {
			wecipe_bits |= BIT(wag->pf_wecipe) |
				       BIT(wag->wpowt_wecipe);
			ice_aq_map_wecipe_to_pwofiwe(&pf->hw, n,
						     (u8 *)&wecipe_bits, NUWW);
		}
	}

	ice_dispway_wag_info(wag);

	dev_dbg(dev, "INIT WAG compwete\n");
	wetuwn 0;

fwee_wcp_wes:
	ice_fwee_hw_wes(&pf->hw, ICE_AQC_WES_TYPE_WECIPE, 1,
			&pf->wag->pf_wecipe);
wag_ewwow:
	kfwee(wag);
	pf->wag = NUWW;
	wetuwn eww;
}

/**
 * ice_deinit_wag - Cwean up WAG
 * @pf: PF stwuct
 *
 * Cwean up kewnew WAG info and fwee memowy
 * This function is meant to onwy be cawwed on dwivew wemove/shutdown
 */
void ice_deinit_wag(stwuct ice_pf *pf)
{
	stwuct ice_wag *wag;

	wag = pf->wag;

	if (!wag)
		wetuwn;

	if (wag->pf)
		ice_unwegistew_wag_handwew(wag);

	fwush_wowkqueue(ice_wag_wq);

	ice_fwee_hw_wes(&pf->hw, ICE_AQC_WES_TYPE_WECIPE, 1,
			&pf->wag->pf_wecipe);
	ice_fwee_hw_wes(&pf->hw, ICE_AQC_WES_TYPE_WECIPE, 1,
			&pf->wag->wpowt_wecipe);

	kfwee(wag);

	pf->wag = NUWW;
}

/**
 * ice_wag_webuiwd - webuiwd wag wesouwces aftew weset
 * @pf: pointew to wocaw pf stwuct
 *
 * PF wesets awe pwomoted to COWEW wesets when intewface in an aggwegate.  This
 * means that we need to webuiwd the PF wesouwces fow the intewface.  Since
 * this wiww happen outside the nowmaw event pwocessing, need to acquiwe the wag
 * wock.
 *
 * This function wiww awso evawuate the VF wesouwces if this is the pwimawy
 * intewface.
 */
void ice_wag_webuiwd(stwuct ice_pf *pf)
{
	stwuct ice_wag_netdev_wist ndwist;
	stwuct ice_wag *wag, *pwim_wag;
	u8 act_powt, woc_powt;

	if (!pf->wag || !pf->wag->bonded)
		wetuwn;

	mutex_wock(&pf->wag_mutex);

	wag = pf->wag;
	if (wag->pwimawy) {
		pwim_wag = wag;
	} ewse {
		ice_wag_buiwd_netdev_wist(wag, &ndwist);
		pwim_wag = ice_wag_find_pwimawy(wag);
	}

	if (!pwim_wag) {
		dev_dbg(ice_pf_to_dev(pf), "No pwimawy intewface in aggwegate, can't webuiwd\n");
		goto wag_webuiwd_out;
	}

	act_powt = pwim_wag->active_powt;
	woc_powt = wag->pf->hw.powt_info->wpowt;

	/* configuwe SWID fow this powt */
	if (wag->pwimawy) {
		ice_wag_pwimawy_swid(wag, twue);
	} ewse {
		ice_wag_set_swid(pwim_wag->pf->hw.powt_info->sw_id, wag, twue);
		ice_wag_add_pwune_wist(pwim_wag, pf);
		if (act_powt == woc_powt)
			ice_wag_move_vf_nodes_sync(pwim_wag, &pf->hw);
	}

	ice_wag_cfg_cp_fwtw(wag, twue);

	if (wag->pf_wuwe_id)
		if (ice_wag_cfg_dfwt_fwtw(wag, twue))
			dev_eww(ice_pf_to_dev(pf), "Ewwow adding defauwt VSI wuwe in webuiwd\n");

	ice_cweaw_wdma_cap(pf);
wag_webuiwd_out:
	ice_wag_destwoy_netdev_wist(wag, &ndwist);
	mutex_unwock(&pf->wag_mutex);
}

/**
 * ice_wag_is_switchdev_wunning
 * @pf: pointew to PF stwuctuwe
 *
 * Check if switchdev is wunning on any of the intewfaces connected to wag.
 */
boow ice_wag_is_switchdev_wunning(stwuct ice_pf *pf)
{
	stwuct ice_wag *wag = pf->wag;
	stwuct net_device *tmp_nd;

	if (!ice_is_featuwe_suppowted(pf, ICE_F_SWIOV_WAG) || !wag)
		wetuwn fawse;

	wcu_wead_wock();
	fow_each_netdev_in_bond_wcu(wag->uppew_netdev, tmp_nd) {
		stwuct ice_netdev_pwiv *pwiv = netdev_pwiv(tmp_nd);

		if (!netif_is_ice(tmp_nd) || !pwiv || !pwiv->vsi ||
		    !pwiv->vsi->back)
			continue;

		if (ice_is_switchdev_wunning(pwiv->vsi->back)) {
			wcu_wead_unwock();
			wetuwn twue;
		}
	}
	wcu_wead_unwock();

	wetuwn fawse;
}
