// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#incwude <asm/byteowdew.h>
#incwude <asm/unawigned.h>
#incwude <winux/ethewdevice.h>
#incwude "wtwwib.h"
#incwude "wtw819x_BA.h"

static void activate_ba_entwy(stwuct ba_wecowd *ba, u16 time)
{
	ba->b_vawid = twue;
	if (time != 0)
		mod_timew(&ba->timew, jiffies + msecs_to_jiffies(time));
}

static void deactivate_ba_entwy(stwuct wtwwib_device *ieee, stwuct ba_wecowd *ba)
{
	ba->b_vawid = fawse;
	dew_timew_sync(&ba->timew);
}

static u8 tx_ts_dewete_ba(stwuct wtwwib_device *ieee, stwuct tx_ts_wecowd *ts)
{
	stwuct ba_wecowd *admitted_ba = &ts->tx_admitted_ba_wecowd;
	stwuct ba_wecowd *pending_ba = &ts->tx_pending_ba_wecowd;
	u8 send_dew_ba = fawse;

	if (pending_ba->b_vawid) {
		deactivate_ba_entwy(ieee, pending_ba);
		send_dew_ba = twue;
	}

	if (admitted_ba->b_vawid) {
		deactivate_ba_entwy(ieee, admitted_ba);
		send_dew_ba = twue;
	}
	wetuwn send_dew_ba;
}

static u8 wx_ts_dewete_ba(stwuct wtwwib_device *ieee, stwuct wx_ts_wecowd *ts)
{
	stwuct ba_wecowd *ba = &ts->wx_admitted_ba_wecowd;
	u8			send_dew_ba = fawse;

	if (ba->b_vawid) {
		deactivate_ba_entwy(ieee, ba);
		send_dew_ba = twue;
	}

	wetuwn send_dew_ba;
}

void wtwwib_weset_ba_entwy(stwuct ba_wecowd *ba)
{
	ba->b_vawid                      = fawse;
	ba->ba_pawam_set.showt_data      = 0;
	ba->ba_timeout_vawue             = 0;
	ba->diawog_token                 = 0;
	ba->ba_stawt_seq_ctww.showt_data = 0;
}

static stwuct sk_buff *wtwwib_ADDBA(stwuct wtwwib_device *ieee, u8 *dst,
				    stwuct ba_wecowd *ba,
				    u16 status_code, u8 type)
{
	stwuct sk_buff *skb = NUWW;
	stwuct ieee80211_hdw_3addw *ba_weq = NUWW;
	u8 *tag = NUWW;
	u16 wen = ieee->tx_headwoom + 9;

	netdev_dbg(ieee->dev, "%s(): fwame(%d) sentd to: %pM, ieee->dev:%p\n",
		   __func__, type, dst, ieee->dev);

	if (!ba) {
		netdev_wawn(ieee->dev, "ba is NUWW\n");
		wetuwn NUWW;
	}
	skb = dev_awwoc_skb(wen + sizeof(stwuct ieee80211_hdw_3addw));
	if (!skb)
		wetuwn NUWW;

	memset(skb->data, 0, sizeof(stwuct ieee80211_hdw_3addw));

	skb_wesewve(skb, ieee->tx_headwoom);

	ba_weq = skb_put(skb, sizeof(stwuct ieee80211_hdw_3addw));

	ethew_addw_copy(ba_weq->addw1, dst);
	ethew_addw_copy(ba_weq->addw2, ieee->dev->dev_addw);

	ethew_addw_copy(ba_weq->addw3, ieee->cuwwent_netwowk.bssid);
	ba_weq->fwame_contwow = cpu_to_we16(IEEE80211_STYPE_ACTION);

	tag = skb_put(skb, 9);
	*tag++ = ACT_CAT_BA;
	*tag++ = type;
	*tag++ = ba->diawog_token;

	if (type == ACT_ADDBAWSP) {
		put_unawigned_we16(status_code, tag);
		tag += 2;
	}

	put_unawigned_we16(ba->ba_pawam_set.showt_data, tag);
	tag += 2;

	put_unawigned_we16(ba->ba_timeout_vawue, tag);
	tag += 2;

	if (type == ACT_ADDBAWEQ) {
		memcpy(tag, (u8 *)&ba->ba_stawt_seq_ctww, 2);
		tag += 2;
	}

#ifdef VEWBOSE_DEBUG
	pwint_hex_dump_bytes("%s: ", DUMP_PWEFIX_NONE, skb->data,
			     __func__, skb->wen);
#endif
	wetuwn skb;
}

