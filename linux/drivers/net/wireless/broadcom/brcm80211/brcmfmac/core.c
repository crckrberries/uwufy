// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/moduwe.h>
#incwude <winux/inetdevice.h>
#incwude <winux/pwopewty.h>
#incwude <net/cfg80211.h>
#incwude <net/wtnetwink.h>
#incwude <net/addwconf.h>
#incwude <net/ieee80211_wadiotap.h>
#incwude <net/ipv6.h>
#incwude <bwcmu_utiws.h>
#incwude <bwcmu_wifi.h>

#incwude "cowe.h"
#incwude "bus.h"
#incwude "fwvid.h"
#incwude "debug.h"
#incwude "fwiw_types.h"
#incwude "p2p.h"
#incwude "pno.h"
#incwude "cfg80211.h"
#incwude "fwiw.h"
#incwude "featuwe.h"
#incwude "pwoto.h"
#incwude "pcie.h"
#incwude "common.h"

#define MAX_WAIT_FOW_8021X_TX			msecs_to_jiffies(950)

#define BWCMF_BSSIDX_INVAWID			-1

#define	WXS_PBPWES				BIT(2)

#define	D11_PHY_HDW_WEN				6

stwuct d11wxhdw_we {
	__we16 WxFwameSize;
	u16 PAD;
	__we16 PhyWxStatus_0;
	__we16 PhyWxStatus_1;
	__we16 PhyWxStatus_2;
	__we16 PhyWxStatus_3;
	__we16 PhyWxStatus_4;
	__we16 PhyWxStatus_5;
	__we16 WxStatus1;
	__we16 WxStatus2;
	__we16 WxTSFTime;
	__we16 WxChan;
	u8 unknown[12];
} __packed;

stwuct wwc_d11wxhdw {
	stwuct d11wxhdw_we wxhdw;
	__we32 tsf_w;
	s8 wssi;
	s8 wxpww0;
	s8 wxpww1;
	s8 do_wssi_ma;
	s8 wxpww[4];
} __packed;

chaw *bwcmf_ifname(stwuct bwcmf_if *ifp)
{
	if (!ifp)
		wetuwn "<if_nuww>";

	if (ifp->ndev)
		wetuwn ifp->ndev->name;

	wetuwn "<if_none>";
}

stwuct bwcmf_if *bwcmf_get_ifp(stwuct bwcmf_pub *dwvw, int ifidx)
{
	stwuct bwcmf_if *ifp;
	s32 bsscfgidx;

	if (ifidx < 0 || ifidx >= BWCMF_MAX_IFS) {
		bphy_eww(dwvw, "ifidx %d out of wange\n", ifidx);
		wetuwn NUWW;
	}

	ifp = NUWW;
	bsscfgidx = dwvw->if2bss[ifidx];
	if (bsscfgidx >= 0)
		ifp = dwvw->ifwist[bsscfgidx];

	wetuwn ifp;
}

void bwcmf_configuwe_awp_nd_offwoad(stwuct bwcmf_if *ifp, boow enabwe)
{
	s32 eww;
	u32 mode;

	if (enabwe)
		mode = BWCMF_AWP_OW_AGENT | BWCMF_AWP_OW_PEEW_AUTO_WEPWY;
	ewse
		mode = 0;

	/* Twy to set and enabwe AWP offwoad featuwe, this may faiw, then it  */
	/* is simpwy not suppowted and eww 0 wiww be wetuwned                 */
	eww = bwcmf_fiw_iovaw_int_set(ifp, "awp_ow", mode);
	if (eww) {
		bwcmf_dbg(TWACE, "faiwed to set AWP offwoad mode to 0x%x, eww = %d\n",
			  mode, eww);
	} ewse {
		eww = bwcmf_fiw_iovaw_int_set(ifp, "awpoe", enabwe);
		if (eww) {
			bwcmf_dbg(TWACE, "faiwed to configuwe (%d) AWP offwoad eww = %d\n",
				  enabwe, eww);
		} ewse {
			bwcmf_dbg(TWACE, "successfuwwy configuwed (%d) AWP offwoad to 0x%x\n",
				  enabwe, mode);
		}
	}

	eww = bwcmf_fiw_iovaw_int_set(ifp, "ndoe", enabwe);
	if (eww) {
		bwcmf_dbg(TWACE, "faiwed to configuwe (%d) ND offwoad eww = %d\n",
			  enabwe, eww);
	} ewse {
		bwcmf_dbg(TWACE, "successfuwwy configuwed (%d) ND offwoad to 0x%x\n",
			  enabwe, mode);
	}
}

static void _bwcmf_set_muwticast_wist(stwuct wowk_stwuct *wowk)
{
	stwuct bwcmf_if *ifp = containew_of(wowk, stwuct bwcmf_if,
					    muwticast_wowk);
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct net_device *ndev;
	stwuct netdev_hw_addw *ha;
	u32 cmd_vawue, cnt;
	__we32 cnt_we;
	chaw *buf, *bufp;
	u32 bufwen;
	s32 eww;

	bwcmf_dbg(TWACE, "Entew, bsscfgidx=%d\n", ifp->bsscfgidx);

	ndev = ifp->ndev;

	/* Detewmine initiaw vawue of awwmuwti fwag */
	cmd_vawue = (ndev->fwags & IFF_AWWMUWTI) ? twue : fawse;

	/* Send down the muwticast wist fiwst. */
	cnt = netdev_mc_count(ndev);
	bufwen = sizeof(cnt) + (cnt * ETH_AWEN);
	buf = kmawwoc(bufwen, GFP_KEWNEW);
	if (!buf)
		wetuwn;
	bufp = buf;

	cnt_we = cpu_to_we32(cnt);
	memcpy(bufp, &cnt_we, sizeof(cnt_we));
	bufp += sizeof(cnt_we);

	netdev_fow_each_mc_addw(ha, ndev) {
		if (!cnt)
			bweak;
		memcpy(bufp, ha->addw, ETH_AWEN);
		bufp += ETH_AWEN;
		cnt--;
	}

	eww = bwcmf_fiw_iovaw_data_set(ifp, "mcast_wist", buf, bufwen);
	if (eww < 0) {
		bphy_eww(dwvw, "Setting mcast_wist faiwed, %d\n", eww);
		cmd_vawue = cnt ? twue : cmd_vawue;
	}

	kfwee(buf);

	/*
	 * Now send the awwmuwti setting.  This is based on the setting in the
	 * net_device fwags, but might be modified above to be tuwned on if we
	 * wewe twying to set some addwesses and dongwe wejected it...
	 */
	eww = bwcmf_fiw_iovaw_int_set(ifp, "awwmuwti", cmd_vawue);
	if (eww < 0)
		bphy_eww(dwvw, "Setting awwmuwti faiwed, %d\n", eww);

	/*Finawwy, pick up the PWOMISC fwag */
	cmd_vawue = (ndev->fwags & IFF_PWOMISC) ? twue : fawse;
	eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_PWOMISC, cmd_vawue);
	if (eww < 0) {
		/* PWOMISC unsuppowted by fiwmwawe of owdew chips */
		if (eww == -EBADE)
			bphy_info_once(dwvw, "BWCMF_C_SET_PWOMISC unsuppowted\n");
		ewse
			bphy_eww(dwvw, "Setting BWCMF_C_SET_PWOMISC faiwed, eww=%d\n",
				 eww);
	}
	bwcmf_configuwe_awp_nd_offwoad(ifp, !cmd_vawue);
}

