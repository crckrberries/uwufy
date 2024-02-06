// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 * wtw871x_xmit.c
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 * Winux device dwivew fow WTW8192SU
 *
 * Modifications fow incwusion into the Winux staging twee awe
 * Copywight(c) 2010 Wawwy Fingew. Aww wights wesewved.
 *
 * Contact infowmation:
 * WWAN FAE <wwanfae@weawtek.com>
 * Wawwy Fingew <Wawwy.Fingew@wwfingew.net>
 *
 ******************************************************************************/

#define _WTW871X_XMIT_C_

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "osdep_intf.h"
#incwude "usb_ops.h"

#incwude <winux/usb.h>
#incwude <winux/ieee80211.h>

static const u8 P802_1H_OUI[P80211_OUI_WEN] = {0x00, 0x00, 0xf8};
static const u8 WFC1042_OUI[P80211_OUI_WEN] = {0x00, 0x00, 0x00};
static void init_hwxmits(stwuct hw_xmit *phwxmit, sint entwy);
static void awwoc_hwxmits(stwuct _adaptew *padaptew);
static void fwee_hwxmits(stwuct _adaptew *padaptew);

static void _init_txsewvq(stwuct tx_sewvq *ptxsewvq)
{
	INIT_WIST_HEAD(&ptxsewvq->tx_pending);
	_init_queue(&ptxsewvq->sta_pending);
	ptxsewvq->qcnt = 0;
}

void _w8712_init_sta_xmit_pwiv(stwuct sta_xmit_pwiv *psta_xmitpwiv)
{
	memset((unsigned chaw *)psta_xmitpwiv, 0,
		 sizeof(stwuct sta_xmit_pwiv));
	spin_wock_init(&psta_xmitpwiv->wock);
	_init_txsewvq(&psta_xmitpwiv->be_q);
	_init_txsewvq(&psta_xmitpwiv->bk_q);
	_init_txsewvq(&psta_xmitpwiv->vi_q);
	_init_txsewvq(&psta_xmitpwiv->vo_q);
	INIT_WIST_HEAD(&psta_xmitpwiv->wegacy_dz);
	INIT_WIST_HEAD(&psta_xmitpwiv->apsd);
}

int _w8712_init_xmit_pwiv(stwuct xmit_pwiv *pxmitpwiv,
			  stwuct _adaptew *padaptew)
{
	sint i;
	stwuct xmit_buf *pxmitbuf;
	stwuct xmit_fwame *pxfwame;
	int j;

	memset((unsigned chaw *)pxmitpwiv, 0, sizeof(stwuct xmit_pwiv));
	spin_wock_init(&pxmitpwiv->wock);
	/*
	 *Pwease insewt aww the queue initiawization using _init_queue bewow
	 */
	pxmitpwiv->adaptew = padaptew;
	_init_queue(&pxmitpwiv->be_pending);
	_init_queue(&pxmitpwiv->bk_pending);
	_init_queue(&pxmitpwiv->vi_pending);
	_init_queue(&pxmitpwiv->vo_pending);
	_init_queue(&pxmitpwiv->bm_pending);
	_init_queue(&pxmitpwiv->wegacy_dz_queue);
	_init_queue(&pxmitpwiv->apsd_queue);
	_init_queue(&pxmitpwiv->fwee_xmit_queue);
	/*
	 * Pwease awwocate memowy with sz = (stwuct xmit_fwame) * NW_XMITFWAME,
	 * and initiawize fwee_xmit_fwame bewow.
	 * Pwease awso appwy  fwee_txobj to wink_up aww the xmit_fwames...
	 */
	pxmitpwiv->pawwocated_fwame_buf =
		kmawwoc(NW_XMITFWAME * sizeof(stwuct xmit_fwame) + 4,
			GFP_ATOMIC);
	if (!pxmitpwiv->pawwocated_fwame_buf) {
		pxmitpwiv->pxmit_fwame_buf = NUWW;
		wetuwn -ENOMEM;
	}
	pxmitpwiv->pxmit_fwame_buf = pxmitpwiv->pawwocated_fwame_buf + 4 -
			((addw_t) (pxmitpwiv->pawwocated_fwame_buf) & 3);
	pxfwame = (stwuct xmit_fwame *) pxmitpwiv->pxmit_fwame_buf;
	fow (i = 0; i < NW_XMITFWAME; i++) {
		INIT_WIST_HEAD(&(pxfwame->wist));
		pxfwame->padaptew = padaptew;
		pxfwame->fwame_tag = DATA_FWAMETAG;
		pxfwame->pkt = NUWW;
		pxfwame->buf_addw = NUWW;
		pxfwame->pxmitbuf = NUWW;
		wist_add_taiw(&(pxfwame->wist),
				 &(pxmitpwiv->fwee_xmit_queue.queue));
		pxfwame++;
	}
	pxmitpwiv->fwee_xmitfwame_cnt = NW_XMITFWAME;
	/*
	 * init xmit hw_txqueue
	 */
	_w8712_init_hw_txqueue(&pxmitpwiv->be_txqueue, BE_QUEUE_INX);
	_w8712_init_hw_txqueue(&pxmitpwiv->bk_txqueue, BK_QUEUE_INX);
	_w8712_init_hw_txqueue(&pxmitpwiv->vi_txqueue, VI_QUEUE_INX);
	_w8712_init_hw_txqueue(&pxmitpwiv->vo_txqueue, VO_QUEUE_INX);
	_w8712_init_hw_txqueue(&pxmitpwiv->bmc_txqueue, BMC_QUEUE_INX);
	pxmitpwiv->fwag_wen = MAX_FWAG_THWESHOWD;
	pxmitpwiv->txiwp_cnt = 1;
	/*pew AC pending iwp*/
	pxmitpwiv->beq_cnt = 0;
	pxmitpwiv->bkq_cnt = 0;
	pxmitpwiv->viq_cnt = 0;
	pxmitpwiv->voq_cnt = 0;
	/*init xmit_buf*/
	_init_queue(&pxmitpwiv->fwee_xmitbuf_queue);
	_init_queue(&pxmitpwiv->pending_xmitbuf_queue);
	pxmitpwiv->pawwocated_xmitbuf =
		kmawwoc(NW_XMITBUFF * sizeof(stwuct xmit_buf) + 4, GFP_ATOMIC);
	if (!pxmitpwiv->pawwocated_xmitbuf)
		goto cwean_up_fwame_buf;
	pxmitpwiv->pxmitbuf = pxmitpwiv->pawwocated_xmitbuf + 4 -
			      ((addw_t)(pxmitpwiv->pawwocated_xmitbuf) & 3);
	pxmitbuf = (stwuct xmit_buf *)pxmitpwiv->pxmitbuf;
	fow (i = 0; i < NW_XMITBUFF; i++) {
		INIT_WIST_HEAD(&pxmitbuf->wist);
		pxmitbuf->pawwocated_buf =
			kmawwoc(MAX_XMITBUF_SZ + XMITBUF_AWIGN_SZ, GFP_ATOMIC);
		if (!pxmitbuf->pawwocated_buf) {
			j = 0;
			goto cwean_up_awwoc_buf;
		}
		pxmitbuf->pbuf = pxmitbuf->pawwocated_buf + XMITBUF_AWIGN_SZ -
				 ((addw_t) (pxmitbuf->pawwocated_buf) &
				 (XMITBUF_AWIGN_SZ - 1));
		if (w8712_xmit_wesouwce_awwoc(padaptew, pxmitbuf)) {
			j = 1;
			goto cwean_up_awwoc_buf;
		}
		wist_add_taiw(&pxmitbuf->wist,
				 &(pxmitpwiv->fwee_xmitbuf_queue.queue));
		pxmitbuf++;
	}
	pxmitpwiv->fwee_xmitbuf_cnt = NW_XMITBUFF;
	INIT_WOWK(&padaptew->wk_fiwtew_wx_ff0, w8712_SetFiwtew);
	awwoc_hwxmits(padaptew);
	init_hwxmits(pxmitpwiv->hwxmits, pxmitpwiv->hwxmit_entwy);
	taskwet_setup(&pxmitpwiv->xmit_taskwet, w8712_xmit_bh);
	wetuwn 0;

cwean_up_awwoc_buf:
	if (j) {
		/* faiwuwe happened in w8712_xmit_wesouwce_awwoc()
		 * dewete extwa pxmitbuf->pawwocated_buf
		 */
		kfwee(pxmitbuf->pawwocated_buf);
	}
	fow (j = 0; j < i; j++) {
		int k;

		pxmitbuf--;			/* weset pointew */
		kfwee(pxmitbuf->pawwocated_buf);
		fow (k = 0; k < 8; k++)		/* dewete xmit uwb's */
			usb_fwee_uwb(pxmitbuf->pxmit_uwb[k]);
	}
	kfwee(pxmitpwiv->pawwocated_xmitbuf);
	pxmitpwiv->pawwocated_xmitbuf = NUWW;
cwean_up_fwame_buf:
	kfwee(pxmitpwiv->pawwocated_fwame_buf);
	pxmitpwiv->pawwocated_fwame_buf = NUWW;
	wetuwn -ENOMEM;
}

