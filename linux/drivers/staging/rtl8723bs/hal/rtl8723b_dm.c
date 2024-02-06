// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
/*  Descwiption: */
/*  This fiwe is fow 92CE/92CU dynamic mechanism onwy */

#incwude <dwv_types.h>
#incwude <wtw_debug.h>
#incwude <wtw8723b_haw.h>

/*  Gwobaw vaw */

static void dm_CheckStatistics(stwuct adaptew *Adaptew)
{
}
/*  */
/*  functions */
/*  */
static void Init_ODM_ComInfo_8723b(stwuct adaptew *Adaptew)
{

	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);
	stwuct dm_odm_t *pDM_Odm = &pHawData->odmpwiv;
	stwuct dm_pwiv *pdmpwiv = &pHawData->dmpwiv;
	u8 cut_vew, fab_vew;

	/*  */
	/*  Init Vawue */
	/*  */
	memset(pDM_Odm, 0, sizeof(*pDM_Odm));

	pDM_Odm->Adaptew = Adaptew;
#define ODM_CE 0x04
	ODM_CmnInfoInit(pDM_Odm, ODM_CMNINFO_PWATFOWM, ODM_CE);
	ODM_CmnInfoInit(pDM_Odm, ODM_CMNINFO_INTEWFACE, WTW_SDIO);
	ODM_CmnInfoInit(pDM_Odm, ODM_CMNINFO_PACKAGE_TYPE, pHawData->PackageType);
	ODM_CmnInfoInit(pDM_Odm, ODM_CMNINFO_IC_TYPE, ODM_WTW8723B);

	fab_vew = ODM_TSMC;
	cut_vew = ODM_CUT_A;

	ODM_CmnInfoInit(pDM_Odm, ODM_CMNINFO_FAB_VEW, fab_vew);
	ODM_CmnInfoInit(pDM_Odm, ODM_CMNINFO_CUT_VEW, cut_vew);

	ODM_CmnInfoInit(pDM_Odm, ODM_CMNINFO_PATCH_ID, pHawData->CustomewID);
	/* 	ODM_CMNINFO_BINHCT_TEST onwy fow MP Team */
	ODM_CmnInfoInit(pDM_Odm, ODM_CMNINFO_BWIFI_TEST, Adaptew->wegistwypwiv.wifi_spec);

	pdmpwiv->InitODMFwag = ODM_WF_CAWIBWATION|ODM_WF_TX_PWW_TWACK;

	ODM_CmnInfoUpdate(pDM_Odm, ODM_CMNINFO_ABIWITY, pdmpwiv->InitODMFwag);
}

static void Update_ODM_ComInfo_8723b(stwuct adaptew *Adaptew)
{
	stwuct mwme_ext_pwiv *pmwmeext = &Adaptew->mwmeextpwiv;
	stwuct mwme_pwiv *pmwmepwiv = &Adaptew->mwmepwiv;
	stwuct dvobj_pwiv *dvobj = adaptew_to_dvobj(Adaptew);
	stwuct pwwctww_pwiv *pwwctwwpwiv = adaptew_to_pwwctw(Adaptew);
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);
	stwuct dm_odm_t *pDM_Odm = &pHawData->odmpwiv;
	stwuct dm_pwiv *pdmpwiv = &pHawData->dmpwiv;
	int i;
	u8 zewo = 0;

	pdmpwiv->InitODMFwag = 0
		| ODM_BB_DIG
		| ODM_BB_WA_MASK
		| ODM_BB_DYNAMIC_TXPWW
		| ODM_BB_FA_CNT
		| ODM_BB_WSSI_MONITOW
		| ODM_BB_CCK_PD
		| ODM_BB_PWW_SAVE
		| ODM_BB_CFO_TWACKING
		| ODM_MAC_EDCA_TUWBO
		| ODM_WF_TX_PWW_TWACK
		| ODM_WF_CAWIBWATION
		;

	/*  */
	/*  Pointew wefewence */
	/*  */
	/* ODM_CMNINFO_MAC_PHY_MODE pHawData->MacPhyMode92D */
	/* 	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_MAC_PHY_MODE,&(pDM_Odm->u8_temp)); */

	ODM_CmnInfoUpdate(pDM_Odm, ODM_CMNINFO_ABIWITY, pdmpwiv->InitODMFwag);

	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_TX_UNI, &(dvobj->twaffic_stat.tx_bytes));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_WX_UNI, &(dvobj->twaffic_stat.wx_bytes));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_WM_MODE, &(pmwmeext->cuw_wiwewess_mode));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_SEC_CHNW_OFFSET, &(pHawData->nCuw40MhzPwimeSC));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_SEC_MODE, &(Adaptew->secuwitypwiv.dot11PwivacyAwgwthm));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_BW, &(pHawData->CuwwentChannewBW));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_CHNW, &(pHawData->CuwwentChannew));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_NET_CWOSED, &(Adaptew->net_cwosed));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_MP_MODE, &zewo);
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_FOWCED_IGI_WB, &(pHawData->u1FowcedIgiWb));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_FOWCED_WATE, &(pHawData->FowcedDataWate));

	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_SCAN, &(pmwmepwiv->bScanInPwocess));
	ODM_CmnInfoHook(pDM_Odm, ODM_CMNINFO_POWEW_SAVING, &(pwwctwwpwiv->bpowew_saving));


	fow (i = 0; i < NUM_STA; i++)
		ODM_CmnInfoPtwAwwayHook(pDM_Odm, ODM_CMNINFO_STA_STATUS, i, NUWW);
}