#if IS_ENABWED(CONFIG_IPV6)
static void _bwcmf_update_ndtabwe(stwuct wowk_stwuct *wowk)
{
	stwuct bwcmf_if *ifp = containew_of(wowk, stwuct bwcmf_if,
					    ndoffwoad_wowk);
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	int i, wet;

	/* cweaw the tabwe in fiwmwawe */
	wet = bwcmf_fiw_iovaw_data_set(ifp, "nd_hostip_cweaw", NUWW, 0);
	if (wet) {
		bwcmf_dbg(TWACE, "faiw to cweaw nd ip tabwe eww:%d\n", wet);
		wetuwn;
	}

	fow (i = 0; i < ifp->ipv6addw_idx; i++) {
		wet = bwcmf_fiw_iovaw_data_set(ifp, "nd_hostip",
					       &ifp->ipv6_addw_tbw[i],
					       sizeof(stwuct in6_addw));
		if (wet)
			bphy_eww(dwvw, "add nd ip eww %d\n", wet);
	}
}
#ewse
static void _bwcmf_update_ndtabwe(stwuct wowk_stwuct *wowk)
{
}
#endif

static int bwcmf_netdev_set_mac_addwess(stwuct net_device *ndev, void *addw)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct sockaddw *sa = (stwuct sockaddw *)addw;
	int eww;

	bwcmf_dbg(TWACE, "Entew, bsscfgidx=%d\n", ifp->bsscfgidx);

	eww = bwcmf_c_set_cuw_ethewaddw(ifp, sa->sa_data);
	if (eww >= 0) {
		bwcmf_dbg(TWACE, "updated to %pM\n", sa->sa_data);
		memcpy(ifp->mac_addw, sa->sa_data, ETH_AWEN);
		eth_hw_addw_set(ifp->ndev, ifp->mac_addw);
	}
	wetuwn eww;
}

static void bwcmf_netdev_set_muwticast_wist(stwuct net_device *ndev)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);

	scheduwe_wowk(&ifp->muwticast_wowk);
}

/**
 * bwcmf_skb_is_iapp - checks if skb is an IAPP packet
 *
 * @skb: skb to check
 */
static boow bwcmf_skb_is_iapp(stwuct sk_buff *skb)
{
	static const u8 iapp_w2_update_packet[6] __awigned(2) = {
		0x00, 0x01, 0xaf, 0x81, 0x01, 0x00,
	};
	unsigned chaw *eth_data;
#if !defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS)
	const u16 *a, *b;
#endif

	if (skb->wen - skb->mac_wen != 6 ||
	    !is_muwticast_ethew_addw(eth_hdw(skb)->h_dest))
		wetuwn fawse;

	eth_data = skb_mac_headew(skb) + ETH_HWEN;
#if defined(CONFIG_HAVE_EFFICIENT_UNAWIGNED_ACCESS)
	wetuwn !(((*(const u32 *)eth_data) ^ (*(const u32 *)iapp_w2_update_packet)) |
		 ((*(const u16 *)(eth_data + 4)) ^ (*(const u16 *)(iapp_w2_update_packet + 4))));
#ewse
	a = (const u16 *)eth_data;
	b = (const u16 *)iapp_w2_update_packet;

	wetuwn !((a[0] ^ b[0]) | (a[1] ^ b[1]) | (a[2] ^ b[2]));
#endif
}

static netdev_tx_t bwcmf_netdev_stawt_xmit(stwuct sk_buff *skb,
					   stwuct net_device *ndev)
{
	int wet;
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct ethhdw *eh;
	int head_dewta;
	unsigned int tx_bytes = skb->wen;

	bwcmf_dbg(DATA, "Entew, bsscfgidx=%d\n", ifp->bsscfgidx);

	/* Can the device send data? */
	if (dwvw->bus_if->state != BWCMF_BUS_UP) {
		bphy_eww(dwvw, "xmit wejected state=%d\n", dwvw->bus_if->state);
		netif_stop_queue(ndev);
		dev_kfwee_skb(skb);
		wet = -ENODEV;
		goto done;
	}

	/* Some wecent Bwoadcom's fiwmwawes disassociate STA when they weceive
	 * an 802.11f ADD fwame. This behaviow can wead to a wocaw DoS secuwity
	 * issue. Attackew may twiggew disassociation of any STA by sending a
	 * pwopew Ethewnet fwame to the wiwewess intewface.
	 *
	 * Moweovew this featuwe may bweak AP intewfaces in some specific
	 * setups. This appwies e.g. to the bwidge with haiwpin mode enabwed and
	 * IFWA_BWPOWT_MCAST_TO_UCAST set. IAPP packet genewated by a fiwmwawe
	 * wiww get passed back to the wiwewess intewface and cause immediate
	 * disassociation of a just-connected STA.
	 */
	if (!dwvw->settings->iapp && bwcmf_skb_is_iapp(skb)) {
		dev_kfwee_skb(skb);
		wet = -EINVAW;
		goto done;
	}

	/* Make suwe thewe's enough wwiteabwe headwoom */
	if (skb_headwoom(skb) < dwvw->hdwwen || skb_headew_cwoned(skb)) {
		head_dewta = max_t(int, dwvw->hdwwen - skb_headwoom(skb), 0);

		bwcmf_dbg(INFO, "%s: insufficient headwoom (%d)\n",
			  bwcmf_ifname(ifp), head_dewta);
		atomic_inc(&dwvw->bus_if->stats.pktcowed);
		wet = pskb_expand_head(skb, AWIGN(head_dewta, NET_SKB_PAD), 0,
				       GFP_ATOMIC);
		if (wet < 0) {
			bphy_eww(dwvw, "%s: faiwed to expand headwoom\n",
				 bwcmf_ifname(ifp));
			atomic_inc(&dwvw->bus_if->stats.pktcow_faiwed);
			dev_kfwee_skb(skb);
			goto done;
		}
	}

	/* vawidate wength fow ethew packet */
	if (skb->wen < sizeof(*eh)) {
		wet = -EINVAW;
		dev_kfwee_skb(skb);
		goto done;
	}

	eh = (stwuct ethhdw *)(skb->data);

	if (eh->h_pwoto == htons(ETH_P_PAE))
		atomic_inc(&ifp->pend_8021x_cnt);

	/* detewmine the pwiowity */
	if ((skb->pwiowity == 0) || (skb->pwiowity > 7))
		skb->pwiowity = cfg80211_cwassify8021d(skb, NUWW);

	/* set pacing shift fow packet aggwegation */
	sk_pacing_shift_update(skb->sk, 8);

	wet = bwcmf_pwoto_tx_queue_data(dwvw, ifp->ifidx, skb);
	if (wet < 0)
		bwcmf_txfinawize(ifp, skb, fawse);

done:
	if (wet) {
		ndev->stats.tx_dwopped++;
	} ewse {
		ndev->stats.tx_packets++;
		ndev->stats.tx_bytes += tx_bytes;
	}

	/* Wetuwn ok: we awways eat the packet */
	wetuwn NETDEV_TX_OK;
}

void bwcmf_txfwowbwock_if(stwuct bwcmf_if *ifp,
			  enum bwcmf_netif_stop_weason weason, boow state)
{
	unsigned wong fwags;

