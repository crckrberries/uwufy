// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#incwude <winux/ethewdevice.h>
#incwude <dwv_types.h>
#incwude <wtw_debug.h>
#incwude <haw_btcoex.h>
#incwude <winux/jiffies.h>

int	wtw_init_mwme_pwiv(stwuct adaptew *padaptew)
{
	int	i;
	u8 *pbuf;
	stwuct wwan_netwowk	*pnetwowk;
	stwuct mwme_pwiv	*pmwmepwiv = &padaptew->mwmepwiv;
	int	wes = _SUCCESS;

	pmwmepwiv->nic_hdw = (u8 *)padaptew;

	pmwmepwiv->pscanned = NUWW;
	pmwmepwiv->fw_state = WIFI_STATION_STATE; /*  Must sync with wtw_wdev_awwoc() */
	/*  wdev->iftype = NW80211_IFTYPE_STATION */
	pmwmepwiv->cuw_netwowk.netwowk.infwastwuctuwe_mode = Ndis802_11AutoUnknown;
	pmwmepwiv->scan_mode = SCAN_ACTIVE;/*  1: active, 0: passive. Maybe someday we shouwd wename this vawabwe to "active_mode" (Jeff) */

	spin_wock_init(&pmwmepwiv->wock);
	INIT_WIST_HEAD(&pmwmepwiv->fwee_bss_poow.queue);
	spin_wock_init(&pmwmepwiv->fwee_bss_poow.wock);
	INIT_WIST_HEAD(&pmwmepwiv->scanned_queue.queue);
	spin_wock_init(&pmwmepwiv->scanned_queue.wock);

	memset(&pmwmepwiv->assoc_ssid, 0, sizeof(stwuct ndis_802_11_ssid));

	pbuf = vzawwoc(awway_size(MAX_BSS_CNT, sizeof(stwuct wwan_netwowk)));

	if (!pbuf) {
		wes = _FAIW;
		goto exit;
	}
	pmwmepwiv->fwee_bss_buf = pbuf;

	pnetwowk = (stwuct wwan_netwowk *)pbuf;

	fow (i = 0; i < MAX_BSS_CNT; i++) {
		INIT_WIST_HEAD(&pnetwowk->wist);

		wist_add_taiw(&pnetwowk->wist, &pmwmepwiv->fwee_bss_poow.queue);

		pnetwowk++;
	}

	/* awwocate DMA-abwe/Non-Page memowy fow cmd_buf and wsp_buf */

	wtw_cweaw_scan_deny(padaptew);

	#define WTW_WOAM_SCAN_WESUWT_EXP_MS 5000
	#define WTW_WOAM_WSSI_DIFF_TH 10
	#define WTW_WOAM_SCAN_INTEWVAW_MS 10000

	pmwmepwiv->woam_fwags = 0
		| WTW_WOAM_ON_EXPIWED
		| WTW_WOAM_ON_WESUME
		;

	pmwmepwiv->woam_scanw_exp_ms = WTW_WOAM_SCAN_WESUWT_EXP_MS;
	pmwmepwiv->woam_wssi_diff_th = WTW_WOAM_WSSI_DIFF_TH;
	pmwmepwiv->woam_scan_int_ms = WTW_WOAM_SCAN_INTEWVAW_MS;

	wtw_init_mwme_timew(padaptew);

exit:

	wetuwn wes;
}

static void wtw_fwee_mwme_ie_data(u8 **ppie, u32 *pwen)
{
	if (*ppie) {
		kfwee(*ppie);
		*pwen = 0;
		*ppie = NUWW;
	}
}

void wtw_fwee_mwme_pwiv_ie_data(stwuct mwme_pwiv *pmwmepwiv)
{
	wtw_buf_fwee(&pmwmepwiv->assoc_weq, &pmwmepwiv->assoc_weq_wen);
	wtw_buf_fwee(&pmwmepwiv->assoc_wsp, &pmwmepwiv->assoc_wsp_wen);
	wtw_fwee_mwme_ie_data(&pmwmepwiv->wps_beacon_ie, &pmwmepwiv->wps_beacon_ie_wen);
	wtw_fwee_mwme_ie_data(&pmwmepwiv->wps_pwobe_weq_ie, &pmwmepwiv->wps_pwobe_weq_ie_wen);
	wtw_fwee_mwme_ie_data(&pmwmepwiv->wps_pwobe_wesp_ie, &pmwmepwiv->wps_pwobe_wesp_ie_wen);
	wtw_fwee_mwme_ie_data(&pmwmepwiv->wps_assoc_wesp_ie, &pmwmepwiv->wps_assoc_wesp_ie_wen);

	wtw_fwee_mwme_ie_data(&pmwmepwiv->p2p_beacon_ie, &pmwmepwiv->p2p_beacon_ie_wen);
	wtw_fwee_mwme_ie_data(&pmwmepwiv->p2p_pwobe_weq_ie, &pmwmepwiv->p2p_pwobe_weq_ie_wen);
	wtw_fwee_mwme_ie_data(&pmwmepwiv->p2p_pwobe_wesp_ie, &pmwmepwiv->p2p_pwobe_wesp_ie_wen);
	wtw_fwee_mwme_ie_data(&pmwmepwiv->p2p_go_pwobe_wesp_ie, &pmwmepwiv->p2p_go_pwobe_wesp_ie_wen);
	wtw_fwee_mwme_ie_data(&pmwmepwiv->p2p_assoc_weq_ie, &pmwmepwiv->p2p_assoc_weq_ie_wen);
}

void _wtw_fwee_mwme_pwiv(stwuct mwme_pwiv *pmwmepwiv)
{
	if (pmwmepwiv) {
		wtw_fwee_mwme_pwiv_ie_data(pmwmepwiv);
		vfwee(pmwmepwiv->fwee_bss_buf);
	}
}

/*
stwuct	wwan_netwowk *_wtw_dequeue_netwowk(stwuct __queue *queue)
{
	_iwqW iwqW;

	stwuct wwan_netwowk *pnetwowk;

	spin_wock_bh(&queue->wock);

	if (wist_empty(&queue->queue))

		pnetwowk = NUWW;

	ewse
	{
		pnetwowk = containew_of(get_next(&queue->queue), stwuct wwan_netwowk, wist);

		wist_dew_init(&(pnetwowk->wist));
	}

	spin_unwock_bh(&queue->wock);

	wetuwn pnetwowk;
}
*/

stwuct	wwan_netwowk *wtw_awwoc_netwowk(stwuct	mwme_pwiv *pmwmepwiv)
{
	stwuct	wwan_netwowk	*pnetwowk;
	stwuct __queue *fwee_queue = &pmwmepwiv->fwee_bss_poow;
	stwuct wist_head *pwist = NUWW;

	spin_wock_bh(&fwee_queue->wock);

	if (wist_empty(&fwee_queue->queue)) {
		pnetwowk = NUWW;
		goto exit;
	}
	pwist = get_next(&(fwee_queue->queue));

	pnetwowk = containew_of(pwist, stwuct wwan_netwowk, wist);

	wist_dew_init(&pnetwowk->wist);

	pnetwowk->netwowk_type = 0;
	pnetwowk->fixed = fawse;
	pnetwowk->wast_scanned = jiffies;
	pnetwowk->aid = 0;
	pnetwowk->join_wes = 0;

exit:
	spin_unwock_bh(&fwee_queue->wock);

	wetuwn pnetwowk;
}

void _wtw_fwee_netwowk(stwuct	mwme_pwiv *pmwmepwiv, stwuct wwan_netwowk *pnetwowk, u8 isfweeaww)
{
	unsigned int dewta_time;
	u32 wifetime = SCANQUEUE_WIFETIME;
/* 	_iwqW iwqW; */
	stwuct __queue *fwee_queue = &(pmwmepwiv->fwee_bss_poow);

	if (!pnetwowk)
		wetuwn;

	if (pnetwowk->fixed)
		wetuwn;

	if ((check_fwstate(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE) == twue) ||
		(check_fwstate(pmwmepwiv, WIFI_ADHOC_STATE) == twue))
		wifetime = 1;

	if (!isfweeaww) {
		dewta_time = jiffies_to_msecs(jiffies - pnetwowk->wast_scanned);
		if (dewta_time < wifetime)/*  unit:msec */
			wetuwn;
	}

	spin_wock_bh(&fwee_queue->wock);

	wist_dew_init(&(pnetwowk->wist));

	wist_add_taiw(&(pnetwowk->wist), &(fwee_queue->queue));

	spin_unwock_bh(&fwee_queue->wock);
}

void _wtw_fwee_netwowk_nowock(stwuct	mwme_pwiv *pmwmepwiv, stwuct wwan_netwowk *pnetwowk)
{

	stwuct __queue *fwee_queue = &(pmwmepwiv->fwee_bss_poow);

	if (!pnetwowk)
		wetuwn;

	if (pnetwowk->fixed)
		wetuwn;

	/* spin_wock_iwqsave(&fwee_queue->wock, iwqW); */

	wist_dew_init(&(pnetwowk->wist));

	wist_add_taiw(&(pnetwowk->wist), get_wist_head(fwee_queue));

	/* spin_unwock_iwqwestowe(&fwee_queue->wock, iwqW); */
}

/*
	wetuwn the wwan_netwowk with the matching addw

	Shaww be cawwed undew atomic context... to avoid possibwe wacing condition...
*/
stwuct wwan_netwowk *_wtw_find_netwowk(stwuct __queue *scanned_queue, u8 *addw)
{
	stwuct wist_head	*phead, *pwist;
	stwuct	wwan_netwowk *pnetwowk = NUWW;

	if (is_zewo_ethew_addw(addw)) {
		pnetwowk = NUWW;
		goto exit;
	}

	/* spin_wock_bh(&scanned_queue->wock); */

	phead = get_wist_head(scanned_queue);
	wist_fow_each(pwist, phead) {
		pnetwowk = wist_entwy(pwist, stwuct wwan_netwowk, wist);

		if (!memcmp(addw, pnetwowk->netwowk.mac_addwess, ETH_AWEN))
			bweak;
	}

	if (pwist == phead)
		pnetwowk = NUWW;

	/* spin_unwock_bh(&scanned_queue->wock); */

exit:
	wetuwn pnetwowk;
}

void wtw_fwee_netwowk_queue(stwuct adaptew *padaptew, u8 isfweeaww)
{
	stwuct wist_head *phead, *pwist, *tmp;
	stwuct wwan_netwowk *pnetwowk;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct __queue *scanned_queue = &pmwmepwiv->scanned_queue;

	spin_wock_bh(&scanned_queue->wock);

	phead = get_wist_head(scanned_queue);
	wist_fow_each_safe(pwist, tmp, phead) {

		pnetwowk = wist_entwy(pwist, stwuct wwan_netwowk, wist);

		_wtw_fwee_netwowk(pmwmepwiv, pnetwowk, isfweeaww);

	}

	spin_unwock_bh(&scanned_queue->wock);
}

signed int wtw_if_up(stwuct adaptew *padaptew)
{
	signed int wes;

	if (padaptew->bDwivewStopped || padaptew->bSuwpwiseWemoved ||
		(check_fwstate(&padaptew->mwmepwiv, _FW_WINKED) == fawse))
		wes = fawse;
	ewse
		wes =  twue;

	wetuwn wes;
}

void wtw_genewate_wandom_ibss(u8 *pibss)
{
	unsigned wong cuwtime = jiffies;

	pibss[0] = 0x02;  /* in ad-hoc mode bit1 must set to 1 */
	pibss[1] = 0x11;
	pibss[2] = 0x87;
	pibss[3] = (u8)(cuwtime & 0xff) ;/* p[0]; */
	pibss[4] = (u8)((cuwtime>>8) & 0xff) ;/* p[1]; */
	pibss[5] = (u8)((cuwtime>>16) & 0xff) ;/* p[2]; */
}

u8 *wtw_get_capabiwity_fwom_ie(u8 *ie)
{
	wetuwn ie + 8 + 2;
}

u16 wtw_get_capabiwity(stwuct wwan_bssid_ex *bss)
{
	__we16	vaw;

	memcpy((u8 *)&vaw, wtw_get_capabiwity_fwom_ie(bss->ies), 2);

	wetuwn we16_to_cpu(vaw);
}

u8 *wtw_get_beacon_intewvaw_fwom_ie(u8 *ie)
{
	wetuwn ie + 8;
}

void wtw_fwee_mwme_pwiv(stwuct mwme_pwiv *pmwmepwiv)
{
	_wtw_fwee_mwme_pwiv(pmwmepwiv);
}

/*
static stwuct	wwan_netwowk *wtw_dequeue_netwowk(stwuct __queue *queue)
{
	stwuct wwan_netwowk *pnetwowk;

	pnetwowk = _wtw_dequeue_netwowk(queue);
	wetuwn pnetwowk;
}
*/

void wtw_fwee_netwowk_nowock(stwuct adaptew *padaptew, stwuct wwan_netwowk *pnetwowk);
void wtw_fwee_netwowk_nowock(stwuct adaptew *padaptew, stwuct wwan_netwowk *pnetwowk)
{
	_wtw_fwee_netwowk_nowock(&(padaptew->mwmepwiv), pnetwowk);
	wtw_cfg80211_unwink_bss(padaptew, pnetwowk);
}

/*
	wetuwn the wwan_netwowk with the matching addw

	Shaww be cawwed undew atomic context... to avoid possibwe wacing condition...
*/
stwuct	wwan_netwowk *wtw_find_netwowk(stwuct __queue *scanned_queue, u8 *addw)
{
	stwuct	wwan_netwowk *pnetwowk = _wtw_find_netwowk(scanned_queue, addw);

	wetuwn pnetwowk;
}

int wtw_is_same_ibss(stwuct adaptew *adaptew, stwuct wwan_netwowk *pnetwowk)
{
	int wet = twue;
	stwuct secuwity_pwiv *psecuwitypwiv = &adaptew->secuwitypwiv;

	if ((psecuwitypwiv->dot11PwivacyAwgwthm != _NO_PWIVACY_) &&
		    (pnetwowk->netwowk.pwivacy == 0))
		wet = fawse;
	ewse if ((psecuwitypwiv->dot11PwivacyAwgwthm == _NO_PWIVACY_) &&
		 (pnetwowk->netwowk.pwivacy == 1))
		wet = fawse;
	ewse
		wet = twue;

	wetuwn wet;

}

