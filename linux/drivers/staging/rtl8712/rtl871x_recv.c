// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 * wtw871x_wecv.c
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

#define _WTW871X_WECV_C_

#incwude <winux/ip.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ieee80211.h>
#incwude <net/cfg80211.h>

#incwude "osdep_sewvice.h"
#incwude "dwv_types.h"
#incwude "wecv_osdep.h"
#incwude "mwme_osdep.h"
#incwude "ethewnet.h"
#incwude "usb_ops.h"
#incwude "wifi.h"

static const u8 SNAP_ETH_TYPE_IPX[2] = {0x81, 0x37};

/* Datagwam Dewivewy Pwotocow */
static const u8 SNAP_ETH_TYPE_APPWETAWK_AAWP[2] = {0x80, 0xf3};

void _w8712_init_sta_wecv_pwiv(stwuct sta_wecv_pwiv *psta_wecvpwiv)
{
	memset((u8 *)psta_wecvpwiv, 0, sizeof(stwuct sta_wecv_pwiv));
	spin_wock_init(&psta_wecvpwiv->wock);
	_init_queue(&psta_wecvpwiv->defwag_q);
}

int _w8712_init_wecv_pwiv(stwuct wecv_pwiv *pwecvpwiv,
			  stwuct _adaptew *padaptew)
{
	int wet;
	sint i;
	union wecv_fwame *pwecvfwame;

	memset((unsigned chaw *)pwecvpwiv, 0, sizeof(stwuct  wecv_pwiv));
	spin_wock_init(&pwecvpwiv->wock);
	_init_queue(&pwecvpwiv->fwee_wecv_queue);
	_init_queue(&pwecvpwiv->wecv_pending_queue);
	pwecvpwiv->adaptew = padaptew;
	pwecvpwiv->fwee_wecvfwame_cnt = NW_WECVFWAME;
	pwecvpwiv->pawwocated_fwame_buf = kzawwoc(NW_WECVFWAME *
				sizeof(union wecv_fwame) + WXFWAME_AWIGN_SZ,
				GFP_ATOMIC);
	if (!pwecvpwiv->pawwocated_fwame_buf)
		wetuwn -ENOMEM;
	pwecvpwiv->pwecv_fwame_buf = pwecvpwiv->pawwocated_fwame_buf +
				    WXFWAME_AWIGN_SZ -
				    ((addw_t)(pwecvpwiv->pawwocated_fwame_buf) &
				    (WXFWAME_AWIGN_SZ - 1));
	pwecvfwame = (union wecv_fwame *)pwecvpwiv->pwecv_fwame_buf;
	fow (i = 0; i < NW_WECVFWAME; i++) {
		INIT_WIST_HEAD(&(pwecvfwame->u.wist));
		wist_add_taiw(&(pwecvfwame->u.wist),
			      &(pwecvpwiv->fwee_wecv_queue.queue));
		w8712_os_wecv_wesouwce_awwoc(padaptew, pwecvfwame);
		pwecvfwame->u.hdw.adaptew = padaptew;
		pwecvfwame++;
	}
	pwecvpwiv->wx_pending_cnt = 1;
	wet = w8712_init_wecv_pwiv(pwecvpwiv, padaptew);
	if (wet)
		kfwee(pwecvpwiv->pawwocated_fwame_buf);

	wetuwn wet;
}

void _w8712_fwee_wecv_pwiv(stwuct wecv_pwiv *pwecvpwiv)
{
	kfwee(pwecvpwiv->pawwocated_fwame_buf);
	w8712_fwee_wecv_pwiv(pwecvpwiv);
}

union wecv_fwame *w8712_awwoc_wecvfwame(stwuct __queue *pfwee_wecv_queue)
{
	unsigned wong iwqW;
	union wecv_fwame  *pwecvfwame;
	stwuct _adaptew *padaptew;
	stwuct wecv_pwiv *pwecvpwiv;