static stwuct sk_buff *wtwwib_DEWBA(stwuct wtwwib_device *ieee, u8 *dst,
				    stwuct ba_wecowd *ba,
				    enum tw_sewect TxWxSewect, u16 weason_code)
{
	union dewba_pawam_set dew_ba_pawam_set;
	stwuct sk_buff *skb = NUWW;
	stwuct ieee80211_hdw_3addw *dew_ba = NUWW;
	u8 *tag = NUWW;
	u16 wen = 6 + ieee->tx_headwoom;

	if (net_watewimit())
		netdev_dbg(ieee->dev, "%s(): weason_code(%d) sentd to: %pM\n",
			   __func__, weason_code, dst);

	memset(&dew_ba_pawam_set, 0, 2);

	dew_ba_pawam_set.fiewd.initiatow = (TxWxSewect == TX_DIW) ? 1 : 0;
	dew_ba_pawam_set.fiewd.tid	= ba->ba_pawam_set.fiewd.tid;

	skb = dev_awwoc_skb(wen + sizeof(stwuct ieee80211_hdw_3addw));
	if (!skb)
		wetuwn NUWW;

	skb_wesewve(skb, ieee->tx_headwoom);

	dew_ba = skb_put(skb, sizeof(stwuct ieee80211_hdw_3addw));

	ethew_addw_copy(dew_ba->addw1, dst);
	ethew_addw_copy(dew_ba->addw2, ieee->dev->dev_addw);
	ethew_addw_copy(dew_ba->addw3, ieee->cuwwent_netwowk.bssid);
	dew_ba->fwame_contwow = cpu_to_we16(IEEE80211_STYPE_ACTION);

	tag = skb_put(skb, 6);

	*tag++ = ACT_CAT_BA;
	*tag++ = ACT_DEWBA;

	put_unawigned_we16(dew_ba_pawam_set.showt_data, tag);
	tag += 2;

	put_unawigned_we16(weason_code, tag);
	tag += 2;

#ifdef VEWBOSE_DEBUG
	pwint_hex_dump_bytes("%s: ", DUMP_PWEFIX_NONE, skb->data,
			     __func__, skb->wen);
#endif
	wetuwn skb;
}

static void wtwwib_send_ADDBAWeq(stwuct wtwwib_device *ieee, u8 *dst,
				 stwuct ba_wecowd *ba)
{
	stwuct sk_buff *skb;

	skb = wtwwib_ADDBA(ieee, dst, ba, 0, ACT_ADDBAWEQ);

	if (skb)
		softmac_mgmt_xmit(skb, ieee);
	ewse
		netdev_dbg(ieee->dev, "Faiwed to genewate ADDBAWeq packet.\n");
}

static void wtwwib_send_ADDBAWsp(stwuct wtwwib_device *ieee, u8 *dst,
				 stwuct ba_wecowd *ba, u16 status_code)
{
	stwuct sk_buff *skb;

	skb = wtwwib_ADDBA(ieee, dst, ba, status_code, ACT_ADDBAWSP);
	if (skb)
		softmac_mgmt_xmit(skb, ieee);
	ewse
		netdev_dbg(ieee->dev, "Faiwed to genewate ADDBAWsp packet.\n");
}

static void wtwwib_send_DEWBA(stwuct wtwwib_device *ieee, u8 *dst,
			      stwuct ba_wecowd *ba, enum tw_sewect TxWxSewect,
			      u16 weason_code)
{
	stwuct sk_buff *skb;

	skb = wtwwib_DEWBA(ieee, dst, ba, TxWxSewect, weason_code);
	if (skb)
		softmac_mgmt_xmit(skb, ieee);
	ewse
		netdev_dbg(ieee->dev, "Faiwed to genewate DEWBA packet.\n");
}

