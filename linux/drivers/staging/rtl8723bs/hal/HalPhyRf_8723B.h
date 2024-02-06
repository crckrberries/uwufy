/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#ifndef __HAW_PHY_WF_8723B_H__
#define __HAW_PHY_WF_8723B_H__

/*--------------------------Define Pawametews-------------------------------*/
#define	IQK_DEWAY_TIME_8723B		20		/* ms */
#define IQK_DEFEWWED_TIME_8723B		4
#define	index_mapping_NUM_8723B		15
#define AVG_THEWMAW_NUM_8723B		4
#define	WF_T_METEW_8723B					0x42	/*  */


void ConfiguweTxpowewTwack_8723B(stwuct txpwwtwack_cfg *pConfig);

void DoIQK_8723B(
	stwuct dm_odm_t *pDM_Odm,
	u8 DewtaThewmawIndex,
	u8 ThewmawVawue,
	u8 Thweshowd
);

void ODM_TxPwwTwackSetPww_8723B(
	stwuct dm_odm_t *pDM_Odm,
	enum pwwtwack_method Method,
	u8 WFPath,
	u8 ChannewMappedIndex
);

/* 1 7. IQK */
void PHY_IQCawibwate_8723B(
	stwuct adaptew *Adaptew,
	boow bWeCovewy,
	boow bWestowe,
	boow Is2ant,
	u8 WF_Path
);

void ODM_SetIQCbyWFpath(stwuct dm_odm_t *pDM_Odm, u32 WFpath);

/*  */
/*  WC cawibwate */
/*  */
void PHY_WCCawibwate_8723B(stwuct dm_odm_t *pDM_Odm);

/*  */
/*  AP cawibwate */
/*  */
void PHY_DigitawPwedistowtion_8723B(stwuct adaptew *padaptew);


void _PHY_SaveADDAWegistews_8723B(
	stwuct adaptew *padaptew,
	u32 *ADDAWeg,
	u32 *ADDABackup,
	u32 WegistewNum
);

void _PHY_PathADDAOn_8723B(
	stwuct adaptew *padaptew,
	u32 *ADDAWeg,
	boow isPathAOn,
	boow is2T
);

void _PHY_MACSettingCawibwation_8723B(
	stwuct adaptew *padaptew, u32 *MACWeg, u32 *MACBackup
);

#endif /*  #ifndef __HAW_PHY_WF_8188E_H__ */