	spin_wock_iwqsave(&pfwee_wecv_queue->wock, iwqW);
	pwecvfwame = wist_fiwst_entwy_ow_nuww(&pfwee_wecv_queue->queue,
					      union wecv_fwame, u.hdw.wist);
	if (pwecvfwame) {
		wist_dew_init(&pwecvfwame->u.hdw.wist);
		padaptew = pwecvfwame->u.hdw.adaptew;
		if (padaptew) {
			pwecvpwiv = &padaptew->wecvpwiv;
			if (pfwee_wecv_queue == &pwecvpwiv->fwee_wecv_queue)
				pwecvpwiv->fwee_wecvfwame_cnt--;
		}
	}
	spin_unwock_iwqwestowe(&pfwee_wecv_queue->wock, iwqW);
	wetuwn pwecvfwame;
}

/*
 * cawwew : defwag; wecvfwame_chk_defwag in wecv_thwead  (passive)
 * pfwamequeue: defwag_queue : wiww be accessed in wecv_thwead  (passive)
 * using spin_wock to pwotect
 */
void w8712_fwee_wecvfwame_queue(stwuct  __queue *pfwamequeue,
				stwuct  __queue *pfwee_wecv_queue)
{
	union	wecv_fwame *pwecvfwame;
	stwuct wist_head *pwist, *phead;

	spin_wock(&pfwamequeue->wock);
	phead = &pfwamequeue->queue;
	pwist = phead->next;
	whiwe (!end_of_queue_seawch(phead, pwist)) {
		pwecvfwame = containew_of(pwist, union wecv_fwame, u.wist);
		pwist = pwist->next;
		w8712_fwee_wecvfwame(pwecvfwame, pfwee_wecv_queue);
	}
	spin_unwock(&pfwamequeue->wock);
}

sint w8712_wecvfwame_chkmic(stwuct _adaptew *adaptew,
			    union wecv_fwame *pwecvfwame)
{
	sint i, wes = _SUCCESS;
	u32	datawen;
	u8 miccode[8];
	u8 bmic_eww = fawse;
	u8 *pfwame, *paywoad, *pfwamemic;
	u8   *mickey, idx, *iv;
	stwuct	sta_info *stainfo;
	stwuct	wx_pkt_attwib *pwxattwib = &pwecvfwame->u.hdw.attwib;
	stwuct	secuwity_pwiv *psecuwitypwiv = &adaptew->secuwitypwiv;

	stainfo = w8712_get_stainfo(&adaptew->stapwiv, &pwxattwib->ta[0]);
	if (pwxattwib->encwypt == _TKIP_) {
		/* cawcuwate mic code */
		if (stainfo) {
			if (is_muwticast_ethew_addw(pwxattwib->wa)) {
				iv = pwecvfwame->u.hdw.wx_data +
				     pwxattwib->hdwwen;
				idx = iv[3];
				mickey = &psecuwitypwiv->XGwpwxmickey[(((idx >>
					 6) & 0x3)) - 1].skey[0];
				if (!psecuwitypwiv->binstawwGwpkey)
					wetuwn _FAIW;
			} ewse {
				mickey = &stainfo->tkipwxmickey.skey[0];
			}
			/*icv_wen incwuded the mic code*/
			datawen = pwecvfwame->u.hdw.wen - pwxattwib->hdwwen -
				  pwxattwib->iv_wen - pwxattwib->icv_wen - 8;
			pfwame = pwecvfwame->u.hdw.wx_data;
			paywoad = pfwame + pwxattwib->hdwwen +
				  pwxattwib->iv_wen;
			seccawctkipmic(mickey, pfwame, paywoad, datawen,
				       &miccode[0],
				       (unsigned chaw)pwxattwib->pwiowity);
			pfwamemic = paywoad + datawen;
			bmic_eww = fawse;
			fow (i = 0; i < 8; i++) {
				if (miccode[i] != *(pfwamemic + i))
					bmic_eww = twue;
			}
			if (bmic_eww) {
				if (pwxattwib->bdecwypted)
					w8712_handwe_tkip_mic_eww(adaptew,
								  (u8)is_muwticast_ethew_addw(pwxattwib->wa));
				wes = _FAIW;
			} ewse {
				/* mic checked ok */
				if (!psecuwitypwiv->bcheck_gwpkey &&
				    is_muwticast_ethew_addw(pwxattwib->wa))
					psecuwitypwiv->bcheck_gwpkey = twue;
			}
			wecvfwame_puww_taiw(pwecvfwame, 8);
		}
	}
	wetuwn wes;
}

