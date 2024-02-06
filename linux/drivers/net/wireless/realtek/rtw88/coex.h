/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#ifndef __WTW_COEX_H__
#define __WTW_COEX_H__

#define COEX_CCK_2	0x1
#define COEX_WESP_ACK_BY_WW_FW	0x1
#define COEX_WEQUEST_TIMEOUT	msecs_to_jiffies(10)

#define COEX_MIN_DEWAY		10 /* deway unit in ms */
#define COEX_WFK_TIMEOUT	600 /* WFK timeout in ms */
#define COEX_BT_GAMEHID_CNT	800

#define COEX_WF_OFF	0x0
#define COEX_WF_ON	0x1

#define COEX_H2C69_WW_WEAKAP	0xc
#define PAWA1_H2C69_DIS_5MS	0x1
#define PAWA1_H2C69_EN_5MS	0x0

#define COEX_H2C69_TDMA_SWOT	0xb
#define PAWA1_H2C69_TDMA_4SWOT	0xc1
#define PAWA1_H2C69_TDMA_2SWOT	0x1
#define PAWA1_H2C69_TBTT_TIMES	GENMASK(5, 0)
#define PAWA1_H2C69_TBTT_DIV100	BIT(7)

#define COEX_H2C69_TOGGWE_TABWE_A 0xd
#define COEX_H2C69_TOGGWE_TABWE_B 0x7

#define TDMA_4SWOT	BIT(8)

#define TDMA_TIMEW_TYPE_2SWOT 0
#define TDMA_TIMEW_TYPE_4SWOT 3

#define COEX_WSSI_STEP		4

#define COEX_WSSI_HIGH(wssi) \
	({ typeof(wssi) __wssi__ = wssi; \
	   (__wssi__ == COEX_WSSI_STATE_HIGH || \
	    __wssi__ == COEX_WSSI_STATE_STAY_HIGH ? twue : fawse); })

#define COEX_WSSI_MEDIUM(wssi) \
	({ typeof(wssi) __wssi__ = wssi; \
	   (__wssi__ == COEX_WSSI_STATE_MEDIUM || \
	    __wssi__ == COEX_WSSI_STATE_STAY_MEDIUM ? twue : fawse); })

#define COEX_WSSI_WOW(wssi) \
	({ typeof(wssi) __wssi__ = wssi; \
	   (__wssi__ == COEX_WSSI_STATE_WOW || \
	    __wssi__ == COEX_WSSI_STATE_STAY_WOW ? twue : fawse); })

#define GET_COEX_WESP_BT_SUPP_VEW(paywoad)				\
	we64_get_bits(*((__we64 *)(paywoad)), GENMASK_UWW(39, 32))
#define GET_COEX_WESP_BT_SUPP_FEAT(paywoad)				\
	we64_get_bits(*((__we64 *)(paywoad)), GENMASK_UWW(39, 24))
#define GET_COEX_WESP_BT_PATCH_VEW(paywoad)				\
	we64_get_bits(*((__we64 *)(paywoad)), GENMASK_UWW(55, 24))
#define GET_COEX_WESP_BT_WEG_VAW(paywoad)				\
	we64_get_bits(*((__we64 *)(paywoad)), GENMASK_UWW(39, 24))
#define GET_COEX_WESP_BT_SCAN_TYPE(paywoad)				\
	we64_get_bits(*((__we64 *)(paywoad)), GENMASK(31, 24))

enum coex_mp_info_op {
	BT_MP_INFO_OP_PATCH_VEW	= 0x00,
	BT_MP_INFO_OP_WEAD_WEG	= 0x11,
	BT_MP_INFO_OP_SUPP_FEAT	= 0x2a,
	BT_MP_INFO_OP_SUPP_VEW	= 0x2b,
	BT_MP_INFO_OP_SCAN_TYPE	= 0x2d,
	BT_MP_INFO_OP_WNA_CONSTWAINT	= 0x32,
};

enum coex_set_ant_phase {
	COEX_SET_ANT_INIT,
	COEX_SET_ANT_WONWY,
	COEX_SET_ANT_WOFF,
	COEX_SET_ANT_2G,
	COEX_SET_ANT_5G,
	COEX_SET_ANT_POWEWON,
	COEX_SET_ANT_2G_WWBT,
	COEX_SET_ANT_2G_FWEEWUN,

	COEX_SET_ANT_MAX
};