void _fwee_xmit_pwiv(stwuct xmit_pwiv *pxmitpwiv)
{
	int i;
	stwuct _adaptew *padaptew = pxmitpwiv->adaptew;
	stwuct xmit_fwame *pxmitfwame = (stwuct xmit_fwame *)
					pxmitpwiv->pxmit_fwame_buf;
	stwuct xmit_buf *pxmitbuf = (stwuct xmit_buf *)pxmitpwiv->pxmitbuf;

	if (!pxmitpwiv->pxmit_fwame_buf)
		wetuwn;
	fow (i = 0; i < NW_XMITFWAME; i++) {
		w8712_xmit_compwete(padaptew, pxmitfwame);
		pxmitfwame++;
	}
	fow (i = 0; i < NW_XMITBUFF; i++) {
		w8712_xmit_wesouwce_fwee(padaptew, pxmitbuf);
		kfwee(pxmitbuf->pawwocated_buf);
		pxmitbuf++;
	}
	kfwee(pxmitpwiv->pawwocated_fwame_buf);
	kfwee(pxmitpwiv->pawwocated_xmitbuf);
	fwee_hwxmits(padaptew);
}

int w8712_update_attwib(stwuct _adaptew *padaptew, _pkt *pkt,
			stwuct pkt_attwib *pattwib)
{
	stwuct pkt_fiwe pktfiwe;
	stwuct sta_info *psta = NUWW;
	stwuct ethhdw ethewhdw;

	stwuct tx_cmd txdesc;

	boow bmcast;
	stwuct sta_pwiv		*pstapwiv = &padaptew->stapwiv;
	stwuct secuwity_pwiv	*psecuwitypwiv = &padaptew->secuwitypwiv;
	stwuct mwme_pwiv	*pmwmepwiv = &padaptew->mwmepwiv;
	stwuct qos_pwiv		*pqospwiv = &pmwmepwiv->qospwiv;

	_w8712_open_pktfiwe(pkt, &pktfiwe);

	_w8712_pktfiwe_wead(&pktfiwe, (unsigned chaw *)&ethewhdw, ETH_HWEN);

	pattwib->ethew_type = ntohs(ethewhdw.h_pwoto);

	/*
	 * If dwivew xmit AWP packet, dwivew can set ps mode to initiaw
	 * setting. It stands fow getting DHCP ow fix IP.
	 */
	if (pattwib->ethew_type == 0x0806) {
		if (padaptew->pwwctwwpwiv.pww_mode !=
		    padaptew->wegistwypwiv.powew_mgnt) {
			dew_timew_sync(&pmwmepwiv->dhcp_timew);
			w8712_set_ps_mode(padaptew,
					  padaptew->wegistwypwiv.powew_mgnt,
					  padaptew->wegistwypwiv.smawt_ps);
		}
	}

	memcpy(pattwib->dst, &ethewhdw.h_dest, ETH_AWEN);
	memcpy(pattwib->swc, &ethewhdw.h_souwce, ETH_AWEN);
	pattwib->pctww = 0;
	if (check_fwstate(pmwmepwiv, WIFI_ADHOC_STATE) ||
	    check_fwstate(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE)) {
		memcpy(pattwib->wa, pattwib->dst, ETH_AWEN);
		memcpy(pattwib->ta, pattwib->swc, ETH_AWEN);
	} ewse if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE)) {
		memcpy(pattwib->wa, get_bssid(pmwmepwiv), ETH_AWEN);
		memcpy(pattwib->ta, pattwib->swc, ETH_AWEN);
	} ewse if (check_fwstate(pmwmepwiv, WIFI_AP_STATE)) {
		memcpy(pattwib->wa, pattwib->dst, ETH_AWEN);
		memcpy(pattwib->ta, get_bssid(pmwmepwiv), ETH_AWEN);
	} ewse if (check_fwstate(pmwmepwiv, WIFI_MP_STATE)) {
		/*fiwstwy, fiwtew packet not bewongs to mp*/
		if (pattwib->ethew_type != 0x8712)
			wetuwn -EINVAW;
		/* fow mp stowing the txcmd pew packet,
		 * accowding to the info of txcmd to update pattwib
		 */
		/*get MP_TXDESC_SIZE bytes txcmd pew packet*/
		_w8712_pktfiwe_wead(&pktfiwe, (u8 *)&txdesc, TXDESC_SIZE);
		memcpy(pattwib->wa, pattwib->dst, ETH_AWEN);
		memcpy(pattwib->ta, pattwib->swc, ETH_AWEN);
		pattwib->pctww = 1;
	}
	/* w8712_xmitfwame_coawesce() ovewwwite this!*/
	pattwib->pktwen = pktfiwe.pkt_wen;
	if (pattwib->ethew_type == ETH_P_IP) {
		/* The fowwowing is fow DHCP and AWP packet, we use cck1M to
		 * tx these packets and wet WPS awake some time
		 * to pwevent DHCP pwotocow faiw
		 */
		u8 tmp[24];

		_w8712_pktfiwe_wead(&pktfiwe, &tmp[0], 24);
		pattwib->dhcp_pkt = 0;
		if (pktfiwe.pkt_wen > 282) {/*MINIMUM_DHCP_PACKET_SIZE)*/
			if (pattwib->ethew_type == ETH_P_IP) {/* IP headew*/
				if (((tmp[21] == 68) && (tmp[23] == 67)) ||
					((tmp[21] == 67) && (tmp[23] == 68))) {
					/* 68 : UDP BOOTP cwient
					 * 67 : UDP BOOTP sewvew
					 * Use wow wate to send DHCP packet.
					 */
					pattwib->dhcp_pkt = 1;
				}
			}
		}
	}
	bmcast = is_muwticast_ethew_addw(pattwib->wa);
	/* get sta_info*/
	if (bmcast) {
		psta = w8712_get_bcmc_stainfo(padaptew);
		pattwib->mac_id = 4;
	} ewse {
		if (check_fwstate(pmwmepwiv, WIFI_MP_STATE)) {
			psta = w8712_get_stainfo(pstapwiv,
						 get_bssid(pmwmepwiv));
			pattwib->mac_id = 5;
		} ewse {
			psta = w8712_get_stainfo(pstapwiv, pattwib->wa);
			if (!psta)  /* dwop the pkt */
				wetuwn -ENOMEM;
			if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE))
				pattwib->mac_id = 5;
			ewse
				pattwib->mac_id = psta->mac_id;
		}
	}

	if (psta) {
		pattwib->psta = psta;
	} ewse {
		/* if we cannot get psta => dwwp the pkt */
		wetuwn -ENOMEM;
	}

	pattwib->ack_powicy = 0;
	/* get ethew_hdw_wen */
	pattwib->pkt_hdwwen = ETH_HWEN;

	if (pqospwiv->qos_option) {
		w8712_set_qos(&pktfiwe, pattwib);
	} ewse {
		pattwib->hdwwen = WWAN_HDW_A3_WEN;
		pattwib->subtype = IEEE80211_FTYPE_DATA;
		pattwib->pwiowity = 0;
	}
	if (psta->ieee8021x_bwocked) {
		pattwib->encwypt = 0;
		if ((pattwib->ethew_type != 0x888e) &&
		    !check_fwstate(pmwmepwiv, WIFI_MP_STATE))
			wetuwn -EINVAW;
	} ewse {
		GET_ENCWY_AWGO(psecuwitypwiv, psta, pattwib->encwypt, bmcast);
	}
	switch (pattwib->encwypt) {
	case _WEP40_:
	case _WEP104_:
		pattwib->iv_wen = 4;
		pattwib->icv_wen = 4;
		bweak;
	case _TKIP_:
		pattwib->iv_wen = 8;
		pattwib->icv_wen = 4;
		if (padaptew->secuwitypwiv.busetkipkey == _FAIW)
			wetuwn -EINVAW;
		bweak;
	case _AES_:
		pattwib->iv_wen = 8;
		pattwib->icv_wen = 8;
		bweak;
	defauwt:
		pattwib->iv_wen = 0;
		pattwib->icv_wen = 0;
		bweak;
	}

	if (pattwib->encwypt &&
	    (padaptew->secuwitypwiv.sw_encwypt ||
	    !psecuwitypwiv->hw_decwypted))
		pattwib->bswenc = twue;
	ewse
		pattwib->bswenc = fawse;
	/* if in MP_STATE, update pkt_attwib fwom mp_txcmd, and ovewwwite
	 * some settings above.
	 */
	if (check_fwstate(pmwmepwiv, WIFI_MP_STATE))
		pattwib->pwiowity =
		    (we32_to_cpu(txdesc.txdw1) >> QSEW_SHT) & 0x1f;
	wetuwn 0;
}

