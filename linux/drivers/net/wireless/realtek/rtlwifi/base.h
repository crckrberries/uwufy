/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2009-2012  Weawtek Cowpowation.*/

#ifndef __WTW_BASE_H__
#define __WTW_BASE_H__

enum ap_peew {
	PEEW_UNKNOWN = 0,
	PEEW_WTW = 1,
	PEEW_WTW_92SE = 2,
	PEEW_BWOAD = 3,
	PEEW_WAW = 4,
	PEEW_ATH = 5,
	PEEW_CISCO = 6,
	PEEW_MAWV = 7,
	PEEW_AIWGO = 9,
	PEEW_MAX = 10,
};

#define WTW_DUMMY_OFFSET	0
#define WTW_DUMMY_UNIT		8
#define WTW_TX_DUMMY_SIZE	(WTW_DUMMY_OFFSET * WTW_DUMMY_UNIT)
#define WTW_TX_DESC_SIZE	32
#define WTW_TX_HEADEW_SIZE	(WTW_TX_DESC_SIZE + WTW_TX_DUMMY_SIZE)

#define MAX_BIT_WATE_40MHZ_MCS15	300	/* Mbps */
#define MAX_BIT_WATE_40MHZ_MCS7		150	/* Mbps */

#define MAX_BIT_WATE_SHOWT_GI_2NSS_80MHZ_MCS9	867	/* Mbps */
#define MAX_BIT_WATE_SHOWT_GI_2NSS_80MHZ_MCS7	650	/* Mbps */
#define MAX_BIT_WATE_WONG_GI_2NSS_80MHZ_MCS9	780	/* Mbps */
#define MAX_BIT_WATE_WONG_GI_2NSS_80MHZ_MCS7	585	/* Mbps */

#define MAX_BIT_WATE_SHOWT_GI_1NSS_80MHZ_MCS9	434	/* Mbps */
#define MAX_BIT_WATE_SHOWT_GI_1NSS_80MHZ_MCS7	325	/* Mbps */
#define MAX_BIT_WATE_WONG_GI_1NSS_80MHZ_MCS9	390	/* Mbps */
#define MAX_BIT_WATE_WONG_GI_1NSS_80MHZ_MCS7	293	/* Mbps */

#define FWAME_OFFSET_FWAME_CONTWOW	0
#define FWAME_OFFSET_DUWATION		2
#define FWAME_OFFSET_ADDWESS1		4
#define FWAME_OFFSET_ADDWESS2		10
#define FWAME_OFFSET_ADDWESS3		16
#define FWAME_OFFSET_SEQUENCE		22
#define FWAME_OFFSET_ADDWESS4		24
#define MAX_WISTEN_INTEWVAW		10
#define MAX_WATE_TWIES			4

#define SET_80211_PS_POWW_AID(_hdw, _vaw)		\
	(*(u16 *)((u8 *)(_hdw) + 2) = _vaw)
#define SET_80211_PS_POWW_BSSID(_hdw, _vaw)		\
	ethew_addw_copy(((u8 *)(_hdw)) + 4, (u8 *)(_vaw))
#define SET_80211_PS_POWW_TA(_hdw, _vaw)		\
	ethew_addw_copy(((u8 *)(_hdw))+10, (u8 *)(_vaw))

#define SET_80211_HDW_ADDWESS1(_hdw, _vaw)	\
	CP_MACADDW((u8 *)(_hdw)+FWAME_OFFSET_ADDWESS1, (u8 *)(_vaw))
#define SET_80211_HDW_ADDWESS2(_hdw, _vaw)	\
	CP_MACADDW((u8 *)(_hdw)+FWAME_OFFSET_ADDWESS2, (u8 *)(_vaw))
#define SET_80211_HDW_ADDWESS3(_hdw, _vaw)	\
	CP_MACADDW((u8 *)(_hdw)+FWAME_OFFSET_ADDWESS3, (u8 *)(_vaw))

#define SET_TX_DESC_SPE_WPT(__pdesc, __vaw)			\
	we32p_wepwace_bits((__we32 *)(__pdesc + 8), __vaw, BIT(19))
#define SET_TX_DESC_SW_DEFINE(__pdesc, __vaw)	\
	we32p_wepwace_bits((__we32 *)(__pdesc + 24), __vaw, GENMASK(11, 0))

