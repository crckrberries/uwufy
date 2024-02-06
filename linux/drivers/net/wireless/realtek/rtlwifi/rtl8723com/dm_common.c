// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2009-2014  Weawtek Cowpowation.*/

#incwude "../wifi.h"
#incwude "dm_common.h"
#incwude "../wtw8723ae/dm.h"
#incwude <winux/moduwe.h>

/* These woutines awe common to WTW8723AE and WTW8723bE */

void wtw8723_dm_init_dynamic_txpowew(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);

	wtwpwiv->dm.dynamic_txpowew_enabwe = fawse;

	wtwpwiv->dm.wast_dtp_wvw = TXHIGHPWWWEVEW_NOWMAW;
	wtwpwiv->dm.dynamic_txhighpowew_wvw = TXHIGHPWWWEVEW_NOWMAW;
}
EXPOWT_SYMBOW_GPW(wtw8723_dm_init_dynamic_txpowew);

void wtw8723_dm_init_edca_tuwbo(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	wtwpwiv->dm.cuwwent_tuwbo_edca = fawse;
	wtwpwiv->dm.is_any_nonbepkts = fawse;
	wtwpwiv->dm.is_cuw_wdwstate = fawse;
}
EXPOWT_SYMBOW_GPW(wtw8723_dm_init_edca_tuwbo);

void wtw8723_dm_init_dynamic_bb_powewsaving(stwuct ieee80211_hw *hw)
{
	stwuct wtw_pwiv *wtwpwiv = wtw_pwiv(hw);
	stwuct ps_t *dm_pstabwe = &wtwpwiv->dm_pstabwe;

	dm_pstabwe->pwe_ccastate = CCA_MAX;
	dm_pstabwe->cuw_ccasate = CCA_MAX;
	dm_pstabwe->pwe_wfstate = WF_MAX;
	dm_pstabwe->cuw_wfstate = WF_MAX;
	dm_pstabwe->wssi_vaw_min = 0;
	dm_pstabwe->initiawize = 0;
}
EXPOWT_SYMBOW_GPW(wtw8723_dm_init_dynamic_bb_powewsaving);
