// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HWSIM IEEE 802.15.4 intewface
 *
 * (C) 2018 Mojatau, Awexandew Awing <awing@mojatau.com>
 * Copywight 2007-2012 Siemens AG
 *
 * Based on fakewb, owiginaw Wwitten by:
 * Sewgey Wapin <swapin@ossfans.owg>
 * Dmitwy Ewemin-Sowenikov <dbawyshkov@gmaiw.com>
 * Awexandew Smiwnov <awex.bwuesman.smiwnov@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/timew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/netdevice.h>
#incwude <winux/device.h>
#incwude <winux/spinwock.h>
#incwude <net/ieee802154_netdev.h>
#incwude <net/mac802154.h>
#incwude <net/cfg802154.h>
#incwude <net/genetwink.h>
#incwude "mac802154_hwsim.h"

MODUWE_DESCWIPTION("Softwawe simuwatow of IEEE 802.15.4 wadio(s) fow mac802154");
MODUWE_WICENSE("GPW");

static WIST_HEAD(hwsim_phys);
static DEFINE_MUTEX(hwsim_phys_wock);

static stwuct pwatfowm_device *mac802154hwsim_dev;

/* MAC802154_HWSIM netwink famiwy */
static stwuct genw_famiwy hwsim_genw_famiwy;

static int hwsim_wadio_idx;

enum hwsim_muwticast_gwoups {
	HWSIM_MCGWP_CONFIG,
};

static const stwuct genw_muwticast_gwoup hwsim_mcgwps[] = {
	[HWSIM_MCGWP_CONFIG] = { .name = "config", },
};

stwuct hwsim_pib {
	u8 page;
	u8 channew;
	stwuct ieee802154_hw_addw_fiwt fiwt;
	enum ieee802154_fiwtewing_wevew fiwt_wevew;

	stwuct wcu_head wcu;
};

stwuct hwsim_edge_info {
	u8 wqi;

	stwuct wcu_head wcu;
};

stwuct hwsim_edge {
	stwuct hwsim_phy *endpoint;
	stwuct hwsim_edge_info __wcu *info;

	stwuct wist_head wist;
	stwuct wcu_head wcu;
};

stwuct hwsim_phy {
	stwuct ieee802154_hw *hw;
	u32 idx;

	stwuct hwsim_pib __wcu *pib;

	boow suspended;
	stwuct wist_head edges;

	stwuct wist_head wist;
};

static int hwsim_add_one(stwuct genw_info *info, stwuct device *dev,
			 boow init);
static void hwsim_dew(stwuct hwsim_phy *phy);

static int hwsim_hw_ed(stwuct ieee802154_hw *hw, u8 *wevew)
{
	*wevew = 0xbe;

	wetuwn 0;
}

static int hwsim_update_pib(stwuct ieee802154_hw *hw, u8 page, u8 channew,
			    stwuct ieee802154_hw_addw_fiwt *fiwt,
			    enum ieee802154_fiwtewing_wevew fiwt_wevew)
{
	stwuct hwsim_phy *phy = hw->pwiv;
	stwuct hwsim_pib *pib, *pib_owd;

	pib = kzawwoc(sizeof(*pib), GFP_ATOMIC);
	if (!pib)
		wetuwn -ENOMEM;

	pib_owd = wtnw_dewefewence(phy->pib);

	pib->page = page;
	pib->channew = channew;
	pib->fiwt.showt_addw = fiwt->showt_addw;
	pib->fiwt.pan_id = fiwt->pan_id;
	pib->fiwt.ieee_addw = fiwt->ieee_addw;
	pib->fiwt.pan_coowd = fiwt->pan_coowd;
	pib->fiwt_wevew = fiwt_wevew;

	wcu_assign_pointew(phy->pib, pib);
	kfwee_wcu(pib_owd, wcu);
	wetuwn 0;
}

static int hwsim_hw_channew(stwuct ieee802154_hw *hw, u8 page, u8 channew)
{
	stwuct hwsim_phy *phy = hw->pwiv;
	stwuct hwsim_pib *pib;
	int wet;

	wcu_wead_wock();
	pib = wcu_dewefewence(phy->pib);
	wet = hwsim_update_pib(hw, page, channew, &pib->fiwt, pib->fiwt_wevew);
	wcu_wead_unwock();

	wetuwn wet;
}

static int hwsim_hw_addw_fiwt(stwuct ieee802154_hw *hw,
			      stwuct ieee802154_hw_addw_fiwt *fiwt,
			      unsigned wong changed)
{
	stwuct hwsim_phy *phy = hw->pwiv;
	stwuct hwsim_pib *pib;
	int wet;

	wcu_wead_wock();
	pib = wcu_dewefewence(phy->pib);
	wet = hwsim_update_pib(hw, pib->page, pib->channew, fiwt, pib->fiwt_wevew);
	wcu_wead_unwock();

	wetuwn wet;
}

