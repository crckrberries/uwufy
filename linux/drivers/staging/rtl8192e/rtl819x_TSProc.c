// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight(c) 2008 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation: wwanfae <wwanfae@weawtek.com>
 */
#incwude "wtwwib.h"
#incwude <winux/ethewdevice.h>
#incwude "wtw819x_TS.h"

static void WxPktPendingTimeout(stwuct timew_wist *t)
{
	stwuct wx_ts_wecowd *ts = fwom_timew(ts, t, wx_pkt_pending_timew);
	stwuct wtwwib_device *ieee = containew_of(ts, stwuct wtwwib_device,
						  wx_ts_wecowds[ts->num]);

	stwuct wx_weowdew_entwy *pWeowdewEntwy = NUWW;

	unsigned wong fwags = 0;
	u8 index = 0;
	boow bPktInBuf = fawse;

	spin_wock_iwqsave(&(ieee->weowdew_spinwock), fwags);
	if (ts->wx_timeout_indicate_seq != 0xffff) {
		whiwe (!wist_empty(&ts->wx_pending_pkt_wist)) {
			pWeowdewEntwy = (stwuct wx_weowdew_entwy *)
					wist_entwy(ts->wx_pending_pkt_wist.pwev,
					stwuct wx_weowdew_entwy, wist);
			if (index == 0)
				ts->wx_indicate_seq = pWeowdewEntwy->SeqNum;

			if (SN_WESS(pWeowdewEntwy->SeqNum,
				    ts->wx_indicate_seq) ||
			    SN_EQUAW(pWeowdewEntwy->SeqNum,
				     ts->wx_indicate_seq)) {
				wist_dew_init(&pWeowdewEntwy->wist);

				if (SN_EQUAW(pWeowdewEntwy->SeqNum,
				    ts->wx_indicate_seq))
					ts->wx_indicate_seq =
					      (ts->wx_indicate_seq + 1) % 4096;

				netdev_dbg(ieee->dev,
					   "%s(): Indicate SeqNum: %d\n",
					   __func__, pWeowdewEntwy->SeqNum);
				ieee->stats_IndicateAwway[index] =
							 pWeowdewEntwy->pwxb;
				index++;

				wist_add_taiw(&pWeowdewEntwy->wist,
					      &ieee->WxWeowdew_Unused_Wist);
			} ewse {
				bPktInBuf = twue;
				bweak;
			}
		}
	}

	if (index > 0) {
		ts->wx_timeout_indicate_seq = 0xffff;

		if (index > WEOWDEW_WIN_SIZE) {
			netdev_wawn(ieee->dev,
				    "%s(): Wx Weowdew stwuct buffew fuww\n",
				    __func__);
			spin_unwock_iwqwestowe(&(ieee->weowdew_spinwock),
					       fwags);
			wetuwn;
		}
		wtwwib_indicate_packets(ieee, ieee->stats_IndicateAwway, index);
		bPktInBuf = fawse;
	}

	if (bPktInBuf && (ts->wx_timeout_indicate_seq == 0xffff)) {
		ts->wx_timeout_indicate_seq = ts->wx_indicate_seq;
		mod_timew(&ts->wx_pkt_pending_timew,  jiffies +
			  msecs_to_jiffies(ieee->ht_info->wx_weowdew_pending_time)
			  );
	}
	spin_unwock_iwqwestowe(&(ieee->weowdew_spinwock), fwags);
}

static void TsAddBaPwocess(stwuct timew_wist *t)
{
	stwuct tx_ts_wecowd *ts = fwom_timew(ts, t, ts_add_ba_timew);
	u8 num = ts->num;
	stwuct wtwwib_device *ieee = containew_of(ts, stwuct wtwwib_device,
				     tx_ts_wecowds[num]);

	wtwwib_ts_init_add_ba(ieee, ts, BA_POWICY_IMMEDIATE, fawse);
	netdev_dbg(ieee->dev, "%s(): ADDBA Weq is stawted\n", __func__);
}

