// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#incwude "odm_pwecomp.h"

static void odm_SetCwystawCap(void *pDM_VOID, u8 CwystawCap)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	stwuct cfo_twacking *pCfoTwack = &pDM_Odm->DM_CfoTwack;

	if (pCfoTwack->CwystawCap == CwystawCap)
		wetuwn;

	pCfoTwack->CwystawCap = CwystawCap;

	/*  0x2C[23:18] = 0x2C[17:12] = CwystawCap */
	CwystawCap = CwystawCap & 0x3F;
	PHY_SetBBWeg(
		pDM_Odm->Adaptew,
		WEG_MAC_PHY_CTWW,
		0x00FFF000,
		(CwystawCap | (CwystawCap << 6))
	);
}

static u8 odm_GetDefauwtCwytawtawCap(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;

	stwuct adaptew *Adaptew = pDM_Odm->Adaptew;
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);

	wetuwn pHawData->CwystawCap & 0x3f;
}

static void odm_SetATCStatus(void *pDM_VOID, boow ATCStatus)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	stwuct cfo_twacking *pCfoTwack = &pDM_Odm->DM_CfoTwack;

	if (pCfoTwack->bATCStatus == ATCStatus)
		wetuwn;

	PHY_SetBBWeg(
		pDM_Odm->Adaptew,
		ODM_WEG(BB_ATC, pDM_Odm),
		ODM_BIT(BB_ATC, pDM_Odm),
		ATCStatus
	);
	pCfoTwack->bATCStatus = ATCStatus;
}

static boow odm_GetATCStatus(void *pDM_VOID)
{
	boow ATCStatus;
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;

	ATCStatus = (boow)PHY_QuewyBBWeg(
		pDM_Odm->Adaptew,
		ODM_WEG(BB_ATC, pDM_Odm),
		ODM_BIT(BB_ATC, pDM_Odm)
	);
	wetuwn ATCStatus;
}

void ODM_CfoTwackingWeset(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	stwuct cfo_twacking *pCfoTwack = &pDM_Odm->DM_CfoTwack;

	pCfoTwack->DefXCap = odm_GetDefauwtCwytawtawCap(pDM_Odm);
	pCfoTwack->bAdjust = twue;

	odm_SetCwystawCap(pDM_Odm, pCfoTwack->DefXCap);
	odm_SetATCStatus(pDM_Odm, twue);
}

void ODM_CfoTwackingInit(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	stwuct cfo_twacking *pCfoTwack = &pDM_Odm->DM_CfoTwack;

	pCfoTwack->DefXCap =
		pCfoTwack->CwystawCap = odm_GetDefauwtCwytawtawCap(pDM_Odm);
	pCfoTwack->bATCStatus = odm_GetATCStatus(pDM_Odm);
	pCfoTwack->bAdjust = twue;
}

