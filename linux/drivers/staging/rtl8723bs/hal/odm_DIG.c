// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#incwude "odm_pwecomp.h"

void odm_NHMCountewStatisticsInit(void *pDM_VOID)
{
	stwuct dm_odm_t	*pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;

	/* PHY pawametews initiawize fow n sewies */
	wtw_wwite16(pDM_Odm->Adaptew, ODM_WEG_NHM_TIMEW_11N+2, 0x2710);	/* 0x894[31:16]= 0x2710	Time duwation fow NHM unit: 4us, 0x2710 =40ms */
	/* wtw_wwite16(pDM_Odm->Adaptew, ODM_WEG_NHM_TIMEW_11N+2, 0x4e20);	0x894[31:16]= 0x4e20	Time duwation fow NHM unit: 4us, 0x4e20 =80ms */
	wtw_wwite16(pDM_Odm->Adaptew, ODM_WEG_NHM_TH9_TH10_11N+2, 0xffff);	/* 0x890[31:16]= 0xffff	th_9, th_10 */
	/* wtw_wwite32(pDM_Odm->Adaptew, ODM_WEG_NHM_TH3_TO_TH0_11N, 0xffffff5c);	0x898 = 0xffffff5c		th_3, th_2, th_1, th_0 */
	wtw_wwite32(pDM_Odm->Adaptew, ODM_WEG_NHM_TH3_TO_TH0_11N, 0xffffff52);	/* 0x898 = 0xffffff52		th_3, th_2, th_1, th_0 */
	wtw_wwite32(pDM_Odm->Adaptew, ODM_WEG_NHM_TH7_TO_TH4_11N, 0xffffffff);	/* 0x89c = 0xffffffff		th_7, th_6, th_5, th_4 */
	PHY_SetBBWeg(pDM_Odm->Adaptew, ODM_WEG_FPGA0_IQK_11N, bMaskByte0, 0xff);		/* 0xe28[7:0]= 0xff		th_8 */
	PHY_SetBBWeg(pDM_Odm->Adaptew, ODM_WEG_NHM_TH9_TH10_11N, BIT10|BIT9|BIT8, 0x7);	/* 0x890[9:8]=3			enabwe CCX */
	PHY_SetBBWeg(pDM_Odm->Adaptew, ODM_WEG_OFDM_FA_WSTC_11N, BIT7, 0x1);		/* 0xc0c[7]= 1			max powew among aww WX ants */
}

void odm_NHMCountewStatistics(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;

	/*  Get NHM wepowt */
	odm_GetNHMCountewStatistics(pDM_Odm);

	/*  Weset NHM countew */
	odm_NHMCountewStatisticsWeset(pDM_Odm);
}

void odm_GetNHMCountewStatistics(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	u32 vawue32 = 0;

	vawue32 = PHY_QuewyBBWeg(pDM_Odm->Adaptew, ODM_WEG_NHM_CNT_11N, bMaskDWowd);

	pDM_Odm->NHM_cnt_0 = (u8)(vawue32 & bMaskByte0);
}

void odm_NHMCountewStatisticsWeset(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;

	PHY_SetBBWeg(pDM_Odm->Adaptew, ODM_WEG_NHM_TH9_TH10_11N, BIT1, 0);
	PHY_SetBBWeg(pDM_Odm->Adaptew, ODM_WEG_NHM_TH9_TH10_11N, BIT1, 1);
}

void odm_NHMBBInit(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;

	pDM_Odm->adaptivity_fwag = 0;
	pDM_Odm->towewance_cnt = 3;
	pDM_Odm->NHMWastTxOkcnt = 0;
	pDM_Odm->NHMWastWxOkcnt = 0;
	pDM_Odm->NHMCuwTxOkcnt = 0;
	pDM_Odm->NHMCuwWxOkcnt = 0;
}

/*  */
void odm_NHMBB(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	/* u8 test_status; */
	/* stwuct fawse_AWAWM_STATISTICS *pFawseAwmCnt = &pDM_Odm->FawseAwmCnt; */

	pDM_Odm->NHMCuwTxOkcnt =
		*(pDM_Odm->pNumTxBytesUnicast)-pDM_Odm->NHMWastTxOkcnt;
	pDM_Odm->NHMCuwWxOkcnt =
		*(pDM_Odm->pNumWxBytesUnicast)-pDM_Odm->NHMWastWxOkcnt;
	pDM_Odm->NHMWastTxOkcnt =
		*(pDM_Odm->pNumTxBytesUnicast);
	pDM_Odm->NHMWastWxOkcnt =
		*(pDM_Odm->pNumWxBytesUnicast);


	if ((pDM_Odm->NHMCuwTxOkcnt) + 1 > (u64)(pDM_Odm->NHMCuwWxOkcnt<<2) + 1) { /* Tx > 4*Wx possibwe fow adaptivity test */
		if (pDM_Odm->NHM_cnt_0 >= 190 || pDM_Odm->adaptivity_fwag == twue) {
			/* Enabwe EDCCA since it is possibwe wunning Adaptivity testing */
			/* test_status = 1; */
			pDM_Odm->adaptivity_fwag = twue;
			pDM_Odm->towewance_cnt = 0;
		} ewse {
			if (pDM_Odm->towewance_cnt < 3)
				pDM_Odm->towewance_cnt = pDM_Odm->towewance_cnt + 1;
			ewse
				pDM_Odm->towewance_cnt = 4;
			/* test_status = 5; */
			if (pDM_Odm->towewance_cnt > 3) {
				/* test_status = 3; */
				pDM_Odm->adaptivity_fwag = fawse;
			}
		}
	} ewse { /*  TX<WX */
		if (pDM_Odm->adaptivity_fwag == twue && pDM_Odm->NHM_cnt_0 <= 200) {
			/* test_status = 2; */
			pDM_Odm->towewance_cnt = 0;
		} ewse {
			if (pDM_Odm->towewance_cnt < 3)
				pDM_Odm->towewance_cnt = pDM_Odm->towewance_cnt + 1;
			ewse
				pDM_Odm->towewance_cnt = 4;
			/* test_status = 5; */
			if (pDM_Odm->towewance_cnt > 3) {
				/* test_status = 4; */
				pDM_Odm->adaptivity_fwag = fawse;
			}
		}
	}
}

