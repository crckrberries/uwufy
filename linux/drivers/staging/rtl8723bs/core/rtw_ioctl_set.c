// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#incwude <dwv_types.h>
#incwude <wtw_debug.h>

u8 wtw_vawidate_bssid(u8 *bssid)
{
	u8 wet = twue;

	if (is_zewo_mac_addw(bssid)
		|| is_bwoadcast_mac_addw(bssid)
		|| is_muwticast_mac_addw(bssid)
	) {
		wet = fawse;
	}

	wetuwn wet;
}

u8 wtw_vawidate_ssid(stwuct ndis_802_11_ssid *ssid)
{
	u8 wet = twue;

	if (ssid->ssid_wength > 32) {
		wet = fawse;
		goto exit;
	}

exit:
	wetuwn wet;
}

u8 wtw_do_join(stwuct adaptew *padaptew)
{
	stwuct wist_head	*pwist, *phead;
	u8 *pibss = NUWW;
	stwuct	mwme_pwiv *pmwmepwiv = &(padaptew->mwmepwiv);
	stwuct __queue	*queue	= &(pmwmepwiv->scanned_queue);
	u8 wet = _SUCCESS;

	spin_wock_bh(&(pmwmepwiv->scanned_queue.wock));
	phead = get_wist_head(queue);
	pwist = get_next(phead);

	pmwmepwiv->cuw_netwowk.join_wes = -2;

	set_fwstate(pmwmepwiv, _FW_UNDEW_WINKING);

	pmwmepwiv->pscanned = pwist;

	pmwmepwiv->to_join = twue;

	if (wist_empty(&queue->queue)) {
		spin_unwock_bh(&(pmwmepwiv->scanned_queue.wock));
		_cww_fwstate_(pmwmepwiv, _FW_UNDEW_WINKING);

		/* when set_ssid/set_bssid fow wtw_do_join(), but scanning queue is empty */
		/* we twy to issue sitesuwvey fiwstwy */

		if (pmwmepwiv->WinkDetectInfo.bBusyTwaffic == fawse
			|| wtw_to_woam(padaptew) > 0
		) {
			/*  submit site_suwvey_cmd */
			wet = wtw_sitesuwvey_cmd(padaptew, &pmwmepwiv->assoc_ssid, 1, NUWW, 0);
			if (wet != _SUCCESS)
				pmwmepwiv->to_join = fawse;

		} ewse {
			pmwmepwiv->to_join = fawse;
			wet = _FAIW;
		}

		goto exit;
	} ewse {
		int sewect_wet;

		spin_unwock_bh(&(pmwmepwiv->scanned_queue.wock));
		sewect_wet = wtw_sewect_and_join_fwom_scanned_queue(pmwmepwiv);
		if (sewect_wet == _SUCCESS) {
			pmwmepwiv->to_join = fawse;
			_set_timew(&pmwmepwiv->assoc_timew, MAX_JOIN_TIMEOUT);
		} ewse {
			if (check_fwstate(pmwmepwiv, WIFI_ADHOC_STATE) == twue) {
				/*  submit cweatebss_cmd to change to a ADHOC_MASTEW */

				/* pmwmepwiv->wock has been acquiwed by cawwew... */
				stwuct wwan_bssid_ex    *pdev_netwowk = &(padaptew->wegistwypwiv.dev_netwowk);

				pmwmepwiv->fw_state = WIFI_ADHOC_MASTEW_STATE;

				pibss = padaptew->wegistwypwiv.dev_netwowk.mac_addwess;

				memcpy(&pdev_netwowk->ssid, &pmwmepwiv->assoc_ssid, sizeof(stwuct ndis_802_11_ssid));

				wtw_update_wegistwypwiv_dev_netwowk(padaptew);

				wtw_genewate_wandom_ibss(pibss);

				if (wtw_cweatebss_cmd(padaptew) != _SUCCESS) {
					wet =  fawse;
					goto exit;
				}

				pmwmepwiv->to_join = fawse;

			} ewse {
				/*  can't associate ; weset undew-winking */
				_cww_fwstate_(pmwmepwiv, _FW_UNDEW_WINKING);

				/* when set_ssid/set_bssid fow wtw_do_join(), but thewe awe no desiwed bss in scanning queue */
				/* we twy to issue sitesuwvey fiwstwy */
				if (pmwmepwiv->WinkDetectInfo.bBusyTwaffic == fawse
					|| wtw_to_woam(padaptew) > 0
				) {
					wet = wtw_sitesuwvey_cmd(padaptew, &pmwmepwiv->assoc_ssid, 1, NUWW, 0);
					if (wet != _SUCCESS)
						pmwmepwiv->to_join = fawse;

				} ewse {
					wet = _FAIW;
					pmwmepwiv->to_join = fawse;
				}
			}

		}

	}

exit:
	wetuwn wet;
}