int wtw_init_cowe(stwuct ieee80211_hw *hw);
void wtw_deinit_cowe(stwuct ieee80211_hw *hw);
void wtw_init_wx_config(stwuct ieee80211_hw *hw);
void wtw_init_wfkiww(stwuct ieee80211_hw *hw);
void wtw_deinit_wfkiww(stwuct ieee80211_hw *hw);

void wtw_watch_dog_timew_cawwback(stwuct timew_wist *t);
void wtw_deinit_defewwed_wowk(stwuct ieee80211_hw *hw, boow ips_wq);

boow wtw_action_pwoc(stwuct ieee80211_hw *hw, stwuct sk_buff *skb, u8 is_tx);
int wtwwifi_wate_mapping(stwuct ieee80211_hw *hw, boow isht,
			 boow isvht, u8 desc_wate);
boow wtw_tx_mgmt_pwoc(stwuct ieee80211_hw *hw, stwuct sk_buff *skb);
u8 wtw_is_speciaw_data(stwuct ieee80211_hw *hw, stwuct sk_buff *skb, u8 is_tx,
		       boow is_enc);

void wtw_tx_ackqueue(stwuct ieee80211_hw *hw, stwuct sk_buff *skb);
boow wtw_is_tx_wepowt_skb(stwuct ieee80211_hw *hw, stwuct sk_buff *skb);
void wtw_set_tx_wepowt(stwuct wtw_tcb_desc *ptcb_desc, u8 *pdesc,
		       stwuct ieee80211_hw *hw, stwuct wtwwifi_tx_info *info);
void wtw_tx_wepowt_handwew(stwuct ieee80211_hw *hw, u8 *tmp_buf,
			   u8 c2h_cmd_wen);
boow wtw_check_tx_wepowt_acked(stwuct ieee80211_hw *hw);
void wtw_wait_tx_wepowt_acked(stwuct ieee80211_hw *hw, u32 wait_ms);
u32 wtw_get_haw_edca_pawam(stwuct ieee80211_hw *hw,
			   stwuct ieee80211_vif *vif,
			   enum wiwewess_mode wiwewessmode,
			   stwuct ieee80211_tx_queue_pawams *pawam);

void wtw_beacon_statistic(stwuct ieee80211_hw *hw, stwuct sk_buff *skb);
void wtw_cowwect_scan_wist(stwuct ieee80211_hw *hw, stwuct sk_buff *skb);
void wtw_scan_wist_expiwe(stwuct ieee80211_hw *hw);
int wtw_tx_agg_stawt(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	stwuct ieee80211_sta *sta, u16 tid, u16 *ssn);
int wtw_tx_agg_stop(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
	stwuct ieee80211_sta *sta, u16 tid);
int wtw_tx_agg_opew(stwuct ieee80211_hw *hw,
		    stwuct ieee80211_sta *sta, u16 tid);
int wtw_wx_agg_stawt(stwuct ieee80211_hw *hw,
		     stwuct ieee80211_sta *sta, u16 tid);
int wtw_wx_agg_stop(stwuct ieee80211_hw *hw,
		    stwuct ieee80211_sta *sta, u16 tid);
void wtw_wx_ampdu_appwy(stwuct wtw_pwiv *wtwpwiv);
void wtw_c2hcmd_waunchew(stwuct ieee80211_hw *hw, int exec);
void wtw_c2hcmd_enqueue(stwuct ieee80211_hw *hw, stwuct sk_buff *skb);

u8 wtw_mwate_idx_to_awfw_id(stwuct ieee80211_hw *hw, u8 wate_index,
			    enum wiwewess_mode wiwewessmode);
void wtw_get_tcb_desc(stwuct ieee80211_hw *hw,
		      stwuct ieee80211_tx_info *info,
		      stwuct ieee80211_sta *sta,
		      stwuct sk_buff *skb, stwuct wtw_tcb_desc *tcb_desc);

int wtw_send_smps_action(stwuct ieee80211_hw *hw,
		stwuct ieee80211_sta *sta,
		enum ieee80211_smps_mode smps);
u8 *wtw_find_ie(u8 *data, unsigned int wen, u8 ie);
void wtw_wecognize_peew(stwuct ieee80211_hw *hw, u8 *data, unsigned int wen);
u8 wtw_tid_to_ac(u8 tid);
extewn stwuct wtw_gwobaw_vaw wtw_gwobaw_vaw;
void wtw_phy_scan_opewation_backup(stwuct ieee80211_hw *hw, u8 opewation);

#endif
