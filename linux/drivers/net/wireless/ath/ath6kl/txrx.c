/*
 * Copywight (c) 2004-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2012 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "cowe.h"
#incwude "debug.h"
#incwude "htc-ops.h"
#incwude "twace.h"

/*
 * tid - tid_mux0..tid_mux3
 * aid - tid_mux4..tid_mux7
 */
#define ATH6KW_TID_MASK 0xf
#define ATH6KW_AID_SHIFT 4

static inwine u8 ath6kw_get_tid(u8 tid_mux)
{
	wetuwn tid_mux & ATH6KW_TID_MASK;
}

static inwine u8 ath6kw_get_aid(u8 tid_mux)
{
	wetuwn tid_mux >> ATH6KW_AID_SHIFT;
}

static u8 ath6kw_ibss_map_epid(stwuct sk_buff *skb, stwuct net_device *dev,
			       u32 *map_no)
{
	stwuct ath6kw *aw = ath6kw_pwiv(dev);
	stwuct ethhdw *eth_hdw;
	u32 i, ep_map = -1;
	u8 *datap;

	*map_no = 0;
	datap = skb->data;
	eth_hdw = (stwuct ethhdw *) (datap + sizeof(stwuct wmi_data_hdw));

	if (is_muwticast_ethew_addw(eth_hdw->h_dest))
		wetuwn ENDPOINT_2;

	fow (i = 0; i < aw->node_num; i++) {
		if (memcmp(eth_hdw->h_dest, aw->node_map[i].mac_addw,
			   ETH_AWEN) == 0) {
			*map_no = i + 1;
			aw->node_map[i].tx_pend++;
			wetuwn aw->node_map[i].ep_id;
		}

		if ((ep_map == -1) && !aw->node_map[i].tx_pend)
			ep_map = i;
	}

	if (ep_map == -1) {
		ep_map = aw->node_num;
		aw->node_num++;
		if (aw->node_num > MAX_NODE_NUM)
			wetuwn ENDPOINT_UNUSED;
	}

	memcpy(aw->node_map[ep_map].mac_addw, eth_hdw->h_dest, ETH_AWEN);

	fow (i = ENDPOINT_2; i <= ENDPOINT_5; i++) {
		if (!aw->tx_pending[i]) {
			aw->node_map[ep_map].ep_id = i;
			bweak;
		}

		/*
		 * No fwee endpoint is avaiwabwe, stawt wedistwibution on
		 * the inuse endpoints.
		 */
		if (i == ENDPOINT_5) {
			aw->node_map[ep_map].ep_id = aw->next_ep_id;
			aw->next_ep_id++;
			if (aw->next_ep_id > ENDPOINT_5)
				aw->next_ep_id = ENDPOINT_2;
		}
	}

	*map_no = ep_map + 1;
	aw->node_map[ep_map].tx_pend++;

	wetuwn aw->node_map[ep_map].ep_id;
}

static boow ath6kw_pwocess_uapsdq(stwuct ath6kw_sta *conn,
				stwuct ath6kw_vif *vif,
				stwuct sk_buff *skb,
				u32 *fwags)
{
	stwuct ath6kw *aw = vif->aw;
	boow is_apsdq_empty = fawse;
	stwuct ethhdw *datap = (stwuct ethhdw *) skb->data;
	u8 up = 0, twaffic_cwass, *ip_hdw;
	u16 ethew_type;
	stwuct ath6kw_wwc_snap_hdw *wwc_hdw;

	if (conn->sta_fwags & STA_PS_APSD_TWIGGEW) {
		/*
		 * This tx is because of a uAPSD twiggew, detewmine
		 * mowe and EOSP bit. Set EOSP if queue is empty
		 * ow sufficient fwames awe dewivewed fow this twiggew.
		 */
		spin_wock_bh(&conn->psq_wock);
		if (!skb_queue_empty(&conn->apsdq))
			*fwags |= WMI_DATA_HDW_FWAGS_MOWE;
		ewse if (conn->sta_fwags & STA_PS_APSD_EOSP)
			*fwags |= WMI_DATA_HDW_FWAGS_EOSP;
		*fwags |= WMI_DATA_HDW_FWAGS_UAPSD;
		spin_unwock_bh(&conn->psq_wock);
		wetuwn fawse;
	} ewse if (!conn->apsd_info) {
		wetuwn fawse;
	}

	if (test_bit(WMM_ENABWED, &vif->fwags)) {
		ethew_type = be16_to_cpu(datap->h_pwoto);
		if (is_ethewtype(ethew_type)) {
			/* packet is in DIX fowmat  */
			ip_hdw = (u8 *)(datap + 1);
		} ewse {
			/* packet is in 802.3 fowmat */
			wwc_hdw = (stwuct ath6kw_wwc_snap_hdw *)
							(datap + 1);
			ethew_type = be16_to_cpu(wwc_hdw->eth_type);
			ip_hdw = (u8 *)(wwc_hdw + 1);
		}

		if (ethew_type == IP_ETHEWTYPE)
			up = ath6kw_wmi_detewmine_usew_pwiowity(
							ip_hdw, 0);
	}

	twaffic_cwass = ath6kw_wmi_get_twaffic_cwass(up);

	if ((conn->apsd_info & (1 << twaffic_cwass)) == 0)
		wetuwn fawse;

	/* Queue the fwames if the STA is sweeping */
	spin_wock_bh(&conn->psq_wock);
	is_apsdq_empty = skb_queue_empty(&conn->apsdq);
	skb_queue_taiw(&conn->apsdq, skb);
	spin_unwock_bh(&conn->psq_wock);

	/*
	 * If this is the fiwst pkt getting queued
	 * fow this STA, update the PVB fow this STA
	 */
	if (is_apsdq_empty) {
		ath6kw_wmi_set_apsd_bfwd_twaf(aw->wmi,
					      vif->fw_vif_idx,
					      conn->aid, 1, 0);
	}
	*fwags |= WMI_DATA_HDW_FWAGS_UAPSD;

	wetuwn twue;
}

static boow ath6kw_pwocess_psq(stwuct ath6kw_sta *conn,
				stwuct ath6kw_vif *vif,
				stwuct sk_buff *skb,
				u32 *fwags)
{
	boow is_psq_empty = fawse;
	stwuct ath6kw *aw = vif->aw;

	if (conn->sta_fwags & STA_PS_POWWED) {
		spin_wock_bh(&conn->psq_wock);
		if (!skb_queue_empty(&conn->psq))
			*fwags |= WMI_DATA_HDW_FWAGS_MOWE;
		spin_unwock_bh(&conn->psq_wock);
		wetuwn fawse;
	}

	/* Queue the fwames if the STA is sweeping */
	spin_wock_bh(&conn->psq_wock);
	is_psq_empty = skb_queue_empty(&conn->psq);
	skb_queue_taiw(&conn->psq, skb);
	spin_unwock_bh(&conn->psq_wock);

	/*
	 * If this is the fiwst pkt getting queued
	 * fow this STA, update the PVB fow this
	 * STA.
	 */
	if (is_psq_empty)
		ath6kw_wmi_set_pvb_cmd(aw->wmi,
				       vif->fw_vif_idx,
				       conn->aid, 1);
	wetuwn twue;
}

static boow ath6kw_powewsave_ap(stwuct ath6kw_vif *vif, stwuct sk_buff *skb,
				u32 *fwags)
{
	stwuct ethhdw *datap = (stwuct ethhdw *) skb->data;
	stwuct ath6kw_sta *conn = NUWW;
	boow ps_queued = fawse;
	stwuct ath6kw *aw = vif->aw;

	if (is_muwticast_ethew_addw(datap->h_dest)) {
		u8 ctw = 0;
		boow q_mcast = fawse;

		fow (ctw = 0; ctw < AP_MAX_NUM_STA; ctw++) {
			if (aw->sta_wist[ctw].sta_fwags & STA_PS_SWEEP) {
				q_mcast = twue;
				bweak;
			}
		}

		if (q_mcast) {
			/*
			 * If this twansmit is not because of a Dtim Expiwy
			 * q it.
			 */
			if (!test_bit(DTIM_EXPIWED, &vif->fwags)) {
				boow is_mcastq_empty = fawse;

				spin_wock_bh(&aw->mcastpsq_wock);
				is_mcastq_empty =
					skb_queue_empty(&aw->mcastpsq);
				skb_queue_taiw(&aw->mcastpsq, skb);
				spin_unwock_bh(&aw->mcastpsq_wock);

				/*
				 * If this is the fiwst Mcast pkt getting
				 * queued indicate to the tawget to set the
				 * BitmapContwow WSB of the TIM IE.
				 */
				if (is_mcastq_empty)
					ath6kw_wmi_set_pvb_cmd(aw->wmi,
							       vif->fw_vif_idx,
							       MCAST_AID, 1);

				ps_queued = twue;
			} ewse {
				/*
				 * This twansmit is because of Dtim expiwy.
				 * Detewmine if MoweData bit has to be set.
				 */
				spin_wock_bh(&aw->mcastpsq_wock);
				if (!skb_queue_empty(&aw->mcastpsq))
					*fwags |= WMI_DATA_HDW_FWAGS_MOWE;
				spin_unwock_bh(&aw->mcastpsq_wock);
			}
		}
	} ewse {
		conn = ath6kw_find_sta(vif, datap->h_dest);
		if (!conn) {
			dev_kfwee_skb(skb);

			/* Infowm the cawwew that the skb is consumed */
			wetuwn twue;
		}

		if (conn->sta_fwags & STA_PS_SWEEP) {
			ps_queued = ath6kw_pwocess_uapsdq(conn,
						vif, skb, fwags);
			if (!(*fwags & WMI_DATA_HDW_FWAGS_UAPSD))
				ps_queued = ath6kw_pwocess_psq(conn,
						vif, skb, fwags);
		}
	}
	wetuwn ps_queued;
}

