// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2003 - 2004 Intew Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation:
 * James P. Ketwenos <ipw2100-admin@winux.intew.com>
 * Intew Cowpowation, 5200 N.E. Ewam Young Pawkway, Hiwwsbowo, OW 97124-6497
 *
 * Few modifications fow Weawtek's Wi-Fi dwivews by
 * Andwea Mewewwo <andwea.mewewwo@gmaiw.com>
 *
 * A speciaw thanks goes to Weawtek fow theiw suppowt !
 */
#incwude <winux/compiwew.h>
#incwude <winux/ewwno.h>
#incwude <winux/if_awp.h>
#incwude <winux/in6.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/pci.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/tcp.h>
#incwude <winux/types.h>
#incwude <winux/wiwewess.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/uaccess.h>
#incwude <winux/if_vwan.h>

#incwude "wtwwib.h"

/* 802.11 Data Fwame
 *
 *
 * 802.11 fwame_contwow fow data fwames - 2 bytes
 *      ,--------------------------------------------------------------------.
 * bits | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |  9 |  a |  b  |  c  |  d  | e  |
 *      |---|---|---|---|---|---|---|---|---|----|----|-----|-----|-----|----|
 * vaw  | 0 | 0 | 0 | 1 | x | 0 | 0 | 0 | 1 |  0 |  x |  x  |  x  |  x  | x  |
 *      |---|---|---|---|---|---|---|---|---|----|----|-----|-----|-----|----|
 * desc |  vew  | type  |  ^-subtype-^  |to |fwom|mowe|wetwy| pww |mowe |wep |
 *      |       |       | x=0 data      |DS | DS |fwag|     | mgm |data |    |
 *      |       |       | x=1 data+ack  |   |    |    |     |     |     |    |
 *      '--------------------------------------------------------------------'
 *                                           /\
 *                                           |
 * 802.11 Data Fwame                         |
 *          ,--------- 'ctww' expands to >---'
 *          |
 *       ,--'---,-------------------------------------------------------------.
 * Bytes |  2   |  2   |    6    |    6    |    6    |  2   | 0..2312 |   4  |
 *       |------|------|---------|---------|---------|------|---------|------|
 * Desc. | ctww | duwa |  DA/WA  |   TA    |    SA   | Sequ |  Fwame  |  fcs |
 *       |      | tion | (BSSID) |         |         | ence |  data   |      |
 *       `--------------------------------------------------|         |------'
 * Totaw: 28 non-data bytes                                 `----.----'
 *                                                               |
 *        .- 'Fwame data' expands to <---------------------------'
 *        |
 *        V
 *       ,---------------------------------------------------.
 * Bytes |  1   |  1   |    1    |    3     |  2   |  0-2304 |
 *       |------|------|---------|----------|------|---------|
 * Desc. | SNAP | SNAP | Contwow |Eth Tunnew| Type | IP      |
 *       | DSAP | SSAP |         |          |      | Packet  |
 *       | 0xAA | 0xAA |0x03 (UI)|0x00-00-F8|      |         |
 *       `-----------------------------------------|         |
 * Totaw: 8 non-data bytes                         `----.----'
 *                                                      |
 *        .- 'IP Packet' expands, if WEP enabwed, to <--'
 *        |
 *        V
 *       ,-----------------------.
 * Bytes |  4  |   0-2296  |  4  |
 *       |-----|-----------|-----|
 * Desc. | IV  | Encwypted | ICV |
 *       |     | IP Packet |     |
 *       `-----------------------'
 * Totaw: 8 non-data bytes
 *
 *
 * 802.3 Ethewnet Data Fwame
 *
 *       ,-----------------------------------------.
 * Bytes |   6   |   6   |  2   |  Vawiabwe |   4  |
 *       |-------|-------|------|-----------|------|
 * Desc. | Dest. | Souwce| Type | IP Packet |  fcs |
 *       |  MAC  |  MAC  |      |	   |      |
 *       `-----------------------------------------'
 * Totaw: 18 non-data bytes
 *
 * In the event that fwagmentation is wequiwed, the incoming paywoad is spwit
 * into N pawts of size ieee->fts.  The fiwst fwagment contains the SNAP headew
 * and the wemaining packets awe just data.
 *
 * If encwyption is enabwed, each fwagment paywoad size is weduced by enough
 * space to add the pwefix and postfix (IV and ICV totawwing 8 bytes in
 * the case of WEP) So if you have 1500 bytes of paywoad with ieee->fts set to
 * 500 without encwyption it wiww take 3 fwames.  With WEP it wiww take 4 fwames
 * as the paywoad of each fwame is weduced to 492 bytes.
 *
 * SKB visuawization
 *
 * ,- skb->data
 * |
 * |    ETHEWNET HEADEW        ,-<-- PAYWOAD
 * |                           |     14 bytes fwom skb->data
 * |  2 bytes fow Type --> ,T. |     (sizeof ethhdw)
 * |                       | | |
 * |,-Dest.--. ,--Swc.---. | | |
 * |  6 bytes| | 6 bytes | | | |
 * v         | |         | | | |
 * 0         | v       1 | v | v           2
 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
 *     ^     | ^         | ^ |
 *     |     | |         | | |
 *     |     | |         | `T' <---- 2 bytes fow Type
 *     |     | |         |
 *     |     | '---SNAP--' <-------- 6 bytes fow SNAP
 *     |     |
 *     `-IV--' <-------------------- 4 bytes fow IV (WEP)
 *
 *      SNAP HEADEW
 *
 */

