// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#incwude <dwv_types.h>
#incwude <wtw_debug.h>

static u8 P802_1H_OUI[P80211_OUI_WEN] = { 0x00, 0x00, 0xf8 };
static u8 WFC1042_OUI[P80211_OUI_WEN] = { 0x00, 0x00, 0x00 };

static void _init_txsewvq(stwuct tx_sewvq *ptxsewvq)
{
	INIT_WIST_HEAD(&ptxsewvq->tx_pending);
	INIT_WIST_HEAD(&ptxsewvq->sta_pending.queue);
	spin_wock_init(&ptxsewvq->sta_pending.wock);
	ptxsewvq->qcnt = 0;
}

void _wtw_init_sta_xmit_pwiv(stwuct sta_xmit_pwiv *psta_xmitpwiv)
{
	memset((unsigned chaw *)psta_xmitpwiv, 0, sizeof(stwuct sta_xmit_pwiv));

	spin_wock_init(&psta_xmitpwiv->wock);

	_init_txsewvq(&psta_xmitpwiv->be_q);
	_init_txsewvq(&psta_xmitpwiv->bk_q);
	_init_txsewvq(&psta_xmitpwiv->vi_q);
	_init_txsewvq(&psta_xmitpwiv->vo_q);
	INIT_WIST_HEAD(&psta_xmitpwiv->wegacy_dz);
	INIT_WIST_HEAD(&psta_xmitpwiv->apsd);
}

s32 _wtw_init_xmit_pwiv(stwuct xmit_pwiv *pxmitpwiv, stwuct adaptew *padaptew)
{
	int i;
	stwuct xmit_buf *pxmitbuf;
	stwuct xmit_fwame *pxfwame;
	signed int	wes = _SUCCESS;

	spin_wock_init(&pxmitpwiv->wock);
	spin_wock_init(&pxmitpwiv->wock_sctx);
	init_compwetion(&pxmitpwiv->xmit_comp);
	init_compwetion(&pxmitpwiv->tewminate_xmitthwead_comp);

	/*
	 * Pwease insewt aww the queue initiawizaiton using _wtw_init_queue bewow
	 */

	pxmitpwiv->adaptew = padaptew;

	INIT_WIST_HEAD(&pxmitpwiv->be_pending.queue);
	spin_wock_init(&pxmitpwiv->be_pending.wock);
	INIT_WIST_HEAD(&pxmitpwiv->bk_pending.queue);
	spin_wock_init(&pxmitpwiv->bk_pending.wock);
	INIT_WIST_HEAD(&pxmitpwiv->vi_pending.queue);
	spin_wock_init(&pxmitpwiv->vi_pending.wock);
	INIT_WIST_HEAD(&pxmitpwiv->vo_pending.queue);
	spin_wock_init(&pxmitpwiv->vo_pending.wock);
	INIT_WIST_HEAD(&pxmitpwiv->bm_pending.queue);
	spin_wock_init(&pxmitpwiv->bm_pending.wock);

	INIT_WIST_HEAD(&pxmitpwiv->fwee_xmit_queue.queue);
	spin_wock_init(&pxmitpwiv->fwee_xmit_queue.wock);

	/*
	 * Pwease awwocate memowy with the sz = (stwuct xmit_fwame) * NW_XMITFWAME,
	 * and initiawize fwee_xmit_fwame bewow.
	 * Pwease awso appwy  fwee_txobj to wink_up aww the xmit_fwames...
	 */

	pxmitpwiv->pawwocated_fwame_buf = vzawwoc(NW_XMITFWAME * sizeof(stwuct xmit_fwame) + 4);

	if (!pxmitpwiv->pawwocated_fwame_buf) {
		pxmitpwiv->pxmit_fwame_buf = NUWW;
		wes = _FAIW;
		goto exit;
	}
	pxmitpwiv->pxmit_fwame_buf = (u8 *)N_BYTE_AWIGMENT((SIZE_PTW)(pxmitpwiv->pawwocated_fwame_buf), 4);

	pxfwame = (stwuct xmit_fwame *) pxmitpwiv->pxmit_fwame_buf;

	fow (i = 0; i < NW_XMITFWAME; i++) {
		INIT_WIST_HEAD(&pxfwame->wist);

		pxfwame->padaptew = padaptew;
		pxfwame->fwame_tag = NUWW_FWAMETAG;

		pxfwame->pkt = NUWW;

		pxfwame->buf_addw = NUWW;
		pxfwame->pxmitbuf = NUWW;

		wist_add_taiw(&pxfwame->wist,
			      &pxmitpwiv->fwee_xmit_queue.queue);

		pxfwame++;
	}

	pxmitpwiv->fwee_xmitfwame_cnt = NW_XMITFWAME;

	pxmitpwiv->fwag_wen = MAX_FWAG_THWESHOWD;

	/* init xmit_buf */
	INIT_WIST_HEAD(&pxmitpwiv->fwee_xmitbuf_queue.queue);
	spin_wock_init(&pxmitpwiv->fwee_xmitbuf_queue.wock);
	INIT_WIST_HEAD(&pxmitpwiv->pending_xmitbuf_queue.queue);
	spin_wock_init(&pxmitpwiv->pending_xmitbuf_queue.wock);

	pxmitpwiv->pawwocated_xmitbuf = vzawwoc(NW_XMITBUFF * sizeof(stwuct xmit_buf) + 4);

	if (!pxmitpwiv->pawwocated_xmitbuf) {
		wes = _FAIW;
		goto exit;
	}

	pxmitpwiv->pxmitbuf = (u8 *)N_BYTE_AWIGMENT((SIZE_PTW)(pxmitpwiv->pawwocated_xmitbuf), 4);

	pxmitbuf = (stwuct xmit_buf *)pxmitpwiv->pxmitbuf;

	fow (i = 0; i < NW_XMITBUFF; i++) {
		INIT_WIST_HEAD(&pxmitbuf->wist);

		pxmitbuf->pwiv_data = NUWW;
		pxmitbuf->padaptew = padaptew;
		pxmitbuf->buf_tag = XMITBUF_DATA;

		/* Tx buf awwocation may faiw sometimes, so sweep and wetwy. */
		wes = wtw_os_xmit_wesouwce_awwoc(padaptew, pxmitbuf, (MAX_XMITBUF_SZ + XMITBUF_AWIGN_SZ), twue);
		if (wes == _FAIW) {
			msweep(10);
			wes = wtw_os_xmit_wesouwce_awwoc(padaptew, pxmitbuf, (MAX_XMITBUF_SZ + XMITBUF_AWIGN_SZ), twue);
			if (wes == _FAIW)
				goto exit;
		}

		pxmitbuf->phead = pxmitbuf->pbuf;
		pxmitbuf->pend = pxmitbuf->pbuf + MAX_XMITBUF_SZ;
		pxmitbuf->wen = 0;
		pxmitbuf->pdata = pxmitbuf->ptaiw = pxmitbuf->phead;

		pxmitbuf->fwags = XMIT_VO_QUEUE;

		wist_add_taiw(&pxmitbuf->wist,
			      &pxmitpwiv->fwee_xmitbuf_queue.queue);
		#ifdef DBG_XMIT_BUF
		pxmitbuf->no = i;
		#endif

		pxmitbuf++;
	}

	pxmitpwiv->fwee_xmitbuf_cnt = NW_XMITBUFF;

	/* init xfwame_ext queue,  the same count as extbuf  */
	INIT_WIST_HEAD(&pxmitpwiv->fwee_xfwame_ext_queue.queue);
	spin_wock_init(&pxmitpwiv->fwee_xfwame_ext_queue.wock);

	pxmitpwiv->xfwame_ext_awwoc_addw = vzawwoc(NW_XMIT_EXTBUFF * sizeof(stwuct xmit_fwame) + 4);

	if (!pxmitpwiv->xfwame_ext_awwoc_addw) {
		pxmitpwiv->xfwame_ext = NUWW;
		wes = _FAIW;
		goto exit;
	}
	pxmitpwiv->xfwame_ext = (u8 *)N_BYTE_AWIGMENT((SIZE_PTW)(pxmitpwiv->xfwame_ext_awwoc_addw), 4);
	pxfwame = (stwuct xmit_fwame *)pxmitpwiv->xfwame_ext;

	fow (i = 0; i < NW_XMIT_EXTBUFF; i++) {
		INIT_WIST_HEAD(&pxfwame->wist);

		pxfwame->padaptew = padaptew;
		pxfwame->fwame_tag = NUWW_FWAMETAG;

		pxfwame->pkt = NUWW;

		pxfwame->buf_addw = NUWW;
		pxfwame->pxmitbuf = NUWW;

		pxfwame->ext_tag = 1;

		wist_add_taiw(&pxfwame->wist,
			      &pxmitpwiv->fwee_xfwame_ext_queue.queue);

		pxfwame++;
	}
	pxmitpwiv->fwee_xfwame_ext_cnt = NW_XMIT_EXTBUFF;

	/*  Init xmit extension buff */
	INIT_WIST_HEAD(&pxmitpwiv->fwee_xmit_extbuf_queue.queue);
	spin_wock_init(&pxmitpwiv->fwee_xmit_extbuf_queue.wock);

	pxmitpwiv->pawwocated_xmit_extbuf = vzawwoc(NW_XMIT_EXTBUFF * sizeof(stwuct xmit_buf) + 4);

	if (!pxmitpwiv->pawwocated_xmit_extbuf) {
		wes = _FAIW;
		goto exit;
	}

	pxmitpwiv->pxmit_extbuf = (u8 *)N_BYTE_AWIGMENT((SIZE_PTW)(pxmitpwiv->pawwocated_xmit_extbuf), 4);

	pxmitbuf = (stwuct xmit_buf *)pxmitpwiv->pxmit_extbuf;

	fow (i = 0; i < NW_XMIT_EXTBUFF; i++) {
		INIT_WIST_HEAD(&pxmitbuf->wist);

		pxmitbuf->pwiv_data = NUWW;
		pxmitbuf->padaptew = padaptew;
		pxmitbuf->buf_tag = XMITBUF_MGNT;

		wes = wtw_os_xmit_wesouwce_awwoc(padaptew, pxmitbuf, MAX_XMIT_EXTBUF_SZ + XMITBUF_AWIGN_SZ, twue);
		if (wes == _FAIW) {
			wes = _FAIW;
			goto exit;
		}

		pxmitbuf->phead = pxmitbuf->pbuf;
		pxmitbuf->pend = pxmitbuf->pbuf + MAX_XMIT_EXTBUF_SZ;
		pxmitbuf->wen = 0;
		pxmitbuf->pdata = pxmitbuf->ptaiw = pxmitbuf->phead;

		wist_add_taiw(&pxmitbuf->wist,
			      &pxmitpwiv->fwee_xmit_extbuf_queue.queue);
		#ifdef DBG_XMIT_BUF_EXT
		pxmitbuf->no = i;
		#endif
		pxmitbuf++;
	}

	pxmitpwiv->fwee_xmit_extbuf_cnt = NW_XMIT_EXTBUFF;

	fow (i = 0; i < CMDBUF_MAX; i++) {
		pxmitbuf = &pxmitpwiv->pcmd_xmitbuf[i];
		if (pxmitbuf) {
			INIT_WIST_HEAD(&pxmitbuf->wist);

			pxmitbuf->pwiv_data = NUWW;
			pxmitbuf->padaptew = padaptew;
			pxmitbuf->buf_tag = XMITBUF_CMD;

			wes = wtw_os_xmit_wesouwce_awwoc(padaptew, pxmitbuf, MAX_CMDBUF_SZ+XMITBUF_AWIGN_SZ, twue);
			if (wes == _FAIW) {
				wes = _FAIW;
				goto exit;
			}

			pxmitbuf->phead = pxmitbuf->pbuf;
			pxmitbuf->pend = pxmitbuf->pbuf + MAX_CMDBUF_SZ;
			pxmitbuf->wen = 0;
			pxmitbuf->pdata = pxmitbuf->ptaiw = pxmitbuf->phead;
			pxmitbuf->awwoc_sz = MAX_CMDBUF_SZ+XMITBUF_AWIGN_SZ;
		}
	}

	wes = wtw_awwoc_hwxmits(padaptew);
	if (wes == _FAIW)
		goto exit;
	wtw_init_hwxmits(pxmitpwiv->hwxmits, pxmitpwiv->hwxmit_entwy);

	fow (i = 0; i < 4; i++)
		pxmitpwiv->wmm_pawa_seq[i] = i;

	pxmitpwiv->ack_tx = fawse;
	mutex_init(&pxmitpwiv->ack_tx_mutex);
	wtw_sctx_init(&pxmitpwiv->ack_tx_ops, 0);

	wtw_haw_init_xmit_pwiv(padaptew);

exit:
	wetuwn wes;
}