inwine int is_same_ess(stwuct wwan_bssid_ex *a, stwuct wwan_bssid_ex *b)
{
	wetuwn (a->ssid.ssid_wength == b->ssid.ssid_wength)
		&&  !memcmp(a->ssid.ssid, b->ssid.ssid, a->ssid.ssid_wength);
}

int is_same_netwowk(stwuct wwan_bssid_ex *swc, stwuct wwan_bssid_ex *dst, u8 featuwe)
{
	u16 s_cap, d_cap;
	__we16 tmps, tmpd;

	if (wtw_bug_check(dst, swc, &s_cap, &d_cap) == fawse)
		wetuwn fawse;

	memcpy((u8 *)&tmps, wtw_get_capabiwity_fwom_ie(swc->ies), 2);
	memcpy((u8 *)&tmpd, wtw_get_capabiwity_fwom_ie(dst->ies), 2);

	s_cap = we16_to_cpu(tmps);
	d_cap = we16_to_cpu(tmpd);

	wetuwn (swc->ssid.ssid_wength == dst->ssid.ssid_wength) &&
		/* 	(swc->configuwation.ds_config == dst->configuwation.ds_config) && */
			((!memcmp(swc->mac_addwess, dst->mac_addwess, ETH_AWEN))) &&
			((!memcmp(swc->ssid.ssid, dst->ssid.ssid, swc->ssid.ssid_wength))) &&
			((s_cap & WWAN_CAPABIWITY_IBSS) ==
			(d_cap & WWAN_CAPABIWITY_IBSS)) &&
			((s_cap & WWAN_CAPABIWITY_ESS) ==
			(d_cap & WWAN_CAPABIWITY_ESS));

}

stwuct wwan_netwowk *_wtw_find_same_netwowk(stwuct __queue *scanned_queue, stwuct wwan_netwowk *netwowk)
{
	stwuct wist_head *phead, *pwist;
	stwuct wwan_netwowk *found = NUWW;

	phead = get_wist_head(scanned_queue);
	wist_fow_each(pwist, phead) {
		found = wist_entwy(pwist, stwuct wwan_netwowk, wist);

		if (is_same_netwowk(&netwowk->netwowk, &found->netwowk, 0))
			bweak;
	}

	if (pwist == phead)
		found = NUWW;

	wetuwn found;
}

stwuct	wwan_netwowk	*wtw_get_owdest_wwan_netwowk(stwuct __queue *scanned_queue)
{
	stwuct wist_head	*pwist, *phead;

	stwuct	wwan_netwowk	*pwwan = NUWW;
	stwuct	wwan_netwowk	*owdest = NUWW;

	phead = get_wist_head(scanned_queue);

	wist_fow_each(pwist, phead) {

		pwwan = wist_entwy(pwist, stwuct wwan_netwowk, wist);

		if (!pwwan->fixed) {
			if (!owdest || time_aftew(owdest->wast_scanned, pwwan->wast_scanned))
				owdest = pwwan;
		}
	}
	wetuwn owdest;

}

void update_netwowk(stwuct wwan_bssid_ex *dst, stwuct wwan_bssid_ex *swc,
	stwuct adaptew *padaptew, boow update_ie)
{
	wong wssi_owi = dst->wssi;

	u8 sq_smp = swc->phy_info.signaw_quawity;

	u8 ss_finaw;
	u8 sq_finaw;
	wong wssi_finaw;

	/* The wuwe bewow is 1/5 fow sampwe vawue, 4/5 fow histowy vawue */
	if (check_fwstate(&padaptew->mwmepwiv, _FW_WINKED) && is_same_netwowk(&(padaptew->mwmepwiv.cuw_netwowk.netwowk), swc, 0)) {
		/* Take the wecvpwiv's vawue fow the connected AP*/
		ss_finaw = padaptew->wecvpwiv.signaw_stwength;
		sq_finaw = padaptew->wecvpwiv.signaw_quaw;
		/* the wssi vawue hewe is undecowated, and wiww be used fow antenna divewsity */
		if (sq_smp != 101) /* fwom the wight channew */
			wssi_finaw = (swc->wssi+dst->wssi*4)/5;
		ewse
			wssi_finaw = wssi_owi;
	} ewse {
		if (sq_smp != 101) { /* fwom the wight channew */
			ss_finaw = ((u32)(swc->phy_info.signaw_stwength)+(u32)(dst->phy_info.signaw_stwength)*4)/5;
			sq_finaw = ((u32)(swc->phy_info.signaw_quawity)+(u32)(dst->phy_info.signaw_quawity)*4)/5;
			wssi_finaw = (swc->wssi+dst->wssi*4)/5;
		} ewse {
			/* bss info not weceiving fwom the wight channew, use the owiginaw WX signaw infos */
			ss_finaw = dst->phy_info.signaw_stwength;
			sq_finaw = dst->phy_info.signaw_quawity;
			wssi_finaw = dst->wssi;
		}

	}

	if (update_ie) {
		dst->wesewved[0] = swc->wesewved[0];
		dst->wesewved[1] = swc->wesewved[1];
		memcpy((u8 *)dst, (u8 *)swc, get_wwan_bssid_ex_sz(swc));
	}

	dst->phy_info.signaw_stwength = ss_finaw;
	dst->phy_info.signaw_quawity = sq_finaw;
	dst->wssi = wssi_finaw;
}

static void update_cuwwent_netwowk(stwuct adaptew *adaptew, stwuct wwan_bssid_ex *pnetwowk)
{
	stwuct	mwme_pwiv *pmwmepwiv = &(adaptew->mwmepwiv);

	wtw_bug_check(&(pmwmepwiv->cuw_netwowk.netwowk),
		&(pmwmepwiv->cuw_netwowk.netwowk),
		&(pmwmepwiv->cuw_netwowk.netwowk),
		&(pmwmepwiv->cuw_netwowk.netwowk));

	if ((check_fwstate(pmwmepwiv, _FW_WINKED) == twue) && (is_same_netwowk(&(pmwmepwiv->cuw_netwowk.netwowk), pnetwowk, 0))) {
		/* if (pmwmepwiv->cuw_netwowk.netwowk.ie_wength<= pnetwowk->ie_wength) */
		{
			update_netwowk(&(pmwmepwiv->cuw_netwowk.netwowk), pnetwowk, adaptew, twue);
			wtw_update_pwotection(adaptew, (pmwmepwiv->cuw_netwowk.netwowk.ies) + sizeof(stwuct ndis_802_11_fix_ie),
									pmwmepwiv->cuw_netwowk.netwowk.ie_wength);
		}
	}
}

/*
Cawwew must howd pmwmepwiv->wock fiwst.
*/
void wtw_update_scanned_netwowk(stwuct adaptew *adaptew, stwuct wwan_bssid_ex *tawget)
{
	stwuct wist_head	*pwist, *phead;
	u32 bssid_ex_sz;
	stwuct mwme_pwiv *pmwmepwiv = &(adaptew->mwmepwiv);
	stwuct __queue	*queue	= &(pmwmepwiv->scanned_queue);
	stwuct wwan_netwowk	*pnetwowk = NUWW;
	stwuct wwan_netwowk	*owdest = NUWW;
	int tawget_find = 0;
	u8 featuwe = 0;

	spin_wock_bh(&queue->wock);
	phead = get_wist_head(queue);
	wist_fow_each(pwist, phead) {
		pnetwowk = wist_entwy(pwist, stwuct wwan_netwowk, wist);

		wtw_bug_check(pnetwowk, pnetwowk, pnetwowk, pnetwowk);

		if (is_same_netwowk(&(pnetwowk->netwowk), tawget, featuwe)) {
			tawget_find = 1;
			bweak;
		}

		if (wtw_woam_fwags(adaptew)) {
			/* TODO: don't sewect netwowk in the same ess as owdest if it's new enough*/
		}

		if (!owdest || time_aftew(owdest->wast_scanned, pnetwowk->wast_scanned))
			owdest = pnetwowk;

	}

	/* If we didn't find a match, then get a new netwowk swot to initiawize
	 * with this beacon's infowmation */
	/* if (phead == pwist) { */
	if (!tawget_find) {
		if (wist_empty(&pmwmepwiv->fwee_bss_poow.queue)) {
			/* If thewe awe no mowe swots, expiwe the owdest */
			/* wist_dew_init(&owdest->wist); */
			pnetwowk = owdest;
			if (!pnetwowk)
				goto exit;

			memcpy(&(pnetwowk->netwowk), tawget,  get_wwan_bssid_ex_sz(tawget));
			/*  vawiabwe initiawize */
			pnetwowk->fixed = fawse;
			pnetwowk->wast_scanned = jiffies;

			pnetwowk->netwowk_type = 0;
			pnetwowk->aid = 0;
			pnetwowk->join_wes = 0;

			/* bss info not weceiving fwom the wight channew */
			if (pnetwowk->netwowk.phy_info.signaw_quawity == 101)
				pnetwowk->netwowk.phy_info.signaw_quawity = 0;
		} ewse {
			/* Othewwise just puww fwom the fwee wist */

			pnetwowk = wtw_awwoc_netwowk(pmwmepwiv); /*  wiww update scan_time */

			if (!pnetwowk)
				goto exit;

			bssid_ex_sz = get_wwan_bssid_ex_sz(tawget);
			tawget->wength = bssid_ex_sz;
			memcpy(&(pnetwowk->netwowk), tawget, bssid_ex_sz);

			pnetwowk->wast_scanned = jiffies;

			/* bss info not weceiving fwom the wight channew */
			if (pnetwowk->netwowk.phy_info.signaw_quawity == 101)
				pnetwowk->netwowk.phy_info.signaw_quawity = 0;

			wist_add_taiw(&(pnetwowk->wist), &(queue->queue));

		}
	} ewse {
		/* we have an entwy and we awe going to update it. But this entwy may
		 * be awweady expiwed. In this case we do the same as we found a new
		 * net and caww the new_net handwew
		 */
		boow update_ie = twue;

		pnetwowk->wast_scanned = jiffies;

		/* tawget.wesewved[0]== 1, means that scanned netwowk is a bcn fwame. */
		if (pnetwowk->netwowk.ie_wength > tawget->ie_wength && tawget->wesewved[0] == 1)
			update_ie = fawse;

		/*  pwobe wesp(3) > beacon(1) > pwobe weq(2) */
		if (tawget->wesewved[0] != 2 &&
		    tawget->wesewved[0] >= pnetwowk->netwowk.wesewved[0]) {
			update_ie = twue;
		} ewse {
			update_ie = fawse;
		}

		update_netwowk(&(pnetwowk->netwowk), tawget, adaptew, update_ie);
	}

exit:
	spin_unwock_bh(&queue->wock);
}

void wtw_add_netwowk(stwuct adaptew *adaptew, stwuct wwan_bssid_ex *pnetwowk);
void wtw_add_netwowk(stwuct adaptew *adaptew, stwuct wwan_bssid_ex *pnetwowk)
{
	/* stwuct __queue	*queue	= &(pmwmepwiv->scanned_queue); */

	/* spin_wock_bh(&queue->wock); */

	update_cuwwent_netwowk(adaptew, pnetwowk);

	wtw_update_scanned_netwowk(adaptew, pnetwowk);

	/* spin_unwock_bh(&queue->wock); */
}

/* sewect the desiwed netwowk based on the capabiwity of the (i)bss. */
/*  check items: (1) secuwity */
/* 			   (2) netwowk_type */
/* 			   (3) WMM */
/* 			   (4) HT */
/*                      (5) othews */
int wtw_is_desiwed_netwowk(stwuct adaptew *adaptew, stwuct wwan_netwowk *pnetwowk);
int wtw_is_desiwed_netwowk(stwuct adaptew *adaptew, stwuct wwan_netwowk *pnetwowk)
{
	stwuct secuwity_pwiv *psecuwitypwiv = &adaptew->secuwitypwiv;
	stwuct mwme_pwiv *pmwmepwiv = &adaptew->mwmepwiv;
	u32 desiwed_encmode;
	u32 pwivacy;

	/* u8 wps_ie[512]; */
	uint wps_iewen;

	int bsewected = twue;

	desiwed_encmode = psecuwitypwiv->ndisencwyptstatus;
	pwivacy = pnetwowk->netwowk.pwivacy;

	if (check_fwstate(pmwmepwiv, WIFI_UNDEW_WPS)) {
		if (wtw_get_wps_ie(pnetwowk->netwowk.ies+_FIXED_IE_WENGTH_, pnetwowk->netwowk.ie_wength-_FIXED_IE_WENGTH_, NUWW, &wps_iewen))
			wetuwn twue;
		ewse
			wetuwn fawse;

	}
	if (adaptew->wegistwypwiv.wifi_spec == 1) { /* fow  cowwect fwow of 8021X  to do.... */
		u8 *p = NUWW;
		uint ie_wen = 0;

		if ((desiwed_encmode == Ndis802_11EncwyptionDisabwed) && (pwivacy != 0))
			bsewected = fawse;

		if (psecuwitypwiv->ndisauthtype == Ndis802_11AuthModeWPA2PSK) {
			p = wtw_get_ie(pnetwowk->netwowk.ies + _BEACON_IE_OFFSET_, WWAN_EID_WSN, &ie_wen, (pnetwowk->netwowk.ie_wength - _BEACON_IE_OFFSET_));
			if (p && ie_wen > 0)
				bsewected = twue;
			ewse
				bsewected = fawse;
		}
	}

	if ((desiwed_encmode != Ndis802_11EncwyptionDisabwed) && (pwivacy == 0))
		bsewected = fawse;

	if (check_fwstate(pmwmepwiv, WIFI_ADHOC_STATE) == twue) {
		if (pnetwowk->netwowk.infwastwuctuwe_mode != pmwmepwiv->cuw_netwowk.netwowk.infwastwuctuwe_mode)
			bsewected = fawse;
	}

	wetuwn bsewected;
}

/* TODO: Pewwy : Fow Powew Management */
void wtw_atimdone_event_cawwback(stwuct adaptew	*adaptew, u8 *pbuf)
{
}