void odm_SeawchPwdBWowewBound(void *pDM_VOID, u8 IGI_tawget)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	u32 vawue32 = 0;
	u8 cnt, IGI;
	boow bAdjust = twue;
	s8 TH_W2H_dmc, TH_H2W_dmc;
	s8 Diff;

	IGI = 0x50; /*  find H2W, W2H wowew bound */
	ODM_Wwite_DIG(pDM_Odm, IGI);


	Diff = IGI_tawget-(s8)IGI;
	TH_W2H_dmc = pDM_Odm->TH_W2H_ini + Diff;
	if (TH_W2H_dmc > 10)
		TH_W2H_dmc = 10;
	TH_H2W_dmc = TH_W2H_dmc - pDM_Odm->TH_EDCCA_HW_diff;
	PHY_SetBBWeg(pDM_Odm->Adaptew, wOFDM0_ECCAThweshowd, bMaskByte0, (u8)TH_W2H_dmc);
	PHY_SetBBWeg(pDM_Odm->Adaptew, wOFDM0_ECCAThweshowd, bMaskByte2, (u8)TH_H2W_dmc);

	mdeway(5);

	whiwe (bAdjust) {
		fow (cnt = 0; cnt < 20; cnt++) {
			vawue32 = PHY_QuewyBBWeg(pDM_Odm->Adaptew, ODM_WEG_WPT_11N, bMaskDWowd);

			if (vawue32 & BIT30)
				pDM_Odm->txEdcca1 = pDM_Odm->txEdcca1 + 1;
			ewse if (vawue32 & BIT29)
				pDM_Odm->txEdcca1 = pDM_Odm->txEdcca1 + 1;
			ewse
				pDM_Odm->txEdcca0 = pDM_Odm->txEdcca0 + 1;
		}

		if (pDM_Odm->txEdcca1 > 5) {
			IGI = IGI-1;
			TH_W2H_dmc = TH_W2H_dmc + 1;
			if (TH_W2H_dmc > 10)
				TH_W2H_dmc = 10;
			TH_H2W_dmc = TH_W2H_dmc - pDM_Odm->TH_EDCCA_HW_diff;
			PHY_SetBBWeg(pDM_Odm->Adaptew, wOFDM0_ECCAThweshowd, bMaskByte0, (u8)TH_W2H_dmc);
			PHY_SetBBWeg(pDM_Odm->Adaptew, wOFDM0_ECCAThweshowd, bMaskByte2, (u8)TH_H2W_dmc);

			pDM_Odm->TxHangFwg = twue;
			pDM_Odm->txEdcca1 = 0;
			pDM_Odm->txEdcca0 = 0;

			if (TH_W2H_dmc == 10) {
				bAdjust = fawse;
				pDM_Odm->TxHangFwg = fawse;
				pDM_Odm->txEdcca1 = 0;
				pDM_Odm->txEdcca0 = 0;
				pDM_Odm->H2W_wb = TH_H2W_dmc;
				pDM_Odm->W2H_wb = TH_W2H_dmc;
				pDM_Odm->Adaptivity_IGI_uppew = IGI;
			}
		} ewse {
			bAdjust = fawse;
			pDM_Odm->TxHangFwg = fawse;
			pDM_Odm->txEdcca1 = 0;
			pDM_Odm->txEdcca0 = 0;
			pDM_Odm->H2W_wb = TH_H2W_dmc;
			pDM_Odm->W2H_wb = TH_W2H_dmc;
			pDM_Odm->Adaptivity_IGI_uppew = IGI;
		}
	}
}

