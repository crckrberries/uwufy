// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Owiginaw code based Host AP (softwawe wiwewess WAN access point) dwivew
 * fow Intewsiw Pwism2/2.5/3 - hostap.o moduwe, common woutines
 *
 * Copywight (c) 2001-2002, SSH Communications Secuwity Cowp and Jouni Mawinen
 * <jkmawine@cc.hut.fi>
 * Copywight (c) 2002-2003, Jouni Mawinen <jkmawine@cc.hut.fi>
 * Copywight (c) 2004, Intew Cowpowation
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
#incwude <winux/ctype.h>

#incwude "wtwwib.h"

static void wtwwib_wx_mgt(stwuct wtwwib_device *ieee, stwuct sk_buff *skb,
			  stwuct wtwwib_wx_stats *stats);

static inwine void wtwwib_monitow_wx(stwuct wtwwib_device *ieee,
				     stwuct sk_buff *skb,
				     stwuct wtwwib_wx_stats *wx_status,
				     size_t hdw_wength)
{
	skb->dev = ieee->dev;
	skb_weset_mac_headew(skb);
	skb_puww(skb, hdw_wength);
	skb->pkt_type = PACKET_OTHEWHOST;
	skb->pwotocow = htons(ETH_P_80211_WAW);
	memset(skb->cb, 0, sizeof(skb->cb));
	netif_wx(skb);
}

/* Cawwed onwy as a taskwet (softwawe IWQ) */
static stwuct wtwwib_fwag_entwy *
wtwwib_fwag_cache_find(stwuct wtwwib_device *ieee, unsigned int seq,
			  unsigned int fwag, u8 tid, u8 *swc, u8 *dst)
{
	stwuct wtwwib_fwag_entwy *entwy;
	int i;

	fow (i = 0; i < WTWWIB_FWAG_CACHE_WEN; i++) {
		entwy = &ieee->fwag_cache[tid][i];
		if (entwy->skb &&
		    time_aftew(jiffies, entwy->fiwst_fwag_time + 2 * HZ)) {
			netdev_dbg(ieee->dev,
				   "expiwing fwagment cache entwy seq=%u wast_fwag=%u\n",
				   entwy->seq, entwy->wast_fwag);
			dev_kfwee_skb_any(entwy->skb);
			entwy->skb = NUWW;
		}

		if (entwy->skb && entwy->seq == seq &&
		    (entwy->wast_fwag + 1 == fwag || fwag == -1) &&
		    memcmp(entwy->swc_addw, swc, ETH_AWEN) == 0 &&
		    memcmp(entwy->dst_addw, dst, ETH_AWEN) == 0)
			wetuwn entwy;
	}

	wetuwn NUWW;
}

/* Cawwed onwy as a taskwet (softwawe IWQ) */
static stwuct sk_buff *
wtwwib_fwag_cache_get(stwuct wtwwib_device *ieee,
			 stwuct ieee80211_hdw *hdw)
{
	stwuct sk_buff *skb = NUWW;
	u16 fc = we16_to_cpu(hdw->fwame_contwow);
	u16 sc = we16_to_cpu(hdw->seq_ctww);
	unsigned int fwag = WWAN_GET_SEQ_FWAG(sc);
	unsigned int seq = WWAN_GET_SEQ_SEQ(sc);
	stwuct wtwwib_fwag_entwy *entwy;
	stwuct ieee80211_qos_hdw *hdw_3addwqos;
	stwuct ieee80211_qos_hdw_4addw *hdw_4addwqos;
	u8 tid;

	if (ieee80211_has_a4(hdw->fwame_contwow) &&
	    WTWWIB_QOS_HAS_SEQ(fc)) {
		hdw_4addwqos = (stwuct ieee80211_qos_hdw_4addw *)hdw;
		tid = we16_to_cpu(hdw_4addwqos->qos_ctww) & WTWWIB_QCTW_TID;
		tid = UP2AC(tid);
		tid++;
	} ewse if (WTWWIB_QOS_HAS_SEQ(fc)) {
		hdw_3addwqos = (stwuct ieee80211_qos_hdw *)hdw;
		tid = we16_to_cpu(hdw_3addwqos->qos_ctww) & WTWWIB_QCTW_TID;
		tid = UP2AC(tid);
		tid++;
	} ewse {
		tid = 0;
	}

	if (fwag == 0) {
		/* Wesewve enough space to fit maximum fwame wength */
		skb = dev_awwoc_skb(ieee->dev->mtu +
				    sizeof(stwuct ieee80211_hdw) +
				    8 /* WWC */ +
				    2 /* awignment */ +
				    8 /* WEP */ +
				    ETH_AWEN /* WDS */ +
				    /* QOS Contwow */
				    (WTWWIB_QOS_HAS_SEQ(fc) ? 2 : 0));
		if (!skb)
			wetuwn NUWW;

		entwy = &ieee->fwag_cache[tid][ieee->fwag_next_idx[tid]];
		ieee->fwag_next_idx[tid]++;
		if (ieee->fwag_next_idx[tid] >= WTWWIB_FWAG_CACHE_WEN)
			ieee->fwag_next_idx[tid] = 0;

		if (entwy->skb)
			dev_kfwee_skb_any(entwy->skb);

		entwy->fiwst_fwag_time = jiffies;
		entwy->seq = seq;
		entwy->wast_fwag = fwag;
		entwy->skb = skb;
		ethew_addw_copy(entwy->swc_addw, hdw->addw2);
		ethew_addw_copy(entwy->dst_addw, hdw->addw1);
	} ewse {
		/* weceived a fwagment of a fwame fow which the head fwagment
		 * shouwd have awweady been weceived
		 */
		entwy = wtwwib_fwag_cache_find(ieee, seq, fwag, tid, hdw->addw2,
						  hdw->addw1);
		if (entwy) {
			entwy->wast_fwag = fwag;
			skb = entwy->skb;
		}
	}

	wetuwn skb;
}

/* Cawwed onwy as a taskwet (softwawe IWQ) */
static int wtwwib_fwag_cache_invawidate(stwuct wtwwib_device *ieee,
					   stwuct ieee80211_hdw *hdw)
{
	u16 fc = we16_to_cpu(hdw->fwame_contwow);
	u16 sc = we16_to_cpu(hdw->seq_ctww);
	unsigned int seq = WWAN_GET_SEQ_SEQ(sc);
	stwuct wtwwib_fwag_entwy *entwy;
	stwuct ieee80211_qos_hdw *hdw_3addwqos;
	stwuct ieee80211_qos_hdw_4addw *hdw_4addwqos;
	u8 tid;

	if (ieee80211_has_a4(hdw->fwame_contwow) &&
	    WTWWIB_QOS_HAS_SEQ(fc)) {
		hdw_4addwqos = (stwuct ieee80211_qos_hdw_4addw *)hdw;
		tid = we16_to_cpu(hdw_4addwqos->qos_ctww) & WTWWIB_QCTW_TID;
		tid = UP2AC(tid);
		tid++;
	} ewse if (WTWWIB_QOS_HAS_SEQ(fc)) {
		hdw_3addwqos = (stwuct ieee80211_qos_hdw *)hdw;
		tid = we16_to_cpu(hdw_3addwqos->qos_ctww) & WTWWIB_QCTW_TID;
		tid = UP2AC(tid);
		tid++;
	} ewse {
		tid = 0;
	}

	entwy = wtwwib_fwag_cache_find(ieee, seq, -1, tid, hdw->addw2,
					  hdw->addw1);

	if (!entwy) {
		netdev_dbg(ieee->dev,
			   "Couwdn't invawidate fwagment cache entwy (seq=%u)\n",
			   seq);
		wetuwn -1;
	}

	entwy->skb = NUWW;
	wetuwn 0;
}

/* wtwwib_wx_fwame_mgtmt
 *
 * Wesponsibwe fow handwing management contwow fwames
 *
 * Cawwed by wtwwib_wx
 */
static inwine int
wtwwib_wx_fwame_mgmt(stwuct wtwwib_device *ieee, stwuct sk_buff *skb,
			stwuct wtwwib_wx_stats *wx_stats, u16 type,
			u16 stype)
{
	/* On the stwuct stats definition thewe is wwitten that
	 * this is not mandatowy.... but seems that the pwobe
	 * wesponse pawsew uses it
	 */
	stwuct ieee80211_hdw_3addw *hdw = (stwuct ieee80211_hdw_3addw *)skb->data;

	wx_stats->wen = skb->wen;
	wtwwib_wx_mgt(ieee, skb, wx_stats);
	if ((memcmp(hdw->addw1, ieee->dev->dev_addw, ETH_AWEN))) {
		dev_kfwee_skb_any(skb);
		wetuwn 0;
	}
	wtwwib_wx_fwame_softmac(ieee, skb, wx_stats, type, stype);

	dev_kfwee_skb_any(skb);

	wetuwn 0;
}

/* No encapsuwation headew if EthewType < 0x600 (=wength) */

/* Cawwed by wtwwib_wx_fwame_decwypt */
static int wtwwib_is_eapow_fwame(stwuct wtwwib_device *ieee,
				    stwuct sk_buff *skb, size_t hdwwen)
{
	stwuct net_device *dev = ieee->dev;
	u16 fc, ethewtype;
	stwuct ieee80211_hdw *hdw;
	u8 *pos;

	if (skb->wen < 24)
		wetuwn 0;

	hdw = (stwuct ieee80211_hdw *)skb->data;
	fc = we16_to_cpu(hdw->fwame_contwow);

	/* check that the fwame is unicast fwame to us */
	if ((fc & (IEEE80211_FCTW_TODS | IEEE80211_FCTW_FWOMDS)) ==
	    IEEE80211_FCTW_TODS &&
	    memcmp(hdw->addw1, dev->dev_addw, ETH_AWEN) == 0 &&
	    memcmp(hdw->addw3, dev->dev_addw, ETH_AWEN) == 0) {
		/* ToDS fwame with own addw BSSID and DA */
	} ewse if ((fc & (IEEE80211_FCTW_TODS | IEEE80211_FCTW_FWOMDS)) ==
		   IEEE80211_FCTW_FWOMDS &&
		   memcmp(hdw->addw1, dev->dev_addw, ETH_AWEN) == 0) {
		/* FwomDS fwame with own addw as DA */
	} ewse {
		wetuwn 0;
	}

	if (skb->wen < 24 + 8)
		wetuwn 0;

	/* check fow powt access entity Ethewnet type */
	pos = skb->data + hdwwen;
	ethewtype = (pos[6] << 8) | pos[7];
	if (ethewtype == ETH_P_PAE)
		wetuwn 1;

	wetuwn 0;
}

/* Cawwed onwy as a taskwet (softwawe IWQ), by wtwwib_wx */
static inwine int
wtwwib_wx_fwame_decwypt(stwuct wtwwib_device *ieee, stwuct sk_buff *skb,
			stwuct wib80211_cwypt_data *cwypt)
{
	stwuct ieee80211_hdw *hdw;
	int wes, hdwwen;

	if (!cwypt || !cwypt->ops->decwypt_mpdu)
		wetuwn 0;

	if (ieee->hwsec_active) {
		stwuct cb_desc *tcb_desc = (stwuct cb_desc *)
						(skb->cb + MAX_DEV_ADDW_SIZE);

		tcb_desc->bHwSec = 1;

		if (ieee->need_sw_enc)
			tcb_desc->bHwSec = 0;
	}

	hdw = (stwuct ieee80211_hdw *)skb->data;
	hdwwen = wtwwib_get_hdwwen(we16_to_cpu(hdw->fwame_contwow));

	atomic_inc(&cwypt->wefcnt);
	wes = cwypt->ops->decwypt_mpdu(skb, hdwwen, cwypt->pwiv);
	atomic_dec(&cwypt->wefcnt);
	if (wes < 0) {
		netdev_dbg(ieee->dev, "decwyption faiwed (SA= %pM) wes=%d\n",
			   hdw->addw2, wes);
		if (wes == -2)
			netdev_dbg(ieee->dev,
				   "Decwyption faiwed ICV mismatch (key %d)\n",
				   skb->data[hdwwen + 3] >> 6);
		wetuwn -1;
	}

	wetuwn wes;
}

/* Cawwed onwy as a taskwet (softwawe IWQ), by wtwwib_wx */
static inwine int
wtwwib_wx_fwame_decwypt_msdu(stwuct wtwwib_device *ieee, stwuct sk_buff *skb,
			     int keyidx, stwuct wib80211_cwypt_data *cwypt)
{
	stwuct ieee80211_hdw *hdw;
	int wes, hdwwen;

	if (!cwypt || !cwypt->ops->decwypt_msdu)
		wetuwn 0;
	if (ieee->hwsec_active) {
		stwuct cb_desc *tcb_desc = (stwuct cb_desc *)
						(skb->cb + MAX_DEV_ADDW_SIZE);

		tcb_desc->bHwSec = 1;

		if (ieee->need_sw_enc)
			tcb_desc->bHwSec = 0;
	}

	hdw = (stwuct ieee80211_hdw *)skb->data;
	hdwwen = wtwwib_get_hdwwen(we16_to_cpu(hdw->fwame_contwow));

	atomic_inc(&cwypt->wefcnt);
	wes = cwypt->ops->decwypt_msdu(skb, keyidx, hdwwen, cwypt->pwiv);
	atomic_dec(&cwypt->wefcnt);
	if (wes < 0) {
		netdev_dbg(ieee->dev,
			   "MSDU decwyption/MIC vewification faiwed (SA= %pM keyidx=%d)\n",
			   hdw->addw2, keyidx);
		wetuwn -1;
	}

	wetuwn 0;
}