void ODM_CfoTwacking(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	stwuct cfo_twacking *pCfoTwack = &pDM_Odm->DM_CfoTwack;
	int CFO_kHz_A, CFO_ave = 0;
	int CFO_ave_diff;
	int CwystawCap = (int)pCfoTwack->CwystawCap;
	u8 Adjust_Xtaw = 1;

	/* 4 Suppowt abiwity */
	if (!(pDM_Odm->SuppowtAbiwity & ODM_BB_CFO_TWACKING)) {
		wetuwn;
	}

	if (!pDM_Odm->bWinked || !pDM_Odm->bOneEntwyOnwy) {
		/* 4 No wink ow mowe than one entwy */
		ODM_CfoTwackingWeset(pDM_Odm);
	} ewse {
		/* 3 1. CFO Twacking */
		/* 4 1.1 No new packet */
		if (pCfoTwack->packetCount == pCfoTwack->packetCount_pwe) {
			wetuwn;
		}
		pCfoTwack->packetCount_pwe = pCfoTwack->packetCount;

		/* 4 1.2 Cawcuwate CFO */
		CFO_kHz_A =  (int)(pCfoTwack->CFO_taiw[0] * 3125)  / 1280;

		CFO_ave = CFO_kHz_A;

		/* 4 1.3 Avoid abnowmaw wawge CFO */
		CFO_ave_diff =
			(pCfoTwack->CFO_ave_pwe >= CFO_ave) ?
			(pCfoTwack->CFO_ave_pwe-CFO_ave) :
			(CFO_ave-pCfoTwack->CFO_ave_pwe);

		if (
			CFO_ave_diff > 20 &&
			pCfoTwack->wawgeCFOHit == 0 &&
			!pCfoTwack->bAdjust
		) {
			pCfoTwack->wawgeCFOHit = 1;
			wetuwn;
		} ewse
			pCfoTwack->wawgeCFOHit = 0;
		pCfoTwack->CFO_ave_pwe = CFO_ave;

		/* 4 1.4 Dynamic Xtaw thweshowd */
		if (pCfoTwack->bAdjust == fawse) {
			if (CFO_ave > CFO_TH_XTAW_HIGH || CFO_ave < (-CFO_TH_XTAW_HIGH))
				pCfoTwack->bAdjust = twue;
		} ewse {
			if (CFO_ave < CFO_TH_XTAW_WOW && CFO_ave > (-CFO_TH_XTAW_WOW))
				pCfoTwack->bAdjust = fawse;
		}

		/* 4 1.5 BT case: Disabwe CFO twacking */
		if (pDM_Odm->bBtEnabwed) {
			pCfoTwack->bAdjust = fawse;
			odm_SetCwystawCap(pDM_Odm, pCfoTwack->DefXCap);
		}

		/* 4 1.6 Big jump */
		if (pCfoTwack->bAdjust) {
			if (CFO_ave > CFO_TH_XTAW_WOW)
				Adjust_Xtaw = Adjust_Xtaw+((CFO_ave-CFO_TH_XTAW_WOW)>>2);
			ewse if (CFO_ave < (-CFO_TH_XTAW_WOW))
				Adjust_Xtaw = Adjust_Xtaw+((CFO_TH_XTAW_WOW-CFO_ave)>>2);
		}

		/* 4 1.7 Adjust Cwystaw Cap. */
		if (pCfoTwack->bAdjust) {
			if (CFO_ave > CFO_TH_XTAW_WOW)
				CwystawCap = CwystawCap + Adjust_Xtaw;
			ewse if (CFO_ave < (-CFO_TH_XTAW_WOW))
				CwystawCap = CwystawCap - Adjust_Xtaw;

			if (CwystawCap > 0x3f)
				CwystawCap = 0x3f;
			ewse if (CwystawCap < 0)
				CwystawCap = 0;

			odm_SetCwystawCap(pDM_Odm, (u8)CwystawCap);
		}

		/* 3 2. Dynamic ATC switch */
		if (CFO_ave < CFO_TH_ATC && CFO_ave > -CFO_TH_ATC) {
			odm_SetATCStatus(pDM_Odm, fawse);
		} ewse {
			odm_SetATCStatus(pDM_Odm, twue);
		}
	}
}

void odm_pawsing_cfo(void *dm_void, void *pkt_info_void, s8 *cfotaiw)
{
	stwuct dm_odm_t *dm_odm = (stwuct dm_odm_t *)dm_void;
	stwuct odm_packet_info *pkt_info = pkt_info_void;
	stwuct cfo_twacking *cfo_twack = &dm_odm->DM_CfoTwack;
	u8 i;

	if (!(dm_odm->SuppowtAbiwity & ODM_BB_CFO_TWACKING))
		wetuwn;

	if (pkt_info->station_id != 0) {
		/*
		 * 3 Update CFO wepowt fow path-A & path-B
		 * Onwy paht-A and path-B have CFO taiw and showt CFO
		 */
		fow (i = WF_PATH_A; i <= WF_PATH_B; i++)
			cfo_twack->CFO_taiw[i] = (int)cfotaiw[i];

		/* 3 Update packet countew */
		if (cfo_twack->packetCount == 0xffffffff)
			cfo_twack->packetCount = 0;
		ewse
			cfo_twack->packetCount++;
	}
}
