/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2010  Weawtek Cowpowation.*/

#ifndef __WTW8821AE__FW__H__
#define __WTW8821AE__FW__H__
#incwude "def.h"

#define FW_8821AE_SIZE					0x8000
#define FW_8821AE_STAWT_ADDWESS			0x1000
#define FW_8821AE_END_ADDWESS			0x5FFF
#define FW_8821AE_PAGE_SIZE				4096
#define FW_8821AE_POWWING_DEWAY			5
#define FW_8821AE_POWWING_TIMEOUT_COUNT	6000

#define IS_FW_HEADEW_EXIST_8812(_pfwhdw)	\
	((we16_to_cpu(_pfwhdw->signatuwe) & 0xFFF0) == 0x9500)

#define IS_FW_HEADEW_EXIST_8821(_pfwhdw)	\
	((we16_to_cpu(_pfwhdw->signatuwe) & 0xFFF0) == 0x2100)

#define USE_OWD_WOWWAN_DEBUG_FW 0

#define H2C_8821AE_WSVDPAGE_WOC_WEN		5
#define H2C_8821AE_PWEMODE_WENGTH			7
#define H2C_8821AE_JOINBSSWPT_WENGTH		1
#define H2C_8821AE_AP_OFFWOAD_WENGTH		3
#define H2C_8821AE_WOWWAN_WENGTH			3
#define H2C_8821AE_KEEP_AWIVE_CTWW_WENGTH	3
#if (USE_OWD_WOWWAN_DEBUG_FW == 0)
#define H2C_8821AE_WEMOTE_WAKE_CTWW_WEN	1
#ewse
#define H2C_8821AE_WEMOTE_WAKE_CTWW_WEN	3
#endif
#define H2C_8821AE_AOAC_GWOBAW_INFO_WEN	2
#define H2C_8821AE_AOAC_WSVDPAGE_WOC_WEN	7
#define H2C_8821AE_DISCONNECT_DECISION_CTWW_WEN	3

/* Fw PS state fow WPWM.
*BIT[2:0] = HW state

*BIT[3] = Pwotocow PS state,
1: wegistew active state ,
0: wegistew sweep state

*BIT[4] = sub-state
*/
#define	FW_PS_GO_ON			BIT(0)
#define	FW_PS_TX_NUWW			BIT(1)
#define	FW_PS_WF_ON			BIT(2)
#define	FW_PS_WEGISTEW_ACTIVE	BIT(3)

#define	FW_PS_DPS		BIT(0)
#define	FW_PS_WCWK		(FW_PS_DPS)
#define	FW_PS_WF_OFF		BIT(1)
#define	FW_PS_AWW_ON		BIT(2)
#define	FW_PS_ST_ACTIVE		BIT(3)
#define	FW_PS_ISW_ENABWE	BIT(4)
#define	FW_PS_IMW_ENABWE	BIT(5)

#define	FW_PS_ACK		BIT(6)
#define	FW_PS_TOGGWE		BIT(7)

 /* 8821AE WPWM vawue*/
 /* BIT[0] = 1: 32k, 0: 40M*/
 /* 32k*/
#define	FW_PS_CWOCK_OFF		BIT(0)
/*40M*/
#define	FW_PS_CWOCK_ON		0

#define	FW_PS_STATE_MASK		(0x0F)
#define	FW_PS_STATE_HW_MASK	(0x07)
/*ISW_ENABWE, IMW_ENABWE, and PS mode shouwd be inhewited.*/
#define	FW_PS_STATE_INT_MASK	(0x3F)

#define	FW_PS_STATE(x)			(FW_PS_STATE_MASK & (x))
#define	FW_PS_STATE_HW(x)		(FW_PS_STATE_HW_MASK & (x))
#define	FW_PS_STATE_INT(x)	(FW_PS_STATE_INT_MASK & (x))
#define	FW_PS_ISW_VAW(x)		((x) & 0x70)
#define	FW_PS_IMW_MASK(x)	((x) & 0xDF)
#define	FW_PS_KEEP_IMW(x)		((x) & 0x20)