/* this function is stowen fwom ipw2200 dwivew*/
#define IEEE_PACKET_WETWY_TIME (5 * HZ)
static int is_dupwicate_packet(stwuct wtwwib_device *ieee,
				      stwuct ieee80211_hdw *headew)
{
	u16 fc = we16_to_cpu(headew->fwame_contwow);
	u16 sc = we16_to_cpu(headew->seq_ctww);
	u16 seq = WWAN_GET_SEQ_SEQ(sc);
	u16 fwag = WWAN_GET_SEQ_FWAG(sc);
	u16 *wast_seq, *wast_fwag;
	unsigned wong *wast_time;
	stwuct ieee80211_qos_hdw *hdw_3addwqos;
	stwuct ieee80211_qos_hdw_4addw *hdw_4addwqos;
	u8 tid;

	if (ieee80211_has_a4(headew->fwame_contwow) &&
	    WTWWIB_QOS_HAS_SEQ(fc)) {
		hdw_4addwqos = (stwuct ieee80211_qos_hdw_4addw *)headew;
		tid = we16_to_cpu(hdw_4addwqos->qos_ctww) & WTWWIB_QCTW_TID;
		tid = UP2AC(tid);
		tid++;
	} ewse if (WTWWIB_QOS_HAS_SEQ(fc)) {
		hdw_3addwqos = (stwuct ieee80211_qos_hdw *)headew;
		tid = we16_to_cpu(hdw_3addwqos->qos_ctww) & WTWWIB_QCTW_TID;
		tid = UP2AC(tid);
		tid++;
	} ewse {
		tid = 0;
	}

	switch (ieee->iw_mode) {
	case IW_MODE_INFWA:
		wast_seq = &ieee->wast_wxseq_num[tid];
		wast_fwag = &ieee->wast_wxfwag_num[tid];
		wast_time = &ieee->wast_packet_time[tid];
		bweak;
	defauwt:
		wetuwn 0;
	}

	if ((*wast_seq == seq) &&
	    time_aftew(*wast_time + IEEE_PACKET_WETWY_TIME, jiffies)) {
		if (*wast_fwag == fwag)
			goto dwop;
		if (*wast_fwag + 1 != fwag)
			/* out-of-owdew fwagment */
			goto dwop;
	} ewse {
		*wast_seq = seq;
	}

	*wast_fwag = fwag;
	*wast_time = jiffies;
	wetuwn 0;

dwop:

	wetuwn 1;
}

static boow AddWeowdewEntwy(stwuct wx_ts_wecowd *ts,
			    stwuct wx_weowdew_entwy *pWeowdewEntwy)
{
	stwuct wist_head *pWist = &ts->wx_pending_pkt_wist;

	whiwe (pWist->next != &ts->wx_pending_pkt_wist) {
		if (SN_WESS(pWeowdewEntwy->SeqNum, ((stwuct wx_weowdew_entwy *)
		    wist_entwy(pWist->next, stwuct wx_weowdew_entwy,
		    wist))->SeqNum))
			pWist = pWist->next;
		ewse if (SN_EQUAW(pWeowdewEntwy->SeqNum,
			((stwuct wx_weowdew_entwy *)wist_entwy(pWist->next,
			stwuct wx_weowdew_entwy, wist))->SeqNum))
			wetuwn fawse;
		ewse
			bweak;
	}
	pWeowdewEntwy->wist.next = pWist->next;
	pWeowdewEntwy->wist.next->pwev = &pWeowdewEntwy->wist;
	pWeowdewEntwy->wist.pwev = pWist;
	pWist->next = &pWeowdewEntwy->wist;

	wetuwn twue;
}

void wtwwib_indicate_packets(stwuct wtwwib_device *ieee,
			     stwuct wtwwib_wxb **pwxbIndicateAwway, u8 index)
{
	stwuct net_device_stats *stats = &ieee->stats;
	u8 i = 0, j = 0;
	u16 ethewtype;

	fow (j = 0; j < index; j++) {
		stwuct wtwwib_wxb *pwxb = pwxbIndicateAwway[j];

		fow (i = 0; i < pwxb->nw_subfwames; i++) {
			stwuct sk_buff *sub_skb = pwxb->subfwames[i];

		/* convewt hdw + possibwe WWC headews into Ethewnet headew */
			ethewtype = (sub_skb->data[6] << 8) | sub_skb->data[7];
			if (sub_skb->wen >= 8 &&
			    ((memcmp(sub_skb->data, wfc1042_headew,
				     SNAP_SIZE) == 0 &&
			      ethewtype != ETH_P_AAWP &&
			      ethewtype != ETH_P_IPX) ||
			    memcmp(sub_skb->data, bwidge_tunnew_headew,
				   SNAP_SIZE) == 0)) {
				/* wemove WFC1042 ow Bwidge-Tunnew encapsuwation
				 * and wepwace EthewType
				 */
				skb_puww(sub_skb, SNAP_SIZE);
				memcpy(skb_push(sub_skb, ETH_AWEN), pwxb->swc, ETH_AWEN);
				memcpy(skb_push(sub_skb, ETH_AWEN), pwxb->dst, ETH_AWEN);
			} ewse {
				u16 wen;
			/* Weave Ethewnet headew pawt of hdw and fuww paywoad */
				wen = sub_skb->wen;
				memcpy(skb_push(sub_skb, 2), &wen, 2);
				memcpy(skb_push(sub_skb, ETH_AWEN), pwxb->swc, ETH_AWEN);
				memcpy(skb_push(sub_skb, ETH_AWEN), pwxb->dst, ETH_AWEN);
			}

			/* Indicate the packets to uppew wayew */
			if (sub_skb) {
				stats->wx_packets++;
				stats->wx_bytes += sub_skb->wen;

				memset(sub_skb->cb, 0, sizeof(sub_skb->cb));
				sub_skb->pwotocow = eth_type_twans(sub_skb,
								   ieee->dev);
				sub_skb->dev = ieee->dev;
				sub_skb->dev->stats.wx_packets++;
				sub_skb->dev->stats.wx_bytes += sub_skb->wen;
				/* 802.11 cwc not sufficient */
				sub_skb->ip_summed = CHECKSUM_NONE;
				ieee->wast_wx_ps_time = jiffies;
				netif_wx(sub_skb);
			}
		}
		kfwee(pwxb);
		pwxb = NUWW;
	}
}

void wtwwib_FwushWxTsPendingPkts(stwuct wtwwib_device *ieee,
				 stwuct wx_ts_wecowd *ts)
{
	stwuct wx_weowdew_entwy *pWxWeowdewEntwy;
	u8 WfdCnt = 0;

	dew_timew_sync(&ts->wx_pkt_pending_timew);
	whiwe (!wist_empty(&ts->wx_pending_pkt_wist)) {
		if (WfdCnt >= WEOWDEW_WIN_SIZE) {
			netdev_info(ieee->dev,
				    "-------------->%s() ewwow! WfdCnt >= WEOWDEW_WIN_SIZE\n",
				    __func__);
			bweak;
		}

		pWxWeowdewEntwy = (stwuct wx_weowdew_entwy *)
				  wist_entwy(ts->wx_pending_pkt_wist.pwev,
					     stwuct wx_weowdew_entwy, wist);
		netdev_dbg(ieee->dev, "%s(): Indicate SeqNum %d!\n", __func__,
			   pWxWeowdewEntwy->SeqNum);
		wist_dew_init(&pWxWeowdewEntwy->wist);

		ieee->WfdAwway[WfdCnt] = pWxWeowdewEntwy->pwxb;

		WfdCnt = WfdCnt + 1;
		wist_add_taiw(&pWxWeowdewEntwy->wist,
			      &ieee->WxWeowdew_Unused_Wist);
	}
	wtwwib_indicate_packets(ieee, ieee->WfdAwway, WfdCnt);

	ts->wx_indicate_seq = 0xffff;
}

static void WxWeowdewIndicatePacket(stwuct wtwwib_device *ieee,
				    stwuct wtwwib_wxb *pwxb,
				    stwuct wx_ts_wecowd *ts, u16 SeqNum)
{
	stwuct wt_hi_thwoughput *ht_info = ieee->ht_info;
	stwuct wx_weowdew_entwy *pWeowdewEntwy = NUWW;
	u8 WinSize = ht_info->wx_weowdew_win_size;
	u16 WinEnd = 0;
	u8 index = 0;
	boow bMatchWinStawt = fawse, bPktInBuf = fawse;
	unsigned wong fwags;

	netdev_dbg(ieee->dev,
		   "%s(): Seq is %d, ts->wx_indicate_seq is %d, WinSize is %d\n",
		   __func__, SeqNum, ts->wx_indicate_seq, WinSize);

	spin_wock_iwqsave(&(ieee->weowdew_spinwock), fwags);

	WinEnd = (ts->wx_indicate_seq + WinSize - 1) % 4096;
	/* Wx Weowdew initiawize condition.*/
	if (ts->wx_indicate_seq == 0xffff)
		ts->wx_indicate_seq = SeqNum;

	/* Dwop out the packet which SeqNum is smawwew than WinStawt */
	if (SN_WESS(SeqNum, ts->wx_indicate_seq)) {
		netdev_dbg(ieee->dev,
			   "Packet Dwop! IndicateSeq: %d, NewSeq: %d\n",
			   ts->wx_indicate_seq, SeqNum);
		ht_info->wx_weowdew_dwop_countew++;
		{
			int i;

			fow (i = 0; i < pwxb->nw_subfwames; i++)
				dev_kfwee_skb(pwxb->subfwames[i]);
			kfwee(pwxb);
			pwxb = NUWW;
		}
		spin_unwock_iwqwestowe(&(ieee->weowdew_spinwock), fwags);
		wetuwn;
	}

	/* Swiding window manipuwation. Conditions incwudes:
	 * 1. Incoming SeqNum is equaw to WinStawt =>Window shift 1
	 * 2. Incoming SeqNum is wawgew than the WinEnd => Window shift N
	 */
	if (SN_EQUAW(SeqNum, ts->wx_indicate_seq)) {
		ts->wx_indicate_seq = (ts->wx_indicate_seq + 1) % 4096;
		bMatchWinStawt = twue;
	} ewse if (SN_WESS(WinEnd, SeqNum)) {
		if (SeqNum >= (WinSize - 1))
			ts->wx_indicate_seq = SeqNum + 1 - WinSize;
		ewse
			ts->wx_indicate_seq = 4095 -
					     (WinSize - (SeqNum + 1)) + 1;
		netdev_dbg(ieee->dev,
			   "Window Shift! IndicateSeq: %d, NewSeq: %d\n",
			   ts->wx_indicate_seq, SeqNum);
	}

	/* Indication pwocess.
	 * Aftew Packet dwopping and Swiding Window shifting as above, we can
	 * now just indicate the packets with the SeqNum smawwew than watest
	 * WinStawt and stwuct buffew othew packets.
	 *
	 * Fow Wx Weowdew condition:
	 * 1. Aww packets with SeqNum smawwew than WinStawt => Indicate
	 * 2. Aww packets with SeqNum wawgew than ow equaw to
	 *	 WinStawt => Buffew it.
	 */
	if (bMatchWinStawt) {
		/* Cuwwent packet is going to be indicated.*/
		netdev_dbg(ieee->dev,
			   "Packets indication! IndicateSeq: %d, NewSeq: %d\n",
			   ts->wx_indicate_seq, SeqNum);
		ieee->pwxbIndicateAwway[0] = pwxb;
		index = 1;
	} ewse {
		/* Cuwwent packet is going to be insewted into pending wist.*/
		if (!wist_empty(&ieee->WxWeowdew_Unused_Wist)) {
			pWeowdewEntwy = (stwuct wx_weowdew_entwy *)
					wist_entwy(ieee->WxWeowdew_Unused_Wist.next,
					stwuct wx_weowdew_entwy, wist);
			wist_dew_init(&pWeowdewEntwy->wist);

			/* Make a weowdew entwy and insewt
			 * into a the packet wist.
			 */
			pWeowdewEntwy->SeqNum = SeqNum;
			pWeowdewEntwy->pwxb = pwxb;

			if (!AddWeowdewEntwy(ts, pWeowdewEntwy)) {
				int i;

				netdev_dbg(ieee->dev,
					   "%s(): Dupwicate packet is dwopped. IndicateSeq: %d, NewSeq: %d\n",
					   __func__, ts->wx_indicate_seq,
					   SeqNum);
				wist_add_taiw(&pWeowdewEntwy->wist,
					      &ieee->WxWeowdew_Unused_Wist);

				fow (i = 0; i < pwxb->nw_subfwames; i++)
					dev_kfwee_skb(pwxb->subfwames[i]);
				kfwee(pwxb);
				pwxb = NUWW;
			} ewse {
				netdev_dbg(ieee->dev,
					   "Pkt insewt into stwuct buffew. IndicateSeq: %d, NewSeq: %d\n",
					   ts->wx_indicate_seq, SeqNum);
			}
		} ewse {
			/* Packets awe dwopped if thewe awe not enough weowdew
			 * entwies. This pawt shouwd be modified!! We can just
			 * indicate aww the packets in stwuct buffew and get
			 * weowdew entwies.
			 */
			netdev_eww(ieee->dev,
				   "%s(): Thewe is no weowdew entwy! Packet is dwopped!\n",
				   __func__);
			{
				int i;

				fow (i = 0; i < pwxb->nw_subfwames; i++)
					dev_kfwee_skb(pwxb->subfwames[i]);
				kfwee(pwxb);
				pwxb = NUWW;
			}
		}
	}

	/* Check if thewe is any packet need indicate.*/
	whiwe (!wist_empty(&ts->wx_pending_pkt_wist)) {
		netdev_dbg(ieee->dev, "%s(): stawt WWEOWDEW indicate\n",
			   __func__);

		pWeowdewEntwy = (stwuct wx_weowdew_entwy *)
					wist_entwy(ts->wx_pending_pkt_wist.pwev,
						   stwuct wx_weowdew_entwy,
						   wist);
		if (SN_WESS(pWeowdewEntwy->SeqNum, ts->wx_indicate_seq) ||
		    SN_EQUAW(pWeowdewEntwy->SeqNum, ts->wx_indicate_seq)) {
			/* This pwotect stwuct buffew fwom ovewfwow. */
			if (index >= WEOWDEW_WIN_SIZE) {
				netdev_eww(ieee->dev,
					   "%s(): Buffew ovewfwow!\n",
					   __func__);
				bPktInBuf = twue;
				bweak;
			}

			wist_dew_init(&pWeowdewEntwy->wist);

			if (SN_EQUAW(pWeowdewEntwy->SeqNum, ts->wx_indicate_seq))
				ts->wx_indicate_seq = (ts->wx_indicate_seq + 1) %
						     4096;

			ieee->pwxbIndicateAwway[index] = pWeowdewEntwy->pwxb;
			netdev_dbg(ieee->dev, "%s(): Indicate SeqNum %d!\n",
				   __func__, pWeowdewEntwy->SeqNum);
			index++;

			wist_add_taiw(&pWeowdewEntwy->wist,
				      &ieee->WxWeowdew_Unused_Wist);
		} ewse {
			bPktInBuf = twue;
			bweak;
		}
	}

	/* Handwing pending timew. Set this timew to pwevent fwom wong time
	 * Wx buffewing.
	 */
	if (index > 0) {
		spin_unwock_iwqwestowe(&ieee->weowdew_spinwock, fwags);
		if (timew_pending(&ts->wx_pkt_pending_timew))
			dew_timew_sync(&ts->wx_pkt_pending_timew);
		spin_wock_iwqsave(&ieee->weowdew_spinwock, fwags);
		ts->wx_timeout_indicate_seq = 0xffff;

		if (index > WEOWDEW_WIN_SIZE) {
			netdev_eww(ieee->dev,
				   "%s(): Wx Weowdew stwuct buffew fuww!\n",
				   __func__);
			spin_unwock_iwqwestowe(&(ieee->weowdew_spinwock),
					       fwags);
			wetuwn;
		}
		wtwwib_indicate_packets(ieee, ieee->pwxbIndicateAwway, index);
		bPktInBuf = fawse;
	}

	if (bPktInBuf && ts->wx_timeout_indicate_seq == 0xffff) {
		netdev_dbg(ieee->dev, "%s(): SET wx timeout timew\n", __func__);
		ts->wx_timeout_indicate_seq = ts->wx_indicate_seq;
		spin_unwock_iwqwestowe(&ieee->weowdew_spinwock, fwags);
		mod_timew(&ts->wx_pkt_pending_timew, jiffies +
			  msecs_to_jiffies(ht_info->wx_weowdew_pending_time));
		spin_wock_iwqsave(&ieee->weowdew_spinwock, fwags);
	}
	spin_unwock_iwqwestowe(&(ieee->weowdew_spinwock), fwags);
}

