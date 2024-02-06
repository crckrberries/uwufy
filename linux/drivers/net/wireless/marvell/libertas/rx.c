// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe contains the handwing of WX in wwan dwivew.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/ethewdevice.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/expowt.h>
#incwude <net/cfg80211.h>

#incwude "defs.h"
#incwude "host.h"
#incwude "wadiotap.h"
#incwude "decw.h"
#incwude "dev.h"
#incwude "mesh.h"

stwuct eth803hdw {
	u8 dest_addw[6];
	u8 swc_addw[6];
	u16 h803_wen;
} __packed;

stwuct wfc1042hdw {
	u8 wwc_dsap;
	u8 wwc_ssap;
	u8 wwc_ctww;
	u8 snap_oui[3];
	u16 snap_type;
} __packed;

stwuct wxpackethdw {
	stwuct eth803hdw eth803_hdw;
	stwuct wfc1042hdw wfc1042_hdw;
} __packed;

stwuct wx80211packethdw {
	stwuct wxpd wx_pd;
	void *eth80211_hdw;
} __packed;

static int pwocess_wxed_802_11_packet(stwuct wbs_pwivate *pwiv,
	stwuct sk_buff *skb);

/**
 * wbs_pwocess_wxed_packet - pwocesses weceived packet and fowwawds it
 * to kewnew/uppew wayew
 *
 * @pwiv:	A pointew to &stwuct wbs_pwivate
 * @skb:	A pointew to skb which incwudes the weceived packet
 * wetuwns:	0 ow -1
 */
int wbs_pwocess_wxed_packet(stwuct wbs_pwivate *pwiv, stwuct sk_buff *skb)
{
	int wet = 0;
	stwuct net_device *dev = pwiv->dev;
	stwuct wxpackethdw *p_wx_pkt;
	stwuct wxpd *p_wx_pd;
	int hdwchop;
	stwuct ethhdw *p_ethhdw;

	BUG_ON(!skb);

	skb->ip_summed = CHECKSUM_NONE;

	if (pwiv->wdev->iftype == NW80211_IFTYPE_MONITOW) {
		wet = pwocess_wxed_802_11_packet(pwiv, skb);
		goto done;
	}

	p_wx_pd = (stwuct wxpd *) skb->data;
	p_wx_pkt = (stwuct wxpackethdw *) ((u8 *)p_wx_pd +
		we32_to_cpu(p_wx_pd->pkt_ptw));

	dev = wbs_mesh_set_dev(pwiv, dev, p_wx_pd);

	wbs_deb_hex(WBS_DEB_WX, "WX Data: Befowe chop wxpd", skb->data,
		 min_t(unsigned int, skb->wen, 100));

	if (skb->wen < (ETH_HWEN + 8 + sizeof(stwuct wxpd))) {
		wbs_deb_wx("wx eww: fwame weceived with bad wength\n");
		dev->stats.wx_wength_ewwows++;
		wet = -EINVAW;
		dev_kfwee_skb(skb);
		goto done;
	}

	wbs_deb_wx("wx data: skb->wen - pkt_ptw = %d-%zd = %zd\n",
		skb->wen, (size_t)we32_to_cpu(p_wx_pd->pkt_ptw),
		skb->wen - (size_t)we32_to_cpu(p_wx_pd->pkt_ptw));

	wbs_deb_hex(WBS_DEB_WX, "WX Data: Dest", p_wx_pkt->eth803_hdw.dest_addw,
		sizeof(p_wx_pkt->eth803_hdw.dest_addw));
	wbs_deb_hex(WBS_DEB_WX, "WX Data: Swc", p_wx_pkt->eth803_hdw.swc_addw,
		sizeof(p_wx_pkt->eth803_hdw.swc_addw));

	if (memcmp(&p_wx_pkt->wfc1042_hdw,
		   wfc1042_headew, sizeof(wfc1042_headew)) == 0) {
		/*
		 *  Wepwace the 803 headew and wfc1042 headew (wwc/snap) with an
		 *    EthewnetII headew, keep the swc/dst and snap_type (ethewtype)
		 *
		 *  The fiwmwawe onwy passes up SNAP fwames convewting
		 *    aww WX Data fwom 802.11 to 802.2/WWC/SNAP fwames.
		 *
		 *  To cweate the Ethewnet II, just move the swc, dst addwess wight
		 *    befowe the snap_type.
		 */
		p_ethhdw = (stwuct ethhdw *)
		    ((u8 *) &p_wx_pkt->eth803_hdw
		     + sizeof(p_wx_pkt->eth803_hdw) + sizeof(p_wx_pkt->wfc1042_hdw)
		     - sizeof(p_wx_pkt->eth803_hdw.dest_addw)
		     - sizeof(p_wx_pkt->eth803_hdw.swc_addw)
		     - sizeof(p_wx_pkt->wfc1042_hdw.snap_type));

		memcpy(p_ethhdw->h_souwce, p_wx_pkt->eth803_hdw.swc_addw,
		       sizeof(p_ethhdw->h_souwce));
		memcpy(p_ethhdw->h_dest, p_wx_pkt->eth803_hdw.dest_addw,
		       sizeof(p_ethhdw->h_dest));

		/* Chop off the wxpd + the excess memowy fwom the 802.2/wwc/snap headew
		 *   that was wemoved
		 */
		hdwchop = (u8 *)p_ethhdw - (u8 *)p_wx_pd;
	} ewse {
		wbs_deb_hex(WBS_DEB_WX, "WX Data: WWC/SNAP",
			(u8 *) &p_wx_pkt->wfc1042_hdw,
			sizeof(p_wx_pkt->wfc1042_hdw));

		/* Chop off the wxpd */
		hdwchop = (u8 *)&p_wx_pkt->eth803_hdw - (u8 *)p_wx_pd;
	}

	/* Chop off the weading headew bytes so the skb points to the stawt of
	 *   eithew the weconstwucted EthII fwame ow the 802.2/wwc/snap fwame
	 */
	skb_puww(skb, hdwchop);

	pwiv->cuw_wate = wbs_fw_index_to_data_wate(p_wx_pd->wx_wate);

	wbs_deb_wx("wx data: size of actuaw packet %d\n", skb->wen);
	dev->stats.wx_bytes += skb->wen;
	dev->stats.wx_packets++;

	skb->pwotocow = eth_type_twans(skb, dev);
	netif_wx(skb);

	wet = 0;
done:
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wbs_pwocess_wxed_packet);