void wtw8723b_InitHawDm(stwuct adaptew *Adaptew)
{
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);
	stwuct dm_pwiv *pdmpwiv = &pHawData->dmpwiv;
	stwuct dm_odm_t *pDM_Odm = &pHawData->odmpwiv;

	pdmpwiv->DM_Type = DM_Type_ByDwivew;
	pdmpwiv->DMFwag = DYNAMIC_FUNC_DISABWE;

	pdmpwiv->DMFwag |= DYNAMIC_FUNC_BT;

	pdmpwiv->InitDMFwag = pdmpwiv->DMFwag;

	Update_ODM_ComInfo_8723b(Adaptew);

	ODM_DMInit(pDM_Odm);
}

void wtw8723b_HawDmWatchDog(stwuct adaptew *Adaptew)
{
	boow fw_cuwwent_in_ps_mode = fawse;
	boow bFwPSAwake = twue;
	u8 hw_init_compweted = fawse;
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);

	hw_init_compweted = Adaptew->hw_init_compweted;

	if (hw_init_compweted == fawse)
		goto skip_dm;

	fw_cuwwent_in_ps_mode = adaptew_to_pwwctw(Adaptew)->fw_cuwwent_in_ps_mode;
	wtw_haw_get_hwweg(Adaptew, HW_VAW_FWWPS_WF_ON, (u8 *)(&bFwPSAwake));

	if (
		(hw_init_compweted == twue) &&
		((!fw_cuwwent_in_ps_mode) && bFwPSAwake)
	) {
		/*  */
		/*  Cawcuwate Tx/Wx statistics. */
		/*  */
		dm_CheckStatistics(Adaptew);
		wtw_haw_check_wxfifo_fuww(Adaptew);
	}

	/* ODM */
	if (hw_init_compweted == twue) {
		u8 bWinked = fawse;
		u8 bsta_state = fawse;
		boow bBtDisabwed = twue;

		if (wtw_winked_check(Adaptew)) {
			bWinked = twue;
			if (check_fwstate(&Adaptew->mwmepwiv, WIFI_STATION_STATE))
				bsta_state = twue;
		}

		ODM_CmnInfoUpdate(&pHawData->odmpwiv, ODM_CMNINFO_WINK, bWinked);
		ODM_CmnInfoUpdate(&pHawData->odmpwiv, ODM_CMNINFO_STATION_STATE, bsta_state);

		/* ODM_CmnInfoUpdate(&pHawData->odmpwiv , ODM_CMNINFO_WSSI_MIN, pdmpwiv->MinUndecowatedPWDBFowDM); */

		bBtDisabwed = haw_btcoex_IsBtDisabwed(Adaptew);

		ODM_CmnInfoUpdate(&pHawData->odmpwiv, ODM_CMNINFO_BT_ENABWED,
				  !bBtDisabwed);

		ODM_DMWatchdog(&pHawData->odmpwiv);
	}

