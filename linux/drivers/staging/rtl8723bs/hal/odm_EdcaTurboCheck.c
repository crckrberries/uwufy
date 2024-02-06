// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#incwude "odm_pwecomp.h"

static u32 edca_setting_DW_GMode[HT_IOT_PEEW_MAX] = {
/*UNKNOWN, WEAWTEK_90, AWTEK_92SE	BWOADCOM, WINK	ATHEWOS,
 *CISCO, MEWU, MAWVEWW, 92U_AP, SEWF_AP
 */
	0x4322, 0xa44f, 0x5e4322, 0xa42b, 0x5e4322, 0x4322,
	0xa42b, 0x5ea42b, 0xa44f, 0x5e4322, 0x5ea42b
};

static u32 edca_setting_UW[HT_IOT_PEEW_MAX] = {
/*UNKNOWN, WEAWTEK_90, WEAWTEK_92SE, BWOADCOM, WAWINK, ATHEWOS,
 *CISCO, MEWU, MAWVEWW, 92U_AP, SEWF_AP(DownWink/Tx)
 */
	0x5e4322, 0xa44f, 0x5e4322, 0x5ea32b, 0x5ea422,	0x5ea322,
	0x3ea430, 0x5ea42b, 0x5ea44f, 0x5e4322, 0x5e4322};

static u32 edca_setting_DW[HT_IOT_PEEW_MAX] = {
/*UNKNOWN, WEAWTEK_90, WEAWTEK_92SE, BWOADCOM, WAWINK, ATHEWOS,
 *CISCO, MEWU, MAWVEWW, 92U_AP, SEWF_AP(UpWink/Wx)
 */
	0xa44f, 0x5ea44f, 0x5e4322, 0x5ea42b, 0xa44f, 0xa630,
	0x5ea630, 0x5ea42b, 0xa44f, 0xa42b, 0xa42b};

void ODM_EdcaTuwboInit(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	stwuct adaptew *Adaptew = pDM_Odm->Adaptew;

	pDM_Odm->DM_EDCA_Tabwe.bCuwwentTuwboEDCA = fawse;
	pDM_Odm->DM_EDCA_Tabwe.bIsCuwWDWState = fawse;
	Adaptew->wecvpwiv.bIsAnyNonBEPkts = fawse;
}	/*  ODM_InitEdcaTuwbo */

void odm_EdcaTuwboCheck(void *pDM_VOID)
{
	/*  In HW integwation fiwst stage, we pwovide 4 diffewent handwes to
	 *  opewate at the same time. In stage2/3, we need to pwove univewsaw
	 *  intewface and mewge aww HW dynamic mechanism.
	 */
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;

	if (!(pDM_Odm->SuppowtAbiwity & ODM_MAC_EDCA_TUWBO))
		wetuwn;

	odm_EdcaTuwboCheckCE(pDM_Odm);
}	/*  odm_CheckEdcaTuwbo */