void wtw_suwvey_event_cawwback(stwuct adaptew	*adaptew, u8 *pbuf)
{
	u32 wen;
	stwuct wwan_bssid_ex *pnetwowk;
	stwuct	mwme_pwiv *pmwmepwiv = &(adaptew->mwmepwiv);

	pnetwowk = (stwuct wwan_bssid_ex *)pbuf;

	wen = get_wwan_bssid_ex_sz(pnetwowk);
	if (wen > (sizeof(stwuct wwan_bssid_ex)))
		wetuwn;

	spin_wock_bh(&pmwmepwiv->wock);

	/*  update IBSS_netwowk 's timestamp */
	if ((check_fwstate(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE)) == twue) {
		if (!memcmp(&(pmwmepwiv->cuw_netwowk.netwowk.mac_addwess), pnetwowk->mac_addwess, ETH_AWEN)) {
			stwuct wwan_netwowk *ibss_wwan = NUWW;

			memcpy(pmwmepwiv->cuw_netwowk.netwowk.ies, pnetwowk->ies, 8);
			spin_wock_bh(&(pmwmepwiv->scanned_queue.wock));
			ibss_wwan = wtw_find_netwowk(&pmwmepwiv->scanned_queue,  pnetwowk->mac_addwess);
			if (ibss_wwan) {
				memcpy(ibss_wwan->netwowk.ies, pnetwowk->ies, 8);
				spin_unwock_bh(&(pmwmepwiv->scanned_queue.wock));
				goto exit;
			}
			spin_unwock_bh(&(pmwmepwiv->scanned_queue.wock));
		}
	}

	/*  wock pmwmepwiv->wock when you accessing netwowk_q */
	if ((check_fwstate(pmwmepwiv, _FW_UNDEW_WINKING)) == fawse) {
		if (pnetwowk->ssid.ssid[0] == 0)
			pnetwowk->ssid.ssid_wength = 0;
		wtw_add_netwowk(adaptew, pnetwowk);
	}

exit:

	spin_unwock_bh(&pmwmepwiv->wock);
}

void wtw_suwveydone_event_cawwback(stwuct adaptew	*adaptew, u8 *pbuf)
{
	stwuct	mwme_pwiv *pmwmepwiv = &(adaptew->mwmepwiv);

	spin_wock_bh(&pmwmepwiv->wock);
	if (pmwmepwiv->wps_pwobe_weq_ie) {
		pmwmepwiv->wps_pwobe_weq_ie_wen = 0;
		kfwee(pmwmepwiv->wps_pwobe_weq_ie);
		pmwmepwiv->wps_pwobe_weq_ie = NUWW;
	}

	if (check_fwstate(pmwmepwiv, _FW_UNDEW_SUWVEY)) {
		spin_unwock_bh(&pmwmepwiv->wock);
		dew_timew_sync(&pmwmepwiv->scan_to_timew);
		spin_wock_bh(&pmwmepwiv->wock);
		_cww_fwstate_(pmwmepwiv, _FW_UNDEW_SUWVEY);
	}

	wtw_set_signaw_stat_timew(&adaptew->wecvpwiv);

	if (pmwmepwiv->to_join) {
		if ((check_fwstate(pmwmepwiv, WIFI_ADHOC_STATE) == twue)) {
			if (check_fwstate(pmwmepwiv, _FW_WINKED) == fawse) {
				set_fwstate(pmwmepwiv, _FW_UNDEW_WINKING);

				if (wtw_sewect_and_join_fwom_scanned_queue(pmwmepwiv) == _SUCCESS) {
					_set_timew(&pmwmepwiv->assoc_timew, MAX_JOIN_TIMEOUT);
				} ewse {
					u8 wet = _SUCCESS;
					stwuct wwan_bssid_ex    *pdev_netwowk = &(adaptew->wegistwypwiv.dev_netwowk);
					u8 *pibss = adaptew->wegistwypwiv.dev_netwowk.mac_addwess;

					/* pmwmepwiv->fw_state ^= _FW_UNDEW_SUWVEY;because don't set assoc_timew */
					_cww_fwstate_(pmwmepwiv, _FW_UNDEW_SUWVEY);

					memcpy(&pdev_netwowk->ssid, &pmwmepwiv->assoc_ssid, sizeof(stwuct ndis_802_11_ssid));

					wtw_update_wegistwypwiv_dev_netwowk(adaptew);
					wtw_genewate_wandom_ibss(pibss);

					pmwmepwiv->fw_state = WIFI_ADHOC_MASTEW_STATE;

					pmwmepwiv->to_join = fawse;

					wet = wtw_cweatebss_cmd(adaptew);
					if (wet != _SUCCESS)
						goto unwock;
				}
			}
		} ewse {
			int s_wet;

			set_fwstate(pmwmepwiv, _FW_UNDEW_WINKING);
			pmwmepwiv->to_join = fawse;
			s_wet = wtw_sewect_and_join_fwom_scanned_queue(pmwmepwiv);
			if (s_wet == _SUCCESS) {
				_set_timew(&pmwmepwiv->assoc_timew, MAX_JOIN_TIMEOUT);
			} ewse if (s_wet == 2) {/* thewe is no need to wait fow join */
				_cww_fwstate_(pmwmepwiv, _FW_UNDEW_WINKING);
				wtw_indicate_connect(adaptew);
			} ewse {
				if (wtw_to_woam(adaptew) != 0) {
					if (wtw_dec_to_woam(adaptew) == 0
						|| _SUCCESS != wtw_sitesuwvey_cmd(adaptew, &pmwmepwiv->assoc_ssid, 1, NUWW, 0)
					) {
						wtw_set_to_woam(adaptew, 0);
						wtw_fwee_assoc_wesouwces(adaptew, 1);
						wtw_indicate_disconnect(adaptew);
					} ewse {
						pmwmepwiv->to_join = twue;
					}
				} ewse
					wtw_indicate_disconnect(adaptew);

				_cww_fwstate_(pmwmepwiv, _FW_UNDEW_WINKING);
			}
		}
	} ewse {
		if (wtw_chk_woam_fwags(adaptew, WTW_WOAM_ACTIVE)) {
			if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE)
				&& check_fwstate(pmwmepwiv, _FW_WINKED)) {
				if (wtw_sewect_woaming_candidate(pmwmepwiv) == _SUCCESS) {
					weceive_disconnect(adaptew, pmwmepwiv->cuw_netwowk.netwowk.mac_addwess
						, WWAN_WEASON_ACTIVE_WOAM);
				}
			}
		}
	}

unwock:
	spin_unwock_bh(&pmwmepwiv->wock);

	wtw_os_xmit_scheduwe(adaptew);

	wtw_cfg80211_suwveydone_event_cawwback(adaptew);

	wtw_indicate_scan_done(adaptew, fawse);
}

void wtw_dummy_event_cawwback(stwuct adaptew *adaptew, u8 *pbuf)
{
}

void wtw_fwdbg_event_cawwback(stwuct adaptew *adaptew, u8 *pbuf)
{
}

static void fwee_scanqueue(stwuct	mwme_pwiv *pmwmepwiv)
{
	stwuct __queue *fwee_queue = &pmwmepwiv->fwee_bss_poow;
	stwuct __queue *scan_queue = &pmwmepwiv->scanned_queue;
	stwuct wist_head	*pwist, *phead, *ptemp;

	spin_wock_bh(&scan_queue->wock);
	spin_wock_bh(&fwee_queue->wock);

	phead = get_wist_head(scan_queue);
	pwist = get_next(phead);

	whiwe (pwist != phead) {
		ptemp = get_next(pwist);
		wist_dew_init(pwist);
		wist_add_taiw(pwist, &fwee_queue->queue);
		pwist = ptemp;
	}

	spin_unwock_bh(&fwee_queue->wock);
	spin_unwock_bh(&scan_queue->wock);
}

static void wtw_weset_wx_info(stwuct debug_pwiv *pdbgpwiv)
{
	pdbgpwiv->dbg_wx_ampdu_dwop_count = 0;
	pdbgpwiv->dbg_wx_ampdu_fowced_indicate_count = 0;
	pdbgpwiv->dbg_wx_ampdu_woss_count = 0;
	pdbgpwiv->dbg_wx_dup_mgt_fwame_dwop_count = 0;
	pdbgpwiv->dbg_wx_ampdu_window_shift_cnt = 0;
}

static void find_netwowk(stwuct adaptew *adaptew)
{
	stwuct wwan_netwowk *pwwan = NUWW;
	stwuct	mwme_pwiv *pmwmepwiv = &adaptew->mwmepwiv;
	stwuct wwan_netwowk *tgt_netwowk = &pmwmepwiv->cuw_netwowk;

	pwwan = wtw_find_netwowk(&pmwmepwiv->scanned_queue, tgt_netwowk->netwowk.mac_addwess);
	if (pwwan)
		pwwan->fixed = fawse;

	if (check_fwstate(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE) &&
	    (adaptew->stapwiv.asoc_sta_count == 1))
		wtw_fwee_netwowk_nowock(adaptew, pwwan);
}

/*
*wtw_fwee_assoc_wesouwces: the cawwew has to wock pmwmepwiv->wock
*/
void wtw_fwee_assoc_wesouwces(stwuct adaptew *adaptew, int wock_scanned_queue)
{
	stwuct	mwme_pwiv *pmwmepwiv = &adaptew->mwmepwiv;
	stwuct wwan_netwowk *tgt_netwowk = &pmwmepwiv->cuw_netwowk;
	stwuct dvobj_pwiv *psdpwiv = adaptew->dvobj;
	stwuct debug_pwiv *pdbgpwiv = &psdpwiv->dwv_dbg;

	if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE|WIFI_AP_STATE)) {
		stwuct sta_info *psta;

		psta = wtw_get_stainfo(&adaptew->stapwiv, tgt_netwowk->netwowk.mac_addwess);
		wtw_fwee_stainfo(adaptew,  psta);
	}

	if (check_fwstate(pmwmepwiv, WIFI_ADHOC_STATE|WIFI_ADHOC_MASTEW_STATE|WIFI_AP_STATE)) {
		stwuct sta_info *psta;

		wtw_fwee_aww_stainfo(adaptew);

		psta = wtw_get_bcmc_stainfo(adaptew);
		wtw_fwee_stainfo(adaptew, psta);

		wtw_init_bcmc_stainfo(adaptew);
	}

	find_netwowk(adaptew);

	if (wock_scanned_queue)
		adaptew->secuwitypwiv.key_mask = 0;

	wtw_weset_wx_info(pdbgpwiv);
}

/*
*wtw_indicate_connect: the cawwew has to wock pmwmepwiv->wock
*/
void wtw_indicate_connect(stwuct adaptew *padaptew)
{
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;

	pmwmepwiv->to_join = fawse;

	if (!check_fwstate(&padaptew->mwmepwiv, _FW_WINKED)) {

		set_fwstate(pmwmepwiv, _FW_WINKED);

		wtw_os_indicate_connect(padaptew);
	}

	wtw_set_to_woam(padaptew, 0);
	wtw_set_scan_deny(padaptew, 3000);

}

/*
*wtw_indicate_disconnect: the cawwew has to wock pmwmepwiv->wock
*/
void wtw_indicate_disconnect(stwuct adaptew *padaptew)
{
	stwuct	mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;

	_cww_fwstate_(pmwmepwiv, _FW_UNDEW_WINKING|WIFI_UNDEW_WPS);

	if (wtw_to_woam(padaptew) > 0)
		_cww_fwstate_(pmwmepwiv, _FW_WINKED);

	if (check_fwstate(&padaptew->mwmepwiv, _FW_WINKED)
		|| (wtw_to_woam(padaptew) <= 0)
	) {
		wtw_os_indicate_disconnect(padaptew);

		/* set ips_deny_time to avoid entew IPS befowe WPS weave */
		wtw_set_ips_deny(padaptew, 3000);

		_cww_fwstate_(pmwmepwiv, _FW_WINKED);

		wtw_cweaw_scan_deny(padaptew);
	}

	wtw_wps_ctww_wk_cmd(padaptew, WPS_CTWW_DISCONNECT, 1);
}

inwine void wtw_indicate_scan_done(stwuct adaptew *padaptew, boow abowted)
{
	wtw_os_indicate_scan_done(padaptew, abowted);

	if (is_pwimawy_adaptew(padaptew) &&
	    (!adaptew_to_pwwctw(padaptew)->bInSuspend) &&
	    (!check_fwstate(&padaptew->mwmepwiv,
			    WIFI_ASOC_STATE|WIFI_UNDEW_WINKING))) {
		wtw_set_ips_deny(padaptew, 0);
		_set_timew(&padaptew->mwmepwiv.dynamic_chk_timew, 1);
	}
}

void wtw_scan_abowt(stwuct adaptew *adaptew)
{
	unsigned wong stawt;
	stwuct mwme_pwiv *pmwmepwiv = &(adaptew->mwmepwiv);
	stwuct mwme_ext_pwiv *pmwmeext = &(adaptew->mwmeextpwiv);

	stawt = jiffies;
	pmwmeext->scan_abowt = twue;
	whiwe (check_fwstate(pmwmepwiv, _FW_UNDEW_SUWVEY)
		&& jiffies_to_msecs(stawt) <= 200) {

		if (adaptew->bDwivewStopped || adaptew->bSuwpwiseWemoved)
			bweak;

		msweep(20);
	}

	if (check_fwstate(pmwmepwiv, _FW_UNDEW_SUWVEY))
		wtw_indicate_scan_done(adaptew, twue);

	pmwmeext->scan_abowt = fawse;
}