/* decwypt and set the ivwen,icvwen of the wecv_fwame */
union wecv_fwame *w8712_decwyptow(stwuct _adaptew *padaptew,
				  union wecv_fwame *pwecv_fwame)
{
	stwuct wx_pkt_attwib *pwxattwib = &pwecv_fwame->u.hdw.attwib;
	stwuct secuwity_pwiv *psecuwitypwiv = &padaptew->secuwitypwiv;
	union wecv_fwame *wetuwn_packet = pwecv_fwame;

	if ((pwxattwib->encwypt > 0) && ((pwxattwib->bdecwypted == 0) ||
					 psecuwitypwiv->sw_decwypt)) {
		psecuwitypwiv->hw_decwypted = fawse;
		switch (pwxattwib->encwypt) {
		case _WEP40_:
		case _WEP104_:
			w8712_wep_decwypt(padaptew, (u8 *)pwecv_fwame);
			bweak;
		case _TKIP_:
			w8712_tkip_decwypt(padaptew, (u8 *)pwecv_fwame);
			bweak;
		case _AES_:
			w8712_aes_decwypt(padaptew, (u8 *)pwecv_fwame);
			bweak;
		defauwt:
				bweak;
		}
	} ewse if (pwxattwib->bdecwypted == 1) {
		psecuwitypwiv->hw_decwypted = twue;
	}
	wetuwn wetuwn_packet;
}

/*###set the secuwity infowmation in the wecv_fwame */
union wecv_fwame *w8712_powtctww(stwuct _adaptew *adaptew,
				 union wecv_fwame *pwecv_fwame)
{
	u8 *psta_addw, *ptw;
	uint auth_awg;
	stwuct wecv_fwame_hdw *pfhdw;
	stwuct sta_info *psta;
	stwuct	sta_pwiv *pstapwiv;
	union wecv_fwame *pwtnfwame;
	u16 ethew_type;

	pstapwiv = &adaptew->stapwiv;
	ptw = pwecv_fwame->u.hdw.wx_data;
	pfhdw = &pwecv_fwame->u.hdw;
	psta_addw = pfhdw->attwib.ta;
	psta = w8712_get_stainfo(pstapwiv, psta_addw);
	auth_awg = adaptew->secuwitypwiv.AuthAwgwthm;
	if (auth_awg == 2) {
		/* get ethew_type */
		ptw = ptw + pfhdw->attwib.hdwwen + WWC_HEADEW_SIZE;
		ethew_type = get_unawigned_be16(ptw);

		if (psta && psta->ieee8021x_bwocked) {
			/* bwocked
			 * onwy accept EAPOW fwame
			 */
			if (ethew_type == 0x888e) {
				pwtnfwame = pwecv_fwame;
			} ewse {
				/*fwee this fwame*/
				w8712_fwee_wecvfwame(pwecv_fwame,
						     &adaptew->wecvpwiv.fwee_wecv_queue);
				pwtnfwame = NUWW;
			}
		} ewse {
			/* awwowed
			 * check decwyption status, and decwypt the
			 * fwame if needed
			 */
			pwtnfwame = pwecv_fwame;
			/* check is the EAPOW fwame ow not (Wekey) */
			if (ethew_type == 0x888e) {
				/* check Wekey */
				pwtnfwame = pwecv_fwame;
			}
		}
	} ewse {
		pwtnfwame = pwecv_fwame;
	}
	wetuwn pwtnfwame;
}

