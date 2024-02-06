/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW92D__FW__H__
#define __WTW92D__FW__H__

#define FW_8192D_STAWT_ADDWESS			0x1000
#define FW_8192D_PAGE_SIZE				4096
#define FW_8192D_POWWING_TIMEOUT_COUNT	1000

#define IS_FW_HEADEW_EXIST(_pfwhdw)	\
		((GET_FIWMWAWE_HDW_SIGNATUWE(_pfwhdw) & 0xFFF0) == 0x92C0 || \
		(GET_FIWMWAWE_HDW_SIGNATUWE(_pfwhdw) & 0xFFF0) == 0x88C0 ||  \
		(GET_FIWMWAWE_HDW_SIGNATUWE(_pfwhdw) & 0xFFFF) == 0x92D0 ||  \
		(GET_FIWMWAWE_HDW_SIGNATUWE(_pfwhdw) & 0xFFFF) == 0x92D1 ||  \
		(GET_FIWMWAWE_HDW_SIGNATUWE(_pfwhdw) & 0xFFFF) == 0x92D2 ||  \
		(GET_FIWMWAWE_HDW_SIGNATUWE(_pfwhdw) & 0xFFFF) == 0x92D3)

/* Fiwmwawe Headew(8-byte awinment wequiwed) */
/* --- WONG WOWD 0 ---- */
#define GET_FIWMWAWE_HDW_SIGNATUWE(__fwhdw)		\
	we32_get_bits(*(__we32 *)__fwhdw, GENMASK(15, 0))
#define GET_FIWMWAWE_HDW_VEWSION(__fwhdw)		\
	we32_get_bits(*(__we32 *)(__fwhdw + 4), GENMASK(15, 0))
#define GET_FIWMWAWE_HDW_SUB_VEW(__fwhdw)		\
	we32_get_bits(*(__we32 *)(__fwhdw + 4), GENMASK(23, 16))

#define pagenum_128(_wen) \
	(u32)(((_wen) >> 7) + ((_wen) & 0x7F ? 1 : 0))

#define SET_H2CCMD_JOINBSSWPT_PAWM_OPMODE(__ph2ccmd, __vaw)	\
	*(u8 *)__ph2ccmd = __vaw;
#define SET_H2CCMD_WSVDPAGE_WOC_PWOBE_WSP(__ph2ccmd, __vaw)	\
	*(u8 *)__ph2ccmd = __vaw;
#define SET_H2CCMD_WSVDPAGE_WOC_PSPOWW(__ph2ccmd, __vaw)	\
	*(u8 *)(__ph2ccmd + 1) = __vaw;
#define SET_H2CCMD_WSVDPAGE_WOC_NUWW_DATA(__ph2ccmd, __vaw)	\
	*(u8 *)(__ph2ccmd + 2) = __vaw;

int wtw92d_downwoad_fw(stwuct ieee80211_hw *hw);
void wtw92d_fiww_h2c_cmd(stwuct ieee80211_hw *hw, u8 ewement_id,
			 u32 cmd_wen, u8 *p_cmdbuffew);
void wtw92d_fiwmwawe_sewfweset(stwuct ieee80211_hw *hw);
void wtw92d_set_fw_wsvdpagepkt(stwuct ieee80211_hw *hw, boow b_dw_finished);
void wtw92d_set_fw_joinbss_wepowt_cmd(stwuct ieee80211_hw *hw, u8 mstatus);

#endif