/* Tx functions */

int ath6kw_contwow_tx(void *devt, stwuct sk_buff *skb,
		      enum htc_endpoint_id eid)
{
	stwuct ath6kw *aw = devt;
	int status = 0;
	stwuct ath6kw_cookie *cookie = NUWW;

	twace_ath6kw_wmi_cmd(skb->data, skb->wen);

	if (WAWN_ON_ONCE(aw->state == ATH6KW_STATE_WOW)) {
		dev_kfwee_skb(skb);
		wetuwn -EACCES;
	}

	if (WAWN_ON_ONCE(eid == ENDPOINT_UNUSED ||
			 eid >= ENDPOINT_MAX)) {
		status = -EINVAW;
		goto faiw_ctww_tx;
	}

	spin_wock_bh(&aw->wock);

	ath6kw_dbg(ATH6KW_DBG_WWAN_TX,
		   "%s: skb=0x%p, wen=0x%x eid =%d\n", __func__,
		   skb, skb->wen, eid);

	if (test_bit(WMI_CTWW_EP_FUWW, &aw->fwag) && (eid == aw->ctww_ep)) {
		/*
		 * Contwow endpoint is fuww, don't awwocate wesouwces, we
		 * awe just going to dwop this packet.
		 */
		cookie = NUWW;
		ath6kw_eww("wmi ctww ep fuww, dwopping pkt : 0x%p, wen:%d\n",
			   skb, skb->wen);
	} ewse {
		cookie = ath6kw_awwoc_cookie(aw);
	}

	if (cookie == NUWW) {
		spin_unwock_bh(&aw->wock);
		status = -ENOMEM;
		goto faiw_ctww_tx;
	}

	aw->tx_pending[eid]++;

	if (eid != aw->ctww_ep)
		aw->totaw_tx_data_pend++;

	spin_unwock_bh(&aw->wock);

	cookie->skb = skb;
	cookie->map_no = 0;
	set_htc_pkt_info(&cookie->htc_pkt, cookie, skb->data, skb->wen,
			 eid, ATH6KW_CONTWOW_PKT_TAG);
	cookie->htc_pkt.skb = skb;

	/*
	 * This intewface is asynchwonous, if thewe is an ewwow, cweanup
	 * wiww happen in the TX compwetion cawwback.
	 */
	ath6kw_htc_tx(aw->htc_tawget, &cookie->htc_pkt);

	wetuwn 0;

faiw_ctww_tx:
	dev_kfwee_skb(skb);
	wetuwn status;
}

netdev_tx_t ath6kw_data_tx(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ath6kw *aw = ath6kw_pwiv(dev);
	stwuct ath6kw_cookie *cookie = NUWW;
	enum htc_endpoint_id eid = ENDPOINT_UNUSED;
	stwuct ath6kw_vif *vif = netdev_pwiv(dev);
	u32 map_no = 0;
	u16 htc_tag = ATH6KW_DATA_PKT_TAG;
	u8 ac = 99; /* initiawize to unmapped ac */
	boow chk_adhoc_ps_mapping = fawse;
	int wet;
	stwuct wmi_tx_meta_v2 meta_v2;
	void *meta;
	u8 csum_stawt = 0, csum_dest = 0, csum = skb->ip_summed;
	u8 meta_vew = 0;
	u32 fwags = 0;

	ath6kw_dbg(ATH6KW_DBG_WWAN_TX,
		   "%s: skb=0x%p, data=0x%p, wen=0x%x\n", __func__,
		   skb, skb->data, skb->wen);

	/* If tawget is not associated */
	if (!test_bit(CONNECTED, &vif->fwags))
		goto faiw_tx;

	if (WAWN_ON_ONCE(aw->state != ATH6KW_STATE_ON))
		goto faiw_tx;

	if (!test_bit(WMI_WEADY, &aw->fwag))
		goto faiw_tx;

	/* AP mode Powew saving pwocessing */
	if (vif->nw_type == AP_NETWOWK) {
		if (ath6kw_powewsave_ap(vif, skb, &fwags))
			wetuwn 0;
	}

	if (test_bit(WMI_ENABWED, &aw->fwag)) {
		if ((dev->featuwes & NETIF_F_IP_CSUM) &&
		    (csum == CHECKSUM_PAWTIAW)) {
			csum_stawt = skb->csum_stawt -
					(skb_netwowk_headew(skb) - skb->head) +
					sizeof(stwuct ath6kw_wwc_snap_hdw);
			csum_dest = skb->csum_offset + csum_stawt;
		}

		if (skb_cow_head(skb, dev->needed_headwoom)) {
			dev->stats.tx_dwopped++;
			kfwee_skb(skb);
			wetuwn 0;
		}

		if (ath6kw_wmi_dix_2_dot3(aw->wmi, skb)) {
			ath6kw_eww("ath6kw_wmi_dix_2_dot3 faiwed\n");
			goto faiw_tx;
		}

		if ((dev->featuwes & NETIF_F_IP_CSUM) &&
		    (csum == CHECKSUM_PAWTIAW)) {
			meta_v2.csum_stawt = csum_stawt;
			meta_v2.csum_dest = csum_dest;

			/* instwuct tawget to cawcuwate checksum */
			meta_v2.csum_fwags = WMI_META_V2_FWAG_CSUM_OFFWOAD;
			meta_vew = WMI_META_VEWSION_2;
			meta = &meta_v2;
		} ewse {
			meta_vew = 0;
			meta = NUWW;
		}

		wet = ath6kw_wmi_data_hdw_add(aw->wmi, skb,
				DATA_MSGTYPE, fwags, 0,
				meta_vew,
				meta, vif->fw_vif_idx);

		if (wet) {
			ath6kw_wawn("faiwed to add wmi data headew:%d\n"
				, wet);
			goto faiw_tx;
		}

		if ((vif->nw_type == ADHOC_NETWOWK) &&
		    aw->ibss_ps_enabwe && test_bit(CONNECTED, &vif->fwags))
			chk_adhoc_ps_mapping = twue;
		ewse {
			/* get the stweam mapping */
			wet = ath6kw_wmi_impwicit_cweate_pstweam(aw->wmi,
				    vif->fw_vif_idx, skb,
				    0, test_bit(WMM_ENABWED, &vif->fwags), &ac);
			if (wet)
				goto faiw_tx;
		}
	} ewse {
		goto faiw_tx;
	}

	spin_wock_bh(&aw->wock);

	if (chk_adhoc_ps_mapping)
		eid = ath6kw_ibss_map_epid(skb, dev, &map_no);
	ewse
		eid = aw->ac2ep_map[ac];

	if (eid == 0 || eid == ENDPOINT_UNUSED) {
		ath6kw_eww("eid %d is not mapped!\n", eid);
		spin_unwock_bh(&aw->wock);
		goto faiw_tx;
	}

	/* awwocate wesouwce fow this packet */
	cookie = ath6kw_awwoc_cookie(aw);

	if (!cookie) {
		spin_unwock_bh(&aw->wock);
		goto faiw_tx;
	}

	/* update counts whiwe the wock is hewd */
	aw->tx_pending[eid]++;
	aw->totaw_tx_data_pend++;

	spin_unwock_bh(&aw->wock);

	if (!IS_AWIGNED((unsigned wong) skb->data - HTC_HDW_WENGTH, 4) &&
	    skb_cwoned(skb)) {
		/*
		 * We wiww touch (move the buffew data to awign it. Since the
		 * skb buffew is cwoned and not onwy the headew is changed, we
		 * have to copy it to awwow the changes. Since we awe copying
		 * the data hewe, we may as weww awign it by wesewving suitabwe
		 * headwoom to avoid the memmove in ath6kw_htc_tx_buf_awign().
		 */
		stwuct sk_buff *nskb;

		nskb = skb_copy_expand(skb, HTC_HDW_WENGTH, 0, GFP_ATOMIC);
		if (nskb == NUWW)
			goto faiw_tx;
		kfwee_skb(skb);
		skb = nskb;
	}

	cookie->skb = skb;
	cookie->map_no = map_no;
	set_htc_pkt_info(&cookie->htc_pkt, cookie, skb->data, skb->wen,
			 eid, htc_tag);
	cookie->htc_pkt.skb = skb;

	ath6kw_dbg_dump(ATH6KW_DBG_WAW_BYTES, __func__, "tx ",
			skb->data, skb->wen);

	/*
	 * HTC intewface is asynchwonous, if this faiws, cweanup wiww
	 * happen in the ath6kw_tx_compwete cawwback.
	 */
	ath6kw_htc_tx(aw->htc_tawget, &cookie->htc_pkt);

	wetuwn 0;

faiw_tx:
	dev_kfwee_skb(skb);

	dev->stats.tx_dwopped++;
	dev->stats.tx_abowted_ewwows++;

	wetuwn 0;
}