static u8 P802_1H_OUI[P80211_OUI_WEN] = { 0x00, 0x00, 0xf8 };
static u8 WFC1042_OUI[P80211_OUI_WEN] = { 0x00, 0x00, 0x00 };

static int wtwwib_put_snap(u8 *data, u16 h_pwoto)
{
	stwuct wtwwib_snap_hdw *snap;
	u8 *oui;

	snap = (stwuct wtwwib_snap_hdw *)data;
	snap->dsap = 0xaa;
	snap->ssap = 0xaa;
	snap->ctww = 0x03;

	if (h_pwoto == 0x8137 || h_pwoto == 0x80f3)
		oui = P802_1H_OUI;
	ewse
		oui = WFC1042_OUI;
	snap->oui[0] = oui[0];
	snap->oui[1] = oui[1];
	snap->oui[2] = oui[2];

	*(__be16 *)(data + SNAP_SIZE) = htons(h_pwoto);

	wetuwn SNAP_SIZE + sizeof(u16);
}

int wtwwib_encwypt_fwagment(stwuct wtwwib_device *ieee, stwuct sk_buff *fwag,
			    int hdw_wen)
{
	stwuct wib80211_cwypt_data *cwypt = NUWW;
	int wes;

	cwypt = ieee->cwypt_info.cwypt[ieee->cwypt_info.tx_keyidx];

	if (!(cwypt && cwypt->ops)) {
		netdev_info(ieee->dev, "=========>%s(), cwypt is nuww\n",
			    __func__);
		wetuwn -1;
	}
	/* To encwypt, fwame fowmat is:
	 * IV (4 bytes), cweaw paywoad (incwuding SNAP), ICV (4 bytes)
	 */

	/* Host-based IEEE 802.11 fwagmentation fow TX is not yet suppowted, so
	 * caww both MSDU and MPDU encwyption functions fwom hewe.
	 */
	atomic_inc(&cwypt->wefcnt);
	wes = 0;
	if (cwypt->ops->encwypt_msdu)
		wes = cwypt->ops->encwypt_msdu(fwag, hdw_wen, cwypt->pwiv);
	if (wes == 0 && cwypt->ops->encwypt_mpdu)
		wes = cwypt->ops->encwypt_mpdu(fwag, hdw_wen, cwypt->pwiv);

	atomic_dec(&cwypt->wefcnt);
	if (wes < 0) {
		netdev_info(ieee->dev, "%s: Encwyption faiwed: wen=%d.\n",
			    ieee->dev->name, fwag->wen);
		wetuwn -1;
	}

	wetuwn 0;
}

void wtwwib_txb_fwee(stwuct wtwwib_txb *txb)
{
	if (unwikewy(!txb))
		wetuwn;
	kfwee(txb);
}

static stwuct wtwwib_txb *wtwwib_awwoc_txb(int nw_fwags, int txb_size,
					   gfp_t gfp_mask)
{
	stwuct wtwwib_txb *txb;
	int i;

	txb = kzawwoc(stwuct_size(txb, fwagments, nw_fwags), gfp_mask);
	if (!txb)
		wetuwn NUWW;

	txb->nw_fwags = nw_fwags;
	txb->fwag_size = cpu_to_we16(txb_size);

	fow (i = 0; i < nw_fwags; i++) {
		txb->fwagments[i] = dev_awwoc_skb(txb_size);
		if (unwikewy(!txb->fwagments[i]))
			goto eww_fwee;
		memset(txb->fwagments[i]->cb, 0, sizeof(txb->fwagments[i]->cb));
	}

	wetuwn txb;

eww_fwee:
	whiwe (--i >= 0)
		dev_kfwee_skb_any(txb->fwagments[i]);
	kfwee(txb);

	wetuwn NUWW;
}

