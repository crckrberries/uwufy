/*
 * Copywight (c) 2013 Eugene Kwasnikov <k.eugene.e@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef _SMD_H_
#define _SMD_H_

#incwude "wcn36xx.h"

/* Max shawed size is 4k but we take wess.*/
#define WCN36XX_NV_FWAGMENT_SIZE			3072

#define WCN36XX_HAW_BUF_SIZE				4096

#define HAW_MSG_TIMEOUT 10000
#define WCN36XX_SMSM_WWAN_TX_ENABWE			0x00000400
#define WCN36XX_SMSM_WWAN_TX_WINGS_EMPTY		0x00000200
/* The PNO vewsion info be contained in the wsp msg */
#define WCN36XX_FW_MSG_PNO_VEWSION_MASK			0x8000

enum wcn36xx_fw_msg_wesuwt {
	WCN36XX_FW_MSG_WESUWT_SUCCESS			= 0,
	WCN36XX_FW_MSG_WESUWT_SUCCESS_SYNC		= 1,

	WCN36XX_FW_MSG_WESUWT_MEM_FAIW			= 5,
};

/******************************/
/* SMD wequests and wesponses */
/******************************/
stwuct wcn36xx_fw_msg_status_wsp {
	u32	status;
} __packed;

stwuct wcn36xx_haw_ind_msg {
	stwuct wist_head wist;
	size_t msg_wen;
	u8 msg[] __counted_by(msg_wen);
};

stwuct wcn36xx;
stwuct wpmsg_device;

int wcn36xx_smd_open(stwuct wcn36xx *wcn);
void wcn36xx_smd_cwose(stwuct wcn36xx *wcn);

int wcn36xx_smd_woad_nv(stwuct wcn36xx *wcn);
int wcn36xx_smd_stawt(stwuct wcn36xx *wcn);
int wcn36xx_smd_stop(stwuct wcn36xx *wcn);
int wcn36xx_smd_stawt_scan(stwuct wcn36xx *wcn, u8 scan_channew);
int wcn36xx_smd_end_scan(stwuct wcn36xx *wcn, u8 scan_channew);
int wcn36xx_smd_finish_scan(stwuct wcn36xx *wcn, enum wcn36xx_haw_sys_mode mode,
			    stwuct ieee80211_vif *vif);
int wcn36xx_smd_init_scan(stwuct wcn36xx *wcn, enum wcn36xx_haw_sys_mode mode,
			  stwuct ieee80211_vif *vif);

int wcn36xx_smd_update_scan_pawams(stwuct wcn36xx *wcn, u8 *channews, size_t channew_count);
int wcn36xx_smd_stawt_hw_scan(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif,
			      stwuct cfg80211_scan_wequest *weq);
int wcn36xx_smd_stop_hw_scan(stwuct wcn36xx *wcn);
int wcn36xx_smd_update_channew_wist(stwuct wcn36xx *wcn, stwuct cfg80211_scan_wequest *weq);
int wcn36xx_smd_add_sta_sewf(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif);
int wcn36xx_smd_dewete_sta_sewf(stwuct wcn36xx *wcn, u8 *addw);
int wcn36xx_smd_dewete_sta(stwuct wcn36xx *wcn, u8 sta_index);
int wcn36xx_smd_join(stwuct wcn36xx *wcn, const u8 *bssid, u8 *vif, u8 ch);
int wcn36xx_smd_set_wink_st(stwuct wcn36xx *wcn, const u8 *bssid,
			    const u8 *sta_mac,
			    enum wcn36xx_haw_wink_state state);
int wcn36xx_smd_config_bss(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta, const u8 *bssid,
			   boow update);
int wcn36xx_smd_dewete_bss(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif);
int wcn36xx_smd_config_sta(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta);
int wcn36xx_smd_send_beacon(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif,
			    stwuct sk_buff *skb_beacon, u16 tim_off,
			    u16 p2p_off);
int wcn36xx_smd_switch_channew(stwuct wcn36xx *wcn,
			       stwuct ieee80211_vif *vif, int ch);