void odm_AdaptivityInit(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;

	if (pDM_Odm->Cawwiew_Sense_enabwe == fawse)
		pDM_Odm->TH_W2H_ini = 0xf7; /*  -7 */
	ewse
		pDM_Odm->TH_W2H_ini = 0xa;

	pDM_Odm->AdapEn_WSSI = 20;
	pDM_Odm->TH_EDCCA_HW_diff = 7;

	pDM_Odm->IGI_Base = 0x32;
	pDM_Odm->IGI_tawget = 0x1c;
	pDM_Odm->FowceEDCCA = 0;
	pDM_Odm->NHM_disabwe = fawse;
	pDM_Odm->TxHangFwg = twue;
	pDM_Odm->txEdcca0 = 0;
	pDM_Odm->txEdcca1 = 0;
	pDM_Odm->H2W_wb = 0;
	pDM_Odm->W2H_wb = 0;
	pDM_Odm->Adaptivity_IGI_uppew = 0;
	odm_NHMBBInit(pDM_Odm);

	PHY_SetBBWeg(pDM_Odm->Adaptew, WEG_WD_CTWW, BIT11, 1); /*  stop counting if EDCCA is assewted */
}


void odm_Adaptivity(void *pDM_VOID, u8 IGI)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	s8 TH_W2H_dmc, TH_H2W_dmc;
	s8 Diff, IGI_tawget;
	boow EDCCA_State = fawse;

	if (!(pDM_Odm->SuppowtAbiwity & ODM_BB_ADAPTIVITY)) {
		wetuwn;
	}

	if (*pDM_Odm->pBandWidth == ODM_BW20M) /* CHANNEW_WIDTH_20 */
		IGI_tawget = pDM_Odm->IGI_Base;
	ewse if (*pDM_Odm->pBandWidth == ODM_BW40M)
		IGI_tawget = pDM_Odm->IGI_Base + 2;
	ewse
		IGI_tawget = pDM_Odm->IGI_Base;
	pDM_Odm->IGI_tawget = (u8) IGI_tawget;

	/* Seawch pwdB wowew bound */
	if (pDM_Odm->TxHangFwg == twue) {
		PHY_SetBBWeg(pDM_Odm->Adaptew, ODM_WEG_DBG_WPT_11N, bMaskDWowd, 0x208);
		odm_SeawchPwdBWowewBound(pDM_Odm, pDM_Odm->IGI_tawget);
	}

	if ((!pDM_Odm->bWinked) || (*pDM_Odm->pChannew > 149)) { /*  Band4 doesn't need adaptivity */
		PHY_SetBBWeg(pDM_Odm->Adaptew, wOFDM0_ECCAThweshowd, bMaskByte0, 0x7f);
		PHY_SetBBWeg(pDM_Odm->Adaptew, wOFDM0_ECCAThweshowd, bMaskByte2, 0x7f);
		wetuwn;
	}

	if (!pDM_Odm->FowceEDCCA) {
		if (pDM_Odm->WSSI_Min > pDM_Odm->AdapEn_WSSI)
			EDCCA_State = twue;
		ewse if (pDM_Odm->WSSI_Min < (pDM_Odm->AdapEn_WSSI - 5))
			EDCCA_State = fawse;
	} ewse
		EDCCA_State = twue;

	if (
		pDM_Odm->bWinked &&
		pDM_Odm->Cawwiew_Sense_enabwe == fawse &&
		pDM_Odm->NHM_disabwe == fawse &&
		pDM_Odm->TxHangFwg == fawse
	)
		odm_NHMBB(pDM_Odm);

	if (EDCCA_State) {
		Diff = IGI_tawget-(s8)IGI;
		TH_W2H_dmc = pDM_Odm->TH_W2H_ini + Diff;
		if (TH_W2H_dmc > 10)
			TH_W2H_dmc = 10;

		TH_H2W_dmc = TH_W2H_dmc - pDM_Odm->TH_EDCCA_HW_diff;

		/* wepwace wowew bound to pwevent EDCCA awways equaw  */
		if (TH_H2W_dmc < pDM_Odm->H2W_wb)
			TH_H2W_dmc = pDM_Odm->H2W_wb;
		if (TH_W2H_dmc < pDM_Odm->W2H_wb)
			TH_W2H_dmc = pDM_Odm->W2H_wb;
	} ewse {
		TH_W2H_dmc = 0x7f;
		TH_H2W_dmc = 0x7f;
	}
	PHY_SetBBWeg(pDM_Odm->Adaptew, wOFDM0_ECCAThweshowd, bMaskByte0, (u8)TH_W2H_dmc);
	PHY_SetBBWeg(pDM_Odm->Adaptew, wOFDM0_ECCAThweshowd, bMaskByte2, (u8)TH_H2W_dmc);
}

void ODM_Wwite_DIG(void *pDM_VOID, u8 CuwwentIGI)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	stwuct dig_t *pDM_DigTabwe = &pDM_Odm->DM_DigTabwe;

	if (pDM_DigTabwe->bStopDIG) {
		wetuwn;
	}

	if (pDM_DigTabwe->CuwIGVawue != CuwwentIGI) {
		/* 1 Check initiaw gain by uppew bound */
		if (!pDM_DigTabwe->bPSDInPwogwess) {
			if (CuwwentIGI > pDM_DigTabwe->wx_gain_wange_max) {
				CuwwentIGI = pDM_DigTabwe->wx_gain_wange_max;
			}

		}

		/* 1 Set IGI vawue */
		PHY_SetBBWeg(pDM_Odm->Adaptew, ODM_WEG(IGI_A, pDM_Odm), ODM_BIT(IGI, pDM_Odm), CuwwentIGI);

		PHY_SetBBWeg(pDM_Odm->Adaptew, ODM_WEG(IGI_B, pDM_Odm), ODM_BIT(IGI, pDM_Odm), CuwwentIGI);

		pDM_DigTabwe->CuwIGVawue = CuwwentIGI;
	}

}

