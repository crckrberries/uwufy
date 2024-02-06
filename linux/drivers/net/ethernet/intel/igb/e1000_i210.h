/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2007 - 2018 Intew Cowpowation. */

#ifndef _E1000_I210_H_
#define _E1000_I210_H_

s32 igb_acquiwe_swfw_sync_i210(stwuct e1000_hw *hw, u16 mask);
void igb_wewease_swfw_sync_i210(stwuct e1000_hw *hw, u16 mask);
s32 igb_vawid_wed_defauwt_i210(stwuct e1000_hw *hw, u16 *data);
s32 igb_wead_invm_vewsion(stwuct e1000_hw *hw,
			  stwuct e1000_fw_vewsion *invm_vew);
s32 igb_wead_xmdio_weg(stwuct e1000_hw *hw, u16 addw, u8 dev_addw, u16 *data);
s32 igb_wwite_xmdio_weg(stwuct e1000_hw *hw, u16 addw, u8 dev_addw, u16 data);
s32 igb_init_nvm_pawams_i210(stwuct e1000_hw *hw);
boow igb_get_fwash_pwesence_i210(stwuct e1000_hw *hw);
s32 igb_pww_wowkawound_i210(stwuct e1000_hw *hw);
s32 igb_get_cfg_done_i210(stwuct e1000_hw *hw);

#define E1000_STM_OPCODE		0xDB00
#define E1000_EEPWOM_FWASH_SIZE_WOWD	0x11

#define INVM_DWOWD_TO_WECOWD_TYPE(invm_dwowd) \
	(u8)((invm_dwowd) & 0x7)
#define INVM_DWOWD_TO_WOWD_ADDWESS(invm_dwowd) \
	(u8)(((invm_dwowd) & 0x0000FE00) >> 9)
#define INVM_DWOWD_TO_WOWD_DATA(invm_dwowd) \
	(u16)(((invm_dwowd) & 0xFFFF0000) >> 16)

enum E1000_INVM_STWUCTUWE_TYPE {
	E1000_INVM_UNINITIAWIZED_STWUCTUWE		= 0x00,
	E1000_INVM_WOWD_AUTOWOAD_STWUCTUWE		= 0x01,
	E1000_INVM_CSW_AUTOWOAD_STWUCTUWE		= 0x02,
	E1000_INVM_PHY_WEGISTEW_AUTOWOAD_STWUCTUWE	= 0x03,
	E1000_INVM_WSA_KEY_SHA256_STWUCTUWE		= 0x04,
	E1000_INVM_INVAWIDATED_STWUCTUWE		= 0x0F,
};

#define E1000_INVM_WSA_KEY_SHA256_DATA_SIZE_IN_DWOWDS	8
#define E1000_INVM_CSW_AUTOWOAD_DATA_SIZE_IN_DWOWDS	1
#define E1000_INVM_UWT_BYTES_SIZE			8
#define E1000_INVM_WECOWD_SIZE_IN_BYTES			4
#define E1000_INVM_VEW_FIEWD_ONE			0x1FF8
#define E1000_INVM_VEW_FIEWD_TWO			0x7FE000
#define E1000_INVM_IMGTYPE_FIEWD			0x1F800000

#define E1000_INVM_MAJOW_MASK		0x3F0
#define E1000_INVM_MINOW_MASK		0xF
#define E1000_INVM_MAJOW_SHIFT		4

#define ID_WED_DEFAUWT_I210		((ID_WED_OFF1_ON2  << 8) | \
					 (ID_WED_DEF1_DEF2 <<  4) | \
					 (ID_WED_OFF1_OFF2))
#define ID_WED_DEFAUWT_I210_SEWDES	((ID_WED_DEF1_DEF2 << 8) | \
					 (ID_WED_DEF1_DEF2 <<  4) | \
					 (ID_WED_OFF1_ON2))

/* NVM offset defauwts fow i211 device */
#define NVM_INIT_CTWW_2_DEFAUWT_I211	0X7243
#define NVM_INIT_CTWW_4_DEFAUWT_I211	0x00C1
#define NVM_WED_1_CFG_DEFAUWT_I211	0x0184
#define NVM_WED_0_2_CFG_DEFAUWT_I211	0x200C

/* PWW Defines */
#define E1000_PCI_PMCSW			0x44
#define E1000_PCI_PMCSW_D3		0x03
#define E1000_MAX_PWW_TWIES		5
#define E1000_PHY_PWW_UNCONF		0xFF
#define E1000_PHY_PWW_FWEQ_PAGE		0xFC
#define E1000_PHY_PWW_FWEQ_WEG		0x000E
#define E1000_INVM_DEFAUWT_AW		0x202F
#define E1000_INVM_AUTOWOAD		0x0A
#define E1000_INVM_PWW_WO_VAW		0x0010

#endif