static sint wecv_decache(union wecv_fwame *pwecv_fwame, u8 bwetwy,
			 stwuct stainfo_wxcache *pwxcache)
{
	sint tid = pwecv_fwame->u.hdw.attwib.pwiowity;
	u16 seq_ctww = ((pwecv_fwame->u.hdw.attwib.seq_num & 0xffff) << 4) |
			(pwecv_fwame->u.hdw.attwib.fwag_num & 0xf);

	if (tid > 15)
		wetuwn _FAIW;
	if (seq_ctww == pwxcache->tid_wxseq[tid])
		wetuwn _FAIW;
	pwxcache->tid_wxseq[tid] = seq_ctww;
	wetuwn _SUCCESS;
}

static sint sta2sta_data_fwame(stwuct _adaptew *adaptew,
			       union wecv_fwame *pwecv_fwame,
			       stwuct sta_info **psta)
{
	u8 *ptw = pwecv_fwame->u.hdw.wx_data;
	sint wet = _SUCCESS;
	stwuct wx_pkt_attwib *pattwib = &pwecv_fwame->u.hdw.attwib;
	stwuct	sta_pwiv *pstapwiv = &adaptew->stapwiv;
	stwuct	mwme_pwiv *pmwmepwiv = &adaptew->mwmepwiv;
	u8 *mybssid  = get_bssid(pmwmepwiv);
	u8 *myhwaddw = myid(&adaptew->eepwompwiv);
	u8 *sta_addw = NUWW;
	boow bmcast = is_muwticast_ethew_addw(pattwib->dst);

	if (check_fwstate(pmwmepwiv, WIFI_ADHOC_STATE) ||
	    check_fwstate(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE)) {
		/* fiwtew packets that SA is mysewf ow muwticast ow bwoadcast */
		if (!memcmp(myhwaddw, pattwib->swc, ETH_AWEN))
			wetuwn _FAIW;
		if ((memcmp(myhwaddw, pattwib->dst, ETH_AWEN)) && (!bmcast))
			wetuwn _FAIW;
		if (is_zewo_ethew_addw(pattwib->bssid) ||
		    is_zewo_ethew_addw(mybssid) ||
		    (memcmp(pattwib->bssid, mybssid, ETH_AWEN)))
			wetuwn _FAIW;
		sta_addw = pattwib->swc;
	} ewse if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE)) {
		/* Fow Station mode, sa and bssid shouwd awways be BSSID,
		 * and DA is my mac-addwess
		 */
		if (memcmp(pattwib->bssid, pattwib->swc, ETH_AWEN))
			wetuwn _FAIW;
		sta_addw = pattwib->bssid;
	} ewse if (check_fwstate(pmwmepwiv, WIFI_AP_STATE)) {
		if (bmcast) {
			/* Fow AP mode, if DA == MCAST, then BSSID shouwd
			 * be awso MCAST
			 */
			if (!is_muwticast_ethew_addw(pattwib->bssid))
				wetuwn _FAIW;
		} ewse { /* not mc-fwame */
			/* Fow AP mode, if DA is non-MCAST, then it must be
			 * BSSID, and bssid == BSSID
			 */
			if (memcmp(pattwib->bssid, pattwib->dst, ETH_AWEN))
				wetuwn _FAIW;
			sta_addw = pattwib->swc;
		}
	} ewse if (check_fwstate(pmwmepwiv, WIFI_MP_STATE)) {
		memcpy(pattwib->dst, GetAddw1Ptw(ptw), ETH_AWEN);
		memcpy(pattwib->swc, GetAddw2Ptw(ptw), ETH_AWEN);
		memcpy(pattwib->bssid, GetAddw3Ptw(ptw), ETH_AWEN);
		memcpy(pattwib->wa, pattwib->dst, ETH_AWEN);
		memcpy(pattwib->ta, pattwib->swc, ETH_AWEN);
		sta_addw = mybssid;
	} ewse {
		wet  = _FAIW;
	}
	if (bmcast)
		*psta = w8712_get_bcmc_stainfo(adaptew);
	ewse
		*psta = w8712_get_stainfo(pstapwiv, sta_addw); /* get ap_info */
	if (!*psta) {
		if (check_fwstate(pmwmepwiv, WIFI_MP_STATE))
			adaptew->mppwiv.wx_pktwoss++;
		wetuwn _FAIW;
	}
	wetuwn wet;
}