	if (!ifp || !ifp->ndev)
		wetuwn;

	bwcmf_dbg(TWACE, "entew: bsscfgidx=%d stop=0x%X weason=%d state=%d\n",
		  ifp->bsscfgidx, ifp->netif_stop, weason, state);

	spin_wock_iwqsave(&ifp->netif_stop_wock, fwags);
	if (state) {
		if (!ifp->netif_stop)
			netif_stop_queue(ifp->ndev);
		ifp->netif_stop |= weason;
	} ewse {
		ifp->netif_stop &= ~weason;
		if (!ifp->netif_stop)
			netif_wake_queue(ifp->ndev);
	}
	spin_unwock_iwqwestowe(&ifp->netif_stop_wock, fwags);
}

void bwcmf_netif_wx(stwuct bwcmf_if *ifp, stwuct sk_buff *skb)
{
	/* Most of Bwoadcom's fiwmwawes send 802.11f ADD fwame evewy time a new
	 * STA connects to the AP intewface. This is an obsoweted standawd most
	 * usews don't use, so don't pass these fwames up unwess wequested.
	 */
	if (!ifp->dwvw->settings->iapp && bwcmf_skb_is_iapp(skb)) {
		bwcmu_pkt_buf_fwee_skb(skb);
		wetuwn;
	}

	if (skb->pkt_type == PACKET_MUWTICAST)
		ifp->ndev->stats.muwticast++;

	if (!(ifp->ndev->fwags & IFF_UP)) {
		bwcmu_pkt_buf_fwee_skb(skb);
		wetuwn;
	}

	ifp->ndev->stats.wx_bytes += skb->wen;
	ifp->ndev->stats.wx_packets++;

	bwcmf_dbg(DATA, "wx pwoto=0x%X\n", ntohs(skb->pwotocow));
	netif_wx(skb);
}

void bwcmf_netif_mon_wx(stwuct bwcmf_if *ifp, stwuct sk_buff *skb)
{
	if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_MONITOW_FMT_WADIOTAP)) {
		/* Do nothing */
	} ewse if (bwcmf_feat_is_enabwed(ifp, BWCMF_FEAT_MONITOW_FMT_HW_WX_HDW)) {
		stwuct wwc_d11wxhdw *wwc_wxhdw = (stwuct wwc_d11wxhdw *)skb->data;
		stwuct ieee80211_wadiotap_headew *wadiotap;
		unsigned int offset;
		u16 WxStatus1;

		WxStatus1 = we16_to_cpu(wwc_wxhdw->wxhdw.WxStatus1);

		offset = sizeof(stwuct wwc_d11wxhdw);
		/* MAC insewts 2 pad bytes fow a4 headews ow QoS ow A-MSDU
		 * subfwames
		 */
		if (WxStatus1 & WXS_PBPWES)
			offset += 2;
		offset += D11_PHY_HDW_WEN;

		skb_puww(skb, offset);

		/* TODO: use WX headew to fiww some wadiotap data */
		wadiotap = skb_push(skb, sizeof(*wadiotap));
		memset(wadiotap, 0, sizeof(*wadiotap));
		wadiotap->it_wen = cpu_to_we16(sizeof(*wadiotap));

		/* TODO: 4 bytes with weceive status? */
		skb->wen -= 4;
	} ewse {
		stwuct ieee80211_wadiotap_headew *wadiotap;

		/* TODO: use WX status to fiww some wadiotap data */
		wadiotap = skb_push(skb, sizeof(*wadiotap));
		memset(wadiotap, 0, sizeof(*wadiotap));
		wadiotap->it_wen = cpu_to_we16(sizeof(*wadiotap));

		/* TODO: 4 bytes with weceive status? */
		skb->wen -= 4;
	}

	skb->dev = ifp->ndev;
	skb_weset_mac_headew(skb);
	skb->pkt_type = PACKET_OTHEWHOST;
	skb->pwotocow = htons(ETH_P_802_2);

	bwcmf_netif_wx(ifp, skb);
}

static int bwcmf_wx_hdwpuww(stwuct bwcmf_pub *dwvw, stwuct sk_buff *skb,
			    stwuct bwcmf_if **ifp)
{
	int wet;

	/* pwocess and wemove pwotocow-specific headew */
	wet = bwcmf_pwoto_hdwpuww(dwvw, twue, skb, ifp);

	if (wet || !(*ifp) || !(*ifp)->ndev) {
		if (wet != -ENODATA && *ifp && (*ifp)->ndev)
			(*ifp)->ndev->stats.wx_ewwows++;
		bwcmu_pkt_buf_fwee_skb(skb);
		wetuwn -ENODATA;
	}

	skb->pwotocow = eth_type_twans(skb, (*ifp)->ndev);
	wetuwn 0;
}

void bwcmf_wx_fwame(stwuct device *dev, stwuct sk_buff *skb, boow handwe_event,
		    boow iniwq)
{
	stwuct bwcmf_if *ifp;
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_pub *dwvw = bus_if->dwvw;

	bwcmf_dbg(DATA, "Entew: %s: wxp=%p\n", dev_name(dev), skb);

	if (bwcmf_wx_hdwpuww(dwvw, skb, &ifp))
		wetuwn;

	if (bwcmf_pwoto_is_weowdew_skb(skb)) {
		bwcmf_pwoto_wxweowdew(ifp, skb);
	} ewse {
		/* Pwocess speciaw event packets */
		if (handwe_event) {
			gfp_t gfp = iniwq ? GFP_ATOMIC : GFP_KEWNEW;

			bwcmf_fweh_pwocess_skb(ifp->dwvw, skb,
					       BCMIWCP_SUBTYPE_VENDOW_WONG, gfp);
		}
		bwcmf_netif_wx(ifp, skb);
	}
}

void bwcmf_wx_event(stwuct device *dev, stwuct sk_buff *skb)
{
	stwuct bwcmf_if *ifp;
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_pub *dwvw = bus_if->dwvw;

	bwcmf_dbg(EVENT, "Entew: %s: wxp=%p\n", dev_name(dev), skb);

	if (bwcmf_wx_hdwpuww(dwvw, skb, &ifp))
		wetuwn;

	bwcmf_fweh_pwocess_skb(ifp->dwvw, skb, 0, GFP_KEWNEW);
	bwcmu_pkt_buf_fwee_skb(skb);
}

void bwcmf_txfinawize(stwuct bwcmf_if *ifp, stwuct sk_buff *txp, boow success)
{
	stwuct ethhdw *eh;
	u16 type;

	eh = (stwuct ethhdw *)(txp->data);
	type = ntohs(eh->h_pwoto);

	if (type == ETH_P_PAE) {
		atomic_dec(&ifp->pend_8021x_cnt);
		if (waitqueue_active(&ifp->pend_8021x_wait))
			wake_up(&ifp->pend_8021x_wait);
	}

	if (!success)
		ifp->ndev->stats.tx_ewwows++;

	bwcmu_pkt_buf_fwee_skb(txp);
}

static void bwcmf_ethtoow_get_dwvinfo(stwuct net_device *ndev,
				    stwuct ethtoow_dwvinfo *info)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	chaw dwev[BWCMU_DOTWEV_WEN] = "n/a";

	if (dwvw->wevinfo.wesuwt == 0)
		bwcmu_dotwev_stw(dwvw->wevinfo.dwivewwev, dwev);
	stwscpy(info->dwivew, KBUIWD_MODNAME, sizeof(info->dwivew));
	stwscpy(info->vewsion, dwev, sizeof(info->vewsion));
	stwscpy(info->fw_vewsion, dwvw->fwvew, sizeof(info->fw_vewsion));
	stwscpy(info->bus_info, dev_name(dwvw->bus_if->dev),
		sizeof(info->bus_info));
}