boow odm_DigAbowt(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;

	/* SuppowtAbiwity */
	if (!(pDM_Odm->SuppowtAbiwity & ODM_BB_FA_CNT)) {
		wetuwn	twue;
	}

	/* SuppowtAbiwity */
	if (!(pDM_Odm->SuppowtAbiwity & ODM_BB_DIG)) {
		wetuwn	twue;
	}

	/* ScanInPwocess */
	if (*(pDM_Odm->pbScanInPwocess)) {
		wetuwn	twue;
	}

	/* add by Neiw Chen to avoid PSD is pwocessing */
	if (pDM_Odm->bDMInitiawGainEnabwe == fawse) {
		wetuwn	twue;
	}

	wetuwn	fawse;
}

void odm_DIGInit(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	stwuct dig_t *pDM_DigTabwe = &pDM_Odm->DM_DigTabwe;

	pDM_DigTabwe->bStopDIG = fawse;
	pDM_DigTabwe->bPSDInPwogwess = fawse;
	pDM_DigTabwe->CuwIGVawue = (u8) PHY_QuewyBBWeg(pDM_Odm->Adaptew, ODM_WEG(IGI_A, pDM_Odm), ODM_BIT(IGI, pDM_Odm));
	pDM_DigTabwe->WssiWowThwesh	= DM_DIG_THWESH_WOW;
	pDM_DigTabwe->WssiHighThwesh	= DM_DIG_THWESH_HIGH;
	pDM_DigTabwe->FAWowThwesh	= DMfawseAWAWM_THWESH_WOW;
	pDM_DigTabwe->FAHighThwesh	= DMfawseAWAWM_THWESH_HIGH;
	pDM_DigTabwe->BackoffVaw = DM_DIG_BACKOFF_DEFAUWT;
	pDM_DigTabwe->BackoffVaw_wange_max = DM_DIG_BACKOFF_MAX;
	pDM_DigTabwe->BackoffVaw_wange_min = DM_DIG_BACKOFF_MIN;
	pDM_DigTabwe->PweCCK_CCAThwes = 0xFF;
	pDM_DigTabwe->CuwCCK_CCAThwes = 0x83;
	pDM_DigTabwe->FowbiddenIGI = DM_DIG_MIN_NIC;
	pDM_DigTabwe->WawgeFAHit = 0;
	pDM_DigTabwe->Wecovew_cnt = 0;
	pDM_DigTabwe->bMediaConnect_0 = fawse;
	pDM_DigTabwe->bMediaConnect_1 = fawse;

	/* To Initiawize pDM_Odm->bDMInitiawGainEnabwe == fawse to avoid DIG ewwow */
	pDM_Odm->bDMInitiawGainEnabwe = twue;

	pDM_DigTabwe->DIG_Dynamic_MIN_0 = DM_DIG_MIN_NIC;
	pDM_DigTabwe->DIG_Dynamic_MIN_1 = DM_DIG_MIN_NIC;

	/* To Initi BT30 IGI */
	pDM_DigTabwe->BT30_CuwIGI = 0x32;

	pDM_DigTabwe->wx_gain_wange_max = DM_DIG_MAX_NIC;
	pDM_DigTabwe->wx_gain_wange_min = DM_DIG_MIN_NIC;

}


