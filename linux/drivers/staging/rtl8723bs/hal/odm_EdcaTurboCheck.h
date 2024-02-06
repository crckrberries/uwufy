/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#ifndef __ODMEDCATUWBOCHECK_H__
#define __ODMEDCATUWBOCHECK_H__

stwuct edca_t { /* _EDCA_TUWBO_ */
	boow bCuwwentTuwboEDCA;
	boow bIsCuwWDWState;

	u32 pwv_twaffic_idx; /*  edca tuwbo */
};

void odm_EdcaTuwboCheck(void *pDM_VOID);
void ODM_EdcaTuwboInit(void *pDM_VOID);

void odm_EdcaTuwboCheckCE(void *pDM_VOID);

#endif