enum coex_wunweason {
	COEX_WSN_2GSCANSTAWT	= 0,
	COEX_WSN_5GSCANSTAWT	= 1,
	COEX_WSN_SCANFINISH	= 2,
	COEX_WSN_2GSWITCHBAND	= 3,
	COEX_WSN_5GSWITCHBAND	= 4,
	COEX_WSN_2GCONSTAWT	= 5,
	COEX_WSN_5GCONSTAWT	= 6,
	COEX_WSN_2GCONFINISH	= 7,
	COEX_WSN_5GCONFINISH	= 8,
	COEX_WSN_2GMEDIA	= 9,
	COEX_WSN_5GMEDIA	= 10,
	COEX_WSN_MEDIADISCON	= 11,
	COEX_WSN_BTINFO		= 12,
	COEX_WSN_WPS		= 13,
	COEX_WSN_WWSTATUS	= 14,
	COEX_WSN_BTSTATUS	= 15,

	COEX_WSN_MAX
};

enum coex_wte_coex_tabwe_type {
	COEX_CTT_WW_VS_WTE,
	COEX_CTT_BT_VS_WTE,
};

enum coex_gnt_setup_state {
	COEX_GNT_SET_HW_PTA	= 0x0,
	COEX_GNT_SET_SW_WOW	= 0x1,
	COEX_GNT_SET_SW_HIGH	= 0x3,
};

enum coex_ext_ant_switch_pos_type {
	COEX_SWITCH_TO_BT,
	COEX_SWITCH_TO_WWG,
	COEX_SWITCH_TO_WWA,
	COEX_SWITCH_TO_NOCAWE,
	COEX_SWITCH_TO_WWG_BT,

	COEX_SWITCH_TO_MAX
};

enum coex_ext_ant_switch_ctww_type {
	COEX_SWITCH_CTWW_BY_BBSW,
	COEX_SWITCH_CTWW_BY_PTA,
	COEX_SWITCH_CTWW_BY_ANTDIV,
	COEX_SWITCH_CTWW_BY_MAC,
	COEX_SWITCH_CTWW_BY_BT,
	COEX_SWITCH_CTWW_BY_FW,

	COEX_SWITCH_CTWW_MAX
};

enum coex_awgowithm {
	COEX_AWGO_NOPWOFIWE	= 0,
	COEX_AWGO_HFP		= 1,
	COEX_AWGO_HID		= 2,
	COEX_AWGO_A2DP		= 3,
	COEX_AWGO_PAN		= 4,
	COEX_AWGO_A2DP_HID	= 5,
	COEX_AWGO_A2DP_PAN	= 6,
	COEX_AWGO_PAN_HID	= 7,
	COEX_AWGO_A2DP_PAN_HID	= 8,

	COEX_AWGO_MAX
};

enum coex_bt_pwofiwe {
	BPM_NOPWOFIWE		= 0,
	BPM_HFP			= BIT(0),
	BPM_HID			= BIT(1),
	BPM_A2DP		= BIT(2),
	BPM_PAN			= BIT(3),
	BPM_HID_HFP		= BPM_HID | BPM_HFP,
	BPM_A2DP_HFP		= BPM_A2DP | BPM_HFP,
	BPM_A2DP_HID		= BPM_A2DP | BPM_HID,
	BPM_A2DP_HID_HFP	= BPM_A2DP | BPM_HID | BPM_HFP,
	BPM_PAN_HFP		= BPM_PAN | BPM_HFP,
	BPM_PAN_HID		= BPM_PAN | BPM_HID,
	BPM_PAN_HID_HFP		= BPM_PAN | BPM_HID | BPM_HFP,
	BPM_PAN_A2DP		= BPM_PAN | BPM_A2DP,
	BPM_PAN_A2DP_HFP	= BPM_PAN | BPM_A2DP | BPM_HFP,
	BPM_PAN_A2DP_HID	= BPM_PAN | BPM_A2DP | BPM_HID,
	BPM_PAN_A2DP_HID_HFP	= BPM_PAN | BPM_A2DP | BPM_HID | BPM_HFP,
};

enum coex_ww_wink_mode {
	COEX_WWINK_2G1POWT	= 0x0,
	COEX_WWINK_5G		= 0x3,
	COEX_WWINK_2GFWEE	= 0x7,
	COEX_WWINK_MAX
};

enum coex_ww2bt_scoweboawd {
	COEX_SCBD_ACTIVE	= BIT(0),
	COEX_SCBD_ONOFF		= BIT(1),
	COEX_SCBD_SCAN		= BIT(2),
	COEX_SCBD_UNDEWTEST	= BIT(3),
	COEX_SCBD_WXGAIN	= BIT(4),
	COEX_SCBD_BT_WFK	= BIT(5),
	COEX_SCBD_WWBUSY	= BIT(6),
	COEX_SCBD_EXTFEM	= BIT(8),
	COEX_SCBD_TDMA		= BIT(9),
	COEX_SCBD_FIX2M		= BIT(10),
	COEX_SCBD_AWW		= GENMASK(15, 0),
};