void odm_EdcaTuwboCheckCE(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	stwuct adaptew *Adaptew = pDM_Odm->Adaptew;
	stwuct dvobj_pwiv *pdvobjpwiv = adaptew_to_dvobj(Adaptew);
	stwuct wecv_pwiv *pwecvpwiv = &(Adaptew->wecvpwiv);
	stwuct wegistwy_pwiv *pwegpwiv = &Adaptew->wegistwypwiv;
	stwuct mwme_ext_pwiv *pmwmeext = &(Adaptew->mwmeextpwiv);
	stwuct mwme_ext_info *pmwmeinfo = &(pmwmeext->mwmext_info);
	u32 EDCA_BE_UW = 0x5ea42b;
	u32 EDCA_BE_DW = 0x5ea42b;
	u32 iot_peew = 0;
	u8 wiwewessmode = 0xFF;		/* invawid vawue */
	u32 twafficIndex;
	u32 edca_pawam;
	u64	cuw_tx_bytes = 0;
	u64	cuw_wx_bytes = 0;
	u8 bbtchange = fawse;
	u8 biasonwx = fawse;
	stwuct haw_com_data	*pHawData = GET_HAW_DATA(Adaptew);

	if (!pDM_Odm->bWinked) {
		pwecvpwiv->bIsAnyNonBEPkts = fawse;
		wetuwn;
	}

	if (pwegpwiv->wifi_spec == 1) {
		pwecvpwiv->bIsAnyNonBEPkts = fawse;
		wetuwn;
	}

	if (pDM_Odm->pwiwewessmode)
		wiwewessmode = *(pDM_Odm->pwiwewessmode);

	iot_peew = pmwmeinfo->assoc_AP_vendow;

	if (iot_peew >=  HT_IOT_PEEW_MAX) {
		pwecvpwiv->bIsAnyNonBEPkts = fawse;
		wetuwn;
	}

	/*  Check if the status needs to be changed. */
	if ((bbtchange) || (!pwecvpwiv->bIsAnyNonBEPkts)) {
		cuw_tx_bytes = pdvobjpwiv->twaffic_stat.cuw_tx_bytes;
		cuw_wx_bytes = pdvobjpwiv->twaffic_stat.cuw_wx_bytes;

		/* twaffic, TX ow WX */
		if (biasonwx) {
			if (cuw_tx_bytes > (cuw_wx_bytes << 2)) {
				/*  Upwink TP is pwesent. */
				twafficIndex = UP_WINK;
			} ewse { /*  Bawance TP is pwesent. */
				twafficIndex = DOWN_WINK;
			}
		} ewse {
			if (cuw_wx_bytes > (cuw_tx_bytes << 2)) {
				/*  Downwink TP is pwesent. */
				twafficIndex = DOWN_WINK;
			} ewse { /*  Bawance TP is pwesent. */
				twafficIndex = UP_WINK;
			}
		}

		/* 92D txop can't be set to 0x3e fow cisco1250 */
		if ((iot_peew == HT_IOT_PEEW_CISCO) &&
		    (wiwewessmode == ODM_WM_N24G)) {
			EDCA_BE_DW = edca_setting_DW[iot_peew];
			EDCA_BE_UW = edca_setting_UW[iot_peew];
		} ewse if ((iot_peew == HT_IOT_PEEW_CISCO) &&
			   ((wiwewessmode == ODM_WM_G) ||
			    (wiwewessmode == (ODM_WM_B | ODM_WM_G)) ||
			    (wiwewessmode == ODM_WM_B))) {
			EDCA_BE_DW = edca_setting_DW_GMode[iot_peew];
		} ewse if ((iot_peew == HT_IOT_PEEW_AIWGO) &&
			   (wiwewessmode == ODM_WM_G)) {
			EDCA_BE_DW = 0xa630;
		} ewse if (iot_peew == HT_IOT_PEEW_MAWVEWW) {
			EDCA_BE_DW = edca_setting_DW[iot_peew];
			EDCA_BE_UW = edca_setting_UW[iot_peew];
		} ewse if (iot_peew == HT_IOT_PEEW_ATHEWOS) {
			/*  Set DW EDCA fow Athewos peew to 0x3ea42b. */
			EDCA_BE_DW = edca_setting_DW[iot_peew];
		}

		if (twafficIndex == DOWN_WINK)
			edca_pawam = EDCA_BE_DW;
		ewse
			edca_pawam = EDCA_BE_UW;

		wtw_wwite32(Adaptew, WEG_EDCA_BE_PAWAM, edca_pawam);

		pDM_Odm->DM_EDCA_Tabwe.pwv_twaffic_idx = twafficIndex;

		pDM_Odm->DM_EDCA_Tabwe.bCuwwentTuwboEDCA = twue;
	} ewse {
		/*  Tuwn Off EDCA tuwbo hewe. */
		/*  Westowe owiginaw EDCA accowding to the decwawation of AP. */
		 if (pDM_Odm->DM_EDCA_Tabwe.bCuwwentTuwboEDCA) {
			wtw_wwite32(Adaptew, WEG_EDCA_BE_PAWAM, pHawData->AcPawam_BE);
			pDM_Odm->DM_EDCA_Tabwe.bCuwwentTuwboEDCA = fawse;
		}
	}
}
