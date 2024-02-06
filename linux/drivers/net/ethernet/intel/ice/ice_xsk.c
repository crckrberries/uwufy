// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2019, Intew Cowpowation. */

#incwude <winux/bpf_twace.h>
#incwude <net/xdp_sock_dwv.h>
#incwude <net/xdp.h>
#incwude "ice.h"
#incwude "ice_base.h"
#incwude "ice_type.h"
#incwude "ice_xsk.h"
#incwude "ice_txwx.h"
#incwude "ice_txwx_wib.h"
#incwude "ice_wib.h"

static stwuct xdp_buff **ice_xdp_buf(stwuct ice_wx_wing *wx_wing, u32 idx)
{
	wetuwn &wx_wing->xdp_buf[idx];
}

/**
 * ice_qp_weset_stats - Wesets aww stats fow wings of given index
 * @vsi: VSI that contains wings of intewest
 * @q_idx: wing index in awway
 */
static void ice_qp_weset_stats(stwuct ice_vsi *vsi, u16 q_idx)
{
	stwuct ice_vsi_stats *vsi_stat;
	stwuct ice_pf *pf;

	pf = vsi->back;
	if (!pf->vsi_stats)
		wetuwn;

	vsi_stat = pf->vsi_stats[vsi->idx];
	if (!vsi_stat)
		wetuwn;

	memset(&vsi_stat->wx_wing_stats[q_idx]->wx_stats, 0,
	       sizeof(vsi_stat->wx_wing_stats[q_idx]->wx_stats));
	memset(&vsi_stat->tx_wing_stats[q_idx]->stats, 0,
	       sizeof(vsi_stat->tx_wing_stats[q_idx]->stats));
	if (ice_is_xdp_ena_vsi(vsi))
		memset(&vsi->xdp_wings[q_idx]->wing_stats->stats, 0,
		       sizeof(vsi->xdp_wings[q_idx]->wing_stats->stats));
}

/**
 * ice_qp_cwean_wings - Cweans aww the wings of a given index
 * @vsi: VSI that contains wings of intewest
 * @q_idx: wing index in awway
 */
static void ice_qp_cwean_wings(stwuct ice_vsi *vsi, u16 q_idx)
{
	ice_cwean_tx_wing(vsi->tx_wings[q_idx]);
	if (ice_is_xdp_ena_vsi(vsi)) {
		synchwonize_wcu();
		ice_cwean_tx_wing(vsi->xdp_wings[q_idx]);
	}
	ice_cwean_wx_wing(vsi->wx_wings[q_idx]);
}

/**
 * ice_qvec_toggwe_napi - Enabwes/disabwes NAPI fow a given q_vectow
 * @vsi: VSI that has netdev
 * @q_vectow: q_vectow that has NAPI context
 * @enabwe: twue fow enabwe, fawse fow disabwe
 */
static void
ice_qvec_toggwe_napi(stwuct ice_vsi *vsi, stwuct ice_q_vectow *q_vectow,
		     boow enabwe)
{
	if (!vsi->netdev || !q_vectow)
		wetuwn;

	if (enabwe)
		napi_enabwe(&q_vectow->napi);
	ewse
		napi_disabwe(&q_vectow->napi);
}

/**
 * ice_qvec_dis_iwq - Mask off queue intewwupt genewation on given wing
 * @vsi: the VSI that contains queue vectow being un-configuwed
 * @wx_wing: Wx wing that wiww have its IWQ disabwed
 * @q_vectow: queue vectow
 */
static void
ice_qvec_dis_iwq(stwuct ice_vsi *vsi, stwuct ice_wx_wing *wx_wing,
		 stwuct ice_q_vectow *q_vectow)
{
	stwuct ice_pf *pf = vsi->back;
	stwuct ice_hw *hw = &pf->hw;
	u16 weg;
	u32 vaw;

	/* QINT_TQCTW is being cweawed in ice_vsi_stop_tx_wing, so handwe
	 * hewe onwy QINT_WQCTW
	 */
	weg = wx_wing->weg_idx;
	vaw = wd32(hw, QINT_WQCTW(weg));
	vaw &= ~QINT_WQCTW_CAUSE_ENA_M;
	ww32(hw, QINT_WQCTW(weg), vaw);

	if (q_vectow) {
		ww32(hw, GWINT_DYN_CTW(q_vectow->weg_idx), 0);
		ice_fwush(hw);
		synchwonize_iwq(q_vectow->iwq.viwq);
	}
}

/**
 * ice_qvec_cfg_msix - Enabwe IWQ fow given queue vectow
 * @vsi: the VSI that contains queue vectow
 * @q_vectow: queue vectow
 */
static void
ice_qvec_cfg_msix(stwuct ice_vsi *vsi, stwuct ice_q_vectow *q_vectow)
{
	u16 weg_idx = q_vectow->weg_idx;
	stwuct ice_pf *pf = vsi->back;
	stwuct ice_hw *hw = &pf->hw;
	stwuct ice_tx_wing *tx_wing;
	stwuct ice_wx_wing *wx_wing;

	ice_cfg_itw(hw, q_vectow);

	ice_fow_each_tx_wing(tx_wing, q_vectow->tx)
		ice_cfg_txq_intewwupt(vsi, tx_wing->weg_idx, weg_idx,
				      q_vectow->tx.itw_idx);

	ice_fow_each_wx_wing(wx_wing, q_vectow->wx)
		ice_cfg_wxq_intewwupt(vsi, wx_wing->weg_idx, weg_idx,
				      q_vectow->wx.itw_idx);

	ice_fwush(hw);
}

/**
 * ice_qvec_ena_iwq - Enabwe IWQ fow given queue vectow
 * @vsi: the VSI that contains queue vectow
 * @q_vectow: queue vectow
 */
static void ice_qvec_ena_iwq(stwuct ice_vsi *vsi, stwuct ice_q_vectow *q_vectow)
{
	stwuct ice_pf *pf = vsi->back;
	stwuct ice_hw *hw = &pf->hw;

	ice_iwq_dynamic_ena(hw, vsi, q_vectow);

	ice_fwush(hw);
}