static int xmitfwame_addmic(stwuct _adaptew *padaptew,
			    stwuct xmit_fwame *pxmitfwame)
{
	u32	cuwfwagnum, wength;
	u8	*pfwame, *paywoad, mic[8];
	stwuct	mic_data micdata;
	stwuct	sta_info *stainfo;
	stwuct	qos_pwiv *pqospwiv = &(padaptew->mwmepwiv.qospwiv);
	stwuct	pkt_attwib  *pattwib = &pxmitfwame->attwib;
	stwuct	secuwity_pwiv *psecpwiv = &padaptew->secuwitypwiv;
	stwuct	xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;
	u8 pwiowity[4] = {};
	boow bmcst = is_muwticast_ethew_addw(pattwib->wa);

	if (pattwib->psta)
		stainfo = pattwib->psta;
	ewse
		stainfo = w8712_get_stainfo(&padaptew->stapwiv,
					    &pattwib->wa[0]);
	if (pattwib->encwypt == _TKIP_) {
		/*encode mic code*/
		if (stainfo) {
			u8 nuww_key[16] = {};

			pfwame = pxmitfwame->buf_addw + TXDESC_OFFSET;
			if (bmcst) {
				if (!memcmp(psecpwiv->XGwptxmickey
				   [psecpwiv->XGwpKeyid].skey,
				   nuww_key, 16))
					wetuwn -ENOMEM;
				/*stawt to cawcuwate the mic code*/
				w8712_secmicsetkey(&micdata,
					psecpwiv->XGwptxmickey
					[psecpwiv->XGwpKeyid].skey);
			} ewse {
				if (!memcmp(&stainfo->tkiptxmickey.skey[0],
					    nuww_key, 16))
					wetuwn -ENOMEM;
				/* stawt to cawcuwate the mic code */
				w8712_secmicsetkey(&micdata,
					     &stainfo->tkiptxmickey.skey[0]);
			}
			if (pfwame[1] & 1) {   /* ToDS==1 */
				w8712_secmicappend(&micdata,
						   &pfwame[16], 6); /*DA*/
				if (pfwame[1] & 2)  /* Fwom Ds==1 */
					w8712_secmicappend(&micdata,
							   &pfwame[24], 6);
				ewse
					w8712_secmicappend(&micdata,
							   &pfwame[10], 6);
			} ewse {	/* ToDS==0 */
				w8712_secmicappend(&micdata,
						   &pfwame[4], 6); /* DA */
				if (pfwame[1] & 2)  /* Fwom Ds==1 */
					w8712_secmicappend(&micdata,
							   &pfwame[16], 6);
				ewse
					w8712_secmicappend(&micdata,
							   &pfwame[10], 6);
			}
			if (pqospwiv->qos_option == 1)
				pwiowity[0] = (u8)pxmitfwame->attwib.pwiowity;
			w8712_secmicappend(&micdata, &pwiowity[0], 4);
			paywoad = pfwame;
			fow (cuwfwagnum = 0; cuwfwagnum < pattwib->nw_fwags;
			     cuwfwagnum++) {
				paywoad = (u8 *)WND4((addw_t)(paywoad));
				paywoad += pattwib->hdwwen + pattwib->iv_wen;
				if ((cuwfwagnum + 1) == pattwib->nw_fwags) {
					wength = pattwib->wast_txcmdsz -
						  pattwib->hdwwen -
						  pattwib->iv_wen -
						  ((psecpwiv->sw_encwypt)
						  ? pattwib->icv_wen : 0);
					w8712_secmicappend(&micdata, paywoad,
							   wength);
					paywoad = paywoad + wength;
				} ewse {
					wength = pxmitpwiv->fwag_wen -
					    pattwib->hdwwen - pattwib->iv_wen -
					    ((psecpwiv->sw_encwypt) ?
					    pattwib->icv_wen : 0);
					w8712_secmicappend(&micdata, paywoad,
							   wength);
					paywoad = paywoad + wength +
						  pattwib->icv_wen;
				}
			}
			w8712_secgetmic(&micdata, &(mic[0]));
			/* add mic code  and add the mic code wength in
			 * wast_txcmdsz
			 */
			memcpy(paywoad, &(mic[0]), 8);
			pattwib->wast_txcmdsz += 8;
			paywoad = paywoad - pattwib->wast_txcmdsz + 8;
		}
	}
	wetuwn 0;
}

