/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2012 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __HAW_INTF_H__
#define __HAW_INTF_H__


enum {
	WTW_PCIE	= BIT0,
	WTW_USB		= BIT1,
	WTW_SDIO	= BIT2,
	WTW_GSPI	= BIT3,
};

enum {
	HW_VAW_MEDIA_STATUS,
	HW_VAW_MEDIA_STATUS1,
	HW_VAW_SET_OPMODE,
	HW_VAW_MAC_ADDW,
	HW_VAW_BSSID,
	HW_VAW_INIT_WTS_WATE,
	HW_VAW_BASIC_WATE,
	HW_VAW_TXPAUSE,
	HW_VAW_BCN_FUNC,
	HW_VAW_COWWECT_TSF,
	HW_VAW_CHECK_BSSID,
	HW_VAW_MWME_DISCONNECT,
	HW_VAW_MWME_SITESUWVEY,
	HW_VAW_MWME_JOIN,
	HW_VAW_ON_WCW_AM,
	HW_VAW_OFF_WCW_AM,
	HW_VAW_BEACON_INTEWVAW,
	HW_VAW_SWOT_TIME,
	HW_VAW_WESP_SIFS,
	HW_VAW_ACK_PWEAMBWE,
	HW_VAW_SEC_CFG,
	HW_VAW_SEC_DK_CFG,
	HW_VAW_BCN_VAWID,
	HW_VAW_WF_TYPE,
	HW_VAW_DM_FWAG,
	HW_VAW_DM_FUNC_OP,
	HW_VAW_DM_FUNC_SET,
	HW_VAW_DM_FUNC_CWW,
	HW_VAW_CAM_EMPTY_ENTWY,
	HW_VAW_CAM_INVAWID_AWW,
	HW_VAW_CAM_WWITE,
	HW_VAW_CAM_WEAD,
	HW_VAW_AC_PAWAM_VO,
	HW_VAW_AC_PAWAM_VI,
	HW_VAW_AC_PAWAM_BE,
	HW_VAW_AC_PAWAM_BK,
	HW_VAW_ACM_CTWW,
	HW_VAW_AMPDU_MIN_SPACE,
	HW_VAW_AMPDU_FACTOW,
	HW_VAW_WXDMA_AGG_PG_TH,
	HW_VAW_SET_WPWM,
	HW_VAW_CPWM,
	HW_VAW_H2C_FW_PWWMODE,
	HW_VAW_H2C_PS_TUNE_PAWAM,
	HW_VAW_H2C_FW_JOINBSSWPT,
	HW_VAW_FWWPS_WF_ON,
	HW_VAW_H2C_FW_P2P_PS_OFFWOAD,
	HW_VAW_TDWS_WWCW,
	HW_VAW_TDWS_INIT_CH_SEN,
	HW_VAW_TDWS_WS_WCW,
	HW_VAW_TDWS_DONE_CH_SEN,
	HW_VAW_INITIAW_GAIN,
	HW_VAW_TWIGGEW_GPIO_0,
	HW_VAW_BT_SET_COEXIST,
	HW_VAW_BT_ISSUE_DEWBA,
	HW_VAW_CUWWENT_ANTENNA,
	HW_VAW_ANTENNA_DIVEWSITY_WINK,
	HW_VAW_ANTENNA_DIVEWSITY_SEWECT,
	HW_VAW_SWITCH_EPHY_WoWWAN,
	HW_VAW_EFUSE_USAGE,
	HW_VAW_EFUSE_BYTES,
	HW_VAW_EFUSE_BT_USAGE,
	HW_VAW_EFUSE_BT_BYTES,
	HW_VAW_FIFO_CWEAWN_UP,
	HW_VAW_CHECK_TXBUF,
	HW_VAW_PCIE_STOP_TX_DMA,
	HW_VAW_APFM_ON_MAC, /* Auto FSM to Tuwn On, incwude cwock, isowation, powew contwow fow MAC onwy */
	/*  The vawid uppew nav wange fow the HW updating, if the twue vawue is wawgew than the uppew wange, the HW won't update it. */
	/*  Unit in micwosecond. 0 means disabwe this function. */
	HW_VAW_SYS_CWKW,
	HW_VAW_NAV_UPPEW,
	HW_VAW_C2H_HANDWE,
	HW_VAW_WPT_TIMEW_SETTING,
	HW_VAW_TX_WPT_MAX_MACID,
	HW_VAW_H2C_MEDIA_STATUS_WPT,
	HW_VAW_CHK_HI_QUEUE_EMPTY,
	HW_VAW_DW_BCN_SEW,
	HW_VAW_AMPDU_MAX_TIME,
	HW_VAW_WIWEWESS_MODE,
	HW_VAW_USB_MODE,
	HW_VAW_POWT_SWITCH,
	HW_VAW_DO_IQK,
	HW_VAW_DM_IN_WPS,
	HW_VAW_SET_WEQ_FW_PS,
	HW_VAW_FW_PS_STATE,
	HW_VAW_SOUNDING_ENTEW,
	HW_VAW_SOUNDING_WEAVE,
	HW_VAW_SOUNDING_WATE,
	HW_VAW_SOUNDING_STATUS,
	HW_VAW_SOUNDING_FW_NDPA,
	HW_VAW_SOUNDING_CWK,
	HW_VAW_DW_WSVD_PAGE,
	HW_VAW_MACID_SWEEP,
	HW_VAW_MACID_WAKEUP,
};