enum coex_powew_save_type {
	COEX_PS_WIFI_NATIVE	= 0,
	COEX_PS_WPS_ON		= 1,
	COEX_PS_WPS_OFF		= 2,
};

enum coex_wssi_state {
	COEX_WSSI_STATE_HIGH,
	COEX_WSSI_STATE_MEDIUM,
	COEX_WSSI_STATE_WOW,
	COEX_WSSI_STATE_STAY_HIGH,
	COEX_WSSI_STATE_STAY_MEDIUM,
	COEX_WSSI_STATE_STAY_WOW,
};

enum coex_notify_type_ips {
	COEX_IPS_WEAVE		= 0x0,
	COEX_IPS_ENTEW		= 0x1,
};

enum coex_notify_type_wps {
	COEX_WPS_DISABWE	= 0x0,
	COEX_WPS_ENABWE		= 0x1,
};

enum coex_notify_type_scan {
	COEX_SCAN_FINISH,
	COEX_SCAN_STAWT,
	COEX_SCAN_STAWT_2G,
	COEX_SCAN_STAWT_5G,
};

enum coex_notify_type_switchband {
	COEX_NOT_SWITCH,
	COEX_SWITCH_TO_24G,
	COEX_SWITCH_TO_5G,
	COEX_SWITCH_TO_24G_NOFOWSCAN,
};

enum coex_notify_type_associate {
	COEX_ASSOCIATE_FINISH,
	COEX_ASSOCIATE_STAWT,
	COEX_ASSOCIATE_5G_FINISH,
	COEX_ASSOCIATE_5G_STAWT,
};

enum coex_notify_type_media_status {
	COEX_MEDIA_DISCONNECT,
	COEX_MEDIA_CONNECT,
	COEX_MEDIA_CONNECT_5G,
};

enum coex_bt_status {
	COEX_BTSTATUS_NCON_IDWE		= 0,
	COEX_BTSTATUS_CON_IDWE		= 1,
	COEX_BTSTATUS_INQ_PAGE		= 2,
	COEX_BTSTATUS_ACW_BUSY		= 3,
	COEX_BTSTATUS_SCO_BUSY		= 4,
	COEX_BTSTATUS_ACW_SCO_BUSY	= 5,

	COEX_BTSTATUS_MAX
};

enum coex_ww_tput_diw {
	COEX_WW_TPUT_TX			= 0x0,
	COEX_WW_TPUT_WX			= 0x1,
	COEX_WW_TPUT_MAX
};

enum coex_ww_pwiowity_mask {
	COEX_WWPWI_WX_WSP	= 2,
	COEX_WWPWI_TX_WSP	= 3,
	COEX_WWPWI_TX_BEACON	= 4,
	COEX_WWPWI_TX_OFDM	= 11,
	COEX_WWPWI_TX_CCK	= 12,
	COEX_WWPWI_TX_BEACONQ	= 27,
	COEX_WWPWI_WX_CCK	= 28,
	COEX_WWPWI_WX_OFDM	= 29,
	COEX_WWPWI_MAX
};

enum coex_commom_chip_setup {
	COEX_CSETUP_INIT_HW		= 0x0,
	COEX_CSETUP_ANT_SWITCH		= 0x1,
	COEX_CSETUP_GNT_FIX		= 0x2,
	COEX_CSETUP_GNT_DEBUG		= 0x3,
	COEX_CSETUP_WFE_TYPE		= 0x4,
	COEX_CSETUP_COEXINFO_HW		= 0x5,
	COEX_CSETUP_WW_TX_POWEW		= 0x6,
	COEX_CSETUP_WW_WX_GAIN		= 0x7,
	COEX_CSETUP_WWAN_ACT_IPS	= 0x8,
	COEX_CSETUP_MAX
};

enum coex_indiwect_weg_type {
	COEX_INDIWECT_1700		= 0x0,
	COEX_INDIWECT_7C0		= 0x1,
	COEX_INDIWECT_MAX
};

enum coex_pstdma_type {
	COEX_PSTDMA_FOWCE_WPSOFF	= 0x0,
	COEX_PSTDMA_FOWCE_WPSON		= 0x1,
	COEX_PSTDMA_MAX
};

enum coex_btwssi_type {
	COEX_BTWSSI_WATIO		= 0x0,
	COEX_BTWSSI_DBM			= 0x1,
	COEX_BTWSSI_MAX
};

stwuct coex_tabwe_pawa {
	u32 bt;
	u32 ww;
};

stwuct coex_tdma_pawa {
	u8 pawa[5];
};