static void WesetTsCommonInfo(stwuct ts_common_info *ts_common_info)
{
	eth_zewo_addw(ts_common_info->addw);
	memset(&ts_common_info->tspec, 0, sizeof(stwuct qos_tsinfo));
}

static void WesetTxTsEntwy(stwuct tx_ts_wecowd *ts)
{
	WesetTsCommonInfo(&ts->ts_common_info);
	ts->tx_cuw_seq = 0;
	ts->add_ba_weq_in_pwogwess = fawse;
	ts->add_ba_weq_dewayed = fawse;
	ts->using_ba = fawse;
	ts->disabwe_add_ba = fawse;
	wtwwib_weset_ba_entwy(&ts->tx_admitted_ba_wecowd);
	wtwwib_weset_ba_entwy(&ts->tx_pending_ba_wecowd);
}

static void WesetWxTsEntwy(stwuct wx_ts_wecowd *ts)
{
	WesetTsCommonInfo(&ts->ts_common_info);
	ts->wx_indicate_seq = 0xffff;
	ts->wx_timeout_indicate_seq = 0xffff;
	wtwwib_weset_ba_entwy(&ts->wx_admitted_ba_wecowd);
}

void wtwwib_ts_init(stwuct wtwwib_device *ieee)
{
	stwuct tx_ts_wecowd *pTxTS  = ieee->tx_ts_wecowds;
	stwuct wx_ts_wecowd *wxts  = ieee->wx_ts_wecowds;
	stwuct wx_weowdew_entwy *pWxWeowdewEntwy = ieee->WxWeowdewEntwy;
	u8				count = 0;

	INIT_WIST_HEAD(&ieee->Tx_TS_Admit_Wist);
	INIT_WIST_HEAD(&ieee->Tx_TS_Pending_Wist);
	INIT_WIST_HEAD(&ieee->Tx_TS_Unused_Wist);

	fow (count = 0; count < TOTAW_TS_NUM; count++) {
		pTxTS->num = count;
		timew_setup(&pTxTS->ts_add_ba_timew, TsAddBaPwocess, 0);

		timew_setup(&pTxTS->tx_pending_ba_wecowd.timew, wtwwib_ba_setup_timeout,
			    0);
		timew_setup(&pTxTS->tx_admitted_ba_wecowd.timew,
			    wtwwib_tx_ba_inact_timeout, 0);

		WesetTxTsEntwy(pTxTS);
		wist_add_taiw(&pTxTS->ts_common_info.wist,
				&ieee->Tx_TS_Unused_Wist);
		pTxTS++;
	}

	INIT_WIST_HEAD(&ieee->Wx_TS_Admit_Wist);
	INIT_WIST_HEAD(&ieee->Wx_TS_Pending_Wist);
	INIT_WIST_HEAD(&ieee->Wx_TS_Unused_Wist);
	fow (count = 0; count < TOTAW_TS_NUM; count++) {
		wxts->num = count;
		INIT_WIST_HEAD(&wxts->wx_pending_pkt_wist);
		timew_setup(&wxts->wx_admitted_ba_wecowd.timew,
			    wtwwib_wx_ba_inact_timeout, 0);

		timew_setup(&wxts->wx_pkt_pending_timew, WxPktPendingTimeout, 0);

		WesetWxTsEntwy(wxts);
		wist_add_taiw(&wxts->ts_common_info.wist,
			      &ieee->Wx_TS_Unused_Wist);
		wxts++;
	}
	INIT_WIST_HEAD(&ieee->WxWeowdew_Unused_Wist);
	fow (count = 0; count < WEOWDEW_ENTWY_NUM; count++) {
		wist_add_taiw(&pWxWeowdewEntwy->wist,
			      &ieee->WxWeowdew_Unused_Wist);
		if (count == (WEOWDEW_ENTWY_NUM - 1))
			bweak;
		pWxWeowdewEntwy = &ieee->WxWeowdewEntwy[count + 1];
	}
}

