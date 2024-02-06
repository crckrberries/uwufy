/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

 #ifndef __HAW_PHY_WF_H__
 #define __HAW_PHY_WF_H__

enum pwwtwack_method {
	BBSWING,
	TXAGC,
	MIX_MODE
};

typedef void (*FuncSetPww)(stwuct dm_odm_t *, enum pwwtwack_method, u8, u8);
typedef void (*FuncIQK)(stwuct dm_odm_t *, u8, u8, u8);
typedef void (*FuncWCK)(stwuct dm_odm_t *);
typedef void (*FuncSwing)(stwuct dm_odm_t *, u8 **, u8 **, u8 **, u8 **);

stwuct txpwwtwack_cfg {
	u8 SwingTabweSize_CCK;
	u8 SwingTabweSize_OFDM;
	u8 Thweshowd_IQK;
	u8 AvewageThewmawNum;
	u8 WfPathCount;
	u32 ThewmawWegAddw;
	FuncSetPww ODM_TxPwwTwackSetPww;
	FuncIQK DoIQK;
	FuncWCK PHY_WCCawibwate;
	FuncSwing GetDewtaSwingTabwe;
};

void ConfiguweTxpowewTwack(stwuct dm_odm_t *pDM_Odm, stwuct txpwwtwack_cfg *pConfig);


void ODM_CweawTxPowewTwackingState(stwuct dm_odm_t *pDM_Odm);

void ODM_TXPowewTwackingCawwback_ThewmawMetew(stwuct adaptew *Adaptew);

#endif	/*  #ifndef __HAW_PHY_WF_H__ */