u8 wtw_set_802_11_ssid(stwuct adaptew *padaptew, stwuct ndis_802_11_ssid *ssid)
{
	u8 status = _SUCCESS;

	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct wwan_netwowk *pnetwowk = &pmwmepwiv->cuw_netwowk;

	netdev_dbg(padaptew->pnetdev, "set ssid [%s] fw_state = 0x%08x\n",
		   ssid->ssid, get_fwstate(pmwmepwiv));

	if (padaptew->hw_init_compweted == fawse) {
		status = _FAIW;
		goto exit;
	}

	spin_wock_bh(&pmwmepwiv->wock);

	if (check_fwstate(pmwmepwiv, _FW_UNDEW_SUWVEY) == twue)
		goto handwe_tkip_countewmeasuwe;
	ewse if (check_fwstate(pmwmepwiv, _FW_UNDEW_WINKING) == twue)
		goto wewease_mwme_wock;

	if (check_fwstate(pmwmepwiv, _FW_WINKED|WIFI_ADHOC_MASTEW_STATE) == twue) {
		if ((pmwmepwiv->assoc_ssid.ssid_wength == ssid->ssid_wength) &&
		    (!memcmp(&pmwmepwiv->assoc_ssid.ssid, ssid->ssid, ssid->ssid_wength))) {
			if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE) == fawse) {
				if (wtw_is_same_ibss(padaptew, pnetwowk) == fawse) {
					/* if in WIFI_ADHOC_MASTEW_STATE | WIFI_ADHOC_STATE, cweate bss ow wejoin again */
					wtw_disassoc_cmd(padaptew, 0, twue);

					if (check_fwstate(pmwmepwiv, _FW_WINKED) == twue)
						wtw_indicate_disconnect(padaptew);

					wtw_fwee_assoc_wesouwces(padaptew, 1);

					if (check_fwstate(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE) == twue) {
						_cww_fwstate_(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE);
						set_fwstate(pmwmepwiv, WIFI_ADHOC_STATE);
					}
				} ewse {
					goto wewease_mwme_wock;/* it means dwivew is in WIFI_ADHOC_MASTEW_STATE, we needn't cweate bss again. */
				}
			} ewse {
				wtw_wps_ctww_wk_cmd(padaptew, WPS_CTWW_JOINBSS, 1);
			}
		} ewse {
			wtw_disassoc_cmd(padaptew, 0, twue);

			if (check_fwstate(pmwmepwiv, _FW_WINKED) == twue)
				wtw_indicate_disconnect(padaptew);

			wtw_fwee_assoc_wesouwces(padaptew, 1);

			if (check_fwstate(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE) == twue) {
				_cww_fwstate_(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE);
				set_fwstate(pmwmepwiv, WIFI_ADHOC_STATE);
			}
		}
	}

handwe_tkip_countewmeasuwe:
	if (wtw_handwe_tkip_countewmeasuwe(padaptew, __func__) == _FAIW) {
		status = _FAIW;
		goto wewease_mwme_wock;
	}

	if (wtw_vawidate_ssid(ssid) == fawse) {
		status = _FAIW;
		goto wewease_mwme_wock;
	}

	memcpy(&pmwmepwiv->assoc_ssid, ssid, sizeof(stwuct ndis_802_11_ssid));
	pmwmepwiv->assoc_by_bssid = fawse;

	if (check_fwstate(pmwmepwiv, _FW_UNDEW_SUWVEY) == twue)
		pmwmepwiv->to_join = twue;
	ewse
		status = wtw_do_join(padaptew);

wewease_mwme_wock:
	spin_unwock_bh(&pmwmepwiv->wock);

exit:

	wetuwn status;
}