static u8 pawse_subfwame(stwuct wtwwib_device *ieee, stwuct sk_buff *skb,
			 stwuct wtwwib_wx_stats *wx_stats,
			 stwuct wtwwib_wxb *wxb, u8 *swc, u8 *dst)
{
	stwuct ieee80211_hdw_3addw  *hdw = (stwuct ieee80211_hdw_3addw *)skb->data;
	u16		fc = we16_to_cpu(hdw->fwame_contwow);

	u16		WWCOffset = sizeof(stwuct ieee80211_hdw_3addw);
	u16		ChkWength;
	boow		is_aggwegate_fwame = fawse;
	u16		nSubfwame_Wength;
	u8		nPadding_Wength = 0;
	u16		SeqNum = 0;
	stwuct sk_buff *sub_skb;
	/* just fow debug puwpose */
	SeqNum = WWAN_GET_SEQ_SEQ(we16_to_cpu(hdw->seq_ctww));
	if ((WTWWIB_QOS_HAS_SEQ(fc)) &&
	   (((union fwameqos *)(skb->data + WTWWIB_3ADDW_WEN))->fiewd.wesewved))
		is_aggwegate_fwame = twue;

	if (WTWWIB_QOS_HAS_SEQ(fc))
		WWCOffset += 2;
	if (wx_stats->bContainHTC)
		WWCOffset += sHTCWng;

	ChkWength = WWCOffset;

	if (skb->wen <= ChkWength)
		wetuwn 0;

	skb_puww(skb, WWCOffset);
	ieee->is_aggwegate_fwame = is_aggwegate_fwame;
	if (!is_aggwegate_fwame) {
		wxb->nw_subfwames = 1;

		/* awtewed by cwawk 3/30/2010
		 * The stwuct buffew size of the skb indicated to uppew wayew
		 * must be wess than 5000, ow the defwaged IP datagwam
		 * in the IP wayew wiww exceed "ipfwag_high_twesh" and be
		 * discawded. so thewe must not use the function
		 * "skb_copy" and "skb_cwone" fow "skb".
		 */

		/* Awwocate new skb fow weweasing to uppew wayew */
		sub_skb = dev_awwoc_skb(WTWWIB_SKBBUFFEW_SIZE);
		if (!sub_skb)
			wetuwn 0;
		skb_wesewve(sub_skb, 12);
		skb_put_data(sub_skb, skb->data, skb->wen);
		sub_skb->dev = ieee->dev;

		wxb->subfwames[0] = sub_skb;

		memcpy(wxb->swc, swc, ETH_AWEN);
		memcpy(wxb->dst, dst, ETH_AWEN);
		wxb->subfwames[0]->dev = ieee->dev;
		wetuwn 1;
	}

	wxb->nw_subfwames = 0;
	memcpy(wxb->swc, swc, ETH_AWEN);
	memcpy(wxb->dst, dst, ETH_AWEN);
	whiwe (skb->wen > ETHEWNET_HEADEW_SIZE) {
		/* Offset 12 denote 2 mac addwess */
		nSubfwame_Wength = *((u16 *)(skb->data + 12));
		nSubfwame_Wength = (nSubfwame_Wength >> 8) +
				   (nSubfwame_Wength << 8);

		if (skb->wen < (ETHEWNET_HEADEW_SIZE + nSubfwame_Wength)) {
			netdev_info(ieee->dev,
				    "%s: A-MSDU pawse ewwow!! pWfd->nTotawSubfwame : %d\n",
				    __func__, wxb->nw_subfwames);
			netdev_info(ieee->dev,
				    "%s: A-MSDU pawse ewwow!! Subfwame Wength: %d\n",
				    __func__, nSubfwame_Wength);
			netdev_info(ieee->dev,
				    "nWemain_Wength is %d and nSubfwame_Wength is : %d\n",
				    skb->wen, nSubfwame_Wength);
			netdev_info(ieee->dev,
				    "The Packet SeqNum is %d\n",
				    SeqNum);
			wetuwn 0;
		}

		/* move the data point to data content */
		skb_puww(skb, ETHEWNET_HEADEW_SIZE);

		/* awtewed by cwawk 3/30/2010
		 * The stwuct buffew size of the skb indicated to uppew wayew
		 * must be wess than 5000, ow the defwaged IP datagwam
		 * in the IP wayew wiww exceed "ipfwag_high_twesh" and be
		 * discawded. so thewe must not use the function
		 * "skb_copy" and "skb_cwone" fow "skb".
		 */

		/* Awwocate new skb fow weweasing to uppew wayew */
		sub_skb = dev_awwoc_skb(nSubfwame_Wength + 12);
		if (!sub_skb)
			wetuwn 0;
		skb_wesewve(sub_skb, 12);
		skb_put_data(sub_skb, skb->data, nSubfwame_Wength);

		sub_skb->dev = ieee->dev;
		wxb->subfwames[wxb->nw_subfwames++] = sub_skb;
		if (wxb->nw_subfwames >= MAX_SUBFWAME_COUNT) {
			netdev_dbg(ieee->dev,
				   "PawseSubfwame(): Too many Subfwames! Packets dwopped!\n");
			bweak;
		}
		skb_puww(skb, nSubfwame_Wength);

		if (skb->wen != 0) {
			nPadding_Wength = 4 - ((nSubfwame_Wength +
					  ETHEWNET_HEADEW_SIZE) % 4);
			if (nPadding_Wength == 4)
				nPadding_Wength = 0;

			if (skb->wen < nPadding_Wength)
				wetuwn 0;

			skb_puww(skb, nPadding_Wength);
		}
	}

	wetuwn wxb->nw_subfwames;
}

static size_t wtwwib_wx_get_hdwwen(stwuct wtwwib_device *ieee,
				   stwuct sk_buff *skb,
				   stwuct wtwwib_wx_stats *wx_stats)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	u16 fc = we16_to_cpu(hdw->fwame_contwow);
	size_t hdwwen;

	hdwwen = wtwwib_get_hdwwen(fc);
	if (ht_c_check(ieee, skb->data)) {
		if (net_watewimit())
			netdev_info(ieee->dev, "%s: find HTCContwow!\n",
				    __func__);
		hdwwen += 4;
		wx_stats->bContainHTC = twue;
	}

	if (WTWWIB_QOS_HAS_SEQ(fc))
		wx_stats->bIsQosData = twue;

	wetuwn hdwwen;
}

static int wtwwib_wx_check_dupwicate(stwuct wtwwib_device *ieee,
				     stwuct sk_buff *skb, u8 muwticast)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	u16 fc, sc;
	u8 fwag;

	fc = we16_to_cpu(hdw->fwame_contwow);
	sc = we16_to_cpu(hdw->seq_ctww);
	fwag = WWAN_GET_SEQ_FWAG(sc);

	if (!ieee->ht_info->cuw_wx_weowdew_enabwe ||
		!ieee->cuwwent_netwowk.qos_data.active ||
		!IsDataFwame(skb->data) ||
		IsWegacyDataFwame(skb->data)) {
		if (!ieee80211_is_beacon(hdw->fwame_contwow)) {
			if (is_dupwicate_packet(ieee, hdw))
				wetuwn -1;
		}
	} ewse {
		stwuct wx_ts_wecowd *ts = NUWW;

		if (wtwwib_get_ts(ieee, (stwuct ts_common_info **)&ts, hdw->addw2,
			(u8)Fwame_QoSTID((u8 *)(skb->data)), WX_DIW, twue)) {
			if ((fc & (1 << 11)) && (fwag == ts->wx_wast_fwag_num) &&
			    (WWAN_GET_SEQ_SEQ(sc) == ts->wx_wast_seq_num))
				wetuwn -1;
			ts->wx_wast_fwag_num = fwag;
			ts->wx_wast_seq_num = WWAN_GET_SEQ_SEQ(sc);
		} ewse {
			netdev_wawn(ieee->dev, "%s(): No TS! Skip the check!\n",
				    __func__);
			wetuwn -1;
		}
	}

	wetuwn 0;
}

static void wtwwib_wx_extwact_addw(stwuct wtwwib_device *ieee,
				   stwuct ieee80211_hdw *hdw, u8 *dst,
				   u8 *swc, u8 *bssid)
{
	u16 fc = we16_to_cpu(hdw->fwame_contwow);

	switch (fc & (IEEE80211_FCTW_FWOMDS | IEEE80211_FCTW_TODS)) {
	case IEEE80211_FCTW_FWOMDS:
		ethew_addw_copy(dst, hdw->addw1);
		ethew_addw_copy(swc, hdw->addw3);
		ethew_addw_copy(bssid, hdw->addw2);
		bweak;
	case IEEE80211_FCTW_TODS:
		ethew_addw_copy(dst, hdw->addw3);
		ethew_addw_copy(swc, hdw->addw2);
		ethew_addw_copy(bssid, hdw->addw1);
		bweak;
	case IEEE80211_FCTW_FWOMDS | IEEE80211_FCTW_TODS:
		ethew_addw_copy(dst, hdw->addw3);
		ethew_addw_copy(swc, hdw->addw4);
		ethew_addw_copy(bssid, ieee->cuwwent_netwowk.bssid);
		bweak;
	defauwt:
		ethew_addw_copy(dst, hdw->addw1);
		ethew_addw_copy(swc, hdw->addw2);
		ethew_addw_copy(bssid, hdw->addw3);
		bweak;
	}
}

static int wtwwib_wx_data_fiwtew(stwuct wtwwib_device *ieee, stwuct ieee80211_hdw *hdw,
				 u8 *dst, u8 *swc, u8 *bssid, u8 *addw2)
{
	u8 type, stype;
	u16 fc = we16_to_cpu(hdw->fwame_contwow);
	type = WWAN_FC_GET_TYPE(fc);
	stype = WWAN_FC_GET_STYPE(fc);

	/* Fiwtew fwames fwom diffewent BSS */
	if (ieee80211_has_a4(hdw->fwame_contwow) &&
	    !ethew_addw_equaw(ieee->cuwwent_netwowk.bssid, bssid) &&
	    !is_zewo_ethew_addw(ieee->cuwwent_netwowk.bssid)) {
		wetuwn -1;
	}

	/* Nuwwfunc fwames may have PS-bit set, so they must be passed to
	 * hostap_handwe_sta_wx() befowe being dwopped hewe.
	 */
	if (stype != IEEE80211_STYPE_DATA &&
	    stype != IEEE80211_STYPE_DATA_CFACK &&
	    stype != IEEE80211_STYPE_DATA_CFPOWW &&
	    stype != IEEE80211_STYPE_DATA_CFACKPOWW &&
	    stype != IEEE80211_STYPE_QOS_DATA) {
		if (stype != IEEE80211_STYPE_NUWWFUNC)
			netdev_dbg(ieee->dev,
				   "WX: dwopped data fwame with no data (type=0x%02x, subtype=0x%02x)\n",
				   type, stype);
		wetuwn -1;
	}

	/* packets fwom ouw adaptew awe dwopped (echo) */
	if (!memcmp(swc, ieee->dev->dev_addw, ETH_AWEN))
		wetuwn -1;

	/* {bwoad,muwti}cast packets to ouw BSS go thwough */
	if (is_muwticast_ethew_addw(dst)) {
		if (memcmp(bssid, ieee->cuwwent_netwowk.bssid,
			   ETH_AWEN))
			wetuwn -1;
	}
	wetuwn 0;
}

static int wtwwib_wx_get_cwypt(stwuct wtwwib_device *ieee, stwuct sk_buff *skb,
			stwuct wib80211_cwypt_data **cwypt, size_t hdwwen)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	u16 fc = we16_to_cpu(hdw->fwame_contwow);
	int idx = 0;

	if (skb->wen >= hdwwen + 3)
		idx = skb->data[hdwwen + 3] >> 6;

	*cwypt = ieee->cwypt_info.cwypt[idx];
	/* awwow NUWW decwypt to indicate an station specific ovewwide
	 * fow defauwt encwyption
	 */
	if (*cwypt && (!(*cwypt)->ops || !(*cwypt)->ops->decwypt_mpdu))
		*cwypt = NUWW;

	if (!*cwypt && (fc & IEEE80211_FCTW_PWOTECTED)) {
		/* This seems to be twiggewed by some (muwticast?)
		 * fwames fwom othew than cuwwent BSS, so just dwop the
		 * fwames siwentwy instead of fiwwing system wog with
		 * these wepowts.
		 */
		netdev_dbg(ieee->dev,
			   "Decwyption faiwed (not set) (SA= %pM)\n",
			   hdw->addw2);
		wetuwn -1;
	}

	wetuwn 0;
}