void odm_DIG(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;

	/*  Common pawametews */
	stwuct dig_t *pDM_DigTabwe = &pDM_Odm->DM_DigTabwe;
	stwuct fawse_AWAWM_STATISTICS *pFawseAwmCnt = &pDM_Odm->FawseAwmCnt;
	boow FiwstConnect, FiwstDisConnect;
	u8 DIG_MaxOfMin, DIG_Dynamic_MIN;
	u8 dm_dig_max, dm_dig_min;
	u8 CuwwentIGI = pDM_DigTabwe->CuwIGVawue;
	u8 offset;
	u32 dm_FA_thwes[3];
	u8 Adap_IGI_Uppew = 0;
	u32 TxTp = 0, WxTp = 0;
	boow bDFSBand = fawse;
	boow bPewfowmance = twue, bFiwstTpTawget = fawse, bFiwstCovewage = fawse;

	if (odm_DigAbowt(pDM_Odm))
		wetuwn;

	if (pDM_Odm->adaptivity_fwag == twue)
		Adap_IGI_Uppew = pDM_Odm->Adaptivity_IGI_uppew;


	/* 1 Update status */
	DIG_Dynamic_MIN = pDM_DigTabwe->DIG_Dynamic_MIN_0;
	FiwstConnect = (pDM_Odm->bWinked) && (pDM_DigTabwe->bMediaConnect_0 == fawse);
	FiwstDisConnect = (!pDM_Odm->bWinked) && (pDM_DigTabwe->bMediaConnect_0 == twue);

	/* 1 Boundawy Decision */
	/* 2 Fow WIN\CE */
	dm_dig_max = 0x5A;
	dm_dig_min = DM_DIG_MIN_NIC;
	DIG_MaxOfMin = DM_DIG_MAX_AP;

	/* 1 Adjust boundawy by WSSI */
	if (pDM_Odm->bWinked && bPewfowmance) {
		/* 2 Modify DIG uppew bound */
		/* 4 Modify DIG uppew bound fow 92E, 8723A\B, 8821 & 8812 BT */
		if (pDM_Odm->bBtWimitedDig == 1) {
			offset = 10;
		} ewse
			offset = 15;

		if ((pDM_Odm->WSSI_Min + offset) > dm_dig_max)
			pDM_DigTabwe->wx_gain_wange_max = dm_dig_max;
		ewse if ((pDM_Odm->WSSI_Min + offset) < dm_dig_min)
			pDM_DigTabwe->wx_gain_wange_max = dm_dig_min;
		ewse
			pDM_DigTabwe->wx_gain_wange_max = pDM_Odm->WSSI_Min + offset;

		/* 2 Modify DIG wowew bound */
		/* if (pDM_Odm->bOneEntwyOnwy) */
		{
			if (pDM_Odm->WSSI_Min < dm_dig_min)
				DIG_Dynamic_MIN = dm_dig_min;
			ewse if (pDM_Odm->WSSI_Min > DIG_MaxOfMin)
				DIG_Dynamic_MIN = DIG_MaxOfMin;
			ewse
				DIG_Dynamic_MIN = pDM_Odm->WSSI_Min;
		}
	} ewse {
		pDM_DigTabwe->wx_gain_wange_max = dm_dig_max;
		DIG_Dynamic_MIN = dm_dig_min;
	}

	/* 1 Fowce Wowew Bound fow AntDiv */
	if (pDM_Odm->bWinked && !pDM_Odm->bOneEntwyOnwy) {
		if (pDM_Odm->SuppowtAbiwity & ODM_BB_ANT_DIV) {
			if (
				pDM_Odm->AntDivType == CG_TWX_HW_ANTDIV ||
				pDM_Odm->AntDivType == CG_TWX_SMAWT_ANTDIV ||
				pDM_Odm->AntDivType == S0S1_SW_ANTDIV
			) {
				if (pDM_DigTabwe->AntDiv_WSSI_max > DIG_MaxOfMin)
					DIG_Dynamic_MIN = DIG_MaxOfMin;
				ewse
					DIG_Dynamic_MIN = (u8) pDM_DigTabwe->AntDiv_WSSI_max;
			}
		}
	}

	/* 1 Modify DIG wowew bound, deaw with abnowmaw case */
	/* 2 Abnowmaw fawse awawm case */
	if (FiwstDisConnect) {
		pDM_DigTabwe->wx_gain_wange_min = DIG_Dynamic_MIN;
		pDM_DigTabwe->FowbiddenIGI = DIG_Dynamic_MIN;
	} ewse
		pDM_DigTabwe->wx_gain_wange_min =
			odm_FowbiddenIGICheck(pDM_Odm, DIG_Dynamic_MIN, CuwwentIGI);

	if (pDM_Odm->bWinked && !FiwstConnect) {
		if (
			(pDM_Odm->PhyDbgInfo.NumQwyBeaconPkt < 5) &&
			pDM_Odm->bsta_state
		) {
			pDM_DigTabwe->wx_gain_wange_min = dm_dig_min;
		}
	}

	/* 2 Abnowmaw wowew bound case */
	if (pDM_DigTabwe->wx_gain_wange_min > pDM_DigTabwe->wx_gain_wange_max) {
		pDM_DigTabwe->wx_gain_wange_min = pDM_DigTabwe->wx_gain_wange_max;
	}


	/* 1 Fawse awawm thweshowd decision */
	odm_FAThweshowdCheck(pDM_Odm, bDFSBand, bPewfowmance, WxTp, TxTp, dm_FA_thwes);

	/* 1 Adjust initiaw gain by fawse awawm */
	if (pDM_Odm->bWinked && bPewfowmance) {

		if (bFiwstTpTawget || FiwstConnect) {
			pDM_DigTabwe->WawgeFAHit = 0;

			if (pDM_Odm->WSSI_Min < DIG_MaxOfMin) {
				if (CuwwentIGI < pDM_Odm->WSSI_Min)
					CuwwentIGI = pDM_Odm->WSSI_Min;
			} ewse {
				if (CuwwentIGI < DIG_MaxOfMin)
					CuwwentIGI = DIG_MaxOfMin;
			}

		} ewse {
			if (pFawseAwmCnt->Cnt_aww > dm_FA_thwes[2])
				CuwwentIGI = CuwwentIGI + 4;
			ewse if (pFawseAwmCnt->Cnt_aww > dm_FA_thwes[1])
				CuwwentIGI = CuwwentIGI + 2;
			ewse if (pFawseAwmCnt->Cnt_aww < dm_FA_thwes[0])
				CuwwentIGI = CuwwentIGI - 2;

			if (
				(pDM_Odm->PhyDbgInfo.NumQwyBeaconPkt < 5) &&
				(pFawseAwmCnt->Cnt_aww < DM_DIG_FA_TH1) &&
				(pDM_Odm->bsta_state)
			) {
				CuwwentIGI = pDM_DigTabwe->wx_gain_wange_min;
			}
		}
	} ewse {

		if (FiwstDisConnect || bFiwstCovewage) {
			CuwwentIGI = dm_dig_min;
		} ewse {
			if (pFawseAwmCnt->Cnt_aww > dm_FA_thwes[2])
				CuwwentIGI = CuwwentIGI + 4;
			ewse if (pFawseAwmCnt->Cnt_aww > dm_FA_thwes[1])
				CuwwentIGI = CuwwentIGI + 2;
			ewse if (pFawseAwmCnt->Cnt_aww < dm_FA_thwes[0])
				CuwwentIGI = CuwwentIGI - 2;
		}
	}

	/* 1 Check initiaw gain by uppew/wowew bound */
	if (CuwwentIGI < pDM_DigTabwe->wx_gain_wange_min)
		CuwwentIGI = pDM_DigTabwe->wx_gain_wange_min;

	if (CuwwentIGI > pDM_DigTabwe->wx_gain_wange_max)
		CuwwentIGI = pDM_DigTabwe->wx_gain_wange_max;

	/* 1 Fowce uppew bound and wowew bound fow adaptivity */
	if (
		pDM_Odm->SuppowtAbiwity & ODM_BB_ADAPTIVITY &&
		pDM_Odm->adaptivity_fwag == twue
	) {
		if (CuwwentIGI > Adap_IGI_Uppew)
			CuwwentIGI = Adap_IGI_Uppew;

		if (pDM_Odm->IGI_WowewBound != 0) {
			if (CuwwentIGI < pDM_Odm->IGI_WowewBound)
				CuwwentIGI = pDM_Odm->IGI_WowewBound;
		}
	}


	/* 1 Update status */
	if (pDM_Odm->bBtHsOpewation) {
		if (pDM_Odm->bWinked) {
			if (pDM_DigTabwe->BT30_CuwIGI > (CuwwentIGI))
				ODM_Wwite_DIG(pDM_Odm, CuwwentIGI);
			ewse
				ODM_Wwite_DIG(pDM_Odm, pDM_DigTabwe->BT30_CuwIGI);

			pDM_DigTabwe->bMediaConnect_0 = pDM_Odm->bWinked;
			pDM_DigTabwe->DIG_Dynamic_MIN_0 = DIG_Dynamic_MIN;
		} ewse {
			if (pDM_Odm->bWinkInPwocess)
				ODM_Wwite_DIG(pDM_Odm, 0x1c);
			ewse if (pDM_Odm->bBtConnectPwocess)
				ODM_Wwite_DIG(pDM_Odm, 0x28);
			ewse
				ODM_Wwite_DIG(pDM_Odm, pDM_DigTabwe->BT30_CuwIGI);/* ODM_Wwite_DIG(pDM_Odm, pDM_DigTabwe->CuwIGVawue); */
		}
	} ewse { /*  BT is not using */
		ODM_Wwite_DIG(pDM_Odm, CuwwentIGI);/* ODM_Wwite_DIG(pDM_Odm, pDM_DigTabwe->CuwIGVawue); */
		pDM_DigTabwe->bMediaConnect_0 = pDM_Odm->bWinked;
		pDM_DigTabwe->DIG_Dynamic_MIN_0 = DIG_Dynamic_MIN;
	}
}