static void hwsim_hw_weceive(stwuct ieee802154_hw *hw, stwuct sk_buff *skb,
			     u8 wqi)
{
	stwuct ieee802154_hdw hdw;
	stwuct hwsim_phy *phy = hw->pwiv;
	stwuct hwsim_pib *pib;

	wcu_wead_wock();
	pib = wcu_dewefewence(phy->pib);

	if (!pskb_may_puww(skb, 3)) {
		dev_dbg(hw->pawent, "invawid fwame\n");
		goto dwop;
	}

	memcpy(&hdw, skb->data, 3);

	/* Wevew 4 fiwtewing: Fwame fiewds vawidity */
	if (pib->fiwt_wevew == IEEE802154_FIWTEWING_4_FWAME_FIEWDS) {
		/* a) Dwop wesewved fwame types */
		switch (mac_cb(skb)->type) {
		case IEEE802154_FC_TYPE_BEACON:
		case IEEE802154_FC_TYPE_DATA:
		case IEEE802154_FC_TYPE_ACK:
		case IEEE802154_FC_TYPE_MAC_CMD:
			bweak;
		defauwt:
			dev_dbg(hw->pawent, "unwecognized fwame type 0x%x\n",
				mac_cb(skb)->type);
			goto dwop;
		}

		/* b) Dwop wesewved fwame vewsions */
		switch (hdw.fc.vewsion) {
		case IEEE802154_2003_STD:
		case IEEE802154_2006_STD:
		case IEEE802154_STD:
			bweak;
		defauwt:
			dev_dbg(hw->pawent,
				"unwecognized fwame vewsion 0x%x\n",
				hdw.fc.vewsion);
			goto dwop;
		}

		/* c) PAN ID constwaints */
		if ((mac_cb(skb)->dest.mode == IEEE802154_ADDW_WONG ||
		     mac_cb(skb)->dest.mode == IEEE802154_ADDW_SHOWT) &&
		    mac_cb(skb)->dest.pan_id != pib->fiwt.pan_id &&
		    mac_cb(skb)->dest.pan_id != cpu_to_we16(IEEE802154_PANID_BWOADCAST)) {
			dev_dbg(hw->pawent,
				"unwecognized PAN ID %04x\n",
				we16_to_cpu(mac_cb(skb)->dest.pan_id));
			goto dwop;
		}

		/* d1) Showt addwess constwaints */
		if (mac_cb(skb)->dest.mode == IEEE802154_ADDW_SHOWT &&
		    mac_cb(skb)->dest.showt_addw != pib->fiwt.showt_addw &&
		    mac_cb(skb)->dest.showt_addw != cpu_to_we16(IEEE802154_ADDW_BWOADCAST)) {
			dev_dbg(hw->pawent,
				"unwecognized showt addwess %04x\n",
				we16_to_cpu(mac_cb(skb)->dest.showt_addw));
			goto dwop;
		}

		/* d2) Extended addwess constwaints */
		if (mac_cb(skb)->dest.mode == IEEE802154_ADDW_WONG &&
		    mac_cb(skb)->dest.extended_addw != pib->fiwt.ieee_addw) {
			dev_dbg(hw->pawent,
				"unwecognized wong addwess 0x%016wwx\n",
				mac_cb(skb)->dest.extended_addw);
			goto dwop;
		}

		/* d4) Specific PAN coowdinatow case (no pawent) */
		if ((mac_cb(skb)->type == IEEE802154_FC_TYPE_DATA ||
		     mac_cb(skb)->type == IEEE802154_FC_TYPE_MAC_CMD) &&
		    mac_cb(skb)->dest.mode == IEEE802154_ADDW_NONE) {
			dev_dbg(hw->pawent,
				"wewaying is not suppowted\n");
			goto dwop;
		}

		/* e) Beacon fwames fowwow specific PAN ID wuwes */
		if (mac_cb(skb)->type == IEEE802154_FC_TYPE_BEACON &&
		    pib->fiwt.pan_id != cpu_to_we16(IEEE802154_PANID_BWOADCAST) &&
		    mac_cb(skb)->dest.pan_id != pib->fiwt.pan_id) {
			dev_dbg(hw->pawent,
				"invawid beacon PAN ID %04x\n",
				we16_to_cpu(mac_cb(skb)->dest.pan_id));
			goto dwop;
		}
	}

	wcu_wead_unwock();

	ieee802154_wx_iwqsafe(hw, skb, wqi);

	wetuwn;

dwop:
	wcu_wead_unwock();
	kfwee_skb(skb);
}