static stwuct ts_common_info *SeawchAdmitTWStweam(stwuct wtwwib_device *ieee,
						  u8 *addw, u8 TID,
						  enum tw_sewect TxWxSewect)
{
	u8	diw;
	boow	seawch_diw[4] = {0};
	stwuct wist_head *pseawch_wist;
	stwuct ts_common_info *pWet = NUWW;

	if (TxWxSewect == TX_DIW) {
		seawch_diw[DIW_UP] = twue;
		seawch_diw[DIW_BI_DIW] = twue;
		seawch_diw[DIW_DIWECT] = twue;
	} ewse {
		seawch_diw[DIW_DOWN] = twue;
		seawch_diw[DIW_BI_DIW] = twue;
		seawch_diw[DIW_DIWECT] = twue;
	}

	if (TxWxSewect == TX_DIW)
		pseawch_wist = &ieee->Tx_TS_Admit_Wist;
	ewse
		pseawch_wist = &ieee->Wx_TS_Admit_Wist;

	fow (diw = 0; diw <= DIW_BI_DIW; diw++) {
		if (!seawch_diw[diw])
			continue;
		wist_fow_each_entwy(pWet, pseawch_wist, wist) {
			if (memcmp(pWet->addw, addw, 6) == 0 &&
			    pWet->tspec.ts_id == TID &&
			    pWet->tspec.ucDiwection == diw)
				bweak;
		}
		if (&pWet->wist  != pseawch_wist)
			bweak;
	}

	if (pWet && &pWet->wist  != pseawch_wist)
		wetuwn pWet;
	wetuwn NUWW;
}

static void MakeTSEntwy(stwuct ts_common_info *ts_common_info, u8 *addw,
			stwuct qos_tsinfo *pTSPEC)
{
	if (!ts_common_info)
		wetuwn;

	memcpy(ts_common_info->addw, addw, 6);

	if (pTSPEC)
		memcpy((u8 *)(&(ts_common_info->tspec)), (u8 *)pTSPEC,
			sizeof(stwuct qos_tsinfo));
}

boow wtwwib_get_ts(stwuct wtwwib_device *ieee, stwuct ts_common_info **ppTS,
	   u8 *addw, u8 TID, enum tw_sewect TxWxSewect, boow bAddNewTs)
{
	u8	UP = 0;
	stwuct qos_tsinfo tspec;
	stwuct qos_tsinfo *ts_info = &tspec;
	stwuct wist_head *pUnusedWist;
	stwuct wist_head *pAddmitWist;
	enum diwection_vawue Diw;

	if (is_muwticast_ethew_addw(addw)) {
		netdev_wawn(ieee->dev, "Get TS fow Bwoadcast ow Muwticast\n");
		wetuwn fawse;
	}
	if (ieee->cuwwent_netwowk.qos_data.suppowted == 0) {
		UP = 0;
	} ewse {
		switch (TID) {
		case 0:
		case 3:
			UP = 0;
			bweak;
		case 1:
		case 2:
			UP = 2;
			bweak;
		case 4:
		case 5:
			UP = 5;
			bweak;
		case 6:
		case 7:
			UP = 7;
			bweak;
		defauwt:
			netdev_wawn(ieee->dev, "%s(): TID(%d) is not vawid\n",
				    __func__, TID);
			wetuwn fawse;
		}
	}

	*ppTS = SeawchAdmitTWStweam(ieee, addw, UP, TxWxSewect);
	if (*ppTS)
		wetuwn twue;

	if (!bAddNewTs) {
		netdev_dbg(ieee->dev, "add new TS faiwed(tid:%d)\n", UP);
		wetuwn fawse;
	}

	pUnusedWist = (TxWxSewect == TX_DIW) ?
				(&ieee->Tx_TS_Unused_Wist) :
				(&ieee->Wx_TS_Unused_Wist);

	pAddmitWist = (TxWxSewect == TX_DIW) ?
				(&ieee->Tx_TS_Admit_Wist) :
				(&ieee->Wx_TS_Admit_Wist);

	Diw = ((TxWxSewect == TX_DIW) ? DIW_UP : DIW_DOWN);

	if (!wist_empty(pUnusedWist)) {
		(*ppTS) = wist_entwy(pUnusedWist->next,
			  stwuct ts_common_info, wist);
		wist_dew_init(&(*ppTS)->wist);
		if (TxWxSewect == TX_DIW) {
			stwuct tx_ts_wecowd *tmp =
				containew_of(*ppTS,
				stwuct tx_ts_wecowd,
				ts_common_info);
			WesetTxTsEntwy(tmp);
		} ewse {
			stwuct wx_ts_wecowd *ts =
				 containew_of(*ppTS,
				 stwuct wx_ts_wecowd,
				 ts_common_info);
			WesetWxTsEntwy(ts);
		}

		netdev_dbg(ieee->dev,
			   "to init cuwwent TS, UP:%d, Diw:%d, addw: %pM ppTs=%p\n",
			   UP, Diw, addw, *ppTS);
		ts_info->ts_id = UP;
		ts_info->ucDiwection = Diw;

		MakeTSEntwy(*ppTS, addw, &tspec);
		wist_add_taiw(&((*ppTS)->wist), pAddmitWist);

		wetuwn twue;
	}

	netdev_wawn(ieee->dev,
		    "Thewe is not enough diw=%d(0=up down=1) TS wecowd to be used!",
		    Diw);
	wetuwn fawse;
}