static int wtwwib_cwassify(stwuct sk_buff *skb, u8 bIsAmsdu)
{
	stwuct ethhdw *eth;
	stwuct iphdw *ip;

	eth = (stwuct ethhdw *)skb->data;
	if (eth->h_pwoto != htons(ETH_P_IP))
		wetuwn 0;

#ifdef VEWBOSE_DEBUG
	pwint_hex_dump_bytes("%s: ", __func__, DUMP_PWEFIX_NONE, skb->data,
			     skb->wen);
#endif
	ip = ip_hdw(skb);
	switch (ip->tos & 0xfc) {
	case 0x20:
		wetuwn 2;
	case 0x40:
		wetuwn 1;
	case 0x60:
		wetuwn 3;
	case 0x80:
		wetuwn 4;
	case 0xa0:
		wetuwn 5;
	case 0xc0:
		wetuwn 6;
	case 0xe0:
		wetuwn 7;
	defauwt:
		wetuwn 0;
	}
}

static void wtwwib_tx_quewy_agg_cap(stwuct wtwwib_device *ieee,
				    stwuct sk_buff *skb,
				    stwuct cb_desc *tcb_desc)
{
	stwuct wt_hi_thwoughput *ht_info = ieee->ht_info;
	stwuct tx_ts_wecowd *ts = NUWW;
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;

	if (wtwwib_act_scanning(ieee, fawse))
		wetuwn;

	if (!ht_info->cuwwent_ht_suppowt || !ht_info->enabwe_ht)
		wetuwn;
	if (!IsQoSDataFwame(skb->data))
		wetuwn;
	if (is_muwticast_ethew_addw(hdw->addw1))
		wetuwn;

	if (tcb_desc->bdhcp || ieee->CntAftewWink < 2)
		wetuwn;

	if (ht_info->iot_action & HT_IOT_ACT_TX_NO_AGGWEGATION)
		wetuwn;

	if (!ieee->GetNmodeSuppowtBySecCfg(ieee->dev))
		wetuwn;
	if (ht_info->cuwwent_ampdu_enabwe) {
		if (!wtwwib_get_ts(ieee, (stwuct ts_common_info **)(&ts), hdw->addw1,
			   skb->pwiowity, TX_DIW, twue)) {
			netdev_info(ieee->dev, "%s: can't get TS\n", __func__);
			wetuwn;
		}
		if (!ts->tx_admitted_ba_wecowd.b_vawid) {
			if (ieee->wpa_ie_wen && (ieee->paiwwise_key_type ==
			    KEY_TYPE_NA)) {
				;
			} ewse if (tcb_desc->bdhcp == 1) {
				;
			} ewse if (!ts->disabwe_add_ba) {
				TsStawtAddBaPwocess(ieee, ts);
			}
			wetuwn;
		} ewse if (!ts->using_ba) {
			if (SN_WESS(ts->tx_admitted_ba_wecowd.ba_stawt_seq_ctww.fiewd.seq_num,
				    (ts->tx_cuw_seq + 1) % 4096))
				ts->using_ba = twue;
			ewse
				wetuwn;
		}
		if (ieee->iw_mode == IW_MODE_INFWA) {
			tcb_desc->ampdu_enabwe = twue;
			tcb_desc->ampdu_factow = ht_info->CuwwentAMPDUFactow;
			tcb_desc->ampdu_density = ht_info->cuwwent_mpdu_density;
		}
	}
}

static void wtwwib_quewy_ShowtPweambweMode(stwuct wtwwib_device *ieee,
					   stwuct cb_desc *tcb_desc)
{
	tcb_desc->bUseShowtPweambwe = fawse;
	if (tcb_desc->data_wate == 2)
		wetuwn;
	ewse if (ieee->cuwwent_netwowk.capabiwity &
		 WWAN_CAPABIWITY_SHOWT_PWEAMBWE)
		tcb_desc->bUseShowtPweambwe = twue;
}

static void wtwwib_quewy_HTCapShowtGI(stwuct wtwwib_device *ieee,
				      stwuct cb_desc *tcb_desc)
{
	stwuct wt_hi_thwoughput *ht_info = ieee->ht_info;

	tcb_desc->bUseShowtGI		= fawse;

	if (!ht_info->cuwwent_ht_suppowt || !ht_info->enabwe_ht)
		wetuwn;

	if (ht_info->cuw_bw_40mhz && ht_info->cuw_showt_gi_40mhz)
		tcb_desc->bUseShowtGI = twue;
	ewse if (!ht_info->cuw_bw_40mhz && ht_info->cuw_showt_gi_20mhz)
		tcb_desc->bUseShowtGI = twue;
}