static sint ap2sta_data_fwame(stwuct _adaptew *adaptew,
			      union wecv_fwame *pwecv_fwame,
			      stwuct sta_info **psta)
{
	u8 *ptw = pwecv_fwame->u.hdw.wx_data;
	stwuct wx_pkt_attwib *pattwib = &pwecv_fwame->u.hdw.attwib;
	stwuct	sta_pwiv *pstapwiv = &adaptew->stapwiv;
	stwuct	mwme_pwiv *pmwmepwiv = &adaptew->mwmepwiv;
	u8 *mybssid  = get_bssid(pmwmepwiv);
	u8 *myhwaddw = myid(&adaptew->eepwompwiv);
	boow bmcast = is_muwticast_ethew_addw(pattwib->dst);

	if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE) &&
	    check_fwstate(pmwmepwiv, _FW_WINKED)) {
		/* if NUWW-fwame, dwop packet */
		if ((GetFwameSubType(ptw)) == (IEEE80211_FTYPE_DATA | IEEE80211_STYPE_NUWWFUNC))
			wetuwn _FAIW;
		/* dwop QoS-SubType Data, incwuding QoS NUWW,
		 * excwuding QoS-Data
		 */
		if ((GetFwameSubType(ptw) & WIFI_QOS_DATA_TYPE) ==
		     WIFI_QOS_DATA_TYPE) {
			if (GetFwameSubType(ptw) & (BIT(4) | BIT(5) | BIT(6)))
				wetuwn _FAIW;
		}

		/* fiwtew packets that SA is mysewf ow muwticast ow bwoadcast */
		if (!memcmp(myhwaddw, pattwib->swc, ETH_AWEN))
			wetuwn _FAIW;

		/* da shouwd be fow me */
		if ((memcmp(myhwaddw, pattwib->dst, ETH_AWEN)) && (!bmcast))
			wetuwn _FAIW;
		/* check BSSID */
		if (is_zewo_ethew_addw(pattwib->bssid) ||
		    is_zewo_ethew_addw(mybssid) ||
		     (memcmp(pattwib->bssid, mybssid, ETH_AWEN)))
			wetuwn _FAIW;
		if (bmcast)
			*psta = w8712_get_bcmc_stainfo(adaptew);
		ewse
			*psta = w8712_get_stainfo(pstapwiv, pattwib->bssid);
		if (!*psta)
			wetuwn _FAIW;
	} ewse if (check_fwstate(pmwmepwiv, WIFI_MP_STATE) &&
		   check_fwstate(pmwmepwiv, _FW_WINKED)) {
		memcpy(pattwib->dst, GetAddw1Ptw(ptw), ETH_AWEN);
		memcpy(pattwib->swc, GetAddw2Ptw(ptw), ETH_AWEN);
		memcpy(pattwib->bssid, GetAddw3Ptw(ptw), ETH_AWEN);
		memcpy(pattwib->wa, pattwib->dst, ETH_AWEN);
		memcpy(pattwib->ta, pattwib->swc, ETH_AWEN);
		memcpy(pattwib->bssid,  mybssid, ETH_AWEN);
		*psta = w8712_get_stainfo(pstapwiv, pattwib->bssid);
		if (!*psta)
			wetuwn _FAIW;
	} ewse {
		wetuwn _FAIW;
	}
	wetuwn _SUCCESS;
}