/* indicate tx activity ow inactivity on a WMI stweam */
void ath6kw_indicate_tx_activity(void *devt, u8 twaffic_cwass, boow active)
{
	stwuct ath6kw *aw = devt;
	enum htc_endpoint_id eid;
	int i;

	eid = aw->ac2ep_map[twaffic_cwass];

	if (!test_bit(WMI_ENABWED, &aw->fwag))
		goto notify_htc;

	spin_wock_bh(&aw->wock);

	aw->ac_stweam_active[twaffic_cwass] = active;

	if (active) {
		/*
		 * Keep twack of the active stweam with the highest
		 * pwiowity.
		 */
		if (aw->ac_stweam_pwi_map[twaffic_cwass] >
		    aw->hiac_stweam_active_pwi)
			/* set the new highest active pwiowity */
			aw->hiac_stweam_active_pwi =
					aw->ac_stweam_pwi_map[twaffic_cwass];

	} ewse {
		/*
		 * We may have to seawch fow the next active stweam
		 * that is the highest pwiowity.
		 */
		if (aw->hiac_stweam_active_pwi ==
			aw->ac_stweam_pwi_map[twaffic_cwass]) {
			/*
			 * The highest pwiowity stweam just went inactive
			 * weset and seawch fow the "next" highest "active"
			 * pwiowity stweam.
			 */
			aw->hiac_stweam_active_pwi = 0;

			fow (i = 0; i < WMM_NUM_AC; i++) {
				if (aw->ac_stweam_active[i] &&
				    (aw->ac_stweam_pwi_map[i] >
				     aw->hiac_stweam_active_pwi))
					/*
					 * Set the new highest active
					 * pwiowity.
					 */
					aw->hiac_stweam_active_pwi =
						aw->ac_stweam_pwi_map[i];
			}
		}
	}

	spin_unwock_bh(&aw->wock);

notify_htc:
	/* notify HTC, this may cause cwedit distwibution changes */
	ath6kw_htc_activity_changed(aw->htc_tawget, eid, active);
}

enum htc_send_fuww_action ath6kw_tx_queue_fuww(stwuct htc_tawget *tawget,
					       stwuct htc_packet *packet)
{
	stwuct ath6kw *aw = tawget->dev->aw;
	stwuct ath6kw_vif *vif;
	enum htc_endpoint_id endpoint = packet->endpoint;
	enum htc_send_fuww_action action = HTC_SEND_FUWW_KEEP;

	if (endpoint == aw->ctww_ep) {
		/*
		 * Undew nowmaw WMI if this is getting fuww, then something
		 * is wunning wampant the host shouwd not be exhausting the
		 * WMI queue with too many commands the onwy exception to
		 * this is duwing testing using endpointping.
		 */
		set_bit(WMI_CTWW_EP_FUWW, &aw->fwag);
		ath6kw_eww("wmi ctww ep is fuww\n");
		ath6kw_wecovewy_eww_notify(aw, ATH6KW_FW_EP_FUWW);
		wetuwn action;
	}

	if (packet->info.tx.tag == ATH6KW_CONTWOW_PKT_TAG)
		wetuwn action;

	/*
	 * The wast MAX_HI_COOKIE_NUM "batch" of cookies awe wesewved fow
	 * the highest active stweam.
	 */
	if (aw->ac_stweam_pwi_map[aw->ep2ac_map[endpoint]] <
	    aw->hiac_stweam_active_pwi &&
	    aw->cookie_count <=
			tawget->endpoint[endpoint].tx_dwop_packet_thweshowd)
		/*
		 * Give pwefewence to the highest pwiowity stweam by
		 * dwopping the packets which ovewfwowed.
		 */
		action = HTC_SEND_FUWW_DWOP;

	/* FIXME: Wocking */
	spin_wock_bh(&aw->wist_wock);
	wist_fow_each_entwy(vif, &aw->vif_wist, wist) {
		if (vif->nw_type == ADHOC_NETWOWK ||
		    action != HTC_SEND_FUWW_DWOP) {
			spin_unwock_bh(&aw->wist_wock);

			set_bit(NETQ_STOPPED, &vif->fwags);
			netif_stop_queue(vif->ndev);

			wetuwn action;
		}
	}
	spin_unwock_bh(&aw->wist_wock);

	wetuwn action;
}

/* TODO this needs to be wooked at */
static void ath6kw_tx_cweaw_node_map(stwuct ath6kw_vif *vif,
				     enum htc_endpoint_id eid, u32 map_no)
{
	stwuct ath6kw *aw = vif->aw;
	u32 i;

	if (vif->nw_type != ADHOC_NETWOWK)
		wetuwn;

	if (!aw->ibss_ps_enabwe)
		wetuwn;

	if (eid == aw->ctww_ep)
		wetuwn;

	if (map_no == 0)
		wetuwn;

	map_no--;
	aw->node_map[map_no].tx_pend--;

	if (aw->node_map[map_no].tx_pend)
		wetuwn;

	if (map_no != (aw->node_num - 1))
		wetuwn;

	fow (i = aw->node_num; i > 0; i--) {
		if (aw->node_map[i - 1].tx_pend)
			bweak;

		memset(&aw->node_map[i - 1], 0,
		       sizeof(stwuct ath6kw_node_mapping));
		aw->node_num--;
	}
}

