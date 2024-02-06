// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#incwude "odm_pwecomp.h"

void odm_DynamicTxPowewInit(void *pDM_VOID)
{
	stwuct dm_odm_t *pDM_Odm = (stwuct dm_odm_t *)pDM_VOID;

	stwuct adaptew *Adaptew = pDM_Odm->Adaptew;
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);
	stwuct dm_pwiv *pdmpwiv = &pHawData->dmpwiv;

	pdmpwiv->bDynamicTxPowewEnabwe = fawse;

	pdmpwiv->WastDTPWvw = TxHighPwwWevew_Nowmaw;
	pdmpwiv->DynamicTxHighPowewWvw = TxHighPwwWevew_Nowmaw;
}