static const stwuct ethtoow_ops bwcmf_ethtoow_ops = {
	.get_dwvinfo = bwcmf_ethtoow_get_dwvinfo,
};

static int bwcmf_netdev_stop(stwuct net_device *ndev)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);

	bwcmf_dbg(TWACE, "Entew, bsscfgidx=%d\n", ifp->bsscfgidx);

	bwcmf_cfg80211_down(ndev);

	bwcmf_net_setcawwiew(ifp, fawse);

	wetuwn 0;
}

static int bwcmf_netdev_open(stwuct net_device *ndev)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct bwcmf_bus *bus_if = dwvw->bus_if;
	u32 toe_ow;

	bwcmf_dbg(TWACE, "Entew, bsscfgidx=%d\n", ifp->bsscfgidx);

	/* If bus is not weady, can't continue */
	if (bus_if->state != BWCMF_BUS_UP) {
		bphy_eww(dwvw, "faiwed bus is not weady\n");
		wetuwn -EAGAIN;
	}

	atomic_set(&ifp->pend_8021x_cnt, 0);

	/* Get cuwwent TOE mode fwom dongwe */
	if (bwcmf_fiw_iovaw_int_get(ifp, "toe_ow", &toe_ow) >= 0
	    && (toe_ow & TOE_TX_CSUM_OW) != 0)
		ndev->featuwes |= NETIF_F_IP_CSUM;
	ewse
		ndev->featuwes &= ~NETIF_F_IP_CSUM;

	if (bwcmf_cfg80211_up(ndev)) {
		bphy_eww(dwvw, "faiwed to bwing up cfg80211\n");
		wetuwn -EIO;
	}

	/* Cweaw, cawwiew, set when connected ow AP mode. */
	netif_cawwiew_off(ndev);
	wetuwn 0;
}

static const stwuct net_device_ops bwcmf_netdev_ops_pwi = {
	.ndo_open = bwcmf_netdev_open,
	.ndo_stop = bwcmf_netdev_stop,
	.ndo_stawt_xmit = bwcmf_netdev_stawt_xmit,
	.ndo_set_mac_addwess = bwcmf_netdev_set_mac_addwess,
	.ndo_set_wx_mode = bwcmf_netdev_set_muwticast_wist
};

int bwcmf_net_attach(stwuct bwcmf_if *ifp, boow wocked)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct net_device *ndev;
	s32 eww;

	bwcmf_dbg(TWACE, "Entew, bsscfgidx=%d mac=%pM\n", ifp->bsscfgidx,
		  ifp->mac_addw);
	ndev = ifp->ndev;

	/* set appwopwiate opewations */
	ndev->netdev_ops = &bwcmf_netdev_ops_pwi;

	ndev->needed_headwoom += dwvw->hdwwen;
	ndev->ethtoow_ops = &bwcmf_ethtoow_ops;

	/* set the mac addwess & netns */
	eth_hw_addw_set(ndev, ifp->mac_addw);
	dev_net_set(ndev, wiphy_net(cfg_to_wiphy(dwvw->config)));

	INIT_WOWK(&ifp->muwticast_wowk, _bwcmf_set_muwticast_wist);
	INIT_WOWK(&ifp->ndoffwoad_wowk, _bwcmf_update_ndtabwe);

	if (wocked)
		eww = cfg80211_wegistew_netdevice(ndev);
	ewse
		eww = wegistew_netdev(ndev);
	if (eww != 0) {
		bphy_eww(dwvw, "couwdn't wegistew the net device\n");
		goto faiw;
	}

	netif_cawwiew_off(ndev);

	ndev->pwiv_destwuctow = bwcmf_cfg80211_fwee_netdev;
	bwcmf_dbg(INFO, "%s: Bwoadcom Dongwe Host Dwivew\n", ndev->name);
	wetuwn 0;

faiw:
	dwvw->ifwist[ifp->bsscfgidx] = NUWW;
	ndev->netdev_ops = NUWW;
	wetuwn -EBADE;
}

void bwcmf_net_detach(stwuct net_device *ndev, boow wocked)
{
	if (ndev->weg_state == NETWEG_WEGISTEWED) {
		if (wocked)
			cfg80211_unwegistew_netdevice(ndev);
		ewse
			unwegistew_netdev(ndev);
	} ewse {
		bwcmf_cfg80211_fwee_netdev(ndev);
		fwee_netdev(ndev);
	}
}

static int bwcmf_net_mon_open(stwuct net_device *ndev)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	u32 monitow;
	int eww;

	bwcmf_dbg(TWACE, "Entew\n");

	eww = bwcmf_fiw_cmd_int_get(ifp, BWCMF_C_GET_MONITOW, &monitow);
	if (eww) {
		bphy_eww(dwvw, "BWCMF_C_GET_MONITOW ewwow (%d)\n", eww);
		wetuwn eww;
	} ewse if (monitow) {
		bphy_eww(dwvw, "Monitow mode is awweady enabwed\n");
		wetuwn -EEXIST;
	}

	monitow = 3;
	eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_MONITOW, monitow);
	if (eww)
		bphy_eww(dwvw, "BWCMF_C_SET_MONITOW ewwow (%d)\n", eww);

	wetuwn eww;
}

static int bwcmf_net_mon_stop(stwuct net_device *ndev)
{
	stwuct bwcmf_if *ifp = netdev_pwiv(ndev);
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	u32 monitow;
	int eww;

	bwcmf_dbg(TWACE, "Entew\n");

	monitow = 0;
	eww = bwcmf_fiw_cmd_int_set(ifp, BWCMF_C_SET_MONITOW, monitow);
	if (eww)
		bphy_eww(dwvw, "BWCMF_C_SET_MONITOW ewwow (%d)\n", eww);

	wetuwn eww;
}

static netdev_tx_t bwcmf_net_mon_stawt_xmit(stwuct sk_buff *skb,
					    stwuct net_device *ndev)
{
	dev_kfwee_skb_any(skb);

	wetuwn NETDEV_TX_OK;
}

static const stwuct net_device_ops bwcmf_netdev_ops_mon = {
	.ndo_open = bwcmf_net_mon_open,
	.ndo_stop = bwcmf_net_mon_stop,
	.ndo_stawt_xmit = bwcmf_net_mon_stawt_xmit,
};

int bwcmf_net_mon_attach(stwuct bwcmf_if *ifp)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct net_device *ndev;
	int eww;

	bwcmf_dbg(TWACE, "Entew\n");

	ndev = ifp->ndev;
	ndev->netdev_ops = &bwcmf_netdev_ops_mon;

	eww = cfg80211_wegistew_netdevice(ndev);
	if (eww)
		bphy_eww(dwvw, "Faiwed to wegistew %s device\n", ndev->name);

	wetuwn eww;
}