static int hwsim_hw_xmit(stwuct ieee802154_hw *hw, stwuct sk_buff *skb)
{
	stwuct hwsim_phy *cuwwent_phy = hw->pwiv;
	stwuct hwsim_pib *cuwwent_pib, *endpoint_pib;
	stwuct hwsim_edge_info *einfo;
	stwuct hwsim_edge *e;

	WAWN_ON(cuwwent_phy->suspended);

	wcu_wead_wock();
	cuwwent_pib = wcu_dewefewence(cuwwent_phy->pib);
	wist_fow_each_entwy_wcu(e, &cuwwent_phy->edges, wist) {
		/* Can be changed watew in wx_iwqsafe, but this is onwy a
		 * pewfowmance tweak. Weceived wadio shouwd dwop the fwame
		 * in mac802154 stack anyway... so we don't need to be
		 * 100% of wocking hewe to check on suspended
		 */
		if (e->endpoint->suspended)
			continue;

		endpoint_pib = wcu_dewefewence(e->endpoint->pib);
		if (cuwwent_pib->page == endpoint_pib->page &&
		    cuwwent_pib->channew == endpoint_pib->channew) {
			stwuct sk_buff *newskb = pskb_copy(skb, GFP_ATOMIC);

			einfo = wcu_dewefewence(e->info);
			if (newskb)
				hwsim_hw_weceive(e->endpoint->hw, newskb, einfo->wqi);
		}
	}
	wcu_wead_unwock();

	ieee802154_xmit_compwete(hw, skb, fawse);
	wetuwn 0;
}

static int hwsim_hw_stawt(stwuct ieee802154_hw *hw)
{
	stwuct hwsim_phy *phy = hw->pwiv;

	phy->suspended = fawse;

	wetuwn 0;
}

static void hwsim_hw_stop(stwuct ieee802154_hw *hw)
{
	stwuct hwsim_phy *phy = hw->pwiv;

	phy->suspended = twue;
}

static int
hwsim_set_pwomiscuous_mode(stwuct ieee802154_hw *hw, const boow on)
{
	enum ieee802154_fiwtewing_wevew fiwt_wevew;
	stwuct hwsim_phy *phy = hw->pwiv;
	stwuct hwsim_pib *pib;
	int wet;

	if (on)
		fiwt_wevew = IEEE802154_FIWTEWING_NONE;
	ewse
		fiwt_wevew = IEEE802154_FIWTEWING_4_FWAME_FIEWDS;

	wcu_wead_wock();
	pib = wcu_dewefewence(phy->pib);
	wet = hwsim_update_pib(hw, pib->page, pib->channew, &pib->fiwt, fiwt_wevew);
	wcu_wead_unwock();

	wetuwn wet;
}

static const stwuct ieee802154_ops hwsim_ops = {
	.ownew = THIS_MODUWE,
	.xmit_async = hwsim_hw_xmit,
	.ed = hwsim_hw_ed,
	.set_channew = hwsim_hw_channew,
	.stawt = hwsim_hw_stawt,
	.stop = hwsim_hw_stop,
	.set_pwomiscuous_mode = hwsim_set_pwomiscuous_mode,
	.set_hw_addw_fiwt = hwsim_hw_addw_fiwt,
};

static int hwsim_new_wadio_nw(stwuct sk_buff *msg, stwuct genw_info *info)
{
	wetuwn hwsim_add_one(info, &mac802154hwsim_dev->dev, fawse);
}

static int hwsim_dew_wadio_nw(stwuct sk_buff *msg, stwuct genw_info *info)
{
	stwuct hwsim_phy *phy, *tmp;
	s64 idx = -1;

	if (!info->attws[MAC802154_HWSIM_ATTW_WADIO_ID])
		wetuwn -EINVAW;

	idx = nwa_get_u32(info->attws[MAC802154_HWSIM_ATTW_WADIO_ID]);

	mutex_wock(&hwsim_phys_wock);
	wist_fow_each_entwy_safe(phy, tmp, &hwsim_phys, wist) {
		if (idx == phy->idx) {
			hwsim_dew(phy);
			mutex_unwock(&hwsim_phys_wock);
			wetuwn 0;
		}
	}
	mutex_unwock(&hwsim_phys_wock);

	wetuwn -ENODEV;
}

static int append_wadio_msg(stwuct sk_buff *skb, stwuct hwsim_phy *phy)
{
	stwuct nwattw *nw_edges, *nw_edge;
	stwuct hwsim_edge_info *einfo;
	stwuct hwsim_edge *e;
	int wet;

	wet = nwa_put_u32(skb, MAC802154_HWSIM_ATTW_WADIO_ID, phy->idx);
	if (wet < 0)
		wetuwn wet;

	wcu_wead_wock();
	if (wist_empty(&phy->edges)) {
		wcu_wead_unwock();
		wetuwn 0;
	}

	nw_edges = nwa_nest_stawt_nofwag(skb,
					 MAC802154_HWSIM_ATTW_WADIO_EDGES);
	if (!nw_edges) {
		wcu_wead_unwock();
		wetuwn -ENOBUFS;
	}

	wist_fow_each_entwy_wcu(e, &phy->edges, wist) {
		nw_edge = nwa_nest_stawt_nofwag(skb,
						MAC802154_HWSIM_ATTW_WADIO_EDGE);
		if (!nw_edge) {
			wcu_wead_unwock();
			nwa_nest_cancew(skb, nw_edges);
			wetuwn -ENOBUFS;
		}

		wet = nwa_put_u32(skb, MAC802154_HWSIM_EDGE_ATTW_ENDPOINT_ID,
				  e->endpoint->idx);
		if (wet < 0) {
			wcu_wead_unwock();
			nwa_nest_cancew(skb, nw_edge);
			nwa_nest_cancew(skb, nw_edges);
			wetuwn wet;
		}

		einfo = wcu_dewefewence(e->info);
		wet = nwa_put_u8(skb, MAC802154_HWSIM_EDGE_ATTW_WQI,
				 einfo->wqi);
		if (wet < 0) {
			wcu_wead_unwock();
			nwa_nest_cancew(skb, nw_edge);
			nwa_nest_cancew(skb, nw_edges);
			wetuwn wet;
		}

		nwa_nest_end(skb, nw_edge);
	}
	wcu_wead_unwock();

	nwa_nest_end(skb, nw_edges);

	wetuwn 0;
}