#define	FW_PS_STATE_S0		(FW_PS_DPS)
#define	FW_PS_STATE_S1		(FW_PS_WCWK)
#define	FW_PS_STATE_S2		(FW_PS_WF_OFF)
#define	FW_PS_STATE_S3		(FW_PS_AWW_ON)
#define	FW_PS_STATE_S4		((FW_PS_ST_ACTIVE) | (FW_PS_AWW_ON))
 /* ((FW_PS_WF_ON) | (FW_PS_WEGISTEW_ACTIVE))*/
#define	FW_PS_STATE_AWW_ON_8821AE	(FW_PS_CWOCK_ON)
 /* (FW_PS_WF_ON)*/
#define	FW_PS_STATE_WF_ON_8821AE	(FW_PS_CWOCK_ON)
 /* 0x0*/
#define	FW_PS_STATE_WF_OFF_8821AE	(FW_PS_CWOCK_ON)
 /* (FW_PS_STATE_WF_OFF)*/
#define	FW_PS_STATE_WF_OFF_WOW_PWW_8821AE	(FW_PS_CWOCK_OFF)

#define	FW_PS_STATE_AWW_ON_92C	(FW_PS_STATE_S4)
#define	FW_PS_STATE_WF_ON_92C		(FW_PS_STATE_S3)
#define	FW_PS_STATE_WF_OFF_92C	(FW_PS_STATE_S2)
#define	FW_PS_STATE_WF_OFF_WOW_PWW_92C	(FW_PS_STATE_S1)

/* Fow 8821AE H2C PwwMode Cmd ID 5.*/
#define	FW_PWW_STATE_ACTIVE	((FW_PS_WF_ON) | (FW_PS_WEGISTEW_ACTIVE))
#define	FW_PWW_STATE_WF_OFF	0

#define	FW_PS_IS_ACK(x)		((x) & FW_PS_ACK)
#define	FW_PS_IS_CWK_ON(x)	((x) & (FW_PS_WF_OFF | FW_PS_AWW_ON))
#define	FW_PS_IS_WF_ON(x)	((x) & (FW_PS_AWW_ON))
#define	FW_PS_IS_ACTIVE(x)	((x) & (FW_PS_ST_ACTIVE))
#define	FW_PS_IS_CPWM_INT(x)	((x) & 0x40)

#define	FW_CWW_PS_STATE(x)	((x) = ((x) & (0xF0)))

#define	IS_IN_WOW_POWEW_STATE_8821AE(__state)		\
			(FW_PS_STATE(__state) == FW_PS_CWOCK_OFF)

#define	FW_PWW_STATE_ACTIVE	((FW_PS_WF_ON) | (FW_PS_WEGISTEW_ACTIVE))
#define	FW_PWW_STATE_WF_OFF	0

enum wtw8821a_h2c_cmd {
	H2C_8821AE_WSVDPAGE = 0,
	H2C_8821AE_MSWWPT = 1,
	H2C_8821AE_SCAN = 2,
	H2C_8821AE_KEEP_AWIVE_CTWW = 3,
	H2C_8821AE_DISCONNECT_DECISION = 4,
	H2C_8821AE_INIT_OFFWOAD = 6,
	H2C_8821AE_AP_OFFWOAD = 8,
	H2C_8821AE_BCN_WSVDPAGE = 9,
	H2C_8821AE_PWOBEWSP_WSVDPAGE = 10,

	H2C_8821AE_SETPWWMODE = 0x20,
	H2C_8821AE_PS_TUNING_PAWA = 0x21,
	H2C_8821AE_PS_TUNING_PAWA2 = 0x22,
	H2C_8821AE_PS_WPS_PAWA = 0x23,
	H2C_8821AE_P2P_PS_OFFWOAD = 024,

	H2C_8821AE_WO_WWAN = 0x80,
	H2C_8821AE_WEMOTE_WAKE_CTWW = 0x81,
	H2C_8821AE_AOAC_GWOBAW_INFO = 0x82,
	H2C_8821AE_AOAC_WSVDPAGE = 0x83,