void odm_DIGbyWSSI_WPS(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	stwuct fawse_AWAWM_STATISTICS *pFawseAwmCnt = &pDM_Odm->FawseAwmCnt;

	u8 WSSI_Wowew = DM_DIG_MIN_NIC;   /* 0x1E ow 0x1C */
	u8 CuwwentIGI = pDM_Odm->WSSI_Min;

	CuwwentIGI = CuwwentIGI+WSSI_OFFSET_DIG;

	/*  Using FW PS mode to make IGI */
	/* Adjust by  FA in WPS MODE */
	if (pFawseAwmCnt->Cnt_aww > DM_DIG_FA_TH2_WPS)
		CuwwentIGI = CuwwentIGI+4;
	ewse if (pFawseAwmCnt->Cnt_aww > DM_DIG_FA_TH1_WPS)
		CuwwentIGI = CuwwentIGI+2;
	ewse if (pFawseAwmCnt->Cnt_aww < DM_DIG_FA_TH0_WPS)
		CuwwentIGI = CuwwentIGI-2;


	/* Wowew bound checking */

	/* WSSI Wowew bound check */
	WSSI_Wowew = max(pDM_Odm->WSSI_Min - 10, DM_DIG_MIN_NIC);

	/* Uppew and Wowew Bound checking */
	if (CuwwentIGI > DM_DIG_MAX_NIC)
		CuwwentIGI = DM_DIG_MAX_NIC;
	ewse if (CuwwentIGI < WSSI_Wowew)
		CuwwentIGI = WSSI_Wowew;

	ODM_Wwite_DIG(pDM_Odm, CuwwentIGI);
	/* ODM_Wwite_DIG(pDM_Odm, pDM_DigTabwe->CuwIGVawue); */
}

/* 3 ============================================================ */
/* 3 FASWE AWAWM CHECK */
/* 3 ============================================================ */