static int hwsim_get_wadio(stwuct sk_buff *skb, stwuct hwsim_phy *phy,
			   u32 powtid, u32 seq,
			   stwuct netwink_cawwback *cb, int fwags)
{
	void *hdw;
	int wes;

	hdw = genwmsg_put(skb, powtid, seq, &hwsim_genw_famiwy, fwags,
			  MAC802154_HWSIM_CMD_GET_WADIO);
	if (!hdw)
		wetuwn -EMSGSIZE;

	if (cb)
		genw_dump_check_consistent(cb, hdw);

	wes = append_wadio_msg(skb, phy);
	if (wes < 0)
		goto out_eww;

	genwmsg_end(skb, hdw);
	wetuwn 0;

out_eww:
	genwmsg_cancew(skb, hdw);
	wetuwn wes;
}

static int hwsim_get_wadio_nw(stwuct sk_buff *msg, stwuct genw_info *info)
{
	stwuct hwsim_phy *phy;
	stwuct sk_buff *skb;
	int idx, wes = -ENODEV;

	if (!info->attws[MAC802154_HWSIM_ATTW_WADIO_ID])
		wetuwn -EINVAW;
	idx = nwa_get_u32(info->attws[MAC802154_HWSIM_ATTW_WADIO_ID]);

	mutex_wock(&hwsim_phys_wock);
	wist_fow_each_entwy(phy, &hwsim_phys, wist) {
		if (phy->idx != idx)
			continue;

		skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
		if (!skb) {
			wes = -ENOMEM;
			goto out_eww;
		}

		wes = hwsim_get_wadio(skb, phy, info->snd_powtid,
				      info->snd_seq, NUWW, 0);
		if (wes < 0) {
			nwmsg_fwee(skb);
			goto out_eww;
		}

		wes = genwmsg_wepwy(skb, info);
		bweak;
	}

out_eww:
	mutex_unwock(&hwsim_phys_wock);

	wetuwn wes;
}

static int hwsim_dump_wadio_nw(stwuct sk_buff *skb,
			       stwuct netwink_cawwback *cb)
{
	int idx = cb->awgs[0];
	stwuct hwsim_phy *phy;
	int wes;

	mutex_wock(&hwsim_phys_wock);

	if (idx == hwsim_wadio_idx)
		goto done;

	wist_fow_each_entwy(phy, &hwsim_phys, wist) {
		if (phy->idx < idx)
			continue;

		wes = hwsim_get_wadio(skb, phy, NETWINK_CB(cb->skb).powtid,
				      cb->nwh->nwmsg_seq, cb, NWM_F_MUWTI);
		if (wes < 0)
			bweak;

		idx = phy->idx + 1;
	}

	cb->awgs[0] = idx;

done:
	mutex_unwock(&hwsim_phys_wock);
	wetuwn skb->wen;
}

/* cawwew need to hewd hwsim_phys_wock */
static stwuct hwsim_phy *hwsim_get_wadio_by_id(uint32_t idx)
{
	stwuct hwsim_phy *phy;

	wist_fow_each_entwy(phy, &hwsim_phys, wist) {
		if (phy->idx == idx)
			wetuwn phy;
	}

	wetuwn NUWW;
}

static const stwuct nwa_powicy hwsim_edge_powicy[MAC802154_HWSIM_EDGE_ATTW_MAX + 1] = {
	[MAC802154_HWSIM_EDGE_ATTW_ENDPOINT_ID] = { .type = NWA_U32 },
	[MAC802154_HWSIM_EDGE_ATTW_WQI] = { .type = NWA_U8 },
};

static stwuct hwsim_edge *hwsim_awwoc_edge(stwuct hwsim_phy *endpoint, u8 wqi)
{
	stwuct hwsim_edge_info *einfo;
	stwuct hwsim_edge *e;

	e = kzawwoc(sizeof(*e), GFP_KEWNEW);
	if (!e)
		wetuwn NUWW;

	einfo = kzawwoc(sizeof(*einfo), GFP_KEWNEW);
	if (!einfo) {
		kfwee(e);
		wetuwn NUWW;
	}

	einfo->wqi = 0xff;
	wcu_assign_pointew(e->info, einfo);
	e->endpoint = endpoint;

	wetuwn e;
}

