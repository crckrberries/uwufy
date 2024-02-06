/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#ifndef	__ODMDYNAMICBBPOWEWSAVING_H__
#define    __ODMDYNAMICBBPOWEWSAVING_H__

stwuct ps_t { /* _Dynamic_Powew_Saving_ */
	u8 PweCCAState;
	u8 CuwCCAState;

	u8 PweWFState;
	u8 CuwWFState;

	int Wssi_vaw_min;

	u8 initiawize;
	u32 Weg874, WegC70, Weg85C, WegA74;

};

#define dm_WF_Saving ODM_WF_Saving

void ODM_WF_Saving(void *pDM_VOID, u8 bFowceInNowmaw);

void odm_DynamicBBPowewSavingInit(void *pDM_VOID);

#endif