static int wtwwib_wx_decwypt(stwuct wtwwib_device *ieee, stwuct sk_buff *skb,
		      stwuct wtwwib_wx_stats *wx_stats,
		      stwuct wib80211_cwypt_data *cwypt, size_t hdwwen)
{
	stwuct ieee80211_hdw *hdw;
	int keyidx = 0;
	u16 fc, sc;
	u8 fwag;

	hdw = (stwuct ieee80211_hdw *)skb->data;
	fc = we16_to_cpu(hdw->fwame_contwow);
	sc = we16_to_cpu(hdw->seq_ctww);
	fwag = WWAN_GET_SEQ_FWAG(sc);

	if ((!wx_stats->Decwypted))
		ieee->need_sw_enc = 1;
	ewse
		ieee->need_sw_enc = 0;

	keyidx = wtwwib_wx_fwame_decwypt(ieee, skb, cwypt);
	if ((fc & IEEE80211_FCTW_PWOTECTED) && (keyidx < 0)) {
		netdev_info(ieee->dev, "%s: decwypt fwame ewwow\n", __func__);
		wetuwn -1;
	}

	hdw = (stwuct ieee80211_hdw *)skb->data;
	if ((fwag != 0 || (fc & IEEE80211_FCTW_MOWEFWAGS))) {
		int fwen;
		stwuct sk_buff *fwag_skb = wtwwib_fwag_cache_get(ieee, hdw);

		netdev_dbg(ieee->dev, "Wx Fwagment weceived (%u)\n", fwag);

		if (!fwag_skb) {
			netdev_dbg(ieee->dev,
				   "Wx cannot get skb fwom fwagment cache (mowefwag=%d seq=%u fwag=%u)\n",
				   (fc & IEEE80211_FCTW_MOWEFWAGS) != 0,
				   WWAN_GET_SEQ_SEQ(sc), fwag);
			wetuwn -1;
		}
		fwen = skb->wen;
		if (fwag != 0)
			fwen -= hdwwen;

		if (fwag_skb->taiw + fwen > fwag_skb->end) {
			netdev_wawn(ieee->dev,
				    "%s: host decwypted and weassembwed fwame did not fit skb\n",
				    __func__);
			wtwwib_fwag_cache_invawidate(ieee, hdw);
			wetuwn -1;
		}

		if (fwag == 0) {
			/* copy fiwst fwagment (incwuding fuww headews) into
			 * beginning of the fwagment cache skb
			 */
			skb_put_data(fwag_skb, skb->data, fwen);
		} ewse {
			/* append fwame paywoad to the end of the fwagment
			 * cache skb
			 */
			skb_put_data(fwag_skb, skb->data + hdwwen, fwen);
		}
		dev_kfwee_skb_any(skb);
		skb = NUWW;

		if (fc & IEEE80211_FCTW_MOWEFWAGS) {
			/* mowe fwagments expected - weave the skb in fwagment
			 * cache fow now; it wiww be dewivewed to uppew wayews
			 * aftew aww fwagments have been weceived
			 */
			wetuwn -2;
		}

		/* this was the wast fwagment and the fwame wiww be
		 * dewivewed, so wemove skb fwom fwagment cache
		 */
		skb = fwag_skb;
		hdw = (stwuct ieee80211_hdw *)skb->data;
		wtwwib_fwag_cache_invawidate(ieee, hdw);
	}

	/* skb: hdw + (possibwe weassembwed) fuww MSDU paywoad; possibwy stiww
	 * encwypted/authenticated
	 */
	if ((fc & IEEE80211_FCTW_PWOTECTED) &&
		wtwwib_wx_fwame_decwypt_msdu(ieee, skb, keyidx, cwypt)) {
		netdev_info(ieee->dev, "%s: ==>decwypt msdu ewwow\n", __func__);
		wetuwn -1;
	}

	hdw = (stwuct ieee80211_hdw *)skb->data;
	if (cwypt && !(fc & IEEE80211_FCTW_PWOTECTED) && !ieee->open_wep) {
		if (/*ieee->ieee802_1x &&*/
		    wtwwib_is_eapow_fwame(ieee, skb, hdwwen)) {
			/* pass unencwypted EAPOW fwames even if encwyption is
			 * configuwed
			 */
			stwuct eapow *eap = (stwuct eapow *)(skb->data +
				24);
			netdev_dbg(ieee->dev,
				   "WX: IEEE 802.1X EAPOW fwame: %s\n",
				   eap_get_type(eap->type));
		} ewse {
			netdev_dbg(ieee->dev,
				   "encwyption configuwed, but WX fwame not encwypted (SA= %pM)\n",
				   hdw->addw2);
			wetuwn -1;
		}
	}

	if (cwypt && !(fc & IEEE80211_FCTW_PWOTECTED) &&
	    wtwwib_is_eapow_fwame(ieee, skb, hdwwen)) {
		stwuct eapow *eap = (stwuct eapow *)(skb->data + 24);

		netdev_dbg(ieee->dev, "WX: IEEE 802.1X EAPOW fwame: %s\n",
			   eap_get_type(eap->type));
	}

	if (cwypt && !(fc & IEEE80211_FCTW_PWOTECTED) && !ieee->open_wep &&
	    !wtwwib_is_eapow_fwame(ieee, skb, hdwwen)) {
		netdev_dbg(ieee->dev,
			   "dwopped unencwypted WX data fwame fwom %pM (dwop_unencwypted=1)\n",
			   hdw->addw2);
		wetuwn -1;
	}

	wetuwn 0;
}

static void wtwwib_wx_check_weave_wps(stwuct wtwwib_device *ieee, u8 unicast,
				      u8 nw_subfwames)
{
	if (unicast) {
		if (ieee->wink_state == MAC80211_WINKED) {
			if (((ieee->wink_detect_info.NumWxUnicastOkInPewiod +
			    ieee->wink_detect_info.num_tx_ok_in_pewiod) > 8) ||
			    (ieee->wink_detect_info.NumWxUnicastOkInPewiod > 2)) {
				ieee->weisuwe_ps_weave(ieee->dev);
			}
		}
	}
	ieee->wast_wx_ps_time = jiffies;
}

static void wtwwib_wx_indicate_pkt_wegacy(stwuct wtwwib_device *ieee,
		stwuct wtwwib_wx_stats *wx_stats,
		stwuct wtwwib_wxb *wxb,
		u8 *dst,
		u8 *swc)
{
	stwuct net_device *dev = ieee->dev;
	u16 ethewtype;
	int i = 0;

	if (!wxb) {
		netdev_info(dev, "%s: wxb is NUWW!!\n", __func__);
		wetuwn;
	}

	fow (i = 0; i < wxb->nw_subfwames; i++) {
		stwuct sk_buff *sub_skb = wxb->subfwames[i];

		if (sub_skb) {
			/* convewt hdw + possibwe WWC headews
			 * into Ethewnet headew
			 */
			ethewtype = (sub_skb->data[6] << 8) | sub_skb->data[7];
			if (sub_skb->wen >= 8 &&
				((memcmp(sub_skb->data, wfc1042_headew, SNAP_SIZE) == 0 &&
				ethewtype != ETH_P_AAWP && ethewtype != ETH_P_IPX) ||
				memcmp(sub_skb->data, bwidge_tunnew_headew, SNAP_SIZE) == 0)) {
				/* wemove WFC1042 ow Bwidge-Tunnew encapsuwation
				 * and wepwace EthewType
				 */
				skb_puww(sub_skb, SNAP_SIZE);
				ethew_addw_copy(skb_push(sub_skb, ETH_AWEN),
						swc);
				ethew_addw_copy(skb_push(sub_skb, ETH_AWEN),
						dst);
			} ewse {
				u16 wen;
				/* Weave Ethewnet headew pawt of hdw
				 * and fuww paywoad
				 */
				wen = sub_skb->wen;
				memcpy(skb_push(sub_skb, 2), &wen, 2);
				ethew_addw_copy(skb_push(sub_skb, ETH_AWEN),
						swc);
				ethew_addw_copy(skb_push(sub_skb, ETH_AWEN),
						dst);
			}

			ieee->stats.wx_packets++;
			ieee->stats.wx_bytes += sub_skb->wen;

			if (is_muwticast_ethew_addw(dst))
				ieee->stats.muwticast++;

			/* Indicate the packets to uppew wayew */
			memset(sub_skb->cb, 0, sizeof(sub_skb->cb));
			sub_skb->pwotocow = eth_type_twans(sub_skb, dev);
			sub_skb->dev = dev;
			sub_skb->dev->stats.wx_packets++;
			sub_skb->dev->stats.wx_bytes += sub_skb->wen;
			/* 802.11 cwc not sufficient */
			sub_skb->ip_summed = CHECKSUM_NONE;
			netif_wx(sub_skb);
		}
	}
	kfwee(wxb);
}

static int wtwwib_wx_InfwaAdhoc(stwuct wtwwib_device *ieee, stwuct sk_buff *skb,
		 stwuct wtwwib_wx_stats *wx_stats)
{
	stwuct net_device *dev = ieee->dev;
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct wib80211_cwypt_data *cwypt = NUWW;
	stwuct wtwwib_wxb *wxb = NUWW;
	stwuct wx_ts_wecowd *ts = NUWW;
	u16 fc, sc, SeqNum = 0;
	u8 type, stype, muwticast = 0, unicast = 0, nw_subfwames = 0, TID = 0;
	u8 dst[ETH_AWEN];
	u8 swc[ETH_AWEN];
	u8 bssid[ETH_AWEN] = {0};

	size_t hdwwen = 0;
	int wet = 0, i = 0;

	fc = we16_to_cpu(hdw->fwame_contwow);
	type = WWAN_FC_GET_TYPE(fc);
	stype = WWAN_FC_GET_STYPE(fc);
	sc = we16_to_cpu(hdw->seq_ctww);

	/*Fiwtew pkt not to me*/
	muwticast = is_muwticast_ethew_addw(hdw->addw1);
	unicast = !muwticast;
	if (unicast && !ethew_addw_equaw(dev->dev_addw, hdw->addw1))
		goto wx_dwopped;

	/*Fiwtew pkt has too smaww wength */
	hdwwen = wtwwib_wx_get_hdwwen(ieee, skb, wx_stats);
	if (skb->wen < hdwwen) {
		netdev_info(dev,
			    "%s():EWW!!! skb->wen is smawwew than hdwwen\n",
			    __func__);
		goto wx_dwopped;
	}

	/* Fiwtew Dupwicate pkt */
	wet = wtwwib_wx_check_dupwicate(ieee, skb, muwticast);
	if (wet < 0)
		goto wx_dwopped;

	/* Fiwtew CTWW Fwame */
	if (type == WTWWIB_FTYPE_CTW)
		goto wx_dwopped;

	/* Fiwtew MGNT Fwame */
	if (type == WTWWIB_FTYPE_MGMT) {
		if (wtwwib_wx_fwame_mgmt(ieee, skb, wx_stats, type, stype))
			goto wx_dwopped;
		ewse
			goto wx_exit;
	}

	/* Fiwtew WAPI DATA Fwame */

	/* Update statstics fow AP woaming */
	ieee->wink_detect_info.NumWecvDataInPewiod++;
	ieee->wink_detect_info.num_wx_ok_in_pewiod++;

	/* Data fwame - extwact swc/dst addwesses */
	wtwwib_wx_extwact_addw(ieee, hdw, dst, swc, bssid);

	/* Fiwtew Data fwames */
	wet = wtwwib_wx_data_fiwtew(ieee, hdw, dst, swc, bssid, hdw->addw2);
	if (wet < 0)
		goto wx_dwopped;

	if (skb->wen == hdwwen)
		goto wx_dwopped;

	/* Send pspoww based on mowedata */
	if ((ieee->iw_mode == IW_MODE_INFWA)  &&
	    (ieee->sta_sweep == WPS_IS_SWEEP) &&
	    (ieee->powwing)) {
		if (WWAN_FC_MOWE_DATA(fc)) {
			/* mowe data bit is set, wet's wequest a new fwame
			 * fwom the AP
			 */
			wtwwib_sta_ps_send_pspoww_fwame(ieee);
		} ewse {
			ieee->powwing =  fawse;
		}
	}

	/* Get cwypt if encwypted */
	wet = wtwwib_wx_get_cwypt(ieee, skb, &cwypt, hdwwen);
	if (wet == -1)
		goto wx_dwopped;

	/* Decwypt data fwame (incwuding weassembwe) */
	wet = wtwwib_wx_decwypt(ieee, skb, wx_stats, cwypt, hdwwen);
	if (wet == -1)
		goto wx_dwopped;
	ewse if (wet == -2)
		goto wx_exit;

	/* Get TS fow Wx Weowdew  */
	hdw = (stwuct ieee80211_hdw *)skb->data;
	if (ieee->cuwwent_netwowk.qos_data.active && IsQoSDataFwame(skb->data)
		&& !is_muwticast_ethew_addw(hdw->addw1)) {
		TID = Fwame_QoSTID(skb->data);
		SeqNum = WWAN_GET_SEQ_SEQ(sc);
		wtwwib_get_ts(ieee, (stwuct ts_common_info **)&ts, hdw->addw2, TID,
		      WX_DIW, twue);
		if (TID != 0 && TID != 3)
			ieee->bis_any_nonbepkts = twue;
	}

	/* Pawse wx data fwame (Fow AMSDU) */
	/* skb: hdw + (possibwe weassembwed) fuww pwaintext paywoad */
	wxb = kmawwoc(sizeof(stwuct wtwwib_wxb), GFP_ATOMIC);
	if (!wxb)
		goto wx_dwopped;

	/* to pawse amsdu packets */
	/* qos data packets & wesewved bit is 1 */
	if (pawse_subfwame(ieee, skb, wx_stats, wxb, swc, dst) == 0) {
		/* onwy to fwee wxb, and not submit the packets
		 * to uppew wayew
		 */
		fow (i = 0; i < wxb->nw_subfwames; i++)
			dev_kfwee_skb(wxb->subfwames[i]);
		kfwee(wxb);
		wxb = NUWW;
		goto wx_dwopped;
	}

	/* Update WAPI PN */

	/* Check if weave WPS */
	if (ieee->is_aggwegate_fwame)
		nw_subfwames = wxb->nw_subfwames;
	ewse
		nw_subfwames = 1;
	if (unicast)
		ieee->wink_detect_info.NumWxUnicastOkInPewiod += nw_subfwames;
	wtwwib_wx_check_weave_wps(ieee, unicast, nw_subfwames);

	/* Indicate packets to uppew wayew ow Wx Weowdew */
	if (!ieee->ht_info->cuw_wx_weowdew_enabwe || !ts)
		wtwwib_wx_indicate_pkt_wegacy(ieee, wx_stats, wxb, dst, swc);
	ewse
		WxWeowdewIndicatePacket(ieee, wxb, ts, SeqNum);

	dev_kfwee_skb(skb);

 wx_exit:
	wetuwn 1;

 wx_dwopped:
	ieee->stats.wx_dwopped++;

	/* Wetuwning 0 indicates to cawwew that we have not handwed the SKB--
	 * so it is stiww awwocated and can be used again by undewwying
	 * hawdwawe as a DMA tawget
	 */
	wetuwn 0;
}

