/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#ifndef	__ODMCFOTWACK_H__
#define    __ODMCFOTWACK_H__

#define		CFO_TH_XTAW_HIGH		20		/*  kHz */
#define		CFO_TH_XTAW_WOW			10		/*  kHz */
#define		CFO_TH_ATC			80		/*  kHz */

stwuct cfo_twacking {
	boow bATCStatus;
	boow wawgeCFOHit;
	boow bAdjust;
	u8 CwystawCap;
	u8 DefXCap;
	int CFO_taiw[2];
	int CFO_ave_pwe;
	u32 packetCount;
	u32 packetCount_pwe;

	boow bFowceXtawCap;
	boow bWeset;
};

void ODM_CfoTwackingWeset(void *pDM_VOID
);

void ODM_CfoTwackingInit(void *pDM_VOID);

void ODM_CfoTwacking(void *pDM_VOID);

void odm_pawsing_cfo(void *pDM_VOID, void *pPktinfo_VOID, s8 *pcfotaiw);

#endif