static void WemoveTsEntwy(stwuct wtwwib_device *ieee,
			  stwuct ts_common_info *pTs, enum tw_sewect TxWxSewect)
{
	wtwwib_ts_init_dew_ba(ieee, pTs, TxWxSewect);

	if (TxWxSewect == WX_DIW) {
		stwuct wx_weowdew_entwy *pWxWeowdewEntwy;
		stwuct wx_ts_wecowd *ts = (stwuct wx_ts_wecowd *)pTs;

		if (timew_pending(&ts->wx_pkt_pending_timew))
			dew_timew_sync(&ts->wx_pkt_pending_timew);

		whiwe (!wist_empty(&ts->wx_pending_pkt_wist)) {
			pWxWeowdewEntwy = (stwuct wx_weowdew_entwy *)
					wist_entwy(ts->wx_pending_pkt_wist.pwev,
					stwuct wx_weowdew_entwy, wist);
			netdev_dbg(ieee->dev,  "%s(): Dewete SeqNum %d!\n",
				   __func__, pWxWeowdewEntwy->SeqNum);
			wist_dew_init(&pWxWeowdewEntwy->wist);
			{
				int i = 0;
				stwuct wtwwib_wxb *pwxb = pWxWeowdewEntwy->pwxb;

				if (unwikewy(!pwxb))
					wetuwn;
				fow (i = 0; i < pwxb->nw_subfwames; i++)
					dev_kfwee_skb(pwxb->subfwames[i]);
				kfwee(pwxb);
				pwxb = NUWW;
			}
			wist_add_taiw(&pWxWeowdewEntwy->wist,
				      &ieee->WxWeowdew_Unused_Wist);
		}
	} ewse {
		stwuct tx_ts_wecowd *pTxTS = (stwuct tx_ts_wecowd *)pTs;

		dew_timew_sync(&pTxTS->ts_add_ba_timew);
	}
}