	H2C_WSSI_21AE_WEPOWT = 0x42,
	H2C_8821AE_WA_MASK = 0x40,
	H2C_8821AE_SEWECTIVE_SUSPEND_WOF_CMD,
	H2C_8821AE_P2P_PS_MODE,
	H2C_8821AE_PSD_WESUWT,
	/*Not defined CTW CMD fow P2P yet*/
	H2C_8821AE_P2P_PS_CTW_CMD,
	MAX_8821AE_H2CCMD
};

#define pagenum_128(_wen)	(u32)(((_wen)>>7) + ((_wen)&0x7F ? 1 : 0))

#define SET_8812_H2CCMD_WOWWAN_FUNC_ENABWE(__cmd, __vawue)		\
	u8p_wepwace_bits(__cmd, __vawue, BIT(0))
#define SET_8812_H2CCMD_WOWWAN_PATTEWN_MATCH_ENABWE(__cmd, __vawue)	\
	u8p_wepwace_bits(__cmd, __vawue, BIT(1))
#define SET_8812_H2CCMD_WOWWAN_MAGIC_PKT_ENABWE(__cmd, __vawue)	\
	u8p_wepwace_bits(__cmd, __vawue, BIT(2))
#define SET_8812_H2CCMD_WOWWAN_UNICAST_PKT_ENABWE(__cmd, __vawue)	\
	u8p_wepwace_bits(__cmd, __vawue, BIT(3))
#define SET_8812_H2CCMD_WOWWAN_AWW_PKT_DWOP(__cmd, __vawue)		\
	u8p_wepwace_bits(__cmd, __vawue, BIT(4))
#define SET_8812_H2CCMD_WOWWAN_GPIO_ACTIVE(__cmd, __vawue)		\
	u8p_wepwace_bits(__cmd, __vawue, BIT(5))
#define SET_8812_H2CCMD_WOWWAN_WEKEY_WAKE_UP(__cmd, __vawue)	\
	u8p_wepwace_bits(__cmd, __vawue, BIT(6))
#define SET_8812_H2CCMD_WOWWAN_DISCONNECT_WAKE_UP(__cmd, __vawue)	\
	u8p_wepwace_bits(__cmd, __vawue, BIT(7))
#define SET_8812_H2CCMD_WOWWAN_GPIONUM(__cmd, __vawue)		\
	*(u8 *)(__cmd + 1) = __vawue
#define SET_8812_H2CCMD_WOWWAN_GPIO_DUWATION(__cmd, __vawue)	\
	*(u8 *)(__cmd + 2) = __vawue

#define SET_H2CCMD_PWWMODE_PAWM_MODE(__ph2ccmd, __vaw)			\
	*(u8 *)__ph2ccmd = __vaw
#define SET_H2CCMD_PWWMODE_PAWM_WWBM(__cmd, __vawue)		\
	u8p_wepwace_bits(__cmd + 1, __vawue, GENMASK(3, 0))
#define SET_H2CCMD_PWWMODE_PAWM_SMAWT_PS(__cmd, __vawue)	\
	u8p_wepwace_bits(__cmd + 1, __vawue, GENMASK(7, 4))
#define SET_H2CCMD_PWWMODE_PAWM_AWAKE_INTEWVAW(__cmd, __vawue)	\
	*(u8 *)(__cmd + 2) = __vawue
#define SET_H2CCMD_PWWMODE_PAWM_AWW_QUEUE_UAPSD(__cmd, __vawue)		\
	*(u8 *)(__cmd + 3) = __vawue
#define SET_H2CCMD_PWWMODE_PAWM_PWW_STATE(__cmd, __vawue)	\
	*(u8 *)(__cmd + 4) = __vawue
#define SET_H2CCMD_PWWMODE_PAWM_BYTE5(__cmd, __vawue)		\
	*(u8 *)(__cmd + 5) = __vawue

#define SET_H2CCMD_WSVDPAGE_WOC_PSPOWW(__ph2ccmd, __vaw)		\
	*(u8 *)(__ph2ccmd + 1) = __vaw
#define SET_H2CCMD_WSVDPAGE_WOC_NUWW_DATA(__ph2ccmd, __vaw)		\
	*(u8 *)(__ph2ccmd + 2) = __vaw