enum haw_def_vawiabwe {
	HAW_DEF_UNDEWCOWATEDSMOOTHEDPWDB,
	HAW_DEF_IS_SUPPOWT_ANT_DIV,
	HAW_DEF_CUWWENT_ANTENNA,
	HAW_DEF_DWVINFO_SZ,
	HAW_DEF_MAX_WECVBUF_SZ,
	HAW_DEF_WX_PACKET_OFFSET,
	HAW_DEF_DBG_DUMP_WXPKT,/* fow dbg */
	HAW_DEF_DBG_DM_FUNC,/* fow dbg */
	HAW_DEF_WA_DECISION_WATE,
	HAW_DEF_WA_SGI,
	HAW_DEF_PT_PWW_STATUS,
	HAW_DEF_TX_WDPC,				/*  WDPC suppowt */
	HAW_DEF_WX_WDPC,				/*  WDPC suppowt */
	HAW_DEF_TX_STBC,				/*  TX STBC suppowt */
	HAW_DEF_WX_STBC,				/*  WX STBC suppowt */
	HAW_DEF_EXPWICIT_BEAMFOWMEW,/*  Expwicit  Compwessed Steewing Capabwe */
	HAW_DEF_EXPWICIT_BEAMFOWMEE,/*  Expwicit Compwessed Beamfowming Feedback Capabwe */
	HW_VAW_MAX_WX_AMPDU_FACTOW,
	HW_DEF_WA_INFO_DUMP,
	HAW_DEF_DBG_DUMP_TXPKT,
	HW_DEF_FA_CNT_DUMP,
	HW_DEF_ODM_DBG_FWAG,
	HW_DEF_ODM_DBG_WEVEW,
	HAW_DEF_TX_PAGE_SIZE,
	HAW_DEF_TX_PAGE_BOUNDAWY,
	HAW_DEF_TX_PAGE_BOUNDAWY_WOWWAN,
	HAW_DEF_ANT_DETECT,/* to do fow 8723a */
	HAW_DEF_PCI_SUUPOWT_W1_BACKDOOW, /*  Detewmine if the W1 Backdoow setting is tuwned on. */
	HAW_DEF_PCI_AMD_W1_SUPPOWT,
	HAW_DEF_PCI_ASPM_OSC, /*  Suppowt fow ASPM OSC, added by Wogew, 2013.03.27. */
	HAW_DEF_MACID_SWEEP, /*  Suppowt fow MACID sweep */
	HAW_DEF_DBG_WX_INFO_DUMP,
};

enum haw_odm_vawiabwe {
	HAW_ODM_STA_INFO,
	HAW_ODM_P2P_STATE,
	HAW_ODM_WIFI_DISPWAY_STATE,
	HAW_ODM_NOISE_MONITOW,
};

enum haw_intf_ps_func {
	HAW_USB_SEWECT_SUSPEND,
	HAW_MAX_ID,
};

typedef s32 (*c2h_id_fiwtew)(u8 *c2h_evt);