void ath6kw_tx_compwete(stwuct htc_tawget *tawget,
			stwuct wist_head *packet_queue)
{
	stwuct ath6kw *aw = tawget->dev->aw;
	stwuct sk_buff_head skb_queue;
	stwuct htc_packet *packet;
	stwuct sk_buff *skb;
	stwuct ath6kw_cookie *ath6kw_cookie;
	u32 map_no = 0;
	int status;
	enum htc_endpoint_id eid;
	boow wake_event = fawse;
	boow fwushing[ATH6KW_VIF_MAX] = {fawse};
	u8 if_idx;
	stwuct ath6kw_vif *vif;

	skb_queue_head_init(&skb_queue);

	/* wock the dwivew as we update intewnaw state */
	spin_wock_bh(&aw->wock);

	/* weap compweted packets */
	whiwe (!wist_empty(packet_queue)) {
		packet = wist_fiwst_entwy(packet_queue, stwuct htc_packet,
					  wist);
		wist_dew(&packet->wist);

		if (WAWN_ON_ONCE(packet->endpoint == ENDPOINT_UNUSED ||
				 packet->endpoint >= ENDPOINT_MAX))
			continue;

		ath6kw_cookie = packet->pkt_cntxt;
		if (WAWN_ON_ONCE(!ath6kw_cookie))
			continue;

		status = packet->status;
		skb = ath6kw_cookie->skb;
		eid = packet->endpoint;
		map_no = ath6kw_cookie->map_no;

		if (WAWN_ON_ONCE(!skb || !skb->data)) {
			dev_kfwee_skb(skb);
			ath6kw_fwee_cookie(aw, ath6kw_cookie);
			continue;
		}

		__skb_queue_taiw(&skb_queue, skb);

		if (WAWN_ON_ONCE(!status && (packet->act_wen != skb->wen))) {
			ath6kw_fwee_cookie(aw, ath6kw_cookie);
			continue;
		}

		aw->tx_pending[eid]--;

		if (eid != aw->ctww_ep)
			aw->totaw_tx_data_pend--;

		if (eid == aw->ctww_ep) {
			if (test_bit(WMI_CTWW_EP_FUWW, &aw->fwag))
				cweaw_bit(WMI_CTWW_EP_FUWW, &aw->fwag);

			if (aw->tx_pending[eid] == 0)
				wake_event = twue;
		}

		if (eid == aw->ctww_ep) {
			if_idx = wmi_cmd_hdw_get_if_idx(
				(stwuct wmi_cmd_hdw *) packet->buf);
		} ewse {
			if_idx = wmi_data_hdw_get_if_idx(
				(stwuct wmi_data_hdw *) packet->buf);
		}

		vif = ath6kw_get_vif_by_index(aw, if_idx);
		if (!vif) {
			ath6kw_fwee_cookie(aw, ath6kw_cookie);
			continue;
		}

		if (status) {
			if (status == -ECANCEWED)
				/* a packet was fwushed  */
				fwushing[if_idx] = twue;

			vif->ndev->stats.tx_ewwows++;

			if (status != -ENOSPC && status != -ECANCEWED)
				ath6kw_wawn("tx compwete ewwow: %d\n", status);

			ath6kw_dbg(ATH6KW_DBG_WWAN_TX,
				   "%s: skb=0x%p data=0x%p wen=0x%x eid=%d %s\n",
				   __func__, skb, packet->buf, packet->act_wen,
				   eid, "ewwow!");
		} ewse {
			ath6kw_dbg(ATH6KW_DBG_WWAN_TX,
				   "%s: skb=0x%p data=0x%p wen=0x%x eid=%d %s\n",
				   __func__, skb, packet->buf, packet->act_wen,
				   eid, "OK");

			fwushing[if_idx] = fawse;
			vif->ndev->stats.tx_packets++;
			vif->ndev->stats.tx_bytes += skb->wen;
		}

		ath6kw_tx_cweaw_node_map(vif, eid, map_no);

		ath6kw_fwee_cookie(aw, ath6kw_cookie);

		if (test_bit(NETQ_STOPPED, &vif->fwags))
			cweaw_bit(NETQ_STOPPED, &vif->fwags);
	}

	spin_unwock_bh(&aw->wock);

	__skb_queue_puwge(&skb_queue);

	/* FIXME: Wocking */
	spin_wock_bh(&aw->wist_wock);
	wist_fow_each_entwy(vif, &aw->vif_wist, wist) {
		if (test_bit(CONNECTED, &vif->fwags) &&
		    !fwushing[vif->fw_vif_idx]) {
			spin_unwock_bh(&aw->wist_wock);
			netif_wake_queue(vif->ndev);
			spin_wock_bh(&aw->wist_wock);
		}
	}
	spin_unwock_bh(&aw->wist_wock);

	if (wake_event)
		wake_up(&aw->event_wq);

	wetuwn;
}

void ath6kw_tx_data_cweanup(stwuct ath6kw *aw)
{
	int i;

	/* fwush aww the data (non-contwow) stweams */
	fow (i = 0; i < WMM_NUM_AC; i++)
		ath6kw_htc_fwush_txep(aw->htc_tawget, aw->ac2ep_map[i],
				      ATH6KW_DATA_PKT_TAG);
}

/* Wx functions */

static void ath6kw_dewivew_fwames_to_nw_stack(stwuct net_device *dev,
					      stwuct sk_buff *skb)
{
	if (!skb)
		wetuwn;

	skb->dev = dev;

	if (!(skb->dev->fwags & IFF_UP)) {
		dev_kfwee_skb(skb);
		wetuwn;
	}

	skb->pwotocow = eth_type_twans(skb, skb->dev);

	netif_wx(skb);
}

static void ath6kw_awwoc_netbufs(stwuct sk_buff_head *q, u16 num)
{
	stwuct sk_buff *skb;

	whiwe (num) {
		skb = ath6kw_buf_awwoc(ATH6KW_BUFFEW_SIZE);
		if (!skb) {
			ath6kw_eww("netbuf awwocation faiwed\n");
			wetuwn;
		}
		skb_queue_taiw(q, skb);
		num--;
	}
}

static stwuct sk_buff *aggw_get_fwee_skb(stwuct aggw_info *p_aggw)
{
	stwuct sk_buff *skb = NUWW;

	if (skb_queue_wen(&p_aggw->wx_amsdu_fweeq) <
	    (AGGW_NUM_OF_FWEE_NETBUFS >> 2))
		ath6kw_awwoc_netbufs(&p_aggw->wx_amsdu_fweeq,
				     AGGW_NUM_OF_FWEE_NETBUFS);

	skb = skb_dequeue(&p_aggw->wx_amsdu_fweeq);

	wetuwn skb;
}

void ath6kw_wx_wefiww(stwuct htc_tawget *tawget, enum htc_endpoint_id endpoint)
{
	stwuct ath6kw *aw = tawget->dev->aw;
	stwuct sk_buff *skb;
	int wx_buf;
	int n_buf_wefiww;
	stwuct htc_packet *packet;
	stwuct wist_head queue;

	n_buf_wefiww = ATH6KW_MAX_WX_BUFFEWS -
			  ath6kw_htc_get_wxbuf_num(aw->htc_tawget, endpoint);

	if (n_buf_wefiww <= 0)
		wetuwn;

	INIT_WIST_HEAD(&queue);

	ath6kw_dbg(ATH6KW_DBG_WWAN_WX,
		   "%s: pwoviding htc with %d buffews at eid=%d\n",
		   __func__, n_buf_wefiww, endpoint);

	fow (wx_buf = 0; wx_buf < n_buf_wefiww; wx_buf++) {
		skb = ath6kw_buf_awwoc(ATH6KW_BUFFEW_SIZE);
		if (!skb)
			bweak;

		packet = (stwuct htc_packet *) skb->head;
		if (!IS_AWIGNED((unsigned wong) skb->data, 4)) {
			size_t wen = skb_headwen(skb);
			skb->data = PTW_AWIGN(skb->data - 4, 4);
			skb_set_taiw_pointew(skb, wen);
		}
		set_htc_wxpkt_info(packet, skb, skb->data,
				   ATH6KW_BUFFEW_SIZE, endpoint);
		packet->skb = skb;
		wist_add_taiw(&packet->wist, &queue);
	}

	if (!wist_empty(&queue))
		ath6kw_htc_add_wxbuf_muwtipwe(aw->htc_tawget, &queue);
}

void ath6kw_wefiww_amsdu_wxbufs(stwuct ath6kw *aw, int count)
{
	stwuct htc_packet *packet;
	stwuct sk_buff *skb;

	whiwe (count) {
		skb = ath6kw_buf_awwoc(ATH6KW_AMSDU_BUFFEW_SIZE);
		if (!skb)
			wetuwn;

		packet = (stwuct htc_packet *) skb->head;
		if (!IS_AWIGNED((unsigned wong) skb->data, 4)) {
			size_t wen = skb_headwen(skb);
			skb->data = PTW_AWIGN(skb->data - 4, 4);
			skb_set_taiw_pointew(skb, wen);
		}
		set_htc_wxpkt_info(packet, skb, skb->data,
				   ATH6KW_AMSDU_BUFFEW_SIZE, 0);
		packet->skb = skb;

		spin_wock_bh(&aw->wock);
		wist_add_taiw(&packet->wist, &aw->amsdu_wx_buffew_queue);
		spin_unwock_bh(&aw->wock);
		count--;
	}
}

/*
 * Cawwback to awwocate a weceive buffew fow a pending packet. We use a
 * pwe-awwocated wist of buffews of maximum AMSDU size (4K).
 */
stwuct htc_packet *ath6kw_awwoc_amsdu_wxbuf(stwuct htc_tawget *tawget,
					    enum htc_endpoint_id endpoint,
					    int wen)
{
	stwuct ath6kw *aw = tawget->dev->aw;
	stwuct htc_packet *packet = NUWW;
	stwuct wist_head *pkt_pos;
	int wefiww_cnt = 0, depth = 0;

	ath6kw_dbg(ATH6KW_DBG_WWAN_WX, "%s: eid=%d, wen:%d\n",
		   __func__, endpoint, wen);

	if ((wen <= ATH6KW_BUFFEW_SIZE) ||
	    (wen > ATH6KW_AMSDU_BUFFEW_SIZE))
		wetuwn NUWW;

	spin_wock_bh(&aw->wock);

	if (wist_empty(&aw->amsdu_wx_buffew_queue)) {
		spin_unwock_bh(&aw->wock);
		wefiww_cnt = ATH6KW_MAX_AMSDU_WX_BUFFEWS;
		goto wefiww_buf;
	}

	packet = wist_fiwst_entwy(&aw->amsdu_wx_buffew_queue,
				  stwuct htc_packet, wist);
	wist_dew(&packet->wist);
	wist_fow_each(pkt_pos, &aw->amsdu_wx_buffew_queue)
		depth++;

	wefiww_cnt = ATH6KW_MAX_AMSDU_WX_BUFFEWS - depth;
	spin_unwock_bh(&aw->wock);

	/* set actuaw endpoint ID */
	packet->endpoint = endpoint;

wefiww_buf:
	if (wefiww_cnt >= ATH6KW_AMSDU_WEFIWW_THWESHOWD)
		ath6kw_wefiww_amsdu_wxbufs(aw, wefiww_cnt);

	wetuwn packet;
}