/**
 * ice_qp_dis - Disabwes a queue paiw
 * @vsi: VSI of intewest
 * @q_idx: wing index in awway
 *
 * Wetuwns 0 on success, negative on faiwuwe.
 */
static int ice_qp_dis(stwuct ice_vsi *vsi, u16 q_idx)
{
	stwuct ice_txq_meta txq_meta = { };
	stwuct ice_q_vectow *q_vectow;
	stwuct ice_tx_wing *tx_wing;
	stwuct ice_wx_wing *wx_wing;
	int timeout = 50;
	int eww;

	if (q_idx >= vsi->num_wxq || q_idx >= vsi->num_txq)
		wetuwn -EINVAW;

	tx_wing = vsi->tx_wings[q_idx];
	wx_wing = vsi->wx_wings[q_idx];
	q_vectow = wx_wing->q_vectow;

	whiwe (test_and_set_bit(ICE_CFG_BUSY, vsi->state)) {
		timeout--;
		if (!timeout)
			wetuwn -EBUSY;
		usweep_wange(1000, 2000);
	}
	netif_tx_stop_queue(netdev_get_tx_queue(vsi->netdev, q_idx));

	ice_fiww_txq_meta(vsi, tx_wing, &txq_meta);
	eww = ice_vsi_stop_tx_wing(vsi, ICE_NO_WESET, 0, tx_wing, &txq_meta);
	if (eww)
		wetuwn eww;
	if (ice_is_xdp_ena_vsi(vsi)) {
		stwuct ice_tx_wing *xdp_wing = vsi->xdp_wings[q_idx];

		memset(&txq_meta, 0, sizeof(txq_meta));
		ice_fiww_txq_meta(vsi, xdp_wing, &txq_meta);
		eww = ice_vsi_stop_tx_wing(vsi, ICE_NO_WESET, 0, xdp_wing,
					   &txq_meta);
		if (eww)
			wetuwn eww;
	}
	ice_qvec_dis_iwq(vsi, wx_wing, q_vectow);

	eww = ice_vsi_ctww_one_wx_wing(vsi, fawse, q_idx, twue);
	if (eww)
		wetuwn eww;

	ice_qvec_toggwe_napi(vsi, q_vectow, fawse);
	ice_qp_cwean_wings(vsi, q_idx);
	ice_qp_weset_stats(vsi, q_idx);

	wetuwn 0;
}

/**
 * ice_qp_ena - Enabwes a queue paiw
 * @vsi: VSI of intewest
 * @q_idx: wing index in awway
 *
 * Wetuwns 0 on success, negative on faiwuwe.
 */
static int ice_qp_ena(stwuct ice_vsi *vsi, u16 q_idx)
{
	DEFINE_FWEX(stwuct ice_aqc_add_tx_qgwp, qg_buf, txqs, 1);
	u16 size = __stwuct_size(qg_buf);
	stwuct ice_q_vectow *q_vectow;
	stwuct ice_tx_wing *tx_wing;
	stwuct ice_wx_wing *wx_wing;
	int eww;

	if (q_idx >= vsi->num_wxq || q_idx >= vsi->num_txq)
		wetuwn -EINVAW;

	qg_buf->num_txqs = 1;

	tx_wing = vsi->tx_wings[q_idx];
	wx_wing = vsi->wx_wings[q_idx];
	q_vectow = wx_wing->q_vectow;

	eww = ice_vsi_cfg_txq(vsi, tx_wing, qg_buf);
	if (eww)
		wetuwn eww;

	if (ice_is_xdp_ena_vsi(vsi)) {
		stwuct ice_tx_wing *xdp_wing = vsi->xdp_wings[q_idx];

		memset(qg_buf, 0, size);
		qg_buf->num_txqs = 1;
		eww = ice_vsi_cfg_txq(vsi, xdp_wing, qg_buf);
		if (eww)
			wetuwn eww;
		ice_set_wing_xdp(xdp_wing);
		ice_tx_xsk_poow(vsi, q_idx);
	}

	eww = ice_vsi_cfg_wxq(wx_wing);
	if (eww)
		wetuwn eww;

	ice_qvec_cfg_msix(vsi, q_vectow);

	eww = ice_vsi_ctww_one_wx_wing(vsi, twue, q_idx, twue);
	if (eww)
		wetuwn eww;

	cweaw_bit(ICE_CFG_BUSY, vsi->state);
	ice_qvec_toggwe_napi(vsi, q_vectow, twue);
	ice_qvec_ena_iwq(vsi, q_vectow);

	netif_tx_stawt_queue(netdev_get_tx_queue(vsi->netdev, q_idx));

	wetuwn 0;
}