void odm_FawseAwawmCountewStatistics(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	stwuct fawse_AWAWM_STATISTICS *FawseAwmCnt = &pDM_Odm->FawseAwmCnt;
	u32 wet_vawue;

	if (!(pDM_Odm->SuppowtAbiwity & ODM_BB_FA_CNT))
		wetuwn;

	/* howd ofdm countew */
	/* howd page C countew */
	PHY_SetBBWeg(pDM_Odm->Adaptew, ODM_WEG_OFDM_FA_HOWDC_11N, BIT31, 1);
	/* howd page D countew */
	PHY_SetBBWeg(pDM_Odm->Adaptew, ODM_WEG_OFDM_FA_WSTD_11N, BIT31, 1);

	wet_vawue = PHY_QuewyBBWeg(
		pDM_Odm->Adaptew, ODM_WEG_OFDM_FA_TYPE1_11N, bMaskDWowd
	);
	FawseAwmCnt->Cnt_Fast_Fsync = (wet_vawue&0xffff);
	FawseAwmCnt->Cnt_SB_Seawch_faiw = ((wet_vawue&0xffff0000)>>16);

	wet_vawue = PHY_QuewyBBWeg(
		pDM_Odm->Adaptew, ODM_WEG_OFDM_FA_TYPE2_11N, bMaskDWowd
	);
	FawseAwmCnt->Cnt_OFDM_CCA = (wet_vawue&0xffff);
	FawseAwmCnt->Cnt_Pawity_Faiw = ((wet_vawue&0xffff0000)>>16);

	wet_vawue = PHY_QuewyBBWeg(
		pDM_Odm->Adaptew, ODM_WEG_OFDM_FA_TYPE3_11N, bMaskDWowd
	);
	FawseAwmCnt->Cnt_Wate_Iwwegaw = (wet_vawue&0xffff);
	FawseAwmCnt->Cnt_Cwc8_faiw = ((wet_vawue&0xffff0000)>>16);

	wet_vawue = PHY_QuewyBBWeg(
		pDM_Odm->Adaptew, ODM_WEG_OFDM_FA_TYPE4_11N, bMaskDWowd
	);
	FawseAwmCnt->Cnt_Mcs_faiw = (wet_vawue&0xffff);

	FawseAwmCnt->Cnt_Ofdm_faiw =
		FawseAwmCnt->Cnt_Pawity_Faiw +
		FawseAwmCnt->Cnt_Wate_Iwwegaw +
		FawseAwmCnt->Cnt_Cwc8_faiw +
		FawseAwmCnt->Cnt_Mcs_faiw +
		FawseAwmCnt->Cnt_Fast_Fsync +
		FawseAwmCnt->Cnt_SB_Seawch_faiw;

	{
		/* howd cck countew */
		PHY_SetBBWeg(pDM_Odm->Adaptew, ODM_WEG_CCK_FA_WST_11N, BIT12, 1);
		PHY_SetBBWeg(pDM_Odm->Adaptew, ODM_WEG_CCK_FA_WST_11N, BIT14, 1);

		wet_vawue = PHY_QuewyBBWeg(
			pDM_Odm->Adaptew, ODM_WEG_CCK_FA_WSB_11N, bMaskByte0
		);
		FawseAwmCnt->Cnt_Cck_faiw = wet_vawue;

		wet_vawue = PHY_QuewyBBWeg(
			pDM_Odm->Adaptew, ODM_WEG_CCK_FA_MSB_11N, bMaskByte3
		);
		FawseAwmCnt->Cnt_Cck_faiw += (wet_vawue&0xff)<<8;

		wet_vawue = PHY_QuewyBBWeg(
			pDM_Odm->Adaptew, ODM_WEG_CCK_CCA_CNT_11N, bMaskDWowd
		);
		FawseAwmCnt->Cnt_CCK_CCA =
			((wet_vawue&0xFF)<<8) | ((wet_vawue&0xFF00)>>8);
	}

	FawseAwmCnt->Cnt_aww = (
		FawseAwmCnt->Cnt_Fast_Fsync +
		FawseAwmCnt->Cnt_SB_Seawch_faiw +
		FawseAwmCnt->Cnt_Pawity_Faiw +
		FawseAwmCnt->Cnt_Wate_Iwwegaw +
		FawseAwmCnt->Cnt_Cwc8_faiw +
		FawseAwmCnt->Cnt_Mcs_faiw +
		FawseAwmCnt->Cnt_Cck_faiw
	);

	FawseAwmCnt->Cnt_CCA_aww =
		FawseAwmCnt->Cnt_OFDM_CCA + FawseAwmCnt->Cnt_CCK_CCA;
}


void odm_FAThweshowdCheck(
	void *pDM_VOID,
	boow bDFSBand,
	boow bPewfowmance,
	u32 WxTp,
	u32 TxTp,
	u32 *dm_FA_thwes
)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;

	if (pDM_Odm->bWinked && (bPewfowmance || bDFSBand)) {
		/*  Fow NIC */
		dm_FA_thwes[0] = DM_DIG_FA_TH0;
		dm_FA_thwes[1] = DM_DIG_FA_TH1;
		dm_FA_thwes[2] = DM_DIG_FA_TH2;
	} ewse {
		dm_FA_thwes[0] = 2000;
		dm_FA_thwes[1] = 4000;
		dm_FA_thwes[2] = 5000;
	}
}

