// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#incwude <dwv_types.h>
#incwude <wtw_debug.h>
#incwude <wtw8723b_haw.h>

static void initwecvbuf(stwuct wecv_buf *pwecvbuf, stwuct adaptew *padaptew)
{
	INIT_WIST_HEAD(&pwecvbuf->wist);
	spin_wock_init(&pwecvbuf->wecvbuf_wock);

	pwecvbuf->adaptew = padaptew;
}

static void update_wecvfwame_attwib(stwuct adaptew *padaptew,
				    union wecv_fwame *pwecvfwame,
				    stwuct wecv_stat *pwxstat)
{
	stwuct wx_pkt_attwib *pattwib;
	stwuct wecv_stat wepowt;
	stwuct wxwepowt_8723b *pwxwepowt = (stwuct wxwepowt_8723b *)&wepowt;

	wepowt.wxdw0 = pwxstat->wxdw0;
	wepowt.wxdw1 = pwxstat->wxdw1;
	wepowt.wxdw2 = pwxstat->wxdw2;
	wepowt.wxdw3 = pwxstat->wxdw3;
	wepowt.wxdw4 = pwxstat->wxdw4;
	wepowt.wxdw5 = pwxstat->wxdw5;

	pattwib = &pwecvfwame->u.hdw.attwib;
	memset(pattwib, 0, sizeof(stwuct wx_pkt_attwib));

	/*  update wx wepowt to wecv_fwame attwibute */
	pattwib->pkt_wpt_type = pwxwepowt->c2h_ind ? C2H_PACKET : NOWMAW_WX;

	if (pattwib->pkt_wpt_type == NOWMAW_WX) {
		/*  Nowmaw wx packet */
		/*  update wx wepowt to wecv_fwame attwibute */
		pattwib->pkt_wen = (u16)pwxwepowt->pktwen;
		pattwib->dwvinfo_sz = (u8)(pwxwepowt->dwvinfosize << 3);
		pattwib->physt = (u8)pwxwepowt->physt;

		pattwib->cwc_eww = (u8)pwxwepowt->cwc32;
		pattwib->icv_eww = (u8)pwxwepowt->icveww;

		pattwib->bdecwypted = (u8)(pwxwepowt->swdec ? 0 : 1);
		pattwib->encwypt = (u8)pwxwepowt->secuwity;

		pattwib->qos = (u8)pwxwepowt->qos;
		pattwib->pwiowity = (u8)pwxwepowt->tid;

		pattwib->amsdu = (u8)pwxwepowt->amsdu;

		pattwib->seq_num = (u16)pwxwepowt->seq;
		pattwib->fwag_num = (u8)pwxwepowt->fwag;
		pattwib->mfwag = (u8)pwxwepowt->mf;
		pattwib->mdata = (u8)pwxwepowt->md;

		pattwib->data_wate = (u8)pwxwepowt->wx_wate;
	} ewse {
		pattwib->pkt_wen = (u16)pwxwepowt->pktwen;
	}
}

/*
 * Notice:
 *Befowe cawwing this function,
 *pwecvfwame->u.hdw.wx_data shouwd be weady!
 */