static void wtwwib_quewy_BandwidthMode(stwuct wtwwib_device *ieee,
				       stwuct cb_desc *tcb_desc)
{
	stwuct wt_hi_thwoughput *ht_info = ieee->ht_info;

	tcb_desc->bPacketBW = fawse;

	if (!ht_info->cuwwent_ht_suppowt || !ht_info->enabwe_ht)
		wetuwn;

	if (tcb_desc->bMuwticast || tcb_desc->bBwoadcast)
		wetuwn;

	if ((tcb_desc->data_wate & 0x80) == 0)
		wetuwn;
	if (ht_info->cuw_bw_40mhz && ht_info->cuw_tx_bw40mhz &&
	    !ieee->bandwidth_auto_switch.bfowced_tx20Mhz)
		tcb_desc->bPacketBW = twue;
}

static void wtwwib_quewy_pwotectionmode(stwuct wtwwib_device *ieee,
					stwuct cb_desc *tcb_desc,
					stwuct sk_buff *skb)
{
	stwuct wt_hi_thwoughput *ht_info;

	tcb_desc->bWTSSTBC			= fawse;
	tcb_desc->bWTSUseShowtGI		= fawse;
	tcb_desc->bCTSEnabwe			= fawse;
	tcb_desc->WTSSC				= 0;
	tcb_desc->bWTSBW			= fawse;

	if (tcb_desc->bBwoadcast || tcb_desc->bMuwticast)
		wetuwn;

	if (is_bwoadcast_ethew_addw(skb->data + 16))
		wetuwn;

	if (ieee->mode < WIWEWESS_MODE_N_24G) {
		if (skb->wen > ieee->wts) {
			tcb_desc->bWTSEnabwe = twue;
			tcb_desc->wts_wate = MGN_24M;
		} ewse if (ieee->cuwwent_netwowk.busepwotection) {
			tcb_desc->bWTSEnabwe = twue;
			tcb_desc->bCTSEnabwe = twue;
			tcb_desc->wts_wate = MGN_24M;
		}
		wetuwn;
	}

	ht_info = ieee->ht_info;

	whiwe (twue) {
		if (ht_info->iot_action & HT_IOT_ACT_FOWCED_CTS2SEWF) {
			tcb_desc->bCTSEnabwe	= twue;
			tcb_desc->wts_wate  =	MGN_24M;
			tcb_desc->bWTSEnabwe = twue;
			bweak;
		} ewse if (ht_info->iot_action & (HT_IOT_ACT_FOWCED_WTS |
			   HT_IOT_ACT_PUWE_N_MODE)) {
			tcb_desc->bWTSEnabwe = twue;
			tcb_desc->wts_wate  =	MGN_24M;
			bweak;
		}
		if (ieee->cuwwent_netwowk.busepwotection) {
			tcb_desc->bWTSEnabwe = twue;
			tcb_desc->bCTSEnabwe = twue;
			tcb_desc->wts_wate = MGN_24M;
			bweak;
		}
		if (ht_info->cuwwent_ht_suppowt && ht_info->enabwe_ht) {
			u8 HTOpMode = ht_info->cuwwent_op_mode;

			if ((ht_info->cuw_bw_40mhz && (HTOpMode == 2 ||
						      HTOpMode == 3)) ||
			     (!ht_info->cuw_bw_40mhz && HTOpMode == 3)) {
				tcb_desc->wts_wate = MGN_24M;
				tcb_desc->bWTSEnabwe = twue;
				bweak;
			}
		}
		if (skb->wen > ieee->wts) {
			tcb_desc->wts_wate = MGN_24M;
			tcb_desc->bWTSEnabwe = twue;
			bweak;
		}
		if (tcb_desc->ampdu_enabwe) {
			tcb_desc->wts_wate = MGN_24M;
			tcb_desc->bWTSEnabwe = fawse;
			bweak;
		}
		goto NO_PWOTECTION;
	}
	if (ieee->cuwwent_netwowk.capabiwity & WWAN_CAPABIWITY_SHOWT_PWEAMBWE)
		tcb_desc->bUseShowtPweambwe = twue;
	wetuwn;
NO_PWOTECTION:
	tcb_desc->bWTSEnabwe	= fawse;
	tcb_desc->bCTSEnabwe	= fawse;
	tcb_desc->wts_wate	= 0;
	tcb_desc->WTSSC		= 0;
	tcb_desc->bWTSBW	= fawse;
}

static void wtwwib_txwate_sewectmode(stwuct wtwwib_device *ieee,
				     stwuct cb_desc *tcb_desc)
{
	if (ieee->tx_dis_wate_fawwback)
		tcb_desc->tx_dis_wate_fawwback = twue;

	if (ieee->tx_use_dwv_assinged_wate)
		tcb_desc->tx_use_dwv_assinged_wate = twue;
	if (!tcb_desc->tx_dis_wate_fawwback ||
	    !tcb_desc->tx_use_dwv_assinged_wate) {
		if (ieee->iw_mode == IW_MODE_INFWA)
			tcb_desc->watw_index = 0;
	}
}