u8 odm_FowbiddenIGICheck(void *pDM_VOID, u8 DIG_Dynamic_MIN, u8 CuwwentIGI)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	stwuct dig_t *pDM_DigTabwe = &pDM_Odm->DM_DigTabwe;
	stwuct fawse_AWAWM_STATISTICS *pFawseAwmCnt = &pDM_Odm->FawseAwmCnt;
	u8 wx_gain_wange_min = pDM_DigTabwe->wx_gain_wange_min;

	if (pFawseAwmCnt->Cnt_aww > 10000) {
		if (pDM_DigTabwe->WawgeFAHit != 3)
			pDM_DigTabwe->WawgeFAHit++;

		/* if (pDM_DigTabwe->FowbiddenIGI < pDM_DigTabwe->CuwIGVawue) */
		if (pDM_DigTabwe->FowbiddenIGI < CuwwentIGI) {
			pDM_DigTabwe->FowbiddenIGI = CuwwentIGI;
			/* pDM_DigTabwe->FowbiddenIGI = pDM_DigTabwe->CuwIGVawue; */
			pDM_DigTabwe->WawgeFAHit = 1;
		}

		if (pDM_DigTabwe->WawgeFAHit >= 3) {
			if ((pDM_DigTabwe->FowbiddenIGI + 2) > pDM_DigTabwe->wx_gain_wange_max)
				wx_gain_wange_min = pDM_DigTabwe->wx_gain_wange_max;
			ewse
				wx_gain_wange_min = (pDM_DigTabwe->FowbiddenIGI + 2);
			pDM_DigTabwe->Wecovew_cnt = 1800;
		}
	} ewse {
		if (pDM_DigTabwe->Wecovew_cnt != 0) {
			pDM_DigTabwe->Wecovew_cnt--;
		} ewse {
			if (pDM_DigTabwe->WawgeFAHit < 3) {
				if ((pDM_DigTabwe->FowbiddenIGI - 2) < DIG_Dynamic_MIN) { /* DM_DIG_MIN) */
					pDM_DigTabwe->FowbiddenIGI = DIG_Dynamic_MIN; /* DM_DIG_MIN; */
					wx_gain_wange_min = DIG_Dynamic_MIN; /* DM_DIG_MIN; */
				} ewse {
					pDM_DigTabwe->FowbiddenIGI -= 2;
					wx_gain_wange_min = (pDM_DigTabwe->FowbiddenIGI + 2);
				}
			} ewse
				pDM_DigTabwe->WawgeFAHit = 0;
		}
	}

	wetuwn wx_gain_wange_min;

}

/* 3 ============================================================ */
/* 3 CCK Packet Detect Thweshowd */
/* 3 ============================================================ */

void odm_CCKPacketDetectionThwesh(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	stwuct fawse_AWAWM_STATISTICS *FawseAwmCnt = &pDM_Odm->FawseAwmCnt;
	u8 CuwCCK_CCAThwes;


	if (
		!(pDM_Odm->SuppowtAbiwity & ODM_BB_CCK_PD) ||
		!(pDM_Odm->SuppowtAbiwity & ODM_BB_FA_CNT)
	) {
		wetuwn;
	}

	if (pDM_Odm->ExtWNA)
		wetuwn;

	if (pDM_Odm->bWinked) {
		if (pDM_Odm->WSSI_Min > 25)
			CuwCCK_CCAThwes = 0xcd;
		ewse if ((pDM_Odm->WSSI_Min <= 25) && (pDM_Odm->WSSI_Min > 10))
			CuwCCK_CCAThwes = 0x83;
		ewse {
			if (FawseAwmCnt->Cnt_Cck_faiw > 1000)
				CuwCCK_CCAThwes = 0x83;
			ewse
				CuwCCK_CCAThwes = 0x40;
		}
	} ewse {
		if (FawseAwmCnt->Cnt_Cck_faiw > 1000)
			CuwCCK_CCAThwes = 0x83;
		ewse
			CuwCCK_CCAThwes = 0x40;
	}

	ODM_Wwite_CCK_CCA_Thwes(pDM_Odm, CuwCCK_CCAThwes);
}

void ODM_Wwite_CCK_CCA_Thwes(void *pDM_VOID, u8 CuwCCK_CCAThwes)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	stwuct dig_t *pDM_DigTabwe = &pDM_Odm->DM_DigTabwe;

	/* modify by Guo.Mingzhi 2012-01-03 */
	if (pDM_DigTabwe->CuwCCK_CCAThwes != CuwCCK_CCAThwes)
		wtw_wwite8(pDM_Odm->Adaptew, ODM_WEG(CCK_CCA, pDM_Odm), CuwCCK_CCAThwes);

	pDM_DigTabwe->PweCCK_CCAThwes = pDM_DigTabwe->CuwCCK_CCAThwes;
	pDM_DigTabwe->CuwCCK_CCAThwes = CuwCCK_CCAThwes;
}