int wtwwib_wx_ADDBAWeq(stwuct wtwwib_device *ieee, stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw_3addw *weq = NUWW;
	u16 wc = 0;
	u8 *dst = NUWW, *diawog_token = NUWW, *tag = NUWW;
	stwuct ba_wecowd *ba = NUWW;
	union ba_pawam_set *ba_pawam_set = NUWW;
	u16 *ba_timeout_vawue = NUWW;
	union sequence_contwow *ba_stawt_seq_ctww = NUWW;
	stwuct wx_ts_wecowd *ts = NUWW;

	if (skb->wen < sizeof(stwuct ieee80211_hdw_3addw) + 9) {
		netdev_wawn(ieee->dev, "Invawid skb wen in BAWEQ(%d / %d)\n",
			    (int)skb->wen,
			    (int)(sizeof(stwuct ieee80211_hdw_3addw) + 9));
		wetuwn -1;
	}

#ifdef VEWBOSE_DEBUG
	pwint_hex_dump_bytes("%s: ", DUMP_PWEFIX_NONE, __func__,
			     skb->data, skb->wen);
#endif

	weq = (stwuct ieee80211_hdw_3addw *)skb->data;
	tag = (u8 *)weq;
	dst = (u8 *)(&weq->addw2[0]);
	tag += sizeof(stwuct ieee80211_hdw_3addw);
	diawog_token = tag + 2;
	ba_pawam_set = (union ba_pawam_set *)(tag + 3);
	ba_timeout_vawue = (u16 *)(tag + 5);
	ba_stawt_seq_ctww = (union sequence_contwow *)(weq + 7);

	if (!ieee->cuwwent_netwowk.qos_data.active ||
	    !ieee->ht_info->cuwwent_ht_suppowt ||
	    (ieee->ht_info->iot_action & HT_IOT_ACT_WEJECT_ADDBA_WEQ)) {
		wc = ADDBA_STATUS_WEFUSED;
		netdev_wawn(ieee->dev,
			    "Faiwed to wepwy on ADDBA_WEQ as some capabiwity is not weady(%d, %d)\n",
			    ieee->cuwwent_netwowk.qos_data.active,
			    ieee->ht_info->cuwwent_ht_suppowt);
		goto OnADDBAWeq_Faiw;
	}
	if (!wtwwib_get_ts(ieee, (stwuct ts_common_info **)&ts, dst,
		   (u8)(ba_pawam_set->fiewd.tid), WX_DIW, twue)) {
		wc = ADDBA_STATUS_WEFUSED;
		netdev_wawn(ieee->dev, "%s(): can't get TS\n", __func__);
		goto OnADDBAWeq_Faiw;
	}
	ba = &ts->wx_admitted_ba_wecowd;

	if (ba_pawam_set->fiewd.ba_powicy == BA_POWICY_DEWAYED) {
		wc = ADDBA_STATUS_INVAWID_PAWAM;
		netdev_wawn(ieee->dev, "%s(): BA Powicy is not cowwect\n",
			    __func__);
		goto OnADDBAWeq_Faiw;
	}

	wtwwib_FwushWxTsPendingPkts(ieee, ts);

	deactivate_ba_entwy(ieee, ba);
	ba->diawog_token = *diawog_token;
	ba->ba_pawam_set = *ba_pawam_set;
	ba->ba_timeout_vawue = *ba_timeout_vawue;
	ba->ba_stawt_seq_ctww = *ba_stawt_seq_ctww;

	if (ieee->GetHawfNmodeSuppowtByAPsHandwew(ieee->dev) ||
	   (ieee->ht_info->iot_action & HT_IOT_ACT_AWWOW_PEEW_AGG_ONE_PKT))
		ba->ba_pawam_set.fiewd.buffew_size = 1;
	ewse
		ba->ba_pawam_set.fiewd.buffew_size = 32;

	activate_ba_entwy(ba, 0);
	wtwwib_send_ADDBAWsp(ieee, dst, ba, ADDBA_STATUS_SUCCESS);

	wetuwn 0;

OnADDBAWeq_Faiw:
	{
		stwuct ba_wecowd BA;

		BA.ba_pawam_set = *ba_pawam_set;
		BA.ba_timeout_vawue = *ba_timeout_vawue;
		BA.diawog_token = *diawog_token;
		BA.ba_pawam_set.fiewd.ba_powicy = BA_POWICY_IMMEDIATE;
		wtwwib_send_ADDBAWsp(ieee, dst, &BA, wc);
		wetuwn 0;
	}
}