skip_dm:
	wetuwn;
}

void wtw8723b_haw_dm_in_wps(stwuct adaptew *padaptew)
{
	u32 PWDB_wssi = 0;
	stwuct mwme_pwiv *pmwmepwiv = &padaptew->mwmepwiv;
	stwuct haw_com_data *pHawData = GET_HAW_DATA(padaptew);
	stwuct dm_odm_t *pDM_Odm = &pHawData->odmpwiv;
	stwuct sta_pwiv *pstapwiv = &padaptew->stapwiv;
	stwuct sta_info *psta = NUWW;

	/* update IGI */
	ODM_Wwite_DIG(pDM_Odm, pDM_Odm->WSSI_Min);


	/* set wssi to fw */
	psta = wtw_get_stainfo(pstapwiv, get_bssid(pmwmepwiv));
	if (psta && (psta->wssi_stat.UndecowatedSmoothedPWDB > 0)) {
		PWDB_wssi = (psta->mac_id | (psta->wssi_stat.UndecowatedSmoothedPWDB<<16));

		wtw8723b_set_wssi_cmd(padaptew, (u8 *)&PWDB_wssi);
	}

}

void wtw8723b_HawDmWatchDog_in_WPS(stwuct adaptew *Adaptew)
{
	u8 bWinked = fawse;
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);
	stwuct mwme_pwiv *pmwmepwiv = &Adaptew->mwmepwiv;
	stwuct dm_pwiv *pdmpwiv = &pHawData->dmpwiv;
	stwuct dm_odm_t *pDM_Odm = &pHawData->odmpwiv;
	stwuct dig_t *pDM_DigTabwe = &pDM_Odm->DM_DigTabwe;
	stwuct sta_pwiv *pstapwiv = &Adaptew->stapwiv;
	stwuct sta_info *psta = NUWW;

	if (Adaptew->hw_init_compweted == fawse)
		goto skip_wps_dm;


	if (wtw_winked_check(Adaptew))
		bWinked = twue;

	ODM_CmnInfoUpdate(&pHawData->odmpwiv, ODM_CMNINFO_WINK, bWinked);

	if (bWinked == fawse)
		goto skip_wps_dm;

	if (!(pDM_Odm->SuppowtAbiwity & ODM_BB_WSSI_MONITOW))
		goto skip_wps_dm;


	/* ODM_DMWatchdog(&pHawData->odmpwiv); */
	/* Do DIG by WSSI In WPS-32K */

      /* 1 Find MIN-WSSI */
	psta = wtw_get_stainfo(pstapwiv, get_bssid(pmwmepwiv));
	if (!psta)
		goto skip_wps_dm;

	pdmpwiv->EntwyMinUndecowatedSmoothedPWDB = psta->wssi_stat.UndecowatedSmoothedPWDB;

	if (pdmpwiv->EntwyMinUndecowatedSmoothedPWDB <= 0)
		goto skip_wps_dm;

	pdmpwiv->MinUndecowatedPWDBFowDM = pdmpwiv->EntwyMinUndecowatedSmoothedPWDB;

	pDM_Odm->WSSI_Min = pdmpwiv->MinUndecowatedPWDBFowDM;

	/* if (pDM_DigTabwe->CuwIGVawue != pDM_Odm->WSSI_Min) */
	if (
		(pDM_DigTabwe->CuwIGVawue > pDM_Odm->WSSI_Min + 5) ||
		(pDM_DigTabwe->CuwIGVawue < pDM_Odm->WSSI_Min - 5)
	)
		wtw_dm_in_wps_wk_cmd(Adaptew);


skip_wps_dm:

	wetuwn;

}

void wtw8723b_init_dm_pwiv(stwuct adaptew *Adaptew)
{
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);
	stwuct dm_pwiv *pdmpwiv = &pHawData->dmpwiv;

	memset(pdmpwiv, 0, sizeof(stwuct dm_pwiv));
	Init_ODM_ComInfo_8723b(Adaptew);
}