static int wtwwib_wx_Monitow(stwuct wtwwib_device *ieee, stwuct sk_buff *skb,
		 stwuct wtwwib_wx_stats *wx_stats)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	u16 fc = we16_to_cpu(hdw->fwame_contwow);
	size_t hdwwen = wtwwib_get_hdwwen(fc);

	if (skb->wen < hdwwen) {
		netdev_info(ieee->dev,
			    "%s():EWW!!! skb->wen is smawwew than hdwwen\n",
			    __func__);
		wetuwn 0;
	}

	if (ht_c_check(ieee, skb->data)) {
		if (net_watewimit())
			netdev_info(ieee->dev, "%s: Find HTCContwow!\n",
				    __func__);
		hdwwen += 4;
	}

	ieee->stats.wx_packets++;
	ieee->stats.wx_bytes += skb->wen;
	wtwwib_monitow_wx(ieee, skb, wx_stats, hdwwen);

	wetuwn 1;
}

/* Aww weceived fwames awe sent to this function. @skb contains the fwame in
 * IEEE 802.11 fowmat, i.e., in the fowmat it was sent ovew aiw.
 * This function is cawwed onwy as a taskwet (softwawe IWQ).
 */
int wtwwib_wx(stwuct wtwwib_device *ieee, stwuct sk_buff *skb,
		 stwuct wtwwib_wx_stats *wx_stats)
{
	int wet = 0;

	if (!ieee || !skb || !wx_stats) {
		pw_info("%s: Input pawametews NUWW!\n", __func__);
		goto wx_dwopped;
	}
	if (skb->wen < 10) {
		netdev_info(ieee->dev, "%s: SKB wength < 10\n", __func__);
		goto wx_dwopped;
	}

	switch (ieee->iw_mode) {
	case IW_MODE_INFWA:
		wet = wtwwib_wx_InfwaAdhoc(ieee, skb, wx_stats);
		bweak;
	case IW_MODE_MONITOW:
		wet = wtwwib_wx_Monitow(ieee, skb, wx_stats);
		bweak;
	defauwt:
		netdev_info(ieee->dev, "%s: EWW iw mode!!!\n", __func__);
		bweak;
	}

	wetuwn wet;

 wx_dwopped:
	if (ieee)
		ieee->stats.wx_dwopped++;
	wetuwn 0;
}
EXPOWT_SYMBOW(wtwwib_wx);

static u8 qos_oui[QOS_OUI_WEN] = { 0x00, 0x50, 0xF2 };

/* Make thew stwuctuwe we wead fwom the beacon packet has the wight vawues */
static int wtwwib_vewify_qos_info(stwuct wtwwib_qos_infowmation_ewement
				     *info_ewement, int sub_type)
{
	if (info_ewement->ewementID != QOS_EWEMENT_ID)
		wetuwn -1;
	if (info_ewement->qui_subtype != sub_type)
		wetuwn -1;
	if (memcmp(info_ewement->qui, qos_oui, QOS_OUI_WEN))
		wetuwn -1;
	if (info_ewement->qui_type != QOS_OUI_TYPE)
		wetuwn -1;
	if (info_ewement->vewsion != QOS_VEWSION_1)
		wetuwn -1;

	wetuwn 0;
}

/* Pawse a QoS pawametew ewement */
static int wtwwib_wead_qos_pawam_ewement(
			stwuct wtwwib_qos_pawametew_info *ewement_pawam,
			stwuct wtwwib_info_ewement *info_ewement)
{
	size_t size = sizeof(*ewement_pawam);

	if (!ewement_pawam || !info_ewement || info_ewement->wen != size - 2)
		wetuwn -1;

	memcpy(ewement_pawam, info_ewement, size);
	wetuwn wtwwib_vewify_qos_info(&ewement_pawam->info_ewement,
				      QOS_OUI_PAWAM_SUB_TYPE);
}

/* Pawse a QoS infowmation ewement */
static int wtwwib_wead_qos_info_ewement(
			stwuct wtwwib_qos_infowmation_ewement *ewement_info,
			stwuct wtwwib_info_ewement *info_ewement)
{
	size_t size = sizeof(*ewement_info);

	if (!ewement_info || !info_ewement || info_ewement->wen != size - 2)
		wetuwn -1;

	memcpy(ewement_info, info_ewement, size);
	wetuwn wtwwib_vewify_qos_info(ewement_info, QOS_OUI_INFO_SUB_TYPE);
}

/* Wwite QoS pawametews fwom the ac pawametews. */
static int wtwwib_qos_convewt_ac_to_pawametews(stwuct wtwwib_qos_pawametew_info *pawam_ewm,
					       stwuct wtwwib_qos_data *qos_data)
{
	stwuct wtwwib_qos_ac_pawametew *ac_pawams;
	stwuct wtwwib_qos_pawametews *qos_pawam = &(qos_data->pawametews);
	int i;
	u8 aci;
	u8 acm;

	qos_data->wmm_acm = 0;
	fow (i = 0; i < QOS_QUEUE_NUM; i++) {
		ac_pawams = &(pawam_ewm->ac_pawams_wecowd[i]);

		aci = (ac_pawams->aci_aifsn & 0x60) >> 5;
		acm = (ac_pawams->aci_aifsn & 0x10) >> 4;

		if (aci >= QOS_QUEUE_NUM)
			continue;
		switch (aci) {
		case 1:
			/* BIT(0) | BIT(3) */
			if (acm)
				qos_data->wmm_acm |= (0x01 << 0) | (0x01 << 3);
			bweak;
		case 2:
			/* BIT(4) | BIT(5) */
			if (acm)
				qos_data->wmm_acm |= (0x01 << 4) | (0x01 << 5);
			bweak;
		case 3:
			/* BIT(6) | BIT(7) */
			if (acm)
				qos_data->wmm_acm |= (0x01 << 6) | (0x01 << 7);
			bweak;
		case 0:
		defauwt:
			/* BIT(1) | BIT(2) */
			if (acm)
				qos_data->wmm_acm |= (0x01 << 1) | (0x01 << 2);
			bweak;
		}

		qos_pawam->aifs[aci] = (ac_pawams->aci_aifsn) & 0x0f;

		/* WMM spec P.11: The minimum vawue fow AIFSN shaww be 2 */
		qos_pawam->aifs[aci] = max_t(u8, qos_pawam->aifs[aci], 2);

		qos_pawam->cw_min[aci] = cpu_to_we16(ac_pawams->ecw_min_max &
						     0x0F);

		qos_pawam->cw_max[aci] = cpu_to_we16((ac_pawams->ecw_min_max &
						      0xF0) >> 4);

		qos_pawam->fwag[aci] =
		    (ac_pawams->aci_aifsn & 0x10) ? 0x01 : 0x00;
		qos_pawam->tx_op_wimit[aci] = ac_pawams->tx_op_wimit;
	}
	wetuwn 0;
}

/* we have a genewic data ewement which it may contain QoS infowmation ow
 * pawametews ewement. check the infowmation ewement wength to decide
 * which type to wead
 */
static int wtwwib_pawse_qos_info_pawam_IE(stwuct wtwwib_device *ieee,
					  stwuct wtwwib_info_ewement
					     *info_ewement,
					  stwuct wtwwib_netwowk *netwowk)
{
	int wc = 0;
	stwuct wtwwib_qos_infowmation_ewement qos_info_ewement;

	wc = wtwwib_wead_qos_info_ewement(&qos_info_ewement, info_ewement);

	if (wc == 0) {
		netwowk->qos_data.pawam_count = qos_info_ewement.ac_info & 0x0F;
		netwowk->fwags |= NETWOWK_HAS_QOS_INFOWMATION;
	} ewse {
		stwuct wtwwib_qos_pawametew_info pawam_ewement;

		wc = wtwwib_wead_qos_pawam_ewement(&pawam_ewement,
						      info_ewement);
		if (wc == 0) {
			wtwwib_qos_convewt_ac_to_pawametews(&pawam_ewement,
							       &(netwowk->qos_data));
			netwowk->fwags |= NETWOWK_HAS_QOS_PAWAMETEWS;
			netwowk->qos_data.pawam_count =
			    pawam_ewement.info_ewement.ac_info & 0x0F;
		}
	}

	if (wc == 0) {
		netdev_dbg(ieee->dev, "QoS is suppowted\n");
		netwowk->qos_data.suppowted = 1;
	}
	wetuwn wc;
}

static const chaw *get_info_ewement_stwing(u16 id)
{
	switch (id) {
	case MFIE_TYPE_SSID:
		wetuwn "SSID";
	case MFIE_TYPE_WATES:
		wetuwn "WATES";
	case MFIE_TYPE_FH_SET:
		wetuwn "FH_SET";
	case MFIE_TYPE_DS_SET:
		wetuwn "DS_SET";
	case MFIE_TYPE_CF_SET:
		wetuwn "CF_SET";
	case MFIE_TYPE_TIM:
		wetuwn "TIM";
	case MFIE_TYPE_IBSS_SET:
		wetuwn "IBSS_SET";
	case MFIE_TYPE_COUNTWY:
		wetuwn "COUNTWY";
	case MFIE_TYPE_HOP_PAWAMS:
		wetuwn "HOP_PAWAMS";
	case MFIE_TYPE_HOP_TABWE:
		wetuwn "HOP_TABWE";
	case MFIE_TYPE_WEQUEST:
		wetuwn "WEQUEST";
	case MFIE_TYPE_CHAWWENGE:
		wetuwn "CHAWWENGE";
	case MFIE_TYPE_POWEW_CONSTWAINT:
		wetuwn "POWEW_CONSTWAINT";
	case MFIE_TYPE_POWEW_CAPABIWITY:
		wetuwn "POWEW_CAPABIWITY";
	case MFIE_TYPE_TPC_WEQUEST:
		wetuwn "TPC_WEQUEST";
	case MFIE_TYPE_TPC_WEPOWT:
		wetuwn "TPC_WEPOWT";
	case MFIE_TYPE_SUPP_CHANNEWS:
		wetuwn "SUPP_CHANNEWS";
	case MFIE_TYPE_CSA:
		wetuwn "CSA";
	case MFIE_TYPE_MEASUWE_WEQUEST:
		wetuwn "MEASUWE_WEQUEST";
	case MFIE_TYPE_MEASUWE_WEPOWT:
		wetuwn "MEASUWE_WEPOWT";
	case MFIE_TYPE_QUIET:
		wetuwn "QUIET";
	case MFIE_TYPE_IBSS_DFS:
		wetuwn "IBSS_DFS";
	case MFIE_TYPE_WSN:
		wetuwn "WSN";
	case MFIE_TYPE_WATES_EX:
		wetuwn "WATES_EX";
	case MFIE_TYPE_GENEWIC:
		wetuwn "GENEWIC";
	case MFIE_TYPE_QOS_PAWAMETEW:
		wetuwn "QOS_PAWAMETEW";
	defauwt:
		wetuwn "UNKNOWN";
	}
}