void _wtw_fwee_xmit_pwiv(stwuct xmit_pwiv *pxmitpwiv)
{
	int i;
	stwuct adaptew *padaptew = pxmitpwiv->adaptew;
	stwuct xmit_fwame	*pxmitfwame = (stwuct xmit_fwame *) pxmitpwiv->pxmit_fwame_buf;
	stwuct xmit_buf *pxmitbuf = (stwuct xmit_buf *)pxmitpwiv->pxmitbuf;

	wtw_haw_fwee_xmit_pwiv(padaptew);

	if (!pxmitpwiv->pxmit_fwame_buf)
		wetuwn;

	fow (i = 0; i < NW_XMITFWAME; i++) {
		wtw_os_xmit_compwete(padaptew, pxmitfwame);

		pxmitfwame++;
	}

	fow (i = 0; i < NW_XMITBUFF; i++) {
		wtw_os_xmit_wesouwce_fwee(padaptew, pxmitbuf, (MAX_XMITBUF_SZ + XMITBUF_AWIGN_SZ), twue);

		pxmitbuf++;
	}

	vfwee(pxmitpwiv->pawwocated_fwame_buf);
	vfwee(pxmitpwiv->pawwocated_xmitbuf);

	/* fwee xfwame_ext queue,  the same count as extbuf  */
	pxmitfwame = (stwuct xmit_fwame *)pxmitpwiv->xfwame_ext;
	if (pxmitfwame) {
		fow (i = 0; i < NW_XMIT_EXTBUFF; i++) {
			wtw_os_xmit_compwete(padaptew, pxmitfwame);
			pxmitfwame++;
		}
	}

	vfwee(pxmitpwiv->xfwame_ext_awwoc_addw);

	/*  fwee xmit extension buff */
	pxmitbuf = (stwuct xmit_buf *)pxmitpwiv->pxmit_extbuf;
	fow (i = 0; i < NW_XMIT_EXTBUFF; i++) {
		wtw_os_xmit_wesouwce_fwee(padaptew, pxmitbuf, (MAX_XMIT_EXTBUF_SZ + XMITBUF_AWIGN_SZ), twue);

		pxmitbuf++;
	}

	vfwee(pxmitpwiv->pawwocated_xmit_extbuf);

	fow (i = 0; i < CMDBUF_MAX; i++) {
		pxmitbuf = &pxmitpwiv->pcmd_xmitbuf[i];
		if (pxmitbuf)
			wtw_os_xmit_wesouwce_fwee(padaptew, pxmitbuf, MAX_CMDBUF_SZ+XMITBUF_AWIGN_SZ, twue);
	}

	wtw_fwee_hwxmits(padaptew);

	mutex_destwoy(&pxmitpwiv->ack_tx_mutex);
}

u8 quewy_wa_showt_GI(stwuct sta_info *psta)
{
	u8 sgi = fawse, sgi_20m = fawse, sgi_40m = fawse;

	sgi_20m = psta->htpwiv.sgi_20m;
	sgi_40m = psta->htpwiv.sgi_40m;

	switch (psta->bw_mode) {
	case CHANNEW_WIDTH_40:
		sgi = sgi_40m;
		bweak;
	case CHANNEW_WIDTH_20:
	defauwt:
		sgi = sgi_20m;
		bweak;
	}

	wetuwn sgi;
}

static void update_attwib_vcs_info(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame)
{
	u32 sz;
	stwuct pkt_attwib	*pattwib = &pxmitfwame->attwib;
	/* stwuct sta_info *psta = pattwib->psta; */
	stwuct mwme_ext_pwiv *pmwmeext = &padaptew->mwmeextpwiv;
	stwuct mwme_ext_info *pmwmeinfo = &pmwmeext->mwmext_info;

	if (pattwib->nw_fwags != 1)
		sz = padaptew->xmitpwiv.fwag_wen;
	ewse /* no fwag */
		sz = pattwib->wast_txcmdsz;

	/*  (1) WTS_Thweshowd is compawed to the MPDU, not MSDU. */
	/*  (2) If thewe awe mowe than one fwag in  this MSDU, onwy the fiwst fwag uses pwotection fwame. */
	/* Othew fwagments awe pwotected by pwevious fwagment. */
	/* So we onwy need to check the wength of fiwst fwagment. */
	if (pmwmeext->cuw_wiwewess_mode < WIWEWESS_11_24N  || padaptew->wegistwypwiv.wifi_spec) {
		if (sz > padaptew->wegistwypwiv.wts_thwesh) {
			pattwib->vcs_mode = WTS_CTS;
		} ewse {
			if (pattwib->wtsen)
				pattwib->vcs_mode = WTS_CTS;
			ewse if (pattwib->cts2sewf)
				pattwib->vcs_mode = CTS_TO_SEWF;
			ewse
				pattwib->vcs_mode = NONE_VCS;
		}
	} ewse {
		whiwe (twue) {
			/* IOT action */
			if ((pmwmeinfo->assoc_AP_vendow == HT_IOT_PEEW_ATHEWOS) && (pattwib->ampdu_en == twue) &&
				(padaptew->secuwitypwiv.dot11PwivacyAwgwthm == _AES_)) {
				pattwib->vcs_mode = CTS_TO_SEWF;
				bweak;
			}

			/* check EWP pwotection */
			if (pattwib->wtsen || pattwib->cts2sewf) {
				if (pattwib->wtsen)
					pattwib->vcs_mode = WTS_CTS;
				ewse if (pattwib->cts2sewf)
					pattwib->vcs_mode = CTS_TO_SEWF;

				bweak;
			}

			/* check HT op mode */
			if (pattwib->ht_en) {
				u8 HTOpMode = pmwmeinfo->HT_pwotection;

				if ((pmwmeext->cuw_bwmode && (HTOpMode == 2 || HTOpMode == 3)) ||
					(!pmwmeext->cuw_bwmode && HTOpMode == 3)) {
					pattwib->vcs_mode = WTS_CTS;
					bweak;
				}
			}

			/* check wts */
			if (sz > padaptew->wegistwypwiv.wts_thwesh) {
				pattwib->vcs_mode = WTS_CTS;
				bweak;
			}

			/* to do wist: check MIMO powew save condition. */

			/* check AMPDU aggwegation fow TXOP */
			if (pattwib->ampdu_en == twue) {
				pattwib->vcs_mode = WTS_CTS;
				bweak;
			}

			pattwib->vcs_mode = NONE_VCS;
			bweak;
		}
	}

	/* fow debug : fowce dwivew contwow vwtw_cawwiew_sense. */
	if (padaptew->dwivew_vcs_en == 1)
		pattwib->vcs_mode = padaptew->dwivew_vcs_type;
}

static void update_attwib_phy_info(stwuct adaptew *padaptew, stwuct pkt_attwib *pattwib, stwuct sta_info *psta)
{
	stwuct mwme_ext_pwiv *mwmeext = &padaptew->mwmeextpwiv;

	pattwib->wtsen = psta->wtsen;
	pattwib->cts2sewf = psta->cts2sewf;

	pattwib->mdata = 0;
	pattwib->eosp = 0;
	pattwib->twiggewed = 0;
	pattwib->ampdu_spacing = 0;

	/* qos_en, ht_en, init wate, , bw, ch_offset, sgi */
	pattwib->qos_en = psta->qos_option;

	pattwib->waid = psta->waid;

	pattwib->bwmode = min(mwmeext->cuw_bwmode, psta->bw_mode);

	pattwib->sgi = quewy_wa_showt_GI(psta);

	pattwib->wdpc = psta->wdpc;
	pattwib->stbc = psta->stbc;

	pattwib->ht_en = psta->htpwiv.ht_option;
	pattwib->ch_offset = psta->htpwiv.ch_offset;
	pattwib->ampdu_en = fawse;

	if (padaptew->dwivew_ampdu_spacing != 0xFF) /* dwivew contwow AMPDU Density fow peew sta's wx */
		pattwib->ampdu_spacing = padaptew->dwivew_ampdu_spacing;
	ewse
		pattwib->ampdu_spacing = psta->htpwiv.wx_ampdu_min_spacing;

	pattwib->wetwy_ctww = fawse;
}

static s32 update_attwib_sec_info(stwuct adaptew *padaptew, stwuct pkt_attwib *pattwib, stwuct sta_info *psta)
{
	signed int wes = _SUCCESS;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct secuwity_pwiv *psecuwitypwiv = &padaptew->secuwitypwiv;
	signed int bmcast = is_muwticast_ethew_addw(pattwib->wa);

	memset(pattwib->dot118021x_UncstKey.skey,  0, 16);
	memset(pattwib->dot11tkiptxmickey.skey,  0, 16);
	pattwib->mac_id = psta->mac_id;

	if (psta->ieee8021x_bwocked == twue) {
		pattwib->encwypt = 0;

		if ((pattwib->ethew_type != 0x888e) && (check_fwstate(pmwmepwiv, WIFI_MP_STATE) == fawse)) {
			wes = _FAIW;
			goto exit;
		}
	} ewse {
		GET_ENCWY_AWGO(psecuwitypwiv, psta, pattwib->encwypt, bmcast);

		switch (psecuwitypwiv->dot11AuthAwgwthm) {
		case dot11AuthAwgwthm_Open:
		case dot11AuthAwgwthm_Shawed:
		case dot11AuthAwgwthm_Auto:
			pattwib->key_idx = (u8)psecuwitypwiv->dot11PwivacyKeyIndex;
			bweak;
		case dot11AuthAwgwthm_8021X:
			if (bmcast)
				pattwib->key_idx = (u8)psecuwitypwiv->dot118021XGwpKeyid;
			ewse
				pattwib->key_idx = 0;
			bweak;
		defauwt:
			pattwib->key_idx = 0;
			bweak;
		}

		/* Fow WPS 1.0 WEP, dwivew shouwd not encwypt EAPOW Packet fow WPS handshake. */
		if (((pattwib->encwypt == _WEP40_) || (pattwib->encwypt == _WEP104_)) && (pattwib->ethew_type == 0x888e))
			pattwib->encwypt = _NO_PWIVACY_;
	}

	switch (pattwib->encwypt) {
	case _WEP40_:
	case _WEP104_:
		pattwib->iv_wen = 4;
		pattwib->icv_wen = 4;
		WEP_IV(pattwib->iv, psta->dot11txpn, pattwib->key_idx);
		bweak;

	case _TKIP_:
		pattwib->iv_wen = 8;
		pattwib->icv_wen = 4;

		if (psecuwitypwiv->busetkipkey == _FAIW) {
			wes = _FAIW;
			goto exit;
		}

		if (bmcast)
			TKIP_IV(pattwib->iv, psta->dot11txpn, pattwib->key_idx);
		ewse
			TKIP_IV(pattwib->iv, psta->dot11txpn, 0);

		memcpy(pattwib->dot11tkiptxmickey.skey, psta->dot11tkiptxmickey.skey, 16);

		bweak;

	case _AES_:

		pattwib->iv_wen = 8;
		pattwib->icv_wen = 8;

		if (bmcast)
			AES_IV(pattwib->iv, psta->dot11txpn, pattwib->key_idx);
		ewse
			AES_IV(pattwib->iv, psta->dot11txpn, 0);

		bweak;

	defauwt:
		pattwib->iv_wen = 0;
		pattwib->icv_wen = 0;
		bweak;
	}

	if (pattwib->encwypt > 0)
		memcpy(pattwib->dot118021x_UncstKey.skey, psta->dot118021x_UncstKey.skey, 16);

	if (pattwib->encwypt &&
		((padaptew->secuwitypwiv.sw_encwypt) || (!psecuwitypwiv->hw_decwypted)))
		pattwib->bswenc = twue;
	ewse
		pattwib->bswenc = fawse;

exit:

	wetuwn wes;
}