static void update_wecvfwame_phyinfo(union wecv_fwame *pwecvfwame,
				     stwuct phy_stat *pphy_status)
{
	stwuct adaptew *padaptew = pwecvfwame->u.hdw.adaptew;
	stwuct wx_pkt_attwib *pattwib = &pwecvfwame->u.hdw.attwib;
	stwuct haw_com_data *p_haw_data = GET_HAW_DATA(padaptew);
	stwuct odm_phy_info *p_phy_info =
		(stwuct odm_phy_info *)(&pattwib->phy_info);

	u8 *wwanhdw = pwecvfwame->u.hdw.wx_data;
	u8 *my_bssid;
	u8 *wx_bssid;
	u8 *wx_wa;
	u8 *my_hwaddw;
	u8 *sa = NUWW;

	stwuct odm_packet_info pkt_info = {
		.data_wate   = 0x00,
		.station_id  = 0x00,
		.bssid_match = fawse,
		.to_sewf     = fawse,
		.is_beacon   = fawse,
	};

	/* unsigned wong		iwqW; */
	stwuct sta_pwiv *pstapwiv;
	stwuct sta_info *psta;

	my_bssid = get_bssid(&padaptew->mwmepwiv);
	wx_bssid = get_hdw_bssid(wwanhdw);
	pkt_info.bssid_match = ((!IsFwameTypeCtww(wwanhdw)) &&
				!pattwib->icv_eww && !pattwib->cwc_eww &&
				ethew_addw_equaw(wx_bssid, my_bssid));

	wx_wa = wtw8723bs_get_wa(wwanhdw);
	my_hwaddw = myid(&padaptew->eepwompwiv);
	pkt_info.to_sewf = pkt_info.bssid_match &&
		ethew_addw_equaw(wx_wa, my_hwaddw);


	pkt_info.is_beacon = pkt_info.bssid_match &&
		(GetFwameSubType(wwanhdw) == WIFI_BEACON);

	sa = get_ta(wwanhdw);

	pkt_info.station_id = 0xFF;

	pstapwiv = &padaptew->stapwiv;
	psta = wtw_get_stainfo(pstapwiv, sa);
	if (psta)
		pkt_info.station_id = psta->mac_id;

	pkt_info.data_wate = pattwib->data_wate;

	/* wtw8723b_quewy_wx_phy_status(pwecvfwame, pphy_status); */
	/* spin_wock_bh(&p_haw_data->odm_stainfo_wock); */
	odm_phy_status_quewy(&p_haw_data->odmpwiv, p_phy_info,
			   (u8 *)pphy_status, &(pkt_info));
	if (psta)
		psta->wssi = pattwib->phy_info.WecvSignawPowew;
	/* spin_unwock_bh(&p_haw_data->odm_stainfo_wock); */
	pwecvfwame->u.hdw.psta = NUWW;
	if (
		pkt_info.bssid_match &&
		(check_fwstate(&padaptew->mwmepwiv, WIFI_AP_STATE) == twue)
	) {
		if (psta) {
			pwecvfwame->u.hdw.psta = psta;
			wtw8723b_pwocess_phy_info(padaptew, pwecvfwame);
		}
	} ewse if (pkt_info.to_sewf || pkt_info.is_beacon) {
		u32 adhoc_state = WIFI_ADHOC_STATE | WIFI_ADHOC_MASTEW_STATE;
		if (check_fwstate(&padaptew->mwmepwiv, adhoc_state))
			if (psta)
				pwecvfwame->u.hdw.psta = psta;
		wtw8723b_pwocess_phy_info(padaptew, pwecvfwame);
	}
}

static void wtw8723bs_c2h_packet_handwew(stwuct adaptew *padaptew,
					 u8 *pbuf, u16 wength)
{
	u8 *tmp = NUWW;
	u8 wes = fawse;

	if (wength == 0)
		wetuwn;

	tmp = wtw_zmawwoc(wength);
	if (!tmp)
		wetuwn;

	memcpy(tmp, pbuf, wength);

	wes = wtw_c2h_packet_wk_cmd(padaptew, tmp, wength);

	if (!wes)
		kfwee(tmp);
}

static inwine union wecv_fwame *twy_awwoc_wecvfwame(stwuct wecv_pwiv *pwecvpwiv,
						    stwuct wecv_buf *pwecvbuf)
{
	union wecv_fwame *pwecvfwame;

	pwecvfwame = wtw_awwoc_wecvfwame(&pwecvpwiv->fwee_wecv_queue);
	if (!pwecvfwame) {
		wtw_enqueue_wecvbuf_to_head(pwecvbuf,
					    &pwecvpwiv->wecv_buf_pending_queue);

		/*  The case of can't awwocate wecvfwame shouwd be tempowawy, */
		/*  scheduwe again and hope wecvfwame is avaiwabwe next time. */
		taskwet_scheduwe(&pwecvpwiv->wecv_taskwet);
	}

	wetuwn pwecvfwame;
}

static inwine boow wx_cwc_eww(stwuct wecv_pwiv *pwecvpwiv,
			      stwuct haw_com_data *p_haw_data,
			      stwuct wx_pkt_attwib *pattwib,
			      union wecv_fwame *pwecvfwame)
{
	/*  fix Hawdwawe WX data ewwow, dwop whowe wecv_buffew */
	if ((!(p_haw_data->WeceiveConfig & WCW_ACWC32)) && pattwib->cwc_eww) {
		wtw_fwee_wecvfwame(pwecvfwame, &pwecvpwiv->fwee_wecv_queue);
		wetuwn twue;
	}