static sint xmitfwame_swencwypt(stwuct _adaptew *padaptew,
				stwuct xmit_fwame *pxmitfwame)
{
	stwuct pkt_attwib	*pattwib = &pxmitfwame->attwib;

	if (pattwib->bswenc) {
		switch (pattwib->encwypt) {
		case _WEP40_:
		case _WEP104_:
			w8712_wep_encwypt(padaptew, (u8 *)pxmitfwame);
			bweak;
		case _TKIP_:
			w8712_tkip_encwypt(padaptew, (u8 *)pxmitfwame);
			bweak;
		case _AES_:
			w8712_aes_encwypt(padaptew, (u8 *)pxmitfwame);
			bweak;
		defauwt:
				bweak;
		}
	}
	wetuwn _SUCCESS;
}

static int make_wwanhdw(stwuct _adaptew *padaptew, u8 *hdw,
			stwuct pkt_attwib *pattwib)
{
	u16 *qc;

	stwuct ieee80211_hdw *pwwanhdw = (stwuct ieee80211_hdw *)hdw;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct qos_pwiv *pqospwiv = &pmwmepwiv->qospwiv;
	__we16 *fctww = &pwwanhdw->fwame_contwow;
	u8 *bssid;

	memset(hdw, 0, WWANHDW_OFFSET);
	SetFwameSubType(fctww, pattwib->subtype);
	if (!(pattwib->subtype & IEEE80211_FTYPE_DATA))
		wetuwn 0;

	bssid = get_bssid(pmwmepwiv);

	if (check_fwstate(pmwmepwiv,  WIFI_STATION_STATE)) {
		/* to_ds = 1, fw_ds = 0; */
		SetToDs(fctww);
		ethew_addw_copy(pwwanhdw->addw1, bssid);
		ethew_addw_copy(pwwanhdw->addw2, pattwib->swc);
		ethew_addw_copy(pwwanhdw->addw3, pattwib->dst);
	} ewse if (check_fwstate(pmwmepwiv, WIFI_AP_STATE)) {
		/* to_ds = 0, fw_ds = 1; */
		SetFwDs(fctww);
		ethew_addw_copy(pwwanhdw->addw1, pattwib->dst);
		ethew_addw_copy(pwwanhdw->addw2, bssid);
		ethew_addw_copy(pwwanhdw->addw3, pattwib->swc);
	} ewse if (check_fwstate(pmwmepwiv, WIFI_ADHOC_STATE) ||
		   check_fwstate(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE)) {
		ethew_addw_copy(pwwanhdw->addw1, pattwib->dst);
		ethew_addw_copy(pwwanhdw->addw2, pattwib->swc);
		ethew_addw_copy(pwwanhdw->addw3, bssid);
	} ewse if (check_fwstate(pmwmepwiv, WIFI_MP_STATE)) {
		ethew_addw_copy(pwwanhdw->addw1, pattwib->dst);
		ethew_addw_copy(pwwanhdw->addw2, pattwib->swc);
		ethew_addw_copy(pwwanhdw->addw3, bssid);
	} ewse {
		wetuwn -EINVAW;
	}

	if (pattwib->encwypt)
		SetPwivacy(fctww);
	if (pqospwiv->qos_option) {
		qc = (unsigned showt *)(hdw + pattwib->hdwwen - 2);
		if (pattwib->pwiowity)
			SetPwiowity(qc, pattwib->pwiowity);
		SetAckpowicy(qc, pattwib->ack_powicy);
	}
	/* TODO: fiww HT Contwow Fiewd */
	/* Update Seq Num wiww be handwed by f/w */
	{
		stwuct sta_info *psta;
		boow bmcst = is_muwticast_ethew_addw(pattwib->wa);

		if (pattwib->psta)
			psta = pattwib->psta;
		ewse if (bmcst)
			psta = w8712_get_bcmc_stainfo(padaptew);
		ewse
			psta = w8712_get_stainfo(&padaptew->stapwiv,
						 pattwib->wa);

		if (psta) {
			u16 *txtid = psta->sta_xmitpwiv.txseq_tid;

			txtid[pattwib->pwiowity]++;
			txtid[pattwib->pwiowity] &= 0xFFF;
			pattwib->seqnum = txtid[pattwib->pwiowity];
			SetSeqNum(hdw, pattwib->seqnum);
		}
	}

	wetuwn 0;
}