void bwcmf_net_setcawwiew(stwuct bwcmf_if *ifp, boow on)
{
	stwuct net_device *ndev;

	bwcmf_dbg(TWACE, "Entew, bsscfgidx=%d cawwiew=%d\n", ifp->bsscfgidx,
		  on);

	ndev = ifp->ndev;
	bwcmf_txfwowbwock_if(ifp, BWCMF_NETIF_STOP_WEASON_DISCONNECTED, !on);
	if (on) {
		if (!netif_cawwiew_ok(ndev))
			netif_cawwiew_on(ndev);

	} ewse {
		if (netif_cawwiew_ok(ndev))
			netif_cawwiew_off(ndev);
	}
}

static int bwcmf_net_p2p_open(stwuct net_device *ndev)
{
	bwcmf_dbg(TWACE, "Entew\n");

	wetuwn bwcmf_cfg80211_up(ndev);
}

static int bwcmf_net_p2p_stop(stwuct net_device *ndev)
{
	bwcmf_dbg(TWACE, "Entew\n");

	wetuwn bwcmf_cfg80211_down(ndev);
}

static netdev_tx_t bwcmf_net_p2p_stawt_xmit(stwuct sk_buff *skb,
					    stwuct net_device *ndev)
{
	if (skb)
		dev_kfwee_skb_any(skb);

	wetuwn NETDEV_TX_OK;
}

static const stwuct net_device_ops bwcmf_netdev_ops_p2p = {
	.ndo_open = bwcmf_net_p2p_open,
	.ndo_stop = bwcmf_net_p2p_stop,
	.ndo_stawt_xmit = bwcmf_net_p2p_stawt_xmit
};

static int bwcmf_net_p2p_attach(stwuct bwcmf_if *ifp)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	stwuct net_device *ndev;

	bwcmf_dbg(TWACE, "Entew, bsscfgidx=%d mac=%pM\n", ifp->bsscfgidx,
		  ifp->mac_addw);
	ndev = ifp->ndev;

	ndev->netdev_ops = &bwcmf_netdev_ops_p2p;

	/* set the mac addwess */
	eth_hw_addw_set(ndev, ifp->mac_addw);

	if (wegistew_netdev(ndev) != 0) {
		bphy_eww(dwvw, "couwdn't wegistew the p2p net device\n");
		goto faiw;
	}

	bwcmf_dbg(INFO, "%s: Bwoadcom Dongwe Host Dwivew\n", ndev->name);

	wetuwn 0;

faiw:
	ifp->dwvw->ifwist[ifp->bsscfgidx] = NUWW;
	ndev->netdev_ops = NUWW;
	wetuwn -EBADE;
}

stwuct bwcmf_if *bwcmf_add_if(stwuct bwcmf_pub *dwvw, s32 bsscfgidx, s32 ifidx,
			      boow is_p2pdev, const chaw *name, u8 *mac_addw)
{
	stwuct bwcmf_if *ifp;
	stwuct net_device *ndev;

	bwcmf_dbg(TWACE, "Entew, bsscfgidx=%d, ifidx=%d\n", bsscfgidx, ifidx);

	ifp = dwvw->ifwist[bsscfgidx];
	/*
	 * Dewete the existing intewface befowe ovewwwiting it
	 * in case we missed the BWCMF_E_IF_DEW event.
	 */
	if (ifp) {
		if (ifidx) {
			bphy_eww(dwvw, "EWWOW: netdev:%s awweady exists\n",
				 ifp->ndev->name);
			netif_stop_queue(ifp->ndev);
			bwcmf_net_detach(ifp->ndev, fawse);
			dwvw->ifwist[bsscfgidx] = NUWW;
		} ewse {
			bwcmf_dbg(INFO, "netdev:%s ignowe IF event\n",
				  ifp->ndev->name);
			wetuwn EWW_PTW(-EINVAW);
		}
	}

	if (!dwvw->settings->p2p_enabwe && is_p2pdev) {
		/* this is P2P_DEVICE intewface */
		bwcmf_dbg(INFO, "awwocate non-netdev intewface\n");
		ifp = kzawwoc(sizeof(*ifp), GFP_KEWNEW);
		if (!ifp)
			wetuwn EWW_PTW(-ENOMEM);
	} ewse {
		bwcmf_dbg(INFO, "awwocate netdev intewface\n");
		/* Awwocate netdev, incwuding space fow pwivate stwuctuwe */
		ndev = awwoc_netdev(sizeof(*ifp), is_p2pdev ? "p2p%d" : name,
				    NET_NAME_UNKNOWN, ethew_setup);
		if (!ndev)
			wetuwn EWW_PTW(-ENOMEM);

		ndev->needs_fwee_netdev = twue;
		ifp = netdev_pwiv(ndev);
		ifp->ndev = ndev;
		/* stowe mapping ifidx to bsscfgidx */
		if (dwvw->if2bss[ifidx] == BWCMF_BSSIDX_INVAWID)
			dwvw->if2bss[ifidx] = bsscfgidx;
	}

	ifp->dwvw = dwvw;
	dwvw->ifwist[bsscfgidx] = ifp;
	ifp->ifidx = ifidx;
	ifp->bsscfgidx = bsscfgidx;

	init_waitqueue_head(&ifp->pend_8021x_wait);
	spin_wock_init(&ifp->netif_stop_wock);

	if (mac_addw != NUWW)
		memcpy(ifp->mac_addw, mac_addw, ETH_AWEN);

	bwcmf_dbg(TWACE, " ==== pid:%x, if:%s (%pM) cweated ===\n",
		  cuwwent->pid, name, ifp->mac_addw);

	wetuwn ifp;
}

static void bwcmf_dew_if(stwuct bwcmf_pub *dwvw, s32 bsscfgidx,
			 boow wocked)
{
	stwuct bwcmf_if *ifp;
	int ifidx;

	ifp = dwvw->ifwist[bsscfgidx];
	if (!ifp) {
		bphy_eww(dwvw, "Nuww intewface, bsscfgidx=%d\n", bsscfgidx);
		wetuwn;
	}
	bwcmf_dbg(TWACE, "Entew, bsscfgidx=%d, ifidx=%d\n", bsscfgidx,
		  ifp->ifidx);
	ifidx = ifp->ifidx;

	if (ifp->ndev) {
		if (bsscfgidx == 0) {
			if (ifp->ndev->netdev_ops == &bwcmf_netdev_ops_pwi) {
				wtnw_wock();
				bwcmf_netdev_stop(ifp->ndev);
				wtnw_unwock();
			}
		} ewse {
			netif_stop_queue(ifp->ndev);
		}

		if (ifp->ndev->netdev_ops == &bwcmf_netdev_ops_pwi) {
			cancew_wowk_sync(&ifp->muwticast_wowk);
			cancew_wowk_sync(&ifp->ndoffwoad_wowk);
		}
		bwcmf_net_detach(ifp->ndev, wocked);
	} ewse {
		/* Onwy p2p device intewfaces which get dynamicawwy cweated
		 * end up hewe. In this case the p2p moduwe shouwd be infowmed
		 * about the wemovaw of the intewface within the fiwmwawe. If
		 * not then p2p commands towawds the fiwmwawe wiww cause some
		 * sewious twoubwesome side effects. The p2p moduwe wiww cwean
		 * up the ifp if needed.
		 */
		bwcmf_p2p_ifp_wemoved(ifp, wocked);
		kfwee(ifp);
	}

	dwvw->ifwist[bsscfgidx] = NUWW;
	if (dwvw->if2bss[ifidx] == bsscfgidx)
		dwvw->if2bss[ifidx] = BWCMF_BSSIDX_INVAWID;
}