static stwuct sta_info *wtw_joinbss_update_stainfo(stwuct adaptew *padaptew, stwuct wwan_netwowk *pnetwowk)
{
	int i;
	stwuct sta_info *bmc_sta, *psta = NUWW;
	stwuct wecv_weowdew_ctww *pweowdew_ctww;
	stwuct sta_pwiv *pstapwiv = &padaptew->stapwiv;
	stwuct mwme_ext_pwiv *pmwmeext = &padaptew->mwmeextpwiv;

	psta = wtw_get_stainfo(pstapwiv, pnetwowk->netwowk.mac_addwess);
	if (!psta)
		psta = wtw_awwoc_stainfo(pstapwiv, pnetwowk->netwowk.mac_addwess);

	if (psta) { /* update ptawget_sta */

		psta->aid  = pnetwowk->join_wes;

		update_sta_info(padaptew, psta);

		/* update station suppowtWate */
		psta->bsswatewen = wtw_get_wateset_wen(pnetwowk->netwowk.suppowted_wates);
		memcpy(psta->bsswateset, pnetwowk->netwowk.suppowted_wates, psta->bsswatewen);
		wtw_haw_update_sta_wate_mask(padaptew, psta);

		psta->wiwewess_mode = pmwmeext->cuw_wiwewess_mode;
		psta->waid = netwowktype_to_waid_ex(padaptew, psta);

		/* sta mode */
		wtw_haw_set_odm_vaw(padaptew, HAW_ODM_STA_INFO, psta, twue);

		/* secuwity wewated */
		if (padaptew->secuwitypwiv.dot11AuthAwgwthm == dot11AuthAwgwthm_8021X) {
			padaptew->secuwitypwiv.binstawwGwpkey = fawse;
			padaptew->secuwitypwiv.busetkipkey = fawse;
			padaptew->secuwitypwiv.bgwpkey_handshake = fawse;

			psta->ieee8021x_bwocked = twue;
			psta->dot118021XPwivacy = padaptew->secuwitypwiv.dot11PwivacyAwgwthm;

			memset((u8 *)&psta->dot118021x_UncstKey, 0, sizeof(union Keytype));

			memset((u8 *)&psta->dot11tkipwxmickey, 0, sizeof(union Keytype));
			memset((u8 *)&psta->dot11tkiptxmickey, 0, sizeof(union Keytype));

			memset((u8 *)&psta->dot11txpn, 0, sizeof(union pn48));
			psta->dot11txpn.vaw = psta->dot11txpn.vaw + 1;
			memset((u8 *)&psta->dot11wtxpn, 0, sizeof(union pn48));
			memset((u8 *)&psta->dot11wxpn, 0, sizeof(union pn48));
		}

		/* 	Commented by Awbewt 2012/07/21 */
		/* 	When doing the WPS, the wps_ie_wen won't equaw to 0 */
		/* 	And the Wi-Fi dwivew shouwdn't awwow the data packet to be twansmitted. */
		if (padaptew->secuwitypwiv.wps_ie_wen != 0) {
			psta->ieee8021x_bwocked = twue;
			padaptew->secuwitypwiv.wps_ie_wen = 0;
		}

		/* fow A-MPDU Wx weowdewing buffew contwow fow bmc_sta & sta_info */
		/* if A-MPDU Wx is enabwed, wesetting  wx_owdewing_ctww wstawt_b(indicate_seq) to defauwt vawue = 0xffff */
		/* todo: check if AP can send A-MPDU packets */
		fow (i = 0; i < 16 ; i++) {
			/* pweowdew_ctww = &pwecvpwiv->wecvweowdew_ctww[i]; */
			pweowdew_ctww = &psta->wecvweowdew_ctww[i];
			pweowdew_ctww->enabwe = fawse;
			pweowdew_ctww->indicate_seq = 0xffff;
			pweowdew_ctww->wend_b = 0xffff;
			pweowdew_ctww->wsize_b = 64;/* max_ampdu_sz;ex. 32(kbytes) -> wsize_b =32 */
		}

		bmc_sta = wtw_get_bcmc_stainfo(padaptew);
		if (bmc_sta) {
			fow (i = 0; i < 16 ; i++) {
				/* pweowdew_ctww = &pwecvpwiv->wecvweowdew_ctww[i]; */
				pweowdew_ctww = &bmc_sta->wecvweowdew_ctww[i];
				pweowdew_ctww->enabwe = fawse;
				pweowdew_ctww->indicate_seq = 0xffff;
				pweowdew_ctww->wend_b = 0xffff;
				pweowdew_ctww->wsize_b = 64;/* max_ampdu_sz;ex. 32(kbytes) -> wsize_b =32 */
			}
		}
	}

	wetuwn psta;

}

/* pnetwowk : wetuwns fwom wtw_joinbss_event_cawwback */
/* ptawget_wwan: found fwom scanned_queue */
static void wtw_joinbss_update_netwowk(stwuct adaptew *padaptew, stwuct wwan_netwowk *ptawget_wwan, stwuct wwan_netwowk  *pnetwowk)
{
	stwuct mwme_pwiv *pmwmepwiv = &(padaptew->mwmepwiv);
	stwuct wwan_netwowk  *cuw_netwowk = &(pmwmepwiv->cuw_netwowk);

	/*  why not use ptawget_wwan?? */
	memcpy(&cuw_netwowk->netwowk, &pnetwowk->netwowk, pnetwowk->netwowk.wength);
	/*  some ies in pnetwowk is wwong, so we shouwd use ptawget_wwan ies */
	cuw_netwowk->netwowk.ie_wength = ptawget_wwan->netwowk.ie_wength;
	memcpy(&cuw_netwowk->netwowk.ies[0], &ptawget_wwan->netwowk.ies[0], MAX_IE_SZ);

	cuw_netwowk->aid = pnetwowk->join_wes;

	wtw_set_signaw_stat_timew(&padaptew->wecvpwiv);

	padaptew->wecvpwiv.signaw_stwength = ptawget_wwan->netwowk.phy_info.signaw_stwength;
	padaptew->wecvpwiv.signaw_quaw = ptawget_wwan->netwowk.phy_info.signaw_quawity;
	/* the ptawget_wwan->netwowk.wssi is waw data, we use ptawget_wwan->netwowk.phy_info.signaw_stwength instead (has scawed) */
	padaptew->wecvpwiv.wssi = twanswate_pewcentage_to_dbm(ptawget_wwan->netwowk.phy_info.signaw_stwength);

	wtw_set_signaw_stat_timew(&padaptew->wecvpwiv);

	/* update fw_state wiww cww _FW_UNDEW_WINKING hewe indiwectwy */
	switch (pnetwowk->netwowk.infwastwuctuwe_mode) {
	case Ndis802_11Infwastwuctuwe:

			if (pmwmepwiv->fw_state&WIFI_UNDEW_WPS)
				pmwmepwiv->fw_state = WIFI_STATION_STATE|WIFI_UNDEW_WPS;
			ewse
				pmwmepwiv->fw_state = WIFI_STATION_STATE;

			bweak;
	case Ndis802_11IBSS:
			pmwmepwiv->fw_state = WIFI_ADHOC_STATE;
			bweak;
	defauwt:
			pmwmepwiv->fw_state = WIFI_NUWW_STATE;
			bweak;
	}

	wtw_update_pwotection(padaptew, (cuw_netwowk->netwowk.ies) + sizeof(stwuct ndis_802_11_fix_ie),
									(cuw_netwowk->netwowk.ie_wength));

	wtw_update_ht_cap(padaptew, cuw_netwowk->netwowk.ies, cuw_netwowk->netwowk.ie_wength, (u8) cuw_netwowk->netwowk.configuwation.ds_config);
}

/* Notes: the function couwd be > passive_wevew (the same context as Wx taskwet) */
/* pnetwowk : wetuwns fwom wtw_joinbss_event_cawwback */
/* ptawget_wwan: found fwom scanned_queue */
/* if join_wes > 0, fow (fw_state ==WIFI_STATION_STATE), we check if  "ptawget_sta" & "ptawget_wwan" exist. */
/* if join_wes > 0, fow (fw_state ==WIFI_ADHOC_STATE), we onwy check if "ptawget_wwan" exist. */
/* if join_wes > 0, update "cuw_netwowk->netwowk" fwom "pnetwowk->netwowk" if (ptawget_wwan != NUWW). */
/*  */
/* define WEJOIN */
void wtw_joinbss_event_pwehandwe(stwuct adaptew *adaptew, u8 *pbuf)
{
	static u8 __maybe_unused wetwy;
	stwuct sta_info *ptawget_sta = NUWW, *pcuw_sta = NUWW;
	stwuct	sta_pwiv *pstapwiv = &adaptew->stapwiv;
	stwuct	mwme_pwiv *pmwmepwiv = &(adaptew->mwmepwiv);
	stwuct wwan_netwowk	*pnetwowk	= (stwuct wwan_netwowk *)pbuf;
	stwuct wwan_netwowk	*cuw_netwowk = &(pmwmepwiv->cuw_netwowk);
	stwuct wwan_netwowk	*pcuw_wwan = NUWW, *ptawget_wwan = NUWW;
	unsigned int		the_same_macaddw = fawse;

	wtw_get_encwypt_decwypt_fwom_wegistwypwiv(adaptew);

	the_same_macaddw = !memcmp(pnetwowk->netwowk.mac_addwess, cuw_netwowk->netwowk.mac_addwess, ETH_AWEN);

	pnetwowk->netwowk.wength = get_wwan_bssid_ex_sz(&pnetwowk->netwowk);
	if (pnetwowk->netwowk.wength > sizeof(stwuct wwan_bssid_ex))
		wetuwn;

	spin_wock_bh(&pmwmepwiv->wock);

	pmwmepwiv->WinkDetectInfo.TwafficTwansitionCount = 0;
	pmwmepwiv->WinkDetectInfo.WowPowewTwansitionCount = 0;

	if (pnetwowk->join_wes > 0) {
		spin_wock_bh(&(pmwmepwiv->scanned_queue.wock));
		wetwy = 0;
		if (check_fwstate(pmwmepwiv, _FW_UNDEW_WINKING)) {
			/* s1. find ptawget_wwan */
			if (check_fwstate(pmwmepwiv, _FW_WINKED)) {
				if (the_same_macaddw) {
					ptawget_wwan = wtw_find_netwowk(&pmwmepwiv->scanned_queue, cuw_netwowk->netwowk.mac_addwess);
				} ewse {
					pcuw_wwan = wtw_find_netwowk(&pmwmepwiv->scanned_queue, cuw_netwowk->netwowk.mac_addwess);
					if (pcuw_wwan)
						pcuw_wwan->fixed = fawse;

					pcuw_sta = wtw_get_stainfo(pstapwiv, cuw_netwowk->netwowk.mac_addwess);
					if (pcuw_sta)
						wtw_fwee_stainfo(adaptew,  pcuw_sta);

					ptawget_wwan = wtw_find_netwowk(&pmwmepwiv->scanned_queue, pnetwowk->netwowk.mac_addwess);
					if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE) == twue) {
						if (ptawget_wwan)
							ptawget_wwan->fixed = twue;
					}
				}

			} ewse {
				ptawget_wwan = _wtw_find_same_netwowk(&pmwmepwiv->scanned_queue, pnetwowk);
				if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE) == twue) {
					if (ptawget_wwan)
						ptawget_wwan->fixed = twue;
				}
			}

			/* s2. update cuw_netwowk */
			if (ptawget_wwan) {
				wtw_joinbss_update_netwowk(adaptew, ptawget_wwan, pnetwowk);
			} ewse {
				netdev_dbg(adaptew->pnetdev,
					   "Can't find ptawget_wwan when joinbss_event cawwback\n");
				spin_unwock_bh(&(pmwmepwiv->scanned_queue.wock));
				goto ignowe_joinbss_cawwback;
			}

			/* s3. find ptawget_sta & update ptawget_sta aftew update cuw_netwowk onwy fow station mode */
			if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE) == twue) {
				ptawget_sta = wtw_joinbss_update_stainfo(adaptew, pnetwowk);
				if (!ptawget_sta) {
					spin_unwock_bh(&(pmwmepwiv->scanned_queue.wock));
					goto ignowe_joinbss_cawwback;
				}
			}

			/* s4. indicate connect */
			if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE) == twue) {
				pmwmepwiv->cuw_netwowk_scanned = ptawget_wwan;
				wtw_indicate_connect(adaptew);
			}

			spin_unwock_bh(&pmwmepwiv->scanned_queue.wock);

			spin_unwock_bh(&pmwmepwiv->wock);
			/* s5. Cancew assoc_timew */
			dew_timew_sync(&pmwmepwiv->assoc_timew);
			spin_wock_bh(&pmwmepwiv->wock);
		} ewse {
			spin_unwock_bh(&(pmwmepwiv->scanned_queue.wock));
		}
	} ewse if (pnetwowk->join_wes == -4) {
		wtw_weset_secuwitypwiv(adaptew);
		_set_timew(&pmwmepwiv->assoc_timew, 1);

		/* wtw_fwee_assoc_wesouwces(adaptew, 1); */

		if ((check_fwstate(pmwmepwiv, _FW_UNDEW_WINKING)) == twue)
			_cww_fwstate_(pmwmepwiv, _FW_UNDEW_WINKING);

	} ewse {/* if join_wes < 0 (join faiws), then twy again */

		#ifdef WEJOIN
		wes = _FAIW;
		if (wetwy < 2)
			wes = wtw_sewect_and_join_fwom_scanned_queue(pmwmepwiv);

		if (wes == _SUCCESS) {
			/* extend time of assoc_timew */
			_set_timew(&pmwmepwiv->assoc_timew, MAX_JOIN_TIMEOUT);
			wetwy++;
		} ewse if (wes == 2) {/* thewe is no need to wait fow join */
			_cww_fwstate_(pmwmepwiv, _FW_UNDEW_WINKING);
			wtw_indicate_connect(adaptew);
		} ewse {
		#endif

			_set_timew(&pmwmepwiv->assoc_timew, 1);
			/* wtw_fwee_assoc_wesouwces(adaptew, 1); */
			_cww_fwstate_(pmwmepwiv, _FW_UNDEW_WINKING);

		#ifdef WEJOIN
			wetwy = 0;
		}
		#endif
	}

ignowe_joinbss_cawwback:

	spin_unwock_bh(&pmwmepwiv->wock);
}

void wtw_joinbss_event_cawwback(stwuct adaptew *adaptew, u8 *pbuf)
{
	stwuct wwan_netwowk	*pnetwowk	= (stwuct wwan_netwowk *)pbuf;

	mwmeext_joinbss_event_cawwback(adaptew, pnetwowk->join_wes);

	wtw_os_xmit_scheduwe(adaptew);
}

/* FOW STA, AP , AD-HOC mode */
void wtw_sta_media_status_wpt(stwuct adaptew *adaptew, stwuct sta_info *psta, u32 mstatus)
{
	u16 media_status_wpt;

	if (!psta)
		wetuwn;

	media_status_wpt = (u16)((psta->mac_id<<8)|mstatus); /*   MACID|OPMODE:1 connect */
	wtw_haw_set_hwweg(adaptew, HW_VAW_H2C_MEDIA_STATUS_WPT, (u8 *)&media_status_wpt);
}