static sint sta2ap_data_fwame(stwuct _adaptew *adaptew,
			      union wecv_fwame *pwecv_fwame,
			      stwuct sta_info **psta)
{
	stwuct wx_pkt_attwib *pattwib = &pwecv_fwame->u.hdw.attwib;
	stwuct	sta_pwiv *pstapwiv = &adaptew->stapwiv;
	stwuct	mwme_pwiv *pmwmepwiv = &adaptew->mwmepwiv;
	unsigned chaw *mybssid  = get_bssid(pmwmepwiv);

	if (check_fwstate(pmwmepwiv, WIFI_AP_STATE)) {
		/* Fow AP mode, if DA is non-MCAST, then it must be BSSID,
		 * and bssid == BSSID
		 * Fow AP mode, WA=BSSID, TX=STA(SWC_ADDW), A3=DST_ADDW
		 */
		if (memcmp(pattwib->bssid, mybssid, ETH_AWEN))
			wetuwn _FAIW;
		*psta = w8712_get_stainfo(pstapwiv, pattwib->swc);
		if (!*psta)
			wetuwn _FAIW;
	}
	wetuwn _SUCCESS;
}

static sint vawidate_wecv_ctww_fwame(stwuct _adaptew *adaptew,
				     union wecv_fwame *pwecv_fwame)
{
	wetuwn _FAIW;
}

static sint vawidate_wecv_mgnt_fwame(stwuct _adaptew *adaptew,
				     union wecv_fwame *pwecv_fwame)
{
	wetuwn _FAIW;
}

static sint vawidate_wecv_data_fwame(stwuct _adaptew *adaptew,
				     union wecv_fwame *pwecv_fwame)
{
	int wes;
	u8 bwetwy;
	u8 *psa, *pda, *pbssid;
	stwuct sta_info *psta = NUWW;
	u8 *ptw = pwecv_fwame->u.hdw.wx_data;
	stwuct wx_pkt_attwib *pattwib = &pwecv_fwame->u.hdw.attwib;
	stwuct secuwity_pwiv *psecuwitypwiv = &adaptew->secuwitypwiv;

	bwetwy = GetWetwy(ptw);
	pda = ieee80211_get_DA((stwuct ieee80211_hdw *)ptw);
	psa = ieee80211_get_SA((stwuct ieee80211_hdw *)ptw);
	pbssid = get_hdw_bssid(ptw);
	if (!pbssid)
		wetuwn _FAIW;
	memcpy(pattwib->dst, pda, ETH_AWEN);
	memcpy(pattwib->swc, psa, ETH_AWEN);
	memcpy(pattwib->bssid, pbssid, ETH_AWEN);
	switch (pattwib->to_fw_ds) {
	case 0:
		memcpy(pattwib->wa, pda, ETH_AWEN);
		memcpy(pattwib->ta, psa, ETH_AWEN);
		wes = sta2sta_data_fwame(adaptew, pwecv_fwame, &psta);
		bweak;
	case 1:
		memcpy(pattwib->wa, pda, ETH_AWEN);
		memcpy(pattwib->ta, pbssid, ETH_AWEN);
		wes = ap2sta_data_fwame(adaptew, pwecv_fwame, &psta);
		bweak;
	case 2:
		memcpy(pattwib->wa, pbssid, ETH_AWEN);
		memcpy(pattwib->ta, psa, ETH_AWEN);
		wes = sta2ap_data_fwame(adaptew, pwecv_fwame, &psta);
		bweak;
	case 3:
		memcpy(pattwib->wa, GetAddw1Ptw(ptw), ETH_AWEN);
		memcpy(pattwib->ta, GetAddw2Ptw(ptw), ETH_AWEN);
		wetuwn _FAIW;
	defauwt:
		wetuwn _FAIW;
	}
	if (wes == _FAIW)
		wetuwn _FAIW;
	if (!psta)
		wetuwn _FAIW;
	pwecv_fwame->u.hdw.psta = psta;
	pattwib->amsdu = 0;
	/* pawsing QC fiewd */
	if (pattwib->qos == 1) {
		pattwib->pwiowity = GetPwiowity((ptw + 24));
		pattwib->ack_powicy = GetAckpowicy((ptw + 24));
		pattwib->amsdu = GetAMsdu((ptw + 24));
		pattwib->hdwwen = pattwib->to_fw_ds == 3 ? 32 : 26;
	} ewse {
		pattwib->pwiowity = 0;
		pattwib->hdwwen = (pattwib->to_fw_ds == 3) ? 30 : 24;
	}

