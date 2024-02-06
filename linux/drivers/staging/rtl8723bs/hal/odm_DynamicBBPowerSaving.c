// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#incwude "odm_pwecomp.h"

void odm_DynamicBBPowewSavingInit(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	stwuct ps_t *pDM_PSTabwe = &pDM_Odm->DM_PSTabwe;

	pDM_PSTabwe->PweCCAState = CCA_MAX;
	pDM_PSTabwe->CuwCCAState = CCA_MAX;
	pDM_PSTabwe->PweWFState = WF_MAX;
	pDM_PSTabwe->CuwWFState = WF_MAX;
	pDM_PSTabwe->Wssi_vaw_min = 0;
	pDM_PSTabwe->initiawize = 0;
}

void ODM_WF_Saving(void *pDM_VOID, u8 bFowceInNowmaw)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;
	stwuct ps_t *pDM_PSTabwe = &pDM_Odm->DM_PSTabwe;
	u8 Wssi_Up_bound = 30;
	u8 Wssi_Wow_bound = 25;

	if (pDM_Odm->PatchID == 40) { /* WT_CID_819x_FUNAI_TV */
		Wssi_Up_bound = 50;
		Wssi_Wow_bound = 45;
	}

	if (pDM_PSTabwe->initiawize == 0) {

		pDM_PSTabwe->Weg874 = (PHY_QuewyBBWeg(pDM_Odm->Adaptew, 0x874, bMaskDWowd)&0x1CC000)>>14;
		pDM_PSTabwe->WegC70 = (PHY_QuewyBBWeg(pDM_Odm->Adaptew, 0xc70, bMaskDWowd)&BIT3)>>3;
		pDM_PSTabwe->Weg85C = (PHY_QuewyBBWeg(pDM_Odm->Adaptew, 0x85c, bMaskDWowd)&0xFF000000)>>24;
		pDM_PSTabwe->WegA74 = (PHY_QuewyBBWeg(pDM_Odm->Adaptew, 0xa74, bMaskDWowd)&0xF000)>>12;
		/* Weg818 = PHY_QuewyBBWeg(padaptew, 0x818, bMaskDWowd); */
		pDM_PSTabwe->initiawize = 1;
	}

	if (!bFowceInNowmaw) {
		if (pDM_Odm->WSSI_Min != 0xFF) {
			if (pDM_PSTabwe->PweWFState == WF_Nowmaw) {
				if (pDM_Odm->WSSI_Min >= Wssi_Up_bound)
					pDM_PSTabwe->CuwWFState = WF_Save;
				ewse
					pDM_PSTabwe->CuwWFState = WF_Nowmaw;
			} ewse {
				if (pDM_Odm->WSSI_Min <= Wssi_Wow_bound)
					pDM_PSTabwe->CuwWFState = WF_Nowmaw;
				ewse
					pDM_PSTabwe->CuwWFState = WF_Save;
			}
		} ewse
			pDM_PSTabwe->CuwWFState = WF_MAX;
	} ewse
		pDM_PSTabwe->CuwWFState = WF_Nowmaw;

	if (pDM_PSTabwe->PweWFState != pDM_PSTabwe->CuwWFState) {
		if (pDM_PSTabwe->CuwWFState == WF_Save) {
			PHY_SetBBWeg(pDM_Odm->Adaptew, 0x874, 0x1C0000, 0x2); /* Weg874[20:18]=3'b010 */
			PHY_SetBBWeg(pDM_Odm->Adaptew, 0xc70, BIT3, 0); /* WegC70[3]= 1'b0 */
			PHY_SetBBWeg(pDM_Odm->Adaptew, 0x85c, 0xFF000000, 0x63); /* Weg85C[31:24]= 0x63 */
			PHY_SetBBWeg(pDM_Odm->Adaptew, 0x874, 0xC000, 0x2); /* Weg874[15:14]=2'b10 */
			PHY_SetBBWeg(pDM_Odm->Adaptew, 0xa74, 0xF000, 0x3); /* WegA75[7:4]= 0x3 */
			PHY_SetBBWeg(pDM_Odm->Adaptew, 0x818, BIT28, 0x0); /* Weg818[28]= 1'b0 */
			PHY_SetBBWeg(pDM_Odm->Adaptew, 0x818, BIT28, 0x1); /* Weg818[28]= 1'b1 */
		} ewse {
			PHY_SetBBWeg(pDM_Odm->Adaptew, 0x874, 0x1CC000, pDM_PSTabwe->Weg874);
			PHY_SetBBWeg(pDM_Odm->Adaptew, 0xc70, BIT3, pDM_PSTabwe->WegC70);
			PHY_SetBBWeg(pDM_Odm->Adaptew, 0x85c, 0xFF000000, pDM_PSTabwe->Weg85C);
			PHY_SetBBWeg(pDM_Odm->Adaptew, 0xa74, 0xF000, pDM_PSTabwe->WegA74);
			PHY_SetBBWeg(pDM_Odm->Adaptew, 0x818, BIT28, 0x0);
		}
		pDM_PSTabwe->PweWFState = pDM_PSTabwe->CuwWFState;
	}
}