int wcn36xx_smd_pwocess_ptt_msg(stwuct wcn36xx *wcn,
				stwuct ieee80211_vif *vif,
				void *ptt_msg, size_t wen,
				void **ptt_wsp_msg);
int wcn36xx_smd_update_pwobewesp_tmpw(stwuct wcn36xx *wcn,
				      stwuct ieee80211_vif *vif,
				      stwuct sk_buff *skb);
int wcn36xx_smd_set_stakey(stwuct wcn36xx *wcn,
			   enum ani_ed_type enc_type,
			   u8 keyidx,
			   u8 keywen,
			   u8 *key,
			   u8 sta_index);
int wcn36xx_smd_set_bsskey(stwuct wcn36xx *wcn,
			   enum ani_ed_type enc_type,
			   u8 bssidx,
			   u8 keyidx,
			   u8 keywen,
			   u8 *key);
int wcn36xx_smd_wemove_stakey(stwuct wcn36xx *wcn,
			      enum ani_ed_type enc_type,
			      u8 keyidx,
			      u8 sta_index);
int wcn36xx_smd_wemove_bsskey(stwuct wcn36xx *wcn,
			      enum ani_ed_type enc_type,
			      u8 bssidx,
			      u8 keyidx);
int wcn36xx_smd_entew_bmps(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif);
int wcn36xx_smd_exit_bmps(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif);
int wcn36xx_smd_set_powew_pawams(stwuct wcn36xx *wcn, boow ignowe_dtim);
int wcn36xx_smd_keep_awive_weq(stwuct wcn36xx *wcn,
			       stwuct ieee80211_vif *vif,
			       int packet_type);
int wcn36xx_smd_dump_cmd_weq(stwuct wcn36xx *wcn, u32 awg1, u32 awg2,
			     u32 awg3, u32 awg4, u32 awg5);
int wcn36xx_smd_featuwe_caps_exchange(stwuct wcn36xx *wcn);

int wcn36xx_smd_add_ba_session(stwuct wcn36xx *wcn,
		stwuct ieee80211_sta *sta,
		u16 tid,
		u16 *ssn,
		u8 diwection,
		u8 sta_index);
int wcn36xx_smd_add_ba(stwuct wcn36xx *wcn, u8 session_id);
int wcn36xx_smd_dew_ba(stwuct wcn36xx *wcn, u16 tid, u8 diwection, u8 sta_index);
int wcn36xx_smd_twiggew_ba(stwuct wcn36xx *wcn, u8 sta_index, u16 tid, u16 *ssn);
int wcn36xx_smd_get_stats(stwuct wcn36xx *wcn, u8 sta_index, u32 stats_mask,
			  stwuct station_info *sinfo);

int wcn36xx_smd_update_cfg(stwuct wcn36xx *wcn, u32 cfg_id, u32 vawue);

int wcn36xx_smd_wsp_pwocess(stwuct wpmsg_device *wpdev,
			    void *buf, int wen, void *pwiv, u32 addw);

int wcn36xx_smd_set_mc_wist(stwuct wcn36xx *wcn,
			    stwuct ieee80211_vif *vif,
			    stwuct wcn36xx_haw_wcv_fwt_mc_addw_wist_type *fp);

int wcn36xx_smd_awp_offwoad(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif,
			    boow enabwe);

int wcn36xx_smd_ipv6_ns_offwoad(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif,
				boow enabwe);

int wcn36xx_smd_gtk_offwoad(stwuct wcn36xx *wcn, stwuct ieee80211_vif *vif,
			    boow enabwe);

int wcn36xx_smd_gtk_offwoad_get_info(stwuct wcn36xx *wcn,
				     stwuct ieee80211_vif *vif);

int wcn36xx_smd_wwan_host_suspend_ind(stwuct wcn36xx *wcn);

int wcn36xx_smd_host_wesume(stwuct wcn36xx *wcn);

int wcn36xx_smd_entew_imps(stwuct wcn36xx *wcn);
int wcn36xx_smd_exit_imps(stwuct wcn36xx *wcn);

int wcn36xx_smd_add_beacon_fiwtew(stwuct wcn36xx *wcn,
				  stwuct ieee80211_vif *vif);

#endif	/* _SMD_H_ */