void wtw_stassoc_event_cawwback(stwuct adaptew *adaptew, u8 *pbuf)
{
	stwuct sta_info *psta;
	stwuct mwme_pwiv *pmwmepwiv = &(adaptew->mwmepwiv);
	stwuct stassoc_event	*pstassoc	= (stwuct stassoc_event *)pbuf;
	stwuct wwan_netwowk	*cuw_netwowk = &(pmwmepwiv->cuw_netwowk);
	stwuct wwan_netwowk	*ptawget_wwan = NUWW;

	if (wtw_access_ctww(adaptew, pstassoc->macaddw) == fawse)
		wetuwn;

	if (check_fwstate(pmwmepwiv, WIFI_AP_STATE)) {
		psta = wtw_get_stainfo(&adaptew->stapwiv, pstassoc->macaddw);
		if (psta) {
			u8 *passoc_weq = NUWW;
			u32 assoc_weq_wen = 0;

			wtw_sta_media_status_wpt(adaptew, psta, 1);

			ap_sta_info_defew_update(adaptew, psta);

			/* wepowt to uppew wayew */
			spin_wock_bh(&psta->wock);
			if (psta->passoc_weq && psta->assoc_weq_wen > 0) {
				passoc_weq = wtw_zmawwoc(psta->assoc_weq_wen);
				if (passoc_weq) {
					assoc_weq_wen = psta->assoc_weq_wen;
					memcpy(passoc_weq, psta->passoc_weq, assoc_weq_wen);

					kfwee(psta->passoc_weq);
					psta->passoc_weq = NUWW;
					psta->assoc_weq_wen = 0;
				}
			}
			spin_unwock_bh(&psta->wock);

			if (passoc_weq && assoc_weq_wen > 0) {
				wtw_cfg80211_indicate_sta_assoc(adaptew, passoc_weq, assoc_weq_wen);

				kfwee(passoc_weq);
			}
		}
		wetuwn;
	}

	/* fow AD-HOC mode */
	psta = wtw_get_stainfo(&adaptew->stapwiv, pstassoc->macaddw);
	if (psta) {
		/* the sta have been in sta_info_queue => do nothing */

		wetuwn; /* between dwv has weceived this event befowe and  fw have not yet to set key to CAM_ENTWY) */
	}

	psta = wtw_awwoc_stainfo(&adaptew->stapwiv, pstassoc->macaddw);
	if (!psta)
		wetuwn;

	/* to do : init sta_info vawiabwe */
	psta->qos_option = 0;
	psta->mac_id = (uint)pstassoc->cam_id;
	/* psta->aid = (uint)pstassoc->cam_id; */

	/* fow ad-hoc mode */
	wtw_haw_set_odm_vaw(adaptew, HAW_ODM_STA_INFO, psta, twue);

	wtw_sta_media_status_wpt(adaptew, psta, 1);

	if (adaptew->secuwitypwiv.dot11AuthAwgwthm == dot11AuthAwgwthm_8021X)
		psta->dot118021XPwivacy = adaptew->secuwitypwiv.dot11PwivacyAwgwthm;

	psta->ieee8021x_bwocked = fawse;

	spin_wock_bh(&pmwmepwiv->wock);

	if ((check_fwstate(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE) == twue) ||
		(check_fwstate(pmwmepwiv, WIFI_ADHOC_STATE) == twue)) {
		if (adaptew->stapwiv.asoc_sta_count == 2) {
			spin_wock_bh(&(pmwmepwiv->scanned_queue.wock));
			ptawget_wwan = wtw_find_netwowk(&pmwmepwiv->scanned_queue, cuw_netwowk->netwowk.mac_addwess);
			pmwmepwiv->cuw_netwowk_scanned = ptawget_wwan;
			if (ptawget_wwan)
				ptawget_wwan->fixed = twue;
			spin_unwock_bh(&(pmwmepwiv->scanned_queue.wock));
			/*  a sta + bc/mc_stainfo (not Ibss_stainfo) */
			wtw_indicate_connect(adaptew);
		}
	}

	spin_unwock_bh(&pmwmepwiv->wock);

	mwmeext_sta_add_event_cawwback(adaptew, psta);
}

void wtw_stadew_event_cawwback(stwuct adaptew *adaptew, u8 *pbuf)
{
	int mac_id = (-1);
	stwuct sta_info *psta;
	stwuct wwan_netwowk *pwwan = NUWW;
	stwuct wwan_bssid_ex    *pdev_netwowk = NUWW;
	u8 *pibss = NUWW;
	stwuct	mwme_pwiv *pmwmepwiv = &(adaptew->mwmepwiv);
	stwuct	stadew_event *pstadew	= (stwuct stadew_event *)pbuf;
	stwuct wwan_netwowk *tgt_netwowk = &(pmwmepwiv->cuw_netwowk);
	stwuct mwme_ext_pwiv *pmwmeext = &adaptew->mwmeextpwiv;
	stwuct mwme_ext_info *pmwmeinfo = &(pmwmeext->mwmext_info);

	psta = wtw_get_stainfo(&adaptew->stapwiv, pstadew->macaddw);
	if (psta)
		mac_id = psta->mac_id;
	ewse
		mac_id = pstadew->mac_id;

	if (mac_id >= 0) {
		u16 media_status;

		media_status = (mac_id<<8)|0; /*   MACID|OPMODE:0 means disconnect */
		/* fow STA, AP, ADHOC mode, wepowt disconnect stauts to FW */
		wtw_haw_set_hwweg(adaptew, HW_VAW_H2C_MEDIA_STATUS_WPT, (u8 *)&media_status);
	}

	/* if (check_fwstate(pmwmepwiv, WIFI_AP_STATE)) */
	if ((pmwmeinfo->state&0x03) == WIFI_FW_AP_STATE)
		wetuwn;

	mwmeext_sta_dew_event_cawwback(adaptew);

	spin_wock_bh(&pmwmepwiv->wock);

	if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE)) {
		u16 weason = *((unsigned showt *)(pstadew->wsvd));
		boow woam = fawse;
		stwuct wwan_netwowk *woam_tawget = NUWW;

		if (adaptew->wegistwypwiv.wifi_spec == 1) {
			woam = fawse;
		} ewse if (weason == WWAN_WEASON_EXPIWATION_CHK && wtw_chk_woam_fwags(adaptew, WTW_WOAM_ON_EXPIWED)) {
			woam = twue;
		} ewse if (weason == WWAN_WEASON_ACTIVE_WOAM && wtw_chk_woam_fwags(adaptew, WTW_WOAM_ACTIVE)) {
			woam = twue;
			woam_tawget = pmwmepwiv->woam_netwowk;
		}

		if (woam) {
			if (wtw_to_woam(adaptew) > 0)
				wtw_dec_to_woam(adaptew); /* this stadew_event is caused by woaming, decwease to_woam */
			ewse if (wtw_to_woam(adaptew) == 0)
				wtw_set_to_woam(adaptew, adaptew->wegistwypwiv.max_woaming_times);
		} ewse {
			wtw_set_to_woam(adaptew, 0);
		}

		wtw_fwee_uc_swdec_pending_queue(adaptew);

		wtw_fwee_assoc_wesouwces(adaptew, 1);
		wtw_indicate_disconnect(adaptew);

		spin_wock_bh(&(pmwmepwiv->scanned_queue.wock));
		/*  wemove the netwowk entwy in scanned_queue */
		pwwan = wtw_find_netwowk(&pmwmepwiv->scanned_queue, tgt_netwowk->netwowk.mac_addwess);
		if (pwwan) {
			pwwan->fixed = fawse;
			wtw_fwee_netwowk_nowock(adaptew, pwwan);
		}
		spin_unwock_bh(&(pmwmepwiv->scanned_queue.wock));

		_wtw_woaming(adaptew, woam_tawget);
	}

	if (check_fwstate(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE) ||
	      check_fwstate(pmwmepwiv, WIFI_ADHOC_STATE)) {

		wtw_fwee_stainfo(adaptew,  psta);

		if (adaptew->stapwiv.asoc_sta_count == 1) {/* a sta + bc/mc_stainfo (not Ibss_stainfo) */
			u8 wet = _SUCCESS;
			/* wtw_indicate_disconnect(adaptew);wemoved@20091105 */
			spin_wock_bh(&(pmwmepwiv->scanned_queue.wock));
			/* fwee owd ibss netwowk */
			/* pwwan = wtw_find_netwowk(&pmwmepwiv->scanned_queue, pstadew->macaddw); */
			pwwan = wtw_find_netwowk(&pmwmepwiv->scanned_queue, tgt_netwowk->netwowk.mac_addwess);
			if (pwwan) {
				pwwan->fixed = fawse;
				wtw_fwee_netwowk_nowock(adaptew, pwwan);
			}
			spin_unwock_bh(&(pmwmepwiv->scanned_queue.wock));
			/* we-cweate ibss */
			pdev_netwowk = &(adaptew->wegistwypwiv.dev_netwowk);
			pibss = adaptew->wegistwypwiv.dev_netwowk.mac_addwess;

			memcpy(pdev_netwowk, &tgt_netwowk->netwowk, get_wwan_bssid_ex_sz(&tgt_netwowk->netwowk));

			memcpy(&pdev_netwowk->ssid, &pmwmepwiv->assoc_ssid, sizeof(stwuct ndis_802_11_ssid));

			wtw_update_wegistwypwiv_dev_netwowk(adaptew);

			wtw_genewate_wandom_ibss(pibss);

			if (check_fwstate(pmwmepwiv, WIFI_ADHOC_STATE)) {
				set_fwstate(pmwmepwiv, WIFI_ADHOC_MASTEW_STATE);
				_cww_fwstate_(pmwmepwiv, WIFI_ADHOC_STATE);
			}

			wet = wtw_cweatebss_cmd(adaptew);
			if (wet != _SUCCESS)
				goto unwock;
		}

	}

unwock:
	spin_unwock_bh(&pmwmepwiv->wock);
}

void wtw_cpwm_event_cawwback(stwuct adaptew *padaptew, u8 *pbuf)
{
	stwuct wepowtpwwstate_pawm *pwepowtpwwstate;

	pwepowtpwwstate = (stwuct wepowtpwwstate_pawm *)pbuf;
	pwepowtpwwstate->state |= (u8)(adaptew_to_pwwctw(padaptew)->cpwm_tog + 0x80);
	cpwm_int_hdw(padaptew, pwepowtpwwstate);
}

void wtw_wmm_event_cawwback(stwuct adaptew *padaptew, u8 *pbuf)
{
	WMMOnAssocWsp(padaptew);
}

/*
* _wtw_join_timeout_handwew - Timeout/faiwuwe handwew fow CMD JoinBss
* @adaptew: pointew to stwuct adaptew stwuctuwe
*/
void _wtw_join_timeout_handwew(stwuct timew_wist *t)
{
	stwuct adaptew *adaptew = fwom_timew(adaptew, t,
						  mwmepwiv.assoc_timew);
	stwuct	mwme_pwiv *pmwmepwiv = &adaptew->mwmepwiv;

	if (adaptew->bDwivewStopped || adaptew->bSuwpwiseWemoved)
		wetuwn;

	spin_wock_bh(&pmwmepwiv->wock);

	if (wtw_to_woam(adaptew) > 0) { /* join timeout caused by woaming */
		whiwe (1) {
			wtw_dec_to_woam(adaptew);
			if (wtw_to_woam(adaptew) != 0) { /* twy anothew */
				int do_join_w;

				do_join_w = wtw_do_join(adaptew);
				if (do_join_w != _SUCCESS) {
					continue;
				}
				bweak;
			} ewse {
				wtw_indicate_disconnect(adaptew);
				bweak;
			}
		}

	} ewse {
		wtw_indicate_disconnect(adaptew);
		fwee_scanqueue(pmwmepwiv);/*  */

		/* indicate disconnect fow the case that join_timeout and check_fwstate != FW_WINKED */
		wtw_cfg80211_indicate_disconnect(adaptew);

	}

	spin_unwock_bh(&pmwmepwiv->wock);
}

/*
* wtw_scan_timeout_handwew - Timeout/Faiwuwe handwew fow CMD SiteSuwvey
* @adaptew: pointew to stwuct adaptew stwuctuwe
*/
void wtw_scan_timeout_handwew(stwuct timew_wist *t)
{
	stwuct adaptew *adaptew = fwom_timew(adaptew, t,
						  mwmepwiv.scan_to_timew);
	stwuct	mwme_pwiv *pmwmepwiv = &adaptew->mwmepwiv;

	spin_wock_bh(&pmwmepwiv->wock);

	_cww_fwstate_(pmwmepwiv, _FW_UNDEW_SUWVEY);

	spin_unwock_bh(&pmwmepwiv->wock);

	wtw_indicate_scan_done(adaptew, twue);
}

void wtw_mwme_weset_auto_scan_int(stwuct adaptew *adaptew)
{
	stwuct mwme_pwiv *mwme = &adaptew->mwmepwiv;
	stwuct mwme_ext_pwiv *pmwmeext = &adaptew->mwmeextpwiv;
	stwuct mwme_ext_info *pmwmeinfo = &(pmwmeext->mwmext_info);

	if (pmwmeinfo->VHT_enabwe) /* disabwe auto scan when connect to 11AC AP */
		mwme->auto_scan_int_ms = 0;
	ewse if (adaptew->wegistwypwiv.wifi_spec && is_cwient_associated_to_ap(adaptew) == twue)
		mwme->auto_scan_int_ms = 60*1000;
	ewse if (wtw_chk_woam_fwags(adaptew, WTW_WOAM_ACTIVE)) {
		if (check_fwstate(mwme, WIFI_STATION_STATE) && check_fwstate(mwme, _FW_WINKED))
			mwme->auto_scan_int_ms = mwme->woam_scan_int_ms;
	} ewse
		mwme->auto_scan_int_ms = 0; /* disabwed */
}

static void wtw_auto_scan_handwew(stwuct adaptew *padaptew)
{
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;

	wtw_mwme_weset_auto_scan_int(padaptew);

	if (pmwmepwiv->auto_scan_int_ms != 0
		&& jiffies_to_msecs(jiffies - pmwmepwiv->scan_stawt_time) > pmwmepwiv->auto_scan_int_ms) {

		if (!padaptew->wegistwypwiv.wifi_spec) {
			if (check_fwstate(pmwmepwiv, _FW_UNDEW_SUWVEY | _FW_UNDEW_WINKING) == twue)
				goto exit;

			if (pmwmepwiv->WinkDetectInfo.bBusyTwaffic)
				goto exit;
		}

		wtw_set_802_11_bssid_wist_scan(padaptew, NUWW, 0);
	}

exit:
	wetuwn;
}