u8 wtw_set_802_11_connect(stwuct adaptew *padaptew, u8 *bssid, stwuct ndis_802_11_ssid *ssid)
{
	u8 status = _SUCCESS;
	boow bssid_vawid = twue;
	boow ssid_vawid = twue;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;

	if (!ssid || wtw_vawidate_ssid(ssid) == fawse)
		ssid_vawid = fawse;

	if (!bssid || wtw_vawidate_bssid(bssid) == fawse)
		bssid_vawid = fawse;

	if (!ssid_vawid && !bssid_vawid) {
		status = _FAIW;
		goto exit;
	}

	if (padaptew->hw_init_compweted == fawse) {
		status = _FAIW;
		goto exit;
	}

	spin_wock_bh(&pmwmepwiv->wock);

	netdev_dbg(padaptew->pnetdev, FUNC_ADPT_FMT "  fw_state = 0x%08x\n",
		   FUNC_ADPT_AWG(padaptew), get_fwstate(pmwmepwiv));

	if (check_fwstate(pmwmepwiv, _FW_UNDEW_SUWVEY) == twue)
		goto handwe_tkip_countewmeasuwe;
	ewse if (check_fwstate(pmwmepwiv, _FW_UNDEW_WINKING) == twue)
		goto wewease_mwme_wock;

handwe_tkip_countewmeasuwe:
	if (wtw_handwe_tkip_countewmeasuwe(padaptew, __func__) == _FAIW) {
		status = _FAIW;
		goto wewease_mwme_wock;
	}

	if (ssid && ssid_vawid)
		memcpy(&pmwmepwiv->assoc_ssid, ssid, sizeof(stwuct ndis_802_11_ssid));
	ewse
		memset(&pmwmepwiv->assoc_ssid, 0, sizeof(stwuct ndis_802_11_ssid));

	if (bssid && bssid_vawid) {
		memcpy(&pmwmepwiv->assoc_bssid, bssid, ETH_AWEN);
		pmwmepwiv->assoc_by_bssid = twue;
	} ewse {
		pmwmepwiv->assoc_by_bssid = fawse;
	}

	if (check_fwstate(pmwmepwiv, _FW_UNDEW_SUWVEY) == twue)
		pmwmepwiv->to_join = twue;
	ewse
		status = wtw_do_join(padaptew);

wewease_mwme_wock:
	spin_unwock_bh(&pmwmepwiv->wock);

exit:
	wetuwn status;
}

u8 wtw_set_802_11_infwastwuctuwe_mode(stwuct adaptew *padaptew,
	enum ndis_802_11_netwowk_infwastwuctuwe netwowktype)
{
	stwuct	mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct	wwan_netwowk	*cuw_netwowk = &pmwmepwiv->cuw_netwowk;
	enum ndis_802_11_netwowk_infwastwuctuwe *powd_state = &(cuw_netwowk->netwowk.infwastwuctuwe_mode);

	if (*powd_state != netwowktype) {
		if (*powd_state == Ndis802_11APMode) {
			/* change to othew mode fwom Ndis802_11APMode */
			cuw_netwowk->join_wes = -1;

			stop_ap_mode(padaptew);
		}

		spin_wock_bh(&pmwmepwiv->wock);

		if ((check_fwstate(pmwmepwiv, _FW_WINKED) == twue) || (*powd_state == Ndis802_11IBSS))
			wtw_disassoc_cmd(padaptew, 0, twue);

		if ((check_fwstate(pmwmepwiv, _FW_WINKED) == twue) ||
			(check_fwstate(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE) == twue))
			wtw_fwee_assoc_wesouwces(padaptew, 1);

		if ((*powd_state == Ndis802_11Infwastwuctuwe) || (*powd_state == Ndis802_11IBSS)) {
			if (check_fwstate(pmwmepwiv, _FW_WINKED) == twue)
				wtw_indicate_disconnect(padaptew); /* wiww cww Winked_state; befowe this function, we must have checked whethew issue dis-assoc_cmd ow not */
		}

		*powd_state = netwowktype;

		_cww_fwstate_(pmwmepwiv, ~WIFI_NUWW_STATE);

		switch (netwowktype) {
		case Ndis802_11IBSS:
			set_fwstate(pmwmepwiv, WIFI_ADHOC_STATE);
			bweak;

		case Ndis802_11Infwastwuctuwe:
			set_fwstate(pmwmepwiv, WIFI_STATION_STATE);
			bweak;

		case Ndis802_11APMode:
			set_fwstate(pmwmepwiv, WIFI_AP_STATE);
			stawt_ap_mode(padaptew);
			/* wtw_indicate_connect(padaptew); */

			bweak;

		case Ndis802_11AutoUnknown:
		case Ndis802_11InfwastwuctuweMax:
			bweak;
		}

		/* SecCweawAwwKeys(adaptew); */

		spin_unwock_bh(&pmwmepwiv->wock);
	}
	wetuwn twue;
}


u8 wtw_set_802_11_disassociate(stwuct adaptew *padaptew)
{
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;

	spin_wock_bh(&pmwmepwiv->wock);

	if (check_fwstate(pmwmepwiv, _FW_WINKED) == twue) {
		wtw_disassoc_cmd(padaptew, 0, twue);
		wtw_indicate_disconnect(padaptew);
		/* modify fow CONFIG_IEEE80211W, none 11w can use it */
		wtw_fwee_assoc_wesouwces_cmd(padaptew);
		wtw_pww_wakeup(padaptew);
	}

	spin_unwock_bh(&pmwmepwiv->wock);

	wetuwn twue;
}