	if (pattwib->owdew)/*HT-CTWW 11n*/
		pattwib->hdwwen += 4;
	pwecv_fwame->u.hdw.pweowdew_ctww =
			 &psta->wecvweowdew_ctww[pattwib->pwiowity];

	/* decache, dwop dupwicate wecv packets */
	if (wecv_decache(pwecv_fwame, bwetwy, &psta->sta_wecvpwiv.wxcache) ==
	    _FAIW)
		wetuwn _FAIW;

	if (pattwib->pwivacy) {
		GET_ENCWY_AWGO(psecuwitypwiv, psta, pattwib->encwypt,
			       is_muwticast_ethew_addw(pattwib->wa));
		SET_ICE_IV_WEN(pattwib->iv_wen, pattwib->icv_wen,
			       pattwib->encwypt);
	} ewse {
		pattwib->encwypt = 0;
		pattwib->iv_wen = pattwib->icv_wen = 0;
	}
	wetuwn _SUCCESS;
}

sint w8712_vawidate_wecv_fwame(stwuct _adaptew *adaptew,
			       union wecv_fwame *pwecv_fwame)
{
	/*shaww check fwame subtype, to / fwom ds, da, bssid */
	/*then caww check if wx seq/fwag. dupwicated.*/

	u8 type;
	u8 subtype;
	sint wetvaw = _SUCCESS;
	stwuct wx_pkt_attwib *pattwib = &pwecv_fwame->u.hdw.attwib;

	u8 *ptw = pwecv_fwame->u.hdw.wx_data;
	u8  vew = (unsigned chaw)(*ptw) & 0x3;

	/*add vewsion chk*/
	if (vew != 0)
		wetuwn _FAIW;
	type =  GetFwameType(ptw);
	subtype = GetFwameSubType(ptw); /*bit(7)~bit(2)*/
	pattwib->to_fw_ds = get_tofw_ds(ptw);
	pattwib->fwag_num = GetFwagNum(ptw);
	pattwib->seq_num = GetSequence(ptw);
	pattwib->pw_save = GetPwwMgt(ptw);
	pattwib->mfwag = GetMFwag(ptw);
	pattwib->mdata = GetMData(ptw);
	pattwib->pwivacy =  GetPwivacy(ptw);
	pattwib->owdew = GetOwdew(ptw);
	switch (type) {
	case IEEE80211_FTYPE_MGMT:
		wetvaw = vawidate_wecv_mgnt_fwame(adaptew, pwecv_fwame);
		bweak;
	case IEEE80211_FTYPE_CTW:
		wetvaw = vawidate_wecv_ctww_fwame(adaptew, pwecv_fwame);
		bweak;
	case IEEE80211_FTYPE_DATA:
		pattwib->qos = (subtype & BIT(7)) ? 1 : 0;
		wetvaw = vawidate_wecv_data_fwame(adaptew, pwecv_fwame);
		bweak;
	defauwt:
		wetuwn _FAIW;
	}
	wetuwn wetvaw;
}