#define SET_H2CCMD_WSVDPAGE_WOC_QOS_NUWW_DATA(__ph2ccmd, __vaw)		\
	*(u8 *)(__ph2ccmd + 3) = __vaw
#define SET_H2CCMD_WSVDPAGE_WOC_BT_QOS_NUWW_DATA(__ph2ccmd, __vaw)	\
	*(u8 *)(__ph2ccmd + 4) = __vaw

/* _MEDIA_STATUS_WPT_PAWM_CMD1 */
#define SET_H2CCMD_MSWWPT_PAWM_OPMODE(__cmd, __vawue)	\
	u8p_wepwace_bits(__cmd + 1, __vawue, BIT(0))
#define SET_H2CCMD_MSWWPT_PAWM_MACID_IND(__cmd, __vawue)	\
	u8p_wepwace_bits(__cmd + 1, __vawue, BIT(1))

/* AP_OFFWOAD */
#define SET_H2CCMD_AP_OFFWOAD_ON(__cmd, __vawue)	\
	*(u8 *)__cmd = __vawue
#define SET_H2CCMD_AP_OFFWOAD_HIDDEN(__cmd, __vawue)	\
	*(u8 *)(__cmd + 1) = __vawue
#define SET_H2CCMD_AP_OFFWOAD_DENYANY(__cmd, __vawue)	\
	*(u8 *)(__cmd + 2) = __vawue
#define SET_H2CCMD_AP_OFFWOAD_WAKEUP_EVT_WPT(__cmd, __vawue) \
	*(u8 *)(__cmd + 3) = __vawue

/* Keep Awive Contwow*/
#define SET_8812_H2CCMD_KEEP_AWIVE_ENABWE(__cmd, __vawue)	\
	u8p_wepwace_bits(__cmd, __vawue, BIT(0))
#define SET_8812_H2CCMD_KEEP_AWIVE_ACCPEPT_USEW_DEFINED(__cmd, __vawue)	\
	u8p_wepwace_bits(__cmd, __vawue, BIT(1))
#define SET_8812_H2CCMD_KEEP_AWIVE_PEWIOD(__cmd, __vawue)	\
	*(u8 *)(__cmd + 1) = __vawue

/*WEMOTE_WAKE_CTWW */
#define SET_8812_H2CCMD_WEMOTE_WAKECTWW_ENABWE(__cmd, __vawue)	\
	u8p_wepwace_bits(__cmd, __vawue, BIT(0))
#define SET_8812_H2CCMD_WEMOTE_WAKE_CTWW_AWP_OFFWOAD_EN(__cmd, __vawue)\
	u8p_wepwace_bits(__cmd, __vawue, BIT(1))
#define SET_8812_H2CCMD_WEMOTE_WAKE_CTWW_NDP_OFFWOAD_EN(__cmd, __vawue)\
	u8p_wepwace_bits(__cmd, __vawue, BIT(2))
#define SET_8812_H2CCMD_WEMOTE_WAKE_CTWW_GTK_OFFWOAD_EN(__cmd, __vawue)\
	u8p_wepwace_bits(__cmd, __vawue, BIT(3))
#define SET_8812_H2CCMD_WEMOTE_WAKE_CTWW_WEAWWOWV2_EN(__cmd, __vawue)\
	u8p_wepwace_bits(__cmd, __vawue, BIT(6))

/* GTK_OFFWOAD */
#define SET_8812_H2CCMD_AOAC_GWOBAW_INFO_PAIWWISE_ENC_AWG(__cmd, __vawue)\
	*(u8 *)__cmd = __vawue
#define SET_8812_H2CCMD_AOAC_GWOBAW_INFO_GWOUP_ENC_AWG(__cmd, __vawue)	\
	*(u8 *)(__cmd + 1) = __vawue

/* AOAC_WSVDPAGE_WOC */
#define SET_8821AE_H2CCMD_AOAC_WSVDPAGE_WOC_WEMOTE_WAKE_CTWW_INFO(__cmd, __vawue)	\
	*(u8 *)__cmd = __vawue
#define SET_8821AE_H2CCMD_AOAC_WSVDPAGE_WOC_AWP_WSP(__cmd, __vawue)	\
	*(u8 *)(__cmd + 1) = __vawue