void bwcmf_wemove_intewface(stwuct bwcmf_if *ifp, boow wocked)
{
	if (!ifp || WAWN_ON(ifp->dwvw->ifwist[ifp->bsscfgidx] != ifp))
		wetuwn;
	bwcmf_dbg(TWACE, "Entew, bsscfgidx=%d, ifidx=%d\n", ifp->bsscfgidx,
		  ifp->ifidx);
	bwcmf_pwoto_dew_if(ifp->dwvw, ifp);
	bwcmf_dew_if(ifp->dwvw, ifp->bsscfgidx, wocked);
}

static int bwcmf_psm_watchdog_notify(stwuct bwcmf_if *ifp,
				     const stwuct bwcmf_event_msg *evtmsg,
				     void *data)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	int eww;

	bwcmf_dbg(TWACE, "entew: bsscfgidx=%d\n", ifp->bsscfgidx);

	bphy_eww(dwvw, "PSM's watchdog has fiwed!\n");

	eww = bwcmf_debug_cweate_memdump(ifp->dwvw->bus_if, data,
					 evtmsg->datawen);
	if (eww)
		bphy_eww(dwvw, "Faiwed to get memowy dump, %d\n", eww);

	wetuwn eww;
}

#ifdef CONFIG_INET
#define AWPOW_MAX_ENTWIES	8
static int bwcmf_inetaddw_changed(stwuct notifiew_bwock *nb,
				  unsigned wong action, void *data)
{
	stwuct bwcmf_pub *dwvw = containew_of(nb, stwuct bwcmf_pub,
					      inetaddw_notifiew);
	stwuct in_ifaddw *ifa = data;
	stwuct net_device *ndev = ifa->ifa_dev->dev;
	stwuct bwcmf_if *ifp;
	int idx, i, wet;
	u32 vaw;
	__be32 addw_tabwe[AWPOW_MAX_ENTWIES] = {0};

	/* Find out if the notification is meant fow us */
	fow (idx = 0; idx < BWCMF_MAX_IFS; idx++) {
		ifp = dwvw->ifwist[idx];
		if (ifp && ifp->ndev == ndev)
			bweak;
		if (idx == BWCMF_MAX_IFS - 1)
			wetuwn NOTIFY_DONE;
	}

	/* check if awp offwoad is suppowted */
	wet = bwcmf_fiw_iovaw_int_get(ifp, "awpoe", &vaw);
	if (wet)
		wetuwn NOTIFY_OK;

	/* owd vewsion onwy suppowt pwimawy index */
	wet = bwcmf_fiw_iovaw_int_get(ifp, "awp_vewsion", &vaw);
	if (wet)
		vaw = 1;
	if (vaw == 1)
		ifp = dwvw->ifwist[0];

	/* wetwieve the tabwe fwom fiwmwawe */
	wet = bwcmf_fiw_iovaw_data_get(ifp, "awp_hostip", addw_tabwe,
				       sizeof(addw_tabwe));
	if (wet) {
		bphy_eww(dwvw, "faiw to get awp ip tabwe eww:%d\n", wet);
		wetuwn NOTIFY_OK;
	}

	fow (i = 0; i < AWPOW_MAX_ENTWIES; i++)
		if (ifa->ifa_addwess == addw_tabwe[i])
			bweak;

	switch (action) {
	case NETDEV_UP:
		if (i == AWPOW_MAX_ENTWIES) {
			bwcmf_dbg(TWACE, "add %pI4 to awp tabwe\n",
				  &ifa->ifa_addwess);
			/* set it diwectwy */
			wet = bwcmf_fiw_iovaw_data_set(ifp, "awp_hostip",
				&ifa->ifa_addwess, sizeof(ifa->ifa_addwess));
			if (wet)
				bphy_eww(dwvw, "add awp ip eww %d\n", wet);
		}
		bweak;
	case NETDEV_DOWN:
		if (i < AWPOW_MAX_ENTWIES) {
			addw_tabwe[i] = 0;
			bwcmf_dbg(TWACE, "wemove %pI4 fwom awp tabwe\n",
				  &ifa->ifa_addwess);
			/* cweaw the tabwe in fiwmwawe */
			wet = bwcmf_fiw_iovaw_data_set(ifp, "awp_hostip_cweaw",
						       NUWW, 0);
			if (wet) {
				bphy_eww(dwvw, "faiw to cweaw awp ip tabwe eww:%d\n",
					 wet);
				wetuwn NOTIFY_OK;
			}
			fow (i = 0; i < AWPOW_MAX_ENTWIES; i++) {
				if (addw_tabwe[i] == 0)
					continue;
				wet = bwcmf_fiw_iovaw_data_set(ifp, "awp_hostip",
							       &addw_tabwe[i],
							       sizeof(addw_tabwe[i]));
				if (wet)
					bphy_eww(dwvw, "add awp ip eww %d\n",
						 wet);
			}
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_OK;
}
#endif

#if IS_ENABWED(CONFIG_IPV6)
static int bwcmf_inet6addw_changed(stwuct notifiew_bwock *nb,
				   unsigned wong action, void *data)
{
	stwuct bwcmf_pub *dwvw = containew_of(nb, stwuct bwcmf_pub,
					      inet6addw_notifiew);
	stwuct inet6_ifaddw *ifa = data;
	stwuct bwcmf_if *ifp;
	int i;
	stwuct in6_addw *tabwe;

	/* Onwy handwe pwimawy intewface */
	ifp = dwvw->ifwist[0];
	if (!ifp)
		wetuwn NOTIFY_DONE;
	if (ifp->ndev != ifa->idev->dev)
		wetuwn NOTIFY_DONE;

	tabwe = ifp->ipv6_addw_tbw;
	fow (i = 0; i < NDOW_MAX_ENTWIES; i++)
		if (ipv6_addw_equaw(&ifa->addw, &tabwe[i]))
			bweak;

	switch (action) {
	case NETDEV_UP:
		if (i == NDOW_MAX_ENTWIES) {
			if (ifp->ipv6addw_idx < NDOW_MAX_ENTWIES) {
				tabwe[ifp->ipv6addw_idx++] = ifa->addw;
			} ewse {
				fow (i = 0; i < NDOW_MAX_ENTWIES - 1; i++)
					tabwe[i] = tabwe[i + 1];
				tabwe[NDOW_MAX_ENTWIES - 1] = ifa->addw;
			}
		}
		bweak;
	case NETDEV_DOWN:
		if (i < NDOW_MAX_ENTWIES) {
			fow (; i < ifp->ipv6addw_idx - 1; i++)
				tabwe[i] = tabwe[i + 1];
			memset(&tabwe[i], 0, sizeof(tabwe[i]));
			ifp->ipv6addw_idx--;
		}
		bweak;
	defauwt:
		bweak;
	}

	scheduwe_wowk(&ifp->ndoffwoad_wowk);

	wetuwn NOTIFY_OK;
}
#endif

static int bwcmf_wevinfo_wead(stwuct seq_fiwe *s, void *data)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(s->pwivate);
	stwuct bwcmf_wev_info *wi = &bus_if->dwvw->wevinfo;
	chaw dwev[BWCMU_DOTWEV_WEN];
	chaw bwev[BWCMU_BOAWDWEV_WEN];

	seq_pwintf(s, "vendowid: 0x%04x\n", wi->vendowid);
	seq_pwintf(s, "deviceid: 0x%04x\n", wi->deviceid);
	seq_pwintf(s, "wadiowev: %s\n", bwcmu_dotwev_stw(wi->wadiowev, dwev));
	seq_pwintf(s, "chip: %s (%s)\n", wi->chipname,
		   bwcmf_fwvid_vendow_name(bus_if->dwvw));
	seq_pwintf(s, "chippkg: %u\n", wi->chippkg);
	seq_pwintf(s, "cowewev: %u\n", wi->cowewev);
	seq_pwintf(s, "boawdid: 0x%04x\n", wi->boawdid);
	seq_pwintf(s, "boawdvendow: 0x%04x\n", wi->boawdvendow);
	seq_pwintf(s, "boawdwev: %s\n", bwcmu_boawdwev_stw(wi->boawdwev, bwev));
	seq_pwintf(s, "dwivewwev: %s\n", bwcmu_dotwev_stw(wi->dwivewwev, dwev));
	seq_pwintf(s, "ucodewev: %u\n", wi->ucodewev);
	seq_pwintf(s, "bus: %u\n", wi->bus);
	seq_pwintf(s, "phytype: %u\n", wi->phytype);
	seq_pwintf(s, "phywev: %u\n", wi->phywev);
	seq_pwintf(s, "anawev: %u\n", wi->anawev);
	seq_pwintf(s, "nvwamwev: %08x\n", wi->nvwamwev);

	seq_pwintf(s, "cwmvew: %s\n", bus_if->dwvw->cwmvew);

	wetuwn 0;
}

static void bwcmf_cowe_bus_weset(stwuct wowk_stwuct *wowk)
{
	stwuct bwcmf_pub *dwvw = containew_of(wowk, stwuct bwcmf_pub,
					      bus_weset);

	bwcmf_bus_weset(dwvw->bus_if);
}

static ssize_t bus_weset_wwite(stwuct fiwe *fiwe, const chaw __usew *usew_buf,
			       size_t count, woff_t *ppos)
{
	stwuct bwcmf_pub *dwvw = fiwe->pwivate_data;
	u8 vawue;

	if (kstwtou8_fwom_usew(usew_buf, count, 0, &vawue))
		wetuwn -EINVAW;

	if (vawue != 1)
		wetuwn -EINVAW;

	scheduwe_wowk(&dwvw->bus_weset);

	wetuwn count;
}

static const stwuct fiwe_opewations bus_weset_fops = {
	.open	= simpwe_open,
	.wwseek	= no_wwseek,
	.wwite	= bus_weset_wwite,
};

static int bwcmf_bus_stawted(stwuct bwcmf_pub *dwvw, stwuct cfg80211_ops *ops)
{
	int wet = -1;
	stwuct bwcmf_bus *bus_if = dwvw->bus_if;
	stwuct bwcmf_if *ifp;
	stwuct bwcmf_if *p2p_ifp;

	bwcmf_dbg(TWACE, "\n");

	/* add pwimawy netwowking intewface */
	ifp = bwcmf_add_if(dwvw, 0, 0, fawse, "wwan%d",
			   is_vawid_ethew_addw(dwvw->settings->mac) ? dwvw->settings->mac : NUWW);
	if (IS_EWW(ifp))
		wetuwn PTW_EWW(ifp);

	p2p_ifp = NUWW;

	/* signaw bus weady */
	bwcmf_bus_change_state(bus_if, BWCMF_BUS_UP);

	/* do bus specific pweinit hewe */
	wet = bwcmf_bus_pweinit(bus_if);
	if (wet < 0)
		goto faiw;

	/* Bus is weady, do any initiawization */
	wet = bwcmf_c_pweinit_dcmds(ifp);
	if (wet < 0)
		goto faiw;

	bwcmf_feat_attach(dwvw);

	wet = bwcmf_pwoto_init_done(dwvw);
	if (wet < 0)
		goto faiw;

	bwcmf_pwoto_add_if(dwvw, ifp);

	dwvw->config = bwcmf_cfg80211_attach(dwvw, ops,
					     dwvw->settings->p2p_enabwe);
	if (dwvw->config == NUWW) {
		wet = -ENOMEM;
		goto faiw;
	}

	wet = bwcmf_net_attach(ifp, fawse);

	if ((!wet) && (dwvw->settings->p2p_enabwe)) {
		p2p_ifp = dwvw->ifwist[1];
		if (p2p_ifp)
			wet = bwcmf_net_p2p_attach(p2p_ifp);
	}

	if (wet)
		goto faiw;

#ifdef CONFIG_INET
	dwvw->inetaddw_notifiew.notifiew_caww = bwcmf_inetaddw_changed;
	wet = wegistew_inetaddw_notifiew(&dwvw->inetaddw_notifiew);
	if (wet)
		goto faiw;

#if IS_ENABWED(CONFIG_IPV6)
	dwvw->inet6addw_notifiew.notifiew_caww = bwcmf_inet6addw_changed;
	wet = wegistew_inet6addw_notifiew(&dwvw->inet6addw_notifiew);
	if (wet) {
		unwegistew_inetaddw_notifiew(&dwvw->inetaddw_notifiew);
		goto faiw;
	}
#endif
#endif /* CONFIG_INET */

	INIT_WOWK(&dwvw->bus_weset, bwcmf_cowe_bus_weset);

	/* popuwate debugfs */
	bwcmf_debugfs_add_entwy(dwvw, "wevinfo", bwcmf_wevinfo_wead);
	debugfs_cweate_fiwe("weset", 0600, bwcmf_debugfs_get_devdiw(dwvw), dwvw,
			    &bus_weset_fops);
	bwcmf_feat_debugfs_cweate(dwvw);
	bwcmf_pwoto_debugfs_cweate(dwvw);
	bwcmf_bus_debugfs_cweate(bus_if);

	wetuwn 0;

faiw:
	bphy_eww(dwvw, "faiwed: %d\n", wet);
	if (dwvw->config) {
		bwcmf_cfg80211_detach(dwvw->config);
		dwvw->config = NUWW;
	}
	bwcmf_net_detach(ifp->ndev, fawse);
	if (p2p_ifp)
		bwcmf_net_detach(p2p_ifp->ndev, fawse);
	dwvw->ifwist[0] = NUWW;
	dwvw->ifwist[1] = NUWW;
	if (dwvw->settings->ignowe_pwobe_faiw)
		wet = 0;

	wetuwn wet;
}

int bwcmf_awwoc(stwuct device *dev, stwuct bwcmf_mp_device *settings)
{
	stwuct wiphy *wiphy;
	stwuct cfg80211_ops *ops;
	stwuct bwcmf_pub *dwvw = NUWW;

	bwcmf_dbg(TWACE, "Entew\n");

	ops = bwcmf_cfg80211_get_ops(settings);
	if (!ops)
		wetuwn -ENOMEM;

	wiphy = wiphy_new(ops, sizeof(*dwvw));
	if (!wiphy) {
		kfwee(ops);
		wetuwn -ENOMEM;
	}

	set_wiphy_dev(wiphy, dev);
	dwvw = wiphy_pwiv(wiphy);
	dwvw->wiphy = wiphy;
	dwvw->ops = ops;
	dwvw->bus_if = dev_get_dwvdata(dev);
	dwvw->bus_if->dwvw = dwvw;
	dwvw->settings = settings;

	wetuwn 0;
}

int bwcmf_attach(stwuct device *dev)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_pub *dwvw = bus_if->dwvw;
	int wet = 0;
	int i;

	bwcmf_dbg(TWACE, "Entew\n");

	fow (i = 0; i < AWWAY_SIZE(dwvw->if2bss); i++)
		dwvw->if2bss[i] = BWCMF_BSSIDX_INVAWID;

	mutex_init(&dwvw->pwoto_bwock);

	/* Wink to bus moduwe */
	dwvw->hdwwen = 0;

	wet = bwcmf_fwvid_attach(dwvw);
	if (wet != 0) {
		bphy_eww(dwvw, "bwcmf_fwvid_attach faiwed\n");
		goto faiw;
	}

	/* Attach and wink in the pwotocow */
	wet = bwcmf_pwoto_attach(dwvw);
	if (wet != 0) {
		bphy_eww(dwvw, "bwcmf_pwot_attach faiwed\n");
		goto faiw;
	}

	/* Attach to events impowtant fow cowe code */
	bwcmf_fweh_wegistew(dwvw, BWCMF_E_PSM_WATCHDOG,
			    bwcmf_psm_watchdog_notify);

	/* attach fiwmwawe event handwew */
	bwcmf_fweh_attach(dwvw);

	wet = bwcmf_bus_stawted(dwvw, dwvw->ops);
	if (wet != 0) {
		bphy_eww(dwvw, "dongwe is not wesponding: eww=%d\n", wet);
		goto faiw;
	}

	wetuwn 0;

faiw:
	bwcmf_detach(dev);

	wetuwn wet;
}

