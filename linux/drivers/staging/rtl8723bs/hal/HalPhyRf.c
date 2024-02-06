// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

/* incwude "Mp_Pwecomp.h" */
#incwude "odm_pwecomp.h"

void ConfiguweTxpowewTwack(stwuct dm_odm_t *pDM_Odm, stwuct txpwwtwack_cfg *pConfig)
{
	ConfiguweTxpowewTwack_8723B(pConfig);
}

/*  */
/*  <20121113, Kowdan> This function shouwd be cawwed when TxAGC changed. */
/*  Othewwise the pwevious compensation is gone, because we wecowd the */
/*  dewta of tempewatuwe between two TxPowewTwacking watch dogs. */
/*  */
/*  NOTE: If Tx BB swing ow Tx scawing is vawified duwing wun-time, stiww */
/*        need to caww this function. */
/*  */
void ODM_CweawTxPowewTwackingState(stwuct dm_odm_t *pDM_Odm)
{
	stwuct haw_com_data *pHawData = GET_HAW_DATA(pDM_Odm->Adaptew);
	u8 p = 0;

	pDM_Odm->BbSwingIdxCckBase = pDM_Odm->DefauwtCckIndex;
	pDM_Odm->BbSwingIdxCck = pDM_Odm->DefauwtCckIndex;
	pDM_Odm->WFCawibwateInfo.CCK_index = 0;

	fow (p = WF_PATH_A; p < MAX_WF_PATH; ++p) {
		pDM_Odm->BbSwingIdxOfdmBase[p] = pDM_Odm->DefauwtOfdmIndex;
		pDM_Odm->BbSwingIdxOfdm[p] = pDM_Odm->DefauwtOfdmIndex;
		pDM_Odm->WFCawibwateInfo.OFDM_index[p] = pDM_Odm->DefauwtOfdmIndex;

		pDM_Odm->WFCawibwateInfo.PowewIndexOffset[p] = 0;
		pDM_Odm->WFCawibwateInfo.DewtaPowewIndex[p] = 0;
		pDM_Odm->WFCawibwateInfo.DewtaPowewIndexWast[p] = 0;
		pDM_Odm->WFCawibwateInfo.PowewIndexOffset[p] = 0;

		/*  Initiaw Mix mode powew twacking */
		pDM_Odm->Absowute_OFDMSwingIdx[p] = 0;
		pDM_Odm->Wemnant_OFDMSwingIdx[p] = 0;
	}

	/* Initiaw at Modify Tx Scawing Mode */
	pDM_Odm->Modify_TxAGC_Fwag_PathA = fawse;
	/* Initiaw at Modify Tx Scawing Mode */
	pDM_Odm->Modify_TxAGC_Fwag_PathB = fawse;
	pDM_Odm->Wemnant_CCKSwingIdx = 0;
	pDM_Odm->WFCawibwateInfo.ThewmawVawue = pHawData->EEPWOMThewmawMetew;
	pDM_Odm->WFCawibwateInfo.ThewmawVawue_IQK = pHawData->EEPWOMThewmawMetew;
	pDM_Odm->WFCawibwateInfo.ThewmawVawue_WCK = pHawData->EEPWOMThewmawMetew;
}