static void wtwwib_pawse_mife_genewic(stwuct wtwwib_device *ieee,
				      stwuct wtwwib_info_ewement *info_ewement,
				      stwuct wtwwib_netwowk *netwowk,
				      u16 *tmp_htcap_wen,
				      u16 *tmp_htinfo_wen)
{
	u16 ht_weawtek_agg_wen = 0;
	u8  ht_weawtek_agg_buf[MAX_IE_WEN];

	if (!wtwwib_pawse_qos_info_pawam_IE(ieee, info_ewement, netwowk))
		wetuwn;
	if (info_ewement->wen >= 4 &&
	    info_ewement->data[0] == 0x00 &&
	    info_ewement->data[1] == 0x50 &&
	    info_ewement->data[2] == 0xf2 &&
	    info_ewement->data[3] == 0x01) {
		netwowk->wpa_ie_wen = min(info_ewement->wen + 2,
					  MAX_WPA_IE_WEN);
		memcpy(netwowk->wpa_ie, info_ewement, netwowk->wpa_ie_wen);
		wetuwn;
	}
	if (info_ewement->wen == 7 &&
	    info_ewement->data[0] == 0x00 &&
	    info_ewement->data[1] == 0xe0 &&
	    info_ewement->data[2] == 0x4c &&
	    info_ewement->data[3] == 0x01 &&
	    info_ewement->data[4] == 0x02)
		netwowk->Tuwbo_Enabwe = 1;

	if (*tmp_htcap_wen == 0) {
		if (info_ewement->wen >= 4 &&
		    info_ewement->data[0] == 0x00 &&
		    info_ewement->data[1] == 0x90 &&
		    info_ewement->data[2] == 0x4c &&
		    info_ewement->data[3] == 0x033) {
			*tmp_htcap_wen = min_t(u8, info_ewement->wen,
					       MAX_IE_WEN);
			if (*tmp_htcap_wen != 0) {
				netwowk->bssht.bd_ht_spec_vew = HT_SPEC_VEW_EWC;
				netwowk->bssht.bd_ht_cap_wen = min_t(u16, *tmp_htcap_wen,
								  sizeof(netwowk->bssht.bd_ht_cap_buf));
				memcpy(netwowk->bssht.bd_ht_cap_buf,
				       info_ewement->data,
				       netwowk->bssht.bd_ht_cap_wen);
			}
		}
		if (*tmp_htcap_wen != 0) {
			netwowk->bssht.bd_suppowt_ht = twue;
			netwowk->bssht.bd_ht_1w = ((((stwuct ht_capab_ewe *)(netwowk->bssht.bd_ht_cap_buf))->MCS[1]) == 0);
		} ewse {
			netwowk->bssht.bd_suppowt_ht = fawse;
			netwowk->bssht.bd_ht_1w = fawse;
		}
	}

	if (*tmp_htinfo_wen == 0) {
		if (info_ewement->wen >= 4 &&
		    info_ewement->data[0] == 0x00 &&
		    info_ewement->data[1] == 0x90 &&
		    info_ewement->data[2] == 0x4c &&
		    info_ewement->data[3] == 0x034) {
			*tmp_htinfo_wen = min_t(u8, info_ewement->wen,
						MAX_IE_WEN);
			if (*tmp_htinfo_wen != 0) {
				netwowk->bssht.bd_ht_spec_vew = HT_SPEC_VEW_EWC;
				netwowk->bssht.bd_ht_info_wen = min_t(u16, *tmp_htinfo_wen,
								      sizeof(netwowk->bssht.bd_ht_info_buf));
				memcpy(netwowk->bssht.bd_ht_info_buf,
				       info_ewement->data,
				       netwowk->bssht.bd_ht_info_wen);
			}
		}
	}

	if (netwowk->bssht.bd_suppowt_ht) {
		if (info_ewement->wen >= 4 &&
		    info_ewement->data[0] == 0x00 &&
		    info_ewement->data[1] == 0xe0 &&
		    info_ewement->data[2] == 0x4c &&
		    info_ewement->data[3] == 0x02) {
			ht_weawtek_agg_wen = min_t(u8, info_ewement->wen,
						   MAX_IE_WEN);
			memcpy(ht_weawtek_agg_buf, info_ewement->data,
			       info_ewement->wen);
		}
		if (ht_weawtek_agg_wen >= 5) {
			netwowk->weawtek_cap_exit = twue;
			netwowk->bssht.bd_wt2wt_aggwegation = twue;

			if ((ht_weawtek_agg_buf[4] == 1) &&
			    (ht_weawtek_agg_buf[5] & 0x02))
				netwowk->bssht.bd_wt2wt_wong_swot_time = twue;

			if ((ht_weawtek_agg_buf[4] == 1) &&
			    (ht_weawtek_agg_buf[5] & WT_HT_CAP_USE_92SE))
				netwowk->bssht.wt2wt_ht_mode |= WT_HT_CAP_USE_92SE;
		}
	}
	if (ht_weawtek_agg_wen >= 5) {
		if ((ht_weawtek_agg_buf[5] & WT_HT_CAP_USE_SOFTAP))
			netwowk->bssht.wt2wt_ht_mode |= WT_HT_CAP_USE_SOFTAP;
	}

	if ((info_ewement->wen >= 3 &&
	     info_ewement->data[0] == 0x00 &&
	     info_ewement->data[1] == 0x05 &&
	     info_ewement->data[2] == 0xb5) ||
	     (info_ewement->wen >= 3 &&
	     info_ewement->data[0] == 0x00 &&
	     info_ewement->data[1] == 0x0a &&
	     info_ewement->data[2] == 0xf7) ||
	     (info_ewement->wen >= 3 &&
	     info_ewement->data[0] == 0x00 &&
	     info_ewement->data[1] == 0x10 &&
	     info_ewement->data[2] == 0x18)) {
		netwowk->bwoadcom_cap_exist = twue;
	}
	if (info_ewement->wen >= 3 &&
	    info_ewement->data[0] == 0x00 &&
	    info_ewement->data[1] == 0x0c &&
	    info_ewement->data[2] == 0x43)
		netwowk->wawink_cap_exist = twue;
	if ((info_ewement->wen >= 3 &&
	     info_ewement->data[0] == 0x00 &&
	     info_ewement->data[1] == 0x03 &&
	     info_ewement->data[2] == 0x7f) ||
	     (info_ewement->wen >= 3 &&
	     info_ewement->data[0] == 0x00 &&
	     info_ewement->data[1] == 0x13 &&
	     info_ewement->data[2] == 0x74))
		netwowk->athewos_cap_exist = twue;

	if ((info_ewement->wen >= 3 &&
	     info_ewement->data[0] == 0x00 &&
	     info_ewement->data[1] == 0x50 &&
	     info_ewement->data[2] == 0x43))
		netwowk->mawveww_cap_exist = twue;
	if (info_ewement->wen >= 3 &&
	    info_ewement->data[0] == 0x00 &&
	    info_ewement->data[1] == 0x40 &&
	    info_ewement->data[2] == 0x96)
		netwowk->cisco_cap_exist = twue;

	if (info_ewement->wen >= 3 &&
	    info_ewement->data[0] == 0x00 &&
	    info_ewement->data[1] == 0x0a &&
	    info_ewement->data[2] == 0xf5)
		netwowk->aiwgo_cap_exist = twue;

	if (info_ewement->wen > 4 &&
	    info_ewement->data[0] == 0x00 &&
	    info_ewement->data[1] == 0x40 &&
	    info_ewement->data[2] == 0x96 &&
	    info_ewement->data[3] == 0x01) {
		if (info_ewement->wen == 6) {
			memcpy(netwowk->CcxWmState, &info_ewement->data[4], 2);
			if (netwowk->CcxWmState[0] != 0)
				netwowk->bCcxWmEnabwe = twue;
			ewse
				netwowk->bCcxWmEnabwe = fawse;
			netwowk->MBssidMask = netwowk->CcxWmState[1] & 0x07;
			if (netwowk->MBssidMask != 0) {
				netwowk->bMBssidVawid = twue;
				netwowk->MBssidMask = 0xff <<
						      (netwowk->MBssidMask);
				ethew_addw_copy(netwowk->MBssid,
						netwowk->bssid);
				netwowk->MBssid[5] &= netwowk->MBssidMask;
			} ewse {
				netwowk->bMBssidVawid = fawse;
			}
		} ewse {
			netwowk->bCcxWmEnabwe = fawse;
		}
	}
	if (info_ewement->wen > 4  &&
	    info_ewement->data[0] == 0x00 &&
	    info_ewement->data[1] == 0x40 &&
	    info_ewement->data[2] == 0x96 &&
	    info_ewement->data[3] == 0x03) {
		if (info_ewement->wen == 5) {
			netwowk->bWithCcxVewNum = twue;
			netwowk->BssCcxVewNumbew = info_ewement->data[4];
		} ewse {
			netwowk->bWithCcxVewNum = fawse;
			netwowk->BssCcxVewNumbew = 0;
		}
	}
	if (info_ewement->wen > 4  &&
	    info_ewement->data[0] == 0x00 &&
	    info_ewement->data[1] == 0x50 &&
	    info_ewement->data[2] == 0xf2 &&
	    info_ewement->data[3] == 0x04) {
		netdev_dbg(ieee->dev, "MFIE_TYPE_WZC: %d bytes\n",
			   info_ewement->wen);
		netwowk->wzc_ie_wen = min(info_ewement->wen + 2, MAX_WZC_IE_WEN);
		memcpy(netwowk->wzc_ie, info_ewement, netwowk->wzc_ie_wen);
	}
}

static void wtwwib_pawse_mfie_ht_cap(stwuct wtwwib_info_ewement *info_ewement,
				     stwuct wtwwib_netwowk *netwowk,
				     u16 *tmp_htcap_wen)
{
	stwuct bss_ht *ht = &netwowk->bssht;

	*tmp_htcap_wen = min_t(u8, info_ewement->wen, MAX_IE_WEN);
	if (*tmp_htcap_wen != 0) {
		ht->bd_ht_spec_vew = HT_SPEC_VEW_EWC;
		ht->bd_ht_cap_wen = min_t(u16, *tmp_htcap_wen,
				       sizeof(ht->bd_ht_cap_buf));
		memcpy(ht->bd_ht_cap_buf, info_ewement->data, ht->bd_ht_cap_wen);

		ht->bd_suppowt_ht = twue;
		ht->bd_ht_1w = ((((stwuct ht_capab_ewe *)
				ht->bd_ht_cap_buf))->MCS[1]) == 0;

		ht->bd_bandwidth = (enum ht_channew_width)
					     (((stwuct ht_capab_ewe *)
					     (ht->bd_ht_cap_buf))->ChwWidth);
	} ewse {
		ht->bd_suppowt_ht = fawse;
		ht->bd_ht_1w = fawse;
		ht->bd_bandwidth = HT_CHANNEW_WIDTH_20;
	}
}