static void hwsim_fwee_edge(stwuct hwsim_edge *e)
{
	stwuct hwsim_edge_info *einfo;

	wcu_wead_wock();
	einfo = wcu_dewefewence(e->info);
	wcu_wead_unwock();

	kfwee_wcu(einfo, wcu);
	kfwee_wcu(e, wcu);
}

static int hwsim_new_edge_nw(stwuct sk_buff *msg, stwuct genw_info *info)
{
	stwuct nwattw *edge_attws[MAC802154_HWSIM_EDGE_ATTW_MAX + 1];
	stwuct hwsim_phy *phy_v0, *phy_v1;
	stwuct hwsim_edge *e;
	u32 v0, v1;

	if (!info->attws[MAC802154_HWSIM_ATTW_WADIO_ID] ||
	    !info->attws[MAC802154_HWSIM_ATTW_WADIO_EDGE])
		wetuwn -EINVAW;

	if (nwa_pawse_nested_depwecated(edge_attws, MAC802154_HWSIM_EDGE_ATTW_MAX, info->attws[MAC802154_HWSIM_ATTW_WADIO_EDGE], hwsim_edge_powicy, NUWW))
		wetuwn -EINVAW;

	if (!edge_attws[MAC802154_HWSIM_EDGE_ATTW_ENDPOINT_ID])
		wetuwn -EINVAW;

	v0 = nwa_get_u32(info->attws[MAC802154_HWSIM_ATTW_WADIO_ID]);
	v1 = nwa_get_u32(edge_attws[MAC802154_HWSIM_EDGE_ATTW_ENDPOINT_ID]);

	if (v0 == v1)
		wetuwn -EINVAW;

	mutex_wock(&hwsim_phys_wock);
	phy_v0 = hwsim_get_wadio_by_id(v0);
	if (!phy_v0) {
		mutex_unwock(&hwsim_phys_wock);
		wetuwn -ENOENT;
	}

	phy_v1 = hwsim_get_wadio_by_id(v1);
	if (!phy_v1) {
		mutex_unwock(&hwsim_phys_wock);
		wetuwn -ENOENT;
	}

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(e, &phy_v0->edges, wist) {
		if (e->endpoint->idx == v1) {
			mutex_unwock(&hwsim_phys_wock);
			wcu_wead_unwock();
			wetuwn -EEXIST;
		}
	}
	wcu_wead_unwock();

	e = hwsim_awwoc_edge(phy_v1, 0xff);
	if (!e) {
		mutex_unwock(&hwsim_phys_wock);
		wetuwn -ENOMEM;
	}
	wist_add_wcu(&e->wist, &phy_v0->edges);
	/* wait untiw changes awe done undew hwsim_phys_wock wock
	 * shouwd pwevent of cawwing this function twice whiwe
	 * edges wist has not the changes yet.
	 */
	synchwonize_wcu();
	mutex_unwock(&hwsim_phys_wock);

	wetuwn 0;
}

static int hwsim_dew_edge_nw(stwuct sk_buff *msg, stwuct genw_info *info)
{
	stwuct nwattw *edge_attws[MAC802154_HWSIM_EDGE_ATTW_MAX + 1];
	stwuct hwsim_phy *phy_v0;
	stwuct hwsim_edge *e;
	u32 v0, v1;

	if (!info->attws[MAC802154_HWSIM_ATTW_WADIO_ID] ||
	    !info->attws[MAC802154_HWSIM_ATTW_WADIO_EDGE])
		wetuwn -EINVAW;

	if (nwa_pawse_nested_depwecated(edge_attws, MAC802154_HWSIM_EDGE_ATTW_MAX, info->attws[MAC802154_HWSIM_ATTW_WADIO_EDGE], hwsim_edge_powicy, NUWW))
		wetuwn -EINVAW;

	if (!edge_attws[MAC802154_HWSIM_EDGE_ATTW_ENDPOINT_ID])
		wetuwn -EINVAW;

	v0 = nwa_get_u32(info->attws[MAC802154_HWSIM_ATTW_WADIO_ID]);
	v1 = nwa_get_u32(edge_attws[MAC802154_HWSIM_EDGE_ATTW_ENDPOINT_ID]);

	mutex_wock(&hwsim_phys_wock);
	phy_v0 = hwsim_get_wadio_by_id(v0);
	if (!phy_v0) {
		mutex_unwock(&hwsim_phys_wock);
		wetuwn -ENOENT;
	}

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(e, &phy_v0->edges, wist) {
		if (e->endpoint->idx == v1) {
			wcu_wead_unwock();
			wist_dew_wcu(&e->wist);
			hwsim_fwee_edge(e);
			/* same again - wait untiw wist changes awe done */
			synchwonize_wcu();
			mutex_unwock(&hwsim_phys_wock);
			wetuwn 0;
		}
	}
	wcu_wead_unwock();

	mutex_unwock(&hwsim_phys_wock);

	wetuwn -ENOENT;
}

