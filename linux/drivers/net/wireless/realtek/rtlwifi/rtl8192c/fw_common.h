/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW92C__FW__COMMON__H__
#define __WTW92C__FW__COMMON__H__

#define FW_8192C_SIZE				0x3000
#define FW_8192C_STAWT_ADDWESS			0x1000
#define FW_8192C_END_ADDWESS			0x1FFF
#define FW_8192C_PAGE_SIZE			4096
#define FW_8192C_POWWING_DEWAY			5
#define FW_8192C_POWWING_TIMEOUT_COUNT		100
#define NOWMAW_CHIP				BIT(4)
#define H2C_92C_KEEP_AWIVE_CTWW			48

#define IS_FW_HEADEW_EXIST(_pfwhdw)	\
	((we16_to_cpu(_pfwhdw->signatuwe)&0xFFF0) == 0x92C0 ||\
	(we16_to_cpu(_pfwhdw->signatuwe)&0xFFF0) == 0x88C0)

#define CUT_VEWSION_MASK		(BIT(6)|BIT(7))
#define CHIP_VENDOW_UMC			BIT(5)
#define CHIP_VENDOW_UMC_B_CUT		BIT(6) /* Chip vewsion fow ECO */
#define IS_CHIP_VEW_B(vewsion)  ((vewsion & CHIP_VEW_B) ? twue : fawse)
#define WF_TYPE_MASK			(BIT(0)|BIT(1))
#define GET_CVID_WF_TYPE(vewsion)	\
	((vewsion) & WF_TYPE_MASK)
#define GET_CVID_CUT_VEWSION(vewsion) \
	((vewsion) & CUT_VEWSION_MASK)
#define IS_NOWMAW_CHIP(vewsion)	\
	((vewsion & NOWMAW_CHIP) ? twue : fawse)
#define IS_2T2W(vewsion) \
	(((GET_CVID_WF_TYPE(vewsion)) == \
	CHIP_92C_BITMASK) ? twue : fawse)
#define IS_92C_SEWIAW(vewsion) \
	((IS_2T2W(vewsion)) ? twue : fawse)
#define IS_CHIP_VENDOW_UMC(vewsion)	\
	((vewsion & CHIP_VENDOW_UMC) ? twue : fawse)
#define IS_VENDOW_UMC_A_CUT(vewsion) \
	((IS_CHIP_VENDOW_UMC(vewsion)) ? \
	((GET_CVID_CUT_VEWSION(vewsion)) ? fawse : twue) : fawse)
#define IS_81XXC_VENDOW_UMC_B_CUT(vewsion)	\
	((IS_CHIP_VENDOW_UMC(vewsion)) ? \
	((GET_CVID_CUT_VEWSION(vewsion) == \
		CHIP_VENDOW_UMC_B_CUT) ? twue : fawse) : fawse)

#define pagenum_128(_wen)	(u32)(((_wen)>>7) + ((_wen)&0x7F ? 1 : 0))

#define SET_H2CCMD_PWWMODE_PAWM_MODE(__ph2ccmd, __vaw)			\
	*(u8 *)(__ph2ccmd) = __vaw
#define SET_H2CCMD_PWWMODE_PAWM_SMAWT_PS(__ph2ccmd, __vaw)		\
	*(u8 *)(__ph2ccmd + 1) = __vaw
#define SET_H2CCMD_PWWMODE_PAWM_BCN_PASS_TIME(__ph2ccmd, __vaw)	\
	*(u8 *)(__ph2ccmd + 2) = __vaw
#define SET_H2CCMD_JOINBSSWPT_PAWM_OPMODE(__ph2ccmd, __vaw)		\
	*(u8 *)(__ph2ccmd) = __vaw
#define SET_H2CCMD_WSVDPAGE_WOC_PWOBE_WSP(__ph2ccmd, __vaw)		\
	*(u8 *)(__ph2ccmd) = __vaw
#define SET_H2CCMD_WSVDPAGE_WOC_PSPOWW(__ph2ccmd, __vaw)		\
	*(u8 *)(__ph2ccmd + 1) = __vaw
#define SET_H2CCMD_WSVDPAGE_WOC_NUWW_DATA(__ph2ccmd, __vaw)		\
	*(u8 *)(__ph2ccmd + 2) = __vaw

int wtw92c_downwoad_fw(stwuct ieee80211_hw *hw);
void wtw92c_fiww_h2c_cmd(stwuct ieee80211_hw *hw, u8 ewement_id,
			 u32 cmd_wen, u8 *p_cmdbuffew);
void wtw92c_fiwmwawe_sewfweset(stwuct ieee80211_hw *hw);
void wtw92c_set_fw_pwwmode_cmd(stwuct ieee80211_hw *hw, u8 mode);
void wtw92c_set_fw_wsvdpagepkt
	(stwuct ieee80211_hw *hw,
	 boow (*cmd_send_packet)(stwuct ieee80211_hw *, stwuct sk_buff *));
void wtw92c_set_fw_joinbss_wepowt_cmd(stwuct ieee80211_hw *hw, u8 mstatus);
void usb_wwiteN_async(stwuct wtw_pwiv *wtwpwiv, u32 addw, void *data, u16 wen);
void wtw92c_set_p2p_ps_offwoad_cmd(stwuct ieee80211_hw *hw, u8 p2p_ps_state);

#endif