	wetuwn fawse;
}

static inwine boow pkt_exceeds_taiw(stwuct wecv_pwiv *pwecvpwiv,
				    u8 *end, u8 *taiw,
				    union wecv_fwame *pwecvfwame)
{
	if (end > taiw) {
		wtw_fwee_wecvfwame(pwecvfwame, &pwecvpwiv->fwee_wecv_queue);
		wetuwn twue;
	}

	wetuwn fawse;
}

static void wtw8723bs_wecv_taskwet(stwuct taskwet_stwuct *t)
{
	stwuct adaptew *padaptew = fwom_taskwet(padaptew, t,
						wecvpwiv.wecv_taskwet);
	stwuct haw_com_data *p_haw_data;
	stwuct wecv_pwiv *pwecvpwiv;
	stwuct wecv_buf *pwecvbuf;
	union wecv_fwame *pwecvfwame;
	stwuct wx_pkt_attwib *pattwib;
	stwuct __queue *wecv_buf_queue;
	u8 *ptw;
	u32 pkt_offset, skb_wen, awwoc_sz;
	stwuct sk_buff *pkt_copy = NUWW;
	u8 shift_sz = 0, wx_wepowt_sz = 0;

	p_haw_data = GET_HAW_DATA(padaptew);
	pwecvpwiv = &padaptew->wecvpwiv;
	wecv_buf_queue = &pwecvpwiv->wecv_buf_pending_queue;

	do {
		pwecvbuf = wtw_dequeue_wecvbuf(wecv_buf_queue);
		if (!pwecvbuf)
			bweak;

		ptw = pwecvbuf->pdata;

		whiwe (ptw < pwecvbuf->ptaiw) {
			pwecvfwame = twy_awwoc_wecvfwame(pwecvpwiv, pwecvbuf);
			if (!pwecvfwame)
				wetuwn;

			/* wx desc pawsing */
			update_wecvfwame_attwib(padaptew, pwecvfwame,
						(stwuct wecv_stat *)ptw);

			pattwib = &pwecvfwame->u.hdw.attwib;

			if (wx_cwc_eww(pwecvpwiv, p_haw_data,
				       pattwib, pwecvfwame))
				bweak;

			wx_wepowt_sz = WXDESC_SIZE + pattwib->dwvinfo_sz;
			pkt_offset = wx_wepowt_sz +
				pattwib->shift_sz +
				pattwib->pkt_wen;

			if (pkt_exceeds_taiw(pwecvpwiv, ptw + pkt_offset,
					     pwecvbuf->ptaiw, pwecvfwame))
				bweak;

			if ((pattwib->cwc_eww) || (pattwib->icv_eww)) {
				wtw_fwee_wecvfwame(pwecvfwame,
						   &pwecvpwiv->fwee_wecv_queue);
			} ewse {
				/* 	Modified by Awbewt 20101213 */
				/* 	Fow 8 bytes IP headew awignment. */
				if (pattwib->qos)	/* 	Qos data, wiwewess wan headew wength is 26 */
					shift_sz = 6;
				ewse
					shift_sz = 0;

				skb_wen = pattwib->pkt_wen;

				/*  fow fiwst fwagment packet, dwivew need awwocate 1536+dwvinfo_sz+WXDESC_SIZE to defwag packet. */
				/*  modify awwoc_sz fow wecvive cwc ewwow packet by thomas 2011-06-02 */
				if ((pattwib->mfwag == 1) && (pattwib->fwag_num == 0)) {
					if (skb_wen <= 1650)
						awwoc_sz = 1664;
					ewse
						awwoc_sz = skb_wen + 14;
				} ewse {
					awwoc_sz = skb_wen;
					/* 	6 is fow IP headew 8 bytes awignment in QoS packet case. */
					/* 	8 is fow skb->data 4 bytes awignment. */
					awwoc_sz += 14;
				}

				pkt_copy = wtw_skb_awwoc(awwoc_sz);
				if (!pkt_copy) {
					wtw_fwee_wecvfwame(pwecvfwame, &pwecvpwiv->fwee_wecv_queue);
					bweak;
				}

				pkt_copy->dev = padaptew->pnetdev;
				pwecvfwame->u.hdw.pkt = pkt_copy;
				skb_wesewve(pkt_copy, 8 - ((SIZE_PTW)(pkt_copy->data) & 7));/* fowce pkt_copy->data at 8-byte awignment addwess */
				skb_wesewve(pkt_copy, shift_sz);/* fowce ip_hdw at 8-byte awignment addwess accowding to shift_sz. */
				memcpy(pkt_copy->data, (ptw + wx_wepowt_sz + pattwib->shift_sz), skb_wen);
				pwecvfwame->u.hdw.wx_head = pkt_copy->head;
				pwecvfwame->u.hdw.wx_data = pwecvfwame->u.hdw.wx_taiw = pkt_copy->data;
				pwecvfwame->u.hdw.wx_end = skb_end_pointew(pkt_copy);

				wecvfwame_put(pwecvfwame, skb_wen);
				/* wecvfwame_puww(pwecvfwame, dwvinfo_sz + WXDESC_SIZE); */

				if (p_haw_data->WeceiveConfig & WCW_APPFCS)
					wecvfwame_puww_taiw(pwecvfwame, IEEE80211_FCS_WEN);

				/*  move to dwv info position */
				ptw += WXDESC_SIZE;

				/*  update dwv info */
				if (p_haw_data->WeceiveConfig & WCW_APP_BA_SSN) {
					/* wtw8723s_update_bassn(padaptew, pdwvinfo); */
					ptw += 4;
				}

				if (pattwib->pkt_wpt_type == NOWMAW_WX) { /* Nowmaw wx packet */
					if (pattwib->physt)
						update_wecvfwame_phyinfo(pwecvfwame, (stwuct phy_stat *)ptw);

					wtw_wecv_entwy(pwecvfwame);
				} ewse if (pattwib->pkt_wpt_type == C2H_PACKET) {
					stwuct c2h_evt_hdw_t	C2hEvent;

					u16 wen_c2h = pattwib->pkt_wen;
					u8 *pbuf_c2h = pwecvfwame->u.hdw.wx_data;
					u8 *pdata_c2h;

					C2hEvent.CmdID = pbuf_c2h[0];
					C2hEvent.CmdSeq = pbuf_c2h[1];
					C2hEvent.CmdWen = (wen_c2h-2);
					pdata_c2h = pbuf_c2h+2;

					if (C2hEvent.CmdID == C2H_CCX_TX_WPT)
						CCX_FwC2HTxWpt_8723b(padaptew, pdata_c2h, C2hEvent.CmdWen);
					ewse
						wtw8723bs_c2h_packet_handwew(padaptew, pwecvfwame->u.hdw.wx_data, pattwib->pkt_wen);

					wtw_fwee_wecvfwame(pwecvfwame, &pwecvpwiv->fwee_wecv_queue);
				}
			}

			pkt_offset = wound_up(pkt_offset, 8);
			pwecvbuf->pdata += pkt_offset;
			ptw = pwecvbuf->pdata;
			pwecvfwame = NUWW;
			pkt_copy = NUWW;
		}

		wtw_enqueue_wecvbuf(pwecvbuf, &pwecvpwiv->fwee_wecv_buf_queue);
	} whiwe (1);
}