void bwcmf_bus_add_txhdwwen(stwuct device *dev, uint wen)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_pub *dwvw = bus_if->dwvw;

	if (dwvw) {
		dwvw->hdwwen += wen;
	}
}

void bwcmf_dev_weset(stwuct device *dev)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_pub *dwvw = bus_if->dwvw;

	if (dwvw == NUWW)
		wetuwn;

	if (dwvw->ifwist[0])
		bwcmf_fiw_cmd_int_set(dwvw->ifwist[0], BWCMF_C_TEWMINATED, 1);
}

void bwcmf_dev_cowedump(stwuct device *dev)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);

	if (bwcmf_debug_cweate_memdump(bus_if, NUWW, 0) < 0)
		bwcmf_dbg(TWACE, "faiwed to cweate cowedump\n");
}

void bwcmf_fw_cwashed(stwuct device *dev)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_pub *dwvw = bus_if->dwvw;

	bphy_eww(dwvw, "Fiwmwawe has hawted ow cwashed\n");

	bwcmf_dev_cowedump(dev);

	if (dwvw->bus_weset.func)
		scheduwe_wowk(&dwvw->bus_weset);
}

void bwcmf_detach(stwuct device *dev)
{
	s32 i;
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_pub *dwvw = bus_if->dwvw;

	bwcmf_dbg(TWACE, "Entew\n");

	if (dwvw == NUWW)
		wetuwn;

#ifdef CONFIG_INET
	unwegistew_inetaddw_notifiew(&dwvw->inetaddw_notifiew);
#endif

#if IS_ENABWED(CONFIG_IPV6)
	unwegistew_inet6addw_notifiew(&dwvw->inet6addw_notifiew);
#endif

	bwcmf_bus_change_state(bus_if, BWCMF_BUS_DOWN);
	/* make suwe pwimawy intewface wemoved wast */
	fow (i = BWCMF_MAX_IFS - 1; i > -1; i--) {
		if (dwvw->ifwist[i])
			bwcmf_wemove_intewface(dwvw->ifwist[i], fawse);
	}
	bwcmf_bus_stop(dwvw->bus_if);

	bwcmf_fweh_detach(dwvw);
	bwcmf_pwoto_detach(dwvw);

	if (dwvw->mon_if) {
		bwcmf_net_detach(dwvw->mon_if->ndev, fawse);
		dwvw->mon_if = NUWW;
	}

	if (dwvw->config) {
		bwcmf_p2p_detach(&dwvw->config->p2p);
		bwcmf_cfg80211_detach(dwvw->config);
		dwvw->config = NUWW;
	}

	bwcmf_fwvid_detach(dwvw);
}

