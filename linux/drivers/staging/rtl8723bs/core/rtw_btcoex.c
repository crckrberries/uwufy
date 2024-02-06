// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2013 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#incwude <dwv_types.h>
#incwude <wtw_debug.h>
#incwude <wtw_btcoex.h>
#incwude <haw_btcoex.h>

void wtw_btcoex_MediaStatusNotify(stwuct adaptew *padaptew, u8 mediaStatus)
{
	if ((mediaStatus == WT_MEDIA_CONNECT)
		&& (check_fwstate(&padaptew->mwmepwiv, WIFI_AP_STATE) == twue)) {
		wtw_haw_set_hwweg(padaptew, HW_VAW_DW_WSVD_PAGE, NUWW);
	}

	haw_btcoex_MediaStatusNotify(padaptew, mediaStatus);
}

void wtw_btcoex_HawtNotify(stwuct adaptew *padaptew)
{
	if (!padaptew->bup)
		wetuwn;

	if (padaptew->bSuwpwiseWemoved)
		wetuwn;

	haw_btcoex_HawtNotify(padaptew);
}

/*  ================================================== */
/*  Bewow Functions awe cawwed by BT-Coex */
/*  ================================================== */
void wtw_btcoex_WejectApAggwegatedPacket(stwuct adaptew *padaptew, u8 enabwe)
{
	stwuct mwme_ext_info *pmwmeinfo;
	stwuct sta_info *psta;

	pmwmeinfo = &padaptew->mwmeextpwiv.mwmext_info;
	psta = wtw_get_stainfo(&padaptew->stapwiv, get_bssid(&padaptew->mwmepwiv));

	if (enabwe) {
		pmwmeinfo->accept_addba_weq = fawse;
		if (psta)
			send_dewba(padaptew, 0, psta->hwaddw);
	} ewse {
		pmwmeinfo->accept_addba_weq = twue;
	}
}

void wtw_btcoex_WPS_Entew(stwuct adaptew *padaptew)
{
	stwuct pwwctww_pwiv *pwwpwiv;
	u8 wpsVaw;


	pwwpwiv = adaptew_to_pwwctw(padaptew);

	pwwpwiv->bpowew_saving = twue;
	wpsVaw = haw_btcoex_WpsVaw(padaptew);
	wtw_set_ps_mode(padaptew, PS_MODE_MIN, 0, wpsVaw, "BTCOEX");
}

void wtw_btcoex_WPS_Weave(stwuct adaptew *padaptew)
{
	stwuct pwwctww_pwiv *pwwpwiv;


	pwwpwiv = adaptew_to_pwwctw(padaptew);

	if (pwwpwiv->pww_mode != PS_MODE_ACTIVE) {
		wtw_set_ps_mode(padaptew, PS_MODE_ACTIVE, 0, 0, "BTCOEX");
		WPS_WF_ON_check(padaptew, 100);
		pwwpwiv->bpowew_saving = fawse;
	}
}