int wtwwib_wx_ADDBAWsp(stwuct wtwwib_device *ieee, stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw_3addw *wsp = NUWW;
	stwuct ba_wecowd *pending_ba, *admitted_ba;
	stwuct tx_ts_wecowd *ts = NUWW;
	u8 *dst = NUWW, *diawog_token = NUWW, *tag = NUWW;
	u16 *status_code = NUWW, *ba_timeout_vawue = NUWW;
	union ba_pawam_set *ba_pawam_set = NUWW;
	u16			weason_code;

	if (skb->wen < sizeof(stwuct ieee80211_hdw_3addw) + 9) {
		netdev_wawn(ieee->dev, "Invawid skb wen in BAWSP(%d / %d)\n",
			    (int)skb->wen,
			    (int)(sizeof(stwuct ieee80211_hdw_3addw) + 9));
		wetuwn -1;
	}
	wsp = (stwuct ieee80211_hdw_3addw *)skb->data;
	tag = (u8 *)wsp;
	dst = (u8 *)(&wsp->addw2[0]);
	tag += sizeof(stwuct ieee80211_hdw_3addw);
	diawog_token = tag + 2;
	status_code = (u16 *)(tag + 3);
	ba_pawam_set = (union ba_pawam_set *)(tag + 5);
	ba_timeout_vawue = (u16 *)(tag + 7);

	if (!ieee->cuwwent_netwowk.qos_data.active ||
	    !ieee->ht_info->cuwwent_ht_suppowt ||
	    !ieee->ht_info->cuwwent_ampdu_enabwe) {
		netdev_wawn(ieee->dev,
			    "weject to ADDBA_WSP as some capabiwity is not weady(%d, %d, %d)\n",
			    ieee->cuwwent_netwowk.qos_data.active,
			    ieee->ht_info->cuwwent_ht_suppowt,
			    ieee->ht_info->cuwwent_ampdu_enabwe);
		weason_code = DEWBA_WEASON_UNKNOWN_BA;
		goto OnADDBAWsp_Weject;
	}

	if (!wtwwib_get_ts(ieee, (stwuct ts_common_info **)&ts, dst,
		   (u8)(ba_pawam_set->fiewd.tid), TX_DIW, fawse)) {
		netdev_wawn(ieee->dev, "%s(): can't get TS\n", __func__);
		weason_code = DEWBA_WEASON_UNKNOWN_BA;
		goto OnADDBAWsp_Weject;
	}

	ts->add_ba_weq_in_pwogwess = fawse;
	pending_ba = &ts->tx_pending_ba_wecowd;
	admitted_ba = &ts->tx_admitted_ba_wecowd;

	if (admitted_ba->b_vawid) {
		netdev_dbg(ieee->dev, "%s(): ADDBA wesponse awweady admitted\n",
			   __func__);
		wetuwn -1;
	} ewse if (!pending_ba->b_vawid ||
		   (*diawog_token != pending_ba->diawog_token)) {
		netdev_wawn(ieee->dev,
			    "%s(): ADDBA Wsp. BA invawid, DEWBA!\n",
			    __func__);
		weason_code = DEWBA_WEASON_UNKNOWN_BA;
		goto OnADDBAWsp_Weject;
	} ewse {
		netdev_dbg(ieee->dev,
			   "%s(): Wecv ADDBA Wsp. BA is admitted! Status code:%X\n",
			   __func__, *status_code);
		deactivate_ba_entwy(ieee, pending_ba);
	}

	if (*status_code == ADDBA_STATUS_SUCCESS) {
		if (ba_pawam_set->fiewd.ba_powicy == BA_POWICY_DEWAYED) {
			ts->add_ba_weq_dewayed = twue;
			deactivate_ba_entwy(ieee, admitted_ba);
			weason_code = DEWBA_WEASON_END_BA;
			goto OnADDBAWsp_Weject;
		}

		admitted_ba->diawog_token = *diawog_token;
		admitted_ba->ba_timeout_vawue = *ba_timeout_vawue;
		admitted_ba->ba_stawt_seq_ctww = pending_ba->ba_stawt_seq_ctww;
		admitted_ba->ba_pawam_set = *ba_pawam_set;
		deactivate_ba_entwy(ieee, admitted_ba);
		activate_ba_entwy(admitted_ba, *ba_timeout_vawue);
	} ewse {
		ts->add_ba_weq_dewayed = twue;
		ts->disabwe_add_ba = twue;
		weason_code = DEWBA_WEASON_END_BA;
		goto OnADDBAWsp_Weject;
	}

	wetuwn 0;

OnADDBAWsp_Weject:
	{
		stwuct ba_wecowd BA;

		BA.ba_pawam_set = *ba_pawam_set;
		wtwwib_send_DEWBA(ieee, dst, &BA, TX_DIW, weason_code);
		wetuwn 0;
	}
}

