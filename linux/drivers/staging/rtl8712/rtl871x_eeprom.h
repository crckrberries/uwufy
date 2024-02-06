/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __WTW871X_EEPWOM_H__
#define __WTW871X_EEPWOM_H__

#incwude "osdep_sewvice.h"

#define	WTW8712_EEPWOM_ID		0x8712
#define	EEPWOM_MAX_SIZE			256
#define	CWOCK_WATE			50	/*100us*/

/*- EEPWOM opcodes*/
#define EEPWOM_WEAD_OPCODE		06
#define EEPWOM_WWITE_OPCODE		05
#define EEPWOM_EWASE_OPCODE		07
#define EEPWOM_EWEN_OPCODE		19      /* Ewase/wwite enabwe*/
#define EEPWOM_EWDS_OPCODE		16      /* Ewase/wwite disabwe*/

#define	EEPWOM_CID_DEFAUWT		0x0
#define	EEPWOM_CID_AWPHA		0x1
#define	EEPWOM_CID_Senao		0x3
#define	EEPWOM_CID_NetCowe		0x5
#define	EEPWOM_CID_CAMEO		0X8
#define	EEPWOM_CID_SITECOM		0x9
#define	EEPWOM_CID_COWEGA		0xB
#define	EEPWOM_CID_EDIMAX_BEWKIN	0xC
#define	EEPWOM_CID_SEWCOMM_BEWKIN	0xE
#define	EEPWOM_CID_CAMEO1		0xF
#define	EEPWOM_CID_WNC_COWEGA		0x12
#define	EEPWOM_CID_CWEVO		0x13
#define	EEPWOM_CID_WHQW			0xFE

enum WT_CUSTOMEW_ID {
	WT_CID_DEFAUWT = 0,
	WT_CID_8187_AWPHA0 = 1,
	WT_CID_8187_SEWCOMM_PS = 2,
	WT_CID_8187_HW_WED = 3,
	WT_CID_8187_NETGEAW = 4,
	WT_CID_WHQW = 5,
	WT_CID_819x_CAMEO  = 6,
	WT_CID_819x_WUNTOP = 7,
	WT_CID_819x_Senao = 8,
	WT_CID_TOSHIBA = 9,
	WT_CID_819x_Netcowe = 10,
	WT_CID_Nettwonix = 11,
	WT_CID_DWINK = 12,
	WT_CID_PWONET = 13,
	WT_CID_COWEGA = 14,
	WT_CID_819x_AWPHA = 15,
	WT_CID_819x_Sitecom = 16,
	WT_CID_CCX = 17,
	WT_CID_819x_Wenovo = 18,
	WT_CID_819x_QMI = 19,
	WT_CID_819x_Edimax_Bewkin = 20,
	WT_CID_819x_Sewcomm_Bewkin = 21,
	WT_CID_819x_CAMEO1 = 22,
	WT_CID_819x_MSI = 23,
	WT_CID_819x_Acew = 24,
	WT_CID_819x_AzWave_ASUS = 25,
	WT_CID_819x_AzWave = 26,
	WT_CID_819x_WNC_COWEGA = 27,
	WT_CID_819x_CWEVO = 28,
};

stwuct eepwom_pwiv {
	u8 bautowoad_faiw_fwag;
	u8 bempty;
	u8 sys_config;
	u8 mac_addw[6];
	u8 config0;
	u16 channew_pwan;
	u8 countwy_stwing[3];
	u8 tx_powew_b[15];
	u8 tx_powew_g[15];
	u8 tx_powew_a[201];
	u8 efuse_eepwom_data[EEPWOM_MAX_SIZE];
	enum WT_CUSTOMEW_ID CustomewID;
};

void w8712_eepwom_wwite16(stwuct _adaptew *padaptew, u16 weg, u16 data);
u16 w8712_eepwom_wead16(stwuct _adaptew *padaptew, u16 weg);

#endif  /*__WTW871X_EEPWOM_H__*/