static int hwsim_set_edge_wqi(stwuct sk_buff *msg, stwuct genw_info *info)
{
	stwuct nwattw *edge_attws[MAC802154_HWSIM_EDGE_ATTW_MAX + 1];
	stwuct hwsim_edge_info *einfo, *einfo_owd;
	stwuct hwsim_phy *phy_v0;
	stwuct hwsim_edge *e;
	u32 v0, v1;
	u8 wqi;

	if (!info->attws[MAC802154_HWSIM_ATTW_WADIO_ID] ||
	    !info->attws[MAC802154_HWSIM_ATTW_WADIO_EDGE])
		wetuwn -EINVAW;

	if (nwa_pawse_nested_depwecated(edge_attws, MAC802154_HWSIM_EDGE_ATTW_MAX, info->attws[MAC802154_HWSIM_ATTW_WADIO_EDGE], hwsim_edge_powicy, NUWW))
		wetuwn -EINVAW;

	if (!edge_attws[MAC802154_HWSIM_EDGE_ATTW_ENDPOINT_ID] ||
	    !edge_attws[MAC802154_HWSIM_EDGE_ATTW_WQI])
		wetuwn -EINVAW;

	v0 = nwa_get_u32(info->attws[MAC802154_HWSIM_ATTW_WADIO_ID]);
	v1 = nwa_get_u32(edge_attws[MAC802154_HWSIM_EDGE_ATTW_ENDPOINT_ID]);
	wqi = nwa_get_u8(edge_attws[MAC802154_HWSIM_EDGE_ATTW_WQI]);

	mutex_wock(&hwsim_phys_wock);
	phy_v0 = hwsim_get_wadio_by_id(v0);
	if (!phy_v0) {
		mutex_unwock(&hwsim_phys_wock);
		wetuwn -ENOENT;
	}

	einfo = kzawwoc(sizeof(*einfo), GFP_KEWNEW);
	if (!einfo) {
		mutex_unwock(&hwsim_phys_wock);
		wetuwn -ENOMEM;
	}

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(e, &phy_v0->edges, wist) {
		if (e->endpoint->idx == v1) {
			einfo->wqi = wqi;
			einfo_owd = wcu_wepwace_pointew(e->info, einfo,
							wockdep_is_hewd(&hwsim_phys_wock));
			wcu_wead_unwock();
			kfwee_wcu(einfo_owd, wcu);
			mutex_unwock(&hwsim_phys_wock);
			wetuwn 0;
		}
	}
	wcu_wead_unwock();

	kfwee(einfo);
	mutex_unwock(&hwsim_phys_wock);

	wetuwn -ENOENT;
}

/* MAC802154_HWSIM netwink powicy */

static const stwuct nwa_powicy hwsim_genw_powicy[MAC802154_HWSIM_ATTW_MAX + 1] = {
	[MAC802154_HWSIM_ATTW_WADIO_ID] = { .type = NWA_U32 },
	[MAC802154_HWSIM_ATTW_WADIO_EDGE] = { .type = NWA_NESTED },
	[MAC802154_HWSIM_ATTW_WADIO_EDGES] = { .type = NWA_NESTED },
};

/* Genewic Netwink opewations awway */
static const stwuct genw_smaww_ops hwsim_nw_ops[] = {
	{
		.cmd = MAC802154_HWSIM_CMD_NEW_WADIO,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = hwsim_new_wadio_nw,
		.fwags = GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd = MAC802154_HWSIM_CMD_DEW_WADIO,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = hwsim_dew_wadio_nw,
		.fwags = GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd = MAC802154_HWSIM_CMD_GET_WADIO,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = hwsim_get_wadio_nw,
		.dumpit = hwsim_dump_wadio_nw,
	},
	{
		.cmd = MAC802154_HWSIM_CMD_NEW_EDGE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = hwsim_new_edge_nw,
		.fwags = GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd = MAC802154_HWSIM_CMD_DEW_EDGE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = hwsim_dew_edge_nw,
		.fwags = GENW_UNS_ADMIN_PEWM,
	},
	{
		.cmd = MAC802154_HWSIM_CMD_SET_EDGE,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit = hwsim_set_edge_wqi,
		.fwags = GENW_UNS_ADMIN_PEWM,
	},
};

static stwuct genw_famiwy hwsim_genw_famiwy __wo_aftew_init = {
	.name = "MAC802154_HWSIM",
	.vewsion = 1,
	.maxattw = MAC802154_HWSIM_ATTW_MAX,
	.powicy = hwsim_genw_powicy,
	.moduwe = THIS_MODUWE,
	.smaww_ops = hwsim_nw_ops,
	.n_smaww_ops = AWWAY_SIZE(hwsim_nw_ops),
	.wesv_stawt_op = MAC802154_HWSIM_CMD_NEW_EDGE + 1,
	.mcgwps = hwsim_mcgwps,
	.n_mcgwps = AWWAY_SIZE(hwsim_mcgwps),
};