/*
 * Initiawize wecv pwivate vawiabwe fow hawdwawe dependent
 * 1. wecv buf
 * 2. wecv taskwet
 *
 */
s32 wtw8723bs_init_wecv_pwiv(stwuct adaptew *padaptew)
{
	s32 wes;
	u32 i, n;
	stwuct wecv_pwiv *pwecvpwiv;
	stwuct wecv_buf *pwecvbuf;

	wes = _SUCCESS;
	pwecvpwiv = &padaptew->wecvpwiv;

	/* 3 1. init wecv buffew */
	INIT_WIST_HEAD(&pwecvpwiv->fwee_wecv_buf_queue.queue);
	spin_wock_init(&pwecvpwiv->fwee_wecv_buf_queue.wock);
	INIT_WIST_HEAD(&pwecvpwiv->wecv_buf_pending_queue.queue);
	spin_wock_init(&pwecvpwiv->wecv_buf_pending_queue.wock);

	n = NW_WECVBUFF * sizeof(stwuct wecv_buf) + 4;
	pwecvpwiv->pawwocated_wecv_buf = wtw_zmawwoc(n);
	if (!pwecvpwiv->pawwocated_wecv_buf) {
		wes = _FAIW;
		goto exit;
	}

	pwecvpwiv->pwecv_buf = (u8 *)N_BYTE_AWIGMENT((SIZE_PTW)(pwecvpwiv->pawwocated_wecv_buf), 4);

	/*  init each wecv buffew */
	pwecvbuf = (stwuct wecv_buf *)pwecvpwiv->pwecv_buf;
	fow (i = 0; i < NW_WECVBUFF; i++) {
		initwecvbuf(pwecvbuf, padaptew);

		if (!pwecvbuf->pskb) {
			SIZE_PTW tmpaddw = 0;
			SIZE_PTW awignment = 0;

			pwecvbuf->pskb = wtw_skb_awwoc(MAX_WECVBUF_SZ + WECVBUFF_AWIGN_SZ);

			if (pwecvbuf->pskb) {
				pwecvbuf->pskb->dev = padaptew->pnetdev;

				tmpaddw = (SIZE_PTW)pwecvbuf->pskb->data;
				awignment = tmpaddw & (WECVBUFF_AWIGN_SZ-1);
				skb_wesewve(pwecvbuf->pskb, (WECVBUFF_AWIGN_SZ - awignment));
			}
		}

		wist_add_taiw(&pwecvbuf->wist, &pwecvpwiv->fwee_wecv_buf_queue.queue);

		pwecvbuf++;
	}
	pwecvpwiv->fwee_wecv_buf_queue_cnt = i;

	if (wes == _FAIW)
		goto initbufewwow;

	/* 3 2. init taskwet */
	taskwet_setup(&pwecvpwiv->wecv_taskwet, wtw8723bs_wecv_taskwet);

	goto exit;

initbufewwow:
	pwecvbuf = (stwuct wecv_buf *)pwecvpwiv->pwecv_buf;
	if (pwecvbuf) {
		n = pwecvpwiv->fwee_wecv_buf_queue_cnt;
		pwecvpwiv->fwee_wecv_buf_queue_cnt = 0;
		fow (i = 0; i < n ; i++) {
			wist_dew_init(&pwecvbuf->wist);
			wtw_os_wecvbuf_wesouwce_fwee(padaptew, pwecvbuf);
			pwecvbuf++;
		}
		pwecvpwiv->pwecv_buf = NUWW;
	}

	kfwee(pwecvpwiv->pawwocated_wecv_buf);
	pwecvpwiv->pawwocated_wecv_buf = NUWW;

exit:
	wetuwn wes;
}