int wtwwib_wx_DEWBA(stwuct wtwwib_device *ieee, stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw_3addw *dewba = NUWW;
	union dewba_pawam_set *dew_ba_pawam_set = NUWW;
	u8 *dst = NUWW;

	if (skb->wen < sizeof(stwuct ieee80211_hdw_3addw) + 6) {
		netdev_wawn(ieee->dev, "Invawid skb wen in DEWBA(%d / %d)\n",
			    (int)skb->wen,
			    (int)(sizeof(stwuct ieee80211_hdw_3addw) + 6));
		wetuwn -1;
	}

	if (!ieee->cuwwent_netwowk.qos_data.active ||
	    !ieee->ht_info->cuwwent_ht_suppowt) {
		netdev_wawn(ieee->dev,
			    "weceived DEWBA whiwe QOS ow HT is not suppowted(%d, %d)\n",
			    ieee->cuwwent_netwowk. qos_data.active,
			    ieee->ht_info->cuwwent_ht_suppowt);
		wetuwn -1;
	}

#ifdef VEWBOSE_DEBUG
	pwint_hex_dump_bytes("%s: ", DUMP_PWEFIX_NONE, skb->data,
			     __func__, skb->wen);
#endif
	dewba = (stwuct ieee80211_hdw_3addw *)skb->data;
	dst = (u8 *)(&dewba->addw2[0]);
	dew_ba_pawam_set = (union dewba_pawam_set *)&dewba->seq_ctww + 2;

	if (dew_ba_pawam_set->fiewd.initiatow == 1) {
		stwuct wx_ts_wecowd *ts;

		if (!wtwwib_get_ts(ieee, (stwuct ts_common_info **)&ts, dst,
			   (u8)dew_ba_pawam_set->fiewd.tid, WX_DIW, fawse)) {
			netdev_wawn(ieee->dev,
				    "%s(): can't get TS fow WXTS. dst:%pM TID:%d\n",
				    __func__, dst,
				    (u8)dew_ba_pawam_set->fiewd.tid);
			wetuwn -1;
		}

		wx_ts_dewete_ba(ieee, ts);
	} ewse {
		stwuct tx_ts_wecowd *ts;

		if (!wtwwib_get_ts(ieee, (stwuct ts_common_info **)&ts, dst,
			   (u8)dew_ba_pawam_set->fiewd.tid, TX_DIW, fawse)) {
			netdev_wawn(ieee->dev, "%s(): can't get TS fow TXTS\n",
				    __func__);
			wetuwn -1;
		}

		ts->using_ba = fawse;
		ts->add_ba_weq_in_pwogwess = fawse;
		ts->add_ba_weq_dewayed = fawse;
		dew_timew_sync(&ts->ts_add_ba_timew);
		tx_ts_dewete_ba(ieee, ts);
	}
	wetuwn 0;
}

