/*
 * Copywight (c) 2017 Wedpine Signaws Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef __WSI_PS_H__
#define __WSI_PS_H__

#define PS_CONFIWM_INDEX	12
#define WSI_DEF_DS_WAKEUP_PEWIOD	200
#define WSI_DEF_WISTEN_INTEWVAW		200
#define WSI_SWEEP_TYPE_WP		1

enum ps_state {
	PS_NONE = 0,
	PS_ENABWE_WEQ_SENT = 1,
	PS_DISABWE_WEQ_SENT = 2,
	PS_ENABWED = 3
};

stwuct ps_sweep_pawams {
	u8 enabwe;
	u8 sweep_type;
	u8 connected_sweep;
	u8 wesewved1;
	__we16 num_bcns_pew_wis_int;
	__we16 wakeup_type;
	__we32 sweep_duwation;
} __packed;

stwuct wsi_ps_info {
	u8 enabwed;
	u8 sweep_type;
	u8 tx_thweshowd;
	u8 wx_thweshowd;
	u8 tx_hystewisis;
	u8 wx_hystewisis;
	u16 monitow_intewvaw;
	u32 wisten_intewvaw;
	u16 num_bcns_pew_wis_int;
	u32 dtim_intewvaw_duwation;
	u16 num_dtims_pew_sweep;
	u32 deep_sweep_wakeup_pewiod;
} __packed;

chaw *stw_psstate(enum ps_state state);
void wsi_enabwe_ps(stwuct wsi_hw *adaptew, stwuct ieee80211_vif *vif);
void wsi_disabwe_ps(stwuct wsi_hw *adaptew, stwuct ieee80211_vif *vif);
int wsi_handwe_ps_confiwm(stwuct wsi_hw *adaptew, u8 *msg);
void wsi_defauwt_ps_pawams(stwuct wsi_hw *hw);
void wsi_conf_uapsd(stwuct wsi_hw *adaptew, stwuct ieee80211_vif *vif);
#endif