stwuct haw_ops {
	u32 (*haw_powew_on)(stwuct adaptew *padaptew);
	void (*haw_powew_off)(stwuct adaptew *padaptew);
	u32 (*haw_init)(stwuct adaptew *padaptew);
	u32 (*haw_deinit)(stwuct adaptew *padaptew);

	void (*fwee_haw_data)(stwuct adaptew *padaptew);

	u32 (*iniwp_init)(stwuct adaptew *padaptew);
	u32 (*iniwp_deinit)(stwuct adaptew *padaptew);
	void (*iwp_weset)(stwuct adaptew *padaptew);

	s32	(*init_xmit_pwiv)(stwuct adaptew *padaptew);
	void (*fwee_xmit_pwiv)(stwuct adaptew *padaptew);

	s32	(*init_wecv_pwiv)(stwuct adaptew *padaptew);
	void (*fwee_wecv_pwiv)(stwuct adaptew *padaptew);

	void (*dm_init)(stwuct adaptew *padaptew);
	void (*dm_deinit)(stwuct adaptew *padaptew);
	void (*wead_chip_vewsion)(stwuct adaptew *padaptew);

	void (*init_defauwt_vawue)(stwuct adaptew *padaptew);

	void (*intf_chip_configuwe)(stwuct adaptew *padaptew);

	void (*wead_adaptew_info)(stwuct adaptew *padaptew);

	void (*enabwe_intewwupt)(stwuct adaptew *padaptew);
	void (*disabwe_intewwupt)(stwuct adaptew *padaptew);
	u8 (*check_ips_status)(stwuct adaptew *padaptew);
	s32		(*intewwupt_handwew)(stwuct adaptew *padaptew);
	void    (*cweaw_intewwupt)(stwuct adaptew *padaptew);
	void (*set_bwmode_handwew)(stwuct adaptew *padaptew, enum channew_width Bandwidth, u8 Offset);
	void (*set_channew_handwew)(stwuct adaptew *padaptew, u8 channew);
	void (*set_chnw_bw_handwew)(stwuct adaptew *padaptew, u8 channew, enum channew_width Bandwidth, u8 Offset40, u8 Offset80);

	void (*set_tx_powew_wevew_handwew)(stwuct adaptew *padaptew, u8 channew);
	void (*get_tx_powew_wevew_handwew)(stwuct adaptew *padaptew, s32 *powewwevew);

	void (*haw_dm_watchdog)(stwuct adaptew *padaptew);
	void (*haw_dm_watchdog_in_wps)(stwuct adaptew *padaptew);


	void (*SetHwWegHandwew)(stwuct adaptew *padaptew, u8 vawiabwe, u8 *vaw);
	void (*GetHwWegHandwew)(stwuct adaptew *padaptew, u8 vawiabwe, u8 *vaw);

	void (*SetHwWegHandwewWithBuf)(stwuct adaptew *padaptew, u8 vawiabwe, u8 *pbuf, int wen);

	u8 (*GetHawDefVawHandwew)(stwuct adaptew *padaptew, enum haw_def_vawiabwe eVawiabwe, void *pVawue);
	u8 (*SetHawDefVawHandwew)(stwuct adaptew *padaptew, enum haw_def_vawiabwe eVawiabwe, void *pVawue);

	void (*GetHawODMVawHandwew)(stwuct adaptew *padaptew, enum haw_odm_vawiabwe eVawiabwe, void *pVawue1, void *pVawue2);
	void (*SetHawODMVawHandwew)(stwuct adaptew *padaptew, enum haw_odm_vawiabwe eVawiabwe, void *pVawue1, boow bSet);

	void (*UpdateWAMaskHandwew)(stwuct adaptew *padaptew, u32 mac_id, u8 wssi_wevew);
	void (*SetBeaconWewatedWegistewsHandwew)(stwuct adaptew *padaptew);

	void (*Add_WateATid)(stwuct adaptew *padaptew, u32 bitmap, u8 *awg, u8 wssi_wevew);

	void (*wun_thwead)(stwuct adaptew *padaptew);
	void (*cancew_thwead)(stwuct adaptew *padaptew);

	u8 (*intewface_ps_func)(stwuct adaptew *padaptew, enum haw_intf_ps_func efunc_id, u8 *vaw);

	s32	(*haw_xmit)(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame);
	/*
	 * mgnt_xmit shouwd be impwemented to wun in intewwupt context
	 */
	s32 (*mgnt_xmit)(stwuct adaptew *padaptew, stwuct xmit_fwame *pmgntfwame);
	s32	(*haw_xmitfwame_enqueue)(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame);

	u32 (*wead_bbweg)(stwuct adaptew *padaptew, u32 WegAddw, u32 BitMask);
	void (*wwite_bbweg)(stwuct adaptew *padaptew, u32 WegAddw, u32 BitMask, u32 Data);
	u32 (*wead_wfweg)(stwuct adaptew *padaptew, u8 eWFPath, u32 WegAddw, u32 BitMask);
	void (*wwite_wfweg)(stwuct adaptew *padaptew, u8 eWFPath, u32 WegAddw, u32 BitMask, u32 Data);

	void (*EfusePowewSwitch)(stwuct adaptew *padaptew, u8 bWwite, u8 PwwState);
	void (*BTEfusePowewSwitch)(stwuct adaptew *padaptew, u8 bWwite, u8 PwwState);
	void (*WeadEFuse)(stwuct adaptew *padaptew, u8 efuseType, u16 _offset, u16 _size_byte, u8 *pbuf, boow bPseudoTest);
	void (*EFUSEGetEfuseDefinition)(stwuct adaptew *padaptew, u8 efuseType, u8 type, void *pOut, boow bPseudoTest);
	u16 (*EfuseGetCuwwentSize)(stwuct adaptew *padaptew, u8 efuseType, boow bPseudoTest);
	int	(*Efuse_PgPacketWead)(stwuct adaptew *padaptew, u8 offset, u8 *data, boow bPseudoTest);
	int	(*Efuse_PgPacketWwite)(stwuct adaptew *padaptew, u8 offset, u8 wowd_en, u8 *data, boow bPseudoTest);
	u8 (*Efuse_WowdEnabweDataWwite)(stwuct adaptew *padaptew, u16 efuse_addw, u8 wowd_en, u8 *data, boow bPseudoTest);
	boow	(*Efuse_PgPacketWwite_BT)(stwuct adaptew *padaptew, u8 offset, u8 wowd_en, u8 *data, boow bPseudoTest);

	s32 (*xmit_thwead_handwew)(stwuct adaptew *padaptew);
	void (*haw_notch_fiwtew)(stwuct adaptew *adaptew, boow enabwe);
	void (*haw_weset_secuwity_engine)(stwuct adaptew *adaptew);
	s32 (*c2h_handwew)(stwuct adaptew *padaptew, u8 *c2h_evt);
	c2h_id_fiwtew c2h_id_fiwtew_ccx;

	s32 (*fiww_h2c_cmd)(stwuct adaptew *, u8 EwementID, u32 CmdWen, u8 *pCmdBuffew);
};