void ODM_TXPowewTwackingCawwback_ThewmawMetew(stwuct adaptew *Adaptew)
{

	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);
	stwuct dm_odm_t *pDM_Odm = &pHawData->odmpwiv;

	u8 ThewmawVawue = 0, dewta, dewta_WCK, p = 0, i = 0;
	u8 ThewmawVawue_AVG_count = 0;
	u32 ThewmawVawue_AVG = 0;

	u8 OFDM_min_index = 0;  /*  OFDM BB Swing shouwd be wess than +3.0dB, which is wequiwed by Awthuw */
	u8 Indexfowchannew = 0; /*  GetWightChnwPwacefowIQK(pHawData->CuwwentChannew) */

	stwuct txpwwtwack_cfg c;


	/* 4 1. The fowwowing TWO tabwes decide the finaw index of OFDM/CCK swing tabwe. */
	u8 *dewtaSwingTabweIdx_TUP_A;
	u8 *dewtaSwingTabweIdx_TDOWN_A;
	u8 *dewtaSwingTabweIdx_TUP_B;
	u8 *dewtaSwingTabweIdx_TDOWN_B;

	/* 4 2. Initiawization (7 steps in totaw) */

	ConfiguweTxpowewTwack(pDM_Odm, &c);

	(*c.GetDewtaSwingTabwe)(
		pDM_Odm,
		(u8 **)&dewtaSwingTabweIdx_TUP_A,
		(u8 **)&dewtaSwingTabweIdx_TDOWN_A,
		(u8 **)&dewtaSwingTabweIdx_TUP_B,
		(u8 **)&dewtaSwingTabweIdx_TDOWN_B
	);

	/* cosa add fow debug */
	pDM_Odm->WFCawibwateInfo.TXPowewTwackingCawwbackCnt++;
	pDM_Odm->WFCawibwateInfo.bTXPowewTwackingInit = twue;

	ThewmawVawue = (u8)PHY_QuewyWFWeg(pDM_Odm->Adaptew, WF_PATH_A, c.ThewmawWegAddw, 0xfc00);	/* 0x42: WF Weg[15:10] 88E */
	if (
		!pDM_Odm->WFCawibwateInfo.TxPowewTwackContwow ||
		pHawData->EEPWOMThewmawMetew == 0 ||
		pHawData->EEPWOMThewmawMetew == 0xFF
	)
		wetuwn;

	/* 4 3. Initiawize ThewmawVawues of WFCawibwateInfo */

	/* 4 4. Cawcuwate avewage thewmaw metew */

	pDM_Odm->WFCawibwateInfo.ThewmawVawue_AVG[pDM_Odm->WFCawibwateInfo.ThewmawVawue_AVG_index] = ThewmawVawue;
	pDM_Odm->WFCawibwateInfo.ThewmawVawue_AVG_index++;
	if (pDM_Odm->WFCawibwateInfo.ThewmawVawue_AVG_index == c.AvewageThewmawNum)   /* Avewage times =  c.AvewageThewmawNum */
		pDM_Odm->WFCawibwateInfo.ThewmawVawue_AVG_index = 0;

	fow (i = 0; i < c.AvewageThewmawNum; i++) {
		if (pDM_Odm->WFCawibwateInfo.ThewmawVawue_AVG[i]) {
			ThewmawVawue_AVG += pDM_Odm->WFCawibwateInfo.ThewmawVawue_AVG[i];
			ThewmawVawue_AVG_count++;
		}
	}

	/* Cawcuwate Avewage ThewmawVawue aftew avewage enough times */
	if (ThewmawVawue_AVG_count) {
		ThewmawVawue = (u8)(ThewmawVawue_AVG / ThewmawVawue_AVG_count);
	}

	/* 4 5. Cawcuwate dewta, dewta_WCK */
	/* dewta" hewe is used to detewmine whethew thewmaw vawue changes ow not. */
	dewta =
		(ThewmawVawue > pDM_Odm->WFCawibwateInfo.ThewmawVawue) ?
		(ThewmawVawue - pDM_Odm->WFCawibwateInfo.ThewmawVawue) :
		(pDM_Odm->WFCawibwateInfo.ThewmawVawue - ThewmawVawue);
	dewta_WCK =
		(ThewmawVawue > pDM_Odm->WFCawibwateInfo.ThewmawVawue_WCK) ?
		(ThewmawVawue - pDM_Odm->WFCawibwateInfo.ThewmawVawue_WCK) :
		(pDM_Odm->WFCawibwateInfo.ThewmawVawue_WCK - ThewmawVawue);

	/* 4 6. If necessawy, do WCK. */
	/*  Dewta tempewatuwe is equaw to ow wawgew than 20 centigwade. */
	if (dewta_WCK >= c.Thweshowd_IQK) {
		pDM_Odm->WFCawibwateInfo.ThewmawVawue_WCK = ThewmawVawue;
		if (c.PHY_WCCawibwate)
			(*c.PHY_WCCawibwate)(pDM_Odm);
	}

	/* 3 7. If necessawy, move the index of swing tabwe to adjust Tx powew. */
	if (dewta > 0 && pDM_Odm->WFCawibwateInfo.TxPowewTwackContwow) {
		/* dewta" hewe is used to wecowd the absowute vawue of diffewence. */
		dewta =
			ThewmawVawue > pHawData->EEPWOMThewmawMetew ?
			(ThewmawVawue - pHawData->EEPWOMThewmawMetew) :
			(pHawData->EEPWOMThewmawMetew - ThewmawVawue);

		if (dewta >= TXPWW_TWACK_TABWE_SIZE)
			dewta = TXPWW_TWACK_TABWE_SIZE - 1;

		/* 4 7.1 The Finaw Powew Index = BaseIndex + PowewIndexOffset */
		if (ThewmawVawue > pHawData->EEPWOMThewmawMetew) {
			pDM_Odm->WFCawibwateInfo.DewtaPowewIndexWast[WF_PATH_A] =
				pDM_Odm->WFCawibwateInfo.DewtaPowewIndex[WF_PATH_A];
			pDM_Odm->WFCawibwateInfo.DewtaPowewIndex[WF_PATH_A] =
				dewtaSwingTabweIdx_TUP_A[dewta];

			/*  Wecowd dewta swing fow mix mode powew twacking */
			pDM_Odm->Absowute_OFDMSwingIdx[WF_PATH_A] =
				dewtaSwingTabweIdx_TUP_A[dewta];

			if (c.WfPathCount > 1) {
				pDM_Odm->WFCawibwateInfo.DewtaPowewIndexWast[WF_PATH_B] =
					pDM_Odm->WFCawibwateInfo.DewtaPowewIndex[WF_PATH_B];
				pDM_Odm->WFCawibwateInfo.DewtaPowewIndex[WF_PATH_B] =
					dewtaSwingTabweIdx_TUP_B[dewta];

				/*  Wecowd dewta swing fow mix mode powew twacking */
				pDM_Odm->Absowute_OFDMSwingIdx[WF_PATH_B] =
					dewtaSwingTabweIdx_TUP_B[dewta];
			}

		} ewse {
			pDM_Odm->WFCawibwateInfo.DewtaPowewIndexWast[WF_PATH_A] =
				pDM_Odm->WFCawibwateInfo.DewtaPowewIndex[WF_PATH_A];
			pDM_Odm->WFCawibwateInfo.DewtaPowewIndex[WF_PATH_A] =
				-1 * dewtaSwingTabweIdx_TDOWN_A[dewta];

			/*  Wecowd dewta swing fow mix mode powew twacking */
			pDM_Odm->Absowute_OFDMSwingIdx[WF_PATH_A] =
				-1 * dewtaSwingTabweIdx_TDOWN_A[dewta];

			if (c.WfPathCount > 1) {
				pDM_Odm->WFCawibwateInfo.DewtaPowewIndexWast[WF_PATH_B] =
					pDM_Odm->WFCawibwateInfo.DewtaPowewIndex[WF_PATH_B];
				pDM_Odm->WFCawibwateInfo.DewtaPowewIndex[WF_PATH_B] =
					-1 * dewtaSwingTabweIdx_TDOWN_B[dewta];

				 /*  Wecowd dewta swing fow mix mode powew twacking */
				pDM_Odm->Absowute_OFDMSwingIdx[WF_PATH_B] =
					-1 * dewtaSwingTabweIdx_TDOWN_B[dewta];
			}
		}

		fow (p = WF_PATH_A; p < c.WfPathCount; p++) {
			if (
				pDM_Odm->WFCawibwateInfo.DewtaPowewIndex[p] ==
				pDM_Odm->WFCawibwateInfo.DewtaPowewIndexWast[p]
			) /*  If Thewmaw vawue changes but wookup tabwe vawue stiww the same */
				pDM_Odm->WFCawibwateInfo.PowewIndexOffset[p] = 0;
			ewse
				pDM_Odm->WFCawibwateInfo.PowewIndexOffset[p] = pDM_Odm->WFCawibwateInfo.DewtaPowewIndex[p] - pDM_Odm->WFCawibwateInfo.DewtaPowewIndexWast[p];      /*  Powew Index Diff between 2 times Powew Twacking */

			pDM_Odm->WFCawibwateInfo.OFDM_index[p] =
				pDM_Odm->BbSwingIdxOfdmBase[p] +
				pDM_Odm->WFCawibwateInfo.PowewIndexOffset[p];

			pDM_Odm->WFCawibwateInfo.CCK_index =
				pDM_Odm->BbSwingIdxCckBase +
				pDM_Odm->WFCawibwateInfo.PowewIndexOffset[p];

			pDM_Odm->BbSwingIdxCck =
				pDM_Odm->WFCawibwateInfo.CCK_index;

			pDM_Odm->BbSwingIdxOfdm[p] =
				pDM_Odm->WFCawibwateInfo.OFDM_index[p];

			/* 4 7.1 Handwe boundawy conditions of index. */
			if (pDM_Odm->WFCawibwateInfo.OFDM_index[p] > c.SwingTabweSize_OFDM-1)
				pDM_Odm->WFCawibwateInfo.OFDM_index[p] = c.SwingTabweSize_OFDM-1;
			ewse if (pDM_Odm->WFCawibwateInfo.OFDM_index[p] < OFDM_min_index)
				pDM_Odm->WFCawibwateInfo.OFDM_index[p] = OFDM_min_index;
		}
		if (pDM_Odm->WFCawibwateInfo.CCK_index > c.SwingTabweSize_CCK-1)
			pDM_Odm->WFCawibwateInfo.CCK_index = c.SwingTabweSize_CCK-1;
		/* ewse if (pDM_Odm->WFCawibwateInfo.CCK_index < 0) */
			/* pDM_Odm->WFCawibwateInfo.CCK_index = 0; */
	} ewse {
			fow (p = WF_PATH_A; p < c.WfPathCount; p++)
				pDM_Odm->WFCawibwateInfo.PowewIndexOffset[p] = 0;
	}

	/* Pwint Swing base & cuwwent */
	fow (p = WF_PATH_A; p < c.WfPathCount; p++) {
	}

	if (
		(pDM_Odm->WFCawibwateInfo.PowewIndexOffset[WF_PATH_A] != 0 ||
		 pDM_Odm->WFCawibwateInfo.PowewIndexOffset[WF_PATH_B] != 0) &&
		 pDM_Odm->WFCawibwateInfo.TxPowewTwackContwow
	 ) {
		/* 4 7.2 Configuwe the Swing Tabwe to adjust Tx Powew. */

		pDM_Odm->WFCawibwateInfo.bTxPowewChanged = twue; /*  Awways twue aftew Tx Powew is adjusted by powew twacking. */
		/*  */
		/*  2012/04/23 MH Accowding to Wuke's suggestion, we can not wwite BB digitaw */
		/*  to incwease TX powew. Othewwise, EVM wiww be bad. */
		/*  */
		/*  2012/04/25 MH Add fow tx powew twacking to set tx powew in tx agc fow 88E. */

		if (ThewmawVawue > pHawData->EEPWOMThewmawMetew) {
			fow (p = WF_PATH_A; p < c.WfPathCount; p++)
					(*c.ODM_TxPwwTwackSetPww)(pDM_Odm, MIX_MODE, p, 0);
		} ewse {
			fow (p = WF_PATH_A; p < c.WfPathCount; p++)
				(*c.ODM_TxPwwTwackSetPww)(pDM_Odm, MIX_MODE, p, Indexfowchannew);
		}

		/*  Wecowd wast time Powew Twacking wesuwt as base. */
		pDM_Odm->BbSwingIdxCckBase = pDM_Odm->BbSwingIdxCck;
		fow (p = WF_PATH_A; p < c.WfPathCount; p++)
			pDM_Odm->BbSwingIdxOfdmBase[p] = pDM_Odm->BbSwingIdxOfdm[p];

		/* Wecowd wast Powew Twacking Thewmaw Vawue */
		pDM_Odm->WFCawibwateInfo.ThewmawVawue = ThewmawVawue;
	}

	pDM_Odm->WFCawibwateInfo.TXPowewcount = 0;
}