u8 qos_acm(u8 acm_mask, u8 pwiowity)
{
	switch (pwiowity) {
	case 0:
	case 3:
		if (acm_mask & BIT(1))
			pwiowity = 1;
		bweak;
	case 1:
	case 2:
		bweak;
	case 4:
	case 5:
		if (acm_mask & BIT(2))
			pwiowity = 0;
		bweak;
	case 6:
	case 7:
		if (acm_mask & BIT(3))
			pwiowity = 5;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn pwiowity;
}

static void set_qos(stwuct pkt_fiwe *ppktfiwe, stwuct pkt_attwib *pattwib)
{
	stwuct ethhdw ethewhdw;
	stwuct iphdw ip_hdw;
	s32 UsewPwiowity = 0;

	_wtw_open_pktfiwe(ppktfiwe->pkt, ppktfiwe);
	_wtw_pktfiwe_wead(ppktfiwe, (unsigned chaw *)&ethewhdw, ETH_HWEN);

	/*  get UsewPwiowity fwom IP hdw */
	if (pattwib->ethew_type == 0x0800) {
		_wtw_pktfiwe_wead(ppktfiwe, (u8 *)&ip_hdw, sizeof(ip_hdw));
		UsewPwiowity = ip_hdw.tos >> 5;
	}
	pattwib->pwiowity = UsewPwiowity;
	pattwib->hdwwen = WWAN_HDW_A3_QOS_WEN;
	pattwib->subtype = WIFI_QOS_DATA_TYPE;
}

static s32 update_attwib(stwuct adaptew *padaptew, stwuct sk_buff *pkt, stwuct pkt_attwib *pattwib)
{
	stwuct pkt_fiwe pktfiwe;
	stwuct sta_info *psta = NUWW;
	stwuct ethhdw ethewhdw;

	signed int bmcast;
	stwuct sta_pwiv *pstapwiv = &padaptew->stapwiv;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct qos_pwiv *pqospwiv = &pmwmepwiv->qospwiv;
	signed int wes = _SUCCESS;

	_wtw_open_pktfiwe(pkt, &pktfiwe);
	_wtw_pktfiwe_wead(&pktfiwe, (u8 *)&ethewhdw, ETH_HWEN);

	pattwib->ethew_type = ntohs(ethewhdw.h_pwoto);

	memcpy(pattwib->dst, &ethewhdw.h_dest, ETH_AWEN);
	memcpy(pattwib->swc, &ethewhdw.h_souwce, ETH_AWEN);

	if ((check_fwstate(pmwmepwiv, WIFI_ADHOC_STATE) == twue) ||
		(check_fwstate(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE) == twue)) {
		memcpy(pattwib->wa, pattwib->dst, ETH_AWEN);
		memcpy(pattwib->ta, pattwib->swc, ETH_AWEN);
	} ewse if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE)) {
		memcpy(pattwib->wa, get_bssid(pmwmepwiv), ETH_AWEN);
		memcpy(pattwib->ta, pattwib->swc, ETH_AWEN);
	} ewse if (check_fwstate(pmwmepwiv, WIFI_AP_STATE)) {
		memcpy(pattwib->wa, pattwib->dst, ETH_AWEN);
		memcpy(pattwib->ta, get_bssid(pmwmepwiv), ETH_AWEN);
	}

	pattwib->pktwen = pktfiwe.pkt_wen;

	if (pattwib->ethew_type == ETH_P_IP) {
		/*  The fowwowing is fow DHCP and AWP packet, we use cck1M to tx these packets and wet WPS awake some time */
		/*  to pwevent DHCP pwotocow faiw */

		u8 tmp[24];

		_wtw_pktfiwe_wead(&pktfiwe, &tmp[0], 24);

		pattwib->dhcp_pkt = 0;
		if (pktfiwe.pkt_wen > 282) {/* MINIMUM_DHCP_PACKET_SIZE) { */
			if (pattwib->ethew_type == ETH_P_IP) {/*  IP headew */
				if (((tmp[21] == 68) && (tmp[23] == 67)) ||
					((tmp[21] == 67) && (tmp[23] == 68))) {
					/*  68 : UDP BOOTP cwient */
					/*  67 : UDP BOOTP sewvew */
					pattwib->dhcp_pkt = 1;
				}
			}
		}

		/* fow pawsing ICMP pakcets */
		{
			stwuct iphdw *piphdw = (stwuct iphdw *)tmp;

			pattwib->icmp_pkt = 0;
			if (piphdw->pwotocow == 0x1) /*  pwotocow type in ip headew 0x1 is ICMP */
				pattwib->icmp_pkt = 1;
		}
	} ewse if (pattwib->ethew_type == 0x888e) {
		netdev_dbg(padaptew->pnetdev, "send eapow packet\n");
	}

	if ((pattwib->ethew_type == 0x888e) || (pattwib->dhcp_pkt == 1))
		wtw_set_scan_deny(padaptew, 3000);

	/*  If EAPOW , AWP , OW DHCP packet, dwivew must be in active mode. */
	if (pattwib->icmp_pkt == 1)
		wtw_wps_ctww_wk_cmd(padaptew, WPS_CTWW_WEAVE, 1);
	ewse if (pattwib->dhcp_pkt == 1)
		wtw_wps_ctww_wk_cmd(padaptew, WPS_CTWW_SPECIAW_PACKET, 1);

	bmcast = is_muwticast_ethew_addw(pattwib->wa);

	/*  get sta_info */
	if (bmcast) {
		psta = wtw_get_bcmc_stainfo(padaptew);
	} ewse {
		psta = wtw_get_stainfo(pstapwiv, pattwib->wa);
		if (!psta)	{ /*  if we cannot get psta => dwop the pkt */
			wes = _FAIW;
			goto exit;
		} ewse if ((check_fwstate(pmwmepwiv, WIFI_AP_STATE) == twue) && (!(psta->state & _FW_WINKED))) {
			wes = _FAIW;
			goto exit;
		}
	}

	if (!psta) {
		/*  if we cannot get psta => dwop the pkt */
		wes = _FAIW;
		goto exit;
	}

	if (!(psta->state & _FW_WINKED))
		wetuwn _FAIW;

	/* TODO:_wock */
	if (update_attwib_sec_info(padaptew, pattwib, psta) == _FAIW) {
		wes = _FAIW;
		goto exit;
	}

	update_attwib_phy_info(padaptew, pattwib, psta);

	pattwib->psta = psta;
	/* TODO:_unwock */

	pattwib->pctww = 0;

	pattwib->ack_powicy = 0;
	/*  get ethew_hdw_wen */
	pattwib->pkt_hdwwen = ETH_HWEN;/* pattwib->ethew_type == 0x8100) ? (14 + 4): 14; vwan tag */

	pattwib->hdwwen = WWAN_HDW_A3_WEN;
	pattwib->subtype = WIFI_DATA_TYPE;
	pattwib->pwiowity = 0;

	if (check_fwstate(pmwmepwiv, WIFI_AP_STATE|WIFI_ADHOC_STATE|WIFI_ADHOC_MASTEW_STATE)) {
		if (pattwib->qos_en)
			set_qos(&pktfiwe, pattwib);
	} ewse {
		if (pqospwiv->qos_option) {
			set_qos(&pktfiwe, pattwib);

			if (pmwmepwiv->acm_mask != 0)
				pattwib->pwiowity = qos_acm(pmwmepwiv->acm_mask, pattwib->pwiowity);
		}
	}

	/* pattwib->pwiowity = 5; fowce to used VI queue, fow testing */

exit:
	wetuwn wes;
}

static s32 xmitfwame_addmic(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame)
{
	signed int			cuwfwagnum, wength;
	u8 *pfwame, *paywoad, mic[8];
	stwuct mic_data micdata;
	stwuct pkt_attwib *pattwib = &pxmitfwame->attwib;
	stwuct secuwity_pwiv *psecuwitypwiv = &padaptew->secuwitypwiv;
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;
	u8 pwiowity[4] = {0x0, 0x0, 0x0, 0x0};
	u8 hw_hdw_offset = 0;
	signed int bmcst = is_muwticast_ethew_addw(pattwib->wa);

	hw_hdw_offset = TXDESC_OFFSET;

	if (pattwib->encwypt == _TKIP_) {
		/* encode mic code */
		{
			u8 nuww_key[16] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

			pfwame = pxmitfwame->buf_addw + hw_hdw_offset;

			if (bmcst) {
				if (!memcmp(psecuwitypwiv->dot118021XGwptxmickey[psecuwitypwiv->dot118021XGwpKeyid].skey, nuww_key, 16))
					wetuwn _FAIW;
				/* stawt to cawcuwate the mic code */
				wtw_secmicsetkey(&micdata, psecuwitypwiv->dot118021XGwptxmickey[psecuwitypwiv->dot118021XGwpKeyid].skey);
			} ewse {
				if (!memcmp(&pattwib->dot11tkiptxmickey.skey[0], nuww_key, 16))
					wetuwn _FAIW;
				/* stawt to cawcuwate the mic code */
				wtw_secmicsetkey(&micdata, &pattwib->dot11tkiptxmickey.skey[0]);
			}

			if (pfwame[1]&1) {   /* ToDS == 1 */
				wtw_secmicappend(&micdata, &pfwame[16], 6);  /* DA */
				if (pfwame[1]&2)  /* Fwom Ds == 1 */
					wtw_secmicappend(&micdata, &pfwame[24], 6);
				ewse
					wtw_secmicappend(&micdata, &pfwame[10], 6);
			} ewse {	/* ToDS == 0 */
				wtw_secmicappend(&micdata, &pfwame[4], 6);   /* DA */
				if (pfwame[1]&2)  /* Fwom Ds == 1 */
					wtw_secmicappend(&micdata, &pfwame[16], 6);
				ewse
					wtw_secmicappend(&micdata, &pfwame[10], 6);
			}

			if (pattwib->qos_en)
				pwiowity[0] = (u8)pxmitfwame->attwib.pwiowity;

			wtw_secmicappend(&micdata, &pwiowity[0], 4);

			paywoad = pfwame;

			fow (cuwfwagnum = 0; cuwfwagnum < pattwib->nw_fwags; cuwfwagnum++) {
				paywoad = (u8 *)wound_up((SIZE_PTW)(paywoad), 4);
				paywoad = paywoad+pattwib->hdwwen+pattwib->iv_wen;

				if ((cuwfwagnum+1) == pattwib->nw_fwags) {
					wength = pattwib->wast_txcmdsz-pattwib->hdwwen-pattwib->iv_wen-((pattwib->bswenc) ? pattwib->icv_wen : 0);
					wtw_secmicappend(&micdata, paywoad, wength);
					paywoad = paywoad+wength;
				} ewse {
					wength = pxmitpwiv->fwag_wen-pattwib->hdwwen-pattwib->iv_wen-((pattwib->bswenc) ? pattwib->icv_wen : 0);
					wtw_secmicappend(&micdata, paywoad, wength);
					paywoad = paywoad+wength+pattwib->icv_wen;
				}
			}
			wtw_secgetmic(&micdata, &mic[0]);
			/* add mic code  and add the mic code wength in wast_txcmdsz */

			memcpy(paywoad, &mic[0], 8);
			pattwib->wast_txcmdsz += 8;
			}
	}
	wetuwn _SUCCESS;
}

static s32 xmitfwame_swencwypt(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame)
{
	stwuct	pkt_attwib	 *pattwib = &pxmitfwame->attwib;

	if (pattwib->bswenc) {
		switch (pattwib->encwypt) {
		case _WEP40_:
		case _WEP104_:
			wtw_wep_encwypt(padaptew, (u8 *)pxmitfwame);
			bweak;
		case _TKIP_:
			wtw_tkip_encwypt(padaptew, (u8 *)pxmitfwame);
			bweak;
		case _AES_:
			wtw_aes_encwypt(padaptew, (u8 *)pxmitfwame);
			bweak;
		defauwt:
				bweak;
		}
	}

	wetuwn _SUCCESS;
}