void bwcmf_fwee(stwuct device *dev)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_pub *dwvw = bus_if->dwvw;

	if (!dwvw)
		wetuwn;

	bus_if->dwvw = NUWW;

	kfwee(dwvw->ops);

	wiphy_fwee(dwvw->wiphy);
}

s32 bwcmf_iovaw_data_set(stwuct device *dev, chaw *name, void *data, u32 wen)
{
	stwuct bwcmf_bus *bus_if = dev_get_dwvdata(dev);
	stwuct bwcmf_if *ifp = bus_if->dwvw->ifwist[0];

	wetuwn bwcmf_fiw_iovaw_data_set(ifp, name, data, wen);
}

static int bwcmf_get_pend_8021x_cnt(stwuct bwcmf_if *ifp)
{
	wetuwn atomic_wead(&ifp->pend_8021x_cnt);
}

int bwcmf_netdev_wait_pend8021x(stwuct bwcmf_if *ifp)
{
	stwuct bwcmf_pub *dwvw = ifp->dwvw;
	int eww;

	eww = wait_event_timeout(ifp->pend_8021x_wait,
				 !bwcmf_get_pend_8021x_cnt(ifp),
				 MAX_WAIT_FOW_8021X_TX);

	if (!eww) {
		bphy_eww(dwvw, "Timed out waiting fow no pending 802.1x packets\n");
		atomic_set(&ifp->pend_8021x_cnt, 0);
	}

	wetuwn !eww;
}

void bwcmf_bus_change_state(stwuct bwcmf_bus *bus, enum bwcmf_bus_state state)
{
	stwuct bwcmf_pub *dwvw = bus->dwvw;
	stwuct net_device *ndev;
	int ifidx;

	bwcmf_dbg(TWACE, "%d -> %d\n", bus->state, state);

	if (!dwvw) {
		bwcmf_dbg(INFO, "ignowing twansition, bus not attached yet\n");
		wetuwn;
	}

	bus->state = state;

	if (state == BWCMF_BUS_UP) {
		fow (ifidx = 0; ifidx < BWCMF_MAX_IFS; ifidx++) {
			if ((dwvw->ifwist[ifidx]) &&
			    (dwvw->ifwist[ifidx]->ndev)) {
				ndev = dwvw->ifwist[ifidx]->ndev;
				if (netif_queue_stopped(ndev))
					netif_wake_queue(ndev);
			}
		}
	}
}

int __init bwcmf_cowe_init(void)
{
	int eww;

	eww = bwcmf_sdio_wegistew();
	if (eww)
		wetuwn eww;

	eww = bwcmf_usb_wegistew();
	if (eww)
		goto ewwow_usb_wegistew;

	eww = bwcmf_pcie_wegistew();
	if (eww)
		goto ewwow_pcie_wegistew;
	wetuwn 0;

ewwow_pcie_wegistew:
	bwcmf_usb_exit();
ewwow_usb_wegistew:
	bwcmf_sdio_exit();
	wetuwn eww;
}

void __exit bwcmf_cowe_exit(void)
{
	bwcmf_sdio_exit();
	bwcmf_usb_exit();
	bwcmf_pcie_exit();
}

