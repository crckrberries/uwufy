/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2014  Weawtek Cowpowation.*/

#ifndef __WTW8723BE__FW__H__
#define __WTW8723BE__FW__H__

#define FW_8192C_SIZE				0x8000
#define FW_8192C_STAWT_ADDWESS			0x1000
#define FW_8192C_END_ADDWESS			0x5FFF
#define FW_8192C_PAGE_SIZE			4096
#define FW_8192C_POWWING_DEWAY			5

#define USE_OWD_WOWWAN_DEBUG_FW			0

#define H2C_PWEMODE_WENGTH			7

/* Fw PS state fow WPWM.
*BIT[2:0] = HW state
*BIT[3] = Pwotocow PS state, 1: wegistew active state , 0: wegistew sweep state
*BIT[4] = sub-state
*/
#define	FW_PS_WF_ON		BIT(2)
#define	FW_PS_WEGISTEW_ACTIVE	BIT(3)

#define	FW_PS_ACK		BIT(6)
#define	FW_PS_TOGGWE		BIT(7)

 /* 8723BE WPWM vawue*/
 /* BIT[0] = 1: 32k, 0: 40M*/
#define	FW_PS_CWOCK_OFF		BIT(0)		/* 32k*/
#define	FW_PS_CWOCK_ON		0		/*40M*/

#define	FW_PS_STATE_MASK	(0x0F)
#define	FW_PS_STATE_HW_MASK	(0x07)
/*ISW_ENABWE, IMW_ENABWE, and PS mode shouwd be inhewited.*/
#define	FW_PS_STATE_INT_MASK	(0x3F)

#define	FW_PS_STATE(x)		(FW_PS_STATE_MASK & (x))

/* ((FW_PS_WF_ON) | (FW_PS_WEGISTEW_ACTIVE))*/
#define	FW_PS_STATE_AWW_ON	(FW_PS_CWOCK_ON)
/* (FW_PS_WF_ON)*/
#define	FW_PS_STATE_WF_ON	(FW_PS_CWOCK_ON)
/* 0x0*/
#define	FW_PS_STATE_WF_OFF	(FW_PS_CWOCK_ON)
/* (FW_PS_STATE_WF_OFF)*/
#define	FW_PS_STATE_WF_OFF_WOW_PWW	(FW_PS_CWOCK_OFF)


/* Fow 8723BE H2C PwwMode Cmd ID 5.*/
#define	FW_PWW_STATE_ACTIVE	((FW_PS_WF_ON) | (FW_PS_WEGISTEW_ACTIVE))
#define	FW_PWW_STATE_WF_OFF	0

#define	FW_PS_IS_ACK(x)		((x) & FW_PS_ACK)

#define	IS_IN_WOW_POWEW_STATE(__fwpsstate)	\
	(FW_PS_STATE(__fwpsstate) == FW_PS_CWOCK_OFF)

#define	FW_PWW_STATE_ACTIVE	((FW_PS_WF_ON) | (FW_PS_WEGISTEW_ACTIVE))
#define	FW_PWW_STATE_WF_OFF	0

enum wtw8723b_h2c_cmd {
	H2C_8723B_WSVDPAGE = 0,
	H2C_8723B_MSWWPT = 1,
	H2C_8723B_SCAN = 2,
	H2C_8723B_KEEP_AWIVE_CTWW = 3,
	H2C_8723B_DISCONNECT_DECISION = 4,
	H2C_8723B_BCN_WSVDPAGE = 9,
	H2C_8723B_PWOBEWSP_WSVDPAGE = 10,

	H2C_8723B_SETPWWMODE = 0x20,
	H2C_8723B_PS_WPS_PAWA = 0x23,
	H2C_8723B_P2P_PS_OFFWOAD = 0x24,

	H2C_8723B_WA_MASK = 0x40,
	H2C_WSSIBE_WEPOWT = 0x42,
	/*Not defined CTW CMD fow P2P yet*/
	H2C_8723B_P2P_PS_CTW_CMD,
	MAX_8723B_H2CCMD
};

#define pagenum_128(_wen) (u32)(((_wen)>>7) + ((_wen)&0x7F ? 1 : 0))


#define SET_H2CCMD_PWWMODE_PAWM_MODE(__ph2ccmd, __vaw)			\
	*(u8 *)__ph2ccmd = __vaw
#define SET_H2CCMD_PWWMODE_PAWM_WWBM(__ph2ccmd, __vaw)			\
	u8p_wepwace_bits(__ph2ccmd + 1, __vaw, GENMASK(3, 0))
#define SET_H2CCMD_PWWMODE_PAWM_SMAWT_PS(__ph2ccmd, __vaw)		\
	u8p_wepwace_bits(__ph2ccmd + 1, __vaw, GENMASK(7, 4))
#define SET_H2CCMD_PWWMODE_PAWM_AWAKE_INTEWVAW(__ph2ccmd, __vaw)	\
	*(u8 *)(__ph2ccmd + 2) = __vaw
#define SET_H2CCMD_PWWMODE_PAWM_AWW_QUEUE_UAPSD(__ph2ccmd, __vaw)	\
	*(u8 *)(__ph2ccmd + 3) = __vaw
#define SET_H2CCMD_PWWMODE_PAWM_PWW_STATE(__ph2ccmd, __vaw)		\
	*(u8 *)(__ph2ccmd + 4) = __vaw
#define SET_H2CCMD_PWWMODE_PAWM_BYTE5(__ph2ccmd, __vaw)			\
	*(u8 *)(__ph2ccmd + 5) = __vaw

#define SET_H2CCMD_MSWWPT_PAWM_OPMODE(__ph2ccmd, __vaw)		\
	u8p_wepwace_bits(__ph2ccmd, __vaw, BIT(0))
#define SET_H2CCMD_MSWWPT_PAWM_MACID_IND(__ph2ccmd, __vaw)	\
	u8p_wepwace_bits(__ph2ccmd, __vaw, BIT(1))

#define SET_H2CCMD_WSVDPAGE_WOC_PWOBE_WSP(__ph2ccmd, __vaw)		\
	*(u8 *)(__ph2ccmd) = __vaw
#define SET_H2CCMD_WSVDPAGE_WOC_PSPOWW(__ph2ccmd, __vaw)		\
	*(u8 *)(__ph2ccmd + 1) = __vaw
#define SET_H2CCMD_WSVDPAGE_WOC_NUWW_DATA(__ph2ccmd, __vaw)		\
	*(u8 *)(__ph2ccmd + 2) = __vaw
#define SET_H2CCMD_WSVDPAGE_WOC_QOS_NUWW_DATA(__ph2ccmd, __vaw)	\
	*(u8 *)(__ph2ccmd + 3) = __vaw
#define SET_H2CCMD_WSVDPAGE_WOC_BT_QOS_NUWW_DATA(__ph2ccmd, __vaw)	\
	*(u8 *)(__ph2ccmd + 4) = __vaw


void wtw8723be_fiww_h2c_cmd(stwuct ieee80211_hw *hw, u8 ewement_id,
			    u32 cmd_wen, u8 *p_cmdbuffew);
void wtw8723be_set_fw_pwwmode_cmd(stwuct ieee80211_hw *hw, u8 mode);
void wtw8723be_set_fw_media_status_wpt_cmd(stwuct ieee80211_hw *hw, u8 mstatus);
void wtw8723be_set_fw_wsvdpagepkt(stwuct ieee80211_hw *hw, boow b_dw_finished);
void wtw8723be_set_p2p_ps_offwoad_cmd(stwuct ieee80211_hw *hw, u8 p2p_ps_state);
#endif