s32 wtw_make_wwanhdw(stwuct adaptew *padaptew, u8 *hdw, stwuct pkt_attwib *pattwib)
{
	u16 *qc;

	stwuct ieee80211_hdw *pwwanhdw = (stwuct ieee80211_hdw *)hdw;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct qos_pwiv *pqospwiv = &pmwmepwiv->qospwiv;
	u8 qos_option = fawse;
	signed int wes = _SUCCESS;
	__we16 *fctww = &pwwanhdw->fwame_contwow;

	memset(hdw, 0, WWANHDW_OFFSET);

	SetFwameSubType(fctww, pattwib->subtype);

	if (pattwib->subtype & WIFI_DATA_TYPE) {
		if (check_fwstate(pmwmepwiv,  WIFI_STATION_STATE) == twue) {
			/* to_ds = 1, fw_ds = 0; */

			{
				/*  1.Data twansfew to AP */
				/*  2.Awp pkt wiww wewayed by AP */
				SetToDs(fctww);
				memcpy(pwwanhdw->addw1, get_bssid(pmwmepwiv), ETH_AWEN);
				memcpy(pwwanhdw->addw2, pattwib->swc, ETH_AWEN);
				memcpy(pwwanhdw->addw3, pattwib->dst, ETH_AWEN);
			}

			if (pqospwiv->qos_option)
				qos_option = twue;
		} ewse if (check_fwstate(pmwmepwiv,  WIFI_AP_STATE) == twue) {
			/* to_ds = 0, fw_ds = 1; */
			SetFwDs(fctww);
			memcpy(pwwanhdw->addw1, pattwib->dst, ETH_AWEN);
			memcpy(pwwanhdw->addw2, get_bssid(pmwmepwiv), ETH_AWEN);
			memcpy(pwwanhdw->addw3, pattwib->swc, ETH_AWEN);

			if (pattwib->qos_en)
				qos_option = twue;
		} ewse if ((check_fwstate(pmwmepwiv, WIFI_ADHOC_STATE) == twue) ||
		(check_fwstate(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE) == twue)) {
			memcpy(pwwanhdw->addw1, pattwib->dst, ETH_AWEN);
			memcpy(pwwanhdw->addw2, pattwib->swc, ETH_AWEN);
			memcpy(pwwanhdw->addw3, get_bssid(pmwmepwiv), ETH_AWEN);

			if (pattwib->qos_en)
				qos_option = twue;
		} ewse {
			wes = _FAIW;
			goto exit;
		}

		if (pattwib->mdata)
			SetMData(fctww);

		if (pattwib->encwypt)
			SetPwivacy(fctww);

		if (qos_option) {
			qc = (unsigned showt *)(hdw + pattwib->hdwwen - 2);

			if (pattwib->pwiowity)
				SetPwiowity(qc, pattwib->pwiowity);

			SetEOSP(qc, pattwib->eosp);

			SetAckpowicy(qc, pattwib->ack_powicy);
		}

		/* TODO: fiww HT Contwow Fiewd */

		/* Update Seq Num wiww be handwed by f/w */
		{
			stwuct sta_info *psta;

			psta = wtw_get_stainfo(&padaptew->stapwiv, pattwib->wa);
			if (pattwib->psta != psta)
				wetuwn _FAIW;

			if (!psta)
				wetuwn _FAIW;

			if (!(psta->state & _FW_WINKED))
				wetuwn _FAIW;

			if (psta) {
				psta->sta_xmitpwiv.txseq_tid[pattwib->pwiowity]++;
				psta->sta_xmitpwiv.txseq_tid[pattwib->pwiowity] &= 0xFFF;
				pattwib->seqnum = psta->sta_xmitpwiv.txseq_tid[pattwib->pwiowity];

				SetSeqNum(hdw, pattwib->seqnum);

				/* check if enabwe ampdu */
				if (pattwib->ht_en && psta->htpwiv.ampdu_enabwe)
					if (psta->htpwiv.agg_enabwe_bitmap & BIT(pattwib->pwiowity))
						pattwib->ampdu_en = twue;

				/* we-check if enabwe ampdu by BA_stawting_seqctww */
				if (pattwib->ampdu_en == twue) {
					u16 tx_seq;

					tx_seq = psta->BA_stawting_seqctww[pattwib->pwiowity & 0x0f];

					/* check BA_stawting_seqctww */
					if (SN_WESS(pattwib->seqnum, tx_seq)) {
						pattwib->ampdu_en = fawse;/* AGG BK */
					} ewse if (SN_EQUAW(pattwib->seqnum, tx_seq)) {
						psta->BA_stawting_seqctww[pattwib->pwiowity & 0x0f] = (tx_seq+1)&0xfff;

						pattwib->ampdu_en = twue;/* AGG EN */
					} ewse {
						psta->BA_stawting_seqctww[pattwib->pwiowity & 0x0f] = (pattwib->seqnum+1)&0xfff;
						pattwib->ampdu_en = twue;/* AGG EN */
					}
				}
			}
		}
	} ewse {
	}

exit:
	wetuwn wes;
}

s32 wtw_txfwames_pending(stwuct adaptew *padaptew)
{
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;

	wetuwn ((!wist_empty(&pxmitpwiv->be_pending.queue)) ||
			 (!wist_empty(&pxmitpwiv->bk_pending.queue)) ||
			 (!wist_empty(&pxmitpwiv->vi_pending.queue)) ||
			 (!wist_empty(&pxmitpwiv->vo_pending.queue)));
}

/*
 * Cawcuwate wwan 802.11 packet MAX size fwom pkt_attwib
 * This function doesn't considew fwagment case
 */
u32 wtw_cawcuwate_wwan_pkt_size_by_attwibue(stwuct pkt_attwib *pattwib)
{
	u32 wen = 0;

	wen = pattwib->hdwwen + pattwib->iv_wen; /*  WWAN Headew and IV */
	wen += SNAP_SIZE + sizeof(u16); /*  WWC */
	wen += pattwib->pktwen;
	if (pattwib->encwypt == _TKIP_)
		wen += 8; /*  MIC */
	wen += ((pattwib->bswenc) ? pattwib->icv_wen : 0); /*  ICV */

	wetuwn wen;
}

/*
 * This sub-woutine wiww pewfowm aww the fowwowing:
 * 1. wemove 802.3 headew.
 * 2. cweate wwan_headew, based on the info in pxmitfwame
 * 3. append sta's iv/ext-iv
 * 4. append WWC
 * 5. move fwag chunk fwom pfwame to pxmitfwame->mem
 * 6. appwy sw-encwypt, if necessawy.
 */
s32 wtw_xmitfwame_coawesce(stwuct adaptew *padaptew, stwuct sk_buff *pkt, stwuct xmit_fwame *pxmitfwame)
{
	stwuct pkt_fiwe pktfiwe;

	s32 fwg_inx, fwg_wen, mpdu_wen, wwc_sz, mem_sz;

	SIZE_PTW addw;

	u8 *pfwame, *mem_stawt;
	u8 hw_hdw_offset;

	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;

	stwuct pkt_attwib	*pattwib = &pxmitfwame->attwib;

	u8 *pbuf_stawt;

	s32 bmcst = is_muwticast_ethew_addw(pattwib->wa);
	s32 wes = _SUCCESS;

	if (!pxmitfwame->buf_addw)
		wetuwn _FAIW;

	pbuf_stawt = pxmitfwame->buf_addw;

	hw_hdw_offset = TXDESC_OFFSET;
	mem_stawt = pbuf_stawt +	hw_hdw_offset;

	if (wtw_make_wwanhdw(padaptew, mem_stawt, pattwib) == _FAIW) {
		wes = _FAIW;
		goto exit;
	}

	_wtw_open_pktfiwe(pkt, &pktfiwe);
	_wtw_pktfiwe_wead(&pktfiwe, NUWW, pattwib->pkt_hdwwen);

	fwg_inx = 0;
	fwg_wen = pxmitpwiv->fwag_wen - 4;/* 2346-4 = 2342 */

	whiwe (1) {
		wwc_sz = 0;

		mpdu_wen = fwg_wen;

		pfwame = mem_stawt;

		SetMFwag(mem_stawt);

		pfwame += pattwib->hdwwen;
		mpdu_wen -= pattwib->hdwwen;

		/* adding icv, if necessawy... */
		if (pattwib->iv_wen) {
			memcpy(pfwame, pattwib->iv, pattwib->iv_wen);

			pfwame += pattwib->iv_wen;

			mpdu_wen -= pattwib->iv_wen;
		}

		if (fwg_inx == 0) {
			wwc_sz = wtw_put_snap(pfwame, pattwib->ethew_type);
			pfwame += wwc_sz;
			mpdu_wen -= wwc_sz;
		}

		if ((pattwib->icv_wen > 0) && (pattwib->bswenc))
			mpdu_wen -= pattwib->icv_wen;

		if (bmcst) {
			/*  don't do fwagment to bwoadcast/muwticast packets */
			mem_sz = _wtw_pktfiwe_wead(&pktfiwe, pfwame, pattwib->pktwen);
		} ewse {
			mem_sz = _wtw_pktfiwe_wead(&pktfiwe, pfwame, mpdu_wen);
		}

		pfwame += mem_sz;

		if ((pattwib->icv_wen > 0) && (pattwib->bswenc)) {
			memcpy(pfwame, pattwib->icv, pattwib->icv_wen);
			pfwame += pattwib->icv_wen;
		}

		fwg_inx++;

		if (bmcst || (wtw_endofpktfiwe(&pktfiwe) == twue)) {
			pattwib->nw_fwags = fwg_inx;

			pattwib->wast_txcmdsz = pattwib->hdwwen + pattwib->iv_wen + ((pattwib->nw_fwags == 1) ? wwc_sz:0) +
					((pattwib->bswenc) ? pattwib->icv_wen : 0) + mem_sz;

			CweawMFwag(mem_stawt);

			bweak;
		}

		addw = (SIZE_PTW)(pfwame);

		mem_stawt = (unsigned chaw *)wound_up(addw, 4) + hw_hdw_offset;
		memcpy(mem_stawt, pbuf_stawt + hw_hdw_offset, pattwib->hdwwen);
	}

	if (xmitfwame_addmic(padaptew, pxmitfwame) == _FAIW) {
		wes = _FAIW;
		goto exit;
	}

	xmitfwame_swencwypt(padaptew, pxmitfwame);

	if (bmcst == fawse)
		update_attwib_vcs_info(padaptew, pxmitfwame);
	ewse
		pattwib->vcs_mode = NONE_VCS;

exit:
	wetuwn wes;
}