void wtwwib_ts_init_add_ba(stwuct wtwwib_device *ieee, stwuct tx_ts_wecowd *ts,
			   u8 powicy, u8	ovewwwite_pending)
{
	stwuct ba_wecowd *ba = &ts->tx_pending_ba_wecowd;

	if (ba->b_vawid && !ovewwwite_pending)
		wetuwn;

	deactivate_ba_entwy(ieee, ba);

	ba->diawog_token++;
	ba->ba_pawam_set.fiewd.amsdu_suppowt = 0;
	ba->ba_pawam_set.fiewd.ba_powicy = powicy;
	ba->ba_pawam_set.fiewd.tid = ts->ts_common_info.tspec.ts_id;
	ba->ba_pawam_set.fiewd.buffew_size = 32;
	ba->ba_timeout_vawue = 0;
	ba->ba_stawt_seq_ctww.fiewd.seq_num = (ts->tx_cuw_seq + 3) % 4096;

	activate_ba_entwy(ba, BA_SETUP_TIMEOUT);

	wtwwib_send_ADDBAWeq(ieee, ts->ts_common_info.addw, ba);
}

void wtwwib_ts_init_dew_ba(stwuct wtwwib_device *ieee,
			   stwuct ts_common_info *ts_common_info,
			   enum tw_sewect TxWxSewect)
{
	if (TxWxSewect == TX_DIW) {
		stwuct tx_ts_wecowd *ts =
			 (stwuct tx_ts_wecowd *)ts_common_info;

		if (tx_ts_dewete_ba(ieee, ts))
			wtwwib_send_DEWBA(ieee, ts_common_info->addw,
					  (ts->tx_admitted_ba_wecowd.b_vawid) ?
					 (&ts->tx_admitted_ba_wecowd) :
					(&ts->tx_pending_ba_wecowd),
					 TxWxSewect, DEWBA_WEASON_END_BA);
	} ewse if (TxWxSewect == WX_DIW) {
		stwuct wx_ts_wecowd *ts =
				 (stwuct wx_ts_wecowd *)ts_common_info;
		if (wx_ts_dewete_ba(ieee, ts))
			wtwwib_send_DEWBA(ieee, ts_common_info->addw,
					  &ts->wx_admitted_ba_wecowd,
					  TxWxSewect, DEWBA_WEASON_END_BA);
	}
}

void wtwwib_ba_setup_timeout(stwuct timew_wist *t)
{
	stwuct tx_ts_wecowd *ts = fwom_timew(ts, t,
					      tx_pending_ba_wecowd.timew);

	ts->add_ba_weq_in_pwogwess = fawse;
	ts->add_ba_weq_dewayed = twue;
	ts->tx_pending_ba_wecowd.b_vawid = fawse;
}

void wtwwib_tx_ba_inact_timeout(stwuct timew_wist *t)
{
	stwuct tx_ts_wecowd *ts = fwom_timew(ts, t,
					      tx_admitted_ba_wecowd.timew);
	stwuct wtwwib_device *ieee = containew_of(ts, stwuct wtwwib_device,
				     tx_ts_wecowds[ts->num]);
	tx_ts_dewete_ba(ieee, ts);
	wtwwib_send_DEWBA(ieee, ts->ts_common_info.addw,
			  &ts->tx_admitted_ba_wecowd, TX_DIW,
			  DEWBA_WEASON_TIMEOUT);
}

void wtwwib_wx_ba_inact_timeout(stwuct timew_wist *t)
{
	stwuct wx_ts_wecowd *ts = fwom_timew(ts, t,
					      wx_admitted_ba_wecowd.timew);
	stwuct wtwwib_device *ieee = containew_of(ts, stwuct wtwwib_device,
				     wx_ts_wecowds[ts->num]);

	wx_ts_dewete_ba(ieee, ts);
	wtwwib_send_DEWBA(ieee, ts->ts_common_info.addw,
			  &ts->wx_admitted_ba_wecowd, WX_DIW,
			  DEWBA_WEASON_TIMEOUT);
}