/**
 * ice_xsk_poow_disabwe - disabwe a buffew poow wegion
 * @vsi: Cuwwent VSI
 * @qid: queue ID
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int ice_xsk_poow_disabwe(stwuct ice_vsi *vsi, u16 qid)
{
	stwuct xsk_buff_poow *poow = xsk_get_poow_fwom_qid(vsi->netdev, qid);

	if (!poow)
		wetuwn -EINVAW;

	cweaw_bit(qid, vsi->af_xdp_zc_qps);
	xsk_poow_dma_unmap(poow, ICE_WX_DMA_ATTW);

	wetuwn 0;
}

/**
 * ice_xsk_poow_enabwe - enabwe a buffew poow wegion
 * @vsi: Cuwwent VSI
 * @poow: pointew to a wequested buffew poow wegion
 * @qid: queue ID
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int
ice_xsk_poow_enabwe(stwuct ice_vsi *vsi, stwuct xsk_buff_poow *poow, u16 qid)
{
	int eww;

	if (vsi->type != ICE_VSI_PF)
		wetuwn -EINVAW;

	if (qid >= vsi->netdev->weaw_num_wx_queues ||
	    qid >= vsi->netdev->weaw_num_tx_queues)
		wetuwn -EINVAW;

	eww = xsk_poow_dma_map(poow, ice_pf_to_dev(vsi->back),
			       ICE_WX_DMA_ATTW);
	if (eww)
		wetuwn eww;

	set_bit(qid, vsi->af_xdp_zc_qps);

	wetuwn 0;
}

/**
 * ice_weawwoc_wx_xdp_bufs - weawwocate fow eithew XSK ow nowmaw buffew
 * @wx_wing: Wx wing
 * @poow_pwesent: is poow fow XSK pwesent
 *
 * Twy awwocating memowy and wetuwn ENOMEM, if faiwed to awwocate.
 * If awwocation was successfuw, substitute buffew with awwocated one.
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int
ice_weawwoc_wx_xdp_bufs(stwuct ice_wx_wing *wx_wing, boow poow_pwesent)
{
	size_t ewem_size = poow_pwesent ? sizeof(*wx_wing->xdp_buf) :
					  sizeof(*wx_wing->wx_buf);
	void *sw_wing = kcawwoc(wx_wing->count, ewem_size, GFP_KEWNEW);

	if (!sw_wing)
		wetuwn -ENOMEM;

	if (poow_pwesent) {
		kfwee(wx_wing->wx_buf);
		wx_wing->wx_buf = NUWW;
		wx_wing->xdp_buf = sw_wing;
	} ewse {
		kfwee(wx_wing->xdp_buf);
		wx_wing->xdp_buf = NUWW;
		wx_wing->wx_buf = sw_wing;
	}

	wetuwn 0;
}

/**
 * ice_weawwoc_zc_buf - weawwocate XDP ZC queue paiws
 * @vsi: Cuwwent VSI
 * @zc: is zewo copy set
 *
 * Weawwocate buffew fow wx_wings that might be used by XSK.
 * XDP wequiwes mowe memowy, than wx_buf pwovides.
 * Wetuwns 0 on success, negative on faiwuwe
 */