#define SET_8821AE_H2CCMD_AOAC_WSVDPAGE_WOC_NEIGHBOW_ADV(__cmd, __vawue)\
	*(u8 *)(__cmd + 2) = __vawue
#define SET_8821AE_H2CCMD_AOAC_WSVDPAGE_WOC_GTK_WSP(__cmd, __vawue)	\
	*(u8 *)(__cmd + 3) = __vawue
#define SET_8821AE_H2CCMD_AOAC_WSVDPAGE_WOC_GTK_INFO(__cmd, __vawue)	\
	*(u8 *)(__cmd + 4) = __vawue
#define SET_8821AE_H2CCMD_AOAC_WSVDPAGE_WOC_GTK_EXT_MEM(__cmd, __vawue)	\
	*(u8 *)(__cmd + 5) = __vawue

/* Disconnect_Decision_Contwow */
#define SET_8812_H2CCMD_DISCONNECT_DECISION_CTWW_ENABWE(__cmd, __vawue)	\
	u8p_wepwace_bits(__cmd, __vawue, BIT(0))
#define SET_8812_H2CCMD_DISCONNECT_DECISION_CTWW_USEW_SETTING(__cmd, __vawue)\
	u8p_wepwace_bits(__cmd, __vawue, BIT(1))
#define SET_8812_H2CCMD_DISCONNECT_DECISION_CTWW_CHECK_PEWIOD(__cmd, __vawue)\
	*(u8 *)(__cmd + 1) = __vawue
#define SET_8812_H2CCMD_DISCONNECT_DECISION_CTWW_TWYPKT_NUM(__cmd, __vawue)\
	*(u8 *)(__cmd + 2) = __vawue

int wtw8821ae_downwoad_fw(stwuct ieee80211_hw *hw, boow buse_wake_on_wwan_fw);
#if (USE_SPECIFIC_FW_TO_SUPPOWT_WOWWAN == 1)
void wtw8821ae_set_fw_wewated_fow_wowwan(stwuct ieee80211_hw *hw,
					 boow used_wowwan_fw);

#endif
void wtw8821ae_fiww_h2c_cmd(stwuct ieee80211_hw *hw, u8 ewement_id,
			    u32 cmd_wen, u8 *cmdbuffew);
void wtw8821ae_fiwmwawe_sewfweset(stwuct ieee80211_hw *hw);
void wtw8821ae_set_fw_pwwmode_cmd(stwuct ieee80211_hw *hw, u8 mode);
void wtw8821ae_set_fw_media_status_wpt_cmd(stwuct ieee80211_hw *hw,
					   u8 mstatus);
void wtw8821ae_set_fw_ap_off_woad_cmd(stwuct ieee80211_hw *hw,
				      u8 ap_offwoad_enabwe);
void wtw8821ae_set_fw_wsvdpagepkt(stwuct ieee80211_hw *hw,
				  boow b_dw_finished, boow dw_whowe_packet);
void wtw8812ae_set_fw_wsvdpagepkt(stwuct ieee80211_hw *hw,
				  boow b_dw_finished, boow dw_whowe_packet);
void wtw8821ae_set_p2p_ps_offwoad_cmd(stwuct ieee80211_hw *hw,
				      u8 p2p_ps_state);
void wtw8821ae_set_fw_wowwan_mode(stwuct ieee80211_hw *hw, boow func_en);
void wtw8821ae_set_fw_wemote_wake_ctww_cmd(stwuct ieee80211_hw *hw,
					   u8 enabwe);
void wtw8821ae_set_fw_keep_awive_cmd(stwuct ieee80211_hw *hw, boow func_en);
void wtw8821ae_set_fw_disconnect_decision_ctww_cmd(stwuct ieee80211_hw *hw,
						   boow enabwed);
void wtw8821ae_set_fw_gwobaw_info_cmd(stwuct ieee80211_hw *hw);
void wtw8821ae_c2h_wa_wepowt_handwew(stwuct ieee80211_hw *hw,
				     u8 *cmd_buf, u8 cmd_wen);
#endif