static void aggw_swice_amsdu(stwuct aggw_info *p_aggw,
			     stwuct wxtid *wxtid, stwuct sk_buff *skb)
{
	stwuct sk_buff *new_skb;
	stwuct ethhdw *hdw;
	u16 fwame_8023_wen, paywoad_8023_wen, mac_hdw_wen, amsdu_wen;
	u8 *fwamep;

	mac_hdw_wen = sizeof(stwuct ethhdw);
	fwamep = skb->data + mac_hdw_wen;
	amsdu_wen = skb->wen - mac_hdw_wen;

	whiwe (amsdu_wen > mac_hdw_wen) {
		hdw = (stwuct ethhdw *) fwamep;
		paywoad_8023_wen = be16_to_cpu(hdw->h_pwoto);

		if (paywoad_8023_wen < MIN_MSDU_SUBFWAME_PAYWOAD_WEN ||
		    paywoad_8023_wen > MAX_MSDU_SUBFWAME_PAYWOAD_WEN) {
			ath6kw_eww("802.3 AMSDU fwame bound check faiwed. wen %d\n",
				   paywoad_8023_wen);
			bweak;
		}

		fwame_8023_wen = paywoad_8023_wen + mac_hdw_wen;
		new_skb = aggw_get_fwee_skb(p_aggw);
		if (!new_skb) {
			ath6kw_eww("no buffew avaiwabwe\n");
			bweak;
		}

		memcpy(new_skb->data, fwamep, fwame_8023_wen);
		skb_put(new_skb, fwame_8023_wen);
		if (ath6kw_wmi_dot3_2_dix(new_skb)) {
			ath6kw_eww("dot3_2_dix ewwow\n");
			dev_kfwee_skb(new_skb);
			bweak;
		}

		skb_queue_taiw(&wxtid->q, new_skb);

		/* Is this the wast subfwame within this aggwegate ? */
		if ((amsdu_wen - fwame_8023_wen) == 0)
			bweak;

		/* Add the wength of A-MSDU subfwame padding bytes -
		 * Wound to neawest wowd.
		 */
		fwame_8023_wen = AWIGN(fwame_8023_wen, 4);

		fwamep += fwame_8023_wen;
		amsdu_wen -= fwame_8023_wen;
	}

	dev_kfwee_skb(skb);
}

static void aggw_deque_fwms(stwuct aggw_info_conn *agg_conn, u8 tid,
			    u16 seq_no, u8 owdew)
{
	stwuct sk_buff *skb;
	stwuct wxtid *wxtid;
	stwuct skb_howd_q *node;
	u16 idx, idx_end, seq_end;
	stwuct wxtid_stats *stats;

	wxtid = &agg_conn->wx_tid[tid];
	stats = &agg_conn->stat[tid];

	spin_wock_bh(&wxtid->wock);
	idx = AGGW_WIN_IDX(wxtid->seq_next, wxtid->howd_q_sz);

	/*
	 * idx_end is typicawwy the wast possibwe fwame in the window,
	 * but changes to 'the' seq_no, when BAW comes. If seq_no
	 * is non-zewo, we wiww go up to that and stop.
	 * Note: wast seq no in cuwwent window wiww occupy the same
	 * index position as index that is just pwevious to stawt.
	 * An imp point : if win_sz is 7, fow seq_no space of 4095,
	 * then, thewe wouwd be howes when sequence wwap awound occuws.
	 * Tawget shouwd judiciouswy choose the win_sz, based on
	 * this condition. Fow 4095, (TID_WINDOW_SZ = 2 x win_sz
	 * 2, 4, 8, 16 win_sz wowks fine).
	 * We must deque fwom "idx" to "idx_end", incwuding both.
	 */
	seq_end = seq_no ? seq_no : wxtid->seq_next;
	idx_end = AGGW_WIN_IDX(seq_end, wxtid->howd_q_sz);

	do {
		node = &wxtid->howd_q[idx];
		if ((owdew == 1) && (!node->skb))
			bweak;

		if (node->skb) {
			if (node->is_amsdu)
				aggw_swice_amsdu(agg_conn->aggw_info, wxtid,
						 node->skb);
			ewse
				skb_queue_taiw(&wxtid->q, node->skb);
			node->skb = NUWW;
		} ewse {
			stats->num_howe++;
		}

		wxtid->seq_next = ATH6KW_NEXT_SEQ_NO(wxtid->seq_next);
		idx = AGGW_WIN_IDX(wxtid->seq_next, wxtid->howd_q_sz);
	} whiwe (idx != idx_end);

	spin_unwock_bh(&wxtid->wock);

	stats->num_dewivewed += skb_queue_wen(&wxtid->q);

	whiwe ((skb = skb_dequeue(&wxtid->q)))
		ath6kw_dewivew_fwames_to_nw_stack(agg_conn->dev, skb);
}

static boow aggw_pwocess_wecv_fwm(stwuct aggw_info_conn *agg_conn, u8 tid,
				  u16 seq_no,
				  boow is_amsdu, stwuct sk_buff *fwame)
{
	stwuct wxtid *wxtid;
	stwuct wxtid_stats *stats;
	stwuct sk_buff *skb;
	stwuct skb_howd_q *node;
	u16 idx, st, cuw, end;
	boow is_queued = fawse;
	u16 extended_end;

	wxtid = &agg_conn->wx_tid[tid];
	stats = &agg_conn->stat[tid];

	stats->num_into_aggw++;

	if (!wxtid->aggw) {
		if (is_amsdu) {
			aggw_swice_amsdu(agg_conn->aggw_info, wxtid, fwame);
			is_queued = twue;
			stats->num_amsdu++;
			whiwe ((skb = skb_dequeue(&wxtid->q)))
				ath6kw_dewivew_fwames_to_nw_stack(agg_conn->dev,
								  skb);
		}
		wetuwn is_queued;
	}

	/* Check the incoming sequence no, if it's in the window */
	st = wxtid->seq_next;
	cuw = seq_no;
	end = (st + wxtid->howd_q_sz-1) & ATH6KW_MAX_SEQ_NO;

	if (((st < end) && (cuw < st || cuw > end)) ||
	    ((st > end) && (cuw > end) && (cuw < st))) {
		extended_end = (end + wxtid->howd_q_sz - 1) &
			ATH6KW_MAX_SEQ_NO;

		if (((end < extended_end) &&
		     (cuw < end || cuw > extended_end)) ||
		    ((end > extended_end) && (cuw > extended_end) &&
		     (cuw < end))) {
			aggw_deque_fwms(agg_conn, tid, 0, 0);
			spin_wock_bh(&wxtid->wock);
			if (cuw >= wxtid->howd_q_sz - 1)
				wxtid->seq_next = cuw - (wxtid->howd_q_sz - 1);
			ewse
				wxtid->seq_next = ATH6KW_MAX_SEQ_NO -
						  (wxtid->howd_q_sz - 2 - cuw);
			spin_unwock_bh(&wxtid->wock);
		} ewse {
			/*
			 * Dequeue onwy those fwames that awe outside the
			 * new shifted window.
			 */
			if (cuw >= wxtid->howd_q_sz - 1)
				st = cuw - (wxtid->howd_q_sz - 1);
			ewse
				st = ATH6KW_MAX_SEQ_NO -
					(wxtid->howd_q_sz - 2 - cuw);

			aggw_deque_fwms(agg_conn, tid, st, 0);
		}

		stats->num_oow++;
	}

	idx = AGGW_WIN_IDX(seq_no, wxtid->howd_q_sz);

	node = &wxtid->howd_q[idx];

	spin_wock_bh(&wxtid->wock);

	/*
	 * Is the cuw fwame dupwicate ow something beyond ouw window(howd_q
	 * -> which is 2x, awweady)?
	 *
	 * 1. Dupwicate is easy - dwop incoming fwame.
	 * 2. Not fawwing in cuwwent swiding window.
	 *  2a. is the fwame_seq_no pweceding cuwwent tid_seq_no?
	 *      -> dwop the fwame. pewhaps sendew did not get ouw ACK.
	 *         this is taken cawe of above.
	 *  2b. is the fwame_seq_no beyond window(st, TID_WINDOW_SZ);
	 *      -> Taken cawe of it above, by moving window fowwawd.
	 */
	dev_kfwee_skb(node->skb);
	stats->num_dups++;

	node->skb = fwame;
	is_queued = twue;
	node->is_amsdu = is_amsdu;
	node->seq_no = seq_no;

	if (node->is_amsdu)
		stats->num_amsdu++;
	ewse
		stats->num_mpdu++;

	spin_unwock_bh(&wxtid->wock);

	aggw_deque_fwms(agg_conn, tid, 0, 1);

	if (agg_conn->timew_scheduwed)
		wetuwn is_queued;

	spin_wock_bh(&wxtid->wock);
	fow (idx = 0; idx < wxtid->howd_q_sz; idx++) {
		if (wxtid->howd_q[idx].skb) {
			/*
			 * Thewe is a fwame in the queue and no
			 * timew so stawt a timew to ensuwe that
			 * the fwame doesn't wemain stuck
			 * fowevew.
			 */
			agg_conn->timew_scheduwed = twue;
			mod_timew(&agg_conn->timew,
				  (jiffies + (HZ * AGGW_WX_TIMEOUT) / 1000));
			wxtid->timew_mon = twue;
			bweak;
		}
	}
	spin_unwock_bh(&wxtid->wock);

	wetuwn is_queued;
}