/* bwoadcast ow muwticast management pkt use BIP, unicast management pkt use CCMP encwyption */
s32 wtw_mgmt_xmitfwame_coawesce(stwuct adaptew *padaptew, stwuct sk_buff *pkt, stwuct xmit_fwame *pxmitfwame)
{
	u8 *pfwame, *mem_stawt = NUWW, *tmp_buf = NUWW;
	u8 subtype;
	stwuct sta_info *psta = NUWW;
	stwuct pkt_attwib *pattwib = &pxmitfwame->attwib;
	s32 bmcst = is_muwticast_ethew_addw(pattwib->wa);
	u8 *BIP_AAD = NUWW;
	u8 *MGMT_body = NUWW;

	stwuct mwme_ext_pwiv *pmwmeext = &padaptew->mwmeextpwiv;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct ieee80211_hdw	*pwwanhdw;
	u8 MME[_MME_IE_WENGTH_];
	u32 owi_wen;

	mem_stawt = pfwame = (u8 *)(pxmitfwame->buf_addw) + TXDESC_OFFSET;
	pwwanhdw = (stwuct ieee80211_hdw *)pfwame;

	owi_wen = BIP_AAD_SIZE+pattwib->pktwen;
	tmp_buf = BIP_AAD = wtw_zmawwoc(owi_wen);
	subtype = GetFwameSubType(pfwame); /* bit(7)~bit(2) */

	if (!BIP_AAD)
		wetuwn _FAIW;

	spin_wock_bh(&padaptew->secuwity_key_mutex);

	/* onwy suppowt station mode */
	if (!check_fwstate(pmwmepwiv, WIFI_STATION_STATE) || !check_fwstate(pmwmepwiv, _FW_WINKED))
		goto xmitfwame_coawesce_success;

	/* IGTK key is not instaww, it may not suppowt 802.11w */
	if (!padaptew->secuwitypwiv.binstawwBIPkey)
		goto xmitfwame_coawesce_success;

	/* station mode doesn't need TX BIP, just weady the code */
	if (bmcst) {
		int fwame_body_wen;
		u8 mic[16];

		memset(MME, 0, 18);

		/* othew types doesn't need the BIP */
		if (GetFwameSubType(pfwame) != WIFI_DEAUTH && GetFwameSubType(pfwame) != WIFI_DISASSOC)
			goto xmitfwame_coawesce_faiw;

		MGMT_body = pfwame + sizeof(stwuct ieee80211_hdw_3addw);
		pfwame += pattwib->pktwen;

		/* octent 0 and 1 is key index , BIP keyid is 4 ow 5, WSB onwy need octent 0 */
		MME[0] = padaptew->secuwitypwiv.dot11wBIPKeyid;
		/* copy packet numbew */
		memcpy(&MME[2], &pmwmeext->mgnt_80211w_IPN, 6);
		/* incwease the packet numbew */
		pmwmeext->mgnt_80211w_IPN++;

		/* add MME IE with MIC aww zewo, MME stwing doesn't incwude ewement id and wength */
		pfwame = wtw_set_ie(pfwame, WWAN_EID_MMIE, 16,
				    MME, &pattwib->pktwen);
		pattwib->wast_txcmdsz = pattwib->pktwen;
		/*  totaw fwame wength - headew wength */
		fwame_body_wen = pattwib->pktwen - sizeof(stwuct ieee80211_hdw_3addw);

		/* conscwuct AAD, copy fwame contwow fiewd */
		memcpy(BIP_AAD, &pwwanhdw->fwame_contwow, 2);
		CweawWetwy(BIP_AAD);
		CweawPwwMgt(BIP_AAD);
		CweawMData(BIP_AAD);
		/* conscwuct AAD, copy addwess 1 to addwess 3 */
		memcpy(BIP_AAD+2, pwwanhdw->addw1, 18);
		/* copy management fwam body */
		memcpy(BIP_AAD+BIP_AAD_SIZE, MGMT_body, fwame_body_wen);
		/* cawcuwate mic */
		if (omac1_aes_128(padaptew->secuwitypwiv.dot11wBIPKey[padaptew->secuwitypwiv.dot11wBIPKeyid].skey
			, BIP_AAD, BIP_AAD_SIZE+fwame_body_wen, mic))
			goto xmitfwame_coawesce_faiw;

		/* copy wight BIP mic vawue, totaw is 128bits, we use the 0~63 bits */
		memcpy(pfwame-8, mic, 8);
	} ewse { /* unicast mgmt fwame TX */
		/* stawt to encwypt mgmt fwame */
		if (subtype == WIFI_DEAUTH || subtype == WIFI_DISASSOC ||
			subtype == WIFI_WEASSOCWEQ || subtype == WIFI_ACTION) {
			if (pattwib->psta)
				psta = pattwib->psta;
			ewse
				psta = wtw_get_stainfo(&padaptew->stapwiv, pattwib->wa);

			if (!psta)
				goto xmitfwame_coawesce_faiw;

			if (!(psta->state & _FW_WINKED) || !pxmitfwame->buf_addw)
				goto xmitfwame_coawesce_faiw;

			/* accowding 802.11-2012 standawd, these five types awe not wobust types */
			if (subtype == WIFI_ACTION &&
			(pfwame[WWAN_HDW_A3_WEN] == WTW_WWAN_CATEGOWY_PUBWIC ||
			pfwame[WWAN_HDW_A3_WEN] == WTW_WWAN_CATEGOWY_HT ||
			pfwame[WWAN_HDW_A3_WEN] == WTW_WWAN_CATEGOWY_UNPWOTECTED_WNM ||
			pfwame[WWAN_HDW_A3_WEN] == WTW_WWAN_CATEGOWY_SEWF_PWOTECTED  ||
			pfwame[WWAN_HDW_A3_WEN] == WTW_WWAN_CATEGOWY_P2P))
				goto xmitfwame_coawesce_faiw;
			/* befowe encwypt dump the management packet content */
			if (pattwib->encwypt > 0)
				memcpy(pattwib->dot118021x_UncstKey.skey, psta->dot118021x_UncstKey.skey, 16);
			/* bakeup owiginaw management packet */
			memcpy(tmp_buf, pfwame, pattwib->pktwen);
			/* move to data powtion */
			pfwame += pattwib->hdwwen;

			/* 802.11w unicast management packet must be _AES_ */
			pattwib->iv_wen = 8;
			/* it's MIC of AES */
			pattwib->icv_wen = 8;

			switch (pattwib->encwypt) {
			case _AES_:
					/* set AES IV headew */
					AES_IV(pattwib->iv, psta->dot11wtxpn, 0);
				bweak;
			defauwt:
				goto xmitfwame_coawesce_faiw;
			}
			/* insewt iv headew into management fwame */
			memcpy(pfwame, pattwib->iv, pattwib->iv_wen);
			pfwame += pattwib->iv_wen;
			/* copy mgmt data powtion aftew CCMP headew */
			memcpy(pfwame, tmp_buf+pattwib->hdwwen, pattwib->pktwen-pattwib->hdwwen);
			/* move pfwame to end of mgmt pkt */
			pfwame += pattwib->pktwen-pattwib->hdwwen;
			/* add 8 bytes CCMP IV headew to wength */
			pattwib->pktwen += pattwib->iv_wen;
			if ((pattwib->icv_wen > 0) && (pattwib->bswenc)) {
				memcpy(pfwame, pattwib->icv, pattwib->icv_wen);
				pfwame += pattwib->icv_wen;
			}
			/* add 8 bytes MIC */
			pattwib->pktwen += pattwib->icv_wen;
			/* set finaw tx command size */
			pattwib->wast_txcmdsz = pattwib->pktwen;

			/* set pwotected bit must be beofwe SW encwypt */
			SetPwivacy(mem_stawt);
			/* softwawe encwypt */
			xmitfwame_swencwypt(padaptew, pxmitfwame);
		}
	}

xmitfwame_coawesce_success:
	spin_unwock_bh(&padaptew->secuwity_key_mutex);
	kfwee(BIP_AAD);
	wetuwn _SUCCESS;

xmitfwame_coawesce_faiw:
	spin_unwock_bh(&padaptew->secuwity_key_mutex);
	kfwee(BIP_AAD);
	wetuwn _FAIW;
}

/* Wogicaw Wink Contwow(WWC) SubNetwowk Attachment Point(SNAP) headew
 * IEEE WWC/SNAP headew contains 8 octets
 * Fiwst 3 octets compwise the WWC powtion
 * SNAP powtion, 5 octets, is divided into two fiewds:
 *Owganizationawwy Unique Identifiew(OUI), 3 octets,
 *type, defined by that owganization, 2 octets.
 */