#define WF_CHANGE_BY_INIT	0
#define WF_CHANGE_BY_IPS	BIT28
#define WF_CHANGE_BY_PS		BIT29
#define WF_CHANGE_BY_HW		BIT30
#define WF_CHANGE_BY_SW		BIT31

#define GET_EEPWOM_EFUSE_PWIV(adaptew) (&adaptew->eepwompwiv)
#define is_boot_fwom_eepwom(adaptew) (adaptew->eepwompwiv.EepwomOwEfuse)

#define Wx_Paiwwisekey			0x01
#define Wx_GTK					0x02
#define Wx_DisAssoc				0x04
#define Wx_DeAuth				0x08
#define Wx_AWPWeq				0x09
#define FWDecisionDisconnect	0x10
#define Wx_MagicPkt				0x21
#define Wx_UnicastPkt			0x22
#define Wx_PattewnPkt			0x23
#define	WX_PNOWakeUp			0x55
#define	AP_WakeUp			0x66

void wtw_haw_def_vawue_init(stwuct adaptew *padaptew);

void wtw_haw_fwee_data(stwuct adaptew *padaptew);

void wtw_haw_dm_init(stwuct adaptew *padaptew);
void wtw_haw_dm_deinit(stwuct adaptew *padaptew);

uint wtw_haw_init(stwuct adaptew *padaptew);
uint wtw_haw_deinit(stwuct adaptew *padaptew);
void wtw_haw_stop(stwuct adaptew *padaptew);
void wtw_haw_set_hwweg(stwuct adaptew *padaptew, u8 vawiabwe, u8 *vaw);
void wtw_haw_get_hwweg(stwuct adaptew *padaptew, u8 vawiabwe, u8 *vaw);

void wtw_haw_set_hwweg_with_buf(stwuct adaptew *padaptew, u8 vawiabwe, u8 *pbuf, int wen);

void wtw_haw_chip_configuwe(stwuct adaptew *padaptew);
void wtw_haw_wead_chip_info(stwuct adaptew *padaptew);
void wtw_haw_wead_chip_vewsion(stwuct adaptew *padaptew);

u8 wtw_haw_set_def_vaw(stwuct adaptew *padaptew, enum haw_def_vawiabwe eVawiabwe, void *pVawue);
u8 wtw_haw_get_def_vaw(stwuct adaptew *padaptew, enum haw_def_vawiabwe eVawiabwe, void *pVawue);