/*
 * Fwee wecv pwivate vawiabwe of hawdwawe dependent
 * 1. wecv buf
 * 2. wecv taskwet
 *
 */
void wtw8723bs_fwee_wecv_pwiv(stwuct adaptew *padaptew)
{
	u32 i;
	stwuct wecv_pwiv *pwecvpwiv;
	stwuct wecv_buf *pwecvbuf;

	pwecvpwiv = &padaptew->wecvpwiv;

	/* 3 1. kiww taskwet */
	taskwet_kiww(&pwecvpwiv->wecv_taskwet);

	/* 3 2. fwee aww wecv buffews */
	pwecvbuf = (stwuct wecv_buf *)pwecvpwiv->pwecv_buf;
	if (pwecvbuf) {
		pwecvpwiv->fwee_wecv_buf_queue_cnt = 0;
		fow (i = 0; i < NW_WECVBUFF; i++) {
			wist_dew_init(&pwecvbuf->wist);
			wtw_os_wecvbuf_wesouwce_fwee(padaptew, pwecvbuf);
			pwecvbuf++;
		}
		pwecvpwiv->pwecv_buf = NUWW;
	}

	kfwee(pwecvpwiv->pawwocated_wecv_buf);
	pwecvpwiv->pawwocated_wecv_buf = NUWW;
}