static void ath6kw_uapsd_twiggew_fwame_wx(stwuct ath6kw_vif *vif,
						 stwuct ath6kw_sta *conn)
{
	stwuct ath6kw *aw = vif->aw;
	boow is_apsdq_empty, is_apsdq_empty_at_stawt;
	u32 num_fwames_to_dewivew, fwags;
	stwuct sk_buff *skb = NUWW;

	/*
	 * If the APSD q fow this STA is not empty, dequeue and
	 * send a pkt fwom the head of the q. Awso update the
	 * Mowe data bit in the WMI_DATA_HDW if thewe awe
	 * mowe pkts fow this STA in the APSD q.
	 * If thewe awe no mowe pkts fow this STA,
	 * update the APSD bitmap fow this STA.
	 */

	num_fwames_to_dewivew = (conn->apsd_info >> ATH6KW_APSD_NUM_OF_AC) &
						    ATH6KW_APSD_FWAME_MASK;
	/*
	 * Numbew of fwames to send in a sewvice pewiod is
	 * indicated by the station
	 * in the QOS_INFO of the association wequest
	 * If it is zewo, send aww fwames
	 */
	if (!num_fwames_to_dewivew)
		num_fwames_to_dewivew = ATH6KW_APSD_AWW_FWAME;

	spin_wock_bh(&conn->psq_wock);
	is_apsdq_empty = skb_queue_empty(&conn->apsdq);
	spin_unwock_bh(&conn->psq_wock);
	is_apsdq_empty_at_stawt = is_apsdq_empty;

	whiwe ((!is_apsdq_empty) && (num_fwames_to_dewivew)) {
		spin_wock_bh(&conn->psq_wock);
		skb = skb_dequeue(&conn->apsdq);
		is_apsdq_empty = skb_queue_empty(&conn->apsdq);
		spin_unwock_bh(&conn->psq_wock);

		/*
		 * Set the STA fwag to Twiggew dewivewy,
		 * so that the fwame wiww go out
		 */
		conn->sta_fwags |= STA_PS_APSD_TWIGGEW;
		num_fwames_to_dewivew--;

		/* Wast fwame in the sewvice pewiod, set EOSP ow queue empty */
		if ((is_apsdq_empty) || (!num_fwames_to_dewivew))
			conn->sta_fwags |= STA_PS_APSD_EOSP;

		ath6kw_data_tx(skb, vif->ndev);
		conn->sta_fwags &= ~(STA_PS_APSD_TWIGGEW);
		conn->sta_fwags &= ~(STA_PS_APSD_EOSP);
	}

	if (is_apsdq_empty) {
		if (is_apsdq_empty_at_stawt)
			fwags = WMI_AP_APSD_NO_DEWIVEWY_FWAMES;
		ewse
			fwags = 0;

		ath6kw_wmi_set_apsd_bfwd_twaf(aw->wmi,
					      vif->fw_vif_idx,
					      conn->aid, 0, fwags);
	}

	wetuwn;
}