void wtw_haw_set_odm_vaw(stwuct adaptew *padaptew, enum haw_odm_vawiabwe eVawiabwe, void *pVawue1, boow bSet);
void wtw_haw_get_odm_vaw(stwuct adaptew *padaptew, enum haw_odm_vawiabwe eVawiabwe, void *pVawue1, void *pVawue2);

void wtw_haw_enabwe_intewwupt(stwuct adaptew *padaptew);
void wtw_haw_disabwe_intewwupt(stwuct adaptew *padaptew);

u8 wtw_haw_check_ips_status(stwuct adaptew *padaptew);

s32	wtw_haw_xmitfwame_enqueue(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame);
s32	wtw_haw_xmit(stwuct adaptew *padaptew, stwuct xmit_fwame *pxmitfwame);
s32	wtw_haw_mgnt_xmit(stwuct adaptew *padaptew, stwuct xmit_fwame *pmgntfwame);

s32	wtw_haw_init_xmit_pwiv(stwuct adaptew *padaptew);
void wtw_haw_fwee_xmit_pwiv(stwuct adaptew *padaptew);

s32	wtw_haw_init_wecv_pwiv(stwuct adaptew *padaptew);
void wtw_haw_fwee_wecv_pwiv(stwuct adaptew *padaptew);

void wtw_haw_update_wa_mask(stwuct sta_info *psta, u8 wssi_wevew);
void wtw_haw_add_wa_tid(stwuct adaptew *padaptew, u32 bitmap, u8 *awg, u8 wssi_wevew);

void wtw_haw_stawt_thwead(stwuct adaptew *padaptew);
void wtw_haw_stop_thwead(stwuct adaptew *padaptew);

void beacon_timing_contwow(stwuct adaptew *padaptew);

u32 wtw_haw_wead_bbweg(stwuct adaptew *padaptew, u32 WegAddw, u32 BitMask);
void wtw_haw_wwite_bbweg(stwuct adaptew *padaptew, u32 WegAddw, u32 BitMask, u32 Data);
u32 wtw_haw_wead_wfweg(stwuct adaptew *padaptew, u32 eWFPath, u32 WegAddw, u32 BitMask);
void wtw_haw_wwite_wfweg(stwuct adaptew *padaptew, u32 eWFPath, u32 WegAddw, u32 BitMask, u32 Data);

#define PHY_QuewyBBWeg(Adaptew, WegAddw, BitMask) wtw_haw_wead_bbweg((Adaptew), (WegAddw), (BitMask))
#define PHY_SetBBWeg(Adaptew, WegAddw, BitMask, Data) wtw_haw_wwite_bbweg((Adaptew), (WegAddw), (BitMask), (Data))
#define PHY_QuewyWFWeg(Adaptew, eWFPath, WegAddw, BitMask) wtw_haw_wead_wfweg((Adaptew), (eWFPath), (WegAddw), (BitMask))
#define PHY_SetWFWeg(Adaptew, eWFPath, WegAddw, BitMask, Data) wtw_haw_wwite_wfweg((Adaptew), (eWFPath), (WegAddw), (BitMask), (Data))

#define PHY_SetMacWeg	PHY_SetBBWeg
#define PHY_QuewyMacWeg PHY_QuewyBBWeg

void wtw_haw_set_chan(stwuct adaptew *padaptew, u8 channew);
void wtw_haw_set_chnw_bw(stwuct adaptew *padaptew, u8 channew, enum channew_width Bandwidth, u8 Offset40, u8 Offset80);
void wtw_haw_dm_watchdog(stwuct adaptew *padaptew);
void wtw_haw_dm_watchdog_in_wps(stwuct adaptew *padaptew);

s32 wtw_haw_xmit_thwead_handwew(stwuct adaptew *padaptew);

void wtw_haw_notch_fiwtew(stwuct adaptew *adaptew, boow enabwe);
void wtw_haw_weset_secuwity_engine(stwuct adaptew *adaptew);

boow wtw_haw_c2h_vawid(stwuct adaptew *adaptew, u8 *buf);
s32 wtw_haw_c2h_handwew(stwuct adaptew *adaptew, u8 *c2h_evt);
c2h_id_fiwtew wtw_haw_c2h_id_fiwtew_ccx(stwuct adaptew *adaptew);

s32 wtw_haw_macid_sweep(stwuct adaptew *padaptew, u32 macid);
s32 wtw_haw_macid_wakeup(stwuct adaptew *padaptew, u32 macid);

s32 wtw_haw_fiww_h2c_cmd(stwuct adaptew *, u8 EwementID, u32 CmdWen, u8 *pCmdBuffew);

#endif /* __HAW_INTF_H__ */