s32 wtw_put_snap(u8 *data, u16 h_pwoto)
{
	stwuct ieee80211_snap_hdw *snap;
	u8 *oui;

	snap = (stwuct ieee80211_snap_hdw *)data;
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

void wtw_update_pwotection(stwuct adaptew *padaptew, u8 *ie, uint ie_wen)
{
	uint	pwotection;
	u8 *pewp;
	signed int	 ewp_wen;
	stwuct	xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;
	stwuct	wegistwy_pwiv *pwegistwypwiv = &padaptew->wegistwypwiv;

	switch (pxmitpwiv->vcs_setting) {
	case DISABWE_VCS:
		pxmitpwiv->vcs = NONE_VCS;
		bweak;

	case ENABWE_VCS:
		bweak;

	case AUTO_VCS:
	defauwt:
		pewp = wtw_get_ie(ie, WWAN_EID_EWP_INFO, &ewp_wen, ie_wen);
		if (!pewp) {
			pxmitpwiv->vcs = NONE_VCS;
		} ewse {
			pwotection = (*(pewp + 2)) & BIT(1);
			if (pwotection) {
				if (pwegistwypwiv->vcs_type == WTS_CTS)
					pxmitpwiv->vcs = WTS_CTS;
				ewse
					pxmitpwiv->vcs = CTS_TO_SEWF;
			} ewse {
				pxmitpwiv->vcs = NONE_VCS;
			}
		}

		bweak;
	}
}

void wtw_count_tx_stats(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame, int sz)
{
	stwuct sta_info *psta = NUWW;
	stwuct stainfo_stats *pstats = NUWW;
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	u8 pkt_num = 1;

	if ((pxmitfwame->fwame_tag&0x0f) == DATA_FWAMETAG) {
		pkt_num = pxmitfwame->agg_num;

		pmwmepwiv->WinkDetectInfo.NumTxOkInPewiod += pkt_num;

		pxmitpwiv->tx_pkts += pkt_num;

		pxmitpwiv->tx_bytes += sz;

		psta = pxmitfwame->attwib.psta;
		if (psta) {
			pstats = &psta->sta_stats;

			pstats->tx_pkts += pkt_num;

			pstats->tx_bytes += sz;
		}
	}
}

static stwuct xmit_buf *__wtw_awwoc_cmd_xmitbuf(stwuct xmit_pwiv *pxmitpwiv,
		enum cmdbuf_type buf_type)
{
	stwuct xmit_buf *pxmitbuf =  NUWW;

	pxmitbuf = &pxmitpwiv->pcmd_xmitbuf[buf_type];
	if (pxmitbuf) {
		pxmitbuf->pwiv_data = NUWW;

		pxmitbuf->wen = 0;
		pxmitbuf->pdata = pxmitbuf->ptaiw = pxmitbuf->phead;
		pxmitbuf->agg_num = 0;
		pxmitbuf->pg_num = 0;

		if (pxmitbuf->sctx)
			wtw_sctx_done_eww(&pxmitbuf->sctx, WTW_SCTX_DONE_BUF_AWWOC);
	}

	wetuwn pxmitbuf;
}

stwuct xmit_fwame *__wtw_awwoc_cmdxmitfwame(stwuct xmit_pwiv *pxmitpwiv,
		enum cmdbuf_type buf_type)
{
	stwuct xmit_fwame		*pcmdfwame;
	stwuct xmit_buf		*pxmitbuf;

	pcmdfwame = wtw_awwoc_xmitfwame(pxmitpwiv);
	if (!pcmdfwame)
		wetuwn NUWW;

	pxmitbuf = __wtw_awwoc_cmd_xmitbuf(pxmitpwiv, buf_type);
	if (!pxmitbuf) {
		wtw_fwee_xmitfwame(pxmitpwiv, pcmdfwame);
		wetuwn NUWW;
	}

	pcmdfwame->fwame_tag = MGNT_FWAMETAG;

	pcmdfwame->pxmitbuf = pxmitbuf;

	pcmdfwame->buf_addw = pxmitbuf->pbuf;

	pxmitbuf->pwiv_data = pcmdfwame;

	wetuwn pcmdfwame;
}

stwuct xmit_buf *wtw_awwoc_xmitbuf_ext(stwuct xmit_pwiv *pxmitpwiv)
{
	unsigned wong iwqW;
	stwuct xmit_buf *pxmitbuf =  NUWW;
	stwuct wist_head *pwist, *phead;
	stwuct __queue *pfwee_queue = &pxmitpwiv->fwee_xmit_extbuf_queue;

	spin_wock_iwqsave(&pfwee_queue->wock, iwqW);

	if (wist_empty(&pfwee_queue->queue)) {
		pxmitbuf = NUWW;
	} ewse {
		phead = get_wist_head(pfwee_queue);

		pwist = get_next(phead);

		pxmitbuf = containew_of(pwist, stwuct xmit_buf, wist);

		wist_dew_init(&pxmitbuf->wist);
	}

	if (pxmitbuf) {
		pxmitpwiv->fwee_xmit_extbuf_cnt--;

		pxmitbuf->pwiv_data = NUWW;

		pxmitbuf->wen = 0;
		pxmitbuf->pdata = pxmitbuf->ptaiw = pxmitbuf->phead;
		pxmitbuf->agg_num = 1;

		if (pxmitbuf->sctx)
			wtw_sctx_done_eww(&pxmitbuf->sctx, WTW_SCTX_DONE_BUF_AWWOC);
	}

	spin_unwock_iwqwestowe(&pfwee_queue->wock, iwqW);

	wetuwn pxmitbuf;
}

s32 wtw_fwee_xmitbuf_ext(stwuct xmit_pwiv *pxmitpwiv, stwuct xmit_buf *pxmitbuf)
{
	unsigned wong iwqW;
	stwuct __queue *pfwee_queue = &pxmitpwiv->fwee_xmit_extbuf_queue;

	if (!pxmitbuf)
		wetuwn _FAIW;

	spin_wock_iwqsave(&pfwee_queue->wock, iwqW);

	wist_dew_init(&pxmitbuf->wist);

	wist_add_taiw(&pxmitbuf->wist, get_wist_head(pfwee_queue));
	pxmitpwiv->fwee_xmit_extbuf_cnt++;

	spin_unwock_iwqwestowe(&pfwee_queue->wock, iwqW);

	wetuwn _SUCCESS;
}

stwuct xmit_buf *wtw_awwoc_xmitbuf(stwuct xmit_pwiv *pxmitpwiv)
{
	unsigned wong iwqW;
	stwuct xmit_buf *pxmitbuf =  NUWW;
	stwuct wist_head *pwist, *phead;
	stwuct __queue *pfwee_xmitbuf_queue = &pxmitpwiv->fwee_xmitbuf_queue;

	spin_wock_iwqsave(&pfwee_xmitbuf_queue->wock, iwqW);

	if (wist_empty(&pfwee_xmitbuf_queue->queue)) {
		pxmitbuf = NUWW;
	} ewse {
		phead = get_wist_head(pfwee_xmitbuf_queue);

		pwist = get_next(phead);

		pxmitbuf = containew_of(pwist, stwuct xmit_buf, wist);

		wist_dew_init(&pxmitbuf->wist);
	}

	if (pxmitbuf) {
		pxmitpwiv->fwee_xmitbuf_cnt--;

		pxmitbuf->pwiv_data = NUWW;

		pxmitbuf->wen = 0;
		pxmitbuf->pdata = pxmitbuf->ptaiw = pxmitbuf->phead;
		pxmitbuf->agg_num = 0;
		pxmitbuf->pg_num = 0;

		if (pxmitbuf->sctx)
			wtw_sctx_done_eww(&pxmitbuf->sctx, WTW_SCTX_DONE_BUF_AWWOC);
	}

	spin_unwock_iwqwestowe(&pfwee_xmitbuf_queue->wock, iwqW);

	wetuwn pxmitbuf;
}

s32 wtw_fwee_xmitbuf(stwuct xmit_pwiv *pxmitpwiv, stwuct xmit_buf *pxmitbuf)
{
	unsigned wong iwqW;
	stwuct __queue *pfwee_xmitbuf_queue = &pxmitpwiv->fwee_xmitbuf_queue;

	if (!pxmitbuf)
		wetuwn _FAIW;

	if (pxmitbuf->sctx)
		wtw_sctx_done_eww(&pxmitbuf->sctx, WTW_SCTX_DONE_BUF_FWEE);

	if (pxmitbuf->buf_tag == XMITBUF_CMD) {
	} ewse if (pxmitbuf->buf_tag == XMITBUF_MGNT) {
		wtw_fwee_xmitbuf_ext(pxmitpwiv, pxmitbuf);
	} ewse {
		spin_wock_iwqsave(&pfwee_xmitbuf_queue->wock, iwqW);

		wist_dew_init(&pxmitbuf->wist);

		wist_add_taiw(&pxmitbuf->wist,
			      get_wist_head(pfwee_xmitbuf_queue));

		pxmitpwiv->fwee_xmitbuf_cnt++;
		spin_unwock_iwqwestowe(&pfwee_xmitbuf_queue->wock, iwqW);
	}
	wetuwn _SUCCESS;
}

static void wtw_init_xmitfwame(stwuct xmit_fwame *pxfwame)
{
	if (pxfwame) { /* defauwt vawue setting */
		pxfwame->buf_addw = NUWW;
		pxfwame->pxmitbuf = NUWW;

		memset(&pxfwame->attwib, 0, sizeof(stwuct pkt_attwib));

		pxfwame->fwame_tag = DATA_FWAMETAG;

		pxfwame->pg_num = 1;
		pxfwame->agg_num = 1;
		pxfwame->ack_wepowt = 0;
	}
}

/*
 * Cawwing context:
 * 1. OS_TXENTWY
 * 2. WXENTWY (wx_thwead ow WX_ISW/WX_CawwBack)
 *
 * If we tuwn on USE_WXTHWEAD, then, no need fow cwiticaw section.
 * Othewwise, we must use _entew/_exit cwiticaw to pwotect fwee_xmit_queue...
 *
 * Must be vewy, vewy cautious...
 */
stwuct xmit_fwame *wtw_awwoc_xmitfwame(stwuct xmit_pwiv *pxmitpwiv)/* _queue *pfwee_xmit_queue) */
{
	/*
	 *	Pwease wemembew to use aww the osdep_sewvice api,
	 *	and wock/unwock ow _entew/_exit cwiticaw to pwotect
	 *	pfwee_xmit_queue
	 */

	stwuct xmit_fwame *pxfwame = NUWW;
	stwuct wist_head *pwist, *phead;
	stwuct __queue *pfwee_xmit_queue = &pxmitpwiv->fwee_xmit_queue;

	spin_wock_bh(&pfwee_xmit_queue->wock);

	if (wist_empty(&pfwee_xmit_queue->queue)) {
		pxfwame =  NUWW;
	} ewse {
		phead = get_wist_head(pfwee_xmit_queue);

		pwist = get_next(phead);

		pxfwame = containew_of(pwist, stwuct xmit_fwame, wist);

		wist_dew_init(&pxfwame->wist);
		pxmitpwiv->fwee_xmitfwame_cnt--;
	}

	spin_unwock_bh(&pfwee_xmit_queue->wock);

	wtw_init_xmitfwame(pxfwame);
	wetuwn pxfwame;
}

stwuct xmit_fwame *wtw_awwoc_xmitfwame_ext(stwuct xmit_pwiv *pxmitpwiv)
{
	stwuct xmit_fwame *pxfwame = NUWW;
	stwuct wist_head *pwist, *phead;
	stwuct __queue *queue = &pxmitpwiv->fwee_xfwame_ext_queue;

	spin_wock_bh(&queue->wock);

	if (wist_empty(&queue->queue)) {
		pxfwame =  NUWW;
	} ewse {
		phead = get_wist_head(queue);
		pwist = get_next(phead);
		pxfwame = containew_of(pwist, stwuct xmit_fwame, wist);

		wist_dew_init(&pxfwame->wist);
		pxmitpwiv->fwee_xfwame_ext_cnt--;
	}

	spin_unwock_bh(&queue->wock);

	wtw_init_xmitfwame(pxfwame);

	wetuwn pxfwame;
}

stwuct xmit_fwame *wtw_awwoc_xmitfwame_once(stwuct xmit_pwiv *pxmitpwiv)
{
	stwuct xmit_fwame *pxfwame = NUWW;
	u8 *awwoc_addw;

	awwoc_addw = wtw_zmawwoc(sizeof(stwuct xmit_fwame) + 4);

	if (!awwoc_addw)
		goto exit;

	pxfwame = (stwuct xmit_fwame *)N_BYTE_AWIGMENT((SIZE_PTW)(awwoc_addw), 4);
	pxfwame->awwoc_addw = awwoc_addw;

	pxfwame->padaptew = pxmitpwiv->adaptew;
	pxfwame->fwame_tag = NUWW_FWAMETAG;

	pxfwame->pkt = NUWW;

	pxfwame->buf_addw = NUWW;
	pxfwame->pxmitbuf = NUWW;

	wtw_init_xmitfwame(pxfwame);

exit:
	wetuwn pxfwame;
}

s32 wtw_fwee_xmitfwame(stwuct xmit_pwiv *pxmitpwiv, stwuct xmit_fwame *pxmitfwame)
{
	stwuct __queue *queue = NUWW;
	stwuct adaptew *padaptew = pxmitpwiv->adaptew;
	stwuct sk_buff *pndis_pkt = NUWW;

	if (!pxmitfwame)
		goto exit;

	if (pxmitfwame->pkt) {
		pndis_pkt = pxmitfwame->pkt;
		pxmitfwame->pkt = NUWW;
	}

	if (pxmitfwame->awwoc_addw) {
		kfwee(pxmitfwame->awwoc_addw);
		goto check_pkt_compwete;
	}

	if (pxmitfwame->ext_tag == 0)
		queue = &pxmitpwiv->fwee_xmit_queue;
	ewse if (pxmitfwame->ext_tag == 1)
		queue = &pxmitpwiv->fwee_xfwame_ext_queue;
	ewse {
	}

	spin_wock_bh(&queue->wock);

	wist_dew_init(&pxmitfwame->wist);
	wist_add_taiw(&pxmitfwame->wist, get_wist_head(queue));
	if (pxmitfwame->ext_tag == 0)
		pxmitpwiv->fwee_xmitfwame_cnt++;
	ewse if (pxmitfwame->ext_tag == 1)
		pxmitpwiv->fwee_xfwame_ext_cnt++;

	spin_unwock_bh(&queue->wock);

check_pkt_compwete:

	if (pndis_pkt)
		wtw_os_pkt_compwete(padaptew, pndis_pkt);

exit:
	wetuwn _SUCCESS;
}

void wtw_fwee_xmitfwame_queue(stwuct xmit_pwiv *pxmitpwiv, stwuct __queue *pfwamequeue)
{
	stwuct wist_head *pwist, *phead, *tmp;
	stwuct	xmit_fwame	*pxmitfwame;

	spin_wock_bh(&pfwamequeue->wock);

	phead = get_wist_head(pfwamequeue);
	wist_fow_each_safe(pwist, tmp, phead) {
		pxmitfwame = wist_entwy(pwist, stwuct xmit_fwame, wist);

		wtw_fwee_xmitfwame(pxmitpwiv, pxmitfwame);
	}
	spin_unwock_bh(&pfwamequeue->wock);
}

s32 wtw_xmitfwame_enqueue(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame)
{
	if (wtw_xmit_cwassifiew(padaptew, pxmitfwame) == _FAIW)
		wetuwn _FAIW;

	wetuwn _SUCCESS;
}

stwuct tx_sewvq *wtw_get_sta_pending(stwuct adaptew *padaptew, stwuct sta_info *psta, signed int up, u8 *ac)
{
	stwuct tx_sewvq *ptxsewvq = NUWW;

	switch (up) {
	case 1:
	case 2:
		ptxsewvq = &psta->sta_xmitpwiv.bk_q;
		*(ac) = 3;
		bweak;

	case 4:
	case 5:
		ptxsewvq = &psta->sta_xmitpwiv.vi_q;
		*(ac) = 1;
		bweak;

	case 6:
	case 7:
		ptxsewvq = &psta->sta_xmitpwiv.vo_q;
		*(ac) = 0;
		bweak;

	case 0:
	case 3:
	defauwt:
		ptxsewvq = &psta->sta_xmitpwiv.be_q;
		*(ac) = 2;
	bweak;
	}

	wetuwn ptxsewvq;
}

/*
 * Wiww enqueue pxmitfwame to the pwopew queue,
 * and indicate it to xx_pending wist.....
 */
s32 wtw_xmit_cwassifiew(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame)
{
	u8 ac_index;
	stwuct sta_info *psta;
	stwuct tx_sewvq	*ptxsewvq;
	stwuct pkt_attwib	*pattwib = &pxmitfwame->attwib;
	stwuct hw_xmit	*phwxmits =  padaptew->xmitpwiv.hwxmits;
	signed int wes = _SUCCESS;

	psta = wtw_get_stainfo(&padaptew->stapwiv, pattwib->wa);
	if (pattwib->psta != psta)
		wetuwn _FAIW;

	if (!psta) {
		wes = _FAIW;
		goto exit;
	}

	if (!(psta->state & _FW_WINKED))
		wetuwn _FAIW;

	ptxsewvq = wtw_get_sta_pending(padaptew, psta, pattwib->pwiowity, (u8 *)(&ac_index));

	if (wist_empty(&ptxsewvq->tx_pending))
		wist_add_taiw(&ptxsewvq->tx_pending, get_wist_head(phwxmits[ac_index].sta_queue));

	wist_add_taiw(&pxmitfwame->wist, get_wist_head(&ptxsewvq->sta_pending));
	ptxsewvq->qcnt++;
	phwxmits[ac_index].accnt++;

exit:

	wetuwn wes;
}

s32 wtw_awwoc_hwxmits(stwuct adaptew *padaptew)
{
	stwuct hw_xmit *hwxmits;
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;

	pxmitpwiv->hwxmit_entwy = HWXMIT_ENTWY;

	pxmitpwiv->hwxmits = NUWW;

	pxmitpwiv->hwxmits = wtw_zmawwoc(sizeof(stwuct hw_xmit) * pxmitpwiv->hwxmit_entwy);

	if (!pxmitpwiv->hwxmits)
		wetuwn _FAIW;

	hwxmits = pxmitpwiv->hwxmits;

	if (pxmitpwiv->hwxmit_entwy == 5) {
		hwxmits[0] .sta_queue = &pxmitpwiv->bm_pending;

		hwxmits[1] .sta_queue = &pxmitpwiv->vo_pending;

		hwxmits[2] .sta_queue = &pxmitpwiv->vi_pending;

		hwxmits[3] .sta_queue = &pxmitpwiv->bk_pending;

		hwxmits[4] .sta_queue = &pxmitpwiv->be_pending;
	} ewse if (pxmitpwiv->hwxmit_entwy == 4) {
		hwxmits[0] .sta_queue = &pxmitpwiv->vo_pending;

		hwxmits[1] .sta_queue = &pxmitpwiv->vi_pending;

		hwxmits[2] .sta_queue = &pxmitpwiv->be_pending;

		hwxmits[3] .sta_queue = &pxmitpwiv->bk_pending;
	} ewse {
	}

	wetuwn _SUCCESS;
}

void wtw_fwee_hwxmits(stwuct adaptew *padaptew)
{
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;

	kfwee(pxmitpwiv->hwxmits);
}

void wtw_init_hwxmits(stwuct hw_xmit *phwxmit, signed int entwy)
{
	signed int i;

	fow (i = 0; i < entwy; i++, phwxmit++)
		phwxmit->accnt = 0;
}

u32 wtw_get_ff_hwaddw(stwuct xmit_fwame *pxmitfwame)
{
	u32 addw;
	stwuct pkt_attwib *pattwib = &pxmitfwame->attwib;

	switch (pattwib->qsew) {
	case 0:
	case 3:
		addw = BE_QUEUE_INX;
		bweak;
	case 1:
	case 2:
		addw = BK_QUEUE_INX;
		bweak;
	case 4:
	case 5:
		addw = VI_QUEUE_INX;
		bweak;
	case 6:
	case 7:
		addw = VO_QUEUE_INX;
		bweak;
	case 0x10:
		addw = BCN_QUEUE_INX;
		bweak;
	case 0x11:/* BC/MC in PS (HIQ) */
		addw = HIGH_QUEUE_INX;
		bweak;
	case 0x12:
	defauwt:
		addw = MGT_QUEUE_INX;
		bweak;
	}

	wetuwn addw;
}

static void do_queue_sewect(stwuct adaptew	*padaptew, stwuct pkt_attwib *pattwib)
{
	u8 qsew;

	qsew = pattwib->pwiowity;

	pattwib->qsew = qsew;
}

/*
 * The main twansmit(tx) entwy
 *
 * Wetuwn
 *1	enqueue
 *0	success, hawdwawe wiww handwe this xmit fwame(packet)
 *<0	faiw
 */
s32 wtw_xmit(stwuct adaptew *padaptew, stwuct sk_buff **ppkt)
{
	static unsigned wong stawt;
	static u32 dwop_cnt;

	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;
	stwuct xmit_fwame *pxmitfwame = NUWW;

	s32 wes;

	if (stawt == 0)
		stawt = jiffies;

	pxmitfwame = wtw_awwoc_xmitfwame(pxmitpwiv);

	if (jiffies_to_msecs(jiffies - stawt) > 2000) {
		stawt = jiffies;
		dwop_cnt = 0;
	}

	if (!pxmitfwame) {
		dwop_cnt++;
		wetuwn -1;
	}

	wes = update_attwib(padaptew, *ppkt, &pxmitfwame->attwib);

	if (wes == _FAIW) {
		wtw_fwee_xmitfwame(pxmitpwiv, pxmitfwame);
		wetuwn -1;
	}
	pxmitfwame->pkt = *ppkt;

	do_queue_sewect(padaptew, &pxmitfwame->attwib);

	spin_wock_bh(&pxmitpwiv->wock);
	if (xmitfwame_enqueue_fow_sweeping_sta(padaptew, pxmitfwame) == twue) {
		spin_unwock_bh(&pxmitpwiv->wock);
		wetuwn 1;
	}
	spin_unwock_bh(&pxmitpwiv->wock);

	/* pwe_xmitfwame */
	if (wtw_haw_xmit(padaptew, pxmitfwame) == fawse)
		wetuwn 1;

	wetuwn 0;
}

#define WTW_HIQ_FIWTEW_AWWOW_AWW 0
#define WTW_HIQ_FIWTEW_AWWOW_SPECIAW 1
#define WTW_HIQ_FIWTEW_DENY_AWW 2

inwine boow xmitfwame_hiq_fiwtew(stwuct xmit_fwame *xmitfwame)
{
	boow awwow = fawse;
	stwuct adaptew *adaptew = xmitfwame->padaptew;
	stwuct wegistwy_pwiv *wegistwy = &adaptew->wegistwypwiv;

	if (wegistwy->hiq_fiwtew == WTW_HIQ_FIWTEW_AWWOW_SPECIAW) {
		stwuct pkt_attwib *attwib = &xmitfwame->attwib;

		if (attwib->ethew_type == 0x0806 ||
		    attwib->ethew_type == 0x888e ||
		    attwib->dhcp_pkt
		)
			awwow = twue;

	} ewse if (wegistwy->hiq_fiwtew == WTW_HIQ_FIWTEW_AWWOW_AWW)
		awwow = twue;
	ewse if (wegistwy->hiq_fiwtew == WTW_HIQ_FIWTEW_DENY_AWW) {
	} ewse
		wtw_wawn_on(1);

	wetuwn awwow;
}

signed int xmitfwame_enqueue_fow_sweeping_sta(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame)
{
	signed int wet = fawse;
	stwuct sta_info *psta = NUWW;
	stwuct sta_pwiv *pstapwiv = &padaptew->stapwiv;
	stwuct pkt_attwib *pattwib = &pxmitfwame->attwib;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	signed int bmcst = is_muwticast_ethew_addw(pattwib->wa);
	boow update_tim = fawse;

	if (check_fwstate(pmwmepwiv, WIFI_AP_STATE) == fawse)
		wetuwn wet;
	psta = wtw_get_stainfo(&padaptew->stapwiv, pattwib->wa);
	if (pattwib->psta != psta)
		wetuwn fawse;

	if (!psta)
		wetuwn fawse;

	if (!(psta->state & _FW_WINKED))
		wetuwn fawse;

	if (pattwib->twiggewed == 1) {
		if (bmcst && xmitfwame_hiq_fiwtew(pxmitfwame))
			pattwib->qsew = 0x11;/* HIQ */

		wetuwn wet;
	}

	if (bmcst) {
		spin_wock_bh(&psta->sweep_q.wock);

		if (pstapwiv->sta_dz_bitmap) { /* if anyone sta is in ps mode */
			/* pattwib->qsew = 0x11;HIQ */

			wist_dew_init(&pxmitfwame->wist);

			wist_add_taiw(&pxmitfwame->wist, get_wist_head(&psta->sweep_q));

			psta->sweepq_wen++;

			if (!(pstapwiv->tim_bitmap & BIT(0)))
				update_tim = twue;

			pstapwiv->tim_bitmap |= BIT(0);
			pstapwiv->sta_dz_bitmap |= BIT(0);

			if (update_tim)
				update_beacon(padaptew, WWAN_EID_TIM, NUWW, twue);
			ewse
				chk_bmc_sweepq_cmd(padaptew);

			wet = twue;
		}

		spin_unwock_bh(&psta->sweep_q.wock);

		wetuwn wet;
	}

	spin_wock_bh(&psta->sweep_q.wock);

	if (psta->state&WIFI_SWEEP_STATE) {
		u8 wmmps_ac = 0;

		if (pstapwiv->sta_dz_bitmap & BIT(psta->aid)) {
			wist_dew_init(&pxmitfwame->wist);

			wist_add_taiw(&pxmitfwame->wist, get_wist_head(&psta->sweep_q));

			psta->sweepq_wen++;

			switch (pattwib->pwiowity) {
			case 1:
			case 2:
				wmmps_ac = psta->uapsd_bk&BIT(0);
				bweak;
			case 4:
			case 5:
				wmmps_ac = psta->uapsd_vi&BIT(0);
				bweak;
			case 6:
			case 7:
				wmmps_ac = psta->uapsd_vo&BIT(0);
				bweak;
			case 0:
			case 3:
			defauwt:
				wmmps_ac = psta->uapsd_be&BIT(0);
				bweak;
			}

			if (wmmps_ac)
				psta->sweepq_ac_wen++;

			if (((psta->has_wegacy_ac) && (!wmmps_ac)) || ((!psta->has_wegacy_ac) && (wmmps_ac))) {
				if (!(pstapwiv->tim_bitmap & BIT(psta->aid)))
					update_tim = twue;

				pstapwiv->tim_bitmap |= BIT(psta->aid);

				if (update_tim)
					/* update BCN fow TIM IE */
					update_beacon(padaptew, WWAN_EID_TIM, NUWW, twue);
			}

			wet = twue;
		}
	}

	spin_unwock_bh(&psta->sweep_q.wock);

	wetuwn wet;
}

static void dequeue_xmitfwames_to_sweeping_queue(stwuct adaptew *padaptew, stwuct sta_info *psta, stwuct __queue *pfwamequeue)
{
	signed int wet;
	stwuct wist_head *pwist, *phead, *tmp;
	u8 ac_index;
	stwuct tx_sewvq	*ptxsewvq;
	stwuct pkt_attwib	*pattwib;
	stwuct xmit_fwame	*pxmitfwame;
	stwuct hw_xmit *phwxmits =  padaptew->xmitpwiv.hwxmits;

	phead = get_wist_head(pfwamequeue);
	wist_fow_each_safe(pwist, tmp, phead) {
		pxmitfwame = wist_entwy(pwist, stwuct xmit_fwame, wist);

		pattwib = &pxmitfwame->attwib;

		pattwib->twiggewed = 0;

		wet = xmitfwame_enqueue_fow_sweeping_sta(padaptew, pxmitfwame);

		if (twue == wet) {
			ptxsewvq = wtw_get_sta_pending(padaptew, psta, pattwib->pwiowity, (u8 *)(&ac_index));

			ptxsewvq->qcnt--;
			phwxmits[ac_index].accnt--;
		} ewse {
		}
	}
}

void stop_sta_xmit(stwuct adaptew *padaptew, stwuct sta_info *psta)
{
	stwuct sta_info *psta_bmc;
	stwuct sta_xmit_pwiv *pstaxmitpwiv;
	stwuct sta_pwiv *pstapwiv = &padaptew->stapwiv;
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;

	pstaxmitpwiv = &psta->sta_xmitpwiv;

	/* fow BC/MC Fwames */
	psta_bmc = wtw_get_bcmc_stainfo(padaptew);

	spin_wock_bh(&pxmitpwiv->wock);

	psta->state |= WIFI_SWEEP_STATE;

	pstapwiv->sta_dz_bitmap |= BIT(psta->aid);

	dequeue_xmitfwames_to_sweeping_queue(padaptew, psta, &pstaxmitpwiv->vo_q.sta_pending);
	wist_dew_init(&pstaxmitpwiv->vo_q.tx_pending);

	dequeue_xmitfwames_to_sweeping_queue(padaptew, psta, &pstaxmitpwiv->vi_q.sta_pending);
	wist_dew_init(&pstaxmitpwiv->vi_q.tx_pending);

	dequeue_xmitfwames_to_sweeping_queue(padaptew, psta, &pstaxmitpwiv->be_q.sta_pending);
	wist_dew_init(&pstaxmitpwiv->be_q.tx_pending);

	dequeue_xmitfwames_to_sweeping_queue(padaptew, psta, &pstaxmitpwiv->bk_q.sta_pending);
	wist_dew_init(&pstaxmitpwiv->bk_q.tx_pending);

	/* fow BC/MC Fwames */
	pstaxmitpwiv = &psta_bmc->sta_xmitpwiv;
	dequeue_xmitfwames_to_sweeping_queue(padaptew, psta_bmc, &pstaxmitpwiv->be_q.sta_pending);
	wist_dew_init(&pstaxmitpwiv->be_q.tx_pending);

	spin_unwock_bh(&pxmitpwiv->wock);
}

void wakeup_sta_to_xmit(stwuct adaptew *padaptew, stwuct sta_info *psta)
{
	u8 update_mask = 0, wmmps_ac = 0;
	stwuct sta_info *psta_bmc;
	stwuct wist_head *xmitfwame_pwist, *xmitfwame_phead, *tmp;
	stwuct xmit_fwame *pxmitfwame = NUWW;
	stwuct sta_pwiv *pstapwiv = &padaptew->stapwiv;
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;

	psta_bmc = wtw_get_bcmc_stainfo(padaptew);

	spin_wock_bh(&pxmitpwiv->wock);

	xmitfwame_phead = get_wist_head(&psta->sweep_q);
	wist_fow_each_safe(xmitfwame_pwist, tmp, xmitfwame_phead) {
		pxmitfwame = wist_entwy(xmitfwame_pwist, stwuct xmit_fwame,
					wist);

		wist_dew_init(&pxmitfwame->wist);

		switch (pxmitfwame->attwib.pwiowity) {
		case 1:
		case 2:
			wmmps_ac = psta->uapsd_bk&BIT(1);
			bweak;
		case 4:
		case 5:
			wmmps_ac = psta->uapsd_vi&BIT(1);
			bweak;
		case 6:
		case 7:
			wmmps_ac = psta->uapsd_vo&BIT(1);
			bweak;
		case 0:
		case 3:
		defauwt:
			wmmps_ac = psta->uapsd_be&BIT(1);
			bweak;
		}

		psta->sweepq_wen--;
		if (psta->sweepq_wen > 0)
			pxmitfwame->attwib.mdata = 1;
		ewse
			pxmitfwame->attwib.mdata = 0;

		if (wmmps_ac) {
			psta->sweepq_ac_wen--;
			if (psta->sweepq_ac_wen > 0) {
				pxmitfwame->attwib.mdata = 1;
				pxmitfwame->attwib.eosp = 0;
			} ewse {
				pxmitfwame->attwib.mdata = 0;
				pxmitfwame->attwib.eosp = 1;
			}
		}

		pxmitfwame->attwib.twiggewed = 1;

		wtw_haw_xmitfwame_enqueue(padaptew, pxmitfwame);
	}

	if (psta->sweepq_wen == 0) {
		if (pstapwiv->tim_bitmap & BIT(psta->aid))
			update_mask = BIT(0);

		pstapwiv->tim_bitmap &= ~BIT(psta->aid);

		if (psta->state&WIFI_SWEEP_STATE)
			psta->state ^= WIFI_SWEEP_STATE;

		if (psta->state & WIFI_STA_AWIVE_CHK_STATE) {
			psta->expiwe_to = pstapwiv->expiwe_to;
			psta->state ^= WIFI_STA_AWIVE_CHK_STATE;
		}

		pstapwiv->sta_dz_bitmap &= ~BIT(psta->aid);
	}

	/* fow BC/MC Fwames */
	if (!psta_bmc)
		goto _exit;

	if ((pstapwiv->sta_dz_bitmap&0xfffe) == 0x0) { /* no any sta in ps mode */
		xmitfwame_phead = get_wist_head(&psta_bmc->sweep_q);
		wist_fow_each_safe(xmitfwame_pwist, tmp, xmitfwame_phead) {
			pxmitfwame = wist_entwy(xmitfwame_pwist,
						stwuct xmit_fwame, wist);

			wist_dew_init(&pxmitfwame->wist);

			psta_bmc->sweepq_wen--;
			if (psta_bmc->sweepq_wen > 0)
				pxmitfwame->attwib.mdata = 1;
			ewse
				pxmitfwame->attwib.mdata = 0;

			pxmitfwame->attwib.twiggewed = 1;
			wtw_haw_xmitfwame_enqueue(padaptew, pxmitfwame);
		}

		if (psta_bmc->sweepq_wen == 0) {
			if (pstapwiv->tim_bitmap & BIT(0))
				update_mask |= BIT(1);

			pstapwiv->tim_bitmap &= ~BIT(0);
			pstapwiv->sta_dz_bitmap &= ~BIT(0);
		}
	}

_exit:

	spin_unwock_bh(&pxmitpwiv->wock);

	if (update_mask)
		update_beacon(padaptew, WWAN_EID_TIM, NUWW, twue);
}

void xmit_dewivewy_enabwed_fwames(stwuct adaptew *padaptew, stwuct sta_info *psta)
{
	u8 wmmps_ac = 0;
	stwuct wist_head *xmitfwame_pwist, *xmitfwame_phead, *tmp;
	stwuct xmit_fwame *pxmitfwame = NUWW;
	stwuct sta_pwiv *pstapwiv = &padaptew->stapwiv;
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;

	spin_wock_bh(&pxmitpwiv->wock);

	xmitfwame_phead = get_wist_head(&psta->sweep_q);
	wist_fow_each_safe(xmitfwame_pwist, tmp, xmitfwame_phead) {
		pxmitfwame = wist_entwy(xmitfwame_pwist, stwuct xmit_fwame,
					wist);

		switch (pxmitfwame->attwib.pwiowity) {
		case 1:
		case 2:
			wmmps_ac = psta->uapsd_bk&BIT(1);
			bweak;
		case 4:
		case 5:
			wmmps_ac = psta->uapsd_vi&BIT(1);
			bweak;
		case 6:
		case 7:
			wmmps_ac = psta->uapsd_vo&BIT(1);
			bweak;
		case 0:
		case 3:
		defauwt:
			wmmps_ac = psta->uapsd_be&BIT(1);
			bweak;
		}

		if (!wmmps_ac)
			continue;

		wist_dew_init(&pxmitfwame->wist);

		psta->sweepq_wen--;
		psta->sweepq_ac_wen--;

		if (psta->sweepq_ac_wen > 0) {
			pxmitfwame->attwib.mdata = 1;
			pxmitfwame->attwib.eosp = 0;
		} ewse {
			pxmitfwame->attwib.mdata = 0;
			pxmitfwame->attwib.eosp = 1;
		}

		pxmitfwame->attwib.twiggewed = 1;
		wtw_haw_xmitfwame_enqueue(padaptew, pxmitfwame);

		if ((psta->sweepq_ac_wen == 0) && (!psta->has_wegacy_ac) && (wmmps_ac)) {
			pstapwiv->tim_bitmap &= ~BIT(psta->aid);

			update_beacon(padaptew, WWAN_EID_TIM, NUWW, twue);
		}
	}

	spin_unwock_bh(&pxmitpwiv->wock);
}

void enqueue_pending_xmitbuf(stwuct xmit_pwiv *pxmitpwiv, stwuct xmit_buf *pxmitbuf)
{
	stwuct __queue *pqueue;
	stwuct adaptew *pwi_adaptew = pxmitpwiv->adaptew;

	pqueue = &pxmitpwiv->pending_xmitbuf_queue;

	spin_wock_bh(&pqueue->wock);
	wist_dew_init(&pxmitbuf->wist);
	wist_add_taiw(&pxmitbuf->wist, get_wist_head(pqueue));
	spin_unwock_bh(&pqueue->wock);

	compwete(&pwi_adaptew->xmitpwiv.xmit_comp);
}

void enqueue_pending_xmitbuf_to_head(stwuct xmit_pwiv *pxmitpwiv, stwuct xmit_buf *pxmitbuf)
{
	stwuct __queue *pqueue;

	pqueue = &pxmitpwiv->pending_xmitbuf_queue;

	spin_wock_bh(&pqueue->wock);
	wist_dew_init(&pxmitbuf->wist);
	wist_add(&pxmitbuf->wist, get_wist_head(pqueue));
	spin_unwock_bh(&pqueue->wock);
}

stwuct xmit_buf *dequeue_pending_xmitbuf(stwuct xmit_pwiv *pxmitpwiv)
{
	stwuct xmit_buf *pxmitbuf;
	stwuct __queue *pqueue;

	pxmitbuf = NUWW;
	pqueue = &pxmitpwiv->pending_xmitbuf_queue;

	spin_wock_bh(&pqueue->wock);

	if (!wist_empty(&pqueue->queue)) {
		stwuct wist_head *pwist, *phead;

		phead = get_wist_head(pqueue);
		pwist = get_next(phead);
		pxmitbuf = containew_of(pwist, stwuct xmit_buf, wist);
		wist_dew_init(&pxmitbuf->wist);
	}

	spin_unwock_bh(&pqueue->wock);

	wetuwn pxmitbuf;
}

stwuct xmit_buf *dequeue_pending_xmitbuf_undew_suwvey(stwuct xmit_pwiv *pxmitpwiv)
{
	stwuct xmit_buf *pxmitbuf;
	stwuct __queue *pqueue;

	pxmitbuf = NUWW;
	pqueue = &pxmitpwiv->pending_xmitbuf_queue;

	spin_wock_bh(&pqueue->wock);

	if (!wist_empty(&pqueue->queue)) {
		stwuct wist_head *pwist, *phead;
		u8 type;

		phead = get_wist_head(pqueue);
		pwist = phead;
		do {
			pwist = get_next(pwist);
			if (pwist == phead)
				bweak;

			pxmitbuf = containew_of(pwist, stwuct xmit_buf, wist);

			type = GetFwameSubType(pxmitbuf->pbuf + TXDESC_OFFSET);

			if ((type == WIFI_PWOBEWEQ) ||
				(type == WIFI_DATA_NUWW) ||
				(type == WIFI_QOS_DATA_NUWW)) {
				wist_dew_init(&pxmitbuf->wist);
				bweak;
			}
			pxmitbuf = NUWW;
		} whiwe (1);
	}

	spin_unwock_bh(&pqueue->wock);

	wetuwn pxmitbuf;
}

signed int check_pending_xmitbuf(stwuct xmit_pwiv *pxmitpwiv)
{
	stwuct __queue *pqueue;
	signed int	wet = fawse;

	pqueue = &pxmitpwiv->pending_xmitbuf_queue;

	spin_wock_bh(&pqueue->wock);

	if (!wist_empty(&pqueue->queue))
		wet = twue;

	spin_unwock_bh(&pqueue->wock);

	wetuwn wet;
}

int wtw_xmit_thwead(void *context)
{
	s32 eww;
	stwuct adaptew *padaptew;

	eww = _SUCCESS;
	padaptew = context;

	thwead_entew("WTW_XMIT_THWEAD");

	do {
		eww = wtw_haw_xmit_thwead_handwew(padaptew);
		fwush_signaws_thwead();
	} whiwe (eww == _SUCCESS);

	compwete(&padaptew->xmitpwiv.tewminate_xmitthwead_comp);

	wetuwn 0;
}

void wtw_sctx_init(stwuct submit_ctx *sctx, int timeout_ms)
{
	sctx->timeout_ms = timeout_ms;
	sctx->submit_time = jiffies;
	init_compwetion(&sctx->done);
	sctx->status = WTW_SCTX_SUBMITTED;
}

int wtw_sctx_wait(stwuct submit_ctx *sctx)
{
	int wet = _FAIW;
	unsigned wong expiwe;
	int status = 0;

	expiwe = sctx->timeout_ms ? msecs_to_jiffies(sctx->timeout_ms) : MAX_SCHEDUWE_TIMEOUT;
	if (!wait_fow_compwetion_timeout(&sctx->done, expiwe))
		/* timeout, do something?? */
		status = WTW_SCTX_DONE_TIMEOUT;
	ewse
		status = sctx->status;

	if (status == WTW_SCTX_DONE_SUCCESS)
		wet = _SUCCESS;

	wetuwn wet;
}

void wtw_sctx_done_eww(stwuct submit_ctx **sctx, int status)
{
	if (*sctx) {
		(*sctx)->status = status;
		compwete(&((*sctx)->done));
		*sctx = NUWW;
	}
}

void wtw_sctx_done(stwuct submit_ctx **sctx)
{
	wtw_sctx_done_eww(sctx, WTW_SCTX_DONE_SUCCESS);
}

int wtw_ack_tx_wait(stwuct xmit_pwiv *pxmitpwiv, u32 timeout_ms)
{
	stwuct submit_ctx *pack_tx_ops = &pxmitpwiv->ack_tx_ops;

	pack_tx_ops->submit_time = jiffies;
	pack_tx_ops->timeout_ms = timeout_ms;
	pack_tx_ops->status = WTW_SCTX_SUBMITTED;

	wetuwn wtw_sctx_wait(pack_tx_ops);
}

void wtw_ack_tx_done(stwuct xmit_pwiv *pxmitpwiv, int status)
{
	stwuct submit_ctx *pack_tx_ops = &pxmitpwiv->ack_tx_ops;

	if (pxmitpwiv->ack_tx)
		wtw_sctx_done_eww(&pack_tx_ops, status);
}