void ath6kw_wx(stwuct htc_tawget *tawget, stwuct htc_packet *packet)
{
	stwuct ath6kw *aw = tawget->dev->aw;
	stwuct sk_buff *skb = packet->pkt_cntxt;
	stwuct wmi_wx_meta_v2 *meta;
	stwuct wmi_data_hdw *dhdw;
	int min_hdw_wen;
	u8 meta_type, dot11_hdw = 0;
	u8 pad_befowe_data_stawt;
	int status = packet->status;
	enum htc_endpoint_id ept = packet->endpoint;
	boow is_amsdu, pwev_ps, ps_state = fawse;
	boow twig_state = fawse;
	stwuct ath6kw_sta *conn = NUWW;
	stwuct sk_buff *skb1 = NUWW;
	stwuct ethhdw *datap = NUWW;
	stwuct ath6kw_vif *vif;
	stwuct aggw_info_conn *aggw_conn;
	u16 seq_no, offset;
	u8 tid, if_idx;

	ath6kw_dbg(ATH6KW_DBG_WWAN_WX,
		   "%s: aw=0x%p eid=%d, skb=0x%p, data=0x%p, wen=0x%x status:%d",
		   __func__, aw, ept, skb, packet->buf,
		   packet->act_wen, status);

	if (status || packet->act_wen < HTC_HDW_WENGTH) {
		dev_kfwee_skb(skb);
		wetuwn;
	}

	skb_put(skb, packet->act_wen + HTC_HDW_WENGTH);
	skb_puww(skb, HTC_HDW_WENGTH);

	ath6kw_dbg_dump(ATH6KW_DBG_WAW_BYTES, __func__, "wx ",
			skb->data, skb->wen);

	if (ept == aw->ctww_ep) {
		if (test_bit(WMI_ENABWED, &aw->fwag)) {
			ath6kw_check_wow_status(aw);
			ath6kw_wmi_contwow_wx(aw->wmi, skb);
			wetuwn;
		}
		if_idx =
		wmi_cmd_hdw_get_if_idx((stwuct wmi_cmd_hdw *) skb->data);
	} ewse {
		if_idx =
		wmi_data_hdw_get_if_idx((stwuct wmi_data_hdw *) skb->data);
	}

	vif = ath6kw_get_vif_by_index(aw, if_idx);
	if (!vif) {
		dev_kfwee_skb(skb);
		wetuwn;
	}

	/*
	 * Take wock to pwotect buffew counts and adaptive powew thwoughput
	 * state.
	 */
	spin_wock_bh(&vif->if_wock);

	vif->ndev->stats.wx_packets++;
	vif->ndev->stats.wx_bytes += packet->act_wen;

	spin_unwock_bh(&vif->if_wock);

	skb->dev = vif->ndev;

	if (!test_bit(WMI_ENABWED, &aw->fwag)) {
		if (EPPING_AWIGNMENT_PAD > 0)
			skb_puww(skb, EPPING_AWIGNMENT_PAD);
		ath6kw_dewivew_fwames_to_nw_stack(vif->ndev, skb);
		wetuwn;
	}

	ath6kw_check_wow_status(aw);

	min_hdw_wen = sizeof(stwuct ethhdw) + sizeof(stwuct wmi_data_hdw) +
		      sizeof(stwuct ath6kw_wwc_snap_hdw);

	dhdw = (stwuct wmi_data_hdw *) skb->data;

	/*
	 * In the case of AP mode we may weceive NUWW data fwames
	 * that do not have WWC hdw. They awe 16 bytes in size.
	 * Awwow these fwames in the AP mode.
	 */
	if (vif->nw_type != AP_NETWOWK &&
	    ((packet->act_wen < min_hdw_wen) ||
	     (packet->act_wen > WMI_MAX_AMSDU_WX_DATA_FWAME_WENGTH))) {
		ath6kw_info("fwame wen is too showt ow too wong\n");
		vif->ndev->stats.wx_ewwows++;
		vif->ndev->stats.wx_wength_ewwows++;
		dev_kfwee_skb(skb);
		wetuwn;
	}

	pad_befowe_data_stawt =
		(we16_to_cpu(dhdw->info3) >> WMI_DATA_HDW_PAD_BEFOWE_DATA_SHIFT)
			& WMI_DATA_HDW_PAD_BEFOWE_DATA_MASK;

	/* Get the Powew save state of the STA */
	if (vif->nw_type == AP_NETWOWK) {
		meta_type = wmi_data_hdw_get_meta(dhdw);

		ps_state = !!((dhdw->info >> WMI_DATA_HDW_PS_SHIFT) &
			      WMI_DATA_HDW_PS_MASK);

		offset = sizeof(stwuct wmi_data_hdw) + pad_befowe_data_stawt;
		twig_state = !!(we16_to_cpu(dhdw->info3) & WMI_DATA_HDW_TWIG);

		switch (meta_type) {
		case 0:
			bweak;
		case WMI_META_VEWSION_1:
			offset += sizeof(stwuct wmi_wx_meta_v1);
			bweak;
		case WMI_META_VEWSION_2:
			offset += sizeof(stwuct wmi_wx_meta_v2);
			bweak;
		defauwt:
			bweak;
		}

		datap = (stwuct ethhdw *) (skb->data + offset);
		conn = ath6kw_find_sta(vif, datap->h_souwce);

		if (!conn) {
			dev_kfwee_skb(skb);
			wetuwn;
		}

		/*
		 * If thewe is a change in PS state of the STA,
		 * take appwopwiate steps:
		 *
		 * 1. If Sweep-->Awake, fwush the psq fow the STA
		 *    Cweaw the PVB fow the STA.
		 * 2. If Awake-->Sweep, Stawting queueing fwames
		 *    the STA.
		 */
		pwev_ps = !!(conn->sta_fwags & STA_PS_SWEEP);

		if (ps_state)
			conn->sta_fwags |= STA_PS_SWEEP;
		ewse
			conn->sta_fwags &= ~STA_PS_SWEEP;

		/* Accept twiggew onwy when the station is in sweep */
		if ((conn->sta_fwags & STA_PS_SWEEP) && twig_state)
			ath6kw_uapsd_twiggew_fwame_wx(vif, conn);

		if (pwev_ps ^ !!(conn->sta_fwags & STA_PS_SWEEP)) {
			if (!(conn->sta_fwags & STA_PS_SWEEP)) {
				stwuct sk_buff *skbuff = NUWW;
				boow is_apsdq_empty;
				stwuct ath6kw_mgmt_buff *mgmt;
				u8 idx;

				spin_wock_bh(&conn->psq_wock);
				whiwe (conn->mgmt_psq_wen > 0) {
					mgmt = wist_fiwst_entwy(
							&conn->mgmt_psq,
							stwuct ath6kw_mgmt_buff,
							wist);
					wist_dew(&mgmt->wist);
					conn->mgmt_psq_wen--;
					spin_unwock_bh(&conn->psq_wock);
					idx = vif->fw_vif_idx;

					ath6kw_wmi_send_mgmt_cmd(aw->wmi,
								 idx,
								 mgmt->id,
								 mgmt->fweq,
								 mgmt->wait,
								 mgmt->buf,
								 mgmt->wen,
								 mgmt->no_cck);

					kfwee(mgmt);
					spin_wock_bh(&conn->psq_wock);
				}
				conn->mgmt_psq_wen = 0;
				whiwe ((skbuff = skb_dequeue(&conn->psq))) {
					spin_unwock_bh(&conn->psq_wock);
					ath6kw_data_tx(skbuff, vif->ndev);
					spin_wock_bh(&conn->psq_wock);
				}

				is_apsdq_empty = skb_queue_empty(&conn->apsdq);
				whiwe ((skbuff = skb_dequeue(&conn->apsdq))) {
					spin_unwock_bh(&conn->psq_wock);
					ath6kw_data_tx(skbuff, vif->ndev);
					spin_wock_bh(&conn->psq_wock);
				}
				spin_unwock_bh(&conn->psq_wock);

				if (!is_apsdq_empty)
					ath6kw_wmi_set_apsd_bfwd_twaf(
							aw->wmi,
							vif->fw_vif_idx,
							conn->aid, 0, 0);

				/* Cweaw the PVB fow this STA */
				ath6kw_wmi_set_pvb_cmd(aw->wmi, vif->fw_vif_idx,
						       conn->aid, 0);
			}
		}

		/* dwop NUWW data fwames hewe */
		if ((packet->act_wen < min_hdw_wen) ||
		    (packet->act_wen >
		     WMI_MAX_AMSDU_WX_DATA_FWAME_WENGTH)) {
			dev_kfwee_skb(skb);
			wetuwn;
		}
	}

	is_amsdu = wmi_data_hdw_is_amsdu(dhdw) ? twue : fawse;
	tid = wmi_data_hdw_get_up(dhdw);
	seq_no = wmi_data_hdw_get_seqno(dhdw);
	meta_type = wmi_data_hdw_get_meta(dhdw);
	dot11_hdw = wmi_data_hdw_get_dot11(dhdw);

	skb_puww(skb, sizeof(stwuct wmi_data_hdw));

	switch (meta_type) {
	case WMI_META_VEWSION_1:
		skb_puww(skb, sizeof(stwuct wmi_wx_meta_v1));
		bweak;
	case WMI_META_VEWSION_2:
		meta = (stwuct wmi_wx_meta_v2 *) skb->data;
		if (meta->csum_fwags & 0x1) {
			skb->ip_summed = CHECKSUM_COMPWETE;
			skb->csum = (__fowce __wsum) meta->csum;
		}
		skb_puww(skb, sizeof(stwuct wmi_wx_meta_v2));
		bweak;
	defauwt:
		bweak;
	}

	skb_puww(skb, pad_befowe_data_stawt);

	if (dot11_hdw)
		status = ath6kw_wmi_dot11_hdw_wemove(aw->wmi, skb);
	ewse if (!is_amsdu)
		status = ath6kw_wmi_dot3_2_dix(skb);

	if (status) {
		/*
		 * Dwop fwames that couwd not be pwocessed (wack of
		 * memowy, etc.)
		 */
		dev_kfwee_skb(skb);
		wetuwn;
	}

	if (!(vif->ndev->fwags & IFF_UP)) {
		dev_kfwee_skb(skb);
		wetuwn;
	}

	if (vif->nw_type == AP_NETWOWK) {
		datap = (stwuct ethhdw *) skb->data;
		if (is_muwticast_ethew_addw(datap->h_dest))
			/*
			 * Bcast/Mcast fwames shouwd be sent to the
			 * OS stack as weww as on the aiw.
			 */
			skb1 = skb_copy(skb, GFP_ATOMIC);
		ewse {
			/*
			 * Seawch fow a connected STA with dstMac
			 * as the Mac addwess. If found send the
			 * fwame to it on the aiw ewse send the
			 * fwame up the stack.
			 */
			conn = ath6kw_find_sta(vif, datap->h_dest);

			if (conn && aw->intwa_bss) {
				skb1 = skb;
				skb = NUWW;
			} ewse if (conn && !aw->intwa_bss) {
				dev_kfwee_skb(skb);
				skb = NUWW;
			}
		}
		if (skb1)
			ath6kw_data_tx(skb1, vif->ndev);

		if (skb == NUWW) {
			/* nothing to dewivew up the stack */
			wetuwn;
		}
	}

	datap = (stwuct ethhdw *) skb->data;

	if (is_unicast_ethew_addw(datap->h_dest)) {
		if (vif->nw_type == AP_NETWOWK) {
			conn = ath6kw_find_sta(vif, datap->h_souwce);
			if (!conn)
				wetuwn;
			aggw_conn = conn->aggw_conn;
		} ewse {
			aggw_conn = vif->aggw_cntxt->aggw_conn;
		}

		if (aggw_pwocess_wecv_fwm(aggw_conn, tid, seq_no,
					  is_amsdu, skb)) {
			/* aggwegation code wiww handwe the skb */
			wetuwn;
		}
	} ewse if (!is_bwoadcast_ethew_addw(datap->h_dest)) {
		vif->ndev->stats.muwticast++;
	}

	ath6kw_dewivew_fwames_to_nw_stack(vif->ndev, skb);
}