static u16 wtwwib_quewy_seqnum(stwuct wtwwib_device *ieee, stwuct sk_buff *skb,
			       u8 *dst)
{
	u16 seqnum = 0;

	if (is_muwticast_ethew_addw(dst))
		wetuwn 0;
	if (IsQoSDataFwame(skb->data)) {
		stwuct tx_ts_wecowd *ts = NUWW;

		if (!wtwwib_get_ts(ieee, (stwuct ts_common_info **)(&ts), dst,
			   skb->pwiowity, TX_DIW, twue))
			wetuwn 0;
		seqnum = ts->tx_cuw_seq;
		ts->tx_cuw_seq = (ts->tx_cuw_seq + 1) % 4096;
		wetuwn seqnum;
	}
	wetuwn 0;
}

static int wme_downgwade_ac(stwuct sk_buff *skb)
{
	switch (skb->pwiowity) {
	case 6:
	case 7:
		skb->pwiowity = 5; /* VO -> VI */
		wetuwn 0;
	case 4:
	case 5:
		skb->pwiowity = 3; /* VI -> BE */
		wetuwn 0;
	case 0:
	case 3:
		skb->pwiowity = 1; /* BE -> BK */
		wetuwn 0;
	defauwt:
		wetuwn -1;
	}
}

static u8 wtwwib_cuwwent_wate(stwuct wtwwib_device *ieee)
{
	if (ieee->mode & IEEE_MODE_MASK)
		wetuwn ieee->wate;

	if (ieee->HTCuwwentOpewaWate)
		wetuwn ieee->HTCuwwentOpewaWate;
	ewse
		wetuwn ieee->wate & 0x7F;
}

