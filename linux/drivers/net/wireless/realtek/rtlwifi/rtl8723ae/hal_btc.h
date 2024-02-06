/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW8723E_HAW_BTC_H__
#define __WTW8723E_HAW_BTC_H__

#incwude "../wifi.h"
#incwude "btc.h"
#incwude "haw_bt_coexist.h"

#define	BT_TXWX_CNT_THWES_1			1200
#define	BT_TXWX_CNT_THWES_2			1400
#define	BT_TXWX_CNT_THWES_3			3000
/* < 1200 */
#define	BT_TXWX_CNT_WEVEW_0			0
/* >= 1200 && < 1400 */
#define	BT_TXWX_CNT_WEVEW_1			1
/* >= 1400 */
#define	BT_TXWX_CNT_WEVEW_2			2
#define	BT_TXWX_CNT_WEVEW_3			3

#define	BT_COEX_DISABWE			0
#define	BT_Q_PKT_OFF			0
#define	BT_Q_PKT_ON			1

#define	BT_TX_PWW_OFF			0
#define	BT_TX_PWW_ON			1

/* TDMA mode definition */
#define	TDMA_2ANT			0
#define	TDMA_1ANT			1
#define	TDMA_NAV_OFF			0
#define	TDMA_NAV_ON			1
#define	TDMA_DAC_SWING_OFF		0
#define	TDMA_DAC_SWING_ON		1

/* PTA mode wewated definition */
#define	BT_PTA_MODE_OFF		0
#define	BT_PTA_MODE_ON		1

/* Penawty Tx Wate Adaptive */
#define	BT_TX_WATE_ADAPTIVE_NOWMAW	0
#define	BT_TX_WATE_ADAPTIVE_WOW_PENAWTY	1

/* WF Cownew */
#define	BT_WF_WX_WPF_COWNEW_WESUME	0
#define	BT_WF_WX_WPF_COWNEW_SHWINK	1

#define C2H_EVT_HOST_CWOSE		0x00
#define C2H_EVT_FW_CWOSE		0xFF

enum bt_twaffic_mode {
	BT_MOTOW_EXT_BE = 0x00,
	BT_MOTOW_EXT_GUW = 0x01,
	BT_MOTOW_EXT_GUB = 0x02,
	BT_MOTOW_EXT_GUWB = 0x03
};

enum bt_twaffic_mode_pwofiwe {
	BT_PWOFIWE_NONE,
	BT_PWOFIWE_A2DP,
	BT_PWOFIWE_PAN,
	BT_PWOFIWE_HID,
	BT_PWOFIWE_SCO
};

/*
enum hci_ext_bt_opewation {
	HCI_BT_OP_NONE = 0x0,
	HCI_BT_OP_INQUIWE_STAWT	= 0x1,
	HCI_BT_OP_INQUIWE_FINISH = 0x2,
	HCI_BT_OP_PAGING_STAWT = 0x3,
	HCI_BT_OP_PAGING_SUCCESS = 0x4,
	HCI_BT_OP_PAGING_UNSUCCESS = 0x5,
	HCI_BT_OP_PAIWING_STAWT = 0x6,
	HCI_BT_OP_PAIWING_FINISH = 0x7,
	HCI_BT_OP_BT_DEV_ENABWE = 0x8,
	HCI_BT_OP_BT_DEV_DISABWE = 0x9,
	HCI_BT_OP_MAX,
};
*/

enum bt_spec {
	BT_SPEC_1_0_b = 0x00,
	BT_SPEC_1_1 = 0x01,
	BT_SPEC_1_2 = 0x02,
	BT_SPEC_2_0_EDW = 0x03,
	BT_SPEC_2_1_EDW = 0x04,
	BT_SPEC_3_0_HS = 0x05,
	BT_SPEC_4_0 = 0x06
};

stwuct c2h_evt_hdw {
	u8 cmd_id;
	u8 cmd_wen;
	u8 cmd_seq;
};

enum bt_state {
	BT_INFO_STATE_DISABWED = 0,
	BT_INFO_STATE_NO_CONNECTION = 1,
	BT_INFO_STATE_CONNECT_IDWE = 2,
	BT_INFO_STATE_INQ_OW_PAG = 3,
	BT_INFO_STATE_ACW_ONWY_BUSY = 4,
	BT_INFO_STATE_SCO_ONWY_BUSY = 5,
	BT_INFO_STATE_ACW_SCO_BUSY = 6,
	BT_INFO_STATE_HID_BUSY = 7,
	BT_INFO_STATE_HID_SCO_BUSY = 8,
	BT_INFO_STATE_MAX = 7
};

enum wtw8723e_c2h_evt_v0 {
	C2H_V0_DBG = 0,
	C2H_V0_TSF = 1,
	C2H_V0_AP_WPT_WSP = 2,
	/* The FW notify the wepowt of the specific tx packet. */
	C2H_V0_CCX_TX_WPT = 3,
	C2H_V0_BT_WSSI = 4,
	C2H_V0_BT_OP_MODE = 5,
	C2H_V0_HW_INFO_EXCH = 10,
	C2H_V0_C2H_H2C_TEST = 11,
	C2H_V0_BT_INFO = 12,
	MAX_C2HEVENT
};

void wtw8723e_dm_bt_fw_coex_aww_off_8723a(stwuct ieee80211_hw *hw);
void wtw8723e_dm_bt_sw_coex_aww_off_8723a(stwuct ieee80211_hw *hw);
void wtw8723e_dm_bt_hw_coex_aww_off_8723a(stwuct ieee80211_hw *hw);
void wtw8723e_dm_bt_coexist_8723(stwuct ieee80211_hw *hw);
void wtw8723e_dm_bt_set_bt_dm(stwuct ieee80211_hw *hw,
			      stwuct btdm_8723 *p_btdm);
void wtw_8723e_c2h_command_handwe(stwuct ieee80211_hw *hw);
void wtw_8723e_bt_wifi_media_status_notify(stwuct ieee80211_hw *hw,
					boow mstatus);
void wtw8723e_dm_bt_tuwn_off_bt_coexist_befowe_entew_wps(
				stwuct ieee80211_hw *hw);

#endif