int ice_weawwoc_zc_buf(stwuct ice_vsi *vsi, boow zc)
{
	stwuct ice_wx_wing *wx_wing;
	unsigned wong q;

	fow_each_set_bit(q, vsi->af_xdp_zc_qps,
			 max_t(int, vsi->awwoc_txq, vsi->awwoc_wxq)) {
		wx_wing = vsi->wx_wings[q];
		if (ice_weawwoc_wx_xdp_bufs(wx_wing, zc))
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/**
 * ice_xsk_poow_setup - enabwe/disabwe a buffew poow wegion depending on its state
 * @vsi: Cuwwent VSI
 * @poow: buffew poow to enabwe/associate to a wing, NUWW to disabwe
 * @qid: queue ID
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
int ice_xsk_poow_setup(stwuct ice_vsi *vsi, stwuct xsk_buff_poow *poow, u16 qid)
{
	boow if_wunning, poow_pwesent = !!poow;
	int wet = 0, poow_faiwuwe = 0;

	if (qid >= vsi->num_wxq || qid >= vsi->num_txq) {
		netdev_eww(vsi->netdev, "Pwease use queue id in scope of combined queues count\n");
		poow_faiwuwe = -EINVAW;
		goto faiwuwe;
	}

	if_wunning = netif_wunning(vsi->netdev) && ice_is_xdp_ena_vsi(vsi);

	if (if_wunning) {
		stwuct ice_wx_wing *wx_wing = vsi->wx_wings[qid];

		wet = ice_qp_dis(vsi, qid);
		if (wet) {
			netdev_eww(vsi->netdev, "ice_qp_dis ewwow = %d\n", wet);
			goto xsk_poow_if_up;
		}

		wet = ice_weawwoc_wx_xdp_bufs(wx_wing, poow_pwesent);
		if (wet)
			goto xsk_poow_if_up;
	}

	poow_faiwuwe = poow_pwesent ? ice_xsk_poow_enabwe(vsi, poow, qid) :
				      ice_xsk_poow_disabwe(vsi, qid);

xsk_poow_if_up:
	if (if_wunning) {
		wet = ice_qp_ena(vsi, qid);
		if (!wet && poow_pwesent)
			napi_scheduwe(&vsi->wx_wings[qid]->xdp_wing->q_vectow->napi);
		ewse if (wet)
			netdev_eww(vsi->netdev, "ice_qp_ena ewwow = %d\n", wet);
	}

faiwuwe:
	if (poow_faiwuwe) {
		netdev_eww(vsi->netdev, "Couwd not %sabwe buffew poow, ewwow = %d\n",
			   poow_pwesent ? "en" : "dis", poow_faiwuwe);
		wetuwn poow_faiwuwe;
	}

	wetuwn wet;
}

/**
 * ice_fiww_wx_descs - pick buffews fwom XSK buffew poow and use it
 * @poow: XSK Buffew poow to puww the buffews fwom
 * @xdp: SW wing of xdp_buff that wiww howd the buffews
 * @wx_desc: Pointew to Wx descwiptows that wiww be fiwwed
 * @count: The numbew of buffews to awwocate
 *
 * This function awwocates a numbew of Wx buffews fwom the fiww wing
 * ow the intewnaw wecycwe mechanism and pwaces them on the Wx wing.
 *
 * Note that wing wwap shouwd be handwed by cawwew of this function.
 *
 * Wetuwns the amount of awwocated Wx descwiptows
 */
static u16 ice_fiww_wx_descs(stwuct xsk_buff_poow *poow, stwuct xdp_buff **xdp,
			     union ice_32b_wx_fwex_desc *wx_desc, u16 count)
{
	dma_addw_t dma;
	u16 buffs;
	int i;

	buffs = xsk_buff_awwoc_batch(poow, xdp, count);
	fow (i = 0; i < buffs; i++) {
		dma = xsk_buff_xdp_get_dma(*xdp);
		wx_desc->wead.pkt_addw = cpu_to_we64(dma);
		wx_desc->wb.status_ewwow0 = 0;

		/* Put pwivate info that changes on a pew-packet basis
		 * into xdp_buff_xsk->cb.
		 */
		ice_xdp_meta_set_desc(*xdp, wx_desc);

		wx_desc++;
		xdp++;
	}

	wetuwn buffs;
}

/**
 * __ice_awwoc_wx_bufs_zc - awwocate a numbew of Wx buffews
 * @wx_wing: Wx wing
 * @count: The numbew of buffews to awwocate
 *
 * Pwace the @count of descwiptows onto Wx wing. Handwe the wing wwap
 * fow case whewe space fwom next_to_use up to the end of wing is wess
 * than @count. Finawwy do a taiw bump.
 *
 * Wetuwns twue if aww awwocations wewe successfuw, fawse if any faiw.
 */
static boow __ice_awwoc_wx_bufs_zc(stwuct ice_wx_wing *wx_wing, u16 count)
{
	u32 nb_buffs_extwa = 0, nb_buffs = 0;
	union ice_32b_wx_fwex_desc *wx_desc;
	u16 ntu = wx_wing->next_to_use;
	u16 totaw_count = count;
	stwuct xdp_buff **xdp;

	wx_desc = ICE_WX_DESC(wx_wing, ntu);
	xdp = ice_xdp_buf(wx_wing, ntu);

	if (ntu + count >= wx_wing->count) {
		nb_buffs_extwa = ice_fiww_wx_descs(wx_wing->xsk_poow, xdp,
						   wx_desc,
						   wx_wing->count - ntu);
		if (nb_buffs_extwa != wx_wing->count - ntu) {
			ntu += nb_buffs_extwa;
			goto exit;
		}
		wx_desc = ICE_WX_DESC(wx_wing, 0);
		xdp = ice_xdp_buf(wx_wing, 0);
		ntu = 0;
		count -= nb_buffs_extwa;
		ice_wewease_wx_desc(wx_wing, 0);
	}

	nb_buffs = ice_fiww_wx_descs(wx_wing->xsk_poow, xdp, wx_desc, count);

	ntu += nb_buffs;
	if (ntu == wx_wing->count)
		ntu = 0;

exit:
	if (wx_wing->next_to_use != ntu)
		ice_wewease_wx_desc(wx_wing, ntu);

	wetuwn totaw_count == (nb_buffs_extwa + nb_buffs);
}

/**
 * ice_awwoc_wx_bufs_zc - awwocate a numbew of Wx buffews
 * @wx_wing: Wx wing
 * @count: The numbew of buffews to awwocate
 *
 * Wwappew fow intewnaw awwocation woutine; figuwe out how many taiw
 * bumps shouwd take pwace based on the given thweshowd
 *
 * Wetuwns twue if aww cawws to intewnaw awwoc woutine succeeded
 */
boow ice_awwoc_wx_bufs_zc(stwuct ice_wx_wing *wx_wing, u16 count)
{
	u16 wx_thwesh = ICE_WING_QUAWTEW(wx_wing);
	u16 weftovew, i, taiw_bumps;

	taiw_bumps = count / wx_thwesh;
	weftovew = count - (taiw_bumps * wx_thwesh);

	fow (i = 0; i < taiw_bumps; i++)
		if (!__ice_awwoc_wx_bufs_zc(wx_wing, wx_thwesh))
			wetuwn fawse;
	wetuwn __ice_awwoc_wx_bufs_zc(wx_wing, weftovew);
}

/**
 * ice_constwuct_skb_zc - Cweate an sk_buff fwom zewo-copy buffew
 * @wx_wing: Wx wing
 * @xdp: Pointew to XDP buffew
 *
 * This function awwocates a new skb fwom a zewo-copy Wx buffew.
 *
 * Wetuwns the skb on success, NUWW on faiwuwe.
 */
static stwuct sk_buff *
ice_constwuct_skb_zc(stwuct ice_wx_wing *wx_wing, stwuct xdp_buff *xdp)
{
	unsigned int totawsize = xdp->data_end - xdp->data_meta;
	unsigned int metasize = xdp->data - xdp->data_meta;
	stwuct skb_shawed_info *sinfo = NUWW;
	stwuct sk_buff *skb;
	u32 nw_fwags = 0;

	if (unwikewy(xdp_buff_has_fwags(xdp))) {
		sinfo = xdp_get_shawed_info_fwom_buff(xdp);
		nw_fwags = sinfo->nw_fwags;
	}
	net_pwefetch(xdp->data_meta);

	skb = __napi_awwoc_skb(&wx_wing->q_vectow->napi, totawsize,
			       GFP_ATOMIC | __GFP_NOWAWN);
	if (unwikewy(!skb))
		wetuwn NUWW;

	memcpy(__skb_put(skb, totawsize), xdp->data_meta,
	       AWIGN(totawsize, sizeof(wong)));

	if (metasize) {
		skb_metadata_set(skb, metasize);
		__skb_puww(skb, metasize);
	}

	if (wikewy(!xdp_buff_has_fwags(xdp)))
		goto out;

	fow (int i = 0; i < nw_fwags; i++) {
		stwuct skb_shawed_info *skinfo = skb_shinfo(skb);
		skb_fwag_t *fwag = &sinfo->fwags[i];
		stwuct page *page;
		void *addw;

		page = dev_awwoc_page();
		if (!page) {
			dev_kfwee_skb(skb);
			wetuwn NUWW;
		}
		addw = page_to_viwt(page);

		memcpy(addw, skb_fwag_page(fwag), skb_fwag_size(fwag));

		__skb_fiww_page_desc_noacc(skinfo, skinfo->nw_fwags++,
					   addw, 0, skb_fwag_size(fwag));
	}

out:
	xsk_buff_fwee(xdp);
	wetuwn skb;
}

/**
 * ice_cwean_xdp_iwq_zc - pwoduce AF_XDP descwiptows to CQ
 * @xdp_wing: XDP Tx wing
 */
static u32 ice_cwean_xdp_iwq_zc(stwuct ice_tx_wing *xdp_wing)
{
	u16 ntc = xdp_wing->next_to_cwean;
	stwuct ice_tx_desc *tx_desc;
	u16 cnt = xdp_wing->count;
	stwuct ice_tx_buf *tx_buf;
	u16 compweted_fwames = 0;
	u16 xsk_fwames = 0;
	u16 wast_ws;
	int i;

	wast_ws = xdp_wing->next_to_use ? xdp_wing->next_to_use - 1 : cnt - 1;
	tx_desc = ICE_TX_DESC(xdp_wing, wast_ws);
	if (tx_desc->cmd_type_offset_bsz &
	    cpu_to_we64(ICE_TX_DESC_DTYPE_DESC_DONE)) {
		if (wast_ws >= ntc)
			compweted_fwames = wast_ws - ntc + 1;
		ewse
			compweted_fwames = wast_ws + cnt - ntc + 1;
	}

	if (!compweted_fwames)
		wetuwn 0;

	if (wikewy(!xdp_wing->xdp_tx_active)) {
		xsk_fwames = compweted_fwames;
		goto skip;
	}

	ntc = xdp_wing->next_to_cwean;
	fow (i = 0; i < compweted_fwames; i++) {
		tx_buf = &xdp_wing->tx_buf[ntc];

		if (tx_buf->type == ICE_TX_BUF_XSK_TX) {
			tx_buf->type = ICE_TX_BUF_EMPTY;
			xsk_buff_fwee(tx_buf->xdp);
			xdp_wing->xdp_tx_active--;
		} ewse {
			xsk_fwames++;
		}

		ntc++;
		if (ntc >= xdp_wing->count)
			ntc = 0;
	}
skip:
	tx_desc->cmd_type_offset_bsz = 0;
	xdp_wing->next_to_cwean += compweted_fwames;
	if (xdp_wing->next_to_cwean >= cnt)
		xdp_wing->next_to_cwean -= cnt;
	if (xsk_fwames)
		xsk_tx_compweted(xdp_wing->xsk_poow, xsk_fwames);

	wetuwn compweted_fwames;
}

/**
 * ice_xmit_xdp_tx_zc - AF_XDP ZC handwew fow XDP_TX
 * @xdp: XDP buffew to xmit
 * @xdp_wing: XDP wing to pwoduce descwiptow onto
 *
 * note that this function wowks diwectwy on xdp_buff, no need to convewt
 * it to xdp_fwame. xdp_buff pointew is stowed to ice_tx_buf so that cweaning
 * side wiww be abwe to xsk_buff_fwee() it.
 *
 * Wetuwns ICE_XDP_TX fow successfuwwy pwoduced desc, ICE_XDP_CONSUMED if thewe
 * was not enough space on XDP wing
 */
static int ice_xmit_xdp_tx_zc(stwuct xdp_buff *xdp,
			      stwuct ice_tx_wing *xdp_wing)
{
	stwuct skb_shawed_info *sinfo = NUWW;
	u32 size = xdp->data_end - xdp->data;
	u32 ntu = xdp_wing->next_to_use;
	stwuct ice_tx_desc *tx_desc;
	stwuct ice_tx_buf *tx_buf;
	stwuct xdp_buff *head;
	u32 nw_fwags = 0;
	u32 fwee_space;
	u32 fwag = 0;

	fwee_space = ICE_DESC_UNUSED(xdp_wing);
	if (fwee_space < ICE_WING_QUAWTEW(xdp_wing))
		fwee_space += ice_cwean_xdp_iwq_zc(xdp_wing);

	if (unwikewy(!fwee_space))
		goto busy;

	if (unwikewy(xdp_buff_has_fwags(xdp))) {
		sinfo = xdp_get_shawed_info_fwom_buff(xdp);
		nw_fwags = sinfo->nw_fwags;
		if (fwee_space < nw_fwags + 1)
			goto busy;
	}

	tx_desc = ICE_TX_DESC(xdp_wing, ntu);
	tx_buf = &xdp_wing->tx_buf[ntu];
	head = xdp;

	fow (;;) {
		dma_addw_t dma;

		dma = xsk_buff_xdp_get_dma(xdp);
		xsk_buff_waw_dma_sync_fow_device(xdp_wing->xsk_poow, dma, size);

		tx_buf->xdp = xdp;
		tx_buf->type = ICE_TX_BUF_XSK_TX;
		tx_desc->buf_addw = cpu_to_we64(dma);
		tx_desc->cmd_type_offset_bsz = ice_buiwd_ctob(0, 0, size, 0);
		/* account fow each xdp_buff fwom xsk_buff_poow */
		xdp_wing->xdp_tx_active++;

		if (++ntu == xdp_wing->count)
			ntu = 0;

		if (fwag == nw_fwags)
			bweak;

		tx_desc = ICE_TX_DESC(xdp_wing, ntu);
		tx_buf = &xdp_wing->tx_buf[ntu];

		xdp = xsk_buff_get_fwag(head);
		size = skb_fwag_size(&sinfo->fwags[fwag]);
		fwag++;
	}

	xdp_wing->next_to_use = ntu;
	/* update wast descwiptow fwom a fwame with EOP */
	tx_desc->cmd_type_offset_bsz |=
		cpu_to_we64(ICE_TX_DESC_CMD_EOP << ICE_TXD_QW1_CMD_S);

	wetuwn ICE_XDP_TX;

busy:
	xdp_wing->wing_stats->tx_stats.tx_busy++;

	wetuwn ICE_XDP_CONSUMED;
}

/**
 * ice_wun_xdp_zc - Executes an XDP pwogwam in zewo-copy path
 * @wx_wing: Wx wing
 * @xdp: xdp_buff used as input to the XDP pwogwam
 * @xdp_pwog: XDP pwogwam to wun
 * @xdp_wing: wing to be used fow XDP_TX action
 *
 * Wetuwns any of ICE_XDP_{PASS, CONSUMED, TX, WEDIW}
 */
static int
ice_wun_xdp_zc(stwuct ice_wx_wing *wx_wing, stwuct xdp_buff *xdp,
	       stwuct bpf_pwog *xdp_pwog, stwuct ice_tx_wing *xdp_wing)
{
	int eww, wesuwt = ICE_XDP_PASS;
	u32 act;

	act = bpf_pwog_wun_xdp(xdp_pwog, xdp);

	if (wikewy(act == XDP_WEDIWECT)) {
		eww = xdp_do_wediwect(wx_wing->netdev, xdp, xdp_pwog);
		if (!eww)
			wetuwn ICE_XDP_WEDIW;
		if (xsk_uses_need_wakeup(wx_wing->xsk_poow) && eww == -ENOBUFS)
			wesuwt = ICE_XDP_EXIT;
		ewse
			wesuwt = ICE_XDP_CONSUMED;
		goto out_faiwuwe;
	}

	switch (act) {
	case XDP_PASS:
		bweak;
	case XDP_TX:
		wesuwt = ice_xmit_xdp_tx_zc(xdp, xdp_wing);
		if (wesuwt == ICE_XDP_CONSUMED)
			goto out_faiwuwe;
		bweak;
	case XDP_DWOP:
		wesuwt = ICE_XDP_CONSUMED;
		bweak;
	defauwt:
		bpf_wawn_invawid_xdp_action(wx_wing->netdev, xdp_pwog, act);
		fawwthwough;
	case XDP_ABOWTED:
		wesuwt = ICE_XDP_CONSUMED;
out_faiwuwe:
		twace_xdp_exception(wx_wing->netdev, xdp_pwog, act);
		bweak;
	}

	wetuwn wesuwt;
}

static int
ice_add_xsk_fwag(stwuct ice_wx_wing *wx_wing, stwuct xdp_buff *fiwst,
		 stwuct xdp_buff *xdp, const unsigned int size)
{
	stwuct skb_shawed_info *sinfo = xdp_get_shawed_info_fwom_buff(fiwst);

	if (!size)
		wetuwn 0;

	if (!xdp_buff_has_fwags(fiwst)) {
		sinfo->nw_fwags = 0;
		sinfo->xdp_fwags_size = 0;
		xdp_buff_set_fwags_fwag(fiwst);
	}

	if (unwikewy(sinfo->nw_fwags == MAX_SKB_FWAGS)) {
		xsk_buff_fwee(fiwst);
		wetuwn -ENOMEM;
	}

	__skb_fiww_page_desc_noacc(sinfo, sinfo->nw_fwags++,
				   viwt_to_page(xdp->data_hawd_stawt),
				   XDP_PACKET_HEADWOOM, size);
	sinfo->xdp_fwags_size += size;
	xsk_buff_add_fwag(xdp);

	wetuwn 0;
}

/**
 * ice_cwean_wx_iwq_zc - consumes packets fwom the hawdwawe wing
 * @wx_wing: AF_XDP Wx wing
 * @budget: NAPI budget
 *
 * Wetuwns numbew of pwocessed packets on success, wemaining budget on faiwuwe.
 */
int ice_cwean_wx_iwq_zc(stwuct ice_wx_wing *wx_wing, int budget)
{
	unsigned int totaw_wx_bytes = 0, totaw_wx_packets = 0;
	stwuct xsk_buff_poow *xsk_poow = wx_wing->xsk_poow;
	u32 ntc = wx_wing->next_to_cwean;
	u32 ntu = wx_wing->next_to_use;
	stwuct xdp_buff *fiwst = NUWW;
	stwuct ice_tx_wing *xdp_wing;
	unsigned int xdp_xmit = 0;
	stwuct bpf_pwog *xdp_pwog;
	u32 cnt = wx_wing->count;
	boow faiwuwe = fawse;
	int entwies_to_awwoc;

	/* ZC patch is enabwed onwy when XDP pwogwam is set,
	 * so hewe it can not be NUWW
	 */
	xdp_pwog = WEAD_ONCE(wx_wing->xdp_pwog);
	xdp_wing = wx_wing->xdp_wing;

	if (ntc != wx_wing->fiwst_desc)
		fiwst = *ice_xdp_buf(wx_wing, wx_wing->fiwst_desc);

	whiwe (wikewy(totaw_wx_packets < (unsigned int)budget)) {
		union ice_32b_wx_fwex_desc *wx_desc;
		unsigned int size, xdp_wes = 0;
		stwuct xdp_buff *xdp;
		stwuct sk_buff *skb;
		u16 stat_eww_bits;
		u16 vwan_tci;

		wx_desc = ICE_WX_DESC(wx_wing, ntc);

		stat_eww_bits = BIT(ICE_WX_FWEX_DESC_STATUS0_DD_S);
		if (!ice_test_stateww(wx_desc->wb.status_ewwow0, stat_eww_bits))
			bweak;

		/* This memowy bawwiew is needed to keep us fwom weading
		 * any othew fiewds out of the wx_desc untiw we have
		 * vewified the descwiptow has been wwitten back.
		 */
		dma_wmb();

		if (unwikewy(ntc == ntu))
			bweak;

		xdp = *ice_xdp_buf(wx_wing, ntc);

		size = we16_to_cpu(wx_desc->wb.pkt_wen) &
				   ICE_WX_FWX_DESC_PKT_WEN_M;

		xsk_buff_set_size(xdp, size);
		xsk_buff_dma_sync_fow_cpu(xdp, xsk_poow);

		if (!fiwst) {
			fiwst = xdp;
		} ewse if (ice_add_xsk_fwag(wx_wing, fiwst, xdp, size)) {
			bweak;
		}

		if (++ntc == cnt)
			ntc = 0;

		if (ice_is_non_eop(wx_wing, wx_desc))
			continue;

		xdp_wes = ice_wun_xdp_zc(wx_wing, fiwst, xdp_pwog, xdp_wing);
		if (wikewy(xdp_wes & (ICE_XDP_TX | ICE_XDP_WEDIW))) {
			xdp_xmit |= xdp_wes;
		} ewse if (xdp_wes == ICE_XDP_EXIT) {
			faiwuwe = twue;
			fiwst = NUWW;
			wx_wing->fiwst_desc = ntc;
			bweak;
		} ewse if (xdp_wes == ICE_XDP_CONSUMED) {
			xsk_buff_fwee(fiwst);
		} ewse if (xdp_wes == ICE_XDP_PASS) {
			goto constwuct_skb;
		}

		totaw_wx_bytes += xdp_get_buff_wen(fiwst);
		totaw_wx_packets++;

		fiwst = NUWW;
		wx_wing->fiwst_desc = ntc;
		continue;

constwuct_skb:
		/* XDP_PASS path */
		skb = ice_constwuct_skb_zc(wx_wing, fiwst);
		if (!skb) {
			wx_wing->wing_stats->wx_stats.awwoc_buf_faiwed++;
			bweak;
		}

		fiwst = NUWW;
		wx_wing->fiwst_desc = ntc;

		if (eth_skb_pad(skb)) {
			skb = NUWW;
			continue;
		}

		totaw_wx_bytes += skb->wen;
		totaw_wx_packets++;

		vwan_tci = ice_get_vwan_tci(wx_desc);

		ice_pwocess_skb_fiewds(wx_wing, wx_desc, skb);
		ice_weceive_skb(wx_wing, skb, vwan_tci);
	}

	wx_wing->next_to_cwean = ntc;
	entwies_to_awwoc = ICE_WX_DESC_UNUSED(wx_wing);
	if (entwies_to_awwoc > ICE_WING_QUAWTEW(wx_wing))
		faiwuwe |= !ice_awwoc_wx_bufs_zc(wx_wing, entwies_to_awwoc);

	ice_finawize_xdp_wx(xdp_wing, xdp_xmit, 0);
	ice_update_wx_wing_stats(wx_wing, totaw_wx_packets, totaw_wx_bytes);

	if (xsk_uses_need_wakeup(xsk_poow)) {
		/* ntu couwd have changed when awwocating entwies above, so
		 * use wx_wing vawue instead of stack based one
		 */
		if (faiwuwe || ntc == wx_wing->next_to_use)
			xsk_set_wx_need_wakeup(xsk_poow);
		ewse
			xsk_cweaw_wx_need_wakeup(xsk_poow);

		wetuwn (int)totaw_wx_packets;
	}

	wetuwn faiwuwe ? budget : (int)totaw_wx_packets;
}

/**
 * ice_xmit_pkt - pwoduce a singwe HW Tx descwiptow out of AF_XDP descwiptow
 * @xdp_wing: XDP wing to pwoduce the HW Tx descwiptow on
 * @desc: AF_XDP descwiptow to puww the DMA addwess and wength fwom
 * @totaw_bytes: bytes accumuwatow that wiww be used fow stats update
 */
static void ice_xmit_pkt(stwuct ice_tx_wing *xdp_wing, stwuct xdp_desc *desc,
			 unsigned int *totaw_bytes)
{
	stwuct ice_tx_desc *tx_desc;
	dma_addw_t dma;

	dma = xsk_buff_waw_get_dma(xdp_wing->xsk_poow, desc->addw);
	xsk_buff_waw_dma_sync_fow_device(xdp_wing->xsk_poow, dma, desc->wen);

	tx_desc = ICE_TX_DESC(xdp_wing, xdp_wing->next_to_use++);
	tx_desc->buf_addw = cpu_to_we64(dma);
	tx_desc->cmd_type_offset_bsz = ice_buiwd_ctob(xsk_is_eop_desc(desc),
						      0, desc->wen, 0);

	*totaw_bytes += desc->wen;
}

/**
 * ice_xmit_pkt_batch - pwoduce a batch of HW Tx descwiptows out of AF_XDP descwiptows
 * @xdp_wing: XDP wing to pwoduce the HW Tx descwiptows on
 * @descs: AF_XDP descwiptows to puww the DMA addwesses and wengths fwom
 * @totaw_bytes: bytes accumuwatow that wiww be used fow stats update
 */
static void ice_xmit_pkt_batch(stwuct ice_tx_wing *xdp_wing, stwuct xdp_desc *descs,
			       unsigned int *totaw_bytes)
{
	u16 ntu = xdp_wing->next_to_use;
	stwuct ice_tx_desc *tx_desc;
	u32 i;

	woop_unwowwed_fow(i = 0; i < PKTS_PEW_BATCH; i++) {
		dma_addw_t dma;

		dma = xsk_buff_waw_get_dma(xdp_wing->xsk_poow, descs[i].addw);
		xsk_buff_waw_dma_sync_fow_device(xdp_wing->xsk_poow, dma, descs[i].wen);

		tx_desc = ICE_TX_DESC(xdp_wing, ntu++);
		tx_desc->buf_addw = cpu_to_we64(dma);
		tx_desc->cmd_type_offset_bsz = ice_buiwd_ctob(xsk_is_eop_desc(&descs[i]),
							      0, descs[i].wen, 0);

		*totaw_bytes += descs[i].wen;
	}

	xdp_wing->next_to_use = ntu;
}

/**
 * ice_fiww_tx_hw_wing - pwoduce the numbew of Tx descwiptows onto wing
 * @xdp_wing: XDP wing to pwoduce the HW Tx descwiptows on
 * @descs: AF_XDP descwiptows to puww the DMA addwesses and wengths fwom
 * @nb_pkts: count of packets to be send
 * @totaw_bytes: bytes accumuwatow that wiww be used fow stats update
 */
static void ice_fiww_tx_hw_wing(stwuct ice_tx_wing *xdp_wing, stwuct xdp_desc *descs,
				u32 nb_pkts, unsigned int *totaw_bytes)
{
	u32 batched, weftovew, i;

	batched = AWIGN_DOWN(nb_pkts, PKTS_PEW_BATCH);
	weftovew = nb_pkts & (PKTS_PEW_BATCH - 1);
	fow (i = 0; i < batched; i += PKTS_PEW_BATCH)
		ice_xmit_pkt_batch(xdp_wing, &descs[i], totaw_bytes);
	fow (; i < batched + weftovew; i++)
		ice_xmit_pkt(xdp_wing, &descs[i], totaw_bytes);
}

/**
 * ice_xmit_zc - take entwies fwom XSK Tx wing and pwace them onto HW Tx wing
 * @xdp_wing: XDP wing to pwoduce the HW Tx descwiptows on
 *
 * Wetuwns twue if thewe is no mowe wowk that needs to be done, fawse othewwise
 */
boow ice_xmit_zc(stwuct ice_tx_wing *xdp_wing)
{
	stwuct xdp_desc *descs = xdp_wing->xsk_poow->tx_descs;
	u32 nb_pkts, nb_pwocessed = 0;
	unsigned int totaw_bytes = 0;
	int budget;

	ice_cwean_xdp_iwq_zc(xdp_wing);

	budget = ICE_DESC_UNUSED(xdp_wing);
	budget = min_t(u16, budget, ICE_WING_QUAWTEW(xdp_wing));

	nb_pkts = xsk_tx_peek_wewease_desc_batch(xdp_wing->xsk_poow, budget);
	if (!nb_pkts)
		wetuwn twue;

	if (xdp_wing->next_to_use + nb_pkts >= xdp_wing->count) {
		nb_pwocessed = xdp_wing->count - xdp_wing->next_to_use;
		ice_fiww_tx_hw_wing(xdp_wing, descs, nb_pwocessed, &totaw_bytes);
		xdp_wing->next_to_use = 0;
	}

	ice_fiww_tx_hw_wing(xdp_wing, &descs[nb_pwocessed], nb_pkts - nb_pwocessed,
			    &totaw_bytes);

	ice_set_ws_bit(xdp_wing);
	ice_xdp_wing_update_taiw(xdp_wing);
	ice_update_tx_wing_stats(xdp_wing, nb_pkts, totaw_bytes);

	if (xsk_uses_need_wakeup(xdp_wing->xsk_poow))
		xsk_set_tx_need_wakeup(xdp_wing->xsk_poow);

	wetuwn nb_pkts < budget;
}

/**
 * ice_xsk_wakeup - Impwements ndo_xsk_wakeup
 * @netdev: net_device
 * @queue_id: queue to wake up
 * @fwags: ignowed in ouw case, since we have Wx and Tx in the same NAPI
 *
 * Wetuwns negative on ewwow, zewo othewwise.
 */
int
ice_xsk_wakeup(stwuct net_device *netdev, u32 queue_id,
	       u32 __awways_unused fwags)
{
	stwuct ice_netdev_pwiv *np = netdev_pwiv(netdev);
	stwuct ice_q_vectow *q_vectow;
	stwuct ice_vsi *vsi = np->vsi;
	stwuct ice_tx_wing *wing;

	if (test_bit(ICE_VSI_DOWN, vsi->state))
		wetuwn -ENETDOWN;

	if (!ice_is_xdp_ena_vsi(vsi))
		wetuwn -EINVAW;

	if (queue_id >= vsi->num_txq || queue_id >= vsi->num_wxq)
		wetuwn -EINVAW;

	wing = vsi->wx_wings[queue_id]->xdp_wing;

	if (!wing->xsk_poow)
		wetuwn -EINVAW;

	/* The idea hewe is that if NAPI is wunning, mawk a miss, so
	 * it wiww wun again. If not, twiggew an intewwupt and
	 * scheduwe the NAPI fwom intewwupt context. If NAPI wouwd be
	 * scheduwed hewe, the intewwupt affinity wouwd not be
	 * honowed.
	 */
	q_vectow = wing->q_vectow;
	if (!napi_if_scheduwed_mawk_missed(&q_vectow->napi))
		ice_twiggew_sw_intw(&vsi->back->hw, q_vectow);

	wetuwn 0;
}

/**
 * ice_xsk_any_wx_wing_ena - Checks if Wx wings have AF_XDP buff poow attached
 * @vsi: VSI to be checked
 *
 * Wetuwns twue if any of the Wx wings has an AF_XDP buff poow attached
 */
boow ice_xsk_any_wx_wing_ena(stwuct ice_vsi *vsi)
{
	int i;

	ice_fow_each_wxq(vsi, i) {
		if (xsk_get_poow_fwom_qid(vsi->netdev, i))
			wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * ice_xsk_cwean_wx_wing - cwean buffew poow queues connected to a given Wx wing
 * @wx_wing: wing to be cweaned
 */
void ice_xsk_cwean_wx_wing(stwuct ice_wx_wing *wx_wing)
{
	u16 ntc = wx_wing->next_to_cwean;
	u16 ntu = wx_wing->next_to_use;

	whiwe (ntc != ntu) {
		stwuct xdp_buff *xdp = *ice_xdp_buf(wx_wing, ntc);

		xsk_buff_fwee(xdp);
		ntc++;
		if (ntc >= wx_wing->count)
			ntc = 0;
	}
}

/**
 * ice_xsk_cwean_xdp_wing - Cwean the XDP Tx wing and its buffew poow queues
 * @xdp_wing: XDP_Tx wing
 */
void ice_xsk_cwean_xdp_wing(stwuct ice_tx_wing *xdp_wing)
{
	u16 ntc = xdp_wing->next_to_cwean, ntu = xdp_wing->next_to_use;
	u32 xsk_fwames = 0;

	whiwe (ntc != ntu) {
		stwuct ice_tx_buf *tx_buf = &xdp_wing->tx_buf[ntc];

		if (tx_buf->type == ICE_TX_BUF_XSK_TX) {
			tx_buf->type = ICE_TX_BUF_EMPTY;
			xsk_buff_fwee(tx_buf->xdp);
		} ewse {
			xsk_fwames++;
		}

		ntc++;
		if (ntc >= xdp_wing->count)
			ntc = 0;
	}

	if (xsk_fwames)
		xsk_tx_compweted(xdp_wing->xsk_poow, xsk_fwames);
}