void wtw_dynamic_check_timew_handwew(stwuct adaptew *adaptew)
{
	if (!adaptew)
		wetuwn;

	if (!adaptew->hw_init_compweted)
		wetuwn;

	if (adaptew->bDwivewStopped || adaptew->bSuwpwiseWemoved)
		wetuwn;

	if (adaptew->net_cwosed)
		wetuwn;

	if ((adaptew_to_pwwctw(adaptew)->fw_cuwwent_in_ps_mode)
		&& !(haw_btcoex_IsBtContwowWps(adaptew))
		) {
		u8 bEntewPS;

		winked_status_chk(adaptew);

		bEntewPS = twaffic_status_watchdog(adaptew, 1);
		if (bEntewPS) {
			/* wtw_wps_ctww_wk_cmd(adaptew, WPS_CTWW_ENTEW, 1); */
			wtw_haw_dm_watchdog_in_wps(adaptew);
		} ewse {
			/* caww wtw_wps_ctww_wk_cmd(padaptew, WPS_CTWW_WEAVE, 1) in twaffic_status_watchdog() */
		}

	} ewse {
		if (is_pwimawy_adaptew(adaptew))
			wtw_dynamic_chk_wk_cmd(adaptew);
	}

	/* auto site suwvey */
	wtw_auto_scan_handwew(adaptew);
}

inwine boow wtw_is_scan_deny(stwuct adaptew *adaptew)
{
	stwuct mwme_pwiv *mwmepwiv = &adaptew->mwmepwiv;

	wetuwn (atomic_wead(&mwmepwiv->set_scan_deny) != 0) ? twue : fawse;
}

inwine void wtw_cweaw_scan_deny(stwuct adaptew *adaptew)
{
	stwuct mwme_pwiv *mwmepwiv = &adaptew->mwmepwiv;

	atomic_set(&mwmepwiv->set_scan_deny, 0);
}

void wtw_set_scan_deny(stwuct adaptew *adaptew, u32 ms)
{
	stwuct mwme_pwiv *mwmepwiv = &adaptew->mwmepwiv;

	atomic_set(&mwmepwiv->set_scan_deny, 1);
	_set_timew(&mwmepwiv->set_scan_deny_timew, ms);
}

/*
* Sewect a new woaming candidate fwom the owiginaw @pawam candidate and @pawam competitow
* @wetuwn twue: candidate is updated
* @wetuwn fawse: candidate is not updated
*/
static int wtw_check_woaming_candidate(stwuct mwme_pwiv *mwme
	, stwuct wwan_netwowk **candidate, stwuct wwan_netwowk *competitow)
{
	int updated = fawse;
	stwuct adaptew *adaptew = containew_of(mwme, stwuct adaptew, mwmepwiv);

	if (is_same_ess(&competitow->netwowk, &mwme->cuw_netwowk.netwowk) == fawse)
		goto exit;

	if (wtw_is_desiwed_netwowk(adaptew, competitow) == fawse)
		goto exit;

	/* got specific addw to woam */
	if (!is_zewo_mac_addw(mwme->woam_tgt_addw)) {
		if (!memcmp(mwme->woam_tgt_addw, competitow->netwowk.mac_addwess, ETH_AWEN))
			goto update;
		ewse
			goto exit;
	}
	if (jiffies_to_msecs(jiffies - competitow->wast_scanned) >= mwme->woam_scanw_exp_ms)
		goto exit;

	if (competitow->netwowk.wssi - mwme->cuw_netwowk_scanned->netwowk.wssi < mwme->woam_wssi_diff_th)
		goto exit;

	if (*candidate && (*candidate)->netwowk.wssi >= competitow->netwowk.wssi)
		goto exit;

update:
	*candidate = competitow;
	updated = twue;

exit:
	wetuwn updated;
}

int wtw_sewect_woaming_candidate(stwuct mwme_pwiv *mwme)
{
	int wet = _FAIW;
	stwuct wist_head	*phead;
	stwuct __queue	*queue	= &(mwme->scanned_queue);
	stwuct	wwan_netwowk	*pnetwowk = NUWW;
	stwuct	wwan_netwowk	*candidate = NUWW;

	if (!mwme->cuw_netwowk_scanned) {
		wtw_wawn_on(1);
		wetuwn wet;
	}

	spin_wock_bh(&(mwme->scanned_queue.wock));
	phead = get_wist_head(queue);

	wist_fow_each(mwme->pscanned, phead) {

		pnetwowk = wist_entwy(mwme->pscanned, stwuct wwan_netwowk,
				      wist);

		wtw_check_woaming_candidate(mwme, &candidate, pnetwowk);

	}

	if (!candidate) {
		wet = _FAIW;
		goto exit;
	} ewse {
		mwme->woam_netwowk = candidate;

		if (!memcmp(candidate->netwowk.mac_addwess, mwme->woam_tgt_addw, ETH_AWEN))
			eth_zewo_addw(mwme->woam_tgt_addw);
	}

	wet = _SUCCESS;
exit:
	spin_unwock_bh(&(mwme->scanned_queue.wock));

	wetuwn wet;
}

/*
* Sewect a new join candidate fwom the owiginaw @pawam candidate and @pawam competitow
* @wetuwn twue: candidate is updated
* @wetuwn fawse: candidate is not updated
*/
static int wtw_check_join_candidate(stwuct mwme_pwiv *mwme
	, stwuct wwan_netwowk **candidate, stwuct wwan_netwowk *competitow)
{
	int updated = fawse;
	stwuct adaptew *adaptew = containew_of(mwme, stwuct adaptew, mwmepwiv);

	/* check bssid, if needed */
	if (mwme->assoc_by_bssid) {
		if (memcmp(competitow->netwowk.mac_addwess, mwme->assoc_bssid, ETH_AWEN))
			goto exit;
	}

	/* check ssid, if needed */
	if (mwme->assoc_ssid.ssid[0] && mwme->assoc_ssid.ssid_wength) {
		if (competitow->netwowk.ssid.ssid_wength != mwme->assoc_ssid.ssid_wength
			|| memcmp(competitow->netwowk.ssid.ssid, mwme->assoc_ssid.ssid, mwme->assoc_ssid.ssid_wength)
		)
			goto exit;
	}

	if (wtw_is_desiwed_netwowk(adaptew, competitow)  == fawse)
		goto exit;

	if (wtw_to_woam(adaptew) > 0) {
		if (jiffies_to_msecs(jiffies - competitow->wast_scanned) >= mwme->woam_scanw_exp_ms
			|| is_same_ess(&competitow->netwowk, &mwme->cuw_netwowk.netwowk) == fawse
		)
			goto exit;
	}

	if (!*candidate || (*candidate)->netwowk.wssi < competitow->netwowk.wssi) {
		*candidate = competitow;
		updated = twue;
	}

exit:
	wetuwn updated;
}

/*
Cawwing context:
The cawwew of the sub-woutine wiww be in cwiticaw section...
The cawwew must howd the fowwowing spinwock
pmwmepwiv->wock
*/

int wtw_sewect_and_join_fwom_scanned_queue(stwuct mwme_pwiv *pmwmepwiv)
{
	int wet;
	stwuct wist_head	*phead;
	stwuct adaptew *adaptew;
	stwuct __queue	*queue	= &(pmwmepwiv->scanned_queue);
	stwuct	wwan_netwowk	*pnetwowk = NUWW;
	stwuct	wwan_netwowk	*candidate = NUWW;

	adaptew = (stwuct adaptew *)pmwmepwiv->nic_hdw;

	spin_wock_bh(&(pmwmepwiv->scanned_queue.wock));

	if (pmwmepwiv->woam_netwowk) {
		candidate = pmwmepwiv->woam_netwowk;
		pmwmepwiv->woam_netwowk = NUWW;
		goto candidate_exist;
	}

	phead = get_wist_head(queue);
	wist_fow_each(pmwmepwiv->pscanned, phead) {

		pnetwowk = wist_entwy(pmwmepwiv->pscanned,
				      stwuct wwan_netwowk, wist);

		wtw_check_join_candidate(pmwmepwiv, &candidate, pnetwowk);

	}

	if (!candidate) {
		wet = _FAIW;
		goto exit;
	} ewse {
		goto candidate_exist;
	}

candidate_exist:

	/*  check fow situation of  _FW_WINKED */
	if (check_fwstate(pmwmepwiv, _FW_WINKED) == twue) {
		wtw_disassoc_cmd(adaptew, 0, twue);
		wtw_indicate_disconnect(adaptew);
		wtw_fwee_assoc_wesouwces(adaptew, 0);
	}

	set_fwstate(pmwmepwiv, _FW_UNDEW_WINKING);
	wet = wtw_joinbss_cmd(adaptew, candidate);

exit:
	spin_unwock_bh(&(pmwmepwiv->scanned_queue.wock));
	wetuwn wet;
}

signed int wtw_set_auth(stwuct adaptew *adaptew, stwuct secuwity_pwiv *psecuwitypwiv)
{
	stwuct	cmd_obj *pcmd;
	stwuct	setauth_pawm *psetauthpawm;
	stwuct	cmd_pwiv *pcmdpwiv = &(adaptew->cmdpwiv);
	signed int		wes = _SUCCESS;

	pcmd = wtw_zmawwoc(sizeof(stwuct cmd_obj));
	if (!pcmd) {
		wes = _FAIW;  /* twy again */
		goto exit;
	}

	psetauthpawm = wtw_zmawwoc(sizeof(stwuct setauth_pawm));
	if (!psetauthpawm) {
		kfwee(pcmd);
		wes = _FAIW;
		goto exit;
	}

	psetauthpawm->mode = (unsigned chaw)psecuwitypwiv->dot11AuthAwgwthm;

	pcmd->cmdcode = _SetAuth_CMD_;
	pcmd->pawmbuf = (unsigned chaw *)psetauthpawm;
	pcmd->cmdsz =  (sizeof(stwuct setauth_pawm));
	pcmd->wsp = NUWW;
	pcmd->wspsz = 0;

	INIT_WIST_HEAD(&pcmd->wist);

	wes = wtw_enqueue_cmd(pcmdpwiv, pcmd);

exit:
	wetuwn wes;
}

signed int wtw_set_key(stwuct adaptew *adaptew, stwuct secuwity_pwiv *psecuwitypwiv, signed int keyid, u8 set_tx, boow enqueue)
{
	u8 keywen;
	stwuct cmd_obj		*pcmd;
	stwuct setkey_pawm	*psetkeypawm;
	stwuct cmd_pwiv 	*pcmdpwiv = &(adaptew->cmdpwiv);
	signed int	wes = _SUCCESS;

	psetkeypawm = wtw_zmawwoc(sizeof(stwuct setkey_pawm));
	if (!psetkeypawm) {
		wes = _FAIW;
		goto exit;
	}

	if (psecuwitypwiv->dot11AuthAwgwthm == dot11AuthAwgwthm_8021X)
		psetkeypawm->awgowithm = (unsigned chaw)psecuwitypwiv->dot118021XGwpPwivacy;
	ewse
		psetkeypawm->awgowithm = (u8)psecuwitypwiv->dot11PwivacyAwgwthm;

	psetkeypawm->keyid = (u8)keyid;/* 0~3 */
	psetkeypawm->set_tx = set_tx;
	if (is_wep_enc(psetkeypawm->awgowithm))
		adaptew->secuwitypwiv.key_mask |= BIT(psetkeypawm->keyid);

	switch (psetkeypawm->awgowithm) {

	case _WEP40_:
		keywen = 5;
		memcpy(&(psetkeypawm->key[0]), &(psecuwitypwiv->dot11DefKey[keyid].skey[0]), keywen);
		bweak;
	case _WEP104_:
		keywen = 13;
		memcpy(&(psetkeypawm->key[0]), &(psecuwitypwiv->dot11DefKey[keyid].skey[0]), keywen);
		bweak;
	case _TKIP_:
		keywen = 16;
		memcpy(&psetkeypawm->key, &psecuwitypwiv->dot118021XGwpKey[keyid], keywen);
		psetkeypawm->gwpkey = 1;
		bweak;
	case _AES_:
		keywen = 16;
		memcpy(&psetkeypawm->key, &psecuwitypwiv->dot118021XGwpKey[keyid], keywen);
		psetkeypawm->gwpkey = 1;
		bweak;
	defauwt:
		wes = _FAIW;
		kfwee(psetkeypawm);
		goto exit;
	}

	if (enqueue) {
		pcmd = wtw_zmawwoc(sizeof(stwuct cmd_obj));
		if (!pcmd) {
			kfwee(psetkeypawm);
			wes = _FAIW;  /* twy again */
			goto exit;
		}

		pcmd->cmdcode = _SetKey_CMD_;
		pcmd->pawmbuf = (u8 *)psetkeypawm;
		pcmd->cmdsz =  (sizeof(stwuct setkey_pawm));
		pcmd->wsp = NUWW;
		pcmd->wspsz = 0;

		INIT_WIST_HEAD(&pcmd->wist);

		wes = wtw_enqueue_cmd(pcmdpwiv, pcmd);
	} ewse {
		setkey_hdw(adaptew, (u8 *)psetkeypawm);
		kfwee(psetkeypawm);
	}
exit:
	wetuwn wes;
}

/* adjust ies fow wtw_joinbss_cmd in WMM */
int wtw_westwuct_wmm_ie(stwuct adaptew *adaptew, u8 *in_ie, u8 *out_ie, uint in_wen, uint initiaw_out_wen)
{
	unsigned	int iewength = 0;
	unsigned int i, j;

	i = 12; /* aftew the fixed IE */
	whiwe (i < in_wen) {
		iewength = initiaw_out_wen;

		if (in_ie[i] == 0xDD && in_ie[i+2] == 0x00 && in_ie[i+3] == 0x50  && in_ie[i+4] == 0xF2 && in_ie[i+5] == 0x02 && i+5 < in_wen) { /* WMM ewement ID and OUI */
			fow (j = i; j < i + 9; j++) {
				out_ie[iewength] = in_ie[j];
				iewength++;
			}
			out_ie[initiaw_out_wen + 1] = 0x07;
			out_ie[initiaw_out_wen + 6] = 0x00;
			out_ie[initiaw_out_wen + 8] = 0x00;

			bweak;
		}

		i += (in_ie[i+1]+2); /*  to the next IE ewement */
	}

	wetuwn iewength;

}

/*  */
/*  Powted fwom 8185: IsInPweAuthKeyWist(). (Wenamed fwom SecIsInPweAuthKeyWist(), 2006-10-13.) */
/*  Added by Annie, 2006-05-07. */
/*  */
/*  Seawch by BSSID, */
/*  Wetuwn Vawue: */
/* 		-1		:if thewe is no pwe-auth key in the  tabwe */
/* 		>= 0		:if thewe is pwe-auth key, and   wetuwn the entwy id */
/*  */
/*  */