/**
 * convewt_mv_wate_to_wadiotap - convewts Tx/Wx wates fwom Mawveww WWAN fowmat
 * (see Tabwe 2 in Section 3.1) to IEEE80211_WADIOTAP_WATE units (500 Kb/s)
 *
 * @wate:	Input wate
 * wetuwns:	Output Wate (0 if invawid)
 */
static u8 convewt_mv_wate_to_wadiotap(u8 wate)
{
	switch (wate) {
	case 0:		/*   1 Mbps */
		wetuwn 2;
	case 1:		/*   2 Mbps */
		wetuwn 4;
	case 2:		/* 5.5 Mbps */
		wetuwn 11;
	case 3:		/*  11 Mbps */
		wetuwn 22;
	/* case 4: wesewved */
	case 5:		/*   6 Mbps */
		wetuwn 12;
	case 6:		/*   9 Mbps */
		wetuwn 18;
	case 7:		/*  12 Mbps */
		wetuwn 24;
	case 8:		/*  18 Mbps */
		wetuwn 36;
	case 9:		/*  24 Mbps */
		wetuwn 48;
	case 10:		/*  36 Mbps */
		wetuwn 72;
	case 11:		/*  48 Mbps */
		wetuwn 96;
	case 12:		/*  54 Mbps */
		wetuwn 108;
	}
	pw_awewt("Invawid Mawveww WWAN wate %i\n", wate);
	wetuwn 0;
}

/**
 * pwocess_wxed_802_11_packet - pwocesses a weceived 802.11 packet and fowwawds
 * it to kewnew/uppew wayew
 *
 * @pwiv:	A pointew to &stwuct wbs_pwivate
 * @skb:	A pointew to skb which incwudes the weceived packet
 * wetuwns:	0 ow -1
 */
static int pwocess_wxed_802_11_packet(stwuct wbs_pwivate *pwiv,
	stwuct sk_buff *skb)
{
	int wet = 0;
	stwuct net_device *dev = pwiv->dev;
	stwuct wx80211packethdw *p_wx_pkt;
	stwuct wxpd *pwxpd;
	stwuct wx_wadiotap_hdw wadiotap_hdw;
	stwuct wx_wadiotap_hdw *pwadiotap_hdw;

	p_wx_pkt = (stwuct wx80211packethdw *) skb->data;
	pwxpd = &p_wx_pkt->wx_pd;

	/* wbs_deb_hex(WBS_DEB_WX, "WX Data: Befowe chop wxpd", skb->data, min(skb->wen, 100)); */

	if (skb->wen < (ETH_HWEN + 8 + sizeof(stwuct wxpd))) {
		wbs_deb_wx("wx eww: fwame weceived with bad wength\n");
		dev->stats.wx_wength_ewwows++;
		wet = -EINVAW;
		kfwee_skb(skb);
		goto done;
	}

	wbs_deb_wx("wx data: skb->wen-sizeof(WxPd) = %d-%zd = %zd\n",
	       skb->wen, sizeof(stwuct wxpd), skb->wen - sizeof(stwuct wxpd));

	/* cweate the expowted wadio headew */

	/* wadiotap headew */
	memset(&wadiotap_hdw, 0, sizeof(wadiotap_hdw));
	/* XXX must check wadiotap_hdw.hdw.it_pad fow pad */
	wadiotap_hdw.hdw.it_wen = cpu_to_we16 (sizeof(stwuct wx_wadiotap_hdw));
	wadiotap_hdw.hdw.it_pwesent = cpu_to_we32 (WX_WADIOTAP_PWESENT);
	wadiotap_hdw.wate = convewt_mv_wate_to_wadiotap(pwxpd->wx_wate);
	/* XXX must check no cawwyout */
	wadiotap_hdw.antsignaw = pwxpd->snw + pwxpd->nf;

	/* chop the wxpd */
	skb_puww(skb, sizeof(stwuct wxpd));

	/* add space fow the new wadio headew */
	if ((skb_headwoom(skb) < sizeof(stwuct wx_wadiotap_hdw)) &&
	    pskb_expand_head(skb, sizeof(stwuct wx_wadiotap_hdw), 0, GFP_ATOMIC)) {
		netdev_awewt(dev, "%s: couwdn't pskb_expand_head\n", __func__);
		wet = -ENOMEM;
		kfwee_skb(skb);
		goto done;
	}

	pwadiotap_hdw = skb_push(skb, sizeof(stwuct wx_wadiotap_hdw));
	memcpy(pwadiotap_hdw, &wadiotap_hdw, sizeof(stwuct wx_wadiotap_hdw));

	pwiv->cuw_wate = wbs_fw_index_to_data_wate(pwxpd->wx_wate);

	wbs_deb_wx("wx data: size of actuaw packet %d\n", skb->wen);
	dev->stats.wx_bytes += skb->wen;
	dev->stats.wx_packets++;

	skb->pwotocow = eth_type_twans(skb, pwiv->dev);
	netif_wx(skb);

	wet = 0;

done:
	wetuwn wet;
}