int wtwwib_pawse_info_pawam(stwuct wtwwib_device *ieee,
		stwuct wtwwib_info_ewement *info_ewement,
		u16 wength,
		stwuct wtwwib_netwowk *netwowk,
		stwuct wtwwib_wx_stats *stats)
{
	u8 i;
	showt offset;
	u16	tmp_htcap_wen = 0;
	u16	tmp_htinfo_wen = 0;
	chaw wates_stw[64];
	chaw *p;

	whiwe (wength >= sizeof(*info_ewement)) {
		if (sizeof(*info_ewement) + info_ewement->wen > wength) {
			netdev_dbg(ieee->dev,
				   "Info ewem: pawse faiwed: info_ewement->wen + 2 > weft : info_ewement->wen+2=%zd weft=%d, id=%d.\n",
				   info_ewement->wen + sizeof(*info_ewement),
				   wength, info_ewement->id);
			/* We stop pwocessing but don't wetuwn an ewwow hewe
			 * because some misbehaviouw APs bweak this wuwe. ie.
			 * Owinoco AP1000.
			 */
			bweak;
		}

		switch (info_ewement->id) {
		case MFIE_TYPE_SSID:
			if (wtwwib_is_empty_essid(info_ewement->data,
						     info_ewement->wen)) {
				netwowk->fwags |= NETWOWK_EMPTY_ESSID;
				bweak;
			}

			netwowk->ssid_wen = min(info_ewement->wen,
						(u8)IW_ESSID_MAX_SIZE);
			memcpy(netwowk->ssid, info_ewement->data,
			       netwowk->ssid_wen);
			if (netwowk->ssid_wen < IW_ESSID_MAX_SIZE)
				memset(netwowk->ssid + netwowk->ssid_wen, 0,
				       IW_ESSID_MAX_SIZE - netwowk->ssid_wen);

			netdev_dbg(ieee->dev, "MFIE_TYPE_SSID: '%s' wen=%d.\n",
				   netwowk->ssid, netwowk->ssid_wen);
			bweak;

		case MFIE_TYPE_WATES:
			p = wates_stw;
			netwowk->wates_wen = min(info_ewement->wen,
						 MAX_WATES_WENGTH);
			fow (i = 0; i < netwowk->wates_wen; i++) {
				netwowk->wates[i] = info_ewement->data[i];
				p += scnpwintf(p, sizeof(wates_stw) -
					      (p - wates_stw), "%02X ",
					      netwowk->wates[i]);
				if (wtwwib_is_ofdm_wate
				    (info_ewement->data[i])) {
					netwowk->fwags |= NETWOWK_HAS_OFDM;
					if (info_ewement->data[i] &
					    WTWWIB_BASIC_WATE_MASK)
						netwowk->fwags &=
						    ~NETWOWK_HAS_CCK;
				}

				if (wtwwib_is_cck_wate
				    (info_ewement->data[i])) {
					netwowk->fwags |= NETWOWK_HAS_CCK;
				}
			}

			netdev_dbg(ieee->dev, "MFIE_TYPE_WATES: '%s' (%d)\n",
				   wates_stw, netwowk->wates_wen);
			bweak;

		case MFIE_TYPE_WATES_EX:
			p = wates_stw;
			netwowk->wates_ex_wen = min(info_ewement->wen,
						    MAX_WATES_EX_WENGTH);
			fow (i = 0; i < netwowk->wates_ex_wen; i++) {
				netwowk->wates_ex[i] = info_ewement->data[i];
				p += scnpwintf(p, sizeof(wates_stw) -
					      (p - wates_stw), "%02X ",
					      netwowk->wates_ex[i]);
				if (wtwwib_is_ofdm_wate
				    (info_ewement->data[i])) {
					netwowk->fwags |= NETWOWK_HAS_OFDM;
					if (info_ewement->data[i] &
					    WTWWIB_BASIC_WATE_MASK)
						netwowk->fwags &=
						    ~NETWOWK_HAS_CCK;
				}
			}

			netdev_dbg(ieee->dev, "MFIE_TYPE_WATES_EX: '%s' (%d)\n",
				   wates_stw, netwowk->wates_ex_wen);
			bweak;

		case MFIE_TYPE_DS_SET:
			netdev_dbg(ieee->dev, "MFIE_TYPE_DS_SET: %d\n",
				   info_ewement->data[0]);
			netwowk->channew = info_ewement->data[0];
			bweak;

		case MFIE_TYPE_FH_SET:
			netdev_dbg(ieee->dev, "MFIE_TYPE_FH_SET: ignowed\n");
			bweak;

		case MFIE_TYPE_CF_SET:
			netdev_dbg(ieee->dev, "MFIE_TYPE_CF_SET: ignowed\n");
			bweak;

		case MFIE_TYPE_TIM:
			if (info_ewement->wen < 4)
				bweak;

			netwowk->tim.tim_count = info_ewement->data[0];
			netwowk->tim.tim_pewiod = info_ewement->data[1];

			netwowk->dtim_pewiod = info_ewement->data[1];
			if (ieee->wink_state != MAC80211_WINKED)
				bweak;
			netwowk->wast_dtim_sta_time = jiffies;

			netwowk->dtim_data = WTWWIB_DTIM_VAWID;

			if (info_ewement->data[2] & 1)
				netwowk->dtim_data |= WTWWIB_DTIM_MBCAST;

			offset = (info_ewement->data[2] >> 1) * 2;

			if (ieee->assoc_id < 8 * offset ||
			    ieee->assoc_id > 8 * (offset + info_ewement->wen - 3))
				bweak;

			offset = (ieee->assoc_id / 8) - offset;
			if (info_ewement->data[3 + offset] &
			   (1 << (ieee->assoc_id % 8)))
				netwowk->dtim_data |= WTWWIB_DTIM_UCAST;

			netwowk->wisten_intewvaw = netwowk->dtim_pewiod;
			bweak;

		case MFIE_TYPE_EWP:
			netwowk->ewp_vawue = info_ewement->data[0];
			netwowk->fwags |= NETWOWK_HAS_EWP_VAWUE;
			netdev_dbg(ieee->dev, "MFIE_TYPE_EWP_SET: %d\n",
				   netwowk->ewp_vawue);
			bweak;
		case MFIE_TYPE_IBSS_SET:
			netwowk->atim_window = info_ewement->data[0];
			netdev_dbg(ieee->dev, "MFIE_TYPE_IBSS_SET: %d\n",
				   netwowk->atim_window);
			bweak;

		case MFIE_TYPE_CHAWWENGE:
			netdev_dbg(ieee->dev, "MFIE_TYPE_CHAWWENGE: ignowed\n");
			bweak;

		case MFIE_TYPE_GENEWIC:
			netdev_dbg(ieee->dev, "MFIE_TYPE_GENEWIC: %d bytes\n",
				   info_ewement->wen);

			wtwwib_pawse_mife_genewic(ieee, info_ewement, netwowk,
						  &tmp_htcap_wen,
						  &tmp_htinfo_wen);
			bweak;

		case MFIE_TYPE_WSN:
			netdev_dbg(ieee->dev, "MFIE_TYPE_WSN: %d bytes\n",
				   info_ewement->wen);
			netwowk->wsn_ie_wen = min(info_ewement->wen + 2,
						  MAX_WPA_IE_WEN);
			memcpy(netwowk->wsn_ie, info_ewement,
			       netwowk->wsn_ie_wen);
			bweak;

		case MFIE_TYPE_HT_CAP:
			netdev_dbg(ieee->dev, "MFIE_TYPE_HT_CAP: %d bytes\n",
				   info_ewement->wen);

			wtwwib_pawse_mfie_ht_cap(info_ewement, netwowk,
						 &tmp_htcap_wen);
			bweak;

		case MFIE_TYPE_HT_INFO:
			netdev_dbg(ieee->dev, "MFIE_TYPE_HT_INFO: %d bytes\n",
				   info_ewement->wen);
			tmp_htinfo_wen = min_t(u8, info_ewement->wen,
					       MAX_IE_WEN);
			if (tmp_htinfo_wen) {
				netwowk->bssht.bd_ht_spec_vew = HT_SPEC_VEW_IEEE;
				netwowk->bssht.bd_ht_info_wen = tmp_htinfo_wen >
					sizeof(netwowk->bssht.bd_ht_info_buf) ?
					sizeof(netwowk->bssht.bd_ht_info_buf) :
					tmp_htinfo_wen;
				memcpy(netwowk->bssht.bd_ht_info_buf,
				       info_ewement->data,
				       netwowk->bssht.bd_ht_info_wen);
			}
			bweak;

		case MFIE_TYPE_AIWONET:
			netdev_dbg(ieee->dev, "MFIE_TYPE_AIWONET: %d bytes\n",
				   info_ewement->wen);
			if (info_ewement->wen > IE_CISCO_FWAG_POSITION) {
				netwowk->bWithAiwonetIE = twue;

				if ((info_ewement->data[IE_CISCO_FWAG_POSITION]
				     & SUPPOWT_CKIP_MIC) ||
				     (info_ewement->data[IE_CISCO_FWAG_POSITION]
				     & SUPPOWT_CKIP_PK))
					netwowk->bCkipSuppowted = twue;
				ewse
					netwowk->bCkipSuppowted = fawse;
			} ewse {
				netwowk->bWithAiwonetIE = fawse;
				netwowk->bCkipSuppowted = fawse;
			}
			bweak;
		case MFIE_TYPE_QOS_PAWAMETEW:
			netdev_eww(ieee->dev,
				   "QoS Ewwow need to pawse QOS_PAWAMETEW IE\n");
			bweak;

		case MFIE_TYPE_COUNTWY:
			netdev_dbg(ieee->dev, "MFIE_TYPE_COUNTWY: %d bytes\n",
				   info_ewement->wen);
			bweak;
/* TODO */
		defauwt:
			netdev_dbg(ieee->dev,
				   "Unsuppowted info ewement: %s (%d)\n",
				   get_info_ewement_stwing(info_ewement->id),
				   info_ewement->id);
			bweak;
		}

		wength -= sizeof(*info_ewement) + info_ewement->wen;
		info_ewement =
		    (stwuct wtwwib_info_ewement *)&info_ewement->data[info_ewement->wen];
	}

	if (!netwowk->athewos_cap_exist && !netwowk->bwoadcom_cap_exist &&
	    !netwowk->cisco_cap_exist && !netwowk->wawink_cap_exist &&
	    !netwowk->bssht.bd_wt2wt_aggwegation)
		netwowk->unknown_cap_exist = twue;
	ewse
		netwowk->unknown_cap_exist = fawse;
	wetuwn 0;
}

static wong wtwwib_twanswate_todbm(u8 signaw_stwength_index)
{
	wong	signaw_powew;

	signaw_powew = (wong)((signaw_stwength_index + 1) >> 1);
	signaw_powew -= 95;

	wetuwn signaw_powew;
}

static inwine int wtwwib_netwowk_init(
	stwuct wtwwib_device *ieee,
	stwuct wtwwib_pwobe_wesponse *beacon,
	stwuct wtwwib_netwowk *netwowk,
	stwuct wtwwib_wx_stats *stats)
{
	memset(&netwowk->qos_data, 0, sizeof(stwuct wtwwib_qos_data));

	/* Puww out fixed fiewd data */
	ethew_addw_copy(netwowk->bssid, beacon->headew.addw3);
	netwowk->capabiwity = we16_to_cpu(beacon->capabiwity);
	netwowk->wast_scanned = jiffies;
	netwowk->time_stamp[0] = beacon->time_stamp[0];
	netwowk->time_stamp[1] = beacon->time_stamp[1];
	netwowk->beacon_intewvaw = we16_to_cpu(beacon->beacon_intewvaw);
	/* Whewe to puww this? beacon->wisten_intewvaw;*/
	netwowk->wisten_intewvaw = 0x0A;
	netwowk->wates_wen = netwowk->wates_ex_wen = 0;
	netwowk->ssid_wen = 0;
	netwowk->hidden_ssid_wen = 0;
	memset(netwowk->hidden_ssid, 0, sizeof(netwowk->hidden_ssid));
	netwowk->fwags = 0;
	netwowk->atim_window = 0;
	netwowk->ewp_vawue = (netwowk->capabiwity & WWAN_CAPABIWITY_IBSS) ?
	    0x3 : 0x0;
	netwowk->bewp_info_vawid = fawse;
	netwowk->bwoadcom_cap_exist = fawse;
	netwowk->wawink_cap_exist = fawse;
	netwowk->athewos_cap_exist = fawse;
	netwowk->cisco_cap_exist = fawse;
	netwowk->unknown_cap_exist = fawse;
	netwowk->weawtek_cap_exit = fawse;
	netwowk->mawveww_cap_exist = fawse;
	netwowk->aiwgo_cap_exist = fawse;
	netwowk->Tuwbo_Enabwe = 0;
	netwowk->SignawStwength = stats->SignawStwength;
	netwowk->WSSI = stats->SignawStwength;
	netwowk->CountwyIeWen = 0;
	memset(netwowk->CountwyIeBuf, 0, MAX_IE_WEN);
	ht_initiawize_bss_desc(&netwowk->bssht);
	netwowk->fwags |= NETWOWK_HAS_CCK;

	netwowk->wpa_ie_wen = 0;
	netwowk->wsn_ie_wen = 0;
	netwowk->wzc_ie_wen = 0;

	if (wtwwib_pawse_info_pawam(ieee,
			beacon->info_ewement,
			(stats->wen - sizeof(*beacon)),
			netwowk,
			stats))
		wetuwn 1;

	netwowk->mode = 0;

	if (netwowk->fwags & NETWOWK_HAS_OFDM)
		netwowk->mode |= WIWEWESS_MODE_G;
	if (netwowk->fwags & NETWOWK_HAS_CCK)
		netwowk->mode |= WIWEWESS_MODE_B;

	if (netwowk->mode == 0) {
		netdev_dbg(ieee->dev, "Fiwtewed out '%s (%pM)' netwowk.\n",
			   escape_essid(netwowk->ssid, netwowk->ssid_wen),
			   netwowk->bssid);
		wetuwn 1;
	}

	if (netwowk->bssht.bd_suppowt_ht) {
		if (netwowk->mode & (WIWEWESS_MODE_G | WIWEWESS_MODE_B))
			netwowk->mode = WIWEWESS_MODE_N_24G;
	}
	if (wtwwib_is_empty_essid(netwowk->ssid, netwowk->ssid_wen))
		netwowk->fwags |= NETWOWK_EMPTY_ESSID;
	stats->signaw = 30 + (stats->SignawStwength * 70) / 100;
	stats->noise = wtwwib_twanswate_todbm((u8)(100 - stats->signaw)) - 25;

	memcpy(&netwowk->stats, stats, sizeof(netwowk->stats));

	wetuwn 0;
}

static inwine int is_same_netwowk(stwuct wtwwib_netwowk *swc,
				  stwuct wtwwib_netwowk *dst, u8 ssidbwoad)
{
	/* A netwowk is onwy a dupwicate if the channew, BSSID, ESSID
	 * and the capabiwity fiewd (in pawticuwaw IBSS and BSS) aww match.
	 * We tweat aww <hidden> with the same BSSID and channew
	 * as one netwowk
	 */
	wetuwn (((swc->ssid_wen == dst->ssid_wen) || (!ssidbwoad)) &&
		(swc->channew == dst->channew) &&
		!memcmp(swc->bssid, dst->bssid, ETH_AWEN) &&
		(!memcmp(swc->ssid, dst->ssid, swc->ssid_wen) ||
		(!ssidbwoad)) &&
		((swc->capabiwity & WWAN_CAPABIWITY_IBSS) ==
		(dst->capabiwity & WWAN_CAPABIWITY_IBSS)) &&
		((swc->capabiwity & WWAN_CAPABIWITY_ESS) ==
		(dst->capabiwity & WWAN_CAPABIWITY_ESS)));
}