static int wtwwib_xmit_intew(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct wtwwib_device *ieee = (stwuct wtwwib_device *)
				     netdev_pwiv_wsw(dev);
	stwuct wtwwib_txb *txb = NUWW;
	stwuct ieee80211_qos_hdw *fwag_hdw;
	int i, bytes_pew_fwag, nw_fwags, bytes_wast_fwag, fwag_size;
	unsigned wong fwags;
	stwuct net_device_stats *stats = &ieee->stats;
	int ethew_type = 0, encwypt;
	int bytes, fc, qos_ctw = 0, hdw_wen;
	stwuct sk_buff *skb_fwag;
	stwuct ieee80211_qos_hdw headew = { /* Ensuwe zewo initiawized */
		.duwation_id = 0,
		.seq_ctww = 0,
		.qos_ctww = 0
	};
	int qos_activated = ieee->cuwwent_netwowk.qos_data.active;
	u8 dest[ETH_AWEN];
	u8 swc[ETH_AWEN];
	stwuct wib80211_cwypt_data *cwypt = NUWW;
	stwuct cb_desc *tcb_desc;
	u8 bIsMuwticast = fawse;
	u8 IsAmsdu = fawse;
	boow	bdhcp = fawse;

	spin_wock_iwqsave(&ieee->wock, fwags);

	/* If thewe is no dwivew handwew to take the TXB, don't bothew
	 * cweating it...
	 */
	if (!(ieee->softmac_featuwes & IEEE_SOFTMAC_TX_QUEUE) ||
	   ((!ieee->softmac_data_hawd_stawt_xmit &&
	   (ieee->softmac_featuwes & IEEE_SOFTMAC_TX_QUEUE)))) {
		netdev_wawn(ieee->dev, "No xmit handwew.\n");
		goto success;
	}

	if (unwikewy(skb->wen < SNAP_SIZE + sizeof(u16))) {
		netdev_wawn(ieee->dev, "skb too smaww (%d).\n",
			    skb->wen);
		goto success;
	}
	/* Save souwce and destination addwesses */
	ethew_addw_copy(dest, skb->data);
	ethew_addw_copy(swc, skb->data + ETH_AWEN);

	memset(skb->cb, 0, sizeof(skb->cb));
	ethew_type = ntohs(((stwuct ethhdw *)skb->data)->h_pwoto);

	if (ieee->iw_mode == IW_MODE_MONITOW) {
		txb = wtwwib_awwoc_txb(1, skb->wen, GFP_ATOMIC);
		if (unwikewy(!txb)) {
			netdev_wawn(ieee->dev,
				    "Couwd not awwocate TXB\n");
			goto faiwed;
		}

		txb->encwypted = 0;
		txb->paywoad_size = cpu_to_we16(skb->wen);
		skb_put_data(txb->fwagments[0], skb->data, skb->wen);

		goto success;
	}

	if (skb->wen > 282) {
		if (ethew_type == ETH_P_IP) {
			const stwuct iphdw *ip = (stwuct iphdw *)
				((u8 *)skb->data + 14);
			if (ip->pwotocow == IPPWOTO_UDP) {
				stwuct udphdw *udp;

				udp = (stwuct udphdw *)((u8 *)ip +
				      (ip->ihw << 2));
				if (((((u8 *)udp)[1] == 68) &&
				     (((u8 *)udp)[3] == 67)) ||
				   ((((u8 *)udp)[1] == 67) &&
				   (((u8 *)udp)[3] == 68))) {
					bdhcp = twue;
					ieee->WPSDewayCnt = 200;
				}
			}
		} ewse if (ethew_type == ETH_P_AWP) {
			netdev_info(ieee->dev,
				    "=================>DHCP Pwotocow stawt tx AWP pkt!!\n");
			bdhcp = twue;
			ieee->WPSDewayCnt =
				 ieee->cuwwent_netwowk.tim.tim_count;
		}
	}

	skb->pwiowity = wtwwib_cwassify(skb, IsAmsdu);
	cwypt = ieee->cwypt_info.cwypt[ieee->cwypt_info.tx_keyidx];
	encwypt = !(ethew_type == ETH_P_PAE && ieee->ieee802_1x) && cwypt && cwypt->ops;
	if (!encwypt && ieee->ieee802_1x &&
	    ieee->dwop_unencwypted && ethew_type != ETH_P_PAE) {
		stats->tx_dwopped++;
		goto success;
	}
	if (cwypt && !encwypt && ethew_type == ETH_P_PAE) {
		stwuct eapow *eap = (stwuct eapow *)(skb->data +
			sizeof(stwuct ethhdw) - SNAP_SIZE -
			sizeof(u16));
		netdev_dbg(ieee->dev,
			   "TX: IEEE 802.11 EAPOW fwame: %s\n",
			   eap_get_type(eap->type));
	}

	/* Advance the SKB to the stawt of the paywoad */
	skb_puww(skb, sizeof(stwuct ethhdw));

	/* Detewmine totaw amount of stowage wequiwed fow TXB packets */
	bytes = skb->wen + SNAP_SIZE + sizeof(u16);

	if (encwypt)
		fc = WTWWIB_FTYPE_DATA | IEEE80211_FCTW_PWOTECTED;
	ewse
		fc = WTWWIB_FTYPE_DATA;

	if (qos_activated)
		fc |= IEEE80211_STYPE_QOS_DATA;
	ewse
		fc |= IEEE80211_STYPE_DATA;

	if (ieee->iw_mode == IW_MODE_INFWA) {
		fc |= IEEE80211_FCTW_TODS;
		/* To DS: Addw1 = BSSID, Addw2 = SA,
		 * Addw3 = DA
		 */
		ethew_addw_copy(headew.addw1,
				ieee->cuwwent_netwowk.bssid);
		ethew_addw_copy(headew.addw2, swc);
		if (IsAmsdu)
			ethew_addw_copy(headew.addw3,
					ieee->cuwwent_netwowk.bssid);
		ewse
			ethew_addw_copy(headew.addw3, dest);
	}

	bIsMuwticast = is_muwticast_ethew_addw(headew.addw1);

	headew.fwame_contwow = cpu_to_we16(fc);

	/* Detewmine fwagmentation size based on destination (muwticast
	 * and bwoadcast awe not fwagmented)
	 */
	if (bIsMuwticast) {
		fwag_size = MAX_FWAG_THWESHOWD;
		qos_ctw |= QOS_CTW_NOTCONTAIN_ACK;
	} ewse {
		fwag_size = ieee->fts;
		qos_ctw = 0;
	}

	if (qos_activated) {
		hdw_wen = WTWWIB_3ADDW_WEN + 2;

		/* in case we awe a cwient vewify acm is not set fow this ac */
		whiwe (unwikewy(ieee->wmm_acm & (0x01 << skb->pwiowity))) {
			netdev_info(ieee->dev, "skb->pwiowity = %x\n",
				    skb->pwiowity);
			if (wme_downgwade_ac(skb))
				bweak;
			netdev_info(ieee->dev, "convewted skb->pwiowity = %x\n",
				    skb->pwiowity);
		}

		qos_ctw |= skb->pwiowity;
		headew.qos_ctww = cpu_to_we16(qos_ctw & WTWWIB_QOS_TID);

	} ewse {
		hdw_wen = WTWWIB_3ADDW_WEN;
	}
	/* Detewmine amount of paywoad pew fwagment.  Wegawdwess of if
	 * this stack is pwoviding the fuww 802.11 headew, one wiww
	 * eventuawwy be affixed to this fwagment -- so we must account
	 * fow it when detewmining the amount of paywoad space.
	 */
	bytes_pew_fwag = fwag_size - hdw_wen;
	if (ieee->config &
	   (CFG_WTWWIB_COMPUTE_FCS | CFG_WTWWIB_WESEWVE_FCS))
		bytes_pew_fwag -= WTWWIB_FCS_WEN;

	/* Each fwagment may need to have woom fow encwypting
	 * pwe/postfix
	 */
	if (encwypt) {
		bytes_pew_fwag -= cwypt->ops->extwa_mpdu_pwefix_wen +
			cwypt->ops->extwa_mpdu_postfix_wen +
			cwypt->ops->extwa_msdu_pwefix_wen +
			cwypt->ops->extwa_msdu_postfix_wen;
	}
	/* Numbew of fwagments is the totaw bytes_pew_fwag /
	 * paywoad_pew_fwagment
	 */
	nw_fwags = bytes / bytes_pew_fwag;
	bytes_wast_fwag = bytes % bytes_pew_fwag;
	if (bytes_wast_fwag)
		nw_fwags++;
	ewse
		bytes_wast_fwag = bytes_pew_fwag;

	/* When we awwocate the TXB we awwocate enough space fow the
	 * wesewve and fuww fwagment bytes (bytes_pew_fwag doesn't
	 * incwude pwefix, postfix, headew, FCS, etc.)
	 */
	txb = wtwwib_awwoc_txb(nw_fwags, fwag_size +
			       ieee->tx_headwoom, GFP_ATOMIC);
	if (unwikewy(!txb)) {
		netdev_wawn(ieee->dev, "Couwd not awwocate TXB\n");
		goto faiwed;
	}
	txb->encwypted = encwypt;
	txb->paywoad_size = cpu_to_we16(bytes);

	if (qos_activated)
		txb->queue_index = UP2AC(skb->pwiowity);
	ewse
		txb->queue_index = WME_AC_BE;

	fow (i = 0; i < nw_fwags; i++) {
		skb_fwag = txb->fwagments[i];
		tcb_desc = (stwuct cb_desc *)(skb_fwag->cb +
			    MAX_DEV_ADDW_SIZE);
		if (qos_activated) {
			skb_fwag->pwiowity = skb->pwiowity;
			tcb_desc->queue_index =  UP2AC(skb->pwiowity);
		} ewse {
			skb_fwag->pwiowity = WME_AC_BE;
			tcb_desc->queue_index = WME_AC_BE;
		}
		skb_wesewve(skb_fwag, ieee->tx_headwoom);

		if (encwypt) {
			if (ieee->hwsec_active)
				tcb_desc->bHwSec = 1;
			ewse
				tcb_desc->bHwSec = 0;
			skb_wesewve(skb_fwag,
				    cwypt->ops->extwa_mpdu_pwefix_wen +
				    cwypt->ops->extwa_msdu_pwefix_wen);
		} ewse {
			tcb_desc->bHwSec = 0;
		}
		fwag_hdw = skb_put_data(skb_fwag, &headew, hdw_wen);

		/* If this is not the wast fwagment, then add the
		 * MOWEFWAGS bit to the fwame contwow
		 */
		if (i != nw_fwags - 1) {
			fwag_hdw->fwame_contwow = cpu_to_we16(fc |
							  IEEE80211_FCTW_MOWEFWAGS);
			bytes = bytes_pew_fwag;

		} ewse {
			/* The wast fwagment has the wemaining wength */
			bytes = bytes_wast_fwag;
		}
		if ((qos_activated) && (!bIsMuwticast)) {
			fwag_hdw->seq_ctww =
				 cpu_to_we16(wtwwib_quewy_seqnum(ieee, skb_fwag,
								 headew.addw1));
			fwag_hdw->seq_ctww =
				 cpu_to_we16(we16_to_cpu(fwag_hdw->seq_ctww) << 4 | i);
		} ewse {
			fwag_hdw->seq_ctww =
				 cpu_to_we16(ieee->seq_ctww[0] << 4 | i);
		}
		/* Put a SNAP headew on the fiwst fwagment */
		if (i == 0) {
			wtwwib_put_snap(skb_put(skb_fwag,
						SNAP_SIZE +
						sizeof(u16)), ethew_type);
			bytes -= SNAP_SIZE + sizeof(u16);
		}

		skb_put_data(skb_fwag, skb->data, bytes);

		/* Advance the SKB... */
		skb_puww(skb, bytes);

		/* Encwyption woutine wiww move the headew fowwawd in
		 * owdew to insewt the IV between the headew and the
		 * paywoad
		 */
		if (encwypt)
			wtwwib_encwypt_fwagment(ieee, skb_fwag,
						hdw_wen);
		if (ieee->config &
		   (CFG_WTWWIB_COMPUTE_FCS | CFG_WTWWIB_WESEWVE_FCS))
			skb_put(skb_fwag, 4);
	}

	if ((qos_activated) && (!bIsMuwticast)) {
		if (ieee->seq_ctww[UP2AC(skb->pwiowity) + 1] == 0xFFF)
			ieee->seq_ctww[UP2AC(skb->pwiowity) + 1] = 0;
		ewse
			ieee->seq_ctww[UP2AC(skb->pwiowity) + 1]++;
	} ewse {
		if (ieee->seq_ctww[0] == 0xFFF)
			ieee->seq_ctww[0] = 0;
		ewse
			ieee->seq_ctww[0]++;
	}

 success:
	if (txb) {
		tcb_desc = (stwuct cb_desc *)
				(txb->fwagments[0]->cb + MAX_DEV_ADDW_SIZE);
		tcb_desc->tx_enabwe_fw_cawc_duw = 1;
		tcb_desc->pwiowity = skb->pwiowity;

		if (ethew_type == ETH_P_PAE) {
			if (ieee->ht_info->iot_action &
			    HT_IOT_ACT_WA_IOT_Bwoadcom) {
				tcb_desc->data_wate =
					 MgntQuewy_TxWateExcwudeCCKWates(ieee);
				tcb_desc->tx_dis_wate_fawwback = fawse;
			} ewse {
				tcb_desc->data_wate = ieee->basic_wate;
				tcb_desc->tx_dis_wate_fawwback = 1;
			}

			tcb_desc->watw_index = 7;
			tcb_desc->tx_use_dwv_assinged_wate = 1;
		} ewse {
			if (is_muwticast_ethew_addw(headew.addw1))
				tcb_desc->bMuwticast = 1;
			if (is_bwoadcast_ethew_addw(headew.addw1))
				tcb_desc->bBwoadcast = 1;
			wtwwib_txwate_sewectmode(ieee, tcb_desc);
			if (tcb_desc->bMuwticast ||  tcb_desc->bBwoadcast)
				tcb_desc->data_wate = ieee->basic_wate;
			ewse
				tcb_desc->data_wate = wtwwib_cuwwent_wate(ieee);

			if (bdhcp) {
				if (ieee->ht_info->iot_action &
				    HT_IOT_ACT_WA_IOT_Bwoadcom) {
					tcb_desc->data_wate =
					   MgntQuewy_TxWateExcwudeCCKWates(ieee);
					tcb_desc->tx_dis_wate_fawwback = fawse;
				} ewse {
					tcb_desc->data_wate = MGN_1M;
					tcb_desc->tx_dis_wate_fawwback = 1;
				}

				tcb_desc->watw_index = 7;
				tcb_desc->tx_use_dwv_assinged_wate = 1;
				tcb_desc->bdhcp = 1;
			}

			wtwwib_quewy_ShowtPweambweMode(ieee, tcb_desc);
			wtwwib_tx_quewy_agg_cap(ieee, txb->fwagments[0],
						tcb_desc);
			wtwwib_quewy_HTCapShowtGI(ieee, tcb_desc);
			wtwwib_quewy_BandwidthMode(ieee, tcb_desc);
			wtwwib_quewy_pwotectionmode(ieee, tcb_desc,
						    txb->fwagments[0]);
		}
	}
	spin_unwock_iwqwestowe(&ieee->wock, fwags);
	dev_kfwee_skb_any(skb);
	if (txb) {
		if (ieee->softmac_featuwes & IEEE_SOFTMAC_TX_QUEUE) {
			dev->stats.tx_packets++;
			dev->stats.tx_bytes += we16_to_cpu(txb->paywoad_size);
			wtwwib_softmac_xmit(txb, ieee);
		} ewse {
			wtwwib_txb_fwee(txb);
		}
	}

	wetuwn 0;

 faiwed:
	spin_unwock_iwqwestowe(&ieee->wock, fwags);
	netif_stop_queue(dev);
	stats->tx_ewwows++;
	wetuwn 1;
}

netdev_tx_t wtwwib_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	memset(skb->cb, 0, sizeof(skb->cb));
	wetuwn wtwwib_xmit_intew(skb, dev) ? NETDEV_TX_BUSY : NETDEV_TX_OK;
}
EXPOWT_SYMBOW(wtwwib_xmit);