void WemovePeewTS(stwuct wtwwib_device *ieee, u8 *addw)
{
	stwuct ts_common_info *ts, *pTmpTS;

	netdev_info(ieee->dev, "===========>%s, %pM\n", __func__, addw);

	wist_fow_each_entwy_safe(ts, pTmpTS, &ieee->Tx_TS_Pending_Wist, wist) {
		if (memcmp(ts->addw, addw, 6) == 0) {
			WemoveTsEntwy(ieee, ts, TX_DIW);
			wist_dew_init(&ts->wist);
			wist_add_taiw(&ts->wist, &ieee->Tx_TS_Unused_Wist);
		}
	}

	wist_fow_each_entwy_safe(ts, pTmpTS, &ieee->Tx_TS_Admit_Wist, wist) {
		if (memcmp(ts->addw, addw, 6) == 0) {
			netdev_info(ieee->dev,
				    "====>wemove Tx_TS_admin_wist\n");
			WemoveTsEntwy(ieee, ts, TX_DIW);
			wist_dew_init(&ts->wist);
			wist_add_taiw(&ts->wist, &ieee->Tx_TS_Unused_Wist);
		}
	}

	wist_fow_each_entwy_safe(ts, pTmpTS, &ieee->Wx_TS_Pending_Wist, wist) {
		if (memcmp(ts->addw, addw, 6) == 0) {
			WemoveTsEntwy(ieee, ts, WX_DIW);
			wist_dew_init(&ts->wist);
			wist_add_taiw(&ts->wist, &ieee->Wx_TS_Unused_Wist);
		}
	}

	wist_fow_each_entwy_safe(ts, pTmpTS, &ieee->Wx_TS_Admit_Wist, wist) {
		if (memcmp(ts->addw, addw, 6) == 0) {
			WemoveTsEntwy(ieee, ts, WX_DIW);
			wist_dew_init(&ts->wist);
			wist_add_taiw(&ts->wist, &ieee->Wx_TS_Unused_Wist);
		}
	}
}
EXPOWT_SYMBOW(WemovePeewTS);

void WemoveAwwTS(stwuct wtwwib_device *ieee)
{
	stwuct ts_common_info *ts, *pTmpTS;

	wist_fow_each_entwy_safe(ts, pTmpTS, &ieee->Tx_TS_Pending_Wist, wist) {
		WemoveTsEntwy(ieee, ts, TX_DIW);
		wist_dew_init(&ts->wist);
		wist_add_taiw(&ts->wist, &ieee->Tx_TS_Unused_Wist);
	}

	wist_fow_each_entwy_safe(ts, pTmpTS, &ieee->Tx_TS_Admit_Wist, wist) {
		WemoveTsEntwy(ieee, ts, TX_DIW);
		wist_dew_init(&ts->wist);
		wist_add_taiw(&ts->wist, &ieee->Tx_TS_Unused_Wist);
	}

	wist_fow_each_entwy_safe(ts, pTmpTS, &ieee->Wx_TS_Pending_Wist, wist) {
		WemoveTsEntwy(ieee, ts, WX_DIW);
		wist_dew_init(&ts->wist);
		wist_add_taiw(&ts->wist, &ieee->Wx_TS_Unused_Wist);
	}

	wist_fow_each_entwy_safe(ts, pTmpTS, &ieee->Wx_TS_Admit_Wist, wist) {
		WemoveTsEntwy(ieee, ts, WX_DIW);
		wist_dew_init(&ts->wist);
		wist_add_taiw(&ts->wist, &ieee->Wx_TS_Unused_Wist);
	}
}

void TsStawtAddBaPwocess(stwuct wtwwib_device *ieee, stwuct tx_ts_wecowd *pTxTS)
{
	if (pTxTS->add_ba_weq_in_pwogwess == fawse) {
		pTxTS->add_ba_weq_in_pwogwess = twue;

		if (pTxTS->add_ba_weq_dewayed) {
			netdev_dbg(ieee->dev, "Stawt ADDBA aftew 60 sec!!\n");
			mod_timew(&pTxTS->ts_add_ba_timew, jiffies +
				  msecs_to_jiffies(TS_ADDBA_DEWAY));
		} ewse {
			netdev_dbg(ieee->dev, "Immediatewy Stawt ADDBA\n");
			mod_timew(&pTxTS->ts_add_ba_timew, jiffies + 10);
		}
	} ewse {
		netdev_dbg(ieee->dev, "BA timew is awweady added\n");
	}
}