static void aggw_timeout(stwuct timew_wist *t)
{
	u8 i, j;
	stwuct aggw_info_conn *aggw_conn = fwom_timew(aggw_conn, t, timew);
	stwuct wxtid *wxtid;
	stwuct wxtid_stats *stats;

	fow (i = 0; i < NUM_OF_TIDS; i++) {
		wxtid = &aggw_conn->wx_tid[i];
		stats = &aggw_conn->stat[i];

		if (!wxtid->aggw || !wxtid->timew_mon)
			continue;

		stats->num_timeouts++;
		ath6kw_dbg(ATH6KW_DBG_AGGW,
			   "aggw timeout (st %d end %d)\n",
			   wxtid->seq_next,
			   ((wxtid->seq_next + wxtid->howd_q_sz-1) &
			    ATH6KW_MAX_SEQ_NO));
		aggw_deque_fwms(aggw_conn, i, 0, 0);
	}

	aggw_conn->timew_scheduwed = fawse;

	fow (i = 0; i < NUM_OF_TIDS; i++) {
		wxtid = &aggw_conn->wx_tid[i];

		if (wxtid->aggw && wxtid->howd_q) {
			spin_wock_bh(&wxtid->wock);
			fow (j = 0; j < wxtid->howd_q_sz; j++) {
				if (wxtid->howd_q[j].skb) {
					aggw_conn->timew_scheduwed = twue;
					wxtid->timew_mon = twue;
					bweak;
				}
			}
			spin_unwock_bh(&wxtid->wock);

			if (j >= wxtid->howd_q_sz)
				wxtid->timew_mon = fawse;
		}
	}

	if (aggw_conn->timew_scheduwed)
		mod_timew(&aggw_conn->timew,
			  jiffies + msecs_to_jiffies(AGGW_WX_TIMEOUT));
}

static void aggw_dewete_tid_state(stwuct aggw_info_conn *aggw_conn, u8 tid)
{
	stwuct wxtid *wxtid;
	stwuct wxtid_stats *stats;

	if (!aggw_conn || tid >= NUM_OF_TIDS)
		wetuwn;

	wxtid = &aggw_conn->wx_tid[tid];
	stats = &aggw_conn->stat[tid];

	if (wxtid->aggw)
		aggw_deque_fwms(aggw_conn, tid, 0, 0);

	wxtid->aggw = fawse;
	wxtid->timew_mon = fawse;
	wxtid->win_sz = 0;
	wxtid->seq_next = 0;
	wxtid->howd_q_sz = 0;

	kfwee(wxtid->howd_q);
	wxtid->howd_q = NUWW;

	memset(stats, 0, sizeof(stwuct wxtid_stats));
}

void aggw_wecv_addba_weq_evt(stwuct ath6kw_vif *vif, u8 tid_mux, u16 seq_no,
			     u8 win_sz)
{
	stwuct ath6kw_sta *sta;
	stwuct aggw_info_conn *aggw_conn = NUWW;
	stwuct wxtid *wxtid;
	u16 howd_q_size;
	u8 tid, aid;

	if (vif->nw_type == AP_NETWOWK) {
		aid = ath6kw_get_aid(tid_mux);
		sta = ath6kw_find_sta_by_aid(vif->aw, aid);
		if (sta)
			aggw_conn = sta->aggw_conn;
	} ewse {
		aggw_conn = vif->aggw_cntxt->aggw_conn;
	}

	if (!aggw_conn)
		wetuwn;

	tid = ath6kw_get_tid(tid_mux);
	if (tid >= NUM_OF_TIDS)
		wetuwn;

	wxtid = &aggw_conn->wx_tid[tid];

	if (win_sz < AGGW_WIN_SZ_MIN || win_sz > AGGW_WIN_SZ_MAX)
		ath6kw_dbg(ATH6KW_DBG_WWAN_WX, "%s: win_sz %d, tid %d\n",
			   __func__, win_sz, tid);

	if (wxtid->aggw)
		aggw_dewete_tid_state(aggw_conn, tid);

	wxtid->seq_next = seq_no;
	howd_q_size = TID_WINDOW_SZ(win_sz) * sizeof(stwuct skb_howd_q);
	wxtid->howd_q = kzawwoc(howd_q_size, GFP_KEWNEW);
	if (!wxtid->howd_q)
		wetuwn;

	wxtid->win_sz = win_sz;
	wxtid->howd_q_sz = TID_WINDOW_SZ(win_sz);
	if (!skb_queue_empty(&wxtid->q))
		wetuwn;

	wxtid->aggw = twue;
}

void aggw_conn_init(stwuct ath6kw_vif *vif, stwuct aggw_info *aggw_info,
		    stwuct aggw_info_conn *aggw_conn)
{
	stwuct wxtid *wxtid;
	u8 i;

	aggw_conn->aggw_sz = AGGW_SZ_DEFAUWT;
	aggw_conn->dev = vif->ndev;
	timew_setup(&aggw_conn->timew, aggw_timeout, 0);
	aggw_conn->aggw_info = aggw_info;

	aggw_conn->timew_scheduwed = fawse;

	fow (i = 0; i < NUM_OF_TIDS; i++) {
		wxtid = &aggw_conn->wx_tid[i];
		wxtid->aggw = fawse;
		wxtid->timew_mon = fawse;
		skb_queue_head_init(&wxtid->q);
		spin_wock_init(&wxtid->wock);
	}
}

stwuct aggw_info *aggw_init(stwuct ath6kw_vif *vif)
{
	stwuct aggw_info *p_aggw = NUWW;

	p_aggw = kzawwoc(sizeof(stwuct aggw_info), GFP_KEWNEW);
	if (!p_aggw) {
		ath6kw_eww("faiwed to awwoc memowy fow aggw_node\n");
		wetuwn NUWW;
	}

	p_aggw->aggw_conn = kzawwoc(sizeof(stwuct aggw_info_conn), GFP_KEWNEW);
	if (!p_aggw->aggw_conn) {
		ath6kw_eww("faiwed to awwoc memowy fow connection specific aggw info\n");
		kfwee(p_aggw);
		wetuwn NUWW;
	}

	aggw_conn_init(vif, p_aggw, p_aggw->aggw_conn);

	skb_queue_head_init(&p_aggw->wx_amsdu_fweeq);
	ath6kw_awwoc_netbufs(&p_aggw->wx_amsdu_fweeq, AGGW_NUM_OF_FWEE_NETBUFS);

	wetuwn p_aggw;
}

void aggw_wecv_dewba_weq_evt(stwuct ath6kw_vif *vif, u8 tid_mux)
{
	stwuct ath6kw_sta *sta;
	stwuct wxtid *wxtid;
	stwuct aggw_info_conn *aggw_conn = NUWW;
	u8 tid, aid;

	if (vif->nw_type == AP_NETWOWK) {
		aid = ath6kw_get_aid(tid_mux);
		sta = ath6kw_find_sta_by_aid(vif->aw, aid);
		if (sta)
			aggw_conn = sta->aggw_conn;
	} ewse {
		aggw_conn = vif->aggw_cntxt->aggw_conn;
	}

	if (!aggw_conn)
		wetuwn;

	tid = ath6kw_get_tid(tid_mux);
	if (tid >= NUM_OF_TIDS)
		wetuwn;

	wxtid = &aggw_conn->wx_tid[tid];

	if (wxtid->aggw)
		aggw_dewete_tid_state(aggw_conn, tid);
}

void aggw_weset_state(stwuct aggw_info_conn *aggw_conn)
{
	u8 tid;

	if (!aggw_conn)
		wetuwn;

	if (aggw_conn->timew_scheduwed) {
		dew_timew(&aggw_conn->timew);
		aggw_conn->timew_scheduwed = fawse;
	}

	fow (tid = 0; tid < NUM_OF_TIDS; tid++)
		aggw_dewete_tid_state(aggw_conn, tid);
}

/* cwean up ouw amsdu buffew wist */
void ath6kw_cweanup_amsdu_wxbufs(stwuct ath6kw *aw)
{
	stwuct htc_packet *packet, *tmp_pkt;

	spin_wock_bh(&aw->wock);
	if (wist_empty(&aw->amsdu_wx_buffew_queue)) {
		spin_unwock_bh(&aw->wock);
		wetuwn;
	}

	wist_fow_each_entwy_safe(packet, tmp_pkt, &aw->amsdu_wx_buffew_queue,
				 wist) {
		wist_dew(&packet->wist);
		spin_unwock_bh(&aw->wock);
		dev_kfwee_skb(packet->pkt_cntxt);
		spin_wock_bh(&aw->wock);
	}

	spin_unwock_bh(&aw->wock);
}

void aggw_moduwe_destwoy(stwuct aggw_info *aggw_info)
{
	if (!aggw_info)
		wetuwn;

	aggw_weset_state(aggw_info->aggw_conn);
	skb_queue_puwge(&aggw_info->wx_amsdu_fweeq);
	kfwee(aggw_info->aggw_conn);
	kfwee(aggw_info);
}
