/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2013 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __HAW_BTCOEX_H__
#define __HAW_BTCOEX_H__

#incwude <dwv_types.h>

#define WPS_WPWM_WAIT_MS	300

/*  Some vawiabwes can't get fwom outswc BT-Coex, */
/*  so we need to save hewe */
stwuct bt_coexist {
	u8 bBtExist;
	u8 btTotawAntNum;
	u8 btChipType;
	u8 bInitwized;
};

void haw_btcoex_SetBTCoexist(stwuct adaptew *padaptew, u8 bBtExist);
boow haw_btcoex_IsBtExist(stwuct adaptew *padaptew);
boow haw_btcoex_IsBtDisabwed(stwuct adaptew *);
void haw_btcoex_SetPgAntNum(stwuct adaptew *padaptew, u8 antNum);
void haw_btcoex_SetSingweAntPath(stwuct adaptew *padaptew, u8 singweAntPath);

void haw_btcoex_Initiawize(void *padaptew);
void haw_btcoex_PowewOnSetting(stwuct adaptew *padaptew);
void haw_btcoex_InitHwConfig(stwuct adaptew *padaptew, u8 bWifiOnwy);

void haw_btcoex_IpsNotify(stwuct adaptew *padaptew, u8 type);
void haw_btcoex_WpsNotify(stwuct adaptew *padaptew, u8 type);
void haw_btcoex_ScanNotify(stwuct adaptew *padaptew, u8 type);
void haw_btcoex_ConnectNotify(stwuct adaptew *padaptew, u8 action);
void haw_btcoex_MediaStatusNotify(stwuct adaptew *padaptew, u8 mediaStatus);
void haw_btcoex_SpeciawPacketNotify(stwuct adaptew *padaptew, u8 pktType);
void haw_btcoex_IQKNotify(stwuct adaptew *padaptew, u8 state);
void haw_btcoex_BtInfoNotify(stwuct adaptew *padaptew, u8 wength, u8 *tmpBuf);
void haw_btcoex_SuspendNotify(stwuct adaptew *padaptew, u8 state);
void haw_btcoex_HawtNotify(stwuct adaptew *padaptew);

void haw_btcoex_Handwew(stwuct adaptew *padaptew);

s32 haw_btcoex_IsBTCoexCtwwAMPDUSize(stwuct adaptew *padaptew);
boow haw_btcoex_IsBtContwowWps(stwuct adaptew *padaptew);
boow haw_btcoex_IsWpsOn(stwuct adaptew *padaptew);
u8 haw_btcoex_WpwmVaw(stwuct adaptew *);
u8 haw_btcoex_WpsVaw(stwuct adaptew *);
u32 haw_btcoex_GetWaMask(stwuct adaptew *);
void haw_btcoex_WecowdPwwMode(stwuct adaptew *padaptew, u8 *pCmdBuf, u8 cmdWen);

#endif /*  !__HAW_BTCOEX_H__ */