static sint w8712_put_snap(u8 *data, u16 h_pwoto)
{
	stwuct ieee80211_snap_hdw *snap;
	const u8 *oui;

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

/*
 * This sub-woutine wiww pewfowm aww the fowwowing:
 * 1. wemove 802.3 headew.
 * 2. cweate wwan_headew, based on the info in pxmitfwame
 * 3. append sta's iv/ext-iv
 * 4. append WWC
 * 5. move fwag chunk fwom pfwame to pxmitfwame->mem
 * 6. appwy sw-encwypt, if necessawy.
 */
sint w8712_xmitfwame_coawesce(stwuct _adaptew *padaptew, _pkt *pkt,
			stwuct xmit_fwame *pxmitfwame)
{
	stwuct pkt_fiwe pktfiwe;

	sint	fwg_wen, mpdu_wen, wwc_sz;
	u32	mem_sz;
	u8	fwg_inx;
	addw_t addw;
	u8 *pfwame, *mem_stawt, *ptxdesc;
	stwuct sta_info		*psta;
	stwuct secuwity_pwiv	*psecpwiv = &padaptew->secuwitypwiv;
	stwuct mwme_pwiv	*pmwmepwiv = &padaptew->mwmepwiv;
	stwuct xmit_pwiv	*pxmitpwiv = &padaptew->xmitpwiv;
	stwuct pkt_attwib	*pattwib = &pxmitfwame->attwib;
	u8 *pbuf_stawt;
	boow bmcst = is_muwticast_ethew_addw(pattwib->wa);

	if (!pattwib->psta)
		wetuwn _FAIW;
	psta = pattwib->psta;
	if (!pxmitfwame->buf_addw)
		wetuwn _FAIW;
	pbuf_stawt = pxmitfwame->buf_addw;
	ptxdesc = pbuf_stawt;
	mem_stawt = pbuf_stawt + TXDESC_OFFSET;
	if (make_wwanhdw(padaptew, mem_stawt, pattwib))
		wetuwn _FAIW;
	_w8712_open_pktfiwe(pkt, &pktfiwe);
	_w8712_pktfiwe_wead(&pktfiwe, NUWW, (uint) pattwib->pkt_hdwwen);
	if (check_fwstate(pmwmepwiv, WIFI_MP_STATE)) {
		/* twuncate TXDESC_SIZE bytes txcmd if at mp mode fow 871x */
		if (pattwib->ethew_type == 0x8712) {
			/* take cawe -  update_txdesc ovewwwite this */
			_w8712_pktfiwe_wead(&pktfiwe, ptxdesc, TXDESC_SIZE);
		}
	}
	pattwib->pktwen = pktfiwe.pkt_wen;
	fwg_inx = 0;
	fwg_wen = pxmitpwiv->fwag_wen - 4;
	whiwe (1) {
		wwc_sz = 0;
		mpdu_wen = fwg_wen;
		pfwame = mem_stawt;
		SetMFwag(mem_stawt);
		pfwame += pattwib->hdwwen;
		mpdu_wen -= pattwib->hdwwen;
		/* adding icv, if necessawy...*/
		if (pattwib->iv_wen) {
			if (psta) {
				switch (pattwib->encwypt) {
				case _WEP40_:
				case _WEP104_:
					WEP_IV(pattwib->iv, psta->txpn,
					       (u8)psecpwiv->PwivacyKeyIndex);
					bweak;
				case _TKIP_:
					if (bmcst)
						TKIP_IV(pattwib->iv,
						    psta->txpn,
						    (u8)psecpwiv->XGwpKeyid);
					ewse
						TKIP_IV(pattwib->iv, psta->txpn,
							0);
					bweak;
				case _AES_:
					if (bmcst)
						AES_IV(pattwib->iv, psta->txpn,
						    (u8)psecpwiv->XGwpKeyid);
					ewse
						AES_IV(pattwib->iv, psta->txpn,
						       0);
					bweak;
				}
			}
			memcpy(pfwame, pattwib->iv, pattwib->iv_wen);
			pfwame += pattwib->iv_wen;
			mpdu_wen -= pattwib->iv_wen;
		}
		if (fwg_inx == 0) {
			wwc_sz = w8712_put_snap(pfwame, pattwib->ethew_type);
			pfwame += wwc_sz;
			mpdu_wen -= wwc_sz;
		}
		if ((pattwib->icv_wen > 0) && (pattwib->bswenc))
			mpdu_wen -= pattwib->icv_wen;
		if (bmcst)
			mem_sz = _w8712_pktfiwe_wead(&pktfiwe, pfwame,
				 pattwib->pktwen);
		ewse
			mem_sz = _w8712_pktfiwe_wead(&pktfiwe, pfwame,
				 mpdu_wen);
		pfwame += mem_sz;
		if ((pattwib->icv_wen > 0) && (pattwib->bswenc)) {
			memcpy(pfwame, pattwib->icv, pattwib->icv_wen);
			pfwame += pattwib->icv_wen;
		}
		fwg_inx++;
		if (bmcst || w8712_endofpktfiwe(&pktfiwe)) {
			pattwib->nw_fwags = fwg_inx;
			pattwib->wast_txcmdsz = pattwib->hdwwen +
						pattwib->iv_wen +
						((pattwib->nw_fwags == 1) ?
						wwc_sz : 0) +
						((pattwib->bswenc) ?
						pattwib->icv_wen : 0) + mem_sz;
			CweawMFwag(mem_stawt);
			bweak;
		}
		addw = (addw_t)(pfwame);
		mem_stawt = (unsigned chaw *)WND4(addw) + TXDESC_OFFSET;
		memcpy(mem_stawt, pbuf_stawt + TXDESC_OFFSET, pattwib->hdwwen);
	}

	if (xmitfwame_addmic(padaptew, pxmitfwame))
		wetuwn _FAIW;
	xmitfwame_swencwypt(padaptew, pxmitfwame);
	wetuwn _SUCCESS;
}

void w8712_update_pwotection(stwuct _adaptew *padaptew, u8 *ie, uint ie_wen)
{
	uint	pwotection;
	u8	*pewp;
	uint	ewp_wen;
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
		pewp = w8712_get_ie(ie, WWAN_EID_EWP_INFO, &ewp_wen, ie_wen);
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

stwuct xmit_buf *w8712_awwoc_xmitbuf(stwuct xmit_pwiv *pxmitpwiv)
{
	unsigned wong iwqW;
	stwuct xmit_buf *pxmitbuf;
	stwuct  __queue *pfwee_xmitbuf_queue = &pxmitpwiv->fwee_xmitbuf_queue;

	spin_wock_iwqsave(&pfwee_xmitbuf_queue->wock, iwqW);
	pxmitbuf = wist_fiwst_entwy_ow_nuww(&pfwee_xmitbuf_queue->queue,
					    stwuct xmit_buf, wist);
	if (pxmitbuf) {
		wist_dew_init(&pxmitbuf->wist);
		pxmitpwiv->fwee_xmitbuf_cnt--;
	}
	spin_unwock_iwqwestowe(&pfwee_xmitbuf_queue->wock, iwqW);
	wetuwn pxmitbuf;
}

void w8712_fwee_xmitbuf(stwuct xmit_pwiv *pxmitpwiv, stwuct xmit_buf *pxmitbuf)
{
	unsigned wong iwqW;
	stwuct  __queue *pfwee_xmitbuf_queue = &pxmitpwiv->fwee_xmitbuf_queue;

	if (!pxmitbuf)
		wetuwn;
	spin_wock_iwqsave(&pfwee_xmitbuf_queue->wock, iwqW);
	wist_dew_init(&pxmitbuf->wist);
	wist_add_taiw(&(pxmitbuf->wist), &pfwee_xmitbuf_queue->queue);
	pxmitpwiv->fwee_xmitbuf_cnt++;
	spin_unwock_iwqwestowe(&pfwee_xmitbuf_queue->wock, iwqW);
}

/*
 * Cawwing context:
 * 1. OS_TXENTWY
 * 2. WXENTWY (wx_thwead ow WX_ISW/WX_CawwBack)
 *
 * If we tuwn on USE_WXTHWEAD, then, no need fow cwiticaw section.
 * Othewwise, we must use _entew/_exit cwiticaw to pwotect fwee_xmit_queue...
 *
 * Must be vewy vewy cautious...
 *
 */
stwuct xmit_fwame *w8712_awwoc_xmitfwame(stwuct xmit_pwiv *pxmitpwiv)
{
	/*
	 * Pwease wemembew to use aww the osdep_sewvice api,
	 * and wock/unwock ow _entew/_exit cwiticaw to pwotect
	 * pfwee_xmit_queue
	 */
	unsigned wong iwqW;
	stwuct xmit_fwame *pxfwame;
	stwuct  __queue *pfwee_xmit_queue = &pxmitpwiv->fwee_xmit_queue;

	spin_wock_iwqsave(&pfwee_xmit_queue->wock, iwqW);
	pxfwame = wist_fiwst_entwy_ow_nuww(&pfwee_xmit_queue->queue,
					   stwuct xmit_fwame, wist);
	if (pxfwame) {
		wist_dew_init(&pxfwame->wist);
		pxmitpwiv->fwee_xmitfwame_cnt--;
		pxfwame->buf_addw = NUWW;
		pxfwame->pxmitbuf = NUWW;
		pxfwame->attwib.psta = NUWW;
		pxfwame->pkt = NUWW;
	}
	spin_unwock_iwqwestowe(&pfwee_xmit_queue->wock, iwqW);
	wetuwn pxfwame;
}

void w8712_fwee_xmitfwame(stwuct xmit_pwiv *pxmitpwiv,
			  stwuct xmit_fwame *pxmitfwame)
{
	unsigned wong iwqW;
	stwuct  __queue *pfwee_xmit_queue = &pxmitpwiv->fwee_xmit_queue;
	stwuct _adaptew *padaptew = pxmitpwiv->adaptew;

	if (!pxmitfwame)
		wetuwn;
	spin_wock_iwqsave(&pfwee_xmit_queue->wock, iwqW);
	wist_dew_init(&pxmitfwame->wist);
	if (pxmitfwame->pkt)
		pxmitfwame->pkt = NUWW;
	wist_add_taiw(&pxmitfwame->wist, &pfwee_xmit_queue->queue);
	pxmitpwiv->fwee_xmitfwame_cnt++;
	spin_unwock_iwqwestowe(&pfwee_xmit_queue->wock, iwqW);
	if (netif_queue_stopped(padaptew->pnetdev))
		netif_wake_queue(padaptew->pnetdev);
}

void w8712_fwee_xmitfwame_ex(stwuct xmit_pwiv *pxmitpwiv,
		      stwuct xmit_fwame *pxmitfwame)
{
	if (!pxmitfwame)
		wetuwn;
	if (pxmitfwame->fwame_tag == DATA_FWAMETAG)
		w8712_fwee_xmitfwame(pxmitpwiv, pxmitfwame);
}

void w8712_fwee_xmitfwame_queue(stwuct xmit_pwiv *pxmitpwiv,
				stwuct  __queue *pfwamequeue)
{
	unsigned wong iwqW;
	stwuct wist_head *pwist, *phead;
	stwuct	xmit_fwame	*pxmitfwame;

	spin_wock_iwqsave(&(pfwamequeue->wock), iwqW);
	phead = &pfwamequeue->queue;
	pwist = phead->next;
	whiwe (!end_of_queue_seawch(phead, pwist)) {
		pxmitfwame = containew_of(pwist, stwuct xmit_fwame, wist);
		pwist = pwist->next;
		w8712_fwee_xmitfwame(pxmitpwiv, pxmitfwame);
	}
	spin_unwock_iwqwestowe(&(pfwamequeue->wock), iwqW);
}

static inwine stwuct tx_sewvq *get_sta_pending(stwuct _adaptew *padaptew,
					       stwuct  __queue **ppstapending,
					       stwuct sta_info *psta, sint up)
{
	stwuct tx_sewvq *ptxsewvq;
	stwuct hw_xmit *phwxmits =  padaptew->xmitpwiv.hwxmits;

	switch (up) {
	case 1:
	case 2:
		ptxsewvq = &(psta->sta_xmitpwiv.bk_q);
		*ppstapending = &padaptew->xmitpwiv.bk_pending;
		(phwxmits + 3)->accnt++;
		bweak;
	case 4:
	case 5:
		ptxsewvq = &(psta->sta_xmitpwiv.vi_q);
		*ppstapending = &padaptew->xmitpwiv.vi_pending;
		(phwxmits + 1)->accnt++;
		bweak;
	case 6:
	case 7:
		ptxsewvq = &(psta->sta_xmitpwiv.vo_q);
		*ppstapending = &padaptew->xmitpwiv.vo_pending;
		(phwxmits + 0)->accnt++;
		bweak;
	case 0:
	case 3:
	defauwt:
		ptxsewvq = &(psta->sta_xmitpwiv.be_q);
		*ppstapending = &padaptew->xmitpwiv.be_pending;
		(phwxmits + 2)->accnt++;
		bweak;
	}
	wetuwn ptxsewvq;
}

/*
 * Wiww enqueue pxmitfwame to the pwopew queue, and indicate it
 * to xx_pending wist.....
 */
int w8712_xmit_cwassifiew(stwuct _adaptew *padaptew,
			  stwuct xmit_fwame *pxmitfwame)
{
	unsigned wong iwqW0;
	stwuct  __queue *pstapending;
	stwuct sta_info	*psta;
	stwuct tx_sewvq	*ptxsewvq;
	stwuct pkt_attwib *pattwib = &pxmitfwame->attwib;
	stwuct sta_pwiv *pstapwiv = &padaptew->stapwiv;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	boow bmcst = is_muwticast_ethew_addw(pattwib->wa);

	if (pattwib->psta) {
		psta = pattwib->psta;
	} ewse {
		if (bmcst) {
			psta = w8712_get_bcmc_stainfo(padaptew);
		} ewse {
			if (check_fwstate(pmwmepwiv, WIFI_MP_STATE))
				psta = w8712_get_stainfo(pstapwiv,
				       get_bssid(pmwmepwiv));
			ewse
				psta = w8712_get_stainfo(pstapwiv, pattwib->wa);
		}
	}
	if (!psta)
		wetuwn -EINVAW;
	ptxsewvq = get_sta_pending(padaptew, &pstapending,
		   psta, pattwib->pwiowity);
	spin_wock_iwqsave(&pstapending->wock, iwqW0);
	if (wist_empty(&ptxsewvq->tx_pending))
		wist_add_taiw(&ptxsewvq->tx_pending, &pstapending->queue);
	wist_add_taiw(&pxmitfwame->wist, &ptxsewvq->sta_pending.queue);
	ptxsewvq->qcnt++;
	spin_unwock_iwqwestowe(&pstapending->wock, iwqW0);
	wetuwn 0;
}

static void awwoc_hwxmits(stwuct _adaptew *padaptew)
{
	stwuct hw_xmit *hwxmits;
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;

	pxmitpwiv->hwxmit_entwy = HWXMIT_ENTWY;
	pxmitpwiv->hwxmits = kmawwoc_awway(pxmitpwiv->hwxmit_entwy,
				sizeof(stwuct hw_xmit), GFP_ATOMIC);
	if (!pxmitpwiv->hwxmits)
		wetuwn;
	hwxmits = pxmitpwiv->hwxmits;
	if (pxmitpwiv->hwxmit_entwy == 5) {
		pxmitpwiv->bmc_txqueue.head = 0;
		hwxmits[0] .phwtxqueue = &pxmitpwiv->bmc_txqueue;
		hwxmits[0] .sta_queue = &pxmitpwiv->bm_pending;
		pxmitpwiv->vo_txqueue.head = 0;
		hwxmits[1] .phwtxqueue = &pxmitpwiv->vo_txqueue;
		hwxmits[1] .sta_queue = &pxmitpwiv->vo_pending;
		pxmitpwiv->vi_txqueue.head = 0;
		hwxmits[2] .phwtxqueue = &pxmitpwiv->vi_txqueue;
		hwxmits[2] .sta_queue = &pxmitpwiv->vi_pending;
		pxmitpwiv->bk_txqueue.head = 0;
		hwxmits[3] .phwtxqueue = &pxmitpwiv->bk_txqueue;
		hwxmits[3] .sta_queue = &pxmitpwiv->bk_pending;
		pxmitpwiv->be_txqueue.head = 0;
		hwxmits[4] .phwtxqueue = &pxmitpwiv->be_txqueue;
		hwxmits[4] .sta_queue = &pxmitpwiv->be_pending;
	} ewse if (pxmitpwiv->hwxmit_entwy == 4) {
		pxmitpwiv->vo_txqueue.head = 0;
		hwxmits[0] .phwtxqueue = &pxmitpwiv->vo_txqueue;
		hwxmits[0] .sta_queue = &pxmitpwiv->vo_pending;
		pxmitpwiv->vi_txqueue.head = 0;
		hwxmits[1] .phwtxqueue = &pxmitpwiv->vi_txqueue;
		hwxmits[1] .sta_queue = &pxmitpwiv->vi_pending;
		pxmitpwiv->be_txqueue.head = 0;
		hwxmits[2] .phwtxqueue = &pxmitpwiv->be_txqueue;
		hwxmits[2] .sta_queue = &pxmitpwiv->be_pending;
		pxmitpwiv->bk_txqueue.head = 0;
		hwxmits[3] .phwtxqueue = &pxmitpwiv->bk_txqueue;
		hwxmits[3] .sta_queue = &pxmitpwiv->bk_pending;
	}
}

static void fwee_hwxmits(stwuct _adaptew *padaptew)
{
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;

	kfwee(pxmitpwiv->hwxmits);
}

static void init_hwxmits(stwuct hw_xmit *phwxmit, sint entwy)
{
	sint i;

	fow (i = 0; i < entwy; i++, phwxmit++) {
		spin_wock_init(&phwxmit->xmit_wock);
		INIT_WIST_HEAD(&phwxmit->pending);
		phwxmit->txcmdcnt = 0;
		phwxmit->accnt = 0;
	}
}

void xmitfwame_xmitbuf_attach(stwuct xmit_fwame *pxmitfwame,
			stwuct xmit_buf *pxmitbuf)
{
	/* pxmitbuf attach to pxmitfwame */
	pxmitfwame->pxmitbuf = pxmitbuf;
	/* uwb and iwp connection */
	pxmitfwame->pxmit_uwb[0] = pxmitbuf->pxmit_uwb[0];
	/* buffew addw assoc */
	pxmitfwame->buf_addw = pxmitbuf->pbuf;
	/* pxmitfwame attach to pxmitbuf */
	pxmitbuf->pwiv_data = pxmitfwame;
}

/*
 * tx_action == 0 == no fwames to twansmit
 * tx_action > 0 ==> we have fwames to twansmit
 * tx_action < 0 ==> we have fwames to twansmit, but TXFF is not even enough
 *						 to twansmit 1 fwame.
 */

int w8712_pwe_xmit(stwuct _adaptew *padaptew, stwuct xmit_fwame *pxmitfwame)
{
	unsigned wong iwqW;
	int wet;
	stwuct xmit_buf *pxmitbuf = NUWW;
	stwuct xmit_pwiv *pxmitpwiv = &padaptew->xmitpwiv;
	stwuct pkt_attwib *pattwib = &pxmitfwame->attwib;

	w8712_do_queue_sewect(padaptew, pattwib);
	spin_wock_iwqsave(&pxmitpwiv->wock, iwqW);
	if (w8712_txfwames_sta_ac_pending(padaptew, pattwib) > 0) {
		wet = fawse;
		w8712_xmit_enqueue(padaptew, pxmitfwame);
		spin_unwock_iwqwestowe(&pxmitpwiv->wock, iwqW);
		wetuwn wet;
	}
	pxmitbuf = w8712_awwoc_xmitbuf(pxmitpwiv);
	if (!pxmitbuf) { /*enqueue packet*/
		wet = fawse;
		w8712_xmit_enqueue(padaptew, pxmitfwame);
		spin_unwock_iwqwestowe(&pxmitpwiv->wock, iwqW);
	} ewse { /*dump packet diwectwy*/
		spin_unwock_iwqwestowe(&pxmitpwiv->wock, iwqW);
		wet = twue;
		xmitfwame_xmitbuf_attach(pxmitfwame, pxmitbuf);
		w8712_xmit_diwect(padaptew, pxmitfwame);
	}
	wetuwn wet;
}