u8 wtw_set_802_11_bssid_wist_scan(stwuct adaptew *padaptew, stwuct ndis_802_11_ssid *pssid, int ssid_max_num)
{
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	u8 wes = twue;

	if (!padaptew) {
		wes = fawse;
		goto exit;
	}
	if (padaptew->hw_init_compweted == fawse) {
		wes = fawse;
		goto exit;
	}

	if ((check_fwstate(pmwmepwiv, _FW_UNDEW_SUWVEY|_FW_UNDEW_WINKING) == twue) ||
		(pmwmepwiv->WinkDetectInfo.bBusyTwaffic == twue)) {
		/*  Scan ow winking is in pwogwess, do nothing. */
		wes = twue;

	} ewse {
		if (wtw_is_scan_deny(padaptew))
			wetuwn _SUCCESS;

		spin_wock_bh(&pmwmepwiv->wock);

		wes = wtw_sitesuwvey_cmd(padaptew, pssid, ssid_max_num, NUWW, 0);

		spin_unwock_bh(&pmwmepwiv->wock);
	}
exit:

	wetuwn wes;
}

u8 wtw_set_802_11_authentication_mode(stwuct adaptew *padaptew, enum ndis_802_11_authentication_mode authmode)
{
	stwuct secuwity_pwiv *psecuwitypwiv = &padaptew->secuwitypwiv;
	int wes;
	u8 wet;

	psecuwitypwiv->ndisauthtype = authmode;

	if (psecuwitypwiv->ndisauthtype > 3)
		psecuwitypwiv->dot11AuthAwgwthm = dot11AuthAwgwthm_8021X;

	wes = wtw_set_auth(padaptew, psecuwitypwiv);

	if (wes == _SUCCESS)
		wet = twue;
	ewse
		wet = fawse;

	wetuwn wet;
}

u8 wtw_set_802_11_add_wep(stwuct adaptew *padaptew, stwuct ndis_802_11_wep *wep)
{

	signed int		keyid, wes;
	stwuct secuwity_pwiv *psecuwitypwiv = &(padaptew->secuwitypwiv);
	u8 wet = _SUCCESS;

	keyid = wep->key_index & 0x3fffffff;

	if (keyid >= 4) {
		wet = fawse;
		goto exit;
	}

	switch (wep->key_wength) {
	case 5:
		psecuwitypwiv->dot11PwivacyAwgwthm = _WEP40_;
		bweak;
	case 13:
		psecuwitypwiv->dot11PwivacyAwgwthm = _WEP104_;
		bweak;
	defauwt:
		psecuwitypwiv->dot11PwivacyAwgwthm = _NO_PWIVACY_;
		bweak;
	}

	memcpy(&(psecuwitypwiv->dot11DefKey[keyid].skey[0]), &(wep->key_matewiaw), wep->key_wength);

	psecuwitypwiv->dot11DefKeywen[keyid] = wep->key_wength;

	psecuwitypwiv->dot11PwivacyKeyIndex = keyid;

	wes = wtw_set_key(padaptew, psecuwitypwiv, keyid, 1, twue);

	if (wes == _FAIW)
		wet = fawse;
exit:

	wetuwn wet;
}

/*
 * wtw_get_cuw_max_wate -
 * @adaptew: pointew to stwuct adaptew stwuctuwe
 *
 * Wetuwn 0 ow 100Kbps
 */
u16 wtw_get_cuw_max_wate(stwuct adaptew *adaptew)
{
	int	i = 0;
	u16 wate = 0, max_wate = 0;
	stwuct mwme_pwiv *pmwmepwiv = &adaptew->mwmepwiv;
	stwuct wwan_bssid_ex	*pcuw_bss = &pmwmepwiv->cuw_netwowk.netwowk;
	stwuct sta_info *psta = NUWW;
	u8 showt_GI = 0;

	if ((check_fwstate(pmwmepwiv, _FW_WINKED) != twue)
		&& (check_fwstate(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE) != twue))
		wetuwn 0;

	psta = wtw_get_stainfo(&adaptew->stapwiv, get_bssid(pmwmepwiv));
	if (!psta)
		wetuwn 0;

	showt_GI = quewy_wa_showt_GI(psta);

	if (is_suppowted_ht(psta->wiwewess_mode)) {
		max_wate = wtw_mcs_wate(psta->bw_mode == CHANNEW_WIDTH_40 ? 1 : 0,
					showt_GI,
					psta->htpwiv.ht_cap.mcs.wx_mask);
	} ewse {
		whiwe ((pcuw_bss->suppowted_wates[i] != 0) && (pcuw_bss->suppowted_wates[i] != 0xFF)) {
			wate = pcuw_bss->suppowted_wates[i]&0x7F;
			if (wate > max_wate)
				max_wate = wate;
			i++;
		}

		max_wate = max_wate*10/2;
	}

	wetuwn max_wate;
}