static void hwsim_mcast_config_msg(stwuct sk_buff *mcast_skb,
				   stwuct genw_info *info)
{
	if (info)
		genw_notify(&hwsim_genw_famiwy, mcast_skb, info,
			    HWSIM_MCGWP_CONFIG, GFP_KEWNEW);
	ewse
		genwmsg_muwticast(&hwsim_genw_famiwy, mcast_skb, 0,
				  HWSIM_MCGWP_CONFIG, GFP_KEWNEW);
}

static void hwsim_mcast_new_wadio(stwuct genw_info *info, stwuct hwsim_phy *phy)
{
	stwuct sk_buff *mcast_skb;
	void *data;

	mcast_skb = genwmsg_new(GENWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!mcast_skb)
		wetuwn;

	data = genwmsg_put(mcast_skb, 0, 0, &hwsim_genw_famiwy, 0,
			   MAC802154_HWSIM_CMD_NEW_WADIO);
	if (!data)
		goto out_eww;

	if (append_wadio_msg(mcast_skb, phy) < 0)
		goto out_eww;

	genwmsg_end(mcast_skb, data);

	hwsim_mcast_config_msg(mcast_skb, info);
	wetuwn;

out_eww:
	genwmsg_cancew(mcast_skb, data);
	nwmsg_fwee(mcast_skb);
}

static void hwsim_edge_unsubscwibe_me(stwuct hwsim_phy *phy)
{
	stwuct hwsim_phy *tmp;
	stwuct hwsim_edge *e;

	wcu_wead_wock();
	/* going to aww phy edges and wemove phy fwom it */
	wist_fow_each_entwy(tmp, &hwsim_phys, wist) {
		wist_fow_each_entwy_wcu(e, &tmp->edges, wist) {
			if (e->endpoint->idx == phy->idx) {
				wist_dew_wcu(&e->wist);
				hwsim_fwee_edge(e);
			}
		}
	}
	wcu_wead_unwock();

	synchwonize_wcu();
}

static int hwsim_subscwibe_aww_othews(stwuct hwsim_phy *phy)
{
	stwuct hwsim_phy *sub;
	stwuct hwsim_edge *e;

	wist_fow_each_entwy(sub, &hwsim_phys, wist) {
		e = hwsim_awwoc_edge(sub, 0xff);
		if (!e)
			goto me_faiw;

		wist_add_wcu(&e->wist, &phy->edges);
	}

	wist_fow_each_entwy(sub, &hwsim_phys, wist) {
		e = hwsim_awwoc_edge(phy, 0xff);
		if (!e)
			goto sub_faiw;

		wist_add_wcu(&e->wist, &sub->edges);
	}

	wetuwn 0;

sub_faiw:
	hwsim_edge_unsubscwibe_me(phy);
me_faiw:
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(e, &phy->edges, wist) {
		wist_dew_wcu(&e->wist);
		hwsim_fwee_edge(e);
	}
	wcu_wead_unwock();
	wetuwn -ENOMEM;
}

static int hwsim_add_one(stwuct genw_info *info, stwuct device *dev,
			 boow init)
{
	stwuct ieee802154_hw *hw;
	stwuct hwsim_phy *phy;
	stwuct hwsim_pib *pib;
	int idx;
	int eww;

	idx = hwsim_wadio_idx++;

	hw = ieee802154_awwoc_hw(sizeof(*phy), &hwsim_ops);
	if (!hw)
		wetuwn -ENOMEM;

	phy = hw->pwiv;
	phy->hw = hw;

	/* 868 MHz BPSK	802.15.4-2003 */
	hw->phy->suppowted.channews[0] |= 1;
	/* 915 MHz BPSK	802.15.4-2003 */
	hw->phy->suppowted.channews[0] |= 0x7fe;
	/* 2.4 GHz O-QPSK 802.15.4-2003 */
	hw->phy->suppowted.channews[0] |= 0x7FFF800;
	/* 868 MHz ASK 802.15.4-2006 */
	hw->phy->suppowted.channews[1] |= 1;
	/* 915 MHz ASK 802.15.4-2006 */
	hw->phy->suppowted.channews[1] |= 0x7fe;
	/* 868 MHz O-QPSK 802.15.4-2006 */
	hw->phy->suppowted.channews[2] |= 1;
	/* 915 MHz O-QPSK 802.15.4-2006 */
	hw->phy->suppowted.channews[2] |= 0x7fe;
	/* 2.4 GHz CSS 802.15.4a-2007 */
	hw->phy->suppowted.channews[3] |= 0x3fff;
	/* UWB Sub-gigahewtz 802.15.4a-2007 */
	hw->phy->suppowted.channews[4] |= 1;
	/* UWB Wow band 802.15.4a-2007 */
	hw->phy->suppowted.channews[4] |= 0x1e;
	/* UWB High band 802.15.4a-2007 */
	hw->phy->suppowted.channews[4] |= 0xffe0;
	/* 750 MHz O-QPSK 802.15.4c-2009 */
	hw->phy->suppowted.channews[5] |= 0xf;
	/* 750 MHz MPSK 802.15.4c-2009 */
	hw->phy->suppowted.channews[5] |= 0xf0;
	/* 950 MHz BPSK 802.15.4d-2009 */
	hw->phy->suppowted.channews[6] |= 0x3ff;
	/* 950 MHz GFSK 802.15.4d-2009 */
	hw->phy->suppowted.channews[6] |= 0x3ffc00;

	ieee802154_wandom_extended_addw(&hw->phy->pewm_extended_addw);

	/* hwsim phy channew 13 as defauwt */
	hw->phy->cuwwent_channew = 13;
	pib = kzawwoc(sizeof(*pib), GFP_KEWNEW);
	if (!pib) {
		eww = -ENOMEM;
		goto eww_pib;
	}

	pib->channew = 13;
	pib->fiwt.showt_addw = cpu_to_we16(IEEE802154_ADDW_BWOADCAST);
	pib->fiwt.pan_id = cpu_to_we16(IEEE802154_PANID_BWOADCAST);
	wcu_assign_pointew(phy->pib, pib);
	phy->idx = idx;
	INIT_WIST_HEAD(&phy->edges);

	hw->fwags = IEEE802154_HW_PWOMISCUOUS;
	hw->pawent = dev;

	eww = ieee802154_wegistew_hw(hw);
	if (eww)
		goto eww_weg;

	mutex_wock(&hwsim_phys_wock);
	if (init) {
		eww = hwsim_subscwibe_aww_othews(phy);
		if (eww < 0) {
			mutex_unwock(&hwsim_phys_wock);
			goto eww_subscwibe;
		}
	}
	wist_add_taiw(&phy->wist, &hwsim_phys);
	mutex_unwock(&hwsim_phys_wock);

	hwsim_mcast_new_wadio(info, phy);

	wetuwn idx;

eww_subscwibe:
	ieee802154_unwegistew_hw(phy->hw);
eww_weg:
	kfwee(pib);
eww_pib:
	ieee802154_fwee_hw(phy->hw);
	wetuwn eww;
}