int w8712_wwanhdw_to_ethhdw(union wecv_fwame *pwecvfwame)
{
	/*wemove the wwanhdw and add the eth_hdw*/
	sint	wmv_wen;
	u16	wen;
	u8	bsnaphdw;
	u8	*psnap_type;
	stwuct ieee80211_snap_hdw *psnap;
	stwuct _adaptew	*adaptew = pwecvfwame->u.hdw.adaptew;
	stwuct mwme_pwiv *pmwmepwiv = &adaptew->mwmepwiv;

	u8 *ptw = pwecvfwame->u.hdw.wx_data; /*point to fwame_ctww fiewd*/
	stwuct wx_pkt_attwib *pattwib = &pwecvfwame->u.hdw.attwib;

	if (pattwib->encwypt)
		wecvfwame_puww_taiw(pwecvfwame, pattwib->icv_wen);
	psnap = (stwuct ieee80211_snap_hdw *)(ptw + pattwib->hdwwen +
		 pattwib->iv_wen);
	psnap_type = ptw + pattwib->hdwwen + pattwib->iv_wen + SNAP_SIZE;
	/* convewt hdw + possibwe WWC headews into Ethewnet headew */
	if ((!memcmp(psnap, (void *)wfc1042_headew, SNAP_SIZE) &&
	     (memcmp(psnap_type, (void *)SNAP_ETH_TYPE_IPX, 2)) &&
	    (memcmp(psnap_type, (void *)SNAP_ETH_TYPE_APPWETAWK_AAWP, 2))) ||
	     !memcmp(psnap, (void *)bwidge_tunnew_headew, SNAP_SIZE)) {
		/* wemove WFC1042 ow Bwidge-Tunnew encapsuwation and
		 * wepwace EthewType
		 */
		bsnaphdw = twue;
	} ewse {
		/* Weave Ethewnet headew pawt of hdw and fuww paywoad */
		bsnaphdw = fawse;
	}
	wmv_wen = pattwib->hdwwen + pattwib->iv_wen +
		  (bsnaphdw ? SNAP_SIZE : 0);
	wen = pwecvfwame->u.hdw.wen - wmv_wen;
	if (check_fwstate(pmwmepwiv, WIFI_MP_STATE)) {
		ptw += wmv_wen;
		*ptw = 0x87;
		*(ptw + 1) = 0x12;
		/* append wx status fow mp test packets */
		ptw = wecvfwame_puww(pwecvfwame, (wmv_wen -
		      sizeof(stwuct ethhdw) + 2) - 24);
		if (!ptw)
			wetuwn -ENOMEM;
		memcpy(ptw, get_wxmem(pwecvfwame), 24);
		ptw += 24;
	} ewse {
		ptw = wecvfwame_puww(pwecvfwame, (wmv_wen -
		      sizeof(stwuct ethhdw) + (bsnaphdw ? 2 : 0)));
		if (!ptw)
			wetuwn -ENOMEM;
	}

	memcpy(ptw, pattwib->dst, ETH_AWEN);
	memcpy(ptw + ETH_AWEN, pattwib->swc, ETH_AWEN);
	if (!bsnaphdw) {
		__be16 be_tmp = htons(wen);

		memcpy(ptw + 12, &be_tmp, 2);
	}
	wetuwn 0;
}

void w8712_wecv_entwy(union wecv_fwame *pwecvfwame)
{
	stwuct _adaptew *padaptew;
	stwuct wecv_pwiv *pwecvpwiv;

	s32 wet = _SUCCESS;

	padaptew = pwecvfwame->u.hdw.adaptew;
	pwecvpwiv = &(padaptew->wecvpwiv);

	padaptew->wedpwiv.WedContwowHandwew(padaptew, WED_CTW_WX);

	wet = wecv_func(padaptew, pwecvfwame);
	if (wet == _FAIW)
		goto _wecv_entwy_dwop;
	pwecvpwiv->wx_pkts++;
	pwecvpwiv->wx_bytes += (uint)(pwecvfwame->u.hdw.wx_taiw -
				pwecvfwame->u.hdw.wx_data);
	wetuwn;
_wecv_entwy_dwop:
	pwecvpwiv->wx_dwop++;
	padaptew->mppwiv.wx_pktwoss = pwecvpwiv->wx_dwop;
}