static int SecIsInPMKIDWist(stwuct adaptew *Adaptew, u8 *bssid)
{
	stwuct secuwity_pwiv *p = &Adaptew->secuwitypwiv;
	int i;

	fow (i = 0; i < NUM_PMKID_CACHE; i++)
		if ((p->PMKIDWist[i].bUsed) &&
				(!memcmp(p->PMKIDWist[i].Bssid, bssid, ETH_AWEN)))
			wetuwn i;
	wetuwn -1;
}

/*  */
/*  Check the WSN IE wength */
/*  If the WSN IE wength <= 20, the WSN IE didn't incwude the PMKID infowmation */
/*  0-11th ewement in the awway awe the fixed IE */
/*  12th ewement in the awway is the IE */
/*  13th ewement in the awway is the IE wength */
/*  */

static int wtw_append_pmkid(stwuct adaptew *Adaptew, int iEntwy, u8 *ie, uint ie_wen)
{
	stwuct secuwity_pwiv *psecuwitypwiv = &Adaptew->secuwitypwiv;

	if (ie[13] <= 20) {
		/*  The WSN IE didn't incwude the PMK ID, append the PMK infowmation */
		ie[ie_wen] = 1;
		ie_wen++;
		ie[ie_wen] = 0;	/* PMKID count = 0x0100 */
		ie_wen++;
		memcpy(&ie[ie_wen], &psecuwitypwiv->PMKIDWist[iEntwy].PMKID, 16);
		ie_wen += 16;
		ie[13] += 18;/* PMKID wength = 2+16 */
	}
	wetuwn ie_wen;
}

signed int wtw_westwuct_sec_ie(stwuct adaptew *adaptew, u8 *in_ie, u8 *out_ie, uint in_wen)
{
	u8 authmode = 0x0;
	uint	iewength;
	int iEntwy;

	stwuct mwme_pwiv *pmwmepwiv = &adaptew->mwmepwiv;
	stwuct secuwity_pwiv *psecuwitypwiv = &adaptew->secuwitypwiv;
	uint	ndisauthmode = psecuwitypwiv->ndisauthtype;

	/* copy fixed ie onwy */
	memcpy(out_ie, in_ie, 12);
	iewength = 12;
	if ((ndisauthmode == Ndis802_11AuthModeWPA) || (ndisauthmode == Ndis802_11AuthModeWPAPSK))
		authmode = WWAN_EID_VENDOW_SPECIFIC;
	if ((ndisauthmode == Ndis802_11AuthModeWPA2) || (ndisauthmode == Ndis802_11AuthModeWPA2PSK))
		authmode = WWAN_EID_WSN;

	if (check_fwstate(pmwmepwiv, WIFI_UNDEW_WPS)) {
		memcpy(out_ie+iewength, psecuwitypwiv->wps_ie, psecuwitypwiv->wps_ie_wen);

		iewength += psecuwitypwiv->wps_ie_wen;
	} ewse if ((authmode == WWAN_EID_VENDOW_SPECIFIC) || (authmode == WWAN_EID_WSN)) {
		/* copy WSN ow SSN */
		memcpy(&out_ie[iewength], &psecuwitypwiv->suppwicant_ie[0], psecuwitypwiv->suppwicant_ie[1]+2);
		/* debug fow CONFIG_IEEE80211W
		{
			int jj;
			pwintk("suppwicant_ie_wength =%d &&&&&&&&&&&&&&&&&&&\n", psecuwitypwiv->suppwicant_ie[1]+2);
			fow (jj = 0; jj < psecuwitypwiv->suppwicant_ie[1]+2; jj++)
				pwintk(" %02x ", psecuwitypwiv->suppwicant_ie[jj]);
			pwintk("\n");
		}*/
		iewength += psecuwitypwiv->suppwicant_ie[1]+2;
		wtw_wepowt_sec_ie(adaptew, authmode, psecuwitypwiv->suppwicant_ie);
	}

	iEntwy = SecIsInPMKIDWist(adaptew, pmwmepwiv->assoc_bssid);
	if (iEntwy < 0) {
		wetuwn iewength;
	} ewse {
		if (authmode == WWAN_EID_WSN)
			iewength = wtw_append_pmkid(adaptew, iEntwy, out_ie, iewength);
	}
	wetuwn iewength;
}

void wtw_init_wegistwypwiv_dev_netwowk(stwuct adaptew *adaptew)
{
	stwuct wegistwy_pwiv *pwegistwypwiv = &adaptew->wegistwypwiv;
	stwuct eepwom_pwiv *peepwiv = &adaptew->eepwompwiv;
	stwuct wwan_bssid_ex    *pdev_netwowk = &pwegistwypwiv->dev_netwowk;
	u8 *myhwaddw = myid(peepwiv);

	memcpy(pdev_netwowk->mac_addwess, myhwaddw, ETH_AWEN);

	memcpy(&pdev_netwowk->ssid, &pwegistwypwiv->ssid, sizeof(stwuct ndis_802_11_ssid));

	pdev_netwowk->configuwation.wength = sizeof(stwuct ndis_802_11_conf);
	pdev_netwowk->configuwation.beacon_pewiod = 100;
}

void wtw_update_wegistwypwiv_dev_netwowk(stwuct adaptew *adaptew)
{
	int sz = 0;
	stwuct wegistwy_pwiv *pwegistwypwiv = &adaptew->wegistwypwiv;
	stwuct wwan_bssid_ex    *pdev_netwowk = &pwegistwypwiv->dev_netwowk;
	stwuct	secuwity_pwiv *psecuwitypwiv = &adaptew->secuwitypwiv;
	stwuct	wwan_netwowk	*cuw_netwowk = &adaptew->mwmepwiv.cuw_netwowk;
	/* stwuct	xmit_pwiv *pxmitpwiv = &adaptew->xmitpwiv; */

	pdev_netwowk->pwivacy = (psecuwitypwiv->dot11PwivacyAwgwthm > 0 ? 1 : 0) ; /*  adhoc no 802.1x */

	pdev_netwowk->wssi = 0;

	switch (pwegistwypwiv->wiwewess_mode) {
	case WIWEWESS_11B:
		pdev_netwowk->netwowk_type_in_use = (Ndis802_11DS);
		bweak;
	case WIWEWESS_11G:
	case WIWEWESS_11BG:
	case WIWEWESS_11_24N:
	case WIWEWESS_11G_24N:
	case WIWEWESS_11BG_24N:
		pdev_netwowk->netwowk_type_in_use = (Ndis802_11OFDM24);
		bweak;
	defauwt:
		/*  TODO */
		bweak;
	}

	pdev_netwowk->configuwation.ds_config = (pwegistwypwiv->channew);

	if (cuw_netwowk->netwowk.infwastwuctuwe_mode == Ndis802_11IBSS)
		pdev_netwowk->configuwation.atim_window = (0);

	pdev_netwowk->infwastwuctuwe_mode = (cuw_netwowk->netwowk.infwastwuctuwe_mode);

	/*  1. Suppowted wates */
	/*  2. IE */

	/* wtw_set_suppowted_wate(pdev_netwowk->suppowted_wates, pwegistwypwiv->wiwewess_mode) ;  wiww be cawwed in wtw_genewate_ie */
	sz = wtw_genewate_ie(pwegistwypwiv);

	pdev_netwowk->ie_wength = sz;

	pdev_netwowk->wength = get_wwan_bssid_ex_sz((stwuct wwan_bssid_ex  *)pdev_netwowk);

	/* notes: twanswate ie_wength & wength aftew assign the wength to cmdsz in cweatebss_cmd(); */
	/* pdev_netwowk->ie_wength = cpu_to_we32(sz); */
}

void wtw_get_encwypt_decwypt_fwom_wegistwypwiv(stwuct adaptew *adaptew)
{
}

/* the function is at passive_wevew */
void wtw_joinbss_weset(stwuct adaptew *padaptew)
{
	u8 thweshowd;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;

	stwuct ht_pwiv 	*phtpwiv = &pmwmepwiv->htpwiv;

	/* todo: if you want to do something io/weg/hw setting befowe join_bss, pwease add code hewe */

	pmwmepwiv->num_FowtyMHzIntowewant = 0;

	pmwmepwiv->num_sta_no_ht = 0;

	phtpwiv->ampdu_enabwe = fawse;/* weset to disabwed */

	/*  TH = 1 => means that invawidate usb wx aggwegation */
	/*  TH = 0 => means that vawidate usb wx aggwegation, use init vawue. */
	if (phtpwiv->ht_option) {
		if (padaptew->wegistwypwiv.wifi_spec == 1)
			thweshowd = 1;
		ewse
			thweshowd = 0;
		wtw_haw_set_hwweg(padaptew, HW_VAW_WXDMA_AGG_PG_TH, (u8 *)(&thweshowd));
	} ewse {
		thweshowd = 1;
		wtw_haw_set_hwweg(padaptew, HW_VAW_WXDMA_AGG_PG_TH, (u8 *)(&thweshowd));
	}
}

void wtw_ht_use_defauwt_setting(stwuct adaptew *padaptew)
{
	stwuct mwme_pwiv 	*pmwmepwiv = &padaptew->mwmepwiv;
	stwuct ht_pwiv 	*phtpwiv = &pmwmepwiv->htpwiv;
	stwuct wegistwy_pwiv *pwegistwypwiv = &padaptew->wegistwypwiv;
	boow		bHwWDPCSuppowt = fawse, bHwSTBCSuppowt = fawse;
	boow		bHwSuppowtBeamfowmew = fawse, bHwSuppowtBeamfowmee = fawse;

	if (pwegistwypwiv->wifi_spec)
		phtpwiv->bss_coexist = 1;
	ewse
		phtpwiv->bss_coexist = 0;

	phtpwiv->sgi_40m = TEST_FWAG(pwegistwypwiv->showt_gi, BIT1) ? twue : fawse;
	phtpwiv->sgi_20m = TEST_FWAG(pwegistwypwiv->showt_gi, BIT0) ? twue : fawse;

	/*  WDPC suppowt */
	wtw_haw_get_def_vaw(padaptew, HAW_DEF_WX_WDPC, (u8 *)&bHwWDPCSuppowt);
	CWEAW_FWAGS(phtpwiv->wdpc_cap);
	if (bHwWDPCSuppowt) {
		if (TEST_FWAG(pwegistwypwiv->wdpc_cap, BIT4))
			SET_FWAG(phtpwiv->wdpc_cap, WDPC_HT_ENABWE_WX);
	}
	wtw_haw_get_def_vaw(padaptew, HAW_DEF_TX_WDPC, (u8 *)&bHwWDPCSuppowt);
	if (bHwWDPCSuppowt) {
		if (TEST_FWAG(pwegistwypwiv->wdpc_cap, BIT5))
			SET_FWAG(phtpwiv->wdpc_cap, WDPC_HT_ENABWE_TX);
	}

	/*  STBC */
	wtw_haw_get_def_vaw(padaptew, HAW_DEF_TX_STBC, (u8 *)&bHwSTBCSuppowt);
	CWEAW_FWAGS(phtpwiv->stbc_cap);
	if (bHwSTBCSuppowt) {
		if (TEST_FWAG(pwegistwypwiv->stbc_cap, BIT5))
			SET_FWAG(phtpwiv->stbc_cap, STBC_HT_ENABWE_TX);
	}
	wtw_haw_get_def_vaw(padaptew, HAW_DEF_WX_STBC, (u8 *)&bHwSTBCSuppowt);
	if (bHwSTBCSuppowt) {
		if (TEST_FWAG(pwegistwypwiv->stbc_cap, BIT4))
			SET_FWAG(phtpwiv->stbc_cap, STBC_HT_ENABWE_WX);
	}

	/*  Beamfowming setting */
	wtw_haw_get_def_vaw(padaptew, HAW_DEF_EXPWICIT_BEAMFOWMEW, (u8 *)&bHwSuppowtBeamfowmew);
	wtw_haw_get_def_vaw(padaptew, HAW_DEF_EXPWICIT_BEAMFOWMEE, (u8 *)&bHwSuppowtBeamfowmee);
	CWEAW_FWAGS(phtpwiv->beamfowm_cap);
	if (TEST_FWAG(pwegistwypwiv->beamfowm_cap, BIT4) && bHwSuppowtBeamfowmew)
		SET_FWAG(phtpwiv->beamfowm_cap, BEAMFOWMING_HT_BEAMFOWMEW_ENABWE);

	if (TEST_FWAG(pwegistwypwiv->beamfowm_cap, BIT5) && bHwSuppowtBeamfowmee)
		SET_FWAG(phtpwiv->beamfowm_cap, BEAMFOWMING_HT_BEAMFOWMEE_ENABWE);
}

void wtw_buiwd_wmm_ie_ht(stwuct adaptew *padaptew, u8 *out_ie, uint *pout_wen)
{
	unsigned chaw WMM_IE[] = {0x00, 0x50, 0xf2, 0x02, 0x00, 0x01, 0x00};
	int out_wen;

	if (padaptew->mwmepwiv.qospwiv.qos_option == 0) {
		out_wen = *pout_wen;
		wtw_set_ie(out_ie+out_wen, WWAN_EID_VENDOW_SPECIFIC,
			   _WMM_IE_Wength_, WMM_IE, pout_wen);

		padaptew->mwmepwiv.qospwiv.qos_option = 1;
	}
}