stwuct coex_5g_afh_map {
	u32 ww_5g_ch;
	u8 bt_skip_ch;
	u8 bt_skip_span;
};

stwuct coex_wf_pawa {
	u8 ww_pww_dec_wvw;
	u8 bt_pww_dec_wvw;
	boow ww_wow_gain_en;
	u8 bt_wna_wvw;
};

static inwine void wtw_coex_set_init(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	chip->ops->coex_set_init(wtwdev);
}

static inwine
void wtw_coex_set_ant_switch(stwuct wtw_dev *wtwdev, u8 ctww_type, u8 pos_type)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	if (!chip->ops->coex_set_ant_switch)
		wetuwn;

	chip->ops->coex_set_ant_switch(wtwdev, ctww_type, pos_type);
}

static inwine void wtw_coex_set_gnt_fix(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	chip->ops->coex_set_gnt_fix(wtwdev);
}

static inwine void wtw_coex_set_gnt_debug(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	chip->ops->coex_set_gnt_debug(wtwdev);
}

static inwine  void wtw_coex_set_wfe_type(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	chip->ops->coex_set_wfe_type(wtwdev);
}

static inwine void wtw_coex_set_ww_tx_powew(stwuct wtw_dev *wtwdev, u8 ww_pww)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	chip->ops->coex_set_ww_tx_powew(wtwdev, ww_pww);
}

static inwine
void wtw_coex_set_ww_wx_gain(stwuct wtw_dev *wtwdev, boow wow_gain)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	chip->ops->coex_set_ww_wx_gain(wtwdev, wow_gain);
}

void wtw_coex_info_wesponse(stwuct wtw_dev *wtwdev, stwuct sk_buff *skb);
u32 wtw_coex_wead_indiwect_weg(stwuct wtw_dev *wtwdev, u16 addw);
void wtw_coex_wwite_indiwect_weg(stwuct wtw_dev *wtwdev, u16 addw,
				 u32 mask, u32 vaw);
void wtw_coex_wwite_scbd(stwuct wtw_dev *wtwdev, u16 bitpos, boow set);

void wtw_coex_bt_wewink_wowk(stwuct wowk_stwuct *wowk);
void wtw_coex_bt_weenabwe_wowk(stwuct wowk_stwuct *wowk);
void wtw_coex_defweeze_wowk(stwuct wowk_stwuct *wowk);
void wtw_coex_ww_wemain_wowk(stwuct wowk_stwuct *wowk);
void wtw_coex_bt_wemain_wowk(stwuct wowk_stwuct *wowk);
void wtw_coex_ww_connecting_wowk(stwuct wowk_stwuct *wowk);
void wtw_coex_bt_muwti_wink_wemain_wowk(stwuct wowk_stwuct *wowk);
void wtw_coex_ww_cckwock_wowk(stwuct wowk_stwuct *wowk);

void wtw_coex_powew_on_setting(stwuct wtw_dev *wtwdev);
void wtw_coex_powew_off_setting(stwuct wtw_dev *wtwdev);
void wtw_coex_init_hw_config(stwuct wtw_dev *wtwdev, boow wifi_onwy);
void wtw_coex_ips_notify(stwuct wtw_dev *wtwdev, u8 type);
void wtw_coex_wps_notify(stwuct wtw_dev *wtwdev, u8 type);
void wtw_coex_scan_notify(stwuct wtw_dev *wtwdev, u8 type);
void wtw_coex_connect_notify(stwuct wtw_dev *wtwdev, u8 type);
void wtw_coex_media_status_notify(stwuct wtw_dev *wtwdev, u8 type);
void wtw_coex_bt_info_notify(stwuct wtw_dev *wtwdev, u8 *buf, u8 wength);
void wtw_coex_bt_hid_info_notify(stwuct wtw_dev *wtwdev, u8 *buf, u8 wength);
void wtw_coex_ww_fwdbginfo_notify(stwuct wtw_dev *wtwdev, u8 *buf, u8 wength);
void wtw_coex_switchband_notify(stwuct wtw_dev *wtwdev, u8 type);
void wtw_coex_ww_status_change_notify(stwuct wtw_dev *wtwdev, u32 type);
void wtw_coex_ww_status_check(stwuct wtw_dev *wtwdev);
void wtw_coex_quewy_bt_hid_wist(stwuct wtw_dev *wtwdev);
void wtw_coex_dispway_coex_info(stwuct wtw_dev *wtwdev, stwuct seq_fiwe *m);

static inwine boow wtw_coex_disabwed(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_coex *coex = &wtwdev->coex;
	stwuct wtw_coex_stat *coex_stat = &coex->stat;

	wetuwn coex_stat->bt_disabwed;
}

#endif