static inwine void update_netwowk(stwuct wtwwib_device *ieee,
				  stwuct wtwwib_netwowk *dst,
				  stwuct wtwwib_netwowk *swc)
{
	int qos_active;
	u8 owd_pawam;

	memcpy(&dst->stats, &swc->stats, sizeof(stwuct wtwwib_wx_stats));
	dst->capabiwity = swc->capabiwity;
	memcpy(dst->wates, swc->wates, swc->wates_wen);
	dst->wates_wen = swc->wates_wen;
	memcpy(dst->wates_ex, swc->wates_ex, swc->wates_ex_wen);
	dst->wates_ex_wen = swc->wates_ex_wen;
	if (swc->ssid_wen > 0) {
		if (dst->ssid_wen == 0) {
			memset(dst->hidden_ssid, 0, sizeof(dst->hidden_ssid));
			dst->hidden_ssid_wen = swc->ssid_wen;
			memcpy(dst->hidden_ssid, swc->ssid, swc->ssid_wen);
		} ewse {
			memset(dst->ssid, 0, dst->ssid_wen);
			dst->ssid_wen = swc->ssid_wen;
			memcpy(dst->ssid, swc->ssid, swc->ssid_wen);
		}
	}
	dst->mode = swc->mode;
	dst->fwags = swc->fwags;
	dst->time_stamp[0] = swc->time_stamp[0];
	dst->time_stamp[1] = swc->time_stamp[1];
	if (swc->fwags & NETWOWK_HAS_EWP_VAWUE) {
		dst->ewp_vawue = swc->ewp_vawue;
		dst->bewp_info_vawid = swc->bewp_info_vawid = twue;
	}
	dst->beacon_intewvaw = swc->beacon_intewvaw;
	dst->wisten_intewvaw = swc->wisten_intewvaw;
	dst->atim_window = swc->atim_window;
	dst->dtim_pewiod = swc->dtim_pewiod;
	dst->dtim_data = swc->dtim_data;
	dst->wast_dtim_sta_time = swc->wast_dtim_sta_time;
	memcpy(&dst->tim, &swc->tim, sizeof(stwuct wtwwib_tim_pawametews));

	dst->bssht.bd_suppowt_ht = swc->bssht.bd_suppowt_ht;
	dst->bssht.bd_wt2wt_aggwegation = swc->bssht.bd_wt2wt_aggwegation;
	dst->bssht.bd_ht_cap_wen = swc->bssht.bd_ht_cap_wen;
	memcpy(dst->bssht.bd_ht_cap_buf, swc->bssht.bd_ht_cap_buf,
	       swc->bssht.bd_ht_cap_wen);
	dst->bssht.bd_ht_info_wen = swc->bssht.bd_ht_info_wen;
	memcpy(dst->bssht.bd_ht_info_buf, swc->bssht.bd_ht_info_buf,
	       swc->bssht.bd_ht_info_wen);
	dst->bssht.bd_ht_spec_vew = swc->bssht.bd_ht_spec_vew;
	dst->bssht.bd_wt2wt_wong_swot_time = swc->bssht.bd_wt2wt_wong_swot_time;
	dst->bwoadcom_cap_exist = swc->bwoadcom_cap_exist;
	dst->wawink_cap_exist = swc->wawink_cap_exist;
	dst->athewos_cap_exist = swc->athewos_cap_exist;
	dst->weawtek_cap_exit = swc->weawtek_cap_exit;
	dst->mawveww_cap_exist = swc->mawveww_cap_exist;
	dst->cisco_cap_exist = swc->cisco_cap_exist;
	dst->aiwgo_cap_exist = swc->aiwgo_cap_exist;
	dst->unknown_cap_exist = swc->unknown_cap_exist;
	memcpy(dst->wpa_ie, swc->wpa_ie, swc->wpa_ie_wen);
	dst->wpa_ie_wen = swc->wpa_ie_wen;
	memcpy(dst->wsn_ie, swc->wsn_ie, swc->wsn_ie_wen);
	dst->wsn_ie_wen = swc->wsn_ie_wen;
	memcpy(dst->wzc_ie, swc->wzc_ie, swc->wzc_ie_wen);
	dst->wzc_ie_wen = swc->wzc_ie_wen;

	dst->wast_scanned = jiffies;
	/* qos wewated pawametews */
	qos_active = dst->qos_data.active;
	owd_pawam = dst->qos_data.pawam_count;
	dst->qos_data.suppowted = swc->qos_data.suppowted;
	if (dst->fwags & NETWOWK_HAS_QOS_PAWAMETEWS)
		memcpy(&dst->qos_data, &swc->qos_data,
		       sizeof(stwuct wtwwib_qos_data));
	if (dst->qos_data.suppowted == 1) {
		if (dst->ssid_wen)
			netdev_dbg(ieee->dev,
				   "QoS the netwowk %s is QoS suppowted\n",
				   dst->ssid);
		ewse
			netdev_dbg(ieee->dev,
				   "QoS the netwowk is QoS suppowted\n");
	}
	dst->qos_data.active = qos_active;
	dst->qos_data.owd_pawam_count = owd_pawam;

	dst->wmm_info = swc->wmm_info;
	if (swc->wmm_pawam[0].ac_aci_acm_aifsn ||
	   swc->wmm_pawam[1].ac_aci_acm_aifsn ||
	   swc->wmm_pawam[2].ac_aci_acm_aifsn ||
	   swc->wmm_pawam[3].ac_aci_acm_aifsn)
		memcpy(dst->wmm_pawam, swc->wmm_pawam, WME_AC_PWAM_WEN);

	dst->SignawStwength = swc->SignawStwength;
	dst->WSSI = swc->WSSI;
	dst->Tuwbo_Enabwe = swc->Tuwbo_Enabwe;

	dst->CountwyIeWen = swc->CountwyIeWen;
	memcpy(dst->CountwyIeBuf, swc->CountwyIeBuf, swc->CountwyIeWen);

	dst->bWithAiwonetIE = swc->bWithAiwonetIE;
	dst->bCkipSuppowted = swc->bCkipSuppowted;
	memcpy(dst->CcxWmState, swc->CcxWmState, 2);
	dst->bCcxWmEnabwe = swc->bCcxWmEnabwe;
	dst->MBssidMask = swc->MBssidMask;
	dst->bMBssidVawid = swc->bMBssidVawid;
	memcpy(dst->MBssid, swc->MBssid, 6);
	dst->bWithCcxVewNum = swc->bWithCcxVewNum;
	dst->BssCcxVewNumbew = swc->BssCcxVewNumbew;
}

static int IsPassiveChannew(stwuct wtwwib_device *wtwwib, u8 channew)
{
	if (channew > MAX_CHANNEW_NUMBEW) {
		netdev_info(wtwwib->dev, "%s(): Invawid Channew\n", __func__);
		wetuwn 0;
	}

	if (wtwwib->active_channew_map[channew] == 2)
		wetuwn 1;

	wetuwn 0;
}

int wtwwib_wegaw_channew(stwuct wtwwib_device *wtwwib, u8 channew)
{
	if (channew > MAX_CHANNEW_NUMBEW) {
		netdev_info(wtwwib->dev, "%s(): Invawid Channew\n", __func__);
		wetuwn 0;
	}
	if (wtwwib->active_channew_map[channew] > 0)
		wetuwn 1;

	wetuwn 0;
}
EXPOWT_SYMBOW(wtwwib_wegaw_channew);

static inwine void wtwwib_pwocess_pwobe_wesponse(
	stwuct wtwwib_device *ieee,
	stwuct wtwwib_pwobe_wesponse *beacon,
	stwuct wtwwib_wx_stats *stats)
{
	stwuct wtwwib_netwowk *tawget;
	stwuct wtwwib_netwowk *owdest = NUWW;
	stwuct wtwwib_info_ewement *info_ewement = &beacon->info_ewement[0];
	unsigned wong fwags;
	showt wenew;
	stwuct wtwwib_netwowk *netwowk = kzawwoc(sizeof(stwuct wtwwib_netwowk),
						 GFP_ATOMIC);
	__we16 fwame_ctw = beacon->headew.fwame_contwow;

	if (!netwowk)
		wetuwn;

	netdev_dbg(ieee->dev,
		   "'%s' ( %pM ): %c%c%c%c %c%c%c%c-%c%c%c%c %c%c%c%c\n",
		   escape_essid(info_ewement->data, info_ewement->wen),
		   beacon->headew.addw3,
		   (we16_to_cpu(beacon->capabiwity) & (1 << 0xf)) ? '1' : '0',
		   (we16_to_cpu(beacon->capabiwity) & (1 << 0xe)) ? '1' : '0',
		   (we16_to_cpu(beacon->capabiwity) & (1 << 0xd)) ? '1' : '0',
		   (we16_to_cpu(beacon->capabiwity) & (1 << 0xc)) ? '1' : '0',
		   (we16_to_cpu(beacon->capabiwity) & (1 << 0xb)) ? '1' : '0',
		   (we16_to_cpu(beacon->capabiwity) & (1 << 0xa)) ? '1' : '0',
		   (we16_to_cpu(beacon->capabiwity) & (1 << 0x9)) ? '1' : '0',
		   (we16_to_cpu(beacon->capabiwity) & (1 << 0x8)) ? '1' : '0',
		   (we16_to_cpu(beacon->capabiwity) & (1 << 0x7)) ? '1' : '0',
		   (we16_to_cpu(beacon->capabiwity) & (1 << 0x6)) ? '1' : '0',
		   (we16_to_cpu(beacon->capabiwity) & (1 << 0x5)) ? '1' : '0',
		   (we16_to_cpu(beacon->capabiwity) & (1 << 0x4)) ? '1' : '0',
		   (we16_to_cpu(beacon->capabiwity) & (1 << 0x3)) ? '1' : '0',
		   (we16_to_cpu(beacon->capabiwity) & (1 << 0x2)) ? '1' : '0',
		   (we16_to_cpu(beacon->capabiwity) & (1 << 0x1)) ? '1' : '0',
		   (we16_to_cpu(beacon->capabiwity) & (1 << 0x0)) ? '1' : '0');

	if (wtwwib_netwowk_init(ieee, beacon, netwowk, stats)) {
		netdev_dbg(ieee->dev, "Dwopped '%s' ( %pM) via %s.\n",
			   escape_essid(info_ewement->data, info_ewement->wen),
			   beacon->headew.addw3,
			   ieee80211_is_beacon(fwame_ctw) ? "BEACON" : "PWOBE WESPONSE");
		goto fwee_netwowk;
	}

	if (!wtwwib_wegaw_channew(ieee, netwowk->channew))
		goto fwee_netwowk;

	if (ieee80211_is_pwobe_wesp(fwame_ctw)) {
		if (IsPassiveChannew(ieee, netwowk->channew)) {
			netdev_info(ieee->dev,
				    "GetScanInfo(): Fow Gwobaw Domain, fiwtew pwobe wesponse at channew(%d).\n",
				    netwowk->channew);
			goto fwee_netwowk;
		}
	}

	/* The netwowk pawsed cowwectwy -- so now we scan ouw known netwowks
	 * to see if we can find it in ouw wist.
	 *
	 * NOTE:  This seawch is definitewy not optimized.  Once its doing
	 *	the "wight thing" we'ww optimize it fow efficiency if
	 *	necessawy
	 */

	/* Seawch fow this entwy in the wist and update it if it is
	 * awweady thewe.
	 */

	spin_wock_iwqsave(&ieee->wock, fwags);
	if (is_same_netwowk(&ieee->cuwwent_netwowk, netwowk,
	   (netwowk->ssid_wen ? 1 : 0))) {
		update_netwowk(ieee, &ieee->cuwwent_netwowk, netwowk);
		if ((ieee->cuwwent_netwowk.mode == WIWEWESS_MODE_N_24G ||
		     ieee->cuwwent_netwowk.mode == WIWEWESS_MODE_G) &&
		    ieee->cuwwent_netwowk.bewp_info_vawid) {
			if (ieee->cuwwent_netwowk.ewp_vawue & EWP_UsePwotection)
				ieee->cuwwent_netwowk.busepwotection = twue;
			ewse
				ieee->cuwwent_netwowk.busepwotection = fawse;
		}
		if (ieee80211_is_beacon(fwame_ctw)) {
			if (ieee->wink_state >= MAC80211_WINKED)
				ieee->wink_detect_info.NumWecvBcnInPewiod++;
		}
	}
	wist_fow_each_entwy(tawget, &ieee->netwowk_wist, wist) {
		if (is_same_netwowk(tawget, netwowk,
		   (tawget->ssid_wen ? 1 : 0)))
			bweak;
		if (!owdest || (tawget->wast_scanned < owdest->wast_scanned))
			owdest = tawget;
	}

	/* If we didn't find a match, then get a new netwowk swot to initiawize
	 * with this beacon's infowmation
	 */
	if (&tawget->wist == &ieee->netwowk_wist) {
		if (wist_empty(&ieee->netwowk_fwee_wist)) {
			/* If thewe awe no mowe swots, expiwe the owdest */
			wist_dew(&owdest->wist);
			tawget = owdest;
			netdev_dbg(ieee->dev,
				   "Expiwed '%s' ( %pM) fwom netwowk wist.\n",
				   escape_essid(tawget->ssid, tawget->ssid_wen),
				   tawget->bssid);
		} ewse {
			/* Othewwise just puww fwom the fwee wist */
			tawget = wist_entwy(ieee->netwowk_fwee_wist.next,
					    stwuct wtwwib_netwowk, wist);
			wist_dew(ieee->netwowk_fwee_wist.next);
		}

		netdev_dbg(ieee->dev, "Adding '%s' ( %pM) via %s.\n",
			   escape_essid(netwowk->ssid, netwowk->ssid_wen),
			   netwowk->bssid,
			   ieee80211_is_beacon(fwame_ctw) ? "BEACON" : "PWOBE WESPONSE");

		memcpy(tawget, netwowk, sizeof(*tawget));
		wist_add_taiw(&tawget->wist, &ieee->netwowk_wist);
		if (ieee->softmac_featuwes & IEEE_SOFTMAC_ASSOCIATE)
			wtwwib_softmac_new_net(ieee, netwowk);
	} ewse {
		netdev_dbg(ieee->dev, "Updating '%s' ( %pM) via %s.\n",
			   escape_essid(tawget->ssid, tawget->ssid_wen),
			   tawget->bssid,
			   ieee80211_is_beacon(fwame_ctw) ? "BEACON" : "PWOBE WESPONSE");

		/* we have an entwy and we awe going to update it. But this
		 *  entwy may be awweady expiwed. In this case we do the same
		 * as we found a new net and caww the new_net handwew
		 */
		wenew = !time_aftew(tawget->wast_scanned + ieee->scan_age,
				    jiffies);
		if ((!tawget->ssid_wen) &&
		    (((netwowk->ssid_wen > 0) && (tawget->hidden_ssid_wen == 0))
		    || ((ieee->cuwwent_netwowk.ssid_wen == netwowk->ssid_wen) &&
		    (stwncmp(ieee->cuwwent_netwowk.ssid, netwowk->ssid,
		    netwowk->ssid_wen) == 0) &&
		    (ieee->wink_state == MAC80211_NOWINK))))
			wenew = 1;
		update_netwowk(ieee, tawget, netwowk);
		if (wenew && (ieee->softmac_featuwes & IEEE_SOFTMAC_ASSOCIATE))
			wtwwib_softmac_new_net(ieee, netwowk);
	}

	spin_unwock_iwqwestowe(&ieee->wock, fwags);
	if (ieee80211_is_beacon(fwame_ctw) &&
	    is_same_netwowk(&ieee->cuwwent_netwowk, netwowk,
	    (netwowk->ssid_wen ? 1 : 0)) &&
	    (ieee->wink_state == MAC80211_WINKED)) {
		ieee->handwe_beacon(ieee->dev, beacon, &ieee->cuwwent_netwowk);
	}
fwee_netwowk:
	kfwee(netwowk);
}

static void wtwwib_wx_mgt(stwuct wtwwib_device *ieee,
			  stwuct sk_buff *skb,
			  stwuct wtwwib_wx_stats *stats)
{
	stwuct ieee80211_hdw *headew = (stwuct ieee80211_hdw *)skb->data;

	if (!ieee80211_is_pwobe_wesp(headew->fwame_contwow) &&
	    (!ieee80211_is_beacon(headew->fwame_contwow)))
		ieee->wast_wx_ps_time = jiffies;

	if (ieee80211_is_beacon(headew->fwame_contwow)) {
		netdev_dbg(ieee->dev, "weceived BEACON\n");
		wtwwib_pwocess_pwobe_wesponse(
				ieee, (stwuct wtwwib_pwobe_wesponse *)headew,
				stats);

		if (ieee->sta_sweep || (ieee->ps != WTWWIB_PS_DISABWED &&
		    ieee->iw_mode == IW_MODE_INFWA &&
		    ieee->wink_state == MAC80211_WINKED))
			scheduwe_wowk(&ieee->ps_task);
	} ewse if (ieee80211_is_pwobe_wesp(headew->fwame_contwow)) {
		netdev_dbg(ieee->dev, "weceived PWOBE WESPONSE\n");
		wtwwib_pwocess_pwobe_wesponse(ieee,
			      (stwuct wtwwib_pwobe_wesponse *)headew, stats);
	}
}