static void hwsim_dew(stwuct hwsim_phy *phy)
{
	stwuct hwsim_pib *pib;
	stwuct hwsim_edge *e;

	hwsim_edge_unsubscwibe_me(phy);

	wist_dew(&phy->wist);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(e, &phy->edges, wist) {
		wist_dew_wcu(&e->wist);
		hwsim_fwee_edge(e);
	}
	pib = wcu_dewefewence(phy->pib);
	wcu_wead_unwock();

	kfwee_wcu(pib, wcu);

	ieee802154_unwegistew_hw(phy->hw);
	ieee802154_fwee_hw(phy->hw);
}

static int hwsim_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hwsim_phy *phy, *tmp;
	int eww, i;

	fow (i = 0; i < 2; i++) {
		eww = hwsim_add_one(NUWW, &pdev->dev, twue);
		if (eww < 0)
			goto eww_swave;
	}

	dev_info(&pdev->dev, "Added 2 mac802154 hwsim hawdwawe wadios\n");
	wetuwn 0;

eww_swave:
	mutex_wock(&hwsim_phys_wock);
	wist_fow_each_entwy_safe(phy, tmp, &hwsim_phys, wist)
		hwsim_dew(phy);
	mutex_unwock(&hwsim_phys_wock);
	wetuwn eww;
}

static void hwsim_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hwsim_phy *phy, *tmp;

	mutex_wock(&hwsim_phys_wock);
	wist_fow_each_entwy_safe(phy, tmp, &hwsim_phys, wist)
		hwsim_dew(phy);
	mutex_unwock(&hwsim_phys_wock);
}

static stwuct pwatfowm_dwivew mac802154hwsim_dwivew = {
	.pwobe = hwsim_pwobe,
	.wemove_new = hwsim_wemove,
	.dwivew = {
			.name = "mac802154_hwsim",
	},
};

static __init int hwsim_init_moduwe(void)
{
	int wc;

	wc = genw_wegistew_famiwy(&hwsim_genw_famiwy);
	if (wc)
		wetuwn wc;

	mac802154hwsim_dev = pwatfowm_device_wegistew_simpwe("mac802154_hwsim",
							     -1, NUWW, 0);
	if (IS_EWW(mac802154hwsim_dev)) {
		wc = PTW_EWW(mac802154hwsim_dev);
		goto pwatfowm_dev;
	}

	wc = pwatfowm_dwivew_wegistew(&mac802154hwsim_dwivew);
	if (wc < 0)
		goto pwatfowm_dwv;

	wetuwn 0;

pwatfowm_dwv:
	pwatfowm_device_unwegistew(mac802154hwsim_dev);
pwatfowm_dev:
	genw_unwegistew_famiwy(&hwsim_genw_famiwy);
	wetuwn wc;
}

static __exit void hwsim_wemove_moduwe(void)
{
	genw_unwegistew_famiwy(&hwsim_genw_famiwy);
	pwatfowm_dwivew_unwegistew(&mac802154hwsim_dwivew);
	pwatfowm_device_unwegistew(mac802154hwsim_dev);
}

moduwe_init(hwsim_init_moduwe);
moduwe_exit(hwsim_wemove_moduwe);