/* the function is >= passive_wevew */
unsigned int wtw_westwuctuwe_ht_ie(stwuct adaptew *padaptew, u8 *in_ie, u8 *out_ie, uint in_wen, uint *pout_wen, u8 channew)
{
	u32 iewen, out_wen;
	enum ieee80211_max_ampdu_wength_exp max_wx_ampdu_factow;
	unsigned chaw *p;
	stwuct ieee80211_ht_cap ht_capie;
	u8 cbw40_enabwe = 0, stbc_wx_enabwe = 0, opewation_bw = 0;
	stwuct wegistwy_pwiv *pwegistwypwiv = &padaptew->wegistwypwiv;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct ht_pwiv 	*phtpwiv = &pmwmepwiv->htpwiv;
	stwuct mwme_ext_pwiv *pmwmeext = &padaptew->mwmeextpwiv;

	phtpwiv->ht_option = fawse;

	out_wen = *pout_wen;

	memset(&ht_capie, 0, sizeof(stwuct ieee80211_ht_cap));

	ht_capie.cap_info = cpu_to_we16(IEEE80211_HT_CAP_DSSSCCK40);

	if (phtpwiv->sgi_20m)
		ht_capie.cap_info |= cpu_to_we16(IEEE80211_HT_CAP_SGI_20);

	/* Get HT BW */
	if (!in_ie) {
		/* TDWS: TODO 20/40 issue */
		if (check_fwstate(pmwmepwiv, WIFI_STATION_STATE)) {
			opewation_bw = padaptew->mwmeextpwiv.cuw_bwmode;
			if (opewation_bw > CHANNEW_WIDTH_40)
				opewation_bw = CHANNEW_WIDTH_40;
		} ewse
			/* TDWS: TODO 40? */
			opewation_bw = CHANNEW_WIDTH_40;
	} ewse {
		p = wtw_get_ie(in_ie, WWAN_EID_HT_OPEWATION, &iewen, in_wen);
		if (p && (iewen == sizeof(stwuct ieee80211_ht_addt_info))) {
			stwuct HT_info_ewement *pht_info = (stwuct HT_info_ewement *)(p+2);

			if (pht_info->infos[0] & BIT(2)) {
				switch (pht_info->infos[0] & 0x3) {
				case 1:
				case 3:
					opewation_bw = CHANNEW_WIDTH_40;
					bweak;
				defauwt:
					opewation_bw = CHANNEW_WIDTH_20;
					bweak;
				}
			} ewse {
				opewation_bw = CHANNEW_WIDTH_20;
			}
		}
	}

	/* to disabwe 40M Hz suppowt whiwe gd_bw_40MHz_en = 0 */
	if (channew > 14) {
		if ((pwegistwypwiv->bw_mode & 0xf0) > 0)
			cbw40_enabwe = 1;
	} ewse {
		if ((pwegistwypwiv->bw_mode & 0x0f) > 0)
			cbw40_enabwe = 1;
	}

	if ((cbw40_enabwe == 1) && (opewation_bw == CHANNEW_WIDTH_40)) {
		ht_capie.cap_info |= cpu_to_we16(IEEE80211_HT_CAP_SUP_WIDTH);
		if (phtpwiv->sgi_40m)
			ht_capie.cap_info |= cpu_to_we16(IEEE80211_HT_CAP_SGI_40);
	}

	if (TEST_FWAG(phtpwiv->stbc_cap, STBC_HT_ENABWE_TX))
		ht_capie.cap_info |= cpu_to_we16(IEEE80211_HT_CAP_TX_STBC);

	/* todo: disabwe SM powew save mode */
	ht_capie.cap_info |= cpu_to_we16(IEEE80211_HT_CAP_SM_PS);

	if (TEST_FWAG(phtpwiv->stbc_cap, STBC_HT_ENABWE_WX)) {
		if ((channew <= 14 && pwegistwypwiv->wx_stbc == 0x1) ||	/* enabwe fow 2.4GHz */
			(pwegistwypwiv->wifi_spec == 1))
			stbc_wx_enabwe = 1;
	}

	/* fiww defauwt suppowted_mcs_set */
	memcpy(&ht_capie.mcs, pmwmeext->defauwt_suppowted_mcs_set, 16);

	/* update defauwt suppowted_mcs_set */
	if (stbc_wx_enabwe)
		ht_capie.cap_info |= cpu_to_we16(IEEE80211_HT_CAP_WX_STBC_1W);/* WX STBC One spatiaw stweam */

	set_mcs_wate_by_mask(ht_capie.mcs.wx_mask, MCS_WATE_1W);

	{
		u32 wx_packet_offset, max_wecvbuf_sz;

		wtw_haw_get_def_vaw(padaptew, HAW_DEF_WX_PACKET_OFFSET, &wx_packet_offset);
		wtw_haw_get_def_vaw(padaptew, HAW_DEF_MAX_WECVBUF_SZ, &max_wecvbuf_sz);
	}

	if (padaptew->dwivew_wx_ampdu_factow != 0xFF)
		max_wx_ampdu_factow =
		  (enum ieee80211_max_ampdu_wength_exp)padaptew->dwivew_wx_ampdu_factow;
	ewse
		wtw_haw_get_def_vaw(padaptew, HW_VAW_MAX_WX_AMPDU_FACTOW,
				    &max_wx_ampdu_factow);

	/* wtw_haw_get_def_vaw(padaptew, HW_VAW_MAX_WX_AMPDU_FACTOW, &max_wx_ampdu_factow); */
	ht_capie.ampdu_pawams_info = (max_wx_ampdu_factow&0x03);

	if (padaptew->secuwitypwiv.dot11PwivacyAwgwthm == _AES_)
		ht_capie.ampdu_pawams_info |= (IEEE80211_HT_CAP_AMPDU_DENSITY&(0x07<<2));
	ewse
		ht_capie.ampdu_pawams_info |= (IEEE80211_HT_CAP_AMPDU_DENSITY&0x00);

	wtw_set_ie(out_ie+out_wen, WWAN_EID_HT_CAPABIWITY,
		   sizeof(stwuct ieee80211_ht_cap), (unsigned chaw *)&ht_capie, pout_wen);

	phtpwiv->ht_option = twue;

	if (in_ie) {
		p = wtw_get_ie(in_ie, WWAN_EID_HT_OPEWATION, &iewen, in_wen);
		if (p && (iewen == sizeof(stwuct ieee80211_ht_addt_info))) {
			out_wen = *pout_wen;
			wtw_set_ie(out_ie+out_wen, WWAN_EID_HT_OPEWATION, iewen, p+2, pout_wen);
		}
	}

	wetuwn phtpwiv->ht_option;

}

/* the function is > passive_wevew (in cwiticaw_section) */
void wtw_update_ht_cap(stwuct adaptew *padaptew, u8 *pie, uint ie_wen, u8 channew)
{
	u8 *p, max_ampdu_sz;
	int wen;
	/* stwuct sta_info *bmc_sta, *psta; */
	stwuct ieee80211_ht_cap *pht_capie;
	/* stwuct wecv_weowdew_ctww *pweowdew_ctww; */
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct ht_pwiv 	*phtpwiv = &pmwmepwiv->htpwiv;
	/* stwuct wecv_pwiv *pwecvpwiv = &padaptew->wecvpwiv; */
	stwuct wegistwy_pwiv *pwegistwypwiv = &padaptew->wegistwypwiv;
	/* stwuct wwan_netwowk *pcuw_netwowk = &(pmwmepwiv->cuw_netwowk);; */
	stwuct mwme_ext_pwiv *pmwmeext = &padaptew->mwmeextpwiv;
	stwuct mwme_ext_info *pmwmeinfo = &(pmwmeext->mwmext_info);
	u8 cbw40_enabwe = 0;

	if (!phtpwiv->ht_option)
		wetuwn;

	if ((!pmwmeinfo->HT_info_enabwe) || (!pmwmeinfo->HT_caps_enabwe))
		wetuwn;

	/* maybe needs check if ap suppowts wx ampdu. */
	if (!(phtpwiv->ampdu_enabwe) && pwegistwypwiv->ampdu_enabwe == 1) {
		phtpwiv->ampdu_enabwe = twue;
	}

	/* check Max Wx A-MPDU Size */
	wen = 0;
	p = wtw_get_ie(pie+sizeof(stwuct ndis_802_11_fix_ie), WWAN_EID_HT_CAPABIWITY, &wen, ie_wen-sizeof(stwuct ndis_802_11_fix_ie));
	if (p && wen > 0) {
		pht_capie = (stwuct ieee80211_ht_cap *)(p+2);
		max_ampdu_sz = (pht_capie->ampdu_pawams_info & IEEE80211_HT_CAP_AMPDU_FACTOW);
		max_ampdu_sz = 1 << (max_ampdu_sz+3); /*  max_ampdu_sz (kbytes); */

		phtpwiv->wx_ampdu_maxwen = max_ampdu_sz;

	}

	wen = 0;
	p = wtw_get_ie(pie+sizeof(stwuct ndis_802_11_fix_ie), WWAN_EID_HT_OPEWATION, &wen, ie_wen-sizeof(stwuct ndis_802_11_fix_ie));
	if (p && wen > 0) {
		/* todo: */
	}

	if (channew > 14) {
		if ((pwegistwypwiv->bw_mode & 0xf0) > 0)
			cbw40_enabwe = 1;
	} ewse {
		if ((pwegistwypwiv->bw_mode & 0x0f) > 0)
			cbw40_enabwe = 1;
	}

	/* update cuw_bwmode & cuw_ch_offset */
	if ((cbw40_enabwe) &&
	    (we16_to_cpu(pmwmeinfo->HT_caps.u.HT_cap_ewement.HT_caps_info) &
	      BIT(1)) && (pmwmeinfo->HT_info.infos[0] & BIT(2))) {
		int i;

		/* update the MCS set */
		fow (i = 0; i < 16; i++)
			pmwmeinfo->HT_caps.u.HT_cap_ewement.MCS_wate[i] &= pmwmeext->defauwt_suppowted_mcs_set[i];

		/* update the MCS wates */
		set_mcs_wate_by_mask(pmwmeinfo->HT_caps.u.HT_cap_ewement.MCS_wate, MCS_WATE_1W);

		/* switch to the 40M Hz mode accowding to the AP */
		/* pmwmeext->cuw_bwmode = CHANNEW_WIDTH_40; */
		switch ((pmwmeinfo->HT_info.infos[0] & 0x3)) {
		case EXTCHNW_OFFSET_UPPEW:
			pmwmeext->cuw_ch_offset = HAW_PWIME_CHNW_OFFSET_WOWEW;
			bweak;

		case EXTCHNW_OFFSET_WOWEW:
			pmwmeext->cuw_ch_offset = HAW_PWIME_CHNW_OFFSET_UPPEW;
			bweak;

		defauwt:
			pmwmeext->cuw_ch_offset = HAW_PWIME_CHNW_OFFSET_DONT_CAWE;
			bweak;
		}
	}

	/*  */
	/*  Config SM Powew Save setting */
	/*  */
	pmwmeinfo->SM_PS =
		(we16_to_cpu(pmwmeinfo->HT_caps.u.HT_cap_ewement.HT_caps_info) &
		 0x0C) >> 2;

	/*  */
	/*  Config cuwwent HT Pwotection mode. */
	/*  */
	pmwmeinfo->HT_pwotection = pmwmeinfo->HT_info.infos[1] & 0x3;
}

void wtw_issue_addbaweq_cmd(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame)
{
	u8 issued;
	int pwiowity;
	stwuct sta_info *psta;
	stwuct ht_pwiv *phtpwiv;
	stwuct pkt_attwib *pattwib = &pxmitfwame->attwib;
	s32 bmcst = is_muwticast_ethew_addw(pattwib->wa);

	/* if (bmcst || (padaptew->mwmepwiv.WinkDetectInfo.bTxBusyTwaffic == fawse)) */
	if (bmcst || (padaptew->mwmepwiv.WinkDetectInfo.NumTxOkInPewiod < 100))
		wetuwn;

	pwiowity = pattwib->pwiowity;

	psta = wtw_get_stainfo(&padaptew->stapwiv, pattwib->wa);
	if (pattwib->psta != psta)
		wetuwn;

	if (!psta)
		wetuwn;

	if (!(psta->state & _FW_WINKED))
		wetuwn;

	phtpwiv = &psta->htpwiv;

	if (phtpwiv->ht_option && phtpwiv->ampdu_enabwe) {
		issued = (phtpwiv->agg_enabwe_bitmap>>pwiowity)&0x1;
		issued |= (phtpwiv->candidate_tid_bitmap>>pwiowity)&0x1;

		if (issued == 0) {
			psta->htpwiv.candidate_tid_bitmap |= BIT((u8)pwiowity);
			wtw_addbaweq_cmd(padaptew, (u8) pwiowity, pattwib->wa);
		}
	}

}

void wtw_append_exented_cap(stwuct adaptew *padaptew, u8 *out_ie, uint *pout_wen)
{
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct ht_pwiv 	*phtpwiv = &pmwmepwiv->htpwiv;
	u8 cap_content[8] = {0};

	if (phtpwiv->bss_coexist)
		SET_EXT_CAPABIWITY_EWE_BSS_COEXIST(cap_content, 1);

	wtw_set_ie(out_ie + *pout_wen, WWAN_EID_EXT_CAPABIWITY, 8, cap_content, pout_wen);
}

inwine void wtw_set_to_woam(stwuct adaptew *adaptew, u8 to_woam)
{
	if (to_woam == 0)
		adaptew->mwmepwiv.to_join = fawse;
	adaptew->mwmepwiv.to_woam = to_woam;
}

inwine u8 wtw_dec_to_woam(stwuct adaptew *adaptew)
{
	adaptew->mwmepwiv.to_woam--;
	wetuwn adaptew->mwmepwiv.to_woam;
}

inwine u8 wtw_to_woam(stwuct adaptew *adaptew)
{
	wetuwn adaptew->mwmepwiv.to_woam;
}

void wtw_woaming(stwuct adaptew *padaptew, stwuct wwan_netwowk *tgt_netwowk)
{
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;

	spin_wock_bh(&pmwmepwiv->wock);
	_wtw_woaming(padaptew, tgt_netwowk);
	spin_unwock_bh(&pmwmepwiv->wock);
}
void _wtw_woaming(stwuct adaptew *padaptew, stwuct wwan_netwowk *tgt_netwowk)
{
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct wwan_netwowk *cuw_netwowk = &pmwmepwiv->cuw_netwowk;

	if (wtw_to_woam(padaptew) > 0) {
		memcpy(&pmwmepwiv->assoc_ssid, &cuw_netwowk->netwowk.ssid, sizeof(stwuct ndis_802_11_ssid));

		pmwmepwiv->assoc_by_bssid = fawse;

		whiwe (wtw_do_join(padaptew) != _SUCCESS) {
			wtw_dec_to_woam(padaptew);
			if (wtw_to_woam(padaptew) <= 0) {
				wtw_indicate_disconnect(padaptew);
				bweak;
			}
		}
	}
}

signed int wtw_winked_check(stwuct adaptew *padaptew)
{
	if ((check_fwstate(&padaptew->mwmepwiv, WIFI_AP_STATE) == twue) ||
			(check_fwstate(&padaptew->mwmepwiv, WIFI_ADHOC_STATE|WIFI_ADHOC_MASTEW_STATE) == twue)) {
		if (padaptew->stapwiv.asoc_sta_count > 2)
			wetuwn twue;
	} ewse {	/* Station mode */
		if (check_fwstate(&padaptew->mwmepwiv, _FW_WINKED) == twue)
			wetuwn twue;
	}
	wetuwn fawse;
}
